ifneq ($(PROJECT_CPU),simulator)
BOARDCPPSRC += \
    $(BOARD_DIR)/board_configuration.cpp \

endif

# mini6ch ships with either an STM32F407VGT6 (earlier boards) or an
# STM32F427VGT6 (current boards), so build for the F407 and let one binary run
# on both. Do NOT set IS_STM32F427: it links ram0 as 192KB, placing the heap
# and thread stacks in SRAM3 (0x20020000+), which does not exist on the F407 -
# the board hard-faults before USB ever enumerates.
#
# The F427 is still detected and used at runtime via isStm32F42x() (DBGMCU
# IDCODE 0x419): its 64KB SRAM3 becomes extra Lua heap (lua_heap.cpp) and the
# VBAT divider is corrected (stm32_adc_v2.cpp). Tune storage sectors come from
# the flash-size register, and both parts are 1MB, so they match. Both chips
# run at 168MHz, keeping USB 48MHz exact (PLLN=336, PLLQ=7).

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
