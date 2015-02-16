// Library
#include "moteur.h"

//Variables
Codeur codeurGauche;
Codeur codeurDroit;

// Initialisation

void moteurInit() {
    // Configuration des pins
    TRISCbits.TRISC4 = 0; // PWM_G
    TRISEbits.TRISE7 = 0; // PWM_D

    TRISEbits.TRISE5 = 0; // BREAK_D
    TRISCbits.TRISC2 = 0; // BREAK_G

    TRISEbits.TRISE6 = 0; // DIR_D
    TRISCbits.TRISC3 = 0; // DIR_G

    // Init des freins
    BRAKE_G = 0;
    BRAKE_D = 0;

    // PTCON & PTPER
    PTCON = 0x0000; // Free Running, no pre/postscale
    PTPER = PTP; // Frzquence de la PWM (1600 => Fpwm = 20kHz)


    // PWCON6
    PWMCON6bits.FLTIEN = 0;
    PWMCON6bits.CLIEN = 0;
    PWMCON6bits.TRGIEN = 0;
    PWMCON6bits.ITB = 0;
    PWMCON6bits.MDCS = 0;
    PWMCON6bits.DTC = 0b10;
    PWMCON6bits.MTBS = 0;
    PWMCON6bits.XPRES = 0;
    PWMCON6bits.IUE = 0; //Ancienne valeur 0;

    // PWCON4
    PWMCON4bits.IUE = 1; // Immediate update of PWM enabled

    // IOCON6
    IOCON6bits.PENH = 1;
    IOCON6bits.PENL = 0;
    IOCON6bits.POLH = 0;
    IOCON6bits.PMOD = 0b11;
    IOCON6bits.OVRENL = 0;
    IOCON6bits.SWAP = 0;
    IOCON6bits.OSYNC = 1;

    // IOCON4
    IOCON4bits.PENH = 1;
    IOCON4bits.PENL = 0;
    IOCON4bits.POLH = 0;
    IOCON4bits.PMOD = 0b11;
    IOCON4bits.OVRENL = 0;
    IOCON4bits.SWAP = 0;
    IOCON4bits.OSYNC = 1;

    // Initialisaiton du duty cycle
    PWM_G = PWM_D = 0;
    DIR_G = DIR_D = 0;

    // Activation du signal PWM
    PTCONbits.PTEN = 1;

    //Initialise les encodeurs
    qeiInit();


}

void qeiInit() {
    //Init for the remamapable pins
    // Encoders (right:E1, left:E2)
    RPINR14bits.QEA1R = 81; //E1 CHA
    RPINR14bits.QEB1R = 126; //E1 CHB

    RPINR16bits.QEA2R = 124; //E2 CHA
    RPINR16bits.QEB2R = 125; //E2 CHB

    QEI1CONbits.QEIEN = 1; //Enable QEI
    QEI1CONbits.QEISIDL = 0; // Don't care idle mode
    QEI1CONbits.PIMOD = 0b000; // Position init not affected by index
    QEI1CONbits.IMV = 0b00; //Index input event don't match with position counter
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
    QEI2CONbits.IMV = 0b00; //Index input event don't match with position counter
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
    POS1CNTL = (uint16)0xFFFF;
    POS1CNTH = (uint16)0x0000;

    POS2CNTL = (uint16)0xFFFF;
    POS2CNTH = (uint16)0x0000;
}


//R»cupÀre la valeure renvoy»e par les codeurs

inline void valeurCodeurs() {
    //Variables
    uint32 valQEIL1, valQEIH1, valQEIL2, valQEIH2;

    // Valeur codeur droit
    valQEIL1 = POS1CNTL;
    valQEIH1 = POS1HLD;
    codeurGauche.newCodeur = (valQEIH1 << 16) | valQEIL1;
    codeurGauche.variation = codeurGauche.newCodeur - codeurGauche.oldCodeur;
    codeurGauche.oldCodeur = codeurGauche.newCodeur;
    // Valeur codeur gauche
    valQEIL2 = POS2CNTL;
    valQEIH2 = POS2HLD;
    codeurDroit.newCodeur = (valQEIH2 << 16) | valQEIL2;
    codeurDroit.variation = codeurDroit.newCodeur - codeurDroit.oldCodeur;
    codeurDroit.oldCodeur = codeurDroit.newCodeur;
}

float codeurGetDistance() {
    return (codeurGauche.variation * 0.817e-5f + codeurDroit.variation * 0.817e-5f)/2.0f;
}

float codeurGetAngle() {
    return (codeurGauche.variation * 0.840e-4f - codeurDroit.variation * 0.840e-4f)/2.0f;
}

void encodersDebug() {
    StringFormatted("Valeur du codeur Gauche:%d Variation Gauche :%d \n", codeurGauche.newCodeur, codeurGauche.variation);
    StringFormatted("Valeur du codeur Droit:%d Variation Droit :%d \n", codeurDroit.newCodeur, codeurDroit.variation);
}

// Envoyer les ordres aux moteurs

inline void applicationAssPosMoteurs(float ordreDistance, float ordreAngle) {
    //Calcule les ordres rÈels grace aux ordres polaires
    float OrdreGauche = ordreDistance; //0.7f * ordreDistance - 0.3f * ordreAngle;
    float OrdreDroit = ordreDistance;  //0.7f * ordreDistance + 0.3f * ordreAngle;
    int32 PWMGauche;
    int32 PWMDroite;

    //Retier les freins
    enleverFrein();

    //Afficher un message
    //StringFormatted("Valeur de l'ordre Gauche:%f l'ordre Droit :%f \n", OrdreGauche, OrdreDroit);

    //On vÈrifie que la valeur n'est pas nul
    if (OrdreGauche != 0.0f) {
        PWMGauche = 2500 * ABS(OrdreGauche) + 250;
    } else PWMGauche = 0;

    if (OrdreDroit != 0.0f) {
        PWMDroite = 2500 * ABS(OrdreDroit) + 250;
    } else PWMDroite = 0;

StringFormatted("%d",OrdreDroit);

    //Le sens
    DIR_G = SENS(-1.0f* PWMGauche);
    DIR_D = SENS(PWMDroite);

    //La valeur
    PWM_G = ABS(PWMGauche);
    PWM_D = ABS(PWMDroite);
}





// Envoyer les ordres aux moteurs

inline void applicationAssCirMoteurs(int32 PWMGauche, int32 PWMDroite) {
    //Retier les freins
    BRAKE_G = 0;
    BRAKE_D = 0;

    //Le sens
    DIR_G = SENS(PWMGauche);
    DIR_D = SENS(PWMDroite);

    //La valeur
    PWM_G = ABS(PWMGauche);
    PWM_D = ABS(PWMDroite);
}

void mettreFrein() {
    BRAKE_G = 1;
    BRAKE_D = 1;
}

void enleverFrein() {
    BRAKE_G = 0;
    BRAKE_D = 0;
}