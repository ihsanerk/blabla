/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <xc.h>
#include <stdint.h>        /* Includes uint16_t definition */
#include <stdbool.h>       /* Includes true/false definition */

#include "../GaLib/include/debug/leds.h"

/******************************************************************************/
/* Trap Function Prototypes                                                   */
/******************************************************************************/

/* Use if INTCON2 ALTIVT=1 */
void __attribute__((interrupt, no_auto_psv)) _OscillatorFail(void);
void __attribute__((interrupt, no_auto_psv)) _AddressError(void);
void __attribute__((interrupt, no_auto_psv)) _StackError(void);
void __attribute__((interrupt, no_auto_psv)) _MathError(void);

/* Default interrupt handler */
void __attribute__((interrupt, no_auto_psv)) _DefaultInterrupt(void);

/* These are additional traps in the 33E family.  Refer to the PIC33E
migration guide.  There are no Alternate Vectors in the 33E family. */
void __attribute__((interrupt, no_auto_psv)) _HardTrapError(void);
void __attribute__((interrupt, no_auto_psv)) _SoftTrapError(void);


/******************************************************************************/
/* Trap Handling                                                              */
/*                                                                            */
/* These trap routines simply ensure that the device continuously loops       */
/* within each routine.  Users who actually experience one of these traps     */
/* can add code to handle the error.  Some basic examples for trap code,      */
/* including assembly routines that process trap sources, are available at    */
/* www.microchip.com/codeexamples                                             */
/******************************************************************************/

/* Primary (non-alternate) address error trap function declarations */
void __attribute__((interrupt, no_auto_psv)) _OscillatorFail(void) {
    INTCON1bits.OSCFAIL = 0; /* Clear the trap flag */
    while (1);
}

void __attribute__((interrupt, no_auto_psv)) _AddressError(void) {
    INTCON1bits.ADDRERR = 0; /* Clear the trap flag */
    while (1);
}

void __attribute__((interrupt, no_auto_psv)) _StackError(void) {
    INTCON1bits.STKERR = 0; /* Clear the trap flag */
    ledSet(7, true);
    while (1);
}

void __attribute__((interrupt, no_auto_psv)) _MathError(void) {
    INTCON1bits.MATHERR = 0; /* Clear the trap flag */
    while (1);
}

/******************************************************************************/
/* Default Interrupt Handler                                                  */
/*                                                                            */
/* This executes when an interrupt occurs for an interrupt source with an     */
/* improperly defined or undefined interrupt handling routine.                */

/******************************************************************************/
void __attribute__((interrupt, no_auto_psv)) _DefaultInterrupt(void) {
    while (1);
}

/* These traps are new to the dsPIC33E family.  Refer to the device Interrupt
chapter of the FRM to understand trap priority. */
void __attribute__((interrupt, no_auto_psv)) _HardTrapError(void) {
    while (1);
}

void __attribute__((interrupt, no_auto_psv)) _SoftTrapError(void) {
    while (1);
}
