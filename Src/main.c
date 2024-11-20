#include <stm32f446xx.h>
#include "main.h"

ONEWIRE_PINOUT	PINOUT;
uint8_t Bytes_recive[9]= {0};
uint8_t Flag = 0;

#define TEST_1 0
#define TEST_2 1

int main(void)
{
	/* Peripherals initialisation */
	GPIO_Init();
	USART2_Init();
	SYSTICK_Init();
	DWT_Init();
	TIM2TICK_Init();
	Ds18b20_Init(GPIOA,1);

	uint16_t temperature_brut = 0;
	int16_t  temperature = 0;
	int16_t  Av_virgule  = 0;
	int16_t  Ap_virgule  = 0;

	Flag = 0;
	Ds18b20_Read_Temp( Bytes_recive);
	temperature_brut = Bytes_recive[1]<<8 | Bytes_recive[0];
	temperature = temperature_brut*1000/16;
	Av_virgule  = temperature / 1000;
	Ap_virgule  = temperature % 1000;
	printf("temp = %d,%d deg \r\n",Av_virgule, Ap_virgule);

	while(1)
	{
		/* TEST 1 */
		#if TEST_1
			SYSTICK_Delay(1000);
			GPIOA->ODR ^= 1<<5;
			Ds18b20_Is_Connected();
		#endif

		/* TEST 1 */
		#if TEST_2


			if (Flag)
			{
				Flag = 0;
				Ds18b20_Read_Temp( Bytes_recive);
				temperature_brut = Bytes_recive[1]<<8 | Bytes_recive[0];
				temperature = temperature_brut*1000/16;
				Av_virgule  = temperature / 1000;
				Ap_virgule  = temperature % 1000;
				printf("temp = %d,%d deg \r\n",Av_virgule, Ap_virgule);
			}
		#endif
	}
}
