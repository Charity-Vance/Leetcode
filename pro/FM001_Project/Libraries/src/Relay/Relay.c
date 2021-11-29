/********************************************************************************
Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     Relay.c
Version:       V1
Date:          2014-3-12
Description:   ���ɿ��ش���
Function List: 
---------------------------------------------------------------------------------
History1:      ��1���޸�
����1. Date:    2021-10-12
       Author:  wxy
       Modification:
       --------------------------------------------------------------------------
����2. Date:
       Author:
       Modification:
---------------------------------------------------------------------------------
History2:      ��2���޸�
����1. Date:
       Author:
       Modification:
       --------------------------------------------------------------------------
����2. Date:
       Author:
       Modification:
********************************************************************************/

#include "Public.h"
#include "Relay.h"

uchar8 SV_ExternalRelayStatus;

/*******************************************************************************
����ԭ�ͣ�void InF_ InitRelayStatusPowerUp��void��
�����������ϵ��ʼ��
�����������
�����������
���ز�������
����λ�ã�
��    ע���ϵ��ʼ��ʱ����
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
	InF_Read_Data(CMeter_Work_State1, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*��ȡ�������״̬��1*/
	V_ucDataBuff[1] &= C_ControlLoopNoError;	/*�޿��ƻ�·��*/
	InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State1, &V_ucDataBuff[0], CLMeter_Work_State1, C_W_SafeFlag);	/*�������״̬��1д���ݲ�*/
		
	if(C_Meter_Type == C_SmartMeter)	/*���ܱ���������״̬��״̬*/
	{	/*�������״̬��3��ʼ��*/
		V_usDataLength = CLMeter_Work_State3;
		InF_Read_Data(CMeter_Work_State3, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*��ȡ�������״̬��3*/
		V_ucDataBuff[0] &= C_RelayOrderStatusOn;	/*�̵������ͨ*/
		V_ucDataBuff[1] &= C_RelayProtect_Current_Release;	/*�Ǳ���*/
		V_ucDataBuff[0] &= C_RelayStatusOn;	/*�̵�����ͨ*/
		V_ucDataBuff[0] &= C_RelayPreWarning_Release;	/*��Ԥ��բ����*/
		InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State3, &V_ucDataBuff[0], CLMeter_Work_State3, C_W_SafeFlag);	/*�������״̬��3д���ݲ�*/
		
		return;
	}
	if(C_Meter_Type == C_R_SmartMeter)
	{
		Local_RelayOrder.RelayOrderStatus = C_Close_Direct;
		Local_RelayOrder.PreWarning = C_PreWarning_Release;
		
		InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_LocalOrder, &Local_RelayOrder.PreWarning, CLRelay_LocalOrder, C_W_SafeFlag);	/*���ؿ�������д���ݲ�*/
		SV_LocalOrderNum = 0x00;	/*�������������Ϊ0*/
	}
	
	V_usDataLength = CLRelay_RemoteOrder;
	if(InF_Read_Data(CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, &V_usDataLength, &V_usDataEncode) != C_OK)	/*��ȡԶ�̿�������*/
	{
		Com_RelayOrder.Protect_Current = C_Protect_Current_Release;	
		Com_RelayOrder.RelayOrderStatus = C_Close_Direct;
		Com_RelayOrder.PreWarning = C_PreWarning_Release;	
		
		InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, CLRelay_RemoteOrder, C_W_SafeFlag);	/*Զ�̿�������д���ݲ�*/
		SV_ComOrderNum = 0x00;	/*Զ�����������*/
	}
	
	V_usDataLength = CLRelay_LocalOrder;
	if(InF_Read_Data(CRelay_LocalOrder, &Local_RelayOrder.PreWarning, &V_usDataLength, &V_usDataEncode) != C_OK)	/*��ȡ���ؿ�������*/
	{	
		Local_RelayOrder.RelayOrderStatus = C_Close_Direct;
		Local_RelayOrder.PreWarning = C_PreWarning_Release;
		
		InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_LocalOrder, &Local_RelayOrder.PreWarning, CLRelay_LocalOrder, C_W_SafeFlag);	/*���ؿ�������д���ݲ�*/
		SV_LocalOrderNum = 0x00;	/*�������������Ϊ0*/
	}
	
	V_usDataLength = CLRelay_State;
	if(InF_Read_Data(CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, &V_usDataLength, &V_usDataEncode) != C_OK)	/*��ȡ�̵���״̬*/
	{
		Relay_Stutas.RelaytheoreticWarningStatus = C_PreWarning_Release;
		Relay_Stutas.RelaytheoreticStatus = C_RelayOn;	
		Relay_Stutas.RelayRealStatus = C_RelayOn;
		
		InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, CLRelay_State, C_W_SafeFlag);	/*����״̬д���ݲ�*/
	}	
	
	V_usDataLength = CLRelay_Type;
	InF_Read_Data(CRelay_Type, &V_ucRelayType, &V_usDataLength, &V_usDataEncode);	/*��ȡ���ɿ�������*/
	
	V_usDataLength = CLRelay_State;
	InF_Read_Data(CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, &V_usDataLength, &V_usDataEncode);	/*��ȡ�̵���״̬*/
	
	if(SF_Judge_EventIntegrity(C_RelayFaEndEnEventNo) == 0x68)	/*��ǰΪ�з����޽�����д�ָ�*/
	{
		SV_Error_Time = 0x00;

		V_usDataLength = CLRelayFa_Degree;
		InF_Read_Data(CRelayFa_Degree, &V_ucDataBuff2[0], &V_usDataLength, &V_usDataEncode);	/*��ȡ��������*/
		V_usOffset += 4;
		PF_CopyDataBytes(V_ucStartTime, &V_ucDataBuff2[V_usOffset], CLEventHPTime);	/*����ʱ��*/
		V_usOffset += 7;
		V_usDataLength = CLEnter_LowPower_Time;
		InF_Read_Data(CEnter_LowPower_Time, &V_ucDataBuff2[V_usOffset], &V_usDataLength, &V_usDataEncode);	/*��ȡ��ǰʱ�䣬���¼�����ʱ��*/
		V_ucDataBuff2[V_usOffset + 6] = 0x20;
		V_usOffset += 8;
		V_usResidualLength = 300 - V_usOffset;	/*ʣ��buff����*/
		V_ucEventFlag = 0x02;
		
		if(Inf_GetRecordData(&V_ucDataBuff2[V_usOffset], &V_usResidualLength, CRelayFa_OADTab, V_ucEventFlag) != C_OK)	/*��ȡ����OAD����*/
		{
			return;
		}
		V_usOffset += V_usResidualLength;	/*�����ܳ���*/
		InF_Write_Data(C_Msg_Deal_RelayStatus, CRelayFa_Note_1 + 0x00000001, V_ucDataBuff2, V_usOffset, C_W_SafeFlag);	/*�¼�����д����*/
		Inf_EventReport_HP(C_RelayFaEndEnEventNo, C_End_EventReport);
	}

	/*��̬�����ϵ��ʼ��*/
	SV_24HourDelayTimer = 1;	/*�����������޵�����ʱ*/
	SV_RelayRework_Timer = C_RelayReworkPowerUp_Timer;	/*�ظ�������ʱ��*/
	SV_AlarmAfterPowerUp = C_PreWarning;	/*�ϵ�ʱ�б�������ʱ��Ҫ���½��б������� �ϵ���0x68���ù�������*/
	SV_RelayOpenAfterPowerUp = C_Open;	/*�ϵ�ʱ������բ״̬Ҫ����բ���ϵ���0x68���ù�������*/
	SV_Error_Time = 0x00;	/*�̵����쳣ʱ��*/
	
	/*����Զ�̿��������*/
	SV_RelayDisplayStatus &= C_RealayOpenSignOff;	/*��բ�ַ�Ϩ��*/
	SV_RelayDisplayStatus &= C_BackLEDOff;	/*����Ϩ��*/
	
	if( (Com_RelayOrder.RelayOrderStatus == C_Open) && (SV_OpenRealyDelay_Time != 0) )	/*��բ*/
	{
		SV_OpenRealyDelay_Time = 1;
		SF_RealayOpenSignMsgSend_Relay(C_DisplayOn);	/*��բ�ַ�����*/
	}
	else
	{
		SV_OpenRealyDelay_Time = 0;
	}
	if( (Local_RelayOrder.RelayOrderStatus == C_Pre_Open) && (SV_L_CloseRealyDelay_Time != 0) )	/*��ǰ���ڱ���Ԥ��բ״̬��������բ��ʱʱ�䲻Ϊ0*/
	{
		SV_L_CloseRealyDelay_Time = C_L_CloseRealyDelay_Time;
		SF_RealayOpenSignMsgSend_Relay(C_DisplayOn);	/*��բ�ַ�����*/
	}
	else if( (Local_RelayOrder.RelayOrderStatus == C_Close_Allow) && (SV_L_CloseRealyDelay_Time != 0) )	/*��ǰ���ڱ���Ԥ��բ״̬��������բ��ʱʱ�䲻Ϊ0*/
	{
		SV_L_CloseRealyDelay_Time = 1;
		SF_RealayOpenSignMsgSend_Relay(C_DisplayOn);	/*��բ�ַ�����*/
	}
	else
	{
		SV_L_CloseRealyDelay_Time = 0;	
	}
	
	if( ( (Com_RelayOrder.RelayOrderStatus == C_Close_Allow) || (Local_RelayOrder.RelayOrderStatus == C_Close_Allow) )
		 && ( (SV_RelayDisplayStatus&C_RelayStatusLEDTwinkle) == C_RelayStatusLEDTwinkle) )
	{		
		SF_RelayStatusLEDMsgSend_Relay(C_DisplayTwinkle);	/*��բָʾ����˸*/
	}
	else
	{
		SV_RelayDisplayStatus &= C_RelayStatusLEDOff;	/*��բָʾ��Ϩ��*/
	}	
	
	if( (Com_RelayOrder.RelayOrderStatus == C_Open_Allow) && (SV_Comm_CloseRealyDelay_Time != 0) )
	{
		SV_Comm_CloseRealyDelay_Time = 0;
		SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*��բ�ַ�Ϩ��*/

		if( (V_ucRelayType & C_Relay_Type) == 1)
		{
			Com_RelayOrder.RelayOrderStatus = C_Close_Direct;	/*Զ�̿���������ֱ�Ӻ�բ*/
		}
		else
		{
			if(Relay_Stutas.RelaytheoreticStatus == C_RelayOff)
			{				
				SF_RelayStatusLEDMsgSend_Relay(C_DisplayTwinkle);	/*��բָʾ����˸*/
				Com_RelayOrder.RelayOrderStatus = C_Close_Allow;	/*Զ�̿��������ú�բ����*/
				SV_ComOrderNum = SF_GetNewOrderNum();	/*����Զ���������*/
			}
			else
			{
				V_usDataLength = CLControl_ExecuteState;
				if(InF_Read_Data(CControl_ExecuteState, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode) == C_OK)	/*��ȡ��������ִ��״̬��*/
				{
					ushort16 V_usRelayRelayStatus = 0;
					PF_Buffer2ToUshort16(V_ucDataBuff, &V_usRelayRelayStatus);
					if( (V_usRelayRelayStatus&C_Relay_DelayOpen_Current_Status) == C_Relay_DelayOpen_Current_Status)
					{
						Relay_Stutas.RelaytheoreticStatus = C_RelayOff;
						SV_ComOrderNum = SF_GetNewOrderNum();	/*����Զ���������*/
					}
					else
					{
						Com_RelayOrder.RelayOrderStatus = C_Close_Direct;	/*Զ�̿���������ֱ�Ӻ�բ*/
						SV_ComOrderNum = SF_GetNewOrderNum();	/*����Զ���������*/
					}
				}
				else
				{
					Com_RelayOrder.RelayOrderStatus = C_Close_Direct;	/*Զ�̿���������ֱ�Ӻ�բ*/
					SV_ComOrderNum = SF_GetNewOrderNum();	/*����Զ���������*/				
				}
			}	
		}
	}
	else if( (Com_RelayOrder.RelayOrderStatus == C_Open_Direct) && (SV_Comm_CloseRealyDelay_Time != 0) )
	{
		Com_RelayOrder.RelayOrderStatus = C_Close_Direct;
		SV_ComOrderNum = SF_GetNewOrderNum();	/*����Զ���������*/
		SV_Comm_CloseRealyDelay_Time = 0;
		SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*��բ�ַ�Ϩ��*/

	}
	else
	{
		SV_Comm_CloseRealyDelay_Time = 0;	
	}
	
	memset(&V_ucDataBuff[0], 0x00, 8);	
	InF_Write_Data(C_Msg_Deal_RelayStatus, CControl_ExecuteState, V_ucDataBuff, CLControl_ExecuteState, C_W_SafeFlag);	/*��������ִ��״̬��*/
	InF_Write_Data(C_Msg_Deal_RelayStatus, CControl_ErrorState, &V_ucDataBuff[2], CLControl_ErrorState, C_W_SafeFlag);	/*�����������״̬��*/
	
	/*�������״̬��3��ʼ��*/
	V_usDataLength = CLMeter_Work_State3;
	InF_Read_Data(CMeter_Work_State3, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*��ȡ�������״̬��3*/

	if( (Com_RelayOrder.RelayOrderStatus == C_Open)
		|| (Com_RelayOrder.RelayOrderStatus == C_Open_Allow)
		|| (Com_RelayOrder.RelayOrderStatus == C_Open_Direct) )
	{
		V_ucDataBuff[0] |= C_RelayOrderStatusOff;	/*�̵�������Ͽ�*/
	}
	else 
	{
		V_ucDataBuff[0] &= C_RelayOrderStatusOn;	/*�̵������ͨ*/
	}
	if(Com_RelayOrder.Protect_Current == C_Protect_Current)
	{
		V_ucDataBuff[1] |= C_RelayProtect_Current;	/*����*/
		V_ucDataBuff[0] &= C_RelayOrderStatusOn;	/*�̵������ͨ*/
	}
	else
	{
		V_ucDataBuff[1] &= C_RelayProtect_Current_Release;	/*�Ǳ���*/
	}
	InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State3, &V_ucDataBuff[0], CLMeter_Work_State3, C_W_SafeFlag);	/*�������״̬��3д���ݲ�*/
	InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, CLRelay_RemoteOrder, C_W_SafeFlag);	/*Զ�̿�������д���ݲ�*/
#if 0	
	SV_ucExternalRelayStatusTime = 0;	/*���ü̵��������ź�5s���ʱ������*/
#endif			
  return;  
}

/*******************************************************************************
����ԭ�ͣ�uchar8 InF_RelayProtectStatus(void)
�����������жϵ�ǰ�Ƿ񱣵�״̬
�����������
�����������
���ز�����C_Protect����ǰ���ڱ��磻	C_NotProtect����ǰ�Ǳ���
����λ�ã��ú�����ͨ��ģ���SF_GetAPDU_Read��������
��    ע��
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
	InF_Read_Data(CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, &V_usDataLength, &V_usDataEncode);	/*��ȡԶ�̿�������*/
	
	if(Com_RelayOrder.Protect_Current == C_Protect_Current)	/*��ǰ����Զ�̱���״̬*/
	{
		V_ucReturnFlag = C_Protect;	
	}

	return	V_ucReturnFlag;
}

/*******************************************************************************
����ԭ�ͣ�uchar8 InF_RelayOpenStatus(void)
�����������жϵ�ǰ�Ƿ����ñ���բ״̬
�����������
�����������
���ز�����C_EventError����ǰ�������ñ�̵�����բ״̬�����ǵ�Դ�쳣�¼���¼����
          C_EventOK����ǰ�����ñ���բ״̬����Ҫ���е�Դ�쳣�жϣ�
����λ�ã��ú�����Inf_PowerAbnormal�ӿں�������
��    ע��
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
	InF_Read_Data(CRelay_Type, &V_ucRelayType, &V_usDataLength, &V_usDataEncode);	/*��ȡ���ɿ�������*/

	if( (V_ucRelayType & C_Relay_Type) == 0)
	{
		V_usDataLength = CLRelay_State;
		InF_Read_Data(CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, &V_usDataLength, &V_usDataEncode);	/*��ȡ�̵���״̬*/
		if(Relay_Stutas.RelayRealStatus == C_RelayOff)
		{
			V_ucReturnFlag = C_EventError;	
		}
	}

	return	V_ucReturnFlag;
}

/*******************************************************************************
����ԭ�ͣ�uchar8 InF_RelayOpenStatus_698 (void)
�����������жϵ�ǰ�Ƿ���բ״̬
�����������
�����������
���ز�����1����ǰ���ڼ̵�����բ״̬��0����ǰ����բ״̬
����λ�ã��ú�����Inf_Get_ApplianceF205�ӿں�������
��    ע��
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
	InF_Read_Data(CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, &V_usDataLength, &V_usDataEncode);	/*��ȡ�̵���״̬*/

	if(Relay_Stutas.RelayRealStatus == C_RelayOff)
	{
		V_ucReturnFlag = 0x01;	
	}

	return V_ucReturnFlag;
}

/*******************************************************************************
����ԭ�ͣ�uchar8 InF_DealwithComRelayOrder(uchar8 V_ucOrderType, uchar8 *P_OperaterCode, ulong32 V_ucDelayTime, ushort16 *V_usOrderExcuteStatus, uchar8 V_Flag)
�������������������
���������V_ucOrderType, �������*P_OperaterCode�������ߴ��룻V_ucDelayTime����բ�Զ��ָ�����ʱ�䣨����բ�Զ��ָ�����ʱ��0��
          V_Flag���ж��Ƿ�645Э����ã����ж���բ�Զ��ָ���R2Ϊ00ʱ��Ӧ���쳣
�����������
���ز�����C_OK����ʾ������������ִ�У���ʱ���ز���*V_usOrderExcuteStatus��ֵΪ��������ִ��״̬�֣�
          C_Error����ʾ��������ִ���쳣����ʱ���ز���V_usOrderExcuteStatus��ֵΪ����״̬�֡�
����λ�ã�
��    ע��
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
	InF_Read_Data(CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, &V_usDataLength, &V_usDataEncode);	/*��ȡԶ�̿�������*/

	V_usDataLength = CLRelay_LocalOrder;
	InF_Read_Data(CRelay_LocalOrder, &Local_RelayOrder.PreWarning, &V_usDataLength, &V_usDataEncode);	/*��ȡ���ؿ�������*/
	
	V_usDataLength = CLRelay_State;
	InF_Read_Data(CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, &V_usDataLength, &V_usDataEncode);	/*��ȡ�̵���״̬*/
	
	switch(V_ucOrderType)
	{
		case C_Alarm_comm:	/*����*/
		{	
			Com_RelayOrder.PreWarning = C_PreWarning;
			*V_usOrderExcuteStatus = C_Alarm_Status;
		}break;
		
		case C_Alarm_Release_comm:	/*�������*/
		{	
			Com_RelayOrder.PreWarning = C_PreWarning_Release;
			*V_usOrderExcuteStatus = C_Alarm_Release_Status;
		}break;
		
		case C_AlarmOpenRelay_Direct_comm:	/*��բ�Զ��ָ�����ʱʱ�䵽ֱ�Ӻ�բ��*/
		case C_AlarmOpenRelay_Allow_comm:	/*��բ�Զ��ָ�����ʱʱ�䵽��բ����*/
		{	
			if(Com_RelayOrder.Protect_Current == C_Protect_Current)	/*��բ�Զ��ָ�ʧ�ܣ����磩*/
			{
				V_ucReturnFlag = C_Error;
				*V_usOrderExcuteStatus = C_Protect_AlarmOpenfailure;
				break;
			}
			
			if(SF_JudgeOrderStatus() == C_UnAllowed)	/*��բ�Զ��ָ�ʧ�ܣ���բ��*/
			{
				V_ucReturnFlag = C_Error;
				*V_usOrderExcuteStatus = C_RelayOpen_OpenAlarmfailure;
				break;
			}

			if(V_ucFlag == C_UsedBy645)
			{
				if(V_ulDelayTime == 0x00)	/*��բ�Զ��ָ�����ʱ����Ч*/
				{
					V_ucReturnFlag = C_Error;
					*V_usOrderExcuteStatus = C_TimeUnvalid_AlarmOpenfailure;
					break;
				}
			}

			SF_DealWithSV_Relay();	/*�ڲ���̬��������*/
			PF_CopyDataBytes(pV_ucOperaterCode, SV_ucRelayOperatorCode, 4);	/*�����ߴ��븳ֵ*/
			V_usDataLength = CLMeter_Work_State3;
			InF_Read_Data(CMeter_Work_State3, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*��ȡ�������״̬��3*/
			V_ucDataBuff[0] |= C_RelayOrderStatusOff;	/*�̵�������Ͽ�*/
			InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State3, &V_ucDataBuff[0], CLMeter_Work_State3, C_W_SafeFlag);	/*�������״̬��3д���ݲ�*/

			/*�жϵ�ǰ�����Ƿ�������բ*/
			if(SF_JudgeCurrent_Relay() != C_CurrentOk)
			{
				V_usDataLength = CLRelay_Open_CurrTimer;
				if(InF_Read_Data(CRelay_Open_CurrTimer, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode) != C_OK)	/*�������ʱʱ��*/
				{
					SV_24HourDelayTimer = 1;	/*�������ʱʱ���ó�ֵ*/
				}
				else
				{
					PF_BufferXToUlong32(V_ucDataBuff, &V_ulTime, V_usDataLength);
					if(V_ulTime == 0)
					{
						SV_24HourDelayTimer = 1;	/*�������ʱʱ���ó�ֵ*/
					}
					else
					{
						*V_usOrderExcuteStatus |= C_Relay_DelayOpen_Current_Status;
						V_ucCurrentFlag = 0x68;
						SV_24HourDelayTimer = V_ulTime * 60 * 2;	/*�������ʱʱ���ó�ֵ*/
					}
				}
			}

			if( (V_ucDelayTimeFlag == 0x68) || (V_ucCurrentFlag == 0x68) )
			{
				if(Relay_Stutas.RelaytheoreticStatus != C_RelayOff)
				{
					SF_RealayOpenSignMsgSend_Relay(C_DisplayTwinkle);	/*��բ�ַ���˸*/
					SF_BackLEDMsgSend_Relay(C_DisplayOn);	/*��������*/
				}
				else
				{
					SF_RealayOpenSignMsgSend_Relay(C_DisplayOn);	/*��բ�ַ�����*/
				}	
			}
			
			/*��բ�Զ��ָ���ʱ���ó�ֵ*/
			SV_Comm_CloseRealyDelay_Time = V_ulDelayTime * 60 * 2;
					
			if(V_ucOrderType == C_AlarmOpenRelay_Direct_comm)
			{
				Com_RelayOrder.RelayOrderStatus = C_Open_Direct;	/*Զ�̿�����������բ�Զ��ָ�����ʱʱ�䵽ֱ�Ӻ�բ��*/
			}
			else
			{
				Com_RelayOrder.RelayOrderStatus = C_Open_Allow;	/*Զ�̿�����������բ�Զ��ָ�����ʱʱ�䵽��բ����*/
			}
					
			/*�жϵ�ǰ��������բ��ʱʱ���Ƿ�������բ*/
			if( (V_ucCurrentFlag == 0) && (V_ucDelayTimeFlag == 0) )
			{
				*V_usOrderExcuteStatus = C_AlarmOpenRelay_Status;	
			}
		}break;

		case C_Relay_Open_comm:	/*��բ*/
		{	
			if(Com_RelayOrder.Protect_Current == C_Protect_Current)	/*��բʧ�ܣ����磩*/
			{
				V_ucReturnFlag = C_Error;
				*V_usOrderExcuteStatus = C_Protect_Openfailure;
				break;
			}
			
			SF_DealWithSV_Relay();	/*�ڲ���̬��������*/
			PF_CopyDataBytes(pV_ucOperaterCode, SV_ucRelayOperatorCode, 4);	/*�����ߴ��븳ֵ*/
			
			Com_RelayOrder.RelayOrderStatus = C_Open;	/*Զ�̿�����������բ*/
			
			V_usDataLength = CLMeter_Work_State3;
			InF_Read_Data(CMeter_Work_State3, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*��ȡ�������״̬��3*/
			V_ucDataBuff[0] |= C_RelayOrderStatusOff;	/*�̵�������Ͽ�*/
			InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State3, &V_ucDataBuff[0], CLMeter_Work_State3, C_W_SafeFlag);	/*�������״̬��3д���ݲ�*/
			
			/*�жϵ�ǰ�����Ƿ�������բ*/
			if(SF_JudgeCurrent_Relay() != C_CurrentOk)
			{
				V_usDataLength = CLRelay_Open_CurrTimer;
				if(InF_Read_Data(CRelay_Open_CurrTimer, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode) != C_OK)	/*�������ʱʱ��*/
				{
					SV_24HourDelayTimer = 1;	/*�������ʱʱ���ó�ֵ*/
				}
				else
				{
					PF_BufferXToUlong32(V_ucDataBuff, &V_ulTime, V_usDataLength);
					if(V_ulTime == 0)
					{
						SV_24HourDelayTimer = 1;	/*�������ʱʱ���ó�ֵ*/
					}
					else
					{
						*V_usOrderExcuteStatus |= C_Relay_DelayOpen_Current_Status;
						V_ucCurrentFlag = 0x68;
					}
				}
			}

			if(V_ulDelayTime == 0)	/*�ж���բ��ʱʱ���Ƿ�Ϊ0*/
			{
				SV_OpenRealyDelay_Time = 1;	/*��բ��ʱʱ���ó�ֵ*/
			}
			else
			{
				SV_OpenRealyDelay_Time = V_ulDelayTime * 60 * 2;	/*��բ��ʱʱ���ó�ֵ*/
				V_ucDelayTimeFlag = 0x68;
				if( (V_ucFlag == C_UsedBy645) && (V_ucCurrentFlag == 0x68) )
				{
					*V_usOrderExcuteStatus &= (~C_Relay_DelayOpen_Current_Status);	/*698����645�ù���բ��ʱ��Ϊ0��ͬʱ�������ʱ��բ, ֻ����բ��ʱ*/
				}
				*V_usOrderExcuteStatus |= C_Relay_DelayOpen_Time_Status;
			}

			if( (V_ucDelayTimeFlag == 0x68) || (V_ucCurrentFlag == 0x68) )
			{
				if(Relay_Stutas.RelaytheoreticStatus != C_RelayOff)
				{
					SF_RealayOpenSignMsgSend_Relay(C_DisplayTwinkle);	/*��բ�ַ���˸*/
					SF_BackLEDMsgSend_Relay(C_DisplayOn);	/*��������*/
				}
				else
				{
					SF_RealayOpenSignMsgSend_Relay(C_DisplayOn);	/*��բ�ַ�����*/
				}	
			}	
			else
			{
				*V_usOrderExcuteStatus = C_Relay_Open_Status;	
			}
		}break;
		
		case C_Relay_Close_Allow_comm:	/*��բ����*/
		{	
			if(Com_RelayOrder.Protect_Current == C_Protect_Current_Release)	/*����*/
			{
				SF_DealWithSV_Relay();	/*�ڲ���̬��������*/
				PF_CopyDataBytes(pV_ucOperaterCode, SV_ucRelayOperatorCode, 4);	/*�����ߴ��븳ֵ*/
			}			
			
			V_usDataLength = CLMeter_Work_State3;
			InF_Read_Data(CMeter_Work_State3, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*��ȡ�������״̬��3*/
			V_ucDataBuff[0] &= C_RelayOrderStatusOn;	/*�̵������ͨ*/
			InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State3, &V_ucDataBuff[0], CLMeter_Work_State3, C_W_SafeFlag);	/*�������״̬��3д���ݲ�*/
			
			V_usDataLength = CLRelay_Type;
			InF_Read_Data(CRelay_Type, &V_ucRelayType, &V_usDataLength, &V_usDataEncode);	/*��ȡ���ɿ�������*/

			if( (V_ucRelayType & C_Relay_Type) == 1)
			{
				Com_RelayOrder.RelayOrderStatus = C_Close_Direct;	/*Զ�̿���������ֱ�Ӻ�բ*/
				
				if(Local_RelayOrder.RelayOrderStatus != C_Open)
				{
					SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*��բ�ַ�Ϩ��*/
				}
				if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
				{
					SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*����ر�*/
				}	
			}
			else
			{
				if(Local_RelayOrder.RelayOrderStatus != C_Open)
				{
					SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*��բ�ַ�Ϩ��*/
				
					if(Relay_Stutas.RelaytheoreticStatus == C_RelayOff)
					{
						SF_RelayStatusLEDMsgSend_Relay(C_DisplayTwinkle);	/*��բָʾ����˸*/
					}
				}

				if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
				{
					SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*����ر�*/
				}

				if(Com_RelayOrder.RelayOrderStatus == C_Close_Direct)
				{
					*V_usOrderExcuteStatus = C_Relay_Close_Allow_Status;
					break;	
				}
				
				Com_RelayOrder.RelayOrderStatus = C_Close_Allow;	/*Զ�̿��������������բ*/
				SV_ComOrderNum = SF_GetNewOrderNum();	/*����Զ���������*/
			}
			*V_usOrderExcuteStatus = C_Relay_Close_Allow_Status;
		}break;

		case C_Relay_Close_Direct_comm:	/*ֱ�Ӻ�բ*/
		{	
			if(Com_RelayOrder.Protect_Current == C_Protect_Current_Release)	/*����*/
			{
				SF_DealWithSV_Relay();	/*�ڲ���̬��������*/
				PF_CopyDataBytes(pV_ucOperaterCode, SV_ucRelayOperatorCode, 4);	/*�����ߴ��븳ֵ*/
			}

			V_usDataLength = CLMeter_Work_State3;
			InF_Read_Data(CMeter_Work_State3, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*��ȡ�������״̬��3*/
			V_ucDataBuff[0] &= C_RelayOrderStatusOn;	/*�̵������ͨ*/
			InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State3, &V_ucDataBuff[0], CLMeter_Work_State3, C_W_SafeFlag);	/*�������״̬��3д���ݲ�*/
			
			Com_RelayOrder.RelayOrderStatus = C_Close_Direct;	/*Զ�̿���������ֱ�Ӻ�բ*/
			SV_ComOrderNum = SF_GetNewOrderNum();	/*����Զ���������*/
			
			if(Local_RelayOrder.RelayOrderStatus == C_Close_Allow)
			{
				Local_RelayOrder.RelayOrderStatus = C_Close_Direct;	/*�յ���������󣬿������ñ����ؿ��������ú�բ����*/
				InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_LocalOrder, &Local_RelayOrder.PreWarning, CLRelay_LocalOrder, C_W_SafeFlag);	/*���ؿ�������д���ݲ�*/
				SV_LocalOrderNum = SF_GetNewOrderNum();	/*���±����������*/
			}
			
			if(Local_RelayOrder.RelayOrderStatus != C_Open)
			{
				SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*��բ�ַ�Ϩ��*/
			}
			if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
			{
				SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*����ر�*/
			}	
			
			*V_usOrderExcuteStatus = C_Relay_Close_Direct_Status;			
		}break;

		case C_Protect_Current_comm:	/*����*/
		{
			SF_DealWithSV_Relay();	/*�ڲ���̬��������*/
			PF_CopyDataBytes(pV_ucOperaterCode, SV_ucRelayOperatorCode, 4);	/*�����ߴ��븳ֵ*/
			
			V_usDataLength = CLMeter_Work_State3;
			InF_Read_Data(CMeter_Work_State3, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*��ȡ�������״̬��3*/
			V_ucDataBuff[0] &= C_RelayOrderStatusOn;	/*�̵������ͨ*/
			V_ucDataBuff[1] |= C_RelayProtect_Current;	/*�̵�������*/
			InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State3, &V_ucDataBuff[0], CLMeter_Work_State3, C_W_SafeFlag);	/*�������״̬��3д���ݲ�*/
			
			V_usDataLength = CLRelay_Type;
			InF_Read_Data(CRelay_Type, &V_ucRelayType, &V_usDataLength, &V_usDataEncode);	/*��ȡ���ɿ�������*/
			
			if( (V_ucRelayType & C_Relay_Type) == 1)	
			{
				SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*��բ�ַ�Ϩ��*/
				
				if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
				{
					SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*�رձ���*/
				}
			
				Com_RelayOrder.RelayOrderStatus = C_Close_Direct;	/*�յ���������󣬿������ñ�Զ��������Ϊֱ�Ӻ�բ*/
				InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, CLRelay_RemoteOrder, C_W_SafeFlag);	/*Զ�̿�������д���ݲ�*/
			
				Local_RelayOrder.RelayOrderStatus = C_Close_Direct;	/*�յ���������󣬿������ñ����ؿ���������ֱ�Ӻ�բ*/
				InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_LocalOrder, &Local_RelayOrder.PreWarning, CLRelay_LocalOrder, C_W_SafeFlag);	/*���ؿ�������д���ݲ�*/
			}
			else
			{
				SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*��բ�ַ�Ϩ��*/
				
				if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
				{
					SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*�رձ���*/
				}
					
				if(Relay_Stutas.RelaytheoreticStatus == C_RelayOff)
				{				
					SF_RelayStatusLEDMsgSend_Relay(C_DisplayTwinkle);	/*��բָʾ����˸*/
				}					
				
				if(Local_RelayOrder.RelayOrderStatus != C_Close_Direct)
				{
					Local_RelayOrder.RelayOrderStatus = C_Close_Allow;	/*�յ���������󣬿������ñ����ؿ��������ú�բ����*/
					InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_LocalOrder, &Local_RelayOrder.PreWarning, CLRelay_LocalOrder, C_W_SafeFlag);	/*���ؿ�������д���ݲ�*/
					SV_LocalOrderNum = SF_GetNewOrderNum();	/*���±����������*/
				}

				if(Com_RelayOrder.RelayOrderStatus != C_Close_Direct)
				{
					Com_RelayOrder.RelayOrderStatus = C_Close_Allow;	/*�յ���������󣬿������ñ�Զ��������Ϊ��բ����*/
					InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, CLRelay_RemoteOrder, C_W_SafeFlag);	/*Զ�̿�������д���ݲ�*/
					SV_ComOrderNum = SF_GetNewOrderNum();	/*����Զ���������*/
				}	
			}
			
			Com_RelayOrder.Protect_Current = C_Protect_Current;	/*Զ�̿��������ñ���*/
			*V_usOrderExcuteStatus = C_Protect_Current_Status;
			
			if(C_Meter_Type == C_L_SmartMeter)	/*���ر�*/
			{
				V_ucDataBuff_Msg[0] = Pt_ParaMetersChange;
				V_ucDataBuff_Msg[1] = C_ReworkWarningPara;	/*�������*/
			
				SF_MsgSend_Relay(V_ucDataBuff_Msg, Pt_ParaMetersChange+1, C_Msg_EnergyMetering);	/*��������ģ����������Ϣ*/

			}
		}break;

		case C_Protect_Current_Release_comm:	/*������*/
		{	
			V_usDataLength = CLMeter_Work_State3;
			InF_Read_Data(CMeter_Work_State3, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*��ȡ�������״̬��3*/
			V_ucDataBuff[1] &= C_RelayProtect_Current_Release;	/*�̵����Ǳ���*/
			InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State3, &V_ucDataBuff[0], CLMeter_Work_State3, C_W_SafeFlag);	/*�������״̬��3д���ݲ�*/
			
			Com_RelayOrder.Protect_Current = C_Protect_Current_Release;	/*Զ�̿��������÷Ǳ���*/
			
			if(C_Meter_Type == C_L_SmartMeter)	/*���ر�*/
			{
				V_ucDataBuff_Msg[0] = Pt_ParaMetersChange;
				V_ucDataBuff_Msg[1] = C_ReworkWarningPara;	/*�������*/
				
				SF_MsgSend_Relay(V_ucDataBuff_Msg, Pt_ParaMetersChange + 1, C_Msg_EnergyMetering);	/*��������ģ����������Ϣ*/
			}
			
			*V_usOrderExcuteStatus = C_Protect_Current_Release_Status;
		}break;
		
		default:
		{	
			V_ucReturnFlag = C_Error;
			*V_usOrderExcuteStatus = C_PasswordError_failure;
		}break;	
	}
	InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, CLRelay_RemoteOrder, C_W_SafeFlag);	/*Զ�̿�������д���ݲ�*/
		
	ushort16 V_usRelayRelayStatus = 0;

	if(V_ucReturnFlag == C_OK)
	{
		PF_Ushort16ToBuffer2(V_ucDataBuff, V_usOrderExcuteStatus);
		PF_Ushort16ToBuffer2(&V_ucDataBuff[2], &V_usRelayRelayStatus);
		InF_Write_Data(C_Msg_Deal_RelayStatus, CControl_ExecuteState, V_ucDataBuff, CLControl_ExecuteState, C_W_SafeFlag);	/*��������ִ��״̬��*/
		InF_Write_Data(C_Msg_Deal_RelayStatus, CControl_ErrorState, &V_ucDataBuff[2], CLControl_ErrorState, C_W_SafeFlag);	/*�����������״̬��*/
	}
	else
	{
		PF_Ushort16ToBuffer2(V_ucDataBuff, &V_usRelayRelayStatus);
		PF_Ushort16ToBuffer2(&V_ucDataBuff[2], V_usOrderExcuteStatus);
		InF_Write_Data(C_Msg_Deal_RelayStatus, CControl_ExecuteState, V_ucDataBuff, CLControl_ExecuteState, C_W_SafeFlag);	/*��������ִ��״̬��*/
		InF_Write_Data(C_Msg_Deal_RelayStatus, CControl_ErrorState, &V_ucDataBuff[2], CLControl_ErrorState, C_W_SafeFlag);	/*�����������״̬��*/
	}

	return V_ucReturnFlag;
}

/*******************************************************************************
����ԭ�ͣ�void Msg_Deal_RelayStatus(Str_Msg_Parameter *P_Msg)
�����������̵�����Ϣ����
�����������Ϣ�����ṹ��
�����������
���ز�������
����λ�ã�
��    ע��������仯���ú��������仯���øú���������ģ�鷢����Ϣ��
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
		return;	/*���ܱ�֧��*/
	}

	pV_ucParm = pStr_Msg_Parameter->Parameter;
	if(pStr_Msg_Parameter->PowerFlag != C_PowerOn)
	{
		return;
	}
	if( (*pV_ucParm == Pt_MeterClear) && (pStr_Msg_Parameter->Length == Pt_MeterClear_Len + 1) )	/*ͨ��������Ϣ*/
	{
		V_usDataLength = CLMeter_Work_State1;
		InF_Read_Data(CMeter_Work_State1, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*��ȡ�������״̬��1*/
		V_ucDataBuff[1] &= C_ControlLoopNoError;	/*����ƻ�·��*/
		InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State1, &V_ucDataBuff[0], CLMeter_Work_State1, C_W_SafeFlag);	/*�������״̬��1д���ݲ�*/
		SV_Error_Time = 0x00;
#if 0
		V_usDataLength = CLMeter_Work_State3;
		InF_Read_Data(CMeter_Work_State3, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*��ȡ�������״̬��3*/
		V_ucDataBuff[0] &= C_RelayStatusOn_External;	/*���ü̵��������ź�״̬��0(0:ͨ 1:��)*/
		InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State3, &V_ucDataBuff[0], CLMeter_Work_State1, C_W_SafeFlag);	/*�������״̬��3д���ݲ�*/
		SV_ucExternalRelayStatusTime = 0;	/*���ü̵��������ź�5s���ʱ������*/
#endif
		V_usDataLength = CLRelay_Type;
		InF_Read_Data(CRelay_Type, &V_ucRelayType, &V_usDataLength, &V_usDataEncode);	/*��ȡ���ɿ�������*/
	
		V_usDataLength = CLRelay_State;
		InF_Read_Data(CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, &V_usDataLength, &V_usDataEncode);	/*��ȡ�̵���״̬*/
	
		if( (V_ucRelayType & C_Relay_Type) == 1)
		{
			if(Relay_Stutas.RelaytheoreticStatus == C_RelayOn)
			{
				Relay_Stutas.RelayRealStatus = C_RelayOn;	
				InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, CLRelay_State, C_W_SafeFlag);	/*�̵���״̬д���ݲ�*/
				SF_RelayStatusLEDMsgSend_Relay(C_DisplayOff);	/*��բָʾ��Ϩ��*/
			}
		}
		if(Relay_Stutas.RelaytheoreticStatus == C_RelayOff)	/*����״̬Ϊ��բ*/
		{
			SV_EventOut_Err_Relay[0] = C_EventOutOpenErr_Relay;	/*��ʾ��Ҫ�ϱ����ɿ��������¼�*/
			V_usDataCRC = PF_Cal_CRC(SV_EventOut_Err_Relay, 1);
			PF_Ushort16ToBuffer2(&SV_EventOut_Err_Relay[1], &V_usDataCRC);	
		}
		if(Relay_Stutas.RelaytheoreticStatus == C_RelayOn)	/*����״̬Ϊ��բ*/
		{
			SV_EventOut_Err_Relay[0] = C_EventOutCloseErr_Relay;	/*��ʾ��Ҫ�ϱ����ɿ��������¼�*/
			V_usDataCRC = PF_Cal_CRC(SV_EventOut_Err_Relay, 1);
			PF_Ushort16ToBuffer2(&SV_EventOut_Err_Relay[1], &V_usDataCRC);		
		}
		
		SV_EventOut_Open_Relay[0] = C_EventOutNot_Relay;	/*��ʾ����Ҫ�ϱ���բ�ɹ��¼� lzy20150714*/
		V_usDataCRC = PF_Cal_CRC(SV_EventOut_Open_Relay, 1);
		PF_Ushort16ToBuffer2(&SV_EventOut_Open_Relay[1], &V_usDataCRC); 
		
		SV_EventOut_Close_Relay[0] = C_EventOutNot_Relay;	/*��ʾ����Ҫ�ϱ���բ�ɹ��¼� lzy20150714*/
		V_usDataCRC = PF_Cal_CRC(SV_EventOut_Close_Relay, 1);
		PF_Ushort16ToBuffer2(&SV_EventOut_Close_Relay[1], &V_usDataCRC);	
		
		if(C_Meter_Type == C_L_SmartMeter)	/*���ر�*/
		{
			InF_DealwithComRelayOrder(C_Alarm_Release_comm, V_ucOperaterCode, 0x00, &V_usOrderExcuteStatus, C_UsedBy698);	
			InF_DealwithComRelayOrder(C_Relay_Close_Direct_comm, V_ucOperaterCode, 0x00, &V_usOrderExcuteStatus, C_UsedBy698);
			if( (V_ucRelayType & C_Relay_Type) == 1)	/*20150731�޸ģ�������ر�����������ʱ�õ�������ʶ*/
			{
				SV_ClearFlag = 0x68;	/*��������ʶ*/
			}
		}
		else	/*20150731�޸ģ�Զ�̱�������������Ҳ���Զ����բ״̬*/
		{
			if( (V_ucRelayType & C_Relay_Type) == 1)
			{
				InF_DealwithComRelayOrder(C_Relay_Close_Direct_comm, V_ucOperaterCode, 0x00, &V_usOrderExcuteStatus, C_UsedBy698);	
				SV_ClearFlag = 0x68;	/*��������ʶ*/
			}
		}
	}
	else if( (*pV_ucParm == Pt_EventClearDI) && (pStr_Msg_Parameter->Length == Pt_EventClearDI_Len+1) )	/*ͨ���¼�������Ϣ*/
	{
		PF_Buffer4ToUlong32(pV_ucParm + 1, &V_ulDataCode, 4);

		if( (V_ulDataCode == C_EventClearSingle) || (V_ulDataCode == C_EventClearAll) )
		{
			V_usDataLength = CLMeter_Work_State1;
			InF_Read_Data(CMeter_Work_State1, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*��ȡ�������״̬��1*/
			V_ucDataBuff[1] &= C_ControlLoopNoError;	/*����ƻ�·��*/
			InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State1, &V_ucDataBuff[0], CLMeter_Work_State1, C_W_SafeFlag);	/*�������״̬��1д���ݲ�*/
			SV_Error_Time = 0x00;	
		}

		if(V_ulDataCode == C_EventClearAll)
		{
			if(Relay_Stutas.RelaytheoreticStatus == C_RelayOff)	/*����״̬Ϊ��բ*/
			{
				SV_EventOut_Err_Relay[0] = C_EventOutOpenErr_Relay;	/*��ʾ��Ҫ�ϱ����ɿ��������¼�*/
				V_usDataCRC = PF_Cal_CRC(SV_EventOut_Err_Relay, 1);
				PF_Ushort16ToBuffer2(&SV_EventOut_Err_Relay[1], &V_usDataCRC);	
			}
			if(Relay_Stutas.RelaytheoreticStatus == C_RelayOn)	/*����״̬Ϊ��բ*/
			{
				SV_EventOut_Err_Relay[0] = C_EventOutCloseErr_Relay;	/*��ʾ��Ҫ�ϱ����ɿ��������¼�*/
				V_usDataCRC = PF_Cal_CRC(SV_EventOut_Err_Relay, 1);
				PF_Ushort16ToBuffer2(&SV_EventOut_Err_Relay[1], &V_usDataCRC);		
			}
			
			SV_EventOut_Open_Relay[0] = C_EventOutNot_Relay;	/*��ʾ����Ҫ�ϱ���բ�ɹ��¼� lzy20150714*/
			V_usDataCRC = PF_Cal_CRC(SV_EventOut_Open_Relay, 1);
			PF_Ushort16ToBuffer2(&SV_EventOut_Open_Relay[1], &V_usDataCRC); 
			
			SV_EventOut_Close_Relay[0] = C_EventOutNot_Relay;	/*��ʾ����Ҫ�ϱ���բ�ɹ��¼� lzy20150714*/
			V_usDataCRC = PF_Cal_CRC(SV_EventOut_Close_Relay, 1);
			PF_Ushort16ToBuffer2(&SV_EventOut_Close_Relay[1], &V_usDataCRC);		
		}
	}
	else if( (*pV_ucParm == Pt_RelayStateFlag) && (pStr_Msg_Parameter->Length == Pt_RelayStateFlag_Len + 1) )	/*����ģ�鴥���̵���������Ϣ*/
	{
		if(C_Meter_Type == C_L_SmartMeter)	/*���ر�*/
		{
			SF_LocalControl_Relay(*(pV_ucParm + 1) );	
		}			
	}
	else if( (*pV_ucParm == Pt_CardFlag) && (pStr_Msg_Parameter->Length == Pt_CardFlag_Len + 1) )	/*�忨��Ϣ*/
	{
		if(C_Meter_Type == C_L_SmartMeter)	/*���ر�*/
		{
			SF_Cardor3sCloseRelayTask_Relay();	
		}			
	}
	else if( (*pV_ucParm == Pt_Dispatch_Key) && (pStr_Msg_Parameter->Length == Pt_Dispatch_Key_Len + 1) && (*(pV_ucParm + 1) == C_Key3s) )	/*���Ȱ���3s��Ϣ*/
	{
		SF_Cardor3sCloseRelayTask_Relay();	
	}
	else if( (*pV_ucParm == Pt_Dispatch_Timing) && (pStr_Msg_Parameter->Length == Pt_Dispatch_Timing_Len + 1) )	/*����ʱ����Ϣ*/
	{
		if(*(pV_ucParm + 1) == C_HalfSecond)	/*���Ȼ�������500ms	*/
		{
			SF_TimeTask_Relay();	
		}	
		else if(*(pV_ucParm + 1) == C_SystemSecondChange)	/*����ϵͳ��仯	*/
		{
			SF_Event_RelayCheck_Relay();	
		}
	}
	return;	
}

/*******************************************************************************
����ԭ�ͣ�void SF_LocalControl_Relay(uchar8 V_RelayOrder)
�������������ر����������Ϣ����
���������V_RelayOrder�����ؼ̵�����������
�����������
���ز�������
����λ�ã��ú�����Msg_Deal_RelayStatus��������
��    ע������ģ�鴥���̵���������Ϣʱ����
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
	InF_Read_Data(CRelay_LocalOrder, &Local_RelayOrder.PreWarning, &V_usDataLength, &V_usDataEncode);	/*��ȡ���ؿ�������*/
	
	V_usDataLength = CLRelay_RemoteOrder;
	InF_Read_Data(CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, &V_usDataLength, &V_usDataEncode);	/*��ȡԶ�̿�������*/
	
	V_usDataLength = CLRelay_State;
	InF_Read_Data(CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, &V_usDataLength, &V_usDataEncode);	/*��ȡ�̵���״̬*/
	
	V_ucRelayOrderStatus = Local_RelayOrder.RelayOrderStatus;	/*��ֵ���ؼ̵��������ֵ*/
	V_ucPreWarningStatus = Local_RelayOrder.PreWarning;	/*��ֵ�̵���Ԥ��բ���������ֵ*/
	
	switch(V_ucRelayOrder)
	{
		case C_Alarm:	/*����*/
		{
			V_ucPreWarningStatus = C_PreWarning;
			SV_Relay_L_OpenFlag[0] = 0x00;	/*��Ԥ��բ��ʶ*/
		}break;
		
		case C_Alarm_Release:	/*�������*/
		{			
			V_ucPreWarningStatus = C_PreWarning_Release;
			SV_Relay_L_OpenFlag[0] = 0x00;	/*��Ԥ��բ��ʶ*/
		}break;	
		
		case C_AlarmOpenRelay:	/*Ԥ��բ*/
		{
			if(Local_RelayOrder.RelayOrderStatus == C_Open)
			{
				break;	
			}
			if( (PF_Check_CRC(SV_Relay_L_OpenFlag, 3) == C_OK) && (SV_Relay_L_OpenFlag[0] == C_Pre_Open) )	
			{
				break;
			}
			
			if(Com_RelayOrder.Protect_Current == C_Protect_Current_Release)	/*������*/
			{
				SF_Judge1D1EOrderStatus();	/*ͨ����բ�Զ��ָ������*/
				SV_24HourDelayTimer = 0x00;	/*�����������޵�����ʱ*/
				SV_RelayRework_Timer = 0x00;	/*�ظ�������ʱ��*/
				SV_RelayOpenAfterPowerUp = 0x00;	/*�ϵ�ʱ������բ״̬Ҫ����բ���ϵ���0x68���ù�������*/
				SV_ClearFlag = 0x00;	/*��������ʶ*/
				if( (SV_RelayDisplayStatus&C_RelayStatusLEDTwinkle) == C_RelayStatusLEDTwinkle)
				{
					SF_RelayStatusLEDMsgSend_Relay(C_DisplayOff);	/*��բָʾ��Ϩ��*/
				}
				
				PF_CopyDataBytes(V_ucOperaterCode, SV_ucRelayOperatorCode, 4);	/*�����ߴ��븳ֵ*/
				
				SV_L_CloseRealyDelay_Time = C_L_CloseRealyDelay_Time;	/*������բ��ʱʱ���ó�ֵ*/
				
				V_ucRelayOrderStatus = C_Pre_Open;	
			}
			
			V_ucPreWarningStatus = C_PreWarning;	/*����*/
			
			SV_Relay_L_OpenFlag[0] = C_Pre_Open;	/*����Ԥ��բ��ʶ���յ�����������ʱ�˱�ʶ��Ч�򴥷�������բ��Ϣ*/
			V_usDataCRC = PF_Cal_CRC(SV_Relay_L_OpenFlag, 1);
			PF_Ushort16ToBuffer2(&SV_Relay_L_OpenFlag[1], &V_usDataCRC);
		}break;
		
		case C_Relay_OpenNow:	/*������բ*/
		{
			if(Local_RelayOrder.RelayOrderStatus == C_Open)	/*�����ǰ�Ѿ���������բ״̬����ֱ���˳�*/
			{
				break;	
			}
			
			if(Com_RelayOrder.Protect_Current == C_Protect_Current_Release)	/*������*/
			{
				SF_Judge1D1EOrderStatus();	/*ͨ����բ�Զ��ָ������*/
				/*�ڲ���̬��������*/
				SV_L_CloseRealyDelay_Time = 0x00;	/*���ر���һ����բ�������բ��ʱʱ��*/
				SV_24HourDelayTimer = 0x00;	/*�����������޵�����ʱ*/
				SV_RelayRework_Timer = 0x00;	/*�ظ�������ʱ��*/
				SV_RelayOpenAfterPowerUp = 0x00;	/*�ϵ�ʱ������բ״̬Ҫ����բ���ϵ���0x68���ù�������*/
				SV_ClearFlag = 0x00;	/*��������ʶ*/
				if( (SV_RelayDisplayStatus&C_RelayStatusLEDTwinkle) == C_RelayStatusLEDTwinkle)
				{
					SF_RelayStatusLEDMsgSend_Relay(C_DisplayOff);	/*��բָʾ��Ϩ��*/
				}
				
				PF_CopyDataBytes(V_ucOperaterCode, SV_ucRelayOperatorCode, 4);	/*�����ߴ��븳ֵ*/
				V_ucRelayOrderStatus = C_Open;
			}
			V_ucPreWarningStatus = C_PreWarning;	/*����*/
			SV_Relay_L_OpenFlag[0] = 0x00;	/*��Ԥ��բ��ʶ*/
		}break;	
		
		case C_Relay_Close_Direct:	/*��բ����*/
		{
			SV_Relay_L_OpenFlag[0] = 0x00;	/*��Ԥ��բ��ʶ*/
			
			if( (Local_RelayOrder.RelayOrderStatus == C_Close_Direct)
				|| ( (Local_RelayOrder.RelayOrderStatus == C_Close_Allow) 
				&& (SV_L_CloseRealyDelay_Time == 0) ) )
			{
				break;	/*SV_L_CloseRealyDelay_Time == 0, ��ʾ����Ԥ��բ�ĺ�բ����*/
			}
			
			if(Com_RelayOrder.Protect_Current == C_Protect_Current_Release)	/*������*/
			{
				/*�ڲ���̬��������*/
				SV_L_CloseRealyDelay_Time = 0x00;	/*���ر���һ����բ�������բ��ʱʱ��*/
				SV_24HourDelayTimer = 0x00;	/*�����������޵�����ʱ*/
				SV_RelayRework_Timer = 0x00;	/*�ظ�������ʱ��*/
				SV_RelayOpenAfterPowerUp = 0x00;	/*�ϵ�ʱ������բ״̬Ҫ����բ���ϵ���0x68���ù�������*/
				SV_ClearFlag = 0x00;	/*��������ʶ*/
				if( (SV_RelayDisplayStatus&C_RelayStatusLEDTwinkle) == C_RelayStatusLEDTwinkle)
				{
					SF_RelayStatusLEDMsgSend_Relay(C_DisplayOff);	/*��բָʾ��Ϩ��*/
				}
				PF_CopyDataBytes(V_ucOperaterCode, SV_ucRelayOperatorCode, 4);	/*�����ߴ��븳ֵ*/
			}
			
			V_usDataLength = CLRelay_Type;
			InF_Read_Data(CRelay_Type, &V_ucRelayType, &V_usDataLength, &V_usDataEncode);	/*��ȡ���ɿ�������*/
			if( (V_ucRelayType & C_Relay_Type) == 1)
			{
				V_ucRelayOrderStatus = C_Close_Direct;	/*����������ֱ�Ӻ�բ*/
				
				if(Com_RelayOrder.RelayOrderStatus != C_Open)
				{
					SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*��բ�ַ�Ϩ��*/
				}
				if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
				{
					SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*����ر�*/
				}
			}
			else
			{
				V_ucRelayOrderStatus = C_Close_Allow;	/*���������������բ*/
				SV_LocalOrderNum = SF_GetNewOrderNum();	/*���±����������*/
				
				if(Com_RelayOrder.RelayOrderStatus != C_Open)
				{
					SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*��բ�ַ�Ϩ��*/

					if(Relay_Stutas.RelaytheoreticStatus == C_RelayOff)
					{				
						SF_RelayStatusLEDMsgSend_Relay(C_DisplayTwinkle);	/*��բָʾ����˸*/
					}
				}
				if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
				{
					SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*����ر�*/
				}
			}
		}break;
		
		case C_PurchaseOK:	/*��ֵ�ɹ�*/
		{
#if 0
			if( ( (Local_RelayOrder.RelayOrderStatus == C_Pre_Open) || (Local_RelayOrder.RelayOrderStatus == C_Close_Allow) ) && (SV_L_CloseRealyDelay_Time != 0) )	/*��ǰ���ڱ���Ԥ��բ״̬��������բ��ʱʱ�䲻Ϊ0*/
			{
				SV_L_CloseRealyDelay_Time = 0;
				
				V_usDataLength = CLRelay_Type;
				InF_Read_Data(CRelay_Type, &V_ucRelayType, &V_usDataLength, &V_usDataEncode);	/*��ȡ���ɿ�������*/
				if( (V_ucRelayType & C_Relay_Type) == 1)
				{
					V_ucRelayOrderStatus = C_Close_Direct;	/*����������ֱ�Ӻ�բ*/
					
					if(Com_RelayOrder.RelayOrderStatus != C_Open)
					{
						SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*��բ�ַ�Ϩ��*/
					}
				}
				else
				{
					V_ucRelayOrderStatus = C_Close_Allow;	/*���������������բ*/
					SV_LocalOrderNum = SF_GetNewOrderNum();	/*���±����������*/
					
					if(Com_RelayOrder.RelayOrderStatus != C_Open)
					{
						SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*��բ�ַ�Ϩ��*/
				
						if(Relay_Stutas.RelaytheoreticStatus == C_RelayOff)
						{				
							SF_RelayStatusLEDMsgSend_Relay(C_DisplayTwinkle);	/*��բָʾ����˸*/
						}
					}
					if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
					{
						SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*����ر�*/
					}
				}
			}
#endif
			if( (Com_RelayOrder.RelayOrderStatus == C_Open_Direct) && (SV_Comm_CloseRealyDelay_Time != 0) )
			{
				SF_DealWithSV_Relay();	/*�ڲ���̬��������*/
				PF_CopyDataBytes(V_ucOperaterCode, SV_ucRelayOperatorCode, 4);	/*�����ߴ��븳ֵ*/
				
				Com_RelayOrder.RelayOrderStatus = C_Close_Direct;
				InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, CLRelay_RemoteOrder, C_W_SafeFlag);	/*Զ�̿�������д���ݲ�*/
				SV_ComOrderNum = SF_GetNewOrderNum();	/*����Զ���������*/
				
				if(Local_RelayOrder.RelayOrderStatus != C_Open)
				{
					SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*��բ�ַ�Ϩ��*/
				}
				
				if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
				{
					SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*����ر�*/
				}
					
				V_usDataLength = CLMeter_Work_State3;
				InF_Read_Data(CMeter_Work_State3, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*��ȡ�������״̬��3*/
				V_ucDataBuff[0] &= C_RelayOrderStatusOn;	/*�̵������ͨ*/
				InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State3, &V_ucDataBuff[0], CLMeter_Work_State3, C_W_SafeFlag);	/*�������״̬��3д���ݲ�*/
			}
			if( (Com_RelayOrder.RelayOrderStatus == C_Open_Allow) && (SV_Comm_CloseRealyDelay_Time != 0) )
			{
				SF_DealWithSV_Relay();	/*�ڲ���̬��������*/
				PF_CopyDataBytes(V_ucOperaterCode, SV_ucRelayOperatorCode, 4);	/*�����ߴ��븳ֵ*/
				
				V_usDataLength = CLRelay_Type;
				InF_Read_Data(CRelay_Type, &V_ucRelayType, &V_usDataLength, &V_usDataEncode);	/*��ȡ���ɿ�������*/
				if( (V_ucRelayType & C_Relay_Type) == 1)
				{
					Com_RelayOrder.RelayOrderStatus = C_Close_Direct;	/*Զ�̿���������ֱ�Ӻ�բ*/
					InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, CLRelay_RemoteOrder, C_W_SafeFlag);	/*Զ�̿�������д���ݲ�*/
					
					if(Local_RelayOrder.RelayOrderStatus != C_Open)
					{
						SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*��բ�ַ�Ϩ��*/
					}
					
					if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
					{
						SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*����ر�*/
					}
				}
				else
				{
					Com_RelayOrder.RelayOrderStatus = C_Close_Allow;
					InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, CLRelay_RemoteOrder, C_W_SafeFlag);	/*Զ�̿�������д���ݲ�*/
					SV_ComOrderNum = SF_GetNewOrderNum();	/*����Զ���������*/
					
					if(Local_RelayOrder.RelayOrderStatus != C_Open)
					{
						SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*��բ�ַ�Ϩ��*/
						
						if(Relay_Stutas.RelaytheoreticStatus == C_RelayOff)
						{
							SF_RelayStatusLEDMsgSend_Relay(C_DisplayTwinkle);	/*��բָʾ����˸*/
						}	
					}
					
					if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
					{
						SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*����ر�*/
					}	
				}
				
				V_usDataLength = CLMeter_Work_State3;
				InF_Read_Data(CMeter_Work_State3, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*��ȡ�������״̬��3*/
				V_ucDataBuff[0] &= C_RelayOrderStatusOn;	/*�̵������ͨ*/
				InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State3, &V_ucDataBuff[0], CLMeter_Work_State3, C_W_SafeFlag);	/*�������״̬��3д���ݲ�*/
			}
		}break;
		
		case C_Relay_Close_Direct_Init:	/*��բ*/
		{
			SV_Relay_L_OpenFlag[0] = 0x00;	/*��Ԥ��բ��ʶ*/
			
			if(Com_RelayOrder.Protect_Current == C_Protect_Current_Release)	/*������*/
			{
				/*�ڲ���̬��������*/
				SV_L_CloseRealyDelay_Time = 0x00;	/*���ر���һ����բ�������բ��ʱʱ��*/
				SV_24HourDelayTimer = 0x00;	/*�����������޵�����ʱ*/
				SV_RelayRework_Timer = 0x00;	/*�ظ�������ʱ��*/
				SV_RelayOpenAfterPowerUp = 0x00;	/*�ϵ�ʱ������բ״̬Ҫ����բ���ϵ���0x68���ù�������*/
				if( (SV_RelayDisplayStatus&C_RelayStatusLEDTwinkle) == C_RelayStatusLEDTwinkle)
				{
					SF_RelayStatusLEDMsgSend_Relay(C_DisplayOff);	/*��բָʾ��Ϩ��*/
				}
				
				PF_CopyDataBytes(V_ucOperaterCode, SV_ucRelayOperatorCode, 4);	/*�����ߴ��븳ֵ*/
			}

			V_ucRelayOrderStatus = C_Close_Direct;	/*����������ֱ�Ӻ�բ*/
			SV_LocalOrderNum = SF_GetNewOrderNum();	/*���±����������*/
				
			if(Com_RelayOrder.RelayOrderStatus != C_Open)
			{
				SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*��բ�ַ�Ϩ��*/
			}
			if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
			{
				SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*����ر�*/
			}
		}break;
		
		default:
		{

		}break;	
	}

	if(Local_RelayOrder.RelayOrderStatus != V_ucRelayOrderStatus)
	{
		Local_RelayOrder.RelayOrderStatus = V_ucRelayOrderStatus;
		InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_LocalOrder, &Local_RelayOrder.PreWarning, CLRelay_LocalOrder, C_W_SafeFlag);	/*���ؿ�������д���ݲ�*/
	}
	if(Local_RelayOrder.PreWarning != V_ucPreWarningStatus)
	{
		Local_RelayOrder.PreWarning = V_ucPreWarningStatus;
		InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_LocalOrder, &Local_RelayOrder.PreWarning, CLRelay_LocalOrder, C_W_SafeFlag);	/*���ؿ�������д���ݲ�*/
	}	

	return;
}

/*******************************************************************************
����ԭ�ͣ�uchar8 SF_JudgeCurrent_Relay(void)
������������������ֵ�ж�
�����������
�����������
���ز�����C_CurrentOk����ǰ����ֵ��С�����޵�����������բ��C_CurrentOver����ǰ����������г������޵���ֵ�ģ���������բ
����λ�ã�
��    ע��1���յ���բ�������øú������жϵ�ǰ�����Ƿ�������բ��������բ���Ƶ������ޱ�����ʱʱ�䣩
          2������բ֮ǰ���øú����ж��Ƿ������բҪ��
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
	InF_Read_Data(CRelay_Type, &V_ucRelayType, &V_usDataLength, &V_usDataEncode);	/*��ȡ���ɿ�������*/
	if( (V_ucRelayType & C_Relay_Type) == 0)	/*�������ñ�������ֵ����*/
	{
		V_usDataLength = CLRelay_Open_CurrTreshold;
		if(InF_Read_Data(CRelay_Open_CurrTreshold, V_ucData, &V_usDataLength, &V_usDataEncode) != C_OK)	/*��ȡ�̵�����բ���Ƶ�������ֵ*/
		{
			V_lRelay_OpenCurrTreshold = 0;
		}
		else
		{
			PF_BufferXToUlong32(&V_ucData[0], (ulong32 *)&V_lRelay_OpenCurrTreshold, V_usDataLength);			
		}
		if(V_lRelay_OpenCurrTreshold == 0)
		{
			return V_ucReturnFlag;	/*���޵���ֵΪ0���ù��ܲ�����*/
		}

		V_usDataLength = CLPhaseFF_Curr_4Dig;
		InF_Read_Data(CPhaseFF_Curr_4Dig, V_ucCurrent, &V_usDataLength, &V_usDataEncode);	/*��ȡ����ֵ*/
		PF_BufferXToUlong32(&V_ucCurrent[0], (ulong32 *)&V_lCurrentHEX_ABC[0], CLPhaseA_Curr_4Dig);
		V_lCurrentHEX_ABC[0] = SF_ABS(V_lCurrentHEX_ABC[0]);
		PF_BufferXToUlong32(&V_ucCurrent[4], (ulong32 *)&V_lCurrentHEX_ABC[1], CLPhaseB_Curr_4Dig);
		V_lCurrentHEX_ABC[1] = SF_ABS(V_lCurrentHEX_ABC[1]);
		PF_BufferXToUlong32(&V_ucCurrent[8], (ulong32 *)&V_lCurrentHEX_ABC[2], CLPhaseC_Curr_4Dig);
		V_lCurrentHEX_ABC[2] = SF_ABS(V_lCurrentHEX_ABC[2]);

		if( (V_lCurrentHEX_ABC[0] > V_lRelay_OpenCurrTreshold) || (V_lCurrentHEX_ABC[1] > V_lRelay_OpenCurrTreshold) || (V_lCurrentHEX_ABC[2] > V_lRelay_OpenCurrTreshold) )
		{
			V_ucReturnFlag = C_CurrentOver;	/*����һ�������������ֵ ���ش���*/
		}
	}
	
	return V_ucReturnFlag;
}

/*******************************************************************************
����ԭ�ͣ�void SF_Event_CloseRelay_Relay(void)
����������д��բ��¼
�����������
�����������
���ز�������
����λ�ã��ú�����SF_CombineOrderExecute_Relay˽�к�������
��    ע��
*******************************************************************************/
void SF_Event_CloseRelay_Relay(void)
{
	uchar8	V_ucDataBuff[300] = {0};
	uchar8	V_ucEventFlag;
	ushort16	V_usOffset = 0, V_usResidualLength;
	ushort16	V_usDataLength;
	ushort16	V_usDataEncode = 0;
	
	V_usDataLength = CLRelayClose_Degree;
	InF_Read_Data(CRelayClose_Degree, V_ucDataBuff, &V_usDataLength, &V_usDataEncode);	/*���¼����*/
	V_usOffset += 4;
	
	V_usDataLength = CLDate_Week_Time;
	InF_Read_Data(CDate_Time, &V_ucDataBuff[V_usOffset], &V_usDataLength, &V_usDataEncode);	/*���¼�����ʱ�䣬����ʱ��Ϊ00000000000000*/
	V_usOffset += 7;
	V_usOffset += 7;
	V_usOffset += 1;	/*����Դ����*/
	V_usOffset += 1;	/*�ϱ�״̬����*/
	
	V_usResidualLength = 300 - V_usOffset;	/*ʣ��buff����*/
	V_ucEventFlag = 0x01;
	if(Inf_GetRecordData(&V_ucDataBuff[V_usOffset], &V_usResidualLength, CRelayClose_OADTab, V_ucEventFlag) != C_OK)	/*��ȡ����OAD����*/
	{
		return;
	}
	V_usOffset += V_usResidualLength;	/*�����ܳ���*/

	InF_Write_Data(C_Msg_Deal_RelayStatus, CRelayClose_FF_1, V_ucDataBuff, V_usOffset, C_W_SafeFlag);	/*д��բ��¼*/
	Inf_EventReport_HP(C_RelayCloseEventNo, C_Happen_EventReport);

	return;
}

/*******************************************************************************
����ԭ�ͣ�void SF_Event_OpenRelay_Relay(void)
����������д��բ��¼
�����������
�����������
���ز�������
����λ�ã��ú�����SF_CombineOrderExecute_Relay˽�к�������
��    ע��
*******************************************************************************/
void SF_Event_OpenRelay_Relay(void)
{
	uchar8	V_ucDataBuff[300] = {0};
	uchar8	V_ucEventFlag;
	ushort16	V_usOffset = 0, V_usResidualLength;
	ushort16	V_usDataLength;
	ushort16	V_usDataEncode = 0;

	V_usDataLength = CLRelayOpen_Degree;
	InF_Read_Data(CRelayOpen_Degree, V_ucDataBuff, &V_usDataLength, &V_usDataEncode);	/*���¼����*/
	V_usOffset += 4;
	
	V_usDataLength = CLDate_Week_Time;
	InF_Read_Data(CDate_Time, &V_ucDataBuff[V_usOffset], &V_usDataLength, &V_usDataEncode);	/*���¼�����ʱ�䣬����ʱ��Ϊ00000000000000*/
	V_usOffset += 7;
	V_usOffset += 7;
	V_usOffset += 1;	/*����Դ����*/
	V_usOffset += 1;	/*�ϱ�״̬����*/
	
	V_usResidualLength = 300 - V_usOffset;	/*ʣ��buff����*/
	V_ucEventFlag = 0x01;
	if(Inf_GetRecordData(&V_ucDataBuff[V_usOffset], &V_usResidualLength, CRelayOpen_OADTab, V_ucEventFlag) != C_OK)	/*��ȡ����OAD����*/
	{
		return;
	}
	V_usOffset += V_usResidualLength;	/*�����ܳ���*/
	
	InF_Write_Data(C_Msg_Deal_RelayStatus, CRelayOpen_FF_1, V_ucDataBuff, V_usOffset, C_W_SafeFlag);	/*д��բ��¼*/
	Inf_EventReport_HP(C_RelayOpenEventNo, C_Happen_EventReport);
	
	return;
}

/*******************************************************************************
����ԭ�ͣ�void SF_Event_RelayCheck_Relay(void)
�������������ɿ�������
�����������
�����������
���ز�������
����λ�ã��ú�����Msg_Deal_RelayStatus��������
��    ע������ϵͳ��仯���øú���
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
	ushort16	V_usRelayOpenVol_Lim[2];	/*��Դ�쳣��ѹ����, ����*/
	ushort16	V_usVoltageHEX_ABC[3];	/*ABC�����ѹ*/
	ushort16	V_usDataCRC;
	ushort16	V_usOffset = 0, V_usResidualLength, V_usHPTime_Len;
	ushort16	V_usDataLength;
	ushort16	V_usDataEncode = 0;
    uchar8  V_ucTemp[2] = {9, 1};
	Str_Read_T V_Str_ReadRecord;

	
	V_usDataLength = CLRelay_Type;
	InF_Read_Data(CRelay_Type, &V_ucRelayType, &V_usDataLength, &V_usDataEncode);	/*��ȡ���ɿ�������*/
	
	V_usDataLength = CLRelay_State;
	InF_Read_Data(CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, &V_usDataLength, &V_usDataEncode);	/*��ȡ�̵���״̬*/
	
	V_ucReadOAD_Hp[0] = CRelayFa_Note_1;
	V_ucReadOAD_Hp[1] = CEventHPTime;
	V_ucReadOAD_Hp[2] = 0xFFFFFFFF;
	V_ucReadOAD_End[0] = CRelayFa_Note_1;
	V_ucReadOAD_End[1] = CEventEndTime;
	V_ucReadOAD_End[2] = 0xFFFFFFFF;
	
	V_usHPTime_Len = CLEventHPTime;
	V_Str_ReadRecord.pV_ulROAD = &V_ucReadOAD_Hp[0];
	V_Str_ReadRecord.pV_ucRST = &V_ucTemp[0];       /*����9*//*��ȡ��1��*/
	V_Str_ReadRecord.V_usROAD_Num = 1;              /*��������1��*/
	V_Str_ReadRecord.V_ucReadMode = C_OtherMode;    /*ģ���ڲ���ȡ*/
	V_Str_ReadRecord.V_ucChannelNo = 0xFF;          /*��ͨ�Ŷ�ȡ*/
	InF_GetData_Record(&V_Str_ReadRecord, &V_ucStartTime[0], &V_usHPTime_Len, C_NULL);      /*��ȡ��1�θ��ɿ�����������ʱ��*/

	V_usHPTime_Len = CLEventEndTime;
    V_Str_ReadRecord.pV_ulROAD = &V_ucReadOAD_End[0];
	InF_GetData_Record(&V_Str_ReadRecord, &V_ucEndTime[0], &V_usHPTime_Len, C_NULL);        /*��ȡ��1�θ��ɿ�����������ʱ��*/

	
	if( (PF_Campare_Data(V_ucStartTime, V_ucDataBuff, CLEventHPTime) != C_Equal) && (PF_Campare_Data(V_ucEndTime, V_ucDataBuff, CLEventEndTime) == C_Equal) )
	{
		V_ucEventStatus = C_EventOnlyStart;	/*��ǰΪ�з����޽���*/
	}
	else
	{
		V_ucEventStatus = C_EventNotOnlyStart;	/*��ǰ�����з����޽���*/
	}
		
	V_usDataLength = CLVolage_Abnor_Vol;
	InF_Read_Data(CVolage_Abnor_Vol, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*��Դ�쳣��ѹ����, ����*/
	PF_Buffer2ToUshort16(&V_ucDataBuff[0], &V_usRelayOpenVol_Lim[0]);	/*��Դ�쳣��ѹ����*/
	PF_Buffer2ToUshort16(&V_ucDataBuff[2], &V_usRelayOpenVol_Lim[1]);	/*��Դ�쳣��ѹ����*/
	
	V_usDataLength = CLPhaseFF_Volage;
	InF_Read_Data(CPhaseFF_Volage, &V_ucPhaseFF_Volage[0], &V_usDataLength, &V_usDataEncode);	/*ABC��ѹ*/
	PF_Buffer2ToUshort16(&V_ucPhaseFF_Volage[0], &V_usVoltageHEX_ABC[0]);
	PF_Buffer2ToUshort16(&V_ucPhaseFF_Volage[2], &V_usVoltageHEX_ABC[1]);
	PF_Buffer2ToUshort16(&V_ucPhaseFF_Volage[4], &V_usVoltageHEX_ABC[2]);
	
	if( ( (V_usVoltageHEX_ABC[0] >= V_usRelayOpenVol_Lim[0]) && (V_usVoltageHEX_ABC[0] <= V_usRelayOpenVol_Lim[1]) )	/*A���ѹ���ڵ�Դ�쳣��ѹ���޺�����֮��*/
		|| ( (V_usVoltageHEX_ABC[1] >= V_usRelayOpenVol_Lim[0]) && (V_usVoltageHEX_ABC[1] <= V_usRelayOpenVol_Lim[1]) )	/*B���ѹ���ڵ�Դ�쳣��ѹ���޺�����֮��*/
		|| ( (V_usVoltageHEX_ABC[2] >= V_usRelayOpenVol_Lim[0]) && (V_usVoltageHEX_ABC[2] <= V_usRelayOpenVol_Lim[1]) ) )	/*C���ѹ���ڵ�Դ�쳣��ѹ���޺�����֮��*/
	{
		SV_Error_Time++;
		if(Relay_Stutas.RelaytheoreticStatus == Relay_Stutas.RelayRealStatus)	
		{
			if(V_ucEventStatus != C_EventOnlyStart)
			{
				SV_Error_Time = 0x00;
				
				V_usDataLength = CLMeter_Work_State1;
				InF_Read_Data(CMeter_Work_State1, &V_ucDataBuff1[0], &V_usDataLength, &V_usDataEncode);	/*��ȡ�������״̬��1*/
				if( (V_ucDataBuff1[1]&C_ControlLoopError) == C_ControlLoopError)
				{
					V_ucDataBuff1[1] &= C_ControlLoopNoError;	/*�޿��ƻ�·��*/
					InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State1, &V_ucDataBuff1[0], CLMeter_Work_State1, C_W_SafeFlag);	/*�������״̬��1д���ݲ�*/
				}
			}	
			if(SV_Error_Time > C_Error_Time)
			{
				SV_Error_Time = 0x00;
				
				V_usDataLength = CLMeter_Work_State1;
				InF_Read_Data(CMeter_Work_State1, &V_ucDataBuff1[0], &V_usDataLength, &V_usDataEncode);	/*��ȡ�������״̬��1*/
				V_ucDataBuff1[1] &= C_ControlLoopNoError;	/*�޿��ƻ�·��*/
				InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State1, &V_ucDataBuff1[0], CLMeter_Work_State1, C_W_SafeFlag);	/*�������״̬��1д���ݲ�*/
				
				V_usDataLength = CLRelayFa_Degree;
				InF_Read_Data(CRelayFa_Degree, &V_ucDataBuff2[0], &V_usDataLength, &V_usDataEncode);	/*��ȡ��������*/
				V_usOffset += 4;
				PF_CopyDataBytes(V_ucStartTime, &V_ucDataBuff2[V_usOffset], CLEventHPTime);	/*����ʱ��*/
				V_usOffset += 7;
				V_usDataLength = CLEventEndTime;
				InF_Read_Data(CDate_Time, &V_ucDataBuff2[V_usOffset], &V_usDataLength, &V_usDataEncode);	/*��ȡ��ǰʱ�䣬���¼�����ʱ��*/
				V_usOffset += 7;
				V_usOffset += 1;
				V_usOffset += 1;	/*�ϱ�״̬����*/
				V_usResidualLength = 300 - V_usOffset;	/*ʣ��buff����*/
				V_ucEventFlag = 0x02;
				
				if(Inf_GetRecordData(&V_ucDataBuff2[V_usOffset], &V_usResidualLength, CRelayFa_OADTab, V_ucEventFlag) != C_OK)	/*��ȡ����OAD����*/
				{
					return;
				}
				V_usOffset += V_usResidualLength;	/*�����ܳ���*/
				InF_Write_Data(C_Msg_Deal_RelayStatus, CRelayFa_Note_1 + 0x00000001, V_ucDataBuff2, V_usOffset, C_W_SafeFlag);	/*�¼�����д����*/

				Inf_EventReport_HP(C_RelayFaEndEnEventNo, C_End_EventReport);
			}
		}
		else
		{
			if(V_ucEventStatus == C_EventOnlyStart)	/*��ǰ�����Ѿ�����ʱ����ʱ������*/
			{
				SV_Error_Time = 0x00;	
			}
			
			if(SV_Error_Time > C_Error_Time)
			{
				SV_Error_Time = 0x00;
						
				V_usDataLength = CLMeter_Work_State1;
				InF_Read_Data(CMeter_Work_State1, &V_ucDataBuff1[0], &V_usDataLength, &V_usDataEncode);	/*��ȡ�������״̬��1*/
				V_ucDataBuff1[1] |= C_ControlLoopError;	/*���ƻ�·��*/
				InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State1, &V_ucDataBuff1[0], CLMeter_Work_State1, C_W_SafeFlag);	/*�������״̬��1д���ݲ�*/
			
				if( ( (V_ucRelayType & C_Relay_Type) == 1) && (Relay_Stutas.RelaytheoreticStatus == C_RelayOn) )	/*���ñ���բ״̬ʱ���Ǹ��ɿ�������*/
				{
					SV_Error_Time = 0x00;
					return;	
				}	
				
				if(Relay_Stutas.RelayRealStatus == C_RelayOff)
				{
					if( (PF_Check_CRC(SV_EventOut_Err_Relay, 3) == C_OK) && (SV_EventOut_Err_Relay[0] == C_EventOutCloseErr_Relay) )	
					{
						V_usDataLength = CLRelayFa_Degree;
						InF_Read_Data(CRelayFa_Degree, &V_ucDataBuff2[0], &V_usDataLength, &V_usDataEncode);	/*��ȡ��������*/
						V_usOffset += 4;
						V_usDataLength = CLEventHPTime;
						InF_Read_Data(CDate_Time, &V_ucDataBuff2[V_usOffset], &V_usDataLength, &V_usDataEncode);	/*��ȡ��ǰʱ�䣬���¼�����ʱ�䣬�¼�����ʱ��Ϊ0000000*/
						V_usOffset += 7;
						V_usOffset += 7;
						V_usOffset += 1;	/*����Դ����*/
						V_usOffset += 1;	/*�ϱ�״̬����*/
						V_usResidualLength = 300 - V_usOffset;	/*ʣ��buff����*/
						V_ucEventFlag = 0x01;
						
						if(Inf_GetRecordData(&V_ucDataBuff2[V_usOffset], &V_usResidualLength, CRelayFa_OADTab, V_ucEventFlag) != C_OK)	/*��ȡ����OAD����*/
						{
							return;
						}

						V_usOffset += V_usResidualLength;	/*�����ܳ���*/
						InF_Write_Data(C_Msg_Deal_RelayStatus, CRelayFa_Note_1, V_ucDataBuff2, V_usOffset, C_W_SafeFlag);	/*�¼�����д����*/

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
						InF_Read_Data(CRelayFa_Degree, &V_ucDataBuff2[0], &V_usDataLength, &V_usDataEncode);	/*��ȡ��������*/
						V_usOffset += 4;
						V_usDataLength = CLEventHPTime;
						InF_Read_Data(CDate_Time, &V_ucDataBuff2[V_usOffset], &V_usDataLength, &V_usDataEncode);	/*��ȡ��ǰʱ�䣬���¼�����ʱ�䣬�¼�����ʱ��Ϊ0000000*/
						V_usOffset += 7;
						V_usOffset += 7;
						V_usOffset += 1;	/*����Դ����*/
						V_usOffset += 1;	/*�ϱ�״̬����*/
						V_usResidualLength = 300 - V_usOffset;	/*ʣ��buff����*/
						V_ucEventFlag = 0x01;
						
						if(Inf_GetRecordData(&V_ucDataBuff2[V_usOffset], &V_usResidualLength, CRelayFa_OADTab, V_ucEventFlag) != C_OK)	/*��ȡ����OAD����*/
						{
							return;
						}
						V_usOffset += V_usResidualLength;	/*�����ܳ���*/
						InF_Write_Data(C_Msg_Deal_RelayStatus, CRelayFa_Note_1, V_ucDataBuff2, V_usOffset, C_W_SafeFlag);	/*�¼�����д����*/
						
						Inf_EventReport_HP(C_RelayFaEndEnEventNo, C_Happen_EventReport);

#if 0						
						InF_ActiveReportSetting(C_Times_ContralLoopErr);	/*�����ϱ�*/
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
����ԭ�ͣ�uchar8 SF_GetRelay0nOffStatus(void)
������������ȡ���ü̵���״̬
�����������
�����������
���ز�������
����λ�ã��ú�����SF_TimeTask_Relay��������
��    ע��SF_TimeTask_Relayÿ500ms����һ�Σ������κι���ģ�鲻�������
*******************************************************************************/
void SF_GetRelay0nOffStatus(void)
{
	uchar8	V_ucExternalRelayStatus = C_Invalid;
	uchar8	V_ucRelayType;
	ushort16	V_usDataLength;
	ushort16	V_usDataEncode = 0;
		
	V_usDataLength = CLRelay_Type;
	InF_Read_Data(CRelay_Type, &V_ucRelayType, &V_usDataLength, &V_usDataEncode);	/*��ȡ���ɿ�������*/

	if( (V_ucRelayType & C_Relay_Type ) == 1)	/*�������ñ�*/	/*wxy����������*/
	{
		if( (V_ucRelayType & C_RelayFbackLine_Type ) != 0)	/*220��380V���ñ��м̵���������*/
		{
			V_ucExternalRelayStatus = InF_GetPeripheralStatus(C_ExternalRelayStatus); 
		}
	}
	SV_ExternalRelayStatus = V_ucExternalRelayStatus;	/*�������õĲ���*/
}

/*******************************************************************************
����ԭ�ͣ�void SF_RelayStatusCheck_Relay(void)
�����������̵���ʵ��״̬�ж�
�����������
�����������
���ز�������
����λ�ã��ú�����SF_TimeTask_Relay��������
��    ע��SF_TimeTask_Relayÿ500ms����һ�Σ������κι���ģ�鲻�������
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
	InF_Read_Data(CRelay_Type, &V_ucRelayType, &V_usDataLength, &V_usDataEncode);	/*��ȡ���ɿ�������*/

	V_usDataLength = CLInstantFF_AcPow;
	InF_Read_Data(CInstantFF_AcPow, V_ucInstantFF_AcPow, &V_usDataLength, &V_usDataEncode);	/*��ȡ˲ʱ�й��������ݿ�*/
	PF_BufferXToUlong32(&V_ucInstantFF_AcPow[4], (ulong32 *)&V_lInstantABCHEX_AcPow[0], CLInstantA_AcPow);
	PF_BufferXToUlong32(&V_ucInstantFF_AcPow[8], (ulong32 *)&V_lInstantABCHEX_AcPow[1], CLInstantB_AcPow);
	PF_BufferXToUlong32(&V_ucInstantFF_AcPow[12], (ulong32 *)&V_lInstantABCHEX_AcPow[2], CLInstantC_AcPow);

	V_usDataLength = CLStart_Up_Power;
	InF_Read_Data(CStart_Up_Power, V_ucData, &V_usDataLength, &V_usDataEncode);	/*��ȡ�������㷧ֵ 20150831 lzy*/
	PF_BufferXToUlong32(&V_ucData[0], (ulong32 *)&V_lStartUpPower, CLStart_Up_Power);
	V_lStartUpPower = SF_ABS(V_lStartUpPower / 3);

	V_usDataLength = CLRelay_State;
	InF_Read_Data(CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, &V_usDataLength, &V_usDataEncode);	/*��ȡ�̵���״̬*/
	
	V_usDataLength = CLMeter_Work_State3;
	InF_Read_Data(CMeter_Work_State3, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*��ȡ�������״̬��3*/

	if( (V_ucRelayType & C_Relay_Type) == 1)
	{
		if( (Relay_Stutas.RelaytheoreticStatus == C_RelayOn)
			&& (Relay_Stutas.RelayRealStatus == C_RelayOn ) )
		{
			V_ucDataBuff[0] &= C_RelayStatusOn;	/*�̵�����ͨ*/
		}
		else
		{
			if( (V_ucRelayType & C_RelayFbackLine_Type ) != 0)	/*220��380V���ñ��м̵���������*/
			{
				if( (SF_ABS(V_lInstantABCHEX_AcPow[0]) > V_lStartUpPower)
					|| (SF_ABS(V_lInstantABCHEX_AcPow[1]) > V_lStartUpPower)
					|| (SF_ABS(V_lInstantABCHEX_AcPow[2]) > V_lStartUpPower)
					|| (SV_ExternalRelayStatus == C_Valid ) )
				{
					SV_RelayCheckStatus &= C_RelayRealOn;	/*��ͨ*/
				}
				else
				{
					SV_RelayCheckStatus |= C_RelayRealOff;		/*�Ͽ�*/
				}
			}
			else
			{
				if( (SF_ABS(V_lInstantABCHEX_AcPow[0]) > V_lStartUpPower)
					|| (SF_ABS(V_lInstantABCHEX_AcPow[1]) > V_lStartUpPower)
					|| (SF_ABS(V_lInstantABCHEX_AcPow[2]) > V_lStartUpPower) )
				{
					SV_RelayCheckStatus &= C_RelayRealOn;	/*��ͨ*/
				}
				else
				{
					SV_RelayCheckStatus |= C_RelayRealOff;		/*�Ͽ�*/
				}
			}
		
			if( (SV_RelayCheckStatus & 0x01 ) == 0x01)
			{
				V_ucDataBuff[0] |= C_RelayStatusOff;	/*�̵����Ͽ�*/
			}
			else if( (SV_RelayCheckStatus & 0x01 ) == 0x00)
			{
				V_ucDataBuff[0] &= C_RelayStatusOn;	/*�̵�����ͨ*/
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
			SV_RelayCheckStatus &= C_RelayRealOn;	/*��ͨ*/
		}
		else
		{
			SV_RelayCheckStatus |= C_RelayRealOff;	/*�Ͽ�*/
		}
		if( (SV_RelayCheckStatus & 0x01) == 0x01)
		{
			V_ucDataBuff[0] |= C_RelayStatusOff;	/*�̵����Ͽ�*/
		}
		else if( (SV_RelayCheckStatus & 0x01 ) == 0x00)
		{	
			V_ucDataBuff[0] &= C_RelayStatusOn;	/*�̵�����ͨ*/
		}	
	}
	
	if( ( V_ucDataBuff[0] & C_RelayStatusOff ) == C_RelayStatusOff )
	{
		if(Relay_Stutas.RelayRealStatus != C_RelayOff)
		{
			Relay_Stutas.RelayRealStatus = C_RelayOff;	/*�ü̵���ʵ��״̬�Ͽ�*/
			InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, CLRelay_State, C_W_SafeFlag);	/*�̵���״̬д���ݲ�*/
		}
		if(Relay_Stutas.RelaytheoreticStatus == C_RelayOff)
		{
			if( (PF_Check_CRC(SV_EventOut_Open_Relay, 3) == C_OK ) && ( SV_EventOut_Open_Relay[0] == C_EventOut_Relay) )
			{
				/*��բ�ɹ������ϱ�*/
				InF_ActiveReportSetting(C_Times_OpenRelay);
				Inf_WriteMeterStatus8(C_RelayOpenEventNo);
				
				SV_EventOut_Open_Relay[0] = C_EventOutNot_Relay;	/*��ʾ����Ҫ�ϱ���բ�ɹ��¼�*/
				V_usDataCRC = PF_Cal_CRC(SV_EventOut_Open_Relay, 1);
				PF_Ushort16ToBuffer2(&SV_EventOut_Open_Relay[1], &V_usDataCRC); 
			}
		}
		
		if( ( (SV_RelayDisplayStatus & C_RelayStatusLEDTwinkle) != C_RelayStatusLEDTwinkle)
			 && ( (SV_RelayDisplayStatus & C_RelayStatusLEDOn) != C_RelayStatusLEDOn) )
		{
			SF_RelayStatusLEDMsgSend_Relay(C_DisplayOn);	/*��բָʾ�Ƶ���*/
		}	
	}
	else if( (V_ucDataBuff[0] & C_RelayStatusOff) != C_RelayStatusOff)
	{
		if(Relay_Stutas.RelayRealStatus != C_RelayOn)
		{
			Relay_Stutas.RelayRealStatus = C_RelayOn;	/*�ü̵���ʵ��״̬��ͨ*/
			InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, CLRelay_State, C_W_SafeFlag);	/*�̵���״̬д���ݲ�*/
		}
		if(Relay_Stutas.RelaytheoreticStatus == C_RelayOn)
		{
			if( (PF_Check_CRC(SV_EventOut_Close_Relay, 3) == C_OK) && (SV_EventOut_Close_Relay[0] == C_EventOut_Relay) )
			{
				SV_EventOut_Close_Relay[0] = C_EventOutNot_Relay;	/*��ʾ����Ҫ�ϱ���բ�ɹ��¼�*/
				V_usDataCRC = PF_Cal_CRC(SV_EventOut_Close_Relay, 1);
				PF_Ushort16ToBuffer2(&SV_EventOut_Close_Relay[1], &V_usDataCRC);	
			
				/*��բ�ɹ������ϱ�*/
				InF_ActiveReportSetting(C_Times_CloseRelay);
				Inf_WriteMeterStatus8(C_RelayCloseEventNo);	
			}
		}

		if( (SV_RelayDisplayStatus & C_RelayStatusLEDTwinkle) != C_RelayStatusLEDTwinkle)
		{
			if( (SV_RelayDisplayStatus & C_RelayStatusLEDOn) == C_RelayStatusLEDOn)
			{
				SF_RelayStatusLEDMsgSend_Relay(C_DisplayOff);	/*��բָʾ��Ϩ��*/
			}
		}
	}
	
	InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State3, &V_ucDataBuff[0], CLMeter_Work_State3, C_W_SafeFlag);	/*�������״̬��3д���ݲ�*/

	return;
}

#if 0
/******************************************************************************************
Function��	void Get_ExternalRelayFeedbackSignal(void)                            	                		   	
Description��    ���ü̵��������źż��                                                				
Input��                                                                                                                                                                              
Output��																						 			
Calls��                                                                                 
Called By��                                                                             
Author:                                                                          
******************************************************************************************/
void Get_ExternalRelayFeedbackSignal(void)
{
	uchar8 V_ucSignalValid, V_ucDataBuff[2], V_ucRelayType;
	uchar8 V_ucEventNo;
	ushort16	V_usDataLength;
	ushort16	V_usDataEncode = 0;
	
	V_usDataLength = CLMeter_Work_State3;
	if(InF_Read_Data(CMeter_Work_State3, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode) != C_OK)	/*��ȡ�������״̬��3*/
	{
		return;
	}

	V_usDataLength = CLRelay_Type;
	if(InF_Read_Data(CRelay_Type, &V_ucRelayType, &V_usDataLength, &V_usDataEncode) != C_OK)	/*��ȡ���ɿ�������*/
	{
		return;
	}

	if( ( (V_ucRelayType & C_Relay_Type) == 1)	/*���ñ�*/	/*wxy����*/
	 && ( (V_ucRelayType & C_RelayFbackLine_Type) != 0) )	/*�м̵���������*/
	{
		V_ucSignalValid = SV_ExternalRelayStatus;	/*���ü̵�����ʵ��״̬*/
		
		if( ( (V_ucSignalValid == C_Valid) 
			 && ( (V_ucDataBuff[0] & C_RelayStatusOff_External) == C_ExternalRelayFeedbackClose) )	/*0��ͨ*/
			 || ( (V_ucSignalValid == C_Invalid) 
			 && ( (V_ucDataBuff[0] & C_RelayStatusOff_External) == C_ExternalRelayFeedbackOpen) ) )	/*1����*/
		{
			SV_ucExternalRelayStatusTime = 0;			
		}
		else
		{
			if(SV_ucExternalRelayStatusTime < C_ExternalRelayStatusTime)	/*5s���ʱ�䵽��д�����ϱ�״̬�֣����и����ϱ�*/
			{
				SV_ucExternalRelayStatusTime++;
			}
			else
			{
				if(V_ucSignalValid == C_Valid)
				{
					V_ucDataBuff[0] &= C_RelayStatusOn_External;	/*0��ͨ*/
					V_ucEventNo = C_ExternalRelayCloseEventNo;
				}
				else
				{
					V_ucDataBuff[0] |= C_RelayStatusOff_External;	/*1����*/
					V_ucEventNo = C_ExternalRelayOpenEventNo;
				}
				
				/*�������״̬��3д���ݲ�*/
				InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State3, &V_ucDataBuff[0], CLMeter_Work_State3, C_W_SafeFlag);
				/*д�����ϱ�״̬��*/
				Inf_WriteMeterStatus8(V_ucEventNo);			
			}			
		}
	}
}
#endif

/*******************************************************************************
����ԭ�ͣ�void SF_DealWithSV_Relay(void)
�����������̵���ģ���ڲ���̬��������
�����������
�����������
���ز�������
����λ�ã�
��    ע��
*******************************************************************************/
void SF_DealWithSV_Relay(void)
{
	SV_OpenRealyDelay_Time = 0x00;	/*��բ��ʱʱ��*/
	SV_L_CloseRealyDelay_Time = 0x00;	/*���ر���һ����բ�������բ��ʱʱ��*/
	SV_Comm_CloseRealyDelay_Time = 0x00;	/*ͨ����բ�Զ��ָ�����ʱ��*/
	SV_24HourDelayTimer = 0x00;	/*�����������޵�����ʱ*/
	SV_RelayRework_Timer = 0x00;	/*�ظ�������ʱ��*/
	SV_RelayOpenAfterPowerUp = 0x00;	/*�ϵ�ʱ������բ״̬Ҫ����բ���ϵ���0x68���ù�������*/

	if( (SV_RelayDisplayStatus&C_RelayStatusLEDTwinkle) == C_RelayStatusLEDTwinkle)
	{
		SF_RelayStatusLEDMsgSend_Relay(C_DisplayOff);	/*��բָʾ��Ϩ��*/
	}
	SV_ClearFlag = 0x00;	/*��������ʶ*/

	return;
}

/*******************************************************************************
����ԭ�ͣ�void SF_Cardor3sCloseRelayTask_Relay(void)
�����������忨�򰴼�3s��բ����
�����������
�����������
���ز�������
����λ�ã��ú�����Msg_Deal_RelayStatus��������
��    ע��
*******************************************************************************/
void SF_Cardor3sCloseRelayTask_Relay(void)
{
	ushort16	V_usDataLength;
	ushort16	V_usDataEncode = 0;
	
	SF_Combine_R_L_Order_Relay();	/*Զ�̱��ؿ����������*/
	if(Combine_RelayOrder.RelayOrderStatus == C_Close_conditonal)	/*�������Ϊ������բ*/
	{
		SF_DealWithSV_Relay();	/*�ڲ���̬��������*/
		
		V_usDataLength = CLRelay_RemoteOrder;
		InF_Read_Data(CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, &V_usDataLength, &V_usDataEncode);	/*��ȡԶ�̿�������*/
	
		V_usDataLength = CLRelay_LocalOrder;
		InF_Read_Data(CRelay_LocalOrder, &Local_RelayOrder.PreWarning, &V_usDataLength, &V_usDataEncode);	/*��ȡ���ؿ�������*/
		
		SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*��բ�ַ�Ϩ��*/
			
		if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
		{
			SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*����ر�*/
		}

		Com_RelayOrder.RelayOrderStatus = C_Close_Direct;
		Local_RelayOrder.RelayOrderStatus = C_Close_Direct;	
		SV_LocalOrderNum = 0x00;	/*�������������Ϊ0*/
		SV_ComOrderNum = 0x00;	/*Զ�����������*/
		
		InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, CLRelay_RemoteOrder, C_W_SafeFlag);	/*Զ�̿�������д���ݲ�*/
		InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_LocalOrder, &Local_RelayOrder.PreWarning, CLRelay_LocalOrder, C_W_SafeFlag);	/*���ؿ�������д���ݲ�*/
	}
}

/*******************************************************************************
����ԭ�ͣ�void SF_TimeTask_Relay(void)
��������������500ms����������
�����������
�����������
���ز�������
����λ�ã��ú�����Msg_Deal_RelayStatus��������
��    ע������ÿ500ms���øú���
*******************************************************************************/
void SF_TimeTask_Relay(void)
{
	uchar8	V_ucDataBuff[10];
	uchar8	V_ucRelayType;
	ushort16	V_usDataLength;
	ushort16	V_usDataEncode = 0;
	
	V_usDataLength = CLRelay_RemoteOrder;
	InF_Read_Data(CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, &V_usDataLength, &V_usDataEncode);	/*��ȡԶ�̿�������*/

	V_usDataLength = CLRelay_LocalOrder;
	InF_Read_Data(CRelay_LocalOrder, &Local_RelayOrder.PreWarning, &V_usDataLength, &V_usDataEncode);	/*��ȡ���ؿ�������*/

	V_usDataLength = CLRelay_State;
	InF_Read_Data(CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, &V_usDataLength, &V_usDataEncode);	/*��ȡ�̵���״̬*/

	SF_GetRelay0nOffStatus();	/*���������ü̵�����ʵ��״̬��ȡ*/
	SF_RelayStatusCheck_Relay();	/*�̵���ʵ��״̬���*/
	if( (Local_RelayOrder.RelayOrderStatus == C_Pre_Open) && (SV_L_CloseRealyDelay_Time > 1)
		&& (Relay_Stutas.RelaytheoreticStatus == C_RelayOff) )
	{
		SV_L_CloseRealyDelay_Time--;	/*������բ��ʱʱ���1*/
		if(SV_L_CloseRealyDelay_Time == 1)
		{
			Local_RelayOrder.RelayOrderStatus = C_Close_Allow;	/*���������������բ*/
			InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_LocalOrder, &Local_RelayOrder.PreWarning, CLRelay_LocalOrder, C_W_SafeFlag);	/*���ؿ�������д���ݲ�*/
			SV_LocalOrderNum = SF_GetNewOrderNum();	/*���±����������*/
		}
	}
	if(SV_RelayRework_Timer != 0)
	{
		SV_RelayRework_Timer--;	/*�ظ�������ʱʱ���1*/
	}
	if(SV_24HourDelayTimer > 1)
	{
		SV_24HourDelayTimer--;	/*�������ʱʱ���1*/
	}
	if( (Com_RelayOrder.RelayOrderStatus == C_Open) && (SV_OpenRealyDelay_Time > 1) )
	{
		SV_OpenRealyDelay_Time--;	/*��բ��ʱʱ���1*/
	}
	else if( (Com_RelayOrder.RelayOrderStatus == C_Open_Direct) && (SV_Comm_CloseRealyDelay_Time != 0)
			&& (Relay_Stutas.RelaytheoreticStatus == C_RelayOff) )
	{
		SV_Comm_CloseRealyDelay_Time--;	/*1D��բ�Զ��ָ���ʱʱ���1*/
		if(SV_Comm_CloseRealyDelay_Time == 0)
		{
			SV_L_CloseRealyDelay_Time = 0x00;	/*��������Ԥ��բ״̬*/
			Com_RelayOrder.RelayOrderStatus = C_Close_Direct;
			InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, CLRelay_RemoteOrder, C_W_SafeFlag);	/*Զ�̿�������д���ݲ�*/
			SV_ComOrderNum = SF_GetNewOrderNum();	/*����Զ���������*/
			
			if(Local_RelayOrder.RelayOrderStatus != C_Open)
			{
				SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*��բ�ַ�Ϩ��*/
			}			
			
			if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
			{
				SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*����ر�*/
			}
				
			V_usDataLength = CLMeter_Work_State3;
			InF_Read_Data(CMeter_Work_State3, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*��ȡ�������״̬��3*/
			V_ucDataBuff[0] &= C_RelayOrderStatusOn;	/*�̵������ͨ*/
			InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State3, &V_ucDataBuff[0], CLMeter_Work_State3, C_W_SafeFlag);	/*�������״̬��3д���ݲ�*/
		}	
	}
	else if( (Com_RelayOrder.RelayOrderStatus == C_Open_Allow) && (SV_Comm_CloseRealyDelay_Time != 0)
			&& (Relay_Stutas.RelaytheoreticStatus == C_RelayOff) )
	{
		SV_Comm_CloseRealyDelay_Time--;	/*1E��բ�Զ��ָ���ʱʱ���1*/
		if(SV_Comm_CloseRealyDelay_Time == 0)
		{
			SV_L_CloseRealyDelay_Time = 0x00;	/*��������Ԥ��բ״̬*/
			V_usDataLength = CLRelay_Type;
			InF_Read_Data(CRelay_Type, &V_ucRelayType, &V_usDataLength, &V_usDataEncode);	/*��ȡ���ɿ�������*/
			if( (V_ucRelayType & C_Relay_Type) == 1)
			{
				Com_RelayOrder.RelayOrderStatus = C_Close_Direct;	/*Զ�̿���������ֱ�Ӻ�բ*/
				InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, CLRelay_RemoteOrder, C_W_SafeFlag);	/*Զ�̿�������д���ݲ�*/
				
				if(Local_RelayOrder.RelayOrderStatus != C_Open)
				{
					SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*��բ�ַ�Ϩ��*/
				}
				
				if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
				{
					SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*����ر�*/
				}
			}
			else
			{
				Com_RelayOrder.RelayOrderStatus = C_Close_Allow;
				InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, CLRelay_RemoteOrder, C_W_SafeFlag);	/*Զ�̿�������д���ݲ�*/
				SV_ComOrderNum = SF_GetNewOrderNum();	/*����Զ���������*/
				
				if(Local_RelayOrder.RelayOrderStatus != C_Open)
				{
					SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*��բ�ַ�Ϩ��*/
					
					if(Relay_Stutas.RelaytheoreticStatus == C_RelayOff)
					{
						SF_RelayStatusLEDMsgSend_Relay(C_DisplayTwinkle);	/*��բָʾ����˸*/
					}
				}
				
				if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
				{
					SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*����ر�*/
				}	
			}	
			
			V_usDataLength = CLMeter_Work_State3;
			InF_Read_Data(CMeter_Work_State3, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*��ȡ�������״̬��3*/
			V_ucDataBuff[0] &= C_RelayOrderStatusOn;	/*�̵������ͨ*/
			InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State3, &V_ucDataBuff[0], CLMeter_Work_State3, C_W_SafeFlag);	/*�������״̬��3д���ݲ�*/
		}
	}
	
	SF_Combine_R_L_Order_Relay();	/*Զ�̱��ؿ����������*/
	SF_CombineOrderExecute_Relay();	/*��Ͽ�������ִ��*/
#if 0    
	Get_ExternalRelayFeedbackSignal();	/*���ü̵��������źż��*/
#endif

	return;	
}

/*******************************************************************************
����ԭ�ͣ�void SF_Combine_R_L_Order_Relay(void)
����������Զ�̱��ؿ����������
�����������
�����������
���ز�������
����λ�ã��ú�����SF_TimeTask_Relay������SF_Cardor3sCloseRelayTask_Relay��������
��    ע������Զ�̿�������ͱ��ؿ������������Ͽ�������״̬
*******************************************************************************/
void SF_Combine_R_L_Order_Relay(void)
{
	uchar8	V_ucRelayType;
	ushort16	V_usDataLength;
	ushort16	V_usDataEncode = 0;
	
	V_usDataLength = CLRelay_RemoteOrder;
	InF_Read_Data(CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, &V_usDataLength, &V_usDataEncode);	/*��ȡԶ�̿�������*/

	V_usDataLength = CLRelay_LocalOrder;
	InF_Read_Data(CRelay_LocalOrder, &Local_RelayOrder.PreWarning, &V_usDataLength, &V_usDataEncode);	/*��ȡ���ؿ�������*/
	
	Combine_RelayOrder.RelayOrderStatus = C_OrderNull;	/*��ϼ̵�������״̬����Ϊ��*/

	/*�����������*/
	if( (Com_RelayOrder.PreWarning == C_PreWarning) || (Local_RelayOrder.PreWarning == C_PreWarning) )
	{
		Combine_RelayOrder.PreWarning = C_PreWarning;	
	}
	else
	{
		Combine_RelayOrder.PreWarning = C_PreWarning_Release;	
	}
	
	/*�̵����������*/
	if(Com_RelayOrder.Protect_Current == C_Protect_Current)	/*��ǰ����Զ�̱���״̬*/
	{
		V_usDataLength = CLRelay_Type;
		InF_Read_Data(CRelay_Type, &V_ucRelayType, &V_usDataLength, &V_usDataEncode);	/*��ȡ���ɿ�������*/
		
		if( (V_ucRelayType&C_Relay_Type) == 1)	
		{
			Combine_RelayOrder.RelayOrderStatus = C_Close_Direct;	/*��������ֱ�Ӻ�բ*/
		}
		else
		{
			if( (Local_RelayOrder.RelayOrderStatus == C_Close_Direct) && (Com_RelayOrder.RelayOrderStatus == C_Close_Direct) )
			{
				Combine_RelayOrder.RelayOrderStatus = C_Close_Direct;	/*��������ֱ�Ӻ�բ*/
			}
			else
			{
				Combine_RelayOrder.RelayOrderStatus = C_Close_conditonal;	/*��������������բ*/
			}					
		}
	}
	else if(Local_RelayOrder.RelayOrderStatus == C_Open)	/*��ǰ���ڱ���������բ״̬*/
	{
		Combine_RelayOrder.RelayOrderStatus = C_Open;	/*ֱ����բ*/
	}
	else if(Local_RelayOrder.RelayOrderStatus == C_Pre_Open)	/*��ǰ���ڱ���Ԥ��բ״̬*/
	{
		if(Com_RelayOrder.RelayOrderStatus == C_Open)	/*��բ*/
		{
			if( (SV_L_CloseRealyDelay_Time > 1) || (SV_OpenRealyDelay_Time == 1) )
			{
				Combine_RelayOrder.RelayOrderStatus = C_Open;	/*ֱ����բ*/
			}
		}
		else if(Com_RelayOrder.RelayOrderStatus == C_Close_Allow)	/*��բ����*/
		{
			if(SV_L_CloseRealyDelay_Time > 1)
			{
				Combine_RelayOrder.RelayOrderStatus = C_Open;	/*ֱ����բ*/
			}
			else 
			{
				Combine_RelayOrder.RelayOrderStatus = C_Close_conditonal;	/*������բ*/
			}	
		}
		else if(Com_RelayOrder.RelayOrderStatus == C_Close_Direct)	/*ֱ�Ӻ�բ*/
		{
			if(SV_L_CloseRealyDelay_Time > 1)
			{
				Combine_RelayOrder.RelayOrderStatus = C_Open;	/*ֱ����բ*/
			}
			else 
			{
				Combine_RelayOrder.RelayOrderStatus = C_Close_Direct;	/*ֱ�Ӻ�բ*/
			}			
		}
		else
		{
			if( (SV_L_CloseRealyDelay_Time > 1) || (SV_Comm_CloseRealyDelay_Time != 0) )
			{
				Combine_RelayOrder.RelayOrderStatus = C_Open;	/*ֱ����բ*/
			}
		}
	}
	else if(Local_RelayOrder.RelayOrderStatus == C_Close_Allow)	/*��ǰ���ڱ��غ�բ����״̬*/
	{
		if(Com_RelayOrder.RelayOrderStatus == C_Open_Direct)	/*��բ�Զ��ָ�����ʱʱ�䵽ֱ�Ӻ�բ��*/
		{
			if(SV_Comm_CloseRealyDelay_Time != 0)
			{
				Combine_RelayOrder.RelayOrderStatus = C_Open;	/*ֱ����բ*/
			}
			else
			{
				Combine_RelayOrder.RelayOrderStatus = C_Close_conditonal;	/*������բ*/
			}
		}
		if(Com_RelayOrder.RelayOrderStatus == C_Open_Allow)	/*��բ�Զ��ָ�����ʱʱ�䵽��բ����*/
		{
			if(SV_Comm_CloseRealyDelay_Time != 0)
			{
				Combine_RelayOrder.RelayOrderStatus = C_Open;	/*ֱ����բ*/
			}
			else
			{
				Combine_RelayOrder.RelayOrderStatus = C_Close_conditonal;	/*������բ*/
			}
		}
		if(Com_RelayOrder.RelayOrderStatus == C_Open)	/*��բ*/
		{
			if(SV_OpenRealyDelay_Time == 1)
			{
				Combine_RelayOrder.RelayOrderStatus = C_Open;	/*ֱ����բ*/
			}
		}
		if(Com_RelayOrder.RelayOrderStatus == C_Close_Allow)	/*��բ����*/
		{
			Combine_RelayOrder.RelayOrderStatus = C_Close_conditonal;	/*������բ*/
		}
		if(Com_RelayOrder.RelayOrderStatus == C_Close_Direct)	/*ֱ�Ӻ�բ*/
		{
			if(PF_Campare_Data(&SV_LocalOrderNum, &SV_ComOrderNum, 1) == C_GreaterThan)	/*�Ƚ�Զ������ͱ��ؿ���������Ŵ�С*/
			{
				Combine_RelayOrder.RelayOrderStatus = C_Close_conditonal;	/*������բ*/
			}
			else 
			{
				Combine_RelayOrder.RelayOrderStatus = C_Close_Direct;	/*ֱ�Ӻ�բ*/
			}	
		}	
	}
	else	/*if(Local_RelayOrder.RelayOrderStatus == C_Close_Direct)*/	/*��ǰ���ڱ��غ�բ״̬*/
	{
		if(Com_RelayOrder.RelayOrderStatus == C_Open_Direct)	/*��բ�Զ��ָ�����ʱʱ�䵽ֱ�Ӻ�բ��*/
		{
			if(SV_Comm_CloseRealyDelay_Time != 0)
			{
				Combine_RelayOrder.RelayOrderStatus = C_Open;	/*ֱ����բ*/
			}
			else 
			{
				Combine_RelayOrder.RelayOrderStatus = C_Close_Direct;	/*ֱ�Ӻ�բ*/
			}		
		}
		if(Com_RelayOrder.RelayOrderStatus == C_Open_Allow)	/*��բ�Զ��ָ�����ʱʱ�䵽��բ����*/
		{
			if(SV_Comm_CloseRealyDelay_Time != 0)
			{
				Combine_RelayOrder.RelayOrderStatus = C_Open;	/*ֱ����բ*/
			}
			else 
			{
				Combine_RelayOrder.RelayOrderStatus = C_Close_Direct;	/*ֱ�Ӻ�բ*/
			}		
		}
		if(Com_RelayOrder.RelayOrderStatus == C_Open)	/*��բ*/
		{
			if(SV_OpenRealyDelay_Time == 1)
			{
				Combine_RelayOrder.RelayOrderStatus = C_Open;	/*ֱ����բ*/
			}	
		}
		if(Com_RelayOrder.RelayOrderStatus == C_Close_Allow)	/*��բ����*/
		{
			if(PF_Campare_Data(&SV_LocalOrderNum, &SV_ComOrderNum, 1) == C_LessThan)	/*�Ƚ�Զ������ͱ��ؿ���������Ŵ�С*/
			{
				Combine_RelayOrder.RelayOrderStatus = C_Close_conditonal;	/*������բ*/
			}
			else 
			{
				Combine_RelayOrder.RelayOrderStatus = C_Close_Direct;	/*ֱ�Ӻ�բ*/
			}
		}
		if(Com_RelayOrder.RelayOrderStatus == C_Close_Direct)	/*ֱ�Ӻ�բ*/
		{
			Combine_RelayOrder.RelayOrderStatus = C_Close_Direct;	/*ֱ�Ӻ�բ*/
		}	
	}
}

/*******************************************************************************
����ԭ�ͣ�void SF_CombineOrderExecute_Relay(void)
������������Ͽ�������ִ��
�����������
�����������
���ز�������
����λ�ã��ú�����SF_TimeTask_Relay��������
��    ע���̵���������Ͽ�������״̬������ض���
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
	InF_Read_Data(CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, &V_usDataLength, &V_usDataEncode);	/*��ȡԶ�̿�������*/
	
	V_usDataLength = CLRelay_State;
	InF_Read_Data(CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, &V_usDataLength, &V_usDataEncode);	/*��ȡ�̵���״̬*/
	
	memset(&V_ucDataBuff_Msg[0], 0xFF, 8);
	if(Combine_RelayOrder.PreWarning == C_PreWarning)	/*�������Ϊ����*/
	{
		V_usDataLength = CLMeter_Work_State3;
		InF_Read_Data(CMeter_Work_State3, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*��ȡ�������״̬��3*/
		V_ucDataBuff[0] |= C_RelayPreWarning;	/*Ԥ��բ����*/
		InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State3, &V_ucDataBuff[0], CLMeter_Work_State3, C_W_SafeFlag);	/*�������״̬��3д���ݲ�*/
			
		V_ucDataBuff_Msg[0] = Pt_DisplayStatus;
		V_ucDataBuff_Msg[1] = (C_PurchaseSign | C_TwinkleDisplay);	/*�빺���ַ���˸*/
		V_ucDataBuff_Msg[4] = Pt_DisplayStatus;
		V_ucDataBuff_Msg[5] = (C_BackLED | C_AlwaysDisplay);	/*��������*/
		if(Relay_Stutas.RelaytheoreticWarningStatus == C_PreWarning)	/*����״̬Ϊ����*/
		{
			if(SV_AlarmAfterPowerUp == C_PreWarning)	/*������ʵ��һ�¾�Ϊ����ʱ���ϵ籨����ʶ��Ч�������������ʶ����*/
			{
				SV_AlarmAfterPowerUp = C_PreWarning_Release;	
#if 0
				V_ucDataBuff_Msg[0] = Pt_DisplayStatus;
				V_ucDataBuff_Msg[1] = (C_PurchaseSign | C_TwinkleDisplay);	/*�빺���ַ���˸*/
				V_ucDataBuff_Msg[2] = 0xFF;
				V_ucDataBuff_Msg[3] = 0xFF;
				V_ucDataBuff_Msg[4] = Pt_DisplayStatus;
				V_ucDataBuff_Msg[5] = (C_BackLED | C_AlwaysDisplay);	/*��������*/
				V_ucDataBuff_Msg[6] = 0xFF;
				V_ucDataBuff_Msg[7] = 0xFF;
#endif
				SF_MsgSend_Relay(V_ucDataBuff_Msg, (Pt_DisplayStatus_Len + 1) * 2, C_Msg_Display);	/*������ʾ��Ϣ*/
			}	
		}
		else
		{
			Relay_Stutas.RelaytheoreticWarningStatus = C_PreWarning;	/*�����۱���״̬*/
			InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, CLRelay_State, C_W_SafeFlag);	/*����״̬д���ݲ�*/
#if 0	
			V_ucDataBuff_Msg[0] = Pt_DisplayStatus;
			V_ucDataBuff_Msg[1] = (C_PurchaseSign | C_TwinkleDisplay);	/*�빺���ַ���˸*/
			V_ucDataBuff_Msg[2] = 0xFF;
			V_ucDataBuff_Msg[3] = 0xFF;
			V_ucDataBuff_Msg[4] = Pt_DisplayStatus;
			V_ucDataBuff_Msg[5] = (C_BackLED | C_AlwaysDisplay);	/*��������*/
			V_ucDataBuff_Msg[6] = 0xFF;
			V_ucDataBuff_Msg[7] = 0xFF;
#endif
			SF_MsgSend_Relay(V_ucDataBuff_Msg, (Pt_DisplayStatus_Len + 1) * 2, C_Msg_Display);	/*������ʾ��Ϣ*/
		}	
	}
	else /*if(Combine_RelayOrder.PreWarning == C_PreWarning_Release)*/	/*�������Ϊ�������*/
	{
		V_usDataLength = CLMeter_Work_State3;
		InF_Read_Data(CMeter_Work_State3, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*��ȡ�������״̬��3*/
		V_ucDataBuff[0] &= C_RelayPreWarning_Release;	/*��Ԥ��բ����*/
		InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State3, &V_ucDataBuff[0], CLMeter_Work_State3, C_W_SafeFlag);	/*�������״̬��3д���ݲ�*/
		
		if(Relay_Stutas.RelaytheoreticWarningStatus == C_PreWarning)
		{
			V_ucDataBuff_Msg[0] = Pt_DisplayStatus;
			V_ucDataBuff_Msg[1] = (C_PurchaseSign | C_NotDisplay);	/*�빺���ַ�Ϩ��*/
			
			SF_MsgSend_Relay(V_ucDataBuff_Msg, Pt_DisplayStatus_Len + 1, C_Msg_Display);	/*������ʾ��Ϣ*/
			
			if( (Com_RelayOrder.RelayOrderStatus == C_Open) && (SV_OpenRealyDelay_Time > 1) && (Relay_Stutas.RelaytheoreticStatus != C_RelayOff) )	/*��բ��ʱ�ڼ�*/
			{
				V_ucBackLEDStatus = C_BackLEDstatusOn;	
			}	
			if( (Combine_RelayOrder.RelayOrderStatus == C_Open) && (SV_24HourDelayTimer > 1) && (Relay_Stutas.RelaytheoreticStatus != C_RelayOff) )
			{
				V_ucBackLEDStatus = C_BackLEDstatusOn;		
			}
			if(V_ucBackLEDStatus != C_BackLEDstatusOn)
			{
				SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*�رձ���*/
			}
			
			Relay_Stutas.RelaytheoreticWarningStatus = C_PreWarning_Release;	/*�����۱������״̬*/
			InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, CLRelay_State, C_W_SafeFlag);	/*����״̬д���ݲ�*/
		}
	}
	if(Combine_RelayOrder.RelayOrderStatus == C_Open)	/*�������Ϊ��բ*/
	{
		if(Relay_Stutas.RelaytheoreticStatus == C_RelayOff)	/*����״̬Ϊ��բ*/
		{
			if( (SV_RelayDisplayStatus&C_RealayOpenSignOn) != C_RealayOpenSignOn)
			{
				SF_RealayOpenSignMsgSend_Relay(C_DisplayOn);	/*��բ�ַ�����*/
			}
			if(SV_RelayRework_Timer == 0)	/*�ظ�������ʱʱ�䵽���̵�������һ��*/
			{
				if( ( ( (SF_JudgeCurrent_Relay() == C_CurrentOk) && (SV_RelayOpenAfterPowerUp != C_Open) ) || (SV_RelayOpenAfterPowerUp == C_Open) )
					&& (InF_JudgeVolage_Relay() == C_VoltageOk) )	/*��ѹ����������Ҫ��*/
				{
					InF_RelayAct(C_Off);	/*��բ*/
					SV_RelayOpenAfterPowerUp = 0x00;				
					
					if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
					{
						SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*�رձ���*/
					}
				}
				SV_RelayRework_Timer = C_RelayRework_Timer;	
			}
		}
		else	/*if(Relay_Stutas.RelaytheoreticStatus == C_RelayOn)*/	/*����״̬Ϊ��բ*/
		{
			if(SV_24HourDelayTimer == 0)	/*�������ʱʱ��Ϊ0*/
			{
				if( (SF_JudgeCurrent_Relay() != C_CurrentOk) || (InF_JudgeVolage_Relay() != C_VoltageOk) )	/*��ѹ�������������բҪ������Ӧ��ʾ��Ϣ*/
				{
					if( (SV_RelayDisplayStatus&C_RealayOpenSignTwinkle) != C_RealayOpenSignTwinkle)
					{
						SF_RealayOpenSignMsgSend_Relay(C_DisplayTwinkle);	/*��բ�ַ���˸*/
					}
					if( (SV_RelayDisplayStatus&C_BackLEDOn) != C_BackLEDOn)
					{
						SF_BackLEDMsgSend_Relay(C_DisplayOn);	/*��������*/
					}
				}
				if(SF_JudgeCurrent_Relay() == C_CurrentOk)	/*����������բҪ��*/
				{
					if(InF_JudgeVolage_Relay() == C_VoltageOk)	/*��ѹ������բҪ��*/
					{
						SF_Op_OpenRelay_Relay();
					}
				}
				else
				{
					V_usDataLength = CLRelay_Open_CurrTimer;
					if(InF_Read_Data(CRelay_Open_CurrTimer, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode) != C_OK)	/*�������ʱʱ��*/
					{
						SV_24HourDelayTimer = 1;	/*�������ʱʱ���ó�ֵ*/
					}
					else
					{
						PF_BufferXToUlong32(V_ucDataBuff, &V_ulTime, V_usDataLength);
						if(V_ulTime == 0)
						{
							SV_24HourDelayTimer = 1;	/*�������ʱʱ���ó�ֵ*/
						}
						else
						{
							SV_24HourDelayTimer = V_ulTime*60*2;	/*�������ʱʱ���ó�ֵ*/
						}
					}
				}
			}
			if(SV_24HourDelayTimer > 1)	/*�������ʱʱ�����1��24Сʱ��ʱʱ��δ��*/
			{
				if(SF_JudgeCurrent_Relay() == C_CurrentOk)	/*����������բҪ��*/
				{
					if(InF_JudgeVolage_Relay() == C_VoltageOk)	/*��ѹ������բҪ��*/
					{
						SF_Op_OpenRelay_Relay();
					}
				}
			}
			if(SV_24HourDelayTimer == 1)	/*�������ʱʱ��Ϊ1, 24Сʱ��ʱʱ�䵽�������жϵ�����ֵ*/
			{
				if(InF_JudgeVolage_Relay() == C_VoltageOk)	/*��ѹ������բҪ��*/
				{
					SF_Op_OpenRelay_Relay();
				}
				else
				{
					if( (SV_RelayDisplayStatus&C_RealayOpenSignTwinkle) != C_RealayOpenSignTwinkle)	
					{
						SF_RealayOpenSignMsgSend_Relay(C_DisplayTwinkle);	/*��բ�ַ���˸*/
					}
					if( (SV_RelayDisplayStatus&C_BackLEDOn) != C_BackLEDOn)
					{
						SF_BackLEDMsgSend_Relay(C_DisplayOn);	/*��������*/
					}
				}
			}
		}
	}
	else if(Combine_RelayOrder.RelayOrderStatus == C_Close_conditonal)	/*�������Ϊ������բ*/
	{
		if(SV_RelayOpenAfterPowerUp == C_Open)
		{
			if(Relay_Stutas.RelaytheoreticStatus == C_RelayOff)	/*����״̬Ϊ��բ*/
			{
				if(InF_JudgeVolage_Relay() == C_VoltageOk)	/*��ѹ����������Ҫ��*/
				{
					InF_RelayAct(C_Off);	/*��բ*/
					SV_RelayOpenAfterPowerUp = 0x00;					
				}
			}
		}
	}
	else if(Combine_RelayOrder.RelayOrderStatus == C_OrderNull)	/*�������Ϊ�ղ�ִ�� ֱ�ӷ���*/
	{
		return;	
	}
	else	/*if(Combine_RelayOrder.RelayOrderStatus == C_Close_Direct)*/	/*�������Ϊ��բ*/
	{
		if(Relay_Stutas.RelaytheoreticStatus == C_RelayOn)	/*����״̬Ϊ��բ*/
		{
			if(SV_RelayRework_Timer == 0)	/*�ظ�������ʱʱ�䵽*/
			{
				if(InF_JudgeVolage_Relay() == C_VoltageOk)	/*��ѹ�����բҪ��*/
				{
					InF_RelayAct(C_On);	/*��բ*/
				}
				
				SV_RelayRework_Timer = C_RelayRework_Timer;	/*���ظ�������ʱʱ���ֵ*/
			}
		}
		else	/*if(Relay_Stutas.RelaytheoreticStatus == C_RelayOff)*/	/*����״̬Ϊ��բ*/
		{
			if( ( (SV_RelayDisplayStatus&C_RealayOpenSignOn) == C_RealayOpenSignOn)
				|| ( (SV_RelayDisplayStatus&C_RealayOpenSignTwinkle) == C_RealayOpenSignTwinkle) )
			{
				SF_RealayOpenSignMsgSend_Relay(C_DisplayOff);	/*��բ�ַ�Ϩ��*/
			}
			
			if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
			{
				if( (SV_RelayDisplayStatus&C_BackLEDOn) == C_BackLEDOn)
				{
					SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*�رձ���*/
				}
			}
			
			if(InF_JudgeVolage_Relay() == C_VoltageOk)	/*��ѹ�����բҪ��*/
			{
				if( (SV_RelayDisplayStatus&C_RelayStatusLEDTwinkle) == C_RelayStatusLEDTwinkle)
				{
					SF_RelayStatusLEDMsgSend_Relay(C_DisplayOff);	/*��բָʾ��Ϩ��*/
				}
				
				InF_RelayAct(C_On);	/*��բ*/
				
				SV_Error_Time = 0x00;
				Relay_Stutas.RelaytheoreticStatus = C_RelayOn;	/*������״̬Ϊ��բ*/
				InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, CLRelay_State, C_W_SafeFlag);	/*����״̬д���ݲ�*/
				
				SV_EventOut_Open_Relay[0] = C_EventOutNot_Relay;	/*��ʾ����Ҫ�ϱ���բ�ɹ��¼�*/
				V_usDataCRC = PF_Cal_CRC(SV_EventOut_Open_Relay, 1);
				PF_Ushort16ToBuffer2(&SV_EventOut_Open_Relay[1], &V_usDataCRC); 
		
				SV_EventOut_Close_Relay[0] = C_EventOut_Relay;	/*��ʾ��Ҫ�ϱ���բ�ɹ��¼�*/
				V_usDataCRC = PF_Cal_CRC(SV_EventOut_Close_Relay, 1);
				PF_Ushort16ToBuffer2(&SV_EventOut_Close_Relay[1], &V_usDataCRC);	
					
				SV_EventOut_Err_Relay[0] = C_EventOutCloseErr_Relay;	/*��ʾ��Ҫ�ϱ����ɿ��������¼�*/
				V_usDataCRC = PF_Cal_CRC(SV_EventOut_Err_Relay, 1);
				PF_Ushort16ToBuffer2(&SV_EventOut_Err_Relay[1], &V_usDataCRC);	
				
				SF_Event_CloseRelay_Relay();	/*�Ǻ�բ�¼���¼*/
				
				V_usDataLength = CLRelay_Type;
				InF_Read_Data(CRelay_Type, &V_ucRelayType, &V_usDataLength, &V_usDataEncode);	/*��ȡ���ɿ�������*/
				if( (V_ucRelayType & C_Relay_Type) == 1)
				{
					if(SV_ClearFlag == 0x68)	/*��������ʶ*/
					{
						Relay_Stutas.RelayRealStatus = C_RelayOn;	/*�ü̵���ʵ��״̬��ͨ*/
						InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, CLRelay_State, C_W_SafeFlag);	/*�̵���״̬д���ݲ�*/
						SF_RelayStatusLEDMsgSend_Relay(C_DisplayOff);	/*��բָʾ��Ϩ��*/
						SV_ClearFlag = 0x00;	/*��������ʶ*/
					}	
				}
#if 0				
				/*��բ�ɹ������ϱ�*/
				InF_ActiveReportSetting(C_Times_CloseRelay);
#endif
				SV_RelayRework_Timer = C_RelayRework_Timer;	/*���ظ�������ʱʱ���ֵ*/
			}
			else
			{
				if( (SV_RelayDisplayStatus&C_RelayStatusLEDTwinkle) != C_RelayStatusLEDTwinkle)
				{
					SF_RelayStatusLEDMsgSend_Relay(C_DisplayTwinkle);	/*��բָʾ����˸*/
				}	
			}
		}
	}
	return;
}

/*******************************************************************************
����ԭ�ͣ�uchar8 InF_JudgeVolage_Relay(void)
������������ѹֵ�ж�
�����������
�����������
���ز�����C_VoltageOk����ʾ��ǰ��ѹ��������բ��C_VoltageErr����ʾ��ǰ��ѹ����������բ
����λ�ã��ú�����SF_CombineOrderExecute_Relay��������
��    ע������բ֮ǰ���øú������ж��Ƿ���ϼ̵�������բҪ��
*******************************************************************************/
uchar8 InF_JudgeVolage_Relay(void)
{
	uchar8	V_ucVoltage[6];
	uchar8	V_ucData[2];
	uchar8	V_ucReturnFlag;
	ushort16	V_usVoltageHEX_ABC[3];	/*ABC�����ѹ*/
	ushort16	V_usRelayOpenVol_LowLim;	/*����բ��ѹ����*/
	ushort16	V_usDataLength;
	ushort16	V_usDataEncode = 0;

	V_ucReturnFlag = C_VoltageOk;	
	
	if( InF_JudgeIJTimer() == C_OK )	/*������ڳ���״̬, ֱ�ӷ���OK*/
	{
		return V_ucReturnFlag;
	}
	
	V_usDataLength = CLRelayOpen_Vol__LowLim;
	InF_Read_Data(CRelayOpen_Vol__LowLim, V_ucData, &V_usDataLength, &V_usDataEncode);	/*��ȡ����բ��ѹ����*/
	PF_Buffer2ToUshort16(&V_ucData[0], &V_usRelayOpenVol_LowLim);

	V_usDataLength = CLPhaseFF_Volage;
	InF_Read_Data(CPhaseFF_Volage, V_ucVoltage, &V_usDataLength, &V_usDataEncode);	/*��ȡ�����ѹ*/
	PF_Buffer2ToUshort16(&V_ucVoltage[0], &V_usVoltageHEX_ABC[0]);
	PF_Buffer2ToUshort16(&V_ucVoltage[2], &V_usVoltageHEX_ABC[1]);
	PF_Buffer2ToUshort16(&V_ucVoltage[4], &V_usVoltageHEX_ABC[2]);
	
	if( (V_usVoltageHEX_ABC[0] < V_usRelayOpenVol_LowLim)
		&& (V_usVoltageHEX_ABC[1] < V_usRelayOpenVol_LowLim)
		&& (V_usVoltageHEX_ABC[2] < V_usRelayOpenVol_LowLim) )	/*�����ѹ��С������բ��ѹ����*/
	{
		V_ucReturnFlag = C_VoltageErr;	/*���ش���*/
	}

	return	V_ucReturnFlag;
}

/*******************************************************************************
����ԭ�ͣ�void SF_RealayOpenSignMsgSend_Relay(uchar8 V_ucDisplayType)
������������բ�ַ���ʾ��Ϣ
�����������
�����������
���ز�������
����λ�ã�
��    ע��
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
			V_ucDataBuff_Msg[1] = (C_RealayOpenSign | C_AlwaysDisplay);	/*��բ�ַ�����*/
			SF_MsgSend_Relay(V_ucDataBuff_Msg, Pt_DisplayStatus_Len + 1, C_Msg_Display);	/*������ʾ��Ϣ*/
			SV_RelayDisplayStatus &= C_RealayOpenSignOff;	/*��բ�ַ�Ϩ��*/
			SV_RelayDisplayStatus |= C_RealayOpenSignOn;	/*����բ�ַ����Ա�ʶ*/
		}break;
		
		case C_DisplayTwinkle:
		{
			V_ucDataBuff_Msg[1] = (C_RealayOpenSign | C_TwinkleDisplay);	/*��բ�ַ���˸*/
			SF_MsgSend_Relay(V_ucDataBuff_Msg, Pt_DisplayStatus_Len + 1, C_Msg_Display);	/*������ʾ��Ϣ*/
			SV_RelayDisplayStatus &= C_RealayOpenSignOff;	/*��բ�ַ�Ϩ��*/
			SV_RelayDisplayStatus |= C_RealayOpenSignTwinkle;	/*����բ�ַ���˸��ʶ*/
		}break;
		
		case C_DisplayOff:
		{
			V_ucDataBuff_Msg[1] = (C_RealayOpenSign | C_NotDisplay);	/*��բ�ַ�����ʾ*/
			SF_MsgSend_Relay(V_ucDataBuff_Msg, Pt_DisplayStatus_Len + 1, C_Msg_Display);	/*������ʾ��Ϣ*/
			SV_RelayDisplayStatus &= C_RealayOpenSignOff;	/*��բ�ַ�Ϩ���ʶ*/
		}break;
		
		default:
		{

		}break;
	}
	return;	
}

/*******************************************************************************
����ԭ�ͣ�void SF_RelayStatusLEDMsgSend_Relay(uchar8 V_ucDisplayType)
������������բָʾ����ʾ��Ϣ
�����������
�����������
���ز�������
����λ�ã�
��    ע��
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
			V_ucDataBuff_Msg[1] = (C_RelayStatusLED | C_AlwaysDisplay);	/*��բָʾ�Ƴ���*/
			SF_MsgSend_Relay(V_ucDataBuff_Msg, Pt_DisplayStatus_Len + 1, C_Msg_Display);	/*������ʾ��Ϣ*/
			SV_RelayDisplayStatus &= C_RelayStatusLEDOff;	/*��բָʾ��Ϩ��*/
			SV_RelayDisplayStatus |= C_RelayStatusLEDOn;	/*����բָʾ�Ƴ���*/
		}break;
		
		case C_DisplayTwinkle:
		{
			V_ucDataBuff_Msg[1] = (C_RelayStatusLED | C_TwinkleDisplay);	/*��բָʾ����˸*/
			SF_MsgSend_Relay(V_ucDataBuff_Msg, Pt_DisplayStatus_Len + 1, C_Msg_Display);	/*������ʾ��Ϣ*/
			SV_RelayDisplayStatus &= C_RelayStatusLEDOff;	/*��բָʾ��Ϩ��*/
			SV_RelayDisplayStatus |= C_RelayStatusLEDTwinkle;	/*����բָʾ����˸*/
		}break;
		
		case C_DisplayOff:
		{
			V_ucDataBuff_Msg[1] = (C_RelayStatusLED | C_NotDisplay);	/*��բָʾ�Ƴ���*/
			SF_MsgSend_Relay(V_ucDataBuff_Msg, Pt_DisplayStatus_Len + 1, C_Msg_Display);	/*������ʾ��Ϣ*/
			SV_RelayDisplayStatus &= C_RelayStatusLEDOff;	/*��բָʾ��Ϩ��*/
		}break;
		
		default:
		{

		}break;
	}
	return;			
}

/*******************************************************************************
����ԭ�ͣ�void SF_BackLEDMsgSend_Relay(uchar8 V_ucDisplayType)
����������������ʾ��Ϣ
�����������
�����������
���ز�������
����λ�ã�
��    ע��
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
			V_ucDataBuff_Msg[1] = (C_BackLED | C_AlwaysDisplay);	/*��������*/
			SF_MsgSend_Relay(V_ucDataBuff_Msg, Pt_DisplayStatus_Len + 1, C_Msg_Display);	/*������ʾ��Ϣ*/
			SV_RelayDisplayStatus |= C_BackLEDOn;	/*�������*/
		}break;
		
		case C_DisplayOff:
		{
			V_ucDataBuff_Msg[1] = (C_BackLED | C_NotDisplay);	/*�رձ���*/
			SF_MsgSend_Relay(V_ucDataBuff_Msg, Pt_DisplayStatus_Len + 1, C_Msg_Display);	/*������ʾ��Ϣ*/
			SV_RelayDisplayStatus &= C_BackLEDOff;	/*����Ϩ��*/
		}break;
		
		default:
		{

		}break;
	}
	return;			
}

/*******************************************************************************
����ԭ�ͣ�void SF_MsgSend_Relay(uchar8 *V_ucParm, uchar8 V_ucParmLen, uchar8 V_ucDerictAddr)
����������������Ϣ
�����������
�����������
���ز�������
����λ�ã�
��    ע��
*******************************************************************************/
void SF_MsgSend_Relay(uchar8 *V_ucParm, uchar8 V_ucParmLen, uchar8 V_ucDerictAddr)
{
	Str_Msg_Parameter Str_Msg_RelayStatus;
 
	Str_Msg_RelayStatus.SourceAddr = C_Msg_Deal_RelayStatus;	/*Դ��Ϣ��*/
	Str_Msg_RelayStatus.DerictAddr = V_ucDerictAddr;	/*Ŀ����Ϣ��*/
	Str_Msg_RelayStatus.Length = V_ucParmLen;	/*����*/
	Str_Msg_RelayStatus.Parameter = V_ucParm;	/*����*/
	InF_WriteMessege(&Str_Msg_RelayStatus);	/*д��Ϣ����*/
}

/*******************************************************************************
����ԭ�ͣ�uchar8 SF_GetNewOrderNum(void)
����������ȡ�����������
�����������
�����������
���ز�������ǰ������Žϴ��ֵ��1���
����λ�ã�
��    ע������Զ��������źͱ�����������нϴ��ֵ��1
*******************************************************************************/
uchar8 SF_GetNewOrderNum(void)
{
	uchar8	V_ucReturnNum = 1;
	
	if(SV_LocalOrderNum >= SV_ComOrderNum)	/*�Ƚ�Զ������ͱ��ؿ���������Ŵ�С*/
	{
		if(SV_LocalOrderNum == 0xFF)	/*��ǰΪFF������*/
		{
			SV_LocalOrderNum = 0x00;
			SV_ComOrderNum = 0x00;	
		}
		V_ucReturnNum += SV_LocalOrderNum;
	}
	else
	{
		if(SV_ComOrderNum == 0xFF)	/*��ǰΪFF������*/
		{
			SV_LocalOrderNum = 0x00;
			SV_ComOrderNum = 0x00;	
		}
		V_ucReturnNum += SV_ComOrderNum;	
	}
	
	return V_ucReturnNum;
}

/*******************************************************************************
����ԭ�ͣ�uchar8 SF_JudgeOrderStatus(void)
�����������жϵ�ǰ�̵���״̬�Ƿ������·���բ�Զ��ָ�����
�����������
�����������
���ز�����C_Allowed�������·���բ�Զ��ָ����C_UnAllowed���������·���բ�Զ��ָ�����
����λ�ã��ú�����InF_DealwithComRelayOrder�ӿں�������
��    ע��
*******************************************************************************/
uchar8 SF_JudgeOrderStatus(void)
{
	uchar8	V_ucReturnFlag;
	ushort16	V_usDataLength;
	ushort16	V_usDataEncode = 0;

	V_ucReturnFlag = C_Allowed;
	
	V_usDataLength = CLRelay_RemoteOrder;
	InF_Read_Data(CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, &V_usDataLength, &V_usDataEncode);	/*��ȡԶ�̿�������*/

	V_usDataLength = CLRelay_LocalOrder;
	InF_Read_Data(CRelay_LocalOrder, &Local_RelayOrder.PreWarning, &V_usDataLength, &V_usDataEncode);	/*��ȡ���ؿ�������*/
	
	V_usDataLength = CLRelay_State;
	InF_Read_Data(CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, &V_usDataLength, &V_usDataEncode);	/*��ȡ�̵���״̬*/
	
	if(Local_RelayOrder.RelayOrderStatus == C_Open)	/*��ǰ���ڱ���������բ״̬*/
	{
		V_ucReturnFlag = C_UnAllowed;	/*�������·���բ�Զ��ָ�����*/
		return V_ucReturnFlag;
	}
	
	if( ( (Local_RelayOrder.RelayOrderStatus == C_Pre_Open) || (Local_RelayOrder.RelayOrderStatus == C_Close_Allow) ) && (SV_L_CloseRealyDelay_Time != 0) )	/*��ǰ���ڱ���Ԥ��բ״̬��������բ��ʱʱ�䲻Ϊ0*/
	{
		V_ucReturnFlag = C_UnAllowed;	/*�������·���բ�Զ��ָ�����*/
		return V_ucReturnFlag;
	}
	
	if( (Combine_RelayOrder.RelayOrderStatus == C_Close_conditonal) && (Relay_Stutas.RelaytheoreticStatus == C_RelayOff) )
	{
		V_ucReturnFlag = C_UnAllowed;	/*�������·���բ�Զ��ָ�����*/
		return V_ucReturnFlag;	
	}
	
	if(Com_RelayOrder.RelayOrderStatus == C_Open)	/*��բ*/
	{
		V_ucReturnFlag = C_UnAllowed;	/*�������·���բ�Զ��ָ�����*/
		return V_ucReturnFlag;
	}
	
	return V_ucReturnFlag;
}

/*******************************************************************************
����ԭ�ͣ�void SF_Judge1D1EOrderStatus(void)
����������ͨ����բ�Զ��ָ������
�����������
�����������
���ز�������
����λ�ã��ú�����SF_LocalControl_Relay��������
��    ע��
*******************************************************************************/
void SF_Judge1D1EOrderStatus(void)
{
	uchar8	V_ucDataBuff[10];	
	ushort16	V_usDataLength;
	ushort16	V_usDataEncode = 0;

	V_usDataLength = CLRelay_RemoteOrder;
	InF_Read_Data(CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, &V_usDataLength, &V_usDataEncode);	/*��ȡԶ�̿�������*/

	if( ( (Com_RelayOrder.RelayOrderStatus == C_Open_Direct) || (Com_RelayOrder.RelayOrderStatus == C_Open_Allow) )
		&& (SV_Comm_CloseRealyDelay_Time != 0) )
	{
		SV_Comm_CloseRealyDelay_Time = 0;
		
		Com_RelayOrder.RelayOrderStatus = C_Close_Direct;
		InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_RemoteOrder, &Com_RelayOrder.PreWarning, CLRelay_RemoteOrder, C_W_SafeFlag);	/*Զ�̿�������д���ݲ�*/
			
		V_usDataLength = CLMeter_Work_State3;
		InF_Read_Data(CMeter_Work_State3, &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode);	/*��ȡ�������״̬��3*/
		V_ucDataBuff[0] &= C_RelayOrderStatusOn;	/*�̵������ͨ*/
		InF_Write_Data(C_Msg_Deal_RelayStatus, CMeter_Work_State3, &V_ucDataBuff[0], CLMeter_Work_State3, C_W_SafeFlag);	/*�������״̬��3д���ݲ�*/
	}
	return;
}

/*******************************************************************************
����ԭ�ͣ�void SF_Event_OpenRelay_Relay(void)
��������������բ����
�����������
�����������
���ز�������
����λ�ã��ú�����SF_CombineOrderExecute_Relay˽�к�������
��    ע��1�����øú���ǰ����ȷ����ѹ������������բҪ��
          2���ú���������բ�������ϱ���ʶ�����¼���¼��������բ��ʾ�ַ�
*******************************************************************************/
void SF_Op_OpenRelay_Relay(void)
{
	ushort16	V_usDataCRC;

	InF_RelayAct(C_Off);	/*��բ*/

	SV_Error_Time = 0x00;
	Relay_Stutas.RelaytheoreticStatus = C_RelayOff;	/*��������բ״̬*/
	InF_Write_Data(C_Msg_Deal_RelayStatus, CRelay_State, &Relay_Stutas.RelaytheoreticWarningStatus, CLRelay_State, C_W_SafeFlag);	/*����״̬д���ݲ�*/
	
	SV_EventOut_Open_Relay[0] = C_EventOut_Relay;	/*��ʾ��Ҫ�ϱ���բ�ɹ��¼�*/
	V_usDataCRC = PF_Cal_CRC(SV_EventOut_Open_Relay, 1);
	PF_Ushort16ToBuffer2(&SV_EventOut_Open_Relay[1], &V_usDataCRC); 
	
	SV_EventOut_Close_Relay[0] = C_EventOutNot_Relay;	/*��ʾ����Ҫ�ϱ���բ�ɹ��¼�*/
	V_usDataCRC = PF_Cal_CRC(SV_EventOut_Close_Relay, 1);
	PF_Ushort16ToBuffer2(&SV_EventOut_Close_Relay[1], &V_usDataCRC);	
	
	SV_EventOut_Err_Relay[0] = C_EventOutOpenErr_Relay;	/*��ʾ��Ҫ�ϱ����ɿ��������¼�*/
	V_usDataCRC = PF_Cal_CRC(SV_EventOut_Err_Relay, 1);
	PF_Ushort16ToBuffer2(&SV_EventOut_Err_Relay[1], &V_usDataCRC);		
	
	SF_Event_OpenRelay_Relay();	/*����բ�¼���¼*/
	
	SV_RelayRework_Timer = C_RelayRework_Timer;	/*���ظ�������ʱʱ���ֵ*/
	
	if( (SV_RelayDisplayStatus&C_RealayOpenSignOn) != C_RealayOpenSignOn)
	{
		SF_RealayOpenSignMsgSend_Relay(C_DisplayOn);	/*��բ�ַ�����*/
	}
	
	if(Relay_Stutas.RelaytheoreticWarningStatus != C_PreWarning)
	{
		if( (SV_RelayDisplayStatus&C_BackLEDOn) == C_BackLEDOn)
		{
			SF_BackLEDMsgSend_Relay(C_DisplayOff);	/*�رձ���*/
		}
	}
}

/**********************************************************************************************************************************
����ԭ�ͣ�uchar8 InF_Get_RelayModule(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, ushort16 *p_usDataEncode)
�������������ѿ�ģ��ӿ�
���������V_ulOAD:��Ҫ��ȡ��OAD��
		  pV_ucDataBuf:��ȡ���ݵĻ�����׵�ַ
		  *pV_usDataLen:��ȡ���ݵĻ������󳤶ȣ�
��������� pV_ucDataBuf:��ȡ���ݵĻ�����׵�ַ
		  *pV_usDataLen:��ȡ����ʵ�ʳ��ȣ�
          *P_usDataEncode:�����ڲ����룻
���ز�����C_OK,��ȡ�ɹ�;��������;
����λ�ã���������
��    ע��
************************************************************************************************************************************/
uchar8 InF_Get_RelayModule(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, ushort16 *p_usDataEncode)
{
	uchar8	V_ucBuffer[2], V_ucReturn = C_Error;
	ushort16	V_usDataLength;
	ushort16	V_usDataEncode = 0;

	if( (V_ulOAD & 0xFFFFFF00) == 0xF2050200)	/*�̵�������豸�����б�*/
	{
		V_ucReturn = SF_Get_ApplianceF205(V_ulOAD, pV_ucDataBuf, pV_usDataLen);
	}
	if(V_ulOAD == 0x80010200)	/*����״̬*/
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
	if(V_ulOAD == 0x80000400)	/*����״̬*/
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
	if(V_ulOAD == 0x80000500)	/*�̵�������״̬*/
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
����ԭ�ͣ�uchar8 SF_Get_ApplianceF205(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen)
������������ȡF205�豸�����
���������V_ulOAD:��Ҫ��ȡ��OAD��
		  pV_ucDataBuf:��ȡ���ݵĻ�����׵�ַ
		  *pV_usDataLen:��ȡ���ݵĻ������󳤶ȣ�
��������� pV_ucDataBuf:��ȡ���ݵĻ�����׵�ַ
		  *pV_usDataLen:��ȡ����ʵ�ʳ��ȣ�
���ز�����C_OK,��ȡ�ɹ�;��������;
����λ�ã��ú�����InF_Get_RelayModule��������
��    ע��
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
	V_ucReturn = InF_Read_Data(CMeter_Work_Char1, &pV_ucDataBuf[V_usOff], &V_usDataLength, &V_usDataEncode);	/*��ȡ�̵���״̬ */
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