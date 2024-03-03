/**
 ********************************************************************************
 * @file    app.h
 * @author  Mostafa Refaat
 * @date    31/1/2024
 * @brief   
 ********************************************************************************
 */

#ifndef _NVIC_H_
#define _NVIC_H_

/************************************
 * INCLUDES
 ************************************/
#include "..\GPIO\GPIO.h"
/************************************
 * MACROS AND DEFINES
 ************************************/
 
#define FALLING_LOW			0
#define RISING_HIGH			1
#define BOTH						2

#define EDGE						1
#define LEVEL						0

/*User Config*/
#define CFG_INT_NUM_MODULES								1					         /*NUMBER OF NEEDED INTERRUPTS MODULES*/
#define CFG_INT_NUM_PIN						        1									/*NUMBER OF NEEDED INTERRUPT PINS*/

/*Masks*/
#define VECT_KEY									0X05FA
#define APINT_VECT_KEY_POS				16

#define APINT_PRIGROUP_POS				8
#define APINT_PRIGROUP_MSK				0XF8FF /*TO SAVE THE DATA IN THE APINT REGISTER IN BITS FROM 0:7 AND FROM 11:15*/

/*Main & Syb Groups*/
#define GroupsPriority_Config			0x05 			/*4 MAIN AND 2 SUB*/

#define USE_4_GROUPS_2_SUBGROUPS	5
#define USE_2_GROUPS_4_SUBGROUPS	6
#define USE_ALL_SUBGROUPS					7

#define MAIN_GROUP_0							0
#define MAIN_GROUP_1							1
#define MAIN_GROUP_2							2
#define MAIN_GROUP_3							3
#define MAIN_GROUP_4							4
#define MAIN_GROUP_5							5
#define MAIN_GROUP_6							6
#define MAIN_GROUP_7							7

#define SUB_GROUP_0								0
#define SUB_GROUP_1								1
#define SUB_GROUP_2								2
#define SUB_GROUP_3								3
#define SUB_GROUP_4								4
#define SUB_GROUP_5								5
#define SUB_GROUP_6								6
#define SUB_GROUP_7								7

/*ARM Reserved Interrupts Numbers in The Vector Table*/
#define RESET 										1 
#define NMI												2
#define HARD_FAULT								3
#define MEMORY_MANAGEMENT 				4
#define BUS_FAULT									5	
#define USAGE_FAULT								6
#define	SV_CALL										11	
#define	DEBUG_MONITOR							12
#define	PEND_SV										14
#define SYS_TICK_Interrupt				15
 
 
 /*INTERRRUPT REGISTERS and Base Address*/
#define PER_BASE_ADDRESS    			0XE000E000
#define PRIx(i)  					 				(*((volatile uint32 *) (PER_BASE_ADDRESS + ( (0x0400 + ((i/4)*4) ) ) ) ) )
#define ENx(i)						 				(*((volatile uint32 *) (PER_BASE_ADDRESS + ( (0x0100 + ((i/32)*32) ) ) ) ) )
#define DISIx(i) 					 				(*((volatile uint32 *) (PER_BASE_ADDRESS + ( (0x0180 + ((i/32)*32) ) ) ) ) )
#define APINT			         				(*((volatile uint32 *)( PER_BASE_ADDRESS + 0xD0C)))

/************************************
 * TYPEDEFS
 ************************************/
typedef uint8 Group_SubgroupType;
typedef uint8 IntCtrl_InterruptType;

/************************************
 * ENUMS
************************************/
enum IntCtrl_InerruptType
{

	INT_GPIOPORTA, INT_GPIOPORTB, INT_GPIOPORTC, INT_GPIOPORTD, INT_GPIOPORTE,
	
	UART0, UART1, SSI0, I2C0, PWM0_Fault,
	
	PWM0_Gen0, PWM0_Gen1, PWM0_Gen2, QEI0, ADC0_Seq0,
	
	ADC0_Seq1, ADC0_Seq2, ADC0_Seq3, Watch_Dog, Timer_0_A,
	
	Timer_0_B, Timer_1_A, Timer_1_B, Timer_2_A, Timer_2_B,
	
	Analog_Comp0, Analog_Comp1, Reserved, Sys_Control, Flash_and_EEPROM_Ctrl,
	
	INT_GPIOPORTF,
	
	          
	/*TODO: WRITE THE REST OF THE INTERRUPTS NUMBERS*/   /*PAGE 104*/
  

	
};

/************************************
 * STRUCTURES
 ************************************/

typedef struct
{
	uint8	IntCtrl_Num;
	uint8 Main_Group_Priority_Config;
	uint8 Sub_Group_Priority_Config;
	
}User_data_type;

typedef struct
{
	uint8	Port;
	uint8	Pin;
	uint8	Sensitivity;
	uint8	Event;
	
}User_pin_data_type;


/************************************
 * EXPORTED VARIABLES
 ************************************/

/************************************
 * GLOBAL FUNCTION PROTOTYPES
 ************************************/
void IntCtrl_init(const User_data_type *Config_Ptr);
void IntCtrl_PIN_Enable(const User_pin_data_type *Config_Ptr);

#endif 
