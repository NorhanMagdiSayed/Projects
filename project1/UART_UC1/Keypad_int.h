/*
 * Keypad_int.h
 *
 *  Created on: 17 Aug 2021
 *      Author: norha
 */

#ifndef KEYPAD_INT_H_
#define KEYPAD_INT_H_




#define PORT     2

#define ROW_1    DIO_u8PIN_0
#define ROW_2    DIO_u8PIN_1
#define ROW_3    DIO_u8PIN_2
#define ROW_4    DIO_u8PIN_3


#define COL_1   DIO_u8PIN_4
#define COL_2   DIO_u8PIN_5
#define COL_3   DIO_u8PIN_6
#define COL_4   DIO_u8PIN_7

#define NOT_Pressed  0

void Keypad_vidInit();
u8 Keypad_u8GetKey();   // she does the for loops until it finds the pressed button


#endif /* KEYPAD_INT_H_ */
