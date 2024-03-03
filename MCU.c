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
cb_ptr CallBack_Ptr_HardFault = NULL_PTR;
cb_ptr CallBack_Ptr_BusFault = NULL_PTR;
cb_ptr CallBack_Ptr_UsageFault = NULL_PTR;
cb_ptr CallBack_Ptr_MemoryFault = NULL_PTR;
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
		case UART_0:	
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
		case UART_0:	
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

void MPU_Init(void)
{
    /* Enable the MemManage Fault Exception */
    Enable_MemoryFault();
    /* Check if this target supports MPU or not */
    if(MPU_TYPE_REG == 0)
        return;

    /* Ensures all memory accesses are finished before a fresh memory access is made */
    DMB();

    /* Disable the MPU before start programming the memory regions */
    MPU_CTRL_REG = 0;

    /********************** Programming Region 0 - Flash memory (256KB) **********************
     * Normal Memory, Cacheable, Not Shareable and Write Through
     * Base Address 0x00000000
     * Region Size 256KB --> SIZE field in the attribute register should be 0x11
     * Privilege has FULL ACCESS (RW) --> AP field in the attribute register should be 0x03
     * Non-Privilege has FULL ACCESS (RW) --> AP field in the attribute register should be 0x03
     ******************************************************************************************/

    /* Update the region number */
    MPU_NUMBER_REG = 0;

    /* Update the region base address */
    MPU_BASE_REG = 0x00000000;

    /* Update the region size and attributes */
    MPU_ATTR_REG = (0x11<<MPU_ATTR_SIZE_BITS_POS) | MPU_ATTR_REGION_ENABLE_MASK | 
            MPU_ATTR_C_MASK | (0x03 << MPU_ATTR_AP_BITS_POS);

    /*************************** Programming Region 1 - SRAM (32KB) *************************
     * Normal Memory, Cacheable, Shareable and Write Through
     * Base Address 0x20000000
     * Region Size 32KB --> SIZE field in the attribute register should be 0x0E
     * Privilege has FULL ACCESS (RW) --> AP field in the attribute register should be 0x03
     * Non-Privilege has FULL ACCESS (RW) --> AP field in the attribute register should be 0x03
     *****************************************************************************************/

    /* Update the region base address and region number */
    MPU_BASE_REG = 0x20000000 | MPU_BASE_VALID_MASK | 1;

    /* Update the region size and attributes */
    MPU_ATTR_REG = (0x0E << MPU_ATTR_SIZE_BITS_POS) | MPU_ATTR_REGION_ENABLE_MASK |
            MPU_ATTR_C_MASK | MPU_ATTR_S_MASK | (0x03 << MPU_ATTR_AP_BITS_POS);

    /******************** Programming region 2 - PORTF Memory Map Area **********************
     * Device Memory Sharable and Bufferable
     * Base Address 0x40025000
     * region Size 4k(0x1000) --> SIZE field in the attribute register should be 0x0B
     * Privilege has FULL ACCESS (RW) --> AP field in the attribute register should be 0x03
     * Non-Privilege has FULL ACCESS (RW) --> AP field in the attribute register should be 0x03
     *****************************************************************************************/

    /* Update the region base address and region number */
    MPU_BASE_REG = 0x40025000 | MPU_BASE_VALID_MASK | 2;

    /* Update the region size and attributes */
    MPU_ATTR_REG = (0x0B << MPU_ATTR_SIZE_BITS_POS) | MPU_ATTR_REGION_ENABLE_MASK |
            MPU_ATTR_B_MASK | MPU_ATTR_S_MASK | (0x03 << MPU_ATTR_AP_BITS_POS);

    /* Enable the MPU */
    MPU_CTRL_REG |= MPU_CTRL_ENABLE_MASK;

    /* Ensures all memory accesses are finished before the next instruction is executed */
    DSB();

    /* Ensures that all previous instructions are completed before the next instruction is executed. This also flushes the CPU pipeline */
    ISB();
}

/* Set PRIV Bit(Bit 0) in the CONTROL register to switch to Unprivileged access level */
void Switch_To_Unprivileged(void)
{
    __asm(" MOV R0, #1 ");      /* Set the R0 register value to 1 */
    __asm(" MSR CONTROL, R0 "); /* Set the PRIV Bit(Bit 0) to 1 ... This will switch to Unprivileged access level */
}
void SVC_Handler(void){

uint8 SVC_Num = 0;              /* First local variable stored in stack */
    __asm(" LDR  R3, [__current_sp(), #24] ");   /* Extract the stacked PC register value which vectoring to this handler and add it to R3 */
    __asm(" LDRB R3, [R3, #-2] ");  /* Extract the SVC number value, it is exist in the first byte of address PC-2 */
    __asm(" MOV #SVC_Num, R3 ");        /* Load the R3 value to SVC_Num variable as SP is pointing to SVC_Num location in the stack memory */
	
	switch(SVC_Num){
		
		case 0 :   break;
		case 1 :         __asm(" MOV R3, #0 ");      /* Load the R3 register with value 0 */
										 __asm(" MSR CONTROL, R3 "); /* Clear the PRIV Bit(Bit 0) ... This will switch to Privileged access level */
							 break;
		case 2 : 	 break;
		case 3 :   break;
		case 4 : 	 break;
		default :  break;
	}
   
}
void SVC_Set_PRI(uint8 Priority){
	
	SYSPRI2 &= SVC_PRI_Mask;
	SYSPRI2 |= Priority << SVC_Pri_Bit_Pos;
}


void PendSV_Pend(void){
	
	Write_Pin(&INTCTRL, PENDSV_Pending_Bit_Pos, HIGH);
	
}
void PendSV_unPend(void){
	
	Write_Pin(&INTCTRL, PENDSV_unPending_Bit_Pos, HIGH);
	
}
void PendSV_Set_PRI(uint8 Priority){
	
	SYSPRI3 &= PENDSV_PRI_Mask;
	SYSPRI3 |= Priority << PENDSV_Pri_Bit_Pos;
	
}
void PendSV_Handler(void){
	
	/*Write Code here*/
}
void BusFault_Set_PRI(uint8 Priority){
	SYSPRI1 &= BusFault_PRI_Mask;
	SYSPRI1 |= Priority << BusFault_Pri_Bit_Pos;
	
}

void MemManage_Set_PRI(uint8 Priority){
	SYSPRI1 &= MemoryFault_PRI_Mask;
	SYSPRI1 |= Priority << MemoryFault_Pri_Bit_Pos;
	
}

void UsageFault_Set_PRI(uint8 Priority){
	SYSPRI1 &= UsageFault_PRI_Mask;
	SYSPRI1 |= Priority << UsageFault_Pri_Bit_Pos;
	
}

void register_Faults_cb( const cb_ptr *Ptr, uint8 size)
{
	int i;
	for( i = 0; i<size; i++){
		if(NULL_PTR != *Ptr)
		{
			switch(i){
				case 0: CallBack_Ptr_HardFault = *Ptr; break;
				case 1: CallBack_Ptr_BusFault = *Ptr; break;
				case 2: CallBack_Ptr_UsageFault = *Ptr; break;
				case 3: CallBack_Ptr_MemoryFault = *Ptr; break;
				default: break;
			}
		}
			Ptr++;
	}
}

void HardFault_Handler(void){
	if(NULL_PTR != CallBack_Ptr_HardFault)
	{
		CallBack_Ptr_HardFault();
	}
	
}
void BusFault_Handler(void){
	if(NULL_PTR != CallBack_Ptr_BusFault)
	{
		CallBack_Ptr_BusFault();
	}
	
}
void UsageFault_Handler(void){
	if(NULL_PTR != CallBack_Ptr_UsageFault)
	{
		CallBack_Ptr_UsageFault();
	}
	
}
void MemManage_Handler(void){
	if(NULL_PTR != CallBack_Ptr_MemoryFault)
	{
		CallBack_Ptr_MemoryFault();
	}
	
}


