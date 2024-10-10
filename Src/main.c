#include <stdint.h>
#include <stm32f446xx.h>
#include <stdio.h>
#include "main.h"
#include "gpio.h"
#include "usart.h"
#include "timer.h"


int main(void)
{
	GPIO_Init();
	USART2_Init();
	SYSTICK_Init();

	while(1){
		//for(uint32_t i = 0 ; i<100000; i++);
		SYSTICK_Delay(1000);
		GPIOA->ODR ^= 1<<5;
		printf("Hello\r\n");
	}
}
