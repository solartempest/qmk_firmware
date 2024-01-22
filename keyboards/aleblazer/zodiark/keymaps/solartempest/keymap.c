/*
Copyright 2021 Spencer Deven <splitlogicdesign@gmail.com>
Copyright 2021 solartempest
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
#include QMK_KEYBOARD_H
#ifdef OLED_ENABLE
	#include "snake_photo.c"
#endif
#include "encoder.c"

#ifdef POINTING_DEVICE_ENABLE
	bool trackball_is_scrolling = true;		//Default mode is scrolling
	bool trackball_is_precision = false;	//Default mode is less precise
	bool was_scrolling = true;	//Remember preferred state of trackball scrolling
#endif

#ifdef HAPTIC_ENABLE
	#include "drivers/haptic/DRV2605L.h"
#endif

#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS)
	extern rgblight_config_t rgblight_config; // To pull layer status for RGBLIGHT
#endif

//Variables for custom keycodes
#ifdef SUPER_ALT_TAB_ENABLE
	bool is_alt_tab_active = false; // Super Alt Tab Code
	uint16_t alt_tab_timer = 0;
#endif
bool lshift_held = false;	// LShift Backspace Delete whole Word Code
bool rshift_held = false;	// RShift Backspace Delete whole Word Code
static uint16_t held_shift = 0;

#ifdef D2SKATE_MACRO_ENABLE
	uint16_t D2SKATE_TIMER = 0;
	bool D2SKATE_skated = false;	//Has skated
	bool D2SKATE_reset = true;	//Has skated
#endif

#ifdef VIA_ENABLE
	enum custom_keycodes { //Use USER 00 instead of SAFE_RANGE for Via. VIA json must include the custom keycode.
	  ATABF = USER00, 	//Alt tab forwards
	  ATABR, 			//Alt tab reverse
	  NMR, 				//Move window to monitor on right
	  NML, 				//Move window to monitor on left
	  SBS, 				//Shift backspace to delete whole word (Swap KC_BPSC with this)
      PM_SCROLL,		//Toggle trackball scrolling mode
      PM_PRECISION,		//Toggle trackball precision mode
	  D2SKATE			//Destiny 2 hunter sword skate
	};
#else
	enum custom_keycodes { //Use USER 00 instead of SAFE_RANGE for Via. VIA json must include the custom keycode.
	  ATABF = SAFE_RANGE, //Alt tab forwards
	  ATABR, 			//Alt tab reverse
	  NMR, 				//Move window to monitor on right
	  NML, 				//Move window to monitor on left
	  SBS,				//Shift backspace to delete whole word (Swap KC_BPSC with this)
      PM_SCROLL,		//Toggle trackball scrolling mode
      PM_PRECISION,		//Toggle trackball precision mode
	  D2SKATE			//Destiny 2 hunter sword skate
	};
#endif

#ifdef VIA_ENABLE
	// Extra keys are added for rotary encoder support in VIA
	#define LAYOUT_via( \
		 L00, L01, L02, L03, L04, L05,                               R05, R04, R03, R02, R01, R00, \
		 L10, L11, L12, L13, L14, L15, L06,                     R06, R15, R14, R13, R12, R11, R10, \
		 L20, L21, L22, L23, L24, L25, L16,                     R16, R25, R24, R23, R22, R21, R20, \
		 L30, L31, L32, L33, L34, L35, L26, L36, L37, R37, R36, R26, R35, R34, R33, R32, R31, R30, \
		 L40, L41, L42, L43, L44,    L45,   L46, L47, R47, R46,   R45,    R44, R43, R42, R41, R40  \
		  ) \
		  { \
		 { L00,   L01,   L02,   L03,   L04,   L05,   L06,   KC_NO }, \
		 { L10,   L11,   L12,   L13,   L14,   L15,   L16,   KC_NO }, \
		 { L20,   L21,   L22,   L23,   L24,   L25,   L26,   KC_NO }, \
		 { L30,   L31,   L32,   L33,   L34,   L35,   L36,   L37   }, \
		 { L40,   L41,   L42,   L43,   L44,   L45,   L46,   L47   }, \
		 { R00,   R01,   R02,   R03,   R04,   R05,   R06,   KC_NO }, \
		 { R10,   R11,   R12,   R13,   R14,   R15,   R16,   KC_NO }, \
		 { R20,   R21,   R22,   R23,   R24,   R25,   R26,   KC_NO }, \
		 { R30,   R31,   R32,   R33,   R34,   R35,   R36,   R37   }, \
		 { R40,   R41,   R42,   R43,   R44,   R45,   R46,   R47   }  \
		}
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
#ifndef VIA_ENABLE //This will bypass the layout when VIA is enabled to save space. Requires loading layout in VIA otherwise random keys may be occur.
	[0] = LAYOUT(
	  KC_ESC,  KC_1,    KC_2,    KC_3,   KC_4,  KC_5,                                                         KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
	  KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,  KC_T,  KC_LBRC,                                      KC_RBRC, KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
	  MO(3),   KC_A,    KC_S,    KC_D,   KC_F,  KC_G,  KC_MINS,                                      KC_EQL,  KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
	  KC_LSFT, KC_Z,    KC_X,    KC_C,   KC_V,  KC_B,  KC_GRV,  KC_MUTE, _______, _______, RGB_TOG,  KC_DEL,  KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
	  KC_LCTL, KC_LALT, KC_LGUI, KC_APP, MO(1),    KC_SPC,      KC_ENT,  _______, _______, KC_ENT,       KC_SPC,       MO(2),  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
	  ),
		
	[1] = LAYOUT(
	  _______, KC_F1, KC_F2,   KC_F3,   KC_F4,   KC_F5,                                                             KC_F6,   KC_F7,   KC_F8, KC_F9,   KC_F10,  KC_F11,
	  KC_PSLS, KC_P7, KC_P8,   KC_P9,   KC_NLCK, _______, _______,                                         _______, _______, KC_PSLS, KC_P7, KC_P8,   KC_P9,   KC_F12,
	  KC_CAPS, KC_P4, KC_P5,   KC_P6,   KC_NLCK, _______, _______,                                         _______, _______, _______, KC_P4, KC_P5,   KC_P6,   KC_NLCK,
	  _______, KC_P1, KC_P2,   KC_P3,   _______, _______, _______, _______,  _______,  _______,  _______,  _______, _______, _______, KC_P1, KC_P2,   KC_P3,   _______,
	  _______, KC_P0, KC_PDOT, KC_PENT, _______,      _______,     _______,  _______,  _______,  _______,  _______,    _______,       KC_P0, KC_PDOT, KC_PENT, _______
	  ),
	  
	[2] = LAYOUT(
	  _______, KC_F1, KC_F2,   KC_F3,   KC_F4,   KC_F5,                                                            KC_F6,   KC_F7,   KC_F8, KC_F9,   KC_F10,  KC_F11,
	  KC_PSLS, KC_P7, KC_P8,   KC_P9,   KC_NLCK, _______, _______,                                        _______, _______, KC_PSLS, KC_P7, KC_P8,   KC_P9,   KC_F12,
	  KC_CAPS, KC_P4, KC_P5,   KC_P6,   KC_NLCK, _______, _______,                                        _______, _______, _______, KC_P4, KC_P5,   KC_P6,   KC_NLCK,
	  _______, KC_P1, KC_P2,   KC_P3,   _______, _______, _______, _______,  _______,  _______,  _______, _______, _______, _______, KC_P1, KC_P2,   KC_P3,   _______,
	  _______, KC_P0, KC_PDOT, KC_PENT, _______,       _______,    _______,  _______,  _______,  _______,    _______,       _______, KC_P0, KC_PDOT, KC_PENT, _______
	  ),

	[3] = LAYOUT(
	  _______, _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______, _______,
	  _______, _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______, _______,
	  _______, _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______, _______,
	  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
	  _______, _______, _______, _______, _______,     _______,      _______, _______, _______, _______,     _______,      _______, _______, _______, _______, _______
	  )
#endif
};

#ifdef POINTING_DEVICE_ENABLE
	void run_trackball_cleanup(void) {	//Set colour of trackball LED. Does not require RGBLIGHT_ENABLE if colour shorthands are not used.
		if (trackball_is_scrolling) {
			pimoroni_trackball_set_rgbw(217, 165, 33, 0x00);	//RGB_GOLDENROD in number form. 
			//pimoroni_trackball_set_rgbw(43, 153, 103, 0x00);
		} else if (!trackball_is_precision) {
			pimoroni_trackball_set_rgbw(0, 27, 199, 0x00);
		} else {
			//pimoroni_trackball_set_rgbw(217, 165, 33, 0x00);	//RGB_GOLDENROD in number form.
			pimoroni_trackball_set_rgbw(43, 153, 103, 0x00);
		}
	}
	
	uint8_t pointing_device_handle_buttons(uint8_t buttons, bool pressed, pointing_device_buttons_t button) {
		if (pressed) {
			buttons |= 1 << (button);
			#ifdef HAPTIC_ENABLE	//Haptic feedback when trackball button is pressed
				DRV_pulse(4);		//sharp_click
			#endif
		} else {
			buttons &= ~(1 << (button));
		}
		return buttons;
	}

	report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
		if (trackball_is_scrolling) {
			mouse_report.h = mouse_report.x;
			#ifndef PIMORONI_TRACKBALL_INVERT_X
				mouse_report.v = 0.2*mouse_report.y;	//Multiplier to lower scrolling sensitivity
			#else
				mouse_report.v = 0.2*-mouse_report.y;	//invert vertical scroll direction
			#endif
			mouse_report.x = mouse_report.y = 0;
		}
		return mouse_report;
	}

	#if !defined(MOUSEKEY_ENABLE)	//Allows for button clicks on keymap even though mousekeys is not defined.
		static bool mouse_button_one, trackball_button_one;
	#endif

	void trackball_register_button(bool pressed, enum mouse_buttons button) {
		report_mouse_t currentReport = pointing_device_get_report();
		if (pressed) {
			currentReport.buttons |= button;
		} else {
			currentReport.buttons &= ~button;
		}
		pointing_device_set_report(currentReport);
	}
#endif



void matrix_scan_user(void) {
	#ifdef ENCODER_ENABLE
		encoder_action_unregister(); 
	#endif
	
	#ifdef SUPER_ALT_TAB_ENABLE
		if (is_alt_tab_active) {	//Allows for use of super alt tab.
			if (timer_elapsed(alt_tab_timer) > 1000) {
				unregister_code(KC_LALT);
				is_alt_tab_active = false;
			}
		}
	#endif
	#ifdef D2SKATE_MACRO_ENABLE
		if (D2SKATE_reset == false) {	//Check if Destiny 2 skate timer is activated
			if (timer_elapsed(D2SKATE_TIMER) > 4000) {
				rgblight_sethsv_noeeprom(252,255,80); //Set regular game layer colour
				D2SKATE_reset = true;
				#ifdef HAPTIC_ENABLE
					DRV_pulse(12);		//trp_click
				#endif
			}
		}
	#endif
	#ifdef ENCODER_ENABLE
		encoder_action_unregister();
	#endif
	
	#ifdef POINTING_DEVICE_ENABLE
		if (timer_elapsed32(oled_timer) > 60000) { //60000ms = 60s
			pimoroni_trackball_set_rgbw(0,0,0, 0x00); //Turn off Pimoroni trackball LED when computer is idle for 1 minute. Would use suspend_power_down_user but the code is not working.
		}
	#endif
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	#if defined(KEYBOARD_PET) || defined(OLED_LOGO)
		if (record->event.pressed) { //OLED timeout code
			oled_timer = timer_read32();
		}
	#endif
	
	switch (keycode) { //For keycode overrides
		#ifdef SUPER_ALT_TAB_ENABLE
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
		#endif
		  
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

		case KC_RSFT: //Shift Backspace to Delete Whole Word. Inspired by Hellsingcoder.
			rshift_held = record->event.pressed;
			held_shift = keycode;
			#ifdef KEYBOARD_PET // KEYBOARD PET STATUS
				if (record->event.pressed) {
					isBarking = true;
				} else {
					isBarking = false;
				}
			#endif
			return true;
		case KC_LSFT:
			lshift_held = record->event.pressed;
			held_shift = keycode;
			#ifdef KEYBOARD_PET // KEYBOARD PET STATUS
				if (record->event.pressed) {
					isBarking = true;
				} else {
					isBarking = false;
				}
			#endif
			return true;
		case SBS:
			if (record->event.pressed) { //When left shift is held and backspace pressed, one whole word will be deleted (left).
				if (lshift_held) {
					unregister_code(held_shift);
					register_code(KC_LCTL);
					register_code(KC_BSPC);
				} else if (rshift_held) { //When left shift is held and backspace pressed, one whole word will be deleted (right).
					unregister_code(held_shift);
					register_code(KC_LCTL);
					register_code(KC_DEL);
				} else {
					register_code(KC_BSPC);
				}
			} else {
				unregister_code(KC_BSPC);
				unregister_code(KC_DEL);
				unregister_code(KC_LCTL);
				if (lshift_held || rshift_held) {
					register_code(held_shift);
				}
			}
			return false;
		#ifdef D2SKATE_MACRO_ENABLE
			case D2SKATE:
					if (record->event.pressed) {
						register_code(KC_0);
						wait_ms(34);
						register_code(KC_SPC);
						unregister_code(KC_0);
						register_code(KC_X);
						wait_ms(18);
						unregister_code(KC_SPC);
						unregister_code(KC_X);
						rgblight_sethsv_noeeprom(180,255,80);
						D2SKATE_skated = true;
					}
				return false;
			case KC_1:
			case KC_2:
			case KC_3:
				if (record->event.pressed) {
					if(D2SKATE_skated){	//Start the cooldown timer
						D2SKATE_TIMER = timer_read();
						D2SKATE_skated = false;
						D2SKATE_reset = false;
					}
				}
				return true;
		#endif

		#ifdef POINTING_DEVICE_ENABLE //Allow modes when trackball is enabled.
				case PM_SCROLL:
					if (record->event.pressed) {
						if (trackball_is_scrolling || was_scrolling){ //Enable toggling for trackball scrolling
							trackball_is_scrolling=false;
							was_scrolling=false; //Tracks status of scrolling setting. Works with holding of layer key for mouse mode.
						} else{
							trackball_is_scrolling=true;
							was_scrolling=true;
						}
						run_trackball_cleanup();
						break;
					}
				case PM_PRECISION:
					if (record->event.pressed) {
						if (trackball_is_precision){ //Enable toggling for trackball precision
							pimoroni_trackball_set_precision(1.75);
							trackball_is_precision=false;
						} else{
							pimoroni_trackball_set_precision(0.8);
							trackball_is_precision=true;
						}
						run_trackball_cleanup();
						break;
					}
			#ifndef MOUSEKEY_ENABLE //Allow for using mouse buttons in the keymap when mouse keys is not enabled.
					case KC_MS_BTN1:
						mouse_button_one = record->event.pressed;
						trackball_register_button(mouse_button_one | trackball_button_one, MOUSE_BTN1);
						break;
					case KC_MS_BTN2:
						trackball_register_button(record->event.pressed, MOUSE_BTN2);
						break;
					case KC_MS_BTN3:
						trackball_register_button(record->event.pressed, MOUSE_BTN3);
						break;
			#endif
		#endif
		
		#ifdef KEYBOARD_PET // KEYBOARD PET STATUS
			case KC_LCTL:
			case KC_RCTL:
				#ifndef SNEAK_DISABLE
				if (record->event.pressed) { //Pet sneaks when control held.
					isSneaking = true;
				} else {
					isSneaking = false;
				}
				#endif
				#ifdef HAPTIC_ENABLE	//Set different patterns for keys on certain layers. In this case it is for gaming feedback.
					if (record->event.pressed && (get_highest_layer(layer_state)==1)) {
						DRV_pulse(51);		//buzz_20
					}
				#endif
				return true;
			case KC_SPC:
				if (record->event.pressed) { //Pet jumps when enter is pressed.
					isJumping = true;
					showedJump = false;
				} else {
					isJumping = false;
				}
				return true;
		#endif
		
		#ifdef HAPTIC_ENABLE	//Set different patterns for keys on certain layers. In this case it is for gaming feedback.
			case KC_G:
				if (record->event.pressed && (get_highest_layer(layer_state)==1)) {
					DRV_pulse(50);		//buzz_40
				}
			case KC_R:
				if (record->event.pressed && (get_highest_layer(layer_state)==1)) {
					DRV_pulse(52);		//pulsing_strong
				}
			case KC_F:
				if (record->event.pressed && (get_highest_layer(layer_state)==1)) {
					DRV_pulse(49);		//buzz_60
				}
		#endif
		}
	return true;
}


#ifdef RGBLIGHT_ENABLE
	layer_state_t layer_state_set_user(layer_state_t state)	//Use for layer lighting. This method uses less space than RGBLIGHT_LAYER_SEGMENTS.
	{
		switch (get_highest_layer(state)) { // Change all other LEDs based on layer state as well
			case 0:
				//rgblight_sethsv_noeeprom(50,255,80);	//green-blue gradient
				//rgblight_sethsv_noeeprom(115,170,80);	//pale blue gradient
				rgblight_sethsv_noeeprom(0,220,60);	//yellow gradient
				#ifdef POINTING_DEVICE_ENABLE
					if (was_scrolling==true){ //Check if was scrolling when layer was left
						trackball_is_scrolling=true;
						run_trackball_cleanup();
					} else{
						trackball_is_scrolling=false;
						run_trackball_cleanup();
					}
				#endif
				break;
			case 1:
				rgblight_sethsv_noeeprom(252,255,80);
				#ifdef HAPTIC_ENABLE	//Set different patterns for haptic feedback layer indication
					DRV_pulse(69);		//transition_hum_10
				#endif
				break;
			case 2:
				rgblight_sethsv_noeeprom(80,255,80);
				#ifdef HAPTIC_ENABLE
					DRV_pulse(37);		//lg_dblclick_str
				#endif
				break;
			case 3:
				//rgblight_sethsv_noeeprom(118,255,80);	//blue-purple gradient
				rgblight_sethsv_noeeprom(160,255,80);	//blue-magenta gradient
				#ifdef HAPTIC_ENABLE
					DRV_pulse(31);		//sh_dblclick_med
				#endif
				break;
			case 4:
				rgblight_sethsv_noeeprom(218,255,80);
				#ifdef HAPTIC_ENABLE
					DRV_pulse(7);		//soft_bump
				#endif
				#ifdef POINTING_DEVICE_ENABLE	//Set trackball mouse mode when layer 4 is activated
					if (was_scrolling==true){	//Check if in scrolling mode when layer was activated
						trackball_is_scrolling=false;
						run_trackball_cleanup();
					}
				#endif
		  }
		return state;
	}
	
	bool led_update_user(led_t led_state)	//Lock key status indicators
	{
		if(led_state.caps_lock){
			rgblight_sethsv_range(43,100,170, 4,8); //White-left caps lock indication
		}
		if(!(led_state.num_lock)){
			rgblight_sethsv_range(43,100,170, 0,2); //White-right num lock indication. Since this indicator is inverted, it must be on the master side of the keyboard to shut off properly when the computer is sleeping.
			rgblight_sethsv_range(43,100,170, 10,12);
		}
		if(led_state.scroll_lock){
			rgblight_sethsv_range(43,100,170, 2,4); //White-middle scroll lock indication
			rgblight_sethsv_range(43,100,170, 8,10);
		}
		return true;
	}
#endif


void keyboard_post_init_user(void)
{
	#ifdef RGBLIGHT_ENABLE
		rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_GRADIENT+8); //Set to static gradient 9
		//rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING); //Test
	#endif
	layer_move(0); 						//Start on layer0 by default to set LED colours. Can remove to save a very small amount of space.
	#ifdef POINTING_DEVICE_ENABLE
		pimoroni_trackball_set_precision(1.75);	//Start trackball with lower precision mode
		run_trackball_cleanup();
	#endif
}

#ifdef POINTING_DEVICE_ENABLE
	void suspend_power_down_user(void) {	//Code does not work, need to confirm why
			pimoroni_trackball_set_rgbw(0,0,0, 0x00); //Turn off Pimoroni trackball LED when computer is sleeping
	}
#endif

#ifdef POINTING_DEVICE_ENABLE
	void suspend_wakeup_init_user(void) { //turn on Pimoroni LED when awoken
		run_trackball_cleanup();
	}
#endif
