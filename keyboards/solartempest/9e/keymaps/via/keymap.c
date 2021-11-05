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

#ifdef RGBLIGHT_ENABLE
	extern rgblight_config_t rgblight_config; // To pull layer status for RGBLIGHT
	
	bool is_encoder1_rotate = false; // For encoder animated LEDs
	bool is_encoder6_rotate = false;
	bool is_encoder7_rotate = false;
	bool encoder_effect = false;
	uint16_t encoder_timer = 0;
	uint16_t encoder_interval = 500;
#endif


bool is_alt_tab_active = false; // Super Alt Tab Code
uint16_t alt_tab_timer = 0;

bool is_stretch_active = false; // Stretch Timer Code
bool is_stretch_time = false;
uint32_t stretch_timer = 0;

#ifdef VIA_ENABLE
	enum custom_keycodes { //Use USER 00 instead of SAFE_RANGE for Via. VIA json must include the custom keycode.
	  ATABF = USER00,	//Alt tab forwards
	  ATABR,			//Alt tab reverse
	  NMR,				//Move window to monitor on right
	  NML,				//Move window to monitor on left
	  STRT				//Stretch Timer
	};
#else
	enum custom_keycodes { //Use USER 00 instead of SAFE_RANGE for Via. VIA json must include the custom keycode.
	  ATABF = SAFE_RANGE,	//Alt tab forwards
	  ATABR,			//Alt tab reverse
	  NMR,				//Move window to monitor on right
	  NML,				//Move window to monitor on left
	  STRT				//Stretch Timer
	};
#endif


//Keymap physical layout as follows:
// 		E2	Keys Row 1	E4	E5
// E1		Keys Row 2	  E6
// 		E3	Keys Row 3
//			 E8   E9	  E7
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
		KC_LEFT, KC__MUTE, KC_RIGHT,							//Rotary Encoder 1
		TO(1), TO(2), TO(3), KC_P7, KC_P8, KC_P9,				//Keys Row 1
		RGB_VAD, KC_SPACE, RGB_VAI, 							//Rotary Encoder 4
		RGB_MODE_REVERSE, RGB_TOG, RGB_MODE_FORWARD,			//Rotary Encoder 2
		KC_CAPS, KC_SLCK, KC_NLCK, KC_P4, KC_P5, KC_P6,			//Keys Row 2
		RGB_HUD, A(KC_F4), RGB_HUI, 							//Rotary Encoder 5
		ATABR, KC_MSTP, ATABF,									//Rotary Encoder 3
		KC_WREF, KC_MYCM, KC_P0, KC_P1, KC_P2, KC_P3,			//Keys Row 3
		KC_MS_WH_UP, C(KC_W), KC_MS_WH_DOWN, 					//Rotary Encoder 6
		C(S(KC_TAB)), KC_HOME, C(KC_TAB),						//Rotary Encoder 8
		C(KC_PMNS), KC__MUTE, C(KC_PPLS),						//Rotary Encoder 9
		C(S(KC_TAB)), C(KC_T), C(KC_TAB)						//Rotary Encoder 7
	),
	[1] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 1
		TO(0), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,		//Keys Row 1
		KC_TRNS, KC_TRNS, KC_TRNS, 								//Rotary Encoder 4
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 2
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,	//Keys Row 2
		KC_TRNS, KC_TRNS, KC_TRNS, 								//Rotary Encoder 5
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 3
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,	//Keys Row 3
		KC_TRNS, KC_TRNS, KC_TRNS, 								//Rotary Encoder 6
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 8
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 9
		KC_TRNS, KC_TRNS, KC_TRNS								//Rotary Encoder 7
	),
	[2] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 1
		TO(0), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,		//Keys Row 1
		KC_TRNS, KC_TRNS, KC_TRNS, 								//Rotary Encoder 4
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 2
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,	//Keys Row 2
		KC_TRNS, KC_TRNS, KC_TRNS, 								//Rotary Encoder 5
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 3
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,	//Keys Row 3
		KC_TRNS, KC_TRNS, KC_TRNS, 								//Rotary Encoder 6
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 8
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 9
		KC_TRNS, KC_TRNS, KC_TRNS								//Rotary Encoder 7
	),
	[3] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 1
		TO(0), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,		//Keys Row 1
		KC_TRNS, KC_TRNS, KC_TRNS, 								//Rotary Encoder 4
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 2
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,	//Keys Row 2
		KC_TRNS, KC_TRNS, KC_TRNS, 								//Rotary Encoder 5
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 3
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,	//Keys Row 3
		KC_TRNS, KC_TRNS, KC_TRNS, 								//Rotary Encoder 6
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 8
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 9
		KC_TRNS, KC_TRNS, KC_TRNS								//Rotary Encoder 7
	),
	[4] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 1
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,	//Keys Row 1
		KC_TRNS, KC_TRNS, KC_TRNS, 								//Rotary Encoder 4
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 2
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,	//Keys Row 2
		KC_TRNS, KC_TRNS, KC_TRNS, 								//Rotary Encoder 5
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 3
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,	//Keys Row 3
		KC_TRNS, KC_TRNS, KC_TRNS, 								//Rotary Encoder 6
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 8
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 9
		KC_TRNS, KC_TRNS, KC_TRNS								//Rotary Encoder 7
	),
	[5] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 1
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,	//Keys Row 1
		KC_TRNS, KC_TRNS, KC_TRNS, 								//Rotary Encoder 4
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 2
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,	//Keys Row 2
		KC_TRNS, KC_TRNS, KC_TRNS, 								//Rotary Encoder 5
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 3
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,	//Keys Row 3
		KC_TRNS, KC_TRNS, KC_TRNS, 								//Rotary Encoder 6
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 8
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 9
		KC_TRNS, KC_TRNS, KC_TRNS								//Rotary Encoder 7
	),
	[6] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 1
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,	//Keys Row 1
		KC_TRNS, KC_TRNS, KC_TRNS, 								//Rotary Encoder 4
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 2
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,	//Keys Row 2
		KC_TRNS, KC_TRNS, KC_TRNS, 								//Rotary Encoder 5
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 3
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,	//Keys Row 3
		KC_TRNS, KC_TRNS, KC_TRNS, 								//Rotary Encoder 6
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 8
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 9
		KC_TRNS, KC_TRNS, KC_TRNS								//Rotary Encoder 7
	),
	[7] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 1
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,	//Keys Row 1
		KC_TRNS, KC_TRNS, KC_TRNS, 								//Rotary Encoder 4
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 2
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,	//Keys Row 2
		KC_TRNS, KC_TRNS, KC_TRNS, 								//Rotary Encoder 5
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 3
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,	//Keys Row 3
		KC_TRNS, KC_TRNS, KC_TRNS, 								//Rotary Encoder 6
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 8
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 9
		KC_TRNS, KC_TRNS, KC_TRNS								//Rotary Encoder 7
	),
	[8] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 1
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,	//Keys Row 1
		KC_TRNS, KC_TRNS, KC_TRNS, 								//Rotary Encoder 4
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 2
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,	//Keys Row 2
		KC_TRNS, KC_TRNS, KC_TRNS, 								//Rotary Encoder 5
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 3
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,	//Keys Row 3
		KC_TRNS, KC_TRNS, KC_TRNS, 								//Rotary Encoder 6
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 8
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 9
		KC_TRNS, KC_TRNS, KC_TRNS								//Rotary Encoder 7
	),
	[9] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 1
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,	//Keys Row 1
		KC_TRNS, KC_TRNS, KC_TRNS, 								//Rotary Encoder 4
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 2
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,	//Keys Row 2
		KC_TRNS, KC_TRNS, KC_TRNS, 								//Rotary Encoder 5
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 3
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,	//Keys Row 3
		KC_TRNS, KC_TRNS, KC_TRNS, 								//Rotary Encoder 6
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 8
		KC_TRNS, KC_TRNS, KC_TRNS,								//Rotary Encoder 9
		KC_TRNS, KC_TRNS, KC_TRNS								//Rotary Encoder 7
	),
};


void matrix_init_user(void) {
}

void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }

  
  #ifdef RGBLIGHT_ENABLE //Add rotation animations underneath rotary encoders when turning
	if (!encoder_effect && is_encoder1_rotate) { //Turn on the effect for encoder 1
		rgblight_set_effect_range(0, 4);
		rgblight_mode_noeeprom(RGBLIGHT_MODE_SNAKE);
		is_encoder1_rotate = false;
		encoder_effect = true;
	} else if (!encoder_effect && is_encoder6_rotate) { //Turn on the effect for encoder 6
		rgblight_set_effect_range(22, 4);
		rgblight_mode_noeeprom(RGBLIGHT_MODE_SNAKE);
		is_encoder6_rotate = false;
		encoder_effect = true;
	} else if (!encoder_effect && is_encoder7_rotate) { //Turn on the effect for encoder 7
		rgblight_set_effect_range(26, 4);
		rgblight_mode_noeeprom(RGBLIGHT_MODE_SNAKE);
		is_encoder7_rotate = false;
		encoder_effect = true;
	} else if (!is_encoder1_rotate && !is_encoder6_rotate && !is_encoder7_rotate && timer_elapsed(encoder_timer) > encoder_interval) { //Turn off the animated LED effect
		if(encoder_effect){
			rgblight_set_effect_range(0, 42);
			rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_GRADIENT+8);
			if(is_stretch_time){
				rgblight_sethsv_at(0,230,100,40); //Set LED to orange to indicate timer is on
			}
		}
		is_encoder1_rotate = false;
		is_encoder6_rotate = false;
		is_encoder7_rotate = false;
		encoder_effect = false;
	  } else {
		is_encoder1_rotate = false;	//Wait until encoder is turned again
		is_encoder6_rotate = false;
		is_encoder7_rotate = false;
	  }
  #endif
    
  #ifdef RGBLIGHT_ENABLE //Stretch timer code
	  if (is_stretch_active && !is_stretch_time) {
		if (timer_elapsed(stretch_timer) > 2700000) { //Change RGB after 5s (Configurable. Test for 5s. 45 minutes is 2,700,000. 1 hour is 3,600,000)
		  rgblight_set_effect_range(0, 42);
		  rgblight_mode_noeeprom(RGBLIGHT_MODE_SNAKE);
		  is_stretch_time = true;
		}
	  }
  #endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) { //For super alt tab keycodes
		case ATABF:	//Alt tab forwards
		  if (record->event.pressed) {
			if (!is_alt_tab_active) {
			  is_alt_tab_active = true;
			  register_code(KC_LALT);
			}
			alt_tab_timer = timer_read();
			register_code(KC_TAB);
		  } else {
			unregister_code(KC_TAB);
		  }
		  return true;
		case ATABR:	//Alt tab reverse
		  if (record->event.pressed) {
			if (!is_alt_tab_active) {
			  is_alt_tab_active = true;
			  register_code(KC_LALT);
			}
			alt_tab_timer = timer_read();
			register_code(KC_LSHIFT);
			register_code(KC_TAB);
		  } else {
			unregister_code(KC_LSHIFT);
			unregister_code(KC_TAB);
		  }
		  return true;
		  
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
		  
		case STRT:	//Stretch timer
		  if (record->event.pressed) {
			is_stretch_active ^= 1;
			stretch_timer = timer_read();
			//rgblight_sethsv_at(75,215,80,41);
			if(is_stretch_time==1) { //Check if it is time to stretch, then dismiss the animation.
				rgblight_set_effect_range(0, 42);
				rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_GRADIENT+8);
				rgblight_sethsv_at(0,230,100,40); //Set LED to orange to indicate timer is on
				is_stretch_active = 1;
				is_stretch_time = 0;
				}
			else if(is_stretch_active==1) {
				rgblight_set_effect_range(0, 42);
				rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_GRADIENT+8);
				rgblight_sethsv_at(0,230,100,40); //Set LED to orange to indicate timer is on
				is_stretch_time = 0;
				}
			else {
				rgblight_set_effect_range(0, 42);
				rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_GRADIENT+8); //Set back to layer colours
				is_stretch_time = 0;
				}
		  }
		  return false;
	}
	return true;
}


bool encoder_update_user(uint8_t index, bool clockwise) 
{
    if (index == 0) { /* 1 encoder */
        if (clockwise) {
        	action_exec((keyevent_t){.key = (keypos_t){.row = 0, .col = 0}, .pressed = true, .time = (timer_read() | 1)  /* time should not be 0 */});  
        	action_exec((keyevent_t){.key = (keypos_t){.row = 0, .col = 0}, .pressed = false, .time = (timer_read() | 1)  /* time should not be 0 */});
			is_encoder1_rotate = true;  
			encoder_timer = timer_read();
        	} 
        	else {
        	action_exec((keyevent_t){.key = (keypos_t){.row = 0, .col = 2}, .pressed = true, .time = (timer_read() | 1)  /* time should not be 0 */});
        	action_exec((keyevent_t){.key = (keypos_t){.row = 0, .col = 2}, .pressed = false, .time = (timer_read() | 1)  /* time should not be 0 */});
			is_encoder1_rotate = true;  
			encoder_timer = timer_read();
            }
    }
    else if (index == 1) { /* 2 encoder */
        if (clockwise) {
        	action_exec((keyevent_t){.key = (keypos_t){.row = 1, .col = 0}, .pressed = true, .time = (timer_read() | 1)  /* time should not be 0 */});  
        	action_exec((keyevent_t){.key = (keypos_t){.row = 1, .col = 0}, .pressed = false, .time = (timer_read() | 1)  /* time should not be 0 */});
        	} 
        	else {
        	action_exec((keyevent_t){.key = (keypos_t){.row = 1, .col = 2}, .pressed = true, .time = (timer_read() | 1)  /* time should not be 0 */});
        	action_exec((keyevent_t){.key = (keypos_t){.row = 1, .col = 2}, .pressed = false, .time = (timer_read() | 1)  /* time should not be 0 */});  
            }
    }
    else if (index == 2) { /* 3 encoder */
        if (clockwise) {
        	action_exec((keyevent_t){.key = (keypos_t){.row = 2, .col = 0}, .pressed = true, .time = (timer_read() | 1)  /* time should not be 0 */});  
        	action_exec((keyevent_t){.key = (keypos_t){.row = 2, .col = 0}, .pressed = false, .time = (timer_read() | 1)  /* time should not be 0 */});
        	} 
        	else {
        	action_exec((keyevent_t){.key = (keypos_t){.row = 2, .col = 2}, .pressed = true, .time = (timer_read() | 1)  /* time should not be 0 */});
        	action_exec((keyevent_t){.key = (keypos_t){.row = 2, .col = 2}, .pressed = false, .time = (timer_read() | 1)  /* time should not be 0 */});  
            }
    }
    else if (index == 3) { /* 4 encoder */
        if (clockwise) {
        	action_exec((keyevent_t){.key = (keypos_t){.row = 0, .col = 9}, .pressed = true, .time = (timer_read() | 1)  /* time should not be 0 */});  
        	action_exec((keyevent_t){.key = (keypos_t){.row = 0, .col = 9}, .pressed = false, .time = (timer_read() | 1)  /* time should not be 0 */});
        	} 
        	else {
        	action_exec((keyevent_t){.key = (keypos_t){.row = 0, .col = 11}, .pressed = true, .time = (timer_read() | 1)  /* time should not be 0 */});
        	action_exec((keyevent_t){.key = (keypos_t){.row = 0, .col = 11}, .pressed = false, .time = (timer_read() | 1)  /* time should not be 0 */});  
            }
    }
    else if (index == 4) { /* 5 encoder */
        if (clockwise) {
        	action_exec((keyevent_t){.key = (keypos_t){.row = 1, .col =9}, .pressed = true, .time = (timer_read() | 1)  /* time should not be 0 */});  
        	action_exec((keyevent_t){.key = (keypos_t){.row = 1, .col =9}, .pressed = false, .time = (timer_read() | 1)  /* time should not be 0 */});
        	} 
        	else {
        	action_exec((keyevent_t){.key = (keypos_t){.row = 1, .col = 11}, .pressed = true, .time = (timer_read() | 1)  /* time should not be 0 */});
        	action_exec((keyevent_t){.key = (keypos_t){.row = 1, .col = 11}, .pressed = false, .time = (timer_read() | 1)  /* time should not be 0 */});  
            }
    }
    else if (index == 5) { /* 6 encoder */
        if (clockwise) {
        	action_exec((keyevent_t){.key = (keypos_t){.row = 2, .col = 9}, .pressed = true, .time = (timer_read() | 1)  /* time should not be 0 */});  
        	action_exec((keyevent_t){.key = (keypos_t){.row = 2, .col = 9}, .pressed = false, .time = (timer_read() | 1)  /* time should not be 0 */});
			is_encoder6_rotate = true;  
			encoder_timer = timer_read();
        	} 
        	else {
        	action_exec((keyevent_t){.key = (keypos_t){.row = 2, .col = 11}, .pressed = true, .time = (timer_read() | 1)  /* time should not be 0 */});
        	action_exec((keyevent_t){.key = (keypos_t){.row = 2, .col = 11}, .pressed = false, .time = (timer_read() | 1)  /* time should not be 0 */});
			is_encoder6_rotate = true;  
			encoder_timer = timer_read();
            }
    }
    else if (index == 6) { /* 7 encoder */
        if (clockwise) {
        	action_exec((keyevent_t){.key = (keypos_t){.row = 3, .col = 9}, .pressed = true, .time = (timer_read() | 1)  /* time should not be 0 */});  
        	action_exec((keyevent_t){.key = (keypos_t){.row = 3, .col = 9}, .pressed = false, .time = (timer_read() | 1)  /* time should not be 0 */});
			is_encoder7_rotate = true;  
			encoder_timer = timer_read();
        	} 
        	else {
        	action_exec((keyevent_t){.key = (keypos_t){.row = 3, .col = 11}, .pressed = true, .time = (timer_read() | 1)  /* time should not be 0 */});
        	action_exec((keyevent_t){.key = (keypos_t){.row = 3, .col = 11}, .pressed = false, .time = (timer_read() | 1)  /* time should not be 0 */});
			is_encoder7_rotate = true;  
			encoder_timer = timer_read();
            }
    }
    else if (index == 7) { /* 8 encoder */
        if (clockwise) {
        	action_exec((keyevent_t){.key = (keypos_t){.row = 3, .col = 3}, .pressed = true, .time = (timer_read() | 1)  /* time should not be 0 */});  
        	action_exec((keyevent_t){.key = (keypos_t){.row = 3, .col = 3}, .pressed = false, .time = (timer_read() | 1)  /* time should not be 0 */});
        	} 
        	else {
        	action_exec((keyevent_t){.key = (keypos_t){.row = 3, .col = 5}, .pressed = true, .time = (timer_read() | 1)  /* time should not be 0 */});
        	action_exec((keyevent_t){.key = (keypos_t){.row = 3, .col = 5}, .pressed = false, .time = (timer_read() | 1)  /* time should not be 0 */});  
            }
    }
    else if (index == 8) { /* 9 encoder */
        if (clockwise) {
        	action_exec((keyevent_t){.key = (keypos_t){.row = 3, .col = 6}, .pressed = true, .time = (timer_read() | 1)  /* time should not be 0 */});  
        	action_exec((keyevent_t){.key = (keypos_t){.row = 3, .col = 6}, .pressed = false, .time = (timer_read() | 1)  /* time should not be 0 */});
        	} 
        	else {
        	action_exec((keyevent_t){.key = (keypos_t){.row = 3, .col = 8}, .pressed = true, .time = (timer_read() | 1)  /* time should not be 0 */});
        	action_exec((keyevent_t){.key = (keypos_t){.row = 3, .col = 8}, .pressed = false, .time = (timer_read() | 1)  /* time should not be 0 */});  
            }
    }
	return true;
}


// RGB Layer Light Settings - Note that this will fix the key switches with same LED colour and brightness
const rgblight_segment_t PROGMEM my_layer0_layer[] = RGBLIGHT_LAYER_SEGMENTS({4, 18, 95,255,90}); //Spring green
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS({4, 18, 30,255,120}); //Yellow-orange
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS({4, 18, 128,255,100}); //Cyan
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS({4, 18, 215,255,120}); //Magenta
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS({4, 2, 43,100,160}); //White-left caps lock indication (No dedicated LED)
const rgblight_segment_t PROGMEM my_numlock_layer[] = RGBLIGHT_LAYER_SEGMENTS({8, 2, 43,100,150}); //White-right num lock indication (No dedicated LED)
const rgblight_segment_t PROGMEM my_scrollock_layer[] = RGBLIGHT_LAYER_SEGMENTS({6, 2, 43,100,160}); //White-middle scroll lock indication (No dedicated LED)


const rgblight_segment_t *const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST( //Lighting layers
    my_layer0_layer,
    my_layer1_layer,
    my_layer2_layer,
    my_layer3_layer,
	my_capslock_layer,    //Highest status indicators override other layers
	my_numlock_layer,
	my_scrollock_layer
);


void keyboard_post_init_user(void)
{
    rgblight_layers = my_rgb_layers;// Enable the LED layers
	rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_GRADIENT+8); //Set to static gradient 9
	layer_move(0); //start on layer 0 to get the lighting activated
}


layer_state_t layer_state_set_user(layer_state_t state)
{
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));    // Multiple layers will light up if both kb layers are active
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
	
	switch(biton32(state)){ // Change all other LEDs based on layer state as well
		case 0:
			rgblight_sethsv_noeeprom(50,255,30);
			break;
		case 1:
			rgblight_sethsv_noeeprom(30,255,30);
			break;
		case 2:
			rgblight_sethsv_noeeprom(106,255,30);
			break;
		case 3:
			rgblight_sethsv_noeeprom(215,255,30);
			break;
		default:
			rgblight_sethsv_noeeprom(64,255,30);
	  }
    return state;
}


bool led_update_user(led_t led_state)
{
	rgblight_set_layer_state(4, led_state.caps_lock); //Activate capslock lighting layer
	rgblight_set_layer_state(5, !(led_state.num_lock)); //Invert the indication so numlock does not always appear "on".
	rgblight_set_layer_state(6, led_state.scroll_lock); //Activate scrollock lighting layer
    return true;
}
