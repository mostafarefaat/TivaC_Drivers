/**
 ********************************************************************************
 * @file    app.c
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
