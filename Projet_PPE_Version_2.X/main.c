//Librairies
#include <stdio.h>
#include <stdlib.h>
#include <p33EP512MU810.h>
#include <libpic30.h>
#include <pps.h>

#include  "configuration.h"
#include  "definition.h"
#include  "uart.h"
#include  "debugger.h"
#include  "moteur.h"
#include  "adc.h"
#include  "controleur.h"
#include  "math.h"
#include  "asservissement.h"
#include  "DetectionSharp.h"





// DSPIC33EP512MU810 Configuration Bit Settings
// FGS
#pragma config GWRP = OFF               // General Segment Write-Protect bit (General Segment may be written)
#pragma config GSS = OFF                // General Segment Code-Protect bit (General Segment Code protect is disabled)
#pragma config GSSK = OFF               // General Segment Key bits (General Segment Write Protection and Code Protection is Disabled)


// FOSCSEL
#pragma config FNOSC = PRIPLL           // Initial Oscillator Source Selection Bits (Internal Fast RC (FRC))
#pragma config IESO = ON               // Two-speed Oscillator Start-up Enable bit (Start up with user-selected oscillator source)


// FOSC
#pragma config POSCMD = HS              // Primary Oscillator Mode Select bits (HS Crystal Oscillator Mode)
#pragma config OSCIOFNC = OFF           // OSC2 Pin Function bit (OSC2 is clock output)
#pragma config IOL1WAY = OFF             // Peripheral pin select configuration (Allow only one reconfiguration)
#pragma config FCKSM = CSECMD           // Clock Switching Mode bits (Both Clock switching and Fail-safe Clock Monitor are disabled)


// FWDT
#pragma config WDTPOST = PS32768        // Watchdog Timer Postscaler Bits (1:32,768)
#pragma config WDTPRE = PR128           // Watchdog Timer Prescaler bit (1:128)
#pragma config PLLKEN = OFF              // PLL Lock Wait Enable bit (Clock switch to PLL source will wait until the PLL lock signal is valid.)
#pragma config WINDIS = OFF             // Watchdog Timer Window Enable bit (Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable bit (Watchdog timer enabled/disabled by user software)


// FPOR
#pragma config FPWRT = PWR128           // Power-on Reset Timer Value Select bits (128ms)
#pragma config BOREN = OFF              // Brown-out Reset (BOR) Detection Enable bit (BOR is disabled)
#pragma config ALTI2C1 = OFF            // Alternate I2C pins for I2C1 (SDA1/SCK1 pins are selected as the I/O pins for I2C1)
#pragma config ALTI2C2 = OFF            // Alternate I2C pins for I2C2 (SDA2/SCK2 pins are selected as the I/O pins for I2C2)


// FICD
#pragma config ICS = PGD3               // ICD Communication Channel Select bits (Communicate on PGEC3 and PGED3)
#pragma config RSTPRI = PF              // Reset Target Vector Select bit (Device will obtain reset instruction from Primary flash)
#pragma config JTAGEN = OFF             // JTAG Enable bit (JTAG is disabled)


// FAS
#pragma config AWRP = OFF               // Auxiliary Segment Write-protect bit (Auxiliary program memory is not write-protected)
#pragma config APL = OFF                // Auxiliary Segment Code-protect bit (Aux Flash Code protect is disabled)
#pragma config APLK = OFF               // Auxiliary Segment Key bits (Aux Flash Write Protection and Code Protection is Disabled)


int8 team;

void main(void) {
    //Ressources
    float CodeurDroit = 0.0f;
    float CodeurGauche = 0.0f;
    float  distance =0.0f;
    float angle=0.0f;
    int compteur=0;

    //Initialisation
    pinConfiguration(); // Initialisation des différents PINS
    adcInit(); //Initialisation des ADC
    uart_init(); // Initialisation de la communication avec l'ordinateur
    asservissementInit(); // Initialisation du moteur + encodeur + asservissement
    SetPositionCurrent(0, 0, 0); //Initialisation de la position de départ
    SetPositionObjectif(0, 0.3f, 0); // initialisation de la position de l'objectif
    //detectionSharpInit();

    // Initialise l'équipe
    if (!PORTFbits.RF0) team = 1;
    else team = -1;

    sendString("Fin de l'initialisation.\n");


    do
    {
        delay_ms(500);
        UpdatePosition();
        //valeurCodeurs();
        //distance+=codeurGetDistance();
        //CodeurDroit+=codeurGetDroit();
        //CodeurGauche+=codeurGetGauche();
        //angle+=codeurGetAngle();


        //StringFormatted("D:%1.5f , G:%1.5f ;",CodeurDroit,CodeurGauche);
        //StringFormatted("D:%1.5f ;",distance);
        //StringFormatted("A:%1.5f ;",angle);
        StringFormatted("X:%1.5f , Y:%1.5f ,A:%1.5f;",Gali_current.x,Gali_current.y,Gali_current.angle);

        //encodersDebug();
        //afficher_Gali();
        compteur++;
    }while((ABS(Gali_current.y-Gali_objectif.y)>0.01f));
    sendString("Fin de la consigne.\n");
    mettreFrein();
    
    //delay_ms(10000);
    while (1) {
        //on récupère la valeur des codeurs
        //UpdatePosition();

                //StringFormatted("X:%1.5f , Y:%1.5f ,A:%1.5f;",Gali_current.x,Gali_current.y,Gali_current.angle);



    }


}