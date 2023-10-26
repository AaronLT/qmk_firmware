#include "caps_word.h"
#include "caps_word_extended.h"
#include "quantum.h"

caps_word_mode_t caps_word_mode = CAPS_WORD_MODE_DEFAULT;
bool caps_word_last_key_was_space = false;
uint16_t caps_word_space_substitute = CAPS_WORD_SPACE_SUB_KEYCODE_DEFAULT;

bool caps_word_press_user(uint16_t keycode) {
    switch(caps_word_mode) {
        case CWMODE_NORMAL:
            switch (keycode) {
                // Keycodes that continue Caps Word, with shift applied.
                case KC_A ... KC_Z:
                    add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
                    return true;

                // Keycodes that continue Caps Word, without shifting.
                case KC_1 ... KC_0:
                case KC_BACKSPACE:
                case KC_MINUS:
                    return true;

                default:
                    return false;  // Deactivate Caps Word.
            }
        case CWMODE_CAMEL_CASE:
        case CWMODE_PASCAL_CASE:
        case CWMODE_SPACE_SUB:
        case CWMODE_CAPS_SPACE_SUB:
            switch (keycode) {
                case KC_SPACE:
                    // If the last key was NOT a space, then register it having been pressed and
                    // move on as normal
                    if (!caps_word_last_key_was_space) {
                        caps_word_last_key_was_space = true;
                        return true;
                    }
                    // if this is the second space in a row, delete one and exit Caps Word
                    else {
                        tap_code16(KC_BSPC);
                        return false;
                    }

                // Keys that do NOT break the Caps Word state
                case KC_A ... KC_Z:
                case KC_1 ... KC_0:
                case KC_MINUS:
                case KC_BACKSPACE:
                    if (caps_word_last_key_was_space) {
                        tap_code16(KC_BACKSPACE);
                        switch (caps_word_mode) {
                            case CWMODE_CAMEL_CASE:
                            case CWMODE_PASCAL_CASE:
                                add_weak_mods(MOD_BIT(KC_LSFT));
                                break;
                            case CWMODE_SPACE_SUB:
                            case CWMODE_CAPS_SPACE_SUB:
                                tap_code16(caps_word_space_substitute);
                                break;
                            default:
                                break;

                        }
                        caps_word_last_key_was_space = false;
                    }
                    if (
                        caps_word_mode == CWMODE_CAPS_SPACE_SUB
                        && (KC_A <= keycode && keycode <= KC_Z)
                    ) {
                        add_weak_mods(MOD_BIT(KC_LSFT));
                    }
                    return true;

                default:
                    return false;  // Deactivate Caps Word
            }

        default:
            return false;
    }
}

void caps_word_set_user(bool active) {
    if (active) {
        caps_word_last_key_was_space = false;
        if (caps_word_mode == CWMODE_PASCAL_CASE) {
            add_oneshot_mods(MOD_BIT(KC_LSFT));
        }
    } else {
        caps_word_mode = CAPS_WORD_MODE_DEFAULT;
        caps_word_space_substitute = CAPS_WORD_SPACE_SUB_KEYCODE_DEFAULT;
        clear_oneshot_mods();
    }
}

// Sets caps word for the given mode,  If caps word is already on in any mode, it is turned off
// and replaced with the new mode.  This will reset the caps word timer.
bool set_caps_word_mode(caps_word_mode_t new_mode) {
    // Turn it off in case it was on before this
    caps_word_off();

    // Set the mode and turn it on
    caps_word_mode = new_mode;
    caps_word_on();

    return is_caps_word_on();
}

// Sets caps word to one of the space substitution modes and sets the space substitution keycode
bool set_caps_word_space_sub(uint16_t sub_keycode, bool in_caps) {
    caps_word_space_substitute = sub_keycode;

    if (in_caps) {
        return set_caps_word_mode(CWMODE_CAPS_SPACE_SUB);
    }
    else {
        return set_caps_word_mode(CWMODE_SPACE_SUB);
    }
}

bool is_caps_word_mode_on(caps_word_mode_t mode_to_check) {
    if (caps_word_mode == mode_to_check) {
        return is_caps_word_on();
    }

    return false;
}
