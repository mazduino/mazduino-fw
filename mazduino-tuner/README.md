# Mazduino Tuner menu layout

This folder supports **Mazduino Tuner**, the Mazduino tuning software whose menu is short and grouped by engine subsystem,
unlike the TunerStudio menu layout from the rusEFI INI.

The firmware, INI, and TunerStudio are **unchanged**. This folder only adds:

- A **menu layout** (`menu/mazduino-tuner-menu.ini`) that defines where pages are placed.
- A **generator** (`tools/gen_tuner_menu.sh`) that combines the layout with the built INI
  into a ready-to-use menu (JSON for the app, preview INI for TunerStudio, Markdown for review).

Every INI page that the layout does not place is automatically put in the **Expert** menu, so
no feature is lost.

## Quick start

```bash
# from the mazduino-fw repo root (Linux, macOS, or Git Bash on Windows)
mazduino-tuner/tools/gen_tuner_menu.sh path/to/rusefi_mazduino-lite.ini
# -> mazduino-tuner/generated/mazduino-lite/
#      mazduino-lite.tuner-menu.json   (read by Mazduino Tuner)
#      mazduino-lite.tuner-menu.md     (human review)
#      rusefi_mazduino-lite.tuner.ini  (TunerStudio preview, not committed)
```

Generate all boards from the latest nightly INI on the `gh-pages` branch:

```bash
mazduino-tuner/tools/gen_all_from_gh_pages.sh
```

## Structure

```
mazduino-tuner/
├── README.md                  ← this file
├── menu/
│   └── mazduino-tuner-menu.ini   ← the ONLY file to edit to change the menu
├── tools/
│   ├── gen_tuner_menu.sh         ← per-INI generator
│   ├── gen_tuner_menu.awk        ← generator logic
│   ├── gen_all_from_gh_pages.sh  ← generate all boards from nightly INIs
│   ├── board_flags.sh            ← the feature defines a board sets
│   ├── gen_board_features.sh     ← write boards/FEATURES.md from them
│   └── check_generated.sh        ← CI gate: generated/ and FEATURES.md are up to date
├── generated/<board>/         ← generator output (json + md committed, *.tuner.ini ignored)
└── docs/
    ├── 01-concept.md             ← why & how (architecture, branch)
    ├── 02-menu-structure.md      ← Mazduino Tuner menu tree vs TunerStudio
    ├── 03-layout-format.md       ← layout file syntax
    ├── 04-generator-and-output.md← generator usage, JSON format, TunerStudio preview, CI
    └── 05-maintenance.md          ← workflow when rusEFI/Mazduino adds features
```

## Branch

This work lives on the **`mazduino-tuner`** branch (created from `master`) so it does not conflict with
other work on `master`/`main`. Its files are in `mazduino-tuner/`, plus the CI workflow
`.github/workflows/mazduino-tuner-menu.yaml` and the menu step in `nightly-release.yaml`. The `ext/rusefi`
submodule points at the `mazduino-tuner-fixes` branch of rusefi-core.
