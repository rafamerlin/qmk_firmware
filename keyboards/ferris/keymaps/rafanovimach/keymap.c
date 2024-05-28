// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include <stdint.h>
#include QMK_KEYBOARD_H
#include "g/keymap_combo.h"

#ifdef ACHORDION_ENABLE
#include "features/achordion.h"
#endif

#ifdef TAPPING_TERM_PER_KEY
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // case KC_A:
        // case KC_I:
        // case KC_SCLN:
        //     return TAPPING_TERM + 50;
        case MT(MOD_LSFT, KC_Z):
        case MT(MOD_RSFT, KC_SLSH):
            return TAPPING_TERM - 100;
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

#ifdef HOLD_ON_OTHER_KEY_PRESS_PER_KEY
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MT(MOD_LSFT, KC_Z):
        case MT(MOD_RSFT, KC_SLSH):
            // Immediately select the hold action when another key is pressed.
            return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}
#endif
// Custom keycodes for the actions on Layer 8
enum custom_keycodes {
    FIRST_VD = SAFE_RANGE,
    SECOND_VD,
    THIRD_VD,
    FOURTH_VD,
    WORD_BK,
    WORD_FWD,
    C_GODEF,
    C_GOIMP,
    C_GOREF,
    C_BACK,
    C_FORWARD,
    TG_NAV
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x5_2(
  //,----------------------------------------.                    ,-----------------------------------------------------.
     KC_Q,    KC_W,    LT(8, KC_E),    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,
  //|----+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     MT(MOD_LGUI, KC_A),    MT(MOD_LCTL, KC_S),    MT(MOD_LALT, KC_D),    MT(MOD_LSFT, KC_F),    LT(9, KC_G),            KC_H,    MT(MOD_RSFT, KC_J),    MT(MOD_RALT, KC_K),    MT(MOD_RCTL, KC_L), MT(MOD_RGUI, KC_SCLN),
  //|----+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     MT(MOD_LSFT, KC_Z),    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, MT(MOD_RSFT, KC_SLSH),
  //|----+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          LT(2, KC_TAB),  LT(5, KC_ENT),   LT(3, KC_SPC),   LT(1, KC_BSPC)
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
      KC_LSFT,    KC_X,    KC_C,    KC_V, XXXXXXX,                      XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           TG_NAV,  TG_NAV,     TG_NAV, KC_DEL
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
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+|
                                          KC_RPRN,  KC_ENT,     KC_BTN1, KC_BTN2
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
                                          KC_RPRN,  KC_ENT,     KC_SPC, _______
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
         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+|
         KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+|
         KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+|
                                          _______,  KC_ENT,     KC_SPC, _______
                                      //`--------------------------'  `--------------------------'
  ),

// extra
    [8] = LAYOUT_split_3x5_2(
  //,--------------------------------------------.                    ,---------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, FIRST_VD, SECOND_VD, XXXXXXX, KC_KB_VOLUME_UP,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, THIRD_VD, FOURTH_VD, XXXXXXX, KC_KB_VOLUME_DOWN,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPLY,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+|
                                          QK_BOOT,  KC_ENT,    XXXXXXX, KC_APP
                                      //`--------------------------'  `--------------------------'
  ),

// coding
    [9] = LAYOUT_split_3x5_2(
    //,--------------------------------------------.                    ,---------------------------------------------.
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, C_GODEF, C_GOIMP, C_GOREF, XXXXXXX,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+|
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,  C_BACK, XXXXXXX,C_FORWARD, XXXXXXX,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+|
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+|
                                            XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX
                                        //`--------------------------'  `--------------------------'
    )
};

static bool navlayer_locked = false;

void matrix_scan_user(void) {
    #ifdef ACHORDION_ENABLE
        achordion_task();
    #endif
}

//Default implementation, let's see how it will behave
//https://getreuer.info/posts/keyboards/achordion/index.html
#ifdef ACHORDION_ENABLE
    bool achordion_chord(uint16_t tap_hold_keycode,
                        keyrecord_t* tap_hold_record,
                        uint16_t other_keycode,
                        keyrecord_t* other_record) {


        // Exceptionally consider the following chords as holds, even though they
        // are on the same hand
        switch (tap_hold_keycode) {
            case MT(MOD_LCTL, KC_S): //Ctrl left hand
                // We want to avoid an accidental Ctrl+Q but allow any keys in the left hand
                if (other_keycode == KC_Q ) { return false; }
                else if (on_left_hand(tap_hold_record->event.key)) { return true;}
                break;

            case MT(MOD_LALT, KC_D):
                if (other_keycode == LT(2, KC_TAB)) {return true;}
                break;
        }

        // Also allow same-hand holds when the other key is in the rows below the
        // alphas. I need the `% (MATRIX_ROWS / 2)` because my keyboard is split.
        if (other_record->event.key.row % (MATRIX_ROWS / 2) >= 3) { return true; }

        // Also allow same-hand holds when the held key is in the rows below the
        // alphas. I need the `% (MATRIX_ROWS / 2)` because my keyboard is split.
        if (tap_hold_record->event.key.row % (MATRIX_ROWS / 2) >= 3) { return true; }
    
        return achordion_opposite_hands(tap_hold_record, other_record);
    }

    uint16_t achordion_timeout(uint16_t tap_hold_keycode) {
       return 800;
    }
#endif

#ifdef ACHORDION_STREAK
    uint16_t achordion_streak_timeout(uint16_t tap_hold_keycode) {
        // if (IS_QK_LAYER_TAP(tap_hold_keycode)) {
        //     return 0;  // Disable streak detection on layer-tap keys.
        // }

        // Otherwise, tap_hold_keycode is a mod-tap key.
        uint8_t mod = mod_config(QK_MOD_TAP_GET_MODS(tap_hold_keycode));
        if ((mod & MOD_LSFT) != 0 || (mod & MOD_RSFT) != 0) {
            return 50;  // A shorter streak timeout for Shift mod-tap keys.
        } else {
            return 120;  // A longer timeout otherwise.
        }
    }
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #ifdef ACHORDION_ENABLE
        if (!process_achordion(keycode, record)) { return false; }
    #endif

    bool custom_keypress = false;
    switch (keycode) {
        case WORD_FWD:
        case WORD_BK:
        case TG_NAV:
        case LT(2, KC_TAB): //Used on the locking nav
            custom_keypress = true;
            break;
    }

    if (!record->event.pressed && !custom_keypress) {
        return true; // Skip all release events
    }
    switch (keycode) {
        //Leaving more complex stuff at the top
        
        // Locking navigation layer
        case TG_NAV:
            if (record->event.pressed) {
                navlayer_locked = !navlayer_locked;
                if (navlayer_locked) {
                    layer_on(2);
                } else {
                    layer_off(2);
                }
            }
            return false;
        case LT(2, KC_TAB):
            if (record->event.pressed) {
                if (!navlayer_locked) {
                    layer_on(2);
                }
            } else {
                if (!navlayer_locked && layer_state_is(2)) {
                    layer_off(2);
                }
            
                //We need to check if it was tapped and send the tab manually as LT kind of breaks with these changes
                if (record->tap.count != 0) {
                    tap_code(KC_TAB);
                }
            }   
            return false;
        // ^ Locking layer2

        case WORD_BK:
            // Press Ctrl + Left
            // Doing it this way as if I hold it I want it to continue happenin
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_LEFT);
            } else {
                unregister_code(KC_LEFT);
                unregister_code(KC_LCTL);
            }
            break;
        case WORD_FWD:
            // Press Ctrl + Left
            // Doing it this way as if I hold it I want it to continue happenin
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_RIGHT);
            } else {
                unregister_code(KC_RIGHT);
                unregister_code(KC_LCTL);
            }  
            break; 
        case FIRST_VD:
            // Press Win + Ctrl + Up + Left
            register_code(KC_LWIN);
            register_code(KC_LCTL);
            tap_code(KC_UP);
            tap_code(KC_LEFT);
            unregister_code(KC_LCTL);
            unregister_code(KC_LWIN);
            break;
        case SECOND_VD:
            // Press Win + Ctrl + Up + Right
            register_code(KC_LWIN);
            register_code(KC_LCTL);
            tap_code(KC_UP);
            tap_code(KC_RGHT);
            unregister_code(KC_LCTL);
            unregister_code(KC_LWIN);
            break;
        case THIRD_VD:
            // Press Win + Ctrl + Down + Left
            register_code(KC_LWIN);
            register_code(KC_LCTL);
            tap_code(KC_DOWN);
            tap_code(KC_LEFT);
            unregister_code(KC_LCTL);
            unregister_code(KC_LWIN);
            break;
        case FOURTH_VD:
            // Press Win + Ctrl + Down + Right
            register_code(KC_LWIN);
            register_code(KC_LCTL);
            tap_code(KC_DOWN);
            tap_code(KC_RGHT);
            unregister_code(KC_LCTL);
            unregister_code(KC_LWIN);
            break;
        case C_BACK:
            // Press Ctrl + -
            register_code(KC_LCTL);
            tap_code(KC_MINUS);
            unregister_code(KC_LCTL);
            break;
        case C_FORWARD:
            // Press Ctrl + =
            register_code(KC_LCTL);
            tap_code(KC_EQL);
            unregister_code(KC_LCTL);
            break; 
        case C_GODEF:
            // Press F12
            tap_code(KC_F12);
            break; 
        case C_GOIMP:
            // Press Ctrl + F12
            register_code(KC_LCTL);
            tap_code(KC_F12);
            unregister_code(KC_LCTL);
            break; 
        case C_GOREF:
            // Press Shift + F12
            register_code(KC_LSFT);
            tap_code(KC_F12);
            unregister_code(KC_LSFT);
            break;
    }
    return true;
}