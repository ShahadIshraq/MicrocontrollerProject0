/*
 * GccApplication2.c
 *
 * Created: 4/25/2017 11:09:58 AM
 *  Author: WhiteWalker
 */ 


#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

void drawCharRed(unsigned char *);
void matrixRotateLeft(unsigned char *);
void flush() ;

unsigned char M[] = {
	/*0b11000111,
	0b10111011,
	0b01010101,
	0b01111110,
	0b01011010,
	0b01100101,
	0b10111011,
	0b11000111*/
	
	0b01111111,
	0b11111111,
	0b11111111,
	0b11111101,
	0b11111111,
	0b11111101,
	0b10111111,
	0b11111111
};

int main(void)
{
	
	DDRA=0xff;
	DDRB=0xff;
	while(1)
	{
		drawCharRed(M);
		//flush();
		//matrixRotateLeft(M);
		//_delay_ms(50);
		
	}
}

void flush(){
	DDRB = 0xff;
	_delay_ms(400) ;	
}



void drawCharRed(unsigned char *character)
{
	int i,j;
	PORTB = 0xFF;
	for (i=0; i<25; i++)
	{
		unsigned char row = 1;
		for (j=0; j<8; j++)
		{
			PORTA = row ;
			row = row << 1 ;
			if (row == 0) row = 1 ;
			PORTB = character[j];
			_delay_ms(2);
		}
		
	}
}


void matrixRotateLeft(unsigned char *character)
{
	int i;
	for (i=0; i<=7; i++)
	{
		unsigned char MSB = character[i] & 0b10000000;
		MSB = MSB >> 7;
		character[i] = character[i] << 1;
		character[i] = character[i] | MSB;
	}
}
