/*
 * main1.c
 *
 *  Created on: 29 Aug 2021
 *      Author: norha
 */

#include<avr/delay.h>
#include "STD_TYPE.h"
#include "MATH_H.h"
#include "ATMEGA32_REGISTER.h"
#include "Keypad_int.h"
#include "UART_int.h"
#include "DIO_int.h"





int main (void)
{
	UART_vidInit();
	Keypad_vidInit() ;
	while(1)
	{
		UART_vidSendByte(Keypad_u8GetKey());
	}



	return 0 ;
}

