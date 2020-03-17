/**
	@author Moin n Elvis
	@version 0.1
	@file main.c
	@brief ENTER discription
*/

/**
	@brief The CPU speed in Hz
*/

/******************************************************************************/
/* INCLUDED FILES                                                             */
/******************************************************************************/
#include <avr/io.h>
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

	// Init LED outputs
	//TODO
	DDRB |= (1 << DDB0);	// PB0 output
}
/******************************************************************************/




/**
	@brief Main function
	@return only a dummy to avoid a compiler warning, not used
*/
int main(void){
		
	// Init
	init();

	// Loop forever
	while (1){
		
		//Task 2.1
		//Enable and disable Red LED
		
		//(~PIND & (1<<PD2))=bit_is_clear(PIND, PD2)
		
		if (~PIND & (1<<PD2)){
			PORTB |= (1 << PB0);
		}
		else if  (~PIND & (1<<PD3)){
			PORTB &= ~(1 << PB0);
		}
		
}
	
	return 0;

}