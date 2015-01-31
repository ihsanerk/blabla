//Libraries
#include "asservissement.h"

//Variables
Asservissement angle;
Asservissement distance;
Asservissement roueDroite;
Asservissement roueGauche;

void asservissementInit() {
    //Initialisation asservissements
    asservissementPolInit();
    asservissementCircuInit();

    //Initialise les moteurs
    moteurInit();
}

void asservissementPolInit() {
    //Initialisation de "angle"
    angle.coefDerive = 0.0f;
    angle.coefDeriveNeg = 0.0f;
    angle.coefProportionnel = 5.0f;
    angle.coefPropNeg = 5.0f;
    angle.ordre = 0;
    angle.oldOrdre = 0;
    angle.erreur = 0;
    angle.erreurTolerance = 1e-6f;
    angle.variation = 0;
    angle.variationSomme = 0;
    angle.enable = TRUE;

    //Initialisation de "distance"
    distance.coefDerive = 0.0f;
    distance.coefDeriveNeg = 0.0f;
    distance.coefProportionnel = 15.0f;
    distance.coefPropNeg = 15.0f;
    distance.ordre = 0;
    distance.oldOrdre = 0;
    distance.erreur = 0;
    distance.erreurTolerance = 1e-6f;
    distance.variation = 0;
    distance.variationSomme = 0;
    distance.enable = TRUE;

    //Initialisation des  valeurs max
    distance.VMax = 800;
    distance.Vmin = 250;

    angle.VMax = 1000;
    angle.Vmin = 300;

    angle.coefAcceleration = 10;
    distance.coefAcceleration = 10;
}



inline void pid(Asservissement * ass, BOOL ralentir) {
    //Si l'erreur est inf»rieure au seuil de tol»rance l'ordre a »t» atteint
    if ((ABS(ass->erreur)) < (ass->erreurTolerance))
        ass->ordre = 0;

        //Sinon continuer d'ex»cuter l'ordre en cours
    else {
        //Calculer le nouvel ordre
        ass->ordre = ((ass->erreur * ass->coefProportionnel) / 100) + ((ass->coefDerive * ass->variation) / 100);

        //Seuillage
        limite(ass, ralentir);
    }
}

//Calcule le d»calage par rapport ? la consigne ? atteindre

inline void polaire() {
    //Variation de chaque roue depuis le dernier check
    codeurGauche.variation = codeurGauche.newCodeur - codeurGauche.oldCodeur;
    codeurDroit.variation = codeurDroit.newCodeur - codeurDroit.oldCodeur;

    // Mise ? niveau (? mettre en commentaire si n»cessaire
    //codeurDroit.variation = ((int32) (codeurDroit.variation * 101500) / 100000);
    //101430 droite,  gauche 101520

    //Mise a jour valeurs asservissement
    distance.variation = (codeurDroit.variation + codeurGauche.variation);
    angle.variation = codeurDroit.variation - codeurGauche.variation;

    //Mettre ? jour les anciennes valeurs
    codeurGauche.oldCodeur = codeurGauche.newCodeur;
    codeurDroit.oldCodeur = codeurDroit.newCodeur;

    //Mettre ? jour l'erreur restante (donc le d»calage par rapport ? la consigne ? atteindre)
    distance.erreur -= distance.variation;
    angle.erreur -= angle.variation;

    // Somme des variations
    angle.variationSomme += angle.variation;
    distance.variationSomme += distance.variation;
}


//Gestion de l'asservissement du robot

void asservissementPolaire(BOOL avance) {
    //On obtiens les valeurs des codeurs
    valeurCodeurs();

    //On convertit ces valeurs en polaire (angle + distance)
    polaire();

    //Appliquer le PID
    if (angle.enable) {
        if (!avance) pid(&angle, TRUE);
        else pid(&angle, FALSE);
    }
    if (distance.enable) {
        if (avance) pid(&distance, TRUE);
        else pid(&distance, FALSE);
    }

    //Envoyer la consigne au moteur
    applicationAssPosMoteurs(distance.ordre, angle.ordre);
}
