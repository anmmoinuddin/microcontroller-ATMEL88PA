/**
	@author Thomas Grunenberg
	@version 0.1
	@file uart.h
	@brief Simple Uart communication
*/

#ifndef UART_H
#define UART_H


void uart_init(void);

void uart_send(uint8_t out);
uint8_t uart_receive(void);


#endif
