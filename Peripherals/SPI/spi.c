/********************************************************************************
 * @file           : spi.c
 * @brief          : Contain all the function for use SPI
 ********************************************************************************/

//------------------ INCLUDE -------------------------------------------------------------------------------- INCLUDE --------------------------------------------------------*/

//------------------ GLOBAL FUNCTIONS DEFINITION ------------------------------------------------------------ GLOBAL FUNCTIONS DEFINITION ------------------------------------*/
//------------------ SPI SET NSS ---------------------------------------------------------------------------- SPI SET NSS ----------------------------------------------------*/
/* @brief  Set the NSS of the SPI for start a transmission
 * @retval None */
void Spi_Set_Nss(void)
{
	Gpio_Set_Pin(port_nss_spi , pin_nss_spi);
}

//------------------ SPI RESET NSS -------------------------------------------------------------------------- SPI RESET NSS --------------------------------------------------*/
/* @brief  Reset the NSS of the SPI for start a transmission
 * @retval None */
void Spi_Reset_Nss(void)
{
	Gpio_Reset_Pin(port_nss_spi , pin_nss_spi);
}

//------------------ TRANSMIT ------------------------------------------------------------------------------- TRANSMIT -------------------------------------------------------*/
/* @brief  Put the data in the TXE register for send data on the SPI
 * @retval None */
void Transmit(spix,data)
{
	spix -> DR = data;
	while(spix -> TXE & SPI1_SR_TXE_Pos == 0);
	while(spix -> RXNE & SPI1_SR_TXE_Pos == 0);
}

//------------------ RECIVE --------------------------------------------------------------------------------- RECIVE ---------------------------------------------------------*/
/* @brief  Put an empty value in the TXE register for send data on the SPI and read the RXNE register for get the data
 * @retval None */
uint8_t Recive(spix)
{
	spix -> DR = EMPTY;
	while(spix -> TXE & SPI1_SR_TXE_Pos == 0);
	while(spix -> RXNE & SPI1_SR_TXE_Pos == 0);
	return SPIX->DR;
}

//------------------ TRANSMIT RECIVE ------------------------------------------------------------------------ TRANSMIT RECIVE ------------------------------------------------*/
/* @brief  Put the data value in the TXE register for send data on the SPI and read the RXNE register for get the data
 * @retval None */
uint8_t Transmit_Recive(spix,data)
{
	spix -> DR = data;
	while(spix -> TXE & SPI1_SR_TXE_Pos == 0);
	while(spix -> RXNE & SPI1_SR_TXE_Pos == 0);
	return SPIX->DR;
}

//------------------ SPI RESET NSS -------------------------------------------------------------------------- SPI RESET NSS --------------------------------------------------*/
/* @brief  Reset the NSS of the SPI for start a transmission
 * @retval None */
void Write_Reg (void)
{
	Spi_Rest_Nss();
	Transmit(spi1,reg);
	Transmit(spi1, data);
	Spi_Set_Nss_pin();
}

//------------------ SPI RESET NSS -------------------------------------------------------------------------- SPI RESET NSS --------------------------------------------------*/
/* @brief  Reset the NSS of the SPI for start a transmission
 * @retval None */
void Read_Reg (void)
{
	Spi_Rest_Nss();
	Transmit(spi1,data);
	res = Recive(spi1);
	Spi_Set_Nss_pin();
}
