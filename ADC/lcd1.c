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
#include "adc.h"


int main(void)
{
	unsigned int result;
	float volt = 0.00;
	char buffer[7];

	Lcd4_Init();
	Lcd4_Clear();
	PORTB = 0xff;
	Lcd4_Set_Cursor(1,0);
	Lcd4_Write_String("Start");
	_delay_ms(5000);
	PORTB = 0x00;
	 Lcd4_Clear();

	DDRD = 0xFF;
	DDRC = 0xFF;
	DDRB=0xff; //PORTB as OUTPUT
	
	int analog_ir_sensor_value;
	/*Variable declarations*/

	adc_init();
	/*ADC initialization*/
	
	
	while(1) {

		analog_ir_sensor_value = read_adc_channel(0);
		/*Reading analog ir sensor value*/
		 
//		volt = (float)result*5/1024.0;
//		int dec = (int)(volt);

		snprintf(buffer, sizeof(buffer), "%d",analog_ir_sensor_value );
		Lcd4_Clear();
		Lcd4_Set_Cursor(1,0);
		Lcd4_Write_String(buffer);
	}
	
}
