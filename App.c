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
#define Config_Pins_NUM	4
/************************************
 * PRIVATE TYPEDEFS
 ************************************/

/************************************
 * STATIC VARIABLES
 ************************************/
 const cb_ptr Faults_Functions[Number_of_Faults]=  /*HardFault - BusFault - UsageFault - MemoryFault (ORDER IS IMPORTANT)*/
 {
	 
		HardFault_App_Handler, 
		BusFault_App_Handler,
		UsageFault_App_Handler ,
		MemManage_App_Handler
		 
 };

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
		{INT_GPIOPORTF,MAIN_GROUP_1,SUB_GROUP_0},
	};
	
	const User_pin_data_type g_user_pin_data[CFG_INT_NUM_PIN] =
	{
		{PORTF, PIN0, EDGE, FALLING_LOW}, 
	};
	
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
 
void App_init(void){
	
	
	Enable_Exceptions();
	Enable_Faults();
		
	SVC_Set_PRI(SVC_PRI);
	PendSV_Set_PRI(PendSV_PRI);
	BusFault_Set_PRI(BusFault_PRI);
	UsageFault_Set_PRI(MemManage_PRI);
	MemManage_Set_PRI(UsageFault_PRI);
	
	register_Faults_cb(Faults_Functions, Number_of_Faults);

	
	Enable_BusFault();
	Enable_UsageFault();
	Enable_MemoryFault();
	Disable_Divide_By_Zero();
	Disable_UnAlinged();
	
  //Switch_To_Unprivileged(); 
	//Trigger_SVC1_Exception();
	MPU_Init();
	
	error = Port_Init(PortsConfig_array, Config_Pins_NUM);
	IntCtrl_init(g_user_data);
	IntCtrl_PIN_Enable(g_user_pin_data);
	
	register_gpio_cb(GPIOF_Driver_Handler);
	register_systick_cb(SysTick_Driver_Handler);
	
	PLL_init();
	Sys_tick_init(15999999, System_CLK, Interrupt_ON, 1);
	

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
/************************************
 * Faults Handlers
 ************************************/
void HardFault_App_Handler(void){
		while(1){
		
	}
	
}
void BusFault_App_Handler(void){
	while(1){
		
	}
	
}

void MemManage_App_Handler(void){
		while(1){
		
	}
	
}
void UsageFault_App_Handler(void){
	
		while(1){
		
	}
}

/************************************
 * Helper Functions
 ************************************/

void Delay_MS(unsigned long long n){

	volatile uint64 count = 0;
	while( count++ < (NUMBER_OF_ITERATIONS_FOR_ONE_MILLI_SECOND * n));
}


uint32 Divide(uint32 num1,uint32 num2)
{
    return num1/num2;
}

