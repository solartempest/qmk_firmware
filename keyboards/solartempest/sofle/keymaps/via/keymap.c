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
#include <stdio.h> //This is required for OLED sprintf.
#include "encoder.c"
#ifdef OLED_ENABLE
	//#include "oled.c" //Stock OLED code
	//Note that the keyboard animations below take a large amount of space!
		//#include "bongocat.c" //OLED code for Bongocat, original code by foureight84. Disable RGBLIGHT to make enough space.
		//#include "luna.c" //OLED code for Luna, original code by Hellsingcoder and adapted by Jackasaur.
		#include "snakey.c" //OLED code for Snakey, customized from Luna.
#endif

#ifdef RGBLIGHT_ENABLE
	extern rgblight_config_t rgblight_config; // To pull layer status for RGBLIGHT
#endif


bool is_alt_tab_active = false; // Super Alt Tab Code
uint16_t alt_tab_timer = 0;
bool lshift_held = false;	// LShift Backspace Delete whole Word Code
bool rshift_held = false;	// RShift Backspace Delete whole Word Code
static uint16_t held_shift = 0;
#ifdef VIA_ENABLE
	enum custom_keycodes { //Use USER 00 instead of SAFE_RANGE for Via. VIA json must include the custom keycode.
	  ATABF = USER00, //Alt tab forwards
	  ATABR, //Alt tab reverse
	  NMR, //Move window to monitor on right
	  NML, //Move window to monitor on left
	  SBS //Shift backspace to delete whole word (Swap KC_BPSC with this)
	};
#else
	enum custom_keycodes { //Use USER 00 instead of SAFE_RANGE for Via. VIA json must include the custom keycode.
	  ATABF = SAFE_RANGE, //Alt tab forwards
	  ATABR, //Alt tab reverse
	  NMR, //Move window to monitor on right
	  NML, //Move window to monitor on left
	  SBS //Shift backspace to delete whole word (Swap KC_BPSC with this)
	};
#endif


/*#ifdef COMBO_ENABLE //(+42 firmware size for this combo). SBS takes care of this combo, so it is an example only and can be replaced with others as required.
	enum combo_events {
	  sbs_delword
	};

	const uint16_t PROGMEM delword_combo[] = {KC_LSFT, KC_BSPC, COMBO_END}; //Shift-Backspace to delete whole words
	combo_t key_combos[COMBO_COUNT] = {
	  [sbs_delword] = COMBO_ACTION(delword_combo)
	};

	void process_combo_event(uint16_t combo_index, bool pressed) {
	  switch(combo_index) {
		case sbs_delword:
		  if (pressed) {
			tap_code16(LCTL(KC_BSPC));
		  }
		  break;
	  }
	}
#endif*/


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {  //Can skip these layouts to save space when using only VIA.
/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|  Enc  |    |  Enc  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
/*[0] = LAYOUT(
  KC_GRV,	KC_1,	KC_2,	KC_3,	KC_4,	KC_5,						KC_6,	KC_7,	KC_8,	KC_9,	KC_0,		KC_MINS,
  KC_ESC,	KC_Q,	KC_W,	KC_E,	KC_R,	KC_T,	KC__VOLUP,	KC_PGUP,KC_Y,	KC_U,	KC_I,	KC_O,	KC_P,		SBS,
  KC_TAB,	KC_A,	KC_S,	KC_D,	KC_F,	KC_G,	KC_MUTE,	KC_NO,	KC_H,	KC_J,	KC_K,	KC_L,	KC_SCLN,	KC_QUOT,
  KC_LSFT,	KC_Z,	KC_X,	KC_C,	KC_V,	KC_B,	KC__VOLDOWN,KC_PGDN,KC_N,	KC_M,	KC_COMM,KC_DOT,	KC_SLSH,	KC_RSFT,
					KC_LGUI,KC_LALT,KC_LCTRL,MO(2),	KC_ENT,		KC_SPC,	MO(3),	KC_RCTRL,KC_RALT,KC_RGUI
)
,
[1] = LAYOUT(
  KC_PSCR,	KC_5,		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,							KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_F11,		KC_F4,
  KC_T,		KC_ESC,		KC_Q,		KC_W,		KC_E,		KC_R,		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_F12,
  KC_G,		KC_TAB,		KC_A,		KC_S,		KC_D,		KC_F,		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
  KC_LSFT,	KC_LSFT,	KC_Z,		KC_X,		KC_C,		KC_V,		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_RALT,
						KC_ENT,		KC_B,		KC_TRNS,	KC_PAUS,	KC_SPACE,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS
),
[2] = LAYOUT(
  KC_TRNS,	KC_F1,	KC_F2,	KC_F3,	KC_F4,	KC_F5,							KC_F6,	KC_F7,	KC_F8,	KC_F9,	KC_F10,		KC_F11,
  KC_GRV,	KC_1,	KC_2,	KC_3,	KC_4,	KC_5,	KC_RGHT,		KC_TRNS,KC_6,	KC_7,	KC_8,	KC_9,	KC_0,		KC_F12,
  KC_WREF,	KC_EXLM,KC_AT,	KC_HASH,KC_DLR,	KC_PERC,KC_TRNS,		KC_TRNS,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,	KC_PIPE,
  KC_TRNS,	KC_EQL,	KC_MINS,KC_PLUS,KC_LCBR,KC_LCBR,KC_LEFT,		KC_TRNS,KC_LBRC,KC_RBRC,KC_DOT,	KC_COLN,KC_BSLS,	KC_TRNS,
					KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,		KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS
),
[3] = LAYOUT(
  NML,		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,							KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	NMR,
  KC_NLCK,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	ATABF,		NMR,		KC_WFWD,	KC_HOME,	KC_UP,		KC_END,		KC_INS,		KC_DEL,
  KC_SLCK,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_WBAK,	KC_LEFT,	KC_DOWN,	KC_RIGHT,	KC_TRNS,	KC_TRNS,
  KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	ATABR,		NML,		KC_CAPS,	KC_PGUP,	KC_TRNS,	KC_PGDN,	KC_TRNS,	KC_TRNS,
						KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS
)*/
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
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	#ifdef KEYBOARD_PET
		if (record->event.pressed) { //Drashna's OLED timeout off code for animations
			oled_timer = timer_read32();
		}
	#endif
	
	switch (keycode) { //For keycode overrides
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

		case KC_RSFT:	//Shift Backspace to Delete Whole Word. Inspired by Hellsingcoder.
			rshift_held = record->event.pressed;
			held_shift = keycode;
			// KEYBOARD PET STATUS
			#ifdef KEYBOARD_PET
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
			// KEYBOARD PET STATUS
			#ifdef KEYBOARD_PET
				if (record->event.pressed) {
					isBarking = true;
				} else {
					isBarking = false;
				}
			#endif
			return true;
		case SBS:
			if (record->event.pressed) {
				if (lshift_held) {
					unregister_code(held_shift);
					register_code(KC_LCTL);
					register_code(KC_BSPC);
				} else if (rshift_held) {
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
			
		// KEYBOARD PET STATUS
		#ifdef KEYBOARD_PET
			case KC_LCTL:
			case KC_RCTL:
				if (record->event.pressed) {
					isSneaking = true;
				} else {
					isSneaking = false;
				}
				return true;
			case KC_SPC:
				if (record->event.pressed) {
					isJumping = true;
					showedJump = false;
				} else {
					isJumping = false;
				}
				return true;
		#endif
		}
	return true;
}


#ifdef OLED_ENABLE
	void suspend_power_down_user(void) { //turn off OLEDs when computer is sleeping
		oled_off();
	}
#endif


#ifdef RGBLIGHT_ENABLE
	// RGB Layer Light Settings - Note that this will fix the key switch LED colour and brightness
	const rgblight_segment_t PROGMEM my_layer0_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 0, 95,255,90}); //Change range for multiple keys with same colour
	const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 0, 252,255,125}); //Change range for multiple keys with same colour
	const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 0, 95,255,90}); //Change range for multiple keys with same colour
	const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 0, 128,255,100}); //Change range for multiple keys with same colour
	const rgblight_segment_t PROGMEM my_layer4_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 0, 215,255,120}); //Change range for multiple keys with same colour
	const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS({4, 3, 43,100,170}); //White-left caps lock indication (No dedicated LED)
	const rgblight_segment_t PROGMEM my_numlock_layer[] = RGBLIGHT_LAYER_SEGMENTS({28, 3, 43,100,170}); //White-right num lock indication (No dedicated LED). Since this indicator is inverted, it must be on the master side of the keyboard to shut off properly when the computer is sleeping.
	const rgblight_segment_t PROGMEM my_scrollock_layer[] = RGBLIGHT_LAYER_SEGMENTS({55, 3, 43,100,170}); //White-middle-right scroll lock indication (No dedicated LED)
	const rgblight_segment_t *const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST( //Lighting layers
		my_layer0_layer,
		my_layer1_layer,
		my_layer2_layer,
		my_layer3_layer,
		my_layer4_layer,
		my_capslock_layer,    //Highest status indicators override other layers
		my_numlock_layer,
		my_scrollock_layer
	);


	void keyboard_post_init_user(void)
	{
		rgblight_layers = my_rgb_layers;// Enable the LED layers
		rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_GRADIENT+8); //Set to static gradient 9
		//layer_move(0); //start on layer 0 to get the lighting activated in all cases
	}


	layer_state_t layer_state_set_user(layer_state_t state)
	{
		rgblight_set_layer_state(0, layer_state_cmp(state, 0));    // Multiple layers will light up if both kb layers are active
		rgblight_set_layer_state(1, layer_state_cmp(state, 1));
		rgblight_set_layer_state(2, layer_state_cmp(state, 2));
		rgblight_set_layer_state(3, layer_state_cmp(state, 3));
		rgblight_set_layer_state(4, layer_state_cmp(state, 4));
		
		switch(biton32(state)){ // Change all other LEDs based on layer state as well
			case 0:
				rgblight_sethsv_noeeprom(50,255,80);
				break;
			case 1:
				rgblight_sethsv_noeeprom(252,255,80);
				break;
			case 2:
				rgblight_sethsv_noeeprom(80,255,80);
				break;
			case 3:
				rgblight_sethsv_noeeprom(118,255,80);
				break;
			case 4:
				rgblight_sethsv_noeeprom(218,255,80);
		  }
		return state;
	}


	bool led_update_user(led_t led_state)
	{
		rgblight_set_layer_state(5, led_state.caps_lock); //Activate capslock lighting layer
		rgblight_set_layer_state(6, !(led_state.num_lock)); //Invert the indication so numlock does not always appear "on".
		rgblight_set_layer_state(7, led_state.scroll_lock); //Activate scrollock lighting layer
		return true;
	}
#endif
