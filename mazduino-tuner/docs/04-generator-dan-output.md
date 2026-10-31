# 04. Generator & format output

## Kebutuhan

`bash` dan `awk` (gawk atau mawk, POSIX). Cukup Git Bash di Windows, tidak perlu Docker atau Python.

## Perintah

```bash
# satu INI
mazduino-tuner/tools/gen_tuner_menu.sh <rusefi_board.ini> [out_dir] [layout.ini]

# semua board, memakai INI nightly terbaru di gh-pages
mazduino-tuner/tools/gen_all_from_gh_pages.sh [fw_branch]     # default: master
```

Contoh dengan INI hasil build lokal (Docker, lihat readme root). `build_boards.sh` menulis INI ke
`generated/tunerstudio/generated/` di root repo:

```bash
./build_boards.sh mazduino-lite
mazduino-tuner/tools/gen_tuner_menu.sh generated/tunerstudio/generated/rusefi_mazduino-lite.ini
```

INI yang ada di folder itu bisa sudah lama (dari build terakhir yang di-commit). Cek baris `signature`.
Untuk INI terbaru tanpa build, pakai `gen_all_from_gh_pages.sh`.

Ringkasan di stderr:
```
mazduino-lite: 304 item INI -> 207 ditempatkan, 97 Expert, 27 dilewati
```
Exit code `1` berarti layout tidak valid (ID dobel, `groupChildMenu` tanpa grup, sintaks salah).

## Output

| File | Untuk | Di-commit |
|---|---|---|
| `<board>.tuner-menu.json` | Dibaca aplikasi Mazduino Tuner | ya |
| `<board>.tuner-menu.md` | Review perubahan menu di PR | ya |
| `rusefi_<board>.tuner.ini` | Preview di TunerStudio | tidak (`.gitignore`) |

### Format JSON

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

| Field | Arti |
|---|---|
| `signature` | Signature firmware INI sumber. Aplikasi harus memakai JSON dengan signature yang sama dengan ECU |
| `type` | `page`, `group`, `separator` |
| `id` | ID dialog/tabel/kurva di INI. Buka halaman dengan mencari definisi ini di INI |
| `kind` | `dialog` (`[UserDefined]`), `table` (`[TableEditor]`), `table3d` (map 3D dari tabel), `curve` (`[CurveEditor]`), `other` (panel/help khusus) |
| `enable` / `visible` | Ekspresi kondisi TunerStudio (variabel dari `[Constants]`/`[PcVariables]`). Kosong berarti selalu |
| `origin` | `layout` (ditempatkan manual) atau `expert:<menu TS asal>` |

## Preview di TunerStudio

`rusefi_<board>.tuner.ini` identik dengan INI firmware kecuali section `[Menu]`. Signature tetap sama,
sehingga file ini bisa dipakai di project TunerStudio yang sudah ada:

1. Generate INI untuk board yang dipakai.
2. Di TunerStudio: *File → Project Properties → ECU Definition (.ini)* → pilih `rusefi_<board>.tuner.ini`
   (atau salin ke `projectCfg/mainController.ini`).
3. Menubar TunerStudio akan menampilkan susunan Mazduino Tuner. Kembalikan INI asli untuk menu standar.

Tune (`.msq`) tidak terpengaruh karena layout memori sama persis.

## CI

`.github/workflows/mazduino-tuner-menu.yaml` berjalan saat push ke branch `mazduino-tuner`, saat PR yang
menyentuh `mazduino-tuner/**`, atau secara manual. Workflow ini:
1. Generate menu untuk semua board dari INI nightly di gh-pages.
2. Gagal jika layout tidak valid.
3. Memberi peringatan bila `generated/` yang di-commit sudah tidak sama dengan hasil terbaru.
4. Mengunggah hasil sebagai artifact `mazduino-tuner-menu`.

Workflow nightly release **tidak diubah**. Kalau nanti JSON perlu dipublikasikan bersama INI di gh-pages
(`.../<hash>.tuner-menu.json`), tambahkan pemanggilan `gen_tuner_menu.sh` di step
"Extract INI files from bundles" pada `nightly-release.yaml`.
