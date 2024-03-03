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
#include "..\MCAL\GPIO\GPIO.h"
#include "..\MCAL\Sys_Timer\Sys_Tick.h"
#include "..\MCAL\MCU\MCU.h"
#include "..\MCAL\NVIC\NVIC.h"
#include "..\MCAL\MPU\MPU.h" 
#include "..\MCAL\UART\uart0.h" 
/************************************
 * MACROS AND DEFINES
 ************************************/
#define NUMBER_OF_ITERATIONS_FOR_ONE_MILLI_SECOND		364
#define Red_On						0x02
#define Blue_On						0x04
#define Green_On					0x08
#define SVC_PRI						1
#define PendSV_PRI				7
#define BusFault_PRI			0
#define MemManage_PRI			0
#define UsageFault_PRI		0
#define Number_of_Faults 	4

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

void HardFault_App_Handler(void);
void BusFault_App_Handler(void);
void MemManage_App_Handler(void); 
void UsageFault_App_Handler(void);



uint32 Divide(uint32 num1,uint32 num2);


#endif 
