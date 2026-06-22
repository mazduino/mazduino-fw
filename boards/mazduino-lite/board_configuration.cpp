/**
 * @file board_configuration.cpp
 * Mazduino Lite v0.2
 * https://wiki.mazduino.com/mazduino-lite-v0.2/
 */

#include "pch.h"
#include "board_overrides.h"

Gpio getCommsLedPin() { return config->communityCommsLedPin; }
Gpio getRunningLedPin() { return Gpio::Unassigned; }
Gpio getWarningLedPin() { return Gpio::Unassigned; }

static void customBoardDefaultConfiguration() {
    config->communityCommsLedPin = Gpio::B7;

    // Trigger inputs - digital output from VR conditioner
    engineConfiguration->triggerInputPins[0] = Gpio::C6;   // CKP
    // VR1=PD3, VR2=PD4 are raw analog inputs to VR conditioner on board

    // Analog sensors - ADC1
    // PA3 (EFI_ADC_3) used for TPS on Lite; knock shares PA3 via ADC3 independently
    engineConfiguration->map.sensor.hwChannel  = EFI_ADC_0;  // PA0
    engineConfiguration->afr.hwChannel         = EFI_ADC_1;  // PA1
    engineConfiguration->vbattAdcChannel        = EFI_ADC_2;  // PA2
    engineConfiguration->tps1_1AdcChannel       = EFI_ADC_3;  // PA3
    engineConfiguration->clt.adcChannel         = EFI_ADC_4;  // PA4
    engineConfiguration->iat.adcChannel         = EFI_ADC_5;  // PA5

    engineConfiguration->analogInputDividerCoefficient = (470.0f + 910.0f) / 910.0f; // 470R high side/910R low side
    engineConfiguration->vbattDividerCoeff = (82.0f + 10.0f) / 10.0f; // 82k high side/10k low side
    engineConfiguration->adcVcc = 3.3f;
    engineConfiguration->clt.config.bias_resistor = 2700;
    engineConfiguration->iat.config.bias_resistor = 2700;

    // Injectors - 4 channel
    engineConfiguration->injectionPins[0] = Gpio::D8;
    engineConfiguration->injectionPins[1] = Gpio::B15;
    engineConfiguration->injectionPins[2] = Gpio::B14;
    engineConfiguration->injectionPins[3] = Gpio::B13;

    // Ignition - 2 channel
    engineConfiguration->ignitionPins[0] = Gpio::E15; // coil-on-plug for cylinder 1; wasted spark for 4-cylinder engines uses E14 for cylinder 3
    engineConfiguration->ignitionPins[2] = Gpio::E14; // wasted spark for 4-cylinder engines

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
