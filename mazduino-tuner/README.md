# Mazduino Tuner: menu gaya MaxxECU

Folder ini mendukung **Mazduino Tuner**, software tuner Mazduino yang menunya disusun seperti
MaxxECU MTune (sederhana dan dikelompokkan per subsistem), berbeda dengan susunan menu TunerStudio
dari INI rusEFI.

Firmware, INI, dan TunerStudio **tidak berubah**. Folder ini hanya menambahkan:

- **Layout menu** (`menu/mazduino-tuner-menu.ini`) yang menentukan penempatan halaman.
- **Generator** (`tools/gen_tuner_menu.sh`) yang menggabungkan layout dengan INI hasil build
  menjadi menu siap pakai (JSON untuk aplikasi, INI preview untuk TunerStudio, Markdown untuk review).

Semua halaman INI yang tidak punya padanan di MaxxECU otomatis masuk menu **Expert**, jadi
tidak ada fitur yang hilang.

## Mulai cepat

```bash
# dari root repo mazduino-fw (Linux, macOS, atau Git Bash di Windows)
mazduino-tuner/tools/gen_tuner_menu.sh path/to/rusefi_mazduino-lite.ini
# -> mazduino-tuner/generated/mazduino-lite/
#      mazduino-lite.tuner-menu.json   (dibaca Mazduino Tuner)
#      mazduino-lite.tuner-menu.md     (review manusia)
#      rusefi_mazduino-lite.tuner.ini  (preview di TunerStudio, tidak di-commit)
```

Generate semua board dari INI nightly terbaru di branch `gh-pages`:

```bash
mazduino-tuner/tools/gen_all_from_gh_pages.sh
```

## Struktur

```
mazduino-tuner/
├── README.md                  ← file ini
├── menu/
│   └── mazduino-tuner-menu.ini   ← SATU-SATUNYA file yang diedit untuk mengubah menu
├── tools/
│   ├── gen_tuner_menu.sh         ← generator per INI
│   ├── gen_tuner_menu.awk        ← logika generator
│   └── gen_all_from_gh_pages.sh  ← generate semua board dari INI nightly
├── generated/<board>/         ← hasil generator (json + md di-commit, *.tuner.ini diabaikan)
└── docs/
    ├── 01-konsep.md              ← kenapa & bagaimana (arsitektur, branch)
    ├── 02-struktur-menu.md       ← pohon menu Mazduino Tuner vs MaxxECU vs TunerStudio
    ├── 03-format-layout.md       ← sintaks file layout
    ├── 04-generator-dan-output.md← cara pakai generator, format JSON, preview TunerStudio, CI
    └── 05-pemeliharaan.md        ← alur kerja saat rusEFI/Mazduino menambah fitur
```

## Branch

Pekerjaan ini ada di branch **`mazduino-tuner`** (dibuat dari `master`) agar tidak bentrok dengan
pekerjaan lain di `master`/`main`. Semua file baru berada di `mazduino-tuner/` ditambah satu
workflow CI `.github/workflows/mazduino-tuner-menu.yaml`. Submodule `ext/rusefi` tidak disentuh.
