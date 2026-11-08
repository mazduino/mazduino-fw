#!/usr/bin/env bash
# republish_menus.sh - rebuild the published Mazduino Tuner menu of EVERY firmware INI with the
# current layout, so firmware from earlier nightlies shows the same menu as the latest one.
#
# Usage (from the mazduino-fw repo root):
#   mazduino-tuner/tools/republish_menus.sh <ini_root>
#
# <ini_root> is the gh-pages "ini" folder (ini/<branch>/<yyyy>/<mm>/<dd>/<board>/<hash>.ini).
# Next to each <hash>.ini it writes <hash>.tuner-menu.json, replacing the old one. INIs of boards
# that are not in boards/ are left alone. Prints how many menus changed.

set -euo pipefail
export LC_ALL=C

HERE="$(cd "$(dirname "$0")" && pwd)"
ROOT="$(cd "$HERE/.." && pwd)"
REPO="$(cd "$ROOT/.." && pwd)"
INI_ROOT="${1:?Usage: $0 <ini_root>}"
[ -d "$INI_ROOT" ] || { echo "Not a folder: $INI_ROOT" >&2; exit 2; }

TMP="$(mktemp -d)"
trap 'rm -rf "$TMP"' EXIT

total=0 changed=0 failed=0
while IFS= read -r ini; do
	board="$(basename "$(dirname "$ini")")"
	[ -d "$REPO/boards/$board" ] || continue
	total=$((total + 1))
	hash="$(basename "$ini" .ini)"
	dest="$(dirname "$ini")/$hash.tuner-menu.json"
	rm -rf "$TMP/in" "$TMP/out"
	mkdir -p "$TMP/in"
	cp "$ini" "$TMP/in/rusefi_$board.ini"
	if ! "$HERE/gen_tuner_menu.sh" "$TMP/in/rusefi_$board.ini" "$TMP/out" < /dev/null 2> "$TMP/err"; then
		echo "FAIL $ini: $(tail -1 "$TMP/err")" >&2
		failed=$((failed + 1))
		continue
	fi
	if ! cmp -s "$TMP/out/$board.tuner-menu.json" "$dest"; then
		cp "$TMP/out/$board.tuner-menu.json" "$dest"
		changed=$((changed + 1))
	fi
done < <(find "$INI_ROOT" -name '*.ini' -type f | sort)

echo "Menus: $total firmware INIs, $changed changed, $failed failed" >&2
# A firmware whose INI the layout cannot handle keeps its old menu (or the app's built-in one).
exit 0
