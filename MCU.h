#ifndef  MCU_H_
#define  MCU_H_
/*-----------INCLUDES-----------*/
#include "..\DIO\Dio.h"

typedef uint32_t 		STR_RELOAD_TYPE;
typedef uint32_t 		STR_CURRENT_TYPE;
typedef uint8_t 		STR_CONTROL_TYPE;
typedef uint8_t 		MODULE_TYPE;
/*-----------LOCAL MACROS-----------*/

#define BASE_ADDRESS					0XE000E000
#define RELOAD_VALUE_MASK			0xFFFFFF
#define CURRENT_VALUE_RESET		0X00000000
#define SYS_TIMER_MAX_VALUE		16777215
#define SYS_TIMER_1sec_VALUE	16000000
#define	PIOSC									16000000.0
#define	SYSTEM_CLK						1
#define	INTERRUPT_ON					1
#define	INTERRUPT_OFF					0


/*-----------STCTRL PINS-----------*/
#define EN_PIN						0
#define INTEN_PIN					1
#define CLK_SRC_PIN				2
#define COUNT_PIN					16

/*-----------SYSTEM TIMER REGISTERS-----------*/ 
#define STCTRL 			 		*((volatile uint32_t *)(BASE_ADDRESS + 0x010))
#define STRELOAD 			 	*((volatile uint32_t *)(BASE_ADDRESS + 0x014))
#define STCURRENT 			*((volatile uint32_t *)(BASE_ADDRESS + 0x018))
	
/*-----------SYSTEM CONTROL REGISTERS-----------*/  /*PAGE 232*/

#define RCGCGPIO 		*((volatile uint32_t *)0x400FE608)
#define RCGCDMA 		*((volatile uint32_t *)0x400FE60C)
#define RCGCUART 		*((volatile uint32_t *)0x400FE618)
#define RCGCI2C 		*((volatile uint32_t *)0x400FE620)
#define RCGCCAN 		*((volatile uint32_t *)0x400FE634)
#define RCGCADC 		*((volatile uint32_t *)0x400FE638)
#define RCGCPWM 		*((volatile uint32_t *)0x400FE640)
#define RCGCWD			*((volatile uint32_t *)0x400FE600)
#define RCGCTIMER			*((volatile uint32_t *)0x400FE604)	
#define RCGCWTIMER			*((volatile uint32_t *)0x400FE65C)


#define PRGPIO		 	*((volatile uint32_t *)( 0x400FEA08))

/*-----------END OF MCU REGISTERS-----------*/


/*-----------GLOBAL STATIC VARIABLES-----------*/

 typedef struct
 {
	 STR_CONTROL_TYPE		Clk_Souce;
	 STR_CONTROL_TYPE		INT_Config;
	 
	 
 }Clk_user_Config;
 
 enum Module
 {
	 GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, DMA, UART, I2C, CAN, ADC, PWM, WDT0, WDT1,	/*PAGE 104*/
	 Timer_0_module_16_32, Timer_1_module_16_32, Timer_2_module_16_32, Timer_3_module_16_32, Timer_4_module_16_32, Timer_5_module_16_32,
	 Timer_0_module_32_64, Timer_1_module_32_64, Timer_2_module_32_64, Timer_3_module_32_64, Timer_4_module_32_64, Timer_5_module_32_64,
	 
 };
	
/*-----------GLOBAL EXTERN VARIABLES-----------*/
 

/*-----------APIs FUNCTIONS DECLARATION-----------*/
void Sys_Timer_init(const Clk_user_Config *clk_config_Ptr );
void Sys_Timer_delay_1sec(uint32_t ticks);
void Sys_Timer_delay(uint32_t ticks);
void Module_Clk_init(MODULE_TYPE module);
void Module_Clk_Deinit(MODULE_TYPE module);
 
void register_systick_cb(cb_type Ptr);

void SysTick_Handler(void);

//STR_RELOAD_TYPE reload_value_hex, STR_CONTROL_TYPE clk_source, STR_CONTROL_TYPE interrupt_config

#endif
