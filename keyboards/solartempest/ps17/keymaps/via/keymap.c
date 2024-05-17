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

#include QMK_KEYBOARD_H
#include "ps17.h"
#ifdef RGBLIGHT_ENABLE
	extern rgblight_config_t rgblight_config; // To pull layer status for RGBLIGHT
#endif


bool is_alt_tab_active = false; // Super Alt Tab Code
uint16_t alt_tab_timer = 0;

bool spam_arrow;				// Spam F24 or other keys like arrows Code
uint16_t spam_timer = false;
uint16_t spam_interval = 1000;	// (1000ms == 1s)

bool teams_muted;				// Teams muted simple LED indicator 

bool is_stretch_active = false; // Stretch Timer Code
bool is_stretch_time = false;
uint16_t stretch_timer = 0;
uint16_t stretch_minutes = 0;

#ifdef VIA_ENABLE
	enum custom_keycodes { //Use USER 00 instead of SAFE_RANGE for Via. VIA json must include the custom keycode.
	  ATABF = USER00, //Alt tab forwards
	  ATABR, //Alt tab reverse
	  NMR, //Move window to monitor on right
	  NML, //Move window to monitor on left
	  SPAMARROW, //Spam arrows. Updated to send F24 instead, which is more convenient.
	  TEAMSMUTE, //MS Teams mute shortcut and simple LED status
	  STRT				//Stretch Timer
	};
#else
	enum custom_keycodes { //Use USER 00 instead of SAFE_RANGE for Via. VIA json must include the custom keycode.
	  ATABF = SAFE_RANGE, //Alt tab forwards
	  ATABR, //Alt tab reverse
	  NMR, //Move window to monitor on right
	  NML, //Move window to monitor on left
	  SPAMARROW, //Spam arrows. Updated to send F24 instead, which is more convenient.
	  TEAMSMUTE, //MS Teams mute shortcut and simple LED status
	  STRT				//Stretch Timer
	};
#endif

#ifdef COMBO_ENABLE //Tap combos
	enum combos {
	  kppls_7, //Hold plus and 7 to backspace
	  kppls_8, //Hold plus and 8 to delete
	  kpent_4, //Hold enter and 4 for left arrow
	  kpent_5, //Hold enter and 5 for down arrow
	  kpent_6, //Hold enter and 6 for right arrow
	  kpent_8, //Hold enter and 4'8 for up arrow
	};
	const uint16_t PROGMEM kppls7_combo[] = {KC_KP_PLUS, KC_KP_7, COMBO_END};
	const uint16_t PROGMEM kppl8_combo[] = {KC_KP_PLUS, KC_KP_8, COMBO_END};
	const uint16_t PROGMEM kpent4_combo[] = {KC_PENT, KC_KP_4, COMBO_END};
	const uint16_t PROGMEM kpent5_combo[] = {KC_PENT, KC_KP_5, COMBO_END};
	const uint16_t PROGMEM kpent6_combo[] = {KC_PENT, KC_KP_6, COMBO_END};
	const uint16_t PROGMEM kpent8_combo[] = {KC_PENT, KC_KP_8, COMBO_END};
	combo_t key_combos[COMBO_COUNT] = {
	  [kppls_7] = COMBO(kppls7_combo, KC_BSPACE),
	  [kppls_8] = COMBO(kppl8_combo, KC_DELETE),
	  [kpent_4] = COMBO(kpent4_combo, KC_LEFT),
	  [kpent_5] = COMBO(kpent5_combo, KC_DOWN),
	  [kpent_6] = COMBO(kpent6_combo, KC_RGHT),
	  [kpent_8] = COMBO(kpent8_combo, KC_UP)
	};
#endif

#ifdef TAP_DANCE_ENABLE// Tap Dance definitions. Not compatible with VIA.
	enum {
		TD_MINUS_NUMLOCK,
	};
	qk_tap_dance_action_t tap_dance_actions[] = {
		// Tap once for Escape, twice for Caps Lock
		[TD_MINUS_NUMLOCK] = ACTION_TAP_DANCE_DOUBLE(KC_KP_MINUS, KC_NUMLOCK),
	};
	//TD(TD_MINUS_NUMLOCK) // Add tap dance item to your keymap in place of a keycode (non-VIA only)
#endif


enum layer_names {
    _LAYER0,
    _LAYER1,
    _LAYER2,
    _LAYER3,
    _LAYER4,
    _LAYER5,
    _LAYER6,
    _LAYER7,
    _LAYER8,
    _LAYER9
};
	  
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_LAYER0] = LAYOUT(
		KC_PGDOWN, KC__MUTE, KC_PGUP,
		MO(_LAYER1), KC_KP_SLASH, KC_KP_ASTERISK, KC_KP_MINUS,
        KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_PLUS,
        KC_KP_4, KC_KP_5, KC_KP_6,
        KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_ENTER,
        KC_KP_0,          KC_KP_DOT
    ),
    [_LAYER1] = LAYOUT(
		KC_RIGHT, KC_TRNS, KC_LEFT,
        KC_TRNS, KC_MEDIA_STOP, KC_SPACE, KC_NUMLOCK,
        TO(_LAYER4), TG(_LAYER2), TG(_LAYER3), KC_BSPACE,
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, RESET,
        RESET,          KC_TRNS
    ),
    [_LAYER2] = LAYOUT(
		KC_RBRACKET, KC_TRNS, KC_LBRACKET,
        TO(0), KC_B, KC_T, C(S(KC_N)),
        KC_J, KC_S, KC_D, C(KC_MINS),
        C(KC_C), C(KC_V), KC_M,
        C(KC_N), C(S(KC_Z)), KC_LSHIFT, C(KC_PPLS),
        KC_SPACE,          KC_LALT
    ),
    [_LAYER3] = LAYOUT(
		ATABF, KC_TRNS, ATABR,
        TO(0), KC_WWW_REFRESH, KC_HOME, C(KC_T),
        C(S(KC_TAB)), KC_UP, C(KC_TAB), C(KC_W),
        KC_LEFT, KC_DOWN, KC_RIGHT,
        KC_WWW_BACK, KC_SPACE, KC_WWW_FORWARD, KC_ENTER,
        KC_PGDOWN,          KC_PGUP
    ),
    [_LAYER4] = LAYOUT(
		ATABF, KC_TRNS, ATABR,
        TO(0), KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_UP, KC_TRNS, KC_TRNS,
        KC_LEFT, KC_DOWN, KC_RIGHT,
        C(S(KC_M)), LWIN(KC_F4), KC_TRNS, KC_NUMLOCK,
        KC_F13,          KC_F14
    ),
    [_LAYER5] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,          KC_TRNS
    ),
    [_LAYER6] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,          KC_TRNS
    ),
    [_LAYER7] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,          KC_TRNS
    ),
    [_LAYER8] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,          KC_TRNS
    ),
    [_LAYER9] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,          KC_TRNS
    )
};


void matrix_scan_user(void) {
  if (is_alt_tab_active) {		//Super alt tab code
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
  if (spam_arrow && timer_elapsed(spam_timer) >= spam_interval) {
    spam_timer = timer_read();	//Spam arrow code
    tap_code(KC_F24);
  }
  
  #ifdef RGBLIGHT_ENABLE
	if (is_stretch_active && !is_stretch_time) { //Stretch timer code
		if(timer_elapsed(stretch_timer)>60000) { //1 minute in ms has passed. Timer is uint16 max.
			stretch_minutes++;
			stretch_timer = timer_read();
		}
		if (stretch_minutes > 30) { //Change RGB animation effect after set number of minutes. 30 minutes is a good interval.
		  rgblight_set_effect_range(0, 28);
		  rgblight_mode_noeeprom(RGBLIGHT_MODE_SNAKE);
		  is_stretch_time = true;
		  stretch_minutes = 0;
		}
	}
	
	if(!is_stretch_time){	//Update LED status indicators when stretch animation is not playing.
		if(is_stretch_active==1) {
			rgblight_sethsv_at(0,230,100,8); //Set LED to orange to indicate timer is on
			rgblight_sethsv_at(0,230,100,9); //Set LED to orange to indicate timer is on
			rgblight_sethsv_at(0,230,100,13); //Set LED to orange to indicate timer is on
			}
		  
		if(teams_muted==1) { //Check and display teamsmuted status
			rgblight_sethsv_at(15,255,120,18);
			rgblight_sethsv_at(15,255,120,22);
			}

		if(spam_arrow==1) { //Change LED colour on bottom row and underglow to orange to indicate on
			rgblight_sethsv_at(15,255,120,24);
			rgblight_sethsv_at(15,255,120,25);
			rgblight_sethsv_at(15,255,120,26);
			rgblight_sethsv_at(15,255,120,27);
			}
		}
  #endif
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) { //For keycode overrides
		case ATABF:	//Super alt tab forwards
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
		case ATABR:	//Super alt tab reverse
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
		  
		case SPAMARROW: // Spam F24 or other keys like arrows
		  if (record->event.pressed) { 
			spam_arrow ^= 1; 
			spam_timer = timer_read();
			#ifdef RGBLIGHT_ENABLE
				if(spam_arrow==1) { //Change LED colour on bottom row and underglow to orange to indicate on
					rgblight_sethsv_at(15,255,120,24);
					rgblight_sethsv_at(15,255,120,25);
					rgblight_sethsv_at(15,255,120,26);
					rgblight_sethsv_at(15,255,120,27);
					}
				else {
					rgblight_set_effect_range(0, 28);
					rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_GRADIENT+8); //Set back to layer colours
					}
			#endif
		  }
		  return false;
		  
		case TEAMSMUTE:	//Mute MS teams shortcut and simply change LED for key 1 colour
		  if (record->event.pressed) {
			register_code(KC_LCTRL);
			register_code(KC_LSFT);
			register_code(KC_M);
			unregister_code(KC_M);
			unregister_code(KC_LSFT);
			unregister_code(KC_LCTRL);
			teams_muted ^= 1; 
			#ifdef RGBLIGHT_ENABLE
				if(teams_muted==1) { //Change LED colour on LEDs for key 1 and underglow to orange to indicate muted
					rgblight_sethsv_at(15,255,120,18);
					rgblight_sethsv_at(15,255,120,22);
					}
				else {
					//rgblight_sethsv_at(175,255,120,18); //Set LEDs back to violet, assuming on that coloured layer
					//rgblight_sethsv_at(175,255,120,22);
					rgblight_sethsv_at(207,255,120,18); //Set LEDs back to magenta, assuming on that coloured layer
					rgblight_sethsv_at(207,255,120,22);
					}
			#endif
		  }
		  return true;
		  
		  
		case STRT:	//Stretch timer
		  if (record->event.pressed) {
			#ifdef RGBLIGHT_ENABLE
				is_stretch_active ^= 1;
				stretch_timer = timer_read();
				//rgblight_sethsv_at(75,215,80,41);
				if(is_stretch_time==1) { //Check if it is time to stretch, then dismiss the animation.
					rgblight_set_effect_range(0, 28);
					rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_GRADIENT+8);
					rgblight_sethsv_at(0,230,100,8); //Set LED to orange to indicate timer is on
					rgblight_sethsv_at(0,230,100,9); //Set LED to orange to indicate timer is on
					rgblight_sethsv_at(0,230,100,13); //Set LED to orange to indicate timer is on
					is_stretch_active = 1;
					is_stretch_time = 0;
					stretch_minutes = 0;
					}
				else if(is_stretch_active==1) {
					rgblight_set_effect_range(0, 28);
					rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_GRADIENT+8);
					rgblight_sethsv_at(0,230,100,8); //Set LED to orange to indicate timer is on
					rgblight_sethsv_at(0,230,100,9); //Set LED to orange to indicate timer is on
					rgblight_sethsv_at(0,230,100,13); //Set LED to orange to indicate timer is on
					is_stretch_time = 0;
					stretch_minutes = 0;
					}
				else {
					rgblight_set_effect_range(0, 28);
					rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_GRADIENT+8); //Set back to layer colours -- CHECK LAYERS RESET LED STATUS
					is_stretch_time = 0;
					stretch_minutes = 0;
					}
			#endif
		  }
		  return false;
	}
	return true;
}


void keyboard_post_init_user(void) {
  #ifdef RGB_MATRIX_ENABLE
    //NOTE 1: Layer lighting doesn't work in RGB matrix mode
	//NOTE 2: VIA lighting tab doesn't work and might crash in RGB matrix mode
	//NOTE 3: VIA layers doesn't seem to work properly in RGB matrix mode
	//rgb_matrix_enable_noeeprom(); //turn on RGB matrix based on previous state
	rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE); //set initial RGB matrix mode	
	rgb_matrix_sethsv_noeeprom(50, 255, 100); //sets LED to green-yellow
  #endif
  #ifdef RGBLIGHT_ENABLE
    //rgblight_layers = my_rgb_layers;// Enable the LED layers
	rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_GRADIENT+8); //Set to static gradient 9
	layer_move(0); //start on layer 0 to get the lighting activated
  #endif
};


#ifdef RGBLIGHT_ENABLE
layer_state_t layer_state_set_user(layer_state_t state) {
	/*rgblight_set_layer_state(0, layer_state_cmp(state, 0));    // Multiple layers will light up if both kb layers are active
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
    rgblight_set_layer_state(4, layer_state_cmp(state, 4));*/
	
	// This is what the LED layout is.
	// 1,                 0, 
	// 3,                 2, 
	// 9,   8, 7,  6,  5, 4, 
	// 13, 12, 11, 10,   
	// 18, 17, 16, 15,    14,
	// 22, 21, 20, 19,   
	// 27, 26, 25, 24,    23 
		
	switch (get_highest_layer(state)) { // Change all other LEDs based on layer state as well
		case 0:
			//rgblight_sethsv_noeeprom(50,255,100);	//blue-green gradient
			rgblight_sethsv_noeeprom(115,200,100);	//pale-blue gradient
			//You can selectively decrease certain LEDs if you are have a clear acrylic case and the shine-through is bothersome. Rgblight_sethsv_at() can be used here for those LEDs (0, 2, 4, 14, and 23). Otherwise some black tape on the acrylic plate or foam underneath the FR4 plate will do the trick.
			break;
		case 1:
			rgblight_sethsv_noeeprom(5,255,100);
		case 2:
			//rgblight_sethsv_noeeprom(128,255,100);//blue-purple gradient
			rgblight_sethsv_noeeprom(160,255,100);	//blue-magenta gradient
			break;
		case 3:
			rgblight_sethsv_noeeprom(215,255,100);
			break;
		case 4:
			rgblight_sethsv_noeeprom(15,255,100);
			break;
	  }
    return state;
	};
#endif
