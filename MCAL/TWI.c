/*
 * TWI_init.c
 *
 *  Created on: Oct 13, 2017
 *      Author: SALEH
 */
#include "TWI.h"


/*****************************************************/
/*I2c initialization*/
void TWI_init(void)
{
#if TWI_SPEED == 100
	TWBR=32;   // to set the speed 100kb/s  TWBR=32;

#elif TWI_SPEED == 400
	TWBR=2;   // to set the speed 400kb/s  TWBR=2;
#endif

	TWSR=0;   // TWPS=0; //PreScaler 1:1
	TWCR=(1<<TWEN)|(1<<TWEA); // enable the TWI peripheral
}

/*****************************************************/
/*Device Address*/
void TWI_address(unsigned char address,unsigned char mode)
{
	TWAR=((address<<1)&(0xfe)); //disable General call
	switch (mode)
	{
	case read: //read from me //SLA+write received to replay with ACK
		TWCR=(1<<TWEN)|(1<<TWEA)|(1<<TWINT);
		while(!(TWCR&(1<<TWINT)));
		while((TWSR&0xf8)!=0x60)
		{
			TWCR=(1<<TWEN)|(1<<TWEA)|(1<<TWINT);
			while(!(TWCR&(1<<TWINT)));
		}
		break;
	case write: //I will write to the master //SLA+read received
		TWCR=(1<<TWEN)|(1<<TWEA)|(1<<TWINT);
		while(!(TWCR&(1<<TWINT)));
		while((TWSR&0xf8)!=0xA8)
		{
			TWCR=(1<<TWEN)|(1<<TWEA)|(1<<TWINT);
			while(!(TWCR&(1<<TWINT)));
		}
		break;
	default:
		break;

	}
}

/*****************************************************/
/*Sending a start bit for starting the comm.*/
void TWI_start(void)
{
	TWCR =(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);

	/*Status Register checking for start or repeated start*/
	while((!(TWCR & (1<<TWINT)))&&( (((TWSR&0xf8)!=0x08))||(((TWSR&0xf8)!=0x10)))); //wait for TWSR to be sure its start or repeated start
	{

	}
}

/*****************************************************/
/*Sending the Address*/
void TWI_send_DeviceAddress_Read(unsigned char address)
{
	TWDR=((address<<1)|(0x01));//Address+ReadBit
	TWCR=(1<<TWEN)|(1<<TWINT);
		while(!(TWCR & (1<<TWINT)));
		while((((TWSR&0xf8)!=0x40))) //send the address again if its not send.
		{
			TWDR=((address<<1)|(0x01));//Address+ReadBit
			TWCR=(1<<TWEN)|(1<<TWINT);
			while(!(TWCR & (1<<TWINT)));

		}
}

/*****************************************************/
void TWI_send_DeviceAddress_Write(unsigned char address)
{
	TWDR=((address<<1)&(0xfe));//Address+WriteBit
	TWCR=(1<<TWEN)|(1<<TWINT);
	while(!(TWCR & (1<<TWINT)));
	while((TWSR&0xf8)!=0x18) //if the slave didn't replay by ACK send the address again
	{
		TWDR=((address<<1)&(0xfe));//Address+WriteBit
		TWCR=(1<<TWEN)|(1<<TWINT);
	}
}

/*****************************************************/
/*Sending a byte of data*/
void TWI_send_data(unsigned char Data,unsigned char mode)
{
	TWDR=Data;
	TWCR=(1<<TWEN)|(1<<TWINT);
	while((!(TWCR & (1<<TWINT))));
	switch (mode)
	{
	case MASTER:
		while((((TWSR&0xf8)!=0x28))) //if master send data wait for the slave ACK replay
		{
			TWDR=Data;
			TWCR=(1<<TWEN)|(1<<TWINT);
			while((!(TWCR & (1<<TWINT))));

		}
		break;
	case SLAVE:
		while((((TWSR&0xf8)!=0xB8))) //if the slave send data wait for the master ACK replay
		{
			TWDR=Data;
			TWCR=(1<<TWEN)|(1<<TWINT);
			while((!(TWCR & (1<<TWINT))));

		}
		break;
	default:
		break;

	}

}

/*****************************************************/
/*Sending a stop bit*/
void TWI_stop(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);


}

/*****************************************************/
/*Receive with ACK*/
unsigned char  TWI_recieve_data_ACK(unsigned char mode)
{
	switch (mode)
	{
	case MASTER:
		TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);
		while(!(TWCR & (1<<TWINT)));
		while(((TWSR&0xf8)!=0x50))
			{
			TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);
			while(!(TWCR&(1<<TWINT)));
			}
		break;
	case SLAVE:
		TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);
		while(!(TWCR & (1<<TWINT)));
		while(((TWSR&0xf8)!=0x80))
			{
			TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);
			while(!(TWCR&(1<<TWINT)));
			}
		break;
	default:
		break;

	}
	return TWDR;
}
/*****************************************************/
/*Receive with NACK*/
unsigned char  TWI_recieve_data_NACK(unsigned char mode)
{
	switch (mode)
	{
	case MASTER:
		TWCR=(1<<TWEN)|(1<<TWINT);
		while(!(TWCR & (1<<TWINT)));
		while(((TWSR&0xf8)!=0x58))//)||((TWSR&0xf8)!=0x50)))
			{
			TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);
			while(!(TWCR&(1<<TWINT)));
			}
		break;
	case SLAVE:
		TWCR=(1<<TWEN)|(1<<TWINT);
		while(!(TWCR & (1<<TWINT)));
		while(((TWSR&0xf8)!=0x88))
			{
			TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);
			while(!(TWCR&(1<<TWINT)));
			}
		break;
	default:
		break;

	}
	return TWDR;
}

