//Librairies
#include "uart.h"

//RESSOURCES
char recievedChar;

// Programme d'initialisation des Pin
void uart_init()
{
    RPINR19bits.U2RXR = 0b1100100;// On assigne au pin 49 le resgistre RX de U2
    RPOR9bits.RP101R = 3;// 3 :U2TX 27 : U3TX
    //Initialisation du Ramaping
    U2MODEbits.UARTEN  = 0;     // Disable UART
    U2MODEbits.ABAUD   = 0;     // Auto-Baud Disabled
    U2MODEbits.PDSEL   = 0b00;  // 8 bit, no parity
    U2MODEbits.STSEL   = 0;     // One stop bit
    U2MODEbits.BRGH    = 1;     // 0 = Mode which works ou BRGH = 1 : mode rapide : XBee

    //BRGH = 1 : mode rapide : XBee ou FT232 BRGH =0 : mode lent FT232
    //BAUD Rate Setting (formula 19-2 from dsPIC33F Family datasheet)
    //+2 for bug correction (FT232) +5 (xbee) en mode rapide
	U3BRG = BRGVAL;                // 207 = 9600 bauds

    // Rx interrupt
    U2STAbits.URXISEL  = 0b00;  // On each char
    IFS1bits.U2RXIF    = 0;     // Clear interrupt flag
    IEC1bits.U2RXIE    = 0;     // Enable interrupt
    IPC7bits.U2RXIP    = 4; // Interruption level TODO: set good level

    // Tx interrupt
    IEC1bits.U2TXIE    = 1;      // Enable interrupt

    // Enable UART
    U2MODEbits.UARTEN  = 1;      // Enable UART
    U2STAbits.UTXEN    = 1;      // Enable UART Tx
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

