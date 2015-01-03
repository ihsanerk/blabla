#ifndef TOOLS_DELAY_H
#define	TOOLS_DELAY_H

#include <libpic30.h>
/**
 *  \file delay.h
 *  \brief Tools for __delay32 funtion
 */

// This MUST be defined by the main project
extern unsigned long long int conf_fcy;

/**
 *  \def delay_ms
 *  \brief Wait for a specified amount of miliseconds
 */
#define delay_ms(A)         __delay32((unsigned long)(A)*(conf_fcy/1000))
/**
 *  \def delay_us
 *  \brief Wait for a specified amount of microseconds
 */
#define delay_us(A)         __delay32((unsigned long)(A)*(conf_fcy/1000000))

#endif	/* TOOLS_DELAY_H */

