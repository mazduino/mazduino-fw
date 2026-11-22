/**
 * @file board_configuration.cpp
 * Mazduino Compact 4CH v2.5, plus the v3.0 VR/Hall trigger inputs
 * https://wiki.mazduino.com/mazduino-compact-4ch-v2.5/
 */

#include "pch.h"
#include "board_overrides.h"

/**
 * Compact v3.0 trigger inputs. Each of CKP and CMP has one Trigger+/Trigger- pair on the connector:
 * - Hall: read as a digital input on PD3 (CKP) / PD4 (CMP), as on v2.5. Needs the switched pull-up.
 * - VR: read from the VR conditioner output on PE0 (CKP) / PE1 (CMP). Its threshold comes from the
 *   vrThreshold curves, PWM on PA8 (CKP) / PC6 (CMP). The pull-up must be off, it would load the sensor.
 * The pin chosen for the trigger input is the only setting: picking the VR pin turns that pull-up off,
 * any other pin leaves it on. The pull-up enables are active high and the board defaults them to on.
 * On v2.5 and older these MCU pins are not connected, so driving them there has no effect.
 */
static constexpr Gpio crankVrPin = Gpio::E0;
static constexpr Gpio camVrPin = Gpio::E1;

static OutputPin crankHallPullUp;
static OutputPin camHallPullUp;

static bool isUsedAsTriggerInput(Gpio pin) {
    for (auto input : engineConfiguration->triggerInputPins) {
        if (input == pin) {
            return true;
        }
    }
    for (auto input : engineConfiguration->camInputs) {
        if (input == pin) {
            return true;
        }
    }
    return false;
}

static void customBoardInitHardware() {
    crankHallPullUp.initPin("CKP Hall pull-up", Gpio::E4);
    camHallPullUp.initPin("CMP Hall pull-up", Gpio::E6);
}

// Also runs once at boot, right after customBoardInitHardware
static void customBoardOnConfigurationChange(const engine_configuration_s * /*previousConfiguration*/) {
    crankHallPullUp.setValue(!isUsedAsTriggerInput(crankVrPin));
    camHallPullUp.setValue(!isUsedAsTriggerInput(camVrPin));
}

Gpio getCommsLedPin() { return config->communityCommsLedPin; }
Gpio getRunningLedPin() { return Gpio::Unassigned; }
Gpio getWarningLedPin() { return Gpio::Unassigned; }

static void customBoardDefaultConfiguration() {
    config->communityCommsLedPin = Gpio::B7;

    // Trigger inputs
    engineConfiguration->triggerInputPins[0] = Gpio::D3;   // CKP, Hall (PE0 for VR on v3.0)

    // Analog sensors - ADC1
    // PA3 (EFI_ADC_3) is reserved for knock via ADC3 - do not assign here
    engineConfiguration->map.sensor.hwChannel  = EFI_ADC_0;  // PA0
    engineConfiguration->afr.hwChannel         = EFI_ADC_1;  // PA1
    engineConfiguration->vbattAdcChannel        = EFI_ADC_2;  // PA2
    engineConfiguration->tps1_1AdcChannel       = EFI_ADC_6;  // PA6
    engineConfiguration->clt.adcChannel         = EFI_ADC_4;  // PA4
    engineConfiguration->iat.adcChannel         = EFI_ADC_5;  // PA5

    engineConfiguration->analogInputDividerCoefficient = 1.56f; // 5.6k high side/10k low side
    engineConfiguration->vbattDividerCoeff = (82.0f + 10.0f) / 10.0f; // 82k high side/10k low side
    engineConfiguration->adcVcc = 3.3f;
    engineConfiguration->clt.config.bias_resistor = 2700;
    engineConfiguration->iat.config.bias_resistor = 2700;

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

    // Secondary TS channel (Bluetooth) on USART3. rusEFI defaults these to PC10/PC11, which this board
    // uses for the SD card on SPI3. Wiring: PB10 -> HC-05 RXD, PB11 <- HC-05 TXD.
    engineConfiguration->binarySerialTxPin = Gpio::B10;
    engineConfiguration->binarySerialRxPin = Gpio::B11;

    // SD card - SPI3
    engineConfiguration->is_enabled_spi_3  = true;
    engineConfiguration->spi3mosiPin        = Gpio::C12;
    engineConfiguration->spi3misoPin        = Gpio::C11;
    engineConfiguration->spi3sckPin         = Gpio::C10;
    engineConfiguration->isSdCardEnabled    = true;
    engineConfiguration->sdCardSpiDevice    = SPI_DEVICE_3;
    engineConfiguration->sdCardCsPin        = Gpio::D2;
}

// Applied after every tune load and reset, so a tune made on another board still gets the threshold PWM
// (the pins are hidden in TunerStudio). The threshold PWM starts once at boot.
static void customBoardConfigOverrides() {
    // VR threshold PWM for the v3.0 VR conditioners, it matters only while PE0 / PE1 is the input
    engineConfiguration->vrThreshold[0].pin = Gpio::A8;    // CKP, TIM1_CH1
    engineConfiguration->vrThreshold[1].pin = Gpio::C6;    // CMP, TIM3_CH1
}

void setup_custom_board_overrides() {
    custom_board_ConfigOverrides = customBoardConfigOverrides;
    custom_board_InitHardware = customBoardInitHardware;
    custom_board_OnConfigurationChange = customBoardOnConfigurationChange;
    custom_board_DefaultConfiguration = customBoardDefaultConfiguration;
}
