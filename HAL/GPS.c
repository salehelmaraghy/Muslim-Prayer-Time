/*
 * GPS.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: SALEH
 */
#include "GPS.h"
#include"LCD.h"

volatile unsigned char data_buffer[70];
volatile unsigned char frame_type[6];
volatile unsigned char comma_pointer[20];
float longit_number;
float latit_number;
volatile unsigned char frame_check_name[6]={"GPGGA"};
volatile unsigned char flag=0;
volatile unsigned char x;
volatile unsigned char rec_char;
volatile unsigned char comma_index=0;
volatile unsigned char data_buffer_index=0;
volatile unsigned char check_flag=0;
unsigned char degree_buffer[15];

bool goingtocheck = false, //using this bool to first save the frame name $GPGGA in  frame buffer then save the numbers in data buffer
		readdata = false;

ISR(USART_RXC_vect)
{
	processing_port^=(1<<process); //to notify while processing
	rec_char=UDR; //received byte
	if(rec_char=='$') //start of a frame
	{
		check_flag=0;
		goingtocheck=true;
		readdata=false;
	}
	else if(goingtocheck==true) //get the frame GPGGA
	{
		if(check_flag<5)
		{
			frame_type[check_flag++]=rec_char;

			if(check_flag==5) { //if 5 chars received check the frame name
				x=strcmp((char*)frame_type,(char*)frame_check_name);

				if(x==0){//if frame name is GPGGA save numbers to data buffer
				check_flag=0;
				goingtocheck=false;
				readdata=true;
				}
				else { //if it's not GPGGA frame get other frames
					check_flag=0;
					goingtocheck=false;
					readdata=false;
				}
				check_flag=0;
			}
		}
	}
	else if((readdata==true) &&(goingtocheck==false)) //if its GPGGA frame save the numbers to parse it
	{
		flag++; //if the flag == 67 stop (by disable the interrupt) (a whole frame received)
		if(rec_char==',')
		{
			//saving the comma to help in parsing the data
			comma_pointer[comma_index++]=data_buffer_index;
		}
		data_buffer[data_buffer_index++]=rec_char;
	}
}

void get_latitute(unsigned char comma_place) //start parsing data
{
	//send for it commapointer[1] //take data from second comma to third comma that is the latitute number
	unsigned char i;
	comma_place++; //to get the number after the comma
	for(i=0;i<15;i++)
	{
		degree_buffer[i]=0; //to store in it the latitute, to avoid data overlap
	}
	i=0;
	while(data_buffer[comma_place]!=',')
	{
		degree_buffer[i]=data_buffer[comma_place];
		i++;
		comma_place++;
	}

	convert_to_degree(latit); //the numbers the GPS send is ASKI value so go convert it from ASKI in an array to a float number
}
void get_longitute(unsigned char comma_place)
{
	//send for it commapointer[3]
	unsigned char i;
	comma_place++;
	for(i=0;i<15;i++)
	{
		degree_buffer[i]=0;  //to store in it the longitute,use the same buffer of latitute to save memory
	}
	i=0;
	while(data_buffer[comma_place]!=',')
	{
		degree_buffer[i]=data_buffer[comma_place];
		i++;
		comma_place++;
	}
	convert_to_degree(longit); //to get it as a float number instead of ASKI numbers saved in an array
}
void convert_to_degree(unsigned char type)
{
	unsigned char i;
	int decimal;
	float data;
	float fraction;
	data=atof((char*)degree_buffer); //data=3116.1323;
	for(i=0;i<15;i++)
	{
		degree_buffer[i]=0;
	}

		data=data/100; //if its 3116.1323 to be 31.161323
		switch(type)
		{
		case latit:
			latit_number=data;
			break;
		case longit:
			longit_number=data;
			break;
		default:
			break;
		}
		//to show the number of long. lat. on the LCD(which only shows chars or strings) convert the float number to string
		//convert it to string by getting the decimal part and fraction part and display it at the LCD
		decimal=(int)data; //decimal=31
		fraction=(data-decimal);
		fraction*=1000000;
		//position=(float)decimal+fraction;
		sprintf((char*)degree_buffer,"%d.%d",decimal,(int)fraction); //long=29.5032     lat=  31.30139
		CLEAR_LCD();
		LCD_GOTO(2,1);
		LCD_SEND_STR(degree_buffer);_delay_ms(3000);
		CLEAR_LCD();
//we have the b=number in the degree buffer converted it to float,then make some process to it and return it back to the
//degree buffer so, it can be displayed on the LCD as a write number.
}

void get_gps_reading()
{
	//This function is to start the UART interrupt to get the longitute and latitute.
	int i=0;
	CLEAR_LCD();
	LCD_GOTO(1,1);
	LCD_SEND_STR("processing"); //waiting to receiver the GPGGA frame
	LCD_GOTO(1,1);
	sei(); //enable GLOBAL interrupt
	UART_RECEIVE_BYTE_INT(); //enable UART interrupt
	while(flag!=67); //wait the whole frame to come
	DISABLE_UART_INT();//disaple the UART interrupt
	flag=0;
		while(i!=5)
		{	frame_type[i++]=0;
		}
	get_latitute(comma_pointer[1]); //start parsing the frame to get longitute and latitute to save it in longit_number and latit_number
	get_longitute(comma_pointer[3]);
	EEPROM_WRITE_float(100,longit_number); //save this numbers to the EEPROM so if the power is cut off the data is saved to the EEPROM
	EEPROM_WRITE_float(108,latit_number);
}
