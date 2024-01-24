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

/* USB Device descriptor parameter */
#define VENDOR_ID       0x414B // AK
#define PRODUCT_ID      0x0009 // 9e
#define DEVICE_VER      0x0001
#define MANUFACTURER    Atlantis
#define PRODUCT         A9e
#define DESCRIPTION     Keyboard

// key matrix settings
#define MATRIX_ROWS 4
#define MATRIX_COLS 12
#define MATRIX_ROW_PINS { F0, F1, F2, F3 }
#define MATRIX_COL_PINS { F5, F6, F7, A0, A1, A2, A3, A4, A5, B7, B6, B5 } //F5, F7, B7, B5 are unused on the MCU. Necessary for encoder key matrix.
#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE 6 //Default is 5

// NKRO Settings
#ifdef NKRO_ENABLE
	#define FORCE_NKRO //Force NKRO if enabled.
#endif

#define LOCKING_SUPPORT_ENABLE //Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap
#define LOCKING_RESYNC_ENABLE //Locking resynchronize hack

/* encoder pins */
#define ENCODERS_PAD_A { C0, C3, C5, C7, D1, D3, D5, D6, A7 } //Encoder pads ordered so on VIA mapping it is cw/ccw and up/down rotation orientation.
#define ENCODERS_PAD_B { C1, C2, C4, C6, D0, D2, D4, D7, A6 }
#define ENCODER_RESOLUTIONS { 4, 4, 4, 4, 4, 4, 4, 2, 2 } //Better control of individual encoders and encoder types.

//RGB Settings
#define RGB_DI_PIN E6
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_EFFECT_SNAKE_LENGTH 1 //Default 4
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
	L17,L16,L15,L14,L13,L12,L27,L26,L25,L24,L23,L22,L37,L36,L35,L34,L33,L32,L10,L20,L30,L21,L38,L47,L58,L49,L68,L77,L88,L79,L69,L39,L08,L07,L05,L03,L11,L31,L41,L46,L67, \
  }
//RGB LED logical order map
//Left encoder -> keys -> right encoders -> backlight
#define RGBLIGHT_LED_MAP LED_LAYOUT( \
	31,		32,		33,		34,	35,			\
3,	30,	4,	5,	6,	7,	8,	9,				\
0,	2,	10,	11,	12,	13,	14,	15,				\
1,	41,	16,	17,	18,	19,	20,	21,	25,	36,		\
	40,					39,	22,		24,		\
								23,			\
							38,	29,	37,		\
							26,		28,		\
								27			)
