/*
 * RTC.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: SALEH
 */
#include"RTC.h"
unsigned char sec_rtc,min_rtc,hour_rtc;
unsigned char day_rtc,month_rtc,year_rtc;

void RTC_SET_TIME(unsigned char sec,unsigned char min,unsigned char hour)
{
	TWI_start();
	TWI_send_DeviceAddress_Write(0x68);//because the address of RTC is 0xD0 so after shifting and ORing the 0x68 it become 0xD0

	TWI_send_data(00,MASTER);//send the address of the RTC pointer
	_delay_ms(100);
	TWI_send_data(sec,MASTER); //store at this address the second
	_delay_ms(100);
	TWI_send_data(min,MASTER); //the RTC will increment the pointer by default
	_delay_ms(1);
	TWI_send_data(hour,MASTER);
	_delay_ms(1);
	TWI_stop();
}
void RTC_SET_DATE(unsigned char day,unsigned char month,unsigned char year)
{

	TWI_start();

	TWI_send_DeviceAddress_Write(0x68);

	 TWI_send_data(04,MASTER);//send the address of the pointer to store the date
	 TWI_send_data(day,MASTER);
	_delay_ms(1);
	TWI_send_data(month,MASTER); //the RTC will increment the address by default
	_delay_ms(1);
	TWI_send_data(year,MASTER);
	_delay_ms(1);
	TWI_stop();
}

void RTC_GET_TIME()
{
	TWI_start();
	TWI_send_DeviceAddress_Write(0x68);
	TWI_send_data(0,MASTER); //the address I want to read data from it (update the RTC pointer)

	TWI_start();
	TWI_send_DeviceAddress_Read(0x68); //read the data
	sec_rtc=TWI_recieve_data_ACK(MASTER);
	decimal_to_hexa(&sec_rtc);
	min_rtc=TWI_recieve_data_ACK(MASTER);
	decimal_to_hexa(&min_rtc);
	hour_rtc=TWI_recieve_data_NACK(MASTER); //the last byte received don't replay with ACK
	decimal_to_hexa(&hour_rtc);
	TWI_stop();
}
void RTC_GET_DATE()
{
	TWI_start();
	TWI_send_DeviceAddress_Write(0x68);
	TWI_send_data(4,MASTER); //start read the date at address 4
	_delay_ms(5);
	TWI_start();
	_delay_ms(5);
	TWI_send_DeviceAddress_Read(0x68);
	_delay_ms(20);
	day_rtc=TWI_recieve_data_ACK(MASTER);
	decimal_to_hexa(&day_rtc);
	_delay_ms(5);
	month_rtc=TWI_recieve_data_ACK(MASTER);
	decimal_to_hexa(&month_rtc);
	_delay_ms(5);
	year_rtc=TWI_recieve_data_NACK(MASTER);
	decimal_to_hexa(&year_rtc);
	TWI_stop();
}

void decimal_to_hexa(unsigned char* number)
{ //The RTC store the number as hexadecimal number! so to use the numbers of the RTC we need to convert it to decimal
    unsigned char arr[5];
    int i=0,j=0,count=0;
    int temp1,temp2,temp3=*number;
    while((int)temp3!=0)
        {
        temp1=temp3%16;
        temp3=(int)(temp3/16);
        arr[count++]=temp1;
        }
        count--;
        for(i=0,j=count;i<=j;i++,j--)
        {
            temp2=arr[i];
            arr[i]=arr[j];
            arr[j]=temp2;
        }
       if((*number)>=10 && (*number)<=99)
       {
    	   *number=(arr[0]*10)+arr[1]*1;
       }
       else if((*number)>=100 && (*number)<=999)
       {
    	   *number=(arr[0]*100)+(arr[1]*10)+arr[0];
       }
}
