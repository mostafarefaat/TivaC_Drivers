 /******************************************************************************
 *
 * Module: Common - Platform Types Abstraction
 *
 * File Name: std_types.h
 *
 * Description: types for ARM Cortex M4F
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/* Boolean Values */
#ifndef FALSE
#define FALSE       (0u)
#endif
#ifndef TRUE
#define TRUE        (1u)
#endif

#define HIGH        (1u)
#define LOW         (0u)

#define NULL_PTR    ((void*)0)
#define NULL    		 0
#define ERROR				 1    

typedef unsigned char         uint8;          /*           0 .. 255              */
typedef signed char           sint8;          /*        -128 .. +127             */
typedef unsigned short        uint16;         /*           0 .. 65535            */
typedef signed short          sint16;         /*      -32768 .. +32767           */
typedef unsigned long         uint32;         /*           0 .. 4294967295       */
typedef signed long           sint32;         /* -2147483648 .. +2147483647      */
typedef unsigned long long    uint64;         /*       0 .. 18446744073709551615  */
typedef signed long long      sint64;         /* -9223372036854775808 .. 9223372036854775807 */
typedef float                 float32;
typedef double                float64;

/* Boolean Data Type */
typedef uint8 boolean;

/* Pointer to Function Type */
typedef void(*cb_ptr)(void);

/************************************
 * GPIO PORTS
 ************************************/
#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3
#define PORTE 4
#define PORTF 5

/************************************
 * GPIO I/O PINS
 ************************************/
#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7
#define PIN9 8
#define PIN8 9
#define PIN10 10
#define PIN11 11
#define PIN12 12
#define PIN13 13
#define PIN14 14
#define PIN15 15
#define PIN16 16
#define PIN17 17
#define PIN18 18
#define PIN19 19
#define PIN20 20
#define PIN21 21
#define PIN22 22
#define PIN23 23
#define PIN24 24
#define PIN25 25
#define PIN26 26
#define PIN27 27
#define PIN28 28
#define PIN29 29
#define PIN30 30
#define PIN31 31
/************************************
 * BIT MANIPULATIONS
 ************************************/
#define SET_BIT(REGISTER,PIN)    ( REGISTER |= (1<<PIN))

#define CLEAR_BIT(REGISTER,PIN)  ( REGISTER &= ~(1U<<PIN))

#define READ_BIT(REGISTER,PIN)   ((REGISTER & (1<<PIN))>>PIN)

#define TOGGLE_BIT(REGISTER,PIN) ( REGISTER ^= (1<<PIN))


#endif /* STD_TYPE_H_ */
