/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    INTERNALE2DRV.H                                                                        
**** Brief:       类E2驱动头文件                                                                      
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

#ifndef   INTERNALE2DRV_H
#define   INTERNALE2DRV_H

/*-------------------------------- H文件使用说明 -------------------------------------------------------*/
/*
 *  该文件宏定义的前缀为:
 *
 */

 
/*----------------< 包含文件 >----------------------------------*/


/*----------------< 宏定义区 >----------------------------------*/
#define	FLASH_RW_ENABLE			0X68
#define	FLASH_RW_DISENABLE		0X00

#define	FLASH_RW_ENABLE_STEP1	0X08
#define	FLASH_RW_ENABLE_STEP2	0X20
#define	FLASH_RW_ENABLE_STEP3	0X40

/*----------------< 变量声明 >----------------------------------*/


/*----------------< 函数声明 >----------------------------------*/

extern void Hal_WriteFlash_byte(INT16U adr, INT8U dat, INT8U sta);
extern INT8U Hal_ReadFlash_byte(INT16U adr, INT8U sta);
extern INT8U Hal_ReadEEPROM(INT8U  *Dst, INT16U Src, INT16U Len);


#endif
