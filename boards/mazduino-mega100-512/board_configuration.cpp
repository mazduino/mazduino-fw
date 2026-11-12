/**
 * @file board_configuration.cpp
 * Mazduino Mega100-512 (STM32F407VET6 - 512KB flash)
 * Arduino Mega socket form factor
 * Reference: https://github.com/rusefi/fw-custom-mega100-f4
 *
 * Uses board_04 pinout (INJ: B15/B14/B12/B13, IGN: E2/E3/C13/E7) by default.
 * TunerStudio board actions set the pins for a Speeduino board on the Mega converter v1.3,
 * shared with mazduino-mega100 (../mazduino-mega100/speeduino_presets.cpp).
 * No SD card, no Lua (EFI_LUA=FALSE in board.mk). USB enabled for TunerStudio.
 */

#include "pch.h"
#include "board_overrides.h"
#include "flash_main.h"
#include "tunerstudio.h"
#include "../mazduino-mega100/speeduino_presets.h"

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

    // Trigger inputs
    engineConfiguration->triggerInputPins[0] = Gpio::D3;   // CKP

    // Analog sensors - ADC1
    // PA3 (EFI_ADC_3) reserved for knock via ADC3
    engineConfiguration->map.sensor.hwChannel  = EFI_ADC_0;  // PA0
    engineConfiguration->afr.hwChannel         = EFI_ADC_1;  // PA1
    engineConfiguration->vbattAdcChannel        = EFI_ADC_2;  // PA2
    engineConfiguration->tps1_1AdcChannel       = EFI_ADC_6;  // PA6
    engineConfiguration->clt.adcChannel         = EFI_ADC_4;  // PA4
    engineConfiguration->iat.adcChannel         = EFI_ADC_5;  // PA5

    engineConfiguration->analogInputDividerCoefficient = (470.0f + 910.0f) / 910.0f; // 470R high side/910R low side
    engineConfiguration->vbattDividerCoeff = (82.0f + 10.0f) / 10.0f; // 82k high side/10k low side
    engineConfiguration->adcVcc = 3.3f;
    engineConfiguration->clt.config.bias_resistor = 2700;
    engineConfiguration->iat.config.bias_resistor = 2700;

    // Injectors - 4 channel (board_04 pinout)
    engineConfiguration->injectionPins[0] = Gpio::B15;
    engineConfiguration->injectionPins[1] = Gpio::B14;
    engineConfiguration->injectionPins[2] = Gpio::B12;
    engineConfiguration->injectionPins[3] = Gpio::B13;

    // Ignition - 4 channel (board_04 pinout)
    engineConfiguration->ignitionPins[0] = Gpio::E2;
    engineConfiguration->ignitionPins[1] = Gpio::E3;
    engineConfiguration->ignitionPins[2] = Gpio::C13;
    engineConfiguration->ignitionPins[3] = Gpio::E7;

    // Aux outputs
    engineConfiguration->fuelPumpPin               = Gpio::C8;
    engineConfiguration->mainRelayPin               = Gpio::E8;
    engineConfiguration->idle.solenoidPin           = Gpio::D9;
    engineConfiguration->fanPin                     = Gpio::A15;
    engineConfiguration->tachOutputPin              = Gpio::C9;
    engineConfiguration->acSwitch                   = Gpio::B0;
    engineConfiguration->acRelayPin                 = Gpio::C7;
    engineConfiguration->vehicleSpeedSensorInputPin = Gpio::D7;
    engineConfiguration->clutchDownPin              = Gpio::E13;
    engineConfiguration->clutchDownPinMode          = PI_INVERTED_PULLUP;

    // CAN
    engineConfiguration->canTxPin = Gpio::D1;
    engineConfiguration->canRxPin = Gpio::D0;

    // Secondary TS channel (Bluetooth) on USART3. rusEFI defaults these to PC10/PC11, which this board
    // uses for the SD card on SPI3. Wiring: PB10 -> HC-05 RXD, PB11 <- HC-05 TXD.
    engineConfiguration->binarySerialTxPin = Gpio::B10;
    engineConfiguration->binarySerialRxPin = Gpio::B11;

    // No SD card (EFI_FILE_LOGGING=FALSE, USE_FATFS=no in board.mk)
}

void setup_custom_board_overrides() {
    custom_board_DefaultConfiguration = customBoardDefaultConfiguration;
    custom_board_ts_command = customBoardTsAction;
}
