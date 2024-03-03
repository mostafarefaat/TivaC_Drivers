/**
 ********************************************************************************
 * @file    MCU.h
 * @author  Mostafa Refaat
 * @date    31/1/2024
 * @brief   
 ********************************************************************************
 */

#ifndef PLL_H_
#define PLL_H_

/************************************
 * INCLUDES
 ************************************/
#include "..\GPIO\GPIO.h"

/************************************
 * MACROS AND DEFINES
 ************************************/
 
 /* Go to low power mode while waiting for the next interrupt */
#define Wait_For_Interrupt()   __asm(" WFI ")
 
/*****************************************************************************
Faults & Exceptions Calls and Registers
*****************************************************************************/
#define Enable_Exceptions()					__asm("CPSIE I")
#define Disable_Exceptions()				__asm("CPSID I")					/*Blocks all Exceptions except Reset & NMI & HardFault*/
#define Enable_Faults()							__asm("CPSIE F")
#define Disable_Faults()						__asm("CPSID F")  				/*Blocks all Exceptions except Reset & NMI*/

#define SYSPRI1												*((volatile uint32 *)0xE000ED18) 		/*System Handler Priority 1 Reg*/
#define BusFault_PRI_Mask							0xFFFF1FFF							/*BusFault Priority bit mask*/
#define UsageFault_PRI_Mask						0xFF1FFFFF							/*UsageFault Priority bit mask*/
#define MemoryFault_PRI_Mask					0xFFFFFF1F						  /*MemoryFault Priority bit mask*/
#define BusFault_Pri_Bit_Pos					13
#define UsageFault_Pri_Bit_Pos				21
#define MemoryFault_Pri_Bit_Pos				5

#define BusFault_Address							*((volatile uint32 *)0xE000ED38)


#define SYSHNDCTRL										*((volatile uint32 *)0xE000ED24)
#define Enable_BusFault()							(SYSHNDCTRL |= (1<<17))
#define Enable_UsageFault()						(SYSHNDCTRL |= (1<<18))
#define Enable_MemoryFault()					(SYSHNDCTRL |= (1<<16))

#define CFGCTRL												*((volatile uint32 *)0xE000ED14)
#define Disable_Divide_By_Zero()				(CFGCTRL |= (1<<4))
#define Disable_UnAlinged()							(CFGCTRL |= (1<<3))

/*****************************************************************************
SVC Calls and Registers
*****************************************************************************/
#define Trigger_SVC0_Exception()		__asm("SVC #0")
#define Trigger_SVC1_Exception()		__asm("SVC #1")
#define Trigger_SVC2_Exception()		__asm("SVC #2")
#define Trigger_SVC3_Exception()		__asm("SVC #3")
#define Trigger_SVC4_Exception()		__asm("SVC #4")

#define SYSPRI2 						*((volatile uint32 *)0xE000ED1C) /*System Handler Priority 2 Reg*/ 
#define SVC_PRI_Mask				0x1FFFFFFF		/*SVC Priority bit mask*/
#define SVC_Pri_Bit_Pos			29

/*****************************************************************************
PendSV Registers
*****************************************************************************/
#define INTCTRL 										*((volatile uint32 *)0xE000ED04) /*Interrupt Control and State Reg*/
#define SYSPRI3 										*((volatile uint32 *)0xE000ED20) /*System Handler Priority 3 Reg*/
#define PENDSV_PRI_Mask							0xFF1FFFFF		/*PendSV Priority bit mask*/
#define PENDSV_Pri_Bit_Pos					21	
#define PENDSV_Pending_Bit_Pos			28
#define PENDSV_unPending_Bit_Pos		27

/*****************************************************************************
Clock Registers
*****************************************************************************/
#define RCGCGPIO 										*((volatile uint32 *)0x400FE608)
#define RCGCDMA 										*((volatile uint32 *)0x400FE60C)
#define RCGCUART 										*((volatile uint32 *)0x400FE618)
#define RCGCI2C 										*((volatile uint32 *)0x400FE620)
#define RCGCCAN 										*((volatile uint32 *)0x400FE634)
#define RCGCADC 										*((volatile uint32 *)0x400FE638)
#define RCGCPWM 										*((volatile uint32 *)0x400FE640)
#define RCGCWD											*((volatile uint32 *)0x400FE600)
#define RCGCTIMER										*((volatile uint32 *)0x400FE604)	
#define RCGCWTIMER									*((volatile uint32 *)0x400FE65C)

#define PRGPIO		 									*((volatile uint32 *)( 0x400FEA08))

/*****************************************************************************
PLL 
*****************************************************************************/
#define SYSCTL_RCC2_USERCC2_MASK        0x80000000  /* USERCC2 Bit MASK */
#define SYSCTL_RCC2_BYPASS2_MASK        0x00000800  /* PLL BYPASS2 Bit MASK */
#define SYSCTL_RCC_XTAL_MASK            0x000007C0  /* XTAL Bits MASK */
#define SYSCTL_RCC_XTAL_8MHZ            0x0E        /* 8 MHz Crystal Value */
#define SYSCTL_RCC_XTAL_16MHZ           0x15        /* 16 MHz Crystal Value */
#define SYSCTL_RCC_XTAL_BIT_POS         6           /* XTAL Bits Position start from bit number 6 */
#define SYSCTL_RCC2_OSCSRC2_MASK        0x00000070  /* OSCSRC2 Bits MASK */
#define SYSCTL_RCC2_OSCSRC2_MOSC        0x0         /* MOSC(Main Oscillator) value */
#define SYSCTL_RCC2_OSCSRC2_BIT_POS     4           /* OSCSRC2 Bits Position start from bit number 4 */
#define SYSCTL_RCC2_PWRDN2_MASK         0x00002000  /* PWRDN2 Bit MASK */
#define SYSCTL_RCC2_DIV400_MASK         0x40000000  /* DIV400 Bit MASK to Divide PLL as 400 MHz vs. 200 */
#define SYSCTL_RCC2_SYSDIV2_MASK        0x1FC00000  /* SYSDIV2 Bits MASK */
#define SYSCTL_RIS_PLLLRIS_MASK         0x00000040  /* PLLLRIS Bit MASK */
#define SYSCTL_RCC2_SYSDIV2_BIT_POS     22          /* SYSDIV2 Bits Position start from bit number 22 */
#define SYSDIV2_VALUE_80MHZ             4						
#define SYSDIV2_VALUE_10MHZ             39

#define USERCC2													31
#define BYPASS2													11
#define PWRDN2													13
#define DIV400													30

#define RIS 												(*((volatile uint32 *)0x400FE050))
#define RCC 												(*((volatile uint32 *)0x400FE060))
#define RCC2 												(*((volatile uint32 *)0x400FE070))
	
/*****************************************************************************
MPU Registers
*****************************************************************************/

/* Data memory barrier instruction */
#define DMB()                  __asm(" DMB ")

/* Data synchronization barrier instruction */
#define DSB()                  __asm(" DSB ")

/* Instruction synchronization barrier instruction */
#define ISB()                  __asm(" ISB ")

#define MPU_ATTR_SIZE_BITS_POS                    1
#define MPU_ATTR_AP_BITS_POS                      24
#define MPU_ATTR_REGION_ENABLE_MASK           0x00000001
#define MPU_ATTR_B_MASK                       0x00010000
#define MPU_ATTR_C_MASK                       0x00020000
#define MPU_ATTR_S_MASK                       0x00040000
#define MPU_BASE_VALID_MASK                   0x00000010
#define MPU_CTRL_ENABLE_MASK                  0x00000001
#define MPU_CTRL_PRIVDEFEN_MASK               0x00000004

#define MPU_TYPE_REG              (*((volatile uint32 *)0xE000ED90))
#define MPU_CTRL_REG              (*((volatile uint32 *)0xE000ED94))
#define MPU_NUMBER_REG            (*((volatile uint32 *)0xE000ED98))
#define MPU_BASE_REG              (*((volatile uint32 *)0xE000ED9C))
#define MPU_ATTR_REG              (*((volatile uint32 *)0xE000EDA0))
#define MPU_BASE1_REG             (*((volatile uint32 *)0xE000EDA4))
#define MPU_ATTR1_REG             (*((volatile uint32 *)0xE000EDA8))
#define MPU_BASE2_REG             (*((volatile uint32 *)0xE000EDAC))
#define MPU_ATTR2_REG             (*((volatile uint32 *)0xE000EDB0))
#define MPU_BASE3_REG             (*((volatile uint32 *)0xE000EDB4))
#define MPU_ATTR3_REG             (*((volatile uint32 *)0xE000EDB8))

/************************************
 * TYPEDEFS
 ************************************/
typedef uint8		MODULE_TYPE;
/************************************
 * EXPORTED VARIABLES
 ************************************/

/************************************
 * ENUMS
************************************/
 enum Module
 {
	 GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, DMA, UART_0, I2C, CAN, ADC, PWM, WDT0, WDT1,	/*PAGE 104*/
	 
	 Timer_0_module_16_32, Timer_1_module_16_32, Timer_2_module_16_32, Timer_3_module_16_32, Timer_4_module_16_32, Timer_5_module_16_32,
	 
	 Timer_0_module_32_64, Timer_1_module_32_64, Timer_2_module_32_64, Timer_3_module_32_64, Timer_4_module_32_64, Timer_5_module_32_64,
	 
 };

/************************************
 * STRUCTURES
 ************************************/

/************************************
 * GLOBAL FUNCTION PROTOTYPES
 ************************************/
void PLL_init(void);
 void MPU_Init(void);
void Module_Clk_init(MODULE_TYPE module);
void Module_Clk_Deinit(MODULE_TYPE module);
 
void SVC_Handler(void);
void Switch_To_Unprivileged(void);
void SVC_Set_PRI(uint8 Priority);
void PendSV_Pend(void);
void PendSV_unPend(void);
void PendSV_Set_PRI(uint8 Priority);
void PendSV_Handler(void);
 
void BusFault_Set_PRI(uint8 Priority);
void BusFault_Handler(void);
void MemManage_Set_PRI(uint8 Priority);
void MemManage_Handler(void); 
void UsageFault_Set_PRI(uint8 Priority);
void UsageFault_Handler(void);
void HardFault_Handler(void);

void register_Faults_cb(const cb_ptr *Ptr, uint8 size);

#endif

