/*
 * USART_Trans.c
 *
 * Created: 4/26/2021 12:44:30 PM
 * Author : Paramjeet singh
 */ 

#define F_CPU 8000000UL

#define FOSC 8000000// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

#include <avr/io.h>
#include <util/delay.h>////including delay library
#include <avr/interrupt.h>////including interrupt library
#include <stdio.h>
#include <string.h>

char a;

////////////////////////USART_Start/////////////////////////////////

void USART_Init( unsigned int ubrr)//initialize usart with ubrr value
{
	/* Set baud rate */
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN);
	/* Set frame format: 8data, 2stop bit */
	UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
}

char ReadData( void )// this function read only one byte
{
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)) )
	;
	/* Get and return received data from buffer */
	return UDR;
}


void WriteData(char data)//this function write only one byte
{
	//Wait For Transmitter to become ready
	while(!(UCSRA & (1<<UDRE)));

	//Now write
	UDR=data;
}
void ReadStringData(char *str){
	
	char c;
	do{
		c=ReadData();
		*str=c;
		str++;
	}
	while(c!='\0');

	return;
}

void WriteStringData(char *strData)
{
	while(*strData!='\0')
	{
		WriteData(*strData);
		strData++;
	}
	WriteData('\0');
	return;
}

//////////////////////////USART_end//////////////////////

int main(void)
{
	USART_Init(51);  //we use 8 MHz clock and 9600 baud and our ubrr is 51
	a = 3;
	
	while(1)
	{
		WriteData(a);
		_delay_ms(5000);
		WriteStringData("hello world");
		_delay_ms(3000);
	}
}

