/* common_overrides.h – header‑only replacement for common key-overrides on Windows/Linux */

#pragma once

#include "quantum.h"

/* ---------------------------------------------------------------------
 * Helper: send Ctrl+kc once, *suppressing* the specified modifier mask.
 * ------------------------------------------------------------------- */
static inline void tap_ctrl_combo_suppress(uint16_t kc, uint8_t suppress_mask) {
    uint8_t saved_mods = get_mods();   // remember current mods
    del_mods(suppress_mask);           // temporarily clear (Alt / Gui)
    tap_code16(LCTL(kc));              // Ctrl + kc
    set_mods(saved_mods);              // restore original mods
}

/* Convenience wrappers */
#define tap_ctrl_combo_no_gui(kc) tap_ctrl_combo_suppress(kc, MOD_MASK_GUI)
#define tap_ctrl_combo_no_alt(kc) tap_ctrl_combo_suppress(kc, MOD_MASK_ALT)

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
            last_overridden_kc = KC_NO;      /* done with this override */
            return false;                    /* swallow release        */
        }
        return true;                         /* not ours → let it through */
    }

    uint8_t mods     = get_mods();
    bool    altHeld  = mods & MOD_MASK_ALT;
    bool    guiHeld  = mods & MOD_MASK_GUI;
    bool    ctrlHeld = mods & MOD_MASK_CTRL;

    /* -------------------------------------------------------------
     * 1) Alt + letters  →  Ctrl + letters  (Alt suppressed!)
     * ----------------------------------------------------------- */
    if (altHeld && !ctrlHeld) {
        switch (keycode) {
            case KC_C: tap_ctrl_combo_no_alt(KC_C); return false;
            case KC_V: tap_ctrl_combo_no_alt(KC_V); return false;
            case KC_X: tap_ctrl_combo_no_alt(KC_X); return false;
            case KC_A: tap_ctrl_combo_no_alt(KC_A); return false;
            case KC_Z: tap_ctrl_combo_no_alt(KC_Z); return false;
            case KC_Y: tap_ctrl_combo_no_alt(KC_Y); return false;
            case KC_W: tap_ctrl_combo_no_alt(KC_W); return false;
            case KC_T: tap_ctrl_combo_no_alt(KC_T); return false;
            case KC_R: tap_ctrl_combo_no_alt(KC_R); return false;
            case KC_F: tap_ctrl_combo_no_alt(KC_F); return false;
            default: break;
        }
    }

    /* -------------------------------------------------------------
     * 2) Win/GUI + arrows / Backspace  →  Ctrl + … (GUI suppressed)
     * ----------------------------------------------------------- */
    if (guiHeld && !ctrlHeld) {
        switch (keycode) {
            case KC_LEFT:  tap_ctrl_combo_no_gui(KC_LEFT);  return false;
            case KC_DOWN:  tap_ctrl_combo_no_gui(KC_DOWN);  return false;
            case KC_UP:    tap_ctrl_combo_no_gui(KC_UP);    return false;
            case KC_RIGHT: tap_ctrl_combo_no_gui(KC_RIGHT); return false;
            case KC_BSPC:  tap_ctrl_combo_no_gui(KC_BSPC);  return false;
            default: break;
        }
    }

    /* Not handled here → let QMK continue. */
    return true;
}
