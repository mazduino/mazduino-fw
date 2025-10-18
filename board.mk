BOARDCPPSRC =  $(BOARD_DIR)/board_configuration.cpp \
    $(BOARD_DIR)/firmware/pinouts.cpp \

BOARDINC += $(BOARD_DIR)/generated/controllers/generated

# defines SHORT_BOARD_NAME
include $(BOARD_DIR)/meta-info.env

# this would save some flash while being unable to update WBO controller firmware
DDEFS += -DEFI_WIDEBAND_FIRMWARE_UPDATE=FALSE
DDEFS += -DRAM_UNUSED_SIZE=100

DDEFS += -DSTM32_ADC_USE_ADC2=TRUE
# todo: make knock pin software-selectable?
DDEFS += -DEFI_SOFTWARE_KNOCK=TRUE -DSTM32_ADC_USE_ADC2=TRUE
DDEFS += -DKNOCK_SPECTROGRAM=TRUE

# assign critical LED to a non-existent pin if you do not have it on your board
# good old PD14 is still the default value
# DDEFS += -DLED_CRITICAL_ERROR_BRAIN_PIN=Gpio::I15
