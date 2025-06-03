#include<avr/delay.h>
#include "../LIB/STD_TYPE.h"
#include "../DIO_DRIVER/DIO_int.h"
#include <avr/interrupt.h>
#include "../LIB/MATH_H.h"
#include "../LIB/ATMEGA32_REGISTER.h"
#include "PWM_int.h"

void PWM_vidInit(u8 Copy_TimerNo)
{
	switch(Copy_TimerNo)
	{
	case TIMER_0 :
		TCCR0_REG.BITS.BIT_3 = 1;
		TCCR0_REG.BITS.BIT_6 = 1;
		break;
	case TIMER_1 :
		/*set compare output mode , fast PWM to  Clear OC1A/OC1B on compare match, set
		OC1A/OC1B at BOTTOM */
		TCCR1A_REG.BITS.BIT_7 = 1 ;  //set OCr1a
		TCCR1A_REG.BITS.BIT_6 = 0  ;

		TCCR1A_REG.BITS.BIT_5= 0  ;
		TCCR1A_REG.BITS.BIT_4= 0  ;
		/* wave generation mode FAST PWM (MODE 14) */
		TCCR1A_REG.BITS.BIT_0= 0  ; //wgm10
		TCCR1A_REG.BITS.BIT_1= 1 ;//WGM11

		TCCR1B_REG.BITS.BIT_3= 1 ; //wgm12
		TCCR1B_REG.BITS.BIT_4= 1 ;//wgm13

		/*The Input Capture is updated with the counter (TCNT1) value each time an event occurs on the
		ICP1 pin (or optionally on the analog comparator output for Timer/Counter1 which is this case).*/
		ICR1_REG = PWM_ICR1_VALUE ;
		break ;

	case TIMER_2 :


		break;


	}
}

void PWM_vidSetPwmDutyCycle(u8 Copy_TimerNo , f32 Copy_DC )
{
	switch(Copy_TimerNo)
	{
	case TIMER_0 :

		OCR0_REG.Whole_Register = (u8)(((f32)Copy_DC*((f32)256))/100);

		break;
	case TIMER_1 :
		/*The Output Compare Registers contain a 16-bit value that is continuously compared with the
		counter value (TCNT1). A match can be used to generate an output compare interrupt, or to
		generate a waveform output on the OC1x pin.*/
		OCR1A_REG = (u16)(((f32)Copy_DC*((f32)PWM_ICR1_VALUE))/100);

		break;

	}
}

void PWM_StopTimer(u8 Copy_TimerNo )
{
	switch(Copy_TimerNo)
	{
	case TIMER_0 :
		TCCR0_REG.Whole_Register  &= 0xf8 ;
		break;

	case TIMER_1 :
		/* sets the first three bits zero (no clock source /timer stopped ) )*/
		TCCR1A_REG.Whole_Register &= 0xf8 ;
		break;
	}
}

void PWM_StartTimer(u8 Copy_TimerNo )
{
	switch(Copy_TimerNo)
	{
	case TIMER_0 :
		TCCR0_REG.Whole_Register &= PWM_CS_CLEAR_MASK ;
		TCCR0_REG.Whole_Register |= PWM_CS0_MODE;
		break;

	case TIMER_1 :
		/* clearing the register first four bits then seting only the first four bits based on the prescalar
		selected (clock select bit discription)*/
		TCCR1B_REG.Whole_Register &= PWM_CS_CLEAR_MASK ;
		TCCR1B_REG.Whole_Register |= PWM_CS1_MODE;
		break;
	}
}












