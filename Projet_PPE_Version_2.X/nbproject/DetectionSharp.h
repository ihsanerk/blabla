
#ifndef DETECTIONSHARP_H_INCLUDED
#define DETECTIONSHARP_H_INCLUDED
//Libraries
#include "./../moteur.h"
#include "math.h"
// Structures



//// Variable
//extern GestionnaireACD			gestionnaireACD [2];
//extern Blocage					blocage;


//Constante
#define NB_SHARP    2
#define NB_SAMPLE   6

//Enumérations





// Prototypes
void 				detectionSharpInit ();
void 				sharpTimerInit();
int 				detectionSharpProcess (BOOL sens);
inline uint16                   getSharp(int8 id);
BOOL 				detectionSharpObstacle (BOOL sens);
BOOL 				detectionSharpObstacleSide (BOOL sens, BOOL side);



#endif // DETECTIONSHARP_H_INCLUDED
