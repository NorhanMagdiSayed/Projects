/*
 * DIO_PROG.C
 *
 *  Created on: 15 Aug 2021
 *      Author: norha
 */


#include "../LIB/STD_TYPE.h"
#include "../LIB/MATH_H.h"
#include "../LIB/ATMEGA32_REGISTER.h"
#include "DIO_INT.h"


u8 var=0;


u8  DIO_u8GETPIN(u8 Copy_PortX , u8 Copy_PinX)
{
if(((Copy_PortX >= u8PORTA) && (Copy_PortX <= u8PORTD)) && ((Copy_PinX >= DIO_u8PIN_0) && (Copy_PinX <= DIO_u8PIN_7)))
{
	switch(Copy_PortX)
	{
	case u8PORTA:
		var=GET_BIT(PINA_REG ,Copy_PinX);
		break;
	case u8PORTB:
		var=GET_BIT(PINB_REG ,Copy_PinX);
		break;
	case u8PORTC:
		var=GET_BIT(PINC_REG ,Copy_PinX);
		break;
	case u8PORTD:
		var=GET_BIT(PIND_REG ,Copy_PinX);
		break;
	}
}

return var;
}

void DIO_vidSETPINval(u8 Copy_PortX , u8 Copy_PinX , u8 copy_value)

{


	if(((Copy_PortX >= u8PORTA) && (Copy_PortX <= u8PORTD)) && ((Copy_PinX >= DIO_u8PIN_0) && (Copy_PinX <= DIO_u8PIN_7)) \
			&& ((copy_value == DIO_u8HIGH) || (copy_value == DIO_u8LOW)))
	{
		if (copy_value==DIO_u8HIGH)
		{
			switch(Copy_PortX)
			{
			case u8PORTA:
				SET_BIT(PORTA_REG,Copy_PinX);
				break;
			case u8PORTB:
				SET_BIT(PORTB_REG,Copy_PinX);
				break;
			case u8PORTC:
				SET_BIT(PORTC_REG,Copy_PinX);
				break;
			case u8PORTD:
				SET_BIT(PORTD_REG,Copy_PinX);
				break;

			}
		}
			else if(copy_value == DIO_u8LOW)
			{

				switch(Copy_PortX)
				{
				case u8PORTA:
					CLR_BIT(PORTA_REG,Copy_PinX);
					break;
				case u8PORTB:
					CLR_BIT(PORTB_REG,Copy_PinX);
					break;
				case u8PORTC:
					CLR_BIT(PORTC_REG,Copy_PinX);
					break;
				case u8PORTD:
					CLR_BIT(PORTD_REG,Copy_PinX);
					break;

				}


			}

		}


	}
	void DIO_vidSetPinDirection(u8 Copy_PortX,u8 Copy_PinX, u8 Copy_Direction)
	{
		if(((Copy_PortX >= u8PORTA) && (Copy_PortX <= u8PORTD)) && ((Copy_PinX >= DIO_u8PIN_0) && (Copy_PinX <= DIO_u8PIN_7)) \
				&& ((Copy_Direction == DIO_u8INPUT) || (Copy_Direction == DIO_u8OUTPUT)))
		{
			if(Copy_Direction == DIO_u8INPUT)
			{
				switch(Copy_PortX)
				{
				case u8PORTA:
					CLR_BIT(DDRA_REG,Copy_PinX);
					break;
				case u8PORTB:
					CLR_BIT(DDRB_REG,Copy_PinX);
					break;
				case u8PORTC:
					CLR_BIT(DDRC_REG,Copy_PinX);
					break;
				case u8PORTD:
					CLR_BIT(DDRD_REG,Copy_PinX);
					break;
				}
			}
			else if(Copy_Direction == DIO_u8OUTPUT)
			{
				switch(Copy_PortX)
				{
				case u8PORTA:
					SET_BIT(DDRA_REG,Copy_PinX);
					break;
				case u8PORTB:
					SET_BIT(DDRB_REG,Copy_PinX);
					break;
				case u8PORTC:
					SET_BIT(DDRC_REG,Copy_PinX);
					break;
				case u8PORTD:
					SET_BIT(DDRD_REG,Copy_PinX);
					break;
				}
			}
		}

	}

	void DIO_vidSETPORTDIRECION(u8 copy_portx , u8 copy_direction)  // ALL THE 8 EIGHT PINS
	{

		if((copy_portx >= u8PORTA)&&(copy_portx <= u8PORTD))
		{
			switch (copy_portx)
			{
			case u8PORTA :
				DDRA_REG = copy_direction ;
				break;

			case u8PORTB :
				DDRB_REG = copy_direction ;
				break;

			case u8PORTC :
				DDRC_REG = copy_direction ;
				break;

			case u8PORTD :
				DDRD_REG = copy_direction ;
				break;
			}

		}


	}
	void DIO_vidSETPORTVAL(u8 COPY_PORTX , u8 copy_value)
	{
		if((COPY_PORTX >= u8PORTA)&&(COPY_PORTX <= u8PORTD))
		{
			switch (COPY_PORTX)
			{
			case u8PORTA :
				PORTA_REG = copy_value ;
				break;

			case u8PORTB :
				PORTB_REG = copy_value ;
				break;

			case u8PORTC :
				PORTC_REG = copy_value ;
				break;

			case u8PORTD :
				PORTD_REG = copy_value ;
				break;
			}
		}
	}

	void DIO_vidSTOGGPORTVAL(u8 copy_portX, u8 copy_pinX)
	{
		switch (copy_portX)
		{
		case u8PORTA:
			TOGGLE_BIT(PORTA_REG,copy_pinX);
			break;

		case u8PORTB:
			TOGGLE_BIT(PORTB_REG,copy_pinX);
			break;

		case u8PORTC:
			TOGGLE_BIT(PORTC_REG,copy_pinX);
			break;

		case u8PORTD:
			TOGGLE_BIT(PORTD_REG,copy_pinX);
			break;
		}
	}












