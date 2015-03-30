#ifndef ASCENSEUR_H_INCLUDED
#define ASCENSEUR_H_INCLUDED

//Libraries
#include "Definitions.h"
#include "AscenseurListe.h"
#include "AX12.h"

//	Constantes
#define OUVRIRE_PINCE_DROITE			320
#define FERMER_PINCE_DROITE				135//145
#define OUVRIRE_PINCE_GAUCHE			350
#define FERMER_PINCE_GAUCHE				540

#define OUVRIRE_TUNNEL_DROIT			445
#define FERMER_TUNNEL_DROIT				180//197
#define OUVRIRE_TUNNEL_GAUCHE			313
#define FERMER_TUNNEL_GAUCHE			510 //528

#define OUVRIRE_TUNNEL_DROIT_PEU		270
#define OUVRIRE_TUNNEL_GAUCHE_PEU		410

#define MONTER_PINCE_DROITE				1023
#define DESCENDRE_PINCE_DROITE			729//450

#define MONTER_PINCE_GAUCHE				0
#define DESCENDRE_PINCE_GAUCHE			290//265
	

//	Structures

//	Prototypes
void 				ascenseurInit ();
inline void 		ascenseurProcess(int8 liste);

//	Variables
extern	uint32 timerIA;
extern	bool recup;

#endif // ASCENSEUR_H_INCLUDED
