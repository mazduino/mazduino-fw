/**
 * @file board_configuration.cpp
 * Mazduino Mini 6CH v1.3C
 * https://wiki.mazduino.com/mazduino-mini-6ch-v1.3c/
 */

#include "pch.h"
#include "board_overrides.h"

/**
 * Board revision ID on PC4 (ADC12_IN14), added in v1.3E: R144 10k from VREF+ to PC4 and R145
 * to GND. The reading is ratiometric to the ADC reference, so code = nearest ratio raw / 4095.
 * v1.3D and older have no divider and PC4 floats there.
 *
 * PC4 is read twice, once right after a short internal pull-down and once right after a short
 * pull-up, with the pin back in analog mode for each read (the ~40k internal resistor would
 * shift the higher codes if it stayed on). A fitted divider gives the same ratio both times;
 * a floating pin follows the last pull and the two reads disagree. This also tells code 0
 * (R145 0R) and code 7 (R145 not fitted) apart from a floating pin.
 */
static constexpr int BOARD_ID_UNKNOWN = -1;
static constexpr int BOARD_ID_MINI6CH_V13E = 1;

static constexpr float boardIdRatios[] = {
	0.0f,                    // 0: R145 0R
	2.2f / (10.0f + 2.2f),   // 1: R145 2.2k, v1.3E
	4.7f / (10.0f + 4.7f),   // 2: R145 4.7k
	10.0f / (10.0f + 10.0f), // 3: R145 10k
	22.0f / (10.0f + 22.0f), // 4: R145 22k
	47.0f / (10.0f + 47.0f), // 5: R145 47k
	100.0f / (10.0f + 100.0f), // 6: R145 100k
	1.0f,                    // 7: R145 not fitted
};
static constexpr float boardIdTolerance = 0.03f;

static int boardRevisionId = BOARD_ID_UNKNOWN;

#if EFI_PROD_CODE
// Averaged ratio of PC4 after a short pull in the given pad mode, read with ADC1 by register
// access. This runs before the ADC driver is started, and leaves ADC1 off and unclocked.
static float readBoardIdRatio(iomode_t pullMode) {
	constexpr int sampleCount = 16;

	palSetPadMode(GPIOC, 4, pullMode);
	chThdSleepMilliseconds(2);
	palSetPadMode(GPIOC, 4, PAL_MODE_INPUT_ANALOG);

	uint32_t sum = 0;
	for (int i = 0; i < sampleCount; i++) {
		ADC1->CR2 |= ADC_CR2_SWSTART;
		// One conversion takes about 3 us; give up rather than hang the boot
		for (int wait = 0; wait < 100000 && !(ADC1->SR & ADC_SR_EOC); wait++) {
		}
		sum += ADC1->DR & 0xFFF; // reading DR clears EOC
	}

	return (float)sum / (sampleCount * 4095.0f);
}

static int matchBoardIdCode(float ratio) {
	for (size_t code = 0; code < efi::size(boardIdRatios); code++) {
		if (absF(ratio - boardIdRatios[code]) <= boardIdTolerance) {
			return code;
		}
	}
	return BOARD_ID_UNKNOWN;
}

static void detectBoardRevision() {
	rccEnableADC1(true);
	// Common prescaler, set the same way adcStart() does; CCR can only be written with an ADC clocked
	ADC->CCR = (ADC->CCR & (ADC_CCR_TSVREFE | ADC_CCR_VBATE)) | (STM32_ADC_ADCPRE << 16);
	ADC1->CR1 = 0;  // 12 bit, single channel, no scan
	ADC1->CR2 = ADC_CR2_ADON;
	ADC1->SMPR1 = ADC_SMPR1_SMP_AN14(ADC_SAMPLE_56);
	ADC1->SQR1 = 0; // one conversion
	ADC1->SQR3 = ADC_SQR3_SQ1_N(14);
	chThdSleepMilliseconds(1); // ADC power-up time

	float afterPullDown = readBoardIdRatio(PAL_MODE_INPUT_PULLDOWN);
	float afterPullUp = readBoardIdRatio(PAL_MODE_INPUT_PULLUP);

	ADC1->CR2 = 0;
	ADC1->SMPR1 = 0;
	ADC1->SQR3 = 0;
	rccDisableADC1();

	int codeDown = matchBoardIdCode(afterPullDown);
	int codeUp = matchBoardIdCode(afterPullUp);
	boardRevisionId = (codeDown == codeUp) ? codeDown : BOARD_ID_UNKNOWN;

#ifndef EFI_BOOTLOADER
	// Read-only in TunerStudio as "Detected Board ID": -1 = v1.3D or older, 1 = v1.3E
	engine->engineState.hellenBoardId = boardRevisionId;
#endif
	efiPrintf("Mini 6CH board ID %d (PC4 %.3f / %.3f)", boardRevisionId, afterPullDown, afterPullUp);
}
#endif // EFI_PROD_CODE

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

    // Proto-area dividers: v1.3E has 5.6k/10k, v1.3D and older 470R/910R. Applied with the board
    // defaults only (new board or reset), so a coefficient in a saved tune is never overwritten.
    if (boardRevisionId == BOARD_ID_MINI6CH_V13E) {
        engineConfiguration->analogInputDividerCoefficient = (5.6f + 10.0f) / 10.0f;
    } else {
        engineConfiguration->analogInputDividerCoefficient = (470.0f + 910.0f) / 910.0f;
    }
    engineConfiguration->vbattDividerCoeff = (82.0f + 10.0f) / 10.0f; // 82k high side/10k low side
    engineConfiguration->adcVcc = 3.3f;
    engineConfiguration->clt.config.bias_resistor = 2700;
    engineConfiguration->iat.config.bias_resistor = 2700;

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

    // Secondary TS channel (Bluetooth) on USART3. rusEFI defaults these to
    // PC10/PC11, which this board uses for the SD card on SPI3, so the default
    // would collide. PB10/PB11 are free on mini6ch (mazduino-lite and -core use
    // them for the LPS25 baro; mini6ch has no baro fitted).
    // Wiring: PB10 -> HC-05 RXD, PB11 <- HC-05 TXD.
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

    // Electronic throttle - TLE9201
    setupEtb();
}

void setup_custom_board_overrides() {
#if EFI_PROD_CODE
    // Before the configuration is loaded, so the board defaults on a blank flash already know the revision
    custom_board_InitHardwareEarly = detectBoardRevision;
#endif
    custom_board_DefaultConfiguration = customBoardDefaultConfiguration;
}
