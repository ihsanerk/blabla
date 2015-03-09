#ifndef ASSERVISSEMENTLISTE_H_INCLUDED
#define ASSERVISSEMENTLISTE_H_INCLUDED

//Libraries
#include "math.h"
#include "asservissement.h"

//Pines

//Constante
#define MAX_ORDRES_ASSER 100

//Enum»rations

typedef enum {
    AVANCE, ROTATION, RECALAGE_1, RECALAGE_2, CERCLE
} OrdreType;

//Structures

typedef struct _OrdreAsser {
    OrdreType type; //Type d'action: voir plus haut
    int32 valeur; //Valeur de l'ordre en centimÀtre ou radian

} OrdreAsser;

typedef struct _ListeAsser {
    int32 begin; //Position du premier »l»ment (»l»ment courant)
    int32 end; //Position du denrier »l»ment
    bool empty; //Permet de g»rer la synchronisation avec l'IA

    OrdreAsser ordres[MAX_ORDRES_ASSER]; //Liste des ordres

} ListeAsser;

typedef struct _Gali {
    int32 x; //En mm
    int32 y;
    int32 angle; //Angle en milliÀme de radian (PI = 3141)

} Gali;

//Prototypes
void addAsserOrdre(OrdreType type, int32 value);
bool listeAsserIsFull();
bool listeAsserIsEmpty();
void listeAsserInit();
void getNextAsserOrdre();
void cleanAsserListe();

inline void gestionnaireOrdres();
inline void nouvelOrdre();
int32 getLastOrder();

void updatePosition();
void updateCurrentPosition();

//Variables
extern Gali gali;
extern Gali currentGali;
extern ListeAsser listeAsser;

#endif // ASCENSEURLISTE_H_INCLUDED
