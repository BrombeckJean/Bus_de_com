/********************************************************************************
 * @file           : gpio.c
 * @brief          : Configuration and settings values of GPIO.
 ********************************************************************************/

//----------------- INCLUDE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ INCLUDE --------------------------------------------------------*/
#include "gpio.h"
#include "Option_comp.h"

//----------------- LOCAL DEFINE ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ LOCAL DEFINE ---------------------------------------------------*/
/* Values MODER Register */
#define INPUT_MODE 	0
#define OUTPUT_MODE	1
#define ALT_MODE 	2
#define ANALOG_MODE	3

/* Values OTYPER Register */
#define OUTPUT_PUSH_PULL 	0
#define OUTPUT_OPEN_DRAIN	1

/* Values PUPDR Register */
#define NO_PULL 	0
#define PULL_UP		1
#define PULL_DOWN 	2

//----------------- GPIO INIT +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ GPIO INIT ------------------------------------------------------*/
/* @brief  Reads the FLASH at the specified address to the given buffer.
 * @param1 [in/out] gpio  Holds MCU gpio parameters
 * @param2 [in]     value Initial MCU pit value
 * @param3 [in/out] irq   Pointer to IRQ data context.
 * @retval None */
void GPIO_Init(void){
	/* Clock Init */
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN;

	/* Led Gpio Pin */
	GPIOA->MODER   |= OUTPUT_MODE <<10;						// PA5 Output LED

	/* Board Button Gpio Pin */
	GPIOC->MODER |= INPUT_MODE	<< 26;						// PC13 Input Push-Button

	/* One Wire Gpio Pin */
	RCC->AHB1ENR  |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN; /* Clock activation */
	GPIOA->MODER  |= OUTPUT_MODE << GPIO_MODER_MODER1_Pos;		/* PA1 alternate One wire */
	GPIOA->OTYPER |= OUTPUT_OPEN_DRAIN << GPIO_OTYPER_OT1_Pos;	/* PA1 open drain One wire */
	GPIOA->PUPDR  |= PULL_UP << GPIO_PUPDR_PUPD1_Pos;			/* PA1 push_pull One wire */
}

//----------------- GPIO SET PIN ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ GPIO SETP IN ---------------------------------------------------*/
void GPIO_Set_Pin(GPIO_TypeDef* GPIO, uint16_t pin){
	GPIO->ODR |= 1 << pin ;
}

//----------------- GPIO RESET PIN ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ GPIO RESET PIN -------------------------------------------------*/
void GPIO_Reset_Pin(GPIO_TypeDef* GPIO, uint16_t pin){
	GPIO->ODR &= ~(1 << pin) ;
}

//----------------- GPIO TOGGLE PIN +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ GPIO TOGGLE PIN ------------------------------------------------*/
void GPIO_Toggle_Pin(GPIO_TypeDef* GPIO, uint16_t pin){
	GPIO->ODR ^= 1 << pin ;
}

//----------------- GPIO READ PIN +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ GPIO READ PIN --------------------------------------------------*/
uint16_t GPIO_Read_Pin(GPIO_TypeDef* GPIO, uint16_t pin){
	if((GPIO->IDR & (1 << pin)) !=0)	return 1;
	else 								return 0;
}
