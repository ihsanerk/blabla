#ifndef BUS_H
#define BUS_H

#include <stdint.h>
#include <stdbool.h>

#include "../tools/bits.h"

void busInit(void);
void busClose(void);

// Packet
typedef struct {
    uint8_t address;// bus_address_t
    uint8_t action; // bus_action_t
    uint8_t param1;
    uint8_t param2;
} bus_packet_t; // packets must be 4 bytes long

// Address of each dsPIC
typedef enum {
    ALL, MAIN, ACT, ARM, ALIM
} bus_address_t;

void busSentPacket(bus_packet_t *);
bool busIsPacketReceived(bus_address_t);
bus_packet_t busGetReceivedPacket(void);

// Rx interrupt behaviours
void busRxInterruptReadPacket(void);
void busRxInterruptResend(void);


typedef enum {
    ACT_LIFT_INIT,
    // Reset position of lift at the top or bottom
            // param1 (bool): true=Up, false=Down

    ACT_LIFT_GOTO,
    // Set position of the lift
            // param1 (bool): true=Fast, false=Slow
            // param2 (enum): ACT_LIFT_GOTO_POSITION

    MAIN_LIFT_STATUS,
    // Status of the arm lift
            // param1 ???

    ACT_SPEARS_THROW,
    // Launch a sequence to throw spears
            // param1 (enum): ACT_SPEARS_THROW_SEQUENCE

    MAIN_SPEARS_STATUS,
            //

    ARM_FIREDETECT_SCAN,
    // Request detection of a fire

    MAIN_FIREDETECT_STATUS,
    // Result of fire detection of the arm
            // param1 ???

    ARM_FIRECOLOR_SCAN,
    // Request a color detection of a fire

    MAIN_FIRECOLOR_STATUS,
    // Result of color detection of the arm
            // param1 ???

    ALIM_RESTART,
    // Cut and restart an alimentation
            // param1s (enum): ALIM_RESTART_***

    ALL_STOP
    // End of match or emergency switch
} bus_action_t;

// Pin controlling Tx Enable
extern bitPtr bus_txen, bus_txen_tris;

#endif // BUS_H
