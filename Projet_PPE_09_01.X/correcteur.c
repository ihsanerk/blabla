#include "correcteur.h"

//Ressources
//La position actuelles
float position_x = 0.0f;
float position_y = 0.0f;
float position_angle = 0.0f;
//L'objectif de destination
float objectif_x = 0.0f;
float objectif_y = 0.0f;
float objectif_angle = 0.0f;
//Coeficient
float angle[4];
float r[4];
float coeff[4];
BOOL isAngleAbsolute = FALSE;

//Fonction pour Définir les positions de l'objectif
void SetPositionObjectif(float x, float y, float angle) {
    objectif_x = x;
    objectif_y = y;
    objectif_angle = normalAngle(angle);
}

//Fonction pour actualiser les postions actuelles
void trackerSetPosition(float new_position_x, float new_position_y, float new_position_angle) {
    position_x = new_position_x;
    position_y = new_position_y;
    position_angle = normalAngle(new_position_angle);
}

//Fonction pour actualiser les déplacements
void trackerUpdate() {

    ////////////////
    //Ressources //
    ///////////////

    //Pour les variations
    float variation_length;
    float variation_angle;
    //Pour les erreurs
    float current_error_length;
    float current_error_angle;
    //Pour les corrections après erreur
    float current_correction_length;
    float current_correction_angle;
    //Les erreues en X et Y
    float error_x;
    float error_y;
    //Pour parcourir les différents tableau
    int i;


    //Initialisation
    encodersFetch(); // On récupère la valeur des encodeurs des les registres
    //On récupère la variation de longueur
    variation_length = encodersGetLengthVariation();
    //On récupère la variation d'angle
    variation_angle = encodersGetAngleVariation();

    //On calcule les positions de l'angle, X et Y
    position_angle = normalAngle(position_angle + variation_angle);
    position_x += variation_length * cos(position_angle);
    position_y += variation_length * sin(position_angle);

    //On calcule les erreurs entre l'objectif et la position réel de l'encodeur
    error_x = objectif_x - position_x;
    error_y = objectif_y - position_y;

    //Si l'erreur est minime, on ne modifie pas la trajectoire
    if(ABS(error_x) < 1e-6f && ABS(error_y) < 1e-6f) {
        current_error_length = 0.0f;
        current_error_angle = 0.0f;
    }
    else { // Sinon on calcule la nouvelle trajectoire
        // Formule : (X^2+Y^2)^1/2
        current_error_length = sqrt(error_x * error_x + error_y * error_y);
        current_error_angle = atan2(error_y, error_x);
    }

    //On réinitialise les valeurs du tableau à zéro
    for (i=0; i<4; i++){
        angle[i] = 0.0f;
        r[i] = 0.0f;
        coeff[i] = 0.25f;
    }

    //On actualise la nouvelle destination
    realPoint(error_x, error_y);

    //Onc actualise la position fictive
    fictivePoint();


        // Si l'erreur est trop importante
        if(ABS(current_error_length) > 0.02f){
            // Si l'objectif n'est pas en face, on tourne
            if(ABS(normalAngle(current_error_angle - position_angle)) > (PI*1.0f/10.0f)
            && ABS(normalAngle(current_error_angle - position_angle)) < (PI*9.0f/10.0f))
            {
                correctionLookAtObjective(current_error_angle, &current_correction_length, &current_correction_angle);
                current_correction_angle = normalAngle(current_correction_angle);
            }
            // Else, go for it
            else {
                correctionGoStraight(current_error_length, current_error_angle, &current_correction_length, &current_correction_angle);
                current_correction_angle = normalAngle(current_correction_angle);
            }
        }
        // Else ajust the orientation to the objective one
        else {
            correctionObjectiveOrientation(current_error_length, current_error_angle, &current_correction_length, &current_correction_angle);
                current_correction_angle = normalAngle(current_correction_angle);
        }
        // On doit ici actualiser la consigne des moteurs.

    //controllerUpdate(current_correction_length, current_correction_angle);
}

void trackerDebugPosition() {
    StringFormatted("Pos :(%1.3f %1.3f %1.3f) ", position_x, position_y, position_angle);
}

void trackerDebugObjective() {
    StringFormatted("Obj :(%1.3f %1.3f %1.3f) ", objectif_x, objectif_y, objectif_angle);
}

void fictivePoint (){
    angle[1] = objectif_angle-PI/2.0f;
    r[1] = (objectif_x - position_x) * sin(objectif_angle)-(objectif_y - position_y) * cos(objectif_angle);
}

void realPoint(float error_x, float error_y){

    if(error_x < 1e-6f && error_y < 1e-6f) {
        r[0] = 10.0f;
        angle[0] = 0.0f;
    }
    else {
        r[0] = 1/(error_x) * sin(objectif_angle)-(error_y) * cos(objectif_angle);
        angle[0] = atan2(error_x, error_y);
    }
}


float computeNewErrorAngle(){
    float up_fraction = 0.0f;
    float down_fraction = 0.0f;
    int i=0;
    for(i=0;i<4;i++){
        up_fraction += coeff[i]*r[i]*angle[i];
        down_fraction += coeff[i]*r[i];
    }

    if(down_fraction < 1e-6f)
        return 0;
    else
        return position_angle-up_fraction/down_fraction;
}

//Fonction pour normaliser l'angle
float normalAngle(float angle) {
    angle = fmod(angle, (2.0f * PI));
    if(angle > PI) {
        angle = angle - 2.0f * PI;
    }
    return angle;
}

void correctionLookAtObjective(float current_error_angle, __eds__ float *current_correction_length, __eds__ float *current_correction_angle) {
    if(normalAngle(current_error_angle - position_angle) > PI/2.0f || normalAngle(current_error_angle - position_angle) < -PI/2.0f) {
    // Reverse
        *current_correction_length = 0.0f;
        *current_correction_angle = normalAngle(PI + current_error_angle - position_angle);
    }
    else {
    // Forward
        *current_correction_length = 0.0f;
        *current_correction_angle = normalAngle(current_error_angle - position_angle);
    }
}

void correctionGoStraight(float current_error_length, float current_error_angle, __eds__ float *current_correction_length, __eds__ float *current_correction_angle) {
        if(normalAngle(current_error_angle - position_angle) > PI/2.0f || normalAngle(current_error_angle - position_angle) < -PI/2.0f) {
        // Reverse
            *current_correction_length = -1.0f * current_error_length;
            *current_correction_angle = normalAngle(PI + current_error_angle - position_angle);
        }
        else {
        // Forward
            *current_correction_length = current_error_length;
            *current_correction_angle = normalAngle(current_error_angle - position_angle);
        }
}

void correctionObjectiveOrientation(float current_error_length, float current_error_angle, __eds__ float *current_correction_length, __eds__ float *current_correction_angle) {
        if(normalAngle(current_error_angle - position_angle) > PI/2.0f || normalAngle(current_error_angle - position_angle) < -PI/2.0f) {
        // Reverse
            *current_correction_length = 0.0f;//-1.0f * current_error_length;
            *current_correction_angle = normalAngle(objectif_angle - position_angle);
        }
        else {
        // Forward
            *current_correction_length = 0.0f;//current_error_length;
            *current_correction_angle = normalAngle(objectif_angle - position_angle);
        }
}

BOOL trackerIsPositionAtObjective() {
    if(ABS(position_x - objectif_x) < 0.02f && ABS(position_x - objectif_x) < 0.02f && ABS(normalAngle(position_angle - objectif_angle)) < PI/16) {
        return TRUE;
    }
    return FALSE;
}

void trackerLogPosition(void) {
    StringFormatted("\
    state->next_on_success = aiStateGoto(%ff, %ff, %ff);\n\
    state = state->next_on_success;\n\n", position_x, position_y, position_angle);
}



float pidGetOrder(PID *pid, float error) {
    float order;
    pid->accumulator += error;
    order = error * pid->param_P + (pid->last_error - error) * pid->param_D + pid->accumulator * pid->param_I;
    pid->last_error = error;
    if (order > 1.0f)
        order = 1.0f;
    else if (order < -1.0f)
        order = -1.0f;
    return order;
}