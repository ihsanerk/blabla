#ifndef BALISE_H_INCLUDED
#define BALISE_H_INCLUDED

//Libraries
#include "Definitions.h"

//Pins

//Constante

//Enumérations

// Structures
typedef struct _Balise
{
	uint32 	 timer;
	int8	 bougies [20];
	int16 	 compteur;

}Balise;

// Prototypes
void 		baliseInit ();
void 		uartBaliseInit();
void 		bluetoothInit ();

void 		baliseUartSendChar(const unsigned char c);
void 		baliseUartSendSeq(const char * c, int i);

// Variable
extern Balise balise;


#endif // BALISE_H_INCLUDED
