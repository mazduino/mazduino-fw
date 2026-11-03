ifneq ($(PROJECT_CPU),simulator)
BOARDCPPSRC += \
    $(BOARD_DIR)/board_configuration.cpp \

endif

DDEFS += -DEFI_WIDEBAND_FIRMWARE_UPDATE=FALSE
DDEFS += -DRAM_UNUSED_SIZE=100

# INI embedded in flash overflows the 768KB budget with CAN feature additions.
# INI is published as a GitHub Releases artifact instead.
DDEFS += -DEFI_EMBED_INI_MSD=FALSE

# Mazda PFI — no GDI high-pressure fuel pump
DDEFS += -DEFI_HPFP=FALSE

# Secondary TunerStudio channel on USART1 (PA9 = TXD1, PA10 = RXD1), for a Bluetooth module such as
# an HC-05. PB10/PB11 carry the LPS25 baro on this board. See mazduino-mini6ch/board.mk for why it
# uses the Serial driver.
DDEFS += -DSTM32_SERIAL_USE_USART1=TRUE -DSTM32_SERIAL_USART1_PRIORITY=6
DDEFS += -DTS_SECONDARY_UxART_PORT=SD1 -DEFI_TS_SECONDARY_IS_SERIAL=TRUE

# Transmission control: the TunerStudio pages are on (ts_show_tcu), and without this nothing behind
# them is built. It stays idle until tcuEnabled is set in the tune.
DDEFS += -DEFI_TCU=TRUE
