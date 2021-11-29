/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    AppComm.c                                                                          
**** Brief:       通信处理文件，主要处理通信数据，不处理协议数据                                                                      
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
void ApiComm_CommTask(void);
void ApiComm_CommParaInit( uchar8 v_ucChID );

static void ApiComm_ChannelProcess( uchar8 v_ucChID );
static void ApiComm_ProtocolProcess( uchar8 v_ucChID );
/*----------------< 函数定义 >----------------------------------*/

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief   通信任务处理函数
 *
 *  @return   none
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/

void ApiComm_CommTask(void)	
{
	uchar8 V_ucCnti;
	
	if ( (GStr_Flag.ucSystem & F_PWON)==0 )	///* 掉电了就直接退出 *///
	{
		return;
	}
	
	///* 通信任务处理。一次处理多通道  *///
	for ( V_ucCnti=0; V_ucCnti<UART_CHNUMS; V_ucCnti++ )
	{
		ApiComm_ChannelProcess ( V_ucCnti );
		ApiComm_ProtocolProcess( V_ucCnti );
		ApiComm_ChannelProcess ( V_ucCnti );
	}
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief   通信参数解析
 *
 *  @param   chID: 通道ID
 *
 *  @return   none
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
static void ApiComm_ChannelProcess( uchar8 v_ucChID )
{
	uchar8  V_ucInitUartFlg = _FALSE;
	ulong32	V_ulTempData = 0;
	
	switch ( Gstr_UartComm[v_ucChID].ucCommChStatus )
	{
		
		///* 空闲状态,1s定时初始化一次 *///
		case API_COMM_STATUS_IDLE:	
		{   
			if ( _TRUE == LibPub_GetDiffTime( Gstr_UartComm[v_ucChID].ulCommTimeInit, LibPub_GetTimerBeat(), API_COMM_UART_INIT_TIME) )
			{
				V_ucInitUartFlg = _TRUE;
			}
			 
		}break;
		
		///* 发送状态，判断字节超时 500ms *///
		case API_COMM_STATUS_SEND:		
		{ 
			V_ulTempData = Gstr_UartComm[v_ucChID].ulCommSndByteOverTime;
			if ( _TRUE == LibPub_GetDiffTime( V_ulTempData, LibPub_GetTimerBeat(), API_DLT645_BYTE_INTEVAL_TIME) )
			{
				V_ucInitUartFlg = _TRUE;
			}
		}break;
		
		///* 接收状态，判断字节超时500ms *///
		case API_COMM_STATUS_RECV:		
		{
			V_ulTempData = Gstr_UartComm[v_ucChID].ulCommRcvByteOverTime;
			if ( _TRUE == LibPub_GetDiffTime( V_ulTempData, LibPub_GetTimerBeat(), API_DLT645_BYTE_INTEVAL_TIME) )
			{
				V_ucInitUartFlg = _TRUE;
			}
		}break;
		
//		///* 接收完成，接收缓存转移到发送缓存中（485和蓝牙处理不同） *///
//		case API_COMM_STATUS_RECV_OK:	
//		{
//			Gstr_UartComm[v_ucChID].ucCommChStatus = API_COMM_STATUS_TRANS_OK;	///* 转成转化完成状态，接收buff中的数据拷贝到发送buff中 *///
//			if ( CH_UART_UART0 == v_ucChID)	// 目前是485
//			{
//				LibPub_MemCopyBytes( &Gstr_UartComm[v_ucChID].ucaCommRXBuff[0], &Gstr_UartComm[v_ucChID].ucaCommTXBuff[0], Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN]+16 );
//			}
//			
//			if ( CH_UART_UART1 == v_ucChID)	// 目前是蓝牙
//			{
//				LibPub_MemCopyBytes( &Gstr_UartComm[v_ucChID].ucaCommRXBuff[17], &Gstr_UartComm[v_ucChID].ucaCommTXBuff[0], Gstr_UartComm[v_ucChID].ucaCommTXBuff[5] );	/*ucaCommTXBuff[5]为645数据帧的长度	*/				
//			}
//			
//		}break;

		///* 接收完成，可以开始解析数据帧了 *///
		case API_COMM_STATUS_RECV_OK:	
		{
			GStr_Monitor.ucCommSymbolTime = API_COMM_SYMBOL_TIME ;
			///* 响应时间在20ms-500ms之间 *///
			if (   (_TRUE == LibPub_GetDiffTime( Gstr_UartComm[v_ucChID].ulCommRspOverTime, LibPub_GetTimerBeat(), API_DLT645_FRAME_RSPN_TIME_MIN))
				 &&(_FALSE== LibPub_GetDiffTime( Gstr_UartComm[v_ucChID].ulCommRspOverTime, LibPub_GetTimerBeat(), API_DLT645_FRAME_RSPN_TIME_MAX)))
			{
				ApiComm_ProtocolProcess(v_ucChID);
			}
		}break;
		
		///* 通信错误，可以直接初始化 *///
		case API_COMM_STATUS_ERROR:		
		{
			V_ucInitUartFlg = _TRUE;
			/*完成帧解析并已经返回数据，判断是否有修改蓝牙mac参数标志*/
			if( BLE_STAT_MAC_MOD == GStr_Flag.ucBLESTATFlag )
			{
				GStr_Flag.ucBLESTATFlag = BLE_STAT_RST;	//蓝牙模块需要重启，重新设置参数
			}
		}break;
		
		///* 解析完了可以启动发送了 *///
		case API_COMM_STATUS_FRAME_OK:
		{
			Gstr_UartComm[v_ucChID].ucCommChStatus = API_COMM_STATUS_SEND;	///* 转成发送状态 *///
			Gstr_UartComm[v_ucChID].ulCommSndByteOverTime = LibPub_GetTimerBeat() ;
			
			// 配置串口为发送状态，发送一个字节，开启发送
			if ( CH_UART_UART0 == v_ucChID)	// 目前是485
			{
				ApiPwOn_UART_SendEn(CH_UART_UART0);
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
			
			if ( CH_UART_UART1 == v_ucChID)	// 目前是蓝牙
			{
				//BleDrv_WakeUpBle( BLE_TRMODE_UART ); // 唤醒一下蓝牙，串口传输	//不采用AT协议，取消唤醒口线
				ApiPwOn_UART_SendEn(CH_UART_UART1);
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
			
		}break;
		
		default:break; 
	}
	
	if ( V_ucInitUartFlg == _TRUE )	///* 初始化通道 *///
	{
		
		if ( CH_UART_UART0 == v_ucChID )
		{
			ApiPwOn_McuUartXInit(CH_UART_UART0);
		}
		else if ( CH_UART_UART1 == v_ucChID)
		{
			ApiPwOn_McuUartXInit(CH_UART_UART1);
		}
		
	}
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief   协议数据处理 
 *
 *  @param   chID: 通道ID
 *
 *  @return   none
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
static void ApiComm_ProtocolProcess( uchar8 v_ucChID )
{
	if ( API_COMM_STATUS_RECV_OK == Gstr_UartComm[v_ucChID].ucCommChStatus )
	{
		Gstr_UartComm[v_ucChID].ucCommChStatus = API_COMM_STATUS_FRAME;
		ApiDLT645_FrameAnalysis(v_ucChID);
	}
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief   通信参数状态寄存器初始化 
 *
 *  @param   chID: 通道ID
 *
 *  @return   none
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
#pragma SAVE
#pragma OT(0)
void ApiComm_CommParaInit( uchar8 v_ucChID )
{
//	if( CH_485 == v_ucChID )
//	{
//		if( Gstr_UartComm[v_ucChID].ucCommChStatus == API_COMM_STATUS_RECV )
//		{
//			NOP();
//			NOP();
//		}
//		if( Gstr_UartComm[v_ucChID].ucCommChStatus == API_COMM_STATUS_SEND )
//		{
//			NOP();
//			NOP();
//		}
//		if( Gstr_UartComm[v_ucChID].ucCommChStatus == API_COMM_STATUS_RECV_OK )
//		{
//			NOP();
//			NOP();
//		}
//		if( Gstr_UartComm[v_ucChID].ucCommChStatus == API_COMM_STATUS_FRAME )
//		{
//			NOP();
//			NOP();
//		}
//		if( Gstr_UartComm[v_ucChID].ucCommChStatus == API_COMM_STATUS_FRAME_OK )
//		{
//			NOP();
//			NOP();
//		}
//	}
	
	Gstr_UartComm[v_ucChID].ucCommChStatus = API_COMM_STATUS_IDLE;
	Gstr_UartComm[v_ucChID].ucCommRevStep  = API_COMM_STEP0;
	Gstr_UartComm[v_ucChID].ucCommRevLen   = 0;
	Gstr_UartComm[v_ucChID].ucCommSndLen   = 0;
	Gstr_UartComm[v_ucChID].ucCommSndCnt   = 0;
	Gstr_UartComm[v_ucChID].ulCommTimeInit = LibPub_GetTimerBeat();
	Gstr_UartComm[v_ucChID].ulCommRcvByteOverTime = 0;
	Gstr_UartComm[v_ucChID].ulCommSndByteOverTime = 0;
	Gstr_UartComm[v_ucChID].ulCommRspOverTime = 0 ;
	Gstr_UartComm[v_ucChID].ucCommAddrType = F_COMMADDRTYPE_NULL;
	Gstr_UartComm[v_ucChID].ucCommError = API_DLT645_COMM_ERR_OK;
}
#pragma RESTORE