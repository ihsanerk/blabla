#ifndef DEBUGGER_H
#define	DEBUGGER_H

//Librairies
#include "definition.h"
#include "uart.h"

//Pins
#define LED0 LATDbits.LATD6
#define LED1 LATDbits.LATD5
#define LED2 LATDbits.LATD4
#define LED3 LATDbits.LATD13
#define LED4 LATDbits.LATD12
#define LED5 LATDbits.LATD3
#define LED6 LATDbits.LATD2
#define LED7 LATDbits.LATD1

//Prototypes
void debugger_init();
void sendString (char* string);
void sendSignedInteger (int32_t n);
void sendUnSignedInteger (uint32_t n);


#endif	/* DEBUGGER_H */

