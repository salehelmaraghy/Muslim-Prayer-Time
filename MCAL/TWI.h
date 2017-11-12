/*
 * TWI.h
 *
 *  Created on: Oct 13, 2017
 *      Author: SALEH
 */

#ifndef TWI_H_
#define TWI_H_
#include<avr/io.h>
#include<util/delay.h>
#define TWI_SPEED 100
#define MASTER 1
#define SLAVE 2
#define read 2
#define write 1

void TWI_init(void);

void TWI_address(unsigned char address,unsigned char mode);

void TWI_start(void);

void TWI_send_DeviceAddress_Write(unsigned char address);
void TWI_send_DeviceAddress_Read(unsigned char address);

void TWI_send_data(unsigned char Data,unsigned char mode);

unsigned char  TWI_recieve_data_ACK(unsigned char mode);
unsigned char  TWI_recieve_data_NACK(unsigned char mode);

void TWI_stop(void);



#endif /* TWI_H_ */
