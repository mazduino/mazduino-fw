# 01. Concept & architecture

## Problem

The TunerStudio menu for Mazduino comes from the `[Menu]` section of the rusEFI INI. It is organized around
rusEFI's development history: many groups, technical labels, and basic features mixed with
experimental ones (for example *Setup*, *Advanced*, *Controller*, *View*). For Mazduino users this layout is hard to follow.

MaxxECU MTune organizes its menu by engine subsystem (Fuel, Ignition, Idle control, Boost control,
Inputs, Outputs, Diagnostics, Tuning, etc.) with short labels. Mazduino Tuner uses this pattern.

## Principles

| Layer | Source | Contents |
|---|---|---|
| **Data** | Built firmware INI (`rusefi_<board>.ini`) | Fields, memory offsets, types, units, tables, curves, visibility conditions, serial commands |
| **Placement** | `menu/mazduino-tuner-menu.ini` | Page order and grouping, MaxxECU-style labels |
| **Output** | `generated/<board>/` | Final per-board menu (JSON / preview INI / Markdown) |

1. **The INI remains the source of truth.** The layout only references page IDs (`veTableDialog`,
   `triggerConfiguration`, …). No offsets or fields are copied, so nothing can be written to the ECU incorrectly.
2. **Conditions are inherited.** If the layout does not specify a condition, the original INI condition is used
   (`{isInjectionEnabled == 1}`, `uiMode`, etc.). Visibility/enable logic still follows the firmware.
3. **No feature is lost.** Every INI page that is not placed automatically goes into
   **Expert**, grouped by its original TunerStudio menu.
4. **Safe across boards.** IDs that do not exist on a given board (e.g. ETB on Lite) are skipped, and empty
   groups/menus are hidden. One layout is used for all boards.
5. **Firmware and INI are not modified.** The signature stays the same, so the preview INI can be opened in TunerStudio
   to try the new menu without reflashing.

## Data flow

```
ext/rusefi + boards/<board>  ──build──►  rusefi_<board>.ini  ─┐
                                                               ├─► gen_tuner_menu.sh ─► <board>.tuner-menu.json ─► Mazduino Tuner
mazduino-tuner/menu/mazduino-tuner-menu.ini ───────────────────┘                     ├─► <board>.tuner-menu.md   ─► review
                                                                                       └─► rusefi_<board>.tuner.ini ─► TunerStudio preview
```

When Mazduino Tuner connects to the ECU:
1. Read the signature (`S`), then find the matching INI, for example
   `https://mazduino.github.io/mazduino-fw/ini/<branch>/<yyyy>/<mm>/<dd>/<board>/<hash>.ini`.
2. Parse the INI for fields, tables, and channels.
3. Use `<board>.tuner-menu.json` to display the menu tree. If the JSON is not available, run the same generator
   logic in the app with the built-in layout.

## Branch strategy

- The **`mazduino-tuner`** branch is created from `master`.
- Changes only **add** files in `mazduino-tuner/` plus one CI workflow, so merging back into `master`
  or rebasing onto `master` will not conflict.
- The `ext/rusefi` submodule (rusefi-core) is not modified. If tuner-specific firmware changes are needed later
  (for example a new protocol command), make them on a separate branch of `rusefi-core` with the same name.
