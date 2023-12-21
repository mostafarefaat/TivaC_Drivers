#ifndef GPIO_H_
#define GPIO_H_

/*-----------INCLUDES-----------*/
#include "Dio.h"
#include "MCU.h"

/*-----------LOCAL TYPE DEFs-----------*/
typedef uint8_t Port_PinType;
typedef uint8_t Port_PinLevelType;
typedef uint8_t Port_PinDirectionType;
typedef uint8_t Port_PinModeType;
typedef uint8_t Port_PinInternalAttachType;
typedef uint8_t Port_PinOutputCurrentType;
typedef uint8_t Port_Num;
typedef uint8_t Port_PinNum;
/*-----------INCLUDES-----------*/

/*-----------LOCAL MACROS-----------*/
#define APB_BUS
#ifdef APB_BUS
#define GPIO_BASE_ADDRESS(x)	( x<4? ((0X40004000) + ((x)*0x1000)) : ((0X40024000) + ((x-4)*0x1000)) )
#else 
#ifdef AHB_BUS
#define GPIO_BASE_ADDRESS(x)	( x<2? ((0X40058000) + ((x)*0x1000)) : ((0X4005A000) + ((x-2)*0x1000)) )
/*TODO: CHECK IT'S FUNCTIONALITY*/
#else
#error "PLEASE CHOOSE A BUS FOR GPIO"
#endif
#endif

#define ACTIVE_PINS_NUM 		5
#define UNLOCK_VALUE     0x4C4F434B
#define LOCK_VALUE     	 0x00000001

/*-----------ENUMS-----------*/
enum Pin_OutputCurrentType
{
	PORT_PIN_CURRENT_2mA, PORT_PIN_CURRENT_4mA, PORT_PIN_CURRENT_8mA
};

enum Pin_DirectionType
{
	PORT_PIN_INTPUT, PORT_PIN_OUTPUT
};

enum Pin_InternalAttachType
{
	PORT_PIN_PUR, PORT_PIN_PDR, PORT_PIN_ODR
};

enum Pin_LevelType
{
	PORT_PIN_LOW, PORT_PIN_HIGH
};

enum PinModeType   /*TODO: ADD THE REST OF THE MODES*/
{
	PORT_PIN_DEN, PORT_PIN_ANLG, PORT_PIN_ALTER
};
enum Alter_FuncType   /*TODO: ADD THE ALTERNATE FUNCTION */
{
	uart, can, pwm,
};

/*-----------STRUCT AND UNIONS-----------*/
typedef struct
{
	Port_Num										PortNum;
	Port_PinNum									PinNum;
	Port_PinModeType 						Port_Pin_Mode;
	Port_PinModeType 						Port_Pin_Alter_Mode;
	Port_PinDirectionType 			Port_Pin_Direction;
	Port_PinInternalAttachType 	Port_Pin_Internal_Attach;
	Port_PinLevelType 					Port_Pin_Level_Value;
	Port_PinOutputCurrentType 	Port_Pin_Output_Current;
	
}Port_ConfigType;


/*-----------GPIO REGISTERS-----------*/ /*PAGE 660*/

#define GPIODATA(x) 			 *((volatile uint32_t *)(GPIO_BASE_ADDRESS(x) + 0x03FC))
#define GPIODIR(x) 				 *((volatile uint32_t *)(GPIO_BASE_ADDRESS(x) + 0x0400))
#define GPIOIS(x) 				 *((volatile uint32_t *)(GPIO_BASE_ADDRESS(x) + 0x0404))
#define GPIOIBE(x) 				 *((volatile uint32_t *)(GPIO_BASE_ADDRESS(x) + 0x0408))
#define GPIOIEV(x) 				 *((volatile uint32_t *)(GPIO_BASE_ADDRESS(x) + 0x040C))
#define GPIOIM(x) 				 *((volatile uint32_t *)(GPIO_BASE_ADDRESS(x) + 0x0410))
#define GPIORIS(x) 				 *((volatile uint32_t *)(GPIO_BASE_ADDRESS(x) + 0x0414))
#define GPIOMIS(x) 				 *((volatile uint32_t *)(GPIO_BASE_ADDRESS(x) + 0x0418))
#define GPIOICR(x) 				 *((volatile uint32_t *)(GPIO_BASE_ADDRESS(x) + 0x041C))
#define GPIOAFSEL(x) 			 *((volatile uint32_t *)(GPIO_BASE_ADDRESS(x) + 0x0420))
#define GPIODR2R(x) 			 *((volatile uint32_t *)(GPIO_BASE_ADDRESS(x) + 0x0500))
#define GPIODR4R(x) 			 *((volatile uint32_t *)(GPIO_BASE_ADDRESS(x) + 0x0504))
#define GPIODR8R(x) 			 *((volatile uint32_t *)(GPIO_BASE_ADDRESS(x) + 0x0508))
#define GPIOODR(x) 				 *((volatile uint32_t *)(GPIO_BASE_ADDRESS(x) + 0x050C))
#define GPIOPUR(x) 				 *((volatile uint32_t *)(GPIO_BASE_ADDRESS(x) + 0x0510))	
#define GPIOPDR(x) 				 *((volatile uint32_t *)(GPIO_BASE_ADDRESS(x) + 0x0514))
#define GPIOSLR(x) 				 *((volatile uint32_t *)(GPIO_BASE_ADDRESS(x) + 0x0518))
#define GPIODEN(x) 				 *((volatile uint32_t *)(GPIO_BASE_ADDRESS(x) + 0x051C))
#define GPIOLOCK(x) 			 *((volatile uint32_t *)(GPIO_BASE_ADDRESS(x) + 0x0520))
#define GPIOCR(x) 				 *((volatile uint32_t *)(GPIO_BASE_ADDRESS(x) + 0x0524))
#define GPIOAMSEL(x) 			 *((volatile uint32_t *)(GPIO_BASE_ADDRESS(x) + 0x0528))
#define GPIOPCTL(x) 			 *((volatile uint32_t *)(GPIO_BASE_ADDRESS(x) + 0x052C))
#define GPIOADCCTL(x) 		 *((volatile uint32_t *)(GPIO_BASE_ADDRESS(x) + 0x0530))
#define GPIODMACTL(x) 		 *((volatile uint32_t *)(GPIO_BASE_ADDRESS(x) + 0x0534))
#define GPIOPeriphlD4(x) 	 *((volatile uint32_t *)(GPIO_BASE_ADDRESS(x) + 0x0FD0))
#define GPIOPeriphlD5(x) 	 *((volatile uint32_t *)(GPIO_BASE_ADDRESS(x) + 0x0FD4))
#define GPIOPeriphlD6(x) 	 *((volatile uint32_t *)(GPIO_BASE_ADDRESS(x) + 0x0FD8))
#define GPIOPeriphlD7(x) 	 *((volatile uint32_t *)(GPIO_BASE_ADDRESS(x) + 0x0FDC))
#define GPIOPeriphlD0(x) 	 *((volatile uint32_t *)(GPIO_BASE_ADDRESS(x) + 0x0FE0))
#define GPIOPeriphlD1(x) 	 *((volatile uint32_t *)(GPIO_BASE_ADDRESS(x) + 0x0FE4))
#define GPIOPeriphlD2(x) 	 *((volatile uint32_t *)(GPIO_BASE_ADDRESS(x) + 0x0FE8))
#define GPIOPeriphlD3(x) 	 *((volatile uint32_t *)(GPIO_BASE_ADDRESS(x) + 0x0FEC))
#define GPIOPCellD0(x) 		 *((volatile uint32_t *)(GPIO_BASE_ADDRESS(x) + 0x0FF0))
#define GPIOPCellD1(x) 		 *((volatile uint32_t *)(GPIO_BASE_ADDRESS(x) + 0x0FF4))
#define GPIOPCellD2(x) 		 *((volatile uint32_t *)(GPIO_BASE_ADDRESS(x) + 0x0FF8))
#define GPIOPCellD3(x) 		 *((volatile uint32_t *)(GPIO_BASE_ADDRESS(x) + 0x0FFC))
	
/*-----------END OF GPIO REGISTERS-----------*/


/*-----------GLOBAL STATIC VARIABLES-----------*/

/*-----------GLOBAL EXTERN VARIABLES-----------*/

/*-----------APIs IMPLEMENTATION-----------*/
void Port_Init(const Port_ConfigType *Config_Ptr);

#endif

