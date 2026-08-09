# Changelog

All notable changes to Mazduino firmware are documented here.

## [Unreleased]

### Added
- DFCO enable switch input (`coastingFuelCutSwitchPin`): assign a pin to control DFCO via a physical switch; switch ON allows fuel cut per RPM/TPS/CLT parameters, switch OFF disables fuel cut entirely; leave unassigned for parameter-only control
- Rotational Idle manual enable switch input (`rotationalIdleController.switchPin`): when switch is ON, rotational idle is forced active regardless of automatic CLT/TPS conditions
- Rotational Idle RPM window (`minRpm`, `maxRpm`): configurable RPM range for rotational idle engagement; 0 = no limit; displayed in live data as `rotIdleEngineTooSlow` / `rotIdleEngineTooFast`
- Fuel consumption output channels: trip-average L/100km and instantaneous L/hr, user-configurable via TunerStudio (Engine > Fuel Consumption); requires VSS, injection enabled, and injector flow set
- Predefined TunerStudio gauges for fuel consumption (`fuelConsumptionL100kmGauge`, `fuelConsumptionLitersPerHourGauge`) under the Fueling category, so L/100km and L/hr are selectable from the right-click gauge picker (rusefi-core `gauge_declarations.ini`)
- `fuelConsumptionEnabled` bit and `fuelDensity` (g/L, default 750 petrol) added to engine configuration; calculation runs in `TripOdometer::onSlowCallback()`
- `OUTCH_FuelConsumptionL100km` and `OUTCH_FuelConsumptionLitersPerHour` added to `output_channel_e` enum for Lua access
- `common.mk`: added `$(PROJECT_DIR)/$(META_OUTPUT_ROOT_FOLDER)controllers/generated` to `ALLINC` so the unit test build finds board-specific generated headers when `META_OUTPUT_ROOT_FOLDER` points outside the firmware tree
- Nightly release workflow publishing per-board .bin, .srec, and .hex artifacts as GitHub Releases
- Docker-based build system (`build_boards.sh`) using `--platform linux/amd64` for consistent builds on Apple Silicon and x86-64
- TunerStudio UI flags in `prepend.txt` to hide ETB, traction control, boost, rotary, Harley-Davidson, torque model, and other features not applicable to each board variant
- mazduino-mega100: STM32F407VGT6 (1MB) board with full feature set, dual pinout support (board04 and UA4C) selectable via TunerStudio board action
- mazduino-mega100-512: STM32F407VET6 (512KB) board with reduced feature set; firmware constrained to 384KB to keep tune storage sector (sector 7, 0x08060000) free

### Changed
- TunerStudio menu: Fuel Consumption moved from Advanced to Fuel menu (after DFCO entry)
- TunerStudio menu: Rotational Idle moved from Advanced to Idle menu
- TunerStudio dialog: Fuel Consumption dialog removes duplicate VSS input pin and Injector Flow fields (already configurable in their own dedicated menus)
- `_compile_unit_tests.sh` updated to use `boards/mazduino-lite/meta-info.env` as the reference board (replacing deleted root `meta-info.env`)
- `generated/controllers/generated/` pre-generated headers regenerated to include CAN input/output feature structs and new enum values from the mazduino rusefi fork
- mazduino-mega100 and mega100-512: status LED at PB7 enabled (`getCommsLedPin()` and `LED_CRITICAL_ERROR_BRAIN_PIN` both assigned to PB7)
- mazduino-compact: second idle solenoid field corrected to `secondSolenoidPin`
- mazduino-lite: knock disabled by leaving `EFI_SOFTWARE_KNOCK` undefined (not set to FALSE) so `#ifdef` guards evaluate correctly
- mazduino-mini6ch: `ts_show_traction_control true` enabled as ETB-capable board is the only variant that supports traction control
- mazduino-mini6ch and mazduino-core: stepper idle valve exposed in TunerStudio — added `panel = idleStepper` to the `idleHwType` (Idle Valve Hardware) dialog and the `Use Stepper` enable toggle (`useStepperIdle`) to the `idlehw` dialog in the generated INI, matching the official rusEFI layout; the Stepper option now appears alongside Solenoid with a working enable/disable control. No firmware rebuild required since the stepper config fields already exist at fixed offsets. Intentionally left hidden on mazduino-lite and mazduino-compact (hardware does not support stepper idle)
- Dockerfile updated to handle both `ports.ubuntu.com` (ARM64) and `archive.ubuntu.com` (x86-64) Ubuntu mirror replacements for EOL Mantic release

### Removed
- Root `meta-info.env` (SHORT_BOARD_NAME=mazduino): generic board identifier removed; all builds now reference a named board variant

### Fixed
- mazduino-mini6ch: PD14 pin conflict between the stepper driver enable (`stepperEnablePin`, MCU-ENBL → DRV8825 EN via JP6 manual-enable jumper) and the critical-error LED. mini6ch never overrode `LED_CRITICAL_ERROR_BRAIN_PIN`, so it inherited the rusEFI default of PD14 and claimed the pin before the stepper could use it. Moved the critical-error LED to the dedicated onboard PB4 LED (mini6ch has 3 LEDs — PB4, PB6, PB7 — with PB7 reserved for comms), freeing PD14 for stepper enable. Requires a firmware rebuild
- Root `board_configuration.cpp`: removed forward declaration of `customBoardTsAction` which caused undefined reference linker error in CI unit test build
- `EFI_EMBED_INI_MSD=FALSE` on mega100-512: the embedded TunerStudio INI file was contributing approximately 155KB to the firmware binary; disabling it reduced firmware from 488KB to 271KB
- `EFI_EMBED_INI_MSD=FALSE` on all boards (mazduino-lite, mazduino-compact, mazduino-mini6ch, mazduino-mega100): CAN feature additions grew firmware beyond the 768KB linker budget; disabling INI embedding removes the 160KB ramdisk from flash. The TunerStudio INI is published as a GitHub Releases artifact instead
- `EFI_HPFP=FALSE` on all boards: high-pressure fuel pump (GDI) control is not applicable to Mazda port-injection hardware; disabling it removes unused code
- `board_unit_tests.mk`: added `BOARDINC` pointing to `generated/controllers/generated/` so the unit test build can find `rusefi_generated_mazduino.h` (previously the compiler could not find this file because the unit test Makefile does not include `rusefi.mk` which is what adds that path for firmware builds)

## [2025-01-01]

### Added
- Initial multi-board support: mazduino-compact, mazduino-lite, mazduino-mini6ch
- Hardware knock detection on compact via ADC3/PA3
- Per-board `prepend.txt` for TunerStudio UI customization
- GitHub Actions matrix build (`build-matrix.yaml`) scanning `boards/` directory automatically
- Unit test build (`unit-tests.yaml`)
- rusEFI submodule reference tracking (`update-rusefi-reference.yaml`)

### Changed
- Engine displacement updated to 1.8L default
- Knock ADC channel updated to ADC3/PA3 for improved signal isolation
