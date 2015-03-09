//	Library
#include "DetectionSharp.h"

//	Variables
uint32 				sharp1 [NB_SAMPLE] = {0, 0, 0, 0, 0, 0};

//	Fonctions
void detectionSharpInit ()
{
	
	// 	ACD
		
	//	ANSELy
	/* On va faire un test avec 1 Sharp.
        _ANSB15 = 1;
	_ANSB14 = 1;
	_ANSB13 = 1;
         */
	_ANSB10 = 1;
	
	// CON1
	AD1CON1bits.ADON = 0; 		// ACD mode disable
	AD1CON1bits.ADSIDL = 0; 	// Idle mode module operation
	AD1CON1bits.ADDMABM = 0;        // DMA buffers are written in Scatter/Gather mode.
	AD1CON1bits.AD12B = 0; 		// 10-bit, 4-channel ADC operation
	AD1CON1bits.FORM = 0b00;	// Integer (DOUT = 0000 00dd dddd dddd)
	AD1CON1bits.SSRCG = 0;
        AD1CON1bits.SSRC = 0b111;	// Internal counter ends sampling and starts conversion (auto-convert)
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


        //ON initialise de la même manière le ACD2
        //	ACD2
	AD2CON1  = 0b0000000011100000;
	AD2CON2  = 0b0000000000000000;
	AD2CON3  = 0b0001111100000010;
	AD2CON4  = 0b0000000000000000;
	AD2CHS0bits.CH0NA = 0; 			// Channel 0 negative input is VREFL
	
	//On lance les 2 ADC
        //	Lancement ACD
	AD1CON1bits.ADON = 1;
	AD2CON1bits.ADON = 1;

	AD1CHS0bits.CH0SA =10; //Correspond au port analogique 10
}

void adc_detection()
{
    //Ressources
    uint16 valeur_sharp=0;

    if(AD1CON1bits.DONE)
    {
        valeur_sharp = (uint16) ADC1BUF0;
        //On affiche la valeur du sharp
    }
    else
    {
        valeur_sharp = 0;
    }
    // Restart convertion
       // AD1CHS0bits.CH0SA = 10;
        AD1CON1bits.SAMP = 1;

}

