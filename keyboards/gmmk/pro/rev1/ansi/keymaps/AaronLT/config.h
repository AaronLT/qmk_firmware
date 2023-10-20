/* Copyright 2021 Jonavin Eng @Jonavin
   Copyright 2022 gourdo1 <gourdo1@outlook.com>
   Copyright 2023 Aaron Thomas @AaronLT

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

// Force n-key rollover
#define FORCE_NKRO

// Set maximum time between taps (in ms)
#define TAPPING_TOGGLE 2
#define TAPPING_TERM 300
//#define TAPPING_TERM_PER_KEY   // only used if you define your own get_tapping_term() function, since tapping term affects more than the tap dance feature

// Caps Word configuration
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD
#define CAPS_WORD_IDLE_TIMEOUT 5000      // Automatically turn off after x milliseconds of idle. 0 to never timeout.

#ifdef RGB_MATRIX_ENABLE
    // disable RGB on USB and timer
    #define RGB_DISABLE_WHEN_USB_SUSPENDED
    #define RGB_DISABLE_TIMEOUT 900000

    // default color & mode
    #define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR
    #define RGB_MATRIX_DEFAULT_HUE 15
    #define RGB_MATRIX_DEFAULT_SAT 255
    #define RGB_MATRIX_DEFAULT_VAL 140
    #define RGB_MATRIX_DEFAULT_SPD 127

    // effects
    #define RGB_MATRIX_KEYPRESSES            // Enables REACTIVE & SPLASH modes
    #define RGB_MATRIX_FRAMEBUFFER_EFFECTS   // Enables Heatmap, Rain

#endif //RGB_MATRIX_ENABLE
