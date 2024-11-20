/********************************************************************************
  * @file           : ds18b20.c
  * @brief          : Captor Humidity and temperature
  *******************************************************************************/

//----------------- INCLUDE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ INCLUDE --------------------------------------------------------*/
#include "ds18b20.h"

extern ONEWIRE_PINOUT	PINOUT;

//----------------- DS18B20 INIT ------------------------------------------------------------------------------- DS18B20 INIT ------------------------------------------------------*/
void Ds18b20_Init(GPIO_TypeDef * GPIOX, uint8_t pin)
{
	PINOUT.port  = GPIOX;
	PINOUT.pin   = pin;
	Ds18b20_Is_Connected();
}

//----------------- DS18B20 IS CONNECTED ------------------------------------------------------------------------------- DS18B20 IS CONNECTED ------------------------------------------------------*/
uint8_t Ds18b20_Is_Connected(void)
{
	uint8_t val = 1;

    val = ONEWIRE_Reset(PINOUT);

    if (val == 0)
    {
    	printf("The device are connected\r\n");
    }
    else
    {
    	printf("No device\r\n");
    }

    return val;
}

//----------------- DS18B20 READ TEMP ------------------------------------------------------------------------------- DS18B20 READ TEMP ------------------------------------------------------*/
void Ds18b20_Read_Temp(uint8_t Tab_val[9])
{
    ONEWIRE_Reset(PINOUT);
    ONEWIRE_WriteByte(PINOUT,0xCC);
    ONEWIRE_WriteByte(PINOUT,0x44);
    DWT_Delay(10);

    ONEWIRE_Reset(PINOUT);
    ONEWIRE_WriteByte(PINOUT,0xCC);
    ONEWIRE_WriteByte(PINOUT,0xBE);
    for(int i = 0; i < 8; i++)
    {
    	Tab_val[i] = ONEWIRE_ReadByte (PINOUT);
    }
}

/* --- EOF ------------------------------------------------------------------ */