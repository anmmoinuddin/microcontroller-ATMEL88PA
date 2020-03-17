 
/**
	@author Thomas Grunenberg
	@version 0.1
	@file one.c
	@brief Seven segment display
	Bonus part
*/

#define F_CPU 8000000UL

/******************************************************************************/
/* INCLUDED FILES                                                             */
/******************************************************************************/
#include <avr/io.h>
#include <util/delay.h>
/******************************************************************************/


/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
/**
	@brief Init input and output
*/
void init(void){
	
	// Input
	DDRD &= (1 << DDD2);
	DDRD &= (1 << DDD3);
	PORTD |= (1 << PD2);
	PORTD |= (1 << PD3);

	// Output
	DDRB |= (1 << DDB0);
	DDRB |= (1 << DDB1);
	DDRB |= (1 << DDB2);
	DDRB |= (1 << DDB3);
	DDRC |= (1 << DDC0);
	DDRC |= (1 << DDC1);
	DDRC |= (1 << DDC2);
	
	// ADC init------------------------------------------------------------
	DDRC &= ~(1 << DDC3);		// PC3 as Input (Poti)
	PORTC &= ~(1 << PC3);		// Pullup PC3 OFF
	//ADC Reference Voltage and Channel 3
	ADMUX |= (1 << REFS0) | (1 << MUX0) | (1 << MUX1);
	// ADCSRA
	ADCSRA = (1 << ADPS2)|(1 << ADPS1); // Set ADC Prescale to 64
	// Start conversion, Free running, Enalbe ADC
	ADCSRA |= (1 << ADSC) | (1 << ADATE) | (1 << ADEN);
}
/******************************************************************************/

void sevensegment(uint8_t value){
	static uint8_t last = 255;
	
	// stop here if no change
	if (value == last)
		return;
	
	last = value;
	

	// Disable all LEDs
	/*PORTB &= ~(1 << PB0);
	PORTB &= ~(1 << PB1);
	PORTB &= ~(1 << PB2);
	PORTB &= ~(1 << PB3);*/		
	//PORTC &= ~(1 << PC0);		
	//PORTC &= ~(1 << PC1);
//	PORTC &= ~(1 << PC2);

	// Enable LEDs for value
	switch(value){
	
		 case(1):
			PORTC &= ~(1 << PC2); // A
			PORTC |= (1 << PC1); // B
			PORTC |= (1 << PC0); // C
			PORTB &= ~(1 << PB0); // D
			PORTB &= ~(1 << PB1); // E
			PORTB &= ~(1 << PB2); // F
			PORTB &= ~(1 << PB3); // G
			
			break;
			
		case(2):
			PORTC |= (1 << PC2); // A
			PORTC |= (1 << PC1); // B
			PORTC &= ~(1 << PC0); // C
			PORTB |= (1 << PB0); // D
			PORTB |= (1 << PB1); // E
			PORTB &= ~(1 << PB2); // F
			PORTB |= (1 << PB3); // G
			
		break;

		case(3):
			PORTC |= (1 << PC2); // A
			PORTC |= (1 << PC1); // B
			PORTC |= (1 << PC0); // C
			PORTB |= (1 << PB0); // D
			PORTB &= ~(1 << PB1); // E
			PORTB &= ~(1 << PB2); // F
			PORTB |=  (1 << PB3); // G
			
		break;

		case(4):
			PORTC &= ~(1 << PC2); // A
			PORTC |= (1 << PC1); // B
			PORTC |= (1 << PC0); // C
			PORTB &= ~(1 << PB0); // D
			PORTB &= ~(1 << PB1); // E
			PORTB |= (1 << PB2); // F
			PORTB |= (1 << PB3); // G
			
		break;

		case(5):
			PORTC |= (1 << PC2); // A
			PORTC &= ~(1 << PC1); // B
			PORTC |= (1 << PC0); // C
			PORTB |= (1 << PB0); // D
			PORTB &= ~(1 << PB1); // E
			PORTB |= (1 << PB2); // F
			PORTB |= (1 << PB3); // G
			
		break;

		case(6):
			PORTC &= ~(1 << PC2); // A
			PORTC &= ~(1 << PC1); // B
			PORTC |= (1 << PC0); // C
			PORTB |= (1 << PB0); // D
			PORTB |= (1 << PB1); // E
			PORTB |= (1 << PB2); // F
			PORTB |= (1 << PB3); // G
			
		break;

		case(7):
			PORTC |= (1 << PC2); // A
			PORTC |= (1 << PC1); // B
			PORTC |= (1 << PC0); // C
			PORTB &= ~(1 << PB0); // D
			PORTB &= ~(1 << PB1); // E
			PORTB &= ~(1 << PB2); // F
			PORTB &= ~(1 << PB3); // G
			
		break;
			
		case(8):
			PORTC |= (1 << PC2); // A
			PORTC |= (1 << PC1); // B
			PORTC |= (1 << PC0); // C
			PORTB |= (1 << PB0); // D
			PORTB |= (1 << PB1); // E
			PORTB |= (1 << PB2); // F
			PORTB |= (1 << PB3); // G
			
		break;

		case(9):
			PORTC |= (1 << PC2); // A
			PORTC |= (1 << PC1); // B
			PORTC |= (1 << PC0); // C
			PORTB &= ~(1 << PB0); // D
			PORTB &= ~(1 << PB1); // E
			PORTB |= (1 << PB2); // F
			PORTB |= (1 << PB3); // G
			
		break;


		default:
			PORTC |= (1 << PC2); // A   pin 10
			PORTC |= (1 << PC1); // B   pin 9
			PORTC |= (1 << PC0); // C   pin 7
			PORTB |= (1 << PB0); // D   pin 5
			PORTB |= (1 << PB1); // E   pin 4 
			PORTB |= (1 << PB2); // F   pin 2
			PORTB &= ~(1 << PB3); // G    pin 1
			
		break;
	
			
	 
	
			
			
	}


}
/******************************************************************************/


/**
	@brief Main function
	@return only a dummy to avoid a compiler warning, not used
*/
int main(void){
	uint16_t value = 0;
	init(); 	// Function to initialise I/Os
	uint16_t adc_value;
	uint16_t voltage;
	
	// Loop forever
	while (1){
		sevensegment(value);
		
		adc_value = ADCW;
		voltage = adc_value * 5;
		voltage /= 1020;
		value = voltage;
		_delay_ms(50);
		
		
		
		

	}
	

	return 0;
}
/******************************************************************************/
