#!/usr/bin/env bash
# board_flags.sh - the feature defines a board sets, one "NAME value" per line, the last one winning.
#
# Usage: mazduino-tuner/tools/board_flags.sh <board>
#
# Read in build order: board.mk (a -bigfuel board includes its base board's first), efifeatures.h,
# prepend*.txt. A define the board does not set is not listed: its value is the firmware default.

set -euo pipefail
export LC_ALL=C

HERE="$(cd "$(dirname "$0")" && pwd)"
BOARDS="$(cd "$HERE/../../boards" && pwd)"
BOARD="${1:?Usage: $0 <board>}"
[ -d "$BOARDS/$BOARD" ] || exit 0

board_mk() {
	[ -f "$BOARDS/$1/board.mk" ] || return 0
	base="$(sed -n 's#^include \$(BOARD_DIR)/\.\./\([^/]*\)/board\.mk.*#\1#p' "$BOARDS/$1/board.mk" | head -1)"
	[ -z "$base" ] || board_mk "$base"
	grep -v '^[[:space:]]*#' "$BOARDS/$1/board.mk" | grep -oE -- '-D(EFI_[A-Za-z0-9_]+|TS_(PRIMARY|SECONDARY)_[A-Za-z0-9_]+)=[A-Za-z0-9_]+' | sed 's/^-D//; s/=/ /'
}

# A git symlink checked out without symlink support (Windows, core.symlinks=false) is a small text
# file holding the relative target path. Follow it, so a -bigfuel board still reads the base board's
# prepend.txt there as it does on Linux.
follow() {
	local f="$1" target
	if [ ! -L "$f" ] && [ "$(wc -c < "$f")" -lt 256 ]; then
		target="$(tr -d '\r\n' < "$f")"
		case "$target" in
			*[[:space:]]*|'') ;;
			*) [ -f "$(dirname "$f")/$target" ] && f="$(dirname "$f")/$target" ;;
		esac
	fi
	printf '%s\n' "$f"
}

{
	board_mk "$BOARD"
	for f in "$BOARDS/$BOARD"/efifeatures.h "$BOARDS/$BOARD"/prepend*.txt; do
		[ -f "$f" ] || continue
		f="$(follow "$f")"
		awk '$1 == "#define" && NF >= 3 && $2 ~ /^(ts_show_|EFI_|VE_|IGN_|VVT_)/ { print $2, $3 }' "$f"
	done
} | awk '{ v[$1] = $2 } END { for (k in v) print k, v[k] }' | sort
