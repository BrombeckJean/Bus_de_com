/********************************************************************************
  * @file           : ds18b20.h
  * @brief          : Captor Humidity and temperature
  *******************************************************************************/
//----------------- SPECIAL DEFINE ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ SPECIAL DEFINE -------------------------------------------------*/
#ifndef DEVICES_DS18B20_ONEWIRE_DS18B20_H_
#define DEVICES_DS18B20_ONEWIRE_DS18B20_H_

//------------------ INCLUDE -------------------------------------------------------------------------------- INCLUDE ----------------------------------------------------------*/
#include "one_wire.h"
#include "usart.h"

//----------------- PROTOTYPE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ PROTOTYPE ------------------------------------------------------*/
void Ds18b20_Init(GPIO_TypeDef * GPIOX, uint8_t pin);
uint8_t Ds18b20_Is_Connected(void);
void Ds18b20_Scratchpad(uint8_t Tab_val[9]);
uint16_t Ds18b20_Dysplay_Temp (void);
void Ds18b20_Dysplay_Temp_Min (void);


/* Alarm */
void Ds18b20_Set_Threshold_Alarm(uint8_t high_threshold, uint8_t low_threshold);
void Ds18b20_Reg_Threshold_Alarm(uint8_t Tab_val[9]);
void Ds18b20_Is_Threshold_Alarm (uint8_t high_threshold, uint8_t low_threshold);

//----------------- END SPECIAL DEFINE ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ END SPECIAL DEFINE ---------------------------------------------*/
#endif /* DEVICES_DS18B20_ONEWIRE_DS18B20_H_ */
