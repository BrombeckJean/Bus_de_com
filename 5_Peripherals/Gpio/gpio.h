/********************************************************************************
  * @file           : gpio.h
  * @brief          : Header for gpio.c file.
  *******************************************************************************/

//----------------- SPECIAL DEFINE ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ SPECIAL DEFINE -------------------------------------------------*/
#ifndef GPIO_H_
#define GPIO_H_

//----------------- INCLUDE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ INCLUDE --------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>
#include "stm32f446xx.h"
#include "util.h"

//----------------- PROTOTYPE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ PROTOTYPE ------------------------------------------------------*/
/* Settings */
void GPIO_Init(void);

/* Actions */
void GPIO_Set_Pin	(GPIO_TypeDef* GPIO, uint16_t pin);
void GPIO_Reset_Pin	(GPIO_TypeDef* GPIO, uint16_t pin);
void GPIO_Toggle_Pin	(GPIO_TypeDef* GPIO, uint16_t pin);

/* Displaying */
uint16_t GPIO_Read_Pin(GPIO_TypeDef* GPIO, uint16_t pin);

//----------------- END SPECIAL DEFINE ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ END SPECIAL DEFINE ---------------------------------------------*/
#endif /* GPIO_H_ */
