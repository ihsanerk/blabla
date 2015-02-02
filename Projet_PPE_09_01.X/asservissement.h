#ifndef ASSERVISSEMENT_H_INCLUDED
#define ASSERVISSEMENT_H_INCLUDED

//Libraries
#include "moteur.h"
#include "math.h"

//Pines

//Structures

typedef struct _Asservissement {
    int32 variation; //Variation entre les valeurs actuelles et les anciainnes
    int32 variationSomme;
    int32 ordre; //Consigne donn»au robot ? la fin du threas
    int32 erreur;
    int32 oldOrdre; //Pr»c»dente consigne du robot
    int32 erreurTolerance; //Tolerance par rapport ? l'erreur

    int32 coefDerive;
    int32 coefDeriveNeg; //Lorsque le robot va en marche arriÀre
    int32 coefProportionnel;
    int32 coefPropNeg; //Lorsque le robot va en marche arriÀre

    int32 VMax; //Vitesse max
    int32 Vmin; //Vitesse min

    BOOL enable;
    int32 coefAcceleration;

} Asservissement;


//Prototypes
void asservissementPolInit();
void asservissementCircuInit();
void asservissementInit();

inline void polaire();
inline void circulaire();
inline void pid(Asservissement * ass, BOOL ralentir); //Calcule la nouvelle consigne
void limite(Asservissement * ass, BOOL ralentir); //Seuillage

void asservissementPolaire(BOOL avance);
void asservissementCirculaire();
void erreursReInit();
void erreurMemory();
void sommeVariations();

//Variables
extern Asservissement angle; //Angle pour l'asserivssement polaire
extern Asservissement distance; //Distance pour l'asserivssement polaire

extern Asservissement roueDroite; //Pour asservissement circulaire
extern Asservissement roueGauche;

#endif // ASSERVISSEMENT_H_INCLUDED
