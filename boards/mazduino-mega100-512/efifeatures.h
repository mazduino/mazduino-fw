/**
 * @file efifeatures.h
 * Mazduino Mega100-512 (STM32F407VET6 - 512KB flash)
 *
 * Firmware code MUST stay below 384KB (0x08060000) because rusefi stores the
 * tune in sector 7 (0x08060000-0x0807FFFF, 128KB) — erasing it for a tune
 * write would brick the ECU if code occupies that sector.
 */

#pragma once

#include "../../ext/rusefi/firmware/config/stm32f4ems/efifeatures.h"

/* No Lua */
#undef EFI_LUA
#define EFI_LUA FALSE

/* No SD card */
#undef EFI_STORAGE_SD
#define EFI_STORAGE_SD FALSE

/* No ETB */
#undef EFI_ELECTRONIC_THROTTLE_BODY
#define EFI_ELECTRONIC_THROTTLE_BODY FALSE

/* No software knock — leave undefined so #ifdef EFI_SOFTWARE_KNOCK is FALSE */
#undef EFI_SOFTWARE_KNOCK

/* Debug/analysis tools — not needed in production firmware */
#undef EFI_TOOTH_LOGGER
#define EFI_TOOTH_LOGGER FALSE

#undef EFI_LOGIC_ANALYZER
#define EFI_LOGIC_ANALYZER FALSE

/* Anti-lag and HPFP (GDI) not applicable to Mazda OEM hardware */
#undef EFI_ANTILAG_SYSTEM
#define EFI_ANTILAG_SYSTEM FALSE

#undef EFI_HPFP
#define EFI_HPFP FALSE

/* CAN GPIO bridging not used */
#undef EFI_CAN_GPIO
#define EFI_CAN_GPIO FALSE

/* Verbose TS output not needed */
#undef EFI_TUNER_STUDIO_VERBOSE
#define EFI_TUNER_STUDIO_VERBOSE FALSE

/* Bluetooth setup not used */
#undef EFI_BLUETOOTH_SETUP
#define EFI_BLUETOOTH_SETUP FALSE

/* Dyno view — nice-to-have but saves code space */
#undef EFI_DYNO_VIEW
#define EFI_DYNO_VIEW FALSE

/* Engine position emulation — debug/bench testing only */
#undef EFI_ENGINE_EMULATOR
#define EFI_ENGINE_EMULATOR FALSE

#undef EFI_EMULATE_POSITION_SENSORS
#define EFI_EMULATE_POSITION_SENSORS FALSE

/* Text console logging — no USB, no UART console exposed on board */
#undef EFI_TEXT_LOGGING
#define EFI_TEXT_LOGGING FALSE

/* CLI support — no console connection on production unit */
#undef EFI_CLI_SUPPORT
#define EFI_CLI_SUPPORT FALSE

/* Alternator control — not commonly required */
#undef EFI_ALTERNATOR_CONTROL
#define EFI_ALTERNATOR_CONTROL FALSE

/* CIC-style idle PID — standard PID still works without it */
#undef EFI_IDLE_PID_CIC
#define EFI_IDLE_PID_CIC FALSE

/* TS scatter gather — saves protocol overhead code */
#undef EFI_TS_SCATTER
#define EFI_TS_SCATTER FALSE

/* Launch control — omitted on 512KB budget variant */
#undef EFI_LAUNCH_CONTROL
#define EFI_LAUNCH_CONTROL FALSE

/* VVT PID closed-loop — omitted on 512KB budget variant */
#undef EFI_VVT_PID
#define EFI_VVT_PID FALSE

/* Vehicle speed sensor support */
#undef EFI_VEHICLE_SPEED
#define EFI_VEHICLE_SPEED FALSE

/* RTC support */
#undef EFI_RTC
#define EFI_RTC FALSE

/* Main relay control via MCU pin — not wired on this board */
#undef EFI_MAIN_RELAY_CONTROL
#define EFI_MAIN_RELAY_CONTROL FALSE

/* Boost control — omitted on 512KB budget variant */
#undef EFI_BOOST_CONTROL
#define EFI_BOOST_CONTROL FALSE

/* Engine sniffer (real-time trigger oscilloscope) — debug tool */
#undef EFI_ENGINE_SNIFFER
#define EFI_ENGINE_SNIFFER FALSE

/* Embedded INI MSD (USB mass storage) — USB is disabled, no point embedding */
#undef EFI_EMBED_INI_MSD
#define EFI_EMBED_INI_MSD FALSE

/* Lua lookup tables — Lua is disabled, LTO strips these but explicitly disable */
#undef EFI_LUA_LOOKUP
#define EFI_LUA_LOOKUP FALSE

/* Clock lock assertions — debug aid */
#undef EFI_CLOCK_LOCKS
#define EFI_CLOCK_LOCKS FALSE
