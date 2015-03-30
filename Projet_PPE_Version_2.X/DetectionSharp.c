//	Library
#include "DetectionSharp.h"

//	Variables
uint32 				sharpFrontUp1   [NB_SAMPLE] = {0, 0, 0, 0, 0, 0};
uint32 				sharpFrontUp2   [NB_SAMPLE] = {0, 0, 0, 0, 0, 0};
uint32 				sharpFrontDown1 [NB_SAMPLE] = {0, 0, 0, 0, 0, 0};
uint32 				sharpFrontDown2 [NB_SAMPLE] = {0, 0, 0, 0, 0, 0};
uint32 				sharpBack1      [NB_SAMPLE] = {0, 0, 0, 0, 0, 0};
uint32 				sharpBack2      [NB_SAMPLE] = {0, 0, 0, 0, 0, 0};


typedef struct _GestionnaireACD
{
	int32 sampleIndex;
	int32 currentSharpIndex;

}GestionnaireACD;
GestionnaireACD		gestionnaireACD [2];
BOOL	blocage;

void sharpTimerInit()
{
    // --- Timer 3 : ADC ---
    T3CONbits.TON   = 0;      // Disable timer
    T3CONbits.TCKPS = 0b00;   // Prescaler : 1
    T3CONbits.TCS   = 0;      // Internal clock
    T3CONbits.TGATE = 0;      // Timer mode
    TMR3            = 0x00;   // Clear Timer register

    // NB_SHARP * NB_SAMPLE * F_SAMPLE = PERIODE_ADC
    //    4     *     4     *   100Hz  =    3200
    PR3   = NB_SHARP * NB_SAMPLE *100 ;   // PERIODE_ADC

	//	Autres
    _T3IP = 0b010;            // Priority : 4
    _T3IF = 0;                // Clear flag
    _T3IE = 1;                // Enable interrupt

	// Active le timer
    T3CONbits.TON = 1;
}

//	Fonctions
void detectionSharpInit ()
{
	// Initialise le timer sharp
	sharpTimerInit();

//	// Init
	gestionnaireACD[0].sampleIndex = gestionnaireACD[1].sampleIndex = 0;
	gestionnaireACD[0].currentSharpIndex = gestionnaireACD[1].currentSharpIndex = 0;

	// 	ACD

	//	ANSELy
	_ANSB15 = 1;
	_ANSB14 = 1;
	_ANSB13 = 1;
	_ANSB12 = 1;
        _ANSB11 = 1;
        _ANSB10 = 1;

	// CON1
	AD1CON1bits.ADON = 0; 		// ACD mode disable
	AD1CON1bits.ADSIDL = 0; 	// Idle mode module operation
	AD1CON1bits.ADDMABM = 0;        // DMA buffers are written in Scatter/Gather mode.
	AD1CON1bits.AD12B = 0; 		// 10-bit, 4-channel ADC operation
	AD1CON1bits.FORM = 0b00;	// Integer (DOUT = 0000 00dd dddd dddd)
	AD1CON1bits.SSRC = 0b111;	// Internal counter ends sampling and starts conversion (auto-convert)
	AD1CON1bits.SSRCG = 0;
	AD1CON1bits.SIMSAM = 0;		// Samples multiple channels individually in sequence
	AD1CON1bits.ASAM = 0;		// Sampling begins when SAMP bit is set
	AD1CON1bits.SAMP = 0;		// ADC conversion not started or in progress

	//	CON2
	AD1CON2bits.VCFG = 0b000;	// VCFG
	AD1CON2bits.CSCNA = 0;		// Do not scan inputs
	AD1CON2bits.CHPS = 0;		// Converts CH0
	AD1CON2bits.BUFS = 0;		// ADC is currently filling the first half of the buffer
	AD1CON2bits.SMPI = 0b00000;	// Increments the DMA address after completion of every sample/conversion operation
	AD1CON2bits.BUFM = 0;		// Always starts filling the buffer from the start address
	AD1CON2bits.ALTS = 0;		// Always uses channel input selects for Sample A

	// CON 3
	AD1CON3bits.ADRC = 0; 				// Clock Derived from System Clock
	AD1CON3bits.SAMC = 0b11111; 		// 31 TAD
	AD1CON3bits.ADCS = 0b000000010;		// TCY · (ADCS<7:0> + 1) = 3 · TCY = TAD

	//	CON 4
	AD1CON4bits.DMABL   = 0;		// Allocates 1 word of buffer to each analog input
	AD1CON4bits.ADDMAEN = 0;		// Conversion results stored in ADCxBUF0 register, for transfer to RAM using DMA
	AD1CHS0bits.CH0NA = 0;			// Channel 0 negative input is VREFL

	//	ACD2
	AD2CON1  = 0b0000000011100000;
	AD2CON2  = 0b0000000000000000;
	AD2CON3  = 0b0001111100000010;
	AD2CON4  = 0b0000000000000000;
	AD2CHS0bits.CH0NA = 0; 			// Channel 0 negative input is VREFL


	//	Lancement ACD
	AD1CON1bits.ADON = 1;
	AD2CON1bits.ADON = 1;

//	//Initialiser les variables
//	blocage.timerDetection = millis;
	blocage = FALSE;
}


// Récupère la valeur d'un sharp
inline uint16 getSharp(int8 id)
{
	// Ressources
	int8 i;
	uint16 value = 0;

	// Trouver la valeur moyenne
	for(i=0; i < NB_SAMPLE; i++)
	{
		switch (id)
		{
                    // Front Down left
			case 0: value += sharpFrontDown1[i];
					break;
                    // Front Up left
			case 1:value += sharpFrontUp1[i];
					break;
                    // Back Left
			case 2:value += sharpBack1[i];
					break;
                    // Back Right
			case 3:value += sharpBack2[i];
					break;

                        case 4:value += sharpFrontDown2[i];
					break;

			case 5:value += sharpFrontUp2[i];
					break;
		}

	}

	return value;
}

// Détermine si un obstacle quelconque se trouve à 30 cm dans le sens donné
BOOL detectionSharpObstacle (BOOL sens)
{
	// En avant
	if ( sens && ((getSharp(0) > 1300) || (getSharp(1) > 1300) || (getSharp(2) > 1300) || (getSharp(3) > 1300)))
		return TRUE;

	// En arrière
	else if ( !sens && ((getSharp(4) >	1300) || (getSharp(5) > 1300)))
		return TRUE;

	return FALSE;
}

int detectionSharpProcess (BOOL sens)
{
	// Si on détecte un ennemie dans le sens d'avancée que l'on avait pas détecté avant
	if ((detectionSharpObstacle(sens)) && (! blocage))
	{
		// Signaler qu'on est bloqué
		blocage = TRUE;
		return 1;
	}

	//	Sinon si on ne détecte rien, réinitialiser les variables
	else if ( !detectionSharpObstacle(sens) && (blocage))
	{
		blocage = FALSE;
		return 2;
	}
        StringFormatted("%s",blocage ? "TRUE" : "FALSE");
	return 0;
}



//	Test chaque capteur un à un
BOOL detectionSharpObstacleSide (BOOL sens, BOOL side)
{
	// En avant
	if ( sens && side && ((getSharp(0) > 1300)))
		return TRUE;

	else if ( sens && !side && ((getSharp(1) > 1300)))
		return TRUE;

        else if ( sens && side && ((getSharp(2) > 1300)))
		return TRUE;

	else if ( sens && !side && ((getSharp(3) > 1300)))
		return TRUE;
	// En arrière
	else if ( !sens && side && ((getSharp(4) > 1300)))
		return TRUE;

	else if ( !sens && !side && ((getSharp(5) > 1300)))
		return TRUE;

	return FALSE;
}

/* In timer */
void __attribute__((__interrupt__,auto_psv)) _T3Interrupt(void)
{
	// Capteurs Left front
	if(AD1CON1bits.DONE)
	{

		if (gestionnaireACD [0].currentSharpIndex == 0)
                {
                    sharpFrontDown1[gestionnaireACD [0].sampleIndex] = ADC1BUF0;
//                    sendString (" | Sharp 1 = %d ", ADC1BUF0);
                }
		else if (gestionnaireACD [0].currentSharpIndex == 1){
                    sharpFrontUp1[gestionnaireACD [0].sampleIndex] = ADC1BUF0;
//                    sendString (" | Sharp 2  ");
                }
                else if (gestionnaireACD [0].currentSharpIndex == 2){
                    sharpFrontDown2[gestionnaireACD [0].sampleIndex] = ADC1BUF0;
                    StringFormatted(" | Sharp 3 = %d ",ADC1BUF0);
//                    sendString (" | Sharp 3  ");
                }
                else if (gestionnaireACD [0].currentSharpIndex == 3){
                    sharpFrontUp2[gestionnaireACD [0].sampleIndex] = ADC1BUF0;
//                    sendString (" | Sharp 4  ");
                }
                    
	}
	else
	{
		if (gestionnaireACD [0].currentSharpIndex == 0) 
                    sharpFrontDown1[gestionnaireACD [0].sampleIndex] = 0;
		else if (gestionnaireACD [0].currentSharpIndex == 1)
                    sharpFrontUp1[gestionnaireACD [0].sampleIndex] = 0;
                else if (gestionnaireACD [0].currentSharpIndex == 2)
                    sharpFrontDown2[gestionnaireACD [0].sampleIndex] = 0;
                else if (gestionnaireACD [0].currentSharpIndex == 3)
                    sharpFrontUp2[gestionnaireACD [0].sampleIndex] = 0;
	}

	// Capteurs arrières
	if(AD2CON1bits.DONE)
	{
		if (gestionnaireACD [1].currentSharpIndex == 0) {
//                    sendString (" | Sharp 5  ");
                    sharpBack2[gestionnaireACD [1].sampleIndex] = ADC2BUF0;
                    StringFormatted(" | Sharp 5 = %d ",ADC2BUF0);
                }
                    
		else {
//                    sendString (" | Sharp 6  ");
                    sharpBack1[gestionnaireACD [1].sampleIndex] = ADC2BUF0;
                }
	}
	else
	{
		if (gestionnaireACD [1].currentSharpIndex == 0)
                    sharpBack2[gestionnaireACD [1].sampleIndex] = 0;
		else
                    sharpBack1[gestionnaireACD [1].sampleIndex] = 0;
	}

	// Mise à jour des index
	gestionnaireACD [0].currentSharpIndex += 1;
	if(gestionnaireACD [0].currentSharpIndex == 4)
	{
		gestionnaireACD [0].currentSharpIndex = 0;
		gestionnaireACD [0].sampleIndex = (gestionnaireACD [0].sampleIndex + 1)%NB_SAMPLE;
	}

        gestionnaireACD [1].currentSharpIndex += 1;
	if(gestionnaireACD [1].currentSharpIndex == 2)
	{
		gestionnaireACD [1].currentSharpIndex = 0;
		gestionnaireACD [1].sampleIndex = (gestionnaireACD [1].sampleIndex + 1)%NB_SAMPLE;
	}

	// Changement des entrées AD
	AD1CHS0bits.CH0SA = gestionnaireACD [0].currentSharpIndex + 12;
	AD2CHS0bits.CH0SA = gestionnaireACD [1].currentSharpIndex + 14;

	// Lancements AD
	AD1CON1bits.SAMP = 1;
	AD2CON1bits.SAMP = 1;

	// Réinitialise le flag
	_T3IF = 0;
}

