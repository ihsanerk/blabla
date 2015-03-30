#include "leds.h"



void ledsInit() {
    //Initialisation des leds
    /*TRISDbits.TRISD6=0; //Led 0
    TRISDbits.TRISD5=0; //Led 1
    TRISDbits.TRISD4=0; //Led 2
    TRISDbits.TRISD13=0;//Led 3
    TRISDbits.TRISD12=0;//Led 4
    TRISDbits.TRISD3=0; //Led 5
    TRISDbits.TRISD2=0; //Led 6
    TRISDbits.TRISD1=0; //Led 7
     */
    
    TRISAbits.TRISA0=0;
    TRISAbits.TRISA1=0;
    TRISAbits.TRISA2=0;
    TRISAbits.TRISA3=0;
    TRISAbits.TRISA4=0;
    TRISAbits.TRISA5=0;
    TRISAbits.TRISA6=0;
    TRISAbits.TRISA7=0;
    
    //Eteindre les leds
    led0=0;
    led1=0;
    led2=0;
    led3=0;
    led4=0;
    led5=0;
    led6=0;
    led7=0;


    
}

void ledSet(uint8 led, BOOL state) {
    switch (led) {
        case 0:
            led0=state;
            break;
        case 1:
            led1=state;
            break;
        case 2:
            led2=state;
            break;
        case 3:
            led3=state;
            break;
        case 4:
            led4=state;
            break;
        case 5:
            led5=state;
            break;
        case 6:
            led6=state;
            break;
        case 7:
            led7=state;
            break;
        default:
            break;
    }
}

void ledToggle(uint8 led) {
    switch (led) {
        case 0:
            led0=~led0;
            break;
        case 1:
            led1=~led1;
            break;
        case 2:
            led2=~led2;
            break;
        case 3:
            led3=~led3;
            break;
        case 4:
            led4=~led4;
            break;
        case 5:
            led5=~led5;
            break;
        case 6:
            led6=~led6;
            break;
        case 7:
            led7=~led7;
            break;
        default:
            break;
    }
}

void ledSetAll(uint8 value) {
    ledSet(0, value & 0b00000001);
    ledSet(1, value & 0b00000010);
    ledSet(2, value & 0b00000100);
    ledSet(3, value & 0b00001000);
    ledSet(4, value & 0b00010000);
    ledSet(5, value & 0b00100000);
    ledSet(6, value & 0b01000000);
    ledSet(7, value & 0b10000000);
}

