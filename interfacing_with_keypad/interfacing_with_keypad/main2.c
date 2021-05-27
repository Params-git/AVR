/*
 * glcd_ks0108.c
 *
 * Created: 4/20/2021 7:54:32 PM
 * Author : Paramjeet singh
 */ 

#define F_CPU 8000000UL

#define FOSC 8000000// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD

#include "ks0108.h"
#include "arial_bold_14.h"
#include "glcd.h"
#include "graph.h"
#include "SC.h"
#include "font12x16.h"
#include "corsiva_12.h"

#define prt 	PORTC
#define ddr		DDRC
#define pin		PINC
							
unsigned char key[4][4] = {'7','/','9','8',
	                       '4','*','6','5',
	                       '1','-','3','2',
                            ' ','+','=','0'};							

unsigned char col, row;
unsigned char z;

char keyfind()
{
	prt = 0xFF;
	ddr = 0xF0;
	while(1)
	{
		prt = 0xef;
		col = (pin & 0x0f);
		if(col != 0x0f)
		{
			row = 0;
			goto xx;
		}
		prt = 0xdf;
		col = (pin & 0x0f);
		if(col != 0x0f)
		{
			row = 1;
			goto xx;
		}
		prt = 0xbf;
		col = (pin & 0x0f);
		if(col != 0x0f)
		{
			row = 2;
			goto xx;
		}
		prt = 0x7f;
		col = (pin & 0x0f);
		if(col != 0x0f)
		{
			row = 3;
			goto xx;
		}
		xx:
		if(col == 0x0e)
		{
			z = (key[0][row]);
			return z;
		}
		else if(col == 0x0d)
		{
			z = (key[1][row]);
			return z;
		}
		else if(col == 0x0b)
		{
			z = (key[2][row]);
			return z;
		}
		else if(col == 0x07)
		{
			z = (key[3][row]);
			return z;
		}
	}
}

void ledON(int num)
{
	for(int i=0; i<num; i++)
	{
		PORTB |= (1<<PB0);
		_delay_ms(50);
		PORTB &= ~(1<<PB0);
		_delay_ms(50);
	}
}

int main(void)
{
	/*DDRB = 0xFF;*/
	
	USART_Init(51);
	
	ks0108Init(0);
	glcd_on();
	glcd_clear();
	
	int a = 4;
	
	while(1)
	{
// 	char val = ReadData();
// 	if(val == 3)
// 	{
// 		PORTB |= (1<<PB0);
// 		_delay_ms(100);
// 		PORTB &= ~(1<<PB0);
// 		_delay_ms(100);
// 		val = 0;
// 	}
    ks0108SelectFont(font12x16,ks0108ReadFontData,BLACK);
    ks0108GotoXY(a,14);
	
    char ch = keyfind();
	if(ch == '1')
	{
		ks0108Puts("1");
		a += 4;
	}
	else if(ch == '2')
	{
		ks0108Puts("2");
		a += 6;
	}
	else if(ch == '3')
	{
		ks0108Puts("3");
		a += 6;
	}
	else if(ch == '4')
	{
		ks0108Puts("4");
		a += 6;
	}
	else if(ch == '5')
	{
		ks0108Puts("5");
		a += 6;
	}
	else if(ch == '6')
	{
		ks0108Puts("6");
		a += 6;
	}
	else if(ch == '7')
	{
		ks0108Puts("7");
		a += 6;
	}
	else if(ch == '8')
	{
		ks0108Puts("8");
		a += 6;
	}
	else if(ch == '9')
	{
		ks0108Puts("9");
		a += 6;
	}
	else if(ch == '0')
	{
		ks0108Puts("0");
		a += 6;
	}
	
}
}

