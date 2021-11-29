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

#ifndef   _APPVIRTUALESAM_H
#define   _APPVIRTUALESAM_H

/*-------------------------------- H文件使用说明 -------------------------------------------------------*/
/*
 *  该文件宏定义的前缀为:
 *
*/

 
/*----------------< 包含文件 >----------------------------------*/


/*----------------< 宏定义区 >----------------------------------*/
#define C_AvailTimer         5

/*----------------< 变量声明 >----------------------------------*/


typedef struct 
{											
	uchar8 ucTempKey[16];      						    ///* 临时密钥        *///
	uchar8 ucDisKey[16];      						    ///* 分散密钥        *///
	uchar8 ucComplexKey[16];      						///* 复杂密钥        *///
	uchar8 ucRs485RandNum[8];  						    ///* 485认证随机数2  *///
	uchar8 ucRs485RandNum2[8];     						    ///* 提前获取的随机数2  *///
}Gstr_VirtualEsam;               

extern uchar8 GV_ucMACErrNum;
extern Gstr_VirtualEsam   GStr_VirtualEsamPara;
/*----------------< 函数声明 >----------------------------------*/
extern void PrepaymentModule_Comm_ClrMACErrNum();
extern uchar8 PrepaymentModule_Comm_INTAUTH(uchar8 *P_ucDataPtr);
extern uchar8 PrepaymentModule_DataDecription(uchar8 *P_DataPtr, uchar8 V_ucMACType, uchar8 *P_ucLen);
extern uchar8 PrepaymentModule_GetChallenge(uchar8 *P_DataPtr, uchar8 V_DataLen);
#endif

