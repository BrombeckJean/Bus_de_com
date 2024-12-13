/********************************************************************************
  * @file           : Option_comp.h
  * @brief          : All option settings parameters
  *******************************************************************************/

//----------------- SPECIAL DEFINE ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ SPECIAL DEFINE -------------------------------------------------*/
#ifndef OPTION_COMP_H_
#define OPTION_COMP_H_

//----------------- GLOBAL DEFINE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ GLOBAL DEFINE --------------------------------------------------*/
// the value is equal to the test numbers, so Test_1 = 1, Test_2 = 2, ect...
#define ONE_WIRE  	0 /* Only 3 test */
#define SPI  		0 /* Only 3 test */
#define I2C  		3 /* Only 3 test */
#if 	SPI>1
#define TRANSMIT	1
#define RECEIVE		0
#endif

//----------------- END SPECIAL DEFINE ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ END SPECIAL DEFINE ---------------------------------------------*/
#endif /* OPTION_COMP_H_ */
