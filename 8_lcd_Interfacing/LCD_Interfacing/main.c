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
 * Current Sensor Connections					<br>
 *		Sensor pins		Micro-controller Pins	<br>
 *				out --> PF1						<br>
 *
 */


//---------------------------------- HEADER FILES -----------------------------------------------------
#include "pin_config.h"					// Header file included that contains macro definitions essential for lcd pin
#include <util/delay.h>					// Standard AVR Delay Library
#include <stdio.h>						// Library for standard Input Output	
#include "lcd.h"						// LCD Header file included that contains function definitions essential to deal with LCD

//---------------------------------- GLOBAL VARIABLES -----------------------------------------------------
unsigned char ADC_Value;

//---------------------------------- FUNCTIONS -----------------------------------------------------

/**
 * @brief      Function to make all ADC sensor pins as input and deactivate pull up for all pins
 */
void adc_port_config (void)
{
	current_sensor_ddr_reg	= 0x00;				// set PORTF direction as input
	current_sensor_port_reg	= 0x00;				// set PORTF pins floating
}

/**
 * @brief      Initializes the Analog-to-Digital converter inside the micro-controller
 */
void adc_init(){
	
	// enable ADC and pre-scalar = 64 (ADEN = 1, ADPS2 = 1, ADPS1 = 1, ADPS0 = 0)
	// and clear ADC start conversion bit, auto trigger enable bit, interrupt flag bit and interrupt enable bit
	ADCSRA_reg	|= ( (1 << ADEN_bit) | (1 << ADPS2_bit) | (1 << ADPS1_bit) );
	ADCSRA_reg	&= ~( (1 << ADSC_bit) | (1 << ADATE_bit) | (1 << ADIF_bit) | (1 << ADIE_bit) | (1 << ADPS0_bit) );
	
	// In ADCSRB, disable Analog Comparator Multiplexer, MUX5 bit and ADC Auto Trigger Source bits
	ADCSRB_reg	&= ~( (1 << ACME_bit) | (1 << MUX5_bit) | (1 << ADTS2_bit) | (1 << ADTS1_bit) | (1 << ADTS0_bit) );
	
	// In ADMUX, set the Reference Selection bits to use the AVCC as reference, and disable the channel selection bits MUX[4:0]
	ADMUX_reg	&= ~( (1 << REFS1_bit) | (1 << MUX4_bit) | (1 << MUX3_bit) | (1 << MUX2_bit) | (1 << MUX1_bit) | (1 << MUX0_bit) );
	ADMUX_reg	|= (1 << REFS0_bit);
	
	// In ADMUX, enable the ADLAR bit for 8-bit ADC result
	ADMUX_reg	|= (1 << ADLAR_bit);
	
	// In ACSR, disable the Analog Comparator by writing 1 to ACD_bit
	ACSR_reg	|= ( 1 << ACD_bit );
}

/**
 * @brief      Convert the analog readings to 8-bit digital format from the sensor's ADC channel number as input
 *
 * @param[in]  sensor_channel_number   ADC channel number of sensor
 *
 * @return     8-bit digital data from the input sensor ADC channel
 */
unsigned char ADC_Conversion(unsigned char channel_num)
{
	unsigned char adc_8bit_data;
	
	// MUX[5:0] bits to select the ADC channel number
	if ( channel_num > 7 )
	{
		ADCSRB_reg |= ( 1 << MUX5_bit );					// set the MUX5 bit for selecting channel if its greater than 7
	}
	channel_num	= channel_num & 0x07;						// retain the last 3 bits from the variable for MUX[2:0] bits
	ADMUX_reg	= ( ADMUX_reg | channel_num );
	
	// set the ADSC bit in ADCSRA register
	ADCSRA_reg		|= ( 1 << ADSC_bit );
	
	//Wait for ADC conversion to complete
	while( ( ADCSRA_reg & ( 1 << ADIF_bit ) ) == 0x00 );
	
	adc_8bit_data = ADCH_reg;
	
	// clear ADIF bit by writing 1 to it
	ADCSRA_reg		|= ( 1 << ADIF_bit );
	
	// clear the MUX5 bit
	ADCSRB_reg		&= ~( 1 << MUX5_bit );
	
	// clear the MUX[4:0] bits
	ADMUX_reg		&= ~( (1 << MUX4_bit) | (1 << MUX3_bit) | (1 << MUX2_bit) | (1 << MUX1_bit) | (1 << MUX0_bit) );
	
	return adc_8bit_data;
}

/**
 * @brief      Displays Converted 8-bit digital data from the sensor's ADC channel on LCD
 *
 * @param[in]  row   LCD row 1 or 2
 * @param[in]  column LCD column 1 to 16
 * @param[in]  channel ADC channel number of sensor 0 to 15
 *
 */
void print_sensor(char row, char coloumn,unsigned char channel)
{
	ADC_Value = ADC_Conversion(channel);
	lcd_numeric_value(row, coloumn, ADC_Value, 3);
}

//---------------------------------- MAIN ----------------------------------------------------------------
/**
 * @brief      Main Function
 *
 * @details    First Initializes LCD and displays message on LCD
 */
int main(void) {
	
	//unsigned int value;
	adc_port_config();					// Initialize the ADC port
	adc_init();
	
	lcd_port_config();					// Initialize the LCD port
	lcd_init();							// Initialize the LCD
	
	lcd_string(1, 1, "ADC Value:");
	
	while(1)
	{
		// Display text on LCD at specific location
		print_sensor(1, 11, current_sensor_port_reg);
	}
}
//---------------------------------- END ------------------------------------------------------------------

