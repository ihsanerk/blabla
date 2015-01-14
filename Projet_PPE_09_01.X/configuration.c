//Librairies
#include "configuration.h"

void pinConfiguration ()
{
    //Définition des Pins

    // Disable ADC
    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;
    ANSELD = 0;
    ANSELE = 0;
    ANSELG = 0;

    //UART3 : Débug
    // Registre 27 du UART3 Receive, les bits de data pour recevoir
    //RPINR1bits.U3RXR=0b01100010; // 111 1111
    //RPOR15bits.RP127R=0b00100111; //  11 1111
}

void oscillatorInit() {
    // The settings below set up the oscillator and PLL for 40 MIPS as
    // follows:
    //               Crystal Frequency * (PLLFBD+2)
    //       Fcy =  ----------------------------
    //                       2 * N1 * N2
    // Configure Oscillator to operate the device at 40Mhz
    // Fosc= Fin*M/(N1*N2), Fcy=Fosc/2
    // Fosc= 8M*40(2*2)=80Mhz for 8M input clock
    PLLFBD=32; // M=40
    CLKDIVbits.PLLPOST=0; // N1=2
    CLKDIVbits.PLLPRE=2; // N2=2
    OSCTUN=0; // Tune FRC oscillator, if FRC is used
    RCONbits.SWDTEN=0; // Disable Watch Dog Timer
    TRISF=0;
    INTCON2bits.GIE=1;
    IEC1bits.U2TXIE=1;
    



   //while(OSCCONbits.LOCK!=1) {}; // Wait for PLL to lock

}