/*
 * header.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: SALEH
 */

#ifndef HEADER_H_
#define HEADER_H_
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include<math.h>

#define button1 PD2
#define button2 PD3
#define button_dir DDRD
#define button_pin PIND
#define buzzer_dir DDRD
#define buzzer_port PORTD
#define buzzer 5
#define processing_dir DDRD
#define processing_port PORTD
#define process 4

#endif /* HEADER_H_ */
