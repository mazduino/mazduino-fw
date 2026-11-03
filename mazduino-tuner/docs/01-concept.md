# 01. Concept & architecture

## Problem

The TunerStudio menu for Mazduino comes from the `[Menu]` section of the rusEFI INI. It is organized around
rusEFI's development history: many groups, technical labels, and basic features mixed with
experimental ones (for example *Setup*, *Advanced*, *Controller*, *View*). For Mazduino users this layout is hard to follow.

Mazduino Tuner organizes its menu by engine subsystem (Fuel, Ignition, Idle control, Boost control,
Inputs, Outputs, Diagnostics, Tuning, etc.) with short labels.

## Principles

| Layer | Source | Contents |
|---|---|---|
| **Data** | Built firmware INI (`rusefi_<board>.ini`) | Fields, memory offsets, types, units, tables, curves, visibility conditions, serial commands |
| **Placement** | `menu/mazduino-tuner-menu.ini` | Page order, grouping and short labels |
| **Output** | `generated/<board>/` | Final per-board menu (JSON / preview INI / Markdown) |

1. **The INI remains the source of truth.** The layout only references page IDs (`veTableDialog`,
   `triggerConfiguration`, …). No offsets or fields are copied, so nothing can be written to the ECU incorrectly.
2. **Conditions are inherited.** If the layout does not specify a condition, the original INI condition is used
   (`{isInjectionEnabled == 1}`, `uiMode`, etc.). Visibility/enable logic still follows the firmware.
3. **No feature is lost.** Every INI page that is not placed automatically goes into
   **Expert**, grouped by its original TunerStudio menu. The only exception is a page of a feature the board does not have.
4. **Each board shows what it has.** One layout serves all boards. IDs a board's INI lacks are skipped, and pages the
   INI leaves in although the board turns their feature off are hidden through `requires` (see `03-layout-format.md`).
   Empty groups and menus disappear, so a board without an electronic throttle has no E-Throttle menu.
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
3. Display the menu tree from `<hash>.tuner-menu.json`, published beside that INI. If it is not available
   (offline, or firmware built before menus were published), use the `<board>.tuner-menu.json` the app ships with.

## Branch strategy

- The **`mazduino-tuner`** branch is created from `master`.
- Its files are in `mazduino-tuner/`, plus one CI workflow and the menu step in `nightly-release.yaml`, so merging
  back into `master` or rebasing onto `master` will not conflict.
- Firmware changes the tuner needs live on the `mazduino-tuner-fixes` branch of `rusefi-core`, and the `ext/rusefi`
  submodule points there.
