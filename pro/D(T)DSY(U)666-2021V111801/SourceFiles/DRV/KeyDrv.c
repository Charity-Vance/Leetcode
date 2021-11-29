/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    KeyDrv.c                                                                          
**** Brief:       按键驱动文件                                                                      
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


/*----------------< 常量定义 >----------------------------------*/


/*----------------< 变量定义 >----------------------------------*/


/*----------------< 函数声明 >----------------------------------*/
void DrvKey_FactoryKeyInit(void);
void DrvKey_DisplayKeyInit(void);

void DrvKey_FactoryKeyMonitor(void);
void DrvKey_DisplayKeyMonitor(void);
/*----------------< 函数定义 >----------------------------------*/


/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    工厂模式短接点初始化，主要配置短接点输入输出及口线功能
 *
 *  @return   NONE
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void DrvKey_FactoryKeyInit(void)
{
	FACTORYMODE_KEY_INPUT();	// 配置成输入
	FACTORYMODE_KEY_UPON();		// 上拉开起来
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    轮显按键初始化，主要配置轮显按键输入输出及口线功能
 *
 *  @return   NONE
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void DrvKey_DisplayKeyInit(void)
{
	DISPLAY_KEY_INPUT();	// 配置成输入
	DISPLAY_KEY_UPON();		// 上拉开起来
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    工厂模式查询
 *
 *  @return   NONE
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/

void DrvKey_FactoryKeyMonitor(void)
{
	// @brief    配置一下口线
	DrvKey_FactoryKeyInit();
	#if( METER_TYPE == METER_TYPE_DDSYU666 )
	{  
		GStr_Flag.ucFactoryKey |=  F_KEY_ACKTION_DOWN; // 导轨表没有I_J短接点，直接认为就可以通过命令进厂内
	}
	#else
	{	
		///*直接判断口线
		if(FACTORYMODE_KEY_LOW)
		{
			GStr_Counter.ucFactoryMode_Cnt++;
			if(GStr_Counter.ucFactoryMode_Cnt>=250)
			{
				GStr_Counter.ucFactoryMode_Cnt=0;
				GStr_Flag.ucFactoryKey |=  F_KEY_ACKTION_DOWN; 	
			}
		}
		else
		{
			GStr_Counter.ucFactoryMode_Cnt=0;
			GStr_Flag.ucFactoryKey &=  ~F_KEY_ACKTION_DOWN;
		}
	}
	#endif
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    轮显按键查询
 *
 *  @return   NONE
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void DrvKey_DisplayKeyMonitor(void)
{
	// @brief    配置一下口线
	DrvKey_DisplayKeyInit();  

	// @brief    检查一下口线状态
	if( F_KEY_STATUS_IDLE & GStr_Flag.ucDispKey )	// 如果口线状态是空闲
	{
		if( DISPLAY_KEY_LOW )	// 按键按下，状态改变
		{
			GStr_Flag.ucDispKey |= F_KEY_ACKTION_DOWN;
			GStr_Flag.ucDispKey &= (~F_KEY_STATUS_IDLE);
			GStr_DisplayPara.ucKeydelaytimer = 0;
		}  
	}
	else if( F_KEY_ACKTION_DOWN & GStr_Flag.ucDispKey )
	{
		if( DISPLAY_KEY_LOW )	// 开始要消抖,消抖时间由LCD_DISP_Keydelay_TIME控制
		{
			GStr_DisplayPara.ucKeydelaytimer++;
			if( LCD_DISP_Keydelay_TIME <= GStr_DisplayPara.ucKeydelaytimer )
			{
				GStr_Flag.ucDispKey |= F_KEY_STATUS_TRUE;
				GStr_Flag.ucDispKey &= (~F_KEY_ACKTION_DOWN);
				
				GStr_DisplayPara.ucKeydelaytimer = 0;
				GStr_Flag.ucDisp |= F_DISP_KEYDISP;					// 进入按键轮显
				GStr_DisplayPara.ulDisptimer = LCD_DISP_Key_TIME*2/LCD_UPTATA_TIME;	// 按键显示持续时间
				GStr_DisplayPara.ucBackLightTime = LCD_DISP_Key_TIME/LCD_UPTATA_TIME;	// 背光显示持续时间
				
				if( GStr_DisplayPara.ucFirstKeyDisp == 0 )			// 第一次循环显示,从第一屏开始显示
				{
					GStr_DisplayPara.ucDispNum = 0 ;
					GStr_DisplayPara.ucFirstKeyDisp = 0x68;			// 非第一次按键显示标志
				}
				else                                 				// 不是第一次按键显示，显示屏号加1
				{
					GStr_DisplayPara.ucDispNum++;
					if( GStr_DisplayPara.ucDispNum >= GStr_DisplayPara.ucKeyDispNum )
					{
						GStr_DisplayPara.ucDispNum = 0;
					}
				}		
			}
		}
		else
		{
			GStr_DisplayPara.ucKeydelaytimer = 0;
			GStr_Flag.ucDispKey = F_KEY_STATUS_IDLE;
		}
		
	}
	else if( F_KEY_STATUS_TRUE & GStr_Flag.ucDispKey )
	{
		if( DISPLAY_KEY_HIGHT )
		{
			GStr_DisplayPara.ucKeydelaytimer = 0;
			GStr_Flag.ucDispKey = F_KEY_STATUS_IDLE;
		}
	}
	else
	{
		GStr_DisplayPara.ucKeydelaytimer=0;
		GStr_Flag.ucDispKey = F_KEY_STATUS_IDLE;
	}
	
}


