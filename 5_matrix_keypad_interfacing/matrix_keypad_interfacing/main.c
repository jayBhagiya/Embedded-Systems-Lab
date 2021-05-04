/*
 * matrix_keypad_interfacing.c
 *
 * Created: 04-05-2021 08:58:09
 * Author : LENOVO
 */ 

#include <avr/io.h>
#include <util/delay.h>

#if defined(__AVR_ATmega2560__)

	#ifndef F_CPU
	#define F_CPU 14745600
	#endif
	
	//---------------------------------- INPUT / OUTPUT PERIPHERALS -----------------------------------------------------

	// Seven Segment definitions
	#define seven_seg_ddr_reg		DDRA
	#define seven_seg_port_reg		PORTA
	
	// Matrix Column definitions
	#define matrix_col_ddr_reg		DDRF
	#define matrix_col_port_reg		PORTF
	#define matrix_col_1_pin		PF0
	#define matrix_col_2_pin		PF1
	#define matrix_col_3_pin		PF2
	#define matrix_col_4_pin		PF3
	
	// Matrix Row Definitions
	#define matrix_row_ddr_reg		DDRB
	#define matrix_row_port_reg		PORTB
	#define matrix_row_pin_reg		PINB
	#define matrix_row_1_pin		PB0
	#define matrix_row_2_pin		PB1
	#define matrix_row_3_pin		PB2
	#define matrix_row_4_pin		PB3
	
#endif
// ----------------------------------------- Functions -----------------------------------------

//-----------------------------CONFIGURATION FUNCTIONS --------------------------------------------------

/**
 * @brief      Function to make **ONLY** Configuration of Seven Segment Display.
 */
void seven_seg_config(void)
{
	// Make **ONLY** all pins as output
	seven_seg_ddr_reg = 0xFF;
	
	// Make **ONLY** set all pins initially low
	seven_seg_port_reg = 0x00;
}

/**
 * @brief      Function to make **ONLY** Configuration of Columns of matrix.
 */
void matrix_col_pin_config(void)
{
	// Make **ONLY** Four column pins as output
	matrix_col_ddr_reg |= ((1 << matrix_col_1_pin) | (1 << matrix_col_2_pin) | (1 << matrix_col_3_pin) | (1 << matrix_col_4_pin));
	
	// Make **ONLY** Disabling all columns witout disturbing reamianing pins
	matrix_col_port_reg &= ~((1 << matrix_col_1_pin) | (1 << matrix_col_2_pin) | (1 << matrix_col_3_pin) | (1 << matrix_col_4_pin));
}

/**
 * @brief      Function to make **ONLY** Configuration of Rows of matrix.
 */
void matrix_row_pin_config(void)
{
	// Make **ONLY** Four row pins defined as input
	matrix_row_ddr_reg &= ~((1 << matrix_row_1_pin) | (1 << matrix_row_2_pin) | (1 << matrix_row_3_pin) | (1 << matrix_row_4_pin));
	
	// Make **ONLY** Disabling all pull-up resister on four rows witout disturbing reamianing pins
	matrix_row_port_reg &= ~((1 << matrix_row_1_pin) | (1 << matrix_row_2_pin) | (1 << matrix_row_3_pin) | (1 << matrix_row_4_pin));
}

// ----------------------------------------- Main ----------------------------------------- 
int main(void)
{
	seven_seg_config();
	matrix_col_pin_config();
	matrix_row_pin_config();
	
     while (1)
     {
	     char array[] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6, 0xEE, 0x3E, 0x9C, 0x7A, 0x9E, 0x8E};
		           //   {   0,    1,    2,    3,    4,    5,    6,    7,    8,    9,    A,    B,    C,    D,    E,    F}
		 int key=0, column = 0, temp = 0;
	     for (column=1,temp=1; column<=4; temp*=2,column++)
	     {
			 // Make **ONLY** Disabling all pull-up resister on four rows witout disturbing reamianing pins
			 matrix_col_port_reg &= ~((1 << matrix_col_1_pin) | (1 << matrix_col_2_pin) | (1 << matrix_col_3_pin) | (1 << matrix_col_4_pin));
			 matrix_col_port_reg |= temp;
			 
			 // Reading rows data and identify the key
			 switch(matrix_row_pin_reg & ((1 << matrix_row_1_pin) | (1 << matrix_row_2_pin) | (1 << matrix_row_3_pin) | (1 << matrix_row_4_pin)))
			 {
				 case (1 << matrix_row_1_pin):{			// row1
					 key = column;
				 }break;
				 
				 case (1 << matrix_row_2_pin):{			// row2
					 key = 4 + column;
				 }break;
				 
				 case (1 << matrix_row_3_pin):{			// row3
					 key = 8 + column;
				 }break;
				 
				 case (1 << matrix_row_4_pin):{			// row4
					 key = 12 + column;
				 }break;
			 }
		     _delay_ms(10);  // Key debounce
	     }
		 if((key < 0) || (key > 15) ){
			 seven_seg_port_reg = array[0];
		 }
		 else{
			 seven_seg_port_reg = array[key];
		 }
     }
}

