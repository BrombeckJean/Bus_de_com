/********************************************************************************
  * @file           : sx1272.c
  * @brief          : Lora transmitter
  *******************************************************************************/

//----------------- INCLUDE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ INCLUDE --------------------------------------------------------*/
#include "sx1272.h"

//----------------- GLOBAL CONSTANTS ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ GLOBAL CONSTANTS -----------------------------------------------*/
extern SPI_PINOUT	PINOUT_SPI;

//----------------- GLOBAL FUNCTIONS DEFINITION +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ GLOBAL FUNCTIONS DEFINITION ------------------------------------*/
//----------------- SX1272 INIT ----------------------------------------------------------------------------- SX1272 INIT ----------------------------------------------------*/
/* @brief  Initialise the device PinOut and look if device respond.
 * @param1 [in]  GPIOX  Holds MCU GPIO parameters
 * @param2 [in]  pin	Pin value
 * @retval None */
void Sx1272_Init(GPIO_TypeDef * GPIOX_nss, uint8_t pin_nss)
{
	PINOUT_SPI.port_NSS   = GPIOX_nss;
	PINOUT_SPI.pin_NSS    = pin_nss;
	Sx1272_Is_Connected();
}

//----------------- SX1272 IS CONNECTED --------------------------------------------------------------------- SX1272 IS CONNECTED --------------------------------------------*/
/* @brief  Look if device respond by checking the version.
 * @retval None */
void Sx1272_Is_Connected(void)
{
	Spi_Set_Nss(PINOUT_SPI);
	Spi_Reset_Nss(PINOUT_SPI);
	Spi_Transmit_Recive(SPI1, 0x42);
	uint8_t data = Spi_Receive(SPI1);
	Spi_Set_Nss(PINOUT_SPI);
	printf("data = %x \r\n",data);
}

//----------------- SX1272 CONF --------------------------------------------------------------------- SX1272 IS CONNECTED --------------------------------------------*/
/* @brief  Send on SPI the configuration for a LoRa transmission
 * @retval None */
void Sx1272_Conf(void)
{
	/* Standby Mode */
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x01, 0x81);

	/* Frequency */
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x06, 0xD9);
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x07, 0x06);
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x08, 0x66);

	/* Reset All Irq */
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x12, 0xFF);
}

//----------------- SX1272 CONF --------------------------------------------------------------------- SX1272 IS CONNECTED --------------------------------------------*/
/* @brief  Read registers and display registers value on UART
 * @retval None */
void Sx1272_Check_Conf(void)
{
	uint8_t RegOpMode   	= Spi_Read_Reg(PINOUT_SPI, SPI1, 0x01);
	uint8_t RegFrfMsb   	= Spi_Read_Reg(PINOUT_SPI, SPI1, 0x06);
	uint8_t RegFrfMid   	= Spi_Read_Reg(PINOUT_SPI, SPI1, 0x07);
	uint8_t RegFrfLsb		= Spi_Read_Reg(PINOUT_SPI, SPI1, 0x08);
	uint8_t RegIrqFlagsMask = Spi_Read_Reg(PINOUT_SPI, SPI1, 0x11);
	uint8_t irqreg 			= Spi_Read_Reg(PINOUT_SPI, SPI1, 0x12);

	printf("Sx1272 Configuration :\r\n");
	printf(" - RegOpMode (0x01) = %x\r\n", RegOpMode);
	printf(" - RegFrfMsb (0x06) = %x\r\n", RegFrfMsb);
	printf(" - RegFrfMid (0x07) = %x\r\n", RegFrfMid);
	printf(" - RegFrfLsb (0x08) = %x\r\n", RegFrfLsb);
	printf(" - RegIrqFlagsMask (0x11) = %x\r\n", RegIrqFlagsMask);
	printf(" - RegIrqFlags (0x12) = %x\r\n", irqreg);
}

//----------------- SX1272 SEND --------------------------------------------------------------------- SX1272 IS CONNECTED --------------------------------------------*/
/* @brief  Send the data you want to transmit in LoRa on the SPI
 * @retval None */
void Sx1272_Send(void)
{
	/* Payload Length */
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x22, 0x01);

	/* FIFO */
    Spi_Write_Reg(PINOUT_SPI, SPI1, 0x0E, 0x80);
    Spi_Write_Reg(PINOUT_SPI, SPI1, 0x0D, 0x80);
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x00, 0x24); // data

	/* activate Irq TX Done */
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x11, 0xF7); // mask other irq

	/* Mode TX */
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x01, 0x83);

    /* TX Done ? */
    while ((Spi_Read_Reg(PINOUT_SPI, SPI1, 0x12) & 0x08) == 0);
    Spi_Write_Reg(PINOUT_SPI, SPI1, 0x12, 0x08); // reset txdone
}

//----------------- SX1272 RECEIVE --------------------------------------------------------------------- SX1272 IS CONNECTED --------------------------------------------*/
/* @brief  Send on SPI the configuration for a LoRa transmission
 * @retval None */
void Sx1272_Receive(void)
{
	/* Activate Irq TX Done */
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x11, 0xBF); // mask other irq

	/* Mode RX */
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x01, 0x85);

	/* TX Done ? */
	while ((Spi_Read_Reg(PINOUT_SPI, SPI1, 0x12) & 0x40) == 0);
	uint8_t rxLength = Spi_Read_Reg(PINOUT_SPI, SPI1, 0x13);
	uint8_t fifoAddr = Spi_Read_Reg(PINOUT_SPI, SPI1, 0x10);
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x0D, fifoAddr);

	uint8_t rxBuffer[rxLength];
	for (uint8_t i = 0; i < rxLength; i++) {
	    rxBuffer[i] = Spi_Read_Reg(PINOUT_SPI, SPI1, 0x00); // Lire FIFO
	}

	printf("Message received : ");
	for (int i = 0; i < 8; i++) {
	  printf("%d",(char)rxBuffer[i]);
	}
	printf("\r\n");

	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x12, 0x40); // Effacer RxDone
}
