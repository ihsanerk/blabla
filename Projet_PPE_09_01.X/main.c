/* 
 * File:   main.c
 * Author: Guillaume Sétan
 *
 * Created on 9 janvier 2015, 15:11
 */

// Librairies
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <stdint.h>
#include "configuration.h"
#include "debugger.h"
#include "definition.h"
#include "uart.h"

/*
 * 
 */
int main(int argc, char** argv) {
    //Ressources

    //Initialisation
    pinConfiguration ();
    uart_init();
    sendString("Fin de l'initialisation.");
    while(1)
    {

    }


}

