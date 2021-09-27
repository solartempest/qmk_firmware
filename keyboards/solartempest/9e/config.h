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

#ifndef CONFIG_H
	#define CONFIG_H

	#include "config_common.h"

	/* USB Device descriptor parameter */
	#define VENDOR_ID       0x414B // AK
	#define PRODUCT_ID      0x0009 // 9e
	#define DEVICE_VER      0x0001
	#define MANUFACTURER    Atlantis
	#define PRODUCT         A9e
	#define DESCRIPTION     Keyboard

	/* key matrix size */
	#define MATRIX_ROWS 4
	#define MATRIX_COLS 12

	/* key matrix pins */
	#define MATRIX_ROW_PINS { F0, F1, F2, F3 }
	#define MATRIX_COL_PINS { F5, F6, F7, A0, A1, A2, A3, A4, A5, B7, B6, B5 } //F5, F7, B7, B5 are unused on the MCU. They are needed for the encoder key matrix.
	#define UNUSED_PINS

	/* encoder pins */
	#define ENCODERS_PAD_A { C0, C3, C5, C7, D1, D3, D5, D6, A7 } //Encoder pads ordered so on VIA mapping it is cw/ccw and up/down rotation orientation.
	#define ENCODERS_PAD_B { C1, C2, C4, C6, D0, D2, D4, D7, A6 }
	#define ENCODER_RESOLUTIONS { 4, 4, 4, 4, 4, 4, 4, 2, 2 } //Better control of individual encoders and encoder types.
	//#define ENCODER_RESOLUTION 4

	/* COL2ROW or ROW2COL */
	#define DIODE_DIRECTION COL2ROW

	/* Set 0 if debouncing isn't needed */
	#define DEBOUNCE 5

	/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
	#define LOCKING_SUPPORT_ENABLE

	/* Locking resynchronize hack */
	#define LOCKING_RESYNC_ENABLE


	#define RGB_DI_PIN E6
	#ifdef RGB_DI_PIN
		#define RGBLIGHT_ANIMATIONS
		#define RGBLIGHT_HUE_STEP 8
		#define RGBLIGHT_SAT_STEP 8
		#define RGBLIGHT_VAL_STEP 8
		#define RGBLIGHT_LAYERS
		#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
		#define RGBLIGHT_SLEEP // 18 keys, 9*3 encoders = 45 keys
		#define RGBLED_NUM 42 // 18 keys + 12 encoders + 12 underglow for RGBLIGHT
		#define RGBLIGHT_LIMIT_VAL 180
		
		//RGB LED Conversion macro from physical array to electric array
		//First section is the LED matrix, second section is the electrical wiring order, and the third section is the desired mapping
		#define LED_LAYOUT( \
					L01,			L03,			L05,			L07,	L08,		 \
			L10,	L11,	L12,	L13,	L14,	L15,	L16,	L17,				 \
			L20,	L21,	L22,	L23,	L24,	L25,	L26,	L27,				 \
			L30,	L31,	L32,	L33,	L34,	L35,	L36,	L37,	L38,	L39, \
					L41,									L46,	L47,			L49, \
																			L58,		 \
																	L67,	L68,	L69, \
																	L77,			L79, \
																			L88			)\
		  { \
			L17,L16,L15,L14,L13,L12,L27,L26,L25,L24,L23,L22,L37,L36,L35,L34,L33,L32,L10,L20,L30,L21,L38,L47,L58,L49,L68,L77,L88,L79,L69,L39,L08,L07,L05,L03,L01,L11,L31,L41,L46,L67, \
		  }
		//RGB LED logical order map
		//Left encoder -> keys -> right encoders -> backlight
		#define RGBLIGHT_LED_MAP LED_LAYOUT( \
			31,		32,		33,		34,	35,			\
		1,	30,	4,	5,	6,	7,	8,	9,				\
		0,	3,	10,	11,	12,	13,	14,	15,				\
		2,	41,	16,	17,	18,	19,	20,	21,	23,	36,		\
			40,					39,	22,		25,		\
										24,			\
									38,	27,	37,		\
									26,		29,		\
										28			)
	#endif
	
	#ifdef RGB_MATRIX_ENABLE // For dynamic RGB Matrix effects
		#define DRIVER_LED_TOTAL 42 // The number of LEDs connected for matrix, 18 keys + 12 encoders + 12 underglow
		#define RGB_MATRIX_CENTER { 110, 110 };
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

	
#endif
