#include QMK_KEYBOARD_H
#include "version.h"
#define MOON_LED_LEVEL LED_LEVEL
#include "os_detection.h"          // custom: host‑OS detection
#ifndef ZSA_SAFE_RANGE
#define ZSA_SAFE_RANGE SAFE_RANGE
#endif

enum custom_keycodes {
  RGB_SLD = ZSA_SAFE_RANGE,
  HSV_0_255_255,
  HSV_74_255_255,
  HSV_169_255_255,
  OS_MAC_WIN_LANG_CHANGE,          // Alt+Shift (Win) / Ctrl+Space (macOS)
  ST_MACRO_0,
  ST_MACRO_1,
  ST_MACRO_2,
  ST_MACRO_3,
};



#define DUAL_FUNC_0 LT(13, KC_0)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_voyager(
    KC_GRAVE,       KC_1,           KC_2,           KC_3,           KC_4,           KC_5,                                           KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_MINUS,       
    KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,                                           KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           DUAL_FUNC_0,    
    KC_LEFT_SHIFT,  KC_A,           KC_S,           KC_D,           KC_F,           KC_G,                                           KC_H,           KC_J,           KC_K,           KC_L,           LT(3, KC_SCLN), MT(MOD_RSFT, KC_QUOTE),
    KC_LEFT_CTRL,   KC_Z,           KC_X,           KC_C,           MT(MOD_LALT, KC_V),KC_B,                                           KC_N,           KC_M,           KC_COMMA,       KC_DOT,         KC_SLASH,       KC_BSLS,        
                                                    LT(2, KC_ENTER),MT(MOD_LGUI, KC_ESCAPE),                                LT(1, KC_BSPC), MT(MOD_LSFT, KC_SPACE)
  ),
  [1] = LAYOUT_voyager(
    KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F6,                                          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         KC_F12,         
    KC_TRANSPARENT, KC_TRANSPARENT, ST_MACRO_0,     KC_LPRN,        KC_RPRN,        ST_MACRO_1,                                     LALT(KC_LEFT),  LALT(KC_DOWN),  LALT(KC_UP),    LALT(KC_RIGHT), KC_TRANSPARENT, KC_BSPC,        
    KC_TRANSPARENT, KC_TRANSPARENT, LGUI(LCTL(LSFT(KC_SPACE))),KC_LBRC,        KC_RBRC,        ST_MACRO_2,                                     KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT,       KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_LABK,        KC_RABK,        KC_LCBR,        KC_RCBR,        ST_MACRO_3,                                     KC_HOME,        LGUI(KC_DOWN),  LGUI(KC_UP),    KC_END,         KC_TRANSPARENT, KC_TRANSPARENT, 
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [2] = LAYOUT_voyager(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_QUES,        KC_PLUS,        KC_LPRN,        KC_RPRN,        KC_DQUO,                                        KC_AMPR,        KC_CIRC,        KC_AT,          KC_HASH,        KC_DLR,         KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_EXLM,        KC_ASTR,        KC_LBRC,        KC_RBRC,        KC_EQUAL,                                       KC_PIPE,        KC_COLN,        KC_TILD,        KC_PERC,        KC_TRANSPARENT, KC_ENTER,       
    KC_TRANSPARENT, KC_LABK,        KC_RABK,        KC_LCBR,        KC_RCBR,        KC_QUOTE,                                       KC_MINUS,       KC_UNDS,        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [3] = LAYOUT_voyager(
    RGB_TOG,        TOGGLE_LAYER_COLOR,RGB_MODE_FORWARD,RGB_SLD,        RGB_VAD,        RGB_VAI,                                        KC_AUDIO_VOL_UP,KC_AUDIO_MUTE,  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,        
    KC_TRANSPARENT, RGB_HUD,        RGB_HUI,        RGB_SAD,        RGB_SAI,        KC_TRANSPARENT,                                 KC_AUDIO_VOL_DOWN,KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_MEDIA_PLAY_PAUSE,KC_MEDIA_PREV_TRACK,KC_MEDIA_NEXT_TRACK,KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, HSV_0_255_255,  HSV_74_255_255, HSV_169_255_255,                                KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 OS_MAC_WIN_LANG_CHANGE, KC_TRANSPARENT
  ),
};




extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [1] = { {236,226,161}, {236,226,161}, {236,226,161}, {236,226,161}, {236,226,161}, {236,226,161}, {0,0,0}, {0,0,0}, {169,255,84}, {139,226,161}, {139,226,161}, {169,255,84}, {0,0,0}, {0,0,0}, {169,255,84}, {139,226,161}, {139,226,161}, {169,255,84}, {0,0,0}, {139,226,161}, {139,226,161}, {139,226,161}, {139,226,161}, {169,255,84}, {0,0,0}, {0,0,0}, {236,226,161}, {236,226,161}, {236,226,161}, {236,226,161}, {236,226,161}, {236,226,161}, {0,151,211}, {0,151,211}, {0,151,211}, {0,151,211}, {0,0,0}, {188,255,255}, {11,201,168}, {11,201,168}, {11,201,168}, {11,201,168}, {0,0,0}, {0,0,0}, {11,201,168}, {0,151,211}, {0,151,211}, {11,201,168}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [2] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {11,201,168}, {11,201,168}, {139,226,161}, {139,226,161}, {85,226,161}, {0,0,0}, {11,201,168}, {11,201,168}, {139,226,161}, {139,226,161}, {11,201,168}, {0,0,0}, {139,226,161}, {139,226,161}, {139,226,161}, {139,226,161}, {85,226,161}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {11,201,168}, {85,226,161}, {85,226,161}, {85,226,161}, {85,226,161}, {0,0,0}, {11,201,168}, {11,201,168}, {85,226,161}, {85,226,161}, {85,226,161}, {188,255,255}, {85,226,161}, {85,226,161}, {85,226,161}, {85,226,161}, {85,226,161}, {85,226,161}, {0,0,0}, {0,0,0} },

    [3] = { {0,245,245}, {0,245,245}, {74,255,255}, {0,245,245}, {0,245,245}, {0,245,245}, {0,0,0}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {236,226,161}, {236,226,161}, {236,226,161}, {0,0,0}, {0,0,0}, {236,226,161}, {236,226,161}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {236,226,161}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {139,226,161}, {139,226,161}, {139,226,161}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {74,255,255}, {0,0,0} },

};

void set_layer_color(int layer) {
  for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

bool rgb_matrix_indicators_user(void) {
  if (rawhid_state.rgb_control) {
      return false;
  }
  if (keyboard_config.disable_layer_led) { return false; }
  switch (biton32(layer_state)) {
    case 1:
      set_layer_color(1);
      break;
    case 2:
      set_layer_color(2);
      break;
    case 3:
      set_layer_color(3);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
  return true;
}

// ────────────────────────────────────────────────────────────────────
// Host‑OS detection, automatic Alt⌥/Gui⌘ swap and custom key overrides
// ────────────────────────────────────────────────────────────────────

static const key_override_t KO_GUI_C   = ko_make_basic(MOD_MASK_GUI, KC_C,   LCTL(KC_C));   // copy
static const key_override_t KO_GUI_V   = ko_make_basic(MOD_MASK_GUI, KC_V,   LCTL(KC_V));   // paste
static const key_override_t KO_GUI_X   = ko_make_basic(MOD_MASK_GUI, KC_X,   LCTL(KC_X));   // cut
static const key_override_t KO_GUI_A   = ko_make_basic(MOD_MASK_GUI, KC_A,   LCTL(KC_A));   // select-all
static const key_override_t KO_GUI_Z   = ko_make_basic(MOD_MASK_GUI, KC_Z,   LCTL(KC_Z));   // undo
static const key_override_t KO_GUI_Y   = ko_make_basic(MOD_MASK_GUI, KC_Y,   LCTL(KC_Y));   // redo
static const key_override_t KO_GUI_W   = ko_make_basic(MOD_MASK_GUI, KC_W,   LCTL(KC_W));   // close-tab
static const key_override_t KO_GUI_T   = ko_make_basic(MOD_MASK_GUI, KC_T,   LCTL(KC_T));   // new-tab
static const key_override_t KO_GUI_R   = ko_make_basic(MOD_MASK_GUI, KC_R,   LCTL(KC_R));   // reload-tab
static const key_override_t KO_GUI_F   = ko_make_basic(MOD_MASK_GUI, KC_F,   LCTL(KC_F));   // find/search

static const key_override_t KO_ALT_L   = ko_make_basic(MOD_MASK_ALT, KC_LEFT,  LCTL(KC_LEFT));  // word-left
static const key_override_t KO_ALT_D   = ko_make_basic(MOD_MASK_ALT, KC_DOWN, LCTL(KC_DOWN)); // word-down
static const key_override_t KO_ALT_U   = ko_make_basic(MOD_MASK_ALT, KC_UP, LCTL(KC_UP)); // word-up
static const key_override_t KO_ALT_R   = ko_make_basic(MOD_MASK_ALT, KC_RIGHT, LCTL(KC_RIGHT)); // word-right
static const key_override_t KO_ALT_BSP = ko_make_basic(MOD_MASK_ALT, KC_BSPC,  LCTL(KC_BSPC));  // delete-prev-word

static const key_override_t *windows_overrides[] = {
    &KO_GUI_C, &KO_GUI_V, &KO_GUI_X, &KO_GUI_A,
    &KO_GUI_Z, &KO_GUI_Y, &KO_GUI_W, &KO_GUI_T, &KO_GUI_R, &KO_GUI_F,
    &KO_ALT_L, &KO_ALT_D, &KO_ALT_U, &KO_ALT_R, &KO_ALT_BSP,
    NULL
};

// This is what QMK pays attention to when searching for overrides.
__attribute__((weak)) const key_override_t **key_overrides = NULL;

bool process_detected_host_os_user(os_variant_t os) {
    bool is_macos = os == OS_MACOS || os == OS_IOS;
    // Swap command and option on Windows/Linux
    keymap_config.swap_lalt_lgui = !is_macos;
    // Apply key overrides on Windows/Linux
    key_overrides = is_macos ? NULL : windows_overrides;
    return true;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case OS_MAC_WIN_LANG_CHANGE:
    if (!record->event.pressed) return false;
    switch (detected_host_os()) {
      case OS_MACOS:
      case OS_IOS:
        tap_code16(LCTL(KC_SPC));
        break;
      default:
        register_code(KC_LALT);
        register_code(KC_LSFT);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        break;
    }
    return false;
    case ST_MACRO_0:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_W))));
    }
    break;
    case ST_MACRO_1:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_T))));
    }
    break;
    case ST_MACRO_2:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_G))));
    }
    break;
    case ST_MACRO_3:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_E))));
    }
    break;

    case DUAL_FUNC_0:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(KC_LBRC);
        } else {
          unregister_code16(KC_LBRC);
        }
      } else {
        if (record->event.pressed) {
          register_code16(KC_RBRC);
        } else {
          unregister_code16(KC_RBRC);
        }  
      }  
      return false;
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
    case HSV_0_255_255:
      if (record->event.pressed) {
        rgblight_mode(1);
        rgblight_sethsv(0,255,255);
      }
      return false;
    case HSV_74_255_255:
      if (record->event.pressed) {
        rgblight_mode(1);
        rgblight_sethsv(74,255,255);
      }
      return false;
    case HSV_169_255_255:
      if (record->event.pressed) {
        rgblight_mode(1);
        rgblight_sethsv(169,255,255);
      }
      return false;
  }
  return true;
}


