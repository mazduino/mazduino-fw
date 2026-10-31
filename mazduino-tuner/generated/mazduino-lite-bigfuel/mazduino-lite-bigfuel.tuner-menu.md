# Mazduino Tuner menu - mazduino-lite-bigfuel

> Generated oleh `mazduino-tuner/tools/gen_tuner_menu.sh` - jangan diedit manual.
> Signature: `rusEFI master.2026.10.31.mazduino-lite-bigfuel.637508062`

| Statistik | Jumlah |
|---|---:|
| Item menu di INI firmware | 304 |
| Ditempatkan di menu gaya MaxxECU | 207 |
| Otomatis masuk menu Expert | 97 |
| ID layout tidak ada di board ini (dilewati) | 27 |


## Configuration

- Engine settings - _dialog_ `engineChars`
- Base tunes - _dialog_ `engineTypeDialog`
- ---
- ECU logging settings - _dialog_ `sdCard`
- Connection settings - _dialog_ `connection`
- ECU lock - _dialog_ `ecuPasswordPanel`

## Limits

- Rev limit / boost cut - _dialog_ `limitsAndFallback`
- Lean power cut - _dialog_ `lambdaProtection`
- **Oil pressure cut**
  - Low oil pressure - _dialog_ `lowOilPressureProtection`
  - High oil pressure - _dialog_ `highOilPressureProtection`
- Warnings (check engine light) - _dialog_ `celSensorChecksDialog`

## Fuel

- **Fuel inj general**
  - Injector configuration - _dialog_ `injectorConfig`
  - Injector hardware - _dialog_ `injectionSettings`
  - Injector deadtime - _table_ `injectorsDeadTime`
  - Injector small-pulse correction - _other_ `injectorNonlinear`
  - Injection timing - _table_ `injPhaseTableTbl`
- **Staged injection**
  - Staged injection settings - _dialog_ `stagedInjection`
  - Staged injection outputs - _dialog_ `stagedInjectionOutputs`
  - Staged injection table - _table_ `stagedInjectionTbl`
- **Fuel start/warmup/ase**
  - Cranking settings - _dialog_ `crankingDialog`
  - Cranking base fuel - _table_ `crankingCycleFuelMultTbl`
  - Cranking fuel vs CLT - _curve_ `crankingCltCurve`
  - Cranking fuel vs TPS - _curve_ `crankingTpsCurve`
  - Warmup enrichment - _other_ `cltFuelCorrCurveDialog`
  - After-start enrichment (ASE) - _table_ `postCrankingEnrichmentTbl`
- Fuel priming - _dialog_ `primingFuelPulsePanel`
- Fuel IAT trim - _curve_ `iatFuelCorrCurve`
- Fuel baro trim - _table_ `baroCorrTbl`
- **Fuel acc enrich**
  - Acceleration enrichment - _dialog_ `AccelEnrich`
  - TPS acceleration extra fuel - _dialog_ `tpsTpsDialog`
  - TPS extra fuel RPM correction - _curve_ `tpsTspRpmCorrection`
- Lambda control - _dialog_ `fuelClosedLoopDialog`
- **Fuel adaptation**
  - Adaptation settings - _dialog_ `fuelLTFCDialog`
  - Adaptation table bank 1 - _table_ `ltftBank1Tbl`
  - Adaptation table bank 2 - _table_ `ltftBank2Tbl`
- Overrun fuel cut - _dialog_ `coastingFuelCutControl`
- **Cylinder adjustment**
  - Fuel trim cyl 1 - _table_ `fuelTrimTbl1`
  - Fuel trim cyl 2 - _table_ `fuelTrimTbl2`
  - Fuel trim cyl 3 - _table_ `fuelTrimTbl3`
  - Fuel trim cyl 4 - _table_ `fuelTrimTbl4`
  - Fuel trim cyl 5 - _table_ `fuelTrimTbl5`
  - Fuel trim cyl 6 - _table_ `fuelTrimTbl6`
  - Fuel trim cyl 7 - _table_ `fuelTrimTbl7`
  - Fuel trim cyl 8 - _table_ `fuelTrimTbl8`
  - Fuel trim cyl 9 - _table_ `fuelTrimTbl9`
  - Fuel trim cyl 10 - _table_ `fuelTrimTbl10`
  - Fuel trim cyl 11 - _table_ `fuelTrimTbl11`
  - Fuel trim cyl 12 - _table_ `fuelTrimTbl12`
- Fuel usage - _dialog_ `fuelConsumptionSettings`
- Fuel pressure sensor - _dialog_ `fuelPressureSensor`

## Ignition

- Ignition settings - _dialog_ `ignitionSettings`
- Dwell - _dialog_ `dwellSettings`
- Cranking ignition - _curve_ `crankingAdvanceCurve`
- **Ignition correction**
  - CLT ignition correction - _table_ `ignitionCltCorrTable`
  - IAT ignition correction - _table_ `ignitionIatCorrTableTbl`
- **Ignition lock/idle control**
  - Idle ignition control - _dialog_ `idleTimingPidCorrDialog`
  - Idle ignition angle - _curve_ `idleAdvanceCurve`
- **Cylinder angle trim**
  - Ignition trim cyl 1 - _table_ `ignTrimTbl1`
  - Ignition trim cyl 2 - _table_ `ignTrimTbl2`
  - Ignition trim cyl 3 - _table_ `ignTrimTbl3`
  - Ignition trim cyl 4 - _table_ `ignTrimTbl4`
- Trailing ignition (rotary) - _dialog_ `rotaryDialog`

## Idle control

- **Idle control settings**
  - Idle settings - _dialog_ `idleSettings`
  - Idle hardware - _dialog_ `idlehw`
  - Idle position vs CLT - _table_ `cltIdleTable`
  - Cranking idle position vs CLT - _other_ `cltCrankingCurveDialog`
  - After-start idle taper - _other_ `afterCrankingIACtaperDurationDialog`
  - Idle PID multiplier - _table_ `iacPidMultTbl`
  - Coasting idle position - _curve_ `iacCoastingCurve`
- Idle control target RPM - _curve_ `cltIdleRPMCurve`

## Motorsport

- Anti-lag - _dialog_ `antiLagDialog`
- Launch control - _dialog_ `smLaunchControl`
- **Shiftcut**
  - Shiftcut settings - _dialog_ `ShiftTorqueReductionDialog`
  - Shiftcut time - _dialog_ `torqueReductionTimeDialog`
  - Shiftcut ignition retard - _dialog_ `torqueReductionIgnitionRetardDialog`
  - Shiftcut ignition cut - _dialog_ `torqueReductionIgnitionCutDialog`

## VVT

- VVT cam position inputs & control - _dialog_ `vvtPidDialog`
- VVT intake cam target - _dialog_ `vvtIntakeTargetDialog`
- VVT exhaust cam target - _table_ `vvtTable2Tbl`
- VVL / VTEC control - _dialog_ `VvlControlDialog`

## Speed/Gear

- Speed sensor - _dialog_ `speedSensor`
- **Traction control**
  - Traction control ignition retard - _table_ `tractionTimingTableTbl`
  - Traction control ignition cut - _dialog_ `tractionIgnitionSkipDialog`

## Nitrous

- Nitrous control - _dialog_ `NitrousControlDialog`

## E-Throttle

- Pedal position - _dialog_ `pedalSensor`
- Throttle feed forward - _curve_ `etbTpsBiasCurve`
- Throttle #2 trim - _table_ `throttle2TrimTbl`

## Transmission control

- General settings - _dialog_ `tcuControls`
- Gear selector - _dialog_ `gearControls`
- Input speed sensor - _dialog_ `inputSpeedSensor`
- Shift points - _dialog_ `shiftSpeedDialog`
- Shift solenoids - _table_ `tcuSolenoidTableTbl`
- Lockup converter - _dialog_ `tccCurves`
- **Line pressure**
  - Line pressure per gear - _dialog_ `pcPerGearDialog`
  - Line pressure per shift - _dialog_ `pcPerShiftDialog`
  - 3-2 shift solenoid - _dialog_ `32Dialog`
- Range selector matrix - _dialog_ `rangeMatrixDialog`

## CAN Bus

- CAN bus settings - _dialog_ `canBusMain`
- **CAN inputs**
  - CAN analog inputs - _dialog_ `canAnalogInputsDialog`
  - CAN sensor inputs - _dialog_ `canSensorInputsDialog`
  - CAN switch inputs - _dialog_ `canVirtualInputs`
  - CAN vehicle speed - _dialog_ `speedSensorCan`
  - CAN EGT - _dialog_ `egtInputsCan`
- **CAN outputs**
  - CAN Output 1 - _dialog_ `canOutput1Dialog`
  - CAN Output 2 - _dialog_ `canOutput2Dialog`
  - CAN Output 3 - _dialog_ `canOutput3Dialog`
  - CAN Output 4 - _dialog_ `canOutput4Dialog`
  - CAN Output 5 - _dialog_ `canOutput5Dialog`
  - CAN Output 6 - _dialog_ `canOutput6Dialog`
  - CAN Output 7 - _dialog_ `canOutput7Dialog`
  - CAN Output 8 - _dialog_ `canOutput8Dialog`
- **CAN lambda module setup**
  - CAN lambda sensors - _dialog_ `uegoCan`
  - Wideband tools - _dialog_ `canReWidebandTools`
- CAN modules (IO box) - _dialog_ `msIoBox`

## Advanced

- **User scripts (Lua)**
  - Script settings - _dialog_ `scriptSetting`
  - Script analog inputs - _dialog_ `auxInputsDialog`
  - Script digital inputs - _dialog_ `luaDigitalInputsDialog`
  - Script PWM outputs - _dialog_ `luaOutputs`
  - Script buttons - _dialog_ `luaCommands`
- **User tables**
  - Script Table #1 - _dialog_ `scriptTable1TblSettings`
  - Script Table #2 - _dialog_ `scriptTable2TblSettings`
  - Script Table #3 - _dialog_ `scriptTable3TblSettings`
  - Script Table #4 - _dialog_ `scriptTable4TblSettings`
  - Script Curve #1 - _dialog_ `scriptCurve1Settings`
  - Script Curve #2 - _dialog_ `scriptCurve2Settings`
  - Script Curve #3 - _dialog_ `scriptCurve3Settings`
  - Script Curve #4 - _dialog_ `scriptCurve4Settings`
  - Script Curve #5 - _dialog_ `scriptCurve5Settings`
  - Script Curve #6 - _dialog_ `scriptCurve6Settings`

## Inputs

- **Triggers/Home inputs**
  - Trigger - _dialog_ `triggerConfiguration`
  - Advanced trigger options - _dialog_ `trigger_advanced`
  - Trigger gap override - _dialog_ `triggerConfiguration_gap`
- **Sensors (CLT, IAT, TPS, MAP)**
  - CLT sensor - _dialog_ `cltSensor`
  - IAT sensor - _dialog_ `iatSensorDialog`
  - TPS sensor - _dialog_ `tpsSensor`
  - MAP sensor - _dialog_ `mapSettings`
  - MAP sampling - _dialog_ `mapCurves`
  - Baro sensor - _dialog_ `baroSettings`
- Lambda sensor - _dialog_ `analogEgoSettings`
- Ethanol sensor - _dialog_ `flexSensorDialog`
- EGT sensors - _dialog_ `egtInputs`
- **Analog inputs**
  - Analog input settings - _dialog_ `analogInputSettings`
  - Aux linear sensors - _other_ `auxLinearSensors`
  - Aux temperature 1 - _dialog_ `auxTempSensor1Sensor`
  - Aux temperature 2 - _dialog_ `auxTempSensor2Sensor`
- **Other sensors**
  - Oil pressure - _dialog_ `oilPressureSensor`
  - Oil temperature - _dialog_ `oilTempSensor`
  - Fuel temperature - _dialog_ `fuelTempSensor`
  - Fuel level - _dialog_ `fuelLevelDialog`
  - Ambient temperature - _dialog_ `ambientTempSensor`
  - A/C pressure - _dialog_ `acPressureSensor`
  - Compressor discharge temperature - _dialog_ `compressorDischargeTemperature`
  - Misc sensors - _dialog_ `otherSensorInputs`
- **Multi position switch**
  - Analog multi-switch 1 - _dialog_ `analogMultiSwitchSettings1`
  - Analog multi-switch 2 - _dialog_ `analogMultiSwitchSettings2`
  - Analog multi-switch 3 - _dialog_ `analogMultiSwitchSettings3`
  - Analog multi-switch 4 - _dialog_ `analogMultiSwitchSettings4`
- SENT protocol input - _dialog_ `sentInputs`
- **ECU supply**
  - Battery and alternator - _dialog_ `energySystems`
  - Ignition key input - _dialog_ `ignitionInputDialog`
- Input summary - _dialog_ `allPinsInputs`

## Outputs

- Output config - _dialog_ `outputsDialog`
- **Fans**
  - Fan settings - _dialog_ `fanSettings`
  - Fan 1 PWM - _dialog_ `fan1PwmCurveDialog`
  - Fan 2 PWM - _dialog_ `fan2PwmCurveDialog`
- A/C control - _dialog_ `acSettings`
- **GP PWM**
  - General Purpose PWM 1 - _dialog_ `gppwm1`
  - General Purpose PWM 2 - _dialog_ `gppwm2`
  - General Purpose PWM 3 - _dialog_ `gppwm3`
  - General Purpose PWM 4 - _dialog_ `gppwm4`
- Status LEDs - _dialog_ `statusLeds`
- Output summary - _dialog_ `allPinsOutputs`

## Diagnostics

- Output test - _dialog_ `ioTest`
- Injector test - _dialog_ `injTest`
- Output diagnostics - _dialog_ `OutputDiagDialog`

## Tuning

- Fuel table - _dialog_ `veTableDialog`
- Lambda table - _dialog_ `lambdaTableDialog`
- AFR table - _dialog_ `afrTableDialog`
- Ignition angle table - _dialog_ `IgnitionTableDialog`
- **Extra fuel tables**
  - Second fuel table - _dialog_ `secondVeTableDialog`
  - VE blend 1 settings - _dialog_ `veBlend1Cfg`
  - VE blend table 1 - _table_ `veBlend1Table`
  - VE blend 2 settings - _dialog_ `veBlend2Cfg`
  - VE blend table 2 - _table_ `veBlend2Table`
  - VE blend 3 settings - _dialog_ `veBlend3Cfg`
  - VE blend table 3 - _table_ `veBlend3Table`
  - VE blend 4 settings - _dialog_ `veBlend4Cfg`
  - VE blend table 4 - _table_ `veBlend4Table`
- **Extra ignition tables**
  - Second ignition table - _dialog_ `secondIgnitionTableDialog`
  - Ignition blend 1 bias - _dialog_ `ignAdder1Cfg`
  - Ignition blend table 1 - _table_ `ignAdder1Table`
  - Ignition blend 2 bias - _dialog_ `ignAdder2Cfg`
  - Ignition blend table 2 - _table_ `ignAdder2Table`
  - Ignition blend 3 bias - _dialog_ `ignAdder3Cfg`
  - Ignition blend table 3 - _table_ `ignAdder3Table`
  - Ignition blend 4 bias - _dialog_ `ignAdder4Cfg`
  - Ignition blend table 4 - _table_ `ignAdder4Table`

## Boost control

- Boost control settings - _dialog_ `boostDialog`
- Boost control (open loop) - _dialog_ `boostOpenLoopDialog`
- Open loop gear adjustment - _dialog_ `boostOpenLoopGearAdderDialog`
- Closed loop boost, targets - _dialog_ `boostTargetDialog`
- Closed loop boost, PID - _dialog_ `boostPidDialog`
- **Boost corrections**
  - CLT duty multiplier - _curve_ `cltBoostCorrCurve`
  - IAT duty multiplier - _curve_ `iatBoostCorrCurve`
  - CLT target adder - _curve_ `cltBoostAdderCurve`
  - IAT target adder - _curve_ `iatBoostAdderCurve`
- Electronic wastegate feed forward - _curve_ `ewgBiasCurve`

## Expert

- **Setup**
  - Limits and protection - Misfire Detection - _dialog_ `misfireDetectionDialog`
- **Fuel**
  - VE 3D view - _table3d_ `veTableMap`
  - Target AFR adder tables - Target AFR 1 settings - _dialog_ `targetAfrBlend1Cfg`
  - Target AFR adder tables - Target AFR 1 table - _table_ `targetAfrBlend1Table`
  - Target AFR adder tables - Target AFR 2 settings - _dialog_ `targetAfrBlend2Cfg`
  - Target AFR adder tables - Target AFR 2 table - _table_ `targetAfrBlend2Table`
  - Fuel Corrections - Charge temperature estimation - _dialog_ `tChargeSettings`
  - TPS Acceleration Enrichment / Wall Wetting AE - MAP estimate table - _table_ `mapEstimateTableTbl`
  - TPS Acceleration Enrichment / Wall Wetting AE - Predictive Map Blend Duration - _curve_ `predictiveMapBlendDuration`
  - TPS Acceleration Enrichment / Wall Wetting AE - Flex fuel: accel enrichment multiplier - _dialog_ `flexAeMultDialog`
  - TPS Acceleration Enrichment / Wall Wetting AE - Flex fuel: wall wetting tau multiplier - _dialog_ `flexWwTauMultDialog`
  - TPS Acceleration Enrichment / Wall Wetting AE - Flex fuel: wall wetting beta multiplier - _dialog_ `flexWwBetaMultDialog`
  - Wall wetting AE - Evap time - _dialog_ `wwTauCurves`
  - Wall wetting AE - Impact fraction - _dialog_ `wwBetaCurves`
- **Ignition**
  - Multispark - _dialog_ `multisparkSettings`
- **Cranking**
  - Fuel Engine Temp (Flex Fuel E85) - _curve_ `crankingCltCurveE100`
- **Idle**
  - Idle VE - _table_ `idleVeTableTbl`
  - Rotational Idle - _dialog_ `rotIdleMainDialog`
- **Advanced**
  - Cylinder offsets - _dialog_ `ignitionCylExtra`
  - Boost blend tables - Open loop 1 bias - _dialog_ `boostOpenBlend1Cfg`
  - Boost blend tables - Open loop 1 adder - _table_ `boostOpenBlend1Table`
  - Boost blend tables - Open loop 2 bias - _dialog_ `boostOpenBlend2Cfg`
  - Boost blend tables - Open loop 2 adder - _table_ `boostOpenBlend2Table`
  - Boost blend tables - Closed loop 1 bias - _dialog_ `boostClosedBlend1Cfg`
  - Boost blend tables - Closed loop 1 adder - _table_ `boostClosedBlend1Table`
  - Boost blend tables - Closed loop 2 bias - _dialog_ `boostClosedBlend2Cfg`
  - Boost blend tables - Closed loop 2 adder - _table_ `boostClosedBlend2Table`
- **Sensors**
  - MAF sensor - _dialog_ `mafSettings`
  - MAF transfer function - _curve_ `mafDecodingCurve`
  - CAN O2 sensors - _dialog_ `egoSettings`
  - ETB-style Idle valve position sensor - _dialog_ `idleValvePosDialog`
  - Turbo sensors - Electronic Wastegate position sensor - _dialog_ `wastegatePosDialog`
- **CAN-bus**
  - Triggered CAN Outputs - Triggered CAN Output 1 - _dialog_ `triggeredCanOutput1Dialog`
  - Triggered CAN Outputs - Triggered CAN Output 2 - _dialog_ `triggeredCanOutput2Dialog`
  - Triggered CAN Outputs - Triggered CAN Output 3 - _dialog_ `triggeredCanOutput3Dialog`
  - Triggered CAN Outputs - Triggered CAN Output 4 - _dialog_ `triggeredCanOutput4Dialog`
  - Triggered CAN Outputs - Triggered CAN Output 5 - _dialog_ `triggeredCanOutput5Dialog`
  - Triggered CAN Outputs - Triggered CAN Output 6 - _dialog_ `triggeredCanOutput6Dialog`
  - Triggered CAN Outputs - Triggered CAN Output 7 - _dialog_ `triggeredCanOutput7Dialog`
  - Triggered CAN Outputs - Triggered CAN Output 8 - _dialog_ `triggeredCanOutput8Dialog`
- **Controller**
  - ECU stimulator - _dialog_ `ecuStimulator`
  - SPI Buses - _dialog_ `spiBuses`
  - SPI Devices - _dialog_ `spiDevices`
  - rusEFI console - _dialog_ `monitoringSettings`
  - Full pinout - Internal - _dialog_ `allPinsInternal`
  - K-Line - _dialog_ `kLineDialog`
  - Harley - _dialog_ `harleyAcr`
  - Idle flow estimate - _curve_ `idleFlowEstimate`
  - Idle airmass/timing equivalence - _curve_ `idleAirmassTimingEquivalence`
  - Torque - Throttle effective area - _curve_ `throttleEffectiveArea`
  - Torque - Torque - _table_ `torqueTableTbl`
  - Torque - Torque Table Generator - _other_ `torqueTableGenerator`
  - Torque - TMF - _table_ `torque2TableTbl`
- **View**
  - fuel_computer - _dialog_ `fuel_computerDialog`
  - ignition_state - _dialog_ `ignition_stateDialog`
  - knock_controller - _dialog_ `knock_controllerDialog`
  - prime_injection - _dialog_ `prime_injectionDialog`
  - tcu_controller - _dialog_ `tcu_controllerDialog`
  - throttle_model - _dialog_ `throttle_modelDialog`
  - high_pressure_fuel_pump - _dialog_ `high_pressure_fuel_pumpDialog`
  - injector_model - _dialog_ `injector_modelDialog`
  - launch_control_state - _dialog_ `launch_control_stateDialog`
  - shift_torque_reduction_state - _dialog_ `shift_torque_reduction_stateDialog`
  - antilag_system_state - _dialog_ `antilag_system_stateDialog`
  - boost_control - _dialog_ `boost_controlDialog`
  - ac_control - _dialog_ `ac_controlDialog`
  - nitrous_control_state - _dialog_ `nitrous_control_stateDialog`
  - fan_control0 - _dialog_ `fan_control0Dialog`
  - fan_control1 - _dialog_ `fan_control1Dialog`
  - fuel_pump_control - _dialog_ `fuel_pump_controlDialog`
  - main_relay - _dialog_ `main_relayDialog`
  - tps_accel_state - _dialog_ `tps_accel_stateDialog`
  - trigger_central - _dialog_ `trigger_centralDialog`
  - trigger_state0 - _dialog_ `trigger_state0Dialog`
  - trigger_state1 - _dialog_ `trigger_state1Dialog`
  - trigger_state2 - _dialog_ `trigger_state2Dialog`
  - trigger_state3 - _dialog_ `trigger_state3Dialog`
  - trigger_state4 - _dialog_ `trigger_state4Dialog`
  - trigger_state_primary - _dialog_ `trigger_state_primaryDialog`
  - wall_fuel_state - _dialog_ `wall_fuel_stateDialog`
  - closed_loop_idle - _dialog_ `closed_loop_idleDialog`
  - misfire_detection_state - _dialog_ `misfire_detection_stateDialog`
  - live_data_example - _dialog_ `live_data_exampleDialog`
  - idle_state - _dialog_ `idle_stateDialog`
  - electronic_throttle0 - _dialog_ `electronic_throttle0Dialog`
  - electronic_throttle1 - _dialog_ `electronic_throttle1Dialog`
  - wideband_state0 - _dialog_ `wideband_state0Dialog`
  - wideband_state1 - _dialog_ `wideband_state1Dialog`
  - dc_motors - _dialog_ `dc_motorsDialog`
  - sent_state - _dialog_ `sent_stateDialog`
  - vvt - _dialog_ `vvtDialog`
  - lambda_monitor - _dialog_ `lambda_monitorDialog`
  - mc33810_state - _dialog_ `mc33810_stateDialog`
  - long_term_fuel_trim_state - _dialog_ `long_term_fuel_trim_stateDialog`
  - short_term_fuel_trim_state - _dialog_ `short_term_fuel_trim_stateDialog`
  - vvl_controller_state - _dialog_ `vvl_controller_stateDialog`
  - live_data_rotational_idle - _dialog_ `live_data_rotational_idleDialog`

## Help

- Mazduino help - _other_ `helpGeneral`

## ID layout yang tidak ada di board ini

`cylinderBankSelect`, `ignTrimTbl5`, `ignTrimTbl6`, `ignTrimTbl7`, `ignTrimTbl8`, `ignTrimTbl9`, `ignTrimTbl10`, `ignTrimTbl11`, `ignTrimTbl12`, `softwareKnock`, `maxKnockRetardTbl`, `knockGainTbl1`, `knockGainTbl2`, `knockGainTbl3`, `knockGainTbl4`, `knockGainTbl5`, `knockGainTbl6`, `knockGainTbl7`, `knockGainTbl8`, `knockGainTbl9`, `knockGainTbl10`, `knockGainTbl11`, `knockGainTbl12`, `tractionControlEtb`, `etbDialog`, `pedalToTpsTbl`, `ewgDialog`
