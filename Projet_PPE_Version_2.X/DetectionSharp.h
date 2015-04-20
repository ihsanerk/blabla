#ifndef DETECTIONSHARP_H
#define	DETECTIONSHARP_H

//Librairies
#include "math.h"
#include "debugger.h"

//Constante
#define NB_SHARP 2
#define NB_SAMPLE 6

//Prototypes
void sharpTimerInit();
void detectionSharpInit ();
void adc_detection();
inline uint16 getSharp(int8 id);
int detectionSharpProcess (BOOL sens);
BOOL detectionSharpObstacle (BOOL sens);
BOOL detectionSharpObstacleSide (BOOL sens, BOOL side);

#endif	/* DETECTIONSHARP_H */

