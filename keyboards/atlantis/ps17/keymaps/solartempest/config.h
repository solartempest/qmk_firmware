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

// Set number of layers for VIA (+30 per layer)
#define DYNAMIC_KEYMAP_LAYER_COUNT 4

#undef DEVICE_VER 
#define DEVICE_VER      0x0002 // Ver2
//#undef PRODUCT 
//#define PRODUCT         PS17

// For LED status indicators
#define LED_NUM_LOCK_PIN D0
#define LED_CAPS_LOCK_PIN D5
#define LED_SCROLL_LOCK_PIN D4
#define LED_PIN_ON_STATE 0

#define ENCODER_DIRECTION_FLIP