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
#define PRODUCT_ID      0x0021
#define DEVICE_VER      0x0001 // Ver1
#define MANUFACTURER    ATLANTIS
#define PRODUCT         AK21


// key matrix size 
#ifdef RGBLIGHT_ENABLE 
	#define MATRIX_ROWS 6
	#define MATRIX_COLS 4
#endif

#define MATRIX_ROW_PINS { B3, F1, F4, F5, F6, F7 }
#define MATRIX_COL_PINS { B2, F0, D6, D7 }
#define UNUSED_PINS

// COL2ROW or ROW2COL
#define DIODE_DIRECTION ROW2COL

// For LED status indicators
#define LED_NUM_LOCK_PIN E6
#define LED_PIN_ON_STATE 0

#define RGB_DI_PIN B0
#ifdef RGBLIGHT_ENABLE
	#define RGBLED_NUM 33 // 21 key + 12 underglow for RGBLIGHT
	#define RGBLIGHT_HUE_STEP 8
	#define RGBLIGHT_SAT_STEP 8
	#define RGBLIGHT_VAL_STEP 8
	#define RGBLIGHT_DEFAULT_VAL 40 // default brightness on clearing EEPROM
	#define RGBLIGHT_LIMIT_VAL 200 // brightness level max is 255
	#define RGBLIGHT_SLEEP //  if defined, RGB lighting off when host is sleeping
	#define RGBLIGHT_ANIMATIONS

	//RGB LED Conversion macro from physical array to electric array
	//First section is the LED matrix, second section is the electrical wiring order, and the third section is the desired mapping
	#define LED_LAYOUT( \
		     L01, L02, L03, L04, L05,  \
		L10, L11, L12, L13, L14, L15,  \
		L20, L21, L22, L23,      L25,  \
		L30, L31, L32, L33, L34, L35,  \
		L40, L41, L42, L43,      L45,  \
		     L51,      L53,      L55,  \
		L60,           L63,      L65 ) \
	  { \
	    L01,L02,L03,L05,L14,L13,L12,L11,L21,L22,L23,L34,L33,L32,L31,L41,L42,L43,L55,L53,L51,L60,L63,L65,L45,L35,L25,L04,L10,L20,L30,L40, \
	  }
	//RGB LED logical order map
	//Right->Left, Top->Bottom
	#define RGBLIGHT_LED_MAP LED_LAYOUT( \
		     4,  3,  2,  1,  0,  \
		10,  9,  8,  7,  6,  5,  \
		15, 14, 13, 12,     11,  \
		21, 20, 19, 18, 17, 16,  \
		26, 25, 24, 23,     22,  \
		    29,     28,     27,  \
		32,         31,     30 )
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define COMBO_COUNT 2 //Number of tap combos used
#define COMBO_TERM 300 //Default combo time is 200ms

#define TAPPING_TERM 200 //Tap dance time
