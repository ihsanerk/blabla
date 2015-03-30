//	Library
#include "DetectionTourelle.h"

//	Variables
RobotDetecte 		robot;

//	Fonctions
void detectionTourelleInit ()
{
	// Initialise l'robot
	robot.angleRelatif = -100;
	robot.distanceRelative = -100;
	
	// Initialise l'uart
	tourelleUartInit ();
}

//	Fonctions
void tourelleUartInit ()
{
	// Setting the remapable pin 
	_U4RXR = 75; //Maping AX12RX to the RP104 pin
	_RP64R = 0b011101; //Maping U4TX to the RP98 pin

	//Init
	U4MODEbits.UARTEN  = 0;  // Disable UART
	U4MODEbits.ABAUD   = 0;  // Auto-Baud Disabled
	U4MODEbits.PDSEL   = 0;  // 8 bit, no parity
	U4MODEbits.STSEL   = 0;  // One stop bit
	U4MODEbits.BRGH    = 0;     // 0 = Mode which works
	
	//Baud rate setting
	U4BRG = 1;

	// Rx interrupt
	U4STAbits.URXISEL = 0;   // On each char
	_U4RXIF           = 0;   // Clear interrupt flag
	_U4RXIE           = 0;   // Disable interrupt
	_U4RXIP       	  = 0b010;// Priority : 4
	
	// Tx interrupt
	U4STAbits.UTXISEL0 = 0;   // On each char
	U4STAbits.UTXISEL1 = 0;   // On each char
	_U4TXIE           = 0;   // Disable interrupt
	
	// Enable UART
	U4MODEbits.UARTEN  = 1;  // Enable UART
	U4STAbits.UTXEN    = 1;  // Enable UART Tx
}

bool detectionTourelleProcess ()
{
	// Demander la position pour le prochain tour
	tourelleUartSendChar('n');
	
	// Récupérer la position renvoyée par la tourelle
	return getPositionRelativeEnnemi ();
}

void tourelleUartSendChar(const unsigned char c)
{
	while(U4STAbits.UTXBF == 1); // Wait until buffer is full
	U4TXREG = c;                 // Buffer the char to send
}

// Récupérer la position de Baby Gali
bool getPositionRelativeEnnemi ()
{
	// Ressources
	uint8 i = 1;
		
	// En cas d'erreur
	if(U4STAbits.OERR)
		U4STAbits.OERR = 0;

	// Récupérer l'angle
	robot.angleRelatif = 0;
	
	for (i = 1; i < 5; i++)
	{
		if (U4STAbits.URXDA == 0) i = 10; // Si aucune donnée n'est disponible sortir de la boucle
		else robot.angleRelatif = robot.angleRelatif*10 + tourelleUartGetInt();
	}
	
	// Si l'angle a été reçue
	if (i < 10)
	{
		// Récupérer la distance
		robot.distanceRelative = 0;
		
		for (i = 1; i < 5; i++)
		{
			if (U4STAbits.URXDA == 0) i = 10; // Si aucune donnée n'est disponible sortir de la boucle
			robot.distanceRelative = robot.distanceRelative*10 +  tourelleUartGetInt();
		}
	}
		
	//  Modifier zone de check en fonction
	if (i < 10) return TRUE; 
	
	// Si les données étaient incomplètes réinitialiser les coordonnées de l'ennemie
	else
	{
		robot.angleRelatif = -100;
		robot.distanceRelative = -100;
		return FALSE;
	}
}

// Récupérer l'entier suivant
uint8 tourelleUartGetInt()
{
	// Récupérer le caractère
	uint8 value = (unsigned char)U4RXREG;
	
	// Renvoyer la valeur
	return value;
}
