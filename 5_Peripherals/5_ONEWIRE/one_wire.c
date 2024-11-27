/********************************************************************************
  * @file           : one_wire.c
  * @brief          : All function for use one wire
  *******************************************************************************/

//----------------- INCLUDE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ INCLUDE --------------------------------------------------------*/
#include "one_wire.h"

//----------------- ONEWIRE RESET --------------------------------------------------------------------------- ONEWIRE RESET --------------------------------------------------*/
/* @brief  Reset Process for the OneWire protocol
 * @param1 [in]  oneWire_Pinout  Structure contain the GPIO and the Pin used
 * @retval [out] reset_status 	 The value of the GPIO PIN used */
uint8_t ONEWIRE_Reset(ONEWIRE_PINOUT oneWire_Pinout)
{
    uint8_t reset_status = 0;

 /* Low voltage level*/
    GPIO_Reset_Pin(oneWire_Pinout.port, oneWire_Pinout.pin);
    DWT_Delay(480);

 /* High voltage level */
    GPIO_Set_Pin(oneWire_Pinout.port, oneWire_Pinout.pin);
    DWT_Delay(70);

 /* Level reading */
    reset_status = GPIO_Read_Pin(oneWire_Pinout.port, oneWire_Pinout.pin);
    DWT_Delay(410);

    return reset_status;
}

//----------------- ONEWIRE WRITE BIT 0 --------------------------------------------------------------------- ONEWIRE WRITE BIT 0 --------------------------------------------*/
/* @brief  Zero bit writing process for OneWire protocol
 * @param1 [in]  oneWire_Pinout  Structure contain the GPIO and the Pin used
 * @retval None */
void ONEWIRE_WriteBit0(ONEWIRE_PINOUT oneWire_Pinout)
{
 /* Low voltage level */
    GPIO_Reset_Pin(oneWire_Pinout.port, oneWire_Pinout.pin);
    DWT_Delay(60);

 /* High voltage level */
    GPIO_Set_Pin(oneWire_Pinout.port, oneWire_Pinout.pin);
    DWT_Delay(10);
}

//----------------- ONEWIRE WRITE BIT 1 --------------------------------------------------------------------- ONEWIRE WRITE BIT 1 --------------------------------------------*/
/* @brief  Bit writing process for OneWire protocol
 * @param1 [in]  oneWire_Pinout  Structure contain the GPIO and the Pin used
 * @retval None */
void ONEWIRE_WriteBit1(ONEWIRE_PINOUT oneWire_Pinout)
{
 /* Low voltage level */
    GPIO_Reset_Pin(oneWire_Pinout.port, oneWire_Pinout.pin);
    DWT_Delay(6);

 /* High voltage level */
    GPIO_Set_Pin(oneWire_Pinout.port, oneWire_Pinout.pin);
    DWT_Delay(64);
}

//----------------- ONEWIRE WRITE BYTE ---------------------------------------------------------------------- ONEWIRE WRITE BYTE ---------------------------------------------*/
/* @brief  Write a byte in OneWire
 * @param1 [in]  oneWire_Pinout  Structure contain the GPIO and the Pin used
 * @param2 [in]  data			 Data you want transmit
 * @retval None */
void ONEWIRE_WriteByte(ONEWIRE_PINOUT oneWire_Pinout, uint8_t data)
{
    for(int i = 0; i < 8; i++)
    {
        if ((data >> i) & 1)
        {
            ONEWIRE_WriteBit1(oneWire_Pinout);
        } else {
            ONEWIRE_WriteBit0(oneWire_Pinout);
        }
    }
}

//----------------- ONEWIRE READ BIT ------------------------------------------------------------------------ ONEWIRE READ BIT -----------------------------------------------*/
/* @brief  Bit reading process for OneWire protocol
 * @param1 [in]  oneWire_Pinout  Structure contain the GPIO and the Pin used
 * @retval [out] data			 bit received */
uint8_t ONEWIRE_ReadBit(ONEWIRE_PINOUT oneWire_Pinout)
{
    uint8_t data = 0;

 /* Low voltage level */
    GPIO_Reset_Pin(oneWire_Pinout.port, oneWire_Pinout.pin);
    DWT_Delay(6);

 /* High voltage level */
    GPIO_Set_Pin(oneWire_Pinout.port, oneWire_Pinout.pin);
    DWT_Delay(9);

    /* Level reading */
    data = GPIO_Read_Pin(oneWire_Pinout.port, oneWire_Pinout.pin);
    DWT_Delay(55);

    return data;
}

//----------------- ONEWIRE READ BYTE ----------------------------------------------------------------------- ONEWIRE READ BYTE ----------------------------------------------*/
/* @brief  Read a byte in OneWire
 * @param1 [in]  oneWire_Pinout  Structure contain the GPIO and the Pin used
 * @retval [out] data			 Byte received */
uint8_t ONEWIRE_ReadByte(ONEWIRE_PINOUT oneWire_Pinout)
{
    uint8_t data = 0;

    for(int i = 0; i < 8; i++)
    {
    	data |= (ONEWIRE_ReadBit(oneWire_Pinout)<<i);
    }
    return data;
}


