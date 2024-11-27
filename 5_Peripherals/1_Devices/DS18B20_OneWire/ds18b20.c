/********************************************************************************
  * @file           : ds18b20.c
  * @brief          : Captor Humidity and temperature
  *******************************************************************************/

//----------------- INCLUDE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ INCLUDE --------------------------------------------------------*/
#include "ds18b20.h"

//----------------- GLOBAL CONSTANTS ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ GLOBAL CONSTANTS -----------------------------------------------*/
extern ONEWIRE_PINOUT	PINOUT;
uint8_t Flag = 0;

//----------------- GLOBAL FUNCTIONS DEFINITION +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ GLOBAL FUNCTIONS DEFINITION ------------------------------------*/
//----------------- DS18B20 INIT ---------------------------------------------------------------------------- DS18B20 INIT ---------------------------------------------------*/
/* @brief  Initialise the device PinOut and look if device respond.
 * @param1 [in]  GPIOX  Holds MCU GPIO parameters
 * @param2 [in]  pin	Pin value
 * @retval None */
void Ds18b20_Init(GPIO_TypeDef * GPIOX, uint8_t pin)
{
	PINOUT.port  = GPIOX;
	PINOUT.pin   = pin;
	Ds18b20_Is_Connected();
}

//----------------- DS18B20 IS CONNECTED -------------------------------------------------------------------- DS18B20 IS CONNECTED -------------------------------------------*/
/* @brief  Initialise the device PinOut and look if device respond (On Usart).
 * @retval [Out]  val  The connection value on the OneWire PinOut */
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

//----------------- DS18B20 SCRATCHPAD ---------------------------------------------------------------------- DS18B20 SCRATCHPAD ---------------------------------------------*/
/* @brief  Return the DS18B20 ScratchPad
 * @param1 [in/out]  Tab_val[9]  Array containing all the bytes of the ScratchPad
 * @retval None */
void Ds18b20_Scratchpad(uint8_t Tab_val[9])
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

//----------------- DS18B20 SET THRESHOLD ALARM ------------------------------------------------------------- DS18B20 SET THRESHOLD ALARM ------------------------------------*/
/* @brief  Set the high and low temperature threshold and displays the threshold value on the Usart
 * @param1 [in] high_threshold  the high temperature threshold
 * @param2 [in] low_threshold   the low temperature threshold
 * @retval None */
void Ds18b20_Set_Threshold_Alarm(uint8_t high_threshold, uint8_t low_threshold)
{
	uint8_t Tab_vals[9] ={0};

	/* Send the configuration*/
    ONEWIRE_Reset(PINOUT);
    ONEWIRE_WriteByte(PINOUT,0xCC);
    ONEWIRE_WriteByte(PINOUT,0x4E);
    ONEWIRE_WriteByte(PINOUT,high_threshold);
    ONEWIRE_WriteByte(PINOUT,low_threshold);
    ONEWIRE_WriteByte(PINOUT,0x7F);
    SYSTICK_Delay(10);

    /* Read the Scratchpad */
    ONEWIRE_Reset(PINOUT);
    ONEWIRE_WriteByte(PINOUT,0xCC);
    ONEWIRE_WriteByte(PINOUT,0xBE);
    for(int i = 0; i < 8; i++)
    {
    	Tab_vals[i] = ONEWIRE_ReadByte (PINOUT);
    }

    /* Load the configuration in ROM */
    ONEWIRE_Reset(PINOUT);
    ONEWIRE_WriteByte(PINOUT,0xCC);
    ONEWIRE_WriteByte(PINOUT,0x48);
    SYSTICK_Delay(10);

    printf("Alarm set TH = %d deg LH = %d deg \r\n",Tab_vals[2],Tab_vals[3]);
}

//----------------- DS18B20 REG THRESHOLD ALARM ------------------------------------------------------------- DS18B20 REG THRESHOLD ALARM ------------------------------------*/
/* @brief  Return the value of the threshold alarm register
 * @param1 [in/out]  Tab_val[9]  Array containing all the bytes value alarm
 * @retval None */
void Ds18b20_Reg_Threshold_Alarm(uint8_t Tab_val[9])
{
	ONEWIRE_Reset(PINOUT);
    ONEWIRE_WriteByte(PINOUT,0xEC);
    SYSTICK_Delay(100);

    for(int i = 0; i < 8; i++)
    {
    	Tab_val[i] = ONEWIRE_ReadByte (PINOUT);
    }
}

//----------------- DS18B20 DYSPLAY TEMP -------------------------------------------------------------------- DS18B20 DYSPLAY TEMP -------------------------------------------*/
/* @brief  Display the temperature on USART and return the temperature with out the comma
 * @retval the temperature with out the comma */
uint16_t Ds18b20_Dysplay_Temp (void)
{
	uint8_t  scratchpad_receive[9]= {0};
	uint16_t raw_temperature = 0;
	int16_t  temperature = 0;
	int16_t  be_comma  = 0;
	int16_t  af_comma  = 0;

	Ds18b20_Scratchpad( scratchpad_receive);
	raw_temperature = scratchpad_receive[1]<<8 | scratchpad_receive[0];
	temperature = raw_temperature * 1000 / 16;
	be_comma  = temperature / 1000;
	af_comma  = temperature % 1000;
	printf("temp = %d,%d deg \r\n",be_comma, af_comma);

	return temperature;
}

//----------------- DS18B20 DYSPLAY TEMP MIN ---------------------------------------------------------------- DS18B20 DYSPLAY TEMP MIN ---------------------------------------*/
/* @brief  Display the temperature on USART all the minute with the TIMER2
 * @retval None */
void Ds18b20_Dysplay_Temp_Min (void)
{
	if (Flag)
	{
		Flag = 0;
		Ds18b20_Dysplay_Temp();
	}
}

//----------------- DS18B20 DYSPLAY TEMP MIN ---------------------------------------------------------------- DS18B20 DYSPLAY TEMP MIN ---------------------------------------*/
/* @brief  Checks which alarm threshold is set and displays it
 * @param1 [in] high_threshold  the high temperature threshold
 * @param2 [in] low_threshold   the low temperature threshold
 * @retval None */
void Ds18b20_Is_Threshold_Alarm (uint8_t high_threshold, uint8_t low_threshold)
{
	uint8_t alarm_reg[9]= {0};
	uint16_t temperature = 0;

	temperature = Ds18b20_Dysplay_Temp();
	Ds18b20_Reg_Threshold_Alarm(alarm_reg);

	if (alarm_reg[0] == 254)
	{
		if (high_threshold*1000 < temperature)
		{
			printf("   \r\n");
			printf("la temp est sup a %d \r\n", high_threshold);
		}
		if (low_threshold*1000 > temperature)
		{
			printf("   \r\n");
			printf("la temp est inf a %d \r\n", low_threshold);
		}
	}
	SYSTICK_Delay(1000);
}

/* --- EOF ------------------------------------------------------------------ */
