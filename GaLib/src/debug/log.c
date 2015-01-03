#include "debug/log.h"

#include <stdarg.h>
#include <stdio.h>
#include <xc.h>

#include "debug/leds.h"

void uartWaitEndOfTransmission();

void logInit() {
    U3MODEbits.UARTEN = 0; // Disable UART
    U3MODEbits.ABAUD = 0; // Auto-Baud Disabled
    U3MODEbits.PDSEL = 0b00; // 8 bit, no parity
    U3MODEbits.STSEL = 0; // One stop bit

    //BRGH = 1 : mode rapide : XBee ou FT232 BRGH =0 : mode lent FT232
    //BAUD Rate Setting (formula 19-2 from dsPIC33F Family datasheet)
    //+2 for bug correction (FT232) +5 (xbee) en mode rapide
    U3MODEbits.BRGH = 0;
    U3BRG = 207; // 207 = 9600 bauds

    // Rx interrupt
    U3STAbits.URXISEL = 0b00; // On each char
    IFS5bits.U3RXIF = 0; // Clear interrupt flag
    IEC5bits.U3RXIE = 1; // Enable interrupt
    IPC20bits.U3RXIP = 0b110; // Interruption level TODO: set good level

    // Tx interrupt
    IEC5bits.U3TXIE = 0; // Enable interrupt

    // Enable UART
    U3MODEbits.UARTEN = 1; // Enable UART
    U3STAbits.UTXEN = 1; // Enable UART Tx
}

void logClose() {
    uartWaitEndOfTransmission();
    U3MODEbits.UARTEN = 0;
}

// Envoyer un caractère avec l'uart

void uartSendChar(const unsigned char c) {
    while (U3STAbits.UTXBF == 1); // Wait until buffer is full
    U3TXREG = c; // Buffer the char to send
}

// Récupérer un caractère

unsigned char uartGetChar() {
    while (U3STAbits.URXDA == 0);
    return (unsigned char) U3RXREG;
}

// Attendre la fin de la transmission

void uartWaitEndOfTransmission() {
    while (U3STAbits.TRMT == 0);
}

// Envoyer une chaine de caractère avec l'uart

void logString(const char *string) {
    unsigned char i;
    for (i = 0; string[i] != '\0'; i++)
        uartSendChar(string[i]);
}

void logStringFormatted(const char *fmt, ...) {
    char buffer[200];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, 200, fmt, args);
    va_end(args);
    logString(buffer);
}

// TODO: implement reception, and then remote configuration

char receivedChar;

// Interruption lors de la réception d'un caractère

void __attribute__((__interrupt__, auto_psv)) _U3RXInterrupt(void) {
    char c;

    if (U3STAbits.OERR) {
        U3STAbits.OERR = 0;
    }
    c = (char) uartGetChar();

    receivedChar = c;
    uartSendChar(receivedChar); // loopback test!

    IFS5bits.U3RXIF = 0;
}