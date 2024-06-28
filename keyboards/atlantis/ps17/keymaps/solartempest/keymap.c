// Copyright 2023 mjbogusz (@mjbogusz)
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Default layer: numpad + volume control
    [0] = LAYOUT(
                 KC_MUTE,
        TO(1),   KC_PSLS, KC_PAST, KC_PMNS,
        KC_KP_7, KC_KP_8, KC_KP_9, KC_PPLS,
        KC_KP_4, KC_KP_5, KC_KP_6,
        KC_KP_1, KC_KP_2, KC_KP_3, KC_PENT,
        KC_KP_0,          KC_PDOT
    ),
    [1] = LAYOUT(
                 RGB_MOD,
        TO(2),   KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,          KC_TRNS
    ),
    [2] = LAYOUT(
                 KC_TRNS,
        TO(3),   KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,          KC_TRNS
    ),
    [3] = LAYOUT(
                 KC_TRNS,
        TO(0),   KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,          KC_TRNS
    ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(RGB_HUI, RGB_HUD) },
    [2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [3] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
#endif


bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
      HSV hsv = {HSV_CHARTREUSE};
	if (layer_state_cmp(layer_state, 1)) {
		hsv = (HSV){HSV_SPRINGGREEN};
	} else if (layer_state_cmp(layer_state, 2)) {
        hsv = (HSV){HSV_BLUE};
	} else if (layer_state_cmp(layer_state, 3)) {
        hsv = (HSV){HSV_MAGENTA};
    } else {
        hsv = (HSV){HSV_CHARTREUSE};
    }

    if (hsv.v > rgb_matrix_get_val()) {	//Limit max brightness of underglow, if desired
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
				//rgb_matrix_mode(RGB_MATRIX_GRADIENT_UP_DOWN);
				}
		  }
		  return false;
	}
	return true;
}