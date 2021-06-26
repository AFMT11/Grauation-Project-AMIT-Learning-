/*
 * SPI.h
 *
 * Created: 6/25/2021 5:50:03 PM
 *  Author: ahmed
 */ 


#ifndef SPI_H_
#define SPI_H_

#include "SPI_CFG.h"
/*SCK Sources*/
#define Fosc_4          0
#define Fosc_16         1
#define Fosc_64         2
#define Fosc_128        3

/*SCK CASES*/
#define NOT_Doubled     0
#define Doubled         1
/*Device Modes*/
#define SLAVE           0
#define MASTER          1

void SPI_Master0_INIT(Uint8 port, Uint8 pin);
void SPI_Slave_INIT(void);

void SPI_INIT_Com(Uint8 port, Uint8 pin);
void SPI_END_Com(Uint8 port, Uint8 pin);

Uint8 SPI_Transceiver(Uint8 data);





#endif /* SPI_H_ */