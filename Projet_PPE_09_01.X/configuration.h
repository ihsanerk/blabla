#ifndef CONFIGURATION_H
#define	CONFIGURATION_H

//Librairies
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <libpic30.h>
#include <xc.h>

//Inclure les librairies
#include "debugger.h"
#include "definition.h"
#include "uart.h"

//Prototypes
void pinConfiguration ();
void oscillatorInit();


#endif	/* CONFIGURATION_H */

