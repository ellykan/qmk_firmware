// Copyright 2022 Markus Knutsson (@TweetyDaBird)
// SPDX-License-Identifier: GPL-2.0-or-later

// STEPS TO COMPILE AND FLASH:
// 1. Open QMK MSYS
// 2. Run qmk flash -kb tweetydabird/lotus58 -km ellykan -e CONVERT_TO=rp2040_ce
// 3. To enter bootloader mode, you can hold top left key and plug in usb (BOOTMAGIC)

#include QMK_KEYBOARD_H

#define _LAYER0 0
#define _LAYER1 1
#define _LAYER2 2

enum custom_keycodes
{
   LAYER0 = SAFE_RANGE,
   LAYER1,
   LAYER2,
};

enum tapDances
{
   TD_RSHIFT_CAPS = 0,
   TD_LSHIFT_CAPS = 1,
   TD_F12_RESET = 2,
   TD_LAYER_0_1 = 3, // Change from Layer 0 to Layer 1
   TD_LAYER_1_2 = 4, // Change from Layer 1 to Layer 2
   TD_LAYER_2_0 = 5, // Change from Layer 2 to Layer 0
};

void safe_reset(tap_dance_state_t *state, void *user_data) 
{
    if (state->count == 1)
    {
        tap_code(KC_F12);
    }
    if (state->count >= 3)
    {
        // Reset the keyboard if you tap the key more than three times
        reset_keyboard();
    }
    reset_tap_dance(state);
}

void td_layer_0_1_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        layer_on(1);  // hold-like (MO)
    } else if (state->count == 2) {
        layer_move(1);  // toggle-to (TO)
    }
}
void td_layer_0_1_reset(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        layer_off(1);
    }
}

void td_layer_1_2_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        layer_on(2);
    } else if (state->count == 2) {
        layer_move(2);
    }
}
void td_layer_1_2_reset(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        layer_off(2);
    }
}

void td_layer_2_0_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        layer_on(0);
    } else if (state->count == 2) {
        layer_move(0);
    }
}
void td_layer_2_0_reset(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        layer_off(0);
    }
}

tap_dance_action_t tap_dance_actions[] = {
  [TD_RSHIFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_RSFT, KC_CAPS),
  [TD_LSHIFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
  [TD_F12_RESET]   = ACTION_TAP_DANCE_FN(safe_reset),
  [TD_LAYER_0_1]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_layer_0_1_finished, td_layer_0_1_reset),
  [TD_LAYER_1_2]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_layer_1_2_finished, td_layer_1_2_reset),
  [TD_LAYER_2_0]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_layer_2_0_finished, td_layer_2_0_reset),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
                    //┌────────────────┬────────────────┬────────────────┬────────────────┬────────────────┬────────────────┬─────────┐      ┌─────────┬────────────────┬────────────────┬────────────────┬────────────────┬────────────────┬────────────────┐
[_LAYER0] = LAYOUT(         KC_ESC,           KC_1,             KC_2,           KC_3,            KC_4,            KC_5,        KC_NO,          KC_MUTE,       KC_6,            KC_7,            KC_8,            KC_9,            KC_0,          KC_DELETE, 
/*BASE*/            //├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┼────────────────┼─────────┘      └─────────├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┼────────────────┤
                            KC_TAB,           KC_Q,             KC_W,           KC_E,            KC_R,            KC_T,                                       KC_Y,            KC_U,            KC_I,            KC_O,            KC_P,           KC_BSLS,
                    //├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┼────────────────┤                          ├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┼────────────────┤
                      TD(TD_LSHIFT_CAPS),     KC_A,             KC_S,           KC_D,            KC_F,            KC_G,                                       KC_H,            KC_J,            KC_K,            KC_L,            KC_SCLN,        KC_QUOT,
                    //├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┼────────────────┤────────┐        ┌────────├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┼────────────────┤  
                            KC_LCTL,          KC_Z,             KC_X,           KC_C,            KC_V,            KC_B,      KC_LBRC,          KC_RBRC,       KC_N,            KC_M,            KC_COMM,         KC_DOT,          KC_SLSH,   TD(TD_RSHIFT_CAPS),
                    //└────────────────┴────────────────┴────────────────┴───────┬────────┴───────┬────────┴───────┬────────┴─────┬──┘        └───┬────┴───────────┬────┴───────────┬────┴─────────┬──────┴────────────────┴────────────────┴────────────────┘
                                                                      KC_LGUI,         KC_LALT,         KC_SPC,        KC_ENT,                         KC_BSPC,     TD(TD_LAYER_0_1),   KC_RALT,     KC_GRV     ),
                    //                                          └────────────────┴────────────────┴────────────────┴──────────────┘               └────────────────┴────────────────┴──────────────┴──────────────┘

                    //┌────────────────┬────────────────┬────────────────┬────────────────┬────────────────┬────────────────┬─────────┐      ┌─────────┬────────────────┬────────────────┬────────────────┬────────────────┬────────────────┬────────────────┐
[_LAYER1] = LAYOUT(    TD(TD_F12_RESET),      KC_F1,            KC_F2,          KC_F3,           KC_F4,           KC_F5,       KC_NO,          KC_MUTE,      KC_F6,           KC_F7,           KC_F8,           KC_F9,           KC_F10,         KC_F11,         
/*FUNC*/            //├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┼────────────────┼─────────┘      └─────────├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┼────────────────┤
                            KC_TAB,           KC_NO,            KC_NO,          KC_PGUP,         KC_NO,           KC_PLUS,                                   KC_UNDS,         KC_NO,           KC_UP,           KC_NO,           KC_NO,          KC_BSLS,
                    //├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┼────────────────┤                          ├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┼────────────────┤
                      TD(TD_LSHIFT_CAPS),     KC_NO,            KC_HOME,        KC_PGDN,         KC_END,          KC_EQL,                                    KC_MINS,         KC_LEFT,         KC_DOWN,         KC_RGHT,         KC_NO,          KC_NO,
                    //├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┼────────────────┤────────┐        ┌────────├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┼────────────────┤  
                            KC_LCTL,          KC_NO,            KC_NO,          KC_PSCR,         KC_NO,           KC_NO,     KC_LCBR,          KC_LCBR,      KC_NO,           KC_NO,           KC_NO,           KC_NO,           KC_NO,          KC_NO,
                    //└────────────────┴────────────────┴────────────────┴───────┬────────┴───────┬────────┴───────┬────────┴─────┬──┘        └───┬────┴───────────┬────┴───────────┬────┴─────────┬──────┴────────────────┴────────────────┴────────────────┘
                                                                      KC_LGUI,         KC_LALT,         KC_SPC,        KC_ENT,                         KC_NO,        TD(TD_LAYER_1_2),   KC_RALT,      KC_GRV     ),
                    //                                          └────────────────┴────────────────┴────────────────┴──────────────┘               └────────────────┴────────────────┴──────────────┴──────────────┘
                    //┌────────────────┬────────────────┬────────────────┬────────────────┬────────────────┬────────────────┬─────────┐      ┌─────────┬────────────────┬────────────────┬────────────────┬────────────────┬────────────────┬────────────────┐
[_LAYER2] = LAYOUT(         KC_GRV,           KC_1,          KC_2,           KC_3,            KC_4,            KC_5,           KC_NO,          KC_MUTE,    KC_6,            KC_7,            KC_8,            KC_9,            KC_0,            KC_DELETE,
/*GAME*/            //├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┼────────────────┼─────────┘      └─────────├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┼────────────────┤
                            KC_TAB,           KC_Q,          KC_W,           KC_E,            KC_R,            KC_T,                                       KC_Y,            KC_U,            KC_I,            KC_O,           KC_P,             KC_BSLS,
                    //├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┼────────────────┤                          ├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┼────────────────┤
                            KC_LSFT,          KC_A,          KC_S,           KC_D,            KC_F,            KC_G,                                       KC_H,            KC_J,            KC_K,            KC_L,           KC_SCLN,          KC_QUOT, 
                    //├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┼────────────────┤────────┐        ┌────────├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┼────────────────┤  
                            KC_LCTL,          KC_Z,          KC_X,           KC_C,            KC_V,            KC_B,          KC_ESC,             KC_NO,   KC_N,            KC_M,            KC_COMM,         KC_DOT,         KC_SLSH,        TD(TD_RSHIFT_CAPS),
                    //└────────────────┴────────────────┴────────────────┴───────┬────────┴───────┬────────┴───────┬────────┴─────┬──┘        └───┬────┴───────────┬────┴───────────┬────┴─────────┬──────┴────────────────┴────────────────┴────────────────┘
                                                                     KC_LCTL,          KC_LALT,         KC_SPC,        KC_ENT,                         KC_BSPC,      TD(TD_LAYER_2_0),     KC_RALT,      KC_GRV     )
                    //                                          └────────────────┴────────────────┴────────────────┴──────────────┘               └────────────────┴────────────────┴──────────────┴──────────────┘

};

layer_state_t layer_state_set_user(layer_state_t state)
{
#ifdef RGB_MATRIX_ENABLE
    // change the color any time a layer switches
    // This function is called every time a layer switches, no matter how it switches
    // Look up RGB colorpicker on google, take HSV values after colorpicker
    // Pink - 250, 180, 255
    // Light Blue - 132, 80, 180
    // Gold - 21, 255, 255 (HSV_Orange, but shows a gold)
    // Light Blue - 0, 0, 255 (HSV_White, but shows as blue)
    switch (get_highest_layer(state))
    {
        case _LAYER1:
            rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
            rgb_matrix_sethsv_noeeprom(128, 190, 130); // HSV_CYAN -- lowered brightness with (H,S,V) S and V value
            break;
        case _LAYER2:
            rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
            rgb_matrix_sethsv_noeeprom(191, 190, 255); // HSV_PURPLE
            break;
        default: // _LAYER0
            rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
            rgb_matrix_sethsv_noeeprom(250, 190, 255); // HSV_PINK 
            break;
    }
#endif
   return state;  // this is required, DO NOT REMOVE
}

/*required in rules.mk: ENCODER_ENABLE = yes 
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) }
};
#endif*/

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 1) 
    {
        switch (get_highest_layer(layer_state))
        {
            case _LAYER1:
                if (clockwise)
                {
                    // SWAP -- encoder seems reverse mounted
                    tap_code16(LCTL(KC_LEFT)); // CTRL+Right Arrow -> move right one word
                } 
                else 
                {
                    tap_code16(LCTL(KC_RGHT)); // CTRL+Left Arrow -> move left one word
                }
                break;
            case _LAYER2:
                if (clockwise)
                {
                    tap_code16(LCTL(KC_PMNS)); // CTRL+NumpadPlus -> Zoom in
                } 
                else 
                {
                    tap_code16(LCTL(KC_PPLS)); // CTRL+NumpadMinus -> Zoom out
                }
                break;
            default: // _LAYER0 and all layers
                if (clockwise)
                {
                    tap_code(KC_VOLD);
                } 
                else 
                {
                    tap_code(KC_VOLU);
                }
                break;
        }
    }
    return true;
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}
static void print_status_narrow(void) {
    // Create OLED content
    oled_write_P(PSTR("\n"), false);
    oled_write_P(PSTR(""), false);
    oled_write_P(PSTR("Lotus -58-"), false);
    oled_write_P(PSTR("\n"), false);

    // Print current layer
    oled_write_P(PSTR("Layer"), false);
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("-Base\n"), false);
            break;
        case 1:
            oled_write_P(PSTR("-Func \n"), false);
            break;
        case 2:
            oled_write_P(PSTR("-Game\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undef"), false);
    }
    
    oled_write_P(PSTR("\n"), false);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("Caps- lock"), led_usb_state.caps_lock);
    
}

#ifdef AUTO_SHIFT_ENABLE

    bool autoshift = get_autoshift_state();
    oled_advance_page(true);
    oled_write_P(PSTR("Auto-Shift"), autoshift);
    oled_advance_page(true);
    
#endif

bool oled_task_user(void) {
    // Render the OLED
    print_status_narrow();
    return false;
}

#endif