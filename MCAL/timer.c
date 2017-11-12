/*
 * timer.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: SALEH
 */
#include"timer.h"
//#include"../HAL/RTC.h"

volatile unsigned char time_counter=0;
//extern unsigned char min_rtc,hour_rtc;;
//extern uint8_t zohr_min,asr_min,maghrib_min,esha_min,fajr_min;
//extern uint8_t zohr_hour,asr_hour,maghrib_hour,esha_hour,fajr_hour;
//using timer is to get every 30 seconds the time from the RTC and compare it with the prayer minuits if its equal the buzzer turn on
ISR(TIMER1_OVF_vect)
{
	time_counter++; //to get the 30 second
}

void timer_init()
{
	TCNT1=0;
	TCCR1A=0x00;
	TCCR1B=0x04; //normal mode, prescaler 256
	TIMSK|=(1<<TOIE1);//enable the timer interrupt
	SREG|=(1<<7);//enable global interrupt

}
void timer_30(void (*function_ptr)(void))
{
	if(time_counter==14) //30seconds have passed
	{
		time_counter=0;
		(*function_ptr)();  //calback function to a function in the application layer(timer_app.c)
//		RTC_GET_TIME();//get time from the RTC
//
//		if(min_rtc==zohr_min && hour_rtc==zohr_hour)
//		{
//			CLEAR_LCD();
//			LCD_GOTO(1,1);
//			LCD_SEND_STR("ZOHR TIME");
//			buzzer_dir|=(1<<buzzer);
//			buzzer_port|=(1<<4);
//			_delay_ms(2000);
//			buzzer_port&=~(1<<4);
//		}
//		else if(min_rtc==asr_min && hour_rtc==asr_hour)
//		{
//			CLEAR_LCD();
//			LCD_GOTO(1,1);
//			LCD_SEND_STR("ASR TIME");
//			buzzer_dir|=(1<<buzzer);
//			buzzer_port|=(1<<4);
//			_delay_ms(1000);
//			buzzer_port&=~(1<<4);
//		}
//		else if(min_rtc==maghrib_min && hour_rtc==maghrib_hour)
//		{
//			CLEAR_LCD();
//			LCD_GOTO(1,1);
//			LCD_SEND_STR("MAGHRIB TIME");
//			buzzer_dir|=(1<<buzzer);
//			buzzer_port|=(1<<buzzer);
//			_delay_ms(1000);
//			buzzer_port&=~(1<<buzzer);
//		}
//		else if(min_rtc==esha_min && hour_rtc==esha_hour)
//		{
//			CLEAR_LCD();
//			LCD_GOTO(1,1);
//			LCD_SEND_STR("ISHA TIME");
//			buzzer_dir|=(1<<buzzer);
//			buzzer_port|=(1<<4);
//			_delay_ms(1000);
//			buzzer_port&=~(1<<4);
//		}
//		else if(min_rtc==fajr_min && hour_rtc==fajr_hour)
//		{
//			CLEAR_LCD();
//			LCD_GOTO(1,1);
//			LCD_SEND_STR("FAJR TIME");
//			buzzer_dir|=(1<<buzzer);
//			buzzer_port|=(1<<4);
//			_delay_ms(1000);
//			buzzer_port&=~(1<<4);
//		}
	}
}
