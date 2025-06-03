/*
 * DIO_INT.h
 *
 *  Created on: 15 Aug 2021
 *      Author: norha
 */

#ifndef DIO_INT_H_
#define DIO_INT_H_
#define DIO_INT_H_

#define u8PORTA            1
#define u8PORTB            2
#define u8PORTC            3
#define u8PORTD            4




 #define DIO_u8PIN_0     0
 #define DIO_u8PIN_1     1
 #define DIO_u8PIN_2     2
 #define DIO_u8PIN_3     3
 #define DIO_u8PIN_4     4
 #define DIO_u8PIN_5     5
 #define DIO_u8PIN_6     6
 #define DIO_u8PIN_7     7


#define DIO_u8INPUT  0
#define DIO_u8OUTPUT 1


#define DIO_u8HIGH  0
#define DIO_u8LOW   1






u8  DIO_u8GETPIN(u8 Copy_PortX , u8 Copy_PinX);
void DIO_vidSETPINval(u8 Copy_PortX , u8 Copy_PinX , u8 copy_value);
void DIO_vidSetPinDirection(u8 Copy_PortX,u8 Copy_PinX, u8 Copy_Direction);

void DIO_vidSETPORTDIRECION(u8 copy_portx , u8 copy_direction); // ALL THE 8 EIGHT PINS
void DIO_vidSETPORTVAL(u8 COPY_PORTX , u8 copy_value);
void DIO_vidSTOGGPORTVAL(u8 COPY_PORTX , u8 copy_PINx);




#endif /* DIO_INT_H_ */
