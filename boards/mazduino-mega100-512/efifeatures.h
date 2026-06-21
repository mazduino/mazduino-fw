/**
 * @file efifeatures.h
 * Mazduino Mega100-512 (STM32F407VET6 - 512KB flash)
 * Feature overrides to fit in 512KB flash.
 */

#pragma once

#include "../../ext/rusefi/firmware/config/stm32f4ems/efifeatures.h"

/* No USB */
#undef EFI_USB_SERIAL
#define EFI_USB_SERIAL FALSE

/* No Lua */
#undef EFI_LUA
#define EFI_LUA FALSE

/* No SD card storage */
#undef EFI_STORAGE_SD
#define EFI_STORAGE_SD FALSE

/* No Electronic Throttle Body */
#undef EFI_ELECTRONIC_THROTTLE_BODY
#define EFI_ELECTRONIC_THROTTLE_BODY FALSE

/* No software knock (saves ~50KB flash) - leave undefined so #ifdef checks are FALSE */
#undef EFI_SOFTWARE_KNOCK
