#ifndef MOTEUR_H_INCLUDED
#define MOTEUR_H_INCLUDED

//Libraries
#include "configuration.h"
#include "math.h"
#include "debugger.h"

//Constantes
#define PWMPRE		1
#define FPWM		20000
#define PTP (FOSC / (FPWM * PWMPRE))

//Pins
#define DIR_D 		LATEbits.LATE6
#define DIR_G 		LATCbits.LATC3

#define BRAKE_D 	LATCbits.LATC2
#define BRAKE_G 	LATEbits.LATE5

#define PWM_D 		PDC4
#define PWM_G 		PDC6

//Structures

typedef struct _Codeur {
    uint32 oldCodeur;
    uint32 newCodeur;
    int16 variation;
    uint32 somme;


} Codeur;

//Prototype

//Prototypes
void moteurInit();
void qeiInit();
inline void valeurCodeurs();
void encodersDebug();
inline void applicationAssPosMoteurs(float ordreDistance, float ordreAngle);
inline void applicationAssCirMoteurs(int32 PWMGauche, int32 PWMDroite);
void mettreFrein();
void enleverFrein();

float codeurGetDistance();
float codeurGetDroit();
float codeurGetGauche();

float codeurGetAngle();



//Variables
extern Codeur codeurGauche;
extern Codeur codeurDroit;

#endif // MOTEUR_H_INCLUDED
