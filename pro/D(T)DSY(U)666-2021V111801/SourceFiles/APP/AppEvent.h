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

#ifndef   _APPEVENT_H
#define   _APPEVENT_H

/*-------------------------------- H文件使用说明 -------------------------------------------------------*/
/*
 *  该文件宏定义的前缀为:
 *
*/

 
/*----------------< 包含文件 >----------------------------------*/


/*----------------< 宏定义区 >----------------------------------*/

#define	C_Clear				     0x00     //电表清零
#define	C_BuyMoney           	 0x01     //购电
#define	C_Program           	 0x02     //编程
#define	C_RejectMoney	         0x03     //退费
#define	C_OpenRelay	    	     0x04     //拉闸
#define	C_CloseRelay	         0x05     //合闸
#define C_EventMaxNum                 10 ///事件最大次数  
#define C_EventValidPoint_Lenth   6 //支持的事件数
///类EE存储地址：
#define  CAddr_Cleardl_Note    0x0000u   
 #define  CAddr_Cleardl_Note_Lenth  12  ///操作者代码 4  清零前正向+反向     ////时间不保存默认回全FF，分相电能也不保存

#define  CAddr_SelfMoney_Note       0x0200u
 #define CAddr_SelfMoney_Lenth   18    ///上一次购电后购电次数 2  购电金额4  购电前剩余金额 4  购电后剩余金额4  购电后累计购电金额4

#define  CAddr_Program_Note    0x0400u
  #define  CAddr_Program_Note_Lenth  44 ///操作者代码4 +10个操作数据标识

#define  CAddr_RejectMoney_Note    0x0600u
  #define  CAddr_RejectMoney_Lenth  14 ///退费前购电次数   2   退费金额 4  退费前剩余金额4  退费后剩余金额4

#define  CAddr_OpenRelay_Note    0x0800u
  #define  CAddr_E2OpenRelay_Lenth  12 ///操作者代码 跳闸时正向有功电能、反向有功电能
 
#define  CAddr_CloseRelay_Note    0x0A00u
  #define  CAddr_E2CloseRelay_Lenth  12 ///操作者代码 跳闸时正向有功电能、反向有功电能

/*----------------< 变量声明 >----------------------------------*/
		 		//事件结构体// 
typedef struct{
	ushort16	V_usEventID;			//DI2DI1标识
	ushort16 	V_usEventAddr; 	 		//事件首条记录的类EE地址//
	uchar8		V_ucEventLenth;			//事件记录内容长度
}GStr_EventParaData;

extern uchar8 xdata GA_ucEventRecordBuff[60];///事件记录缓存
extern uchar8 xdata GA_ucDICode[4];///编程数据标识
extern uchar8 xdata GA_ucOperCode[4];///操作者代码
extern uchar8 xdata GA_ucRelayOperCode[4];///拉合闸操作者代码
/*----------------< 函数声明 >----------------------------------*/

extern void ApiEvent_WriteRecord(uchar8 v_ucEventType);
extern uchar8 ReadEventRecordData(ulong32 V_ulProgDIx,uchar8 *DataPoint,uchar8 *PtrDataLen);
#endif

