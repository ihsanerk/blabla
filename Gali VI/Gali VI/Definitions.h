#ifndef DEFINITIONS_H_INCLUDED
#define DEFINITIONS_H_INCLUDED



//TRANSLATORS FUNCTIONS
int16 parseInt16            (char **);
int32 parseInt32            (char **);
void allumerLeds            (int8 data);

//Variables communes
extern uint32 				millis;
extern int8					team;

//LUT
extern int16	asinLUT [2001]; 
extern int16	sinLUT [2001]; 
extern int16	cosLUT [2001]; 

//Outils de debug
#include "Debugger.h"

#endif // DEFINITIONS_H_INCLUDED
