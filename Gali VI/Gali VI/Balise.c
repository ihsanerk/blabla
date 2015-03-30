// Library
#include "Balise.h"

//	Variables
Balise balise;
			
//	Fonctions
void baliseInit ()
{
	// Initialiser la réception
		/*baliseUartInit();
	bluetoothInit ();
	
	// Initialiser la variable
	balise.compteur = 0;
	balise.timer = 0;
	
	// Initialiser le tableau de départ
	int16 i = 0;
	for (i = 0; i < 20; i++)
		balise.bougies[i] = 0;
		
	// Les 2 dernières appartiennent à l'adversaire
	balise.bougies[12] = 1;
	balise.bougies[19] = 1;*/
}
/*
void baliseUartInit()
{
	//RPINR18bits.U3RXR = 108; //Remaping RxPin to RP108
	//RPOR12bits.RP109R = 1; // Remaping RP109 to TxPin

	U3MODEbits.UARTEN  = 0;     // Disable UART
    U3MODEbits.ABAUD   = 0;     // Auto-Baud Disabled
    U3MODEbits.PDSEL   = 0b00;  // 8 bit, no parity
    U3MODEbits.STSEL   = 0;     // One stop bit
    U3MODEbits.BRGH    = 0;     // 0 = Mode which works

    //BRGH = 1 : mode rapide : XBee ou FT232 BRGH =0 : mode lent FT232
    //BAUD Rate Setting (formula 19-2 from dsPIC33F Family datasheet)
    //+2 for bug correction (FT232) +5 (xbee) en mode rapide
	U3BRG = BALISE_FINAL_BAUD;

    // Rx interrupt
    U3STAbits.URXISEL  = 0b00;  // On each char
    IFS0bits.U3RXIF    = 0;     // Clear interrupt flag
    IEC0bits.U3RXIE    = 1;     // Enable interrupt
    IPC2bits.U3RXIP    = 0b100; // Interruption level 4

    // Tx interrupt
    IEC0bits.U3TXIE    = 0;      // Disable interrupt

     // Enable UART
     U3MODEbits.UARTEN  = 1;      // Enable UART
     U3STAbits.UTXEN    = 0;      // Disable UART Tx
}

void bluetoothInit ()
{
	// --- Timer 4 : Balise ---
	/*
		PRESCALER 256
		FOVERFLOW 1 Hz (1 seconde)
		FCY 32 000 000
		PR	125 000 (1110 1000 0100 1000)
	*/
	/*T4CONbits.TON   = 0;      		// Disable timer
	T4CONbits.TCKPS = 0b11;   		// Prescaler : 256
	T4CONbits.TCS   = 0;      		// Internal clock
	T4CONbits.TGATE = 0;     		// Timer mode
	TMR4            = 0x00;   		// Clear Timer register
	PR4             = PR_BALISE;    // Period value (125 000 = 1Hz)
	
	// Interruption
	_T4IP = 0b010;   		// Priority : 2
	IFS0bits.T4IF = 0;      // Clear flag
	
	/*	Switch to Host controlled mode request (0x01)
		Lenght (0x04) 
		CODE (0xFF,0x00,0x55,0xAA) */
	/*char SHCM[6] = {0x01,0x04,0xFF,0x00,0x55,0xAA};
	baliseUartSendSeq(SHCM, 6);	
	delay_ms(DELAY_INIT_BLUETOOTH);
	
	/*	Set operating mode request (0x13) 
		Lenght (0x01)
		End point mode(0x02)
	*/
	/*char SOM[3] = {0x13,0x01,0x02};
		baliseUartSendSeq(SOM, 3);	
	delay_ms(DELAY_INIT_BLUETOOTH);
	
	/*	Serial port configuration (A request to change the serial port configuration)
		Lenght (0x05)
		Baude rate 38400 (bps) (0x05)
		Hardware flow control ON(0x01)
		No parity (0x00)
		Number of data bits to use (Not configurable at the moment)(0x08)
		1 stop bit(0x01)
	*/
	/*char serial[7]={0x15,0x05,0x05,0x01,0x00,0x08,0x01};
	baliseUartSendSeq(serial, 7);	
	delay_ms(DELAY_INIT_BLUETOOTH);

	/* Set connect accept rule request (0x19)
	   Lenght (0x06)
	   A changer : BLUETOOTH_ADDRESS(0x00,0x17,0x83,0xE9,0x80,0xF8)
	*/
	/*char adresse[8]={0x19,0x06,0x00,0x17,0x83,0xE9,0x80,0xF8};
	baliseUartSendSeq(adresse, 8);			
	delay_ms(DELAY_INIT_BLUETOOTH);
	
	/* Set local Bluetooth name request (0x1D)
	   Lenght (0x05)
	*/
	/*char name[7]={0x1D,0x05,'G','A','L','I','\0'};
	baliseUartSendSeq(name, 7);	
	delay_ms(DELAY_INIT_BLUETOOTH);	
						
	/* Desactivation de la sécurité
	   Set security mode request (0x63)
	   Lenght (0x02)
	   Security off (0x00)
	   Encryption Off (0x00)
	*/
	/*char security[4]={0x63,0x02,0x00,0x00};
	baliseUartSendSeq(security, 4);	
	delay_ms(DELAY_INIT_BLUETOOTH);	
						
	/* Set PIN code request (0x65)
	   Lenght (0x05)
	*/
	/*char pin[7]={0x65,0x05,'4','3','2','1','\0'};
	baliseUartSendSeq(pin, 7);	
	delay_ms(DELAY_INIT_BLUETOOTH);	
						
	/*	Sortir du mode config
		Run response (0x50)
		Lenght (0x00)
	*/
	/*char end[2]={0x50,0x00};
	baliseUartSendSeq(end, 2);	
	delay_ms(DELAY_INIT_BLUETOOTH);
	
	// Interruption
	IEC0bits.T3IE = 1;        // Enable interrupt
	T3CONbits.TON   = 1;      // Enable timer
}*/
/*
void baliseUartSendSeq(const char * c, int i)
{
	int16 j = 0;
	while(j != i)
	{
		baliseUartSendChar(c[j]);
		j++;
	}
}

// Envoyer un caractère avec l'uart
void baliseUartSendChar(const unsigned char c)
{
	while(U3STAbits.UTXBF == 1); // Wait until buffer is full
	U3TXREG = c;                 // Buffer the char to send
}

// Interruption balise
void __attribute__((__interrupt__, auto_psv)) _T3Interrupt(void)
{
	//Timer indépendant de la boucle principale
	balise.timer++;
				
	// Après 1 min 30 secondes le timer meurt
	if(balise.timer >= 90000)
	{
		T4CONbits.TON   = 0;      // Désactiver l'interruption
		
		// Désactiver l'interruption de l'uart
		_U3RXIF = 1;
		U3MODEbits.UARTEN  = 0;   
	}
	
	//	Réinitialise le flag
	IFS0bits.T4IF=0;
}

// Interruption lors de la réception d'un caractère
void __attribute__((__interrupt__, auto_psv)) _U3RXInterrupt(void)
{	
	// En cas d'erreur
	if(U3STAbits.OERR)
	{
		U3STAbits.OERR = 0;
	}
	
	// récupérer le caractère dans la liste
	balise.bougies[balise.compteur] = (uint8)U3RXREG;
	balise.compteur++;

	// Réinitialiser le flag
	_U3RXIF = 0;
}
*/
