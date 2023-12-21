/*-----------INCLUDES-----------*/
#include "Dio.h"
/*-----------LOCAL MACROS-----------*/

/*-----------GLOBAL STATIC VARIABLES-----------*/

/*-----------GLOBAL EXTERN VARIABLES-----------*/

/*-----------APIs IMPLEMENTATION-----------*/		/*TODO: GUARD CONDITIONS FOR THE POINTERS IF THEY ARE NULL*/
uint8_t Dio_Read_Pin(volatile uint32_t *PORT, uint8_t PIN)
{
	return (uint8_t)READ_BIT(*PORT,PIN);
}
uint8_t Dio_Read_Port(volatile uint32_t *PORT)
{
	return (uint8_t)(*PORT);
}
void Dio_Write_Pin(volatile uint32_t *PORT, uint8_t PIN, uint8_t LEVEL)
{
	
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
}
void Dio_Write_Port(volatile uint32_t *PORT, uint32_t VALUE_HEX)
{
	*PORT = VALUE_HEX;
}
void Dio_Toggle_Pin(volatile uint32_t *PORT, uint8_t PIN)
{
	TOGGLE_BIT(*PORT,PIN);
}
