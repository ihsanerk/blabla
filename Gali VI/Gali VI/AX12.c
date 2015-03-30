// Library
#include "AX12.h"

//	Variables

//	Fonctions
void ax12Init ()
{
	// Setting the remapable pin 
	RPINR19bits.U2RXR = 112; //Maping AX12RX to the RP104 pin
	RPOR7bits.RP96R = 3; //Maping U2TX to the RP96 pin

	//Init
	U2MODEbits.UARTEN  = 0;  // Disable UART
	U2MODEbits.ABAUD   = 0;  // Auto-Baud Disabled
	U2MODEbits.PDSEL   = 0;  // 8 bit, no parity
	U2MODEbits.STSEL   = 0;  // One stop bit
	
	//Baud rate setting
	U2BRG = 16;

	// Rx interrupt
	U2STAbits.URXISEL = 0;   // On each char
	_U2RXIF           = 0;   // Clear interrupt flag
	_U2RXIE           = 1;   // Enable interrupt
	_U2RXIP       = 0b110;   // Level 6
	
	// Tx interrupt
	U2STAbits.UTXISEL0 = 0;   // On each char
	U2STAbits.UTXISEL1 = 0;   // On each char
	_U2TXIE           = 0;   // Disable interrupt
	
	// Enable UART
	U2MODEbits.UARTEN  = 1;  // Enable UART
	U2STAbits.UTXEN    = 1;  // Enable UART Tx
	
	//RX and TX Enable for the AX12
	TRISAbits.TRISA7 = 0;
	TRISAbits.TRISA6 = 0;
}

void ax12SetMode (bool mode)
{
	//	Write Mode
	if (mode)
	{
		RXENABLE = 1;
		asm("nop");
		
		TXENABLE = 0;
		asm("nop");
	}
	
	//Read Mode
	else
	{
		ax12WaitEndOfTransmission();
		
		TXENABLE = 1;
		asm("nop");
		
		RXENABLE = 0;
		asm("nop");
	}
}

void ax12SendChar(uint8 c, int8 * checksum)
{
	//Send the char
	ax12UartSendChar(c);
	
	// Compute the checksum
	if(checksum != NULL)
		*checksum += c; 
}

void ax12Execute (int32 goal, uint8 id, bool ax12)
{
	//Only the goal and ID of the acurator are needed for this project
	int8 checksum = 0; // Cf datasheet to get the formula
	ax12SetMode(TRUE); //Enable the write mode
	
	//Signal d'envoie
	ax12SendChar (0xff, NULL);
	ax12SendChar (0xff, NULL);
	
	// Id de l'AX-12
	ax12SendChar(id, &checksum);
	
	// Taille de la commande (nb Paramametres + 2)
	ax12SendChar (0x07, &checksum);
	
	// Mode envoie ordre (WRITE_MODE)
	ax12SendChar (0x03, &checksum);
	
	// --params --
	
	//Start to write at the goal LSB adress
	ax12SendChar (0x1e, &checksum);
	
	//Writing the ten bit of goal position
	ax12SendChar ((goal & 0x00ff), &checksum); // LSB
	ax12SendChar (((goal >> 8) & 0b11), &checksum); // MSB
	
	//Set the speed of acurator ( 0 = as fast as possible )
	if (ax12)
	{
		ax12SendChar (0x00, &checksum); //LSB
		ax12SendChar (0x00, &checksum); //MSB
	}
	
	//Pour les servo chinois
	else
	{
		ax12SendChar (0xff, &checksum); //LSB
		ax12SendChar (0x03, &checksum); //MSB
	}
	
	// --end params
	
	//Sending the Checksum
	ax12SendChar (~checksum, NULL);
} 

void ax12UartSendChar(uint8 c)
{
	while(U2STAbits.UTXBF == 1); // Wait until buffer is full
	U2TXREG = c;                 // Buffer the char to send
}

void ax12WaitEndOfTransmission()
{
	while(U2STAbits.TRMT == 0);
}

uint8 ax12GetChar()
{
	while(U2STAbits.URXDA == 0);
	return (uint8)U2RXREG;
}

void ax12DisableTorque (uint8 id)
{
	//	Ressources
	int8 checksum = 0;
	ax12SetMode(TRUE); //Enable the write mode

	//	Signal d'envoie
	ax12SendChar(0xff, NULL);
	ax12SendChar(0xff, NULL);
	
	//	Id de l'AX-12
	ax12SendChar(id, &checksum)   ;   // Broadcast

	//	Taille de la commande (nb Paramametres + 2)
	ax12SendChar(0x04, &checksum);
	
	//	Mode envoie ordre (WRITE_MODE)
	ax12SendChar(0x03, &checksum);
	
	// --params --
	
	//	Torque enable address
	ax12SendChar(0x18, &checksum);
	
	//	Put it to 0 (disable)
	ax12SendChar(0x00, &checksum);
	
	// --end params

	// Sending the Checksum
	ax12SendChar(~checksum, NULL);
}
