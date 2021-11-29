
///*****************************************************************************************///
///*Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     Timer.c
///*Version:       V1
///*Date:          2014-3-12
///*Description:   定时器处理文件
///*Function List: 
///*****************************************************************************************///
///*History1:      第1次修改
///*内容1. Date:
///*   	   Author:
///*       Modification:
		///***********************************************///
///*内容2. Date:
///*   	   Author:
///*       Modification:
		///*********************************************************************************///
///*History2:      第2次修改
///*内容1. Date:
///*   	   Author:
///*       Modification:
		///***********************************************///
///*内容2. Date:
///*   	   Author:
///*       Modification:
///*****************************************************************************************///

#include "Public.h"
#include "Timer.h"
#include "IO.h"
#include "Dispatch.h"
#include "MCUConfig.h"
#include "uart.h"



void InF_DealWith5ms(void);
void InF_Delay_us(ulong32 Delay_Num);
//uchar8 InF_SwithMultiFunction(uchar8 Peripherals);
///***********************************************************************************///
///*Function：基本节拍中断*///
///*Description：5ms中断一次,直接操作全局变量进行++*///
///*Input：*///
///*Output：*///
///*Calls：*///
///*Called By：*///
///*Influence：*///
///*Tips：*///
///*Others：*///
///*Author:zhiyong.gu*///
///***********************************************************************************///
extern uchar8 GV_ucEvenHarmonicDelayTimer;
void TickTimer_IRQHandler(void)
{
	uchar8 V_ExternalRelayStatus = 0;

	TickTimer->ETxIF |= C_TimerStatus_RESET;		///*将中断标志清零*///
	///*****************************************///
	///*50ms计数器*///
	if( GV_ucEvenHarmonicDelayTimer != 0 )
	{
		GV_ucEvenHarmonicDelayTimer--;
	}
	if( SV_PowerDownReportTime <= ( C_Interval_1000ms * 3 ) )
	{
		SV_PowerDownReportTime++;
	}
	
	///*****************************************///
	///*100ms计数器*///
	if( SV_TimerBasedTickTimer_100ms <= C_Interval_100ms )
	{
		SV_TimerBasedTickTimer_100ms++;
	}
	///*****************************************///
	///*500ms计数器*///
	if( SV_TimerBasedTickTimer_500ms <= C_Interval_500ms )
	{
		SV_TimerBasedTickTimer_500ms++;
//		if(SV_TimerBasedTickTimer_500ms%2)
//		{ 
//			SwitchOn_BackLight();///test niu,5ms
//		}
//		else
//		{
//			SwitchOff_BackLight();///test niu
//		}		
	}

	///*****************************************///
	///*1000ms计数器*///
	if( SV_TimerBasedTickTimer_1000ms <= C_Interval_1000ms )
	{
		SV_TimerBasedTickTimer_1000ms++;
	}
	///*****************************************///
	///*巡航计数器*///
	if( SV_TimerCruise <= C_Interval_5000ms )
	{
		SV_TimerCruise++;
	}
	///*分钟计数器*///
	if( SV_TimerCheckMcu < C_Interval_1min )
	{
		SV_TimerCheckMcu++;
	}
	///**************************************///
	///*上电后闭锁读取外部检测口线功能100ms*///
	if( SV_TimerShut100ms != 0 )
	{
		SV_TimerShut100ms--;
	}
	///*上电后闭锁3s:上电后电压等实时量未刷新,为避免对负荷记录/事件记录/电压合格率等的影响,这些功能需要闭锁3s*///
	if( SV_TimerShutRealTimeData != 0 )
	{
		SV_TimerShutRealTimeData--;
	}
	///**************************************///
	///*喂狗定时器*///
//	SV_TimerFeedWatchdog++;
	if( SV_TimerFeedWatchdog <= C_WatchDog_Feed )
	{
		SV_TimerFeedWatchdog++;
		FeedWatchDog();
	}
	///**************************************///
	if( SV_Timer_Delay >= (C_TimerSwitch_16+C_Interval_5ms) )
	{
		SV_Timer_Delay -= C_Interval_5ms;
	}
	else
	{
		SV_Timer_Delay = 0;
	}
	///**************************************///
	///*需量周期脉冲、时段投切脉冲的处理*///
	if(  SV_Timer_MultiFunction > C_TimerSwitch_8 )
	{
		SV_Timer_MultiFunction--;
		if( SV_Timer_MultiFunction == C_TimerSwitch_8 )
		{
			///*关闭多功能输出口线*///
			DF_MultiFunction_Close();
			SV_Timer_MultiFunction = C_Interval_0ms;
		}
		else
		{
			SV_Timer_MultiFunction |= C_TimerSwitch_8;
		}
	}
	///**************************************///
	///*继电器控制信号处理：包括内置/外置继电器*///
	if( SV_InternalRelayActTime > C_TimerSwitch_16 )		///*内置负荷开关动作时间*///
	{
		SV_InternalRelayActTime--;
		if( SV_InternalRelayActTime == C_TimerSwitch_16 )
		{
			DF_InternalRelayHold();
			SV_InternalRelayActTime = C_Interval_0ms;
		}
	}
	
	if( SV_ExternalRelayActTime > C_TimerSwitch_16 )
	{
		SV_ExternalRelayActTime--;
		if( SV_ExternalRelayActTime == C_TimerSwitch_16 )
		{
			SwitchOn_ExternalRelay();						///*外置开关信号为脉冲式，脉冲发出后继电器实际处于通*///
			SV_ExternalRelayActTime = C_Interval_0ms;
		}
	}
	///**************************************///
	///*载波模块、GPRS模块、微功率模块的复位处理*///
	if( SV_Timer_ModuleReset > C_TimerSwitch_8 )
	{
		SV_Timer_ModuleReset--;
		if( SV_Timer_ModuleReset == C_TimerSwitch_8 )
		{
			DF_SwitchOn_ModuleEn();
			SV_Timer_ModuleReset = C_Interval_0ms;
		}
	}
	///**************************************///
	///*处理蜂鸣器*///
	if( SV_BeeperAct == C_AlwaysDisplay )
	{
		if( SV_BeeperTime == 0xffff )
		{
			//SV_BeeperCycle = 0;
		}
		else if( SV_BeeperTime >= C_Interval_5ms )
		{
			SV_BeeperTime -= C_Interval_5ms;
			//SV_BeeperCycle = 0;
		}
		else
		{
			SV_BeeperTime = 0;
			SV_BeeperAct = C_NotDisplay;
			//SV_BeeperCycle = 0;
			DF_SwitchOff_Beeper();
		}
	}
	else if( SV_BeeperAct == C_TwinkleDisplay )
	{
		if( SV_BeeperTime >= C_Interval_5ms )
		{
			SV_BeeperTime -= C_Interval_5ms;
			if( SV_BeeperCycle == 0 )			///*闪烁时间为0,就认为一直响,直到总时间为0*///
			{
				;
			}
			else
			{
				if( SV_BeeperReverseTime >= C_Interval_5ms )
				{
					SV_BeeperReverseTime -= C_Interval_5ms;
				}
				else
				{
					SV_BeeperReverseTime = (SV_BeeperCycle/2 + SV_BeeperCycle%2);
					DF_ReversePhase_Beeper();
				}
			}
		}
		else
		{
			SV_BeeperTime = 0;
			SV_BeeperAct = C_NotDisplay;
			//SV_BeeperCycle = 0;
			DF_SwitchOff_Beeper();
		}
	}
	else
	{
		SV_BeeperAct = C_NotDisplay;
		SV_BeeperTime = 0;
		SV_BeeperCycle = 0;
		//DF_SwitchOff_Beeper();
	}
	///**************************************///
	///**************************************///
	///*查询上翻按键*///
	if( Str_KeyUp.Timer <= C_Interval_50ms )
	{
		Str_KeyUp.Timer++;
		if( DF_GetIOStatus(C_KeyUp) == Str_KeyUp.HStatus )	///*当前状态与历史状态相同*///
		{
			Str_KeyUp.Timer = 0;
		}
	}
	if( Str_KeyUpPermit.Timer <= C_Interval_3000ms )
	{
		Str_KeyUpPermit.Timer++;
		if( DF_GetIOStatus(C_KeyUp) == Str_KeyUpPermit.HStatus )	///*当前状态与历史状态相同*///
		{
			Str_KeyUpPermit.Timer = 0;
		}
	}
	///**************************************///
	///*查询下翻按键*///
	if( Str_KeyDown.Timer <= C_Interval_50ms )
	{
		Str_KeyDown.Timer++;
		if( DF_GetIOStatus(C_KeyDown) == Str_KeyDown.HStatus )	///*当前状态与历史状态相同*///
		{
			Str_KeyDown.Timer = 0;
		}
	}
	if( Str_KeyDownPermit.Timer <= C_Interval_3000ms )
	{
		Str_KeyDownPermit.Timer++;
		if( DF_GetIOStatus(C_KeyDown) == Str_KeyDownPermit.HStatus )	///*当前状态与历史状态相同*///
		{
			Str_KeyDownPermit.Timer = 0;
		}
	}
	///**************************************///
	///*查询编程按键*///
//	if( Str_KeyPrg.Timer <= C_Interval_50ms )
//	{
//		Str_KeyPrg.Timer++;
//		if( DF_GetIOStatus(C_KeyPrg) == Str_KeyPrg.HStatus )	///*当前状态与历史状态相同*///
//		{
//			Str_KeyPrg.Timer = 0;
//		}
//	}
	///**************************************///
	///*查询开表盖按键*///
	if( Str_KeyOpenCover.Timer <= C_Interval_50ms )
	{
		Str_KeyOpenCover.Timer++;
	}
	if( DF_GetIOStatus(C_KeyOpenCover) == Str_KeyOpenCover.HStatus )	///*当前状态与历史状态相同*///
	{
		Str_KeyOpenCover.Timer = 0;
	}
	///**************************************///
	///*查询端尾盖按键*///
	if( Str_KeyOpenTerminal.Timer <= C_Interval_50ms )
	{
		Str_KeyOpenTerminal.Timer++;
	}
	if( DF_GetIOStatus(C_KeyOpenTerminal) == Str_KeyOpenTerminal.HStatus )	///*当前状态与历史状态相同*///
	{
		Str_KeyOpenTerminal.Timer = 0;
	}
	///**************************************///
	///*查询磁场检测口线*///
	if( Str_Magnetic.Timer <= C_Interval_50ms )
	{
		Str_Magnetic.Timer++;
	}
	if( DF_GetIOStatus(C_Magnetic) == Str_Magnetic.HStatus )	///*当前状态与历史状态相同*///
	{
		Str_Magnetic.Timer = 0;
	}
	///**************************************///
	///*辅助电源检测口线*///
	if( Str_CheckAuPower.Timer <= C_Interval_50ms )
	{
		Str_CheckAuPower.Timer++;
	}
	if( DF_GetIOStatus(C_CheckAuPower) == Str_CheckAuPower.HStatus )	///*当前状态与历史状态相同*///
	{
		Str_CheckAuPower.Timer = 0;
	}
	///**************************************///
	///*计量芯片IRQ中断检测口线*///
//	if( Str_MeterICIRQ.Timer <= C_Interval_50ms )
//	{
//		Str_MeterICIRQ.Timer++;
//	}
//	if( DF_GetIOStatus(C_MeterICIRQ) == Str_MeterICIRQ.HStatus )	///*当前状态与历史状态相同*///
//	{
//		Str_MeterICIRQ.Timer = 0;
//	}
	///**************************************///
	///*继电器状态检测口线*///
	if( Str_RelayStatus.Timer <= C_Interval_50ms )
	{
		Str_RelayStatus.Timer++;
	}
	if( DF_GetIOStatus(C_RelayStatus) == Str_RelayStatus.HStatus )	///*当前状态与历史状态相同*///
	{
		Str_RelayStatus.Timer = 0;
	}
	/**************************************/
	/*外置继电器状态检测口线*/	
	V_ExternalRelayStatus = DF_GetIOStatus(C_ExternalRelayStatus);
	if( Str_ExternalRelayStatus.Timer < C_ExRelayInvaildNum )
	{
		if(V_ExternalRelayStatus == C_Invalid)				/*如果有低电平，就进行次数累加*/
		{
			Str_ExternalRelayStatus.Timer++;
		}
	}
	///**************************************///
	///*模块发送状态指示检测口线*///
	if( Str_ModuleStatus.Timer <= C_Interval_50ms )
	{
		Str_ModuleStatus.Timer++;
	}
	if( DF_GetIOStatus(C_ModuleStatus) == Str_ModuleStatus.HStatus )	///*当前状态与历史状态相同*///
	{
		Str_ModuleStatus.Timer = 0;
	}
	///*****************************************///
	///*插卡状态检测*///
	if(Str_CardStatus.Timer <= C_Interval_50ms)
	{
		Str_CardStatus.Timer++;
	}
	if( DF_GetIOStatus(C_CardStatus) == Str_CardStatus.HStatus )	///*当前状态与历史状态相同*///
	{
		Str_CardStatus.Timer = 0;
	}
	///*****************************************///
}

///***********************************************************************************///
///*Function：基本节拍定时器开始*///
///*Description：上电初始化时调用、唤醒后调用*///
///*Input：*///
///*Output：*///
///*Calls：*///
///*Called By：*///
///*Influence：*///
///*Tips：*///
///*Others：*///
///*Author:zhiyong.gu*///
///***********************************************************************************///
void InF_TickTimerStart(void)
{
	TickTimerClock_EN;						///*系统时钟提供给定时器：无分频=系统时钟*///
	TickTimer->ETxCR = C_TIM_CR1_CLEAR;				///*控制寄存器清零*///
	
	TickTimer->ETxINSEL = 0;				///*输入信号选择控制，APBCLK*///
	TickTimer->ETxPESCALE1 = 0x00000001;			///*预分频寄存器，2分频*///  
	TickTimer->ETxPESCALE2 = 0;			///*预分频寄存器，不分频*///  
	TickTimer->ETxIE &= C_TIM_UIE_DIS;	///*中断禁止*///          
	TickTimer->ETxIF |= C_TimerStatus_RESET;	///*清中断标志*///  
	TickTimer->ETxIVR = C_TickTimerCounter;
	
	TickTimer->ETxCR |= C_CardBaudRateTimerETxCR;		///*控制寄存器配置：PWM禁止、定时模式*///
	///*******************************************************///
	TickTimer->ETxCR |= C_TIM_CR1_CEN;	///*正式启动定时器开始计数*///
	TickTimer->ETxIE |= C_TIM_UIE_EN;		///*使能中断*///
	///*******************************************************///
	NVIC_EnableIRQ(TickTimer_Interrupt);	///*基本节拍中断使能*///	
}

///***********************************************************************************///
///*Function：基本节拍定时器停止*///
///*Description：进入低功耗时调用、从唤醒状态进入低功耗调用*///
///*Input：*///
///*Output：*///
///*Calls：*///
///*Called By：*///
///*Influence：停止计数器、系统时钟的供给、禁止中断，从而节省功耗*///
///*Tips：*///
///*Others：*///
///*Author:zhiyong.gu*///
///***********************************************************************************///
void InF_TickTimerStop(void)
{
	TickTimer->ETxCR &= (~C_TIM_CR1_CEN);			///*停止计数*///
	TickTimer->ETxIF |= C_TimerStatus_RESET;	///*清中断标志*///
	TickTimerClock_DIS;												///*系统时钟停止提供给定时器*///
	NVIC_DisableIRQ(TickTimer_Interrupt);			///*基本节拍中断禁止*///
}

///**************************************************************************************///
///*Function:蜂鸣器输出*///
///*Description:蜂鸣器长响、关闭、发出周期性蜂鸣音*///
///*Input: BeeperOutType:C_AlwaysDisplay: 长响
///*					 C_NotDisplay:    关闭
///*					 C_TwinkleDisplay:发出周期性蜂鸣音*///
///*       BeeperOutTime:动作总时间(以ms为单位,hex形式,ffff为常开或常闭,0为不动作)
///*					 不是5的整数倍时,去掉余数.小于5时不动作
///*					 BeeperOutType=C_TwinkleDisplay,本函数执行后,总是以关闭结束
///*					 BeeperOutType=C_AlwaysDisplay,响BeeperOutTime时间后关闭,BeeperOutCycle无效
///*					 BeeperOutType=C_NotDisplay,直接关闭,BeeperOutTime与BeeperOutCycle都无效
///*	   BeeperOutCycle:开关1个周期的时间(以ms为单位, hex格式)
///*					  BeeperOutType为C_AlwaysDisplay或C_NotDisplay时无效
///*					  如果BeeperOutCycle=1000而BeeperOutTime<500,则响BeeperOutTime时间后关闭;以此类推
///*Output:置相应的定时器并操作蜂鸣器*///
///*Return:无
///*Tips:本函数基于5ms的基本节拍,因此总时间与动作时间可能相差最多5ms
///*	 调用本函数后蜂鸣器立即动作,与时间相关的在5ms基本节拍里处理
///*     如果在蜂鸣器动作期间本函数又被调用,则按照最新调用的参数重新开始对蜂鸣器动作*///
///**************************************************************************************///
void InF_BeeperOut(uchar8 BeeperOutType,ushort16 BeeperOutTime,ushort16 BeeperOutCycle)
{
	switch(BeeperOutType)
	{
		case C_NotDisplay:				///*关闭蜂鸣器,不管其他入口参数*///
		{
			SV_BeeperAct = C_NotDisplay;
			SV_BeeperTime = 0;
			SV_BeeperCycle = 0;
			DF_SwitchOff_Beeper();
			break;
		}
		case C_AlwaysDisplay:			///*开蜂鸣器*///
		{
			if(BeeperOutTime != 0)
			{
				SV_BeeperAct = C_AlwaysDisplay;
				SV_BeeperTime = BeeperOutTime;
				SV_BeeperCycle = 0;
				DF_SwitchOn_Beeper();
			}
			else						///*动作总时间为0直接关闭蜂鸣器*///
			{
				SV_BeeperAct = C_NotDisplay;
				SV_BeeperTime = 0;
				SV_BeeperCycle = 0;
				DF_SwitchOff_Beeper();
			}
			break;
		}
		case C_TwinkleDisplay:			///*发出蜂鸣音*///
		{
			if(BeeperOutTime >= 2)
			{
				SV_BeeperAct = C_TwinkleDisplay;
				SV_BeeperTime = BeeperOutTime;
				SV_BeeperCycle = BeeperOutCycle;
				SV_BeeperReverseTime = (BeeperOutCycle/2);
				DF_SwitchOn_Beeper();
			}
			else
			{
				SV_BeeperAct = C_NotDisplay;
				SV_BeeperTime = 0;
				SV_BeeperCycle = 0;
				DF_SwitchOff_Beeper();
			}
			break;
		}
		default:
			break;
	}
}

/**********************************************************************************************************
函数原型: uchar8 InF_GetPeripheralStatus(uchar8 Peripheral)		
功能描述: 所有用到的口线状态都读取并返回												           
输入参数: 	    	
输出参数:   						       					
返回参数:
											C_Valid			C_Invalid		C_Error	
C_KeyUp   			上翻键                  按下            松开                  	
C_KeyDown   		下翻键                  按下            松开                  	
C_KeyPrg   			编程键                  按下            松开                  	
C_KeyOpenCover   	开表盖                  合盖            开盖                  	
C_KeyOpenTerminal	开端尾盖                合盖            开盖                  	
C_CheckAuPower   	辅助电源检测            掉电            未掉电                 	
C_Magnetic       	磁场检测                有磁场          无磁场                 	
C_MeterICIRQ     	计量芯片IRQ中断         有中断          无中断                	
C_RelayStatus    	继电器状态检测          继电器通        断开                   	
C_ModuleStatus   	模块发送状态指示        模块发送        未发送                 	
C_CardStatus		插卡状态检测			有插卡			无插卡 
C_ExternalRelayStatus 外置继电器检测        通              断
调用位置: 																		
备    注:	
        1.对于上翻键/下翻键/编程键/插卡,在判断到状态由无效C_Invalid翻转为有效C_Valid时,
            同时将消息发给相应的模块,并对去抖定时器清零
            该函数做这样的修改,是20141028有时候连续按键2次才有效,对程序进行调整,假如去抖时间到,
            但主流程没有执行按键消息处理,但某个功能模块调用了本函数,主流程就有可能丢消息,所以进行了本次调整
        2.在上电后闭锁读取口线状态的功能100ms，100ms内读取口线状态，
            则延时满100ms后再给调用函数一个正确的口线状态
        3.C_ExternalRelayStatus外置继电器状态，禁止SF_GetRelay0nOffStatus以外的函数调用
*********************************************************************************************************/
uchar8 InF_GetPeripheralStatus(uchar8 Peripheral)
{
	uchar8	V_ucReturn = C_Error;						/*返回值初始为“错误”*/
	ulong32	i;
	uchar8 V_ucBuffer[2];
	/*******************************************************/
	/*判断100ms的上电闭锁时间是否到*/
	for(i = 0; i < 100; i++)									/*最多延时100ms*/
	{
		if( SV_TimerShut100ms == 0 )
		{
			break;
		}
		InF_Delay_us(1000);
	}
	/*******************************************************/
	switch( Peripheral )
	{
		/*******************************************************/
		case C_KeyUp:									/*上翻键状态*/
		{
			if( Str_KeyUp.Timer >= C_Interval_50ms )
			{
				if(Str_KeyUp.HStatus == C_Valid )
				{
					Str_KeyUp.HStatus = C_Invalid;
				}
				else
				{
					Str_KeyUp.HStatus = C_Valid;
					/*由无效变为有效,发消息给显示模块*/
					V_ucBuffer[0] = Pt_Dispatch_Key;
					V_ucBuffer[1] = C_KeyUp;
					Dispatch_SendMessage(C_Msg_Display, V_ucBuffer, Pt_Dispatch_Key_Len + 1);
				}
				Str_KeyUp.Timer = 0;
			}
			V_ucReturn = Str_KeyUp.HStatus;
			break;
		}
		/*******************************************************/
		case C_KeyUpForRelay:									/*上翻键状态*/
		{
			if( Str_KeyUpPermit.Timer >= C_Interval_3000ms )
			{
				if(Str_KeyUpPermit.HStatus == C_Valid )
				{
					Str_KeyUpPermit.HStatus = C_Invalid;
				}
				else
				{
					Str_KeyUpPermit.HStatus = C_Valid;
					/*由无效变为有效,发消息给继电器模块*/
					V_ucBuffer[0] = Pt_Dispatch_Key;
					V_ucBuffer[1] = C_Key3s;
					Dispatch_SendMessage(C_Msg_Deal_RelayStatus, V_ucBuffer, Pt_Dispatch_Key_Len + 1);
				}
				Str_KeyUpPermit.Timer = 0;
			}
			V_ucReturn = Str_KeyUpPermit.HStatus;
			break;
		}
		/*******************************************************/
		case C_KeyDown:									/*下翻键状态*/
		{
			if( Str_KeyDown.Timer >= C_Interval_50ms )
			{
				if(Str_KeyDown.HStatus == C_Valid )
				{
					Str_KeyDown.HStatus = C_Invalid;
				}
				else
				{
					Str_KeyDown.HStatus = C_Valid;
					/*由无效变为有效,发消息给显示模块*/
					V_ucBuffer[0] = Pt_Dispatch_Key;
					V_ucBuffer[1] = C_KeyDown;
					Dispatch_SendMessage(C_Msg_Display, V_ucBuffer, Pt_Dispatch_Key_Len + 1);
				}
				Str_KeyDown.Timer = 0;
			}
			V_ucReturn = Str_KeyDown.HStatus;
			break;
		}
		/*******************************************************/
		case C_KeyDownForRelay:									/*下翻键状态*/
		{
			if( Str_KeyDownPermit.Timer >= C_Interval_3000ms )
			{
				if(Str_KeyDownPermit.HStatus == C_Valid )
				{
					Str_KeyDownPermit.HStatus = C_Invalid;
				}
				else
				{
					Str_KeyDownPermit.HStatus = C_Valid;
					/*由无效变为有效,发消息给继电器模块*/
					V_ucBuffer[0] = Pt_Dispatch_Key;
					V_ucBuffer[1] = C_Key3s;
					Dispatch_SendMessage(C_Msg_Deal_RelayStatus, V_ucBuffer, Pt_Dispatch_Key_Len + 1);
				}
				Str_KeyDownPermit.Timer = 0;
			}
			V_ucReturn = Str_KeyDownPermit.HStatus;
			break;
		}
		/******************************************************/
		case C_KeyOpenCover:							/*开表盖状态*/
		{
			if( InF_ReadPowerState() == C_PowerOn )
			{
				if( Str_KeyOpenCover.Timer >= C_Interval_50ms )
				{
					if(Str_KeyOpenCover.HStatus == C_Valid )
					{
						Str_KeyOpenCover.HStatus = C_Invalid;
					}
					else
					{
						Str_KeyOpenCover.HStatus = C_Valid;
					}
					Str_KeyOpenCover.Timer = 0;
				}
				V_ucReturn = Str_KeyOpenCover.HStatus;
			}
			else
			{
				V_ucReturn = DF_GetIOStatus(C_KeyOpenCover);
			}
			break;
		}
		/*******************************************************/
		case C_KeyOpenTerminal:							/*开端尾盖*/
		{
			if( InF_ReadPowerState() == C_PowerOn )
			{
				if( Str_KeyOpenTerminal.Timer >= C_Interval_50ms )
				{
					if(Str_KeyOpenTerminal.HStatus == C_Valid )
					{
						Str_KeyOpenTerminal.HStatus = C_Invalid;
					}
					else
					{
						Str_KeyOpenTerminal.HStatus = C_Valid;
					}
					Str_KeyOpenTerminal.Timer = 0;
				}
				V_ucReturn = Str_KeyOpenTerminal.HStatus;
			}
			else
			{
				V_ucReturn = DF_GetIOStatus(C_KeyOpenTerminal);
			}
			break;
		}
		/*******************************************************/
		case C_CheckAuPower:							/*辅助电源掉电检测*/
		{
			if( Str_CheckAuPower.Timer >= C_Interval_50ms )
			{
				if(Str_CheckAuPower.HStatus == C_Valid )
				{
					Str_CheckAuPower.HStatus = C_Invalid;
				}
				else
				{
					Str_CheckAuPower.HStatus = C_Valid;
				}
				Str_CheckAuPower.Timer = 0;
			}
			V_ucReturn = Str_CheckAuPower.HStatus;
			break;
		}
		/*******************************************************/
		case C_Magnetic:								/*磁场检测*/
		{
			if( Str_Magnetic.Timer >= C_Interval_50ms )
			{
				if(Str_Magnetic.HStatus == C_Valid )
				{
					Str_Magnetic.HStatus = C_Invalid;
				}
				else
				{
					Str_Magnetic.HStatus = C_Valid;
				}
				Str_Magnetic.Timer = 0;
			}
			V_ucReturn = Str_Magnetic.HStatus;
			break;
		}
		/*******************************************************/
		case C_MeterICIRQ:								/*计量芯片IRQ请求*/
		{
			if( Str_MeterICIRQ.Timer >= C_Interval_50ms )
			{
				if(Str_MeterICIRQ.HStatus == C_Valid )
				{
					Str_MeterICIRQ.HStatus = C_Invalid;
				}
				else
				{
					Str_MeterICIRQ.HStatus = C_Valid;
				}
				Str_MeterICIRQ.Timer = 0;
			}
			V_ucReturn = Str_MeterICIRQ.HStatus;
			break;
		}
		/*******************************************************/
		case C_RelayStatus:								/*内置继电器状态*/
		{
			if( Str_RelayStatus.Timer >= C_Interval_50ms )
			{
				if(Str_RelayStatus.HStatus == C_Valid )
				{
					Str_RelayStatus.HStatus = C_Invalid;
				}
				else
				{
					Str_RelayStatus.HStatus = C_Valid;
				}
				Str_RelayStatus.Timer = 0;
			}
			V_ucReturn = Str_RelayStatus.HStatus;
			break;
		}
        /*******************************************************/
		case C_ExternalRelayStatus:							            /*外置继电器状态*/
		{
			if( Str_ExternalRelayStatus.Timer >= C_ExRelayInvaildNum )  /*这个外置继电器状态，除了SF_GetRelay0nOffStatus()，其他函数禁止调用*/
			{
                Str_ExternalRelayStatus.HStatus = C_Valid;              /*有低电平超过20次说明继电器通*/
			}
            else
            {
                Str_ExternalRelayStatus.HStatus = C_Invalid;            /*一直高电平说明继电器断*/
            }
            V_ucReturn = Str_ExternalRelayStatus.HStatus;
            Str_ExternalRelayStatus.Timer = 0;
			break;
		}
		/*******************************************************/
		case C_ModuleStatus:							/*模块上行通信状态*/
		{
			if( Str_ModuleStatus.Timer >= C_Interval_50ms )
			{
				if(Str_ModuleStatus.HStatus == C_Valid )
				{
					Str_ModuleStatus.HStatus = C_Invalid;
				}
				else
				{
					Str_ModuleStatus.HStatus = C_Valid;
				}
				Str_ModuleStatus.Timer = 0;
			}
			V_ucReturn = Str_ModuleStatus.HStatus;
			break;
		}
		/*******************************************************/
		case C_CardStatus:							/*有无插卡状态监测*/
		{
			if( Str_CardStatus.Timer >= C_Interval_50ms )
			{
				if(Str_CardStatus.HStatus == C_Valid )
				{
					Str_CardStatus.HStatus = C_Invalid;
				}
				else
				{
					Str_CardStatus.HStatus = C_Valid;
					/*由无效变为有效,发消息给卡处理模块*/
					V_ucBuffer[0] = Pt_CardFlag;
					V_ucBuffer[1] = C_InsertCard;
					Dispatch_SendMessage(C_Msg_Card, V_ucBuffer, Pt_Dispatch_Key_Len + 1);
				}
				Str_CardStatus.Timer = 0;
			}
			V_ucReturn = Str_CardStatus.HStatus;
			break;
		}
		default:
			;
			break;
		/*******************************************************/
	}
	return V_ucReturn;
}

///**************************************************************************************///
///*函数原型：uchar8 InF_RelayAct(uchar8 C_Act)											*///
///*功能描述：继电器动作接口函数                                                        *///
///*输入参数：C_On，表示继电器闭合；C_Off，表示继电器断开                               *///
///*输出参数：内置负荷开关:不管是闭合还是断开,ushort16 SV_InternalRelayActTime赋值      *///
///*	                   C_InternalRelayActTime=400ms后打开计时器开关                 *///
///*          外置负荷开关:断开动作：读取数据层的电表运行特征字1的外置开关控制方式确定  *///
///*                       是脉冲式还电平式。脉冲式断开动作的有效时间通过读取数据层的   *///
///*                       脉宽时间赋值，该定时器带开关；电平式断开/闭合都直接操作口线，*///
///*                       不启用定时器。                                               *///
///*          闭合动作：直接释放口线。                                                  *///
///*          外置开关定时器ushort16 SV_ExternalRelayTimer带开关。                      *///
///*返回参数：C_Ok，正确执行；C_Error，入口错误                                         *///
///*调用位置：该函数由费控模块调用                                                      *///
///*功能说明：1）调用该驱动函数时，只需要明确是继电器闭合还是断开                       *///
///**************************************************************************************///
uchar8 InF_RelayAct(uchar8 C_Act)
{
	uchar8 V_ucTemp = C_Error;	///*返回值置为错误：入口参数错误时才返回错误，只要入口参数正确就返回正确*///
	uchar8 V_DataBuff[4];
	ushort16 V_usLen, V_usDataEncode;
	
	switch( C_Act )
	{
 		///***********************************************************///
		case C_On:
		{
			DF_RelayControl(C_On);
			//SV_InternalRelayActTime = (C_TimerSwitch_16|C_Interval_400ms);	///*内置负荷开关动作时间*///
            SV_InternalRelayActTime = (C_TimerSwitch_16|C_Interval_150ms);	///*内置负荷开关动作时间,同步蒙东改为150ms*///
			SV_ExternalRelayActTime = C_Interval_0ms;						///*外置负荷开关：闭合时不需要延时*///
			V_ucTemp = C_OK;
			break;
		}
 		///***********************************************************///
		case C_Off:
		{
			V_ucTemp = C_OK;
			DF_RelayControl(C_Off);
			//SV_InternalRelayActTime = (C_TimerSwitch_16|C_Interval_400ms);			///*内置负荷开关动作时间*///
            SV_InternalRelayActTime = (C_TimerSwitch_16|C_Interval_150ms);			///*内置负荷开关动作时间,同步蒙东改为150ms*///
			///*从数据层读取外跳方式*///
			V_usLen = CLMeter_Work_Char1;
			if( InF_Read_Data(CMeter_Work_Char1,&V_DataBuff[0],&V_usLen, &V_usDataEncode) == C_OK )
			{
				if( (V_DataBuff[0] & C_PulseMode) == 0 )					///*脉冲式*///
				{
					///*读取脉冲宽度*///
					V_usLen = CLExtern_Relay_PulW;
					if( InF_Read_Data(CExtern_Relay_PulW,&V_DataBuff[0],&V_usLen, &V_usDataEncode) == C_OK )
					{
						SV_ExternalRelayActTime = V_DataBuff[1];
						SV_ExternalRelayActTime <<=8;
						SV_ExternalRelayActTime += V_DataBuff[0];
						SV_ExternalRelayActTime |= C_TimerSwitch_16;
					}
					else			///*默认为400ms*///
					{
						SV_ExternalRelayActTime = C_Interval_400ms;
						SV_ExternalRelayActTime |= C_TimerSwitch_16;
					}
				}
				else				///*电平式*///
				{
					SV_ExternalRelayActTime = C_Interval_0ms;
				}
			}
			break;
		}
 		///***********************************************************///
		default:
			;
		break;
	}
	
	return V_ucTemp;
}

///**********************************************************************************///
///*Function：多功能端子输出定时器赋值*///
///**********************************************************************************///
void SF_Set_MultiFunctionTimer(uchar8 Timer)
{
	SV_Timer_MultiFunction = Timer;
}

///***********************************************************************************///
///*Function：外部器件/设备的控制
///*Description：
///*Input：
///*												C_On			C_Off			*///
///*C_BackLight				背光            		开背光			关背光			*///
///*C_TripLed               拉闸指示灯              指示灯亮		指示灯灭        *///
///*C_Beep                  蜂鸣器                  蜂鸣器响		蜂鸣器关        *///
///*C_WarnOut               报警继电器              有报警输出		无报警输出      *///
///*C_FlashPower            Flash电源控制           打开电源		关闭电源        *///
///*C_CapCharge             超级电容充电控制        允许充电		关闭充电        *///
///*C_CapDischarge          超级电容放电控制        允许放电		禁止放电        *///
///*C_WakeUpPower           6V电池电源控制          打开电源		关闭电源        *///
///*C_BattDischarge         6V电池防钝化控制        打开			关闭            *///
///*C_EventOut              主动上报                允许上报		关闭上报        *///
///*C_ModuleReset           模块复位                模块复位		模块使能        *///
///*C_ModuleSet             模块设置                模块设置		设置释放        *///
///*C_InfraPower			红外接收电源			打开电源		关闭电源		*///
///*C_EsamPower             ESAM电源                打开电源		关闭电源        *///
///*C_CardPower             CARD电源                打开电源		关闭电源        *///
///*C_EsamReset				ESAM复位  				ESAM复位		ESAM使能  		*///
///*C_CardSck               卡时钟使能              卡时钟使能		卡时钟禁止      *///
///*C_CardReset             卡复位                  卡复位			卡使能          *///
///*Output：
///*Return：C_Error:入口参数错误，C_OK:正确执行
///*Calls：
///*Called By：
///*Influence：该函数不能在中断里调用
///*Tips：
///*Others：
///***********************************************************************************///
uchar8 InF_SwithPeripherals(uchar8 Peripherals,uchar8 Act)
{
	uchar8 V_ucTemp = C_Error;	///*返回值置为错误：入口参数错误时才返回错误，只要入口参数正确就返回正确*///
		
	switch(Peripherals)			///*控制哪个器件或设备*///
	{
 		case C_BackLight:		///*操作背光口线:不需要定时器*///
		{
 			switch(Act)
 			{
 				case C_On:		///*背光点亮*///
 				{
 					SwitchOn_BackLight();
 					V_ucTemp = C_OK;
 					break;
 				}
 				case C_Off:		///*背光熄灭*///
 				{
 					SwitchOff_BackLight();
 					V_ucTemp = C_OK;
 					break;
 				}
 				default:
 					;
 				break;
 			}
 			break;
		}
 		///***********************************************************///
 		case C_TripLed:			///*拉闸指示灯*///
		{
 			switch(Act)
 			{
 				case C_On:		///*拉闸灯点亮*///
 				{
 					SwitchOn_TripLed();
 					V_ucTemp = C_OK;
 					break;
 				}
 				case C_Off:		///*拉闸灯熄灭*///
 				{
 					SwitchOff_TripLed();
 					V_ucTemp = C_OK;
 					break;
 				}
 				default:
 					;
 				break;
 			}
 			break;
		}
 		///***********************************************************///
 		///***********************************************************///
 		case C_Beep:			///*蜂鸣器*///
		{
 			switch(Act)
 			{
 				case C_On:		///*蜂鸣器打开*///
 				{
 					DF_SwitchOn_Beeper();
 					V_ucTemp = C_OK;
 					break;
 				}
 				case C_Off:		///*蜂鸣器关闭*///
 				{
 					DF_SwitchOff_Beeper();
 					V_ucTemp = C_OK;
 					break;
 				}
 				default:
 					;
 				break;
 			}
 			break;
		}
 		///***********************************************************///
 		case C_WarnOut:			///*报警输出*///
		{
 			switch(Act)
 			{
 				case C_On:		///*报警继电器闭合*///
 				{
 					SwitchOn_WarnOut();
 					V_ucTemp = C_OK;
 					break;
 				}
 				case C_Off:		///*报警继电器断开*///
 				{
 					SwitchOff_WarnOut();
 					V_ucTemp = C_OK;
 					break;
 				}
 				default:
 					;
 				break;
 			}
 			break;
		}
 		///***********************************************************///
 		case C_FlashPower:		///*Flash电源控制*///
		{
 			switch(Act)
 			{
 				case C_On:		///*Flash电源打开*///
 				{
 					SwitchOn_FlashPower();
 					V_ucTemp = C_OK;
 					break;
 				}
 				case C_Off:		///*Flash电源关闭*///
 				{
 					SwitchOff_FlashPower();
 					V_ucTemp = C_OK;
 					break;
 				}
 				default:
 					;
 				break;
 			}
 			break;
		}
 		///***********************************************************///
 		case C_CapCharge:		///*超级电容充电控制*///
		{
 			switch(Act)
 			{
 				case C_On:		///*超级电容充电使能*///
 				{
 					SuperCapCharge_En();
 					V_ucTemp = C_OK;
 					break;
 				}
 				case C_Off:		///*超级电容充电禁止*///
 				{
 					SuperCapCharge_Dis();
 					V_ucTemp = C_OK;
 					break;
 				}
 				default:
 					;
 				break;
 			}
 			break;
		}
 		///***********************************************************///
 		case C_CapDischarge:	///*超级电容放电控制*///
		{
 			switch(Act)
 			{
 				case C_On:		///*超级电容放电使能*///
 				{
 					SwitchOn_SuperCapPower();
 					V_ucTemp = C_OK;
 					break;
 				}
 				case C_Off:		///*超级电容放电禁止*///
 				{
 					SwitchOff_SuperCapPower();
 					V_ucTemp = C_OK;
 					break;
 				}
 				default:
 					;
 				break;
 			}
 			break;
		}
 		///***********************************************************///
 		case C_WakeUpPower:		///*6V电池电源控制*///
		{
 			switch(Act)
 			{
 				case C_On:		///*6V电池电源控制：打开*///
 				{
 					SwitchOn_WakeUpPower();
 					V_ucTemp = C_OK;
 					break;
 				}
 				case C_Off:		///*6V电池电源控制：关闭*///
 				{
 					SwitchOff_WakeUpPower();
 					V_ucTemp = C_OK;
 					break;
 				}
 				default:
 					;
 				break;
 			}
 			break;
		}
 		///***********************************************************///
 		case C_BattDischarge:	///*6V电池防钝化控制*///
		{
 			switch(Act)
 			{
 				case C_On:		///*6V电池防钝化控制：放电*///
 				{
// 					SwitchOn_PreventBlunt();
 					V_ucTemp = C_OK;
 					break;
 				}
 				case C_Off:		///*6V电池防钝化控制：关闭放电*///
 				{
// 					SwitchOff_PreventBlunt();
 					V_ucTemp = C_OK;
 					break;
 				}
 				default:
 					;
 				break;
 			}
 			break;
		}
 		///***********************************************************///
 		case C_EventOut:		///*主动上报*///
		{
 			switch(Act)
 			{
 				case C_On:		///*主动上报*///
 				{
 					EventOut_EN();
 					V_ucTemp = C_OK;
 					break;
 				}
 				case C_Off:		///*关闭主动上报*///
 				{
 					EventOut_DIS();
 					V_ucTemp = C_OK;
 					break;
 				}
 				default:
 					;
 				break;
 			}
 			break;
		}
 		///***********************************************************///
 		case C_ModuleReset:		///*模块复位*///
		{
 			switch(Act)
 			{
 				case C_On:		///*复位模块*///
 				{
 					DF_SwitchOff_ModuleEn();
 					SV_Timer_ModuleReset = (C_Interval_300ms|C_TimerSwitch_8);
 					V_ucTemp = C_OK;
 					break;
 				}
 				case C_Off:		///*使能模块*///
 				{
 					DF_SwitchOn_ModuleEn();
 					V_ucTemp = C_OK;
 					break;
 				}
 				default:
 					;
 				break;
 			}
 			break;
		}
 		///***********************************************************///
 		case C_ModuleSet:		///*模块设置*///
		{
 			switch(Act)
 			{
 				case C_On:		///*模块设置*///
 				{
 					ModuleSet_EN();
 					V_ucTemp = C_OK;
 					break;
 				}
 				case C_Off:		///*模块设置释放*///
 				{
 					ModuleSet_DIS();
 					V_ucTemp = C_OK;
 					break;
 				}
 				default:
 					;
 				break;
 			}
 			break;
		}
 		///***********************************************************///
 		case C_InfraPower:		///*红外接收电源*///
		{
 			switch(Act)
 			{
 				case C_On:		///*红外接收电源：打开*///
 				{
 					SwitchOn_InfrarxPower();
 					V_ucTemp = C_OK;
 					break;
 				}
 				case C_Off:		///*红外接收电源：关闭*///
 				{
 					SwitchOff_InfrarxPower();
 					V_ucTemp = C_OK;
 					break;
 				}
 				default:
 					;
 				break;
 			}
 			break;
		}
 		///***********************************************************///
// 		case C_EsamPower:		///*ESAM电源*///
//		{
// 			switch(Act)
// 			{
// 				case C_On:		///*ESAM电源：打开*///
// 				{
// 					SwitchOn_EsamPower();
// 					V_ucTemp = C_OK;
// 					break;
// 				}
// 				case C_Off:		///*ESAM电源：关闭*///
// 				{
// 					SwitchOff_EsamPower();
// 					V_ucTemp = C_OK;
// 					break;
// 				}
// 				default:
// 					;
// 				break;
// 			}
// 			break;
//		}
// 		///***********************************************************///
// 		case C_CardPower:		///*CARD电源*///
//		{
// 			switch(Act)
// 			{
// 				case C_On:		///*CARD电源：打开*///
// 				{
// 					SwitchOn_CardPower();
// 					V_ucTemp = C_OK;
// 					break;
// 				}
// 				case C_Off:		///*CARD电源：关闭*///
// 				{
// 					SwitchOff_CardPower();
// 					V_ucTemp = C_OK;
// 					break;
// 				}
// 				default:
// 					;
// 				break;
// 			}
// 			break;
//		}
// 		///***********************************************************///
// 		case C_EsamReset:		///*ESAM复位*///
//		{
// 			switch(Act)
// 			{
// 				case C_On:		///*ESAM复位*///
// 				{
// 					Esam_Reset();
// 					V_ucTemp = C_OK;
// 					break;
// 				}
// 				case C_Off:		///*ESAM使能*///
// 				{
// 					Esam_EN();
// 					V_ucTemp = C_OK;
// 					break;
// 				}
// 				default:
// 					;
// 				break;
// 			}
// 			break;
//		}
// 		///***********************************************************///
// 		case C_CardSck:			///*卡时钟使能*///
//		{
// 			switch(Act)
// 			{
// 				case C_On:		///*卡时钟使能*///
// 				{
// 					CardSck_EN();
// 					V_ucTemp = C_OK;
// 					break;
// 				}
// 				case C_Off:		///*卡时钟禁止*///
// 				{
// 					CardSck_DIS();
// 					V_ucTemp = C_OK;
// 					break;
// 				}
// 				default:
// 					;
// 				break;
// 			}
// 			break;
//		}
// 		///***********************************************************///
// 		case C_CardReset:		///*卡复位*///
//		{
// 			switch(Act)
// 			{
// 				case C_On:		///*卡复位*///
// 				{
// 					Card_Reset();
// 					V_ucTemp = C_OK;
// 					break;
// 				}
// 				case C_Off:		///*卡使能*///
// 				{
// 					Card_EN();
// 					V_ucTemp = C_OK;
// 					break;
// 				}
// 				default:
// 					;
// 				break;
// 			}
// 			break;
//		}
 		///***********************************************************///
 		///***********************************************************///
 		case C_MeterICPower:		///*计量芯片电源*///
		{
 			switch(Act)
 			{
 				case C_On:		///*卡复位*///
 				{
 					DF_SwitchOn_EMeterIcPower();
 					V_ucTemp = C_OK;
 					break;
 				}
 				case C_Off:		///*卡使能*///
 				{
 					DF_SwitchOff_EMeterIcPower();
 					V_ucTemp = C_OK;
 					break;
 				}
 				default:
 					;
 				break;
 			}
 			break;
		}
 		///***********************************************************///
 		
 		
 		
 		
 		default:
 			;
 			break;
	}
	return V_ucTemp;
}
/*******************************************************************************
函数原型： ulong32 Inf_PowerDownTime(void)
功能描述：掉电低功耗发生主动上报用的定时器
输入参数：
输出参数：
返回参数： 定时器的值
调用位置： 
备    注： 
*******************************************************************************/
ulong32 Inf_PowerDownTime(void)
{
    return SV_PowerDownReportTime;
}
/*******************************************************************************
函数原型： void Inf_ClearPowerDownTime(void)
功能描述：掉电低功耗发生主动上报用的定时器清零
输入参数：
输出参数：
返回参数： 
调用位置： 
备    注： 
*******************************************************************************/
void Inf_ClearPowerDownTime(void)
{
    SV_PowerDownReportTime = 0;
}
/*******************************************************************************
函数原型： ulong32 Inf_Get_PowerOffShutAcReportTime(void)
功能描述：上电满1小时标志
输入参数：
输出参数：
返回参数： 定时器的值
调用位置： 
备    注： 
*******************************************************************************/
ulong32 Inf_Get_PowerOffShutAcReportTime(void)
{
    return SV_PowerOffShutAcReportTime;
}
/*******************************************************************************
函数原型： uchar8 Inf_SatisfyPowerOnTime(void)
功能描述：掉电满1小时返回OK，不足返回错误；
输入参数：
输出参数：
返回参数： OK:满一小时，C_Error：不满一小时
调用位置： 
备    注： 
*******************************************************************************/
uchar8 Inf_SatisfyPowerOnTime(void)
{
    uchar8  V_Return = C_Error;
    
    if(SV_PowerOffShutAcReportTime >= C_Interval_1hour)
    {
        V_Return = C_OK;
    }
    return V_Return;
}
/*******************************************************************************
函数原型： void Inf_Clear_PowerOffShutAcReportTime(void)
功能描述：上电满1小时定时器清零
输入参数：
输出参数：
返回参数： 
调用位置： 
备    注： 
*******************************************************************************/
void Inf_Clear_PowerOffShutAcReportTime(void)
{
    SV_PowerOffShutAcReportTime = 0;
}
///***********************************************************************************///
///*Function：*///
///*Description：上电初始化时调用,用于初始化各个定时器*///
///*Input：*///
///*Output：*///
///*Calls：*///
///*Called By：*///
///*Influence：*///
///*Tips：*///
///*Others：*///
///*Author:zhiyong.gu*///
///***********************************************************************************///
void InF_InitTimer(void)
{
	SV_TimerBasedTickTimer_1000ms = 0;			///*基于基本节拍定时器的1s定时器*///
	SV_TimerBasedTickTimer_500ms = 0;			///*基于基本节拍定时器的500ms定时器*///
	SV_TimerBasedTickTimer_100ms = 0;			///*基于基本节拍定时器的100ms定时器*///
	SV_TimerShut100ms = C_Interval_100ms;		///*闭锁100ms定时器*///
	SV_TimerShutRealTimeData = C_ShutRealTimeData;	///*闭锁2s定时器*///
	
	SV_TimerFeedWatchdog = 0;					///*看门狗定时器清零*///
	
	Str_KeyUp.Timer = 0;						///*上翻键*///
	Str_KeyDown.Timer = 0;						///*下翻键*///
	Str_KeyPrg.Timer = 0;						///*编程键*///
	Str_KeyOpenCover.Timer = 0;					///*开表盖*///
	Str_KeyOpenTerminal.Timer = 0;				///*开端尾盖*///
	SV_PowerDownReportTime = 0x00;				///*低功耗下上报时间清零*///
	Str_CheckAuPower.Timer = 0;					///*辅助电源掉电检测*///
	Str_Magnetic.Timer = 0;						///*磁场检测*///
	Str_MeterICIRQ.Timer = 0;					///*计量芯片IRQ请求*///
	Str_RelayStatus.Timer = 0;					///*继电器状态*///
	Str_ExternalRelayStatus.Timer = 0;			///*外置继电器状态*///
	Str_ModuleStatus.Timer = 0;					///*模块上行通信状态*///
	Str_CardStatus.Timer = 0;					///*插卡状态*///
	Str_KeyUpPermit.Timer = 0;					///*上翻键合闸允许：3s*///
	Str_KeyDownPermit.Timer = 0;				///*下翻键合闸允许：3s*///
	
	Str_KeyUp.HStatus = C_Valid;				///*上翻键*///
	Str_KeyDown.HStatus = C_Valid;				///*下翻键*///
	Str_KeyPrg.HStatus = C_Invalid;				///*编程键*///
	Str_KeyOpenCover.HStatus = C_Invalid;		///*开表盖*///
	Str_KeyOpenTerminal.HStatus = C_Invalid;	///*开端尾盖*///
	Str_CheckAuPower.HStatus = C_Invalid;		///*辅助电源掉电检测*///
	Str_Magnetic.HStatus = C_Invalid;			///*磁场检测*///
	Str_MeterICIRQ.HStatus = C_Invalid;			///*计量芯片IRQ请求*///
	Str_RelayStatus.HStatus = C_Invalid;		///*继电器状态*///
	Str_ExternalRelayStatus.HStatus = C_Invalid;		///*外置继电器高低电平，默认高电平，如果20m内状态没有变化就是断开*///  
	
	Str_ModuleStatus.HStatus = C_Invalid;		///*模块上行通信状态*///
	Str_CardStatus.HStatus = C_Invalid;			///*插卡状态*///
	Str_KeyUpPermit.HStatus = C_Invalid;		///*上翻键合闸允许：3s*///
	Str_KeyDownPermit.HStatus = C_Invalid;		///*下翻键合闸允许：3s*///

//	SV_TimerFeedWatchdog = 0;					///*看门狗定时器清零*///

	SV_TimerPowerOn = 0;						///*上电计时器：用于区分频繁上下电*///
		
//	SF_LowpowerTimerStop();						///*低功耗基本节拍停止*///

	SV_BeeperAct = C_NotDisplay;
	SV_BeeperTime = 0;
	SV_BeeperCycle = 0;
	SV_BeeperReverseTime = 0;
	
	SV_Timer_Delay = 0;
	
	SF_GetMeterType();
	SV_RCHFTemp=0;///*温度清零
	
	if(C_Cap_OpenAfter30min == C_Cap_OpenAfter30min_En)	
	{
		SV_usSuperCapCharge_Time = C_PowerOn_30min;						/*上电计时器：用于开启超级电容充电*/		
	}
	else
	{
		SV_usSuperCapCharge_Time = C_PowerOn_3s;						/*上电计时器：用于开启超级电容充电*/	
	}

	
	
//	Str_KeyUp.Timer = C_InitialValue_150ms;				///*上翻键*///
//	Str_KeyDown.Timer = C_InitialValue_150ms;			///*下翻键*///
//	Str_KeyPrg.Timer = C_InitialValue_150ms;			///*编程键*///
//	Str_KeyOpenCover.Timer = C_InitialValue_150ms;		///*开表盖*///
//	Str_KeyOpenTerminal.Timer = C_InitialValue_150ms;	///*开端尾盖*///
//	Str_CheckAuPower.Timer = C_InitialValue_150ms;		///*辅助电源掉电检测*///
//	Str_Magnetic.Timer = C_InitialValue_150ms;			///*磁场检测*///
//	Str_MeterICIRQ.Timer = C_InitialValue_150ms;		///*计量芯片IRQ请求*///
//	Str_RelayStatus.Timer = C_InitialValue_150ms;		///*继电器状态*///
//	Str_ModuleStatus.Timer = C_InitialValue_150ms;		///*模块上行通信状态*///
//	Str_CardStatus.Timer = C_InitialValue_150ms;		///*插卡状态*///
//	
//	Str_KeyUpPermit.Timer = C_InitialValue_3150ms;		///*上翻键合闸允许：3s*///
//	Str_KeyDownPermit.Timer = C_InitialValue_3150ms;	///*下翻键合闸允许：3s*///

}

///**************************************************************************************************///
///*函数原型：void InF_Delay_us(ulong32 Delay_Num)                                                  *///
///*输入参数：Delay_Num：延时数据。即延时的us为延时单位的延时数,该参数由使用者自行进行宏定义，      *///
///*定义在通用文件中。该入口参数为16进制数，由调用者进行转换                                        *///
///*输出参数：无                                                                                    *///
///*返回参数：无                                                                                    *///
///*功能说明：以us为单位进行延时，此延时是在该接口函数中死等。                                      *///
///*备    注：                                                                                      *///
	///*1）该延时程序需考虑进/出函数时间、配置定时器时间、程序指令执行时间（需要调试)。             *///
	///*2）该延时函数不关闭中断，如果在延时过程中发生中断延时时间就超过预期（对于底层操作没有影响） *///
	///*3）该函数严禁中断调用																	    *///
	///*4）因为程序本身执行时间的关系，该延时程序最好用于50us以上的延时                 		    *///
	///*5) 最大延时不能超过1048575us
///**************************************************************************************************///
#define C_Delay_1us 16000000/1000000

void InF_Delay_us(ulong32 Delay_Num)
{
	ulong32 V_Delay_Num;
	ulong64 V_Temp;
//	SwitchOn_BackLight();
	if((0 == Delay_Num)||(Delay_Num>1048575))///*根据V_Temp不能大于0xFFFFFF及Fcpu 22020096，得到1048575
	{
		return;
	}
	///*SysTick的时钟源为Fcpu/2：即22020096/2  MHz*///
	V_Temp=Delay_Num;
	V_Temp=V_Temp*C_Delay_1us;
	
	if(V_Temp>0xFFFFFF)///*由于SysTick 计数器只有24 位，用户需保证ticks 不能超过0xFFFFFF。
	{
		return;
	}
	V_Delay_Num=(ulong32)V_Temp;
//	SysTick_Config(V_Delay_Num);///*库函数
	SysTick->CTRL = 0;
	SysTick->LOAD = V_Delay_Num-1;		
	SysTick->VAL = 0;
	SysTick->CTRL |= SysTick_ENABLE;

	while( (SysTick->CTRL & SysTick_COUNTFLAG) != SysTick_COUNTFLAG )
	{
		if( 0 == SysTick->LOAD )
		{
			break;
		}
	}
	
	SysTick->CTRL = 0;
//	SwitchOff_BackLight();
}

///**************************************************************************************************///
///*函数原型：uchar8 InF_Delay_us_Start(ulong32 Delay_Num)                                                  *///
///*输入参数：Delay_Num：延时数据。即延时的us为延时单位的延时数,该参数由使用者自行进行宏定义，      *///
///*定义在通用文件中。该入口参数为16进制数，由调用者进行转换                                        *///
///*输出参数：无                                                                                    *///
///*返回参数：无                                                                                    *///
///*功能说明：以us为单位进行延时，该函数仅起动延时                                    *///
///*备    注：                                                                                      *///
	///*1）该延时程序需考虑进/出函数时间、配置定时器时间、程序指令执行时间（需要调试)。             *///
	///*2）该延时函数不关闭中断，如果在延时过程中发生中断延时时间就超过预期（对于底层操作没有影响） *///
	///*3）该函数严禁中断调用																	    *///
	///*4）因为程序本身执行时间的关系，该延时程序最好用于50us以上的延时                 		    *///
	///*5) 最大延时不能超过761904us
///**************************************************************************************************///
void InF_Delay_us_Start(ulong32 Delay_Num)
{
	ulong32 V_Delay_Num;
	ulong64 V_Temp;
	
	if((0 == Delay_Num)||(Delay_Num>1048575))///*根据V_Temp不能大于0xFFFFFF及Fcpu 22020096，得到761904
	{
		return;
	}
	///*SysTick的时钟源为Fcpu/2：即22020096/2  MHz*///
	V_Temp=Delay_Num;
	V_Temp=V_Temp*C_Delay_1us;
	
	if(V_Temp>0xFFFFFF)///*由于SysTick 计数器只有24 位，用户需保证ticks 不能超过0xFFFFFF。
	{
		return;
	}
	V_Delay_Num=(ulong32)V_Temp;
//	SysTick_Config(V_Delay_Num);///*库函数
	SysTick->CTRL = 0;
	SysTick->LOAD = V_Delay_Num-1;		
	SysTick->VAL = 0;
	SysTick->CTRL |= SysTick_ENABLE;
}

void InF_Delay_us_Stop( void )
{
	///*SysTick的时钟源为HCLK：本系统中配置为2MHz*///
	//SysTick->CTRL &= SysTick_CLKSource_HCLK_Div8;
	SysTick->CTRL = 0;
	SysTick->VAL = 0;

}
///**************************************************************************************************///
///*函数原型：uchar8 InF_Delay_us_Finish( void )                                                  *///
///*输入参数：无      *///
///*输出参数：无                                                                                    *///
///*返回参数：C_OK:延时时间到;C_Error:延时未到                                                                                    *///
///*功能说明：以us为单位进行延时，调用该函数时返回延时时间是否到                                    *///
///*备    注：                                                                                      *///
	///*1）延时未到,只返回标志             *///
	///*2）延时时间到，关闭定时器,并返回延时时间到标志                 		    *///
///**************************************************************************************************///
uchar8 InF_Delay_us_Finish( void )
{
	
	if( (SysTick->CTRL & SysTick_COUNTFLAG) != SysTick_COUNTFLAG )
	{
		return C_Error;
	}
	else
	{
		SysTick->CTRL = 0;
		return C_OK;
	}
}

///**************************************************************************************************///
///*函数原型：void InF_SysTickDelay_1s(void)                                                  *///
///*输入参数：无      *///
///*输出参数：无                                                                                    *///
///*返回参数：无                                                                                    *///
///*功能说明：将systick定时器的配置为1s定时，用于CARD/ESAM通信的超时控制                            *///
///*备    注：                                                                                      *///
	///*1）该函数将定时器溢出时间配置为1s             *///
	///*2）1s到后产生溢出标志SysTick_COUNTFLAG *///
	///*3）该函数严禁中断调用																	    *///
///**************************************************************************************************///
void InF_SysTickDelay_1s(void)
{
	///*SysTick的时钟源为HCLK：本系统中配置为2MHz*///
	//SysTick->CTRL &= SysTick_CLKSource_HCLK_Div8;
	SysTick->CTRL = 0;
	SysTick->LOAD = 16000000;		///*1s定时*///
	SysTick->VAL = 0;
	SysTick->CTRL |= SysTick_ENABLE;
	///*test
//	SwitchOn_TripLed();///*test
//	while( (SysTick->CTRL & SysTick_COUNTFLAG) != SysTick_COUNTFLAG )
//	{
//		if( 0 == SysTick->LOAD )
//		{
//			break;
//		}
//	}
//	SwitchOff_TripLed();///*test
}

///**************************************************************************************************///
///*函数原型：void InF_Delay_1s(void)                                                  *///
///*输入参数：无      *///
///*输出参数：无                                                                                    *///
///*返回参数：C_OK:延时时间未到;C_Error:延时时间已到                                                *///
///*功能说明：将systick定时器的配置为1s定时，用于CARD/ESAM通信的超时控制                            *///
///*备    注：                                                                                      *///
	///*1）该函数将定时器溢出时间配置为1s             *///
	///*2）1s到后产生溢出标志SysTick_COUNTFLAG *///
	///*3）该函数严禁中断调用																	    *///
///**************************************************************************************************///
uchar8 InF_JudgeDelay_1s(void)
{
	if( SysTick->CTRL & SysTick_COUNTFLAG )
	{
		SysTick->CTRL = 0;
		return C_Error;
	}
	else
	{
		if( 0 == SysTick->LOAD )
		{
			SysTick->CTRL = 0;
			return C_Error;
		}
	}
	return C_OK;
}
///**************************************************************************************************///
///*函数原型：void InF_Delay_2us                                                                    *///
///*输入参数：无                                                                                    *///
///*输出参数：无                                                                                    *///
///*返回参数：无                                                                                    *///
///*功能说明：延时2us，此延时是在该接口函数中死等。                                                 *///
///**************************************************************************************************///
void InF_Delay_2us(void)
{
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
}

///************************************************************************///
///*函数原型:void InF_ClrWatchDogTimer(void)*///
///*函数功能:处理看门狗*///
///*输入参数:无*///
///*输出参数:无*///
///*返回参数:掉电了，返回C_Error；没有掉电，返回C_OK*///
///*调用时机：*///
///*备注:*///
///************************************************************************///
void InF_ClrWatchDogTimer(void)
{
//	if( SV_TimerFeedWatchdog < C_WatchDog_FeedOut )
//	{
		SV_TimerFeedWatchdog = 0;
//	}
}

/*******************************************************************************
函数原型：void InF_DealWith5ms(void)
功能描述：无
输入参数：无
输出参数：无
返回参数：无
调用位置：主调度每个循环都调用该函数，进行5ms是否到的判断，到则进行5ms相关的一堆处理
备    注：
*******************************************************************************/
void InF_DealWith5ms(void)
{
	uchar8 V_ucBuffer[5];
	ushort16 usTemp, V_usDataEncode;
	ulong32 ulTemp;
	uchar8 ucTemp[CLMeter_Temp];
    
	/**********************************/
	/*增加100ms采样处理，采一个点时间6.42ms*/
		
	if( SV_TimerBasedTickTimer_100ms >= C_Interval_100ms )
	{
		SV_TimerBasedTickTimer_100ms = 0;
#if 0		
		if(GV_ucGetADC_Flag == C_GetADC_On)
		{
#endif
            SF_ADC_Set(C_ADC_CmpAndJec);
#if 0		
        }
#endif

        /*2020标准主动上报2005*/
        {
            V_ucBuffer[0] = Pt_Dispatch_Timing;
            V_ucBuffer[1] = C_100MS;
            Dispatch_SendMessage(C_Msg_Communication, V_ucBuffer, (Pt_Dispatch_Timing_Len + 1));
        }
	}
	
	/**********************************/
	/*下面处理500ms到周期的事情：超过500ms的时间直接被丢弃*/
	if( SV_TimerBasedTickTimer_500ms >= C_Interval_500ms )
	{
		SV_TimerBasedTickTimer_500ms = 0;
        
		/*500ms到，发消息给显示模块、通信模块、继电器模块、计量模块、调度读取RTC、电能计算*/
		V_ucBuffer[0] = Pt_Dispatch_Timing;
		V_ucBuffer[1] = C_HalfSecond;
        
		Dispatch_SendMessage(C_Msg_Dispatch, V_ucBuffer, (Pt_Dispatch_Timing_Len + 1) );
		
		Dispatch_SendMessage(C_Msg_Display, V_ucBuffer, (Pt_Dispatch_Timing_Len + 1) );
		
		Dispatch_SendMessage(C_Msg_Communication, V_ucBuffer, (Pt_Dispatch_Timing_Len + 1) );
		
		Dispatch_SendMessage(C_Msg_Deal_RelayStatus, V_ucBuffer, (Pt_Dispatch_Timing_Len + 1) );
		
		Dispatch_SendMessage(C_Msg_MeterIC, V_ucBuffer, (Pt_Dispatch_Timing_Len + 1) );
		
		Dispatch_SendMessage(C_Msg_EnergyMetering, V_ucBuffer, (Pt_Dispatch_Timing_Len + 1) );
		
		SF_GetMeterType();		/*读取电表通信类型:模块表还是非模块表*/
		SF_UartOvertime();		/*串口超时处理*/
	}
    
	/**************************************/
	if( SV_TimerBasedTickTimer_1000ms >= C_Interval_1000ms )
	{
		SV_TimerBasedTickTimer_1000ms = 0;
        
		/*1s到，发消息给A/D转换模块，进行电池电压测量*/
		V_ucBuffer[0] = Pt_Dispatch_Timing;
		V_ucBuffer[1] = C_SecondChange;
		Dispatch_SendMessage(C_Msg_BatteryVoltagleMetering, V_ucBuffer, (Pt_Dispatch_Timing_Len + 1));
        
		/*全失压处理模块:全失压在有电的时候也发,在处理的时候判如果有电不处理,电源处于PowerOff才处理*/
		Dispatch_SendMessage(C_Msg_AllLossVoltage, V_ucBuffer, (Pt_AllLossVoltage_Len + 1) );
		
        if( InF_ReadPowerState() == C_PowerOn )
		{
			if(SV_TimerPowerOn < C_PowerOn_3s)			/*上电计时器是否满3s*/
			{
				SV_TimerPowerOn++;			
			}
					
			if(SV_usSuperCapCharge_Time != 0x00)			/*上电计时器是否满30min*/
			{
				SV_usSuperCapCharge_Time--;
				if( SV_usSuperCapCharge_Time == 0x00 )		/*上电30min，在有电的情况下*/
				{
					DF_SwitchOn_SuperCapCharge(  );	    /*超级电容充电、关闭放电*/
					DF_SwitchOff_SuperCapPower(  );
				}
			}			
		}
		
		if(Inf_SatisfyPowerOnTime() != C_OK)                            /*主动上报1小时闭锁时间*/ 
		{
			if( C_OK == Inf_BackLightLimit() )                          /*电压满足要求，目前是≥60%Un，点亮背光、报警继电器*/
			{
				SV_PowerOffShutAcReportTime++;         
			}
		}
		
		/*****************增加扩展定义的消息出发*********************/
		V_ucBuffer[0] = Pt_Dispatch_Timing;
		Dispatch_SendMessage(C_Msg_DataProcess_External, V_ucBuffer, (Pt_DataProcess_Len + 1));
	}
	
	/**************************************/
	if( SV_TimerCruise >= C_Interval_5000ms )
	{
		SV_TimerCruise = 0;
	
		/*发消息给数据层，进行5s巡航处理，巡航程序自己进行20min的累加保存电量(此处不管)*/
		V_ucBuffer[0] = Pt_Dispatch_Timing;
		Dispatch_SendMessage(C_Msg_DataProcess, V_ucBuffer, (Pt_DataProcess_Len + 1));
	
		InF_S_Dispatch_5s();		               /*安全模块每5s调一次*/
	
		if( InF_ReadPowerState(  ) == C_PowerOn )  /*采用32.768进行RCHF校正*/
		{						
			usTemp = CLMeter_Temp;
			if(InF_Read_Data(CMeter_Temp, &ucTemp[0], &usTemp, &V_usDataEncode) == C_OK)
			{
				if(ucTemp[1] & 0x80)						/*负数*/
				{
					ucTemp[1] &= 0x7F;
				}	
	
				PF_BCDtoHexBytes(&ucTemp[0], &ulTemp, CLMeter_Temp);
				usTemp = (ushort16)ulTemp;

				if(SV_RCHFTemp > usTemp)
				{
					if( (SV_RCHFTemp - usTemp) >= 0x50 )	/*相差大于5°*/
					{
						SV_RCHFTemp = usTemp;
						RCHF_Adj_Proc( );
					}					
				}
				else 
				{
					if((usTemp - SV_RCHFTemp) >= 0x50)
					{
						SV_RCHFTemp = usTemp;
						RCHF_Adj_Proc();
					}
				}
			}
			else 
			{
				RCHF_Adj_Proc();
			}
		}
	}
    
	/**************************************/
	if( SV_TimerCheckMcu >= C_Interval_1min )
	{
		SV_TimerCheckMcu = 0;
	
		/*检查mcu是否正常工作：直接调用接口函数*/
		InF_SystemMonitor();
	
		/*每min校验一次RTC的SFR是否正常:直接调用接口函数*/
		InF_CheckRTC();
	
		/*发消息给调度,进行每分钟一次的RC校准*/
		V_ucBuffer[0] = Pt_CalibrateRC;
		Dispatch_SendMessage(C_Msg_CalibrateRC,V_ucBuffer,Pt_CalibrateRC_Len+1);
	}
    
	/**************************************/
	/*以下是对上翻键/下翻键/编程键/插卡的处理
	直接调用InF_GetPeripheralStatus( uchar8 )函数,在此函数中,对于上述4个动作,
	直接判定去抖时间是否到,如果去抖时间到,则HStatus翻转,再判断翻转后的状态
	如果翻转为有效状态,则将定时器清零,同时将消息发给相关模块*/
	
	InF_GetPeripheralStatus( C_KeyUp );				/*上翻:键显给显示模块*/
	InF_GetPeripheralStatus( C_KeyUpForRelay );		/*上翻:按键3s给继电器模块*/
	
	InF_GetPeripheralStatus( C_KeyDown );			/*下翻:键显给显示模块*/
	InF_GetPeripheralStatus( C_KeyDownForRelay );	/*下翻:按键3s给继电器模块*/

#if 0	
	InF_GetPeripheralStatus( C_KeyPrg );			/*编程:给通信模块*/
#endif
	
	InF_GetPeripheralStatus( C_CardStatus );		/*插卡:给卡处理模块*/

#if 0	
	if( Str_KeyUp.Timer >= C_Interval_50ms )
	{
		Str_KeyUp.Timer = 0;
		/*发上翻键按下消息给显示模块*/
		if( InF_GetPeripheralStatus( C_KeyUp ) == C_Valid )
		{
			V_ucBuffer[0] = Pt_Dispatch_Key;
			V_ucBuffer[1] = C_KeyUp;
			Dispatch_SendMessage(C_Msg_Display,V_ucBuffer,Pt_Dispatch_Key_Len+1);
		}
	}
	if( Str_KeyUpPermit.Timer >= C_Interval_3000ms )
	{
		Str_KeyUpPermit.Timer = 0;
		/*发上翻键3s消息给继电器模块*/
		if( InF_GetPeripheralStatus( C_KeyUpForRelay ) == C_Valid )
		{
			V_ucBuffer[0] = Pt_Dispatch_Key;
			V_ucBuffer[1] = C_Key3s;
			Dispatch_SendMessage(C_Msg_Deal_RelayStatus,V_ucBuffer,Pt_Dispatch_Key_Len+1);
		}
	}
	/**************************************/
	/*下翻键处理*///
	if( Str_KeyDown.Timer >= C_Interval_50ms )
	{
		Str_KeyDown.Timer = 0;
		/*发下翻键按下消息给显示模块*/
		if( InF_GetPeripheralStatus( C_KeyDown ) == C_Valid )
		{
			V_ucBuffer[0] = Pt_Dispatch_Key;
			V_ucBuffer[1] = C_KeyDown;
			Dispatch_SendMessage(C_Msg_Display,V_ucBuffer,Pt_Dispatch_Key_Len+1);
		}
	}
	if( Str_KeyDownPermit.Timer >= C_Interval_3000ms )
	{
		Str_KeyDownPermit.Timer = 0;
		/*发下翻键3s消息给继电器模块*/
		if( InF_GetPeripheralStatus( C_KeyDownForRelay ) == C_Valid )
		{
			V_ucBuffer[0] = Pt_Dispatch_Key;
			V_ucBuffer[1] = C_Key3s;
			Dispatch_SendMessage(C_Msg_Deal_RelayStatus,V_ucBuffer,Pt_Dispatch_Key_Len+1);
		}
	}
	/**************************************/
	/*编程键处理*/
	if( Str_KeyPrg.Timer >= C_Interval_50ms )
	{
		Str_KeyPrg.Timer = 0;
		/*发编程键按下消息给显示模块*/
		if( InF_GetPeripheralStatus( C_KeyPrg ) == C_Valid )
		{
			V_ucBuffer[0] = Pt_Dispatch_Key;
			V_ucBuffer[1] = C_KeyPrg;
			Dispatch_SendMessage(C_Msg_Communication,V_ucBuffer,Pt_Dispatch_Key_Len+1);
		}
	}
	/**************************************/
	/*插卡处理*///
	if( Str_CardStatus.Timer >= C_Interval_50ms )
	{
		Str_CardStatus.Timer = 0;
		/*发有插卡消息给通信模块*/
		if( InF_GetPeripheralStatus( C_CardStatus ) == C_Valid )
		{
			V_ucBuffer[0] = Pt_CardFlag;
			V_ucBuffer[1] = C_InsertCard;
			Dispatch_SendMessage(C_Msg_Card,V_ucBuffer,Pt_Dispatch_Key_Len+1);
		}
	}
#endif
	/**************************************/
}

///***********************************************************************************///
///*Function：低功耗基本节拍中断*///
///*Description：5ms中断一次,直接操作全局变量进行++*///
///***********************************************************************************///
void LowpowerTimer_IRQHandler(void)
{
	LowpowerTimer->LPTIF |= 0x00000007;	///*清中断标志*///
	///*****************************************///
	///*****************************************///
	///*500ms计数器*///
	if( SV_TimerBasedTickTimer_500ms <= C_Interval_500ms )
	{
		SV_TimerBasedTickTimer_500ms++;
//		if(SV_TimerBasedTickTimer_500ms%2)
//		{ 
//			SwitchOn_BackLight();///test niu,5ms
//		}
//		else
//		{
//			SwitchOff_BackLight();///test niu
//		}	
	}
	///*****************************************///
	///*1000ms计数器:停电唤醒时不需要s变化消息(这个s变化仅用于有电时电池转换和超级电容充电管理)*///
	if( SV_TimerBasedTickTimer_1000ms <= C_Interval_1000ms )
	{
		SV_TimerBasedTickTimer_1000ms++;
	}
	///*分钟计数器*///
	if( SV_TimerCheckMcu < C_Interval_1min )
	{
		SV_TimerCheckMcu++;
	}
	///**************************************///
	///*上电后闭锁读取外部检测口线功能100ms*///
	SV_TimerShut100ms = 0;
	///**************************************///
	///*喂狗定时器*///
//	SV_TimerFeedWatchdog++;
	if( SV_TimerFeedWatchdog <= C_WatchDog_Feed )
	{
		SV_TimerFeedWatchdog++;
		FeedWatchDog();
	}
	///**************************************///
	///*查询上翻按键*///
	if( Str_KeyUp.Timer <= C_Interval_50ms )
	{
		Str_KeyUp.Timer++;
		if( DF_GetIOStatus(C_KeyUp) == Str_KeyUp.HStatus )	///*当前状态与历史状态相同*///
		{
			Str_KeyUp.Timer = 0;
		}
	}
	///**************************************///
	///*查询下翻按键*///
	if( Str_KeyDown.Timer <= C_Interval_50ms )
	{
		Str_KeyDown.Timer++;
		if( DF_GetIOStatus(C_KeyDown) == Str_KeyDown.HStatus )	///*当前状态与历史状态相同*///
		{
			Str_KeyDown.Timer = 0;
		}
	}
	///**************************************///
	///*查询开表盖按键*///
	if( Str_KeyOpenCover.Timer <= C_Interval_50ms )
	{
		Str_KeyOpenCover.Timer++;
	}
	if( DF_GetIOStatus(C_KeyOpenCover) == Str_KeyOpenCover.HStatus )	///*当前状态与历史状态相同*///
	{
		Str_KeyOpenCover.Timer = 0;
	}
	///**************************************///
	///*查询端尾盖按键*///
	if( Str_KeyOpenTerminal.Timer <= C_Interval_50ms )
	{
		Str_KeyOpenTerminal.Timer++;
	}
	if( DF_GetIOStatus(C_KeyOpenTerminal) == Str_KeyOpenTerminal.HStatus )	///*当前状态与历史状态相同*///
	{
		Str_KeyOpenTerminal.Timer = 0;
	}
	///**************************************///
}

///***********************************************************************************///
///*Function：停电唤醒后的基本节拍定时器开始*///
///*Description：唤醒后调用*///
///***********************************************************************************///
void SF_LowpowerTimerStart(void)
{
	LowpowerTimerClock_EN;						///*系统时钟提供给定时器：无分频=系统时钟*///
	LowpowerTimer->LPTCFG = 0x00000400;		///*2分频，LSCLK计数时钟*///
	
	LowpowerTimer->LPTCMP = C_LowpowerTimerCounter;	
	LowpowerTimer->LPTTARGET = C_LowpowerTimerCounter;	///*5ms的节拍间隔*///
	LowpowerTimer->LPTIE &= C_TIM_UIE_DIS;		///*禁止中断*///
	LowpowerTimer->LPTIF |= 0x00000007;
	///*******************************************************///
	LowpowerTimer->LPTCTRL |= C_TimerCounter_EN;	///*正式启动定时器开始计数*///
	LowpowerTimer->LPTIE |= C_TIM_UIE_EN;		///*使能中断*///
	///*******************************************************///
	NVIC_EnableIRQ(LowpowerTimer_Interrupt);	///*基本节拍中断使能*///	
}

///***********************************************************************************///
///*Function：基本节拍定时器停止*///
///*Description：进入低功耗时调用、从唤醒状态进入低功耗调用*///
///*Influence：停止计数器、系统时钟的供给、禁止中断，从而节省功耗*///
///***********************************************************************************///
void SF_LowpowerTimerStop(void)
{	
	LowpowerTimer->LPTCTRL &= (~C_TimerCounter_EN);		///*定时器停止计数*///
	
	LowpowerTimerClock_DIS;							///*系统时钟停止提供给定时器*///
	if (LowpowerTimer->LPTIE != 0x00000000)
	{
		LowpowerTimer->LPTIE=0x00000000;
	}	
	if (LowpowerTimer->LPTIF != 0x00000000)
	{
		LowpowerTimer->LPTIF|=0x00000007;
	}				
	if (LowpowerTimer->LPTCTRL != 0x00000000)
	{
		LowpowerTimer->LPTCTRL=0x00000000;
	}
	NVIC_DisableIRQ(LowpowerTimer_Interrupt);		///*基本节拍中断禁止*///	
}

///**************************************************************************************///
///*Function:启动或者获取计时数据*///
///*Description:*///
///*Input: Method:C_StartTimer:启动定时器
///*			  C_GetTimer:获取定时器剩余的定时值
///*       time:定时值,以ms为单位, hex格式
///*			Method=C_StartTimer时,启动计时
///*			Method=C_GetTimer时,time无效
///*Output:无*///
///*Return:返回剩余计时值,当Method=C_StartTimer时直接返回输入参数time
///*Tips:time输入值最大不能超过32767(即32.767s),如果超过则强制转为32767
///**************************************************************************************///
ushort16 InF_OprateTimer(uchar8 Method,ushort16 time)
{
	switch(Method)
	{
		case C_StartTimer:
			if(time >= 32767)
			{
				SV_Timer_Delay = 32767;
			}
			else
			{
				SV_Timer_Delay = time;
			}
			SV_Timer_Delay |= C_TimerSwitch_16;
			break;
		///**************************************************///
		case C_GetTimer:
			
			break;
		///**************************************************///
		default:
			SV_Timer_Delay = 0;
			break;
	}
	return (SV_Timer_Delay & ~C_TimerSwitch_16 );
}

///**********************************************************///
///*获得上电计时器标志：满5s返回C_OK，不满5s返回C_Error*///
///**********************************************************///
uchar8 InF_GetPowerOnTimer(void)
{
	if(SV_TimerPowerOn < C_PowerOn_3s)			///*上电计时器是否满5s*///
	{
		return C_Error;
	}
	else
	{
		return C_OK;
	}
}

///**********************************************************///
///*清上电计时器标志*///
///**********************************************************///
void SF_ClrPowerOnTimer(void)
{
	SV_TimerPowerOn = 0;
}


///***********************************************************************************///
///*Function：低功耗下红外唤醒1200波特率定时器初始化*///
///***********************************************************************************///
//void SF_InfarWakeupTimerInit(void)
//{
//	InfraWakeupTimerClock_EN;								///*系统时钟提供给定时器：无分频=系统时钟*///
//	InfraWakeupTimer->CR1 = C_TIM_CR1_CLEAR;				///*控制寄存器清零*///
//	InfraWakeupTimer->CR1 |= C_TIM_CR1_URS;					///*只有溢出才产生中断*///
//	InfraWakeupTimer->CR1 |= C_TIM_CR1_ARPE;
//	InfraWakeupTimer->CR2 = C_TIM_CR1_CLEAR;				///*控制寄存器清零*///
//	InfraWakeupTimer->DIER &= C_TIM_UIE_DIS;				///*禁止中断*///
//	InfraWakeupTimer->SR &= C_TimerStatus_UIF_RESET;
//
//	InfraWakeupTimer->ARR = C_InfraWakeupTimerCounter;		///*833us的节拍间隔*///
//	InfraWakeupTimer->PSC = TIM_Prescaler_0;				///*不分频*///
//	
//	InfraWakeupTimer->EGR = C_TIM_EGR_CLEAR;
//}
///***********************************************************************************///
///*Function：低功耗下红外唤醒1200波特率定时器禁止*///
///***********************************************************************************///
//void SF_InfarWakeupTimer_Disable(void)
//{
//	InfraWakeupTimer->CR1 = C_TIM_CR1_CLEAR;				///*控制寄存器清零*///
//	InfraWakeupTimer->DIER &= C_TIM_UIE_DIS;				///*禁止中断*///
//	NVIC_DisableIRQ(InfraWakeupTimer_Interrupt);			///*中断禁止*///
//	///*******************************************************///
//	InfraWakeupTimerClock_DIS;								///*系统时钟关闭*///
//}

///***********************************************************************************///
///*Function：低功耗下红外唤醒1200波特率定时器起动*///
///***********************************************************************************///
void SF_InfarWakeupTimer_Start(void)
{
//	InfraWakeupTimer->SR &= C_TimerStatus_UIF_RESET;
//	InfraWakeupTimer->CR1 |= C_TIM_CR1_URS;					///*只有溢出才产生中断*///
//	InfraWakeupTimer->CR1 |= C_TimerCounter_EN;				///*正式启动定时器开始计数*///
//	InfraWakeupTimer->DIER |= C_TIM_UIE_EN;					///*使能中断*///
//	NVIC_EnableIRQ(InfraWakeupTimer_Interrupt);				///*中断使能*///
}

///***********************************************************************************///
///*Function：低功耗下红外唤醒1200波特率定时器停止*///
///***********************************************************************************///
void SF_InfarWakeupTimerStop(void)
{
//	InfraWakeupTimer->CR1 = C_TIM_CR1_CLEAR;				///*控制寄存器清零*///
//	InfraWakeupTimer->DIER &= C_TIM_UIE_DIS;				///*禁止中断*///
//	NVIC_DisableIRQ(InfraWakeupTimer_Interrupt);			///*中断禁止*///
	///*******************************************************///
}

///***********************************************************************************///
///*Function：清口线闭锁时间:该函数专门给低功耗下调用*///
///***********************************************************************************///
void SF_ClrShutTime(void)
{
	SV_TimerShut100ms = 0;
}

///***********************************************************************************///
///*Function：判断上电后实时量闭锁时间是否到*///
///*该函数判断上电后寄存器是否为0,不为0返回C_Error,为0返回C_OK,为非法值清零定时器并返回C_OK
///***********************************************************************************///
uchar8 SF_Shut_RealTimeData(void)
{
	if( SV_TimerShutRealTimeData == 0 )
	{
		return C_OK;
	}
	else if( SV_TimerShutRealTimeData > C_ShutRealTimeData )
	{///*不合理的值,认为时间到,并将寄存器清零*///
		SV_TimerShutRealTimeData = 0;
		return C_OK;
	}
	else
	{
		return C_Error;
	}
}
///***********************************************************************************///
///*Function：清基本节拍中1000ms定时器*///
///*Description:在做全失压时,因为计量芯片在写入初始数据后需要延时2s才能读取RMS
///*            因此在写初始数据后,需要将延时时间清零,重新计时
///***********************************************************************************///
void SF_ClrSV_TimerBasedTickTimer_1000ms(void)
{
	SV_TimerBasedTickTimer_1000ms = 0;
}


///***********************************************************************************///
///*Function：卡通信超时定时器配置*///
///*单片机工作于16M,卡工作于3.579545M,按照此频率配置单片机的定时器
///*入口参数说明:
///*			Timer_Init		C_Init				需要初始化定时器
///*							C_NotInit			不需要初始化定时器:直接配置定时器节拍就可以了
///*			ETU_Number		C_9600_ETU			9600个ETU
///*							C_1_3_ETU			1/3个ETU
///*							C_1_2_ETU			1/2个ETU
///*							C_1_ETU				1个ETU
///*							C_1_Piont_5_ETU		1.5个ETU
///*							C_2_ETU				2个ETU
///*							C_2_Piont_5_ETU		2.5个ETU
///*							C_16_ETU			16个ETU
///*							C_20_ETU			20个ETU
///*出口说明:定时器按照入口参数配置，并启动定时*///
///*注    意:该函数不可重入，需要注意*///
///***********************************************************************************///
void SF_CardBaudRateTimerInit( uchar8 Timer_Init,uchar8 ETU_Number )
{
	if( C_Init == Timer_Init )
	{
		CardBaudRateTimerClock_EN;								///*系统时钟提供给定时器：无分频=系统时钟*///
		CardBaudRateTimer->ETxCR = C_TIM_CR1_CLEAR;				///*控制寄存器清零*///
		CardBaudRateTimer->ETxINSEL = 0;				///*输入信号选择控制，APBCLK*///
		CardBaudRateTimer->ETxPESCALE1 = 0;			///*预分频寄存器，不分频*///
		CardBaudRateTimer->ETxPESCALE2 = 0;			///*预分频寄存器，不分频*///
		CardBaudRateTimer->ETxIE &= C_TIM_UIE_DIS;	///*中断禁止*///
		CardBaudRateTimer->ETxIF |= C_TimerStatus_RESET;	///*清中断标志*///
		
		CardBaudRateTimer->ETxCR |= C_CardBaudRateTimerETxCR;		///*控制寄存器配置：PWM禁止、定时模式*///
	}

	switch(ETU_Number)
	{
		case C_4ms:
		{
			CardBaudRateTimer->ETxIVR = C_CardBaudRateTimerCounter_4ms;
			CardBaudRateTimer->ETxCR |= C_TIM_CR1_CEN;					///*正式启动定时器开始计数*///
			CardBaudRateTimer->ETxIF |= C_TimerStatus_OVIF_RESET;
			break;
		}
		case C_1_3_ETU:
		{
			CardBaudRateTimer->ETxIVR = C_CardBaudRateTimerCounter_1_3_ETU;
			CardBaudRateTimer->ETxCR |= C_TIM_CR1_CEN;					///*正式启动定时器开始计数*///
			CardBaudRateTimer->ETxIF |= C_TimerStatus_OVIF_RESET;
			break;
		}
		case C_1_2_ETU:
		{
			CardBaudRateTimer->ETxIVR = C_CardBaudRateTimerCounter_1_2_ETU;
			CardBaudRateTimer->ETxCR |= C_TIM_CR1_CEN;					///*正式启动定时器开始计数*///
			CardBaudRateTimer->ETxIF |= C_TimerStatus_OVIF_RESET;
			break;
		}
		case C_1_ETU:
		{
			CardBaudRateTimer->ETxIVR = C_CardBaudRateTimerCounter_1_ETU;
			CardBaudRateTimer->ETxCR |= C_TIM_CR1_CEN;					///*正式启动定时器开始计数*///
			CardBaudRateTimer->ETxIF |= C_TimerStatus_OVIF_RESET;
			break;
		}
		case C_1_Piont_5_ETU:
		{
			CardBaudRateTimer->ETxIVR = C_CardBaudRateTimerCounter_1_Piont_5_ETU;
			CardBaudRateTimer->ETxCR |= C_TIM_CR1_CEN;					///*正式启动定时器开始计数*///
			CardBaudRateTimer->ETxIF |= C_TimerStatus_OVIF_RESET;
			break;
		}
		case C_2_ETU:
		{
			CardBaudRateTimer->ETxIVR = C_CardBaudRateTimerCounter_2_ETU;
			CardBaudRateTimer->ETxCR |= C_TIM_CR1_CEN;					///*正式启动定时器开始计数*///
			CardBaudRateTimer->ETxIF |= C_TimerStatus_OVIF_RESET;
			break;
		}
		case C_2_Piont_5_ETU:
		{
			CardBaudRateTimer->ETxIVR = C_CardBaudRateTimerCounter_2_Piont_5_ETU;
			CardBaudRateTimer->ETxCR |= C_TIM_CR1_CEN;					///*正式启动定时器开始计数*///
			CardBaudRateTimer->ETxIF |= C_TimerStatus_OVIF_RESET;
			break;
		}
		case C_16_ETU:
		{
			CardBaudRateTimer->ETxIVR = C_CardBaudRateTimerCounter_16_ETU;
			CardBaudRateTimer->ETxCR |= C_TIM_CR1_CEN;					///*正式启动定时器开始计数*///
			CardBaudRateTimer->ETxIF |= C_TimerStatus_OVIF_RESET;
			break;
		}
		case C_20_ETU:
		{
			CardBaudRateTimer->ETxIVR = C_CardBaudRateTimerCounter_20_ETU;
			CardBaudRateTimer->ETxCR |= C_TIM_CR1_CEN;					///*正式启动定时器开始计数*///
			CardBaudRateTimer->ETxIF |= C_TimerStatus_OVIF_RESET;
			break;
		}
		default:
		{
			CardBaudRateTimer->ETxIF |= C_TimerStatus_OVIF_RESET;
			CardBaudRateTimer->ETxCR &= (~C_TIM_CR1_CEN);			///*停止计数*///
			break;
		}
	}
}

///***********************************************************************************///
///*Function：卡通信ETU定时器起动*///
///***********************************************************************************///
void SF_CardBaudRateTimer_Start(void)
{
//	CardBaudRateTimer->SR &= C_TimerStatus_UIF_RESET;
//	CardBaudRateTimer->CR1 |= C_TIM_CR1_CEN;					///*正式启动定时器开始计数*///
}

///***********************************************************************************///
///*Function：卡通信ETU定时器停止*///
///***********************************************************************************///
void SF_CardBaudRateTimerStop(void)
{
	CardBaudRateTimer->ETxCR &= (~C_TIM_CR1_CEN);			///*停止计数*///
	CardBaudRateTimer->ETxIF |= C_TimerStatus_RESET;		///*清中断标志*///
	CardBaudRateTimerClock_DIS;
}


///***********************************************************************************///
///*Function：卡通信延时ETU_Number个ETU*///
///*ETU_Number:表示需要延时ETU的个数
///*            该函数基于0.5ETU的定时器溢出延时,在函数内部将入口参数*2
///***********************************************************************************///
void SF_CardTimerDelay_N_ETU( uchar8 ETU_Number )
{
	ushort16 i,j;
	
	j = 2*ETU_Number;
	
	for(i=0;i<j;i++)
	{
		while( !(CardBaudRateTimer->ETxIF & C_TimerStatus_OVIF_RESET) )
		{
			;
		}
		CardBaudRateTimer->ETxIF |= C_TimerStatus_OVIF_RESET;///*清中断标志
	}
}

