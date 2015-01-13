//Librairies
#include "uart.h"

//RESSOURCES
char recievedChar;

// Programme d'initialisation des Pin
void uart_init()
{
    RPINR27bits.U3RXR = 62;
    //RPOR15bits.RP127R = 27;
    //Initialisation du Ramaping
    U3MODEbits.UARTEN  = 0;     // Disable UART
    U3MODEbits.ABAUD   = 0;     // Auto-Baud Disabled
    U3MODEbits.PDSEL   = 0b00;  // 8 bit, no parity
    U3MODEbits.STSEL   = 0;     // One stop bit
    U3MODEbits.BRGH    = 1;     // 0 = Mode which works ou BRGH = 1 : mode rapide : XBee

    //BRGH = 1 : mode rapide : XBee ou FT232 BRGH =0 : mode lent FT232
    //BAUD Rate Setting (formula 19-2 from dsPIC33F Family datasheet)
    //+2 for bug correction (FT232) +5 (xbee) en mode rapide
	U3BRG = BRGVAL;                // 207 = 9600 bauds

    // Rx interrupt
    U3STAbits.URXISEL  = 0b00;  // On each char
    IFS5bits.U3RXIF    = 0;     // Clear interrupt flag
    IEC5bits.U3RXIE    = 1;     // Enable interrupt
    IPC20bits.U3RXIP    = 0b110; // Interruption level TODO: set good level

    // Tx interrupt
    IEC5bits.U3TXIE    = 0;      // Disable interrupt

    // Enable UART
    U3MODEbits.UARTEN  = 1;      // Enable UART
    U3STAbits.UTXEN    = 1;      // Enable UART Tx
}
// Récupérer un caractère
unsigned char uartGetChar()
{
	while(U3STAbits.URXDA == 0);
	return (unsigned char)U3RXREG;
}

// Envoyer un caractère avec l'uart
void uartSendChar(const unsigned char c)
{
	while(U3STAbits.UTXBF == 1); // Wait until buffer is full
	U3TXREG = c;                 // Buffer the char to send
}

// Attendre la fin de la transmission
void uartWaitEndOfTransmission()
{
	while(U3STAbits.TRMT == 0);
}

// Interruption lors de la réception d'un caractère
void __attribute__((__interrupt__,auto_psv)) _U3TXInterrupt(void)
{
    //Ressources
    char c;

    if(U3STAbits.OERR)
    {
        U3STAbits.OERR = 0;
    }

    c = (char) uartGetChar();// On recupère le caractère

    recievedChar= c; // On recopie le char dans la variable

    IFS5bits.U3TXIF = 0; // Clear TX Interrupt flag
}

