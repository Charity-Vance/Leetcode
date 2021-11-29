/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    AppComm.h                                                                         
**** Brief:       通信处理头文件                                                                      
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

#ifndef   APPCOMM_H
#define   APPCOMM_H

/*-------------------------------- H文件使用说明 -------------------------------------------------------*/
/*
 *  该文件宏定义的前缀为:
 *
 */

 
/*----------------< 包含文件 >----------------------------------*/


/*----------------< 宏定义区 >----------------------------------*/
#define	API_COMM_STEP0			0
#define	API_COMM_STEP1			1
#define	API_COMM_STEP2			2
#define	API_COMM_STEP3			3
#define	API_COMM_STEP4			4
#define	API_COMM_STEP5			5
#define	API_COMM_STEP6			6
#define	API_COMM_STEP7			7
#define	API_COMM_STEP8			8
#define	API_COMM_STEP9			9
 


///* Gstr_UartComm.ucCommChStatus *///
typedef enum{	
	API_COMM_STATUS_IDLE = 1,			///* 空闲状态 *///
	API_COMM_STATUS_SEND,				///* 发送状态 *///
	API_COMM_STATUS_RECV,				///* 接收状态 *///
	API_COMM_STATUS_RECV_OK,			///* 接收完成 *///
//	API_COMM_STATUS_TRANS_OK,			///* 转化完成 *///
	API_COMM_STATUS_OVERTIME,			///* 超时状态 *///
	API_COMM_STATUS_FRAME,				///* 帧解析状态 *///
	API_COMM_STATUS_FRAME_OK,			///* 帧解析状完成 *///
	API_COMM_STATUS_ERROR,				///* 错误状态 *///
}ENUM_API_COMM_STATUS;

#define	API_COMM_SYMBOL_TIME		10	///* 通信符号闪烁时间，500ms闪烁一次 *///

/*----------------< 变量声明 >----------------------------------*/

/*----------------< 函数声明 >----------------------------------*/
extern void ApiComm_CommParaInit( uchar8 v_ucChID );
extern void ApiComm_CommTask(void);




#endif
