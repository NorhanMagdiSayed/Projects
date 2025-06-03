/*
 * Keypad_prog.c
 *
 *  Created on: 17 Aug 2021
 *      Author: norha
 */

#include<avr/delay.h>
#include "../LIB/STD_TYPE.h"
#include "../LIB/MATH_H.h"
#include "../LIB/ATMEGA32_REGISTER.h"
#include "DIO_INT.h"
#include "../LCD_driver/LCD_int.h"
#include "Keypad_int.h"




u8 Keypad_Matrix[2][4]= // declaring a 2D array that has arrays one for rows other for columns
{
		{
			ROW_1 ,  //first element in array 0
			ROW_2 ,   //second element in array 0
			ROW_3 ,   //third element in array 0
			ROW_4 ,   //fourth element in array 0
		},
		{
		    COL_1,     //first element in array 1
			COL_2,    //second element in array 1
			COL_3,   //third element in array 1
			COL_4,   //fourth element in array 1
		}
};


u8 Keypad_Layout[4][4]= // 2d array with the all the characters aviable on the 4 X 4 keypad
{
		{'7','8','9','/'} ,  // first row in the keypad
		{'4','5','6','*'} ,  // second row in the keypad
		{'1','2','3','-'} ,   // third row in the keypad
		{ '#','0','=','+'} ,   // fourth row in the keypad
};









void Keypad_vidInit()
{
	//DDRB_REG = 0xF0 ;
	//PORTB_REG = 0xFF;
DIO_vidSetPinDirection(PORT,ROW_1,DIO_u8OUTPUT); // setting pins from 0, 1,2,3 from PORT(B) as output
DIO_vidSetPinDirection(PORT,ROW_2,DIO_u8OUTPUT); // setting pins from 0, 1,2,3 from PORT(B) as output
DIO_vidSetPinDirection(PORT,ROW_3,DIO_u8OUTPUT);// setting pins from 0, 1,2,3 from PORT(B) as output
DIO_vidSetPinDirection(PORT,ROW_4,DIO_u8OUTPUT);// setting pins from 0, 1,2,3 from PORT(B) as output

DIO_vidSetPinDirection(PORT,COL_1,DIO_u8INPUT); // setting pins 4,5,6,7 from PORT(B) as input
DIO_vidSetPinDirection(PORT,COL_2,DIO_u8INPUT); // setting pins 4,5,6,7 from PORT(B) as input
DIO_vidSetPinDirection(PORT,COL_3,DIO_u8INPUT); // setting pins 4,5,6,7 from PORT(B) as input
DIO_vidSetPinDirection(PORT,COL_4,DIO_u8INPUT); // setting pins 4,5,6,7 from PORT(B) as input

DIO_vidSETPINval(PORT,ROW_1,DIO_u8HIGH);  // setting the values of the output pins ( 0,1,2,3) as HIGH
DIO_vidSETPINval(PORT,ROW_2,DIO_u8HIGH);  // setting the values of the output pins ( 0,1,2,3) as HIGH
DIO_vidSETPINval(PORT,ROW_3,DIO_u8HIGH); // setting the values of the output pins ( 0,1,2,3) as HIGH
DIO_vidSETPINval(PORT,ROW_4,DIO_u8HIGH); // setting the values of the output pins ( 0,1,2,3) as HIGH

DIO_vidSETPINval(PORT,COL_1,DIO_u8HIGH);  //activating pull up mode by setting the value of port register of the input pins as HIGH
DIO_vidSETPINval(PORT,COL_2,DIO_u8HIGH);  //activating pull up mode by setting the value of port register of the input pins as HIGH
DIO_vidSETPINval(PORT,COL_3,DIO_u8HIGH);  //activating pull up mode by setting the value of port register of the input pins as HIGH
DIO_vidSETPINval(PORT,COL_4,DIO_u8HIGH); //activating pull up mode by setting the value of port register of the input pins as HIGH



}

u8 Keypad_u8GetKey()
{
u8 ROW_iterator ;  // declaring iterator for the rows array
u8 COL_iterator ;  //declaring iterator for column array


for(ROW_iterator =0 ; ROW_iterator < 4; ROW_iterator ++ )  // for loop to set one of the output pins as low
{
	DIO_vidSETPINval(PORT,Keypad_Matrix[0][ROW_iterator],DIO_u8LOW); // setting one output pin as low based on the loop cycle
	 //Iterating over the elements in the first element in keypad_matrix

	for(COL_iterator=0;COL_iterator < 4; COL_iterator ++) // for loop to check if a button is pressed and one of the inputs pins became LOW
	{
		if(DIO_u8GETPIN(PORT,Keypad_Matrix[1][COL_iterator])== 0) // checking if there is a button pressed & if one input pin became low
		{
			while(DIO_u8GETPIN(PORT,Keypad_Matrix[1][COL_iterator])== 0) // protecting to avoid debouncing
			{

			};
			 //while the button is pressed the return wont happen because while pressed its infinite loop
			return Keypad_Layout[ROW_iterator][COL_iterator]; /* the value of the pressed button returns only the instant
				the button is released and the while condition isn't satisfied */
		}

	}


	DIO_vidSETPINval(PORT,Keypad_Matrix[0][ROW_iterator],DIO_u8HIGH); // setting the output pin that was low to high
}
return NOT_Pressed ; // in case no button is pressed it returns 0

}












