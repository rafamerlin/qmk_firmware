#pragma once

#include <stdbool.h>
#include <stdint.h>

void os_mode_led_init(void);
void os_mode_led_task(void);
void os_mode_led_toggle(bool is_mac);
void os_mode_led_set_layer_lock(bool active);
