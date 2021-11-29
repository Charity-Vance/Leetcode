/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    AppDisplay.h                                                                          
**** Brief:       显示模块                                                                      
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

#ifndef   _APPDISPLAY_H
#define   _APPDISPLAY_H

/*-------------------------------- H文件使用说明 -------------------------------------------------------*/
/*
 *  该文件宏定义的前缀为:
 *
 */

 
/*----------------< 包含文件 >----------------------------------*/


/*----------------< 宏定义区 >----------------------------------*/
#if( METER_TYPE == METER_TYPE_DDSY666 )
	#define  LCDLEDON()  		{ GPIO_IOCFG_P9_DIR_O(1);GPIO_IOCFG_P9_SET_0(1); } // 背光点亮  
	#define  LCDLEDOFF()  		{ GPIO_IOCFG_P9_DIR_O(1);GPIO_IOCFG_P9_SET_1(1); } // 背光不点亮  
	#define  RELAYLEDON()  		{ GPIO_IOCFG_P1_DIR_O(3);GPIO_IOCFG_P1_SET_0(3); } // 报警灯点亮  
	#define  RELAYLEDOFF()  	{ GPIO_IOCFG_P1_DIR_O(3);GPIO_IOCFG_P1_SET_1(3); } // 报警灯不点亮  
#endif

#if( METER_TYPE == METER_TYPE_DTSY666 )
	#define  LCDLEDON()  		{ GPIO_IOCFG_P9_DIR_O(1);GPIO_IOCFG_P9_SET_0(1); } // 背光点亮  
	#define  LCDLEDOFF()  		{ GPIO_IOCFG_P9_DIR_O(1);GPIO_IOCFG_P9_SET_1(1); } // 背光不点亮  
	#define  RELAYLEDON()  		{ GPIO_IOCFG_P1_DIR_O(3);GPIO_IOCFG_P1_SET_0(3); } // 报警灯点亮  
	#define  RELAYLEDOFF()  	{ GPIO_IOCFG_P1_DIR_O(3);GPIO_IOCFG_P1_SET_1(3); } // 报警灯不点亮  
#endif
	
#if( METER_TYPE == METER_TYPE_DDSYU666 )
	#define  LCDLEDON()  		{ GPIO_IOCFG_P0_DIR_O(1);GPIO_IOCFG_P0_SET_1(1); } // 背光点亮  
	#define  LCDLEDOFF()  		{ GPIO_IOCFG_P0_DIR_O(1);GPIO_IOCFG_P0_SET_0(1); } // 背光不点亮  
	#define  RELAYLEDON()  		{ GPIO_IOCFG_P0_DIR_O(7);GPIO_IOCFG_P0_SET_1(7); } // 报警灯点亮  
	#define  RELAYLEDOFF()  	{ GPIO_IOCFG_P0_DIR_O(7);GPIO_IOCFG_P0_SET_0(7); } // 报警灯不点亮  
#endif
/*----------------< 变量声明 >----------------------------------*/

/*----------------< 函数声明 >----------------------------------*/
extern void ApiDisp_DisplayTask(void);
extern uchar8 ApiGet_Lcd_Num(ulong32 DataId,uchar8 ScreenNum);
extern ulong32 ApiGet_Lcd_ID(uchar8 v_LcdNum);
void LCDDrv_DispRamUpdata(void);
void LCDDrv_SetLcdBuff( uchar8 v_ucVal );
extern void APiDisp_LcdledControl();





#endif
