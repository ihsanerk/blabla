#ifndef IA_H_INCLUDED
#define IA_H_INCLUDED

//Libraries
#include "Definitions.h"

#include "Debugger.h"
#include "Uart.h"
#include "AX12.h"

#include "AsservissementListe.h"
#include "Ascenseur.h"

#include "DetectionTourelle.h"
#include "DetectionSharp.h"
#include "CommunicationBaby.h"

#include "Bras.h"
#include "Balise.h"

#include "IAListe.h"

//Constante

//Enumérations

// Structures

// Prototypes
void 				start ();

void 				intitialisation (SequenceType sequence);
void 				oscillatorInit();
void 				timerInit ();
void 				jackInit ();

inline void 		intelligenceArtificielle ();
void 				updatePosition ();
void 				calculateurDeTrajectoire (int32 x, int32 y, int32 angle);	
void 				recalage ();
void 				intelligenceArtificielleInit(SequenceType sequence);

void 				gestionnaireBlocage ();	
void 				afterDetection (int8 ret);

void 				getPositionEnnemi ();
bool 				horsTerrain (bool side);
bool 				sharpOff ();
bool				isBabyGali ();
void 				analyseTerrain (uint16 x, uint16 y);
inline void         asservissement(bool circulaire);

void 				algoVerres ();
void 				algoCerises ();

// Variable
extern Robot ennemi;

#endif // IA_H_INCLUDED
