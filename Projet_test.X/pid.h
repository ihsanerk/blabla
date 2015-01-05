#ifndef PID_H
#define	PID_H

/**
 *  \file pid.h
 *  \brief PID Control
 */

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

/**
 *  \brief Calculates a normalised order from the error with PID control
 *
 *  \param [in] pid PID parameters and data
 *  \param [in] error Error to correct
 *  \return Normalised order
 */
float pidGetOrder(PID *pid, float error);

#endif	/* PID_H */

