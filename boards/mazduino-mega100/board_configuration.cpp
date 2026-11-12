/**
 * @file board_configuration.cpp
 * Mazduino Mega100 (STM32F407VGT6 - 1MB flash)
 * Arduino Mega socket form factor
 * Reference: https://github.com/rusefi/fw-custom-mega100-f4
 *
 * TunerStudio board actions set the pins for a Speeduino board on the Mega converter v1.3,
 * see speeduino_presets.cpp.
 */

#include "pch.h"
#include "board_overrides.h"
#include "flash_main.h"
#include "tunerstudio.h"
#include "speeduino_presets.h"

// PB7 is the critical error LED (LED_CRITICAL_ERROR_BRAIN_PIN in board.mk); a tune that still has the
// comms LED there would stop the ECU with a pin conflict, so that setting is ignored.
Gpio getCommsLedPin() {
    return config->communityCommsLedPin == LED_CRITICAL_ERROR_BRAIN_PIN ? Gpio::Unassigned : config->communityCommsLedPin;
}
Gpio getRunningLedPin() { return Gpio::Unassigned; }
Gpio getWarningLedPin() { return Gpio::Unassigned; }

void customBoardTsAction(uint16_t subSystem, uint16_t index) {
    if (subSystem != (uint16_t)TS_BOARD_ACTION) {
        return;
    }
    if (!applySpeeduinoPreset(index)) {
        return;
    }
    writeToFlashNow();
    onApplyPreset();
}

static void customBoardDefaultConfiguration() {
    config->communityCommsLedPin = Gpio::Unassigned;

    // Secondary TS channel (Bluetooth) on USART3. rusEFI defaults these to PC10/PC11, which this board
    // uses for the SD card on SPI3. Wiring: PB10 -> HC-05 RXD, PB11 <- HC-05 TXD.
    // These are D16/D17 on the Mega header; a preset whose board uses them (v0.4: stepper) frees them.
    engineConfiguration->binarySerialTxPin = Gpio::B10;
    engineConfiguration->binarySerialRxPin = Gpio::B11;

    // Pins: Speeduino v0.4 through the Mega converter v1.3 (speeduino_presets.cpp). Software knock
    // samples PA3, which is MAP (A3) on that board, so leave knock off with this layout.
    applySpeeduinoPreset(SPEEDUINO_PRESET_V04);

    engineConfiguration->analogInputDividerCoefficient = (470.0f + 910.0f) / 910.0f; // 470R high side/910R low side
    engineConfiguration->vbattDividerCoeff = (82.0f + 10.0f) / 10.0f; // 82k high side/10k low side
    engineConfiguration->adcVcc = 3.3f;
    engineConfiguration->clt.config.bias_resistor = 2700;
    engineConfiguration->iat.config.bias_resistor = 2700;

    // CAN
    engineConfiguration->canTxPin = Gpio::D1;
    engineConfiguration->canRxPin = Gpio::D0;

    // SD card - SPI3
    engineConfiguration->is_enabled_spi_3  = true;
    engineConfiguration->spi3mosiPin        = Gpio::C12;
    engineConfiguration->spi3misoPin        = Gpio::C11;
    engineConfiguration->spi3sckPin         = Gpio::C10;
    engineConfiguration->isSdCardEnabled    = true;
    engineConfiguration->sdCardSpiDevice    = SPI_DEVICE_3;
    engineConfiguration->sdCardCsPin        = Gpio::D2;
}

void setup_custom_board_overrides() {
    custom_board_DefaultConfiguration = customBoardDefaultConfiguration;
    custom_board_ts_command = customBoardTsAction;
}
