
///*****************************************************************************************///
///*Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     LowPower.c
///*Version:       V1
///*Date:          2014-3-12
///*Description:   低功耗处理
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
#include "LowPower.h"
#include "IO.h"
#include "Timer.h"
#include "uart.h"
#include "MCUConfig.h"
#include "FM33A0XX.h"
#include "ADC.h"

extern void SF_SystemClockInPowerOff(void);
extern void SF_PeriSetupPowerOff(void);
extern void SF_IOSetupPowerOff(void);
extern void SF_IOSetupPowerOff_UsedCAP(void);
extern void SF_RTCWakeUpInit(void);
extern void SF_SoftRTCWakeupMode(void);
extern void SF_SoftRTCInit(void);
extern void SF_EnterLowPower(void);
extern void SF_WritePowerMode_PowerOff(void);
extern void SF_WriteLopwerTime(ulong32 v_di,uchar8 v_lenbuf);
extern void SF_Cal_BattWorktime(void);


static uchar8 SV_PowerFlag;					///*当前电源状态标志*///

//static Str_Msg_Parameter Str_Msg_Parameter_PowerFalling;	///*定义全局的消息结构体，用于存放调度读取的消息参数信息*///



static uchar8 SV_Wakeup_Time_CNT;			///*3s检查一次有无红外唤醒*///
uchar8 SV_Wakeup_Flag;				///*有红外中断标志*///
//static uchar8 SV_Wakeup_Bit_CNT;			///*红外唤醒1200下收到的位计数器*///
//static uchar8 SV_Wakeup_CS;					///*红外接收时校验寄存器*///
//static uchar8 SV_Wakeup_RecData;			///*红外收到的1字节*///
ulong32 SV_Wakeup_Data;				///*红外唤醒收到的数据：68 11 04*///

//static uchar8 SV_CalibrateRC_State;			///*校准RC流程特征字*///
//static ulong32 SV_CalibrateRC;				///*1s唤醒寄存器*///

static ulong32 SV_LowPower_7Day;					///*停电7天计时：以秒为单位的计时*///

static Str_LowPower_Type	Str_LowPower_KeyUp;		///*上翻键在低功耗下的状态*///
static Str_LowPower_Type	Str_LowPower_KeyDown;	///*下翻键在低功耗下的状态*///
Str_LowPower_Type	Str_LowPower_Infra;		///*红外在低功耗下的状态*///

static ushort16 SV_LowPower_RTC83min;					///*停电情况下，RTC调校每83min更新一次*///

uchar8 SV_ucEnterLowPowerTimer_UpdateFlag;
///***********************************************************************************///
///*Function：基于4M计数器的初始化，用于校准基于RC的1s定时器*///
///***********************************************************************************///
void SF_CalibrateRCTimerInit(void)
{
//	CalibrateRCTimerClock_EN;								///*系统时钟提供给定时器：无分频=系统时钟*///
//	CalibrateRCTimer->CR1 = C_TIM_CR1_CLEAR;				///*控制寄存器清零*///
//	CalibrateRCTimer->CR1 |= C_TIM_CR1_URS;					///*只有溢出才产生中断*///
//	CalibrateRCTimer->CR1 |= C_TIM_CR1_ARPE;
//	CalibrateRCTimer->CR2 = C_TIM_CR1_CLEAR;				///*控制寄存器清零*///
//	CalibrateRCTimer->DIER &= C_TIM_UIE_DIS;				///*禁止中断*///
//	CalibrateRCTimer->SR &= C_TimerStatus_UIF_RESET;
//
//	CalibrateRCTimer->ARR = C_CalibrateRCTimerCounter;		///**///
//	CalibrateRCTimer->PSC = TIM_Prescaler_16000;			///*16*1000分频*///
//
//	CalibrateRCTimer->EGR = C_TIM_EGR_CLEAR;
//
//	CalibrateRCTimer->SR &= C_TimerStatus_UIF_RESET;
//	CalibrateRCTimer->CR1 |= C_TIM_CR1_URS;					///*只有溢出才产生中断*///
//	CalibrateRCTimer->CNT = 0;
//	CalibrateRCTimer->CR1 |= C_TimerCounter_EN;				///*正式启动定时器开始计数*///
//	NVIC_DisableIRQ(CalibrateRCTimer_Interrupt);			///*中断禁止*///
}
///***********************************************************************************///
///*Function：用于校准RC振荡的定时器停止*///
///***********************************************************************************///
void SF_CalibrateRCTimer_Disable(void)
{
//	CalibrateRCTimer->CR1 = C_TIM_CR1_CLEAR;				///*控制寄存器清零*///
//	CalibrateRCTimer->DIER &= C_TIM_UIE_DIS;				///*禁止中断*///
//	NVIC_DisableIRQ(CalibrateRCTimer_Interrupt);			///*中断禁止*///
//	///*******************************************************///
//	CalibrateRCTimerClock_DIS;								///*系统时钟关闭*///
}

///************************************************************************///
///*函数原型:void Msg_CalibrateRC(Str_Msg_Parameter *P_Msg_Parameter)
///*函数功能:开启校准RC1s定时器的使能
///*输入参数:P_Msg_Parameter: 统一的Str_Msg_Parameter型变量
///*消息来源:SourceAddr= C_Msg_Dispatch,调度
///*目的消息:DerictAddr = C_Msg_CalibrateRC;Len = 0
///*输出参数:
///*返回参数:无
///*调用时机:每min校准一次
///*备注:
///************************************************************************///
void Msg_CalibrateRC(Str_Msg_Parameter *P_Msg_Parameter)
{
//	uchar8 V_ucBuffer[20];
//
//	PF_CopyDataBytes(P_Msg_Parameter->Parameter,V_ucBuffer,4);
//	if( (P_Msg_Parameter->DerictAddr != C_Msg_CalibrateRC) || (V_ucBuffer[0] != Pt_CalibrateRC) )
//	{
//		return;
//	}
//
//	///*置流程特征字:其他所有校准工作在中断里做*///
//	SV_CalibrateRC_State = 0x68;
}

///************************************************************************///
///*函数原型:void Msg_CalibrateRC(Str_Msg_Parameter *P_Msg_Parameter)
///*函数功能:校准RC振荡
///*输入参数:P_Msg_Parameter: 统一的Str_Msg_Parameter型变量
///*消息来源:SourceAddr= C_Msg_Dispatch,调度
///*目的消息:DerictAddr = C_Msg_CalibrateRC;Len = 0
///*输出参数:
///*返回参数:无
///*调用时机:每min校准一次
///*备注:
///************************************************************************///
void InF_CalibrateRC(void)
{
//	SV_CalibrateRC_State = 0;			///*校准特征字清零*///
//	SV_CalibrateRC = C_1sTimer;			///*将ST自带的RTC的秒中断寄存器初始值*///
//	SF_SoftRTCInit();					///*内部软时钟配置，用于定时唤醒：每秒唤醒一次*///
//	SF_RTCWakeUpInit();
}

///**************************************************************///
///*Function：void InF_ExcuteMessage_PowerFalling(void)*///
///*Description：掉电时，将消息队列中的消息取出并且通知各个模块*///
///*Input：无*///
///*Output：无*///
///*Calls：*///
///*Called By：*///
///*Influence：*///
///*Tips：*///
///*Others：*///
///**************************************************************///
void InF_ExcuteMessage_PowerFalling(void)
{
	//uchar8 temp;

	while(1)
	{
		if( C_Error == InF_Dealwith_MessageSqueue() )
		{
			break;
		}
	}
}

///***********************************************************************************///
///*Function：低功耗下红外唤醒外部中断配置——外部中断使能*///
///***********************************************************************************///
void SF_InfraWakeup_En(void)
{
//	IO_INFRARX->MODER &= INFRARX_IN_MODE;				///*输入模式*///
//	IO_INFRARX->PUPDR &= INFRARX_NOPUPD;				///*关闭上下拉*///
//	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
//
//	SYSCFG->InfraWakeup_ConfigRegister &= (~InfraWakeup_Configration_Select);
//	SYSCFG->InfraWakeup_ConfigRegister |= InfraWakeup_Configration_Select;
//
//	EXTI->IMR |= InfraWakeup_NoMask;
//	EXTI->RTSR &= ~InfraWakeup_Rising;					///*禁止上升沿中断*///
//	EXTI->FTSR |= InfraWakeup_Falling;					///*下降沿中断*///
//	EXTI->PR |= InfraWakeup_Trigger;					///*清中断标志*///
//	NVIC_EnableIRQ(InfraWakeup_IRQn);					///*中断使能*///
}

///***********************************************************************************///
///*Function：低功耗下红外唤醒外部中断配置——禁止*///
///***********************************************************************************///
void SF_InfraWakeup_Dis(void)
{
//	EXTI->IMR &= (~InfraWakeup_NoMask);
//	EXTI->PR |= InfraWakeup_Trigger;					///*清中断标志*///
//	NVIC_DisableIRQ(InfraWakeup_IRQn);					///*中断禁止*///
}

/*******************************************************************************
函数原型： uchar8 InF_Read_LowpowerLive(void)
功能描述： 是否允许做低功耗下的事件和上报。需要有停抄电池或者超级电容有电；
输入参数：
输出参数： 无
返回参数： C_OK：停抄电池有电或者超级电容有电；C_Error：抄表电池没有电并且超级电容没有电
调用位置:
备    注：
*******************************************************************************/
uchar8 InF_Read_LowpowerLive(void)
{
    uchar8 V_ucBuffer[CLCap_Vol] = {0}, V_BattDataBuff[CLMeter_Work_State1 + 1] = {0}, V_EleCapacitorReadFlag = C_Error;
    uchar8 V_LowpowerLive = 0, V_ucMeterWorkReadFlag = C_Error;
    ushort16 V_usEleCapacitor = 0, V_usLen, V_usDataEncode;

/*从数据层读取停电唤醒电池状态*/
    V_usLen = CLMeter_Work_State1;
    V_ucMeterWorkReadFlag = InF_Read_Data(CMeter_Work_State1, &V_BattDataBuff[0], &V_usLen, &V_usDataEncode);

/*从数据层读取超级电容状态*/
    V_usLen = CLCap_Vol;
	V_EleCapacitorReadFlag = InF_Read_Data(CCap_Vol, V_ucBuffer, &V_usLen, &V_usDataEncode);                         		/*超级电容电压值*/
    PF_Buffer2ToUshort16(V_ucBuffer, &V_usEleCapacitor);                                                    /*电压值转成ushort16格式*/

    if( ( V_ucMeterWorkReadFlag == C_OK ) && ( ( V_BattDataBuff[0] & 0x08 ) == 0 ) )                        /*停抄电池有电*/
    {
        V_LowpowerLive |= C_BattPower;
    }
    if( ( V_EleCapacitorReadFlag == C_OK ) && (V_usEleCapacitor > C_CapReport_LowerLimit ) )                /*超级电容大于3V*/
    {
        V_LowpowerLive |= C_EleCapacitor;
    }

    return V_LowpowerLive;
}

///***********************************************************************************///
///*Function：掉电中断*///
///*Description：在掉电中断里连续检测掉电标志50次，满45次则认为掉电*///
///***********************************************************************************///
void PowerDown_IRQHandler(void)
{
	uchar8 V_CheckTimes = 0;
	uchar8 V_CheckCounter = 0;

	ANAC->SVDSIF|=0x00000003;	///*清中断标志*///
	if(((ANAC->SVDALM)&ANAC_SVDALM_SVDALM_B_ENABLE) == ANAC_SVDALM_SVDALM_B_DISABLE)///*掉电,测试中断响应及while检测时间
	{
//		SwitchOn_BackLight();	///*test
//		Set_PowerDown_Input();///*设置为普通IO口

		while( V_CheckTimes < C_CheckPowerDownTimes )
		{
	    	V_CheckTimes++;

	    	if(((ANAC->SVDALM)&ANAC_SVDALM_SVDALM_B_ENABLE) == ANAC_SVDALM_SVDALM_B_DISABLE)
	    	{
	    		V_CheckCounter++;
				}
		}
		if( V_CheckCounter >= C_CheckPowerDownCounter )
		{
			///*打开停电唤醒电源*///
    		DF_SwitchOn_WakeUpPower();
    		///*打开计量芯片电源：不管6V电池是否有都打开，具体处理的时候再说*///
    		DF_SwitchOn_EMeterIcPower();
    		///*打开Flash电源*///
    		DF_SwitchOn_FlashPower();
    		///*关闭充电*///
				DF_SwitchOff_SuperCapCharge();
    		///*超级电容供电*///
    		DF_SwitchOn_SuperCapPower();
		InF_Deactivation_7816_Esam();
		///*关闭拉闸灯:防止主流程中函数时间较长时掉电,拉闸灯长时间不熄灭*///
    		DF_SwitchOff_TripLed();
//		SwitchOff_BackLight();///*test
		}
	}
}

///***********************************************************************************///
///*Function：当前电源状态*///
///***********************************************************************************///
uchar8 InF_ReadPowerState()
{
	if( (SV_PowerFlag != C_PowerOff) && (SV_PowerFlag != C_PowerFalling) && (SV_PowerFlag != C_PowerRising) )
	{
		SV_PowerFlag = C_PowerOn;
	}
	return SV_PowerFlag;
}

///**********************************************************************************///
///*Function：检测当前电源状态														*///
///*Description：检测电源是否掉电，连续判断N次，超过M次口线低则认为掉电				*///
///*Input：powerflag = 	C_PowerOn： 表示有电的时候检测是否掉电:共检测50次,45次低认为掉电*///
///*Input：			 = 	C_PowerOff：表示掉电的时候检测是否来电:共检测6次,4次低认为处于掉电*///
///*Output：赋值SV_PowerFlag并将该变量返回											*///
///*	C_PowerOn:     处于有电状态													*///
///*	C_PowerFalling:发生掉电														*///
///*	C_PowerOff:    处于掉电状态													*///
///*	C_PowerRising: 发生来电														*///
///*Calls：																			*///
///*Called By：																		*///
///*Influence：																		*///
///*Tips：																			*///
///*Others：																		*///
///*Author:																			*///
///**********************************************************************************///
uchar8 SF_Check_PowerDown(uchar8 powerflag)
{
	uchar8 checktimes_threshold,checkcounter_threshold;
	uchar8 V_CheckTimes = 0;
	uchar8 V_CheckCounter = 0;
//	SwitchOn_Beep();///*test
//	Set_PowerDown_Input();///*设置为普通IO口

	if( powerflag == C_PowerOn )
	{
		checktimes_threshold = C_CheckPowerDownTimes;
		checkcounter_threshold = C_CheckPowerDownCounter;
	}
	else
	{
		checktimes_threshold = C_CheckPowerOnTimes;
		checkcounter_threshold = C_CheckPowerOnCounter;
	}

	while( V_CheckTimes < checktimes_threshold )
	{
	    	V_CheckTimes++;

 	   	if( ((ANAC->SVDALM)&ANAC_SVDALM_SVDALM_B_ENABLE) == ANAC_SVDALM_SVDALM_B_DISABLE )///*掉电，SVD内部滤波后的电压检测标志
	    	{
	    		V_CheckCounter++;
		}
	}

	if( V_CheckCounter >= checkcounter_threshold )
	{
		if( SV_PowerFlag == C_PowerOn )
		{
			///*关闭背光、打开电池、打开Flash电源、打开红外接收电源*///
//			InF_SwithPeripherals(C_BackLight,C_Off);
//			DF_SwitchOn_WakeUpPower();
//    		DF_SwitchOn_EMeterIcPower();
//    		DF_SwitchOn_FlashPower();

			SV_PowerFlag = C_PowerFalling;		///*电源发生沿变：发生掉电*///
		}
		else
		{
			SV_PowerFlag = C_PowerOff;
		}
	}
	else
	{
		if( SV_PowerFlag == C_PowerOff )
		{
			SV_PowerFlag = C_PowerRising;		///*来电*///
		}
		else
		{
			SV_PowerFlag = C_PowerOn;			///*电源未发生沿变：未发生掉电*///
		}
//		DF_ConfigPowerDownInterrupt();///*配置为中断
	}

	return SV_PowerFlag;
}

///**********************************************************************************///
///*Function：低功耗下检测是否来电   												*///
///*Description：检测电源是否掉电，连续判断5次，超过4次口线低则认为掉电			    *///
///**********************************************************************************///
//uchar8 SF_Check_PowerDown(void)
//{
//	uchar8 V_CheckTimes = 0;
//	uchar8 V_CheckCounter = 0;
//
//	while( V_CheckTimes < 6 )
//	{
//    	V_CheckTimes++;
//
//    	if( DF_GetIOStatus_MainPower() == C_Invalid )
//    	{
//    		V_CheckCounter++;
//		}
//	}
//
//	if( V_CheckCounter >= 4 )
//	{
//		if( SV_PowerFlag == C_PowerOn )
//		{
//			SV_PowerFlag = C_PowerFalling;		///*电源发生沿变：发生掉电*///
//		}
//		else
//		{
//			SV_PowerFlag = C_PowerOff;
//		}
//	}
//	else
//	{
//		if( SV_PowerFlag == C_PowerOff )
//		{
//			SV_PowerFlag = C_PowerRising;		///*来电*///
//		}
//		else
//		{
//			SV_PowerFlag = C_PowerOn;			///*电源未发生沿变：未发生掉电*///
//		}
//	}
//	return SV_PowerFlag;
//}

///************************************************************************///
///*函数原型:uchar8 SF_KeyLock(void)*///
///*函数功能:按键锁死处理:每0.5s程序处理一次*///
///************************************************************************///
void SF_KeyLock(void)
{
	if( InF_GetPeripheralStatus(C_KeyUp) == C_Valid )
	{
		if( Str_LowPower_KeyUp.Times >= C_KeyLockCNT )
		{
			Str_LowPower_KeyUp.Wakeup_En = C_Disable;
		}
		else
		{
			Str_LowPower_KeyUp.Times++;
		}
	}
	else
	{
		Str_LowPower_KeyUp.Times = 0;
		Str_LowPower_KeyUp.Wakeup_En = C_Enable;
	}

	if( InF_GetPeripheralStatus(C_KeyDown) == C_Valid )
	{
		if( Str_LowPower_KeyDown.Times >= C_KeyLockCNT )
		{
			Str_LowPower_KeyDown.Wakeup_En = C_Disable;
		}
		else
		{
			Str_LowPower_KeyDown.Times++;
		}
	}
	else
	{
		Str_LowPower_KeyDown.Times = 0;
		Str_LowPower_KeyDown.Wakeup_En = C_Enable;
	}
}

/***************************************************************************************
函数原型: void SF_NeedToReport(uchar8 V_ReportFlag, uchar8 *V_ReportDataFramesNo)
函数功能: 如果上电不到1小时或者电表不是直接接入式不上报；如果是新掉电置上报次数为3；不过进低功耗的时候不是第一帧那么就不重新组帧直接发送缓存中数据
输入参数: V_ReportFlag：是否掉电；V_ReportDataFramesNo：是否第一帧
输出参数: 无
返回参数:
调用位置:V_ReportDataFramesNo：不是新发生的事件，置成不是第一帧
备    注:
****************************************************************************************/
void SF_NeedToReport(uchar8 V_ReportFlag, uchar8 *V_ReportDataFramesNo)
{
    uchar8 V_Mode = C_ReportNull, V_PowerOffReportType = 0, V_MeterReportMode = C_MeterReportClose;
    uchar8 V_Return = C_Error;
	ushort16 V_DataLen = CLLossVolage_Report_Mode, V_usDataEncode;

    if(Inf_SatisfyPowerOnTime() == C_OK)                    /*上报1hour闭锁*/
    {
        if(Inf_Event_REPORTONumGet() == 0)                  /*如果是新发生的掉电(上报次数为0），就重新赋值3次。否则就上报剩余次数*/
        {
            if(V_ReportFlag  == C_Happen_EventState )       /*掉电记录,如果是掉电动作*/
            {
				V_DataLen = CLPowerOff_Report_Mode;
                V_Return = InF_Read_Data(CPowerOff_Report_Mode, &V_Mode, &V_DataLen , &V_usDataEncode);     /*读掉电上报模式字是否开启*/
                if(V_Return == C_OK)
                {
                    if( ( V_Mode == C_ReportHP ) || ( V_Mode == C_ReportAll ) )		/*掉电开启上报*/
                    {
                        V_DataLen = CLReport_Type;
                        V_Return = InF_Read_Data( CPowerOff_Report_Type, &V_PowerOffReportType, &V_DataLen, &V_usDataEncode);   /*掉电主动上报*/

                        if(V_Return == C_OK)
                        {
                            if(V_PowerOffReportType  == C_ActiveReportType )
                            {
                                if(InF_ValtageType() == C_OK)       /*电压类型为直接接入式*/
                                {
                                    V_MeterReportMode = Inf_MeterReportOpen(C_PowerOff, C_FirstNo);     /*电能表主动上报开启*/
                                    if(V_MeterReportMode == C_MeterReportOpen)
                                    {
                                        Inf_Event_REPORTONumDeal(C_NewReportFlag);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    else
    {
        Inf_Event_REPORTONumDeal(0);            /*如果掉电结束上报没有发完进入低功耗，也清零不再上报。规范要求*/
        Inf_Clear_PowerOffShutAcReportTime();   /*掉电时不满1小时掉电发生时清零，如果满1小时的不清零等掉电结束后再清零*/
    }

    if(Inf_Event_REPORTONumGet() < C_ActiveReportMaxNum)      /*如果掉电的瞬间写了上报，那么直接发送数据帧不用再组帧*/
    {
        (*V_ReportDataFramesNo)++;
    }
}
/***************************************************************************************
函数原型: uchar8 InF_CheckPowerAndExcute(void)
函数功能: 检测是否掉电，如果掉电，进行掉电处理（进行低功耗前后的处理）；没有掉电直接退出
输入参数: 无
输出参数: 无
返回参数: 掉电了，返回C_Error；没有掉电，返回C_OK
调用位置:
备    注:
****************************************************************************************/
uchar8 InF_CheckPowerAndExcute(void)
{
	uchar8 V_DataBuff[20];
	ushort16 V_Delay;
	uchar8 wakeupbattflag;	     /*有无唤醒电池标志*/
	uchar8 v_keystatus, v_keytimes;
	uchar8 checkpower;
	uchar8 V_InfrarxFlag = C_Disable;
    uchar8 V_ReportDataFramesNo = C_FirstNo , V_ReportFlag = C_NULL; /*停电上报用到的临时变量，是否第一帧，是否需要上报*/
    ushort16 V_AddNum = 0;
    uchar8 V_PowerStatus = 0;
	ushort16 V_usLen, V_usDataEncode;

	checkpower = SF_Check_PowerDown( C_PowerOn );

#if 0   /*test*/
	SwitchOn_TripLed();
#endif

	if( (checkpower == C_PowerOn) || (checkpower == C_PowerRising) )
	{
		/*关闭停电唤醒电源*/
		DF_SwitchOff_WakeUpPower();

		/*关闭计量芯片电源*/
		DF_SwitchOff_EMeterIcPower();

		/*关闭Flash电源*/
		DF_SwitchOff_FlashPower();

		DF_SwitchOff_LCDPower();

        /*按键上拉电阻使用，口线推挽输出高*/
		SwitchOn_KEYPU_PowerOn();

#if 0	/*test*/
		SwitchOff_TripLed();
#endif

		return C_PowerOn;
	}

#if 0	/*test*/
	SwitchOn_TripLed();
#endif

	/**********************************************************/
	/*一旦判断到掉电，立即禁止全局中断(21规范需要掉电主动上报，所以这里不关全局中断)*/
//	__disable_irq();

    	/*关闭与低功耗无关的中断*/
	NVIC_DisableIRQ( Esam_IRQn );
	NVIC_DisableIRQ( First485_IRQn );
	NVIC_DisableIRQ( Second485_IRQn );
	NVIC_DisableIRQ( Card_IRQn );
	NVIC_DisableIRQ( Infra_IRQn );
	NVIC_DisableIRQ( LowpowerTimer_Interrupt );
	NVIC_DisableIRQ( PowerDown_IRQn );

	/*停电按键上拉电阻不使用，口线开漏输出高*/
	SwitchOff_KEYPU_PowerOff();

	/*打开唤醒电源*/
	DF_SwitchOn_WakeUpPower();

	/*打开Flash电源*/
	DF_SwitchOn_FlashPower();
	/*如果有超级电容，则打开超级电容进行供电*/

#if 1
	DF_SwitchOff_SuperCapCharge();
	DF_SwitchOn_SuperCapPower();
#endif

	/*关闭背光*/
	InF_SwithPeripherals(C_BackLight, C_Off);

	InF_SwithPeripherals(C_TripLed, C_Off);

#if 0	/*test*/
	 SwitchOn_BackLight();
#endif

	/*关闭液晶驱动*/
	InF_SwitchOffLCD();

#if 0	/*test*/
	SwitchOff_TripLed();
#endif

	InF_Deactivation_7816_Esam();

	/*关闭ADC转换*/
	InF_ADC_OFF();

	/*禁止6V电池防钝化放电*/
	DF_SwitchOff_PreventBlunt();

	/*关闭液晶显示电源*/
	DF_SwitchOff_LCDPower();

	/*处理消息队列:将队列里的消息取空并发布出去*/
	InF_ExcuteMessage_PowerFalling();
	SV_PowerFlag = C_PowerOff;

	/**********************************************************/
	/*写进低功耗时间*/
	SV_ucEnterLowPowerTimer_UpdateFlag = C_EnterLowPowerTimer_NoUpdate;
	if( InF_GetPowerOnTimer() == C_OK )
	{	/*如果上电不满3s,则认为频繁上下电,不更新进低功耗时间;否则更新*/
		/*这样做的目的是为了解决台体上电过程中,有可能会抖动,造成某些事件因为时间丢失造成事件丢失*/
		SF_WriteLopwerTime(CEnter_LowPower_Time, CLEnter_LowPower_Time);
		SV_ucEnterLowPowerTimer_UpdateFlag = C_EnterLowPowerTimer_Update;
	}
#if 0
	SwitchOff_BackLight();
#endif
	/**********************************************************/
	/*处理电源异常事件记录*/
    V_PowerStatus = InF_Read_LowpowerLive();
    if( V_PowerStatus != C_NoPower )      /*有停抄电池或者超级电容大于3V*/
    {
        if( InF_GetPowerOnTimer() == C_OK )         /*上电满3s再掉电才做*/
        {
			/*打开计量芯片电源：用于电源异常事件记录*/
			DF_SwitchOn_EMeterIcPower();

#if 0	/*test*/
			SwitchOn_BackLight();
#endif
			/*延时1s*/
			for(V_Delay = 0; V_Delay < 1000; V_Delay++)
			{
				InF_Delay_us(1000);
			}

#if 0	/*test*/
			SwitchOff_BackLight();
#endif

			if( SF_Check_PowerDown( C_PowerOff ) == C_PowerOff )      /*当前处于掉电状态才做电源异常记录、掉电记录*/
            {
                if( ( InF_PowerDownReadData_MeterIC() == C_OK )         /*低功耗下读取计量参数用于事件判断*/
                 && ( ( V_PowerStatus == C_BattPower ) || ( V_PowerStatus == C_BothBattAndCapacitor ) ) )/*停抄电池有电 或者 停抄电池和超级电容都有电*/
                {
                    Inf_PowerAbnormal();                                /*电源异常记录*/
                }
                else
                {
                    ;                                                   /*不做电源异常*/
                }

                V_ReportFlag =	Inf_LowpowerPowerFail_No6VBat();		/*掉电记录*/
                SF_NeedToReport(V_ReportFlag, &V_ReportDataFramesNo);
            }
		}
        else
        {
            ;                                                           /*不做电源异常和掉电记录*/
        }
	}

	SV_PowerFlag = C_PowerOff;
	MeterIC_Reset();				/*复位计量芯片:防止有Vcc,从而彻底关闭计量芯片*/
	DF_SwitchOff_EMeterIcPower();
#if 0
	SF_ClrPowerOnTimer();
#endif
	InF_ClearHexVarregtype_MeterIC(C_ClearCurrData);

	/**********************************************************/
	/*辅助电源失电记录*///
	Inf_LowpowerACPowerFail();

	/**********************************************************/
	InF_LowPower_IR_Inti();
	InF_LowPower_DemandInit();

	/**********************************************************/
	InF_SwitchOffLCD();

	/*关闭电源*/
	DF_SwitchOff_FlashPower();
	DF_SwitchOff_InfrarxPower();

#if 0
	DF_SwitchOff_SuperCapPower();
#endif

	DF_SwitchOff_LCDPower();

	/**********************************************************/
    if( ( InF_GetPowerOnTimer() == C_OK )	&& ( V_PowerStatus != C_NoPower ) )  /*有停抄电池或者超级电容大于3V*//*上电满3s再掉电才做*/
    {
/*低功耗下掉电上报数据帧发送*/
        Inf_ClearPowerDownTime();
        if(Inf_Event_REPORTONumGet() != 0 )                                     /*需要上报*/
        {
 //       	InF_WatchDog_Init();
            do
            {
                if( ( Inf_Comm_GetModuleCommuniFlag() == C_NoCommunication ) && ( Inf_Comm_REPORTFlag() == C_ReportNULL ) )   /*如果通信模块空闲*/
                {
                   break;
                }
				InF_Delay_us(10000);                                        /*延时10mS*/

                if(V_AddNum > C_HardDelay_100 * 1)                     /*如果次数没有清零退出，自循环3秒+发送1秒，强制退出*/
                {
                    break;
                }
				else
				{
					V_AddNum++;
				}
            }while(Inf_PowerDownTime() <= ( C_Interval_1000ms * 1 ) );           /*1S之内判是否发完*/
            V_AddNum = 0;
            Inf_ClearPowerDownTime();
            do
            {
                if(Inf_Event_REPORTONumGet() == 0 )
                {
                    InF_Delay_us(1000000);                                        /*延时1S*/
                    break;
                }
                if( ( Inf_PowerDownTime() % C_Interval_1000ms ) == 0 )
                {
                    InF_Delay_us(10000);                                        /*延时10mS*/

                    if(V_AddNum > C_HardDelay_100 * 4)                     /*如果次数没有清零退出，自循环3秒+发送1秒，强制退出*/
                    {
                        break;
                    }
					else
					{
                    	V_AddNum++;
					}
                    InF_InitComm(C_Module);
                    Inf_EventTypeCommReport(C_PowerOff, V_ReportDataFramesNo);    /*数据帧组织好了*/
                    V_ReportDataFramesNo++;
                }
            }while(Inf_PowerDownTime() <= ( C_Interval_1000ms * 3 ) );           /*3S之内判是否有应答帧*/
        }
    }

	SF_ClrPowerOnTimer();		/*上电满3秒定时器放到上报之后*/

    DF_SwitchOff_SuperCapPower();
	/**********************************************************/
	/*将红外唤醒天数、按键卡死次数(上翻、下翻)、进入低功耗后的计时器、秒累加计时器(用于累计分钟数)清零*/
	SF_EnterLowPower();

	/**********************************************************/
	InF_TickTimerStop();
	/*InF_BackUpBaseTimerStop();*/
	/**********************************************************/
	/*进低功耗前刷新一次电表运行状态字4/5/6/以及7中与事件记录相关的状态*/
	Inf_LowPowerMeterStatus();

	/*关闭与低功耗无关的中断*/
	NVIC_DisableIRQ( Esam_IRQn );
	NVIC_DisableIRQ( First485_IRQn );
	NVIC_DisableIRQ( Second485_IRQn );
	NVIC_DisableIRQ( Card_IRQn );
	NVIC_DisableIRQ( Infra_IRQn );
	NVIC_DisableIRQ( TickTimer_Interrupt );
	NVIC_DisableIRQ( LowpowerTimer_Interrupt );
	NVIC_DisableIRQ( PowerDown_IRQn );

	SF_SoftRTCInit();			/*内部软时钟配置，用于定时唤醒：每秒唤醒一次*/
	SF_RTCWakeUpInit();

#if 0
	IWDT->IWDTCFG |= 0x00000004;
#endif

	__enable_irq();

	/**********************************************************/
Lowpower_Sleep:

	if(C_Cap_WhetherUsed == C_Cap_WhetherUsed_En)
    {
		SF_IOSetupPowerOff_UsedCAP();
    }
    else
    {
		SF_IOSetupPowerOff();
    }

	SF_PeriSetupPowerOff();

	SF_SystemClockInPowerOff();

	/*清看门狗定时器,并喂狗*/
	InF_ClrWatchDogTimer();
	FeedWatchDog();

#if 0   /*test*/
	goto Lowpower_Sleep;
#endif

	/*唤醒后切换系统时钟为2M*/
	/**********************************************************/
	/*每s醒来一次：进行计时*/

#if 0   /*test*/
	SwitchOn_Beep();
#endif

	Str_LowPower_Infra.WakeupState = C_Disable;
	if( SV_LowPower_7Day < C_InfraWakeup_7Day )
	{
		SV_LowPower_7Day++;
		Str_LowPower_Infra.Wakeup_En = C_Enable;
	}
	else
	{
		Str_LowPower_Infra.Wakeup_En = C_Disable;
	}

	SV_LowPower_RTC83min++;		/*低功耗RTC时钟调校，定时器以1s为基本单位*/

	if( SV_LowPower_RTC83min >= C_LowPower_RTC83min )
	{
		SV_LowPower_RTC83min = 0;

#if 0	/*test*/
		SwitchOn_Beep();		/*test 27ms*/
#endif

		InF_TempAdc_CmpAndJec();

#if 0	/*test*/
		SwitchOff_Beep();
#endif

	}

	/**********************************************************/
	if( !(RCC->PERCLKCON1 & RCC_PERRCCCON1_PDCCKEN_ON) )	/*IO口时钟使能*/
	{
		RCC->PERCLKCON1 |= RCC_PERRCCCON1_PDCCKEN_ON;
	}

#if 0
/*test*/
	if( (IO_MCUSECOND->MODER & MCUSECOND_ANALOG_MODE) != MCUSECOND_SELECT_AF)
	{
		IO_MCUSECOND->MODER &= MCUSECOND_IN_MODE;
		IO_MCUSECOND->MODER |= MCUSECOND_SELECT_AF;
	}
	if( (IO_MCUSECOND->INEN & MCUSECOND_IN_On) == MCUSECOND_IN_On)
	{
		IO_MCUSECOND->INEN &= MCUSECOND_IN_Off;
	}
	if( (IO_MCUSECOND->PUPDR & MCUSECOND_PULLUP) == MCUSECOND_PULLUP)
	{
		IO_MCUSECOND->PUPDR &= MCUSECOND_NOPUPD;
	}
	if( (IO_MCUSECOND->OTYPER & MCUSECOND_OUTPUT_OD) != MCUSECOND_OUTPUT_OD)
	{
		IO_SECOND->OTYPER |= MCUSECOND_OUTPUT_OD;
	}
	if( (IO_MCUSECOND->OTYPER & MCUSECOND_OUTPUT_OD) != MCUSECOND_OUTPUT_OD)
	{
		IO_SECOND->OTYPER |= MCUSECOND_OUTPUT_OD;
	}

	GPIO->FOUTSEL = 0x00000002;
   	SwitchOn_BackLight();	/*test*/
	Set_PowerDown_Input();
	if( SF_Check_PowerDown( C_PowerOff ) == C_PowerRising )		/*判断是否来电*/
	{
		goto Lowpower_Exit;
	}
#endif

	checkpower = SF_Check_PowerDown( C_PowerOff );

#if 0    /*test*/
	InF_Delay_us(1000);
#endif

	if( (checkpower == C_PowerOn) || (checkpower == C_PowerRising) )
	{
		goto Lowpower_Exit;
	}

	/**********************************************************/
	/*判断是否有停抄电池*/
	wakeupbattflag = C_Disable;			/*首先置为无唤醒电池*/
	Set_WakeupBatt_Input();

	if( Read_WakeupBatt() )
	{
		wakeupbattflag = C_Enable;		/*口线为高，置为有电池*/
        DF_SwitchOn_WakeUpPower();      /*有6V电池，配置为推挽输出*/
	}
    else
    {
        DF_SwitchOn_WakeUpPower_NoBatter();     /*没有6V电池，降低功耗，配置为开漏输出高*/
    }

#if 0    /*test*/
	wakeupbattflag = C_Disable;
#endif

	/**********************************************************/
	/*如果没有唤醒电池，不能唤醒、不做全失压/掉电事件、不做开盖记录*/
	if( wakeupbattflag != C_Enable )
	{
		SV_Wakeup_Time_CNT = 0;			/*3s检查一次有无红外唤醒*/
        /****山东要求停电做全失压/停电事件、做开盖记录***/
		/**********************************************************/
		/*首先做开盖记录:*///
		SF_ClrShutTime();				/*清按键闭锁时间*/
		SET_KEYOPENCOVER_INPUT();
		SET_KEYOPENTERMINAL_INPUT();
		Inf_LowpowerOpenCoverState(C_OpenTerminalCoverEventNo);
		Inf_LowpowerOpenCoverState(C_OpenMeterCoverEventNo);
#if 0
		/**********************************************************/
		/*然后做全失压/停电事件判断,山东增加*///
		if( SV_LowPower_7Day == C_AllLossTime )
		{
			Inf_LowpowerPowerFail_No6VBat();		/*掉电记录*/
		}
#endif
		/**********************************************************/
		goto Lowpower_Sleep;
	}
	else
	{
		/**********************************************************/
		/*首先做开盖记录:*/
		SF_ClrShutTime();				/*清按键闭锁时间*/
		SET_KEYOPENCOVER_INPUT();
		SET_KEYOPENTERMINAL_INPUT();
		Inf_LowpowerOpenCoverState(C_OpenTerminalCoverEventNo);
		Inf_LowpowerOpenCoverState(C_OpenMeterCoverEventNo);

		/**********************************************************/
		/*然后做全失压/停电事件判断*/
		if( SV_LowPower_7Day == C_AllLossPrepare )
        {
			/*开计量芯片电源*/
			DF_SwitchOn_EMeterIcPower();

#if 0	/*test*/
			SwitchOn_BackLight();
#endif

            /*延时100ms写入校表数据*/
			InF_Delay_us(50000);	/*唤醒后运行8M*/

#if 0	/*test*/
			SwitchOff_BackLight();
#endif
			InF_PowerDownInitial_MeterIC();
		}

		if( SV_LowPower_7Day == C_AllLossTime )
		{
			if( InF_PowerDownReadData_MeterIC() == C_OK )
			{
#if 0
				Inf_LowpowerPowerFail();		    /*掉电记录*/
#endif

				Inf_LowpowerTotalVoltagelose();	    /*全失压*/
				InF_ClearHexVarregtype_MeterIC(C_ClearCurrData);
			}

			DF_SwitchOff_EMeterIcPower();	/*关闭计量芯片电源*/
			MeterIC_Reset();				/*复位计量芯片:防止有Vcc*/
		}

		if( SV_LowPower_7Day > C_AllLossTime )
		{
			DF_SwitchOff_EMeterIcPower();	/*确保关闭计量芯片电源*/
		}
		/**********************************************************/

		/**********************************************************/
		/*处理红外唤醒:首先开电源、使能外部中断*/
		SV_Wakeup_Flag = 0;
		SV_Wakeup_Data = 0;					/*红外唤醒收到的数据清零：68 11 04*/
		Str_LowPower_Infra.WakeupState = C_Disable;

		if( Str_LowPower_Infra.Wakeup_En == C_Enable )
		{
			SV_Wakeup_Time_CNT++;
			if( SV_Wakeup_Time_CNT >= C_InfraWakeup_Interval )	    /*检查是否到3s一次的红外唤醒判断*/
			{
				/*打开红外接收电源*/
				DF_SwitchOn_InfrarxPower();
				V_InfrarxFlag = C_Enable;
				SV_Wakeup_Time_CNT = 0;

				/*使能红外接收口线外部中断*/
				SF_InfarWakeupTimerInit();  /*低功耗红外串口配置*/
			}
		}

		/**********************************************************/
		/*然后做按键唤醒:上翻键/下翻键唤醒*/
		SET_KEYUP_INPUT();
		SET_KEYDOWN_INPUT();
		v_keytimes = 0;

		do
		{
			v_keystatus = DF_GetIOStatus( C_KeyUp );
			v_keytimes++;
		}while( (v_keystatus == C_Valid) && (v_keytimes < (C_CheckKeyTimes + 1)) );

		if( v_keytimes >= C_CheckKeyTimes )
		{
			if( Str_LowPower_KeyUp.Wakeup_En == C_Enable )
			{
				goto Lowpower_Wakeup;
			}
		}
		else
		{
			Str_LowPower_KeyUp.Wakeup_En = C_Enable;	/*判断到无按键，解锁*/
		}

		v_keytimes = 0;
		do
		{
			v_keystatus = DF_GetIOStatus( C_KeyDown );
			v_keytimes++;
		}while( (v_keystatus == C_Valid) && (v_keytimes < (C_CheckKeyTimes + 1)) );

		if( v_keytimes >= C_CheckKeyTimes )
		{
			if( Str_LowPower_KeyDown.Wakeup_En == C_Enable )
			{
				goto Lowpower_Wakeup;
			}
		}
		else
		{
			Str_LowPower_KeyDown.Wakeup_En = C_Enable;	    /*判断到无按键，解锁*/
		}

		/**********************************************************/
		if( Str_LowPower_Infra.Wakeup_En == C_Enable )
		{
			if(C_Enable == V_InfrarxFlag)     /*红外电源打开*/
			{
				V_InfrarxFlag = C_Disable;

#if 0    /*test*/
                SwitchOn_Beep();
#endif

                /*延时等待30ms*/
                for(V_Delay = 0; V_Delay < 25000; V_Delay++)		/*@2.097MHz*/
                {
                    __NOP();
                }

#if 0    /*test*/
                SwitchOff_Beep();
#endif

                /*判断是否有红外中断信号*/
                /*如果有，等待接收完成，没有，关闭红外接收电源，继续休眠*/
                if( SV_Wakeup_Flag == C_InfraWakeup_Flag )      /*有红外中断信号，最多延时200ms(实测198ms)*/
                {
                    for(V_Delay = 0; V_Delay < 10200; V_Delay++)		/*@2.097MHz*/
                    {
                        if ( ( SV_Wakeup_Data == 0x00681104 )
                          || ( SV_Wakeup_Data == 0x00110468 )
                          || ( SV_Wakeup_Data == 0x00046811 ) )
                        {
                            break;
                        }
                    }

                    if ( ( SV_Wakeup_Data == 0x00681104 )
                      || ( SV_Wakeup_Data == 0x00110468 )
                      || ( SV_Wakeup_Data == 0x00046811 ) )
                    {
                        SV_Wakeup_Data = 0;
                        SV_Wakeup_Flag = 0;

                        /*关闭红外接收电源、禁止红外中断、禁止红外时钟*/
                        DF_SwitchOff_InfrarxPower();
                        SF_InfraWakeup_Dis();
                        SF_InfarWakeupTimer_Disable();

                        goto Lowpower_Wakeup;
                    }
                }
			}
		}

#if 0
		else	/*无红外中断信号*/
#endif

		{
			SV_Wakeup_Flag = 0;
			SV_Wakeup_Data = 0;

			/*关闭红外接收电源、禁止红外中断、禁止红外时钟*/
			DF_SwitchOff_InfrarxPower();
			SF_InfraWakeup_Dis();
			SF_InfarWakeupTimer_Disable();
		}

		/**********************************************************/
		goto Lowpower_Sleep;
	}

/*电能表被唤醒*/
Lowpower_Wakeup:

	Str_LowPower_Infra.WakeupState = C_Enable;      /*红外通信判断用*/

	if( RCC->SYSCLKSEL != 0x00000000 )     /*唤醒后运行8M*/
	{
		RCC->SYSCLKSEL = 0x00000000;
	}

	SF_InfraWakeup_Dis();
	SF_InfarWakeupTimer_Disable();
	InF_Delay_us(500);					/*因为时钟源差约2倍，因此该函数延时约1ms*/
	SF_LowpowerTimerStart();			/*配置唤醒期间的基本节拍:因为非整数关系，实际约4.998ms*/

#if 0   /*test*/
	if((IO_MCUSECOND->MODER & MCUSECOND_ANALOG_MODE) != MCUSECOND_SELECT_AF)
	{
		IO_MCUSECOND->MODER &= MCUSECOND_IN_MODE;
		IO_MCUSECOND->MODER |= MCUSECOND_SELECT_AF;
	}
	if((IO_MCUSECOND->INEN & MCUSECOND_IN_On) == MCUSECOND_IN_On)
	{
		IO_MCUSECOND->INEN &= MCUSECOND_IN_Off;
	}
	if((IO_MCUSECOND->PUPDR & MCUSECOND_PULLUP) == MCUSECOND_PULLUP)
	{
		IO_MCUSECOND->PUPDR &= MCUSECOND_NOPUPD;
	}
	if((IO_MCUSECOND->OTYPER & MCUSECOND_OUTPUT_OD) != MCUSECOND_OUTPUT_OD)
	{
		IO_SECOND->OTYPER |= MCUSECOND_OUTPUT_OD;
	}
	if((IO_MCUSECOND->OTYPER & MCUSECOND_OUTPUT_OD) != MCUSECOND_OUTPUT_OD)
	{
		IO_SECOND->OTYPER |= MCUSECOND_OUTPUT_OD;
	}
	GPIO->FOUTSEL = 0x00000002;
	NVIC_DisableIRQ(RTC_WKUP_IRQn);			/*唤醒后禁止软RTC定时中断*/
#endif

	/*打开Flash电源、LCD电源*/		/*下面用于程序执行时间的测试*/
	DF_SwitchOn_LCDPower();			/*打开液晶显示电源*/

#if 0   /*test*/
    SwitchOn_BackLight();
#endif

	DF_SwitchOn_FlashPower();
	DF_SwitchOn_InfrarxPower();
	InF_Delay_us(1000);

#if 0   /*test*/
    SwitchOff_BackLight();
#endif

	/*初始化LCD驱动芯片:直接调InF*/
	InF_InitLCD();

#if 0   /*test*/
    SwitchOn_BackLight();
#endif

	InF_Delay_us(1000);

#if 0   /*test*/
        SwitchOff_BackLight();
#endif

	InF_InitLCD();
	/*低功耗下初始化显示*/
	InF_Display_WakeUpInit();
	InF_InitTimer();

	/*初始化红外通道*/
	InF_InitComm(C_IR);

	/*将J-Tag口线配置为使能*/
	InF_JTagEnable();

    /**********************************************************/
    /*更新电表运行状态字3中的供电方式*/
	V_usLen = CLMeter_Work_State3;
	InF_Read_Data(CMeter_Work_State3, &V_DataBuff[0], &V_usLen, &V_usDataEncode);

	V_DataBuff[0] &= C_PowerSupplyInit;
	V_DataBuff[0] |= C_PowerSupply;
	InF_Write_Data(C_Msg_Dispatch, CMeter_Work_State3, &V_DataBuff[0], CLMeter_Work_State3, C_W_SafeFlag);

	/*然后做全失压/停电事件判断*/
	while(1)
	{

#if 0
        if( SF_Check_PowerDown( C_PowerOn ) == C_PowerRising )
        {
            goto Lowpower_Exit;
        }
#endif

		checkpower = SF_Check_PowerDown( C_PowerOn );

#if 0   /*test*/
		SwitchOn_BackLight();
#endif

		if( (checkpower == C_PowerOn) || (checkpower == C_PowerRising) )
		{
			goto Lowpower_Exit;
		}

		/*处理看门狗*/
		InF_ClrWatchDogTimer();

		/**********************************************************/
		/*判断是否有停抄电池*/
		wakeupbattflag = C_Disable;			/*首先置为无唤醒电池*/
		Set_WakeupBatt_Input();

		if( Read_WakeupBatt() != WAKEBATT_SELECT )
		{
			/*关闭液晶、Flash电源、LCD电源、配置6V电池*/
			InF_SwitchOffLCD();
			DF_SwitchOff_FlashPower();
			DF_SwitchOff_InfrarxPower();
			DF_SwitchOff_LCDPower();	            /*关闭液晶显示电源*/
            DF_SwitchOff_WakeUpPower_NoBatter();    /*没有6V电池配置为开漏输出高*/
			goto Lowpower_Sleep;
		}
		/**********************************************************/

		/**********************************************************/
		/*每个循环处理一次5ms事件：该函数中将定时相关的消息发布*/
		InF_DealWith5ms();

		/*判断唤醒时间是否到*/
		if( InF_GetPowerOffDisplayState() != C_ContinueReceive )
		{
			/*唤醒时间到，停止低功耗5ms计时，进入低功耗*/
			SF_LowpowerTimerStop();

			/*关闭液晶、Flash电源、LCD电源*/
			InF_SwitchOffLCD();
			DF_SwitchOff_FlashPower();
			DF_SwitchOff_InfrarxPower();
			DF_SwitchOff_LCDPower();			/*关闭液晶显示电源*/
			goto Lowpower_Sleep;
		}

		/**********************************************************/
		/*处理串口解析、串口初始化：中断里置标志，主流程根据标志发消息*/
		InF_Dispatch_CommInterruptMessage();

		/**********************************************************/
		/*处理消息队列*/
		InF_Dealwith_MessageSqueue();
	}
	/**********************************************************/

Lowpower_Exit:			/*退出低功耗程序*/

#if 0   /*test*/
	SwitchOn_Beep();
#endif

	SF_LowpowerTimerStop();
	NVIC_DisableIRQ( RTC_IRQn );

	/**********************************************************/
	/*写数据层进出低功耗时间*/
	SF_WriteLopwerTime(CExit_LowPower_Time, CLExit_LowPower_Time);

	/**********************************************************/
	/*写内部电池工作时间：进出低功耗时间差值加上原来的数据*/
	if( InF_GetEnterLowPowerTimerUpdateFlag() == C_OK )
	{
		SF_Cal_BattWorktime();
	}
	/**********************************************************/

#if 0    /*test*/
	SwitchOff_Beep();
#endif

	RCC->SOFTRST = 0x5C5CAABB;

	return C_PowerRising;
}
/************************************************************************
*函数原型:void SF_WriteLopwerTime(void)
*函数功能:低功耗下写进出低功耗时间
************************************************************************/
void SF_WriteLopwerTime(ulong32 v_di,uchar8 v_lenbuf)
{
	uchar8 V_DataBuff[10];
	ushort16 V_usLen, V_usDataEncode;
	/*首先读取当前时间*/
	V_usLen = CLDate_Time;
	InF_Read_Data(CDate_Time, &V_DataBuff[0], &V_usLen, &V_usDataEncode);
	if( PF_DataTimeActive_698(&V_DataBuff[0], C_DT_Start_ss, CLDate_Time) != C_OK )
	{
		memset(&V_DataBuff[0], 0x00, CLDate_Time);
	}
	InF_Write_Data(C_Msg_Dispatch,v_di, &V_DataBuff[0], v_lenbuf, C_W_SafeFlag);
}

///************************************************************************///
///*函数原型:void SF_WriteBattWorkTime(void)
///*函数功能:写电池工作时间
///************************************************************************///
void SF_WriteBattWorkTime(void)
{

}
/*******************************************************************************
获得进出低功耗时间更新标志：已更新返回C_OK，未更新返回C_Error
*******************************************************************************/
uchar8 InF_GetEnterLowPowerTimerUpdateFlag(void)
{
	if(SV_ucEnterLowPowerTimer_UpdateFlag == C_EnterLowPowerTimer_Update)
	{
		return C_OK;
	}
	else
	{
		return C_Error;
	}
}
///************************************************************************///
///*函数原型:void SF_PeriSetupPowerOff(void)
///*函数功能:低功耗下单片机外设的配置
///*调用时机:在低功耗死循环中，每个循环都调用
///************************************************************************///
void SF_PeriSetupPowerOff(void)
{
	if(UART0->RXSTA!=0x00000000)
	{
		UART0->RXSTA&= 0xFFFFFFFE;
	}
	if(UART0->TXSTA!=0x00000002)
	{
		UART0->TXSTA &= 0xFFFFFF87;
	}
	if(UART1->RXSTA!=0x00000000)
	{
		UART1->RXSTA&= 0xFFFFFFFE;
	}
	if(UART1->TXSTA!=0x00000002)
	{
		UART1->TXSTA &= 0xFFFFFF87;
	}
	if(UART2->RXSTA!=0x00000000)
	{
		UART2->RXSTA&= 0xFFFFFFFE;
	}
	if(UART2->TXSTA!=0x00000002)
	{
		UART2->TXSTA &= 0xFFFFFF87;
	}
	if(UART3->RXSTA!=0x00000000)
	{
		UART3->RXSTA&= 0xFFFFFFFE;
	}
	if(UART3->TXSTA!=0x00000002)
	{
		UART3->TXSTA &= 0xFFFFFF87;
	}
	if(UART4->RXSTA!=0x00000000)
	{
		UART4->RXSTA&= 0xFFFFFFFE;
	}
	if(UART4->TXSTA!=0x00000002)
	{
		UART4->TXSTA &= 0xFFFFFF87;
	}
	if(UART5->RXSTA!=0x00000000)
	{
		UART5->RXSTA&= 0xFFFFFFFE;
	}
	if(UART5->TXSTA!=0x00000002)
	{
		UART5->TXSTA &= 0xFFFFFF87;
	}
	///*电源管理*///
	if(PMU->WKPFLAG!=0x00000000)
	{
		PMU->WKPFLAG|=0x000001FF;
	}
	if(PMU->LPREIF!=0x00000000)
	{
		PMU->LPREIF|=0x00000003;
	}
	///*HardFault*///
	if(SCU->HDFFLAG != 0x00000000)
	{
		SCU->HDFFLAG |= 0x0000007F;
	}

	WWDT->WWDTCON=0x000000AC;
	if(WWDT->WWDTIF != 0x00000000)
	{
		WWDT->WWDTIF |= 0x00000001;
	}
	///*Clock*///
	if(ANAC->FDETIE != 0x00000000)
	{
		ANAC->FDETIE= 0x00000000;
	}
	if(ANAC->FDETIF != 0x00000000)
	{
		ANAC->FDETIF |= 0x00000001;
	}

	///*模拟比较器*///
	if(ANAC->COMP1CR!=0x00000000)
	{
		ANAC->COMP1CR &= 0xfffffffE;
	}
	if(ANAC->COMP2CR!=0x00000000)
	{
		ANAC->COMP2CR &= 0xfffffffE;
	}
	if(ANAC->COMPIF!=0x00000000)
	{
		ANAC->COMPIF|=0x00000003;
	}
	///*I2C*///
	if(I2C->I2CCTRL!=0x00006000)
	{
		I2C->I2CCTRL=0x00006000;
	}
	if(I2C->I2CIR!=0x00000000)
	{
		I2C->I2CIR=0x00000001;
	}
	if(I2C->I2CERR!=0x00000000)
	{
		I2C->I2CERR=0x00000007;
	}
	///*HSPI*///
	if(HSPI->SPICR2!=0x00000054)
	{
		HSPI->SPICR2=0x00000054;
	}
	if(HSPI->SPIIE!=0x00000000)
	{
		HSPI->SPIIE=0x00000000;
	}
	if((HSPI->SPIIF&0x00000018)!=0x00000000)
	{
		HSPI->SPIIF|=0x00000018;
	}
	///*SPI*///
	if(SPI1->SPICR2!=0x00000054)
	{
		SPI1->SPICR2=0x00000054;
	}
	if((SPI1->SPIIF&0x00000018)!=0x00000000)
	{
		SPI1->SPIIF|=0x00000018;
	}
	if(SPI2->SPICR2!=0x00000054)
	{
		SPI2->SPICR2=0x00000054;
	}
	if((SPI2->SPIIF&0x00000018)!=0x00000000)
	{
		SPI2->SPIIF|=0x00000018;
	}
	///*7816*///
	if (U78160->U7816CTRL != 0x00000000)
	{
		U78160->U7816CTRL=0x00000000;
	}
	if (U78160->U7816IF != 0x00000002)
	{
		U78160->U7816IF|=0x00000005;
	}
	if (U78160->U7816ERR != 0x00000000)
	{
		U78160->U7816ERR|=0x0000000F;
	}
	if (U78161->U7816CTRL != 0x00000000)
	{
		U78161->U7816CTRL=0x00000000;
	}
	if (U78161->U7816IF != 0x00000002)
	{
		U78161->U7816IF|=0x00000005;
	}
	if (U78161->U7816ERR != 0x00000000)
	{
		U78161->U7816ERR|=0x0000000F;
	}
	///*DMA*///
	if (DMA->GLOBALCTRL != 0x00000000)
	{
		DMA->GLOBALCTRL=0x00000000;
	}

	///*CRC*///
	if (CRC->FLSCRCEN != 0x00000000)
	{
		CRC->FLSCRCEN=0x00000000;
	}
	///*ETIME*///
	if (ETIM1->ETxCR != 0x00000000)
	{
		ETIM1->ETxCR=0x00000000;
	}
	if (ETIM1->ETxIF != 0x00000000)
	{
		ETIM1->ETxIF|=0x0000000F;
	}
	if (ETIM2->ETxCR != 0x00000000)
	{
		ETIM2->ETxCR=0x00000000;
	}
	if (ETIM2->ETxIF != 0x00000000)
	{
		ETIM2->ETxIF|=0x0000000F;
	}
	if (ETIM3->ETxCR != 0x00000000)
	{
		ETIM3->ETxCR=0x00000000;
	}
	if (ETIM3->ETxIF != 0x00000000)
	{
		ETIM3->ETxIF|=0x0000000F;
	}
	if (ETIM4->ETxCR != 0x00000000)
	{
		ETIM4->ETxCR=0x00000000;
	}
	if (ETIM4->ETxIF != 0x00000000)
	{
		ETIM4->ETxIF|=0x0000000F;
	}
	///*BTIME*///
	if (BTIM1->BTCR1 != 0x00000000)
	{
		BTIM1->BTCR1=0x00000000;
	}
	if (BTIM1->BTIF != 0x00000000)
	{
		BTIM1->BTIF|=0x0000001F;
	}
	if (BTIM2->BTCR1 != 0x00000000)
	{
		BTIM2->BTCR1=0x00000000;
	}
	if (BTIM2->BTIF != 0x00000000)
	{
		BTIM2->BTIF|=0x0000001F;
	}
	///*LCD*///
	if (LCD->DISPCTRL != 0x00000000)
	{
		LCD->DISPCTRL=0x00000000;
	}
	if (LCD->LCDTEST != 0x00000000)
	{
		LCD->LCDTEST=0x00000000;
	}
	if (LCD->DISPIF != 0x00000000)
	{
		LCD->DISPIF|=0x00000003;
	}
	if (LCD->COM_EN != 0x00000000)
	{
		LCD->COM_EN=0x00000000;
	}
	if (LCD->SEG_EN0 != 0x00000000)
	{
		LCD->SEG_EN0=0x00000000;
	}
	if (LCD->SEG_EN1 != 0x00000000)
	{
		LCD->SEG_EN1=0x00000000;
	}
	if (LCD->LCDBSTCON != 0x00000040)
	{
		LCD->LCDBSTCON=0x00000040;
	}
	///*ADC*///
	if (ANAC->ADCCON != 0x00000000)
	{
		ANAC->ADCCON=0x00000000;
	}
	if (ANAC->ADCIF != 0x00000000)
	{
		ANAC->ADCIF|=0x00000001;
	}
	if(LPTIM->LPTCTRL != 0x00000000)
	{
		LPTIM->LPTCTRL=0x00000000;
	}
	if (LPTIM->LPTIE != 0x00000000)
	{
		LPTIM->LPTIE=0x00000000;
	}
	if (LPTIM->LPTIF != 0x00000000)
	{
		LPTIM->LPTIF|=0x00000007;
	}
	///**********SVD检测************///
	if(ANAC->SVDCFG !=	0x000000F8)///*常使能，开启数字滤波,测试功耗
	{
		ANAC->SVDCFG = 0x000000F8;
	}
	if(ANAC->SVDCON !=	0x00000001)
	{
		ANAC->SVDCON = 0x00000001;
	}
	if((ANAC->SVDSIF&0x00000003)!=0)///*清中断标志
	{
		ANAC->SVDSIF|=0x00000003;
	}
	if (!(ANAC->BORCON&ANAC_BORCFG_OFF_BOR_ENABLE))
	{
		ANAC->BORCON|=ANAC_BORCFG_OFF_BOR_ENABLE;
	}
	if (!(ANAC->PDRCON&ANAC_PDRCFG_PDREN_ENABLE))
	{
		ANAC->PDRCON=ANAC_PDRCFG_PDREN_ENABLE;
	}
	if (RCC->PLLCON&RCC_PLLCON_PLLEN_ON)
	{
		RCC->PLLCON &= (~RCC_PLLCON_PLLEN_ON);
	}
	if (!(RCC->RCLPCON&RCC_RCLPCON_RCLP_EN_B_OFF))
	{
		RCC->RCLPCON |= RCC_RCLPCON_RCLP_EN_B_OFF;
	}
	SysTick->CTRL = 0;

	///*低功耗电源配置
	if(PMU->LPREIE != 0x00000000)
	{
		PMU->LPREIE = 0x00000000;
	}
	if(RCC->SYSCLKSEL != 0x80000000)///*唤醒后运行8M
	{
		RCC->SYSCLKSEL = 0x80000000;
	}
	if(ANAC->ADCINSEL&ANAC_ANATESTSEL_BUF4TST_EN_ENABLE)
	{
		ANAC->ADCINSEL &=(~ANAC_ANATESTSEL_BUF4TST_EN_ENABLE);
	}

	if(PMU->LPMCFG != 0x00060602)
	{
		PMU->LPMCFG = 0x00060602;
	}

	if(RCC->PERCLKCON1!=0x800000FC)///*时钟初始化
	{
		RCC->PERCLKCON1=0x800000FC;
	}
	if(RCC->PERCLKCON2!=0x00060000)
	{
		RCC->PERCLKCON2=0x00060000;
	}
	if(RCC->PERCLKCON3!=0x00000000)
	{
		RCC->PERCLKCON3=0x00000000;
	}
	if(RCC->PERCLKCON4!=0x00000000)
	{
		RCC->PERCLKCON4=0x00000000;
	}
}
/**************************************************************************************************
函数原型: void SF_IOSetupPowerOff(void)
函数功能: 低功耗下单片机外设的配置
输入参数: 无
输出参数: 无
调用位置: 在低功耗死循环中，每个循环都调用
备    注: ********************没有特殊情况下，配置为开漏输出高
          *******特殊管脚配置如下*********
**************计量芯片操作，全失压判断用*************************************
计量复位管脚:在该部分配置为不对复位管脚进行任何操作，即不做配置，在进入低功耗时会配置为复位状态，
*****在低功耗程序中，开始进行全失压时即58s时，会打开复位管脚，然后全失压完成后即60s后最终复位该管脚；
计量电源控制管脚：考虑全失压，计量电源在该部分不做处理维持之前状态。
***由低功耗运行进入该配置会关闭电源，做完全失压60s后，也会关闭计量电源。
6V电源控制管脚:配置为6V电源有效，有停抄电池配置为推挽输出高；无停抄电池配置为开漏输出高
**************************************************************************************************/
void SF_IOSetupPowerOff(void)
{
	ulong32 VL_DataBuff;

	if( !( RCC->PERCLKCON1 & RCC_PERRCCCON1_PDCCKEN_ON ) )
	{
		RCC->PERCLKCON1 |= RCC_PERRCCCON1_PDCCKEN_ON;
	}

	/*关闭输入使能*/
	GPIOA->INEN &= 0xFFFF0002;    /*去除计量复位管脚*/
	GPIOB->INEN  = 0x00000000;
	GPIOC->INEN &= 0xFFFF4400;    /*去除计量电源控制及6V电池使能管脚*/
	GPIOD->INEN  = 0x00000000;
	GPIOE->INEN  = 0x00000000;
	GPIOF->INEN  = 0x00000800;    /*掉电检测*/
	GPIOG->INEN  = 0x00000000;

    /*关闭上拉使能*/
	GPIOA->PUPDR &= 0xFFFF0002;    /*去除计量复位管脚*/
	GPIOB->PUPDR  = 0x00000000;
	GPIOC->PUPDR &= 0xFFFF4400;    /*去除计量电源控制及6V电池使能管脚*/
	GPIOD->PUPDR  = 0x00000000;
	GPIOE->PUPDR  = 0x00000000;
	GPIOF->PUPDR  = 0x00000000;
	GPIOG->PUPDR  = 0x00000000;

    /*打开开漏使能*/
	GPIOA->OTYPER |= 0x0000FFFD;	/*去除计量复位管脚*/
	GPIOB->OTYPER  = 0x0000FFFF;
	GPIOC->OTYPER |= 0x0000BBFF;	/*去除计量电源控制及6V电池使能管脚*/
	GPIOD->OTYPER  = 0x0000FFFF;
	GPIOE->OTYPER  = 0x0000FFFF;
	GPIOF->OTYPER  = 0x0000FFFF;
	GPIOG->OTYPER  = 0x0000FFFF;

    /*输出高*/
	GPIOA->BSETH = 0x0000FFFD;	    /*去除计量复位管脚*/
	GPIOB->BSETH = 0x0000FFFF;
	GPIOC->BSETH = 0x0000BBFF;	    /*去除计量电源控制及6V电池使能管脚*/
	GPIOD->BSETH = 0x0000FFFF;
	GPIOE->BSETH = 0x0000FFFF;
	GPIOF->BSETH = 0x0000FFFF;
	GPIOG->BSETH = 0x0000FFFF;

	/*设置为输出*/
	VL_DataBuff=GPIOA->MODER;
	VL_DataBuff &= 0x0000000C;
	VL_DataBuff	|= 0x55555551;
	GPIOA->MODER = VL_DataBuff;	    /*去除计量复位管脚*/
	GPIOB->MODER = 0x55555555;

	VL_DataBuff  = GPIOC->MODER;
	VL_DataBuff &= 0x30300000;
	VL_DataBuff	|= 0x45455555;
	GPIOC->MODER = VL_DataBuff;	   /*去除计量电源控制及6V电池使能管脚*/

	GPIOD->MODER = 0x55555555;
	GPIOE->MODER = 0x55555555;
	GPIOF->MODER = 0x55D55555;	   /*掉电检测PF11设置为模拟输入，功耗测试*/

    #if ( 0 == _DEBUG )
	{
		GPIOG->MODER = 0x55555555;
	}
	#else
	{
		GPIOG->MODER = 0x555A5555;
	}
	#endif

	GPIO->PINWKEN	= 0x00000000;
}
/***************************************************************************************************
函数原型: void SF_IOSetupPowerOff_UsedCAP(void)
功能描述: 低功耗下单片机外设的配置
输入参数: 无
输出参数：无
返回参数: 在低功耗死循环中，每个循环都调用
备    注:********************没有特殊情况下，配置为开漏输出高
        *******特殊管脚配置如下*********
        **************计量芯片操作，全失压判断用*************************************
计量复位管脚:在该部分配置为不对复位管脚进行任何操作，即不做配置，在进入低功耗时会配置为复位状态，
*****在低功耗程序中，开始进行全失压时即58s时，会打开复位管脚，然后全失压完成后即60s后最终复位该管脚；
计量电源控制管脚：考虑全失压，计量电源在该部分不做处理维持之前状态。
***由低功耗运行进入该配置会关闭电源，做完全失压60s后，也会关闭计量电源。
6V电源控制管脚:配置为6V电源有效，有停抄电池配置为推挽输出高；无停抄电池配置为开漏输出高
超级电容管脚：有超级电容时，推挽输出高
***************************************************************************************************/
void SF_IOSetupPowerOff_UsedCAP(void)
{
	ulong32 VL_DataBuff;

	if( !(RCC->PERCLKCON1 & RCC_PERRCCCON1_PDCCKEN_ON) )
	{
		RCC->PERCLKCON1 |= RCC_PERRCCCON1_PDCCKEN_ON;
	}
	/*关闭输入使能*/
	GPIOA->INEN &= 0xFFFF2002;	    /*去除计量复位管脚及超级电容放电管脚*/
	GPIOB->INEN  = 0x00000000;
	GPIOC->INEN &= 0xFFFF4400;	    /*去除计量电源控制及6V电池使能管脚*/
	GPIOD->INEN  = 0x00000000;
	GPIOE->INEN  = 0x00000000;
	GPIOF->INEN  = 0x00000800;     /*掉电检测*/
	GPIOG->INEN  = 0x00000000;

    /*关闭上拉使能*/
	GPIOA->PUPDR &= 0xFFFF2002;	    /*去除计量复位管脚及超级电容放电管脚*/
	GPIOB->PUPDR  = 0x00000000;
	GPIOC->PUPDR &= 0xFFFF4400;	    /*去除计量电源控制及6V电池使能管脚*/
	GPIOD->PUPDR  = 0x00000000;
	GPIOE->PUPDR  = 0x00000000;
	GPIOF->PUPDR  = 0x00000000;
	GPIOG->PUPDR  = 0x00000000;

    /*打开开漏使能*/
	GPIOA->OTYPER |= 0x0000DFFD;    /*去除计量复位管脚及超级电容放电管脚*/
	GPIOB->OTYPER  = 0x0000FFFF;
	GPIOC->OTYPER |= 0x0000BBFF;    /*去除计量电源控制及6V电池使能管脚*/
	GPIOD->OTYPER  = 0x0000FFFF;
	GPIOE->OTYPER  = 0x0000FFFF;
	GPIOF->OTYPER  = 0x0000FFFF;
	GPIOG->OTYPER  = 0x0000FFFF;

    /*输出高*/
	GPIOA->BSETH = 0x0000DFFD;	    /*去除计量复位管脚及超级电容放电管脚*/
	GPIOB->BSETH = 0x0000FFFF;
	GPIOC->BSETH = 0x0000BBFF;	    /*去除计量电源控制及6V电池使能管脚*/
	GPIOD->BSETH = 0x0000FFFF;
	GPIOE->BSETH = 0x0000FFFF;
	GPIOF->BSETH = 0x0000FFFF;
	GPIOG->BSETH = 0x0000FFFF;

    /*设置为输出*/
	VL_DataBuff=GPIOA->MODER;
	VL_DataBuff &= 0x0C00000C;
	VL_DataBuff	|= 0x51555551;
	GPIOA->MODER = VL_DataBuff;	    /*去除计量复位管脚及超级电容放电管脚*/
	GPIOB->MODER = 0x55555555;

	VL_DataBuff=GPIOC->MODER;
	VL_DataBuff &= 0x30300000;
	VL_DataBuff	|= 0x45455555;
	GPIOC->MODER = VL_DataBuff;	    /*去除计量电源控制及6V电池使能管脚*/

	GPIOD->MODER = 0x55555555;
	GPIOE->MODER = 0x55555555;
	GPIOF->MODER = 0x55D55555;	   /*掉电检测PF11设置为模拟输入，功耗测试*/

    #if ( 0 == _DEBUG )
	{
		GPIOG->MODER = 0x55555555;
	}
	#else
	{
		GPIOG->MODER = 0x555A5555;
	}
	#endif

	GPIO->PINWKEN	= 0x00000000;

	DF_SwitchOn_SuperCapPower();
}
///************************************************************************///
///*函数原型:void SF_SystemClockInPowerOff(void)
///*函数功能:低功耗下系统时钟的配置
///*调用时机:在低功耗死循环中，每个循环都调用
///************************************************************************///
#define		CR_DS_MASK		0xfffffffc
void SF_SystemClockInPowerOff(void)
{
	__NOP();
	__NOP();

	/* Request Wait For Interrupt */
	__WFI();

	__NOP();
	__NOP();
}


///************************************************************************///
///*函数原型:void SF_RTCWakeUpInit(void)
///*函数功能:低功耗下单片机外设的配置
///*调用时机:在低功耗死循环中，每个循环都调用
///************************************************************************///
void SF_RTCWakeUpInit(void)
{
	if (RTC->RTCIF != 0x00000000)
	{
		RTC->RTCIF|=0x00001FFF;
	}
	RTC->RTCIE=0x00000008; ///*闹钟中断使能
	NVIC_EnableIRQ(RTC_IRQn);
}


///************************************************************************///
///*函数原型:void RTC_WKUP_IRQHandler(void)
///*函数功能:低功耗下RTC定时中断:1s中断一次,并且在有电时开定时器对1s进行校准
///*         并且校准值不写入SFR,只是算出校准值,在掉电后将校准值再写入SFR
///*调用时机:
///************************************************************************///
void RTC_WKUP_IRQHandler(void)
{
//	ulong32 temp;
//	EXTI->PR |= LINE20TRIGGER;
//	RTC->ISR &= (ulong32)~RTC_ISR_WUTF;
//////	GPIOA->ODR ^= 0x00000001;
//	if( SV_PowerFlag == C_PowerOn )		///*有电的时候才校准*///
//	{
//		if( SV_CalibrateRC_State == 0x86 )
//		{
//			SV_CalibrateRC_State = 0;
//			temp = CalibrateRCTimer->CNT;		///*取出基于4M的计数值，单位ms*///
//			temp = 1000000/temp;				///*标准1s与4M计数值之间的倍数，放大1000倍，实际为调校值*///
//			SV_CalibrateRC = RTC->WUTR;			///*基于RC振荡器典型频率(38k)的1s定时器的计数值，目前为2375*///
//			SV_CalibrateRC = SV_CalibrateRC*temp;
//			SV_CalibrateRC = SV_CalibrateRC/1000;	///*这里只需要将调校值算出来,*///
//													///*在停电进入低功耗后,直接将这个数据写入,此处不写*///
//			SF_CalibrateRCTimer_Disable();		///*停掉16位定时器*///
//		}
//		else if( SV_CalibrateRC_State == 0x68)
//		{
//			SV_CalibrateRC_State = 0x86;
//			SF_CalibrateRCTimerInit();				///*启动16位计数器*///
//		}
//	}
}

///***********************************************************************************///
///*Function：低功耗下红外1200波特率处理*///
///*Description：*///
///***********************************************************************************///
void InfraWakeupTimer_IRQHandler(void)
{
//	ulong32 databuf;
//////	GPIOA->ODR ^= 0x00000001;
//	SV_Wakeup_Flag = C_InfraWakeup_Flag;
//
//	databuf = (IO_INFRARX->IDR & INFRARX_SELECT);	///*取红外口线信号*///
//	InfraWakeupTimer->SR = C_TimerStatus_RESET;		///*将中断标志清零*///
//	///*****************************************///
//	if( SV_Wakeup_Bit_CNT <= 7 )	///*数据位：8位，只管收并算校验*///
//	{
//		SV_Wakeup_Bit_CNT++;
//		if( databuf )
//		{
//			SV_Wakeup_RecData >>= 1;
//			SV_Wakeup_RecData |= 0x80;
//			SV_Wakeup_CS++;
//		}
//		else
//		{
//			SV_Wakeup_RecData >>= 1;
//			SV_Wakeup_RecData &= 0x7f;
//		}
//	}
//	else if( SV_Wakeup_Bit_CNT == 8 )	///*校验位*///
//	{
//		SV_Wakeup_Bit_CNT = 0;
//
//		SV_Wakeup_Flag = 0;
//		SV_Wakeup_Data = 0;
//		SF_InfarWakeupTimer_Disable();
//		SF_InfraWakeup_Dis();
//		if( ((databuf)&&((SV_Wakeup_CS&0x01) == 0x01))
//			||((!(databuf))&&((SV_Wakeup_CS&0x01) == 0x00)) )
//		{
//			if( (SV_Wakeup_RecData == 0x68)||(SV_Wakeup_RecData == 0x11)||(SV_Wakeup_RecData == 0x04) )
//			{
//				SV_Wakeup_Flag = C_InfraWakeup_Flag;
//
//				SV_Wakeup_Data <<= 8;
//				SV_Wakeup_Data |= SV_Wakeup_RecData;
//				SV_Wakeup_Data &= 0x00ffffff;
//
//				if( (SV_Wakeup_Data == 0x00681104)||(SV_Wakeup_Data == 0x00110468)||(SV_Wakeup_Data == 0x00046811) )
//				{
//					//SF_InfarWakeupTimer_Disable();
//					//SF_InfraWakeup_Dis();
//
//				}
//				else
//				{
//					//SF_InfarWakeupTimer_Disable();
//					SF_InfraWakeup_En();
//				}
//			}
//			//else
//			//{
//				//SV_Wakeup_Flag = 0;
//				//SV_Wakeup_Data = 0;
//				//SF_InfarWakeupTimer_Disable();
//				//SF_InfraWakeup_Dis();
//			//}
//		}
//		//else
//		//{
//			//SV_Wakeup_Flag = 0;
//			//SV_Wakeup_Data = 0;
//			//SF_InfarWakeupTimer_Disable();
//			//SF_InfraWakeup_Dis();
//		//}
//	}
//	else
//	{
//		SV_Wakeup_Flag = 0;
//		SV_Wakeup_Data = 0;
//		SF_InfarWakeupTimer_Disable();
//		SF_InfraWakeup_Dis();
//	}
}

///************************************************************************///
///*函数原型:void SF_SoftRTCInit(void)
///*函数功能:软时钟初始化
///*调用时机:软时钟用于低功耗下的定时唤醒
///************************************************************************///
void SF_SoftRTCInit(void)
{
	RCC->PERCLKCON1|=RCC_PERRCCCON1_RTCRCCEN_ON;	///*RTC时钟使能*///

	if (RTC->RTCIF != 0x00000000)
	{
		RTC->RTCIF|=0x00001FFF;
	}
}


///************************************************************************///
///*函数原型:void SF_SoftRTCWakeupMode(void)
///*函数功能:软时钟进入初始化模式
///*调用时机:
///************************************************************************///
void SF_SoftRTCWakeupMode(void)
{
//	ulong32 initcounter = 0x00;
//	ulong32 initstatus = 0x00;
//
//	/* Disable the write protection for RTC registers */
//	RTC->WPR = C_RTCRegWpr1;
//	RTC->WPR = C_RTCRegWpr2;
//
//	/* Check if the Initialization mode is set */
//	if ((RTC->ISR & RTC_ISR_INITF) == (ulong32)0x00000000)
//	{
//		/* Set the Initialization mode */
//		RTC->ISR = (ulong32)RTC_INIT_MASK;
//
//		/* Wait till RTC is in INIT state and if Time out is reached exit */
//		do
//		{
//			initstatus = RTC->ISR & RTC_ISR_INITF;
//			initcounter++;
//		} while((initcounter != INITMODE_TIMEOUT) && (initstatus == 0x00));
//	}
}

///************************************************************************///
///*函数原型:void SF_EnterLowPower(void)
///*函数功能:进入低功耗前，需要初始化一些变量：如红外7天限制，按键卡死次数限制等
///*调用时机:
///************************************************************************///
void SF_EnterLowPower(void)
{
	Str_LowPower_KeyUp.Wakeup_En = C_Enable;
	Str_LowPower_KeyUp.Times = 0;

	Str_LowPower_KeyDown.Wakeup_En = C_Enable;
	Str_LowPower_KeyDown.Times = 0;

	SV_LowPower_7Day = 0;
	Str_LowPower_Infra.Wakeup_En = C_Enable;
	Str_LowPower_Infra.Times = 0;
	Str_LowPower_Infra.WakeupState = C_Disable;///*处于未唤醒状态
	SV_LowPower_RTC83min=0;
}

///************************************************************************///
///*函数原型:void InF_PowerOnDelay(void)
///*函数功能:上电固定延时500ms
///*调用时机:
///************************************************************************///
void InF_PowerOnDelay(void)
{
	ushort16 v_delay;
	for(v_delay=0;v_delay<C_PowerOnDelay;v_delay++)
	{
		if( ((ANAC->SVDALM)&ANAC_SVDALM_SVDALM_B_ENABLE) == ANAC_SVDALM_SVDALM_B_ENABLE )	///*检测有的，连续500次，每次间隔1ms. *///
		{
			InF_Delay_us(1000);
		}
		else
		{
			break;
		}
	}
}

/************************************************************************
*将电表运行状态字3中的供电方式写为“电池供电”
************************************************************************/
void SF_WritePowerMode_PowerOff(void)
{
	uchar8 V_ucBuffer[10];
	ushort16 V_usLen, V_usDataEncode;

	V_usLen = CLMeter_Work_State3;
	InF_Read_Data(CMeter_Work_State3, &V_ucBuffer[0], &V_usLen, &V_usDataEncode);
	V_ucBuffer[0] &= C_PowerModeInit;
	V_ucBuffer[0] |= C_PowerMode;
	InF_Write_Data(C_Msg_Dispatch, CMeter_Work_State3, &V_ucBuffer[0], CLMeter_Work_State3, C_W_SafeFlag);
}

///************************************************************************///
///*函数原型:uchar8 SF_JudgeAllLoseVoltage(void)
///*函数功能:判断是否符合全失压操作条件
///*输入:无
///*输出:SV_LowPower_7Day进行了加操作(这个变量用于停电累计7天,单位为秒)
///*返回:C_AllLossPrepare:表示需要准备做全失压:打开计量芯片电源,
///*     C_AllLossTime:标志进行全失压记录
///*调用时机:这个函数每s调用一次
///************************************************************************///
uchar8 SF_JudgeAllLoseVoltage(void)
{
	SV_LowPower_7Day++;
	if( SV_LowPower_7Day == C_AllLossPrepare )
	{
		return C_AllLossPrepare;
	}
	else if( SV_LowPower_7Day == C_AllLossTime )
	{
		return C_AllLossTime;
	}
	else
	{
		return C_Error;
	}
}

///************************************************************************///
///*函数原型:void Msg_AllLoseVoltage(Str_Msg_Parameter * P_Msg_Parameter)
///*函数功能:进行全失压处理
///*输入:P_Msg_Parameter指向消息读取后存放的变量区,
///*输出:根据相关条件进行全失压记录
///*返回:C_AllLossPrepare:表示需要准备做全失压:打开计量芯片电源,
///*     C_AllLossTime:表示进行全失压记录
///*调用时机:这个函数每s调用一次
///************************************************************************///
void Msg_AllLoseVoltage(Str_Msg_Parameter * P_Msg_Parameter)
{
	uchar8 v_databuf;

	SV_LowPower_RTC83min++;///*低功耗RTC时钟调校，定时器以1s为基本单位
		if( SV_LowPower_RTC83min >= C_LowPower_RTC83min )
		{
			SV_LowPower_RTC83min=0;
			InF_TempAdc_CmpAndJec();
	}

	if( P_Msg_Parameter->DerictAddr == C_Msg_AllLossVoltage )
	{
		if(P_Msg_Parameter->PowerFlag == C_PowerOff )
		{
			v_databuf = SF_JudgeAllLoseVoltage();
			if( C_AllLossPrepare == v_databuf )
			{
				///*开计量芯片电源*///
				DF_SwitchOn_EMeterIcPower();
				///*延时100ms写入校表数据*///
				InF_Delay_us(12500);				///*时钟差约8倍，因此100ms的延时采用12500us的值*///
				InF_PowerDownInitial_MeterIC();
				SF_ClrSV_TimerBasedTickTimer_1000ms();	///*初始化计量芯片后,重新开始计时*///
			}
			else if( C_AllLossTime == v_databuf )
			{
				if( InF_PowerDownReadData_MeterIC() == C_OK )
				{
//					Inf_LowpowerPowerFail();		///*掉电记录*///
					Inf_LowpowerTotalVoltagelose();	///*全失压*///
					InF_ClearHexVarregtype_MeterIC(C_ClearCurrData);
				}
				DF_SwitchOff_EMeterIcPower();	///*关闭计量芯片电源*///
				MeterIC_Reset();				///*复位计量芯片:防止有Vcc*///
			}


		}
	}
}

/***********************************************************************************
*Function：计算内部电池工作时间
*Description：
*Input：进出低功耗时间,数据层的内部电池工作时间
*Output：计算后的内部电池工作时间
*Calls：
*Called By：退出低功耗时做一次时间的累加
*Influence：
*Tips：
*    1.内部电池工作时间,RAM不带CRC,使用时仅判断是否为BCD码
*    2.如果进出低功耗时间非法,则默认为本次停电期间累计的工作时间为0
*    3.如果数据层的内部电池工作时间非BCD码,直接将该时间清零
*Others：
*Author: 2014/11/5
***********************************************************************************/
void SF_Cal_BattWorktime(void)
{
	uchar8 V_Buffer_DataProcess[CLBatt_Work_Time];			/*数据层读过来的时间*/
	uchar8 V_Buffer_Current[CLBatt_Work_Time];				/*本次根据进出低功耗时间计算的电池工作时间*/
	uchar8 V_Buffer_EnterLowPower[CLEnter_LowPower_Time];	/*进低功耗时间*/
	uchar8 V_Buffer_ExitLowPower[CLExit_LowPower_Time];		/*出低功耗时间*/

	ushort16 V_uslen, V_usDataEncode;
	ulong32 time;
	uchar8 V_ReturnFlag, V_len;

	/*首先从数据层读出内部电池工作时间*/
	V_uslen = CLBatt_Work_Time;
	V_ReturnFlag=InF_Read_Data(CBatt_Work_Time, &V_Buffer_DataProcess[0], &V_uslen, &V_usDataEncode);
	if(C_OK!=V_ReturnFlag)
	{
		memset(&V_Buffer_Current[0],0x00,4);
		InF_Write_Data(C_Msg_Dispatch, CBatt_Work_Time, &V_Buffer_Current[0], CLBatt_Work_Time, C_W_SafeFlag);
		return;
	}
	/*判断内部电池工作时间是否为BCD码*/
	if( PF_Judge_BCD(CLBatt_Work_Time, &V_Buffer_DataProcess[0]) == C_OK )
	{
		V_uslen = CLEnter_LowPower_Time;
		V_ReturnFlag=InF_Read_Data(CEnter_LowPower_Time, &V_Buffer_EnterLowPower[0], &V_uslen, &V_usDataEncode);
		if(C_OK!=V_ReturnFlag)
		{
			return;
		}
		V_uslen = CLExit_LowPower_Time;
		V_ReturnFlag=InF_Read_Data(CExit_LowPower_Time, &V_Buffer_ExitLowPower[0], &V_uslen, &V_usDataEncode);
		if(C_OK!=V_ReturnFlag)
		{
			return;
		}
		/*判断进出低功耗时间是否合法*/
#if 0
		if( (PF_DataTimeActive(V_Buffer_EnterLowPower, C_DT_Start_ss, CLEnter_LowPower_Time) == C_OK)
			&&(PF_DataTimeActive(V_Buffer_ExitLowPower, C_DT_Start_ss, CLExit_LowPower_Time) == C_OK) )
		{
#endif
			/*进出低功耗时间相减:在函数内已经进行合法性判断了,所以前面不需要进行合法性判断*/
			if( PF_TimeSub_Min_698(V_Buffer_EnterLowPower, V_Buffer_ExitLowPower, &time) == C_LessThan )
			{
				V_len = 4;
				PF_HextoBCDBytes(&time, &V_Buffer_Current[0], &V_len);
				PF_BCDAddBytes(&V_Buffer_DataProcess[0], &V_Buffer_Current[0], &V_Buffer_Current[0], CLBatt_Work_Time);
				InF_Write_Data(C_Msg_Dispatch, CBatt_Work_Time, &V_Buffer_Current[0], CLBatt_Work_Time, C_W_SafeFlag);
			}
#if 0
		}
#endif
	}
	else
	{
		memset(&V_Buffer_Current[0], 0x00, 4);
		InF_Write_Data(C_Msg_Dispatch, CBatt_Work_Time, &V_Buffer_Current[0], CLBatt_Work_Time, C_W_SafeFlag);
	}
}

