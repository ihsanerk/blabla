#include "configuration.h"


int main(void)
{
    oscillatorInit();
    pinConfiguration ();
    uart_init();
    int i =0;


 // Transmit one character
 
    
    
while(1)
{
        U2TXREG='c';
        //PORTFbits.RF3 = 1;
        for( i =0;i<150000;i++){}
        //PORTFbits.RF3 = 0;
        //for( i =0;i<150000;i++){}
}

}
