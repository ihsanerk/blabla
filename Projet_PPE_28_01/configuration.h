#ifndef CONFIGURATION_H
#define	CONFIGURATION_H


// Crytal is 24MHz.
// Configure the oscillator to operate the device at 51 MIPS using PLL
#define _XTAL_FREQ  24000000
#define FOSC    (102000000)
#define FCY     (FOSC/2)






//Prototypes
void pinConfiguration ();


#endif	/* CONFIGURATION_H */

