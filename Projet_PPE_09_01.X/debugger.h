#ifndef DEBUGGER_H
#define	DEBUGGER_H

//Librairies
#include "configuration.h"


//Prototypes
void debugger_init();
void sendString (char* string);
void sendSignedInteger (long n);
void sendUnSignedInteger (long n);


#endif	/* DEBUGGER_H */

