/*
 * LCD.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: SALEH
 */
#include "LCD.h"

#ifdef FOURBIT //if four bit mode

//this function is to enable the LCD to send command or data
void ENABLE_LCD()
{
	SETBIT(LCD_CONTROL_PORT,EN);
	_delay_us(5);
	CLEARBIT(LCD_CONTROL_PORT,EN);
}
//this function is to send commands to the LCD
void LCD_COMMAND(unsigned char cmd){

	unsigned char temp=0;
	CLEARBIT(LCD_CONTROL_PORT,RS);
	temp=cmd;
	temp&=0xF0;//send the first four bits first
	LCD_DATA_PORT&=0x0F;
	LCD_DATA_PORT|=temp;
	ENABLE_LCD(); //send the command
	if(cmd==0x01 || cmd==0x02) //it differs in the delay (trial and error from the LCD data sheet)
	{ _delay_ms(2);}
	else { _delay_us(100);}
	temp=cmd;
	temp&=0x0f; //then send the next four bits
	temp=temp<<4;
	LCD_DATA_PORT&=0x0F;
	LCD_DATA_PORT|=temp;
	ENABLE_LCD();
	if(cmd==0x01 || cmd==0x02)
	{ _delay_ms(2);}
	else { _delay_us(100);}
}

void LCD_INIT()
{
	SETBIT(LCD_CONTROL_DIR,EN);
	SETBIT(LCD_CONTROL_DIR,RS);
	_delay_ms(50);

	LCD_DATA_DIR|=0Xf0; //it have to be first because cmd fn uses this pins
	LCD_COMMAND(0x01);
	LCD_COMMAND(0x33);
	LCD_COMMAND(0x32);
	LCD_COMMAND(0x28);//4bit mode
	LCD_COMMAND(0x0C);//cursor off
}

void LCD_GOTO(unsigned char row,unsigned char col)
{
	//this function is to get the row and colomn you want to write the data at.
	switch(row)
	{
	case 1:
		LCD_COMMAND(0x80+(col-1));
		break;
	case 2:
		LCD_COMMAND(0xC0+(col-1));
		break;
	default:
		break;
	}
}
void LCD_SEND_CHAR(unsigned char data)
{
	unsigned char temp=0;
		SETBIT(LCD_CONTROL_PORT,RS);
		temp=data;
		temp&=0xF0; //first sent the first four bytes MSB first
		LCD_DATA_PORT&=0x0F;
		LCD_DATA_PORT|=temp;
		ENABLE_LCD();
		_delay_us(100);
		temp=data;
		temp&=0x0f;
		temp=temp<<4;//sent the second four bytes
		LCD_DATA_PORT&=0x0F;
		LCD_DATA_PORT|=temp;
		ENABLE_LCD();
		_delay_us(100);
		LCD_COMMAND(0x06); //move the cursor after to write the next char.
}

void LCD_SEND_STR(unsigned char* data)
{
	//this function is to sent a whole array of char (string)
	int i=0;
	while(*(data+i)!='\0')
	{
		LCD_SEND_CHAR(*(data+i));
		i++;
	}
}
void LCD_SEND_INT(unsigned int number)
{
	//to sent to the LCD an integer as the LCD only display ASKI values
	unsigned char size,a,b,c,d;
	if(number>=0 && number<=9)
	{
		size=1;
		a=number;a+=48; //check integer to decimal ASKII table
		LCD_SEND_CHAR(a);
	}
	else if(number>=10 && number<=99)
	{
		size=2;
		a=number%10;a+=48; //get last digit
		b=number/10;b+=48; //get first digit
		LCD_SEND_CHAR(b);
		LCD_SEND_CHAR(a);
	}
	else if(number>=100 && number<=999)
	{
		size=3;
		a=number%10;a+=48; //get each digit alone
		number=number/10;
		b=number%10;b+=48;
		c=number/10;c+=48;
		LCD_SEND_CHAR(c);
		LCD_SEND_CHAR(b);
		LCD_SEND_CHAR(a);

	}
	else if(number>=1000 && number<=9999)
	{
		size=4;
		a=number%10;a+=48;
		number=number/10;
		b=number%10;b+=48;
		number=number/10;
		c=number%10;c+=48;
		d=number/10;d+=48;
		LCD_SEND_CHAR(d); //get each digit alone
		LCD_SEND_CHAR(c);
		LCD_SEND_CHAR(b);
		LCD_SEND_CHAR(a);
	}
}

void CLEAR_LCD()
{
	//this function is to clear the LCD
	LCD_COMMAND(0x01);
	LCD_COMMAND(0x0E);
}
#endif
#ifdef EIGHTBIT
void ENABLE_LCD()
{
	SETBIT(LCD_CONTROL_PORT,EN);
	_delay_us(5);
	CLEARBIT(LCD_CONTROL_PORT,EN);
}

void LCD_COMMAND(unsigned char cmd){
	CLEARBIT(LCD_CONTROL_PORT,RS);
	LCD_DATA_PORT=cmd;
	ENABLE_LCD();
	if(cmd==0x01 || cmd==0x02)
	{ _delay_ms(2);}
	else { _delay_us(100);}
}

void LCD_INIT()
{
	SETBIT(LCD_CONTROL_DIR,EN);
	SETBIT(LCD_CONTROL_DIR,RS);
	LCD_DATA_DIR=0XFF;
	LCD_COMMAND(0x38);
	LCD_COMMAND(0x01);
	LCD_COMMAND(0x0E);
}

void LCD_GOTO(unsigned char row,unsigned char col)
{
	switch(row)
	{
	case 1:
		LCD_COMMAND(0x80+(col-1));
		break;
	case 2:
		LCD_COMMAND(0xC0+(col-1));
		break;
	default:
		break;
	}
}
void LCD_SEND_CHAR(unsigned char data)
{
	SETBIT(LCD_CONTROL_PORT,RS);
	LCD_DATA_PORT=data;
	ENABLE_LCD();
	_delay_us(100);
	LCD_COMMAND(0x06);
}

void LCD_SEND_STR(unsigned char* data)
{
	int i=0;
	while(*(data+i)!='\0')
	{
		LCD_SEND_CHAR(*(data+i));
		i++;
	}
}
void LCD_SEND_INT(unsigned int number)
{
	unsigned char size,a,b,c,d;
	if(number>=0 && number<=9)
	{
		size=1;
		a=number;a+=48;
		LCD_SEND_CHAR(a);
	}
	else if(number>=10 && number<=99)
	{
		size=2;
		a=number%10;a+=48;
		b=number/10;b+=48;
		LCD_SEND_CHAR(b);
		LCD_SEND_CHAR(a);
	}
	else if(number>=100 && number<=999)
	{
		size=3;
		a=number%10;a+=48;
		number=number/10;
		b=number%10;b+=48;
		c=number/10;c+=48;
		LCD_SEND_CHAR(c);
		LCD_SEND_CHAR(b);
		LCD_SEND_CHAR(a);

	}
	else if(number>=1000 && number<=9999)
	{
		size=4;
		a=number%10;a+=48;
		number=number/10;
		b=number%10;b+=48;
		number=number/10;
		c=number%10;c+=48;
		d=number/10;d+=48;
		LCD_SEND_CHAR(d);
		LCD_SEND_CHAR(c);
		LCD_SEND_CHAR(b);
		LCD_SEND_CHAR(a);
	}
}
void CLEAR_LCD()
{
	LCD_COMMAND(0x01);
	LCD_COMMAND(0x0E);
}
#endif

