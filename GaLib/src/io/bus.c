#include "io/bus.h"

#include <xc.h>
#include <stddef.h>

#include "tools/delay.h"

bitPtr bus_txen, bus_txen_tris;
bus_packet_t bus_rx_buffer;
bool bus_rx_buffer_new;

void busEnableTx(bool enable) {
    if(enable) {
        bitSet(bus_txen, 1);
        delay_us(10);
    }
    else {
        delay_us(10);
        bitSet(bus_txen, 0);
    }
}

void busInit(void) {
    // Pin direction
    bitSet(bus_txen_tris, 0);

    busEnableTx(false);
    bus_rx_buffer_new = false;

    // Configure UART
    U1MODEbits.UARTEN = 0;
    U1MODEbits.UEN = 0; // Only enable Rx and Tx pins
    U1MODEbits.PDSEL = 0; // 8-bit data, no parity
    U1MODEbits.STSEL = 0; // 1 stop bit
    U1STAbits.UTXISEL0 = 0;
    U1STAbits.UTXISEL1 = 0; // Tx Interrupt not used
    U1STAbits.URXISEL = 3; // Interrupt when 4 bytes are received

    U1MODEbits.BRGH = 0;
    U1BRG = 207; // 9615 bauds, near standard 9600
    
//    U1MODEbits.BRGH = 1;
//    U1BRG = 0; // 921'250 bauds, near 1'000'000
    
    IEC0bits.U1TXIE = 0; // Disable Tx interrupt
    IEC0bits.U1RXIE = 1; // Enable Rx interrupt

    // Start UART
    U1MODEbits.UARTEN = 1;
    U1STAbits.UTXEN = 1; // Enable Tx

    // Clear interrupt flags
    IFS0bits.U1TXIF = 0;
    IFS0bits.U1RXIF = 0;

    // Wait for BRG to stabilize
    delay_us(105);
}

void busClose(void) {
    // Stop and reset UART
    U1MODEbits.UARTEN = 1;
}

void busSendByte(uint8_t byte) {
    while(U1STAbits.UTXBF) // Wait if the Tx buffer is full
        ;
    U1TXREG = byte;
}

void busSentPacket(bus_packet_t *packet) {
    size_t i;
    busEnableTx(true);
    for(i = 0; i < 4; ++i) {
        busSendByte(((uint8_t*)packet)[i]);
    }
    // Wait for end of transmission
    while(!U1STAbits.TRMT)
        ;
    busEnableTx(false);
}

void busRxInterruptReadPacket(void) {
    size_t i;
    uint8_t *buffer = (uint8_t*) &bus_rx_buffer;
    for(i = 0; i < 4; i++) {
        while(!U1STAbits.URXDA) // Wait if data is not available
            ;
        buffer[i] = U1RXREG;
    }
    bus_rx_buffer_new = true;
}

void busRxInterruptResend(void) {
    uint8_t byte = U1RXREG;
    busEnableTx(true);
    busSendByte(byte);
    busEnableTx(false);
}

bool busIsPacketReceived(bus_address_t address) {
    // If a packet is received
    if(bus_rx_buffer_new) {
        // Check address
        if(address == bus_rx_buffer.address || address == ALL) {
            return true;
        }
        else {
            // Wrong address, ignore packet
            bus_rx_buffer_new = false;
        }
    }
    return false;
}

bus_packet_t busGetReceivedPacket(void) {
    while(!bus_rx_buffer_new) // Wait if no packet has been received
        ;
    bus_rx_buffer_new = false;
    return bus_rx_buffer;
}
