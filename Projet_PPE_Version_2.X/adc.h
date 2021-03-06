/* 
 * File:   adc.h
 * Author: guillaume
 *
 * Created on 26 janvier 2015, 13:44
 */

#ifndef ADC_H
#define	ADC_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "math.h"


// Initialise ADC and start first conversion
void adcInit();
// Store conversion result if available and restart conversion
void adcPoll();
// Get last conversion result from channel
uint16_t adcGetChannel(uint8_t channel);


// Enables ADC channels
extern bool adc_enable[ADC_MAX];

#endif	/* ADC_H */
