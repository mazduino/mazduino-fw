#include "pch.h"
#include "board_overrides.h"

Gpio getCommsLedPin() {
	return Gpio::B7;
}

Gpio getRunningLedPin() {
	return Gpio::Unassigned;
}

Gpio getWarningLedPin() {
	return Gpio::Unassigned;
}



// board-specific configuration setup
static void customBoardDefaultConfiguration() {
    // engineConfiguration->injectionPins[0] = Gpio::F13;
    // engineConfiguration->ignitionPins[0] = Gpio::E15;

  engineConfiguration->triggerInputPins[0] = Gpio::D3;
//	engineConfiguration->triggerInputPins[1] = Gpio::Unassigned;

	engineConfiguration->map.sensor.hwChannel = EFI_ADC_0;
	engineConfiguration->afr.hwChannel = EFI_ADC_1;
	// Battery sense on PA2
	engineConfiguration->vbattAdcChannel = EFI_ADC_2;
	engineConfiguration->tps1_1AdcChannel = EFI_ADC_3;
	engineConfiguration->clt.adcChannel = EFI_ADC_4;
	engineConfiguration->iat.adcChannel = EFI_ADC_5;


    	// 5.6k high side/10k low side = 1.56 ratio divider
   	engineConfiguration->analogInputDividerCoefficient = 1.47f;

    	// 6.34k high side/ 1k low side
//    	engineConfiguration->vbattDividerCoeff = (6.34 + 1) / 1;

	engineConfiguration->adcVcc = 3.3f;

	engineConfiguration->clt.config.bias_resistor = 2490;
	engineConfiguration->iat.config.bias_resistor = 2490;

    engineConfiguration->isSdCardEnabled = true;
	engineConfiguration->sdCardSpiDevice = SPI_DEVICE_3;

	engineConfiguration->spi3mosiPin = Gpio::C12;
	engineConfiguration->spi3misoPin = Gpio::C11;
	engineConfiguration->spi3sckPin = Gpio::C10;
	engineConfiguration->is_enabled_spi_3 = true;
	engineConfiguration->sdCardCsPin = Gpio::D2;
	engineConfiguration->canTxPin = Gpio::D1;
	engineConfiguration->canRxPin = Gpio::D0;


}

void setup_custom_board_overrides() {
    custom_board_DefaultConfiguration = customBoardDefaultConfiguration;
}
