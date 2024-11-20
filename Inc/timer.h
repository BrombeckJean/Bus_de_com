/********************************************************************************
  * @file           : timer.h
  * @brief          : All function for use timer
  *******************************************************************************/

//----------------- SPECIAL DEFINE ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ SPECIAL DEFINE -------------------------------------------------*/
#ifndef TIMER_H_
#define TIMER_H_

//----------------- PROTOTYPE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ PROTOTYPE ------------------------------------------------------*/
void SYSTICK_Init(void);
void SYSTICK_Delay(uint32_t Delay);
uint32_t SYSTICK_Get(void);

void TIM2TICK_Init(void);
void TIM2TICK_Delay(uint32_t Delay);
uint32_t TIM2TICK_Get(void);

void DWT_Init(void);
void DWT_Delay(uint32_t _us);

//----------------- END SPECIAL DEFINE ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ END SPECIAL DEFINE ---------------------------------------------*/
#endif
