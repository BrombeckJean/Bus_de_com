/********************************************************************************
  * @file           : sx1272.h
  * @brief          : Lora transmitter
  *******************************************************************************/

//----------------- SPECIAL DEFINE ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ SPECIAL DEFINE -------------------------------------------------*/
#ifndef DEVICES_SX1272_SPI_SX1272_H_
#define DEVICES_SX1272_SPI_SX1272_H_

//------------------ INCLUDE -------------------------------------------------------------------------------- INCLUDE ----------------------------------------------------------*/
#include "spi.h"
#include "usart.h"
#include "ds18b20.h"

//----------------- PROTOTYPE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ PROTOTYPE ------------------------------------------------------*/
void Sx1272_Init(GPIO_TypeDef * GPIOX_nss, uint8_t pin_nss);
void Sx1272_Conf(void);
void Sx1272_Check_Conf(void);

void Sx1272_Is_Connected(void);

void Sx1272_Send(uint8_t* data, uint8_t size);
void Sx1272_Receive(void);

void Sx1272_Send_Temp(void);
void Sx1272_Receive_Temp(void);

#endif /* DEVICES_SX1272_SPI_SX1272_H_ */
