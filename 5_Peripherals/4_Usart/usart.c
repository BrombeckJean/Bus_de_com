/********************************************************************************
  * @file           : usart.C
  * @brief          : All function for use Usart
  *******************************************************************************/

//----------------- INCLUDE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ INCLUDE --------------------------------------------------------*/
#include "usart.h"
#include <stdint.h>
#include "stm32f446xx.h"
#include "gpio.h"

//----------------- GLOBAL FUNCTIONS DEFINITION +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ GLOBAL FUNCTIONS DEFINITION ------------------------------------*/
//----------------- USART2 INIT ----------------------------------------------------------------------------- USART2 INIT ----------------------------------------------------*/
/* @brief  Initialise the USART2
 * @retval None */
void USART2_Init(void){
	/* USART2 Init */
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;			// ABP1
	USART2->CR1 |= USART_CR1_UE;
	GPIOA->MODER |= ALT_MODE<<4;					// PA2
	GPIOA->MODER |= ALT_MODE<<6;					// PA3
	GPIOA->AFR[0] |= 7<<8;							// USART2
	GPIOA->AFR[0] |= 7<<12;							// USART2
	USART2->BRR  = 139;								// 115200 - APB1:16Mhz
	USART2->CR1 |= USART_CR1_TE | USART_CR1_RE;		// RX-TX
}

//----------------- USART2 TRANSMIT CHAR -------------------------------------------------------------------- USART2 TRANSMIT CHAR -------------------------------------------*/
/* @brief  transmit a character on USART2
 * @param1 [in]  the_char The character you want transmit
 * @retval None */
void USART2_TransmitChar(uint8_t the_char){
	USART2->DR = the_char;
	while( (USART2->SR & USART_SR_TXE)==0 );
}

//----------------- USART2 RECEIVE CHAR --------------------------------------------------------------------- USART2 RECEIVE CHAR --------------------------------------------*/
/* @brief  Read the character you received on the USART2
 * @retval The character you received */
uint8_t USART2_ReceiveChar(void){
	while( (USART2->SR & USART_SR_RXNE)==0 );
	return USART2->DR;

}
