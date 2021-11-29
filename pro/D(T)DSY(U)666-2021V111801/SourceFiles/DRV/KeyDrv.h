/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    KeyDrv.c                                                                          
**** Brief:       按键驱动头文件                                                                      
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

#ifndef   _KEYDRV_H
#define   _KEYDRV_H

/*-------------------------------- H文件使用说明 -------------------------------------------------------*/
/*
 *  该文件宏定义的前缀为:
 *
 */

 
/*----------------< 包含文件 >----------------------------------*/


/*----------------< 宏定义区 >----------------------------------*/

#define	LCD_DISP_Keydelay_TIME		8	///* 按键去抖时间40ms *///

#if( METER_TYPE == METER_TYPE_DDSY666 )
	/* I_J短接点 */
	#define	FACTORYMODE_KEY_INPUT()		GPIO_IOCFG_P5_DIR_I(2)
	#define	FACTORYMODE_KEY_UPON()		GPIO_IOCFG_P5_PUP_O(2)
	#define	FACTORYMODE_KEY_HIGHT		GPIO_IOCFG_P5_STAT_H(2)
	#define	FACTORYMODE_KEY_LOW			GPIO_IOCFG_P5_STAT_L(2)
	/* 轮显按键 */
	#define	DISPLAY_KEY_INPUT()			GPIO_IOCFG_P2_DIR_I(2)
	#define	DISPLAY_KEY_UPON()			GPIO_IOCFG_P2_PUP_O(2)
	#define	DISPLAY_KEY_HIGHT			GPIO_IOCFG_P2_STAT_H(2)
	#define	DISPLAY_KEY_LOW				GPIO_IOCFG_P2_STAT_L(2)
#endif


#if( METER_TYPE == METER_TYPE_DTSY666 )
	/* I_J短接点 */
	#define	FACTORYMODE_KEY_INPUT()		GPIO_IOCFG_P5_DIR_I(2)
	#define	FACTORYMODE_KEY_UPON()		GPIO_IOCFG_P5_PUP_O(2)
	#define	FACTORYMODE_KEY_HIGHT		GPIO_IOCFG_P5_STAT_H(2)
	#define	FACTORYMODE_KEY_LOW			GPIO_IOCFG_P5_STAT_L(2) 
	/* 轮显按键 */
	#define	DISPLAY_KEY_INPUT()			GPIO_IOCFG_P1_DIR_I(0)
	#define	DISPLAY_KEY_UPON()			GPIO_IOCFG_P1_PUP_O(0)
	#define	DISPLAY_KEY_HIGHT			GPIO_IOCFG_P1_STAT_H(0)
	#define	DISPLAY_KEY_LOW				GPIO_IOCFG_P1_STAT_L(0)
#endif

#if( METER_TYPE == METER_TYPE_DDSYU666 )// 导轨表没有I-J短接点
	/* I_J短接点 */
	#define	FACTORYMODE_KEY_INPUT()		NOP();//GPIO_IOCFG_P5_DIR_I(2)	//
	#define	FACTORYMODE_KEY_UPON()		NOP();//GPIO_IOCFG_P5_PUP_O(2)
	#define	FACTORYMODE_KEY_HIGHT		NOP();//GPIO_IOCFG_P5_STAT_H(2)
	#define	FACTORYMODE_KEY_LOW			NOP();//GPIO_IOCFG_P5_STAT_L(2)
	/* 轮显按键 */
	#define	DISPLAY_KEY_INPUT()			GPIO_IOCFG_P3_DIR_I(2)
	#define	DISPLAY_KEY_UPON()			GPIO_IOCFG_P3_PUP_O(2)
	#define	DISPLAY_KEY_HIGHT			GPIO_IOCFG_P3_STAT_H(2)
	#define	DISPLAY_KEY_LOW				GPIO_IOCFG_P3_STAT_L(2)
#endif
/*----------------< 变量声明 >----------------------------------*/


/*----------------< 函数声明 >----------------------------------*/
extern void DrvKey_FactoryKeyMonitor(void);
extern void DrvKey_DisplayKeyInit(void);
extern void DrvKey_DisplayKeyMonitor(void);





#endif
