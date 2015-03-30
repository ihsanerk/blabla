// Libraries
#include "Debugger.h"

//Variable
int32 counter;
bool angle_distance; // TRUE angle et FALSE distance

// Initialise le debugger
void debuggerInit ()
{
	//LED
	_TRISD6 = 0;
	_TRISD5 = 0;
	_TRISD4 = 0;
	_TRISD13 = 0;
	_TRISD12 = 0;
	_TRISD3 = 0;
	_TRISD2 = 0;
	_TRISD1 = 0;
	
	//Counter
	counter = 0;
	angle_distance = TRUE;
}

// Envoyer une chaine de caractère avec l'uart
void sendString (char* string)
{
	unsigned char i;
	for (i=0; string[i] != '\0'; i++)
		uartSendChar(string[i]);
}

// Envoyer un entier  avec l'uart
void sendSignedInteger (int32 n)
{
        int i=0;
        char temp[15]="\0";
        if(n < 0)
        {
            temp[i]='-';
            i++;
            temp[i]='\0';
            n=-n;
        }
        if(n == 0)
        {
                temp[i]='0';
                i++;
                temp[i]='\0';
        }
        else{
            char*pos;
            char buffer[12];
                    pos=buffer;
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
        }
        sendString(temp);
}

// Envoyer un entier  avec l'uart
void sendUnSignedInteger (uint32 n)
{
        int i=0;
        char temp[15]="\0";

        if(n == 0)
        {
			temp[i]='0';
			i++;
			temp[i]='\0';
        }
        else
		{
			char*pos;
			char buffer[13];
			pos=buffer;
			
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
        }
        sendString(temp);
}

// Affichages
void displaySharp ()
{
	/*sendString (" | Sharp 1 = ");
	sendSignedInteger (getSharp(0));
	sendString (" | Sharp 2 = ");
	sendSignedInteger (getSharp(1));
	sendString (" | Sharp 3 = ");
	sendSignedInteger (getSharp(2));
	sendString (" | Sharp 4 = ");
	sendSignedInteger (getSharp(3));*/
}

void displayPos ()
{
	/*sendString (" | X = ");
	sendSignedInteger (gali.x);
	sendString (" | Y = ");
	sendSignedInteger (gali.y);
	sendString (" | Angle = ");
	sendSignedInteger (gali.angle);*/
}

void displayAsser ()
{
	//sendString (" | Ordre = ");
	//sendSignedInteger (angle.ordre);
	/*sendString (" | Erreur = ");
	sendSignedInteger (angle.erreur);
	//sendString (" | Ordre = ");
	//sendSignedInteger (distance.ordre);
	sendString (" | Erreur = ");
	sendSignedInteger (distance.erreur);
	sendString (" | droit = ");
	sendSignedInteger (codeurDroit.variation);
	sendString (" | gauche = ");
	sendSignedInteger (codeurGauche.variation);*/
	
	/*sendString ("\n\r");
	sendString (" | Roue gauche = ");
	sendSignedInteger (roueGauche.erreur);
	sendString (" | Roue droite = ");
	sendSignedInteger (roueDroite.erreur);*/
}

//	Reguler le PID
void regulationPD ()
{
	/*if (counter > 5)
	{
		switch (recievedChar)
		{
			case 'a':
					if (angle_distance) angle.coefProportionnel += 1;
					else distance.coefProportionnel += 1;
					break;
			
			case 'q':
					if (angle_distance) angle.coefProportionnel -= 1;
					else distance.coefProportionnel -= 1;
					break;
			
			case 'z':
					if (angle_distance) angle.coefProportionnel += 10;
					else distance.coefProportionnel += 10;
					break;
					
			case 's':
					if (angle_distance) angle.coefProportionnel -= 10;
					else distance.coefProportionnel -= 10;
					break;
			
			case 'e':
					if (angle_distance) angle.coefProportionnel += 100;
					else distance.coefProportionnel += 100;
					break;
			
			case 'd':
					if (angle_distance) angle.coefProportionnel -= 100;
					else distance.coefProportionnel -= 100;
					break;
					
			case 'r':
					if (angle_distance) angle.coefProportionnel += 1000;
					else distance.coefProportionnel += 1000;
					break;
			
			case 'f':
					if (angle_distance) angle.coefProportionnel -= 1000;
					else distance.coefProportionnel -= 1000;
					break;
			
			case 'u':
					if (angle_distance) angle.coefDerive += 1;
					else distance.coefDerive += 1;
					break;
					
			case 'j':
					if (angle_distance) angle.coefDerive -= 1;
					else distance.coefDerive -= 1;
					break;
			
			case 'i':
					if (angle_distance) angle.coefDerive += 10;
					else distance.coefDerive += 10;
					break;
			
			case 'k':
					if (angle_distance) angle.coefDerive -= 10;
					else distance.coefDerive -= 10;
					break;
					
			case 'o':
					if (angle_distance) angle.coefDerive += 100;
					else distance.coefDerive += 100;
					break;
			
			case 'l':
					if (angle_distance) angle.coefDerive -= 100;
					else distance.coefDerive -= 100;
					break;
			
			case 'p':
					if (angle_distance) angle.coefDerive += 1000;
					else distance.coefDerive += 1000;
					break;
					
			case 'm':
					if (angle_distance) angle.coefDerive -= 1000;
					else distance.coefDerive -= 1000;
					break;
			
			case 'w':
					angle.erreur = 0;
					distance.erreur = 0;
					break;
					
			case ' ':
					angle_distance = !angle_distance;
					//listeAsserInit();
					
					if (angle_distance)
					{
						angle.enable = TRUE;
						distance.enable = FALSE;
					angle.VMax = 1000;
					distance.VMax = 600;
					}
					else
					{
						angle.enable = TRUE;
						distance.enable = TRUE;
						angle.VMax = 600;
					distance.VMax = 1000;
					}
					break;
		}
		
		// Afficher les valeurs
		if (angle_distance)
		{
			sendString ("\n\rAngle: P = ");
			sendSignedInteger (angle.coefProportionnel);
			sendString (" | D = ");
			sendSignedInteger (angle.coefDerive);
			sendString (" | Ordre = ");
			sendSignedInteger (angle.ordre);
			sendString (" | Erreur = ");
			sendSignedInteger (angle.erreur);
		}
		
		else
		{
			sendString ("\n\rDistance: P = ");
			sendSignedInteger (distance.coefProportionnel);
			sendString (" | D = ");
			sendSignedInteger (distance.coefDerive);
			sendString (" | Ordre = ");
			sendSignedInteger (distance.ordre);
			sendString (" | Erreur = ");
			sendSignedInteger (distance.erreur);
		}
		
		//Réinitialiser counter et le caractère
		counter = 0;
		recievedChar = 'x';
	}
	
	else counter++;*/
}
