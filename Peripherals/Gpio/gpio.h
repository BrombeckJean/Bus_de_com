/********************************************************************************
  * @file           : gpio.h
  * @brief          : Header for gpio.c file.
  *******************************************************************************/

//------------------ SPECIAL DEFINE ------------------------------------------------------------------------- SPECIAL DEFINE ---------------------------------------------------*/
#ifndef GPIO_H_
#define GPIO_H_

//------------------ INCLUDE -------------------------------------------------------------------------------- INCLUDE ----------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>
#include <stm32f446xx.h>
#include "util.h"

//------------------ PROTOTYPE ------------------------------------------------------------------------------ PROTOTYPE --------------------------------------------------------*/
void GPIO_Init(void);
void GPIO_SetPin	(GPIO_TypeDef* GPIO, uint16_t pin);
void GPIO_ResetPin	(GPIO_TypeDef* GPIO, uint16_t pin);
void GPIO_TogglePin	(GPIO_TypeDef* GPIO, uint16_t pin);
uint16_t GPIO_ReadPin(GPIO_TypeDef* GPIO, uint16_t pin);

//------------------ END SPECIAL DEFINE --------------------------------------------------------------------- END SPECIAL DEFINE -----------------------------------------------*/
#endif /* GPIO_H_ */
