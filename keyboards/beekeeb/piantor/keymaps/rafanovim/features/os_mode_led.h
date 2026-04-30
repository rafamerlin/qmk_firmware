#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifndef SPLIT_TRANSACTION_IDS_USER
#define SPLIT_TRANSACTION_IDS_USER RPC_ID_USER_LED_SYNC
#endif

void os_mode_led_init(void);
void os_mode_led_task(void);
void os_mode_led_toggle(void);
void os_mode_led_set_layer_lock(bool active);
