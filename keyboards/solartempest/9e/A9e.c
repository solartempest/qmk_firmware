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

#include "A9e.h"

/*	#define RGBLIGHT_LED_MAP LED_LAYOUT( \
		31,		32,		33,		34,	35,			\
	1,	30,	4,	5,	6,	7,	8,	9,				\
	0,	3,	10,	11,	12,	13,	14,	15,				\
	2,	41,	16,	17,	18,	19,	20,	21,	23,	36,		\
		40,					39,	22,		25,		\
									24,			\
								38,	27,	37,		\
								26,		29,		\
									28			)*/
// 		E2	Keys Row 1	E4	E5
// E1		Keys Row 2	  E6
// 		E3	Keys Row 3
//			 E8   E9	  E7

#ifdef RGB_MATRIX_ENABLE //Add in addressable LED underglow support with physical locations
	led_config_t g_led_config = { {
		//Key matrix to LED index
		{		36,				35,				34,				33,		32,			},
		{18,	37,		5,		4,		3,		2,		1,		0,					},
		{19,	21,		11,		10,		9,		8,		7,		6,					},
		{20,	38,		17,		16,		15,		14,		13,		12,		22,		31,	},
		{		39,										40,		23,				25,	},
		{																24,			},
		{														41,		26,		30,	},
		{														27,				29, },
		{																28, NO_LED, NO_LED, NO_LED, }
	}, {
	  // LED Key Index to Physical Position, calculated with Plot Digitizer and scaled PCB Image with center at {110,110}
		{150,98},{132,98},{116,98},{100,98},{84,98},{60,98},
		{150,80},{132,80},{116,80},{100,80},{84,80},{60,80},
		{150,64},{132,64},{116,64},{100,64},{84,64},{60,64},
		
		{16,85},{7,76},{16,66},{24,76},  {192,74},{184,62},
		{192,52},{202,62},  {192,30},{184,20},{192,8},{202,19},
		
		{209,32},{211,71},{191,105},{141,105},{101,104},{76,104},
		{52,98},{30,89},{30,63},{52,50},{141,44},{181,32}
	}, { 									// LED Index to Flag.
	  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,	// 4 for 18-key backlight.
      1,1,1,1,1,1,1,1,1,1,1,1,				// 1 for 3*4LED large rotary encoders.
	  2,2,2,2,2,2,2,2,2,2,2,2 				// 2 for 12-case underglow.
	} };
#endif
