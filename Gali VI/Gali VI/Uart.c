// Librarie
#include "Uart.h"

//Variables
char recievedChar;

// Intialise l'uart
void uartInit()
{
	RPINR18bits.U1RXR = 109; //Remaping RxPin to RP108
	RPOR11bits.RP108R = 1; // Remaping RP109 to TxPin

	U1MODEbits.UARTEN  = 0;     // Disable UART
    U1MODEbits.ABAUD   = 0;     // Auto-Baud Disabled
    U1MODEbits.PDSEL   = 0b00;  // 8 bit, no parity
    U1MODEbits.STSEL   = 0;     // One stop bit
    U1MODEbits.BRGH    = 0;     // 0 = Mode which works

    //BRGH = 1 : mode rapide : XBee ou FT232 BRGH =0 : mode lent FT232
    //BAUD Rate Setting (formula 19-2 from dsPIC33F Family datasheet)
    //+2 for bug correction (FT232) +5 (xbee) en mode rapide
	U1BRG = FINAL_BAUD;                // 207 = 9600 bauds

    // Rx interrupt
    U1STAbits.URXISEL  = 0b00;  // On each char
    IFS0bits.U1RXIF    = 0;     // Clear interrupt flag
    IEC0bits.U1RXIE    = 1;     // Enable interrupt
    IPC2bits.U1RXIP    = 0b110; // Interruption level TODO: set good level

    // Tx interrupt
    IEC0bits.U1TXIE    = 0;      // Disable interrupt

    // Enable UART
    U1MODEbits.UARTEN  = 1;      // Enable UART
    U1STAbits.UTXEN    = 1;      // Enable UART Tx
}


// Récupérer un caractère
unsigned char uartGetChar()
{
	while(U1STAbits.URXDA == 0);
	return (unsigned char)U1RXREG;
}


// Envoyer un caractère avec l'uart
void uartSendChar(const unsigned char c)
{
	while(U1STAbits.UTXBF == 1); // Wait until buffer is full
	U1TXREG = c;                 // Buffer the char to send
}


// Attendre la fin de la transmission
void uartWaitEndOfTransmission()
{
	while(U1STAbits.TRMT == 0);
}


// Interruption lors de la réception d'un caractère
void __attribute__((__interrupt__, auto_psv)) _U1RXInterrupt(void)
{
	char c;

	if(U1STAbits.OERR)
	{
		U1STAbits.OERR = 0;
	}
	
	c = (char)uartGetChar();
	
    recievedChar = c;
	
	IFS0bits.U1RXIF = 0;
}
