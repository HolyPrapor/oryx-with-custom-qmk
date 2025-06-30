/* common_overrides.h – header‑only replacement for common key-overrides on Windows/Linux */

#pragma once

#include "quantum.h"

/* QMK packs modifier bits in the high byte: 0b000xxxxx kkkkkkkk
 * where xxxxx are the 5 one-shot/L/R mods (LSFT, LCTL, etc.).        */
static inline uint8_t  mods_from_keycode(uint16_t kc) { return (kc >> 8) & 0x1F; }
static inline uint16_t strip_qmk_mods   (uint16_t kc) { return kc & 0xFF;        }

/* Helper: if this is a dual-role key, return its tap kc; otherwise return keycode */
static inline uint16_t base_key(uint16_t kc) {
    /* Unwrap dual-role keys ---------------------------------- */
    if (IS_QK_MOD_TAP(kc))   return QK_MOD_TAP_GET_TAP_KEYCODE(kc);
    if (IS_QK_LAYER_TAP(kc)) return QK_LAYER_TAP_GET_TAP_KEYCODE(kc);

    /* Unwrap QMK's mod-prefixed keycodes, e.g. LALT(KC_LEFT) -- */
    return kc & 0xFF;   /* just strip the high-byte modifier bits */
}

/* ---------------------------------------------------------------------
 * Helper: send Ctrl+kc once, suppressing and then restoring the specified mods.
 * ------------------------------------------------------------------- */
static inline void tap_ctrl_combo_suppress(uint16_t kc, uint8_t suppress_mods, uint8_t restore_mods) {
    del_mods(suppress_mods);
    tap_code16(LCTL(kc));
    set_mods(restore_mods);
}

/* ---------------------------------------------------------------------
 * Core hook – call this from process_record_user().
 * Returns false when the keypress/release has been fully handled.
 * ------------------------------------------------------------------- */
static inline bool process_common_override(uint16_t keycode, keyrecord_t *record) {
    /* Remember if the *previous press* was converted → we must eat its release */
    static uint16_t last_overridden_kc = KC_NO;

    /* ---------------------------------------------------------
     * Handle key‑RELEASE first: swallow only if we converted the
     * matching press (prevents stuck keys / key‑repeat spam).
     * ------------------------------------------------------- */
    if (!record->event.pressed) {
        if (keycode == last_overridden_kc) {
            last_overridden_kc = KC_NO;
            return false;
        }
        return true;
    }

    uint8_t real_mods   = get_mods();                  // keys the user is holding
    uint8_t qmk_mods    = mods_from_keycode(keycode);  // mods baked into LALT(...)
    uint8_t all_mods    = real_mods | qmk_mods;        // treat them the same
    
    bool altHeld  = all_mods & MOD_MASK_ALT;
    // bool guiHeld  = all_mods & MOD_MASK_GUI;
    bool ctrlHeld = all_mods & MOD_MASK_CTRL;
    
    uint16_t plain_kc = base_key(keycode);

    /* ======================================================
     * Word/para navigation – Alt + arrows/Bksp → Ctrl
     * Copy/Paste etc. – Alt + letters → Ctrl
     * ==================================================== */
    if (altHeld && !ctrlHeld) {
        switch (plain_kc) {
            case KC_C: case KC_V: case KC_X: case KC_A: case KC_Z:
            case KC_Y: case KC_W: case KC_T: case KC_R: case KC_F:
            case KC_LEFT: case KC_DOWN: case KC_UP: case KC_RIGHT: case KC_BSPC:
                tap_ctrl_combo_suppress(plain_kc, all_mods, real_mods);
                last_overridden_kc = keycode;
                return false;
            default:
                break;
        }
    }

    last_overridden_kc = KC_NO;
    return true;
}
