#include "tracker.h"
#include "encodeur.h"
#include "controller.h"
#include "math.h"
#include "debug.h"

#include <math.h>

float normalizeAngle(float angle);
// Simple trajectory
void correctionGoStraight(float current_error_length, float current_error_angle, __eds__ float *current_correction_length, __eds__ float *current_correction_angle);
void correctionGoStraight(float current_error_length, float current_error_angle, __eds__ float *current_correction_length, __eds__ float *current_correction_angle);
void correctionObjectiveOrientation(float current_error_length, float current_error_angle, __eds__ float *current_correction_length, __eds__ float *current_correction_angle);
void correctionLookAtObjective(float current_error_angle, __eds__ float *current_correction_length, __eds__ float *current_correction_angle);
// Curved trajectory
void fictivePoint ();
void ennemiPoint();
void realPoint(float error_x, float error_y);
void terrainPoint();
float computeNewErrorAngle();

float position_x = 0.0f, position_y = 0.0f, position_angle = 0.0f;
float objective_x = 0.0f, objective_y = 0.0f, objective_angle = 0.0f;
float angle[4];
float r[4];
float coeff[4];
bool isAngleAbsolute = false;

void trackerSetObjective(float x, float y, float angle) {
    objective_x = x;
    objective_y = y;
    objective_angle = normalizeAngle(angle);
}

void trackerSetPosition(float new_position_x, float new_position_y, float new_position_angle) {
    position_x = new_position_x;
    position_y = new_position_y;
    position_angle = normalizeAngle(new_position_angle);
}

void trackerUpdate() {
    float variation_length, variation_angle, current_error_length, current_error_angle, current_correction_length, current_correction_angle;
    encodersFetch();
    variation_length = encodersGetLengthVariation();
    variation_angle = encodersGetAngleVariation();

    position_angle = normalizeAngle(position_angle + variation_angle);
    position_x += variation_length * cos(position_angle);
    position_y += variation_length * sin(position_angle);

    float error_x, error_y;
    error_x = objective_x - position_x;
    error_y = objective_y - position_y;

    if(ABS(error_x) < 1e-6f && ABS(error_y) < 1e-6f) {
        current_error_length = 0.0f;
        current_error_angle = 0.0f;
    }
    else {
        current_error_length = sqrt(error_x * error_x + error_y * error_y);
        current_error_angle = atan2(error_y, error_x);
    }

    int i;
    for (i=0; i<4; i++){
        angle[i] = 0.0f;
        r[i] = 0.0f;
        coeff[i] = 0.25f;
    }

    //update real destination
    realPoint(error_x, error_y);

    // update fictive point
    fictivePoint();

    //update ennemi influence
    ennemiPoint();

    //update terrain influence
    terrainPoint();

//    if(1) { // Select simple or curved trajectory
        // If we are still far
        if(ABS(current_error_length) > 0.02f){
            // If the objective is not in front, turn
            if(ABS(normalizeAngle(current_error_angle - position_angle)) > (PI*1.0f/10.0f)
            && ABS(normalizeAngle(current_error_angle - position_angle)) < (PI*9.0f/10.0f)) {
                correctionLookAtObjective(current_error_angle, &current_correction_length, &current_correction_angle);
                current_correction_angle = normalizeAngle(current_correction_angle);
//                logString("[Look]");
            }
            // Else, go for it
            else {
                correctionGoStraight(current_error_length, current_error_angle, &current_correction_length, &current_correction_angle);
                current_correction_angle = normalizeAngle(current_correction_angle);
//                logString("[ Go ]");
            }
        }
        // Else ajust the orientation to the objective one
        else {
            correctionObjectiveOrientation(current_error_length, current_error_angle, &current_correction_length, &current_correction_angle);
//            if(!isAngleAbsolute) {
                current_correction_angle = normalizeAngle(current_correction_angle);
//            }
//            logString("[Set ]");
        }
//    }
//    else {
//        // Curved
//        current_correction_length = current_error_length;
//        current_correction_angle = normalizeAngle(computeNewErrorAngle());
//        logString("[Curv]");
//    }

//    logStringFormatted("Encoders: %f %f | ", variation_length, variation_angle);
//    logStringFormatted("Correction: %1.5f, %1.5f | position: %1.5f, %1.5f, %1.5f | objectif: %1.5f, %1.5f, %1.5f\n", current_correction_length, current_correction_angle, position_x, position_y, position_angle, objective_x, objective_y, objective_angle);

    controllerUpdate(current_correction_length, current_correction_angle);
}

void trackerDebugPosition() {
    logStringFormatted("Pos :(%1.3f %1.3f %1.3f) ", position_x, position_y, position_angle);
}

void trackerDebugObjective() {
    logStringFormatted("Obj :(%1.3f %1.3f %1.3f) ", objective_x, objective_y, objective_angle);
}

void fictivePoint (){
    angle[1] = objective_angle-PI/2.0f;
    r[1] = (objective_x - position_x) * sin(objective_angle)-(objective_y - position_y) * cos(objective_angle);
}

void realPoint(float error_x, float error_y){

    if(error_x < 1e-6f && error_y < 1e-6f) {
        r[0] = 10.0f;
        angle[0] = 0.0f;
    }
    else {
        r[0] = 1/(error_x) * sin(objective_angle)-(error_y) * cos(objective_angle);
        angle[0] = atan2(error_x, error_y);
    }
}

void ennemiPoint(){

}

void terrainPoint(){

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

float normalizeAngle(float angle) {
    angle = fmod(angle, (2.0f * PI));
    if(angle > PI) {
        angle = angle - 2.0f * PI;
    }
    return angle;
}

void correctionLookAtObjective(float current_error_angle, __eds__ float *current_correction_length, __eds__ float *current_correction_angle) {
    if(normalizeAngle(current_error_angle - position_angle) > PI/2.0f || normalizeAngle(current_error_angle - position_angle) < -PI/2.0f) {
    // Reverse
        *current_correction_length = 0.0f;
        *current_correction_angle = normalizeAngle(PI + current_error_angle - position_angle);
    }
    else {
    // Forward
        *current_correction_length = 0.0f;
        *current_correction_angle = normalizeAngle(current_error_angle - position_angle);
    }
}

void correctionGoStraight(float current_error_length, float current_error_angle, __eds__ float *current_correction_length, __eds__ float *current_correction_angle) {
        if(normalizeAngle(current_error_angle - position_angle) > PI/2.0f || normalizeAngle(current_error_angle - position_angle) < -PI/2.0f) {
        // Reverse
            *current_correction_length = -1.0f * current_error_length;
            *current_correction_angle = normalizeAngle(PI + current_error_angle - position_angle);
        }
        else {
        // Forward
            *current_correction_length = current_error_length;
            *current_correction_angle = normalizeAngle(current_error_angle - position_angle);
        }
}

void correctionObjectiveOrientation(float current_error_length, float current_error_angle, __eds__ float *current_correction_length, __eds__ float *current_correction_angle) {
        if(normalizeAngle(current_error_angle - position_angle) > PI/2.0f || normalizeAngle(current_error_angle - position_angle) < -PI/2.0f) {
        // Reverse
            *current_correction_length = 0.0f;//-1.0f * current_error_length;
            *current_correction_angle = normalizeAngle(objective_angle - position_angle);
        }
        else {
        // Forward
            *current_correction_length = 0.0f;//current_error_length;
            *current_correction_angle = normalizeAngle(objective_angle - position_angle);
        }
}

bool trackerIsPositionAtObjective() {
    if(ABS(position_x - objective_x) < 0.02f && ABS(position_x - objective_x) < 0.02f && ABS(normalizeAngle(position_angle - objective_angle)) < PI/16) {
        return true;
    }
    return false;
}

void trackerLogPosition(void) {
    logStringFormatted("\
    state->next_on_success = aiStateGoto(%ff, %ff, %ff);\n\
    state = state->next_on_success;\n\n", position_x, position_y, position_angle);
}
