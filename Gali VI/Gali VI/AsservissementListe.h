#ifndef ASSERVISSEMENTLISTE_H_INCLUDED
#define ASSERVISSEMENTLISTE_H_INCLUDED

//Libraries
#include "Definitions.h"
#include "Asservissement.h"
#include "Bras.h"

//Pines

//Constante
#define MAX_ORDRES_ASSER 100

//Enumérations
typedef enum  {AVANCE, ROTATION, RECALAGE_1, RECALAGE_2, CERCLE} OrdreType;

//Structures
typedef struct _OrdreAsser
{
	OrdreType   type         ;//Type d'action: voir plus haut
	int32 		valeur		 ;//Valeur de l'ordre en centimètre ou radian
	
}OrdreAsser;

typedef struct _ListeAsser
{
    int32         begin   ;//Position du premier élément (élément courant)
    int32         end     ;//Position du denrier élément
	bool		  empty	  ;//Permet de gérer la synchronisation avec l'IA

    OrdreAsser   	ordres[MAX_ORDRES_ASSER];//Liste des ordres

}ListeAsser;

typedef struct _Gali
{
	int32 	x; //En mm
	int32 	y;
	int32 	angle;//Angle en millième de radian (PI = 3141)
	
}Gali;

//Prototypes
void 			addAsserOrdre (OrdreType type, int32 value);
bool 			listeAsserIsFull ();
bool 			listeAsserIsEmpty ();
void 			listeAsserInit();
void 			getNextAsserOrdre ();
void 			cleanAsserListe ();

inline void 		gestionnaireOrdres();
inline void 		nouvelOrdre ();
int32 				getLastOrder ();

void 				updatePosition ();
void 				updateCurrentPosition ();

//Variables
extern Gali 				gali;
extern Gali 				currentGali;
extern ListeAsser 			listeAsser;

#endif // ASCENSEURLISTE_H_INCLUDED
