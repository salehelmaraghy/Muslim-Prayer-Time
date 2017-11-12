/*
 * GPS.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: SALEH
 */

#ifndef GPS_H_
#define GPS_H_

#include"../service_layer/header.h"
#include"../MCAL/UART.h"
#include"../MCAL/EEPROM.h"


#define latit 0
#define longit 1

void get_latitute(unsigned char comma_place);
void get_longitute(unsigned char comma_place);
void convert_to_degree(unsigned char type);
void get_gps_reading();

//void get_time(unsigned char* sec,unsigned char* min,unsigned char* sec);



#endif /* GPS_H_ */
