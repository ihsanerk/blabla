#ifndef CONTROLLER_H
#define	CONTROLLER_H

#include <stdbool.h>

#include "../control/pid.h"

/**
 *  \file controller.h
 *  \brief Controls the robot's mouvement with PID
 *  
 *  Transforms the error to the objective into a normalised order for the motors
 *  A state machine is used to switch between the differents possible actions
 */
 
/**
 *  \enum ControllerState
 *  \brief States of the controller's state machine
 */
typedef enum {
    CS_PositionControl,	/*!< Position Control. Slows down and stops */
    CS_SpeedControl, 	/*!< Speed Control. Accelerates to maximum speed */
    CS_Braking, 	/*!< Emergency Braking. Stops as soon as possible to avoid collision */
    CS_Calibration	/*!< Calibration. Moves until a wall is touched to calibrate the position */
} ControllerState;

/**
 *  \struct Controller
 *  \brief Controller's state machine
 *  
 *  Saves the current state and the last normalised orders
 */
struct Controller {
    ControllerState state;	/*!< Current state */
    float order_length, 	/*!< Last length order */
	order_angle;			/*!< Last angle order*/
    bool state_initialisation_done;
    PID pid_length, pid_angle, pid_speed;
    float threshold_length, calibration_order, speed_max_order;
};
typedef struct Controller Controller;

extern Controller controller;

/**
 *  \brief Updates the length and angle orders depending on the current state and the new errors to the objective
 *  
 *  \param [in] error_length Distance error to the objective in meters
 *  \param [in] error_angle Angle error to the objective in radian (counter-clock wise)
 */
void controllerUpdate(float error_length, float error_angle);

void controllerAngleOptimization(float relative_x, float relative_y, float final_angle, float current_error_angle);

/**
 *  \brief Switches the current state of the controller
 *  
 *  \param [in] state New state
 */
void controllerChangeState(ControllerState state);

#endif	// CONTROL_H

