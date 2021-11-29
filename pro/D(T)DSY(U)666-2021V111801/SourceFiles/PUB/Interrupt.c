/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    Interrupt.c                                                                          
**** Brief:       中断函数                                                                      
**** Author:      peter.he@chint.com                                                                 
**** Version:     V1.0                                                                               
**** Date:        2016-7-14                                                                          
****                                                                                                 
**** note:修改历史记录列表，每条修改记录应包括修改日期、修改者                                          
**** 1.  Author:                                                                                     
****     Version:                                                                                    
****     Date :                                                                                      
**** 2.  Author:                                                                                     
****     Version:                                                                                       
****     Date:
****                                                                                        
****  addtogroup:Library                                                             
**********************************************************************************************************/

/*--------------------------------- 文件功能说明 -------------------------------------------------------*/
/*
 *  该文件所有函数的前缀为xxxx_
 *  文件主函数和对外函数需放在文件的首部，并且主函数需要放在第一个位置;
 *  函数注释采用标准模板，函数内部注释采用//;
 *  对于注释较多的部分，可以增加一个注释符，然后详细说明放在文件的尾部;
 *--------------------------------- 文件功能说明 -------------------------------------------------------*/
 
/**有形参的函数格式:*/
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    xx任务处理函数
 *
 *  @param    xx :
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
/**无形参的函数格式:*/
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    上电所有口线配置成初始状态，后面可根据需要开启和配置
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
 
 
/*----------------< 包含文件 >----------------------------------*/
#include "..\SourceFiles\PUB\Include.h"

/*----------------< 宏定义区 >----------------------------------*/


/*----------------< 常量定义 >----------------------------------*/


/*----------------< 变量定义 >----------------------------------*/


/*----------------< 函数声明 >----------------------------------*/


/*----------------< 函数定义 >----------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    外部中断4,暂时不用
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void Inter_INT4(void) interrupt 0
{
	unsigned char xdata bak_PPBANK,FLASHCON_bak;
	
	FLASHCON_bak = FLASHCON;
	FLASHCON = 0;
	
	PBANKLO = 0x55;   			// Set PSBANK LOCK                      *
	bak_PPBANK = PBANK;			// Set PSBANK                           *
	PBANKLO = 0x00;
	
#if ( METER_TYPE == METER_TYPE_DTSY666)	
	if((EXF0&0x10)==0x10)
	{
		EXF0=0x00;//清IF44外部中断标志
		if (GStr_EnergyPulseFw.ucPulseStatu & F_PULSESTATU_BUSY)	///* 如果是在处理过程中 *///
		{
			GStr_EnergyPulseFw.ucPulseAddBusy++;
		}
		else
		{
			GStr_EnergyPulseFw.ucPulseAdd += GStr_EnergyPulseFw.ucPulseAddBusy;
			GStr_EnergyPulseFw.ucPulseAdd++;
			GStr_EnergyPulseFw.ucPulseAddBusy = 0;
		}
		Pulse_Out_Enable();
		GStr_Monitor.ulPulsewidth=0;///脉冲宽度开始计数
	}
#else
	IENX = 0x00;
	EXF0 = 0x00;
#endif
	
	PBANKLO = 0x55;   			// Set PSBANK LOCK                      *
	PBANK = bak_PPBANK;			// Set PSBANK                           *
	PBANKLO = 0x00;	

	FLASHCON = FLASHCON_bak;	
}


/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    定时器2，暂时没用
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void Inter_Timer1(void) interrupt 3
{
	unsigned char xdata bak_PPBANK,FLASHCON_bak;

	
	FLASHCON_bak = FLASHCON;
	FLASHCON = 0;
	
	PBANKLO = 0x55;   			// Set PSBANK LOCK                      *
	bak_PPBANK = PBANK;			// Set PSBANK                           *
	PBANKLO = 0x00;

	
	IEN0 &= ~IEN0_ET1;
	TCON &= ~(TCON_TF1 | TCON_TR1);
	

	PBANKLO = 0x55;   			// Set PSBANK LOCK                      *
	PBANK = bak_PPBANK;			// Set PSBANK                           *
	PBANKLO = 0x00;	
	
	FLASHCON = FLASHCON_bak;
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    定时中断函数，基本节拍计数源，暂定2ms中断一次
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void Inter_Timer0(void) interrupt 1
{
	unsigned char xdata bak_PPBANK,FLASHCON_bak;
	
	FLASHCON_bak = FLASHCON;
	FLASHCON = 0;
	
	PBANKLO = 0x55;   			// Set PSBANK LOCK                      *
	bak_PPBANK = PBANK;			// Set PSBANK                           *
	PBANKLO = 0x00;


	TCON &= ~TCON_TF0;	// 清除标志

	TL0 = T_Xms_TL0;	// 重新配置
    TH0 = T_Xms_TH0;

	// 检测一下掉电
	if( LPDCON2 & LPDCON2_LPD2F )
	{  
		GStr_Flag.ucSystem |= F_PWOFF_NOW ; 
	}
	#if ( METER_TYPE == METER_TYPE_DTSY666)	
	if(GStr_Monitor.ulPulsewidth<C_PulseWidth)
	{
		GStr_Monitor.ulPulsewidth++;
		if(GStr_Monitor.ulPulsewidth>=C_PulseWidth)
		{
			 Pulse_Out_Disable() ;
		}
	}
	#endif

	GStr_Monitor.ulTimer_ms_old = GStr_Monitor.ulTimer_ms;
	if ( GStr_Monitor.ulTimer_ms < 0xffffffff )
	{
		GStr_Monitor.ulTimer_ms++;
	}
	else
	{
		GStr_Monitor.ulTimer_ms = 0;
	}

	PBANKLO = 0x55;   			// Set PSBANK LOCK                      *
	PBANK = bak_PPBANK;			// Set PSBANK                           *
	PBANKLO = 0x00;	
	
	FLASHCON = FLASHCON_bak;
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    串口通信，RS485通信中断
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void Inter_EUART0(void) interrupt 4
{
	uchar8 V_ucTempData;
	unsigned char xdata bak_PPBANK,FLASHCON_bak;
	
	FLASHCON_bak = FLASHCON;
	FLASHCON = 0;
	
	PBANKLO = 0x55;   			// Set PSBANK LOCK                      *
	bak_PPBANK = PBANK;			// Set PSBANK                           *
	PBANKLO = 0x00;
	

	// @brief 接收：往缓存里发送一个字节 
	
	if( TI )
	{
		TI = 0; 
		
		Gstr_UartComm[CH_485].ucCommSndCnt++;
		if ( Gstr_UartComm[CH_485].ucCommSndCnt < Gstr_UartComm[CH_485].ucCommSndLen )
		{
			Gstr_UartComm[CH_485].ulCommSndByteOverTime = LibPub_GetTimerBeatInt0() ;
			ACC = Gstr_UartComm[CH_485].ucaCommTXBuff[Gstr_UartComm[CH_485].ucCommSndCnt];
			if( P )
			{
				TB8 = 1;
			}
			else
			{
				TB8 = 0;
			}
			SBUF = Gstr_UartComm[CH_485].ucaCommTXBuff[Gstr_UartComm[CH_485].ucCommSndCnt] ;
 		}
		else
		{
			Gstr_UartComm[CH_485].ucCommChStatus = API_COMM_STATUS_ERROR; 
		}
	}
	
		
	// @brief 接收：从缓存里接收一个字节 
	if( RI )
	{
		RI = 0; 
		V_ucTempData = SBUF; 
		
		// 判断一下是否偶校验
		// ACC = V_ucTempData;
		// if( P == RB81 )
		{
			ApiDLT645_UARTReceiveDataJudge0( CH_485 , V_ucTempData);
		}
	}	
	
	PBANKLO = 0x55;   			// Set PSBANK LOCK                      *
	PBANK = bak_PPBANK;			// Set PSBANK                           *
	PBANKLO = 0x00;	

	FLASHCON = FLASHCON_bak;	
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    串口通信，蓝牙通信中断
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void Inter_EUART1(void) interrupt 9
{
	uchar8 V_ucTempData;
	unsigned char xdata bak_PPBANK,FLASHCON_bak;

		
	FLASHCON_bak = FLASHCON;
	FLASHCON = 0;
	
	PBANKLO = 0x55;   			// Set PSBANK LOCK                      *
	bak_PPBANK = PBANK;			// Set PSBANK                           *
	PBANKLO = 0x00;
	

	// @brief 接收：往缓存里发送一个字节 
	
	if( TI1 )
	{
		TI1 = 0; 
		
		Gstr_UartComm[CH_BLE].ucCommSndCnt++;
		if ( Gstr_UartComm[CH_BLE].ucCommSndCnt < Gstr_UartComm[CH_BLE].ucCommSndLen )
		{
			Gstr_UartComm[CH_BLE].ulCommSndByteOverTime = LibPub_GetTimerBeatInt1() ;
			ACC = Gstr_UartComm[CH_BLE].ucaCommTXBuff[Gstr_UartComm[CH_BLE].ucCommSndCnt];
			if( P )
			{
				TB81 = 1;
			}
			else
			{
				TB81 = 0;
			}
			SBUF1 = Gstr_UartComm[CH_BLE].ucaCommTXBuff[Gstr_UartComm[CH_BLE].ucCommSndCnt] ;
 		}
		else
		{
			Gstr_UartComm[CH_BLE].ucCommChStatus = API_COMM_STATUS_ERROR;
		}
	}
	
		
	// @brief 接收：从缓存里接收一个字节 
	if( RI1 )
	{
		RI1 = 0; 
		V_ucTempData = SBUF1; 
		
		// 判断一下是否偶校验
//		ACC = V_ucTempData;
//		if( P == RB81 )		
		{
			ApiDLT645_UARTReceiveDataJudge1( CH_BLE , V_ucTempData);	/*正常为Judge1，导轨表只有蓝牙一个uart0，用485通信时帧解析调用ApiDLT645_UARTReceiveDataJudge0函数*/
		}
	}
	
	PBANKLO = 0x55;   			// Set PSBANK LOCK                      *
	PBANK = bak_PPBANK;			// Set PSBANK                           *
	PBANKLO = 0x00;		

	FLASHCON = FLASHCON_bak;	
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    定时器2中断
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void Inter_Timer2(void) interrupt 5
{
	unsigned char xdata bak_PPBANK,FLASHCON_bak;

	FLASHCON_bak = FLASHCON;
	FLASHCON = 0;
	
	PBANKLO = 0x55;   			// Set PSBANK LOCK                      *
	bak_PPBANK = PBANK;			// Set PSBANK                           *
	PBANKLO = 0x00;
	
	
	IEN0  &= ~IEN0_ET2;
	T2CON &= ~(T2CON_TF2 | T2CON_EXF2 | T2CON_EXEN2 | T2CON_TR2 );

	PBANKLO = 0x55;   			// Set PSBANK LOCK                      *
	PBANK = bak_PPBANK;			// Set PSBANK                           *
	PBANKLO = 0x00;		

	FLASHCON = FLASHCON_bak;
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ADC/TPS中断
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void Inter_ADC_TPS(void) interrupt 6
{
	unsigned char xdata bak_PPBANK,FLASHCON_bak;

	FLASHCON_bak = FLASHCON;
	FLASHCON = 0;
	
	PBANKLO = 0x55;   			// Set PSBANK LOCK                      *
	bak_PPBANK = PBANK;			// Set PSBANK                           *
	PBANKLO = 0x00;
	
	
	IEN0  &= ~IEN0_EADTP;
	ADCON &= ~(ADCON_ADON | ADCON_ADCIF | ADCON_TPSCON );

	PBANKLO = 0x55;   			// Set PSBANK LOCK                      *
	PBANK = bak_PPBANK;			// Set PSBANK                           *
	PBANKLO = 0x00;		
	
	FLASHCON = FLASHCON_bak;
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    EMU中断
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void Inter_EMU(void) interrupt 7
{		
	#if ( METER_TYPE != METER_TYPE_DTSY666)
	uchar8 V_ucTempEMUIF;
	#endif
	unsigned char xdata bak_PPBANK,FLASHCON_bak;	
	
	FLASHCON_bak = FLASHCON;
	FLASHCON = 0;

	
	PBANKLO = 0x55;   			// Set PSBANK LOCK                      *
	bak_PPBANK = PBANK;			// Set PSBANK                           *
	PBANKLO = 0x00;
	
	#if ( METER_TYPE != METER_TYPE_DTSY666)
	V_ucTempEMUIF = EMUIF;	
	EMUIF = 0x00;
	
	if ( V_ucTempEMUIF & EMUIF_PFIF )	///* 有产生脉冲中断，因为是SOC，所以可以省去判断沿的烦恼 *///
	{
		if (GStr_EnergyPulseFw.ucPulseStatu & F_PULSESTATU_BUSY)	///* 如果是在处理过程中 *///
		{
			GStr_EnergyPulseFw.ucPulseAddBusy++;
		}
		else
		{
			GStr_EnergyPulseFw.ucPulseAdd += GStr_EnergyPulseFw.ucPulseAddBusy;
			GStr_EnergyPulseFw.ucPulseAdd++;
			GStr_EnergyPulseFw.ucPulseAddBusy = 0;
		}
	}
	#else
	IEN1 &= ~IEN1_EEMU;///关闭EMU中断
	#endif
	
	PBANKLO = 0x55;   			// Set PSBANK LOCK                      *
	PBANK = bak_PPBANK;			// Set PSBANK                           *
	PBANKLO = 0x00;

	
	FLASHCON = FLASHCON_bak;
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    RTC中断
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void Inter_RTC(void) interrupt 8
{
	unsigned char xdata bak_PPBANK,FLASHCON_bak;

	FLASHCON_bak = FLASHCON;
	FLASHCON = 0;
	
	PBANKLO = 0x55;   			// Set PSBANK LOCK                      *
	bak_PPBANK = PBANK;			// Set PSBANK                           *
	PBANKLO = 0x00;
	
	
	RTCIE = 0X00;
	RTCIF = 0X00;
	IEN1  &= ~IEN1_ERTC;
	
	
	PBANKLO = 0x55;   			// Set PSBANK LOCK                      *
	PBANK = bak_PPBANK;			// Set PSBANK                           *
	PBANKLO = 0x00;


	FLASHCON = FLASHCON_bak	;
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    LPD中断,中断里就置一下位就好，掉电在主循环中检测
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void Inter_LPD(void) interrupt 12
{ 
	unsigned char xdata bak_PPBANK,FLASHCON_bak;
	

	FLASHCON_bak = FLASHCON;
	FLASHCON = 0;
	
	PBANKLO = 0x55;   			// Set PSBANK LOCK                      *
	bak_PPBANK = PBANK;			// Set PSBANK                           *
	PBANKLO = 0x00; 

	DIS_LPD_INT();
	LPDCON1 = 0x00;
	
//	if( LPDCON2 & LPDCON2_LPD2F )
//	{ 
//		LPDCON2 &= ~LPDCON2_LPD2F;
//		GStr_Flag.ucSystem |= F_PWOFF_NOW ; 
//	}


	PBANKLO = 0x55;   			// Set PSBANK LOCK                      *
	PBANK = bak_PPBANK;			// Set PSBANK                           *
	PBANKLO = 0x00;		


	FLASHCON = FLASHCON_bak;
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    EUART3中断
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void Inter_EUART3(void) interrupt 14
{ 
	unsigned char xdata bak_PPBANK,FLASHCON_bak;


	FLASHCON_bak = FLASHCON;
	FLASHCON = 0;
	
	PBANKLO = 0x55;   			// Set PSBANK LOCK                      *
	bak_PPBANK = PBANK;			// Set PSBANK                           *
	PBANKLO = 0x00;
	
	
	SCON3 &= ~( SCON3_TI3 | SCON3_RI3) ; 
	IEN1  &= ~IEN1_ERTC;
	
	PBANKLO = 0x55;   			// Set PSBANK LOCK                      *
	PBANK = bak_PPBANK;			// Set PSBANK                           *
	PBANKLO = 0x00;
	

	FLASHCON = FLASHCON_bak;
}