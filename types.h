#ifndef TYPES_H_
#define TYPES_H_

/*-----------INCLUDES-----------*/

/*-----------LOCAL MACROS-----------*/
typedef unsigned char 	uint8_t;
typedef unsigned short 	uint16_t;
typedef unsigned int 		uint32_t;


#define PIOSC_t 		16000000.0 				/*16 MHZ*/

#define NULL 0
#define HIGH 1
#define LOW 0

/*-----------GPIO PORTS-----------*/
#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3
#define PORTE 4
#define PORTF 5
/*-----------END OF GPIO PORTS-----------*/

/*-----------GPIO I/O PINS-----------*/

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

/*-----------END OF GPIO I/O PINS-----------*/

/*-----------BIT MANIPULATIONS MACRO LIKE FUNCTIONS-----------*/

#define SET_BIT(REGISTER,PIN) ( REGISTER |= (1<<PIN))

#define CLEAR_BIT(REGISTER,PIN) ( REGISTER &= ~(1U<<PIN))

#define READ_BIT(REGISTER,PIN) ((REGISTER & (1<<PIN))>>PIN)

#define TOGGLE_BIT(REGISTER,PIN) ( REGISTER ^= (1<<PIN))

/*-----------END OF BIT MANIPULATIONS MACRO LIKE FUNCTIONS-----------*/


/*-----------GLOBAL STATIC VARIABLES-----------*/

/*-----------GLOBAL EXTERN VARIABLES-----------*/

/*-----------APIs IMPLEMENTATION-----------*/

#endif
