 /**
	@author Moin 
	
	
*/

// CPU clock
#define F_CPU 8000000UL

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

	// Example set data direction PC1 to output
 
	DDRB |= (1 << DDB0); 	// PB0 is the output
	
	TCCR1B |= (1 << CS12); //1, 2 and 3
	 
	TCCR2B |= (1 << CS22)|(1 << CS20); 
	TCCR1B |= (1 << CS12)|(1 << CS10); 
	
}
/******************************************************************************/


/**
	@brief Main function
	@return only a dummy to avoid a compiler warning, not used
*/
int main(void){
	
	// Init
	init();
	
	 
	 //Task 2
	while (1){
		
				
	
		if (TCNT1 >= 62499){
			PORTB ^= (1 << PB0);
			TCNT1 = 0;
		}
				
	}
	 
	
 
	
	return 0;
}


/*end ******************************/
