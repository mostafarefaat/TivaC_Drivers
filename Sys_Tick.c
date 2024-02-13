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
#include "Sys_Tick.h"
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
cb_ptr CallBack_Ptr_SysTick = NULL_PTR; 
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
void Sys_tick_init(uint32 ticks, uint8 clk_source, uint8 interrupt_config){
	/*0.DISABLE THE SYS_TIMER*/
	Write_Pin(&(STCTRL), EN_PIN, LOW);

	/*1.SET RELOAD VALUE IN STRELOAD REGISTER*/
	Write_Port(&(STRELOAD), ticks);

	/*2.RESET CURRENT VALUE IN STCURRENT REGISTER AND TO CLEAR COUNT FLAG*/
	Write_Port(&(STCURRENT), 0);

	/*3.CHOOSE SYSTEM CLK or PIOSC*/
	if(clk_source == PIOSC){
		Write_Pin(&(STCTRL), CLK_SRC_PIN, LOW);
	}
	else if(clk_source == System_CLK){
		Write_Pin(&(STCTRL), CLK_SRC_PIN, HIGH);
	}
	else{
		/*TODO: ERROR*/
	}
	/*4.ENABLE/DISABLE THE INTERRUPT*/
	if(interrupt_config == Interrupt_ON)
	{
		Write_Pin(&(STCTRL), INTEN_PIN, HIGH);
	}
	else if(interrupt_config == Interrupt_OFF)
	{
		Write_Pin(&(STCTRL), INTEN_PIN, LOW);
	}
	else{
		/*TODO: ERROR*/
	}
	
}
void Sys_tick_Start(){
	
	/*5. ENABLE THE SYS_TIMER*/
	Write_Pin(&(STCTRL), EN_PIN, HIGH);
	
}
void Sys_tick_Stop(){
	
	/*5. ENABLE THE SYS_TIMER*/
	Write_Pin(&(STCTRL), EN_PIN, LOW);
	
}
void register_systick_cb(cb_ptr Ptr)
{
	if(NULL != Ptr)
	{
		CallBack_Ptr_SysTick = Ptr;
	}	
}
void SysTick_Handler(void)
{
	if(NULL != CallBack_Ptr_SysTick)
	{
		CallBack_Ptr_SysTick();
	}

}
