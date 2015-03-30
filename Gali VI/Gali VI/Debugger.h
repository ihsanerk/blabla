#ifndef DEBUGGER_H_INCLUDED
#define DEBUGGER_H_INCLUDED

//Libraries
#include "Definitions.h"
#include "Uart.h"

//Pins
#define LED1 LATDbits.LATD6
#define LED2 LATDbits.LATD5
#define LED3 LATDbits.LATD4
#define LED4 LATDbits.LATD13
#define LED5 LATDbits.LATD12
#define LED6 LATDbits.LATD3
#define LED7 LATDbits.LATD2
#define LED8 LATDbits.LATD1
	
//Variables

//Prototypes
void 			debuggerInit ();
void 			sendString (char* string);
void 			sendSignedInteger (int32 n);
void 			sendUnSignedInteger (uint32 n);
void 			regulationPD ();

void 			displaySharp ();
void 			displayPos ();
void 			displayAsser ();

#endif // DEBUGGER_H_INCLUDED
