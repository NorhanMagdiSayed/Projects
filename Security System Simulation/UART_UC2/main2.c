
#include<avr/delay.h>
#include "STD_TYPE.h"
#include "MATH_H.h"
#include "ATMEGA32_REGISTER.h"
#include "DIO_INT.h"
#include "UART_int.h"
#include <avr/interrupt.h>
#include "LCD_int.h"


char pass[4]= { '5','2','6','0' } ; //previously saved password array
char enter[4] ;  //password array to be entered by the user

u8 wrong_counter = 0 ; //variable counts number of failed trials entered by the user
u8 segment_counter=0; //variable that holds the number of failed counts to be displayed on the 7 segment using the "Numbers" array
u8 counter = 6; //starting point on the LCD while entering the password
u8 element = 0  ; // variable for the enter array
u8 star = '*' ; // star variable holds the ASCII code for the character '*'
u8 data ;  // variable that takes the received data from function UART_ReceivedByte
void check_pass(void);   //function that checks if the password entered is the same as the one previously stored
void fill_array(u8 digit);  // function that stores the password entered by the user
void key_print(void); // function that takes the received data and prints it on the LCD
void start_pass (void); // function that displays the string "pass = " and calls the key_print function 5 times for each character
void warning(void); // function that displays on the LCD "warning there is an intruder " after three failed trails
void segment (void);  //

u8 Numbers[3]=
{
		0b01111001,
		0b00100100,
		0b00110000,
};
int main (void)
{

	DIO_vidSetPinDirection(u8PORTD,DIO_u8PIN_4,DIO_u8OUTPUT); //Green Leds
	DIO_vidSetPinDirection(u8PORTD,DIO_u8PIN_5,DIO_u8OUTPUT); //Red Leds
	DIO_vidSetPinDirection(u8PORTD,DIO_u8PIN_6,DIO_u8OUTPUT); //Buzzer
	//motor pins
	DIO_vidSetPinDirection(u8PORTA,DIO_u8PIN_6,DIO_u8OUTPUT);
	DIO_vidSetPinDirection(u8PORTA,DIO_u8PIN_7,DIO_u8OUTPUT);

	//initiating all leds to low
	DIO_vidSETPINval(u8PORTD,DIO_u8PIN_4,DIO_u8LOW);
	DIO_vidSETPINval(u8PORTD,DIO_u8PIN_5,DIO_u8LOW);

	//PIR sensor
	DIO_vidSetPinDirection(u8PORTD,DIO_u8PIN_2,DIO_u8INPUT);
	DIO_vidSETPINval(u8PORTD,DIO_u8PIN_2,DIO_u8HIGH);

	//7 segment
	DIO_vidSETPORTDIRECION(u8PORTC,0xff);
	DIO_vidSETPORTVAL(u8PORTC,0xff);

//	DDRC=0XFF;
//	PORTC=0XFF;

	UART_vidInit();
	LCD_vidInt();
	start_pass();

	while(1)
	{
		for(u8 k = 0 ; k < 5; k++)
		{
			key_print();
		}

	}


	return 0 ;
}

void start_pass (void)
{
	LCD_vidSendCommand(LCD_u8CLEAR_DISPLAY);
	LCD_vidWriteString("pass =");
	for(u8 k = 0 ; k < 5; k++)
	{
		key_print(); }
}

void key_print()
{   data = UART_u8ReceiveByte();

if (data)
{
	switch (data)
	{

	case '1':
		_delay_ms(100);
		LCD_vidWriteString("1");
		fill_array('1');
		_delay_ms(200);
		LCD_vidGoTo(0,counter);
		LCD_vidWriteData(star);
		counter ++ ;
		break ;
	case '2':
		_delay_ms(100);
		LCD_vidWriteString("2");
		fill_array('2');
		_delay_ms(200);
		LCD_vidGoTo(0,counter);
		LCD_vidWriteData(star);
		counter ++ ;
		break ;
	case '3':
		_delay_ms(100);
		LCD_vidWriteString("3");
		fill_array('3');
		_delay_ms(200);
		LCD_vidGoTo(0,counter);
		LCD_vidWriteData(star);
		counter ++ ;
		break ;

	case '4':
		_delay_ms(100);
		LCD_vidWriteString("4");
		fill_array('4');
		_delay_ms(200);
		LCD_vidGoTo(0,counter);
		LCD_vidWriteData(star);
		counter ++ ;
		break ;
	case '5':
		_delay_ms(100);
		LCD_vidWriteString("5");
		fill_array('5');
		_delay_ms(200);
		LCD_vidGoTo(0,counter);
		LCD_vidWriteData(star);
		counter ++ ;
		break ;
	case '6':
		_delay_ms(100);
		LCD_vidWriteString("6");
		fill_array('6');
		_delay_ms(200);
		LCD_vidGoTo(0,counter);
		LCD_vidWriteData(star);
		counter ++ ;
		break ;
	case '7':
		_delay_ms(100);
		LCD_vidWriteString("7");
		fill_array('7');
		_delay_ms(200);
		LCD_vidGoTo(0,counter);
		LCD_vidWriteData(star);
		counter ++ ;
		break ;

	case '8':
		_delay_ms(100);
		LCD_vidWriteString("8");
		fill_array('8');
		_delay_ms(200);
		LCD_vidGoTo(0,counter);
		LCD_vidWriteData(star);
		counter ++ ;
		break ;

	case '9':
		_delay_ms(500);
		LCD_vidWriteString("9");
		fill_array('9');
		_delay_ms(200);
		LCD_vidGoTo(0,counter);
		LCD_vidWriteData(star);
		counter ++ ;
		break ;
	case '0':
		_delay_ms(100);
		LCD_vidWriteString("0");
		fill_array('0');
		_delay_ms(200);
		LCD_vidGoTo(0,counter);
		LCD_vidWriteData(star);
		counter ++ ;
		break ;

	case '#':

		LCD_vidSendCommand(LCD_u8CLEAR_DISPLAY);
		check_pass();

		break ;
	}
}
}
void fill_array(u8 digit)
{

	enter[element] = digit ;
	element++ ;


}

void check_pass(void)
{
	if((enter[0] == pass[0])&&(enter[1] == pass[1])&&(enter[2] == pass[2])&&(enter[3] == pass[3]))
	{
		LCD_vidSendCommand(LCD_u8CLEAR_DISPLAY);
		LCD_vidGoTo(0,0);
		LCD_vidWriteString("access approved");

		DIO_vidSETPINval(u8PORTD,DIO_u8PIN_4,DIO_u8HIGH);
		DIO_vidSETPINval(u8PORTD,DIO_u8PIN_6,DIO_u8HIGH);
		_delay_ms(50);
		DIO_vidSETPINval(u8PORTD,DIO_u8PIN_6,DIO_u8LOW);

		DIO_vidSETPINval(u8PORTA,DIO_u8PIN_6,DIO_u8HIGH);  //motor (door opens) clockwise
		DIO_vidSETPINval(u8PORTA,DIO_u8PIN_7,DIO_u8LOW);

		_delay_ms(2000);
		DIO_vidSETPINval(u8PORTA,DIO_u8PIN_6,DIO_u8LOW);  //motor (door stops)
		DIO_vidSETPINval(u8PORTA,DIO_u8PIN_7,DIO_u8LOW);
		do
		{


		}while(DIO_u8GETPIN(u8PORTD,DIO_u8PIN_2) == DIO_u8HIGH);    // check if there is still someone

		DIO_vidSETPINval(u8PORTA,DIO_u8PIN_7,DIO_u8HIGH); //motor (door closes) anti-clockwise
		DIO_vidSETPINval(u8PORTA,DIO_u8PIN_6,DIO_u8LOW);

		_delay_ms(2000);
		DIO_vidSETPINval(u8PORTA,DIO_u8PIN_7,DIO_u8LOW); // motor (door stops)
		DIO_vidSETPINval(u8PORTA,DIO_u8PIN_6,DIO_u8LOW);
		DIO_vidSETPINval(u8PORTD,DIO_u8PIN_4,DIO_u8LOW);
		element = 0 ;
		counter = 6 ;
		for(u8 iterator=0;iterator<4;iterator++)
		{
			enter[iterator]='0';
		}
		start_pass();

	}

	else
	{
		LCD_vidSendCommand(LCD_u8CLEAR_DISPLAY);
		LCD_vidGoTo(0,0);
		LCD_vidWriteString("access denied");

		segment();
		_delay_ms(500);
		start_pass();
		element = 0 ;
		counter = 6 ;
		wrong_counter ++ ;
		if(wrong_counter<3)
		{
			DIO_vidSETPINval(u8PORTD,DIO_u8PIN_5,DIO_u8HIGH);
			for(u8 iterator=0;iterator<2;iterator++)
			{
			DIO_vidSETPINval(u8PORTD,DIO_u8PIN_6,DIO_u8HIGH);
			_delay_ms(100);
			DIO_vidSETPINval(u8PORTD,DIO_u8PIN_6,DIO_u8LOW);
			_delay_ms(100);
			}
			DIO_vidSETPINval(u8PORTD,DIO_u8PIN_5,DIO_u8LOW);


		}
		warning();
	}
}

void warning(void)
{


	if(wrong_counter==3)
	{
		LCD_vidSendCommand(LCD_u8CLEAR_DISPLAY);
		LCD_vidGoTo(0,0);
		LCD_vidWriteString("WARNING!");
		_delay_ms(500);
		LCD_vidSendCommand(LCD_u8CLEAR_DISPLAY);
		LCD_vidWriteString("THERE IS");
		LCD_vidGoTo(1,0);
		LCD_vidWriteString("AN INTRUDER!!");
		for(u8 iterator=0;iterator<10;iterator++)
		{
			DIO_vidSETPINval(u8PORTD,DIO_u8PIN_6,DIO_u8HIGH);
			DIO_vidSTOGGPORTVAL(u8PORTD,DIO_u8PIN_5);
			_delay_ms(400);
			DIO_vidSETPINval(u8PORTD,DIO_u8PIN_6,DIO_u8LOW);
			_delay_ms(100);

		}
		LCD_vidSendCommand(LCD_u8CLEAR_DISPLAY);
	}


}

void segment(void)
{

	if(segment_counter==0)
	{
		DIO_vidSETPORTVAL(u8PORTC,Numbers[0] );
	}
	if(segment_counter==1)
	{
		DIO_vidSETPORTVAL(u8PORTC,Numbers[1] );
	}
	if(segment_counter==2)
	{
		DIO_vidSETPORTVAL(u8PORTC,Numbers[2]);
	}
	segment_counter++;
}


