#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
//#include <avr/interrupt.h>
//#include "serial.c"


//------------------------------MAIN------------------------------------
int main(void)
{	
	DDRB = 0xFF;
	
	while(1)
	{
		PORTB |= (1<<PB4);
		_delay_ms(500);
		PORTB &= ~(1<<PB4);
		_delay_ms(500);
//------------------------------------------
	}//end of while
}//end of main
