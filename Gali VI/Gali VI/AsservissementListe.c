//Libraries
#include "AsservissementListe.h"

//Variables
Gali 			gali;
Gali 			currentGali;
ListeAsser 		listeAsser;
uint32 			timer = 0;
uint32 			timerRecalage = 0;
int8			team;

// Initialisation
void listeAsserInit()
{
	//	Initialise la liste
    listeAsser.begin = listeAsser.end = 0;
	listeAsser.empty = TRUE;
	
	//	Initialise l'asservissement
	asservissementInit ();
}

void addAsserOrdre (OrdreType type, int32 value)
{
	//Si la liste n'est pas pleine
	if (! listeAsserIsFull())
	{
		//Créer un nouvel ordre
		listeAsser.ordres[listeAsser.end].type = type;
		listeAsser.ordres[listeAsser.end].valeur = value;	
		
		//Augmenter la taille de la liste
		listeAsser.end = (listeAsser.end+1)%MAX_ORDRES_ASSER;
	}
}	

//Vérifie si la liste est pleine ou non
bool listeAsserIsFull ()
{
	if ((listeAsser.end+1)%MAX_ORDRES_ASSER == listeAsser.begin)
		return TRUE;
		
	else return FALSE;
}

//Vérifie si la liste est vide ou non
bool listeAsserIsEmpty ()
{
	if (listeAsser.end == listeAsser.begin)
		return TRUE;
		
	else return FALSE;
}

//Récupère le dernier ordre
int32 getLastOrder ()
{
	int32 lastOrder;

	if (listeAsser.begin == 0) lastOrder = listeAsser.ordres[MAX_ORDRES_ASSER - 1].valeur;
	else lastOrder = listeAsser.ordres[listeAsser.begin - 1].valeur;
	
	return lastOrder;
}

//Vérifie si la liste est vide ou non
void cleanAsserListe ()
{
	listeAsser.empty = TRUE;
	listeAsser.end = listeAsser.begin;
}

void getNextAsserOrdre ()
{	
	// Mettre à jour la position de Gali
	updatePosition ();
	
	//Avancer dans la liste
	listeAsser.begin = (listeAsser.begin+1)%MAX_ORDRES_ASSER;
	
	// Si elle n'est pas vide
	if (! listeAsserIsEmpty ())
		nouvelOrdre ();
		
	//	Sinon attendre
	else listeAsser.empty = TRUE;
}

inline void nouvelOrdre ()
{
	//	Dire qu'elle ne l'est plus
	listeAsser.empty = FALSE;

	// Selon le type d'ordre
	switch (listeAsser.ordres[listeAsser.begin].type)
	{
		case AVANCE:
					angle.ordre = 0;
					distance.erreur += ((int32)IMP_M*listeAsser.ordres[listeAsser.begin].valeur)/1000;
					angle.enable = TRUE;
					distance.enable = TRUE;
					distance.VMax = 1000;
					angle.VMax = 600;
					break;
		
		case ROTATION:
					distance.ordre = 0;
					angle.erreur += ((int32)IMP_T*listeAsser.ordres[listeAsser.begin].valeur)/2000;
					angle.enable = TRUE;
					distance.enable = TRUE;
					angle.VMax = 1000;
					distance.VMax = 600;
					break;
		
		case CERCLE:
					if (listeAsser.ordres[listeAsser.begin].valeur == 0)
					{
						roueGauche.erreur = (((int32)team*IMP_M*PI*470) / (2000));
						roueDroite.erreur = (((int32)team*IMP_M*PI*(470 + 250)) / (2000));
					}
					
					else 
					{
						brasBaisses ();
						roueGauche.erreur = 0;
						roueDroite.erreur = ((int32)team*8*IMP_T)/360;
					}
					break;
		
		case RECALAGE_1:
					angle.ordre = 0;
					distance.ordre = listeAsser.ordres[listeAsser.begin].valeur;
					angle.enable = FALSE;
					distance.enable = FALSE;
					timer = millis;
					break;
		
		case RECALAGE_2:
					distance.ordre = listeAsser.ordres[listeAsser.begin].valeur;
					angle.enable = TRUE;
					angle.VMax = 1000;
					distance.enable = FALSE;
					timer = millis;
					break;
	}f
}

inline void gestionnaireOrdres()
{
	// Selon le type d'ordre
	switch (listeAsser.ordres[listeAsser.begin].type)
	{
		case AVANCE:
					if((distance.ordre == 0) && (angle.ordre == 0))
						getNextAsserOrdre ();
					break;
		
		case ROTATION:
					if((distance.ordre == 0) && (angle.ordre == 0))
						getNextAsserOrdre ();
					break;
					
		case CERCLE:
					if((ABS(roueDroite.erreur) <= 50) && (ABS(roueGauche.erreur) <= 50))
					{
						applicationAssCirMoteurs(0, 0);
						getNextAsserOrdre ();
					}
					break;
				
		case RECALAGE_1: //	Mettre une autre valeure que erreurTolerance si nécessaire
					if( ((ABS(distance.variation)) < 5 ) && ((ABS(angle.variation)) < 5 ) && ((millis-timer) > 1000))
        
						if (millis-timerRecalage > 20)
						{
							//Mettre la consigne à 0	
							distance.ordre = 0;
							angle.ordre = 0;
							angle.erreur = 0;
							distance.erreur = 0;
							
							//Récupérer le prochain ordre
							getNextAsserOrdre ();
						}
					}
					
					else timerRecalage = millis;
					
					break;
					
		case RECALAGE_2: //	Mettre une autre valeur que erreurTolerance si nécessaire
					if( ((ABS(distance.variation)) < 5 ) && ((angle.ordre == 0) || ((ABS(angle.variation)) < 5 )) && ((millis-timer) > 1000))
					{
						if ((millis-timerRecalage > 20) || (angle.ordre == 0))
						{
							//Mettre la consigne à 0	
							distance.ordre = 0;
							angle.erreur = 0;
							distance.erreur = 0;
							
							//Récupérer le prochain ordre
							getNextAsserOrdre ();
						}
					}
					
					else timerRecalage = millis;
					
					break;
	}
}

void updatePosition ()
{
	// Angle
	int32 angleBuff = gali.angle;
	gali.angle += ((int32)team*angle.variationSomme *2000)/IMP_T;
	
	// Arrondir la valeur
	if ((((int32)angle.variationSomme *2000)%IMP_T) > (IMP_T/2)) gali.angle += team;
	
	//Calcule de l'angle moyen
	int32 angleMoyen = (gali.angle + angleBuff)/2;
	
	// Trouver l'angle moyen lissé
	if (angleMoyen <= - 2000) angleMoyen = angleMoyen%(-2000);
	else if (angleMoyen > 2000) angleMoyen = angleMoyen%(2000);
	
	if (angleMoyen <= - 1000) angleMoyen = angleMoyen + 2000;
	else if (angleMoyen > 1000) angleMoyen = angleMoyen - 2000;
	
	// Mettre pour le tableau
	angleMoyen += 1000;
	
	// Trouver le nouvel angle "propre" de baby Gali
	if (gali.angle <= - 2000) gali.angle = gali.angle%(-2000);
	else if (gali.angle > 2000) gali.angle = gali.angle%(2000);
	
	if (gali.angle <= - 1000) gali.angle = gali.angle + 2000;
	else if (gali.angle > 1000) gali.angle = gali.angle - 2000;
	
	//Distance
	int32 dis = ((int32)distance.variationSomme*1000) / IMP_M; //Distance en mm

	//Position
	gali.x += ((int32)dis * cosLUT[angleMoyen]) / 1000;
	gali.y += ((int32)dis * sinLUT[angleMoyen]) / 1000;
	
	// Reset variables
	angle.variationSomme = 0;
	distance.variationSomme  = 0;
}

void updateCurrentPosition ()
{
	// Angle
	currentGali.angle = gali.angle + ((int32)team*angle.variationSomme *2000)/IMP_T;
	
	// Arrondir la valeur
	if ((((int32)angle.variationSomme *2000)%IMP_T) > (IMP_T/2)) currentGali.angle += team;
		
	//Calcule de l'angle moyen
	int32 angleMoyen = (gali.angle + currentGali.angle)/2;
	
	// Trouver l'angle moyen lissé
	if (angleMoyen <= - 2000) angleMoyen = angleMoyen%(-2000);
	else if (angleMoyen > 2000) angleMoyen = angleMoyen%(2000);
	
	if (angleMoyen <= - 1000) angleMoyen = angleMoyen + 2000;
	else if (angleMoyen > 1000) angleMoyen = angleMoyen - 2000;
	
	// Mettre pour le tableau
	angleMoyen += 1000;
		
	// Trouver le nouvel angle "propre" de baby Gali
	if (currentGali.angle <= - 2000) currentGali.angle = currentGali.angle%(-2000);
	else if (currentGali.angle > 2000) currentGali.angle = currentGali.angle%(2000);
	
	if (currentGali.angle <= - 1000) currentGali.angle = currentGali.angle + 2000;
	else if (currentGali.angle > 1000) currentGali.angle = currentGali.angle - 2000;
		
	//Distance
	int32 dis = ((int32)distance.variationSomme*1000) / IMP_M; //Distance en mm
	
	//Position
	currentGali.x =  gali.x + ((int32)dis * cosLUT[angleMoyen]) / 1000;
	currentGali.y =  gali.y + ((int32)dis * sinLUT[angleMoyen]) / 1000;
}
