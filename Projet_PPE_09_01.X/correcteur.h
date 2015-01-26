/* 
 * File:   correcteur.h
 * Author: guillaume
 *
 * Created on 23 janvier 2015, 16:42
 */

#ifndef CORRECTEUR_H
#define	CORRECTEUR_H

//Librairies
#include "encodeur.h"
//#include "ccontroller.h"
#include "math.h"
#include "debugger.h"
#include <math.h>



/**
 *  \struct PID
 *  \brief Parameters and data for a PID control
 */
struct PID {
    float param_P;	/*!< Proportional parameter */
    float param_I; 	/*!< Integral parameter */
    float param_D; 	/*!< Derivative parameter */
    float last_error; 	/*!< Last error */
    float accumulator;	/*!< Accumulated errors */
};
typedef struct PID PID;


float normalAngle(float angle);
// Simple trajectory
void correctionGoStraight(float current_error_length, float current_error_angle, __eds__ float *current_correction_length, __eds__ float *current_correction_angle);
void correctionObjectiveOrientation(float current_error_length, float current_error_angle, __eds__ float *current_correction_length, __eds__ float *current_correction_angle);
void correctionLookAtObjective(float current_error_angle, __eds__ float *current_correction_length, __eds__ float *current_correction_angle);
// Curved trajectory
void fictivePoint ();
void realPoint(float error_x, float error_y);
float computeNewErrorAngle();

void SetPositionObjectif(float x, float y, float angle);
void trackerSetPosition(float new_position_x, float new_position_y, float new_position_angle);

BOOL trackerIsPositionAtObjective();
void trackerLogPosition(void);
//Pour actualiser l'asservissement
void trackerUpdate();
void trackerDebugPosition();
void trackerDebugObjective();

/**
 *  \brief Calculates a normalised order from the error with PID control
 *  
 *  \param [in] pid PID parameters and data
 *  \param [in] error Error to correct
 *  \return Normalised order
 */
float pidGetOrder(PID *pid, float error);

#endif	/* CORRECTEUR_H */

