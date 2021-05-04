/*
 * led_pattern_1.c
 *
 * Created: 03-02-2021 18:56:24
 * Author : LENOVO
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL //clock speed is 16MHz
#endif

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    DDRA = 0xFF;
    while (1) 
    {
		for (int i=0; i<8; i++)
		{
			PORTA = (0x01 << i);
			_delay_ms(500);
			PORTA = 0x00;
		}
    }
}

