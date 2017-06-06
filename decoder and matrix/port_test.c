/* port_test.c
 * The following program just  keeps toggling pin 0 of port B
 */

#include <avr/io.h> //standard include for ATMega16
#define sbi(x,y) x |= _BV(y) //set bit - using bitwise OR operator
#define cbi(x,y) x &= ~(_BV(y)) //clear bit - using bitwise AND operator
#define tbi(x,y) x ^= _BV(y) //toggle bit - using bitwise XOR operator
#define is_high(x,y) (x & _BV(y) == _BV(y)) //check if the y'th bit of register 'x' is high ... test if its AND with 1 is 1

/* _BV(a) is a macro which returns the value corresponding to 2 to the power 'a'. Thus _BV(PX3) would be 0x08 or 0b00001000 */

void main(void)
{
	DDRB=0xff; //PORTB as OUTPUT
	PORTB=0x00; //All pins of PORTB LOW

	unsigned int i;
	unsigned char t = 1;
	while(1==1) //Infinite loop
	{
		PORTB = t;			
		for(i=0;i<65535*2;i++); //delay
		for(i=0;i<65535*2;i++); //delay
		if(t) t = 0;
		else t = 1;
	}
}
