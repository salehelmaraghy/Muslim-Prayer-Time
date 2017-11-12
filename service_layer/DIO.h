/*
 * DIO.h
 *
 *  Created on: ??�/??�/????
 *      Author: SALEH
 */

#ifndef DIO_H_
#define DIO_H_

#define SETBIT(REG,NO) (REG|=(1<<NO))
#define CLEARBIT(REG,NO) (REG&=~(1<<NO))
#define CHECKBIT(REG,NO) ((REG&(1<<NO)))
#define CHECKBITZ(REG,NO) ((!(REG&(1<<NO))))


#endif /* DIO_H_ */
