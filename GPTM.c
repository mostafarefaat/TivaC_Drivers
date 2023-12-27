/*-----------INCLUDES-----------*/
#include "GPTM.h"
#include "math.h"
/*-----------LOCAL MACROS-----------*/
cb_type CallBack_Ptr_timer 	= NULL;
cb_type Callback_Ptr[12];     /*Array of pointers to functions for delay */

uint8_t Timer_Handler_served = 0;
uint8_t Timer_Stopped = 0;
/*-----------GLOBAL STATIC VARIABLES-----------*/

/*-----------GLOBAL EXTERN VARIABLES-----------*/

/*-----------APIs FUNCTIONS DECLARATION-----------*/
void Gpt_Init(const Gpt_ConfigType *ConfigPtr)
{
	uint8_t idx = 0;
	uint8_t TimerBitType = 0;
	uint8_t	BitConfigType = 0;
	
	for(idx = 0; idx < NUM_OF_TIMERS_Config; idx++)
	{
	 Gpt_ChannelModeType     Mode 				    = 	ConfigPtr[idx].Gpt_ChannelMode;					/*ONESHOOT or PERIODIC or CAPTURE*/     /*DONE*/
	 Gpt_CountDirType 		   countDir 		    = 	ConfigPtr[idx].Gpt_CountDir;						/*UP or DOWN*/													/*DONE*/
   Gpt_EventModeType 			 event_modeType 	= 	ConfigPtr[idx].Gpt_EventMode;				    /*POS or NEG or BOTH*/                  /*DONE*/
	 Gpt_CaptureModeType 	   capture_mode 		= 	ConfigPtr[idx].Gpt_CaptureMode;				  /*EDGE COUNT or EDGE TIMER*/						/*DONE*/
		
	 Gpt_ChannelType		   timermodule 	= 	ConfigPtr[idx].Gpt_Channel_ID;    			   /*TIMER_0 -> TIMER_5*/               
	 Gpt_ChannelType 		   TimerType 		= 	ConfigPtr[idx].Gpt_Timer;								   /*TIMER_A or TIMER_B*/
	 uint8_t 						   frequency		=   ConfigPtr[idx].Gpt_ChannelTickFrequency;
	 uint32_t 					   max_ticks	  =   ConfigPtr[idx].Gpt_ChannelTickValueMax;
	 Gpt_ConcateType			 concate      =		ConfigPtr[idx].Gpt_Timer16_32_Concate;
		
	 CallBack_Ptr_timer		              = 	ConfigPtr[idx].Gpt_Notificaton;                         /*Call Back Function Pointer*/
		
	if(max_ticks <= 65535)   
	{	
	 TimerBitType =  TIMER_16_32;
	 BitConfigType = TIMER_16;
	}
	else if((max_ticks <= 4294967295) && (concate != NULL) )
	{
		BitConfigType = TIMER_32;
	}
	else
	{
		TimerBitType =  TIMER_32_64;
		( (max_ticks <= 4294967295)?  (BitConfigType = TIMER_32) : (BitConfigType = TIMER_64) );
	}
		
	 if(TIMER_16_32 == TimerBitType)
	 {
		 switch(timermodule)
		 {
				case TIMER0: Module_Clk_init(Timer_0_module_16_32);  timermodule = TIMER0_16_32;  Callback_Ptr[0] = ConfigPtr[idx].Gpt_Notificaton; 
				break;
			 	case TIMER1: Module_Clk_init(Timer_1_module_16_32);  timermodule = TIMER1_16_32;	Callback_Ptr[1] = ConfigPtr[idx].Gpt_Notificaton;			 
				break;
			 	case TIMER2: Module_Clk_init(Timer_2_module_16_32);  timermodule = TIMER2_16_32; 	Callback_Ptr[2] = ConfigPtr[idx].Gpt_Notificaton;			 
				break;
			 	case TIMER3: Module_Clk_init(Timer_3_module_16_32);  timermodule = TIMER3_16_32;	Callback_Ptr[3] = ConfigPtr[idx].Gpt_Notificaton;			 
				break;
			 	case TIMER4: Module_Clk_init(Timer_4_module_16_32);  timermodule = TIMER4_16_32;	Callback_Ptr[4] = ConfigPtr[idx].Gpt_Notificaton;			 
				break;
			 	case TIMER5: Module_Clk_init(Timer_5_module_16_32);  timermodule = TIMER5_16_32;	Callback_Ptr[5] = ConfigPtr[idx].Gpt_Notificaton;		 
				break;
				default: /*TODO: ERROR*/ break;			 
		 }
		 
		 //while((Dio_Read_Pin(&(PRTIMER_16_32), TIMER1)) == 0); 			// STEP_2 Wait until the peripheral is ready
		 
		if(TIMERA == TimerType)  		 /*disable TIMER_A counter*/
		{
			 Dio_Write_Pin(&(GPTMCTL(timermodule)), TAEN, LOW);   
			
		}
		else if(TIMERB == TimerType)  /*disable TIMER_B counter*/
		{
			 Dio_Write_Pin(&(GPTMCTL(timermodule)), TBEN, LOW);  
		}
		else{/*TODO: ERROR*/}
		
		switch(BitConfigType)   /*16bits or 32bits*/
		{
			GPTMCFG(timermodule) &= GPTMCFG_TIMER_MASK; 
			case TIMER_16: GPTMCFG(timermodule) |= 0X4; 
			break;
			case TIMER_32: GPTMCFG(timermodule) |= 0X0; 
			break;
			default: /*TODO: ERROR*/ break;
		}

		if( (BitConfigType == TIMER_32) || (TIMERA == TimerType) )
		{
			switch(Mode)
			{
				GPTMTAMR(timermodule) &= GPTMTnMR_TIMER_MASK;   
			
				case ONESHOT:  GPTMTAMR(timermodule) |= 0X01; 
				break;
				case PERIODIC: GPTMTAMR(timermodule) |= 0X02;
				break;
				case CAPTURE:  GPTMTAMR(timermodule) |= 0X03; ( (EDGE_COUNT == capture_mode)? Dio_Write_Pin(&(GPTMTAMR(timermodule)), TACMR, LOW): Dio_Write_Pin(&(GPTMTAMR(timermodule)), TACMR, HIGH) );
				break;
				default: /*TODO: ERROR*/ break;
			}
		
			if(UP_COUNT == countDir)
			{
				Dio_Write_Pin(&(GPTMTAMR(timermodule)), TACDIR, HIGH);
				
			}
			else if(DOWN_COUNT == countDir)
			{
				Dio_Write_Pin(&(GPTMTAMR(timermodule)), TACDIR, LOW);
				
			}
			else {/*TODO: ERROR*/}
			
			
			if(TIMERA == TimerType)
			{
				GPTMCTL(timermodule) &= GPTMCTL_TIMERA_MASK;
				if(pos_edge == event_modeType)
				{		                   
					GPTMCTL(timermodule) |= 0X0;
				}
				else if(neg_edge == event_modeType)
				{
					Dio_Write_Pin(&(GPTMCTL(timermodule)), PIN2, HIGH);      //0X1
				}
				else if(both_edges == event_modeType)
				{
					Dio_Write_Pin(&(GPTMCTL(timermodule)), PIN2, HIGH);    //0X3
					Dio_Write_Pin(&(GPTMCTL(timermodule)), PIN3, HIGH);
				}
				else {/*TODO: ERROR*/}			
			}
			else if(TIMERB == TimerType)
			{
				 GPTMCTL(timermodule) &= GPTMCTL_TIMERB_MASK;
				 if(pos_edge == event_modeType)
				 {			                   
						GPTMCTL(timermodule) |= 0X0;
				 }
				 else if(neg_edge == event_modeType)
				 {
						Dio_Write_Pin(&(GPTMCTL(timermodule)), PIN10, HIGH);      //0X1
				 }
				 else if(both_edges == event_modeType)
				 {
						Dio_Write_Pin(&(GPTMCTL(timermodule)), PIN10, HIGH);    //0X3
						Dio_Write_Pin(&(GPTMCTL(timermodule)), PIN11, HIGH);
				 }
				 else {/*TODO: ERROR*/}				
				
			}
			else {/*TODO: ERROR PLEASE CHOOOSE TIMERA OR TIMERB**/}
		}
		else if(TIMERB == TimerType)
		{		 
				switch(Mode)
			{
				GPTMTBMR(timermodule) &= GPTMTnMR_TIMER_MASK;   
			
				case ONESHOT:  GPTMTBMR(timermodule) |= 0X01;
				break;
				case PERIODIC: GPTMTBMR(timermodule) |= 0X02; 
				break;
				case CAPTURE:  GPTMTBMR(timermodule) |= 0X03; ( (EDGE_COUNT == capture_mode)? Dio_Write_Pin(&(GPTMTBMR(timermodule)), TBCMR, LOW): Dio_Write_Pin(&(GPTMTBMR(timermodule)), TBCMR, HIGH) );
				break;
				default: /*TODO: ERROR*/ break;
			
			}
		
			if(UP_COUNT == countDir)
			{
				Dio_Write_Pin(&(GPTMTBMR(timermodule)), TBCDIR, HIGH);
			}
			else if(DOWN_COUNT == countDir)
			{
				Dio_Write_Pin(&(GPTMTBMR(timermodule)), TBCDIR, LOW);
			}
			else {/*TODO: ERROR*/}			
			
 			GPTMCTL(timermodule) &= GPTMCTL_TIMERB_MASK;
			if(pos_edge == event_modeType)
			{		                   
				GPTMCTL(timermodule) |= 0X0;
			}
			else if(neg_edge == event_modeType)
			{
				Dio_Write_Pin(&(GPTMCTL(timermodule)), PIN10, HIGH);      //0X1
			}
			else if(both_edges == event_modeType)
			{
				Dio_Write_Pin(&(GPTMCTL(timermodule)), PIN10, HIGH);    //0X3
				Dio_Write_Pin(&(GPTMCTL(timermodule)), PIN11, HIGH);
			}
			else {/*TODO: ERROR*/}
	
		}

		else{/*TODO: ERROR PLEASE CHOOOSE TIMERA OR TIMERB*/}
		

		 
		}
	 else if(TIMER_32_64 == TimerBitType)
	 {
		 	switch(timermodule)
		 {
				case TIMER0: Module_Clk_init(Timer_0_module_32_64);  timermodule = TIMER0_32_64;  Callback_Ptr[6] = ConfigPtr[idx].Gpt_Notificaton; 
				break;
			 	case TIMER1: Module_Clk_init(Timer_1_module_32_64);  timermodule = TIMER1_32_64;  Callback_Ptr[7] = ConfigPtr[idx].Gpt_Notificaton;       
				break;
			 	case TIMER2: Module_Clk_init(Timer_2_module_32_64);  timermodule = TIMER2_32_64;  Callback_Ptr[8] = ConfigPtr[idx].Gpt_Notificaton;       
				break;
			 	case TIMER3: Module_Clk_init(Timer_3_module_32_64);  timermodule = TIMER3_32_64;  Callback_Ptr[9] = ConfigPtr[idx].Gpt_Notificaton;    		
				break;
			 	case TIMER4: Module_Clk_init(Timer_4_module_32_64);  timermodule = TIMER4_32_64;  Callback_Ptr[10] = ConfigPtr[idx].Gpt_Notificaton;  			
				break;
			 	case TIMER5: Module_Clk_init(Timer_5_module_32_64);  timermodule = TIMER5_32_64;  Callback_Ptr[11] = ConfigPtr[idx].Gpt_Notificaton;			 
				break;
				default: /*TODO: ERROR*/ break;
		 }
		 //while((Dio_Read_Pin(&(PRTIMER_16_32), TIMER1)) == 0); 			// STEP_2 Wait until the peripheral is ready
		 
		if(TIMERA == TimerType)
		{
			 Dio_Write_Pin(&(GPTMCTL(timermodule)), TAEN, LOW);   /*disable the counter*/
			
		}
		else if(TIMERB == TimerType)
		{
			 Dio_Write_Pin(&(GPTMCTL(timermodule)), TBEN, LOW);  /*disable the counter*/
		}
		else{/*TODO: ERROR*/}
		
		switch(BitConfigType)
		{
			GPTMCFG(timermodule) &= GPTMCFG_TIMER_MASK; 
			case TIMER_32: GPTMCFG(timermodule) |= 0X4; 
			break;
			case TIMER_64: GPTMCFG(timermodule) |= 0X0; 
			break;
			default: /*TODO: ERROR*/ break;
		}
		
		if( (BitConfigType == TIMER_64) || (TIMERA == TimerType) )
		{
			switch(Mode)
			{
				GPTMTAMR(timermodule) &= GPTMTnMR_TIMER_MASK;   
			
				case ONESHOT:  GPTMTAMR(timermodule) |= 0X01; 
				break;
				case PERIODIC: GPTMTAMR(timermodule) |= 0X02;
				break;
				case CAPTURE:  GPTMTAMR(timermodule) |= 0X03; ( (EDGE_COUNT == capture_mode)? Dio_Write_Pin(&(GPTMTAMR(timermodule)), TACMR, LOW): Dio_Write_Pin(&(GPTMTAMR(timermodule)), TACMR, HIGH) );
				break;
				default: /*TODO: ERROR*/ break;
			}
		
			if(UP_COUNT == countDir)
			{
				Dio_Write_Pin(&(GPTMTAMR(timermodule)), TACDIR, HIGH);
			}
			else if(DOWN_COUNT == countDir)
			{
				Dio_Write_Pin(&(GPTMTAMR(timermodule)), TACDIR, LOW);
			}
			else {/*TODO: ERROR*/}
			
			
			if(TIMERA == TimerType)
			{
				GPTMCTL(timermodule) &= GPTMCTL_TIMERA_MASK;
				if(pos_edge == event_modeType)
				{		                   
					GPTMCTL(timermodule) |= 0X0;
				}
				else if(neg_edge == event_modeType)
				{
					Dio_Write_Pin(&(GPTMCTL(timermodule)), PIN2, HIGH);      //0X1
				}
				else if(both_edges == event_modeType)
				{
					Dio_Write_Pin(&(GPTMCTL(timermodule)), PIN2, HIGH);    //0X3
					Dio_Write_Pin(&(GPTMCTL(timermodule)), PIN3, HIGH);
				}
				else {/*TODO: ERROR*/}			
			}
			else if(TIMERB == TimerType)
			{
				 GPTMCTL(timermodule) &= GPTMCTL_TIMERB_MASK;
				 if(pos_edge == event_modeType)
				 {			                   
						GPTMCTL(timermodule) |= 0X0;
				 }
				 else if(neg_edge == event_modeType)
				 {
						Dio_Write_Pin(&(GPTMCTL(timermodule)), PIN10, HIGH);      //0X1
				 }
				 else if(both_edges == event_modeType)
				 {
						Dio_Write_Pin(&(GPTMCTL(timermodule)), PIN10, HIGH);    //0X3
						Dio_Write_Pin(&(GPTMCTL(timermodule)), PIN11, HIGH);
				 }
				 else {/*TODO: ERROR*/}				
				
			}
			else {/*TODO: ERROR PLEASE CHOOOSE TIMERA OR TIMERB**/}
		}	
		else if(TIMERB == TimerType)
		{		 
				switch(Mode)
			{
				GPTMTBMR(timermodule) &= GPTMTnMR_TIMER_MASK;   
			
				case ONESHOT:  GPTMTBMR(timermodule) |= 0X01;
				break;
				case PERIODIC: GPTMTBMR(timermodule) |= 0X02; 
				break;
				case CAPTURE:  GPTMTBMR(timermodule) |= 0X03; ( (EDGE_COUNT == capture_mode)? Dio_Write_Pin(&(GPTMTBMR(timermodule)), TBCMR, LOW): Dio_Write_Pin(&(GPTMTBMR(timermodule)), TBCMR, HIGH) );
				break;
				default: /*TODO: ERROR*/ break;
			
			}
		
			if(UP_COUNT == countDir)
			{
				Dio_Write_Pin(&(GPTMTBMR(timermodule)), TBCDIR, HIGH);
			}
			else if(DOWN_COUNT == countDir)
			{
				Dio_Write_Pin(&(GPTMTBMR(timermodule)), TBCDIR, LOW);
			}
			else {/*TODO: ERROR*/}			
			
 			GPTMCTL(timermodule) &= GPTMCTL_TIMERB_MASK;
			if(pos_edge == event_modeType)
			{		                   
				GPTMCTL(timermodule) |= 0X0;
			}
			else if(neg_edge == event_modeType)
			{
				Dio_Write_Pin(&(GPTMCTL(timermodule)), PIN10, HIGH);      //0X1
			}
			else if(both_edges == event_modeType)
			{
				Dio_Write_Pin(&(GPTMCTL(timermodule)), PIN10, HIGH);    //0X3
				Dio_Write_Pin(&(GPTMCTL(timermodule)), PIN11, HIGH);
			}
			else {/*TODO: ERROR*/}				
		}

		else{/*TODO: ERROR PLEASE CHOOOSE TIMERA OR TIMERB*/}
	 }
	 else{/*TODO: ERROR PLEASE CHOOOSE TIMER16_32 OR TIMER32_64*/}
	 
	 	if(NULL != CallBack_Ptr_timer)
		{
			Gpt_EnableNotification(timermodule, TimerType);
		}
		else 
		{
			Gpt_DisableNotification(timermodule, TimerType);
		}
	}
	
}

void Gpt_EnableNotification(Gpt_ChannelType module, Gpt_ChannelType Timer)
{
	if((TIMERA) == (Timer))
  {
			Dio_Write_Pin(&(GPTMICR(module)), TATOCINT, HIGH);
	
			Dio_Write_Pin(&(GPTMIMR(module)), TATOIM, HIGH);	
	} 
	else if(TIMERB == Timer)
{
			Dio_Write_Pin(&(GPTMICR(module)), TBTOCINT, HIGH);

			Dio_Write_Pin(&(GPTMIMR(module)), TBTOIM, HIGH);		
}
	else {/*ERROR HANDLE PLEASE SELECT A OR B*/}
	
}

void Gpt_DisableNotification(Gpt_ChannelType module, Gpt_ChannelType Timer)
{
	if((TIMERA) == (Timer))
  {
			Dio_Write_Pin(&(GPTMICR(module)), TATOCINT, HIGH);
	
			Dio_Write_Pin(&(GPTMIMR(module)), TATOIM, LOW);	
	} 
	else if(TIMERB == Timer)
{
			Dio_Write_Pin(&(GPTMICR(module)), TBTOCINT, HIGH);

			Dio_Write_Pin(&(GPTMIMR(module)), TBTOIM, LOW);		
}
	else {/*ERROR HANDLE PLEASE SELECT A OR B*/}	
}

void Gpt_StartTimer(Gpt_ChannelType module, Gpt_ChannelType Timer, Gpt_ValueType Value)
{
	uint8_t prescale = 0;
	uint32_t value = 0;
  if(module <= 5) 			/*_16_32*/
	{
		if(Value > MAX_DELAY_16bit)
	  {
			Value = Value * 0.001;
	    prescale = (ceil((16000000*Value)/MAX_TICKS_16bit)) - 1; value = MAX_TICKS_16bit; /* (clk_freq * Y) / (MAX_TICKS) -> where y is needed delay  */
		}
		else {prescale = 0; value = ceil((Value * MAX_TICKS_16bit )/(MAX_DELAY_16bit));}		/* (MAX_TICKS * Y) / (MAX_DELAY) -> where y is needed delay    */
		
	  if((TIMERA) == (Timer))
  	{
			GPTMTAPR(module) =  prescale;
			
		 ( ( (Dio_Read_Pin(&(GPTMTBMR(module)), TACDIR)) == UP_COUNT)? (GPTMTAILR(module) =  value-1) : (GPTMTAILR(module) =  value-1) );
			
			Dio_Write_Pin(&(GPTMCTL(module)), TAEN, HIGH);
			
			if(NULL == Callback_Ptr[module])     /*interrupt off*/
			{
				while( ( Dio_Read_Pin( &(GPTMRIS(module)), TATORIS ) )  == 0 && (Timer_Stopped == 0) ){}; 	
			}
			else{ 
				while( ( Dio_Read_Pin( &(GPTMRIS(module)), TATORIS ) )  == 0 && (Timer_Handler_served == 0) ){}; 
			  
			}
		}
		else if(TIMERB == Timer)
		{
			GPTMTBPR(module) =  prescale;
			
		 ( ( (Dio_Read_Pin(&(GPTMTBMR(module)), TBCDIR)) == UP_COUNT)? (GPTMTBILR(module) =  value-1) : (GPTMTBILR(module) =  value-1) );
			
			Dio_Write_Pin(&(GPTMCTL(module)), TBEN, HIGH);
			
			if(NULL == Callback_Ptr[module]) /*interrupt off*/
			{
				while( ( Dio_Read_Pin( &(GPTMRIS(module)), TBTORIS ) )  == 0 && (Timer_Stopped == 0));	
			}
			else{ 
				while( ( Dio_Read_Pin( &(GPTMRIS(module)), TBTORIS ) )  == 0 && (Timer_Handler_served == 0) ){}; 			
			}
		}		
	else {/*ERROR HANDLE PLEASE SELECT A OR B*/}
	}
	else if(module >= 6) 			/*_32_64*/
	{
		if(Value > MAX_DELAY_32bit)
	  {
			Value = Value * 0.001;
	    prescale = (ceil((16000000*Value)/MAX_TICKS_32bit)) - 1; value = MAX_TICKS_32bit;
		}
		else {prescale = 0;  value = ceil((Value * MAX_TICKS_32bit )/(MAX_DELAY_32bit));}
		
	  if((TIMERA) == (Timer))
  	{
			GPTMTAPR(module) =  prescale;
			
		 ( ( (Dio_Read_Pin(&(GPTMTBMR(module)), TACDIR)) == UP_COUNT)? (GPTMTAILR(module) =  value-1) : (GPTMTAILR(module) =  value-1) );
			
			Dio_Write_Pin(&(GPTMCTL(module)), TAEN, HIGH);
			
			if(NULL == Callback_Ptr[module])     /*interrupt off*/
			{
				while( ( Dio_Read_Pin( &(GPTMRIS(module)), TATORIS ) )  == 0 && (Timer_Stopped == 0)){};		
			}
			else{ 
				while( ( Dio_Read_Pin( &(GPTMRIS(module)), TATORIS ) )  == 0 && (Timer_Handler_served == 0) ){}; 			
			}		
		}
		else if(TIMERB == Timer)
		{
			GPTMTBPR(module) =  prescale;
			
		 ( ( (Dio_Read_Pin(&(GPTMTBMR(module)), TBCDIR)) == UP_COUNT)? (GPTMTBILR(module) =  value-1) : (GPTMTBILR(module) =  value-1) );
			
			Dio_Write_Pin(&(GPTMCTL(module)), TBEN, HIGH);
			if(NULL == Callback_Ptr[module]) /*interrupt off*/
			{
				while( ( Dio_Read_Pin( &(GPTMRIS(module)), TBTORIS ) )  == 0 && (Timer_Stopped == 0));
			}
			else{ 
				while( ( Dio_Read_Pin( &(GPTMRIS(module)), TBTORIS ) )  == 0 && (Timer_Handler_served == 0) ){}; 
			}		
		}		
	else {/*ERROR HANDLE PLEASE SELECT A OR B*/}		
	}
	else {/*ERROR HANDLE PLEASE ENTER CORRECT TIMER MODULE*/}
	
	if(Timer_Stopped == 0)
	{
		Gpt_StopTimer(module,Timer);
	}
	else {}

	Timer_Stopped = 0;
	Timer_Handler_served = 0;
}
void Gpt_StopTimer(Gpt_ChannelType module, Gpt_ChannelType Timer)
{
	if(TIMERA == Timer)
	{
		Dio_Write_Pin(&(GPTMCTL(module)), TAEN, LOW);
		if(( Dio_Read_Pin( &(GPTMRIS(module)), TATORIS ) )  == 0 && Timer_Handler_served == 0) /*Stopped before timed out*/
		{
			Timer_Stopped = 1;
			Timer_Handler_served = 1;
		}
		Dio_Write_Pin(&(GPTMICR(module)), TATOCINT, HIGH);
		
	}
	else if(TIMERB == Timer)
	{
		Dio_Write_Pin(&(GPTMCTL(module)), TBEN, LOW);
		if(( Dio_Read_Pin( &(GPTMRIS(module)), TBTORIS ) )  == 0 && Timer_Handler_served == 0) /*Stopped before timed out*/
		{
			Timer_Stopped = 1;
			Timer_Handler_served = 1;
			
		}
		Dio_Write_Pin(&(GPTMICR(module)), TBTOCINT, HIGH);
	}
	else{/*ERROR HANDLE PLEASE SELECT A OR B*/}
	
}

void TIMER1A_Handler(void)
{
	if(NULL != Callback_Ptr[TIMER1_16_32])
	{
		Callback_Ptr[TIMER1_16_32]();
	}

}
void WTIMER1B_Handler(void)
{
	if(NULL != Callback_Ptr[TIMER1_32_64])
	{
		Callback_Ptr[TIMER1_32_64]();
	}
}
