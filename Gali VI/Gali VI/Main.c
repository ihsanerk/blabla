//Libraries
#include "IA.h"

//Initialisations
_FOSCSEL(FNOSC_PRIPLL);
_FOSC(FCKSM_CSDCMD & OSCIOFNC_OFF & POSCMD_XT);
_FWDT(FWDTEN_OFF);
_FPOR(FPWRT_PWR128);

//Variables
int8 actions = 0;
uint32 millis = 0;
bool reset = FALSE;

void main (void)
{
	//	Attendre que le d�part soit activ�
	start ();

	//	Initialise les diff�rents modules
	intitialisation (SEQUENCE_RECALAGE);

	//	Lancer les ordres
	intelligenceArtificielle ();
	
	//Boucle de jeu
	while (!reset)
	{
		//Faire clignoter une led pour les tests
		LED2 =~ LED2;
		
		//Pause
		delay_ms(100);
	}
	
	// Reseter le pic
	asm("reset");
}
	
// Interruption g�n�r�e par le connecteur Jack
void __attribute__((__interrupt__,auto_psv))  _INT1Interrupt(void)
{	
	// Allumer une led
	LED3 = 1;
	
	// Start match timer
	T6CONbits.TON = 1;
		
	//R�activer architecture interruption
	T2CONbits.TON = 1; 
	
	// D�sactiver l'interuption
	IEC1bits.INT1IE    = 0;
	
	// Ouvrire les pinces
	ax12Execute (OUVRIRE_PINCE_DROITE, 8, FALSE);
	ax12Execute (OUVRIRE_PINCE_DROITE, 8, FALSE);
	
	ax12Execute (OUVRIRE_PINCE_GAUCHE, 10, FALSE);	
	ax12Execute (OUVRIRE_PINCE_GAUCHE, 10, FALSE);	
	
	// R�initialiser le flag
	_INT1IF = 0;
}

// Interruption g�n�r�e par le bouton reset
void __attribute__((__interrupt__,auto_psv))  _INT2Interrupt(void)
{	
	// Allumer une led
	LED4 = 1;
	
	// Stopper les moteurs
	PWM_G = 0;
	PWM_D  = 0;
	BRAKE_G = 1;
	BRAKE_D  = 1;
	
	// D�sactiver le torque des AX12
	uint8 i;
	/*for (i = 0; i < 4; i++)
		ax12DisableTorque (i);*/

	// D�sactivation de l'architecture
	T2CONbits.TON = 0; //	Disable timer
	TMR2 = 0x00;	//	Clear Timer register
	
	// D�sactiver le timer principal
	T7CONbits.TON = 0;
	TMR7 = 0x00;	//	Clear Timer register
	
	// Reseter le pics
	reset = TRUE;
	
	// R�initialiser le flag
	_INT2IF = 0;
}

//	Interruption de base grace au timer 2, controlant l'architecture du robot
void __attribute__((__interrupt__,auto_psv)) _T2Interrupt(void)
{
	//	Incr�menter la clock
	millis = millis + 1;

    //	Selon le compteur d'actions
    switch(actions)
    {
        //	Asservissement une fois sur 2
        case 0 :
        case 2 :
        case 4 :
        case 6 :
        case 8 ://	Asservissement / Controle du canon 
				//	Tant que tous les modules compl�mentaires ne sont pas �teint bloquer le mouvement
				if (!ascenseur[0].tunnelActif && !ascenseur[1].tunnelActif)
				{	
					//	Asservire le robot sauf lors des blocages
					if (listeAsser.ordres[listeAsser.begin].type == CERCLE) asservissement(TRUE);
					else asservissement(FALSE);
				}
				else applicationAssPosMoteurs(0, 0);
				
				// V�rifier la s�quence de blocage
				gestionnaireBlocage ();
            break;
			
		case 1 ://	Gestion de l'IA
			if (listeIA.active) intelligenceArtificielle ();
            break;
			
		case 3://	Mise � jour des infos tourelle / D�tection proche
			
			// D�tection proche : lorsque l'on avance et que l'on est pas sur un bord du terrain
			if (!sharpOff ()) afterDetection (detectionSharpProcess (SENS(distance.ordre)));
			
			// D�tection lointaine
			/*if(detectionTourelleProcess ()) getPositionEnnemi ();
			else
			{
				ennemi.x = -100;
				ennemi.y = -100;
			}*/
			
            break;
			
        case 5 ://	Mise � jour des infos balise / Gestion des bras
			if ((listeIA.sequence == SEQUENCE_BOUGIES) && (listeIA.ordres[listeIA.begin].asserCercleOn))
				brasProcess (roueDroite.erreur, roueGauche.erreur);

			break;
			
        case 7://	Ascenseurs
			ascenseurProcess(0);
			ascenseurProcess(1);
			break;
			
        case 9://	Communication avec Baby Gali
			//if (getPositionBaby ()) analyseTerrain (baby_Gali.x, baby_Gali.y);
            break;
			
        default ://	Bug
            break;
    }

    //	Incr�menter le compteur
    actions = (actions+1)%10;

    //	R�initialise le flag
    IFS0bits.T2IF = 0;
}

// Interruption de fin de match
void __attribute__((__interrupt__,auto_psv)) _T7Interrupt(void)
{
	// Stopper les moteurs
	PWM_G = 0;
	PWM_D  = 0;
	BRAKE_G = 1;
	BRAKE_D  = 1;
	
	// D�sactiver le torque des AX12
	uint8 i;
	/*for (i = 0; i < 4; i++)
		ax12DisableTorque (i);*/

	
	// D�sactivation de l'architecture
	T2CONbits.TON = 0; //	Disable timer
	TMR2 = 0x00;	//	Clear Timer register

	//	R�initialise le flag
	_T7IF = 0;     
}
