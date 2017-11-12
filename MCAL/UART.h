/*
 * UART.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: SALEH
 */

#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include "../service_layer/DIO.h"

#define UART_DIR DDRD
#define UART_PORT PORTD
#define osc_clk 8000000
#define tx 1
#define rx 0

void UART_INIT();
void UART_SEND_BYTE(unsigned char data);
unsigned char UART_RECEIVE_BYTE();
void UART_SEND_STRING(unsigned char* str); //take data from this str
void UART_RECEIVE_STRING(unsigned char* str); //to write data to this str
void UART_SEND_BYTE_INT(unsigned char data);
void UART_RECEIVE_BYTE_INT();
void DISABLE_UART_INT();

#endif /* UART_H_ */
