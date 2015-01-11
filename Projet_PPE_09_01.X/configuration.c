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
    RPINR27bits.U3RXR=0b01100010; // 111 1111
    RPOR15bits.RP127R=0b00100111; //  11 1111
}