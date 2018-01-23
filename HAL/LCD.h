/*
 * LCD.H
 *
 *  Created on: ??þ/??þ/????
 *      Author: SALEH
 */

#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h>
#include <util/delay.h>
#include "../service_layer/DIO.h"
#define LCD_CONTROL_DIR DDRC
#define LCD_CONTROL_PORT PORTC
#define LCD_DATA_DIR DDRB
#define LCD_DATA_PORT PORTB

#define FOURBIT

#define EN 7
#define RS 6

void LCD_INIT();
void LCD_COMMAND(unsigned char cmd);
void LCD_SEND_CHAR(unsigned char data);
void LCD_SEND_STR(unsigned char* data);
void LCD_SEND_INT(unsigned int number);
void LCD_GOTO(unsigned char row,unsigned char col);
//void ENABLE_LCD();
void CLEAR_LCD();


#endif /* LCD_H_ */
