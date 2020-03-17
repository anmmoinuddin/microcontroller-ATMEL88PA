#include <avr/io.h>  
#include "led.h"  

void ledRed(uint8_t value)   
{ 
	if (value == 0)      
		PORTB &= ~(1 << PB1);   
	else  
		PORTB |= (1 << PB1);  
} 

void ledYellow(uint8_t value) 
{   
	if (value == 0)     
		PORTB &= ~(1 << PB2);    
	else                  
		PORTB |= (1 << PB2); 
} 
void ledGreen(uint8_t value) 
{   
	if (value == 0)       
		PORTB &= ~(1 << PB3);          
	else         
		PORTB |= (1 << PB3); 
}