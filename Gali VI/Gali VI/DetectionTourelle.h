#ifndef DETECTIONTOURELLE_H_INCLUDED
#define DETECTIONTOURELLE_H_INCLUDED

//Libraries
#include "Definitions.h"

//Pins

//Constante

//Enumérations

// Structures
typedef struct _RobotDetecte
{
	int32 			angleRelatif;
	int32 			distanceRelative;
	
}RobotDetecte;

// Prototypes
void 		detectionTourelleInit ();

void 		tourelleUartInit ();
void 		tourelleUartSendChar(const unsigned char c);

bool 		detectionTourelleProcess ();
bool 		getPositionRelativeEnnemi ();
uint8 		tourelleUartGetInt();

// Variable
extern RobotDetecte 		robot;

#endif // DETECTIONTOURELLE_H_INCLUDED
