/* Copyright
 *   2021 solartempest
 *   2021 QMK
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

#pragma once
#include "config_common.h"

// USB Device descriptor parameter 
#define VENDOR_ID       0x414B // "AK"
#define PRODUCT_ID      0x0015
#define DEVICE_VER      0x0002 // Ver2
#define MANUFACTURER    ATLANTIS
#define PRODUCT         PS17

//#define ENCODER_RESOLUTION 2 // default is 4

// key matrix size 
#ifdef RGBLIGHT_ENABLE 
	#define MATRIX_ROWS 6
#endif
#ifdef RGB_MATRIX_ENABLE 
	#define MATRIX_ROWS 11 //Numpad actually has 6 rows. 5 rows were added for underglow RGB matrix to work together
#endif
#define MATRIX_COLS 4
#define MATRIX_ROW_PINS { F0, B4, B5, B6, C6, C7 } //Rotary encoder SPST is on F0,F7
#define MATRIX_COL_PINS { F6, F7, D3, D6 }
#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE 5 //Default is 5, 0 if not needed.

// Encoder matrix
#define ENCODERS_PAD_A { D1 }
#define ENCODERS_PAD_B { D2 }

// NKRO Settings
#ifdef NKRO_ENABLE
	#define FORCE_NKRO //Force NKRO if enabled.
#endif

// Combo settings
#ifdef COMBO_ENABLE
	#define COMBO_COUNT 6 //Number of tap combos used
	#define COMBO_TERM 400 //Default combo time is 200ms
#endif

// Tapping settings
#define TAP_CODE_DELAY 10
#define TAPPING_TOGGLE 2 //Tap TT twice to toggle layer
#define TAPPING_TERM 160 //Tapping duration in ms

// For LED status indicators
#define LED_NUM_LOCK_PIN D0
#define LED_CAPS_LOCK_PIN D5
#define LED_SCROLL_LOCK_PIN D4
#define LED_PIN_ON_STATE 0

#define RGB_DI_PIN B7
#ifdef RGBLIGHT_ENABLE
	#define RGBLED_NUM 28 //17 key + 11 underglow for RGBLIGHT
	#define RGBLIGHT_HUE_STEP 8
	#define RGBLIGHT_SAT_STEP 8
	#define RGBLIGHT_VAL_STEP 8
	#define RGBLIGHT_DEFAULT_VAL 40 //Default brightness on clearing EEPROM
	#define RGBLIGHT_LIMIT_VAL 180 //Brightness level max is 255
	//#define RGBLIGHT_LAYERS //Enable layer light indicators. Not required as layer_state_set_user is used instead.
	//#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
	#define RGBLIGHT_SLEEP  	//Turn off LEDs when computer sleeping (+72)
	#define RGBLIGHT_ANIMATIONS //Very memory intensive (+2604)

	//RGB LED Conversion macro from physical array to electric array
	//First section is the LED matrix, second section is the electrical wiring order, and the third section is the desired mapping
	#define LED_LAYOUT( \
		L00,                     L05,  \
		L10,                     L15,  \
		L20, L21, L22, L23, L24, L25,  \
		     L31, L32, L33, L34,       \
		L40, L41, L42, L43,      L45,  \
		     L51, L52, L53, L54,       \
		L60, L61, L62, L63,      L65 ) \
	  { \
		L21,L22,L23,L24,L31,L32,L33,L34,L41,L42,L43,L51,L52,L53,L54,L61,L63,L60,L40,L20,L10,L00,L05,L15,L25,L45,L65,L62, \
	  }
	//RGB LED logical order map
	//Right->Left, Top->Bottom
	#define RGBLIGHT_LED_MAP LED_LAYOUT( \
		1,                  0, \
		3,                  2, \
		9,   8,  7,  6,  5, 4, \
		    13, 12, 11, 10,    \
		18, 17, 16, 15,    14, \
		    22, 21, 20, 19,    \
		27, 26, 25, 24,    23  )
#endif

#ifdef RGB_MATRIX_ENABLE // For reactive RGB Matrix effects
	#define DRIVER_LED_TOTAL 28 // The number of LEDs connected for matrix, 17 key + 11 underglow
	#define RGB_MATRIX_CENTER { 126, 126 };
	#define RGB_MATRIX_KEYPRESSES
	#define DISABLE_RGB_MATRIX_ALPHAS_MODS //Remove effects not desired
	#define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
	#define DISABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
	#define DISABLE_RGB_MATRIX_BAND_SAT
	#define DISABLE_RGB_MATRIX_BAND_VAL
	#define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
	#define DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
	#define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
	#define DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL
	#define DISABLE_RGB_MATRIX_CYCLE_ALL
	#define DISABLE_RGB_MATRIX_CYCLE_OUT_IN
	#define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
	#define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
	#define DISABLE_RGB_MATRIX_CYCLE_PINWHEEL
	#define DISABLE_RGB_MATRIX_CYCLE_SPIRAL
	#define DISABLE_RGB_MATRIX_DUAL_BEACON
	#define DISABLE_RGB_MATRIX_RAINBOW_BEACON
	#define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
	#define DISABLE_RGB_MATRIX_RAINDROPS
	#define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
	#define DISABLE_RGB_MATRIX_HUE_BREATHING
	#define DISABLE_RGB_MATRIX_HUE_PENDULUM
	#define DISABLE_RGB_MATRIX_HUE_WAVE
	#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
	#define DISABLE_RGB_MATRIX_SOLID_REACTIVE
	#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
	#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
	#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
	#define DISABLE_RGB_MATRIX_SPLASH
	#define DISABLE_RGB_MATRIX_MULTISPLASH
	#define DISABLE_RGB_MATRIX_SOLID_SPLASH
	#define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH
#endif
