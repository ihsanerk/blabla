#ifndef MOTEUR_H_INCLUDED
#define MOTEUR_H_INCLUDED

//Libraries
#include "Definitions.h"

//Constantes
#define PWMPRE		1
#define FPWM		20000 
#define PTP			(FOSC / (FPWM * PWMPRE))

//Pins
#define DIR_D 		LATCbits.LATC3
#define DIR_G 		LATEbits.LATE6

#define BRAKE_G 	LATEbits.LATE4
#define BRAKE_D 	LATCbits.LATC1

#define PWM_D 		PDC5
#define PWM_G 		PDC4

//Structures
typedef struct _Codeur
{
		uint32            oldCodeur  ;
		uint32            newCodeur  ;
		int32             variation  ;

}Codeur;

//Prototype

//Prototypes
void 					moteurInit ();
void 					qeiInit ();
inline void 			valeurCodeurs() ;
inline void 			applicationAssPosMoteurs(int32 ordreDistance, int32 ordreAngle);
inline void 			applicationAssCirMoteurs(int32 PWMGauche, int32 PWMDroite);

//Variables
extern Codeur 			codeurGauche	;
extern Codeur 			codeurDroit		;

#endif // MOTEUR_H_INCLUDED
