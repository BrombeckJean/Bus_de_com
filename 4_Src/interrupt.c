/********************************************************************************
  * @file           : interrupt.c
  * @brief          : All interrupt function
  *******************************************************************************/

//----------------- INFO +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ INFO ------------------------------------------------*/
/*  //////////////// HOW TO SETUP INTERUPT ? ///////////
 *  1. Activate the NVIC IT :  NVIC_EnableIRQ().
 *  2. Define the Event that generate IT : GPIO Rising Edge, Timer Update, USART RX not empty...
 *  3. Write the corresponding ISR (Interrupt Sub-Routine) code. Do not forget to reset IT Flag. */

///////////////         EXTI             //////////
/*    When using EXTI, to define the Event that generate IT (2), we need :
 * a. Enable SYSCFG peripheral clock.
 * b. Select the right PORT connected to EXTIx : SYSCFR->EXTICR.
 * c. Unmask IT on EXTIx : EXTI->IMR.
 * d. Select Rising or falling trigger edge :  EXTI->RTSR or EXTI->FTSR.*/

//----------------- INCLUDE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ INCLUDE --------------------------------------------------------*/
#include <stdint.h>
#include "stm32f446xx.h"
#include "interrupt.h"

//----------------- EXTERN GLOBAL VALUES ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ EXTERN GLOBAL VALUES -------------------------------------------*/
extern uint32_t ticks;
extern uint32_t ticks_tim2;
extern uint8_t Flag;

//----------------- SYSTICK HANDLER +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ SYSTICK HANDLER ------------------------------------------------*/
/* @brief  Go in this function when a SysTick timer IRQ are activate.
 * @retval None */
void SysTick_Handler(void){
	ticks++;
}

//----------------- SYSTICK HANDLER +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ SYSTICK HANDLER ------------------------------------------------*/
/* @brief  Go in this function when a Timer 2 IRQ are activate.
 * @retval None */
void TIM2_IRQHandler(void){
	if (TIM2->SR & TIM_SR_UIF){
		TIM2->SR &= ~TIM_SR_UIF;
		Flag = 1;
	}
}

