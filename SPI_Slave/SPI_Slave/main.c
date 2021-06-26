/*
 * SPI_Slave.c
 *
 * Created: 6/25/2021 9:07:03 PM
 * Author : ahmed
 */ 

#include "SPI.h"
#include "LCD.h"
#define F_CPU 16000000
#include <util/delay.h>

int main(void)
{
	/*variables used to transmit & receive data with SPI*/
	Uint8 trans_data = 1;
	Uint8 receive_data = 0;

	Uint8 i, j, k, h; //variables used in loops
	
	Uint8 error_check = 1; //variable to check if the password written is incorrect
	
	/*Strings to be displayed at the run time*/
	Uint8 password[] = "ahmed_atef";  //password of the system
	Uint8 password_message[] = "Enter Your Pass";  
	Uint8 wrong_password[] = "Wrong Password";
	Uint8 welocme_message0[] = "Welcome Home";
	Uint8 welocme_message1[] = "Mr. Ahmed";
	Uint8 error_message[] = "No such a LED or Actuator";
	Uint8 led0[] = "LED 0";
	Uint8 led1[] = "LED 1";
	Uint8 led2[] = "LED 2";
	
	DIO_SetPinVal(DIO_PORTA, DIO_PIN_3, DIO_PIN_OFF); //turning off the buzzer
	
	SPI_Slave_INIT();  //SPI slave initialization
	LCD_INT();         //LCD initialization

    /* Replace with your application code */
    while (1) 
    {
		/*the first stage of the code: checking of the password*/
		while (error_check > 0)     //if the variable error_check has a value more than 0,
		{                           //then continue in the loop until the entered password is correct                         
			error_check = 0;
			LCD_Clear();
			LCD_WriteSTRING(password_message);
			LCD_WriteCMD(Cursor_Begin_2st_Line); //Begin the cursor at the second line
			
			for (i = 0; i < 10; i++)             //stage of taking the code
			{
				receive_data = SPI_Transceiver(trans_data); //Transmit & receive the data from the Master
				LCD_WriteCHAR('*');
				for (j = 0; j < 2; j++)          //beep for every character you enter
				{
					DIO_TogglePin(DIO_PORTA, DIO_PIN_3);
					_delay_ms(50);
				}				
				if (receive_data != password[i]) //if there one or more than one character are wrong increase the variable error_check by 1
				{
					error_check++;
				}
			}
			
			if (error_check)  //if the password entered is wrong      
			{
				LCD_Clear();
				LCD_WriteSTRING(password_message);
				LCD_GoTo(1,0);
				LCD_WriteSTRING(wrong_password);
				for (k = 0; k < 6; k++)    //three beeps indicates the entered password is wrong
				{
					DIO_TogglePin(DIO_PORTA, DIO_PIN_3);
					_delay_ms(100);
				}
				_delay_ms(1000);
			}		
		}
		
		LCD_Clear();           //after entering the password right finally, show up the welcome message
		LCD_WriteSTRING(welocme_message0);
		LCD_GoTo(1,0);
		LCD_WriteSTRING(welocme_message1);
		
		while(1)       //checking for the entered character to do some response
		{
			receive_data = SPI_Transceiver(trans_data); //receive the data from the Master
			
			LCD_Clear();
			LCD_WriteCHAR(receive_data);      //Display the entered character on the screen
			
			if (receive_data == 'a')          //if the entered character is 'a' toggle LED 0,
			{                                 //and display the number of the LED on LCD
				DIO_TogglePin(DIO_PORTC, DIO_PIN_2);
				LCD_WriteCMD(Cursor_Begin_2st_Line);
				LCD_WriteSTRING(led0);				
			}
			else if (receive_data == 'b')     //if the entered character is 'b' toggle LED 1,
			{                                 //and display the number of the LED on LCD
				DIO_TogglePin(DIO_PORTC, DIO_PIN_7);
				LCD_WriteCMD(Cursor_Begin_2st_Line);
				LCD_WriteSTRING(led1);				
			}
			else if (receive_data == 'c')     //if the entered character is 'c' toggle LED 2,
			{                                 //and display the number of the LED on LCD
				DIO_TogglePin(DIO_PORTD, DIO_PIN_3);
				LCD_WriteCMD(Cursor_Begin_2st_Line);
				LCD_WriteSTRING(led2);				
			}
			else                              //if the entered character is not one the previous characters
			{
				LCD_WriteCMD(Cursor_Begin_2st_Line);
				LCD_WriteSTRING(error_message);      //display the error message
				_delay_ms(1000);
				
				for (h = 0; h < 9; h++)              //shift the display left to show the entire message
				{
					LCD_WriteCMD(Shift_Entire_Display_Left);
					LCD_GoTo(0,h+1);
					LCD_WriteCHAR(receive_data);
					_delay_ms(300);				
				}
			}		
		}
    }
}

