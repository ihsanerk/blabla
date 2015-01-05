#ifndef CONFIG_FLASH_H
#define	CONFIG_FLASH_H

#include <stdint.h>
/**
 *  \file config_flash.h
 *  \brief Loads and saves 64 floats from and to program flash memory
 */

/**
 *  \brief Initialises parameters
 */
void configInit();
/**
 *  Loads the configuration array from flash
 */
void configLoadFromFlash();
/**
 *  Saves the configuration array to flash
 */
void configSaveToFlash();

/**
 *  \var configuration
 *  \brief Contains float parameters saved in persisant memory
 */
extern float configuration[];

#endif	/* CONFIG_FLASH_H */
