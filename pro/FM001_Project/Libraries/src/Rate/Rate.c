/********************************************************************************************
Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     Rate.c
Version:       V1
Author:        
Date:          2014-3-12
Description:   ���ʡ�ʱ�εȵĴ���
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
#include "Public.h"
#include "Rate.h"
#include "IO.h"

/*******************************************************************************
����ԭ��: void SF_JudgeTimeInterval_RateNum(uchar8 *pV_ucData, uchar8 V_ucTimeIntervalNum)
��������: �ж�ʱ�α��з��ʺţ����ʺŴ������õķ���������Ƿ�ʱ�κ����ʱ�ξ������һ���Ϸ���ִ��
�������: pV_ucDataʱ�α����ݵ�ַ�����42�ֽڣ��� TimeIntervalNumʱ�α����
�������: pV_ucDataʱ�α����������ݵ�ַ������Ϊ�����1���Ϸ���
���ز���: ��
����λ��: Msg_Deal_MultiRates	���ʴ�����
��    ע: TimeIntervalNum�Ϸ��������Ѿ��й���
*******************************************************************************/
void SF_JudgeTimeInterval_RateNum(uchar8 *pV_ucData, uchar8 V_ucTimeIntervalNum)
{
	uchar8 V_ucBuffer[CLFirst_TZone_1PT_Data];
	uchar8 V_uci, V_ucj, V_ucDataoff = 0, V_ucRateNum;
	ushort16 V_usDataLen, V_usDataEncode = 0;
	
	V_usDataLen = CLRate_Num;
	if (InF_Read_Data(CRate_Num, &V_ucRateNum, &V_usDataLen, &V_usDataEncode) != C_OK)
	{
		V_ucRateNum = C_MaxRatesNum;							/*zlj��֮ǰ��BCD��ʽ�����ڶ�������HEX��ʽ*/
	}
	
	PF_CopyDataBytes(pV_ucData, V_ucBuffer, CLFirst_TZone_1PT_Data);
	for (V_uci = 0; V_uci < V_ucTimeIntervalNum; V_uci++)
	{
		if (V_ucBuffer[V_ucDataoff + 2] >  V_ucRateNum)			/*zlj��֮ǰ��ʱ�α��ڵ��ֽڣ�������ʱ�α��ڸ��ֽ�*/
		{
			if (V_ucTimeIntervalNum == 1)						/*ֻ��1��ʱ�α��ҷǷ�*/
			{
				V_ucBuffer[V_ucDataoff + 2] = 1;				/*��1�����ʺţ�Ĭ�ϼ�*/
				break;
			}
			if (V_uci == 0)										/*��1�����ʺžͷǷ�*/
			{
				V_ucBuffer[V_ucDataoff + 2] = 1;				/*��1�����ʺţ�Ĭ�ϼ�*/
				for (V_ucj = 0; V_ucj < (V_ucTimeIntervalNum - 1); V_ucj++)
				{
					PF_CopyDataBytes(&V_ucBuffer[V_ucDataoff], &V_ucBuffer[V_ucDataoff + CL_OneTimeIntervalNum], CL_OneTimeIntervalNum);
					V_ucDataoff += CL_OneTimeIntervalNum;
					if (V_ucDataoff > CLFirst_TZone_1PT_Data)
					{
						break;
					}
				}
				break;
			}
			else
			{
				for (V_ucj = 0; V_ucj < (V_ucTimeIntervalNum - V_uci); V_ucj++)
				{
					PF_CopyDataBytes(&V_ucBuffer[V_ucDataoff - CL_OneTimeIntervalNum], &V_ucBuffer[V_ucDataoff + CL_OneTimeIntervalNum * V_ucj], CL_OneTimeIntervalNum);
				}
				break;
			}
		}
		else
		{
			V_ucDataoff += CL_OneTimeIntervalNum;
			if (V_ucDataoff > CLFirst_TZone_1PT_Data)
			{
				break;
			}
		}
	}
	PF_CopyDataBytes(V_ucBuffer, pV_ucData, CLFirst_TZone_1PT_Data);

}

/*******************************************************************************
����ԭ��: void InF_MultiRates_ParseMessageMsg_Deal_MultiRates (Str_Msg_Parameter *pStr_Msg)
��������: �����жϴ�����
�������: �ж���Ϣ�����ṹ��pStr_Msg�еĲ������ṹ���ʽ���£�
         SourceAddr ΪMsg_Communication�����ʾͨ��ģ�鴥����ΪMsg_Dispatch��������Ϣ�ţ���
         ���ʾÿ���ӵ��ȴ�����ΪC_Msg_Deal_MultiRates��ʾ��ʼ�����ã����ִ����������һ�£�
�������: ��
���ز���: ��
����λ��: ��ʼ����ÿ���ӵ��Ⱥ�ͨ��ģ�鴥��
��    ע: 
*******************************************************************************/
void InF_MultiRates_ParseMessage(Str_Msg_Parameter *pStr_Msg)
{
	uchar8 V_ucTimeInterval = 1;							/*ʱ��*/
	uchar8 V_ucRates = 0;									/*���ʺ�*/
	ushort16 V_usLength, V_usDataEncode = 0;
	uchar8 V_ucTimeZoneNum;									/*ʱ����*/
	uchar8 V_ucTimeIntervalNum;								/*ʱ�α���*/
	uchar8 V_ucDaySwitchNum;								/*��ʱ����*/
	uchar8 V_ucRatesNum;									/*������*/
	uchar8 V_ucHolidayNum;									/*����������*/
	uchar8 V_ucDisStutas_Char1;								/*������1�Т٢�����*/
	uchar8 V_ucMeterRunChar1;								/*�������������1����*/
	uchar8 V_ucCurrentTime[CLDate_Week_Time];				/*��ǰʱ�仺��*/
	uchar8 V_ucDataTemp[CLHolidy_PT_TableFF];				/*���ݻ�����*/
	ulong32 V_ulDataCode;
	uchar8 V_uci;
	uchar8 V_ucWeekTemp;									/*����*/
	uchar8 V_ucRestDayTemp;									/*������������*/
	uchar8 V_ucRestTimeIntervalTemp;						/*�����ղ�����ʱ�α��*/
	uchar8 V_ucWrSafeFlag = C_W_SafeFlag_1;
	uchar8 V_ucDisTemp[4], V_ucDemTemp[2],V_ucEneTemp;		/*��Ϣ��������*/
	uchar8 V_ucTimeChangeFlag = C_TimeNoChange;				/*ʱ��Ͷ�б�ʶĬ��û����Ͷ��*/
	uchar8 V_ucStepStatus = C_Valid, V_ucCurrentStepData[CLCurrent_Ladder_Table];
	uchar8 V_ucA[3], V_ucB[3];								/*zlj���������ڱȽ�ʱ��ʱ�ݴ棬��Ϊ����ʱ��ʱ��֮��Ĵ洢�����֮ǰ���෴���Ƚ�ʱ��ʱ�赹��*/
	uchar8 V_returnFlag;
	uchar8 V_ucGotoFlag = C_Error;
	
	if ( SF_ParseMessage_MultiRates(pStr_Msg) == C_Error )	/*��Ϣ��������,ֱ�ӷ���*/
	{
		SV_ucPowerStatus = C_PowerOnPeriod;					/*�˳�ǰ�õ��Ϊ�е�״̬*/
		return;
	}
    
    /*************************����ǰ������***************************/	
    V_usLength = CLRate_Num;
	if (InF_Read_Data(CRate_Num, &V_ucRatesNum, &V_usLength, &V_usDataEncode) != C_OK)
	{
		V_ucRatesNum = C_MaxRatesNum;				
	}
    
	if (C_Meter_Type == C_L_SmartMeter)
	{	
		V_usLength = CLCurrent_Ladder_Table;
		InF_Read_Data(CCurrent_Ladder_Table, V_ucCurrentStepData, &V_usLength, &V_usDataEncode);				/*����ǰ�׽�������*/

		V_ucStepStatus = PF_Is_Buf_AllFixedData(V_ucCurrentStepData, 0x00, CLCurrent_Ladder_Table_LadNum);		/*�жϽ���ֵ�Ƿ�Ϊȫ0,zlj���ù�������*/
	}
    
	if (*(pStr_Msg->Parameter) == Pt_ParaMetersChange)
	{
		SF_ParaChangeProcess_MultiRates(V_ucStepStatus, V_ucRatesNum);					/*���������ı�ʱ���Ĵ���*/
	}
	V_usLength = CL1And2Display;
	InF_Read_Data(C1And2Display, &V_ucMeterRunChar1, &V_usLength, &V_usDataEncode);		/*��������1*/
	
	if (V_ucMeterRunChar1 == 0x01)														/*�٢ڱ�ʾ���ʵ��*/
	{
		V_ucDisStutas_Char1 = C_DisplayRate;
	}
	else			    /*�٢ڱ�ʾʱ�α�����*/
	{
		V_ucDisStutas_Char1 = C_DisplayTimeInterval;
	}
	V_usLength = CLDate_Time;
	if (InF_Read_Data(CDate_Time, V_ucCurrentTime, &V_usLength, &V_usDataEncode) != C_OK)			/*����ǰʱ��,���λΪ��,7�ֽ�*/
	{
		SV_ucPowerStatus = C_PowerOnPeriod;															/*�˳�ǰ�õ��Ϊ�е�״̬*/
		return;		/*��ʱ�䲻�ɹ�,ֱ���˳�*/
	}
    
/*************************�����������ж�***************************/	
	if (C_Meter_Type == C_L_SmartMeter)																/*���ر�Ŵ�����ʵ������ݵ��*/
	{
        if (V_ucRatesNum != 0)
        {
            SF_JudgeRateSwitch_MultiRates(V_ucDisStutas_Char1, V_ucCurrentTime);					/*���ʵ���ж�,��ǰʱ��ӷֿ�ʼ*/
        }
        
		SF_JudgeStepSwitch_MultiRates(V_ucCurrentTime, V_ucCurrentStepData, V_ucStepStatus);		/*���ݵ���ж�*/
	}
    
    if (V_ucRatesNum != 0)
    {
        SF_JudgeTimeZoneSwitch_MultiRates(V_ucCurrentTime, &V_ucTimeChangeFlag);						        /*ʱ���������ж�*/
	
        SF_JudgeTimeIntervalSwitch_MultiRates(V_ucDisStutas_Char1, V_ucCurrentTime, &V_ucTimeChangeFlag);		/*ʱ�α������ж�*/

    /*************************���ݺϷ����ж�***************************/	
        V_usLength = CLYear_Zone_Num;
        V_returnFlag = InF_Read_Data(CYear_Zone_Num, &V_ucTimeZoneNum, &V_usLength, &V_usDataEncode);			/*��ʱ����*/
        if ( (V_returnFlag != C_OK) || (V_ucTimeZoneNum == 0) || (V_ucTimeZoneNum > C_MaxYearTZNum) )			/*�Ƿ�Ĭ��Ϊ1*/
        {
            V_ucTimeZoneNum = 1;
        }
        
        V_usLength = CLDay_Table_Num;
        V_returnFlag = InF_Read_Data(CDay_Table_Num, &V_ucTimeIntervalNum, &V_usLength, &V_usDataEncode);       /*��ʱ�α���*/
        if ( (V_returnFlag != C_OK) || (V_ucTimeIntervalNum == 0) || (V_ucTimeIntervalNum > C_MaxDayPTTabNum) )	/*�Ƿ�Ĭ��Ϊ1*/
        {
            V_ucTimeIntervalNum = 1;
        }
        
        V_usLength = CLDay_Time_Num;
        V_returnFlag = InF_Read_Data(CDay_Time_Num, &V_ucDaySwitchNum, &V_usLength, &V_usDataEncode);			/*��ʱ����*/
        if ( (V_returnFlag != C_OK) || (V_ucDaySwitchNum == 0) || (V_ucDaySwitchNum > C_MaxDayPTNum) )			/*�Ƿ�Ĭ��Ϊ1*/
        {
            V_ucDaySwitchNum = 1;
        }
        
        V_usLength = CLHoliday_Num;							/*zlj���ȸ�Ϊ1�ֽ�*/
        V_returnFlag = InF_Read_Data(CHoliday_Num, &V_ucHolidayNum, &V_usLength, &V_usDataEncode);	/*������������*/

        if ( (V_returnFlag != C_OK) || (V_ucHolidayNum > C_MaxHolidayNum) )							/*�Ƿ�Ĭ��Ϊ1*/
        {
            V_ucHolidayNum = 0;
        }
        
    /****************************�ڼ����ж�**********************************/
        if (V_ucHolidayNum != 0)		/*zlj֮ǰ���254���ڼ��գ��޷�һ�δ����꣬�ֶδ���ģ����ڸ�Ϊ���20���ڼ��գ�����һ�δ�����*/
        {
            V_usLength = CLHolidy_PT_TableFF;
            if (InF_Read_Data(CHolidy_PT_TableFF, V_ucDataTemp, &V_usLength, &V_usDataEncode) == C_OK)
            {
                for (V_uci = 0; V_uci < V_ucHolidayNum; V_uci++)
                {
                    if ( (V_ucDataTemp[V_uci * CLHolidy_PT_Table1 + 4] == 0xFF)
                      && (V_ucDataTemp[V_uci * CLHolidy_PT_Table1 + 3] == 0xFF)
                      && (V_ucDataTemp[V_uci * CLHolidy_PT_Table1 + 1] != 0xFF) )               /*����Ч,Ϊ��ǰ��*//*zlj��Ϊ�����ڵ��ֽڣ���ʱ�α���ڸ��ֽ�*/ 
                    {
                        V_ucDataTemp[V_uci * CLHolidy_PT_Table1 + 4] = V_ucCurrentTime[6];		/*���õ�ǰ���ڸ�ֵ*/
                        V_ucDataTemp[V_uci * CLHolidy_PT_Table1 + 3] = V_ucCurrentTime[5];
                        
                        if (V_ucDataTemp[V_uci * CLHolidy_PT_Table1 + 2] == 0xFF)				/*����Ч������Ч,����Ч*/
                        {
                            V_ucDataTemp[V_uci * CLHolidy_PT_Table1 + 2] = V_ucCurrentTime[4];
                        }
                    }
                    if (PF_Campare_Data( (V_ucDataTemp + V_uci * CLHolidy_PT_Table1 + 1), &V_ucCurrentTime[C_DayStart], (CLHolidy_PT_Table1 - 1 - 1) ) == C_Equal)	/*�жϵ����Ƿ�ڼ���*/ /*ȥ����ʱ�α�ź���*/
                    {
                        if ( (V_ucDataTemp[V_uci * CLHolidy_PT_Table1 + 5] > 0) && (V_ucDataTemp[V_uci * CLHolidy_PT_Table1 + 5] <= V_ucTimeIntervalNum) )			/*�жϲ��õ�ʱ�α���Ƿ���Ч*/
                        {
                            V_ucTimeInterval = V_ucDataTemp[V_uci * CLHolidy_PT_Table1 + 5];
                            V_ucGotoFlag = C_OK;
                            /*goto Judge_TimeInterval;*/		/*����ʱ�α��ж�*/
                        }
                    }
                }
            }
        }
        
    /****************************�������ж�**********************************/
        if (V_ucGotoFlag != C_OK)
        {
            V_ucWeekTemp = PF_WeekCompute(V_ucCurrentTime);
            V_usLength = CLWeek_RestDay;
            if (InF_Read_Data(CWeek_RestDay, &V_ucRestDayTemp, &V_usLength, &V_usDataEncode) == C_OK)				/*��������������*/
            {
                if ( ( (V_ucRestDayTemp >> V_ucWeekTemp) & 0x01) == 0)												/*��ʾ����Ϊ������*/
                {
                    V_usLength = CLWeek_RestDay_DTable;
                    if (InF_Read_Data(CWeek_RestDay_DTable, &V_ucRestTimeIntervalTemp, &V_usLength, &V_usDataEncode) == C_OK)
                    {
                        if ( (V_ucRestTimeIntervalTemp > 0) && (V_ucRestTimeIntervalTemp <= V_ucTimeIntervalNum) )	/*�жϲ��õ�ʱ�α���Ƿ���Ч*/
                        {
                            V_ucTimeInterval = V_ucRestTimeIntervalTemp;
                            /*goto Judge_TimeInterval;*/															/*����ʱ�α��ж�*/
                            V_ucGotoFlag = C_OK;
                        }
                    }
                }
            }
        }
    /****************************ʱ���ж�**********************************/
        if (V_ucGotoFlag != C_OK)
        {
            V_usLength = CLFirst_TZone_Data;								/*��������ݳ���*/

            InF_Read_Data(CFirst_TZone_Data, V_ucDataTemp, &V_usLength, &V_usDataEncode);

            /*�ж������Ƿ�Ϊȫ0*/
            memset(&V_ucDataTemp[60], 0x00, 3);
            for (V_uci = (V_ucTimeZoneNum - 1); V_uci > 0; V_uci--)			/*zlj�ҳ���Чʱ�����ĸ���*/
            {
                if ( (PF_Campare_Data(&V_ucDataTemp[60], &V_ucDataTemp[V_uci * 3], 3) == C_Equal)
                  || (PF_Campare_Data(&V_ucDataTemp[V_uci * 3], &V_ucDataTemp[(V_uci - 1) * 3], 2) == C_Equal) )	/*zlj�³����Ϊ���ڵ��ֽڣ���ʱ�α���ڸ��ֽ�*/
                {
                    V_ucTimeZoneNum--;
                }
                else
                {
                    break;
                }
            }

            /*���ݵ�ǰʱ���ж�����ʱ�α�*/
            SF_TimeZoneSequence(V_ucDataTemp, V_ucTimeZoneNum);										/*��ʱ���������������*/
            if ( (V_ucTimeZoneNum > 0) && (V_ucTimeZoneNum <= C_MaxYearTZNum) )						/*����ʱ�����Ϸ����ж�*/
            {
                PF_OneDataReversed(&V_ucDataTemp[0], &V_ucA[0], 2);									/*zlj�³����Ϊ���ڵ��ֽڣ����ڸ��ֽڣ������赹��*/
                PF_OneDataReversed(&V_ucDataTemp[(V_ucTimeZoneNum - 1 ) * 3], &V_ucB[0], 2);

                if ( (PF_Campare_Data(&V_ucCurrentTime[C_Day], &V_ucA[0], 2) == C_LessThan)
                  || (PF_Campare_Data(&V_ucCurrentTime[C_Day], &V_ucB[0], 2) != C_LessThan) )
                {
                    V_ucTimeInterval = V_ucDataTemp[(V_ucTimeZoneNum - 1 ) * 3 + 2];				/*��ֵ��ʱʱ�α��*/
                }
                else
                {
                    for (V_uci = 0; V_uci < (V_ucTimeZoneNum - 1); V_uci++)							/*ѭ���жϵ�ǰ���ڵڼ���ʱ��*/
                    {
                        PF_OneDataReversed(&V_ucDataTemp[V_uci * 3], &V_ucA[0], 2);					/*zlj��Ϊ���ڵ��ֽڣ����ڸ��ֽ�*/
                        PF_OneDataReversed(&V_ucDataTemp[(V_uci + 1) * 3], &V_ucB[0], 2);
                        if ( (PF_Campare_Data(&V_ucCurrentTime[C_Day], &V_ucA[0], 2) != C_LessThan)
                          && (PF_Campare_Data(&V_ucCurrentTime[C_Day], &V_ucB[0], 2) == C_LessThan) )
                        {
                            V_ucTimeInterval = V_ucDataTemp[V_uci * 3 + 2];							/*��ֵ��ʱʱ�α��*/
                            break;
                        }
                    }
                }
            }
            if ( (V_ucTimeInterval == 0) || (V_ucTimeInterval > V_ucTimeIntervalNum) )				/*ʱ�α�Ƿ�,Ĭ��Ϊ1*/
            {
                V_ucTimeInterval = 1;
            }	
        }
    /****************************ʱ���ж�**********************************/
    /*Judge_TimeInterval:*/
        V_ucWrSafeFlag |= C_W_SafeFlag_2;
        
        V_usLength = CLFirst_TZone_1PT_Data;				/*��������ݳ���*/
        
        V_ulDataCode = (CFirst_TZone_1PT_Data & 0xFFFFFF00);
        V_ulDataCode = V_ulDataCode | V_ucTimeInterval;		/*������ʱʱ�α�Ŷ�ȡ����*/
            
        InF_Read_Data(V_ulDataCode, V_ucDataTemp, &V_usLength, &V_usDataEncode);
        
        if (SV_ucTimeIntSetStatus != V_ucTimeInterval)		/*�ж�ʱ�α��Ƿ��л�*/
        {
            SV_ucTimeIntSetStatus = V_ucTimeInterval;
            
            V_ucTimeChangeFlag = C_TimeChange;				/*��ʱ��Ͷ����Ч*/
        }
        /*�ж������Ƿ�Ϊȫ0*/
        memset(&V_ucDataTemp[60], 0x00, 3);
        for (V_uci = (V_ucDaySwitchNum - 1); V_uci > 0; V_uci--)
        {
            if ( (PF_Campare_Data(&V_ucDataTemp[60], &V_ucDataTemp[V_uci * 3], 3) == C_Equal)
              || (PF_Campare_Data(&V_ucDataTemp[V_uci * 3], &V_ucDataTemp[(V_uci - 1) * 3], 2) == C_Equal) )	/*zlj�³���ʱ�ڵ��ֽڣ����ʺ��ڸ��ֽ�*/
            {
                V_ucDaySwitchNum--;
            }
            else
            {
                break;
            }
        }
        SF_JudgeTimeInterval_RateNum(V_ucDataTemp, V_ucDaySwitchNum);
        
        /*���ݵ�ǰʱ���ж�����ʱ��*/
        if ( (V_ucDaySwitchNum > 0) && (V_ucDaySwitchNum <= C_MaxDayPTNum) )			/*����ʱ�����Ϸ����ж�*/
        {
            PF_OneDataReversed(&V_ucDataTemp[0], &V_ucA[0], 2);							/*zlj�³���ʱ�ڵ��ֽڣ����ʺ��ڸ��ֽڣ������Ϊ���ڵ��ֽڣ�ʱ�ڸ��ֽ�*/
            PF_OneDataReversed(&V_ucDataTemp[(V_ucDaySwitchNum - 1 ) * 3], &V_ucB[0], 2);
            
            if ( (PF_Campare_Data(&V_ucCurrentTime[C_Minute], &V_ucA[0], 2) == C_LessThan)
              || (PF_Campare_Data(&V_ucCurrentTime[C_Minute], &V_ucB[0], 2) != C_LessThan) )
            {
                V_ucRates = V_ucDataTemp[(V_ucDaySwitchNum - 1) * 3 + 2];				/*��ֵ��ʱ���ʺ�*/
                
                if (SV_ucTimeIntervalStatus != (V_uci + 1) )
                {	
                    SV_ucTimeIntervalStatus = (V_uci + 1);								/*��ֵ�ڲ���̬��������ʱ������ͬ*/
                    
                    V_ucTimeChangeFlag = C_TimeChange;									/*��ʱ��Ͷ����Ч*/
                }
            }
            else
            {
                for (V_uci = 0; V_uci < (V_ucDaySwitchNum - 1); V_uci++)				/*ѭ���жϵ�ǰ�ķ��ʺ�*/
                {
                    PF_OneDataReversed(&V_ucDataTemp[V_uci * 3], &V_ucA[0], 2);			/*zlj��Ϊ���ڵ��ֽڣ�ʱ�ڸ��ֽ�*/
                    PF_OneDataReversed(&V_ucDataTemp[(V_uci + 1) * 3], &V_ucB[0], 2);
            
                    if ( (PF_Campare_Data(&V_ucCurrentTime[C_Minute], &V_ucA[0], 2) != C_LessThan)
                      && (PF_Campare_Data(&V_ucCurrentTime[C_Minute], &V_ucB[0], 2) == C_LessThan) )
                    {
                        V_ucRates = V_ucDataTemp[V_uci * 3 + 2];						/*��ֵ��ʱ���ʺ�*/
                        
                        if (SV_ucTimeIntervalStatus != (V_uci + 1) )					/*(V_uci+1)��ʾ������ʱ�κ�*/
                        {	
                            SV_ucTimeIntervalStatus = (V_uci + 1);						/*��ֵ�ڲ���̬����-ʱ�κ�*/
                            
                            V_ucTimeChangeFlag = C_TimeChange;							/*��ʱ��Ͷ����Ч*/
                        }
                        break;
                    }
                }
            }
        }
        
        if ( (V_ucRates == 0) || (V_ucRates > V_ucRatesNum) )	/*���ʺŷǷ�,Ĭ��Ϊ��*/
        {
            V_ucRates = 1;
        }
    }

    if (C_Meter_Type == C_L_SmartMeter)						/*���ر�Ŵ�����ʵ��*/
    {
        /*��Ϣ��������-����*/
        V_ucEneTemp = Pt_RatePrice;
        SF_MsgProcess(&V_ucEneTemp, Pt_RatePrice_Len + 1, C_Msg_EnergyMetering);
    }

	V_usLength = CLCurr_Rate_No;
	V_returnFlag = InF_Read_Data(CCurr_Rate_No, V_ucDataTemp, &V_usLength, &V_usDataEncode);					/*��ȡ��ǰ����*/
	if (V_returnFlag != C_OK)
	{
		V_ucDataTemp[0] = 1;
	}
	if (V_ucRates != V_ucDataTemp[0])						/*���ʷ����仯*/
	{
		V_ucWrSafeFlag = C_W_SafeFlag;
		
		InF_Write_Data(C_Msg_Deal_MultiRates, CCurr_Rate_No, &V_ucRates, CLCurr_Rate_No, V_ucWrSafeFlag);		/*д��ǰ����*/
		/*��Ϣ��������-��ʾ*/
		V_ucDisTemp[0] = Pt_DisplayStatus;
		if (V_ucRates == 0)
		{
			V_ucDisTemp[1] = C_TSign | C_NotDisplay;			/*����ʾ����T*/
		}
		else
		{
			V_ucDisTemp[1] = C_TSign | C_AlwaysDisplay;			/*��ʾ����T*/
		}
		V_ucDisTemp[2] = 0xFF;
		V_ucDisTemp[3] = 0xFF;
		SF_MsgProcess(V_ucDisTemp, (Pt_DisplayStatus_Len + 1), C_Msg_Display);
        
		/*��Ϣ��������-����*/
		V_ucDemTemp[0] = Pt_DemandStatus;
		V_ucDemTemp[1] = C_RatesChanged;
		SF_MsgProcess(V_ucDemTemp, (Pt_DemandStatus_Len + 1), C_Msg_DemandMetering);
	}
    
	if (V_ucTimeChangeFlag == C_TimeChange)					/*ʱ�η���Ͷ��*/
	{
		InF_MultiFunctionOutput(C_RatePulse);				/*����IO�����ӿں���,����ʱ��Ͷ���ź�*/
	}
	SV_ucPowerStatus = C_PowerOnPeriod;
}


/*******************************************************************************
����ԭ��: InF_Deal_MultiRates(void)
��������: �����жϳ�ʼ������
�������: ��
�������: ��
���ز���: ��
����λ��: ����ʼ������
��    ע: 
*******************************************************************************/
void InF_Deal_MultiRates(void)
{
	uchar8 V_ucMeterRunChar1;			            /*�������������1����*/
	uchar8 V_ucReturnTemp, V_ucDataTemp, V_ucDemTemp[2];
	uchar8 V_ucRatesNum;
	uchar8 V_ucWrSafeFlag = C_W_SafeFlag_1;
	uchar8 V_ucRateNum_Msg[4];			            /*��ʾ��������*/
	uchar8 V_ucRatePr_Msg[8];
	uchar8 V_ucStep_Msg[8];
	uchar8 V_ucTimeInt_Msg[8];
	uchar8 V_ucRateTemp = Pt_Initialization;		/*�����жϲ�������*/
	uchar8 V_ucCurrentStepData[CLCurrent_Ladder_Table];
	uchar8 V_ucMeterRunStatus3[5];					/*�������״̬��3����*/
	ushort16 V_usLength, V_usDataEncode = 0;
    
	SV_ucPowerStatus = C_PowerUpEdge;				/*�ϵ��ʼ��ʱ,��Ϊ�ϵ��ر�־*/
	
	V_usLength = CLMeter_Work_State3;
	InF_Read_Data(CMeter_Work_State3, V_ucMeterRunStatus3, &V_usLength, &V_usDataEncode);	/*��״̬��3*/
	
	V_usLength = CL1And2Display;
	InF_Read_Data(C1And2Display, &V_ucMeterRunChar1, &V_usLength, &V_usDataEncode);			/*��������1*/
	
	V_ucWrSafeFlag |= C_W_SafeFlag_2;	
	V_ucMeterRunStatus3[C_LowByte] &= C_FirstTimeZone;										/*״̬��3Ĭ�ϵ�һ��*/
	V_ucMeterRunStatus3[C_LowByte] &= C_FirstTimeInterval;
	V_ucWrSafeFlag |= C_W_SafeFlag_3;
	InF_Write_Data(C_Msg_Deal_MultiRates, CMeter_Work_State3, V_ucMeterRunStatus3, CLMeter_Work_State3, V_ucWrSafeFlag);		/*д״̬��3*/

	V_usLength = CLCurr_Rate_No;
	V_ucReturnTemp = InF_Read_Data(CCurr_Rate_No, &V_ucDataTemp, &V_usLength, &V_usDataEncode);									/*��ȡ��ǰ����*/
	
    V_usLength = CLRate_Num;
	if (InF_Read_Data(CRate_Num, &V_ucRatesNum, &V_usLength, &V_usDataEncode) != C_OK)
	{
		V_ucRatesNum = C_MaxRatesNum;				
	}
	
	if ( (V_ucReturnTemp != C_OK) || (V_ucDataTemp > V_ucRatesNum) )
	{
		V_ucDataTemp = 1;																	/*�����ݴ���������ݲ��Ϸ���Ĭ��Ϊ��*/
		
		V_ucWrSafeFlag = C_W_SafeFlag;
		InF_Write_Data(C_Msg_Deal_MultiRates, CCurr_Rate_No, &V_ucDataTemp, CLCurr_Rate_No, V_ucWrSafeFlag);					/*д��ǰ����*/
	}

    V_ucRateNum_Msg[0] = Pt_DisplayStatus;
    if (V_ucRatesNum == 0)  /*ȥ���ʣ�����ʾT*/
    {
        V_ucRateNum_Msg[1] = C_TSign | C_NotDisplay;										/*��ֵ��ʾ��ʶ*/
    }
    else
    {
        V_ucRateNum_Msg[1] = C_TSign | C_AlwaysDisplay;										/*��ֵ��ʾ��ʶ*/

    }
	V_ucRateNum_Msg[2] = 0xFF;
    V_ucRateNum_Msg[3] = 0xFF;
	SF_MsgProcess(V_ucRateNum_Msg, Pt_DisplayStatus_Len + 1, C_Msg_Display);				/*�������ʺ���ʾ��Ϣ*/
	
	if (C_Meter_Type == C_L_SmartMeter)														/*���ر�Ŵ�����ʺͽ�����ʾ*/
	{
		V_usLength = CLCurrent_Ladder_Table;
		InF_Read_Data(CCurrent_Ladder_Table, V_ucCurrentStepData, &V_usLength, &V_usDataEncode);								/*����ǰ�׽�������*/
		
		if (PF_Is_Buf_AllFixedData(V_ucCurrentStepData, 0x00, CLCurrent_Ladder_Table_LadNum) != C_OK)							/*����ֵ��ȫΪ0�ŵ������ݷ���,zlj���ù�������*/
		{
			SF_Deal12dig(CChange_Ladder, V_ucStep_Msg);
			SF_SendMsgToDisplay(C_CurrentStep, C_BakStep, V_ucStep_Msg[1], V_ucStep_Msg[5], 2);
		}
		
		if (V_ucMeterRunChar1 == 0x01)					/*�٢ڱ�ʾ���ʵ��*/
		{
            if (V_ucRatesNum == 0)                      /*ȥ���ʣ�����ʾ�٢�*/
            {
                V_ucRatePr_Msg[1] = C_NotDisplay;	    /*��ǰ�׷��ʷ���*/
                V_ucRatePr_Msg[5] = C_NotDisplay;		/*�����׷��ʷ���*/
            }
            else
            {
				SF_Deal12dig(CChange_Rate, V_ucRatePr_Msg);
            }
			SF_SendMsgToDisplay(C_TimeTable1Sign, C_TimeTable2Sign, V_ucRatePr_Msg[1], V_ucRatePr_Msg[5], 2);
		}	
	}
    
	if (V_ucMeterRunChar1 == 0)							/*�٢ڱ�ʾʱ������*/
	{
        if (V_ucRatesNum == 0)                          /*ȥ���ʣ�����ʾ�٢�*/
        {
            V_ucRatePr_Msg[1] = C_NotDisplay;	        /*��ǰ�׷��ʷ���*/
            V_ucRatePr_Msg[5] = C_NotDisplay;		    /*�����׷��ʷ���*/
        }
        else
        {
			SF_Deal12dig(CChange_PT_Time, V_ucTimeInt_Msg);
        }
		SF_SendMsgToDisplay(C_TimeTable1Sign, C_TimeTable2Sign, V_ucTimeInt_Msg[1], V_ucTimeInt_Msg[5], 2);
	}
	SF_MsgProcess(&V_ucRateTemp, Pt_Initialization_Len + 1, C_Msg_Deal_MultiRates);			    /*���������ж���Ϣ*/
    
	/*�ϵ�������ʼ��ʱ����Ҫ����ģ�鴥����Ϣ*/
	V_ucDemTemp[0] = Pt_DemandStatus;
	V_ucDemTemp[1] = C_RatesChanged;
	SF_MsgProcess(V_ucDemTemp, (Pt_DemandStatus_Len + 1), C_Msg_DemandMetering);
}

/*******************************************************************************
����ԭ��: void  SF_ParaChangeProcess(uchar8 V_ucStepStatus, uchar8 V_ucRatesNum)
��������: ���������仯ʱ���Ĵ���
�������: V_ucStepStatus-����ֵ��Ϊȫ0,ΪC_Valid,����ΪC_Invalid,�����ж��Ƿ����ݷ���
         uchar8 V_ucRatesNum����ǰ������
�������: ��
���ز���: ��
����λ��: ����ģ��
��    ע: 
*******************************************************************************/
void SF_ParaChangeProcess_MultiRates(uchar8 V_ucStepStatus, uchar8 V_ucRatesNum)
{
	ushort16 V_usLength, V_usDataEncode = 0; 
	uchar8 V_ucMeterRunChar1;
	uchar8 V_ucStep_Msg[8], V_ucTimeInt_Msg[8];

    if (V_ucRatesNum == 0)                                      /*ȥ����*/
    {
        V_ucTimeInt_Msg[1] = C_NotDisplay;
        V_ucTimeInt_Msg[5] = C_NotDisplay;
    }
    else
    {
        V_usLength = CL1And2Display;
        InF_Read_Data(C1And2Display, &V_ucMeterRunChar1, &V_usLength, &V_usDataEncode);				/*��������1*/

        if (V_ucMeterRunChar1 == 0)								/*�٢ڱ�ʾʱ������*/
        {
			SF_Deal12dig(CChange_PT_Time, V_ucTimeInt_Msg);  
        }
        else
        {
            if (C_Meter_Type == C_L_SmartMeter)					/*���ر����жϷ��ʵ��*/
            {
				SF_Deal12dig(CChange_Rate, V_ucTimeInt_Msg); 
            }
            else												/*�Ǳ��ر�,��٢�*/
            {
                V_ucTimeInt_Msg[1] = C_NotDisplay;
                V_ucTimeInt_Msg[5] = C_NotDisplay;
            }
        }
    }
	SF_SendMsgToDisplay(C_TimeTable1Sign, C_TimeTable2Sign, V_ucTimeInt_Msg[1], V_ucTimeInt_Msg[5], 2);

	/*���ر�Ŵ��������ʾ*/
	if (C_Meter_Type == C_L_SmartMeter)
	{
		if (V_ucStepStatus != C_OK)
		{
			SF_Deal12dig(CChange_Ladder, V_ucStep_Msg);
		}
		else		/*����ֵȫΪ0,����ʵ������������*/
		{
			V_ucStep_Msg[1] = C_NotDisplay;					/*��ǰ�׽��ݷ���*/
			V_ucStep_Msg[5] = C_NotDisplay;					/*�����׽��ݷ���*/
		}
		SF_SendMsgToDisplay(C_CurrentStep, C_BakStep, V_ucStep_Msg[1], V_ucStep_Msg[5], 2);
	}
}

/*******************************************************************************
����ԭ��: void  SF_JudgeStepSwitch_MultiRates(uchar8 *pV_ucCurrentTime, uchar8 *pV_ucCurrentStepData, uchar8 V_ucStepStatus)
��������: ���ݵ���л��ж�	
�������: pV_ucCurrentTime-��ǰʱ��
         *pV_ucCurrentStepData-��ǰ�׽��������׵�ַ
         V_ucStepStatus-����ֵ��Ϊȫ0,ΪC_Valid,����ΪC_Invalid,�����ж��Ƿ����ݷ���
�������: ��
���ز���: ��
����λ��: ����ģ��
��    ע: 
*******************************************************************************/
void SF_JudgeStepSwitch_MultiRates(uchar8 *pV_ucCurrentTime, uchar8 *pV_ucCurrentStepData, uchar8 V_ucStepStatus)
{
	uchar8 V_ucSwitchTime[CLChange_Ladder];						/*�л�ʱ��*/
	uchar8 V_ucBackupStepData[CLCurrent_Ladder_Table];			/*��ǰ�ͱ��������ݻ�����*/
	ushort16 V_ucStepDataLength = CLCurrent_Ladder_Table;		/*�������ݳ���*/
	uchar8 V_ucSwitchStatus;									/*�л�״̬*/
	uchar8 V_ucWrSafeFlag = C_W_SafeFlag_1;
	uchar8 V_ucDisTemp[10], V_ucReturnFlag = C_OK;
    ushort16 V_usDataEncode = 0;
	
	V_ucSwitchStatus = SF_JudgeSwitchTime_MultiRates(CChange_Ladder, &pV_ucCurrentTime[C_MinStart], V_ucSwitchTime);						/*�ж��Ƿ����л�*/

	if (V_ucSwitchStatus == C_SwitchValid)
	{
		V_ucWrSafeFlag |= C_W_SafeFlag_2;
		/*�������׽�������*/
		if (InF_Read_Data(CBackUp_Ladder_Table, V_ucBackupStepData, &V_ucStepDataLength, &V_usDataEncode) != C_OK)
		{
			if (InF_Read_Data(CBackUp_Ladder_Table, V_ucBackupStepData, &V_ucStepDataLength, &V_usDataEncode) != C_OK)
			{
				V_ucReturnFlag = C_Error;
			}
		}
		if (V_ucReturnFlag == C_OK)								/*�������׳ɹ��ˣ��Ž�����д�뵱ǰ��,��������/�½����л�����*/
		{
			V_ucWrSafeFlag |= C_W_SafeFlag_3;
			InF_Write_Data(C_Msg_Deal_MultiRates, CCurrent_Ladder_Table, V_ucBackupStepData, CLCurrent_Ladder_Table, V_ucWrSafeFlag);		/*������������д�뵱ǰ��*/
			
			SF_StepTypeProcess(pV_ucCurrentStepData + CLCurrent_Ladder_Table_LadNum + CLCurrent_Ladder_Table_LadPri, V_ucBackupStepData + CLBackUp_Ladder_Table_LadNum + CLBackUp_Ladder_Table_LadPri, &V_ucSwitchTime[1]);		/*�ж��������ݽ�������,��������ش���,zlj�궨�����DILenth.h��ĺ궨�壬��ʹ���Լ���������ĺ궨��*/
		}

		InF_FreezeSwitch(CChange_Ladder, pV_ucCurrentTime);		/*���н����л�Լ������*/

		if (PF_Is_Buf_AllFixedData(V_ucBackupStepData, 0x00, CLCurrent_Ladder_Table_LadNum) != C_OK)										/*����ֵ��ȫΪ0�ŵ���ݷ���,zlj���ù�������*/
		{
			V_ucDisTemp[1] = C_AlwaysDisplay;
		}
		else
		{
			V_ucDisTemp[1] = C_NotDisplay;
		}
		SF_SendMsgToDisplay(C_CurrentStep, C_BakStep, V_ucDisTemp[1], C_NotDisplay, 2);
	}
	else if ( (V_ucSwitchStatus == C_SwitchInvalid) && (V_ucStepStatus != C_OK) )
	{
		/*������ǰ�ͱ����׽��ݷ���*/
		SF_SendMsgToDisplay(C_CurrentStep, C_BakStep, C_AlwaysDisplay, C_AlwaysDisplay, 2);
	}
}

/*******************************************************************************
����ԭ��: void  SF_JudgeRateSwitch_MultiRates(uchar8 V_ucDisplayType, uchar8 *pV_ucCurrentTime)
��������: ���ʵ���л��ж�
�������: V_ucDisplayType-Һ���٢ڷ��ŵı�ʾ���壬���ڴ�����ʾʱ�ж�
         pV_ucCurrentTime-��ǰʱ��	
�������: ��
���ز���: ��
����λ��: ����ģ��
��    ע: 
*******************************************************************************/
void SF_JudgeRateSwitch_MultiRates(uchar8 V_ucDisplayType, uchar8 *pV_ucCurrentTime)
{
	uchar8 V_ucSwitchTime[CLChange_Rate];					/*�л�ʱ�仺��*/
	uchar8 V_ucBackupRateData[CLBackUp_RateFF_Price];		/*���������ݻ�����*/
	ushort16 V_usRateDataLength;							/*���ʵ�����ݳ���*/
	uchar8 V_ucSwitchStatus;								/*�л�״̬*/
	uchar8 V_ucWrSafeFlag = C_W_SafeFlag_1;
	uchar8 V_ucReturnFlag = C_Error;
	uchar8 V_uci;
    ushort16 V_usDataEncode = 0;

	V_ucSwitchStatus = SF_JudgeSwitchTime_MultiRates(CChange_Rate, &pV_ucCurrentTime[C_MinStart], V_ucSwitchTime);		/*�ж��Ƿ����л�*/
	
	if (V_ucSwitchStatus == C_SwitchValid)
	{
		V_ucWrSafeFlag |= C_W_SafeFlag_2;
		for (V_uci = 0; V_uci < C_MaxRatesNum; V_uci++)
		{
			V_usRateDataLength = CLBackUp_Rate1_Price;
			if (InF_Read_Data( (CBackUp_Rate1_Price + V_uci * C_RateOADChange_Flag), &V_ucBackupRateData[CLBackUp_Rate1_Price * V_uci], &V_usRateDataLength, &V_usDataEncode) != C_OK)
			{
				break;
			}
		}
		if (V_uci == C_MaxRatesNum)
		{
			V_ucReturnFlag = C_OK;
		}
		
		if (V_ucReturnFlag == C_OK)							/*�������׳ɹ��ˣ��Ž�����д�뵱ǰ��*/
		{
			V_usRateDataLength = CLBackUp_RateFF_Price;
			
			V_ucWrSafeFlag |= C_W_SafeFlag_3;
			InF_Write_Data(C_Msg_Deal_MultiRates, CCurrent_RateFF_Price, V_ucBackupRateData, V_usRateDataLength, V_ucWrSafeFlag);		/*������������д�뵱ǰ��*/
		}
		InF_FreezeSwitch(CChange_Rate, pV_ucCurrentTime);	/*���з����л�Լ������*/

		if (V_ucDisplayType == C_DisplayRate)
		{
			/*������ǰ�׷��ʵ�۷���*/
			SF_SendMsgToDisplay(C_TimeTable1Sign, C_TimeTable2Sign, C_AlwaysDisplay, C_NotDisplay,2);
		}
	}
	else if ( (V_ucSwitchStatus == C_SwitchInvalid) && (V_ucDisplayType == C_DisplayRate) )
	{
			/*������ǰ�׷��ʵ�۷���*/
		SF_SendMsgToDisplay(C_TimeTable1Sign, C_TimeTable2Sign, C_AlwaysDisplay, C_AlwaysDisplay, 2);
	}
}	

/*******************************************************************************
����ԭ��: uchar8  SF_JudgeTimeZoneSwitch_MultiRates(uchar8 *pV_ucCurrentTime, uchar8 *pV_ucChangeFlag)
��������: ʱ�����л��ж�
�������: pV_ucCurrentTime-��ǰʱ��,date_time_s��ʽ
         pV_ucChangeFlag-ʱ��Ͷ�б�ʶ,�����ж��Ƿ������ʱ��Ͷ��		
�������: pV_ucChangeFlag-ʱ��Ͷ�б�ʶ,��ʱ�����л�,����ΪC_TimeChange
���ز���: ��ǰ����ʱ��������  
����λ��: ����ģ��
��    ע: 
*******************************************************************************/
void SF_JudgeTimeZoneSwitch_MultiRates(uchar8 *pV_ucCurrentTime, uchar8 *pV_ucChangeFlag)
{
	uchar8 V_ucSwitchTime[CLChange_TZ_Time];
	uchar8 V_ucSwitchStatus;		/*�л�״̬*/
	uchar8 V_ucWrSafeFlag = C_W_SafeFlag_1;
	ushort16 V_usLength, V_usDataEncode = 0;
	uchar8 V_ucSec_TZone_Data[CLSec_TZone_Data];
	
	
	V_ucSwitchStatus = SF_JudgeSwitchTime_MultiRates(CChange_TZ_Time, &pV_ucCurrentTime[C_MinStart], V_ucSwitchTime);			/*�ж��Ƿ����л�*/
	
	V_ucWrSafeFlag |= C_W_SafeFlag_2;
	
	if (V_ucSwitchStatus == C_SwitchValid)		/*�л���Ч*/
	{
		*pV_ucChangeFlag = C_TimeChange;		/*��ʱ��Ͷ����Ч*/
		V_ucWrSafeFlag |= C_W_SafeFlag_3;
		
		V_usLength = CLSec_TZone_Data;
		if (InF_Read_Data(CSec_TZone_Data, V_ucSec_TZone_Data, &V_usLength, &V_usDataEncode) == C_OK)							/*�����׵�1��ʱ�α�*/
		{
			InF_Write_Data(C_Msg_Deal_MultiRates, CFirst_TZone_Data, V_ucSec_TZone_Data, CLFirst_TZone_Data, V_ucWrSafeFlag);	/*���ǵ�ǰ��*/
			
		}
		InF_FreezeSwitch(CChange_TZ_Time, pV_ucCurrentTime);																	/*����ʱ�����л�Լ������*/
	}
}

/*******************************************************************************
����ԭ��: void SF_JudgeTimeIntervalSwitch_MultiRates(uchar8 V_ucDisplayType, uchar8 *pV_ucCurrentTime, uchar8 *pV_ucChangeFlag)
��������: ʱ�α��л��ж�
�������: V_ucDisplayType-��ǰʱ��,5�ֽ�,��ʽYYMMDDhhmm
         pV_ucCurrentTime-Һ���٢ڷ��ŵı�ʾ���壬���ڴ�����ʾʱ�ж�	
         pV_ucChangeFlag-ʱ��Ͷ�б�ʶ,�����ж��Ƿ������ʱ��Ͷ��	
�������: pV_ucChangeFlag-ʱ��Ͷ�б�ʶ,ʱ�α����л�,����ΪC_TimeChange
���ز���: ��ǰ����ʱ�α�����
����λ��: ����ģ��
��    ע: 
*******************************************************************************/
void SF_JudgeTimeIntervalSwitch_MultiRates(uchar8 V_ucDisplayType, uchar8 *pV_ucCurrentTime, uchar8 *pV_ucChangeFlag)
{
	uchar8 V_ucSwitchTime[CLChange_TZ_Time], V_uci;
	uchar8 V_ucSwitchStatus;		/*�л�״̬*/
	uchar8 V_ucWrSafeFlag = C_W_SafeFlag_1;
	ushort16 V_usLength, V_usDataEncode = 0;
	uchar8 V_ucSec_TZone_PT_Data[CLSec_TZone_1PT_Data];
	

	V_ucSwitchStatus = SF_JudgeSwitchTime_MultiRates(CChange_PT_Time, &pV_ucCurrentTime[C_MinStart], V_ucSwitchTime);									/*�ж��Ƿ����л�*/
	
	V_ucWrSafeFlag |= C_W_SafeFlag_2;
	
	if (V_ucSwitchStatus == C_SwitchValid)							/*�л���Ч*/
	{
		*pV_ucChangeFlag = C_TimeChange;							/*��ʱ��Ͷ����Ч*/
		V_ucWrSafeFlag |= C_W_SafeFlag_3;
		
		for (V_uci = 0; V_uci < C_MaxDayPTTabNum; V_uci++)
		{
			V_usLength = CLSec_TZone_1PT_Data;
			if (InF_Read_Data(CSec_TZone_1PT_Data + V_uci, V_ucSec_TZone_PT_Data, &V_usLength, &V_usDataEncode) == C_OK)								/*�����׵�1��ʱ�α�*/
			{
				InF_Write_Data(C_Msg_Deal_MultiRates, CFirst_TZone_1PT_Data + V_uci, V_ucSec_TZone_PT_Data, CLFirst_TZone_1PT_Data, V_ucWrSafeFlag);	/*���ǵ�ǰ��*/
				
			}
		}

		InF_FreezeSwitch(CChange_PT_Time, pV_ucCurrentTime);		/*����ʱ�α��л�Լ������*/

		if (V_ucDisplayType == C_DisplayTimeInterval)				/*�٢ڱ�ʾʱ�α�*/
		{
			/*����ʱ�α�������Ӧ����ʾ����*/
			SF_SendMsgToDisplay(C_TimeTable2Sign, C_TimeTable2Sign, C_AlwaysDisplay, C_NotDisplay, 2);
		}
	}
	return;
}
/*******************************************************************************
����ԭ��: void SF_StepTypeProcess(uchar8 *pV_ucOldDate, uchar8 *pV_ucNewDate, uchar8 *pV_ucSettlementTime)
��������: ��/�½����л��ж�
�������: pV_ucOldDateָ����ԭִ�е�������������׵�ַ,pV_ucNewDate�����ý��������׵�ַ,
         *pV_ucSettlementTimeʱ���ַ,���ڽ���ʱ��������ģ��,6�ֽ�(������ʱ����)
�������: ��
���ز���: ��
����λ��: ���ڶԵ�ǰ���������޸�ʱ����
��    ע: �����жϵ����ݳ���Ϊ12�ֽ�
          ���ݶ���������������ݵ���Ч���жϣ�������/�½��ݼ��л��Ľ�����Ϣ����
*******************************************************************************/
void SF_StepTypeProcess(uchar8 *pV_ucOldDate, uchar8 *pV_ucNewDate, uchar8 *pV_ucSettlementTime)
{
	uchar8 V_ucOldValidNum = 0;
	uchar8 V_ucNewValidNum = 0;						/*��ԭ/��������Ч����*/
	uchar8 V_uci, V_ucDataTemp[10];
	uchar8 V_ucCurrentTime[CLDate_Week_Time];		/*zlj��Ϊdata_time_s���ݸ�ʽ*/
	uchar8 V_ucA[CLDate_Week_Time];					/*zlj�洢����������ʱ*/
	ushort16 V_usLength, V_usDataEncode = 0;
    
	/*��Ϣ��������*/
	V_ucDataTemp[0] = Pt_StepSwitchFlag;
	if (SV_ucPowerStatus == C_PowerOnPeriod)		/*�е��ڼ�,����Ϊ��ǰʱ��*/
	{
		V_usLength = CLDate_Time;
		if (InF_Read_Data(CDate_Time, V_ucCurrentTime, &V_usLength, &V_usDataEncode) == C_OK)			/*zlj����Ϊ��698OAD��ʱ��*/
		{
			PF_CopyDataBytes(&V_ucCurrentTime[C_MinStart], &V_ucDataTemp[2], (CLDate_Week_Time - 1) );	/*zlj���ĳ�������ʱ��6�ֽ�*/
		}
		else
		{
			PF_CopyDataBytes(pV_ucSettlementTime, &V_ucDataTemp[2], (CLDate_Week_Time - 1) );
		}
	}
	else
	{
		PF_CopyDataBytes(pV_ucSettlementTime, &V_ucDataTemp[2], (CLDate_Week_Time - 1) );
	}

	for (V_uci = 0; V_uci < C_SettlementNum; V_uci ++)                                                  /*�ж����������еĽ�������Ч����*/
	{
		PF_OneDataReversed(pV_ucOldDate + (C_SettlementLength_One * V_uci), &V_ucA[C_HourStart], C_SettlementLength_One);
        
		if (PF_DataTimeActive_698( &V_ucA[C_HourStart], C_HourStart, C_SettlementLength_One) == C_OK)	/*zlj����698��ʽʱ���ж�*/
		{
			V_ucOldValidNum++;
		}
        
		PF_OneDataReversed( (pV_ucNewDate + (C_SettlementLength_One * V_uci) ), &V_ucA[C_HourStart], C_SettlementLength_One);

		if (PF_DataTimeActive_698( &V_ucA[C_HourStart], C_HourStart, C_SettlementLength_One) == C_OK)	/*zlj����698��ʽʱ���ж�*/
		{
			V_ucNewValidNum++;
		}
	}

	if (V_ucOldValidNum != V_ucNewValidNum)
	{
		V_ucDataTemp[1] = C_Step_SetttleChange;
		SF_MsgProcess(V_ucDataTemp, (Pt_StepSwitchFlag_Len + 1), C_Msg_SettleAccounts);
	}
	else
	{
		for (V_uci = CLCurrent_Ladder_Table_LadSett; V_uci > 0; V_uci--)								/*zlj�궨�����DILenth.h��ĺ궨�壬�������Լ���������ĺ궨��*/
		{
			if ( ( (*(pV_ucOldDate + V_uci - 1) == 99) || (*(pV_ucOldDate + V_uci - 1) == 0xFF) )
              && ( (*(pV_ucNewDate + V_uci - 1) == 99) || (*(pV_ucNewDate + V_uci - 1) == 0xFF) ) )		/*�¾ɽ��ݱ������Ϊ99orFF*/  
			{
				continue;
			}
			else if ( (*(pV_ucOldDate + V_uci - 1) ) != (*(pV_ucNewDate + V_uci - 1) ) )		        /*����ֱ�ӷ��ͽ��ݽ��㶳����Ϣ*/
			{
				V_ucDataTemp[1] = C_Step_SetttleChange;
				SF_MsgProcess(V_ucDataTemp, (Pt_StepSwitchFlag_Len + 1), C_Msg_SettleAccounts);
				break;
			}
			else
			{
				;					/*�����ж�*/
			}
		}
	}

#if 0 
	if ( OldValidNum == 0 )			/*ԭ���������Ч*/
	{
		if ( NewValidNum != 0 )		/*�½����������*/
		{
			V_ucDataTemp[1] = C_Step_MToY;
			SF_MsgProcess(V_ucDataTemp, (Pt_StepSwitchFlag_Len + 1), C_Msg_SettleAccounts);
		}
	}
	else							/*ԭ���������Ч*/
	{
		if (NewValidNum == 0)		/*��������½���*/
		{
			V_ucDataTemp[1] = C_Step_YToM;
			SF_MsgProcess(V_ucDataTemp, (Pt_StepSwitchFlag_Len + 1), C_Msg_SettleAccounts);
		}
		else if (OldValidNum == NewValidNum)
		{
			for (i = 0; i < C_SettlementLength_T; i ++)
			{
				if (*(OldDate + i) != *(NewDate + i) )		/*��ǰ������������ݲ�һ��,��������������*/
				{
					V_ucDataTemp[1] = C_Step_YToY;
					SF_MsgProcess(V_ucDataTemp, Pt_StepSwitchFlag_Len + 1, C_Msg_SettleAccounts);
					break;
				}
			}
		}
		else
		{
			V_ucDataTemp[1] = C_Step_YToY;
			SF_MsgProcess(V_ucDataTemp, Pt_StepSwitchFlag_Len + 1, C_Msg_SettleAccounts);
		}
	}	
#endif
	
}

/*******************************************************************************
����ԭ��: uchar8 SF_JudgeSwitchTime_MultiRates(ulong32 V_ulSwitchTimeID, uchar8 *pV_ucCurrentTime, uchar8 *pV_ucSwitchTimeTemp)
��������: ���л�ʱ��͵�ǰʱ��Ƚ�,�ж��Ƿ����л�	
�������: V_ulSwitchTimeID �C�����ж��л�ʱ��ı�ʶ��,pV_ucCurrentTime �C��ǰʱ���׵�ַ,
         *pV_ucSwitchTimeTemp-�Ĵ����׵�ַ�����ڴ���������	
�������: *pV_ucSwitchTimeTemp-��������л�ʱ�䣬��������ͽ���ģ��
���ز���: C_SwitchInvalid�C�л���Ч,C_SwitchValid�C�л���Ч
����λ��: SF_JudgeStepSwitch_MultiRates/SF_JudgeStepSwitch_MultiRates/
         PF_JudgeTimeIntervalSwitch_MultiRates/SF_JudgeStepSwitch_MultiRates
��    ע: 
*******************************************************************************/
uchar8 SF_JudgeSwitchTime_MultiRates(ulong32 V_ulSwitchTimeID, uchar8 *pV_ucCurrentTime, uchar8 *pV_ucSwitchTimeTemp)
{
	uchar8 V_ucSwitchTime[CLChange_TZ_Time];		/*�л�ʱ�仺����*/
	uchar8 V_ucResult;
	uchar8 V_ucWrSafeFlag = C_W_SafeFlag_1;
	uchar8 V_ucReturnTemp;
	ushort16 V_usSwitchTimeLength, V_usDataEncode = 0;
	
	V_usSwitchTimeLength = CLChange_TZ_Time;		/*�л�ʱ�䳤��,4�ֳ���һ��,�˴�ȡ�����л����ȵĺ�*/
	
	V_ucReturnTemp = InF_Read_Data(V_ulSwitchTimeID, pV_ucSwitchTimeTemp, &V_usSwitchTimeLength, &V_usDataEncode);	/*���л�ʱ��*/
	
	if ( (V_ucReturnTemp != C_OK)
      || (PF_DataTimeActive_698(&pV_ucSwitchTimeTemp[1], C_MinStart, (CLChange_TZ_Time - 1) ) != C_OK) )			/*zlj����698��ʽʱ���ж�*/
	{
		return C_SwitchTimeErr;																					/*���л�ʱ��ʧ��,���ش���*/
	}
	V_ucResult = PF_Campare_Data(pV_ucCurrentTime, &pV_ucSwitchTimeTemp[1], (CLChange_TZ_Time - 1) );				/*�л�ʱ��͵�ǰʱ�����Ƚ�,zlj���ȸ��ú궨��*/
	
	V_ucWrSafeFlag |= C_W_SafeFlag_2;
	
	if (V_ucResult == C_LessThan)		/*��ǰʱ��С���л�ʱ��,���л���Ч*/
	{
		return C_SwitchInvalid;
	}
	else								/*��ǰʱ����ڵ����л�ʱ��,�л���Ч*/
	{
		V_ucSwitchTime[0]= 0xFF;		/*���л�ʱ������,��д���ݲ�*/
		memset(&V_ucSwitchTime[1], 0x00, (CLChange_TZ_Time - 1) );
		
		V_ucWrSafeFlag |= C_W_SafeFlag_3;
		InF_Write_Data(C_Msg_Deal_MultiRates, V_ulSwitchTimeID, V_ucSwitchTime, CLChange_TZ_Time, V_ucWrSafeFlag);
		
		return C_SwitchValid;
	}
}

/*******************************************************************************
����ԭ��: uchar8 SF_MultiRates_ParseMessage(Str_Msg_Parameter *pStr_Msg_Parameter)
��������: ����ģ����Ϣ�������	
�������: P_Msg_Parameter �C��Ϣ�ṹ��
�������:  
���ز���: C_OK-��Ϣ������ȷ,����з����ж�/C_Error-��Ϣ��������,���账��
����λ��: 
��    ע:���1�� SourceAddr= ͨ�š�����������йصĲ���ʱ������
                 DerictAddr = C_Msg_Deal_MultiRates
                 Len = 1
                 ������Pt_ParaMetersChange,ȡֵΪ��
         ���2�� SourceAddr= ���ȡ�����ÿ���Ӵ���
                 DerictAddr = C_Msg_Deal_MultiRates
                 Len = 2
                ������Pt_Dispatch_Timing��ȡֵC_SystemMinChange
        ���3�� SourceAddr�����ʡ��ϵ��ʼ��ʱ����
                DerictAddr = C_Msg_Deal_MultiRates
                Len = 1
                ������Pt_Initialization,ȡֵΪ��
*******************************************************************************/
uchar8 SF_ParseMessage_MultiRates(Str_Msg_Parameter *pStr_Msg_Parameter)
{
	uchar8 *pV_ucParm;
	 
	if (pStr_Msg_Parameter->PowerFlag != C_PowerOn)		/*����ʱֱ�ӷ��ش���,���账��*/
	{
		return C_Error;
	}
	/*�����������,����������÷����������*/
	pV_ucParm = pStr_Msg_Parameter->Parameter;
	
	if (*pV_ucParm == Pt_ParaMetersChange)
	{
		if(pStr_Msg_Parameter->Length == (Pt_ParaMetersChange_Len + 1) )
		{
			return C_OK;
		}
	}
	else if (*pV_ucParm == Pt_Dispatch_Timing)
	{
		if (pStr_Msg_Parameter->Length == (Pt_Dispatch_Timing_Len + 1) )
		{
			return C_OK;
		}
	}
	else if (*pV_ucParm == Pt_Initialization)
	{
		if (pStr_Msg_Parameter->Length ==(Pt_Initialization_Len + 1) )
		{
			return C_OK;
		}
	}
	return C_Error;
}

/*******************************************************************************
����ԭ��: void SF_MsgProcess(uchar8 *pV_ucParm, uchar8 V_ucParmLen, uchar8 V_ucDerictMod)
��������: д��Ϣ����	
�������: *pV_ucParm-��Ϣ������Parameter����
          V_ucParmLen-��Ϣ��������
         V_ucDerictMod-Ŀ����Ϣ��
�������: ��  
���ز���: �� 
����λ��: 
��    ע:
*******************************************************************************/
void SF_MsgProcess(uchar8 *pV_ucParm, uchar8 V_ucParmLen, uchar8 V_ucDerictMod)
{
	Str_Msg_Parameter Str_Msg_MultiRates;
	
	Str_Msg_MultiRates.PowerFlag = C_PowerOn;
	Str_Msg_MultiRates.SourceAddr = C_Msg_Deal_MultiRates;
	Str_Msg_MultiRates.DerictAddr = V_ucDerictMod;
	Str_Msg_MultiRates.Length = V_ucParmLen;
	Str_Msg_MultiRates.Parameter = pV_ucParm;

	InF_WriteMessege(&Str_Msg_MultiRates);		/*д��Ϣ����*/
}

/*******************************************************************************
����ԭ��: void SF_SendMsgToDisplay(uchar8 V_ucMsg1, uchar8 V_ucMsg2, uchar8 V_ucMsg1_Mode, uchar8 V_ucMsg2_Mode, uchar8 V_ucMsgNum)
��������: ����Ϣ����ʾģ�飬��Ϊ����ģʽ,��෢��2����Ϣ	
�������: V_ucMsg1Ϊ��Ϣ1��V_ucMsg2Ϊ��Ϣ2��V_ucMsgNum������Ϣ��������=1ʱ���ڶ�����Ϣ��Ч
�������: ��
���ز���: ��
����λ��: 
��    ע:
*******************************************************************************/
void SF_SendMsgToDisplay(uchar8 V_ucMsg1, uchar8 V_ucMsg2, uchar8 V_ucMsg1_Mode, uchar8 V_ucMsg2_Mode, uchar8 V_ucMsgNum)
{
	uchar8 V_ucDisTemp[8];
    
	V_ucDisTemp[0] = Pt_DisplayStatus;
	V_ucDisTemp[1] = (V_ucMsg1 | V_ucMsg1_Mode);
	V_ucDisTemp[2] = 0xFF;
	V_ucDisTemp[3] = 0xFF;
	V_ucDisTemp[4] = Pt_DisplayStatus;
	V_ucDisTemp[5] = (V_ucMsg2 | V_ucMsg2_Mode);
	V_ucDisTemp[6] = 0xFF;
	V_ucDisTemp[7] = 0xFF;
	
	SF_MsgProcess(V_ucDisTemp, (Pt_DisplayStatus_Len + 1) * V_ucMsgNum, C_Msg_Display);
}

/*******************************************************************************
����ԭ��: void SF_TimeZoneSequence( uchar8 *pV_ucBuf, uchar8 V_ucNum)
��������: ʱ����ʱ�α���������
�������: pV_ucBufִ��ʱ�����ݴ�buffer�׵�ַ��V_ucNumʱ����/ʱ�α����		
�������: ������ʱ����
���ز���: ��
����λ��: 	
��    ע:
*******************************************************************************/
void SF_TimeZoneSequence( uchar8 *pV_ucBuf, uchar8 V_ucNum)
{
	uchar8 V_uci, V_ucn;
	uchar8 V_ucBufB[3];
	uchar8 V_ucBF[2], V_ucAF[2];
	if ( V_ucNum < 2 ) 
	{
		return;
	}
	for ( V_ucn = 0; V_ucn < (V_ucNum - 1); V_ucn++ )
	{
		for ( V_uci = 0; V_uci < (V_ucNum - 1 - V_ucn); V_uci++)
		{
			PF_OneDataReversed(&pV_ucBuf[V_uci * 3], &V_ucBF[0], 2);						/*zlj�³����Ϊ���ڵ��ֽڣ���ʱ�α���ڸ��ֽڣ���Ҫ�޸�ƫ�ƣ��ٵ���*/
			PF_OneDataReversed(&pV_ucBuf[(V_uci + 1) * 3], &V_ucAF[0], 2);

			if ( PF_Campare_Data( V_ucBF, V_ucAF, 2 ) == C_GreaterThan )					/*ǰ���� > ������*/
			{
				PF_CopyDataBytes( pV_ucBuf + V_uci * 3, V_ucBufB, 3 );						/*��������*/
				PF_CopyDataBytes( pV_ucBuf + (V_uci + 1) * 3, pV_ucBuf + V_uci * 3, 3 );	/*��������*/
				PF_CopyDataBytes( V_ucBufB, pV_ucBuf + (V_uci + 1) * 3, 3 );				/*��������*/
			}
		}
	}
}

/*******************************************************************************
����ԭ��: void SF_Deal12dig(ulong32 V_ulOAD, uchar8 *pV_ucdata)
��������: ������ʾ�٢�
�������: ulong32 V_ulOAD���л�ʱ���OAD	��uchar8 *pV_ucdata����Ϣ����
�������: pV_ucdata: ��������Ϣ����
���ز���: ��
����λ��: 	
��    ע:
*******************************************************************************/
void SF_Deal12dig(ulong32 V_ulOAD, uchar8 *pV_ucdata)
{
	uchar8 V_ucSwitchTime[CLChange_Rate];
	ushort16 V_usLength, V_usDataEncode = 0;
	
	V_usLength = CLChange_Rate;
	InF_Read_Data(V_ulOAD, V_ucSwitchTime, &V_usLength, &V_usDataEncode);	/*��ʱ��*/

	pV_ucdata[1] = C_AlwaysDisplay;											/*��������*/
	
	if (PF_DataTimeActive_698(&V_ucSwitchTime[C_MinStart], C_MinStart, (CLChange_Rate - C_MinStart) ) == C_OK)
	{
		pV_ucdata[5] = C_AlwaysDisplay;		/*��������*/
	}
	else
	{
		pV_ucdata[5] = C_NotDisplay;		/*�����*/
	}
}