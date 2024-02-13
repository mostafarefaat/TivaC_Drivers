/**
 ********************************************************************************
 * @file    MCU.c
 * @author  Mostafa Refaat
 * @date    31/1/2024
 * @brief   
 ********************************************************************************
 */

/************************************
 * INCLUDES
 ************************************/
#include "MCU.h"
/************************************
 * EXTERN VARIABLES
 ************************************/

/************************************
 * PRIVATE MACROS AND DEFINES
 ************************************/

/************************************
 * PRIVATE TYPEDEFS
 ************************************/

/************************************
 * STATIC VARIABLES
 ************************************/

/************************************
 * GLOBAL VARIABLES
 ************************************/

/************************************
 * STATIC FUNCTION PROTOTYPES
 ************************************/

/************************************
 * STATIC FUNCTIONS
 ************************************/

/************************************
 * GLOBAL FUNCTIONS
 ************************************/
void PLL_init(){
	/*1.Configure the system to use RCC2 for advanced features such as 400 MHz PLL and non-integer System Clock Divisor*/
	RCC2 |= SYSCTL_RCC2_USERCC2_MASK;
	/*2.Bypass PLL while initializing, Don t use PLL while initialization*/
	RCC2 |= SYSCTL_RCC2_BYPASS2_MASK;
	/*3.Select the crystal value and oscillator source -- configure for main oscillator source */
	RCC &= ~(SYSCTL_RCC_XTAL_MASK);
	RCC |=  (SYSCTL_RCC_XTAL_16MHZ << SYSCTL_RCC_XTAL_BIT_POS);

	RCC2 &= ~(SYSCTL_RCC2_OSCSRC2_MASK);
	RCC2 |= (SYSCTL_RCC2_OSCSRC2_MOSC<<SYSCTL_RCC2_OSCSRC2_BIT_POS);
	/*4.Activate PLL by clearing PWRDN2*/
	RCC2 &= ~(SYSCTL_RCC2_PWRDN2_MASK);
	/*5.Set the desired system divider and the system divider least significant bit*/
	RCC2 &= ~ (SYSCTL_RCC2_DIV400_MASK);
	RCC2 |= 	 SYSCTL_RCC2_DIV400_MASK;
	
	RCC2 &= ~ (SYSCTL_RCC2_SYSDIV2_MASK);
	RCC2 |= 	(SYSDIV2_VALUE_80MHZ << SYSCTL_RCC2_SYSDIV2_BIT_POS);
	/*6.Wait for the PLL to lock by polling PLLLRIS bit*/
	while(!(RIS & SYSCTL_RIS_PLLLRIS_MASK));
	/*7.Enable use of PLL by clearing BYPASS2*/
	RCC2 &= ~(SYSCTL_RCC2_BYPASS2_MASK);
}

void Module_Clk_init(MODULE_TYPE module)
{
	switch(module)
	{
		case GPIOA: RCGCGPIO |= (1<<PORTA);
		break;
		case GPIOB: RCGCGPIO |= (1<<PORTB);
		break;
		case GPIOC: RCGCGPIO |= (1<<PORTC);
		break;
		case GPIOD: RCGCGPIO |= (1<<PORTD);
		break;
		case GPIOE: RCGCGPIO |= (1<<PORTE);
		break;
		case GPIOF: RCGCGPIO |= (1<<PORTF);
		break;
		/*TODO: COMPLETE THE MODULES*/
	  case DMA:	
		break;
		case UART:	
		break;
		case I2C:
		break;
		case CAN:
		break;
		case ADC:
		break;
		case PWM:
		break;
		case WDT0: RCGCWD |= (1<<PIN0);
		break;		
		case WDT1: RCGCWD |= (1<<PIN1);
		break;
		case Timer_0_module_16_32: RCGCTIMER |= (1<<PIN0);
		break;
		case Timer_1_module_16_32: RCGCTIMER |= (1<<PIN1);
		break;
		case Timer_2_module_16_32: RCGCTIMER |= (1<<PIN2);
		break;
		case Timer_3_module_16_32: RCGCTIMER |= (1<<PIN3);
		break;
		case Timer_4_module_16_32: RCGCTIMER |= (1<<PIN4);
		break;
		case Timer_5_module_16_32: RCGCTIMER |= (1<<PIN5);
		break;
		case Timer_0_module_32_64: RCGCWTIMER |= (1<<PIN0);
		break;
		case Timer_1_module_32_64: RCGCWTIMER |= (1<<PIN1);
		break;
		case Timer_2_module_32_64: RCGCWTIMER |= (1<<PIN2);
		break;
		case Timer_3_module_32_64: RCGCWTIMER |= (1<<PIN3);
		break;
		case Timer_4_module_32_64: RCGCWTIMER |= (1<<PIN4);
		break;
		case Timer_5_module_32_64: RCGCWTIMER |= (1<<PIN5);
		break;
	}
	
}

void Module_Clk_Deinit(MODULE_TYPE module)
{
	switch(module)
	{
		case GPIOA: RCGCGPIO &= ~(1U<<PORTA);
		break;
		case GPIOB: RCGCGPIO &= ~(1U<<PORTB);
		break;
		case GPIOC: RCGCGPIO &= ~(1U<<PORTC);
		break;
		case GPIOD: RCGCGPIO &= ~(1U<<PORTD);
		break;
		case GPIOE: RCGCGPIO &= ~(1U<<PORTE);
		break;
		case GPIOF: RCGCGPIO &= ~(1U<<PORTF);
		break;
		/*TODO: COMPLETE THE MODULES*/
	  case DMA:	
		break;
		case UART:	
		break;
		case I2C:
		break;
		case CAN:
		break;
		case ADC:
		break;
		case PWM:
		break;
		case WDT0: RCGCWD &= ~(1U<<PIN0);
		break;		
		case WDT1: RCGCWD &= ~(1U<<PIN1);
		break;
		case Timer_0_module_16_32: RCGCTIMER &= ~(1<<PIN0);
		break;
		case Timer_1_module_16_32: RCGCTIMER &= ~(1<<PIN1);
		break;
		case Timer_2_module_16_32: RCGCTIMER &= ~(1<<PIN2);
		break;
		case Timer_3_module_16_32: RCGCTIMER &= ~(1<<PIN3);
		break;
		case Timer_4_module_16_32: RCGCTIMER &= ~(1<<PIN4);
		break;
		case Timer_5_module_16_32: RCGCTIMER &= ~(1<<PIN5);
		break;
		case Timer_0_module_32_64: RCGCWTIMER &= ~(1<<PIN0);
		break;
		case Timer_1_module_32_64: RCGCWTIMER &= ~(1<<PIN1);
		break;
		case Timer_2_module_32_64: RCGCWTIMER &= ~(1<<PIN2);
		break;
		case Timer_3_module_32_64: RCGCWTIMER &= ~(1<<PIN3);
		break;
		case Timer_4_module_32_64: RCGCWTIMER &= ~(1<<PIN4);
		break;
		case Timer_5_module_32_64: RCGCWTIMER &= ~(1<<PIN5);
		break;
		
	}
	
}
