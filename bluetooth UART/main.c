/**
	@author Thomas Grunenberg
	@version 0.1
	@file main.c
	@brief Software for Lev. Magnet
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
#include "lcd.h"
#include "uart.h"

uint8_t a;
char str[16];


int main(void){

	uart_init();
	lcd_init();
	
	lcd_string("project .....");
	lcd_setcursor(0, 2);
	_delay_ms(1000);
	lcd_clear();
	
	for(;;){
		
		a = uart_receive();
		lcd_string(str);

		sprintf(str, "%i", a);
		

		//lcd_setcursor(0, 2);
		//uart_send('a');
		
	}


	return 0;
}
/******************************************************************************/

