#include <stdint.h>
#include QMK_KEYBOARD_H
#include "g/keymap_combo.h"
#include "features/layer_lock.h"
#include "features/os_mode_led.h"
#include "keymap_brazilian_abnt2.h"

// macOS modifier swap for the Piantor (System Settings → Keyboard → Modifier Keys):
//   Option (LALT) → Command,  Command (LGUI) → Option
// So in mac_mode, to make macOS see:
//   Command → send LALT
//   Option  → send LGUI
//   Control → send LCTL (unchanged)
#define SHORTCUT_TAP_DELAY 10
// Custom keycodes for the actions on Layer 8
enum custom_keycodes {
    LLOCK = SAFE_RANGE,
    //Basic left and right for windows and linux if configured
    LEFT_VD,
    RIGHT_VD,
    //These are to emulate linux desktops on windows
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
    SH_F7,
    OS_MODE_TOG,
    C_PSCR,
    C_HOME,
    C_END,
    C_VOLU,
    C_VOLD,
    C_PROMPTS
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
    [0] = LAYOUT_split_3x5_3(
  //,----------------------------------------.                    ,-----------------------------------------------------.
     KC_Q,    KC_W,    LT(8, KC_E),    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,
  //|----+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     MT(MOD_LGUI, KC_A),    MT(MOD_LCTL, KC_S),    MT(MOD_LALT, KC_D),    MT(MOD_LSFT, KC_F),    LT(9, KC_G),            KC_H,    MT(MOD_RSFT, KC_J),    MT(MOD_RALT, KC_K),    MT(MOD_RCTL, KC_L), MT(MOD_RGUI, KC_SCLN),
  //|----+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     MT(MOD_LSFT, KC_Z),    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, MT(MOD_RSFT, KC_SLSH),
  //|----+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                  LT(10,KC_ESC), LT(2, KC_TAB),  LT(5, KC_ENT),           LT(3, KC_SPC),   LT(1, KC_BSPC), LT(1, KC_DEL)
                                      //`--------------------------'  `--------------------------'

  ),

// numbers
    [1] = LAYOUT_split_3x5_3(
  //,------------------------------------------.                    ,-----------------------------------------------------.
      KC_LBRC,    KC_7,    KC_8,    KC_9,    KC_RBRC,                XXXXXXX,  KC_LCBR, KC_RCBR, XXXXXXX, XXXXXXX,
  //|------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_QUOT,   KC_4,    KC_5,    KC_6, KC_EQL,                      XXXXXXX, KC_LPRN , KC_RPRN,  KC_DQT, KC_QUOT,
  //|------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_GRV,    KC_1,    KC_2,    KC_3, KC_BSLS,                      XXXXXXX, KC_LBRC, KC_RBRC, XXXXXXX, XXXXXXX,
  //|------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                KC_DOT, KC_0,  KC_PMNS,     KC_SPC,   MO(3),  KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

// navigation
    [2] = LAYOUT_split_3x5_3(
  //,---------------------------------------------.                   ,-----------------------------------------------------.
      XXXXXXX, WORD_BK,WORD_FWD, XXXXXXX, XXXXXXX,                       XXXXXXX, C_HOME,   KC_UP,  C_END, KC_PGUP,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LGUI, KC_LCTL, KC_LALT, KC_LSFT, KC_MINUS,                     XXXXXXX, KC_LEFT, KC_DOWN,KC_RIGHT, KC_PGDN,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_X,    KC_C,    KC_V, XXXXXXX,                      XXXXXXX,  SH_F7,  KC_F7, XXXXXXX, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                XXXXXXX, XXXXXXX,  XXXXXXX,     LLOCK, KC_DEL, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

// symbols
    [3] = LAYOUT_split_3x5_3(
  //,--------------------------------------------.                    ,---------------------------------------------
      KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,                      XXXXXXX, KC_LCBR, KC_RCBR, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+|
      KC_DQT, KC_DLR, KC_PERC, KC_CIRC, KC_PLUS,                      XXXXXXX, KC_LPRN, KC_RPRN, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+|
      KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_PIPE,                      XXXXXXX, KC_LBRC, KC_RBRC, XXXXXXX, QK_BOOT,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+|
                                XXXXXXX,KC_RPRN,  KC_UNDS,     KC_SPC, _______,XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

// mouse
    [4] = LAYOUT_split_3x5_3(
  //,--------------------------------------------.                    ,---------------------------------------------
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+|
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      MS_LEFT, MS_DOWN, MS_UP, MS_RGHT, XXXXXXX,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+|
                                 XXXXXXX, KC_RPRN,  KC_ENT,     MS_BTN1, MS_BTN2,XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

// function
    [5] = LAYOUT_split_3x5_3(
  //,--------------------------------------------.                    ,-----------------------------------------------.
      KC_F12, KC_F7, KC_F8, KC_F9, C_PSCR,                               C_PSCR, KC_F7, KC_F8, KC_F9, KC_F12,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--|
      KC_F11, KC_F4, KC_F5, KC_F6, KC_LSFT,                               KC_RSFT, KC_F4, KC_F5, KC_F6, KC_F11,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--|
      KC_F10, KC_F1, KC_F2, KC_F3, KC_PAUS,                               KC_PAUS, KC_F1, KC_F2, KC_F3, KC_F10,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--|
                                    XXXXXXX,KC_RPRN,  KC_ENT,     KC_UNDS, KC_PMNS, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

  // media
    [6] = LAYOUT_split_3x5_3(
  //,--------------------------------------------.                    ,----------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+-|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MPRV, C_VOLD, C_VOLU, KC_MNXT, KC_MSEL,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+-|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+-|
                             XXXXXXX,  KC_RPRN,  KC_ENT,     KC_MUTE, KC_MPLY,XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

// gaming
    [7] = LAYOUT_split_3x5_3(
  //,--------------------------------------------.                    ,---------------------------------------------.
         KC_Q,    KC_1,    KC_2,    KC_3,    KC_4,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+|
      KC_LCTL,    KC_A,    KC_W,    KC_D,    KC_E,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+|
      KC_LSFT,    KC_C,    KC_S,    KC_R,    KC_F,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+|
                              KC_X, KC_SPC,  KC_G,                     KC_SPC, _______, TO(0)
                                      //`--------------------------'  `--------------------------'
  ),

// extra
    [8] = LAYOUT_split_3x5_3(
  //,--------------------------------------------.                    ,---------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, FIRST_PROG_VD, SECOND_PROG_VD, XXXXXXX, C_VOLU,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+|
     XXXXXXX, XXXXXXX, OS_MODE_TOG, XXXXXXX, XXXXXXX,                      XXXXXXX, THIRD_PROG_VD, FOURTH_PROG_VD, XXXXXXX, C_VOLD,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+|
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, LEFT_VD, RIGHT_VD, XXXXXXX, KC_MPLY,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+|
                                   TO(7), XXXXXXX,  KC_ENT,    XXXXXXX, KC_APP, KC_APP 
                                      //`--------------------------'  `--------------------------'
  ),

// coding
    [9] = LAYOUT_split_3x5_3(
    //,--------------------------------------------.                    ,---------------------------------------------.
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     C_GODECL, C_GODEF, C_GOIMP, C_GOREF, XXXXXXX,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+|
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,  C_BACK, XXXXXXX,C_FORWARD, XXXXXXX,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+|
        KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      C_PROMPTS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+|
                                     XXXXXXX,XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX,XXXXXXX
                                        //`--------------------------'  `--------------------------'
    ),

// language WIP
    [10] = LAYOUT_split_3x5_3(
    //,--------------------------------------------.                    ,---------------------------------------------.
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, BR_ACUT, BR_GRV,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+|
        XXXXXXX, XXXXXXX, XXXXXXX, KC_LSFT, XXXXXXX,                      XXXXXXX, XXXXXXX, BR_CCED, BR_TILD, BR_CIRC,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+|
        KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, BR_QUES,
    //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+|
                                     XXXXXXX,XXXXXXX,  XXXXXXX,  XXXXXXX, KC_BSPC, XXXXXXX
                                        //`--------------------------'  `--------------------------'
    )
};

static bool mac_mode = false;

// All one-shot shortcut chords go through this instead of tap_code16().
//
// Why the delay: tap_code16() registers and unregisters the chord in
// back-to-back HID reports, so the host sees a hold time of ~0 ms. macOS
// processes keyboard events asynchronously, and its system-level shortcut
// handlers (Mission Control / Spaces switching, screenshots, etc.) would
// intermittently drop chords that were released before the OS got around to
// looking at the modifier+key state. Holding the chord for
// SHORTCUT_TAP_DELAY ms (10 ms) between register and unregister gives macOS
// time to observe the modifiers and the key down together, making the
// shortcuts fire reliably. Linux/Windows didn't need this, but the delay is
// imperceptible, so it is applied unconditionally rather than branching on
// mac_mode.
static void tap_shortcut(uint16_t keycode) {
    tap_code16_delay(keycode, SHORTCUT_TAP_DELAY);
}

// Mac: rewrite GUI <-> CTL for the navigation and deletion keys, so the
// Linux/Windows muscle memory lands on the right macOS shortcut. After the
// System Settings swap (LALT -> Cmd, LGUI -> Option):
//
//   Ctrl(S) + arrow/bspc/del -> Option+...  (word movement, delete word)  = send LGUI
//   GUI(A)  + arrow/bspc/del -> Control+... (Spaces / Mission Control)    = send LCTL
//
// The swap stays applied for as long as a rewritten key is held, so the host
// keeps auto-repeating (holding Ctrl+Left still walks back word by word).
//
// The hazard this has to avoid: an earlier version swapped real_mods on press
// and swapped back on release with no bookkeeping, which leaked a modifier
// whenever the home row mod was let go while the nav key was still down. QMK's
// mod-tap release calls unregister_mods() for the mod it believes it holds;
// that bit had already been cleared behind its back, so the call did nothing,
// and the release-side swap then re-added a modifier nothing was holding. The
// result was a stuck Cmd or Ctrl that only a replug cleared.
//
// The fix is nav_swap_src_up: any release of the modifier we suppressed is
// noticed while the swap is live, and the restore then re-adds that modifier
// only if it is genuinely still held. Restoring nothing costs the user nothing;
// restoring a phantom is what wedged the board.
//
// Layer-tap and mod-tap keys only take part on their tap resolution — a hold
// there is a layer or a modifier and must be left alone. That also means
// LT(1, KC_BSPC) / LT(1, KC_DEL) holds no longer rewrite the modifiers for the
// whole duration of the number-layer hold, which is how this used to fire on
// the most common path of all.
static uint8_t  nav_swap_removed   = 0;     // real_mods bit we suppressed
static uint8_t  nav_swap_added     = 0;     // real_mods bit we injected
static uint8_t  nav_swap_keys      = 0;     // rewritten nav keys currently held
static bool     nav_swap_src_up    = false; // suppressed mod was released mid-swap
static uint16_t mac_swap_swallowed = KC_NO; // tap we sent in full, release to eat

// Bit position tracking a held nav key, or -1 if the keycode isn't one.
static int8_t nav_swap_bit(uint16_t keycode) {
    switch (keycode) {
        case KC_UP:    return 0;
        case KC_DOWN:  return 1;
        case KC_LEFT:  return 2;
        case KC_RIGHT: return 3;
        case KC_BSPC:  return 4;
        case KC_DEL:   return 5;
        default:       return -1;
    }
}

// The real_mods bits this key event adds or removes, or 0 if it isn't a modifier.
static uint8_t nav_swap_event_mods(uint16_t keycode) {
    if (IS_QK_MOD_TAP(keycode)) {
        uint8_t mods = QK_MOD_TAP_GET_MODS(keycode);
        // Bit 4 marks the right-hand variants, which live in the high nibble.
        return (mods & 0x10) ? ((mods & 0x0F) << 4) : (mods & 0x0F);
    }
    if (IS_MODIFIER_KEYCODE(keycode)) {
        return MOD_BIT(keycode);
    }
    return 0;
}

static void nav_swap_end(void) {
    set_mods((get_mods() & ~nav_swap_added) | (nav_swap_src_up ? 0 : nav_swap_removed));
    send_keyboard_report();
    nav_swap_removed = 0;
    nav_swap_added   = 0;
    nav_swap_keys    = 0;
    nav_swap_src_up  = false;
}

static bool mac_swap_nav(uint16_t keycode, keyrecord_t *record) {
    // Watch for the suppressed modifier being let go. This runs before QMK's
    // own handling of the event, which is what makes the restore safe.
    if (nav_swap_keys && !record->event.pressed
            && (nav_swap_event_mods(keycode) & nav_swap_removed)) {
        nav_swap_src_up = true;
    }

    uint16_t base_kc = keycode;
    bool     tap_only = false;
    if (IS_QK_LAYER_TAP(keycode) || IS_QK_MOD_TAP(keycode)) {
        if (!record->tap.count) { return false; }
        base_kc  = keycode & 0xFF; // tap keycode, for both LT and MT
        tap_only = true;
    }
    int8_t bit = nav_swap_bit(base_kc);
    if (bit < 0) { return false; }

    if (!record->event.pressed) {
        // A tap we already sent start to finish; eat the release.
        if (keycode == mac_swap_swallowed) {
            mac_swap_swallowed = KC_NO;
            return true;
        }
        if (nav_swap_keys & (1 << bit)) {
            nav_swap_keys &= ~(1 << bit);
            if (!nav_swap_keys) { nav_swap_end(); }
        }
        return false; // let QMK unregister the key itself
    }

    if (!mac_mode) { return false; }

    if (nav_swap_keys) {
        // Already swapped — get_mods() now shows the injected modifier, so
        // re-deriving here would swap it straight back.
        if (!tap_only) { nav_swap_keys |= (1 << bit); }
        return false;
    }

    uint8_t mods    = get_mods();
    bool    has_gui = mods & MOD_BIT(KC_LGUI);
    bool    has_ctl = mods & MOD_BIT(KC_LCTL);
    if (has_gui == has_ctl) { return false; }

    uint8_t removed = has_gui ? MOD_BIT(KC_LGUI) : MOD_BIT(KC_LCTL);
    uint8_t added   = has_gui ? MOD_BIT(KC_LCTL) : MOD_BIT(KC_LGUI);
    set_mods((mods & ~removed) | added);
    send_keyboard_report();

    if (tap_only) {
        // An LT/MT hold is a layer or a modifier, so the tap is the only shot
        // at this key — send it complete and put the modifiers back now.
        tap_code_delay((uint8_t)base_kc, SHORTCUT_TAP_DELAY);
        set_mods(mods);
        send_keyboard_report();
        mac_swap_swallowed = keycode;
        return true;
    }

    nav_swap_removed = removed;
    nav_swap_added   = added;
    nav_swap_keys    = (1 << bit);
    nav_swap_src_up  = false;
    return false; // let QMK register the key, and hold it for auto-repeat
}

void keyboard_post_init_user(void) {
    os_mode_led_init();
}

void housekeeping_task_user(void) {
    os_mode_led_task();
}

void layer_lock_set_user(layer_state_t locked_layers) {
    os_mode_led_set_layer_lock(locked_layers != 0);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_layer_lock(keycode, record, LLOCK)) { return false; }

    // Mac: swap GUI(A) ↔ CTL(S) on arrows and delete/backspace
    if (mac_swap_nav(keycode, record)) { return false; }

    bool custom_keypress = false;
    switch (keycode) {
        case WORD_FWD:
        case WORD_BK:
        case C_VOLU:
        case C_VOLD:
            custom_keypress = true;
            break;
    }

    if (!record->event.pressed && !custom_keypress) {
        return true; // Skip all release events
    }
    switch (keycode) {
        //Leaving more complex stuff at the top
        case WORD_BK: {
            static uint16_t word_bk_chord;
            if (record->event.pressed) {
                word_bk_chord = mac_mode ? LGUI(KC_LEFT) : LCTL(KC_LEFT);
                register_code16(word_bk_chord);
            } else {
                unregister_code16(word_bk_chord);
            }
            break;
        }
        case WORD_FWD: {
            static uint16_t word_fwd_chord;
            if (record->event.pressed) {
                word_fwd_chord = mac_mode ? LGUI(KC_RGHT) : LCTL(KC_RGHT);
                register_code16(word_fwd_chord);
            } else {
                unregister_code16(word_fwd_chord);
            }
            break;
        }
        // Mac: Option+Shift+Volume changes volume in quarter-segment steps
        // instead of full segments. After the System Settings swap, macOS sees
        // LGUI as Option, so we send LGUI+LSFT around the consumer volume key.
        // Register/unregister (not tap) so holding the key keeps repeating —
        // with 4x smaller steps you need the repeat even more.
        case C_VOLU: {
            static uint16_t volu_chord;
            if (record->event.pressed) {
                volu_chord = mac_mode ? LSFT(LGUI(KC_VOLU)) : KC_VOLU;
                register_code16(volu_chord);
            } else {
                unregister_code16(volu_chord);
            }
            break;
        }
        case C_VOLD: {
            static uint16_t vold_chord;
            if (record->event.pressed) {
                vold_chord = mac_mode ? LSFT(LGUI(KC_VOLD)) : KC_VOLD;
                register_code16(vold_chord);
            } else {
                unregister_code16(vold_chord);
            }
            break;
        }
        case LEFT_VD:
            tap_shortcut(mac_mode ? LCTL(LALT(KC_LEFT)) : LCTL(LGUI(KC_LEFT)));
            break;
        case RIGHT_VD:
            tap_shortcut(mac_mode ? LCTL(LALT(KC_RGHT)) : LCTL(LGUI(KC_RGHT)));
            break;
        case FIRST_PROG_VD:
            if (mac_mode) { tap_shortcut(LCTL(LGUI(KC_1))); wait_ms(30); tap_shortcut(LCTL(LGUI(KC_1))); }
            else { tap_shortcut(LGUI(LALT(KC_1))); }
            break;
        case SECOND_PROG_VD:
            if (mac_mode) { tap_shortcut(LCTL(LGUI(KC_2))); wait_ms(30); tap_shortcut(LCTL(LGUI(KC_2))); }
            else { tap_shortcut(LGUI(LALT(KC_2))); }
            break;
        case THIRD_PROG_VD:
            if (mac_mode) { tap_shortcut(LCTL(LGUI(KC_3))); wait_ms(30); tap_shortcut(LCTL(LGUI(KC_3))); }
            else { tap_shortcut(LGUI(LALT(KC_3))); }
            break;
        case FOURTH_PROG_VD:
            if (mac_mode) { tap_shortcut(LCTL(LGUI(KC_4))); wait_ms(30); tap_shortcut(LCTL(LGUI(KC_4))); }
            else { tap_shortcut(LGUI(LALT(KC_4))); }
            break;
        case C_BACK:
            tap_shortcut(mac_mode ? LALT(KC_MINS) : LCTL(KC_MINS));
            break;
        case C_FORWARD:
            tap_shortcut(mac_mode ? LALT(KC_EQL) : LCTL(KC_EQL));
            break;
        case C_GODEF:
            tap_shortcut(KC_F12);
            break; 
        case C_GOIMP:
            tap_shortcut(mac_mode ? LALT(KC_F12) : LCTL(KC_F12));
            break;
        case C_GOREF:
            tap_shortcut(LSFT(KC_F12));
            break;
        case C_GODECL:
            tap_shortcut(mac_mode ? LCTL(LSFT(LGUI(KC_F12))) : LCTL(LSFT(LALT(KC_F12))));
            break;
        case SH_F7:
            tap_shortcut(LSFT(KC_F7));
            break;
        // Mac only: double-tap within TAPPING_TERM types the prompts path; a
        // single tap only arms it. Firing disarms, so a triple tap doesn't
        // type it twice.
        case C_PROMPTS: {
            static uint32_t prompts_timer;
            static bool     prompts_armed = false;
            if (!mac_mode) { break; }
            if (prompts_armed && timer_elapsed32(prompts_timer) < TAPPING_TERM) {
                SEND_STRING("@~/dev/prompts/");
                prompts_armed = false;
            } else {
                prompts_timer = timer_read32();
                prompts_armed = true;
            }
            break;
        }
        case C_HOME: {
            if (mac_mode) {
                uint8_t mods = get_mods();
                bool shift = mods & MOD_MASK_SHIFT;
                bool ctrl = mods & MOD_MASK_CTRL;
                clear_mods();
                if (ctrl) {
                    tap_shortcut(shift ? LSFT(LALT(KC_UP)) : LALT(KC_UP));
                } else {
                    tap_shortcut(shift ? LSFT(LALT(KC_LEFT)) : LALT(KC_LEFT));
                }
                set_mods(mods);
            } else {
                tap_code(KC_HOME);
            }
            break;
        }
        case C_END: {
            if (mac_mode) {
                uint8_t mods = get_mods();
                bool shift = mods & MOD_MASK_SHIFT;
                bool ctrl = mods & MOD_MASK_CTRL;
                clear_mods();
                if (ctrl) {
                    tap_shortcut(shift ? LSFT(LALT(KC_DOWN)) : LALT(KC_DOWN));
                } else {
                    tap_shortcut(shift ? LSFT(LALT(KC_RIGHT)) : LALT(KC_RIGHT));
                }
                set_mods(mods);
            } else {
                tap_code(KC_END);
            }
            break;
        }
        case C_PSCR:
            tap_shortcut(mac_mode ? LALT(LCTL(LSFT(KC_4))) : KC_PSCR);
            break;
        case OS_MODE_TOG:
            mac_mode = !mac_mode;
            os_mode_led_toggle(mac_mode);
            break;

    }
    return true;
}
