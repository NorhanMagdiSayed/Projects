/*
 * ATMEGA32_REGISTER.H
 *
 *  Created on: 15 Aug 2021
 *      Author: norha
 */

#ifndef ATMEGA32_REGISTER_H_
#define ATMEGA32_REGISTER_H_

typedef union
{
	struct{
		u8 BIT_0 : 1 ;
		u8 BIT_1 : 1 ;
		u8 BIT_2 : 1 ;
		u8 BIT_3 : 1 ;
		u8 BIT_4 : 1 ;
		u8 BIT_5 : 1 ;
		u8 BIT_6 : 1 ;
		u8 BIT_7 : 1 ;
	}BITS;
	u8 Whole_Register ;
}tuniReg;


#define SREG_REG   ((*(volatile tuniReg*)((0x5F) )))


/*DIOA*/
#define PORTA_REG (*(volatile u8*)((0x3B) ))
#define DDRA_REG  (*(volatile u8*)((0x3A) ))
#define PINA_REG  (*(volatile u8*)((0x39) ))


/*DIOB*/
#define PORTB_REG   (*(volatile u8*)((0x38)))
#define DDRB_REG    (*(volatile u8*)((0x37)) )
#define PINB_REG    (*(volatile u8*)((0x36)) )

/*DIOC*/
#define PORTC_REG  (*(volatile u8*)((0x35) ) )
#define DDRC_REG   (*(volatile u8*)((0x34) ) )
#define PINC_REG   (*(volatile u8*)((0x33) ) )


/*DIOD*/
#define PORTD_REG   (*(volatile u8*)((0x32) ))
#define DDRD_REG    (*(volatile u8*)((0x31) ))
#define PIND_REG    (*(volatile u8*)((0x30) ))

/*EXTERNAL interrupts registers */

#define MCUCR_REG  ((*(volatile tuniReg*)((0x55) )))
#define GICR_REG   ((*(volatile tuniReg*)((0x5B) )))
#define GIFR_REG   ((*(volatile tuniReg*)((0x5A) )))

/* ADC REGISTERS  */

#define ADMUX_REG  ((*(volatile tuniReg*) ((0x27) )))  //ADC Multiplexer register
#define ADCSRA_REG ((*(volatile tuniReg*)((0x26) ))) //ADC CONTROL AND STATUS REGISTER
#define ADCH_REG  ((*(volatile tuniReg*)  ((0x25) ))) //ADC HIGH REGISTER
#define ADCL_REG ((*(volatile tuniReg*)   ((0x24) ))) //ADC LOW REGISTER

/* TIMER0 REGISTERS */

#define OCR0_REG   ((*(volatile tuniReg*)   ((0x5C) )))
#define TIMSK_REG  ((*(volatile tuniReg*)   ((0x59) )))
#define TCCR0_REG   ((*(volatile tuniReg*)   ((0x53) )))
#define TCNT0_REG   ((*(volatile tuniReg*)   ((0x52) )))  //counting register

/* TIMER1 REGISTERS */
#define TCCR1A_REG  ((*(volatile tuniReg*)   ((0x4f) )))
#define TCCR1B_REG  ((*(volatile tuniReg*)   ((0x4e) )))
#define TCNT1_REG  ((*(volatile u16*)        ((0x4C) )))  //accessing the 16 bit TCNT one at a time and starting adress of low because filling the least significant bits first
#define OCR1A_REG  ((*(volatile u16*)        ((0x4A) )))
#define OCR1B_REG  ((*(volatile u16*)        ((0x48) )))
#define ICR1_REG   ((*(volatile u16*)        ((0x46) )))

/*watchdog timer */
#define WDTCR_REG  ((*(volatile tuniReg*)   ((0x41) )))


/* UART REGISTERS */
#define UCSRC_REG  ((*(volatile tuniReg*)   ((0x40) )))
#define UBRRH_REG  ((*(volatile tuniReg*)   ((0x40) )))

#define UDR_REG  ((*(volatile tuniReg*)   ((0x2C) )))
#define UCSRA_REG  ((*(volatile tuniReg*)   ((0x2B) )))
#define UCSRB_REG  ((*(volatile tuniReg*)   ((0x2A) )))
#define UBRRL_REG  ((*(volatile tuniReg*)   ((0x29) )))

/* SPI REGISTERS*/
#define SPCR_REG ((*(volatile tuniReg*)   ((0x2D) )))
#define SPSR_REG ((*(volatile tuniReg*)   ((0x2E) )))
#define SPDR_REG ((*(volatile tuniReg*)   ((0x2F) )))
/*I2C REGISTERS*/
#define TWCR_REG ((*(volatile tuniReg*)   ((0x56) )))
#define TWDR_REG ((*(volatile tuniReg*)   ((0x23) )))
#define TWAR_REG ((*(volatile tuniReg*)   ((0x22) )))
#define TWSR_REG ((*(volatile tuniReg*)   ((0x21) )))
#define TWBR_REG ((*(volatile tuniReg*)   ((0x20) )))












#endif /* ATMEGA32_REGISTER_H_ */
