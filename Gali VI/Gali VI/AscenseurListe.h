#ifndef ASCENSEURLISTE_H_INCLUDED
#define ASCENSEURLISTE_H_INCLUDED

//	Libraries
#include "Definitions.h"

//	Constant
#define MAX_ORDRES_ASCEN 32

//	Enumeration
typedef enum  {MONTER, DESCENDRE, OUVRIRE_PINCE, FERMER_PINCE, OUVRIRE_TUNNEL, FERMER_TUNNEL, OUVRIRE_TUNNEL_PEU} ActionAscen;

//	Structures
typedef struct _OrdreAscen
{
	ActionAscen 	action;
	bool 			endSequence;

}OrdreAscen;

typedef struct _ListeAscen
{
	int32 			begin;
	int32 			end;

    OrdreAscen   	ordres [MAX_ORDRES_ASCEN];

}ListeAscen;

typedef struct _Ascenseur
{
	bool	ordreFini;
	int32 	verres;	//	Nombre de verres dans l'ascenseur
	bool	ouvert; //	FALSE fermé et TRUE ouvert
	bool 	tunnelActif;
	bool	ordreEnvoye;
	
	uint32 	timer;

}Ascenseur;

//	Prototypes
void 		chargementAscenOrdres(int8 liste);
void 		listesAscenInit();

void 		addAscenOrdre (ActionAscen action, bool endSequence, int8 liste);
bool 		listeAscenIsFull (int8 liste);
bool 		listeAscenIsEmpty (int8 liste);
void 		getNextAscenOrdre (int8 liste);

//	Variables
extern ListeAscen listeAscen [2];
extern 				Ascenseur ascenseur [2];

#endif // LISTEASCENSEUR_H_INCLUDED
