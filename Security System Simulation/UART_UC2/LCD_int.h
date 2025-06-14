/*
 * LCD_int.h
 *
 *  Created on: 16 Aug 2021
 *      Author: norha
 */

#ifndef LCD_INT_H_
#define LCD_INT_H_
#define LCD_u8CLEAR_DISPLAY    0X01
#define LCD_u8RETURN_HOME    0X02

void LCD_vidWriteData(u8 Copy_Data);
void LCD_vidSendCommand(u8 Copy_Comand); //
void LCD_vidWriteString(u8 *Copy_String);
void LCD_vidInt();
void LCD_vidGoTo(u8 Copy_Row, u8 Copy_Column);

#endif /* LCD_INT_H_ */
