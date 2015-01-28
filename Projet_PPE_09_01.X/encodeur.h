/* 
 * File:   encodeur.h
 * Author: guillaume
 *
 * Created on 23 janvier 2015, 16:28
 */

#ifndef ENCODEUR_H
#define	ENCODEUR_H

#include <stdint.h>

/**
 *  \file encoders.h
 *  \brief Interface to the quadrature encoders
 */

/**
 *  \struct Encoder
 *  \brief Contains data about an encoder
 */
struct Encoder {
    uint32_t old_value;
    uint32_t new_value;
    int16_t variation;
    float mm_per_tick;
    float rad_per_tick;
};
typedef struct Encoder Encoder;

/**
 *  \var encoder_right
 *  \brief Data of the right wheel encoder
 */
extern Encoder encoder_right;
/**
 *  \var encoder_left
 *  \brief Data of the left wheel encoder
 */
extern Encoder encoder_left;

/**
 *  \brief Initialises the QEI (Quadrature Encoder Interface)
 */
void encodersDebug();

void encodersInit();
/**
 *  \brief Fetches the encoders' new values and calculates variation
 */
void encodersFetch();
/**
 *  \brief Calculates the length variation
 *
 *  \return Length variation since the last fetch in meter
 */
float encodersGetLengthVariation();
/**
 *  \brief Calculates the angle variation
 *
 *  \return Angle variation since the last fetch in radian
 */
float encodersGetAngleVariation();


#endif	/* ENCODEUR_H */

