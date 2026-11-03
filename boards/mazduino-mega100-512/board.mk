ifneq ($(PROJECT_CPU),simulator)
BOARDCPPSRC += \
    $(BOARD_DIR)/board_configuration.cpp \

endif

DDEFS += -DEFI_WIDEBAND_FIRMWARE_UPDATE=FALSE
DDEFS += -DRAM_UNUSED_SIZE=100

# STM32F407VET6: 512KB total flash, but tune occupies sector 7 (0x08060000-0x0807FFFF).
# Code region is limited to sectors 0-6 (384KB) to leave sector 7 free for tune storage.
# The linker will error with "overflow" if code exceeds 384KB.
DDEFS += -DMIN_FLASH_SIZE=512
USE_OPT += -Wl,--defsym=EFI_FLASH_SIZE=384k

# Status LED at PB7
DDEFS += -DLED_CRITICAL_ERROR_BRAIN_PIN=Gpio::B7

# EFI_LUA=FALSE, EFI_ELECTRONIC_THROTTLE_BODY=FALSE set in efifeatures.h
# EFI_USB_SERIAL=TRUE (default) — USB virtual COM port enabled for TunerStudio

# Disable SD card/FAT to save flash
DDEFS += -DEFI_FILE_LOGGING=FALSE
USE_FATFS = no

# Secondary TunerStudio channel on USART3 (PB10 = TXD3, PB11 = RXD3), for a Bluetooth module such as
# an HC-05. See mazduino-mini6ch/board.mk for why it uses the Serial driver.
DDEFS += -DSTM32_SERIAL_USE_USART3=TRUE -DSTM32_SERIAL_USART3_PRIORITY=6
DDEFS += -DTS_SECONDARY_UxART_PORT=SD3 -DEFI_TS_SECONDARY_IS_SERIAL=TRUE
