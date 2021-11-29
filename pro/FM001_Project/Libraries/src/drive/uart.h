
///*****************************************************************************************///
///*Copyright£º    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     uart.h
///*Version:       V1
///*Date:          2014-3-12
///*Description:   
///*Function List: 
///*****************************************************************************************///
#ifndef __UART_H
#define __UART_H

#include "Public.h"

#define	C_Uart_Parse		0x68			///*Uart½âÎöÏûÏ¢*///
#define	C_Uart_Init			0x68			///*Uart³õÊ¼»¯ÏûÏ¢*///
#define	C_Uart_Normal		0x00			///*Uart´¦ÓÚ³£Ì¬*///
#define	C_Uart_Init_TEST 	0x88
//#define C_MeterType_Module	0x02			///*Ä£¿é±í*///

#define	C_Uart_OverTime		10				///*´®¿Ú³¬Ê±¶¨Ê±Æ÷Öµ£¬ÒÔ0.5sÎªµ¥Î»¼ÆÊ±*///



//static	ulong32	SV_ulTemp_UART;

///*****************************************************************************************///
///*****************************************************************************************///
///*****************************************************************************************///
///*****************************************************************************************///

///*****************************************************************************************///
//#define		C_bps_38400					0x80
//#define		C_bps_19200					0x40
//#define		C_bps_9600					0x20
//#define		C_bps_4800					0x10
//#define		C_bps_2400					0x08
//#define		C_bps_1200					0x04
//#define		C_bps_600					0x02
//#define		C_bps_300					0x01
//
//#define		C_CommDataLen7				0x07///*word lenth*///
//#define		C_CommDataLen8				0x08
//
//#define		C_parity_None				0x00///*no parity*///
//#define		C_parity_Even				0x02///*even parity*///
//#define		C_parity_Odd				0x01///*odd parity*///
//
//#define		C_SerStp_1					0x01///*stop bit*///
//#define		C_SerStp_2					0x02
///*****************************************************************************************///
///*baud rate:fpclk=16MHz*///
///*baud rate=fpclk/(aaa + 1):0xaaab*///
#define	USART_bps_38400				(416)
#define	USART_bps_19200				(832)
#define	USART_bps_9600				(1666)
#define	USART_bps_4800				(3332)
#define	USART_bps_2400				(6666)
#define	USART_bps_1200				(13332)
#define	USART_bps_600					(26665)
#define	USART_bps_300					(53332)

#define	USART_bps_1200_Wakeup		(6666)

#define	ESAM_bps					((ulong32)0x000005d0)	///*ESAMµÄ1etu=93us*///
///*****************************************************************************************///
#define	USART_SR_RESET				((ulong32)0x00000000)
///*****************************************************************************************///
#define	USART_CR1_RESET				((ulong32)0x00000000)
///* overSampling *///
#define USART_OVER8_Reset			((ulong32)0x00007fff)	///* oversampling by 16 *///
#define USART_OVER8_Set				((ulong32)0x00008000)	///* oversampling by 8 *///
///* usart en/dis *///
#define USART_USART_EN				((ulong32)0x00002000)	///* USART Enable *///
#define USART_USART_DIS				((ulong32)0x0000dfff)	///* USART Disable *///

#define	USART_WordLength_8b			((ulong32)0x00000000)	///*word lenth,include parity,at usart->cr1.12*///
#define	USART_WordLength_8bEven		((ulong32)0x00000040)	///*word lenth,include parity,at usart->cr1.12*///
#define	USART_WordLength_8bOdd		((ulong32)0x00000080)	///*word lenth,include parity,at usart->cr1.12*///
#define	USART_WordLength_8bNo			((ulong32)0x00000000)	///*word lenth,include parity,at usart->cr1.12*///
#define	USART_WordLength_9b_Parity_No		((ulong32)0x000000C0)
#define	USART_WordLength_Even_Reset	((ulong32)0xffffff3f)	///*Êý¾Ý³¤¶È£¬ÆæÅ¼Ð£Ñé¸´Î»*///


#define USART_Parity_No				((ulong32)0x00000000)	///*parity bit,at usart->cr1.10:9*///
#define USART_Parity_Even			((ulong32)0x00000400)
#define USART_Parity_Odd			((ulong32)0x00000600)

#define USART_ParityErrInt_EN		((ulong32)0x00000020)	///*enable parity error interrupt*///
#define USART_ParityErrInt_DIS		((ulong32)0x00000000)	///*disable parity error interrupt*///

#define	USART_RTIF_TXIF0              ((ulong32)0x00000001)	///**///
#define	USART_RTIF_RXIF0             ((ulong32)0x00000002)		///* ½ÓÊÕÖÐ¶Ï±êÖ¾Î»*///
#define	USART_RTIF_TXIF1              ((ulong32)0x00000004)	///*½ÓÊÕÖÐ¶Ï±êÖ¾Î»*///
#define	USART_RTIF_RXIF1             ((ulong32)0x00000008)		///* *///
#define	USART_RTIF_TXIF2              ((ulong32)0x00000010)	///**///
#define	USART_RTIF_RXIF2             ((ulong32)0x00000020)		///* ½ÓÊÕÖÐ¶Ï±êÖ¾Î»*///
#define	USART_RTIF_TXIF3              ((ulong32)0x00000040)	///**///
#define	USART_RTIF_RXIF3             ((ulong32)0x00000080)		///* ½ÓÊÕÖÐ¶Ï±êÖ¾Î»*///
#define	USART_RTIF_TXIF4              ((ulong32)0x00000100)	///**///
#define	USART_RTIF_RXIF4             ((ulong32)0x00000200)		///* ½ÓÊÕÖÐ¶Ï±êÖ¾Î»*///
#define	USART_RTIF_TXIF5             ((ulong32)0x00000400)	///**///
#define	USART_RTIF_RXIF5             ((ulong32)0x00000800)		///* ½ÓÊÕÖÐ¶Ï±êÖ¾Î»*///


#define	USART_REIE_Set_UART1              ((ulong32)0x00000008)	///* USART Enable Receive Interupt *///
#define	USART_REIE_Reset_UART1            ((ulong32)0x00000ff7)	///* USART Disable Receive Interupt *///

#define	USART_TXEIE_EN_UART1				((ulong32)0x00000004)	///* USART Enable Transmit Interupt *///
#define	USART_TXEIE_DIS_UART1			((ulong32)0x00000ffb)	///* USART Disable Transmit Interupt *///

#define	USART_REIE_Set_UART0              ((ulong32)0x00000002)	///* USART Enable Receive Interupt *///
#define	USART_REIE_Reset_UART0            ((ulong32)0x00000ffd)	///* USART Disable Receive Interupt *///

#define	USART_TXEIE_EN_UART0				((ulong32)0x00000001)	///* USART Enable Transmit Interupt *///
#define	USART_TXEIE_DIS_UART0			((ulong32)0x00000ffe)	///* USART Disable Transmit Interupt *///

#define	USART_REIE_Set_UART4              ((ulong32)0x00000200)	///* USART Enable Receive Interupt *///
#define	USART_REIE_Reset_UART4            ((ulong32)0x00000dff)	///* USART Disable Receive Interupt *///

#define	USART_TXEIE_EN_UART4				((ulong32)0x00000100)	///* USART Enable Transmit Interupt *///
#define	USART_TXEIE_DIS_UART4			((ulong32)0x00000eff)	///* USART Disable Transmit Interupt *///

#define	USART_REIE_Set_UART5              ((ulong32)0x00000800)	///* USART Enable Receive Interupt *///
#define	USART_REIE_Reset_UART5            ((ulong32)0x000007ff)	///* USART Disable Receive Interupt *///

#define	USART_TXEIE_EN_UART5				((ulong32)0x00000400)	///* USART Enable Transmit Interupt *///
#define	USART_TXEIE_DIS_UART5			((ulong32)0x00000bff)	///* USART Disable Transmit Interupt *///

#define	USART_TCIE_EN				((ulong32)0x00000004)	///* USART Enable Transmit Interupt *///
#define	USART_TCIE_DIS				((ulong32)0x0000fffb)	///* USART Disable Transmit Interupt *///

#define USART_RXBUFSTA_InTsel		((ulong32)0xfffffffb)	///* Êý¾Ý½ÓÊÕÍê³É²úÉúÖÐ¶Ï*///
#define USART_TXBUFSTA_InTsel		((ulong32)0xfffffff3)	///* ÓÉ TXISTXISTXISTXIS¾ö¶¨·¢ËÍÖÐ¶ÏÔÚ»º³å¿Õ»òÕßÒÆÎ»¼Ä´æÆ÷Ê±²úÉ*///
#define USART_RE_EN					((ulong32)0x00000010)	///* USART Enable Receive *///
#define USART_RE_DIS				((ulong32)0x0000ffef)	///* USART Disable Receive *///
#define USART_TE_Txis	                ((ulong32)0x00000020)	///* ÒÆÎ»¼Ä´æÆ÷Îª¿Õ²úÉúÖÐ¶Ï *///
#define USART_TE_Set                ((ulong32)0x00000010)	///* USART Enable Transmit *///
#define USART_TE_Reset              ((ulong32)0xffffffef)	///* USART Disable Transmit *///
#define USART_TEIREN_Dis              ((ulong32)0xfffffff7)	///* ½ûÖ¹ºìÍâ·¢ËÍµ÷ÖÆ*///
#define USART_TEIREN_En              ((ulong32)0x00000008)	///* Ê¹ÄÜºìÍâ·¢ËÍµ÷ÖÆ*///
#define USART_IRCONn			((ulong32)0x000041A4)	///* ºìÍâµ÷ÖÆÅäÖÃ¼Ä´æÆ÷*///
#define USART_IRCONn_WakeUp	((ulong32)0x000040D2)	///* ºìÍâµ÷ÖÆÅäÖÃ¼Ä´æÆ÷*///
#define USART_TE_IntSecM               ((ulong32)0x00000020)	///* ÒÆÎ»¼Ä´æÆ÷¿Õ²úÉúÖÐ¶Ï£»  *///
#define USART_TE_IntSecT               ((ulong32)0x00000000)	///* ·¢ËÍ»º³åÆ÷¿Õ²úÉúÖÐ¶Ï£»  *///
///*****************************************************************************************///
#define	USART_CR2_RESET				((ulong32)0x00000000)
///*stop bits*///
#define USART_StopBits_1			((ulong32)0x00000000)	///*stop bit,at usart->cr2.13:12*///
#define USART_StopBits_2			((ulong32)0x00000040)
#define USART_StopBits_15			((ulong32)0x00003000)

#define USART_CLKOut_EN				((ulong32)0x00000800)	///*clock outside en,use as smartcard*///
#define USART_CLKOut_DIS			((ulong32)0x0000ff0f)
///*****************************************************************************************///
#define	USART_CR3_RESET				((ulong32)0x00000000)

#define	USART_THREEBIT				((ulong32)0x000007ff)	///*samle bit:3*///
#define	USART_ONEBIT				((ulong32)0x00000800)	///*samle bit:1*///

#define	USART_SmartCard_EN			((ulong32)0x00000020)	///*smartcard enable*///
#define	USART_SmartCard_DIS			((ulong32)0x0000ffdf)	///*smartcard disable*///

#define	USART_NACK_EN				((ulong32)0x00000010)	///*smartcard mode:NACK transmission enable*///
#define	USART_NACK_DIS				((ulong32)0x0000ffef)	///*smartcard mode:NACK transmission disable*///

///*****************************************************************************************///
#define	USART_GTPR_RESET			((ulong32)0x00000000)

#define	USART_GuardTime				((ulong32)0x00000300)	///*guard time value of number of baud clocks*///
#define	USART_Prescaler				((ulong32)0x00000002)	///*smartcard prescaler for dividing the system clock*///
///*****************************************************************************************///
///*usart status register*///
#define USART_FLAG_CTS				((ulong32)0x00000200)
#define USART_FLAG_LBD				((ulong32)0x00000100)
#define USART_FLAG_TXE				((ulong32)0x00000080)
#define USART_FLAG_TC1				((ulong32)0x00000004)
#define USART_FLAG_RXNE1			((ulong32)0x00000008)
#define USART_FLAG_TC0				((ulong32)0x00000001)
#define USART_FLAG_RXNE0			((ulong32)0x00000002)
#define USART_FLAG_TC2				((ulong32)0x00000010)
#define USART_FLAG_RXNE2			((ulong32)0x00000020)
#define USART_FLAG_TC3				((ulong32)0x00000040)
#define USART_FLAG_RXNE3			((ulong32)0x00000080)
#define USART_FLAG_TC4				((ulong32)0x00000100)
#define USART_FLAG_RXNE4			((ulong32)0x00000200)
#define USART_FLAG_TC5				((ulong32)0x00000400)
#define USART_FLAG_RXNE5			((ulong32)0x00000800)
#define USART_FLAG_IDLE				((ulong32)0x00000010)
#define USART_FLAG_ORE				((ulong32)0x00000002)
#define USART_FLAG_NF				((ulong32)0x00000002)///*over
#define USART_FLAG_FE				((ulong32)0x00000004)
#define USART_FLAG_PE				((ulong32)0x00000008)
///*½ÓÊÕ·¢ËÍÈ¡·´¼Ä´æÆ÷
#define USART_RTXCONx_Reset				((ulong32)0x00000000)
#define USART_RTXCONx_RTX7ENNom				((ulong32)0x00000000)
#define USART_RTXCONx_RXDFLAG				((ulong32)0x00000000)
#define USART_RTXCONx_TXDFLAG				((ulong32)0x00000000)
///*****************************************************************************************///
#define Start_First485_Rx			{UART->UARTIE &= USART_TXEIE_DIS_UART1;\
									SFR_FIRST485->TXSTA &= USART_TE_Reset;\
									SFR_FIRST485->RTXCON = USART_RTXCONx_Reset;\
									SFR_FIRST485->RXBUFSTA &= USART_RXBUFSTA_InTsel;\
									SFR_FIRST485->RXSTA |= USART_RE_EN;\
									UART->UARTIF  = (USART_RTIF_TXIF1);\
									UART->UARTIE |= USART_REIE_Set_UART1;}

#define Stop_First485_Rx			{UART->UARTIE &= USART_REIE_Reset_UART1;\
									SFR_FIRST485->RXSTA &= USART_RE_DIS;}
									
#define Start_First485_Tx			{	SFR_FIRST485->TXSTA &= USART_TEIREN_Dis;	\
									SFR_FIRST485->TXSTA |= (USART_TE_Set|USART_TE_Txis);\
									SFR_FIRST485->TXBUFSTA &= USART_TXBUFSTA_InTsel;\
									UART->UARTIE |= USART_TXEIE_EN_UART1;}
									
#define Stop_First485_Tx			{UART->UARTIE &= USART_TXEIE_DIS_UART1;\
									SFR_FIRST485->TXSTA &= USART_TE_Reset;}
///**********************************************************************///
///*#if	( C_PcbVersion == C_Pcb2457 )///*-M±í£¬Í¨ÐÅÄ£¿é´®¿Ú
#define Start_Modular_Rx			{UART->UARTIE &= USART_TXEIE_DIS_UART0;\
									SFR_MODULAR->TXSTA &= USART_TE_Reset;\
									SFR_MODULAR->RTXCON = USART_RTXCONx_Reset;\
									SFR_MODULAR->RXBUFSTA &= USART_RXBUFSTA_InTsel;\
									SFR_MODULAR->RXSTA |= USART_RE_EN;\
									UART->UARTIF  = (USART_RTIF_TXIF0);\
									UART->UARTIE |= USART_REIE_Set_UART0;}

#define Start_ModularReport_Rx      {SFR_MODULAR->RTXCON = USART_RTXCONx_Reset;\
									SFR_MODULAR->RXBUFSTA &= USART_RXBUFSTA_InTsel;\
									SFR_MODULAR->RXSTA |= USART_RE_EN;\
									UART->UARTIF  = (USART_RTIF_TXIF0);\
									UART->UARTIE |= USART_REIE_Set_UART0;}

#define Stop_Modular_Rx			{UART->UARTIE &= USART_REIE_Reset_UART0;\
									SFR_MODULAR->RXSTA &= USART_RE_DIS;}
									
#define Start_Modular_Tx			{	SFR_MODULAR->TXSTA &= USART_TEIREN_Dis;	\
										SFR_MODULAR->TXSTA |= (USART_TE_Set|USART_TE_Txis);\
										SFR_MODULAR->TXBUFSTA &= USART_TXBUFSTA_InTsel;\
										UART->UARTIE |= USART_TXEIE_EN_UART0;}
									
#define Stop_Modular_Tx			{UART->UARTIE &= USART_TXEIE_DIS_UART0;\
									SFR_MODULAR->TXSTA &= USART_TE_Reset;}
///*ÖÇÄÜ±í µÚ2Â·485
#define Start_Second485_Rx			{UART->UARTIE &= USART_TXEIE_DIS_UART5;\
									SFR_SECOND485->TXSTA &= USART_TE_Reset;\
									SFR_SECOND485->RTXCON = USART_RTXCONx_Reset;\
									SFR_SECOND485->RXBUFSTA &= USART_RXBUFSTA_InTsel;\
									SFR_SECOND485->RXSTA |= USART_RE_EN;\
									UART->UARTIF  = (USART_RTIF_TXIF5);\
									UART->UARTIE |= USART_REIE_Set_UART5;}

#define Stop_Second485_Rx			{UART->UARTIE &= USART_REIE_Reset_UART5;\
									SFR_SECOND485->RXSTA &= USART_RE_DIS;}
									
#define Start_Second485_Tx			{	SFR_SECOND485->TXSTA &= USART_TEIREN_Dis;	\
										SFR_SECOND485->TXSTA |= (USART_TE_Set|USART_TE_Txis);\
										SFR_SECOND485->TXBUFSTA &= USART_TXBUFSTA_InTsel;\
										UART->UARTIE |= USART_TXEIE_EN_UART5;}
									
#define Stop_Second485_Tx			{UART->UARTIE &= USART_TXEIE_DIS_UART5;\
									SFR_SECOND485->TXSTA &= USART_TE_Reset;}																	
///**********************************************************************///
#define Start_Infra_Rx				{UART->UARTIE &= USART_TXEIE_DIS_UART4;\
									SFR_INFRA->TXSTA &= USART_TE_Reset;\
									SFR_INFRA->RTXCON = USART_RTXCONx_Reset;\
									SFR_INFRA->RXBUFSTA &= USART_RXBUFSTA_InTsel;\
									SFR_INFRA->RXSTA |= USART_RE_EN;\
									UART->UARTIF = (USART_RTIF_TXIF4);\
									UART->UARTIE |= USART_REIE_Set_UART4;}

#define Stop_Infra_Rx				{UART->UARTIE &= USART_REIE_Reset_UART4;\
									SFR_INFRA->RXSTA &= USART_RE_DIS;}
									
#define Start_Infra_Tx				{SFR_INFRA->TXSTA |= (USART_TE_Set|USART_TE_Txis);\
									SFR_INFRA->TXBUFSTA &= USART_TXBUFSTA_InTsel;\
									UART->UARTIE |= USART_TXEIE_EN_UART4;}
									
#define Stop_Infra_Tx					{UART->UARTIE &= USART_TXEIE_DIS_UART4;\
									SFR_INFRA->TXSTA &= USART_TE_Reset;}
									
///*****************************************************************************************///
#define		Enable_ComUart_Clock		ComUart_SouceClock_SFR |= ComUart_SouceClock_EN;
#define 		Disable_ComUart_Clock		ComUart_SouceClock_SFR &= ComUart_SouceClock_DIS;

#define		Enable_485_1_Clock		First485_SouceClock_SFR |= First485_SouceClock_EN;
#define 	Disable_485_1_Clock		First485_SouceClock_SFR &= First485_SouceClock_DIS;
//#define		Select_485_1_UartMode	{IO_FIRST485R->IO_FIRST485R_AF &= FIRST485R_AF_RESET;\
//									IO_FIRST485R->IO_FIRST485R_AF |= FIRST485R_AF_UART;\
//									IO_FIRST485T->IO_FIRST485T_AF &= FIRST485T_AF_RESET;\
//									IO_FIRST485T->IO_FIRST485T_AF |= FIRST485T_AF_UART;}
#define		Select_485_1_AFMode		{IO_FIRST485R->MODER &= FIRST485R_IN_MODE;\
									IO_FIRST485R->MODER |= IO_FIRST485R_AF;\
									IO_FIRST485T->MODER &= FIRST485T_IN_MODE;\
									IO_FIRST485T->MODER |= IO_FIRST485T_AF;}
#define		Select_485_1_IO_Type	{IO_FIRST485R->PUPDR &= FIRST485R_NOPUPD;\
									IO_FIRST485T->OTYPER &= FIRST485T_OUTPUT_PP;}
//#define		Enable_485_1_Receive	{IO_FIRST485->PUPDR &= FIRST485_NOPUPD;\
//									IO_FIRST485->MODER &= FIRST485_IN_MODE;}
#define		Enable_485_1_Receive	{IO_FIRST485->BSETH = FIRST485SET;\
									IO_FIRST485->MODER &= FIRST485_IN_MODE;\
									IO_FIRST485->MODER |= FIRST485_OUT_MODE;\
									IO_FIRST485->OTYPER &= FIRST485_OUTPUT_PP;\
									IO_FIRST485->BSETH = FIRST485SET;}	
#define		Enable_485_1_Transmit	{IO_FIRST485->BSRR = FIRST485RESET;\
									IO_FIRST485->MODER &= FIRST485_IN_MODE;\
									IO_FIRST485->MODER |= FIRST485_OUT_MODE;\
									IO_FIRST485->OTYPER &= FIRST485_OUTPUT_PP;\
									IO_FIRST485->BSRR = FIRST485RESET;}
///*****************************************************************************************///
#define		Enable_485_2_Clock		Second485_SouceClock_SFR |= Second485_SouceClock_EN;
#define 	Disable_485_2_Clock		Second485_SouceClock_SFR &= Second485_SouceClock_DIS;
//#define		Select_485_2_UartMode	{IO_SECOND485R->IO_SECOND485R_AF &= SECOND485R_AF_RESET;\
//									IO_SECOND485R->IO_SECOND485R_AF |= SECOND485R_AF_UART;\
//									IO_SECOND485T->IO_SECOND485T_AF &= SECOND485T_AF_RESET;\
//									IO_SECOND485T->IO_SECOND485T_AF |= SECOND485T_AF_UART;}
#define		Select_485_2_AFMode		{IO_SECOND485R->MODER &= SECOND485R_IN_MODE;\
									IO_SECOND485R->MODER |= IO_SECOND485R_AF;\
									IO_SECOND485T->MODER &= SECOND485T_IN_MODE;\
									IO_SECOND485T->MODER |= IO_SECOND485T_AF;}
#define		Select_485_2_IO_Type	{IO_SECOND485R->PUPDR &= SECOND485R_NOPUPD;\
									IO_SECOND485T->OTYPER &= SECOND485T_OUTPUT_PP;}
									
#define		Select_485_2_ComIO_Type		{IO_SECOND485R->BSETH = SECOND485RSET;\
									IO_SECOND485R->MODER &= SECOND485R_IN_MODE;\
									IO_SECOND485R->MODER |= SECOND485R_OUT_MODE;\
									IO_SECOND485R->OTYPER |= SECOND485R_OUTPUT_OD;\
									IO_SECOND485R->BSETH = SECOND485RSET;\
									IO_SECOND485T->BSETH = SECOND485TSET;\
									IO_SECOND485T->MODER &= SECOND485T_IN_MODE;\
									IO_SECOND485T->MODER |= SECOND485T_OUT_MODE;\
									IO_SECOND485T->OTYPER |= SECOND485T_OUTPUT_OD;\
									IO_SECOND485T->BSETH = SECOND485TSET;}

#define		Enable_485_2_Receive	{IO_SECOND485->BSETH = SECOND485SET;\
									IO_SECOND485->MODER &= SECOND485_IN_MODE;\
									IO_SECOND485->MODER |= SECOND485_OUT_MODE;\
									IO_SECOND485->OTYPER &= SECOND485_OUTPUT_PP;\
									IO_SECOND485->BSETH = SECOND485SET;}
#define		Enable_485_2_Transmit	{IO_SECOND485->BSRR = SECOND485RESET;\
									IO_SECOND485->MODER &= SECOND485_IN_MODE;\
									IO_SECOND485->MODER |= SECOND485_OUT_MODE;\
									IO_SECOND485->OTYPER &= SECOND485_OUTPUT_PP;\
									IO_SECOND485->BSRR = SECOND485RESET;}
///*****************************************************************************************///
#define		Enable_Modular_Clock		Modular_SouceClock_SFR |= Modular_SouceClock_EN;
#define 	Disable_Modular_Clock		Modular_SouceClock_SFR &= Modular_SouceClock_DIS;
//#define		Select_Modular_UartMode	{IO_MODULARR->IO_MODULARR_AF &= MODULARR_AF_RESET;\
//									IO_MODULARR->IO_MODULARR_AF |= MODULARR_AF_UART;\
//									IO_MODULART->IO_MODULARR_AF &= MODULARR_AF_RESET;\
//									IO_MODULART->IO_MODULARR_AF |= MODULARR_AF_UART;}
#define		Select_Modular_AFMode		{IO_MODULARR->MODER &= MODULARR_IN_MODE;\
									IO_MODULARR->MODER |= IO_MODULARR_AF;\
									IO_MODULART->MODER &= MODULART_IN_MODE;\
									IO_MODULART->MODER |= IO_MODULART_AF;}
#define		Select_Modular_IO_Type	{IO_MODULARR->PUPDR &= MODULARR_NOPUPD;\
									IO_MODULART->OTYPER &= MODULART_OUTPUT_PP;}
									
#define		Select_Modular_ComIO_Type		{IO_MODULARR->BSETH = MODULARRSET;\
									IO_MODULARR->MODER &= MODULARR_IN_MODE;\
									IO_MODULARR->MODER |= MODULARR_OUT_MODE;\
									IO_MODULARR->OTYPER |= MODULARR_OUTPUT_OD;\
									IO_MODULARR->BSETH = MODULARRSET;\
									IO_MODULART->BSETH = MODULARTSET;\
									IO_MODULART->MODER &= MODULART_IN_MODE;\
									IO_MODULART->MODER |= MODULART_OUT_MODE;\
									IO_MODULART->OTYPER |= MODULART_OUTPUT_OD;\
									IO_MODULART->BSETH = MODULARTSET;}								
///*****************************************************************************************///
//#define		Select_InfraIO_PWM		{IO_TXDI38K->IO_TXDI38K_AF &= TXDI38K_AF_RESET;\
//									IO_TXDI38K->IO_TXDI38K_AF |= TXDI38K_AF3;\
//									IO_TXDI38K->MODER &= TXDI38K_IN_MODE;\
//									IO_TXDI38K->MODER |= TXDI38K_AF_MODE;\
//									IO_TXDI38K->OTYPER &= TXDI38K_OUTPUT_PP;\
//									IO_TXDI38K->OSPEEDR &= TXDI38K_SPEED_INIT;\
//									IO_TXDI38K->OSPEEDR |= TXDI38K_SPEED_2MHZ;}

#define		Enable_Infra_Clock		Infra_SouceClock_SFR |= Infra_SouceClock_EN;
#define 	Disable_Infra_Clock		Infra_SouceClock_SFR &= Infra_SouceClock_DIS;

//#define		Select_Infra_UartMode	{ulong32 SV_ulTemp_UART;\
//									SV_ulTemp_UART = IO_INFRARX->IO_INFRARX_AF;\
//									SV_ulTemp_UART &= INFRARX_AF_RESET;\
//									SV_ulTemp_UART |= INFRARX_AF_UART;\
//									IO_INFRARX->IO_INFRARX_AF = SV_ulTemp_UART;\
//									SV_ulTemp_UART = IO_INFRATX->IO_INFRATX_AF;\
//									SV_ulTemp_UART &= INFRATX_AF_RESET;\
//									SV_ulTemp_UART |= INFRATX_AF_UART;\
//									IO_INFRATX->IO_INFRATX_AF = SV_ulTemp_UART;}
									
#define		Select_Infra_AFMode		{ulong32 SV_ulTemp_UART;\
									SV_ulTemp_UART = IO_INFRARX->MODER;\
									SV_ulTemp_UART &= INFRARX_IN_MODE;\
									SV_ulTemp_UART |= IO_INFRARX_AF;\
									IO_INFRARX->MODER = SV_ulTemp_UART;\
									SV_ulTemp_UART = IO_INFRATX->MODER;\
									SV_ulTemp_UART &= INFRATX_IN_MODE;\
									SV_ulTemp_UART |= IO_INFRATX_AF;\
									IO_INFRATX->MODER = SV_ulTemp_UART;}
#define		Select_Infra_IO_Type	{IO_INFRARX->PUPDR &= INFRARX_NOPUPD;\
									IO_INFRATX->OTYPER &= INFRATX_OUTPUT_PP;}

///*****************************************************************************************///
//#define		Enable_ESAM_Clock		Esam_SouceClock_SFR |= EsamSouceClock_EN;
//#define		Disable_ESAM_Clock		Esam_SouceClock_SFR &= EsamSouceClock_DIS;
//#define		Select_ESAMClk_UartMode	{IO_ESAMCLK->MODER &= ESAMCLK_IN_MODE;\
//									IO_ESAMCLK->MODER |= ESAMCLK_AF_MODE;\
//									IO_ESAMCLK->IO_ESAMCLK_AF &= ESAMCLK_AF_RESET;\
//									IO_ESAMCLK->IO_ESAMCLK_AF |= ESAMCLK_AF_UART;}
//									
//#define		Select_ESAMIO_UartMode	{ulong32 SV_ulTemp_UART;\
//									SV_ulTemp_UART = IO_ESAMDATA->MODER;\
//									SV_ulTemp_UART &= ESAMDATA_IN_MODE;\
//									SV_ulTemp_UART |= ESAMDATA_AF_MODE;\
//									IO_ESAMDATA->MODER = SV_ulTemp_UART;\
//									SV_ulTemp_UART = IO_ESAMDATA->IO_ESAMDATA_AF;\
//									SV_ulTemp_UART &= ESAMDATA_AF_RESET;\
//									SV_ulTemp_UART |= ESAMDATA_AF_UART;\
//									IO_ESAMDATA->IO_ESAMDATA_AF = SV_ulTemp_UART;}
///***********************************************************************************///
#define		Enable_CARD_Clock		Card_SouceClock_SFR |= CardSouceClock_EN;
#define		Disable_CARD_Clock		Card_SouceClock_SFR &= CardSouceClock_DIS;

#define		Select_CARDIO_UartMode	{ulong32 SV_ulTemp_UART;\
									SV_ulTemp_UART = IO_CARDDATA->MODER;\
									SV_ulTemp_UART &= CARDDATA_IN_MODE;\
									SV_ulTemp_UART |= CARDDATA_AF_MODE;\
									IO_CARDDATA->MODER = SV_ulTemp_UART;\
									SV_ulTemp_UART = IO_CARDDATA->IO_CARDDATA_AF;\
									SV_ulTemp_UART &= CARDDATA_AF_RESET;\
									SV_ulTemp_UART |= CARDDATA_AF_UART;\
									IO_CARDDATA->IO_CARDDATA_AF = SV_ulTemp_UART;}
///***********************************************************************************///
///***********************************************************************************///

extern void InF_Dispatch_CommInterruptMessage(void);
extern void InF_Inti_UartTemp(void);
//extern uchar8 SF_RecOneByteFrom_Esam(uchar8 *P_Buff);
//extern uchar8 SF_SendOneByteTo_Esam(uchar8 data);
extern uchar8 SF_RecOneByteFrom_Card(uchar8 *P_Buff);
extern uchar8 SF_SendOneByteTo_Card(uchar8 data);
extern void SF_InfraModulatedSignalConfig(void);
extern void SF_InfarWakeupTimerInit(void);
extern void SF_InfarWakeupTimer_Disable(void);
//extern uchar8 SV_485_1_timer;
//extern uchar8 SV_485_1_int;
//extern uchar8 SV_485_1_dispatch;

extern void SF_UartOvertime(void);

#endif
