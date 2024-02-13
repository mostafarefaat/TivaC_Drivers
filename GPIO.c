/**
 ********************************************************************************
 * @file    GPIO.c
 * @author  Mostafa Refaat
 * @date    31/1/2024
 * @brief
 ********************************************************************************
 */

/************************************
 * INCLUDES
 ************************************/
#include "GPIO.h"
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
cb_ptr CallBack_Ptr_gpio = NULL_PTR;
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

uint8 Port_Init(const Port_ConfigType *Port_Config_Ptr, uint8 Num_of_pins )
{
	uint8 Pin_Counter = 0;
	uint8 error = 0;
	
	if(Port_Config_Ptr != 0)
	{
		
		for(Pin_Counter = 0; Pin_Counter < Num_of_pins; Pin_Counter++)
		{
			PortType 			port_num = Port_Config_Ptr[Pin_Counter].Port;
			PinNumType 		pin_num  = Port_Config_Ptr[Pin_Counter].Pin_Num;
			
			/*STEP_1 INITIALIZE THE CLOCK*/
			Module_Clk_init(port_num);
			
		  /* STEP_2 Wait until the peripheral is ready*/
			while((Read_Pin(&(PRGPIO), port_num)) == 0);
 			
			/* STEP_3 Unlock the peripheral if needed */
			if( (PORTC == port_num) & ( (pin_num == 0) || (pin_num == 1) || (pin_num == 2) || (pin_num == 3) ) ){   /*PC[3:0]*/
				error = 1; 				/*MUST UNLOCK BEFORE CALLING THE Port_Init Function*/
				break;
			}
			else if( (PORTD == port_num) & (pin_num == 7) ){     /*PD7*/ 
				error = 1; 				/*MUST UNLOCK BEFORE CALLING THE Port_Init Function*/
				break;
			}
			else if((PORTF == port_num) & (pin_num == 0)){
				Write_Port(&(GPIOLOCK(port_num)),UNLOCK_VALUE);		/*  Unlock the peripheral*/
				Write_Pin(&(GPIOCR(port_num)), pin_num, HIGH);		/*  Commit the needed PINs for change*/
			}
			
			/*TODO : SLEEP MODE AND DEEP SLEEP MODE (PAGE 656)*/
			
			/*STEP_4 SET THE DIRECTION*/
			if(OUTPUT == Port_Config_Ptr[Pin_Counter].Pin_Direction)
			{
				Write_Pin(&(GPIODIR(port_num)),pin_num, HIGH);
				
				/*STEP_4.1 CONFIGURE PIN LEVEL*/
				if(HIGH == Port_Config_Ptr[Pin_Counter].Pin_Level)
				{
					Write_Pin(&(GPIODATA(port_num)), pin_num, HIGH);				
				}
				else if(LOW == Port_Config_Ptr[Pin_Counter].Pin_Level)
				{
					Write_Pin(&(GPIODATA(port_num)), pin_num, LOW);
				}
				else
				{
					/*INVALID CONFIG ERROR*/  /*TODO: RETURN AN INT TO SPECIFY IF ERROR HAPPENED OR NOT*/
					error = 1;
					break;
				}
			}
			else if(INTPUT == Port_Config_Ptr[Pin_Counter].Pin_Direction)
			{
				Write_Pin(&(GPIODIR(port_num)),pin_num, LOW);
				
				/*STEP_4.1 SET INTERNAL ATTACH TYPE*/
				switch(Port_Config_Ptr[Pin_Counter].Pin_Internal_Attach)
				{
					case PUR: Write_Pin(&(GPIOPUR(port_num)),pin_num, HIGH);
					break;
					case PDR: Write_Pin(&(GPIOPDR(port_num)),pin_num, HIGH);
					break;
					case ODR: Write_Pin(&(GPIOODR(port_num)),pin_num, HIGH);
					break;
					default: error = 1;/*INVALID CONFIG ERROR*/  /*TODO: RETURN AN INT TO SPECIFY IF ERROR HAPPENED OR NOT*/
					break;
			}	
		 }
			else
			{
				error = 1;/*INVALID CONFIG ERROR*/  /*TODO: RETURN AN INT TO SPECIFY IF ERROR HAPPENED OR NOT*/
				break;
			}
			
			/*STEP_5 SET OUTPUT CURRENT*/
			switch(Port_Config_Ptr[Pin_Counter].Pin_Current)
			 {
					case CURRENT_2mA: Write_Pin(&(GPIODR2R(port_num)),pin_num, HIGH);
					break;
					case CURRENT_4mA: Write_Pin(&(GPIODR4R(port_num)),pin_num, HIGH);
					break;
					case CURRENT_8mA: Write_Pin(&(GPIODR8R(port_num)),pin_num, HIGH);
					break;
					default: error = 1; /*INVALID CONFIG ERROR*/  /*TODO: RETURN AN INT TO SPECIFY IF ERROR HAPPENED OR NOT*/
					break;
				}

			/*STEP_6 SET PIN MODE*/
			if( DEN == Port_Config_Ptr[Pin_Counter].Pin_Mode )
			{
				/*CLEAR THE CORRESPONDING BIT IN GPIOAFSEL REGISTER TO DISABLE THE ALTERNATIVE FUNCTIONALITY ON THIS PIN*/
				Write_Pin(&(GPIOAFSEL(port_num)),pin_num, LOW);
				/*SET THE CORRESPONDING BIT IN GPIODEN REGISTER TO ENABLE THE DIGITAL FUNCTIONALITY ON THIS PIN*/
				Write_Pin(&(GPIODEN(port_num)),pin_num, HIGH);
				/*CLEAR THE CORRESPONDING BIT IN GPIOAMSEL REGISTER TO DISABLE THE ANALOG FUNCTIONALITY ON THIS PIN*/
				Write_Pin(&(GPIOAMSEL(port_num)),pin_num, LOW);
				
				Write_Pin(&(GPIOPCTL(port_num)),pin_num, LOW);
			}
			else if(ANLG == Port_Config_Ptr[Pin_Counter].Pin_Mode)
			{
				/*CLEAR THE CORRESPONDING BIT IN GPIOAFSEL REGISTER TO DISABLE THE ALTERNATIVE FUNCTIONALITY ON THIS PIN*/
				Write_Pin(&(GPIOAFSEL(port_num)),pin_num, LOW);
				/*SET THE CORRESPONDING BIT IN GPIODEN REGISTER TO DISABLE THE DIGITAL FUNCTIONALITY ON THIS PIN*/
				Write_Pin(&(GPIODEN(port_num)),pin_num, LOW);
				/*CLEAR THE CORRESPONDING BIT IN GPIOAMSEL REGISTER TO ENABLE THE ANALOG FUNCTIONALITY ON THIS PIN*/
				Write_Pin(&(GPIOAMSEL(port_num)),pin_num, HIGH);
				
				Write_Pin(&(GPIOPCTL(port_num)),pin_num, LOW);
			}
			else if(ALTER == Port_Config_Ptr[Pin_Counter].Pin_Mode)
			{
				/*CLEAR THE CORRESPONDING BIT IN GPIOAFSEL REGISTER TO DISABLE THE ALTERNATIVE FUNCTIONALITY ON THIS PIN*/
				Write_Pin(&(GPIOAFSEL(port_num)),pin_num, HIGH);
				/*SET THE CORRESPONDING BIT IN GPIODEN REGISTER TO ENABLE THE DIGITAL FUNCTIONALITY ON THIS PIN*/
				Write_Pin(&(GPIODEN(port_num)),pin_num, LOW);
				/*CLEAR THE CORRESPONDING BIT IN GPIOAMSEL REGISTER TO DISABLE THE ANALOG FUNCTIONALITY ON THIS PIN*/
				Write_Pin(&(GPIOAMSEL(port_num)),pin_num, LOW);
				
				/*TODO: enable each ALTERNATE function*/	/*switch case*/		
			}
			else
			{
				error = 1;/*INVALID CONFIG ERROR*/  /*TODO: RETURN AN INT TO SPECIFY IF ERROR HAPPENED OR NOT*/
				break;
			}
			
		}
	}
	else
	{
		error = 1;		/*NULL POINTER ERROR*/  /*TODO: RETURN AN INT TO SPECIFY IF ERROR HAPPENED OR NOT*/
	}
	return error;
}

uint8 Read_Pin(volatile uint32 *PORT, uint8 PIN)
{
	if(PORT != NULL_PTR){
		return (uint8)READ_BIT(*PORT,PIN);
	}
	return ERROR;
}
uint8 Read_Port(volatile uint32 *PORT)
{
	if(PORT != NULL_PTR){
		return (uint8)(*PORT);
	}
	return ERROR;
}
uint8 Write_Pin(volatile uint32 *PORT, uint8 PIN, uint8 LEVEL)
{
	if(PORT != NULL_PTR){
	switch(LEVEL)
	{
		case HIGH:
			SET_BIT(*PORT,PIN);
		break;
		case LOW:
			CLEAR_BIT(*PORT,PIN);
		break;
		default:
		break;
	}
	return 0;
}
	else{
		return ERROR;
	}
}
uint8 Write_Port(volatile uint32 *PORT, uint32 VALUE_HEX)
{
	if(PORT != NULL_PTR){
		*PORT = VALUE_HEX;
		return 0;
	}
	else{
		return ERROR;
	}
}
uint8 Toggle_Pin(volatile uint32 *PORT, uint8 PIN)
{
	if(PORT != NULL_PTR){
	TOGGLE_BIT(*PORT,PIN);
	return 0;
	}
	else{
		return ERROR;
	}
}

void register_gpio_cb(cb_ptr Ptr)
{
	if(NULL_PTR != Ptr)
	{
		CallBack_Ptr_gpio = Ptr;
	}	
}
void GPIOF_Handler(void)
{
	if(NULL_PTR != CallBack_Ptr_gpio)
	{
		CallBack_Ptr_gpio();
	}
}


	


