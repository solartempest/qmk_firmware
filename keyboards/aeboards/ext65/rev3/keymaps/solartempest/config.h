/* Copyright 2021 Jonavin Eng
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

#define TAPPING_TOGGLE 2 // TT set to two taps
#define TAPPING_TERM 180

// Handle GRAVESC combo keys
//#define GRAVE_ESC_ALT_OVERRIDE  //Always send Escape if Alt is pressed
//#define GRAVE_ESC_CTRL_OVERRIDE  //Always send Escape if Control is pressed

// NKRO Settings
#ifdef NKRO_ENABLE
	#define FORCE_NKRO //Force NKRO if enabled.
#endif

//RGB Settings
#ifdef RGB_MATRIX_ENABLE
    #define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_HUE_WAVE
    #define RGB_DISABLE_WHEN_USB_SUSPENDED
	#define RGB_DISABLE_TIMEOUT 300000 //300000ms = 5 minutes (Suspect the max timer is <5mins).
	
	#define RGB_MATRIX_KEYPRESSES	//Remove or keep effects not desired
	#undef ENABLE_RGB_MATRIX_SOLID_COLOR
	#undef ENABLE_RGB_MATRIX_ALPHAS_MODS
	#undef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
	#undef ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
	#undef ENABLE_RGB_MATRIX_BREATHING
	#undef ENABLE_RGB_MATRIX_BAND_SAT
	#undef ENABLE_RGB_MATRIX_BAND_VAL
	#undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
	#undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
	#undef ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
	#undef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
	#undef ENABLE_RGB_MATRIX_CYCLE_ALL
	#undef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
	#undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
	#undef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
	#undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN
	#undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
	#undef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
	#undef ENABLE_RGB_MATRIX_CYCLE_SPIRAL
	#undef ENABLE_RGB_MATRIX_DUAL_BEACON
	#undef ENABLE_RGB_MATRIX_RAINBOW_BEACON
	#undef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
	#undef ENABLE_RGB_MATRIX_RAINDROPS
	#undef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
	#undef ENABLE_RGB_MATRIX_HUE_BREATHING
	#undef ENABLE_RGB_MATRIX_HUE_PENDULUM
	#define ENABLE_RGB_MATRIX_HUE_WAVE	//Enabled
	#undef ENABLE_RGB_MATRIX_PIXEL_FRACTAL
	#undef ENABLE_RGB_MATRIX_PIXEL_RAIN
	#undef ENABLE_RGB_MATRIX_PIXEL_FLOW
	#undef ENABLE_RGB_MATRIX_PIXEL_FRACTAL
	#undef ENABLE_RGB_MATRIX_TYPING_HEATMAP
	#undef ENABLE_RGB_MATRIX_DIGITAL_RAIN
	#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
	#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE
	#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
	#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
	#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
	#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
	#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
	#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS	//Enabled
	#undef ENABLE_RGB_MATRIX_SPLASH
	#undef ENABLE_RGB_MATRIX_MULTISPLASH
	#undef ENABLE_RGB_MATRIX_SOLID_SPLASH
	#undef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#endif
