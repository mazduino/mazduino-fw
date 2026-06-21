# Mazduino ECU Custom Firmware

Custom rusEFI firmware for Mazduino ECU boards and compatible STM32F4-based engine management systems.

## Download

Pre-built firmware is published as nightly releases on the [Releases page](../../releases).

Each release includes `.bin`, `.srec`, and `.hex` files for every supported board.

## Supported Boards

### Mazduino Compact
- MCU: STM32F407VGT6 (1MB flash)
- Hardware knock detection via ADC3/PA3
- Software knock spectrogram
- CAN bus, USB virtual COM port (TunerStudio)
- Dual idle solenoid outputs
- No ETB, no traction control

### Mazduino Lite
- MCU: STM32F407VGT6 (1MB flash)
- No hardware knock (ADC3 not connected)
- CAN bus, USB virtual COM port
- Dual idle solenoid outputs
- No ETB, no traction control

### Mazduino Mini 6CH (STM32F427VGT6)
- MCU: STM32F427VGT6 (1MB flash)
- Electronic throttle body (ETB) support
- Traction control (requires ETB)
- Hardware knock detection
- CAN bus, USB virtual COM port

### Mazduino Mega100 (STM32F407VGT6)
- MCU: STM32F407VGT6 (1MB flash)
- Full feature set: ETB, traction control, knock, boost, launch control
- Dual pinout support: board04 layout and UA4C layout, switchable via TunerStudio board action
- USB virtual COM port and CAN bus for TunerStudio connection
- Status LED at PB7

### Mazduino Mega100-512 (STM32F407VET6)
- MCU: STM32F407VET6 (512KB flash)
- Firmware constrained to 384KB to preserve tune storage sector
- Feature reduction vs Mega100: no ETB, no knock, no boost control, no launch control, no Lua, no SD card
- CAN bus or USB virtual COM port for TunerStudio connection
- Status LED at PB7

## TunerStudio Connection

| Board | Connection |
|-------|------------|
| Compact, Lite, Mini 6CH | USB virtual COM port |
| Mega100 | USB virtual COM port or CAN bus |
| Mega100-512 | USB virtual COM port or CAN bus |

## Building Firmware

### Local Build (Docker)

Docker is required. The build image uses Ubuntu Mantic with ARM GCC toolchain.

```bash
# Build all boards
./build_boards.sh

# Build a single board
./build_boards.sh mazduino-compact
```

The script uses `--platform linux/amd64` to ensure hex2dfu.bin (x86-64) runs correctly on Apple Silicon via Rosetta 2.

### CI Build (GitHub Actions)

All boards are built automatically on every push via the matrix workflow in `.github/workflows/build-matrix.yaml`. Nightly releases are published by `.github/workflows/nightly-release.yaml`.

## Flash Instructions

### ST-Link or SWD

Use STM32CubeProgrammer or OpenOCD with the `.bin` file:

```bash
st-flash write rusefi_mazduino-compact.bin 0x08000000
```

### DFU (USB bootloader)

Put the board into DFU mode (hold BOOT0 while resetting), then:

```bash
dfu-util -d 0483:df11 -a 0 -s 0x08000000:leave -D rusefi_mazduino-compact.bin
```

### OpenBLT Bootloader

Use the `.srec` file with the rusEFI Flasher tool or BootCommander.

## Repository Structure

```
boards/
  mazduino-compact/       # Board-specific configuration files
  mazduino-lite/
  mazduino-mini6ch/
  mazduino-mega100/
  mazduino-mega100-512/
ext/rusefi/               # rusEFI submodule
generated/                # Auto-generated code (configs, headers, INI files)
.github/workflows/        # CI/CD workflows
```

Each board directory contains:
- `meta-info.env` - Board identity and CPU selection
- `board.mk` - Makefile flags and feature overrides
- `board_configuration.cpp` - Pin assignments and hardware init
- `efifeatures.h` (optional) - Feature flag overrides
- `prepend.txt` - TunerStudio UI visibility flags
- `knock_config.h` - Knock sensor configuration

## Safety Notice

This is engine management software controlling critical engine functions. Test on a bench setup before installing in a vehicle. Incorrect configuration can cause engine damage.

## Links

- [rusEFI Project](https://github.com/rusefi/rusefi)
- [rusEFI Custom Firmware Guide](https://github.com/rusefi/rusefi/wiki/Custom-Firmware)
- [Mazduino Wiki](https://wiki.mazduino.com/)
