#include QMK_KEYBOARD_H
#include "keymap_german.h"
#include "gamemode.h"

// clang-format off

#define FIRST_GAME_KEYCODE (KC_GAME_BEGIN + 1)
#define LAST_GAME_KEYCODE  (KC_GAME_END - 1)

#define RESULT_QMK_STOP_PROCESSING false 
#define RESULT_QMK_CONTINUE_PROCESSING true

enum layers{
  GAMING_BASE, // Hardware Switch set to Mac
  GAMING_FN,
  WIN_BASE,
  WIN_FN
};

enum {
    GAME_1,
    GAME_2,
    GAME_3,
    GAME_4,
    GAME_5,
    GAME_6,
    GAME_7,
    GAME_8,
    GAME_9,
    GAME_N,
} games;

enum custom_keycodes {
    KC_GAME_NONE = QK_USER,
    KC_GAME_PREVIOUS,
    KC_GAME_NEXT,

    KC_GAME_BEGIN,
    KC_GAME_END = KC_GAME_BEGIN + GAME_N
};

#define GAME(x) (KC_GAME_BEGIN + x)

static game_mode_t current_game_mode;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [GAMING_BASE] = LAYOUT_iso_110(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,     KC_MUTE,  KC_PSCR,  KC_F13,   RGB_MOD,  KC_F14,   KC_F15 ,  KC_F16 ,  KC_F17 ,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,     KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,  KC_NUM,   KC_PSLS,  KC_PAST,  KC_PMNS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,              KC_DEL,   KC_END,   KC_PGDN,  KC_P7,    KC_P8,    KC_P9,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,    KC_ENT,                                 KC_P4,    KC_P5,    KC_P6,    KC_PPLS,
        KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,            KC_UP,              KC_P1,    KC_P2,    KC_P3,
        KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 KC_RALT,  KC_RWIN,MO(GAMING_FN),KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_P0,              KC_PDOT,  KC_PENT),
    [GAMING_FN] = LAYOUT_iso_110(
        _______,  KC_BRID,  KC_BRIU,  _______,  _______,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,    RGB_TOG,  _______,  _______,  RGB_TOG,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,  _______,  _______,  GAME(7),  GAME(8),  GAME(9),
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,                                GAME(4),  GAME(5),  GAME(6),_______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,            _______,            GAME(1),  GAME(2),  GAME(3),
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______,            _______,  _______),
    [WIN_BASE] = LAYOUT_iso_110(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,     KC_MUTE,  KC_PSCR,  KC_F13,   RGB_MOD,  KC_F14,   KC_F15 ,  KC_F16 ,  KC_F17 ,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,     KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,  KC_NUM,   KC_PSLS,  KC_PAST,  KC_PMNS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,              KC_DEL,   KC_END,   KC_PGDN,  KC_P7,    KC_P8,    KC_P9,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,    KC_ENT,                                 KC_P4,    KC_P5,    KC_P6,    KC_PPLS,
        KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,            KC_UP,              KC_P1,    KC_P2,    KC_P3,
        KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 KC_RALT,  KC_RWIN,  MO(WIN_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_P0,              KC_PDOT,  KC_PENT),
    [WIN_FN] = LAYOUT_iso_110(
        _______,  KC_BRID,  KC_BRIU,  _______,  _______,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,    RGB_TOG,  _______,  _______,  RGB_TOG,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,  _______,  _______,  _______,  _______,  _______,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,                                _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,            _______,            _______,  _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______,            _______,  _______),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [GAMING_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [GAMING_FN]   = {ENCODER_CCW_CW(KC_GAME_PREVIOUS, KC_GAME_NEXT) },
    [WIN_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [WIN_FN]   = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI) }
};
#else 
#warning "ENCODER_MAP_ENABLE is disabled!"
#endif

// clang-format on

void change_game_mode(game_mode_t game_mode) {
    current_game_mode = game_mode;

    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
    switch (current_game_mode) {
        case GAME_MODE_NONE: {
            rgb_matrix_set_color_all(RGB_CYAN);
            break;
        }
        case GAME_MODE_CS2: {
            rgb_matrix_set_color_all(RGB_BLUE);
            break;
        }
        case GAME_MODE_PUBG: {
            rgb_matrix_set_color_all(RGB_YELLOW);
            break;
        }
        default:
            break;
    };
}

#if defined(DIP_SWITCH_ENABLE)
bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
            if (active) {
                change_game_mode(GAME_MODE_NONE);
            } else {
                change_game_mode(GAME_MODE_FIRST + 1);
            }
            break;
        }
    }
    return true;
}
#else
#    warning "DIP_SWITCH_ENABLE is not enabled!"
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_GAME_PREVIOUS: {
            change_game_mode(GAME_MODE_CS2);
            return RESULT_QMK_STOP_PROCESSING;

            // const game_mode_t previous_gamemode = current_game_mode - 1;

            // if (previous_gamemode <= GAME_MODE_FIRST) {
            //     current_game_mode = GAME_MODE_LAST - 1;
            //     return RESULT_QMK_STOP_PROCESSING;
            // }
            // current_game_mode = previous_gamemode;
            // return RESULT_QMK_STOP_PROCESSING;
        }
        case KC_GAME_NEXT: {
            change_game_mode(GAME_MODE_PUBG);
            return RESULT_QMK_STOP_PROCESSING;

            // const game_mode_t next_gamemode = current_game_mode + 1;
            // if (next_gamemode >= GAME_MODE_LAST) {
            //     current_game_mode = GAME_MODE_FIRST + 1;
            //     return RESULT_QMK_STOP_PROCESSING;
            // }
            // current_game_mode = next_gamemode;
            // return RESULT_QMK_STOP_PROCESSING;
        }
        case FIRST_GAME_KEYCODE ... LAST_GAME_KEYCODE:
            if (record->event.pressed) {
                change_game_mode(keycode - KC_GAME_BEGIN);
            }
            return RESULT_QMK_STOP_PROCESSING;

        default:
            return RESULT_QMK_CONTINUE_PROCESSING;
    };

    return RESULT_QMK_CONTINUE_PROCESSING;
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
#if defined(CAPS_LOCK_LED_INDEX)
    if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_LED_INDEX, 255, 0, 0);
    } else {
        if (!rgb_matrix_get_flags()) {
            RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_LED_INDEX, 0, 0, 0);
        }
    }
#else
#    warning "CAPS_LOCK_LED_INDEX is not defined!"
#endif // CAPS_LOCK_LED_INDEX
#if defined(NUM_LOCK_LED_INDEX)
    if (host_keyboard_led_state().num_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(NUM_LOCK_LED_INDEX, 255, 0, 0);
    } else {
        if (!rgb_matrix_get_flags()) {
            RGB_MATRIX_INDICATOR_SET_COLOR(NUM_LOCK_LED_INDEX, 0, 0, 0);
        }
    }
#else
#    warning "NUM_LOCK_LED_INDEX is not defined!"
#endif // NUM_LOCK_LED_INDEX

    if (get_highest_layer(layer_state) >= 0) {
        uint8_t layer = get_highest_layer(layer_state);

        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];
                if (index >= led_min && index < led_max && index != NO_LED) {
                    const int keycode = keymap_key_to_keycode(layer, (keypos_t){col, row});
                    switch (current_game_mode) {
                        case GAME_MODE_CS2: {
                            switch (keycode) {
                                case KC_W:
                                case KC_A:
                                case KC_S:
                                case KC_D:
                                case KC_LSFT:
                                case KC_LCTL:
                                case KC_SPACE:
                                    rgb_matrix_set_color(index, RGB_CYAN);
                                    break;
                                case KC_3:
                                    rgb_matrix_set_color(index, RGB_MAGENTA);
                                    break;
                                case KC_4:
                                    rgb_matrix_set_color(index, RGB_WHITE);
                                    break;
                                case KC_5:
                                    rgb_matrix_set_color(index, RGB_GREEN);
                                    break;
                                case KC_6:
                                case KC_G:
                                    rgb_matrix_set_color(index, RGB_RED);
                                    break;
                                case KC_7:
                                    rgb_matrix_set_color(index, RGB_YELLOW);
                                    break;
                                case KC_T:
                                case KC_M:
                                case KC_B:
                                case KC_Z:
                                case KC_Y:
                                case KC_U:
                                case KC_8:
                                    rgb_matrix_set_color(index, RGB_ORANGE);
                                    break;
                                case KC_E:
                                case KC_F:
                                case KC_Q:
                                    rgb_matrix_set_color(index, RGB_PURPLE);
                                    break;
                                default:
                                    break;
                            }
                            break;
                        }
                        case GAME_MODE_NONE:
                        default:
                            break;
                    }
                }
            }
        }
    }
    return RESULT_QMK_STOP_PROCESSING;
}
