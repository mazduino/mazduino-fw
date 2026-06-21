/**
 * @file board_configuration.cpp
 * Mazduino Mega100-512 (STM32F407VET6 - 512KB flash)
 * Arduino Mega socket form factor
 * Reference: https://github.com/rusefi/fw-custom-mega100-f4
 *
 * Uses board_04 pinout (INJ: B15/B14/B12/B13, IGN: E2/E3/C13/E7).
 * Runtime pinout switching disabled to reduce flash usage.
 * No USB, no SD card, no Lua (EFI_LUA=FALSE in board.mk).
 */

#include "pch.h"
#include "board_overrides.h"

Gpio getCommsLedPin() { return Gpio::Unassigned; }
Gpio getRunningLedPin() { return Gpio::Unassigned; }
Gpio getWarningLedPin() { return Gpio::Unassigned; }

static void customBoardDefaultConfiguration() {
    // Trigger inputs
    engineConfiguration->triggerInputPins[0] = Gpio::D3;   // CKP
    engineConfiguration->triggerInputPins[1] = Gpio::Unassigned;

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

    // No SD card (EFI_FILE_LOGGING=FALSE, USE_FATFS=no in board.mk)
}

void setup_custom_board_overrides() {
    custom_board_DefaultConfiguration = customBoardDefaultConfiguration;
}
