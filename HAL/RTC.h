/*
 * RTC.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: SALEH
 */

#ifndef RTC_H_
#define RTC_H_

#include "../MCAL/TWI.h"

void RTC_SET_TIME(unsigned char sec,unsigned char min,unsigned char hour);
void RTC_SET_DATE(unsigned char day,unsigned char month,unsigned char year);
void RTC_GET_TIME();
void RTC_GET_DATE();
void decimal_to_hexa(unsigned char* number);
#endif /* RTC_H_ */
