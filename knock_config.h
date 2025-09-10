/**
 * @file knock_config.h
 */

#pragma once

// Knock is on ADC1 (PA6 is available on ADC1)
#define KNOCK_ADC ADCD2

// knock 1 - pin PA6
#define KNOCK_ADC_CH1 ADC_CHANNEL_IN6
#define KNOCK_PIN_CH1 Gpio::A6

// Sample rate & time - depends on the exact MCU
#define KNOCK_SAMPLE_TIME ADC_SAMPLE_84
#define KNOCK_SAMPLE_RATE (STM32_PCLK2 / (4 * (84 + 12)))
