/********************************************************************************
 * @file           : gpio.c
 * @brief          : Configuration and initialisation of GPIO.
 ********************************************************************************/

//------------------ INCLUDE -------------------------------------------------------------------------------- INCLUDE --------------------------------------------------------*/
#include "gpio.h"
#include "main.h"

//------------------ DEFINE ----------------------------------------------------------------------- GLOBLAL STATEMENT ----------------------------------------------*/
void GPIO_Init(void){
	/* Clock Init */
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN;

	/* GPIO Init */
	GPIOA->MODER   |= OUTPUT_MODE <<10;						// PA5 Output LED
	GPIOC->MODER |= INPUT_MODE	<< 26;		// PC13 Input Push-Button

	/* One Wire */
	GPIOA->MODER  |= OUTPUT_MODE << GPIO_MODER_MODER1_Pos;		// PA1 alternate One wire
	GPIOA->OTYPER |= OUTPUT_OPEN_DRAIN << GPIO_OTYPER_OT1_Pos;	// PA1 open drain One wire
	GPIOA->PUPDR  |= PULL_UP << GPIO_PUPDR_PUPD1_Pos;			// PA1 push_pull One wire
}

void GPIO_SetPin(GPIO_TypeDef* GPIO, uint16_t pin){
	GPIO->ODR |= 1 << pin ;
}

void GPIO_ResetPin(GPIO_TypeDef* GPIO, uint16_t pin){
	GPIO->ODR &= ~(1 << pin) ;
}

void GPIO_TogglePin(GPIO_TypeDef* GPIO, uint16_t pin){
	GPIO->ODR ^= 1 << pin ;
}

uint16_t GPIO_ReadPin(GPIO_TypeDef* GPIO, uint16_t pin){
	if((GPIO->IDR & (1 << pin)) !=0)	return 1;
	else 								return 0;
}
