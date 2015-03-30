//Library
#include "IA.h"

//	Variables

//Parce que Mplab nous y oblige...
int8 		zoneVerres [4] = {0, 0, 1, 1};
Robot 		ennemi;

bool		game = FALSE;
bool	 	babyGaliEvite;
uint32		timeout;
uint8		ascenseurActif;
bool		changementAscenseur;
bool 		freeze;
bool		changementColonne = FALSE;
bool		blockChange = FALSE;

int32		cptAnnuleVerre = 10;
uint32 		timer2 = 0;
bool		wasRecalage = FALSE;

//	Départ
void start ()
{
	// Pin
	_ANSE8 = 0;
	_TRISE8 = 1;
	_INT2R = 88;

	// Registre
	IEC1bits.INT2IE    = 0;     // Disable interrupt
	IFS1bits.INT2IF    = 0;     // Clear interrupt flag
	INTCON2bits.INT2EP = 0;		// Interrupt on positive edge
	
	_INT2IP    = 0b110; 		// Priority : 6
    IEC1bits.INT2IE    = 1;     // Enable interrupt
	
	// Attendre que l'état change
	while (PORTEbits.RE8);
}
	
//	Initialisation
void intitialisation (SequenceType sequence)
{
	//	Base
	oscillatorInit();
	uartInit();
	timerInit();
	ax12Init ();
	debuggerInit ();
	jackInit ();
	
	//	Asservissement
	listeAsserInit();
	
	//	Ascenseurs
	ascenseurInit ();
	
	// Bras
	baliseInit ();
	brasInit ();
		
	// Detection
	//detectionTourelleInit ();
	detectionSharpInit ();
	
	//	Modules complémentaires
	//communicationBabyInit();
	
	//	IA
	intelligenceArtificielleInit(sequence);
}

void intelligenceArtificielleInit(SequenceType sequence)
{
	// Initialise la couleur
	_ANSE9 = 0;
	_TRISE9 = 1;
	
	

	// Autre
	babyGaliEvite = FALSE;
	timeout = millis;
	freeze = FALSE;
	changementAscenseur = FALSE;
	
	// Initialisation pour la séquence des verres
	if (team == -1) ascenseurActif = 1;
	else ascenseurActif = 0;
	
	//	Initialisaition IA
	listeIAInit(sequence);
}

void oscillatorInit()
{
	// The settings below set up the oscillator and PLL for 40 MIPS as
    // follows:
    //               Crystal Frequency * (PLLFBD+2)
    //       Fcy =  ----------------------------
    //                       2 * N1 * N2

    PLLFBD             = 30; // PLLDIV = 38, M  = 40
    CLKDIVbits.PLLPOST =  0; // PLLPOST = 0, N1 =  2
    CLKDIVbits.PLLPRE  =  0; // PLLPRE  = 0, N2 =  2
	CLKDIVbits.DOZEN   =  0; // Fcy = Fosc/2
    OSCCONbits.CLKLOCK =  0; // Enable clock settings to change
    OSCCONbits.LPOSCEN =  0; // Disable secondary oscillator

    OSCCONbits.NOSC  = 0b011; // New config XT PLL
    OSCCONbits.OSWEN = 1;     // Activate new config

	// WARNING : infinite loop !
    while(OSCCONbits.COSC != 0b011); // Wait until config is set
}

void timerInit ()
{
    // --- Timer 2 : Control du robot ---
    T2CONbits.TON   = 0;      // Disable timer
	T2CONbits.TCKPS = 0b01;   // Prescaler : 8
    T2CONbits.T32   = 0;      // 16 bits
    T2CONbits.TCS   = 0;      // Internal clock
    T2CONbits.TGATE = 0;      // Timer mode
    TMR2            = 0x00;   // Clear Timer register
	PR2             = PR;     // Period value (4000 = 1000Hz)

    IPC1bits.T2IP = 0b101;    // Priority : 6
    IFS0bits.T2IF = 0;        // Clear flag
    IEC0bits.T2IE = 1;        // Enable interrupt
	
	// --- Timers 6 et 7 (32 bits) : Fin du match ---
	
	/*
		PRESCALER 256
		FOVERFLOW 0.011111111 Hz (90 secondes)
		FCY 32 000 000
		PR	11 250 000 ( 1010 1011 1010 1001 0101 0000 )
	*/
	T6CONbits.TON   = 0;      // Disable timer
	T7CONbits.TON   = 0;      // Disable timer
	
	// Timer 6
	T6CONbits.TCKPS = 0b11;   	// Prescaler : 256
	T6CONbits.T32   = 1;      	// 32 bits
	T6CONbits.TCS   = 0;      	// Internal clock 
	T6CONbits.TGATE = 0;      	// Timer mode
	TMR6            = 0x00;   	// Clear Timer register
	PR6 			= 43344;	// Period value (LSB) 1010 1001 0101 0000

	// Timer 7
	T7CONbits.TCS   = 0;      	// Internal clock 
	T7CONbits.TGATE = 0;      	// Timer mode
	TMR7            = 0x00;  	// Clear Timer register
	PR7				 = 171;		// Period value (MSB) 1010 1011 

	// Interruption
	_T7IP = 0b111;    // Priority : 7 (Highest)
	_T7IF = 0;        // Clear flag
	_T7IE = 1;        // Enable interrupt
}

void jackInit ()
{
	// Pin
	RPINR0bits.INT1R = 104;
	
	// Register
	IEC1bits.INT1IE    = 0;     // Disable interrupt
	IFS1bits.INT1IF    = 0;     // Clear interrupt flag
    INTCON2bits.INT1EP = 1;		// Interrupt on negative edge
	
	IPC5bits.INT1IP    = 0b110; // Priority : 6
		
    IEC1bits.INT1IE    = 1;     // Enable interrupt
}

// Fonction gérant l'ensemble des décisions du robot
/*
	L'IA doit attendre l'scenseur avant d'avancer : utilisation d'un timeout qui simule l'activation dans ascenseur timeout lance la prochaine action
*/
inline void intelligenceArtificielle ()
{
	// S'il n'y a plus d'ordre d'asservissement
	if ((listeAsser.empty) && (listeAsserIsEmpty ()))
	{	
		// Réinit blocage
		babyGaliEvite = FALSE;
		
		//Si c'était la séquence de reclage
		if (listeIA.sequence == SEQUENCE_RECALAGE)
		{
			//Si c'est la première fois
			if (T2CONbits.TON == 0)
			{
				//Donner les ordres
				addAsserOrdre (RECALAGE_1, -420);
				addAsserOrdre (AVANCE, 875);
				addAsserOrdre (ROTATION, team*500);
				addAsserOrdre (RECALAGE_2, -420);
				
				//Activer l'architecture
				T2CONbits.TON = 1;
			}

			else
			{
				//Initialiser la position de gali 
				gali.x = 100;
				gali.y = 1025;
				gali.angle = 0;
			
				//Charger la prochaine stratégie
				if (game) listeIA.sequence = SEQUENCE_VERRES;
				else listeIA.sequence = SEQUENCE_HOMOLOGATION;
				
				strategie ();
				
				// Charger le premier ordre
				calculateurDeTrajectoire (listeIA.ordres[listeIA.begin].x,
										  listeIA.ordres[listeIA.begin].y,
										  listeIA.ordres[listeIA.begin].angle);

				// Désactivation de l'architecture
				applicationAssPosMoteurs(0, 0);
				T2CONbits.TON = 0;
				
			}
		}
		
		else
		{
			// Si le robot était bloqué et a du manoeuvré
			if (listeIA.lastOrderBlocked)
			{
				// Recalculer le chemin
				calculateurDeTrajectoire (listeIA.ordres[listeIA.begin].x,
										  listeIA.ordres[listeIA.begin].y,
										  listeIA.ordres[listeIA.begin].angle);
				
				// Réinitialiser la variable
				listeIA.lastOrderBlocked = FALSE;
			}
			
			else
			{
				// Avancer dans la liste
				switch (listeIA.sequence)
				{
					case SEQUENCE_CERISES:  // Parce que certains n'ont rien foutu cette année
											recup = FALSE;
											algoCerises ();
											break;
											
					case SEQUENCE_VERRES: 	recup = TRUE;
											algoVerres ();
											break;
											
					case SEQUENCE_BOUGIES:	// Si on utilisait les bras, les ranger
											if (listeIA.ordres[listeIA.begin].asserCercleOn)
											{
												applicationAssPosMoteurs(0, 0);
												brasFermeture ();
											}
											
											// Passer à l'ordre suivant
											getNextIAOrdre();
											break;
					
					default: // Sequence homologation
							getNextIAOrdre();
								break;
				}
				
				// Si la liste d'IA est vide passer à la séquence suivante
				if (listeIAIsEmpty ())
				{
					// Avancer dans la séquence
					listeIA.sequence++;
					
					// Si c'est la séquence des bougies, relever les bras
					if ((listeIA.sequence == SEQUENCE_BOUGIES) && (ascenseur[0].verres != 4) && (ascenseur[1].verres != 4))
					{
						applicationAssPosMoteurs(0, 0);
					
						ax12Execute (FERMER_PINCE_DROITE, 8, FALSE);
						ax12Execute (FERMER_PINCE_GAUCHE, 10, FALSE);
						delay_ms (500);
						ax12Execute (MONTER_PINCE_DROITE, 11, TRUE);
						ax12Execute (MONTER_PINCE_GAUCHE, 9, TRUE);
						delay_ms (500);
						ax12Execute (FERMER_TUNNEL_DROIT, 6, TRUE);
						ax12Execute (FERMER_TUNNEL_GAUCHE, 7, TRUE);
						
						strategie ();
						LED7 = 1;
					}
	
					else if (listeIA.sequence != SEQUENCE_BOUGIES)
						strategie ();
				}
							
				// Si la liste IA n'est pas vide
				if (!listeIAIsEmpty () && !freeze)
				{	
					// Cas particuliere du recalage sur gateau
					if (listeIA.ordres[listeIA.begin].x == -1000)
					{
						addAsserOrdre (RECALAGE_2, -team*450);
						addAsserOrdre (AVANCE, team*100);	
						addAsserOrdre (ROTATION, team*500);
					}
					
					// Cas particulier du changement de colonne
					else if (changementColonne) 
					{
						// Selon la partie du terrain
						cptAnnuleVerre = 1;
						addAsserOrdre (AVANCE, 150);
						
						if (listeIA.ordres[listeIA.begin].x <= 2000) addAsserOrdre (ROTATION, 250);
						else addAsserOrdre (ROTATION, 750);
						
						addAsserOrdre (AVANCE, 300);
					}
					
					else if ((listeIA.sequence == SEQUENCE_CERISES) && (listeIA.ordres[listeIA.begin].x == -2000))
					{
						addAsserOrdre (ROTATION, 1000);
						addAsserOrdre (RECALAGE_2, -450);
					}
					
					// Le traduire en ordre d'asservissement
					else if (!listeIA.ordres[listeIA.begin].asserCercleOn)
					{
						calculateurDeTrajectoire (listeIA.ordres[listeIA.begin].x,
												  listeIA.ordres[listeIA.begin].y,
												  listeIA.ordres[listeIA.begin].angle);
					}
						
					// Si on est en asservissement circulaire
					else 
					{
						// Déployer les bras
						applicationAssPosMoteurs(0, 0);
						brasOuverture ();
						
						// Ordre de mouvement	
						addAsserOrdre (ROTATION, -team*500);
						addAsserOrdre (RECALAGE_2, -team*450);
						addAsserOrdre (CERCLE, 100);
						addAsserOrdre (CERCLE, 0);
						addAsserOrdre (ROTATION, -team*500);
					}
				}
				
				// Plus d'ordre
				else if (listeIAIsEmpty ()) listeIA.active = FALSE;
			}
		}
	}
}

// Calcule les ordres à partir des points à atteindre
/*
	x et y coordonnées en mm depuis le bord inférieur gauche de la table
	angle en millième de radian
*/
void calculateurDeTrajectoire (int32 x, int32 y, int32 angle)
{		
	// Mise à jour de la position
	updatePosition ();

	// Déterminer la distance
	int32 y_distance = ABS(gali.y - y);
	int32 distance = sqrt( (int32)(gali.x - x)*(gali.x - x) + (int32)(y_distance)*(y_distance) );

	// Déterminer l'angle à avoir avant d'atteindre l'objectif
	int32 angleTemp = (((int32)(y-gali.y)*1000)/distance) + 1000;
	int32 angleAvance = asinLUT[angleTemp]; //	Simule la fonction :  asin(x/1000) * 1000/180 grace à une lutte
	int32 angleDepart = angleAvance - gali.angle;
	
	// Prendre en compte x
	if (gali.x > x) angleDepart = 1000 - angleDepart;

	// Trouver l'angle le plus court de face
	if (angleDepart <= - 2000) angleDepart = angleDepart%(-2000);
	else if (angleDepart > 2000) angleDepart = angleDepart%(2000);
	
	if (angleDepart <= - 1000) angleDepart = angleDepart + 2000;
	else if (angleDepart > 1000) angleDepart = angleDepart - 2000;
	
	// Marche arrière si plus efficace
if ( angleDepart  >= 500)
	{
		angleDepart = - 1000 + angleDepart;
		distance = -distance;
	}

else if ( angleDepart  <= -500)
	{
		angleDepart =  1000 + angleDepart;
		distance = -distance;
	}
	
	// Retrouver l'angle avance épuré
	angleAvance = angleDepart + gali.angle;
	if (angleAvance <= - 1000) angleAvance = (angleAvance%(-2000)) + 2000;
	else if (angleAvance > 1000) angleAvance = (angleAvance%(2000)) - 2000;

	// Déterminer l'angle de fin d'objectif
	int32 angleFin = angle - angleAvance;
			
	// Trouver l'angle le plus court de face
	if (angleFin <= - 2000) angleFin = angleFin%(-2000);
	else if (angleFin > 2000) angleFin = angleFin%(2000);
	
	if (angleFin <= - 1000) angleFin = angleFin + 2000;
	else if (angleFin > 1000) angleFin = angleFin - 2000;

	// Créer les ordres
	addAsserOrdre (ROTATION, team*angleDepart);
	addAsserOrdre (AVANCE, distance);
	addAsserOrdre (ROTATION, team*angleFin);
}
		
void gestionnaireBlocage ()
{
	if (blocage.actif) 
	{
		if (((millis - blocage.timerDetection) > 3000) && (listeIA.sequence != SEQUENCE_HOMOLOGATION) && (!listeIA.ordres[listeIA.begin].asserCercleOn) && (!wasRecalage))
		{	
			//Si on est entre 2 séquences passe à la prochaine phase
			if (listeIA.ordres[listeIA.begin].interSequenceOn)
				blocage.timerDetection = millis;
	
			//Sinon l'action échoue
			else 
			{
				// Vider la liste d'ordre
				cleanAsserListe ();
				
				// Passer à l'ordre suivant
				listeIA.lastOrderSucceded = FALSE;
				
				// Débloquer le robot
				blocage.actif = FALSE;
			}
		}
	}
}

void afterDetection (int8 ret)
{
	// Selon le nouveau type d'état
	switch (ret)
	{
		// Si on vient de se faire bloquer
		case 1: // Si on vient de passer en attente sauver l'ordre en cours dans un buffer
				if ((listeAsser.ordres[listeAsser.begin].type == CERCLE))
				{
					// Garder en mémoire l'erreur actuelle
					erreurMemory ();
					
					// Garder l'action en mémoire dans le buffeur
					blocage.bufferErreur_1 = roueGauche.erreur;
					blocage.bufferErreur_2 = roueDroite.erreur;
					
					// Mettre les erreurs à 0
					roueGauche.erreur = 0;
					roueDroite.erreur = 0;
				}
				
				else if ((listeAsser.ordres[listeAsser.begin].type == RECALAGE_2))
				{
					// Garder en mémoire l'erreur actuelle
					erreurMemory ();
					
					// Garder l'action en mémoire dans le buffeur
					blocage.bufferErreur_2 = angle.erreur;
					wasRecalage = TRUE;
					angle.enable = TRUE;
					distance.enable = TRUE;
					
					// Mettre les erreurs à 0
					distance.erreur = 0;
					angle.erreur = 0;
				
					// Transformer l'ordre en ordre de distance
					listeAsser.ordres[listeAsser.begin].type = AVANCE;
				}
				
				else
				{
					// Garder en mémoire l'erreur actuelle
					erreurMemory ();

					// Garder l'action en mémoire dans le buffeur
					blocage.bufferErreur_1 = distance.erreur;
					blocage.bufferErreur_2 = angle.erreur;
					
					// Mettre les erreurs à 0
					distance.erreur = 0;
					angle.erreur = 0;
					
					applicationAssPosMoteurs(0, 0);
				}
				break;
		
		// Si on vient d'être débloqué
		case 2: if ((listeAsser.ordres[listeAsser.begin].type == CERCLE))
				{
					roueGauche.erreur = blocage.bufferErreur_1;
					roueDroite.erreur = blocage.bufferErreur_2;
				}
				
				else if (wasRecalage)
				{
					angle.erreur = blocage.bufferErreur_2;
					wasRecalage = FALSE;
				
					// Transformer l'ordre en ordre de distance
					listeAsser.ordres[listeAsser.begin].type = RECALAGE_2;
					
					distance.ordre = listeAsser.ordres[listeAsser.begin].valeur;
					angle.enable = TRUE;
					distance.enable = FALSE;
				}
				
				else
				{
					distance.erreur = blocage.bufferErreur_1;
					angle.erreur = blocage.bufferErreur_2;
				}
				break;
				
		default: //Nothing
				break;
	}
}

//Gestion de l'asservissement du robot
inline void asservissement(bool circulaire)
{
	if (((!changementColonne) || (ascenseur[ascenseurActif].ordreFini) || (listeAsser.ordres[listeAsser.begin].type != ROTATION))
	&& ((!blockChange) || (millis - timer2 > 1000)))
	{
		//On convertit ces valeurs en polaire (angle + distance)
		if (circulaire) asservissementCirculaire ();
		else
		{
			if (listeAsser.ordres[listeAsser.begin].type == AVANCE) asservissementPolaire (TRUE);
			else asservissementPolaire (FALSE);
		}
	 
		// Gérer la liste des ordres
		if (!blocage.actif)
		{
			if (! listeAsser.empty) gestionnaireOrdres();
			else if ((! listeAsserIsEmpty ()) && (distance.ordre == 0) && (angle.ordre == 0)) nouvelOrdre ();
		}
	}
	
	else applicationAssPosMoteurs(0, 0);
}

// Gestionnaire de détection

// Désactiver sur les bords du terrain et près du gâteau
bool sharpOff ()
{	
	// Si on a un ordre d'assert
	if ((!listeAsser.empty) || (!listeAsserIsEmpty ()))
	{
		// Lorsque l'on utilise l'asservissement ciculaire activer les sharps : à tester
		if (listeAsser.ordres[listeAsser.begin].type == CERCLE)
			return FALSE;
		
		else if ((listeAsser.ordres[listeAsser.begin].type == ROTATION) || (listeIA.sequence == SEQUENCE_RECALAGE))
			return TRUE;
			
		// Sinon
		else
		{
			// lorsque le tunnel s'ouvre désactiver les sharps
			if (SENS(distance.ordre))
			{
				if ((!ascenseur[0].ordreFini) && (((listeAscen[0].ordres[listeAscen[0].begin].action) == OUVRIRE_TUNNEL) 
					|| ((listeAscen[0].ordres[listeAscen[0].begin].action) == OUVRIRE_TUNNEL_PEU) 
					|| ((listeAscen[0].ordres[listeAscen[0].begin].action) == FERMER_TUNNEL))) 
						return TRUE;
						
				if ((!ascenseur[1].ordreFini) && (((listeAscen[1].ordres[listeAscen[1].begin].action) == OUVRIRE_TUNNEL) 
					|| ((listeAscen[1].ordres[listeAscen[1].begin].action) == OUVRIRE_TUNNEL_PEU) 
					|| ((listeAscen[1].ordres[listeAscen[1].begin].action) == FERMER_TUNNEL))) 
						return TRUE;
			}
			
			// Mettre à jour la position de Gali
			updateCurrentPosition ();
			
			// Angle selon le coté
			int32 angle = currentGali.angle;
			angle += 1000;
			int32 x = currentGali.x +((int32)200 * cosLUT[angle]) / 1000;
			int32 y = currentGali.y +((int32)200 * sinLUT[angle]) / 1000;
								
			// Si le robot est à moins de 20 cm d'une bordure dans son sens désactiver les sharps
			if ( (x < 150) || (x > 2850) || (y > 1850) || (y < 150)) return TRUE;
			
			// Si le robot est orienté vers le gâteau désactiver les sharps
			else if ( (x < 2150) && (x > 850) && (y > 1350) && (y < 1850)) return TRUE;
		}
		
		return FALSE;
	}
	
	// Sinon désactiver les
	return TRUE;
}

bool isBabyGali ()
{
	// Mettre à jour la position de Gali
	updateCurrentPosition ();
	
	// Angle selon le coté
	int32 angle = currentGali.angle;
	angle += 1000;
	int32 x = currentGali.x +((int32)200 * cosLUT[angle]) / 1000;
	int32 y = currentGali.y +((int32)200 * sinLUT[angle]) / 1000;
						
	// Si le robot est à moins de 30 cm de Baby Gali
	if ((baby_Gali.x < x + 150) && (baby_Gali.y < y + 150) && (baby_Gali.x > x - 150) && (baby_Gali.y > y - 150)) return TRUE;
	
	// Sinon activer les
	return FALSE;
}

bool horsTerrain (bool side)
{
	// Mettre à jour la position de Gali
	updateCurrentPosition ();
	
	// Angle selon le coté
	int32 angle;
	if (side) angle = currentGali.angle + 500;
	else angle = currentGali.angle - 500;
	
	// Le reste des calcules
	if (angle < - 1000) angle = (angle%(-2000)) + 2000;
	else if (angle > 1000) angle = (angle%(2000)) - 2000;

	angle += 1000;

	int32 x = currentGali.x +((int32)600 * cosLUT[angle]) / 1000;
	int32 y = currentGali.y +((int32)600 * sinLUT[angle]) / 1000;
	
	//	Déterminer si la nouvelle position est hors limite
	if ( (x < 2600) && (x > 400) && (y < 1325) && (y > 175)) return TRUE;
	else return FALSE;
}

void analyseTerrain (uint16 x, uint16 y)
{
	// Regarder les verres restants
	/*if (listeIA.sequence <= SEQUENCE_VERRES )
	{
		// Ligne 1
		if ((y > 850) && (y < 1250))
		{
			if ((x < 1100) && (x > 700)) zoneVerres [2][0] = TRUE;
			if ((x > 1000) && (x < 1400)) zoneVerres [2][1] = TRUE;
			if ((x > 1600) && (x < 2000)) zoneVerres [2][2] = TRUE;
			if ((x > 1900) && (x < 2300)) zoneVerres [2][3] = TRUE;
		}
	}*/
}

void getPositionEnnemi ()
{
	// Mettre à jour la position de Gali
	updateCurrentPosition ();
	
	//  Déterminer les coordonnées cartésiennes du robot
	robot.angleRelatif = robot.angleRelatif*team;
	robot.angleRelatif += 1000;
		
	ennemi.x = currentGali.x + (robot.distanceRelative * cosLUT[robot.angleRelatif]) / 1000;
	ennemi.y = currentGali.y + (robot.distanceRelative * sinLUT[robot.angleRelatif]) / 1000;

	//  Modifier zone de check en fonction
	analyseTerrain (ennemi.x, ennemi.y);
}

// Stratégies
void algoVerres ()
{ 
	// Si l'ascenseur a récupéré le dernier verres ou si timeout (pas utilisé normalement)
	if ((ascenseur[ascenseurActif].ordreFini) || (millis - timeout > 5000))
	{	
		// Réinitialiser les variables de gestion
		freeze = FALSE;
		
		// Fermer l'ascenseur
		if (ascenseurActif == 0) ax12Execute (FERMER_TUNNEL_DROIT, 6, TRUE);
		else ax12Execute (FERMER_TUNNEL_GAUCHE, 7, TRUE);
		
		// Si l'action a échouée
		if (!listeIA.lastOrderSucceded)
			 getNextIAOrdre ();

			 	/*		listeIA.ordres[listeIA.begin].x = listeIA.ordres[buffBegin].x + 200;
					listeIA.ordres[listeIA.begin].y = 850;
					listeIA.ordres[listeIA.begin].angle = 1000; 
					listeIA.ordres[listeIA.begin].interSequenceOn = FALSE;
					
					// Changer d'ascenseur
					ascenseurActif = ascenseurActif + team;
					changementAscenseur = TRUE;
					
// Si 2 en meme temps, avancer 10 puis ordre verres, puis new pos du change ascen
// Si changement colonne, avancer 10, ordre verres
codeer jack pot*/

		// Sinon l'action a réussi 
		else
		{	
			// Selon le verre dispo
			bool prendre = TRUE;
			blockChange = FALSE;
			if ((listeIA.ordres[listeIA.begin].x < 500) || changementAscenseur || (cptAnnuleVerre == 2)) prendre = FALSE;
			
			changementAscenseur = FALSE;
			changementColonne = FALSE;
			cptAnnuleVerre++;
			
			// Avancer dans la liste
			int16 avanceListe = (listeIA.begin + listeIA.ordres[listeIA.begin].goIfSuccess)%MAX_ORDRES_IA;
			int16 buffBegin = 0;
			
			if ((zoneVerres[0] == 1) && (listeIA.ordres[avanceListe].x == 680)) 
			{
				buffBegin = (avanceListe + listeIA.ordres[avanceListe].goIfFail)%MAX_ORDRES_IA;
				changementColonne = TRUE;
			}
			else if ((zoneVerres[1] == 1) && (listeIA.ordres[avanceListe].x == 980))
			{			
				buffBegin = (avanceListe + listeIA.ordres[avanceListe].goIfFail)%MAX_ORDRES_IA;
				changementColonne = TRUE;
			}
			else if ((zoneVerres[2] == 1) && (listeIA.ordres[avanceListe].x == 1580)) 
			{
				buffBegin = (avanceListe + listeIA.ordres[avanceListe].goIfFail)%MAX_ORDRES_IA;
				changementColonne = TRUE;
			}
			else if ((zoneVerres[3] == 1) && (listeIA.ordres[avanceListe].x == 1880))
			{
				buffBegin = (avanceListe + listeIA.ordres[avanceListe].goIfFail)%MAX_ORDRES_IA;
				changementColonne = TRUE;
			}
			else buffBegin = avanceListe;

			// Si l'ascenseur est plein passé au suivant
			if ((ascenseur[ascenseurActif].verres == 3) && prendre && (listeIA.ordres[listeIA.begin].x != 1270))
			{
				// Récupérer le nouveau verre s'il y a encore des ordres de verres
				if (listeAscen[ascenseurActif].begin <= 25)
				{
					getNextAscenOrdre (ascenseurActif);
					timerIA = millis;
				}

				// Ordre polymorphe
				if ((((ascenseurActif == 0) && (team == 1)) || ((ascenseurActif == 1) && (team == -1)) ))
				{
					listeIA.ordres[listeIA.begin].x = listeIA.ordres[buffBegin].x + 200;
					listeIA.ordres[listeIA.begin].y = 850;
					listeIA.ordres[listeIA.begin].angle = 1000; 
					listeIA.ordres[listeIA.begin].interSequenceOn = FALSE;
					
					// Changer d'ascenseur
					ascenseurActif = ascenseurActif + team;
					changementAscenseur = TRUE;
				}
			}
			
			// Sinon aller à l'ordre suivant
			else
			{
				listeIA.begin = buffBegin;
	
				// Récupérer le nouveau verre s'il y a encore des ordres de verres
				if (prendre && (listeAscen[ascenseurActif].begin <= 25))
				{
					getNextAscenOrdre (ascenseurActif);
					timerIA = millis;
				}
			}
			
			// Si on a déjà changer de colonne, changer l'ordonnée
			if (listeAscen[ascenseurActif].begin <= 25)
				if (((ascenseurActif == 1) && (team == 1)) || ((ascenseurActif == 0) && (team == -1)) )
					listeIA.ordres[listeIA.begin].y = 850;
		}
		
		// Réinitialiser le timer
		timeout = millis;
		
		// Ne pas attendre après un ordre de changement
		if (cptAnnuleVerre == 2) 
		{
			timerIA = millis + 1000;
			timer2 = millis;
			blockChange = TRUE;
		}
	}
	
	else freeze = TRUE;
}

void algoCerises ()
{
	//Vérifier si on a terminé une action la checker
	/*if (listeIA.lastOrderSucceded && (listeIA.ordres[listeIA.begin].x > 100) && (listeIA.ordres[listeIA.begin].x < 400))
		switch (listeIA.ordres[listeIA.begin].y)
		{			
			case 600 :	//sendPositionGali (gali.x, gali.y);
						break;
			
			case 1000:	//sendPositionGali (gali.x, gali.y);
						break;
		}
		
	if (listeIA.ordres[listeIA.begin].x == -2000) gali.x = 100;*/
	
	// Activer l'ascenseur si nécessaire
	if (listeIA.lastOrderSucceded && listeIA.ordres[listeIA.begin].tunnelOn)
	{
		if ((listeIA.ordres[listeIA.begin].x > 100) && (listeIA.ordres[listeIA.begin].x < 400) && ((ascenseur[0].verres != 0) || (ascenseur[1].verres != 0)))
		{
			ascenseur[0].tunnelActif = TRUE;
			ascenseur[1].tunnelActif = TRUE;
		}
		
		if ((listeIA.ordres[listeIA.begin].x == 600) && ((ascenseur[0].ouvert) || (ascenseur[1].ouvert)))
		{
			ascenseur[0].verres = 0;
			ascenseur[1].verres = 0;
			
			ascenseur[0].tunnelActif = TRUE;
			ascenseur[1].tunnelActif = TRUE;
		}
	}
	
	//Avancer dans la liste
	listeIA.begin = (listeIA.begin + 1)%MAX_ORDRES_IA;
	listeIA.lastOrderSucceded = TRUE;

	//Verifier que l'action n'a pas déjà été faite
	if ((listeIA.ordres[listeIA.begin].x > 100) && (listeIA.ordres[listeIA.begin].x < 400) && (ascenseur[0].verres == 0) && (ascenseur[1].verres == 0))
		listeIA.begin = (listeIA.begin + 2)%MAX_ORDRES_IA;
}
