
#ifndef DETECTIONSHARP_H_INCLUDED
#define DETECTIONSHARP_H_INCLUDED

//Libraries
#include "Definitions.h"

//Pins

//Constante
#define NB_SHARP    2
#define NB_SAMPLE   6

//Enumérations

// Structures
typedef struct _Blocage
{
	bool				actif;

	uint32				timerDetection;
	
	int32 				bufferErreur_1;
	int32				bufferErreur_2;
	
}Blocage;

typedef struct _GestionnaireACD
{
	int32 sampleIndex;  		
	int32 currentSharpIndex;
	
}GestionnaireACD;

// Prototypes
void 				detectionSharpInit ();
void 				sharpTimerInit();
int 				detectionSharpProcess (bool sens);
inline uint16 		getSharp(int8 id);
bool 				detectionSharpObstacle (bool sens);
bool 				detectionSharpObstacleSide (bool sens, bool side);

// Variable
extern GestionnaireACD			gestionnaireACD [2];
extern Blocage					blocage;


#endif // DETECTIONSHARP_H_INCLUDED
