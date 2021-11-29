/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    AppMeasure.h                                                                          
**** Brief:       计量相关操作头文件                                                                      
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

#ifndef   _APPMEASURE_H
#define   _APPMEASURE_H

/*-------------------------------- H文件使用说明 -------------------------------------------------------*/
/*
 *  该文件宏定义的前缀为:
 *
 */

 
/*----------------< 包含文件 >----------------------------------*/


/*----------------< 宏定义区 >----------------------------------*/


/*----------------< 变量声明 >----------------------------------*/


/*----------------< 函数声明 >----------------------------------*/
extern void ApiMS_UpdateUIP(void);
extern void ApiMS_MeasureTask(void);
extern void ApiMS_EnergyPulseUpdate(void);
extern uchar8 ApiMS_EnergyProcess( GStr_ENERGY_PULSE_Type *p_strEnergyPulse );
extern uchar8 ApiMS_CalibrationMeterComm( uchar8 v_ucChID );
extern void ApiMS_InitMeterICPara( void );
extern void ApiMS_MeterICParaCheck( void );
extern void ApiMS_DisOrEnable( uchar8 v_ucWorkMode);



#endif
