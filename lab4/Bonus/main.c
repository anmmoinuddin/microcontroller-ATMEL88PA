/**
	@author Moin and Elvis
	@version 0.1
	@file main.c
	@brief ENTER discription
*/

/**
	@brief The CPU speed in Hz
*/
#define F_CPU 8000000UL

/******************************************************************************/
/* INCLUDED FILES                                                             */
/******************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
/******************************************************************************/


/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/**
	@brief Init the microcontroller
*/
void init(void){

	// Init key inputs
	DDRD &=  ~(1 << DDD2);		// PD2 input
	DDRD &=  ~(1 << DDD3);		// PD3 input
	PORTD |= (1 << PD2); // enable Pullup PD2
	PORTD |= (1 << PD3); // enable Pullup PD3

	// Analog input
	DDRC &= ~(1 << DDC0);		// PC0 as Input (ADC0)
	PORTC &= ~( 1 << PC0);		// Pullup PC0 off

	// Init LED outputs
	//TODO
	DDRB |= (1 << DDB0);	// PB0 output
	DDRB |= (1 << DDB1);	// PB1 output
	DDRB |= (1 << DDB2);	// PB2 output
	
	// Enable interrupts
	//TODO for Task 2.2
	EIMSK |= (1 << INT0) | (1 << INT1);
	EICRA |= (1 << ISC01) | (1 << ISC11); //External interrupt mask register
	
	// Timer1 for Task 2.3
//	TCCR1B |= (1 << CS12);	// Prescaler 256
	
	//Timer/Counter Interrupt Mask Register
	
	TIMSK1 |= (1 << TOIE1);	//Timer/Counter1 Overflow Interrupt Enable 

	// AREF = AVCC P*248
	ADMUX |= (1 << REFS0);
	
	// Prescaler 64 p*249-250
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1);
	
	// ADC Enable>free running>start conversion
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	
	//Enabling ADC interrupt
	ADCSRA |= (1 << ADIE);
		
}

//delay function
void mydelay(uint8_t time){
	
	while (time > 0){
		_delay_ms(250);
		time--;
	}
	
	return;
}
/******************************************************************************/




/**
	@brief Main function
	@return only a dummy to avoid a compiler warning, not used
*/
int main(void){
		
	// Init
	init();
	uint16_t adc_value;  

	// Global interrupt enable
	sei();

	// Loop forever
	while (1){
	adc_value = ADCW;		
		
		// Task 2b
		//Blink Yellow LED every 0.5 sec
		
		PORTB ^= (1 << PB1);
		mydelay(2);
				
	}
	
	return 0;
}
/******************************************************************************/

/**
	@brief INT0 interrupt
*/

ISR(INT0_vect){
	// Your code here
	PORTB ^= (1 << PB0);
	
}
/******************************************************************************/

/**
	@brief INT1 interrupt
*/

ISR(INT1_vect){
	// Your code here
PORTB |= (1 << PB0);uint16_t adc_values;  
	
}
/******************************************************************************/

/**
	@brief Timer1 overflow interrupt
*/
ISR(TIMER1_OVF_vect){
	// Your code here
	PORTB ^= (1 << PB2);
}
/******************************************************************************/

// Task 2.4 Bonus part
ISR(ADC_vect){
	TCCR1B = 0;
	
	if (ADCW < 256){
		TCCR1B |= (1 << CS10); // Prescaler 1
	}
	
	if (ADCW >= 256 && ADCW < 512){
		TCCR1B |= (1 << CS11);	// Prescaler 8
	}
	
	if (ADCW >= 512 && ADCW < 768){
		TCCR1B |= (1 << CS11) | (1 << CS10);	// Prescaler 64
	}
	
	if (ADCW >= 768){
		TCCR1B |= (1 << CS12);	// Prescaler 256*/
	}

}
