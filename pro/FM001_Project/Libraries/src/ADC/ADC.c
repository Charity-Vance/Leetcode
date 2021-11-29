/*******************************************************************************
Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     ADC.c
Version:       V1
Author:
Date:          2014-3-12
Description:   ��ص�ѹת���ļ�
---------------------------------------------------------------------------------
History1:      ��1���޸�
����1. Date:   20201206
   	   Author:
       Modification:ɽ��˫Э�����
	   ---------------------------------------------------------------------------
����2. Date:
   	   Author:
       Modification:
----------------------------------------------------------------------------------
History2:      ��2���޸�
����1. Date:
   	   Author:
       Modification:
	   ---------------------------------------------------------------------------
����2. Date:
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
///*Function��void ADC_SendMessage(uchar8 *pParm,uchar8 ParmLen,uchar8 DestMsg)*///
///*Description��ADCģ�鷢��Ϣ������ģ��*///
///*Input��	*P_Parameter:��Ϣ�еĲ������׵�ַ*///
///*		ParameterLen:�����򳤶�*///
///*		DerictAddrMsg:Ŀ�ĵ�ַ*///
///*Output����*///
///*Calls��*///
///*Called By�������ȷ���Ϣʱ����*///
///*Influence�����õĵط���Դ��Ϣ�š�Ŀ����Ϣ�š�����������ú���øú���*///
///**********************************************************************************///
void ADC_SendMessage(uchar8 MsgDerictAddr,uchar8 *P_Parameter,uchar8 ParameterLen)
{
	Str_Msg_Parameter	Str_Message;
	Str_Message.SourceAddr = C_Msg_BatteryVoltagleMetering;	///*Դ��ַ��Ȼ��ADCģ��*///
	Str_Message.DerictAddr = MsgDerictAddr;
	Str_Message.Parameter = P_Parameter;
	Str_Message.Length = ParameterLen;
	InF_WriteMessege(&Str_Message);
}

///***********************************************************************************///
///*Function���ж��Ƿ�������*///
///*Description��*///
///*Input:warn_type:   ��������:C_AlarmSign,C_BackLED,C_WarnOutPut*///
///*	  warn_object: ��������:C_RTCBatterySign,C_PowerBatterySign*///
///*      C_RTCBatterySign        46      ///*ʱ�ӵ��Ƿѹ 		*///
///*      C_PowerBatterySign      47      ///*ͣ�����Ƿѹ 		*///
///*      C_AlarmSign             26      ///*������־     		*///
///*      C_BackLED               51      ///*����		       	*///
///*      C_WarnOutPut            52      ///*�������    		*///
///*Output��C_OK:������,C_Error:��ֹ����*///
///***********************************************************************************///
uchar8 SF_JudgeWarn(uchar8 warn_object,uchar8 warn_type)
{
	uchar8 V_ucBuffer[15];
	uchar8 v_return = C_Error;			///*�˴��ĸ���ֵΪ�����󡱱�����*///
	ushort16 V_len, V_usDataEncode;

	V_len = CLAlarm_Status;
	if( InF_Read_Data(CAlarm_Status,&V_ucBuffer[0],&V_len, &V_usDataEncode) != C_OK )
	{
		return v_return;
	}
	switch (warn_type)
	{
		///**************************************///
		///*����С����*///
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
		///*�����*///
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
		///*�����̵������*///
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
///*Function:���ݵ�ǰʱ�ӵ��״̬����ʾ��ط���*///
///*Description:*///
///*input:C_OK:�������,C_Error:���Ƿѹ*///
///*output:��ط���*///
///*return:��*///
///***********************************************************************************///
void SF_RTCBattSymbol(uchar8 BattStatus)
{
	uchar8 V_ucBuffer[4];

	if( BattStatus == C_BATT_OK )
	{
		///*ʱ�ӵ�ز���ʾ*///
		V_ucBuffer[0] = Pt_DisplayStatus;
		V_ucBuffer[1] = C_RTCBatterySign|C_NotDisplay;
		V_ucBuffer[2] = 0xFF;
		V_ucBuffer[3] = 0xFF;
	}
	else
	{
		///*ʱ�ӵ����ʾ*///
		V_ucBuffer[0] = Pt_DisplayStatus;
		V_ucBuffer[1] = C_RTCBatterySign|C_AlwaysDisplay;
		V_ucBuffer[2] = 0xFF;
		V_ucBuffer[3] = 0xFF;
	}

	ADC_SendMessage(C_Msg_Display,V_ucBuffer,(Pt_DisplayStatus_Len+1));
}
///***********************************************************************************///
///*Function:���ݵ�ǰ���ѵ��״̬����ʾ��ط���*///
///*Description:*///
///*input:C_OK:�������,C_Error:���Ƿѹ*///
///*output:��ط���*///
///*return:��*///
///***********************************************************************************///
void SF_WakeUpBattSymbol(uchar8 BattStatus)
{
	uchar8 V_ucBuffer[4];

	if( BattStatus == C_BATT_OK )
	{
		///*���ѵ�ز���ʾ*///
		V_ucBuffer[0] = Pt_DisplayStatus;
		V_ucBuffer[1] = C_PowerBatterySign|C_NotDisplay;
		V_ucBuffer[2] = 0xFF;
		V_ucBuffer[3] = 0xFF;
	}
	else
	{
		///*���ѵ����ʾ*///
		V_ucBuffer[0] = Pt_DisplayStatus;
		V_ucBuffer[1] = C_PowerBatterySign|C_AlwaysDisplay;
		V_ucBuffer[2] = 0xFF;
		V_ucBuffer[3] = 0xFF;
	}

	ADC_SendMessage(C_Msg_Display,V_ucBuffer,(Pt_DisplayStatus_Len+1));
}

///***********************************************************************************///
///*Function:������״̬�б仯������С���������⡢�����̵������౨�������*///
///*Description:�ú�����״̬�����仯�����*///
///*input:ChangeFlag=C_BattChange,��ʾ���״̬�б仯*///
///*output:С����/����/�����̵���������ָ�*///
///*return:��*///
///***********************************************************************************///
void SF_BattWarn(uchar8 ChangeFlag)
{
	uchar8 V_ucBuffer[16];
	uchar8 i=0;

	if( ChangeFlag != 0 )	///*���״̬�б仯����*///
	{
		///*С������˸*///
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
		///*�������*///
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
		///*�����̵������*///
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
///*Function���ر�ADC*///
///*Description��ֹͣADCת��,�ر�ADC��ʱ��Դ*///
///***********************************************************************************///
void InF_ADC_OFF(void)
{
	ANAC->ADCCON = 0;
	ANAC->ADCIF |= ANAC_ADCIF_ADC_IF_SET;///*���жϱ�־
	RCC->PERCLKCON2 &= (~RCC_PERRCCCON2_ADCCKE_ON);///*�ر�ADCʱ��Դ
}

///***********************************************************************************///
///*Function����ʼ��ADC*///
///***********************************************************************************///
void SF_InitADC(void)
{
	///*ʹ��ADCʱ��Դ������Ƶ��512k*///
	RCC->PERCLKCON2 &= (~RCC_PERRCCCON2_ADCCKSEL_RCLP);
	RCC->PERCLKCON2 |= (RCC_PERRCCCON2_ADCCKSEL_RCHFDIV32|RCC_PERRCCCON2_ADCCKE_ON);
//	SF_ADC_Set(C_ADC_Iint);
	///*���ÿ���Ϊģ�������*///
	Set_IO_RTCBatt_Analong();
	Set_IO_WakeBatt_Analong();
	Set_IO_Cap_Analong();
	ANAC->ADCINSEL = ANAC_ANATESTSEL_BUF4TST_SEL_AN8;///*ѡ��PB3ͨ����3.6V
	ANAC->ADCINSEL |= ANAC_ANATESTSEL_BUF4TST_EN_ENABLE;///*����Buffʹ��

	ANAC->ADCCON = 0;
	ANAC->ADCCON |= ANAC_ADCCON_ADC_VANA_EN_Voltage;///*��ѹ����
	ANAC->ADCTRIM = const_adc_TrimB;

	ANAC->ADCIF |= ANAC_ADCIF_ADC_IF_SET;///*���жϱ�־
	ANAC->ADCCON |= ANAC_ADCCON_ADC_EN_ENABLE;///*ʹ��ADC

}
///***********************************************************************************///
///*Function��ADC�¶ȼ���*///
///***********************************************************************************///
//long32 SF_ADC_TempCalc(ulong32 ulADCData)
//{
//	long64 l64Data,l64DataADC,l64DataT;///*����10000��
//	ushort16 us16DataFa;
//
//	if( const_temp_TestA == 0x1E )
//	{
//		//ʹ���¶ȶ�������
//		l64DataT = const_temp_TestA*10000+(const_temp_TestB>>7)*5000;
//		l64DataADC = const_adc_Test*10000 - const_T_Offset3V*const_TmpsH;
//	}
//	else
//	{
//		//������ʱʹ��
//		l64DataT = 300000;
//		l64DataADC = 15000000;
//	}
//	l64Data=ulADCData*10000;
//	if( l64Data > (l64DataADC-250000) )	//����
//	{
//		us16DataFa = const_TmpsH;
//	}
//	else
//	{
//		us16DataFa = const_TmpsL;
//	}
//	l64Data = (l64Data - l64DataADC)/us16DataFa + l64DataT;
//	l64Data=l64Data/1000;///*Ԥ��һλС��
//	return (long32)l64Data;
//}
///***********************************************************************************///
///*Function��ADC����ֵ����*///
///***********************************************************************************///
ulong32 SF_ADC_VoltageCalc(ulong32 ulADCData)
{
	long64 ul64Data;///*����100��

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
	else///*����������
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
		ul64Data /= 1000;///*xxxmV��
	}
	return (ulong32)ul64Data;
}

float GetRtcRTrimVal( ulong32 Temperature_Adc )//����adc���ݲ���ֵ
{
	float Rtcadj = 0;
	float Fk;
	uchar8 i;

	for(i=1; i<=20; i++)//�¶������ж�
	{
		if(Temperature_Adc < RTC_RT.TAdc.PTAT_Value[i])
		{
			break;
		}
	}

	//����ֵ����
	if(i<21)
	{
		Fk = (float)(((float)RTC_RT.TVal.Trim_Value[i-1] - (float)RTC_RT.TVal.Trim_Value[i])/((float)RTC_RT.TAdc.PTAT_Value[i-1] - (float)RTC_RT.TAdc.PTAT_Value[i]));

		Rtcadj = Fk*(((float)Temperature_Adc - (float)RTC_RT.TAdc.PTAT_Value[i-1])) + (float)RTC_RT.TVal.Trim_Value[i-1];
	}
	return Rtcadj;
}
/***********************************************************************************
*Function��ADC�¶Ȳ�����ʱ�ӵ�У���ϵ�5s���ã������е�10s���á�û�������83min����1�Σ�ͬʱ���������ݲ��¶ȡ�
*ͨ��ʱ�ӵ�Уֱ�ӵ��ýӿں���
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

	if(C_PowerOn!=InF_ReadPowerState() )	/*��ȡ��ǰ״̬,�͹���״̬��ʹ��ʱ��*/
	{
	/*ʹ��ADCʱ��Դ������Ƶ��512k*/
		SF_ADC_Set(C_ADC_Lowpower);
	}
	Temperature_Adc = GV_ucTemp_Data[32];
	AverADCf = (float)GV_ucTemp_Data[32]/32;

	/*0 �����¶�б��΢�����ݲ�֧�֣�
	1 �����¶�б��΢�����ݲ�֧�֣�
	2 ���¾�������΢���������޵����κ���ϵ����x*0.0001 kh
	3 ���¾�������΢���������޵����κ���ϵ����x*0.0001 kl
	4 ���¶����Уֵ����ֵ(��1.27ppm)
	5 �����¶�ADC΢��
	6 ���¶����УֵL��ͨ�ŵ�ʱ������327.68ppm
	7 ���¶����УֵH��ͨ�ŵ�ʱ����
	8 RTC��������ģʽ��0x55:����ģʽ��0xAA���²���ֵģʽ����������ͨģʽ
	9 ����25+��������΢��������25+�޵����κ���ϵ����x*0.0002 krh
	10����25-��������΢��������25-�޵����κ���ϵ����x*0.0002 krl*/
		memcpy( BufC, Tpara.Offset, ee_temperature_lenth );/*�����¶�ϵ��*/
		for( i=0; i<6; i++ ) //��������ת�����з�����
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
			/*ʹ���¶ȶ�������*/
#if 0		/*ԭ������*/
			T25ADC = (const_adc_Test+(short)BufC[5]) - (const_temp_TestA+(float)(const_temp_TestB/0x80)*0.5-const_xtl_top)*const_TmpsH;/*����ߵ�������ת�۵��ADCֵ*/
			if( EA_OFF )
			{
				T = T + const_T_OffsetSlp;
				T25ADC = (const_adc_Test+(short)BufC[5]) - (const_temp_TestA+(float)(const_temp_TestB/0x80)*0.5-const_xtl_top)*const_TmpsH - const_T_OffsetSlp*const_TmpsH;		/*����ߵ�������ת�۵��ADCֵ*/
			}
			else
			{
				T = T + const_T_OffsetRun;
#endif
				T25ADC = (const_adc_Test+(short)BufC[5]) - (const_temp_TestA+(float)(const_temp_TestB/0x80)*0.5-const_xtl_top)*const_TmpsH - const_T_OffsetRun*const_TmpsH;		/*����ߵ�������ת�۵��ADCֵ*/
#if 0		/*ԭ������*/
			}
#endif
		}
		else
		{
			/*������ʱʹ��*/
			T25ADC = 1470 + (25 - const_xtl_top)*const_TmpsH;	/*�����ã��������滻Ϊ�¶ȶ�������*/
		}
#if 0		/*ԭ������*/
		if( (SleepPtatOffsetCfg == 0x55)&&(EA_OFF) )/*ͣ���¶Ȳ�������3v offset*/
		{
#endif
			if( const_ptat_Offset3V <= 10 )
			{
				T25ADC -= const_ptat_Offset3V;
			}
#if 0		/*ԭ������*/
			else
			{
				T25ADC -= 5;
			}
		}
#endif
		T25 = const_xtl_top;
		if( const_tx_flag != 0x3cc3 )					/*ͨ��У׼ʱ�����*/
		{
			TopF_Rtc_Adj = ((short16)((uchar8)BufC[6]|((uchar8)BufC[7]<<8)))/100.0;	/*��С100��*/
		}
		else											/*��У��У׼ʱ�����*/
		{
			TopF_Rtc_Adj = const_rtc_adj_top/100.0;		/*��С100��*/
		}

		if( AverADCf > T25ADC )							/*����*/
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
		if( T >= 0x00 )/*���㵱ǰ�¶�*/
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
		if(C_PowerOn==InF_ReadPowerState() )		/*��ȡ��ǰ״̬,�е�״̬�²Ÿ���*/
		{
			InF_Write_Data(C_Msg_MeterIC,CMeter_Temp,&V_ucBuffer[0],CLMeter_Temp,C_W_SafeFlag);
		}
		/*******����Ϊ�¶Ȳ���********/
/*		TR_Proc(T);û��ʵ�����ã������¼��*/
		/*����¶ȷ�Χ��־�ж� 0=���£�1=���£�2=���£�����Ϊ�¶�ʱ�Ӳ���*/
		if( T < 0 )
		{
			Result = 1;//���²��
		}
		else if( T > 50 )
		{
			Result = 2;//���²��
		}
		else
		{
			Result = 0;//���²��
		}

		if( const_C_Mode != 0x55 )
		{
			RTC_RT.TempFlag = 0;
			RTC_RT.CFixTrim = TopF_Rtc_Adj;
		}
		else if( ((Tpara.RtcTMode == 0xAA)||(Tpara.RtcTMode == 0x55)) && (RTC_RT.TempFlag != Result) )/*�ı������У���²�����*/
		{
			RTC_RT.TempFlag = Result;

			Fill_RTC_RT_TAdc();
			Fill_RTC_RT_TVal();

			if( RTC_RT.TempFlag == 0 )//���²��
			{
				RTC_RT.CFixTrim = TopF_Rtc_Adj;
			}
			else if( RTC_RT.TempFlag == 1 )//���²��
			{
				Fa = const_KL +0.0001*BufC[3];
				RTC_RT.CFixTrim = TopF_Rtc_Adj + (-1.0)*Fa*(const_T_CL-const_xtl_top)*(const_T_CL-const_xtl_top);//���²�������¶������㣬ppm
			}
			else if( RTC_RT.TempFlag == 2 )//���²��
			{
				Fa = const_KH +0.0001*BufC[2];
				RTC_RT.CFixTrim = TopF_Rtc_Adj + (-1.0)*Fa*(const_T_CH-const_xtl_top)*(const_T_CH-const_xtl_top);//���²�������¶������㣬ppm
			}
		}

		if( (Tpara.RtcTMode == 0xAA)||(Tpara.RtcTMode == 0x55) )//���²���ֵģʽ,��ֹkrh��krl΢������
		{
			BufC[9] = 0;
			BufC[10] = 0;
		}
 		if( AverADCf > T25ADC )		/*����*/
		{
			/*����kh��kl΢���Գ��²���Ӱ��*/
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

		Rtcadj_Offset = Fa*(T-const_xtl_top)*(T-const_xtl_top);		/*���������㣬ppm*/
		Rtcadj_Offset2 = Fb*(T-const_xtl_top)*(T-const_xtl_top);	/*���������㣬ppm����У��*/

		/*���²���ֵģʽ*/
		if( (Tpara.RtcTMode == 0xAA)&&( (Temperature_Adc>RTC_RT.TAdc.PTAT_Value[0]) && (Temperature_Adc<RTC_RT.TAdc.PTAT_Value[20]) ))//����������
		{
			Rtcadj = GetRtcRTrimVal( Temperature_Adc );
			/*������*�������� = ������ppm��*/
			Rtcadj = Rtcadj*0.23842;	/*��С������Ϊ0.238ppm*/
			if( (const_mark404 == 0x0404)&&(RTC_Trim_Ctrl == 0x55) )
			{
				Rtcadj = Rtcadj/2.0;	/*��С������Ϊ0.119ppm*/
			}
			Rtcadj = Rtcadj + ((short)BufC[4])/100.0 + RTC_RT.CFixTrim;
		}
		else if( (Tpara.RtcTMode == 0x55)&&(C_OK==InF_IsInFactoryState())) /*����ģʽ,ʹ�ù̶���Уֵ*/
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
		else if( (RtcStopProcFlag == 0x55)&&(C_OK==InF_IsInFactoryState()))	/*ͨ��У׼ʱ�ӹرղ���������*/
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
			Rtcadj = Rtcadj*8.388608;/*ת��Ϊ��Уֵ,0.119*/
		}
		else
		{
			Rtcadj = Rtcadj*4.194304;/*ת��Ϊ��Уֵ,0.238*/
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
����ԭ�ͣ� InF_ADC_Action_Message
���������� ADCת��
��������� P_Msg_Parameter  ��Ϣ��ڲ���
��������� ��
���ز����� ��
����λ��:
��    ע��
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
			ANAC->ADCIF |= ANAC_ADCIF_ADC_IF_SET;			/*���жϱ�־*/
			V_ulRTC_Data = ANAC->ADCDATA;
			break;
		}
	}
	/*��1��ת��ֵ����*/
	V_ulRTC_Data = 0;
	for(V_usdelaycount = 0; V_usdelaycount < C_ADC_Delay; V_usdelaycount++)
	{
		InF_Delay_2us();
		if( ANAC->ADCIF & ANAC_ADCIF_ADC_IF_SET )
		{
			ANAC->ADCIF |= ANAC_ADCIF_ADC_IF_SET;			/*���жϱ�־*/
			V_ulRTC_Data = ANAC->ADCDATA;
			break;
		}
	}

	ANAC->ADCINSEL = ANAC_ANATESTSEL_BUF4TST_SEL_AN2;		/*ѡ��PC13ͨ����6V*/
	ANAC->ADCINSEL |= ANAC_ANATESTSEL_BUF4TST_EN_ENABLE;	/*����Buffʹ��*/

	V_ulWakeUp_Data = 0;

	for(V_usdelaycount = 0; V_usdelaycount < C_ADC_Delay; V_usdelaycount++)
	{
		InF_Delay_2us();
		if( ANAC->ADCIF & ANAC_ADCIF_ADC_IF_SET )
		{
			ANAC->ADCIF |= ANAC_ADCIF_ADC_IF_SET;			/*���жϱ�־*/
			V_ulWakeUp_Data = ANAC->ADCDATA;
			break;
		}
	}
	ANAC->ADCINSEL = ANAC_ANATESTSEL_BUF4TST_SEL_AN7;		/*ѡ��PB2ͨ������������*/
	ANAC->ADCINSEL |= ANAC_ANATESTSEL_BUF4TST_EN_ENABLE;	/*����Buffʹ��*/

	V_ulCAP_Data = 0;
	for(V_usdelaycount = 0; V_usdelaycount < C_ADC_Delay; V_usdelaycount++)
	{
		InF_Delay_2us();
		if( ANAC->ADCIF & ANAC_ADCIF_ADC_IF_SET )
		{
			ANAC->ADCIF |= ANAC_ADCIF_ADC_IF_SET;			/*���жϱ�־*/
			V_ulCAP_Data = ANAC->ADCDATA;
			break;
		}
	}

	/*******************�����¶�ֵ��ʱ��RTC��У********************/
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
	V_ulRTC_Data >>= 1;										/*Ӳ����·�й�*/
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
	if( V_ucstatus == C_BATT_OK )							/*��ǰ���״̬����*/
	{
		if( Str_RTCBATT.HStatus == C_BATT_OK )			/*��ʷ״̬����*/
		{
			Str_RTCBATT.Timer = 0;
		}
		else
		{
			if( Str_RTCBATT.Timer >= C_BATTErr_Times )			/*��ʷ���������ҳ���3��*/
			{
				Str_RTCBATT.HStatus = C_BATT_OK;
				/*��ʷ״̬д���ݲ�*/
				InF_Write_Data(C_Msg_BatteryVoltagleMetering, CCloc_Batt_LowState, &Str_RTCBATT.HStatus, CLCloc_Batt_LowState, C_W_SafeFlag);
				V_ucChangeFlag |= C_RTCBattChange_Ok;			/*�õ��״̬�б仯��־*/
				SF_RTCBattSymbol(C_BATT_OK);					/*ȡ����ط���*/
			}
		}
	}
	else if( V_ucstatus == C_BATT_ERR )							/*��ǰ���״̬�쳣*/
	{
		if( Str_RTCBATT.HStatus == C_BATT_ERR )					/*��ʷ״̬�쳣*/
		{
			Str_RTCBATT.Timer = 0;
		}
		else
		{
			if( Str_RTCBATT.Timer >= C_BATTErr_Times )			/*��ʷ�������ҳ���3��*/
			{
				Str_RTCBATT.HStatus = C_BATT_ERR;
				InF_ActiveReportSetting(C_Times_RTCBatteryErr);	/*645�������ϱ�*/
				Inf_WriteMeterStatus8(C_RTCBatLowVolEventNo);
				/*��ʷ״̬д���ݲ�*/
				InF_Write_Data(C_Msg_BatteryVoltagleMetering, CCloc_Batt_LowState, &Str_RTCBATT.HStatus, CLCloc_Batt_LowState, C_W_SafeFlag);
				V_ucChangeFlag |= C_RTCBattChange_Err;			/*�õ��״̬�б仯��־*/
				SF_RTCBattSymbol(C_BATT_ERR);					/*��ʾ��ط���*/
			}
		}
	}
	/*���µ������״̬��1�е�ʱ�ӵ�ع���״̬��־�����ϻ����������ȴ����ݲ����ˢ�º���д*/
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
	V_ulWakeUp_Data <<= 1;									/*Ӳ����·�й�*/
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
	if( V_ucstatus == C_BATT_OK )							/*��ǰ���״̬����*/
	{
		if( Str_WAKEUPBATT.HStatus == C_BATT_OK )			/*��ʷ״̬����*/
		{
			Str_WAKEUPBATT.Timer = 0;
		}
		else
		{
			if( Str_WAKEUPBATT.Timer >= C_BATTErr_Times )	/*��ʷ���������ҳ���3��*/
			{
				/*״̬�����仯,��״̬д���ݲ�,���б�����ش���*/
				Str_WAKEUPBATT.HStatus = C_BATT_OK;
				InF_Write_Data(C_Msg_BatteryVoltagleMetering, CReadMeter_Batt_LowState, &Str_WAKEUPBATT.HStatus, CLReadMeter_Batt_LowState, C_W_SafeFlag);
				V_ucChangeFlag |= C_WakeupBattChange_Ok;		/*�õ��״̬�б仯��־*/
				SF_WakeUpBattSymbol(C_BATT_OK);				/*ȡ����ط���*/
			}
		}
	}
	else if( V_ucstatus == C_BATT_ERR )						/*��ǰ���״̬�쳣*/
	{
		if( Str_WAKEUPBATT.HStatus == C_BATT_ERR )			/*��ʷ״̬�쳣*/
		{
			Str_WAKEUPBATT.Timer = 0;
		}
		else
		{
			if( Str_WAKEUPBATT.Timer >= C_BATTErr_Times )   /*��ʷ�������ҳ���3��*/
			{
				/*״̬�����仯,��״̬д���ݲ�,���б�����ش���������ϱ�*/
				Str_WAKEUPBATT.HStatus = C_BATT_ERR;
				InF_ActiveReportSetting(C_Times_PowerBatteryErr);	/*645�������ϱ�*/

				Inf_WriteMeterStatus8(C_PowerBatLowVolEventNo);
				InF_Write_Data(C_Msg_BatteryVoltagleMetering, CReadMeter_Batt_LowState, &Str_WAKEUPBATT.HStatus, CLReadMeter_Batt_LowState, C_W_SafeFlag);
				V_ucChangeFlag |= C_WakeupBattChange_Err;	    /*�õ��״̬�б仯��־*/
				SF_WakeUpBattSymbol(C_BATT_ERR);			/*��ʾ��ط���*/
			}
		}
	}
	/*���µ������״̬��1�еĻ��ѵ�ع���״̬��־�����ϻ����������ȴ����ݲ����ˢ�º���д*/
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
	SF_BattWarn(V_ucChangeFlag);		/*���ݵ�ر仯��־,�Ե��Ƿѹ���б�������*/
	/**********************************************************/
	V_ulCAP_Data = SF_ADC_VoltageCalc(V_ulCAP_Data);
	V_ulCAP_Data <<= 1;					/*Ӳ����·�й�*/
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
///*����ԭ��:void InF_ExecuteClr_RTCBatt(void)
///*��������:�������ʱ������ʱ�ӵ�ع��ϱ�־�Ĵ���
///*�������:
///*���������
///*���ز���:��
///*����ʱ����
///*��ע:
///*����˵����
///************************************************************************///
void InF_ExecuteClr_RTCBatt(void)
{
	uchar8 V_ucBuffer[16];
	ushort16 V_len, V_usDataEncode;

	Str_RTCBATT.HStatus = C_BATT_OK;
	Str_RTCBATT.Timer = 0;

	///*�������ʷ״̬(�������)д���ݲ�*///
	InF_Write_Data(C_Msg_BatteryVoltagleMetering,CCloc_Batt_LowState,&Str_RTCBATT.HStatus,CLCloc_Batt_LowState,C_W_SafeFlag);

	///*�������ݲ�ʱ�ӵ�ع���״̬��־�����ϻ����������ȴ����ݲ����ˢ�º���д*///
	V_len = CLMeter_Work_State1;
	InF_Read_Data(CMeter_Work_State1,&V_ucBuffer[0],&V_len, &V_usDataEncode);

	V_ucBuffer[0] &= ~C_RTCBattERR_MeterWorkState;

	InF_Write_Data(C_Msg_Dispatch,CMeter_Work_State1,&V_ucBuffer[0],CLMeter_Work_State1,C_W_SafeFlag);
	///*ȡ��ʱ�ӵ�ر���:����ǰ���Ƿ񱨾�,ֱ��ȡ��///
		///*ʱ�ӵ�ز���ʾ*///
	V_ucBuffer[0] = Pt_DisplayStatus;
	V_ucBuffer[1] = C_RTCBatterySign|C_NotDisplay;
	V_ucBuffer[2] = 0xFF;
	V_ucBuffer[3] = 0xFF;
	///*С��������˸*///
	V_ucBuffer[4] = Pt_DisplayStatus;
	V_ucBuffer[5] = C_AlarmSign|C_NotDisplay;
	V_ucBuffer[6] = 0xFF;
	V_ucBuffer[7] = 0xFF;
	///*���ⲻ����*///
	V_ucBuffer[8] = Pt_DisplayStatus;
	V_ucBuffer[9] = C_BackLED|C_NotDisplay;
	V_ucBuffer[10] = 0xFF;
	V_ucBuffer[11] = 0xFF;
	///*�����̵��������*///
	V_ucBuffer[12] = Pt_DisplayStatus;
	V_ucBuffer[13] = C_WarnOutPut|C_NotDisplay;
	V_ucBuffer[14] = 0xFF;
	V_ucBuffer[15] = 0xFF;
	ADC_SendMessage(C_Msg_Display,V_ucBuffer,(Pt_DisplayStatus_Len+1)*4);
}


///************************************************************************///
///*����ԭ��:void InF_ExecuteClr_WakeUpBatt(void)
///*��������:�������ʱ������ͣ�糭���ع��ϱ�־�Ĵ���
///*�������:
///*���������
///*���ز���:��
///*����ʱ����
///*��ע:
///*����˵����
///************************************************************************///
void InF_ExecuteClr_WakeUpBatt(void)
{
	uchar8 V_ucBuffer[16];
	ushort16 V_len, V_usDataEncode;

	Str_WAKEUPBATT.HStatus = C_BATT_OK;
	Str_WAKEUPBATT.Timer = 0;

	///*�������ʷ״̬(�������)д���ݲ�*///
	InF_Write_Data(C_Msg_BatteryVoltagleMetering,CReadMeter_Batt_LowState,&Str_WAKEUPBATT.HStatus,CLReadMeter_Batt_LowState,C_W_SafeFlag);
	///*�������ݲ�ͣ�糭���ع���״̬��־�����ϻ����������ȴ����ݲ����ˢ�º���д*///
	V_len = CLMeter_Work_State1;
	InF_Read_Data(CMeter_Work_State1, &V_ucBuffer[0], &V_len, &V_usDataEncode);

	V_ucBuffer[0] &= ~C_WakeUpBattERR_MeterWorkState;

	InF_Write_Data(C_Msg_Dispatch,CMeter_Work_State1,&V_ucBuffer[0],CLMeter_Work_State1,C_W_SafeFlag);
	///*ȡ�����ѵ�ر���:����ǰ���Ƿ񱨾�,ֱ��ȡ��///
	///*���ѵ�ز���ʾ*///
	V_ucBuffer[0] = Pt_DisplayStatus;
	V_ucBuffer[1] = C_PowerBatterySign|C_NotDisplay;
	V_ucBuffer[2] = 0xFF;
	V_ucBuffer[3] = 0xFF;
	///*С��������˸*///
	V_ucBuffer[4] = Pt_DisplayStatus;
	V_ucBuffer[5] = C_AlarmSign|C_NotDisplay;
	V_ucBuffer[6] = 0xFF;
	V_ucBuffer[7] = 0xFF;
	///*���ⲻ����*///
	V_ucBuffer[8] = Pt_DisplayStatus;
	V_ucBuffer[9] = C_BackLED|C_NotDisplay;
	V_ucBuffer[10] = 0xFF;
	V_ucBuffer[11] = 0xFF;
	///*�����̵��������*///
	V_ucBuffer[12] = Pt_DisplayStatus;
	V_ucBuffer[13] = C_WarnOutPut|C_NotDisplay;
	V_ucBuffer[14] = 0xFF;
	V_ucBuffer[15] = 0xFF;
	ADC_SendMessage(C_Msg_Display,V_ucBuffer,(Pt_DisplayStatus_Len+1)*4);
}

///************************************************************************///
///*��������:�ϵ�ʱ�������ݲ���������ʷ״̬,�����������״̬���еĵ��Ƿѹ״̬/����
///*�������:��
///*�������:�����ʷ״̬/�������״̬��1/����
///*���ز���:��
///*����ʱ����
///************************************************************************///
void InF_InitBatt(void)
{
    uchar8 V_ucBuffer[5];
    ushort16 V_Len, V_usDataEncode;

    ///*�������ʱ������*///
	Str_RTCBATT.Timer = 0;
	Str_WAKEUPBATT.Timer = 0;

	///*�����ݲ������ص���ʷ״̬*///
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
	SF_RTCBattSymbol(Str_RTCBATT.HStatus);		///*��ʾ������صķ���*///
	SF_WakeUpBattSymbol(Str_WAKEUPBATT.HStatus);
	SF_BattWarn(C_BattChange);	///*�ϵ��ʼ��,Ĭ��Ϊ���״̬�б仯*///
	/*��������bug:���ͣ��ǰ���Ƿѹ,���ϵ�ǰװ�ϵ��,
	��ʱ��ط��ż����������ʾ,3s��(����ʱ��)����,
	��Ϊ���ϵ�ȫ��,���Դ�bug������,���Ժ���;
	������������̵������ʹ��ʱ,�����̵����ᵼͨ���ٶϿ�,��һ���ݲ���*/

	///**********************************************************///
	///*������ʷ״̬ˢ�����ݲ�ĵ������״̬��*///
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
	///*����΢RTC����
	Temperature_Adc=0;
	GV_ucTime=6;///*�ϵ��ʼ��Ϊ6s��10s�����¶�
	RTC_RT.TempFlag = 0xff;//���²������


	SF_ADC_Set(C_ADC_Iint);
}
///************************************************************************///
///*��������:ADC���ú���
///*�������:V_ucFlag��C_ADC_Iint��ʼ����־��C_ADC_CmpAndJecADC�¶Ȳ���ʱ�ӵ�У����
///*�������:V_flData:����ƽ��ֵ
///*���ز���:��
///*����ʱ�����ϵ��ʼ����ʱ�ӵ�У
///************************************************************************///
void SF_ADC_Set(uchar8 V_ucFlag)
{
	ulong32 Temp_Data;
	ulong64 V_ulResult;
 	ushort16 v_delaycount;
 	uchar8 i;
	//if(C_PowerOn!=InF_ReadPowerState())///*��ȡ��ǰ״̬,�͹���״̬��ʹ��ʱ��*///
	//{
	///*ʹ��ADCʱ��Դ������Ƶ��512k*///
		RCC->PERCLKCON2 &= (~RCC_PERRCCCON2_ADCCKSEL_RCLP);
		RCC->PERCLKCON2 |= (RCC_PERRCCCON2_ADCCKSEL_RCHFDIV32|RCC_PERRCCCON2_ADCCKE_ON);
	//}
	ANAC->ADCCON = 0;
	ANAC->ADCCON |= ANAC_ADCCON_ADC_VANA_EN_Temp;///*�¶Ȳ���
	ANAC->ADCTRIM = const_adc_TrimT;
	ANAC->ADCIF |= ANAC_ADCIF_ADC_IF_SET;///*���жϱ�־
	ANAC->ADCCON |= ANAC_ADCCON_ADC_EN_ENABLE;///*ʹ��ADC	switch(V_ucFlag)

	Temp_Data = 0;
	for(v_delaycount=0;v_delaycount<C_ADC_Delay;v_delaycount++)
	{
		InF_Delay_2us();
		if( ANAC->ADCIF & ANAC_ADCIF_ADC_IF_SET )
		{
			ANAC->ADCIF |= ANAC_ADCIF_ADC_IF_SET;///*���жϱ�־
			Temp_Data = ANAC->ADCDATA&0x000007FF;
			break;
		}
	}

	switch(V_ucFlag)
	{
		case C_ADC_Iint:
				///*��1��ת��ֵ����
				//0x640ģʽ������ʼ��
				Temp_Data = 0;
				for(v_delaycount=0;v_delaycount<C_ADC_Delay;v_delaycount++)
				{
					InF_Delay_2us();
					if( ANAC->ADCIF & ANAC_ADCIF_ADC_IF_SET )
					{
						ANAC->ADCIF |= ANAC_ADCIF_ADC_IF_SET;///*���жϱ�־
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
				///*��1��ת��ֵ����
				Temp_Data = 0;
				for(v_delaycount=0;v_delaycount<C_ADC_Delay;v_delaycount++)
				{
					InF_Delay_2us();
					if( ANAC->ADCIF & ANAC_ADCIF_ADC_IF_SET )
					{
						ANAC->ADCIF |= ANAC_ADCIF_ADC_IF_SET;///*���жϱ�־
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
