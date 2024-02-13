#ifndef GPTM_H_
#define GPTM_H_
/*-----------INCLUDES-----------*/
#include "GPIO.h"
#include "MCU.h"

/*-----------TYPE DEFs-----------*/
typedef uint8  Gpt_ChannelType;
typedef double Gpt_ValueType;
typedef uint32 Gpt_ChannelTickFrequencyType;
typedef uint32 Gpt_ChannelTickValueMaxType;
typedef uint8	 Gpt_ChannelModeType;
typedef uint8	 Gpt_CountDirType;
typedef uint8  Gpt_EventModeType;
typedef uint8  Gpt_CaptureModeType;
typedef uint8  Gpt_ConcateType;


/*--------------------------------*/
enum timer_module
{
	TIMER0, TIMER1, TIMER2, TIMER3, TIMER4, TIMER5,
};

enum event_mode
{
	pos_edge, neg_edge, reserved, both_edges
	
};

typedef struct
{
	Gpt_ChannelType				                Gpt_Channel_ID;             /*TIMER_0 TO TIMER_5*/
	Gpt_ChannelType												Gpt_Timer;									/*TIMER_A OR TIMER_B*/
	Gpt_ChannelTickFrequencyType					Gpt_ChannelTickFrequency;
	Gpt_ChannelTickValueMaxType						Gpt_ChannelTickValueMax;
	
	Gpt_ChannelModeType										Gpt_ChannelMode;			    /*ONESHOOT or PERIODIC or CAPTURE*/
	Gpt_CountDirType											Gpt_CountDir;							/*UP or DOWN*/												
	Gpt_EventModeType											Gpt_EventMode;						/*POS or NEG or BOTH*/
	Gpt_CaptureModeType										Gpt_CaptureMode;					/*EDGE COUNT or EDGE TIMER*/
	Gpt_ConcateType												Gpt_Timer16_32_Concate;		/*USED WHEN NEED TO USE TIMER16_32 IN CONCATE MODE PUT NULL IF NOT NEEDED*/
	
	cb_ptr																Gpt_Notificaton;
	
}Gpt_ConfigType;
/*--------------------------------*/

/*-----------MACROS-----------*/
#define NUM_OF_TIMERS_Config 				1
#define MAX_TICKS_16bit							65536
#define MAX_TICKS_32bit							4294967295
#define MAX_DELAY_16bit							4    //ms    	/*IN CASE 16MHZ*/ 
#define MAX_DELAY_32bit							268  //ms     /*IN CASE 16MHZ*/
/*---------------------------*/
#define TIMER0_16_32	0
#define TIMER1_16_32	1
#define TIMER2_16_32	2
#define TIMER3_16_32	3
#define TIMER4_16_32	4
#define TIMER5_16_32	5
/*---------------------------*/
#define TIMER0_32_64	6
#define TIMER1_32_64	7
#define TIMER2_32_64	0xC
#define TIMER3_32_64	0xD
#define TIMER4_32_64	0xE
#define TIMER5_32_64	0xF
/*---------------------------*/
#define TIMERA			0
#define TIMERB  		1
/*---------------------------*/
#define TIMER_16_32  0
#define TIMER_32_64  1
/*---------------------------*/
#define TIMER_16		 0
#define TIMER_32		 1
#define TIMER_64     2
/*---------------------------*/
#define ONESHOT      1
#define PERIODIC  	 2
#define CAPTURE			 3
/*---------------------------*/
#define EDGE_COUNT   0
#define EDGE_TIME	   1
/*---------------------------*/
#define UP_COUNT   	 1
#define DOWN_COUNT	 0
/*---------------------------*/
#define GPTMCFG_TIMER_MASK 		0xFFFFFFF8
#define GPTMTnMR_TIMER_MASK		0xFFFFFFFC
#define GPTMCTL_TIMERA_MASK		0xFFFFFFF3
#define GPTMCTL_TIMERB_MASK		0xFFFFF3FF
/*-----------GPTMTAMR Pins -----------*/
//#define TAMR			0 , 1
#define TACMR				2
#define TAAMS				3
#define TACDIR			4
#define TAMIE				5
#define TAWOT				6
#define TASNAPS			7
#define TAILD				8
#define TAPWMIE			9
#define TAMRSU			10
#define TAPLO				11
/*-----------GPTMTBMR Pins -----------*/
//#define TBMR			0 , 1
#define TBCMR				2
#define TBAMS				3
#define TBCDIR			4
#define TBMIE				5
#define TBWOT				6
#define TBSNAPS			7
#define TBILD				8
#define TBPWMIE			9
#define TBMRSU			10
#define TBPLO				11
/*-----------GPTMCTL Pins -----------*/
#define TAEN			0
#define TASTALL		1
//#define TAEVENT	2 , 3	
#define RTCEN			4
#define TAOTE			5
#define TAPWML		6
#define TBEN			8
#define TBSTALL		9
//#define TBEVENT	10 ,11	
#define TBOTE			13
#define TBPWML		14
/*-----------GPTMICR Pins -----------*/
#define TATOCINT				0
#define CAMCINT					1
#define CAECINT					2
#define RTCCINT					3
#define TAMCINT					4
#define TBTOCINT				8
#define CBMCINT					9
#define CBECINT					10
#define TBMCINT					11
/*-----------GPTMIMR Pins -----------*/
#define TATOIM				0
#define CAMIM					1
#define CAEIM					2
#define RTCIM					3
#define TAMIM					4
#define TBTOIM				8
#define CBMIM					9
#define CBEIM					10
#define TBMIM					11
/*-----------GPTMRIS Pins -----------*/
#define TATORIS				  0
#define CAMRIS					1         
#define CAERIS					2
#define RTCRIS					3
#define TAMRIS 					4
#define TBTORIS				  8
#define CBMRIS					9
#define CBERIS					10
#define TBMRIS					11
/*-----------GPTMMIS Pins -----------*/
#define TATOMIS				  0
#define CAMMIS					1         
#define CAEMIS					2
#define RTCMIS					3
#define TAMMIS 					4
#define TBTOMIS				  8
#define CBMMIS					9
#define CBEMIS					10
#define TBMMIS					11
/*---------------------------*/

#define GPTM_BASE_ADDRESS(x)	( x<8? ((0X40030000) + ((x)*0x1000)) : ((0X40040000) + ((x)*0x1000)) )
/*-----------TIMERS REGISTERS-----------*/  /*PAGE 726*/
#define GPTMCFG(x) 			 	 *((volatile uint32 *)(GPTM_BASE_ADDRESS(x) + 0x000))
#define GPTMTAMR(x) 			 *((volatile uint32 *)(GPTM_BASE_ADDRESS(x) + 0x004))
#define GPTMTBMR(x) 			 *((volatile uint32 *)(GPTM_BASE_ADDRESS(x) + 0x008))
#define GPTMCTL(x) 			   *((volatile uint32 *)(GPTM_BASE_ADDRESS(x) + 0x00C))
#define GPTMSYNC(x) 			 *((volatile uint32 *)(GPTM_BASE_ADDRESS(x) + 0x010))
#define GPTMIMR(x) 			   *((volatile uint32 *)(GPTM_BASE_ADDRESS(x) + 0x018))
#define GPTMRIS(x) 			   *((volatile uint32 *)(GPTM_BASE_ADDRESS(x) + 0x01C))
#define GPTMMIS(x) 			   *((volatile uint32 *)(GPTM_BASE_ADDRESS(x) + 0x020))
#define GPTMICR(x) 			   *((volatile uint32 *)(GPTM_BASE_ADDRESS(x) + 0x024))
#define GPTMTAILR(x) 			 *((volatile uint32 *)(GPTM_BASE_ADDRESS(x) + 0x028))
#define GPTMTBILR(x) 			 *((volatile uint32 *)(GPTM_BASE_ADDRESS(x) + 0x02C))
#define GPTMTAMATCHR(x) 	 *((volatile uint32 *)(GPTM_BASE_ADDRESS(x) + 0x030))
#define GPTMTBMATCHR(x) 	 *((volatile uint32 *)(GPTM_BASE_ADDRESS(x) + 0x034))
#define GPTMTAPR(x) 			 *((volatile uint32 *)(GPTM_BASE_ADDRESS(x) + 0x038))
#define GPTMTBPR(x) 			 *((volatile uint32 *)(GPTM_BASE_ADDRESS(x) + 0x03C))
#define GPTMTAPMR(x) 			 *((volatile uint32 *)(GPTM_BASE_ADDRESS(x) + 0x040))
#define GPTMTBPMR(x) 			 *((volatile uint32 *)(GPTM_BASE_ADDRESS(x) + 0x044))
#define GPTMTAR(x) 			   *((volatile uint32 *)(GPTM_BASE_ADDRESS(x) + 0x048))
#define GPTMTBR(x) 			   *((volatile uint32 *)(GPTM_BASE_ADDRESS(x) + 0x04C))
#define GPTMTAV(x) 			   *((volatile uint32 *)(GPTM_BASE_ADDRESS(x) + 0x050))
#define GPTMTBV(x) 			   *((volatile uint32 *)(GPTM_BASE_ADDRESS(x) + 0x054))
#define GPTMRTCPD(x) 			 *((volatile uint32 *)(GPTM_BASE_ADDRESS(x) + 0x058))
#define GPTMTAPS(x) 			 *((volatile uint32 *)(GPTM_BASE_ADDRESS(x) + 0x05C))
#define GPTMTBPS(x) 			 *((volatile uint32 *)(GPTM_BASE_ADDRESS(x) + 0x060))
#define GPTMTAPV(x) 			 *((volatile uint32 *)(GPTM_BASE_ADDRESS(x) + 0x064))
#define GPTMTBPV(x) 			 *((volatile uint32 *)(GPTM_BASE_ADDRESS(x) + 0x068))
#define GPTMPP(x) 			   *((volatile uint32 *)(GPTM_BASE_ADDRESS(x) + 0xFC0))
	
#define PRTIMER_16_32 		*((volatile uint32 *)0x400FEA04)

/*#define GPTMCFG_TIMER0_16_32 		*((volatile uint32 *)0x40030000)
#define GPTMCFG_TIMER1_16_32 		*((volatile uint32 *)0x40031000)
#define GPTMCFG_TIMER2_16_32 		*((volatile uint32 *)0x40032000)
#define GPTMCFG_TIMER3_16_32 		*((volatile uint32 *)0x40033000)
#define GPTMCFG_TIMER4_16_32 		*((volatile uint32 *)0x40034000)
#define GPTMCFG_TIMER5_16_32 		*((volatile uint32 *)0x40035000)

#define GPTMCFG_TIMER0_32_64 		*((volatile uint32 *)0x40036000)
#define GPTMCFG_TIMER1_32_64 		*((volatile uint32 *)0x40037000)
#define GPTMCFG_TIMER2_32_64 		*((volatile uint32 *)0x4004C000)
#define GPTMCFG_TIMER3_32_64 		*((volatile uint32 *)0x4004D000)
#define GPTMCFG_TIMER4_32_64 		*((volatile uint32 *)0x4004E000)
#define GPTMCFG_TIMER5_32_64 		*((volatile uint32 *)0x4004F000)
	
#define GPTMTAMR_TIMER0_16_32 		*((volatile uint32 *)0x40030004)
#define GPTMTAMR_TIMER1_16_32 		*((volatile uint32 *)0x40031004)
#define GPTMTAMR_TIMER2_16_32 		*((volatile uint32 *)0x40032004)
#define GPTMTAMR_TIMER3_16_32 		*((volatile uint32 *)0x40033004)
#define GPTMTAMR_TIMER4_16_32 		*((volatile uint32 *)0x40034004)
#define GPTMTAMR_TIMER5_16_32 		*((volatile uint32 *)0x40035004)

#define GPTMTAMR_TIMER0_32_64 		*((volatile uint32 *)0x40036004)
#define GPTMTAMR_TIMER1_32_64 		*((volatile uint32 *)0x40037004)
#define GPTMTAMR_TIMER2_32_64 		*((volatile uint32 *)0x4004C004)
#define GPTMTAMR_TIMER3_32_64 		*((volatile uint32 *)0x4004D004)
#define GPTMTAMR_TIMER4_32_64 		*((volatile uint32 *)0x4004E004)
#define GPTMTAMR_TIMER5_32_64 		*((volatile uint32 *)0x4004F004)
	
#define GPTMCTL_TIMER0_16_32 		*((volatile uint32 *)0x4003000C)
#define GPTMCTL_TIMER1_16_32 		*((volatile uint32 *)0x4003100C)
#define GPTMCTL_TIMER2_16_32 		*((volatile uint32 *)0x4003200C)
#define GPTMCTL_TIMER3_16_32 		*((volatile uint32 *)0x4003300C)
#define GPTMCTL_TIMER4_16_32 		*((volatile uint32 *)0x4003400C)
#define GPTMCTL_TIMER5_16_32 		*((volatile uint32 *)0x4003500C)

#define GPTMCTL_TIMER0_32_64 		*((volatile uint32 *)0x4003600C)
#define GPTMCTL_TIMER1_32_64 		*((volatile uint32 *)0x4003700C)
#define GPTMCTL_TIMER2_32_64 		*((volatile uint32 *)0x4004C00C)
#define GPTMCTL_TIMER3_32_64 		*((volatile uint32 *)0x4004D00C)
#define GPTMCTL_TIMER4_32_64 		*((volatile uint32 *)0x4004E00C)
#define GPTMCTL_TIMER5_32_64 		*((volatile uint32 *)0x4004F00C)
	
#define GPTMTAPR_TIMER0_16_32 		*((volatile uint32 *)0x40030038)
#define GPTMTAPR_TIMER1_16_32 		*((volatile uint32 *)0x40031038)
#define GPTMTAPR_TIMER2_16_32 		*((volatile uint32 *)0x40032038)
#define GPTMTAPR_TIMER3_16_32 		*((volatile uint32 *)0x40033038)
#define GPTMTAPR_TIMER4_16_32 		*((volatile uint32 *)0x40034038)
#define GPTMTAPR_TIMER5_16_32 		*((volatile uint32 *)0x40035038)

#define GPTMTAPR_TIMER0_32_64 		*((volatile uint32 *)0x40036038)
#define GPTMTAPR_TIMER1_32_64 		*((volatile uint32 *)0x40037038)
#define GPTMTAPR_TIMER2_32_64 		*((volatile uint32 *)0x4004C038)
#define GPTMTAPR_TIMER3_32_64 		*((volatile uint32 *)0x4004D038)
#define GPTMTAPR_TIMER4_32_64 		*((volatile uint32 *)0x4004E038)
#define GPTMTAPR_TIMER5_32_64 		*((volatile uint32 *)0x4004F038)
	
#define GPTMTAILR_TIMER0_16_32 		*((volatile uint32 *)0x40030028)
#define GPTMTAILR_TIMER1_16_32 		*((volatile uint32 *)0x40031028)
#define GPTMTAILR_TIMER2_16_32 		*((volatile uint32 *)0x40032028)
#define GPTMTAILR_TIMER3_16_32 		*((volatile uint32 *)0x40033028)
#define GPTMTAILR_TIMER4_16_32 		*((volatile uint32 *)0x40034028)
#define GPTMTAILR_TIMER5_16_32 		*((volatile uint32 *)0x40035028)

#define GPTMTAILR_TIMER0_32_64 		*((volatile uint32 *)0x40036028)
#define GPTMTAILR_TIMER1_32_64 		*((volatile uint32 *)0x40037028)
#define GPTMTAILR_TIMER2_32_64 		*((volatile uint32 *)0x4004C028)
#define GPTMTAILR_TIMER3_32_64 		*((volatile uint32 *)0x4004D028)
#define GPTMTAILR_TIMER4_32_64 		*((volatile uint32 *)0x4004E028)
#define GPTMTAILR_TIMER5_32_64 		*((volatile uint32 *)0x4004F028)
	
#define GPTMICR_TIMER0_16_32 		*((volatile uint32 *)0x40030024)
#define GPTMICR_TIMER1_16_32 		*((volatile uint32 *)0x40031024)
#define GPTMICR_TIMER2_16_32 		*((volatile uint32 *)0x40032024)
#define GPTMICR_TIMER3_16_32 		*((volatile uint32 *)0x40033024)
#define GPTMICR_TIMER4_16_32 		*((volatile uint32 *)0x40034024)
#define GPTMICR_TIMER5_16_32 		*((volatile uint32 *)0x40035024)

#define GPTMICR_TIMER0_32_64 		*((volatile uint32 *)0x40036024)
#define GPTMICR_TIMER1_32_64 		*((volatile uint32 *)0x40037024)
#define GPTMICR_TIMER2_32_64 		*((volatile uint32 *)0x4004C024)
#define GPTMICR_TIMER3_32_64 		*((volatile uint32 *)0x4004D024)
#define GPTMICR_TIMER4_32_64 		*((volatile uint32 *)0x4004E024)
#define GPTMICR_TIMER5_32_64 		*((volatile uint32 *)0x4004F024)
	
#define GPTMIMR_TIMER0_16_32 		*((volatile uint32 *)0x40030018)
#define GPTMIMR_TIMER1_16_32 		*((volatile uint32 *)0x40031018)
#define GPTMIMR_TIMER2_16_32 		*((volatile uint32 *)0x40032018)
#define GPTMIMR_TIMER3_16_32 		*((volatile uint32 *)0x40033018)
#define GPTMIMR_TIMER4_16_32 		*((volatile uint32 *)0x40034018)
#define GPTMIMR_TIMER5_16_32 		*((volatile uint32 *)0x40035018)

#define GPTMIMR_TIMER0_32_64 		*((volatile uint32 *)0x40036018)
#define GPTMIMR_TIMER1_32_64 		*((volatile uint32 *)0x40037018)
#define GPTMIMR_TIMER2_32_64 		*((volatile uint32 *)0x4004C018)
#define GPTMIMR_TIMER3_32_64 		*((volatile uint32 *)0x4004D018)
#define GPTMIMR_TIMER4_32_64 		*((volatile uint32 *)0x4004E018)
#define GPTMIMR_TIMER5_32_64 		*((volatile uint32 *)0x4004F018*/

/*-----------END OF TIMERS REGISTERS-----------*/ 

/*-----------ENUMs AND STRUCTs-----------*/

/*-----------GLOBAL STATIC VARIABLES-----------*/

/*-----------GLOBAL EXTERN VARIABLES-----------*/

/*-----------APIs FUNCTIONS DECLARATION-----------*/


void Gpt_Init(const Gpt_ConfigType *ConfigPtr);
void Gpt_EnableNotification(Gpt_ChannelType timermodule, Gpt_ChannelType Timer);
void Gpt_DisableNotification(Gpt_ChannelType timermodule, Gpt_ChannelType Timer);

void Gpt_StartTimer(Gpt_ChannelType module, Gpt_ChannelType Timer, Gpt_ValueType Value);
void Gpt_StopTimer(Gpt_ChannelType module, Gpt_ChannelType Timer);


void register_timer1A_cb(cb_ptr Ptr);
void TIMER1A_Handler(void);
void WTIMER1B_Handler(void);

#endif

