/*
 * SPI_Master.c
 *
 * Created: 6/25/2021 8:22:55 PM
 * Author : ahmed
 */ 

#include "SPI.h"
#include "UART.h"
#define F_CPU 16000000
#include <util/delay.h>

int main(void)
{
	/*variables used to transmit & receive data with SPI*/
	Uint8 receive_data = 0;
	Uint8 uart_receive = 0;
	
	SPI_Master0_INIT(DIO_PORTB, DIO_PIN_2);   //SPI Master initialization
	SPI_INIT_Com(DIO_PORTB, DIO_PIN_2);       //SPI initiate the communication
	UART_INIT();                              //UART initialization
	
	_delay_ms(1000);                          //Delay for 1 s wait for other devices to be settled up.

    /* Replace with your application code */
    while (1) 
    {
		uart_receive = UART_Rx();        //receive the data from Blue_tooth module
		receive_data = SPI_Transceiver(uart_receive);     //Transmit & receive the data from the Slave
		_delay_ms(50);      //Delay for 50 ms
    }
}

