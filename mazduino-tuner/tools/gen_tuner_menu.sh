#!/usr/bin/env bash
# gen_tuner_menu.sh - build the Mazduino Tuner menu from a firmware INI.
#
# Usage:
#   mazduino-tuner/tools/gen_tuner_menu.sh <rusefi_board.ini> [out_dir] [layout.ini]
#
# Output in <out_dir> (default: mazduino-tuner/generated/<board>/):
#   <board>.tuner-menu.json   menu for the Mazduino Tuner app
#   <board>.tuner-menu.md     menu documentation (for review)
#   rusefi_<board>.tuner.ini  firmware INI with [Menu] replaced (can be opened in TunerStudio
#                             for preview; signature and all other definitions unchanged)
#
# Exit code != 0 if the layout is invalid (duplicate ID, unknown syntax, etc.).

set -euo pipefail
export LC_ALL=C

HERE="$(cd "$(dirname "$0")" && pwd)"
ROOT="$(cd "$HERE/.." && pwd)"

INI="${1:?Usage: $0 <rusefi_board.ini> [out_dir] [layout.ini]}"
LAYOUT="${3:-$ROOT/menu/mazduino-tuner-menu.ini}"

[ -f "$INI" ] || { echo "INI not found: $INI" >&2; exit 2; }
[ -f "$LAYOUT" ] || { echo "Layout not found: $LAYOUT" >&2; exit 2; }

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

# Replace the [Menu] section (up to the next section) with the new menu.
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
