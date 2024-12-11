/********************************************************************************
 * @file           : gpio.c
 * @brief          : Configuration and settings values of GPIO.
 ********************************************************************************/

//----------------- INCLUDE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ INCLUDE --------------------------------------------------------*/
#include "gpio.h"
#include "Option_comp.h"

//----------------- GLOBAL FUNCTIONS DEFINITION +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ GLOBAL FUNCTIONS DEFINITION ------------------------------------*/
//----------------- GPIO INIT ------------------------------------------------------------------------------- GPIO INIT ------------------------------------------------------*/
/* @brief  Initialise all PinOut
 * @retval None */
void GPIO_Init(void){

	/* Led Gpio Pin */
	//RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; /* Clock activation */
	//GPIOA->MODER   |= OUTPUT_MODE <<10;	 /* PA5 Output LED */

	/* Board Button Gpio Pin */
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; /* Clock activation */
	GPIOC->MODER |= INPUT_MODE	<< 26;   /* PC13 Input Push-Button */

#if (ONE_WIRE > 0)
	/* One Wire Gpio Pin */
	RCC->AHB1ENR  |= RCC_AHB1ENR_GPIOAEN; 						/* Clock activation */
	GPIOA->MODER  |= OUTPUT_MODE << GPIO_MODER_MODER1_Pos;		/* PA1 Output One wire */
	GPIOA->OTYPER |= OUTPUT_OPEN_DRAIN << GPIO_OTYPER_OT1_Pos;	/* PA1 open drain One wire */
	GPIOA->PUPDR  |= PULL_UP << GPIO_PUPDR_PUPD1_Pos;			/* PA1 push_pull One wire */
#endif

#if (SPI > 0)
	/* SPI pin Clock Init */
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN;
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	/* Alternate functions */
	GPIOA->MODER |= 1 << 11;  // PA5 11
	GPIOA->MODER |= 1 << 13;  // PA6 13
	GPIOA->MODER |= 1 << 15;  // PA7 15
	GPIOB->MODER |= 1 << 12;  // PB6 12

	/* HIGH Speed mode */
	GPIOA->OSPEEDR |= 3<<10;  // PA5
	GPIOA->OSPEEDR |= 3<<12;  // PA6
	GPIOA->OSPEEDR |= 3<<14;  // PA7

	/* AF5(SPI1) */
	GPIOA->AFR[0] |= 5<<20;  // PA5
	GPIOA->AFR[0] |= 5<<24;  // PA6
	GPIOA->AFR[0] |= 5<<28;  // PA7
	RCC->APB2ENR |= (1<<12);  // Enable SPI1 CLock

	/*SPI1->CR1 |= 1<<6;
	SPI1->CR1 |= 4<<3;
	SPI1->CR1 |= (1<<8) | (1<<9);   // SSM=1, SSi=1 -> Software Slave Management
	SPI1->CR1 |= (1<<2);  			// Master Mode*/
#endif
}

//----------------- GPIO SET PIN ---------------------------------------------------------------------------- GPIO SETP IN ---------------------------------------------------*/
/* @brief  Set the GPIO pin you want
 * @param1 [in]  GPIOX  Holds MCU GPIO parameters
 * @param2 [in]  pin	Pin value
 * @retval None */
void GPIO_Set_Pin(GPIO_TypeDef* GPIO, uint16_t pin){
	GPIO->ODR |= 1 << pin ;
}

//----------------- GPIO RESET PIN -------------------------------------------------------------------------- GPIO RESET PIN -------------------------------------------------*/
/* @brief  Reset the GPIO pin you want
 * @param1 [in]  GPIOX  Holds MCU GPIO parameters
 * @param2 [in]  pin	Pin value
 * @retval None */
void GPIO_Reset_Pin(GPIO_TypeDef* GPIO, uint16_t pin){
	GPIO->ODR &= ~(1 << pin) ;
}

//----------------- GPIO TOGGLE PIN ------------------------------------------------------------------------- GPIO TOGGLE PIN ------------------------------------------------*/
/* @brief  Toggle the GPIO pin you want
 * @param1 [in]  GPIOX  Holds MCU GPIO parameters
 * @param2 [in]  pin	Pin value
 * @retval None */
void GPIO_Toggle_Pin(GPIO_TypeDef* GPIO, uint16_t pin){
	GPIO->ODR ^= 1 << pin ;
}

//----------------- GPIO READ PIN --------------------------------------------------------------------------- GPIO READ PIN --------------------------------------------------*/
/* @brief  Read the value of the GPIO pin you want
 * @param1 [in]  GPIOX  Holds MCU GPIO parameters
 * @param2 [in]  pin	Pin value
 * @retval None */
uint16_t GPIO_Read_Pin(GPIO_TypeDef* GPIO, uint16_t pin){
	if((GPIO->IDR & (1 << pin)) !=0)	return 1;
	else 								return 0;
}
