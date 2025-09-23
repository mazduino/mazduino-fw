/**
 * @file knock_config.h
 */

#pragma once

// Knock is on ADC2 (PC0 is available on ADC2)
#define KNOCK_ADC ADCD2

// knock 1 - pin PC0
#define KNOCK_ADC_CH1 ADC_CHANNEL_IN10
#define KNOCK_PIN_CH1 Gpio::C0

// Sample rate & time - depends on the exact MCU
#define KNOCK_SAMPLE_TIME ADC_SAMPLE_84
#define KNOCK_SAMPLE_RATE (STM32_PCLK2 / (4 * (84 + 12)))
