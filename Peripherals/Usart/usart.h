/*
 * usart.h
 *
 *  Created on: 16 oct. 2024
 *      Author: jean
 */

#ifndef USART_USART_H_
#define USART_USART_H_

void USART2_Init(void);
void USART2_TransmitChar(uint8_t data);
uint8_t USART2_ReceiveChar(void);

#endif /* USART_USART_H_ */
