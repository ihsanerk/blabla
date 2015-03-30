#ifndef UART_H_INCLUDED
#define UART_H_INCLUDED

//Libraries
#include "Definitions.h"

//Pines

//Structures

//Prototypes
void 				uartInit();
unsigned char 		uartGetChar();
void 				uartSendChar(const unsigned char c);
void 				uartWaitEndOfTransmission();

//Variables
extern char 		recievedChar;

#endif // UART_H_INCLUDED
