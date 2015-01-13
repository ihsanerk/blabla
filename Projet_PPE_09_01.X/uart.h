#ifndef UART_H
#define	UART_H


//Librairies
#include "configuration.h"

//Prototypes des fonctions
void uart_init();
unsigned char uartGetChar();
void uartSendChar(const unsigned char c);
void uartWaitEndOfTransmission();
void __attribute__((__interrupt__,auto_psv)) _U1TXInterrupt(void);

//Variables
extern char 		recievedChar;




#endif	/* UART_H */

