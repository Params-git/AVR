/*
 * USART_Receiver.c
 *
 * Created: 4/26/2021 12:51:27 PM
 * Author : Paramjeet singh
 */ 

#define F_CPU 8000000UL

#define FOSC 8000000// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD

#include <inttypes.h>
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>

char str[100];


////////////////////////////////////USART_Start//////////////////////////////////


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

void WriteData(char data) //this function write only one byte
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

//////////////////////////////////////////////USART_End///////////////////////////////////////////


int main(void)
{
	DDRB = 0xFF;
	USART_Init(51); //we use 8 MHz clock and 9600 baud and our ubrr is 51
	
	while(1)
	{
	char val = ReadData();
	ReadStringData(str);
	
	if(val == 3)
	{
		PORTB |= (1<<PB0);
		_delay_ms(100);
		PORTB &= ~(1<<PB0);
		_delay_ms(100);
		val = 0;
	}
	else
	{
		PORTB &= ~(1<<PB0);
	}
	}
}

