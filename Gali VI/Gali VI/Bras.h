#ifndef BRAS_H_INCLUDED
#define BRAS_H_INCLUDED

//Libraries
#include "Definitions.h"
#include "AX12.h"

//Pins

//Constante
#define BRAS_HAUT_RANGE					141
#define BRAS_HAUT_BAISSE				400
#define BRAS_HAUT_LEVE					446

#define BRAS_BAS_RANGE					688
#define BRAS_BAS_SEMI_RANGE				530
#define BRAS_BAS_BAISSE					340
#define BRAS_BAS_LEVE					500


// Structures

// Prototypes
void 		brasInit ();
void 		brasProcess(int32 droite, int32 gauche);
void 		brasBaisses ();
void 		brasOuverture ();
void 		brasFermeture ();

// Variable

#endif // BRAS_H_INCLUDED
