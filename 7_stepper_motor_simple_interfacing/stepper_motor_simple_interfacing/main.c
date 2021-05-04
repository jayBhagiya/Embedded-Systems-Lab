/*
 * stepper_motor_simple_interfacing.c
 *
 * Created: 04-05-2021 14:03:58
 * Author : LENOVO
 */ 

#include <avr/io.h>
#include <util/delay.h>

#if defined(__AVR_ATmega2560__)

	#define		F_CPU							14745600
	
	//---------------------------------- INPUT / OUTPUT PERIPHERALS -----------------------------------------------------
	
	// Motor direction registers and pins
	#define 	stepper_motor_ddr_reg				DDRC
	#define 	stepper_motor_port_reg				PORTC
	#define		stepper_motor_1_pin					PC0
	#define		stepper_motor_2_pin					PC1
	#define		stepper_motor_3_pin					PC2
	#define		stepper_motor_4_pin					PC3

#endif

//---------------------------------- FUNCTIONS ----------------------------------------------------------

//-----------------------------CONFIGURATION FUNCTIONS --------------------------------------------------

/**
 * @brief      Function to configure stepper motor pins
 */
void stepper_motor_pin_config(void) {
	// Setting all the pins of stepper motor as output pins
	stepper_motor_ddr_reg |= ((1 << stepper_motor_1_pin) | (1 << stepper_motor_2_pin) | (1 << stepper_motor_3_pin) | (1 << stepper_motor_4_pin));
	
	// Initially setting all of them low
	stepper_motor_port_reg &= ~((1 << stepper_motor_1_pin) | (1 << stepper_motor_2_pin) | (1 << stepper_motor_3_pin) | (1 << stepper_motor_4_pin));
}


//---------------------------------- MAIN ----------------------------------------------------------------

int main(void)
{
    stepper_motor_pin_config();
	
	int period = 100;
	
    while (1) 
    {
		/* Rotate Stepper Motor clockwise with full step sequence */
		stepper_motor_port_reg = 0x09;
		_delay_ms(period);
		stepper_motor_port_reg = 0x08;
		_delay_ms(period);
		stepper_motor_port_reg = 0x0C;
		_delay_ms(period);
		stepper_motor_port_reg = 0x04;
		_delay_ms(period);
		stepper_motor_port_reg = 0x06;
		_delay_ms(period);
		stepper_motor_port_reg = 0x02;
		_delay_ms(period);
		stepper_motor_port_reg = 0x03;
		_delay_ms(period);
		stepper_motor_port_reg = 0x01;
		_delay_ms(period);

		stepper_motor_port_reg = 0x09;		/* Last step to initial position */
		_delay_ms(period);
		_delay_ms(1000);
		
		/* Rotate Stepper Motor Anti-clockwise with full step sequence */
		stepper_motor_port_reg = 0x01;
		_delay_ms(period);
		stepper_motor_port_reg = 0x03;
		_delay_ms(period);
		stepper_motor_port_reg = 0x02;
		_delay_ms(period);
		stepper_motor_port_reg = 0x06;
		_delay_ms(period);
		stepper_motor_port_reg = 0x04;
		_delay_ms(period);
		stepper_motor_port_reg = 0x0C;
		_delay_ms(period);
		stepper_motor_port_reg = 0x08;
		_delay_ms(period);
		stepper_motor_port_reg = 0x09;
		_delay_ms(period);
		
		stepper_motor_port_reg = 0x09;		/* Last step to initial position */
		_delay_ms(period);
		_delay_ms(1000);
    }
}

