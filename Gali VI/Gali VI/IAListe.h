#ifndef IALISTE_H_INCLUDED
#define IALISTE_H_INCLUDED

//Libraries
#include "Definitions.h"

//Pins

//Constante
#define MAX_ORDRES_IA 100

//Enumérations
typedef enum  {SEQUENCE_RECALAGE = 0, SEQUENCE_VERRES = 1, SEQUENCE_CERISES = 2, SEQUENCE_BOUGIES = 3, SEQUENCE_HOMOLOGATION = 8} SequenceType;

// Structures
typedef struct _OrdreIA
{
	int32	x;
	int32	y;
	int32	angle;//Angle en millième de radian (PI = 3141)
	
	bool	canonOn;
	bool	tunnelOn;
	bool 	turbineOn;
	bool	asserCercleOn; //Activer le thread controlant les bras en même temps
	bool	interSequenceOn;
	
	int32	goIfFail;
	int32	goIfSuccess;
	
}OrdreIA;

typedef struct _ListeIA
{
	SequenceType sequence;
	bool active;	
	bool lastOrderSucceded;
	bool lastOrderBlocked;
	
	int32 begin;
	int32 end;
	
	OrdreIA ordres [MAX_ORDRES_IA];
	
}ListeIA;

// Prototypes
void 		listeIAInit();
void 		addIAOrdre (int32 x, int32 y, int32 angle, bool turbineOn, bool canonOn, bool tunnelOn, bool asserCercleOn, bool interSequenceOn, int32 goIfFail, int32 goIfSuccess);
bool 		listeIAIsEmpty ();
void 		getNextIAOrdre ();

void 		sequenceVerres ();
void 		sequenceCerises ();
void 		sequenceBougies ();
void 		sequenceHomologation ();

void 		strategie ();

// Variable
extern ListeIA 		listeIA;  

#endif // IALISTE_H_INCLUDED
