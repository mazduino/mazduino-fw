ifneq ($(PROJECT_CPU),simulator)
BOARDCPPSRC += \
    $(BOARD_DIR)/board_configuration.cpp \

endif

DDEFS += -DEFI_WIDEBAND_FIRMWARE_UPDATE=FALSE
DDEFS += -DRAM_UNUSED_SIZE=100

# STM32F407VET6: 512KB flash
DDEFS += -DMIN_FLASH_SIZE=512
USE_OPT += -Wl,--defsym=EFI_FLASH_SIZE=512k

# Assign critical LED to a non-existent pin (board has no LEDs)
DDEFS += -DLED_CRITICAL_ERROR_BRAIN_PIN=Gpio::I15

# EFI_USB_SERIAL=FALSE, EFI_LUA=FALSE, EFI_ELECTRONIC_THROTTLE_BODY=FALSE set in efifeatures.h
# HAL_USE_USB derives FALSE automatically from EFI_USB_SERIAL

# Disable SD card/FAT to save flash
DDEFS += -DEFI_FILE_LOGGING=FALSE
USE_FATFS = no
