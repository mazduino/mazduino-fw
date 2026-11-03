# 02. Mazduino Tuner menu structure

The top-level menus are grouped by engine subsystem, and the app adds a **Start** node above them. A group a board lacks is left out; the others keep this order. The full per-board tree, with page IDs and
types, is in `generated/<board>/<board>.tuner-menu.md`.

## Top-level menu summary

| # | Mazduino Tuner menu | Main contents (INI ID) |
|---|---|---|
| 1 | **Configuration** | Engine settings `engineChars`, Base tunes `engineTypeDialog`, ECU logging `sdCard`, Connection `connection`, ECU lock `ecuPasswordPanel` |
| 2 | **Limits** | Rev limit/boost cut `limitsAndFallback`, Lean power cut `lambdaProtection`, Oil pressure cut (low/high), Warnings `celSensorChecksDialog` |
| 3 | **Fuel** | Fuel general (injector, deadtime, small-pulse, timing), Staged injection, Start/warmup/ASE (cranking, warmup, ASE), priming, IAT trim, acceleration enrichment, baro trim, Lambda control (STFT), Fuel adaptation (LTFT), Overrun cut, Cylinder adjustments, Fuel usage, Fuel pressure sensor |
| 4 | **Ignition** | Ignition settings (with dwell and cranking ignition), Ignition correction (CLT/IAT), Ignition lock/idle control, Cylinder angle trim, Trailing (rotary), Knock sensing (gain per cyl) / control / max retard |
| 5 | **Idle control** | Idle control settings, hardware, position vs CLT, cranking, taper, PID mult, coasting, Idle target RPM |
| 6 | **Boost control** | Settings, open loop, gear adjustment, closed loop PID & target, corrections CLT/IAT, electronic wastegate |
| 7 | **Motorsport** | Anti-lag, Launch control, Shiftcut (settings, time, retard, cut) |
| 8 | **VVT** | VVT cam position inputs & control `vvtPidDialog`, intake/exhaust target, VVL/VTEC |
| 9 | **Speed/Gear** | Speed sensor, Traction control (retard, cut, ETB drop) |
| 10 | **Nitrous** | Nitrous control |
| 11 | **E-Throttle** | Throttle control `etbDialog`, Pedal position, Throttle targets `pedalToTpsTbl`, feed forward, ETB #2 trim |
| 12 | **Transmission control** | General, gear selector, input speed, shift points, solenoids, lockup, line pressure, range matrix (TCU alpha) |
| 13 | **CAN Bus** | Settings, CAN modules (IO box), CAN inputs, CAN outputs 1-8, CAN lambda module (wideband) |
| 14 | **Advanced** | User tables (script table 1-4, curve 1-6), User scripts (Lua settings, analog/digital input, PWM output, buttons) |
| 15 | **Inputs** | Input summary, Triggers/Home inputs, Sensors (IAT/CLT/TPS/MAP/Baro), Lambda sensors, Multi position switch, Analog inputs, Other sensors, Ethanol sensor, EGT, SENT, ECU supply |
| 16 | **Outputs** | Output config, Output summary, Fans, A/C, GP PWM 1-4, Status LEDs |
| 17 | **Diagnostics** | Error codes, Output test `ioTest`, Injector test `injTest`, Output diagnostics, Temporary cylinder shutoff, Trigger logger/sniffer/oscilloscope, Tune problems (the app adds its own pages) |
| 18 | **Tuning** | Fuel table (VE), Lambda/AFR table, Ignition angle table, Extra fuel tables (Second VE, VE blend 1-4), Extra ignition tables (Second ign, ign blend 1-4) |
| 19 | **Expert** | **Automatic:** every INI page not placed above, grouped by its original TunerStudio menu |
| 20 | **Help** | Mazduino help |

Placement notes that intentionally differ from TunerStudio:
- **Cranking** is not a menu of its own. Cranking fuel is in *Fuel → Fuel start/warmup/ase*, cranking
  ignition angle is in *Ignition*, and cranking idle position is in *Idle control*.
- **Main tables** (VE, lambda/AFR, ignition) are collected in *Tuning*. *Fuel* and *Ignition* contain
  configuration and corrections.
- TunerStudio **Sensors** is split: engine sensors go to *Inputs*, fuel pressure sensor to *Fuel*, CAN O2 to *CAN Bus*.
- TunerStudio **Controller** is split: tests go to *Diagnostics*, connection/logging/lock to *Configuration*, pinout to
  *Inputs → Input summary* and *Outputs → Output summary*, the rest to *Expert*.

## Expert menu contents (nightly snapshot 2026-10-31)

| Expert group (original TS menu) | Contents |
|---|---|
| Setup | Misfire detection |
| Fuel | VE 3D view, Target AFR adder tables, Charge temperature estimation, MAP estimate, predictive MAP, flex fuel AE/wall wetting multipliers, wall wetting curves, cylinder bank selection*, HPFP (GDI)* |
| Ignition | Multispark |
| Cranking | Cranking fuel E85 (flex) |
| Idle | Idle VE, Rotational idle |
| Advanced | Cylinder offsets, Boost blend tables, DC motor actuator* |
| Sensors | MAF sensor & transfer function, CAN O2 sensors (legacy), ETB idle valve position, electronic wastegate position |
| CAN-bus | Triggered CAN outputs 1-8 |
| Controller | ECU stimulator, SPI buses/devices, rusEFI console, internal pinout, K-Line, Harley, idle flow estimate, airmass/timing equivalence, torque tables, GDI injector control* |
| View | All live-data dialogs (controller state: fuel_computer, trigger_state, vvt, wideband, etc.) |

`*` only on certain boards (Core, Mega100, Mini6ch).

Menus and pages of a feature a board does not have do not appear on it: see *Board features* in `03-layout-format.md`. What each board has is in [`boards/FEATURES.md`](../../boards/FEATURES.md).

Counts per board:

| Board | INI items | Placed | Expert | Layout IDs skipped | Hidden by board flag |
|---|---:|---:|---:|---:|---:|
| mazduino-lite / -bigfuel | 304 | 193 | 89 | 27 | 22 |
| mazduino-compact / -bigfuel | 322 | 211 | 90 | 9 | 21 |
| mazduino-core / -bigfuel | 331 | 234 | 95 | 0 | 2 |
| mazduino-mini6ch / -bigfuel | 333 | 234 | 97 | 0 | 2 |
| mazduino-mega100 | 339 | 234 | 98 | 0 | 7 |
| mazduino-mega100-512 | 293 | 166 | 68 | 33 | 59 |

Candidates to move from Expert to a top-level menu later (after user testing): *Misfire detection* → Limits,
*Idle VE* → Idle control, *Multispark* → Ignition, *MAF* → Inputs, *Triggered CAN outputs* → CAN Bus.
