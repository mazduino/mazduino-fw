#include "pch.h"
#include "board_overrides.h"

Gpio getCommsLedPin() {
	return config->communityCommsLedPin;
}

Gpio getRunningLedPin() {
	return Gpio::Unassigned;
}

Gpio getWarningLedPin() {
	return Gpio::Unassigned;
}



// board-specific configuration setup
static void customBoardDefaultConfiguration() {


}

void setup_custom_board_overrides() {
    custom_board_DefaultConfiguration = customBoardDefaultConfiguration;
}
