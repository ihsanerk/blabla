#include "adc.h"

#include <xc.h>

bool adc_enable[ADC_MAX];
static uint16_t adc_data[ADC_MAX];
static size_t adc_current_channel;

void adcInit() {
    // Initialise ADC1
    AD1CON1 = 0;
    AD1CON1bits.SSRC = 0b111; // auto-convert

    AD1CON2 = 0;
    AD1CON2bits.CHPS = 0b11; // convert CH0 to CH3

    AD1CON3 = 0;
    AD1CON3bits.SAMC = 31; // sample every 31 Tad
    AD1CON3bits.ADCS = 2; // Tad = (2 + 1) * Tcy

    AD1CON4 = 0;

    AD1CHS123 = 0;

    AD1CHS0 = 0;

    // Enable ADC
    AD1CON1bits.ADON = 1;

    // Start first conversion
    int i;
    for(i = 0; i < ADC_MAX; ++i) {
        if(adc_enable[i]) {
            adc_current_channel = i;
            AD1CHS0bits.CH0SA = adc_current_channel;
            AD1CON1bits.SAMP = 1;
            break;
        }
    }
}

void adcPoll() {
    if(AD1CON1bits.DONE) {
        // Save value
        adc_data[adc_current_channel++] = (uint16_t) ADC1BUF0;
        // Search next channel
        int i;
        for(i = 0; i < ADC_MAX; ++i) {
            unsigned int next_channel = (adc_current_channel + i) % ADC_MAX;
            if(adc_enable[next_channel]) {
                adc_current_channel = next_channel;
                break;
            }
        }
        // Restart convertion
        AD1CHS0bits.CH0SA = adc_current_channel;
        AD1CON1bits.SAMP = 1;
    }
}

uint16_t adcGetChannel(uint8_t channel) {
    if(adc_enable[channel]) {
        return adc_data[channel];
    }
    return 0;
}
