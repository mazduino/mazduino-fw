# Requires STM32F427ZGT6 (LQFP144), not the VGT6 (LQFP100) used by the rest of
# the mazduino fleet: this pinout uses GPIOG (LS 2-7, IGN 6-12), which the
# 100-pin package does not bond out.

ifneq ($(PROJECT_CPU),simulator)
BOARDCPPSRC += \
    $(BOARD_DIR)/board_configuration.cpp \

endif

# STM32F427ZGT6: same core as F429 minus LTDC/DMA2D.
# Enables SRAM3 (+64KB), correct flash driver, and EFI_IS_F42x features.
# Clock stays at 168MHz so USB 48MHz remains exact (PLLN=336, PLLQ=7).
IS_STM32F427 = yes

# Hardware serial port on UART 2 -> PD5/PD6, same as official Proteus F4
DDEFS += -DSTM32_UART_USE_USART2=TRUE
DDEFS += -DTS_PRIMARY_UxART_PORT=UARTD2
DDEFS += -DEFI_CONSOLE_TX_BRAIN_PIN=Gpio::D5 -DEFI_CONSOLE_RX_BRAIN_PIN=Gpio::D6

DDEFS += -DEFI_WIDEBAND_FIRMWARE_UPDATE=FALSE
DDEFS += -DRAM_UNUSED_SIZE=100
DDEFS += -DSTM32_ADC_USE_ADC3=TRUE
DDEFS += -DEFI_SOFTWARE_KNOCK=TRUE -DSTM32_ADC_USE_ADC3=TRUE
DDEFS += -DKNOCK_SPECTROGRAM=TRUE

# Comms/Running/Warning LEDs at PE4/PE5/PE6, error LED at PE3 - same as official Proteus F4
DDEFS += -DLED_CRITICAL_ERROR_BRAIN_PIN=Gpio::E3

# INI embedded in flash overflows the 768KB budget with CAN feature additions.
# INI is published as a GitHub Releases artifact instead.
DDEFS += -DEFI_EMBED_INI_MSD=FALSE

# Same as official Proteus F4: EGO/DYNO view and RTC don't fit the F4 flash budget
# alongside ETB + 12x12 outputs + knock spectrogram.
DDEFS += -DEFI_DYNO_VIEW=FALSE
DDEFS += -DEFI_RTC=FALSE

# Mazda PFI — no GDI high-pressure fuel pump
DDEFS += -DEFI_HPFP=FALSE
