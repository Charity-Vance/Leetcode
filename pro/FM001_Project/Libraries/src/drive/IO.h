
///*****************************************************************************************///
///*Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     IO.h
///*Version:       V1
///*Date:          2017-9-18
///*Description:   
///*Function List: 
///*****************************************************************************************///
#ifndef	_IO_H
#define _IO_H

#include "FM33A0XX.h"
#include "Public.h"

//static	ulong32	SV_ulTemp_GPIO;			///*用于SFR的读->修改->写*///

//#define	AFRL		AFR[0]
//#define	AFRH		AFR[1]

///*****************************************************************************************///

///*****************************************************************************************///
#define GPIO_Pin_0					((ulong32)0x00000001)	///* Pin 0 selected *///
#define GPIO_Pin_1					((ulong32)0x00000002)	///* Pin 1 selected *///
#define GPIO_Pin_2					((ulong32)0x00000004)	///* Pin 2 selected *///
#define GPIO_Pin_3					((ulong32)0x00000008)	///* Pin 3 selected *///
#define GPIO_Pin_4					((ulong32)0x00000010)	///* Pin 4 selected *///
#define GPIO_Pin_5					((ulong32)0x00000020)	///* Pin 5 selected *///
#define GPIO_Pin_6					((ulong32)0x00000040)	///* Pin 6 selected *///
#define GPIO_Pin_7					((ulong32)0x00000080)	///* Pin 7 selected *///
#define GPIO_Pin_8					((ulong32)0x00000100)	///* Pin 8 selected *///
#define GPIO_Pin_9					((ulong32)0x00000200)	///* Pin 9 selected *///
#define GPIO_Pin_10					((ulong32)0x00000400)	///* Pin 10 selected *///
#define GPIO_Pin_11					((ulong32)0x00000800)	///* Pin 11 selected *///
#define GPIO_Pin_12					((ulong32)0x00001000)	///* Pin 12 selected *///
#define GPIO_Pin_13					((ulong32)0x00002000)	///* Pin 13 selected *///
#define GPIO_Pin_14					((ulong32)0x00004000)	///* Pin 14 selected *///
#define GPIO_Pin_15					((ulong32)0x00008000)	///* Pin 15 selected *///
#define GPIO_Pin_All				((ulong32)0x0000ffff)	///* All pins selected *///


#define		BIT15ANOLOG			((ulong32)0xc0000000)
#define		BIT15AFMODE			((ulong32)0x80000000)
#define		BIT15OUTMODE		((ulong32)0x40000000)
#define		BIT15INMODE			((ulong32)0x3fffffff)

#define		BIT14ANOLOG			((ulong32)0x30000000)
#define		BIT14AFMODE			((ulong32)0x20000000)
#define		BIT14OUTMODE		((ulong32)0x10000000)
#define		BIT14INMODE			((ulong32)0xcfffffff)

#define		BIT13ANOLOG			((ulong32)0x0c000000)
#define		BIT13AFMODE			((ulong32)0x08000000)
#define		BIT13OUTMODE		((ulong32)0x04000000)
#define		BIT13INMODE			((ulong32)0xf3ffffff)

#define		BIT12ANOLOG			((ulong32)0x03000000)
#define		BIT12AFMODE			((ulong32)0x02000000)
#define		BIT12OUTMODE		((ulong32)0x01000000)
#define		BIT12INMODE			((ulong32)0xfcffffff)

#define		BIT11ANOLOG			((ulong32)0x00c00000)
#define		BIT11AFMODE			((ulong32)0x00800000)
#define		BIT11OUTMODE		((ulong32)0x00400000)
#define		BIT11INMODE			((ulong32)0xff3fffff)

#define		BIT10ANOLOG			((ulong32)0x00300000)
#define		BIT10AFMODE			((ulong32)0x00200000)
#define		BIT10OUTMODE		((ulong32)0x00100000)
#define		BIT10INMODE			((ulong32)0xffcfffff)

#define		BIT9ANOLOG			((ulong32)0x000c0000)
#define		BIT9AFMODE			((ulong32)0x00080000)
#define		BIT9OUTMODE			((ulong32)0x00040000)
#define		BIT9INMODE			((ulong32)0xfff3ffff)

#define		BIT8ANOLOG			((ulong32)0x00030000)
#define		BIT8AFMODE			((ulong32)0x00020000)
#define		BIT8OUTMODE			((ulong32)0x00010000)
#define		BIT8INMODE			((ulong32)0xfffcffff)

#define		BIT7ANOLOG			((ulong32)0x0000c000)
#define		BIT7AFMODE			((ulong32)0x00008000)
#define		BIT7OUTMODE			((ulong32)0x00004000)
#define		BIT7INMODE			((ulong32)0xffff3fff)

#define		BIT6ANOLOG			((ulong32)0x00003000)
#define		BIT6AFMODE			((ulong32)0x00002000)
#define		BIT6OUTMODE			((ulong32)0x00001000)
#define		BIT6INMODE			((ulong32)0xffffcfff)

#define		BIT5ANOLOG			((ulong32)0x00000c00)
#define		BIT5AFMODE			((ulong32)0x00000800)
#define		BIT5OUTMODE			((ulong32)0x00000400)
#define		BIT5INMODE			((ulong32)0xfffff3ff)

#define		BIT4ANOLOG			((ulong32)0x00000300)
#define		BIT4AFMODE			((ulong32)0x00000200)
#define		BIT4OUTMODE			((ulong32)0x00000100)
#define		BIT4INMODE			((ulong32)0xfffffcff)

#define		BIT3ANOLOG			((ulong32)0x000000c0)
#define		BIT3AFMODE			((ulong32)0x00000080)
#define		BIT3OUTMODE			((ulong32)0x00000040)
#define		BIT3INMODE			((ulong32)0xffffff3f)

#define		BIT2ANOLOG			((ulong32)0x00000030)
#define		BIT2AFMODE			((ulong32)0x00000020)
#define		BIT2OUTMODE			((ulong32)0x00000010)
#define		BIT2INMODE			((ulong32)0xffffffcf)

#define		BIT1ANOLOG			((ulong32)0x0000000c)
#define		BIT1AFMODE			((ulong32)0x00000008)
#define		BIT1OUTMODE			((ulong32)0x00000004)
#define		BIT1INMODE			((ulong32)0xfffffff3)

#define		BIT0ANOLOG			((ulong32)0x00000003)
#define		BIT0AFMODE			((ulong32)0x00000002)
#define		BIT0OUTMODE			((ulong32)0x00000001)
#define		BIT0INMODE			((ulong32)0xfffffffc)

#define		BIT15OUTPP			((ulong32)0xffff7fff)
#define		BIT15OUTOD			((ulong32)0x00008000)

#define		BIT14OUTPP			((ulong32)0xffffbfff)
#define		BIT14OUTOD			((ulong32)0x00004000)

#define		BIT13OUTPP			((ulong32)0xffffdfff)
#define		BIT13OUTOD			((ulong32)0x00002000)

#define		BIT12OUTPP			((ulong32)0xffffefff)
#define		BIT12OUTOD			((ulong32)0x00001000)

#define		BIT11OUTPP			((ulong32)0xfffff7ff)
#define		BIT11OUTOD			((ulong32)0x00000800)

#define		BIT10OUTPP			((ulong32)0xfffffbff)
#define		BIT10OUTOD			((ulong32)0x00000400)

#define		BIT9OUTPP			((ulong32)0xfffffdff)
#define		BIT9OUTOD			((ulong32)0x00000200)

#define		BIT8OUTPP			((ulong32)0xfffffeff)
#define		BIT8OUTOD			((ulong32)0x00000100)

#define		BIT7OUTPP			((ulong32)0xffffff7f)
#define		BIT7OUTOD			((ulong32)0x00000080)

#define		BIT6OUTPP			((ulong32)0xffffffbf)
#define		BIT6OUTOD			((ulong32)0x00000040)

#define		BIT5OUTPP			((ulong32)0xffffffdf)
#define		BIT5OUTOD			((ulong32)0x00000020)

#define		BIT4OUTPP			((ulong32)0xffffffef)
#define		BIT4OUTOD			((ulong32)0x00000010)

#define		BIT3OUTPP			((ulong32)0xfffffff7)
#define		BIT3OUTOD			((ulong32)0x00000008)

#define		BIT2OUTPP			((ulong32)0xfffffffb)
#define		BIT2OUTOD			((ulong32)0x00000004)

#define		BIT1OUTPP			((ulong32)0xfffffffd)
#define		BIT1OUTOD			((ulong32)0x00000002)

#define		BIT0OUTPP			((ulong32)0xfffffffe)
#define		BIT0OUTOD			((ulong32)0x00000001)

#define		BIT15OFFIn			((ulong32)0xffff7fff)
#define		BIT15ONIn				((ulong32)0x00008000)

#define		BIT14OFFIn			((ulong32)0xffffbfff)
#define		BIT14ONIn				((ulong32)0x00004000)

#define		BIT13OFFIn			((ulong32)0xffffdfff) 
#define		BIT13ONIn				((ulong32)0x00002000) 

#define		BIT12OFFIn			((ulong32)0xffffefff) 
#define		BIT12ONIn				((ulong32)0x00001000) 

#define		BIT11OFFIn			((ulong32)0xfffff7ff)
#define		BIT11ONIn				((ulong32)0x00000800)

#define		BIT10OFFIn			((ulong32)0xfffffbff)
#define		BIT10ONIn				((ulong32)0x00000400)

#define		BIT9OFFIn				((ulong32)0xfffffdff) 
#define		BIT9ONIn				((ulong32)0x00000200) 

#define		BIT8OFFIn				((ulong32)0xfffffeff)
#define		BIT8ONIn				((ulong32)0x00000100)

#define		BIT7OFFIn				((ulong32)0xffffff7f)
#define		BIT7ONIn				((ulong32)0x00000080)

#define		BIT6OFFIn				((ulong32)0xffffffbf) 
#define		BIT6ONIn				((ulong32)0x00000040) 

#define		BIT5OFFIn				((ulong32)0xffffffdf) 
#define		BIT5ONIn				((ulong32)0x00000020) 

#define		BIT4OFFIn				((ulong32)0xffffffef)
#define		BIT4ONIn				((ulong32)0x00000010)

#define		BIT3OFFIn				((ulong32)0xfffffff7) 
#define		BIT3ONIn				((ulong32)0x00000008) 

#define		BIT2OFFIn				((ulong32)0xfffffffb)
#define		BIT2ONIn				((ulong32)0x00000004)

#define		BIT1OFFIn				((ulong32)0xfffffffd) 
#define		BIT1ONIn				((ulong32)0x00000002) 

#define		BIT0OFFIn				((ulong32)0xfffffffe)
#define		BIT0ONIn				((ulong32)0x00000001)

#define		BIT15PULLUP			((ulong32)0x00008000)
#define		BIT15NOPUPD			((ulong32)0xffff7fff)

#define		BIT14PULLUP			((ulong32)0x00004000)
#define		BIT14NOPUPD			((ulong32)0xffffbfff)

#define		BIT13PULLUP			((ulong32)0x00002000) 
#define		BIT13NOPUPD			((ulong32)0xffffdfff) 

#define		BIT12PULLUP			((ulong32)0x00001000) 
#define		BIT12NOPUPD			((ulong32)0xffffefff) 

#define		BIT11PULLUP			((ulong32)0x00000800)
#define		BIT11NOPUPD			((ulong32)0xfffff7ff)

#define		BIT10PULLUP			((ulong32)0x00000400)
#define		BIT10NOPUPD			((ulong32)0xfffffbff)

#define		BIT9PULLUP			((ulong32)0x00000200) 
#define		BIT9NOPUPD			((ulong32)0xfffffdff) 

#define		BIT8PULLUP			((ulong32)0x00000100)
#define		BIT8NOPUPD			((ulong32)0xfffffeff)

#define		BIT7PULLUP			((ulong32)0x00000080)
#define		BIT7NOPUPD			((ulong32)0xffffff7f)

#define		BIT6PULLUP			((ulong32)0x00000040) 
#define		BIT6NOPUPD			((ulong32)0xffffffbf) 

#define		BIT5PULLUP			((ulong32)0x00000020) 
#define		BIT5NOPUPD			((ulong32)0xffffffdf) 

#define		BIT4PULLUP			((ulong32)0x00000010)
#define		BIT4NOPUPD			((ulong32)0xffffffef)

#define		BIT3PULLUP			((ulong32)0x00000008) 
#define		BIT3NOPUPD			((ulong32)0xfffffff7) 

#define		BIT2PULLUP			((ulong32)0x00000004)
#define		BIT2NOPUPD			((ulong32)0xfffffffb)

#define		BIT1PULLUP			((ulong32)0x00000002) 
#define		BIT1NOPUPD			((ulong32)0xfffffffd) 

#define		BIT0PULLUP			((ulong32)0x00000001)
#define		BIT0NOPUPD			((ulong32)0xfffffffe)

#define		BIT0SET					((ulong32)0x00000001)
#define		BIT0RESET				((ulong32)0x00000001)
#define		BIT1SET					((ulong32)0x00000002)
#define		BIT1RESET				((ulong32)0x00000002)
#define		BIT2SET					((ulong32)0x00000004)
#define		BIT2RESET				((ulong32)0x00000004)
#define		BIT3SET					((ulong32)0x00000008)
#define		BIT3RESET				((ulong32)0x00000008)
#define		BIT4SET					((ulong32)0x00000010)
#define		BIT4RESET				((ulong32)0x00000010)
#define		BIT5SET					((ulong32)0x00000020)
#define		BIT5RESET				((ulong32)0x00000020)
#define		BIT6SET					((ulong32)0x00000040)
#define		BIT6RESET				((ulong32)0x00000040)
#define		BIT7SET					((ulong32)0x00000080)
#define		BIT7RESET				((ulong32)0x00000080)
#define		BIT8SET					((ulong32)0x00000100)
#define		BIT8RESET				((ulong32)0x00000100)
#define		BIT9SET					((ulong32)0x00000200)
#define		BIT9RESET				((ulong32)0x00000200)
#define		BIT10SET				((ulong32)0x00000400)
#define		BIT10RESET				((ulong32)0x00000400)
#define		BIT11SET				((ulong32)0x00000800)
#define		BIT11RESET				((ulong32)0x00000800)
#define		BIT12SET				((ulong32)0x00001000)
#define		BIT12RESET				((ulong32)0x00001000)
#define		BIT13SET				((ulong32)0x00002000)
#define		BIT13RESET				((ulong32)0x00002000)
#define		BIT14SET				((ulong32)0x00004000)
#define		BIT14RESET				((ulong32)0x00004000)
#define		BIT15SET				((ulong32)0x00008000)
#define		BIT15RESET				((ulong32)0x00008000)
#define		BIT2On				    ((ulong32)0x00000004)
#define		BIT2Off				    ((ulong32)0xFFFFFFFB)
///*****************************************************************************************///
///#if	( C_PcbVersion == C_Pcb2457 )///*-M表
///*蜂鸣器,2457	C-Z*///
#define		IO_BEEP						GPIOB				///*allocation in GPIO*///
#define		BEEP_SELECT				GPIO_Pin_10			///*select the pin:bit2*///
#define		BEEP_IN_MODE			BIT10INMODE			///*00:Input,reset state*///
#define		BEEP_OUT_MODE			BIT10OUTMODE			///*01:Output*///
#define		BEEP_OUTPUT_PP		BIT10OUTPP			///*0:Output Push-Pull,reset state*///
//#define		BEEP_SPEED_2MHZ		BIT5OUT2MHZ
//#define		BEEP_SPEED_INIT		BIT5OUTSPEEDINIT
#define		BEEPSET						BIT10SET
#define		BEEPRESET					BIT10RESET
#define		BEEP_NOPUPD				BIT10NOPUPD			///*no pull-up,no pull-down*///
///*辅助电源检测，2481远程*///
#define		IO_CHECKAUPOWER					GPIOB		///*allocation in GPIOx*///
#define		CHECKAUPOWER_SELECT			GPIO_Pin_10  ///*select the pin*///
#define		CHECKAUPOWER_ANALOG_MODE	BIT10ANOLOG
#define		CHECKAUPOWER_IN_MODE		BIT10INMODE  ///*input mode*///
#define		CHECKAUPOWER_IN_On			BIT10ONIn	///*input Open*///
#define		CHECKAUPOWER_IN_Off			BIT10OFFIn	///*input off*///
#define		CHECKAUPOWER_NOPUPD			BIT10NOPUPD  ///*no pull-up,no pull-down*///
#define		CHECKAUPOWER_PULLUP			BIT10PULLUP
//#define		CHECKAUPOWER_FilterDis	BIT4FilterDis
//#define		CHECKAUPOWER_FilterEn		BIT4FilterEn
//#define		CHECKAUPOWER_ANALOG_MODE	BIT8ANOLOG
#define		CHECKAUPOWER_SET				BIT10SET
///*载波通信口的定义,2457	C-Z*///
///*RX*///
#define		IO_MODULARR					GPIOF				///*allocation in GPIO*///
#define		IO_MODULARR_AF			BIT3AFMODE				///*alternate function register is AFRL/AFRH*///
#define		MODULARR_SELECT			GPIO_Pin_3			///*select the pin*///
//#define		MODULARR_AF_MODE		AF_Pin_4			///*port mode*///
#define		MODULARR_IN_MODE		BIT3INMODE			///*port mode*///
#define		MODULARR_OUT_MODE		BIT3OUTMODE			///*port mode*///
#define		MODULARR_OUTPUT_OD	BIT3OUTOD			
//#define		MODULARR_AF_UART		AFCFG2_Pin_4			///*AF7:use as usart1*///
//#define		MODULARR_AF_RESET		BIT2_10AFRESET
#define		MODULARR_NOPUPD			BIT3NOPUPD
#define		MODULARR_PULLUP			BIT3PULLUP
#define		MODULARRSET					BIT3SET
///*TX*///
#define		IO_MODULART					GPIOF				///*allocation in GPIO*///
#define		IO_MODULART_AF			BIT4AFMODE				///*alternate function register is AFRL/AFRH*///
#define		MODULART_SELECT			GPIO_Pin_4			///*select the pin*///
//#define		MODULART_AF_MODE		AF_Pin_4			///*port mode*///
#define		MODULART_IN_MODE		BIT4INMODE			///*port mode*///
#define		MODULART_OUT_MODE		BIT4OUTMODE			///*port mode*///
#define		MODULART_OUTPUT_OD	BIT4OUTOD	
//#define		MODULART_AF_UART		AFCFG2_Pin_5			///*AF7:use as usart1*///
//#define		MODULART_AF_RESET		BIT4_12AFRESET
#define		MODULART_OUTPUT_PP	BIT4OUTPP			///*Output Push-pull*///
#define		MODULARTSET					BIT4SET

#define		SFR_MODULAR							UART0
#define		Modular_IRQHandler			UART0_IRQHandler		///*中断服务程序*///
#define		Modular_IRQn						UART0_IRQn				///*中断号*///
#define		Modular_SouceClock_EN		(RCC_PERRCCCON3_UART0CKE_ON)
#define		Modular_SouceClock_DIS	(~RCC_PERRCCCON3_UART0CKE_ON)
#define		Modular_SouceClock_SFR	RCC->PERCLKCON3
///*card的相关定义*///
///*data i/o*///
#define		IO_CARDDATA						GPIOC				///*allocation in GPIO*///
#define		IO_CARDDATA_AF				BIT3AFMODE				///*alternate function register is AFRL/AFRH*///
#define		CARDDATA_SELECT				GPIO_Pin_3			///*select the pin*///
#define		CARDDATA_IN_MODE				BIT3INMODE			///*port mode*///
#define		CARDDATA_INOn					BIT3ONIn			
#define		CARDDATA_INOff					BIT3OFFIn			
#define		CARDDATA_OUT_MODE			BIT3OUTMODE			///*port mode*///
//#define		CARDDATA_AF_MODE			AF_Pin_2			///*port mode*///
//#define		CARDDATA_AF_UART			AFCFG2_Pin_2			///*AF7:use as usart*///
//#define		CARDDATA_AF_RESET			BIT1_9AFRESET
#define		CARDDATA_OUTPUT_OD		BIT3OUTOD			///*Output Open-Drain*///
#define		CARDDATA_NOPUPD				BIT3NOPUPD
#define		CARDDATASET						BIT3SET
#define		CARDDATARESET					BIT3RESET
//#define		CARDDATA_SPEED_INIT			BIT9OUTSPEEDINIT
//#define		CARDDATA_SPEED_50MHZ		BIT9OUT50MHZ
//#define		CARDDATA_NOPUPD				BIT9NOPUPD
///*卡电源*///
#define		IO_CARDPOWER					GPIOC		///*allocation in GPIO*///
#define		CARDPOWER_SELECT			GPIO_Pin_5	///*select the pin:bit8*///
#define		CARDPOWER_IN_MODE			BIT5INMODE	///*00:Input,reset state*///
#define		CARDPOWER_OUT_MODE		BIT5OUTMODE	///*01:Output*///
#define		CARDPOWER_OUTPUT_PP		BIT5OUTPP	///*Output Open-Drain*///
#define		CARDPOWER_NOPUPD			BIT5NOPUPD	///*no pull-up,no pull-down*///
//#define		CARDPOWER_SPEED_2MHZ	BIT1OUT2MHZ
//#define		CARDPOWER_SPEED_INIT	BIT1OUTSPEEDINIT
#define		CARDPOWERSET					BIT5SET
#define		CARDPOWERRESET				BIT5RESET
///*卡复位*///
#define		IO_CARDRESET					GPIOC		///*allocation in GPIO*///
#define		CARDRESET_SELECT			GPIO_Pin_4	///*select the pin:bit8*///
#define		CARDRESET_IN_MODE			BIT4INMODE	///*00:Input,reset state*///
#define		CARDRESET_OUT_MODE		BIT4OUTMODE	///*01:Output*///
#define		CARDRESET_OUTPUT_PP		BIT4OUTPP	///*Output Open-Drain*///
#define		CARDRESET_NOPUPD			BIT4NOPUPD	///*no pull-up,no pull-down*///
//#define		CARDRESET_SPEED_2MHZ	BIT3OUT2MHZ
//#define		CARDRESET_SPEED_INIT	BIT3OUTSPEEDINIT
#define		CARDRESETSET					BIT4SET
#define		CARDRESETRESET				BIT4RESET
///*第2路RS485的相关定义，2481远程费控、智能表*///
///*RX*///
#define		IO_SECOND485R					GPIOC				///*allocation in GPIO*///
#define		IO_SECOND485R_AF			BIT4AFMODE				///*alternate function register is AFRL/AFRH*///
#define		SECOND485R_SELECT			GPIO_Pin_4			///*select the pin*///
//#define		SECOND485R_AF_MODE		AF_Pin_4			///*port mode*///
#define		SECOND485R_IN_MODE		BIT4INMODE			///*port mode*///
#define		SECOND485R_OUT_MODE		BIT4OUTMODE			///*port mode*///
#define		SECOND485R_OUTPUT_OD	BIT4OUTOD			
//#define		SECOND485R_AF_UART		AFCFG2_Pin_4			///*AF7:use as usart1*///
//#define		SECOND485R_AF_RESET		BIT2_10AFRESET
#define		SECOND485R_NOPUPD			BIT4NOPUPD
#define		SECOND485R_PULLUP			BIT4PULLUP
#define		SECOND485RSET					BIT4SET
///*TX*///
#define		IO_SECOND485T					GPIOC				///*allocation in GPIO*///
#define		IO_SECOND485T_AF			BIT5AFMODE				///*alternate function register is AFRL/AFRH*///
#define		SECOND485T_SELECT			GPIO_Pin_5			///*select the pin*///
//#define		SECOND485T_AF_MODE		AF_Pin_4			///*port mode*///
#define		SECOND485T_IN_MODE		BIT5INMODE			///*port mode*///
#define		SECOND485T_OUT_MODE		BIT5OUTMODE	
#define		SECOND485T_OUTPUT_OD	BIT5OUTOD	
//#define		SECOND485T_AF_UART		AFCFG2_Pin_5			///*AF7:use as usart1*///
//#define		SECOND485T_AF_RESET		BIT4_12AFRESET
#define		SECOND485T_OUTPUT_PP	BIT5OUTPP			///*Output Push-pull*///
#define		SECOND485TSET					BIT5SET
///*第2路485接收/发送控制*///
#define		IO_SECOND485					GPIOC///*allocation in GPIO*///
#define		SECOND485_SELECT			GPIO_Pin_3			///*select the pin:bit2*///
#define		SECOND485_IN_MODE			BIT3INMODE			///*00:Input,reset state*///
#define		SECOND485_OUT_MODE		BIT3OUTMODE			///*01:Output*///
#define		SECOND485_OUTPUT_PP		BIT3OUTPP			///*Output push-pull*///
////#define		SECOND485_SPEED_2MHZ	BIT8OUT2MHZ
////#define		SECOND485_SPEED_INIT	BIT8OUTSPEEDINIT
#define		SECOND485SET					BIT3SET
#define		SECOND485RESET				BIT3RESET
#define		SECOND485_NOPUPD			BIT3NOPUPD

#define		SFR_SECOND485							UART5
#define		Second485_IRQHandler			UART5_IRQHandler		///*中断服务程序*///
#define		Second485_IRQn						UART5_IRQn				///*中断号*///
#define		Second485_SouceClock_EN		(RCC_PERRCCCON3_UART5CKE_ON)
#define		Second485_SouceClock_DIS	(~RCC_PERRCCCON3_UART5CKE_ON)
#define		Second485_SouceClock_SFR	RCC->PERCLKCON3
///*以上为2481远程智能表与2457本地-M表，部分IO冲突处理宏定义。在应用程序中，会对表型做特殊处理，达到hex统一。
///*****************************************************************************************///
///* EEPROM *///
///*select the IO:read the input value of the corresponding io bit*///
#define		IO_EESDA				GPIOB				///*allocation in GPIOA*///
#define		EESDA_SELECT		GPIO_Pin_7			///*select the pin*///
#define		EESDA_IN_MODE		BIT7INMODE	///*00:Input,reset state*///
#define		EESDA_INOn			BIT7ONIn	///*input Open*///
#define		EESDA_OUT_MODE	BIT7OUTMODE	///*01:Output*///
#define		EESDA_OUTPUT_OD	BIT7OUTOD	///*1:Output Open-Drain*///
#define		EESDA_NOPUPD		BIT7NOPUPD	///*00:no pull-up,no pull-down*///
//#define		EESDA_SPEED_2MHZ	BIT3OUT2MHZ
//#define		EESDA_SPEED_INIT	BIT3OUTSPEEDINIT
#define		EESDASET				BIT7SET
#define		EESDARESET			BIT7RESET

#define		IO_EESCL				GPIOB
#define		EESCL_SELECT		GPIO_Pin_8
#define		EESCL_IN_MODE		BIT8INMODE	///*00:Input,reset state*///
#define		EESCL_INOn		BIT8ONIn
#define		EESCL_OUT_MODE	BIT8OUTMODE	///*01:Output*///
#define		EESCL_OUTPUT_PP	BIT8OUTPP	///*0:Output Push-Pull,reset state*///
#define		EESCL_NOPUPD		BIT8NOPUPD	///*00:no pull-up,no pull-down*///
//#define		EESCL_SPEED_2MHZ	BIT2OUT2MHZ
//#define		EESCL_SPEED_INIT	BIT2OUTSPEEDINIT
#define		EESCLSET				BIT8SET
#define		EESCLRESET			BIT8RESET

#define		IO_EEWP					GPIOB
#define		EEWP_SELECT			GPIO_Pin_9
#define		EEWP_IN_MODE		BIT9INMODE	///*00:Input,reset state*///
#define		EEWP_INOn		BIT9ONIn
#define		EEWP_OUT_MODE		BIT9OUTMODE	///*01:Output*///
#define		EEWP_OUTPUT_PP	BIT9OUTPP	///*0:Output Push-Pull,reset state*///
#define		EEWP_NOPUPD			BIT9NOPUPD	///*00:no pull-up,no pull-down*///
//#define		EEWP_SPEED_2MHZ		BIT1OUT2MHZ
//#define		EEWP_SPEED_INIT		BIT1OUTSPEEDINIT
#define		EEWPSET					BIT9SET
#define		EEWPRESET				BIT9RESET

///* 铁电 *///
///*select the IO:read the input value of the corresponding io bit*///
#define		IO_FRAMSDA					GPIOB					///*allocation in GPIOA*///
#define		FRAMSDA_SELECT			GPIO_Pin_4				///*select the pin*///
#define		FRAMSDA_IN_MODE			BIT4INMODE	///*00:Input,reset state*///
#define		FRAMSDA_INOn				BIT4ONIn	///*input Open*///
#define		FRAMSDA_OUT_MODE		BIT4OUTMODE	///*01:Output*///
#define		FRAMSDA_OUTPUT_OD		BIT4OUTOD	///*1:Output Open-Drain*///
#define		FRAMSDA_OUTPUT_PP		BIT4OUTPP	///*1:Output Open-Drain*///
#define		FRAMSDA_NOPUPD			BIT4NOPUPD	///*00:no pull-up,no pull-down*///
//#define		FRAMSDA_SPEED_2MHZ	BIT0OUT2MHZ
//#define		FRAMSDA_SPEED_INIT	BIT0OUTSPEEDINIT
#define		FRAMSDASET					BIT4SET
#define		FRAMSDARESET				BIT4RESET

#define		IO_FRAMSCL					GPIOB
#define		FRAMSCL_SELECT			GPIO_Pin_5
#define		FRAMSCL_IN_MODE			BIT5INMODE	///*00:Input,reset state*///
#define		FRAMSCL_INOn			BIT5ONIn
#define		FRAMSCL_OUT_MODE		BIT5OUTMODE	///*01:Output*///
#define		FRAMSCL_OUTPUT_PP		BIT5OUTPP	///*0:Output Push-Pull,reset state*///
#define		FRAMSCL_NOPUPD			BIT5NOPUPD	///*00:no pull-up,no pull-down*///
//#define		FRAMSCL_SPEED_2MHZ	BIT1OUT2MHZ
//#define		FRAMSCL_SPEED_INIT	BIT1OUTSPEEDINIT
#define		FRAMSCLSET					BIT5SET
#define		FRAMSCLRESET				BIT5RESET

#define		IO_FRAMWP						GPIOB
#define		FRAMWP_SELECT				GPIO_Pin_6
#define		FRAMWP_IN_MODE			BIT6INMODE	///*00:Input,reset state*///
#define		FRAMWP_INOn			BIT6ONIn
#define		FRAMWP_OUT_MODE			BIT6OUTMODE	///*01:Output*///
#define		FRAMWP_OUTPUT_PP		BIT6OUTPP	///*0:Output Push-Pull,reset state*///
#define		FRAMWP_NOPUPD				BIT6NOPUPD	///*00:no pull-up,no pull-down*///
//#define		FRAMWP_SPEED_2MHZ		BIT2OUT2MHZ
//#define		FRAMWP_SPEED_INIT		BIT2OUTSPEEDINIT
#define		FRAMWPSET						BIT6SET
#define		FRAMWPRESET					BIT6RESET
///*****************************************************************************************///
///*****************************************************************************************///
///* LCD drive *///
///* IO LCD:first lcd driver,LCDX:second lcd driver*///
#define		IO_LCDSDA			GPIOA				///*allocation in GPIOC*///
#define		LCDSDA_SELECT			GPIO_Pin_14	///*select the sda:bit0*///
#define		LCDSDA_IN_MODE		BIT14INMODE	///*00:Input,reset state*///
#define		LCDSDA_INOn			BIT14ONIn	///*input Open*///
#define		LCDSDA_OUT_MODE		BIT14OUTMODE	///*01:Output*///
#define		LCDSDA_OUTPUT_PP	BIT14OUTPP	///*1:Output Open-Drain*///
#define		LCDSDA_OUTPUT_OD	BIT14OUTOD	///*1:Output Open-Drain*///
#define		LCDSDA_NOPUPD			BIT14NOPUPD	///*00:no pull-up,no pull-down*///
#define		LCDSDA_PULLUP			BIT14PULLUP	///*00:no pull-up,no pull-down*///
//#define		LCDSDA_SPEED_2MHZ	BIT15OUT2MHZ
//#define		LCDSDA_SPEED_INIT	BIT15OUTSPEEDINIT
#define		LCDSDASET					BIT14SET
#define		LCDSDARESET				BIT14RESET

#define		IO_LCDSCL					GPIOB
#define		LCDSCL_SELECT			GPIO_Pin_0	///*select the sda:bit5*///
#define		LCDSCL_IN_MODE		BIT0INMODE	///*00:Input,reset state*///
#define		LCDSCL_INOn				BIT0ONIn
#define		LCDSCL_OUT_MODE		BIT0OUTMODE	///*01:Output*///
#define		LCDSCL_OUTPUT_PP	BIT0OUTPP	///*0:Output Push-Pull,reset state*///
#define		LCDSCL_OUTPUT_OD	BIT0OUTOD
#define		LCDSCL_NOPUPD			BIT0NOPUPD	///*00:no pull-up,no pull-down*///
#define		LCDSCL_PULLUP			BIT0PULLUP	///*00:no pull-up,no pull-down*///
//#define		LCDSCL_SPEED_2MHZ	BIT15OUT2MHZ
//#define		LCDSCL_SPEED_INIT	BIT15OUTSPEEDINIT
#define		LCDSCLSET					BIT0SET
#define		LCDSCLRESET				BIT0RESET

//#define		IO_LCDA0					GPIOB				///*allocation in GPIOE*///
//#define		LCDA0_SELECT			GPIO_Pin_1			///*select the sda:bit8*///
//#define		LCDA0_IN_MODE			BIT1INMODE			///*00:Input,reset state*///
//#define		LCDA0_INOn				BIT1ONIn
//#define		LCDA0_OUT_MODE		BIT1OUTMODE		///*01:Output*///
//#define		LCDA0_OUTPUT_PP		BIT1OUTPP			///*0:Output Push-Pull,reset state*///
////#define		LCDA0_SPEED_2MHZ	BIT1OUT2MHZ
////#define		LCDA0_SPEED_INIT	BIT1OUTSPEEDINIT
//#define		LCDA0SET					BIT1SET
//#define		LCDA0RESET				BIT1RESET
//
//#define		IO_LCDCS					GPIOB
//#define		LCDCS_SELECT			GPIO_Pin_2	///*select the sda:bit7*///
//#define		LCDCS_IN_MODE			BIT2INMODE	///*00:Input,reset state*///
//#define		LCDCS_INOn				BIT2ONIn
//#define		LCDCS_OUT_MODE		BIT2OUTMODE	///*01:Output*///
//#define		LCDCS_OUTPUT_PP		BIT2OUTPP	///*0:Output Push-Pull,reset state*///
////#define		LCDCS_SPEED_2MHZ	BIT2OUT2MHZ
////#define		LCDCS_SPEED_INIT	BIT2OUTSPEEDINIT
//#define		LCDCSSET					BIT2SET
//#define		LCDCSRESET				BIT2RESET
//
//#define		IO_LCDRST					GPIOB
//#define		LCDRST_SELECT			GPIO_Pin_0	///*select the sda:bit8*///
//#define		LCDRST_IN_MODE		BIT0INMODE	///*00:Input,reset state*///
//#define		LCDRST_INOn			BIT0ONIn
//#define		LCDRST_OUT_MODE		BIT0OUTMODE	///*01:Output*///
//#define		LCDRST_OUTPUT_PP	BIT0OUTPP	///*0:Output Push-Pull,reset state*///
////#define		LCDRST_SPEED_2MHZ	BIT0OUT2MHZ
////#define		LCDRST_SPEED_INIT	BIT0OUTSPEEDINIT
//#define		LCDRSTSET					BIT0SET
//#define		LCDRSTRESET				BIT0RESET
//#define		LCDRST_NOPUPD			BIT0NOPUPD   ///*00:no pull-up,no pull-down*///
//#define		IO_LCDSDA					GPIOD					///*allocation in GPIOC*///
//#define		LCDSDA_SELECT			GPIO_Pin_4	///*select the sda:bit7*///
//#define		LCDSDA_IN_MODE		BIT4INMODE	///*00:Input,reset state*///
//#define		LCDSDA_OUT_MODE		BIT4OUTMODE	///*01:Output*///
//#define		LCDSDA_OUTPUT_OD	BIT4OUTOD	///*1:Output Open-Drain*///
//#define		LCDSDA_NOPUPD			BIT4NOPUPD	///*00:no pull-up,no pull-down*///
////#define		LCDSDA_SPEED_2MHZ	BIT12OUT2MHZ
////#define		LCDSDA_SPEED_INIT	BIT12OUTSPEEDINIT
//#define		LCDSDASET					BIT4SET
//#define		LCDSDARESET				BIT4RESET
//
//#define		IO_LCDSCL					GPIOD
//#define		LCDSCL_SELECT			GPIO_Pin_3	///*select the sda:bit6*///
//#define		LCDSCL_IN_MODE		BIT3INMODE	///*00:Input,reset state*///
//#define		LCDSCL_OUT_MODE		BIT3OUTMODE	///*01:Output*///
//#define		LCDSCL_OUTPUT_PP	BIT3OUTPP	///*0:Output Push-Pull,reset state*///
//#define		LCDSCL_NOPUPD			BIT3NOPUPD
////#define		LCDSCL_SPEED_2MHZ	BIT13OUT2MHZ
////#define		LCDSCL_SPEED_INIT	BIT13OUTSPEEDINIT
//#define		LCDSCLSET					BIT3SET
//#define		LCDSCLRESET				BIT3RESET
//
//#define		IO_LCDXSDA				GPIOD					///*allocation in GPIOE*///
//#define		LCDXSDA_SELECT		GPIO_Pin_12	///*select the sda:bit5*///
//#define		LCDXSDA_IN_MODE		BIT12INMODE	///*00:Input,reset state*///
//#define		LCDXSDA_OUT_MODE	BIT12OUTMODE	///*01:Output*///
//#define		LCDXSDA_OUTPUT_OD	BIT12OUTOD	///*1:Output Open-Drain*///
//#define		LCDXSDA_NOPUPD		BIT12NOPUPD	///*00:no pull-up,no pull-down*///
////#define		LCDXSDA_SPEED_2MHZ	BIT13OUT2MHZ
////#define		LCDXSDA_SPEED_INIT	BIT13OUTSPEEDINIT
//#define		LCDXSDASET				BIT12SET
//#define		LCDXSDARESET			BIT12RESET
//
//#define		IO_LCDXSCL				GPIOD
//#define		LCDXSCL_SELECT		GPIO_Pin_13	///*select the sda:bit4*///
//#define		LCDXSCL_IN_MODE		BIT13INMODE	///*00:Input,reset state*///
//#define		LCDXSCL_OUT_MODE	BIT13OUTMODE	///*01:Output*///
//#define		LCDXSCL_OUTPUT_PP	BIT13OUTPP	///*0:Output Push-Pull,reset state*///
//#define		LCDXSCL_NOPUPD	BIT13NOPUPD
//
////#define		LCDXSCL_SPEED_2MHZ	BIT12OUT2MHZ
////#define		LCDXSCL_SPEED_INIT	BIT12OUTSPEEDINIT
//#define		LCDXSCLSET				BIT13SET
//#define		LCDXSCLRESET			BIT13RESET
///*****************************************************************************************///
///*****************************************************************************************///
///* RTC drive *///
///* IO *///
//#define		IO_RTCSDA					GPIOB					///*allocation in GPIOA*///
//#define		RTCSDA_SELECT			GPIO_Pin_7	///*select the sda:bit6*///
//#define		RTCSDA_IN_MODE		BIT7INMODE	///*00:Input,reset state*///
//#define		RTCSDA_OUT_MODE		BIT7OUTMODE	///*01:Output*///
//#define		RTCSDA_OUTPUT_OD	BIT7OUTOD	///*1:Output Open-Drain*///
//#define		RTCSDA_NOPUPD			BIT7NOPUPD	///*00:no pull-up,no pull-down*///
////#define		RTCSDA_SPEED_2MHZ	BIT7OUT2MHZ
////#define		RTCSDA_SPEED_INIT	BIT7OUTSPEEDINIT
//#define		RTCSDASET					BIT7SET
//#define		RTCSDARESET				BIT7RESET
//
//#define		IO_RTCSCL					GPIOB
//#define		RTCSCL_SELECT			GPIO_Pin_6	///*select the scl:bit5*///
//#define		RTCSCL_IN_MODE		BIT6INMODE	///*00:Input,reset state*///
//#define		RTCSCL_OUT_MODE		BIT6OUTMODE	///*01:Output*///
//#define		RTCSCL_OUTPUT_PP	BIT6OUTPP	///*0:Output Push-Pull,reset state*///
////#define		RTCSCL_SPEED_2MHZ	BIT6OUT2MHZ
////#define		RTCSCL_SPEED_INIT	BIT6OUTSPEEDINIT
//#define		RTCSCLSET					BIT6SET
//#define		RTCSCLRESET				BIT6RESET
//#define		RTCSCL_NOPUPD			BIT6NOPUPD	///*00:no pull-up,no pull-down*///
///*****************************************************************************************///
///*****************************************************************************************///
///* Flash *///
///* IO *///
#define		IO_FLASHSDO					GPIOB			///*allocation in GPIOE,SDO/SDI都相对于主设备来讲的，即SDO是MCU的SDO*///
#define		FLASHSDO_SELECT			GPIO_Pin_15		///*select the sda:bit13*///
#define		FLASHSDO_IN_MODE		BIT15INMODE		///*00:Input,reset state*///
#define		FLASHSDO_INOn			BIT15ONIn
#define		FLASHSDO_OUT_MODE		BIT15OUTMODE	///*01:Output*///
#define		FLASHSDO_OUTPUT_PP	BIT15OUTPP		///*0:Output Push-Pull,reset state*///
#define		FLASHSDO_NOPUPD			BIT15NOPUPD		///*00:no pull-up,no pull-down*///
//#define		FLASHSDO_SPEED_2MHZ	BIT4OUT2MHZ
//#define		FLASHSDO_SPEED_INIT	BIT4OUTSPEEDINIT
#define		FLASHSDOSET					BIT15SET 
#define		FLASHSDORESET				BIT15RESET

#define		IO_FLASHSDI					GPIOB
#define		FLASHSDI_SELECT			GPIO_Pin_14		///*select the sda:bit9*///
#define		FLASHSDI_IN_MODE		BIT14INMODE		///*00:Input,reset state*///
#define		FLASHSDI_INOn			BIT14ONIn		
#define		FLASHSDI_OUT_MODE		BIT14OUTMODE
#define		FLASHSDI_NOPUPD			BIT14NOPUPD		///*00:no pull-up,no pull-down*///
#define		FLASHSDI_OUTPUT_PP	BIT14OUTPP
//#define		FLASHSDI_SPEED_2MHZ	BIT10OUT2MHZ
//#define		FLASHSDI_SPEED_INIT	BIT10OUTSPEEDINIT
#define		FLASHSDISET					BIT14SET
#define		FLASHSDIRESET				BIT14RESET

#define		IO_FLASHCS					GPIOB
#define		FLASHCS_SELECT			GPIO_Pin_12		///*select the sda:bit14*///
#define		FLASHCS_IN_MODE			BIT12INMODE		///*00:Input,reset state*///
#define		FLASHCS_INOn			BIT12ONIn	
#define		FLASHCS_OUT_MODE		BIT12OUTMODE	///*01:Output*///
#define		FLASHCS_NOPUPD			BIT12NOPUPD		///*00:no pull-up,no pull-down*///
#define		FLASHCS_OUTPUT_PP		BIT12OUTPP		///*0:Output Push-Pull,reset state*///
//#define		FLASHCS_SPEED_2MHZ	BIT3OUT2MHZ
//#define		FLASHCS_SPEED_INIT	BIT3OUTSPEEDINIT
#define		FLASHCSSET					BIT12SET
#define		FLASHCSRESET				BIT12RESET

#define		IO_FLASHSCK					GPIOB
#define		FLASHSCK_SELECT			GPIO_Pin_13		///*select the sda:bit12*///
#define		FLASHSCK_IN_MODE		BIT13INMODE		///*00:Input,reset state*///
#define		FLASHSCK_INOn			BIT13ONIn
#define		FLASHSCK_OUT_MODE		BIT13OUTMODE	///*01:Output*///
#define		FLASHSCK_OUTPUT_PP	BIT13OUTPP		///*0:Output Push-Pull,reset state*///
#define		FLASHSCK_NOPUPD			BIT13NOPUPD
//#define		FLASHSCK_SPEED_2MHZ	BIT0OUT2MHZ
//#define		FLASHSCK_SPEED_INIT	BIT0OUTSPEEDINIT
#define		FLASHSCKSET					BIT13SET
#define		FLASHSCKRESET				BIT13RESET
///*****************************************************************************************///
///*****************************************************************************************///
///*****************************************************************************************///
///* Energy Metering IC *///
///* IO *///
#define		IO_EMETERDIN					GPIOA				///*allocation in GPIOE*///
#define		EMETERDIN_SELECT			GPIO_Pin_3			///*select the sda:bit8*///
#define		EMETERDIN_IN_MODE			BIT3INMODE			///*00:Input,reset state*///
#define		EMETERDIN_INOn			BIT3ONIn
#define		EMETERDIN_OUT_MODE		BIT3OUTMODE		///*01:Output*///
#define		EMETERDIN_OUTPUT_PP		BIT3OUTPP			///*0:Output Push-Pull,reset state*///
//#define		EMETERDIN_SPEED_2MHZ	BIT11OUT2MHZ
//#define		EMETERDIN_SPEED_INIT	BIT11OUTSPEEDINIT
#define		EMETERDINSET					BIT3SET
#define		EMETERDINRESET				BIT3RESET

#define		IO_EMETERDOUT					GPIOA
#define		EMETERDOUT_SELECT			GPIO_Pin_2	///*select the sda:bit9*///
#define		EMETERDOUT_IN_MODE		BIT2INMODE	///*00:Input,reset state*///
#define		EMETERDOUT_INOn			BIT2ONIn
#define		EMETERDOUT_NOPUPD			BIT2NOPUPD	///*00:no pull-up,no pull-down*///
#define		EMETERDOUTSET					BIT2SET

#define		IO_EMETERCS						GPIOA
#define		EMETERCS_SELECT				GPIO_Pin_5	///*select the sda:bit11*///
#define		EMETERCS_IN_MODE			BIT5INMODE	///*00:Input,reset state*///
#define		EMETERCS_INOn				BIT5ONIn
#define		EMETERCS_OUT_MODE			BIT5OUTMODE	///*01:Output*///
#define		EMETERCS_OUTPUT_PP		BIT5OUTPP	///*0:Output Push-Pull,reset state*///
//#define		EMETERCS_SPEED_2MHZ		BIT3OUT2MHZ
//#define		EMETERCS_SPEED_INIT		BIT3OUTSPEEDINIT
#define		EMETERCSSET						BIT5SET
#define		EMETERCSRESET					BIT5RESET

#define		IO_EMETERSCK					GPIOA
#define		EMETERSCK_SELECT			GPIO_Pin_4	///*select the sda:bit12*///
#define		EMETERSCK_OUT_MODE		BIT4OUTMODE	///*01:Output*///
#define		EMETERSCK_IN_MODE			BIT4INMODE	///*01:Input*///
#define		EMETERSCK_INOn				BIT4ONIn
#define		EMETERSCK_OUTPUT_PP		BIT4OUTPP	///*0:Output Push-Pull,reset state*///
//#define		EMETERSCK_SPEED_2MHZ	BIT6OUT2MHZ
//#define		EMETERSCK_SPEED_INIT	BIT6OUTSPEEDINIT
#define		EMETERSCKSET					BIT4SET
#define		EMETERSCKRESET				BIT4RESET

#define		IO_EMETERRST					GPIOA
#define		EMETERRST_SELECT			GPIO_Pin_1	///*select the sda:bit8*///
#define		EMETERRST_IN_MODE			BIT1INMODE	///*00:Input,reset state*///
#define		EMETERRST_INOn				BIT1ONIn
#define		EMETERRST_OUT_MODE		BIT1OUTMODE	///*01:Output*///
#define		EMETERRST_OUTPUT_PP		BIT1OUTPP	///*0:Output Push-Pull,reset state*///
//#define		EMETERRST_SPEED_2MHZ	BIT0OUT2MHZ
//#define		EMETERRST_SPEED_INIT	BIT0OUTSPEEDINIT
#define		EMETERRSTSET					BIT1SET
#define		EMETERRSTRESET				BIT1RESET
#define		EMETERRST_NOPUPD			BIT1NOPUPD   ///*00:no pull-up,no pull-down*///

#define		IO_EMETERIRQ					GPIOA
//#define		IO_EMETERIRQ_AF				AF_Pin_5
//#define		IO_EMETERIRQ_AF2			AFCFG2_Pin_13
#define		EMETERIRQ_SELECT			GPIO_Pin_0	///*select the sda:bit6*///
#define		EMETERIRQ_ANALOG_MODE		BIT0ANOLOG
#define		EMETERIRQ_IN_MODE			BIT0INMODE	///*00:Input,reset state*///
#define		EMETERIRQ_INOn				BIT0ONIn	///*input Open*///
#define		EMETERIRQ_IN_Off			BIT0OFFIn	///*input off*///
#define		EMETERIRQ_NOPUPD			BIT0NOPUPD	///*00:no pull-up,no pull-down*///
#define		EMETERIRQ_PULLUP			BIT0PULLUP
#define		EMETERIRQSET					BIT0SET

//#define		EMETERIRQ_ANALOG_MODE	BIT13ANOLOG
///*****************************************************************************************///
///*****************************************************************************************///
///*第1路RS485的相关定义*///
///*RX*///
#define		IO_FIRST485R				GPIOE				///*allocation in GPIO*///
#define		IO_FIRST485R_AF			BIT3AFMODE				///*alternate function register is AFRL/AFRH*///
#define		FIRST485R_SELECT		GPIO_Pin_3			///*select the pin*///
//#define		FIRST485R_AF_MODE		AF_Pin_1			///*port mode*///
#define		FIRST485R_IN_MODE		BIT3INMODE			///*port mode*///
//#define		FIRST485R_AF_UART		AFCFG1_Pin_1			///*AF7:use as usart1*///
//#define		FIRST485R_AF_RESET	BIT3_11AFRESET
#define		FIRST485R_NOPUPD		BIT3NOPUPD
///*TX*///
#define		IO_FIRST485T				GPIOE				///*allocation in GPIO*///
#define		IO_FIRST485T_AF			BIT4AFMODE				///*alternate function register is AFRL/AFRH*///
#define		FIRST485T_SELECT		GPIO_Pin_4			///*select the pin*///
//#define		FIRST485T_AF_MODE		AF_Pin_0			///*port mode*///
#define		FIRST485T_IN_MODE		BIT4INMODE			///*port mode*///
//#define		FIRST485T_AF_UART		AFCFG1_Pin_0			///*AF7:use as usart1*///
//#define		FIRST485T_AF_RESET	BIT2_10AFRESET
#define		FIRST485T_OUTPUT_PP	BIT4OUTPP			///*Output Push-pull*///
///*第1路485接收/发送控制*///
#define		IO_FIRST485					GPIOE				///*allocation in GPIO*///
#define		FIRST485_SELECT			GPIO_Pin_5			///*select the pin*///
#define		FIRST485_IN_MODE		BIT5INMODE			///*00:Input,reset state*///
#define		FIRST485_OUT_MODE		BIT5OUTMODE		///*01:Output*///
#define		FIRST485_OUTPUT_PP	BIT5OUTPP			///*Output Push-Pull*///
//#define		FIRST485_SPEED_2MHZ	BIT15OUT2MHZ
//#define		FIRST485_SPEED_INIT	BIT15OUTSPEEDINIT
#define		FIRST485SET					BIT5SET
#define		FIRST485RESET				BIT5RESET
#define		FIRST485_NOPUPD			BIT5NOPUPD

#define		SFR_FIRST485					UART1
#define		First485_IRQHandler		UART1_IRQHandler		///*中断服务程序*///
#define		First485_IRQn					UART1_IRQn				///*中断号*///
#define		First485_SouceClock_EN	(RCC_PERRCCCON3_UART1CKE_ON)
#define		First485_SouceClock_DIS	(~RCC_PERRCCCON3_UART1CKE_ON)
#define		First485_SouceClock_SFR	RCC->PERCLKCON3

#define		ComUart_SouceClock_EN	(RCC_PERRCCCON3_UARTCCKE_ON)
#define		ComUart_SouceClock_DIS	(~RCC_PERRCCCON3_UARTCCKE_ON)
#define		ComUart_SouceClock_SFR	RCC->PERCLKCON3
///*****************************************************************************************///
/////*第2路RS485的相关定义*///
/////*RX*///
//#define		IO_SECOND485R					GPIOF				///*allocation in GPIO*///
//#define		IO_SECOND485R_AF			BIT3AFMODE				///*alternate function register is AFRL/AFRH*///
//#define		SECOND485R_SELECT			GPIO_Pin_3			///*select the pin*///
////#define		SECOND485R_AF_MODE		AF_Pin_4			///*port mode*///
//#define		SECOND485R_IN_MODE		BIT3INMODE			///*port mode*///
////#define		SECOND485R_AF_UART		AFCFG2_Pin_4			///*AF7:use as usart1*///
////#define		SECOND485R_AF_RESET		BIT2_10AFRESET
//#define		SECOND485R_NOPUPD			BIT3NOPUPD
//#define		SECOND485R_PULLUP			BIT3PULLUP
/////*TX*///
//#define		IO_SECOND485T					GPIOF				///*allocation in GPIO*///
//#define		IO_SECOND485T_AF			BIT4AFMODE				///*alternate function register is AFRL/AFRH*///
//#define		SECOND485T_SELECT			GPIO_Pin_4			///*select the pin*///
////#define		SECOND485T_AF_MODE		AF_Pin_4			///*port mode*///
//#define		SECOND485T_IN_MODE		BIT4INMODE			///*port mode*///
////#define		SECOND485T_AF_UART		AFCFG2_Pin_5			///*AF7:use as usart1*///
////#define		SECOND485T_AF_RESET		BIT4_12AFRESET
//#define		SECOND485T_OUTPUT_PP	BIT4OUTPP			///*Output Push-pull*///
//
/////*第2路485接收/发送控制*///
//#define		IO_SECOND485					GPIOC///*allocation in GPIO*///
//#define		SECOND485_SELECT			GPIO_Pin_15			///*select the pin:bit2*///
//#define		SECOND485_IN_MODE			BIT15INMODE			///*00:Input,reset state*///
//#define		SECOND485_OUT_MODE		BIT15OUTMODE			///*01:Output*///
//#define		SECOND485_OUTPUT_PP		BIT15OUTPP			///*Output push-pull*///
//////#define		SECOND485_SPEED_2MHZ	BIT8OUT2MHZ
//////#define		SECOND485_SPEED_INIT	BIT8OUTSPEEDINIT
//#define		SECOND485SET					BIT15SET
//#define		SECOND485RESET				BIT15RESET
//#define		SECOND485_NOPUPD			BIT15NOPUPD
//
//#define		SFR_SECOND485							UART0
//#define		Second485_IRQHandler			UART0_IRQHandler		///*中断服务程序*///
//#define		Second485_IRQn						UART0_IRQn				///*中断号*///
//#define		Second485_SouceClock_EN		(RCC_PERRCCCON3_UART0CKE_ON)
//#define		Second485_SouceClock_DIS	(~RCC_PERRCCCON3_UART0CKE_ON)
//#define		Second485_SouceClock_SFR	RCC->PERCLKCON3
///*****************************************************************************************///
///*ESAM的相关定义*///
///*data MOSI*///
#define		IO_ESAMMOSI					GPIOF				///*allocation in GPIO*///
#define		IO_ESAMMOSI_AF			BIT12AFMODE				///*alternate function register is AFRL/AFRH*///
#define		ESAMMOSI_SELECT			GPIO_Pin_12			///*select the pin*///
#define		ESAMMOSI_IN_MODE		BIT12INMODE			///*port mode*///
#define		ESAMMOSI_INOn			BIT12ONIn			///*port mode*///
#define		ESAMMOSI_INOff			BIT12OFFIn		///*port mode*///
#define		ESAMMOSI_OUT_MODE		BIT12OUTMODE			///*port mode*///
//#define		ESAMMOSI_AF_MODE		AF_Pin_3			///*port mode*///
//#define		ESAMMOSI_AF_SPI			AFCFG2_Pin_3			///*AF7:use as spi*///
//#define		ESAMMOSI_AF_RESET		BIT4_12AFRESET
#define		ESAMMOSI_OUTPUT_PP	BIT12OUTPP			///*Output Push-Pull*///
#define		ESAMMOSISET					BIT12SET
#define		ESAMMOSIRESET				BIT12RESET
//#define		ESAMMOSI_SPEED_INIT		BIT4OUTSPEEDINIT
//#define		ESAMMOSI_SPEED_2MHZ		BIT4OUT2MHZ
//#define		ESAMMOSI_SPEED_50MHZ	BIT4OUT50MHZ
#define		ESAMMOSI_NOPUPD			BIT12NOPUPD

///*data MISO*///
#define		IO_ESAMMISO					GPIOF				///*allocation in GPIO*///
#define		IO_ESAMMISO_AF			BIT13AFMODE				///*alternate function register is AFRL/AFRH*///
#define		ESAMMISO_SELECT			GPIO_Pin_13			///*select the pin*///
#define		ESAMMISO_IN_MODE			BIT13INMODE			///*port mode*///
#define		ESAMMISO_INOn				BIT13ONIn			///*port mode*///
#define		ESAMMISO_INOff				BIT13OFFIn			///*port mode*///
#define		ESAMMISO_OUT_MODE		BIT13OUTMODE			///*port mode*///
//#define		ESAMMISO_AF_MODE		AF_Pin_2			///*port mode*///
//#define		ESAMMISO_AF_SPI			AFCFG2_Pin_2			///*AF7:use as spi*///
//#define		ESAMMISO_AF_RESET		BIT3_11AFRESET
#define		ESAMMISO_OUTPUT_PP	BIT13OUTPP			///*Output Push-Pull*///
#define		ESAMMISOSET					BIT13SET
#define		ESAMMISORESET				BIT13RESET
//#define		ESAMMISO_SPEED_INIT		BIT3OUTSPEEDINIT
//#define		ESAMMISO_SPEED_2MHZ		BIT3OUT2MHZ
//#define		ESAMMISO_SPEED_50MHZ	BIT3OUT50MHZ
#define		ESAMMISO_NOPUPD			BIT13NOPUPD
#define		ESAMMISO_PULLUP			BIT13PULLUP

///*esam SCK*///
#define		IO_ESAMSCK					GPIOF			///*allocation in GPIO*///
#define		IO_ESAMSCK_AF				BIT14AFMODE				///*alternate function register is AFRL/AFRH*///
#define		ESAMSCK_SELECT			GPIO_Pin_14			///*select the pin*///
#define		ESAMSCK_IN_MODE			BIT14INMODE			///*port mode*///
#define		ESAMSCK_INOff				BIT14OFFIn	
#define		ESAMSCK_OUT_MODE		BIT14OUTMODE			///*port mode*///
////#define		ESAMSCK_AF_MODE			AF_Pin_1			///*port mode*///
#define		ESAMSCK_OUTPUT_PP		BIT14OUTPP			///*Output Push-Pull*///
//#define		ESAMSCK_AF_SPI			AFCFG2_Pin_1			///*AF7:use as spi*///
//#define		ESAMSCK_AF_RESET		BIT1_9AFRESET
#define		ESAMSCKRESET				BIT14RESET
//#define		ESAMSCK_SPEED_INIT		BIT1OUTSPEEDINIT
//#define		ESAMSCK_SPEED_2MHZ		BIT1OUT2MHZ
//#define		ESAMSCK_SPEED_50MHZ		BIT1OUT50MHZ
#define		ESAMSCK_NOPUPD			BIT14NOPUPD
///*esam power*///
#define		IO_ESAMPOWER					GPIOE				///*allocation in GPIO*///
#define		ESAMPOWER_SELECT			GPIO_Pin_8			///*select the pin:bit2*///
#define		ESAMPOWER_IN_MODE			BIT8INMODE			///*00:Input,reset state*///
#define		ESAMPOWER_OUT_MODE		BIT8OUTMODE			///*01:Output*///
#define		ESAMPOWER_ANOLOG		BIT8ANOLOG			///*01:Output*///
#define		ESAMPOWER_OUTPUT_PP		BIT8OUTPP			///*0:Output Push-Pull,reset state*///
#define		ESAMPOWER_OUTPUT_OD		BIT8OUTOD			///*0:Output Push-Pull,reset state*///
//#define		ESAMPOWER_SPEED_2MHZ	BIT9OUT2MHZ
//#define		ESAMPOWER_SPEED_INIT	BIT9OUTSPEEDINIT
#define		ESAMPOWERSET					BIT8SET
#define		ESAMPOWERRESET				BIT8RESET
#define		ESAMPOWER_NOPUPD			BIT8NOPUPD
///*esam CS*///
#define		IO_ESAMCS						GPIOF				///*allocation in GPIO*///
#define		ESAMCS_SELECT				GPIO_Pin_15			///*select the pin:bit2*///
#define		ESAMCS_IN_MODE			BIT15INMODE			///*00:Input,CS state*///
#define		ESAMCS_OUT_MODE			BIT15OUTMODE			///*01:Output*///
#define		ESAMCS_OUTPUT_PP		BIT15OUTPP			///*0:Output Push-Pull,CS state*///
//#define		ESAMCS_SPEED_2MHZ		BIT0OUT2MHZ
//#define		ESAMCS_SPEED_INIT		BIT0OUTSPEEDINIT
#define		ESAMCSSET						BIT15SET
#define		ESAMCSRESET					BIT15RESET
#define		ESAMCS_NOPUPD				BIT15NOPUPD

#define		SFR_ESAMCOM					HSPI
#define		Esam_IRQHandler		HSPI_IRQHandler			///*中断服务程序*///
#define		Esam_IRQn		HSPI_IRQn				///*中断号*///
#define		EsamSouceClock_EN	((uint32_t)0x00000004)
#define		EsamSouceClock_DIS	(~((uint32_t)0x00000004))
#define		Esam_SouceClock_SFR	RCC->PERCLKCON3
                                        
///*****************************************************************************************///
///*红外的相关定义*///
///*RX*///
#define		IO_INFRARX				GPIOD				///*allocation in GPIO*///
#define		IO_INFRARX_AF			BIT9AFMODE				///*alternate function register is AFRL/AFRH*///
#define		INFRARX_SELECT		GPIO_Pin_9			///*select the pin*///
//#define		INFRARX_AF_MODE		AF_Pin_4			///*port mode*///
#define		INFRARX_IN_MODE		BIT9INMODE			///*port mode*///
#define		INFRARX_OUT_MODE	BIT9OUTMODE			///*port mode*///
#define		INFRARX_OUTPUT_OD	BIT9OUTOD			///*Output Push-Pull*///
//#define		INFRARX_AF_UART		AFCFG1_Pin_4			///*AF7:use as usart*///
//#define		INFRARX_AF_RESE 	BIT1_9AFRESET
#define		INFRARX_NOPUPD		BIT9NOPUPD
#define		INFRARX_SET				BIT9SET
//#define		InfraWakeup_IRQHandler			EXTI9_5_IRQHandler	///*中断服务程序*///
///*如果该口线不在9~5之间，中断服务程序要重写*///
//#define		InfraWakeup_IRQn					EXTI9_5_IRQn		///*中断向量地址*///
//#define		InfraWakeup_NoMask				0x00000200			///*中断不屏蔽*///
//#define		InfraWakeup_Rising				0x00000200			///*上升沿*///
//#define		InfraWakeup_Falling				0x00000200			///*下降沿*///
//#define		InfraWakeup_Trigger				0x00000200			///*触发标志*///
//#define		InfraWakeup_ConfigRegister		EXTICR[2]			///*外部触发中断口线选择寄存器*///
//#define		InfraWakeup_Configration_Select	SYSCFG_EXTICR3_EXTI9_PD

///*TX*///
#define		IO_INFRATX				GPIOD				///*allocation in GPIO*///
#define		IO_INFRATX_AF			BIT10AFMODE				///*alternate function register is AFRL/AFRH*///
#define		INFRATX_SELECT		GPIO_Pin_10			///*select the pin*///
//#define		INFRATX_AF_MODE		AF_Pin_5			///*port mode*///
#define		INFRATX_IN_MODE		BIT10INMODE			///*port mode*///
//#define		INFRATX_AF_UART		AFCFG1_Pin_5			///*AF7:use as usart*///
//#define		INFRATX_AF_RESET	BIT0_8AFRESET
#define		INFRATX_OUTPUT_PP	BIT10OUTPP			///*Output Push-Pull*///
///*红外发送38KHz调制信号*///
//#define		IO_TXDI38K					GPIOB			///*allocation in GPIO*///
//#define		IO_TXDI38K_AF				AFRH			///*alternate function register is AFRH*///
//#define		TXDI38K_SELECT			GPIO_Pin_15		///*select the pin:bit8*///
//#define		TXDI38K_IN_MODE			BIT15INMODE		///*00:Input,reset state*///
//#define		TXDI38K_AF_MODE			BIT15AFMODE		///*AF mode*///
//#define		TXDI38K_OUTPUT_PP		BIT15OUTPP		///*Output Push-Pull*///
//#define		TXDI38K_SPEED_2MHZ	BIT15OUT2MHZ
//#define		TXDI38K_SPEED_INIT	BIT15OUTSPEEDINIT
//#define		TXDI38KSET					BIT15SET
//#define		TXDI38KRESET				BIT15RESET
//#define		TXDI38K_AF3					BIT7_15AF3
//#define		TXDI38K_AF_RESET		BIT7_15AFRESET

#define		SFR_INFRA							UART4
#define		Infra_IRQHandler			UART4_IRQHandler		///*中断服务程序*///
#define		Infra_IRQn						UART4_IRQn				///*中断号*///
#define		Infra_SouceClock_EN		(RCC_PERRCCCON3_UART4CKE_ON)
#define		Infra_SouceClock_DIS	(~RCC_PERRCCCON3_UART4CKE_ON)
#define		Infra_SouceClock_SFR	RCC->PERCLKCON3

///*****************************************************************************************///
/////*card的相关定义*///
/////*data i/o*///
//#define		IO_CARDDATA						GPIOC				///*allocation in GPIO*///
//#define		IO_CARDDATA_AF				BIT3AFMODE				///*alternate function register is AFRL/AFRH*///
//#define		CARDDATA_SELECT				GPIO_Pin_3			///*select the pin*///
//#define		CARDDATA_IN_MODE				BIT3INMODE			///*port mode*///
//#define		CARDDATA_INOn					BIT3ONIn			
//#define		CARDDATA_INOff					BIT3OFFIn			
//#define		CARDDATA_OUT_MODE			BIT3OUTMODE			///*port mode*///
////#define		CARDDATA_AF_MODE			AF_Pin_2			///*port mode*///
////#define		CARDDATA_AF_UART			AFCFG2_Pin_2			///*AF7:use as usart*///
////#define		CARDDATA_AF_RESET			BIT1_9AFRESET
//#define		CARDDATA_OUTPUT_OD		BIT3OUTOD			///*Output Open-Drain*///
//#define		CARDDATA_NOPUPD				BIT3NOPUPD
//#define		CARDDATASET						BIT3SET
//#define		CARDDATARESET					BIT3RESET
////#define		CARDDATA_SPEED_INIT			BIT9OUTSPEEDINIT
////#define		CARDDATA_SPEED_50MHZ		BIT9OUT50MHZ
////#define		CARDDATA_NOPUPD				BIT9NOPUPD
/////*卡电源*///
//#define		IO_CARDPOWER					GPIOC		///*allocation in GPIO*///
//#define		CARDPOWER_SELECT			GPIO_Pin_5	///*select the pin:bit8*///
//#define		CARDPOWER_IN_MODE			BIT5INMODE	///*00:Input,reset state*///
//#define		CARDPOWER_OUT_MODE		BIT5OUTMODE	///*01:Output*///
//#define		CARDPOWER_OUTPUT_PP		BIT5OUTPP	///*Output Open-Drain*///
//#define		CARDPOWER_NOPUPD			BIT5NOPUPD	///*no pull-up,no pull-down*///
////#define		CARDPOWER_SPEED_2MHZ	BIT1OUT2MHZ
////#define		CARDPOWER_SPEED_INIT	BIT1OUTSPEEDINIT
//#define		CARDPOWERSET					BIT5SET
//#define		CARDPOWERRESET				BIT5RESET

///*卡时钟允许*///
#define		IO_CARDSCK						GPIOC		///*allocation in GPIO*///      
#define		IO_CARDSCK_AF					BIT2AFMODE				///*alternate function register is AFRL/AFRH*/// 
#define		CARDSCK_SELECT				GPIO_Pin_2	///*select the pin:bit8*///
#define		CARDSCK_IN_MODE				BIT2INMODE	///*00:Input,reset state*///
#define		CARDSCK_OUT_MODE			BIT2OUTMODE	///*01:Output*///
#define		CARDSCK_OUTPUT_PP			BIT2OUTPP	///*Output Open-Drain*///
#define		CARDSCK_NOPUPD				BIT2NOPUPD	///*no pull-up,no pull-down*///
//#define		CARDSCK_SPEED_2MHZ		BIT2OUT2MHZ
//#define		CARDSCK_SPEED_INIT		BIT2OUTSPEEDINIT
#define		CARDSCKSET						BIT2SET
#define		CARDSCKRESET					BIT2RESET
/////*卡复位*///
//#define		IO_CARDRESET					GPIOC		///*allocation in GPIO*///
//#define		CARDRESET_SELECT			GPIO_Pin_4	///*select the pin:bit8*///
//#define		CARDRESET_IN_MODE			BIT4INMODE	///*00:Input,reset state*///
//#define		CARDRESET_OUT_MODE		BIT4OUTMODE	///*01:Output*///
//#define		CARDRESET_OUTPUT_PP		BIT4OUTPP	///*Output Open-Drain*///
//#define		CARDRESET_NOPUPD			BIT4NOPUPD	///*no pull-up,no pull-down*///
////#define		CARDRESET_SPEED_2MHZ	BIT3OUT2MHZ
////#define		CARDRESET_SPEED_INIT	BIT3OUTSPEEDINIT
//#define		CARDRESETSET					BIT4SET
//#define		CARDRESETRESET				BIT4RESET

#define		SFR_CARDCOM						U78161
#define		Card_IRQHandler				U78161_IRQHandler		///*中断服务程序*///
#define		Card_IRQn							U78161_IRQn				///*中断号，7816_0同UART4*///
#define		CardSouceClock_EN			(RCC_PERRCCCON3_U7816CKE1_ON)
#define		CardSouceClock_DIS		(~RCC_PERRCCCON3_U7816CKE1_ON)
#define		Card_SouceClock_SFR		RCC->PERCLKCON3
///*****************************************************************************************///
///*3.6V电池电压检测*///
#define		IO_RTCBATT					GPIOB
#define		IO_RTCBATT_AF				BIT3ANOLOG
#define		RTCBATT_SELECT			GPIO_Pin_3	/*select the pin*///
#define		RTCBATT_ANALOG_MODE	BIT3ANOLOG	/*analog mode*///
#define		RTCBATT_IN_MODE			BIT3INMODE	/*input mode*///
#define		RTCBATT_NOPUPD			BIT3NOPUPD
//#define		RTCBATT_AF0				BIT3_11AF0
//#define		RTCBATT_AF_RESET		BIT3_11AFRESET
//#define		RTCBATT_Channel			ADCChannel13

///*6V电池电压检测*///
#define		IO_WAKEBATT						GPIOC
#define		IO_WAKEBATT_AF				BIT13ANOLOG
#define		WAKEBATT_SELECT				GPIO_Pin_13	///*select the pin*///
#define		WAKEBATT_ANALOG_MODE	BIT13ANOLOG	///*analog mode*///
#define		WAKEBATT_IN_MODE			BIT13INMODE	///*input mode*///
#define		WAKEBATT_IN_On			BIT13ONIn	///*input mode*///
#define		WAKEBATT_NOPUPD				BIT13NOPUPD
//#define		WAKEBATT_AF0					AFCFG2_Pin_12
//#define		WAKEBATT_SET					BIT13SET
//#define		WAKEBATT_AF_RESET			BIT1_9AFRESET
//#define		WAKEBATT_Channel			ADCChannel9
///*CAP电压检测*///
#define		IO_CAP					      GPIOB
#define		IO_CAP_AF				      BIT2ANOLOG
#define		CAP_SELECT				    GPIO_Pin_2	///*select the pin*///
#define		CAP_ANALOG_MODE	      BIT2ANOLOG	///*analog mode*///
#define		CAP_IN_MODE			      BIT2INMODE	///*input mode*///
#define		CAP_IN_On			        BIT2ONIn	///*input mode*///
#define		CAP_NOPUPD				    BIT2NOPUPD
///*****************************************************************************************///
///*input io*///
///*上翻键*///
#define		IO_KEYUP							GPIOC		///*allocation in GPIOx*///
#define		KEYUP_SELECT					GPIO_Pin_6	///*select the pin*///
#define		KEYUP_ANALOG_MODE			BIT6ANOLOG
#define		KEYUP_IN_MODE					BIT6INMODE	///*input mode*///
#define		KEYUP_IN_On						BIT6ONIn	///*input Open*///
#define		KEYUP_IN_Off					BIT6OFFIn	///*input off*///
#define		KEYUP_NOPUPD					BIT6NOPUPD	///*no pull-up,no pull-down*///
#define		KEYUP_PULLUP					BIT6PULLUP	///*pull-up*///
//#define		KEYUP_FilterDis				BIT5FilterDis
//#define		KEYUP_FilterEn				BIT5FilterEn
//#define		KEYUP_ANALOG_MODE			BIT11ANOLOG
//#define		KeyUp_SouceClock_EN		((ulong32)0x00000004)
//#define		KeyUp_SouceClock_DIS	((ulong32)0xfffffffb)
//#define		KeyUp_SouceClock_SFR	RCC->AHBENR
#define		KEYUPSET							BIT6SET
///*下翻键*///
#define		IO_KEYDOWN						GPIOC		///*allocation in GPIOx*///
#define		KEYDOWN_SELECT				GPIO_Pin_7  ///*select the pin*///
#define		KEYDOWN_ANALOG_MODE		BIT7ANOLOG
#define		KEYDOWN_IN_MODE				BIT7INMODE  ///*input mode*///
#define		KEYDOWN_IN_On					BIT7ONIn	///*input Open*///
#define		KEYDOWN_IN_Off				BIT7OFFIn	///*input off*///
#define		KEYDOWN_NOPUPD				BIT7NOPUPD  ///*no pull-up,no pull-down*///
#define		KEYDOWN_PULLUP				BIT7PULLUP  ///*pull-up*///
#define		KEYDOWNSET						BIT7SET
//#define		KEYDOWN_FilterDis			BIT6FilterDis
//#define		KEYDOWN_FilterEn			BIT6FilterEn
//#define		KEYDOWN_ANALOG_MODE		BIT10ANOLOG
//#define		KeyDown_SouceClock_EN	((ulong32)0x00000004)
//#define		KeyDown_SouceClock_DIS	((ulong32)0xfffffffb)
//#define		KeyDown_SouceClock_SFR	RCC->AHBENR
///*按键上拉电阻，上电推挽输出高，停电开漏输出高*///
#define		IO_KEYPU					GPIOC		  ///*allocation in GPIOx*///
#define		KEYPU_SELECT				GPIO_Pin_15	  ///*select the pin*///
#define		KEYPU_OUT_MODE		        BIT15OUTMODE  ///*01:Output*///
#define		KEYPU_IN_MODE		        BIT15INMODE   ///*01:Input*///
#define		KEYPU_OUTPUT_PP		        BIT15OUTPP	  ///*0:Output Push-Pull,reset state*///
#define		KEYPU_OUTPUT_OD			    BIT15OUTOD	  ///*0:Output Push-Pull,reset state*///
#define		KEYPUSET					BIT15SET

/*ZB_PWR_CTL*/
#define		IO_MODULE_PWCTL		        GPIOA			///*allocation in GPIOx*///
#define		MODULE_PWCTL_SELECT		    GPIO_Pin_15		///*select the pin*///
#define		MODULE_PWCTL_OUT_MODE		BIT15OUTMODE  ///*01:Output*///
#define		MODULE_PWCTL_IN_MODE	    BIT15INMODE		///*input mode*///
#define		MODULE_PWCTL_PP		        BIT15OUTPP	  ///*0:Output Push-Pull,reset state*///
#define		MODULE_PWCTL_OD			    BIT15OUTOD	  ///*0:Output Push-Pull,reset state*///
#define		MODULE_PWCTLPUSET			BIT15SET

///*编程键*///
//#define		IO_KEYPRG				GPIOB		///*allocation in GPIOx*///
//#define		KEYPRG_SELECT			GPIO_Pin_7 	///*select the pin*///
//#define		KEYPRG_IN_MODE			BIT7INMODE 	///*input mode*///
//#define		KEYPRG_NOPUPD			BIT7NOPUPD 	///*no pull-up,no pull-down*///
//#define		KEYPRG_PULLUP			BIT7PULLUP 	///*pull-up*///
//#define		KEYPRG_ANALOG_MODE		BIT7ANOLOG
///*开表盖*///
#define		IO_KEYOPENCOVER							GPIOA		///*allocation in GPIOx*///
#define		KEYOPENCOVER_SELECT					GPIO_Pin_6  ///*select the pin*///
#define		KEYOPENCOVER_ANALOG_MODE		BIT6ANOLOG
//#define		KEYOPENCOVER_SELECT_AF	AF_Pin_6  ///*select the pin*///
//#define		KEYOPENCOVER_SELECT_AF2	AFCFG2_Pin_6
#define		KEYOPENCOVER_IN_MODE				BIT6INMODE  ///*input mode*///
#define		KEYOPENCOVER_IN_On					BIT6ONIn	///*input Open*///
#define		KEYOPENCOVER_IN_Off					BIT6OFFIn	///*input off*///
#define		KEYOPENCOVER_OUT_MODE				BIT6OUTMODE  ///*input mode*///
#define		KEYOPENCOVER_OUTPUT_OD			BIT6OUTOD
#define		KEYOPENCOVER_NOPUPD					BIT6NOPUPD  ///*no pull-up,no pull-down*///
#define		KEYOPENCOVER_PULLUP					BIT6PULLUP  ///*pull-up*///
#define		KEYOPENCOVER_SET						BIT6SET
//#define		KEYOPENCOVER_FilterDis	BIT6FilterDis
//#define		KEYOPENCOVER_FilterEn		BIT6FilterEn
//#define		KEYOPENCOVER_ANALOG_MODE	BIT4ANOLOG
//#define		KeyOpenCover_SouceClock_EN	((ulong32)0x00000001)
//#define		KeyOpenCover_SouceClock_DIS	((ulong32)0xfffffffe)
//#define		KeyOpenCover_SouceClock_SFR	RCC->AHBENR
///*开端尾盖*///
#define		IO_KEYOPENTERMINAL						GPIOC		///*allocation in GPIOx*///
#define		KEYOPENTERMINAL_SELECT				GPIO_Pin_8  ///*select the pin*///
#define		KEYOPENTERMINAL_ANALOG_MODE		BIT8ANOLOG
#define		KEYOPENTERMINAL_IN_MODE				BIT8INMODE  ///*input mode*///
#define		KEYOPENTERMINAL_IN_On					BIT8ONIn	///*input Open*///
#define		KEYOPENTERMINAL_IN_Off				BIT8OFFIn	///*input off*///
#define		KEYOPENTERMINAL_OUT_MODE			BIT8OUTMODE  ///*input mode*///
#define		KEYOPENTERMINAL_OUTPUT_OD			BIT8OUTOD
#define		KEYOPENTERMINAL_NOPUPD				BIT8NOPUPD  ///*no pull-up,no pull-down*///
#define		KEYOPENTERMINAL_PULLUP				BIT8PULLUP  ///*pull-up*///
//#define		KEYOPENTERMINAL_FilterDis			BIT7FilterDis
//#define		KEYOPENTERMINAL_FilterEn			BIT7FilterEn
//#define		KEYOPENTERMINAL_ANALOG_MODE	BIT5ANOLOG
//#define		KeyOpenTerminal_SouceClock_EN	((ulong32)0x00000001)
//#define		KeyOpenTerminal_SouceClock_DIS	((ulong32)0xfffffffe)
//#define		KeyOpenTerminal_SouceClock_SFR	RCC->AHBENR
#define		KeyOpenTerminal_SET						BIT8SET
///*辅助电源检测*///
//#define		IO_CHECKAUPOWER					GPIOB		///*allocation in GPIOx*///
//#define		CHECKAUPOWER_SELECT			GPIO_Pin_10  ///*select the pin*///
//#define		CHECKAUPOWER_ANALOG_MODE	BIT10ANOLOG
//#define		CHECKAUPOWER_IN_MODE		BIT10INMODE  ///*input mode*///
//#define		CHECKAUPOWER_IN_On			BIT10ONIn	///*input Open*///
//#define		CHECKAUPOWER_IN_Off			BIT10OFFIn	///*input off*///
//#define		CHECKAUPOWER_NOPUPD			BIT10NOPUPD  ///*no pull-up,no pull-down*///
//#define		CHECKAUPOWER_PULLUP			BIT10PULLUP
////#define		CHECKAUPOWER_FilterDis	BIT4FilterDis
////#define		CHECKAUPOWER_FilterEn		BIT4FilterEn
////#define		CHECKAUPOWER_ANALOG_MODE	BIT8ANOLOG
//#define		CHECKAUPOWER_SET				BIT10SET
///*DET1磁场检测*///
#define		IO_MAGNETICRIGHT				GPIOF		///*allocation in GPIOx*///
#define		MAGNETICRIGHT_SELECT		GPIO_Pin_8  ///*select the pin*///
#define		MAGNETICRIGHT_ANALOG_MODE		BIT8ANOLOG
#define		MAGNETICRIGHT_IN_MODE		BIT8INMODE  ///*input mode*///
#define		MAGNETICRIGHT_IN_On			BIT8ONIn	///*input Open*///
#define		MAGNETICRIGHT_IN_Off		BIT8OFFIn	///*input off*///
#define		MAGNETICRIGHT_NOPUPD		BIT8NOPUPD  ///*no pull-up,no pull-down*///
#define		MAGNETICRIGHT_PULLUP		BIT8PULLUP
//#define		MAGNETICRIGHT_FilterDis	BIT8FilterDis
//#define		MAGNETICRIGHT_FilterEn	BIT8FilterEn
//#define		MAGNETICRIGHT_ANALOG_MODE	BIT0ANOLOG
#define		MAGNETICRIGHT_SET				BIT8SET
///*DET2磁场检测*///
#define		IO_MAGNETICRIGHTUP				GPIOB		///*allocation in GPIOx*///
#define		MAGNETICRIGHTUP_SELECT		GPIO_Pin_11  ///*select the pin*///
#define		MAGNETICRIGHTUP_ANALOG_MODE		BIT11ANOLOG
#define		MAGNETICRIGHTUP_IN_MODE		BIT11INMODE  ///*input mode*///
#define		MAGNETICRIGHTUP_IN_On			BIT11ONIn	///*input Open*///
#define		MAGNETICRIGHTUP_IN_Off		BIT11OFFIn	///*input off*///
#define		MAGNETICRIGHTUP_NOPUPD		BIT11NOPUPD  ///*no pull-up,no pull-down*///
#define		MAGNETICRIGHTUP_PULLUP		BIT11PULLUP
//#define		MAGNETICRIGHTUP_FilterDis	BIT11FilterDis
//#define		MAGNETICRIGHTUP_FilterEn	BIT11FilterEn
//#define		MAGNETICRIGHTUP_ANALOG_MODE	BIT0ANOLOG
#define		MAGNETICRIGHTUP_SET				BIT11SET
///*DET3场检测*///
#define		IO_MAGNETICLEFT					GPIOC			///*allocation in GPIOx*///
#define		MAGNETICLEFT_SELECT			GPIO_Pin_9 	///*select the pin*///
#define		MAGNETICLEFT_ANALOG_MODE		BIT9ANOLOG
#define		MAGNETICLEFT_IN_MODE		BIT9INMODE 	///*input mode*///
#define		MAGNETICLEFT_IN_On			BIT9ONIn	///*input Open*///
#define		MAGNETICLEFT_IN_Off			BIT9OFFIn	///*input off*///
#define		MAGNETICLEFT_NOPUPD			BIT9NOPUPD 	///*no pull-up,no pull-down*///
#define		MAGNETICLEFT_PULLUP		BIT9PULLUP
//#define		MAGNETICLEFT_FilterDis	BIT8FilterDis
//#define		MAGNETICLEFT_FilterEn		BIT8FilterEn
//#define		MAGNETICLEFT_ANALOG_MODE	BIT12ANOLOG
#define		MAGNETICLEFT_SET				BIT9SET
///*DET4磁场检测*///
#define		IO_MAGNETICLEFTUP					GPIOC			///*allocation in GPIOx*///
#define		MAGNETICLEFTUP_SELECT			GPIO_Pin_9		///*select the pin*///
#define		MAGNETICLEFTUP_ANALOG_MODE		BIT9ANOLOG
#define		MAGNETICLEFTUP_IN_MODE		BIT9INMODE		///*input mode*///
#define		MAGNETICLEFTUP_IN_On			BIT9ONIn	///*input Open*///
#define		MAGNETICLEFTUP_IN_Off			BIT9OFFIn	///*input off*///
#define		MAGNETICLEFTUP_NOPUPD			BIT9NOPUPD		///*no pull-up,no pull-down*///
#define		MAGNETICLEFTUP_PULLUP		BIT9PULLUP
//#define		MAGNETICLEFTUP_FilterDis	BIT8FilterDis
//#define		MAGNETICLEFTUP_FilterEn		BIT8FilterEn
//#define		MAGNETICLEFTUP_ANALOG_MODE	BIT12ANOLOG
#define		MAGNETICLEFTUP_SET				BIT9SET
///*继电器检测*///
#define		IO_RELAYSTATUS			GPIOA			///*allocation in GPIOx*///
#define		RELAYSTATUS_SELECT		GPIO_Pin_10		///*select the pin*///
#define		RELAYSTATUS_ANALOG_MODE	BIT10ANOLOG
#define		RELAYSTATUS_IN_MODE		BIT10INMODE		///*input mode*///
#define		RELAYSTATUS_IN_On		BIT10ONIn	///*input Open*///
#define		RELAYSTATUS_IN_Off		BIT10OFFIn	///*input off*///
#define		RELAYSTATUS_NOPUPD		BIT10NOPUPD		///*no pull-up,no pull-down*///
///*外置继电器检测*///
#define		IO_EXTERNALRELAYSTATUS		        GPIOB		///*allocation in GPIOx*///
#define		EXTERNALRELAYSTATUS_SELECT	        GPIO_Pin_1	///*select the pin*///
#define		EXTERNALRELAYSTATUS_ANALOG_MODE		BIT1ANOLOG
#define		EXTERNALRELAYSTATUS_IN_MODE			BIT1INMODE	///*input mode*///
#define		EXTERNALRELAYSTATUS_IN_On			BIT1ONIn	///*input Open*///
#define		EXTERNALRELAYSTATUS_IN_Off			BIT1OFFIn	///*input off*///
#define		EXTERNALRELAYSTATUS_NOPUPD			BIT1NOPUPD	///*no pull-up,no pull-down*///
///*继电器数字滤波*///
#define		IO_RELAYFILT			GPIO			///*allocation in GPIOx*///
#define		RELAYFILT_On		    BIT2On		    ///*开启数字滤波*///
#define		RELAYFILT_Off		    BIT2Off		    ///*开启数字滤波*///
//#define		RELAYSTATUS_ANALOG_MODE	BIT11ANOLOG
#define		RELAYSTATUS_SET				BIT10SET
///*模块发送状态检测*///
#define		IO_MODULESTATUS				GPIOF			///*allocation in GPIOx*///
#define		MODULESTATUS_SELECT		GPIO_Pin_9		///*select the pin*///
#define		MODULESTATUS_ANALOG_MODE		BIT9ANOLOG
#define		MODULESTATUS_IN_MODE	BIT9INMODE		///*input mode*///
#define		MODULESTATUS_IN_On		BIT9ONIn	///*input Open*///
#define		MODULESTATUS_IN_Off		BIT9OFFIn	///*input off*///
#define		MODULESTATUS_NOPUPD		BIT9NOPUPD		///*no pull-up,no pull-down*///
//#define		MODULESTATUS_ANALOG_MODE	BIT9ANOLOG
#define		MODULESTATUS_SET			BIT9SET
///*插卡状态检测*///
#define		IO_CARDSTATUS					GPIOE			///*allocation in GPIOx*///
#define		CARDSTATUS_SELECT			GPIO_Pin_9		///*select the pin*///
#define		CARDSTATUS_ANALOG_MODE		BIT9ANOLOG
#define		CARDSTATUS_IN_MODE		BIT9INMODE		///*input mode*///
#define		CARDSTATUS_IN_On			BIT9ONIn	///*input Open*///
#define		CARDSTATUS_IN_Off			BIT9OFFIn	///*input off*///
#define		CARDSTATUS_NOPUPD			BIT9NOPUPD  	///*no pull-up,no pull-down*///
#define		CARDSTATUS_PULLUP			BIT9PULLUP  	///*no pull-up,no pull-down*///
//#define		CARDSTATUS_FilterDis	BIT2FilterDis
//#define		CARDSTATUS_FilterEn		BIT2FilterEn
//#define		CARDSTATUS_ANALOG_MODE	BIT13ANOLOG
#define		CARDSTATUS_SET				BIT9SET
///*****************************************************************************************///
///*****************************************************************************************///
///*output io*///
///*背光灯*///
#define		IO_BACKLIGHT					GPIOA
#define		BACKLIGHT_SELECT			GPIO_Pin_11		///*select the pin:bit4*///
#define		BACKLIGHT_IN_MODE			BIT11INMODE		///*00:Input,reset state*///
#define		BACKLIGHT_OUT_MODE		BIT11OUTMODE		///*01:Output*///
#define		BACKLIGHT_OUTPUT_PP		BIT11OUTPP		///*0:Output Push-Pull,reset state*///
//#define		BACKLIGHT_SPEED_2MHZ	BIT10OUT2MHZ
//#define		BACKLIGHT_SPEED_INIT	BIT10OUTSPEEDINIT
#define		BACKLIGHTSET					BIT11SET
#define		BACKLIGHTRESET				BIT11RESET
#define		BACKLIGHT_NOPUPD			BIT11NOPUPD		///*no pull-up,no pull-down*///
///*拉闸指示灯*///
#define		IO_TRIPLED						GPIOG
#define		TRIPLED_SELECT				GPIO_Pin_2			///*select the pin:bit4*///
#define		TRIPLED_IN_MODE				BIT2INMODE			///*00:Input,reset state*///
#define		TRIPLED_OUT_MODE			BIT2OUTMODE			///*01:Output*///
#define		TRIPLED_OUTPUT_OD			BIT2OUTOD			///*0:Output Push-Pull,reset state*///
#define		TRIPLED_OUTPUT_PP			BIT2OUTPP			///*0:Output Push-Pull,reset state*///
//#define		TRIPLED_SPEED_2MHZ		BIT7OUT2MHZ
//#define		TRIPLED_SPEED_INIT		BIT7OUTSPEEDINIT
#define		TRIPLEDSET						BIT2SET
#define		TRIPLEDRESET					BIT2RESET
#define		TRIPLED_NOPUPD				BIT2NOPUPD			///*no pull-up,no pull-down*///
///*蜂鸣器*///
//#define		IO_BEEP						GPIOB				///*allocation in GPIO*///
//#define		BEEP_SELECT				GPIO_Pin_10			///*select the pin:bit2*///
//#define		BEEP_IN_MODE			BIT10INMODE			///*00:Input,reset state*///
//#define		BEEP_OUT_MODE			BIT10OUTMODE			///*01:Output*///
//#define		BEEP_OUTPUT_PP		BIT10OUTPP			///*0:Output Push-Pull,reset state*///
////#define		BEEP_SPEED_2MHZ		BIT5OUT2MHZ
////#define		BEEP_SPEED_INIT		BIT5OUTSPEEDINIT
//#define		BEEPSET						BIT10SET
//#define		BEEPRESET					BIT10RESET
//#define		BEEP_NOPUPD				BIT10NOPUPD			///*no pull-up,no pull-down*///
///*报警继电器输出*///
#define		IO_WARNOUT					GPIOA				///*allocation in GPIO*///
#define		WARNOUT_SELECT			GPIO_Pin_7			///*select the pin:bit2*///
#define		WARNOUT_IN_MODE			BIT7INMODE			///*00:Input,reset state*///
#define		WARNOUT_OUT_MODE		BIT7OUTMODE		///*01:Output*///
#define		WARNOUT_OUTPUT_PP		BIT7OUTPP			///*0:Output Push-Pull,reset state*///
//#define		WARNOUT_SPEED_2MHZ	BIT5OUT2MHZ
//#define		WARNOUT_SPEED_INIT	BIT5OUTSPEEDINIT
#define		WARNOUTSET					BIT7SET
#define		WARNOUTRESET				BIT7RESET
#define		WARNOUT_NOPUPD			BIT7NOPUPD			///*no pull-up,no pull-down*///
///*秒脉冲输出控制*///
#define		IO_SECOND						GPIOD			///*allocation in GPIO*///
#define		SECOND_SELECT				GPIO_Pin_0			///*select the pin:bit7*///
#define		SECOND_IN_MODE			BIT0INMODE			///*00:Input,reset state*///
#define		SECOND_OUT_MODE			BIT0OUTMODE			///*01:Output*///
#define		SECOND_OUTPUT_PP		BIT0OUTPP			///*0:Output Push-Pull,reset state*///
//#define		SECOND_SPEED_2MHZ		BIT8OUT2MHZ
//#define		SECOND_SPEED_INIT		BIT8OUTSPEEDINIT
#define		SECONDSET						BIT0SET
#define		SECONDRESET					BIT0RESET
#define		SECOND_NOPUPD				BIT0NOPUPD			///*no pull-up,no pull-down*///
///*MCU秒脉冲输出*///
#define		IO_MCUSECOND						GPIOG			///*allocation in GPIO*///
#define		IO_MCUSECOND_COMMON			GPIO  ///*多功能口
#define		MCUSECOND_ANALOG_MODE		BIT6ANOLOG
//#define		MCUSECOND_ANALOG_MODE		BIT1AFMODE	///*analog mode*///
#define		MCUSECOND_SELECT_AF			BIT6AFMODE			///*select the pin:bit7*///
//#define		MCUSECOND_SELECT_AF2		AFCFG2_Pin_1			///*select the pin:bit7*///
#define		MCUSECOND_IN_On				BIT6ONIn			///*00:Input,reset state*///
#define		MCUSECOND_IN_Off				BIT6OFFIn			///*00:Input,reset state*///
#define		MCUSECOND_IN_MODE				BIT6INMODE			///*00:Input,reset state*///
#define		MCUSECOND_OUT_MODE			BIT6OUTMODE			///*01:Output*///
#define		MCUSECOND_OUTPUT_PP			BIT6OUTPP			///*0:Output Push-Pull,reset state*///
#define		MCUSECOND_OUTPUT_OD			BIT6OUTOD			
#define		MCUSECONDSET						BIT6SET
#define		MCUSECONDRESET					BIT6RESET
#define		MCUSECOND_NOPUPD				BIT6NOPUPD			///*no pull-up,no pull-down*///
#define		MCUSECOND_PULLUP				BIT6PULLUP			///*no pull-up,no pull-down*///

///*需量周期/时段投切脉冲*///
#define		IO_DEMANDCYCLE					GPIOD			///*allocation in GPIO*///
#define		DEMANDCYCLE_SELECT			GPIO_Pin_1		///*select the pin:bit7*///
#define		DEMANDCYCLE_IN_MODE			BIT1INMODE		///*00:Input,reset state*///
#define		DEMANDCYCLE_IN_On			BIT1ONIn		///*00:Input,reset state*///
#define		DEMANDCYCLE_OUT_MODE		BIT1OUTMODE	///*01:Output*///
#define		DEMANDCYCLE_OUTPUT_OD		BIT1OUTOD		///*0:Output Push-Pull,reset state*///
//#define		DEMANDCYCLE_SPEED_2MHZ	BIT8OUT2MHZ
//#define		DEMANDCYCLE_SPEED_INIT	BIT8OUTSPEEDINIT
#define		DEMANDCYCLESET					BIT1SET
#define		DEMANDCYCLERESET				BIT1RESET
#define		DEMANDCYCLE_NOPUPD			BIT1NOPUPD		///*no pull-up,no pull-down*///
///*****************************************************************************************///
///*计量芯片电源控制*///
#define		IO_EMETERPOWER				GPIOC			///*allocation in GPIO*///
#define		EMETERPOWER_SELECT		GPIO_Pin_10		///*select the pin:bit7*///
#define		EMETERPOWER_IN_MODE		BIT10INMODE		///*00:Input,reset state*///
#define		EMETERPOWER_OUT_MODE	BIT10OUTMODE	///*01:Output*///
#define		EMETERPOWER_OUTPUT_PP	BIT10OUTPP		///*0:Output Push-Pull,reset state*///
#define		EMETERPOWER_OUTPUT_OD	BIT10OUTOD		///*0:Output Push-Pull,reset state*///
//#define		EMETERPOWER_SPEED_2MHZ	BIT11OUT2MHZ
//#define		EMETERPOWER_SPEED_INIT	BIT11OUTSPEEDINIT
#define		EMETERPOWERSET				BIT10SET
#define		EMETERPOWERRESET			BIT10RESET
#define		EMETERPOWER_NOPUPD		BIT10NOPUPD		///*no pull-up,no pull-down*///
///*红外发射及Flash电源控制*///
#define		IO_FLASHPOWER					GPIOC			///*allocation in GPIO*///
#define		FLASHPOWER_SELECT			GPIO_Pin_11		///*select the pin:bit7*///
#define		FLASHPOWER_IN_MODE		BIT11INMODE		///*00:Input,reset state*///
#define		FLASHPOWER_OUT_MODE		BIT11OUTMODE		///*01:Output*///
#define		FLASHPOWER_OUTPUT_PP	BIT11OUTPP		///*0:Output Push-Pull,reset state*///
#define		FLASHPOWER_OUTPUT_OD	BIT11OUTOD		///*0:Output Push-Pull,reset state*///
//#define		FLASHPOWER_SPEED_2MHZ	BIT14OUT2MHZ
//#define		FLASHPOWER_SPEED_INIT	BIT14OUTSPEEDINIT
#define		FLASHPOWERSET					BIT11SET
#define		FLASHPOWERRESET				BIT11RESET
#define		FLASHPOWER_NOPUPD			BIT11NOPUPD		///*no pull-up,no pull-down*///
///液晶LCD电源控制*///
#define		IO_LCDPOWER					GPIOG			///*allocation in GPIO*///
#define		LCDPOWER_SELECT			GPIO_Pin_5		///*select the pin:bit7*///
//#define		IO_LCDPOWER_AF			AF_Pin_5		///*allocation in GPIO*///
//#define		IO_LCDPOWER_AF2			AFCFG2_Pin_5		///*allocation in GPIO*///
#define		LCDPOWER_OUT_MODE		BIT5OUTMODE		///*01:Output*///
#define		LCDPOWER_IN_MODE			BIT5INMODE
#define		LCDPOWER_OUTPUT_OD	BIT5OUTOD		///*0:Output Push-Pull,reset state*///
#define		LCDPOWER_OUTPUT_PP	BIT5OUTPP		
#define		LCDPOWERSET					BIT5SET
#define		LCDPOWERRESET				BIT5RESET
///*超级电容充电控制*///
#define		IO_CAPCHARGE					GPIOA			///*allocation in GPIO*///
#define		CAPCHARGE_SELECT			GPIO_Pin_12		///*select the pin:bit7*///
#define		CAPCHARGE_IN_MODE			BIT12INMODE		///*00:Input,reset state*///
#define		CAPCHARGE_OUT_MODE		BIT12OUTMODE		///*01:Output*///
#define		CAPCHARGE_OUTPUT_PP		BIT12OUTPP		///*0:Output Push-Pull,reset state*///
#define		CAPCHARGE_OUTPUT_OD		BIT12OUTOD	
//#define		CAPCHARGE_SPEED_2MHZ	BIT7OUT2MHZ
//#define		CAPCHARGE_SPEED_INIT	BIT7OUTSPEEDINIT
#define		CAPCHARGESET					BIT12SET
#define		CAPCHARGERESET				BIT12RESET
#define		CAPCHARGE_NOPUPD			BIT12NOPUPD		///*no pull-up,no pull-down*///
///*超级电容放电控制*///
#define		IO_CAPDISCHARGE					GPIOA			///*allocation in GPIO*///
#define		CAPDISCHARGE_SELECT			GPIO_Pin_13		///*select the pin:bit7*///
#define		CAPDISCHARGE_IN_MODE		BIT13INMODE		///*00:Input,reset state*///
#define		CAPDISCHARGE_OUT_MODE		BIT13OUTMODE		///*01:Output*///
#define		CAPDISCHARGE_OUTPUT_PP	BIT13OUTPP		///*0:Output Push-Pull,reset state*///
#define		CAPDISCHARGE_OUTPUT_OD	BIT13OUTOD	
//#define		CAPDISCHARGE_SPEED_2MHZ	BIT9OUT2MHZ
//#define		CAPDISCHARGE_SPEED_INIT	BIT9OUTSPEEDINIT
#define		CAPDISCHARGESET					BIT13SET
#define		CAPDISCHARGERESET				BIT13RESET
#define		CAPDISCHARGE_NOPUPD			BIT13NOPUPD		///*no pull-up,no pull-down*///

/*6V电池电源控制*/
#define		IO_BATTPOWER				GPIOC		    /*allocation in GPIO*/
#define		BATTPOWER_SELECT			GPIO_Pin_14		/*select the pin:bit2*/
#define		BATTPOWER_IN_MODE			BIT14INMODE		/*00:Input,reset state*/
#define		BATTPOWER_IN_On			    BIT14ONIn
#define		BATTPOWER_OUT_MODE		    BIT14OUTMODE	/*01:Output*/
#define		BATTPOWER_OUTPUT_PP		    BIT14OUTPP		/*0:Output Push-Pull,reset state*/
#define		BATTPOWER_OUTPUT_OD         BIT14OUTOD

#if 0
#define		BATTPOWER_SPEED_2MHZ	    BIT11OUT2MHZ
#define		BATTPOWER_SPEED_INIT	    BIT11OUTSPEEDINIT
#endif

#define		BATTPOWERSET				BIT14SET
#define		BATTPOWERRESET				BIT14RESET
#define		BATTPOWER_NOPUPD			BIT14NOPUPD		/*no pull-up,no pull-down*/

///*6V电池放电控制：防止电池钝化*///
//#define		IO_BATTDISCHARGE					GPIOB		///*allocation in GPIO*///
//#define		IO_BATTDISCHARGE_AF				AF_Pin_15		///*allocation in GPIO*///
//#define		IO_BATTDISCHARGE_AF2			AFCFG2_Pin_15		///*allocation in GPIO*///
//#define		BATTDISCHARGE_SELECT			GPIO_Pin_15	///*select the pin:bit2*///
//#define		BATTDISCHARGE_IN_MODE			BIT15INMODE	///*00:Input,reset state*///
//#define		BATTDISCHARGE_OUT_MODE		BIT15OUTMODE	///*01:Output*///
//#define		BATTDISCHARGE_OUTPUT_PP		BIT15OUTPP	///*Output Push-Pull*///
////#define		BATTDISCHARGE_SPEED_2MHZ	BIT15OUT2MHZ
////#define		BATTDISCHARGE_SPEED_INIT	BIT15OUTSPEEDINIT
//#define		BATTDISCHARGESET					BIT15SET
//#define		BATTDISCHARGERESET				BIT15RESET
//#define		BATTDISCHARGE_NOPUPD			BIT15NOPUPD	///*no pull-up,no pull-down*///
///*外置负荷开关控制*///
#define		IO_EXTERNALRELAY					GPIOF	///*allocation in GPIO*///
#define		EXTERNALRELAY_SELECT			GPIO_Pin_10	///*select the pin:bit2*///
#define		EXTERNALRELAY_IN_MODE			BIT10INMODE	///*00:Input,reset state*///
#define		EXTERNALRELAY_OUT_MODE		BIT10OUTMODE	///*01:Output*///
#define		EXTERNALRELAY_OUTPUT_PP		BIT10OUTPP	///*Output Push-Pull*///
//#define		EXTERNALRELAY_SPEED_2MHZ	BIT6OUT2MHZ
//#define		EXTERNALRELAY_SPEED_INIT	BIT6OUTSPEEDINIT
#define		EXTERNALRELAYSET					BIT10SET
#define		EXTERNALRELAYRESET				BIT10RESET
#define		EXTERNALRELAY_NOPUPD			BIT10NOPUPD	///*no pull-up,no pull-down*///
///*内置负荷开关控制:A*///
#define		IO_RELAYA						GPIOA		///*allocation in GPIO*///
#define		RELAYA_SELECT				GPIO_Pin_8		///*select the pin:bit8*///
#define		RELAYA_IN_MODE			BIT8INMODE		///*00:Input,reset state*///
#define		RELAYA_OUT_MODE			BIT8OUTMODE	///*01:Output*///
#define		RELAYA_OUTPUT_PP		BIT8OUTPP		///*Output Push-Pull*///
//#define		RELAYA_SPEED_2MHZ		BIT6OUT2MHZ
//#define		RELAYA_SPEED_INIT		BIT6OUTSPEEDINIT
#define		RELAYASET						BIT8SET
#define		RELAYARESET					BIT8RESET
#define		RELAYA_NOPUPD				BIT8NOPUPD		///*no pull-up,no pull-down*///
///*内置负荷开关控制:B*///
#define		IO_RELAYB						GPIOA			///*allocation in GPIO*///
#define		RELAYB_SELECT				GPIO_Pin_9		///*select the pin:bit8*///
#define		RELAYB_IN_MODE			BIT9INMODE		///*00:Input,reset state*///
#define		RELAYB_OUT_MODE			BIT9OUTMODE	///*01:Output*///
#define		RELAYB_OUTPUT_PP		BIT9OUTPP		///*Output Push-Pull*///
//#define		RELAYB_SPEED_2MHZ		BIT4OUT2MHZ
//#define		RELAYB_SPEED_INIT		BIT4OUTSPEEDINIT
#define		RELAYBSET						BIT9SET
#define		RELAYBRESET					BIT9RESET
#define		RELAYB_NOPUPD				BIT9NOPUPD		///*no pull-up,no pull-down*///
///*红外接收电源*///
#define		IO_INFRARXPOWER					GPIOC		///*allocation in GPIO*///
#define		INFRARXPOWER_SELECT			GPIO_Pin_12	///*select the pin:bit8*///
#define		INFRARXPOWER_IN_MODE		BIT12INMODE	///*00:Input,reset state*///
#define		INFRARXPOWER_OUT_MODE		BIT12OUTMODE	///*01:Output*///
#define		INFRARXPOWER_OUTPUT_PP	BIT12OUTPP	///*Output Push-Pull*///
#define		INFRARXPOWER_OUTPUT_OD	BIT12OUTOD
//#define		INFRARXPOWER_SPEED_2MHZ	BIT7OUT2MHZ
//#define		INFRARXPOWER_SPEED_INIT	BIT7OUTSPEEDINIT
#define		INFRARXPOWERSET					BIT12SET
#define		INFRARXPOWERRESET				BIT12RESET
#define		INFRARXPOWER_NOPUPD			BIT12NOPUPD	///*no pull-up,no pull-down*///
///*模块复位*///
#define		IO_MODULERESET					GPIOF		///*allocation in GPIO*///
#define		MODULERESET_SELECT			GPIO_Pin_6	///*select the pin:bit8*///
#define		MODULERESET_IN_MODE			BIT6INMODE	///*00:Input,reset state*///
#define		MODULERESET_OUT_MODE		BIT6OUTMODE	///*01:Output*///
#define		MODULERESET_OUTPUT_OD		BIT6OUTOD	///*Output Open-Drain*///
//#define		MODULERESET_SPEED_2MHZ	BIT9OUT2MHZ
//#define		MODULERESET_SPEED_INIT	BIT9OUTSPEEDINIT
#define		MODULERESETSET					BIT6SET
#define		MODULERESETRESET				BIT6RESET
#define		MODULERESET_NOPUPD			BIT6NOPUPD	///*no pull-up,no pull-down*///
///*模块设置*///
#define		IO_MODULESET						GPIOF			///*allocation in GPIO*///
#define		MODULESET_SELECT				GPIO_Pin_7		///*select the pin:bit8*///
#define		MODULESET_IN_MODE				BIT7INMODE		///*00:Input,reset state*///
#define		MODULESET_OUT_MODE			BIT7OUTMODE	///*01:Output*///
#define		MODULESET_OUTPUT_OD			BIT7OUTOD		///*Output Open-Drain*///
//#define		MODULESET_SPEED_2MHZ		BIT11OUT2MHZ
//#define		MODULESET_SPEED_INIT		BIT11OUTSPEEDINIT
#define		MODULESETSET						BIT7SET
#define		MODULESETRESET					BIT7RESET
#define		MODULESET_NOPUPD				BIT7NOPUPD		///*no pull-up,no pull-down*///
///*主动上报*///
#define		IO_EVENTOUT							GPIOF		///*allocation in GPIO*///
#define		EVENTOUT_SELECT					GPIO_Pin_5		///*select the pin:bit8*///
#define		EVENTOUT_IN_MODE				BIT5INMODE		///*00:Input,reset state*///
#define		EVENTOUT_OUT_MODE				BIT5OUTMODE		///*01:Output*///
#define		EVENTOUT_OUTPUT_OD			BIT5OUTOD		///*Output Open-Drain*///
//#define		EVENTOUT_SPEED_2MHZ			BIT8OUT2MHZ
//#define		EVENTOUT_SPEED_INIT			BIT8OUTSPEEDINIT
#define		EVENTOUTSET							BIT5SET
#define		EVENTOUTRESET						BIT5RESET
#define		EVENTOUT_NOPUPD					BIT5NOPUPD		///*no pull-up,no pull-down*///
///*****************************************************************************************///
///*掉电检测口线*///
#define		IO_POWERDOWN					GPIOF			///*allocation in GPIO*///
//#define		IO_POWERDOWN_AF				AF_Pin_11			///*alternate function register is AFRL*///
//#define		IO_POWERDOWN_AF1			AFCFG1_Pin_11		///*alternate function register is AFRL*///
#define		POWERDOWN_SELECT			GPIO_Pin_11		///*select the pin*///
#define		POWERDOWN_IN_MODE			BIT11INMODE		///*00:Input,reset state*///
#define		POWERDOWN_Ana_MODE			BIT11ANOLOG		
#define		POWERDOWN_INOn				BIT11ONIn
//#define		POWERDOWN_ANALOG_MODE	BIT6ANOLOG
//#define		POWERDOWN_AF_RESET		AFCFG1_Pin_7
#define		POWERDOWN_NOPUPD			BIT11NOPUPD		///*no pull-up,no pull-down*///
#define		POWERDOWN_SET					BIT11SET

#define		PowerDown_IRQHandler		SVD_IRQHandler		///*中断服务程序*///
#define		PowerDown_IRQn					SVD_IRQn					///*中断向量地址*///
//#define		PowerDown_NoMask				PMU_PMUIE_LVD0IE	///*中断不屏蔽*///
//#define		PowerDown_Rising				0x00000040			///*上升沿*///
//#define		PowerDown_Falling				0x00000040			///*下降沿*///
//#define		PowerDown_Trigger				PMU_PMUIF_LVD0IF			///*触发标志*///
//#define		PowerDown_TriggerSta		PMU_PMUSTA_LVD0FLG		//*触发标志,1：表示LVDIN引脚电压大于1.21V阈值*///
//#define		PowerDown_ConfigRegister	EXTICR[1]			///*外部触发中断口线选择寄存器*///
//#define		PowerDown_Configration_Select	SYSCFG_EXTICR2_EXTI6_PE
///*****************************************************************************************///


///*****************************************************************************************///
///*****************************************************************************************///
///*****************************************************************************************///
///*****************************************************************************************///
///*****************************************************************************************///

/////*背光灯:口线推挽输出*///
//extern	SwitchOn_BackLight();
//extern	SwitchOff_BackLight();
/////*拉闸指示灯:口线开漏输出*///
//extern	SwitchOn_TripLed();
//extern	SwitchOff_TripLed();
/////*蜂鸣器:口线推挽输出*///
//extern	SwitchOn_Beep();
//extern	SwitchOff_Beep();
/////*报警继电器输出:口线推挽输出*///
//extern	SwitchOn_WarnOut();
//extern	SwitchOff_WarnOut();
/////*秒脉冲:口线推挽输出*///
//extern	Select_SecondPulseOut();
//extern	Select_DemandPulseOut();
//extern	Select_RatePulseOut();
//extern	Close_MultiFunctionOut();
/////*计量芯片电源控制:口线推挽输出*///
//extern	SwitchOn_MeterICPower();
//extern	SwitchOff_MeterICPower();
/////*红外发射及Flash电源控制:口线推挽输出*///
//extern	SwitchOn_FlashPower();
//extern	SwitchOff_FlashPower();
/////*超级电容充电控制:口线推挽输出*///
//extern	SuperCapCharge_En();
//extern	SuperCapCharge_Dis();
/////*超级电容放电控制:口线推挽输出*///
//extern	SwitchOn_SuperCapPower();
//extern	SwitchOff_SuperCapPower();
/////*6V电池电源控制:口线推挽输出*///
//extern	SwitchOn_WakeUpPower();
//extern	SwitchOff_WakeUpPower();
/////*6V电池放电控制：防止电池钝化:口线推挽输出*///
//extern	SwitchOn_PreventBlunt();
//extern	SwitchOff_PreventBlunt();
/////*外置负荷开关控制:口线推挽输出*///
//extern	SwitchOn_ExternalRelay();
//extern	SwitchOff_ExternalRelay();
/////*内置负荷开关控制:A:口线推挽输出*///
//extern	SwitchOn_InternalRelay();
//extern	SwitchOff_InternalRelay();
//extern	Hold_InternalRelay();
/////*主动上报:口线开漏输出*///
//extern	EventOut_EN();
//extern	EventOut_DIS();
/////*模块设置:口线开漏输出*///
//extern	ModuleSet_EN();
//extern	ModuleSet_DIS();
/////*模块复位:口线开漏输出*///
//extern	Module_EN();
//extern	Module_Reset();
/////*红外接收电源:口线推挽输出*///
//extern	SwitchOn_InfrarxPower();
//extern	SwitchOff_InfrarxPower();
/////*卡电源:口线开漏输出*///}
//extern	SwitchOn_CardPower();
//extern	SwitchOff_CardPower();
/////*卡时钟:口线开漏输出*///
//extern	CardSck_EN();
//extern	CardSck_DIS();
/////*卡复位:口线开漏输出*///
//extern	Card_EN();
//extern	Card_Reset();
/////*ESAM电源:口线推挽输出*///
//extern	SwitchOn_EsamPower();
//extern	SwitchOff_EsamPower();
/////*ESAM复位:口线推挽输出*///
//extern	Esam_EN();
//extern	Esam_Reset();

///*****************************************************************************************///
///*上翻键:开内部上拉*///
#define	SET_KEYUP_INPUT()		{ulong32 SV_ulTemp_GPIO;\
								SV_ulTemp_GPIO = IO_KEYUP->MODER;\
								SV_ulTemp_GPIO &= KEYUP_IN_MODE;\
								IO_KEYUP->MODER = SV_ulTemp_GPIO;\
								IO_KEYUP->INEN |= KEYUP_IN_On;\
								SV_ulTemp_GPIO = IO_KEYUP->PUPDR;\
								SV_ulTemp_GPIO &= KEYUP_NOPUPD;\
								SV_ulTemp_GPIO |= KEYUP_PULLUP;\
								IO_KEYUP->PUPDR = SV_ulTemp_GPIO;}
#define	CLOSE_KEYUP_PULLUP()	{ulong32 SV_ulTemp_GPIO;\
								SV_ulTemp_GPIO = IO_KEYUP->PUPDR;\
								SV_ulTemp_GPIO &= KEYUP_NOPUPD;\
								IO_KEYUP->PUPDR = SV_ulTemp_GPIO;}
///*停电后定时查看有无上翻键*///
//#define	Enable_KeyUp_IOClock()		{KeyUp_SouceClock_SFR |= KeyUp_SouceClock_EN;}
//#define	Disable_KeyUp_IOClock()		{KeyUp_SouceClock_SFR &= KeyUp_SouceClock_DIS;}
//#define Set_KeyUp_Analog()			{ulong32 SV_ulTemp_GPIO;\
//									SV_ulTemp_GPIO = IO_KEYUP->MODER;\
//									SV_ulTemp_GPIO |= KEYUP_ANALOG_MODE;\
//									IO_KEYUP->MODER = SV_ulTemp_GPIO;}
#define	READ_KEYUP				(IO_KEYUP->IDR & KEYUPSET)
///*下翻键:开内部上拉*///
#define	SET_KEYDOWN_INPUT()		{ulong32 SV_ulTemp_GPIO;\
								SV_ulTemp_GPIO = IO_KEYDOWN->MODER;\
								SV_ulTemp_GPIO &= KEYDOWN_IN_MODE;\
								IO_KEYDOWN->MODER = SV_ulTemp_GPIO;\
								IO_KEYDOWN->INEN |= KEYDOWN_IN_On;\
								SV_ulTemp_GPIO = IO_KEYDOWN->PUPDR;\
								SV_ulTemp_GPIO &= KEYDOWN_NOPUPD;\
								SV_ulTemp_GPIO |= KEYDOWN_PULLUP;\
								IO_KEYDOWN->PUPDR = SV_ulTemp_GPIO;}
#define	CLOSE_KEYDOWN_PULLUP()	{ulong32 SV_ulTemp_GPIO;\
								SV_ulTemp_GPIO = IO_KEYDOWN->PUPDR;\
								SV_ulTemp_GPIO &= KEYDOWN_NOPUPD;\
								IO_KEYDOWN->PUPDR = SV_ulTemp_GPIO;}
///*停电后定时查看有无下翻键*///
//#define	Enable_KeyDown_IOClock()	{KeyDown_SouceClock_SFR |= KeyDown_SouceClock_EN;}
//#define	Disable_KeyDown_IOClock()	{KeyDown_SouceClock_SFR &= KeyDown_SouceClock_DIS;}
//#define Set_KeyDown_Analog()		{ulong32 SV_ulTemp_GPIO;\
//									SV_ulTemp_GPIO = IO_KEYDOWN->MODER;\
//									SV_ulTemp_GPIO |= KEYDOWN_ANALOG_MODE;\
//									IO_KEYDOWN->MODER = SV_ulTemp_GPIO;}
#define	READ_KEYDOWN			(IO_KEYDOWN->IDR & KEYDOWNSET)
///*按键上拉，上电使用推挽输出高，停电使用开漏输出高（即不使用上拉电阻）*///
//上电推挽输出高
#define	SET_KEYPU_Push_OUTPUT()	  {ulong32 SV_ulTemp_GPIO;\
	                              SV_ulTemp_GPIO = IO_KEYPU->MODER;\
	                              SV_ulTemp_GPIO &= KEYPU_IN_MODE;\
	                              SV_ulTemp_GPIO |= KEYPU_OUT_MODE;\
	                              IO_KEYPU->MODER = SV_ulTemp_GPIO;\
	                              SV_ulTemp_GPIO = IO_KEYPU->OTYPER;\
	                              SV_ulTemp_GPIO &= KEYPU_OUTPUT_PP;\
	                              IO_KEYPU->OTYPER = SV_ulTemp_GPIO;}
#define	SwitchOn_KEYPU_PowerOn()  {IO_KEYPU->BSETH = KEYPUSET;\
								  SET_KEYPU_Push_OUTPUT();\
								  IO_KEYPU->BSETH = KEYPUSET;}
//停电开漏输出高
#define	SET_KEYPU_Pull_OUTPUT()	  {ulong32 SV_ulTemp_GPIO;\
								  SV_ulTemp_GPIO = IO_KEYPU->MODER;\
								  SV_ulTemp_GPIO &= KEYPU_IN_MODE;\
								  SV_ulTemp_GPIO |= KEYPU_OUT_MODE;\
								  IO_KEYPU->MODER = SV_ulTemp_GPIO;\
								  SV_ulTemp_GPIO = IO_KEYPU->OTYPER;\
								  SV_ulTemp_GPIO |= KEYPU_OUTPUT_OD;\
								  IO_KEYPU->OTYPER = SV_ulTemp_GPIO;}

#define	SwitchOff_KEYPU_PowerOff()	{IO_KEYPU->BSETH = KEYPUSET;\
								    SET_KEYPU_Pull_OUTPUT();\
								    IO_KEYPU->BSETH = KEYPUSET;}

/*ZB_PWR_CTL开漏输出高*/
#define	SET_MODULE_PWCTL_OUTPUT()	  {ulong32 SV_ulTemp_GPIO;\
                                    SV_ulTemp_GPIO = IO_MODULE_PWCTL->MODER;\
                                    SV_ulTemp_GPIO &= MODULE_PWCTL_IN_MODE;\
                                    SV_ulTemp_GPIO |= MODULE_PWCTL_OUT_MODE;\
                                    IO_MODULE_PWCTL->MODER = SV_ulTemp_GPIO;\
                                    SV_ulTemp_GPIO = IO_MODULE_PWCTL->OTYPER;\
                                    SV_ulTemp_GPIO |= MODULE_PWCTL_OD;\
                                    IO_MODULE_PWCTL->OTYPER = SV_ulTemp_GPIO;}

#define	SwitchOff_MODULE_PWCTL_PowerOff()	{IO_MODULE_PWCTL->BSETH = MODULE_PWCTLPUSET;\
                                            SET_MODULE_PWCTL_OUTPUT();\
                                            IO_MODULE_PWCTL->BSETH = MODULE_PWCTLPUSET;}

///*编程键:开内部上拉*///
//#define	SET_KEYPRG_INPUT()		{ulong32 SV_ulTemp_GPIO;\
//								SV_ulTemp_GPIO = IO_KEYPRG->MODER;\
//								SV_ulTemp_GPIO &= KEYPRG_IN_MODE;\
//								IO_KEYPRG->MODER = SV_ulTemp_GPIO;\
//								SV_ulTemp_GPIO = IO_KEYPRG->PUPDR;\
//								SV_ulTemp_GPIO &= KEYPRG_NOPUPD;\
//								SV_ulTemp_GPIO |= KEYPRG_PULLUP;\
//								IO_KEYPRG->PUPDR = SV_ulTemp_GPIO;}
//#define	CLOSE_KEYPRG_PULLUP()	{ulong32 SV_ulTemp_GPIO;\
//								SV_ulTemp_GPIO = IO_KEYPRG->PUPDR;\
//								SV_ulTemp_GPIO &= KEYPRG_NOPUPD;\
//								IO_KEYPRG->PUPDR = SV_ulTemp_GPIO;}
//#define	READ_KEYPRG				(IO_KEYPRG->IDR & KEYPRG_SELECT)
///*开表盖:开内部上拉*///
#define	SET_KEYOPENCOVER_INPUT()	{ulong32 SV_ulTemp_GPIO;\
									SV_ulTemp_GPIO = IO_KEYOPENCOVER->MODER;\
									SV_ulTemp_GPIO &= KEYOPENCOVER_IN_MODE;\
									IO_KEYOPENCOVER->MODER = SV_ulTemp_GPIO;\
									IO_KEYOPENCOVER->INEN |= KEYOPENCOVER_IN_On;\
									SV_ulTemp_GPIO = IO_KEYOPENCOVER->PUPDR;\
									SV_ulTemp_GPIO &= KEYOPENCOVER_NOPUPD;\
									SV_ulTemp_GPIO |= KEYOPENCOVER_PULLUP;\
									IO_KEYOPENCOVER->PUPDR = SV_ulTemp_GPIO;}
#define	CLOSE_KEYOPENCOVER_PULLUP()	{ulong32 SV_ulTemp_GPIO;\
									SV_ulTemp_GPIO = IO_KEYOPENCOVER->PUPDR;\
									SV_ulTemp_GPIO &= KEYOPENCOVER_NOPUPD;\
									IO_KEYOPENCOVER->PUPDR = SV_ulTemp_GPIO;}
#define	READ_KEYOPENCOVER			(IO_KEYOPENCOVER->IDR & KEYOPENCOVER_SELECT)
///*开端尾盖:开内部上拉*///
#define	SET_KEYOPENTERMINAL_INPUT()	{ulong32 SV_ulTemp_GPIO;\
									SV_ulTemp_GPIO = IO_KEYOPENTERMINAL->MODER;\
									SV_ulTemp_GPIO &= KEYOPENTERMINAL_IN_MODE;\
									IO_KEYOPENTERMINAL->MODER = SV_ulTemp_GPIO;\
									IO_KEYOPENTERMINAL->INEN |= KEYOPENTERMINAL_IN_On;\
									SV_ulTemp_GPIO = IO_KEYOPENTERMINAL->PUPDR;\
									SV_ulTemp_GPIO &= KEYOPENTERMINAL_NOPUPD;\
									SV_ulTemp_GPIO |= KEYOPENTERMINAL_PULLUP;\
									IO_KEYOPENTERMINAL->PUPDR = SV_ulTemp_GPIO;}
#define	CLOSE_KEYOPENTERMINAL_PULLUP()	{ulong32 SV_ulTemp_GPIO;\
										SV_ulTemp_GPIO = IO_KEYOPENTERMINAL->PUPDR;\
										SV_ulTemp_GPIO &= KEYOPENTERMINAL_NOPUPD;\
										IO_KEYOPENTERMINAL->PUPDR = SV_ulTemp_GPIO;}
#define	READ_KEYOPENTERMINAL			(IO_KEYOPENTERMINAL->IDR & KEYOPENTERMINAL_SELECT)
///*辅助电源检测:开内部上拉*///
#define	SET_CHECKAUPOWER_INPUT()	{ulong32 SV_ulTemp_GPIO;\
									SV_ulTemp_GPIO = IO_CHECKAUPOWER->MODER;\
									SV_ulTemp_GPIO &= CHECKAUPOWER_IN_MODE;\
									IO_CHECKAUPOWER->MODER = SV_ulTemp_GPIO;\
									IO_CHECKAUPOWER->INEN |= CHECKAUPOWER_IN_On;\
									SV_ulTemp_GPIO = IO_CHECKAUPOWER->PUPDR;\
									SV_ulTemp_GPIO |= CHECKAUPOWER_PULLUP;\
									IO_CHECKAUPOWER->PUPDR = SV_ulTemp_GPIO;}
#define	READ_CHECKAUPOWER			(IO_CHECKAUPOWER->IDR & CHECKAUPOWER_SELECT)
///*右侧磁场检测:开内部上拉*///
#define	SET_MAGNETICRIGHT_INPUT()	{ulong32 SV_ulTemp_GPIO;\
									SV_ulTemp_GPIO = IO_MAGNETICRIGHT->MODER;\
									SV_ulTemp_GPIO &= MAGNETICRIGHT_IN_MODE;\
									IO_MAGNETICRIGHT->MODER = SV_ulTemp_GPIO;\
									IO_MAGNETICRIGHT->INEN |= MAGNETICRIGHT_IN_On;\
									SV_ulTemp_GPIO = IO_MAGNETICRIGHT->PUPDR;\
									SV_ulTemp_GPIO |= MAGNETICRIGHT_PULLUP;\
									IO_MAGNETICRIGHT->PUPDR = SV_ulTemp_GPIO;}
#define	READ_MAGNETICRIGHT			(IO_MAGNETICRIGHT->IDR & MAGNETICRIGHT_SELECT)
///*右上方磁场检测:开内部上拉*///
#define	SET_MAGNETICRIGHTUP_INPUT()	{ulong32 SV_ulTemp_GPIO;\
									SV_ulTemp_GPIO = IO_MAGNETICRIGHTUP->MODER;\
									SV_ulTemp_GPIO &= MAGNETICRIGHTUP_IN_MODE;\
									IO_MAGNETICRIGHTUP->MODER = SV_ulTemp_GPIO;\
									IO_MAGNETICRIGHTUP->INEN |= MAGNETICRIGHTUP_IN_On;\
									SV_ulTemp_GPIO = IO_MAGNETICRIGHTUP->PUPDR;\
									SV_ulTemp_GPIO |= MAGNETICRIGHTUP_PULLUP;\
									IO_MAGNETICRIGHTUP->PUPDR = SV_ulTemp_GPIO;}
#define	READ_MAGNETICRIGHTUP		(IO_MAGNETICRIGHTUP->IDR & MAGNETICRIGHTUP_SELECT)
///*左侧磁场检测:开内部上拉*///
#define	SET_MAGNETICLEFT_INPUT()	{ulong32 SV_ulTemp_GPIO;\
									SV_ulTemp_GPIO = IO_MAGNETICLEFT->MODER;\
									SV_ulTemp_GPIO &= MAGNETICLEFT_IN_MODE;\
									IO_MAGNETICLEFT->MODER = SV_ulTemp_GPIO;\
									IO_MAGNETICLEFT->INEN |= MAGNETICLEFT_IN_On;\
									SV_ulTemp_GPIO = IO_MAGNETICLEFT->PUPDR;\
									SV_ulTemp_GPIO |= MAGNETICLEFT_PULLUP;\
									IO_MAGNETICLEFT->PUPDR = SV_ulTemp_GPIO;}
#define	READ_MAGNETICLEFT			(IO_MAGNETICLEFT->IDR & MAGNETICLEFT_SELECT)
///*左上方磁场检测:开内部上拉*///
#define	SET_MAGNETICLEFTUP_INPUT()	{ulong32 SV_ulTemp_GPIO;\
									SV_ulTemp_GPIO = IO_MAGNETICLEFTUP->MODER;\
									SV_ulTemp_GPIO &= MAGNETICLEFTUP_IN_MODE;\
									IO_MAGNETICLEFTUP->MODER = SV_ulTemp_GPIO;\
									IO_MAGNETICLEFTUP->INEN |= MAGNETICLEFTUP_IN_On;\
									SV_ulTemp_GPIO = IO_MAGNETICLEFTUP->PUPDR;\
									SV_ulTemp_GPIO |= MAGNETICLEFTUP_PULLUP;\
									IO_MAGNETICLEFTUP->PUPDR = SV_ulTemp_GPIO;}
#define	READ_MAGNETICLEFTUP			(IO_MAGNETICLEFTUP->IDR & MAGNETICLEFTUP_SELECT)
///*计量芯片中断请求检测:关内部上拉*///
//#define	SET_EMETERIRQ_INPUT()		{ulong32 SV_ulTemp_GPIO;\
//									SV_ulTemp_GPIO = IO_EMETERIRQ->MODER;\
//									SV_ulTemp_GPIO &= EMETERIRQ_IN_MODE;\
//									IO_EMETERIRQ->MODER = SV_ulTemp_GPIO;\
//									SV_ulTemp_GPIO = IO_EMETERIRQ->PUPDR;\
//									SV_ulTemp_GPIO &= EMETERIRQ_NOPUPD;\
//									IO_EMETERIRQ->PUPDR = SV_ulTemp_GPIO;}
//#define	READ_EMETERIRQ				(IO_EMETERIRQ->IDR & EMETERIRQ_SELECT)
///*继电器状态检测:关内部上拉*///
#define	SET_RELAYSTATUS_INPUT()		{ulong32 SV_ulTemp_GPIO;\
									SV_ulTemp_GPIO = IO_RELAYSTATUS->MODER;\
									SV_ulTemp_GPIO &= RELAYSTATUS_IN_MODE;\
									IO_RELAYSTATUS->MODER = SV_ulTemp_GPIO;\
									IO_RELAYSTATUS->INEN |= RELAYSTATUS_IN_On;\
									SV_ulTemp_GPIO = IO_RELAYSTATUS->PUPDR;\
									SV_ulTemp_GPIO &= RELAYSTATUS_NOPUPD;\
									IO_RELAYSTATUS->PUPDR = SV_ulTemp_GPIO;}
#define	READ_RELAYSTATUS			(IO_RELAYSTATUS->IDR & RELAYSTATUS_SELECT)

///*外置继电器状态检测:关内部上拉*///
#define	SET_EXTERNALRELRELAYSTATUS_INPUT()	{ulong32 SV_ulTemp_GPIO;\
									SV_ulTemp_GPIO = IO_EXTERNALRELAYSTATUS->MODER;\
									SV_ulTemp_GPIO &= EXTERNALRELAYSTATUS_IN_MODE;\
									IO_EXTERNALRELAYSTATUS->MODER = SV_ulTemp_GPIO;\
									IO_EXTERNALRELAYSTATUS->INEN |= EXTERNALRELAYSTATUS_IN_On;\
									SV_ulTemp_GPIO = IO_EXTERNALRELAYSTATUS->PUPDR;\
									SV_ulTemp_GPIO &= EXTERNALRELAYSTATUS_NOPUPD;\
									IO_EXTERNALRELAYSTATUS->PUPDR = SV_ulTemp_GPIO;}
#define	READ_EXTERNALRELAYSTATUS	(IO_EXTERNALRELAYSTATUS->IDR & EXTERNALRELAYSTATUS_SELECT)


///*继电器开启数字率波*///
#define	Switchon_RELAYFILT()		{ulong32 SV_ulTemp_GPIO;\
                                    SV_ulTemp_GPIO = IO_RELAYFILT->IODF;\
									SV_ulTemp_GPIO &= RELAYFILT_Off;\
									SV_ulTemp_GPIO |= RELAYFILT_On;\
									IO_RELAYFILT->IODF = SV_ulTemp_GPIO;}
///*模块发送状态检测:关内部上拉*///
#define	SET_MODULESTATUS_INPUT()	{ulong32 SV_ulTemp_GPIO;\
									SV_ulTemp_GPIO = IO_MODULESTATUS->MODER;\
									SV_ulTemp_GPIO &= MODULESTATUS_IN_MODE;\
									IO_MODULESTATUS->MODER = SV_ulTemp_GPIO;\
									IO_MODULESTATUS->INEN |= MODULESTATUS_IN_On;\
									SV_ulTemp_GPIO = IO_MODULESTATUS->PUPDR;\
									SV_ulTemp_GPIO &= MODULESTATUS_NOPUPD;\
									IO_MODULESTATUS->PUPDR = SV_ulTemp_GPIO;}
#define	READ_MODULESTATUS			(IO_MODULESTATUS->IDR & MODULESTATUS_SELECT)
///*插卡状态检测:关内部上拉*///
#define	SET_CARDSTATUS_INPUT()		{ulong32 SV_ulTemp_GPIO;\
									SV_ulTemp_GPIO = IO_CARDSTATUS->MODER;\
									SV_ulTemp_GPIO &= CARDSTATUS_IN_MODE;\
									IO_CARDSTATUS->MODER = SV_ulTemp_GPIO;\
									IO_CARDSTATUS->INEN |= CARDSTATUS_IN_On;\
									SV_ulTemp_GPIO = IO_CARDSTATUS->PUPDR;\
									SV_ulTemp_GPIO &= CARDSTATUS_NOPUPD;\
									IO_CARDSTATUS->PUPDR = SV_ulTemp_GPIO;}
#define	READ_CARDSTATUS				(IO_CARDSTATUS->IDR & CARDSTATUS_SELECT)
///*****************************************************************************************///


///*****************************************************************************************///
///*背光灯:口线推挽输出*///
#define	SET_BACKLIGHT_OUTPUT()	{ulong32 SV_ulTemp_GPIO;\
								SV_ulTemp_GPIO = IO_BACKLIGHT->MODER;\
								SV_ulTemp_GPIO &= BACKLIGHT_IN_MODE;\
								SV_ulTemp_GPIO |= BACKLIGHT_OUT_MODE;\
								IO_BACKLIGHT->MODER = SV_ulTemp_GPIO;\
								SV_ulTemp_GPIO = IO_BACKLIGHT->OTYPER;\
								SV_ulTemp_GPIO &= BACKLIGHT_OUTPUT_PP;\
								IO_BACKLIGHT->OTYPER = SV_ulTemp_GPIO;}
//#define	SET_BACKLIGHT_INPUT()	{ulong32 SV_ulTemp_GPIO;\
//								SV_ulTemp_GPIO = IO_BACKLIGHT->MODER;\
//								SV_ulTemp_GPIO &= BACKLIGHT_IN_MODE;\
//								IO_BACKLIGHT->MODER = SV_ulTemp_GPIO;\
//								IO_BACKLIGHT->INEN |= BACKLIGHT_IN_On;\	
//								SV_ulTemp_GPIO = IO_BACKLIGHT->PUPDR;\
//								SV_ulTemp_GPIO &= BACKLIGHT_NOPUPD;\
//								IO_BACKLIGHT->PUPDR = SV_ulTemp_GPIO;}
#define	SwitchOn_BackLight()	{IO_BACKLIGHT->BSETH = BACKLIGHTSET;\
								SET_BACKLIGHT_OUTPUT();\
								IO_BACKLIGHT->BSETH = BACKLIGHTSET;}
#define	SwitchOff_BackLight()	{IO_BACKLIGHT->BSRR = BACKLIGHTRESET;\
								SET_BACKLIGHT_OUTPUT();\
								IO_BACKLIGHT->BSRR = BACKLIGHTRESET;}
///*拉闸指示灯:口线开漏输出*///
#define	SET_TRIPLED_OUTPUT()	{ulong32 SV_ulTemp_GPIO;\
								SV_ulTemp_GPIO = IO_TRIPLED->MODER;\
								SV_ulTemp_GPIO &= TRIPLED_IN_MODE;\
								SV_ulTemp_GPIO |= TRIPLED_OUT_MODE;\
								IO_TRIPLED->MODER = SV_ulTemp_GPIO;\
								SV_ulTemp_GPIO = IO_TRIPLED->OTYPER;\
								SV_ulTemp_GPIO |= TRIPLED_OUTPUT_OD;\
								IO_TRIPLED->OTYPER = SV_ulTemp_GPIO;}

#define	SwitchOn_TripLed()		{IO_TRIPLED->BSRR = TRIPLEDRESET;\
								SET_TRIPLED_OUTPUT();\
								IO_TRIPLED->BSRR = TRIPLEDRESET;}
#define	SwitchOff_TripLed()		{IO_TRIPLED->BSETH = TRIPLEDSET;\
								SET_TRIPLED_OUTPUT();\
								IO_TRIPLED->BSETH = TRIPLEDSET;}
///*蜂鸣器:口线推挽输出*///
#define	SET_BEEP_OUTPUT()		{ulong32 SV_ulTemp_GPIO;\
								SV_ulTemp_GPIO = IO_BEEP->MODER;\
								SV_ulTemp_GPIO &= BEEP_IN_MODE;\
								SV_ulTemp_GPIO |= BEEP_OUT_MODE;\
								IO_BEEP->MODER = SV_ulTemp_GPIO;\
								SV_ulTemp_GPIO = IO_BEEP->OTYPER;\
								SV_ulTemp_GPIO &= BEEP_OUTPUT_PP;\
								IO_BEEP->OTYPER = SV_ulTemp_GPIO;}

#define	SwitchOn_Beep()			{IO_BEEP->BSETH = BEEPSET;\
								SET_BEEP_OUTPUT();\
								IO_BEEP->BSETH = BEEPSET;}
#define	SwitchOff_Beep()		{IO_BEEP->BSRR = BEEPRESET;\
								SET_BEEP_OUTPUT();\
								IO_BEEP->BSRR = BEEPRESET;}
#define	Switch_ReversePhaseBeeper()	(IO_BEEP->ODR ^= BEEP_SELECT)
///*报警继电器输出:口线推挽输出*///
#define	SET_WARNOUT_OUTPUT()	{ulong32 SV_ulTemp_GPIO;\
								SV_ulTemp_GPIO = IO_WARNOUT->MODER;\
								SV_ulTemp_GPIO &= WARNOUT_IN_MODE;\
								SV_ulTemp_GPIO |= WARNOUT_OUT_MODE;\
								IO_WARNOUT->MODER = SV_ulTemp_GPIO;\
								SV_ulTemp_GPIO = IO_WARNOUT->OTYPER;\
								SV_ulTemp_GPIO &= WARNOUT_OUTPUT_PP;\
								IO_WARNOUT->OTYPER = SV_ulTemp_GPIO;}

#define	SwitchOn_WarnOut()		{IO_WARNOUT->BSETH = WARNOUTSET;\
								SET_WARNOUT_OUTPUT();\
								IO_WARNOUT->BSETH = WARNOUTSET;}
#define	SwitchOff_WarnOut()		{IO_WARNOUT->BSRR = WARNOUTRESET;\
								SET_WARNOUT_OUTPUT();\
								IO_WARNOUT->BSRR = WARNOUTRESET;}
///*秒脉冲:配置为多功能口，开漏输出*///
#define	SET_SECOND_OUTPUT()		{GPIO->FOUTSEL = GPIO_FOUTSEL_RTCTM;\
								ulong32 SV_ulTemp_GPIO;\
								SV_ulTemp_GPIO = IO_MCUSECOND->MODER;\
								SV_ulTemp_GPIO &= MCUSECOND_IN_MODE;\
								SV_ulTemp_GPIO |= MCUSECOND_SELECT_AF;\
								IO_MCUSECOND->MODER = SV_ulTemp_GPIO;\
								IO_MCUSECOND->INEN &= MCUSECOND_IN_Off;\
								SV_ulTemp_GPIO = IO_MCUSECOND->OTYPER;\
								SV_ulTemp_GPIO |= MCUSECOND_OUTPUT_OD;\
								IO_MCUSECOND->OTYPER = SV_ulTemp_GPIO;\
								GPIO->FOUTSEL = GPIO_FOUTSEL_RTCTM;}

///*需量周期/时段投切脉冲:普通IO，口线开漏输出*///
#define	SET_DEMANDCYCLE_OUTPUT()	{ulong32 SV_ulTemp_GPIO;\
									SV_ulTemp_GPIO = IO_MCUSECOND->MODER;\
									SV_ulTemp_GPIO &= MCUSECOND_IN_MODE;\
									SV_ulTemp_GPIO |= MCUSECOND_OUT_MODE;\
									IO_MCUSECOND->MODER = SV_ulTemp_GPIO;\
									SV_ulTemp_GPIO = IO_MCUSECOND->OTYPER;\
									SV_ulTemp_GPIO |= MCUSECOND_OUTPUT_OD;\
									IO_MCUSECOND->OTYPER = SV_ulTemp_GPIO;}
#define	SET_DEMANDCYCLE_INPUT()		{ulong32 SV_ulTemp_GPIO;\
									SV_ulTemp_GPIO = IO_MCUSECOND->MODER;\
									SV_ulTemp_GPIO &= MCUSECOND_IN_MODE;\
									IO_MCUSECOND->MODER = SV_ulTemp_GPIO;\
									IO_MCUSECOND->INEN |= MCUSECOND_IN_On;\
									SV_ulTemp_GPIO = IO_MCUSECOND->PUPDR;\
									SV_ulTemp_GPIO &= MCUSECOND_NOPUPD;\
									IO_MCUSECOND->PUPDR = SV_ulTemp_GPIO;}

#define	Select_SecondPulseOut()		{IO_MCUSECOND->BSETH = MCUSECONDSET;\
				 					SET_SECOND_OUTPUT();\
				 					IO_MCUSECOND->BSETH = MCUSECONDSET;}
#define	Select_DemandPulseOut()		{IO_MCUSECOND->BSETH = MCUSECONDSET;\
				 					SET_DEMANDCYCLE_OUTPUT();\
				 					IO_MCUSECOND->BSETH = MCUSECONDSET;}
#define	Select_RatePulseOut()		{IO_MCUSECOND->BSETH = MCUSECONDSET;\
				 					SET_DEMANDCYCLE_OUTPUT();\
				 					IO_MCUSECOND->BSETH = MCUSECONDSET;}
///********关闭多功能输出，设置为秒脉冲输出*******///				 					
//#define	Close_MultiFunctionOut()	{IO_MCUSECOND->BSETH = MCUSECONDSET;\
//				 					SET_SECOND_OUTPUT();\
//				 					IO_MCUSECOND->BSETH = MCUSECONDSET;}
#define	Close_MultiFunctionOut()	{IO_MCUSECOND->BSETH = MCUSECONDSET;\
				 					IO_MCUSECOND->BSETH = MCUSECONDSET;}
#define	MultiFunction_OutputSecondPulse()	{IO_MCUSECOND->BSETH = MCUSECONDSET;\
				 							SET_SECOND_OUTPUT();\
				 							IO_MCUSECOND->BSETH = MCUSECONDSET;}
#define	MultiFunction_OutputDemandPulse()	{SET_DEMANDCYCLE_OUTPUT();\
				 							IO_MCUSECOND->BSRR = MCUSECONDRESET;\
				 							SET_DEMANDCYCLE_OUTPUT();}
#define	MultiFunction_OutputRatePulse()		{SET_DEMANDCYCLE_OUTPUT();\
				 							IO_MCUSECOND->BSRR = MCUSECONDRESET;\
				 							SET_DEMANDCYCLE_OUTPUT();}


///*计量芯片复位控制:口线输入(外部有上/下拉电阻)*///
///*90E36与7022E处理方式不同:全失压处理后,90E36的PM0和PM1输出由11改为输出00
///*7022E没有PM0和PM1两个计量方式控制线
#define	MeterIC_Reset()				{ulong32 SV_ulTemp_GPIO;\
									SV_ulTemp_GPIO = IO_EMETERRST->MODER;\
									SV_ulTemp_GPIO &= EMETERRST_IN_MODE;\
									IO_EMETERRST->MODER = SV_ulTemp_GPIO;\
									IO_EMETERRST->INEN |= EMETERRST_INOn;\
									SV_ulTemp_GPIO = IO_EMETERRST->PUPDR;\
									SV_ulTemp_GPIO &= EMETERRST_NOPUPD;\
									IO_EMETERRST->PUPDR = SV_ulTemp_GPIO;}

///*计量芯片电源控制:口线开漏输出*///
#define	SET_EMETERPOWER_OUTPUT()	{ulong32 SV_ulTemp_GPIO;\
									SV_ulTemp_GPIO = IO_EMETERPOWER->MODER;\
									SV_ulTemp_GPIO &= EMETERPOWER_IN_MODE;\
									SV_ulTemp_GPIO |= EMETERPOWER_OUT_MODE;\
									IO_EMETERPOWER->MODER = SV_ulTemp_GPIO;\
									SV_ulTemp_GPIO = IO_EMETERPOWER->OTYPER;\
									SV_ulTemp_GPIO |= EMETERPOWER_OUTPUT_OD;\
									IO_EMETERPOWER->OTYPER = SV_ulTemp_GPIO;}

#define	SwitchOff_MeterICPower()		{IO_EMETERPOWER->BSETH = EMETERPOWERSET;\
									SET_EMETERPOWER_OUTPUT();\
									IO_EMETERPOWER->BSETH = EMETERPOWERSET;}
#define	SwitchOn_MeterICPower()	{IO_EMETERPOWER->BSRR = EMETERPOWERRESET;\
									SET_EMETERPOWER_OUTPUT();\
									IO_EMETERPOWER->BSRR = EMETERPOWERRESET;}
///*红外发射及Flash电源控制:口线开漏输出*///
#define	SET_FLASHPOWER_OUTPUT()		{ulong32 SV_ulTemp_GPIO;\
									SV_ulTemp_GPIO = IO_FLASHPOWER->MODER;\
									SV_ulTemp_GPIO &= FLASHPOWER_IN_MODE;\
									SV_ulTemp_GPIO |= FLASHPOWER_OUT_MODE;\
									IO_FLASHPOWER->MODER = SV_ulTemp_GPIO;\
									SV_ulTemp_GPIO = IO_FLASHPOWER->OTYPER;\
									SV_ulTemp_GPIO |= FLASHPOWER_OUTPUT_OD;\
									IO_FLASHPOWER->OTYPER = SV_ulTemp_GPIO;}

#define	SwitchOff_FlashPower()		{IO_FLASHPOWER->BSETH = FLASHPOWERSET;\
									SET_FLASHPOWER_OUTPUT();\
									IO_FLASHPOWER->BSETH = FLASHPOWERSET;}
#define	SwitchOn_FlashPower()		{IO_FLASHPOWER->BSRR = FLASHPOWERRESET;\
									SET_FLASHPOWER_OUTPUT();\
									IO_FLASHPOWER->BSRR = FLASHPOWERRESET;}
///*超级电容充电控制:口线推挽输出*///
#define	SET_CAPCHARGE_OUTPUT()		{ulong32 SV_ulTemp_GPIO;\
									SV_ulTemp_GPIO = IO_CAPCHARGE->MODER;\
									SV_ulTemp_GPIO &= CAPCHARGE_IN_MODE;\
									SV_ulTemp_GPIO |= CAPCHARGE_OUT_MODE;\
									IO_CAPCHARGE->MODER = SV_ulTemp_GPIO;\
									SV_ulTemp_GPIO = IO_CAPCHARGE->OTYPER;\
									SV_ulTemp_GPIO &= CAPCHARGE_OUTPUT_PP;\
									IO_CAPCHARGE->OTYPER = SV_ulTemp_GPIO;}

#define	SuperCapCharge_En()			{IO_CAPCHARGE->BSETH = CAPCHARGESET;\
									SET_CAPCHARGE_OUTPUT();\
									IO_CAPCHARGE->BSETH = CAPCHARGESET;}
#define	SuperCapCharge_Dis()		{IO_CAPCHARGE->BSRR = CAPCHARGERESET;\
									SET_CAPCHARGE_OUTPUT();\
									IO_CAPCHARGE->BSRR = CAPCHARGERESET;}
///*超级电容放电控制:口线推挽输出*///
#define	SET_CAPDISCHARGE_OUTPUT()	{ulong32 SV_ulTemp_GPIO;\
									SV_ulTemp_GPIO = IO_CAPDISCHARGE->MODER;\
									SV_ulTemp_GPIO &= CAPDISCHARGE_IN_MODE;\
									SV_ulTemp_GPIO |= CAPDISCHARGE_OUT_MODE;\
									IO_CAPDISCHARGE->MODER = SV_ulTemp_GPIO;\
									SV_ulTemp_GPIO = IO_CAPDISCHARGE->OTYPER;\
									SV_ulTemp_GPIO &= CAPDISCHARGE_OUTPUT_PP;\
									IO_CAPDISCHARGE->OTYPER = SV_ulTemp_GPIO;}

#define	SwitchOn_SuperCapPower()	{IO_CAPDISCHARGE->BSETH = CAPDISCHARGESET;\
									SET_CAPDISCHARGE_OUTPUT();\
									IO_CAPDISCHARGE->BSETH = CAPDISCHARGESET;}
#define	SwitchOff_SuperCapPower()	{IO_CAPDISCHARGE->BSRR = CAPDISCHARGERESET;\
									SET_CAPDISCHARGE_OUTPUT();\
									IO_CAPDISCHARGE->BSRR = CAPDISCHARGERESET;}
/*6V电池电源控制:口线推挽输出*/
#define	SET_BATTPOWER_OUTPUT()		{ulong32 SV_ulTemp_GPIO;\
									SV_ulTemp_GPIO  = IO_BATTPOWER->MODER;\
									SV_ulTemp_GPIO &= BATTPOWER_IN_MODE;\
									SV_ulTemp_GPIO |= BATTPOWER_OUT_MODE;\
									IO_BATTPOWER->MODER = SV_ulTemp_GPIO;\
									SV_ulTemp_GPIO  = IO_BATTPOWER->OTYPER;\
									SV_ulTemp_GPIO &= BATTPOWER_OUTPUT_PP;\
									IO_BATTPOWER->OTYPER = SV_ulTemp_GPIO;}

#define	SwitchOn_WakeUpPower()		{IO_BATTPOWER->BSETH = BATTPOWERSET;\
									SET_BATTPOWER_OUTPUT();\
									IO_BATTPOWER->BSETH = BATTPOWERSET;}
#define	SwitchOff_WakeUpPower()		{IO_BATTPOWER->BSRR = BATTPOWERRESET;\
									SET_BATTPOWER_OUTPUT();\
									IO_BATTPOWER->BSRR = BATTPOWERRESET;}

/*6V电池电源控制:开漏输出高*/
#define	SET_BATTPOWERNOBATTER_OUTPUT()		{ulong32 SV_ulTemp_GPIO;\
									        SV_ulTemp_GPIO  = IO_BATTPOWER->MODER;\
									        SV_ulTemp_GPIO &= BATTPOWER_IN_MODE;\
									        SV_ulTemp_GPIO |= BATTPOWER_OUT_MODE;\
									        IO_BATTPOWER->MODER = SV_ulTemp_GPIO;\
									        SV_ulTemp_GPIO  = IO_BATTPOWER->OTYPER;\
									        SV_ulTemp_GPIO |= BATTPOWER_OUTPUT_OD;\
									        IO_BATTPOWER->OTYPER = SV_ulTemp_GPIO;}

#define	SwitchOn_WakeUpPower_NoBatter()		{IO_BATTPOWER->BSETH = BATTPOWERSET;\
                                            SET_BATTPOWERNOBATTER_OUTPUT();\
                                            IO_BATTPOWER->BSETH = BATTPOWERSET;}
#define	SwitchOff_WakeUpPower_NoBatter()	{IO_BATTPOWER->BSRR = BATTPOWERRESET;\
                                            SET_BATTPOWERNOBATTER_OUTPUT();\
                                            IO_BATTPOWER->BSRR = BATTPOWERRESET;}


///*6V电池放电控制：防止电池钝化:口线推挽输出*///
//#define	SET_BATTDISCHARGE_OUTPUT()	{ulong32 SV_ulTemp_GPIO;\
//									SV_ulTemp_GPIO = IO_BATTDISCHARGE->MODER;\
//									SV_ulTemp_GPIO &= BATTDISCHARGE_IN_MODE;\
//									SV_ulTemp_GPIO |= BATTDISCHARGE_OUT_MODE;\
//									IO_BATTDISCHARGE->MODER = SV_ulTemp_GPIO;\
//									SV_ulTemp_GPIO = IO_BATTDISCHARGE->OTYPER;\
//									SV_ulTemp_GPIO &= BATTDISCHARGE_OUTPUT_PP;\
//									IO_BATTDISCHARGE->OTYPER = SV_ulTemp_GPIO;\
//									SV_ulTemp_GPIO = IO_BATTDISCHARGE->OSPEEDR;\
//									SV_ulTemp_GPIO &= BATTDISCHARGE_SPEED_INIT;\
//									SV_ulTemp_GPIO |= BATTDISCHARGE_SPEED_2MHZ;\
//									IO_BATTDISCHARGE->OSPEEDR = SV_ulTemp_GPIO;}
//#define	SET_BATTDISCHARGE_INPUT()	{ulong32 SV_ulTemp_GPIO;\
//									SV_ulTemp_GPIO = IO_BATTDISCHARGE->MODER;\
//									SV_ulTemp_GPIO &= BATTDISCHARGE_IN_MODE;\
//									IO_BATTDISCHARGE->MODER = SV_ulTemp_GPIO;\
//									SV_ulTemp_GPIO = IO_BATTDISCHARGE->PUPDR;\
//									SV_ulTemp_GPIO &= BATTDISCHARGE_NOPUPD;\
//									IO_BATTDISCHARGE->PUPDR = SV_ulTemp_GPIO;}
//#define	SwitchOn_PreventBlunt()		{IO_BATTDISCHARGE->BSRR = BATTDISCHARGESET;\
//									SET_BATTDISCHARGE_OUTPUT();\
//									IO_BATTDISCHARGE->BSRR = BATTDISCHARGESET;}
//#define	SwitchOff_PreventBlunt()	{IO_BATTDISCHARGE->BSRR = BATTDISCHARGERESET;\
//									SET_BATTDISCHARGE_OUTPUT();\
//									IO_BATTDISCHARGE->BSRR = BATTDISCHARGERESET;}
///*外置负荷开关控制:口线推挽输出*///
#define	SET_EXTERNALRELAY_OUTPUT()	{ulong32 SV_ulTemp_GPIO;\
									SV_ulTemp_GPIO = IO_EXTERNALRELAY->MODER;\
									SV_ulTemp_GPIO &= EXTERNALRELAY_IN_MODE;\
									SV_ulTemp_GPIO |= EXTERNALRELAY_OUT_MODE;\
									IO_EXTERNALRELAY->MODER = SV_ulTemp_GPIO;\
									SV_ulTemp_GPIO = IO_EXTERNALRELAY->OTYPER;\
									SV_ulTemp_GPIO &= EXTERNALRELAY_OUTPUT_PP;\
									IO_EXTERNALRELAY->OTYPER = SV_ulTemp_GPIO;}
#define	SwitchOff_ExternalRelay()	{IO_EXTERNALRELAY->BSETH = EXTERNALRELAYSET;\
									SET_EXTERNALRELAY_OUTPUT();\
									IO_EXTERNALRELAY->BSETH = EXTERNALRELAYSET;}
#define	SwitchOn_ExternalRelay()	{IO_EXTERNALRELAY->BSRR = EXTERNALRELAYRESET;\
									SET_EXTERNALRELAY_OUTPUT();\
									IO_EXTERNALRELAY->BSRR = EXTERNALRELAYRESET;}
///*内置负荷开关控制:A:口线推挽输出*///
#define	SET_RELAYA_OUTPUT()		{ulong32 SV_ulTemp_GPIO;\
								SV_ulTemp_GPIO = IO_RELAYA->MODER;\
								SV_ulTemp_GPIO &= RELAYA_IN_MODE;\
								SV_ulTemp_GPIO |= RELAYA_OUT_MODE;\
								IO_RELAYA->MODER = SV_ulTemp_GPIO;\
								SV_ulTemp_GPIO = IO_RELAYA->OTYPER;\
								SV_ulTemp_GPIO &= RELAYA_OUTPUT_PP;\
								IO_RELAYA->OTYPER = SV_ulTemp_GPIO;}
///*内置负荷开关控制:B:口线推挽输出*///
#define	SET_RELAYB_OUTPUT()		{ulong32 SV_ulTemp_GPIO;\
								SV_ulTemp_GPIO = IO_RELAYB->MODER;\
								SV_ulTemp_GPIO &= RELAYB_IN_MODE;\
								SV_ulTemp_GPIO |= RELAYB_OUT_MODE;\
								IO_RELAYB->MODER = SV_ulTemp_GPIO;\
								SV_ulTemp_GPIO = IO_RELAYB->OTYPER;\
								SV_ulTemp_GPIO &= RELAYB_OUTPUT_PP;\
								IO_RELAYB->OTYPER = SV_ulTemp_GPIO;}
#define	SwitchOn_InternalRelay()	{	IO_RELAYB->BSRR = RELAYBRESET;\
									SET_RELAYB_OUTPUT();\
									IO_RELAYB->BSRR = RELAYBRESET;\
									IO_RELAYA->BSETH = RELAYASET;\
									SET_RELAYA_OUTPUT();\
									IO_RELAYA->BSETH = RELAYASET;}
#define	SwitchOff_InternalRelay()	{IO_RELAYA->BSRR = RELAYARESET;\
									SET_RELAYA_OUTPUT();\
									IO_RELAYA->BSRR = RELAYARESET;\
									IO_RELAYB->BSETH = RELAYBSET;\
									SET_RELAYB_OUTPUT();\
									IO_RELAYB->BSETH = RELAYBSET;}
#define	Hold_InternalRelay()		{IO_RELAYA->BSRR = RELAYARESET;\
									IO_RELAYB->BSRR = RELAYBRESET;\
									SET_RELAYA_OUTPUT();\
									SET_RELAYB_OUTPUT();\
									IO_RELAYA->BSRR = RELAYARESET;\
									IO_RELAYB->BSRR = RELAYBRESET;}
///*主动上报:口线开漏输出*///
#define	SET_EVENTOUT_OUTPUT()		{ulong32 SV_ulTemp_GPIO;\
									SV_ulTemp_GPIO = IO_EVENTOUT->MODER;\
									SV_ulTemp_GPIO &= EVENTOUT_IN_MODE;\
									SV_ulTemp_GPIO |= EVENTOUT_OUT_MODE;\
									IO_EVENTOUT->MODER = SV_ulTemp_GPIO;\
									SV_ulTemp_GPIO = IO_EVENTOUT->OTYPER;\
									SV_ulTemp_GPIO |= EVENTOUT_OUTPUT_OD;\
									IO_EVENTOUT->OTYPER = SV_ulTemp_GPIO;}

#define	EventOut_EN()				{IO_EVENTOUT->BSETH = EVENTOUTSET;\
									SET_EVENTOUT_OUTPUT();\
									IO_EVENTOUT->BSETH = EVENTOUTSET;}
#define	EventOut_DIS()				{IO_EVENTOUT->BSRR = EVENTOUTRESET;\
									SET_EVENTOUT_OUTPUT();\
									IO_EVENTOUT->BSRR = EVENTOUTRESET;}
///*模块设置:口线开漏输出*///
#define	SET_MODULESET_OUTPUT()		{ulong32 SV_ulTemp_GPIO;\
									SV_ulTemp_GPIO = IO_MODULESET->MODER;\
									SV_ulTemp_GPIO &= MODULESET_IN_MODE;\
									SV_ulTemp_GPIO |= MODULESET_OUT_MODE;\
									IO_MODULESET->MODER = SV_ulTemp_GPIO;\
									SV_ulTemp_GPIO = IO_MODULESET->OTYPER;\
									SV_ulTemp_GPIO |= MODULESET_OUTPUT_OD;\
									IO_MODULESET->OTYPER = SV_ulTemp_GPIO;}

#define	ModuleSet_EN()				{IO_MODULESET->BSRR = MODULESETRESET;\
									SET_MODULESET_OUTPUT();\
									IO_MODULESET->BSRR = MODULESETRESET;}
#define	ModuleSet_DIS()				{IO_MODULESET->BSETH = MODULESETSET;\
									SET_MODULESET_OUTPUT();\
									IO_MODULESET->BSETH = MODULESETSET;}
///*模块复位:口线开漏输出*///
#define	SET_MODULERESET_OUTPUT()	{ulong32 SV_ulTemp_GPIO;\
									SV_ulTemp_GPIO = IO_MODULERESET->MODER;\
									SV_ulTemp_GPIO &= MODULERESET_IN_MODE;\
									SV_ulTemp_GPIO |= MODULERESET_OUT_MODE;\
									IO_MODULERESET->MODER = SV_ulTemp_GPIO;\
									SV_ulTemp_GPIO = IO_MODULERESET->OTYPER;\
									SV_ulTemp_GPIO |= MODULERESET_OUTPUT_OD;\
									IO_MODULERESET->OTYPER = SV_ulTemp_GPIO;}

#define	Module_EN()					{IO_MODULERESET->BSETH = MODULERESETSET;\
									SET_MODULERESET_OUTPUT();\
									IO_MODULERESET->BSETH = MODULERESETSET;}
#define	Module_Reset()				{IO_MODULERESET->BSRR = MODULERESETRESET;\
									SET_MODULERESET_OUTPUT();\
									IO_MODULERESET->BSRR = MODULERESETRESET;}
///*lcd低功耗电源控制:口线推挽输出*///
#define	SET_LCDPower_OUTPUT()	{ulong32 SV_ulTemp_GPIO;\
								SV_ulTemp_GPIO = IO_LCDPOWER->MODER;\
								SV_ulTemp_GPIO &= LCDPOWER_IN_MODE;\
								SV_ulTemp_GPIO |= LCDPOWER_OUT_MODE;\
								IO_LCDPOWER->MODER = SV_ulTemp_GPIO;\
								SV_ulTemp_GPIO = IO_LCDPOWER->OTYPER;\
								SV_ulTemp_GPIO &= LCDPOWER_OUTPUT_PP;\
								IO_LCDPOWER->OTYPER = SV_ulTemp_GPIO;}								
//#define	SET_LCDPOWER_INPUT()		{IO_LCDPOWER->IOCFG&=LCDPOWER_SELECT;\
//								IO_LCDPOWER->MODER &= LCDPOWER_IN_MODE;\
//								IO_LCDPOWER->PUPDR |= LCDPOWER_NOPUPD;}
								
#define	SwitchOn_LCDPower()		{IO_LCDPOWER->BSETH = LCDPOWERSET;\
									SET_LCDPower_OUTPUT();\
									IO_LCDPOWER->BSETH = LCDPOWERSET;}
#define	SwitchOff_LCDPower()		{IO_LCDPOWER->BSRR = LCDPOWERRESET;\
									SET_LCDPower_OUTPUT();\
									IO_LCDPOWER->BSRR = LCDPOWERRESET;}

///*红外接收电源:口线开漏输出*///
#define	SET_INFRARXPOWER_OUTPUT()	{ulong32 SV_ulTemp_GPIO;\
									SV_ulTemp_GPIO = IO_INFRARXPOWER->MODER;\
									SV_ulTemp_GPIO &= INFRARXPOWER_IN_MODE;\
									SV_ulTemp_GPIO |= INFRARXPOWER_OUT_MODE;\
									IO_INFRARXPOWER->MODER = SV_ulTemp_GPIO;\
									SV_ulTemp_GPIO = IO_INFRARXPOWER->OTYPER;\
									SV_ulTemp_GPIO |= INFRARXPOWER_OUTPUT_OD;\
									IO_INFRARXPOWER->OTYPER = SV_ulTemp_GPIO;}
#define	SwitchOff_InfrarxPower()		{IO_INFRARXPOWER->BSETH = INFRARXPOWERSET;\
									SET_INFRARXPOWER_OUTPUT();\
									IO_INFRARXPOWER->BSETH = INFRARXPOWERSET;}
#define	SwitchOn_InfrarxPower()	{IO_INFRARXPOWER->BSRR = INFRARXPOWERRESET;\
									SET_INFRARXPOWER_OUTPUT();\
									IO_INFRARXPOWER->BSRR = INFRARXPOWERRESET;}
///*****************************************************************************************///
///*停电唤醒时需要看6V电池有没有，将口线配置为输入*///
#define Set_WakeupBatt_Input()			{ulong32 SV_ulTemp_GPIO;\
										SV_ulTemp_GPIO = IO_WAKEBATT->MODER;\
										SV_ulTemp_GPIO &= WAKEBATT_IN_MODE;\
										IO_WAKEBATT->MODER = SV_ulTemp_GPIO;\
										IO_WAKEBATT->INEN |= WAKEBATT_IN_On;\
										SV_ulTemp_GPIO = IO_WAKEBATT->PUPDR;\
										SV_ulTemp_GPIO &= WAKEBATT_NOPUPD;\
										IO_WAKEBATT->PUPDR = SV_ulTemp_GPIO;}

#define	Read_WakeupBatt()				(IO_WAKEBATT->IDR & WAKEBATT_SELECT)
///*****************************************************************************************///
///*停电唤醒时需要看有没有来电，将口线配置为输入*///
#define Set_PowerDown_Input()			{ulong32 SV_ulTemp_GPIO;\
										SV_ulTemp_GPIO = IO_POWERDOWN->MODER;\
										SV_ulTemp_GPIO &= POWERDOWN_IN_MODE;\
										IO_POWERDOWN->MODER = SV_ulTemp_GPIO;\
										IO_POWERDOWN->INEN |= POWERDOWN_INOn;\
										SV_ulTemp_GPIO = IO_POWERDOWN->PUPDR;\
										SV_ulTemp_GPIO &= POWERDOWN_NOPUPD;\
										IO_POWERDOWN->PUPDR = SV_ulTemp_GPIO;}

										

extern uchar8 DF_GetIOStatus(uchar8 Peripheral);
extern void DF_InternalRelayHold(void);
extern uchar8 DF_RelayControl(uchar8 C_Act);
extern void DF_MultiFunction_SelectSecondPulse(void);
extern void DF_MultiFunction_SelectDemandPulse(void);
extern void DF_MultiFunction_SelectRatePulse(void);
extern void DF_MultiFunction_Close(void);
extern void DF_MultiFunction_OutputSecondPulse(void);
extern void DF_MultiFunction_OutputDemandPulse(void);
extern void DF_MultiFunction_OutputDemandPulse(void);
extern void DF_Switch_PreventBlunt(uchar8 Act);
extern void DF_SwitchOn_EMeterIcPower(void);
extern void DF_SwitchOff_EMeterIcPower(void);
extern void DF_SwitchOn_FlashPower(void);
extern void DF_SwitchOff_FlashPower(void);
extern void DF_SwitchOn_SuperCapCharge(void);
extern void DF_SwitchOff_SuperCapCharge(void);
extern void DF_SwitchOn_SuperCapPower(void);
extern void DF_SwitchOff_SuperCapPower(void);
extern void DF_SwitchOn_PreventBlunt(void);
extern void DF_SwitchOff_PreventBlunt(void);
extern void DF_SwitchOn_WakeUpPower(void);
extern void DF_SwitchOff_WakeUpPower(void);
extern void DF_SwitchOn_WakeUpPower_NoBatter(void);
extern void DF_SwitchOff_WakeUpPower_NoBatter(void);
extern void DF_SwitchOn_EventOut(void);
extern void DF_SwitchOff_EventOut(void);
extern void DF_SwitchOn_ModuleSet(void);
extern void DF_SwitchOff_ModuleSet(void);
extern void DF_SwitchOn_ModuleEn(void);
extern void DF_SwitchOff_ModuleEn(void);
extern void DF_SwitchOn_InfrarxPower(void);
extern void DF_SwitchOff_InfrarxPower(void);
extern uchar8 DF_GetIOStatus_MainPower(void);
extern void DF_SwitchOff_TripLed(void);
extern void DF_SwitchOn_Beeper(void);
extern void DF_SwitchOff_Beeper(void);
extern void DF_ReversePhase_Beeper(void);
extern void InF_JTagEnable( void );
extern void DF_ConfigPowerDownInterrupt( void );
extern void DF_SwitchOn_LCDPower( void );
extern void DF_SwitchOff_LCDPower( void );






#endif




