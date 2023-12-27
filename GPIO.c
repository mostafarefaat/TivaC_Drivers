/*-----------INCLUDES-----------*/
#include "GPIO.h"

/*-----------LOCAL MACROS-----------*/

/*-----------GLOBAL STATIC VARIABLES-----------*/
cb_type CallBack_Ptr_gpio = NULL;
/*-----------GLOBAL EXTERN VARIABLES-----------*/

/*-----------APIs IMPLEMENTATION-----------*/
void Port_Init(const Port_ConfigType *Config_Ptr)
{
	uint8_t Pin_Counter = 0;
	if(Config_Ptr != 0)
	{
		
		for(Pin_Counter = 0; Pin_Counter < ACTIVE_PINS_NUM; Pin_Counter++)
		{
			Port_Num port_num = Config_Ptr[Pin_Counter].PortNum;
			Port_PinNum pin_num = Config_Ptr[Pin_Counter].PinNum;
			/*STEP_1 INITIALIZE THE CLOCK*/
			Module_Clk_init(port_num);		/*Enabling the clock to PORTx*/
			
			while((Dio_Read_Pin(&(PRGPIO), port_num)) == 0); 			/* STEP_2 Wait until the peripheral is ready*/
			
			Dio_Write_Port(&(GPIOLOCK(port_num)),UNLOCK_VALUE);		/* STEP_3 Unlock the peripheral*/
			
			Dio_Write_Pin(&(GPIOCR(port_num)), pin_num, HIGH);		/* STEP_4 Commit the needed PINs for change*/

			/*TODO : SLEEP MODE AND DEEP SLEEP MODE (PAGE 656)*/
			
			/*STEP_5 SET THE DIRECTION*/
			if(PORT_PIN_OUTPUT == Config_Ptr[Pin_Counter].Port_Pin_Direction)
			{
				Dio_Write_Pin(&(GPIODIR(port_num)),pin_num, HIGH);
				
				/*STEP_5.1 CONFIGURE PIN LEVEL*/
				if(PORT_PIN_HIGH == Config_Ptr[Pin_Counter].Port_Pin_Level_Value)
				{
					Dio_Write_Pin(&(GPIODATA(port_num)), pin_num, HIGH);
				}
				else if(PORT_PIN_LOW == Config_Ptr[Pin_Counter].Port_Pin_Level_Value)
				{
					Dio_Write_Pin(&(GPIODATA(port_num)), pin_num, LOW);
				}
				else
				{
					/*INVALID CONFIG ERROR*/  /*TODO: RETURN AN INT TO SPECIFY IF ERROR HAPPENED OR NOT*/
					break;
				}
					/*STEP_5.2 SET OUTPUT CURRENT*/
				switch(Config_Ptr[Pin_Counter].Port_Pin_Output_Current)
				{
					case PORT_PIN_CURRENT_2mA: Dio_Write_Pin(&(GPIODR2R(port_num)),pin_num, HIGH);
					break;
					case PORT_PIN_CURRENT_4mA: Dio_Write_Pin(&(GPIODR4R(port_num)),pin_num, HIGH);
					break;
					case PORT_PIN_CURRENT_8mA: Dio_Write_Pin(&(GPIODR8R(port_num)),pin_num, HIGH);
					break;
					default: /*INVALID CONFIG ERROR*/  /*TODO: RETURN AN INT TO SPECIFY IF ERROR HAPPENED OR NOT*/
					break;
				}
			}
			else if(PORT_PIN_INTPUT == Config_Ptr[Pin_Counter].Port_Pin_Direction)
			{
				Dio_Write_Pin(&(GPIODIR(port_num)),pin_num, LOW);
				
				/*STEP_5.1 SET INTERNAL ATTACH TYPE*/
				switch(Config_Ptr[Pin_Counter].Port_Pin_Internal_Attach)
				{
					case PORT_PIN_PUR: Dio_Write_Pin(&(GPIOPUR(port_num)),pin_num, HIGH);
					break;
					case PORT_PIN_PDR: Dio_Write_Pin(&(GPIOPDR(port_num)),pin_num, HIGH);
					break;
					case PORT_PIN_ODR: Dio_Write_Pin(&(GPIOODR(port_num)),pin_num, HIGH);
					break;
					default: /*INVALID CONFIG ERROR*/  /*TODO: RETURN AN INT TO SPECIFY IF ERROR HAPPENED OR NOT*/
					break;
			}	
			}
			else
			{
				/*INVALID CONFIG ERROR*/  /*TODO: RETURN AN INT TO SPECIFY IF ERROR HAPPENED OR NOT*/
				break;
			}

			/*STEP_6 SET PIN MODE*/
			if( PORT_PIN_DEN == Config_Ptr[Pin_Counter].Port_Pin_Mode )
			{
				/*CLEAR THE CORRESPONDING BIT IN GPIOAFSEL REGISTER TO DISABLE THE ALTERNATIVE FUNCTIONALITY ON THIS PIN*/
				Dio_Write_Pin(&(GPIOAFSEL(port_num)),pin_num, LOW);
				/*SET THE CORRESPONDING BIT IN GPIODEN REGISTER TO ENABLE THE DIGITAL FUNCTIONALITY ON THIS PIN*/
				Dio_Write_Pin(&(GPIODEN(port_num)),pin_num, HIGH);
				/*CLEAR THE CORRESPONDING BIT IN GPIOAMSEL REGISTER TO DISABLE THE ANALOG FUNCTIONALITY ON THIS PIN*/
				Dio_Write_Pin(&(GPIOAMSEL(port_num)),pin_num, LOW);
				
			}
			else if(PORT_PIN_ANLG == Config_Ptr[Pin_Counter].Port_Pin_Mode)
			{
				/*CLEAR THE CORRESPONDING BIT IN GPIOAFSEL REGISTER TO DISABLE THE ALTERNATIVE FUNCTIONALITY ON THIS PIN*/
				Dio_Write_Pin(&(GPIOAFSEL(port_num)),pin_num, LOW);
				/*SET THE CORRESPONDING BIT IN GPIODEN REGISTER TO ENABLE THE DIGITAL FUNCTIONALITY ON THIS PIN*/
				Dio_Write_Pin(&(GPIODEN(port_num)),pin_num, LOW);
				/*CLEAR THE CORRESPONDING BIT IN GPIOAMSEL REGISTER TO DISABLE THE ANALOG FUNCTIONALITY ON THIS PIN*/
				Dio_Write_Pin(&(GPIOAMSEL(port_num)),pin_num, HIGH);
			}
			else if(PORT_PIN_ALTER == Config_Ptr[Pin_Counter].Port_Pin_Mode)
			{
				/*CLEAR THE CORRESPONDING BIT IN GPIOAFSEL REGISTER TO DISABLE THE ALTERNATIVE FUNCTIONALITY ON THIS PIN*/
				Dio_Write_Pin(&(GPIOAFSEL(port_num)),pin_num, HIGH);
				/*SET THE CORRESPONDING BIT IN GPIODEN REGISTER TO ENABLE THE DIGITAL FUNCTIONALITY ON THIS PIN*/
				Dio_Write_Pin(&(GPIODEN(port_num)),pin_num, LOW);
				/*CLEAR THE CORRESPONDING BIT IN GPIOAMSEL REGISTER TO DISABLE THE ANALOG FUNCTIONALITY ON THIS PIN*/
				Dio_Write_Pin(&(GPIOAMSEL(port_num)),pin_num, LOW);
				
				/*TODO: enable each ALTERNATE function*/			
			}
			else
			{
				/*INVALID CONFIG ERROR*/  /*TODO: RETURN AN INT TO SPECIFY IF ERROR HAPPENED OR NOT*/
				break;
			}

			Dio_Write_Port(&(GPIOLOCK(port_num)),LOCK_VALUE);   /* STEP_7 lock the peripheral*/
		}
		
	}
	else
	{
				/*NULL POINTER ERROR*/  /*TODO: RETURN AN INT TO SPECIFY IF ERROR HAPPENED OR NOT*/
	}
	
}


void register_gpio_cb(cb_type Ptr)
{
	if(NULL != Ptr)
	{
		CallBack_Ptr_gpio = Ptr;
	}	
}
void GPIOF_Handler(void)
{
	if(NULL != CallBack_Ptr_gpio)
	{
		CallBack_Ptr_gpio();
	}
}

