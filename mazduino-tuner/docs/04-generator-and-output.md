# 04. Generator & output format

## Requirements

`bash` and `awk` (gawk or mawk, POSIX). Git Bash on Windows is enough; no Docker or Python needed.

## Commands

```bash
# single INI
mazduino-tuner/tools/gen_tuner_menu.sh <rusefi_board.ini> [out_dir] [layout.ini]

# all boards, using the latest nightly INI on gh-pages
mazduino-tuner/tools/gen_all_from_gh_pages.sh [fw_branch]     # default: master
```

Example with a locally built INI (Docker, see the root readme). `build_boards.sh` writes the INI to
`generated/tunerstudio/generated/` in the repo root:

```bash
./build_boards.sh mazduino-lite
mazduino-tuner/tools/gen_tuner_menu.sh generated/tunerstudio/generated/rusefi_mazduino-lite.ini
```

The INI in that folder may be outdated (from the last committed build). Check the `signature` line.
For the latest INI without building, use `gen_all_from_gh_pages.sh`.

Summary on stderr:
```
mazduino-lite: 304 INI items -> 207 placed, 97 Expert, 27 skipped
```
Exit code `1` means the layout is invalid (duplicate ID, `groupChildMenu` without a group, syntax error).

## Output

| File | Purpose | Committed |
|---|---|---|
| `<board>.tuner-menu.json` | Read by the Mazduino Tuner app | yes |
| `<board>.tuner-menu.md` | Reviewing menu changes in PRs | yes |
| `rusefi_<board>.tuner.ini` | Preview in TunerStudio | no (`.gitignore`) |

### JSON format

```json
{
  "generator": "mazduino-tuner/tools/gen_tuner_menu.sh",
  "board": "mazduino-lite",
  "signature": "rusEFI master.2026.10.31.mazduino-lite.3546743249",
  "stats": { "iniItems": 304, "placed": 207, "expert": 97, "skippedNotOnBoard": 27 },
  "menus": [
    {
      "title": "Fuel",
      "visible": "",
      "items": [
        { "type": "group", "title": "Fuel inj general", "visible": "", "items": [
          { "type": "page", "id": "injectorConfig", "label": "Injector configuration",
            "kind": "dialog", "enable": "", "visible": "", "origin": "layout" }
        ]},
        { "type": "page", "id": "primingFuelPulsePanel", "label": "Fuel priming",
          "kind": "dialog", "enable": "1", "visible": "uiMode == 0 || uiMode == 1", "origin": "layout" },
        { "type": "separator" }
      ]
    }
  ]
}
```

| Field | Meaning |
|---|---|
| `signature` | Firmware signature of the source INI. The app must use the JSON whose signature matches the ECU |
| `type` | `page`, `group`, `separator` |
| `id` | Dialog/table/curve ID in the INI. Open the page by looking up this definition in the INI |
| `kind` | `dialog` (`[UserDefined]`), `table` (`[TableEditor]`), `table3d` (3D map of a table), `curve` (`[CurveEditor]`), `other` (special panel/help) |
| `enable` / `visible` | TunerStudio condition expression (variables from `[Constants]`/`[PcVariables]`). Empty means always |
| `origin` | `layout` (placed manually) or `expert:<original TS menu>` |

## Preview in TunerStudio

`rusefi_<board>.tuner.ini` is identical to the firmware INI except for the `[Menu]` section. The signature is unchanged,
so the file can be used in an existing TunerStudio project:

1. Generate the INI for the board in use.
2. In TunerStudio: *File → Project Properties → ECU Definition (.ini)* → select `rusefi_<board>.tuner.ini`
   (or copy it to `projectCfg/mainController.ini`).
3. The TunerStudio menubar will show the Mazduino Tuner layout. Restore the original INI for the standard menu.

Tunes (`.msq`) are not affected because the memory layout is exactly the same.

## CI

`.github/workflows/mazduino-tuner-menu.yaml` runs on push to the `mazduino-tuner` branch, on PRs that
touch `mazduino-tuner/**`, or manually. The workflow:
1. Generates the menu for all boards from the nightly INIs on gh-pages.
2. Fails if the layout is invalid.
3. Warns if the committed `generated/` no longer matches the latest output.
4. Uploads the output as the `mazduino-tuner-menu` artifact.

The nightly release workflow is **not changed**. If the JSON later needs to be published alongside the INI on gh-pages
(`.../<hash>.tuner-menu.json`), add a `gen_tuner_menu.sh` call to the
"Extract INI files from bundles" step in `nightly-release.yaml`.
