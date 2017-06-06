/*
 * GccApplication1.c
 *
 * Created: 5/1/2017 3:00:24 PM
 *  Author: WhiteWalker
 */ 


#include <avr/io.h>
#include <stdio.h>
#define F_CPU 1000000UL
#include <util/delay.h>

unsigned char red[8];
unsigned char B[] = {
	0b10000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000001

};
unsigned char ret[8] ;

void init();
void draw(unsigned char * matrix);

int main(void)
{
	init();
	while(1)
	{
		draw(B);
	}
	
}


void init()
{
	DDRD = 0xFF; //Decoder
	DDRA = 0xFF; //Row (Red)
	//DDRB=0xff; //PORTB as OUTPUT
	

}

void draw(unsigned char * matrix)
{
	unsigned char i;
	for (i = 0; i < 15; ++i)
	{
		PORTD = i;
//		PORTA = 0b00100010;
		_delay_ms(900);
	}
}
