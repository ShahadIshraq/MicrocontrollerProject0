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
#include <avr/interrupt.h>


volatile unsigned int score = 0 ;
volatile unsigned int over = 0;

ISR(INT0_vect)
{
    cli();
    score++;
    
    char buffer[7];
    sprintf(buffer, sizeof(buffer), "%d", score);
    Lcd4_Set_Cursor(1,0);
    Lcd4_Write_String("Score: ");
    Lcd4_Set_Cursor(2,0);
    Lcd4_Write_String(score);

    Lcd4_Clear();
    _delay_ms(1000);
    sei();
}

ISR(INT1_vect)
{
    cli();
    Lcd4_Clear();
    Lcd4_Set_Cursor(1,0);
    Lcd4_Write_String("Game over!!");
    _delay_ms(1000);
    over = 1;
    sei();
}

int main(void)
{
    DDRD = 0b11110000;
    DDRC = 0xFF;
    DDRB=0xff; //PORTB as OUTPUT
    
    score = 0;
    char buffer[7];
    
    Lcd4_Init();
    Lcd4_Clear();
    PORTB = 0xff;
    Lcd4_Set_Cursor(1,0);
    Lcd4_Write_String("The Game is");
    Lcd4_Set_Cursor(2,0);
    Lcd4_Write_String("ON!!");
    _delay_ms(1000);
    PORTB = 0x00;
    Lcd4_Clear();
    
    GICR = (1<<INT1 | 1<<INT0);
    MCUCR = MCUCR | 0b00001010;
    MCUCR = MCUCR & 0b11111010;
    sei();
    
    while(1)
    {
        if (over == 1)
        {
            break;
        }
        char buffer[7];
        sprintf(buffer, sizeof(buffer), "%d", score);
        Lcd4_Set_Cursor(1,0);
        Lcd4_Write_String("Score: ");
        Lcd4_Set_Cursor(2,0);
        Lcd4_Write_String(score);
    }
    Lcd4_Set_Cursor(1,0);
    Lcd4_Write_String("Kool");
    _delay_ms(10000);
}


// #define F_CPU 1000000UL
// #include <avr/io.h>
// #include <avr/interrupt.h>
// #include <util/delay.h>

// volatile unsigned int status;

// ISR(INT0_vect)
// {
//     GIFR &= 0b11111111;
//     if (status==0)
//     {
//         status=1;
//     }
//     else if (status==1)
//     {
//         PORTB = 0b10000000;
//         status=0;
//     }
//     _delay_ms(50);
    
// }

// ISR(INT1_vect)
// {
//     GIFR &= 0b11111111;
//     if (status==0)
//     {
//         status=1;
//     }
//     else if (status==1)
//     {
//         PORTB = 0b01000000;
//         status=0;
//     }
//     _delay_ms(50);
// }

// int main(void)
// {
//     status=0;
//     DDRB = 0xFF;
//     PORTB = 0b01000000;
//     PORTA = 0b10101011;
// //    GICR |= (1<<INT0);
//     GICR = (1<<INT1 | 1<<INT0);
//     MCUCR = MCUCR | 0b00001010;
//     MCUCR = MCUCR & 0b11111010;
//     sei();
//     while(1);
// }