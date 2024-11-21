/********************************************************************************
  * @file           : ds18b20.c
  * @brief          : Captor Humidity and temperature
  *******************************************************************************/

//----------------- INCLUDE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ INCLUDE --------------------------------------------------------*/
#include "ds18b20.h"

extern ONEWIRE_PINOUT	PINOUT;
uint8_t Flag = 0;

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
    SYSTICK_Delay(10);

    ONEWIRE_Reset(PINOUT);
    ONEWIRE_WriteByte(PINOUT,0xCC);
    ONEWIRE_WriteByte(PINOUT,0xBE);
    for(int i = 0; i < 8; i++)
    {
    	Tab_val[i] = ONEWIRE_ReadByte (PINOUT);
    }
}

//----------------- DS18B20 READ TEMP ------------------------------------------------------------------------------- DS18B20 READ TEMP ------------------------------------------------------*/
void Ds18b20_Set_Seuil_Alarm(uint8_t seuil_haut, uint8_t seuil_bas)
{
	uint8_t Tab_vals[9] ={0};
    ONEWIRE_Reset(PINOUT);
    ONEWIRE_WriteByte(PINOUT,0xCC);
    ONEWIRE_WriteByte(PINOUT,0x4E);
    ONEWIRE_WriteByte(PINOUT,seuil_haut);
    ONEWIRE_WriteByte(PINOUT,seuil_bas);
    ONEWIRE_WriteByte(PINOUT,0x7F);
    SYSTICK_Delay(10);

    ONEWIRE_Reset(PINOUT);
    ONEWIRE_WriteByte(PINOUT,0xCC);
    ONEWIRE_WriteByte(PINOUT,0xBE);
    for(int i = 0; i < 8; i++)
    {
    	Tab_vals[i] = ONEWIRE_ReadByte (PINOUT);
    }

    ONEWIRE_Reset(PINOUT);
    ONEWIRE_WriteByte(PINOUT,0xCC);
    ONEWIRE_WriteByte(PINOUT,0x48);
    SYSTICK_Delay(10);

    printf("Alarm set TH = %d deg LH = %d deg \r\n",Tab_vals[2],Tab_vals[3]);

}

//----------------- DS18B20 READ TEMP ------------------------------------------------------------------------------- DS18B20 READ TEMP ------------------------------------------------------*/
void Ds18b20_Who_Seuil_Alarm(uint8_t Tab_val[9])
{
	ONEWIRE_Reset(PINOUT);
    ONEWIRE_WriteByte(PINOUT,0xEC);
    SYSTICK_Delay(100);

    for(int i = 0; i < 8; i++)
    {
    	Tab_val[i] = ONEWIRE_ReadByte (PINOUT);
    }
}

uint16_t Ds18b20_affiche_temp (void)
{
	uint8_t Bytes_recive[9]= {0};
	uint16_t temperature_brut = 0;
	int16_t  temperature = 0;
	int16_t  Av_virgule  = 0;
	int16_t  Ap_virgule  = 0;

	Ds18b20_Read_Temp( Bytes_recive);
	temperature_brut = Bytes_recive[1]<<8 | Bytes_recive[0];
	temperature = temperature_brut*1000/16;
	Av_virgule  = temperature / 1000;
	Ap_virgule  = temperature % 1000;
	printf("temp = %d,%d deg \r\n",Av_virgule, Ap_virgule);

	return temperature;
}

void Ds18b20_affiche_temp_min (void)
{
	if (Flag)
	{
		Flag = 0;
		Ds18b20_affiche_temp();
	}
}

void Ds18b20_is_alarmed (uint8_t seuil_haut, uint8_t seuil_bas)
{
	uint8_t Tab_alarm[9]= {0};
	uint16_t temperature = 0;

	temperature = Ds18b20_affiche_temp();
	Ds18b20_Who_Seuil_Alarm(Tab_alarm);

	if (Tab_alarm[0] == 254)
	{
		if (seuil_haut*1000 < temperature)
		{
			printf("   \r\n");
			printf("la temp est sup a %d \r\n", seuil_haut);
		}
		if (seuil_bas*1000 > temperature)
		{
			printf("   \r\n");
			printf("la temp est inf a %d \r\n", seuil_bas);
		}
	}
	SYSTICK_Delay(1000);
}

/* --- EOF ------------------------------------------------------------------ */
