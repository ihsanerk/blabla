#ifndef LOG_H
#define	LOG_H

/**
 *  \file log.h
 *  \brief Logging to UART1
 */
 
extern unsigned int log_final_baud;

/**
 *  \brief Initialises UART1
 */
void logInit();
/**
 *  \brief Closes UART1
 */
void logClose();
/**
 *  \brief Log a string to UART1
 *  
 *  \param [in] string Message to log
 */
void logString(const char *string);/**
 *  \brief Log a string to UART1 with printf-like format
 *  
 *  \param [in] fmt Message to log with format
 *  \param [in] ... Variables to insert
 */
void logStringFormatted(const char *fmt, ...);

#endif	/* LOG_H */

