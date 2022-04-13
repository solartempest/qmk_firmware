/*
Copyright 2021 Spencer Deven <splitlogicdesign@gmail.com>
Copyright 2021 solartempest

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
#pragma once

#define MASTER_LEFT

#undef PRODUCT_ID
#define PRODUCT_ID      0xFF02 //Original was 0xF902. If the same ID is used, VIA will fail to reload saved layouts.

#undef MATRIX_ROWS
#undef MATRIX_COLS
#undef MATRIX_ROW_PINS
#undef MATRIX_COL_PINS
#undef ENCODER_RESOLUTION
#define MATRIX_ROWS 10
#define MATRIX_COLS 8 //Added extra column for rotary encoder VIA mapping.
#define MATRIX_ROW_PINS { C6, D7, E6, B4, F4 }
#define MATRIX_COL_PINS { F5, F6, F7, B1, B3, B2, B6, NO_PIN } //A virtual pin is needed for the encoder key matrix in via.
#define ENCODER_RESOLUTION 4 //Reduce encoder double-input issue.

#undef DEBOUNCE
#define DEBOUNCE 6 //Default is 5

// Tapping settings
#define TAP_CODE_DELAY 10
#define TAPPING_TOGGLE 2 //Tap TT twice to toggle layer
#define TAPPING_TERM 160 //Tapping duration in ms

// Disabled to save space
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
#define NO_ACTION_ONESHOT		//Save 244 bytes (-244).
#define NO_RESET				//Save 40 bytes (-40).
#define LAYER_STATE_8BIT		//For less than 8 bits worth of layers.
#undef LOCKING_SUPPORT_ENABLE	//For MX lock keys only.
#undef LOCKING_RESYNC_ENABLE	//For MX lock keys only.

#ifdef OLED_ENABLE
	#define OLED_DISPLAY_128X64
	#define OLED_TIMEOUT 80000			//80000 = 80secs, 120000 = 2mins in ms.
	#define SPLIT_OLED_ENABLE			//Synx on/off OLED state between halves (+100).
	#define OLED_LOGO					//Enable to print snakey custom logo on slave side (+108).
#endif

#ifdef RGBLIGHT_ENABLE
	#undef RGBLIGHT_ANIMATIONS // Very memory intensive (+2604)
	#define RGBLIGHT_EFFECT_STATIC_GRADIENT //Preferred RGB effect (+262)
	//#define RGBLIGHT_EFFECT_BREATHING  //Testing
	//#define RGBLIGHT_EFFECT_SNAKE //For testing LED order
	#define RGBLIGHT_SLEEP //Turn off LEDs when computer sleeping (+72)
#endif

// Pimoroni trackball settings
#ifdef POINTING_DEVICE_ENABLE
	//#define PIMORONI_TRACKBALL_INTERVAL_MS 6 //Default is 8ms
	#define POINTING_DEVICE_ROTATION_90
	#define PIMORONI_TRACKBALL_INVERT_Y
	#define PIMORONI_TRACKBALL_INVERT_X
#endif      

#ifdef VIA_ENABLE
	#define DYNAMIC_KEYMAP_LAYER_COUNT 5
#endif

#define D2SKATE_MACRO_ENABLE	//Enable Destiny 2 hunter skate macro (+224)
