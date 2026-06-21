/**
 * @file board_configuration.cpp
 * Mazduino Compact 4CH v2.5
 * https://wiki.mazduino.com/mazduino-compact-4ch-v2.5/
 */

#include "pch.h"
#include "board_overrides.h"

Gpio getCommsLedPin() { return config->communityCommsLedPin; }
Gpio getRunningLedPin() { return Gpio::Unassigned; }
Gpio getWarningLedPin() { return Gpio::Unassigned; }

static void customBoardDefaultConfiguration() {
    config->communityCommsLedPin = Gpio::B7;

    // Trigger inputs
    engineConfiguration->triggerInputPins[0] = Gpio::D3;   // CKP

    // Analog sensors - ADC1
    // PA3 (EFI_ADC_3) is reserved for knock via ADC3 - do not assign here
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

    // Injectors - 4 channel
    engineConfiguration->injectionPins[0] = Gpio::D8;
    engineConfiguration->injectionPins[1] = Gpio::B15;
    engineConfiguration->injectionPins[2] = Gpio::B14;
    engineConfiguration->injectionPins[3] = Gpio::B13;

    // Ignition - 4 channel
    engineConfiguration->ignitionPins[0] = Gpio::E15;
    engineConfiguration->ignitionPins[1] = Gpio::E14;
    engineConfiguration->ignitionPins[2] = Gpio::D13;
    engineConfiguration->ignitionPins[3] = Gpio::E5;

    // Aux outputs
    engineConfiguration->fuelPumpPin               = Gpio::C8;
    engineConfiguration->mainRelayPin               = Gpio::E8;
    engineConfiguration->idle.solenoidPin           = Gpio::D9;
    engineConfiguration->secondSolenoidPin          = Gpio::D10;
    engineConfiguration->fanPin                     = Gpio::A15;
    engineConfiguration->tachOutputPin              = Gpio::C9;
    engineConfiguration->acSwitch                   = Gpio::B0;
    engineConfiguration->acRelayPin                 = Gpio::C7;
    engineConfiguration->vehicleSpeedSensorInputPin = Gpio::D7;
    engineConfiguration->clutchDownPin              = Gpio::E13;
    engineConfiguration->clutchDownPinMode          = PI_INVERTED_PULLUP;
    // HS1=PD15, HS2=PD14 available as GP outputs

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
}
