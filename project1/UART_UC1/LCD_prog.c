/*
 * LCD_prog.c
 *
 *  Created on: 16 Aug 2021
 *      Author: norha
 */
#include<avr/delay.h>
#include "../LIB/STD_TYPE.h"
#include "../LIB/MATH_H.h"
#include "DIO_int.h"
#include "DIO_PROG.C"
#include "../LIB/ATMEGA32_REGISTER.h"
#include "../LCD_DRIVER/LCD_int.h"



void LCD_vidWriteData(u8 Copy_Data)
{
	DIO_vidSETPINval(u8PORTA,DIO_u8PIN_0,DIO_u8HIGH);
	DIO_vidSETPINval(u8PORTA,DIO_u8PIN_1,DIO_u8LOW);
	DIO_vidSETPORTVAL(u8PORTB,Copy_Data);
	DIO_vidSETPINval(u8PORTA,DIO_u8PIN_2,DIO_u8HIGH);
	_delay_ms(1.533);

	DIO_vidSETPINval(u8PORTA,DIO_u8PIN_2,DIO_u8LOW);
}

void LCD_vidSendCommand(u8 Copy_Comand)
{
	DIO_vidSETPINval(u8PORTA,DIO_u8PIN_0,DIO_u8LOW);
	DIO_vidSETPINval(u8PORTA,DIO_u8PIN_1,DIO_u8LOW);
	DIO_vidSETPORTVAL(u8PORTB, Copy_Comand);
	DIO_vidSETPINval(u8PORTA,DIO_u8PIN_2,DIO_u8HIGH);
	_delay_ms(1.533);

	DIO_vidSETPINval(u8PORTA,DIO_u8PIN_2,DIO_u8LOW);
}



void LCD_vidWriteString(u8 *Copy_String)
{
	u8 iterator ;
	for(iterator =0 ; Copy_String[iterator]!= 0 ;iterator ++ )
	{
		LCD_vidWriteData(Copy_String[iterator]);
	}
}

void LCD_vidInt()
{
	DIO_vidSetPinDirection(u8PORTA,DIO_u8PIN_0,DIO_u8OUTPUT);
	DIO_vidSetPinDirection(u8PORTA,DIO_u8PIN_1,DIO_u8OUTPUT);
	DIO_vidSetPinDirection(u8PORTA,DIO_u8PIN_2,DIO_u8OUTPUT);
	DIO_vidSETPORTDIRECION(u8PORTB,DIO_u8OUTPUT);
	_delay_ms(30);
	LCD_vidSendCommand(0b00111000);//step2
	_delay_us(39); // microseconds
	LCD_vidSendCommand(0b00001111);//step4
	_delay_us(39); // microseconds
	LCD_vidSendCommand(LCD_u8CLEAR_DISPLAY);
	_delay_ms(1.53);
	LCD_vidSendCommand(0b00000110);

}
void LCD_vidGoTo(u8 Copy_Row, u8 Copy_Column)
{
	if((Copy_Column >=0)&&(Copy_Column<=15))
	{
		switch(Copy_Row)
		{
		case 0 :
			LCD_vidSendCommand(0b010000000 + Copy_Column);
			break;
		case 1 :
		LCD_vidSendCommand(0b110000000 + Copy_Column);
			break;}
	}
}


















