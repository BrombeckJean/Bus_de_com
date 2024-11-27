/********************************************************************************
  * @file           : spi.h
  * @brief          : All function for use SPI
  *******************************************************************************/

//----------------- SPECIAL DEFINE ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ SPECIAL DEFINE -------------------------------------------------*/
#ifndef SPI_SPI_H_
#define SPI_SPI_H_

//------------------ INCLUDE -------------------------------------------------------------------------------- INCLUDE --------------------------------------------------------*/
#include "gpio.h"

//----------------- GLOBAL DEFINE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ GLOBAL DEFINE --------------------------------------------------*/
#define SPI_W_R_BIT_MASK 7

//------------------ TYPE DEFINE ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ TYPE DEFINE ----------------------------------------------------*/
typedef struct {
	GPIO_TypeDef*    port_NSS;
    uint16_t         pin_NSS;
	GPIO_TypeDef*    port_MISO;
    uint16_t         pin__MISO;
	GPIO_TypeDef*    port_MOSI;
    uint16_t         pin_MOSI;
	GPIO_TypeDef*    port_CLK;
    uint16_t         pin_CLK;
}SPI_PINOUT;

//----------------- PROTOTYPE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ PROTOTYPE ------------------------------------------------------*/
void Spi_Set_Nss(SPI_PINOUT Spi_Pinout);
void Spi_Reset_Nss(SPI_PINOUT Spi_Pinout);

void Spi_Transmit(SPI_TypeDef spix ,uint8_t data);
uint8_t Spi_Receive(SPI_TypeDef spix);
uint8_t Spi_Transmit_Recive(SPI_TypeDef spix, uint8_t data);

void Spi_Write_Reg (SPI_PINOUT Spi_Pinout, SPI_TypeDef spix, uint8_t reg, uint8_t data);
uint8_t Spi_Read_Reg (SPI_PINOUT Spi_Pinout, SPI_TypeDef spix, uint8_t reg);

//----------------- END SPECIAL DEFINE ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ END SPECIAL DEFINE ---------------------------------------------*/
#endif /* SPI_SPI_H_ */
