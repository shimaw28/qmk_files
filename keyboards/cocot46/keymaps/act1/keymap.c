/* Copyright 2021 aki27
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include <stdio.h>

#include "paw3204.h"
#include "pointing_device.h"

#include "keymap_jp.h"
#include "quantum.h"
#include "action_layer.h"

bool isScrollMode;

// Defines names for use in layer keycodes and the keymap
enum layer_number {
    _DVORAK = 0,
    _DVORAK_WIN,
    _DVORAK_SUM,
    _DVORAK_JP,
    _DVORAK_JP_WIN,
    _DVORAK_JP_SUM,
    _SUMITOMO_SHIFT,
    _QWERTY,
    _LOWER,
    _SUMITOMO_LOWER,
    _RAISE,
    _SUMITOMO_RAISE,
    _ADJUST,
    _vimMOVE,
    _emacsMOVE,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  DJ_A, DJ_B, DJ_C, DJ_D, DJ_E, DJ_F, DJ_G, DJ_H, DJ_I, DJ_J, DJ_K, DJ_L, DJ_M, DJ_N, DJ_O, DJ_P, DJ_Q, DJ_R, DJ_S, DJ_T, DJ_U, DJ_V, DJ_W, DJ_X, DJ_Y, DJ_Z,
  DJ_QUOT, DJ_COMM, DJ_DOT, DJ_SCLN,
  DJ_XTU, DJ_CLEAR, DJ_BSPC, DJ_ENT, DJ_SAND, ENT_TO_DJ,

  SW_MW, SW_EJ, MW_MOD1, MW_MOD2, MW_MOD3, MW_MOD4, MW_MOD5, MW_MOD6, //switch windows/mac
  SW_SCLN_CLN,
  RAUNCHER, INPUT, ENT_MOVE, TAB_MOVE,
  TO_EN, TO_JP,

  MBTN1,
  MBTN2,
  MBTN3,
  SCRL
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

// Tap Dance declarations
enum {
    TD_ALT_GUI,
};

// Tap Dance definitions
// qk_tap_dance_action_t tap_dance_actions[] = {
//     // Tap once for Escape, twice for Caps Lock
//     [TD_ALT_GUI] = ACTION_TAP_DANCE_DOUBLE(KC_LALT, KC_LGUI),
// };

#define LW_MHEN LT(1,KC_MHEN)  // lower
#define RS_HENK LT(2,KC_HENK)  // raise


short int dj_mode = 0;
bool nn_status = false;
bool windows_mode = false;
bool japanese_mode = false;
static bool move_pressed = false;
static short int dj_spc_mode = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_DVORAK] = LAYOUT(
        LSFT_T(KC_ESC),         KC_QUOT, KC_COMM,               KC_DOT,                KC_P,               KC_Y,                                                        KC_F,      KC_G,           KC_C,   KC_R,    KC_L,  KC_BSPC,
        LT(_emacsMOVE, KC_TAB), KC_A,    KC_O,                  KC_E,                  KC_U,               KC_I,                                                        KC_D,      KC_H,           KC_T,   KC_N,    KC_S,  KC_SLSH,
        LM(_QWERTY, MOD_LGUI),  KC_SCLN, KC_Q,                  KC_J,                  KC_K,               KC_X,               KC_MS_BTN1,               KC_MS_BTN2,    KC_B,      KC_M,           KC_W,   KC_V,    KC_Z,  RAUNCHER,
                                         LM(_QWERTY, MOD_LALT), LM(_QWERTY, MOD_LGUI), LT(_LOWER, KC_SPC), LT(_RAISE, KC_TAB), KC_MS_WH_UP,  KC_MS_BTN3, KC_MS_WH_DOWN, ENT_TO_DJ, LSFT_T(KC_SPC), KC_APP, RAUNCHER
    ),

    [_DVORAK_WIN] = LAYOUT(
        LSFT_T(KC_ESC),         KC_QUOT,  KC_COMM,               KC_DOT,  KC_P,               KC_Y,                                                        KC_F,      KC_G,           KC_C,   KC_R,    KC_L,  KC_BSPC,
        LT(_emacsMOVE, KC_TAB), KC_A,     KC_O,                  KC_E,    KC_U,               KC_I,                                                        KC_D,      KC_H,           KC_T,   KC_N,    KC_S,  KC_SLSH,
        LM(_QWERTY, MOD_LCTL),  KC_SCLN,  KC_Q,                  KC_J,    KC_K,               KC_X,               KC_MS_BTN1,               KC_MS_BTN2,    KC_B,      KC_M,           KC_W,   KC_V,    KC_Z,  RAUNCHER,
                                          LM(_QWERTY, MOD_LGUI), KC_LALT, LT(_LOWER, KC_SPC), LT(_RAISE, KC_TAB), KC_MS_WH_UP,  KC_MS_BTN3, KC_MS_WH_DOWN, ENT_TO_DJ, LSFT_T(KC_SPC), KC_APP, RAUNCHER
    ),

    [_DVORAK_SUM] = LAYOUT(
        LSFT_T(KC_ESC),         JP_QUOT, KC_COMM,                KC_DOT,  KC_P,                        KC_Y,                                                                 KC_F,      KC_G,                        KC_C,   KC_R,    KC_L,  KC_BSPC,
        LT(_emacsMOVE, KC_TAB), KC_A,     KC_O,                  KC_E,    KC_U,                        KC_I,                                                                 KC_D,      KC_H,                        KC_T,   KC_N,    KC_S,  KC_SLSH,
        LM(_QWERTY, MOD_LCTL),  JP_SCLN,  KC_Q,                  KC_J,    KC_K,                        KC_X,                        KC_MS_BTN1,               KC_MS_BTN2,    KC_B,      KC_M,                        KC_W,   KC_V,    KC_Z,  RAUNCHER,
                                          LM(_QWERTY, MOD_LGUI), KC_LALT, LT(_SUMITOMO_LOWER, KC_SPC), LT(_SUMITOMO_RAISE, KC_TAB), KC_MS_WH_UP,  KC_MS_BTN3, KC_MS_WH_DOWN, ENT_TO_DJ, LT(_SUMITOMO_SHIFT, KC_SPC), KC_APP, RAUNCHER
    ),

    [_DVORAK_JP] = LAYOUT( \
        LSFT_T(KC_ESC),         DJ_QUOT, DJ_COMM,               DJ_DOT,                DJ_P,               DJ_Y,                                                       DJ_F,     DJ_G,    DJ_K,   DJ_R,     DJ_L, DJ_BSPC, \
        TAB_MOVE,               DJ_A,    DJ_O,                  DJ_E,                  DJ_U,               DJ_I,                                                       DJ_D,     DJ_H,    DJ_T,   DJ_N,     DJ_S, KC_SLSH, \
        LM(_QWERTY, MOD_LGUI),  DJ_SCLN, DJ_Q,                  DJ_J,                  DJ_C,               DJ_X,               KC_MS_BTN1,              KC_MS_BTN2,    DJ_B,     DJ_M,    DJ_W,   DJ_XTU,   DJ_Z, RAUNCHER, \
                                         LM(_QWERTY, MOD_LALT), LM(_QWERTY, MOD_LGUI), LT(_LOWER, KC_SPC), LT(_RAISE, KC_TAB), KC_MS_WH_UP, KC_MS_BTN3, KC_MS_WH_DOWN, ENT_MOVE, DJ_SAND, KC_APP, RAUNCHER\
    ),

    [_DVORAK_JP_WIN] = LAYOUT( \
        LSFT_T(KC_ESC),        DJ_QUOT, DJ_COMM,               DJ_DOT,  DJ_P,    DJ_Y,                                            DJ_F,    DJ_G,    DJ_K,    DJ_R,     DJ_L, DJ_BSPC, \
        TAB_MOVE,              DJ_A,    DJ_O,                  DJ_E,    DJ_U,    DJ_I,                                            DJ_D,    DJ_H,    DJ_T,    DJ_N,     DJ_S, KC_SLSH, \
        LM(_QWERTY, MOD_LCTL), DJ_SCLN, DJ_Q,                  DJ_J,    DJ_C,    DJ_X,    KC_MS_BTN1,              KC_MS_BTN2,    DJ_B,    DJ_M,    DJ_W,    DJ_XTU,   DJ_Z, RAUNCHER , \
                                        LM(_QWERTY, MOD_LGUI), KC_LALT, _______, _______, KC_MS_WH_UP, KC_MS_BTN3, KC_MS_WH_DOWN, _______, _______, _______, RAUNCHER\
    ),

    [_DVORAK_JP_SUM] = LAYOUT( \
        LSFT_T(KC_ESC),        DJ_QUOT, DJ_COMM,               DJ_DOT,  DJ_P,                        DJ_Y,                                                                DJ_F,     DJ_G,    DJ_K,    DJ_R,     DJ_L,         DJ_BSPC, \
        TAB_MOVE,              DJ_A,    DJ_O,                  DJ_E,    DJ_U,                        DJ_I,                                                                DJ_D,     DJ_H,    DJ_T,    DJ_N,     DJ_S,         KC_SLSH, \
        LM(_QWERTY, MOD_LCTL), DJ_SCLN, DJ_Q,                  DJ_J,    DJ_C,                        DJ_X,                        KC_MS_BTN1,              KC_MS_BTN2,    DJ_B,     DJ_M,    DJ_W,    DJ_XTU,   DJ_Z,         RAUNCHER , \
                                        LM(_QWERTY, MOD_LGUI), KC_LALT, LT(_SUMITOMO_LOWER, KC_SPC), LT(_SUMITOMO_RAISE, KC_TAB), KC_MS_WH_UP, KC_MS_BTN3, KC_MS_WH_DOWN, ENT_MOVE, DJ_SAND, _______, RAUNCHER\
    ),

    [_SUMITOMO_SHIFT] = LAYOUT( \
        LSFT_T(KC_TAB), JP_DOT,     LSFT(KC_COMM), LSFT(KC_DOT), LSFT(KC_P), LSFT(KC_Y),                                         LSFT(KC_F),   LSFT(KC_G),   LSFT(KC_C), LSFT(KC_R), LSFT(KC_L), LSFT(KC_BSPC), \
        KC_LCTL,        LSFT(KC_A), LSFT(KC_O),    LSFT(KC_E),   LSFT(KC_U), LSFT(KC_I),                                         LSFT(KC_D),   LSFT(KC_H),   LSFT(KC_T), LSFT(KC_N), LSFT(KC_S), LSFT(KC_SLSH), \
        LSFT(KC_LSFT),  JP_COLN,    LSFT(KC_Q),    LSFT(KC_J),   LSFT(KC_K), LSFT(KC_X), KC_MS_BTN1,              KC_MS_BTN2,    LSFT(KC_B),   LSFT(KC_M),   LSFT(KC_W), LSFT(KC_V), LSFT(KC_Z), RAUNCHER, \
                                    KC_NO,         KC_NO,        KC_NO,      KC_NO,      KC_MS_WH_UP, KC_MS_BTN3, KC_MS_WH_DOWN, LSFT(KC_ENT), LSFT(KC_SPC), KC_NO,      KC_NO \
    ),

    [_QWERTY] = LAYOUT( \
        LSFT_T(KC_ESC), KC_Q,  KC_W,    KC_E,    KC_R,       KC_T,                                                        KC_Y,                 KC_U,           KC_I,    KC_O,         KC_P,         KC_BSPC,\
        CTL_T(KC_TAB),  KC_A,  KC_S,    KC_D,    KC_F,       KC_G,                                                        KC_H,                 KC_J,           KC_K,    KC_L,         KC_SCLN,      KC_QUOT,\
        KC_LGUI,        KC_Z,  KC_X,    KC_C,    KC_V,       KC_B,                KC_MS_BTN1,              KC_MS_BTN2,    KC_N,                 KC_M,           KC_COMM, KC_DOT,       KC_SLSH,      KC_RSFT,\
                               KC_LCTL, KC_LALT, MO(_LOWER), LT(_RAISE, KC_TAB),  KC_MS_WH_UP, KC_MS_BTN3, KC_MS_WH_DOWN, LT(_vimMOVE, KC_ENT), LSFT_T(KC_SPC), KC_APP,  LGUI(KC_SPC)\
    ),

    [_LOWER] = LAYOUT( \
        LSFT_T(KC_ESC), KC_EXLM, KC_AT,          KC_HASH, KC_DLR,     KC_PERC,                                               KC_CIRC, KC_AMPR,    KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,\
        KC_TAB,         KC_1,    KC_2,           KC_3,    KC_4,       KC_5,                                                  KC_6,    KC_7,       KC_8,    KC_9,    KC_0,    KC_NO,\
        KC_LSFT,        TO_EN,   TO_JP,          KC_NO,   KC_NO,      KC_NO,      KC_MS_BTN1,                KC_MS_BTN2,     KC_NO,   KC_NO,      KC_COMM, KC_DOT,  KC_SLSH, KC_NO,\
                                LCTL(KC_RIGHT), KC_LGUI, MO(_LOWER), MO(_ADJUST), KC_MS_WH_LEFT, KC_MS_BTN3, KC_MS_WH_RIGHT, KC_ENT,  MO(_RAISE), KC_RALT, TO_EN \
  ),

    [_SUMITOMO_LOWER] = LAYOUT( \
        LSFT_T(KC_ESC), KC_EXLM, JP_AT,                KC_HASH, KC_DLR,     KC_PERC,                                                JP_CIRC, JP_AMPR,    JP_ASTR, JP_LPRN, JP_RPRN, KC_BSPC,\
        KC_TAB,         KC_1,    KC_2,                 KC_3,    KC_4,       KC_5,                                                   KC_6,    KC_7,       KC_8,    KC_9,    KC_0,    KC_NO,\
        KC_LSFT,        TO_EN,   TO_JP,                KC_NO,   KC_NO,      KC_NO,       KC_MS_BTN1,                KC_MS_BTN2,     KC_NO,   KC_NO,      KC_COMM, KC_DOT,  KC_SLSH, KC_NO,\
                                 LCTL(LGUI(KC_RIGHT)), KC_LGUI, MO(_LOWER), MO(_ADJUST), KC_MS_WH_LEFT, KC_MS_BTN3, KC_MS_WH_RIGHT, KC_ENT,  MO(_RAISE), KC_RALT, KC_G    \
    ),
    [_RAISE] = LAYOUT( \
        KC_GRV,       KC_F1,  KC_F2,         KC_F3,   KC_F4,        KC_F5,                                           KC_PIPE, KC_UNDS,    KC_PLUS, KC_LCBR, KC_RCBR, KC_DEL,\
        LGUI(KC_TAB), KC_F6,  KC_F7,         KC_F8,   KC_F9,        KC_F10,                                          KC_TILD, KC_MINS,    KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,\
        KC_TILD,      KC_F11, KC_F12,        KC_F13,  KC_F14,       KC_F15,  KC_MS_BTN1,              KC_MS_BTN2,    KC_UNDS, KC_PLUS,    KC_LBRC, KC_RBRC, KC_BSLS, KC_TILD,\
                              LCTL(KC_DOWN), KC_LGUI, MO(_ADJUST),  _______, KC_MS_WH_UP, KC_MS_BTN3, KC_MS_WH_DOWN, KC_ENT,  MO(_RAISE), KC_RALT, KC_K\
    ),

  [_SUMITOMO_RAISE] = LAYOUT( \
    JP_GRV,       KC_F1,   KC_F2,   KC_F3,   KC_F4,       KC_F5,                                           JP_PIPE, JP_UNDS,    JP_PLUS, JP_LCBR, JP_RCBR, KC_DEL,\
    LALT(KC_TAB), KC_F6,   KC_F7,   KC_F8,   KC_F9,       KC_F10,                                          JP_TILD, JP_MINS,    JP_EQL,  JP_LBRC, JP_RBRC, JP_BSLS,\
    JP_TILD,      KC_F11,  KC_F12,  KC_F13,  KC_F14,      KC_F15,  KC_MS_BTN1,              KC_MS_BTN2,    JP_UNDS, JP_PLUS,    JP_LBRC, JP_RBRC, JP_BSLS, JP_TILD,\
                           KC_LGUI, KC_LGUI, MO(_ADJUST), _______, KC_MS_WH_UP, KC_MS_BTN3, KC_MS_WH_DOWN, KC_ENT,  MO(_RAISE), KC_RALT, KC_K\
  ),

  [_ADJUST] = LAYOUT( \
    RESET,   TO(_DVORAK), TO(_DVORAK_WIN), TO(_DVORAK_SUM), KC_NO,      KC_NO,                                           KC_NO,  KC_NO,      KC_NO,   KC_NO, KC_NO, KC_NO,\
    RGB_HUI, TO(_QWERTY), KC_NO,           KC_NO,           KC_NO,      KC_NO,                                           KC_NO,  KC_NO,      KC_NO,   KC_NO, KC_NO, KC_NO,\
    SW_EJ,   KC_NO,       KC_NO,           KC_NO,           KC_NO,      KC_NO,   KC_MS_BTN1,              KC_MS_BTN2,    KC_NO,  KC_NO,      KC_NO,   KC_NO, KC_NO, KC_NO,\
                          KC_NO,           KC_LGUI,         MO(_LOWER), _______, KC_MS_WH_UP, KC_MS_BTN3, KC_MS_WH_DOWN, KC_ENT, MO(_RAISE), KC_RALT, KC_NO\
  ),

  [_vimMOVE] = LAYOUT( \
     LSFT_T(KC_ESC), KC_NO, KC_NO,   KC_NO,   KC_NO, KC_NO,                                         KC_HOME, KC_PGDOWN, KC_PGUP, KC_END,   KC_NO, KC_NO, \
     LSFT_T(KC_TAB), KC_NO, KC_NO,   KC_NO,   KC_NO, KC_NO,                                         KC_LEFT, KC_DOWN,   KC_UP,   KC_RIGHT, KC_NO, KC_NO, \
     KC_LCTL,        KC_NO, KC_NO,   KC_NO,   KC_NO, KC_NO, KC_MS_BTN1,              KC_MS_BTN2,    KC_BSPC, KC_DEL,    KC_NO,   KC_NO,    KC_NO, KC_NO, \
                            KC_LALT, KC_LALT, KC_NO, KC_NO, KC_MS_WH_UP, KC_MS_BTN3, KC_MS_WH_DOWN, KC_NO,   KC_NO,     KC_NO,   KC_NO \
  ),

   [_emacsMOVE] = LAYOUT( \
     LSFT_T(KC_ESC), KC_NO,   KC_NO, KC_END, KC_NO,    KC_NO,                                           KC_NO,   KC_NO, KC_NO, KC_NO, KC_UP, KC_NO, \
     KC_NO,          KC_HOME, KC_NO, KC_DEL, KC_RIGHT, KC_NO,                                           KC_BSPC, KC_NO, KC_NO, KC_NO, KC_F10, KC_NO, \
     KC_LSHIFT,      KC_NO,   KC_NO, KC_NO,  KC_NO,    KC_LEFT, KC_MS_BTN1,              KC_MS_BTN2,    KC_DOWN, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, \
                              KC_NO, KC_NO,  KC_NO,    KC_NO,   KC_MS_WH_UP, KC_MS_BTN3, KC_MS_WH_DOWN, KC_NO,   KC_NO, KC_NO, KC_NO \
  )

};


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']' , '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}


keyevent_t encoder1_ccw = {
    .key = (keypos_t){.row = 3, .col = 6},
    .pressed = false
};

keyevent_t encoder1_cw = {
    .key = (keypos_t){.row = 2, .col = 6},
    .pressed = false
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            encoder1_cw.pressed = true;
            encoder1_cw.time = (timer_read() | 1);
            action_exec(encoder1_cw);
        } else {
            encoder1_ccw.pressed = true;
            encoder1_ccw.time = (timer_read() | 1);
            action_exec(encoder1_ccw);
        }
    }

    return true;
}

void press_mod (uint16_t win_keycode, uint16_t mac_keycode, keyrecord_t *record) {
  bool already_qwerty = false;
  if (windows_mode) {
        if (record->event.pressed) {
            if(!(layer_state_is(_QWERTY))) {layer_on(_QWERTY); already_qwerty = true;};
            register_code(win_keycode);
        } else {
            unregister_code(win_keycode);
            if (already_qwerty) {layer_off(_QWERTY);};
        }
  } else {
        if (record->event.pressed) {
            if(!(layer_state_is(_QWERTY))) {layer_on(_QWERTY); already_qwerty = true;};
            register_code(mac_keycode);
        } else {
            unregister_code(mac_keycode);
            if (already_qwerty) {layer_off(_QWERTY);};
        }
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  report_mouse_t currentReport = {};

  switch (keycode) {
    case MBTN1:
      currentReport = pointing_device_get_report();
      if (record->event.pressed) {
        currentReport.buttons |= MOUSE_BTN1;
      }
      else {
        currentReport.buttons &= ~MOUSE_BTN1;
      }
      pointing_device_set_report(currentReport);
      return false;
    case MBTN2:
      currentReport = pointing_device_get_report();
      if (record->event.pressed) {
        currentReport.buttons |= MOUSE_BTN2;
      }
      else {
        currentReport.buttons &= ~MOUSE_BTN2;
      }
      pointing_device_set_report(currentReport);
      return false;
    case MBTN3:
      currentReport = pointing_device_get_report();
      if (record->event.pressed) {
        currentReport.buttons |= MOUSE_BTN3;
      }
      else {
        currentReport.buttons &= ~MOUSE_BTN3;
      }
      pointing_device_set_report(currentReport);
      return false;
    case SCRL:
      if (record->event.pressed) {
        isScrollMode = true;
        dprint("scroll ON\n");
      }
      else {
        isScrollMode = false;
        dprint("scroll OFF\n");
      }
//       return false;
//   }
//   return true;
// }

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//   switch (keycode) {
    case DJ_QUOT:
     if (dj_mode == 0){
        if (record->event.pressed) {SEND_STRING("'"); dj_mode = 0; nn_status = 0;}
     } else {
        if (record->event.pressed) {SEND_STRING("ai"); dj_mode = 0; nn_status = 0;}
      }
      return false;

    case DJ_COMM:
     if (dj_mode == 0){
        if (record->event.pressed) {SEND_STRING(","); dj_mode = 0; nn_status = 0;}
     } else {
        if (record->event.pressed) {SEND_STRING("ou"); dj_mode = 0; nn_status = 0;}
      }
      return false;

    case DJ_DOT:
     if (dj_mode == 0){
        if (record->event.pressed) {SEND_STRING("."); dj_mode = 0; nn_status = 0;}
     } else {
        if (record->event.pressed) {SEND_STRING("ei"); dj_mode = 0; nn_status = 0;}
      }
      return false;
    case DJ_P:
        if (record->event.pressed) {SEND_STRING("p"); dj_mode = 1; nn_status = 0;}
        return false;

    case DJ_Y:
        if (record->event.pressed) {SEND_STRING("y"); dj_mode = 1; nn_status = 0;}
        return false;

    case DJ_A:
        if (record->event.pressed) {SEND_STRING("a"); dj_mode = 0; nn_status = 0;}
        return false;

    case DJ_O:
        if (record->event.pressed) {SEND_STRING("o"); dj_mode = 0; nn_status = 0;}
        return false;

    case DJ_E:
        if (record->event.pressed) {SEND_STRING("e"); dj_mode = 0; nn_status = 0;}
        return false;

    case DJ_U:
        if (record->event.pressed) {SEND_STRING("u"); dj_mode = 0; nn_status = 0;}
        return false;

    case DJ_I:
        if (record->event.pressed) {SEND_STRING("i"); dj_mode = 0; nn_status = 0;}
        return false;

    case DJ_SCLN:
      if (dj_mode == 0){
        if (record->event.pressed) {SEND_STRING(";"); dj_mode = 0; nn_status = 0;}
      } else {
        if (record->event.pressed) {SEND_STRING("ann"); dj_mode = 0; nn_status = 0;}
      }
      return false;

    case DJ_Q:
     if (dj_mode == 0){
        if (record->event.pressed) {SEND_STRING("q"); dj_mode = 0; nn_status = 0;}
     } else {
        if (record->event.pressed) {SEND_STRING("onn"); dj_mode = 0; nn_status = 0;}
      }
      return false;

    case DJ_J:
      if (dj_mode == 0){
        if (record->event.pressed) {SEND_STRING("j"); dj_mode = 0; nn_status = 0;}
      } else {
        if (record->event.pressed) {SEND_STRING("enn"); dj_mode = 0; nn_status = 0;}
      }
      return false;

    case DJ_C:
      if (dj_mode == 0){
        if (record->event.pressed) {SEND_STRING("c"); dj_mode = 0; nn_status = 0;}
      } else {
        if (record->event.pressed) {SEND_STRING("unn"); dj_mode = 0; nn_status = 0;}
      }
      return false;

    case DJ_X:
      if (dj_mode == 0){
        if (record->event.pressed) {SEND_STRING("x"); dj_mode = 0; nn_status = 0;}
      } else {
        if (record->event.pressed) {SEND_STRING("inn"); dj_mode = 0; nn_status = 0;}
      }
      return false;

    // -----------------------------

    case DJ_F:
        if (record->event.pressed) {SEND_STRING("f"); dj_mode = 1; nn_status = 0;}
        return false;

    case DJ_G:
        if (record->event.pressed) {SEND_STRING("g"); dj_mode = 1; nn_status = 0;}
        return false;

    case DJ_K:
        if (record->event.pressed) {SEND_STRING("k"); dj_mode = 1; nn_status = 0;}
        return false;

    case DJ_R:
        if (record->event.pressed) {SEND_STRING("r"); dj_mode = 2; nn_status = 0;}
        return false;

    case DJ_L:
        if (record->event.pressed) {SEND_STRING("l"); dj_mode = 2; nn_status = 0;}
        return false;

    case DJ_D:
        if (record->event.pressed) {SEND_STRING("d"); dj_mode = 1; nn_status = 0;}
        return false;

    case DJ_H:
        if (record->event.pressed) {
            if (dj_mode == 2) {
                SEND_STRING("y"); nn_status = 0;
            } else {
                SEND_STRING("h"); dj_mode = 1; nn_status = 0;
            }
        }
        return false;

    case DJ_T:
        if (record->event.pressed) {SEND_STRING("t"); dj_mode = 1; nn_status = 0;}
        return false;

    case DJ_N:
        if (record->event.pressed)  {
            if (nn_status == 0) {
                if (dj_mode == 1) {
                    SEND_STRING("y");
                } else {
                    SEND_STRING("n"); dj_mode = 2; nn_status = 1;
                }
            } else {
                SEND_STRING("n"); dj_mode = 0; nn_status = 0;
            }
        }
        return false;

    case DJ_S:
        if (record->event.pressed) {SEND_STRING("s"); dj_mode = 2; nn_status = 0;}
        return false;

    case DJ_B:
        if (record->event.pressed) {SEND_STRING("b"); dj_mode = 1; nn_status = 0;}
        return false;

    case DJ_M:
        if (record->event.pressed) {SEND_STRING("m"); dj_mode = 1; nn_status = 0;}
        return false;

    case DJ_W:
        if (record->event.pressed) {SEND_STRING("w"); dj_mode = 1; nn_status = 0;}
        return false;

    case DJ_V:
        if (record->event.pressed) {SEND_STRING("v"); dj_mode = 2; nn_status = 0;}
        return false;

    case DJ_Z:
        if (record->event.pressed) {SEND_STRING("z"); dj_mode = 2; nn_status = 0;}
        return false;
// -------------------------------------
    case DJ_XTU:
        if (record->event.pressed) {SEND_STRING("xtu"); dj_mode = 0; nn_status = 0;}
        return false;

    case DJ_CLEAR:
        if (record->event.pressed) {dj_mode = 0; nn_status = 0;}
        return false;

    case DJ_BSPC:
        if (record->event.pressed) {
            register_code(KC_BSPC);
        } else {
            unregister_code(KC_BSPC);
        }
        dj_mode = 0;
        nn_status = 0;
        return false;


    case DJ_ENT:
        if (record->event.pressed) {register_code(KC_ENT); unregister_code(KC_ENT); dj_mode = 0; }
        nn_status = 0;
        return false;

    case SW_MW:
      if (record->event.pressed) {
          if (windows_mode) {windows_mode = false;} else {windows_mode = true;} }

    case SW_EJ:
      if (record->event.pressed) {
          if (japanese_mode) {japanese_mode = false;} else {japanese_mode = true;}
      }
      return false;

    case SW_SCLN_CLN:
        if ((keyboard_report->mods & MOD_BIT(KC_LSFT)) || (keyboard_report->mods & MOD_BIT(KC_RSFT))) {
            if (record->event.pressed){
                register_code(KC_COMMA);
            } else {
                unregister_code(KC_COMMA);
            }
        } else {
            register_code(KC_LSFT);
            register_code(KC_9);
            unregister_code(KC_9);
            unregister_code(KC_LSFT);
        }


    case MW_MOD1:
      press_mod(KC_LCTL, KC_LGUI, record);
      return false;
    case MW_MOD2:
      press_mod(KC_LGUI, KC_LALT, record);
      return false;
    case MW_MOD3:
      press_mod(KC_LALT, KC_LGUI, record);
      return false;
    case MW_MOD4:
      press_mod(KC_APP, KC_LCTL, record);
      return false;
    case MW_MOD5:
      press_mod(KC_LCTL, KC_LGUI, record);
      return false;
    case MW_MOD6:
      press_mod(KC_LCTL, KC_LGUI, record);
      return false;

    case TO_EN:
      if (record->event.pressed) {
        if (layer_state_is(_DVORAK) || layer_state_is(_DVORAK_JP)){
          layer_move(_DVORAK);
        } else if (layer_state_is(_DVORAK_WIN) || layer_state_is(_DVORAK_JP_WIN)) {
          layer_move(_DVORAK_WIN);
        } else if (layer_state_is(_DVORAK_SUM) || layer_state_is(_DVORAK_JP_SUM)) {
          layer_move(_DVORAK_SUM);
        }
        register_code(KC_LANG2);
        unregister_code(KC_LANG2);

      return false;
      }

    case TO_JP:
      if (record->event.pressed) {
        if (layer_state_is(_DVORAK) || layer_state_is(_DVORAK_JP)){
          layer_move(_DVORAK_JP);
        } else if (layer_state_is(_DVORAK_WIN) || layer_state_is(_DVORAK_JP_WIN)) {
          layer_move(_DVORAK_JP_WIN);
        } else if (layer_state_is(_DVORAK_SUM) || layer_state_is(_DVORAK_JP_SUM)) {
          layer_move(_DVORAK_JP_SUM);
        }
        register_code(KC_LANG1);
        unregister_code(KC_LANG1);

      return false;
      }

    case RAUNCHER:
      if (record->event.pressed) {
        if (layer_state_is(_DVORAK) || layer_state_is(_DVORAK_JP)){
          layer_move(_DVORAK);
          register_code(KC_LGUI);
          register_code(KC_SPC);
          unregister_code(KC_SPC);
          unregister_code(KC_LGUI);
        } else if (layer_state_is(_DVORAK_WIN) || layer_state_is(_DVORAK_JP_WIN)) {
          layer_move(_DVORAK_WIN);
          register_code(KC_LGUI);
          register_code(KC_R);
          unregister_code(KC_R);
          unregister_code(KC_LGUI);
        } else if (layer_state_is(_DVORAK_SUM) || layer_state_is(_DVORAK_JP_SUM)) {
          layer_move(_DVORAK_SUM);
          register_code(KC_LGUI);
          register_code(KC_R);
          unregister_code(KC_R);
          unregister_code(KC_LGUI);
        }
        register_code(KC_LANG2);
        unregister_code(KC_LANG2);

        return false;
      }

    case ENT_MOVE:
    //   参考: https://okapies.hateblo.jp/entry/2019/02/02/133953
      if (record->event.pressed) {
        move_pressed = true;
        dj_mode = 0; nn_status = 0;
        layer_on(_vimMOVE);
      } else {
        layer_off(_vimMOVE);
        if (move_pressed) {
            register_code(KC_ENT);
            unregister_code(KC_ENT);
        }
        move_pressed = false;
      }
      return false;
      break;

    case TAB_MOVE:
    //   参考: https://okapies.hateblo.jp/entry/2019/02/02/133953
      if (record->event.pressed) {
        move_pressed = true;
        dj_mode = 0; nn_status = 0;
        layer_on(_emacsMOVE);
      } else {
        layer_off(_emacsMOVE);
        if (move_pressed) {
            register_code(KC_TAB);
            unregister_code(KC_TAB);
        }
        move_pressed = false;
      }
      return false;
      break;

    case DJ_SAND:
        if (record->event.pressed) {
            move_pressed = true;
            dj_mode = 0; nn_status = 0;
            register_code(KC_LSFT);
            if (layer_state_is(_DVORAK_JP)){
                dj_spc_mode = true;
                layer_move(_DVORAK);
            } else if (layer_state_is(_DVORAK_JP_WIN)) {
                dj_spc_mode = true;
                layer_move(_DVORAK_WIN);
            } else if (layer_state_is(_DVORAK_JP_SUM)) {
                dj_spc_mode = true;
                layer_move(_DVORAK_SUM);
            }
        } else {
            unregister_code(KC_LSFT);
            if (move_pressed) {
                register_code(KC_SPC);
                unregister_code(KC_SPC);
            }
            move_pressed = false;
        }
        return false;

    case ENT_TO_DJ:
        if (record->event.pressed) {
            move_pressed = true;
            layer_on(_vimMOVE);
        } else {
            layer_off(_vimMOVE);
            if (move_pressed) {
                register_code(KC_ENT);
                unregister_code(KC_ENT);

                if (dj_spc_mode) {
                    if (layer_state_is(_DVORAK)) {
                        dj_spc_mode = false;
                        layer_move(_DVORAK_JP);
                    } else if (layer_state_is(_DVORAK_WIN)) {
                        dj_spc_mode = false;
                        layer_move(_DVORAK_JP_WIN);
                    } else if (layer_state_is(_DVORAK_SUM)) {
                        dj_spc_mode = false;
                        layer_move(_DVORAK_JP_SUM);
                    }
                }
            }
            move_pressed = false;
        }
        return false;


    default:
      if (record->event.pressed) {
          move_pressed = false;
      }
      break;

  }
  return true;
}


void matrix_init_user(void) {
    init_paw3204();
}

void matrix_scan_user(void) {
    static int  cnt;
    static bool paw_ready;

    report_mouse_t mouse_rep = pointing_device_get_report();

    if (IS_PRESSED(encoder1_ccw)) {
        encoder1_ccw.pressed = false;
        encoder1_ccw.time = (timer_read() | 1);
        action_exec(encoder1_ccw);
    }

    if (IS_PRESSED(encoder1_cw)) {
        encoder1_cw.pressed = false;
        encoder1_cw.time = (timer_read() | 1);
        action_exec(encoder1_cw);
    }

    if (cnt++ % 50 == 0) {
        uint8_t pid = read_pid_paw3204();
        if (pid == 0x30) {
            dprint("paw3204 OK\n");
            paw_ready = true;
        } else {
            dprintf("paw3204 NG:%d\n", pid);
            paw_ready = false;
        }
    }

    if (paw_ready) {
        uint8_t stat;
        int8_t x, y;
        int8_t r_x, r_y;

        read_paw3204(&stat, &x, &y);

        // 45-degree angle
        int8_t degree = 45;
        r_x =  + x * cos(degree) + y * sin(degree);
        r_y =  - x * sin(degree) + y * cos(degree);
        // int8_t degree = -45;
        // r_x =  - x * cos(degree) - y * sin(degree);
        // r_y =  + x * sin(degree) - y * cos(degree);
        /* normal angle
        r_x = y;
        r_y = x;
        */

        if (isScrollMode) {
            if (cnt % 5 == 0) {
                mouse_rep.v = -r_y;
                mouse_rep.h = r_x;
            }
        } else {
            mouse_rep.x = r_x;
            mouse_rep.y = r_y;
        }

        if (cnt % 10 == 0) {
            dprintf("stat:%3d x:%4d y:%4d\n", stat, mouse_rep.x, mouse_rep.y);
        }

        if (stat & 0x80) {
            pointing_device_set_report(mouse_rep);
        }
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _LOWER:
        isScrollMode = true;
        break;
    case _RAISE:
        isScrollMode = true;
        break;
    default:
        isScrollMode = false;
        break;
    }
  return state;
}


