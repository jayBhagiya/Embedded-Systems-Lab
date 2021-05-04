/*
 * led_pattern_2.c
 *
 * Created: 03-02-2021 19:33:52
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
		for (int i=3; i>=0; i--)
		{
			PORTA |= (1 << i);
			PORTA |= (1 << (7-i));
			_delay_ms(500);
		}
		for (int i=0; i<4; i++)
		{
			PORTA &= ~(1 << i);
			PORTA &= ~(1 << (7-i));
			_delay_ms(500);
		}
    }
}

