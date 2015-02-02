
//Librairies
#include  "math.h"

#ifndef PID_H
#define	PID_H

struct PID {
    float param_P;	/*!< Proportional parameter */
    float param_I; 	/*!< Integral parameter */
    float param_D; 	/*!< Derivative parameter */
    float last_error; 	/*!< Last error */
    float accumulator;	/*!< Accumulated errors */
};
typedef struct PID PID;

extern PID pid_length,pid_angle;

float pidGetOrder(PID *pid, float error);

#endif	/* PID_H */

