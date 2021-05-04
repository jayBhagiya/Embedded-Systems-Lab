/*
 * dc_motor_control_simple_interfacing.c
 *
 * Created: 04-05-2021 13:20:53
 * Author : LENOVO
 */ 

#include <avr/io.h>
#include <util/delay.h>

#if defined(__AVR_ATmega2560__)

	#define		F_CPU							14745600

	//---------------------------------- INPUT / OUTPUT PERIPHERALS -----------------------------------------------------
	
	// Motor direction registers and pins
	#define 	motors_dir_ddr_reg				DDRA
	#define 	motors_dir_port_reg				PORTA
	#define 	motors_RB_pin					PA3			// 3
	#define 	motors_RF_pin					PA2			// 2
	#define 	motors_LF_pin					PA1			// 1
	#define 	motors_LB_pin					PA0			// 0
	
	// Motor enable registers and pins
	#define 	motors_pwm_ddr_reg				DDRL
	#define 	motors_pwm_port_reg				PORTL
	#define 	motors_pwm_R_pin				PL4			// 4
	#define 	motors_pwm_L_pin				PL3			// 3
	
#endif

//---------------------------------- FUNCTIONS ----------------------------------------------------------

//-----------------------------CONFIGURATION FUNCTIONS --------------------------------------------------

/**
 * @brief      Function to configure motor pins
 */
void motors_pin_config(void) {
	motors_dir_ddr_reg |= (1 << motors_RB_pin) | (1 << motors_RF_pin) | (1 << motors_LF_pin) | (1 << motors_LB_pin) ;			// motor pin as output
	motors_dir_port_reg &=  ~( (1 << motors_RB_pin) | (1 << motors_RF_pin) | (1 << motors_LF_pin) | (1 << motors_LB_pin) );		// stop motor initially
}

/**
 * @brief      Function to configure left and right channel pins of the L293D Motor Driver IC for PWM
 */
void pwm_pin_config(void){
	motors_pwm_ddr_reg |= (1 << motors_pwm_R_pin) | (1 << motors_pwm_L_pin);	// left and right channel pin as output
	motors_pwm_port_reg |= (1 << motors_pwm_R_pin) | (1 << motors_pwm_L_pin);	// turn on left and right channel
}

//----------------------------- MOTION RELATED FUNCTIONS ----------------------------------------------

/**
 * @brief      Function to make both motor to move forward.
 */
void forward (void) //both wheels forward
{
  	motors_dir_port_reg &=  ~( (1 << motors_RB_pin) | (1 << motors_LB_pin) );	// Make LB and RB LOW
	motors_dir_port_reg |= (1 << motors_RF_pin) | (1 << motors_LF_pin) ;		// Make LF and RF HIGH
}

/**
 * @brief      Function to make both motor to move backward.
 */
void back (void) //both wheels backward
{
  	motors_dir_port_reg &=  ~( (1 << motors_RF_pin) | (1 << motors_LF_pin) );	// Make LF and RF LOW
	motors_dir_port_reg |= ((1 << motors_RB_pin) | (1 << motors_LB_pin)) ;		// Make LB and RB HIGH
}

/**
 * @brief      Function to make both motor to rotate left.
 */
void left (void) //Left wheel backward, Right wheel forward
{
  	motors_dir_port_reg &=  ~( (1 << motors_RB_pin) | (1 << motors_LF_pin) );	// Make LF and RB LOW
	motors_dir_port_reg |= (1 << motors_RF_pin) | (1 << motors_LB_pin) ;		// Make LB and RF HIGH
}

/**
 * @brief      Function to make both motor to rotate right.
 */
void right (void) //Left wheel forward, Right wheel backward
{
  	motors_dir_port_reg &=  ~( (1 << motors_LB_pin) | (1 << motors_RF_pin) );	// Make LB and RF LOW
	motors_dir_port_reg |= (1 << motors_LF_pin) | (1 << motors_RB_pin) ;		// Make LF and RB HIGH
}

/**
 * @brief      Function to make both motor to rotate soft left.
 */
void soft_left (void) //Left wheel stationary, Right wheel forward
{
	motors_dir_port_reg &=  ~( (1 << motors_LB_pin) | (1 << motors_RF_pin) | (1 << motors_LF_pin));	// Make LF, LB and RF LOW
	motors_dir_port_reg |= (1 << motors_RF_pin) ;	// Make RF HIGH
}

/**
 * @brief      Function to make both motor to rotate soft right.
 */
void soft_right (void) //Left wheel forward, Right wheel is stationary
{
 	motors_dir_port_reg &=  ~( (1 << motors_LB_pin) | (1 << motors_RF_pin) | (1 << motors_RB_pin));	// Make LB, RF and RB LOW
	motors_dir_port_reg |= (1 << motors_LF_pin) ;	// Make LF HIGH
}

/**
 * @brief      Function to make both motor to rotate backward left.
 */
void soft_left_2 (void) //Left wheel backward, right wheel stationary
{
 	motors_dir_port_reg &=  ~( (1 << motors_LF_pin) | (1 << motors_RF_pin) | (1 << motors_RB_pin));	// Make LF, RF and RB LOW
	motors_dir_port_reg |= (1 << motors_LB_pin) ;	// Make LB HIGH
}

/**
 * @brief      Function to make both motor to rotate backward right.
 */
void soft_right_2 (void) //Left wheel stationary, Right wheel backward
{
	motors_dir_port_reg &=  ~( (1 << motors_LF_pin) | (1 << motors_RF_pin) | (1 << motors_LB_pin));	// Make LF, RF and LB LOW
	motors_dir_port_reg |= (1 << motors_RB_pin) ;	// Make RB HIGH
}

/**
 * @brief      Function to make both motor to stop.
 */
void stop (void)
{
  	motors_dir_port_reg &=  ~( (1 << motors_LF_pin) | (1 << motors_RF_pin) | (1 << motors_LB_pin) | (1 << motors_RB_pin));	// Make LF, RF, LB and RB LOW
}


//---------------------------------- MAIN ----------------------------------------------------------------
/**
 * @brief      Main Function
 *
 * @details    First Initializes the Motor Driver pins.
 * 			   then call different functions to move the motor using different motions.
 */
int main(void)
{
	motors_pin_config();
	pwm_pin_config();
	while(1)
	{
	
		forward();						//both wheels forward
		_delay_ms(1000);

		stop();
		_delay_ms(500);
	
		back();							//both wheels backward
		_delay_ms(1000);

		stop();
		_delay_ms(500);
	
		left();							//Left wheel backward, Right wheel forward
		_delay_ms(1000);
	
		stop();
		_delay_ms(500);
	
		right();						//Left wheel forward, Right wheel backward
		_delay_ms(1000);

		stop();
		_delay_ms(500);

		soft_left();					//Left wheel stationary, Right wheel forward
		_delay_ms(1000);
	
		stop();
		_delay_ms(500);

		soft_right();					//Left wheel forward, Right wheel is stationary
		_delay_ms(1000);

		stop();
		_delay_ms(500);

		soft_left_2();					//Left wheel backward, right wheel stationary
		_delay_ms(1000);

		stop();
		_delay_ms(500);

		soft_right_2();					//Left wheel stationary, Right wheel backward
		_delay_ms(1000);

		stop();
		_delay_ms(1000);
	}
}
//---------------------------------- END ------------------------------------------------------------------
