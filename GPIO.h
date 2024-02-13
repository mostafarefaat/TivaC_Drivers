/**
 ********************************************************************************
 * @file    GPIO.h
 * @author  Mostafa Refaat
 * @date    31/1/2024
 * @brief   
 ********************************************************************************
 */

#ifndef GPIO_H_
#define GPIO_H_

/************************************
 * INCLUDES
 ************************************/
#include "std_types.h"
#include "MCU.h"

/************************************
 * MACROS AND DEFINES
 ************************************/
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

#define UNLOCK_VALUE     			0x4C4F434B
#define LOCK_VALUE     	 			0x00000001

/************************************
 * TYPEDEFS
 ************************************/
typedef uint8     PortType;
typedef uint8     PinNumType;
typedef uint8     PinModeType;
typedef uint8     PinDirectionType;
typedef uint8     PinLevelType;
typedef uint8     PinOutputCurrentType;
typedef uint8     PinInternalAttachType;

/************************************
 * EXPORTED VARIABLES
 ************************************/
/************************************
 * ENUMS
 ************************************/
enum OutputCurrent
{
	CURRENT_2mA, CURRENT_4mA, CURRENT_8mA
};

enum Direction
{
	INTPUT, OUTPUT
};

enum InternalAttachType
{
	PUR, PDR, ODR
};

enum PinMode                       /*TODO: ADD THE REST OF THE MODES*/
{
	DEN, ANLG, ALTER
};
enum Alter_FuncType                    /*TODO: ADD THE ALTERNATE FUNCTION */
{
	uart, can, pwm,
};
/************************************
 * STRUCTURES
 ************************************/
typedef struct
{
	PortType										Port;
	PinNumType									Pin_Num;
	PinModeType 						    Pin_Mode;
	PinModeType 								Pin_Alter_Mode;
	PinDirectionType 						Pin_Direction;
	PinLevelType 								Pin_Level;
	PinOutputCurrentType 				Pin_Current;
	PinInternalAttachType 			Pin_Internal_Attach;
	
}Port_ConfigType;

/************************************
 * GPIO REGISTERS  (PAGE 660)
 ************************************/
#define GPIODATA(x) 			 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x03FC))
#define GPIODIR(x) 				 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x0400))
#define GPIOIS(x) 				 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x0404))
#define GPIOIBE(x) 				 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x0408))
#define GPIOIEV(x) 				 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x040C))
#define GPIOIM(x) 				 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x0410))
#define GPIORIS(x) 				 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x0414))
#define GPIOMIS(x) 				 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x0418))
#define GPIOICR(x) 				 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x041C))
#define GPIOAFSEL(x) 			 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x0420))
#define GPIODR2R(x) 			 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x0500))
#define GPIODR4R(x) 			 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x0504))
#define GPIODR8R(x) 			 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x0508))
#define GPIOODR(x) 				 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x050C))
#define GPIOPUR(x) 				 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x0510))	
#define GPIOPDR(x) 				 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x0514))
#define GPIOSLR(x) 				 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x0518))
#define GPIODEN(x) 				 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x051C))
#define GPIOLOCK(x) 			 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x0520))
#define GPIOCR(x) 				 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x0524))
#define GPIOAMSEL(x) 			 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x0528))
#define GPIOPCTL(x) 			 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x052C))
#define GPIOADCCTL(x) 		 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x0530))
#define GPIODMACTL(x) 		 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x0534))
#define GPIOPeriphlD4(x) 	 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x0FD0))
#define GPIOPeriphlD5(x) 	 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x0FD4))
#define GPIOPeriphlD6(x) 	 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x0FD8))
#define GPIOPeriphlD7(x) 	 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x0FDC))
#define GPIOPeriphlD0(x) 	 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x0FE0))
#define GPIOPeriphlD1(x) 	 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x0FE4))
#define GPIOPeriphlD2(x) 	 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x0FE8))
#define GPIOPeriphlD3(x) 	 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x0FEC))
#define GPIOPCellD0(x) 		 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x0FF0))
#define GPIOPCellD1(x) 		 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x0FF4))
#define GPIOPCellD2(x) 		 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x0FF8))
#define GPIOPCellD3(x) 		 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x0FFC))
/************************************
 * GPIO DATA REGISTER Bit Banding
 ************************************/
#define bit_0_addr_offset			0x0004
#define bit_1_addr_offset			0x0008
#define bit_2_addr_offset			0x0010
#define bit_3_addr_offset			0x0020
#define bit_4_addr_offset			0x0040
#define bit_5_addr_offset			0x0080
#define bit_6_addr_offset			0x0100
#define bit_7_addr_offset			0x0200

#define bit_0_high			0x01
#define bit_1_high			0x02
#define bit_2_high			0x04
#define bit_3_high			0x08
#define bit_4_high			0x10
#define bit_5_high			0x20
#define bit_6_high			0x40
#define bit_7_high			0x80

#define PA0 *((volatile uint32 *)(GPIO_BASE_ADDRESS(0) + bit_0_addr_offset))
#define PA1 *((volatile uint32 *)(GPIO_BASE_ADDRESS(0) + bit_1_addr_offset))
#define PA2 *((volatile uint32 *)(GPIO_BASE_ADDRESS(0) + bit_2_addr_offset))
#define PA3 *((volatile uint32 *)(GPIO_BASE_ADDRESS(0) + bit_3_addr_offset))
#define PA4 *((volatile uint32 *)(GPIO_BASE_ADDRESS(0) + bit_4_addr_offset))
#define PA5 *((volatile uint32 *)(GPIO_BASE_ADDRESS(0) + bit_5_addr_offset))
#define PA6 *((volatile uint32 *)(GPIO_BASE_ADDRESS(0) + bit_6_addr_offset))
#define PA7 *((volatile uint32 *)(GPIO_BASE_ADDRESS(0) + bit_7_addr_offset))

#define PB0 *((volatile uint32 *)(GPIO_BASE_ADDRESS(1) + bit_0_addr_offset))
#define PB1 *((volatile uint32 *)(GPIO_BASE_ADDRESS(1) + bit_1_addr_offset))
#define PB2 *((volatile uint32 *)(GPIO_BASE_ADDRESS(1) + bit_2_addr_offset))
#define PB3 *((volatile uint32 *)(GPIO_BASE_ADDRESS(1) + bit_3_addr_offset))
#define PB4 *((volatile uint32 *)(GPIO_BASE_ADDRESS(1) + bit_4_addr_offset))
#define PB5 *((volatile uint32 *)(GPIO_BASE_ADDRESS(1) + bit_5_addr_offset))
#define PB6 *((volatile uint32 *)(GPIO_BASE_ADDRESS(1) + bit_6_addr_offset))
#define PB7 *((volatile uint32 *)(GPIO_BASE_ADDRESS(1) + bit_7_addr_offset))
	
#define PC0 *((volatile uint32 *)(GPIO_BASE_ADDRESS(2) + bit_0_addr_offset))
#define PC1 *((volatile uint32 *)(GPIO_BASE_ADDRESS(2) + bit_1_addr_offset))
#define PC2 *((volatile uint32 *)(GPIO_BASE_ADDRESS(2) + bit_2_addr_offset))
#define PC3 *((volatile uint32 *)(GPIO_BASE_ADDRESS(2) + bit_3_addr_offset))
#define PC4 *((volatile uint32 *)(GPIO_BASE_ADDRESS(2) + bit_4_addr_offset))
#define PC5 *((volatile uint32 *)(GPIO_BASE_ADDRESS(2) + bit_5_addr_offset))
#define PC6 *((volatile uint32 *)(GPIO_BASE_ADDRESS(2) + bit_6_addr_offset))
#define PC7 *((volatile uint32 *)(GPIO_BASE_ADDRESS(2) + bit_7_addr_offset))
	
#define PD0 *((volatile uint32 *)(GPIO_BASE_ADDRESS(3) + bit_0_addr_offset))
#define PD1 *((volatile uint32 *)(GPIO_BASE_ADDRESS(3) + bit_1_addr_offset))
#define PD2 *((volatile uint32 *)(GPIO_BASE_ADDRESS(3) + bit_2_addr_offset))
#define PD3 *((volatile uint32 *)(GPIO_BASE_ADDRESS(3) + bit_3_addr_offset))
#define PD4 *((volatile uint32 *)(GPIO_BASE_ADDRESS(3) + bit_4_addr_offset))
#define PD5 *((volatile uint32 *)(GPIO_BASE_ADDRESS(3) + bit_5_addr_offset))
#define PD6 *((volatile uint32 *)(GPIO_BASE_ADDRESS(3) + bit_6_addr_offset))
#define PD7 *((volatile uint32 *)(GPIO_BASE_ADDRESS(3) + bit_7_addr_offset))
	
#define PE0 *((volatile uint32 *)(GPIO_BASE_ADDRESS(4) + bit_0_addr_offset))
#define PE1 *((volatile uint32 *)(GPIO_BASE_ADDRESS(4) + bit_1_addr_offset))
#define PE2 *((volatile uint32 *)(GPIO_BASE_ADDRESS(4) + bit_2_addr_offset))
#define PE3 *((volatile uint32 *)(GPIO_BASE_ADDRESS(4) + bit_3_addr_offset))
#define PE4 *((volatile uint32 *)(GPIO_BASE_ADDRESS(4) + bit_4_addr_offset))
#define PE5 *((volatile uint32 *)(GPIO_BASE_ADDRESS(4) + bit_5_addr_offset))
	
#define PF0 *((volatile uint32 *)(GPIO_BASE_ADDRESS(5) + bit_0_addr_offset))
#define PF1 *((volatile uint32 *)(GPIO_BASE_ADDRESS(5) + bit_1_addr_offset))
#define PF2 *((volatile uint32 *)(GPIO_BASE_ADDRESS(5) + bit_2_addr_offset))
#define PF3 *((volatile uint32 *)(GPIO_BASE_ADDRESS(5) + bit_3_addr_offset))
#define PF4 *((volatile uint32 *)(GPIO_BASE_ADDRESS(5) + bit_4_addr_offset))

/************************************
 * GLOBAL FUNCTION PROTOTYPES
 ************************************/

uint8 Port_Init(const Port_ConfigType *Port_Config_Ptr, uint8 Num_of_pins );

uint8 Read_Pin(volatile uint32 *PORT, uint8 PIN);
uint8 Read_Port(volatile uint32 *PORT);
uint8 Write_Pin(volatile uint32 *PORT, uint8 PIN, uint8 LEVEL);
uint8 Write_Port(volatile uint32 *PORT, uint32 VALUE_HEX);
uint8 Toggle_Pin(volatile uint32 *PORT, uint8 PIN);

void register_gpio_cb(cb_ptr Ptr);

void GPIOF_Handler(void);


#endif

