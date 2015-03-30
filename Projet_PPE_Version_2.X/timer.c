//Librairies
#include "timer.h"

void timerInit() {
    // --- Timer 2 : Control du robot ---
    T2CONbits.TON = 0; // Disable timer
    T2CONbits.TCKPS = 0b01; // Prescaler : 8
    T2CONbits.T32 = 0; // 16 bits
    T2CONbits.TCS = 0; // Internal clock
    T2CONbits.TGATE = 0; // Timer mode
    TMR2 = 0x00; // Clear Timer register
    PR2 = 4000; // Period value (4000 = 1000Hz)

    IPC1bits.T2IP = 0b101; // Priority : 6
    IFS0bits.T2IF = 0; // Clear flag
    IEC0bits.T2IE = 1; // Enable interrupt

    // --- Timers 6 et 7 (32 bits) : Fin du match ---

    /*
            PRESCALER 256
            FOVERFLOW 0.011111111 Hz (90 secondes)
            FCY 32 000 000
            PR	11 250 000 ( 1010 1011 1010 1001 0101 0000 )
     */
    T6CONbits.TON = 0; // Disable timer
    T7CONbits.TON = 0; // Disable timer

    // Timer 6
    T6CONbits.TCKPS = 0b11; // Prescaler : 256
    T6CONbits.T32 = 1; // 32 bits
    T6CONbits.TCS = 0; // Internal clock
    T6CONbits.TGATE = 0; // Timer mode
    TMR6 = 0x00; // Clear Timer register
    PR6 = 43344; // Period value (LSB) 1010 1001 0101 0000

    // Timer 7
    T7CONbits.TCS = 0; // Internal clock
    T7CONbits.TGATE = 0; // Timer mode
    TMR7 = 0x00; // Clear Timer register
    PR7 = 171; // Period value (MSB) 1010 1011

    // Interruption
    _T7IP = 0b111; // Priority : 7 (Highest)
    _T7IF = 0; // Clear flag
    _T7IE = 1; // Enable interrupt
}

void jackInit ()
{
	// Pin
	RPINR0bits.INT1R = 104;

	// Register
	IEC1bits.INT1IE    = 0;     // Disable interrupt
	IFS1bits.INT1IF    = 0;     // Clear interrupt flag
    INTCON2bits.INT1EP = 1;		// Interrupt on negative edge

	IPC5bits.INT1IP    = 0b110; // Priority : 6

    IEC1bits.INT1IE    = 1;     // Enable interrupt
}