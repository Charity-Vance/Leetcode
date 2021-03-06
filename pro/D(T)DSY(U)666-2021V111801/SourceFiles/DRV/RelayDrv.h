/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    RELAYDRV.h                                                                          
**** Brief:       继电器驱动头文件                                                                     
**** Author:      peter.he@chint.com                                                                 
**** Version:     V1.0                                                                               
**** Date:        2019年3月14日                                                                         
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

#ifndef   _RELAYDRV_H
#define   _RELAYDRV_H

/*-------------------------------- H文件使用说明 -------------------------------------------------------*/
/*
 *  该文件宏定义的前缀为:
 *
 */

 
/*----------------< 包含文件 >----------------------------------*/


/*----------------< 宏定义区 >----------------------------------*/


/*----------------< 变量声明 >----------------------------------*/
#define  RelayOnce_Delaytimer        200*3       ///继电器判断周期
#define  RelayDrvDrv_Delaytimer      RelayOnce_Delaytimer-24       ///内控口线置位时间120ms
#if ( METER_TYPE == METER_TYPE_DTSY666)
#define  RelayOutsideDrv_Delaytimer      RelayOnce_Delaytimer-200       ///外控口线置位时间120ms
#endif

/*----------------< 函数声明 >----------------------------------*/
extern void RelayDrv_Closerelay();
extern void RelayDrv_Openrelay();
extern void RelayDrv_DelayTimeMonitor();



#endif
