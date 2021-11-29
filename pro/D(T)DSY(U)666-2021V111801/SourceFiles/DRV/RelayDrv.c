/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    RelayDrv.c                                                                          
**** Brief:       继电器驱动函数                                                                     
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
#if( METER_TYPE == METER_TYPE_DDSY666 )
	#define	RELAY1_ON()				 GPIO_IOCFG_P0_SET_1(1) 	// relay1口线置1   P0.1
	#define	RELAY1_OFF()			 GPIO_IOCFG_P0_SET_0(1) 	//  relay1口线置0
	#define	RELAY2_ON()				 GPIO_IOCFG_P0_SET_1(2) 	//  relay2口线置1   P0.2
	#define	RELAY2_OFF()			 GPIO_IOCFG_P0_SET_0(2) 	//  relay2口线置0
#endif

#if( METER_TYPE == METER_TYPE_DTSY666 )
	#define	RELAY1_ON()				 GPIO_IOCFG_P0_SET_1(1) 	// relay1口线置1   P0.1
	#define	RELAY1_OFF()			 GPIO_IOCFG_P0_SET_0(1) 	//  relay1口线置0
	#define	RELAY2_ON()				 GPIO_IOCFG_P0_SET_1(2) 	//  relay2口线置1   P0.2
	#define	RELAY2_OFF()			 GPIO_IOCFG_P0_SET_0(2) 	//  relay2口线置0
	#define RELAYOUT_WORK()          GPIO_IOCFG_P0_SET_1(7)
	#define RELAYOUT_NORAML()        GPIO_IOCFG_P0_SET_0(7) 
#endif

#if( METER_TYPE == METER_TYPE_DDSYU666 )
	#define	RELAY1_ON()				 GPIO_IOCFG_P0_SET_1(3) 	// relay1口线置1   P0.3
	#define	RELAY1_OFF()			 GPIO_IOCFG_P0_SET_0(3) 	//  relay1口线置0
	#define	RELAY2_ON()				 GPIO_IOCFG_P0_SET_1(2) 	//  relay2口线置1   P0.2
	#define	RELAY2_OFF()			 GPIO_IOCFG_P0_SET_0(2) 	//  relay2口线置0
#endif
/*----------------< 常量定义 >----------------------------------*/



/*----------------< 变量定义 >----------------------------------*/

/*----------------< 函数声明 >----------------------------------*/
void RelayDrv_Closerelay();
void RelayDrv_Openrelay();
void RelayDrv_DelayTimeMonitor();

static void RelayDrv_RelayNormal();
/*----------------< 函数定义 >----------------------------------*/

void RelayDrv_Closerelay()               //合闸
{

	RELAY1_OFF();
	_nop_();
	_nop_();
	RELAY2_ON()	;

	#if ( METER_TYPE == METER_TYPE_DTSY666)
	RELAYOUT_NORAML();///同时操作外控口线
	#endif
	
}



void RelayDrv_Openrelay()              //跳闸
{

	RELAY1_ON();
	_nop_();
    _nop_();
	RELAY2_OFF();

	#if ( METER_TYPE == METER_TYPE_DTSY666)
	RELAYOUT_WORK() ;///同时操作外控口线
	#endif
	
}

void RelayDrv_RelayNormal()   ///口线回归常态
{
	RELAY1_OFF();
	_nop_();
	RELAY2_OFF();
	#if ( METER_TYPE == METER_TYPE_DTSY666)
	RELAYOUT_NORAML();///同时操作外控口线///同时操作外控口线
	#endif
}

void RelayDrv_DelayTimeMonitor()   ///
{
	if(GStr_Counter.ucRelayDelay_Cnt)
	{	
		GStr_Counter.ucRelayDelay_Cnt--;
		if(GStr_Counter.ucRelayDelay_Cnt==RelayDrvDrv_Delaytimer)///内控口线置位
		{
			RelayDrv_RelayNormal();
		}
		#if ( METER_TYPE == METER_TYPE_DTSY666)
		if(GStr_Counter.ucRelayDelay_Cnt==RelayOutsideDrv_Delaytimer)///外控口线置位
		{
			RelayDrv_Closerelay();
		}
		#endif
	}
	else
	{
		RelayDrv_RelayNormal();
	}
}