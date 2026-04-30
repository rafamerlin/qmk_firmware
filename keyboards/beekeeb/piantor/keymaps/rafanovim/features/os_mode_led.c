#include "os_mode_led.h"

#include <string.h>

#include QMK_KEYBOARD_H
#include "split_util.h"
#include "transactions.h"

#define PICO_BOARD_LED_PIN GP25
#define LED_PWM_PERIOD 16
#define LED_PWM_INTERVAL_MS 1

typedef struct {
    bool    is_linux_mode;
    uint8_t brightness_index;
} led_state_t;

static const uint8_t led_brightness_steps[] = {0, 2, 6, LED_PWM_PERIOD};
static led_state_t   led_state               = {.is_linux_mode = false, .brightness_index = 2};
static uint8_t       led_pwm_phase           = 0;
static uint32_t      led_pwm_tick_timer      = 0;

static uint8_t led_brightness_step_count(void) {
    return sizeof(led_brightness_steps) / sizeof(led_brightness_steps[0]);
}

static bool should_light_local_half(void) {
    return led_state.is_linux_mode ? is_keyboard_left() : !is_keyboard_left();
}

static void write_os_mode_led(void) {
    bool is_active_side = should_light_local_half();
    bool led_on         = false;

    if (should_light_local_half() && led_state.brightness_index < led_brightness_step_count()) {
        uint8_t duty = led_brightness_steps[led_state.brightness_index];
        led_on       = duty >= LED_PWM_PERIOD || led_pwm_phase < duty;
    }

    gpio_write_pin(PICO_BOARD_LED_PIN, is_active_side && led_on);
}

static void sync_os_mode_led(void) {
    write_os_mode_led();
}

static void send_led_state(void) {
    if (is_transport_connected()) {
        transaction_rpc_send(RPC_ID_USER_LED_SYNC, sizeof(led_state), &led_state);
    }
}

static void apply_led_state_change(void) {
    sync_os_mode_led();
    send_led_state();
}

static void led_sync(uint8_t initiator2target_buffer_size, const void *initiator2target_buffer, uint8_t target2initiator_buffer_size, void *target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(led_state)) {
        memcpy(&led_state, initiator2target_buffer, sizeof(led_state));
        sync_os_mode_led();
    }
}

void os_mode_led_init(void) {
    transaction_register_rpc(RPC_ID_USER_LED_SYNC, led_sync);
    gpio_set_pin_output(PICO_BOARD_LED_PIN);
    led_pwm_phase      = 0;
    led_pwm_tick_timer = timer_read32();
    sync_os_mode_led();
}

void os_mode_led_task(void) {
    if (timer_elapsed32(led_pwm_tick_timer) < LED_PWM_INTERVAL_MS) {
        return;
    }

    led_pwm_tick_timer = timer_read32();
    led_pwm_phase      = (led_pwm_phase + 1) % LED_PWM_PERIOD;
    write_os_mode_led();
}

void os_mode_led_toggle(void) {
    led_state.is_linux_mode = !led_state.is_linux_mode;
    apply_led_state_change();
}

void os_mode_led_increase_brightness(void) {
    uint8_t max_index = led_brightness_step_count() - 1;

    if (led_state.brightness_index < max_index) {
        led_state.brightness_index++;
    }

    apply_led_state_change();
}

void os_mode_led_decrease_brightness(void) {
    if (led_state.brightness_index > 0) {
        led_state.brightness_index--;
    }

    apply_led_state_change();
}
