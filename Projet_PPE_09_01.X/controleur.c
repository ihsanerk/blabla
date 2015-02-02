#include  "controleur.h"

//Variables
Position Gali_current={0.0f,0.0f,0.0f};
Position Gali_objectif={0.0f,0.0f,0.0f};

//Fonctions

void SetPositionObjectif(float x, float y, float angle) {
    Gali_objectif.x = x;
    Gali_objectif.y = y;
    Gali_objectif.angle = angle;
}

void SetPositionCurrent(float x, float y, float angle) {

    Gali_current.x = x;
    Gali_current.y = y;
    Gali_current.angle = angle;
}

void UpdatePosition() {
    //Ressources
    //Pour récupèrer la variation des encodeurs
    float variation_longueur=0.0f;
    float variation_angle=0.0f;
    //Pour déterminer la postion réel du Robot
    float position_x=0.0f;
    float position_y=0.0f;
    float position_angle=0.0f;
    //Pour calculer l'erreur entre la position réel du Robot et l'objetcif
    float erreur_x=0.0f;
    float erreur_y=0.0f;

    //Pour corriger les erreurs
    float current_erreur_longueur=0.0f;
    float current_erreur_angle=0.0f;

    //On récupère la variation des encodeurs
    valeurCodeurs();
    variation_longueur = codeurGetDistance();
    variation_angle = codeurGetAngle();

    //Calcule des positions réelles
    position_angle = NormaliserAngle(Gali_current.angle + variation_angle);
    position_x += variation_longueur * cos(position_angle);
    position_y += variation_longueur * sin(position_angle);

    //Calcule des erreurs
    erreur_x=Gali_objectif.x - position_x;
    erreur_y=Gali_objectif.y - position_y;

    //Calcule pour corriger les erreurs
    if (ABS(erreur_x) < 1e-6f && ABS(erreur_y) < 1e-6f) {
        current_erreur_longueur = 0.0f;
        current_erreur_angle = 0.0f;
    } else {
        current_erreur_longueur = sqrt(erreur_x * erreur_x + erreur_y * erreur_y);
        current_erreur_angle = atan2(erreur_y, erreur_x);
    }

    //On envoi la consigne au moteur
    applicationAssPosMoteurs(current_erreur_longueur,current_erreur_angle);

}

BOOL PositionParRapportObjectif() {
    if(ABS(Gali_current.x - Gali_objectif.x) < 0.02f && ABS(Gali_current.y - Gali_objectif.y) < 0.02f && ABS(NormaliserAngle(Gali_current.angle - Gali_objectif.angle)) < PI/16) {
        return TRUE;
    }
    return FALSE;
}

float NormaliserAngle(float angle) {
    //On normalise l'angle
    angle = fmod(angle, (2.0f * PI));
    if (angle > PI) {
        angle = angle - 2.0f * PI;
    }
    return angle;
}