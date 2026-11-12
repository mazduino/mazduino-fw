# Changelog

All notable changes to Mazduino firmware are documented here.

## [Unreleased]

### Breaking Changes
- VVT target tables enlarged from 8x8 to 16x16 on mazduino-compact, mazduino-core, mazduino-lite and mazduino-mini6ch, giving finer RPM and load resolution for cam targeting. This changes the tune layout, so existing tunes are not compatible — re-flash and re-enter the VVT tables after updating. mazduino-mega100 and mazduino-mega100-512 keep the 8x8 tables
- LTFT trim map now has its own axes (`ltftLoadBins` / `ltftRpmBins`) instead of borrowing the VE table axes. Every board gains these two fields, so all boards need a matching firmware and INI; table dimensions are unchanged on existing boards, so tune values still carry over

### Added
- mazduino-mega100 and mazduino-mega100-512: Speeduino board pin buttons under Base Tunes, for running the board on a Speeduino shield through the STM32F407 Mega converter v1.3. One button per Speeduino board (v0.2, v0.3, v0.4, 96-97 MX5 PNP, NA6 MX5 PNP, Turtana PCB, Plazomat I/O 0.1, Daz V6 Shield 0.1, BMW PnP, NO2C, UA4C, BlitzboxBL49sp, DIY-EFI CORE4 v1.0) sets the injector, coil, trigger, analog sensor and output pins from that board's Arduino Mega pins, then saves; power cycle afterwards. A pin is left unassigned when the converter cannot carry it: D21 and D46 are not wired, D43 is the status LED (PB7), outputs on analog header pins go through input buffers, and a second input on the same EXTI line is dropped. 01-05 MX5 PNP is not offered because its coil 2 is on D43 and injector 2 on D46. These replace the old "0.4 board" and "ua4c" actions, whose injector pins did not match the converter
- Verbose CAN broadcast, frame base+11 (0x20B at the default base): now 8 bytes long and carries launch control and boost target. Byte 0: bit 0 brake pedal (unchanged), bit 1 launch control limiting now, bit 2 launch switch on, bit 3 closed-loop boost control running. Bytes 2-3: closed-loop boost target, little-endian uint16, 0.0333 kPa per bit (absolute, same scale as MAP in base+3), 0 when bit 3 is off. Byte 1 and bytes 4-7 are reserved and read 0. The frame used to go out with DLC 1, so dashes that only accept 8-byte verbose frames never saw the brake pedal. Existing fields did not move. See `rusEFI_CAN_verbose.dbc`
- A/C Idle fuel adder (`acIdleFuelAdder`, Setup > Air Conditioning): extra fuel in % at idle while the A/C button is on, for Alpha-N engines with a bypass idle valve. The A/C Idle adder opens the idle valve, but that air never moves TPS, so Alpha-N added no fuel for it and the engine went lean and dropped RPM when the compressor engaged. The fuel is added exactly while the idle controller adds the A/C air: at idle, in the after-start taper, and while coasting when the coasting table is on. It starts with the A/C button, before the compressor delay ends. With the throttle open no A/C air is added, so no fuel is either. Shown only when Fuel strategy is Alpha-N. Leave it at 0 when idle runs on the electronic throttle, because TPS already sees that air. It uses a byte that was padding, so existing tunes load unchanged
- Temporary cylinder shutoff command (`TS_CYLINDER_CUT`) for finding a weak cylinder by its RPM drop: cuts fuel and spark of the chosen cylinders, only with sequential injection, always leaves at least one cylinder firing, and every cut ends by itself 10 seconds after the last command. Sent by the Mazduino Tuner diagnostics page; TunerStudio has the commands but no button for them. In firmware since Nightly 2026-11-04
- TunerStudio over Bluetooth on every board: USART3 (PB10/PB11) on compact, mega100 and mega100-512, USART1 (PA9/PA10) on lite, where PB10/PB11 carry the baro sensor. mazduino-core already has its TunerStudio port on PD5/PD6. Applies to the BIGFUEL variants too
- Transmission control built on every board that shows its pages (`EFI_TCU`). The pages were there before but nothing behind them ran. It stays idle until enabled in the tune
- mazduino-mini6ch: secondary TunerStudio channel on USART3 (PB10 = TXD3, PB11 = RXD3), for a Bluetooth module such as an HC-05. The firmware previously had no secondary channel at all — the whole thing is behind `#ifdef TS_SECONDARY_UxART_PORT` and no Mazduino board defined it, so the `binarySerial` pins in TunerStudio did nothing and the ECU never sent a byte to the module. Uses the ChibiOS Serial driver (SD3), the same way the reference f407-discovery board does; the UART driver would need `HAL_USE_UART`, which halconf.h only enables when `TS_PRIMARY_UxART_PORT` is defined. Pin defaults are PB10/PB11 because rusEFI's own defaults, PC10/PC11, are the SD card's SPI3 pins on every Mazduino board. Baud follows `tunerStudioSerialSpeed` (38400 by default), and the channel is started once at boot, so changing that value needs an ECU restart, not just a burn. Applies to mazduino-mini6ch-bigfuel too
- BIGFUEL board variants: `mazduino-compact-bigfuel`, `mazduino-core-bigfuel`, `mazduino-lite-bigfuel` and `mazduino-mini6ch-bigfuel`. Identical hardware and pinout to the board they are named after, with a 32x32 VE table and 32x32 ignition table (stock boards stay 16x16) for finer resolution on high-output builds. Tunes are not interchangeable between a board and its BIGFUEL variant
- BIGFUEL variants trade the engine sniffer for the bigger tables: the persistent config lives in the 64KB CCM RAM and its leftovers feed the Lua heap, so 32x32 tables overflowed CCM by ~1.4KB. Disabling the engine sniffer frees its 5000-byte `WAVE_LOGGING_BUFFER` from CCM. All other features are unchanged from the base board — the real-time trigger oscilloscope in TunerStudio is the only thing missing
- Separate `LTFT_LOAD_COUNT` / `LTFT_RPM_COUNT` sizing for the long-term fuel trim map, independent of the VE table. The learned trim map stays 16x16 even on BIGFUEL boards, saving 6KB of RAM versus following a 32x32 VE table, with no loss of tuning resolution. LTFT trims are now interpolated onto the VE table when applied, so the two grids no longer have to match
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
- Live data is served at most every 10 ms (100 Hz). A client that polls back to back, such as a tuner set to its fastest rate, used to keep the USB thread busy at about 260 Hz and a third of the CPU; it now gets 100 Hz. Measured on a Mazduino Lite: 263 Hz before, 100.0 Hz after
- CI (nightly-release): the release body lists all 10 boards, including the four BIGFUEL variants, and links `boards/FEATURES.md`. It listed only 6 boards, and still called mini6ch an F427-only board
- mazduino-core: software knock is off by default. The firmware still supports it, but the 48-pin carrier connector does not bring the knock input out. A tune that already has it on keeps its setting
- CI (nightly-release): release notes list only what changed since the previous nightly tag (the CHANGELOG lines added since then, or the commits when there are none). They used to repeat the whole `[Unreleased]` section, which is never cut, so every release showed every change ever made
- CI (build-matrix): config push-back disabled on master (`push=false`). Every board job in the matrix runs in parallel and each would `git push` regenerated configs to master, so all but the first failed with "fetch first"/non-fast-forward. mazduino commits generated files manually, so the CI push-back is unnecessary
- CI (build-matrix): simulator build disabled on master (`sim=false`). mazduino ships custom boards only — `bundle.mk` already excludes the simulator from custom-board bundles — and the shared f407-discovery generated headers the simulator compiles against lack mazduino's added config fields (`fuelDensity`, DFCO switch, analog multi-switch), so the simulator cannot compile. This was previously masked because the old `mazduino` branch never triggered the simulator build
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
- mazduino-mega100 and mazduino-mega100-512: "Pin PB7 required by led: comm status but is used by led: CRITICAL status" stopped the ECU at start. PB7 is the critical error LED; the comms LED now defaults to unassigned and a tune that still has it on PB7 is ignored
- Check engine light: with "Active while engine not running" on, the lamp now lights whenever the ECU is on and the engine is stopped (key-on bulb check); with it off, the lamp is off. Before, the lamp kept whatever state it had when the engine stopped. In firmware since Nightly 2026-11-04
- Check engine light: the lamp is held off during "Delay after start" instead of keeping its last state. In firmware since Nightly 2026-11-04
- Check engine light: when sensor checking or the shift light is on, only that module drives the lamp. The standard warning blink wrote the same pin as well, so the lamp pulsed and fought its own state. In firmware since Nightly 2026-11-04
- Triggered CAN output: the "Send frame 1..8" buttons did nothing, because the command they send did not exist and the firmware had no handler. They now send the configured frame right away (`TS_TRIGGERED_CAN_SEND`). In firmware since Nightly 2026-11-04
- CLT and IAT calibration temperatures 1 and 2 showed pressure units (kPa/psi) instead of temperature units. In firmware since Nightly 2026-11-04
- The warning text the ECU reports to the tuner (`e` command) could be random bytes until the first warning was stored, because that buffer lives in RAM that is not cleared at boot. It now starts empty. In firmware since Nightly 2026-11-04
- Unit tests did not link after the cylinder shutoff command was added: `isCylinderCutForTest` is now stubbed for unit test builds. Firmware was not affected
- TunerStudio VE Analyze (AutoTune) always removed fuel, even when the engine was lean (e.g. AFR 17 vs 14.7 target), until it went lean enough to stall. The STFT channel offset had been changed from `-1.0` to `-100`; TunerStudio converts with `(raw + translate) * scale`, so at neutral STFT `stftCorrection1` read -9900 and `egoCorrectionForVeAnalyze = 100 + stftCorrection1` fed -9800 instead of 100. Ported the upstream rusEFI fixes: STFT offset back to `-1.0`, `egoCorrectionForVeAnalyze` now reads `Gego` (already 100 at neutral), and VE Analyze uses a mode-independent target table (`veAnalyzeTargetTableTbl`) and AFR/lambda channel (`veAnalyzeAfrLambda1`). INI-only change: projects on an affected INI can be fixed by updating the INI, no reflash needed. VE tables tuned with the broken INI should be restored from a restore point
- mazduino-mini6ch: firmware now runs on both STM32F407 (earlier boards) and STM32F427 (current boards). It was built as F427 only, which links RAM as 192KB and places the heap and thread stacks in SRAM3 — memory the F407 does not have — so an F407 board hard-faulted at boot and USB never enumerated. Built for the F407 again; on an F427 the chip is detected at runtime and its extra 64KB SRAM3 goes to the Lua heap. Applies to mazduino-mini6ch-bigfuel too
- mazduino-lite: onboard LPS25 barometric sensor was never configured, so `initBaro()` had no pins to talk to and barometric correction silently fell back to a fixed value. Set `lps25BaroSensorScl`/`Sda` to PB10/PB11, matching the schematic (BARO_SCL/BARO_SDA) and mazduino-core. Existing tunes keep their stored values, so this takes effect on a config reset or a fresh tune
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
