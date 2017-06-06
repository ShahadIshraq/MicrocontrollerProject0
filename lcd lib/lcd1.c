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
	float volt = 0.00;
	char buffer[7];
	
	DDRD = 0b11110000;
	DDRC = 0xFF;
	DDRB=0xff; //PORTB as OUTPUT
	
//	ADMUX = 0b01100000;
//	ADCSRA = 0b10000111;
	
	Lcd4_Init();
	Lcd4_Clear();
	PORTB = 0xff;
	Lcd4_Set_Cursor(1,0);
	Lcd4_Write_String("Start");
	_delay_ms(5000);
	PORTB = 0x00;
	Lcd4_Clear();
	// char a = '0';
	// unsigned char b = 1;
	// int pr = 2;
	// int po = 35;
	// char row = 1;
	// char col = 0;
	
	// Lcd4_Set_Cursor(0,0);
	while(1) {
		//PORTB = b;
		// if(b) b = 0;
		// else b = 1;
		//_delay_ms(800);
		// if(a == '9') a = '0';
		// else a++;


//		;
		
//		result = ADCL;
//		result = (result>>6) | (ADCH<<2);
		//PORTB = result;
		
//		volt = (float)result*5/1024.0;
//		int dec = (int)(volt);
//		snprintf(buffer, sizeof(buffer), "%d.%d", dec,(int)((volt-dec)*100));
		Lcd4_Clear();
		Lcd4_Set_Cursor(1,0);
		Lcd4_Write_String("Hoise");
		PORTB = 0xff;
		_delay_ms(500);
		PORTB = 0x00;
		_delay_ms(500);		
	}
	
}
