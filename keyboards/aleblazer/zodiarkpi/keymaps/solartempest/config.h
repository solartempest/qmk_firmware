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

#pragma once

// Screen support
#define ST7789_NUM_DEVICES 1
#define QUANTUM_PAINTER_DISPLAY_TIMEOUT 80000
#define LCD_RST_PIN GP27
#define LCD_DC_PIN GP28
#define LCD_CS_PIN GP11
#define LCD_SPI_DIVISOR 8
#define QUANTUM_PAINTER_DEBUG
#define QUANTUM_PAINTER_SUPPORTS_NATIVE_COLORS true

// Cirque support, comment out if using two screens
#define SPLIT_POINTING_ENABLE
//#define POINTING_DEVICE_RIGHT
#define POINTING_DEVICE_LEFT
#define POINTING_DEVICE_ROTATION_180
#define CIRQUE_PINNACLE_POSITION_MODE CIRQUE_PINNACLE_ABSOLUTE_MODE
#define CIRQUE_PINNACLE_DIAMETER_MM 40
#define CIRQUE_PINNACLE_CURVED_OVERLAY
#define POINTING_DEVICE_CS_PIN GP11
#define CIRQUE_PINNACLE_TAP_ENABLE
#define POINTING_DEVICE_GESTURES_SCROLL_ENABLE
#define CIRQUE_PINNACLE_TAPPING_TERM 100


// #define RGB_MATRIX_DEFAULT_FLAGS LED_FLAG_ALL
// #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200
#define RGB_MATRIX_SLEEP
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_OLED_ENABLE
#define SPLIT_ACTIVITY_ENABLE

#define TAP_CODE_DELAY 10
#define TAPPING_TOGGLE 2 //Tap TT twice to toggle layer
#define TAPPING_TERM 100 //Tapping duration in ms, normally using 140