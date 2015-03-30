#ifndef DEBUGGER_H
#define	DEBUGGER_H

//Librairies
#include "configuration.h"
#include <stdio.h>
#include <stdarg.h>
#include "leds.h"

//Prototypes
void debugger_init();
void sendString (char* string);
void sendSignedInteger (long n);
void sendUnSignedInteger (long n);

void StringFormatted(const char *fmt, ...);

void envoyer_message(int CodeurDroit,int CodeurGauche,char c);

#endif	/* DEBUGGER_H */

