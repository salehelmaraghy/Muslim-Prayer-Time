/*
 * timer_app.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: DELL
 */
#include"timer_app.h"
//extern void (*function_ptr)(void)=timer_function;
extern uint8_t zohr_min,asr_min,maghrib_min,esha_min,fajr_min;
extern uint8_t zohr_hour,asr_hour,maghrib_hour,esha_hour,fajr_hour;
extern unsigned char min_rtc,hour_rtc;;

void timer_function()
{
	RTC_GET_TIME();//get time from the RTC

	if(min_rtc==zohr_min && hour_rtc==zohr_hour)
	{
		CLEAR_LCD();
		LCD_GOTO(1,1);
		LCD_SEND_STR("ZOHR TIME");
		buzzer_dir|=(1<<buzzer);
		buzzer_port|=(1<<4);
		_delay_ms(2000);
		buzzer_port&=~(1<<4);
	}
	else if(min_rtc==asr_min && hour_rtc==asr_hour)
	{
		CLEAR_LCD();
		LCD_GOTO(1,1);
		LCD_SEND_STR("ASR TIME");
		buzzer_dir|=(1<<buzzer);
		buzzer_port|=(1<<4);
		_delay_ms(1000);
		buzzer_port&=~(1<<4);
	}
	else if(min_rtc==maghrib_min && hour_rtc==maghrib_hour)
	{
		CLEAR_LCD();
		LCD_GOTO(1,1);
		LCD_SEND_STR("MAGHRIB TIME");
		buzzer_dir|=(1<<buzzer);
		buzzer_port|=(1<<buzzer);
		_delay_ms(1000);
		buzzer_port&=~(1<<buzzer);
	}
	else if(min_rtc==esha_min && hour_rtc==esha_hour)
	{
		CLEAR_LCD();
		LCD_GOTO(1,1);
		LCD_SEND_STR("ISHA TIME");
		buzzer_dir|=(1<<buzzer);
		buzzer_port|=(1<<4);
		_delay_ms(1000);
		buzzer_port&=~(1<<4);
	}
	else if(min_rtc==fajr_min && hour_rtc==fajr_hour)
	{
		CLEAR_LCD();
		LCD_GOTO(1,1);
		LCD_SEND_STR("FAJR TIME");
		buzzer_dir|=(1<<buzzer);
		buzzer_port|=(1<<4);
		_delay_ms(1000);
		buzzer_port&=~(1<<4);
	}
}

void call_timer()
{
	timer_30(&timer_function);
}
