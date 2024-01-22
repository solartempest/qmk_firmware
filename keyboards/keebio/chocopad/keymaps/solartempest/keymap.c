// Copyright 2023 Danny Nguyen (danny@keeb.io)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

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

/*led_config_t g_led_config = { {
  // Key Matrix to LED Index
	{	NO_LED,	0,	1,	NO_LED	},
	{	2,	3,	4,	5	},
	{	6,	7,	8,	9	},
	{	10,	11,	12,	13	},
	{	14,	15,	16,	17	},
	{	NO_LED,	18,	19,	NO_LED	}
}, {
  // LED Index to Physical Position
  {37,0},{187,0},{0,0},{74,0},{149,0},{224,0},{0,21},{74,21},{149,21},{224,21},{0,43},{74,43},{149,43},{224,43},{0,64},{74,64},{149,64},{224,64},{37,64},{187,64}
}, {
  // LED Index to Flag
  2,2,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,2,2
} };*/


bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    for (uint8_t i = led_min; i < led_max; i++) {
        switch(get_highest_layer(layer_state|default_layer_state)) {
            case 2:
                rgb_matrix_set_color(i, RGB_BLUE);
                break;
            case 1:
                rgb_matrix_set_color(i, RGB_SPRINGGREEN);
                break;
            default:
                break;
        }
    }
    return false;
} //Works for all LEDs set to these colours only

/*bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (get_highest_layer(layer_state) > 0) {
        uint8_t layer = get_highest_layer(layer_state);

        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                if (index >= led_min && index < led_max && index != NO_LED &&
                keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
                    rgb_matrix_set_color(index, RGB_SPRINGGREEN );
                }
            }
        }
    }
    return false;
}*/	//Works for keys only, not underglow


/*bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    HSV hsv = {106, 255, 255};	//spring green

	hsv = {HSV_AZURE};
    if (layer_state_cmp(layer_state, 2)) {
        hsv = {132, 102, 255};	//azure
    } else {
        hsv = {30, 218, 218};	//goldenrod
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
}*/



