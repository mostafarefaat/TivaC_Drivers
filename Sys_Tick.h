/**
 ********************************************************************************
 * @file    app.h
 * @author  Mostafa Refaat
 * @date    31/1/2024
 * @brief   
 ********************************************************************************
 */

#ifndef _SYS_TICK_
#define _SYS_TICK_

/************************************
 * INCLUDES
 ************************************/
#include "..\GPIO\GPIO.h"
/************************************
 * MACROS AND DEFINES
 ************************************/

#define BASE_ADDRESS					0XE000E000
#define STCTRL 			 			*((volatile uint32 *)(BASE_ADDRESS + 0x010))
#define STRELOAD 			 		*((volatile uint32 *)(BASE_ADDRESS + 0x014))
#define STCURRENT 				*((volatile uint32 *)(BASE_ADDRESS + 0x018))
	
#define EN_PIN							0
#define INTEN_PIN						1
#define CLK_SRC_PIN					2
#define COUNT_FLAG_PIN			16

#define CURRENT_VALUE_RESET		0X00000000

#define	PIOSC									0
#define	System_CLK						1
#define	Interrupt_ON					1
#define	Interrupt_OFF					0
/************************************
 * TYPEDEFS
 ************************************/

/************************************
 * EXPORTED VARIABLES
 ************************************/

/************************************
 * GLOBAL FUNCTION PROTOTYPES
 ************************************/
void Sys_tick_init(uint32 ticks, uint8 clk_source, uint8 interrupt_config);
void Sys_tick_Start(void);
void Sys_tick_Stop(void);
void register_systick_cb(cb_ptr Ptr);


#endif 
