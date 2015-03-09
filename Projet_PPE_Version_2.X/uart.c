//Librairies
#include <stdio.h>
#include <stdlib.h>
#include <p33EP512MU810.h>
#include <libpic30.h>
#include <pps.h>
#include "configuration.h"
#include "uart.h"
#include "debugger.h"



#define FP 40000000
#define BAUDRATE 9600
#define BRGVAL ((FP/BAUDRATE)/16) - 1


//RESSOURCES
char recievedChar;

// Programme d'initialisation des Pin
void uart_init()
{




// This is an EXAMPLE, so brutal typing goes into explaining all bit sets

	// The HPC16 board has a DB9 connector wired to UART2, so we will
	// be configuring this port only

	// configure U2MODE
	U2MODEbits.UARTEN = 0;	// Bit15 TX, RX DISABLED, ENABLE at end of func
	U2MODEbits.USIDL = 0;	// Bit13 Continue in Idle
	U2MODEbits.IREN = 0;	// Bit12 No IR translation
	U2MODEbits.RTSMD = 1;	// Bit11 Simplex Mode
	U2MODEbits.UEN = 0;		// Bits8,9 TX,RX enabled, CTS,RTS not
	U2MODEbits.WAKE = 0;	// Bit7 No Wake up (since we don't sleep here)
	U2MODEbits.LPBACK = 0;	// Bit6 No Loop Back
	U2MODEbits.ABAUD = 0;	// Bit5 No Autobaud (would require sending '55')

	U2MODEbits.BRGH = 0;	// Bit3 16 clocks per bit period
	U2MODEbits.PDSEL = 0;	// Bits1,2 8bit, No Parity
	U2MODEbits.STSEL = 0;	// Bit0 One Stop Bit

	// Load a value into Baud Rate Generator.  Example is for 9600.
	// See section 19.3.1 of datasheet.
	//  U2BRG = (Fcy/(16*BaudRate))-1
	//  U2BRG = (37M/(16*9600))-1
	//  U2BRG = 240
	U2BRG = BRGVAL;	// 40Mhz osc, 9600 Baud

	// Load all values in for U1STA SFR
	U2STAbits.UTXISEL1 = 0;	//Bit15 Int when Char is transferred (1/2 config!)
	U2STAbits.UTXINV = 0;	//Bit14 N/A, IRDA config
	U2STAbits.UTXISEL0 = 0;	//Bit13 Other half of Bit15
	U2STAbits.UTXBRK = 0;	//Bit11 Disabled
	U2STAbits.UTXEN = 0;	//Bit10 TX pins controlled by periph
	U2STAbits.UTXBF = 0;	//Bit9 *Read Only Bit*
	U2STAbits.TRMT = 0;	//Bit8 *Read Only bit*
	U2STAbits.URXISEL = 0;	//Bits6,7 Int. on character recieved
	U2STAbits.ADDEN = 0;	//Bit5 Address Detect Disabled
	U2STAbits.OERR = 0;		//Bit1 *Read Only Bit*


        // TX pour la carte Explorer 16
	//RPOR9bits.RP101R = 3;		//RP64 as U2TX

        RPINR18bits.U1RXR = 62; //RX pin 74 sur le dsPic33e
        RPOR15bits.RP127R = 3; // RP127 : le pin 73 sur dsPic33e

        //TX sur la carte Gali VII


	U2MODEbits.UARTEN = 1;	// And turn the peripheral on

	U2STAbits.UTXEN = 1;
}
// Récupérer un caractère
unsigned char uartGetChar()
{
	while(U2STAbits.URXDA == 0);
	return (unsigned char)U2RXREG;
}

// Envoyer un caractère avec l'uart
void uartSendChar(const unsigned char c)
{
	while(U2STAbits.UTXBF == 1); // Wait until buffer is full
	U2TXREG = c;                 // Buffer the char to send
}

// Attendre la fin de la transmission
void uartWaitEndOfTransmission()
{
	while(U2STAbits.TRMT == 0);
}

// Interruption lors de la réception d'un caractère
void __attribute__((__interrupt__,auto_psv)) _U2TXInterrupt(void)
{
    //Ressources
    char c;

    if(U2STAbits.OERR)
    {
        U2STAbits.OERR = 0;
    }

    c = (char) uartGetChar();// On recupère le caractère

    recievedChar = c; // On recopie le char dans la variable

    IFS1bits.U2TXIF = 0; // Clear TX Interrupt flag
}



