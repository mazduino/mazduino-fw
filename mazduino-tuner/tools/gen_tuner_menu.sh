#!/usr/bin/env bash
# gen_tuner_menu.sh - buat menu Mazduino Tuner (gaya MaxxECU) dari INI firmware.
#
# Pemakaian:
#   mazduino-tuner/tools/gen_tuner_menu.sh <rusefi_board.ini> [out_dir] [layout.ini]
#
# Output di <out_dir> (default: mazduino-tuner/generated/<board>/):
#   <board>.tuner-menu.json   menu untuk aplikasi Mazduino Tuner
#   <board>.tuner-menu.md     dokumentasi menu (untuk review)
#   rusefi_<board>.tuner.ini  INI firmware dengan [Menu] diganti (bisa dibuka di TunerStudio
#                             untuk preview; signature & semua definisi lain tidak berubah)
#
# Exit code != 0 bila layout salah (ID dobel, sintaks tidak dikenal, dll).

set -euo pipefail
export LC_ALL=C

HERE="$(cd "$(dirname "$0")" && pwd)"
ROOT="$(cd "$HERE/.." && pwd)"

INI="${1:?Pemakaian: $0 <rusefi_board.ini> [out_dir] [layout.ini]}"
LAYOUT="${3:-$ROOT/menu/mazduino-tuner-menu.ini}"

[ -f "$INI" ] || { echo "INI tidak ditemukan: $INI" >&2; exit 2; }
[ -f "$LAYOUT" ] || { echo "Layout tidak ditemukan: $LAYOUT" >&2; exit 2; }

base="$(basename "$INI" .ini)"
BOARD="${base#rusefi_}"
OUT="${2:-$ROOT/generated/$BOARD}"
mkdir -p "$OUT"

MENU_TMP="$(mktemp)"
trap 'rm -f "$MENU_TMP"' EXIT

awk -f "$HERE/gen_tuner_menu.awk" \
	-v MENU_OUT="$MENU_TMP" \
	-v JSON_OUT="$OUT/$BOARD.tuner-menu.json" \
	-v MD_OUT="$OUT/$BOARD.tuner-menu.md" \
	-v BOARD="$BOARD" \
	"$INI" "$LAYOUT"

# Ganti section [Menu] (sampai section berikutnya) dengan menu baru.
awk -v MENU_FILE="$MENU_TMP" '
	/^[ \t]*\[[A-Za-z]+\]/ {
		if (inMenu) inMenu = 0
		if ($0 ~ /^[ \t]*\[Menu\]/) {
			while ((getline l < MENU_FILE) > 0) print l
			close(MENU_FILE); inMenu = 1; next
		}
	}
	!inMenu { print }
' "$INI" > "$OUT/rusefi_$BOARD.tuner.ini"

echo "Output: $OUT" >&2
