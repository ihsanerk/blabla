#include  "controleur.h"

//Variables
Position Gali_current = {0.0f, 0.0f, 0.0f};
Position Gali_objectif = {0.0f, 0.0f, 0.0f};
float position_x = 0.0f;
float position_y = 0.0f;
float position_angle = 0.0f;
float vitesse = 1.0f;

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
    float variation_longueur = 0.0f;
    float variation_angle = 0.0f;

    //Pour calculer l'erreur entre la position réel du Robot et l'objetcif
    float erreur_x = 0.0f;
    float erreur_y = 0.0f;
    float erreur_angle = 0.0f;

    //Pour corriger les erreurs
    float current_erreur_longueur = 0.0f;
    float current_erreur_angle = 0.0f;

    //Pour reculer
    float Avance = 1.0f;




    //On récupère la variation des
    valeurCodeurs();

    variation_longueur = codeurGetDistance();
    variation_angle = codeurGetAngle();
   //variation_angle=0.0f;


    //Calcul des positions réelles
    if (ABS(variation_angle) >0.1f) {
        position_angle = Gali_current.angle + variation_angle;
        Gali_current.angle = position_angle;

    }
    if (ABS(variation_longueur) > 0.001) {

        position_x += -variation_longueur * sin(variation_angle*0.0174532925f);
        position_y += variation_longueur * cos(variation_angle*0.0174532925f);

        Gali_current.x = position_x;
        Gali_current.y = position_y;

    }

    //Calcule des erreurs
    erreur_x = Gali_objectif.x - position_x;
    erreur_y = Gali_objectif.y - position_y;
    erreur_angle = Gali_objectif.angle - position_angle;

    if (erreur_y > 0) Avance = -1.0f;
    else Avance = 1.0f;


    //Calcule pour corriger les erreurs
    if (ABS(erreur_x) < 0.001f )
    {
    erreur_x=0.0f;
    }
    if(ABS(erreur_y) < 0.001f)
    {
     erreur_y=0.0f;
    }
    if(ABS(erreur_angle) <0.1f)
    {
      erreur_angle=0.0f;
    }
    
        current_erreur_longueur = sqrt(erreur_x * erreur_x + erreur_y * erreur_y);
        current_erreur_angle =  Gali_current.angle+erreur_angle;
        



    //On envoi la consigne au moteur
    applicationAssPosMoteurs(Avance*current_erreur_longueur, current_erreur_angle);

}

BOOL PositionParRapportObjectif() {
    if (ABS(Gali_current.x - Gali_objectif.x) > 0.002f && ABS(Gali_current.y - Gali_objectif.y) > 0.002f && ABS(Gali_current.angle - Gali_objectif.angle) < 0.01f) {
        return TRUE;
    }
    return FALSE;
}

float NormaliserAngle(float angle) {
    //On convertie l'angle en radian
    angle=angle*0.0174532925f;

    //On normalise l'angle
    angle = fmod(angle, (2.0f * PI));

    if (angle > PI) {
        angle = angle - 2.0f * PI;
    }
    return angle/0.0174532925f; // Pour le mettre en degré
}

void afficher_position() {
    //StringFormatted("Position x =%1.3f  y = %1.3f  angle = %1.3f\n",position_x, position_y,position_angle);
    StringFormatted(" = %f\n", position_x);
}

void afficher_objectif() {
    StringFormatted("Objectif x =%1.3f  y = %1.3f  angle = %1.3f\n", Gali_objectif.x, Gali_objectif.y, Gali_objectif.angle);
}

void afficher_Gali() {
    StringFormatted("Gali x =%1.3f  y = %1.3f  angle = %1.3f\n", Gali_current.x, Gali_current.y, Gali_current.angle);

}
