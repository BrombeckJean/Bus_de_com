/********************************************************************************
  * @file           : usart.h
  * @brief          : All function for use Usart
  *******************************************************************************/
#include <stdint.h>
#include <stdio.h>

//----------------- SPECIAL DEFINE ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ SPECIAL DEFINE -------------------------------------------------*/
#ifndef USART_H_
#define USART_H_

//----------------- PROTOTYPE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ PROTOTYPE ------------------------------------------------------*/
void USART2_Init(void);
void USART2_TransmitChar(uint8_t data);
uint8_t USART2_ReceiveChar(void);

//----------------- END SPECIAL DEFINE ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ END SPECIAL DEFINE ---------------------------------------------*/
#endif