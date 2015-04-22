/* 
 * File:   actionneur.h
 * Author: user
 *
 * Created on 22 avril 2015, 11:36
 */

#ifndef ACTIONNEUR_H
#define	ACTIONNEUR_H

#include "math.h"
#include "debugger.h"

//Pins A MODIFIER
#define RXENABLE 	LATAbits.LATA7
#define TXENABLE 	LATAbits.LATA6


// Prototypes
void 		ax12Init ();
void 		servoChinoisInit (uint8 id);

void 		ax12SetMode (BOOL mode);
void 		ax12SendChar(uint8 c, int8 * checksum);
void 		ax12Execute (int32 goal, uint8 id, BOOL ax12);
void 		ax12Test ();

void 		ax12UartSendChar(uint8 c);
void 		ax12WaitEndOfTransmission();
uint8 		ax12GetChar();
void 		ax12DisableTorque (uint8 id);


#endif	/* ACTIONNEUR_H */

