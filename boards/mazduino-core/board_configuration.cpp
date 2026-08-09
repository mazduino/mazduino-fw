/**
 * @file board_configuration.cpp
 * Mazduino Core
 * https://wiki.mazduino.com/mazduino-core/
 *
 * Pinout is identical to the official rusEFI Proteus F4 board.
 */

#include "pch.h"
#include "board_overrides.h"

// 12 low-side outputs, same as official Proteus F4 (LS_1..LS_12)
static const brain_pin_e injPins[] = {
	Gpio::D7,  // LS 1
	Gpio::G9,  // LS 2
	Gpio::G10, // LS 3
	Gpio::G11, // LS 4
	Gpio::G12, // LS 5
	Gpio::G13, // LS 6
	Gpio::G14, // LS 7
	Gpio::B4,  // LS 8
	Gpio::B5,  // LS 9
	Gpio::B6,  // LS 10
	Gpio::B7,  // LS 11
	Gpio::B8,  // LS 12
};

// 12 ignition outputs, same as official Proteus F4 (IGN_1..IGN_12)
static const brain_pin_e ignPins[] = {
	Gpio::D4, // IGN 1
	Gpio::D3, // IGN 2
	Gpio::C9, // IGN 3
	Gpio::C8, // IGN 4
	Gpio::C7, // IGN 5
	Gpio::G8, // IGN 6
	Gpio::G7, // IGN 7
	Gpio::G6, // IGN 8
	Gpio::G5, // IGN 9
	Gpio::G4, // IGN 10
	Gpio::G3, // IGN 11
	Gpio::G2, // IGN 12
};

static void setInjectorPins() {
	copyArray(engineConfiguration->injectionPins, injPins);
}

static void setIgnitionPins() {
	copyArray(engineConfiguration->ignitionPins, ignPins);
}

Gpio getCommsLedPin() { return Gpio::E4; }
Gpio getRunningLedPin() { return Gpio::E5; }
Gpio getWarningLedPin() { return Gpio::E6; }
// PE3 is the critical error LED, configured in board.mk

static void setupVbatt() {
	// 5.6k high side/10k low side = 1.56 ratio divider
	engineConfiguration->analogInputDividerCoefficient = 1.56f;

	// 82k high side/10k low side = 9.2
	engineConfiguration->vbattDividerCoeff = (92.0f / 10.0f);

	// Battery sense on PA7
	engineConfiguration->vbattAdcChannel = EFI_ADC_7;

	engineConfiguration->adcVcc = 3.3f;
}

static void setupEtb() {
	// TLE9201 driver: DIR / PWM / DIS, same as official Proteus F4

	// Throttle #1
	engineConfiguration->etbIo[0].controlPin = Gpio::D12;   // PWM
	engineConfiguration->etbIo[0].directionPin1 = Gpio::D10; // DIR
	engineConfiguration->etbIo[0].disablePin = Gpio::D11;    // Disable

	// Throttle #2
	engineConfiguration->etbIo[1].controlPin = Gpio::D13;   // PWM
	engineConfiguration->etbIo[1].directionPin1 = Gpio::D9;  // DIR
	engineConfiguration->etbIo[1].disablePin = Gpio::D8;     // Disable

	// we only have pwm/dir, no dira/dirb
	engineConfiguration->etb_use_two_wires = false;
}

static void setupDefaultSensorInputs() {
	// Digital 1 (PC6) as default trigger input, same as official Proteus F4
	engineConfiguration->triggerInputPins[0] = Gpio::C6;
	engineConfiguration->camInputs[0] = Gpio::Unassigned;
	engineConfiguration->triggerInputPins[1] = Gpio::Unassigned;

	engineConfiguration->clt.adcChannel = EFI_ADC_8;  // PB0 - Analog Temp 3
	engineConfiguration->iat.adcChannel = EFI_ADC_15; // PC5 - Analog Temp 2
	engineConfiguration->tps1_1AdcChannel = EFI_ADC_11; // PC1 - Analog Volt 2
	engineConfiguration->map.sensor.hwChannel = EFI_ADC_10; // PC0 - Analog Volt 1

	// pin PA5 "Analog Volt 10"
	engineConfiguration->afr.hwChannel = EFI_ADC_5;
}

static void setupSdCard() {
	engineConfiguration->sdCardSpiDevice = SPI_DEVICE_3;
	engineConfiguration->sdCardCsPin = Gpio::D2;

	engineConfiguration->is_enabled_spi_3 = true;
	engineConfiguration->spi3sckPin = Gpio::C10;
	engineConfiguration->spi3misoPin = Gpio::C11;
	engineConfiguration->spi3mosiPin = Gpio::C12;
}

static void customBoardDefaultConfiguration() {
	setInjectorPins();
	setIgnitionPins();
	setupEtb();
	setupSdCard();
	setupVbatt();
	setupDefaultSensorInputs();

	engineConfiguration->isSdCardEnabled = true;
	engineConfiguration->enableSoftwareKnock = true;

	engineConfiguration->clt.config.bias_resistor = 2700;
	engineConfiguration->iat.config.bias_resistor = 2700;

	// CAN
	engineConfiguration->canTxPin = Gpio::D1;
	engineConfiguration->canRxPin = Gpio::D0;
	engineConfiguration->can2RxPin = Gpio::B12;
	engineConfiguration->can2TxPin = Gpio::B13;

	// onboard LPS25 baro sensor
	engineConfiguration->lps25BaroSensorScl = Gpio::B10;
	engineConfiguration->lps25BaroSensorSda = Gpio::B11;

	// LS 10/11/12 double as fuel pump/fan/main relay, same as official Proteus F4
	engineConfiguration->mainRelayPin = Gpio::B8;
	engineConfiguration->fanPin = Gpio::B7;
	engineConfiguration->fuelPumpPin = Gpio::B6;
}

void setup_custom_board_overrides() {
	custom_board_DefaultConfiguration = customBoardDefaultConfiguration;
}
