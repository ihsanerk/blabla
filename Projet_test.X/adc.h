#ifndef ADC_H
#define	ADC_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

// Initialise ADC and start first conversion
void adcInit();
// Store conversion result if available and restart conversion
void adcPoll();
// Get last conversion result from channel
uint16_t adcGetChannel(uint8_t channel);

// Number of channels on device
#define ADC_MAX 32
// Enables ADC channels
extern bool adc_enable[ADC_MAX];

#endif	/* ADC_H */
