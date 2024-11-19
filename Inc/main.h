/********************************************************************************
  * @file           : main.h
  * @brief          : Main function
  *******************************************************************************/

//------------------ INCLUDE -------------------------------------------------------------------------------- INCLUDE ----------------------------------------------------------*/
#include "ds18b20.h"

//----------------- SPECIAL DEFINE ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ SPECIAL DEFINE -------------------------------------------------*/
#ifndef MAIN_H_
#define MAIN_H_

//----------------- DEFINE ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ DEFINE ---------------------------------------------------------*/
#define INPUT_MODE 	0
#define OUTPUT_MODE	1
#define ALT_MODE 	2
#define ANALOG_MODE	3

#define OUTPUT_PUSH_PULL 	0
#define OUTPUT_OPEN_DRAIN	1

#define NO_PULL 	0
#define PULL_UP		1
#define PULL_DOWN 	2

#define BITMASK_1BITS	0b1
#define BITMASK_2BITS	0b11
#define BITMASK_3BITS	0b111
#define BITMASK_4BITS	0b1111
#define BITMASK_5BITS	0b11111

//----------------- END SPECIAL DEFINE ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ END SPECIAL DEFINE ---------------------------------------------*/
#endif
