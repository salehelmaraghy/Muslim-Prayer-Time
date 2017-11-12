/*
 * keypad.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: SALEH
 */
#include "KEYPAD.h"
//note:the keypad I have used is 3*3 keypad so it don't have zero so I added it at a single pin
//If you are using another keypad please modify the code but keep the same functions name

void keypad_init()
{
	//this function is to initiate the keypad port
	KEYPAD_DIR|=0xE0;
	KEYPAD_DIR&=~0x1C;

	CLEARBIT(KEYPAD_DIR,extern_zero); //for the external bit
	SETBIT(KEYPAD_PORT,extern_zero); //for the external bit
	SETBIT(KEYPAD_PORT,row_one);
	SETBIT(KEYPAD_PORT,row_two);
	SETBIT(KEYPAD_PORT,row_three); //pull up resistor
	SETBIT(KEYPAD_PORT,colomn_three);
	SETBIT(KEYPAD_PORT,colomn_three);
	SETBIT(KEYPAD_PORT,colomn_three);

}

unsigned char scan()
{
	//this function is to scan the number.
	int r,c,flag;
	signed int numb=-1;
	flag=0;

	for(c=7;c>=5;c--)
	{	//this loop is to pass zeros on the colomns
		if(CHECKBITZ(KEYPAD_PIN,extern_zero))
		{
			numb=0;
			break;
		}
		if(flag==1) //then a button is pressed
		{
			flag=0;
			break;
		}
		if(c==7)
		{
			_delay_ms(5);
		CLEARBIT(KEYPAD_PORT,c);
		SETBIT(KEYPAD_PORT,(c-1));
		SETBIT(KEYPAD_PORT,(c-2));
		_delay_ms(5);
		}
		else if(c==6)
		{
		_delay_ms(5);
		CLEARBIT(KEYPAD_PORT,c);
		SETBIT(KEYPAD_PORT,(c-1));
		SETBIT(KEYPAD_PORT,(c+1));
		_delay_ms(5);
		}
		else if(c==5)
		{
			_delay_ms(5);
		CLEARBIT(KEYPAD_PORT,c);
		SETBIT(KEYPAD_PORT,(c+1));
		SETBIT(KEYPAD_PORT,(c+2));
		_delay_ms(5);
		}
		for(r=4;r>=2;r--)
		{ //this loop is to scan if a key is pressed
			if(CHECKBITZ(KEYPAD_PIN,r))
			{
				numb=estimate_key(r,c);
				flag=1;
				break;

			}
		}
	}
	return numb;
}
unsigned char estimate_key(unsigned char row,unsigned char col)
{
	//this function is to estimate the pressed button is which number
	signed  char numb=-1;
	switch(row)
	{
	case row_one:
		switch(col)
		{
		case colomn_one:
			numb=1;
			break;
		case colomn_two:
			numb=2;
			break;
		case colomn_three:
			numb=3;
			break;
		default:
			break;
		}
		break;
	case row_two:
		switch(col)
		{
		case colomn_one:
			numb=4;
			break;
		case colomn_two:
			numb=5;
			break;
		case colomn_three:
			numb=6;
			break;
		default:
			break;
		}
		break;
	case row_three:
		switch(col)
		{
		case colomn_one:
			numb=7;
			break;
		case colomn_two:
			numb=8;
			break;
		case colomn_three:
			numb=9;
			break;
		default:
			numb=-1;
			break;
		}
		break;
	default:
			break;
	}
	return numb;
}
