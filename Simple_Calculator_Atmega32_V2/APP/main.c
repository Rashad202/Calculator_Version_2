/*
 * main.c
 *
 *  Created on: 26 Sep 2023
 *      Author: Rashad
 */


#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"

#include "../MCAL/DIO/DIO_Interface.h"

#include "../HAL/LCD/LCD_Interface.h"
#include "../HAL/KPAD/KPAD_Interface.h"

#include "avr/delay.h"



void main()
{

	LCD_voidInit();
	KPAD_voidInit();
	LCD_voidClearDisplay();
	LCD_voidWriteString("Welcome To");
	LCD_voidGoTo_XY(1,0);
	LCD_voidWriteString("My Calculator");
	_delay_ms(800);
	LCD_voidClearDisplay();
	u32 Num1=0;
	u32 Num2=0;
	u8 Operator=0;
	u32 Result=0;
	u8 Localcounter=0xff;

	while(1)
	{
		Localcounter=KPAD_u8GetPressedKey();

		if(Localcounter >='0' && Localcounter <='9'  )
		{
			LCD_voidWriteChar( Localcounter ) ;
			if ( Operator == 0 )
			{
				Num1= Num1*10 + ( Localcounter - '0') ;
			}
			else
			{
				Num2= Num2*10 + ( Localcounter - '0') ;
			}
		}


		else if ( Localcounter=='+' || Localcounter=='-' || Localcounter=='*' || Localcounter=='/' )
		{
			LCD_voidWriteString(" ");
			LCD_voidWriteChar ( Localcounter ) ;
			LCD_voidWriteString(" ");
			Operator = Localcounter ;
		}
		else if ( Localcounter == '=')
		{

			switch ( Operator )
			{
			case '+' :
				Result = Num1 + Num2 ;
				break;

			case '-' :
				Result = Num1 - Num2 ;
				break;

			case '*' :
				Result = Num1 * Num2 ;
				break;

			case '/' :
				if ( Num2 == 0)
				{
					LCD_voidClearDisplay() ;
					LCD_voidGoTo_XY(0,3);
					LCD_voidWriteString( "Math Error" ) ;
					continue;
				}
				else
				{
					Result = Num1 / Num2 ;
				}
				break;

			default :
				LCD_voidClearDisplay() ;
				LCD_voidGoTo_XY(0,0);
				LCD_voidWriteString( "Invalid Operator"  ) ;

				continue;
			}
			LCD_voidGoTo_XY(1,0);
			LCD_voidWriteString("Res = ");
			LCD_voidWrite_u32Number ( Result ) ;
			Num1 = 0;
			Num2 = 0;
			Operator = 0;
		}
		else if ( Localcounter == '#')
		{
			LCD_voidClearDisplay() ;
			Num1 = 0;
			Num2 = 0;
			Operator = 0;
		}


	}





}
