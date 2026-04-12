// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include <stdint.h>
#include QMK_KEYBOARD_H
#include "g/keymap_combo.h"
#include "features/layer_lock.h"

#define KC_COPY_UPDATED LCTL(KC_C)
#define KC_CUT_UPDATED LCTL(KC_X)
#define KC_PASTE_UPDATED LCTL(KC_V)
#define KC_UNDO_UPDATED LCTL(KC_Z)
#define KC_REDO_UPDATED LCTL(KC_Y)
#define KC_FOCUS_BROWSER_BAR LCTL(KC_L)
#define SHORTCUT_TAP_DELAY 10

enum custom_keycodes {
    LLOCK = SAFE_RANGE,
    LEFT_VD,
    RIGHT_VD,
    FIRST_VD,
    SECOND_VD,
    THIRD_VD,
    FOURTH_VD,
    FIRST_PROG_VD,
    SECOND_PROG_VD,
    THIRD_PROG_VD,
    FOURTH_PROG_VD,
    WORD_BK,
    WORD_FWD,
    C_GODEF,
    C_GOIMP,
    C_GOREF,
    C_GODECL,
    C_BACK,
    C_FORWARD,
    SH_F7
};

#ifdef TAPPING_TERM_PER_KEY
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MT(MOD_LSFT, KC_Z):
            return TAPPING_TERM - 75;
        case MT(MOD_RSFT, KC_SLSH):
            return TAPPING_TERM - 75;

        // Attempting to avoid 'This' typing '}his' instead
        case LT(3, KC_SPC):
            return TAPPING_TERM + 25;

        // Trying to avoid actuaction of backspace when trying to type other stuff
        case LT(1, KC_BSPC):
            return TAPPING_TERM - 25;

        case MT(MOD_RCTL, KC_L):
            return TAPPING_TERM + 50;

        default:
            return TAPPING_TERM;
    }
}
#endif

#ifdef PERMISSIVE_HOLD_PER_KEY
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Make shift great again
        case MT(MOD_LSFT, KC_Z):
        case MT(MOD_LSFT, KC_F):
        case MT(MOD_RSFT, KC_J):
        case MT(MOD_RSFT, KC_SLSH):
            return true;
        default:
            return false;
    }
}
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x5_2(
  //,----------------------------------------.                    ,-----------------------------------------------------.
     KC_Q,    KC_W,    LT(8, KC_E),    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,
  //|----+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     MT(MOD_LGUI, KC_A),    MT(MOD_LCTL, KC_S),    MT(MOD_LALT, KC_D),    MT(MOD_LSFT, KC_F),    LT(9, KC_G),            KC_H,    MT(MOD_RSFT, KC_J),    MT(MOD_RALT, KC_K),    MT(MOD_RCTL, KC_L), MT(MOD_RGUI, KC_SCLN),
  //|----+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     MT(MOD_LSFT, KC_Z),    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, MT(MOD_RSFT, KC_SLSH),
  //|----+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                    LT(2, KC_TAB),  LT(5, KC_ENT),    LT(3, KC_SPC),   LT(1, KC_BSPC)
                                      //`--------------------------'  `--------------------------'

  ),

// numbers
    [1] = LAYOUT_split_3x5_2(
  //,------------------------------------------.                    ,-----------------------------------------------------.
      KC_LBRC,    KC_7,    KC_8,    KC_9,    KC_RBRC,                XXXXXXX,  KC_LCBR, KC_RCBR, XXXXXXX, XXXXXXX,
  //|------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_QUOT,   KC_4,    KC_5,    KC_6, KC_EQL,                      XXXXXXX, KC_LPRN , KC_RPRN,  KC_DQT, KC_QUOT,
  //|------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_GRV,    KC_1,    KC_2,    KC_3, KC_BSLS,                      XXXXXXX, KC_LBRC, KC_RBRC, XXXXXXX, XXXXXXX,
  //|------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_0,  KC_PMNS,     KC_SPC,   MO(3)
                                      //`--------------------------'  `--------------------------'
  ),

// navigation
    [2] = LAYOUT_split_3x5_2(
  //,---------------------------------------------.                   ,-----------------------------------------------------.
      XXXXXXX, WORD_BK,WORD_FWD, XXXXXXX, XXXXXXX,                       XXXXXXX, KC_HOME,   KC_UP,  KC_END, KC_PGUP,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LGUI, KC_LCTL, KC_LALT, KC_LSFT, KC_MINUS,                     XXXXXXX, KC_LEFT, KC_DOWN,KC_RIGHT, KC_PGDN,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_X,    KC_C,    KC_V, XXXXXXX,                      XXXXXXX,  SH_F7,  KC_F7, XXXXXXX, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        XXXXXXX,  XXXXXXX,     LLOCK, KC_DEL
                                      //`--------------------------'  `--------------------------'
  ),

// symbols
    [3] = LAYOUT_split_3x5_2(
  //,--------------------------------------------.                    ,---------------------------------------------
      KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,                      XXXXXXX, KC_LCBR, KC_RCBR, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+|
      KC_DQT, KC_DLR, KC_PERC, KC_CIRC, KC_PLUS,                      XXXXXXX, KC_LPRN, KC_RPRN, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+|
      KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_PIPE,                      XXXXXXX, KC_LBRC, KC_RBRC, XXXXXXX, QK_BOOT,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+|
                                        KC_RPRN,  KC_UNDS,     KC_SPC, _______
                                      //`--------------------------'  `--------------------------'
  ),

// mouse
    [4] = LAYOUT_split_3x5_2(
  //,--------------------------------------------.                    ,---------------------------------------------
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+|
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      MS_LEFT, MS_DOWN, MS_UP, MS_RGHT, XXXXXXX,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+|
                                         KC_RPRN,  KC_ENT,     MS_BTN1, MS_BTN2
                                      //`--------------------------'  `--------------------------'
  ),

// function
    [5] = LAYOUT_split_3x5_2(
  //,--------------------------------------------.                    ,-----------------------------------------------.
      KC_F12, KC_F7, KC_F8, KC_F9, KC_PSCR,                               KC_PSCR, KC_F7, KC_F8, KC_F9, KC_F12,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--|
      KC_F11, KC_F4, KC_F5, KC_F6, KC_LSFT,                               KC_RSFT, KC_F4, KC_F5, KC_F6, KC_F11,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--|
      KC_F10, KC_F1, KC_F2, KC_F3, KC_PAUS,                               KC_PAUS, KC_F1, KC_F2, KC_F3, KC_F10,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--|
                                        KC_RPRN,  KC_ENT,     KC_UNDS, KC_PMNS
                                      //`--------------------------'  `--------------------------'
  ),

  // media
    [6] = LAYOUT_split_3x5_2(
  //,--------------------------------------------.                    ,----------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+-|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_MSEL,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+-|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+-|
                                            KC_RPRN,  KC_ENT,     KC_MUTE, KC_MPLY
                                      //`--------------------------'  `--------------------------'
  ),

// gaming
    [7] = LAYOUT_split_3x5_2(
  //,--------------------------------------------.                    ,---------------------------------------------.
         KC_Q,    KC_1,    KC_2,    KC_3,    KC_4,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+|
      KC_LCTL,    KC_A,    KC_W,    KC_D,    KC_E,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+|
      KC_LSFT,    KC_C,    KC_S,    KC_R,    KC_F,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+|
                                         KC_SPC,  KC_G,                     KC_SPC, TO(0)
                                      //`--------------------------'  `--------------------------'
  ),

// extra
    [8] = LAYOUT_split_3x5_2(
  //,--------------------------------------------.                    ,---------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, FIRST_PROG_VD, SECOND_PROG_VD, XXXXXXX, KC_VOLU,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, THIRD_PROG_VD, FOURTH_PROG_VD, XXXXXXX, KC_VOLD,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+|
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, LEFT_VD, RIGHT_VD, XXXXXXX, KC_MPLY,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+|
                                             TO(7), KC_ENT,    KC_APP, KC_APP
                                      //`--------------------------'  `--------------------------'
  ),

// coding
    [9] = LAYOUT_split_3x5_2(
    //,--------------------------------------------.                    ,---------------------------------------------.
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     C_GODECL, C_GODEF, C_GOIMP, C_GOREF, XXXXXXX,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+|
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,  C_BACK, XXXXXXX,C_FORWARD, XXXXXXX,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+|
        KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+|
                                            XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX
                                        //`--------------------------'  `--------------------------'
    )
};

static bool is_changing_desktop = false;
static uint8_t current_virtual_desktop = 1;

static void tap_shortcut(uint16_t keycode) {
    tap_code16_delay(keycode, SHORTCUT_TAP_DELAY);
}

static void multi_tap(uint8_t times, uint16_t keycode) {
    for (uint8_t i = 0; i < times; i++) {
        tap_shortcut(keycode);
    }
}

static void move_to_desktop(uint8_t desired) {
    if (is_changing_desktop) {
        return;
    }

    is_changing_desktop = true;

    switch (desired) {
        case 1:
            multi_tap(3, LCTL(LGUI(KC_LEFT)));
            break;
        case 4:
            multi_tap(3, LCTL(LGUI(KC_RGHT)));
            break;
        case 2:
        case 3: {
            uint8_t movement = current_virtual_desktop > desired ? current_virtual_desktop - desired : desired - current_virtual_desktop;
            uint16_t keycode = (current_virtual_desktop < desired) ? LCTL(LGUI(KC_RGHT)) : LCTL(LGUI(KC_LEFT));

            multi_tap(movement, keycode);
            break;
        }
    }

    current_virtual_desktop = desired;
    is_changing_desktop = false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_layer_lock(keycode, record, LLOCK)) { return false; }

    bool custom_keypress = false;
    switch (keycode) {
        case WORD_FWD:
        case WORD_BK:
            custom_keypress = true;
            break;
    }

    if (!record->event.pressed && !custom_keypress) {
        return true; // Skip all release events
    }
    switch (keycode) {
        case WORD_BK:
            if (record->event.pressed) {
                register_code16(LCTL(KC_LEFT));
            } else {
                unregister_code16(LCTL(KC_LEFT));
            }
            break;
        case WORD_FWD:
            if (record->event.pressed) {
                register_code16(LCTL(KC_RGHT));
            } else {
                unregister_code16(LCTL(KC_RGHT));
            }
            break;
        case LEFT_VD:
            tap_shortcut(LCTL(LGUI(KC_LEFT)));
            break;
        case RIGHT_VD:
            tap_shortcut(LCTL(LGUI(KC_RGHT)));
            break;
        case FIRST_VD:
            tap_shortcut(LCTL(LGUI(KC_UP)));
            tap_shortcut(LCTL(LGUI(KC_LEFT)));
            break;
        case SECOND_VD:
            tap_shortcut(LCTL(LGUI(KC_UP)));
            tap_shortcut(LCTL(LGUI(KC_RGHT)));
            break;
        case THIRD_VD:
            tap_shortcut(LCTL(LGUI(KC_DOWN)));
            tap_shortcut(LCTL(LGUI(KC_LEFT)));
            break;
        case FOURTH_VD:
            tap_shortcut(LCTL(LGUI(KC_DOWN)));
            tap_shortcut(LCTL(LGUI(KC_RGHT)));
            break;
        case FIRST_PROG_VD:
            move_to_desktop(1);
            break;
        case SECOND_PROG_VD:
            move_to_desktop(2);
            break;
        case THIRD_PROG_VD:
            move_to_desktop(3);
            break;
        case FOURTH_PROG_VD:
            move_to_desktop(4);
            break;
        case C_BACK:
            tap_shortcut(LCTL(KC_MINS));
            break;
        case C_FORWARD:
            tap_shortcut(LCTL(KC_EQL));
            break;
        case C_GODEF:
            tap_shortcut(KC_F12);
            break;
        case C_GOIMP:
            tap_shortcut(LCTL(KC_F12));
            break;
        case C_GOREF:
            tap_shortcut(LSFT(KC_F12));
            break;
        case C_GODECL:
            tap_shortcut(LCTL(LSFT(LALT(KC_F12))));
            break;
        case SH_F7:
            tap_shortcut(LSFT(KC_F7));
            break;
    }
    return true;
}