/********************************************************************************
Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     Relay.c
Version:       V1
Date:          2014-3-12
Description:   负荷开关处理
Function List: 
---------------------------------------------------------------------------------
History1:      第1次修改
内容1. Date:    2021-10-12
       Author:  wxy
       Modification:
       --------------------------------------------------------------------------
内容2. Date:
       Author:
       Modification:
---------------------------------------------------------------------------------
History2:      第2次修改
内容1. Date:
       Author:
       Modification:
       --------------------------------------------------------------------------
内容2. Date:
       Author:
       Modification:
********************************************************************************/

#include "Public.h"
#include "Relay.h"

uchar8 SV_ExternalRelayStatus;

/*******************************************************************************
函数原型：void InF_ InitRelayStatusPowerUp（void）
功能描述：上电初始化
输入参数：无
输出参数：无
返回参数：无
调用位置：
备    注：上电初始化时调用
*******************************************************************************/
void InF_InitRelayStatusPowerUp(void)
{
	uchar8	V_ucStartTime[7] = {0};
	uchar8	V_ucDataBuff[8] = {0};
	uchar8	V_ucRelayType;
	uchar8	V_ucDataBuff2[300] = {0};
	uchar8	V_ucEventFlag;
	ushort16	V_usOffset = 0, V_usResidualLength;
	ushort16	V_usDataLength;
	ushort16	V_usDataEncode = 0;
		
	V_usDataLength = CLMeter_Work_State1;
	InF_Read_Data(CMeter_Work_State1, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*读取电表运行状态字1*/
	V_ucDataBuff[1] &= C_ControlLoopNoError;	/*无控制回路错*/
	InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State1, &V_ucDataBuff[0], CLMeter_Work_State1, C_W_SafeFlag);	/*电表运行状态字1写数据层*/
		
	if(C_Meter_Type == C_SmartMeter)	/*智能表处理电表运行状态字状态*/
	{	/*电表运行状态字3初始化*/
		V_usDataLength = CLMeter_Work_State3;
		InF_Read_Data(CMeter_Work_State3, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*读取电表运行状态字3*/
		V_ucDataBuff[0] &= C_RelayOrderStatusOn;	/*继电器命令导通*/
		V_ucDataBuff[1] &= C_RelayProtect_Current_Release;	/*非保电*/
		V_ucDataBuff[0] &= C_RelayStatusOn;	/*继电器导通*/
		V_ucDataBuff[0] &= C_RelayPreWarning_Release;	/*无预跳闸报警*/
		InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State3, &V_ucDataBuff[0], CLMeter_Work_State3, C_W_SafeFlag);	/*电表运行状态字3写数据层*/
		
		return;
	}
	if(C_Meter_Type == C_R_SmartMeter)
	{
		Local_RelayOrder.RelayOrderStatus = C_Close_Direct;
		Local_RelayOrder.PreWarning = C_PreWarning_Release;
		
		InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_LocalOrder, &Local_RelayOrder.PreWarning, CLRelay_LocalOrder, C_W_SafeFlag);	/*本地控制命令写数据层*/
		SV_LocalOrderNum = 0x00;	/*本地命令序号置为0*/
	}
	
	V_usDataLength = CLRelay_RemoteOrder;
	if(InF_Read_Data(CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, &V_usDataLength, &V_usDataEncode) != C_OK)	/*读取远程控制命令*/
	{
		Com_RelayOrder.Protect_Current = C_Protect_Current_Release;	
		Com_RelayOrder.RelayOrderStatus = C_Close_Direct;
		Com_RelayOrder.PreWarning = C_PreWarning_Release;	
		
		InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, CLRelay_RemoteOrder, C_W_SafeFlag);	/*远程控制命令写数据层*/
		SV_ComOrderNum = 0x00;	/*远程命令序号置*/
	}
	
	V_usDataLength = CLRelay_LocalOrder;
	if(InF_Read_Data(CRelay_LocalOrder, &Local_RelayOrder.PreWarning, &V_usDataLength, &V_usDataEncode) != C_OK)	/*读取本地控制命令*/
	{	
		Local_RelayOrder.RelayOrderStatus = C_Close_Direct;
		Local_RelayOrder.PreWarning = C_PreWarning_Release;
		
		InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_LocalOrder, &Local_RelayOrder.PreWarning, CLRelay_LocalOrder, C_W_SafeFlag);	/*本地控制命令写数据层*/
		SV_LocalOrderNum = 0x00;	/*本地命令序号置为0*/
	}
	
	V_usDataLength = CLRelay_State;
	if(InF_Read_Data(CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, &V_usDataLength, &V_usDataEncode) != C_OK)	/*读取继电器状态*/
	{
		Relay_Stutas.RelaytheoreticWarningStatus = C_PreWarning_Release;
		Relay_Stutas.RelaytheoreticStatus = C_RelayOn;	
		Relay_Stutas.RelayRealStatus = C_RelayOn;
		
		InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, CLRelay_State, C_W_SafeFlag);	/*理论状态写数据层*/
	}	
	
	V_usDataLength = CLRelay_Type;
	InF_Read_Data(CRelay_Type, &V_ucRelayType, &V_usDataLength, &V_usDataEncode);	/*读取负荷开关类型*/
	
	V_usDataLength = CLRelay_State;
	InF_Read_Data(CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, &V_usDataLength, &V_usDataEncode);	/*读取继电器状态*/
	
	if(SF_Judge_EventIntegrity(C_RelayFaEndEnEventNo) == 0x68)	/*当前为有发生无结束则写恢复*/
	{
		SV_Error_Time = 0x00;

		V_usDataLength = CLRelayFa_Degree;
		InF_Read_Data(CRelayFa_Degree, &V_ucDataBuff2[0], &V_usDataLength, &V_usDataEncode);	/*读取发生次数*/
		V_usOffset += 4;
		PF_CopyDataBytes(V_ucStartTime, &V_ucDataBuff2[V_usOffset], CLEventHPTime);	/*发生时间*/
		V_usOffset += 7;
		V_usDataLength = CLEnter_LowPower_Time;
		InF_Read_Data(CEnter_LowPower_Time, &V_ucDataBuff2[V_usOffset], &V_usDataLength, &V_usDataEncode);	/*读取当前时间，即事件结束时间*/
		V_ucDataBuff2[V_usOffset + 6] = 0x20;
		V_usOffset += 8;
		V_usResidualLength = 300 - V_usOffset;	/*剩余buff长度*/
		V_ucEventFlag = 0x02;
		
		if(Inf_GetRecordData(&V_ucDataBuff2[V_usOffset], &V_usResidualLength, CRelayFa_OADTab, V_ucEventFlag) != C_OK)	/*获取关联OAD数据*/
		{
			return;
		}
		V_usOffset += V_usResidualLength;	/*数据总长度*/
		InF_Write_Data(C_Msg_Deal_RelayStatus, CRelayFa_Note_1 + 0x00000001, V_ucDataBuff2, V_usOffset, C_W_SafeFlag);	/*事件结束写数据*/
		Inf_EventReport_HP(C_RelayFaEndEnEventNo, C_End_EventReport);
	}

	/*静态变量上电初始化*/
	SV_24HourDelayTimer = 1;	/*电流超过门限电流计时*/
	SV_RelayRework_Timer = C_RelayReworkPowerUp_Timer;	/*重复动作定时器*/
	SV_AlarmAfterPowerUp = C_PreWarning;	/*上电时有报警命令时需要重新进行报警处理， 上电置0x68，用过后清零*/
	SV_RelayOpenAfterPowerUp = C_Open;	/*上电时条件合闸状态要先跳闸，上电置0x68，用过后清零*/
	SV_Error_Time = 0x00;	/*继电器异常时间*/
	
	/*本地远程控制命令处理*/
	SV_RelayDisplayStatus &= C_RealayOpenSignOff;	/*拉闸字符熄灭*/
	SV_RelayDisplayStatus &= C_BackLEDOff;	/*背光熄灭*/
	
	if( (Com_RelayOrder.RelayOrderStatus == C_Open) && (SV_OpenRealyDelay_Time != 0) )	/*跳闸*/
	{
		SV_OpenRealyDelay_Time = 1;
		SF_RealayOpenSignMsgSend_Relay(C_DisplayOn);	/*拉闸字符常显*/
	}
	else
	{
		SV_OpenRealyDelay_Time = 0;
	}
	if( (Local_RelayOrder.RelayOrderStatus == C_Pre_Open) && (SV_L_CloseRealyDelay_Time != 0) )	/*当前处于本地预跳闸状态且条件合闸延时时间不为0*/
	{
		SV_L_CloseRealyDelay_Time = C_L_CloseRealyDelay_Time;
		SF_RealayOpenSignMsgSend_Relay(C_DisplayOn);	/*拉闸字符常显*/
	}
	else if( (Local_RelayOrder.RelayOrderStatus == C_Close_Allow) && (SV_L_CloseRealyDelay_Time != 0) )	/*当前处于本地预跳闸状态且条件合闸延时时间不为0*/
	{
		SV_L_CloseRealyDelay_Time = 1;
		SF_RealayOpenSignMsgSend_Relay(C_DisplayOn);	/*拉闸字符常显*/
	}
	else
	{
		SV_L_CloseRealyDelay_Time = 0;	
	}
	
	if( ( (Com_RelayOrder.RelayOrderStatus == C_Close_Allow) || (Local_RelayOrder.RelayOrderStatus == C_Close_Allow) )
		 && ( (SV_RelayDisplayStatus&C_RelayStatusLEDTwinkle) == C_RelayStatusLEDTwinkle) )
	{		
		SF_RelayStatusLEDMsgSend_Relay(C_DisplayTwinkle);	/*跳闸指示灯闪烁*/
	}
	else
	{
		SV_RelayDisplayStatus &= C_RelayStatusLEDOff;	/*跳闸指示灯熄灭*/
	}	
	
	if( (Com_RelayOrder.RelayOrderStatus == C_Open_Allow) && (SV_Comm_CloseRealyDelay_Time != 0) )
	{
		SV_Comm_CloseRealyDelay_Time = 0;
		SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*拉闸字符熄灭*/

		if( (V_ucRelayType & C_Relay_Type) == 1)
		{
			Com_RelayOrder.RelayOrderStatus = C_Close_Direct;	/*远程控制命令置直接合闸*/
		}
		else
		{
			if(Relay_Stutas.RelaytheoreticStatus == C_RelayOff)
			{				
				SF_RelayStatusLEDMsgSend_Relay(C_DisplayTwinkle);	/*跳闸指示灯闪烁*/
				Com_RelayOrder.RelayOrderStatus = C_Close_Allow;	/*远程控制命令置合闸允许*/
				SV_ComOrderNum = SF_GetNewOrderNum();	/*更新远程命令序号*/
			}
			else
			{
				V_usDataLength = CLControl_ExecuteState;
				if(InF_Read_Data(CControl_ExecuteState, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode) == C_OK)	/*读取控制命令执行状态字*/
				{
					ushort16 V_usRelayRelayStatus = 0;
					PF_Buffer2ToUshort16(V_ucDataBuff, &V_usRelayRelayStatus);
					if( (V_usRelayRelayStatus&C_Relay_DelayOpen_Current_Status) == C_Relay_DelayOpen_Current_Status)
					{
						Relay_Stutas.RelaytheoreticStatus = C_RelayOff;
						SV_ComOrderNum = SF_GetNewOrderNum();	/*更新远程命令序号*/
					}
					else
					{
						Com_RelayOrder.RelayOrderStatus = C_Close_Direct;	/*远程控制命令置直接合闸*/
						SV_ComOrderNum = SF_GetNewOrderNum();	/*更新远程命令序号*/
					}
				}
				else
				{
					Com_RelayOrder.RelayOrderStatus = C_Close_Direct;	/*远程控制命令置直接合闸*/
					SV_ComOrderNum = SF_GetNewOrderNum();	/*更新远程命令序号*/				
				}
			}	
		}
	}
	else if( (Com_RelayOrder.RelayOrderStatus == C_Open_Direct) && (SV_Comm_CloseRealyDelay_Time != 0) )
	{
		Com_RelayOrder.RelayOrderStatus = C_Close_Direct;
		SV_ComOrderNum = SF_GetNewOrderNum();	/*更新远程命令序号*/
		SV_Comm_CloseRealyDelay_Time = 0;
		SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*拉闸字符熄灭*/

	}
	else
	{
		SV_Comm_CloseRealyDelay_Time = 0;	
	}
	
	memset(&V_ucDataBuff[0], 0x00, 8);	
	InF_Write_Data(C_Msg_Deal_RelayStatus, CControl_ExecuteState, V_ucDataBuff, CLControl_ExecuteState, C_W_SafeFlag);	/*控制命令执行状态字*/
	InF_Write_Data(C_Msg_Deal_RelayStatus, CControl_ErrorState, &V_ucDataBuff[2], CLControl_ErrorState, C_W_SafeFlag);	/*控制命令错误状态字*/
	
	/*电表运行状态字3初始化*/
	V_usDataLength = CLMeter_Work_State3;
	InF_Read_Data(CMeter_Work_State3, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*读取电表运行状态字3*/

	if( (Com_RelayOrder.RelayOrderStatus == C_Open)
		|| (Com_RelayOrder.RelayOrderStatus == C_Open_Allow)
		|| (Com_RelayOrder.RelayOrderStatus == C_Open_Direct) )
	{
		V_ucDataBuff[0] |= C_RelayOrderStatusOff;	/*继电器命令断开*/
	}
	else 
	{
		V_ucDataBuff[0] &= C_RelayOrderStatusOn;	/*继电器命令导通*/
	}
	if(Com_RelayOrder.Protect_Current == C_Protect_Current)
	{
		V_ucDataBuff[1] |= C_RelayProtect_Current;	/*保电*/
		V_ucDataBuff[0] &= C_RelayOrderStatusOn;	/*继电器命令导通*/
	}
	else
	{
		V_ucDataBuff[1] &= C_RelayProtect_Current_Release;	/*非保电*/
	}
	InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State3, &V_ucDataBuff[0], CLMeter_Work_State3, C_W_SafeFlag);	/*电表运行状态字3写数据层*/
	InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, CLRelay_RemoteOrder, C_W_SafeFlag);	/*远程控制命令写数据层*/
#if 0	
	SV_ucExternalRelayStatusTime = 0;	/*外置继电器反馈信号5s检测时间清零*/
#endif			
  return;  
}

/*******************************************************************************
函数原型：uchar8 InF_RelayProtectStatus(void)
功能描述：判断当前是否保电状态
输入参数：无
输出参数：无
返回参数：C_Protect，当前处于保电；	C_NotProtect，当前非保电
调用位置：该函数由通信模块的SF_GetAPDU_Read函数调用
备    注：
*******************************************************************************/
uchar8 InF_RelayProtectStatus(void)
{
	uchar8	V_ucReturnFlag;
	ushort16	V_usDataLength;
	ushort16	V_usDataEncode = 0;
  
	V_ucReturnFlag = C_NotProtect;
  
	if(C_Meter_Type == C_SmartMeter)
	{
		return V_ucReturnFlag;
	}
  
	V_usDataLength = CLRelay_RemoteOrder;
	InF_Read_Data(CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, &V_usDataLength, &V_usDataEncode);	/*读取远程控制命令*/
	
	if(Com_RelayOrder.Protect_Current == C_Protect_Current)	/*当前处于远程保电状态*/
	{
		V_ucReturnFlag = C_Protect;	
	}

	return	V_ucReturnFlag;
}

/*******************************************************************************
函数原型：uchar8 InF_RelayOpenStatus(void)
功能描述：判断当前是否内置表跳闸状态
输入参数：无
输出参数：无
返回参数：C_EventError，当前处于内置表继电器跳闸状态（不记电源异常事件记录）；
          C_EventOK，当前非内置表跳闸状态（需要进行电源异常判断）
调用位置：该函数由Inf_PowerAbnormal接口函数调用
备    注：
*******************************************************************************/
uchar8 InF_RelayOpenStatus(void)
{
	uchar8	V_ucReturnFlag;
	uchar8	V_ucRelayType;
	ushort16	V_usDataLength;
	ushort16	V_usDataEncode = 0;

	V_ucReturnFlag = C_EventOK;
  
	if(C_Meter_Type == C_SmartMeter)
	{
		return	V_ucReturnFlag;
	}
  
	V_usDataLength = CLRelay_Type;
	InF_Read_Data(CRelay_Type, &V_ucRelayType, &V_usDataLength, &V_usDataEncode);	/*读取负荷开关类型*/

	if( (V_ucRelayType & C_Relay_Type) == 0)
	{
		V_usDataLength = CLRelay_State;
		InF_Read_Data(CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, &V_usDataLength, &V_usDataEncode);	/*读取继电器状态*/
		if(Relay_Stutas.RelayRealStatus == C_RelayOff)
		{
			V_ucReturnFlag = C_EventError;	
		}
	}

	return	V_ucReturnFlag;
}

/*******************************************************************************
函数原型：uchar8 InF_RelayOpenStatus_698 (void)
功能描述：判断当前是否跳闸状态
输入参数：无
输出参数：无
返回参数：1，当前处于继电器跳闸状态；0，当前非跳闸状态
调用位置：该函数由Inf_Get_ApplianceF205接口函数调用
备    注：
*******************************************************************************/
uchar8 InF_RelayOpenStatus_698 (void)
{
	uchar8	V_ucReturnFlag;
	ushort16	V_usDataLength;
	ushort16	V_usDataEncode = 0;

	V_ucReturnFlag = 0;

 	if(C_Meter_Type == C_SmartMeter)
	{
		return	V_ucReturnFlag;
	}

	V_usDataLength = CLRelay_State;
	InF_Read_Data(CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, &V_usDataLength, &V_usDataEncode);	/*读取继电器状态*/

	if(Relay_Stutas.RelayRealStatus == C_RelayOff)
	{
		V_ucReturnFlag = 0x01;	
	}

	return V_ucReturnFlag;
}

/*******************************************************************************
函数原型：uchar8 InF_DealwithComRelayOrder(uchar8 V_ucOrderType, uchar8 *P_OperaterCode, ulong32 V_ucDelayTime, ushort16 *V_usOrderExcuteStatus, uchar8 V_Flag)
功能描述：控制命令处理
输入参数：V_ucOrderType, 控制命令；*P_OperaterCode，操作者代码；V_ucDelayTime，跳闸自动恢复持续时间（非跳闸自动恢复命令时置0）
          V_Flag，判断是否645协议调用，以判断跳闸自动恢复，R2为00时，应答异常
输出参数：无
返回参数：C_OK，表示控制命令正常执行，此时返回参数*V_usOrderExcuteStatus的值为控制命令执行状态字；
          C_Error，表示控制命令执行异常，此时返回参数V_usOrderExcuteStatus的值为错误状态字。
调用位置：
备    注：
*******************************************************************************/
uchar8 InF_DealwithComRelayOrder(uchar8 V_ucOrderType, uchar8 *pV_ucOperaterCode, ulong32 V_ulDelayTime, ushort16 *V_usOrderExcuteStatus, uchar8 V_ucFlag)
{
	uchar8	V_ucDataBuff[6] = {0};
	uchar8	V_ucReturnFlag;
	ulong32	V_ulTime;
	uchar8	V_ucRelayType;
	uchar8	V_ucDataBuff_Msg[5];
	uchar8	V_ucCurrentFlag = 0, V_ucDelayTimeFlag = 0;
	ushort16	V_usDataLength;
	ushort16	V_usDataEncode = 0;
	
	V_ucReturnFlag = C_OK;
	*V_usOrderExcuteStatus = 0;
	
	V_usDataLength = CLRelay_RemoteOrder;
	InF_Read_Data(CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, &V_usDataLength, &V_usDataEncode);	/*读取远程控制命令*/

	V_usDataLength = CLRelay_LocalOrder;
	InF_Read_Data(CRelay_LocalOrder, &Local_RelayOrder.PreWarning, &V_usDataLength, &V_usDataEncode);	/*读取本地控制命令*/
	
	V_usDataLength = CLRelay_State;
	InF_Read_Data(CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, &V_usDataLength, &V_usDataEncode);	/*读取继电器状态*/
	
	switch(V_ucOrderType)
	{
		case C_Alarm_comm:	/*报警*/
		{	
			Com_RelayOrder.PreWarning = C_PreWarning;
			*V_usOrderExcuteStatus = C_Alarm_Status;
		}break;
		
		case C_Alarm_Release_comm:	/*报警解除*/
		{	
			Com_RelayOrder.PreWarning = C_PreWarning_Release;
			*V_usOrderExcuteStatus = C_Alarm_Release_Status;
		}break;
		
		case C_AlarmOpenRelay_Direct_comm:	/*跳闸自动恢复（延时时间到直接合闸）*/
		case C_AlarmOpenRelay_Allow_comm:	/*跳闸自动恢复（延时时间到合闸允许）*/
		{	
			if(Com_RelayOrder.Protect_Current == C_Protect_Current)	/*跳闸自动恢复失败（保电）*/
			{
				V_ucReturnFlag = C_Error;
				*V_usOrderExcuteStatus = C_Protect_AlarmOpenfailure;
				break;
			}
			
			if(SF_JudgeOrderStatus() == C_UnAllowed)	/*跳闸自动恢复失败（跳闸）*/
			{
				V_ucReturnFlag = C_Error;
				*V_usOrderExcuteStatus = C_RelayOpen_OpenAlarmfailure;
				break;
			}

			if(V_ucFlag == C_UsedBy645)
			{
				if(V_ulDelayTime == 0x00)	/*跳闸自动恢复持续时间无效*/
				{
					V_ucReturnFlag = C_Error;
					*V_usOrderExcuteStatus = C_TimeUnvalid_AlarmOpenfailure;
					break;
				}
			}

			SF_DealWithSV_Relay();	/*内部静态变量处理*/
			PF_CopyDataBytes(pV_ucOperaterCode, SV_ucRelayOperatorCode, 4);	/*操作者代码赋值*/
			V_usDataLength = CLMeter_Work_State3;
			InF_Read_Data(CMeter_Work_State3, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*读取电表运行状态字3*/
			V_ucDataBuff[0] |= C_RelayOrderStatusOff;	/*继电器命令断开*/
			InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State3, &V_ucDataBuff[0], CLMeter_Work_State3, C_W_SafeFlag);	/*电表运行状态字3写数据层*/

			/*判断当前电流是否允许跳闸*/
			if(SF_JudgeCurrent_Relay() != C_CurrentOk)
			{
				V_usDataLength = CLRelay_Open_CurrTimer;
				if(InF_Read_Data(CRelay_Open_CurrTimer, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode) != C_OK)	/*大电流延时时间*/
				{
					SV_24HourDelayTimer = 1;	/*大电流延时时间置初值*/
				}
				else
				{
					PF_BufferXToUlong32(V_ucDataBuff, &V_ulTime, V_usDataLength);
					if(V_ulTime == 0)
					{
						SV_24HourDelayTimer = 1;	/*大电流延时时间置初值*/
					}
					else
					{
						*V_usOrderExcuteStatus |= C_Relay_DelayOpen_Current_Status;
						V_ucCurrentFlag = 0x68;
						SV_24HourDelayTimer = V_ulTime * 60 * 2;	/*大电流延时时间置初值*/
					}
				}
			}

			if( (V_ucDelayTimeFlag == 0x68) || (V_ucCurrentFlag == 0x68) )
			{
				if(Relay_Stutas.RelaytheoreticStatus != C_RelayOff)
				{
					SF_RealayOpenSignMsgSend_Relay(C_DisplayTwinkle);	/*拉闸字符闪烁*/
					SF_BackLEDMsgSend_Relay(C_DisplayOn);	/*点亮背光*/
				}
				else
				{
					SF_RealayOpenSignMsgSend_Relay(C_DisplayOn);	/*拉闸字符常显*/
				}	
			}
			
			/*跳闸自动恢复定时器置初值*/
			SV_Comm_CloseRealyDelay_Time = V_ulDelayTime * 60 * 2;
					
			if(V_ucOrderType == C_AlarmOpenRelay_Direct_comm)
			{
				Com_RelayOrder.RelayOrderStatus = C_Open_Direct;	/*远程控制命令置跳闸自动恢复（延时时间到直接合闸）*/
			}
			else
			{
				Com_RelayOrder.RelayOrderStatus = C_Open_Allow;	/*远程控制命令置跳闸自动恢复（延时时间到合闸允许）*/
			}
					
			/*判断当前电流及跳闸延时时间是否允许跳闸*/
			if( (V_ucCurrentFlag == 0) && (V_ucDelayTimeFlag == 0) )
			{
				*V_usOrderExcuteStatus = C_AlarmOpenRelay_Status;	
			}
		}break;

		case C_Relay_Open_comm:	/*跳闸*/
		{	
			if(Com_RelayOrder.Protect_Current == C_Protect_Current)	/*跳闸失败（保电）*/
			{
				V_ucReturnFlag = C_Error;
				*V_usOrderExcuteStatus = C_Protect_Openfailure;
				break;
			}
			
			SF_DealWithSV_Relay();	/*内部静态变量处理*/
			PF_CopyDataBytes(pV_ucOperaterCode, SV_ucRelayOperatorCode, 4);	/*操作者代码赋值*/
			
			Com_RelayOrder.RelayOrderStatus = C_Open;	/*远程控制命令置跳闸*/
			
			V_usDataLength = CLMeter_Work_State3;
			InF_Read_Data(CMeter_Work_State3, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*读取电表运行状态字3*/
			V_ucDataBuff[0] |= C_RelayOrderStatusOff;	/*继电器命令断开*/
			InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State3, &V_ucDataBuff[0], CLMeter_Work_State3, C_W_SafeFlag);	/*电表运行状态字3写数据层*/
			
			/*判断当前电流是否允许跳闸*/
			if(SF_JudgeCurrent_Relay() != C_CurrentOk)
			{
				V_usDataLength = CLRelay_Open_CurrTimer;
				if(InF_Read_Data(CRelay_Open_CurrTimer, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode) != C_OK)	/*大电流延时时间*/
				{
					SV_24HourDelayTimer = 1;	/*大电流延时时间置初值*/
				}
				else
				{
					PF_BufferXToUlong32(V_ucDataBuff, &V_ulTime, V_usDataLength);
					if(V_ulTime == 0)
					{
						SV_24HourDelayTimer = 1;	/*大电流延时时间置初值*/
					}
					else
					{
						*V_usOrderExcuteStatus |= C_Relay_DelayOpen_Current_Status;
						V_ucCurrentFlag = 0x68;
					}
				}
			}

			if(V_ulDelayTime == 0)	/*判断跳闸延时时间是否为0*/
			{
				SV_OpenRealyDelay_Time = 1;	/*跳闸延时时间置初值*/
			}
			else
			{
				SV_OpenRealyDelay_Time = V_ulDelayTime * 60 * 2;	/*跳闸延时时间置初值*/
				V_ucDelayTimeFlag = 0x68;
				if( (V_ucFlag == C_UsedBy645) && (V_ucCurrentFlag == 0x68) )
				{
					*V_usOrderExcuteStatus &= (~C_Relay_DelayOpen_Current_Status);	/*698兼容645置过跳闸延时不为0，同时大电流延时跳闸, 只置跳闸延时*/
				}
				*V_usOrderExcuteStatus |= C_Relay_DelayOpen_Time_Status;
			}

			if( (V_ucDelayTimeFlag == 0x68) || (V_ucCurrentFlag == 0x68) )
			{
				if(Relay_Stutas.RelaytheoreticStatus != C_RelayOff)
				{
					SF_RealayOpenSignMsgSend_Relay(C_DisplayTwinkle);	/*拉闸字符闪烁*/
					SF_BackLEDMsgSend_Relay(C_DisplayOn);	/*点亮背光*/
				}
				else
				{
					SF_RealayOpenSignMsgSend_Relay(C_DisplayOn);	/*拉闸字符常显*/
				}	
			}	
			else
			{
				*V_usOrderExcuteStatus = C_Relay_Open_Status;	
			}
		}break;
		
		case C_Relay_Close_Allow_comm:	/*合闸允许*/
		{	
			if(Com_RelayOrder.Protect_Current == C_Protect_Current_Release)	/*保电*/
			{
				SF_DealWithSV_Relay();	/*内部静态变量处理*/
				PF_CopyDataBytes(pV_ucOperaterCode, SV_ucRelayOperatorCode, 4);	/*操作者代码赋值*/
			}			
			
			V_usDataLength = CLMeter_Work_State3;
			InF_Read_Data(CMeter_Work_State3, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*读取电表运行状态字3*/
			V_ucDataBuff[0] &= C_RelayOrderStatusOn;	/*继电器命令导通*/
			InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State3, &V_ucDataBuff[0], CLMeter_Work_State3, C_W_SafeFlag);	/*电表运行状态字3写数据层*/
			
			V_usDataLength = CLRelay_Type;
			InF_Read_Data(CRelay_Type, &V_ucRelayType, &V_usDataLength, &V_usDataEncode);	/*读取负荷开关类型*/

			if( (V_ucRelayType & C_Relay_Type) == 1)
			{
				Com_RelayOrder.RelayOrderStatus = C_Close_Direct;	/*远程控制命令置直接合闸*/
				
				if(Local_RelayOrder.RelayOrderStatus != C_Open)
				{
					SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*拉闸字符熄灭*/
				}
				if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
				{
					SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*背光关闭*/
				}	
			}
			else
			{
				if(Local_RelayOrder.RelayOrderStatus != C_Open)
				{
					SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*拉闸字符熄灭*/
				
					if(Relay_Stutas.RelaytheoreticStatus == C_RelayOff)
					{
						SF_RelayStatusLEDMsgSend_Relay(C_DisplayTwinkle);	/*跳闸指示灯闪烁*/
					}
				}

				if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
				{
					SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*背光关闭*/
				}

				if(Com_RelayOrder.RelayOrderStatus == C_Close_Direct)
				{
					*V_usOrderExcuteStatus = C_Relay_Close_Allow_Status;
					break;	
				}
				
				Com_RelayOrder.RelayOrderStatus = C_Close_Allow;	/*远程控制命令置允许合闸*/
				SV_ComOrderNum = SF_GetNewOrderNum();	/*更新远程命令序号*/
			}
			*V_usOrderExcuteStatus = C_Relay_Close_Allow_Status;
		}break;

		case C_Relay_Close_Direct_comm:	/*直接合闸*/
		{	
			if(Com_RelayOrder.Protect_Current == C_Protect_Current_Release)	/*保电*/
			{
				SF_DealWithSV_Relay();	/*内部静态变量处理*/
				PF_CopyDataBytes(pV_ucOperaterCode, SV_ucRelayOperatorCode, 4);	/*操作者代码赋值*/
			}

			V_usDataLength = CLMeter_Work_State3;
			InF_Read_Data(CMeter_Work_State3, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*读取电表运行状态字3*/
			V_ucDataBuff[0] &= C_RelayOrderStatusOn;	/*继电器命令导通*/
			InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State3, &V_ucDataBuff[0], CLMeter_Work_State3, C_W_SafeFlag);	/*电表运行状态字3写数据层*/
			
			Com_RelayOrder.RelayOrderStatus = C_Close_Direct;	/*远程控制命令置直接合闸*/
			SV_ComOrderNum = SF_GetNewOrderNum();	/*更新远程命令序号*/
			
			if(Local_RelayOrder.RelayOrderStatus == C_Close_Allow)
			{
				Local_RelayOrder.RelayOrderStatus = C_Close_Direct;	/*收到保电命令后，开关内置表，本地控制命令置合闸允许*/
				InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_LocalOrder, &Local_RelayOrder.PreWarning, CLRelay_LocalOrder, C_W_SafeFlag);	/*本地控制命令写数据层*/
				SV_LocalOrderNum = SF_GetNewOrderNum();	/*更新本地命令序号*/
			}
			
			if(Local_RelayOrder.RelayOrderStatus != C_Open)
			{
				SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*拉闸字符熄灭*/
			}
			if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
			{
				SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*背光关闭*/
			}	
			
			*V_usOrderExcuteStatus = C_Relay_Close_Direct_Status;			
		}break;

		case C_Protect_Current_comm:	/*保电*/
		{
			SF_DealWithSV_Relay();	/*内部静态变量处理*/
			PF_CopyDataBytes(pV_ucOperaterCode, SV_ucRelayOperatorCode, 4);	/*操作者代码赋值*/
			
			V_usDataLength = CLMeter_Work_State3;
			InF_Read_Data(CMeter_Work_State3, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*读取电表运行状态字3*/
			V_ucDataBuff[0] &= C_RelayOrderStatusOn;	/*继电器命令导通*/
			V_ucDataBuff[1] |= C_RelayProtect_Current;	/*继电器保电*/
			InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State3, &V_ucDataBuff[0], CLMeter_Work_State3, C_W_SafeFlag);	/*电表运行状态字3写数据层*/
			
			V_usDataLength = CLRelay_Type;
			InF_Read_Data(CRelay_Type, &V_ucRelayType, &V_usDataLength, &V_usDataEncode);	/*读取负荷开关类型*/
			
			if( (V_ucRelayType & C_Relay_Type) == 1)	
			{
				SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*拉闸字符熄灭*/
				
				if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
				{
					SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*关闭背光*/
				}
			
				Com_RelayOrder.RelayOrderStatus = C_Close_Direct;	/*收到保电命令后，开关外置表，远程命令置为直接合闸*/
				InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, CLRelay_RemoteOrder, C_W_SafeFlag);	/*远程控制命令写数据层*/
			
				Local_RelayOrder.RelayOrderStatus = C_Close_Direct;	/*收到保电命令后，开关外置表，本地控制命令置直接合闸*/
				InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_LocalOrder, &Local_RelayOrder.PreWarning, CLRelay_LocalOrder, C_W_SafeFlag);	/*本地控制命令写数据层*/
			}
			else
			{
				SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*拉闸字符熄灭*/
				
				if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
				{
					SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*关闭背光*/
				}
					
				if(Relay_Stutas.RelaytheoreticStatus == C_RelayOff)
				{				
					SF_RelayStatusLEDMsgSend_Relay(C_DisplayTwinkle);	/*跳闸指示灯闪烁*/
				}					
				
				if(Local_RelayOrder.RelayOrderStatus != C_Close_Direct)
				{
					Local_RelayOrder.RelayOrderStatus = C_Close_Allow;	/*收到保电命令后，开关内置表，本地控制命令置合闸允许*/
					InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_LocalOrder, &Local_RelayOrder.PreWarning, CLRelay_LocalOrder, C_W_SafeFlag);	/*本地控制命令写数据层*/
					SV_LocalOrderNum = SF_GetNewOrderNum();	/*更新本地命令序号*/
				}

				if(Com_RelayOrder.RelayOrderStatus != C_Close_Direct)
				{
					Com_RelayOrder.RelayOrderStatus = C_Close_Allow;	/*收到保电命令后，开关内置表，远程命令置为合闸允许*/
					InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, CLRelay_RemoteOrder, C_W_SafeFlag);	/*远程控制命令写数据层*/
					SV_ComOrderNum = SF_GetNewOrderNum();	/*更新远程命令序号*/
				}	
			}
			
			Com_RelayOrder.Protect_Current = C_Protect_Current;	/*远程控制命令置保电*/
			*V_usOrderExcuteStatus = C_Protect_Current_Status;
			
			if(C_Meter_Type == C_L_SmartMeter)	/*本地表*/
			{
				V_ucDataBuff_Msg[0] = Pt_ParaMetersChange;
				V_ucDataBuff_Msg[1] = C_ReworkWarningPara;	/*参数变更*/
			
				SF_MsgSend_Relay(V_ucDataBuff_Msg, Pt_ParaMetersChange+1, C_Msg_EnergyMetering);	/*触发电能模块参数变更消息*/

			}
		}break;

		case C_Protect_Current_Release_comm:	/*保电解除*/
		{	
			V_usDataLength = CLMeter_Work_State3;
			InF_Read_Data(CMeter_Work_State3, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*读取电表运行状态字3*/
			V_ucDataBuff[1] &= C_RelayProtect_Current_Release;	/*继电器非保电*/
			InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State3, &V_ucDataBuff[0], CLMeter_Work_State3, C_W_SafeFlag);	/*电表运行状态字3写数据层*/
			
			Com_RelayOrder.Protect_Current = C_Protect_Current_Release;	/*远程控制命令置非保电*/
			
			if(C_Meter_Type == C_L_SmartMeter)	/*本地表*/
			{
				V_ucDataBuff_Msg[0] = Pt_ParaMetersChange;
				V_ucDataBuff_Msg[1] = C_ReworkWarningPara;	/*参数变更*/
				
				SF_MsgSend_Relay(V_ucDataBuff_Msg, Pt_ParaMetersChange + 1, C_Msg_EnergyMetering);	/*触发电能模块参数变更消息*/
			}
			
			*V_usOrderExcuteStatus = C_Protect_Current_Release_Status;
		}break;
		
		default:
		{	
			V_ucReturnFlag = C_Error;
			*V_usOrderExcuteStatus = C_PasswordError_failure;
		}break;	
	}
	InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, CLRelay_RemoteOrder, C_W_SafeFlag);	/*远程控制命令写数据层*/
		
	ushort16 V_usRelayRelayStatus = 0;

	if(V_ucReturnFlag == C_OK)
	{
		PF_Ushort16ToBuffer2(V_ucDataBuff, V_usOrderExcuteStatus);
		PF_Ushort16ToBuffer2(&V_ucDataBuff[2], &V_usRelayRelayStatus);
		InF_Write_Data(C_Msg_Deal_RelayStatus, CControl_ExecuteState, V_ucDataBuff, CLControl_ExecuteState, C_W_SafeFlag);	/*控制命令执行状态字*/
		InF_Write_Data(C_Msg_Deal_RelayStatus, CControl_ErrorState, &V_ucDataBuff[2], CLControl_ErrorState, C_W_SafeFlag);	/*控制命令错误状态字*/
	}
	else
	{
		PF_Ushort16ToBuffer2(V_ucDataBuff, &V_usRelayRelayStatus);
		PF_Ushort16ToBuffer2(&V_ucDataBuff[2], V_usOrderExcuteStatus);
		InF_Write_Data(C_Msg_Deal_RelayStatus, CControl_ExecuteState, V_ucDataBuff, CLControl_ExecuteState, C_W_SafeFlag);	/*控制命令执行状态字*/
		InF_Write_Data(C_Msg_Deal_RelayStatus, CControl_ErrorState, &V_ucDataBuff[2], CLControl_ErrorState, C_W_SafeFlag);	/*控制命令错误状态字*/
	}

	return V_ucReturnFlag;
}

/*******************************************************************************
函数原型：void Msg_Deal_RelayStatus(Str_Msg_Parameter *P_Msg)
功能描述：继电器消息处理
输入参数：信息参数结构体
输出参数：无
返回参数：无
调用位置：
备    注：调度秒变化调用函数；金额变化调用该函数（电能模块发送消息）
*******************************************************************************/
void Msg_Deal_RelayStatus(Str_Msg_Parameter *pStr_Msg_Parameter)
{
	uchar8	V_ucDataBuff[6];
	uchar8	*pV_ucParm;
	ulong32	V_ulDataCode;
	uchar8	V_ucRelayType;
	uchar8	V_ucOperaterCode[4] = {0xFF, 0xFF, 0xFF, 0xFF};
	ushort16	V_usOrderExcuteStatus;
	ushort16	V_usDataCRC;
	ushort16	V_usDataLength;
	ushort16	V_usDataEncode = 0;
	
	if(C_Meter_Type == C_SmartMeter)
	{
		return;	/*智能表不支持*/
	}

	pV_ucParm = pStr_Msg_Parameter->Parameter;
	if(pStr_Msg_Parameter->PowerFlag != C_PowerOn)
	{
		return;
	}
	if( (*pV_ucParm == Pt_MeterClear) && (pStr_Msg_Parameter->Length == Pt_MeterClear_Len + 1) )	/*通信总清消息*/
	{
		V_usDataLength = CLMeter_Work_State1;
		InF_Read_Data(CMeter_Work_State1, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*读取电表运行状态字1*/
		V_ucDataBuff[1] &= C_ControlLoopNoError;	/*清控制回路错*/
		InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State1, &V_ucDataBuff[0], CLMeter_Work_State1, C_W_SafeFlag);	/*电表运行状态字1写数据层*/
		SV_Error_Time = 0x00;
#if 0
		V_usDataLength = CLMeter_Work_State3;
		InF_Read_Data(CMeter_Work_State3, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*读取电表运行状态字3*/
		V_ucDataBuff[0] &= C_RelayStatusOn_External;	/*外置继电器反馈信号状态置0(0:通 1:断)*/
		InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State3, &V_ucDataBuff[0], CLMeter_Work_State1, C_W_SafeFlag);	/*电表运行状态字3写数据层*/
		SV_ucExternalRelayStatusTime = 0;	/*外置继电器反馈信号5s检测时间清零*/
#endif
		V_usDataLength = CLRelay_Type;
		InF_Read_Data(CRelay_Type, &V_ucRelayType, &V_usDataLength, &V_usDataEncode);	/*读取负荷开关类型*/
	
		V_usDataLength = CLRelay_State;
		InF_Read_Data(CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, &V_usDataLength, &V_usDataEncode);	/*读取继电器状态*/
	
		if( (V_ucRelayType & C_Relay_Type) == 1)
		{
			if(Relay_Stutas.RelaytheoreticStatus == C_RelayOn)
			{
				Relay_Stutas.RelayRealStatus = C_RelayOn;	
				InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, CLRelay_State, C_W_SafeFlag);	/*继电器状态写数据层*/
				SF_RelayStatusLEDMsgSend_Relay(C_DisplayOff);	/*跳闸指示灯熄灭*/
			}
		}
		if(Relay_Stutas.RelaytheoreticStatus == C_RelayOff)	/*理论状态为跳闸*/
		{
			SV_EventOut_Err_Relay[0] = C_EventOutOpenErr_Relay;	/*表示需要上报负荷开关误动作事件*/
			V_usDataCRC = PF_Cal_CRC(SV_EventOut_Err_Relay, 1);
			PF_Ushort16ToBuffer2(&SV_EventOut_Err_Relay[1], &V_usDataCRC);	
		}
		if(Relay_Stutas.RelaytheoreticStatus == C_RelayOn)	/*理论状态为合闸*/
		{
			SV_EventOut_Err_Relay[0] = C_EventOutCloseErr_Relay;	/*表示需要上报负荷开关误动作事件*/
			V_usDataCRC = PF_Cal_CRC(SV_EventOut_Err_Relay, 1);
			PF_Ushort16ToBuffer2(&SV_EventOut_Err_Relay[1], &V_usDataCRC);		
		}
		
		SV_EventOut_Open_Relay[0] = C_EventOutNot_Relay;	/*表示不需要上报跳闸成功事件 lzy20150714*/
		V_usDataCRC = PF_Cal_CRC(SV_EventOut_Open_Relay, 1);
		PF_Ushort16ToBuffer2(&SV_EventOut_Open_Relay[1], &V_usDataCRC); 
		
		SV_EventOut_Close_Relay[0] = C_EventOutNot_Relay;	/*表示不需要上报合闸成功事件 lzy20150714*/
		V_usDataCRC = PF_Cal_CRC(SV_EventOut_Close_Relay, 1);
		PF_Ushort16ToBuffer2(&SV_EventOut_Close_Relay[1], &V_usDataCRC);	
		
		if(C_Meter_Type == C_L_SmartMeter)	/*本地表*/
		{
			InF_DealwithComRelayOrder(C_Alarm_Release_comm, V_ucOperaterCode, 0x00, &V_usOrderExcuteStatus, C_UsedBy698);	
			InF_DealwithComRelayOrder(C_Relay_Close_Direct_comm, V_ucOperaterCode, 0x00, &V_usOrderExcuteStatus, C_UsedBy698);
			if( (V_ucRelayType & C_Relay_Type) == 1)	/*20150731修改，本地外地表在总清命令时置电表清零标识*/
			{
				SV_ClearFlag = 0x68;	/*电表清零标识*/
			}
		}
		else	/*20150731修改，远程表在总清命令下也清楚远程跳闸状态*/
		{
			if( (V_ucRelayType & C_Relay_Type) == 1)
			{
				InF_DealwithComRelayOrder(C_Relay_Close_Direct_comm, V_ucOperaterCode, 0x00, &V_usOrderExcuteStatus, C_UsedBy698);	
				SV_ClearFlag = 0x68;	/*电表清零标识*/
			}
		}
	}
	else if( (*pV_ucParm == Pt_EventClearDI) && (pStr_Msg_Parameter->Length == Pt_EventClearDI_Len+1) )	/*通信事件清零消息*/
	{
		PF_Buffer4ToUlong32(pV_ucParm + 1, &V_ulDataCode, 4);

		if( (V_ulDataCode == C_EventClearSingle) || (V_ulDataCode == C_EventClearAll) )
		{
			V_usDataLength = CLMeter_Work_State1;
			InF_Read_Data(CMeter_Work_State1, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*读取电表运行状态字1*/
			V_ucDataBuff[1] &= C_ControlLoopNoError;	/*清控制回路错*/
			InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State1, &V_ucDataBuff[0], CLMeter_Work_State1, C_W_SafeFlag);	/*电表运行状态字1写数据层*/
			SV_Error_Time = 0x00;	
		}

		if(V_ulDataCode == C_EventClearAll)
		{
			if(Relay_Stutas.RelaytheoreticStatus == C_RelayOff)	/*理论状态为跳闸*/
			{
				SV_EventOut_Err_Relay[0] = C_EventOutOpenErr_Relay;	/*表示需要上报负荷开关误动作事件*/
				V_usDataCRC = PF_Cal_CRC(SV_EventOut_Err_Relay, 1);
				PF_Ushort16ToBuffer2(&SV_EventOut_Err_Relay[1], &V_usDataCRC);	
			}
			if(Relay_Stutas.RelaytheoreticStatus == C_RelayOn)	/*理论状态为合闸*/
			{
				SV_EventOut_Err_Relay[0] = C_EventOutCloseErr_Relay;	/*表示需要上报负荷开关误动作事件*/
				V_usDataCRC = PF_Cal_CRC(SV_EventOut_Err_Relay, 1);
				PF_Ushort16ToBuffer2(&SV_EventOut_Err_Relay[1], &V_usDataCRC);		
			}
			
			SV_EventOut_Open_Relay[0] = C_EventOutNot_Relay;	/*表示不需要上报跳闸成功事件 lzy20150714*/
			V_usDataCRC = PF_Cal_CRC(SV_EventOut_Open_Relay, 1);
			PF_Ushort16ToBuffer2(&SV_EventOut_Open_Relay[1], &V_usDataCRC); 
			
			SV_EventOut_Close_Relay[0] = C_EventOutNot_Relay;	/*表示不需要上报合闸成功事件 lzy20150714*/
			V_usDataCRC = PF_Cal_CRC(SV_EventOut_Close_Relay, 1);
			PF_Ushort16ToBuffer2(&SV_EventOut_Close_Relay[1], &V_usDataCRC);		
		}
	}
	else if( (*pV_ucParm == Pt_RelayStateFlag) && (pStr_Msg_Parameter->Length == Pt_RelayStateFlag_Len + 1) )	/*电量模块触发继电器命令消息*/
	{
		if(C_Meter_Type == C_L_SmartMeter)	/*本地表*/
		{
			SF_LocalControl_Relay(*(pV_ucParm + 1) );	
		}			
	}
	else if( (*pV_ucParm == Pt_CardFlag) && (pStr_Msg_Parameter->Length == Pt_CardFlag_Len + 1) )	/*插卡消息*/
	{
		if(C_Meter_Type == C_L_SmartMeter)	/*本地表*/
		{
			SF_Cardor3sCloseRelayTask_Relay();	
		}			
	}
	else if( (*pV_ucParm == Pt_Dispatch_Key) && (pStr_Msg_Parameter->Length == Pt_Dispatch_Key_Len + 1) && (*(pV_ucParm + 1) == C_Key3s) )	/*调度按键3s消息*/
	{
		SF_Cardor3sCloseRelayTask_Relay();	
	}
	else if( (*pV_ucParm == Pt_Dispatch_Timing) && (pStr_Msg_Parameter->Length == Pt_Dispatch_Timing_Len + 1) )	/*调度时间消息*/
	{
		if(*(pV_ucParm + 1) == C_HalfSecond)	/*调度基本节拍500ms	*/
		{
			SF_TimeTask_Relay();	
		}	
		else if(*(pV_ucParm + 1) == C_SystemSecondChange)	/*调度系统秒变化	*/
		{
			SF_Event_RelayCheck_Relay();	
		}
	}
	return;	
}

/*******************************************************************************
函数原型：void SF_LocalControl_Relay(uchar8 V_RelayOrder)
功能描述：本地表电量触发消息处理
输入参数：V_RelayOrder，本地继电器控制命令
输出参数：无
返回参数：无
调用位置：该函数由Msg_Deal_RelayStatus函数调用
备    注：电量模块触发继电器命令消息时调用
*******************************************************************************/
void SF_LocalControl_Relay(uchar8 V_ucRelayOrder)
{
	uchar8	V_ucOperaterCode[4] = {0xFF, 0xFF, 0xFF, 0xFF};
	uchar8	V_ucRelayType;
	uchar8	V_ucPreWarningStatus;
	uchar8	V_ucRelayOrderStatus;
	uchar8	V_ucDataBuff[5];
	ushort16	V_usDataCRC;
	ushort16	V_usDataLength;
	ushort16	V_usDataEncode = 0;
	
	V_usDataLength = CLRelay_LocalOrder;
	InF_Read_Data(CRelay_LocalOrder, &Local_RelayOrder.PreWarning, &V_usDataLength, &V_usDataEncode);	/*读取本地控制命令*/
	
	V_usDataLength = CLRelay_RemoteOrder;
	InF_Read_Data(CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, &V_usDataLength, &V_usDataEncode);	/*读取远程控制命令*/
	
	V_usDataLength = CLRelay_State;
	InF_Read_Data(CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, &V_usDataLength, &V_usDataEncode);	/*读取继电器状态*/
	
	V_ucRelayOrderStatus = Local_RelayOrder.RelayOrderStatus;	/*赋值本地继电器命令初值*/
	V_ucPreWarningStatus = Local_RelayOrder.PreWarning;	/*赋值继电器预跳闸报警命令初值*/
	
	switch(V_ucRelayOrder)
	{
		case C_Alarm:	/*报警*/
		{
			V_ucPreWarningStatus = C_PreWarning;
			SV_Relay_L_OpenFlag[0] = 0x00;	/*清预跳闸标识*/
		}break;
		
		case C_Alarm_Release:	/*报警解除*/
		{			
			V_ucPreWarningStatus = C_PreWarning_Release;
			SV_Relay_L_OpenFlag[0] = 0x00;	/*清预跳闸标识*/
		}break;	
		
		case C_AlarmOpenRelay:	/*预跳闸*/
		{
			if(Local_RelayOrder.RelayOrderStatus == C_Open)
			{
				break;	
			}
			if( (PF_Check_CRC(SV_Relay_L_OpenFlag, 3) == C_OK) && (SV_Relay_L_OpenFlag[0] == C_Pre_Open) )	
			{
				break;
			}
			
			if(Com_RelayOrder.Protect_Current == C_Protect_Current_Release)	/*保电解除*/
			{
				SF_Judge1D1EOrderStatus();	/*通信跳闸自动恢复命令处理*/
				SV_24HourDelayTimer = 0x00;	/*电流超过门限电流计时*/
				SV_RelayRework_Timer = 0x00;	/*重复动作定时器*/
				SV_RelayOpenAfterPowerUp = 0x00;	/*上电时条件合闸状态要先跳闸，上电置0x68，用过后清零*/
				SV_ClearFlag = 0x00;	/*电表清零标识*/
				if( (SV_RelayDisplayStatus&C_RelayStatusLEDTwinkle) == C_RelayStatusLEDTwinkle)
				{
					SF_RelayStatusLEDMsgSend_Relay(C_DisplayOff);	/*跳闸指示灯熄灭*/
				}
				
				PF_CopyDataBytes(V_ucOperaterCode, SV_ucRelayOperatorCode, 4);	/*操作者代码赋值*/
				
				SV_L_CloseRealyDelay_Time = C_L_CloseRealyDelay_Time;	/*条件合闸延时时间置初值*/
				
				V_ucRelayOrderStatus = C_Pre_Open;	
			}
			
			V_ucPreWarningStatus = C_PreWarning;	/*报警*/
			
			SV_Relay_L_OpenFlag[0] = C_Pre_Open;	/*保存预跳闸标识，收到保电解除命令时此标识有效则触发立即跳闸消息*/
			V_usDataCRC = PF_Cal_CRC(SV_Relay_L_OpenFlag, 1);
			PF_Ushort16ToBuffer2(&SV_Relay_L_OpenFlag[1], &V_usDataCRC);
		}break;
		
		case C_Relay_OpenNow:	/*立即跳闸*/
		{
			if(Local_RelayOrder.RelayOrderStatus == C_Open)	/*如果当前已经是立即跳闸状态，则直接退出*/
			{
				break;	
			}
			
			if(Com_RelayOrder.Protect_Current == C_Protect_Current_Release)	/*保电解除*/
			{
				SF_Judge1D1EOrderStatus();	/*通信跳闸自动恢复命令处理*/
				/*内部静态变量处理*/
				SV_L_CloseRealyDelay_Time = 0x00;	/*本地表本地一次跳闸后允许合闸延时时间*/
				SV_24HourDelayTimer = 0x00;	/*电流超过门限电流计时*/
				SV_RelayRework_Timer = 0x00;	/*重复动作定时器*/
				SV_RelayOpenAfterPowerUp = 0x00;	/*上电时条件合闸状态要先跳闸，上电置0x68，用过后清零*/
				SV_ClearFlag = 0x00;	/*电表清零标识*/
				if( (SV_RelayDisplayStatus&C_RelayStatusLEDTwinkle) == C_RelayStatusLEDTwinkle)
				{
					SF_RelayStatusLEDMsgSend_Relay(C_DisplayOff);	/*跳闸指示灯熄灭*/
				}
				
				PF_CopyDataBytes(V_ucOperaterCode, SV_ucRelayOperatorCode, 4);	/*操作者代码赋值*/
				V_ucRelayOrderStatus = C_Open;
			}
			V_ucPreWarningStatus = C_PreWarning;	/*报警*/
			SV_Relay_L_OpenFlag[0] = 0x00;	/*清预跳闸标识*/
		}break;	
		
		case C_Relay_Close_Direct:	/*合闸允许*/
		{
			SV_Relay_L_OpenFlag[0] = 0x00;	/*清预跳闸标识*/
			
			if( (Local_RelayOrder.RelayOrderStatus == C_Close_Direct)
				|| ( (Local_RelayOrder.RelayOrderStatus == C_Close_Allow) 
				&& (SV_L_CloseRealyDelay_Time == 0) ) )
			{
				break;	/*SV_L_CloseRealyDelay_Time == 0, 表示不是预跳闸的合闸允许。*/
			}
			
			if(Com_RelayOrder.Protect_Current == C_Protect_Current_Release)	/*保电解除*/
			{
				/*内部静态变量处理*/
				SV_L_CloseRealyDelay_Time = 0x00;	/*本地表本地一次跳闸后允许合闸延时时间*/
				SV_24HourDelayTimer = 0x00;	/*电流超过门限电流计时*/
				SV_RelayRework_Timer = 0x00;	/*重复动作定时器*/
				SV_RelayOpenAfterPowerUp = 0x00;	/*上电时条件合闸状态要先跳闸，上电置0x68，用过后清零*/
				SV_ClearFlag = 0x00;	/*电表清零标识*/
				if( (SV_RelayDisplayStatus&C_RelayStatusLEDTwinkle) == C_RelayStatusLEDTwinkle)
				{
					SF_RelayStatusLEDMsgSend_Relay(C_DisplayOff);	/*跳闸指示灯熄灭*/
				}
				PF_CopyDataBytes(V_ucOperaterCode, SV_ucRelayOperatorCode, 4);	/*操作者代码赋值*/
			}
			
			V_usDataLength = CLRelay_Type;
			InF_Read_Data(CRelay_Type, &V_ucRelayType, &V_usDataLength, &V_usDataEncode);	/*读取负荷开关类型*/
			if( (V_ucRelayType & C_Relay_Type) == 1)
			{
				V_ucRelayOrderStatus = C_Close_Direct;	/*控制命令置直接合闸*/
				
				if(Com_RelayOrder.RelayOrderStatus != C_Open)
				{
					SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*拉闸字符熄灭*/
				}
				if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
				{
					SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*背光关闭*/
				}
			}
			else
			{
				V_ucRelayOrderStatus = C_Close_Allow;	/*控制命令置允许合闸*/
				SV_LocalOrderNum = SF_GetNewOrderNum();	/*更新本地命令序号*/
				
				if(Com_RelayOrder.RelayOrderStatus != C_Open)
				{
					SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*拉闸字符熄灭*/

					if(Relay_Stutas.RelaytheoreticStatus == C_RelayOff)
					{				
						SF_RelayStatusLEDMsgSend_Relay(C_DisplayTwinkle);	/*跳闸指示灯闪烁*/
					}
				}
				if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
				{
					SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*背光关闭*/
				}
			}
		}break;
		
		case C_PurchaseOK:	/*充值成功*/
		{
#if 0
			if( ( (Local_RelayOrder.RelayOrderStatus == C_Pre_Open) || (Local_RelayOrder.RelayOrderStatus == C_Close_Allow) ) && (SV_L_CloseRealyDelay_Time != 0) )	/*当前处于本地预跳闸状态且条件合闸延时时间不为0*/
			{
				SV_L_CloseRealyDelay_Time = 0;
				
				V_usDataLength = CLRelay_Type;
				InF_Read_Data(CRelay_Type, &V_ucRelayType, &V_usDataLength, &V_usDataEncode);	/*读取负荷开关类型*/
				if( (V_ucRelayType & C_Relay_Type) == 1)
				{
					V_ucRelayOrderStatus = C_Close_Direct;	/*控制命令置直接合闸*/
					
					if(Com_RelayOrder.RelayOrderStatus != C_Open)
					{
						SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*拉闸字符熄灭*/
					}
				}
				else
				{
					V_ucRelayOrderStatus = C_Close_Allow;	/*控制命令置允许合闸*/
					SV_LocalOrderNum = SF_GetNewOrderNum();	/*更新本地命令序号*/
					
					if(Com_RelayOrder.RelayOrderStatus != C_Open)
					{
						SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*拉闸字符熄灭*/
				
						if(Relay_Stutas.RelaytheoreticStatus == C_RelayOff)
						{				
							SF_RelayStatusLEDMsgSend_Relay(C_DisplayTwinkle);	/*跳闸指示灯闪烁*/
						}
					}
					if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
					{
						SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*背光关闭*/
					}
				}
			}
#endif
			if( (Com_RelayOrder.RelayOrderStatus == C_Open_Direct) && (SV_Comm_CloseRealyDelay_Time != 0) )
			{
				SF_DealWithSV_Relay();	/*内部静态变量处理*/
				PF_CopyDataBytes(V_ucOperaterCode, SV_ucRelayOperatorCode, 4);	/*操作者代码赋值*/
				
				Com_RelayOrder.RelayOrderStatus = C_Close_Direct;
				InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, CLRelay_RemoteOrder, C_W_SafeFlag);	/*远程控制命令写数据层*/
				SV_ComOrderNum = SF_GetNewOrderNum();	/*更新远程命令序号*/
				
				if(Local_RelayOrder.RelayOrderStatus != C_Open)
				{
					SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*拉闸字符熄灭*/
				}
				
				if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
				{
					SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*背光关闭*/
				}
					
				V_usDataLength = CLMeter_Work_State3;
				InF_Read_Data(CMeter_Work_State3, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*读取电表运行状态字3*/
				V_ucDataBuff[0] &= C_RelayOrderStatusOn;	/*继电器命令导通*/
				InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State3, &V_ucDataBuff[0], CLMeter_Work_State3, C_W_SafeFlag);	/*电表运行状态字3写数据层*/
			}
			if( (Com_RelayOrder.RelayOrderStatus == C_Open_Allow) && (SV_Comm_CloseRealyDelay_Time != 0) )
			{
				SF_DealWithSV_Relay();	/*内部静态变量处理*/
				PF_CopyDataBytes(V_ucOperaterCode, SV_ucRelayOperatorCode, 4);	/*操作者代码赋值*/
				
				V_usDataLength = CLRelay_Type;
				InF_Read_Data(CRelay_Type, &V_ucRelayType, &V_usDataLength, &V_usDataEncode);	/*读取负荷开关类型*/
				if( (V_ucRelayType & C_Relay_Type) == 1)
				{
					Com_RelayOrder.RelayOrderStatus = C_Close_Direct;	/*远程控制命令置直接合闸*/
					InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, CLRelay_RemoteOrder, C_W_SafeFlag);	/*远程控制命令写数据层*/
					
					if(Local_RelayOrder.RelayOrderStatus != C_Open)
					{
						SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*拉闸字符熄灭*/
					}
					
					if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
					{
						SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*背光关闭*/
					}
				}
				else
				{
					Com_RelayOrder.RelayOrderStatus = C_Close_Allow;
					InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, CLRelay_RemoteOrder, C_W_SafeFlag);	/*远程控制命令写数据层*/
					SV_ComOrderNum = SF_GetNewOrderNum();	/*更新远程命令序号*/
					
					if(Local_RelayOrder.RelayOrderStatus != C_Open)
					{
						SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*拉闸字符熄灭*/
						
						if(Relay_Stutas.RelaytheoreticStatus == C_RelayOff)
						{
							SF_RelayStatusLEDMsgSend_Relay(C_DisplayTwinkle);	/*跳闸指示灯闪烁*/
						}	
					}
					
					if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
					{
						SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*背光关闭*/
					}	
				}
				
				V_usDataLength = CLMeter_Work_State3;
				InF_Read_Data(CMeter_Work_State3, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*读取电表运行状态字3*/
				V_ucDataBuff[0] &= C_RelayOrderStatusOn;	/*继电器命令导通*/
				InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State3, &V_ucDataBuff[0], CLMeter_Work_State3, C_W_SafeFlag);	/*电表运行状态字3写数据层*/
			}
		}break;
		
		case C_Relay_Close_Direct_Init:	/*合闸*/
		{
			SV_Relay_L_OpenFlag[0] = 0x00;	/*清预跳闸标识*/
			
			if(Com_RelayOrder.Protect_Current == C_Protect_Current_Release)	/*保电解除*/
			{
				/*内部静态变量处理*/
				SV_L_CloseRealyDelay_Time = 0x00;	/*本地表本地一次跳闸后允许合闸延时时间*/
				SV_24HourDelayTimer = 0x00;	/*电流超过门限电流计时*/
				SV_RelayRework_Timer = 0x00;	/*重复动作定时器*/
				SV_RelayOpenAfterPowerUp = 0x00;	/*上电时条件合闸状态要先跳闸，上电置0x68，用过后清零*/
				if( (SV_RelayDisplayStatus&C_RelayStatusLEDTwinkle) == C_RelayStatusLEDTwinkle)
				{
					SF_RelayStatusLEDMsgSend_Relay(C_DisplayOff);	/*跳闸指示灯熄灭*/
				}
				
				PF_CopyDataBytes(V_ucOperaterCode, SV_ucRelayOperatorCode, 4);	/*操作者代码赋值*/
			}

			V_ucRelayOrderStatus = C_Close_Direct;	/*控制命令置直接合闸*/
			SV_LocalOrderNum = SF_GetNewOrderNum();	/*更新本地命令序号*/
				
			if(Com_RelayOrder.RelayOrderStatus != C_Open)
			{
				SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*拉闸字符熄灭*/
			}
			if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
			{
				SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*背光关闭*/
			}
		}break;
		
		default:
		{

		}break;	
	}

	if(Local_RelayOrder.RelayOrderStatus != V_ucRelayOrderStatus)
	{
		Local_RelayOrder.RelayOrderStatus = V_ucRelayOrderStatus;
		InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_LocalOrder, &Local_RelayOrder.PreWarning, CLRelay_LocalOrder, C_W_SafeFlag);	/*本地控制命令写数据层*/
	}
	if(Local_RelayOrder.PreWarning != V_ucPreWarningStatus)
	{
		Local_RelayOrder.PreWarning = V_ucPreWarningStatus;
		InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_LocalOrder, &Local_RelayOrder.PreWarning, CLRelay_LocalOrder, C_W_SafeFlag);	/*本地控制命令写数据层*/
	}	

	return;
}

/*******************************************************************************
函数原型：uchar8 SF_JudgeCurrent_Relay(void)
功能描述：电流门限值判断
输入参数：无
输出参数：无
返回参数：C_CurrentOk，当前电流值均小于门限电流，允许跳闸；C_CurrentOver，当前三相电流中有超过门限电流值的，不允许跳闸
调用位置：
备    注：1）收到跳闸命令后调用该函数并判断当前电流是否允许跳闸（设置拉闸控制电流门限保护延时时间）
          2）在跳闸之前调用该函数判断是否符合跳闸要求
*******************************************************************************/
uchar8 SF_JudgeCurrent_Relay(void)
{
	uchar8	V_ucCurrent[15];
	uchar8	V_ucData[4];
	uchar8	V_ucRelayType;
	uchar8	V_ucReturnFlag;
	ulong32	V_lRelay_OpenCurrTreshold;
	long32	V_lCurrentHEX_ABC[3];
	ushort16	V_usDataLength;
	ushort16	V_usDataEncode = 0;

	V_ucReturnFlag = C_CurrentOk;

	V_usDataLength = CLRelay_Type;
	InF_Read_Data(CRelay_Type, &V_ucRelayType, &V_usDataLength, &V_usDataEncode);	/*读取负荷开关类型*/
	if( (V_ucRelayType & C_Relay_Type) == 0)	/*开关外置表不受门限值限制*/
	{
		V_usDataLength = CLRelay_Open_CurrTreshold;
		if(InF_Read_Data(CRelay_Open_CurrTreshold, V_ucData, &V_usDataLength, &V_usDataEncode) != C_OK)	/*读取继电器拉闸控制电流门限值*/
		{
			V_lRelay_OpenCurrTreshold = 0;
		}
		else
		{
			PF_BufferXToUlong32(&V_ucData[0], (ulong32 *)&V_lRelay_OpenCurrTreshold, V_usDataLength);			
		}
		if(V_lRelay_OpenCurrTreshold == 0)
		{
			return V_ucReturnFlag;	/*门限电流值为0，该功能不启用*/
		}

		V_usDataLength = CLPhaseFF_Curr_4Dig;
		InF_Read_Data(CPhaseFF_Curr_4Dig, V_ucCurrent, &V_usDataLength, &V_usDataEncode);	/*读取电流值*/
		PF_BufferXToUlong32(&V_ucCurrent[0], (ulong32 *)&V_lCurrentHEX_ABC[0], CLPhaseA_Curr_4Dig);
		V_lCurrentHEX_ABC[0] = SF_ABS(V_lCurrentHEX_ABC[0]);
		PF_BufferXToUlong32(&V_ucCurrent[4], (ulong32 *)&V_lCurrentHEX_ABC[1], CLPhaseB_Curr_4Dig);
		V_lCurrentHEX_ABC[1] = SF_ABS(V_lCurrentHEX_ABC[1]);
		PF_BufferXToUlong32(&V_ucCurrent[8], (ulong32 *)&V_lCurrentHEX_ABC[2], CLPhaseC_Curr_4Dig);
		V_lCurrentHEX_ABC[2] = SF_ABS(V_lCurrentHEX_ABC[2]);

		if( (V_lCurrentHEX_ABC[0] > V_lRelay_OpenCurrTreshold) || (V_lCurrentHEX_ABC[1] > V_lRelay_OpenCurrTreshold) || (V_lCurrentHEX_ABC[2] > V_lRelay_OpenCurrTreshold) )
		{
			V_ucReturnFlag = C_CurrentOver;	/*任意一相电流大于门限值 返回错误*/
		}
	}
	
	return V_ucReturnFlag;
}

/*******************************************************************************
函数原型：void SF_Event_CloseRelay_Relay(void)
功能描述：写合闸记录
输入参数：无
输出参数：无
返回参数：无
调用位置：该函数由SF_CombineOrderExecute_Relay私有函数调用
备    注：
*******************************************************************************/
void SF_Event_CloseRelay_Relay(void)
{
	uchar8	V_ucDataBuff[300] = {0};
	uchar8	V_ucEventFlag;
	ushort16	V_usOffset = 0, V_usResidualLength;
	ushort16	V_usDataLength;
	ushort16	V_usDataEncode = 0;
	
	V_usDataLength = CLRelayClose_Degree;
	InF_Read_Data(CRelayClose_Degree, V_ucDataBuff, &V_usDataLength, &V_usDataEncode);	/*赋事件序号*/
	V_usOffset += 4;
	
	V_usDataLength = CLDate_Week_Time;
	InF_Read_Data(CDate_Time, &V_ucDataBuff[V_usOffset], &V_usDataLength, &V_usDataEncode);	/*赋事件发生时间，结束时间为00000000000000*/
	V_usOffset += 7;
	V_usOffset += 7;
	V_usOffset += 1;	/*发生源赋空*/
	V_usOffset += 1;	/*上报状态赋空*/
	
	V_usResidualLength = 300 - V_usOffset;	/*剩余buff长度*/
	V_ucEventFlag = 0x01;
	if(Inf_GetRecordData(&V_ucDataBuff[V_usOffset], &V_usResidualLength, CRelayClose_OADTab, V_ucEventFlag) != C_OK)	/*获取关联OAD数据*/
	{
		return;
	}
	V_usOffset += V_usResidualLength;	/*数据总长度*/

	InF_Write_Data(C_Msg_Deal_RelayStatus, CRelayClose_FF_1, V_ucDataBuff, V_usOffset, C_W_SafeFlag);	/*写合闸记录*/
	Inf_EventReport_HP(C_RelayCloseEventNo, C_Happen_EventReport);

	return;
}

/*******************************************************************************
函数原型：void SF_Event_OpenRelay_Relay(void)
功能描述：写跳闸记录
输入参数：无
输出参数：无
返回参数：无
调用位置：该函数由SF_CombineOrderExecute_Relay私有函数调用
备    注：
*******************************************************************************/
void SF_Event_OpenRelay_Relay(void)
{
	uchar8	V_ucDataBuff[300] = {0};
	uchar8	V_ucEventFlag;
	ushort16	V_usOffset = 0, V_usResidualLength;
	ushort16	V_usDataLength;
	ushort16	V_usDataEncode = 0;

	V_usDataLength = CLRelayOpen_Degree;
	InF_Read_Data(CRelayOpen_Degree, V_ucDataBuff, &V_usDataLength, &V_usDataEncode);	/*赋事件序号*/
	V_usOffset += 4;
	
	V_usDataLength = CLDate_Week_Time;
	InF_Read_Data(CDate_Time, &V_ucDataBuff[V_usOffset], &V_usDataLength, &V_usDataEncode);	/*赋事件发生时间，结束时间为00000000000000*/
	V_usOffset += 7;
	V_usOffset += 7;
	V_usOffset += 1;	/*发生源赋空*/
	V_usOffset += 1;	/*上报状态赋空*/
	
	V_usResidualLength = 300 - V_usOffset;	/*剩余buff长度*/
	V_ucEventFlag = 0x01;
	if(Inf_GetRecordData(&V_ucDataBuff[V_usOffset], &V_usResidualLength, CRelayOpen_OADTab, V_ucEventFlag) != C_OK)	/*获取关联OAD数据*/
	{
		return;
	}
	V_usOffset += V_usResidualLength;	/*数据总长度*/
	
	InF_Write_Data(C_Msg_Deal_RelayStatus, CRelayOpen_FF_1, V_ucDataBuff, V_usOffset, C_W_SafeFlag);	/*写跳闸记录*/
	Inf_EventReport_HP(C_RelayOpenEventNo, C_Happen_EventReport);
	
	return;
}

/*******************************************************************************
函数原型：void SF_Event_RelayCheck_Relay(void)
功能描述：负荷开关误动作
输入参数：无
输出参数：无
返回参数：无
调用位置：该函数由Msg_Deal_RelayStatus函数调用
备    注：调度系统秒变化调用该函数
*******************************************************************************/
void SF_Event_RelayCheck_Relay(void)
{
	uchar8	V_ucStartTime[7] = {0};
	uchar8	V_ucEndTime[7] = {0};
	uchar8	V_ucDataBuff[8] = {0};
	uchar8	V_ucPhaseFF_Volage[6];
	uchar8	V_ucRelayType;
	uchar8	V_ucEventStatus;
	uchar8	V_ucDataBuff1[5];
	uchar8	V_ucDataBuff2[300] = {0};
	uchar8	V_ucEventFlag;
	ulong32	V_ucReadOAD_Hp[3], V_ucReadOAD_End[3];
	ushort16	V_usRelayOpenVol_Lim[2];	/*电源异常电压下限, 上限*/
	ushort16	V_usVoltageHEX_ABC[3];	/*ABC三相电压*/
	ushort16	V_usDataCRC;
	ushort16	V_usOffset = 0, V_usResidualLength, V_usHPTime_Len;
	ushort16	V_usDataLength;
	ushort16	V_usDataEncode = 0;
    uchar8  V_ucTemp[2] = {9, 1};
	Str_Read_T V_Str_ReadRecord;

	
	V_usDataLength = CLRelay_Type;
	InF_Read_Data(CRelay_Type, &V_ucRelayType, &V_usDataLength, &V_usDataEncode);	/*读取负荷开关类型*/
	
	V_usDataLength = CLRelay_State;
	InF_Read_Data(CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, &V_usDataLength, &V_usDataEncode);	/*读取继电器状态*/
	
	V_ucReadOAD_Hp[0] = CRelayFa_Note_1;
	V_ucReadOAD_Hp[1] = CEventHPTime;
	V_ucReadOAD_Hp[2] = 0xFFFFFFFF;
	V_ucReadOAD_End[0] = CRelayFa_Note_1;
	V_ucReadOAD_End[1] = CEventEndTime;
	V_ucReadOAD_End[2] = 0xFFFFFFFF;
	
	V_usHPTime_Len = CLEventHPTime;
	V_Str_ReadRecord.pV_ulROAD = &V_ucReadOAD_Hp[0];
	V_Str_ReadRecord.pV_ucRST = &V_ucTemp[0];       /*方法9*//*读取上1次*/
	V_Str_ReadRecord.V_usROAD_Num = 1;              /*关联属性1个*/
	V_Str_ReadRecord.V_ucReadMode = C_OtherMode;    /*模块内部读取*/
	V_Str_ReadRecord.V_ucChannelNo = 0xFF;          /*非通信读取*/
	InF_GetData_Record(&V_Str_ReadRecord, &V_ucStartTime[0], &V_usHPTime_Len, C_NULL);      /*读取上1次负荷开关误动作发生时刻*/

	V_usHPTime_Len = CLEventEndTime;
    V_Str_ReadRecord.pV_ulROAD = &V_ucReadOAD_End[0];
	InF_GetData_Record(&V_Str_ReadRecord, &V_ucEndTime[0], &V_usHPTime_Len, C_NULL);        /*读取上1次负荷开关误动作结束时刻*/

	
	if( (PF_Campare_Data(V_ucStartTime, V_ucDataBuff, CLEventHPTime) != C_Equal) && (PF_Campare_Data(V_ucEndTime, V_ucDataBuff, CLEventEndTime) == C_Equal) )
	{
		V_ucEventStatus = C_EventOnlyStart;	/*当前为有发生无结束*/
	}
	else
	{
		V_ucEventStatus = C_EventNotOnlyStart;	/*当前不是有发生无结束*/
	}
		
	V_usDataLength = CLVolage_Abnor_Vol;
	InF_Read_Data(CVolage_Abnor_Vol, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*电源异常电压下限, 上限*/
	PF_Buffer2ToUshort16(&V_ucDataBuff[0], &V_usRelayOpenVol_Lim[0]);	/*电源异常电压下限*/
	PF_Buffer2ToUshort16(&V_ucDataBuff[2], &V_usRelayOpenVol_Lim[1]);	/*电源异常电压上限*/
	
	V_usDataLength = CLPhaseFF_Volage;
	InF_Read_Data(CPhaseFF_Volage, &V_ucPhaseFF_Volage[0], &V_usDataLength, &V_usDataEncode);	/*ABC电压*/
	PF_Buffer2ToUshort16(&V_ucPhaseFF_Volage[0], &V_usVoltageHEX_ABC[0]);
	PF_Buffer2ToUshort16(&V_ucPhaseFF_Volage[2], &V_usVoltageHEX_ABC[1]);
	PF_Buffer2ToUshort16(&V_ucPhaseFF_Volage[4], &V_usVoltageHEX_ABC[2]);
	
	if( ( (V_usVoltageHEX_ABC[0] >= V_usRelayOpenVol_Lim[0]) && (V_usVoltageHEX_ABC[0] <= V_usRelayOpenVol_Lim[1]) )	/*A相电压处于电源异常电压上限和下限之间*/
		|| ( (V_usVoltageHEX_ABC[1] >= V_usRelayOpenVol_Lim[0]) && (V_usVoltageHEX_ABC[1] <= V_usRelayOpenVol_Lim[1]) )	/*B相电压处于电源异常电压上限和下限之间*/
		|| ( (V_usVoltageHEX_ABC[2] >= V_usRelayOpenVol_Lim[0]) && (V_usVoltageHEX_ABC[2] <= V_usRelayOpenVol_Lim[1]) ) )	/*C相电压处于电源异常电压上限和下限之间*/
	{
		SV_Error_Time++;
		if(Relay_Stutas.RelaytheoreticStatus == Relay_Stutas.RelayRealStatus)	
		{
			if(V_ucEventStatus != C_EventOnlyStart)
			{
				SV_Error_Time = 0x00;
				
				V_usDataLength = CLMeter_Work_State1;
				InF_Read_Data(CMeter_Work_State1, &V_ucDataBuff1[0], &V_usDataLength, &V_usDataEncode);	/*读取电表运行状态字1*/
				if( (V_ucDataBuff1[1]&C_ControlLoopError) == C_ControlLoopError)
				{
					V_ucDataBuff1[1] &= C_ControlLoopNoError;	/*无控制回路错*/
					InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State1, &V_ucDataBuff1[0], CLMeter_Work_State1, C_W_SafeFlag);	/*电表运行状态字1写数据层*/
				}
			}	
			if(SV_Error_Time > C_Error_Time)
			{
				SV_Error_Time = 0x00;
				
				V_usDataLength = CLMeter_Work_State1;
				InF_Read_Data(CMeter_Work_State1, &V_ucDataBuff1[0], &V_usDataLength, &V_usDataEncode);	/*读取电表运行状态字1*/
				V_ucDataBuff1[1] &= C_ControlLoopNoError;	/*无控制回路错*/
				InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State1, &V_ucDataBuff1[0], CLMeter_Work_State1, C_W_SafeFlag);	/*电表运行状态字1写数据层*/
				
				V_usDataLength = CLRelayFa_Degree;
				InF_Read_Data(CRelayFa_Degree, &V_ucDataBuff2[0], &V_usDataLength, &V_usDataEncode);	/*读取发生次数*/
				V_usOffset += 4;
				PF_CopyDataBytes(V_ucStartTime, &V_ucDataBuff2[V_usOffset], CLEventHPTime);	/*发生时间*/
				V_usOffset += 7;
				V_usDataLength = CLEventEndTime;
				InF_Read_Data(CDate_Time, &V_ucDataBuff2[V_usOffset], &V_usDataLength, &V_usDataEncode);	/*读取当前时间，即事件结束时间*/
				V_usOffset += 7;
				V_usOffset += 1;
				V_usOffset += 1;	/*上报状态赋空*/
				V_usResidualLength = 300 - V_usOffset;	/*剩余buff长度*/
				V_ucEventFlag = 0x02;
				
				if(Inf_GetRecordData(&V_ucDataBuff2[V_usOffset], &V_usResidualLength, CRelayFa_OADTab, V_ucEventFlag) != C_OK)	/*获取关联OAD数据*/
				{
					return;
				}
				V_usOffset += V_usResidualLength;	/*数据总长度*/
				InF_Write_Data(C_Msg_Deal_RelayStatus, CRelayFa_Note_1 + 0x00000001, V_ucDataBuff2, V_usOffset, C_W_SafeFlag);	/*事件结束写数据*/

				Inf_EventReport_HP(C_RelayFaEndEnEventNo, C_End_EventReport);
			}
		}
		else
		{
			if(V_ucEventStatus == C_EventOnlyStart)	/*当前误动作已经发生时，定时器清零*/
			{
				SV_Error_Time = 0x00;	
			}
			
			if(SV_Error_Time > C_Error_Time)
			{
				SV_Error_Time = 0x00;
						
				V_usDataLength = CLMeter_Work_State1;
				InF_Read_Data(CMeter_Work_State1, &V_ucDataBuff1[0], &V_usDataLength, &V_usDataEncode);	/*读取电表运行状态字1*/
				V_ucDataBuff1[1] |= C_ControlLoopError;	/*控制回路错*/
				InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State1, &V_ucDataBuff1[0], CLMeter_Work_State1, C_W_SafeFlag);	/*电表运行状态字1写数据层*/
			
				if( ( (V_ucRelayType & C_Relay_Type) == 1) && (Relay_Stutas.RelaytheoreticStatus == C_RelayOn) )	/*外置表，合闸状态时不记负荷开关误动作*/
				{
					SV_Error_Time = 0x00;
					return;	
				}	
				
				if(Relay_Stutas.RelayRealStatus == C_RelayOff)
				{
					if( (PF_Check_CRC(SV_EventOut_Err_Relay, 3) == C_OK) && (SV_EventOut_Err_Relay[0] == C_EventOutCloseErr_Relay) )	
					{
						V_usDataLength = CLRelayFa_Degree;
						InF_Read_Data(CRelayFa_Degree, &V_ucDataBuff2[0], &V_usDataLength, &V_usDataEncode);	/*读取发生次数*/
						V_usOffset += 4;
						V_usDataLength = CLEventHPTime;
						InF_Read_Data(CDate_Time, &V_ucDataBuff2[V_usOffset], &V_usDataLength, &V_usDataEncode);	/*读取当前时间，即事件发生时间，事件结束时间为0000000*/
						V_usOffset += 7;
						V_usOffset += 7;
						V_usOffset += 1;	/*发生源赋空*/
						V_usOffset += 1;	/*上报状态赋空*/
						V_usResidualLength = 300 - V_usOffset;	/*剩余buff长度*/
						V_ucEventFlag = 0x01;
						
						if(Inf_GetRecordData(&V_ucDataBuff2[V_usOffset], &V_usResidualLength, CRelayFa_OADTab, V_ucEventFlag) != C_OK)	/*获取关联OAD数据*/
						{
							return;
						}

						V_usOffset += V_usResidualLength;	/*数据总长度*/
						InF_Write_Data(C_Msg_Deal_RelayStatus, CRelayFa_Note_1, V_ucDataBuff2, V_usOffset, C_W_SafeFlag);	/*事件结束写数据*/

						Inf_EventReport_HP(C_RelayFaEndEnEventNo, C_Happen_EventReport);
						
						SV_EventOut_Err_Relay[0] = C_EventOutNot_Relay;	
						V_usDataCRC = PF_Cal_CRC(SV_EventOut_Err_Relay, 1);
						PF_Ushort16ToBuffer2(&SV_EventOut_Err_Relay[1], &V_usDataCRC);		
					}
				}
				else
				{
					if( (PF_Check_CRC(SV_EventOut_Err_Relay, 3) == C_OK) && (SV_EventOut_Err_Relay[0] == C_EventOutOpenErr_Relay) )
					{
						V_usDataLength = CLRelayFa_Degree;
						InF_Read_Data(CRelayFa_Degree, &V_ucDataBuff2[0], &V_usDataLength, &V_usDataEncode);	/*读取发生次数*/
						V_usOffset += 4;
						V_usDataLength = CLEventHPTime;
						InF_Read_Data(CDate_Time, &V_ucDataBuff2[V_usOffset], &V_usDataLength, &V_usDataEncode);	/*读取当前时间，即事件发生时间，事件结束时间为0000000*/
						V_usOffset += 7;
						V_usOffset += 7;
						V_usOffset += 1;	/*发生源赋空*/
						V_usOffset += 1;	/*上报状态赋空*/
						V_usResidualLength = 300 - V_usOffset;	/*剩余buff长度*/
						V_ucEventFlag = 0x01;
						
						if(Inf_GetRecordData(&V_ucDataBuff2[V_usOffset], &V_usResidualLength, CRelayFa_OADTab, V_ucEventFlag) != C_OK)	/*获取关联OAD数据*/
						{
							return;
						}
						V_usOffset += V_usResidualLength;	/*数据总长度*/
						InF_Write_Data(C_Msg_Deal_RelayStatus, CRelayFa_Note_1, V_ucDataBuff2, V_usOffset, C_W_SafeFlag);	/*事件结束写数据*/
						
						Inf_EventReport_HP(C_RelayFaEndEnEventNo, C_Happen_EventReport);

#if 0						
						InF_ActiveReportSetting(C_Times_ContralLoopErr);	/*主动上报*/
#endif

						SV_EventOut_Err_Relay[0] = C_EventOutNot_Relay;	
						V_usDataCRC = PF_Cal_CRC(SV_EventOut_Err_Relay, 1);
						PF_Ushort16ToBuffer2(&SV_EventOut_Err_Relay[1], &V_usDataCRC);
					}
				}
			}	
		}
	}
	else
	{
		SV_Error_Time = 0x00;	
	}

	return;
}

/*******************************************************************************
函数原型：uchar8 SF_GetRelay0nOffStatus(void)
功能描述：获取外置继电器状态
输入参数：无
输出参数：无
返回参数：无
调用位置：该函数由SF_TimeTask_Relay函数调用
备    注：SF_TimeTask_Relay每500ms调用一次，其他任何功能模块不允许调用
*******************************************************************************/
void SF_GetRelay0nOffStatus(void)
{
	uchar8	V_ucExternalRelayStatus = C_Invalid;
	uchar8	V_ucRelayType;
	ushort16	V_usDataLength;
	ushort16	V_usDataEncode = 0;
		
	V_usDataLength = CLRelay_Type;
	InF_Read_Data(CRelay_Type, &V_ucRelayType, &V_usDataLength, &V_usDataEncode);	/*读取负荷开关类型*/

	if( (V_ucRelayType & C_Relay_Type ) == 1)	/*开关外置表*/	/*wxy数字需消除*/
	{
		if( (V_ucRelayType & C_RelayFbackLine_Type ) != 0)	/*220、380V外置表有继电器反馈线*/
		{
			V_ucExternalRelayStatus = InF_GetPeripheralStatus(C_ExternalRelayStatus); 
		}
	}
	SV_ExternalRelayStatus = V_ucExternalRelayStatus;	/*开关内置的不管*/
}

/*******************************************************************************
函数原型：void SF_RelayStatusCheck_Relay(void)
功能描述：继电器实际状态判断
输入参数：无
输出参数：无
返回参数：无
调用位置：该函数由SF_TimeTask_Relay函数调用
备    注：SF_TimeTask_Relay每500ms调用一次，其他任何功能模块不允许调用
*******************************************************************************/
void SF_RelayStatusCheck_Relay(void)
{
	uchar8	V_ucDataBuff[2];
	uchar8	V_ucRelayType, V_ucBuiltinType;
	uchar8	V_ucInstantFF_AcPow[CLInstantFF_AcPow];
	uchar8	V_ucData[5];
	long32	V_lStartUpPower;
	long32	V_lInstantABCHEX_AcPow[3];
	ushort16	V_usDataCRC;
	ushort16	V_usDataLength;
	ushort16	V_usDataEncode = 0;

	V_usDataLength = CLRelay_Type;
	InF_Read_Data(CRelay_Type, &V_ucRelayType, &V_usDataLength, &V_usDataEncode);	/*读取负荷开关类型*/

	V_usDataLength = CLInstantFF_AcPow;
	InF_Read_Data(CInstantFF_AcPow, V_ucInstantFF_AcPow, &V_usDataLength, &V_usDataEncode);	/*读取瞬时有功功率数据块*/
	PF_BufferXToUlong32(&V_ucInstantFF_AcPow[4], (ulong32 *)&V_lInstantABCHEX_AcPow[0], CLInstantA_AcPow);
	PF_BufferXToUlong32(&V_ucInstantFF_AcPow[8], (ulong32 *)&V_lInstantABCHEX_AcPow[1], CLInstantB_AcPow);
	PF_BufferXToUlong32(&V_ucInstantFF_AcPow[12], (ulong32 *)&V_lInstantABCHEX_AcPow[2], CLInstantC_AcPow);

	V_usDataLength = CLStart_Up_Power;
	InF_Read_Data(CStart_Up_Power, V_ucData, &V_usDataLength, &V_usDataEncode);	/*读取功率灭零阀值 20150831 lzy*/
	PF_BufferXToUlong32(&V_ucData[0], (ulong32 *)&V_lStartUpPower, CLStart_Up_Power);
	V_lStartUpPower = SF_ABS(V_lStartUpPower / 3);

	V_usDataLength = CLRelay_State;
	InF_Read_Data(CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, &V_usDataLength, &V_usDataEncode);	/*读取继电器状态*/
	
	V_usDataLength = CLMeter_Work_State3;
	InF_Read_Data(CMeter_Work_State3, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*读取电表运行状态字3*/

	if( (V_ucRelayType & C_Relay_Type) == 1)
	{
		if( (Relay_Stutas.RelaytheoreticStatus == C_RelayOn)
			&& (Relay_Stutas.RelayRealStatus == C_RelayOn ) )
		{
			V_ucDataBuff[0] &= C_RelayStatusOn;	/*继电器导通*/
		}
		else
		{
			if( (V_ucRelayType & C_RelayFbackLine_Type ) != 0)	/*220、380V外置表有继电器反馈线*/
			{
				if( (SF_ABS(V_lInstantABCHEX_AcPow[0]) > V_lStartUpPower)
					|| (SF_ABS(V_lInstantABCHEX_AcPow[1]) > V_lStartUpPower)
					|| (SF_ABS(V_lInstantABCHEX_AcPow[2]) > V_lStartUpPower)
					|| (SV_ExternalRelayStatus == C_Valid ) )
				{
					SV_RelayCheckStatus &= C_RelayRealOn;	/*导通*/
				}
				else
				{
					SV_RelayCheckStatus |= C_RelayRealOff;		/*断开*/
				}
			}
			else
			{
				if( (SF_ABS(V_lInstantABCHEX_AcPow[0]) > V_lStartUpPower)
					|| (SF_ABS(V_lInstantABCHEX_AcPow[1]) > V_lStartUpPower)
					|| (SF_ABS(V_lInstantABCHEX_AcPow[2]) > V_lStartUpPower) )
				{
					SV_RelayCheckStatus &= C_RelayRealOn;	/*导通*/
				}
				else
				{
					SV_RelayCheckStatus |= C_RelayRealOff;		/*断开*/
				}
			}
		
			if( (SV_RelayCheckStatus & 0x01 ) == 0x01)
			{
				V_ucDataBuff[0] |= C_RelayStatusOff;	/*继电器断开*/
			}
			else if( (SV_RelayCheckStatus & 0x01 ) == 0x00)
			{
				V_ucDataBuff[0] &= C_RelayStatusOn;	/*继电器导通*/
			}
		}
	}
	else
	{
		V_ucBuiltinType = InF_GetPeripheralStatus(C_RelayStatus);                         

		if( ( (SF_ABS(V_lInstantABCHEX_AcPow[0]) > V_lStartUpPower)
			|| (SF_ABS(V_lInstantABCHEX_AcPow[1]) > V_lStartUpPower)
			|| (SF_ABS(V_lInstantABCHEX_AcPow[2]) > V_lStartUpPower) )
			|| (V_ucBuiltinType == C_Valid ) )
		{
			SV_RelayCheckStatus &= C_RelayRealOn;	/*导通*/
		}
		else
		{
			SV_RelayCheckStatus |= C_RelayRealOff;	/*断开*/
		}
		if( (SV_RelayCheckStatus & 0x01) == 0x01)
		{
			V_ucDataBuff[0] |= C_RelayStatusOff;	/*继电器断开*/
		}
		else if( (SV_RelayCheckStatus & 0x01 ) == 0x00)
		{	
			V_ucDataBuff[0] &= C_RelayStatusOn;	/*继电器导通*/
		}	
	}
	
	if( ( V_ucDataBuff[0] & C_RelayStatusOff ) == C_RelayStatusOff )
	{
		if(Relay_Stutas.RelayRealStatus != C_RelayOff)
		{
			Relay_Stutas.RelayRealStatus = C_RelayOff;	/*置继电器实际状态断开*/
			InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, CLRelay_State, C_W_SafeFlag);	/*继电器状态写数据层*/
		}
		if(Relay_Stutas.RelaytheoreticStatus == C_RelayOff)
		{
			if( (PF_Check_CRC(SV_EventOut_Open_Relay, 3) == C_OK ) && ( SV_EventOut_Open_Relay[0] == C_EventOut_Relay) )
			{
				/*跳闸成功主动上报*/
				InF_ActiveReportSetting(C_Times_OpenRelay);
				Inf_WriteMeterStatus8(C_RelayOpenEventNo);
				
				SV_EventOut_Open_Relay[0] = C_EventOutNot_Relay;	/*表示不需要上报跳闸成功事件*/
				V_usDataCRC = PF_Cal_CRC(SV_EventOut_Open_Relay, 1);
				PF_Ushort16ToBuffer2(&SV_EventOut_Open_Relay[1], &V_usDataCRC); 
			}
		}
		
		if( ( (SV_RelayDisplayStatus & C_RelayStatusLEDTwinkle) != C_RelayStatusLEDTwinkle)
			 && ( (SV_RelayDisplayStatus & C_RelayStatusLEDOn) != C_RelayStatusLEDOn) )
		{
			SF_RelayStatusLEDMsgSend_Relay(C_DisplayOn);	/*跳闸指示灯点亮*/
		}	
	}
	else if( (V_ucDataBuff[0] & C_RelayStatusOff) != C_RelayStatusOff)
	{
		if(Relay_Stutas.RelayRealStatus != C_RelayOn)
		{
			Relay_Stutas.RelayRealStatus = C_RelayOn;	/*置继电器实际状态导通*/
			InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, CLRelay_State, C_W_SafeFlag);	/*继电器状态写数据层*/
		}
		if(Relay_Stutas.RelaytheoreticStatus == C_RelayOn)
		{
			if( (PF_Check_CRC(SV_EventOut_Close_Relay, 3) == C_OK) && (SV_EventOut_Close_Relay[0] == C_EventOut_Relay) )
			{
				SV_EventOut_Close_Relay[0] = C_EventOutNot_Relay;	/*表示不需要上报合闸成功事件*/
				V_usDataCRC = PF_Cal_CRC(SV_EventOut_Close_Relay, 1);
				PF_Ushort16ToBuffer2(&SV_EventOut_Close_Relay[1], &V_usDataCRC);	
			
				/*合闸成功主动上报*/
				InF_ActiveReportSetting(C_Times_CloseRelay);
				Inf_WriteMeterStatus8(C_RelayCloseEventNo);	
			}
		}

		if( (SV_RelayDisplayStatus & C_RelayStatusLEDTwinkle) != C_RelayStatusLEDTwinkle)
		{
			if( (SV_RelayDisplayStatus & C_RelayStatusLEDOn) == C_RelayStatusLEDOn)
			{
				SF_RelayStatusLEDMsgSend_Relay(C_DisplayOff);	/*跳闸指示灯熄灭*/
			}
		}
	}
	
	InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State3, &V_ucDataBuff[0], CLMeter_Work_State3, C_W_SafeFlag);	/*电表运行状态字3写数据层*/

	return;
}

#if 0
/******************************************************************************************
Function：	void Get_ExternalRelayFeedbackSignal(void)                            	                		   	
Description：    外置继电器反馈信号检测                                                				
Input：                                                                                                                                                                              
Output：																						 			
Calls：                                                                                 
Called By：                                                                             
Author:                                                                          
******************************************************************************************/
void Get_ExternalRelayFeedbackSignal(void)
{
	uchar8 V_ucSignalValid, V_ucDataBuff[2], V_ucRelayType;
	uchar8 V_ucEventNo;
	ushort16	V_usDataLength;
	ushort16	V_usDataEncode = 0;
	
	V_usDataLength = CLMeter_Work_State3;
	if(InF_Read_Data(CMeter_Work_State3, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode) != C_OK)	/*读取电表运行状态字3*/
	{
		return;
	}

	V_usDataLength = CLRelay_Type;
	if(InF_Read_Data(CRelay_Type, &V_ucRelayType, &V_usDataLength, &V_usDataEncode) != C_OK)	/*读取负荷开关类型*/
	{
		return;
	}

	if( ( (V_ucRelayType & C_Relay_Type) == 1)	/*外置表*/	/*wxy数字*/
	 && ( (V_ucRelayType & C_RelayFbackLine_Type) != 0) )	/*有继电器反馈线*/
	{
		V_ucSignalValid = SV_ExternalRelayStatus;	/*外置继电器的实际状态*/
		
		if( ( (V_ucSignalValid == C_Valid) 
			 && ( (V_ucDataBuff[0] & C_RelayStatusOff_External) == C_ExternalRelayFeedbackClose) )	/*0：通*/
			 || ( (V_ucSignalValid == C_Invalid) 
			 && ( (V_ucDataBuff[0] & C_RelayStatusOff_External) == C_ExternalRelayFeedbackOpen) ) )	/*1：断*/
		{
			SV_ucExternalRelayStatusTime = 0;			
		}
		else
		{
			if(SV_ucExternalRelayStatusTime < C_ExternalRelayStatusTime)	/*5s检测时间到，写跟随上报状态字，进行跟随上报*/
			{
				SV_ucExternalRelayStatusTime++;
			}
			else
			{
				if(V_ucSignalValid == C_Valid)
				{
					V_ucDataBuff[0] &= C_RelayStatusOn_External;	/*0：通*/
					V_ucEventNo = C_ExternalRelayCloseEventNo;
				}
				else
				{
					V_ucDataBuff[0] |= C_RelayStatusOff_External;	/*1：断*/
					V_ucEventNo = C_ExternalRelayOpenEventNo;
				}
				
				/*电表运行状态字3写数据层*/
				InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State3, &V_ucDataBuff[0], CLMeter_Work_State3, C_W_SafeFlag);
				/*写跟随上报状态字*/
				Inf_WriteMeterStatus8(V_ucEventNo);			
			}			
		}
	}
}
#endif

/*******************************************************************************
函数原型：void SF_DealWithSV_Relay(void)
功能描述：继电器模块内部静态变量处理
输入参数：无
输出参数：无
返回参数：无
调用位置：
备    注：
*******************************************************************************/
void SF_DealWithSV_Relay(void)
{
	SV_OpenRealyDelay_Time = 0x00;	/*跳闸延时时间*/
	SV_L_CloseRealyDelay_Time = 0x00;	/*本地表本地一次跳闸后允许合闸延时时间*/
	SV_Comm_CloseRealyDelay_Time = 0x00;	/*通信跳闸自动恢复持续时间*/
	SV_24HourDelayTimer = 0x00;	/*电流超过门限电流计时*/
	SV_RelayRework_Timer = 0x00;	/*重复动作定时器*/
	SV_RelayOpenAfterPowerUp = 0x00;	/*上电时条件合闸状态要先跳闸，上电置0x68，用过后清零*/

	if( (SV_RelayDisplayStatus&C_RelayStatusLEDTwinkle) == C_RelayStatusLEDTwinkle)
	{
		SF_RelayStatusLEDMsgSend_Relay(C_DisplayOff);	/*跳闸指示灯熄灭*/
	}
	SV_ClearFlag = 0x00;	/*电表清零标识*/

	return;
}

/*******************************************************************************
函数原型：void SF_Cardor3sCloseRelayTask_Relay(void)
功能描述：插卡或按键3s合闸处理
输入参数：无
输出参数：无
返回参数：无
调用位置：该函数由Msg_Deal_RelayStatus函数调用
备    注：
*******************************************************************************/
void SF_Cardor3sCloseRelayTask_Relay(void)
{
	ushort16	V_usDataLength;
	ushort16	V_usDataEncode = 0;
	
	SF_Combine_R_L_Order_Relay();	/*远程本地控制命令组合*/
	if(Combine_RelayOrder.RelayOrderStatus == C_Close_conditonal)	/*组合命令为条件合闸*/
	{
		SF_DealWithSV_Relay();	/*内部静态变量处理*/
		
		V_usDataLength = CLRelay_RemoteOrder;
		InF_Read_Data(CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, &V_usDataLength, &V_usDataEncode);	/*读取远程控制命令*/
	
		V_usDataLength = CLRelay_LocalOrder;
		InF_Read_Data(CRelay_LocalOrder, &Local_RelayOrder.PreWarning, &V_usDataLength, &V_usDataEncode);	/*读取本地控制命令*/
		
		SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*拉闸字符熄灭*/
			
		if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
		{
			SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*背光关闭*/
		}

		Com_RelayOrder.RelayOrderStatus = C_Close_Direct;
		Local_RelayOrder.RelayOrderStatus = C_Close_Direct;	
		SV_LocalOrderNum = 0x00;	/*本地命令序号置为0*/
		SV_ComOrderNum = 0x00;	/*远程命令序号置*/
		
		InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, CLRelay_RemoteOrder, C_W_SafeFlag);	/*远程控制命令写数据层*/
		InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_LocalOrder, &Local_RelayOrder.PreWarning, CLRelay_LocalOrder, C_W_SafeFlag);	/*本地控制命令写数据层*/
	}
}

/*******************************************************************************
函数原型：void SF_TimeTask_Relay(void)
功能描述：调度500ms触发任务处理
输入参数：无
输出参数：无
返回参数：无
调用位置：该函数由Msg_Deal_RelayStatus函数调用
备    注：调度每500ms调用该函数
*******************************************************************************/
void SF_TimeTask_Relay(void)
{
	uchar8	V_ucDataBuff[10];
	uchar8	V_ucRelayType;
	ushort16	V_usDataLength;
	ushort16	V_usDataEncode = 0;
	
	V_usDataLength = CLRelay_RemoteOrder;
	InF_Read_Data(CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, &V_usDataLength, &V_usDataEncode);	/*读取远程控制命令*/

	V_usDataLength = CLRelay_LocalOrder;
	InF_Read_Data(CRelay_LocalOrder, &Local_RelayOrder.PreWarning, &V_usDataLength, &V_usDataEncode);	/*读取本地控制命令*/

	V_usDataLength = CLRelay_State;
	InF_Read_Data(CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, &V_usDataLength, &V_usDataEncode);	/*读取继电器状态*/

	SF_GetRelay0nOffStatus();	/*带反馈外置继电器的实际状态获取*/
	SF_RelayStatusCheck_Relay();	/*继电器实际状态检测*/
	if( (Local_RelayOrder.RelayOrderStatus == C_Pre_Open) && (SV_L_CloseRealyDelay_Time > 1)
		&& (Relay_Stutas.RelaytheoreticStatus == C_RelayOff) )
	{
		SV_L_CloseRealyDelay_Time--;	/*条件合闸延时时间减1*/
		if(SV_L_CloseRealyDelay_Time == 1)
		{
			Local_RelayOrder.RelayOrderStatus = C_Close_Allow;	/*控制命令置允许合闸*/
			InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_LocalOrder, &Local_RelayOrder.PreWarning, CLRelay_LocalOrder, C_W_SafeFlag);	/*本地控制命令写数据层*/
			SV_LocalOrderNum = SF_GetNewOrderNum();	/*更新本地命令序号*/
		}
	}
	if(SV_RelayRework_Timer != 0)
	{
		SV_RelayRework_Timer--;	/*重复动作延时时间减1*/
	}
	if(SV_24HourDelayTimer > 1)
	{
		SV_24HourDelayTimer--;	/*大电流延时时间减1*/
	}
	if( (Com_RelayOrder.RelayOrderStatus == C_Open) && (SV_OpenRealyDelay_Time > 1) )
	{
		SV_OpenRealyDelay_Time--;	/*跳闸延时时间减1*/
	}
	else if( (Com_RelayOrder.RelayOrderStatus == C_Open_Direct) && (SV_Comm_CloseRealyDelay_Time != 0)
			&& (Relay_Stutas.RelaytheoreticStatus == C_RelayOff) )
	{
		SV_Comm_CloseRealyDelay_Time--;	/*1D跳闸自动恢复延时时间减1*/
		if(SV_Comm_CloseRealyDelay_Time == 0)
		{
			SV_L_CloseRealyDelay_Time = 0x00;	/*结束本地预跳闸状态*/
			Com_RelayOrder.RelayOrderStatus = C_Close_Direct;
			InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, CLRelay_RemoteOrder, C_W_SafeFlag);	/*远程控制命令写数据层*/
			SV_ComOrderNum = SF_GetNewOrderNum();	/*更新远程命令序号*/
			
			if(Local_RelayOrder.RelayOrderStatus != C_Open)
			{
				SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*拉闸字符熄灭*/
			}			
			
			if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
			{
				SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*背光关闭*/
			}
				
			V_usDataLength = CLMeter_Work_State3;
			InF_Read_Data(CMeter_Work_State3, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*读取电表运行状态字3*/
			V_ucDataBuff[0] &= C_RelayOrderStatusOn;	/*继电器命令导通*/
			InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State3, &V_ucDataBuff[0], CLMeter_Work_State3, C_W_SafeFlag);	/*电表运行状态字3写数据层*/
		}	
	}
	else if( (Com_RelayOrder.RelayOrderStatus == C_Open_Allow) && (SV_Comm_CloseRealyDelay_Time != 0)
			&& (Relay_Stutas.RelaytheoreticStatus == C_RelayOff) )
	{
		SV_Comm_CloseRealyDelay_Time--;	/*1E跳闸自动恢复延时时间减1*/
		if(SV_Comm_CloseRealyDelay_Time == 0)
		{
			SV_L_CloseRealyDelay_Time = 0x00;	/*结束本地预跳闸状态*/
			V_usDataLength = CLRelay_Type;
			InF_Read_Data(CRelay_Type, &V_ucRelayType, &V_usDataLength, &V_usDataEncode);	/*读取负荷开关类型*/
			if( (V_ucRelayType & C_Relay_Type) == 1)
			{
				Com_RelayOrder.RelayOrderStatus = C_Close_Direct;	/*远程控制命令置直接合闸*/
				InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, CLRelay_RemoteOrder, C_W_SafeFlag);	/*远程控制命令写数据层*/
				
				if(Local_RelayOrder.RelayOrderStatus != C_Open)
				{
					SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*拉闸字符熄灭*/
				}
				
				if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
				{
					SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*背光关闭*/
				}
			}
			else
			{
				Com_RelayOrder.RelayOrderStatus = C_Close_Allow;
				InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, CLRelay_RemoteOrder, C_W_SafeFlag);	/*远程控制命令写数据层*/
				SV_ComOrderNum = SF_GetNewOrderNum();	/*更新远程命令序号*/
				
				if(Local_RelayOrder.RelayOrderStatus != C_Open)
				{
					SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*拉闸字符熄灭*/
					
					if(Relay_Stutas.RelaytheoreticStatus == C_RelayOff)
					{
						SF_RelayStatusLEDMsgSend_Relay(C_DisplayTwinkle);	/*跳闸指示灯闪烁*/
					}
				}
				
				if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
				{
					SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*背光关闭*/
				}	
			}	
			
			V_usDataLength = CLMeter_Work_State3;
			InF_Read_Data(CMeter_Work_State3, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*读取电表运行状态字3*/
			V_ucDataBuff[0] &= C_RelayOrderStatusOn;	/*继电器命令导通*/
			InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State3, &V_ucDataBuff[0], CLMeter_Work_State3, C_W_SafeFlag);	/*电表运行状态字3写数据层*/
		}
	}
	
	SF_Combine_R_L_Order_Relay();	/*远程本地控制命令组合*/
	SF_CombineOrderExecute_Relay();	/*组合控制命令执行*/
#if 0    
	Get_ExternalRelayFeedbackSignal();	/*外置继电器反馈信号检测*/
#endif

	return;	
}

/*******************************************************************************
函数原型：void SF_Combine_R_L_Order_Relay(void)
功能描述：远程本地控制命令组合
输入参数：无
输出参数：无
返回参数：无
调用位置：该函数由SF_TimeTask_Relay函数和SF_Cardor3sCloseRelayTask_Relay函数调用
备    注：根据远程控制命令和本地控制命令决定组合控制命令状态
*******************************************************************************/
void SF_Combine_R_L_Order_Relay(void)
{
	uchar8	V_ucRelayType;
	ushort16	V_usDataLength;
	ushort16	V_usDataEncode = 0;
	
	V_usDataLength = CLRelay_RemoteOrder;
	InF_Read_Data(CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, &V_usDataLength, &V_usDataEncode);	/*读取远程控制命令*/

	V_usDataLength = CLRelay_LocalOrder;
	InF_Read_Data(CRelay_LocalOrder, &Local_RelayOrder.PreWarning, &V_usDataLength, &V_usDataEncode);	/*读取本地控制命令*/
	
	Combine_RelayOrder.RelayOrderStatus = C_OrderNull;	/*组合继电器命令状态先置为空*/

	/*报警命令组合*/
	if( (Com_RelayOrder.PreWarning == C_PreWarning) || (Local_RelayOrder.PreWarning == C_PreWarning) )
	{
		Combine_RelayOrder.PreWarning = C_PreWarning;	
	}
	else
	{
		Combine_RelayOrder.PreWarning = C_PreWarning_Release;	
	}
	
	/*继电器命令组合*/
	if(Com_RelayOrder.Protect_Current == C_Protect_Current)	/*当前处于远程保电状态*/
	{
		V_usDataLength = CLRelay_Type;
		InF_Read_Data(CRelay_Type, &V_ucRelayType, &V_usDataLength, &V_usDataEncode);	/*读取负荷开关类型*/
		
		if( (V_ucRelayType&C_Relay_Type) == 1)	
		{
			Combine_RelayOrder.RelayOrderStatus = C_Close_Direct;	/*开关外置直接合闸*/
		}
		else
		{
			if( (Local_RelayOrder.RelayOrderStatus == C_Close_Direct) && (Com_RelayOrder.RelayOrderStatus == C_Close_Direct) )
			{
				Combine_RelayOrder.RelayOrderStatus = C_Close_Direct;	/*开关外置直接合闸*/
			}
			else
			{
				Combine_RelayOrder.RelayOrderStatus = C_Close_conditonal;	/*开关内置条件合闸*/
			}					
		}
	}
	else if(Local_RelayOrder.RelayOrderStatus == C_Open)	/*当前处于本地立即跳闸状态*/
	{
		Combine_RelayOrder.RelayOrderStatus = C_Open;	/*直接跳闸*/
	}
	else if(Local_RelayOrder.RelayOrderStatus == C_Pre_Open)	/*当前处于本地预跳闸状态*/
	{
		if(Com_RelayOrder.RelayOrderStatus == C_Open)	/*跳闸*/
		{
			if( (SV_L_CloseRealyDelay_Time > 1) || (SV_OpenRealyDelay_Time == 1) )
			{
				Combine_RelayOrder.RelayOrderStatus = C_Open;	/*直接跳闸*/
			}
		}
		else if(Com_RelayOrder.RelayOrderStatus == C_Close_Allow)	/*合闸允许*/
		{
			if(SV_L_CloseRealyDelay_Time > 1)
			{
				Combine_RelayOrder.RelayOrderStatus = C_Open;	/*直接跳闸*/
			}
			else 
			{
				Combine_RelayOrder.RelayOrderStatus = C_Close_conditonal;	/*条件合闸*/
			}	
		}
		else if(Com_RelayOrder.RelayOrderStatus == C_Close_Direct)	/*直接合闸*/
		{
			if(SV_L_CloseRealyDelay_Time > 1)
			{
				Combine_RelayOrder.RelayOrderStatus = C_Open;	/*直接跳闸*/
			}
			else 
			{
				Combine_RelayOrder.RelayOrderStatus = C_Close_Direct;	/*直接合闸*/
			}			
		}
		else
		{
			if( (SV_L_CloseRealyDelay_Time > 1) || (SV_Comm_CloseRealyDelay_Time != 0) )
			{
				Combine_RelayOrder.RelayOrderStatus = C_Open;	/*直接跳闸*/
			}
		}
	}
	else if(Local_RelayOrder.RelayOrderStatus == C_Close_Allow)	/*当前处于本地合闸允许状态*/
	{
		if(Com_RelayOrder.RelayOrderStatus == C_Open_Direct)	/*跳闸自动恢复（延时时间到直接合闸）*/
		{
			if(SV_Comm_CloseRealyDelay_Time != 0)
			{
				Combine_RelayOrder.RelayOrderStatus = C_Open;	/*直接跳闸*/
			}
			else
			{
				Combine_RelayOrder.RelayOrderStatus = C_Close_conditonal;	/*条件合闸*/
			}
		}
		if(Com_RelayOrder.RelayOrderStatus == C_Open_Allow)	/*跳闸自动恢复（延时时间到合闸允许）*/
		{
			if(SV_Comm_CloseRealyDelay_Time != 0)
			{
				Combine_RelayOrder.RelayOrderStatus = C_Open;	/*直接跳闸*/
			}
			else
			{
				Combine_RelayOrder.RelayOrderStatus = C_Close_conditonal;	/*条件合闸*/
			}
		}
		if(Com_RelayOrder.RelayOrderStatus == C_Open)	/*跳闸*/
		{
			if(SV_OpenRealyDelay_Time == 1)
			{
				Combine_RelayOrder.RelayOrderStatus = C_Open;	/*直接跳闸*/
			}
		}
		if(Com_RelayOrder.RelayOrderStatus == C_Close_Allow)	/*合闸允许*/
		{
			Combine_RelayOrder.RelayOrderStatus = C_Close_conditonal;	/*条件合闸*/
		}
		if(Com_RelayOrder.RelayOrderStatus == C_Close_Direct)	/*直接合闸*/
		{
			if(PF_Campare_Data(&SV_LocalOrderNum, &SV_ComOrderNum, 1) == C_GreaterThan)	/*比较远程命令和本地控制命令序号大小*/
			{
				Combine_RelayOrder.RelayOrderStatus = C_Close_conditonal;	/*条件合闸*/
			}
			else 
			{
				Combine_RelayOrder.RelayOrderStatus = C_Close_Direct;	/*直接合闸*/
			}	
		}	
	}
	else	/*if(Local_RelayOrder.RelayOrderStatus == C_Close_Direct)*/	/*当前处于本地合闸状态*/
	{
		if(Com_RelayOrder.RelayOrderStatus == C_Open_Direct)	/*跳闸自动恢复（延时时间到直接合闸）*/
		{
			if(SV_Comm_CloseRealyDelay_Time != 0)
			{
				Combine_RelayOrder.RelayOrderStatus = C_Open;	/*直接跳闸*/
			}
			else 
			{
				Combine_RelayOrder.RelayOrderStatus = C_Close_Direct;	/*直接合闸*/
			}		
		}
		if(Com_RelayOrder.RelayOrderStatus == C_Open_Allow)	/*跳闸自动恢复（延时时间到合闸允许）*/
		{
			if(SV_Comm_CloseRealyDelay_Time != 0)
			{
				Combine_RelayOrder.RelayOrderStatus = C_Open;	/*直接跳闸*/
			}
			else 
			{
				Combine_RelayOrder.RelayOrderStatus = C_Close_Direct;	/*直接合闸*/
			}		
		}
		if(Com_RelayOrder.RelayOrderStatus == C_Open)	/*跳闸*/
		{
			if(SV_OpenRealyDelay_Time == 1)
			{
				Combine_RelayOrder.RelayOrderStatus = C_Open;	/*直接跳闸*/
			}	
		}
		if(Com_RelayOrder.RelayOrderStatus == C_Close_Allow)	/*合闸允许*/
		{
			if(PF_Campare_Data(&SV_LocalOrderNum, &SV_ComOrderNum, 1) == C_LessThan)	/*比较远程命令和本地控制命令序号大小*/
			{
				Combine_RelayOrder.RelayOrderStatus = C_Close_conditonal;	/*条件合闸*/
			}
			else 
			{
				Combine_RelayOrder.RelayOrderStatus = C_Close_Direct;	/*直接合闸*/
			}
		}
		if(Com_RelayOrder.RelayOrderStatus == C_Close_Direct)	/*直接合闸*/
		{
			Combine_RelayOrder.RelayOrderStatus = C_Close_Direct;	/*直接合闸*/
		}	
	}
}

/*******************************************************************************
函数原型：void SF_CombineOrderExecute_Relay(void)
功能描述：组合控制命令执行
输入参数：无
输出参数：无
返回参数：无
调用位置：该函数由SF_TimeTask_Relay函数调用
备    注：继电器根据组合控制命令状态做出相关动作
*******************************************************************************/
void SF_CombineOrderExecute_Relay(void)
{
	uchar8	V_ucDataBuff[6] = {0};
	uchar8	V_ucDataBuff_Msg[8];
	uchar8	V_ucBackLEDStatus = 0;
	uchar8	V_ucRelayType;
	ulong32	V_ulTime;
	ushort16	V_usDataCRC;
	ushort16	V_usDataLength;
	ushort16	V_usDataEncode = 0;

	V_usDataLength = CLRelay_RemoteOrder;
	InF_Read_Data(CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, &V_usDataLength, &V_usDataEncode);	/*读取远程控制命令*/
	
	V_usDataLength = CLRelay_State;
	InF_Read_Data(CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, &V_usDataLength, &V_usDataEncode);	/*读取继电器状态*/
	
	memset(&V_ucDataBuff_Msg[0], 0xFF, 8);
	if(Combine_RelayOrder.PreWarning == C_PreWarning)	/*组合命令为报警*/
	{
		V_usDataLength = CLMeter_Work_State3;
		InF_Read_Data(CMeter_Work_State3, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*读取电表运行状态字3*/
		V_ucDataBuff[0] |= C_RelayPreWarning;	/*预跳闸报警*/
		InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State3, &V_ucDataBuff[0], CLMeter_Work_State3, C_W_SafeFlag);	/*电表运行状态字3写数据层*/
			
		V_ucDataBuff_Msg[0] = Pt_DisplayStatus;
		V_ucDataBuff_Msg[1] = (C_PurchaseSign | C_TwinkleDisplay);	/*请购电字符闪烁*/
		V_ucDataBuff_Msg[4] = Pt_DisplayStatus;
		V_ucDataBuff_Msg[5] = (C_BackLED | C_AlwaysDisplay);	/*点亮背光*/
		if(Relay_Stutas.RelaytheoreticWarningStatus == C_PreWarning)	/*理论状态为报警*/
		{
			if(SV_AlarmAfterPowerUp == C_PreWarning)	/*理论与实际一致均为报警时，上电报警标识有效报警，报警后标识清零*/
			{
				SV_AlarmAfterPowerUp = C_PreWarning_Release;	
#if 0
				V_ucDataBuff_Msg[0] = Pt_DisplayStatus;
				V_ucDataBuff_Msg[1] = (C_PurchaseSign | C_TwinkleDisplay);	/*请购电字符闪烁*/
				V_ucDataBuff_Msg[2] = 0xFF;
				V_ucDataBuff_Msg[3] = 0xFF;
				V_ucDataBuff_Msg[4] = Pt_DisplayStatus;
				V_ucDataBuff_Msg[5] = (C_BackLED | C_AlwaysDisplay);	/*点亮背光*/
				V_ucDataBuff_Msg[6] = 0xFF;
				V_ucDataBuff_Msg[7] = 0xFF;
#endif
				SF_MsgSend_Relay(V_ucDataBuff_Msg, (Pt_DisplayStatus_Len + 1) * 2, C_Msg_Display);	/*触发显示消息*/
			}	
		}
		else
		{
			Relay_Stutas.RelaytheoreticWarningStatus = C_PreWarning;	/*置理论报警状态*/
			InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, CLRelay_State, C_W_SafeFlag);	/*理论状态写数据层*/
#if 0	
			V_ucDataBuff_Msg[0] = Pt_DisplayStatus;
			V_ucDataBuff_Msg[1] = (C_PurchaseSign | C_TwinkleDisplay);	/*请购电字符闪烁*/
			V_ucDataBuff_Msg[2] = 0xFF;
			V_ucDataBuff_Msg[3] = 0xFF;
			V_ucDataBuff_Msg[4] = Pt_DisplayStatus;
			V_ucDataBuff_Msg[5] = (C_BackLED | C_AlwaysDisplay);	/*点亮背光*/
			V_ucDataBuff_Msg[6] = 0xFF;
			V_ucDataBuff_Msg[7] = 0xFF;
#endif
			SF_MsgSend_Relay(V_ucDataBuff_Msg, (Pt_DisplayStatus_Len + 1) * 2, C_Msg_Display);	/*触发显示消息*/
		}	
	}
	else /*if(Combine_RelayOrder.PreWarning == C_PreWarning_Release)*/	/*组合命令为报警解除*/
	{
		V_usDataLength = CLMeter_Work_State3;
		InF_Read_Data(CMeter_Work_State3, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*读取电表运行状态字3*/
		V_ucDataBuff[0] &= C_RelayPreWarning_Release;	/*无预跳闸报警*/
		InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State3, &V_ucDataBuff[0], CLMeter_Work_State3, C_W_SafeFlag);	/*电表运行状态字3写数据层*/
		
		if(Relay_Stutas.RelaytheoreticWarningStatus == C_PreWarning)
		{
			V_ucDataBuff_Msg[0] = Pt_DisplayStatus;
			V_ucDataBuff_Msg[1] = (C_PurchaseSign | C_NotDisplay);	/*请购电字符熄灭*/
			
			SF_MsgSend_Relay(V_ucDataBuff_Msg, Pt_DisplayStatus_Len + 1, C_Msg_Display);	/*触发显示消息*/
			
			if( (Com_RelayOrder.RelayOrderStatus == C_Open) && (SV_OpenRealyDelay_Time > 1) && (Relay_Stutas.RelaytheoreticStatus != C_RelayOff) )	/*跳闸延时期间*/
			{
				V_ucBackLEDStatus = C_BackLEDstatusOn;	
			}	
			if( (Combine_RelayOrder.RelayOrderStatus == C_Open) && (SV_24HourDelayTimer > 1) && (Relay_Stutas.RelaytheoreticStatus != C_RelayOff) )
			{
				V_ucBackLEDStatus = C_BackLEDstatusOn;		
			}
			if(V_ucBackLEDStatus != C_BackLEDstatusOn)
			{
				SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*关闭背光*/
			}
			
			Relay_Stutas.RelaytheoreticWarningStatus = C_PreWarning_Release;	/*置理论报警解除状态*/
			InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, CLRelay_State, C_W_SafeFlag);	/*理论状态写数据层*/
		}
	}
	if(Combine_RelayOrder.RelayOrderStatus == C_Open)	/*组合命令为跳闸*/
	{
		if(Relay_Stutas.RelaytheoreticStatus == C_RelayOff)	/*理论状态为跳闸*/
		{
			if( (SV_RelayDisplayStatus&C_RealayOpenSignOn) != C_RealayOpenSignOn)
			{
				SF_RealayOpenSignMsgSend_Relay(C_DisplayOn);	/*拉闸字符常显*/
			}
			if(SV_RelayRework_Timer == 0)	/*重复动作延时时间到，继电器动作一次*/
			{
				if( ( ( (SF_JudgeCurrent_Relay() == C_CurrentOk) && (SV_RelayOpenAfterPowerUp != C_Open) ) || (SV_RelayOpenAfterPowerUp == C_Open) )
					&& (InF_JudgeVolage_Relay() == C_VoltageOk) )	/*电压电流均符合要求*/
				{
					InF_RelayAct(C_Off);	/*跳闸*/
					SV_RelayOpenAfterPowerUp = 0x00;				
					
					if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
					{
						SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*关闭背光*/
					}
				}
				SV_RelayRework_Timer = C_RelayRework_Timer;	
			}
		}
		else	/*if(Relay_Stutas.RelaytheoreticStatus == C_RelayOn)*/	/*理论状态为合闸*/
		{
			if(SV_24HourDelayTimer == 0)	/*大电流延时时间为0*/
			{
				if( (SF_JudgeCurrent_Relay() != C_CurrentOk) || (InF_JudgeVolage_Relay() != C_VoltageOk) )	/*电压或电流不符合跳闸要求发生对应显示消息*/
				{
					if( (SV_RelayDisplayStatus&C_RealayOpenSignTwinkle) != C_RealayOpenSignTwinkle)
					{
						SF_RealayOpenSignMsgSend_Relay(C_DisplayTwinkle);	/*拉闸字符闪烁*/
					}
					if( (SV_RelayDisplayStatus&C_BackLEDOn) != C_BackLEDOn)
					{
						SF_BackLEDMsgSend_Relay(C_DisplayOn);	/*点亮背光*/
					}
				}
				if(SF_JudgeCurrent_Relay() == C_CurrentOk)	/*电流符合跳闸要求*/
				{
					if(InF_JudgeVolage_Relay() == C_VoltageOk)	/*电压符合跳闸要求*/
					{
						SF_Op_OpenRelay_Relay();
					}
				}
				else
				{
					V_usDataLength = CLRelay_Open_CurrTimer;
					if(InF_Read_Data(CRelay_Open_CurrTimer, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode) != C_OK)	/*大电流延时时间*/
					{
						SV_24HourDelayTimer = 1;	/*大电流延时时间置初值*/
					}
					else
					{
						PF_BufferXToUlong32(V_ucDataBuff, &V_ulTime, V_usDataLength);
						if(V_ulTime == 0)
						{
							SV_24HourDelayTimer = 1;	/*大电流延时时间置初值*/
						}
						else
						{
							SV_24HourDelayTimer = V_ulTime*60*2;	/*大电流延时时间置初值*/
						}
					}
				}
			}
			if(SV_24HourDelayTimer > 1)	/*大电流延时时间大于1，24小时延时时间未到*/
			{
				if(SF_JudgeCurrent_Relay() == C_CurrentOk)	/*电流符合跳闸要求*/
				{
					if(InF_JudgeVolage_Relay() == C_VoltageOk)	/*电压符合跳闸要求*/
					{
						SF_Op_OpenRelay_Relay();
					}
				}
			}
			if(SV_24HourDelayTimer == 1)	/*大电流延时时间为1, 24小时延时时间到，不再判断电流阀值*/
			{
				if(InF_JudgeVolage_Relay() == C_VoltageOk)	/*电压符合跳闸要求*/
				{
					SF_Op_OpenRelay_Relay();
				}
				else
				{
					if( (SV_RelayDisplayStatus&C_RealayOpenSignTwinkle) != C_RealayOpenSignTwinkle)	
					{
						SF_RealayOpenSignMsgSend_Relay(C_DisplayTwinkle);	/*拉闸字符闪烁*/
					}
					if( (SV_RelayDisplayStatus&C_BackLEDOn) != C_BackLEDOn)
					{
						SF_BackLEDMsgSend_Relay(C_DisplayOn);	/*点亮背光*/
					}
				}
			}
		}
	}
	else if(Combine_RelayOrder.RelayOrderStatus == C_Close_conditonal)	/*组合命令为条件合闸*/
	{
		if(SV_RelayOpenAfterPowerUp == C_Open)
		{
			if(Relay_Stutas.RelaytheoreticStatus == C_RelayOff)	/*理论状态为跳闸*/
			{
				if(InF_JudgeVolage_Relay() == C_VoltageOk)	/*电压电流均符合要求*/
				{
					InF_RelayAct(C_Off);	/*跳闸*/
					SV_RelayOpenAfterPowerUp = 0x00;					
				}
			}
		}
	}
	else if(Combine_RelayOrder.RelayOrderStatus == C_OrderNull)	/*组合命令为空不执行 直接返回*/
	{
		return;	
	}
	else	/*if(Combine_RelayOrder.RelayOrderStatus == C_Close_Direct)*/	/*组合命令为合闸*/
	{
		if(Relay_Stutas.RelaytheoreticStatus == C_RelayOn)	/*理论状态为合闸*/
		{
			if(SV_RelayRework_Timer == 0)	/*重复动作延时时间到*/
			{
				if(InF_JudgeVolage_Relay() == C_VoltageOk)	/*电压满足合闸要求*/
				{
					InF_RelayAct(C_On);	/*合闸*/
				}
				
				SV_RelayRework_Timer = C_RelayRework_Timer;	/*置重复动作延时时间初值*/
			}
		}
		else	/*if(Relay_Stutas.RelaytheoreticStatus == C_RelayOff)*/	/*理论状态为跳闸*/
		{
			if( ( (SV_RelayDisplayStatus&C_RealayOpenSignOn) == C_RealayOpenSignOn)
				|| ( (SV_RelayDisplayStatus&C_RealayOpenSignTwinkle) == C_RealayOpenSignTwinkle) )
			{
				SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*拉闸字符熄灭*/
			}
			
			if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
			{
				if( (SV_RelayDisplayStatus&C_BackLEDOn) == C_BackLEDOn)
				{
					SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*关闭背光*/
				}
			}
			
			if(InF_JudgeVolage_Relay() == C_VoltageOk)	/*电压满足合闸要求*/
			{
				if( (SV_RelayDisplayStatus&C_RelayStatusLEDTwinkle) == C_RelayStatusLEDTwinkle)
				{
					SF_RelayStatusLEDMsgSend_Relay(C_DisplayOff);	/*跳闸指示灯熄灭*/
				}
				
				InF_RelayAct(C_On);	/*合闸*/
				
				SV_Error_Time = 0x00;
				Relay_Stutas.RelaytheoreticStatus = C_RelayOn;	/*置理论状态为合闸*/
				InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, CLRelay_State, C_W_SafeFlag);	/*理论状态写数据层*/
				
				SV_EventOut_Open_Relay[0] = C_EventOutNot_Relay;	/*表示不需要上报跳闸成功事件*/
				V_usDataCRC = PF_Cal_CRC(SV_EventOut_Open_Relay, 1);
				PF_Ushort16ToBuffer2(&SV_EventOut_Open_Relay[1], &V_usDataCRC); 
		
				SV_EventOut_Close_Relay[0] = C_EventOut_Relay;	/*表示需要上报合闸成功事件*/
				V_usDataCRC = PF_Cal_CRC(SV_EventOut_Close_Relay, 1);
				PF_Ushort16ToBuffer2(&SV_EventOut_Close_Relay[1], &V_usDataCRC);	
					
				SV_EventOut_Err_Relay[0] = C_EventOutCloseErr_Relay;	/*表示需要上报负荷开关误动作事件*/
				V_usDataCRC = PF_Cal_CRC(SV_EventOut_Err_Relay, 1);
				PF_Ushort16ToBuffer2(&SV_EventOut_Err_Relay[1], &V_usDataCRC);	
				
				SF_Event_CloseRelay_Relay();	/*记合闸事件记录*/
				
				V_usDataLength = CLRelay_Type;
				InF_Read_Data(CRelay_Type, &V_ucRelayType, &V_usDataLength, &V_usDataEncode);	/*读取负荷开关类型*/
				if( (V_ucRelayType & C_Relay_Type) == 1)
				{
					if(SV_ClearFlag == 0x68)	/*电表清零标识*/
					{
						Relay_Stutas.RelayRealStatus = C_RelayOn;	/*置继电器实际状态导通*/
						InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, CLRelay_State, C_W_SafeFlag);	/*继电器状态写数据层*/
						SF_RelayStatusLEDMsgSend_Relay(C_DisplayOff);	/*跳闸指示灯熄灭*/
						SV_ClearFlag = 0x00;	/*电表清零标识*/
					}	
				}
#if 0				
				/*跳闸成功主动上报*/
				InF_ActiveReportSetting(C_Times_CloseRelay);
#endif
				SV_RelayRework_Timer = C_RelayRework_Timer;	/*置重复动作延时时间初值*/
			}
			else
			{
				if( (SV_RelayDisplayStatus&C_RelayStatusLEDTwinkle) != C_RelayStatusLEDTwinkle)
				{
					SF_RelayStatusLEDMsgSend_Relay(C_DisplayTwinkle);	/*跳闸指示灯闪烁*/
				}	
			}
		}
	}
	return;
}

/*******************************************************************************
函数原型：uchar8 InF_JudgeVolage_Relay(void)
功能描述：电压值判断
输入参数：无
输出参数：无
返回参数：C_VoltageOk，表示当前电压允许跳合闸；C_VoltageErr，表示当前电压不允许跳合闸
调用位置：该函数由SF_CombineOrderExecute_Relay函数调用
备    注：跳合闸之前调用该函数，判断是否符合继电器跳合闸要求
*******************************************************************************/
uchar8 InF_JudgeVolage_Relay(void)
{
	uchar8	V_ucVoltage[6];
	uchar8	V_ucData[2];
	uchar8	V_ucReturnFlag;
	ushort16	V_usVoltageHEX_ABC[3];	/*ABC三相电压*/
	ushort16	V_usRelayOpenVol_LowLim;	/*拉合闸电压下限*/
	ushort16	V_usDataLength;
	ushort16	V_usDataEncode = 0;

	V_ucReturnFlag = C_VoltageOk;	
	
	if( InF_JudgeIJTimer() == C_OK )	/*如果处于厂内状态, 直接返回OK*/
	{
		return V_ucReturnFlag;
	}
	
	V_usDataLength = CLRelayOpen_Vol__LowLim;
	InF_Read_Data(CRelayOpen_Vol__LowLim, V_ucData, &V_usDataLength, &V_usDataEncode);	/*读取拉合闸电压下限*/
	PF_Buffer2ToUshort16(&V_ucData[0], &V_usRelayOpenVol_LowLim);

	V_usDataLength = CLPhaseFF_Volage;
	InF_Read_Data(CPhaseFF_Volage, V_ucVoltage, &V_usDataLength, &V_usDataEncode);	/*读取三相电压*/
	PF_Buffer2ToUshort16(&V_ucVoltage[0], &V_usVoltageHEX_ABC[0]);
	PF_Buffer2ToUshort16(&V_ucVoltage[2], &V_usVoltageHEX_ABC[1]);
	PF_Buffer2ToUshort16(&V_ucVoltage[4], &V_usVoltageHEX_ABC[2]);
	
	if( (V_usVoltageHEX_ABC[0] < V_usRelayOpenVol_LowLim)
		&& (V_usVoltageHEX_ABC[1] < V_usRelayOpenVol_LowLim)
		&& (V_usVoltageHEX_ABC[2] < V_usRelayOpenVol_LowLim) )	/*三相电压均小于拉合闸电压下限*/
	{
		V_ucReturnFlag = C_VoltageErr;	/*返回错误*/
	}

	return	V_ucReturnFlag;
}

/*******************************************************************************
函数原型：void SF_RealayOpenSignMsgSend_Relay(uchar8 V_ucDisplayType)
功能描述：拉闸字符显示消息
输入参数：无
输出参数：无
返回参数：无
调用位置：
备    注：
*******************************************************************************/
void SF_RealayOpenSignMsgSend_Relay(uchar8 V_ucDisplayType)
{
	uchar8	V_ucDataBuff_Msg[4];
	
	memset(&V_ucDataBuff_Msg[0], 0xFF, 4);
	V_ucDataBuff_Msg[0] = Pt_DisplayStatus;

	switch(V_ucDisplayType)
	{
		case C_DisplayOn:
		{
			V_ucDataBuff_Msg[1] = (C_RealayOpenSign | C_AlwaysDisplay);	/*拉闸字符常显*/
			SF_MsgSend_Relay(V_ucDataBuff_Msg, Pt_DisplayStatus_Len + 1, C_Msg_Display);	/*触发显示消息*/
			SV_RelayDisplayStatus &= C_RealayOpenSignOff;	/*拉闸字符熄灭*/
			SV_RelayDisplayStatus |= C_RealayOpenSignOn;	/*置拉闸字符常显标识*/
		}break;
		
		case C_DisplayTwinkle:
		{
			V_ucDataBuff_Msg[1] = (C_RealayOpenSign | C_TwinkleDisplay);	/*拉闸字符闪烁*/
			SF_MsgSend_Relay(V_ucDataBuff_Msg, Pt_DisplayStatus_Len + 1, C_Msg_Display);	/*触发显示消息*/
			SV_RelayDisplayStatus &= C_RealayOpenSignOff;	/*拉闸字符熄灭*/
			SV_RelayDisplayStatus |= C_RealayOpenSignTwinkle;	/*置拉闸字符闪烁标识*/
		}break;
		
		case C_DisplayOff:
		{
			V_ucDataBuff_Msg[1] = (C_RealayOpenSign | C_NotDisplay);	/*拉闸字符不显示*/
			SF_MsgSend_Relay(V_ucDataBuff_Msg, Pt_DisplayStatus_Len + 1, C_Msg_Display);	/*触发显示消息*/
			SV_RelayDisplayStatus &= C_RealayOpenSignOff;	/*拉闸字符熄灭标识*/
		}break;
		
		default:
		{

		}break;
	}
	return;	
}

/*******************************************************************************
函数原型：void SF_RelayStatusLEDMsgSend_Relay(uchar8 V_ucDisplayType)
功能描述：跳闸指示灯显示消息
输入参数：无
输出参数：无
返回参数：无
调用位置：
备    注：
*******************************************************************************/
void SF_RelayStatusLEDMsgSend_Relay(uchar8 V_ucDisplayType)
{
	uchar8	V_ucDataBuff_Msg[4];
	
	memset(&V_ucDataBuff_Msg[0], 0xFF, 4);
	V_ucDataBuff_Msg[0] = Pt_DisplayStatus;

	switch(V_ucDisplayType)
	{
		case C_DisplayOn:
		{
			V_ucDataBuff_Msg[1] = (C_RelayStatusLED | C_AlwaysDisplay);	/*跳闸指示灯常显*/
			SF_MsgSend_Relay(V_ucDataBuff_Msg, Pt_DisplayStatus_Len + 1, C_Msg_Display);	/*触发显示消息*/
			SV_RelayDisplayStatus &= C_RelayStatusLEDOff;	/*跳闸指示灯熄灭*/
			SV_RelayDisplayStatus |= C_RelayStatusLEDOn;	/*置跳闸指示灯常显*/
		}break;
		
		case C_DisplayTwinkle:
		{
			V_ucDataBuff_Msg[1] = (C_RelayStatusLED | C_TwinkleDisplay);	/*跳闸指示灯闪烁*/
			SF_MsgSend_Relay(V_ucDataBuff_Msg, Pt_DisplayStatus_Len + 1, C_Msg_Display);	/*触发显示消息*/
			SV_RelayDisplayStatus &= C_RelayStatusLEDOff;	/*跳闸指示灯熄灭*/
			SV_RelayDisplayStatus |= C_RelayStatusLEDTwinkle;	/*置跳闸指示灯闪烁*/
		}break;
		
		case C_DisplayOff:
		{
			V_ucDataBuff_Msg[1] = (C_RelayStatusLED | C_NotDisplay);	/*跳闸指示灯常显*/
			SF_MsgSend_Relay(V_ucDataBuff_Msg, Pt_DisplayStatus_Len + 1, C_Msg_Display);	/*触发显示消息*/
			SV_RelayDisplayStatus &= C_RelayStatusLEDOff;	/*跳闸指示灯熄灭*/
		}break;
		
		default:
		{

		}break;
	}
	return;			
}

/*******************************************************************************
函数原型：void SF_BackLEDMsgSend_Relay(uchar8 V_ucDisplayType)
功能描述：背光显示消息
输入参数：无
输出参数：无
返回参数：无
调用位置：
备    注：
*******************************************************************************/
void SF_BackLEDMsgSend_Relay(uchar8 V_ucDisplayType)
{
	uchar8	V_ucDataBuff_Msg[4];
	
	memset(&V_ucDataBuff_Msg[0], 0xFF, 4);
	V_ucDataBuff_Msg[0] = Pt_DisplayStatus;

	switch(V_ucDisplayType)
	{
		case C_DisplayOn:
		{
			V_ucDataBuff_Msg[1] = (C_BackLED | C_AlwaysDisplay);	/*点亮背光*/
			SF_MsgSend_Relay(V_ucDataBuff_Msg, Pt_DisplayStatus_Len + 1, C_Msg_Display);	/*触发显示消息*/
			SV_RelayDisplayStatus |= C_BackLEDOn;	/*背光点亮*/
		}break;
		
		case C_DisplayOff:
		{
			V_ucDataBuff_Msg[1] = (C_BackLED | C_NotDisplay);	/*关闭背光*/
			SF_MsgSend_Relay(V_ucDataBuff_Msg, Pt_DisplayStatus_Len + 1, C_Msg_Display);	/*触发显示消息*/
			SV_RelayDisplayStatus &= C_BackLEDOff;	/*背光熄灭*/
		}break;
		
		default:
		{

		}break;
	}
	return;			
}

/*******************************************************************************
函数原型：void SF_MsgSend_Relay(uchar8 *V_ucParm, uchar8 V_ucParmLen, uchar8 V_ucDerictAddr)
功能描述：发送消息
输入参数：无
输出参数：无
返回参数：无
调用位置：
备    注：
*******************************************************************************/
void SF_MsgSend_Relay(uchar8 *V_ucParm, uchar8 V_ucParmLen, uchar8 V_ucDerictAddr)
{
	Str_Msg_Parameter Str_Msg_RelayStatus;
 
	Str_Msg_RelayStatus.SourceAddr = C_Msg_Deal_RelayStatus;	/*源消息号*/
	Str_Msg_RelayStatus.DerictAddr = V_ucDerictAddr;	/*目的消息号*/
	Str_Msg_RelayStatus.Length = V_ucParmLen;	/*长度*/
	Str_Msg_RelayStatus.Parameter = V_ucParm;	/*参数*/
	InF_WriteMessege(&Str_Msg_RelayStatus);	/*写消息函数*/
}

/*******************************************************************************
函数原型：uchar8 SF_GetNewOrderNum(void)
功能描述：取控制命令序号
输入参数：无
输出参数：无
返回参数：当前命令序号较大的值加1结果
调用位置：
备    注：返回远程命令序号和本地命令序号中较大的值加1
*******************************************************************************/
uchar8 SF_GetNewOrderNum(void)
{
	uchar8	V_ucReturnNum = 1;
	
	if(SV_LocalOrderNum >= SV_ComOrderNum)	/*比较远程命令和本地控制命令序号大小*/
	{
		if(SV_LocalOrderNum == 0xFF)	/*当前为FF则清零*/
		{
			SV_LocalOrderNum = 0x00;
			SV_ComOrderNum = 0x00;	
		}
		V_ucReturnNum += SV_LocalOrderNum;
	}
	else
	{
		if(SV_ComOrderNum == 0xFF)	/*当前为FF则清零*/
		{
			SV_LocalOrderNum = 0x00;
			SV_ComOrderNum = 0x00;	
		}
		V_ucReturnNum += SV_ComOrderNum;	
	}
	
	return V_ucReturnNum;
}

/*******************************************************************************
函数原型：uchar8 SF_JudgeOrderStatus(void)
功能描述：判断当前继电器状态是否允许下发跳闸自动恢复命令
输入参数：无
输出参数：无
返回参数：C_Allowed，允许下发跳闸自动恢复命令；C_UnAllowed，不允许下发跳闸自动恢复命令
调用位置：该函数由InF_DealwithComRelayOrder接口函数调用
备    注：
*******************************************************************************/
uchar8 SF_JudgeOrderStatus(void)
{
	uchar8	V_ucReturnFlag;
	ushort16	V_usDataLength;
	ushort16	V_usDataEncode = 0;

	V_ucReturnFlag = C_Allowed;
	
	V_usDataLength = CLRelay_RemoteOrder;
	InF_Read_Data(CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, &V_usDataLength, &V_usDataEncode);	/*读取远程控制命令*/

	V_usDataLength = CLRelay_LocalOrder;
	InF_Read_Data(CRelay_LocalOrder, &Local_RelayOrder.PreWarning, &V_usDataLength, &V_usDataEncode);	/*读取本地控制命令*/
	
	V_usDataLength = CLRelay_State;
	InF_Read_Data(CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, &V_usDataLength, &V_usDataEncode);	/*读取继电器状态*/
	
	if(Local_RelayOrder.RelayOrderStatus == C_Open)	/*当前处于本地立即跳闸状态*/
	{
		V_ucReturnFlag = C_UnAllowed;	/*不允许下发跳闸自动恢复命令*/
		return V_ucReturnFlag;
	}
	
	if( ( (Local_RelayOrder.RelayOrderStatus == C_Pre_Open) || (Local_RelayOrder.RelayOrderStatus == C_Close_Allow) ) && (SV_L_CloseRealyDelay_Time != 0) )	/*当前处于本地预跳闸状态且条件合闸延时时间不为0*/
	{
		V_ucReturnFlag = C_UnAllowed;	/*不允许下发跳闸自动恢复命令*/
		return V_ucReturnFlag;
	}
	
	if( (Combine_RelayOrder.RelayOrderStatus == C_Close_conditonal) && (Relay_Stutas.RelaytheoreticStatus == C_RelayOff) )
	{
		V_ucReturnFlag = C_UnAllowed;	/*不允许下发跳闸自动恢复命令*/
		return V_ucReturnFlag;	
	}
	
	if(Com_RelayOrder.RelayOrderStatus == C_Open)	/*跳闸*/
	{
		V_ucReturnFlag = C_UnAllowed;	/*不允许下发跳闸自动恢复命令*/
		return V_ucReturnFlag;
	}
	
	return V_ucReturnFlag;
}

/*******************************************************************************
函数原型：void SF_Judge1D1EOrderStatus(void)
功能描述：通信跳闸自动恢复命令处理
输入参数：无
输出参数：无
返回参数：无
调用位置：该函数由SF_LocalControl_Relay函数调用
备    注：
*******************************************************************************/
void SF_Judge1D1EOrderStatus(void)
{
	uchar8	V_ucDataBuff[10];	
	ushort16	V_usDataLength;
	ushort16	V_usDataEncode = 0;

	V_usDataLength = CLRelay_RemoteOrder;
	InF_Read_Data(CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, &V_usDataLength, &V_usDataEncode);	/*读取远程控制命令*/

	if( ( (Com_RelayOrder.RelayOrderStatus == C_Open_Direct) || (Com_RelayOrder.RelayOrderStatus == C_Open_Allow) )
		&& (SV_Comm_CloseRealyDelay_Time != 0) )
	{
		SV_Comm_CloseRealyDelay_Time = 0;
		
		Com_RelayOrder.RelayOrderStatus = C_Close_Direct;
		InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, CLRelay_RemoteOrder, C_W_SafeFlag);	/*远程控制命令写数据层*/
			
		V_usDataLength = CLMeter_Work_State3;
		InF_Read_Data(CMeter_Work_State3, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*读取电表运行状态字3*/
		V_ucDataBuff[0] &= C_RelayOrderStatusOn;	/*继电器命令导通*/
		InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State3, &V_ucDataBuff[0], CLMeter_Work_State3, C_W_SafeFlag);	/*电表运行状态字3写数据层*/
	}
	return;
}

/*******************************************************************************
函数原型：void SF_Event_OpenRelay_Relay(void)
功能描述：做跳闸操作
输入参数：无
输出参数：无
返回参数：无
调用位置：该函数由SF_CombineOrderExecute_Relay私有函数调用
备    注：1）调用该函数前必须确保电压、电流符合跳闸要求
          2）该函数包含跳闸，设置上报标识，记事件记录，设置跳闸显示字符
*******************************************************************************/
void SF_Op_OpenRelay_Relay(void)
{
	ushort16	V_usDataCRC;

	InF_RelayAct(C_Off);	/*跳闸*/

	SV_Error_Time = 0x00;
	Relay_Stutas.RelaytheoreticStatus = C_RelayOff;	/*置理论跳闸状态*/
	InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, CLRelay_State, C_W_SafeFlag);	/*理论状态写数据层*/
	
	SV_EventOut_Open_Relay[0] = C_EventOut_Relay;	/*表示需要上报跳闸成功事件*/
	V_usDataCRC = PF_Cal_CRC(SV_EventOut_Open_Relay, 1);
	PF_Ushort16ToBuffer2(&SV_EventOut_Open_Relay[1], &V_usDataCRC); 
	
	SV_EventOut_Close_Relay[0] = C_EventOutNot_Relay;	/*表示不需要上报合闸成功事件*/
	V_usDataCRC = PF_Cal_CRC(SV_EventOut_Close_Relay, 1);
	PF_Ushort16ToBuffer2(&SV_EventOut_Close_Relay[1], &V_usDataCRC);	
	
	SV_EventOut_Err_Relay[0] = C_EventOutOpenErr_Relay;	/*表示需要上报负荷开关误动作事件*/
	V_usDataCRC = PF_Cal_CRC(SV_EventOut_Err_Relay, 1);
	PF_Ushort16ToBuffer2(&SV_EventOut_Err_Relay[1], &V_usDataCRC);		
	
	SF_Event_OpenRelay_Relay();	/*记跳闸事件记录*/
	
	SV_RelayRework_Timer = C_RelayRework_Timer;	/*置重复动作延时时间初值*/
	
	if( (SV_RelayDisplayStatus&C_RealayOpenSignOn) != C_RealayOpenSignOn)
	{
		SF_RealayOpenSignMsgSend_Relay(C_DisplayOn);	/*拉闸字符常显*/
	}
	
	if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
	{
		if( (SV_RelayDisplayStatus&C_BackLEDOn) == C_BackLEDOn)
		{
			SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*关闭背光*/
		}
	}
}

/**********************************************************************************************************************************
函数原型：uchar8 InF_Get_RelayModule(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, ushort16 *p_usDataEncode)
功能描述：读费控模块接口
输入参数：V_ulOAD:需要读取的OAD；
		  pV_ucDataBuf:读取数据的缓存的首地址
		  *pV_usDataLen:读取数据的缓存的最大长度；
输出参数： pV_ucDataBuf:读取数据的缓存的首地址
		  *pV_usDataLen:读取数据实际长度；
          *P_usDataEncode:数据内部编码；
返回参数：C_OK,读取成功;其他错误;
调用位置：对象管理层
备    注：
************************************************************************************************************************************/
uchar8 InF_Get_RelayModule(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, ushort16 *p_usDataEncode)
{
	uchar8	V_ucBuffer[2], V_ucReturn = C_Error;
	ushort16	V_usDataLength;
	ushort16	V_usDataEncode = 0;

	if( (V_ulOAD & 0xFFFFFF00) == 0xF2050200)	/*继电器输出设备对象列表*/
	{
		V_ucReturn = SF_Get_ApplianceF205(V_ulOAD, pV_ucDataBuf, pV_usDataLen);
	}
	if(V_ulOAD == 0x80010200)	/*保电状态*/
	{
		V_ucReturn = C_OK;
		if(InF_RelayProtectStatus()==C_Protect)
		{
			pV_ucDataBuf[0] = 0x01;
		}
		else
		{
			pV_ucDataBuf[0] = 0x00;
		}
	}
	if(V_ulOAD == 0x80000400)	/*报警状态*/
	{
		V_usDataLength = 2;
		V_ucReturn = InF_Read_Data(CMeter_Work_State3, V_ucBuffer, &V_usDataLength, &V_usDataEncode);

		if( (V_ucBuffer[0]&0x80)==0x80)
		{
			pV_ucDataBuf[0] = 0x80;
		}
		else
		{
			pV_ucDataBuf[0] = 0x00;
		}
	}
	if(V_ulOAD == 0x80000500)	/*继电器命令状态*/
	{
		V_usDataLength = 2;
		V_ucReturn = InF_Read_Data(CMeter_Work_State3, V_ucBuffer, &V_usDataLength, &V_usDataEncode);

		if( (V_ucBuffer[0]&0x40)==0x40)
		{
			pV_ucDataBuf[0] = 0x80;
		}
		else
		{
			pV_ucDataBuf[0] = 0x00;
		}		
	}

	return V_ucReturn;
}

/**********************************************************************************************************************************
函数原型：uchar8 SF_Get_ApplianceF205(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen)
功能描述：读取F205设备类对象
输入参数：V_ulOAD:需要读取的OAD；
		  pV_ucDataBuf:读取数据的缓存的首地址
		  *pV_usDataLen:读取数据的缓存的最大长度；
输出参数： pV_ucDataBuf:读取数据的缓存的首地址
		  *pV_usDataLen:读取数据实际长度；
返回参数：C_OK,读取成功;其他错误;
调用位置：该函数由InF_Get_RelayModule函数调用
备    注：
************************************************************************************************************************************/
uchar8 SF_Get_ApplianceF205(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen)
{
	uchar8	V_ucReturn = C_Error;
	ushort16	V_usOff = 0;
	ushort16	V_usDataLength;
	ushort16	V_usDataEncode = 0;

	pV_ucDataBuf[V_usOff] = 82;	/*"R"*/
	V_usOff++;
	pV_ucDataBuf[V_usOff] = 69;	/*"E"*/
	V_usOff++;
	pV_ucDataBuf[V_usOff] = 76;	/*"L"*/
	V_usOff++;
	pV_ucDataBuf[V_usOff] = 65;	/*"A"*/
	V_usOff++;
	pV_ucDataBuf[V_usOff] = 89;	/*"Y"*/
	V_usOff++;
	pV_ucDataBuf[V_usOff] = InF_RelayOpenStatus_698();
	V_usOff++;
	V_usDataLength = CLMeter_Work_Char1;
	V_ucReturn = InF_Read_Data(CMeter_Work_Char1, &pV_ucDataBuf[V_usOff], &V_usDataLength, &V_usDataEncode);	/*读取继电器状态 */
	pV_ucDataBuf[V_usOff] = (pV_ucDataBuf[V_usOff]&0x01);
	V_usOff++;
	if(C_Meter_Type == C_SmartMeter)
	{
		pV_ucDataBuf[V_usOff] = 1;
	}
	else
	{
		pV_ucDataBuf[V_usOff] = 0;
	}
	V_usOff++;
	*pV_usDataLen = V_usOff;

	return V_ucReturn;
}