 /**
	@author Moin and Elvis
	
	
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

/*Frequencies*/

#define A 18	
#define B 16	
#define C 15	
#define E 24	
#define G 20	
#define G1 10	
#define END 1 

/* Durations */

#define d1 2685	
#define d2 732	
#define d3 1709	
#define d4 5615	
#define d5 3662	
#define d6 7812	


/**
	@brief Init the microcontroller
*/
void init(void){

	 // Example set data direction PC1 to output
	//DDRC |=  (1 << DDC1);		// PC1 output
	DDRB |= (1 << DDB0); 	// PB0 is the output
	
	TCCR1B |= (1 << CS12); //1, 2 and 3
	TCCR1B |= (1 << CS10); //Task 2.A
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
	
	uint8_t i = 0;
	uint8_t uchNote[] = {G, A, G, E, G, A, G, E, G1, G1, B, C, C, G, END};
	uint16_t dur[] ={d1,d2,d3,d4,d1,d2,d3,d4,d5,d3,d4,d5,d3,d4,d6};
	
	 
	
	//	bonus Part
	
		while(uchNote[i] != END){
			
			TCNT2 = 0;
			TCNT1 = 0;
			
			while(TCNT1<=dur[i]){
				
				if(TCNT2>= uchNote[i]){
					
					PORTB ^= (1<<PB0);
					TCNT2 = 0;
				
				}
			
			}
					i++;
		}
	
	return 0;
}


/*end ******************************/