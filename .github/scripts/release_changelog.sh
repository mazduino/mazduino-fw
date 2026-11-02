#!/usr/bin/env bash
# release_changelog.sh - what changed in one nightly: the CHANGELOG lines added since the previous
# nightly tag. [Unreleased] is never cut, so the section itself holds every change ever made.
#
# Usage: .github/scripts/release_changelog.sh <tag being released> [ref, default HEAD]

set -euo pipefail
export LC_ALL=C

TAG="${1:?Usage: $0 <tag> [ref]}"
REF="${2:-HEAD}"

# The newest earlier nightly this commit contains. A rerun of the same tag does not compare with itself.
PREV="$(git tag --merged "$REF" --list '20[0-9][0-9]-[0-9][0-9]-[0-9][0-9]' | sort | awk -v t="$TAG" '$0 < t' | tail -1)"
if [ -z "$PREV" ]; then
	echo "First nightly build."
	exit 0
fi

ADDED="$(mktemp)"
FILE="$(mktemp)"
trap 'rm -f "$ADDED" "$FILE"' EXIT
git diff -U0 "$PREV" "$REF" -- CHANGELOG.md | grep '^+' | grep -v '^+++' | cut -c2- | grep -v '^$' > "$ADDED" || true
git show "$REF:CHANGELOG.md" > "$FILE"

# Walk the file rather than the diff, so entries stay under their own heading.
NOTES="$(awk '
	FNR == NR { added[$0] = 1; next }
	/^## /  { next }
	/^### / { heading = $0; next }
	$0 in added {
		if (heading != "") { printf "%s%s\n", (printed ? "\n" : ""), heading; heading = "" }
		print
		printed = 1
	}
' "$ADDED" "$FILE")"

echo "## Changes since $PREV"
echo
if [ -n "$NOTES" ]; then
	echo "$NOTES"
	exit 0
fi

# Nothing in the changelog: the commits are all there is to say.
COMMITS="$(git log --no-merges --format='- %s' "$PREV..$REF")"
if [ -n "$COMMITS" ]; then
	echo "$COMMITS"
else
	echo "No changes: same source as $PREV."
fi
