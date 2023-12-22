#ifndef  INTCTRL_H_
#define  INTCTRL_H_
/*-----------INCLUDES-----------*/

#include "GPIO.h"

/*-----------LOCAL MACROS-----------*/
typedef uint8_t Group_SubgroupType;
typedef uint8_t IntCtrl_InterruptType;

#define VECT_KEY									0X05FA
#define APINT_VECT_KEY_POS				16
#define PER_BASE_ADDRESS    			0XE000E000
#define APINT_PRIGROUP_POS				8
#define APINT_PRIGROUP_MSK				0XF8FF /*TO SAVE THE DATA IN THE APINT REGISTER IN BITS FROM 0:7 AND FROM 11:15*/

#define GroupsPriority_Config			0x05 /*4 MAIN AND 2 SUB*/
#define CFG_INT_NUM								4		/*NUMBER OF NEEDED INTERRUPTS MODULES*/
#define CFG_INT_NUM_PIN						1		/*NUMBER OF NEEDED INTERRUPT PINS*/


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

#define INT_WDT										18
#define INT_GPIOPORTF 						30
#define Timer_1_A									21
#define Timer_1_B									22

#define WTIMER_2_B								99

#define FALLING_LOW			0
#define RISING_HIGH			1
#define BOTH						2

#define EDGE						1
#define LEVEL						0

/*-----------INTERRRUPT REGISTERS-----------*/ 
#define PRIx(i)  					 (*((volatile uint32_t *) (PER_BASE_ADDRESS + ( (0x0400 + ((i/4)*4) ) ) ) ) )
#define ENx(i)						 (*((volatile uint32_t *) (PER_BASE_ADDRESS + ( (0x0100 + ((i/32)*32) ) ) ) ) )
#define DISIx(i) 					 (*((volatile uint32_t *) (PER_BASE_ADDRESS + ( (0x0180 + ((i/32)*32) ) ) ) ) )
#define APINT			         *((volatile uint32_t *)( PER_BASE_ADDRESS + 0xD0C))
/*-----------END OF INTERRRUPT REGISTERS-----------*/



/*-----------GLOBAL STATIC VARIABLES-----------*/
enum IntCtrl_InerruptType
{

	INT_GPIOPORTA, INT_GPIOPORTB, INT_GPIOPORTC, INT_GPIOPORTD, INT_GPIOPORTE
	
	
	/*TODO: WRITE PORTF INTERRUPT NUMBER*/             /*PAGE 104*/
	/*TODO: WRITE THE REST OF THE INTERRUPTS NUMBERS*/ 
  
	/*RESET = 1, NMI, HARD_FAULT, MEMORY_MANAGEMENT, BUS_FAULT,
	
	USAGE_FAULT, RESERVED_7, RESERVED_8, RESERVED_9, RESERVED_10,
	
	SV_CALL, DEBUG_MONITOR, RESERVED_13, PEND_SV, SYS_TICK,*/
	
};
typedef struct
{
	uint8_t	IntCtrl_Num;
	uint8_t Main_Group_Priority_Config;
	uint8_t Sub_Group_Priority_Config;
	
}User_data_type;

typedef struct
{
	uint8_t	Port;
	uint8_t	Pin;
	uint8_t	Sensitivity;
	uint8_t	Event;
	
}User_pin_data_type;
/*-----------GLOBAL EXTERN VARIABLES-----------*/

/*-----------APIs FUNCTIONS DECLARATION-----------*/

void IntCtrl_init(const User_data_type *Config_Ptr);

void IntCtrl_PIN_Enable(const User_pin_data_type *Config_Ptr);


#endif
