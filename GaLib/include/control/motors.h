#ifndef MOTORS_H
#define MOTORS_H

#include "../tools/bits.h"

#include <stdint.h>

/**
 *  \file motors.h
 *  \brief Interface to the DC motors
 */
 
// Pins dedicace alban représente
extern bitPtr motors_dir_r; 		/*!< Register bit for right motor's direction */
extern bitPtr motors_dir_l;			/*!< Register bit for left motor's direction */
extern bitPtr motors_brake_r;		/*!< Register bit for right motor's braking */
extern bitPtr motors_brake_l;		/*!< Register bit for left motor's braking */
extern regPtr motors_pwm_r;			/*!< Register for right motor's PWM */
extern regPtr motors_pwm_l;			/*!< Register for right motor's PWM */
extern bitPtr motors_dir_l_tris;
extern bitPtr motors_dir_r_tris;
extern bitPtr motors_brake_l_tris;
extern bitPtr motors_brake_r_tris;
extern bitPtr motors_pwm_l_tris;
extern bitPtr motors_pwm_r_tris;
extern unsigned int motors_PTP;
extern uint16_t pwm_max, pwm_min;
extern float coef_angle;

// Prototypes
/**
 *  \brief Initialise the motors
 */
void motorsInit();
/**
 *  \brief Activates braking
 */
void motorsBrake();
/**
 *  \brief Deactivates braking
 */
void motorsUnbrake();
/**
 *  \brief Apply orders to the motors with PWM
 *  
 *  \param [in] order_lenght Normalised length order
 *  \param [in] order_angle Normalised angle order
 */
void motorsApplyOrder(float order_lenght, float order_angle);

void motorsFreeRunning(void);

#endif // MOTORS_H
