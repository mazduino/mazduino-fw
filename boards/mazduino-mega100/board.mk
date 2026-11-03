ifneq ($(PROJECT_CPU),simulator)
BOARDCPPSRC += \
    $(BOARD_DIR)/board_configuration.cpp \

endif

DDEFS += -DEFI_WIDEBAND_FIRMWARE_UPDATE=FALSE
DDEFS += -DRAM_UNUSED_SIZE=100
DDEFS += -DSTM32_ADC_USE_ADC3=TRUE
DDEFS += -DEFI_SOFTWARE_KNOCK=TRUE -DSTM32_ADC_USE_ADC3=TRUE
DDEFS += -DKNOCK_SPECTROGRAM=TRUE

# Status LED at PB7
DDEFS += -DLED_CRITICAL_ERROR_BRAIN_PIN=Gpio::B7

# STM32F407VGT6: 1MB chip, 768KB linker budget. CAN feature additions grew the
# firmware beyond 768KB when the INI ramdisk is embedded. Disable embedding;
# the INI is available via GitHub Releases instead.
DDEFS += -DEFI_EMBED_INI_MSD=FALSE

# Mazda PFI — no GDI high-pressure fuel pump
DDEFS += -DEFI_HPFP=FALSE

# Reduce Lua RAM usage
DDEFS += -DWITH_LUA_CONSUMPTION=FALSE
DDEFS += -DWITH_LUA_PID=FALSE
DDEFS += -DWITH_LUA_STOP_ENGINE=FALSE

# Secondary TunerStudio channel on USART3 (PB10 = TXD3, PB11 = RXD3), for a Bluetooth module such as
# an HC-05. See mazduino-mini6ch/board.mk for why it uses the Serial driver.
DDEFS += -DSTM32_SERIAL_USE_USART3=TRUE -DSTM32_SERIAL_USART3_PRIORITY=6
DDEFS += -DTS_SECONDARY_UxART_PORT=SD3 -DEFI_TS_SECONDARY_IS_SERIAL=TRUE

# Transmission control: the TunerStudio pages are on (ts_show_tcu), and without this nothing behind
# them is built. It stays idle until tcuEnabled is set in the tune.
DDEFS += -DEFI_TCU=TRUE
