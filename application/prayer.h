/*
 * prayer.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: SALEH
 */

#ifndef PRAYER_H_
#define PRAYER_H_
#include"../service_layer/header.h"
#include"../HAL/LCD.h"
#include"../HAL/KEYPAD.h"
#include"../HAL/RTC.h"
#define PI 3.141592
#define MAGHRIB 0
#define ISHA 1
#define FAJR 2

double julian_date(uint16_t year,unsigned char month,unsigned char day);
void calc(double JD,double* EqTmin,double* dec_ang);
float zohr_fn(double EqTmin,signed char timezone,float longit_pray);
float asr_fn(float zohr,float latit_pray,double dec_angle);
float three_prayers(char pray,float latit_pray,double dec_angle,float zohr);
void convert_to_string(float time);
void get_min(float time,uint8_t* time_min,uint8_t* time_hour);
void set_date();
void choose_date_way();

#endif /* PRAYER_H_ */
