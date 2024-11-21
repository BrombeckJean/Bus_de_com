/********************************************************************************
  * @file           : ds18b20.h
  * @brief          : Captor Humidity and temperature
  *******************************************************************************/

//------------------ INCLUDE -------------------------------------------------------------------------------- INCLUDE ----------------------------------------------------------*/
#include "one_wire.h"
#include "usart.h"

//----------------- SPECIAL DEFINE ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ SPECIAL DEFINE -------------------------------------------------*/
#ifndef DEVICES_DS18B20_ONEWIRE_DS18B20_H_
#define DEVICES_DS18B20_ONEWIRE_DS18B20_H_

//----------------- PROTOTYPE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ PROTOTYPE ------------------------------------------------------*/
void Ds18b20_Init(GPIO_TypeDef * GPIOX, uint8_t pin);
uint8_t Ds18b20_Is_Connected(void);
void Ds18b20_Read_Temp(uint8_t Tab_val[9]);
uint16_t Ds18b20_affiche_temp (void);
void Ds18b20_affiche_temp_min (void);


/* Alarm */
void Ds18b20_Set_Seuil_Alarm(uint8_t seuil_haut, uint8_t seuil_bas);
void Ds18b20_Who_Seuil_Alarm(uint8_t Tab_val[9]);
void Ds18b20_is_alarmed (uint8_t seuil_haut, uint8_t seuil_bas);

//----------------- END SPECIAL DEFINE ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ END SPECIAL DEFINE ---------------------------------------------*/
#endif /* DEVICES_DS18B20_ONEWIRE_DS18B20_H_ */
