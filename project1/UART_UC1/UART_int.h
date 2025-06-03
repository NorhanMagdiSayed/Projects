/*
 * UART_int.h
 *
 *  Created on: 29 Aug 2021
 *      Author: norha
 */

#ifndef UART_INT_H_
#define UART_INT_H_

void UART_vidInit(void) ;
void UART_vidSendByte(u8 copy_u8Data) ;
u8 UART_u8ReceiveByte(void);




#endif /* UART_INT_H_ */
