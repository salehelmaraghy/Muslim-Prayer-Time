/*
 * prayer.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: SALEH
 */
#include"prayer.h"
extern unsigned char day_rtc,month_rtc,year_rtc;
uint8_t prayer_time[7];
uint16_t year_set;
unsigned char month_set,day_set;
double julian_date(uint16_t year,unsigned char month,unsigned char day)
{
	//this function is to get the julian data of the data either you have entered or saved on the RTC
	uint32_t a,b;
    double JD;

    a=(uint32_t)year/100;
    b=2-a+(uint32_t)(a/4);
    JD=(uint32_t)(365.25*(year+4716))+(uint32_t)(30.6001*(month+1))+day+b-1524.5;

    //this commented part is if you want to display the JD on the LCD
//    uint32_t decimal;
//    double  fraction;
//    decimal= (uint32_t)JD;
//    fraction=JD-decimal;
//    fraction*=10000;
//    //printf("%lf\n",JD);
//    sprintf(arr,"%ld.%ld",decimal,(uint32_t)fraction);
//    LCD_GOTO(2,1);
//    LCD_SEND_STR((unsigned char*)arr);

    return(JD);

}
void calc(double JD,double* EqTmin,double* dec_ang)
{
	//this function is to get the Equation of time and Dec. angle of the sun of the given julian data

    double val2=PI/180;
    double val,g,q,L,R,RA,EqT,d,e;
    uint32_t temp;
    uint32_t decimal;
    val = 180.0/PI;
   // d=2457905.5-2451545.0;
    d = JD - 2451545.0;  // jd is the given Julian date

   g = 357.529 + 0.98560028* d;
   q = 280.459 + 0.98564736* d;
   L = q + 1.915* sin(g*val2) + 0.020* sin(2*g*val2);

   R = 1.00014 - 0.01671* cos(g*val2) - 0.00014* cos(2*g*val2);
   e = 23.439 - 0.00000036* d;
   RA = (atan2(cos(e*val2)* sin(L*val2), cos(L*val2))*val)/ 15;

   *dec_ang = (asin((sin(e*val2))*(sin(L*val2)))*val);  // declination of the Sun
   EqT = q/15 - RA;  // equation of time
   temp=(int32_t)EqT;
   float fraction=EqT-temp;
   fraction=fraction*10000;
   decimal=(int32_t)fraction;
   *EqTmin=EqT-temp;
   /********the next commented part is if you want to display the Eq of time******************/
//   sprintf(arr,"%ld.%ld",temp,decimal);
//   LCD_GOTO(2,1);
//   LCD_SEND_STR((unsigned char*)arr);
//   _delay_ms(5000);
}

float zohr_fn(double EqTmin,signed char timezone,float longit_pray)
{ //this function is to get the zohr time based on the time zone of your city (difference between your city and GMT) and longit number
    float zohr;
    zohr=12+timezone-(longit_pray/15)-EqTmin;
    //convert_to_string(zohr);
    return zohr; //it's not preferable to return float number so for more precise number use it as global variable
}

float asr_fn(float zohr,float latit_pray,double dec_angle)
{
	//this function is to get  the asr time based on the Zohr time and the latit.
    float asr;
    double val2=PI/180, val=180.0/PI;
    double temp,alt;
    float phi=latit_pray-dec_angle;
    temp=1/(1+tan(phi*val2));
    alt=atan(temp)*val;

    temp=(sin(alt*val2)-(sin(dec_angle*val2)*sin(latit_pray*val2)))/(cos(dec_angle*val2)*cos(latit_pray*val2));
    temp=acos(temp)*val;
    temp=temp/15;
    asr=zohr+temp;
    //convert_to_string(asr);
    return asr;
}
float three_prayers(char pray,float latit_pray,double dec_angle,float zohr)
{ //as the Maghrib,Isha,Fajr  have the same function but just a variable changed for them
    float time=0;
    double val2=PI/180, val=180.0/PI;
    char x;
    switch (pray)
    {
    case MAGHRIB:
        x=0.833;
        time=(-sin(x*val2)-(sin(dec_angle*val2)*sin(latit_pray*val2)))/(cos(dec_angle*val2)*cos(latit_pray*val2));
        time=acos(time)*val;
        time=time/15;
        time=zohr+time;
        break;
    case ISHA:
        x=17.5;
        time=(-sin(x*val2)-(sin(dec_angle*val2)*sin(latit_pray*val2)))/(cos(dec_angle*val2)*cos(latit_pray*val2));
        time=acos(time)*val;
        time=time/15;
        time=zohr+time;
        break;
    case FAJR:
        x=19.5;
        time=(-sin(x*val2)-(sin(dec_angle*val2)*sin(latit_pray*val2)))/(cos(dec_angle*val2)*cos(latit_pray*val2));
        time=acos(time)*val;
        time=time/15;
        time=zohr-time; //this differs from them
        break;
    default:
        break;
    }
  // convert_to_string(time);
   return time;
}
void convert_to_string(float time)
{
//this function is to convert the float number of zohr,asr,.... to hours,minuits and seconds
	uint8_t degree,minuits,seconds1,seconds2;
	float degree_frac1,degree_frac2;
	degree=(int)time;
	degree_frac1=time-degree;
	degree_frac1=degree_frac1*60;
	minuits=(int)degree_frac1;
	degree_frac2=minuits-degree_frac1;
	degree_frac2=degree_frac2*60;
	seconds1=(int)degree_frac2;
	degree_frac2=seconds1-degree_frac2;
	seconds2=degree_frac2*10;
	while(seconds1>60){
		seconds1-=60;
	}
	sprintf((char*)prayer_time,"%d:%d:%d.%d",degree,minuits,seconds1,seconds2);
}
void get_min(float time,uint8_t* time_min,uint8_t* time_hour)
{
	//this function is to save the minuit of each prayer time to compare it with the current time from the RTC to turn the BUZZER
	//on at the prayer time.
	uint8_t degree,minuits;
	float degree_frac1;
	degree=(int)time;
	degree_frac1=time-degree;
	degree_frac1=degree_frac1*60;
	minuits=(int)degree_frac1;
	*time_hour=degree;
	*time_min=minuits;
}
void set_date()
{
//this function is used when you choose to enter the date manually not depending on the RTC date
//this function is using the KEYPAD file
		bool goscan=true,	//to scan the number
			goprint=false;	//to display the number you have entered
		LCD_SEND_STR("enter the date");
		_delay_ms(1000);
		CLEAR_LCD();
		char arr_set[5];
		int m;
		unsigned char i=0,j=0,k=0;
		unsigned char flag_set=0;
		char key=-1;
		LCD_GOTO(1,1);

			while(j<3){ //which is the 1-day 2-month 3-year
				if(j==0 && flag_set==0)
				{
					LCD_SEND_STR("day");
					flag_set=1; //to enter four digits
					_delay_ms(200);
				}
				else if(j==1 && flag_set==0 )
				{
					LCD_GOTO(1,8);
					LCD_SEND_STR("month");
					flag_set=1;
					_delay_ms(200);

				}
				else if(j==2 && flag_set==0)
				{
					LCD_GOTO(2,1);
					LCD_SEND_STR("year ");
					flag_set=1;
					_delay_ms(200);
				}
			if((goscan)==true){
			key= scan();
			if(key!=-1 && key!=255){  //keep scaning
				arr_set[i++]=key;
				goprint=true;
				goscan=false;
				key=-1; //quit scanning
					  }}
			if(goprint==true){
				LCD_SEND_INT(arr_set[i-1]);
				_delay_ms(200); //due to the floating of the keypad buttons
				key=-1;
				goscan=true;
				goprint=false;
			}
			if(i==4)
			{
				for(m=0;m<4;m++)
				{
					arr_set[m]+=48; //as array to Int function consider the numbers in the array as ASKI values
				}
				//CLEAR_LCD();
				j++;k++;
				flag_set=0;
				arr_set[i] = '\0';
				if(k==1)
				{
					day_set=atoi((char*)arr_set); //to use the number in our calculations
 				}
				else if(k==2)
				{
					month_set=atoi((char*)arr_set);
				}
				else if(k==3)
				{
					year_set=atoi((char*)arr_set);
				}
				i=0;
			}
					}

	}
void choose_date_way()
{
	//this function is to let the user to choose either enter the date manually or get ir from the RTC
	CLEAR_LCD();
	LCD_GOTO(1,1);
	LCD_SEND_STR("press1enter date");
	LCD_GOTO(2,1);
	LCD_SEND_STR("press2 RTC date");
	uint8_t key_flag=0;
	while(key_flag==0)
	{
		if(CHECKBIT(button_pin,button1))
		{ //if button one pressed so it means enter manually
			_delay_ms(200);
			key_flag=1;
		}
		if(CHECKBIT(button_pin,button2))
		{ //if button one pressed so it means to get it from the RTC
			_delay_ms(200);
			key_flag=2;
		}
	}
	if(key_flag==1)
	{
		set_date();
	}
	else if(key_flag==2)
	{
		RTC_GET_DATE();
		year_set=year_rtc+2000; //+2000 because the date saved to the RTC as the last 2 digits only
		day_set=day_rtc; //this variables are global ones,will be used to get the julian data at the main function.
		month_set=month_rtc;
	}
}
