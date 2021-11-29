/***************************************************************************************
Copyright:	ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:	Dispatch.c
Version:	V1
Date:		2014-3-12
Description:调度处理文件
Function List:
***************************************************************************************
History1:第1次修改
内容1.	Date:
		Author:
		Modification:
		*********************************************
内容2.	Date:
		Author:
		Modification:
		*******************************************************************************
History2:第2次修改
内容1.	Date:
		Author:
		Modification:
		*********************************************
内容2.	Date:
		Author:
		Modification:
***************************************************************************************/

#include "Dispatch.h"
#include "Public.h"

Str_Msg_Parameter SStr_Msg_Parameter;	/*定义全局的消息结构体，用于存放调度读取的消息参数信息*/

/********************************************************************************
Function:void Dispatch_SendMessage(uchar8 MsgDerictAddr,uchar8 *P_Parameter,uchar8 ParameterLen)
Description:主调度发消息给其他模块
Input:	*P_Parameter:消息中的参数域首地址
		ParameterLen:参数域长度
		DerictAddrMsg:目的地址
Output:无
Calls:
Called By:主调度发消息时调用
Influence:调用的地方将源消息号、目的消息号、数据域都整理好后调用该函数
********************************************************************************/
void Dispatch_SendMessage(uchar8 MsgDerictAddr, uchar8 *P_Parameter, uchar8 ParameterLen)
{
	Str_Msg_Parameter	Str_Message;
	Str_Message.SourceAddr = C_Msg_Dispatch;	/*源地址必然是主调度*/
	Str_Message.DerictAddr = MsgDerictAddr;
	Str_Message.Parameter = P_Parameter;
	Str_Message.Length = ParameterLen;
	InF_WriteMessege(&Str_Message);
}

/********************************************************************************
Function:读取两个队列中的消息
Description:1.首先从第1队列中读取消息,如果有消息,则将消息数据送入全局消息缓冲区,并返回C_OK
			2.如果第1队列中没有消息,则读取第2队列
			3.如果第2队列有消息,则将消息数据送入全局消息缓冲区,并返回C_OK
			4.如果第2队列也没有消息,则返回C_Error
Input:
Output:
Calls:
Called By:
Influence:
********************************************************************************/
uchar8 Dispatch_FetchMessage(void)
{
	if(InF_ReadMessegeDerictAddr(&SStr_Msg_Parameter,C_First_Squeue) == C_OK)
	{
		return C_OK;
	}
	if(InF_ReadMessegeDerictAddr(&SStr_Msg_Parameter,C_Second_Squeue) == C_OK)
	{
		return C_OK;
	}
	else
	{
		return C_Error;
	}
}

/********************************************************************
Function:void InF_Dealwith_FirstSqueue(void)
Description:读取第1/2消息队列中消息，并调用相应处理函数进行处理
Input:no
Output:no
Return:有消息处理,返回C_OK;无消息处理,返回C_Error
Calls:读取消息队列并根据消息号进行相应的处理
Called By:main
Influence:
Tips:
Others:
********************************************************************/
uchar8 InF_Dealwith_MessageSqueue(void)
{
	if(Dispatch_FetchMessage() != C_OK)
	{
		return C_Error;
	}
	/*从InF_ReadPowerState90获取的状态有：上电、有电、掉电、低功耗这4种情况
	本次获取的消息，不管出于4种状态中哪一种，都需要调度的消息*/
	switch(SStr_Msg_Parameter.DerictAddr)
	{
		/**********************************/
		case (C_Msg_Communication):			/*通信接口消息*/
		{	/*通信有2种消息，1种为中断触发解析消息，中断置标志，外部直接调用解析函数。
			1种为500ms定时消息，依然采用消息处理方式*/
			Comm_ParseMessage(&SStr_Msg_Parameter);
			return C_OK;									/*本函数一次执行一个消息，所以采用return，以下同*/
		}
		/**********************************/
		case (C_Msg_Dispatch):
		{
			Msg_ExcuteRTC_Message(&SStr_Msg_Parameter);		/*读取外部硬件时钟*/
			return C_OK;
		}
		/**********************************/
		case (C_Msg_Display):								/*显示消息*/
		{
			InF_Display_Message(&SStr_Msg_Parameter);
			if( C_PowerOff == InF_ReadPowerState() )		/*判断是否停电:即停电唤醒*/
			{	/*停电唤醒时需要处理的事情:*/
				/*将电表运行状态字3中的供电方式写为“电池供电”*/
				SF_WritePowerMode_PowerOff();
				SF_KeyLock();								/*按键锁死处理*/
			}
			return C_OK;
		}
		/**********************************/
		default:
		{
			break;
		}
	}
	/*这里判断没有电情况下，不执行的消息*/
	if( C_PowerOff != InF_ReadPowerState() )
	{
		switch(SStr_Msg_Parameter.DerictAddr)
		{
			/**********************************/
			case (C_Msg_PowerNetworkMonitoring):	/*电网检测类事件记录判断消息*/
			{
				InF_Event_Message(&SStr_Msg_Parameter);
				return C_OK;
			}
			/**********************************/
			case (C_Msg_EnergyMetering):			/*电能计量消息*/
			{
				InF_EnergyMetering_Message(&SStr_Msg_Parameter);
				return C_OK;
			}
			/**********************************/
			case (C_Msg_DemandMetering):			/*需量计量消息*/
			{
				InF_DemandMetering_Message(&SStr_Msg_Parameter);
				return C_OK;
			}
			/**********************************/
			case (C_Msg_SettleAccounts):			/*结算消息*/
			{
				Msg_SettleAccounts(&SStr_Msg_Parameter);
				return C_OK;
			}
			/**********************************/
			case (C_Msg_Freeze):					/*冻结消息*/
			{
				Msg_Freeze(&SStr_Msg_Parameter);
				return C_OK;
			}
#if 0
			/**********************************/
			case (C_Msg_LoadProfile):				/*负荷记录消息*/
			{
				Msg_LoadProfile(&SStr_Msg_Parameter);
				return C_OK;
			}
#endif
			/**********************************/
			case (C_Msg_Deal_RelayStatus):			/*继电器功能消息*/
			{
				Msg_Deal_RelayStatus(&SStr_Msg_Parameter);
				return C_OK;
			}
			/**********************************/
			case (C_Msg_Deal_MultiRates):			/*费率判断消息*/
			{
				InF_MultiRates_ParseMessage(&SStr_Msg_Parameter);
				return C_OK;
			}
			/**********************************/
			case (C_Msg_BatteryVoltagleMetering):	/*电池电压测量消息*/
			{
				InF_ADC_Action_Message(&SStr_Msg_Parameter);
				return C_OK;
			}
			/**********************************/
			case (C_Msg_VoltageQualifiedRateMetering):	/*电压合格率检测*/
			{
				InF_VoltageQR_ParseMessage(&SStr_Msg_Parameter);
				return C_OK;
			}
			/**********************************/
			case (C_Msg_MeterIC):						/*计量消息模块*/
			{
				InF_MeterIC_ParseMessage(&SStr_Msg_Parameter);
				return C_OK;
			}
			/**********************************/
			case (C_Msg_Card):							/*卡处理消息模块*/
			{
				InF_Card_Message(&SStr_Msg_Parameter);
				return C_OK;
			}
			/**********************************/
			case (C_Msg_BroadcastAddress):				/*以广播的形式发布消息*/
			{
				InF_DispatchClr_Message(&SStr_Msg_Parameter);
				InF_Event_Message(&SStr_Msg_Parameter);
				InF_EnergyMetering_Message(&SStr_Msg_Parameter);
				InF_DemandMetering_Message(&SStr_Msg_Parameter);
				Msg_SettleAccounts(&SStr_Msg_Parameter);
				Msg_Freeze(&SStr_Msg_Parameter);
				//Msg_LoadProfile(&SStr_Msg_Parameter);
				Msg_Deal_RelayStatus(&SStr_Msg_Parameter);
				InF_MultiRates_ParseMessage(&SStr_Msg_Parameter);
				InF_ADC_Action_Message(&SStr_Msg_Parameter);
				InF_VoltageQR_ParseMessage(&SStr_Msg_Parameter);
				InF_MeterIC_ParseMessage(&SStr_Msg_Parameter);
				return C_OK;
			}
			/**********************************/
			case (C_Msg_Esam):										/*ESAM模块消息*/
			{
				EsamPowerOnRest_Message(&SStr_Msg_Parameter);
				return C_OK;
			}
			/**********************************/
			case (C_Msg_DataProcess):
			{
				Data_CruiseCheck_Message(&SStr_Msg_Parameter);		/*数据层巡航程序*/
				return C_OK;
			}
			/**********************************/
			case (C_Msg_DataProcess_External):
			{
				DataProcess_External_Message(&SStr_Msg_Parameter);	/*数据层巡航程序*/
				return C_OK;
			}
			/**********************************/
			case (C_Msg_CalibrateRC):
			{
				Msg_CalibrateRC(&SStr_Msg_Parameter);				/*校准RC振荡*/
				return C_OK;
			}
			/**********************************/
			default:
			{
				break;
			}
		}
	}
	/*仅在低功耗下运行的消息查表*/
	if( C_PowerOff == InF_ReadPowerState() )	/*全失压消息,有电的时候没有这个消息*/
	{
		if(SStr_Msg_Parameter.DerictAddr == C_Msg_AllLossVoltage)
		{
			/*停电唤醒后的开合盖事件记录*/
			Inf_LowpowerOpenCoverState(C_OpenTerminalCoverEventNo);
			Inf_LowpowerOpenCoverState(C_OpenMeterCoverEventNo);
			/*停电唤醒后的全失压记录*/
			Msg_AllLoseVoltage(&SStr_Msg_Parameter);
		}
	}

	return C_OK;

}

/************************************************************************
函数原型:void InF_Dispatch_ReadRtcToDataProcess(uchar8 powerflag)
函数功能:从外部RTC读取时钟并刷新数据层时钟（7字节）
输入参数:无
输出参数:秒变化消息、分钟变化消息和刷新数据层时间,并做时钟故障报警处理
返回参数:无
调用时机：
备注:
************************************************************************/
void InF_Dispatch_ReadRtcToDataProcess(uchar8 powerflag)
{
	uchar8 V_ucRTCBuffer_BCD[C_RTCLen] = {0};			/*用于存放从RTC读取的7字节时间,格式为YYMMDDWWHHMMSS*/
	uchar8 V_ucRTCBuffer_Hex[CLDate_Time] = {0};		/*用于RTC格式转换后的时间,格式为Data_Time_s*/
	uchar8 V_ucLastTimeBuffer[CLDate_Time] = {0};		/*用于存放从数据层读取的7字节时间，格式为Data_Time_s*/
	ushort16 V_usDataLength = CLDate_Time, V_usDataEncode = 0;
	uchar8 V_ucBuffer[10] = {0}, V_ucRTCState = C_Error, V_ucReturn = C_Error;

	/*****************************************************/
	V_ucRTCState = InF_ReadRTC(V_ucRTCBuffer_BCD,C_RTCLen);		/*从RTC读日期时间，格式为YYMMDDWWHHMMSS*/
	if( ( C_OK == V_ucRTCState )
		&& ( InF_Read_Data( CDate_Time, V_ucLastTimeBuffer, &V_usDataLength, &V_usDataEncode) == C_OK ) )
	{
		/*时钟故障判断,格式为Data_Time_s*/
		V_ucReturn = SF_RTCErrJudgeAndDeal(V_ucLastTimeBuffer);

		/*将RTC提供的YYMMDDWWHHMMSS转换为698格式的Data_Time_s*/
		PF_Data_Week_Time_BCDtoData_Time_s_HEX(V_ucRTCBuffer_BCD, V_ucRTCBuffer_Hex);

		/*只有读取成功的情况下，将从RTC读出的时间写数据层*/
		InF_Write_Data(C_Msg_Dispatch,CDate_Time,V_ucRTCBuffer_Hex,CLDate_Time,C_W_SafeFlag);

		if( powerflag != C_PowerOn )	/*在上电初始化期间读取时钟不发消息*/
		{
			if(V_ucReturn == C_RTC_ERR_BackTime)
			{
				/*如果铁电中的时间和数据层的时间都出错，用RTC时间更新备份时间 */
				InF_Write_Data(C_Msg_Dispatch, CBackTime_OneSec, V_ucRTCBuffer_Hex, CLBackTime_OneSec, C_W_SafeFlag);
			}
			return;
		}
		/*RTC时间更新备份时间*/
		InF_Write_Data(C_Msg_Dispatch, CBackTime_OneSec, V_ucRTCBuffer_Hex, CLBackTime_OneSec, C_W_SafeFlag);

		/*****************************************************
		20140923:事件记录累计时间,在事件00s结束写恢复记录,会少计1min的累计时间
		所以将分钟变化和秒变化进行调整,先分钟再秒
		这个调整经过事件记录模块和继电器模块的确认,没有其他影响*
		*****************************************************/
		/*发分钟变化消息*/
		/*日电压合格率是在日冻结时清零，原来分钟消息是在日消息后面*/
		/*这样日冻结清零后再走电压合格率函数会立即产生1min的数据*/
		/*所以将电压合格率分钟消息单独提前，先走电压合格率流程，再走日冻结清零*/
		if( V_ucLastTimeBuffer[C_Min_698] != V_ucRTCBuffer_Hex[C_Min_698] )
		{
			V_ucBuffer[0] = Pt_Dispatch_Timing;
			V_ucBuffer[1] = C_SystemMinChange;
			if( SF_Shut_RealTimeData() == C_OK )
			{	/*上电后因为电压等实时量为0,电压合格率可能会有影响,因此进行3s的闭锁*/
				/*如果因为闭锁的原因丢掉一次消息,闭锁时间到后不会补消息*/
				/*电压合格率模块*/
				Dispatch_SendMessage(C_Msg_VoltageQualifiedRateMetering,V_ucBuffer,Pt_Dispatch_Timing_Len+1);
			}
		}
		/*发月变化消息*/
		/*为了月末最后一分钟能记录到月冻结中，调整月冻结到电压合格率消息之后*/
		/*自然跨月时，在月冻结之后发月变化消息清零月电压合格率*/
		if( V_ucLastTimeBuffer[C_Month_698] != V_ucRTCBuffer_Hex[C_Month_698] )
		{
			V_ucBuffer[0] = Pt_Dispatch_Timing;
			V_ucBuffer[1] = C_SystemMonthChange;
			PF_CopyDataBytes(&V_ucRTCBuffer_Hex[C_Sec_698], &V_ucBuffer[2], CLDate_Time);	/*增加当前时间作为参数消息*/

			/*冻结模块*/
			Dispatch_SendMessage(C_Msg_Freeze,V_ucBuffer,Pt_Dispatch_Timing_Freeze_Len+1);
			if( SF_Shut_RealTimeData() == C_OK )		/*为了月末最后一分钟能记录到月冻结中，调整月冻结到电压合格率消息之后；自然跨月时，在月冻结之后发月变化消息清零月电压合格率*/
			{	/*上电后因为电压等实时量为0,电压合格率可能会有影响,因此进行3s的闭锁*/
				/*如果因为闭锁的原因丢掉一次消息,闭锁时间到后不会补消息*/
				/*电压合格率模块*/
				Dispatch_SendMessage(C_Msg_VoltageQualifiedRateMetering,V_ucBuffer,Pt_Dispatch_Timing_Len+1);
			}
		}

		/*发小时变化消息*/
		if( V_ucLastTimeBuffer[C_Hour_698] != V_ucRTCBuffer_Hex[C_Hour_698] )
		{
			V_ucBuffer[0] = Pt_Dispatch_Timing;
			V_ucBuffer[1] = C_SystemHourChange;
			PF_CopyDataBytes(&V_ucRTCBuffer_Hex[C_Sec_698], &V_ucBuffer[2], CLDate_Time);	/*增加当前时间作为参数消息*/
			/*冻结模块*/
			Dispatch_SendMessage(C_Msg_Freeze,V_ucBuffer,Pt_Dispatch_Timing_Freeze_Len+1);
		}

		/*发日变化消息*/
		if( V_ucLastTimeBuffer[C_Day_698] != V_ucRTCBuffer_Hex[C_Day_698] )
		{
			V_ucBuffer[0] = Pt_Dispatch_Timing;
			V_ucBuffer[1] = C_SystemDateChange;
			PF_CopyDataBytes(&V_ucRTCBuffer_Hex[C_Sec_698], &V_ucBuffer[2], CLDate_Time);	/*增加当前时间作为参数消息*/
			Dispatch_SendMessage(C_Msg_Freeze,V_ucBuffer,Pt_Dispatch_Timing_Freeze_Len+1);
		}

		/*发分钟变化消息*/
		if( V_ucLastTimeBuffer[C_Min_698] != V_ucRTCBuffer_Hex[C_Min_698] )
		{
			V_ucBuffer[0] = Pt_Dispatch_Timing;
			V_ucBuffer[1] = C_SystemMinChange;
			PF_CopyDataBytes(&V_ucRTCBuffer_Hex[C_Sec_698], &V_ucBuffer[2], CLDate_Time);	/*增加当前时间作为参数消息*/
			/*zlj新增，在需量模块前面先发消息给瞬时量模块，完成1min平均功率写数据层*/
			Dispatch_SendMessage(C_Msg_MeterIC, V_ucBuffer, Pt_Dispatch_Timing_Len+1);
			/*20141020:需量和费率模块调整顺序,因为在约定冻结时当前1min的需量没有冻结进去*/
			/*约定冻结是在费率模块中直接调冻结的接口函数的*/
			/*需量处理模块*/
			Dispatch_SendMessage(C_Msg_DemandMetering,V_ucBuffer,Pt_Dispatch_Timing_Len+1);
			/*费率判断模块*/
			Dispatch_SendMessage(C_Msg_Deal_MultiRates,V_ucBuffer,Pt_Dispatch_Timing_Len+1);
			/*冻结模块*/
			Dispatch_SendMessage(C_Msg_Freeze,V_ucBuffer,Pt_Dispatch_Timing_Freeze_Len+1);
			/*事件记录模块*/
			Dispatch_SendMessage(C_Msg_PowerNetworkMonitoring,V_ucBuffer,Pt_Dispatch_Timing_Len+1);
			/*结算日模块*/
			Dispatch_SendMessage(C_Msg_SettleAccounts,V_ucBuffer,Pt_Dispatch_Timing_Freeze_Len+1);
			/*通信模块*/
			Dispatch_SendMessage(C_Msg_Communication,V_ucBuffer,Pt_Dispatch_Timing_Len+1);
		}

		/*发秒变化消息*/
		if( V_ucLastTimeBuffer[C_Sec_698] != V_ucRTCBuffer_Hex[C_Sec_698] )
		{
			V_ucBuffer[0] = Pt_Dispatch_Timing;
			V_ucBuffer[1] = C_SystemSecondChange;

			if( SF_Shut_RealTimeData() == C_OK )
			{	/*上电后因为电压等实时量为0,对事件记录可能会有影响,因此进行3s的闭锁*/
				/*事件记录模块*/
				Dispatch_SendMessage(C_Msg_PowerNetworkMonitoring,V_ucBuffer,Pt_Dispatch_Timing_Len+1);
			}

			/*继电器处理模块*/
			Dispatch_SendMessage(C_Msg_Deal_RelayStatus,V_ucBuffer,Pt_Dispatch_Timing_Len+1);

			Dispatch_SendMessage(C_Msg_Freeze,V_ucBuffer,Pt_Dispatch_Timing_Len+1);

			Dispatch_SendMessage(C_Msg_Communication,V_ucBuffer,Pt_Dispatch_Timing_Len+1);
		}
	}
	else
	{
		V_ucReturn = SF_RTCErrJudgeAndDeal(V_ucLastTimeBuffer);

		if( (C_OK != V_ucRTCState) )
		{
			/*将从数据层读取的日期时间Data_Time_s转换为YYMMDDWWHHMMSS*/
			PF_Data_Time_s_HEXtoData_Week_Time_BCD(V_ucLastTimeBuffer, V_ucRTCBuffer_BCD);
			InF_WriteRTC(V_ucRTCBuffer_BCD, CLDate_Week_Time);

			InF_Write_Data(C_Msg_Dispatch, CEnter_LowPower_Time, V_ucLastTimeBuffer, CLEnter_LowPower_Time, C_W_SafeFlag);
			InF_Write_Data(C_Msg_Dispatch, CExit_LowPower_Time, V_ucLastTimeBuffer, CLExit_LowPower_Time, C_W_SafeFlag);
		}

		if(powerflag != C_PowerOn)
		{
			InF_Write_Data(C_Msg_Dispatch, CDate_Time, V_ucLastTimeBuffer, CLDate_Time, C_W_SafeFlag);
		}
	}
}

/*************************************************************************
Function:void Msg_ExcuteRTC_Message(Str_Msg_Parameter * P_Msg_Parameter)
Description:0.5秒时钟消息处理函数
Input:P_Msg_Parameter指向消息读取后存放的静态变量
Output:无
Return:C_OK正确处理，C_Error处理过程中出错
Calls:
Called By:调度500ms定时器到调用调用
Influence:
Tips:
Others:
*************************************************************************/
uchar8 Msg_ExcuteRTC_Message(Str_Msg_Parameter * P_Msg_Parameter)
{
	ulong32 V_ulDataCode;

	if( P_Msg_Parameter->DerictAddr == C_Msg_Dispatch )
	{
		if( ( *P_Msg_Parameter->Parameter == Pt_Dispatch_Timing ) && ( *(P_Msg_Parameter->Parameter+1) == C_HalfSecond ) )
		{
			if(P_Msg_Parameter->PowerFlag == C_PowerOn )
			{
				InF_Dispatch_ReadRtcToDataProcess(C_PowerOn);
			}
			else
			{
				return C_Error;
			}
		}
		else if( (*P_Msg_Parameter->Parameter == Pt_EventClearDI)&&(P_Msg_Parameter->Length==Pt_EventClearDI_Len+1) )
		{
			PF_Buffer4ToUlong32(P_Msg_Parameter->Parameter+1,&V_ulDataCode,4);
			if( V_ulDataCode == 0xffffffff )
			{
				InF_DispatchClr_Message( P_Msg_Parameter );
			}
			else
			{
				return C_Error;
			}
		}
	}
	else
	{
		return C_Error;
	}
	return C_OK;
}

/**********************************************************************
函数原型:void InF_DispatchClr_Message(Str_Msg_Parameter *P_Msg_Parameter)
函数功能:电表总清时，调度需要处理的事情
输入参数:
输出参数：
返回参数:无
调用时机：
备注:
功能说明：
**********************************************************************/
void InF_DispatchClr_Message(Str_Msg_Parameter *P_Msg_Parameter)
{
	uchar8 V_ucBuffer[20];

	if(P_Msg_Parameter->Length>20)
	{
		return;		/*正常不存在*/
	}

	PF_CopyDataBytes(P_Msg_Parameter->Parameter,V_ucBuffer,P_Msg_Parameter->Length);
	if( (V_ucBuffer[0] != Pt_MeterClear) && (V_ucBuffer[0] != Pt_EventClearDI) )	/*非电表总清消息或事件总清消息*/
	{
		return;
	}

	/*ESAM故障及其主动上报处理*/
	InF_ExecuteClr_Esam();
	/*时钟电池欠压及其主动上报*/
	InF_ExecuteClr_RTCBatt();
	/*停电抄表电池欠压及其主动上报*/
	InF_ExecuteClr_WakeUpBatt();
	/*内部程序错误及其主动上报*/

	/*存储器故障及其主动上报*/

	/*时钟故障及其主动上报*/
	InF_ExecuteClr_RTC();
}










