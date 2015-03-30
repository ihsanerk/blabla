//	Libraries
#include "Ascenseur.h"

//	Variables
uint32 timerIA;
bool   recup;

//	Initialisation
void ascenseurInit ()
{
	//	Pour chaque ascenseur
	timerIA = millis;
	recup = FALSE;
	int8 i = 0;
	for (i = 0; i < 2; i++)
	{
		//	Descendre la pince et l'ouvrire
		if (i == 0) 
		{
			ax12Execute (FERMER_PINCE_DROITE, 8, FALSE);
			delay_ms (100);
			ax12Execute (DESCENDRE_PINCE_DROITE, 11, TRUE);
			delay_ms (100);
			ax12Execute (FERMER_TUNNEL_DROIT, 6, TRUE);
			delay_ms (100);
		}
		
		else 
		{
			ax12Execute (FERMER_PINCE_GAUCHE, 10, FALSE);
			delay_ms (100);
			ax12Execute (DESCENDRE_PINCE_GAUCHE, 9, TRUE);
			delay_ms (100);
			ax12Execute (FERMER_TUNNEL_GAUCHE, 7, TRUE);
			delay_ms (100);
		}
		
		//	Initialiser les variables
		ascenseur[i].verres = 0;
		ascenseur[i].ordreFini = TRUE;
		ascenseur[i].ordreEnvoye = FALSE;
		ascenseur[i].timer = 0;
		
		//Autre initialisation
		ascenseur[i].ouvert = FALSE;
		ascenseur[i].tunnelActif = FALSE;
	}
		
	//	Initialiser la liste d'ordres
	listesAscenInit ();
}

//	Fonction principale
inline void ascenseurProcess(int8 liste)
{
	//	Si l'ascenseur n'a pas atteint son ordre et que ce n'est pas la fin d'une séquence
	if ((!ascenseur[liste].ordreFini) && (millis - timerIA > 1000))
	{
		//	Selon l'ordre donné, activer le bon actionneur
		switch (listeAscen[liste].ordres[listeAscen[liste].begin].action)
		{
			case MONTER:
						//Si l'ordre n'a pas été envoyé
						if (!ascenseur[liste].ordreEnvoye)  
						{
							//	Selon le coté
							if (liste == 0) ax12Execute (MONTER_PINCE_DROITE, 11, TRUE);
							else ax12Execute (MONTER_PINCE_GAUCHE, 9, TRUE);
							
							ascenseur[liste].ordreEnvoye = TRUE;
						}
						
						else if (millis - ascenseur[liste].timer  > 500) ascenseur[liste].ordreFini = TRUE;
						
						break;
						
			case DESCENDRE:
						//Si l'ordre n'est pas fini
						if (!ascenseur[liste].ordreEnvoye)  
						{
							//	Selon le coté
							if (liste == 0) ax12Execute (DESCENDRE_PINCE_DROITE, 11, TRUE);
							else ax12Execute (DESCENDRE_PINCE_GAUCHE, 9, TRUE);
							
							ascenseur[liste].ordreEnvoye = TRUE;
						}
						
						else if (millis - ascenseur[liste].timer  > 500) ascenseur[liste].ordreFini = TRUE;
						
						break;
						
			case OUVRIRE_PINCE:
						//Si l'ordre n'est pas fini
						if (!ascenseur[liste].ordreEnvoye) 
						{
							//	Selon le coté
							if (liste == 0) 
							{
								ax12Execute (OUVRIRE_PINCE_DROITE, 8, FALSE);
								ax12Execute (OUVRIRE_PINCE_DROITE, 8, FALSE);
								ax12Execute (OUVRIRE_PINCE_DROITE, 8, FALSE);
							}
							else 
							{ax12Execute (OUVRIRE_PINCE_GAUCHE, 10, FALSE);
							ax12Execute (OUVRIRE_PINCE_GAUCHE, 10, FALSE);
							ax12Execute (OUVRIRE_PINCE_GAUCHE, 10, FALSE);
							}
							
							ascenseur[liste].ordreEnvoye = TRUE;
						}
						
						else if (millis - ascenseur[liste].timer  > 400) ascenseur[liste].ordreFini = TRUE;
						
						break;
						
			case FERMER_PINCE:
						//Si l'ordre n'est pas fini
						if (!ascenseur[liste].ordreEnvoye)  
						{
							//	Selon le coté
							if (liste == 0) 
							{ax12Execute (FERMER_PINCE_DROITE, 8, FALSE);
							ax12Execute (FERMER_PINCE_DROITE, 8, FALSE);
							ax12Execute (FERMER_PINCE_DROITE, 8, FALSE);
							}
							else 
							{ax12Execute (FERMER_PINCE_GAUCHE, 10, FALSE);
							ax12Execute (FERMER_PINCE_GAUCHE, 10, FALSE);
							ax12Execute (FERMER_PINCE_GAUCHE, 10, FALSE);}
							
							ascenseur[liste].ordreEnvoye = TRUE;
						}
						
						else if (millis - ascenseur[liste].timer  > 400)
						{
							if (recup) ascenseur[liste].verres++;
							ascenseur[liste].ordreFini = TRUE;
						}
						
						break;
			
			// Les 2 derniers ordres sont exécutés en même temps par les 2 ascenseurs
			case OUVRIRE_TUNNEL:
						//Si l'ordre n'est pas fini
						if (!ascenseur[liste].ordreEnvoye) 
						{
							//	Selon le coté
							if (liste == 0) ax12Execute (OUVRIRE_TUNNEL_DROIT, 6, TRUE);
							else ax12Execute (OUVRIRE_TUNNEL_GAUCHE, 7, TRUE);
							
							ascenseur[liste].ordreEnvoye = TRUE;
						}
									
						else if (millis - ascenseur[liste].timer  > 500)
						{
							ascenseur[liste].ordreFini = TRUE;
							if (ascenseur[liste].tunnelActif) 
							{
								ascenseur[liste].ouvert = TRUE;
								ascenseur[liste].tunnelActif = FALSE;
							}
						}
						
						break;
						
			case OUVRIRE_TUNNEL_PEU:
						//Si l'ordre n'est pas fini
						if (!ascenseur[liste].ordreEnvoye) 
						{
							//	Selon le coté
							if (liste == 0) ax12Execute (OUVRIRE_TUNNEL_DROIT_PEU, 6, TRUE);
							else ax12Execute (OUVRIRE_TUNNEL_GAUCHE_PEU, 7, TRUE);
							
							ascenseur[liste].ordreEnvoye = TRUE;
						}
						
						else if (millis - ascenseur[liste].timer  > 500) ascenseur[liste].ordreFini = TRUE;
						
						break;
						
			case FERMER_TUNNEL:						
						//Si l'ordre n'est pas fini
						if (!ascenseur[liste].ordreEnvoye) 
						{
							//	Selon le coté
							if (liste == 0) ax12Execute (FERMER_TUNNEL_DROIT, 6, TRUE);
							else ax12Execute (FERMER_TUNNEL_GAUCHE, 7, TRUE);
							
							ascenseur[liste].ordreEnvoye = TRUE;
						}
						
						else if (millis - ascenseur[liste].timer  > 600)
						{
							ascenseur[liste].ordreFini = TRUE;
							if (ascenseur[liste].tunnelActif)
							{
								ascenseur[liste].ouvert = FALSE;
							}
						}
						break;
		}
	}
	
	//	Sinon, il l'a terminé
	if (ascenseur[liste].ordreFini)
	{
		//	Si ce n'est pas la fin d'une séquence passer à l'ordre suivant
		if (!listeAscen[liste].ordres[listeAscen[liste].begin].endSequence)
			getNextAscenOrdre (liste);
		
		//	Sinon regarder si l'IA a demandé l'activation du tunnel 
		else if (ascenseur[liste].tunnelActif)
		{
			// Si le tunnel n'a pas été ouvert
			if (!ascenseur[liste].ouvert)
			{
				if (ascenseur[liste].verres == 4) listeAscen[liste].begin = 25;
				else listeAscen[liste].begin = 20;
		
				ascenseur[liste].ordreFini = FALSE;
				ascenseur[liste].timer = millis;
				ascenseur[liste].ordreEnvoye = FALSE;
			}

			//	Sinon si les verres déposés par les 2 ascenseurs
			else
			{
				getNextAscenOrdre (liste);
				ascenseur[liste].tunnelActif = FALSE;
			}
		}
	}
}
