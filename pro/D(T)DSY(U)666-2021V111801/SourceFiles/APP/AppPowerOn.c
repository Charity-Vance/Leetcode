/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发
****                            All rights reserved.
**** FileName:    AppPowerOn.c
**** Brief:       上电系统配置
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
// 静态函数声明
static uchar8 ApiPwOn_McuLPDInit(void);
static void   ApiPwOn_McuRamInit(void);
static void   ApiPwOn_McuGpioInit(void);
static void   ApiPwOn_McuDispInit(void);
static void   ApiPwOn_McuInterruptInit(void);
static void   ApiPwOn_McuUartInit(void);
static void   ApiPwOn_EMUInit(void);
static void   ApiPwOn_McuUartXSetBps(uchar8 v_ucChID); 
static void   ApiPwOn_RemainMoneyCheck(void) ;

void   ApiPwOn_BleInit(void);
void   ApiPwOn_SysClkInit(void);
void   ApiPwOn_McuTimerInit(void);
void   ApiPwOn_MeterClear(void);
void   ApiPwOn_MeterInitInFactory(void);
//全局函数声明
void   ApiPwOn_McuReset(void);
uchar8 ApiPwOn_SysTemInit(void);
void   ApiPwOn_DisplayParaCheck(void);
void   ApiPwOn_McuUartXInit(uchar8 v_ucChID); 
void   ApiPwOn_UART_SendEn(uchar8 v_ucChID);
void   ApiPwOn_MeterInfoParaCheck(void);
void   ApiPwOn_DLXS_READ(GStr_ENERGY_PULSE_Type *p_strEnergyPulse,ushort16 v_usAddrIndex );
void   ApiPwOn_EnergyCheck(void);
void   ApiPwOn_MoneyParaCheck(void);
void   ApiPwOn_EmuParaCheck(void);
uchar8 ApiPwOn_EnergyZSCheck(void);
void   ApiPwOn_FunConfigParaCheck(void);
uchar8 ApiPwOn_PowerChk( void );
void   ApiPwOn_KeyStatusCheck(void);
void   ApiPwOn_EventPointCheck(void) ;
void   ApiPwOn_BleParaChk(void);
/*----------------< 函数定义 >----------------------------------*/


/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    上电配置系统资源寄存器
 *
 *  @return   根据情况返回_SUCCESS或_FAILED
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/

uchar8 ApiPwOn_SysTemInit(void)
{
//@brief ---先清一下看门狗
	WDT_Clr();
//@brief ---关闭所有中断
	DIS_ALL_INT();

//@brief ---检查是否真的掉电
	ApiPwOn_McuLPDInit();
//	LibPub_DelayNms(100);
	
//@brief ---上电稳定后配置一下时钟
	ApiPwOn_SysClkInit();
//	LibPub_DelayNms(100);

//@brief ---配置口线
	ApiPwOn_McuGpioInit();

//@brief ---配置RAM/更新存储数据到RAM
	ApiPwOn_McuRamInit();

//@brief ---配置显示
	ApiPwOn_McuDispInit();

//@brief ---配置定时器
	ApiPwOn_McuTimerInit();

//@brief ---配置中断
	ApiPwOn_McuInterruptInit();

//@brief ---配置通信（蓝牙和RS485 ）
	ApiPwOn_McuUartInit(); 
	
//@brief --- 配置计量
	ApiPwOn_EMUInit();

	EI();
	
	
	return( _SUCCESS );
}


/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    软件复位单片机
 *
 *  @return   none
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void ApiPwOn_McuReset(void)
{
	 MCU_RST();
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    系统时钟配置
 *
 *  @return   none
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/

void ApiPwOn_SysClkInit(void)
{
	uchar8 V_ucCnti;

	if( (CLKCON & CLKCON_32K_SPDUP) !=  CLKCON_32K_SPDUP )
	{
		CLKCON_WR_ENABLE();
		CLKCON |= CLKCON_32K_SPDUP;		// 开启加速模式
	}

	if( (CLKCON & CLKCON_FSYS_FOSCS_ALL) != CLKCON_FSYS_FOSCS )
	{
		CLKCON_WR_ENABLE();
		CLKCON &= CLKCON_FSYS_FOSCS_CLR;	// 先清零
		
		CLKCON_WR_ENABLE();
		CLKCON |= CLKCON_FSYS_FOSCS;		// 00： fSYS = fOSCS  不分频
	}

	if( (CLKCON & CLKCON_HFSEL) != CLKCON_HFSEL )
	{
		CLKCON_WR_ENABLE();
		CLKCON |= CLKCON_HFSEL;			// 1: 选择8M RC作为高频时钟源,暂时不需要pll
	}

	if( (CLKCON & CLKCON_HFON) != CLKCON_HFON )
	{
		CLKCON_WR_ENABLE();
		CLKCON |= CLKCON_HFON;			// 1: 打开8MhzRC振荡器
	}
	
    for( V_ucCnti=0; V_ucCnti<100; V_ucCnti++)
    {
		NOP();				  		//2011.10.DELAY 5MS
    }
	
	if( (CLKCON & CLKCON_CLKSEL) != CLKCON_CLKSEL )	
	{
		CLKCON_WR_ENABLE();
		CLKCON |= CLKCON_CLKSEL;		// 1： 选择HFCLK作为OSCSCLK
	}
	
    for( V_ucCnti=0; V_ucCnti<100; V_ucCnti++)
    {
      NOP();				  //2011.10.DELAY 5MS
    }
}
/*
选择RC8MCLK作为OSCSCLK， 必须按以下步骤依次设置：
(1). 设置高频时钟选择， HFSEL=1
(2)设置HFON= 1 ， 打开8MHz RC振荡器
(3).等待3个NOP
(4).设置CLKSEL=1， 选择HFCLK作为OSCSCLK
将系统时钟在PLL和8MHz RC振荡器之间切换时， 需将系统先切换至CK32。
*/
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    上电稳定检测,
 *
 *  @return   none
 *
 *  @note     使用LPD2，用于监测VOUT电源的电压状态。
 *
 */
/*------------------------------------------------------------------------------------------------------*/
uchar8 ApiPwOn_McuLPDInit(void)
{

//@brief ---配置电源相关
	DIS_LPD_INT();		// 先禁止LPD中断
	
	PASLO_POWER_SWITCH_ON();
	LPDCON1 = 0x00;					//使能LPD1En（总使能，数据手册没说明） 掉电检测,注意：如果没有使用VIN引脚，则需要配置选项字节
	
	PASLO_POWER_SWITCH_ON();
	LPDCON2 = 0x00;					//关闭LPD2 掉电检测
	
//#if( METER_TYPE != METER_TYPE_DDSYU666 )	
//	PASLO_POWER_SWITCH_ON();
//	LPDCON2 = ( LPDCON2_LPD2EN  | LPDCON2_LPDS_315 );	// 允许低电压检测，开LPD2,禁止LPD3检测，电压3.15V 约95%

//	PASLO_POWER_SWITCH_ON();
//	PWRCON1 = ( PWRCON1_VDD2VOUT | PWRCON1_AUTOS ); 	// VDD供电至VOUT,禁止供电自动切换
//#endif

//#if( METER_TYPE == METER_TYPE_DDSYU666 )
	PASLO_POWER_SWITCH_ON();
	LPDCON2 = ( LPDCON2_LPD2EN | LPDCON2_LPDS_300 );	// 允许低电压检测，开LPD2,禁止LPD3检测，电压3.00V 约91%

	PASLO_POWER_SWITCH_ON();
	PWRCON1 = ( PWRCON1_VDD2VOUT | PWRCON1_AUTOS ); 	// VDD供电至VOUT,禁止供电自动切换  
//#endif

	PASLO_POWER_SWITCH_ON();
	PWRCON2 =  0x00;//PWRCON2_LDO28ON | PWRCON2_LCDLDO_300;

//@brief ---判断上电是否稳定
	if( _FALSE == ApiPwOn_PowerChk() )
	{
		ApiPwOn_McuReset();
	}
//@brief ---上电稳定后，开始配置系统时钟及其他接口模块
	if ( (LPDCON2 & LPDCON2_LPD2F) == LPDCON2_LPD2F )
	{
		return _FAILED;
	}

//@brief ---允许掉电中断
	DIS_LPD_INT();		// 先禁止LPD中断,在定时节拍中断中查询
	
	return _SUCCESS;
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    上电Ram数据初始化
 *
 *  @return   none
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void ApiPwOn_McuRamInit(void)
{
	
//---------------------------------------------------------------------------
//@brief ---系统全局变量初始化  所有掉电不保存的标志清零 
	LibPub_MemSetBytes( (uchar8 *)&GStr_Flag.ucSystem, 0x00, GStr_FLAG_Type_LEN); 			 			///* 系统状态 *///
	LibPub_MemSetBytes( (uchar8 *)&GStr_Monitor.ulTimer_ms, 0x00, GStr_MONITOR_Tpye_LEN); 	 			///* 系统节拍 *///
	LibPub_MemSetBytes( (uchar8 *)&GStr_DisplayPara.ucFullDisp_Time, 0x00, GStr_DISPLAY_PARA_Type_LEN);	///* 显示参数 *///
	LibPub_MemSetBytes( (uchar8 *)&GStr_FunConfigPara.ucFunCurrentVal, 0x00, GStr_FUN_CONFIG_TypeLEN);	///* 功能配置参数 *///
	LibPub_MemSetBytes( (uchar8 *)&GStr_EnergyPulseFw.ucPulseAdd, 0x00, GStr_ENERGY_PULSE_Type_LEN);	///* 正向脉冲 *///
	LibPub_MemSetBytes( (uchar8 *)&GStr_EnergyPulseBk.ucPulseAdd, 0x00, GStr_ENERGY_PULSE_Type_LEN);	///* 反向脉冲 *///
	LibPub_MemSetBytes( (uchar8 *)&GStr_Energy.ucaFw_Energy, 0x00, GStr_ENERGY_Type_LEN);				///* 电能清零，从E2中恢复 *///
	LibPub_MemSetBytes( (uchar8 *)&GStr_AVAIL.us_IDAvailTimer, 0x00, GStr_AVAIL_TypeLEN);				///* 身份认证有效时长剩余时间 *///
	LibPub_MemSetBytes( (uchar8 *)&GStr_Counter.ucFactoryMode_Cnt, 0x00, GStr_COUNTER_Type_LEN);		///* 计数清零、密码错误次数清零
//---------------------------------------------------------------------------
//@brief ---更新存储数据到RAM
	GStr_Flag.ucPowerOnFlag=1;///上电标志置1，有该标志时 ，RAM错的时候不复位计量芯片
	///* E2参数校验更新,整个E2重要数据区块是否需要校验 *///
	ApiPwOn_EnergyCheck() ;			///* 电量数据 *///
	ApiPwOn_RemainMoneyCheck();     ///* 上电金额数据处理
	ApiPwOn_EmuParaCheck() ;		///* 计量参数 *
	ApiPwOn_DisplayParaCheck();		///* 显示参数 *///
	ApiPwOn_MeterInfoParaCheck() ;	///* 表信息参数 *///
	ApiPwOn_MoneyParaCheck();       ///* 报警金额等参数校验
	ApiMoney_RefreshPrice();        ///*电价参数效验
	ApiPwOn_FunConfigParaCheck();	///* 功能配置参数 *///
	ApiPwOn_KeyStatusCheck()	;   ///* 开户状态和密钥状态*///
	ApiPwOn_EventPointCheck() ;		///* 事件指针效验*///
	
//---------------------------------------------------------------------------	
	GV_ucMACErrNum = 0;
	GStr_Flag.ucRunState2 &= ~ F_RUN_INTAUTH_MACNumErrFlag;///上电请身份认证挂起标志
	
	GStr_DisplayPara.ucDisp_tongxin_Flag=0x00;					// 通信显示标志清零
	GStr_Flag.ucSystem |= F_PWON ;								// 认为已经在上电 
	GStr_Flag.ucDisp |= ( F_DISP_UPDATA  |F_DISP_DISPALL );		// 上电全显，且刷新显示 
	GStr_DisplayPara.ulDisptimer = GStr_DisplayPara.ucFullDisp_Time*1000/LCD_UPTATA_TIME;//全显时间转换为ms
	GStr_Flag.ucDispKey = F_KEY_STATUS_IDLE;
	GStr_DisplayPara.ucBackLightTime =GStr_DisplayPara.ucFullDisp_Time;	///1s减一次   上电背光和跳闸灯亮的时间等于上电全显时间
	GStr_DisplayPara.ucRelayLEDTime  =GStr_DisplayPara.ucFullDisp_Time;	///1s减一次   上电背光和跳闸灯亮的时间等于上电全显时间
//---------------------------------------------------------------------------	
	if(_TRUE != LibPub_ReadDataFromE2prom(LIB_E2P_RUN_STATE,0,&GStr_Flag.ucRunState))
	{
		GStr_Flag.ucRunState =0;
	}
	if(GStr_Flag.ucRunState&F_RUN_RELAY_STATE_EE) 
	{
		GStr_Flag.ucRunState2|=F_RUN_RELAY_STATE;
	}
	ApiRelay_SubtractMoneyRelayJudge();
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    上电GPIO配置，使用的时候在配置一次
 *
 *  @return   none
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
#if (METER_TYPE == METER_TYPE_DDSYU666)
void ApiPwOn_McuGpioInit(void)
{
// @brief P0口 总共4根口线 p0.1/2/3/7  Lamp/RelayB/RelayA/Alarm
	// 方向
	GPIO_IOCFG_P0_DIR_O( 1);	
	GPIO_IOCFG_P0_DIR_O( 2);	// 01 跳闸 10 合闸
	GPIO_IOCFG_P0_DIR_O( 3);
	GPIO_IOCFG_P0_DIR_O( 7);
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
	GPIO_IOCFG_P1_SET_1( 4); // 上电避免脉冲灯亮，设置为输入

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
	GPIO_IOCFG_P3_DIR_O( 1);
	GPIO_IOCFG_P3_DIR_I( 2);
	GPIO_IOCFG_P3_DIR_O( 3);
	GPIO_IOCFG_P3_DIR_O( 4);
	// 上拉     3        
	GPIO_IOCFG_P3_PUP_F( 0);
	GPIO_IOCFG_P3_PUP_F( 1);
	GPIO_IOCFG_P3_PUP_F( 2);
	GPIO_IOCFG_P3_PUP_F( 3);
	GPIO_IOCFG_P3_PUP_F( 4);
	// 状态     3        
	GPIO_IOCFG_P3_SET_0( 0);
	GPIO_IOCFG_P3_SET_0( 1);
	GPIO_IOCFG_P3_SET_1( 2);	
	GPIO_IOCFG_P3_SET_1( 3);	 
	GPIO_IOCFG_P3_SET_1( 4); 	 
	// 输出模式选择
	GPIO_IOCFG_P3_OUT_N( 0);
	GPIO_IOCFG_P3_OUT_N( 1);
	GPIO_IOCFG_P3_OUT_N( 2);
	GPIO_IOCFG_P3_OUT_N( 3);
	GPIO_IOCFG_P3_OUT_N( 4);

// @brief P4口 总共4根口线 p4.4/5/6/7 SEG1/SEG2/SEG3/SEG4
	GPIO_IOCFG_P4_DIR_O( 4);
	GPIO_IOCFG_P4_DIR_O( 5);
	GPIO_IOCFG_P4_DIR_O( 6);
	GPIO_IOCFG_P4_DIR_O( 7);
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
	GPIO_IOCFG_P5_DIR_O( 0);
	GPIO_IOCFG_P5_DIR_I( 1);	//BT_ATEN设置为无上拉电阻输入 GPIO_IOCFG_P5_DIR_O( 1);
	GPIO_IOCFG_P5_DIR_O( 2);
	GPIO_IOCFG_P5_DIR_O( 3);
	GPIO_IOCFG_P5_DIR_O( 4);
	GPIO_IOCFG_P5_DIR_O( 5);
	GPIO_IOCFG_P5_DIR_O( 6);
	GPIO_IOCFG_P5_DIR_O( 7);
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
	GPIO_IOCFG_P5_SET_0( 0);	// 上电不使能
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
	GPIO_IOCFG_P7_DIR_O( 5);
	GPIO_IOCFG_P7_DIR_O( 6);
	GPIO_IOCFG_P7_DIR_O( 7);
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
	GPIO_IOCFG_P9_DIR_O( 2);
	GPIO_IOCFG_P9_DIR_O( 3);
	GPIO_IOCFG_P9_DIR_O( 4);
	GPIO_IOCFG_P9_DIR_O( 5);
	GPIO_IOCFG_P9_DIR_O( 6);
	GPIO_IOCFG_P9_DIR_O( 7);	
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
	ADCH=0;
} 

#elif ((METER_TYPE == METER_TYPE_DDSY666)||( METER_TYPE == METER_TYPE_DTSY666 ))

void ApiPwOn_McuGpioInit(void)
{
// @brief P0口 总共4根口线 p0.1/2/3/7  Relay1/Relay2/Null/Null
	// 方向
	GPIO_IOCFG_P0_DIR_O( 1);// 01 跳闸 10 合闸
	GPIO_IOCFG_P0_DIR_O( 2);
	GPIO_IOCFG_P0_DIR_I( 3);
	#if ( METER_TYPE != METER_TYPE_DTSY666)
	GPIO_IOCFG_P0_DIR_I( 7);
	#else
	GPIO_IOCFG_P0_DIR_O( 7);
	#endif
	
	// 上拉     0        
	GPIO_IOCFG_P0_PUP_F( 1);
	GPIO_IOCFG_P0_PUP_F( 2);
	GPIO_IOCFG_P0_PUP_F( 3);
	GPIO_IOCFG_P0_PUP_F( 7);
	// 状态     0        
	GPIO_IOCFG_P0_SET_0( 1);
	GPIO_IOCFG_P0_SET_0( 2);
	GPIO_IOCFG_P0_SET_0( 3);
	GPIO_IOCFG_P0_SET_0( 7);
	// 输出模式选择      
	GPIO_IOCFG_P0_OUT_C( 1);	// 开启推挽
	GPIO_IOCFG_P0_OUT_C( 2);
	GPIO_IOCFG_P0_OUT_N( 3);
	#if ( METER_TYPE == METER_TYPE_DTSY666)
	GPIO_IOCFG_P0_OUT_C( 7);
	#else
	GPIO_IOCFG_P0_OUT_N( 7);
	#endif
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


// @brief P1口 总共3根口线 p1.0/3/4	 Null/LED_yellow/PFout
	// 方向  三相表P1.0为DISPKEY
	GPIO_IOCFG_P1_DIR_I( 0);
	GPIO_IOCFG_P1_DIR_O( 3);
	GPIO_IOCFG_P1_DIR_I( 4);
	// 上拉     1        
	GPIO_IOCFG_P1_PUP_F( 0);
	GPIO_IOCFG_P1_PUP_F( 3);
	GPIO_IOCFG_P1_PUP_F( 4);
	// 状态     1        
	GPIO_IOCFG_P1_SET_0( 0);
	GPIO_IOCFG_P1_SET_1( 3);///跳闸不点亮///后续液晶显示时在同时点亮跳闸灯
	GPIO_IOCFG_P1_SET_1( 4);

// @brief P2口 总共3根口线 p2.2/6/7	DISPKEY / 485RXD / 485TXD
///三相表P2.2为Pulsein
	GPIO_IOCFG_P2_DIR_I( 2);
	GPIO_IOCFG_P2_DIR_I( 6);
	GPIO_IOCFG_P2_DIR_O( 7);
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
	GPIO_IOCFG_P3_DIR_O( 1);
	GPIO_IOCFG_P3_DIR_O( 4);
	GPIO_IOCFG_P3_DIR_I( 5);	//BT_ATEN设置为无上拉电阻输入 GPIO_IOCFG_P3_DIR_O( 5);
	GPIO_IOCFG_P3_DIR_O( 6);
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
	GPIO_IOCFG_P3_SET_1( 5);	// 先输出高，使用的时候输出低
	GPIO_IOCFG_P3_SET_1( 6); 	// 电表上电时，蓝牙模块先不进行供电：0供电，1不供电
	// 输出模式选择
	GPIO_IOCFG_P3_OUT_N( 0);
	GPIO_IOCFG_P3_OUT_N( 1);
	GPIO_IOCFG_P3_OUT_N( 4);
	GPIO_IOCFG_P3_OUT_N( 5);
	GPIO_IOCFG_P3_OUT_N( 6);

// @brief P4口 总共4根口线 p4.4/5/6/7 SEG9/SEG10/SEG11/SEG12
	GPIO_IOCFG_P4_DIR_I( 4);
	GPIO_IOCFG_P4_DIR_O( 5);
	GPIO_IOCFG_P4_DIR_O( 6);
	GPIO_IOCFG_P4_DIR_O( 7);
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
	GPIO_IOCFG_P5_DIR_O( 0);
	GPIO_IOCFG_P5_DIR_O( 1);
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
	GPIO_IOCFG_P6_DIR_O( 1);
	GPIO_IOCFG_P6_DIR_O( 2);
	GPIO_IOCFG_P6_DIR_O( 3);
	GPIO_IOCFG_P6_DIR_O( 4);
	GPIO_IOCFG_P6_DIR_O( 5);
	GPIO_IOCFG_P6_DIR_O( 6);
	GPIO_IOCFG_P6_DIR_O( 7);
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
	GPIO_IOCFG_P7_DIR_O( 0);
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
	GPIO_IOCFG_P8_DIR_O( 6);
	GPIO_IOCFG_P8_DIR_O( 7);
	// 上拉     8        
	GPIO_IOCFG_P8_PUP_F( 6);
	GPIO_IOCFG_P8_PUP_F( 7);
	// 状态     8        
	GPIO_IOCFG_P8_SET_1( 6);
	GPIO_IOCFG_P8_SET_1( 7); 

// @brief P9口 总共8根口线 p9.0/1/2/3/4/5/6/7   WP/ LED_CTL/ COM1-COM6 / 
	GPIO_IOCFG_P9_DIR_I( 0);	
	GPIO_IOCFG_P9_DIR_I( 1);	// 先设置成输入,免得上电的时候闪一下
	GPIO_IOCFG_P9_DIR_O( 2);
	GPIO_IOCFG_P9_DIR_O( 3);
	GPIO_IOCFG_P9_DIR_O( 4);
	GPIO_IOCFG_P9_DIR_O( 5);
	GPIO_IOCFG_P9_DIR_O( 6);
	GPIO_IOCFG_P9_DIR_O( 7);	
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
	GPIO_IOCFG_P9_SET_1( 0);
	GPIO_IOCFG_P9_SET_0( 1);  // 背光点亮
	GPIO_IOCFG_P9_SET_0( 2);
	GPIO_IOCFG_P9_SET_0( 3); 
	GPIO_IOCFG_P9_SET_0( 4);
	GPIO_IOCFG_P9_SET_0( 5); 
	GPIO_IOCFG_P9_SET_0( 6);
	GPIO_IOCFG_P9_SET_0( 7); 
	
	ADCH=0;

}
#endif 
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    上电显示参数配置
 *
 *  @return   none
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void ApiPwOn_McuDispInit(void)
{
	LCDDrv_Init(POWER_ON);	// 初始化液晶驱动，不涉及显示
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    上电定时器配置
 *
 *  @return   none
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void ApiPwOn_McuTimerInit(void)
{
	uchar8 V_ucResult = _OK;
// @brief 基本节拍定时器  用TIMER0实现，定时1ms 
	
	TMOD  &= ~( TMOD_GATE0 | TMOD_CT0 );
	
	do
	{ 
		if( TMOD_T0_MODE1 != (TMOD & TMOD_T0_MODE_ALL) )
		{ 
			TMOD  &= TMOD_T0_MODE_CLR;
			TMOD  |= TMOD_T0_MODE1;						// 01： 方式1， 16位向上计数计数器/定时器  
			V_ucResult = _NOK;
		}
		
		if( TCON1 != TCON1_TCLKP0 )
		{
			TCON1 = TCON1_TCLKP0;						// 系统时钟作为定时器时钟源，不分频
			V_ucResult = _NOK;
		}
		
		if( (IEN0 & IEN0_ET0) != IEN0_ET0 )
		{
			IEN0 |=  IEN0_ET0;
			V_ucResult = _NOK;
		}
		
		TCON &= ~(TCON_TF1 | TCON_TR1);		// 不启用定时器1，清除标志并停止
		
	}while(0);
	
	if( _NOK == V_ucResult )
	{
		TL0 = T_Xms_TL0;
		TH0 = T_Xms_TH0;
	}
	
	START_TR0();
	
}
/*------------------------------------------------------------------------------------------------------*/
/**EC
 *  @brief    中断配置
 *
 *  @return   none
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
static void ApiPwOn_McuInterruptInit(void)
{
	#if ( METER_TYPE == METER_TYPE_DTSY666)
	do
	{ 
		if( (IEN0 & IEN0_EX4) != IEN0_EX4 )
		{ 
			IEN0 |=  IEN0_EX4;    ////开启外部中断4，用于检测脉冲
		}
		IENX=0x10;   ///允许使用外部中断44
		EXCON1= 0x20;///上升沿触发外部中断
		EXF0=0;
		
	}while(0);
	
	#endif
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    上电通信配置
 *
 *  @return   none
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void ApiPwOn_McuUartInit(void)
{
	ApiPwOn_McuUartXInit(CH_UART_UART0);
	ApiPwOn_McuUartXInit(CH_UART_UART1);
	ApiPwOn_McuUartXInit(CH_UART_UART2);
	ApiPwOn_McuUartXInit(CH_UART_UART3); 
}
 
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    EUARTX 配置 
 *
 *  @param    v_ucChID : 根据通道来初始化对应的串口通道
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void ApiPwOn_McuUartXInit(uchar8 v_ucChID)
{
	uchar8	V_ucTemp;
// @brief 判断通道，根据通道初始化对应串口
	switch (v_ucChID)
	{
		case CH_UART_UART0:	// 485,作为备用接口，波特率设定为9600bps
		{
			#if( UART0_ENABLE == _ENABLE ) 
			{
				// 配置控制寄存器
				if( PCON != 0X00) { PCON = 0X00; }
				if( (SCON | SCON_TB8) != 0x00 ) { SCON &= ~SCON_TB8;}
				if( (SCON & ( SCON_SM1_RXOV | SCON_SM0_FE ) ) != ( SCON_SM1_RXOV | SCON_SM0_FE ) )
				{
					SCON |= ( SCON_SM1_RXOV | SCON_SM0_FE );	// 8位uart 可变波特率，异步全双工
				}
				
				// 配置IO口
				UART0_IOCFG_RXD();	// 485RXD 设置成输入，开启上拉  
				UART0_IOCFG_TXD();
				
				// 设置波特率	@8Mhz 9600
				ApiPwOn_McuUartXSetBps(CH_UART_UART0);
				 
				// 清空缓冲区、接收使能、允许中断
				ApiComm_CommParaInit(CH_485);
				V_ucTemp = SBUF;
				SCON &= ~(SCON_RI | SCON_TI);
				SCON |=  SCON_REN;
				IEN0 |=  IEN0_ES0;  
			}
			#endif 
		}break;
		
		case CH_UART_UART1:	// 蓝牙
		{
			#if( UART1_ENABLE == _ENABLE ) 
			{
				// 配置控制寄存器
				if( PCON != 0X00) { PCON = 0X00; }
				SCON1 &=  ~( SCON1_TB81 | SCON1_RB81); // 清除第9位			
				SCON1 |= ( SCON1_SM10_FE | SCON1_SM11_RXOV );	// 9位uart 可变波特率，异步全双工
				
				// 配置IO口 
				UART1_IOCFG_RXD();
				UART1_IOCFG_TXD();
				
				// 设置波特率	@8Mhz 38400
				ApiPwOn_McuUartXSetBps(CH_UART_UART1);
				 
				// 清空缓冲区、接收使能、允许中断
				ApiComm_CommParaInit(CH_BLE);
				V_ucTemp = SBUF1;
				SCON1 &= ~(SCON1_RI1 | SCON1_TI1);
				SCON1 |= SCON1_REN1;
				IEN1  |= IEN1_ES1;
			} 
			#endif
		}break;
		
		case CH_UART_UART2:	// 7021A没有这个通道
		{
			
		}break;
		
		
		case CH_UART_UART3:	// 预留uart3
		{
			
		}break;
		
		
		default: break;
	}
	
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    EUARTX 配置 
 *
 *  @param    v_ucChID : 根据通道来初始化对应的串口通道
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void ApiPwOn_UART_SendEn(uchar8 v_ucChID)
{
		uchar8	V_ucTemp;
// @brief 判断通道，根据通道初始化对应串口
	switch (v_ucChID)
	{
		case CH_UART_UART0:	// 485,作为备用接口，波特率设定为9600bps
		{
			if( PCON != 0X00) { PCON = 0X00; }
			SCON &= ~SCON_TB8;
			
			SCON |= ( SCON_SM1_RXOV | SCON_SM0_FE );	// 8位uart 可变波特率，异步全双工
			
			// 设置波特率	@8Mhz  
			ApiPwOn_McuUartXSetBps(CH_UART_UART0);
			
			// 清空缓冲区、接收禁止、清除发送接收中断标志、允许中断
			V_ucTemp = SBUF;
			SCON &= ~(SCON_RI | SCON_TI | SCON_REN); 
			IEN0 |=  IEN0_ES0;
			
		}break;
		
		case CH_UART_UART1:	// 蓝牙
		{
			if( PCON != 0X00) { PCON = 0X00; }
			SCON1 &= ~( SCON1_TB81 | SCON1_RB81);
			
			SCON1 |= ( SCON1_SM10_FE | SCON1_SM11_RXOV );	// 方式3 9位uart 可变波特率，异步全双工
			
			// 设置波特率	@8Mhz 38400
			ApiPwOn_McuUartXSetBps(CH_UART_UART1);
			
			// 清空缓冲区、接收禁止、清除发送接收中断标志、允许中断
			V_ucTemp = SBUF1;
			SCON1 &= ~( SCON1_RI1 | SCON_TI | SCON1_REN1); 			
			IEN1  |= IEN1_ES1;
			 
		}break;
		
		case CH_UART_UART2:	// 7021A没有这个通道
		{
			
		}break;
		
		
		case CH_UART_UART3:	// 预留uart3
		{
			
		}break;
		
		
		default: break;
	}
}
void ApiPwOn_McuUartXSetBps(uchar8 v_ucChID)
{
// 	uchar8	V_ucTemp;
	
// @brief 判断通道，根据通道初始化对应串口
	switch (v_ucChID)
	{
		case CH_UART_UART0:	// 485,作为备用接口，波特率设定为9600bps
		{  
			// 设置波特率	@8Mhz  9600bps
			if( SBRTL != 0xCC ) { SBRTL  = 0xCC; }
			if( SBRTH != 0x7F ) { SBRTH  = 0x7F; }
			 
			if( (SFINE & 0x0F)  != 0x01 ) // bit3-0 管euart0
			{ 
				SFINE &= 0xF0; 
				SFINE |= 0x01; 
			}
			
			if( (SBRTH & 0x80) != 0x80) { SBRTH |= 0x80; }	// 波特率发生器使能 
			
		}break;
		
		case CH_UART_UART1:	// 蓝牙
		{ 
			
//			// 设置波特率	@8Mhz 9600 485通信
//			if( SBRT1L != 0xCC) { SBRT1L = 0xCC; }	// 38400
//			if( SBRT1H != 0x7F) { SBRT1H = 0x7F; }

//			if( (SFINE & 0x0F)  != 0x01 ) //  bit7-4 管euart1	 38400 设置成0
//			{
//				SFINE &=  0xF0; 
//				SFINE |= 0x01; 
//			}
//			
//			if( (SBRT1H & 0x80) != 0x80) { SBRT1H |= 0x80; }	// 波特率发生器使能 
			// 设置波特率	@8Mhz 38400 蓝牙通信
			if( SBRT1L != 0xF3) { SBRT1L = 0xF3; }	// 38400
			if( SBRT1H != 0x7F) { SBRT1H = 0x7F; }

			if( (SFINE & 0xf0)  != 0x00 ) //  bit7-4 管euart1	 38400 设置成0
			{
				SFINE &=  0x0F; 
			}
			
			if( (SBRT1H & 0x80) != 0x80) { SBRT1H |= 0x80; }	 // 波特率发生器使能 
			
		}break;
		
		case CH_UART_UART2:	// 7021A没有这个通道
		{
			
		}break;
		
		
		case CH_UART_UART3:	// 预留uart3
		{
			
		}break;
		
		
		default: break;
	}
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    上电配置计量模块
 *
 *  @return   none
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/

static void ApiPwOn_EMUInit(void)
{
	ApiMS_InitMeterICPara();
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    电表初始化（厂内执行)
 *
 *  @return   none
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/

void ApiPwOn_MeterInitInFactory(void)
{
	uchar8 V_TempData[7]= { 1 , 2 , 10 , 11 , 9 , 3 , 4  } ;///当前正向电量、反向电量、剩余金额、透支金额、电价、通信地址高4低8
	uchar8 V_ucTemp[9];
	/*------------------------------------------------------------------------------------------------------*/
	// @brief 电表清零
	ApiPwOn_MeterClear();
//	GV_ClearFlag=CommClear;
	/*------------------------------------------------------------------------------------------------------*/
	// @brief 参数初始化
	/* 电能表信息 */
	if( _SUCCESS != LibPub_ReadDataFromE2prom(LIB_E2P_METER_INFO, 0, &GStr_MeterIFO.ucaCommAddr[0]) )
	{
		LibPub_MemSetBytes( &GStr_MeterIFO.ucaCommAddr[0], 0x00, GStr_METER_IFO_Type_LEN ) ;
		GStr_MeterIFO.ucaCommAddr[5] = 0x01;
		GStr_MeterIFO.ucaMeterID[5] = 0x01;
		GStr_MeterIFO.ucaUserID[5] = 0x01;
		GStr_MeterIFO.ucVoltageTrans[2] = 0x01;
		GStr_MeterIFO.ucCurrentTrans[2]=0x01;///PTCT均为1
		GStr_MeterIFO.ucBpsVal = 0xff;
		
		LibPub_WriteDataToE2prom(LIB_E2P_METER_INFO, 0, &GStr_MeterIFO.ucaCommAddr[0]) ;
		
	}
	/*---------------------------------------------------------------------------------------------------*/
	///蓝牙相关参数		
	///如果通信地址改变，更改蓝牙参数
	BleDrv_InitBleRunPara();
	GStr_BLEGroup.ucBleTPL = 0x00;		//发射功率默认00级
	BleDrv_SetBleTPL( &GStr_BLEGroup.ucBleTPL );
	
	/* 计算一下crc，将参数写入E2  */
	GStr_BLEGroup.usCRC16 = LibPub_CRC16_CCITT(&GStr_BLEGroup.ucBleMAC[0], GStr_BLE_GROUP_TypeLEN-2); 
	LibPub_WriteDataToE2prom( LIB_E2P_BLE_PARA, 0, &GStr_BLEGroup.ucBleMAC[0]);	
	
	///功能配置参数
		LibPub_MemSetBytes( (uchar8*)&GStr_FunConfigPara.ucFunCurrentVal, 0x00, GStr_FUN_CONFIG_TypeLEN ) ;
		GStr_FunConfigPara.ucFunCurrentVal = 0x03;		///* 默认5A *///
		#if ( METER_TYPE != METER_TYPE_DTSY666)
			GStr_FunConfigPara.ucFunMeterConst = 0x10;		///* 默认常数10（16：即1600）
		#else
			GStr_FunConfigPara.ucFunMeterConst = 0x08;		///* 默认常数10（8：即800）
		#endif
		LibPub_WriteDataToE2prom(LIB_E2P_FUN_CONFIG, 0, (uchar8*)&GStr_FunConfigPara.ucFunCurrentVal) ;////写EE
	
	/*------------------------------------------------------------------------------------------------------*/
	/* 显示参数 */
//	if ( _SUCCESS != LibPub_ReadDataFromE2prom(LIB_E2P_Display_Para, 0, &GStr_DisplayPara.ucFullDisp_Time) )
	{
		GStr_DisplayPara.ucFullDisp_Time=LCD_DISP_FULL_TIME;// 上电全显时间默认5s
		GStr_DisplayPara.ucDispDurTime=LCD_DISP_DUR_TIME;	// 每屏显示时间默认5s
		GStr_DisplayPara.ucAutoDispNum= 7 ;           		// 循显默认7屏，当前正向电量、反向电量、剩余金额、透支金额、电价、通信地址高4低8
		GStr_DisplayPara.ucKeyDispNum=  7;              	// 键显默认7  当前正向电量、反向电量、剩余金额、透支金额、电价、通信地址高4低8
	    
		LibPub_WriteDataToE2prom(LIB_E2P_Display_Para, 0, &GStr_DisplayPara.ucFullDisp_Time) ;
	}
	    LibPub_MemSetBytes( GStr_DisplayPara.ucAutoDisptable, 0x00, 62 ) ;
	    LibPub_MemCopyBytes( V_TempData , GStr_DisplayPara.ucAutoDisptable , 7 );
		LibPub_MemCopyBytes( V_TempData , GStr_DisplayPara.ucKeyDisptable , 7 );
	    LibPub_WriteDataToE2prom(LIB_E2P_Display_Table, 0,  GStr_DisplayPara.ucAutoDisptable) ;
	    
//	if ( _FAILED == LibPub_ReadDataFromE2prom(LIB_E2P_Price, 0, &GStr_PRICE.ucaPrice[0]) )
	{
		LibPub_MemSetBytes( &GStr_PRICE.ucaPrice[0], 0x00, GStr_PRICE_Type_LEN ) ;
		GStr_PRICE.ucaPrice[2]=0x50;///电价默认为0.5
		LibPub_WriteDataToE2prom(LIB_E2P_Price, 0, &GStr_PRICE.ucaPrice[0]);
	}
	
	/*------------------------------------------------------------------------------------------------------*/
  	///本地报警参数
//	if ( _SUCCESS != LibPub_ReadDataFromE2prom(LIB_E2P_Money_Para, 0, GStr_MoneyPara.ucaAlarmMoneyL1) )
	{
		LibPub_MemSetBytes( &GStr_MoneyPara.ucaAlarmMoneyL1[0], 0x00, GStr_MONEY_PARA_Type_LEN ) ;///囤积金额、透支金额、合闸允许金额、过载功率为0  不开启
		GStr_MoneyPara.ucaAlarmMoneyL1[2] = 0x20;    /*报警金额一级   00002000*/
		GStr_MoneyPara.ucaAlarmMoneyL2[2] = 0x10;    /*报警金额二级   00001000 */  
		GStr_MoneyPara.ucaMaxMoneyLimit[0] = 0x10;   /*囤积金额限值设置为100000.00*/
		
		LibPub_WriteDataToE2prom(LIB_E2P_Money_Para, 0, GStr_MoneyPara.ucaAlarmMoneyL1) ;
	}
	///密码默认为0
	LibPub_MemSetBytes( V_ucTemp, 0x00, 9 ) ;
	LibPub_WriteDataToE2prom(LIB_E2P_Password, 0, V_ucTemp) ;///密码默认为0 并写EE	
	LibPub_MemSetBytes(GStr_Counter.ucPasswordErr_Cnt,0x00,3);//密码错计数器清零
	PrepaymentModule_Comm_ClrMACErrNum();//清挂起标志
	LibPub_MemSetBytes( (uchar8*)&GStr_Monitor.usPasswordErrTime, 0x00, 8 ) ;///24小时定时器清零
	
	/*------------------------------------------------------------------------------------------------------*/
	// 系统运行标志
    GStr_Flag.ucRunState = 0;///运行标志清0
    LibPub_WriteDataToE2prom(LIB_E2P_RUN_STATE,0,&GStr_Flag.ucRunState);
    GStr_Flag.ucRunState1 = 0;
	GStr_Flag.ucRunState2=0;
	
	
	LibPub_MemSetBytes((uchar8*) &GStr_AVAIL.us_IDAvailTimer, 0x00, GStr_AVAIL_TypeLEN ) ;
	LibPub_WriteDataToE2prom(LIB_E2P_SecretKey,0,&GStr_AVAIL.ucE2Key);
	///清开户、退费、密钥状态标志、密钥写为0并存EE
	///身份认证有效时长剩余时间也清零，需重新身份认证
	GStr_AVAIL.us_IDAvailTimer=5;///身份认证有效时长为5min
	LibPub_WriteDataToE2prom(LIB_E2P_AvailTimer,0,(uchar8*) &GStr_AVAIL.us_IDAvailTimer);
	
	ApiRelay_SubtractMoneyRelayJudge();
	ApiRelay_ControlProcess();
	
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    电表清零
 *
 *  @return   none
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void ApiPwOn_MeterClear()
{
	uchar8 V_ucCnt_i,V_ucTempBuff[4];
	///* 电量清零 包括小数电量、脉冲电量等都需要清零 *///
	///* 正反向电量清零 *///
	LibPub_MemSetBytes( &GStr_Energy.ucaFw_Energy[0], 0x00, GStr_ENERGY_Type_LEN );
	LibPub_WriteDataToE2prom( LIB_E2P_ENRGY, 0, &GStr_Energy.ucaFw_Energy[0] );///整数电量写EE

	///* 小数电量 *///
	LibPub_MemSetBytes( &GStr_EnergyPulseFw.ucPulseAdd, 0x00, GStr_ENERGY_PULSE_Type_LEN);	///* 正向脉冲包括尾数和小数电量 *///
	LibPub_MemSetBytes( &GStr_EnergyPulseBk.ucPulseAdd, 0x00, GStr_ENERGY_PULSE_Type_LEN);	///* 反向脉冲包括尾数和小数电量 *///
	LibPub_MemSetBytes( &GStr_ENERGYDEC.ucaFw_EnergyDec[0], 0x00, GStr_ENERGYDEC_Type_LEN);///
	for ( V_ucCnt_i=0; V_ucCnt_i<13; V_ucCnt_i++ )
	{
		LibPub_WriteDataToE2prom( LIB_E2P_ENERGY_DECPULSE_FW, V_ucCnt_i, (uchar8 *)&GStr_EnergyPulseFw.ucPulseAdd);
		LibPub_WriteDataToE2prom( LIB_E2P_ENERGY_DECPULSE_BK, V_ucCnt_i, (uchar8 *)&GStr_EnergyPulseBk.ucPulseAdd);
	} 
    
	///小数位写EE
	V_ucTempBuff[0] =   GStr_EnergyPulseFw.ucaPulseRemain[0];
	V_ucTempBuff[1] =  ~GStr_EnergyPulseFw.ucaPulseRemain[0];
	V_ucTempBuff[2] =   GStr_EnergyPulseBk.ucaPulseRemain[0];
	V_ucTempBuff[3] =  ~GStr_EnergyPulseBk.ucaPulseRemain[0]; 
	LibPub_WriteDataToE2prom( LIB_E2P_ENERGY_DECPULSE_WS, 0, V_ucTempBuff );	///* 脉冲尾数存一下， *///
	
	///剩余金额 透支金额 购电金额清零    电价不变
//	if(v_ClearFlag==CommClear)///通信总清
//	{
			LibPub_MemSetBytes( &GStr_Money.ucaRemainMoney[0], 0x00, 12 );  ///透支金额 剩余金额 清零
			LibPub_MemSetBytes( &GStr_PRICE.ucaPurchaseMoneyAll[0], 0x00, 4 );  ///购电金额 清零  
			LibPub_MemSetBytes( &GStr_PRICE.ucPurchaseTimes[0], 0x00, 4 );  ///购电次数 清零
			GStr_Money.usCRC16=LibPub_CRC16_CCITT(&GStr_Money.ucaRemainMoney[0],GStr_MONEY_Type_LEN-2);
			LibPub_WriteDataToE2prom(LIB_E2P_Money, 0, &GStr_Money.ucaRemainMoney[0]);
			LibPub_WriteDataToE2prom(LIB_E2P_Price, 0, &GStr_PRICE.ucaPrice[0]);
//	}
	for(V_ucCnt_i=0;V_ucCnt_i<4;V_ucCnt_i++)
    {
		DrvE2p_WriteData((LIB_E2P_HoldFirstMoney_Addr+V_ucCnt_i*14),&GStr_Money.ucaRemainMoney[0],14);
	}///将定时存储金额的EE区域清零
	
	///事件清零  事件次数  事件指针清零
	 if(GStr_Flag.ucMeterMode &F_FACTORY_MODE)//厂内通信清零清次数和指针，厂外钱包初始化不清
	{
		LibPub_MemSetBytes( &GStr_EventRecordNum.ucEventTimes[0][0], 0x00, 4);  ///清零次数
		GStr_EventNumPiont.uc_Num[0]=0;
		GStr_EventValidPiont.uc_Point[0]=0;
	}
	LibPub_MemSetBytes( &GStr_EventRecordNum.ucEventTimes[1][0], 0x00, 4);  ///次数
	LibPub_MemSetBytes( &GStr_EventRecordNum.ucEventTimes[2][0], 0x00, 4);  ///次数
	LibPub_MemSetBytes( &GStr_EventRecordNum.ucEventTimes[3][0], 0x00, 4);  ///次数
	LibPub_MemSetBytes( &GStr_EventRecordNum.ucEventTimes[4][0], 0x00, 4);  ///次数
	LibPub_MemSetBytes( &GStr_EventRecordNum.ucEventTimes[5][0], 0x00, 4);  ///次数
	GStr_EventRecordNum.usCRC16=LibPub_CRC16_CCITT(&GStr_EventRecordNum.ucEventTimes[0][0],GStr_EventRecordNum_TypeLEN-2);
	LibPub_WriteDataToE2prom(LIB_E2P_EventNum, 0, &GStr_EventRecordNum.ucEventTimes[0][0] );
	
	LibPub_MemSetBytes( &GStr_EventNumPiont.uc_Num[1], 0x00, 5);
	GStr_EventNumPiont.usCRC16=LibPub_CRC16_CCITT(&GStr_EventNumPiont.uc_Num[0],GStr_EventNumPiont_TypeLEN-2);
	
    LibPub_MemSetBytes( &GStr_EventValidPiont.uc_Point[1],0x00,5);///有效指针和循环指针清零 包含CRC
	GStr_EventValidPiont.usCRC16=LibPub_CRC16_CCITT(&GStr_EventValidPiont.uc_Point[0],GStr_EventValidPiont_TypeLEN-2);
	
	LibPub_WriteDataToE2prom(LIB_E2P_EventNumPiont, 0,  &GStr_EventNumPiont.uc_Num[0]);
	LibPub_WriteDataToE2prom(LIB_E2P_EventValidPiont, 0, &GStr_EventValidPiont.uc_Point[0] );
	
	GStr_Flag.ucRunState = 0;///运行标志清0
    LibPub_WriteDataToE2prom(LIB_E2P_RUN_STATE,0,&GStr_Flag.ucRunState);
    GStr_Flag.ucRunState1 = 0;
	GStr_Flag.ucRunState2&=F_RUN_RELAY_STATE;///除了跳合闸状态其他都清掉
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    电表信息效验   通信地址  表号客户编号  清零次数 购电次数
 *
 *  @return   none
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void ApiPwOn_MeterInfoParaCheck(void)
{
	
	if ( _TRUE != LibPub_CrcCheck( &GStr_MeterIFO.ucaCommAddr[0], GStr_METER_IFO_Type_LEN-2, GStr_MeterIFO.usCRC16) )
	{
		if ( _FAILED == LibPub_ReadDataFromE2prom(LIB_E2P_METER_INFO, 0, &GStr_MeterIFO.ucaCommAddr[0]) )
		{
			LibPub_MemSetBytes( &GStr_MeterIFO.ucaCommAddr[0], 0x00, GStr_METER_IFO_Type_LEN ) ;
			GStr_MeterIFO.ucaCommAddr[5]=0x01;	///* 通信地址默认01 *///
			GStr_MeterIFO.ucaMeterID[5]=0x01;	///* 表号默认01 *///
			GStr_MeterIFO.ucaUserID[5]=0x01;	///* 户号默认01*///
			GStr_MeterIFO.ucVoltageTrans[2]=0x01;	///* pt默认01*///
			GStr_MeterIFO.ucCurrentTrans[2]=0x01;	///* CT默认01*///
			GStr_MeterIFO.ucBpsVal = 0xff;	///* 波特率默认2400bps *///后续待定
			
		}
	}
	#if ( METER_TYPE != METER_TYPE_DTSY666)
	if((GStr_MeterIFO.ucVoltageTrans[0]!=0)||(GStr_MeterIFO.ucVoltageTrans[1]!=0)||(GStr_MeterIFO.ucVoltageTrans[2]!=0x01)
	||(GStr_MeterIFO.ucCurrentTrans[0]!=0)||(GStr_MeterIFO.ucCurrentTrans[1]!=0)||(GStr_MeterIFO.ucCurrentTrans[2]!=0x01)
	)////非三相表电压电流互感器变比要默认为1
	{
		LibPub_MemSetBytes( &GStr_MeterIFO.ucVoltageTrans[0], 0x00, 6 ) ;
		GStr_MeterIFO.ucVoltageTrans[2]=0x01;	///* pt默认01*///
		GStr_MeterIFO.ucCurrentTrans[2]=0x01;	///* CT默认01*///
		LibPub_WriteDataToE2prom(LIB_E2P_METER_INFO, 0, &GStr_MeterIFO.ucaCommAddr[0]);
	}
	#endif
	///* 软I_J时间获取 *///
	if( _SUCCESS == LibPub_ReadDataFromE2prom( LIB_E2P_SOFTI_J, 0, ( uchar8*)&GStr_Monitor.ulSoftI_JTime) )
	{
		if ( GStr_Monitor.ulSoftI_JTime > FACTORY_MAX_TIME )
		{
			GStr_Monitor.ulSoftI_JTime = 0;
		}
	}
	else
	{
		GStr_Monitor.ulSoftI_JTime = 0;
	}
	///* 判断一下厂内状态 *///
	if( GStr_Monitor.ulSoftI_JTime )
	{
		GStr_Flag.ucMeterMode |= F_FACTORY_MODE;
	}
	else
	{ 
		GStr_Flag.ucMeterMode &= ~F_FACTORY_MODE;
	}
}


/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    显示信息效验
 *
 *  @return   none
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void ApiPwOn_DisplayParaCheck(void)
{
	uchar8 V_TempData[7]= { 1 , 2 , 10 , 11 , 9 , 3 , 4  } ;///当前正向电量、反向电量、剩余金额、透支金额、电价、通信地址高4低8
	if ( _TRUE != LibPub_CrcCheck( &GStr_DisplayPara.ucFullDisp_Time, 4, GStr_DisplayPara.usDisp_ParaCRC16) )
	///上电全显时间、每屏显示时间、循环显示屏数、按键显示屏数各1  
	{
		if ( _FAILED == LibPub_ReadDataFromE2prom(LIB_E2P_Display_Para, 0, &GStr_DisplayPara.ucFullDisp_Time) )
		{
			GStr_DisplayPara.ucFullDisp_Time=LCD_DISP_FULL_TIME;//上电全显时间默认5s
			GStr_DisplayPara.ucDispDurTime=LCD_DISP_DUR_TIME;//每屏显示时间默认5s
			GStr_DisplayPara.ucAutoDispNum= 7 ;           ///循显默认7屏，当前正向电量、反向电量、剩余金额、透支金额、电价、通信地址高4低8
			GStr_DisplayPara.ucKeyDispNum=  7;              ///键显默认7  当前正向电量、反向电量、剩余金额、透支金额、电价、通信地址高4低8

		}
	}	
	if(_TRUE != LibPub_CrcCheck( &GStr_DisplayPara.ucAutoDisptable[0], 60, GStr_DisplayPara.usDisp_tableCRC16))
	//循显、按键显示各30
	{
		if ( _FAILED == LibPub_ReadDataFromE2prom(LIB_E2P_Display_Table, 0, &GStr_DisplayPara.ucAutoDisptable[0]) )
		{
			LibPub_MemCopyBytes( V_TempData , GStr_DisplayPara.ucAutoDisptable , 7 );
			LibPub_MemCopyBytes( V_TempData , GStr_DisplayPara.ucKeyDisptable , 7 );
		}
	}
	if((GStr_DisplayPara.ucFullDisp_Time>30)||(GStr_DisplayPara.ucFullDisp_Time<05)) 
	{
		GStr_DisplayPara.ucFullDisp_Time=LCD_DISP_FULL_TIME;//上电全显时间默认5~30s,非法默认5s
	}
	if((GStr_DisplayPara.ucDispDurTime>30)||(GStr_DisplayPara.ucDispDurTime<05)) 
	{
		GStr_DisplayPara.ucDispDurTime=LCD_DISP_DUR_TIME;//循环显时间默认5~30s,非法默认5s
	}
	if(GStr_DisplayPara.ucAutoDispNum>30)///循显按键显示最大30屏，非法为7
	{
		GStr_DisplayPara.ucAutoDispNum= 7 ; 
	}
	if(GStr_DisplayPara.ucKeyDispNum>30)
	{
		GStr_DisplayPara.ucKeyDispNum=  7;   
	}
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    报警金额 透支金额 囤积金额过载功率等参数效验
 *
 *  @return   none
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void ApiPwOn_MoneyParaCheck(void)
{
    
	if ( _TRUE != LibPub_CrcCheck( &GStr_MoneyPara.ucaAlarmMoneyL1[0], GStr_MONEY_PARA_Type_LEN-2, GStr_MoneyPara.usCRC16) )
	///一级报警、二级报警、囤积金额、透支金额、过载功率
	{
		if ( _FAILED == LibPub_ReadDataFromE2prom(LIB_E2P_Money_Para, 0, &GStr_MoneyPara.ucaAlarmMoneyL1) )
		{
			LibPub_MemSetBytes( &GStr_MoneyPara.ucaAlarmMoneyL1[0], 0x00, GStr_MONEY_PARA_Type_LEN );	
			GStr_MoneyPara.ucaAlarmMoneyL1[1]=0x20;///* 一级报警0020*///
			GStr_MoneyPara.ucaAlarmMoneyL2[1]=0x10;///* 二级报警0010*///
			///过载功率为0  默认该功率无效\囤积
		}
	}
	if(_TRUE != LibPub_CrcCheck( &GStr_Money.ucaRemainMoney[0], GStr_MONEY_Type_LEN-2, GStr_Money.usCRC16) )
	{
		if ( _FAILED == LibPub_ReadDataFromE2prom(LIB_E2P_Money, 0, &GStr_Money.ucaRemainMoney[0]) )
		{
			LibPub_MemSetBytes( &GStr_Money.ucaRemainMoney[0], 0x00, GStr_MONEY_Type_LEN-2 );
            GStr_Money.ucaRemainMoney[3]=0x50;///默认剩余金额50 	
		
		}
	}

}


///*============================================================================================*///
///* Function:   	void ApiPwOn_DLXS_READ(GStr_ENERGY_PULSE_Type *p_strEnergyPulse,ushort16 v_usAddrIndex)									*///
///* Description:	读电量小数，																*///
///* Calls:    		无																			*///
///* Called By:  	无																			*///
///* Input:        	Add表示用电电量的小数地址，								*///											*///							    
///* Output:													*///
///* Return:		无																			*/// 				
///* Others:																					*///
///*============================================================================================*///
void ApiPwOn_DLXS_READ(GStr_ENERGY_PULSE_Type *p_strEnergyPulse,ushort16 v_usAddrIndex )
{
	uchar8	V_TempData[13];
	uchar8	i,j;	
		
	p_strEnergyPulse->ucPulseDecSavePtr=0;
	p_strEnergyPulse->ucPulseDecimal=0;
	p_strEnergyPulse->ucPulseDecSaveNoFF=0;
	
	LibPub_MemSetBytes(V_TempData,0X00,13);
	DrvE2p_ReadData(EEPROM_MAP_TAB[v_usAddrIndex].usE2pAddress,V_TempData,13);
	
	for(i=0;i<12;i++)
	{
		if(V_TempData[i]==0xff)
		{
			p_strEnergyPulse->ucPulseDecSavePtr++;
			p_strEnergyPulse->ucPulseDecimal+=8;
		}
		else
		{ 		
			break;		
		}
	}
	j=V_TempData[i];
	p_strEnergyPulse->ucPulseDecSaveNoFF=j;
	for(i=0;i<8;i++)
	{
		if((j&0x80)!=0)
		{
			p_strEnergyPulse->ucPulseDecimal+=1;
			 j=j<<1;			
		}
		else
		{
			   break;
		}
	}
		
}
///**********************************************************************///
///* Brief:  电量整数校验                                                */// 
///*                                                                    *///
///* Return: 正确回 _SUCCESS，错误回 FAILED                              *///
///*                                                                    *///
///* Note:   修改及其他说明                                              *///
///**********************************************************************///
uchar8 ApiPwOn_EnergyZSCheck(void)
{ 
	uchar8 V_ucResultChk = _SUCCESS;
	
	if (  _TRUE != LibPub_CrcCheck( &GStr_Energy.ucaFw_Energy[0], GStr_ENERGY_Type_LEN-2, GStr_Energy.usCRC16 ) )
	{
		 V_ucResultChk = LibPub_ReadDataFromE2prom( LIB_E2P_ENRGY, 0 , &GStr_Energy.ucaFw_Energy[0]);
	}
	
	return V_ucResultChk;
}
///**********************************************************************///
///* Brief:  电量参数校验                                                */// 
///*                                                                    *///
///* Return: 无                                                         *///
///*                                                                    *///
///* Note:   修改及其他说明                                              *///
///**********************************************************************///
void ApiPwOn_EnergyCheck(void)
{
//	uchar8 V_ucCnt;
	uchar8 V_ucaTempData[4];
	
	///* 整数电量 */// 
	if ( _SUCCESS == ApiPwOn_EnergyZSCheck() )
	{
		///* 小数电量 *///
		ApiPwOn_DLXS_READ(&GStr_EnergyPulseFw,LIB_E2P_ENERGY_DECPULSE_FW );
		GStr_Energy.ucaFw_Energy[3] = LibPub_1Hex_2_1BCD( GStr_EnergyPulseFw.ucPulseDecimal );///正向

		
		ApiPwOn_DLXS_READ(&GStr_EnergyPulseBk,LIB_E2P_ENERGY_DECPULSE_BK );
		GStr_Energy.ucaBk_Energy[3] = LibPub_1Hex_2_1BCD( GStr_EnergyPulseBk.ucPulseDecimal );///反向

		GStr_Energy.usCRC16 = LibPub_CRC16_CCITT ( &GStr_Energy.ucaFw_Energy[0], GStr_ENERGY_Type_LEN-2);
	}
	  
	///* 尾数,如果校验失败，补一半脉冲尾数  *///
	if ( _SUCCESS == LibPub_ReadDataFromE2prom(LIB_E2P_ENERGY_DECPULSE_WS, 0, V_ucaTempData ) )
	{
		if ( V_ucaTempData[1] != (uchar8)(~V_ucaTempData[0]) )
		{
			V_ucaTempData[0] = GStr_FunConfigPara.ucFunMeterConst / 2;
		}
		if ( V_ucaTempData[3] != (uchar8)(~V_ucaTempData[2]) )
		{
			V_ucaTempData[2] = GStr_FunConfigPara.ucFunMeterConst / 2;
		}
		GStr_EnergyPulseFw.ucaPulseRemain[0] = V_ucaTempData[0];
		GStr_EnergyPulseBk.ucaPulseRemain[0] = V_ucaTempData[2];
	}
	else
	{
		GStr_EnergyPulseFw.ucaPulseRemain[0] = GStr_FunConfigPara.ucFunMeterConst / 2;
		GStr_EnergyPulseBk.ucaPulseRemain[0] = GStr_FunConfigPara.ucFunMeterConst / 2;
	}

}

///**********************************************************************///
///* Brief:  校表参数校验                                                */// 
///*                                                                    *///
///* Return: 无                                                         *///
///*                                                                    *///
///* Note:   修改及其他说明                                              *///
///**********************************************************************///
void ApiPwOn_EmuParaCheck(void)
{ 
	ApiMS_MeterICParaCheck();
}

///**********************************************************************///
///* Brief:  电表信息参数校验                                            */// 
///*                                                                    *///
///* Return: 无                                                         *///
///*                                                                    *///
///* Note:   修改及其他说明                                              *///
///**********************************************************************///
void ApiPwOn_FunConfigParaCheck(void)
{
	if ( _TRUE != LibPub_CrcCheck( &GStr_FunConfigPara.ucFunCurrentVal, GStr_FUN_CONFIG_TypeLEN-2, GStr_FunConfigPara.usCRC16) )
	{
		if ( _FAILED == LibPub_ReadDataFromE2prom( LIB_E2P_FUN_CONFIG, 0, &GStr_FunConfigPara.ucFunCurrentVal) )
		{
			GStr_FunConfigPara.ucFunCurrentVal = 0x03;		///* 默认5A *///
			#if ( METER_TYPE != METER_TYPE_DTSY666)
			GStr_FunConfigPara.ucFunMeterConst = 0x10;		///* 默认常数10（16：即1600）
			#else
			GStr_FunConfigPara.ucFunMeterConst = 0x08;		///* 默认常数10（8：即800）
			#endif
		}
		
	}
	GStr_UIPDisplay.ucMeterConst[0]=0;
	GStr_UIPDisplay.ucMeterConst[1]=LibPub_1Hex_2_1BCD(GStr_FunConfigPara.ucFunMeterConst);
	GStr_UIPDisplay.ucMeterConst[2]=0;///给显示的常数赋值
}

//------------------------------------------------------------------------------//
/**
 *  @brief    掉电检测,主要检测是否掉电或真正上电，只需要返回是否掉电就可以了，不需要进入低功耗
 *
 *  @return   如果掉电则返回_TRUE,否则返回_FALSE
 *
 *  @note     xx
 *
 */
///**********************************************************************///
uchar8 ApiPwOn_PowerChk( void )
{ 
	ushort16 V_usCnti = 10000;
	
	while( (LPDCON2 & LPDCON2_LPD2F) == LPDCON2_LPD2F )
	{
		V_usCnti--;
		WDT_Clr();
		if( V_usCnti == 0 )
		{
			return _FALSE;
		}
	}
	
	return _TRUE;
}
///**********************************************************************///
///* Brief:     ///*定期效验密钥状态*///                                           */// 
///*                                                                    *///
///* Return: 无                                                         *///
///*                                                                    *///
///* Note:      ///*定期效验密钥状态*///                                            *///
///**********************************************************************///
void ApiPwOn_KeyStatusCheck(void)				      ///*定期效验密钥状态*///  
{ 
 	WDT_Clr();
	if ( _TRUE != LibPub_CrcCheck( (uchar8*)&GStr_AVAIL.us_IDAvailTimer, 3, GStr_AVAIL.usCRC16) )
	{
		if ( _FAILED == LibPub_ReadDataFromE2prom( LIB_E2P_AvailTimer, 0, (uchar8*)&GStr_AVAIL.us_IDAvailTimer) )
		{	
			GStr_AVAIL.us_IDAvailTimer = 5; 
			GStr_AVAIL.ucBackMonFlag = 0x00; 
			GStr_AVAIL. usCRC16= 0x00;
		}
	}	
	if( GStr_AVAIL.ucBackMonFlag & B0000_0100)
	{ 
		GStr_Flag.ucRunState2 |=  F_RUN_EsamKeyFlag;
	}
	else 
	{ 
		GStr_Flag.ucRunState2 &= ~F_RUN_EsamKeyFlag;
	}
	
	if( GStr_AVAIL.ucBackMonFlag & B0000_0010)
	{ 
		GStr_Flag.ucRunState2 |=  F_RUN_OpenAccoutFlag;
	}
	else 
	{ 
		GStr_Flag.ucRunState2 &=  ~F_RUN_OpenAccoutFlag;
	}

}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    上电配置蓝牙参数
 *
 *  @return   
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/

void ApiPwOn_BleInit(void)
{
	BleDrv_InitPwn();
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    蓝牙参数定时检查
 *
 *  @return   
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/

void ApiPwOn_BleParaChk(void)
{
	BleDrv_BleParaChk(TIMEING_Mode);			///* 定期检查蓝牙参数 *///
	
	GStr_Monitor.ucBleAdvCnt++;///蓝牙定时校验计数累加
	
	if( _BUSY != BleDrv_GetBleUartSta() )	// 不忙的时候再去查状态
	{
		BleDrv_BleStatuChk();
		/*数据接收完成后，需要初始化串口，设置通信状态*/
		Gstr_UartComm[CH_BLE].ucCommChStatus = API_COMM_STATUS_ERROR;
	}
}
///**********************************************************************///
///* Brief:     ///*定期效验事件指针*/// 和次数                                          */// 
///*                                                                    *///
///* Return: 无                                                         *///
///*                                                                    *///
///* Note:                                           *///
///**********************************************************************///
void ApiPwOn_EventPointCheck(void) 
{
	
	///* 轮换指针+计数指针*///
	if ( _TRUE != LibPub_CrcCheck( GStr_EventNumPiont.uc_Num, GStr_EventNumPiont_TypeLEN-2, GStr_EventNumPiont.usCRC16) )
	{
		if ( _FAILED == LibPub_ReadDataFromE2prom( LIB_E2P_EventNumPiont, 0, GStr_EventNumPiont.uc_Num) )
		{	
			LibPub_MemSetBytes(GStr_EventNumPiont.uc_Num,0x00, GStr_EventNumPiont_TypeLEN );
		}
	}	
	if ( _TRUE != LibPub_CrcCheck( GStr_EventValidPiont.uc_Point, GStr_EventValidPiont_TypeLEN-2, GStr_EventValidPiont.usCRC16) )
	{
		if ( _FAILED == LibPub_ReadDataFromE2prom( LIB_E2P_EventValidPiont, 0, GStr_EventValidPiont.uc_Point) )
		{	
			LibPub_MemSetBytes(GStr_EventValidPiont.uc_Point,0x00, GStr_EventValidPiont_TypeLEN );
		}
	}
	if(_TRUE != LibPub_CrcCheck( (uchar8*)&GStr_EventRecordNum.ucEventTimes[0][0], GStr_EventRecordNum_TypeLEN-2, GStr_EventRecordNum.usCRC16) )
	{
		if(_FAILED == LibPub_ReadDataFromE2prom( LIB_E2P_EventNum, 0, (uchar8*)&GStr_EventRecordNum.ucEventTimes[0][0]) )
		{
			LibPub_MemSetBytes(&GStr_EventRecordNum.ucEventTimes[0][0] , 0x00 , GStr_EventRecordNum_TypeLEN);	///* 次数默认0次  *///
		}
	}	
	
}

///**********************************************************************///
///* Brief:     ///上电效验剩余金额和透支金额    ///从备份或循环存储区恢复                                     */// 
///*                                                                    *///
///* Return: 无                                                         *///
///*                                                                    *///
///* Note:                                           *///
///**********************************************************************///
void ApiPwOn_RemainMoneyCheck(void) 
{
	uchar8 V_ucTempData[14],i;
	ushort16 V_usCRC16;
	uchar8 V_offset;
	uchar8 V_ucRemainMoneyData[30];
	uchar8 V_ucTickMoneyData[30];
	uchar8 V_ucResultData[6];
	
	DrvE2p_ReadData( LIB_E2P_Money_Addr, V_ucTempData, LIB_E2P_Money_Len);///读剩余金额和透支金额
	V_usCRC16  = (ushort16)V_ucTempData[13];
	V_usCRC16 |= (ushort16)(V_ucTempData[12] << 8); 
	if(V_usCRC16!=LibPub_CRC16_CCITT( V_ucTempData, 12 ))///主数据错
	{	
		
		DrvE2p_ReadData( LIB_E2P_Money_BAK_Addr, V_ucTempData, 14);
		V_usCRC16  = (ushort16)V_ucTempData[13];
	    V_usCRC16 |= (ushort16)(V_ucTempData[12] << 8); 
		if(V_usCRC16==LibPub_CRC16_CCITT( V_ucTempData, 12 ))
		{
			LibPub_MemCopyBytes(&V_ucTempData[0], &V_ucRemainMoneyData[0], 6);
			LibPub_MemCopyBytes(&V_ucTempData[6], &V_ucTickMoneyData[0], 6);
			V_offset=1; ////后面的数据放在备份数据后面 用于数组比对
		}
		else
		{
			V_offset=0;
		}
		for(i=0;i<4;i++)
		{
			DrvE2p_ReadData( LIB_E2P_HoldFirstMoney_Addr+i*LIB_E2P_HoldFirstMoney_Len, V_ucTempData, 14);
			V_usCRC16  = (ushort16)V_ucTempData[13];
			V_usCRC16 |= (ushort16)(V_ucTempData[12] << 8); 
			if(V_usCRC16==LibPub_CRC16_CCITT( V_ucTempData, 12 ))
		    {	
				LibPub_MemCopyBytes(&V_ucTempData[0],&V_ucRemainMoneyData[V_offset*6],6);
				LibPub_MemCopyBytes(&V_ucTempData[6],&V_ucTickMoneyData[V_offset*6],6);
				V_offset+=1;
			}
		}
		if(V_offset==1)///只有一份数据是对的
		{	
			LibPub_MemCopyBytes(&V_ucRemainMoneyData[0],&GStr_Money.ucaRemainMoney[0],6);	
			LibPub_MemCopyBytes(&V_ucTickMoneyData[0],&GStr_Money.ucaTickMoney[0],6);	
		}
		else if(V_offset>1)//不只一份数据是对的 就要进行比对了
		{
			LibPub_CompareNBufs(V_ucRemainMoneyData,V_ucResultData,6,V_offset,C_MIN,CMP_MODE_HIGHT);
			LibPub_MemCopyBytes(&V_ucResultData[0],&GStr_Money.ucaRemainMoney[0],6);///剩余金额最小的为准
			if(_FALSE==LibPub_ZeroCheck( &GStr_Money.ucaRemainMoney[0], 6))///剩余金额不为0，透支金额不用恢复直接写0
			{
				LibPub_MemSetBytes(&GStr_Money.ucaTickMoney[0],0x00,6);
			}
			else
			{
				LibPub_CompareNBufs(V_ucTickMoneyData,V_ucResultData,6,V_offset,C_MAX,CMP_MODE_HIGHT);	
				LibPub_MemCopyBytes(&V_ucResultData[0],&GStr_Money.ucaTickMoney[0],6);///透支金额以最大的为准
			}
		}
		else///没有数据是对的
		{
			LibPub_MemSetBytes(&GStr_Money.ucaRemainMoney[0],0x00,6);
			LibPub_MemSetBytes(&GStr_Money.ucaTickMoney[0],0x00,6);
		}
		GStr_Money.usCRC16= LibPub_CRC16_CCITT(&GStr_Money.ucaRemainMoney[0], GStr_MONEY_Type_LEN-2);
		LibPub_WriteDataToE2prom( LIB_E2P_Money, 0, &GStr_Money.ucaRemainMoney[0]);///更新主备份EE
	}
	else///主数据对
	{
		LibPub_MemCopyBytes(&V_ucTempData[0],&GStr_Money.ucaRemainMoney[0],14);////更新RAM中剩余金额和透支金额和crc
	}
}