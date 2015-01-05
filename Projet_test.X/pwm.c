#include "pwm.h"

#include <stdint.h>
#include <xc.h>

#include "bus.h"

bitPtr pwm_bits[PWM_MAX];
bitPtr pwm_tris[PWM_MAX];
bool pwm_enable[PWM_MAX];
unsigned int pwm_values[PWM_MAX];

void pwmInit() {
    // Set bits to output
    int i;
    for(i = 0; i < PWM_MAX; ++i) {
        if(pwm_enable[i]) {
            bitSet(pwm_tris[i], false);
        }
    }

    // --- Timer 2 : Servo PWM ---
    T2CONbits.TON = 0; // Disable timer
    T2CONbits.TCKPS = 0b01; // Prescaler : 8
    T2CONbits.T32 = 0; // 16 bits mode
    T2CONbits.TCS = 0; // Internal clock
    T2CONbits.TGATE = 0; // Timer mode
    TMR2 = 0x00; // Clear Timer register
     // in Hz
    PR2 = 400;

    IPC1bits.T2IP = 0b101; // Priority : 5

    // Enable timer 2
    T2CONbits.TON = 1;
    IFS0bits.T2IF = 0; // Clear flag
    IEC0bits.T2IE = 1; // Enable interrupt
}

void pwmStop() {
    T2CONbits.TON = 0; // Disable timer 4
    IFS0bits.T2IF = 0; // Clear flag
    IEC0bits.T2IE = 0; // Disable interrupt
}

void pwmSet(unsigned char servo, unsigned int angle) {
    if(servo < PWM_MAX && angle <= 90) {
        pwm_values[servo] = angle;
    }
}

// 10kHz Interrupt
void __attribute__((__interrupt__,auto_psv)) _T2Interrupt(void) {
    // Clear flag
    IFS0bits.T2IF = 0;
    TMR2 = 0x00; // Clear Timer register

    // Servo PWM: 50Hz (=10000/200)
    static uint16_t pwm_counter = 0;
    pwm_counter++;
    if(pwm_counter >= 200) {
        pwm_counter = 0;
    }

    int i;
    for(i = 0; i < PWM_MAX; ++i) {
        if(pwm_enable[i]) {
            // Pulse is between 0.9 and 2.1 ms (0% to 100% angle)
            if(pwm_counter < (9 + (13 * pwm_values[i]) / 90)) {
                bitSet(pwm_bits[i], true);
            }
            else {
                bitSet(pwm_bits[i], false);
            }
        }
    }
}
