# 03. Format file layout (`menu/mazduino-tuner-menu.ini`)

Sintaksnya adalah subset section `[Menu]` TunerStudio, ditambah satu direktif `include`.

## Elemen

| Baris | Arti |
|---|---|
| `menu = "Judul"` | Menu utama (level 1, satu node di pohon kiri / menubar) |
| `subMenu = <id>[, "Label"][, kondisi]` | Halaman langsung di bawah menu |
| `groupMenu = "Judul"` | Grup di dalam menu (level 2) |
| `groupChildMenu = <id>[, "Label"][, kondisi]` | Halaman di dalam grup (level 3) |
| `subMenu = std_separator` | Garis pemisah |
| `include = unplaced` | Sisipkan semua halaman INI yang belum ditempatkan (dipakai di menu **Expert**) |
| `; komentar` | Komentar (di luar tanda kutip) |

`<id>` adalah nama dialog/tabel/kurva di INI firmware. Cari di `[UserDefined]` (`dialog = id`),
`[TableEditor]` (`table = id`) atau `[CurveEditor]` (`curve = id`), atau lihat kolom ID di
`generated/<board>/<board>.tuner-menu.md`.

## Kondisi

Format kondisi sama dengan TunerStudio: `[page,] {enable}[, {visible}]`.

```ini
subMenu = veTableDialog                          ; label & kondisi diwarisi dari INI
subMenu = veTableDialog, "Fuel table"            ; label baru, kondisi diwarisi
subMenu = veTableDialog, "Fuel table", 0, { isInjectionEnabled == 1 }   ; semua ditimpa
```

Sebaiknya kondisi **tidak ditulis** supaya otomatis mengikuti perubahan upstream.

## Aturan validasi (generator gagal jika dilanggar)

- Satu `<id>` hanya boleh muncul sekali di layout.
- `groupChildMenu` harus berada setelah `groupMenu` di menu yang sama.
- Hanya elemen di tabel atas yang dikenali.
- `include` hanya menerima `unplaced`.

## Perilaku otomatis

- `<id>` yang tidak ada di INI board → dilewati dan dicatat di bagian "ID layout yang tidak ada" pada `.md`.
- Grup tanpa halaman, menu tanpa halaman, separator di awal/akhir atau berurutan → dihapus.
- Item Expert diberi label `"<grup asal> - <label>"` bila asalnya di dalam grup TunerStudio.
- Satu dialog yang muncul dua kali di INI asli hanya dimasukkan sekali ke Expert.

## Batasan

- TunerStudio hanya mendukung satu level grup. Karena itu struktur maksimum adalah
  menu → grup → halaman, sama seperti 3 level di MaxxECU.
- Kondisi milik `groupMenu` asli tidak dibawa ke Expert. Hal ini aman karena setiap halaman di
  dalamnya sudah punya kondisi sendiri.
