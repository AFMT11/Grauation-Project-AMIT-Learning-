/*
 * UART.c
 *
 * Created: 6/25/2021 1:28:22 PM
 *  Author: ahmed
 */ 

#include "UART.h"

void UART_INIT(void)
{
	/*Set pin Directions*/
	/*pin_0 input*/
	Clear_Bit(DDRD, 0);
	/*pin_1 output*/
	Set_Bit(DDRD, 1);
	
	/* Transmitter/ Receiver Enable */
	UCSRnB = 0x18;
	
	/*Parity Bit Selection*/
	/*Data Size Selection*/
	/*Stop Bit Selection*/
	UCSRnC = (PARITY_MODE << 4) | (DATA_SIZE << 1) | (STOP_BIT << 3);
	
	/*Baud Rate Selection*/
	UBRRnL = BAUD_RATE;
	
	
}
void UART_Tx(Uint8 chr)
{
	//Unused Function 
}
void UART_Tx_String(Uint8* str)
{
	//Unused Function 
}
Uint8 UART_Rx(void)
{
	Uint8 received_data = 0;
	while(Get_Bit(UCSRnA, 7) == 0);
	received_data = UDRn;
	return received_data;
}