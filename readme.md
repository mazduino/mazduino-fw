# Mazduino ECU Custom Firmware

Custom rusEFI firmware for Mazduino ECU boards and compatible STM32F4-based engine management systems.

## Download

Pre-built firmware is published as nightly releases on the [Releases page](../../releases).

Each release includes `.bin`, `.srec`, and `.hex` files for every supported board.

### TunerStudio INI files

Every published firmware's TunerStudio INI is kept at **[mazduino.github.io/mazduino-fw](https://mazduino.github.io/mazduino-fw/)**, grouped by board with the newest first. Use it when a release bundle is gone, or when TunerStudio reports that the firmware signature does not match the project.

INI files are stored by firmware signature. A signature such as `rusEFI master.2026.09.08.mazduino-lite.969326114` (branch, build date, board, config hash) maps to:

```
https://mazduino.github.io/mazduino-fw/ini/master/2026/09/08/mazduino-lite/969326114.ini
```

The hash must match the firmware exactly: it identifies the config layout, so an INI with another hash reads and writes settings at the wrong offsets. The files are published by the nightly release workflow ([`nightly-release.yaml`](.github/workflows/nightly-release.yaml)) to the `gh-pages` branch.

## Supported Boards

**[Features per board](boards/FEATURES.md)** lists what each firmware has. It is generated from the board definitions, so it stays correct when they change.

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

### Mazduino Mini 6CH (STM32F407VGT6 or STM32F427VGT6)
- MCU: STM32F407VGT6 on earlier boards, STM32F427VGT6 on current ones (1MB flash). One firmware runs on both
- Secondary TunerStudio channel for a Bluetooth module (PB10/PB11)
- Electronic throttle body (ETB) support
- Traction control (requires ETB)
- Hardware knock detection
- CAN bus, USB virtual COM port

### Mazduino Core (STM32F427ZGT6)
- MCU: STM32F427ZGT6, LQFP144 (1MB flash) — **not** the 100-pin VGT6 used by the rest of the fleet; GPIOF/G are only bonded out on the 144-pin package, and this pinout needs them
- 6 injector outputs (3A), 6 ignition outputs, 4 extra low-side outputs (3A), 2 high-side outputs (1.3A), 5 auxiliary/relay outputs
- Dual electronic throttle (ETB), stepper idle (dual H-bridge), onboard LPS25 baro sensor
- 11 analog inputs (7 voltage + 4 temperature), 4 digital inputs
- CAN bus + CAN2 (jumper), SD card logging, USB virtual COM port and real TunerStudio port selector
- TunerStudio over Bluetooth on the TunerStudio serial port (PD5/PD6)
- In firmware the brain board uses the official rusEFI Proteus F4 pinout (12 low-side + 4 high-side outputs, 12 ignition outputs); the list above is what the 48-pin carrier connector brings out
- No knock input on the connector: Core is a brain board on a carrier board, and the 48-pin carrier does not bring knock out. The firmware still supports it, on PF4/PF5 (ADC3) of the brain board, off by default
- Traction control (requires ETB)

### Mazduino Mega100 (STM32F407VGT6)
- MCU: STM32F407VGT6 (1MB flash)
- Full feature set: ETB, traction control, knock, boost, launch control
- Dual pinout support: board04 layout and UA4C layout, switchable via TunerStudio board action
- USB virtual COM port and CAN bus for TunerStudio connection
- Status LED at PB7

### Mazduino Mega100-512 (STM32F407VET6)
- MCU: STM32F407VET6 (512KB flash)
- Firmware constrained to 384KB to preserve tune storage sector
- Feature reduction vs Mega100: see [Features per board](boards/FEATURES.md)
- CAN bus or USB virtual COM port for TunerStudio connection
- Status LED at PB7

### BIGFUEL variants
`mazduino-compact-bigfuel`, `mazduino-core-bigfuel`, `mazduino-lite-bigfuel` and `mazduino-mini6ch-bigfuel` are the same hardware as the board they are named after, with 32x32 VE and ignition tables. Tunes are not interchangeable between a board and its BIGFUEL variant.

## TunerStudio Connection

| Board | Connection |
|-------|------------|
| Compact, Lite, Mini 6CH, Core | USB virtual COM port |
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
  mazduino-core/
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
