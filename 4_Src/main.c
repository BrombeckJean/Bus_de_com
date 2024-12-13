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
uint8_t push_button;

void ReadTemperature(void);

//----------------- MAIN ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ MAIN -----------------------------------------------------------*/
/* @brief  This function is the first function of the program
 * @retval None */
int main(void)
{
	/* Peripherals initialisation */
	FPU_Init();
	GPIO_Init();
	USART2_Init();
	SYSTICK_Init();		TIM2TICK_Init();	DWT_Init();

/********** ONE_WIRE *************/
#if (ONE_WIRE > 0)
	Ds18b20_Init(GPIOA,1);
#endif
#if (ONE_WIRE == 3)
	uint8_t TH = 25;
	uint8_t TL = 18;
	Ds18b20_Set_Threshold_Alarm(TH,TL);
#endif
#if (ONE_WIRE == 2 | (ONE_WIRE == 3) )
	Ds18b20_Dysplay_Temp();
#endif

/********** SPI *************/
#if (SPI > 0)
	SPI_Init();
	Sx1272_Init(GPIOB,6);
	Sx1272_Conf();
	Sx1272_Check_Conf();

#if TRANSMIT
	uint8_t buffTX[4] = {0xCA, 0xFE, 0xCA, 0xFE};
#endif
#endif

/********** I2C *************/
#if (I2C > 0)
	I2C_Init();
	Lis2dw12_Is_Connected();
	Lis2dw12_Conf();
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

		#if (SPI == 2)
			#if RECEIVE
				Sx1272_Receive();
			#endif

			#if TRANSMIT
				Sx1272_Send(buffTX,4);
				SYSTICK_Delay(5000);
			#endif
		#endif

		#if (SPI == 3)
			#if RECEIVE
				Sx1272_Receive_Temp();
			#endif

			#if TRANSMIT
				Sx1272_Send_Temp();
				SYSTICK_Delay(5000);
			#endif
		#endif

		#if (I2C == 1)
			Lis2dw12_Is_Connected();
		#endif

		#if (I2C == 2)
			Lis2dw12_Print_Acc();
		#endif

		#if (I2C == 3)
			if(push_button){
				push_button=0;
				printf("Button are push /!\\ \r\n");
				Lis2dw12_Print_Acc();
			}
		#endif
	}
return 0;
}
