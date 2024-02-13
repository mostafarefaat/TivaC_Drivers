/**
 ********************************************************************************
 * @file    GPIO.h
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


#define SYSCTL_RCGCGPIO_REG       	(*((volatile uint32 *)0x400FE608)) 			
#define SYSCTL_PRGPIO_REG         	(*((volatile uint32 *)0x400FEA08))

#define RIS 												(*((volatile uint32 *)0x400FE050))
#define RCC 												(*((volatile uint32 *)0x400FE060))
#define RCC2 												(*((volatile uint32 *)0x400FE070))


/************************************
 * TYPEDEFS
 ************************************/

/************************************
 * EXPORTED VARIABLES
 ************************************/

/************************************
 * ENUMS
************************************/


/************************************
 * STRUCTURES
 ************************************/

/************************************
 * GLOBAL FUNCTION PROTOTYPES
 ************************************/
void PLL_init(void);



#endif

