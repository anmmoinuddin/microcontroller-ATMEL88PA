/**
	@author Thomas Grunenberg
	@version 0.1
	@file uart.c
	@brief Simple Uart communication
*/
//#define F_CPU 16000000UL
#define F_CPU 8000000UL

#define BAUD 38400UL


/******************************************************************************/
/* INCLUDED FILES                                                             */
/******************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"
/******************************************************************************/

// Calculate value
#define UBRR_VAL ((F_CPU+BAUD*8)/(BAUD*16)-1) // round
#define BAUD_REAL (F_CPU/(16*(UBRR_VAL+1))) // real baudrate
#define BAUD_ERROR ((BAUD_REAL*1000)/BAUD) // 1000 is no aberration
#if ((BAUD_ERROR<990) || (BAUD_ERROR>1010))
	#error The aberration is to big.
#endif

/******************************************************************************/
/* Global Memory                                                              */
/******************************************************************************/

volatile uint8_t buffer;



/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/**
	@brief Init the PORTx and DDRx register for the I/O setup
*/
void uart_init(void){

	DDRD &= ~(1 << DDD0);		// PD0 as Input
	PORTD &= ~( 1 << PD0);		// NO Pullup for PD0
	DDRD |= (1 << DDD1);		// PD1 as Output
	PORTD &= ~( 1 << PD1);
	
	// Clear buffer
	buffer = 0;
		
	// Set speed
	UBRR0H = UBRR_VAL >> 8;
	UBRR0L = UBRR_VAL & 0xFF;

	UCSR0B |= (1<<TXEN0) | (1<<RXEN0) |(1 << RXCIE0);  // enable UART, TX,RX and INT
	UCSR0C = (1 << UCSZ01)|(1 << UCSZ00); // Asynchron 8N1


}
/******************************************************************************/

void uart_send(uint8_t out){
	
	// Wait for free output buffer
	while (!(UCSR0A & (1<<UDRE0))) 
			;
 
	// Send value
    UDR0 = out;
}
/******************************************************************************/

uint8_t uart_receive(void){
	uint8_t sreg = SREG;
	uint8_t out;
	cli();
	
	out = buffer;
	
	SREG = sreg;
	
	return out;
}
/******************************************************************************/


ISR(USART_RX_vect){
	buffer = UDR0;
}
/******************************************************************************/
