#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	//srand(time(null));
	DDRA=0xff;
	DDRB=0xff;
	DDRD=0xff;
//	MCUCSR = (1<<JTD);
    int i ;
	while(1)
	{
        for (i = 0; i < 8; ++i)
        {
            PORTA = 1<<i;
            PORTB = 1<<i;
            PORTD = 1<<i;
            _delay_ms(2);
        }
    }

}
