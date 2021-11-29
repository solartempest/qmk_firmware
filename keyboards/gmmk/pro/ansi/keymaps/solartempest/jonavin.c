
/* Copyright 2021 Jonavin Eng @Jonavin
   Copyright 2021 solartempest

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


#include QMK_KEYBOARD_H
#include "jonavin.h"


#ifdef TD_LSFT_CAPSLOCK_ENABLE
  // Tap once for shift, twice for Caps Lock but only if Win Key in not disabled
    void dance_LSFT_finished(qk_tap_dance_state_t *state, void *user_data) {
        if (state->count == 1 || keymap_config.no_gui) {
            register_code16(KC_LSFT);
        } else {
            register_code(KC_CAPS);
        }
    }

    void dance_LSFT_reset(qk_tap_dance_state_t *state, void *user_data) {
        if (state->count == 1 || keymap_config.no_gui) {
            unregister_code16(KC_LSFT);
        } else {
            unregister_code(KC_CAPS);
        }
    }

    qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for shift, twice for Caps Lock
        [TD_LSFT_CAPSLOCK] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
        [TD_LSFT_CAPS_WIN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_LSFT_finished, dance_LSFT_reset),
    };
#endif  // TD_LSFT_CAPSLOCK_ENABLE

// RGB NIGHT MODE
#ifdef RGB_MATRIX_ENABLE
    static bool rgb_nightmode = false;

    // Turn on/off NUM LOCK if current state is different
    void activate_rgb_nightmode (bool turn_on) {
        if (rgb_nightmode != turn_on) {
            rgb_nightmode = !rgb_nightmode;
        }
    }

    bool get_rgb_nightmode(void) {
        return rgb_nightmode;
    }
#endif // RGB_MATRIX_ENABLE


#if defined(ENCODER_ENABLE) && defined(ENCODER_DEFAULTACTIONS_ENABLE)       // Encoder Functionality
    #ifndef DYNAMIC_KEYMAP_LAYER_COUNT
        #define DYNAMIC_KEYMAP_LAYER_COUNT 4  //default in case this is not already defined elsewhere
    #endif
    #ifndef ENCODER_DEFAULTACTIONS_INDEX
        #define ENCODER_DEFAULTACTIONS_INDEX 0  // can select encoder index if there are multiple encoders
    #endif

uint8_t selected_layer = 0;

__attribute__((weak)) bool encoder_update_keymap(uint8_t index, bool clockwise) { return true; }

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (!encoder_update_keymap(index, clockwise)) { return false; }  //This is to override the default kb function and go to userspace
    if (index != ENCODER_DEFAULTACTIONS_INDEX) {return true;}  // exit if the index doesn't match
        if ( clockwise ) {
            if (get_mods() & MOD_BIT(KC_LSFT) ) { // If you are holding L shift, encoder changes layers
                if(selected_layer  < (DYNAMIC_KEYMAP_LAYER_COUNT - 1)) {
                    selected_layer ++;
                    layer_move(selected_layer);
                }
            } else if (get_mods() & MOD_BIT(KC_RSFT) ) { // If you are holding R shift, Page up
                unregister_mods(MOD_BIT(KC_RSFT));
                register_code(KC_PGDN);
                register_mods(MOD_BIT(KC_RSFT));
            } else if (get_mods() & MOD_BIT(KC_LCTL)) {  // if holding Left Ctrl, navigate next word
                tap_code16(LCTL(KC_RGHT));
            } else if (get_mods() & MOD_BIT(KC_LALT)) {  // if holding Left Alt, move window to right monitor
                unregister_mods(MOD_BIT(KC_LALT));
				register_code(KC_LSFT);
				register_code(KC_LWIN);
				register_code(KC_RIGHT);
				unregister_code(KC_RIGHT);
				unregister_code(KC_LWIN);
				unregister_code(KC_LSFT);
                register_mods(MOD_BIT(KC_LALT));
            } else  {
                switch (selected_layer) {
                default:
                    tap_code(KC_VOLU);       // Otherwise it just changes volume
                    break;
                }
            }
        } else {
            if (get_mods() & MOD_BIT(KC_LSFT) ) {
                if (selected_layer  > 0) {
                    selected_layer --;
                    layer_move(selected_layer);
                }
            } else if (get_mods() & MOD_BIT(KC_RSFT) ) {
                unregister_mods(MOD_BIT(KC_RSFT));
                register_code(KC_PGUP);
                register_mods(MOD_BIT(KC_RSFT));
            } else if (get_mods() & MOD_BIT(KC_LCTL)) {  // if holding Left Ctrl, navigate previous word
                tap_code16(LCTL(KC_LEFT));
            } else if (get_mods() & MOD_BIT(KC_LALT)) {  // if holding Left Alt, move window to left monitor
                unregister_mods(MOD_BIT(KC_LALT));
				register_code(KC_LSFT);
				register_code(KC_LWIN);
				register_code(KC_LEFT);
				unregister_code(KC_LEFT);
				unregister_code(KC_LWIN);
				unregister_code(KC_LSFT);
                register_mods(MOD_BIT(KC_LALT));
            } else {
                switch (selected_layer) {
                default:
                    tap_code(KC_VOLD);
                    break;
                }
            }
        }

        return true;
    }
#endif // ENCODER_ENABLE


// PROCESS KEY CODES
__attribute__ ((weak))  bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keymap(keycode, record)) { return false; }
    switch (keycode) {
		case KC_00:
			if (record->event.pressed) {
				// when keycode KC_00 is pressed
				SEND_STRING("00");
			} else unregister_code16(keycode);
			break;
		case KC_WINLCK:
			if (record->event.pressed) {
				keymap_config.no_gui = !keymap_config.no_gui; //toggle status
			} else  unregister_code16(keycode);
			break;

		#ifdef RGB_MATRIX_ENABLE
			case RGB_NITE:
				if(record->event.pressed) {
					rgb_nightmode = !rgb_nightmode;
				} else  unregister_code16(keycode);
				break;
		#endif // RGB_MATRIX_ENABLE
		
		case NMR:	//Move window to next monitor on right
		  if (record->event.pressed) {
			register_code(KC_LSFT);
			register_code(KC_LWIN);
			register_code(KC_RIGHT);
			unregister_code(KC_RIGHT);
			unregister_code(KC_LWIN);
			unregister_code(KC_LSFT);
		  }
		  return true;
		case NML:	//Move window to next monitor on left
		  if (record->event.pressed) {
			register_code(KC_LSFT);
			register_code(KC_LWIN);
			register_code(KC_LEFT);
			unregister_code(KC_LEFT);
			unregister_code(KC_LWIN);
			unregister_code(KC_LSFT);
		  }
		  return true;
		
		default:
			if (record->event.pressed) {
				#ifdef RGB_MATRIX_ENABLE
					rgb_matrix_enable_noeeprom();
				#endif
			}
			break;
	}
	return true;
};


// Turn on/off NUM LOCK if current state is different
void activate_numlock(bool turn_on) {
    if (IS_HOST_LED_ON(USB_LED_NUM_LOCK) != turn_on) {
        tap_code(KC_NUMLOCK);
    }
}


// INITIAL STARTUP
__attribute__ ((weak)) void keyboard_post_init_keymap(void) {}

void keyboard_post_init_user(void) {
    keyboard_post_init_keymap();
    #ifdef STARTUP_NUMLOCK_ON
        activate_numlock(true); // turn on Num lock by default so that the numpad layer always has predictable results
    #endif // STARTUP_NUMLOC_ON
}