#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include <string.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "serial.c"
#include "rotary.c"
#include "hc12.c"

//------------------------------MAIN------------------------------------
int main(void)
{
	unsigned char Input[16];
	unsigned char String[16];
	short temperature = 0;
	unsigned char tempKomma = 0;
	unsigned char sign = 0;
	
	DDRD = 0x02;			//Schalterport
	DDRB = 0xff;			//LEDsport
	DDRC = 0xff;			//LCDdaten
	DDRA = 0xf0;			//LCDctrl & ADC

	lcd_init(LCD_DISP_ON);
	USART_Init(103);
	
	HC_init(96,1,1);

	USART_Flush();
	
	while(1)
	{
		if(USART_check_RX())
		{
			USART_Receive_STRING(Input);
			temperature = atoi(Input);

			if(temperature >= 0)
			{
				tempKomma = temperature % 10;
				temperature /= 10;
				sign = '+';
			}else
			{
				temperature *= -1;
				tempKomma = temperature % 10;
				temperature /=  10;
				sign = '-';
			}
			sprintf(String, "%c%03d,%01dC", sign, temperature, tempKomma);
			
			lcd_gotoxy(0, 0);
			lcd_puts(String);
			
			//Empfangstest
			PORTB |= (1<<PB0);
			_delay_ms(10);
			PORTB &= ~(1<<PB0);

		}
//------------------------------------------
	}//end of while
}//end of main
