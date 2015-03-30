// Librarie
#include "CommunicationBaby.h"

//Variables
Robot 		baby_Gali;

// Intialise l'uart
void communicationBabyInit()
{
	// Initialise la position de Baby Gali
	baby_Gali.y = -100;
	baby_Gali.x = -100;
	
	// Initialiser l'uart
	xbeeInit();
}

void xbeeInit()
{
	/*RPINR18bits.U1RXR = 108; //Remaping RxPin to RP108
	RPOR12bits.RP109R = 1; // Remaping RP109 to TxPin

	U1MODEbits.UARTEN  = 0;     // Disable UART
    U1MODEbits.ABAUD   = 0;     // Auto-Baud Disabled
    U1MODEbits.PDSEL   = 0b00;  // 8 bit, no parity
    U1MODEbits.STSEL   = 0;     // One stop bit
    U1MODEbits.BRGH    = 0;     // 0 = Mode which works

    //BRGH = 1 : mode rapide : XBee ou FT232 BRGH =0 : mode lent FT232
    //BAUD Rate Setting (formula 19-2 from dsPIC33F Family datasheet)
    //+2 for bug correction (FT232) +5 (xbee) en mode rapide
	U1BRG = FINAL_BAUD;                // 207 = 9600 bauds

    // Rx interrupt
    IFS0bits.U1RXIF    = 0;     // Clear interrupt flag
    IEC0bits.U1RXIE    = 0;     // Disable interrupt

    // Tx interrupt
    IEC0bits.U1TXIE    = 0;      // Disable interrupt

     // Enable UART
     U1MODEbits.UARTEN  = 1;      // Enable UART
     U1STAbits.UTXEN    = 1;      // Enable UART Tx*/
}

// Envoyer un caractère avec l'uart
void xbeeUartSendChar(const unsigned char c)
{
	while(U1STAbits.UTXBF == 1); // Wait until buffer is full
	U1TXREG = c;                 // Buffer the char to send
}

// Envoyer une chaine de caractère avec l'uart
void xbeeSendString (char* string)
{
	unsigned char i;
	for (i=0; string[i] != '\0'; i++)
		xbeeUartSendChar(string[i]);
}

// Envoyer un entier non signé  avec l'uart
void xbeeSendUnSignedInteger (uint32 n)
{
	// Ressources
	int i=0;
	char temp[5]="\0";
	char*pos;
	char buffer[4];
	pos=buffer;
			
	// Get the value
	while(n > 0)
	{
		*pos = '0' + n % 10;
		n /= 10;
		pos++;
	}

	pos--;
	for(;pos>=buffer;pos--)
	{
		temp[i]=*pos;
		i++;
	}
	temp[i]='\0';
	
	// Send the value
	xbeeSendString(temp);
}

// Récupérer l'entier suivant
uint8 xbeeUartGetInt()
{
	// Récupérer le caractère
	uint8 value = (unsigned char)U1RXREG;
	
	// Renvoyer la valeur
	return value;
}

// Récupérer la position de Baby Gali
bool getPositionBaby ()
{
	// Ressources
	uint8 i = 1;
		
	// En cas d'erreur
	if(U1STAbits.OERR)
	{
		U1STAbits.OERR = 0;
	}
	
	// Récupérer l'abscisse
	baby_Gali.x = 0;
	
	for (i = 1; i < 5; i++)
	{
		if (U1STAbits.URXDA == 0) i = 10; // Si aucune donnée n'est disponible sortir de la boucle
		else baby_Gali.x = baby_Gali.x*10 + xbeeUartGetInt();
	}
	
	// Si l'ordonnée a été reçue
	if (i < 10)
	{
		// Récupérer l'abscisse
		baby_Gali.y = 0;
		
		for (i = 1; i < 5; i++)
		{
			if (U1STAbits.URXDA == 0) i = 10; // Si aucune donnée n'est disponible sortir de la boucle
			baby_Gali.y = baby_Gali.y*10 +  xbeeUartGetInt();
		}
	}
		
	//  Modifier zone de check en fonction
	if (i < 10) return TRUE;	
	
	// Si les données étaient incomplètes réinitialiser les coordonnées de Baby Gali
	else
	{
		baby_Gali.y = -100;
		baby_Gali.x = -100;
		return FALSE;
	}
}

// Envoie la position de récupération à Baby gali
void sendPositionGali (uint16 x, uint16 y)
{
	xbeeSendUnSignedInteger (x);
	xbeeSendUnSignedInteger (y);
}
