#include QMK_KEYBOARD_H
#include "keymap_jp.h"
#include "quantum.h"
#include "action_layer.h"

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _DVORAK = 0,
    _DVORAK_JP,
    _DVORAK_JP1,
    _DVORAK_JP2,
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
    _vimMOVE,
    _emacsMOVE,
};

// #define _QWERTY 0
// #define _IOS 1
// #define _WIN 2
// #define _SUMITOMO 3
// #define _LOWER 4
// #define _SUMITOMOLOWER 5
// #define _RAISE 6
// #define _SUMITOMORAISE 7
// #define _ADJUST 8
// #define _vimMOVE 9
// #define _emacsMOVE 10

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  DJ_A, DJ_B, DJ_C, DJ_D, DJ_E, DJ_F, DJ_G, DJ_H, DJ_I, DJ_J, DJ_K, DJ_L, DJ_M, DJ_N, DJ_O, DJ_P, DJ_Q, DJ_R, DJ_S, DJ_T, DJ_U, DJ_V, DJ_W, DJ_X, DJ_Y, DJ_Z,
  DJ_QUOT, DJ_COMM, DJ_SCLN,
  DJ_ANN, DJ_INN, DJ_UNN, DJ_ENN, DJ_ONN,
  DJ_AI, DJ_OU, DJ_EI, DJ_UU, DJ_UI,
  DJ_XTU, DJ_CLEAR, DJ_BSPC,

  SW_MW, MW_MOD1, MW_MOD2, MW_MOD3, MW_MOD4, MW_MOD5, MW_MOD6, //switch windows/mac
  RAUNCHER, INPUT,
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

// Tap Dance declarations
enum {
    TD_ALT_GUI,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_ALT_GUI] = ACTION_TAP_DANCE_DOUBLE(KC_LALT, KC_LGUI),
};

short int dj_mode = 0;
bool windows_mode = false;
bool japanese_mode = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DVORAK] = LAYOUT( \
     KC_ESC,                 KC_QUOT, KC_COMM, KC_DOT, KC_P,    KC_Y,                                                 KC_F,           KC_G,   KC_C, KC_R, KC_L,         KC_BSPC, \
     LT(_emacsMOVE, KC_TAB), KC_A,    KC_O,    KC_E,   KC_U,    KC_I,                                                 KC_D,           KC_H,   KC_T, KC_N, KC_S,         KC_SLSH, \
     KC_LSFT,                KC_SCLN, KC_Q,    KC_J,   KC_K,    KC_X,                                                 KC_B,           KC_M,   KC_W, KC_V, KC_Z,         KC_ENT , \
     MW_MOD1,                MW_MOD2,                  MW_MOD3, MO(_LOWER), LT(_RAISE, KC_TAB), LT(_vimMOVE, KC_ENT), LSFT_T(KC_SPC), MW_MOD4,            LALT(KC_SPC), LGUI(KC_SPC) \
  ),

  [_DVORAK_JP] = LAYOUT( \
     KC_ESC,                 KC_QUOT, KC_COMM, KC_DOT, DJ_P,    DJ_Y,                                                DJ_F,           DJ_G,   DJ_K, DJ_R, DJ_L,         KC_BSPC, \
     LT(_emacsMOVE, KC_TAB), DJ_A,    DJ_O,    DJ_E,   DJ_U,    DJ_I,                                                DJ_D,           DJ_H,   DJ_T, DJ_N, DJ_S,         KC_SLSH, \
     KC_LSFT,                KC_SCLN, DJ_Q,    DJ_J,   DJ_K,    DJ_X,                                                DJ_B,           DJ_M,   DJ_W, DJ_XTU, DJ_Z,         KC_ENT , \
     MW_MOD1,                MW_MOD2,                  MW_MOD3, MO(_LOWER), LT(_RAISE, KC_TAB), LT(_vimMOVE, KC_ENT), LSFT_T(KC_SPC), MW_MOD4,            LALT(KC_SPC), LGUI(KC_SPC) \
  ),

  [_DVORAK_JP1] = LAYOUT( \
     DJ_CLEAR, DJ_AI,    DJ_OU,    DJ_EI,    DJ_P,     DJ_Y,                         DJ_F,     DJ_G,     DJ_K, DJ_R, DJ_L,     DJ_BSPC, \
     DJ_CLEAR, DJ_A,     DJ_O,     DJ_E,     DJ_U,     DJ_I,                         DJ_D,     DJ_H,     DJ_T, DJ_Y, DJ_S,     DJ_CLEAR, \
     DJ_CLEAR, DJ_ANN,   DJ_ONN,   DJ_ENN,   DJ_UNN,   DJ_INN,                       DJ_B,     DJ_M,     DJ_W, DJ_XTU, DJ_Z,     DJ_CLEAR , \
     DJ_CLEAR, DJ_CLEAR,                     DJ_CLEAR, DJ_CLEAR, DJ_CLEAR, DJ_CLEAR, DJ_CLEAR, DJ_CLEAR,             DJ_CLEAR, DJ_CLEAR \
  ),

  [_DVORAK_JP2] = LAYOUT( \
     DJ_CLEAR, DJ_AI,    DJ_OU,    DJ_EI,    DJ_P,     DJ_Y,                         DJ_F,     DJ_G,     DJ_K, DJ_R, DJ_L,     DJ_BSPC, \
     DJ_CLEAR, DJ_A,     DJ_O,     DJ_E,     DJ_U,     DJ_I,                         DJ_D,     DJ_Y,     DJ_T, DJ_N, DJ_S,     DJ_CLEAR, \
     DJ_CLEAR, DJ_ANN,   DJ_ONN,   DJ_ENN,   DJ_UNN,   DJ_INN,                       DJ_B,     DJ_M,     DJ_W, DJ_XTU, DJ_Z,     DJ_CLEAR , \
     DJ_CLEAR, DJ_CLEAR,                     DJ_CLEAR, DJ_CLEAR, DJ_CLEAR, DJ_CLEAR, DJ_CLEAR, DJ_CLEAR,             DJ_CLEAR, DJ_CLEAR \
  ),

  [_QWERTY] = LAYOUT( \
     KC_ESC,         KC_Q,  KC_W,  KC_E,  KC_R,    KC_T,                                                 KC_Y,           KC_U,   KC_I,    KC_O,   KC_P,         KC_BSPC,\
     CTL_T(KC_TAB),  KC_A,  KC_S,  KC_D,  KC_F,    KC_G,                                                 KC_H,           KC_J,   KC_K,    KC_L,   KC_SCLN,      KC_QUOT,\
     KC_LSFT,        KC_Z,  KC_X,  KC_C,  KC_V,    KC_B,                                                 KC_N,           KC_M,   KC_COMM, KC_DOT, KC_SLSH,      KC_RSFT,\
     KC_LGUI,        KC_LALT,             KC_LGUI, MO(_LOWER), LT(_RAISE, KC_TAB), LT(_vimMOVE, KC_ENT), LSFT_T(KC_SPC), KC_APP,                  LALT(KC_SPC), LGUI(KC_SPC)\
   ),

  [_LOWER] = LAYOUT( \
    KC_ESC,        KC_EXLM,        KC_AT, KC_HASH, KC_DLR,  KC_PERC,                    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,\
    KC_TAB,        KC_1,           KC_2,  KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_NO,\
    KC_LSFT,       KC_NO,          KC_NO, KC_NO,   KC_NO,   KC_NO,                      KC_NO,   KC_NO,   KC_COMM, KC_DOT,  KC_SLSH, KC_NO,\
    LCTL(KC_LEFT), LCTL(KC_RIGHT),                 KC_LGUI, MO(_LOWER),  MO(_ADJUST), KC_ENT, MO(_RAISE),   KC_RALT,                   KC_G,    KC_H \
  ),

  [_RAISE] = LAYOUT( \
    KC_GRV,        KC_F1,         KC_F2,  KC_F3,  KC_F4,   KC_F5,                           KC_PIPE, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_DEL,\
    LGUI(KC_TAB),  KC_F6,         KC_F7,  KC_F8,  KC_F9,   KC_F10,                          KC_TILD, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,\
    KC_TILD,       KC_F11,        KC_F12, KC_F13, KC_F14,  KC_F15,                          KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS, KC_TILD,\
    LCTL(KC_UP),  LCTL(KC_DOWN),                 KC_LGUI, MO(_ADJUST),  _______,   KC_ENT, MO(_RAISE),   KC_RALT,                   KC_K,    KC_L\
  ),

  [_ADJUST] = LAYOUT( \
    RESET,   TO(_QWERTY), MAGIC_SWAP_ALT_GUI,   MAGIC_UNSWAP_ALT_GUI,   KC_NO, KC_NO,                                KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,\
    RGB_HUI, TO(_DVORAK), TO(_DVORAK_JP),   RGB_VAI,    KC_NO,           KC_NO,                   KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,\
    SW_MW,   RGB_HUD,     RGB_SAD,          RGB_VAD,    KC_NO,           KC_NO,                   KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,\
    KC_NO,   KC_NO,                                    KC_LGUI,         MO(_LOWER), _______,   KC_ENT, MO(_RAISE), KC_RALT,               KC_NO, KC_NO\
  ),

  [_vimMOVE] = LAYOUT( \
     KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,               KC_HOME, KC_PGDOWN, KC_PGUP, KC_END,   KC_NO, KC_NO, \
     KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,               KC_LEFT, KC_DOWN,   KC_UP,   KC_RIGHT, KC_NO, KC_NO, \
     KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,               KC_BSPC, KC_DEL,    KC_NO,   KC_NO,    KC_NO, KC_NO, \
     KC_LCTL, KC_LALT,             KC_LALT, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,                        KC_NO, KC_NO \
  ),

   [_emacsMOVE] = LAYOUT( \
     KC_NO,   KC_NO,   KC_NO, KC_END, KC_NO,    KC_NO,                 KC_NO,   KC_NO, KC_NO, KC_NO, KC_UP, KC_NO, \
     KC_NO,   KC_HOME, KC_NO, KC_DEL, KC_RIGHT, KC_NO,                 KC_BSPC, KC_NO, KC_NO, KC_NO, KC_F10, KC_NO, \
     KC_LSFT, KC_NO,   KC_NO, KC_NO,  KC_NO,    KC_LEFT,               KC_DOWN, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, \
     KC_LCTL, KC_NO,                  KC_NO,    KC_NO,   KC_NO, KC_NO, KC_NO,   KC_NO,               KC_NO, KC_NO \
  )


};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    // matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    // matrix_write_ln(matrix, read_host_led_state());
    // matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

void dj_layer_off(void) {
    if (layer_state_is(_DVORAK_JP1)) {layer_off(_DVORAK_JP1);}
    if (layer_state_is(_DVORAK_JP2)) {layer_off(_DVORAK_JP2);}
}

void press_mod (uint16_t win_keycode, uint16_t mac_keycode, keyrecord_t *record) {
  if (windows_mode) {
        if (record->event.pressed) {
            layer_on(_QWERTY);
            register_code(win_keycode);
        } else {
            unregister_code(win_keycode);
            layer_off(_QWERTY);
        }
      } else {
        if (record->event.pressed) {
            layer_on(_QWERTY);
            register_code(mac_keycode);
        } else {
            unregister_code(mac_keycode);
            layer_off(_QWERTY);
        }
      }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case DJ_P:
        if (record->event.pressed) {SEND_STRING("p"); layer_on(_DVORAK_JP1);}
        return false;

    case DJ_Y:
        if (record->event.pressed) {SEND_STRING("y"); layer_on(_DVORAK_JP1);}
        return false;

    case DJ_A:
        if (record->event.pressed) {SEND_STRING("a"); dj_layer_off();}
        return false;

    case DJ_O:
        if (record->event.pressed) {SEND_STRING("o"); dj_layer_off();}
        return false;

    case DJ_E:
        if (record->event.pressed) {SEND_STRING("e"); dj_layer_off();}
        return false;

    case DJ_U:
        if (record->event.pressed) {SEND_STRING("u"); dj_layer_off();}
        return false;

    case DJ_I:
        if (record->event.pressed) {SEND_STRING("i"); dj_layer_off();}
        return false;

    // case DJ_K:
    //     if (record->event.pressed) {
    //         SEND_STRING("k");
    //         layer_on(_DVORAK_JP2);
    //     }
    //     return false;

    case DJ_Q:
        if (record->event.pressed) {SEND_STRING("q"); layer_on(_DVORAK_JP1);}
        return false;

    case DJ_J:
        if (record->event.pressed) {SEND_STRING("j"); layer_on(_DVORAK_JP1);}
        return false;

    case DJ_C:
        if (record->event.pressed) {SEND_STRING("k"); layer_on(_DVORAK_JP1);}
        return false;

    case DJ_X:
        if (record->event.pressed) {SEND_STRING("x"); layer_on(_DVORAK_JP1);}
        return false;

    // -----------------------------

    case DJ_F:
        if (record->event.pressed) {SEND_STRING("f"); layer_on(_DVORAK_JP1);}
        return false;

    case DJ_G:
        if (record->event.pressed) {SEND_STRING("g"); layer_on(_DVORAK_JP1);}
        return false;

    case DJ_K:
        if (record->event.pressed) {SEND_STRING("k"); layer_on(_DVORAK_JP1);}
        return false;

    case DJ_R:
        if (record->event.pressed) {SEND_STRING("r"); layer_on(_DVORAK_JP2);}
        return false;

    case DJ_L:
        if (record->event.pressed) {SEND_STRING("l"); layer_on(_DVORAK_JP2);}
        return false;

    case DJ_D:
        if (record->event.pressed) {SEND_STRING("d"); layer_on(_DVORAK_JP1);}
        return false;

    case DJ_H:
        if (record->event.pressed) {SEND_STRING("h"); layer_on(_DVORAK_JP1);}
        return false;

    case DJ_T:
        if (record->event.pressed) {SEND_STRING("t"); layer_on(_DVORAK_JP1);}
        return false;

    case DJ_N:
        if (record->event.pressed) {SEND_STRING("n"); layer_on(_DVORAK_JP2);}
        return false;

    case DJ_S:
        if (record->event.pressed) {SEND_STRING("s"); layer_on(_DVORAK_JP2);}
        return false;

    case DJ_B:
        if (record->event.pressed) {SEND_STRING("b"); layer_on(_DVORAK_JP1);}
        return false;

    case DJ_M:
        if (record->event.pressed) {SEND_STRING("m"); layer_on(_DVORAK_JP1);}
        return false;

    case DJ_W:
        if (record->event.pressed) {SEND_STRING("w"); layer_on(_DVORAK_JP1);}
        return false;

    case DJ_V:
        if (record->event.pressed) {SEND_STRING("v"); layer_on(_DVORAK_JP2);}
        return false;

    case DJ_Z:
        if (record->event.pressed) {SEND_STRING("z"); layer_on(_DVORAK_JP2);}
        return false;

    // -----------------------------

    case DJ_ANN:
        if (record->event.pressed) {SEND_STRING("ann"); dj_layer_off();}
        return false;

    case DJ_INN:
        if (record->event.pressed) {SEND_STRING("inn"); dj_layer_off();}
        return false;

    case DJ_UNN:
        if (record->event.pressed) {SEND_STRING("unn"); dj_layer_off();}
        return false;

    case DJ_ENN:
        if (record->event.pressed) {SEND_STRING("enn"); dj_layer_off();}
        return false;

    case DJ_ONN:
        if (record->event.pressed) {SEND_STRING("onn"); dj_layer_off();}
        return false;

    case DJ_AI:
        if (record->event.pressed) {SEND_STRING("ai"); dj_layer_off();}
        return false;

    case DJ_UI:
        if (record->event.pressed) {SEND_STRING("ui"); dj_layer_off();}
        return false;

    case DJ_UU:
        if (record->event.pressed) {SEND_STRING("uu"); dj_layer_off();}
        return false;

    case DJ_EI:
        if (record->event.pressed) {SEND_STRING("ei"); dj_layer_off();}
        return false;

    case DJ_OU:
        if (record->event.pressed) {SEND_STRING("ou"); dj_layer_off();}
        return false;

    case DJ_XTU:
        if (record->event.pressed) {SEND_STRING("xtu"); dj_layer_off();}
        return false;

    case DJ_CLEAR:
        if (record->event.pressed) {dj_layer_off(); }
        return false;

    case DJ_BSPC:
        if (record->event.pressed) {register_code(KC_BSPC); unregister_code(KC_BSPC); dj_layer_off(); }
        return false;

    // case RGBRST:
    //   #ifdef RGBLIGHT_ENABLE
    //     if (record->event.pressed) {
    //       eeconfig_update_rgblight_default();
    //       rgblight_enable();
    //       RGB_current_mode = rgblight_config.mode;
    //     }
    //   #endif
    //   break;
    case SW_MW:
      if (record->event.pressed) {
          if (windows_mode) {windows_mode = false;} else {windows_mode = true;}
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

  }
  return true;
}
