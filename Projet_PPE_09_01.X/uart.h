#ifndef UART_H
#define	UART_H


//Librairies
#include "definition.h"

//Prototypes des fonctions
void uart_init();
unsigned char uartGetChar();
void uartSendChar(const unsigned char c);
void uartWaitEndOfTransmission();
void __attribute__((__interrupt__)) _U1TXInterrupt(void);

//Variables
extern char recievedChar;




#endif	/* UART_H */

