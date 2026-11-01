# Mazduino Tuner: MaxxECU-style menu

This folder supports **Mazduino Tuner**, the Mazduino tuning software whose menu is organized like
MaxxECU MTune (simple and grouped by subsystem), unlike the TunerStudio menu layout from the
rusEFI INI.

The firmware, INI, and TunerStudio are **unchanged**. This folder only adds:

- A **menu layout** (`menu/mazduino-tuner-menu.ini`) that defines where pages are placed.
- A **generator** (`tools/gen_tuner_menu.sh`) that combines the layout with the built INI
  into a ready-to-use menu (JSON for the app, preview INI for TunerStudio, Markdown for review).

Every INI page with no MaxxECU equivalent is automatically placed in the **Expert** menu, so
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
│   └── gen_all_from_gh_pages.sh  ← generate all boards from nightly INIs
├── generated/<board>/         ← generator output (json + md committed, *.tuner.ini ignored)
└── docs/
    ├── 01-konsep.md              ← why & how (architecture, branch)
    ├── 02-struktur-menu.md       ← Mazduino Tuner menu tree vs MaxxECU vs TunerStudio
    ├── 03-format-layout.md       ← layout file syntax
    ├── 04-generator-dan-output.md← generator usage, JSON format, TunerStudio preview, CI
    └── 05-pemeliharaan.md        ← workflow when rusEFI/Mazduino adds features
```

## Branch

This work lives on the **`mazduino-tuner`** branch (created from `master`) so it does not conflict with
other work on `master`/`main`. All new files are in `mazduino-tuner/`, plus one
CI workflow `.github/workflows/mazduino-tuner-menu.yaml`. The `ext/rusefi` submodule is not touched.
