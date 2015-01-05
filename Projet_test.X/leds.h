#ifndef LEDS_H
#define	LEDS_H

#include <stdbool.h>
#include <stdint.h>
#include "bits.h"

/**
 *  \file leds.h
 *  \brief Interface to the 8 debug leds
 */

// Pin configuration
extern bitPtr led0;
extern bitPtr led1;
extern bitPtr led2;
extern bitPtr led3;
extern bitPtr led4;
extern bitPtr led5;
extern bitPtr led6;
extern bitPtr led7;
extern bitPtr led0_tris;
extern bitPtr led1_tris;
extern bitPtr led2_tris;
extern bitPtr led3_tris;
extern bitPtr led4_tris;
extern bitPtr led5_tris;
extern bitPtr led6_tris;
extern bitPtr led7_tris;

/**
 *  \brief Initialises the debug leds
 */
void ledsInit();
/**
 *  \brief Turn on or off a led
 *
 *  \param [in] led Led to use (0 to 7)
 *  \param [in] state Turn on or off ?
 */
void ledSet(uint8_t led, bool state);
/**
 *  \brief Toggles a led between on and off
 *
 *  \param [in] led Led to use (0 to 7)
 */
void ledToggle(uint8_t led);
/**
 *  \brief Set all the leds to show a 8bits value
 *
 *  \param [in] value value to show
 */
void ledSetAll(uint8_t value);


#endif	/* LEDS_H */

