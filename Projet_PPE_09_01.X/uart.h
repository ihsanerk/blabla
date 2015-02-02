#ifndef UART_H
#define	UART_H




#include "definition.h"
#include "math.h"

//Prototypes des fonctions
void uart_init();
unsigned char uartGetChar();
void uartSendChar(const unsigned char c);
void uartWaitEndOfTransmission();
void __attribute__((__interrupt__,auto_psv)) _U2TXInterrupt(void);

//Variables
extern char 		recievedChar;




#endif	/* UART_H */

