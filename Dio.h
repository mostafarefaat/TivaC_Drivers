#ifndef DIO_H_
#define DIO_H_
/*-----------INCLUDES-----------*/
#include "types.h"
/*-----------LOCAL MACROS-----------*/

/*-----------GLOBAL STATIC VARIABLES-----------*/

/*-----------GLOBAL EXTERN VARIABLES-----------*/

/*-----------APIs FUNCTIONS DECLARATION-----------*/
uint8_t Dio_Read_Pin(volatile uint32_t *PORT, uint8_t PIN);
uint8_t Dio_Read_Port(volatile uint32_t *PORT);
void Dio_Write_Pin(volatile uint32_t *PORT, uint8_t PIN, uint8_t LEVEL);
void Dio_Write_Port(volatile uint32_t *PORT, uint32_t VALUE_HEX);
void Dio_Toggle_Pin(volatile uint32_t *PORT, uint8_t PIN);


#endif

