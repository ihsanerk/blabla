#ifndef DEBUGGER_H
#define	DEBUGGER_H

//Librairies
#include "configuration.h"
#include <stdio.h>
#include <stdarg.h>


//Prototypes
void debugger_init();
void sendString (char* string);
void sendSignedInteger (long n);
void sendUnSignedInteger (long n);

void StringFormatted(const char *fmt, ...);

#endif	/* DEBUGGER_H */

