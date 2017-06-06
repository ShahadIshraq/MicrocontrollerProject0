/* port_test.c
 * The following program just  keeps toggling pin 0 of port B
 */

#include <avr/io.h>
#include <stdio.h>
#define F_CPU 1000000UL
#include <util/delay.h>

/* _BV(a) is a macro which returns the value corresponding to 2 to the power 'a'. Thus _BV(PX3) would be 0x08 or 0b00001000 */

void main(void)
{
	DDRD=0xff; //PORTB as OUTPUT
	PORTD=0x00; //All pins of PORTB LOW

	unsigned int i;
	unsigned char t = 0;
	while(1) //Infinite loop
	{
		PORTD = t;			
		_delay_ms(100);
		if(t==0) t = 0xFF;
		else t = 0;
	}
}
