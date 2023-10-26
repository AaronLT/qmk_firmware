#pragma once
#include "keycodes.h"

typedef enum {
    CWMODE_NORMAL = 0,
    CWMODE_CAMEL_CASE,       // camelCase
    CWMODE_PASCAL_CASE,      // PascalCase
    CWMODE_SPACE_SUB,        // snake_case, kebab-case, slash/case, etc.
    CWMODE_CAPS_SPACE_SUB    // same as SPACE_SUB, but with all alpha chars in caps
} caps_word_mode_t;

#define CAPS_WORD_MODE_DEFAULT CWMODE_NORMAL
#define CAPS_WORD_SPACE_SUB_KEYCODE_DEFAULT KC_SPACE

caps_word_mode_t caps_word_mode;

bool set_caps_word_mode(caps_word_mode_t new_mode);
bool set_caps_word_space_sub(uint16_t sub_keycode, bool in_caps);
bool is_caps_word_mode_on(caps_word_mode_t mode_to_check);
