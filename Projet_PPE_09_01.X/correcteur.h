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

//Ressources
float position_x = 0.0f, position_y = 0.0f, position_angle = 0.0f;
float objectif_x = 0.0f, objectif_y = 0.0f, objectif_angle = 0.0f;
float angle[4];
float r[4];
float coeff[4];
BOOL isAngleAbsolute = FALSE;

float normalAngle(float angle);
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



#endif	/* CORRECTEUR_H */

