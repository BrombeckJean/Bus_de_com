/********************************************************************************
  * @file           : main.c
  * @brief          : Main function
  *******************************************************************************/

//----------------- INCLUDE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ INCLUDE --------------------------------------------------------*/
#include "stm32f446xx.h"
#include "main.h"

//----------------- GLOBAL VALUES +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ GLOBAL VALUES --------------------------------------------------*/
ONEWIRE_PINOUT	PINOUT;



/// envoyer sur teams avec oneWire_Nom.zip


#if ONE_WIRE > 0
int main(void)
{

#if TEST_3
	uint8_t TH = 25;
	uint8_t TL = 18;
#endif

	/* Peripherals initialisation */
	GPIO_Init();
	USART2_Init();
	SYSTICK_Init();
	DWT_Init();
	TIM2TICK_Init();
	Ds18b20_Init(GPIOA,1);

#if TEST_2
	Ds18b20_affiche_temp();
#endif

#if TEST_3
	Ds18b20_Set_Seuil_Alarm(TH,TL);
	Ds18b20_affiche_temp();
#endif

	while(1)
	{
		/* TEST 1 */
		#if TEST_1
			/*SYSTICK_Delay(1000);
			GPIOA->ODR ^= 1<<5;*/
			Ds18b20_Is_Connected();
		#endif

		/* TEST 2*/
		#if TEST_2
			Ds18b20_affiche_temp_min();
		#endif

		/* TEST 3*/
		#if TEST_3
			Ds18b20_is_alarmed (TH, TL);
		#endif
	}
}
#endif
