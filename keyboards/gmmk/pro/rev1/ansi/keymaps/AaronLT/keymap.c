/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

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

#include "caps_word.h"
#include QMK_KEYBOARD_H
#include "rgb_matrix_map.h"

#ifndef ARRAYSIZE
    #define ARRAYSIZE(arr)  sizeof(arr)/sizeof(arr[0])
#endif

bool TEST_RGB_IND = false;

RGB get_rgb_values_from_hsv(int hue, int saturation, int value) {
    HSV hsv = { hue, saturation, value };
    return hsv_to_rgb(hsv);
}

enum custom_user_keycodes {
    TEST_RGB_IND_TOGG = SAFE_RANGE,
    RGB_COLOR_HOME,
    RGB_COLOR_WORK
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TEST_RGB_IND_TOGG:
            if (record -> event.pressed) {
                TEST_RGB_IND = !TEST_RGB_IND;
            }
            return false;
        case RGB_COLOR_HOME:
            if (record -> event.pressed) {
                rgb_matrix_sethsv(HSV_BURNT_ORANGE);
            }
            return false;
        case RGB_COLOR_WORK:
            if (record -> event.pressed) {
                rgb_matrix_sethsv(HSV_PINK_RANGER);
            }
            return false;
        default:
            return true;
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
        for (uint8_t i = 0; i < ARRAYSIZE(LED_LIST_LETTERS); i++) {
            RGB rgb_value = get_rgb_values_from_hsv(HSV_GREEN);
            rgb_matrix_set_color(LED_LIST_LETTERS[i], rgb_value.r, rgb_value.g, rgb_value.b);
        }
    }
    if (is_caps_word_on()) {
        for (uint8_t i = 0; i < ARRAYSIZE(LED_LIST_LETTERS); i++) {
            RGB rgb_value = get_rgb_values_from_hsv(HSV_BLUE);
            rgb_matrix_set_color(LED_LIST_LETTERS[i], rgb_value.r, rgb_value.g, rgb_value.b);
        }
    }
    if (keymap_config.no_gui) {
        RGB rgb_value = get_rgb_values_from_hsv(HSV_RED);
        rgb_matrix_set_color(LED_LWIN, rgb_value.r, rgb_value.g, rgb_value.b);
    }
    if (TEST_RGB_IND) {  // test full colors with this indicator
        RGB rgb_value = get_rgb_values_from_hsv(HSV_PINK_RANGER);
        rgb_matrix_set_color_all(rgb_value.r, rgb_value.g, rgb_value.b);
    }
    return true;
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the QK_BOOT key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    //
    // This keyboard defaults to 6KRO instead of NKRO for compatibility reasons (some KVMs and BIOSes are incompatible with NKRO).
    // Since this is, among other things, a "gaming" keyboard, a key combination to enable NKRO on the fly is provided for convenience.
    // Press Fn+N to toggle between 6KRO and NKRO. This setting is persisted to the EEPROM and thus persists between restarts.
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,          KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_END,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGUP,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             MO(1), MO(2),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [1] = LAYOUT(
        QK_RBT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          RGB_TOG,
        _______, RGB_COLOR_HOME, RGB_COLOR_WORK, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_CALC, _______,          _______,
        _______, _______, _______, _______, TEST_RGB_IND_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,            _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_LOCK, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, NK_TOGG, _______, _______, _______, _______,          _______, RGB_SPI, _______,
        _______, GU_TOGG, _______,                            QK_CLEAR_EEPROM,                            _______, _______, _______, RGB_RMOD, RGB_SPD, RGB_MOD
    ),

    [2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),


};
// clang-format on

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) }
};
#endif

