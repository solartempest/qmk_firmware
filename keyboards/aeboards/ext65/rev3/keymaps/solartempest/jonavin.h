
/* Copyright 2021 Jonavin Eng @Jonavin

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

// DEFINE MACROS
#define ARRAYSIZE(arr)  sizeof(arr)/sizeof(arr[0])


// LAYERS
enum custom_user_layers {
    _BASE,
    _FN1,
    _LOWER,
    _RAISE,
};

// KEYCODES
enum custom_user_keycodes {
  KC_00 = SAFE_RANGE,
  ENCFUNC,		//Encoder functions
  KC_WINLCK,	//Toggles Win key on and off
  RGB_NITE,		//Turns off all rgb but allow rgb indicators to work
  NMR,			//Move window to monitor on right
  NML			//Move window to monitor on left
};

#define KC_CAD	LALT(LCTL(KC_DEL))
#define KC_AF4	LALT(KC_F4)
#define KC_TASK	LCTL(LSFT(KC_ESC))


#ifdef TD_LSFT_CAPSLOCK_ENABLE
    // Tap Dance Definitions
    enum custom_tapdance {
        TD_LSFT_CAPSLOCK,
        TD_LSFT_CAPS_WIN
    };

    #define KC_LSFTCAPS     TD(TD_LSFT_CAPSLOCK)
    #define KC_LSFTCAPSWIN  TD(TD_LSFT_CAPS_WIN)
#else // regular Shift
    #define KC_LSFTCAPS    KC_LSFT
#endif // TD_LSFT_CAPSLOCK_ENABLE


#ifdef RGB_MATRIX_ENABLE
    void activate_rgb_nightmode (bool turn_on);
    bool get_rgb_nightmode(void);
#endif


// OTHER FUNCTION PROTOTYPE
void activate_numlock(bool turn_on);
