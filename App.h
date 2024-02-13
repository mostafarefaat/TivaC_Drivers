/**
 ********************************************************************************
 * @file    App.h
 * @author  Mostafa Refaat
 * @date    31/1/2024
 * @brief   
 ********************************************************************************
 */

#ifndef _APP_H_
#define _APP_H_

/************************************
 * INCLUDES
 ************************************/
#include "GPIO.h"
#include "Sys_Tick.h"
#include "MCU.h"
#include "NVIC.h"
/************************************
 * MACROS AND DEFINES
 ************************************/
#define NUMBER_OF_ITERATIONS_FOR_ONE_MILLI_SECOND		364
#define Red_On				0x02
#define Blue_On				0x04
#define Green_On			0x08
/************************************
 * TYPEDEFS
 ************************************/

/************************************
 * EXPORTED VARIABLES
 ************************************/

/************************************
 * GLOBAL FUNCTION PROTOTYPES
 ************************************/
void App_init(void);
void App_run(void);
void Delay_MS(unsigned long long n);

void GPIOF_Driver_Handler(void);
void SysTick_Driver_Handler(void);


#endif 
