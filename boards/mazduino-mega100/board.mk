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
