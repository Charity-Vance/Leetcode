/*******************************************************************************
Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     ADC.c
Version:       V1
Author:
Date:          2014-3-12
Description:   电池电压转换文件
---------------------------------------------------------------------------------
History1:      第1次修改
内容1. Date:   20201206
   	   Author:
       Modification:山东双协议程序
	   ---------------------------------------------------------------------------
内容2. Date:
   	   Author:
       Modification:
----------------------------------------------------------------------------------
History2:      第2次修改
内容1. Date:
   	   Author:
       Modification:
	   ---------------------------------------------------------------------------
内容2. Date:
   	   Author:
       Modification:
******************************************************************************/
#include "Public.h"
#include "ADC.h"
#include "Timer.h"
#include "RTCDrive.h"
#include "Communication.h"

uchar8 GV_ucTime;
//uchar8 GV_ucGetADC_Flag@".DataProcessADDR";
static ushort16 GV_ucTemp_Data[33]@".DataProcessADDR";
///**********************************************************************************///
///*Function：void ADC_SendMessage(uchar8 *pParm,uchar8 ParmLen,uchar8 DestMsg)*///
///*Description：ADC模块发消息给其他模块*///
///*Input：	*P_Parameter:消息中的参数域首地址*///
///*		ParameterLen:参数域长度*///
///*		DerictAddrMsg:目的地址*///
///*Output：无*///
///*Calls：*///
///*Called By：主调度发消息时调用*///
///*Influence：调用的地方将源消息号、目的消息号、数据域都整理好后调用该函数*///
///**********************************************************************************///
void ADC_SendMessage(uchar8 MsgDerictAddr,uchar8 *P_Parameter,uchar8 ParameterLen)
{
	Str_Msg_Parameter	Str_Message;
	Str_Message.SourceAddr = C_Msg_BatteryVoltagleMetering;	///*源地址必然是ADC模块*///
	Str_Message.DerictAddr = MsgDerictAddr;
	Str_Message.Parameter = P_Parameter;
	Str_Message.Length = ParameterLen;
	InF_WriteMessege(&Str_Message);
}

///***********************************************************************************///
///*Function：判断是否允许报警*///
///*Description：*///
///*Input:warn_type:   报警类型:C_AlarmSign,C_BackLED,C_WarnOutPut*///
///*	  warn_object: 报警对象:C_RTCBatterySign,C_PowerBatterySign*///
///*      C_RTCBatterySign        46      ///*时钟电池欠压 		*///
///*      C_PowerBatterySign      47      ///*停抄电池欠压 		*///
///*      C_AlarmSign             26      ///*报警标志     		*///
///*      C_BackLED               51      ///*背光		       	*///
///*      C_WarnOutPut            52      ///*报警输出    		*///
///*Output：C_OK:允许报警,C_Error:禁止报警*///
///***********************************************************************************///
uchar8 SF_JudgeWarn(uchar8 warn_object,uchar8 warn_type)
{
	uchar8 V_ucBuffer[15];
	uchar8 v_return = C_Error;			///*此处的赋初值为“错误”必须有*///
	ushort16 V_len, V_usDataEncode;

	V_len = CLAlarm_Status;
	if( InF_Read_Data(CAlarm_Status,&V_ucBuffer[0],&V_len, &V_usDataEncode) != C_OK )
	{
		return v_return;
	}
	switch (warn_type)
	{
		///**************************************///
		///*报警小铃铛*///
		case C_AlarmSign:
			if( warn_object == C_RTCBatterySign )
			{
				if( V_ucBuffer[10] & 0x04 )
				{
					v_return = C_OK;
				}
			}
			else if( warn_object == C_PowerBatterySign )
			{
				if( V_ucBuffer[11] & 0x08 )
				{
					v_return = C_OK;
				}
			}
		break;
		///**************************************///
		///*背光灯*///
		case C_BackLED:
			if( warn_object == C_RTCBatterySign )
			{
				if( V_ucBuffer[2] & 0x04 )
				{
					v_return = C_OK;
				}
			}
			else if( warn_object == C_PowerBatterySign )
			{
				if( V_ucBuffer[3] & 0x08 )
				{
					v_return = C_OK;
				}
			}
		break;
		///**************************************///
		///*报警继电器输出*///
		case C_WarnOutPut:
			if( warn_object == C_RTCBatterySign )
			{
				if( V_ucBuffer[6] & 0x04 )
				{
					v_return = C_OK;
				}
			}
			else if( warn_object == C_PowerBatterySign )
			{
				if( V_ucBuffer[7] & 0x08 )
				{
					v_return = C_OK;
				}
			}
		break;
		///**************************************///
		default:
			;
		break;
	}
	return v_return;
}

///***********************************************************************************///
///*Function:根据当前时钟电池状态，显示电池符号*///
///*Description:*///
///*input:C_OK:电池正常,C_Error:电池欠压*///
///*output:电池符号*///
///*return:无*///
///***********************************************************************************///
void SF_RTCBattSymbol(uchar8 BattStatus)
{
	uchar8 V_ucBuffer[4];

	if( BattStatus == C_BATT_OK )
	{
		///*时钟电池不显示*///
		V_ucBuffer[0] = Pt_DisplayStatus;
		V_ucBuffer[1] = C_RTCBatterySign|C_NotDisplay;
		V_ucBuffer[2] = 0xFF;
		V_ucBuffer[3] = 0xFF;
	}
	else
	{
		///*时钟电池显示*///
		V_ucBuffer[0] = Pt_DisplayStatus;
		V_ucBuffer[1] = C_RTCBatterySign|C_AlwaysDisplay;
		V_ucBuffer[2] = 0xFF;
		V_ucBuffer[3] = 0xFF;
	}

	ADC_SendMessage(C_Msg_Display,V_ucBuffer,(Pt_DisplayStatus_Len+1));
}
///***********************************************************************************///
///*Function:根据当前唤醒电池状态，显示电池符号*///
///*Description:*///
///*input:C_OK:电池正常,C_Error:电池欠压*///
///*output:电池符号*///
///*return:无*///
///***********************************************************************************///
void SF_WakeUpBattSymbol(uchar8 BattStatus)
{
	uchar8 V_ucBuffer[4];

	if( BattStatus == C_BATT_OK )
	{
		///*唤醒电池不显示*///
		V_ucBuffer[0] = Pt_DisplayStatus;
		V_ucBuffer[1] = C_PowerBatterySign|C_NotDisplay;
		V_ucBuffer[2] = 0xFF;
		V_ucBuffer[3] = 0xFF;
	}
	else
	{
		///*唤醒电池显示*///
		V_ucBuffer[0] = Pt_DisplayStatus;
		V_ucBuffer[1] = C_PowerBatterySign|C_AlwaysDisplay;
		V_ucBuffer[2] = 0xFF;
		V_ucBuffer[3] = 0xFF;
	}

	ADC_SendMessage(C_Msg_Display,V_ucBuffer,(Pt_DisplayStatus_Len+1));
}

///***********************************************************************************///
///*Function:如果电池状态有变化，进行小铃铛、背光、报警继电器三类报警项输出*///
///*Description:该函数在状态发生变化后调用*///
///*input:ChangeFlag=C_BattChange,表示电池状态有变化*///
///*output:小铃铛/背光/报警继电器动作或恢复*///
///*return:无*///
///***********************************************************************************///
void SF_BattWarn(uchar8 ChangeFlag)
{
	uchar8 V_ucBuffer[16];
	uchar8 i=0;

	if( ChangeFlag != 0 )	///*电池状态有变化才做*///
	{
		///*小铃铛闪烁*///
		if( ((SF_JudgeWarn(C_RTCBatterySign,C_AlarmSign)==C_OK)&&(Str_RTCBATT.HStatus == C_BATT_ERR)&&((ChangeFlag&0x0f) == C_RTCBattChange_Err))
			||((SF_JudgeWarn(C_PowerBatterySign,C_AlarmSign)==C_OK)&&(Str_WAKEUPBATT.HStatus == C_BATT_ERR)&&((ChangeFlag&0xf0) == C_WakeupBattChange_Err)) )
		{
			V_ucBuffer[i*4+0] = Pt_DisplayStatus;
			V_ucBuffer[i*4+1] = C_AlarmSign|C_TwinkleDisplay;
			V_ucBuffer[i*4+2] = 0xFF;
			V_ucBuffer[i*4+3] = 0xFF;
			i++;
		}
		else if( ((SF_JudgeWarn(C_RTCBatterySign,C_AlarmSign)!=C_OK)||((Str_RTCBATT.HStatus != C_BATT_ERR)&&((ChangeFlag&0x0f) != C_RTCBattChange_Err)))
			&&((SF_JudgeWarn(C_PowerBatterySign,C_AlarmSign)!=C_OK)||((Str_WAKEUPBATT.HStatus != C_BATT_ERR)&&((ChangeFlag&0xf0) != C_WakeupBattChange_Err))) )
		{
			V_ucBuffer[i*4+0] = Pt_DisplayStatus;
			V_ucBuffer[i*4+1] = C_AlarmSign|C_NotDisplay;
			V_ucBuffer[i*4+2] = 0xFF;
			V_ucBuffer[i*4+3] = 0xFF;
			i++;
		}
		///*背光点亮*///
		if( ((SF_JudgeWarn(C_RTCBatterySign,C_BackLED)==C_OK)&&(Str_RTCBATT.HStatus == C_BATT_ERR)&&((ChangeFlag&0x0f) == C_RTCBattChange_Err))
			||((SF_JudgeWarn(C_PowerBatterySign,C_BackLED)==C_OK)&&(Str_WAKEUPBATT.HStatus == C_BATT_ERR)&&((ChangeFlag&0xf0) == C_WakeupBattChange_Err)) )
		{
			V_ucBuffer[i*4+0] = Pt_DisplayStatus;
			V_ucBuffer[i*4+1] = C_BackLED|C_AlwaysDisplay;
			V_ucBuffer[i*4+2] = 0xFF;
			V_ucBuffer[i*4+3] = 0xFF;
			i++;
		}
		else if( ((SF_JudgeWarn(C_RTCBatterySign,C_BackLED)!=C_OK)||((Str_RTCBATT.HStatus != C_BATT_ERR)&&((ChangeFlag&0x0f) != C_RTCBattChange_Err)))
			&&((SF_JudgeWarn(C_PowerBatterySign,C_BackLED)!=C_OK)||((Str_WAKEUPBATT.HStatus != C_BATT_ERR)&&((ChangeFlag&0xf0) != C_WakeupBattChange_Err))) )
		{
			V_ucBuffer[i*4+0] = Pt_DisplayStatus;
			V_ucBuffer[i*4+1] = C_BackLED|C_NotDisplay;
			V_ucBuffer[i*4+2] = 0xFF;
			V_ucBuffer[i*4+3] = 0xFF;
			i++;
		}
		///*报警继电器输出*///
		if( ((SF_JudgeWarn(C_RTCBatterySign,C_WarnOutPut)==C_OK)&&(Str_RTCBATT.HStatus == C_BATT_ERR)&&((ChangeFlag&0x0f) == C_RTCBattChange_Err))
			||((SF_JudgeWarn(C_PowerBatterySign,C_WarnOutPut)==C_OK)&&(Str_WAKEUPBATT.HStatus == C_BATT_ERR)&&((ChangeFlag&0xf0) == C_WakeupBattChange_Err)) )
		{
			V_ucBuffer[i*4+0] = Pt_DisplayStatus;
			V_ucBuffer[i*4+1] = C_WarnOutPut|C_AlwaysDisplay;
			V_ucBuffer[i*4+2] = 0xFF;
			V_ucBuffer[i*4+3] = 0xFF;
			i++;
		}
		else if( ((SF_JudgeWarn(C_RTCBatterySign,C_WarnOutPut)!=C_OK)||((Str_RTCBATT.HStatus != C_BATT_ERR)&&((ChangeFlag&0x0f) != C_RTCBattChange_Err)))
			&&((SF_JudgeWarn(C_PowerBatterySign,C_WarnOutPut)!=C_OK)||((Str_WAKEUPBATT.HStatus != C_BATT_ERR)&&((ChangeFlag&0xf0) != C_WakeupBattChange_Err))) )
		{
			V_ucBuffer[i*4+0] = Pt_DisplayStatus;
			V_ucBuffer[i*4+1] = C_WarnOutPut|C_NotDisplay;
			V_ucBuffer[i*4+2] = 0xFF;
			V_ucBuffer[i*4+3] = 0xFF;
			i++;
		}
		if( i != 0 )
		{
			ADC_SendMessage(C_Msg_Display,V_ucBuffer,(Pt_DisplayStatus_Len+1)*i);
		}
	}
}
///***********************************************************************************///
///*Function：关闭ADC*///
///*Description：停止ADC转换,关闭ADC的时钟源*///
///***********************************************************************************///
void InF_ADC_OFF(void)
{
	ANAC->ADCCON = 0;
	ANAC->ADCIF |= ANAC_ADCIF_ADC_IF_SET;///*清中断标志
	RCC->PERCLKCON2 &= (~RCC_PERRCCCON2_ADCCKE_ON);///*关闭ADC时钟源
}

///***********************************************************************************///
///*Function：初始化ADC*///
///***********************************************************************************///
void SF_InitADC(void)
{
	///*使能ADC时钟源，采样频率512k*///
	RCC->PERCLKCON2 &= (~RCC_PERRCCCON2_ADCCKSEL_RCLP);
	RCC->PERCLKCON2 |= (RCC_PERRCCCON2_ADCCKSEL_RCHFDIV32|RCC_PERRCCCON2_ADCCKE_ON);
//	SF_ADC_Set(C_ADC_Iint);
	///*配置口线为模拟输入口*///
	Set_IO_RTCBatt_Analong();
	Set_IO_WakeBatt_Analong();
	Set_IO_Cap_Analong();
	ANAC->ADCINSEL = ANAC_ANATESTSEL_BUF4TST_SEL_AN8;///*选择PB3通道，3.6V
	ANAC->ADCINSEL |= ANAC_ANATESTSEL_BUF4TST_EN_ENABLE;///*输入Buff使能

	ANAC->ADCCON = 0;
	ANAC->ADCCON |= ANAC_ADCCON_ADC_VANA_EN_Voltage;///*电压测量
	ANAC->ADCTRIM = const_adc_TrimB;

	ANAC->ADCIF |= ANAC_ADCIF_ADC_IF_SET;///*清中断标志
	ANAC->ADCCON |= ANAC_ADCCON_ADC_EN_ENABLE;///*使能ADC

}
///***********************************************************************************///
///*Function：ADC温度计算*///
///***********************************************************************************///
//long32 SF_ADC_TempCalc(ulong32 ulADCData)
//{
//	long64 l64Data,l64DataADC,l64DataT;///*扩大10000倍
//	ushort16 us16DataFa;
//
//	if( const_temp_TestA == 0x1E )
//	{
//		//使用温度定标数据
//		l64DataT = const_temp_TestA*10000+(const_temp_TestB>>7)*5000;
//		l64DataADC = const_adc_Test*10000 - const_T_Offset3V*const_TmpsH;
//	}
//	else
//	{
//		//调试临时使用
//		l64DataT = 300000;
//		l64DataADC = 15000000;
//	}
//	l64Data=ulADCData*10000;
//	if( l64Data > (l64DataADC-250000) )	//高温
//	{
//		us16DataFa = const_TmpsH;
//	}
//	else
//	{
//		us16DataFa = const_TmpsL;
//	}
//	l64Data = (l64Data - l64DataADC)/us16DataFa + l64DataT;
//	l64Data=l64Data/1000;///*预留一位小数
//	return (long32)l64Data;
//}
///***********************************************************************************///
///*Function：ADC采样值计算*///
///***********************************************************************************///
ulong32 SF_ADC_VoltageCalc(ulong32 ulADCData)
{
	long64 ul64Data;///*扩大100倍

	if( (const_adc_Slope > 2000) && (const_adc_Slope < 2400) )
	{
		if(ulADCData <= 30)
		{
			ul64Data = 0;
		}
		else if(ulADCData <= 50)
		{
			ul64Data=(ulADCData-30)*5*100;
		}
		else if(ulADCData <= 150)
		{
			ul64Data = ulADCData*const_adc_Slope/10;
		}
		else if(ulADCData <= 500)
		{
			ul64Data = ulADCData*98*const_adc_Slope/1000;
		}
		else
		{
			ul64Data = ulADCData*const_adc_Slope/10+const_adc_Offset;
		}
	}
	else///*正常不存在
	{
		ul64Data = (ulADCData - 10)*2174;
		ul64Data /= 10;
	}
	if (ul64Data<0)
	{
		ul64Data=0;
	}
	else
	{
		ul64Data /= 1000;///*xxxmV，
	}
	return (ulong32)ul64Data;
}

float GetRtcRTrimVal( ulong32 Temperature_Adc )//根据adc数据查表差值
{
	float Rtcadj = 0;
	float Fk;
	uchar8 i;

	for(i=1; i<=20; i++)//温度区间判断
	{
		if(Temperature_Adc < RTC_RT.TAdc.PTAT_Value[i])
		{
			break;
		}
	}

	//补偿值计算
	if(i<21)
	{
		Fk = (float)(((float)RTC_RT.TVal.Trim_Value[i-1] - (float)RTC_RT.TVal.Trim_Value[i])/((float)RTC_RT.TAdc.PTAT_Value[i-1] - (float)RTC_RT.TAdc.PTAT_Value[i]));

		Rtcadj = Fk*(((float)Temperature_Adc - (float)RTC_RT.TAdc.PTAT_Value[i-1])) + (float)RTC_RT.TVal.Trim_Value[i-1];
	}
	return Rtcadj;
}
/***********************************************************************************
*Function：ADC温度测量及时钟调校，上电5s调用，正常有电10s调用。没电情况下83min调用1次，同时不更新数据层温度。
*通信时钟调校直接调用接口函数
***********************************************************************************/
void	InF_TempAdc_CmpAndJec(void)
{
	ulong32 Temp_Data;
	uchar8 i;
 	float T25ADC,AverADCf;
 	float Fa,Fb,T,T25,Rtcadj,TopF_Rtc_Adj;
 	ushort16 Temp16;
 	uchar8 Result;
	char8 BufC[ee_temperature_lenth+2];
	uchar8 V_ucBuffer[10];

	if(C_PowerOn!=InF_ReadPowerState() )	/*获取当前状态,低功耗状态下使能时钟*/
	{
	/*使能ADC时钟源，采样频率512k*/
		SF_ADC_Set(C_ADC_Lowpower);
	}
	Temperature_Adc = GV_ucTemp_Data[32];
	AverADCf = (float)GV_ucTemp_Data[32]/32;

	/*0 高温温度斜率微调（暂不支持）
	1 低温温度斜率微调（暂不支持）
	2 高温晶体曲线微调（高温修调二次函数系数）x*0.0001 kh
	3 低温晶体曲线微调（低温修调二次函数系数）x*0.0001 kl
	4 常温顶点调校值修正值(±1.27ppm)
	5 常温温度ADC微调
	6 常温顶点调校值L（通信调时钟误差）±327.68ppm
	7 常温顶点调校值H（通信调时钟误差）
	8 RTC补偿工作模式，0x55:测试模式，0xAA常温查表插值模式，其他：普通模式
	9 常温25+晶体曲线微调（常温25+修调二次函数系数）x*0.0002 krh
	10常温25-晶体曲线微调（常温25-修调二次函数系数）x*0.0002 krl*/
		memcpy( BufC, Tpara.Offset, ee_temperature_lenth );/*复制温度系数*/
		for( i=0; i<6; i++ ) //特殊输入转换成有符号数
		{
			Result = (unsigned char)(BufC[i]);
			if( Result&0x80 ) BufC[i] = ((~Result)|0x80)+1;
		}
		Result = (unsigned char)(BufC[9]);
		if( Result&0x80 ) BufC[9] = ((~Result)|0x80)+1;
		Result = (unsigned char)(BufC[10]);
		if( Result&0x80 ) BufC[10] = ((~Result)|0x80)+1;
		if( const_temp_TestA == 0x1E )
		{
			/*使用温度定标数据*/
#if 0		/*原来屏蔽*/
			T25ADC = (const_adc_Test+(short)BufC[5]) - (const_temp_TestA+(float)(const_temp_TestB/0x80)*0.5-const_xtl_top)*const_TmpsH;/*计算高低温曲线转折点的ADC值*/
			if( EA_OFF )
			{
				T = T + const_T_OffsetSlp;
				T25ADC = (const_adc_Test+(short)BufC[5]) - (const_temp_TestA+(float)(const_temp_TestB/0x80)*0.5-const_xtl_top)*const_TmpsH - const_T_OffsetSlp*const_TmpsH;		/*计算高低温曲线转折点的ADC值*/
			}
			else
			{
				T = T + const_T_OffsetRun;
#endif
				T25ADC = (const_adc_Test+(short)BufC[5]) - (const_temp_TestA+(float)(const_temp_TestB/0x80)*0.5-const_xtl_top)*const_TmpsH - const_T_OffsetRun*const_TmpsH;		/*计算高低温曲线转折点的ADC值*/
#if 0		/*原来屏蔽*/
			}
#endif
		}
		else
		{
			/*调试临时使用*/
			T25ADC = 1470 + (25 - const_xtl_top)*const_TmpsH;	/*调试用，后续需替换为温度定标数据*/
		}
#if 0		/*原来屏蔽*/
		if( (SleepPtatOffsetCfg == 0x55)&&(EA_OFF) )/*停电温度补偿启用3v offset*/
		{
#endif
			if( const_ptat_Offset3V <= 10 )
			{
				T25ADC -= const_ptat_Offset3V;
			}
#if 0		/*原来屏蔽*/
			else
			{
				T25ADC -= 5;
			}
		}
#endif
		T25 = const_xtl_top;
		if( const_tx_flag != 0x3cc3 )					/*通信校准时钟误差*/
		{
			TopF_Rtc_Adj = ((short16)((uchar8)BufC[6]|((uchar8)BufC[7]<<8)))/100.0;	/*缩小100倍*/
		}
		else											/*调校仪校准时钟误差*/
		{
			TopF_Rtc_Adj = const_rtc_adj_top/100.0;		/*缩小100倍*/
		}

		if( AverADCf > T25ADC )							/*高温*/
		{
 			Fa = const_TmpsH+0.05*BufC[0];
 		}
 		else
 		{
 			Fa = const_TmpsL+0.05*BufC[1];
 		}

		T = (AverADCf - T25ADC)/Fa + T25;
		uchar8 status;
		status = 0;
		if( T >= 0x00 )/*计算当前温度*/
		{
			Temp16 = (ushort16)(T*10);
		}
		else
		{
			status=0x68;
			Temp16 = (ushort16)(-T*10);
		}
		Temp_Data=Temp16;
		V_ucBuffer[9] = 4;
		PF_Ulong32ToBuffer4(&V_ucBuffer[0], &Temp_Data, V_ucBuffer[9]);
		if(0x68==status)
		{
			V_ucBuffer[1]|=0x80;
		}
		if(C_PowerOn==InF_ReadPowerState() )		/*获取当前状态,有电状态下才更新*/
		{
			InF_Write_Data(C_Msg_MeterIC,CMeter_Temp,&V_ucBuffer[0],CLMeter_Temp,C_W_SafeFlag);
		}
		/*******以上为温度测量********/
/*		TR_Proc(T);没有实际作用，纯粹记录用*/
		/*查表温度范围标志判断 0=常温，1=低温，2=高温，以下为温度时钟补偿*/
		if( T < 0 )
		{
			Result = 1;//低温查表
		}
		else if( T > 50 )
		{
			Result = 2;//高温查表
		}
		else
		{
			Result = 0;//常温查表
		}

		if( const_C_Mode != 0x55 )
		{
			RTC_RT.TempFlag = 0;
			RTC_RT.CFixTrim = TopF_Rtc_Adj;
		}
		else if( ((Tpara.RtcTMode == 0xAA)||(Tpara.RtcTMode == 0x55)) && (RTC_RT.TempFlag != Result) )/*改变后重新校验温补参数*/
		{
			RTC_RT.TempFlag = Result;

			Fill_RTC_RT_TAdc();
			Fill_RTC_RT_TVal();

			if( RTC_RT.TempFlag == 0 )//常温查表
			{
				RTC_RT.CFixTrim = TopF_Rtc_Adj;
			}
			else if( RTC_RT.TempFlag == 1 )//低温查表
			{
				Fa = const_KL +0.0001*BufC[3];
				RTC_RT.CFixTrim = TopF_Rtc_Adj + (-1.0)*Fa*(const_T_CL-const_xtl_top)*(const_T_CL-const_xtl_top);//低温查表中心温度误差计算，ppm
			}
			else if( RTC_RT.TempFlag == 2 )//高温查表
			{
				Fa = const_KH +0.0001*BufC[2];
				RTC_RT.CFixTrim = TopF_Rtc_Adj + (-1.0)*Fa*(const_T_CH-const_xtl_top)*(const_T_CH-const_xtl_top);//高温查表中心温度误差计算，ppm
			}
		}

		if( (Tpara.RtcTMode == 0xAA)||(Tpara.RtcTMode == 0x55) )//常温查表插值模式,禁止krh，krl微调功能
		{
			BufC[9] = 0;
			BufC[10] = 0;
		}
 		if( AverADCf > T25ADC )		/*高温*/
		{
			/*避免kh，kl微调对常温产生影响*/
			if(AverADCf > (T25ADC+const_KHKL_TrimRange)) Fa = const_KH +0.0001*BufC[2];
			else Fa = const_KH +0.0004*BufC[9];
			Fb = const_KH;
		}
 		else
		{
 			if(AverADCf < (T25ADC-const_KHKL_TrimRange)) Fa = const_KL +0.0001*BufC[3];
			else Fa = const_KL +0.0004*BufC[10];
			Fb = const_KL;
		}

		Rtcadj_Offset = Fa*(T-const_xtl_top)*(T-const_xtl_top);		/*顶点误差计算，ppm*/
		Rtcadj_Offset2 = Fb*(T-const_xtl_top)*(T-const_xtl_top);	/*顶点误差计算，ppm，调校用*/

		/*常温查表插值模式*/
		if( (Tpara.RtcTMode == 0xAA)&&( (Temperature_Adc>RTC_RT.TAdc.PTAT_Value[0]) && (Temperature_Adc<RTC_RT.TAdc.PTAT_Value[20]) ))//进入查表区域
		{
			Rtcadj = GetRtcRTrimVal( Temperature_Adc );
			/*调整量*调整补偿 = 调整的ppm数*/
			Rtcadj = Rtcadj*0.23842;	/*最小调整量为0.238ppm*/
			if( (const_mark404 == 0x0404)&&(RTC_Trim_Ctrl == 0x55) )
			{
				Rtcadj = Rtcadj/2.0;	/*最小调整量为0.119ppm*/
			}
			Rtcadj = Rtcadj + ((short)BufC[4])/100.0 + RTC_RT.CFixTrim;
		}
		else if( (Tpara.RtcTMode == 0x55)&&(C_OK==InF_IsInFactoryState())) /*测试模式,使用固定调校值*/
		{
			if( (const_mark404 == 0x0404)&&(RTC_Trim_Ctrl == 0x55) )
			{
				Rtcadj = ((short)BufC[4])/100.0 + RTC_RT.CFixTrim + RTC_RT.TestTrim*0.11921;
			}
			else
			{
				Rtcadj = ((short)BufC[4])/100.0 + RTC_RT.CFixTrim + RTC_RT.TestTrim*0.23842;
			}
		}
		else if( (RtcStopProcFlag == 0x55)&&(C_OK==InF_IsInFactoryState()))	/*通信校准时钟关闭补偿调顶点*/
		{
			Rtcadj = 0x00;
		}
		else if( (const_TopNoTrim == 0x55)&&(AverADCf < (T25ADC+const_TopNTRange))&&(AverADCf > (T25ADC-const_TopNTRange)) )
		{
			Rtcadj = ((short)BufC[4])/100.0+TopF_Rtc_Adj;
		}
		else
		{
			Rtcadj = ((short)BufC[4])/100.0+TopF_Rtc_Adj-Rtcadj_Offset;
		}

		if( (RTC_Trim_Ctrl == 0x55)&&(const_mark404 == 0x0404) )
		{
			Rtcadj = Rtcadj*8.388608;/*转换为调校值,0.119*/
		}
		else
		{
			Rtcadj = Rtcadj*4.194304;/*转换为调校值,0.238*/
		}

		if( Rtcadj >= 0 )
		{
			RTC->ADJUST = (ulong32)(Rtcadj+0.5);
			RTC->ADSIGN = 0x00;
		}
		else
		{
			RTC->ADJUST = (ulong32)((Rtcadj-0.5)*-1.0);
			RTC->ADSIGN = 0x01;
		}
}
/*******************************************************************************
函数原型： InF_ADC_Action_Message
功能描述： ADC转换
输入参数： P_Msg_Parameter  消息入口参数
输出参数： 无
返回参数： 无
调用位置:
备    注：
*******************************************************************************/
void InF_ADC_Action_Message(Str_Msg_Parameter *pStr_Msg_Parameter)
{
	uchar8 V_ucBuffer[20], V_ucstatus, V_ucChangeFlag = 0;
	ushort16 V_usdelaycount, V_uslen, V_usDataEncode;
	ulong32 V_ulRTC_Data, V_ulWakeUp_Data, V_ulCAP_Data;

	PF_CopyDataBytes(pStr_Msg_Parameter->Parameter, V_ucBuffer, 4);
	if( (pStr_Msg_Parameter->DerictAddr != C_Msg_BatteryVoltagleMetering) || (V_ucBuffer[0] != Pt_Dispatch_Timing) )
	{
		return;
	}

	SF_InitADC();

	V_ulRTC_Data = 0;

	for(V_usdelaycount = 0; V_usdelaycount < C_ADC_Delay; V_usdelaycount++)
	{
		InF_Delay_2us();
		if( ANAC->ADCIF & ANAC_ADCIF_ADC_IF_SET )
		{
			ANAC->ADCIF |= ANAC_ADCIF_ADC_IF_SET;			/*清中断标志*/
			V_ulRTC_Data = ANAC->ADCDATA;
			break;
		}
	}
	/*第1个转换值舍弃*/
	V_ulRTC_Data = 0;
	for(V_usdelaycount = 0; V_usdelaycount < C_ADC_Delay; V_usdelaycount++)
	{
		InF_Delay_2us();
		if( ANAC->ADCIF & ANAC_ADCIF_ADC_IF_SET )
		{
			ANAC->ADCIF |= ANAC_ADCIF_ADC_IF_SET;			/*清中断标志*/
			V_ulRTC_Data = ANAC->ADCDATA;
			break;
		}
	}

	ANAC->ADCINSEL = ANAC_ANATESTSEL_BUF4TST_SEL_AN2;		/*选择PC13通道，6V*/
	ANAC->ADCINSEL |= ANAC_ANATESTSEL_BUF4TST_EN_ENABLE;	/*输入Buff使能*/

	V_ulWakeUp_Data = 0;

	for(V_usdelaycount = 0; V_usdelaycount < C_ADC_Delay; V_usdelaycount++)
	{
		InF_Delay_2us();
		if( ANAC->ADCIF & ANAC_ADCIF_ADC_IF_SET )
		{
			ANAC->ADCIF |= ANAC_ADCIF_ADC_IF_SET;			/*清中断标志*/
			V_ulWakeUp_Data = ANAC->ADCDATA;
			break;
		}
	}
	ANAC->ADCINSEL = ANAC_ANATESTSEL_BUF4TST_SEL_AN7;		/*选择PB2通道，超级电容*/
	ANAC->ADCINSEL |= ANAC_ANATESTSEL_BUF4TST_EN_ENABLE;	/*输入Buff使能*/

	V_ulCAP_Data = 0;
	for(V_usdelaycount = 0; V_usdelaycount < C_ADC_Delay; V_usdelaycount++)
	{
		InF_Delay_2us();
		if( ANAC->ADCIF & ANAC_ADCIF_ADC_IF_SET )
		{
			ANAC->ADCIF |= ANAC_ADCIF_ADC_IF_SET;			/*清中断标志*/
			V_ulCAP_Data = ANAC->ADCDATA;
			break;
		}
	}

	/*******************更新温度值及时钟RTC调校********************/
	GV_ucTime++;

	if(GV_ucTime >= C_Tem10s)
	{
			GV_ucTime=0;

			InF_TempAdc_CmpAndJec();
	}

	InF_ADC_OFF();

	/**********************************************************/
	V_ulRTC_Data = SF_ADC_VoltageCalc(V_ulRTC_Data);
	V_ulRTC_Data = 3 * V_ulRTC_Data;
	V_ulRTC_Data >>= 1;										/*硬件电路有关*/
	V_ulRTC_Data += 37;

	if( V_ulRTC_Data < C_RTCBatt_LowerLimit )
	{
		V_ulRTC_Data = 0;
	}
	if( V_ulRTC_Data > C_RTCBatt_UpperLimit )
	{
		V_ulRTC_Data = C_RTCBatt_UpperLimit;
	}
	if( V_ulRTC_Data < C_RTCBatt_WarnLimit )
	{
		V_ucstatus = C_BATT_ERR;
	}
	else
	{
		V_ucstatus = C_BATT_OK;
	}

	V_ucBuffer[19] = 4;
	PF_Ulong32ToBuffer4(&V_ucBuffer[0], &V_ulRTC_Data, V_ucBuffer[19]);
	InF_Write_Data(C_Msg_BatteryVoltagleMetering, CCloc_Batt_Vol, &V_ucBuffer[0], CLCloc_Batt_Vol, C_W_SafeFlag);
	/**********************************************************/
	Str_RTCBATT.Timer++;
	if( V_ucstatus == C_BATT_OK )							/*当前电池状态正常*/
	{
		if( Str_RTCBATT.HStatus == C_BATT_OK )			/*历史状态正常*/
		{
			Str_RTCBATT.Timer = 0;
		}
		else
		{
			if( Str_RTCBATT.Timer >= C_BATTErr_Times )			/*历史不正常，且超过3次*/
			{
				Str_RTCBATT.HStatus = C_BATT_OK;
				/*历史状态写数据层*/
				InF_Write_Data(C_Msg_BatteryVoltagleMetering, CCloc_Batt_LowState, &Str_RTCBATT.HStatus, CLCloc_Batt_LowState, C_W_SafeFlag);
				V_ucChangeFlag |= C_RTCBattChange_Ok;			/*置电池状态有变化标志*/
				SF_RTCBattSymbol(C_BATT_OK);					/*取消电池符号*/
			}
		}
	}
	else if( V_ucstatus == C_BATT_ERR )							/*当前电池状态异常*/
	{
		if( Str_RTCBATT.HStatus == C_BATT_ERR )					/*历史状态异常*/
		{
			Str_RTCBATT.Timer = 0;
		}
		else
		{
			if( Str_RTCBATT.Timer >= C_BATTErr_Times )			/*历史正常，且超过3次*/
			{
				Str_RTCBATT.HStatus = C_BATT_ERR;
				InF_ActiveReportSetting(C_Times_RTCBatteryErr);	/*645，主动上报*/
				Inf_WriteMeterStatus8(C_RTCBatLowVolEventNo);
				/*历史状态写数据层*/
				InF_Write_Data(C_Msg_BatteryVoltagleMetering, CCloc_Batt_LowState, &Str_RTCBATT.HStatus, CLCloc_Batt_LowState, C_W_SafeFlag);
				V_ucChangeFlag |= C_RTCBattChange_Err;			/*置电池状态有变化标志*/
				SF_RTCBattSymbol(C_BATT_ERR);					/*显示电池符号*/
			}
		}
	}
	/*更新电表运行状态字1中的时钟电池故障状态标志：故障或正常；首先从数据层读，刷新后再写*/
	V_uslen = CLMeter_Work_State1;
	InF_Read_Data(CMeter_Work_State1, &V_ucBuffer[0], &V_uslen, &V_usDataEncode);
	if(Str_RTCBATT.HStatus == C_BATT_OK)
	{
		V_ucBuffer[0] &= ~C_RTCBattERR_MeterWorkState;
	}
	else
	{
		V_ucBuffer[0] |= C_RTCBattERR_MeterWorkState;
	}
	InF_Write_Data(C_Msg_Dispatch, CMeter_Work_State1, &V_ucBuffer[0], CLMeter_Work_State1, C_W_SafeFlag);

	/**********************************************************/
	V_ulWakeUp_Data = SF_ADC_VoltageCalc(V_ulWakeUp_Data);
	V_ulWakeUp_Data <<= 1;									/*硬件电路有关*/
	V_ulWakeUp_Data += 17;
	if( V_ulWakeUp_Data < C_WakeUpBatt_LowerLimit )
	{
		V_ulWakeUp_Data = 0;
	}
	if( V_ulWakeUp_Data > C_WakeUpBatt_UpperLimit )
	{
		V_ulWakeUp_Data = C_WakeUpBatt_UpperLimit;
	}
	if( V_ulWakeUp_Data < C_WakeUpBatt_WarnLimit )
	{
		V_ucstatus = C_BATT_ERR;
	}
	else
	{
		V_ucstatus = C_BATT_OK;
	}
	V_ucBuffer[19] = 4;
	PF_Ulong32ToBuffer4(&V_ucBuffer[0], &V_ulWakeUp_Data, V_ucBuffer[19]);
	InF_Write_Data(C_Msg_BatteryVoltagleMetering, CReadMeter_Batt_Vol, &V_ucBuffer[0], CLReadMeter_Batt_Vol, C_W_SafeFlag);

	/**********************************************************/
	Str_WAKEUPBATT.Timer++;
	if( V_ucstatus == C_BATT_OK )							/*当前电池状态正常*/
	{
		if( Str_WAKEUPBATT.HStatus == C_BATT_OK )			/*历史状态正常*/
		{
			Str_WAKEUPBATT.Timer = 0;
		}
		else
		{
			if( Str_WAKEUPBATT.Timer >= C_BATTErr_Times )	/*历史不正常，且超过3次*/
			{
				/*状态发生变化,将状态写数据层,进行报警相关处理*/
				Str_WAKEUPBATT.HStatus = C_BATT_OK;
				InF_Write_Data(C_Msg_BatteryVoltagleMetering, CReadMeter_Batt_LowState, &Str_WAKEUPBATT.HStatus, CLReadMeter_Batt_LowState, C_W_SafeFlag);
				V_ucChangeFlag |= C_WakeupBattChange_Ok;		/*置电池状态有变化标志*/
				SF_WakeUpBattSymbol(C_BATT_OK);				/*取消电池符号*/
			}
		}
	}
	else if( V_ucstatus == C_BATT_ERR )						/*当前电池状态异常*/
	{
		if( Str_WAKEUPBATT.HStatus == C_BATT_ERR )			/*历史状态异常*/
		{
			Str_WAKEUPBATT.Timer = 0;
		}
		else
		{
			if( Str_WAKEUPBATT.Timer >= C_BATTErr_Times )   /*历史正常，且超过3次*/
			{
				/*状态发生变化,将状态写数据层,进行报警相关处理和主动上报*/
				Str_WAKEUPBATT.HStatus = C_BATT_ERR;
				InF_ActiveReportSetting(C_Times_PowerBatteryErr);	/*645，主动上报*/

				Inf_WriteMeterStatus8(C_PowerBatLowVolEventNo);
				InF_Write_Data(C_Msg_BatteryVoltagleMetering, CReadMeter_Batt_LowState, &Str_WAKEUPBATT.HStatus, CLReadMeter_Batt_LowState, C_W_SafeFlag);
				V_ucChangeFlag |= C_WakeupBattChange_Err;	    /*置电池状态有变化标志*/
				SF_WakeUpBattSymbol(C_BATT_ERR);			/*显示电池符号*/
			}
		}
	}
	/*更新电表运行状态字1中的唤醒电池故障状态标志：故障或正常；首先从数据层读，刷新后再写*/
	V_uslen = CLMeter_Work_State1;
	InF_Read_Data(CMeter_Work_State1, &V_ucBuffer[0], &V_uslen, &V_usDataEncode);
	if(Str_WAKEUPBATT.HStatus == C_BATT_OK)
	{
		V_ucBuffer[0] &= ~C_WakeUpBattERR_MeterWorkState;
	}
	else
	{
		V_ucBuffer[0] |= C_WakeUpBattERR_MeterWorkState;
	}
	InF_Write_Data(C_Msg_Dispatch, CMeter_Work_State1, &V_ucBuffer[0], CLMeter_Work_State1, C_W_SafeFlag);
	///**********************************************************/
	SF_BattWarn(V_ucChangeFlag);		/*根据电池变化标志,对电池欠压进行报警处理*/
	/**********************************************************/
	V_ulCAP_Data = SF_ADC_VoltageCalc(V_ulCAP_Data);
	V_ulCAP_Data <<= 1;					/*硬件电路有关*/
	V_ulCAP_Data += 8;

	if(V_ulCAP_Data <= C_Cap_LowerLimit)
	{
		V_ulCAP_Data = 0;
	}
	V_ucBuffer[19] = 4;
	PF_Ulong32ToBuffer4(&V_ucBuffer[0], &V_ulCAP_Data, V_ucBuffer[19]);
	InF_Write_Data(C_Msg_BatteryVoltagleMetering, CCap_Vol, &V_ucBuffer[0], CLCap_Vol, C_W_SafeFlag);
}
///************************************************************************///
///*函数原型:void InF_ExecuteClr_RTCBatt(void)
///*函数功能:电表总清时，对于时钟电池故障标志的处理
///*输入参数:
///*输出参数：
///*返回参数:无
///*调用时机：
///*备注:
///*功能说明：
///************************************************************************///
void InF_ExecuteClr_RTCBatt(void)
{
	uchar8 V_ucBuffer[16];
	ushort16 V_len, V_usDataEncode;

	Str_RTCBATT.HStatus = C_BATT_OK;
	Str_RTCBATT.Timer = 0;

	///*总清后将历史状态(电池正常)写数据层*///
	InF_Write_Data(C_Msg_BatteryVoltagleMetering,CCloc_Batt_LowState,&Str_RTCBATT.HStatus,CLCloc_Batt_LowState,C_W_SafeFlag);

	///*更新数据层时钟电池故障状态标志：故障或正常；首先从数据层读，刷新后再写*///
	V_len = CLMeter_Work_State1;
	InF_Read_Data(CMeter_Work_State1,&V_ucBuffer[0],&V_len, &V_usDataEncode);

	V_ucBuffer[0] &= ~C_RTCBattERR_MeterWorkState;

	InF_Write_Data(C_Msg_Dispatch,CMeter_Work_State1,&V_ucBuffer[0],CLMeter_Work_State1,C_W_SafeFlag);
	///*取消时钟电池报警:不管前面是否报警,直接取消///
		///*时钟电池不显示*///
	V_ucBuffer[0] = Pt_DisplayStatus;
	V_ucBuffer[1] = C_RTCBatterySign|C_NotDisplay;
	V_ucBuffer[2] = 0xFF;
	V_ucBuffer[3] = 0xFF;
	///*小铃铛不闪烁*///
	V_ucBuffer[4] = Pt_DisplayStatus;
	V_ucBuffer[5] = C_AlarmSign|C_NotDisplay;
	V_ucBuffer[6] = 0xFF;
	V_ucBuffer[7] = 0xFF;
	///*背光不点亮*///
	V_ucBuffer[8] = Pt_DisplayStatus;
	V_ucBuffer[9] = C_BackLED|C_NotDisplay;
	V_ucBuffer[10] = 0xFF;
	V_ucBuffer[11] = 0xFF;
	///*报警继电器不输出*///
	V_ucBuffer[12] = Pt_DisplayStatus;
	V_ucBuffer[13] = C_WarnOutPut|C_NotDisplay;
	V_ucBuffer[14] = 0xFF;
	V_ucBuffer[15] = 0xFF;
	ADC_SendMessage(C_Msg_Display,V_ucBuffer,(Pt_DisplayStatus_Len+1)*4);
}


///************************************************************************///
///*函数原型:void InF_ExecuteClr_WakeUpBatt(void)
///*函数功能:电表总清时，对于停电抄表电池故障标志的处理
///*输入参数:
///*输出参数：
///*返回参数:无
///*调用时机：
///*备注:
///*功能说明：
///************************************************************************///
void InF_ExecuteClr_WakeUpBatt(void)
{
	uchar8 V_ucBuffer[16];
	ushort16 V_len, V_usDataEncode;

	Str_WAKEUPBATT.HStatus = C_BATT_OK;
	Str_WAKEUPBATT.Timer = 0;

	///*总清后将历史状态(电池正常)写数据层*///
	InF_Write_Data(C_Msg_BatteryVoltagleMetering,CReadMeter_Batt_LowState,&Str_WAKEUPBATT.HStatus,CLReadMeter_Batt_LowState,C_W_SafeFlag);
	///*更新数据层停电抄表电池故障状态标志：故障或正常；首先从数据层读，刷新后再写*///
	V_len = CLMeter_Work_State1;
	InF_Read_Data(CMeter_Work_State1, &V_ucBuffer[0], &V_len, &V_usDataEncode);

	V_ucBuffer[0] &= ~C_WakeUpBattERR_MeterWorkState;

	InF_Write_Data(C_Msg_Dispatch,CMeter_Work_State1,&V_ucBuffer[0],CLMeter_Work_State1,C_W_SafeFlag);
	///*取消唤醒电池报警:不管前面是否报警,直接取消///
	///*唤醒电池不显示*///
	V_ucBuffer[0] = Pt_DisplayStatus;
	V_ucBuffer[1] = C_PowerBatterySign|C_NotDisplay;
	V_ucBuffer[2] = 0xFF;
	V_ucBuffer[3] = 0xFF;
	///*小铃铛不闪烁*///
	V_ucBuffer[4] = Pt_DisplayStatus;
	V_ucBuffer[5] = C_AlarmSign|C_NotDisplay;
	V_ucBuffer[6] = 0xFF;
	V_ucBuffer[7] = 0xFF;
	///*背光不点亮*///
	V_ucBuffer[8] = Pt_DisplayStatus;
	V_ucBuffer[9] = C_BackLED|C_NotDisplay;
	V_ucBuffer[10] = 0xFF;
	V_ucBuffer[11] = 0xFF;
	///*报警继电器不输出*///
	V_ucBuffer[12] = Pt_DisplayStatus;
	V_ucBuffer[13] = C_WarnOutPut|C_NotDisplay;
	V_ucBuffer[14] = 0xFF;
	V_ucBuffer[15] = 0xFF;
	ADC_SendMessage(C_Msg_Display,V_ucBuffer,(Pt_DisplayStatus_Len+1)*4);
}

///************************************************************************///
///*函数功能:上电时，从数据层读出电池历史状态,并赋电表运行状态字中的电池欠压状态/报警
///*输入参数:无
///*输出参数:电池历史状态/电表运行状态字1/报警
///*返回参数:无
///*调用时机：
///************************************************************************///
void InF_InitBatt(void)
{
    uchar8 V_ucBuffer[5];
    ushort16 V_Len, V_usDataEncode;

    ///*两个滑差定时器清零*///
	Str_RTCBATT.Timer = 0;
	Str_WAKEUPBATT.Timer = 0;

	///*从数据层读出电池的历史状态*///
	V_Len = CLCloc_Batt_LowState;
	if( InF_Read_Data(CCloc_Batt_LowState, &Str_RTCBATT.HStatus, &V_Len, &V_usDataEncode) != C_OK )
	{
		Str_RTCBATT.HStatus = C_BATT_OK;
	}
	V_Len = CLReadMeter_Batt_LowState;
	if( InF_Read_Data(CReadMeter_Batt_LowState, &Str_WAKEUPBATT.HStatus, &V_Len, &V_usDataEncode) != C_OK )
	{
		Str_WAKEUPBATT.HStatus = C_BATT_OK;
	}
	SF_RTCBattSymbol(Str_RTCBATT.HStatus);		///*显示两个电池的符号*///
	SF_WakeUpBattSymbol(Str_WAKEUPBATT.HStatus);
	SF_BattWarn(C_BattChange);	///*上电初始化,默认为电池状态有变化*///
	/*上面程序的bug:如果停电前电池欠压,但上电前装上电池,
	此时电池符号及背光会先显示,3s后(滑差时间)再灭,
	因为有上电全显,所以此bug不明显,可以忽略;
	但是如果报警继电器输出使能时,报警继电器会导通后再断开,这一点暂不管*/

	///**********************************************************///
	///*根据历史状态刷新数据层的电表运行状态字*///
	V_Len = CLMeter_Work_State1;
	InF_Read_Data(CMeter_Work_State1, &V_ucBuffer[0], &V_Len, &V_usDataEncode);
	if( Str_RTCBATT.HStatus == C_BATT_OK )
	{
		V_ucBuffer[0] &= ~C_RTCBattERR_MeterWorkState;
	}
	else
	{
		V_ucBuffer[0] |= C_RTCBattERR_MeterWorkState;
	}
	if( Str_WAKEUPBATT.HStatus == C_BATT_OK )
	{
		V_ucBuffer[0] &= ~C_WakeUpBattERR_MeterWorkState;
	}
	else
	{
		V_ucBuffer[0] |= C_WakeUpBattERR_MeterWorkState;
	}
	InF_Write_Data(C_Msg_Dispatch, CMeter_Work_State1, &V_ucBuffer[0], CLMeter_Work_State1, C_W_SafeFlag);
	///*复旦微RTC新增
	Temperature_Adc=0;
	GV_ucTime=6;///*上电初始化为6s，10s更新温度
	RTC_RT.TempFlag = 0xff;//更新查表数据


	SF_ADC_Set(C_ADC_Iint);
}
///************************************************************************///
///*函数功能:ADC配置函数
///*输入参数:V_ucFlag：C_ADC_Iint初始化标志；C_ADC_CmpAndJecADC温度测量时钟调校调用
///*输出参数:V_flData:采样平均值
///*返回参数:无
///*调用时机：上电初始化，时钟调校
///************************************************************************///
void SF_ADC_Set(uchar8 V_ucFlag)
{
	ulong32 Temp_Data;
	ulong64 V_ulResult;
 	ushort16 v_delaycount;
 	uchar8 i;
	//if(C_PowerOn!=InF_ReadPowerState())///*获取当前状态,低功耗状态下使能时钟*///
	//{
	///*使能ADC时钟源，采样频率512k*///
		RCC->PERCLKCON2 &= (~RCC_PERRCCCON2_ADCCKSEL_RCLP);
		RCC->PERCLKCON2 |= (RCC_PERRCCCON2_ADCCKSEL_RCHFDIV32|RCC_PERRCCCON2_ADCCKE_ON);
	//}
	ANAC->ADCCON = 0;
	ANAC->ADCCON |= ANAC_ADCCON_ADC_VANA_EN_Temp;///*温度测量
	ANAC->ADCTRIM = const_adc_TrimT;
	ANAC->ADCIF |= ANAC_ADCIF_ADC_IF_SET;///*清中断标志
	ANAC->ADCCON |= ANAC_ADCCON_ADC_EN_ENABLE;///*使能ADC	switch(V_ucFlag)

	Temp_Data = 0;
	for(v_delaycount=0;v_delaycount<C_ADC_Delay;v_delaycount++)
	{
		InF_Delay_2us();
		if( ANAC->ADCIF & ANAC_ADCIF_ADC_IF_SET )
		{
			ANAC->ADCIF |= ANAC_ADCIF_ADC_IF_SET;///*清中断标志
			Temp_Data = ANAC->ADCDATA&0x000007FF;
			break;
		}
	}

	switch(V_ucFlag)
	{
		case C_ADC_Iint:
				///*第1个转换值舍弃
				//0x640模式采样初始化
				Temp_Data = 0;
				for(v_delaycount=0;v_delaycount<C_ADC_Delay;v_delaycount++)
				{
					InF_Delay_2us();
					if( ANAC->ADCIF & ANAC_ADCIF_ADC_IF_SET )
					{
						ANAC->ADCIF |= ANAC_ADCIF_ADC_IF_SET;///*清中断标志
						Temp_Data = ANAC->ADCDATA&0x000007FF;
						break;
					}
				}
				for(i=0; i<32; i++)
				{
					GV_ucTemp_Data[i] = Temp_Data;
				}
				GV_ucTemp_Data[32] = Temp_Data * 32;
				//GV_ucGetADC_Flag = C_GetADC_Off;
			break;
		case C_ADC_CmpAndJec:
				for(i=0; i<31; i++)
				{
					GV_ucTemp_Data[i] = GV_ucTemp_Data[i+1];
				}
				GV_ucTemp_Data[31] = Temp_Data;
				V_ulResult = 0;
				for(i=0;i<32;i++)
				{
					V_ulResult += GV_ucTemp_Data[i];
				}
				GV_ucTemp_Data[32] = V_ulResult;
			break;
		case C_ADC_Lowpower:
				///*第1个转换值舍弃
				Temp_Data = 0;
				for(v_delaycount=0;v_delaycount<C_ADC_Delay;v_delaycount++)
				{
					InF_Delay_2us();
					if( ANAC->ADCIF & ANAC_ADCIF_ADC_IF_SET )
					{
						ANAC->ADCIF |= ANAC_ADCIF_ADC_IF_SET;///*清中断标志
						Temp_Data = ANAC->ADCDATA&0x000007FF;
						break;
					}
				}
				GV_ucTemp_Data[32] = Temp_Data*32;
			break;
		default:
			break;
	}
	return;

}
