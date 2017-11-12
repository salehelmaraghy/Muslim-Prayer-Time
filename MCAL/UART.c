/*
 * UART.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: SALEH
 */
#include "UART.h"
void UART_INIT()
{
	SETBIT(UART_DIR,tx);
	CLEARBIT(UART_DIR,rx);

	//unsigned int temp=0;
	//temp=16*baudrate;
	//temp=osc_clk/temp;
	//temp=temp-1;

	UCSRC|=(1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0); //8bit mode
	UCSRB&=~(1<<UCSZ2);//8 bit mode
	UBRRL=51; //to make the baudrate 9600
}
void UART_SEND_BYTE(unsigned char data)
{
	UCSRB|=(1<<TXEN);
	UDR=data;
	while(!(UCSRA&(1<<UDRE))); //poll until data is send
}
unsigned char UART_RECEIVE_BYTE()
{
	unsigned char data=0;
	UCSRB|=(1<<RXEN);
	while(!(UCSRA&(1<<RXC)));
	data=UDR;
	return data;
}

void UART_SEND_STRING(unsigned char* str)
{
	int i=0;
	while(str[i]!='\0') //send the chars until the NULL is found
	{
		UART_SEND_BYTE(str[i]);
		i++;
	}
}
void UART_RECEIVE_STRING(unsigned char* str)
{
	int i=0;
	do
	{
		str[i]=UART_RECEIVE_BYTE();

	}while(str[i++]!='#');
	str[i]='\0';
}
void UART_SEND_BYTE_INT(unsigned char data)
{

	UCSRB|=(1<<TXEN)|(1<<UDRIE);
	SREG|=(1<<7);
	//while((UCSRA&(1<<UDRE)));
	UDR=data;
}

void UART_RECEIVE_BYTE_INT()
{
	//unsigned char data=0;
	UCSRB|=(1<<RXEN)|(1<<RXCIE);
	SREG|=(1<<7);
	while((UCSRA&(1<<RXC)));
}
void DISABLE_UART_INT()
{
	UCSRB&=~(1<<RXCIE);
}
