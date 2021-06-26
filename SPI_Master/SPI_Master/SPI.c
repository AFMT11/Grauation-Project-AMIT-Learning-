/*
 * SPI.c
 *
 * Created: 6/25/2021 5:50:19 PM
 *  Author: ahmed
 */ 

#include "SPI.h"

void SPI_Master0_INIT(Uint8 port, Uint8 pin)
{
	#if DEVICE_MODE == MASTER
	
	/*Set Pins Direction*/
	
	/*SS1 pin: Output*/
	DIO_SetPinDir(port, pin, DIO_PIN_OUT);
	/*MOSI pin: Output*/
	DIO_SetPinDir(DIO_PORTB, DIO_PIN_3, DIO_PIN_OUT);
	/*MISO pin: Input*/
	DIO_SetPinDir(DIO_PORTB, DIO_PIN_4, DIO_PIN_IN);
	/*SCK pin: Output*/
	DIO_SetPinDir(DIO_PORTB, DIO_PIN_5, DIO_PIN_OUT);
	
	/*Device Mode Selection*/
	/*SCK Source Selection*/
	SPCR = 	0x00;
	SPCR = SCK_SOURCE | (DEVICE_MODE << 4); 
	SPSR = SCK_CASE;
	
	/*SPI Enable*/
	Set_Bit(SPCR, 6);	
	
#endif			
}
void SPI_Slave_INIT(void)
{
	#if DEVICE_MODE == SLAVE
	
	/*Set Pins Direction*/
	
	/*SS pin: Input*/
	DIO_SetPinDir(DIO_PORTB, DIO_PIN_4, DIO_PIN_IN);
	/*MOSI pin: Input*/
	DIO_SetPinDir(DIO_PORTB, DIO_PIN_5, DIO_PIN_IN);
	/*MISO pin: Output*/
	DIO_SetPinDir(DIO_PORTB, DIO_PIN_6, DIO_PIN_OUT);
	/*SCK pin: Input*/
	DIO_SetPinDir(DIO_PORTB, DIO_PIN_7, DIO_PIN_IN);
	
	/*Device Mode Selection*/
	SPCR = 	0x00;
	SPCR = DEVICE_MODE << 4;
	
	/*SPI Enable*/
	Set_Bit(SPCR, 6);	
#endif
}
void SPI_INIT_Com(Uint8 port, Uint8 pin)
{
	DIO_SetPinVal(port, pin, DIO_PIN_OFF);
}
void SPI_END_Com(Uint8 port, Uint8 pin)
{
	DIO_SetPinVal(port, pin, DIO_PIN_ON);
}
Uint8 SPI_Transceiver(Uint8 data)
{
	SPDR = data;
	while(Get_Bit(SPSR, 7) == 0);
	return SPDR;
}