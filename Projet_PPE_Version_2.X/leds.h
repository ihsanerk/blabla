#ifndef LEDS_H
#define	LEDS_H

//Librairies
#include <stdbool.h>
#include <stdint.h>
#include "bits.h"

// Pin configuration
//Pour Carte Gali
/*
#define led0 TRISDbits.TRISD6
#define led1 TRISDbits.TRISD5
#define led2 TRISDbits.TRISD4
#define led3 TRISDbits.TRISD13
#define led4 TRISDbits.TRISD12
#define led5 TRISDbits.TRISD3
#define led6 TRISDbits.TRISD2
#define led7 TRISDbits.TRISD1
 */

//Pour l'explorer 16
#define led0 TRISAbits.TRISA0
#define led1 TRISAbits.TRISA1
#define led2 TRISAbits.TRISA2
#define led3 TRISAbits.TRISA3
#define led4 TRISAbits.TRISA4
#define led5 TRISAbits.TRISA5
#define led6 TRISAbits.TRISA6
#define led7 TRISAbits.TRISA7

void ledsInit();
void ledSet(uint8 led, BOOL state);
void ledToggle(uint8 led);
void ledSetAll(uint8 value);

#endif	/* LEDS_H */

