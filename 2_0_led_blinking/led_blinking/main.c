/*
 * led_blinking.c
 *
 * Created: 03-02-2021 15:30:33
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
		PORTA = 0x01;
		_delay_ms(1000);
		PORTA = 0x00;
		_delay_ms(1000);
    }
}

