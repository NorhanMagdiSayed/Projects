/*
 * UART_prog.c
 *
 *  Created on: 29 Aug 2021
 *      Author: norha
 */
#include<avr/delay.h>
#include "STD_TYPE.h"
#include "DIO_INT.h"
#include "MATH_H.h"
#include "ATMEGA32_REGISTER.h"
#include <avr/interrupt.h>
#include "../ADC_Driver/ADC.h"
#include "UART_int.h"




void UART_vidInit(void)
{
UCSRC_REG.BITS.BIT_7 = 1 ;
UCSRC_REG.BITS.BIT_6 =  0 ; //parity disabled

UCSRC_REG.BITS.BIT_3 =  0;
UCSRC_REG.BITS.BIT_1 =  1;
UCSRC_REG.BITS.BIT_2 =  1;


/*parity mode disabled*/
UCSRC_REG.BITS.BIT_4 =  0;
UCSRC_REG.BITS.BIT_5=   0;
UCSRB_REG.BITS.BIT_2 =  0;

/*rx & TX */
UCSRB_REG.BITS.BIT_3 =  1;
UCSRB_REG.BITS.BIT_4 =  1;

/*bound rate 9600*/
UBRRL_REG.Whole_Register =  51 ;
UBRRH_REG.Whole_Register =  0 ;


}

void UART_vidSendByte(u8 copy_u8Data)
{
	while(UCSRA_REG.BITS.BIT_5 == 0);
	UDR_REG.Whole_Register = copy_u8Data ;
}

u8 UART_u8ReceiveByte(void)
{
	u8 local_u8Result ;
	while(UCSRA_REG.BITS.BIT_7==0);
	local_u8Result = UDR_REG.Whole_Register ;
	UCSRA_REG.BITS.BIT_7 = 0 ;

	return local_u8Result ;
}

