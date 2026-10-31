# 01. Konsep & arsitektur

## Masalah

Menu TunerStudio untuk Mazduino berasal dari section `[Menu]` INI rusEFI. Menu ini disusun mengikuti
sejarah pengembangan rusEFI: banyak grup, label teknis, dan fitur dasar bercampur dengan fitur
eksperimen (misalnya *Setup*, *Advanced*, *Controller*, *View*). Untuk pengguna Mazduino, susunan ini sulit dipahami.

MaxxECU MTune menyusun menu per subsistem mesin (Fuel, Ignition, Idle control, Boost control,
Inputs, Outputs, Diagnostics, Tuning, dll.) dengan label yang singkat. Mazduino Tuner memakai pola ini.

## Prinsip

| Lapisan | Sumber | Isi |
|---|---|---|
| **Data** | INI firmware hasil build (`rusefi_<board>.ini`) | Field, offset memori, tipe, satuan, tabel, kurva, kondisi tampil, perintah serial |
| **Penempatan** | `menu/mazduino-tuner-menu.ini` | Urutan dan pengelompokan halaman, label gaya MaxxECU |
| **Hasil** | `generated/<board>/` | Menu final per board (JSON / INI preview / Markdown) |

1. **INI tetap jadi sumber kebenaran.** Layout hanya merujuk ID halaman (`veTableDialog`,
   `triggerConfiguration`, …). Tidak ada offset atau field yang disalin, sehingga tidak bisa salah tulis ke ECU.
2. **Kondisi diwarisi.** Kalau layout tidak menulis kondisi, kondisi asli dari INI dipakai
   (`{isInjectionEnabled == 1}`, `uiMode`, dll.). Logika tampil/aktif tetap mengikuti firmware.
3. **Tidak ada fitur yang hilang.** Semua halaman INI yang tidak ditempatkan otomatis masuk
   **Expert**, dikelompokkan menurut menu TunerStudio asalnya.
4. **Aman lintas board.** ID yang tidak ada di board tertentu (mis. ETB di Lite) dilewati, dan grup/menu
   kosong disembunyikan. Satu layout dipakai untuk semua board.
5. **Firmware dan INI tidak diubah.** Signature tetap sama, jadi INI preview bisa dibuka di TunerStudio
   untuk mencoba menu baru tanpa reflash.

## Alur data

```
ext/rusefi + boards/<board>  ──build──►  rusefi_<board>.ini  ─┐
                                                               ├─► gen_tuner_menu.sh ─► <board>.tuner-menu.json ─► Mazduino Tuner
mazduino-tuner/menu/mazduino-tuner-menu.ini ───────────────────┘                     ├─► <board>.tuner-menu.md   ─► review
                                                                                       └─► rusefi_<board>.tuner.ini ─► preview TunerStudio
```

Mazduino Tuner saat terhubung ke ECU:
1. Baca signature (`S`), lalu cari INI yang cocok, misalnya
   `https://mazduino.github.io/mazduino-fw/ini/<branch>/<yyyy>/<mm>/<dd>/<board>/<hash>.ini`.
2. Parse INI untuk field, tabel, dan channel.
3. Pakai `<board>.tuner-menu.json` untuk menampilkan pohon menu. Kalau JSON tidak tersedia, jalankan logika
   generator yang sama di aplikasi dengan layout bawaan.

## Strategi branch

- Branch **`mazduino-tuner`** dibuat dari `master`.
- Perubahan hanya **menambah** file di `mazduino-tuner/` dan satu workflow CI, sehingga merge balik ke `master`
  atau rebase dari `master` tidak akan konflik.
- Submodule `ext/rusefi` (rusefi-core) tidak diubah. Kalau nanti dibutuhkan perubahan firmware khusus
  tuner (misalnya perintah protokol baru), lakukan di branch terpisah pada `rusefi-core` dengan nama yang sama.
