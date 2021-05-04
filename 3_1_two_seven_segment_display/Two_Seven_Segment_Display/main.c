/*
 * Two_Seven_Segment_Display.c
 *
 * Created: 22-02-2021 15:00:28
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
	DDRA = 0xFF;
    
	char array[] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6};
	int tenth_num = 0;
	while (1) 
    {
		PORTB = array[tenth_num++];
		
		for(int i=0; i<10; i++)
		{
			PORTA = array[i];
			_delay_ms(500);
		}
		
		if(tenth_num == 10)
			tenth_num = 0;
    }
}

