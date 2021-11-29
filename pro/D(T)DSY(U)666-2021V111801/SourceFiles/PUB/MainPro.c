/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    MainPro.c                                                                          
**** Brief:       主函数入口文件                                                                      
**** Author:      peter.he@chint.com                                                                 
**** Version:     V1.0                                                                               
**** Date:        2019年3月14日                                                                          
****                                                                                                 
**** note:                                         
**** 1.  Author:                                                                                     
****     Version:                                                                                    
****     Date :                                                                                      
**** 2.  Author:                                                                                     
****     Version:                                                                                       
****     Date:
****                                                                                        
****                                                             
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

#include "..\SourceFiles\SH79F7021A\SH79F7021AE.h"
#include "..\SourceFiles\PUB\Include.h"
/*----------------< 信息说明 >----------------------------------*/

#ifdef DDSYU666	// 单相导轨表
	#message "Meter Type:DDSYU666 " 
#endif

#ifdef DDSY666	// 单相壁挂表
	#message "Meter Type:DDSY666 " 
#endif

#ifdef DTSY666	// 三相壁挂表
	#message "Meter Type:DTSY666" 
#endif
	
/*----------------< 宏定义区 >----------------------------------*/


/*----------------< 常量定义 >----------------------------------*/


/*----------------< 变量定义 >----------------------------------*/


/*----------------< 函数声明 >----------------------------------*/


/*----------------< 函数定义 >----------------------------------*/
//#pragma warning(disable:15)
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    调试函数
 *
 *  @return   无返回
 *
 *  @note     
 *
 */
/*------------------------------------------------------------------------------------------------------*/
//#pragma SAVE
//#pragma OT(0)
//void test(void)
//{ 		
//    ushort16 V_TempData;
//	
//	 LibPub_ReadDataFromE2prom( LIB_E2P_EventNum, 0, (uchar8*)&GStr_EventRecordNum.ucEventTimes[0][0]);
//	V_TempData=LIB_E2P_ENRGY_Addr	;
//	V_TempData=LIB_E2P_Money_Addr	;
//	V_TempData=LIB_E2P_Price_Addr;
//	V_TempData=LIB_E2P_EMU_CALPARA_Addr;
//	V_TempData=LIB_E2P_EMU_UIPKms_Addr;
//	V_TempData=LIB_E2P_FUN_CONFIG_Addr;
//	V_TempData=LIB_E2P_ENERGY_DECPULSE_FW_Addr;
//	V_TempData=LIB_E2P_ENERGY_DECPULSE_BK_Addr;
//	V_TempData=LIB_E2P_ENERGY_DECPULSE_WS_Addr;
//	V_TempData=LIB_E2P_RUN_STATE_Addr;
//	V_TempData=LIB_E2P_METER_INFO_Addr;
//	V_TempData=LIB_E2P_Money_Para_Addr;
//	V_TempData=LIB_E2P_Password_Addr;
//	V_TempData=LIB_E2P_SecretKey_Addr;
//	V_TempData=LIB_E2P_SOFTI_J_Addr;
//	V_TempData=LIB_E2P_AvailTimer_Addr;
//	V_TempData=LIB_E2P_EventNumPiont_Addr;	
//	V_TempData=LIB_E2P_EventValidPiont_Addr;	
//	V_TempData=LIB_E2P_EventNum_Addr;	
//	V_TempData=LIB_E2P_EventNum_Addr;	
//	uchar8 LPDCON2BAK;
//	NOP();
//	NOP();
//	LPDCON2BAK = LPDCON2;
//	NOP();
//	NOP();
//	ApiPwOn_MeterInitInFactory();
//	NOP();
//	NOP();
//	RelayDrv_Closerelay() ;
//	NOP();
//	NOP();
//	RelayDrv_Openrelay();
//	NOP();
//	NOP(); 
//}
 
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    主函数，系统上电跑完STARTUP以后，从这里开始运行
 *
 *  @return   无返回
 *
 *  @note    : SH79F7021是大端模式，即数据的高字节保存在内存的低地址中，而数据的低字节保存在内存的高地址中，如
 *             定义4字节的共用体，高字节存储对应BUF[0]
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void main(void)
{ 
// @brief ---上电系统配置，配置失败就复位一下单片机
	if( _FAILED == ApiPwOn_SysTemInit() )
	{
		ApiPwOn_McuReset( );
	}
	


// 	ApiPwOn_MeterInitInFactory();
// @brief --- 正常上电后，进入主循环
	for( ; ; )
	{ 
		// @brief --- 看门狗互锁		
		if( GStr_Monitor.ulTimerClrWDT !=   LibPub_GetTimerBeat() )
		{
			WDT_Clr();
		}
		GStr_Monitor.ulTimerClrWDT = LibPub_GetTimerBeat();
		
		// @brief --- 开始任务查询
		
		
		ApiMS_MeasureTask();			///* 计量任务，如刷新瞬时量、参数校验等等 *///
		
		ApiComm_CommTask();				///* 通信任务处理 *///
		
		ApiPwOff_PowerOffTask();		///* 掉电检测任务，每一个循环都检测 *///		
//		
//		ApiTou_TOUTask();				///* 定时任务处理，如节拍定时等 *///
//		
		ApiDisp_DisplayTask();			///* 显示任务处理，如刷新显示 *///
		  
		ApiMntr_MonitorTask();			///* 监控任务处理 *///  
 
		//test();
	}
}




