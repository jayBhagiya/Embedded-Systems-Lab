/*
 * LCD_Interfacing.c
 *
 * Created: 16-04-2021 19:22:37
 * Author : LENOVO
 */ 

/*! \mainpage 3_LCD_Interfacing
 *
 * \subsection Aim
 * To display string on LCD.
 *
 * \subsection Connections
 * LCD Connections:								<br>
 *		 LCD Pins	  Micro-controller Pins     <br>
 *			  RS  --> PC0						<br>
 *			  RW  --> PC1						<br>
 *			  EN  --> PC2						<br>
 *			  DB7 --> PC7						<br>
 *			  DB6 --> PC6						<br>
 *			  DB5 --> PC5						<br>
 *			  DB4 --> PC4						<br>
 *
 */


//---------------------------------- HEADER FILES -----------------------------------------------------
#include "pin_config.h"					// Header file included that contains macro definitions essential for lcd pin
#include <util/delay.h>					// Standard AVR Delay Library
#include <stdio.h>						// Library for standard Input Output	
#include "lcd.h"						// LCD Header file included that contains function definitions essential to deal with LCD

//---------------------------------- MAIN ----------------------------------------------------------------
/**
 * @brief      Main Function
 *
 * @details    First Initializes LCD and displays message on LCD
 */
int main(void) {
	
	lcd_port_config();					// Initialize the LCD port
	lcd_init();							// Initialize the LCD
	
	while(1)
	{
		// Display text on LCD at specific location
		lcd_string(1, 1, "Embedded Systems");
		lcd_string(2, 1, "Exp No. :");
		lcd_numeric_value(2, 11, 8, 1);
		_delay_ms(100);
		lcd_clear();
	}
}
//---------------------------------- END ------------------------------------------------------------------

