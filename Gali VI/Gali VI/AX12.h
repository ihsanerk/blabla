#ifndef AX12_H_INCLUDED
#define AX12_H_INCLUDED

//Libraries
#include "Definitions.h"

//Pins
#define RXENABLE 	LATAbits.LATA7
#define TXENABLE 	LATAbits.LATA6

//Constante

//Enumérations

// Structures

// Prototypes
void 		ax12Init ();
void 		servoChinoisInit (uint8 id);

void 		ax12SetMode (bool mode);
void 		ax12SendChar(uint8 c, int8 * checksum);
void 		ax12Execute (int32 goal, uint8 id, bool ax12);
void 		ax12Test ();

void 		ax12UartSendChar(uint8 c);
void 		ax12WaitEndOfTransmission();
uint8 		ax12GetChar();
void 		ax12DisableTorque (uint8 id);

// Variable

#endif // AX12_H_INCLUDED
