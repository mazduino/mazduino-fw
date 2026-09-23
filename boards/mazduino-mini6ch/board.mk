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

# Secondary TunerStudio channel on USART3 (PB10 = TXD3, PB11 = RXD3), for a
# Bluetooth module such as an HC-05. Without TS_SECONDARY_UxART_PORT the whole
# secondary channel is compiled out (tunerstudio_io_serial_ports.cpp) and the
# binarySerial pins in TunerStudio do nothing at all.
#
# Uses the ChibiOS Serial driver (SD3), matching how the reference f407-discovery
# board wires up its secondary channel. The UART driver would need HAL_USE_UART,
# which halconf.h only turns on when TS_PRIMARY_UxART_PORT is defined.
DDEFS += -DSTM32_SERIAL_USE_USART3=TRUE -DSTM32_SERIAL_USART3_PRIORITY=6
DDEFS += -DTS_SECONDARY_UxART_PORT=SD3 -DEFI_TS_SECONDARY_IS_SERIAL=TRUE

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
