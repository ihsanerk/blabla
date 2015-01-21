//Librairies
#include <stdio.h>
#include <stdlib.h>
#include <p33EP512MU810.h>
#include <libpic30.h>
#include <pps.h>
#include "configuration.h"
#include "math.h"

// Crytal is 24MHz.
// Configure the oscillator to operate the device at 51 MIPS using PLL
#define _XTAL_FREQ  24000000
#define FOSC    (102000000)
#define FCY     (FOSC/2)

void pinConfiguration ()
{
    // Disable Watch Dog Timer

RCONbits.SWDTEN=0;

TRISF=0;


// Configure PLL prescaler, PLL postscaler, PLL divisor
PLLFBD= 38; // M=34
CLKDIVbits.PLLPOST= 0; // N2=2
CLKDIVbits.PLLPRE= 0; // N1=4

// Initiate Clock Switch to Primary Oscillator with PLL (NOSC=0b011)

//Oscillator select
__builtin_write_OSCCONH(0x03);

// Clock Switch
__builtin_write_OSCCONL(OSCCON | 0x01);  //turn on OSWEN

while (OSCCONbits.OSWEN); //wait until OSWEN to low

// Wait for Clock switch to occur
while (OSCCONbits.COSC!= 0b011);

// Wait for PLL to lock
while (OSCCONbits.LOCK!= 1);


}
