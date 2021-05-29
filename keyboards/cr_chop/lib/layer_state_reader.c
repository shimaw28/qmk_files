
#include QMK_KEYBOARD_H
#include <stdio.h>
#include "cr_chop.h"

// in the future, should use (1U<<_LAYER_NAME) instead, but needs to be moved to keymap,c
#define L_BASE 0
#define L_QWERTY 1
#define L_IOS 2
#define L_WIN 4
#define L_SUMITOMO 8
#define L_LOWER 32


char layer_state_str[24];

const char *read_layer_state(void) {
  switch (layer_state)
  {
  case L_BASE:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Default");
    break;
  case L_QWERTY:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Qwerty");
    break;
  case L_IOS:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: iOS");
    break;
  case L_WIN:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Windows");
    break;
  case L_SUMITOMO:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Sumitomo");
    break;
  case L_LOWER:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Lower");
  default:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undef-%ld", layer_state);
  }

  return layer_state_str;
}
