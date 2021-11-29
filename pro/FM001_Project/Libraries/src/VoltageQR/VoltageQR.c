/********************************************************************************************
Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     VoltageQR.c
Version:       V1
Author:
Date:          2014-3-12
Description:   ��ѹ�ϸ���
---------------------------------------------------------------------------------------------
History1:      ��1���޸�
����1. Date:
       Author:
       Modification:
---------------------------------------------------------------------------------------------
����2. Date:
       Author:
       Modification:
---------------------------------------------------------------------------------------------
History2:      ��2���޸�
����1. Date:
       Author:
       Modification:
---------------------------------------------------------------------------------------------
����2. Date:
       Author:
       Modification:
---------------------------------------------------------------------------------------------
History3:      ��3���޸�
����1. Date:2021.09.22
       Author:zlj
       Modification:
---------------------------------------------------------------------------------------------
����2. Date:
       Author:
       Modification:
********************************************************************************************/

#include "public.h"
#include "VoltageQR.h"
#include "DI.h"

/*zljȥ���ñ�����Ŀǰ��������ģ���ڲ��ж��Ƿ�ʱ�䷢�������޸��ˣ�����������µ�ѹ�ϸ������ݡ�����������ȱ�������ʱ��ĳɿ��µ�1��0ʱ0�֣��򲻻��屾�µ�ѹ�ϸ��ʡ�
����ͨѶ��ʱ��仯��Ϣ*/
/*static Str_CurrentMonth_Type Str_CurrentMonth;*/

/*******************************************************************************
����ԭ��: InF_VoltageQRrestore(void)
��������: ��ѹ�ϸ���ģ���ϵ��ʼ������������ʧ�ܣ�����ȫ������
�������: ��
�������: ��
���ز���: ��
����λ��:
��    ע: �ϵ��ʼ��ʱ����
*******************************************************************************/
void InF_VoltageQRrestore(void)
{
	ushort16 V_usData_Length, V_usDataEncode = 0;
	uchar8 V_ucData[CLVolA_Per_Pass_M] = {0x00};

	/*zlj�����Ƿ�ͣ�ϵ�����жϣ�������£������µ�ѹ�ϸ���*/
	V_usData_Length = CLEnter_LowPower_Time;
	InF_Read_Data(CEnter_LowPower_Time, V_ucData, &V_usData_Length, &V_usDataEncode);
	V_usData_Length = CLExit_LowPower_Time;
	InF_Read_Data(CExit_LowPower_Time, V_ucData + CLEnter_LowPower_Time, &V_usData_Length, &V_usDataEncode);
	if ( (PF_DataTimeActive_698(V_ucData, C_SecondStart, CLEnter_LowPower_Time) == C_OK) && PF_DataTimeActive_698(V_ucData + CLEnter_LowPower_Time, C_SecondStart, CLExit_LowPower_Time) == C_OK)
	{
		if ( (V_ucData[C_Year_hi8] != V_ucData[C_Year_hi8 + CLEnter_LowPower_Time])
          || (V_ucData[C_Year_lo8] != V_ucData[C_Year_lo8 + CLEnter_LowPower_Time])
          || (V_ucData[C_Month] != V_ucData[C_Month + CLEnter_LowPower_Time]) )
		{
			SF_ClearVoltageQualifiedRate_Data();        /*�µ�ѹ�ϸ�������*/
		}
	}

	V_usData_Length = CLVolA_Per_Pass_M;
	if ( (InF_Read_Data(CVolA_Per_Pass_0, V_ucData, &V_usData_Length, &V_usDataEncode) != C_OK)					/*������A��ͳ������*/
      || (InF_Read_Data(CVolB_Per_Pass_0, V_ucData, &V_usData_Length, &V_usDataEncode) != C_OK)					/*������B��ͳ������*/
      || (InF_Read_Data(CVolC_Per_Pass_0, V_ucData, &V_usData_Length, &V_usDataEncode) != C_OK) )				/*������C��ͳ������*/
	{
		SF_ClearVoltageQualifiedRate_Data();            /*�µ�ѹ�ϸ�������*/
	}
	V_usData_Length = CLVolA_Per_Pass_D;
	if ( (InF_Read_Data(CVolA_Per_Pass_0_Freeze, V_ucData, &V_usData_Length, &V_usDataEncode) != C_OK)			/*����A��ͳ������*/
      || (InF_Read_Data(CVolB_Per_Pass_0_Freeze, V_ucData, &V_usData_Length, &V_usDataEncode) != C_OK)			/*����B��ͳ������*/
      || (InF_Read_Data(CVolC_Per_Pass_0_Freeze, V_ucData, &V_usData_Length, &V_usDataEncode) != C_OK) )		/*����C��ͳ������*/
	{
		InF_ClearVoltageQR_Data_D();																			/*�յ�ѹ�ϸ�������*/
	}

}

/*******************************************************************************
����ԭ��: InF_VoltageQR_ParseMessage
��������: ͨ����Ϣ����
�������: *pStr_Msg_Parameter:��Ϣ�ṹ��
�������: ��
���ز���: C_OK/C_Error
����λ��:
��    ע: ����ÿ���ӵ��ú���
*******************************************************************************/
uchar8 InF_VoltageQR_ParseMessage(Str_Msg_Parameter *pStr_Msg_Parameter)
{
	uchar8 *pV_ucParm;
	if (pStr_Msg_Parameter->PowerFlag == C_PowerFalling)						/*�е����־ֱ���˳�������C_OK*/
	{
		return(C_OK);
	}
	pV_ucParm = pStr_Msg_Parameter->Parameter;
	if (*pV_ucParm == Pt_Dispatch_Timing)										/*�жϲ����Ƿ���ȷ*/
	{
		if (*(pV_ucParm + 1) == C_SystemMinChange)
		{
			if (pStr_Msg_Parameter->Length == (Pt_Dispatch_Timing_Len + 1) )	/*�жϲ��������Ƿ���ȷ*/
			{
				Msg_VoltageQualifiedRateMetering();								/*��������ȷ���õ�ѹ�ϸ�������ͳ�ƺ���������C_0K*/
				return(C_OK);
			}
		}
		else if (*(pV_ucParm + 1) == C_SystemMonthChange)
		{
			SF_ClearVoltageQualifiedRate_Data();								/*�µ�ѹ�ϸ�����������*/
		}
	}
	if ( (*pV_ucParm == Pt_VRQTimeChange) && (pStr_Msg_Parameter->Length == (Pt_VRQTimeChange_Len + 1) ) )		/*zlj����ͨѶ�޸�ʱ��*/
	{
		if ( (*(pV_ucParm + 1 + C_Month)    != (*(pV_ucParm + 1 + CLDate_Week_Time + C_Month) ) )				/*�޸�ǰʱ����޸ĺ�ʱ������²�ͬ*/
          || (*(pV_ucParm + 1 + C_Year_lo8) != (*(pV_ucParm + 1 + CLDate_Week_Time + C_Year_lo8) ) )
          || (*(pV_ucParm + 1 + C_Year_hi8) != (*(pV_ucParm + 1 + CLDate_Week_Time + C_Year_hi8) ) ) )

		{
			SF_ClearVoltageQualifiedRate_Data();								/*�µ�ѹ�ϸ�����������*/
		}
	}
	return(C_Error);
}

/*******************************************************************************
����ԭ��: void SF_ClearVoltageQualifiedRate_Data(void)
��������: �µ�ѹ�ϸ�����������
�������: ��
�������: ��
���ز���: ��
����λ��: ���ݲ��Ϸ�ʱ���߹���Ȼ��ʱ����
��    ע:
*******************************************************************************/
void SF_ClearVoltageQualifiedRate_Data(void)
{
	uchar8 V_ucVol_Per_Pass_Data[CLVolA_Per_Pass_M] = {0x00};

	InF_Write_Data(C_Msg_VoltageQualifiedRateMetering, CVolA_Per_Pass_0, V_ucVol_Per_Pass_Data, CLVolA_Per_Pass_M, C_W_SafeFlag);	/*д����A��ͳ������*/
	InF_Write_Data(C_Msg_VoltageQualifiedRateMetering, CVolB_Per_Pass_0, V_ucVol_Per_Pass_Data, CLVolB_Per_Pass_M, C_W_SafeFlag);	/*д����B��ͳ������*/
	InF_Write_Data(C_Msg_VoltageQualifiedRateMetering, CVolC_Per_Pass_0, V_ucVol_Per_Pass_Data, CLVolC_Per_Pass_M, C_W_SafeFlag);	/*д����C��ͳ������*/
}

/*******************************************************************************
����ԭ��: Msg_VoltageQualifiedRateMetering
��������: ��ѹ�ϸ�������ͳ��
�������: ��
�������: ��
���ز���: ��
����λ��:
��    ע: ͨ����Ϣ������InF_VoltageQR_ParseMessage�����������ȷʱ���ã�����
         ������ֵ���㵱ǰ��ѹ�ϸ���ͳ�����ݲ�д���ݲ㡣
*******************************************************************************/
void Msg_VoltageQualifiedRateMetering(void)
{
	ushort16 V_usVoltPama[4];																								/*�洢��ѹ���ޡ���ѹ���ޡ���ѹ�������ޡ���ѹ��������*/
	ulong32 V_ulOADVoltPama[4] = {CVoltage_UpLim, CVoltage_LowLim, CVolage_Check_UpLim, CVolage_Check_LowLim};				/*�洢��ѹ���ޣ���ѹ���ޣ���ѹ�������ޣ���ѹ�������޵�OAD*/

	ushort16 V_usPhaseABC_Volt[3];																							/*�洢ABC���ѹ˲ʱ��*/
	ulong32 V_ulOADPhaseABC_Volt[3] = {CPhaseA_Volage, CPhaseB_Volage, CPhaseC_Volage};										/*�洢ABC���ѹ˲ʱ����OAD*/
    ushort16 V_usDataEncode = 0;

	uchar8 V_ucVol_Per_Pass_Data[3][CLVolA_Per_Pass_M];																		/*�洢ABC���µ�ѹ�ϸ�������*/

	ulong32 V_ulOADVolABC_Per_Pass_0[3] = {CVolA_Per_Pass_0, CVolB_Per_Pass_0, CVolC_Per_Pass_0};							/*�洢ABC���µ�ѹ�ϸ��ʵ�OAD*/

	uchar8  V_ucVol_Per_Pass_Data_D[3][CLVolA_Per_Pass_D];															/*�洢ABC���յ�ѹ�ϸ�������*/


	ulong32 V_ulOADVol_Per_Pass_0_Freeze[3] = {CVolA_Per_Pass_0_Freeze, CVolB_Per_Pass_0_Freeze,CVolC_Per_Pass_0_Freeze};	/*�洢ABC���յ�ѹ�ϸ������ݵ�OAD*/

	ushort16 V_usData_Length;
	uchar8  V_ucLine_Type, V_ucParemeter[CLVoltage_UpLim];
	uchar8 V_uci;

	for (V_uci = 0; V_uci < 4; V_uci++)														/*����ѹ���ޣ���ѹ���ޣ���ѹ�������ޣ���ѹ��������*/
	{
		V_usData_Length = CLVoltage_UpLim;
		if (InF_Read_Data(V_ulOADVoltPama[V_uci], V_ucParemeter, &V_usData_Length, &V_usDataEncode) != C_OK)
		{
			return;
		}
		PF_Buffer2ToUshort16(V_ucParemeter, &V_usVoltPama[V_uci]);
	}

	if ( (V_usVoltPama[C_offVoltage_UpLim] < V_usVoltPama[C_offVoltage_Check_UpLim])
      && (V_usVoltPama[C_offVoltage_LowLim] > V_usVoltPama[C_offVoltage_Check_LowLim])
      && (V_usVoltPama[C_offVoltage_LowLim] < V_usVoltPama[C_offVoltage_UpLim]) )			/*��������Ϸ���*/
	{
		for (V_uci = 0; V_uci < 3; V_uci++)													/*��ABC���ѹ*/
		{
			V_usData_Length = CLPhaseA_Volage;
			InF_Read_Data(V_ulOADPhaseABC_Volt[V_uci], V_ucParemeter, &V_usData_Length, &V_usDataEncode);
			PF_Buffer2ToUshort16(V_ucParemeter, &V_usPhaseABC_Volt[V_uci]);
		}

		V_usData_Length = CLLine_Type;
		InF_Read_Data(CLine_Type, &V_ucLine_Type, &V_usData_Length, &V_usDataEncode);		/*����������*/
		if (V_ucLine_Type == C_3P3W)														/*�������ߣ�ֱ�ӽ�B���ѹ��ֵΪ�ϸ��ѹ*/
		{
			V_usPhaseABC_Volt[C_offB_Volt] = V_usVoltPama[C_offVoltage_LowLim] + 1;
		}

		for (V_uci = 0; V_uci < 3; V_uci++)													/*��ABC���µ�ѹ�ϸ���ͳ������*/
		{
			V_usData_Length = CLVolA_Per_Pass_M;
			if (InF_Read_Data(V_ulOADVolABC_Per_Pass_0[V_uci], &V_ucVol_Per_Pass_Data[V_uci][0], &V_usData_Length, &V_usDataEncode) != C_OK)
			{
				SF_ClearVoltageQualifiedRate_Data();
				return;
			}
		}

		for (V_uci = 0; V_uci < 3; V_uci++)													/*����ABC���ѹ�ϸ���ͳ������*/
		{
			V_usData_Length = CLVolA_Per_Pass_D;
			if (InF_Read_Data(V_ulOADVol_Per_Pass_0_Freeze[V_uci], &V_ucVol_Per_Pass_Data_D[V_uci][0], &V_usData_Length, &V_usDataEncode) != C_OK)
			{
				memset(&V_ucVol_Per_Pass_Data_D[0][0], 0, CLVolA_Per_Pass_D + CLVolB_Per_Pass_D + CLVolC_Per_Pass_D);											/*CRC������������*/
				InF_ClearVoltageQR_Data_D();												/*���յ�ѹ�ϸ�������*/
			}
		}

		for (V_uci = 0; V_uci < 3; V_uci++)													/*ͳ��ABC���º��յ�ѹ�ϸ�������*/
		{
			if ( (V_usPhaseABC_Volt[V_uci] < V_usVoltPama[C_offVoltage_Check_UpLim]) && (V_usPhaseABC_Volt[V_uci] > V_usVoltPama[C_offVoltage_Check_LowLim]) )						/*A/B/C��ѹ�Ƿ��ڿ��˷�Χ��*/
			{
				MF_Calculate(&V_ucVol_Per_Pass_Data[V_uci][0], V_usPhaseABC_Volt[V_uci], V_usVoltPama[C_offVoltage_UpLim], V_usVoltPama[C_offVoltage_LowLim]);						/*A/B/C���ѹ�ڿ��˷�Χ�ڣ�����A/B/C���ѹ�ϸ���ͳ������*/
				MF_Calculate(&V_ucVol_Per_Pass_Data_D[V_uci][0], V_usPhaseABC_Volt[V_uci], V_usVoltPama[C_offVoltage_UpLim], V_usVoltPama[C_offVoltage_LowLim]);					/*A/B/C���ѹ�ڿ��˷�Χ�ڣ�������A/B/C���ѹ�ϸ���ͳ������*/
			}
			InF_Write_Data(C_Msg_VoltageQualifiedRateMetering, V_ulOADVolABC_Per_Pass_0[V_uci], &V_ucVol_Per_Pass_Data[V_uci][0], CLVolA_Per_Pass_M, C_W_SafeFlag);					/*д����A/B/C��ͳ������*/
			InF_Write_Data(C_Msg_VoltageQualifiedRateMetering, V_ulOADVol_Per_Pass_0_Freeze[V_uci], &V_ucVol_Per_Pass_Data_D[V_uci][0], CLVolA_Per_Pass_D, C_W_SafeFlag);			/*д��A/B/C��ͳ������*/
		}
	}
}

/*******************************************************************************
����ԭ��: void MF_Calculate
��������: �����ѹ�ϸ������ݼ���
�������: *pV_Data �����ѹ�ϸ���ͳ������ָ�룻V_usCurrentVoltage ���൱ǰ��ѹ��V_usVoltage_UpLim ��ѹ���ޣ�
          V_usVoltage_LowLim ��ѹ���ޣ�
�������: *pV_Data �����ѹ�ϸ���ͳ�����ݣ�
���ز���: ��
����λ��:
��    ע: ��ѹ�ϸ�������ͳ�ƺ���Msg_VoltageQualifiedRateMetering����A��B��C��
         ��ѹ�ϸ�������ʱ�ֱ���á�
*******************************************************************************/
void MF_Calculate(uchar8 *pV_Data, ushort16 V_usCurrentVoltage, ushort16 V_usVoltage_UpLim, ushort16 V_usVoltage_LowLim)
{
	ulong32 V_ulMonitorTime, V_ulOverUpTime, V_ulOverLowTime;
	ushort16 V_usPassRate, V_usOverRate;
	ulong64 V_ulTemp;

	PF_BufferXToUlong32(pV_Data, &V_ulMonitorTime, CLPer_Pass_MonitorTime);
	V_ulMonitorTime++;						/*��ѹ���ʱ��+1*/
	PF_Ulong32ToBufferX(pV_Data, &V_ulMonitorTime, CLPer_Pass_MonitorTime);

	PF_BufferXToUlong32( (pV_Data + CLPer_Pass_MonitorTime + CLPer_Pass_PassRate + CLPer_Pass_OverRate), &V_ulOverUpTime, CLPer_Pass_OverUpTime);						/*��ѹ������ʱ��*/
	PF_BufferXToUlong32( (pV_Data + CLPer_Pass_MonitorTime + CLPer_Pass_PassRate + CLPer_Pass_OverRate + CLPer_Pass_OverUpTime), &V_ulOverLowTime, CLPer_Pass_OverLowTime);		/*��ѹ������ʱ��*/
	if (V_usCurrentVoltage > V_usVoltage_UpLim)
	{
		V_ulOverUpTime++;					/*��ѹ������ʱ��+1*/
		PF_Ulong32ToBufferX( (pV_Data + CLPer_Pass_MonitorTime + CLPer_Pass_PassRate + CLPer_Pass_OverRate), &V_ulOverUpTime, CLPer_Pass_OverUpTime);
	}
	else if (V_usCurrentVoltage < V_usVoltage_LowLim)
	{
		V_ulOverLowTime++;					/*��ѹ������ʱ��+1*/
		PF_Ulong32ToBufferX( (pV_Data + CLPer_Pass_MonitorTime + CLPer_Pass_PassRate + CLPer_Pass_OverRate + CLPer_Pass_OverUpTime), &V_ulOverLowTime, CLPer_Pass_OverLowTime);
	}

	V_ulTemp = V_ulOverUpTime + V_ulOverLowTime;
	V_usOverRate = (ushort16)( (V_ulTemp * 100000 / V_ulMonitorTime + 5) / 10 );														/*�����ѹ�����ʱ�����λС��*/
	PF_Ushort16ToBuffer2( (pV_Data + CLPer_Pass_MonitorTime + CLPer_Pass_PassRate), &V_usOverRate);

	V_usPassRate = 10000 - V_usOverRate;	/*�����ѹ�ϸ���*/
	PF_Ushort16ToBuffer2( (pV_Data + CLPer_Pass_MonitorTime), &V_usPassRate);

}

/*******************************************************************************
����ԭ��: void InF_ClearVoltageQR_Data_D(void)
��������: �ն����ѹ�ϸ�����������
�������: ��
�������: ��
���ز���: ��
����λ��:
��    ע:
*******************************************************************************/
void InF_ClearVoltageQR_Data_D(void)
{
	uchar8	V_ucData_Buff[CLVol_Per_Pass_D] = {0};

	InF_Write_Data(C_Msg_VoltageQualifiedRateMetering, CVolA_Per_Pass_0_Freeze, V_ucData_Buff, CLVolA_Per_Pass_D, C_W_SafeFlag);	/*д��A��ͳ������*/
	InF_Write_Data(C_Msg_VoltageQualifiedRateMetering, CVolB_Per_Pass_0_Freeze, V_ucData_Buff, CLVolB_Per_Pass_D, C_W_SafeFlag);	/*д��B��ͳ������*/
	InF_Write_Data(C_Msg_VoltageQualifiedRateMetering, CVolC_Per_Pass_0_Freeze, V_ucData_Buff, CLVolC_Per_Pass_D, C_W_SafeFlag);	/*д��C��ͳ������*/
}
