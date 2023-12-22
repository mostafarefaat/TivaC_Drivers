
/*-----------INCLUDES-----------*/
#include "INTCtrl.h"
/*-----------LOCAL MACROS-----------*/

/*-----------GLOBAL STATIC VARIABLES-----------*/

/*-----------GLOBAL EXTERN VARIABLES-----------*/

/*----------LOCAL FUNCTIONS-----------*/
static void SetPriorityGrouping(Group_SubgroupType PriorityGrouping); /*TO SET THE PRIORITY SCHEME IN THE SYSTEM*/
static void IntCtrl_SetPriority(IntCtrl_InterruptType Int_Num, uint8_t Int_Priority); 
static void IntCtrl_EnableInterrupt(IntCtrl_InterruptType Int_Num);
static void IntCtrl_DisableInterrupt(IntCtrl_InterruptType Int_Num);
/*-----------APIs IMPLEMENTATION-----------*/		/*TODO: GUARD CONDITIONS FOR THE POINTERS IF THEY ARE NULL*/


void IntCtrl_init(const User_data_type *Config_Ptr)
{
	uint8_t idx = 0;
	
	/*SET THE PRIORITY SCHEME FOR THE SYSTEM (HOW MANY MAIN_GROUPS AND SUB_GROUPS)*/
	SetPriorityGrouping(GroupsPriority_Config);
	
	for(idx = 0; idx < CFG_INT_NUM; idx++)
	{
		uint8_t IntPriority = 0;
		uint8_t GroupPriority = Config_Ptr[idx].Main_Group_Priority_Config;
		uint8_t Sub_GroupPriority = Config_Ptr[idx].Sub_Group_Priority_Config;
		uint8_t Int_Num = Config_Ptr[idx].IntCtrl_Num;
		
		if(GroupsPriority_Config <= 4)
		{
			IntPriority = GroupPriority;
		}
		else if(USE_4_GROUPS_2_SUBGROUPS == GroupsPriority_Config)
		{
			IntPriority = ((GroupPriority & 0x03) << 1UL) | ((Sub_GroupPriority & 0x01) << 0);
		}
		else if(USE_2_GROUPS_4_SUBGROUPS == GroupsPriority_Config)
		{
			IntPriority = ((GroupPriority & 0x01) << 2UL) | ((Sub_GroupPriority & 0x03) << 0);
		}
		else if(USE_ALL_SUBGROUPS == GroupsPriority_Config)
		{
			IntPriority = Sub_GroupPriority;
		}
		else
		{
			/*TODO: INVALID CFG, RETURN ERROR*/
		}
		IntCtrl_SetPriority(Int_Num, IntPriority);
		
		IntCtrl_EnableInterrupt(Int_Num);	
		
		//IntCtrl_DisableInterrupt(Int_Num);
	}
	
}

static void SetPriorityGrouping(Group_SubgroupType PriorityGrouping)
{
	uint32_t PriorityGrouping_TEMP;
	uint32_t APINT_TEMP;
	
	APINT_TEMP = APINT;
	
	APINT_TEMP &= APINT_PRIGROUP_MSK; /*SAVING DATA FROM BIT _11 TO BIT_15 AND FROM BIT_0 TO BIT_7*/
	
	PriorityGrouping_TEMP = ( (uint32_t)PriorityGrouping & 7UL); /*GUARD THE CHOICE, TAKE FIRST THREE BITS ONLY*/
	

	APINT = APINT_TEMP | (VECT_KEY << APINT_VECT_KEY_POS) | (PriorityGrouping_TEMP << APINT_PRIGROUP_POS) ;
	
	
}
static void IntCtrl_SetPriority(IntCtrl_InterruptType Int_Num, uint8_t Int_Priority)
{
	uint32_t Interrupt_Priority =  (Int_Priority & 0x07); /*TO MAKE SURE THE NUMBER IS LESS THAN OR EQUAL  7 */
		 
		if(Int_Num < 0x8A)			/*TO MAKE SURE THE NUMBER IS LESS THAN OR EQUAL 138 */
	{
		if(Int_Num % 2 == 0)
		{
			if(Int_Num % 4 == 0)
			{
				PRIx(Int_Num) |= (Interrupt_Priority << 5 );
				/*5:7*/
			}
			else
			{
				PRIx(Int_Num) |= (Interrupt_Priority << 21 );
				/*21:23*/
			}
		}
		else if((Int_Num - 1) % 4 == 0)
		{
			PRIx(Int_Num) |= (Interrupt_Priority << 13 );
			/*13:15*/
		}
		else
		{
			PRIx(Int_Num) |= (Interrupt_Priority << 29 );
			/*29:31*/
		}		
	}
	else
	{
		/*TODO: INVALID INTERRUPT NUMBER, RETURN ERROR*/
	}

}
static void IntCtrl_EnableInterrupt(IntCtrl_InterruptType Int_Num)
{
	 Dio_Write_Pin((&(ENx(Int_Num))), Int_Num, HIGH);   
}
static void IntCtrl_DisableInterrupt(IntCtrl_InterruptType Int_Num)
{
	Dio_Write_Pin((&(DISIx(Int_Num))), Int_Num, HIGH);
}
void IntCtrl_PIN_Enable(const User_pin_data_type *Config_Ptr)
{
	uint8_t idx = 0;
	
	for(idx = 0; idx < CFG_INT_NUM_PIN; idx++)
	{
		uint8_t port = Config_Ptr[idx].Port;
		uint8_t pin = Config_Ptr[idx].Pin;
		uint8_t sensitivity = Config_Ptr[idx].Sensitivity;
		uint8_t event = Config_Ptr[idx].Event;
		
		if(LEVEL == sensitivity)
		{
			GPIOIS(port)  |= (1U<<pin);
		}
    else if(EDGE == sensitivity)
		{
			GPIOIS(port)  &= ~(1U<<pin);
		}
		else
		{
			/*TODO: ERROR HANDLING*/
		}
		
		if(BOTH == event)
		{
			GPIOIBE(port) |= (1U<<pin);
		}
		else if(FALLING_LOW == event)
		{
			GPIOIBE(port) &= ~(1U<<pin);
			GPIOIEV(port) &= ~(1U<<pin);
		}
		else if(RISING_HIGH == event)
		{
			GPIOIBE(port) &= ~(1U<<pin);
			GPIOIEV(port) |= (1U<<pin);
		}
		else
		{
			/*TODO: ERROR HANDLING*/
		}
		GPIOICR(port) |= (1U<<pin);
		GPIOIM(port) |= (1U<<pin);	
	}
}

