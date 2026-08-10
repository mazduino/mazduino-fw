// this section was generated automatically by rusEFI tool config_definition_base-all.jar based on (unknown script) console/binary/output_channels.txt
// by class com.rusefi.output.CHeaderConsumer
// begin
#pragma once
#include "rusefi_types.h"
// start of pid_status_s
struct pid_status_s {
	/**
	 * offset 0
	 */
	float pTerm = (float)0;
	/**
	 * offset 4
	 */
	scaled_channel<int16_t, 100, 1> iTerm = (int16_t)0;
	/**
	 * offset 6
	 */
	scaled_channel<int16_t, 100, 1> dTerm = (int16_t)0;
	/**
	 * offset 8
	 */
	scaled_channel<int16_t, 100, 1> output = (int16_t)0;
	/**
	 * offset 10
	 */
	scaled_channel<int16_t, 100, 1> error = (int16_t)0;
	/**
	 * offset 12
	 */
	uint32_t resetCounter = (uint32_t)0;
};
static_assert(sizeof(pid_status_s) == 16);

// start of output_channels_s
struct output_channels_s {
	/**
	 * SD: Present
	offset 0 bit 0 */
	bool sd_present : 1 {};
	/**
	 * SD: Logging
	offset 0 bit 1 */
	bool sd_logging_internal : 1 {};
	/**
	offset 0 bit 2 */
	bool triggerScopeReady : 1 {};
	/**
	offset 0 bit 3 */
	bool antilagTriggered : 1 {};
	/**
	offset 0 bit 4 */
	bool isO2HeaterOn : 1 {};
	/**
	offset 0 bit 5 */
	bool checkEngine : 1 {};
	/**
	offset 0 bit 6 */
	bool needBurn : 1 {};
	/**
	 * SD: MSD
	offset 0 bit 7 */
	bool sd_msd : 1 {};
	/**
	 * Tooth Logger Ready
	offset 0 bit 8 */
	bool toothLogReady : 1 {};
	/**
	 * Error: TPS
	offset 0 bit 9 */
	bool isTpsError : 1 {};
	/**
	 * Error: CLT
	offset 0 bit 10 */
	bool isCltError : 1 {};
	/**
	 * Error: MAP
	offset 0 bit 11 */
	bool isMapError : 1 {};
	/**
	 * Error: IAT
	offset 0 bit 12 */
	bool isIatError : 1 {};
	/**
	 * Error: Trigger
	offset 0 bit 13 */
	bool isTriggerError : 1 {};
	/**
	 * Error: Active
	offset 0 bit 14 */
	bool hasCriticalError : 1 {};
	/**
	 * Warning: Active
	offset 0 bit 15 */
	bool isWarnNow : 1 {};
	/**
	 * Error: Pedal
	offset 0 bit 16 */
	bool isPedalError : 1 {};
	/**
	 * Launch Control Triggered
	offset 0 bit 17 */
	bool launchTriggered : 1 {};
	/**
	 * Error: TPS2
	offset 0 bit 18 */
	bool isTps2Error : 1 {};
	/**
	 * Injector Fault
	offset 0 bit 19 */
	bool injectorFault : 1 {};
	/**
	 * Ignition Fault
	offset 0 bit 20 */
	bool ignitionFault : 1 {};
	/**
	 * isUsbConnected
	 * Original reason for this is to check if USB is connected from Lua
	offset 0 bit 21 */
	bool isUsbConnected : 1 {};
	/**
	offset 0 bit 22 */
	bool dfcoActive : 1 {};
	/**
	 * SD card writing
	offset 0 bit 23 */
	bool sd_active_wr : 1 {};
	/**
	 * SD card reading
	offset 0 bit 24 */
	bool sd_active_rd : 1 {};
	/**
	 * MAP from sensor seems valid
	offset 0 bit 25 */
	bool isMapValid : 1 {};
	/**
	offset 0 bit 26 */
	bool triggerPageRefreshFlag : 1 {};
	/**
	offset 0 bit 27 */
	bool hasFaultReportFile : 1 {};
	/**
	 * Analog sensors supply failure
	offset 0 bit 28 */
	bool isAnalogFailure : 1 {};
	/**
	offset 0 bit 29 */
	bool isTuningNow : 1 {};
	/**
	 * SD: formating is in progress
	offset 0 bit 30 */
	bool sd_formating : 1 {};
	/**
	offset 0 bit 31 */
	bool isMapAveraging : 1 {};
	/**
	 * CEL: active sensor faults
	 * offset 4
	 */
	uint8_t cel_error_codes_count = (uint8_t)0;
	/**
	 * need 4 byte alignment
	 * units: units
	 * offset 5
	 */
	uint8_t alignmentFill_at_5[3] = {};
	/**
	 * CEL: battery voltage out of range
	offset 8 bit 0 */
	bool cel_batv : 1 {};
	/**
	 * CEL: MAP sensor out of range
	offset 8 bit 1 */
	bool cel_map : 1 {};
	/**
	 * CEL: IAT sensor out of range
	offset 8 bit 2 */
	bool cel_iat : 1 {};
	/**
	 * CEL: CLT sensor out of range
	offset 8 bit 3 */
	bool cel_clt : 1 {};
	/**
	 * CEL: TPS sensor out of range
	offset 8 bit 4 */
	bool cel_tps : 1 {};
	/**
	 * CEL: AFR/EGO sensor out of range
	offset 8 bit 5 */
	bool cel_afr : 1 {};
	/**
	 * CEL: oil temperature out of range
	offset 8 bit 6 */
	bool cel_oil_temp : 1 {};
	/**
	 * CEL: oil pressure out of range
	offset 8 bit 7 */
	bool cel_oil_pressure : 1 {};
	/**
	 * CEL: fuel pressure out of range
	offset 8 bit 8 */
	bool cel_fuel_pressure : 1 {};
	/**
	 * CEL: MAF sensor out of range
	offset 8 bit 9 */
	bool cel_maf : 1 {};
	/**
	 * CEL: sync losses over limit
	offset 8 bit 10 */
	bool cel_sync_loss : 1 {};
	/**
	 * CEL: fuel/spark cut active
	offset 8 bit 11 */
	bool cel_any_cut : 1 {};
	/**
	 * CEL: shift light active
	offset 8 bit 12 */
	bool cel_shiftlight_active : 1 {};
	/**
	offset 8 bit 13 */
	bool unusedBit_47_13 : 1 {};
	/**
	offset 8 bit 14 */
	bool unusedBit_47_14 : 1 {};
	/**
	offset 8 bit 15 */
	bool unusedBit_47_15 : 1 {};
	/**
	offset 8 bit 16 */
	bool unusedBit_47_16 : 1 {};
	/**
	offset 8 bit 17 */
	bool unusedBit_47_17 : 1 {};
	/**
	offset 8 bit 18 */
	bool unusedBit_47_18 : 1 {};
	/**
	offset 8 bit 19 */
	bool unusedBit_47_19 : 1 {};
	/**
	offset 8 bit 20 */
	bool unusedBit_47_20 : 1 {};
	/**
	offset 8 bit 21 */
	bool unusedBit_47_21 : 1 {};
	/**
	offset 8 bit 22 */
	bool unusedBit_47_22 : 1 {};
	/**
	offset 8 bit 23 */
	bool unusedBit_47_23 : 1 {};
	/**
	offset 8 bit 24 */
	bool unusedBit_47_24 : 1 {};
	/**
	offset 8 bit 25 */
	bool unusedBit_47_25 : 1 {};
	/**
	offset 8 bit 26 */
	bool unusedBit_47_26 : 1 {};
	/**
	offset 8 bit 27 */
	bool unusedBit_47_27 : 1 {};
	/**
	offset 8 bit 28 */
	bool unusedBit_47_28 : 1 {};
	/**
	offset 8 bit 29 */
	bool unusedBit_47_29 : 1 {};
	/**
	offset 8 bit 30 */
	bool unusedBit_47_30 : 1 {};
	/**
	offset 8 bit 31 */
	bool unusedBit_47_31 : 1 {};
	/**
	 * @@GAUGE_NAME_RPM@@
	 * units: RPM
	 * offset 12
	 */
	uint16_t RPMValue = (uint16_t)0;
	/**
	 * dRPM
	 * units: RPM acceleration/Rate of Change/ROC
	 * offset 14
	 */
	int16_t rpmAcceleration = (int16_t)0;
	/**
	 * @@GAUGE_NAME_GEAR_RATIO@@
	 * units: value
	 * offset 16
	 */
	scaled_channel<uint16_t, 100, 1> speedToRpmRatio = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_CPU_TEMP@@
	 * units: deg C
	 * offset 18
	 */
	int8_t internalMcuTemperature = (int8_t)0;
	/**
	 * need 4 byte alignment
	 * units: units
	 * offset 19
	 */
	uint8_t alignmentFill_at_19[1] = {};
	/**
	 * units: V
	 * offset 20
	 */
	scaled_channel<int16_t, 1000, 1> internalVref = (int16_t)0;
	/**
	 * units: V
	 * offset 22
	 */
	scaled_channel<int16_t, 1000, 1> internalVbat = (int16_t)0;
	/**
	 * @@GAUGE_NAME_CLT@@
	 * units: deg C
	 * offset 24
	 */
	scaled_channel<int16_t, 100, 1> coolant = (int16_t)0;
	/**
	 * @@GAUGE_NAME_IAT@@
	 * units: deg C
	 * offset 26
	 */
	scaled_channel<int16_t, 100, 1> intake = (int16_t)0;
	/**
	 * units: deg C
	 * offset 28
	 */
	scaled_channel<int16_t, 100, 1> auxTemp1 = (int16_t)0;
	/**
	 * units: deg C
	 * offset 30
	 */
	scaled_channel<int16_t, 100, 1> auxTemp2 = (int16_t)0;
	/**
	 * @@GAUGE_NAME_TPS@@
	 * units: %
	 * offset 32
	 */
	scaled_channel<int16_t, 100, 1> TPSValue = (int16_t)0;
	/**
	 * @@GAUGE_NAME_THROTTLE_PEDAL@@
	 * units: %
	 * offset 34
	 */
	scaled_channel<int16_t, 100, 1> throttlePedalPosition = (int16_t)0;
	/**
	 * units: ADC
	 * offset 36
	 */
	uint16_t tpsADC = (uint16_t)0;
	/**
	 * units: V
	 * offset 38
	 */
	scaled_channel<uint16_t, 1000, 1> rawMaf = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_AIR_FLOW_MEASURED@@
	 * units: kg/h
	 * offset 40
	 */
	scaled_channel<uint16_t, 10, 1> mafMeasured = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_MAP@@
	 * units: kPa
	 * offset 42
	 */
	scaled_channel<uint16_t, 30, 1> MAPValue = (uint16_t)0;
	/**
	 * units: kPa
	 * offset 44
	 */
	scaled_channel<uint16_t, 30, 1> baroPressure = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_LAMBDA@@
	 * offset 46
	 */
	scaled_channel<uint16_t, 10000, 1> lambdaValue = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_VBAT@@
	 * units: V
	 * offset 48
	 */
	scaled_channel<uint16_t, 1000, 1> VBatt = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_VIGN@@
	 * units: V
	 * offset 50
	 */
	scaled_channel<uint16_t, 1000, 1> VIgn = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_OIL_PRESSURE@@
	 * units: kPa
	 * offset 52
	 */
	scaled_channel<uint16_t, 30, 1> oilPressure = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_VVT_B1I@@
	 * units: deg
	 * offset 54
	 */
	scaled_channel<int16_t, 50, 1> vvtPositionB1I = (int16_t)0;
	/**
	 * @@GAUGE_NAME_FUEL_LAST_INJECTION@@
	 * Actual last injection time - including all compensation and injection mode
	 * units: ms
	 * offset 56
	 */
	scaled_channel<uint16_t, 300, 1> actualLastInjection = (uint16_t)0;
	/**
	 * need 4 byte alignment
	 * units: units
	 * offset 58
	 */
	uint8_t alignmentFill_at_58[2] = {};
	/**
	 * @@GAUGE_NAME_FUEL_LAST_INJECTION_RATIO@@
	 * Last injection time divided to previous injection time
	 * offset 60
	 */
	float actualLastInjectionRatio = (float)0;
	/**
	 * offset 64
	 */
	uint8_t stopEngineCode = (uint8_t)0;
	/**
	 * @@GAUGE_NAME_FUEL_INJ_DUTY@@
	 * units: %
	 * offset 65
	 */
	scaled_channel<uint8_t, 2, 1> injectorDutyCycle = (uint8_t)0;
	/**
	 * offset 66
	 */
	uint8_t tempLogging1 = (uint8_t)0;
	/**
	 * need 4 byte alignment
	 * units: units
	 * offset 67
	 */
	uint8_t alignmentFill_at_67[1] = {};
	/**
	 * @@GAUGE_NAME_FUEL_INJECTION_TIMING@@
	 * units: deg
	 * offset 68
	 */
	int16_t injectionOffset = (int16_t)0;
	/**
	 * @@GAUGE_NAME_ENGINE_CRC16@@
	 * units: crc16
	 * offset 70
	 */
	uint16_t engineMakeCodeNameCrc16 = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_FUEL_WALL_AMOUNT@@
	 * units: mg
	 * offset 72
	 */
	scaled_channel<uint16_t, 100, 1> wallFuelAmount = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_FUEL_WALL_CORRECTION@@
	 * units: mg
	 * offset 74
	 */
	scaled_channel<int16_t, 100, 1> wallFuelCorrectionValue = (int16_t)0;
	/**
	 * Flex: AE multiplier
	 * units: mult
	 * offset 76
	 */
	scaled_channel<uint16_t, 1000, 1> flexAeMultiplier = (uint16_t)0;
	/**
	 * Flex: WW tau multiplier
	 * units: mult
	 * offset 78
	 */
	scaled_channel<uint16_t, 1000, 1> flexWwTauMultiplier = (uint16_t)0;
	/**
	 * Flex: WW beta multiplier
	 * units: mult
	 * offset 80
	 */
	scaled_channel<uint16_t, 1000, 1> flexWwBetaMultiplier = (uint16_t)0;
	/**
	 * offset 82
	 */
	uint16_t revolutionCounterSinceStart = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_CAN_READ_OK@@
	 * offset 84
	 */
	uint16_t canReadCounter = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_FUEL_TPS_EXTRA@@
	 * units: ms
	 * offset 86
	 */
	scaled_channel<int16_t, 300, 1> tpsAccelFuel = (int16_t)0;
	/**
	 * @@GAUGE_NAME_IGNITION_MODE@@
	 * offset 88
	 */
	uint8_t currentIgnitionMode = (uint8_t)0;
	/**
	 * @@GAUGE_NAME_INJECTION_MODE@@
	 * offset 89
	 */
	uint8_t currentInjectionMode = (uint8_t)0;
	/**
	 * @@GAUGE_NAME_DWELL_DUTY@@
	 * units: %
	 * offset 90
	 */
	scaled_channel<uint16_t, 100, 1> coilDutyCycle = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_ETB_DUTY@@
	 * units: %
	 * offset 92
	 */
	scaled_channel<int16_t, 100, 1> etb1DutyCycle = (int16_t)0;
	/**
	 * Fuel level
	 * units: %
	 * offset 94
	 */
	scaled_channel<int16_t, 100, 1> fuelTankLevel = (int16_t)0;
	/**
	 * @@GAUGE_NAME_FUEL_CONSUMPTION@@
	 * units: grams
	 * offset 96
	 */
	uint16_t totalFuelConsumption = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_FUEL_FLOW@@
	 * units: gram/s
	 * offset 98
	 */
	scaled_channel<uint16_t, 200, 1> fuelFlowRate = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_TPS2@@
	 * units: %
	 * offset 100
	 */
	scaled_channel<int16_t, 100, 1> TPS2Value = (int16_t)0;
	/**
	 * @@GAUGE_NAME_TUNE_CRC16@@
	 * units: crc16
	 * offset 102
	 */
	uint16_t tuneCrc16 = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_FUEL_VE@@
	 * units: ratio
	 * offset 104
	 */
	scaled_channel<uint16_t, 10, 1> veValue = (uint16_t)0;
	/**
	 * need 4 byte alignment
	 * units: units
	 * offset 106
	 */
	uint8_t alignmentFill_at_106[2] = {};
	/**
	 * @@GAUGE_NAME_UPTIME@@
	 * units: sec
	 * offset 108
	 */
	uint32_t seconds = (uint32_t)0;
	/**
	 * Engine Mode
	 * units: em
	 * offset 112
	 */
	uint32_t engineMode = (uint32_t)0;
	/**
	 * @@GAUGE_NAME_VERSION@@
	 * units: version_f
	 * offset 116
	 */
	uint32_t firmwareVersion = (uint32_t)0;
	/**
	 * units: V
	 * offset 120
	 */
	scaled_channel<int16_t, 1000, 1> rawIdlePositionSensor = (int16_t)0;
	/**
	 * units: V
	 * offset 122
	 */
	scaled_channel<int16_t, 1000, 1> rawWastegatePosition = (int16_t)0;
	/**
	 * @@GAUGE_NAME_ACCEL_LAT@@
	 * units: G
	 * offset 124
	 */
	scaled_channel<int16_t, 1000, 1> accelerationLat = (int16_t)0;
	/**
	 * @@GAUGE_NAME_ACCEL_LON@@
	 * units: G
	 * offset 126
	 */
	scaled_channel<int16_t, 1000, 1> accelerationLon = (int16_t)0;
	/**
	 * @@GAUGE_NAME_DETECTED_GEAR@@
	 * offset 128
	 */
	uint8_t detectedGear = (uint8_t)0;
	/**
	 * offset 129
	 */
	uint8_t maxTriggerReentrant = (uint8_t)0;
	/**
	 * units: V
	 * offset 130
	 */
	scaled_channel<int16_t, 1000, 1> rawLowFuelPressure = (int16_t)0;
	/**
	 * units: V
	 * offset 132
	 */
	scaled_channel<int16_t, 1000, 1> rawHighFuelPressure = (int16_t)0;
	/**
	 * @@GAUGE_NAME_FUEL_PRESSURE_LOW@@
	 * units: kpa
	 * offset 134
	 */
	scaled_channel<int16_t, 30, 1> lowFuelPressure = (int16_t)0;
	/**
	 * @@GAUGE_NAME_DESIRED_GEAR@@
	 * units: gear
	 * offset 136
	 */
	int8_t tcuDesiredGear = (int8_t)0;
	/**
	 * @@GAUGE_NAME_FLEX@@
	 * units: %
	 * offset 137
	 */
	scaled_channel<uint8_t, 2, 1> flexPercent = (uint8_t)0;
	/**
	 * @@GAUGE_NAME_WG_POSITION@@
	 * units: %
	 * offset 138
	 */
	scaled_channel<int16_t, 100, 1> wastegatePositionSensor = (int16_t)0;
	/**
	 * @@GAUGE_NAME_FUEL_PRESSURE_HIGH@@
	 * units: bar
	 * offset 140
	 */
	scaled_channel<int16_t, 10, 1> highFuelPressure = (int16_t)0;
	/**
	 * offset 142
	 */
	uint8_t tempLogging3 = (uint8_t)0;
	/**
	 * offset 143
	 */
	uint8_t tempLogging4 = (uint8_t)0;
	/**
	 * offset 144
	 */
	float calibrationValue = (float)0;
	/**
	 * offset 148
	 */
	uint8_t calibrationMode = (uint8_t)0;
	/**
	 * Idle: Stepper target position
	 * offset 149
	 */
	uint8_t idleStepperTargetPosition = (uint8_t)0;
	/**
	 * need 4 byte alignment
	 * units: units
	 * offset 150
	 */
	uint8_t alignmentFill_at_150[2] = {};
	/**
	 * @@GAUGE_NAME_TRG_ERR@@
	 * units: counter
	 * offset 152
	 */
	uint32_t totalTriggerErrorCounter = (uint32_t)0;
	/**
	 * offset 156
	 */
	uint32_t orderingErrorCounter = (uint32_t)0;
	/**
	 * @@GAUGE_NAME_WARNING_COUNTER@@
	 * units: count
	 * offset 160
	 */
	uint16_t warningCounter = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_WARNING_LAST@@
	 * units: error
	 * offset 162
	 */
	uint16_t lastErrorCode = (uint16_t)0;
	/**
	 * Warning code
	 * units: error
	 * offset 164
	 */
	uint16_t recentErrorCode[8] = {};
	/**
	 * units: val
	 * offset 180
	 */
	float debugFloatField1 = (float)0;
	/**
	 * units: val
	 * offset 184
	 */
	float debugFloatField2 = (float)0;
	/**
	 * units: val
	 * offset 188
	 */
	float debugFloatField3 = (float)0;
	/**
	 * units: val
	 * offset 192
	 */
	float debugFloatField4 = (float)0;
	/**
	 * units: val
	 * offset 196
	 */
	float debugFloatField5 = (float)0;
	/**
	 * units: val
	 * offset 200
	 */
	float debugFloatField6 = (float)0;
	/**
	 * units: val
	 * offset 204
	 */
	float debugFloatField7 = (float)0;
	/**
	 * units: val
	 * offset 208
	 */
	uint32_t debugIntField1 = (uint32_t)0;
	/**
	 * units: val
	 * offset 212
	 */
	uint32_t debugIntField2 = (uint32_t)0;
	/**
	 * units: val
	 * offset 216
	 */
	uint32_t debugIntField3 = (uint32_t)0;
	/**
	 * units: val
	 * offset 220
	 */
	uint32_t debugIntField4 = (uint32_t)0;
	/**
	 * units: val
	 * offset 224
	 */
	uint32_t debugIntField5 = (uint32_t)0;
	/**
	 * EGT
	 * units: deg C
	 * offset 228
	 */
	scaled_channel<int16_t, 4, 1> egt[EGT_CHANNEL_COUNT] = {};
	/**
	 * units: V
	 * offset 244
	 */
	scaled_channel<int16_t, 1000, 1> rawTps1Primary = (int16_t)0;
	/**
	 * units: V
	 * offset 246
	 */
	scaled_channel<int16_t, 1000, 1> rawClt = (int16_t)0;
	/**
	 * units: V
	 * offset 248
	 */
	scaled_channel<int16_t, 1000, 1> rawIat = (int16_t)0;
	/**
	 * units: V
	 * offset 250
	 */
	scaled_channel<int16_t, 1000, 1> rawOilPressure = (int16_t)0;
	/**
	 * units: V
	 * offset 252
	 */
	scaled_channel<int16_t, 1000, 1> rawAcPressure = (int16_t)0;
	/**
	 * units: V
	 * offset 254
	 */
	scaled_channel<int16_t, 1000, 1> rawFuelLevel = (int16_t)0;
	/**
	 * units: V
	 * offset 256
	 */
	float rawPpsPrimary = (float)0;
	/**
	 * units: V
	 * offset 260
	 */
	float rawPpsSecondary = (float)0;
	/**
	 * units: V
	 * offset 264
	 */
	float rawRawPpsPrimary = (float)0;
	/**
	 * units: V
	 * offset 268
	 */
	float rawRawPpsSecondary = (float)0;
	/**
	 * @@GAUGE_NAME_IDLE_POSITION@@
	 * units: %
	 * offset 272
	 */
	scaled_channel<int16_t, 100, 1> idlePositionSensor = (int16_t)0;
	/**
	 * @@GAUGE_NAME_AFR@@
	 * units: AFR
	 * offset 274
	 */
	scaled_channel<uint16_t, 1000, 1> AFRValue = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_AFR2@@
	 * units: AFR
	 * offset 276
	 */
	scaled_channel<uint16_t, 1000, 1> AFRValue2 = (uint16_t)0;
	/**
	 * @@SMOOTHED_GAUGE_NAME_AFR@@
	 * units: AFR
	 * offset 278
	 */
	scaled_channel<uint16_t, 1000, 1> SmoothedAFRValue = (uint16_t)0;
	/**
	 * @@SMOOTHED_GAUGE_NAME_AFR2@@
	 * units: AFR
	 * offset 280
	 */
	scaled_channel<uint16_t, 1000, 1> SmoothedAFRValue2 = (uint16_t)0;
	/**
	 * Vss Accel
	 * units: m/s2
	 * offset 282
	 */
	scaled_channel<uint16_t, 300, 1> VssAcceleration = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_LAMBDA2@@
	 * offset 284
	 */
	scaled_channel<uint16_t, 10000, 1> lambdaValue2 = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_VVT_B1E@@
	 * units: deg
	 * offset 286
	 */
	scaled_channel<int16_t, 50, 1> vvtPositionB1E = (int16_t)0;
	/**
	 * @@GAUGE_NAME_VVT_B2I@@
	 * units: deg
	 * offset 288
	 */
	scaled_channel<int16_t, 50, 1> vvtPositionB2I = (int16_t)0;
	/**
	 * @@GAUGE_NAME_VVT_B2E@@
	 * units: deg
	 * offset 290
	 */
	scaled_channel<int16_t, 50, 1> vvtPositionB2E = (int16_t)0;
	/**
	 * units: V
	 * offset 292
	 */
	scaled_channel<int16_t, 1000, 1> rawTps1Secondary = (int16_t)0;
	/**
	 * units: V
	 * offset 294
	 */
	scaled_channel<int16_t, 1000, 1> rawTps2Primary = (int16_t)0;
	/**
	 * units: V
	 * offset 296
	 */
	scaled_channel<int16_t, 1000, 1> rawTps2Secondary = (int16_t)0;
	/**
	 * @@GAUGE_NAME_ACCEL_VERT@@
	 * units: G
	 * offset 298
	 */
	scaled_channel<int16_t, 1000, 1> accelerationVert = (int16_t)0;
	/**
	 * @@GAUGE_NAME_GYRO_YAW@@
	 * units: deg/sec
	 * offset 300
	 */
	scaled_channel<int16_t, 1000, 1> gyroYaw = (int16_t)0;
	/**
	 * units: deg
	 * offset 302
	 */
	int8_t vvtTargets[4] = {};
	/**
	 * @@GAUGE_NAME_TURBO_SPEED@@
	 * units: hz
	 * offset 306
	 */
	uint16_t turboSpeed = (uint16_t)0;
	/**
	 * Ign: Timing Cyl
	 * units: deg
	 * offset 308
	 */
	scaled_channel<int16_t, 50, 1> ignitionAdvanceCyl[MAX_CYLINDER_COUNT] = {};
	/**
	 * units: %
	 * offset 332
	 */
	scaled_channel<int16_t, 100, 1> tps1Split = (int16_t)0;
	/**
	 * units: %
	 * offset 334
	 */
	scaled_channel<int16_t, 100, 1> tps2Split = (int16_t)0;
	/**
	 * units: %
	 * offset 336
	 */
	scaled_channel<int16_t, 100, 1> tps12Split = (int16_t)0;
	/**
	 * units: %
	 * offset 338
	 */
	scaled_channel<int16_t, 100, 1> accPedalSplit = (int16_t)0;
	/**
	 * units: %
	 * offset 340
	 */
	scaled_channel<int16_t, 100, 1> accPedalUnfiltered = (int16_t)0;
	/**
	 * Ign: Cut Code
	 * units: code
	 * offset 342
	 */
	int8_t sparkCutReason = (int8_t)0;
	/**
	 * Fuel: Cut Code
	 * units: code
	 * offset 343
	 */
	int8_t fuelCutReason = (int8_t)0;
	/**
	 * Ign: Total spark cut
	 * units: ratio
	 * offset 344
	 */
	float totalSparkCut = (float)0;
	/**
	 * Fuel: Total fuel cut
	 * units: ratio
	 * offset 348
	 */
	float totalFuelCut = (float)0;
	/**
	 * @@GAUGE_NAME_AIR_FLOW_ESTIMATE@@
	 * units: kg/h
	 * offset 352
	 */
	scaled_channel<uint16_t, 10, 1> mafEstimate = (uint16_t)0;
	/**
	 * sync: instant RPM
	 * units: rpm
	 * offset 354
	 */
	uint16_t instantRpm = (uint16_t)0;
	/**
	 * units: V
	 * offset 356
	 */
	scaled_channel<uint16_t, 1000, 1> rawMap = (uint16_t)0;
	/**
	 * units: V
	 * offset 358
	 */
	scaled_channel<uint16_t, 1000, 1> rawMapFast = (uint16_t)0;
	/**
	 * units: V
	 * offset 360
	 */
	scaled_channel<uint16_t, 1000, 1> rawAfr = (uint16_t)0;
	/**
	 * need 4 byte alignment
	 * units: units
	 * offset 362
	 */
	uint8_t alignmentFill_at_362[2] = {};
	/**
	 * offset 364
	 */
	float calibrationValue2 = (float)0;
	/**
	 * Lua: Tick counter
	 * units: count
	 * offset 368
	 */
	uint32_t luaInvocationCounter = (uint32_t)0;
	/**
	 * Lua: Last tick duration
	 * units: nt
	 * offset 372
	 */
	uint32_t luaLastCycleDuration = (uint32_t)0;
	/**
	 * offset 376
	 */
	uint32_t vssEdgeCounter = (uint32_t)0;
	/**
	 * offset 380
	 */
	uint32_t issEdgeCounter = (uint32_t)0;
	/**
	 * @@GAUGE_NAME_AUX_LINEAR_1@@
	 * offset 384
	 */
	float auxLinear1 = (float)0;
	/**
	 * @@GAUGE_NAME_AUX_LINEAR_2@@
	 * offset 388
	 */
	float auxLinear2 = (float)0;
	/**
	 * @@GAUGE_NAME_AUX_LINEAR_3@@
	 * offset 392
	 */
	float auxLinear3 = (float)0;
	/**
	 * @@GAUGE_NAME_AUX_LINEAR_4@@
	 * offset 396
	 */
	float auxLinear4 = (float)0;
	/**
	 * units: kPa
	 * offset 400
	 */
	scaled_channel<uint16_t, 10, 1> fallbackMap = (uint16_t)0;
	/**
	 * Effective MAP
	 * units: kPa
	 * offset 402
	 */
	scaled_channel<uint16_t, 10, 1> effectiveMap = (uint16_t)0;
	/**
	 * AE: Map Pred New Cycles
	 * offset 404
	 */
	uint16_t predTimerResetCnt = (uint16_t)0;
	/**
	 * AE: Map Pred Expired
	 * offset 406
	 */
	uint16_t mapPredEventOver = (uint16_t)0;
	/**
	 * Instant MAP
	 * units: kPa
	 * offset 408
	 */
	scaled_channel<uint16_t, 30, 1> instantMAPValue = (uint16_t)0;
	/**
	 * units: us
	 * offset 410
	 */
	uint16_t maxLockedDuration = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_CAN_WRITE_OK@@
	 * offset 412
	 */
	uint16_t canWriteOk = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_CAN_WRITE_ERR@@
	 * offset 414
	 */
	uint16_t canWriteNotOk = (uint16_t)0;
	/**
	 * offset 416
	 */
	uint32_t triggerPrimaryFall = (uint32_t)0;
	/**
	 * offset 420
	 */
	uint32_t triggerPrimaryRise = (uint32_t)0;
	/**
	 * offset 424
	 */
	uint32_t triggerSecondaryFall = (uint32_t)0;
	/**
	 * offset 428
	 */
	uint32_t triggerSecondaryRise = (uint32_t)0;
	/**
	 * offset 432
	 */
	uint8_t starterState = (uint8_t)0;
	/**
	 * offset 433
	 */
	uint8_t starterRelayDisable = (uint8_t)0;
	/**
	 * Ign: Multispark count
	 * offset 434
	 */
	uint8_t multiSparkCounter = (uint8_t)0;
	/**
	 * offset 435
	 */
	uint8_t extiOverflowCount = (uint8_t)0;
	/**
	 * offset 436
	 */
	pid_status_s alternatorStatus;
	/**
	 * offset 452
	 */
	pid_status_s idleStatus;
	/**
	 * offset 468
	 */
	pid_status_s etbStatus;
	/**
	 * offset 484
	 */
	pid_status_s boostStatus;
	/**
	 * offset 500
	 */
	pid_status_s wastegateDcStatus;
	/**
	 * offset 516
	 */
	pid_status_s vvtStatus[CAM_INPUTS_COUNT] = {};
	/**
	 * Aux speed 1
	 * units: s
	 * offset 580
	 */
	uint16_t auxSpeed1 = (uint16_t)0;
	/**
	 * Aux speed 2
	 * units: s
	 * offset 582
	 */
	uint16_t auxSpeed2 = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_ISS@@
	 * units: RPM
	 * offset 584
	 */
	uint16_t ISSValue = (uint16_t)0;
	/**
	 * units: V
	 * offset 586
	 */
	scaled_channel<int16_t, 1000, 1> rawAnalogInput[LUA_ANALOG_INPUT_COUNT] = {};
	/**
	 * GPPWM Output
	 * units: %
	 * offset 602
	 */
	scaled_channel<uint8_t, 2, 1> gppwmOutput[4] = {};
	/**
	 * offset 606
	 */
	scaled_channel<int16_t, 1, 1> gppwmXAxis[4] = {};
	/**
	 * offset 614
	 */
	scaled_channel<int16_t, 10, 1> gppwmYAxis[4] = {};
	/**
	 * units: V
	 * offset 622
	 */
	scaled_channel<int16_t, 1000, 1> rawBattery = (int16_t)0;
	/**
	 * offset 624
	 */
	scaled_channel<int16_t, 10, 1> ignBlendParameter[IGN_BLEND_COUNT] = {};
	/**
	 * units: %
	 * offset 632
	 */
	scaled_channel<uint8_t, 2, 1> ignBlendBias[IGN_BLEND_COUNT] = {};
	/**
	 * units: deg
	 * offset 636
	 */
	scaled_channel<int16_t, 100, 1> ignBlendOutput[IGN_BLEND_COUNT] = {};
	/**
	 * offset 644
	 */
	scaled_channel<int16_t, 10, 1> ignBlendYAxis[IGN_BLEND_COUNT] = {};
	/**
	 * offset 652
	 */
	scaled_channel<int16_t, 10, 1> veBlendParameter[VE_BLEND_COUNT] = {};
	/**
	 * units: %
	 * offset 660
	 */
	scaled_channel<uint8_t, 2, 1> veBlendBias[VE_BLEND_COUNT] = {};
	/**
	 * units: %
	 * offset 664
	 */
	scaled_channel<int16_t, 100, 1> veBlendOutput[VE_BLEND_COUNT] = {};
	/**
	 * offset 672
	 */
	scaled_channel<int16_t, 10, 1> veBlendYAxis[VE_BLEND_COUNT] = {};
	/**
	 * offset 680
	 */
	scaled_channel<int16_t, 10, 1> secondVeBlendParameter = (int16_t)0;
	/**
	 * units: %
	 * offset 682
	 */
	scaled_channel<uint8_t, 2, 1> secondVeBlendBias = (uint8_t)0;
	/**
	 * need 4 byte alignment
	 * units: units
	 * offset 683
	 */
	uint8_t alignmentFill_at_683[1] = {};
	/**
	 * offset 684
	 */
	scaled_channel<int16_t, 10, 1> secondIgnitionBlendParameter = (int16_t)0;
	/**
	 * units: %
	 * offset 686
	 */
	scaled_channel<uint8_t, 2, 1> secondIgnitionBlendBias = (uint8_t)0;
	/**
	 * need 4 byte alignment
	 * units: units
	 * offset 687
	 */
	uint8_t alignmentFill_at_687[1] = {};
	/**
	 * offset 688
	 */
	scaled_channel<int16_t, 10, 1> boostOpenLoopBlendParameter[BOOST_BLEND_COUNT] = {};
	/**
	 * units: %
	 * offset 692
	 */
	scaled_channel<uint8_t, 2, 1> boostOpenLoopBlendBias[BOOST_BLEND_COUNT] = {};
	/**
	 * units: %
	 * offset 694
	 */
	int8_t boostOpenLoopBlendOutput[BOOST_BLEND_COUNT] = {};
	/**
	 * offset 696
	 */
	scaled_channel<int16_t, 10, 1> boostOpenLoopBlendYAxis[BOOST_BLEND_COUNT] = {};
	/**
	 * offset 700
	 */
	scaled_channel<int16_t, 10, 1> boostClosedLoopBlendParameter[BOOST_BLEND_COUNT] = {};
	/**
	 * units: %
	 * offset 704
	 */
	scaled_channel<uint8_t, 2, 1> boostClosedLoopBlendBias[BOOST_BLEND_COUNT] = {};
	/**
	 * units: %
	 * offset 706
	 */
	scaled_channel<int16_t, 10, 1> boostClosedLoopBlendOutput[BOOST_BLEND_COUNT] = {};
	/**
	 * offset 710
	 */
	scaled_channel<int16_t, 10, 1> boostClosedLoopBlendYAxis[BOOST_BLEND_COUNT] = {};
	/**
	 * offset 714
	 */
	scaled_channel<int16_t, 10, 1> targetAfrBlendParameter[TARGET_AFR_BLEND_COUNT] = {};
	/**
	 * units: %
	 * offset 718
	 */
	scaled_channel<uint8_t, 2, 1> targetAfrBlendBias[TARGET_AFR_BLEND_COUNT] = {};
	/**
	 * units: %
	 * offset 720
	 */
	scaled_channel<int16_t, 10, 1> targetAfrBlendOutput[TARGET_AFR_BLEND_COUNT] = {};
	/**
	 * offset 724
	 */
	scaled_channel<int16_t, 10, 1> targetAfrBlendYAxis[TARGET_AFR_BLEND_COUNT] = {};
	/**
	offset 728 bit 0 */
	bool coilState1 : 1 {};
	/**
	offset 728 bit 1 */
	bool coilState2 : 1 {};
	/**
	offset 728 bit 2 */
	bool coilState3 : 1 {};
	/**
	offset 728 bit 3 */
	bool coilState4 : 1 {};
	/**
	offset 728 bit 4 */
	bool coilState5 : 1 {};
	/**
	offset 728 bit 5 */
	bool coilState6 : 1 {};
	/**
	offset 728 bit 6 */
	bool coilState7 : 1 {};
	/**
	offset 728 bit 7 */
	bool coilState8 : 1 {};
	/**
	offset 728 bit 8 */
	bool coilState9 : 1 {};
	/**
	offset 728 bit 9 */
	bool coilState10 : 1 {};
	/**
	offset 728 bit 10 */
	bool coilState11 : 1 {};
	/**
	offset 728 bit 11 */
	bool coilState12 : 1 {};
	/**
	offset 728 bit 12 */
	bool injectorState1 : 1 {};
	/**
	offset 728 bit 13 */
	bool injectorState2 : 1 {};
	/**
	offset 728 bit 14 */
	bool injectorState3 : 1 {};
	/**
	offset 728 bit 15 */
	bool injectorState4 : 1 {};
	/**
	offset 728 bit 16 */
	bool injectorState5 : 1 {};
	/**
	offset 728 bit 17 */
	bool injectorState6 : 1 {};
	/**
	offset 728 bit 18 */
	bool injectorState7 : 1 {};
	/**
	offset 728 bit 19 */
	bool injectorState8 : 1 {};
	/**
	offset 728 bit 20 */
	bool injectorState9 : 1 {};
	/**
	offset 728 bit 21 */
	bool injectorState10 : 1 {};
	/**
	offset 728 bit 22 */
	bool injectorState11 : 1 {};
	/**
	offset 728 bit 23 */
	bool injectorState12 : 1 {};
	/**
	offset 728 bit 24 */
	bool triggerChannel1 : 1 {};
	/**
	offset 728 bit 25 */
	bool triggerChannel2 : 1 {};
	/**
	 * bank 1 intake cam input
	offset 728 bit 26 */
	bool vvtChannel1 : 1 {};
	/**
	 * bank 1 exhaust cam input
	offset 728 bit 27 */
	bool vvtChannel2 : 1 {};
	/**
	 * bank 2 intake cam input
	offset 728 bit 28 */
	bool vvtChannel3 : 1 {};
	/**
	 * bank 2 exhaust cam input
	offset 728 bit 29 */
	bool vvtChannel4 : 1 {};
	/**
	 * AE: Map Prediction Active
	offset 728 bit 30 */
	bool isMapPredictionActive : 1 {};
	/**
	 * Error: Flex
	offset 728 bit 31 */
	bool isFlexError : 1 {};
	/**
	 * offset 732
	 */
	uint32_t outputRequestPeriod = (uint32_t)0;
	/**
	 * offset 736
	 */
	float mapFast = (float)0;
	/**
	 * Lua: Gauge
	 * units: value
	 * offset 740
	 */
	float luaGauges[LUA_GAUGE_COUNT] = {};
	/**
	 * units: V
	 * offset 772
	 */
	scaled_channel<uint16_t, 1000, 1> rawMaf2 = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_AIR_FLOW_MEASURED_2@@
	 * units: kg/h
	 * offset 774
	 */
	scaled_channel<uint16_t, 10, 1> mafMeasured2 = (uint16_t)0;
	/**
	 * offset 776
	 */
	uint16_t schedulingUsedCount = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_VVS@@
	 * units: kph
	 * offset 778
	 */
	scaled_channel<uint16_t, 100, 1> vehicleSpeedKph = (uint16_t)0;
	/**
	 * units: %
	 * offset 780
	 */
	scaled_channel<uint16_t, 100, 1> Gego = (uint16_t)0;
	/**
	 * units: count
	 * offset 782
	 */
	uint16_t testBenchIter = (uint16_t)0;
	/**
	 * units: deg C
	 * offset 784
	 */
	scaled_channel<int16_t, 100, 1> oilTemp = (int16_t)0;
	/**
	 * units: deg C
	 * offset 786
	 */
	scaled_channel<int16_t, 100, 1> fuelTemp = (int16_t)0;
	/**
	 * units: deg C
	 * offset 788
	 */
	scaled_channel<int16_t, 100, 1> ambientTemp = (int16_t)0;
	/**
	 * units: deg C
	 * offset 790
	 */
	scaled_channel<int16_t, 100, 1> compressorDischargeTemp = (int16_t)0;
	/**
	 * units: kPa
	 * offset 792
	 */
	scaled_channel<uint16_t, 30, 1> compressorDischargePressure = (uint16_t)0;
	/**
	 * units: kPa
	 * offset 794
	 */
	scaled_channel<uint16_t, 30, 1> throttleInletPressure = (uint16_t)0;
	/**
	 * units: sec
	 * offset 796
	 */
	uint16_t ignitionOnTime = (uint16_t)0;
	/**
	 * units: sec
	 * offset 798
	 */
	uint16_t engineRunTime = (uint16_t)0;
	/**
	 * units: km
	 * offset 800
	 */
	scaled_channel<uint16_t, 10, 1> distanceTraveled = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_AFR_GAS_SCALE@@
	 * units: AFR
	 * offset 802
	 */
	scaled_channel<uint16_t, 1000, 1> afrGasolineScale = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_AFR2_GAS_SCALE@@
	 * units: AFR
	 * offset 804
	 */
	scaled_channel<uint16_t, 1000, 1> afr2GasolineScale = (uint16_t)0;
	/**
	 * need 4 byte alignment
	 * units: units
	 * offset 806
	 */
	uint8_t alignmentFill_at_806[2] = {};
	/**
	 * offset 808
	 */
	float wheelSlipRatio = (float)0;
	/**
	 * offset 812
	 */
	uint8_t ignitorDiagnostic[MAX_CYLINDER_COUNT] = {};
	/**
	 * offset 824
	 */
	uint8_t injectorDiagnostic[MAX_CYLINDER_COUNT] = {};
	/**
	 * @@GAUGE_NAME_FUEL_LAST_INJECTION_STAGE_2@@
	 * units: ms
	 * offset 836
	 */
	scaled_channel<uint16_t, 300, 1> actualLastInjectionStage2 = (uint16_t)0;
	/**
	 * need 4 byte alignment
	 * units: units
	 * offset 838
	 */
	uint8_t alignmentFill_at_838[2] = {};
	/**
	 * @@GAUGE_NAME_FUEL_LAST_INJECTION_RATIO_STAGE_2@@
	 * offset 840
	 */
	float actualLastInjectionRatioStage2 = (float)0;
	/**
	 * @@GAUGE_NAME_FUEL_INJ_DUTY_STAGE_2@@
	 * units: %
	 * offset 844
	 */
	scaled_channel<uint8_t, 2, 1> injectorDutyCycleStage2 = (uint8_t)0;
	/**
	 * offset 845
	 */
	uint8_t rawFlexFreq = (uint8_t)0;
	/**
	 * offset 846
	 */
	uint8_t canReWidebandCmdStatus = (uint8_t)0;
	/**
	 * offset 847
	 */
	uint8_t deviceUid = (uint8_t)0;
	/**
	 * offset 848
	 */
	uint16_t mc33810spiErrorCounter = (uint16_t)0;
	/**
	 * offset 850
	 */
	uint8_t injectionPrimingCounter = (uint8_t)0;
	/**
	 * offset 851
	 */
	uint8_t tempLogging2 = (uint8_t)0;
	/**
	 * @@GAUGE_NAME_AC_PRESSURE@@
	 * units: kPa
	 * offset 852
	 */
	float acPressure = (float)0;
	/**
	 * units: V
	 * offset 856
	 */
	scaled_channel<int16_t, 1000, 1> rawAuxAnalog1 = (int16_t)0;
	/**
	 * units: V
	 * offset 858
	 */
	scaled_channel<int16_t, 1000, 1> rawAuxAnalog2 = (int16_t)0;
	/**
	 * units: V
	 * offset 860
	 */
	scaled_channel<int16_t, 1000, 1> rawAuxAnalog3 = (int16_t)0;
	/**
	 * units: V
	 * offset 862
	 */
	scaled_channel<int16_t, 1000, 1> rawAuxAnalog4 = (int16_t)0;
	/**
	 * ECU: Fast ADC errors
	 * offset 864
	 */
	uint8_t fastAdcErrorCount = (uint8_t)0;
	/**
	 * ECU: Slow ADC errors
	 * offset 865
	 */
	uint8_t slowAdcErrorCount = (uint8_t)0;
	/**
	 * units: V
	 * offset 866
	 */
	scaled_channel<int16_t, 1000, 1> rawAuxTemp1 = (int16_t)0;
	/**
	 * units: V
	 * offset 868
	 */
	scaled_channel<int16_t, 1000, 1> rawAuxTemp2 = (int16_t)0;
	/**
	 * units: V
	 * offset 870
	 */
	scaled_channel<int16_t, 1000, 1> rawAmbientTemp = (int16_t)0;
	/**
	 * offset 872
	 */
	uint32_t rtcUnixEpochTime = (uint32_t)0;
	/**
	 * offset 876
	 */
	int8_t sparkCutReasonBlinker = (int8_t)0;
	/**
	 * offset 877
	 */
	int8_t fuelCutReasonBlinker = (int8_t)0;
	/**
	 * offset 878
	 */
	int16_t hp = (int16_t)0;
	/**
	 * offset 880
	 */
	int16_t torque = (int16_t)0;
	/**
	 * need 4 byte alignment
	 * units: units
	 * offset 882
	 */
	uint8_t alignmentFill_at_882[2] = {};
	/**
	 * offset 884
	 */
	float throttlePressureRatio = (float)0;
	/**
	 * offset 888
	 */
	float throttleEffectiveAreaOpening = (float)0;
	/**
	 * offset 892
	 */
	uint32_t mcuSerial = (uint32_t)0;
	/**
	 * offset 896
	 */
	uint8_t sd_error = (uint8_t)0;
	/**
	 * SD: Logging state
	 * units: code
	 * offset 897
	 */
	uint8_t sdLoggingState = (uint8_t)0;
	/**
	 * ECU: Fast ADC overruns
	 * offset 898
	 */
	uint8_t fastAdcOverrunCount = (uint8_t)0;
	/**
	 * ECU: Slow ADC overruns
	 * offset 899
	 */
	uint8_t slowAdcOverrunCount = (uint8_t)0;
	/**
	 * ECU: Fast ADC error type
	 * offset 900
	 */
	uint8_t fastAdcLastError = (uint8_t)0;
	/**
	 * need 4 byte alignment
	 * units: units
	 * offset 901
	 */
	uint8_t alignmentFill_at_901[1] = {};
	/**
	 * ECU: Fast ADC period
	 * units: ticks
	 * offset 902
	 */
	uint16_t fastAdcPeriod = (uint16_t)0;
	/**
	 * ECU: Fast ADC conversions
	 * units: N
	 * offset 904
	 */
	uint16_t fastAdcConversionCount = (uint16_t)0;
	/**
	 * offset 906
	 */
	uint8_t canReWidebandVersion = (uint8_t)0;
	/**
	 * offset 907
	 */
	uint8_t canReWidebandFwDay = (uint8_t)0;
	/**
	 * offset 908
	 */
	uint8_t canReWidebandFwMon = (uint8_t)0;
	/**
	 * offset 909
	 */
	uint8_t canReWidebandFwYear = (uint8_t)0;
	/**
	 * offset 910
	 */
	uint16_t transitionEventCode = (uint16_t)0;
	/**
	 * offset 912
	 */
	uint16_t transitionEventsCounter = (uint16_t)0;
	/**
	 * units: kPa
	 * offset 914
	 */
	uint8_t mapPerCylinder[MAX_CYLINDER_COUNT] = {};
	/**
	 * Analog multi-switch 1 position
	 * offset 926
	 */
	uint8_t analogMultiSwitchPosition1 = (uint8_t)0;
	/**
	 * Analog multi-switch 2 position
	 * offset 927
	 */
	uint8_t analogMultiSwitchPosition2 = (uint8_t)0;
	/**
	 * Analog multi-switch 3 position
	 * offset 928
	 */
	uint8_t analogMultiSwitchPosition3 = (uint8_t)0;
	/**
	 * Analog multi-switch 4 position
	 * offset 929
	 */
	uint8_t analogMultiSwitchPosition4 = (uint8_t)0;
	/**
	 * need 4 byte alignment
	 * units: units
	 * offset 930
	 */
	uint8_t alignmentFill_at_930[2] = {};
	/**
	 * Analog multi-switch 1 voltage
	 * units: V
	 * offset 932
	 */
	scaled_channel<float, 1000, 1> analogMultiSwitchVoltage1 = (float)0;
	/**
	 * Analog multi-switch 2 voltage
	 * units: V
	 * offset 936
	 */
	scaled_channel<float, 1000, 1> analogMultiSwitchVoltage2 = (float)0;
	/**
	 * Analog multi-switch 3 voltage
	 * units: V
	 * offset 940
	 */
	scaled_channel<float, 1000, 1> analogMultiSwitchVoltage3 = (float)0;
	/**
	 * Analog multi-switch 4 voltage
	 * units: V
	 * offset 944
	 */
	scaled_channel<float, 1000, 1> analogMultiSwitchVoltage4 = (float)0;
	/**
	 * Fuel: Consumption trip average
	 * units: L/100km
	 * offset 948
	 */
	scaled_channel<uint16_t, 10, 1> fuelConsumptionL100km = (uint16_t)0;
	/**
	 * Fuel: Flow rate (instant)
	 * units: L/hr
	 * offset 950
	 */
	scaled_channel<uint16_t, 100, 1> fuelConsumptionLitersPerHour = (uint16_t)0;
};
static_assert(sizeof(output_channels_s) == 952);

// end
// this section was generated automatically by rusEFI tool config_definition_base-all.jar based on (unknown script) console/binary/output_channels.txt
