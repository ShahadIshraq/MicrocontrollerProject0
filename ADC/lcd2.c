/*
 * GccApplication1.c
 *
 * Created: 5/1/2017 3:00:24 PM
 *  Author: WhiteWalker
 */ 


#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTC6
#define EN eS_PORTC7

#include <avr/io.h>
#include <stdio.h>
#define F_CPU 1000000UL
#include <util/delay.h>
#include "lcd.h"


int main(void)
{
	unsigned int result;
	float volt;
	char buffer[7];
	
	DDRD = 0xFF;
	DDRC = 0xFF;
	//DDRB = 0xFF;
	
	ADMUX = 0b01100000;
	ADCSRA = 0b10000111;
	
	Lcd4_Init();
	Lcd4_Clear();
	
	Lcd4_Set_Cursor(1,0);
	Lcd4_Write_String("Patience!!");
	_delay_ms(5000);
	Lcd4_Clear();
	
	while(1) {
		ADCSRA |= (1<<ADSC);
		
		while( ADCSRA & (1<<ADSC) )
		;
		
		result = ADCL;
		result = (result>>6) | (ADCH<<2);
		//PORTB = result;
		
		//volt = (float)result*5.0/1024.0;
		snprintf(buffer, sizeof(buffer), "%d", result);
		
		Lcd4_Set_Cursor(1,0);
		Lcd4_Write_String("Result:");
		Lcd4_Set_Cursor(2,1);
		Lcd4_Write_String(buffer);
		_delay_ms(100);
		
	}
	
}
