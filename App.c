/**
 ********************************************************************************
 * @file    App.c
 * @author  Mostafa Refaat
 * @date    31/1/2024
 * @brief   
 ********************************************************************************
 */

/************************************
 * INCLUDES
 ************************************/
#include "App.h"
/************************************
 * EXTERN VARIABLES
 ************************************/

/************************************
 * PRIVATE MACROS AND DEFINES
 ************************************/
#define Config_Pins_NUM			4
/************************************
 * PRIVATE TYPEDEFS
 ************************************/

/************************************
 * STATIC VARIABLES
 ************************************/

/************************************
 * GLOBAL VARIABLES
 ************************************/
uint8 error = 0;
uint8 Sw1_pressed = 0;
uint8 Sys_Timer_Start = 0;
uint8 ticks = 0;
uint8 SysTick_OverFlow = 0;
/************************************
 * STATIC FUNCTION PROTOTYPES
 ************************************/

/************************************
 * STATIC FUNCTIONS
 ************************************/

/************************************
 * GLOBAL FUNCTIONS
 ************************************/
const Port_ConfigType PortsConfig_array[Config_Pins_NUM] =  /*Port - Pin - Mode - AlterMode - Dir - Level - Current - InternalAttach*/
	{
		/*RGB Leds init*/
		{PORTF, PIN1, DEN, NULL, OUTPUT, LOW,  CURRENT_2mA, NULL},
		
		{PORTF, PIN2, DEN, NULL, OUTPUT, LOW,  CURRENT_2mA, NULL},
		
		{PORTF, PIN3, DEN, NULL, OUTPUT, LOW,  CURRENT_2mA, NULL},
		
		/*Switch_1 init*/
		{PORTF, PIN0, DEN, NULL, INTPUT, NULL,  CURRENT_2mA, PUR},
		
	};
	
	const User_data_type g_user_data[CFG_INT_NUM_MODULES] = 
	{
		{INT_GPIOPORTF,MAIN_GROUP_0,SUB_GROUP_0},
	};
	
	const User_pin_data_type g_user_pin_data[CFG_INT_NUM_PIN] =
	{
		{PORTF, PIN0, EDGE, FALLING_LOW}, 
	};
	
	
void Delay_MS(unsigned long long n){

	volatile uint64 count = 0;
	while( count++ < (NUMBER_OF_ITERATIONS_FOR_ONE_MILLI_SECOND * n));
}


void App_init(void){
	
	/*GPIO init*/
	error = Port_Init(PortsConfig_array, Config_Pins_NUM);

	/*NVIC init*/
	IntCtrl_init(g_user_data);
	IntCtrl_PIN_Enable(g_user_pin_data);

	/*Call Back init*/
	register_gpio_cb(GPIOF_Driver_Handler);
	register_systick_cb(SysTick_Driver_Handler);

	/*PLL_init*/
	PLL_init();

	/*Sys_Tick*/
	Sys_tick_init(15999999, System_CLK, Interrupt_ON);
}
void App_run(void){
	if(error != 1){
		
		if(Sys_Timer_Start == 0){Sys_tick_Start(); Sys_Timer_Start = 1;}
		
		//Delay_MS(1000); //while((Read_Pin(&(STCTRL),COUNT_FLAG_PIN)) == 0);
	}
}

void GPIOF_Driver_Handler(void)
{
	
	GPIOICR(PORTF) |= (1U<<PIN0); //Clear Interrupt Flag
	PF1 = bit_1_high;
	PF2 = bit_2_high;
	PF3 = bit_3_high;
	
}

void SysTick_Driver_Handler(void)
{
		//RESET CURRENT VALUE IN STCURRENT REGISTER AND TO CLEAR COUNT FLAG
	Write_Port(&(STCURRENT), CURRENT_VALUE_RESET);
	
	if(SysTick_OverFlow < 4){
		
		SysTick_OverFlow++;
		
	}
	else{
		SysTick_OverFlow = 0;
		ticks++;
	
		if(ticks == 1){
			PF1 = bit_1_high;
			PF2 = 0x00;
			PF3 = 0x00;
			}
		else if(ticks == 2){
			PF1 = 0x00;
			PF2 = bit_2_high;
			PF3 = 0x00;
			}
		else if(ticks == 3){
			PF1 = 0x00;
			PF2 = 0x00;
			PF3 = bit_3_high;
			ticks = 0;
			}
	}
	
}



