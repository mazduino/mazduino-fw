/**
 * @file board_configuration.cpp
 * Mazduino Mega100 (STM32F407VGT6 - 1MB flash)
 * Arduino Mega socket form factor
 * Reference: https://github.com/rusefi/fw-custom-mega100-f4
 *
 * Two pinout variants selectable via TunerStudio board action:
 *   Index 0: board_04  - legacy wiring (INJ: B15/B14/B12/B13, IGN: E2/E3/C13/E7)
 *   Index 1: ua4c      - UA4C wiring   (INJ: B15/D8/D9/D10,  IGN: E15/E4/D13/E5)
 */

#include "pch.h"
#include "board_overrides.h"
#include "flash_main.h"
#include "tunerstudio.h"

Gpio getCommsLedPin() { return config->communityCommsLedPin; }
Gpio getRunningLedPin() { return Gpio::Unassigned; }
Gpio getWarningLedPin() { return Gpio::Unassigned; }

static void setPinout_board04() {
    engineConfiguration->injectionPins[0] = Gpio::B15;
    engineConfiguration->injectionPins[1] = Gpio::B14;
    engineConfiguration->injectionPins[2] = Gpio::B12;
    engineConfiguration->injectionPins[3] = Gpio::B13;

    engineConfiguration->ignitionPins[0] = Gpio::E2;
    engineConfiguration->ignitionPins[1] = Gpio::E3;
    engineConfiguration->ignitionPins[2] = Gpio::C13;
    engineConfiguration->ignitionPins[3] = Gpio::E7;
}

static void setPinout_ua4c() {
    engineConfiguration->injectionPins[0] = Gpio::B15;
    engineConfiguration->injectionPins[1] = Gpio::D8;
    engineConfiguration->injectionPins[2] = Gpio::D9;
    engineConfiguration->injectionPins[3] = Gpio::D10;

    engineConfiguration->ignitionPins[0] = Gpio::E15;
    engineConfiguration->ignitionPins[1] = Gpio::E4;
    engineConfiguration->ignitionPins[2] = Gpio::D13;
    engineConfiguration->ignitionPins[3] = Gpio::E5;
}

void customBoardTsAction(uint16_t subSystem, uint16_t index) {
    if (subSystem != (uint16_t)TS_BOARD_ACTION) {
        return;
    }
    if (index == 0) {
        setPinout_board04();
    } else if (index == 1) {
        setPinout_ua4c();
    }
    writeToFlashNow();
    onApplyPreset();
}

static void customBoardDefaultConfiguration() {
    config->communityCommsLedPin = Gpio::B7;

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

    engineConfiguration->analogInputDividerCoefficient = 1.47f;
    engineConfiguration->adcVcc = 3.3f;
    engineConfiguration->clt.config.bias_resistor = 2490;
    engineConfiguration->iat.config.bias_resistor = 2490;

    // Default to board_04 pinout
    setPinout_board04();

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
