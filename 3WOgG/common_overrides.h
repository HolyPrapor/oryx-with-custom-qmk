/* common_overrides.h – header‑only replacement for common key-overrides on Windows/Linux */

#pragma once

#include "quantum.h"

/* ---------------------------------------------------------------------
 * Helper: send Ctrl+kc once, suppressing and then restoring the specified mods.
 * ------------------------------------------------------------------- */
static inline void tap_ctrl_combo_suppress(uint16_t kc, uint8_t current_mods) {
    del_mods(current_mods);
    tap_code16(LCTL(kc));
    set_mods(current_mods);
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

    uint8_t mods     = get_mods();
    bool    altHeld  = mods & MOD_MASK_ALT;
    bool    ctrlHeld = mods & MOD_MASK_CTRL;


    /* ======================================================
     * Word/para navigation – Alt + arrows/Bksp → Ctrl
     * Copy/Paste etc. – Alt + letters → Ctrl
     * ==================================================== */
    if (altHeld && !ctrlHeld) {
        switch (keycode) {
            case KC_C: case KC_V: case KC_X: case KC_A: case KC_Z:
            case KC_Y: case KC_W: case KC_T: case KC_R: case KC_F:
            case KC_LEFT: case KC_DOWN: case KC_UP: case KC_RIGHT: case KC_BSPC:
                tap_ctrl_combo_suppress(keycode, mods);
                last_overridden = keycode;
                return false;
            default:
                break;
        }
    }

    last_overridden = KC_NO;
    return true;
}
