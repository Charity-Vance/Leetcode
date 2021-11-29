/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    LCDDrv.c                                                                          
**** Brief:       LCD驱动文件                                                                     
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
static void LCDDrv_SgeComConfig(void);
static void LCDDrv_SetLcdBuff( uchar8 v_ucVal );
static void LCDDrv_PwOnRegCfg(void);
//static void LCDDrv_DispRamUpdata(void);

void LCDDrv_Init( uchar8 v_ucPowerStatus );
/*----------------< 函数定义 >----------------------------------*/

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    LCD初始化，上电或者下电
 *
 *  @param    xx :
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/

void LCDDrv_Init( uchar8 v_ucPowerStatus )
{
	
	switch( v_ucPowerStatus )
	{
		case POWER_ON:		// 上电状态LCD初始化
		{
			LCD_OFF()				// 关闭显示模块
			LCDDrv_PwOnRegCfg();	// 配置寄存器
			LCDDrv_SgeComConfig(); 	// 配置IO
			LCDDrv_SetLcdBuff(0xFF);// 缓存清零
			LCD_ON();				// 打开显示模块
			RELAYLEDON();///液晶点亮的同时点亮跳闸灯
			LCDLEDON();
		    
			

		}break;
		
		case POWER_OFF:		// 掉电状态LCD初始化
		{
			LCD_OFF()				// 关闭显示模块
			LCDDrv_PwOnRegCfg();	// 配置寄存器
			LCDDrv_SgeComConfig(); 	// 配置IO
			LCDDrv_SetLcdBuff(0x00);// 缓存清零
			
		}break;
		
		default:break;
	} 
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    将口线配置成LCD显示功能
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void LCDDrv_SgeComConfig(void)
{
#if( METER_TYPE == METER_TYPE_DDSY666 )
	P4SS = P4SS_P4S7 | P4SS_P4S6 | P4SS_P4S5 | P4SS_P4S4;
	P5SS = P5SS_P5S1 | P5SS_P5S0; 
	P6SS = P6SS_P6S7 | P6SS_P6S6 | P6SS_P6S5 | P6SS_P6S4 | P6SS_P6S3 | P6SS_P6S2 | P6SS_P6S1; 
	P7SS = P7SS_P7S0; 
//	P8SS = P8SS_P8S7 | P8SS_P8S6; 
	P9SS = P9SS_P9S7 | P9SS_P9S6 | P9SS_P9S5 | P9SS_P9S4 | P9SS_P9S3 | P9SS_P9S2; // COM口线定义
#endif
	
#if( METER_TYPE == METER_TYPE_DTSY666 )
	P4SS = P4SS_P4S7 | P4SS_P4S6 | P4SS_P4S5 | P4SS_P4S4;
	P5SS = P5SS_P5S1 | P5SS_P5S0; 
	P6SS = P6SS_P6S7 | P6SS_P6S6 | P6SS_P6S5 | P6SS_P6S4 | P6SS_P6S3 | P6SS_P6S2 | P6SS_P6S1; 
	P7SS = P7SS_P7S0; 
//	P8SS = P8SS_P8S7 | P8SS_P8S6; 
	P9SS = P9SS_P9S7 | P9SS_P9S6 | P9SS_P9S5 | P9SS_P9S4 | P9SS_P9S3 | P9SS_P9S2; // COM口线定义
#endif
	
#if( METER_TYPE == METER_TYPE_DDSYU666 )
	P4SS = P4SS_P4S7 | P4SS_P4S6 | P4SS_P4S5 | P4SS_P4S4;
	P5SS = P5SS_P5S7 | P5SS_P5S6 | P5SS_P5S5 | P5SS_P5S4 | P5SS_P5S3 | P5SS_P5S2; 
//	P6SS = P6SS_P6S7 | P6SS_P6S6 | P6SS_P6S5 | P6SS_P6S4 | P6SS_P6S3 | P6SS_P6S2 | P6SS_P6S1; 
	P7SS = P7SS_P7S7 | P7SS_P7S6 | P7SS_P7S5 ; 
//	P8SS = P8SS_P8S7 | P8SS_P8S6; 
	P9SS = P9SS_P9S7 | P9SS_P9S6 | P9SS_P9S5 | P9SS_P9S4 | P9SS_P9S3 | P9SS_P9S2; // COM口线定义	
#endif
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    LCD数据填充
 *
 *  @param    v_ucVal : 要填充的数据
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void LCDDrv_SetLcdBuff( uchar8 v_ucVal )
{ 
	uchar8 V_ucCnti;
	
	for( V_ucCnti=0; V_ucCnti<40; V_ucCnti++ )
	{
		GStr_DisplayPara.ucLCDDrvDispBuf[V_ucCnti] = v_ucVal;
	}
	
	LCDDrv_DispRamUpdata();
	
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    配置LCD功能寄存器
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void LCDDrv_PwOnRegCfg(void)
{ 
	if( (LCDCON1 & LCDCON1_DBP_ALL) != LCDCON1_D16_B13_P9 ) // 1/6 DUTY 1/3 BIAS
	{ 
		LCDCON1 &= LCDCON1_DBP_CLR;
		LCDCON1 |= LCDCON1_D16_B13_P9;
	}	
	
	if( (LCDCON1 & LCDCON1_VOUT_ALL) != LCDCON1_VOUT1000 ) // VLCD = 1.000 VOUT
	{ 
		LCDCON1 &= LCDCON1_VOUT_CLR;
		LCDCON1 |= LCDCON1_VOUT1000;
	}	
	
	if( (LCDCON2 & LCDCON2_MOD_ALL) != LCDCON2_MOD60k )	// 010： 传统模式，偏置电阻总和为60k
	{ 
		LCDCON2 &= LCDCON2_MOD_CLR;
		LCDCON2 |= LCDCON2_MOD60k;
	}
	
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    将显示缓存写入显示寄存器
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void LCDDrv_DispRamUpdata(void)
{
	uchar8 xdata *P_ucLcdBuf = 0x2500;
	uchar8 V_ucCnti;
	
	for ( V_ucCnti = 0; V_ucCnti<40; V_ucCnti++ )
	{
		P_ucLcdBuf[V_ucCnti] = GStr_DisplayPara.ucLCDDrvDispBuf[V_ucCnti];
		GStr_DisplayPara.ucLCDDrvDispBuf[V_ucCnti] = 0;
	}
} 


