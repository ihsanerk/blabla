
#include "encodeur.h"
#include "debug.h"

#include <xc.h>

Encoder encoder_right;
Encoder encoder_left;

void encodersInit() {
    QEI1CONbits.QEIEN = 1; // Enable QEI
    QEI1CONbits.QEISIDL = 0; // Continue in idle mode
    QEI1CONbits.PIMOD = 0b000; // Position init not affected by index
    QEI1CONbits.IMV = 0b00; // Index input event don't match with position counter
    QEI1CONbits.INTDIV = 0b000; // No presclale
    QEI1CONbits.CNTPOL = 1; // Count in negative
    QEI1CONbits.GATEN = 0; // No external count enable bit
    QEI1CONbits.CCM = 0b00; // Select QEI mode Count

    QEI1IOCbits.QCAPEN = 0;
    QEI1IOCbits.FLTREN = 0; // Digital filter disabled
    QEI1IOCbits.QFDIV = 0b000;
    QEI1IOCbits.OUTFNC = 0b00;
    QEI1IOCbits.SWPAB = 0;
    QEI1IOCbits.HOMPOL = 0;
    QEI1IOCbits.IDXPOL = 0;
    QEI1IOCbits.QEBPOL = 0;
    QEI1IOCbits.QEAPOL = 0;

    QEI1STATbits.PCHEQIEN = 0;
    QEI1STATbits.PCLEQIEN = 0;
    QEI1STATbits.POSOVIEN = 0;
    QEI1STATbits.PCIIEN = 0;

    QEI2CONbits.QEIEN = 1; // Enable QEI
    QEI2CONbits.QEISIDL = 0; // Continue in idle mode
    QEI2CONbits.PIMOD = 0b000; // Position init not affected by index
    QEI2CONbits.IMV = 0b00; // Index input event don't match with position counter
    QEI2CONbits.INTDIV = 0b000; // No presclale
    QEI2CONbits.CNTPOL = 0; // Count in positive
    QEI2CONbits.GATEN = 0; // No external count enable bit
    QEI2CONbits.CCM = 0b00; // Select QEI mode Count

    QEI2IOCbits.QCAPEN = 0;
    QEI2IOCbits.FLTREN = 0; // Digital filter disabled
    QEI2IOCbits.QFDIV = 0b000;
    QEI2IOCbits.OUTFNC = 0b00;
    QEI2IOCbits.SWPAB = 0;
    QEI2IOCbits.HOMPOL = 0;
    QEI2IOCbits.IDXPOL = 0;
    QEI2IOCbits.QEBPOL = 0;
    QEI2IOCbits.QEAPOL = 0;

    QEI2STATbits.PCHEQIEN = 0;
    QEI2STATbits.PCLEQIEN = 0;
    QEI2STATbits.POSOVIEN = 0; // TODO: IMPORTANT enable interrupt in overflow
    QEI2STATbits.PCIIEN = 0;

    // Initial values at middle of counter
    POS1CNTL = (uint16_t) 0xFFFF;
    POS1CNTH = (uint16_t) 0x0000;
    POS2CNTL = (uint16_t) 0xFFFF;
    POS2CNTH = (uint16_t) 0x0000;
}

// Fetch the 32-bits counters of the encoders and calculate the variation
void encodersFetch() {
    uint32_t valQEI1L, valQEI1H, valQEI2L, valQEI2H;

    // Left encoder value
    valQEI1L = POS1CNTL;
    valQEI1H = POS1HLD;
    encoder_right.new_value = (valQEI1H << 16) | valQEI1L;
    encoder_right.variation = encoder_right.new_value - encoder_right.old_value;
    encoder_right.old_value = encoder_right.new_value;

    // Right encoder value
    valQEI2L = POS2CNTL;
    valQEI2H = POS2HLD;
    encoder_left.new_value = (valQEI2H << 16) | valQEI2L;
    encoder_left.variation = encoder_left.new_value - encoder_left.old_value;
    encoder_left.old_value = encoder_left.new_value;
}

void encodersDebug() {
    logStringFormatted("Encoder r:%d l:%d ", encoder_right.variation, encoder_left.variation);
}

float encodersGetLengthVariation() {
    return (encoder_right.variation * encoder_right.mm_per_tick + encoder_left.variation * encoder_left.mm_per_tick) / 2.0f;
}

float encodersGetAngleVariation() {
    return (encoder_right.variation * encoder_right.rad_per_tick - encoder_left.variation * encoder_left.rad_per_tick) / 2.0f;
}
