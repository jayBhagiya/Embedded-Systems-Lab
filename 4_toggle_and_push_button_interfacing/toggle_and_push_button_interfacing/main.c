/*
 * toggle_and_push_button_interfacing.c
 *
 * Created: 03-05-2021 17:26:37
 * Author : LENOVO
 */ 

#include <avr/io.h>
#include <util/delay.h>

// Definitions for ATmega2560 and Interfacing of Toggle and push button 
#if defined(__AVR_ATmega2560__)
	
	#define toggle_button_ddr_reg		DDRF
	#define toggle_button_port_reg		PORTF
	#define toggle_button_pin_reg		PINF
	#define toggle_button_pin			PF1
	
	#define push_button_ddr_reg			DDRF
	#define push_button_port_reg		PORTF
	#define push_button_pin_reg			PINF	
	#define push_button_pin				PF0	
	
	#define led_ddr_reg					DDRA
	#define led_port_reg				PORTA
	#define led_1_pin					PA0
	#define led_2_pin					PA1

#endif

//---------------------------------- FUNCTIONS ---------------------------------------------------------

//-----------------------------CONFIGURATION FUNCTIONS --------------------------------------------------

/**
 * @brief      Function to make **ONLY** Toggle and push button Switch pin as input and pull it up internally
 */
void toggle_and_push_button_switch_config (void) {

	// Make **ONLY** Toogle Switch pin as input
	toggle_button_ddr_reg &= ~( 1 << toggle_button_pin );

	// Make **ONLY** Toggle Switch pin internally pull-up	
	toggle_button_port_reg |= ( 1 << toggle_button_pin );
	
	// Make **ONLY** Push button Switch pin as input
	push_button_ddr_reg &= ~( 1 << push_button_pin );

	// Make **ONLY** Push button Switch pin internally pull-up
	push_button_port_reg |= ( 1 << push_button_pin );
		
}

/**
 * @brief      Function to make **ONLY** 'led_1_pin' and 'led_2_pin' as output and initially set it to low
 */
void led_pin_config (void) {

	// Make 'led_1_pin' as output
	led_ddr_reg	|= ( 1 << led_1_pin );
	
	// Set 'led_1_pin' to low initially
	led_port_reg &= ~( 1 << led_1_pin );
	
	// Make 'led_2_pin' as output
	led_ddr_reg	|= ( 1 << led_2_pin );
	
	// Set 'led_2_pin' to low initially
	led_port_reg &= ~( 1 << led_2_pin );
}

//------------------------------------- LED RELATED FUNCTIONS -----------------------------------------

/**
 * @brief      Function to set LED 1 pin to high, hence turn on LED 1
 */
void led_1_on(void){
	// Turn on all LEDs
	led_port_reg |= (1 << led_1_pin);
}

/**
 * @brief      Function to set LED 1 pin to low, hence turn off LED 1
 */
void led_1_off(void){
	// Turn off all LEDs
	led_port_reg &= ~(1 << led_1_pin);
}

/**
 * @brief      Function to set LED 2 pin to high, hence turn on LED 2
 */
void led_2_on(void){
	// Turn on all LEDs
	led_port_reg |= (1 << led_2_pin);
}

/**
 * @brief      Function to set LED 2 pin to low, hence turn off LED 2
 */
void led_2_off(void){
	// Turn off all LEDs
	led_port_reg &= ~(1 << led_2_pin);
}

//---------------------------------- MAIN ----------------------------------------------------------------

int main(void)
{
	// Initialize the necessary devices (Led, Toggle and push button switch) required for the experiment.
	toggle_and_push_button_switch_config();
	led_pin_config();
    
    while (1) 
    {
		// If the push button Switch is NOT pressed
		if ((push_button_pin_reg & (1 << push_button_pin)) == (1 << push_button_pin)) {
			_delay_ms(100);
			led_1_off(); 			//Turn off LED 1
		} 
		else {
			_delay_ms(100);
			led_1_on(); 			//Turn on LED 1
		}
		if ((toggle_button_pin_reg & (1 << toggle_button_pin)) == (1 << toggle_button_pin)) {
			_delay_ms(100);
			led_2_off(); 			//Turn off LED 2
		}
		else {
			_delay_ms(100);
			led_2_on(); 			//Turn on LED 2
		}
    }
}

