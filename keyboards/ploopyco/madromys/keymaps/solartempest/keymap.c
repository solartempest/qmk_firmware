/* Copyright 2023 Colin Lam (Ploopy Corporation)
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT( KC_BTN4, KC_BTN5, DRAG_SCROLL, KC_BTN2, KC_BTN1, LT(1, KC_BTN3) ),
    [1] = LAYOUT( RGB_MOD, RGB_RMOD, RGB_HUI, RGB_HUD, RGB_TOG, KC_NO)
};


layer_state_t layer_state_set_user(layer_state_t state) {
	switch (get_highest_layer(state)) { // Change all other LEDs based on layer state as well
		case 0:
			//rgblight_sethsv_noeeprom(115,200,255);	//pale-blue
			rgblight_sethsv_noeeprom(105,200,255);	//spring green
			break;
		case 1:
			rgblight_sethsv_noeeprom(160,255,255);	//blue-magenta
			break;
		case 2:
			//rgblight_sethsv_noeeprom(128,255,100);//blue-purple
			rgblight_sethsv_noeeprom(50,255,255);	//yellow
			break;
		case 3:
			rgblight_sethsv_noeeprom(215,255,255);	//magenta
			break;
	  }
    return state;
};