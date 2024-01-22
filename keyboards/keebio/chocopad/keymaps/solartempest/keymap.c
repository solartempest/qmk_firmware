// Copyright 2023 Danny Nguyen (danny@keeb.io)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
uint8_t led_min = 0;
uint8_t led_max = RGB_MATRIX_LED_COUNT;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT_ortho_4x4(
    KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
    KC_P4,   KC_P5,   KC_P6,   KC_PERC,
    KC_P1,   KC_P2,   KC_P3,   KC_EQL,
    KC_P0,   MO(1),   KC_PDOT, KC_PENT
  ),
  [1] = LAYOUT_ortho_4x4(
    RGB_TOG, KC_PSLS, KC_PAST, KC_PMNS,
    KC_PGUP, KC_HOME, KC_UP,   KC_END,
    KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT,
    RGB_MOD, _______, KC_VOLD, KC_VOLU
  )
};

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    HSV hsv = {HSV_SPRINGGREEN};
	if (layer_state_cmp(layer_state, 1)) {
        hsv = (HSV){HSV_CHARTREUSE};
	} else if (layer_state_cmp(layer_state, 2)) {
        hsv = (HSV){HSV_GOLDENROD};
	} else if (layer_state_cmp(layer_state, 3)) {
        hsv = (HSV){HSV_MAGENTA};
    } else {
        hsv = (HSV){HSV_SPRINGGREEN};
    }

    if (hsv.v > rgb_matrix_get_val()) {
        hsv.v = rgb_matrix_get_val();
    }
    RGB rgb = hsv_to_rgb(hsv);

    for (uint8_t i = led_min; i < led_max; i++) {
        if (HAS_FLAGS(g_led_config.flags[i], 0x02)) { // 0x02 == LED_FLAG_UNDERGLOW
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
    return false;
}
