/*
 * Simple_Seven_Segment_led.c
 *
 * Created: 22-02-2021 14:25:15
 * Author : LENOVO
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL //clock speed is 16MHz
#endif
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRB = 0xFF;
    while (1) 
    {
		char array[] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6};
		for (int i=0; i<=9; i++)
		{
			PORTB = array[i];
			_delay_ms(1000);
		}
    }
}

