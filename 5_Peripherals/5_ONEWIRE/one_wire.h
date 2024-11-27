/********************************************************************************
  * @file           : one_wire.h
  * @brief          : All function for use one wire
  *******************************************************************************/

//----------------- SPECIAL DEFINE ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ SPECIAL DEFINE -------------------------------------------------*/
#ifndef ONE_WIRE_H_
#define ONE_WIRE_H_

//----------------- INCLUDE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ INCLUDE --------------------------------------------------------*/
#include "gpio.h"
#include "timer.h"

//------------------ TYPE DEFINE ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ TYPE DEFINE ----------------------------------------------------*/
typedef struct {
	GPIO_TypeDef*    port;
    uint16_t         pin;
}ONEWIRE_PINOUT;

//----------------- PROTOTYPE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ PROTOTYPE ------------------------------------------------------*/
uint8_t ONEWIRE_Reset	(ONEWIRE_PINOUT oneWire_Pinout);

uint8_t ONEWIRE_ReadBit	(ONEWIRE_PINOUT oneWire_Pinout);
uint8_t ONEWIRE_ReadByte(ONEWIRE_PINOUT oneWire_Pinout);

void ONEWIRE_WriteBit0	(ONEWIRE_PINOUT oneWire_Pinout);
void ONEWIRE_WriteBit1	(ONEWIRE_PINOUT oneWire_Pinout);
void ONEWIRE_WriteByte	(ONEWIRE_PINOUT oneWire_Pinout, uint8_t data);

//----------------- END SPECIAL DEFINE ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ END SPECIAL DEFINE ---------------------------------------------*/
#endif
