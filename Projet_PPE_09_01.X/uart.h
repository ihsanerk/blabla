#ifndef UART_H
#define	UART_H


//Librairies
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <p33EP512MU810.h>
#include <libpic30.h>
#include <xc.h>
#include <pps.h>
#include <uart.h>

#include "definition.h"

//Prototypes des fonctions
void uart_init();
unsigned char uartGetChar();
void uartSendChar(const unsigned char c);
void uartWaitEndOfTransmission();
void __attribute__((__interrupt__,auto_psv)) _U2TXInterrupt(void);

//Variables
extern char 		recievedChar;




#endif	/* UART_H */

