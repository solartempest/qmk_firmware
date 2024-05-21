/*
Copyright 2023 Spencer Deven <splitlogicdesign@gmail.com>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

uint8_t led_min = 0;
uint8_t led_max = RGB_MATRIX_LED_COUNT;

const uint16_t PROGMEM enter_combo[] = {KC_LEFT_BRACKET, KC_RIGHT_BRACKET, COMBO_END};
combo_t key_combos[] = {
    COMBO(enter_combo, KC_ENTER),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
      MO(3), KC_A,  KC_S,    KC_D,    KC_F,    KC_G,  KC_MINS, KC_MUTE,     RGB_TOG, KC_EQL,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,  KC_GRV, KC_LBRC,      KC_RBRC, KC_DEL,KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
      KC_LCTL, KC_LALT, KC_LGUI, KC_F12, MO(1),  KC_SPC,   KC_ENT,    KC_ENT,   KC_SPC,  MO(2),    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),

	[1] = LAYOUT(
      _______, KC_F1, KC_F2, KC_F3, KC_F4,   KC_F5,                                       KC_F6,   KC_F7,   KC_F8,  KC_F9, KC_F10, KC_F11,
      KC_PSLS, KC_P7, KC_P8, KC_P9, _______, KC_NUM,                                      KC_NUM,  KC_PSLS, KC_P7, KC_P8, KC_P9, KC_F12,
      KC_CAPS, KC_P4, KC_P5, KC_P6, _______, _______, _______, _______,  _______,  _______, _______, _______, KC_P4, KC_P5, KC_P6, _______,
      _______, KC_P1, KC_P2, KC_P3, _______, _______, _______, _______,  _______, _______, _______, _______,  KC_P1, KC_P2, KC_P3, _______,
      _______, KC_P0, KC_PDOT, KC_PENT, _______,     _______,  _______,   _______,    _______,   _______,     KC_P0, KC_PDOT, KC_PENT, _______
      ),

	[2] = LAYOUT(
      _______, KC_F1, KC_F2, KC_F3, KC_F4,   KC_F5,                                       KC_F6,   KC_F7,   KC_F8,  KC_F9, KC_F10, KC_F11,
      KC_PSLS, KC_P7, KC_P8, KC_P9, _______, KC_NUM,                                      KC_NUM,   KC_PSLS, KC_P7, KC_P8, KC_P9, KC_F12,
      KC_CAPS, KC_P4, KC_P5, KC_P6, _______, _______, _______, _______,  _______,  _______, _______, _______, KC_P4, KC_P5, KC_P6, _______,
      _______, KC_P1, KC_P2, KC_P3, _______, _______, _______, _______,  _______, _______, _______, _______,  KC_P1, KC_P2, KC_P3, _______,
      _______, KC_P0, KC_PDOT, KC_PENT, _______,     _______,  _______,   _______,    _______,   _______,     KC_P0, KC_PDOT, KC_PENT, _______
      ),

	[3] = LAYOUT(
      QK_BOOT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
      _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, KC_F12,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_MOD, RGB_SPI, RGB_HUI, RGB_SAI, RGB_VAI,
      _______, _______, _______, _______, _______,      _______,     _______, _______,     _______,      RGB_RMOD, RGB_SPD, RGB_HUD, RGB_SAD, RGB_VAD
      )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),  ENCODER_CCW_CW(KC_PGDN, KC_PGUP)  },
    [1] =   { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [2] =   { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [3] =   { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  }
};
#endif

/*bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    for (uint8_t i = led_min; i < led_max; i++) {
        switch(get_highest_layer(layer_state|default_layer_state)) {
            case 3:
                rgb_matrix_set_color(i, 138,0,147);
                break;
            case 2:
                rgb_matrix_set_color(i, RGB_BLUE);
                break;
            case 1:
                rgb_matrix_set_color(i, 0,184,103);
                break;
            default:
                break;
        }
    }
    return false;
}*/

/*bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
	if (layer_state_cmp(layer_state, 1)) {
	rgb_matrix_sethsv_noeeprom(HSV_SPRINGGREEN);
	} else if (layer_state_cmp(layer_state, 2)) {
	rgb_matrix_sethsv_noeeprom(HSV_BLUE);
	} else if (layer_state_cmp(layer_state, 3)) {
	rgb_matrix_sethsv_noeeprom(HSV_MAGENTA);
    } else {
	rgb_matrix_sethsv_noeeprom(HSV_CHARTREUSE);
    }
    return false;
}*/

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    HSV hsv = {HSV_SPRINGGREEN};
	if (layer_state_cmp(layer_state, 1)) {
        hsv = (HSV){HSV_CHARTREUSE};
	} else if (layer_state_cmp(layer_state, 2)) {
        hsv = (HSV){HSV_BLUE};
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
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    return false;
}


void suspend_power_down_user(void) {
    rgb_matrix_disable_noeeprom();
}

void suspend_wakeup_init_user(void) {
    rgb_matrix_enable_noeeprom();
}