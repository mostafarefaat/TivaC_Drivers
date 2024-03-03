 /******************************************************************************
 *
 * Module: UART0
 *
 * File Name: uart0.h
 *
 * Description: Header file for the TM4C123GH6PM UART0 driver
 *
 * Author: Edges for Training Team
 *
 *******************************************************************************/

#ifndef UART0_H_
#define UART0_H_


#include "..\STD_TYPES\std_types.h"
#include "..\MCU\MCU.h"

/*******************************************************************************
 *                             GPIO & Clock                           *
 *******************************************************************************/
#define GPIO_BASE_ADDRESS(x)	( x<4? ((0X40004000) + ((x)*0x1000)) : ((0X40024000) + ((x-4)*0x1000)) )
#define PRGPIO		 									*((volatile uint32 *)( 0x400FEA08))
#define PRUART         (*((volatile uint32 *)0x400FEA18))  

/*******************************************************************************
 *                             PreProcessor Macros                             *
 *******************************************************************************/

#define UART_DATA_5BITS          0x0
#define UART_DATA_6BITS          0x1
#define UART_DATA_7BITS          0x2
#define UART_DATA_8BITS          0x3
#define UART_LCRH_WLEN_BITS_POS  5
#define UART_CTL_UARTEN_MASK     0x00000001
#define UART_CTL_TXE_MASK        0x00000100
#define UART_CTL_RXE_MASK        0x00000200
#define UART_FR_TXFE_MASK        0x00000080
#define UART_FR_RXFE_MASK        0x00000010


/*****************************************************************************
UART0 Registers
*****************************************************************************/
#define UART0_DR_REG              (*((volatile uint32 *)0x4000C000))
#define UART0_RSR_REG             (*((volatile uint32 *)0x4000C004))
#define UART0_ECR_REG             (*((volatile uint32 *)0x4000C004))
#define UART0_FR_REG              (*((volatile uint32 *)0x4000C018))
#define UART0_ILPR_REG            (*((volatile uint32 *)0x4000C020))
#define UART0_IBRD_REG            (*((volatile uint32 *)0x4000C024))
#define UART0_FBRD_REG            (*((volatile uint32 *)0x4000C028))
#define UART0_LCRH_REG            (*((volatile uint32 *)0x4000C02C))
#define UART0_CTL_REG             (*((volatile uint32 *)0x4000C030))
#define UART0_IFLS_REG            (*((volatile uint32 *)0x4000C034))
#define UART0_IM_REG              (*((volatile uint32 *)0x4000C038))
#define UART0_RIS_REG             (*((volatile uint32 *)0x4000C03C))
#define UART0_MIS_REG             (*((volatile uint32 *)0x4000C040))
#define UART0_ICR_REG             (*((volatile uint32 *)0x4000C044))
#define UART0_DMACTL_REG          (*((volatile uint32 *)0x4000C048))
#define UART0_9BITADDR_REG        (*((volatile uint32 *)0x4000C0A4))
#define UART0_9BITAMASK_REG       (*((volatile uint32 *)0x4000C0A8))
#define UART0_PP_REG              (*((volatile uint32 *)0x4000CFC0))
#define UART0_CC_REG              (*((volatile uint32 *)0x4000CFC8))
	

#define GPIOAMSEL(x) 			 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x0528))
#define GPIODIR(x) 				 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x0400))
#define GPIOAFSEL(x) 			 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x0420))
#define GPIOPCTL(x) 			 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x052C))
#define GPIODEN(x) 				 *((volatile uint32 *)(GPIO_BASE_ADDRESS(x) + 0x051C))



/*******************************************************************************
 *                            Functions Prototypes                             *
 *******************************************************************************/

extern void UART0_Init(void);

extern void UART0_SendByte(uint8 data);

extern uint8 UART0_ReceiveByte(void);

extern void UART0_SendData(const uint8 *pData, uint32 uSize);

extern void UART0_ReceiveData(uint8 *pData, uint32 uSize);

extern void UART0_SendString(const uint8 *pData);

extern void UART0_ReceiveString(uint8 *pData);

#endif
