#include "os_mode_led.h"

#include <string.h>

#include QMK_KEYBOARD_H
#include "split_util.h"
#include "transactions.h"

#define PICO_BOARD_LED_PIN GP25
#define LED_PWM_PERIOD 8
#define LED_PWM_INTERVAL_MS 1
#define LED_MAX_DUTY 3
#define LED_LOW_DUTY 1
#define OS_ANIMATION_DURATION_MS 5000
#define MAC_BLINK_PERIOD_MS 500
#define LED_SYNC_RETRY_MS 20

typedef enum {
    OS_MODE_LINUX = 0,
    OS_MODE_MAC,
} os_mode_t;

typedef struct {
    uint8_t os_mode;
    bool    layer_lock_active;
    uint8_t animation_nonce;
} led_sync_state_t;

static led_sync_state_t synced_state      = {.os_mode = OS_MODE_LINUX, .layer_lock_active = false, .animation_nonce = 1};
static uint8_t          led_pwm_phase     = 0;
static uint32_t         led_pwm_tick_time = 0;
static uint32_t         animation_start   = 0;
static uint8_t          local_nonce       = 0;
static bool             sync_pending      = false;
static uint32_t         last_sync_attempt = 0;

static bool is_linux_mode(void) {
    return synced_state.os_mode == OS_MODE_LINUX;
}

static bool should_send_state(void) {
    return is_keyboard_master() && is_transport_connected();
}

static bool is_animation_active(void) {
    return timer_elapsed32(animation_start) < OS_ANIMATION_DURATION_MS;
}

static void restart_local_animation(void) {
    animation_start = timer_read32();
    local_nonce     = synced_state.animation_nonce;
}

static bool pwm_gate(uint8_t duty) {
    return duty >= LED_PWM_PERIOD || led_pwm_phase < duty;
}

static uint8_t left_led_duty(void) {
    if (!is_keyboard_left() || !is_animation_active()) {
        return 0;
    }

    if (is_linux_mode()) {
        return LED_MAX_DUTY;
    }

    return (timer_elapsed32(animation_start) / MAC_BLINK_PERIOD_MS) % 2 == 0 ? LED_MAX_DUTY : 0;
}

static uint8_t right_led_duty(void) {
    if (!is_keyboard_left() && synced_state.layer_lock_active) {
        return LED_LOW_DUTY;
    }

    return 0;
}

static void write_local_led(void) {
    uint8_t duty = is_keyboard_left() ? left_led_duty() : right_led_duty();
    gpio_write_pin(PICO_BOARD_LED_PIN, pwm_gate(duty));
}

static void mark_sync_pending(void) {
    sync_pending = true;
}

static void sync_from_remote(const led_sync_state_t *incoming_state) {
    bool nonce_changed = synced_state.animation_nonce != incoming_state->animation_nonce;

    memcpy(&synced_state, incoming_state, sizeof(synced_state));

    if (nonce_changed) {
        restart_local_animation();
    }

    write_local_led();
}

static void led_sync(uint8_t initiator2target_buffer_size, const void *initiator2target_buffer, uint8_t target2initiator_buffer_size, void *target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(synced_state)) {
        sync_from_remote((const led_sync_state_t *)initiator2target_buffer);
    }
}

static void send_led_state_if_needed(void) {
    if (!sync_pending || !should_send_state()) {
        return;
    }

    if (timer_elapsed32(last_sync_attempt) < LED_SYNC_RETRY_MS) {
        return;
    }

    last_sync_attempt = timer_read32();
    if (transaction_rpc_send(RPC_ID_USER_LED_SYNC, sizeof(synced_state), &synced_state)) {
        sync_pending = false;
    }
}

void os_mode_led_init(void) {
    transaction_register_rpc(RPC_ID_USER_LED_SYNC, led_sync);
    gpio_set_pin_output(PICO_BOARD_LED_PIN);
    led_pwm_phase     = 0;
    led_pwm_tick_time = timer_read32();
    last_sync_attempt = timer_read32();
    restart_local_animation();
    mark_sync_pending();
    write_local_led();
}

void os_mode_led_task(void) {
    if (timer_elapsed32(led_pwm_tick_time) >= LED_PWM_INTERVAL_MS) {
        led_pwm_tick_time = timer_read32();
        led_pwm_phase     = (led_pwm_phase + 1) % LED_PWM_PERIOD;
        write_local_led();
    }

    send_led_state_if_needed();
}

void os_mode_led_toggle(void) {
    synced_state.os_mode = is_linux_mode() ? OS_MODE_MAC : OS_MODE_LINUX;
    synced_state.animation_nonce++;
    restart_local_animation();
    mark_sync_pending();
    write_local_led();
}

void os_mode_led_set_layer_lock(bool active) {
    if (synced_state.layer_lock_active == active) {
        return;
    }

    synced_state.layer_lock_active = active;
    mark_sync_pending();
    write_local_led();
}
