/*
 * EEPROM.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: SALEH
 */
#include "EEPROM.h"

void EEPROM_WRITE(unsigned int address,unsigned char data)
{
	while(EECR&(1<<EEWE));
	EEDR=data;
	EEAR=address;
	EECR=(1<<EEMWE); //it have to start first then start writing
	EECR|=(1<<EEWE);
	//while(EECR&(1<<EEWE));
}

unsigned char EEPROM_READ(unsigned int address)
{
	while(EECR&(1<<EEWE));
	EEAR=address;
	EECR|=(1<<EERE);
	return EEDR;
}


void EEPROM_WRITE_float(unsigned int address,float data)
{
	//this function is to store float value to the EEPROM as it only saves bytes using pointer
	char* ptr=&data;
	EEPROM_WRITE(address,*ptr);
	EEPROM_WRITE(address+1,*(ptr+1));
	EEPROM_WRITE(address+2,*(ptr+2));
	EEPROM_WRITE(address+3,*(ptr+3));
	//it can also done by unions as described below
	/*union number
	{
		float x;
		char arr[4];
	}num;
	num.x=data;

	EEPROM_WRITE(address,num.arr[0]);
	EEPROM_WRITE(address+1,num.arr[1]);
	EEPROM_WRITE(address+2,num.arr[2]);
	EEPROM_WRITE(address+3,num.arr[3]);*/

}
float EEPROM_READ_float(unsigned int address)
{
	//this function is to get float number from the EEPROM using union.
	union number
	{
		float x;
		char arr[4];
	}num;

	num.arr[0]=EEPROM_READ(address);
	num.arr[1]=EEPROM_READ(address+1);
	num.arr[2]=EEPROM_READ(address+2);
	num.arr[3]=EEPROM_READ(address+3);
	return num.x;
}

/**************the next commented section is to read/write integers to the EEPROM***************************/
//void EEPROM_WRITE_int(unsigned int address,unsigned int data)
//{
//	//note its little endian
//	char* ptr=&data;
//	EEPROM_WRITE(address,*ptr);
//	EEPROM_WRITE(address+1,*(ptr+1));
//}
//unsigned int EEPROM_READ_int(unsigned int address)
//{
//	int data,final;
//	data=EEPROM_READ(address);
//	final&=0x0000;
//	final|=data;
//	data=EEPROM_READ(address+1);
//	final|=(data<<8);
//	return final;
//}

