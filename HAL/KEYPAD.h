/*
 * KEYPAD.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: SALEH
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_
#include<avr/io.h>
#include<util/delay.h>
#include"../service_layer/DIO.h"
#define KEYPAD_DIR DDRA
#define KEYPAD_PORT PORTA
#define KEYPAD_PIN PINA

#define extern_zero 1

#define row_one 4
#define row_two 3
#define row_three 2
#define colomn_one 7
#define colomn_two 6
#define colomn_three 5

void keypad_init();
unsigned char scan();
unsigned char estimate_key(unsigned char row,unsigned char col);



#endif /* KEYPAD_H_ */
