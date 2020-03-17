// author: moin & Elvis

#include <avr/io.h>
#include "init.h"
#include "led.h"

int main(void){


	
			init();				// call the function from int.c 

	while(1){
		if (!((~PIND & (1 << PD2)) && (~PIND & (1 << PD3))))

			ledRed(1);
		else

			ledRed(0);
		if ((~PIND & (1 << PD2)) || (~PIND & (1 << PD3)))

			ledYellow(1);
		else

			ledYellow(0);
		if (!(~PIND & (1 << PD2)) != !(~PIND & (1 << PD3)))

			ledGreen(1);
		else

			ledGreen(0);
	}
	
	return 0;
}
