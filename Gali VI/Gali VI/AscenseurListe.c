//Libraries
#include "AscenseurListe.h"

//Variables
ListeAscen listeAscen [2];
Ascenseur ascenseur [2];

// Initialisation
void listesAscenInit()
{
	//	Initialisation des lisste
    listeAscen[0].begin = listeAscen[0].end = 0;
	listeAscen[1].begin = listeAscen[1].end = 0;
	
	//	Chargement des ordres
	int8 i = 0;
	for (i = 0; i < 2; i++)
		chargementAscenOrdres(i);
}

//	Chargement des ordres
void chargementAscenOrdres(int8 liste)
{
	//	Ordre de base
	int8 i = 0;
	
	// Ordre buffer
	addAscenOrdre (0, TRUE, liste);
	
	for (i = 0; i < 3; i++)
	{
		addAscenOrdre (FERMER_PINCE, FALSE, liste);
		addAscenOrdre (OUVRIRE_TUNNEL_PEU, FALSE, liste);
		addAscenOrdre (MONTER, FALSE, liste);
		addAscenOrdre (FERMER_TUNNEL, FALSE, liste);
		addAscenOrdre (OUVRIRE_PINCE, FALSE, liste);
		addAscenOrdre (DESCENDRE, TRUE, liste);
	}
	
	addAscenOrdre (FERMER_PINCE, TRUE, liste);

	//	Ouvrir le tunnel
	
	// Moins de 4 verres
	addAscenOrdre (MONTER, FALSE, liste);
	addAscenOrdre (FERMER_PINCE, FALSE, liste);
	addAscenOrdre (OUVRIRE_TUNNEL_PEU, FALSE, liste);
	addAscenOrdre (DESCENDRE, FALSE, liste);
	addAscenOrdre (OUVRIRE_PINCE, FALSE, liste);
	
	// 4 verres
	addAscenOrdre (OUVRIRE_TUNNEL, FALSE, liste);
	addAscenOrdre (OUVRIRE_PINCE, TRUE, liste);
	
	addAscenOrdre (MONTER, FALSE, liste);
	addAscenOrdre (FERMER_PINCE, FALSE, liste);
	addAscenOrdre (FERMER_TUNNEL, TRUE, liste);
}

void addAscenOrdre (ActionAscen action, bool endSequence, int8 liste)
{
	//Si la liste n'est pas pleine
	if (! listeAscenIsFull(liste))
	{
		//Créer un nouvel ordre
		listeAscen[liste].ordres[listeAscen[liste].end].action = action;
		listeAscen[liste].ordres[listeAscen[liste].end].endSequence = endSequence;
		
		//Augmenter la taille de la liste
		listeAscen[liste].end = (listeAscen[liste].end+1)%MAX_ORDRES_ASCEN;
	}
	
	//Allumer LED d'erreur
	else LED4 = 1;
}	

//Vérifie si la liste est pleine ou non
bool listeAscenIsFull (int8 liste)
{
	if ((listeAscen[liste].end+1)%MAX_ORDRES_ASCEN == listeAscen[liste].begin)
		return TRUE;
		
	else return FALSE;
}

//Vérifie si la liste est vide ou non
bool listeAscenIsEmpty (int8 liste)
{
	if (listeAscen[liste].end == listeAscen[liste].begin)
		return TRUE;
		
	else return FALSE;
}

void getNextAscenOrdre (int8 liste)
{		
	//Avancer dans la liste
	listeAscen[liste].begin = (listeAscen[liste].begin+1)%MAX_ORDRES_ASCEN;
	ascenseur[liste].ordreFini = FALSE;
	ascenseur[liste].timer = millis;
	ascenseur[liste].ordreEnvoye = FALSE;
}
