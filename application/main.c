/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: SALEH
 */
#include"../HAL/GPS.h"
#include"prayer.h"
#include"timer_app.h"
#include"../MCAL/EEPROM.h"
#include"../MCAL/timer.h"
#include"../HAL/RTC.h"


extern uint16_t year_set;
extern unsigned char month_set,day_set;
extern volatile unsigned char flag;
extern volatile unsigned char data_buffer[70];
extern uint8_t prayer_time[7];
uint8_t zohr_min=0,asr_min=0,maghrib_min=0,esha_min=0,fajr_min=0;
uint8_t zohr_hour=0,asr_hour=0,maghrib_hour=0,esha_hour=0,fajr_hour=0;
int main()
{
//////**************pins direction**************************////
	SETBIT(processing_dir,process);
	CLEARBIT(button_dir,button1);
	CLEARBIT(button_dir,button2);
	SETBIT(buzzer_dir,buzzer);
	CLEARBIT(processing_port,process);//as its active low
	CLEARBIT(buzzer_port,buzzer); //turn of the buzzer.
/////*******************************************************////
	unsigned char counter=0;
    double JD,EqTmin,dec_ang;
    float zohr=0,asr=0,maghrib=0,esha=0,fajr=0;
    int i=0;
////****************INIT PHERIPHRALS************************////
	LCD_INIT();
	UART_INIT();
	TWI_init();
	keypad_init();
	RTC_SET_DATE(0x16,0x11,0x17);
	RTC_SET_TIME(0x14,0x42,0x12);
////***************Greeting message*************************////
	CLEAR_LCD();
	LCD_GOTO(2,1);
	LCD_SEND_STR("Prayer time");
	_delay_ms(3000);
	CLEAR_LCD();
////********************************************************////
	while(i!=150)
	{	data_buffer[i++]=0;
	}
	flag=0;
	_delay_ms(500);

////*****check if saved longit and latit or use the GPS****////
    float longit_eeprom=EEPROM_READ_float(100);
	float latit_eeprom=EEPROM_READ_float(108);
//*****************enter the date*************************////

	choose_date_way(); //to enter the date manually
	CLEAR_LCD();
	 //****************************to check if there is a previous long-lat saved in the eeprom********************/
	while((int)longit_eeprom==255 ||(int)latit_eeprom==255 ) //the EEPROM is empty
	{
		get_gps_reading();
		longit_eeprom=EEPROM_READ_float(100);
		latit_eeprom=EEPROM_READ_float(108);
	}
	while((int)longit_eeprom==0 ||(int)latit_eeprom==0 ) //the GPS not faced to the sky
	{
		get_gps_reading();
		longit_eeprom=EEPROM_READ_float(100);
		latit_eeprom=EEPROM_READ_float(108);
	}
	CLEAR_LCD();
//********************************some astronomical calculations based on the date***********************//
    JD=julian_date(year_set,month_set,day_set);
    calc(JD,&EqTmin,&dec_ang);
    zohr=zohr_fn(EqTmin,2,longit_eeprom);
    asr=asr_fn(zohr,latit_eeprom,dec_ang);
    maghrib=three_prayers(MAGHRIB,latit_eeprom,dec_ang,zohr);
    esha=three_prayers(ISHA,latit_eeprom,dec_ang,zohr);
    fajr=three_prayers(FAJR,latit_eeprom,dec_ang,zohr);
//**********get the minuit of each prayer time to compare it with the RTC to notify at the prayer time*********//
    get_min(zohr,&zohr_min,&zohr_hour);
    get_min(asr,&asr_min,&asr_hour);
    get_min(maghrib,&maghrib_min,&maghrib_hour);
    get_min(esha,&esha_min,&esha_hour);
    get_min(fajr,&fajr_min,&fajr_hour);

    timer_init(); //to set up the timer to check the time each 30 min.


	while(1)
	{
		call_timer();
		//timer_30();//check the RTC
//**check if buttons pressed for user interface to get the prayer time***//
		if(button_pin&(1<<button1))
		{
			_delay_ms(200);
			if(counter<4)
			{
				counter++;
			}
			else if(counter==4)
			{
				counter=4;
			}
		}
		if(button_pin&(1<<button2))
		{
			_delay_ms(200);
			if(counter>0)
			{
				counter--;
			}
			else if(counter==0)
			{
				counter=0;
			}
		}
		switch (counter)
		{
		case 0:
			LCD_GOTO(1,1);
			convert_to_string(zohr);
			LCD_SEND_STR("ZOHR ");
			LCD_SEND_STR((unsigned char*)prayer_time);
			break;
		case 1:
			LCD_GOTO(1,1);
			convert_to_string(asr);
		    LCD_SEND_STR("Asr ");
		    LCD_SEND_STR((unsigned char*)prayer_time);
		    break;
		case 2:
			LCD_GOTO(1,1);
			convert_to_string(maghrib);
		    LCD_SEND_STR("Magrib ");
		    LCD_SEND_STR((unsigned char*)prayer_time);
		    break;
		case 3:
			LCD_GOTO(1,1);
			convert_to_string(esha);
		    LCD_SEND_STR("Isha ");
		    LCD_SEND_STR((unsigned char*)prayer_time);
		    break;
		case 4:
			LCD_GOTO(1,1);
			convert_to_string(fajr);
		    LCD_SEND_STR("Fajr ");
		    LCD_SEND_STR((unsigned char*)prayer_time);
		    break;
		default:
			break;
		}
	}
	return 0;

}

