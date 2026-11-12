/**
 * @file speeduino_presets.cpp
 * Pin presets for running the Mazduino Mega100 on a Speeduino board through the
 * STM32F407 Mega converter v1.3, applied from TunerStudio (TS_BOARD_ACTION).
 *
 * Each preset lists the Arduino Mega pins of one Speeduino board, copied from
 * speeduino/speeduino src/pins/pinMapping.cpp, and megaHeader[] turns them into
 * STM32 pins. Pins a preset cannot use are left out:
 * - D21 and D46 are not wired on the converter.
 * - D43 also drives the converter's status LED (PB7, the critical error LED).
 * - An output on an analog header pin: those go through the converter's input buffers.
 * - A second function on a pin already taken, or a second input on the same EXTI line.
 * - 01-05 MX5 PNP is missing: its coil 2 is on D43 and injector 2 on D46.
 */

#include "pch.h"
#include "speeduino_presets.h"

namespace {

constexpr uint8_t NC = 0xFF;
constexpr uint8_t ANALOG = 100;
constexpr uint8_t A(int n) { return ANALOG + n; }

// Converter v1.3: Arduino Mega header pin D0..D53 -> STM32 pin.
const Gpio megaHeader[54] = {
	Gpio::A10, Gpio::A9,  Gpio::D7,  Gpio::B6,  Gpio::B12, Gpio::B13, Gpio::B14, Gpio::B15, // D0-D7
	Gpio::D8,  Gpio::D9,  Gpio::D10, Gpio::D11, Gpio::A8,  Gpio::B3,  Gpio::D5,  Gpio::D6,  // D8-D15
	Gpio::B10, Gpio::B11, Gpio::D4,  Gpio::D3,  Gpio::B4,  Gpio::Unassigned, Gpio::C9, Gpio::C8, // D16-D23
	Gpio::A15, Gpio::B5,  Gpio::C7,  Gpio::B2,  Gpio::C6,  Gpio::E1,  Gpio::D14, Gpio::D15, // D24-D31
	Gpio::D12, Gpio::D13, Gpio::E5,  Gpio::E15, Gpio::E4,  Gpio::E14, Gpio::E3,  Gpio::E13, // D32-D39
	Gpio::E2,  Gpio::E12, Gpio::E10, Gpio::B7,  Gpio::E0,  Gpio::E11, Gpio::Unassigned, Gpio::E9, // D40-D47
	Gpio::E6,  Gpio::E8,  Gpio::E7,  Gpio::B8,  Gpio::C13, Gpio::B9, // D48-D53
};

struct SpeeduinoPins {
	const char* name;
	// Trigger2 is the second trigger channel (two-channel crank/cam patterns) instead of the cam input.
	bool trigger2IsSecondary;
	uint8_t inj1, inj2, inj3, inj4;
	uint8_t coil1, coil2, coil3, coil4;
	uint8_t trigger, trigger2;
	uint8_t tps, map, iat, clt, o2, o2_2, bat, baro;
	uint8_t fuelPump, tach, fan, idle1, idle2, boost, vvt1;
	uint8_t stepperDir, stepperStep, stepperEnable;
	uint8_t vss, flex, launch;
};

// Index = TS_BOARD_ACTION index; keep the order, board_commands.ini depends on it.
const SpeeduinoPins presets[] = {
	// Speeduino v0.2 (Speeduino board 1)
	{ "Speeduino v0.2", false, 8, 9, 10, 11, 28, 24, 40, 36, 20, NC, A(2), A(3), A(0), A(1), A(8), NC, A(4), NC, 4, 49, 47, 30, 31, NC, NC, 16, 17, NC, NC, 2, NC },
	// Speeduino v0.3 (Speeduino board 2)
	{ "Speeduino v0.3", false, 8, 9, 10, 11, 28, 24, 40, 36, 19, 18, A(2), A(3), A(0), A(1), A(8), NC, A(4), A(5), 4, 49, NC, 5, 53, 7, 6, 16, 17, 26, NC, 2, 51 },
	// Speeduino v0.4 (Speeduino board 3)
	{ "Speeduino v0.4", false, 8, 9, 10, 11, 40, 38, 52, 50, 19, 18, A(2), A(3), A(0), A(1), A(8), NC, A(4), A(5), 45, 49, 47, 5, 6, 7, 4, 16, 17, 24, NC, 2, 51 },
	// 96-97 MX5 PNP (Speeduino board 8)
	{ "96-97 MX5 PNP", true, 11, 10, 9, 8, 39, 41, 32, 33, 19, 18, A(2), A(5), A(0), A(1), A(3), NC, A(4), NC, 49, NC, 35, 2, NC, 4, NC, 16, 17, 24, NC, 3, 37 },
	// NA6 MX5 PNP (Speeduino board 9)
	{ "NA6 MX5 PNP", true, 11, 10, 9, 8, 39, 41, 32, 33, 19, 18, A(2), A(5), A(0), A(1), A(3), NC, A(4), NC, 37, 49, 35, 2, NC, 4, NC, 16, 17, 15, NC, 3, 12 },
	// Turtana PCB (Speeduino board 10)
	{ "Turtana PCB", false, 4, 5, 6, 7, 24, 28, 36, 40, 18, 19, A(2), A(3), A(0), A(1), A(4), NC, A(7), NC, 42, 49, 47, NC, NC, NC, NC, NC, NC, NC, NC, 2, NC },
	// Plazomat I/O 0.1 (Speeduino board 20)
	{ "Plazomat I/O 0.1", false, 8, 9, 10, 11, 28, 24, 40, 36, 20, NC, A(2), A(3), A(0), A(1), A(8), NC, A(4), NC, 4, 49, 47, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC },
	// Daz V6 Shield 0.1 (Speeduino board 30)
	{ "Daz V6 Shield 0.1", false, 8, 9, 10, 11, 40, 38, 50, 52, 19, 18, A(2), A(3), A(0), A(1), A(8), A(9), A(4), NC, 45, 49, 47, 5, NC, 7, NC, NC, NC, NC, NC, NC, NC },
	// BMW PnP (Speeduino board 31)
	{ "BMW PnP", false, 8, 9, 10, 11, 40, 38, 52, 48, 19, 18, A(2), A(3), A(0), A(1), A(8), A(12), A(4), A(5), 45, 49, 47, 5, 6, 7, 4, 16, 17, 24, 3, 2, 51 },
	// NO2C (Speeduino board 40)
	{ "NO2C", false, 8, 9, 11, 12, 23, 22, 2, 3, 19, 18, A(3), A(0), A(5), A(4), A(2), NC, A(1), A(6), 4, 38, 30, 5, 47, 7, 6, 25, 24, 27, NC, NC, 10 },
	// UA4C (Speeduino board 41)
	{ "UA4C", false, 8, 7, 6, 5, 35, 36, 33, 34, 19, 18, A(3), A(0), A(5), A(4), A(1), A(9), A(2), A(7), 23, 22, 24, 9, 10, 12, 11, 32, 31, 30, 2, NC, 37 },
	// BlitzboxBL49sp (Speeduino board 42)
	{ "BlitzboxBL49sp", false, 6, 7, 8, 9, 24, 25, 23, 22, 19, 18, A(0), A(7), A(3), A(4), A(2), A(9), A(6), A(5), 3, 10, 12, 11, 14, 5, 15, NC, NC, NC, NC, NC, 2 },
	// DIY-EFI CORE4 v1.0 (Speeduino board 45)
	{ "DIY-EFI CORE4 v1.0", false, 10, 11, 12, 9, 39, 29, 28, 27, 19, 18, A(3), A(2), A(11), A(4), A(12), A(5), A(1), A(15), 41, 38, 40, 42, NC, 45, 44, 32, 31, 30, NC, NC, 24 },
};

Gpio digital(uint8_t pin) {
	return pin < efi::size(megaHeader) ? megaHeader[pin] : Gpio::Unassigned;
}

adc_channel_e analog(uint8_t pin) {
	// A0..A15 reach PA0-PA7, PB0, PB1, PC0-PC5 through the buffers, which is EFI_ADC_0..EFI_ADC_15.
	return pin >= ANALOG && pin < ANALOG + 16 ? (adc_channel_e)(EFI_ADC_0 + (pin - ANALOG)) : EFI_ADC_NONE;
}

// Every pin a preset may set, plus the board defaults that sit on header pins, so nothing
// from the previous wiring is left behind on a pin the Speeduino board uses for something else.
void clearHeaderPins() {
	for (size_t i = 0; i < efi::size(engineConfiguration->injectionPins); i++) {
		engineConfiguration->injectionPins[i] = Gpio::Unassigned;
		engineConfiguration->ignitionPins[i] = Gpio::Unassigned;
	}
	for (size_t i = 0; i < efi::size(engineConfiguration->triggerInputPins); i++) {
		engineConfiguration->triggerInputPins[i] = Gpio::Unassigned;
	}
	for (size_t i = 0; i < efi::size(engineConfiguration->camInputs); i++) {
		engineConfiguration->camInputs[i] = Gpio::Unassigned;
		engineConfiguration->vvtPins[i] = Gpio::Unassigned;
	}
	engineConfiguration->tps1_1AdcChannel = EFI_ADC_NONE;
	engineConfiguration->map.sensor.hwChannel = EFI_ADC_NONE;
	engineConfiguration->iat.adcChannel = EFI_ADC_NONE;
	engineConfiguration->clt.adcChannel = EFI_ADC_NONE;
	engineConfiguration->afr.hwChannel = EFI_ADC_NONE;
	engineConfiguration->afr.hwChannel2 = EFI_ADC_NONE;
	engineConfiguration->vbattAdcChannel = EFI_ADC_NONE;
	engineConfiguration->baroSensor.hwChannel = EFI_ADC_NONE;

	engineConfiguration->fuelPumpPin = Gpio::Unassigned;
	engineConfiguration->tachOutputPin = Gpio::Unassigned;
	engineConfiguration->fanPin = Gpio::Unassigned;
	engineConfiguration->fan2Pin = Gpio::Unassigned;
	engineConfiguration->idle.solenoidPin = Gpio::Unassigned;
	engineConfiguration->secondSolenoidPin = Gpio::Unassigned;
	engineConfiguration->boostControlPin = Gpio::Unassigned;
	engineConfiguration->idle.stepperDirectionPin = Gpio::Unassigned;
	engineConfiguration->idle.stepperStepPin = Gpio::Unassigned;
	engineConfiguration->stepperEnablePin = Gpio::Unassigned;
	engineConfiguration->vehicleSpeedSensorInputPin = Gpio::Unassigned;
	engineConfiguration->flexSensorPin = Gpio::Unassigned;
	engineConfiguration->launchActivatePin = Gpio::Unassigned;

	engineConfiguration->mainRelayPin = Gpio::Unassigned;
	engineConfiguration->acSwitch = Gpio::Unassigned;
	engineConfiguration->acRelayPin = Gpio::Unassigned;
	engineConfiguration->clutchDownPin = Gpio::Unassigned;
}

} // namespace

bool applySpeeduinoPreset(uint16_t index) {
	if (index >= efi::size(presets)) {
		return false;
	}
	const SpeeduinoPins& p = presets[index];
	efiPrintf("Speeduino pin preset: %s", p.name);

	clearHeaderPins();

	engineConfiguration->injectionPins[0] = digital(p.inj1);
	engineConfiguration->injectionPins[1] = digital(p.inj2);
	engineConfiguration->injectionPins[2] = digital(p.inj3);
	engineConfiguration->injectionPins[3] = digital(p.inj4);
	engineConfiguration->ignitionPins[0] = digital(p.coil1);
	engineConfiguration->ignitionPins[1] = digital(p.coil2);
	engineConfiguration->ignitionPins[2] = digital(p.coil3);
	engineConfiguration->ignitionPins[3] = digital(p.coil4);

	engineConfiguration->triggerInputPins[0] = digital(p.trigger);
	if (p.trigger2IsSecondary) {
		engineConfiguration->triggerInputPins[1] = digital(p.trigger2);
	} else {
		engineConfiguration->camInputs[0] = digital(p.trigger2);
	}

	engineConfiguration->tps1_1AdcChannel = analog(p.tps);
	engineConfiguration->map.sensor.hwChannel = analog(p.map);
	engineConfiguration->iat.adcChannel = analog(p.iat);
	engineConfiguration->clt.adcChannel = analog(p.clt);
	engineConfiguration->afr.hwChannel = analog(p.o2);
	engineConfiguration->afr.hwChannel2 = analog(p.o2_2);
	engineConfiguration->vbattAdcChannel = analog(p.bat);
	engineConfiguration->baroSensor.hwChannel = analog(p.baro);

	engineConfiguration->fuelPumpPin = digital(p.fuelPump);
	engineConfiguration->tachOutputPin = digital(p.tach);
	engineConfiguration->fanPin = digital(p.fan);
	engineConfiguration->idle.solenoidPin = digital(p.idle1);
	engineConfiguration->secondSolenoidPin = digital(p.idle2);
	engineConfiguration->boostControlPin = digital(p.boost);
	engineConfiguration->vvtPins[0] = digital(p.vvt1);
	engineConfiguration->idle.stepperDirectionPin = digital(p.stepperDir);
	engineConfiguration->idle.stepperStepPin = digital(p.stepperStep);
	engineConfiguration->stepperEnablePin = digital(p.stepperEnable);
	engineConfiguration->vehicleSpeedSensorInputPin = digital(p.vss);
	engineConfiguration->flexSensorPin = digital(p.flex);
	engineConfiguration->launchActivatePin = digital(p.launch);

	// D16/D17 are USART3 (PB10/PB11), the Bluetooth TunerStudio port by default. Speeduino boards
	// wire them to the stepper driver, so the port gives way when the preset uses them.
	if (p.stepperDir == 16 || p.stepperStep == 17) {
		engineConfiguration->binarySerialTxPin = Gpio::Unassigned;
		engineConfiguration->binarySerialRxPin = Gpio::Unassigned;
	}
	return true;
}
