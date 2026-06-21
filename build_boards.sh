#!/usr/bin/env bash
# Build all per-board firmwares inside Docker (needed for mtools/dosfstools).
# Usage:
#   ./build_boards.sh                   # build all boards
#   ./build_boards.sh mazduino-compact  # build single board

set -euo pipefail

REPO_ROOT="$(cd "$(dirname "$0")"; pwd)"
IMAGE_NAME="rusefi-build"
# Force x86-64 so hex2dfu.bin (x86-64 Linux binary) works via Rosetta 2 on Apple Silicon.
# CI runners are already x86-64 Linux, so this keeps local and CI environments identical.
DOCKER_PLATFORM="linux/amd64"
BOARD_ARG="${1:-}"

# Build Docker image if not present
if ! docker image inspect "$IMAGE_NAME" &>/dev/null; then
    echo "=== Building Docker image (first time only) ==="
    docker build --platform "$DOCKER_PLATFORM" -t "$IMAGE_NAME" "$REPO_ROOT/.devcontainer/"
fi

# Determine which boards to build
if [ -n "$BOARD_ARG" ]; then
    BOARDS=("$BOARD_ARG")
else
    BOARDS=()
    for d in "$REPO_ROOT/boards"/*/; do
        BOARDS+=("$(basename "$d")")
    done
fi

echo "=== Boards to build: ${BOARDS[*]} ==="

for BOARD in "${BOARDS[@]}"; do
    META="$REPO_ROOT/boards/$BOARD/meta-info.env"
    if [ ! -f "$META" ]; then
        echo "ERROR: $META not found, skipping $BOARD"
        continue
    fi

    echo ""
    echo "========================================="
    echo " Building: $BOARD"
    echo "========================================="

    docker run --rm --platform "$DOCKER_PLATFORM" \
        -v "$REPO_ROOT:/workspace" \
        -w /workspace/ext/rusefi/firmware \
        -e META_OUTPUT_ROOT_FOLDER=../../../generated/ \
        -e AUTOMATION_REF="$(git -C "$REPO_ROOT" branch --show-current 2>/dev/null || echo mazduino)" \
        "$IMAGE_NAME" \
        bash bin/compile.sh "/workspace/boards/$BOARD/meta-info.env"

    echo "=== $BOARD: DONE ==="
done
