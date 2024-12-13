/********************************************************************************
  * @file           : lis2dw12.c
  * @brief          : Captor Humidity and temperature
  *******************************************************************************/

//----------------- INCLUDE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ INCLUDE --------------------------------------------------------*/
#include "lis2dw12.h"

//----------------- GLOBAL CONSTANTS ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ GLOBAL CONSTANTS -----------------------------------------------*/
//----------------- LIS2DW12 IS CONNECTED ------------------------------------------------------------------- LIS2DW12 IS CONNECTED ------------------------------------------*/
/* @brief  Check if the device are connected
 * @retval None */
void Lis2dw12_Is_Connected(void)
{
	if(ReadReg(0x19, 0x0F) == 0x44)
	{
		printf("LIS2DW12 are connected \r\n");
	}else{
		printf("LIS2DW12 are disconnected \r\n");
	}
	SYSTICK_Delay(1000);
}

//----------------- LIS2DW12 CONF --------------------------------------------------------------------------- LIS2DW12 CONF --------------------------------------------------*/
/* @brief  Configure the LIS2DW12
 * @retval None */
void Lis2dw12_Conf(void)
{
/* Config Acc LIS */
WriteReg(0x19, 0x20, 0x20);

/* Enable Interrupt */
WriteReg(0x19,0x3F,0x20);
WriteReg(0x19,0x34,0xd0);
WriteReg(0x19,0x35,0x10);

WriteReg(0x19,0x24,0xc0);
}

//----------------- LIS2DW12 IS CONNECTED ------------------------------------------------------------------- LIS2DW12 IS CONNECTED ------------------------------------------*/
/* @brief  Initialise the device PinOut and look if device respond (On Usart).
 * @retval [Out]  val  The connection value on the OneWire PinOut */
void Lis2dw12_Print_Acc(void){
	uint8_t X_L,X_H,Y_L,Y_H,Z_H,Z_L;

	int16_t X_int,Y_int,Z_int;
	float X,Y,Z;
	X_L = ReadReg(0x19, 0x28);
	X_H = ReadReg(0x19, 0x29);
	Y_L = ReadReg(0x19, 0x2A);
	Y_H = ReadReg(0x19, 0x2B);
	Z_L = ReadReg(0x19, 0x2C);
	Z_H = ReadReg(0x19, 0x2D);

	X_int = X_H<<8 | X_L;
	X = ((X_int/4)*0.244)/1000;

	Y_int = Y_H<<8 | Y_L;
	Y = ((Y_int/4)*0.244)/1000;

	Z_int = Z_H<<8 | Z_L;
	Z = ((Z_int/4)*0.244)/1000;
	printf("Acc LIS2DW12 Value :\r\n");
	printf("X  = %f \r\n",X);
	printf("Y = %f \r\n",Y);
	printf("Z = %f \r\n\n",Z);
	SYSTICK_Delay(1000);

}
