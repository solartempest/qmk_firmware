/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
   Copyright 2021 Jonavin

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
#include "rgb_matrix_map.h"
#include "jonavin.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Ins           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    [_BASE] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,           KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        TT(_LOWER), KC_A, KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
        KC_LSFTCAPSWIN,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(_FN1),KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_FN1] = LAYOUT(
        _______, KC_MYCM, KC_WHOM, KC_CALC, KC_MSEL, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, _______, KC_CALC,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          RGB_TOG,
        _______, _______, RGB_VAI, _______, _______, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, _______, _______, _______, RESET,            KC_HOME,
        KC_CAPS, _______, RGB_VAD, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          KC_END,
        _______,          _______, RGB_HUI, _______, _______, _______, KC_NLCK, _______, _______, _______, _______,          _______, RGB_MOD, _______,
        _______, KC_WINLCK, _______,                            _______,                          _______, _______, _______, RGB_SPD, RGB_RMOD, RGB_SPI
    ),

    [_LOWER] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_P0,   KC_PMNS, KC_PPLS, _______,          _______,
        _______, KC_HOME, KC_UP,   KC_END,  KC_PGUP, _______, KC_TAB,  KC_P4,   KC_P5,   KC_P6,   KC_PDOT, _______, _______, _______,          KC_HOME,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_NO,   KC_PAST,          KC_PENT,          KC_END,
        _______,          KC_NO,   KC_DEL,  KC_INS,  KC_NO,   KC_NO,   KC_NO,   KC_P0, KC_00, KC_PDOT, KC_PSLS,         _______, RCTL(KC_PGUP), _______,
        _______, _______, _______,                            KC_BSPC,                            _______, _______, _______, RCTL(KC_LEFT), RCTL(KC_PGDN), RCTL(KC_RIGHT)
    ),

   [_RAISE] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

};


#ifdef RGB_MATRIX_ENABLE
    // Capslock, Scroll lock and Numlock indicator on Left side lights.
    void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
		if (IS_HOST_LED_ON(USB_LED_SCROLL_LOCK)) {
            rgb_matrix_set_color(LED_L7, RGB_GOLD);
            rgb_matrix_set_color(LED_L8, RGB_GOLD);
            rgb_matrix_set_color(LED_R7, RGB_GOLD);
            rgb_matrix_set_color(LED_R8, RGB_GOLD);
        }
        if (!IS_HOST_LED_ON(USB_LED_NUM_LOCK)) {   // on if NUM lock is OFF
            rgb_matrix_set_color(LED_L1, RGB_GOLD);
            rgb_matrix_set_color(LED_L2, RGB_GOLD);
            rgb_matrix_set_color(LED_R1, RGB_GOLD);
            rgb_matrix_set_color(LED_R2, RGB_GOLD);
        }
        if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
            rgb_matrix_set_color(LED_L3, RGB_GOLDENROD);
            rgb_matrix_set_color(LED_L4, RGB_GOLDENROD);
            rgb_matrix_set_color(LED_L5, RGB_GOLDENROD);
            rgb_matrix_set_color(LED_L6, RGB_GOLDENROD);
            rgb_matrix_set_color(LED_R3, RGB_GOLDENROD);
            rgb_matrix_set_color(LED_R4, RGB_GOLDENROD);
            rgb_matrix_set_color(LED_R5, RGB_GOLDENROD);
            rgb_matrix_set_color(LED_R6, RGB_GOLDENROD);
        }
        if (keymap_config.no_gui) {
            rgb_matrix_set_color(LED_LWIN, RGB_RED);  //light up Win key when disabled
        }
        switch(get_highest_layer(layer_state)){  // special handling per layer
        case _FN1:  // on Fn layer select what the encoder does when pressed
            /*rgb_matrix_set_color(LED_R2, RGB_RED); //Show the active layer as red
            rgb_matrix_set_color(LED_R3, RGB_RED);
            rgb_matrix_set_color(LED_R4, RGB_RED);
            rgb_matrix_set_color(LED_FN, RGB_RED); //FN key*/
			for (uint8_t i=0; i<ARRAYSIZE(LED_LIST_FUNCROW); i++) {
                rgb_matrix_set_color(LED_LIST_FUNCROW[i], RGB_CHARTREUSE);
            };
			for (uint8_t i=0; i<ARRAYSIZE(LED_LIST_NAV); i++) {
                rgb_matrix_set_color(LED_LIST_NAV[i], RGB_CHARTREUSE);
            };
			for (uint8_t i=0; i<ARRAYSIZE(LED_LIST_ARROWS); i++) {
                rgb_matrix_set_color(LED_LIST_ARROWS[i], RGB_CHARTREUSE);
            };
			for (uint8_t i=0; i<ARRAYSIZE(LED_LIST_MODS); i++) {
                rgb_matrix_set_color(LED_LIST_MODS[i], RGB_CHARTREUSE);
            };
            break;
        case _LOWER:
            for (uint8_t i=0; i<ARRAYSIZE(LED_LIST_NUMPAD); i++) {
                rgb_matrix_set_color(LED_LIST_NUMPAD[i], 210,189,0);
            };
			for (uint8_t i=0; i<ARRAYSIZE(LED_LIST_FUNCROW); i++) {
                rgb_matrix_set_color(LED_LIST_FUNCROW[i], 138,118,0); //0,197,180
            };
			for (uint8_t i=0; i<ARRAYSIZE(LED_LIST_NAV); i++) {
                rgb_matrix_set_color(LED_LIST_NAV[i], 138,118,0);
            };
			for (uint8_t i=0; i<ARRAYSIZE(LED_LIST_ARROWS); i++) {
                rgb_matrix_set_color(LED_LIST_ARROWS[i], 210,189,0);
            };
			for (uint8_t i=0; i<ARRAYSIZE(LED_LIST_MODS); i++) {
                rgb_matrix_set_color(LED_LIST_MODS[i], 138,118,0);
            };
            break;
        case _RAISE:
			for (uint8_t i=0; i<ARRAYSIZE(LED_LIST_FUNCROW); i++) {
                rgb_matrix_set_color(LED_LIST_FUNCROW[i], 238,145,0);
            };
			for (uint8_t i=0; i<ARRAYSIZE(LED_LIST_NAV); i++) {
                rgb_matrix_set_color(LED_LIST_NAV[i], 238,145,0);
            };
			for (uint8_t i=0; i<ARRAYSIZE(LED_LIST_ARROWS); i++) {
                rgb_matrix_set_color(LED_LIST_ARROWS[i], 238,145,0);
            };
			for (uint8_t i=0; i<ARRAYSIZE(LED_LIST_MODS); i++) {
                rgb_matrix_set_color(LED_LIST_MODS[i], 238,145,0);
            };
			for (uint8_t i=0; i<ARRAYSIZE(LED_SIDE_LEFT); i++) {
                rgb_matrix_set_color(LED_SIDE_LEFT[i], 238,145,0);
            };
			for (uint8_t i=0; i<ARRAYSIZE(LED_SIDE_RIGHT); i++) {
                rgb_matrix_set_color(LED_SIDE_RIGHT[i], 238,145,0);
            };
            break;
        default:
            break;
        }
    }

/*  void suspend_power_down_user(void) {
        rgb_matrix_set_suspend_state(true);
    }

    void suspend_wakeup_init_user(void) {
        rgb_matrix_set_suspend_state(false);
    }*/
#endif


void keyboard_post_init_keymap(void) {
    // keyboard_post_init_user() moved to userspace
}

