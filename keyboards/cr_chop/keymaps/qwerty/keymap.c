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
    _QWERTY = 0,
    _SUMITOMO,
    _PORTUGUESE,
    _SUMITOMO_SHIFT,
    _LOWER,
    _SUMITOMO_LOWER,
    _RAISE,
    _SUMITOMO_RAISE,
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
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST,
  SW_WIN, SW_MAC, MW_MOD1, MW_MOD2, MW_MOD3, MW_MOD4, //switch windows/mac
  TO_JP,
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

// Tap Dance declarations
enum {
    TD_ACCENT,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_ACCENT] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_GRV),

};


bool windows_mode = true;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( \
     KC_ESC,                  KC_Q,  KC_W,  KC_E,  KC_R,    KC_T,                                                 KC_Y,           KC_U,   KC_I,    KC_O,   KC_P,         KC_BSPC,\
     LT(_emacsMOVE, KC_TAB),  KC_A,  KC_S,  KC_D,  KC_F,    KC_G,                                                 KC_H,           KC_J,   KC_K,    KC_L,   KC_SCLN,      KC_QUOT,\
     KC_LSFT,                 KC_Z,  KC_X,  KC_C,  KC_V,    KC_B,                                                 KC_N,           KC_M,   KC_COMM, KC_DOT, KC_SLSH,      KC_RSFT,\
     MW_MOD1,                 MW_MOD2,             MW_MOD3, LT(_LOWER, KC_SPC), LT(_RAISE, KC_TAB), LT(_vimMOVE, KC_ENT), LSFT_T(KC_SPC), KC_APP,                  LALT(KC_SPC), LGUI(KC_R)\
   ),

  [_SUMITOMO] = LAYOUT( \
     _______,                _______, _______, _______, _______,        _______,                                                                   _______,                     _______, _______, _______, _______, _______, \
     LT(_emacsMOVE, KC_TAB), _______, _______, _______, _______,        _______,                                                                   _______,                     _______, _______, _______, JP_SCLN, JP_QUOT, \
     KC_LSFT,                _______, _______, _______, _______,        _______,                                                                   _______,                     _______, _______, _______, _______, _______, \
     KC_LCTL,                KC_LCTL,                   KC_LALT, LT(_SUMITOMO_LOWER, KC_SPACE), LT(_SUMITOMO_RAISE, KC_TAB), LT(_vimMOVE, KC_ENT), LT(_SUMITOMO_SHIFT, KC_SPC), _______,                   KC_GRV,  LGUI(KC_R)\
  ),

  [_PORTUGUESE] = LAYOUT( \
     _______,                _______, _______, _______, _______,        _______,                                                                   _______,                     _______, _______, _______, _______, _______, \
     LT(_emacsMOVE, KC_TAB), _______, _______, _______, _______,        _______,                                                                   _______,                     _______, _______, _______, JP_SCLN, JP_QUOT, \
     KC_LSFT,                _______, _______, _______, _______,        _______,                                                                   _______,                     _______, _______, _______, _______, _______, \
     KC_LCTL,                 KC_LGUI,             KC_LALT, LT(_LOWER, KC_SPC), LT(_RAISE, KC_TAB), LT(_vimMOVE, KC_ENT), LSFT_T(KC_SPC), TD(TD_ACCENT),                  KC_SCLN, LGUI(KC_SPC)\
   ),

  [_SUMITOMO_SHIFT] = LAYOUT( \
     LSFT(KC_TAB),  LSFT(KC_Q),   LSFT(KC_W),    LSFT(KC_E),    LSFT(KC_R), LSFT(KC_T),                                LSFT(KC_Y), LSFT(KC_U), LSFT(KC_I),    LSFT(KC_O),   LSFT(KC_P),    LSFT(KC_BSPC), \
     KC_LCTL,       LSFT(KC_A),   LSFT(KC_S),    LSFT(KC_D),    LSFT(KC_F), LSFT(KC_G),                                LSFT(KC_H), LSFT(KC_J), LSFT(KC_K),    LSFT(KC_L),   JP_COLN,       JP_DQT, \
     LSFT(KC_LSFT), LSFT(KC_Z),   LSFT(KC_X),    LSFT(KC_C),    LSFT(KC_V), LSFT(KC_B),                   LSFT(KC_N), LSFT(KC_M), LSFT(KC_COMM), LSFT(KC_DOT), LSFT(KC_SLSH), LSFT(KC_ENT), \
     KC_NO,         KC_NO,                                      KC_NO,      KC_NO,       KC_NO,           LSFT(KC_ENT), LSFT(KC_SPC), KC_NO,                   KC_NO,         KC_NO \
  ),

  [_LOWER] = LAYOUT( \
    KC_ESC,        KC_EXLM,        KC_AT, KC_HASH, KC_DLR,  KC_PERC,                    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,\
    KC_TAB,        KC_1,           KC_2,  KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_NO,\
    KC_LSFT,       LSA(KC_1),      TO_JP, LSA(KC_3),   LSA(KC_4), LSA(KC_5),                      KC_NO,   KC_NO,   KC_COMM, KC_DOT,  KC_SLSH, KC_NO,\
    LCTL(KC_LEFT), LCTL(KC_RIGHT),                 KC_LGUI, LOWER,  MO(_ADJUST), KC_ENT, RAISE,   KC_RALT,                   KC_G,    KC_H \
  ),

  [_SUMITOMO_LOWER] = LAYOUT( \
    KC_ESC,              KC_EXLM,              JP_AT, KC_HASH, KC_DLR,  KC_PERC,                     JP_CIRC, JP_AMPR, JP_ASTR, JP_LPRN, JP_RPRN, KC_BSPC,\
    KC_TAB,              KC_1,                 KC_2,  KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_NO,\
    KC_LSFT,             KC_NO,                KC_NO, KC_NO,   KC_NO,   KC_NO,                       KC_NO,   KC_NO,   KC_COMM, KC_DOT,  KC_SLSH, KC_NO,\
    LCTL(LGUI(KC_LEFT)), LCTL(LGUI(KC_RIGHT)),                 KC_LGUI, LOWER,  MO(_ADJUST), KC_ENT, RAISE,   KC_RALT,                   KC_G,    KC_H \
  ),

  [_RAISE] = LAYOUT( \
    KC_GRV,        KC_F1,         KC_F2,  KC_F3,  KC_F4,   KC_F5,                           KC_PIPE, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_DEL,\
    LGUI(KC_TAB),  KC_F6,         KC_F7,  KC_F8,  KC_F9,   KC_F10,                          KC_TILD, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,\
    KC_TILD,       KC_F11,        KC_F12, KC_F13, KC_F14,  KC_F15,                          KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS, KC_TILD,\
    LCTL(KC_UP),  LCTL(KC_DOWN),                 KC_LGUI, MO(_ADJUST),  _______,   KC_ENT, RAISE,   KC_RALT,                   KC_K,    KC_L\
  ),

  [_SUMITOMO_RAISE] = LAYOUT( \
    JP_GRV,      KC_F1,   KC_F2,  KC_F3,  KC_F4,   KC_F5,                   JP_PIPE, JP_UNDS, JP_PLUS, JP_LCBR, JP_RCBR, KC_DEL,\
    LALT(KC_TAB), KC_F6,   KC_F7,  KC_F8,  KC_F9,   KC_F10,                  JP_TILD, JP_MINS, JP_EQL,  JP_LBRC, JP_RBRC, JP_BSLS,\
    JP_TILD,       KC_F11,  KC_F12, KC_F13, KC_F14,  KC_F15,                  JP_UNDS, JP_PLUS, JP_LBRC, JP_RBRC, JP_BSLS, JP_TILD,\
    LGUI(KC_TAB), KC_LGUI,                 KC_LGUI, MO(_ADJUST),  _______, KC_ENT, RAISE,   KC_RALT,                   KC_K,    KC_L\
  ),


  [_ADJUST] = LAYOUT( \
    RESET,   TO(_QWERTY), KC_NO,         TO(_PORTUGUESE),   TO(_SUMITOMO), KC_NO,             KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,\
    RGB_HUI, SW_WIN, SW_MAC,   RGB_VAI,    KC_NO,           KC_NO,                   KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,\
    RGB_MOD, RGB_HUD,     RGB_SAD,          RGB_VAD,    KC_NO,           KC_NO,                   KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,\
    RGBRST,   KC_NO,                                    KC_LGUI,         LOWER, _______,   KC_ENT, RAISE, KC_RALT,               KC_NO, KC_NO\
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
  #ifdef SSD1306OLED
    set_keylog(keycode, record);
  #endif
    // set_timelog();
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

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;

    case SW_WIN:
       if (record->event.pressed) {windows_mode = true;}
       return false;
    case SW_MAC:
       if (record->event.pressed) {windows_mode = false;}
       return false;
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

    case TO_JP:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_LSFT("2")));
        _delay_ms(250);
        SEND_STRING(SS_LCTRL(SS_TAP(X_CAPSLOCK)));
      }
      return false;
    // case LOWER:
    //   if (record->event.pressed) {
    //     layer_on(_LOWER);
    //     update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
    //   } else {
    //     layer_off(_LOWER);
    //     update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
    //   }
    //   return false;
    // case RAISE:
    //   if (record->event.pressed) {
    //     layer_on(_RAISE);
    //     update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
    //   } else {
    //     layer_off(_RAISE);
    //     update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
    //   }
    //   return false;
    // case ADJUST:
    //     if (record->event.pressed) {
    //       layer_on(_ADJUST);
    //     } else {
    //       layer_off(_ADJUST);
    //     }
    //     return false;
      break;
  }
  return true;
}


