/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    AppMonitor.c                                                                          
**** Brief:       定时监控文件                                                                     
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

void ApiMntr_PeripheralMonitor(void);

void ApiMntr_MonitorTask(void);
/*----------------< 函数定义 >----------------------------------*/




/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    定时监控函数，定式监控硬件，参数，寄存器配置等
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
 
void ApiMntr_MonitorTask(void)
{
	uchar8 i;
	// @brief  检测一下按键和厂内模式短接点
	ApiMntr_PeripheralMonitor();
	
	ApiPwOn_SysClkInit();	// 检查一下系统时钟
	
	ApiPwOn_McuTimerInit(); // 定时器检查（基本节拍定时器）
	
   // @brief  1S
	if ( _TRUE == LibPub_GetDiffTime( GStr_Monitor.ulTimers, LibPub_GetTimerBeat(), 1000) ) ///* 1S定时 *///
	{ 
		GStr_Monitor.ulTimers= LibPub_GetTimerBeat();
				
		if( GStr_Monitor.ucPowerOnTimer < 60 )
		{
			GStr_Monitor.ucPowerOnTimer++;				
			
			/* 上电5s（暂定）以后再操作蓝牙模组*/
			if( 5 == GStr_Monitor.ucPowerOnTimer )	
			{
				ApiPwOn_BleInit();
			}
		}
		
		APiDisp_LcdledControl(); 
		ApiRelay_ControlProcess();//每秒判断一次是否有跳闸但是没跳成功的
		Api_PowerLoadLimitedCheck();//过载跳闸检测
		if(GStr_Flag.ucRunState1&F_RUN_OVER_DEMAND_CLOSE)
		{
			if(_TRUE == LibPub_GetDiffTime( GStr_Monitor.ulOverDemandCloseTime, LibPub_GetTimerBeat(), 300000) )
			{///过载后5min 自动合闸
				GStr_Monitor.ulOverDemandCloseTime=LibPub_GetTimerBeat();
				GStr_Flag.ucRunState1 &=~F_RUN_OVER_DEMAND_CLOSE;///请过载恢复合闸命令，直接合闸
				ApiRelay_ControlProcess();
			}
		}
		/*电表修改了通信地址，需要重启蓝牙模块，设置蓝牙参数*/
		if( (BLE_STAT_RST == GStr_Flag.ucBLESTATFlag)
			|| (BLE_STAT_ERRREP == GStr_Flag.ucBLESTATFlag) )	/* 模块上报连接异常，直接复位 */
		{
			/*写完通信地址后需要重新设置蓝牙模块参数，并重新广播*/
			BleDrv_BleReset();
			BleDrv_InitBleRunPara();
			BleDrv_SetBleStat();	 
		}
//		if((GV_ClearFlag==MoneyClear)||(GV_ClearFlag==CommClear))///总清处理
//		{
//				ApiPwOn_MeterClear(GV_ClearFlag);
//		}
		if((!(GStr_Flag.ucRunState2&F_RUN_INTAUTHAvailabilityFlag))&&(GStr_Flag.ucRunState3&F_RUN_READ_RANDOM2))
		{
			if(_TRUE == LibPub_GetDiffTime( GStr_Monitor.ulReadRandom2DelayTime, LibPub_GetTimerBeat(), 300000) )
			///5min后身份认证还是失效，清标志，重新生成随机数2
			{
				GStr_Flag.ucRunState3 &=~F_RUN_READ_RANDOM2;///清读随机数标志
				PrepaymentModule_GetChallenge(&GStr_VirtualEsamPara.ucRs485RandNum2[0], 0x04) ;///获取随机数2
				LibPub_MemSetBytes(&GStr_VirtualEsamPara.ucRs485RandNum2[4], 0x00, 4);///随机数2重新生成
			}	
		}
		if(GStr_Flag.ucRunState2 &F_RUN_PROG_10MIN_FLAG)
		{
			if(_TRUE == LibPub_GetDiffTime( GStr_Monitor.ulProgEventDelayTime, LibPub_GetTimerBeat(), 600000) )
			{
				GStr_Flag.ucRunState2 &=~F_RUN_PROG_10MIN_FLAG;///请标志
			}
		}
		if(GStr_AVAIL.ulAutRemainingTime)
		{
			GStr_Flag.ucRunState2 |= F_RUN_INTAUTHAvailabilityFlag;
			GStr_AVAIL.ulAutRemainingTime--;
			if(0==GStr_AVAIL.ulAutRemainingTime)
			{
				GStr_Flag.ucRunState2 &= ~F_RUN_INTAUTHAvailabilityFlag;
			}
		}
		else
		{
			GStr_Flag.ucRunState2 &= ~F_RUN_INTAUTHAvailabilityFlag;
			GStr_Flag.ucRunState3 &=~F_RUN_READ_RANDOM2;///清读随机数标志
			PrepaymentModule_GetChallenge(&GStr_VirtualEsamPara.ucRs485RandNum2[0], 0x04) ;///获取随机数2
			LibPub_MemSetBytes(&GStr_VirtualEsamPara.ucRs485RandNum2[4], 0x00, 4);///随机数2重新生成
		}		
	}
	
	// @brief  1分钟定时监测相关参数 定时检测参数定时
	 
	if ( _TRUE == LibPub_GetDiffTime( GStr_Monitor.ulTimerMin, LibPub_GetTimerBeat(), 60000) ) ///* 1分钟 *///
	{
		GStr_Monitor.ulTimerMin = LibPub_GetTimerBeat();
		
		GStr_Flag.ucPowerOnFlag=0;///RAM错需要初始化计量
		
		ApiPwOn_EmuParaCheck() ; 		///* 计量参数校验 *///
		ApiPwOn_MeterInfoParaCheck();	///* 表信息，通信地址、表号、波特率、总清次数、购电次数 *///  
		ApiPwOn_DisplayParaCheck();     ///* 显示信息校验
		ApiPwOn_MoneyParaCheck();       ///* 报警金额等参数校验  包括剩余金额效验
		ApiMoney_RefreshPrice(); 		////*电价参数效验
		ApiPwOn_FunConfigParaCheck();	///* 功能配置定期检查 */// 
		ApiPwOn_KeyStatusCheck();       ///* 密钥状态和开户状态 *///
		ApiPwOn_BleParaChk();			///* 定期检查蓝牙参数 */// 
		ApiPwOn_EventPointCheck();      ///* 事件指针效验
		ApiMoney_TimeingHoldMoney();	///定时保存剩余金额和透支金额
		

	  
		for( i=0; i<4; i++)
		{
			if( GStr_Monitor.usPasswordErrTime[i] != 0 )
			{
				GStr_Monitor.usPasswordErrTime[i]--;
				if( GStr_Monitor.usPasswordErrTime[i] == 0 )
				{
					if( i== 3 )
					{
						PrepaymentModule_Comm_ClrMACErrNum();
					}
					else
					{
						GStr_Counter.ucPasswordErr_Cnt[i]=0;
					}

				}
			}
		}
		 
		if( GStr_Monitor.ulSoftI_JTime != 0 )
		{
			GStr_Flag.ucMeterMode |= F_FACTORY_MODE;
			
			GStr_Monitor.ulSoftI_JTime--;
			if( GStr_Monitor.ulSoftI_JTime == 0 )
			{
				GStr_Flag.ucMeterMode &= ~F_FACTORY_MODE;
			}
			LibPub_WriteDataToE2prom( LIB_E2P_SOFTI_J, 0, (uchar8 *)&GStr_Monitor.ulSoftI_JTime);
		}
		else
		{ 
			GStr_Flag.ucMeterMode &= ~F_FACTORY_MODE;
		}
		
		#if(METER_TYPE==METER_TYPE_DTSY666)	
		if(	(GStr_Flag.ucRunState3 & F_RUN_Relayact_Voltage) && !(GStr_Flag.ucRunState2&F_RUN_RELAY_STATE) )	//有一相电压高于82%Un,且电表认为是合闸状态
		{
			GStr_Counter.ucRelayon_Cnt++;
			if( GStr_Counter.ucRelayon_Cnt >= Relayon_Delaytimer )				//一定时间内没有脉冲信号，则认为电表合闸状态没有合闸
			{ 
				GStr_Counter.ucRelayon_Cnt = 0;
				RelayDrv_Closerelay();									//继电器合闸
				GStr_Counter.ucRelayDelay_Cnt = RelayOnce_Delaytimer;	//3s置位
			}
		}
		else
		{
			GStr_Counter.ucRelayon_Cnt = 0;
		}
		#endif
		
	} 
	
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    外设监控函数，主要是按键、短接点等///跳闸口线置位延时也在这里做
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
 
void ApiMntr_PeripheralMonitor(void)
{
	/* 5ms检测一次 */
	if ( _TRUE == LibPub_GetDiffTime( GStr_Monitor.ulTimer5ms, LibPub_GetTimerBeat(), 5) )
	{
		GStr_Monitor.ulTimer5ms =  LibPub_GetTimerBeat();
		DrvKey_FactoryKeyMonitor();
		DrvKey_DisplayKeyMonitor();
		RelayDrv_DelayTimeMonitor();
		if(((GStr_Flag.ucRunState1&F_RUN_L2_ALRAM)&&(!(GStr_Flag.ucRunState&F_RUN_CLOSE_L2)))
		||((GStr_Flag.ucRunState1&F_RUN_REMAIND_ZERO)&&(!(GStr_Flag.ucRunState&F_RUN_CLOSE_ZERO))))
		{
				DrvKey_DisplayKeyInit();  
				if(DISPLAY_KEY_LOW)
				{
					GStr_Counter.ucKeyRelayOn_Cnt++;
				}
				if(GStr_Counter.ucKeyRelayOn_Cnt>=1000)
				{
						if(GStr_Flag.ucRunState1&F_RUN_L2_ALRAM)
						{
								GStr_Flag.ucRunState|=F_RUN_CLOSE_L2;
						}
						if(GStr_Flag.ucRunState1&F_RUN_REMAIND_ZERO)
						{
								GStr_Flag.ucRunState|=F_RUN_CLOSE_ZERO;
						}
						LibPub_MemSetBytes(GA_ucRelayOperCode,0xFF,4);///按键拉闸的操作者代码为FFFFFFFF
						ApiRelay_ControlProcess();
						LibPub_WriteDataToE2prom(LIB_E2P_RUN_STATE,0,&GStr_Flag.ucRunState);	
				}
		}
		else
		{
				GStr_Counter.ucKeyRelayOn_Cnt=0;
		}

	}
}

