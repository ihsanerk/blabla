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
    long variation; //Variation entre les valeurs actuelles et les anciainnes
    long variationSomme;
    long ordre; //Consigne donn»au robot ? la fin du threas
    long erreur;
    long oldOrdre; //Pr»c»dente consigne du robot
    long erreurTolerance; //Tolerance par rapport ? l'erreur

    long coefDerive;
    long coefDeriveNeg; //Lorsque le robot va en marche arriÀre
    long coefProportionnel;
    long coefPropNeg; //Lorsque le robot va en marche arriÀre

    long VMax; //Vitesse max
    long Vmin; //Vitesse min

    bool enable;
    long coefAcceleration;

} Asservissement;


//Prototypes
void asservissementPolInit();
void asservissementCircuInit();
void asservissementInit();

inline void polaire();
inline void circulaire();
inline void pid(Asservissement * ass, bool ralentir); //Calcule la nouvelle consigne
void limite(Asservissement * ass, bool ralentir); //Seuillage

void asservissementPolaire(bool avance);
void asservissementCirculaire();
void erreursReInit();
void erreurMemory();
void sommeVariations();

//Variables
extern Asservissement angle; //Angle pour l'asserivssement polaire
extern Asservissement distance; //Distance pour l'asserivssement polaire

extern Asservissement roueDroite; //Pour asservissement circulaire
extern Asservissement roueGauche;

#endif	/* ASSERVISSEMENT_H */

