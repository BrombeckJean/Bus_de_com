/********************************************************************************
  * @file           : main.c
  * @brief          : Main function
  *******************************************************************************/

//----------------- INCLUDE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ INCLUDE --------------------------------------------------------*/
#include "stm32f446xx.h"
#include "main.h"

//----------------- GLOBAL VALUES +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ GLOBAL VALUES --------------------------------------------------*/
ONEWIRE_PINOUT	PINOUT;

//----------------- MAIN ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ MAIN -----------------------------------------------------------*/
int main(void)
{

#if (ONE_WIRE == 3)
	uint8_t TH = 25;
	uint8_t TL = 18;
#endif

	/* Peripherals initialisation */
	GPIO_Init();
	USART2_Init();
	SYSTICK_Init();
	DWT_Init();
	TIM2TICK_Init();
#if (ONE_WIRE > 0)
	Ds18b20_Init(GPIOA,1);
#endif
#if (ONE_WIRE == 3)
	Ds18b20_Set_Seuil_Alarm(TH,TL);
#endif
#if (ONE_WIRE == 2 | (ONE_WIRE == 3) )
	Ds18b20_affiche_temp();
#endif


	while(1)
	{
		/*SYSTICK_Delay(1000);
		GPIOA->ODR ^= 1<<5;*/

		#if (ONE_WIRE == 1)
		/* TEST 1 */
			Ds18b20_Is_Connected();
		#endif

		/* TEST 2*/
		#if (ONE_WIRE == 2)
			Ds18b20_affiche_temp_min();
		#endif

		/* TEST 3*/
		#if (ONE_WIRE == 3)
			Ds18b20_is_alarmed (TH, TL);
		#endif
	}
}
