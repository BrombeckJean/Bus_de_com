/********************************************************************************
 * @file           : spi.c
 * @brief          : Contain all the function for use SPI
 ********************************************************************************/

//----------------- INCLUDE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ INCLUDE --------------------------------------------------------*/
#include "spi.h"

//------------------ SPI INIT ------------------------------------------------------------------------------- SPI INIT -------------------------------------------------------*/
/* @brief  Initialise all the SPI parameters
 * @retval None */
void SPI_Init(void){
 /* Clock Activation */
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

 /* CR1 Register Configuration */
    SPI1->CR1 = 0;								// Reset ALL Values
    SPI1->CR1 |= SPI_CR1_MSTR;  				// Mode mSaster
    SPI1->CR1 |= SPI_CR1_BR_1 | SPI_CR1_BR_0; 	// Prediv16
    SPI1->CR1 &= ~(SPI_CR1_CPOL); 				// Clock Polarity 0
    SPI1->CR1 &= ~(SPI_CR1_CPHA); 				// Clock Phase 0
    SPI1->CR1 |= SPI_CR1_SSM;					// Enable Software Slave Management
    SPI1->CR1 |= SPI_CR1_SSI;					// Internal Slave Select
    SPI1->CR1 |= SPI_CR1_SPE;					// SPI Enable
}

//------------------ SPI SET NSS ---------------------------------------------------------------------------- SPI SET NSS ----------------------------------------------------*/
/* @brief  Set the NSS of the SPI for end a transmission
 * @param1 [in]  Spi_Pinout  Structure contain the GPIO and the Pin used
 * @retval None */
void Spi_Set_Nss(SPI_PINOUT Spi_Pinout)
{
	GPIO_Set_Pin(Spi_Pinout.port_NSS , Spi_Pinout.pin_NSS);
}

//------------------ SPI RESET NSS -------------------------------------------------------------------------- SPI RESET NSS --------------------------------------------------*/
/* @brief  Reset the NSS of the SPI for start a transmission
 * @param1 [in]  Spi_Pinout  Structure contain the GPIO and the Pin used
 * @retval None */
void Spi_Reset_Nss(SPI_PINOUT Spi_Pinout)
{
	GPIO_Reset_Pin(Spi_Pinout.port_NSS , Spi_Pinout.pin_NSS);
}

//------------------ TRANSMIT ------------------------------------------------------------------------------- TRANSMIT -------------------------------------------------------*/
/* @brief  Put the data in the DR register for send data on the SPI
 * @param1 [in]  spix  Holds MCU SPI parameters
 * @param2 [in]  data  Byte you want transmit
 * @retval None */
void Spi_Transmit(SPI_TypeDef* spix ,uint8_t data)
{
	while(!(spix->SR & 1<<SPI_SR_TXE_Pos)>>SPI_SR_TXE_Pos);
	spix->DR = data;
	while(!((spix->SR & 1<<SPI_SR_RXNE_Pos)>>SPI_SR_RXNE_Pos));
}

//------------------ RECIVE --------------------------------------------------------------------------------- RECIVE ---------------------------------------------------------*/
/* @brief  Put an empty value in the DR register for send data on the SPI and read the DR register for get the data
 * @param1 [in]  spix  Holds MCU SPI parameters
 * @retval The data receive */
uint8_t Spi_Receive(SPI_TypeDef* spix)
{
	while(!(spix->SR & 1<<SPI_SR_TXE_Pos)>>SPI_SR_TXE_Pos);
	spix->DR = 0xFF;

	while(!((spix->SR & 1<<SPI_SR_RXNE_Pos)>>SPI_SR_RXNE_Pos));
	return spix->DR;
}

//------------------ TRANSMIT RECIVE ------------------------------------------------------------------------ TRANSMIT RECIVE ------------------------------------------------*/
/* @brief  Put the data value in the DR register for send data on the SPI and read the DR register for get the data
 * @param1 [in]  spix  Holds MCU SPI parameters
 * @param2 [in]  data  Byte you want transmit
 * @retval The data receive */
uint8_t Spi_Transmit_Recive(SPI_TypeDef* spix, uint8_t data)
{
	while (!(spix->SR & SPI_SR_TXE));
	spix->DR = data;

	while (!(spix->SR & SPI_SR_RXNE));
	return spix->DR;
}

//------------------ SPI WRITE REG -------------------------------------------------------------------------- SPI WRITE REG --------------------------------------------------*/
/* @brief  Reset the NSS of the SPI for start a transmission
 * @param1 [in]  Spi_Pinout   Structure contain the GPIO and the Pin used
 * @param2 [in]  spix  		  Holds MCU SPI parameters
 * @param1 [in]  reg  		  Value of the register you want write
 * @param2 [in]  data  		  Data you want write
 * @retval None */
void Spi_Write_Reg (SPI_PINOUT Spi_Pinout, SPI_TypeDef* spix, uint8_t reg, uint8_t data)
{
	/* Sets the high-order bit to 1 */
    reg |= (1<<SPI_W_R_BIT_MASK);

	Spi_Reset_Nss(Spi_Pinout);
	Spi_Transmit_Recive(spix, reg);
	Spi_Transmit_Recive(spix, data);
	Spi_Set_Nss(Spi_Pinout);
}

//------------------ SPI READ REG --------------------------------------------------------------------------- SPI READ REG ---------------------------------------------------*/
/* @brief  Reset the NSS of the SPI for start a transmission
 * @param1 [in]  Spi_Pinout   Structure contain the GPIO and the Pin used
 * @param2 [in]  spix  		  Holds MCU SPI parameters
 * @param1 [in]  reg  		  Value of the register you want read
 * @retval [out] data		  Data you want read */
uint8_t Spi_Read_Reg (SPI_PINOUT Spi_Pinout, SPI_TypeDef* spix, uint8_t reg)
{
	uint8_t data = 0;
	/* Sets the high-order bit to 0 */
	reg &= ~(1<<SPI_W_R_BIT_MASK);

	Spi_Reset_Nss(Spi_Pinout);
	Spi_Transmit_Recive(spix,reg);
	data = Spi_Transmit_Recive(spix,0xff);
	Spi_Set_Nss(Spi_Pinout);

	return data;
}
