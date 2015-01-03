#include "tools/timeout.h"

#include <xc.h>

static bool timeout;

void timeoutInit(void) {
    // --- Timer 4 & 5 : Timeout ---
    T4CONbits.TON = 0; // Disable timer
    T5CONbits.TON = 0; // Disable timer

    T4CONbits.TCKPS = 0b01; // Prescaler : 8
    T4CONbits.T32 = 1; // 32 bits
    T4CONbits.TCS = 0; // Internal clock
    T4CONbits.TGATE = 0; // Timer mode
    TMR4 = 0x00; // Clear Timer register

    T5CONbits.TCS = 0; // Internal clock
    T5CONbits.TGATE = 0; // Timer mode
    TMR5 = 0x00; // Clear Timer register

    IPC7bits.T5IP = 0b101; // Priority : 6
}

void timeoutSet(uint16_t msb, uint16_t lsb){
    timeout = false;
    T4CONbits.TON = 0; // Disable timer
    TMR4 = 0x00; // Clear Timer register
    TMR5 = 0x00; // Clear Timer register
    PR4 = lsb;//0x0900;//(unsigned int) ;
    PR5 = msb;//0x003D;//(unsigned int) value >> 16;
    IEC1bits.T5IE = 1; // Enable interrupt
    T4CONbits.TON = 1; // Enable timer
    IFS1bits.T5IF = 0; // Clear flag
}

bool timeoutCheck(void) {
    if(timeout) {
        timeout = false;
        T4CONbits.TON = 0; // Disable timer
        return true;
    }
    else {
        return false;
    }
}

// Control Frequency
void __attribute__((__interrupt__,auto_psv)) _T5Interrupt(void) {
    // Clear flag
    IFS1bits.T5IF = 0;

    timeout = true;
}
