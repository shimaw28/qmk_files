#include QMK_KEYBOARD_H
#include "bootloader.h"
#include "keymap_jp.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

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
    _QWERTY_WIN,
    _IOS,
    _SUMITOMO,
    _LOWER,
    _SUMITOMO_LOWER,
    _RAISE,
    _SUMITOMO_RAISE,
    _ADJUST,
    _VIMMOVE,
    _WINMOVE,
    _IOSMOVE,
    _SUMITOMO_SHIFT
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  EISU,
  KANA,
  RGBRST,
  VIMMOVE,
  WN_SCRN,
  WN_QUOT
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)

#if HELIX_ROWS == 5
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT( \
      KC_ESC,  KC_1,          KC_2,    KC_3,    KC_4,    KC_5,                                  KC_6,             KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, \
      KC_TAB,  KC_Q,          KC_W,    KC_E,    KC_R,    KC_T,                                  KC_Y,             KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
      KC_LCTL, KC_A,          KC_S,    KC_D,    KC_F,    KC_G,                                  KC_H,             KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
      KC_LSFT, KC_Z,          KC_X,    KC_C,    KC_V,    KC_B,  LALT(KC_SPACE), LGUI(KC_SPACE), KC_N,             KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT , \
      KC_LGUI, MO(_VIMMOVE),  KC_LALT, KC_LGUI, KC_RALT,  LOWER, RAISE,   LT(_VIMMOVE, KC_ENT) , LSFT_T(KC_SPC),   KC_APP,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
      ),

  [_IOS] = LAYOUT( \
      _______,      _______, _______, _______, _______, _______,                             _______, _______, _______, _______, _______, _______, \
      _______,      _______, _______, _______, _______, _______,                             _______, _______, _______, _______,  _______, _______, \
      MO(_IOSMOVE), _______, _______, _______, _______, _______,                             _______, _______, _______, _______,  _______, _______, \
      _______,      _______, _______, _______, _______, _______,LCTL(KC_SPACE), _______,     _______, _______, _______, _______,  _______, _______,  \
      _______,      _______, _______, _______, _______, _______,       _______, _______,     _______, _______, _______, _______,  _______, _______ \
      ),

  [_QWERTY_WIN] = LAYOUT( \
      _______,      _______, _______, _______, _______, _______,                             _______, _______, _______, _______, _______, _______, \
      _______,      _______, _______, _______, _______, _______,                             _______, _______, _______, _______,  _______, _______, \
      MO(_WINMOVE), _______, _______, _______, _______, _______,                             _______, _______, _______, _______,  _______, _______, \
      _______,      _______, _______, _______, _______, _______,       _______, _______,     _______, _______, _______, _______,  _______, _______,  \
      KC_LCTL,      _______, _______, _______, _______, _______,       _______, _______,     _______, _______, _______, _______,  _______, _______ \
      ),

  [_SUMITOMO] = LAYOUT( \
      _______,      _______, _______, _______, _______, _______,                                     _______,                         _______, _______, _______, _______, JP_MINS, \
      _______,      _______, _______, _______, _______, _______,                                     _______,                         _______, _______, _______,  _______, _______, \
      MO(_WINMOVE), _______, _______, _______, _______, _______,                                     _______,                         _______, _______, _______,  WN_SCRN, JP_QUOT, \
      KC_LSFT,      _______, _______, _______, _______, _______,  KC_GRV,             LGUI(KC_R), _______,                         _______, _______, _______,  _______, _______,  \
      KC_LCTL,      _______, _______, _______, _______, MO(_SUMITOMO_LOWER),  MO(_SUMITOMO_RAISE), _______,  LT(_SUMITOMO_SHIFT, KC_SPC), _______, _______, _______,  _______, _______ \
      ),

  [_LOWER] = LAYOUT( \
      KC_TILD, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10, KC_F11, \
      _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,KC_DEL, \
      _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_PIPE, \
      _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F11, KC_F12, KC_F12,  KC_1,    KC_COMM, KC_DOT,  KC_SLASH,  _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, MO(_RAISE), KC_0,    KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
      ),

  [_SUMITOMO_LOWER] = LAYOUT( \
      _______,      _______, _______, _______, _______, _______,                             _______, _______, _______, _______, _______, _______, \
      _______,  LSFT(KC_1), JP_AT, JP_HASH, JP_DLR, JP_PERC,                            JP_CIRC, JP_AMPR, JP_ASTR, JP_LPRN, JP_RPRN, JP_UNDS, \
      _______,      KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_PIPE, \
      _______,      _______, _______, _______, _______, _______,       _______, _______,     _______, _______, _______, _______,  _______, _______,  \
      _______,      _______, _______, _______, _______, _______,       _______, _______,     MO(_SUMITOMO_RAISE), _______, _______, _______,  _______, _______ \
      ),

  [_RAISE] = LAYOUT( \
      KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, \
      KC_TILD,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_PIPE, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_DEL, \
      KC_GRV  , KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,                      KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
      _______, KC_F11,   KC_F12,  _______, _______, _______,  _______, _______, KC_F12,  _______, _______, KC_PGDN, KC_PGUP, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
      ),

  [_SUMITOMO_RAISE] = LAYOUT( \
      JP_GRV,  _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
      JP_TILD, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                   JP_PIPE, JP_UNDS, JP_PLUS, JP_LCBR, JP_RCBR, KC_DEL, \
      JP_GRV, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,                     _______, JP_MINS, JP_EQL,  JP_LBRC, JP_RBRC, JP_BSLS,\
      _______, KC_F11, KC_F12, _______, _______, _______,  _______, _______,_______, _______, _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______\
    ),

  [_ADJUST] =  LAYOUT( \
      _______, _______,     _______,          _______,         _______, _______,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
      _______, RESET,       RGBRST,           _______,         _______, _______,                   _______, _______, _______, _______, KC_VOLU, KC_DEL, \
      _______, _______,     _______,          AU_ON,           AU_OFF,  AG_NORM,                   AG_SWAP, KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, _______, \
      _______, TO(_QWERTY), TO(_QWERTY_WIN),  TO(_SUMITOMO),   TO(_IOS), _______, _______, KC__VOLUP, KC_VOLD, _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
      _______, _______,     _______,          _______,         _______, _______, _______, KC__VOLDOWN, _______, _______, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD \
      ),

  [_VIMMOVE] =  LAYOUT( \
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______,                   KC_HOME, KC_PGDN, KC_PGUP, KC_END, _______, _______, \
      _______, _______, _______, _______, _______, _______,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, \
      _______, _______, KC_DEL,  _______, _______, _______, _______, _______, KC_BSPC, KC_DEL,  _______, _______, _______, _______, \
      _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
      ),

  [_IOSMOVE] =  LAYOUT( \
    _______, _______,    _______, _______,    _______,  _______,                                 _______, _______, _______, _______, _______, _______, \
    _______, _______,    _______, LCTL(KC_E), _______,  _______,                                 _______, _______, _______,  _______, KC_UP , _______, \
    _______, LCTL(KC_A), _______, KC_DEL,     KC_RIGHT, _______,                                 KC_BSPC, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, \
    _______, _______,    _______, _______,    _______,  KC_LEFT, LCTL(KC_SPACE), LGUI(KC_SPACE), KC_DOWN, _______, _______, _______, _______, _______, \
    _______,  _______,   _______, _______,    _______,  _______, _______,        _______,        _______, _______, _______, _______, _______, _______ \
    ),

  [_WINMOVE] = LAYOUT( \
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, \
      KC_TAB,  KC_Q,    KC_W,    KC_END,  KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_UP,    KC_BSPC, \
      KC_LCTL, KC_HOME, KC_S,    KC_DEL,  KC_RGHT, KC_G,                               KC_BSPC, KC_J,    KC_K,    KC_L,    KC_F10,   KC_QUOT, \
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_LEFT,        KC_LBRC, KC_RBRC,   KC_DOWN, KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT , \
      KC_LCTL, ADJUST,  KC_LALT, KC_LGUI, EISU,    LSFT_T(KC_SPC), LOWER,   RAISE,     LSFT_T(KC_SPC),   KANA,    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
      ),

  [_SUMITOMO_SHIFT] = LAYOUT( \
      LSFT(KC_ESC),  LSFT(KC_1),   JP_AT,         JP_HASH,       JP_DLR,     JP_PERC,                                   JP_CIRC,    JP_AMPR,    JP_ASTR,       JP_LPRN,      JP_RPRN,       JP_UNDS, \
      LSFT(KC_TAB),  LSFT(KC_Q),   LSFT(KC_W),    LSFT(KC_E),    LSFT(KC_R), LSFT(KC_T),                                LSFT(KC_Y), LSFT(KC_U), LSFT(KC_I),    LSFT(KC_O),   LSFT(KC_P),    LSFT(KC_BSPC), \
      KC_LCTL,       LSFT(KC_A),   LSFT(KC_S),    LSFT(KC_D),    LSFT(KC_F), LSFT(KC_G),                                LSFT(KC_H), LSFT(KC_J), LSFT(KC_K),    LSFT(KC_L),   JP_COLN,       JP_DQT, \
      LSFT(KC_LSFT), LSFT(KC_Z),   LSFT(KC_X),    LSFT(KC_C),    LSFT(KC_V), LSFT(KC_B), JP_LCBR,        JP_RCBR,       LSFT(KC_N), LSFT(KC_M), LSFT(KC_COMM), LSFT(KC_DOT), LSFT(KC_SLSH), LSFT(KC_ENT), \
      LSFT(KC_LCTL), LSFT(KC_ENT), LSFT(KC_LALT), LSFT(KC_LGUI), LSFT(ADJUST), LSFT(LOWER), LSFT(RAISE), LSFT(KC_ENT),  LSFT(KC_SPC), LSFT(KC_APP), LSFT(KC_LEFT), LSFT(KC_DOWN), LSFT(KC_UP), LSFT(KC_RGHT)
    )

};
#else
#error "undefined keymaps"
#endif


// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    #ifdef RGBLIGHT_ENABLE
      //rgblight_mode(RGB_current_mode);
    #endif
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static bool lshift = false;
    static bool rshift = false;

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
          persistent_default_layer_set(1UL << _QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
          // not sure how to have keyboard check mode and set it to a variable, so my work around
          // uses another variable that would be set to true after the first time a reactive key is pressed.
          if (TOG_STATUS) {  // TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
          } else {
              TOG_STATUS = !TOG_STATUS;
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGBLIGHT_MODE_SNAKE + 1);
        #endif
        }
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);   // revert RGB to initial mode prior to RGB mode change
        #endif
        TOG_STATUS = false;
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        //not sure how to have keyboard check mode and set it to a variable, so my work around
        //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(RGBLIGHT_MODE_SNAKE);
          #endif
        }
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
        #endif
        layer_off(_RAISE);
        TOG_STATUS = false;
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case EISU:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG2);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG2);
      }
      return false;
      break;
    case KANA:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG1);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG1);
      }
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;

    case WN_SCRN:
      if (record->event.pressed) {
        lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
        rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
        if (lshift || rshift) {
          if (lshift) unregister_code(KC_LSFT);
          if (rshift) unregister_code(KC_RSFT);
          register_code(JP_COLN);
          unregister_code(JP_COLN);
          if (lshift) register_code(KC_LSFT);
          if (rshift) register_code(KC_RSFT);
        } else {
          register_code(JP_SCLN);
          unregister_code(JP_SCLN);
        }
      }
      return false;
      break;

    // case WN_QUOT:
    //     if (record->event.pressed) {
    //         lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
    //         rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
    //         if (lshift || rshift) {
    //             if (lshift) unregister_code(KC_LSFT);
    //             if (rshift) unregister_code(KC_RSFT);
    //             register_code(JP_DQT);
    //             unregister_code(JP_DQT);
    //             if (lshift) register_code(KC_LSFT);
    //             if (rshift) register_code(KC_RSFT);
    //             // register_code(KC_2);
    //             // unregister_code(KC_2);
    //         } else {
    //             register_code(JP_QUOT);
    //             unregister_code(JP_QUOT);
    //         }
    //     }
    //     return false;
    //     break;

        // case VIMMOVE:
        //     if (record->event.pressed) {
        //       persistent_default_layer_set(1UL << _VIMMOVE);
        //     }
        //     return false;
        //     break;
  }
  return true;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
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

void matrix_scan_user(void) {
     iota_gfx_task();  // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_QWERTY (1<<_QWERTY)
#define L_QWERTY_WIN (1<<_QWERTY_WIN)
#define L_SUMITOMO (1<<_SUMITOMO)
#define L_221MOVE (1<<_WINMOVE)
#define L_IOS (1<<_IOS)
#define L_IOSMOVE (1<<_IOSMOVE)
#define L_LOWER (1<<_LOWER)
#define L_RAISE (1<<_RAISE)
#define L_ADJUST (1<<_ADJUST)
#define L_ADJUST_TRI (L_ADJUST|L_RAISE|L_LOWER)
#define L_VIMMOVE (1<<_VIMMOVE)

static void render_logo(struct CharacterMatrix *matrix) {

  static char logo[]={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  matrix_write(matrix, logo);
  //matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
}



void render_status(struct CharacterMatrix *matrix) {

  // Render to mode icon
  static char logo[][2][3]={{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}};
  if(keymap_config.swap_lalt_lgui==false){
    matrix_write(matrix, logo[0][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[0][1]);
  }else{
    matrix_write(matrix, logo[1][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[1][1]);
  }

  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  char buf[40];
  snprintf(buf,sizeof(buf), "Undef-%ld", layer_state);
  matrix_write_P(matrix, PSTR("\nLayer: "));
    switch (layer_state) {
        case L_BASE:
          matrix_write_P(matrix, PSTR("Default"));
          break;
        case L_QWERTY:
            matrix_write_P(matrix, PSTR("Qwerty"));
            break;
        case L_QWERTY_WIN:
            matrix_write_P(matrix, PSTR("Qwerty Win"));
            break;
        case L_SUMITOMO:
            matrix_write_P(matrix, PSTR("Sumitomo"));
            break;
        case L_221MOVE:
            matrix_write_P(matrix, PSTR("Win Move"));
            break;
        case L_RAISE:
          matrix_write_P(matrix, PSTR("Raise"));
          break;
        case L_LOWER:
          matrix_write_P(matrix, PSTR("Lower"));
          break;
        case L_ADJUST:
        case L_ADJUST_TRI:
          matrix_write_P(matrix, PSTR("Adjust"));
          break;
        case L_VIMMOVE:
            matrix_write_P(matrix, PSTR("VIM move"));
            break;
        case L_IOS:
            matrix_write_P(matrix, PSTR("iOS"));
            break;
        case L_IOSMOVE:
            matrix_write_P(matrix, PSTR("iOS move"));
            break;
        default:
          matrix_write(matrix, buf);
    }

  // Host Keyboard LED Status
  char led[40];
    snprintf(led, sizeof(led), "\n%s  %s  %s",
            (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ? "NUMLOCK" : "       ",
            (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ? "CAPS" : "    ",
            (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ? "SCLK" : "    ");
  matrix_write(matrix, led);
}


void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  if(is_master){
    render_status(&matrix);
  }else{
    render_logo(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif
