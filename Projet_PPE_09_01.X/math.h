/* 
 * File:   math.h
 * Author: guillaume
 *
 * Created on 16 janvier 2015, 14:54
 */

#ifndef MATH_H
#define	MATH_H

//LIBRARIES
#include <p33Exxxx.h>
#include <libpic30.h>
#include <math.h>

//GENERAL CONFIGURATION
#define FXTAL 8000000
#define PLL 8
#define BAUD 9600
#define FINAL_BAUD (((FCY/16)/BAUD)-1)

#define PRESCALER	8	// Modifier T2CONbits.TCKPS
#define FOVERFLOW	1000
#define PR	(FCY / (PRESCALER * FOVERFLOW))

//Définition pour l'UART
// Crytal is 24MHz.
// Configure the oscillator to operate the device at 51 MIPS using PLL
#define _XTAL_FREQ  24000000
#define FOSC    (102000000)
#define FCY     (FOSC/2)

//Définition pour les ADC
// Number of channels on device
#define ADC_MAX 32


//CONSTANT DEFINITION
#define FALSE               0
#define TRUE                1
//#define NULL                ((void *)0)
#define	PI                  3.14159265358979323846f

//TRANSLATORS CONSTANT
#define MIN(a, b)  (   ( (a) < (b) ) ?  (a) : (b)   )
#define MAX(a, b)  (   ( (a) > (b) ) ?  (a) : (b)   )
#define ABS(a)     (   ( (a) <  0  ) ? -(a) : (a)   )
#define SIGN(a)    (   ( (a) <  0  ) ?  -1  :  1    )
#define SIGN0(a)   (   ( (a) <= 0  ) ? (( (a) == 0 ) ? 0 : -1 ) :  1    )
#define SENS(a)    (   ( (a) <  0  ) ?   0  :  1    )

//DELAY CONSTANT
#define delay_ms(A)         __delay32((unsigned long)(A)*(FCY/1000))
#define delay_us(A)         __delay32((unsigned long)(A)*(FCY/1000000))

//TYPE DEFINITION
typedef signed char int8;
typedef signed int int16;
typedef signed long int32;
typedef signed long long int64;

typedef unsigned char uint8;
typedef unsigned int uint16;
typedef unsigned long uint32;
typedef unsigned long long uint64;

typedef signed char BOOL;


//Constantes
#define CPA         20			//Coefficient proportionel pour l'angle
#define CDA        	-300		//Coefficient dÈrivÈ pour l'angle
#define AT          100			//Angle tolÈrance
#define AA          10			//Angle accÈlÈration

#define CP          20			//Coefficient proportionel
#define CD          -595		//Coefficient dÈrivÈ
#define DT          100			//Distance tolÈrance
#define DA          10			//Distance accÈlÈration

#define VAMAX       1000		//Vitesse angulaire maximale (max physique 1600)
#define VAMIN       300			//Vitesse angulaire minimale

#define VMAX       	800			//Vitesse maximale (max physique 1600)
#define VMIN        250			//Vitesse minimale

#define IMP_M       204805		//Impulsions par metre : moitiÈ du rÈel (testÈ sur 1M20 pour 3mm)
#define IMP_T       217237		//Impulsions par tour (prÈcis jusqu'? 100 tours, 3d d'erreur) pas assez

extern int8 team;


#endif	/* MATH_H */

