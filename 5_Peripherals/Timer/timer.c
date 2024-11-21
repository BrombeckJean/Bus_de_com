#include <stdint.h>
#include "stm32f446xx.h"
#include "timer.h"



uint32_t SystemCoreClock = 16000000;
uint32_t ticks = 0;
uint32_t ticks_tim2 = 0;

//////////////////////////////////////////////
////////////// SYSTICK TIMER /////////////////
//////////////////////////////////////////////

void SYSTICK_Init(void){
	SysTick_Config(SystemCoreClock / 1000);
}

/**
 * Millisecond delays with Systick Timer, blocking function
 * @param delay : milliseconds to wait
 */
void SYSTICK_Delay(uint32_t Delay)
{
	  uint32_t tickstart = SYSTICK_Get();

	  while((SYSTICK_Get() - tickstart) < Delay);
}

uint32_t SYSTICK_Get(void){
	return ticks;
}

//////////////////////////////////////////////
////////////// DW TIMER //////////////////////
//////////////////////////////////////////////

void DWT_Init(void)
{
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
//    DWT->LAR = 0xC5ACCE55;  // For Cortex M7
    DWT->CYCCNT = 0;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

/**
 * Microsecond delays with DW Timer, blocking function
 * @param _us : microseconds to wait
 */
void DWT_Delay(uint32_t _us)
{
    uint32_t startTick  = DWT->CYCCNT;
    uint32_t targetTick = DWT->CYCCNT + _us * (SystemCoreClock/1000000);

    // No overflow
    if (targetTick > startTick)
        while (DWT->CYCCNT < targetTick);

    // With overflow
    else
        while (DWT->CYCCNT > startTick || DWT->CYCCNT < targetTick);

}


void TIM2TICK_Init(void){
	/* Clock Activation */
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

	/* Interruption */
	NVIC_EnableIRQ( TIM2_IRQn );

	/* Configuration Periph*/
	TIM2->PSC  = 15999;		// 1Khz en sortie du prescaler (16 MHz / (PSC + 1) = 1 kHz)
	TIM2->ARR  = 60000; 	// 1 kHz * 60,000 = 60 secondes
    TIM2->CNT = 0;    		// Réinitialiser le compteur
	TIM2->DIER |= TIM_DIER_UIE;
	TIM2->CR1  |= TIM_CR1_CEN;

	TIM2->SR &= ~TIM_SR_UIF;
}

/**
 * Millisecond delays with Systick Timer, blocking function
 * @param delay : milliseconds to wait
 */
void TIM2TICK_Delay(uint32_t Delay)
{
	  uint32_t tickstart = TIM2TICK_Get();

	  while((TIM2TICK_Get() - tickstart) < Delay);
}

uint32_t TIM2TICK_Get(void){
	return ticks;
}


// Get MCO HSE to PA8 (D7)
// the MCO1PRE[2:0] and MCO1[1:0]

