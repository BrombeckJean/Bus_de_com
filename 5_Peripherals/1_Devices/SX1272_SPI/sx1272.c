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
	printf("data = %x \r\n\n",data);
}

//----------------- SX1272 CONF ----------------------------------------------------------------------------- SX1272 CONF ----------------------------------------------------*/
/* @brief  Send on SPI the configuration for a LoRa transmission
 * @retval None */
void Sx1272_Conf(void)
{
	/* Mode Init */
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x01, 0x00); /* Sleep Mode */
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x01, 0x80); /* Lora type */

	/* Frequency  868.1 MHz */
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x06, 0xD9);
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x07, 0x06);
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x08, 0x8B);

	/* LoRa Parameters */
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x1D, 0x0A); // BW = 125 kHz, Coding Rate = 4/5
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x1E, 0x70); // SF12

    /* FIFO Configuration */
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x0E, 0x80); // TX
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x0F, 0x00); // RX

	/* Others Parameters */
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x09, 0x88); // Output Power
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x11, 0x8F); // Irq Masked

	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x39, 0x34); // Irq Masked
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x33, 0x01); // Irq Masked
}

//----------------- SX1272 CHECK CONF ----------------------------------------------------------------------- SX1272 CHECK CONF ----------------------------------------------*/
/* @brief  Read registers and display registers value on UART
 * @retval None */
void Sx1272_Check_Conf(void)
{
	uint8_t RegOpMode   		= Spi_Read_Reg(PINOUT_SPI, SPI1, 0x01);
	uint8_t RegFrfMsb   		= Spi_Read_Reg(PINOUT_SPI, SPI1, 0x06);
	uint8_t RegFrfMid   		= Spi_Read_Reg(PINOUT_SPI, SPI1, 0x07);
	uint8_t RegFrfLsb			= Spi_Read_Reg(PINOUT_SPI, SPI1, 0x08);
	uint8_t RegModemConfig1   	= Spi_Read_Reg(PINOUT_SPI, SPI1, 0x1D);
	uint8_t RegModemConfig2   	= Spi_Read_Reg(PINOUT_SPI, SPI1, 0x1E);
	uint8_t RegFifoTxBaseAddr   = Spi_Read_Reg(PINOUT_SPI, SPI1, 0x0E);
	uint8_t RegFifoRxBaseAddr	= Spi_Read_Reg(PINOUT_SPI, SPI1, 0x0F);
	uint8_t RegPaConfig 		= Spi_Read_Reg(PINOUT_SPI, SPI1, 0x09);
	uint8_t RegIrqFlagsMask 	= Spi_Read_Reg(PINOUT_SPI, SPI1, 0x11);
	uint8_t irqreg 				= Spi_Read_Reg(PINOUT_SPI, SPI1, 0x12);
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x01, 0x01); // Standby Mode


	printf("Sx1272 Configuration :\r\n");
	printf(" - RegOpMode (0x01) 	  	= 0x%x\r\n", RegOpMode   		);
	printf(" - RegFrfMsb (0x06) 	  	= 0x%x\r\n", RegFrfMsb   		);
	printf(" - RegFrfMid (0x07) 	  	= 0x%x\r\n", RegFrfMid   		);
	printf(" - RegFrfLsb (0x08) 	  	= 0x%x\r\n", RegFrfLsb		);
	printf(" - RegModemConfig1 (0x1D)	= 0x%x\r\n", RegModemConfig1  );
	printf(" - RegModemConfig2 (0x1E)	= 0x%x\r\n", RegModemConfig2  );
	printf(" - RegFifoTxBaseAddr (0x0E)	= 0x%x\r\n", RegFifoTxBaseAddr);
	printf(" - RegFifoRxBaseAddr (0x0F)	= 0x%x\r\n", RegFifoRxBaseAddr);
	printf(" - RegPaConfig (0x09) 	  	= 0x%x\r\n", RegPaConfig 		);
	printf(" - RegIrqFlagsMask (0x11)		= 0x%x\r\n", RegIrqFlagsMask 	);
	printf(" - irqreg (0x12) 		= 0x%x\r\n\n", irqreg			);
}

//----------------- SX1272 SEND ----------------------------------------------------------------------------- SX1272 SEND ----------------------------------------------------*/
/* @brief  Send the data you want to transmit in LoRa on the SPI
 * @retval None */
void Sx1272_Send(uint8_t* data, uint8_t size)
{
	/* Initialise FIFO TX */
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x0E, 0x80);
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x0D, 0x80);

	/* Payload Length */
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x22, size);

    /* Put Data In FIFO TX */
    for (uint8_t i = 0; i < size; i++) {
    	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x80, data[i]);
    }

	/* Mode TX */
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x01, 0x03);

    /* TX Done ? *//*
    while ((Spi_Read_Reg(PINOUT_SPI, SPI1, 0x12) & 0x08) == 0);
    Spi_Write_Reg(PINOUT_SPI, SPI1, 0x12, 0xFF); // Reset Irq*/

	printf("Message Transmit : ");
	for (int i = 0; i < size; i++) {
	  printf("0x%x ",data[i]);
	}
	printf("\r\n\n");
}

//----------------- SX1272 RECEIVE -------------------------------------------------------------------------- SX1272 RECEIVE -------------------------------------------------*/
/* @brief  Configure the sx1272 in RX mode and display the value received
 * @retval None */
void Sx1272_Receive(void)
{
	/* Initialise FIFO RX */
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x0F, 0x80);

	/* Mode RX Continue */
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x01, 0x05);

	/* RX Done ? */
	while ((Spi_Read_Reg(PINOUT_SPI, SPI1, 0x12) & 0x40) == 0);
	uint8_t rxLength = Spi_Read_Reg(PINOUT_SPI, SPI1, 0x13);
	uint8_t fifoAddr = Spi_Read_Reg(PINOUT_SPI, SPI1, 0x10);
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x0D, fifoAddr);

	uint8_t rxBuffer[rxLength];
	for (uint8_t i = 0; i < rxLength; i++) {
		rxBuffer[i] = Spi_Read_Reg(PINOUT_SPI, SPI1, 0x00);
	}

	printf("Message received : ");
	for (int i = 0; i < rxLength; i++) {
	  printf("0x%x ",rxBuffer[i]);
	}
	printf("\r\n\n");

	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x12, 0xFF);  // Reset Irq
}

//----------------- SX1272 SEND TEMP ------------------------------------------------------------------------ SX1272 SEND TEMP -----------------------------------------------*/
/* @brief  Send the temperature in LoRa
 * @retval None */
void Sx1272_Send_Temp(void)
{
	/* Initialise FIFO TX */
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x0E, 0x80);
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x0D, 0x80);

	/* Payload Length */
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x22, 2);

	uint16_t temps =  Ds18b20_Dysplay_Temp();

    Spi_Write_Reg(PINOUT_SPI, SPI1, 0x80, (uint8_t) temps);
    Spi_Write_Reg(PINOUT_SPI, SPI1, 0x80, (uint8_t) (temps>>8));

	/* Mode TX */
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x01, 0x03);

	uint8_t be_comma  = temps / 1000;
	uint8_t af_comma  = temps % 1000;
	printf("temp transmit = %d,%d deg \r\n\n",be_comma, af_comma);
}

//----------------- SX1272 RECEIVE TEMP --------------------------------------------------------------------- SX1272 RECEIVE TEMP --------------------------------------------*/
/* @brief  Configure the sx1272 in RX mode and display the value received
 * @retval None */
void Sx1272_Receive_Temp(void)
{
	/* Initialise FIFO RX */
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x0F, 0x80);

	/* Mode RX Continue */
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x01, 0x05);

	/* RX Done ? */
	while ((Spi_Read_Reg(PINOUT_SPI, SPI1, 0x12) & 0x40) == 0);
	uint8_t rxLength = Spi_Read_Reg(PINOUT_SPI, SPI1, 0x13);
	uint8_t fifoAddr = Spi_Read_Reg(PINOUT_SPI, SPI1, 0x10);
	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x0D, fifoAddr);

	uint8_t rxBuffer[rxLength];
	for (uint8_t i = 0; i < rxLength; i++) {
		rxBuffer[i] = Spi_Read_Reg(PINOUT_SPI, SPI1, 0x00);
	}
	uint16_t temp = 0;
	 temp = rxBuffer[0]<<8 | rxBuffer[1];
	uint8_t be_comma  = temp / 1000;
	uint8_t af_comma  = temp % 1000;

	printf("temp received = %d,%d deg \r\n\n",be_comma, af_comma);

	Spi_Write_Reg(PINOUT_SPI, SPI1, 0x12, 0xFF);  // Reset Irq
}
