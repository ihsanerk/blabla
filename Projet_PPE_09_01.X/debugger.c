//Librairies
#include "debugger.h"

//Initialise le débugger
void debugger_init()
{

}

// Envoyer une chaine de caractère avec l'uart
void sendString (char* string)
{
	unsigned char i;
	for (i=0; string[i] != '\0'; i++)
		uartSendChar(string[i]);
}

// Envoyer un entier  avec l'uart
void sendSignedInteger (int32_t n)
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
void sendUnSignedInteger (uint32_t n)
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
