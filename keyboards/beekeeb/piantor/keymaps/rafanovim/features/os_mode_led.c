#include "os_mode_led.h"

#include QMK_KEYBOARD_H
#include "split_util.h"
#include "transactions.h"

#define PICO_BOARD_LED_PIN GP25
#define OS_ANIMATION_DURATION_MS 5000
#define MAC_BLINK_PERIOD_MS 500
#define LED_SYNC_RETRY_MS 50
#define LED_SYNC_MAX_RETRIES 5

static bool     is_mac_mode          = false;
static bool     layer_lock_active    = false;
static uint32_t animation_start      = 0;
static bool     animation_running    = false;

static bool     sync_pending         = false;
static uint32_t last_sync_attempt    = 0;
static uint8_t  sync_retries         = 0;

static bool left_led_on(void) {
    if (!is_keyboard_left() || !animation_running) {
        return false;
    }

    if (timer_elapsed32(animation_start) >= OS_ANIMATION_DURATION_MS) {
        animation_running = false;
        return false;
    }

    if (!is_mac_mode) {
        return true;
    }

    return (timer_elapsed32(animation_start) / MAC_BLINK_PERIOD_MS) % 2 == 0;
}

static bool right_led_on(void) {
    return !is_keyboard_left() && layer_lock_active;
}

static void write_led(void) {
    bool on = is_keyboard_left() ? left_led_on() : right_led_on();
    gpio_write_pin(PICO_BOARD_LED_PIN, on);
}

static void sync_from_remote(uint8_t initiator2target_buffer_size, const void *initiator2target_buffer, uint8_t target2initiator_buffer_size, void *target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(uint8_t)) {
        layer_lock_active = *(const uint8_t *)initiator2target_buffer;
        write_led();
    }
}

static void send_sync_if_needed(void) {
    if (!sync_pending) return;
    if (!is_keyboard_master() || !is_transport_connected()) return;
    if (timer_elapsed32(last_sync_attempt) < LED_SYNC_RETRY_MS) return;

    last_sync_attempt = timer_read32();
    uint8_t val = layer_lock_active;
    if (transaction_rpc_send(RPC_ID_USER_LED_SYNC, sizeof(uint8_t), &val)) {
        sync_pending = false;
        sync_retries = 0;
    } else if (++sync_retries >= LED_SYNC_MAX_RETRIES) {
        sync_pending = false;
        sync_retries = 0;
    }
}

void os_mode_led_init(void) {
    transaction_register_rpc(RPC_ID_USER_LED_SYNC, sync_from_remote);
    gpio_set_pin_output(PICO_BOARD_LED_PIN);
    last_sync_attempt = timer_read32();
    animation_start   = timer_read32();
    animation_running = true;
    sync_pending      = true;
    write_led();
}

void os_mode_led_task(void) {
    if (is_keyboard_left() && animation_running) {
        write_led();
    }
    send_sync_if_needed();
}

void os_mode_led_toggle(bool is_mac) {
    is_mac_mode       = is_mac;
    animation_start   = timer_read32();
    animation_running = true;
    write_led();
}

void os_mode_led_set_layer_lock(bool active) {
    if (layer_lock_active == active) return;
    layer_lock_active = active;
    sync_pending  = true;
    sync_retries  = 0;
    write_led();
}
