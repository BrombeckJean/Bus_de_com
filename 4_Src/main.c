/********************************************************************************
  * @file           : main.c
  * @brief          : Main function
  *******************************************************************************/

//----------------- INCLUDE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ INCLUDE --------------------------------------------------------*/
#include "stm32f446xx.h"
#include "main.h"

//----------------- GLOBAL VALUES +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ GLOBAL VALUES --------------------------------------------------*/
ONEWIRE_PINOUT	PINOUT_1WIRE;
SPI_PINOUT	PINOUT_SPI;

//----------------- MAIN ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ MAIN -----------------------------------------------------------*/
/* @brief  This function is the first function of the program
 * @retval None */
int main(void)
{
#if (ONE_WIRE == 3)
	uint8_t TH = 25;
	uint8_t TL = 18;
#endif

	/* Peripherals initialisation */
	GPIO_Init();
	USART2_Init();
	SYSTICK_Init();		TIM2TICK_Init();	DWT_Init();

#if (ONE_WIRE > 0)
	Ds18b20_Init(GPIOA,1);
#endif
#if (ONE_WIRE == 3)
	Ds18b20_Set_Threshold_Alarm(TH,TL);
#endif
#if (ONE_WIRE == 2 | (ONE_WIRE == 3) )
	Ds18b20_Dysplay_Temp();
#endif

#if (SPI > 0)
	Sx1272_Init(GPIOB,6);
	Sx1272_Conf();
	Sx1272_Check_Conf();
#endif

	while(1)
	{
		/*SYSTICK_Delay(1000);
		GPIOA->ODR ^= 1<<5;*/

		#if (ONE_WIRE == 1)
		 /* TEST 1 */
			Ds18b20_Is_Connected();
		#endif

		#if (ONE_WIRE == 2)
		 /* TEST 2*/
			Ds18b20_Dysplay_Temp_Min();
		#endif

		#if (ONE_WIRE == 3)
		 /* TEST 3*/
			Ds18b20_Is_Threshold_Alarm (TH, TL);
		#endif

		#if (SPI == 1)
		 /* TEST 1 */
			Sx1272_Is_Connected();
		#endif

		#if RECEIVE
			Sx1272_Receive();
		#endif

		#if TRANSMIT
			Sx1272_Send();
			SYSTICK_Delay(1000);
		#endif
	}
return 0;
}

