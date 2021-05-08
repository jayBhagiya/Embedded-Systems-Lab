/*
 * SerialLib.c
 *
 * Created: 12/7/2016 12:30:34 PM
 * Author : Lenovo
 */ 

// Program to receive data from USART and displaying it on LCD
/*
Receive data from serial port and display it on LCD
LCD DATA port----PORT A
ctrl port------PORT B
rs-------PB0
rw-------PB1
en-------PB2
using external clock frequency 12MHz
*/

#define F_CPU 8000000UL
#define USART_BAUDRATE 9600 // Baud Rate value
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#include<avr/io.h>
#include<util/delay.h>

#define LCD_DATA PORTA //LCD data port

#define ctrl PORTB
#define en PB2 // enable signal
#define rw PB1 // read/write signal
#define rs PB0 // register select signal

void LCD_cmd(unsigned char cmd);
void init_LCD(void);
void LCD_write(unsigned char data);
void LCD_clear();

void usart_init();
void usart_putch(unsigned char send);
unsigned int usart_getch();

int main()
{
	unsigned char value;
	DDRA=0xff; // LCD_DATA port as output port
	DDRB=0x07; // signal as out put
	init_LCD(); //initialization of LCD
	_delay_ms(50); // delay of 50 milli seconds
	usart_init(); // initialization of USART
	while(1)
	{
		value=usart_getch(); // Call a function to get data from serial port
		LCD_cmd(0xC0); // to go in second line and zeroth  position on LCD
		LCD_write(value); // write data to LCD
	}
	return 0;
}

void init_LCD(void)
{
	LCD_cmd(0x38); // initialization of 16X2 LCD in 8bit mode
	_delay_ms(1);
	
	LCD_cmd(0x01); // clear LCD
	_delay_ms(1);
	
	LCD_cmd(0x0E); // cursor ON
	_delay_ms(1);
	
	LCD_cmd(0x80); // ---8 go to first line and --0 is for 0th position
	_delay_ms(1);
	return;
}

void LCD_cmd(unsigned char cmd)
{
	LCD_DATA=cmd;
	ctrl =(0<<rs)|(0<<rw)|(1<<en);
	_delay_ms(1);
	ctrl =(0<<rs)|(0<<rw)|(0<<en);
	_delay_ms(50);
	return;
}

void LCD_write(unsigned char data)
{
	LCD_DATA= data;
	ctrl = (1<<rs)|(0<<rw)|(1<<en);
	_delay_ms(1);
	ctrl = (1<<rs)|(0<<rw)|(0<<en);
	_delay_ms(50);
	return ;
}

void usart_init()
{
	UCSRB |= (1 << RXEN) | (1 << TXEN);   // Turn on the transmission and reception circuitry
	UCSRC |= (1 << URSEL) | (1<<USBS) | (1 << UCSZ0) | (1 << UCSZ1);
	// Use 8-bit character sizes
	
	UBRRL = BAUD_PRESCALE;
	// Load lower 8-bits of the baud rate value into the low byte of the UBRR register
	UBRRH = (BAUD_PRESCALE >> 8); // Load upper 8-bits of the baud rate value..
	// into the high byte of the UBRR register
}

unsigned int usart_getch()
{
	while ((UCSRA & (1 << RXC)) == 0);
	// Do nothing until data has been received and is ready to be read from UDR
	return(UDR); // return the byte
}