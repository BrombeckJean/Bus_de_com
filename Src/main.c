#include <stm32f446xx.h>
#include "main.h"

ONEWIRE_PINOUT	PINOUT;

int main(void)
{
	/* Peripherals initialisation */
	GPIO_Init();
	USART2_Init();
	SYSTICK_Init();
	DWT_Init();
	Ds18b20_Init(GPIOA,1);

	while(1){

		//for(uint32_t i = 0 ; i<100000; i++);
		SYSTICK_Delay(1000);
		GPIOA->ODR ^= 1<<5;
		Ds18b20_Is_Connected();
	}
}
