# Inherit everything from the board this variant is based on.
include $(BOARD_DIR)/../mazduino-mini6ch/board.mk

# 32x32 VE + ignition tables grow persistent_config, which lives in CCM RAM
# (PERSISTENT_LOCATION = CCM_OPTIONAL = .ram4). CCM is only 64KB and its
# leftovers are handed to the Lua heap, so the stock feature set overflows it
# by ~1.4KB. The engine sniffer's 5000-byte WAVE_LOGGING_BUFFER is also in CCM
# and is a debug-only tool, so BIGFUEL trades it for the bigger tables.
DDEFS += -DEFI_ENGINE_SNIFFER=FALSE
