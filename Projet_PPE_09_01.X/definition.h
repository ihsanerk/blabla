#ifndef DEFINITION_H
#define	DEFINITION_H

//Définition des variables globales
#define FP 51000000
#define BAUDRATE 9600
#define BRGVAL ((FP/BAUDRATE)/16) - 1

#define _XTAL_FREQ 24000000
#define FOSC (119762500UL)
#define FCY (FOSC/2)


#endif	/* DEFINITION_H */

