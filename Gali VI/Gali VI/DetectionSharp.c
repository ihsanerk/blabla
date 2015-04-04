 //	Library
#include "DetectionSharp.h"

//	Variables
uint32 				sharp1 [NB_SAMPLE] = {0, 0, 0, 0, 0, 0};
uint32 				sharp2 [NB_SAMPLE] = {0, 0, 0, 0, 0, 0};
uint32 				sharp3 [NB_SAMPLE] = {0, 0, 0, 0, 0, 0};
uint32 				sharp4 [NB_SAMPLE] = {0, 0, 0, 0, 0, 0};

GestionnaireACD		gestionnaireACD [2];
Blocage				blocage;

//	Fonctions
void detectionSharpInit ()
{
	// Initialise le timer sharp
	sharpTimerInit();

	// Init
	gestionnaireACD[0].sampleIndex = gestionnaireACD[1].sampleIndex = 0;
	gestionnaireACD[0].currentSharpIndex = gestionnaireACD[1].currentSharpIndex = 0;

	// 	ACD

	//	ANSELy
	_ANSB15 = 1;
	_ANSB14 = 1;
	_ANSB13 = 1;
	_ANSB12 = 1;

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
	AD1CON3bits.ADCS = 0b000000010;		// TCY � (ADCS<7:0> + 1) = 3 � TCY = TAD

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

	//Initialiser les variables
	blocage.timerDetection = millis;
	blocage.actif = FALSE;
}

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

int detectionSharpProcess (bool sens)
{
	// Si on d�tecte un ennemie dans le sens d'avanc�e que l'on avait pas d�tect� avant
	if ((detectionSharpObstacle(sens)) && (! blocage.actif))
	{
		// Signaler qu'on est bloqu�
		blocage.actif = TRUE;
		blocage.timerDetection = millis;
		return 1;
	}

	//	Sinon si on ne d�tecte rien, r�initialiser les variables
	else if ( !detectionSharpObstacle(sens) && blocage.actif)
	{
		blocage.actif = FALSE;
		return 2;
	}

	return 0;
}


// R�cup�re la valeur d'un sharp
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
			case 0: value += sharp1[i];
					break;

			case 1:value += sharp2[i];
					break;

			case 2:value += sharp3[i];
					break;

			case 3:value += sharp4[i];
					break;
		}

	}

	return value;
}

// D�termine si un obstacle quelconque se trouve � 30 cm dans le sens donn�
bool detectionSharpObstacle (bool sens)
{
	// En avant
	if ( sens && ((getSharp(3) > 1300) || (getSharp(2) > 1300)))//sharp 4 = J12, sharp 3 = J13
		return TRUE;

	// En arri�re
	else if ( !sens && ((getSharp(0) >	1300) || (getSharp(1) > 1300)))
		return TRUE;

	return FALSE;
}

//	Test chaque capteur un � un
bool detectionSharpObstacleSide (bool sens, bool side)
{
	// En avant
	if ( sens && side && ((getSharp(2) > 1300)))
		return TRUE;

	else if ( sens && !side && ((getSharp(3) > 1300)))
		return TRUE;

	// En arri�re
	else if ( !sens && side && ((getSharp(0) > 1300)))
		return TRUE;

	else if ( !sens && !side && ((getSharp(1) > 1300)))
		return TRUE;

	return FALSE;
}

/* In timer */
void __attribute__((__interrupt__,auto_psv)) _T3Interrupt(void)
{
	// Capteurs avants
	if(AD1CON1bits.DONE)
	{
		if (gestionnaireACD [0].currentSharpIndex == 0) sharp1[gestionnaireACD [0].sampleIndex] = ADC1BUF0;
		else sharp2[gestionnaireACD [0].sampleIndex] = ADC1BUF0;
	}
	else
	{
		if (gestionnaireACD [0].currentSharpIndex == 0) sharp1[gestionnaireACD [0].sampleIndex] = 0;
		else sharp2[gestionnaireACD [0].sampleIndex] = 0;
	}

	// Capteurs arri�res
	if(AD2CON1bits.DONE)
	{
		if (gestionnaireACD [1].currentSharpIndex == 0) sharp3[gestionnaireACD [0].sampleIndex] = ADC2BUF0;
		else sharp4[gestionnaireACD [1].sampleIndex] = ADC2BUF0;
	}
	else
	{
		if (gestionnaireACD [1].currentSharpIndex == 0) sharp3[gestionnaireACD [1].sampleIndex] = 0;
		else sharp4[gestionnaireACD [1].sampleIndex] = 0;
	}

	// Mise � jour des index
	gestionnaireACD [0].currentSharpIndex += 1;
	if(gestionnaireACD [0].currentSharpIndex == 2)
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

	// Changement des entr�es AD
	AD1CHS0bits.CH0SA = gestionnaireACD [0].currentSharpIndex + 12;
	AD2CHS0bits.CH0SA = gestionnaireACD [1].currentSharpIndex + 14;

	// Lancements AD
	AD1CON1bits.SAMP = 1;
	AD2CON1bits.SAMP = 1;

	// R�initialise le flag
	_T3IF = 0;
}
