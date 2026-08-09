ifneq ($(PROJECT_CPU),simulator)
BOARDCPPSRC += \
    $(BOARD_DIR)/board_configuration.cpp \

endif

# STM32F427VGT6: same core as F429 minus LTDC/DMA2D.
# Enables SRAM3 (+64KB), correct flash driver, and EFI_IS_F42x features.
# Clock stays at 168MHz so USB 48MHz remains exact (PLLN=336, PLLQ=7).
IS_STM32F427 = yes

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

# Move critical-error LED off PD14: that pin is the stepper driver enable
# (MCU-ENBL -> DRV8825 EN via JP6 for manual enable). Default rusEFI critical
# LED is PD14, which collided with stepperEnablePin. mini6ch has 3 onboard
# LEDs (PB4, PB6, PB7); PB7 is the comms LED, so use the dedicated PB4 LED for
# critical error. This frees PD14 for stepper enable.
DDEFS += -DLED_CRITICAL_ERROR_BRAIN_PIN=Gpio::B4
