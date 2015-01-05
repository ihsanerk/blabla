
// Dynamixel SDK platform dependent source
#include "dxl_hal.h"
#include "debug.h"
#include "leds.h"
#include "bus.h"
#include "timeout.h"

#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <xc.h>

bitPtr dxl_txen_tris, dxl_rxen_tris;
bitPtr dxl_txen, dxl_rxen;

static void dxlEnableTx(bool enable) {
    if(enable) {
        bitSet(dxl_rxen, 1);
        asm("nop");
        bitSet(dxl_txen, 0);
        asm("nop");
    }
    else {
        // Wait for end of transmission
        while(!U2STAbits.TRMT)
            ;
        bitSet(dxl_txen, 1);
        asm("nop");
        bitSet(dxl_rxen, 0);
        asm("nop");
    }
}

int dxl_hal_open( int devIndex, float baudrate )
{
    // Opening device
    // devIndex: Device index
    // baudrate: Real baudrate (ex> 115200, 57600, 38400...)
    // Return: 0(Failed), 1(Succeed)

    // For now, only 1 device and 1Mbit/s
    if(devIndex != 0 && baudrate != 1000000)
        return 0;

    // Pin direction
    bitSet(dxl_txen_tris, 0);
    bitSet(dxl_rxen_tris, 0);

    dxlEnableTx(false);

    // Configure UART
    U2MODEbits.UARTEN = 0;
    U2MODEbits.UEN = 0; // Only enable Rx and Tx pins
    U2MODEbits.PDSEL = 0; // 8-bit data, no parity
    U2MODEbits.STSEL = 0; // 1 stop bit
    U2STAbits.UTXISEL0 = 0;
    U2STAbits.UTXISEL1 = 0; // Tx Interrupt not used
    U2STAbits.URXISEL = 3; // Interrupt when 4 bytes are received

    U2MODEbits.BRGH = 1;
    U2BRG = 7;          // 1Mbaud

    IEC1bits.U2TXIE = 0; // Disable Tx interrupt
    IEC1bits.U2RXIE = 0; // Disable Rx interrupt

    // Start UART
    U2MODEbits.UARTEN = 1;
    U2STAbits.UTXEN = 1; // Enable Tx

    // Clear interrupt flags
    IFS1bits.U2TXIF = 0;
    IFS1bits.U2RXIF = 0;

    // Wait for BRG to stabilize
    delay_us(105);

    // Configure to return status packet
//    dxlSendFrame1(AX12_ID_BROADCAST, 0x10, 0x02);

    return 1;
}

void dxl_hal_close()
{
	// Closing device
    // Stop and reset UART
    U2MODEbits.UARTEN = 1;
}

void dxl_hal_clear(void)
{
	// Clear communication buffer
}

int dxl_hal_tx( unsigned char *pPacket, int numPacket )
{
    // Transmiting date
    // *pPacket: data array pointer
    // numPacket: number of data array
    // Return: number of data transmitted. -1 is error.

    size_t i;
    dxlEnableTx(true);
    for(i = 0; i < numPacket; ++i) {
        while(U2STAbits.UTXBF) // Wait if the Tx buffer is full
            ;
        U2TXREG = pPacket[i];
    }
    dxlEnableTx(false);

    return i;
}

static bool hasTimedOut;
int dxl_hal_rx( unsigned char *pPacket, int numPacket )
{
    // Recieving date
    // *pPacket: data array pointer
    // numPacket: number of data array
    // Return: number of data recieved. -1 is error.
    hasTimedOut = false;
    int i;
    for(i = 0; i < numPacket; ++i) {
        while(!U2STAbits.URXDA) {
            if(timeoutCheck()) {
                hasTimedOut = true;
                return i;
            }
        }
        pPacket[i] = U2RXREG;
    }

    return i;
}

void dxl_hal_set_timeout(int NumRcvByte)
{
    // Start stop watch
    // NumRcvByte: number of recieving data(to calculate maximum waiting time)
    timeoutSet(1, 0);
}

int dxl_hal_timeout(void)
{
    // Check timeout
    // Return: 0 is false, 1 is true(timeout occurred)
    return hasTimedOut;
}
