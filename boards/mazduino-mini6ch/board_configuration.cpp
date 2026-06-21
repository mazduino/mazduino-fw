/**
 * @file board_configuration.cpp
 * Mazduino Mini 6CH v1.3C
 * https://wiki.mazduino.com/mazduino-mini-6ch-v1.3c/
 */

#include "pch.h"
#include "board_overrides.h"

Gpio getCommsLedPin() { return config->communityCommsLedPin; }
Gpio getRunningLedPin() { return Gpio::Unassigned; }
Gpio getWarningLedPin() { return Gpio::Unassigned; }

static void setupEtb() {
    // TLE9201 - PWM + DIR + DIS
    engineConfiguration->etbIo[0].controlPin    = Gpio::A8;  // PWM
    engineConfiguration->etbIo[0].directionPin1 = Gpio::B8;  // DIR
    engineConfiguration->etbIo[0].disablePin    = Gpio::B9;  // DIS
    engineConfiguration->etb_use_two_wires = false;
}

static void customBoardDefaultConfiguration() {
    config->communityCommsLedPin = Gpio::B7;

    // Trigger inputs
    engineConfiguration->triggerInputPins[0] = Gpio::D3;   // CKP

    // Analog sensors - ADC1
    // PA3 (EFI_ADC_3) is reserved for knock via ADC3 - do not assign here
    engineConfiguration->map.sensor.hwChannel  = EFI_ADC_0;  // PA0
    engineConfiguration->afr.hwChannel         = EFI_ADC_1;  // PA1
    engineConfiguration->tps1_1AdcChannel       = EFI_ADC_6;  // PA6
    engineConfiguration->clt.adcChannel         = EFI_ADC_4;  // PA4
    engineConfiguration->iat.adcChannel         = EFI_ADC_5;  // PA5
    engineConfiguration->vbattAdcChannel        = EFI_ADC_7;  // PA7

    engineConfiguration->analogInputDividerCoefficient = 1.47f;
    engineConfiguration->adcVcc = 3.3f;
    engineConfiguration->clt.config.bias_resistor = 2490;
    engineConfiguration->iat.config.bias_resistor = 2490;

    // Injectors - 6 channel
    engineConfiguration->injectionPins[0] = Gpio::D8;
    engineConfiguration->injectionPins[1] = Gpio::B15;
    engineConfiguration->injectionPins[2] = Gpio::B14;
    engineConfiguration->injectionPins[3] = Gpio::B13;
    engineConfiguration->injectionPins[4] = Gpio::D9;
    engineConfiguration->injectionPins[5] = Gpio::E8;

    // Ignition - 6 channel
    engineConfiguration->ignitionPins[0] = Gpio::E15;
    engineConfiguration->ignitionPins[1] = Gpio::E14;
    engineConfiguration->ignitionPins[2] = Gpio::D13;
    engineConfiguration->ignitionPins[3] = Gpio::E5;
    engineConfiguration->ignitionPins[4] = Gpio::E2;
    engineConfiguration->ignitionPins[5] = Gpio::E3;

    // Aux outputs
    engineConfiguration->fuelPumpPin               = Gpio::C8;
    engineConfiguration->mainRelayPin               = Gpio::C5;
    engineConfiguration->idle.solenoidPin           = Gpio::D10;
    engineConfiguration->secondSolenoidPin          = Gpio::E9;
    engineConfiguration->fanPin                     = Gpio::A15;
    engineConfiguration->tachOutputPin              = Gpio::C9;
    engineConfiguration->acSwitch                   = Gpio::B5;
    engineConfiguration->acRelayPin                 = Gpio::C7;
    engineConfiguration->vehicleSpeedSensorInputPin = Gpio::D7;
    engineConfiguration->clutchDownPin              = Gpio::E12;
    engineConfiguration->clutchDownPinMode          = PI_INVERTED_PULLUP;

    // Stepper motor idle
    engineConfiguration->idle.stepperDirectionPin   = Gpio::D12;
    engineConfiguration->idle.stepperStepPin        = Gpio::D15;
    engineConfiguration->stepperEnablePin           = Gpio::D14;

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

    // Electronic throttle - TLE9201
    setupEtb();
}

void setup_custom_board_overrides() {
    custom_board_DefaultConfiguration = customBoardDefaultConfiguration;
}
