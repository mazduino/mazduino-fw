# 05. Pemeliharaan

## Saat rusEFI / Mazduino menambah atau mengubah halaman

Tidak ada yang rusak. Halaman baru otomatis muncul di **Expert**. Alur kerjanya:

1. Update branch: `git fetch origin && git rebase origin/master` (atau merge).
2. Generate ulang: `mazduino-tuner/tools/gen_all_from_gh_pages.sh`.
3. Lihat diff `generated/*/*.tuner-menu.md`. Halaman baru akan terlihat di bagian `## Expert`.
4. Bila halaman itu punya padanan di MaxxECU, pindahkan ke menu yang tepat di
   `menu/mazduino-tuner-menu.ini`, generate ulang, lalu commit layout dan `generated/`.

Bila ID halaman di-rename upstream, ID lama akan muncul di daftar "ID layout yang tidak ada di board ini"
untuk **semua** board, dan halaman dengan ID baru masuk Expert. Perbaiki ID-nya di layout.

## Checklist mengubah layout

- [ ] Label pendek, gaya MaxxECU, bahasa Inggris (konsisten dengan help firmware).
- [ ] Kondisi tidak ditulis kecuali benar-benar perlu ditimpa.
- [ ] Generator lolos untuk semua board (`gen_all_from_gh_pages.sh` exit 0).
- [ ] `generated/` ikut di-commit.
- [ ] Bila menambah/memindah menu utama, perbarui tabel di `02-struktur-menu.md`.

## Konvensi commit

```
mazduino-tuner: <ringkasan>

contoh:
mazduino-tuner: move misfire detection from Expert to Limits
mazduino-tuner: regenerate menus for nightly 2026-11-05
```

## Referensi

- MaxxECU MTune 1.161: pohon menu lengkap dan pemetaannya ada di project riset
  `Documents/Mazduino-Tuner` (`docs/02-mtune-settings-menu.md`, `docs/05-menu-mapping.md`).
- Sintaks `[Menu]` TunerStudio: section `[Menu]` di INI firmware mana pun.
