/* 
 * File:   asservissement.h
 * Author: guillaume
 *
 * Created on 16 janvier 2015, 14:44
 */

#ifndef ASSERVISSEMENT_H
#define	ASSERVISSEMENT_H

//Libraries
#include "definition.h"
#include "moteur.h"
#include "math.h"

//Pines

//Structures

typedef struct _Asservissement {
    float variation; //Variation entre les valeurs actuelles et les anciainnes
    float variationSomme;
    float ordre; //Consigne donn»au robot ? la fin du threas
    float erreur;
    float oldOrdre; //Pr»c»dente consigne du robot
    float erreurTolerance; //Tolerance par rapport ? l'erreur

    float coefDerive;
    float coefDeriveNeg; //Lorsque le robot va en marche arriÀre
    float coefProportionnel;
    float coefPropNeg; //Lorsque le robot va en marche arriÀre

    float VMax; //Vitesse max
    float Vmin; //Vitesse min

    BOOL enable;
    float coefAcceleration;

} Asservissement;


//Prototypes
void asservissementPolInit();
void asservissementInit();

inline void polaire();
inline void pid(Asservissement * ass, BOOL ralentir); //Calcule la nouvelle consigne

void asservissementPolaire(BOOL avance);

//Variables
extern Asservissement angle; //Angle pour l'asserivssement polaire
extern Asservissement distance; //Distance pour l'asserivssement polaire

extern Asservissement roueDroite; //Pour asservissement circulaire
extern Asservissement roueGauche;

#endif	/* ASSERVISSEMENT_H */

