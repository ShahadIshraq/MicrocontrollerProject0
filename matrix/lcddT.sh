#!/bin/bash
if [ $1  = "32" ]; then
	echo "ATmega 32"
	avr-gcc -w -mmcu=atmega32 -c test.c
	echo "Compiled"
	avr-gcc -w -mmcu=atmega32 test.o -o test
	echo "Built executable"
	avr-objcopy -O ihex test test.hex
	echo "Built hex"
	sudo avrdude -c usbasp -p m32 -U flash:w:test.hex
else	
	echo "ATmega 16"
	avr-gcc -w -mmcu=atmega16 -c test.c
	echo "Compiled"
	avr-gcc -w -mmcu=atmega16 test.o -o test
	echo "Built executable"
	avr-objcopy -O ihex test test.hex
	echo "Built hex"
	sudo avrdude -c usbasp -p m16 -U flash:w:test.hex
fi

