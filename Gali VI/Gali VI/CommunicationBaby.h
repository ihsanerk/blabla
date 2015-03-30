#ifndef COMMUNICATIONBABY_H_INCLUDED
#define COMMUNICATIONBABY_H_INCLUDED

//Libraries
#include "Definitions.h"

//Pines

//Structures
typedef struct _Robot
{
	int32 			x;
	int32 			y;
	
}Robot;

//Prototypes
void				communicationBabyInit();
void 				xbeeInit();

void 				xbeeUartSendChar(const unsigned char c);
void 				xbeeSendString (char* string);
void 				xbeeSendUnSignedInteger (uint32 n);
uint8 				xbeeUartGetInt();
bool 				getPositionBaby ();
void 				sendPositionGali (uint16 x, uint16 y);

//Variables
extern Robot 		baby_Gali;

#endif // COMMUNICATIONBABY_H_INCLUDED
