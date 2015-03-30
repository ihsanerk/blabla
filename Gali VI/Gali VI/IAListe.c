// Library
#include "IAListe.h"

//	Variables
ListeIA listeIA;


// Initialisation
void listeIAInit(SequenceType sequence)
{
	// Initialise la liste
    listeIA.begin = listeIA.end = 0;
	listeIA.sequence = sequence;
	
	listeIA.lastOrderSucceded = TRUE;
	listeIA.lastOrderBlocked = FALSE;
		
	listeIA.active = TRUE;
	
	// Charge la stratégie correspondante
	strategie ();
}

// Stratégies
void strategie ()
{
	switch (listeIA.sequence)
	{	
		case SEQUENCE_VERRES: 
							sequenceVerres ();
							break;
							
		case SEQUENCE_CERISES: 
							sequenceCerises ();
							break;
							
		case SEQUENCE_BOUGIES: 
							sequenceBougies ();
							break;

		case SEQUENCE_HOMOLOGATION: 
							sequenceHomologation ();
							break;
		
		default://Bug
							break;
	}
}

// Passer au prochain ordre
void getNextIAOrdre ()
{
	// Si le dernier ordre a réussi
	if (listeIA.lastOrderSucceded)
		listeIA.begin = (listeIA.begin + listeIA.ordres[listeIA.begin].goIfSuccess)%MAX_ORDRES_IA;
	
	// Sinon
	else 
	{
		listeIA.begin = (listeIA.begin + listeIA.ordres[listeIA.begin].goIfFail)%MAX_ORDRES_IA;
		listeIA.lastOrderSucceded = TRUE;
	}
}

void addIAOrdre (int32 x, int32 y, int32 angle, bool canonOn, bool turbineOn, bool tunnelOn, bool asserCercleOn, bool interSequenceOn, int32 goIfFail, int32 goIfSuccess)
{
	//Créer un nouvel ordre
	listeIA.ordres[listeIA.end].x = x;
	listeIA.ordres[listeIA.end].y = y;	
	listeIA.ordres[listeIA.end].angle = angle;
		
	listeIA.ordres[listeIA.end].canonOn = canonOn;
	listeIA.ordres[listeIA.end].turbineOn = turbineOn;
	listeIA.ordres[listeIA.end].tunnelOn = tunnelOn;	
	listeIA.ordres[listeIA.end].asserCercleOn = asserCercleOn;
	listeIA.ordres[listeIA.end].interSequenceOn = interSequenceOn;
	
	listeIA.ordres[listeIA.end].goIfFail = goIfFail;
	listeIA.ordres[listeIA.end].goIfSuccess = goIfSuccess;
	
	//Augmenter la taille de la liste
	listeIA.end = (listeIA.end+1)%MAX_ORDRES_IA;
}

bool listeIAIsEmpty ()
{
	if (listeIA.end == listeIA.begin)
		return TRUE;
		
	else return FALSE;
}

// Première séquence de jeu
void sequenceHomologation ()
{
	// x, y, angle, canon, tunnel, asservissement circulaire, ifFail, ifSuccess	
	addIAOrdre (400, 1025, 0, FALSE, FALSE, FALSE, FALSE, FALSE, 1, 1);
	addIAOrdre (900, 1300, 0, FALSE, FALSE, FALSE, FALSE, FALSE, 1, 1);
	addIAOrdre (1300, 1050, 1000, FALSE, FALSE, FALSE, FALSE, FALSE, 1, 1);
	addIAOrdre (300, 1050, 1000, FALSE, FALSE, FALSE, FALSE, FALSE, 1, 1);
	addIAOrdre (600, 1050, 1000, FALSE, FALSE, FALSE, FALSE, FALSE, 1, 1);
}

// Première séquence de jeu
void sequenceVerres ()
{
	// x, y, angle, canon, tunnel, asservissement circulaire, ifFail, ifSuccess	
	addIAOrdre (400, 1025, 0, FALSE, FALSE, FALSE, FALSE, FALSE, 1, 1);
	addIAOrdre (680, 1100, 0, FALSE, FALSE, FALSE, FALSE, FALSE, 7, 1);
	addIAOrdre (980, 1100, 0, FALSE, FALSE, FALSE, FALSE, FALSE, 5, 1);
	addIAOrdre (1580, 1100, 0, FALSE, FALSE, FALSE, FALSE, FALSE, 3, 1);
	addIAOrdre (1880, 1100, 0, FALSE, FALSE, FALSE, FALSE, FALSE, 2, 1);
	addIAOrdre (2170, 750, 1000, FALSE, FALSE, FALSE, FALSE, FALSE, 1, 1); 
	addIAOrdre (1870, 750, 1000, FALSE, FALSE, FALSE, FALSE, FALSE, 1, 1);
	addIAOrdre (1570, 750, 1000, FALSE, FALSE, FALSE, FALSE, FALSE, 1, 1);
	addIAOrdre (1270, 750, 1000, FALSE, FALSE, FALSE, FALSE, FALSE, 1, 1);
}

// Seconde séquence
void sequenceCerises ()
{
	// x, y, angle, canon, tunnel, asservissement circulaire, interséquence, ifFail, ifSuccess
	
	// Second
	addIAOrdre (600, 600, 1000, FALSE, FALSE, FALSE, FALSE, TRUE, 1, 1);
	//addIAOrdre (-2000, 800, 1000, FALSE, FALSE, FALSE, FALSE, FALSE, 1, 1);
	addIAOrdre (250, 600, 1000, FALSE, FALSE, TRUE, FALSE, FALSE, 1, 1);
	addIAOrdre (600, 600, -500, FALSE, FALSE, TRUE, FALSE, FALSE, 4, 1);

	// Third
	addIAOrdre (600, 1000, 1000, FALSE, FALSE, FALSE, FALSE, TRUE, 1, 1);
	//addIAOrdre (-2000, 800, 1000, FALSE, FALSE, FALSE, FALSE, FALSE, 1, 1);
	addIAOrdre (250, 1000, 1000, FALSE, FALSE, TRUE, FALSE, FALSE, 1, 1);
	addIAOrdre (600, 1000, -500, FALSE, FALSE, TRUE, FALSE, FALSE, 1, 1);
}

// Troisième séquence 
void sequenceBougies ()
{
    // x, y, angle, canon, ascenseur, asservissement circulaire, ifFail, ifSuccess
	addIAOrdre (805, 1200, -team*500, FALSE, FALSE, FALSE, FALSE, TRUE, 3, 1);
	addIAOrdre (-1000, -1000, -team*500, FALSE, FALSE, FALSE, FALSE, FALSE, 2, 1);
	addIAOrdre (0, 0, 0, FALSE, FALSE, FALSE, TRUE, FALSE, 1, 1); //Particulier car asservissement circulaire
}
