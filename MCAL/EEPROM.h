/*
 * EEPROM.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: SALEH
 */

#ifndef EEPROM_H_
#define EEPROM_H_
#include <avr/io.h>
#include <stdint.h>
#include<stdlib.h>
#include "../service_layer/DIO.h"
//typedef union number num_1
unsigned char EEPROM_READ(unsigned int address);
void EEPROM_WRITE(unsigned int address,unsigned char data);
//unsigned int EEPROM_READ_int(unsigned int address);
//void EEPROM_WRITE_int(unsigned int address,unsigned int data);
float EEPROM_READ_float(unsigned int address);
void EEPROM_WRITE_float(unsigned int address,float data);
#endif /* EEPROM_H_ */
