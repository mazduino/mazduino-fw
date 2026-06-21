#include "pch.h"
#include "board_overrides.h"

Gpio getCommsLedPin() {
	return Gpio::Unassigned;
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

void customBoardTsAction(uint16_t subSystem, uint16_t index);
    custom_board_ts_command = customBoardTsAction;
}
