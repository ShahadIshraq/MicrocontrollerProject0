//**************************************************************//
//Microcontroller			:ATmega16
//System Clock				:1MHz 
//Project					:Analog IR Sensor Interfacing with ATmega16 and LED Display
//Software					:AVR Studio 4
//Author					:Arun Kumar Garg 
//							:ABLab Solutions
//							:www.ablab.in
//							:info@ablab.in
//Date						:1st January 2012
//**************************************************************//

#include<avr/io.h>
/*Includes io.h header file where all the Input/Output Registers and its Bits are defined for all AVR microcontrollers*/

#define	F_CPU	1000000
/*Defines a macro for the delay.h header file. F_CPU is the microcontroller frequency value for the delay.h header file. Default value of F_CPU in delay.h header file is 1000000(1MHz)*/

#include<util/delay.h>
/*Includes delay.h header file which defines two functions, _delay_ms (millisecond delay) and _delay_us (microsecond delay)*/

#include<avr/adc.h>
/*Includes adc.h header file which defines different functions for Analog to Digital Converter. ADC header file version is 1.1*/

int main(void)
{
	DDRB=0xff;
	/*All the 8 pins of PortB are declared output (LED array is connected)*/

	int analog_ir_sensor_value;
	/*Variable declarations*/

	adc_init();
	/*ADC initialization*/

	/*Start of infinite loop*/
	while(1)
	{
		analog_ir_sensor_value=read_adc_channel(0);
		/*Reading analog ir sensor value*/
		 
		PORTB=analog_ir_sensor_value;
		/*Lower 8 bit of analog ir sensor value is displayed in LED array*/

		_delay_ms(500);
		/*Value is displayed for 500ms*/

		PORTB=analog_ir_sensor_value>>8;
		/*Upper 2 bit of analog ir sensor value is displayed in LED array*/

		_delay_ms(500);
		/*Value is displayed for 500ms*/
	}
}
/*End of Program*/

