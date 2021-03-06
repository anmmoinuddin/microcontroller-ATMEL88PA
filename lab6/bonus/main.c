/**
	@author Thomas Grunenberg
	@version 0.1
	@file main.c
	@brief Main programm for external EEPROM usage
*/

/**
	@brief The CPU speed in Hz
*/
#define F_CPU 8000000UL

/******************************************************************************/
/* INCLUDED FILES                                                             */
/******************************************************************************/
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "i2c_master.h"
#include "init.h"
#include "lcd.h"
/******************************************************************************/



/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

uint8_t adr = 0xA0;
//volatile uint8_t pos = 0x00;
//volatile uint8_t pos2 = 0x00;

#define MAX_POS 4

/**
	@brief Show the poti and the memory value with the LCD
	@param poti poti value
	@param memory memory value
*/
void display_showvalues(uint16_t poti, uint16_t memory){
	char line1[17], line2[17];

	// Generate lines
	snprintf(line1, 16, "Poti: %i", poti);
	snprintf(line2, 16, "Memory: %i", memory);

	// Write lines to display
	lcd_clear();
	lcd_string(line1);
	lcd_setcursor(0,2);
	lcd_string(line2);	
}
/******************************************************************************/

/**
	@brief Show "Value saved" with the LCD
*/
void display_showsaved(void){
	uint8_t i;
	
	lcd_clear();
	lcd_string("Value saved");
	lcd_setcursor(0,2);
	lcd_string("to memory");	

	// Wait for button release
	_delay_ms(20);
	while ( ~PINB & (1 << PB0) )
		;
	
	// Wait 1.5 seconds
	for (i = 0; i < 6; i++)
		_delay_ms(250);

}
/******************************************************************************/

/**
	@brief Show "Value loaded" with the LCD
*/
void display_showload(void){
	uint8_t i;
		
	lcd_clear();
	lcd_string("Value load");
	lcd_setcursor(0,2);
	lcd_string("from memory");	

	// Wait for button release
	_delay_ms(20);
	while ( ~PINB & (1 << PB1) )
		;

	// Wait 1.5 seconds
	for (i = 0; i < 6; i++)
		_delay_ms(250);

}
/******************************************************************************/

/**
	@brief Load a value from the EEPROM
	@return loaded value
*/
uint16_t load_value(uint8_t pos){
	uint8_t highbyte, lowbyte;

	
	// TODO
	i2c_master_open_write(adr);
	i2c_master_write(pos*2);
	i2c_master_open_read(adr);
	highbyte = i2c_master_read_next();
	lowbyte = i2c_master_read_last();
	i2c_master_close();
	
	
	display_showload();
	
	return highbyte * 256 + lowbyte;
}
/******************************************************************************/

/**
	@brief Save a value to the EEPROM
	@param tosave value to save
*/
void save_value(uint16_t tosave, uint8_t pos){
	uint8_t highbyte, lowbyte;
	
	// TODO
	highbyte = tosave / 256;
	lowbyte = tosave % 256;

	i2c_master_open_write(adr);
	i2c_master_write(pos*2);
	i2c_master_write(highbyte);
	i2c_master_write(lowbyte);
	i2c_master_close();
	
	display_showsaved();
}
/******************************************************************************/


/**
	@brief Main function
	@return only a dummy to avoid a compiler warning, not used
*/
int main(void){
	uint16_t memory = 0, poti;

	init(); 	// Function to initialise I/Os
	lcd_init(); // Function to initialise LCD display
	i2c_master_init(1, 10); // Init TWI

	uint8_t posit=0;
	char lcdLine1[16], lcdLine2[16];
	uint8_t saveMenu = 1, loadMenu = 1;

	// Loop forever
	while (1){
		
		// Short delay
		_delay_ms(100);
		
		// Read ADC value
		// TODO
		poti = ADCW;
	
		// Refresh LCD display
		display_showvalues(poti, memory);

		// Check for Key1 (save value)
		if ( ~PINB & (1 << PB0) ){
			
			_delay_ms(50);
			while (~PINB & (1 << PB0));
			
			// menu loop
			while(saveMenu)
			{
				// button 2 to increment save slot position
				if (~PINB &(1 << PB1))
				{
					_delay_ms(50);
					while (~PINB & (1 << PB1));
					
					if (posit >= MAX_POS-1)
						posit = 0;
					else
						posit++;
				}
				
				// button 1 save slot confirmation
				if (~PINB &(1 << PB0))
				{
					_delay_ms(50);
					while (~PINB & (1 << PB0));
					saveMenu = 0;
				}
				
				snprintf(lcdLine1, 16, "Save:1 Change:2");
				snprintf(lcdLine2, 16, "Position: %d", posit);
				
				_delay_ms(100);
				// Write lines to display
				lcd_clear();
				lcd_string(lcdLine1);
				lcd_setcursor(0,2);
				lcd_string(lcdLine2);
			}
			
			save_value(poti, posit);
			saveMenu = 1;
		}

		// Check for Key2 (load menu)
		if ( ~PINB & (1 << PB1) )
		{
			_delay_ms(50);
			while (~PINB & (1 << PB1));
			
			// menu loop
			while(loadMenu)
			{
				// button 1 to increment load slot position
				if (~PINB &(1 << PB0))
				{
					_delay_ms(50);
					while (~PINB & (1 << PB0));
					
					if (posit >= MAX_POS-1)
						posit = 0;
					else
						posit++;
				}
				
				// button 2 load slot confirmation
				if (~PINB &(1 << PB1))
				{
					_delay_ms(50);
					while (~PINB & (1 << PB1));
					loadMenu = 0;
				}
				
				snprintf(lcdLine1, 16, "Change:1 Load:2");
				snprintf(lcdLine2, 16, "Load Pos: %d", posit);
				
				_delay_ms(100);
				// Write lines to display
				lcd_clear();
				lcd_string(lcdLine1);
				lcd_setcursor(0,2);
				lcd_string(lcdLine2);
			}
			
			memory = load_value(posit);
			loadMenu = 1;
		}	
	}

	return 0;
}
/******************************************************************************/
