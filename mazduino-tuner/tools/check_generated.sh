#!/usr/bin/env bash
# check_generated.sh - fail when the committed generated/ does not match the layout and generator.
#
# Each committed JSON records the signature of the INI it was built from. This regenerates it from
# that same INI on gh-pages, so a newer nightly INI cannot cause a difference: what is left is a
# layout or generator change committed without regenerating.
#
# Usage (from the mazduino-fw repo root):
#   mazduino-tuner/tools/check_generated.sh

set -euo pipefail
export LC_ALL=C

HERE="$(cd "$(dirname "$0")" && pwd)"
ROOT="$(cd "$HERE/.." && pwd)"
REPO="$(cd "$ROOT/.." && pwd)"

cd "$REPO"
git fetch -q origin gh-pages
TMP="$(mktemp -d)"
trap 'rm -rf "$TMP"' EXIT

fail=0
checked=0
for json in "$ROOT"/generated/*/*.tuner-menu.json; do
	board="$(basename "$json" .tuner-menu.json)"
	sig="$(sed -n 's/^ *"signature": "\(.*\)",$/\1/p' "$json")"
	# rusEFI <branch>.<yyyy>.<mm>.<dd>.<board>.<hash>
	IFS='.' read -r branch year month day target hash <<< "${sig#rusEFI }"
	path="ini/$branch/$year/$month/$day/$target/$hash.ini"
	if ! git show "origin/gh-pages:$path" > "$TMP/rusefi_$board.ini" 2>/dev/null; then
		echo "::warning::$board: cannot check, $path is not on gh-pages (generated from an unpublished INI?)"
		continue
	fi
	"$HERE/gen_tuner_menu.sh" "$TMP/rusefi_$board.ini" "$TMP/$board" 2>/dev/null
	for ext in json md; do
		if ! diff -u "$ROOT/generated/$board/$board.tuner-menu.$ext" "$TMP/$board/$board.tuner-menu.$ext" > "$TMP/diff"; then
			echo "::error::$board.tuner-menu.$ext does not match the layout. Run gen_all_from_gh_pages.sh and commit generated/."
			head -40 "$TMP/diff"
			fail=1
		fi
	done
	checked=$((checked + 1))
done
echo "Checked $checked boards against the INI each menu was built from." >&2

"$HERE/gen_board_features.sh" "$TMP/FEATURES.md"
if ! diff -u "$REPO/boards/FEATURES.md" "$TMP/FEATURES.md" > "$TMP/diff"; then
	echo "::error::boards/FEATURES.md does not match the boards. Run gen_board_features.sh and commit it."
	head -40 "$TMP/diff"
	fail=1
fi
exit $fail
