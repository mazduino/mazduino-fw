ifneq ($(PROJECT_CPU),simulator)
BOARDCPPSRC += \
    $(BOARD_DIR)/board_configuration.cpp \

endif

DDEFS += -DEFI_WIDEBAND_FIRMWARE_UPDATE=FALSE
DDEFS += -DRAM_UNUSED_SIZE=100
DDEFS += -DSTM32_ADC_USE_ADC3=TRUE
DDEFS += -DEFI_SOFTWARE_KNOCK=TRUE -DSTM32_ADC_USE_ADC3=TRUE
DDEFS += -DKNOCK_SPECTROGRAM=TRUE

# INI embedded in flash overflows the 768KB budget with CAN feature additions.
# INI is published as a GitHub Releases artifact instead.
DDEFS += -DEFI_EMBED_INI_MSD=FALSE

# Mazda PFI — no GDI high-pressure fuel pump
DDEFS += -DEFI_HPFP=FALSE
