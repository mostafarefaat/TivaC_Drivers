/*-----------INCLUDES-----------*/
#include "Mcu.h"
#include "math.h"
/*-----------LOCAL MACROS-----------*/
uint8_t INT_on = 0;
uint8_t SYS_TICK_INT_SERVED = 0;
/*-----------GLOBAL STATIC VARIABLES-----------*/
static STR_RELOAD_TYPE reload_value = 0;
static STR_CONTROL_TYPE clk_source = 0;
static STR_CONTROL_TYPE interrupt_config = 0;

cb_type CallBack_Ptr_mcu = NULL;
/*-----------GLOBAL EXTERN VARIABLES-----------*/

/*-----------APIs IMPLEMENTATION-----------*/

void Sys_Timer_init(const Clk_user_Config *clk_config_Ptr)
{
	
	clk_source =  clk_config_Ptr->Clk_Souce;
	
	interrupt_config =  clk_config_Ptr->INT_Config;
	
	/*1.CONFIG STCTRL REGISTER FOR REQUIRED OPERATION*/
	/*1.1 CLOCK SOURCE*/
	if(clk_source == PIOSC)
	{
		Dio_Write_Pin(&(STCTRL), CLK_SRC_PIN, LOW);
	}
	else if(clk_source == SYSTEM_CLK)
	{
		Dio_Write_Pin(&(STCTRL), CLK_SRC_PIN, HIGH);
	}
	/*2. INTERRUPT ENABLE OR DISABLE*/
	if(interrupt_config == INTERRUPT_ON)
	{
		Dio_Write_Pin(&(STCTRL), INTEN_PIN, HIGH);
		INT_on = 1 ;
	}
	else if(interrupt_config == INTERRUPT_OFF)
	{
		Dio_Write_Pin(&(STCTRL), INTEN_PIN, LOW);
	}
	
  Dio_Write_Pin(&(STCTRL), EN_PIN, HIGH);
}

void Sys_Timer_delay_1sec(uint32_t ticks)
{
		//uint8_t counts = 0;
		/*1.SET RELOAD VALUE IN STRELOAD REGISTER*/				
		Dio_Write_Port(&(STRELOAD), ticks-1);
	
		/*2.RESET CURRENT VALUE IN STCURRENT REGISTER AND TO CLEAR COUNT FLAG*/
		Dio_Write_Port(&(STCURRENT), CURRENT_VALUE_RESET);
	
		/*4. ENABLE THE SYS_TIMER*/
		Dio_Write_Pin(&(STCTRL), EN_PIN, HIGH);
		
		while((Dio_Read_Pin(&(STCTRL),PIN16))== 0 && (SYS_TICK_INT_SERVED == 0) )	{}
		SYS_TICK_INT_SERVED = 0;
}

void Sys_Timer_delay(uint32_t ticks)
{
	if(ticks > SYS_TIMER_MAX_VALUE)
	{
		uint8_t counts = 0;
		uint8_t i = 0;
		counts = ceil(ticks / SYS_TIMER_1sec_VALUE );
		Dio_Write_Pin(&(STCTRL), INTEN_PIN, LOW);
		
		for(i = 0; i< counts; i++)
		{
			if((INT_on == 1) && (i == (counts-1)))
			{
				Dio_Write_Pin(&(STCTRL), INTEN_PIN, HIGH);
			}
			
			Sys_Timer_delay_1sec(SYS_TIMER_1sec_VALUE);
		}	
	}
	else 
	{
		/*1.SET RELOAD VALUE IN STRELOAD REGISTER*/				
		Dio_Write_Port(&(STRELOAD), ticks-1);
	
		/*2.RESET CURRENT VALUE IN STCURRENT REGISTER AND TO CLEAR COUNT FLAG*/
		Dio_Write_Port(&(STCURRENT), CURRENT_VALUE_RESET);
	
		/*4. ENABLE THE SYS_TIMER*/
		Dio_Write_Pin(&(STCTRL), EN_PIN, HIGH);
	}	
	
	
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
	
void register_systick_cb(cb_type Ptr)
{
	if(NULL != Ptr)
	{
		CallBack_Ptr_mcu = Ptr;
	}	
}
void SysTick_Handler(void)
{
	if(NULL != CallBack_Ptr_mcu)
	{
		CallBack_Ptr_mcu();
	}

}
