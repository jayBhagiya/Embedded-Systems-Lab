
#ifndef PIN_COFIG_H_
#define PIN_COFIG_H_


#include <avr/io.h>											// Standard AVR IO Library
#include <avr/interrupt.h>									// Standard AVR Interrupt Library

#if defined(__AVR_ATmega2560__)

	#define		F_CPU							14745600
	
	//---------------------------------- INPUT / OUTPUT PERIPHERALS -----------------------------------------------------
	
	// LCD definitions
	#define		lcd_data_ddr_reg				DDRC
	#define		lcd_control_ddr_reg				DDRC

	#define		lcd_data_port_reg				PORTC
	#define		lcd_control_port_reg			PORTC

	#define		RS_pin							PC0			// 0
	#define		RW_pin							PC1			// 1
	#define		EN_pin							PC2			// 2

	#define		DB7_pin							PC7			// 7
	#define		DB6_pin							PC6			// 6
	#define		DB5_pin							PC5			// 5
	#define		DB4_pin							PC4			// 4

	// LM35 sensor definitions
	#define		adc_sensor_ddr_reg				DDRF
	#define		adc_sensor_port_reg				PORTF
	#define		ldr_sensor_pin					PF1
	#define		ldr_sensor_channel				1
	#define		pot_sensor_pin					PF2
	#define		pot_sensor_channel				2
	
	
	// Bits of ADCSRA register ( ADC Control and Status Register A )
	#define		ADCSRA_reg						ADCSRA
	#define		ADEN_bit						ADEN		// 7	( ADC Enable bit )
	#define		ADSC_bit						ADSC		// 6	( ADC Start Conversion bit )
	#define		ADATE_bit						ADATE		// 5	( ADC Auto Trigger Enable bit )
	#define		ADIF_bit						ADIF		// 4	( ADC Interrupt Flag bit )
	#define		ADIE_bit						ADIE		// 3	( ADC Interrupt Enable bit )
	#define		ADPS2_bit						ADPS2		// 2	( ADC Pre-scalar bit 2 )
	#define		ADPS1_bit						ADPS1		// 1	( ADC Pre-scalar bit 1 )
	#define		ADPS0_bit						ADPS0		// 0	( ADC Pre-scalar bit 0 )
	
	// Bits of ADCSRB register ( ADC Control and Status Register B )
	#define		ADCSRB_reg						ADCSRB
	#define		ACME_bit						ACME		// 6	( Analog Comparator Multiplexer Enable bit )
	#define		MUX5_bit						MUX5		// 3	( ADC Channel Selection bit 5 )
	#define		ADTS2_bit						ADTS2		// 2	( ADC Auto Trigger Source bit 2 )
	#define		ADTS1_bit						ADTS1		// 1	( ADC Auto Trigger Source bit 1 )
	#define		ADTS0_bit						ADTS0		// 0	( ADC Auto Trigger Source bit 0 )
	
	// Bits of ADMUX register ( ADC Multiplexer Selection Register )
	#define		ADMUX_reg						ADMUX
	#define		REFS1_bit						REFS1		// 7	( Reference Selection bit 1 )
	#define		REFS0_bit						REFS0		// 6	( Reference Selection bit 0 )
	#define		ADLAR_bit						ADLAR		// 5	( ADC Left Result bit )
	#define		MUX4_bit						MUX4		// 4	( ADC Channel Selection bit 4 )
	#define		MUX3_bit						MUX3		// 3	( ADC Channel Selection bit 3 )
	#define		MUX2_bit						MUX2		// 2	( ADC Channel Selection bit 2 )
	#define		MUX1_bit						MUX1		// 1	( ADC Channel Selection bit 1 )
	#define		MUX0_bit						MUX0		// 0	( ADC Channel Selection bit 0 )
	
	// Bits of ACSR register ( Analog Comparator Control and Status Register )
	#define		ACSR_reg						ACSR
	#define		ACD_bit							ACD			// 7	( Analog Comparator Disable bit )
	
	// ADC Data registers
	#define		ADCH_reg						ADCH		// ADC High Byte Data register
	#define		ADCL_reg						ADCL		// ADC Low Byte Data register
	
	#define		BAUD_RATE						9600		// Baud rate setting
	
#endif


#endif /* PIN_COFIG_H_ */