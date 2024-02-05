// Copyright 2023 Danny Nguyen (danny@keeb.io)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
uint8_t led_min = 0;
uint8_t led_max = RGB_MATRIX_LED_COUNT;

bool spam_arrow = false;	// Spam F24 or other keys like arrows
uint16_t spam_timer = false;
uint16_t spam_interval = 1000;	// (1000ms == 1s)
enum custom_keycodes { //Use Remap-Keys to load custom json
  SPAMARROW = QK_KB_0,
};

const uint16_t PROGMEM divide_combo[] = {KC_P4, KC_P5, COMBO_END};
const uint16_t PROGMEM multiply_combo[] = {KC_P8, KC_P9, COMBO_END};
const uint16_t PROGMEM plus_combo[] = {KC_P5, KC_P6, COMBO_END};
const uint16_t PROGMEM del_combo[] = {KC_BSPC, KC_P9, COMBO_END};
const uint16_t PROGMEM f2_combo[] = {KC_P7, KC_P8, COMBO_END};
combo_t key_combos[] = {
    COMBO(divide_combo, KC_PSLS),
    COMBO(multiply_combo, KC_PAST),
    COMBO(plus_combo, KC_PPLS),
    COMBO(del_combo, KC_DEL),
    COMBO(f2_combo, KC_F2),
};

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
        hsv = (HSV){HSV_CYAN};
	} else if (layer_state_cmp(layer_state, 3)) {
        hsv = (HSV){HSV_MAGENTA};
    } else {
        hsv = (HSV){HSV_SPRINGGREEN};
    }

    /*if (hsv.v > rgb_matrix_get_val()) {	//Limit max brightness of underglow, if desired
        hsv.v = rgb_matrix_get_val();
    }*/
    RGB rgb = hsv_to_rgb(hsv);

    for (uint8_t i = led_min; i < led_max; i++) {
        if (HAS_FLAGS(g_led_config.flags[i], 0x02)) { // 0x02 == LED_FLAG_UNDERGLOW
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
    return false;
}


void matrix_scan_user(void) {
	if (spam_arrow && timer_elapsed(spam_timer) >= spam_interval) {
		spam_timer = timer_read();	//Spam arrow code
		tap_code(KC_F24);
	}
	if(spam_arrow==1) { //Change LED colour on one underglow LED to indicate it is on
		rgb_matrix_set_color(15, 255, 135, 15);
		//rgb_matrix_set_color(15, 15, 255, 120);
	}
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) { //For keycode overrides
		case SPAMARROW: // Spam F24 or other keys like arrows
		  if (record->event.pressed) {
			spam_arrow ^= 1; 
			spam_timer = timer_read();

			if(spam_arrow==1) { //Change LED colour on underglow LED at max brightness
				rgb_matrix_set_color(15, 255, 135, 15);
				//rgb_matrix_set_color(15, 15, 255, 120);
				}
			else {
				rgb_matrix_mode(RGB_MATRIX_GRADIENT_UP_DOWN);
				}
		  }
		  return false;
	}
	return true;
}