/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    AppPowerOn.h                                                                         
**** Brief:       上电系统配置                                                                      
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

#ifndef   _APPRELAYCONTROL_H
#define   _APPRELAYCONTROL_H

/*-------------------------------- H文件使用说明 -------------------------------------------------------*/
/*
 *  该文件宏定义的前缀为:
 *
*/

 
/*----------------< 包含文件 >----------------------------------*/


/*----------------< 宏定义区 >----------------------------------*/
#if(METER_TYPE==METER_TYPE_DTSY666)
#define API_Relayact_Voltage			22*83		//三相表只加一相电压时，判断是否动作的电压阀值 220V*0.83=1826V
#endif


/*----------------< 变量声明 >----------------------------------*/


/*----------------< 函数声明 >----------------------------------*/
extern  void ApiRelay_ControlProcess(void);
	    	
extern void ApiRelay_SubtractMoneyRelayJudge(void);
extern void Api_PowerLoadLimitedCheck(void);


#endif

