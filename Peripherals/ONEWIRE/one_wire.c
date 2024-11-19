/********************************************************************************
  * @file           : one_wire.c
  * @brief          : All function for use one wire
  *******************************************************************************/

//----------------- INCLUDE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ INCLUDE --------------------------------------------------------*/
#include "one_wire.h"

//----------------- ONEWIRE RESET --------------------------------------------------------------------------- ONEWIRE RESET --------------------------------------------------*/
uint8_t ONEWIRE_Reset(ONEWIRE_PINOUT oneWire_Pinout)
{
    uint8_t reset_status = 0;

 /* Niveau de tension bas */
    GPIO_ResetPin(oneWire_Pinout.port, oneWire_Pinout.pin);
    DWT_Delay(480);

 /* Niveau de tension haut */
    GPIO_SetPin(oneWire_Pinout.port, oneWire_Pinout.pin);
    DWT_Delay(70);

 /* Lecture du niveau */
    reset_status = GPIO_ReadPin(oneWire_Pinout.port, oneWire_Pinout.pin);
    DWT_Delay(410);

    return reset_status;
}

//----------------- ONEWIRE WRITE BIT 0 --------------------------------------------------------------------- ONEWIRE WRITE BIT 0 --------------------------------------------*/
void ONEWIRE_WriteBit0(ONEWIRE_PINOUT oneWire_Pinout)
{
 /* Niveau de tension bas */
    GPIO_ResetPin(oneWire_Pinout.port, oneWire_Pinout.pin);
    DWT_Delay(60);

 /* Niveau de tension haut */
    GPIO_SetPin(oneWire_Pinout.port, oneWire_Pinout.pin);
    DWT_Delay(10);
}

//----------------- ONEWIRE WRITE BIT 1 --------------------------------------------------------------------- ONEWIRE WRITE BIT 1 --------------------------------------------*/
void ONEWIRE_WriteBit1(ONEWIRE_PINOUT oneWire_Pinout)
{
 /* Niveau de tension bas */
    GPIO_ResetPin(oneWire_Pinout.port, oneWire_Pinout.pin);
    DWT_Delay(6);

 /* Niveau de tension haut */
    GPIO_SetPin(oneWire_Pinout.port, oneWire_Pinout.pin);
    DWT_Delay(64);
}

//----------------- ONEWIRE WRITE BYTE ---------------------------------------------------------------------- ONEWIRE WRITE BYTE ---------------------------------------------*/
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
uint8_t ONEWIRE_ReadBit(ONEWIRE_PINOUT oneWire_Pinout)
{
    uint8_t value = 0;

 /* Niveau de tension bas */
    GPIO_ResetPin(oneWire_Pinout.port, oneWire_Pinout.pin);
    DWT_Delay(6);

 /* Niveau de tension haut */
    GPIO_SetPin(oneWire_Pinout.port, oneWire_Pinout.pin);
    DWT_Delay(9);

 /* Niveau de tension bas */
    value = GPIO_ReadPin(oneWire_Pinout.port, oneWire_Pinout.pin);
    DWT_Delay(55);

    return value;
}

//----------------- ONEWIRE READ BYTE ----------------------------------------------------------------------- ONEWIRE READ BYTE ----------------------------------------------*/
uint8_t ONEWIRE_ReadByte(ONEWIRE_PINOUT oneWire_Pinout)
{
    uint8_t value = 0;

    for(int i = 0; i < 8; i++)
    {
         value = (ONEWIRE_ReadBit(oneWire_Pinout) | MASQUE(i)) + value;
    }
    return value;
}


