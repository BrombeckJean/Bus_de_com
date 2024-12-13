/********************************************************************************
 * @file           : i2c.c
 * @brief          : Contain all the function for use I2C
 ********************************************************************************/

//----------------- INCLUDE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ INCLUDE --------------------------------------------------------*/
#include "i2c.h"

//------------------ I2C INIT ------------------------------------------------------------------------------- I2C INIT -------------------------------------------------------*/
/* @brief  Initialise all the I2C parameters
 * @retval None */
void I2C_Init(void){
 /* Clock Activation */
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

 /* I2C Configuration */
	I2C1->CR2 = 16; 		 // Bus speed frequency ( 16MHz )
	I2C1->CCR = 80; 		 // Transmitted speed 100 kHz
	I2C1->TRISE = 17; 		 // 100 kHz
	I2C1->CR1 |= I2C_CR1_PE; // I2C Enable
}

int ReadReg(uint8_t addr,uint8_t regR){
	uint8_t data;
	I2C1->CR1 |= I2C_CR1_START;

	while (!(I2C1->SR1 & I2C_SR1_SB));
	I2C1->SR1;
	I2C1->DR = addr<<1;
	while (!(I2C1->SR1 & I2C_SR1_ADDR));
	I2C1->SR1;
	I2C1->SR2;
	while (!(I2C1->SR1 & I2C_SR1_TXE));
	I2C1->DR = regR;
	while (!(I2C1->SR1 & I2C_SR1_TXE));

	I2C1->CR1 |= I2C_CR1_START;
	while (!(I2C1->SR1 & I2C_SR1_SB));
	I2C1->SR1;
	I2C1->DR = addr<<1 | 1;
	while (!(I2C1->SR1 & I2C_SR1_ADDR));
	I2C1->SR1;
	I2C1->SR2;
	while (!(I2C1->SR1 & I2C_SR1_RXNE));
	data = I2C1->DR;
	I2C1->CR1 |= I2C_CR1_STOP;

	return data;
}
void ReadRegExtend(uint8_t addr,uint8_t tab[2]){
	I2C1->CR1 |= I2C_CR1_START;
	while (!(I2C1->SR1 & I2C_SR1_SB));
	I2C1->SR1;
	I2C1->DR = addr<<1 | 1;
	while (!(I2C1->SR1 & I2C_SR1_ADDR));
	I2C1->SR1;
	I2C1->SR2;
	tab[0] = I2C1->DR;
	while (!(I2C1->SR1 & I2C_SR1_RXNE));
	tab[1] = I2C1->DR;
	/*I2C1->SR1;
	while (!(I2C1->SR1 & I2C_SR1_RXNE));*/
	I2C1->CR1 |= I2C_CR1_STOP;
}

void WriteReg(uint8_t addr,uint8_t regW,uint8_t data){
	I2C1->CR1 |= I2C_CR1_START;

	while (!(I2C1->SR1 & I2C_SR1_SB));
	I2C1->SR1;
	I2C1->DR = addr<<1;
	while (!(I2C1->SR1 & I2C_SR1_ADDR));
	I2C1->SR1;
	I2C1->SR2;
	while (!(I2C1->SR1 & I2C_SR1_TXE));
	I2C1->DR = regW;
	while (!(I2C1->SR1 & I2C_SR1_TXE));
	I2C1->DR = data;
	while (!(I2C1->SR1 & I2C_SR1_TXE));

	I2C1->CR1 |= I2C_CR1_STOP;

}

