/* 
 * File:   Main.c
 * Author: guillaume
 *
 * Created on 5 janvier 2015, 17:34
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <stdint.h>


#include "configuration.h"
#include "controller.h"
#include "encodeur.h"
#include "moteur.h"
#include "leds.h"
#include "debug.h"
#include "adc.h"
#include "bus.h"
#include "pwm.h"
#include "dynamixel.h"
#include "timeout.h"
#include "tracker.h"


// Prototypes
void init();
void waitForStartSwitch();
void waitForJack(void);
void ax12Stop();
void parseBusMessages(void);
void testADC(void);
void testAX12ID(void);
void testTimeout(uint32_t us);

// Variables
bool do_reset;
bool do_control;
bool configuration_changed;
int motorMaxConso = 1000;

int main() {
    // Initialisation
    init();

    // Start
    timerStart();
//    waitForJack();

    // Main loop
    logString("Starting...\n");
    do_reset = false;
    do_control = false;

    uint32_t test = 0xDEADBEEF;
    logStringFormatted("Test: %u %u\n", (uint16_t) (test >> 16), (uint16_t) (test & 0xFFFF));
//    testTimeout(1000);
//    testAX12ID();
//        dxl_ping(1);
//    testTimeout(1000000);
//    trackerSetPosition(0.0f, 0.0f, 0.0f);
//    trackerSetObjective(0.5f, 0.0f, 0.0f);
    unsigned int controlCounter = 0;
    while (!do_reset) {
        // Communication with other dsPICs
        parseBusMessages();

        // Motors control
        if(do_control) {
            controlCounter++;
            // Check if we are stuck
//            if(adcGetChannel(5) > motorMaxConso || adcGetChannel(9) > motorMaxConso) {
//                controllerChangeState(CS_Braking);
//            }

            trackerUpdate();
            do_control = false;
        }

        // ADC
        adcPoll();

        // AI
       // aiUpdate();

        // Configuration update
        if(configuration_changed) {
            configurationReload();
            configurationSave();
            configuration_changed = false;
            logString("Configuration saved!\n");
        }

        // Debug
        static unsigned int tmp = 0;
        if(++tmp == 1000) {
            tmp = 0;

//            logStringFormatted("Control done %u times\n", controlCounter);
            controlCounter = 0;

//            bus_packet_t p;
//            p.address = ACT;
//            p.action = ACT_SPEARS_THROW;
//            p.param1 = 0;
//            p.param2 = 1;
//            busSentPacket(&p);

            // Test AX12
//            dxl_write_byte(BROADCAST_ID, REG_LED, 1);
//            dxl_write_word(BROADCAST_ID, REGW_MAXTORQUE, 500);
//            dxl_write_word(BROADCAST_ID, REGW_GOALPOSITION, 923);
//            dxl_write_word(0x05, REGW_MAXTORQUE, 0);
//            unsigned int pos = dxl_read_word(0x05, REGW_PRESENTPOSITION);
//            logStringFormatted("Ax12 pos: %u\n", pos);

            // Log
//            encodersDebug();
//            trackerDebugPosition();
//            trackerDebugObjective();
//            logString("\n");
//
//            testADC();
//            testAX12ID();
        }
    }

    motorsBrake();
    timerStop();
    logString("Shutting Down!");
    logClose();
    while(PORTDbits.RD7)
        ;
    return 0;
}

void init() {
    oscillatorInit();
    pinConfigure();
    configurationInit();
    ledsInit();
    ledSet(0, true);
    timeoutInit();

    ledSet(1, true);

    logInit();
    delay_ms(10); // Wait for UART to initialise
    logString("\n--- Gali VII ---\nBooting...\n");

    ledSet(2, true);

    busInit();
    adcInit();
    if(!dxl_initialize(0, 1)) {
        logString("Error in dynamixel initialisation\n");
    }
    encodersInit();

    ledSet(3, true);

    motorsInit();

    ledSet(4, true);

    timersInit();
    pwmInit();
    //aiInit();
    logString("Initialisation done!\n");
    ledSet(5, true);

    waitForStartSwitch();
}

void waitForStartSwitch() {
    // Wait for start switch and enable INT2 to stop
    RPINR1bits.INT2R = 71;
    IEC1bits.INT2IE = 0; // Disable interrupt
    IFS1bits.INT2IF = 0; // Clear interrupt flag
    INTCON2bits.INT2EP = 1; // Interrupt on negative edge
    _INT2IP = 0b110; // Priority : 6
    IEC1bits.INT2IE = 1; // Enable interrupt

    while (!PORTDbits.RD7)
        ;
}

void waitForJack(void) {
    while(!PORTFbits.RF8)
        ;
}

void parseBusMessages(void) {
    // Parse received messages
    if(busIsPacketReceived(MAIN)) {
        bus_packet_t packet = busGetReceivedPacket();
//        logStringFormatted("Frame received (%d)\n", packet.action);p
        switch(packet.action) {
            case MAIN_SPEARS_STATUS:
                // For now, this means the button has been pushed
                //ai_button_pushed = true;
                trackerLogPosition();
                break;
            case MAIN_FIRECOLOR_STATUS:
                break;
            case MAIN_FIREDETECT_STATUS:
                break;
            case MAIN_LIFT_STATUS:
                break;
        }
    }
}

void testADC(void) {
    // Test ADC
//    logStringFormatted("Motors:  %4u", adcGetChannel(5));
//    logStringFormatted(" %4u\n", adcGetChannel(21));
    logString("Sharps: ");
    logStringFormatted(" %4u", adcGetChannel(14));
    logStringFormatted(" %4u", adcGetChannel(13));
    logStringFormatted(" %4u", adcGetChannel(12));
    logStringFormatted(" %4u", adcGetChannel(10));
    logStringFormatted(" %4u", adcGetChannel(15));
    logStringFormatted(" %4u", adcGetChannel(11));
    logString("\n");
}

void testAX12ID(void) {
    dxl_write_byte(BROADCAST_ID, REG_STATUS_RETURN_LVL, 2);
    dxl_write_byte(BROADCAST_ID, REG_RETURN_DELAY, 100);
    dxl_write_byte(BROADCAST_ID, REG_LED, 1);

    logString("AX12 ID Test\n");
    int id;
    for(id = 0; id < 0xFE; ++id) {
        dxl_ping(id);
        logStringFormatted("ID %d: %d\n", id, dxl_get_result());
    }
}

void testTimeout(uint32_t us) {
    while(true) {
        logStringFormatted("Waiting for %u us... ", us);
        timeoutSet(0, 1000);
        while(!timeoutCheck())
            ;
        logString("OK\n");
    }
}

// Start switch interrupt: when switched down, the program is reset
void __attribute__((__interrupt__, auto_psv)) _INT2Interrupt(void) {
    // Clear flag
    _INT2IF = 0;

    motorsBrake();
    do_reset = true;
}

// Control Frequency
void __attribute__((__interrupt__,auto_psv)) _T3Interrupt(void) {
    // Clear flag
    IFS0bits.T3IF = 0;

    TMR3 = 0x00; // Clear Timer register
    do_control = true;
}

// Stop at 90s
void __attribute__((__interrupt__,auto_psv)) _T7Interrupt(void) {
    // Clear flag
    IFS3bits.T7IF = 0;

    TMR7 = 0x00; // Clear Timer register
    do_reset = true;
}

void __attribute__((__interrupt__,auto_psv)) _U1RXInterrupt(void) {
    IFS0bits.U1RXIF = 0; // Clear flag
    busRxInterruptReadPacket();
}
