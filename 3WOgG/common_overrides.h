/* common_overrides.h – header‑only replacement for common key-overrides on Windows/Linux. Assumes LGUI/LALT swapping! */

#pragma once

#include "quantum.h"

/* QMK packs modifier bits in the high byte: 0b000xxxxx kkkkkkkk
 * where xxxxx are the 5 one-shot/L/R mods (LSFT, LCTL, etc.).        */
static inline uint8_t  mods_from_keycode(uint16_t kc) { return (kc >> 8) & 0x1F; }
static inline uint16_t strip_qmk_mods   (uint16_t kc) { return kc & 0xFF;        }

/* Helper: if this is a dual-role key, the mods are not active, so we should ignore them. */
static inline uint8_t effective_mods(uint16_t kc) {
    return (IS_QK_MOD_TAP(kc) || IS_QK_LAYER_TAP(kc))
           ? 0
           : mods_from_keycode(kc);
}

/* Helper: if this is a dual-role key, return its tap kc; otherwise return keycode */
static inline uint16_t base_key(uint16_t kc) {
    /* Unwrap dual-role keys ---------------------------------- */
    if (IS_QK_MOD_TAP(kc))   return QK_MOD_TAP_GET_TAP_KEYCODE(kc);
    if (IS_QK_LAYER_TAP(kc)) return QK_LAYER_TAP_GET_TAP_KEYCODE(kc);

    /* Unwrap QMK's mod-prefixed keycodes, e.g. LALT(KC_LEFT) -- */
    return kc & 0xFF;   /* just strip the high-byte modifier bits */
}

/* Does this kc behave as Alt? Assumes LGUI/LALT swapping! */
static inline bool is_alt_keycode(uint16_t kc) {
    if (kc == KC_LGUI || kc == KC_RGUI) return true;
    if (IS_QK_MOD_TAP(kc)) {
        uint8_t mt_mods = QK_MOD_TAP_GET_MODS(kc);
        return mt_mods & (MOD_LGUI | MOD_RGUI);
    }
    return false;
}

/* ------------------------------------------------------------------ */
/* State we need between press and release                            */
/* ------------------------------------------------------------------ */
static uint16_t active_override_kc  = KC_NO;   // the key we converted
static uint8_t  restore_mods_cached = 0;       // mods to restore later
static bool     prev_overridden = false;       // whether the previously handled key was overridden

/* ---------------------------------------------------------------------
 * Core hook – call this from process_record_user().
 * Returns false when the keypress/release has been fully handled.
 * ------------------------------------------------------------------- */
static inline bool process_common_override(uint16_t keycode, keyrecord_t *record) {
    /* ------------------------- PRESS branch ------------------------- */
    uint8_t real_mods = get_mods();         /* physical modifiers held  */
    uint8_t qmk_mods  = effective_mods(keycode);
    uint8_t all_mods  = real_mods | qmk_mods;
    uint16_t plain_kc = base_key(keycode);

    /* ---------------------- Handle RELEASE first -------------------- */
    if (!record->event.pressed) {
        if (keycode == active_override_kc) {
            /* Drop the Ctrl+key we registered on press                 */
            unregister_code16(LCTL(plain_kc));
            /* Give the user’s real mods back (they’re still physically held) */
            register_mods(restore_mods_cached);
            active_override_kc  = KC_NO;
            restore_mods_cached = 0;
            prev_overridden = true;
            return false;
        }
        // Stop treating ALT as a key press after overrides to prevent flashing
        if (prev_overridden && is_alt_keycode(keycode)) {
            neutralize_flashing_modifiers(MOD_BIT(KC_LEFT_ALT));
        }
        prev_overridden = false;
        return true;
    }

    bool altHeld  = all_mods & MOD_MASK_ALT;
    bool ctrlHeld = all_mods & MOD_MASK_CTRL;

    /* ===== Alt (without Ctrl) overrides that should become Ctrl ===== */
    if (altHeld && !ctrlHeld) {
        switch (plain_kc) {
            /* letters, navigation & editing & utility keys --------------------- */
            case KC_C: case KC_V: case KC_X: case KC_A: case KC_Z:
            case KC_Y: case KC_W: case KC_T: case KC_R: case KC_F:
            case KC_LEFT: case KC_DOWN: case KC_UP: case KC_RIGHT:
            case KC_BSPC: case KC_SLSH: case KC_L: case KC_S: case KC_SPC:
                /* 1. Neutralise & lift all currently active mods so the
                 *    host never sees Alt (avoids Alt-menus etc.)       */
                neutralize_flashing_modifiers(MOD_BIT(KC_LEFT_ALT));
                unregister_mods(MOD_MASK_ALT);

                /* 2. Hold Ctrl+plain_kc until the key is released      */
                register_code16(LCTL(plain_kc));

                /* 3. Remember what to do on release                    */
                active_override_kc  = keycode;
                restore_mods_cached = real_mods;   /* only physical mods */

                return false;   /* event fully processed */
            default:
                break;
        }
    }

    /* No override applied – let QMK handle normally                    */
    active_override_kc = KC_NO;
    prev_overridden = false;
    return true;
}
