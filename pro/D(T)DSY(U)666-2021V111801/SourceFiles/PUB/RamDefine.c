/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    RamDefine.c                                                                          
**** Brief:       系统变量定义                                                                     
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
GStr_FLAG_Type					GStr_Flag;
GStr_ENERGY_PULSE_Type 			GStr_EnergyPulseFw,GStr_EnergyPulseBk;
GStr_ENERGY_Type 				GStr_Energy; 
GStr_MONITOR_Tpye				GStr_Monitor;
GStr_DISPLAY_PARA_Type			GStr_DisplayPara;
GStr_COUNTER_Type				GStr_Counter;
GStr_UART_COMM_Type				Gstr_UartComm[UART_CHNUMS];	///* 根据通道数量定义 *///
GStr_METER_IFO_Type				GStr_MeterIFO;
GStr_FUN_CONFIG_Type			GStr_FunConfigPara;	///* 功能配置项 *///
GStr_MONEY_PARA_Type            GStr_MoneyPara;
GStr_MONEY_Type                 GStr_Money;
GStr_PRICE_Type                 GStr_PRICE;
GStr_ENERGYDEC_Type             GStr_ENERGYDEC;
GStr_AVAIL_Type                 GStr_AVAIL;
GStr_UIP_GROUP_Type     		GStr_UIPGroup;		/// 瞬时量 *///
GStr_BLE_GROUP_Type     		GStr_BLEGroup;		// 蓝牙模组参数
GStr_UIP_DISPLAY_Type           GStr_UIPDisplay;
GStr_EventNumPiont_Type         GStr_EventNumPiont;
GStr_EventValidPiont_Type       GStr_EventValidPiont;
GStr_EventRecordNum_Type        GStr_EventRecordNum;

//uchar8 ucBletargetMAC[6];			// 目标设备地址蓝牙Mac地址，6字节wxy


/*----------------< 函数声明   >----------------------------------*/


/*----------------< 函数定义 >----------------------------------*/



