# Changelog

All notable changes to Mazduino firmware are documented here.

## [Unreleased]

### Added
- mazduino-mega100: STM32F407VGT6 (1MB) board with full feature set, dual pinout support (board04 and UA4C) selectable via TunerStudio board action
- mazduino-mega100-512: STM32F407VET6 (512KB) board with reduced feature set; firmware constrained to 384KB to keep tune storage sector (sector 7, 0x08060000) free
- Nightly release workflow publishing per-board .bin, .srec, and .hex artifacts as GitHub Releases
- Docker-based build system (`build_boards.sh`) using `--platform linux/amd64` for consistent builds on Apple Silicon and x86-64
- TunerStudio UI flags in `prepend.txt` to hide ETB, traction control, boost, rotary, Harley-Davidson, torque model, and other features not applicable to each board variant

### Changed
- mazduino-mega100 and mega100-512: status LED at PB7 enabled (`getCommsLedPin()` and `LED_CRITICAL_ERROR_BRAIN_PIN` both assigned to PB7)
- mazduino-compact: second idle solenoid field corrected to `secondSolenoidPin`
- mazduino-lite: knock disabled by leaving `EFI_SOFTWARE_KNOCK` undefined (not set to FALSE) so `#ifdef` guards evaluate correctly
- mazduino-mini6ch: `ts_show_traction_control true` enabled as ETB-capable board is the only variant that supports traction control
- Dockerfile updated to handle both `ports.ubuntu.com` (ARM64) and `archive.ubuntu.com` (x86-64) Ubuntu mirror replacements for EOL Mantic release

### Fixed
- Root `board_configuration.cpp`: removed forward declaration of `customBoardTsAction` which caused undefined reference linker error in CI unit test build
- `EFI_EMBED_INI_MSD=FALSE` on mega100-512: the embedded TunerStudio INI file was contributing approximately 155KB to the firmware binary; disabling it reduced firmware from 488KB to 271KB
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
