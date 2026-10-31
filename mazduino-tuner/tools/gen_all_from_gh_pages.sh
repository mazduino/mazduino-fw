#!/usr/bin/env bash
# gen_all_from_gh_pages.sh - generate menu Mazduino Tuner untuk semua board memakai INI
# nightly terbaru yang dipublikasikan di branch gh-pages (ini/<branch>/<yyyy>/<mm>/<dd>/<board>/<hash>.ini).
#
# Pemakaian (dari root repo mazduino-fw):
#   mazduino-tuner/tools/gen_all_from_gh_pages.sh [fw_branch]   # default fw_branch: master
#
# Hasil: mazduino-tuner/generated/<board>/

set -euo pipefail
export LC_ALL=C

HERE="$(cd "$(dirname "$0")" && pwd)"
ROOT="$(cd "$HERE/.." && pwd)"
REPO="$(cd "$ROOT/.." && pwd)"
FW_BRANCH="${1:-master}"

cd "$REPO"
git fetch -q origin gh-pages
TMP="$(mktemp -d)"
trap 'rm -rf "$TMP"' EXIT

FILES="$(git ls-tree -r --name-only origin/gh-pages)"
fail=0
for dir in boards/*/; do
	board="$(basename "$dir")"
	path="$(printf '%s\n' "$FILES" | grep -E "^ini/$FW_BRANCH/[0-9]{4}/[0-9]{2}/[0-9]{2}/$board/[0-9]+\.ini$" | sort | tail -1 || true)"
	if [ -z "$path" ]; then
		echo "SKIP $board: tidak ada INI di gh-pages untuk branch $FW_BRANCH" >&2
		continue
	fi
	git show "origin/gh-pages:$path" > "$TMP/rusefi_$board.ini"
	echo "== $board <- $path" >&2
	"$HERE/gen_tuner_menu.sh" "$TMP/rusefi_$board.ini" || fail=1
done
exit $fail
