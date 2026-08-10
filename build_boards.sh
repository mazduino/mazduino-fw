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

# Persistent ccache directory on the host keeps compiled objects across builds.
# Requires ccache installed in the Docker image (see .devcontainer/Dockerfile).
CCACHE_DIR="${REPO_ROOT}/.ccache"
mkdir -p "$CCACHE_DIR"

# Build Docker image if not present
if ! docker image inspect "$IMAGE_NAME" &>/dev/null; then
    echo "=== Building Docker image (first time only) ==="
    docker build --platform "$DOCKER_PLATFORM" -t "$IMAGE_NAME" "$REPO_ROOT/.devcontainer/"
fi

# If ccache is available in the image, mount a persistent cache dir and prepend
# /usr/lib/ccache to PATH so Ubuntu's compiler symlinks intercept arm-none-eabi-gcc.
USE_CCACHE=false
CCACHE_MOUNTS=()
if docker run --rm --platform "$DOCKER_PLATFORM" "$IMAGE_NAME" test -x /usr/lib/ccache/arm-none-eabi-gcc &>/dev/null; then
    USE_CCACHE=true
    CCACHE_MOUNTS=(-v "$CCACHE_DIR:/ccache" -e CCACHE_DIR=/ccache)
    echo "=== ccache enabled (cache dir: $CCACHE_DIR) ==="
elif docker run --rm --platform "$DOCKER_PLATFORM" "$IMAGE_NAME" which ccache &>/dev/null; then
    echo "=== ccache installed but arm-none-eabi wrappers not found — skipping ==="
else
    echo "=== ccache not in image — rebuild image to enable it (see .devcontainer/Dockerfile) ==="
fi

if $USE_CCACHE; then
    COMPILE_WRAPPER="PATH=/usr/lib/ccache:\$PATH "
else
    COMPILE_WRAPPER=""
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

# The rusefi submodule's date_stamp.h (VCS_DATE, the firmware version date) is
# frozen at whenever set-date last ran. Stamp today's date so local builds
# report the actual build date instead of a stale one, matching the CI stamp.
printf '#pragma once\n#define VCS_DATE %s\n' "$(date +%Y%m%d)" > "$REPO_ROOT/ext/rusefi/firmware/controllers/date_stamp.h"
echo "=== Stamped VCS_DATE=$(date +%Y%m%d) into ext/rusefi/firmware/controllers/date_stamp.h ==="

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
        "${CCACHE_MOUNTS[@]+"${CCACHE_MOUNTS[@]}"}" \
        -w /workspace/ext/rusefi/firmware \
        -e META_OUTPUT_ROOT_FOLDER=../../../generated/ \
        -e AUTOMATION_REF="$(git -C "$REPO_ROOT" branch --show-current 2>/dev/null || echo mazduino)" \
        "$IMAGE_NAME" \
        bash -c "${COMPILE_WRAPPER}bash bin/compile.sh /workspace/boards/$BOARD/meta-info.env"

    echo "=== $BOARD: DONE ==="
done
