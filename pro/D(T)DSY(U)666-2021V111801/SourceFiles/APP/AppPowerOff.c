/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    AppPowerOff.c                                                                          
**** Brief:       掉电配置文件                                                                      
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
static void ApiPwOff_CloseDevices(void);
static void ApiPwOff_DataSave(void);
static void ApiPwOff_EnterSleep(void);
static void ApiPwOff_PeripheralInit(void);
static void ApiPwOff_DataProcess(void);
static void ApiPwOff_Display(void); 
static void ApiPwOff_SysClkInit(void);
static void ApiPwOff_BLEPOWERInit(void);
static void ApiPwOff_McuTimerInit(void);
static void ApiPwOff_McuGpioInit(void);
static void ApiPwOff_McuUartInit(void);
static void ApiPwOff_McuDispInit(void);
static void ApiPwOff_EmuInit(void);
static void ApiPwOff_McuLPDInit(void);
static void ApiPwOff_McuEnterSleep(void);
void ApiPwOff_PowerOffTask(void);

/*----------------< 函数定义 >----------------------------------*/

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    掉电管理函数
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
 
void ApiPwOff_PowerOffTask(void)
{
	uchar8	V_ucCnti;
	
	if ( GStr_Flag.ucSystem & F_PWOFF_NOW )	// 发生掉电在中断中检测，检测到后在这里进行判断
	{
		// @brief ---- 关闭之前开启的功能模块   
			ApiPwOff_CloseDevices();	 
		
		// @brief ---- 如果系统正常运行了就要保存一下需要保存的数据，如脉冲尾数 
		if ( GStr_Flag.ucSystem & F_PWRUN )	
		{
			ApiPwOff_DataSave();
			GStr_Flag.ucSystem &= ~F_PWRUN ;
		}
		
		// @brief ---- 延时判断一下是否真的掉电，如果真的掉电了就在这里进入低功耗 
		for ( V_ucCnti = 0; V_ucCnti<10; V_ucCnti++ )
		{
			LibPub_DelayNms(10);
			if ( _FALSE == ApiPwOn_PowerChk() )	///* 再判断一下掉电情况 *///
			{
				GStr_Flag.ucSystem = GStr_Flag.ucSystem | F_PWOFF_NOW;
				ApiPwOff_EnterSleep();
			}
			WDT_Clr();
		}
		
		// @brief ---- 到这还没有进入低功耗，那就再配置一下 
		if ( (GStr_Flag.ucSystem & F_PWOFF_NOW) != F_PWOFF_NOW )	
		{
			GStr_Flag.ucSystem &= (~F_PWOFF_NOW);
			GStr_Flag.ucSystem |= F_PWON;			///* 置上电标志 */// 
		}
		
		// @brief ---- 到这还没有进入低功耗，那就再配置一下 
		ApiPwOn_SysTemInit();
		
	}
	
	/* 如果跑到这里，这表示已经上电运行了，置上电运行标志 */
	if ( 0 == ( GStr_Flag.ucSystem & F_PWRUN ) )
	{
		GStr_Flag.ucSystem |= F_PWRUN ;
	}
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    掉电关闭外设及功能模块
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
 
static void ApiPwOff_CloseDevices(void)
{
	/* 关闭蓝牙模块供电（检测掉电就直接停止供电） */
	ApiPwOff_BLEPOWERInit();

	/* 关闭定时器 */
	ApiPwOff_McuTimerInit();
	
	/* 关闭串口 */
	ApiPwOff_McuUartInit( );
	
	/* 关闭计量 */
	ApiPwOff_EmuInit( );
	
	/* 关闭显示 */
	ApiPwOff_McuDispInit( );

	
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    掉电配置
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
 
static void ApiPwOff_McuLPDInit(void)
{
	PASLO_POWER_SWITCH_ON();
    LPDCON1 = 0x00;/*关掉低电压检测*/

    PASLO_POWER_SWITCH_ON();
	LPDCON2 = 0x00;/*关掉低电压检测*/ 
	
    PASLO_POWER_SWITCH_ON();;
		#if(METER_TYPE==METER_TYPE_DDSYU666)   //导轨表低电压检测为3.00V
			LPDCON2 |= 0xA3;    //低电压检测，3.00V
		#else
			LPDCON2 |= 0xA9;    //单三相表应配置为 0xA4  
		#endif
	
	PASLO_POWER_SWITCH_ON();
 		#if(METER_TYPE==METER_TYPE_DDSYU666)   //导轨表禁止供电自动切换
			PWRCON1 = 1;
		#else
			PWRCON1 = 0;				//单三相表也应配置为禁止供电自动切换
		#endif
	
    PASLO_POWER_SWITCH_ON();
    PWRCON2 = 0x00;
	
    PASLO_POWER_SWITCH_ON();
		#if(METER_TYPE==METER_TYPE_DDSYU666)   //导轨表禁止供电自动切换
			PWRCON1 = 1;
		#else
			PWRCON1 = 0;				//单三相表也应配置为禁止供电自动切换
		#endif
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    掉电数据存储，主要是E2 
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
 
static void ApiPwOff_DataSave(void)
{
	uchar8	V_ucTempBuff[4];
	
		// 剩余金额、透支金额保存一下
	GStr_Money.usCRC16 = LibPub_CRC16_CCITT(&GStr_Money.ucaRemainMoney[0], GStr_MONEY_Type_LEN-2);
	DrvE2p_WriteData( LIB_E2P_Money_Addr,&GStr_Money.ucaRemainMoney[0] ,GStr_MONEY_Type_LEN);///写剩余金额、透支金额到主数据区，不写备份
	
	// 脉冲尾数保存一下
	V_ucTempBuff[0] =  GStr_EnergyPulseFw.ucaPulseRemain[0];
	V_ucTempBuff[1] = ~GStr_EnergyPulseFw.ucaPulseRemain[0];
	V_ucTempBuff[2] =  GStr_EnergyPulseBk.ucaPulseRemain[1];
	V_ucTempBuff[3] = ~GStr_EnergyPulseFw.ucaPulseRemain[1]; 
	LibPub_WriteDataToE2prom( LIB_E2P_ENERGY_DECPULSE_WS, 0, V_ucTempBuff );	///* 脉冲尾数存一下，其他的就不管了 *///
	
	
	
	/* 补充代码 */
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    进入低功耗  
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
 
static void ApiPwOff_EnterSleep(void)
{
	/* 配置口线 */
	ApiPwOff_PeripheralInit();
	
	/* 关闭打开的模块 */
	ApiPwOff_CloseDevices();
	 
	/* 数据处理 */	
	ApiPwOff_DataProcess();
	
	/* 关闭LDO检测 */
	ApiPwOff_McuLPDInit();
	
	/* 配置停电显示 */		
	ApiPwOff_Display(); 
	
	/* 配置系统时钟*/		
	ApiPwOff_SysClkInit();
	
	/* 进入sleep模式 */
	ApiPwOff_McuEnterSleep();
	
	
	
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    掉电外设配置    
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
 
static void ApiPwOff_PeripheralInit(void)
{
	ApiPwOff_McuGpioInit();
}


/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    掉电数据处理    
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
 
static void ApiPwOff_DataProcess(void)
{
	
}


/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    掉电显示处理     
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
 
static void ApiPwOff_Display(void)
{
	
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    掉电时钟处理     
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
 
static void ApiPwOff_SysClkInit(void)
{
	
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    掉电关闭蓝牙模块供电   
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
static void ApiPwOff_BLEPOWERInit(void)
{
	BLE_POWER_OFF();
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    掉电配置定时器（关闭定时器）     
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
static void ApiPwOff_McuTimerInit(void)
{
	TCON &= ~TCON_TF0;	// 清除标志 
	IEN0 &= ~IEN0_ET0;	// 禁止中断
	STOP_TR0();
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    掉电配置GPIO     
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
#if( METER_TYPE == METER_TYPE_DDSYU666 )
void ApiPwOff_McuGpioInit(void)
{
// @brief P0口 总共4根口线 p0.1/2/3/7  Lamp/RelayB/RelayA/Alarm
	// 方向
	GPIO_IOCFG_P0_DIR_I( 1);	
	GPIO_IOCFG_P0_DIR_I( 2);	// 01 跳闸 10 合闸
	GPIO_IOCFG_P0_DIR_I( 3);
	GPIO_IOCFG_P0_DIR_I( 7);
	// 上拉     0        
	GPIO_IOCFG_P0_PUP_F( 1);
	GPIO_IOCFG_P0_PUP_F( 2);
	GPIO_IOCFG_P0_PUP_F( 3);
	GPIO_IOCFG_P0_PUP_F( 7);
	// 状态     0        
	GPIO_IOCFG_P0_SET_0( 1);	// 背光
	GPIO_IOCFG_P0_SET_0( 2);
	GPIO_IOCFG_P0_SET_0( 3);
	GPIO_IOCFG_P0_SET_0( 7);	// 拉闸灯
	// 输出模式选择      
	GPIO_IOCFG_P0_OUT_C( 1);	// 开启推挽
	GPIO_IOCFG_P0_OUT_C( 2);
	GPIO_IOCFG_P0_OUT_C( 3);
	GPIO_IOCFG_P0_OUT_C( 7);
	// 端口输出高能力减弱模式选择
	GPIO_IOCFG_P0_OUTH_WEAKEN( 1);
	GPIO_IOCFG_P0_OUTH_WEAKEN( 2);
	GPIO_IOCFG_P0_OUTH_WEAKEN( 3);
	GPIO_IOCFG_P0_OUTH_WEAKEN( 7);
	// 输入上拉模式选择寄存器
	GPIO_IOCFG_P0_PUPM_SWITCH( 1);
	GPIO_IOCFG_P0_PUPM_SWITCH( 2);
	GPIO_IOCFG_P0_PUPM_SWITCH( 3);
	GPIO_IOCFG_P0_PUPM_SWITCH( 7);
	// 端口数据来源选择寄存器
	GPIO_IOCFG_P0_INM_DATA( 1);
	GPIO_IOCFG_P0_INM_DATA( 2);
	GPIO_IOCFG_P0_INM_DATA( 3);
	GPIO_IOCFG_P0_INM_DATA( 7);


// @brief P1口 总共1根口线 p1.4	 PFout
	// 方向
//	GPIO_IOCFG_P1_DIR_I( 0);
//	GPIO_IOCFG_P1_DIR_I( 3);
	GPIO_IOCFG_P1_DIR_I( 4);
	// 上拉     1        
//	GPIO_IOCFG_P1_PUP_F( 0);
//	GPIO_IOCFG_P1_PUP_F( 3);
	GPIO_IOCFG_P1_PUP_F( 4);
	// 状态     1        
//	GPIO_IOCFG_P1_SET_1( 0);
//	GPIO_IOCFG_P1_SET_1( 3); 
	GPIO_IOCFG_P1_SET_0( 4); // 上电避免脉冲灯亮，设置为输入

//// @brief P2口 总共3根口线 p2.2/6/7	DISPKEY / 485RXD / 485TXD
//	GPIO_IOCFG_P2_DIR_I( 2);
//	GPIO_IOCFG_P2_DIR_I( 6);
//	GPIO_IOCFG_P2_DIR_O( 7);
//	// 上拉     2
//	GPIO_IOCFG_P2_PUP_F( 2);
//	GPIO_IOCFG_P2_PUP_F( 6);
//	GPIO_IOCFG_P2_PUP_F( 7);
//	// 状态     2        
//	GPIO_IOCFG_P2_SET_0( 2);
//	GPIO_IOCFG_P2_SET_0( 6);
//	GPIO_IOCFG_P2_SET_0( 7);
//	// 输出模式选择      
//	GPIO_IOCFG_P2_OUT_N( 2);
//	GPIO_IOCFG_P2_OUT_N( 6);
//	GPIO_IOCFG_P2_OUT_N( 7);
//	// 端口输出高能力减弱模式选择
//	GPIO_IOCFG_P2_OUTH_WEAKEN( 2);
//	GPIO_IOCFG_P2_OUTH_WEAKEN( 6);
//	GPIO_IOCFG_P2_OUTH_WEAKEN( 7);
//	// 输入上拉模式选择寄存器  
//	GPIO_IOCFG_P2_PUPM_SWITCH( 2);
//	GPIO_IOCFG_P2_PUPM_SWITCH( 6);
//	GPIO_IOCFG_P2_PUPM_SWITCH( 7);
//	// 端口数据来源选择寄存器
//	GPIO_IOCFG_P2_INM_DATA( 2);
//	GPIO_IOCFG_P2_INM_DATA( 6);
//	GPIO_IOCFG_P2_INM_DATA( 7);

// @brief P3口 总共3根口线 p3.0/1/2/3/4	 BT_RXD / BT_TXD / KEY1/ SCL / SDA
	GPIO_IOCFG_P3_DIR_I( 0);
	GPIO_IOCFG_P3_DIR_I( 1);
	GPIO_IOCFG_P3_DIR_I( 2);
	GPIO_IOCFG_P3_DIR_I( 3);
	GPIO_IOCFG_P3_DIR_I( 4);
	// 上拉     3        
	GPIO_IOCFG_P3_PUP_F( 0);
	GPIO_IOCFG_P3_PUP_F( 1);
	GPIO_IOCFG_P3_PUP_F( 2);
	GPIO_IOCFG_P3_PUP_F( 3);
	GPIO_IOCFG_P3_PUP_F( 4);
	// 状态     3        
	GPIO_IOCFG_P3_SET_0( 0);
	GPIO_IOCFG_P3_SET_0( 1);
	GPIO_IOCFG_P3_SET_0( 2);	
	GPIO_IOCFG_P3_SET_0( 3);	 
	GPIO_IOCFG_P3_SET_0( 4); 	 
	// 输出模式选择
	GPIO_IOCFG_P3_OUT_N( 0);
	GPIO_IOCFG_P3_OUT_N( 1);
	GPIO_IOCFG_P3_OUT_N( 2);
	GPIO_IOCFG_P3_OUT_N( 3);
	GPIO_IOCFG_P3_OUT_N( 4);

// @brief P4口 总共4根口线 p4.4/5/6/7 SEG1/SEG2/SEG3/SEG4
	GPIO_IOCFG_P4_DIR_I( 4);
	GPIO_IOCFG_P4_DIR_I( 5);
	GPIO_IOCFG_P4_DIR_I( 6);
	GPIO_IOCFG_P4_DIR_I( 7);
	// 上拉     4        
	GPIO_IOCFG_P4_PUP_F( 4);
	GPIO_IOCFG_P4_PUP_F( 5);
	GPIO_IOCFG_P4_PUP_F( 6);
	GPIO_IOCFG_P4_PUP_F( 7);
	// 状态     4        
	GPIO_IOCFG_P4_SET_0( 4);
	GPIO_IOCFG_P4_SET_0( 5);
	GPIO_IOCFG_P4_SET_0( 6);
	GPIO_IOCFG_P4_SET_0( 7);

// @brief P5口 总共8根口线 p5.0/1/2/3/4/5/6/7	BT_CTL / BT_ATEN / SEG5 / SEG8 / SEG9(DCK) / SEG10(TDI) /SEG11(TMS) / SEG12(TDO)
	GPIO_IOCFG_P5_DIR_I( 0);
	GPIO_IOCFG_P5_DIR_I( 1);
	GPIO_IOCFG_P5_DIR_I( 2);
	GPIO_IOCFG_P5_DIR_I( 3);
	GPIO_IOCFG_P5_DIR_I( 4);
	GPIO_IOCFG_P5_DIR_I( 5);
	GPIO_IOCFG_P5_DIR_I( 6);
	GPIO_IOCFG_P5_DIR_I( 7);
	// 上拉     5        
	GPIO_IOCFG_P5_PUP_F( 0);
	GPIO_IOCFG_P5_PUP_F( 1);
	GPIO_IOCFG_P5_PUP_F( 2);
	GPIO_IOCFG_P5_PUP_F( 3);
	GPIO_IOCFG_P5_PUP_F( 4);
	GPIO_IOCFG_P5_PUP_F( 5);
	GPIO_IOCFG_P5_PUP_F( 6);
	GPIO_IOCFG_P5_PUP_F( 7);
	// 状态     5        
	GPIO_IOCFG_P5_SET_0( 0);
	GPIO_IOCFG_P5_SET_0( 1);
	GPIO_IOCFG_P5_SET_0( 2);
	GPIO_IOCFG_P5_SET_0( 3);
	GPIO_IOCFG_P5_SET_0( 4);
	GPIO_IOCFG_P5_SET_0( 5);
	GPIO_IOCFG_P5_SET_0( 6);
	GPIO_IOCFG_P5_SET_0( 7);

//// @brief P6口 总共7根口线 p6.1/2/3/4/5/6/7   SEG8/ SEG7/ SEG6/ SEG5/ SEG4/ SEG3/ SEG2
//	GPIO_IOCFG_P6_DIR_O( 1);
//	GPIO_IOCFG_P6_DIR_O( 2);
//	GPIO_IOCFG_P6_DIR_O( 3);
//	GPIO_IOCFG_P6_DIR_O( 4);
//	GPIO_IOCFG_P6_DIR_O( 5);
//	GPIO_IOCFG_P6_DIR_O( 6);
//	GPIO_IOCFG_P6_DIR_O( 7);
//	// 上拉     6        
//	GPIO_IOCFG_P6_PUP_F( 1);
//	GPIO_IOCFG_P6_PUP_F( 2);
//	GPIO_IOCFG_P6_PUP_F( 3);
//	GPIO_IOCFG_P6_PUP_F( 4);
//	GPIO_IOCFG_P6_PUP_F( 5);
//	GPIO_IOCFG_P6_PUP_F( 6);
//	GPIO_IOCFG_P6_PUP_F( 7);
//	// 状态     6        
//	GPIO_IOCFG_P6_SET_0( 1);
//	GPIO_IOCFG_P6_SET_0( 2);
//	GPIO_IOCFG_P6_SET_0( 3);
//	GPIO_IOCFG_P6_SET_0( 4);
//	GPIO_IOCFG_P6_SET_0( 5);
//	GPIO_IOCFG_P6_SET_0( 6);
//	GPIO_IOCFG_P6_SET_0( 7); 

// @brief P7口 总共5根口线 p7.5/6/7/ 数据手册寄存器里显示有5个，但实际封装只有3个 SEG13/ SEG14/ SEG15
	GPIO_IOCFG_P7_DIR_I( 5);
	GPIO_IOCFG_P7_DIR_I( 6);
	GPIO_IOCFG_P7_DIR_I( 7);
	// 上拉     7        
	GPIO_IOCFG_P7_PUP_F( 5);
	GPIO_IOCFG_P7_PUP_F( 6);
	GPIO_IOCFG_P7_PUP_F( 7);
	// 状态     7        
	GPIO_IOCFG_P7_SET_0( 5);
	GPIO_IOCFG_P7_SET_0( 6);
	GPIO_IOCFG_P7_SET_0( 7);

//// @brief P8口 总共2根口线 p8.6/7 SDA/ SCL
//	GPIO_IOCFG_P8_DIR_O( 6);
//	GPIO_IOCFG_P8_DIR_O( 7);
//	// 上拉     8        
//	GPIO_IOCFG_P8_PUP_F( 6);
//	GPIO_IOCFG_P8_PUP_F( 7);
//	// 状态     8        
//	GPIO_IOCFG_P8_SET_1( 6);
//	GPIO_IOCFG_P8_SET_1( 7); 

// @brief P9口 总共8根口线 p9.2/3/4/5/6/7   COM1-COM6 /  
	GPIO_IOCFG_P9_DIR_I( 2);
	GPIO_IOCFG_P9_DIR_I( 3);
	GPIO_IOCFG_P9_DIR_I( 4);
	GPIO_IOCFG_P9_DIR_I( 5);
	GPIO_IOCFG_P9_DIR_I( 6);
	GPIO_IOCFG_P9_DIR_I( 7);	
	// 上拉     9         
	GPIO_IOCFG_P9_PUP_F( 2);
	GPIO_IOCFG_P9_PUP_F( 3);
	GPIO_IOCFG_P9_PUP_F( 4);
	GPIO_IOCFG_P9_PUP_F( 5);
	GPIO_IOCFG_P9_PUP_F( 6);
	GPIO_IOCFG_P9_PUP_F( 7);
	// 状态     9         
	GPIO_IOCFG_P9_SET_0( 2);
	GPIO_IOCFG_P9_SET_0( 3); 
	GPIO_IOCFG_P9_SET_0( 4);
	GPIO_IOCFG_P9_SET_0( 5); 
	GPIO_IOCFG_P9_SET_0( 6);
	GPIO_IOCFG_P9_SET_0( 7); 

} 

#else
static void ApiPwOff_McuGpioInit(void)
{
	// @brief P0口 总共4根口线 p0.1/2/3/7  Relay1/Relay2/Null/Null
	// 方向
	GPIO_IOCFG_P0_DIR_I( 1);// 01 跳闸 10 合闸
	GPIO_IOCFG_P0_DIR_I( 2);
	GPIO_IOCFG_P0_DIR_I( 3);
	GPIO_IOCFG_P0_DIR_I( 7);
	// 上拉
	GPIO_IOCFG_P0_PUP_F( 1);
	GPIO_IOCFG_P0_PUP_F( 2);
	GPIO_IOCFG_P0_PUP_F( 3);
	GPIO_IOCFG_P0_PUP_F( 7);
	// 状态
	GPIO_IOCFG_P0_SET_0( 1);
	GPIO_IOCFG_P0_SET_0( 2);
	GPIO_IOCFG_P0_SET_0( 3);
	GPIO_IOCFG_P0_SET_0( 7);
	// 输出模式选择
	GPIO_IOCFG_P0_OUT_N( 1);	// 开启推挽
	GPIO_IOCFG_P0_OUT_N( 2);
	GPIO_IOCFG_P0_OUT_N( 3);
	GPIO_IOCFG_P0_OUT_N( 7);
	// 端口输出高能力减弱模式选择
	GPIO_IOCFG_P0_OUTH_WEAKEN( 1);
	GPIO_IOCFG_P0_OUTH_WEAKEN( 2);
	GPIO_IOCFG_P0_OUTH_WEAKEN( 3);
	GPIO_IOCFG_P0_OUTH_WEAKEN( 7);
	// 输入上拉模式选择寄存器
	GPIO_IOCFG_P0_PUPM_SWITCH( 1);
	GPIO_IOCFG_P0_PUPM_SWITCH( 2);
	GPIO_IOCFG_P0_PUPM_SWITCH( 3);
	GPIO_IOCFG_P0_PUPM_SWITCH( 7);
	// 端口数据来0源选择寄存器
	GPIO_IOCFG_P0_INM_DATA( 1);
	GPIO_IOCFG_P0_INM_DATA( 2);
	GPIO_IOCFG_P0_INM_DATA( 3);
	GPIO_IOCFG_P0_INM_DATA( 7);


// @brief P1口 总共3根口线 p1.0/3/4	 Null/LED_yellow/PFout
	// 方向
	GPIO_IOCFG_P1_DIR_I( 0);
	GPIO_IOCFG_P1_DIR_I( 3);
	GPIO_IOCFG_P1_DIR_I( 4);
	// 上拉     1        
	GPIO_IOCFG_P1_PUP_F( 0);
	GPIO_IOCFG_P1_PUP_F( 3);
	GPIO_IOCFG_P1_PUP_F( 4);
	// 状态     1        
	GPIO_IOCFG_P1_SET_0( 0);
	GPIO_IOCFG_P1_SET_0( 3);
	GPIO_IOCFG_P1_SET_0( 4);

// @brief P2口 总共3根口线 p2.2/6/7	DISPKEY / 485RXD / 485TXD
	GPIO_IOCFG_P2_DIR_I( 2);
	GPIO_IOCFG_P2_DIR_I( 6);
	GPIO_IOCFG_P2_DIR_I( 7);
	// 上拉     2        
	GPIO_IOCFG_P2_PUP_F( 2);
	GPIO_IOCFG_P2_PUP_F( 6);
	GPIO_IOCFG_P2_PUP_F( 7);
	// 状态     2        
	GPIO_IOCFG_P2_SET_0( 2);
	GPIO_IOCFG_P2_SET_0( 6);
	GPIO_IOCFG_P2_SET_0( 7);
	// 输出模式选择      
	GPIO_IOCFG_P2_OUT_N( 2);
	GPIO_IOCFG_P2_OUT_N( 6);
	GPIO_IOCFG_P2_OUT_N( 7);
	// 端口输出高能力减弱模式选择
	GPIO_IOCFG_P2_OUTH_WEAKEN( 2);
	GPIO_IOCFG_P2_OUTH_WEAKEN( 6);
	GPIO_IOCFG_P2_OUTH_WEAKEN( 7);
	// 输入上拉模式选择寄存器
	GPIO_IOCFG_P2_PUPM_SWITCH( 2);
	GPIO_IOCFG_P2_PUPM_SWITCH( 6);
	GPIO_IOCFG_P2_PUPM_SWITCH( 7);
	// 端口数据来源选择寄存器
	GPIO_IOCFG_P2_INM_DATA( 2);
	GPIO_IOCFG_P2_INM_DATA( 6);
	GPIO_IOCFG_P2_INM_DATA( 7);

// @brief P3口 总共3根口线 p3.0/1/4/5/6	 BT_RXD / BT_TXD / BT_RST/ BT_ATEN / BT_CTL
	GPIO_IOCFG_P3_DIR_I( 0);
	GPIO_IOCFG_P3_DIR_I( 1);
	GPIO_IOCFG_P3_DIR_I( 4);
	GPIO_IOCFG_P3_DIR_I( 5);
	GPIO_IOCFG_P3_DIR_I( 6);
	// 上拉     3        
	GPIO_IOCFG_P3_PUP_F( 0);
	GPIO_IOCFG_P3_PUP_F( 1);
	GPIO_IOCFG_P3_PUP_F( 4);
	GPIO_IOCFG_P3_PUP_F( 5);
	GPIO_IOCFG_P3_PUP_F( 6);
	// 状态     3        
	GPIO_IOCFG_P3_SET_0( 0);
	GPIO_IOCFG_P3_SET_0( 1);
	GPIO_IOCFG_P3_SET_1( 4);	// 0复位，1不复位
	GPIO_IOCFG_P3_SET_0( 5);
	GPIO_IOCFG_P3_SET_0( 6); 	// 0供电，1不供电
	// 输出模式选择
	GPIO_IOCFG_P3_OUT_N( 0);
	GPIO_IOCFG_P3_OUT_N( 1);
	GPIO_IOCFG_P3_OUT_N( 4);
	GPIO_IOCFG_P3_OUT_N( 5);
	GPIO_IOCFG_P3_OUT_N( 6);

// @brief P4口 总共4根口线 p4.4/5/6/7 SEG9/SEG10/SEG11/SEG12
	GPIO_IOCFG_P4_DIR_I( 4);
	GPIO_IOCFG_P4_DIR_I( 5);
	GPIO_IOCFG_P4_DIR_I( 6);
	GPIO_IOCFG_P4_DIR_I( 7);
	// 上拉     4        
	GPIO_IOCFG_P4_PUP_F( 4);
	GPIO_IOCFG_P4_PUP_F( 5);
	GPIO_IOCFG_P4_PUP_F( 6);
	GPIO_IOCFG_P4_PUP_F( 7);
	// 状态     4        
	GPIO_IOCFG_P4_SET_0( 4);
	GPIO_IOCFG_P4_SET_0( 5);
	GPIO_IOCFG_P4_SET_0( 6);
	GPIO_IOCFG_P4_SET_0( 7);

// @brief P5口 总共8根口线 p5.0/1/2/3/4/5/6/7	SEG13 / SEG14 / I_J / NULL / DCK / TDI /TMS / TDO
	GPIO_IOCFG_P5_DIR_I( 0);
	GPIO_IOCFG_P5_DIR_I( 1);
	GPIO_IOCFG_P5_DIR_I( 2);
	GPIO_IOCFG_P5_DIR_I( 3);
	GPIO_IOCFG_P5_DIR_I( 4);
	GPIO_IOCFG_P5_DIR_I( 5);
	GPIO_IOCFG_P5_DIR_I( 6);
	GPIO_IOCFG_P5_DIR_I( 7);
	// 上拉     5        
	GPIO_IOCFG_P5_PUP_F( 0);
	GPIO_IOCFG_P5_PUP_F( 1);
	GPIO_IOCFG_P5_PUP_F( 2);
	GPIO_IOCFG_P5_PUP_F( 3);
	GPIO_IOCFG_P5_PUP_F( 4);
	GPIO_IOCFG_P5_PUP_F( 5);
	GPIO_IOCFG_P5_PUP_F( 6);
	GPIO_IOCFG_P5_PUP_F( 7);
	// 状态     5        
	GPIO_IOCFG_P5_SET_0( 0);
	GPIO_IOCFG_P5_SET_0( 1);
	GPIO_IOCFG_P5_SET_0( 2);
	GPIO_IOCFG_P5_SET_0( 3);
	GPIO_IOCFG_P5_SET_0( 4);
	GPIO_IOCFG_P5_SET_0( 5);
	GPIO_IOCFG_P5_SET_0( 6);
	GPIO_IOCFG_P5_SET_0( 7);

// @brief P6口 总共7根口线 p6.1/2/3/4/5/6/7   SEG8/ SEG7/ SEG6/ SEG5/ SEG4/ SEG3/ SEG2
	GPIO_IOCFG_P6_DIR_I( 1);
	GPIO_IOCFG_P6_DIR_I( 2);
	GPIO_IOCFG_P6_DIR_I( 3);
	GPIO_IOCFG_P6_DIR_I( 4);
	GPIO_IOCFG_P6_DIR_I( 5);
	GPIO_IOCFG_P6_DIR_I( 6);
	GPIO_IOCFG_P6_DIR_I( 7);
	// 上拉     6        
	GPIO_IOCFG_P6_PUP_F( 1);
	GPIO_IOCFG_P6_PUP_F( 2);
	GPIO_IOCFG_P6_PUP_F( 3);
	GPIO_IOCFG_P6_PUP_F( 4);
	GPIO_IOCFG_P6_PUP_F( 5);
	GPIO_IOCFG_P6_PUP_F( 6);
	GPIO_IOCFG_P6_PUP_F( 7);
	// 状态     6        
	GPIO_IOCFG_P6_SET_0( 1);
	GPIO_IOCFG_P6_SET_0( 2);
	GPIO_IOCFG_P6_SET_0( 3);
	GPIO_IOCFG_P6_SET_0( 4);
	GPIO_IOCFG_P6_SET_0( 5);
	GPIO_IOCFG_P6_SET_0( 6);
	GPIO_IOCFG_P6_SET_0( 7); 

// @brief P7口 总共5根口线 p7.0/1/5/ 数据手册寄存器里显示有5个，但实际封装只有3个 SEG1/ NULL/ NULL
	GPIO_IOCFG_P7_DIR_I( 0);
	GPIO_IOCFG_P7_DIR_I( 1);
	GPIO_IOCFG_P7_DIR_I( 5);
	// 上拉     7        
	GPIO_IOCFG_P7_PUP_F( 0);
	GPIO_IOCFG_P7_PUP_F( 1);
	GPIO_IOCFG_P7_PUP_F( 5);
	// 状态     7        
	GPIO_IOCFG_P7_SET_0( 0);
	GPIO_IOCFG_P7_SET_0( 1);
	GPIO_IOCFG_P7_SET_0( 5);

// @brief P8口 总共2根口线 p8.6/7 SDA/ SCL
	GPIO_IOCFG_P8_DIR_I( 6);
	GPIO_IOCFG_P8_DIR_I( 7);
	// 上拉     8        
	GPIO_IOCFG_P8_PUP_F( 6);
	GPIO_IOCFG_P8_PUP_F( 7);
	// 状态     8        
	GPIO_IOCFG_P8_SET_0( 6);
	GPIO_IOCFG_P8_SET_0( 7); 

// @brief P9口 总共8根口线 p9.0/1/2/3/4/5/6/7   WP/ LED_CTL/ COM1-COM6 / 
	GPIO_IOCFG_P9_DIR_I( 0);	
	GPIO_IOCFG_P9_DIR_I( 1);	// 先设置成输入,免得上电的时候闪一下
	GPIO_IOCFG_P9_DIR_I( 2);
	GPIO_IOCFG_P9_DIR_I( 3);
	GPIO_IOCFG_P9_DIR_I( 4);
	GPIO_IOCFG_P9_DIR_I( 5);
	GPIO_IOCFG_P9_DIR_I( 6);
	GPIO_IOCFG_P9_DIR_I( 7);	
	// 上拉     9        
	GPIO_IOCFG_P9_PUP_F( 0);
	GPIO_IOCFG_P9_PUP_F( 1);
	GPIO_IOCFG_P9_PUP_F( 2);
	GPIO_IOCFG_P9_PUP_F( 3);
	GPIO_IOCFG_P9_PUP_F( 4);
	GPIO_IOCFG_P9_PUP_F( 5);
	GPIO_IOCFG_P9_PUP_F( 6);
	GPIO_IOCFG_P9_PUP_F( 7);
	// 状态     9        
	GPIO_IOCFG_P9_SET_0( 0);
	GPIO_IOCFG_P9_SET_0( 1);  // 背光暂时不点亮
	GPIO_IOCFG_P9_SET_0( 2);
	GPIO_IOCFG_P9_SET_0( 3); 
	GPIO_IOCFG_P9_SET_0( 4);
	GPIO_IOCFG_P9_SET_0( 5); 
	GPIO_IOCFG_P9_SET_0( 6);
	GPIO_IOCFG_P9_SET_0( 7); 
}
#endif
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    掉电配置uart     
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/

static void ApiPwOff_McuUartInit(void)
{
	SCON &= ~(SCON_RI | SCON_TI);
	IEN0 &= ~IEN0_ES0;
	
	SCON1 &= ~(SCON1_RI1 | SCON1_TI1);
	IEN1  &= ~IEN1_ES1;
	 
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    掉电配置显示    
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/

static void ApiPwOff_McuDispInit(void)
{
	LCDDrv_Init(POWER_OFF);
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    掉电配置计量模块   
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/

static void ApiPwOff_EmuInit(void)
{
	ApiMS_DisOrEnable(EMU_DISENABLE);
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    进入掉电模式  
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/

static void ApiPwOff_McuEnterSleep(void)
{
//	ENTER_POWERDWN();
}



