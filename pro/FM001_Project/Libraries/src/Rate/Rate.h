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

#ifndef __Rate_H
#define __Rate_H

/*ʱ��״̬*/
uchar8 SV_ucTimeIntervalStatus;			/*ʱ��״̬�Ĵ���,����ʱ��Ͷ���ж�*/
uchar8 SV_ucTimeIntSetStatus;			/*ʱ�α�״̬�Ĵ���*/
#define C_TimeChange			0xAA	/*ʱ�η���Ͷ��*/
#define C_TimeNoChange			0xBB	/*ʱ��ûͶ��*/


#define C_HolidyIntID			0x0403FA00	/*���ڶ��������ձ�ʶ���ʼ��ֵ*/
#define C_HoliBlockNum			46			/*�������������ݵĿ���1*/
/*�����л����ʹ���*/
#define C_DisStutas_Char1		0x02	/*������1��ȡbit1,�����жϢ٢ں���*/
#define C_DisplayRate			1		/*Һ���٢ڷ��ŵı�ʾ���ʵ��*/
#define C_DisplayTimeInterval	0		/*Һ���٢ڷ��ŵı�ʾʱ�α�*/

#define C_TimeZone_Status3		0x20	/*״̬��3��ʱ�����Ӧλ*/
#define C_FirstTimeZone			0xDF	/*��һ��ʱ����*/
#define C_SecondTimeZone		0x20	/*�ڶ���ʱ����*/
#define C_TimeZoneOffset		5		/*״̬��3��ʱ��λ��ƫ����*/

#define C_TimeInterval_Status3	0x01	/*״̬��3��ʱ�α��Ӧλ*/
#define C_FirstTimeInterval		0xFE	/*��һ��ʱ�α�*/
#define C_SecondTimeInterval	0x01	/*�ڶ���ʱ�α�*/

#define C_LowByte				0x00	/*״̬��3�еĵ��ֽ�*/
#define C_HighByte				0x01	/*״̬��3�еĸ��ֽ�*/

#define C_First					0x00	/*�����Ĵ�����һ������*/
#define C_Second				0x86	/*�����Ĵ����ڶ�������*/

#define C_RateOADChange_Flag	0x00000001		/*���ʵ�����ݱ�ʶ�ı��־*/


/*�����Ĵ���*/
#define C_TIntervalSet_EX		0		/*ʱ�α�������Ӧ�ֽڵ�ַ*/
#define C_TZoneSet_EX			1		/*ʱ����������Ӧ�ֽڵ�ַ*/

/*��/�½����ж�*/
#define C_SettlementLength_One	3		/*ÿ������������ݳ���*/
#define C_SettlementNum			(CLCurrent_Ladder_Table_LadSett/C_SettlementLength_One)		/*ÿ�׽��ݰ���������ո���*/

/*�л�ʱ���ж�*/
#define C_SwitchValid			0	/*�л���Ч*/
#define C_SwitchInvalid			1	/*�л���Ч*/
#define C_SwitchTimeErr			2	/*�л�ʱ�����*/

/*����,������0x04000101*/
#define C_Week_Data				0	/*��*/
#define C_Day_Data				1	/*��*/
#define C_Month_Datak			2	/*��*/
#define C_Year_Data				3	/*��*/

/*ʱ�������,��������0x040001FD*/
#define C_Sec					0	/*��*/
#define C_Minute				1	/*��*/
#define C_Hour					2	/*ʱ*/
#define C_Day					3	/*��*/
#define C_Month					4	/*��*/
#define C_Year					5	/*��*/

/*ʱ�������,������0x0400010C*/
#define C_Second_Week			0	/*��*/
#define C_Minute_Week			1	/*��*/
#define C_Hour_Week				2	/*ʱ*/
#define C_Week_Week				3	/*��*/
#define C_Day_Week				4	/*��*/
#define C_Month_Week			5	/*��*/
#define C_Year_Week				6	/*��*/

/*���״ָ̬ʾ��־*/
uchar8 SV_ucPowerStatus;			/*���״ָ̬ʾ��־���ж϶��������ʱΪ��ǰʱ�仹�ǲ���ʱ��*/
#define C_PowerUpEdge			0xAA	/*�ϵ���״̬,Ϊ����ʱ��*/
#define C_PowerOnPeriod			0xBB	/*��������е�״̬,Ϊ��ǰʱ��*/
/*ʱ�α�*/
#define CL_OneTimeIntervalNum	3		/*һ��ʱ�α�ĳ���*/


typedef struct
{
	uchar8 StepSwitchType;	/*��������*/
	uchar8 Time[5];			/*����ʱ��*/
}Str_StepSwitch;

/*zlj����������ԭ���ĳ�������C_usLimitJudge[5]*/
#define C_MaxYearTZNum		14	/*��ʱ������ֵ*/
#define C_MaxDayPTTabNum	8	/*��ʱ�α�����ֵ*/
#define C_MaxDayPTNum		14	/*��ʱ������ֵ*/
/*��������ֵ�������е�C_MaxRatesNum�궨��*/
#define C_MaxHolidayNum		20	/*������������ֵ(�������˵��Ϊ20)*/


/**************** ��������********************************************/
void InF_MultiRates_ParseMessage(Str_Msg_Parameter *pStr_Msg);
void InF_Deal_MultiRates(void);
uchar8 SF_JudgeSwitchTime_MultiRates(ulong32 V_ulSwitchTimeID, uchar8 *pV_ucCurrentTime, uchar8 *pV_ucSwitchTimeTemp);
void SF_StepTypeProcess(uchar8 *pV_ucOldDate, uchar8 *pV_ucNewDate, uchar8 *pV_ucSettlementTime);
void SF_JudgeStepSwitch_MultiRates(uchar8 *pV_ucCurrentTime, uchar8 *pV_ucCurrentStepData, uchar8 V_ucStepStatus);
void SF_JudgeTimeIntervalSwitch_MultiRates(uchar8 V_ucDisplayType, uchar8 *pV_ucCurrentTime, uchar8 *pV_ucChangeFlag);
void SF_JudgeTimeZoneSwitch_MultiRates(uchar8 *pV_ucCurrentTime, uchar8 *pV_ucChangeFlag);
void SF_JudgeRateSwitch_MultiRates(uchar8 V_ucDisplayType, uchar8 *pV_ucCurrentTime);
uchar8 SF_ParseMessage_MultiRates(Str_Msg_Parameter *pStr_Msg_Parameter);
void SF_MsgProcess(uchar8 *pV_ucParm, uchar8 V_ucParmLen, uchar8 V_ucDerictMod);
void SF_ParaChangeProcess_MultiRates(uchar8 V_ucStepStatus, uchar8 V_ucRatesNum);
void SF_SendMsgToDisplay(uchar8 V_ucMsg1, uchar8 V_ucMsg2, uchar8 V_ucMsg1_Mode, uchar8 V_ucMsg2_Mode, uchar8 V_ucMsgNum);
void SF_TimeZoneSequence( uchar8 *pV_ucBuf, uchar8 V_ucNum);
void SF_Deal12dig(ulong32 V_ulOAD, uchar8 *pV_ucdata);
#endif
