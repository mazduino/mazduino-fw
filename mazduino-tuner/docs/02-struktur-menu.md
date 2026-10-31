# 02. Struktur menu Mazduino Tuner

Urutan dan nama menu utama mengikuti pohon *Settings* MaxxECU MTune 1.161. Grup MaxxECU yang khusus
produk MaxxECU (DCT, DSG, Dodge 8HP, PDM) tidak dipakai. Pohon lengkap per board, dengan ID dan tipe
halaman, ada di `generated/<board>/<board>.tuner-menu.md`.

## Ringkasan menu utama

| # | Menu Mazduino Tuner | Padanan MaxxECU | Isi utama (ID INI) |
|---|---|---|---|
| 1 | **Configuration** | Configuration | Engine settings `engineChars`, Base tunes `engineTypeDialog`, ECU logging `sdCard`, Connection `connection`, ECU lock `ecuPasswordPanel` |
| 2 | **Limits** | Limits | Rev limit/boost cut `limitsAndFallback`, Lean power cut `lambdaProtection`, Oil pressure cut (low/high), Warnings `celSensorChecksDialog` |
| 3 | **Fuel** | Fuel | Fuel inj general (injector, deadtime, small-pulse, timing), Staged injection, Fuel start/warmup/ASE (cranking, warmup, ASE), priming, IAT/baro trim, acc enrich, Lambda control (STFT), Fuel adaptation (LTFT), Overrun fuel cut, Cylinder adjustment, Fuel usage, Fuel pressure sensor |
| 4 | **Ignition** | Ignition | Ignition settings, dwell, cranking ignition, Ignition correction (CLT/IAT), Ignition lock/idle control, Cylinder angle trim, Trailing (rotary), Knock control / max retard / gain per cyl |
| 5 | **Idle control** | idle control | Idle control settings (settings, hardware, posisi vs CLT, cranking, taper, PID mult, coasting), Idle target RPM |
| 6 | **Motorsport** | Motorsport | Anti-lag, Launch control, Shiftcut (settings, time, retard, cut) |
| 7 | **VVT** | VVT | VVT cam position inputs & control `vvtPidDialog`, intake/exhaust target, VVL/VTEC |
| 8 | **Speed/Gear** | Speed/Gear | Speed sensor, Traction control (retard, cut, ETB drop) |
| 9 | **Nitrous** | Nitrous | Nitrous control |
| 10 | **E-Throttle** | E-Throttle | Throttle control `etbDialog`, Pedal position, Throttle targets `pedalToTpsTbl`, feed forward, ETB #2 trim |
| 11 | **Transmission control** | Transmission control | General, gear selector, input speed, shift points, solenoids, lockup, line pressure, range matrix (TCU alpha) |
| 12 | **CAN Bus** | CAN Bus | Settings, CAN inputs, CAN outputs 1-8, CAN lambda module (wideband), CAN modules (IO box) |
| 13 | **Advanced** | Advanced | User scripts (Lua settings, analog/digital input, PWM output, buttons), User tables (script table 1-4, curve 1-6) |
| 14 | **Inputs** | Inputs | Triggers/Home inputs, Sensors (CLT/IAT/TPS/MAP/Baro), Lambda sensor, Ethanol sensor, EGT, Analog inputs, Other sensors, Multi position switch, SENT, ECU supply, Input summary |
| 15 | **Outputs** | Outputs | Output config, Fans, A/C, GP PWM 1-4, Status LEDs, Output summary |
| 16 | **Diagnostics** | Diagnostics | Output test `ioTest`, Injector test `injTest`, Output diagnostics |
| 17 | **Tuning** | Tuning | Fuel table (VE), Lambda/AFR table, Ignition angle table, Extra fuel tables (Second VE, VE blend 1-4), Extra ignition tables (Second ign, ign blend 1-4) |
| 18 | **Boost control** | Boost control | Settings, open loop, gear adjustment, closed loop target & PID, corrections CLT/IAT, electronic wastegate |
| 19 | **Expert** | — | **Otomatis:** semua halaman INI yang tidak ditempatkan di atas, dikelompokkan menurut menu TunerStudio asal |
| 20 | **Help** | (F1 / quick-help) | Mazduino help |

Catatan penempatan yang sengaja berbeda dari TunerStudio:
- **Cranking** tidak menjadi menu sendiri. Bahan bakar cranking ada di *Fuel → Fuel start/warmup/ase*, sudut
  pengapian cranking di *Ignition*, dan posisi idle saat cranking di *Idle control*, sama seperti MaxxECU.
- **Tabel utama** (VE, lambda/AFR, ignition) dikumpulkan di *Tuning*. *Fuel* dan *Ignition* berisi
  konfigurasi dan koreksi.
- **Sensors** TunerStudio dipecah: sensor mesin ke *Inputs*, sensor tekanan bahan bakar ke *Fuel*, CAN O2 ke *CAN Bus*.
- **Controller** TunerStudio dipecah: test ke *Diagnostics*, koneksi/logging/lock ke *Configuration*, pinout ke
  *Inputs/Outputs → summary*, sisanya ke *Expert*.

## Isi menu Expert (snapshot nightly 2026-10-31)

| Grup Expert (menu TS asal) | Isi |
|---|---|
| Setup | Misfire detection |
| Fuel | VE 3D view, Target AFR adder tables, Charge temperature estimation, MAP estimate, predictive MAP, flex fuel AE/wall wetting multipliers, wall wetting curves, cylinder bank selection*, HPFP (GDI)* |
| Ignition | Multispark |
| Cranking | Cranking fuel E85 (flex) |
| Idle | Idle VE, Rotational idle |
| Advanced | Cylinder offsets, Boost blend tables, DC motor actuator* |
| Sensors | MAF sensor & transfer function, CAN O2 sensors (lama), ETB idle valve position, electronic wastegate position |
| CAN-bus | Triggered CAN outputs 1-8 |
| Controller | ECU stimulator, SPI buses/devices, rusEFI console, internal pinout, K-Line, Harley, idle flow estimate, airmass/timing equivalence, torque tables, GDI injector control* |
| View | Semua dialog live-data (state controller: fuel_computer, trigger_state, vvt, wideband, dll.) |

`*` hanya ada di board tertentu (Core, Mega100, Mini6ch).

Jumlah per board:

| Board | Item INI | Ditempatkan | Expert | ID layout dilewati |
|---|---:|---:|---:|---:|
| mazduino-lite / -bigfuel | 304 | 207 | 97 | 27 |
| mazduino-compact / -bigfuel | 322 | 225 | 97 | 9 |
| mazduino-core / -bigfuel | 331 | 234 | 97 | 0 |
| mazduino-mini6ch / -bigfuel | 333 | 234 | 99 | 0 |
| mazduino-mega100 | 339 | 234 | 105 | 0 |
| mazduino-mega100-512 | 293 | 201 | 92 | 33 |

Kandidat untuk dipindah dari Expert ke menu utama nanti (setelah diuji pengguna): *Misfire detection* → Limits,
*Idle VE* → Idle control, *Multispark* → Ignition, *MAF* → Inputs, *Triggered CAN outputs* → CAN Bus.
