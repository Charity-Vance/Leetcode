/***************************************************************************************
Copyright:	ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:	Dispatch.c
Version:	V1
Date:		2014-3-12
Description:���ȴ����ļ�
Function List:
***************************************************************************************
History1:��1���޸�
����1.	Date:
		Author:
		Modification:
		*********************************************
����2.	Date:
		Author:
		Modification:
		*******************************************************************************
History2:��2���޸�
����1.	Date:
		Author:
		Modification:
		*********************************************
����2.	Date:
		Author:
		Modification:
***************************************************************************************/

#include "Dispatch.h"
#include "Public.h"

Str_Msg_Parameter SStr_Msg_Parameter;	/*����ȫ�ֵ���Ϣ�ṹ�壬���ڴ�ŵ��ȶ�ȡ����Ϣ������Ϣ*/

/********************************************************************************
Function:void Dispatch_SendMessage(uchar8 MsgDerictAddr,uchar8 *P_Parameter,uchar8 ParameterLen)
Description:�����ȷ���Ϣ������ģ��
Input:	*P_Parameter:��Ϣ�еĲ������׵�ַ
		ParameterLen:�����򳤶�
		DerictAddrMsg:Ŀ�ĵ�ַ
Output:��
Calls:
Called By:�����ȷ���Ϣʱ����
Influence:���õĵط���Դ��Ϣ�š�Ŀ����Ϣ�š�����������ú���øú���
********************************************************************************/
void Dispatch_SendMessage(uchar8 MsgDerictAddr, uchar8 *P_Parameter, uchar8 ParameterLen)
{
	Str_Msg_Parameter	Str_Message;
	Str_Message.SourceAddr = C_Msg_Dispatch;	/*Դ��ַ��Ȼ��������*/
	Str_Message.DerictAddr = MsgDerictAddr;
	Str_Message.Parameter = P_Parameter;
	Str_Message.Length = ParameterLen;
	InF_WriteMessege(&Str_Message);
}

/********************************************************************************
Function:��ȡ���������е���Ϣ
Description:1.���ȴӵ�1�����ж�ȡ��Ϣ,�������Ϣ,����Ϣ��������ȫ����Ϣ������,������C_OK
			2.�����1������û����Ϣ,���ȡ��2����
			3.�����2��������Ϣ,����Ϣ��������ȫ����Ϣ������,������C_OK
			4.�����2����Ҳû����Ϣ,�򷵻�C_Error
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
Description:��ȡ��1/2��Ϣ��������Ϣ����������Ӧ���������д���
Input:no
Output:no
Return:����Ϣ����,����C_OK;����Ϣ����,����C_Error
Calls:��ȡ��Ϣ���в�������Ϣ�Ž�����Ӧ�Ĵ���
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
	/*��InF_ReadPowerState90��ȡ��״̬�У��ϵ硢�е硢���硢�͹�����4�����
	���λ�ȡ����Ϣ�����ܳ���4��״̬����һ�֣�����Ҫ���ȵ���Ϣ*/
	switch(SStr_Msg_Parameter.DerictAddr)
	{
		/**********************************/
		case (C_Msg_Communication):			/*ͨ�Žӿ���Ϣ*/
		{	/*ͨ����2����Ϣ��1��Ϊ�жϴ���������Ϣ���ж��ñ�־���ⲿֱ�ӵ��ý���������
			1��Ϊ500ms��ʱ��Ϣ����Ȼ������Ϣ����ʽ*/
			Comm_ParseMessage(&SStr_Msg_Parameter);
			return C_OK;									/*������һ��ִ��һ����Ϣ�����Բ���return������ͬ*/
		}
		/**********************************/
		case (C_Msg_Dispatch):
		{
			Msg_ExcuteRTC_Message(&SStr_Msg_Parameter);		/*��ȡ�ⲿӲ��ʱ��*/
			return C_OK;
		}
		/**********************************/
		case (C_Msg_Display):								/*��ʾ��Ϣ*/
		{
			InF_Display_Message(&SStr_Msg_Parameter);
			if( C_PowerOff == InF_ReadPowerState() )		/*�ж��Ƿ�ͣ��:��ͣ�绽��*/
			{	/*ͣ�绽��ʱ��Ҫ���������:*/
				/*���������״̬��3�еĹ��緽ʽдΪ����ع��硱*/
				SF_WritePowerMode_PowerOff();
				SF_KeyLock();								/*������������*/
			}
			return C_OK;
		}
		/**********************************/
		default:
		{
			break;
		}
	}
	/*�����ж�û�е�����£���ִ�е���Ϣ*/
	if( C_PowerOff != InF_ReadPowerState() )
	{
		switch(SStr_Msg_Parameter.DerictAddr)
		{
			/**********************************/
			case (C_Msg_PowerNetworkMonitoring):	/*����������¼���¼�ж���Ϣ*/
			{
				InF_Event_Message(&SStr_Msg_Parameter);
				return C_OK;
			}
			/**********************************/
			case (C_Msg_EnergyMetering):			/*���ܼ�����Ϣ*/
			{
				InF_EnergyMetering_Message(&SStr_Msg_Parameter);
				return C_OK;
			}
			/**********************************/
			case (C_Msg_DemandMetering):			/*����������Ϣ*/
			{
				InF_DemandMetering_Message(&SStr_Msg_Parameter);
				return C_OK;
			}
			/**********************************/
			case (C_Msg_SettleAccounts):			/*������Ϣ*/
			{
				Msg_SettleAccounts(&SStr_Msg_Parameter);
				return C_OK;
			}
			/**********************************/
			case (C_Msg_Freeze):					/*������Ϣ*/
			{
				Msg_Freeze(&SStr_Msg_Parameter);
				return C_OK;
			}
#if 0
			/**********************************/
			case (C_Msg_LoadProfile):				/*���ɼ�¼��Ϣ*/
			{
				Msg_LoadProfile(&SStr_Msg_Parameter);
				return C_OK;
			}
#endif
			/**********************************/
			case (C_Msg_Deal_RelayStatus):			/*�̵���������Ϣ*/
			{
				Msg_Deal_RelayStatus(&SStr_Msg_Parameter);
				return C_OK;
			}
			/**********************************/
			case (C_Msg_Deal_MultiRates):			/*�����ж���Ϣ*/
			{
				InF_MultiRates_ParseMessage(&SStr_Msg_Parameter);
				return C_OK;
			}
			/**********************************/
			case (C_Msg_BatteryVoltagleMetering):	/*��ص�ѹ������Ϣ*/
			{
				InF_ADC_Action_Message(&SStr_Msg_Parameter);
				return C_OK;
			}
			/**********************************/
			case (C_Msg_VoltageQualifiedRateMetering):	/*��ѹ�ϸ��ʼ��*/
			{
				InF_VoltageQR_ParseMessage(&SStr_Msg_Parameter);
				return C_OK;
			}
			/**********************************/
			case (C_Msg_MeterIC):						/*������Ϣģ��*/
			{
				InF_MeterIC_ParseMessage(&SStr_Msg_Parameter);
				return C_OK;
			}
			/**********************************/
			case (C_Msg_Card):							/*��������Ϣģ��*/
			{
				InF_Card_Message(&SStr_Msg_Parameter);
				return C_OK;
			}
			/**********************************/
			case (C_Msg_BroadcastAddress):				/*�Թ㲥����ʽ������Ϣ*/
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
			case (C_Msg_Esam):										/*ESAMģ����Ϣ*/
			{
				EsamPowerOnRest_Message(&SStr_Msg_Parameter);
				return C_OK;
			}
			/**********************************/
			case (C_Msg_DataProcess):
			{
				Data_CruiseCheck_Message(&SStr_Msg_Parameter);		/*���ݲ�Ѳ������*/
				return C_OK;
			}
			/**********************************/
			case (C_Msg_DataProcess_External):
			{
				DataProcess_External_Message(&SStr_Msg_Parameter);	/*���ݲ�Ѳ������*/
				return C_OK;
			}
			/**********************************/
			case (C_Msg_CalibrateRC):
			{
				Msg_CalibrateRC(&SStr_Msg_Parameter);				/*У׼RC��*/
				return C_OK;
			}
			/**********************************/
			default:
			{
				break;
			}
		}
	}
	/*���ڵ͹��������е���Ϣ���*/
	if( C_PowerOff == InF_ReadPowerState() )	/*ȫʧѹ��Ϣ,�е��ʱ��û�������Ϣ*/
	{
		if(SStr_Msg_Parameter.DerictAddr == C_Msg_AllLossVoltage)
		{
			/*ͣ�绽�Ѻ�Ŀ��ϸ��¼���¼*/
			Inf_LowpowerOpenCoverState(C_OpenTerminalCoverEventNo);
			Inf_LowpowerOpenCoverState(C_OpenMeterCoverEventNo);
			/*ͣ�绽�Ѻ��ȫʧѹ��¼*/
			Msg_AllLoseVoltage(&SStr_Msg_Parameter);
		}
	}

	return C_OK;

}

/************************************************************************
����ԭ��:void InF_Dispatch_ReadRtcToDataProcess(uchar8 powerflag)
��������:���ⲿRTC��ȡʱ�Ӳ�ˢ�����ݲ�ʱ�ӣ�7�ֽڣ�
�������:��
�������:��仯��Ϣ�����ӱ仯��Ϣ��ˢ�����ݲ�ʱ��,����ʱ�ӹ��ϱ�������
���ز���:��
����ʱ����
��ע:
************************************************************************/
void InF_Dispatch_ReadRtcToDataProcess(uchar8 powerflag)
{
	uchar8 V_ucRTCBuffer_BCD[C_RTCLen] = {0};			/*���ڴ�Ŵ�RTC��ȡ��7�ֽ�ʱ��,��ʽΪYYMMDDWWHHMMSS*/
	uchar8 V_ucRTCBuffer_Hex[CLDate_Time] = {0};		/*����RTC��ʽת�����ʱ��,��ʽΪData_Time_s*/
	uchar8 V_ucLastTimeBuffer[CLDate_Time] = {0};		/*���ڴ�Ŵ����ݲ��ȡ��7�ֽ�ʱ�䣬��ʽΪData_Time_s*/
	ushort16 V_usDataLength = CLDate_Time, V_usDataEncode = 0;
	uchar8 V_ucBuffer[10] = {0}, V_ucRTCState = C_Error, V_ucReturn = C_Error;

	/*****************************************************/
	V_ucRTCState = InF_ReadRTC(V_ucRTCBuffer_BCD,C_RTCLen);		/*��RTC������ʱ�䣬��ʽΪYYMMDDWWHHMMSS*/
	if( ( C_OK == V_ucRTCState )
		&& ( InF_Read_Data( CDate_Time, V_ucLastTimeBuffer, &V_usDataLength, &V_usDataEncode) == C_OK ) )
	{
		/*ʱ�ӹ����ж�,��ʽΪData_Time_s*/
		V_ucReturn = SF_RTCErrJudgeAndDeal(V_ucLastTimeBuffer);

		/*��RTC�ṩ��YYMMDDWWHHMMSSת��Ϊ698��ʽ��Data_Time_s*/
		PF_Data_Week_Time_BCDtoData_Time_s_HEX(V_ucRTCBuffer_BCD, V_ucRTCBuffer_Hex);

		/*ֻ�ж�ȡ�ɹ�������£�����RTC������ʱ��д���ݲ�*/
		InF_Write_Data(C_Msg_Dispatch,CDate_Time,V_ucRTCBuffer_Hex,CLDate_Time,C_W_SafeFlag);

		if( powerflag != C_PowerOn )	/*���ϵ��ʼ���ڼ��ȡʱ�Ӳ�����Ϣ*/
		{
			if(V_ucReturn == C_RTC_ERR_BackTime)
			{
				/*��������е�ʱ������ݲ��ʱ�䶼������RTCʱ����±���ʱ�� */
				InF_Write_Data(C_Msg_Dispatch, CBackTime_OneSec, V_ucRTCBuffer_Hex, CLBackTime_OneSec, C_W_SafeFlag);
			}
			return;
		}
		/*RTCʱ����±���ʱ��*/
		InF_Write_Data(C_Msg_Dispatch, CBackTime_OneSec, V_ucRTCBuffer_Hex, CLBackTime_OneSec, C_W_SafeFlag);

		/*****************************************************
		20140923:�¼���¼�ۼ�ʱ��,���¼�00s����д�ָ���¼,���ټ�1min���ۼ�ʱ��
		���Խ����ӱ仯����仯���е���,�ȷ�������
		������������¼���¼ģ��ͼ̵���ģ���ȷ��,û������Ӱ��*
		*****************************************************/
		/*�����ӱ仯��Ϣ*/
		/*�յ�ѹ�ϸ��������ն���ʱ���㣬ԭ��������Ϣ��������Ϣ����*/
		/*�����ն�����������ߵ�ѹ�ϸ��ʺ�������������1min������*/
		/*���Խ���ѹ�ϸ��ʷ�����Ϣ������ǰ�����ߵ�ѹ�ϸ������̣������ն�������*/
		if( V_ucLastTimeBuffer[C_Min_698] != V_ucRTCBuffer_Hex[C_Min_698] )
		{
			V_ucBuffer[0] = Pt_Dispatch_Timing;
			V_ucBuffer[1] = C_SystemMinChange;
			if( SF_Shut_RealTimeData() == C_OK )
			{	/*�ϵ����Ϊ��ѹ��ʵʱ��Ϊ0,��ѹ�ϸ��ʿ��ܻ���Ӱ��,��˽���3s�ı���*/
				/*�����Ϊ������ԭ�򶪵�һ����Ϣ,����ʱ�䵽�󲻻Ჹ��Ϣ*/
				/*��ѹ�ϸ���ģ��*/
				Dispatch_SendMessage(C_Msg_VoltageQualifiedRateMetering,V_ucBuffer,Pt_Dispatch_Timing_Len+1);
			}
		}
		/*���±仯��Ϣ*/
		/*Ϊ����ĩ���һ�����ܼ�¼���¶����У������¶��ᵽ��ѹ�ϸ�����Ϣ֮��*/
		/*��Ȼ����ʱ�����¶���֮���±仯��Ϣ�����µ�ѹ�ϸ���*/
		if( V_ucLastTimeBuffer[C_Month_698] != V_ucRTCBuffer_Hex[C_Month_698] )
		{
			V_ucBuffer[0] = Pt_Dispatch_Timing;
			V_ucBuffer[1] = C_SystemMonthChange;
			PF_CopyDataBytes(&V_ucRTCBuffer_Hex[C_Sec_698], &V_ucBuffer[2], CLDate_Time);	/*���ӵ�ǰʱ����Ϊ������Ϣ*/

			/*����ģ��*/
			Dispatch_SendMessage(C_Msg_Freeze,V_ucBuffer,Pt_Dispatch_Timing_Freeze_Len+1);
			if( SF_Shut_RealTimeData() == C_OK )		/*Ϊ����ĩ���һ�����ܼ�¼���¶����У������¶��ᵽ��ѹ�ϸ�����Ϣ֮����Ȼ����ʱ�����¶���֮���±仯��Ϣ�����µ�ѹ�ϸ���*/
			{	/*�ϵ����Ϊ��ѹ��ʵʱ��Ϊ0,��ѹ�ϸ��ʿ��ܻ���Ӱ��,��˽���3s�ı���*/
				/*�����Ϊ������ԭ�򶪵�һ����Ϣ,����ʱ�䵽�󲻻Ჹ��Ϣ*/
				/*��ѹ�ϸ���ģ��*/
				Dispatch_SendMessage(C_Msg_VoltageQualifiedRateMetering,V_ucBuffer,Pt_Dispatch_Timing_Len+1);
			}
		}

		/*��Сʱ�仯��Ϣ*/
		if( V_ucLastTimeBuffer[C_Hour_698] != V_ucRTCBuffer_Hex[C_Hour_698] )
		{
			V_ucBuffer[0] = Pt_Dispatch_Timing;
			V_ucBuffer[1] = C_SystemHourChange;
			PF_CopyDataBytes(&V_ucRTCBuffer_Hex[C_Sec_698], &V_ucBuffer[2], CLDate_Time);	/*���ӵ�ǰʱ����Ϊ������Ϣ*/
			/*����ģ��*/
			Dispatch_SendMessage(C_Msg_Freeze,V_ucBuffer,Pt_Dispatch_Timing_Freeze_Len+1);
		}

		/*���ձ仯��Ϣ*/
		if( V_ucLastTimeBuffer[C_Day_698] != V_ucRTCBuffer_Hex[C_Day_698] )
		{
			V_ucBuffer[0] = Pt_Dispatch_Timing;
			V_ucBuffer[1] = C_SystemDateChange;
			PF_CopyDataBytes(&V_ucRTCBuffer_Hex[C_Sec_698], &V_ucBuffer[2], CLDate_Time);	/*���ӵ�ǰʱ����Ϊ������Ϣ*/
			Dispatch_SendMessage(C_Msg_Freeze,V_ucBuffer,Pt_Dispatch_Timing_Freeze_Len+1);
		}

		/*�����ӱ仯��Ϣ*/
		if( V_ucLastTimeBuffer[C_Min_698] != V_ucRTCBuffer_Hex[C_Min_698] )
		{
			V_ucBuffer[0] = Pt_Dispatch_Timing;
			V_ucBuffer[1] = C_SystemMinChange;
			PF_CopyDataBytes(&V_ucRTCBuffer_Hex[C_Sec_698], &V_ucBuffer[2], CLDate_Time);	/*���ӵ�ǰʱ����Ϊ������Ϣ*/
			/*zlj������������ģ��ǰ���ȷ���Ϣ��˲ʱ��ģ�飬���1minƽ������д���ݲ�*/
			Dispatch_SendMessage(C_Msg_MeterIC, V_ucBuffer, Pt_Dispatch_Timing_Len+1);
			/*20141020:�����ͷ���ģ�����˳��,��Ϊ��Լ������ʱ��ǰ1min������û�ж����ȥ*/
			/*Լ���������ڷ���ģ����ֱ�ӵ�����Ľӿں�����*/
			/*��������ģ��*/
			Dispatch_SendMessage(C_Msg_DemandMetering,V_ucBuffer,Pt_Dispatch_Timing_Len+1);
			/*�����ж�ģ��*/
			Dispatch_SendMessage(C_Msg_Deal_MultiRates,V_ucBuffer,Pt_Dispatch_Timing_Len+1);
			/*����ģ��*/
			Dispatch_SendMessage(C_Msg_Freeze,V_ucBuffer,Pt_Dispatch_Timing_Freeze_Len+1);
			/*�¼���¼ģ��*/
			Dispatch_SendMessage(C_Msg_PowerNetworkMonitoring,V_ucBuffer,Pt_Dispatch_Timing_Len+1);
			/*������ģ��*/
			Dispatch_SendMessage(C_Msg_SettleAccounts,V_ucBuffer,Pt_Dispatch_Timing_Freeze_Len+1);
			/*ͨ��ģ��*/
			Dispatch_SendMessage(C_Msg_Communication,V_ucBuffer,Pt_Dispatch_Timing_Len+1);
		}

		/*����仯��Ϣ*/
		if( V_ucLastTimeBuffer[C_Sec_698] != V_ucRTCBuffer_Hex[C_Sec_698] )
		{
			V_ucBuffer[0] = Pt_Dispatch_Timing;
			V_ucBuffer[1] = C_SystemSecondChange;

			if( SF_Shut_RealTimeData() == C_OK )
			{	/*�ϵ����Ϊ��ѹ��ʵʱ��Ϊ0,���¼���¼���ܻ���Ӱ��,��˽���3s�ı���*/
				/*�¼���¼ģ��*/
				Dispatch_SendMessage(C_Msg_PowerNetworkMonitoring,V_ucBuffer,Pt_Dispatch_Timing_Len+1);
			}

			/*�̵�������ģ��*/
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
			/*�������ݲ��ȡ������ʱ��Data_Time_sת��ΪYYMMDDWWHHMMSS*/
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
Description:0.5��ʱ����Ϣ������
Input:P_Msg_Parameterָ����Ϣ��ȡ���ŵľ�̬����
Output:��
Return:C_OK��ȷ����C_Error��������г���
Calls:
Called By:����500ms��ʱ�������õ���
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
����ԭ��:void InF_DispatchClr_Message(Str_Msg_Parameter *P_Msg_Parameter)
��������:�������ʱ��������Ҫ���������
�������:
���������
���ز���:��
����ʱ����
��ע:
����˵����
**********************************************************************/
void InF_DispatchClr_Message(Str_Msg_Parameter *P_Msg_Parameter)
{
	uchar8 V_ucBuffer[20];

	if(P_Msg_Parameter->Length>20)
	{
		return;		/*����������*/
	}

	PF_CopyDataBytes(P_Msg_Parameter->Parameter,V_ucBuffer,P_Msg_Parameter->Length);
	if( (V_ucBuffer[0] != Pt_MeterClear) && (V_ucBuffer[0] != Pt_EventClearDI) )	/*�ǵ��������Ϣ���¼�������Ϣ*/
	{
		return;
	}

	/*ESAM���ϼ��������ϱ�����*/
	InF_ExecuteClr_Esam();
	/*ʱ�ӵ��Ƿѹ���������ϱ�*/
	InF_ExecuteClr_RTCBatt();
	/*ͣ�糭����Ƿѹ���������ϱ�*/
	InF_ExecuteClr_WakeUpBatt();
	/*�ڲ���������������ϱ�*/

	/*�洢�����ϼ��������ϱ�*/

	/*ʱ�ӹ��ϼ��������ϱ�*/
	InF_ExecuteClr_RTC();
}










