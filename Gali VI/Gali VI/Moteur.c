// Library
#include "Moteur.h"

//Variables
Codeur 			codeurGauche	;
Codeur 			codeurDroit		;

// Initialisation
void moteurInit ()
{
	// Configuration des pins
	_TRISC2 = 0;// PWM_D
	_TRISE7 = 0;// PWM_G
	
	_TRISE4 = 0;// BREAK_G	
	_TRISC1 = 0;// BREAK_D
	
	_TRISE6 = 0;// DIR_G
	_TRISC3 = 0;// DIR_D

	// Init des freins
    BRAKE_G = 0;
    BRAKE_D  = 0;
	
    // PTCON & PTPER
    PTCON           = 0x0000;           // Free Running, no pre/postscale
	PTPER           = PTP;             // Frzquence de la PWM (1600 => Fpwm = 20kHz)
	
	// PWCON5
	PWMCON5bits.FLTIEN = 0;
	PWMCON5bits.CLIEN = 0;
	PWMCON5bits.TRGIEN = 0;
	PWMCON5bits.ITB = 0;
	PWMCON5bits.MDCS = 0;
	PWMCON5bits.DTC = 0b10;
	PWMCON5bits.MTBS = 0;
	PWMCON5bits.XPRES = 0;
	PWMCON5bits.IUE = 0;
	
	// PWCON4
	PWMCON4bits.IUE = 1;                // Immediate update of PWM enabled
	
	// IOCON5
	IOCON5bits.PENH = 1;
	IOCON5bits.PENL = 0;
	IOCON5bits.POLH = 0;
	IOCON5bits.PMOD = 0b11;
	IOCON5bits.OVRENL = 0;
	IOCON5bits.SWAP = 0;
	IOCON5bits.OSYNC = 1;
	
	// IOCON4
	IOCON4bits.PENH = 1;
	IOCON4bits.PENL = 0;
	IOCON4bits.POLH = 0;
	IOCON4bits.PMOD = 0b11;
	IOCON4bits.OVRENL = 0;
	IOCON4bits.SWAP = 0;
	IOCON4bits.OSYNC = 1;
    
	// Initialisaiton du duty cycle
    PWM_G = PWM_D   = 0;               
    DIR_G = DIR_D   = 0;

    // Activation du signal PWM
    PTCONbits.PTEN  = 1;
	
	// Initialiser les QUI
	qeiInit ();
	
	//Configurer les variables codeurs
	codeurDroit.oldCodeur   = 0x7FFFFFFF  ;
	codeurGauche.oldCodeur  = 0x7FFFFFFF  ;
}


void qeiInit ()
{
	//Init for the remamapable pins
	_QEA1R = 125;
	_QEB1R = 127;
	_QEA2R = 126;
	_QEB2R = 124;
	
	QEI1CONbits.QEIEN = 1; //Enable QEI
	QEI1CONbits.QEISIDL = 0; // Don't care idle mode
	QEI1CONbits.PIMOD = 0b000; // Position init not affected by index
	QEI1CONbits.IMV = 0b00;	//Index input event don't match with position counter
	QEI1CONbits.INTDIV = 0b000; // No presclale
	QEI1CONbits.CNTPOL = 1; //Count in negative
	QEI1CONbits.GATEN = 0; // No external count enable bit
	QEI1CONbits.CCM = 0b00; // Select QEI mode Count
	
	QEI1IOCbits.QCAPEN = 0;
	QEI1IOCbits.FLTREN = 0; //digital filter disabled
	QEI1IOCbits.QFDIV = 0b000;
	QEI1IOCbits.OUTFNC = 0b00;
	QEI1IOCbits.SWPAB = 0;
	QEI1IOCbits.HOMPOL = 0;
	QEI1IOCbits.IDXPOL = 0;
	QEI1IOCbits.QEBPOL = 0;
	QEI1IOCbits.QEAPOL = 0;
	
	QEI1STATbits.PCHEQIEN = 0;
	QEI1STATbits.PCLEQIEN = 0;
	QEI1STATbits.POSOVIEN = 0;
	QEI1STATbits.PCIIEN = 0;
	
	QEI2CONbits.QEIEN = 1; //Enable QEI
	QEI2CONbits.QEISIDL = 0; // Don't care idle mode
	QEI2CONbits.PIMOD = 0b000; // Position init not affected by index
	QEI2CONbits.IMV = 0b00;	//Index input event don't match with position counter
	QEI2CONbits.INTDIV = 0b000; // No presclale
	QEI2CONbits.CNTPOL = 0; //Count in positive
	QEI2CONbits.GATEN = 0; // No external count enable bit
	QEI2CONbits.CCM = 0b00; // Select QEI mode Count
	
	QEI2IOCbits.QCAPEN = 0;
	QEI2IOCbits.FLTREN = 0; //digital filter disabled
	QEI2IOCbits.QFDIV = 0b000;
	QEI2IOCbits.OUTFNC = 0b00;
	QEI2IOCbits.SWPAB = 0;
	QEI2IOCbits.HOMPOL = 0;
	QEI2IOCbits.IDXPOL = 0;
	QEI2IOCbits.QEBPOL = 0;
	QEI2IOCbits.QEAPOL = 0;
	
	QEI2STATbits.PCHEQIEN = 0;
	QEI2STATbits.PCLEQIEN = 0;
	QEI2STATbits.POSOVIEN = 0;
	QEI2STATbits.PCIIEN = 0;
	
	//Valeurs intitiales 
	POS1CNTL = 0xFFFF;
	POS1CNTH = 0x7fff;
	
	POS2CNTL = 0xFFFF;
	POS2CNTH = 0x7fff;
}


//Récupère la valeure renvoyée par les codeurs
inline void valeurCodeurs()
{
	//Variables
	uint32 valQEIL1, valQEIH1, valQEIL2, valQEIH2 ;
	
	// Valeur codeur droit
	valQEIL1 = POS1CNTL;
	valQEIH1 = POS1HLD;
	codeurGauche.newCodeur =  (valQEIH1 << 16) | valQEIL1;

	// Valeur codeur gauche
	valQEIL2 = POS2CNTL;
	valQEIH2 = POS2HLD;
	codeurDroit.newCodeur =  (valQEIH2 << 16) | valQEIL2;	
}


// Envoyer les ordres aux moteurs
inline void applicationAssPosMoteurs(int32 ordreDistance, int32 ordreAngle)
{
    //Calcule les ordres réels grace aux ordres polaires
	int32 PWMGauche = ordreDistance - ordreAngle;
	int32 PWMDroite  = ordreDistance + ordreAngle;

	//Retier les freins
    BRAKE_G         = 0;
    BRAKE_D         = 0;

    //Le sens
	DIR_G           = SENS (PWMGauche);
	DIR_D           = SENS (PWMDroite);

    //La valeur
    PWM_G           = ABS (PWMGauche);
    PWM_D           = ABS (PWMDroite);
}

// Envoyer les ordres aux moteurs
inline void applicationAssCirMoteurs(int32 PWMGauche, int32 PWMDroite)
{
	//Retier les freins
    BRAKE_G         = 0;
    BRAKE_D         = 0;

    //Le sens
	DIR_G           = SENS (PWMGauche);
	DIR_D           = SENS (PWMDroite);

    //La valeur
    PWM_G           = ABS (PWMGauche);
    PWM_D           = ABS (PWMDroite);
}
