/*****************************************************************************************
Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     EventRecord.c
Version:       V1
Date:          2014-04-01
Description:   �¼���¼�ļ�
Function List:
****************************************************************************************
History1:      ��1���޸�
����1. Date:2021.09
 	   Author:DB
       Modification:FH001��һ���޸�
**********************************************
����2. Date:
   	   Author:
       Modification:
********************************************************************************
History2:      ��2���޸�
����1. Date:
  	   Author:
       Modification:
**********************************************
����2. Date:
   	   Author:
       Modification:
****************************************************************************************/

#include "Public.h"
#include "EventRecord.h"
#include "Communication.h"
#include "SecurityCommunication.h"

/***********************************************/
/*�궨��*/
const	uchar8	C_ucAhEquivalent[4]={0xA0, 0x8C, 0x00, 0x00};/*0.01Ah����, ÿ���ۼ�3λС��������3600*10=8CA0(HEX)*/
const	uchar8	C_ucAddAh[4]={01, 00, 00, 00};				/*��0.01Ah�ĳ���*/
const	uchar8	C_ucAddOneMin[4]={01, 00, 00, 00};			/*�ۼ�ʱ���1*/
const	uchar8	C_uc3P3WVotageAngle1[2]={0x2C, 0x01};		/*���������������ѹ�Ƕ�1��30.0�ȣ�hex*/
const	uchar8	C_uc3P3WVotageAngle2[2]={0x7E, 0x04};		/*���������������ѹ�Ƕ�2��115.0�ȣ�hex*/
const	uchar8	C_uc3P3WCurrentAngle1[2]={0x84, 0x03};		/*������������������Ƕ�1��90.0�ȣ�hex*/
const	uchar8	C_uc3P3WCurrentAngle2[2]={0xDC, 0x05};		/*������������������Ƕ�2��150.0�ȣ�hex*/
		uchar8	GV_ucEvent_Hstate[C_EventNoLength];			/*�¼���ʷ״̬*/
		uchar8	GV_ucEvent_JudgeTimer[C_EventNoLength]; 	/*�¼��ж϶�ʱ��*/
		uchar8 	GV_ucEvent_SymbolHstate[C_EventSymbolLength];/*��ʾ������ʷ״̬*/
		Str_BeeperAlerm_Type GStr_BackLightAlarm;		    /*���ⱨ��*/
		Str_BeeperAlerm_Type GStr_Alarmoutput; 			    /*�����������*/
		Str_BeeperAlerm_Type GStr_BellAlarm;				/*С������ʾ����*/
		uchar8 GV_ucBellAlarm_Hstate[C_AlarmTempLength];    /*С���������ʷ״̬*/
		uchar8 GV_ucAlarmoutput_Hstate[C_AlarmTempLength];	/*������������ʷ״̬*/
		uchar8 GV_ucBackLightAlarm_Hstate[C_AlarmTempLength];/*���ⱨ��*/
        uchar8 GV_ucReversecurrentTimes;                     /*���������ʼ������ʱ������*/
        uchar8 GV_ucDirectionExchange;                      /*������������/���򣬷���ı��ʶ*/

/*****************************************************************************************/
/*����Ϊ�¼��ṹ�嶨��*/
/*****************************************************************************************/
Str_LpowerTvoltagelose_Type	GStr_TotalvoltageloseStr;		/*ȫʧѹ*/
Str_LpowerTvoltagelose_Type	GStr_PowerfailStr;				/*����*/
Str_CoverRecord_Type		GStr_OpenMeterCoverStr;			/*�����*/
Str_CoverRecord_Type		GStr_OpenTerminalCoverStr;		/*����ť��*/
Str_ACPowerFail_Type		GStr_PowerabnormalStr;			/*��Դ�쳣*/
Str_ACPowerFail_Type		GStr_ACPowerFailStr;				/*������Դʧ��*/
Str_ActiveDemand_Type 		GStr_OverForwardActiveStr;		/*�����й���������*/
Str_ActiveDemand_Type 		GStr_OverReverseActiveStr;		/*�����й���������*/
Str_ActiveDemand_Type 		GStr_Over1IdleDemandStr;			/*��1�����޹���������*/
Str_ActiveDemand_Type 		GStr_Over2IdleDemandStr;			/*��2�����޹���������*/
Str_ActiveDemand_Type 		GStr_Over3IdleDemandStr;			/*��3�����޹���������*/
Str_ActiveDemand_Type 		GStr_Over4IdleDemandStr;			/*��4�����޹���������*/
Str_Unbanlance_Type 		GStr_UnbanlanceVoltageStr;		/*��ѹ��ƽ��*/
Str_Unbanlance_Type 		GStr_UnbanlanceCurrentStr;		/*������ƽ��*/
Str_Unbanlance_Type 		GStr_SUnbanlanceCurrentStr;		/*�������ز�ƽ��*/
Str_AhMeter_Type			GStr_AlossvoltageStr;			/*A��ʧѹ*/
Str_AhMeter_Type			GStr_BlossvoltageStr;			/*B��ʧѹ*/
Str_AhMeter_Type			GStr_ClossvoltageStr;			/*C��ʧѹ*/
Str_AhMeter_Type			GStr_ALossphaseStr;				/*A�����*/
Str_AhMeter_Type			GStr_BLossphaseStr;				/*B�����*/
Str_AhMeter_Type			GStr_CLossphaseStr;				/*C�����*/
Str_AhMeter_Type			GStr_ALessvoltageStr;			/*A��Ƿѹ*/
Str_AhMeter_Type			GStr_BLessvoltageStr;			/*B��Ƿѹ*/
Str_AhMeter_Type			GStr_CLessvoltageStr;			/*C��Ƿѹ*/
Str_AhMeter_Type			GStr_AOvervoltageStr;			/*A���ѹ*/
Str_AhMeter_Type			GStr_BOvervoltageStr;			/*B���ѹ*/
Str_AhMeter_Type			GStr_COvervoltageStr;			/*C���ѹ*/
Str_OtherMeter_Type 		GStr_ReversephaseVoltageStr;		/*��ѹ������*/
Str_OtherMeter_Type 		GStr_ReversephaseCurrentStr;		/*����������*/
Str_OtherMeter_Type			GStr_ALosscurrentStr;			/*A��ʧ��*/
Str_OtherMeter_Type 		GStr_BLosscurrentStr;			/*B��ʧ��*/
Str_OtherMeter_Type 		GStr_CLosscurrentStr;			/*C��ʧ��*/
Str_OtherMeter_Type 		GStr_AFailcurrentStr;			/*A�����*/
Str_OtherMeter_Type 		GStr_BFailcurrentStr;			/*B�����*/
Str_OtherMeter_Type 		GStr_CFailcurrentStr;			/*C�����*/
Str_OtherMeter_Type 		GStr_AOvercurrentStr;			/*A�����*/
Str_OtherMeter_Type 		GStr_BOvercurrentStr;			/*B�����*/
Str_OtherMeter_Type 		GStr_COvercurrentStr;			/*C�����*/
Str_OtherMeter_Type 		GStr_TReversecurrentStr;			/*�ܹ��ʷ���*/
Str_OtherMeter_Type 		GStr_AReversecurrentStr;			/*A�๦�ʷ���*/
Str_OtherMeter_Type 		GStr_BReversecurrentStr;			/*B�๦�ʷ���*/
Str_OtherMeter_Type 		GStr_CReversecurrentStr;			/*C�๦�ʷ���*/
Str_OtherMeter_Type 		GStr_AOverloadStr;				/*A�����*/
Str_OtherMeter_Type			GStr_BOverloadStr;				/*B�����*/
Str_OtherMeter_Type 		GStr_COverloadStr;				/*C�����*/
Str_OtherMeter_Type 		GStr_OverpowerfactStr;			/*�ܹ�������������*/
Str_OtherMeter_Type 		GStr_AOverpowerfactStr;			/*A�๦������������*/
Str_OtherMeter_Type 		GStr_BOverpowerfactStr;			/*B�๦������������*/
Str_OtherMeter_Type 		GStr_COverpowerfactStr;			/*C�๦������������*/
Str_OtherMeter_Type			GStr_ConMStr;					/*�㶨�ų�����*/
Str_OtherMeter_Type			GStr_MeterFaStr;					/*����оƬ����*/
Str_OtherMeter_Type			GStr_ClockFaStr;					/*ʱ�ӹ���*/
Str_OtherMeter_Type			GStr_NeutralAbnormalStr;			/*���ߵ����쳣*/
Str_OtherMeter_Type			GStr_BroadcastTimeStr;			/*���ߵ����쳣*/

/*****************************************************************************************/
/*����˳���������������*/
/*****************************************************************************************/
const	uchar8	Event_ChooseTableNo[C_EventNoLength][3]=
{/*�¼�����ʱ��ȡ����			�¼�����ʱ��ȡ����*/
	{C_NULL,					C_NULL,					C_3P4W				},/*ȫʧѹ*/
	{C_NULL,					C_NULL,					C_3P4W				},/*������Դʧ��*/
	{C_NULL,					C_NULL,					C_3P4W				},/*����*/
	{C_OpenCoverChooseNo,		C_OpenCoverChooseNo,	C_3P4W				},/*�����*/
  	{C_OpenCoverChooseNo,    	C_OpenCoverChooseNo,	C_3P4W				},/*����ť��*/
	{C_PowerAbnormalChooseNo,	C_PowerAbnormalChooseNo,C_3P4W				},/*�㶨�ų�����*/
	{C_PowerAbnormalChooseNo,	C_NULL,					C_3P4W				},/*��Դ�쳣*/
	{C_NULL,       				C_NULL,					C_3P4W				},/*�����й���������*/
	{C_NULL,       				C_NULL,					C_3P4W				},/*�����й���������*/
	{C_NULL,       				C_NULL,					C_3P4W				},/*1�����޹���������*/
	{C_NULL,       				C_NULL,					C_3P4W				},/*2�����޹���������*/
	{C_NULL,       				C_NULL,					C_3P4W				},/*3�����޹���������*/
	{C_NULL,       				C_NULL,					C_3P4W				},/*4�����޹���������*/
	{C_EERAMChooseNo,       	C_EEChooseNo,			C_3P4W				},/*A��ʧѹ*/
	{C_EERAMChooseNo,       	C_EEChooseNo,			C_3P3W				},/*B��ʧѹ*/
	{C_EERAMChooseNo,       	C_EEChooseNo,			C_3P4W				},/*C��ʧѹ*/
	{C_EERAMChooseNo,       	C_EEChooseNo,			C_3P4W				},/*A��Ƿѹ*/
	{C_EERAMChooseNo,       	C_EEChooseNo,			C_3P3W				},/*B��Ƿѹ*/
	{C_EERAMChooseNo,       	C_EEChooseNo,			C_3P4W				},/*C��Ƿѹ*/
	{C_EERAMChooseNo,       	C_EEChooseNo,			C_3P4W				},/*A���ѹ*/
	{C_EERAMChooseNo,       	C_EEChooseNo,			C_3P3W				},/*B���ѹ*/
	{C_EERAMChooseNo,       	C_EEChooseNo,			C_3P4W				},/*C���ѹ*/
	{C_EERAMChooseNo,       	C_EEChooseNo,			C_3P4W				},/*A�����*/
	{C_EERAMChooseNo,       	C_EEChooseNo,			C_3P3W				},/*B�����*/
	{C_EERAMChooseNo,       	C_EEChooseNo,			C_3P4W				},/*C�����*/
	{C_EEChooseNo,       		C_EEChooseNo,			C_3P4W				},/*��ѹ������*/
	{C_EEChooseNo,       		C_EEChooseNo,			C_3P4W				},/*����������*/
	{C_EEChooseNo,       		C_EEChooseNo,			C_3P4W				},/*��ѹ��ƽ��*/
	{C_EEChooseNo,       		C_EEChooseNo,			C_3P4W				},/*������ƽ��*/
	{C_EERAMChooseNo,       	C_EEChooseNo,			C_3P4W				},/*A��ʧ��*/
	{C_EERAMChooseNo,       	C_EEChooseNo,			C_3P3W				},/*B��ʧ��*/
	{C_EERAMChooseNo,       	C_EEChooseNo,			C_3P4W				},/*C��ʧ��*/
	{C_EERAMChooseNo,       	C_EEChooseNo,			C_3P4W				},/*A�����*/
	{C_EERAMChooseNo,      		C_EEChooseNo,			C_3P3W				},/*B�����*/
	{C_EERAMChooseNo,      		C_EEChooseNo,			C_3P4W				},/*C�����*/
	{C_EERAMChooseNo,      		C_EEChooseNo,			C_3P4W				},/*A�����*/
	{C_EERAMChooseNo,      		C_EEChooseNo,			C_3P3W				},/*B�����*/
	{C_EERAMChooseNo,      		C_EEChooseNo,			C_3P4W				},/*C�����*/
	{C_EEChooseNo,    			C_EEChooseNo,			C_3P4W				},/*�ܹ��ʷ���*/
	{C_EEChooseNo,    			C_EEChooseNo,			C_3P4W				},/*A�๦�ʷ���*/
	{C_EEChooseNo,    			C_EEChooseNo,			C_3P3W				},/*B�๦�ʷ���*/
	{C_EEChooseNo,    			C_EEChooseNo,			C_3P4W				},/*C�๦�ʷ���*//*�����������ж�*/
	{C_EEChooseNo,       		C_EEChooseNo,			C_3P4W				},/*A�����*/
	{C_EEChooseNo,       		C_EEChooseNo,			C_3P3W				},/*B�����*/
	{C_EEChooseNo,       		C_EEChooseNo,			C_3P4W				},/*C�����*/
	{C_OverPowerfactChooseNo,	C_OverPowerfactChooseNo,C_3P4W				},/*�ܹ�������������*/
	{C_OverPowerfactChooseNo,	C_OverPowerfactChooseNo,C_3P3W				},/*A�๦������������*/
	{C_OverPowerfactChooseNo,	C_OverPowerfactChooseNo,C_3P3W				},/*B�๦������������*/
	{C_OverPowerfactChooseNo,	C_OverPowerfactChooseNo,C_3P3W				},/*C�๦������������*//*�����������ж�*/
	{C_EEChooseNo,       		C_EEChooseNo,			C_3P4W				},/*�������ز�ƽ��*/
#if 0
	{C_EEChooseNo,       		C_NULL,					C_3P4W				},/*�ܳ�������*/
#endif
	{C_NULL,			        C_NULL,				    C_3P4W				},/*����оƬ����*/
	{C_NULL,			        C_NULL,				    C_3P4W				},/*ʱ�ӹ���*/
	{C_NULL,			        C_NULL,				    C_3P3W				}/*���ߵ����쳣*/
};

/*****************************************************************************************/
/*����˳���������������*/
/*****************************************************************************************/
/*�¼��ж���ʱʱ����*/
const	ulong32	Event_Delaytime[C_EventNoLength]=
{	/*�ж���ʱʱ�����ݱ�ʶ*/
	CLossVolage_Delay_T,		/*ʧѹ�¼��ж���ʱʱ��*/
	C_NULL,						/*������Դ����*/
	C_NULL,						/*����*/
	C_NULL,						/*�����*/
	C_NULL,						/*����ť��*/
	C_NULL,						/*�㶨�ų�����*/
	C_NULL,						/*��Դ�쳣*/
	CPosAcDemandOv_Delay_T,		/*���������¼��ж���ʱʱ��*/
	CRevAcDemandOv_Delay_T,		/*���������¼��ж���ʱʱ��*/
	CReDemandOv_Delay_T,		/*���������¼��ж���ʱʱ��*/
	CReDemandOv_Delay_T,		/*���������¼��ж���ʱʱ��*/
	CReDemandOv_Delay_T,		/*���������¼��ж���ʱʱ��*/
	CReDemandOv_Delay_T,		/*���������¼��ж���ʱʱ��*/
	CLossVolage_Delay_T,		/*ʧѹ�¼��ж���ʱʱ�䣨A�ࣩ*/
	CLossVolage_Delay_T,		/*ʧѹ�¼��ж���ʱʱ�䣨B�ࣩ*/
	CLossVolage_Delay_T,		/*ʧѹ�¼��ж���ʱʱ�䣨C�ࣩ*/
	CLowVolage_Delay_T,			/*Ƿѹ�¼��ж���ʱʱ�䣨A�ࣩ*/
	CLowVolage_Delay_T,			/*Ƿѹ�¼��ж���ʱʱ�䣨B�ࣩ*/
	CLowVolage_Delay_T,			/*Ƿѹ�¼��ж���ʱʱ�䣨C�ࣩ*/
	COverVolage_Delay_T,		/*��ѹ�¼��ж���ʱʱ�䣨A�ࣩ*/
	COverVolage_Delay_T,		/*��ѹ�¼��ж���ʱʱ�䣨B�ࣩ*/
	COverVolage_Delay_T,		/*��ѹ�¼��ж���ʱʱ�䣨C�ࣩ*/
	CBreakVol_Delay_T,			/*�����¼��ж���ʱʱ�䣨A�ࣩ*/
	CBreakVol_Delay_T,			/*�����¼��ж���ʱʱ�䣨B�ࣩ*/
	CBreakVol_Delay_T,			/*�����¼��ж���ʱʱ�䣨C�ࣩ*/
	CReversedVoltage_Delay_T,	/*��ѹ������*/
	CReversedCurrent_Delay_T,	/*����������*/
	CNoBal_Vol_Delay_T,			/*��ѹ��ƽ�����ж���ʱʱ��*/
	CNoBal_Curr_Delay_T,		/*������ƽ�����ж���ʱʱ��*/
	CLossCurr_Delay_T,			/*ʧ���¼��ж���ʱʱ�䣨A�ࣩ*/
	CLossCurr_Delay_T,			/*ʧ���¼��ж���ʱʱ�䣨B�ࣩ*/
	CLossCurr_Delay_T,			/*ʧ���¼��ж���ʱʱ�䣨C�ࣩ*/
	COverCurr_Delay_T,			/*�����¼��ж���ʱʱ�䣨A�ࣩ*/
	COverCurr_Delay_T,			/*�����¼��ж���ʱʱ�䣨B�ࣩ*/
	COverCurr_Delay_T,			/*�����¼��ж���ʱʱ�䣨C�ࣩ*/
	CBreakCurr_Delay_T,			/*�����¼��ж���ʱʱ�䣨A�ࣩ*/
	CBreakCurr_Delay_T,			/*�����¼��ж���ʱʱ�䣨B�ࣩ*/
	CBreakCurr_Delay_T,			/*�����¼��ж���ʱʱ�䣨C�ࣩ*/
	CPowerRev_Delay_T,			/*���ʷ����¼��ж���ʱʱ�䣨�ܣ�*/
	CPowerRev_Delay_T,			/*���ʷ����¼��ж���ʱʱ�䣨A�ࣩ*/
	CPowerRev_Delay_T,			/*���ʷ����¼��ж���ʱʱ�䣨B�ࣩ*/
	CPowerRev_Delay_T,			/*���ʷ����¼��ж���ʱʱ�䣨C�ࣩ*/
	COverLoad_Delay_T,			/*�����¼��ж���ʱʱ�䣨A�ࣩ*/
	COverLoad_Delay_T,			/*�����¼��ж���ʱʱ�䣨B�ࣩ*/
	COverLoad_Delay_T,			/*�����¼��ж���ʱʱ�䣨C�ࣩ*/
	CPowerFactor_Delay_T,		/*���������������ж���ʱʱ��*/
	CPowerFactor_Delay_T,		/*���������������ж���ʱʱ�䣨A�ࣩ*/
	CPowerFactor_Delay_T,		/*���������������ж���ʱʱ�䣨B�ࣩ*/
	CPowerFactor_Delay_T,		/*���������������ж���ʱʱ�䣨C�ࣩ*/
	CSeriNoBal_Curr_Delay_T,	/*�������ز�ƽ���ж���ʱʱ��*/
#if 0
	CTrendRev_Delay_T,			/*���������¼��ж���ʱʱ��*/
#endif
	CMeterFa_Delay_T,			/*����״̬λʱ��ʱ ����оƬ�����¼��ж���ʱʱ��*/
#if 0
	CClockFa_Delay_T,			/*����״̬λʱ��ʱ ʱ�ӹ����¼��ж���ʱʱ��*/
#endif
	C_NULL,			            /*����״̬λʱ��ʱ ʱ�ӹ����¼��ж���ʱʱ��*/
    CNeutralAbnormal_Delay_T,   /*���ߵ����쳣�ж��ӳ�ʱ��*/
};
/*****************************************************************************************/
/*����˳���������������*/
/*****************************************************************************************/
/*�¼��ж���ʱʱ��Ĭ�ϱ��*/
const uchar8 Event_DDelaytime[C_EventNoLength]=
{/*ʱ���жϷ�ֵĬ������*/
	C_Judge_Event_DefaultTime1,  /*��Event_Delaytime[]����¼�һһ��Ӧ*/
	C_Judge_Time4,				/*������Դ�����ϸǺͺ㶨�ų�ȥ���ɵ�����*/
	C_PowerFail_Judge_Time,              /*������ʱʱ��Ĭ��1s*/
	C_Judge_Time1,
	C_Judge_Time1,
	C_Judge_Time4,
	C_NULL,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Time0,
    C_Judge_Event_DefaultTime1,
};
/*****************************************************************************************/
/*����˳���������������*/
/*****************************************************************************************/
/*�¼���ʼ����ʱ���ʶ�룬�����ж��¼������ָ�״̬*/
const ulong32 EventHappenEndTime[]=
{/*�¼���ʼʱ�����ݱ�ʶ	�¼�����ʱ�����ݱ�ʶ*/
	CAll_Loss_Vol_Note_1,		/*ȫʧѹ����ʼʱ����9���ֽ�*/
	CAux_Pow_Down_Note_1,		/*������Դʧ��*/
	CPow_Down_Note_1,		/*����*/
	COpenW_Note_1,			/*�����*/
	COpenCW_Note_1,			/*����ť��*/
	CConM_Note_1,			/*�㶨�ų�����*/
	CPowerFa_Note_1,		/*��Դ�쳣*/
	CPos_Ac_De_Over_Note_1,		/*�����й���������*/
	CRev_Ac_De_Over_Note_1,		/*�����й���������*/
	CQua1_Re_De_Over_Note_1,	/*1�����޹���������*/
	CQua2_Re_De_Over_Note_1,	/*2�����޹���������*/
	CQua3_Re_De_Over_Note_1,	/*3�����޹���������*/
	CQua4_Re_De_Over_Note_1,	/*4�����޹���������*/
	CLossAVol_FF_1,			/*A��ʧѹ*/
	CLossBVol_FF_1,			/*B��ʧѹ*/
	CLossCVol_FF_1,			/*C��ʧѹ*/
	CLowAVol_FF_1,			/*A��Ƿѹ*/
	CLowBVol_FF_1,			/*B��Ƿѹ*/
	CLowCVol_FF_1,			/*C��Ƿѹ*/
	COverAVol_FF_1,			/*A���ѹ*/
	COverBVol_FF_1,			/*B���ѹ*/
	COverCVol_FF_1,			/*C���ѹ*/
	CBreakAVol_FF_1,		/*A�����*/
	CBreakBVol_FF_1,		/*B�����*/
	CBreakCVol_FF_1,		/*C�����*/
	CRevPSVol_FF_1,			/*��ѹ������*/
	CRevPSCurr_FF_1,		/*����������*/
	CNoBalVol_FF_1,			/*��ѹ��ƽ��*/
	CNoBalCurr_FF_1,		/*������ƽ��*/
	CLossACurr_FF_1,		/*A��ʧ��*/
	CLossBCurr_FF_1,		/*B��ʧ��*/
	CLossCCurr_FF_1,		/*C��ʧ��*/
	COverACurr_FF_1,		/*A�����*/
	COverBCurr_FF_1,		/*B�����*/
	COverCCurr_FF_1,		/*C�����*/
	CBreakACurr_FF_1,		/*A�����*/
	CBreakBCurr_FF_1,		/*B�����*/
	CBreakCCurr_FF_1,		/*C�����*/
	CPowerTRev_FF_1,		/*�ܹ��ʷ���*/
	CPowerARev_FF_1,		/*A�๦�ʷ���*/
	CPowerBRev_FF_1,		/*B�๦�ʷ���*/
	CPowerCRev_FF_1,		/*C�๦�ʷ���*/
	COverALo_FF_1,			/*A�����*/
	COverBLo_FF_1,			/*B�����*/
	COverCLo_FF_1,			/*C�����*/
	CPFactorT_FF_1,			/*�ܹ�������������*/
	CPFactorA_FF_1,		/*A�๦������������*/
	CPFactorB_FF_1,		/*B�๦������������*/
	CPFactorC_FF_1,		/*C�๦������������*/
	CSevNoBalCurr_FF_1,		/*�������ز�ƽ��*/
#if 0
	C_NULL,
#endif
	CMeterFa_Note_1,		/*����оƬ����*/
	CClockFa_Note_1,		/*ʱ�ӹ���*/
    CNeutralCurrentAbnormal_Note_1,   /*���ߵ����쳣*/
	CProgram_Note_1,		/*��̼�¼*/
	C_NULL,
	C_NULL,
	C_NULL,
	C_NULL,
	C_NULL,
	C_NULL,
	C_NULL,
	C_NULL,
	C_NULL,
	C_NULL,
	C_NULL,
	C_NULL,
	C_NULL,
	C_NULL,
	C_NULL,
	C_NULL,
	C_NULL,
	C_NULL,
	C_NULL,
	CRelayFa_Note_1,		/*���ɿ�������*/
};
#define EventHappenEndTime_Len  sizeof(EventHappenEndTime)/sizeof(ulong32)

/*****************************************************************************************/
/*����˳���������������*/
/*****************************************************************************************/
/*�����ݱ��*/
const Str_CommunicateReadTable_Type	CommunicateReadTable[C_ReadDataLength]=
{
/*	DataCode,					*DataRAMAddr,					*CRCRAMAddr,						Length,						EventNo*/
/*	���ݱ�ʶ��					����RAM��ַ��					�ṹ���׵�ַ��						���ݳ��ȣ�					�¼���*/
	{CAll_Loss_Vol_Time,		GStr_TotalvoltageloseStr.AddTime,	&GStr_TotalvoltageloseStr.MeterState,	C_AddTime_Length,			C_TotalVoltageLoseEventNo	},/*0 CAll_Loss_Volȫʧѹ�ܴ�����ʱ��*/
	{CAux_Pow_Down_Time,		GStr_ACPowerFailStr.AddTime,			&GStr_ACPowerFailStr.MeterState,			C_AddTime_Length,			C_ACPowerFailEventNo		},/*1 CAux_Pow_Down������Դ�ܴ�����ʱ��*/
	{CLossA_Vol_Time,			GStr_AlossvoltageStr.AddTime,		GStr_AlossvoltageStr.Renewal,			C_AddTime_Length,			C_AlossvoltageEventNo		},/*2 A��ʧѹ���ۼ�ʱ��*/
	{CLossB_Vol_Time,			GStr_BlossvoltageStr.AddTime,		GStr_BlossvoltageStr.Renewal,			C_AddTime_Length,			C_BlossvoltageEventNo		},/*3 B��ʧѹ���ۼ�ʱ��*/
	{CLossC_Vol_Time,			GStr_ClossvoltageStr.AddTime,		GStr_ClossvoltageStr.Renewal,			C_AddTime_Length,			C_ClossvoltageEventNo		},/*4 C��ʧѹ���ۼ�ʱ��*/
	{CLowA_Vol_Time,			GStr_ALessvoltageStr.AddTime,		GStr_ALessvoltageStr.Renewal,			C_AddTime_Length,			C_ALessvoltageEventNo		},/*5 A��Ƿѹ���ۼ�ʱ��*/
	{CLowB_Vol_Time,			GStr_BLessvoltageStr.AddTime,		GStr_BLessvoltageStr.Renewal,			C_AddTime_Length,			C_BLessvoltageEventNo		},/*6 B��Ƿѹ���ۼ�ʱ��*/
	{CLowC_Vol_Time,			GStr_CLessvoltageStr.AddTime,		GStr_CLessvoltageStr.Renewal,			C_AddTime_Length,			C_CLessvoltageEventNo		},/*7 C��Ƿѹ���ۼ�ʱ��*/
	{COverA_Vol_Time,			GStr_AOvervoltageStr.AddTime,		GStr_AOvervoltageStr.Renewal,			C_AddTime_Length,			C_AOvervoltageEventNo		},/*8 A���ѹ���ۼ�ʱ��*/
	{COverB_Vol_Time,			GStr_BOvervoltageStr.AddTime,		GStr_BOvervoltageStr.Renewal,			C_AddTime_Length,			C_BOvervoltageEventNo		},/*9 B���ѹ���ۼ�ʱ��*/
	{COverC_Vol_Time,			GStr_COvervoltageStr.AddTime,		GStr_COvervoltageStr.Renewal,			C_AddTime_Length,			C_COvervoltageEventNo		},/*10 C���ѹ���ۼ�ʱ��*/
	{CBreakA_Vol_Time,			GStr_ALossphaseStr.AddTime,			GStr_ALossphaseStr.Renewal,				C_AddTime_Length,			C_ALossphaseEventNo			},/*A��������ۼ�ʱ��*/
	{CBreakB_Vol_Time,			GStr_BLossphaseStr.AddTime,			GStr_BLossphaseStr.Renewal,				C_AddTime_Length,			C_BLossphaseEventNo			},/*B��������ۼ�ʱ��*/
	{CBreakC_Vol_Time,			GStr_CLossphaseStr.AddTime,			GStr_CLossphaseStr.Renewal,				C_AddTime_Length,			C_CLossphaseEventNo			},/*C��������ۼ�ʱ��*/
	{CRevPS_Vol_Time,			GStr_ReversephaseVoltageStr.AddTime,	GStr_ReversephaseVoltageStr.AddTime,  	C_AddTime_Length,			C_ReversephaseVoltageEventNo},/*��ѹ���������ۼ�ʱ��*/
	{CRevPS_Curr_Time,			GStr_ReversephaseCurrentStr.AddTime,	GStr_ReversephaseCurrentStr.AddTime,  	C_AddTime_Length,			C_ReversephaseCurrentEventNo},/*�������������ۼ�ʱ��*/
	{CNoBal_Vol_Time,			GStr_UnbanlanceVoltageStr.AddTime,	GStr_UnbanlanceVoltageStr.Renewal,		C_AddTime_Length,			C_UnbanlanceVoltageEventNo	},/*��ѹ��ƽ�����ۼ�ʱ��*/
	{CNoBal_Curr_Time,			GStr_UnbanlanceCurrentStr.AddTime,	GStr_UnbanlanceCurrentStr.Renewal,		C_AddTime_Length,			C_UnbanlanceCurrentEventNo	},/*������ƽ�����ۼ�ʱ��*/
	{CLossA_Curr_Time,			GStr_ALosscurrentStr.AddTime,		GStr_ALosscurrentStr.AddTime,			C_AddTime_Length,			C_ALosscurrentEventNo		},/*A��ʧ�����ۼ�ʱ��*/
	{CLossB_Curr_Time,			GStr_BLosscurrentStr.AddTime,		GStr_BLosscurrentStr.AddTime,			C_AddTime_Length,			C_BLosscurrentEventNo		},/*B��ʧ�����ۼ�ʱ��*/
	{CLossC_Curr_Time,			GStr_CLosscurrentStr.AddTime,		GStr_CLosscurrentStr.AddTime,			C_AddTime_Length,			C_CLosscurrentEventNo		},/*20C��ʧ�����ۼ�ʱ��*/
	{COverA_Curr_Time,			GStr_AOvercurrentStr.AddTime,		GStr_AOvercurrentStr.AddTime,			C_AddTime_Length,			C_AOvercurrentEventNo		},/*A��������ۼ�ʱ��*/
	{COverB_Curr_Time,			GStr_BOvercurrentStr.AddTime,		GStr_BOvercurrentStr.AddTime,			C_AddTime_Length,			C_BOvercurrentEventNo		},/*B��������ۼ�ʱ��*/
	{COverC_Curr_Time,			GStr_COvercurrentStr.AddTime,		GStr_COvercurrentStr.AddTime,			C_AddTime_Length,			C_COvercurrentEventNo		},/*C��������ۼ�ʱ��*/
	{CBreakA_Curr_Time,			GStr_AFailcurrentStr.AddTime,		GStr_AFailcurrentStr.AddTime,			C_AddTime_Length,			C_AFailcurrentEventNo		},/*A��������ۼ�ʱ��*/
	{CBreakB_Curr_Time,			GStr_BFailcurrentStr.AddTime,		GStr_BFailcurrentStr.AddTime,			C_AddTime_Length,			C_BFailcurrentEventNo		},/*B��������ۼ�ʱ��*/
	{CBreakC_Curr_Time,			GStr_CFailcurrentStr.AddTime,		GStr_CFailcurrentStr.AddTime,			C_AddTime_Length,			C_CFailcurrentEventNo		},/*C��������ۼ�ʱ��*/
	{CPowerT_Rev_Time,			GStr_TReversecurrentStr.AddTime,		GStr_TReversecurrentStr.AddTime,			C_AddTime_Length,			C_TReversecurrentEventNo	},/*�ܹ��ʷ������ۼ�ʱ��*/
	{CPowerA_Rev_Time,			GStr_AReversecurrentStr.AddTime,		GStr_AReversecurrentStr.AddTime,			C_AddTime_Length,			C_AReversecurrentEventNo	},/*A�๦�ʷ������ۼ�ʱ��*/
	{CPowerB_Rev_Time,			GStr_BReversecurrentStr.AddTime,		GStr_BReversecurrentStr.AddTime,			C_AddTime_Length,			C_BReversecurrentEventNo	},/*B�๦�ʷ������ۼ�ʱ��*/
	{CPowerC_Rev_Time,			GStr_CReversecurrentStr.AddTime,		GStr_CReversecurrentStr.AddTime,			C_AddTime_Length,			C_CReversecurrentEventNo	},/*C�๦�ʷ������ۼ�ʱ��*/
	{COverA_Lo_Time,			GStr_AOverloadStr.AddTime,			GStr_AOverloadStr.AddTime,				C_AddTime_Length,			C_AOverloadEventNo			},/*30A�����*/
	{COverB_Lo_Time,			GStr_BOverloadStr.AddTime,			GStr_BOverloadStr.AddTime,				C_AddTime_Length,			C_BOverloadEventNo			},/*B�����*/
	{COverC_Lo_Time,			GStr_COverloadStr.AddTime,			GStr_COverloadStr.AddTime,				C_AddTime_Length,			C_COverloadEventNo			},/*C�����*/
	{CPFactorT_Over_Time,		GStr_OverpowerfactStr.AddTime,		GStr_OverpowerfactStr.AddTime,			C_AddTime_Length,			C_OverpowerfactEventNo		},/*�ܹ�������������*/
	{CPFactorA_Over_Time,		GStr_AOverpowerfactStr.AddTime,		GStr_AOverpowerfactStr.AddTime,			C_AddTime_Length,			C_AOverpowerfactEventNo		},/*A�๦������������*/
	{CPFactorB_Over_Time,		GStr_BOverpowerfactStr.AddTime,		GStr_BOverpowerfactStr.AddTime,			C_AddTime_Length,			C_BOverpowerfactEventNo		},/*B�๦������������*/
	{CPFactorC_Over_Time,		GStr_COverpowerfactStr.AddTime,		GStr_COverpowerfactStr.AddTime,			C_AddTime_Length,			C_COverpowerfactEventNo		},/*36C�๦������������*/
	{CSevNoBal_Curr_Time,		GStr_SUnbanlanceCurrentStr.AddTime,	GStr_SUnbanlanceCurrentStr.Renewal,  	C_AddTime_Length,			C_SUnbanlanceCurrentEventNo	},/*37�������ز�ƽ��*/
	{CLoss_Vol_Degree,			0,								0,									C_AddNumber_Length,			0							},/*38 ʧѹ�ܴ���*/
	{CLoss_Vol_Time,			0,								0,									C_AddTime_Length,			0							},/*39 ʧѹ��ʱ��*/
	{CPos_Ac_De_Over_1,	GStr_OverForwardActiveStr.Renewal,	GStr_OverForwardActiveStr.Renewal,		C_OverDemandRenew_Length,	C_OverForwardActiveEventNo	},/*40�����й�����������*/
	{CRev_Ac_De_Over_1,	GStr_OverReverseActiveStr.Renewal,	GStr_OverReverseActiveStr.Renewal,		C_OverDemandRenew_Length,	C_OverReverseActiveEventNo	},/*41�����й�����������*/
	{CQua1_Re_De_Over_1,	GStr_Over1IdleDemandStr.Renewal,		GStr_Over1IdleDemandStr.Renewal,	  		C_OverDemandRenew_Length,	C_1OverIdleDemandEventNo	},/*1�����޹�����������*/
	{CQua2_Re_De_Over_1,	GStr_Over2IdleDemandStr.Renewal,		GStr_Over2IdleDemandStr.Renewal,	  		C_OverDemandRenew_Length,	C_2OverIdleDemandEventNo	},/*2�����޹�����������*/
	{CQua3_Re_De_Over_1,	GStr_Over3IdleDemandStr.Renewal,		GStr_Over3IdleDemandStr.Renewal,	  		C_OverDemandRenew_Length,	C_3OverIdleDemandEventNo	},/*3�����޹�����������*/
	{CQua4_Re_De_Over_1,	GStr_Over4IdleDemandStr.Renewal,		GStr_Over4IdleDemandStr.Renewal,	  		C_OverDemandRenew_Length,	C_4OverIdleDemandEventNo	},/*4�����޹�����������*/
	{CLossAVol_TolAh_1,			GStr_AlossvoltageStr.Renewal,		GStr_AlossvoltageStr.Renewal,			C_Ah_Length,				C_AlossvoltageEventNo		},/*��1��A��ʧѹ�ڼ���Ah��*/
	{CLossAVol_AAh_1,			GStr_AlossvoltageStr.ARenewal,		GStr_AlossvoltageStr.Renewal,			C_Ah_Length,				C_AlossvoltageEventNo		},/*��1��A��ʧѹ�ڼ�A��Ah��*/
	{CLossAVol_BAh_1,			GStr_AlossvoltageStr.BRenewal,		GStr_AlossvoltageStr.Renewal,			C_Ah_Length,				C_AlossvoltageEventNo		},/*��1��A��ʧѹ�ڼ�B��Ah��*/
	{CLossAVol_CAh_1,			GStr_AlossvoltageStr.CRenewal,		GStr_AlossvoltageStr.Renewal,			C_Ah_Length,				C_AlossvoltageEventNo		},/*��1��A��ʧѹ�ڼ�C��Ah��*/
	{CLossBVol_TolAh_1,			GStr_BlossvoltageStr.Renewal,		GStr_BlossvoltageStr.Renewal,			C_Ah_Length,				C_BlossvoltageEventNo		},/*50��1��B��ʧѹ�ڼ���Ah��*/
	{CLossBVol_AAh_1,			GStr_BlossvoltageStr.ARenewal,		GStr_BlossvoltageStr.Renewal,			C_Ah_Length,				C_BlossvoltageEventNo		},/*��1��B��ʧѹ�ڼ�A��Ah��*/
	{CLossBVol_BAh_1,			GStr_BlossvoltageStr.BRenewal,		GStr_BlossvoltageStr.Renewal,			C_Ah_Length,				C_BlossvoltageEventNo		},/*��1��B��ʧѹ�ڼ�B��Ah��*/
	{CLossBVol_CAh_1,			GStr_BlossvoltageStr.CRenewal,		GStr_BlossvoltageStr.Renewal,			C_Ah_Length,				C_BlossvoltageEventNo		},/*��1��B��ʧѹ�ڼ�C��Ah��*/
	{CLossCVol_TolAh_1,			GStr_ClossvoltageStr.Renewal,		GStr_ClossvoltageStr.Renewal,			C_Ah_Length,				C_ClossvoltageEventNo		},/*��1��C��ʧѹ�ڼ���Ah��*/
	{CLossCVol_AAh_1,			GStr_ClossvoltageStr.ARenewal,		GStr_ClossvoltageStr.Renewal,			C_Ah_Length,				C_ClossvoltageEventNo		},/*��1��C��ʧѹ�ڼ�A��Ah��*/
	{CLossCVol_BAh_1,			GStr_ClossvoltageStr.BRenewal,		GStr_ClossvoltageStr.Renewal,			C_Ah_Length,				C_ClossvoltageEventNo		},/*��1��C��ʧѹ�ڼ�B��Ah��*/
	{CLossCVol_CAh_1,			GStr_ClossvoltageStr.CRenewal,		GStr_ClossvoltageStr.Renewal,			C_Ah_Length,				C_ClossvoltageEventNo		},/*��1��C��ʧѹ�ڼ�C��Ah��*/
	{CLowAVol_TolAh_1,			GStr_ALessvoltageStr.Renewal,		GStr_ALessvoltageStr.Renewal,			C_Ah_Length,				C_ALessvoltageEventNo		},/*��1��A��Ƿѹ�ڼ���Ah��*/
	{CLowAVol_AAh_1,			GStr_ALessvoltageStr.ARenewal,		GStr_ALessvoltageStr.Renewal,			C_Ah_Length,				C_ALessvoltageEventNo		},/**/
	{CLowAVol_BAh_1,			GStr_ALessvoltageStr.BRenewal,		GStr_ALessvoltageStr.Renewal,			C_Ah_Length,				C_ALessvoltageEventNo		},/*60*/
	{CLowAVol_CAh_1,			GStr_ALessvoltageStr.CRenewal,		GStr_ALessvoltageStr.Renewal,			C_Ah_Length,				C_ALessvoltageEventNo		},/**/
	{CLowBVol_TolAh_1,			GStr_BLessvoltageStr.Renewal,		GStr_BLessvoltageStr.Renewal,			C_Ah_Length,				C_BLessvoltageEventNo		},/*��1��B��Ƿѹ�ڼ���Ah��*/
	{CLowBVol_AAh_1,			GStr_BLessvoltageStr.ARenewal,		GStr_BLessvoltageStr.Renewal,			C_Ah_Length,				C_BLessvoltageEventNo		},/**/
	{CLowBVol_BAh_1,			GStr_BLessvoltageStr.BRenewal,		GStr_BLessvoltageStr.Renewal,			C_Ah_Length,				C_BLessvoltageEventNo		},/**/
	{CLowBVol_CAh_1,			GStr_BLessvoltageStr.CRenewal,		GStr_BLessvoltageStr.Renewal,			C_Ah_Length,				C_BLessvoltageEventNo		},/**/
	{CLowCVol_TolAh_1,			GStr_CLessvoltageStr.Renewal,		GStr_CLessvoltageStr.Renewal,			C_Ah_Length,				C_CLessvoltageEventNo		},/*��1��C��Ƿѹ�ڼ���Ah��*/
	{CLowCVol_AAh_1,			GStr_CLessvoltageStr.ARenewal,		GStr_CLessvoltageStr.Renewal,			C_Ah_Length,				C_CLessvoltageEventNo		},/**/
	{CLowCVol_BAh_1,			GStr_CLessvoltageStr.BRenewal,		GStr_CLessvoltageStr.Renewal,			C_Ah_Length,				C_CLessvoltageEventNo		},/**/
	{CLowCVol_CAh_1,			GStr_CLessvoltageStr.CRenewal,		GStr_CLessvoltageStr.Renewal,			C_Ah_Length,				C_CLessvoltageEventNo		},/**/
	{COverAVol_TolAh_1,			GStr_AOvervoltageStr.Renewal,		GStr_AOvervoltageStr.Renewal,			C_Ah_Length,				C_AOvervoltageEventNo		},/*70��1��A���ѹ�ڼ���Ah��*/
	{COverAVol_AAh_1,			GStr_AOvervoltageStr.ARenewal,		GStr_AOvervoltageStr.Renewal,			C_Ah_Length,				C_AOvervoltageEventNo		},/**/
	{COverAVol_BAh_1,			GStr_AOvervoltageStr.BRenewal,		GStr_AOvervoltageStr.Renewal,			C_Ah_Length,				C_AOvervoltageEventNo		},/**/
	{COverAVol_CAh_1,			GStr_AOvervoltageStr.CRenewal,		GStr_AOvervoltageStr.Renewal,			C_Ah_Length,				C_AOvervoltageEventNo		},/**/
	{COverBVol_TolAh_1,			GStr_BOvervoltageStr.Renewal,		GStr_BOvervoltageStr.Renewal,			C_Ah_Length,				C_BOvervoltageEventNo		},/*��1��B���ѹ�ڼ���Ah��*/
	{COverBVol_AAh_1,			GStr_BOvervoltageStr.ARenewal,		GStr_BOvervoltageStr.Renewal,			C_Ah_Length,				C_BOvervoltageEventNo		},/**/
	{COverBVol_BAh_1,			GStr_BOvervoltageStr.BRenewal,		GStr_BOvervoltageStr.Renewal,			C_Ah_Length,				C_BOvervoltageEventNo		},/**/
	{COverBVol_CAh_1,			GStr_BOvervoltageStr.CRenewal,		GStr_BOvervoltageStr.Renewal,			C_Ah_Length,				C_BOvervoltageEventNo		},/**/
	{COverCVol_TolAh_1,			GStr_COvervoltageStr.Renewal,		GStr_COvervoltageStr.Renewal,			C_Ah_Length,				C_COvervoltageEventNo		},/*��1��C���ѹ�ڼ���Ah��*/
	{COverCVol_AAh_1,			GStr_COvervoltageStr.ARenewal,		GStr_COvervoltageStr.Renewal,			C_Ah_Length,				C_COvervoltageEventNo		},/**/
	{COverCVol_BAh_1,			GStr_COvervoltageStr.BRenewal,		GStr_COvervoltageStr.Renewal,			C_Ah_Length,				C_COvervoltageEventNo		},/*80*/
	{COverCVol_CAh_1,			GStr_COvervoltageStr.CRenewal,		GStr_COvervoltageStr.Renewal,			C_Ah_Length,				C_COvervoltageEventNo		},/**/
	{CBreakAVol_TolAh_1,		GStr_ALossphaseStr.Renewal,			GStr_ALossphaseStr.Renewal,				C_Ah_Length,				C_ALossphaseEventNo			},/*��1��A������ڼ���Ah��*/
	{CBreakAVol_AAh_1,			GStr_ALossphaseStr.ARenewal,			GStr_ALossphaseStr.Renewal,				C_Ah_Length,				C_ALossphaseEventNo			},/**/
	{CBreakAVol_BAh_1,			GStr_ALossphaseStr.BRenewal,			GStr_ALossphaseStr.Renewal,				C_Ah_Length,				C_ALossphaseEventNo			},/**/
	{CBreakAVol_CAh_1,			GStr_ALossphaseStr.CRenewal,			GStr_ALossphaseStr.Renewal,				C_Ah_Length,				C_ALossphaseEventNo			},/**/
	{CBreakBVol_TolAh_1,		GStr_BLossphaseStr.Renewal,			GStr_BLossphaseStr.Renewal,				C_Ah_Length,				C_BLossphaseEventNo			},/*��1��B������ڼ���Ah��*/
	{CBreakBVol_AAh_1,			GStr_BLossphaseStr.ARenewal,			GStr_BLossphaseStr.Renewal,				C_Ah_Length,				C_BLossphaseEventNo			},/**/
	{CBreakBVol_BAh_1,			GStr_BLossphaseStr.BRenewal,			GStr_BLossphaseStr.Renewal,				C_Ah_Length,				C_BLossphaseEventNo			},/**/
	{CBreakBVol_CAh_1,			GStr_BLossphaseStr.CRenewal,			GStr_BLossphaseStr.Renewal,				C_Ah_Length,				C_BLossphaseEventNo			},/**/
	{CBreakCVol_TolAh_1,		GStr_CLossphaseStr.Renewal,			GStr_CLossphaseStr.Renewal,				C_Ah_Length,				C_CLossphaseEventNo			},/*90��1��C������ڼ���Ah��*/
	{CBreakCVol_AAh_1,			GStr_CLossphaseStr.ARenewal,			GStr_CLossphaseStr.Renewal,				C_Ah_Length,				C_CLossphaseEventNo			},/**/
	{CBreakCVol_BAh_1,			GStr_CLossphaseStr.BRenewal,			GStr_CLossphaseStr.Renewal,				C_Ah_Length,				C_CLossphaseEventNo			},/**/
	{CBreakCVol_CAh_1,			GStr_CLossphaseStr.CRenewal,			GStr_CLossphaseStr.Renewal,				C_Ah_Length,				C_CLossphaseEventNo			},/**/
	{CNoBalRate_Vol_End_1,		GStr_UnbanlanceVoltageStr.Renewal,	GStr_UnbanlanceVoltageStr.Renewal,		C_Unbalance_Length,			C_UnbanlanceVoltageEventNo	},/*94��1�ε�ѹ��ƽ���¼������ڼ����ƽ����*/
	{CNoBalRate_Curr_1,			GStr_UnbanlanceCurrentStr.Renewal,	GStr_UnbanlanceCurrentStr.Renewal,		C_Unbalance_Length,			C_UnbanlanceCurrentEventNo	},/*��1�ε�����ƽ���¼������ڼ����ƽ����*/
	{CSevNoBalRate_Curr_1,		GStr_SUnbanlanceCurrentStr.Renewal,	GStr_SUnbanlanceCurrentStr.Renewal,		C_Unbalance_Length,			C_SUnbanlanceCurrentEventNo	},/*��1�ε������ز�ƽ���¼������ڼ����ƽ����*/
    {CLoss_Vol_Hp,              0,                              0,	                                C_EventTimeLength,          0                           },/*��1��ʧѹ����ʱ��*/
    {CLoss_Vol_End,             0,                              0,	                                C_EventTimeLength,          0                           }, /*��1��ʧѹ����ʱ��*/
	{CPow_Down_Time,			GStr_PowerfailStr.AddTime,			&GStr_PowerfailStr.MeterState,			C_AddTime_Length,			C_PowerfailEventNo			},/*�����ۼ�ʱ��*/
	{COpenW_Time,				GStr_OpenMeterCoverStr.AddTime,		&GStr_OpenMeterCoverStr.OpenCoverState,		C_AddTime_Length,			C_OpenMeterCoverEventNo			},/*������ۼ�ʱ��*/
	{COpenCW_Time,				GStr_OpenTerminalCoverStr.AddTime,		&GStr_OpenTerminalCoverStr.OpenCoverState,		C_AddTime_Length,		C_OpenTerminalCoverEventNo		},/*����ť�Ǽ�ʱ��*/
	{CConM_Time,				GStr_ConMStr.AddTime,			GStr_ConMStr.AddTime,				C_AddTime_Length,			C_MagneticCheckEventNo			},/*�㶨�ų������ۼ�ʱ��*/
	{CPowerFa_Time,				GStr_PowerabnormalStr.AddTime,		&GStr_PowerabnormalStr.MeterState,			C_AddTime_Length,			C_PowerAbnormalEventNo			},/*��Դ�쳣��ʱ��*/
	{CPos_Ac_De_Over_Time,			GStr_OverForwardActiveStr.AddTime,		&GStr_OverForwardActiveStr.MeterState,		C_AddTime_Length,			C_OverForwardActiveEventNo		},/*�����й����������ۼ�ʱ��*/
	{CRev_Ac_De_Over_Time,			GStr_OverReverseActiveStr.AddTime,		&GStr_OverReverseActiveStr.MeterState,		C_AddTime_Length,			C_OverReverseActiveEventNo		},/*�����й����������ۼ�ʱ��*/
	{CQua1_Re_De_Over_Time,			GStr_Over1IdleDemandStr.AddTime,		&GStr_Over1IdleDemandStr.MeterState,			C_AddTime_Length,			C_1OverIdleDemandEventNo		},/*1�����޹����������ۼ�ʱ��*/
	{CQua2_Re_De_Over_Time,			GStr_Over2IdleDemandStr.AddTime,		&GStr_Over2IdleDemandStr.MeterState,			C_AddTime_Length,			C_2OverIdleDemandEventNo		},/*2�����޹����������ۼ�ʱ��*/
	{CQua3_Re_De_Over_Time,			GStr_Over3IdleDemandStr.AddTime,		&GStr_Over3IdleDemandStr.MeterState,			C_AddTime_Length,			C_3OverIdleDemandEventNo		},/*3�����޹����������ۼ�ʱ��*/
	{CQua4_Re_De_Over_Time,			GStr_Over4IdleDemandStr.AddTime,		&GStr_Over4IdleDemandStr.MeterState,			C_AddTime_Length,			C_4OverIdleDemandEventNo		},/*4�����޹����������ۼ�ʱ��*/
	{CMeterFa_Time,				GStr_MeterFaStr.AddTime,			GStr_MeterFaStr.AddTime,				C_AddTime_Length,			C_MeterFaEventNo			},/*����оƬ�����ۼ�ʱ��*/
	{CClockFa_Time,				GStr_ClockFaStr.AddTime,			GStr_ClockFaStr.AddTime,				C_AddTime_Length,			C_ClockFaEventNo			},/*ʱ�ӹ����ۼ�ʱ��*/
	{CNeutralCurrentAbnormal_Time,GStr_NeutralAbnormalStr.AddTime,GStr_NeutralAbnormalStr.AddTime,C_AddTime_Length,C_NeutralCurrentAbnormalEventNo},/*���ߵ����쳣�ۼ�ʱ��*/
#if 0
	{CBroadcastTime_Time,GStr_BroadcastTimeStr.AddTime,GStr_BroadcastTimeStr.AddTime,C_AddTime_Length,C_BroadcastTimeEventNo},/*�㲥Уʱ�ۼ�ʱ��*/
#endif
};
#define C_EventNum_AddTime38    38  /*�ϱ��CommunicateReadTableǰ38��*/
#define C_EventNum_AddTime100   100  /*�ϱ��CommunicateReadTable��100��*/
#define C_EventNum_AddTime110   110  /*�ϱ��CommunicateReadTable��110��*/
#define C_EventNum_AddTime113   113  /*�ϱ��CommunicateReadTable��113��*/
#define CLoss_Vol_Degree_offset 39   /*ʧѹ�������ϱ��CommunicateReadTable��39��*/
#define CLoss_Vol_Time_offset   40   /*ʧѹʱ�����ϱ��CommunicateReadTable��40��*/

/*****************************************************************************************/
/*����˳���������������*/
/*****************************************************************************************/
const Str_AhCountTable_Type Str_RAMAhTable1[12]=	/*Ah����ַ*/
{/*��Ah��RAM�е�ַ			A��Ah��RAM��ַ				B��Ah��RAM��ַ				C��Ah��RAM��ַ*/
	{GStr_AlossvoltageStr.Renewal,	GStr_AlossvoltageStr.ARenewal,	GStr_AlossvoltageStr.BRenewal,	GStr_AlossvoltageStr.CRenewal},
	{GStr_BlossvoltageStr.Renewal,	GStr_BlossvoltageStr.ARenewal,	GStr_BlossvoltageStr.BRenewal,	GStr_BlossvoltageStr.CRenewal},
	{GStr_ClossvoltageStr.Renewal,	GStr_ClossvoltageStr.ARenewal,	GStr_ClossvoltageStr.BRenewal,	GStr_ClossvoltageStr.CRenewal},
	{GStr_ALessvoltageStr.Renewal,	GStr_ALessvoltageStr.ARenewal,	GStr_ALessvoltageStr.BRenewal,	GStr_ALessvoltageStr.CRenewal},
	{GStr_BLessvoltageStr.Renewal,	GStr_BLessvoltageStr.ARenewal,	GStr_BLessvoltageStr.BRenewal,	GStr_BLessvoltageStr.CRenewal},
	{GStr_CLessvoltageStr.Renewal,	GStr_CLessvoltageStr.ARenewal,	GStr_CLessvoltageStr.BRenewal,	GStr_CLessvoltageStr.CRenewal},
	{GStr_AOvervoltageStr.Renewal,	GStr_AOvervoltageStr.ARenewal,	GStr_AOvervoltageStr.BRenewal,	GStr_AOvervoltageStr.CRenewal},
	{GStr_BOvervoltageStr.Renewal,	GStr_BOvervoltageStr.ARenewal,	GStr_BOvervoltageStr.BRenewal,	GStr_BOvervoltageStr.CRenewal},
	{GStr_COvervoltageStr.Renewal,	GStr_COvervoltageStr.ARenewal,	GStr_COvervoltageStr.BRenewal,	GStr_COvervoltageStr.CRenewal},
	{GStr_ALossphaseStr.Renewal,		GStr_ALossphaseStr.ARenewal,		GStr_ALossphaseStr.BRenewal,		GStr_ALossphaseStr.CRenewal  },
	{GStr_BLossphaseStr.Renewal,		GStr_BLossphaseStr.ARenewal,		GStr_BLossphaseStr.BRenewal,		GStr_BLossphaseStr.CRenewal	},
	{GStr_CLossphaseStr.Renewal,		GStr_CLossphaseStr.ARenewal,		GStr_CLossphaseStr.BRenewal,		GStr_CLossphaseStr.CRenewal	},
};
/*****************************************************************************************/
/*����˳���������������*/
/*****************************************************************************************/
const Str_AhCountTable_Type Str_RAMAhTable2[12]=								/*����0.01Ah��ַ*/
{/*�ܲ���0.0Ah��RAM�е�ַ	A�಻��0.01Ah��RAM��ַ	B�಻��0.01Ah��RAM��ַ	C�಻��0.01Ah��RAM��ַ*/
	{GStr_AlossvoltageStr.Ah,	GStr_AlossvoltageStr.AAh,	GStr_AlossvoltageStr.BAh,	GStr_AlossvoltageStr.CAh	},
	{GStr_BlossvoltageStr.Ah,	GStr_BlossvoltageStr.AAh,	GStr_BlossvoltageStr.BAh,	GStr_BlossvoltageStr.CAh	},
	{GStr_ClossvoltageStr.Ah,	GStr_ClossvoltageStr.AAh,	GStr_ClossvoltageStr.BAh,	GStr_ClossvoltageStr.CAh	},
	{GStr_ALessvoltageStr.Ah,	GStr_ALessvoltageStr.AAh,	GStr_ALessvoltageStr.BAh,	GStr_ALessvoltageStr.CAh	},
	{GStr_BLessvoltageStr.Ah,	GStr_BLessvoltageStr.AAh,	GStr_BLessvoltageStr.BAh,	GStr_BLessvoltageStr.CAh	},
	{GStr_CLessvoltageStr.Ah,	GStr_CLessvoltageStr.AAh,	GStr_CLessvoltageStr.BAh,	GStr_CLessvoltageStr.CAh	},
	{GStr_AOvervoltageStr.Ah,	GStr_AOvervoltageStr.AAh,	GStr_AOvervoltageStr.BAh,	GStr_AOvervoltageStr.CAh	},
	{GStr_BOvervoltageStr.Ah,	GStr_BOvervoltageStr.AAh,	GStr_BOvervoltageStr.BAh,	GStr_BOvervoltageStr.CAh	},
	{GStr_COvervoltageStr.Ah,	GStr_COvervoltageStr.AAh,	GStr_COvervoltageStr.BAh,	GStr_COvervoltageStr.CAh	},
	{GStr_ALossphaseStr.Ah,		GStr_ALossphaseStr.AAh,		GStr_ALossphaseStr.BAh,		GStr_ALossphaseStr.CAh	},
	{GStr_BLossphaseStr.Ah,		GStr_BLossphaseStr.AAh,		GStr_BLossphaseStr.BAh,		GStr_BLossphaseStr.CAh	},
	{GStr_CLossphaseStr.Ah,		GStr_CLossphaseStr.AAh,		GStr_CLossphaseStr.BAh,		GStr_CLossphaseStr.CAh 	},
};
/*****************************************************************************************/
/*����˳���������������*/
/*****************************************************************************************/
/*������1*/
const Str_CommunicateEventClearTable_Type CommunicateEventClearTable[C_EventNoLength]=
{
	/*RAM��ַ									CRC��ַ							����							   		״̬�ֵ�ַ			   ƫ����(����ʱ) ƫ������������С����						�������					����					��������ʱ		��������ʱ*/
	{&GStr_TotalvoltageloseStr.MeterState,		GStr_TotalvoltageloseStr.V_CRC,		sizeof(Str_LpowerTvoltagelose_Type),	0,						0,				0,			&GStr_BellAlarm.T1_Flag,	&GStr_Alarmoutput.T1_Flag,	&GStr_BackLightAlarm.T1_Flag,	C_Bit4_Start,	C_Bit4_End	},/*ȫʧѹ*/
	{&GStr_ACPowerFailStr.MeterState,			GStr_ACPowerFailStr.V_CRC,			sizeof(Str_ACPowerFail_Type),			CMeter_Work_State7,		C_Bit4_Start,	C_Bit4_End,	0,						0,							0,								0,				0			},/*������Դʧ��*/
	{&GStr_PowerfailStr.MeterState,				GStr_PowerfailStr.V_CRC,				sizeof(Str_LpowerTvoltagelose_Type),	CMeter_Work_State7,		C_Bit5_Start,	C_Bit5_End,	0,						0,							0,								0,				0			},/*����*/
	{&GStr_OpenMeterCoverStr.OpenCoverState,		GStr_OpenMeterCoverStr.V_CRC,		sizeof(Str_CoverRecord_Type),			CMeter_Work_State7,		C_Bit1_Start,	C_Bit1_End,	&GStr_BellAlarm.T1_Flag,	&GStr_Alarmoutput.T1_Flag,	&GStr_BackLightAlarm.T1_Flag,	C_Bit1_Start,	C_Bit1_End	},/*�����*/
	{&GStr_OpenTerminalCoverStr.OpenCoverState,	GStr_OpenTerminalCoverStr.V_CRC,  	sizeof(Str_CoverRecord_Type),			CMeter_Work_State7,		C_Bit2_Start,	C_Bit2_End,	&GStr_BellAlarm.T1_Flag,	&GStr_Alarmoutput.T1_Flag,	&GStr_BackLightAlarm.T1_Flag,	C_Bit2_Start,	C_Bit2_End	},/*����ť��*/
	{GStr_ConMStr.AddTime,						GStr_ConMStr.V_CRC,					sizeof(Str_OtherMeter_Type),			0,						0,				0,			0,						0,							0,								0,				0			},/*�㶨�ų�����*/
	{&GStr_PowerabnormalStr.MeterState,			GStr_PowerabnormalStr.V_CRC,			sizeof(Str_ACPowerFail_Type),			0,						0,				0,			0,						0,							0,								0,				0			},/*��Դ�쳣*/
	{GStr_OverForwardActiveStr.Renewal,			GStr_OverForwardActiveStr.V_CRC,		sizeof(Str_ActiveDemand_Type),			CMeter_Work_State7,		C_Bit6_Start,	C_Bit6_End,	&GStr_BellAlarm.T1_Flag,	&GStr_Alarmoutput.T1_Flag,	&GStr_BackLightAlarm.T1_Flag,	C_Bit0_Start,	C_Bit0_End	},/*�����й���������*/
	{GStr_OverReverseActiveStr.Renewal,			GStr_OverReverseActiveStr.V_CRC,		sizeof(Str_ActiveDemand_Type),			CMeter_Work_State7,		C_Bit6_Start,	C_Bit6_End,	&GStr_BellAlarm.T1_Flag,	&GStr_Alarmoutput.T1_Flag,	&GStr_BackLightAlarm.T1_Flag,	C_Bit0_Start,	C_Bit0_End	},/*�����й���������*/
	{GStr_Over1IdleDemandStr.Renewal,			GStr_Over1IdleDemandStr.V_CRC,		sizeof(Str_ActiveDemand_Type),			CMeter_Work_State7,		C_Bit6_Start,	C_Bit6_End,	0,						0,							0,								0,				0			},/*1�����޹���������*/
	{GStr_Over2IdleDemandStr.Renewal,			GStr_Over2IdleDemandStr.V_CRC,		sizeof(Str_ActiveDemand_Type),			CMeter_Work_State7,		C_Bit6_Start,	C_Bit6_End,	0,						0,							0,								0,				0			},/*2�����޹���������*/
	{GStr_Over3IdleDemandStr.Renewal,			GStr_Over3IdleDemandStr.V_CRC,		sizeof(Str_ActiveDemand_Type),			CMeter_Work_State7,		C_Bit6_Start,	C_Bit6_End,	0,						0,							0,								0,				0			},/*3�����޹���������*/
	{GStr_Over4IdleDemandStr.Renewal,			GStr_Over4IdleDemandStr.V_CRC,		sizeof(Str_ActiveDemand_Type),			CMeter_Work_State7,		C_Bit6_Start,	C_Bit6_End,	0,						0,							0,								0,				0			},/*4�����޹���������*/
	{GStr_AlossvoltageStr.Renewal,				GStr_AlossvoltageStr.V_CRC,			sizeof(Str_AhMeter_Type),				CMeter_Work_State4,		C_Bit0_Start,	C_Bit0_End,	&GStr_BellAlarm.A0_Flag,	&GStr_Alarmoutput.A0_Flag,	&GStr_BackLightAlarm.A0_Flag,	C_Bit0_Start,	C_Bit0_End	},/*A��ʧѹ*/
	{GStr_BlossvoltageStr.Renewal,				GStr_BlossvoltageStr.V_CRC,			sizeof(Str_AhMeter_Type),				CMeter_Work_State5,		C_Bit0_Start,	C_Bit0_End,	&GStr_BellAlarm.B0_Flag,	&GStr_Alarmoutput.B0_Flag,	&GStr_BackLightAlarm.B0_Flag,	C_Bit0_Start,	C_Bit0_End	},/*B��ʧѹ*/
	{GStr_ClossvoltageStr.Renewal,				GStr_ClossvoltageStr.V_CRC,			sizeof(Str_AhMeter_Type),				CMeter_Work_State6,		C_Bit0_Start,	C_Bit0_End,	&GStr_BellAlarm.C0_Flag,	&GStr_Alarmoutput.C0_Flag,	&GStr_BackLightAlarm.C0_Flag,	C_Bit0_Start,	C_Bit0_End	},/*C��ʧѹ*/
	{GStr_ALessvoltageStr.Renewal,				GStr_ALessvoltageStr.V_CRC,			sizeof(Str_AhMeter_Type),				CMeter_Work_State4,		C_Bit1_Start,	C_Bit1_End,	&GStr_BellAlarm.A0_Flag,	&GStr_Alarmoutput.A0_Flag,	&GStr_BackLightAlarm.A0_Flag,	C_Bit7_Start,	C_Bit7_End	},/*A��Ƿѹ*/
	{GStr_BLessvoltageStr.Renewal,				GStr_BLessvoltageStr.V_CRC,			sizeof(Str_AhMeter_Type),				CMeter_Work_State5,		C_Bit1_Start,	C_Bit1_End,	&GStr_BellAlarm.B0_Flag,	&GStr_Alarmoutput.B0_Flag,	&GStr_BackLightAlarm.B0_Flag,	C_Bit7_Start,	C_Bit7_End	},/*B��Ƿѹ*/
	{GStr_CLessvoltageStr.Renewal,				GStr_CLessvoltageStr.V_CRC,			sizeof(Str_AhMeter_Type),				CMeter_Work_State6,		C_Bit1_Start,	C_Bit1_End,	&GStr_BellAlarm.C0_Flag,	&GStr_Alarmoutput.C0_Flag,	&GStr_BackLightAlarm.C0_Flag,	C_Bit7_Start,	C_Bit7_End	},/*C��Ƿѹ*/
	{GStr_AOvervoltageStr.Renewal,				GStr_AOvervoltageStr.V_CRC,			sizeof(Str_AhMeter_Type),				CMeter_Work_State4,		C_Bit2_Start,	C_Bit2_End,	&GStr_BellAlarm.A0_Flag,	&GStr_Alarmoutput.A0_Flag,	&GStr_BackLightAlarm.A0_Flag,	C_Bit6_Start,	C_Bit6_End	},/*A���ѹ*/
	{GStr_BOvervoltageStr.Renewal,				GStr_BOvervoltageStr.V_CRC,			sizeof(Str_AhMeter_Type),				CMeter_Work_State5,		C_Bit2_Start,	C_Bit2_End,	&GStr_BellAlarm.B0_Flag,	&GStr_Alarmoutput.B0_Flag,	&GStr_BackLightAlarm.B0_Flag,	C_Bit6_Start,	C_Bit6_End	},/*B���ѹ*/
	{GStr_COvervoltageStr.Renewal,				GStr_COvervoltageStr.V_CRC,			sizeof(Str_AhMeter_Type),				CMeter_Work_State6,		C_Bit2_Start,	C_Bit2_End,	&GStr_BellAlarm.C0_Flag,	&GStr_Alarmoutput.C0_Flag,	&GStr_BackLightAlarm.C0_Flag,	C_Bit6_Start,	C_Bit6_End	},/*C���ѹ*/
	{GStr_ALossphaseStr.Renewal,					GStr_ALossphaseStr.V_CRC,			sizeof(Str_AhMeter_Type),				CMeter_Work_State4,		C_Bit7_Start,	C_Bit7_End,	&GStr_BellAlarm.A0_Flag,	&GStr_Alarmoutput.A0_Flag,	&GStr_BackLightAlarm.A0_Flag,	C_Bit4_Start,	C_Bit4_End	},/*A�����*/
	{GStr_BLossphaseStr.Renewal,					GStr_BLossphaseStr.V_CRC,			sizeof(Str_AhMeter_Type),				CMeter_Work_State5,		C_Bit7_Start,	C_Bit7_End,	&GStr_BellAlarm.B0_Flag,	&GStr_Alarmoutput.B0_Flag,	&GStr_BackLightAlarm.B0_Flag,	C_Bit4_Start,	C_Bit4_End	},/*B�����*/
	{GStr_CLossphaseStr.Renewal,					GStr_CLossphaseStr.V_CRC,			sizeof(Str_AhMeter_Type),				CMeter_Work_State6,		C_Bit7_Start,	C_Bit7_End,	&GStr_BellAlarm.C0_Flag,	&GStr_Alarmoutput.C0_Flag,	&GStr_BackLightAlarm.C0_Flag,	C_Bit4_Start,	C_Bit4_End	},/*C�����*/
	{GStr_ReversephaseVoltageStr.AddTime,		GStr_ReversephaseVoltageStr.V_CRC,	sizeof(Str_OtherMeter_Type),			CMeter_Work_State7,		C_Bit0_Start,	C_Bit0_End,	&GStr_BellAlarm.T0_Flag,	&GStr_Alarmoutput.T0_Flag,	&GStr_BackLightAlarm.T0_Flag,	C_Bit0_Start,	C_Bit0_End	},/*��ѹ������*/
	{GStr_ReversephaseCurrentStr.AddTime,		GStr_ReversephaseCurrentStr.V_CRC,	sizeof(Str_OtherMeter_Type),			CMeter_Work_State7,		C_Bit1_Start,	C_Bit1_End,	&GStr_BellAlarm.T0_Flag,	&GStr_Alarmoutput.T0_Flag,	&GStr_BackLightAlarm.T0_Flag,	C_Bit1_Start,	C_Bit1_End	},/*����������*/
	{GStr_UnbanlanceVoltageStr.Renewal,			GStr_UnbanlanceVoltageStr.V_CRC,		sizeof(Str_Unbanlance_Type),			CMeter_Work_State7,		C_Bit2_Start,	C_Bit2_End,	&GStr_BellAlarm.T0_Flag,	&GStr_Alarmoutput.T0_Flag,	&GStr_BackLightAlarm.T0_Flag,	C_Bit5_Start,	C_Bit5_End	},/*��ѹ��ƽ��*/
	{GStr_UnbanlanceCurrentStr.Renewal,			GStr_UnbanlanceCurrentStr.V_CRC,		sizeof(Str_Unbanlance_Type),			CMeter_Work_State7,		C_Bit3_Start,	C_Bit3_End,	&GStr_BellAlarm.T0_Flag,	&GStr_Alarmoutput.T0_Flag,	&GStr_BackLightAlarm.T0_Flag,	C_Bit6_Start,	C_Bit6_End	},/*������ƽ��*/
	{GStr_ALosscurrentStr.AddTime,				GStr_ALosscurrentStr.V_CRC,			sizeof(Str_OtherMeter_Type),			CMeter_Work_State4,		C_Bit3_Start,	C_Bit3_End,	&GStr_BellAlarm.A0_Flag,	&GStr_Alarmoutput.A0_Flag,	&GStr_BackLightAlarm.A0_Flag,	C_Bit3_Start,	C_Bit3_End	},/*A��ʧ��*/
	{GStr_BLosscurrentStr.AddTime,				GStr_BLosscurrentStr.V_CRC,			sizeof(Str_OtherMeter_Type),			CMeter_Work_State5,		C_Bit3_Start,	C_Bit3_End,	&GStr_BellAlarm.B0_Flag,	&GStr_Alarmoutput.B0_Flag,	&GStr_BackLightAlarm.B0_Flag,	C_Bit3_Start,	C_Bit3_End	},/*B��ʧ��*/
	{GStr_CLosscurrentStr.AddTime,				GStr_CLosscurrentStr.V_CRC,			sizeof(Str_OtherMeter_Type),			CMeter_Work_State6,		C_Bit3_Start,	C_Bit3_End,	&GStr_BellAlarm.C0_Flag,	&GStr_Alarmoutput.C0_Flag,	&GStr_BackLightAlarm.C0_Flag,	C_Bit3_Start,	C_Bit3_End	},/*C��ʧ��*/
	{GStr_AOvercurrentStr.AddTime,				GStr_AOvercurrentStr.V_CRC,			sizeof(Str_OtherMeter_Type),			CMeter_Work_State4,		C_Bit4_Start,	C_Bit4_End,	&GStr_BellAlarm.A0_Flag,	&GStr_Alarmoutput.A0_Flag,	&GStr_BackLightAlarm.A0_Flag,	C_Bit5_Start,	C_Bit5_End	},/*A�����*/
	{GStr_BOvercurrentStr.AddTime,				GStr_BOvercurrentStr.V_CRC,			sizeof(Str_OtherMeter_Type),			CMeter_Work_State5,		C_Bit4_Start,	C_Bit4_End,	&GStr_BellAlarm.B0_Flag,	&GStr_Alarmoutput.B0_Flag,	&GStr_BackLightAlarm.B0_Flag,	C_Bit5_Start,	C_Bit5_End	},/*B�����*/
	{GStr_COvercurrentStr.AddTime,				GStr_COvercurrentStr.V_CRC,			sizeof(Str_OtherMeter_Type),			CMeter_Work_State6,		C_Bit4_Start,	C_Bit4_End,	&GStr_BellAlarm.C0_Flag,	&GStr_Alarmoutput.C0_Flag,	&GStr_BackLightAlarm.C0_Flag,	C_Bit5_Start,	C_Bit5_End	},/*C�����*/
	{GStr_AFailcurrentStr.AddTime,				GStr_AFailcurrentStr.V_CRC,			sizeof(Str_OtherMeter_Type),			CMeter_Work_State4,		C_Bit0_Start,	C_Bit0_End,	&GStr_BellAlarm.A1_Flag,	&GStr_Alarmoutput.A1_Flag,	&GStr_BackLightAlarm.A1_Flag,	C_Bit0_Start,	C_Bit0_End	},/*A�����*/
	{GStr_BFailcurrentStr.AddTime,				GStr_BFailcurrentStr.V_CRC,			sizeof(Str_OtherMeter_Type),			CMeter_Work_State5,		C_Bit0_Start,	C_Bit0_End,	&GStr_BellAlarm.B1_Flag,	&GStr_Alarmoutput.B1_Flag,	&GStr_BackLightAlarm.B1_Flag,	C_Bit0_Start,	C_Bit0_End	},/*B�����*/
	{GStr_CFailcurrentStr.AddTime,				GStr_CFailcurrentStr.V_CRC,			sizeof(Str_OtherMeter_Type),			CMeter_Work_State6,		C_Bit0_Start,	C_Bit0_End,	&GStr_BellAlarm.C1_Flag,	&GStr_Alarmoutput.C1_Flag,	&GStr_BackLightAlarm.C1_Flag,	C_Bit0_Start,	C_Bit0_End	},/*C�����*/
	{GStr_TReversecurrentStr.AddTime,			GStr_TReversecurrentStr.V_CRC,		sizeof(Str_OtherMeter_Type),			0,						0,				0,			0,						0,							0,								0,				0			},/*�ܹ��ʷ���*/
	{GStr_AReversecurrentStr.AddTime,			GStr_AReversecurrentStr.V_CRC,		sizeof(Str_OtherMeter_Type),			CMeter_Work_State4,		C_Bit6_Start,	C_Bit6_End,	&GStr_BellAlarm.A0_Flag,	&GStr_Alarmoutput.A0_Flag,	&GStr_BackLightAlarm.A0_Flag,	C_Bit2_Start,	C_Bit2_End	},/*A�๦�ʷ���*/
	{GStr_BReversecurrentStr.AddTime,			GStr_BReversecurrentStr.V_CRC,		sizeof(Str_OtherMeter_Type),			CMeter_Work_State5,		C_Bit6_Start,	C_Bit6_End,	&GStr_BellAlarm.B0_Flag,	&GStr_Alarmoutput.B0_Flag,	&GStr_BackLightAlarm.B0_Flag,	C_Bit2_Start,	C_Bit2_End	},/*B�๦�ʷ���*/
	{GStr_CReversecurrentStr.AddTime,			GStr_CReversecurrentStr.V_CRC,		sizeof(Str_OtherMeter_Type),			CMeter_Work_State6,		C_Bit6_Start,	C_Bit6_End,	&GStr_BellAlarm.C0_Flag,	&GStr_Alarmoutput.C0_Flag,	&GStr_BackLightAlarm.C0_Flag,	C_Bit2_Start,	C_Bit2_End	},/*C�๦�ʷ���*/
	{GStr_AOverloadStr.AddTime,					GStr_AOverloadStr.V_CRC,				sizeof(Str_OtherMeter_Type),			CMeter_Work_State4,		C_Bit5_Start,	C_Bit5_End,	&GStr_BellAlarm.A0_Flag,	&GStr_Alarmoutput.A0_Flag,	&GStr_BackLightAlarm.A0_Flag,	C_Bit1_Start,	C_Bit1_End	},/*A�����*/
	{GStr_BOverloadStr.AddTime,					GStr_BOverloadStr.V_CRC,				sizeof(Str_OtherMeter_Type),			CMeter_Work_State5,		C_Bit5_Start,	C_Bit5_End,	&GStr_BellAlarm.B0_Flag,	&GStr_Alarmoutput.B0_Flag,	&GStr_BackLightAlarm.B0_Flag,	C_Bit1_Start,	C_Bit1_End	},/*B�����*/
	{GStr_COverloadStr.AddTime,					GStr_COverloadStr.V_CRC,				sizeof(Str_OtherMeter_Type),			CMeter_Work_State6,		C_Bit5_Start,	C_Bit5_End,	&GStr_BellAlarm.C0_Flag,	&GStr_Alarmoutput.C0_Flag,	&GStr_BackLightAlarm.C0_Flag,	C_Bit1_Start,	C_Bit1_End	},/*C�����*/
	{GStr_OverpowerfactStr.AddTime,				GStr_OverpowerfactStr.V_CRC,			sizeof(Str_OtherMeter_Type),			CMeter_Work_State7,		C_Bit7_Start,	C_Bit7_End,	&GStr_BellAlarm.T0_Flag,	&GStr_Alarmoutput.T0_Flag,	&GStr_BackLightAlarm.T0_Flag,	C_Bit4_Start,	C_Bit4_End	},/*�ܹ�������������*/
	{GStr_AOverpowerfactStr.AddTime,				GStr_AOverpowerfactStr.V_CRC,		sizeof(Str_OtherMeter_Type),			0,						0,				0,			&GStr_BellAlarm.A1_Flag,	&GStr_Alarmoutput.A1_Flag,	&GStr_BackLightAlarm.A1_Flag,	C_Bit1_Start,	C_Bit1_End	},/*A�๦������������*/
	{GStr_BOverpowerfactStr.AddTime,				GStr_BOverpowerfactStr.V_CRC,		sizeof(Str_OtherMeter_Type),			0,						0,				0,			&GStr_BellAlarm.B1_Flag,	&GStr_Alarmoutput.B1_Flag,	&GStr_BackLightAlarm.B1_Flag,	C_Bit1_Start,	C_Bit1_End	},/*B�๦������������*/
	{GStr_COverpowerfactStr.AddTime,				GStr_COverpowerfactStr.V_CRC,		sizeof(Str_OtherMeter_Type),			0,						0,				0,			&GStr_BellAlarm.C1_Flag,	&GStr_Alarmoutput.C1_Flag,	&GStr_BackLightAlarm.C1_Flag,	C_Bit1_Start,	C_Bit1_End	},/*C�๦������������*/
	{GStr_SUnbanlanceCurrentStr.Renewal,			GStr_SUnbanlanceCurrentStr.V_CRC,	sizeof(Str_Unbanlance_Type),			CMeter_Work_State7,		C_Bit0_Start,	C_Bit0_End,	&GStr_BellAlarm.T0_Flag,	&GStr_Alarmoutput.T0_Flag,	&GStr_BackLightAlarm.T0_Flag,	C_Bit7_Start,	C_Bit7_End	},/*�������ز�ƽ��*/
#if 0
	{0,										0,								0,										0,						0,				0,			&GStr_BellAlarm.T0_Flag,	&GStr_Alarmoutput.T0_Flag,	&GStr_BackLightAlarm.T0_Flag,	C_Bit3_Start,	C_Bit3_End	},/*�ܳ�������*/
#endif
	{GStr_MeterFaStr.AddTime,					GStr_MeterFaStr.V_CRC,				sizeof(Str_OtherMeter_Type),			CMeter_Work_State1,		C_Bit6_Start,	C_Bit6_End,	0,						0,							0,								0,				0			},/*����оƬ����*/
	{GStr_ClockFaStr.AddTime,					GStr_ClockFaStr.V_CRC,				sizeof(Str_OtherMeter_Type),			0,						0,				0,			0,						0,							0,								0,				0			},/*ʱ�ӹ���*/
	{GStr_NeutralAbnormalStr.AddTime,			GStr_NeutralAbnormalStr.V_CRC,		sizeof(Str_OtherMeter_Type),			0,						0,				0,			0,						0,							0,								0,				0			},/*���ߵ����쳣*/
};

/*****************************************************************************************/
/*����˳���������������*/
/*****************************************************************************************/
const   uchar8  ActiveReportTable[C_EventNoLength]=
{
        C_Times_NoVoltage,
        C_Times_SubPowerOff,
        C_Times_PowerOff,
        C_Times_OpenMeterCover,
        C_Times_OpenTerminalCover,
        C_Times_MagneticCheck,
        C_Times_PowerError,
        C_Times_OverDemadn,
        C_Times_OverDemadn,
        C_NULL,
        C_NULL,
        C_NULL,
        C_NULL,
        C_Times_ALossVoltage,
        C_Times_BLossVoltage,
        C_Times_CLossVoltage,
        C_Times_ALessVoltage,
        C_Times_BLessVoltage,
        C_Times_CLessVoltage,
        C_Times_AOverVoltage,
        C_Times_BOverVoltage,
        C_Times_COverVoltage,
        C_Times_ALossPhase,
        C_Times_BLossPhase,
        C_Times_CLossPhase,
        C_Times_ReversedVoltage,
        C_Times_ReversedCurrent,
        C_Times_UnbalancedVoltage,
        C_Times_UnbalancedCurrent,
        C_Times_ALossCurrent,
        C_Times_BLossCurrent,
        C_Times_CLossCurrent,
        C_Times_AOverCurrent,
        C_Times_BOverCurrent,
        C_Times_COverCurrent,
        C_Times_ALessCurrent,
        C_Times_BLessCurrent,
        C_Times_CLessCurrent,
        C_Times_TActivePowerReversed,
        C_Times_APowerReverse,
        C_Times_BPowerReverse,
        C_Times_CPowerReverse,
        C_Times_AOverLoad,
        C_Times_BOverLoad,
        C_Times_COverLoad,
        C_Times_OverPowerFact,
        C_NULL,
        C_NULL,
        C_NULL,
        C_Times_SeriousUnbalancedCurrent,
        C_NULL,
        C_Times_RTCErr,
};


/*****************************************************************************************/
/*����˳���������������*/
/*****************************************************************************************/
/***********�¼���Ӧ���**************/
const Str_EventMapping_Type EventMappingTable[]=
{
	{C_AlossvoltageEventNo,		C_SourceNon,	CLossA_Vol_Degree,	CLoss_Vol_OADTab,	CLossAVol_FF_1},
	{C_BlossvoltageEventNo,		C_SourceNon,	CLossB_Vol_Degree,	CLoss_Vol_OADTab,	CLossBVol_FF_1},
	{C_ClossvoltageEventNo,		C_SourceNon,	CLossC_Vol_Degree,	CLoss_Vol_OADTab,	CLossCVol_FF_1},
	{C_ALessvoltageEventNo,		C_SourceNon,	CLowA_Vol_Degree,	CLow_Vol_OADTab,	CLowAVol_FF_1},
	{C_BLessvoltageEventNo,		C_SourceNon,	CLowB_Vol_Degree,	CLow_Vol_OADTab,	CLowBVol_FF_1},
	{C_CLessvoltageEventNo,		C_SourceNon,	CLowC_Vol_Degree,	CLow_Vol_OADTab,	CLowCVol_FF_1},
	{C_AOvervoltageEventNo,		C_SourceNon,	COverA_Vol_Degree,	COver_Vol_OADTab,	COverAVol_FF_1},
	{C_BOvervoltageEventNo,		C_SourceNon,	COverB_Vol_Degree,	COver_Vol_OADTab,	COverBVol_FF_1},
	{C_COvervoltageEventNo,		C_SourceNon,	COverC_Vol_Degree,	COver_Vol_OADTab,	COverCVol_FF_1},
	{C_ALossphaseEventNo,		C_SourceNon,	CBreakA_Vol_Degree,	CBreak_Vol_OADTab,	CBreakAVol_FF_1},
	{C_BLossphaseEventNo,		C_SourceNon,	CBreakB_Vol_Degree,	CBreak_Vol_OADTab,	CBreakBVol_FF_1},
	{C_CLossphaseEventNo,		C_SourceNon,	CBreakC_Vol_Degree,	CBreak_Vol_OADTab,	CBreakCVol_FF_1},
	{C_ALosscurrentEventNo,		C_SourceNon,	CLossA_Curr_Degree,	CLoss_Curr_OADTab,	CLossACurr_FF_1},
	{C_BLosscurrentEventNo,		C_SourceNon,	CLossB_Curr_Degree,	CLoss_Curr_OADTab,	CLossBCurr_FF_1},
	{C_CLosscurrentEventNo,		C_SourceNon,	CLossC_Curr_Degree,	CLoss_Curr_OADTab,	CLossCCurr_FF_1},
	{C_AOvercurrentEventNo,		C_SourceNon,	COverA_Curr_Degree,	COver_Curr_OADTab,	COverACurr_FF_1},
	{C_BOvercurrentEventNo,		C_SourceNon,	COverB_Curr_Degree,	COver_Curr_OADTab,	COverBCurr_FF_1},
	{C_COvercurrentEventNo,		C_SourceNon,	COverC_Curr_Degree,	COver_Curr_OADTab,	COverCCurr_FF_1},
	{C_AFailcurrentEventNo,		C_SourceNon,	CBreakA_Curr_Degree,	CBreak_Curr_OADTab,	CBreakACurr_FF_1},
	{C_BFailcurrentEventNo,		C_SourceNon,	CBreakB_Curr_Degree,	CBreak_Curr_OADTab,	CBreakBCurr_FF_1},
	{C_CFailcurrentEventNo,		C_SourceNon,	CBreakC_Curr_Degree,	CBreak_Curr_OADTab,	CBreakCCurr_FF_1},
	{C_TReversecurrentEventNo,	C_SourceNon,	CPowerT_Rev_Degree,	CPower_Rev_OADTab,	CPowerTRev_FF_1},
	{C_AReversecurrentEventNo,	C_SourceNon,	CPowerA_Rev_Degree,	CPower_Rev_OADTab,	CPowerARev_FF_1},
	{C_BReversecurrentEventNo,	C_SourceNon,	CPowerB_Rev_Degree,	CPower_Rev_OADTab,	CPowerBRev_FF_1},
	{C_CReversecurrentEventNo,	C_SourceNon,	CPowerC_Rev_Degree,	CPower_Rev_OADTab,	CPowerCRev_FF_1},
	{C_AOverloadEventNo,		C_SourceNon,	COverA_Lo_Degree,	COver_Lo_OADTab,	COverALo_FF_1},
	{C_BOverloadEventNo,		C_SourceNon,	COverB_Lo_Degree,	COver_Lo_OADTab,	COverBLo_FF_1},
	{C_COverloadEventNo,		C_SourceNon,	COverC_Lo_Degree,	COver_Lo_OADTab,	COverCLo_FF_1},
	{C_OverForwardActiveEventNo,	C_SourceExist,	CPos_Ac_De_Over_Degree,	CPos_Ac_De_Over_OADTab,	CPos_Ac_De_Over_Note_1},
	{C_OverReverseActiveEventNo,	C_SourceExist,	CRev_Ac_De_Over_Degree,	CRev_Ac_De_Over_OADTab,	CRev_Ac_De_Over_Note_1},
	{C_1OverIdleDemandEventNo,	C_SourceExist,	CQua1_Re_De_Over_Degree,CQua_Re_De_Over_OADTab,	CQua1_Re_De_Over_Note_1},
	{C_2OverIdleDemandEventNo,	C_SourceExist,	CQua2_Re_De_Over_Degree,CQua_Re_De_Over_OADTab,	CQua2_Re_De_Over_Note_1},
	{C_3OverIdleDemandEventNo,	C_SourceExist,	CQua3_Re_De_Over_Degree,CQua_Re_De_Over_OADTab,	CQua3_Re_De_Over_Note_1},
	{C_4OverIdleDemandEventNo,	C_SourceExist,	CQua4_Re_De_Over_Degree,CQua_Re_De_Over_OADTab,	CQua4_Re_De_Over_Note_1},
	{C_OverpowerfactEventNo,	C_SourceNon,	CPFactorT_Over_Degree,	CPFactorT_Over_OADTab,	CPFactorT_FF_1},
	{C_AOverpowerfactEventNo,	C_SourceNon,	CPFactorA_Over_Degree,	CPFactorT_Over_OADTab,	CPFactorA_FF_1},
    {C_BOverpowerfactEventNo,	C_SourceNon,	CPFactorB_Over_Degree,	CPFactorT_Over_OADTab,	CPFactorB_FF_1},
    {C_COverpowerfactEventNo,	C_SourceNon,	CPFactorC_Over_Degree,	CPFactorT_Over_OADTab,	CPFactorC_FF_1},
	{C_TotalVoltageLoseEventNo,	C_SourceExist,	CAll_Loss_Vol_Degree,	CAll_Loss_Vol_OADTab,	CAll_Loss_Vol_Note_1},
	{C_ACPowerFailEventNo,		C_SourceExist,	CAux_Pow_Down_Degree,	CAux_Pow_Down_OADTab,	CAux_Pow_Down_Note_1},
	{C_ReversephaseVoltageEventNo,	C_SourceExist,	CRevPS_Vol_Degree,	CRevPS_Vol_OADTab,	CRevPSVol_FF_1},
	{C_ReversephaseCurrentEventNo,	C_SourceExist,	CRevPS_Curr_Degree,	CRevPS_Curr_OADTab,	CRevPSCurr_FF_1},
	{C_PowerfailEventNo,		C_SourceExist,	CPow_Down_Degree,	CPow_Down_OADTab,	CPow_Down_Note_1},
	{C_OpenMeterCoverEventNo,	C_SourceExist,	COpenW_Degree,		COpenW_OADTab,		COpenW_Note_1},
	{C_OpenTerminalCoverEventNo,	C_SourceExist,	COpenCW_Degree,		COpenCW_OADTab,		COpenCW_Note_1},
	{C_UnbanlanceVoltageEventNo,	C_SourceExist,	CNoBal_Vol_Degree,	CNoBal_Vol_OADTab,	CNoBalVol_FF_1},
	{C_UnbanlanceCurrentEventNo,	C_SourceExist,	CNoBal_Curr_Degree,	CNoBal_Curr_OADTab,	CNoBalCurr_FF_1},
	{C_MagneticCheckEventNo,	C_SourceExist,	CConM_Degree,		CConM_OADTab,		CConM_Note_1},
	{C_PowerAbnormalEventNo,	C_SourceExist,	CPowerFa_Degree,	CPowerFa_OADTab,	CPowerFa_Note_1},
	{C_SUnbanlanceCurrentEventNo,	C_SourceExist,	CSevNoBal_Curr_Degree,	CSevNoBal_Curr_OADTab,	CSevNoBalCurr_FF_1},
#if 0
	{C_ReversecurrentEventNo,	C_SourceNon,	CTrend_Rev_Degree,	CPower_Rev_OADTab,	CTrend_Rev_Note_1},
#endif
	{C_ProgramEventNo,		C_SourceExist,	CProgram_Degree,	CProgram_OADTab,	CProgram_Note_1},
	{C_TolClearEventNo,		C_SourceExist,	CTol_Clear_Degree,	CTol_Clear_OADTab,	CTol_Clear_Note_1},
	{C_DemandClearEventNo,		C_SourceExist,	CDe_Clear_Degree,	CDe_Clear_OADTab,	CDe_Clear_Note_1},
	{C_EventClearEventNo,		C_SourceExist,	CEven_Clear_Degree,	CEven_Clear_OADTab,	CEven_Clear_Note_1},
	{C_AdjTimeEventNo,		C_SourceExist,	CAdjTime_Degree,	CAdjTime_OADTab,	CAdjTime_Note_1},
	{C_ProgPTEventNo,		C_SourceExist,	CProgPT_Degree,		CProgPT_OADTab,		CProgPT_Note_1},
	{C_ProgPZEventNo,		C_SourceExist,	CProgTZ_Degree,		CProgTZ_OADTab,		CProgTZ_Note_1},
	{C_ProgWReEventNo,		C_SourceExist,	CProgWRe_Degree,	CProgWRe_OADTab,	CProgWRe_Note_1},
	{C_ProgSettDEventNo,		C_SourceExist,	CProgSettD_Degree,	CProgSettD_OADTab,	CProgSettD_Note_1},
	{C_RelayOpenEventNo,		C_SourceExist,	CRelayOpen_Degree,	CRelayOpen_OADTab,	CRelayOpen_FF_1},
	{C_RelayCloseEventNo,		C_SourceExist,	CRelayClose_Degree,	CRelayClose_OADTab,	CRelayClose_FF_1},
	{C_ProgHolEventNo,		C_SourceExist,	CProgHol_Degree,	CProgHol_OADTab,	CProgHol_Note_1},
	{C_ProgAcCEventNo,		C_SourceExist,	CProgAcC_Degree,	CProgAcC_OADTab,	CProgAcC_Note_1},
	{C_ProgReCEventNo,		C_SourceExist,	CProgReC_Degree,	CProgReC_OADTab,	CProgReC_Note_1},
	{C_ProgTParaEventNo,		C_SourceExist,	CProgTPara_Degree,	CProgTPara_OADTab,	CProgTPara_Note_1},
	{C_ProgLadEventNo,		C_SourceExist,	CProgLad_Degree,	CProgLad_OADTab,	CProgLad_Note_1},
	{C_Key_UpdateEventNo,		C_SourceExist,	CProgKD_Degree,		CProgKD_OADTab,		CProgKD_Note_1},
	{C_AbnorCEventNo,		C_SourceExist,	CAbnorC_Degree,		CAbnorC_OADTab,		CAbnorC_Note_1},
	{C_BuyCurrEventNo,		C_SourceExist,	CBuyCurr_Degree,	CBuyCurr_OADTab,	CBuyCurr_FF_Note_1},
	{C_ReturnMoneyEventNo,		C_SourceExist,	CReturn_M_Degree,	CReturn_M_OADTab,	CReturn_M_Note_1},
	{C_RelayFaEndEnEventNo,		C_SourceExist,	CRelayFa_Degree,	CRelayFa_OADTab,	CRelayFa_Note_1},
	{C_MeterFaEventNo,		C_SourceExist,	CMeterFa_Degree,	CMeterFa_OADTab,	CMeterFa_Note_1},
	{C_ClockFaEventNo,		C_SourceExist,	CClockFa_Degree,	CClockFa_OADTab,	CClockFa_Note_1},
	{C_BroadcastTimeEventNo,		C_SourceExist,	CBroadcastTime_Degree,	CBroadcastTime_OADTab,	CBroadcastTime_Note_1},
	{C_NeutralCurrentAbnormalEventNo, C_SourceExist,CNeutralCurrentAbnormal_Degree, CNeutralCurrentAbnormal_OADTab, CNeutralCurrentAbnormal_Note_1},
#if 0
	{C_BroadTimeAbnormalEventNo,		C_SourceExist,	CBroadTimeAbnormal_Degree,	CBroadTimeAbnormal_OADTab,	CBroadTimeAbnormal_Note_1},
#endif
};
#define EventMappingTable_Len  sizeof(EventMappingTable)/sizeof(Str_EventMapping_Type)

/*****************************************************************************************/
/*����˳���������������*/
/*****************************************************************************************/
/*��ʵʱ�����*/
const Str_SpecialReadTable_Type	SpecialReadTable[]=
{
	{CAll_Loss_Vol_Note_1,		CAll_Loss_Vol_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{CAux_Pow_Down_Note_1,		CAux_Pow_Down_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{CLossAVol_FF_1,		CLossA_Vol_Time,	CLossAVol_TolAh_1,	CLossAVol_AAh_1,	CLossAVol_BAh_1,	CLossAVol_CAh_1		},
	{CLossBVol_FF_1,		CLossB_Vol_Time,	CLossBVol_TolAh_1,	CLossBVol_AAh_1,	CLossBVol_BAh_1,	CLossBVol_CAh_1		},
	{CLossCVol_FF_1,		CLossC_Vol_Time,	CLossCVol_TolAh_1,	CLossCVol_AAh_1,	CLossCVol_BAh_1,	CLossCVol_CAh_1		},
	{CLowAVol_FF_1,			CLowA_Vol_Time,		CLowAVol_TolAh_1,	CLowAVol_AAh_1,		CLowAVol_BAh_1,		CLowAVol_CAh_1		},
	{CLowBVol_FF_1,			CLowB_Vol_Time,		CLowBVol_TolAh_1,	CLowBVol_AAh_1,		CLowBVol_BAh_1,		CLowBVol_CAh_1		},
	{CLowCVol_FF_1,			CLowC_Vol_Time,		CLowCVol_TolAh_1,	CLowCVol_AAh_1,		CLowCVol_BAh_1,		CLowCVol_CAh_1		},
	{COverAVol_FF_1,		COverA_Vol_Time,	COverAVol_TolAh_1,	COverAVol_AAh_1,	COverAVol_BAh_1,	COverAVol_CAh_1		},
	{COverBVol_FF_1,		COverB_Vol_Time,	COverBVol_TolAh_1,	COverBVol_AAh_1,	COverBVol_BAh_1,	COverBVol_CAh_1		},
	{COverCVol_FF_1,		COverC_Vol_Time,	COverCVol_TolAh_1,	COverCVol_AAh_1,	COverCVol_BAh_1,	COverCVol_CAh_1		},
	{CBreakAVol_FF_1,		CBreakA_Vol_Time,	CBreakAVol_TolAh_1,	CBreakAVol_AAh_1,	CBreakAVol_BAh_1,	CBreakAVol_CAh_1	},
	{CBreakBVol_FF_1,		CBreakB_Vol_Time,	CBreakBVol_TolAh_1,	CBreakBVol_AAh_1,	CBreakBVol_BAh_1,	CBreakBVol_CAh_1	},
	{CBreakCVol_FF_1,		CBreakC_Vol_Time,	CBreakCVol_TolAh_1,	CBreakCVol_AAh_1,	CBreakCVol_BAh_1,	CBreakCVol_CAh_1	},
	{CRevPSVol_FF_1,		CRevPS_Vol_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{CRevPSCurr_FF_1,		CRevPS_Curr_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{CNoBalVol_FF_1,		CNoBal_Vol_Time,	CNoBalRate_Vol_End_1,	C_NULL,			C_NULL,			C_NULL			},
	{CNoBalCurr_FF_1,		CNoBal_Curr_Time,	CNoBalRate_Curr_1,	C_NULL,			C_NULL,			C_NULL			},
	{CLossACurr_FF_1,		CLossA_Curr_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{CLossBCurr_FF_1,		CLossB_Curr_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{CLossCCurr_FF_1,		CLossC_Curr_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{COverACurr_FF_1,		COverA_Curr_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{COverBCurr_FF_1,		COverB_Curr_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{COverCCurr_FF_1,		COverC_Curr_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{CBreakACurr_FF_1,		CBreakA_Curr_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{CBreakBCurr_FF_1,		CBreakB_Curr_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{CBreakCCurr_FF_1,		CBreakC_Curr_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{CPowerTRev_FF_1,		CPowerT_Rev_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{CPowerARev_FF_1,		CPowerA_Rev_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{CPowerBRev_FF_1,		CPowerB_Rev_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{CPowerCRev_FF_1,		CPowerC_Rev_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{COverALo_FF_1,			COverA_Lo_Time,		C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{COverBLo_FF_1,			COverB_Lo_Time,		C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{COverCLo_FF_1,			COverC_Lo_Time,		C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{CPFactorT_FF_1,		CPFactorT_Over_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{CPFactorA_FF_1,		CPFactorA_Over_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{CPFactorB_FF_1,		CPFactorB_Over_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{CPFactorC_FF_1,		CPFactorC_Over_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{CSevNoBalCurr_FF_1,		CSevNoBal_Curr_Time,	CSevNoBalRate_Curr_1,	C_NULL,			C_NULL,			C_NULL			},
	{CPos_Ac_De_Over_Note_1,	CPos_Ac_De_Over_Time,	CPos_Ac_De_Over_1,	C_NULL,			C_NULL,			C_NULL			},
	{CRev_Ac_De_Over_Note_1,	CRev_Ac_De_Over_Time,	CRev_Ac_De_Over_1,	C_NULL,			C_NULL,			C_NULL			},
	{CQua1_Re_De_Over_Note_1,	CQua1_Re_De_Over_Time,	CQua1_Re_De_Over_1,	C_NULL,			C_NULL,			C_NULL			},
	{CQua2_Re_De_Over_Note_1,	CQua2_Re_De_Over_Time,	CQua2_Re_De_Over_1,	C_NULL,			C_NULL,			C_NULL			},
	{CQua3_Re_De_Over_Note_1,	CQua3_Re_De_Over_Time,	CQua3_Re_De_Over_1,	C_NULL,			C_NULL,			C_NULL			},
	{CQua4_Re_De_Over_Note_1,	CQua4_Re_De_Over_Time,	CQua4_Re_De_Over_1,	C_NULL,			C_NULL,			C_NULL			},
};
#define SpecialReadTable_Len  sizeof(SpecialReadTable)/sizeof(Str_SpecialReadTable_Type)

const Str_CurrentDataReadTable_Type	CurrentDataReadTable[]=
{
	{CLoss_TollVol_Current,		C_SourceNon,			C_NULL,                          CLoss_TollVol_Attri14_Nature,	CLoss_Vol_Degree,		CLoss_Vol_Time},
	{CLossA_Vol_Current,		C_SourceNon,			C_AlossvoltageEventNo,           CLossA_Vol_Attri14_Nature,		CLossA_Vol_Degree,		CLossA_Vol_Time},
	{CLossB_Vol_Current,		C_SourceNon,			C_BlossvoltageEventNo,           CLossB_Vol_Attri14_Nature,		CLossB_Vol_Degree,		CLossB_Vol_Time},
	{CLossC_Vol_Current,		C_SourceNon,			C_ClossvoltageEventNo,           CLossC_Vol_Attri14_Nature,		CLossC_Vol_Degree,		CLossC_Vol_Time},
	{CLowA_Vol_Current,			C_SourceNon,			C_ALessvoltageEventNo,           CLowA_Vol_Attri14_Nature,		CLowA_Vol_Degree,		CLowA_Vol_Time},
	{CLowB_Vol_Current,			C_SourceNon,			C_BLessvoltageEventNo,           CLowB_Vol_Attri14_Nature,		CLowB_Vol_Degree,		CLowB_Vol_Time},
	{CLowC_Vol_Current,			C_SourceNon,			C_CLessvoltageEventNo,           CLowC_Vol_Attri14_Nature,		CLowC_Vol_Degree,		CLowC_Vol_Time},
	{COverA_Vol_Current,		C_SourceNon,			C_AOvervoltageEventNo,           COverA_Vol_Attri14_Nature,		COverA_Vol_Degree,		COverA_Vol_Time},
	{COverB_Vol_Current,		C_SourceNon,			C_BOvervoltageEventNo,           COverB_Vol_Attri14_Nature,		COverB_Vol_Degree,		COverB_Vol_Time},
	{COverC_Vol_Current,		C_SourceNon,			C_COvervoltageEventNo,           COverC_Vol_Attri14_Nature,		COverC_Vol_Degree,		COverC_Vol_Time},
	{CBreakA_Vol_Current,		C_SourceNon,			C_ALossphaseEventNo,             CBreakA_Vol_Attri14_Nature,		CBreakA_Vol_Degree,		CBreakA_Vol_Time},
	{CBreakB_Vol_Current,		C_SourceNon,			C_BLossphaseEventNo,             CBreakB_Vol_Attri14_Nature,		CBreakB_Vol_Degree,		CBreakB_Vol_Time},
	{CBreakC_Vol_Current,		C_SourceNon,			C_CLossphaseEventNo,             CBreakC_Vol_Attri14_Nature,		CBreakC_Vol_Degree,		CBreakC_Vol_Time},
	{CLossA_Curr_Current,		C_SourceNon,			C_ALosscurrentEventNo,           CLossA_Curr_Attri14_Nature,		CLossA_Curr_Degree,		CLossA_Curr_Time},
	{CLossB_Curr_Current,		C_SourceNon,			C_BLosscurrentEventNo,           CLossB_Curr_Attri14_Nature,		CLossB_Curr_Degree,		CLossB_Curr_Time},
	{CLossC_Curr_Current,		C_SourceNon,			C_CLosscurrentEventNo,           CLossC_Curr_Attri14_Nature,		CLossC_Curr_Degree,		CLossC_Curr_Time},
	{COverA_Curr_Current,		C_SourceNon,			C_AOvercurrentEventNo,           COverA_Curr_Attri14_Nature,		COverA_Curr_Degree,		COverA_Curr_Time},
	{COverB_Curr_Current,		C_SourceNon,			C_BOvercurrentEventNo,           COverB_Curr_Attri14_Nature,		COverB_Curr_Degree,		COverB_Curr_Time},
	{COverC_Curr_Current,		C_SourceNon,			C_COvercurrentEventNo,           COverC_Curr_Attri14_Nature,		COverC_Curr_Degree,		COverC_Curr_Time},
	{CBreakA_Curr_Current,		C_SourceNon,			C_AFailcurrentEventNo,           CBreakA_Curr_Attri14_Nature,	CBreakA_Curr_Degree,	CBreakA_Curr_Time},
	{CBreakB_Curr_Current,		C_SourceNon,			C_BFailcurrentEventNo,           CBreakB_Curr_Attri14_Nature,	CBreakB_Curr_Degree,	CBreakB_Curr_Time},
	{CBreakC_Curr_Current,		C_SourceNon,			C_CFailcurrentEventNo,           CBreakC_Curr_Attri14_Nature,	CBreakC_Curr_Degree,	CBreakC_Curr_Time},
	{CPowerT_Rev_Current,		C_SourceNon,			C_TReversecurrentEventNo,        CPowerT_Rev_Attri14_Nature,		CPowerT_Rev_Degree,		CPowerT_Rev_Time},
	{CPowerA_Rev_Current,		C_SourceNon,			C_AReversecurrentEventNo,        CPowerA_Rev_Attri14_Nature,		CPowerA_Rev_Degree,		CPowerA_Rev_Time},
	{CPowerB_Rev_Current,		C_SourceNon,			C_BReversecurrentEventNo,        CPowerB_Rev_Attri14_Nature,		CPowerB_Rev_Degree,		CPowerB_Rev_Time},
	{CPowerC_Rev_Current,		C_SourceNon,			C_CReversecurrentEventNo,        CPowerC_Rev_Attri14_Nature,		CPowerC_Rev_Degree,		CPowerC_Rev_Time},
	{COverA_Lo_Current,			C_SourceNon,			C_AOverloadEventNo,              COverA_Lo_Attri14_Nature,		COverA_Lo_Degree,		COverA_Lo_Time},
	{COverB_Lo_Current,			C_SourceNon,			C_BOverloadEventNo,              COverB_Lo_Attri14_Nature,		COverB_Lo_Degree,		COverB_Lo_Time},
	{COverC_Lo_Current,			C_SourceNon,			C_COverloadEventNo,              COverC_Lo_Attri14_Nature,		COverC_Lo_Degree,		COverC_Lo_Time},
	{CPos_Ac_De_Over_Current,	C_SourceExist,			C_OverForwardActiveEventNo,      CPos_Ac_De_Over_Attri7_Nature,	CPos_Ac_De_Over_Degree,	CPos_Ac_De_Over_Time},
	{CRev_Ac_De_Over_Current,	C_SourceExist,			C_OverReverseActiveEventNo,      CRev_Ac_De_Over_Attri7_Nature,	CRev_Ac_De_Over_Degree,	CRev_Ac_De_Over_Time},
	{CQua1_Re_De_Over_Current,	C_SourceNon,			C_1OverIdleDemandEventNo,        CQua1_Re_De_Over_Attri14_Nature,CQua1_Re_De_Over_Degree,CQua1_Re_De_Over_Time},
	{CQua2_Re_De_Over_Current,	C_SourceNon,			C_2OverIdleDemandEventNo,        CQua2_Re_De_Over_Attri14_Nature,CQua2_Re_De_Over_Degree,CQua2_Re_De_Over_Time},
	{CQua3_Re_De_Over_Current,	C_SourceNon,			C_3OverIdleDemandEventNo,        CQua3_Re_De_Over_Attri14_Nature,CQua3_Re_De_Over_Degree,CQua3_Re_De_Over_Time},
	{CQua4_Re_De_Over_Current,	C_SourceNon,			C_4OverIdleDemandEventNo,        CQua4_Re_De_Over_Attri14_Nature,CQua4_Re_De_Over_Degree,CQua4_Re_De_Over_Time},
	{CPFactorT_Over_Current,	C_SourceNon,			C_OverpowerfactEventNo,          CPFactorT_Over_Attri14_Nature,	CPFactorT_Over_Degree,	CPFactorT_Over_Time},
	{CPFactorA_Over_Current,	C_SourceNon,			C_AOverpowerfactEventNo,          CPFactorA_Over_Attri14_Nature,	CPFactorA_Over_Degree,	CPFactorA_Over_Time},
	{CPFactorB_Over_Current,	C_SourceNon,			C_BOverpowerfactEventNo,          CPFactorB_Over_Attri14_Nature,	CPFactorB_Over_Degree,	CPFactorB_Over_Time},
	{CPFactorC_Over_Current,	C_SourceNon,			C_COverpowerfactEventNo,          CPFactorC_Over_Attri14_Nature,	CPFactorC_Over_Degree,	CPFactorC_Over_Time},
	{CAll_Loss_Vol_Current,		C_SourceExist,			C_TotalVoltageLoseEventNo,       CAll_Loss_Vol_Attri7_Nature,	CAll_Loss_Vol_Degree,	CAll_Loss_Vol_Time},
	{CAux_Pow_Down_Current,		C_SourceExist,			C_ACPowerFailEventNo,            CAux_Pow_Down_Attri7_Nature,	CAux_Pow_Down_Degree,	CAux_Pow_Down_Time},
	{CRevPS_Vol_Current,		C_SourceExist,			C_ReversephaseVoltageEventNo,    CRevPS_Vol_Attri7_Nature,		CRevPS_Vol_Degree,		CRevPS_Vol_Time},
	{CRevPS_Curr_Current,		C_SourceExist,			C_ReversephaseCurrentEventNo,    CRevPS_Curr_Attri7_Nature,		CRevPS_Curr_Degree,		CRevPS_Curr_Time},
	{CPow_Down_Current,			C_SourceExist,			C_PowerfailEventNo,              CPow_Down_Attri7_Nature,		CPow_Down_Degree,		CPow_Down_Time},
	{CProgram_Current,			C_SourceExist,			C_ProgramEventNo,                CProgram_Attri7_Nature,			CProgram_Degree,		C_NULL},
	{CTol_Clear_Current,		C_SourceExist,			C_TolClearEventNo,               CTol_Clear_Attri7_Nature,		CTol_Clear_Degree,		C_NULL},
	{CDe_Clear_Current,			C_SourceExist,			C_DemandClearEventNo,            CDe_Clear_Attri7_Nature,		CDe_Clear_Degree,		C_NULL},
	{CEven_Clear_Current,		C_SourceExist,			C_EventClearEventNo,             CEven_Clear_Attri7_Nature,		CEven_Clear_Degree,		C_NULL},
	{CAdjTime_Current,			C_SourceExist,			C_AdjTimeEventNo,                CAdjTime_Attri7_Nature	,		CAdjTime_Degree,		C_NULL},
	{CProgPT_Current,			C_SourceExist,			C_ProgPTEventNo,                 CProgPT_Attri7_Nature,			CProgPT_Degree,			C_NULL},
	{CProgTZ_Current,			C_SourceExist,			C_ProgPZEventNo,                 CProgTZ_Attri7_Nature,			CProgTZ_Degree,			C_NULL},
	{CProgWRe_Current,			C_SourceExist,			C_ProgWReEventNo,                CProgWRe_Attri7_Nature,			CProgWRe_Degree,		C_NULL},
	{CProgSettD_Current,		C_SourceExist,			C_ProgSettDEventNo,              CProgSettD_Attri7_Nature,		CProgSettD_Degree,		C_NULL},
	{COpenW_Current,			C_SourceExist,			C_OpenMeterCoverEventNo,         COpenW_Attri7_Nature,			COpenW_Degree,			COpenW_Time},
	{COpenCW_Current,			C_SourceExist,			C_OpenTerminalCoverEventNo,      COpenCW_Attri7_Nature,			COpenCW_Degree,			COpenCW_Time},
	{CNoBal_Vol_Current,		C_SourceExist,			C_UnbanlanceVoltageEventNo,      CNoBal_Vol_Attri7_Nature,		CNoBal_Vol_Degree,		CNoBal_Vol_Time},
	{CNoBal_Curr_Current,		C_SourceExist,			C_UnbanlanceCurrentEventNo,      CNoBal_Curr_Attri7_Nature,		CNoBal_Curr_Degree,		CNoBal_Curr_Time},
	{CRelayOpen_Current,		C_SourceExist,			C_RelayOpenEventNo,              CRelayOpen_Attri7_Nature,		CRelayOpen_Degree,		C_NULL},
	{CRelayClose_Current,		C_SourceExist,			C_RelayCloseEventNo,             CRelayClose_Attri7_Nature,		CRelayClose_Degree,		C_NULL},
	{CProgHol_Current,			C_SourceExist,			C_ProgHolEventNo,                CProgHol_Attri7_Nature,			CProgHol_Degree,		C_NULL},
	{CProgAcC_Current,			C_SourceExist,			C_ProgAcCEventNo,                CProgAcC_Attri7_Nature,			CProgAcC_Degree,		C_NULL},
	{CProgReC_Current,			C_SourceExist,			C_ProgReCEventNo,                CProgReC_Attri7_Nature,			CProgReC_Degree,		C_NULL},
	{CProgTPara_Current,		C_SourceExist,			C_ProgTParaEventNo,              CProgTPara_Attri7_Nature,		CProgTPara_Degree,		C_NULL},
	{CProgLad_Current,			C_SourceExist,			C_ProgLadEventNo,                CProgLad_Attri7_Nature,			CProgLad_Degree,		C_NULL},
	{CProgKD_Current,			C_SourceExist,			C_Key_UpdateEventNo,             CProgKD_Attri7_Nature,			CProgKD_Degree,			C_NULL},
	{CAbnorC_Current,			C_SourceExist,			C_AbnorCEventNo,                 CAbnorC_Attri7_Nature,			CAbnorC_Degree,			C_NULL},
	{CBuyCurr_Current,			C_SourceExist,			C_BuyCurrEventNo,                CBuyCurr_Attri7_Nature,			CBuyCurr_Degree,		C_NULL},
	{CReturn_M_Current,			C_SourceExist,			C_ReturnMoneyEventNo,            CReturn_M_Attri7_Nature,		CReturn_M_Degree,		C_NULL},
	{CConM_Current,				C_SourceExist,			C_MagneticCheckEventNo,          CConM_Attri7_Nature,			CConM_Degree,			CConM_Time},
	{CRelayFa_Current,			C_SourceExist,			C_RelayFaEndEnEventNo,           CRelayFa_Attri7_Nature,			CRelayFa_Degree,		C_NULL},
	{CPowerFa_Current,			C_SourceExist,			C_PowerAbnormalEventNo,          CPowerFa_Attri7_Nature,			CPowerFa_Degree,		CPowerFa_Time},
	{CSevNoBal_Curr_Current,	C_SourceExist,			C_SUnbanlanceCurrentEventNo,     CSevNoBal_Curr_Attri7_Nature,	CSevNoBal_Curr_Degree,	CSevNoBal_Curr_Time},
	{CClockFa_Current,			C_SourceExist,			C_ClockFaEventNo,                CClockFa_Attri7_Nature,			CClockFa_Degree,		CClockFa_Time},
	{CMeterFa_Current,			C_SourceExist,			C_MeterFaEventNo,                CMeterFa_Attri7_Nature,			CMeterFa_Degree,		CMeterFa_Time},
#if 0
	{CTrend_Rev_Current,		C_SourceNon,			C_ReversecurrentEventNo,         CTrend_Rev_Attri7_Nature,		CTrend_Rev_Degree,		C_NULL},
#endif
    {CBroadcastTime_Current,	C_SourceExist,			C_BroadcastTimeEventNo,			CBroadcastTime_Attri7_Nature,		CBroadcastTime_Degree,		C_NULL},
	{CNeutralCurrentAbnormal_Current,	C_SourceExist,	C_NeutralCurrentAbnormalEventNo,		CNeutralCurrentAbnormal_Attri7_Nature,		CNeutralCurrentAbnormal_Degree,		CNeutralCurrentAbnormal_Time},
#if 0
	{CBroadTimeAbnormal_Current,	C_SourceExist,		C_BroadTimeAbnormalEventNo,		CBroadTimeAbnormal_Attri7_Nature,		CBroadTimeAbnormal_Degree,		C_NULL},
#endif
};
#define CurrentDataReadTable_Len  sizeof(CurrentDataReadTable)/sizeof(Str_CurrentDataReadTable_Type)

/***********************************************************************************
����ԭ�ͣ�uchar8 PF_GetAbs(uchar8 *V_ucSrc, uchar8 *V_ucDest, uchar8 V_ucNum)
����������ȡ����ֵ
���������*V_ucSrc��ԭʼ�����׵�ַ��
            V_ucNumԭʼ���ݳ��ȣ�ȡֵ��Χ1-4
���������*V_ucDest��ת��������ݣ�������ȸ���V_ucNum����
���ز����������Ƿ�Ϊ������C_Plus��C_Minus��C_Error
����˵�������V_ucSrcԭʼ���ݱ���Ϊhex��ʽ
���û��ƣ�
��    ע��
**********************************************************************************/
uchar8 PF_GetAbs(uchar8 *V_ucSrc, uchar8 *V_ucDest, uchar8 V_ucNum)
{
    long32 V_lBuff = 0;
    uchar8 V_uci, V_ucSign;

    if((V_ucNum == 0)
      ||(V_ucNum > 4))
    {
        return C_Error;
    }
    if((V_ucNum < 4) && (V_ucSrc[V_ucNum - 1] & 0x80))/*С��4�ֽڵĸ������ֽڲ�FF*/
    {
        for(V_uci = 0;V_uci < (4 - V_ucNum);V_uci ++)
        {
            V_lBuff <<= 8;
            V_lBuff |= 0xFF;
        }
    }
    for(V_uci = 0;V_uci < V_ucNum;V_uci ++)/*ԭʼ����ת��Ϊlong32*/
    {
        V_lBuff <<= 8;
		V_lBuff |= V_ucSrc[V_ucNum - V_uci - 1];
	}
    if(V_lBuff < 0)
    {
        V_lBuff = -V_lBuff;
        V_ucSign = C_Minus;
    }
    else
    {
        V_ucSign = C_Plus;
    }
    for(V_uci = 0;V_uci < V_ucNum;V_uci ++)
	{
		V_ucDest[V_uci] = (uchar8)V_lBuff;
		V_lBuff >>= 8;
	}
    return V_ucSign;
}

/***********************************************************************************
����ԭ�ͣ�uchar8 SF_HEXAddBytes(uchar8 *Add1, uchar8 *Add2, uchar8 *AddResult, uchar8 Len)
�������������ֽ�HEX���ݼӷ�
���������Add1Ϊ����1���ֽڵ�ַ
        Add2����2���ֽڵ�ַ
        AddResult�ʹ�ŵ�ַ
        Len���ݳ���
����������ۼӺ����ݴ��AddResult��ַ��ʼ��Len�ֽ�
���ز�����C_CY��ʾ����ֽ�λ��C_NoCY��ʾû�н�λ
����˵����1.ԭʼ������Ϊhex��ʽ��2.AddResult��ַ������Add1����Add2��ͬ
���û��ƣ�
��    ע��Add1,Add2����Ϊ�޷�����
**********************************************************************************/
uchar8 SF_HEXAddBytes(uchar8 *Add1, uchar8 *Add2, uchar8 *AddResult, uchar8 Len)
{
    uchar8 V_ucCY, V_uci;
    ushort16 V_usTemp = 0;

    V_ucCY = C_NoCY;
    for(V_uci = 0;V_uci < Len;V_uci ++)
    {
        V_usTemp = Add1[V_uci] + Add2[V_uci] + V_ucCY;

        if(V_usTemp & 0xFF00)
        {
            V_ucCY = C_CY;
        }
        else
        {
            V_ucCY = C_NoCY;
        }
        AddResult[V_uci] = (uchar8)V_usTemp;
    }
	return V_ucCY;
}

/***********************************************************************************
����ԭ�ͣ�uchar8 SF_HEXDECBytes(uchar8 *Dec1, uchar8 *Dec2, uchar8 *DecResult, uchar8 Len)
�������������ֽ�HEX���ݼ���
���������Dec1Ϊ���������ֽڵ�ַ, Dec2Ϊ�������ֽڵ�ַ, DecResult���ŵ�ַ, Len���ݳ���
�������������DecResult��ַ��ʼ��Len�ֽ�
���ز�����C_CY��ʾ����ֽ�λ��C_NoCY��ʾû�н�λ
����˵����1.ԭʼ������Ϊ�޷���hex��ʽ��2.��DecResult��ָ���ַ������Dec1����Dec2��ͬ
���û��ƣ�
��    ע��Add1,Add2����Ϊ�޷�����
**********************************************************************************/
uchar8 SF_HEXDECBytes(uchar8 *Dec1, uchar8 *Dec2, uchar8 *DecResult, uchar8 Len)
{
    uchar8 V_ucCY, V_uci, V_ucDecResult;
    ushort16 V_usDec1, V_usDec2;

    V_ucCY = C_NoCY;
    for(V_uci = 0;V_uci < Len;V_uci ++)
    {
        V_usDec1 = Dec1[V_uci];
        V_usDec2 = Dec2[V_uci];

        if(V_usDec1 >= (V_usDec2 + V_ucCY))  /*�������Ͱ��ֽ�С�ڼ������λ��־֮��*/
        {
            V_ucDecResult = V_usDec1 - (V_usDec2 + V_ucCY);
            V_ucCY = C_NoCY;
        }
        else
        {
            V_ucDecResult = (V_usDec1 + 0x0100) - (V_usDec2 + V_ucCY);
            V_ucCY = C_CY;
        }
        DecResult[V_uci] = V_ucDecResult;
    }
	return V_ucCY;
}

/***********************************************************************************
����ԭ�ͣ�SF_ReadLastEvt
��������������һ���¼���¼����ش���
���������pV_ulReadOAD:��ȡOAD���棬pV_ucDataBuff����ȡ���ݻ��棬pV_usLen�����泤��, V_ucNum����N��
���������pV_ucDataBuff����ȡ���ݻ��棬pV_usLen����ȡ���ݳ���
���ز�����ͬInF_GetData_Record_DataBase���ز���
����˵����
���û��ƣ�
��    ע��
**********************************************************************************/
uchar8 SF_ReadLastEvt(ulong32 *pV_ulReadOAD, uchar8 *pV_ucDataBuff, ushort16 *pV_usLen, uchar8 V_ucNum)
{
    Str_Read_T Str_Read_TTemp;
    uchar8 V_ucReadBuff[2], V_ucReturn;

    V_ucReadBuff[0] = 9;/*����9*/
    V_ucReadBuff[1] = V_ucNum;/*��N��*/

    Str_Read_TTemp.pV_ulROAD = pV_ulReadOAD;
    Str_Read_TTemp.pV_ucRST = V_ucReadBuff;
    Str_Read_TTemp.V_usROAD_Num = 1;
    Str_Read_TTemp.V_ucReadMode = C_OtherMode;
    Str_Read_TTemp.V_ucChannelNo = 0xFF;


    V_ucReturn = InF_GetData_Record_DataBase(&Str_Read_TTemp, pV_ucDataBuff, pV_usLen, C_NULL);

    return V_ucReturn;
}

/***********************************************************************************
����ԭ�ͣ� uchar8  InF_EventOADFind(uchar8 V_EventNo)
��������*�������ݱ�ʾ�����¼���¼�ţ����¼���¼��ͨ��ģ����
���������
    ulong32 V_DI�����ݱ�ʶ
�����������
���ز�����uchar8��EventNum, C_IDError
����˵�����¼���¼ģ�飬���ڻ�ȡNum�ţ�ͨ��ģ�������жϱ�ʶ���Ƿ���ȷ
���û��ƣ�
��    ע��δ������
***********************************************************************************/
ulong32  InF_EventOADFind(uchar8 V_EventNo)
{
	uchar8  V_uci;
	ulong32 V_Data_Id=C_OADError;

	for(V_uci=0;V_uci<EventMappingTable_Len;V_uci++)
	{
	   if(V_EventNo==EventMappingTable[V_uci].EventNo)
	   {
	  	 break;
	   }
	}

	if(V_uci < EventMappingTable_Len)
	{
		V_Data_Id = EventMappingTable[V_uci].WriteOAD;
	}
	return V_Data_Id;
}

/***********************************************************************************
����ԭ�ͣ�uchar8 SF_Judge_EventIntegrity(uchar8 V_ucEventNo)
�����������ж��¼�FLASH�е��¼�״̬
���������EventNo
��������������¼�����״̬
���ز����CC_IDError             ���ݱ�ʶ�����
           C_Happen_EventState	�¼�״̬���з����޻ָ�
          C_End_EventState	  	�¼�״̬�����з����޻ָ�
����˵������ֹ�¼�дFLASH����
���û��ƣ�д��Ϣʱ����
��    ע��
***********************************************************************************/
uchar8 SF_Judge_EventIntegrity(uchar8 V_ucEventNo)
{
	uchar8		V_ucJudgeBuffer[C_Judge_20BufferLength], V_ucNullJudgeBuffer[C_EventTimeLength] = {0};
	ushort16	V_usBufferLength = C_Judge_20BufferLength;
	uchar8		V_ucMode;
	ulong32		V_ulRead_OAD_Hp[3], V_ulRead_OAD_End[3];

	V_ulRead_OAD_Hp[0] = EventHappenEndTime[V_ucEventNo];
	V_ulRead_OAD_Hp[1] = CEventHPTime;
	V_ulRead_OAD_Hp[2] = 0xFFFFFFFF;
	V_ulRead_OAD_End[0] = EventHappenEndTime[V_ucEventNo];
	V_ulRead_OAD_End[1] = CEventEndTime;
	V_ulRead_OAD_End[2] = 0xFFFFFFFF;

    if( (V_ucEventNo < C_TolClearEventNo) || (V_ucEventNo == C_RelayFaEndEnEventNo) )
    {
        V_usBufferLength = C_Judge_20BufferLength;/*V0.2�������ȸ�ֵ*/

        V_ucMode = SF_ReadLastEvt(V_ulRead_OAD_Hp, &V_ucJudgeBuffer[C_Judge_StartBuffer0], &V_usBufferLength, (uchar8)V_ulRead_OAD_Hp[0]);/*��FLASH�����һ���¼���¼����ʱ��*/
        if(V_ucMode == C_OK)
        {
            V_usBufferLength = C_Judge_20BufferLength - 7;/*V0.2�������ȸ�ֵ*/
            V_ucMode = SF_ReadLastEvt(V_ulRead_OAD_End, &V_ucJudgeBuffer[C_Judge_TimeEndBuffer], &V_usBufferLength, (uchar8)V_ulRead_OAD_End[0]);/*��FLASH�����һ���¼���¼����ʱ��*/
            if(V_ucMode == C_OK)
            {
                if( (PF_Campare_Data(&V_ucJudgeBuffer[C_Judge_StartBuffer0], &V_ucNullJudgeBuffer[C_Judge_StartBuffer0], C_EventTimeLength) != C_Equal)
                    &&(PF_Campare_Data(&V_ucJudgeBuffer[C_Judge_TimeEndBuffer], &V_ucNullJudgeBuffer[C_Judge_StartBuffer0], C_EventTimeLength) == C_Equal) )
                {
                    return(C_Happen_EventState);
                }
                else
                {
                    return(C_End_EventState);
                }
            }
            else
            {
                return(C_Error);
            }
        }
        else
        {
            return(C_Error);
        }
    }
    else
    {
        return(C_IDError);
    }
}

/***********************************************************************************
����ԭ�ͣ�uchar8 Get_E_DalayTime(uchar8 EventNo)
�����������ж��¼��ж���ʱʱ��
���������EventNo
��������������¼�����״̬
���ز�����CC_IDError             	���ݱ�ʶ�����
          	C_Happen_EventState		�¼�״̬���з����޻ָ�
        	C_End_EventState	  	�¼�״̬�����з����޻ָ�
����˵������ֹ�¼�дFLASH����
���û��ƣ�д��Ϣʱ����
��    ע��
**********************************************************************************/
uchar8 SF_Get_Event_DalayTime(uchar8 EventNo)
{
	uchar8	V_ucJudgeBuffer1, V_ucMode;
	ushort16 V_usBufferLength = C_DelayTimeLength, V_usEncode;

	if( (EventNo <= C_NeutralCurrentAbnormalEventNo) && (EventNo != C_PowerAbnormalEventNo) )
	{
		if(Event_Delaytime[EventNo] != C_NULL)
		{
			V_ucMode = InF_GetData_ObjectManage(Event_Delaytime[EventNo], &V_ucJudgeBuffer1, &V_usBufferLength, &V_usEncode);/*��FLASH�����һ���¼���¼����ʱ��*/
			if( (EventNo == C_TotalVoltageLoseEventNo) || (EventNo == C_PowerfailEventNo) )
			{
				if(GV_ucEvent_Hstate[EventNo] != C_Happen_EventState)
				{
					V_ucMode = C_JudgeTimeError;
				}
			}
			if(V_ucMode == C_OK)
			{
				return(V_ucJudgeBuffer1);
			}
			else
			{
				return(Event_DDelaytime[EventNo]);
			}
		}
		else
		{
			return(Event_DDelaytime[EventNo]);
		}
	}
	return(C_JudgeTimeError);
}



/***********************************************************************************
����ԭ�ͣ�uchar8 SF_Get_TotalVoltageLose_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
�����������ж�ȫʧѹ��ǰ״̬
���������V_ucEventNo���¼��ţ���Hstate����ʷ״̬��
��������������¼���ǰ����״̬
���ز����CC_Happen_V_ucEventState	�¼�״̬���з����޻ָ�
          C_End_EventState	  	�¼�״̬�����з����޻ָ�
����˵�����ж��¼���ǰ״̬��
���û��ƣ��¼��жϺ�������
��    ע��
**********************************************************************************/
uchar8 SF_Get_TotalVoltageLose_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
	uchar8	V_ucJudgeBuffer1[C_4Volage_Length], V_ucJudgeBuffer2[C_4Curr_Length];/*��������ѹbuffer*/
	ushort16 V_usJudgeBufferLength1 = C_4Volage_Length, V_usJudgeBufferLength2 = C_4Curr_Length, V_usEncode;

	if(InF_GetData_ObjectManage(CLoss_Volage_Vol, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)/*��ȡȫʧѹ�жϵ�ѹ*/
	{
		return(V_ucHstate);
	}

    V_usJudgeBufferLength1 = C_4Volage_Length;      /*V0.2�������ȸ�ֵ*/
	if(InF_GetData_ObjectManage(CPhaseFF_Volage, &V_ucJudgeBuffer1[C_JudgeVolage_Buffer1], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)/*����ǰ��ѹ*/
	{
		return(V_ucHstate);
	}

	if(InF_GetData_ObjectManage(CLoss_Volage_Curr, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usJudgeBufferLength2, &V_usEncode) != C_OK)/*��ȡȫʧѹ�жϵ���*/
	{
		return(V_ucHstate);
	}

    V_usJudgeBufferLength2 = C_4Curr_Length;    /*V0.2�������ȸ�ֵ*/
	if(InF_GetData_ObjectManage(CPhaseFF_Curr, &V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], &V_usJudgeBufferLength2, &V_usEncode) != C_OK)/*����ǰ����, ��λС������*/
	{
		return(V_ucHstate);
	}

	V_ucJudgeBuffer2[C_Judge_StartBuffer2] = C_NULL;/*�жϵ��������ֽ���0*/
    V_ucJudgeBuffer2[C_Judge_StartBuffer3] = C_NULL;

	PF_GetAbs(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], &V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], C_Curr4Bytes_Length);/*A�����ȡ����ֵ*/
	PF_GetAbs(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer2], &V_ucJudgeBuffer2[C_JudgeCurr_Buffer2], C_Curr4Bytes_Length);/*B�����ȡ����ֵ*/
	PF_GetAbs(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer3], &V_ucJudgeBuffer2[C_JudgeCurr_Buffer3], C_Curr4Bytes_Length);/*C�����ȡ����ֵ*/

	if((PF_Campare_Data(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer1], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_LessThan)
		&&(PF_Campare_Data(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer2], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_LessThan)
		&&(PF_Campare_Data(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer3], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_LessThan))
	{
		if( (PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_Curr_Length) == C_GreaterThan)
            || (PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer2], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_Curr_Length) == C_GreaterThan)
            || (PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer3], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_Curr_Length) == C_GreaterThan) )
		{
            return(C_Happen_EventState);
        }
		else
		{
            return(C_End_EventState);
		}
	}
	else
	{
		return(C_End_EventState);
	}
}

/***********************************************************************************
����ԭ�ͣ�uchar8 SF_Get_Powerfail_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
�����������жϵ��統ǰ״̬
���������V_ucEventNo�¼��ţ�Hstate����ʷ״̬��
��������������¼���ǰ����״̬
���ز����CC_Happen_V_ucEventState	�¼�״̬���з����޻ָ�
          C_End_EventState	  	�¼�״̬�����з����޻ָ�
����˵�����ж��¼���ǰ״̬��
���û��ƣ��¼��жϺ�������
��    ע��
**********************************************************************************/
uchar8 SF_Get_Powerfail_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
	uchar8	V_ucJudgeBuffer1[C_4Volage_Length];/*��������ѹbuffer*/
	ushort16 V_usJudgeBufferLength1 = C_4Volage_Length, V_usEncode;

	if(InF_GetData_ObjectManage(CLoss_Volage_Vol, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)/*��ȡȫʧѹ�жϵ�ѹ*/
	{
		return(V_ucHstate);
	}

    V_usJudgeBufferLength1 = C_4Volage_Length;      /*V0.2�������ȸ�ֵ*/
	if(InF_GetData_ObjectManage(CPhaseFF_Volage, &V_ucJudgeBuffer1[C_JudgeVolage_Buffer1], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)/*����ǰ��ѹ*/
	{
		return(V_ucHstate);
	}

	if( (PF_Campare_Data(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer1], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_LessThan)
		&&(PF_Campare_Data(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer2], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_LessThan)
		&&(PF_Campare_Data(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer3], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_LessThan) )
	{
        return(C_Happen_EventState);
	}
	else
	{
		return(C_End_EventState);
	}
}

/***********************************************************************************
����ԭ�ͣ�uchar8 SF_Get_PeripheralEvt_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
��������������ǡ�����ť�ǡ��ų����š�������Դʧ���¼�
���������EventNo(�¼���)Hstate����ʷ״̬��
��������������¼���ǰ����״̬
���ز����CC_Happen_V_ucEventState		�¼�״̬���з����޻ָ�
          C_End_EventState	  	�¼�״̬�����з����޻ָ�
����˵�����ж��¼���ǰ״̬��
���û��ƣ��¼��жϺ�������
��    ע��
**********************************************************************************/
uchar8 SF_Get_PeripheralEvt_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
    uchar8 V_ucStatus = C_Error, V_ucType;
	uchar8 V_ucHpStatus, V_ucEndStatus;

    if(V_ucEventNo == C_ACPowerFailEventNo)/*������Դʧ��*/
    {
        V_ucType = C_CheckAuPower;
		V_ucHpStatus = C_Valid;
		V_ucEndStatus = C_Invalid;
    }
    else if(V_ucEventNo == C_OpenMeterCoverEventNo)/*�����*/
    {
        V_ucType = C_KeyOpenCover;
		V_ucHpStatus = C_Invalid;
		V_ucEndStatus = C_Valid;
    }
    else if(V_ucEventNo == C_OpenTerminalCoverEventNo)/*����ť��*/
    {
        V_ucType = C_KeyOpenTerminal;
		V_ucHpStatus = C_Invalid;
		V_ucEndStatus = C_Valid;
    }
    else if(V_ucEventNo == C_MagneticCheckEventNo)/*�㶨�ų�����*/
    {
        V_ucType = C_Magnetic;
		V_ucHpStatus = C_Valid;
		V_ucEndStatus = C_Invalid;
    }
    else
    {
        return(V_ucHstate);
    }
	V_ucStatus = InF_GetPeripheralStatus(V_ucType);

    if(V_ucStatus == V_ucHpStatus)
	{
		return(C_Happen_EventState);
	}
	else if(V_ucStatus == V_ucEndStatus)
	{
        return(C_End_EventState);
    }
    else
    {
        return(V_ucHstate);
    }
}

/***********************************************************************************
����ԭ�ͣ�uchar8 Get_OverForwardActive_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
���������������й���������
���������EventNo(�¼���) Hstate����ʷ״̬��
��������������¼���ǰ����״̬
���ز����CC_Happen_V_ucEventState		�¼�״̬���з����޻ָ�
          C_End_EventState	  	�¼�״̬�����з����޻ָ�
          C_Close_EventState		�¼�״̬���ر�
����˵�����ж��¼���ǰ״̬��
���û��ƣ��¼��жϺ�������
��    ע��
**********************************************************************************/
uchar8 SF_Get_OverActiveDemand_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
 	uchar8	V_ucJudgeBuffer1[C_Demand_Length], V_ucJudgeBuffer2[C_Demand_Length], V_ucJudgeBuffer3[C_Demand_Length] = {0};
 	ushort16 V_usBufferLength1 = C_Demand_Length, V_usEncode;
    uchar8  V_ucTemp = C_End_EventState, V_ucSign;

    if(V_ucEventNo == C_OverForwardActiveEventNo)
    {
        if(InF_GetData_ObjectManage(CPosAcDemandOv_De_LowLim, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) != C_OK)/*�й����������¼�������������, Ϊ0�����عر�*/
        {
            return(V_ucHstate);
        }
    }
    else if(V_ucEventNo == C_OverReverseActiveEventNo)
    {
        if(InF_GetData_ObjectManage(CRevAcDemandOv_De_LowLim, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) != C_OK)/*�й����������¼�������������, Ϊ0�����عر�*/
        {
            return(V_ucHstate);
        }
    }
    else
    {
        return(V_ucHstate);
    }
  	if(PF_Campare_Data(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_Demand_Length) == C_Equal)
 	{
 		return(C_Close_EventState);
 	}
    V_usBufferLength1 = C_Demand_Length;
 	if(InF_GetData_ObjectManage(CCurr_AcDemand, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) != C_OK)	/*��ǰ�й�����*/
 	{
 		return(V_ucHstate);
 	}
    V_ucSign = PF_GetAbs(V_ucJudgeBuffer2, V_ucJudgeBuffer2, C_Curr4Bytes_Length);/*��ȡ��ǰ�й����ʷ���, ��ȡ����ֵ*/

 	if(PF_Campare_Data(&V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Demand_Length) == C_GreaterThan)
    {
        if(V_ucEventNo == C_OverForwardActiveEventNo)
        {
			if(V_ucSign != C_Minus)/*�й����ʷ���Ϊ�����Ҵ��ڷ�ֵ*/
            {
                V_ucTemp = C_Happen_EventState;
            }
        }
        else if(V_ucEventNo == C_OverReverseActiveEventNo)
        {
			if(V_ucSign == C_Minus)/*�й����ʷ���Ϊ�����Ҵ��ڷ�ֵ*/
            {
                V_ucTemp = C_Happen_EventState;
            }
        }
        else
        {
            return(V_ucHstate);
        }
    }
	return V_ucTemp;
}


/***********************************************************************************
����ԭ�ͣ�uchar8 SF_Get_OverIdleDemand_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
����������1-4�����޹���������
���������EventNo(�¼���) Hstate����ʷ״̬��
��������������¼���ǰ����״̬
���ز����CC_Happen_V_ucEventState		�¼�״̬���з����޻ָ�
          C_End_EventState	  	�¼�״̬�����з����޻ָ�
          C_Close_EventState		�¼�״̬���ر�
����˵�����ж��¼���ǰ״̬��
���û��ƣ��¼��жϺ�������
��    ע��
**********************************************************************************/
uchar8 SF_Get_OverIdleDemand_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
 	uchar8	V_ucJudgeBuffer1[C_Demand_Length], V_ucJudgeBuffer2[C_Demand_Length], V_ucJudgeBuffer3[C_Demand_Length]={0};
 	uchar8	V_ucJudgeBuffer4[C_Demand_Length];				/*��ǰ�й�����*/
 	ushort16 V_usBufferLength1 = C_Demand_Length, V_usEncode;
    uchar8  V_ucTemp = C_End_EventState, V_ucSign[2];

 	if(InF_GetData_ObjectManage(CReDemandOv_De_LowLim, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) != C_OK)/*�޹����������¼�������������, Ϊ0�����عر�*/
 	{
 		return(V_ucHstate);
 	}
 	if(PF_Campare_Data(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_Demand_Length)==C_Equal)
 	{
 		return(C_Close_EventState);
 	}
    V_usBufferLength1 = C_Demand_Length; /*V0.2�������ȸ�ֵ*/
 	if(InF_GetData_ObjectManage(CCurr_ReDemand, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) != C_OK)	/*�޹�����*/
 	{
 		return(V_ucHstate);
 	}
    V_usBufferLength1 = C_Demand_Length;
 	if(InF_GetData_ObjectManage(CCurr_AcDemand, &V_ucJudgeBuffer4[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) != C_OK)	/*��ǰ�й�����*/
 	{
 		return(V_ucHstate);
 	}
    V_ucSign[0] = PF_GetAbs(V_ucJudgeBuffer2, V_ucJudgeBuffer2, C_Curr4Bytes_Length);/*��ȡ��ǰ�޹����ʷ���, ��ȡ����ֵ*/
    V_ucSign[1] = PF_GetAbs(V_ucJudgeBuffer4, V_ucJudgeBuffer4, C_Curr4Bytes_Length);/*��ȡ��ǰ�й����ʷ���, ��ȡ����ֵ*/

    if(PF_Campare_Data(&V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Demand_Length) == C_GreaterThan)
    {
        if(V_ucEventNo == C_1OverIdleDemandEventNo)
        {
            if((V_ucSign[0] != C_Minus)/*�޹����ʷ���Ϊ�����Ҵ��ڷ�ֵ*/
                &&(V_ucSign[1] != C_Minus))/*�й����ʷ���Ϊ����*/
            {
                V_ucTemp = C_Happen_EventState;
            }
        }
        else if(V_ucEventNo == C_2OverIdleDemandEventNo)
        {
            if((V_ucSign[0] != C_Minus)/*�޹����ʷ���Ϊ�����Ҵ��ڷ�ֵ*/
                &&(V_ucSign[1] == C_Minus))/*�й����ʷ���Ϊ����*/
            {
                V_ucTemp = C_Happen_EventState;
            }
        }
        else if(V_ucEventNo == C_3OverIdleDemandEventNo)
        {
            if((V_ucSign[0] == C_Minus)/*�޹����ʷ���Ϊ�����Ҵ��ڷ�ֵ*/
                &&(V_ucSign[1] == C_Minus))/*�й����ʷ���Ϊ����*/
            {
                V_ucTemp = C_Happen_EventState;
            }
        }
        else if(V_ucEventNo == C_4OverIdleDemandEventNo)
        {
            if((V_ucSign[0] == C_Minus)/*�޹����ʷ���Ϊ�����Ҵ��ڷ�ֵ*/
                &&(V_ucSign[1] != C_Minus))/*�й����ʷ���Ϊ����*/
            {
                V_ucTemp = C_Happen_EventState;
            }
        }
        else
        {
            return(V_ucHstate);
        }
    }
    return V_ucTemp;
}

/***********************************************************************************
����ԭ�ͣ�uchar8 SF_Get_lossvoltage_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
����������ʧѹ
���������EventNo�¼��ţ�Hstate����ʷ״̬��
��������������¼���ǰ����״̬
���ز����CC_Happen_V_ucEventState		�¼�״̬���з����޻ָ�
          C_End_EventState	  		�¼�״̬�����з����޻ָ�
          C_Close_EventState		�¼�״̬���ر�
����˵�����ж��¼���ǰ״̬��
���û��ƣ��¼��жϺ�������
��    ע��
**********************************************************************************/
uchar8 SF_Get_lossvoltage_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
	uchar8	V_ucJudgeBuffer1[C_Volage_Length], V_ucJudgeBuffer2[C_Volage_Length], V_ucJudgeBuffer3[C_Curr_Length];/*������ֵ*/
	uchar8	V_ucJudgeBuffer4[C_Volage_Length], V_ucJudgeBuffer5[C_Curr_Length], V_ucJudgeBuffer6[C_Volage_Length] = {0};/*��ѹ���������ж�����Ϊ��*/
	ushort16 V_usJudgeBufferLength1 = C_Volage_Length, V_usJudgeBufferLength2 = C_Curr_Length, V_usEncode;
	ulong32	V_ulVolage, V_ulCurr;

	if(GV_ucEvent_Hstate[C_TotalVoltageLoseEventNo] == C_Happen_EventState)/*ȫʧѹ������ʧѹ����*/
	{
		return(C_Close_EventState);
	}
	switch(V_ucEventNo)
	{
		case	C_AlossvoltageEventNo:
				V_ulVolage = CPhaseA_Volage;
				V_ulCurr = CPhaseA_Curr_4Dig;
				break;
		case	C_BlossvoltageEventNo:
				V_ulVolage = CPhaseB_Volage;
				V_ulCurr = CPhaseB_Curr_4Dig;
				break;
		case	C_ClossvoltageEventNo:
				V_ulVolage = CPhaseC_Volage;
				V_ulCurr = CPhaseC_Curr_4Dig;
				break;
		default:
				return(V_ucHstate);
	}
	if(InF_GetData_ObjectManage(CLossVolage_Vol_UpLim, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)/*ʧѹ�¼���ѹ��������*/
	{
		return(V_ucHstate);
	}
	if(PF_Campare_Data(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer6[C_Judge_StartBuffer0], C_Volage_Length) == C_Equal)
	{
		return(C_Close_EventState);
	}
    V_usJudgeBufferLength1 = C_Volage_Length;
	if(InF_GetData_ObjectManage(CLossVolage_Vol_LowLim, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)/*ʧѹ�¼���ѹ�ָ�����*/
	{
		return(V_ucHstate);
	}
	if(InF_GetData_ObjectManage(CLossVolage_Curr_LowLim, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_usJudgeBufferLength2, &V_usEncode) != C_OK)/*ʧѹ�¼�������������*/
	{
		return(V_ucHstate);
	}
    V_usJudgeBufferLength1 = C_Volage_Length;
	if(InF_GetData_ObjectManage(V_ulVolage, &V_ucJudgeBuffer4[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
    V_usJudgeBufferLength2 = C_Curr_Length; /*V0.2�������ȸ�ֵ*/
	if(InF_GetData_ObjectManage(V_ulCurr, &V_ucJudgeBuffer5[C_Judge_StartBuffer0], &V_usJudgeBufferLength2, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
    PF_GetAbs(V_ucJudgeBuffer5, V_ucJudgeBuffer5, C_Curr4Bytes_Length);/*ȡ��������ֵ*/

	if( (PF_Campare_Data(&V_ucJudgeBuffer4[C_Judge_StartBuffer0], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_LessThan)
		&&(PF_Campare_Data(&V_ucJudgeBuffer5[C_Judge_StartBuffer0], &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_Curr4Dig_Length) == C_GreaterThan) )
	{
		return(C_Happen_EventState);
	}
	else
	{
		if(PF_Campare_Data(&V_ucJudgeBuffer4[C_Judge_StartBuffer0], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_Volage_Length) == C_GreaterThan)
		{
			return(C_End_EventState);
		}
		else
		{
			return(V_ucHstate);
		}
	}
}

/***********************************************************************************
����ԭ�ͣ�uchar8 SF_Get_Lessvoltage_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
����������Ƿѹ
���������EventNo�¼��ţ�Hstate����ʷ״̬��
��������������¼���ǰ����״̬
���ز����CC_Happen_V_ucEventState		�¼�״̬���з����޻ָ�
          C_End_EventState	  		�¼�״̬�����з����޻ָ�
          C_Close_EventState		�¼�״̬���ر�
����˵�����ж��¼���ǰ״̬��
���û��ƣ��¼��жϺ�������
��    ע��
**********************************************************************************/
uchar8 SF_Get_Lessvoltage_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
	uchar8	V_ucJudgeBuffer1[C_Volage_Length], V_ucJudgeBuffer2[C_Volage_Length], V_ucJudgeBuffer3[C_Volage_Length] = {0};
	ushort16 V_usJudgeBufferLength = C_Volage_Length, V_usEncode;
	ulong32	V_ulVolage;
	switch(V_ucEventNo)
	{
		case	C_ALessvoltageEventNo:
				V_ulVolage = CPhaseA_Volage;
				break;
		case	C_BLessvoltageEventNo:
				V_ulVolage = CPhaseB_Volage;
				break;
		case	C_CLessvoltageEventNo:
				V_ulVolage = CPhaseC_Volage;
				break;
		default:
				return(V_ucHstate);
	}
	if(InF_GetData_ObjectManage(CLowVolage_Vol_UpLim, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
    V_usJudgeBufferLength = C_Volage_Length;
	if(InF_GetData_ObjectManage(V_ulVolage, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usJudgeBufferLength, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
	if(PF_Campare_Data(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_Volage_Length) == C_Equal)
	{
		return(C_Close_EventState);
	}
	else
	{
		if(PF_Campare_Data(&V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_LessThan)
		{
			return(C_Happen_EventState);
		}
		else
		{
			return(C_End_EventState);
		}
	}
}

/***********************************************************************************
����ԭ�ͣ�uchar8 SF_Get_Overvoltage_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
��������: ��ѹ
���������EventNo���¼��ţ���Hstate����ʷ״̬��
��������������¼���ǰ����״̬
���ز����CC_Happen_V_ucEventState		�¼�״̬���з����޻ָ�
          C_End_EventState	  		�¼�״̬�����з����޻ָ�
          C_Close_EventState		�¼�״̬���ر�
����˵�����ж��¼���ǰ״̬��
���û��ƣ��¼��жϺ�������
��    ע��
**********************************************************************************/
uchar8 SF_Get_Overvoltage_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
	uchar8	V_ucJudgeBuffer1[C_Volage_Length], V_ucJudgeBuffer2[C_Volage_Length], V_ucJudgeBuffer3[C_Volage_Length] = {0};
	ushort16 V_usJudgeBufferLength = C_Volage_Length, V_usEncode;
	ulong32	V_ulVolage;
	switch(V_ucEventNo)
	{
		case	C_AOvervoltageEventNo:
				V_ulVolage = CPhaseA_Volage;
				break;
		case	C_BOvervoltageEventNo:
				V_ulVolage = CPhaseB_Volage;
				break;
		case	C_COvervoltageEventNo:
				V_ulVolage = CPhaseC_Volage;
				break;
		default:
				return(V_ucHstate);
	}
	if(GV_ucEvent_Hstate[C_PowerfailEventNo] == C_Happen_EventState)	/*���緢�����¼�����*/
	{
		return(C_Close_EventState);
	}
	if(InF_GetData_ObjectManage(COverVolage_Vol_LowLim, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
    V_usJudgeBufferLength = C_Volage_Length;
	if(InF_GetData_ObjectManage(V_ulVolage, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usJudgeBufferLength, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
	if(PF_Campare_Data(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_Volage_Length) == C_Equal)
	{
		return(C_Close_EventState);
	}
	else
	{
		if(PF_Campare_Data(&V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_GreaterThan)
		{
			return(C_Happen_EventState);
		}
		else
		{
			return(C_End_EventState);
		}
	}
}

/***********************************************************************************
����ԭ�ͣ�uchar8 SF_Get_Lossphase_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
��������: ����
���������EventNo���¼��ţ���Hstate����ʷ״̬��
��������������¼���ǰ����״̬
���ز����CC_Happen_V_ucEventState		�¼�״̬���з����޻ָ�
          C_End_EventState	  		�¼�״̬�����з����޻ָ�
          C_Close_EventState		�¼�״̬���ر�
����˵�����ж��¼���ǰ״̬��
���û��ƣ��¼��жϺ�������
��    ע��
**********************************************************************************/
uchar8 SF_Get_Lossphase_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
 	uchar8	V_ucJudgeBuffer1[C_Volage_Length], V_ucJudgeBuffer2[C_Curr_Length];/*������ֵ*/
 	uchar8	V_ucJudgeBuffer3[C_Volage_Length], V_ucJudgeBuffer4[C_Curr_Length], V_ucJudgeBuffer5[C_Volage_Length] = {0};/*��ѹ���������ж�����Ϊ��*/
 	ushort16 V_usJudgeBufferLength1 = C_Volage_Length, V_usJudgeBufferLength2 = C_Curr_Length, V_usEncode;
 	ulong32	V_ulVolage, V_ulCurr;

	if(GV_ucEvent_Hstate[C_PowerfailEventNo] == C_Happen_EventState)/*���緢�����¼�����*/
	{
		return(C_Close_EventState);
	}
	switch(V_ucEventNo)
	{
		case	C_ALossphaseEventNo:
				V_ulVolage = CPhaseA_Volage;
				V_ulCurr = CPhaseA_Curr_4Dig;
				break;
		case	C_BLossphaseEventNo:
				V_ulVolage = CPhaseB_Volage;
				V_ulCurr = CPhaseB_Curr_4Dig;
				break;
		case	C_CLossphaseEventNo:
				V_ulVolage = CPhaseC_Volage;
				V_ulCurr = CPhaseC_Curr_4Dig;
				break;
		default:
				return(V_ucHstate);
	}
	if(InF_GetData_ObjectManage(CBreakVol_Vol_UpLim, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)	/*�����¼���ѹ��������*/
	{
		return(V_ucHstate);
	}
	if(InF_GetData_ObjectManage(CBreakVol_Curr_UpLim, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usJudgeBufferLength2, &V_usEncode) != C_OK)	/*�����¼�������������*/
	{
		return(V_ucHstate);
	}
    V_usJudgeBufferLength1 = C_Volage_Length;
 	if(InF_GetData_ObjectManage(V_ulVolage, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
    V_usJudgeBufferLength2 = C_Curr_Length; /*V0.2�������ȸ�ֵ*/
 	if(InF_GetData_ObjectManage(V_ulCurr, &V_ucJudgeBuffer4[C_Judge_StartBuffer0], &V_usJudgeBufferLength2, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
	PF_GetAbs(V_ucJudgeBuffer4, V_ucJudgeBuffer4, C_Curr4Bytes_Length);/*����ȡ����ֵ*/

 	if(PF_Campare_Data(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer5[C_Judge_StartBuffer0], C_Volage_Length) == C_Equal)
	{
		return(C_Close_EventState);
	}
	else
	{
		if( (PF_Campare_Data(&V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_LessThan)
			&&(PF_Campare_Data(&V_ucJudgeBuffer4[C_Judge_StartBuffer0], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_JudgeCurr_Length) == C_LessThan) )
		{
			return(C_Happen_EventState);
		}
		else
		{
			return(C_End_EventState);
		}
	}
}
/***********************************************************************************
����ԭ�ͣ�uchar8 SF_Get_ReversePhaseFlag(uchar8 *pV_Buffer)
��������: ��ѹ��������
���������pV_Buffer������ͺţ�C_3P4W/C_3P3W
�����������
���ز����C��ѹ����״̬
����˵����
���û��ƣ��¼��жϺ�������
��    ע��
**********************************************************************************/
uchar8 SF_Get_ReversePhaseVoltageFlag(uchar8 *pV_Buffer)
{
	uchar8	V_ucJudgeBuffer1[CLVolFF_Phase];												/*���ܱ����*/
	uchar8	V_ucJudgeBuffer2[CLPhaseA_Volage];
	ushort16 V_usJudgeBufferLength1 = CLVolA_Phase, V_usEncode;

	InF_GetData_ObjectManage(CVolA_Phase, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode);		/*�����ѹ���*/

    V_usJudgeBufferLength1 = CLVolB_Phase;
	InF_GetData_ObjectManage(CVolB_Phase, &V_ucJudgeBuffer1[C_Judge_StartBuffer2], &V_usJudgeBufferLength1, &V_usEncode);

    V_usJudgeBufferLength1 = CLVolC_Phase;
	InF_GetData_ObjectManage(CVolC_Phase, &V_ucJudgeBuffer1[C_Judge_StartBuffer4], &V_usJudgeBufferLength1, &V_usEncode);

    V_usJudgeBufferLength1 = CLPhaseA_Volage;
	InF_GetData_ObjectManage(CPhaseA_Volage, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode);

	if((V_ucJudgeBuffer2[C_Judge_StartBuffer0]==C_NULL)&&(V_ucJudgeBuffer2[C_Judge_StartBuffer1] == C_NULL))
	{
		return(C_Error);
	}
	if(*pV_Buffer == C_3P4W)
	{
		if(PF_Campare_Data(&V_ucJudgeBuffer1[C_Judge_StartBuffer4], &V_ucJudgeBuffer1[C_Judge_StartBuffer2], C_PhaseAngle) == C_GreaterThan)
		{
			return(C_Positivephase);/*���C���>B��ǣ�����������*/
		}
		else
		{
			return(C_Reversephase);
		}
	}
	else
	{
		if(*pV_Buffer == C_3P3W)
		{
			if((PF_Campare_Data(&V_ucJudgeBuffer1[C_Judge_StartBuffer4], (uchar8 *)C_uc3P3WVotageAngle1, C_PhaseAngle) == C_GreaterThan)
			&&(PF_Campare_Data(&V_ucJudgeBuffer1[C_Judge_StartBuffer4], (uchar8 *)C_uc3P3WVotageAngle2, C_PhaseAngle) == C_LessThan))
			{
				return(C_Reversephase);/*���C�����30�Ⱥ�115�����ڣ�����������*/
			}
			else
			{
				return(C_Positivephase);
			}
		}
		else
		{
			return(C_Error);
		}

	}
}
/***********************************************************************************
����ԭ�ͣ�uchar8 SF_Get_ReverseCurrentFlag(uchar8 *pV_Buffer)
��������: ������������
���������pV_Buffer������ͺţ�C_3P4W/C_3P3W
�����������
���ز����C��������״̬
����˵����
���û��ƣ��¼��жϺ�������
��    ע��
**********************************************************************************/
uchar8 SF_Get_ReverseCurrentFlag(uchar8 *pV_Buffer)
{
	uchar8	V_ucJudgeBuffer1[C_Judge_20BufferLength];												/*���ܱ����*/
	uchar8	V_ucJudgeBuffer2[C_Judge_20BufferLength];
	ushort16 V_usJudgeBufferLength1 = C_Judge_20BufferLength, V_usEncode;

	InF_GetData_ObjectManage(CCurrA_Phase, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode);		/*����������*/

    V_usJudgeBufferLength1 = CLCurrB_Phase;
	InF_GetData_ObjectManage(CCurrB_Phase, &V_ucJudgeBuffer1[C_Judge_StartBuffer2], &V_usJudgeBufferLength1, &V_usEncode);

    V_usJudgeBufferLength1 = CLCurrC_Phase;
	InF_GetData_ObjectManage(CCurrC_Phase, &V_ucJudgeBuffer1[C_Judge_StartBuffer4], &V_usJudgeBufferLength1, &V_usEncode);

    V_usJudgeBufferLength1 = C_Judge_20BufferLength;	/*V0.2�������ȸ�ֵ*/
	InF_GetData_ObjectManage(CPhaseA_Curr, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode);

	if( (V_ucJudgeBuffer2[C_Judge_StartBuffer0] == C_NULL)
        && (V_ucJudgeBuffer2[C_Judge_StartBuffer1] == C_NULL)
        && (V_ucJudgeBuffer2[C_Judge_StartBuffer2] == C_NULL) )
	{
		return(C_Error);
	}
	if(*pV_Buffer == C_3P4W)
	{		/*��B�������-A�������ǣ�<��c�������-A�������ǣ�*/
		SF_HEXDECBytes(&V_ucJudgeBuffer1[C_Judge_StartBuffer2], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer1[C_Judge_StartBuffer2], C_PhaseAngle);/*B�����������*/
		SF_HEXDECBytes(&V_ucJudgeBuffer1[C_Judge_StartBuffer4], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer1[C_Judge_StartBuffer4], C_PhaseAngle);/*C�����������*/

        if(PF_Campare_Data(&V_ucJudgeBuffer1[C_Judge_StartBuffer4], &V_ucJudgeBuffer1[C_Judge_StartBuffer2], C_PhaseAngle) == C_GreaterThan)
		{
			return(C_Positivephase);/*���C���>B��ǣ�����������*/
		}
		else
		{
			return(C_Reversephase);
		}
	}
	else
	{
		if(*pV_Buffer == C_3P3W)
		{
	 		if( (PF_Campare_Data(&V_ucJudgeBuffer1[C_Judge_StartBuffer4], (uchar8 *)C_uc3P3WCurrentAngle1, C_PhaseAngle) == C_GreaterThan)
                &&(PF_Campare_Data(&V_ucJudgeBuffer1[C_Judge_StartBuffer4], (uchar8 *)C_uc3P3WCurrentAngle2, C_PhaseAngle) == C_LessThan) )
	 		{
	 			return(C_Reversephase);/*���C�����90�Ⱥ�150�����ڣ�����������*/
	 		}
	 		else
	 		{
	 			return(C_Positivephase);
	 		}
		}
		else
		{
			return(C_Error);
		}

	}
}
/***********************************************************************************
����ԭ�ͣ�uchar8 SF_Get_ReversephaseVoltage_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
��������: ��ѹ������
���������EventNo���¼��ţ���Hstate����ʷ״̬��
��������������¼���ǰ����״̬
���ز����CC_Happen_V_ucEventState		�¼�״̬���з����޻ָ�
          C_End_EventState	  		�¼�״̬�����з����޻ָ�
          C_Close_EventState		�¼�״̬���ر�
����˵�����ж��¼���ǰ״̬��
���û��ƣ��¼��жϺ�������
��    ע��
**********************************************************************************/
uchar8 SF_Get_ReversephaseVoltage_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
 	uchar8	V_ucJudgeBuffer1[C_4Volage_Length];											/*ȫʧѹ�жϵ�ѹ�������ѹ*/
	uchar8	V_ucJudgeBuffer2[C_Length_Two];												/*���ܱ���������*/
	ushort16 V_usLineLength = C_Length_One, V_usJudgeBufferLength1 = C_4Volage_Length, V_usEncode;
	uchar8	V_ucReverseFlag;

	if(InF_GetData_ObjectManage(CLoss_Volage_Vol, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)	/*ȫʧѹ�жϵ�ѹ*/
	{
		return(V_ucHstate);
	}
    V_usJudgeBufferLength1 = C_4Volage_Length;/*V0.2�������ȸ�ֵ*/
	if(InF_GetData_ObjectManage(CPhaseFF_Volage, &V_ucJudgeBuffer1[C_JudgeVolage_Buffer1], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)	/*�����ѹ*/
	{
		return(V_ucHstate);
	}
	if(InF_GetData_ObjectManage(CLine_Type, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usLineLength, &V_usEncode) != C_OK)	/*��������*/
	{
		return(V_ucHstate);
	}
	V_ucReverseFlag = SF_Get_ReversePhaseVoltageFlag(&V_ucJudgeBuffer2[C_Judge_StartBuffer0]);/*��ȡ��ѹ�������־*/

    if( (V_ucReverseFlag == C_Reversephase)
        &&( ( (PF_Campare_Data(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer1], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_GreaterThan)
                && (PF_Campare_Data(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer2], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_GreaterThan)
                && (PF_Campare_Data(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer3], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_GreaterThan)
                && (V_ucJudgeBuffer2[C_Judge_StartBuffer0] == C_3P4W) )
            ||( (PF_Campare_Data(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer1], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_GreaterThan)
                && (PF_Campare_Data(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer3], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_GreaterThan)
                && (V_ucJudgeBuffer2[C_Judge_StartBuffer0] == C_3P3W) ) ) )
	{
		return(C_Happen_EventState);
	}
	else
	{
        return(C_End_EventState);
	}
}
/***********************************************************************************
����ԭ�ͣ�uchar8 SF_Get_ReversephaseCurrent_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
��������: ����������
���������EventNo���¼��ţ���Hstate����ʷ״̬��
��������������¼���ǰ����״̬
���ز����CC_Happen_V_ucEventState		�¼�״̬���з����޻ָ�
          C_End_EventState	  		�¼�״̬�����з����޻ָ�
          C_Close_EventState		�¼�״̬���ر�
����˵�����ж��¼���ǰ״̬��
���û��ƣ��¼��жϺ�������
��    ע��
**********************************************************************************/
uchar8 SF_Get_ReversephaseCurrent_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
 	uchar8	V_ucJudgeBuffer1[C_4Volage_Length];											/*ȫʧѹ�жϵ�ѹ�������ѹ*/
	uchar8	V_ucJudgeBuffer2[C_Length_Two];												/*���ܱ���������*/
 	uchar8	V_ucJudgeBuffer3[C_4Curr4Dig_Length];												/*ȫʧѹ�жϵ������������*/
	ushort16 V_usJudgeBufferLength1 = C_4Volage_Length, V_usVolageLength = C_Volage_Length;
	ushort16 V_usJudgeBufferLength3 = C_4Curr4Dig_Length, V_usEncode;
	uchar8	V_ucReverseFlag;

	if(InF_GetData_ObjectManage(CLoss_Volage_Vol, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)	/*ȫʧѹ�жϵ�ѹ*/
	{
		return(V_ucHstate);
	}
    V_usJudgeBufferLength1 = C_4Volage_Length;/*V0.2�������ȸ�ֵ*/
	if(InF_GetData_ObjectManage(CPhaseFF_Volage, &V_ucJudgeBuffer1[C_JudgeVolage_Buffer1], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)	/*�����ѹ*/
	{
		return(V_ucHstate);
	}
	if(InF_GetData_ObjectManage(CLine_Type, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usVolageLength, &V_usEncode) != C_OK)	/*��������*/
	{
		return(V_ucHstate);
	}
	if(InF_GetData_ObjectManage(CLoss_Volage_Curr, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_usJudgeBufferLength3, &V_usEncode) != C_OK)	/*ȫʧѹ�жϵ���*/
	{
		return(V_ucHstate);
	}
    V_usJudgeBufferLength3 = C_4Curr4Dig_Length;/*V0.2�������ȸ�ֵ*/
	if(InF_GetData_ObjectManage(CPhaseFF_Curr, &V_ucJudgeBuffer3[C_JudgeCurr_Buffer1], &V_usJudgeBufferLength3, &V_usEncode) != C_OK)	/*�������*/
	{
		return(V_ucHstate);
	}
    V_ucJudgeBuffer3[C_Judge_StartBuffer2] = C_NULL;/*�жϵ��������ֽ���0*/
    V_ucJudgeBuffer3[C_Judge_StartBuffer3] = C_NULL;

    PF_GetAbs(&V_ucJudgeBuffer3[C_JudgeCurr_Buffer1], &V_ucJudgeBuffer3[C_JudgeCurr_Buffer1], C_Curr4Bytes_Length);/*A�����ȡ����ֵ*/
	PF_GetAbs(&V_ucJudgeBuffer3[C_JudgeCurr_Buffer2], &V_ucJudgeBuffer3[C_JudgeCurr_Buffer2], C_Curr4Bytes_Length);/*B�����ȡ����ֵ*/
	PF_GetAbs(&V_ucJudgeBuffer3[C_JudgeCurr_Buffer3], &V_ucJudgeBuffer3[C_JudgeCurr_Buffer3], C_Curr4Bytes_Length);/*C�����ȡ����ֵ*/

	V_ucReverseFlag = SF_Get_ReverseCurrentFlag(&V_ucJudgeBuffer2[C_Judge_StartBuffer0]);/*��ȡ�����������־*/
	if( (V_ucReverseFlag==C_Reversephase)
        && ( ( (PF_Campare_Data(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer1], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length)==C_GreaterThan)
                && (PF_Campare_Data(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer2], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length)==C_GreaterThan)
                && (PF_Campare_Data(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer3], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length)==C_GreaterThan)
                && (V_ucJudgeBuffer2[C_Judge_StartBuffer0]==C_3P4W) )
            || ( (PF_Campare_Data(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer1], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length)==C_GreaterThan)
                && (PF_Campare_Data(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer3], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length)==C_GreaterThan)
                && (V_ucJudgeBuffer2[C_Judge_StartBuffer0]==C_3P3W) ) )
        &&( ( ((PF_Campare_Data(&V_ucJudgeBuffer3[C_JudgeCurr_Buffer1], &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_Curr_Length)==C_GreaterThan)
                && (PF_Campare_Data(&V_ucJudgeBuffer3[C_JudgeCurr_Buffer2], &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_Curr_Length)==C_GreaterThan)
                && (PF_Campare_Data(&V_ucJudgeBuffer3[C_JudgeCurr_Buffer3], &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_Curr_Length)==C_GreaterThan))
                && (V_ucJudgeBuffer2[C_Judge_StartBuffer0]==C_3P4W) )
            || ( ( (PF_Campare_Data(&V_ucJudgeBuffer3[C_JudgeCurr_Buffer1], &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_Curr_Length)==C_GreaterThan)
                && (PF_Campare_Data(&V_ucJudgeBuffer3[C_JudgeCurr_Buffer3], &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_Curr_Length)==C_GreaterThan))
        && (V_ucJudgeBuffer2[C_Judge_StartBuffer0]==C_3P3W) ) ) )
	{
		return(C_Happen_EventState);
	}
	else
	{
        return(C_End_EventState);
	}
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_Get_UnbalanceRate_RealTime( uchar8 V_ucEventNo, uchar8 *V_JudgeUnbanlance )
������������ȡ��ǰ��ƽ����
���������EventNo���¼��ţ���V_JudgeUnbanlance�����ص�ǰ��ƽ���ʻ���
���������V_JudgeUnbanlance�����ص�ǰ��ƽ����
���ز����C��
����˵�����ж��¼���ǰ״̬��
���û��ƣ��¼��жϺ�������
��    ע��
*******************************************************************************/
void SF_Get_UnbalanceRate_RealTime( uchar8 V_ucEventNo, uchar8 *V_JudgeUnbanlance )
{
 	uchar8  V_ucJudgeBuffer1[C_Judge_20BufferLength], V_ucJudgeBuffer2[3]={0};		/*��ѹ��ƽ�����жϷ�ֵ����ѹ��ƽ����*/
	uchar8	V_ucUmax[C_Curr_Length], V_ucUmin[C_Curr_Length];						/*����ѹ����С��ѹ, ��ǰ��ƽ����*/
    ulong32	V_ulDivisor = 0, V_ulDividend = 0, V_ulQuotient = 0;									/*����������������*/
	ushort16 V_usJudgeBufferLength1 = C_Judge_20BufferLength, V_usEncode;
	ulong32	V_ulDataCode;
	uchar8	V_ucRealDatabuffer1, V_ucRealDatabuffer2, V_ucRealDatabuffer3, V_ucDatalength;
	
    memset(V_JudgeUnbanlance, 0, C_Unbalance_Length);
	
	switch( V_ucEventNo )
	{
		case C_UnbanlanceVoltageEventNo:
		{
			V_ulDataCode = CPhaseFF_Volage;
			V_ucRealDatabuffer1 = C_JudgeVolage_Buffer1;
			V_ucRealDatabuffer2 = C_JudgeVolage_Buffer2;
			V_ucRealDatabuffer3 = C_JudgeVolage_Buffer3;
			V_ucDatalength = C_Volage_Length;
		}break;
		case C_UnbanlanceCurrentEventNo:
		case C_SUnbanlanceCurrentEventNo:
		{
			V_ulDataCode = CPhaseFF_Curr;
			V_ucRealDatabuffer1 = C_JudgeCurr_Buffer1;
			V_ucRealDatabuffer2 = C_JudgeCurr_Buffer2;
			V_ucRealDatabuffer3 = C_JudgeCurr_Buffer3;
			V_ucDatalength = C_Curr_Length;
		}break;
		default:
			return;
    }

	if( InF_GetData_ObjectManage( V_ulDataCode, &V_ucJudgeBuffer1[V_ucRealDatabuffer1], &V_usJudgeBufferLength1 , &V_usEncode) != C_OK )	/*�����ѹ/����*/
	{
		return;
	}
	V_usJudgeBufferLength1 = CLLine_Type;
	if( InF_GetData_ObjectManage( CLine_Type, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength1 , &V_usEncode) != C_OK )		/*��������*/
	{
		return;
	}

	if( V_ucEventNo != C_UnbanlanceVoltageEventNo )
	{
        PF_GetAbs(&V_ucJudgeBuffer1[C_JudgeCurr_Buffer1], &V_ucJudgeBuffer1[C_JudgeCurr_Buffer1], C_Curr4Bytes_Length);/*A�����ȡ����ֵ*/
        PF_GetAbs(&V_ucJudgeBuffer1[C_JudgeCurr_Buffer2], &V_ucJudgeBuffer1[C_JudgeCurr_Buffer2], C_Curr4Bytes_Length);/*B�����ȡ����ֵ*/
        PF_GetAbs(&V_ucJudgeBuffer1[C_JudgeCurr_Buffer3], &V_ucJudgeBuffer1[C_JudgeCurr_Buffer3], C_Curr4Bytes_Length);/*C�����ȡ����ֵ*/
	}

	if( PF_Campare_Data( &V_ucJudgeBuffer1[V_ucRealDatabuffer1], &V_ucJudgeBuffer1[V_ucRealDatabuffer3], V_ucDatalength ) == C_GreaterThan )		/*A/C�Ƚϣ���ķ�V_Umax��С�ķ�V_Umin*/
	{
		PF_CopyDataBytes(&V_ucJudgeBuffer1[V_ucRealDatabuffer1], &V_ucUmax[C_Judge_StartBuffer0], V_ucDatalength);
		PF_CopyDataBytes(&V_ucJudgeBuffer1[V_ucRealDatabuffer3], &V_ucUmin[C_Judge_StartBuffer0], V_ucDatalength);
	}
    else
    {
        PF_CopyDataBytes(&V_ucJudgeBuffer1[V_ucRealDatabuffer3], &V_ucUmax[C_Judge_StartBuffer0], V_ucDatalength);
        PF_CopyDataBytes(&V_ucJudgeBuffer1[V_ucRealDatabuffer1], &V_ucUmin[C_Judge_StartBuffer0], V_ucDatalength);
    }
    if(V_ucJudgeBuffer1[C_Judge_StartBuffer0]==C_3P4W)																				/*��������*/
    {
        if(PF_Campare_Data(&V_ucJudgeBuffer1[V_ucRealDatabuffer2], &V_ucUmax[C_Judge_StartBuffer0], V_ucDatalength) == C_GreaterThan)	/*B��V_Umax�󣬷�V_Umax����V_UminС����V_Umin*/
        {
            PF_CopyDataBytes(&V_ucJudgeBuffer1[V_ucRealDatabuffer2], &V_ucUmax[C_Judge_StartBuffer0], V_ucDatalength);
        }
        else
        {
            if(PF_Campare_Data(&V_ucJudgeBuffer1[V_ucRealDatabuffer2], &V_ucUmin[C_Judge_StartBuffer0], V_ucDatalength) == C_LessThan)
            {
                PF_CopyDataBytes(&V_ucJudgeBuffer1[V_ucRealDatabuffer2], &V_ucUmin[C_Judge_StartBuffer0], V_ucDatalength);
            }
        }
    }

    if(PF_Campare_Data(&V_ucUmax[C_Judge_StartBuffer0], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], V_ucDatalength) == C_Equal)/*����������0*/
    {
        return;
    }
    SF_HEXDECBytes(V_ucUmax, V_ucUmin, (uchar8 *)&V_ulDivisor, V_ucDatalength);/*���㱻����*/
    V_ulDivisor *= C_TenThousand_times;/*��ֵ*100*/

    PF_BufferXToUlong32(V_ucUmax, &V_ulDividend, V_ucDatalength);/*����ѹת��1��32λ����*/

    V_ulQuotient = V_ulDivisor / V_ulDividend;

    PF_Ulong32ToBufferX(V_ucJudgeBuffer1, &V_ulQuotient, 4);
    PF_CopyDataBytes(V_ucJudgeBuffer1, V_JudgeUnbanlance, C_Unbalance_Length);
}
/***********************************************************************************
����ԭ�ͣ�uchar8 SF_Get_UnbanlanceVoltage_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
��������: ��ѹ��ƽ��
���������EventNo���¼��ţ���Hstate����ʷ״̬��
��������������¼���ǰ����״̬
���ز����CC_Happen_V_ucEventState		�¼�״̬���з����޻ָ�
          C_End_EventState	  		�¼�״̬�����з����޻ָ�
          C_Close_EventState		�¼�״̬���ر�
����˵�����ж��¼���ǰ״̬��
���û��ƣ��¼��жϺ�������
��    ע��
**********************************************************************************/
uchar8 SF_Get_UnbanlanceVoltage_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
 	uchar8	V_ucJudgeBuffer1[C_Unbalance_Length];					/*��ѹ��ƽ�����жϷ�ֵ����ѹ��ƽ����*/
	uchar8	V_ucJudgeBuffer2[C_4Volage_Length];					/*ȫʧѹ�жϵ�ѹ�������ѹ*/
    uchar8  V_ucJudgeUnbanlance[3];
	ushort16 V_usJudgeBufferLength1 = CLNoBal_Vol_Lim, V_usEncode;

	if(InF_GetData_ObjectManage(CNoBal_Vol_Lim, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)		/*��ѹ��ƽ���жϷ�ֵ, ��ֵΪ0�����عر�*/
	{
		return(V_ucHstate);
	}
	if((V_ucJudgeBuffer1[C_Judge_StartBuffer0] == C_NULL)
       && (V_ucJudgeBuffer1[C_Judge_StartBuffer1] == C_NULL))
	{
		return(C_Close_EventState);
	}
    V_usJudgeBufferLength1 = CLLoss_Volage_Vol;
	if(InF_GetData_ObjectManage(CLoss_Volage_Vol, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)	/*ȫʧѹ��ѹ*/
	{
		return(V_ucHstate);
	}
    V_usJudgeBufferLength1 = CLPhaseFF_Volage;        /*V0.2�������ȸ�ֵ*/
	if(InF_GetData_ObjectManage(CPhaseFF_Volage, &V_ucJudgeBuffer2[C_JudgeVolage_Buffer1], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)	/*�����ѹ*/
	{
		return(V_ucHstate);
	}
	SF_Get_UnbalanceRate_RealTime(C_UnbanlanceVoltageEventNo, &V_ucJudgeUnbanlance[C_Judge_StartBuffer0]);

	if( ((PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeVolage_Buffer1], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_Volage_Length) == C_GreaterThan)
		|| (PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeVolage_Buffer2], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_Volage_Length) == C_GreaterThan)
		|| (PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeVolage_Buffer3], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_Volage_Length) == C_GreaterThan))/*��һ���ѹ�����ٽ��ѹ*/
        &&(PF_Campare_Data(&V_ucJudgeUnbanlance[C_Judge_StartBuffer0], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Unbalance_Length) == C_GreaterThan) )	/*��ѹ��ƽ���ʴ����жϷ�ֵ*/
	{
		return(C_Happen_EventState);
	}
	else
	{
		return(C_End_EventState);
	}
}
/***********************************************************************************
����ԭ�ͣ�uchar8 SF_Get_FFUnbanlanceCurrent_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
��������: ������ƽ�⡢�������ز�ƽ��
���������EventNo���¼��ţ���Hstate����ʷ״̬��
��������������¼���ǰ����״̬
���ز����CC_Happen_V_ucEventState		�¼�״̬���з����޻ָ�
          C_End_EventState	  		�¼�״̬�����з����޻ָ�
          C_Close_EventState		�¼�״̬���ر�
����˵�����ж��¼���ǰ״̬��
���û��ƣ��¼��жϺ�������
��    ע��
**********************************************************************************/
uchar8 SF_Get_FFUnbanlanceCurrent_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
 	uchar8	V_ucJudgeBuffer1[C_Unbalance_Length];					/*��ƽ�����жϷ�ֵ����ǰ������ƽ����*/
	uchar8	V_ucJudgeBuffer2[C_4Curr_Length];					/*ȫʧѹ�жϵ������������*/
    uchar8  V_ucJudgeUnbanlance[C_Unbalance_Length];
    ulong32	V_JudgeThreshold;
	ushort16 V_usJudgeBufferLength1, V_usEncode;

	switch(V_ucEventNo)
	{
		case	C_UnbanlanceCurrentEventNo:
				V_JudgeThreshold = CNoBal_Curr_Lim;
				break;
		case	C_SUnbanlanceCurrentEventNo:
				V_JudgeThreshold = CSeriNoBal_Curr_Lim;
				break;
		default:
				return(V_ucHstate);
	}
    V_usJudgeBufferLength1 = CLNoBal_Curr_Lim;
	if(InF_GetData_ObjectManage(V_JudgeThreshold, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)		/*��ƽ���жϷ�ֵ, ��ֵΪ0�����عر�*/
	{
		return(V_ucHstate);
	}
	if( (V_ucJudgeBuffer1[C_Judge_StartBuffer0] == C_NULL)
        &&(V_ucJudgeBuffer1[C_Judge_StartBuffer1] == C_NULL) )
	{
		return(C_Close_EventState);
	}
    V_usJudgeBufferLength1 = CLLoss_Volage_Curr;
	if(InF_GetData_ObjectManage(CLoss_Volage_Curr, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)	/*ȫʧѹ����*/
	{
		return(V_ucHstate);
	}
	V_ucJudgeBuffer2[C_Judge_StartBuffer2] = C_NULL;
    V_ucJudgeBuffer2[C_Judge_StartBuffer3] = C_NULL;

    V_usJudgeBufferLength1=CLPhaseFF_Curr; /*V0.2�������ȸ�ֵ*/
	if(InF_GetData_ObjectManage(CPhaseFF_Curr, &V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)	/*�������*/
	{
		return(V_ucHstate);
	}
    PF_GetAbs(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], &V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], C_Curr4Bytes_Length);/*A�����ȡ����ֵ*/
	PF_GetAbs(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer2], &V_ucJudgeBuffer2[C_JudgeCurr_Buffer2], C_Curr4Bytes_Length);/*B�����ȡ����ֵ*/
	PF_GetAbs(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer3], &V_ucJudgeBuffer2[C_JudgeCurr_Buffer3], C_Curr4Bytes_Length);/*C�����ȡ����ֵ*/

	SF_Get_UnbalanceRate_RealTime(V_ucEventNo, &V_ucJudgeUnbanlance[C_Judge_StartBuffer0]);

	if( ((PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_Curr_Length) == C_GreaterThan)
		|| (PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer2], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_Curr_Length) == C_GreaterThan)
		|| (PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer3], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_Curr_Length) == C_GreaterThan))	/*��һ���ѹ�����ٽ��ѹ*/
        && (PF_Campare_Data(&V_ucJudgeUnbanlance[C_Judge_StartBuffer0], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Unbalance_Length) == C_GreaterThan) )/*������ƽ���ʴ����жϷ�ֵ*/
	{
		return(C_Happen_EventState);
	}
	else
	{
		return(C_End_EventState);
	}
}

/***********************************************************************************
����ԭ�ͣ�uchar8 SF_Get_Losscurrent_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
��������: ʧ��
���������EventNo���¼��ţ���Hstate����ʷ״̬��
��������������¼���ǰ����״̬
���ز����CC_Happen_V_ucEventState		�¼�״̬���з����޻ָ�
          C_End_EventState	  		�¼�״̬�����з����޻ָ�
          C_Close_EventState		�¼�״̬���ر�
����˵�����ж��¼���ǰ״̬��
���û��ƣ��¼��жϺ�������
��    ע��
**********************************************************************************/
uchar8 SF_Get_Losscurrent_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
	uchar8	V_ucVolage[C_Volage_Length], V_ucCurr[C_Curr4Dig_Length];
	uchar8	V_ucJudgeBuffer1[C_4Volage_Length];	/*��ѹ�жϷ�ֵ�������ѹ*/
	uchar8	V_ucJudgeBuffer2[C_4Curr_Length];		/*�����жϷ�ֵ���������*/
	uchar8	V_ucJudgeBuffer3[C_2Curr_Length];		/*ʧ���¼�������������*/
	uchar8	V_uclineType;
	ushort16 V_usJudgeBufferLength1 = C_4Volage_Length, V_usLineLength=C_Length_One;
	ushort16 V_usJudgeBufferLength2 = C_4Curr_Length, V_usCurrLength = C_Curr_Length, V_usEncode;

	if(InF_GetData_ObjectManage(CLossCurr_Vol_LowLim, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
	if(InF_GetData_ObjectManage(CLossCurr_Curr_UpLim, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usJudgeBufferLength2, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
	if(InF_GetData_ObjectManage(CLine_Type, &V_uclineType, &V_usLineLength, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
	if((V_ucJudgeBuffer2[C_Judge_StartBuffer0] == C_NULL)
        &&(V_ucJudgeBuffer2[C_Judge_StartBuffer1] == C_NULL)
        &&(V_ucJudgeBuffer2[C_Judge_StartBuffer2] == C_NULL)
        &&(V_ucJudgeBuffer2[C_Judge_StartBuffer3] == C_NULL))
	{
		return(C_Close_EventState);
	}
    V_usJudgeBufferLength1 = CLPhaseFF_Volage;      /*V0.2�������ȸ�ֵ*/
	if(InF_GetData_ObjectManage(CPhaseFF_Volage, &V_ucJudgeBuffer1[C_JudgeVolage_Buffer1], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
    V_usJudgeBufferLength2 = CLPhaseFF_Curr_4Dig;    /*V0.2�������ȸ�ֵ*/
	if(InF_GetData_ObjectManage(CPhaseFF_Curr_4Dig, &V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], &V_usJudgeBufferLength2, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
	if(InF_GetData_ObjectManage(CLossCurr_Curr_LowLim, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_usCurrLength, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
    PF_GetAbs(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], &V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], C_Curr4Bytes_Length);/*A�����ȡ����ֵ*/
	PF_GetAbs(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer2], &V_ucJudgeBuffer2[C_JudgeCurr_Buffer2], C_Curr4Bytes_Length);/*B�����ȡ����ֵ*/
	PF_GetAbs(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer3], &V_ucJudgeBuffer2[C_JudgeCurr_Buffer3], C_Curr4Bytes_Length);/*C�����ȡ����ֵ*/

 	if(PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeCurr4Dig_Buffer1], &V_ucJudgeBuffer2[C_JudgeCurr4Dig_Buffer3], C_Curr4Dig_Length) == C_GreaterThan)
	{
		PF_CopyDataBytes(&V_ucJudgeBuffer2[C_JudgeCurr4Dig_Buffer1], &V_ucJudgeBuffer3[C_JudgeCurr4Dig_Buffer1], C_Curr4Dig_Length);
	}
    else
    {
 	    PF_CopyDataBytes(&V_ucJudgeBuffer2[C_JudgeCurr4Dig_Buffer3], &V_ucJudgeBuffer3[C_JudgeCurr4Dig_Buffer1], C_Curr4Dig_Length);
    }
	if(V_uclineType == C_3P4W)
	{
		if(PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeCurr4Dig_Buffer2], &V_ucJudgeBuffer3[C_JudgeCurr4Dig_Buffer1], C_Curr4Dig_Length) == C_GreaterThan)
		{
			PF_CopyDataBytes(&V_ucJudgeBuffer2[C_JudgeCurr4Dig_Buffer2], &V_ucJudgeBuffer3[C_JudgeCurr4Dig_Buffer1], C_Curr4Dig_Length);
		}
	}
	switch(V_ucEventNo)
	{
		case	C_ALosscurrentEventNo:
				PF_CopyDataBytes(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer1], &V_ucVolage[C_Judge_StartBuffer0], C_Volage_Length);
				PF_CopyDataBytes(&V_ucJudgeBuffer2[C_JudgeCurr4Dig_Buffer1], &V_ucCurr[C_Judge_StartBuffer0], C_Curr4Dig_Length);
				break;
		case	C_BLosscurrentEventNo:
				PF_CopyDataBytes(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer2], &V_ucVolage[C_Judge_StartBuffer0], C_Volage_Length);
				PF_CopyDataBytes(&V_ucJudgeBuffer2[C_JudgeCurr4Dig_Buffer2], &V_ucCurr[C_Judge_StartBuffer0], C_Curr4Dig_Length);
				break;

		default:
				PF_CopyDataBytes(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer3], &V_ucVolage[C_Judge_StartBuffer0], C_Volage_Length);
				PF_CopyDataBytes(&V_ucJudgeBuffer2[C_JudgeCurr4Dig_Buffer3], &V_ucCurr[C_Judge_StartBuffer0], C_Curr4Dig_Length);
				break;
	}
	if( (PF_Campare_Data(&V_ucVolage[C_Judge_StartBuffer0], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_GreaterThan)
		&&(PF_Campare_Data(&V_ucCurr[C_Judge_StartBuffer0], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_Curr4Dig_Length) == C_LessThan)
		&&(PF_Campare_Data(&V_ucJudgeBuffer3[C_JudgeCurr4Dig_Buffer1], &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_Curr4Dig_Length) == C_GreaterThan) )
	{
		return(C_Happen_EventState);
	}
	else
	{
		return(C_End_EventState);
	}
}

/***********************************************************************************
����ԭ�ͣ�uchar8 SF_Get_Overcurrent_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
��������: ����
���������EventNo���¼��ţ���Hstate����ʷ״̬��
��������������¼���ǰ����״̬
���ز����CC_Happen_V_ucEventState		�¼�״̬���з����޻ָ�
          C_End_EventState	  		�¼�״̬�����з����޻ָ�
          C_Close_EventState		�¼�״̬���ر�
����˵�����ж��¼���ǰ״̬��
���û��ƣ��¼��жϺ�������
��    ע��
**********************************************************************************/
uchar8	SF_Get_Overcurrent_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
	ulong32	V_ulCurr;
	uchar8	V_ucJudgeBuffer1[C_2Curr_Length];			/*�����жϷ�ֵ���������*/
	ushort16 V_usCurrLength = C_Curr4Bytes_Length, V_usCurrLength2 = C_Curr4Bytes_Length, V_usEncode;

	if(InF_GetData_ObjectManage(COverCurr_Curr_LowLim, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usCurrLength2, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
	if( (V_ucJudgeBuffer1[C_Judge_StartBuffer0] == C_NULL)
        &&(V_ucJudgeBuffer1[C_Judge_StartBuffer1] == C_NULL)
        &&(V_ucJudgeBuffer1[C_Judge_StartBuffer2] == C_NULL)
        &&(V_ucJudgeBuffer1[C_Judge_StartBuffer3] == C_NULL) )
	{
		return(C_Close_EventState);
	}
	switch(V_ucEventNo)
	{
		case	C_AOvercurrentEventNo:
				V_ulCurr = CPhaseA_Curr_4Dig;
				break;
		case	C_BOvercurrentEventNo:
				V_ulCurr = CPhaseB_Curr_4Dig;
				break;
		case	C_COvercurrentEventNo:
				V_ulCurr = CPhaseC_Curr_4Dig;
				break;
		default:
				return(V_ucHstate);
	}
	if(InF_GetData_ObjectManage(V_ulCurr, &V_ucJudgeBuffer1[C_JudgeCurr4Dig_Buffer1], &V_usCurrLength, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
    PF_GetAbs(&V_ucJudgeBuffer1[C_JudgeCurr4Dig_Buffer1], &V_ucJudgeBuffer1[C_JudgeCurr4Dig_Buffer1], C_Curr4Bytes_Length);/*����ȡ����ֵ*/

	if(PF_Campare_Data(&V_ucJudgeBuffer1[C_JudgeCurr4Dig_Buffer1], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Curr_Length) == C_GreaterThan)
	{
		return(C_Happen_EventState);
	}
	else
	{
		return(C_End_EventState);
	}
}

/***********************************************************************************
����ԭ�ͣ�uchar8	SF_Get_Failcurrent_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
��������: ����
���������EventNo���¼��ţ���Hstate����ʷ״̬��
���������
���ز����CC_Happen_V_ucEventState		�¼�״̬���з����޻ָ�
          C_End_EventState	  		�¼�״̬�����з����޻ָ�
          C_Close_EventState		�¼�״̬���ر�
����˵�����ж��¼���ǰ״̬��
���û��ƣ��¼��жϺ�������
��    ע��
**********************************************************************************/
uchar8	SF_Get_Failcurrent_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
	uchar8	V_ucJudgeBuffer1[C_2Curr4Dig_Length];			/*�����жϷ�ֵ���������*/
	uchar8	V_ucJudgeBuffer2[C_2Volage_Length];			/*�����жϷ�ֵ���������*/
	ulong32	V_ulVolage, V_ulCurr;
	ushort16 V_usCurrLength1 = C_JudgeCurr_Length, V_usVolageLength = C_Volage_Length, V_usCurrLength = C_Curr4Dig_Length, V_usEncode;

	if(InF_GetData_ObjectManage(CBreakCurr_Curr_UpLim, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usCurrLength1, &V_usEncode)!=C_OK)
	{
		return(V_ucHstate);
	}
	if( (V_ucJudgeBuffer1[C_Judge_StartBuffer0] == C_NULL)
        &&(V_ucJudgeBuffer1[C_Judge_StartBuffer1] == C_NULL)
        &&(V_ucJudgeBuffer1[C_Judge_StartBuffer2] == C_NULL)
        &&(V_ucJudgeBuffer1[C_Judge_StartBuffer3] == C_NULL) )
	{
		return(C_Close_EventState);
	}
	switch(V_ucEventNo)
	{
		case	C_AFailcurrentEventNo:
				V_ulVolage = CPhaseA_Volage;
				V_ulCurr = CPhaseA_Curr_4Dig;
				break;
		case	C_BFailcurrentEventNo:
				V_ulVolage = CPhaseB_Volage;
				V_ulCurr = CPhaseB_Curr_4Dig;
				break;
		case	C_CFailcurrentEventNo:
				V_ulVolage = CPhaseC_Volage;
				V_ulCurr = CPhaseC_Curr_4Dig;
				break;
		default:
				return(V_ucHstate);
	}
	if(InF_GetData_ObjectManage(CBreakCurr_Vol_LowLim, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usVolageLength, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
    V_usVolageLength = C_Volage_Length;
	if(InF_GetData_ObjectManage(V_ulVolage, &V_ucJudgeBuffer2[C_JudgeVolage_Buffer1], &V_usVolageLength, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
	if(InF_GetData_ObjectManage(V_ulCurr, &V_ucJudgeBuffer1[C_JudgeCurr4Dig_Buffer1], &V_usCurrLength, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
    PF_GetAbs(&V_ucJudgeBuffer1[C_JudgeCurr4Dig_Buffer1], &V_ucJudgeBuffer1[C_JudgeCurr4Dig_Buffer1], C_Curr4Bytes_Length);/*����ȡ����ֵ*/

	if( (PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeVolage_Buffer1], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_Volage_Length) == C_GreaterThan)
		&&(PF_Campare_Data(&V_ucJudgeBuffer1[C_JudgeCurr4Dig_Buffer1], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Curr4Dig_Length) == C_LessThan) )
	{
		return(C_Happen_EventState);
	}
	else
	{
		return(C_End_EventState);
	}
}
/***********************************************************************************
����ԭ�ͣ�uchar8	SF_Get_FFReversecurrent_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
��������:���๦�ʷ���((��������ϵͳ���ж�) )
���������EventNo���¼��ţ���Hstate����ʷ״̬��
��������������¼���ǰ����״̬
���ز����CC_Happen_V_ucEventState		�¼�״̬���з����޻ָ�
          C_End_EventState	  		�¼�״̬�����з����޻ָ�
          C_Close_EventState		�¼�״̬���ر�
����˵�����ж��¼���ǰ״̬��
���û��ƣ��¼��жϺ�������
��    ע��(������ʼ�����Ȳ������ݲ�)
**********************************************************************************/
 uchar8	SF_Get_FFReversecurrent_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
 {
 	ulong32		V_ulInstant_AcPow;
 	uchar8		V_ucJudgeBuffer1[C_Length_Eight];		/*8���ֽڴ���жϷ�ֵ�ͷ��๦��*/
	ushort16    V_usJudgeBufferLength1 = CLInstantA_AcPow, V_usEncode;
    uchar8      V_ucSign;

	switch(V_ucEventNo)
	{
		case	C_TReversecurrentEventNo:
				V_ulInstant_AcPow = CInstant_TolAcPow;	/*���й�����*/
				break;
		case	C_AReversecurrentEventNo:
				V_ulInstant_AcPow = CInstantA_AcPow;	/*A���й�����*/
				break;
		case	C_BReversecurrentEventNo:
				V_ulInstant_AcPow = CInstantB_AcPow;
				break;
		case	C_CReversecurrentEventNo:
				V_ulInstant_AcPow = CInstantC_AcPow;
				break;
		default:
				return(V_ucHstate);
	}
   	if(InF_GetData_ObjectManage(CPowerRev_AcPower_LowLim, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK) /*�¼��жϷ�ֵ*/
	{
		return(V_ucHstate);
	}
	if( (V_ucJudgeBuffer1[C_Judge_StartBuffer0] == C_NULL)
        && (V_ucJudgeBuffer1[C_Judge_StartBuffer1] == C_NULL)
        && (V_ucJudgeBuffer1[C_Judge_StartBuffer2] == C_NULL)
        && (V_ucJudgeBuffer1[C_Judge_StartBuffer3] == C_NULL) )/*��ֵΪ0���ر�*/
	{
		return(C_Close_EventState);
	}
    V_usJudgeBufferLength1 = CLInstantA_AcPow;
	if(InF_GetData_ObjectManage(V_ulInstant_AcPow, &V_ucJudgeBuffer1[C_Instant_AcPow_Buffer], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)		/*�����й�����*/
	{
		return(V_ucHstate);
	}
    V_ucSign = PF_GetAbs(&V_ucJudgeBuffer1[C_Instant_AcPow_Buffer], &V_ucJudgeBuffer1[C_Instant_AcPow_Buffer], C_Curr4Bytes_Length);/*����ȡ����ֵ*/

	if( (V_ucSign == C_GetSignBit)
		&&(PF_Campare_Data(&V_ucJudgeBuffer1[C_Instant_AcPow_Buffer], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], CLInstantA_AcPow) == C_GreaterThan) )
	{
		return(C_Happen_EventState);
	}
	else
	{
		return(C_End_EventState);
	}
 }

/***********************************************************************************
����ԭ�ͣ�uchar8	SF_Get_Overload_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
��������: ����
���������EventNo���¼��ţ���Hstate����ʷ״̬��
��������������¼���ǰ����״̬
���ز����CC_Happen_V_ucEventState		�¼�״̬���з����޻ָ�
          C_End_EventState	  		�¼�״̬�����з����޻ָ�
          C_Close_EventState		�¼�״̬���ر�
����˵�����ж��¼���ǰ״̬��
���û��ƣ��¼��жϺ�������
��    ע��(������ʼ�����Ȳ������ݲ�)
***********************************************************************************/
 uchar8	SF_Get_Overload_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
 {
 	ulong32		V_ulInstant_AcPow;						/*�й�����*/
 	uchar8		V_ucJudgeBuffer1[C_Length_Eight];		/*8���ֽڴ���жϷ�ֵ�ͷ��๦��*/
	ushort16    V_usJudgeBufferLength1 = CLInstantA_AcPow, V_usEncode;

	switch(V_ucEventNo)
	{
		case	C_AOverloadEventNo:
				V_ulInstant_AcPow = CInstantA_AcPow;	/*A���й�����*/
				break;
		case	C_BOverloadEventNo:
				V_ulInstant_AcPow = CInstantB_AcPow;
				break;
		case	C_COverloadEventNo:
				V_ulInstant_AcPow = CInstantC_AcPow;
				break;
		default:
				return(V_ucHstate);
	}
   	if(InF_GetData_ObjectManage(COverLoad_AcPower_LowLim, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK) /*�¼��жϷ�ֵ*/
	{
		return(V_ucHstate);
	}
	if( (V_ucJudgeBuffer1[C_Judge_StartBuffer0] == C_NULL)
        && (V_ucJudgeBuffer1[C_Judge_StartBuffer1] == C_NULL)
        && (V_ucJudgeBuffer1[C_Judge_StartBuffer2] == C_NULL)
        && (V_ucJudgeBuffer1[C_Judge_StartBuffer3] == C_NULL) )/*��ֵΪ0���ر�*/
	{
		return(C_Close_EventState);
	}
    V_usJudgeBufferLength1 = CLInstantA_AcPow;
	if(InF_GetData_ObjectManage(V_ulInstant_AcPow, &V_ucJudgeBuffer1[C_Instant_AcPow_Buffer], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)		/*�����й�����*/
	{
		return(V_ucHstate);
	}
    PF_GetAbs(&V_ucJudgeBuffer1[C_Instant_AcPow_Buffer], &V_ucJudgeBuffer1[C_Instant_AcPow_Buffer], C_Curr4Bytes_Length);/*����ȡ����ֵ*/

	if(PF_Campare_Data(&V_ucJudgeBuffer1[C_Instant_AcPow_Buffer], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], CLInstantA_AcPow) == C_GreaterThan)
	{
		return(C_Happen_EventState);
	}
	else
	{
		return(C_End_EventState);
	}
 }

/***********************************************************************************
����ԭ�ͣ�uchar8 SF_Get_Overpowerfact_Cstate(uchar8 V_ucHstate)
�����������ܹ�������������
���������EventNo��Hstate����ʷ״̬��
��������������¼���ǰ����״̬
���ز����CC_IDError             ���ݱ�ʶ�����
           C_Happen_EventState	�¼�״̬���з����޻ָ�
          C_End_EventState	  	�¼�״̬�����з����޻ָ�
          C_Close_EventState	�¼�״̬���ر�״̬
����˵�����ж��¼���ǰ״̬��
���û��ƣ��¼��жϺ�������
��    ע��
***********************************************************************************/
uchar8 SF_Get_Overpowerfact_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
 	uchar8	V_ucJudgeBuffer1[C_Length_Five];		/*4���ֽڴ���жϷ�ֵ���ܹ�������, ���1�ֽڷ���������*/
	uchar8	V_ucJudgeBuffer2[C_4Curr_Length];
	ushort16 V_usJudgeBufferLength1=C_Length_Five, V_usJudgeBufferLength2 = C_4Curr_Length, V_usEncode;

	if(InF_GetData_ObjectManage(CPowerFactor_LowLim, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)/*�жϷ�ֵ*/
	{
		return(V_ucHstate);
	}
	if( (V_ucJudgeBuffer1[C_Judge_StartBuffer0] == C_NULL)
       && (V_ucJudgeBuffer1[C_Judge_StartBuffer1] == C_NULL) )
	{
		return(C_Close_EventState);
	}
    V_usJudgeBufferLength1 = CLTol_PowerFactor;
	if(InF_GetData_ObjectManage(CTol_PowerFactor, &V_ucJudgeBuffer1[C_Judge_StartBuffer2], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)	/*�ܹ�������*/
	{
		return(V_ucHstate);
	}
	if(InF_GetData_ObjectManage(CLoss_Volage_Curr, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usJudgeBufferLength2, &V_usEncode) != C_OK)	/*ȫʧѹ����*/
	{
		return(V_ucHstate);
	}
	V_ucJudgeBuffer2[C_Judge_StartBuffer2] = C_NULL;
    V_ucJudgeBuffer2[C_Judge_StartBuffer3] = C_NULL;

    PF_GetAbs(&V_ucJudgeBuffer1[C_Judge_StartBuffer2], &V_ucJudgeBuffer1[C_Judge_StartBuffer2], CLTol_PowerFactor);/*��������ȡ����ֵ*/

    V_usJudgeBufferLength2 = CLPhaseFF_Curr;    /*V0.2�������ȸ�ֵ*/
	if(InF_GetData_ObjectManage(CPhaseFF_Curr, &V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], &V_usJudgeBufferLength2, &V_usEncode) != C_OK)		/*�������*/
	{
		return(V_ucHstate);
	}
    PF_GetAbs(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], &V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], C_Curr4Bytes_Length);/*A�����ȡ����ֵ*/
	PF_GetAbs(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer2], &V_ucJudgeBuffer2[C_JudgeCurr_Buffer2], C_Curr4Bytes_Length);/*B�����ȡ����ֵ*/
	PF_GetAbs(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer3], &V_ucJudgeBuffer2[C_JudgeCurr_Buffer3], C_Curr4Bytes_Length);/*C�����ȡ����ֵ*/

	if( (PF_Campare_Data(&V_ucJudgeBuffer1[C_Judge_StartBuffer2], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], CLTol_PowerFactor) == C_LessThan)/*���ʷ�ֵ�ж�*/
		&& ((PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_Curr_Length) == C_GreaterThan)/*�����ж�*/
            || (PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer2], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_Curr_Length) == C_GreaterThan)
            || (PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer3], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_Curr_Length) == C_GreaterThan)) )
	{
		return(C_Happen_EventState);
	}
	else
	{
		return(C_End_EventState);
	}
}

/***********************************************************************************
����ԭ�ͣ�uchar8 SF_Get_FFOverpowerfact_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
�������������๦������������
���������EventNo��Hstate����ʷ״̬��
��������������¼���ǰ����״̬
���ز����CC_IDError             ���ݱ�ʶ�����
           C_Happen_EventState	�¼�״̬���з����޻ָ�
          C_End_EventState	  	�¼�״̬�����з����޻ָ�
          C_Close_EventState	�¼�״̬���ر�״̬
����˵�����ж��¼���ǰ״̬��
���û��ƣ��¼��жϺ�������
��    ע��
***********************************************************************************/
uchar8 SF_Get_FFOverpowerfact_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
	uchar8	V_ucJudgeBuffer1[C_Length_Four];		/*4���ֽڴ���жϷ�ֵ���ܹ�������*/
	uchar8	V_ucJudgeBuffer2[C_4Curr_Length];
	ulong32	V_ulOverpowerfact, V_ulCurr;
	ushort16 V_usJudgeBufferLength1 = CLPowerFactor_LowLim, V_usEncode;

	if(InF_GetData_ObjectManage(CPowerFactor_LowLim, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)/*�жϷ�ֵ*/
	{
		return(V_ucHstate);
	}
	if( (V_ucJudgeBuffer1[C_Judge_StartBuffer0] == C_NULL)
       &&(V_ucJudgeBuffer1[C_Judge_StartBuffer1] == C_NULL) )
	{
		return(C_Close_EventState);
	}
	switch(V_ucEventNo)
	{
		case	C_AOverpowerfactEventNo:
				V_ulOverpowerfact = CPhaseA_PowerFactor;	/*A�๦������, ����*/
				V_ulCurr = CPhaseA_Curr;
				break;
		case	C_BOverpowerfactEventNo:
				V_ulOverpowerfact = CPhaseB_PowerFactor;
				V_ulCurr = CPhaseB_Curr;
				break;
		case	C_COverpowerfactEventNo:
				V_ulOverpowerfact = CPhaseC_PowerFactor;
				V_ulCurr = CPhaseC_Curr;
				break;
		default:
				return(V_ucHstate);
	}
    V_usJudgeBufferLength1 = CLPhaseA_PowerFactor;
	if(InF_GetData_ObjectManage(V_ulOverpowerfact, &V_ucJudgeBuffer1[C_Judge_StartBuffer2], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)	/*�ܹ�������*/
	{
		return(V_ucHstate);
	}
    PF_GetAbs(&V_ucJudgeBuffer1[C_Judge_StartBuffer2], &V_ucJudgeBuffer1[C_Judge_StartBuffer2], CLPhaseA_PowerFactor);/*ȡ������������ֵ*/

    V_usJudgeBufferLength1 = CLLoss_Volage_Curr;
	if(InF_GetData_ObjectManage(CLoss_Volage_Curr, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)	/*ȫʧѹ����*/
	{
		return(V_ucHstate);
	}
	V_ucJudgeBuffer2[C_Judge_StartBuffer2] = C_NULL;
    V_ucJudgeBuffer2[C_Judge_StartBuffer3] = C_NULL;

    V_usJudgeBufferLength1 = CLPhaseA_Curr;    /*V0.2�������ȸ�ֵ*/
	if(InF_GetData_ObjectManage(V_ulCurr, &V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)	/*�������*/
	{
		return(V_ucHstate);
	}
	PF_GetAbs(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], &V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], CLPhaseA_Curr);/*ȡ��������ֵ*/

	if( (PF_Campare_Data(&V_ucJudgeBuffer1[C_Judge_StartBuffer2], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], CLTol_PowerFactor) == C_LessThan)
		&&(PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_Curr_Length) == C_GreaterThan) )
	{
		return(C_Happen_EventState);
	}
	else
	{
		return(C_End_EventState);
	}
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_Get_MeterAndClockFa_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
��������������оƬ��ʱ�ӹ���
���������EventNo��Hstate����ʷ״̬��
��������������¼���ǰ����״̬
���ز�����C_Happen_V_ucEventState �¼�״̬���з����޻ָ�
		 C_End_EventState	 �¼�״̬�����з����޻ָ�
����λ�ã��¼��жϺ�������
��    ע��
*******************************************************************************/
uchar8 SF_Get_MeterAndClockFa_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
	uchar8	V_ucData;
	uchar8  V_ucData_ChipID[3] = {0};
	ulong32 V_ulData = 0;
    ushort16 V_usEncode, V_usDataLen;

	if(V_ucEventNo == C_MeterFaEventNo)
	{
		SF_ReadOneReg_MeterIC(C_ChipID_Reg, V_ucData_ChipID, C_ReadMeaDataRegFlag);
		PF_BufferXToUlong32(V_ucData_ChipID, &V_ulData, C_RegDataLen);

		if( ( V_ulData == 0x00FFFFFF ) || ( V_ulData == 0 ) )		/*20�淶��ͨ��ʧ���ж�Ϊ����о����, ����ʱΪ0xFFFFFF��ȫ0*/
		{
			return(C_Happen_EventState);
		}
		else
		{
			return(C_End_EventState);
		}
	}
	else if(V_ucEventNo == C_ClockFaEventNo)
	{
		V_usDataLen = CLClock_FaultState;
		if(InF_GetData_ObjectManage(CClock_FaultState, &V_ucData, &V_usDataLen, &V_usEncode) != C_OK)	/*�ж�״̬��*/
		{
			return(V_ucHstate);
		}
		if( (V_ucData & C_RTCERR_MeterWorkState) == C_RTCERR_MeterWorkState )
		{
			return(C_Happen_EventState);
		}
		else
		{
			return(C_End_EventState);
		}
	}
	else
	{
		return(V_ucHstate);
	}
}

/***********************************************************************************
����ԭ�ͣ�uchar8 SF_Get_NeutralCurrentAbnormal_Cstate(uchar8 V_ucHstate)
��������: ���ߵ����쳣״̬
���������EventNo���¼��ţ���Hstate����ʷ״̬��
��������������¼���ǰ����״̬
���ز����CC_Happen_V_ucEventState		�¼�״̬���з����޻ָ�
          C_End_EventState	  		�¼�״̬�����з����޻ָ�
          C_Close_EventState		�¼�״̬���ر�
����˵�����ж��¼���ǰ״̬��
���û��ƣ��¼��жϺ�������
��    ע��
***********************************************************************************/
uchar8 SF_Get_NeutralCurrentAbnormal_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
 	uchar8	V_ucJudgeBuffer1[C_Judge_10BufferLength] = {0};					/*���ߵ����ͻ��ߵ�����������ܱ�Ļ��ߵ���Ϊ�������ʸ���ͣ�����һ�������ڵ�����������*/
	uchar8	V_ucJudgeBuffer2[C_3Curr_Length] = {0};					/*���ߵ��������ߵ����Ĳ�ƽ���ʴ��ڲ�ƽ������ֵ*/
	uchar8	V_ucJudgeBuffer3[C_Curr_Length] = {0};					/*���ߵ��������ߵ����Ĳ�ƽ���ʴ��ڲ�ƽ������ֵ*/
	ushort16 V_usDataLength = 0, V_usEncode;
	uchar8	V_ucMax[4] = {0}, V_ucMin[4] = {0};
    ulong32 V_ulDivisor = 0, V_ulDividend = 0, V_ulQuotient = 0;
    ulong32 V_ulVector_Current, V_ulZero_Current;

    /*��ƽ�����жϷ�ֵ*****************************************************/
    V_usDataLength = CLNeutralUnbalanceRate;
	if(InF_GetData_ObjectManage(CNeutralUnbalanceRate, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usDataLength, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}

    /*��ƽ�����жϷ�ֵΪ0�����عر�*/
	if((V_ucJudgeBuffer1[C_Judge_StartBuffer0] == C_NULL)
       &&(V_ucJudgeBuffer1[C_Judge_StartBuffer1] == C_NULL))
	{
		return(C_Close_EventState);
	}

    /*������������*********************************************************/
    V_usDataLength = CLNeutralAbnormal_Curr_LowLim;
	if(InF_GetData_ObjectManage(CNeutralAbnormal_Curr_LowLim, &V_ucJudgeBuffer1[C_Judge_StartBuffer3], &V_usDataLength, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}

    /*�������ʸ����*******************************************************/
    V_usDataLength = CLVector_Current;
	if(InF_GetData_ObjectManage(CVector_Current, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usDataLength, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
    PF_BufferXToUlong32(V_ucJudgeBuffer2, &V_ulVector_Current, CLVector_Current);
    V_ulVector_Current = V_ulVector_Current * 10;
    PF_Ulong32ToBufferX(V_ucJudgeBuffer2, &V_ulVector_Current, CLVector_Current);
    /*���ߵ���*************************************************************/
    V_usDataLength = CLZero_Current;
	if(InF_GetData_ObjectManage(CZero_Current, &V_ucJudgeBuffer2[C_Judge_StartBuffer4], &V_usDataLength, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
    PF_BufferXToUlong32(&V_ucJudgeBuffer2[C_Judge_StartBuffer4], &V_ulZero_Current, CLZero_Current);
    V_ulZero_Current = V_ulZero_Current * 10;
    PF_Ulong32ToBufferX(&V_ucJudgeBuffer2[C_Judge_StartBuffer4], &V_ulZero_Current, CLZero_Current);

    /*��ǰ������ƽ����*****************************************************/
    /*�������ʸ���������ߵ����Ƚϣ���ķ�V_ucMax��С�ķ�V_ucMin*/
	if(PF_Campare_Data(&V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_ucJudgeBuffer2[C_Judge_StartBuffer4], CLVector_Current) == C_GreaterThan)
	{
		PF_CopyDataBytes(&V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_ucMax[C_Judge_StartBuffer0], CLVector_Current);
		PF_CopyDataBytes(&V_ucJudgeBuffer2[C_Judge_StartBuffer4], &V_ucMin[C_Judge_StartBuffer0], CLVector_Current);
	}
    else
    {
		PF_CopyDataBytes(&V_ucJudgeBuffer2[C_Judge_StartBuffer4], &V_ucMax[C_Judge_StartBuffer0], CLVector_Current);
		PF_CopyDataBytes(&V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_ucMin[C_Judge_StartBuffer0], CLVector_Current);
    }

    /*��������0*/
    if(PF_Campare_Data(&V_ucMax[C_Judge_StartBuffer0], &V_ucJudgeBuffer3[C_Judge_StartBuffer0], CLVector_Current) == C_Equal)
    {
        return(C_End_EventState);	/*���ֵΪ0��ʾ���ߵ�������������ľ���ֵ��Ϊ0��������ߵ����쳣�¼�����*/
    }

    /*��ƽ���� = �����ֵ - ��Сֵ�� * 100 / ���ֵ*/
    SF_HEXDECBytes(V_ucMax, V_ucMin, (uchar8 *)&V_ulDivisor, C_Curr_Length);/*���㱻����*/
    V_ulDivisor *= C_TenThousand_times;/*��ֵ*10000*/

    PF_BufferXToUlong32(V_ucMax, &V_ulDividend, CLVector_Current);/*����ѹת��1��32λ����*/

    V_ulQuotient = V_ulDivisor/V_ulDividend;

    PF_Ulong32ToBufferX(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer2], &V_ulQuotient, CLNeutralUnbalanceRate);
    /*���ߵ����쳣���������************************************************/
	if( ( (PF_Campare_Data(&V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_ucJudgeBuffer1[C_Judge_StartBuffer3], CLVector_Current) == C_GreaterThan)
            || (PF_Campare_Data(&V_ucJudgeBuffer2[C_Judge_StartBuffer4], &V_ucJudgeBuffer1[C_Judge_StartBuffer3], CLVector_Current) == C_GreaterThan) )/*�������ʸ���ͻ����ߵ��������ж���ֵ*/
        && (PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer2], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], CLNeutralUnbalanceRate) == C_GreaterThan) )/*��ƽ���ʴ����жϷ�ֵ*/
	{
		return(C_Happen_EventState);
	}
	else
	{
		return(C_End_EventState);
	}
}
/*�����¼��жϺ��������¼���˳�����У�˳�����޸�*/
const Str_EvtJudge Tb_EvtJudgeFunc[] =
{
    SF_Get_TotalVoltageLose_Cstate, 			/*ȫʧѹ*/
    SF_Get_PeripheralEvt_Cstate,               /*������Դʧ��*/
    SF_Get_Powerfail_Cstate,                   /*����*/
    SF_Get_PeripheralEvt_Cstate,               /*�����*/
    SF_Get_PeripheralEvt_Cstate,               /*����ť��*/
    SF_Get_PeripheralEvt_Cstate,               /*�㶨�ų�����*/
    C_NULL,                                 /*��Դ�쳣, ��ר�Žӿں������˴�����*/
    SF_Get_OverActiveDemand_Cstate,            /*�����й���������*/
    SF_Get_OverActiveDemand_Cstate,            /*�����й���������*/
    SF_Get_OverIdleDemand_Cstate,              /*1�����޹���������*/
    SF_Get_OverIdleDemand_Cstate,              /*2�����޹���������*/
    SF_Get_OverIdleDemand_Cstate,              /*3�����޹���������*/
    SF_Get_OverIdleDemand_Cstate,              /*4�����޹���������*/
    SF_Get_lossvoltage_Cstate,                 /*A��ʧѹ*/
    SF_Get_lossvoltage_Cstate,                 /*B��ʧѹ*/
    SF_Get_lossvoltage_Cstate,                 /*C��ʧѹ*/
    SF_Get_Lessvoltage_Cstate,                 /*A��Ƿѹ*/
    SF_Get_Lessvoltage_Cstate,                 /*B��Ƿѹ*/
    SF_Get_Lessvoltage_Cstate,                 /*C��Ƿѹ*/
    SF_Get_Overvoltage_Cstate,                 /*A���ѹ*/
    SF_Get_Overvoltage_Cstate,                 /*B���ѹ*/
    SF_Get_Overvoltage_Cstate,                 /*C���ѹ*/
    SF_Get_Lossphase_Cstate,                   /*A�����*/
    SF_Get_Lossphase_Cstate,                   /*B�����*/
    SF_Get_Lossphase_Cstate,                   /*C�����*/
    SF_Get_ReversephaseVoltage_Cstate,         /*��ѹ������*/
    SF_Get_ReversephaseCurrent_Cstate,         /*����������*/
    SF_Get_UnbanlanceVoltage_Cstate,           /*��ѹ��ƽ��*/
    SF_Get_FFUnbanlanceCurrent_Cstate,         /*������ƽ��*/
    SF_Get_Losscurrent_Cstate,                 /*A��ʧ��*/
    SF_Get_Losscurrent_Cstate,                 /*B��ʧ��*/
    SF_Get_Losscurrent_Cstate,                 /*C��ʧ��*/
    SF_Get_Overcurrent_Cstate,                 /*A�����*/
    SF_Get_Overcurrent_Cstate,                 /*B�����*/
    SF_Get_Overcurrent_Cstate,                 /*C�����*/
    SF_Get_Failcurrent_Cstate,                 /*A�����*/
    SF_Get_Failcurrent_Cstate,                 /*B�����*/
    SF_Get_Failcurrent_Cstate,                 /*C�����*/
    SF_Get_FFReversecurrent_Cstate,            /*�ܹ��ʷ���*/
    SF_Get_FFReversecurrent_Cstate,            /*A�๦�ʷ���*/
    SF_Get_FFReversecurrent_Cstate,            /*B�๦�ʷ���*/
    SF_Get_FFReversecurrent_Cstate,            /*C�๦�ʷ���*/
    SF_Get_Overload_Cstate,                    /*A�����*/
    SF_Get_Overload_Cstate,                    /*B�����*/
    SF_Get_Overload_Cstate,                    /*C�����*/
    SF_Get_Overpowerfact_Cstate,               /*�ܹ�������������*/
    SF_Get_FFOverpowerfact_Cstate,             /*A�๦������������*/
    SF_Get_FFOverpowerfact_Cstate,             /*B�๦������������*/
    SF_Get_FFOverpowerfact_Cstate,             /*C�๦������������*/
    SF_Get_FFUnbanlanceCurrent_Cstate,         /*�������ز�ƽ��*/
    SF_Get_MeterAndClockFa_Cstate, 				/*����оƬ����*/
    SF_Get_MeterAndClockFa_Cstate,             /*ʱ�ӹ���*/
    SF_Get_NeutralCurrentAbnormal_Cstate,      /*���ߵ����쳣�¼���*/
};
/***********************************************************************************
����ԭ�ͣ�uchar8 SF_Get_Event_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
�����������ж��¼���ǰ״̬
���������EventNo��Hstate����ʷ״̬��
��������������¼���ǰ����״̬
���ز����CC_IDError             ���ݱ�ʶ�����
           C_Happen_EventState	�¼�״̬���з����޻ָ�
          C_End_EventState	  	�¼�״̬�����з����޻ָ�
          C_Close_EventState	�¼�״̬���ر�״̬
����˵�����ж��¼���ǰ״̬��
���û��ƣ��¼��жϺ�������
��    ע��
***********************************************************************************/
uchar8 SF_Get_Event_Cstate(uchar8 V_ucEventNo, uchar8 V_ucEvent_Hstate)
{
	uchar8 V_ucMode;

    if((V_ucEventNo > C_NeutralCurrentAbnormalEventNo) || (V_ucEventNo == C_PowerAbnormalEventNo))
    {
        V_ucMode = C_IDError;
    }
    else
    {
        V_ucMode = Tb_EvtJudgeFunc[V_ucEventNo].EvtJudgeFunc(V_ucEventNo, V_ucEvent_Hstate);
    }

	return(V_ucMode);
}

/***********************************************************************************
����ԭ�ͣ�uchar8 SF_Judge_Event_Statechange(uchar8 V_ucEventNo, uchar8 V_ucDelayTime)
�����������ж��¼��Ƿ��з���/�ָ���Ϣ����
���������EventNo���¼��ţ���DelayTime���ж���ʱʱ�䣩
��������������¼���ǰ����״̬
���ز����CC_IDError             ���ݱ�ʶ�����
  		C_Happen_EventMsg	0x68	�¼���������
  		C_End_EventMsg		0x00	�¼��ָ�����
  		C_NULL_EventMsg	    0x66	�¼��޶���
����˵�����ж��¼���ǰ�Ƿ�����Ϣ������
���û��ƣ��¼��жϺ�������
��    ע��
***********************************************************************************/
uchar8 SF_Judge_Event_Statechange(uchar8 V_ucEventNo, uchar8 V_ucDelayTime)
{
	uchar8 V_ucCstate;

	if(V_ucEventNo <= C_NeutralCurrentAbnormalEventNo)
	{
		V_ucCstate = SF_Get_Event_Cstate(V_ucEventNo, GV_ucEvent_Hstate[V_ucEventNo]);

		if( (V_ucCstate == GV_ucEvent_Hstate[V_ucEventNo])
           || ((GV_ucEvent_Hstate[V_ucEventNo] == C_Close_EventState) && (V_ucCstate == C_End_EventState)) )
		{
			GV_ucEvent_JudgeTimer[V_ucEventNo] = C_NULL;
			return(C_Null_EventMsg);
		}
		else
		{
			if(V_ucCstate == C_Close_EventState)
			{
				GV_ucEvent_JudgeTimer[V_ucEventNo] = C_NULL;
				if(GV_ucEvent_Hstate[V_ucEventNo] == C_Happen_EventState)
				{
				    GV_ucEvent_Hstate[V_ucEventNo] = V_ucCstate;
					return(C_End_EventMsg);
				}
				else
				{
				    GV_ucEvent_Hstate[V_ucEventNo] = V_ucCstate;
					return(C_Null_EventMsg);
				}
			}
			else
			{
				if(GV_ucEvent_JudgeTimer[V_ucEventNo] >= V_ucDelayTime)
				{

					if(V_ucCstate == C_Happen_EventState)
					{
					    GV_ucEvent_Hstate[V_ucEventNo] = V_ucCstate;
						return(C_Happen_EventMsg);
					}
					else
					{
					    GV_ucEvent_Hstate[V_ucEventNo] = V_ucCstate;
						return(C_End_EventMsg);
					}
				}
				else
				{
					GV_ucEvent_JudgeTimer[V_ucEventNo] ++;
					return(C_Null_EventMsg);
				}

			}
		}
	}
	else
	{
		return(C_IDError);
	}
}

/***********************************************************************************
����ԭ�ͣ�void SF_AppendEventMessage(uchar8 V_ucEventNo, uchar8 EventMsg)
�����������¼������ָ�ʱ��������Ϣ
���������EventNo��EventMsg���¼�������, V_ucPowFlag����Դ״̬
�����������
���ز������ޣ�
����˵��������Ϣ�е�ʱ�䣬�ϵ�ʱ�ý��͹���ʱ�䣬�е�ʱ�õ�ǰʱ�䣻
���û��ƣ��ϵ��ʼ�����¼��жϺ�������
��    ע��
***********************************************************************************/
void SF_AppendEventMessage(uchar8 V_ucEventNo, uchar8 EventMsg, uchar8 V_ucPowFlag)
{
	uchar8	V_ucDataBuffer[C_Event_MsgLength];				/*����*/
	ushort16 V_usDataBufferLength = C_Event_MsgLength, V_usEncode;			/*ʱ�䳤��*/
	Str_Msg_Parameter	Str_SendMsg;
    ulong32 V_ulDI;

	Str_SendMsg.PowerFlag = C_PowerOn;							/*�е�*/
	Str_SendMsg.SourceAddr = C_Msg_PowerNetworkMonitoring;	/*�¼��ж�Դ��Ϣ��*/
	Str_SendMsg.DerictAddr = C_Msg_PowerNetworkMonitoring;	/*�¼��ж�Ŀ����Ϣ��*/
	Str_SendMsg.Length = C_Event_MsgLength;						/*�¼��жϷ��ͽ������ݳ���*/
	V_ucDataBuffer[C_PTEventNo_Msgbuffer] = PT_EventNo;
	V_ucDataBuffer[C_EventNo_Msgbuffer] = V_ucEventNo;

	Str_SendMsg.Parameter = &V_ucDataBuffer[C_PTEventNo_Msgbuffer];

    if(V_ucPowFlag == C_PowerRising)
    {
        V_ulDI = CEnter_LowPower_Time;
    }
    else
    {
        V_ulDI = CDate_Time;
    }
	if(InF_GetData_ObjectManage(V_ulDI, &V_ucDataBuffer[C_Time_Msgbuffer], &V_usDataBufferLength, &V_usEncode) == C_OK)/*����ǰʱ��*/
	{
		if(EventMsg == C_Happen_EventMsg)
		{
			V_ucDataBuffer[C_PTTime_Msgbuffer] = Pt_HappenTime;
			InF_WriteMessege(&Str_SendMsg);
		}
		else
		{
			if(EventMsg == C_End_EventMsg)
			{
				V_ucDataBuffer[C_PTTime_Msgbuffer] = Pt_EndTime;
				InF_WriteMessege(&Str_SendMsg);
			}
			else
			{
				return;
			}
		}
	}
}

/***********************************************************************************
����ԭ�ͣ�void SF_AppendEventMessageLowPower(uchar8 V_ucEventNo, uchar8 EventMsg)
�����������¼������ָ�ʱ��������Ϣ
���������EventNo��EventMsg���¼�������
��������������¼���ǰ����״̬
���ز������ޣ�
����˵�����ж��¼���ǰ״̬��
���û��ƣ��¼��жϺ�������
��    ע��
***********************************************************************************/
void SF_AppendEventMessageLowPower(uchar8 V_ucEventNo, uchar8 EventMsg)
{
	uchar8	V_ucDataBuffer[C_Event_MsgLength];				/*����*/
	Str_Msg_Parameter	Str_SendMsg;

	Str_SendMsg.PowerFlag = C_PowerOn;							/*�е�*/
	Str_SendMsg.SourceAddr = C_Msg_PowerNetworkMonitoring;	/*�¼��ж�Դ��Ϣ��*/
	Str_SendMsg.DerictAddr = C_Msg_PowerNetworkMonitoring;	/*�¼��ж�Ŀ����Ϣ��*/
	Str_SendMsg.Length = C_Event_MsgLength;						/*�¼��жϷ��ͽ������ݳ���*/
	V_ucDataBuffer[C_PTEventNo_Msgbuffer] = PT_EventNo;
	V_ucDataBuffer[C_EventNo_Msgbuffer] = V_ucEventNo;
	Str_SendMsg.Parameter = &V_ucDataBuffer[C_PTEventNo_Msgbuffer];

	switch(V_ucEventNo)
	{
		case	C_TotalVoltageLoseEventNo:					   /*ȫʧѹ�͹�����ʱ��*/
				PF_CopyDataBytes(GStr_TotalvoltageloseStr.Time, &V_ucDataBuffer[C_Time_Msgbuffer], C_EventTimeLength);
				break;
 		case	C_ACPowerFailEventNo:						 	/*������Դʧ��͹�����ʱ��*/
				PF_CopyDataBytes(GStr_ACPowerFailStr.Time, &V_ucDataBuffer[C_Time_Msgbuffer], C_EventTimeLength);
				break;
		case	C_PowerfailEventNo:						 	 /*����͹�����ʱ��*/
				PF_CopyDataBytes(GStr_PowerfailStr.Time, &V_ucDataBuffer[C_Time_Msgbuffer], C_EventTimeLength);
				break;
		case	C_OpenMeterCoverLowPower:							 /*����ǹ�����ʱ��*/
                V_ucDataBuffer[C_EventNo_Msgbuffer]=C_OpenMeterCoverEventNo;
				PF_CopyDataBytes(GStr_OpenMeterCoverStr.HappenTime, &V_ucDataBuffer[C_Time_Msgbuffer], C_EventTimeLength);
				break;
		case	C_CloseMeterCoverLowPower:							 /*�ϱ�ǹ�����ʱ��*/
				V_ucDataBuffer[C_EventNo_Msgbuffer]=C_OpenMeterCoverEventNo;
                PF_CopyDataBytes(GStr_OpenMeterCoverStr.EndTime, &V_ucDataBuffer[C_Time_Msgbuffer], C_EventTimeLength);
				break;
		case	C_OpenTerminalCoverLowPower:							 /*����ť�ǹ�����ʱ��*/
				V_ucDataBuffer[C_EventNo_Msgbuffer]=C_OpenTerminalCoverEventNo;
                PF_CopyDataBytes(GStr_OpenTerminalCoverStr.HappenTime, &V_ucDataBuffer[C_Time_Msgbuffer], C_EventTimeLength);
				break;
		case	C_CloseTerminalCoverLowPower:							 /*�϶�ť�ǹ�����ʱ��*/
				V_ucDataBuffer[C_EventNo_Msgbuffer]=C_OpenTerminalCoverEventNo;
                PF_CopyDataBytes(GStr_OpenTerminalCoverStr.EndTime, &V_ucDataBuffer[C_Time_Msgbuffer], C_EventTimeLength);
				break;
		default:
				break;
	}

	if(EventMsg == C_Happen_EventMsg)
	{
		V_ucDataBuffer[C_PTTime_Msgbuffer] = Pt_HappenTime;
		InF_WriteMessege(&Str_SendMsg);
	}
	else
	{
		if(EventMsg == C_End_EventMsg)
		{
			V_ucDataBuffer[C_PTTime_Msgbuffer] = Pt_EndTime;
			InF_WriteMessege(&Str_SendMsg);
		}
		else
		{
			return;
		}
	}
}
/***********************************************************************************
����ԭ�ͣ�void SF_Judge_Event_Msg(uchar8 V_ucEventNo, uchar8 EventMsg)
�����������¼������ָ�ʱ��������Ϣ
���������EventNo��EventMsg���¼�������
��������������¼���ǰ����״̬
���ز������ޣ�
����˵�����ж��¼���ǰ״̬��
���û��ƣ��¼��жϺ�������
��    ע��
***********************************************************************************/
void SF_Judge_Event_Msg(void)
{
	uchar8	V_ucDelayTime, V_ucEventNo, V_ucEventMsg;
	uchar8	V_ucPhase;
	uchar8	V_ucDataTemp = 0;
    ushort16 V_usEncode, V_usDataLen;

    V_usDataLen = CLLine_Type;
	InF_GetData_ObjectManage(CLine_Type, &V_ucPhase, &V_usDataLen, &V_usEncode);					/*�����ܱ����ͣ���������/��������*/

	for(V_ucEventNo = C_TotalVoltageLoseEventNo;V_ucEventNo <= C_NeutralCurrentAbnormalEventNo;V_ucEventNo ++)
	{
		if( ( (V_ucPhase == C_3P3W) && (Event_ChooseTableNo[V_ucEventNo][C_PhaseTypeRowN0] == C_3P3W) )
           || (V_ucEventNo == C_PowerAbnormalEventNo) )/*��������ʱ��B���¼������๦���������޲���*/
		{
			continue;
		}
		if(V_ucEventNo == C_ACPowerFailEventNo)
		{
			V_usDataLen = CLAuxi_Power_Sign;
			if(InF_GetData_ObjectManage(CAuxi_Power_Sign, &V_ucDataTemp, &V_usDataLen, &V_usEncode) != C_OK)
			{
				continue;
			}
			if(V_ucDataTemp == C_NoACPowerFail)
			{
				continue;
			}
		}
		if(V_ucEventNo == C_NeutralCurrentAbnormalEventNo)
		{
			V_usDataLen = CLZero_Current_Sign;
			if(InF_GetData_ObjectManage(CZero_Current_Sign, &V_ucDataTemp, &V_usDataLen, &V_usEncode) == C_OK)/*���ߵ�������*/
			{
				if(V_ucDataTemp == C_ZeroCurrentOff)/*�����ߵ�����ֱ���˳�*/
				{
					continue;
				}
			}
		}
		V_ucDelayTime = SF_Get_Event_DalayTime(V_ucEventNo);
		if(V_ucDelayTime == C_JudgeTimeError)
		{
			return;
		}
        V_ucEventMsg = SF_Judge_Event_Statechange(V_ucEventNo, V_ucDelayTime);

        SF_AppendEventMessage(V_ucEventNo, V_ucEventMsg, C_PowerOn);
	}
}
/***********************************************************************************
����ԭ�ͣ�void SF_Str_Clear(void)
�����������ṹ������
���������
���������
���ز�����
����˵��������ʱ����
���û��ƣ�
��    ע��
***********************************************************************************/
void SF_Str_Clear(uchar8 EventNo)
{
	uchar8 V_ucJudgeBuffer1[C_Judge_50BufferLength]={C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL
                , C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL
                , C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL
                , C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL};

	PF_CopyDataBytes_698(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], CommunicateEventClearTable[EventNo].P_Str, CommunicateEventClearTable[EventNo].Length);
}
/***********************************************************************************
����ԭ�ͣ�void SF_Str_CalCRC(uchar8	EventNo)
��������������ṹ��CRC
���������
���������
���ز�����
����˵��������ʱ����
���û��ƣ�
��    ע��
***********************************************************************************/
void SF_Str_CalCRC(uchar8	EventNo)
{
	ushort16 V_usCRC, V_usLength = (CommunicateEventClearTable[EventNo].Length - C_CRC_Length);/*�ṹ�����ݳ���*/

	V_usCRC = PF_Cal_CRC(CommunicateEventClearTable[EventNo].P_Str, V_usLength);

	PF_Ushort16ToBuffer2(CommunicateEventClearTable[EventNo].P_CRCAddr, &V_usCRC);
}
/***********************************************************************************
����ԭ�ͣ�uchar8 SF_Str_CheckCRC(uchar8	EventNo)
����������check�ṹ��CRC
���������
���������
���ز�����
����˵��������ʱ����
���û��ƣ�
��    ע��
***********************************************************************************/
uchar8 SF_Str_CheckCRC(uchar8	EventNo)
{
	uchar8	V_ucReturnFlag;

	V_ucReturnFlag = PF_Check_CRC(CommunicateEventClearTable[EventNo].P_Str, CommunicateEventClearTable[EventNo].Length);

    if(EventNo == C_MagneticCheckEventNo)
    {
        V_ucReturnFlag = C_OK;
    }
	return V_ucReturnFlag;
}

/***********************************************************************************
����ԭ�ͣ�void SF_SymbolDisplay_Judgemsg(void)
������������ʾ���ź���
���������
���������
���ز�����
����˵�����ж���Ϣ����ʱ����
���û��ƣ��ж���Ϣ����
��    ע��
***********************************************************************************/
void SF_SymbolDisplay_Judgemsg(void)
{
	uchar8		V_uci, V_ucPhase;
	uchar8		V_ucDisplayBuffer[10];
	uchar8 		V_ucEvent_SymbolCstate[C_EventSymbolLength];
	Str_Msg_Parameter	Str_Event_DisplayMsg;
    ushort16    V_usPhaseLength = 1, V_usEncode;

    if( (GV_ucEvent_Hstate[C_ALossphaseEventNo] == C_Happen_EventState)
       || ((GV_ucEvent_Hstate[C_PowerfailEventNo] == C_Happen_EventState) && (GV_ucEvent_Hstate[C_TotalVoltageLoseEventNo] != C_Happen_EventState)) )//ȫʧѹ�͵���ͬʱ���������ſ�ȫʧѹ����˸
    {
        V_ucEvent_SymbolCstate[C_AVoltage_SymbolNO] = C_NotDisplay;
    }
    else
	{
        if( (GV_ucEvent_Hstate[C_AlossvoltageEventNo] == C_Happen_EventState)
           || (GV_ucEvent_Hstate[C_TotalVoltageLoseEventNo] == C_Happen_EventState) )
        {
            V_ucEvent_SymbolCstate[C_AVoltage_SymbolNO] = C_TwinkleDisplay;
        }
		else
		{
			V_ucEvent_SymbolCstate[C_AVoltage_SymbolNO] = C_AlwaysDisplay;
		}
	}
    InF_GetData_ObjectManage(CLine_Type, &V_ucPhase, &V_usPhaseLength, &V_usEncode);		/*�����ܱ����ͣ���������/��������*/

    if( (V_ucPhase==C_3P3W) || (GV_ucEvent_Hstate[C_BLossphaseEventNo] == C_Happen_EventState)
       || ((GV_ucEvent_Hstate[C_PowerfailEventNo] == C_Happen_EventState) && (GV_ucEvent_Hstate[C_TotalVoltageLoseEventNo] != C_Happen_EventState)) )/*ȫʧѹ�͵���ͬʱ���������ſ�ȫʧѹ����˸*/
    {
        V_ucEvent_SymbolCstate[C_BVoltage_SymbolNO] = C_NotDisplay;
    }
    else
    {
        if((GV_ucEvent_Hstate[C_BlossvoltageEventNo] == C_Happen_EventState) || (GV_ucEvent_Hstate[C_TotalVoltageLoseEventNo] == C_Happen_EventState) )
        {
            V_ucEvent_SymbolCstate[C_BVoltage_SymbolNO] = C_TwinkleDisplay;
        }
        else
        {
            V_ucEvent_SymbolCstate[C_BVoltage_SymbolNO] = C_AlwaysDisplay;
        }
    }


    if( (GV_ucEvent_Hstate[C_CLossphaseEventNo] == C_Happen_EventState)
       || ((GV_ucEvent_Hstate[C_PowerfailEventNo] == C_Happen_EventState) && (GV_ucEvent_Hstate[C_TotalVoltageLoseEventNo] != C_Happen_EventState)) )/*ȫʧѹ�͵���ͬʱ���������ſ�ȫʧѹ����˸*/
    {
        V_ucEvent_SymbolCstate[C_CVoltage_SymbolNO] = C_NotDisplay;
    }
	else
	{

        if((GV_ucEvent_Hstate[C_ClossvoltageEventNo] == C_Happen_EventState) || (GV_ucEvent_Hstate[C_TotalVoltageLoseEventNo] == C_Happen_EventState))
        {
            V_ucEvent_SymbolCstate[C_CVoltage_SymbolNO] = C_TwinkleDisplay;
        }
		else
		{
			V_ucEvent_SymbolCstate[C_CVoltage_SymbolNO] = C_AlwaysDisplay;
		}
	}

    if( (GV_ucEvent_Hstate[C_ALossphaseEventNo] == C_Happen_EventState)
       || ((GV_ucEvent_Hstate[C_PowerfailEventNo] == C_Happen_EventState) && (GV_ucEvent_Hstate[C_TotalVoltageLoseEventNo] != C_Happen_EventState)) )/*ȫʧѹ�͵���ͬʱ���������ſ�ȫʧѹ����˸*/
    {
      	V_ucEvent_SymbolCstate[C_ACurrentminus_SymbolNO] = C_NotDisplay;/*������ߵ��磬���Źر�*/
		V_ucEvent_SymbolCstate[C_ACurrent_SymbolNO] = C_NotDisplay;
    }
    else
    {
        if(GV_ucEvent_Hstate[C_ALosscurrentEventNo] == C_Happen_EventState)
        {
            V_ucEvent_SymbolCstate[C_ACurrentminus_SymbolNO] = C_TwinkleDisplay;
            V_ucEvent_SymbolCstate[C_ACurrent_SymbolNO] = C_TwinkleDisplay;
        }
        else
        {
            if(GV_ucEvent_Hstate[C_AFailcurrentEventNo] == C_Happen_EventState)
            {
                V_ucEvent_SymbolCstate[C_ACurrentminus_SymbolNO] = C_NotDisplay;
                V_ucEvent_SymbolCstate[C_ACurrent_SymbolNO] = C_NotDisplay;
            }
            else
            {
                V_ucEvent_SymbolCstate[C_ACurrentminus_SymbolNO] = C_AlwaysDisplay;
                V_ucEvent_SymbolCstate[C_ACurrent_SymbolNO] = C_AlwaysDisplay;
            }
        }
    }

    if( (V_ucPhase == C_3P3W) || (GV_ucEvent_Hstate[C_BLossphaseEventNo] == C_Happen_EventState)
       || ((GV_ucEvent_Hstate[C_PowerfailEventNo] == C_Happen_EventState) && (GV_ucEvent_Hstate[C_TotalVoltageLoseEventNo] != C_Happen_EventState)) )/*ȫʧѹ�͵���ͬʱ���������ſ�ȫʧѹ����˸*/
    {
      	V_ucEvent_SymbolCstate[C_BCurrentminus_SymbolNO] = C_NotDisplay;/*������ߵ��磬���Źر�*/
		V_ucEvent_SymbolCstate[C_BCurrent_SymbolNO] = C_NotDisplay;
    }
    else
    {
        if(GV_ucEvent_Hstate[C_BLosscurrentEventNo] == C_Happen_EventState)
        {
            V_ucEvent_SymbolCstate[C_BCurrentminus_SymbolNO] = C_TwinkleDisplay;
            V_ucEvent_SymbolCstate[C_BCurrent_SymbolNO] = C_TwinkleDisplay;
        }
        else
        {
            if(GV_ucEvent_Hstate[C_BFailcurrentEventNo] == C_Happen_EventState)
            {
                V_ucEvent_SymbolCstate[C_BCurrentminus_SymbolNO] = C_NotDisplay;
                V_ucEvent_SymbolCstate[C_BCurrent_SymbolNO] = C_NotDisplay;
            }
            else
            {
                V_ucEvent_SymbolCstate[C_BCurrentminus_SymbolNO] = C_AlwaysDisplay;
                V_ucEvent_SymbolCstate[C_BCurrent_SymbolNO] = C_AlwaysDisplay;
            }
        }
    }

    if( (GV_ucEvent_Hstate[C_CLossphaseEventNo] == C_Happen_EventState)
       || ((GV_ucEvent_Hstate[C_PowerfailEventNo] == C_Happen_EventState) && (GV_ucEvent_Hstate[C_TotalVoltageLoseEventNo] != C_Happen_EventState)) )/*ȫʧѹ�͵���ͬʱ���������ſ�ȫʧѹ����˸*/
    {
      	V_ucEvent_SymbolCstate[C_CCurrentminus_SymbolNO] = C_NotDisplay;/*������ߵ��磬���Źر�*/
		V_ucEvent_SymbolCstate[C_CCurrent_SymbolNO] = C_NotDisplay;
    }
    else
    {
        if(GV_ucEvent_Hstate[C_CLosscurrentEventNo] == C_Happen_EventState)
        {
            V_ucEvent_SymbolCstate[C_CCurrentminus_SymbolNO] = C_TwinkleDisplay;
            V_ucEvent_SymbolCstate[C_CCurrent_SymbolNO] = C_TwinkleDisplay;
        }
        else
        {
            if(GV_ucEvent_Hstate[C_CFailcurrentEventNo] == C_Happen_EventState)
            {
                V_ucEvent_SymbolCstate[C_CCurrentminus_SymbolNO] = C_NotDisplay;
                V_ucEvent_SymbolCstate[C_CCurrent_SymbolNO] = C_NotDisplay;
            }
            else
            {
                V_ucEvent_SymbolCstate[C_CCurrentminus_SymbolNO] = C_AlwaysDisplay;
                V_ucEvent_SymbolCstate[C_CCurrent_SymbolNO] = C_AlwaysDisplay;
            }
        }
    }

	if( (GV_ucEvent_Hstate[C_ReversephaseVoltageEventNo] == C_Happen_EventState) || (GV_ucEvent_Hstate[C_ReversephaseCurrentEventNo] == C_Happen_EventState))
	{
		V_ucEvent_SymbolCstate[C_Reversephase_SymbolNO] = C_AlwaysDisplay;
	}
	else
	{
		V_ucEvent_SymbolCstate[C_Reversephase_SymbolNO] = C_NotDisplay;
	}
	for(V_uci = C_AVoltage_SymbolNO;V_uci <= C_Reversephase_SymbolNO;V_uci ++)
	{
		if(V_ucEvent_SymbolCstate[V_uci] != GV_ucEvent_SymbolHstate[V_uci])
		{
			Str_Event_DisplayMsg.PowerFlag = C_PowerOn;
			Str_Event_DisplayMsg.SourceAddr = C_Msg_PowerNetworkMonitoring;
			Str_Event_DisplayMsg.DerictAddr = C_Msg_Display;
			if((V_uci >= C_ACurrentminus_SymbolNO) && (V_uci <= C_CCurrent_SymbolNO))/*�������ŷ�8���ֽ�����*/
			{
				Str_Event_DisplayMsg.Length = 8;
			}
			else
			{
				Str_Event_DisplayMsg.Length = 4;														/*��ѹ���š�������4���ֽ�*/
			}
			V_ucDisplayBuffer[C_DisplayMsgPT1] = Pt_DisplayStatus;
			V_ucDisplayBuffer[C_DisplayMsgTime1H] = 0xFF;			/*��˸ʱ�䣬��ģ�鲻����������ʾ�������ճ���ʱ��FF������*/
			V_ucDisplayBuffer[C_DisplayMsgTime1L] = 0xFF;
            V_ucDisplayBuffer[C_DisplayMsgPT2] = Pt_DisplayStatus;
            V_ucDisplayBuffer[C_DisplayMsgTime2H] = 0xFF;			/*��˸ʱ�䣬��ģ�鲻����������ʾ�������ճ���ʱ��FF������*/
            V_ucDisplayBuffer[C_DisplayMsgTime2L] = 0xFF;
            if(V_uci == C_AVoltage_SymbolNO)						/*A���ѹ����*/
			{
				V_ucDisplayBuffer[C_DisplayMsgType1] = (V_ucEvent_SymbolCstate[V_uci] | C_UaSign);
			}
			if(V_uci == C_BVoltage_SymbolNO)						/*B���ѹ����*/
			{
				V_ucDisplayBuffer[C_DisplayMsgType1] = (V_ucEvent_SymbolCstate[V_uci] | C_UbSign);
			}
			if(V_uci==C_CVoltage_SymbolNO)						/*C���ѹ����*/
			{
				V_ucDisplayBuffer[C_DisplayMsgType1] = (V_ucEvent_SymbolCstate[V_uci] | C_UcSign);
			}
			if(V_uci == C_ACurrent_SymbolNO)						/*A��������š����ź͵�������Ĭ�϶�ͬʱ����*/
			{
				if(V_ucEvent_SymbolCstate[V_uci] == C_TwinkleDisplay)
				{
					V_ucDisplayBuffer[C_DisplayMsgType1] = (C_TwinkleDisplay | C_IaNegativeSign);
					V_ucDisplayBuffer[C_DisplayMsgType2] = (C_TwinkleDisplay | C_IaSign);
				}
				if(V_ucEvent_SymbolCstate[V_uci] == C_AlwaysDisplay)
				{
					V_ucDisplayBuffer[C_DisplayMsgType1] = (C_AlwaysDisplay | C_IaNegativeSign);
					V_ucDisplayBuffer[C_DisplayMsgType2] = (C_AlwaysDisplay | C_IaSign);
				}
				if(V_ucEvent_SymbolCstate[V_uci] == C_NotDisplay)
				{
					V_ucDisplayBuffer[C_DisplayMsgType1] = (C_NotDisplay | C_IaNegativeSign);
					V_ucDisplayBuffer[C_DisplayMsgType2] = (C_NotDisplay | C_IaSign);
				}
			}
			if(V_uci == C_ACurrentminus_SymbolNO)
			{
				continue;
			}
			if(V_uci == C_BCurrent_SymbolNO)					/*A��������š����ź͵�������Ĭ�϶�ͬʱ����*/
			{
				if(V_ucEvent_SymbolCstate[V_uci] == C_TwinkleDisplay)
				{
					V_ucDisplayBuffer[C_DisplayMsgType1] = (C_TwinkleDisplay | C_IbNegativeSign);
					V_ucDisplayBuffer[C_DisplayMsgType2] = (C_TwinkleDisplay | C_IbSign);
				}
				if(V_ucEvent_SymbolCstate[V_uci] == C_AlwaysDisplay)
				{
					V_ucDisplayBuffer[C_DisplayMsgType1] = (C_AlwaysDisplay | C_IbNegativeSign);
					V_ucDisplayBuffer[C_DisplayMsgType2] = (C_AlwaysDisplay | C_IbSign);
				}
				if(V_ucEvent_SymbolCstate[V_uci] == C_NotDisplay)
				{
					V_ucDisplayBuffer[C_DisplayMsgType1] = (C_NotDisplay | C_IbNegativeSign);
					V_ucDisplayBuffer[C_DisplayMsgType2] = (C_NotDisplay | C_IbSign);
				}
			}
			if(V_uci == C_BCurrentminus_SymbolNO)
			{
				continue;
			}
			if(V_uci == C_CCurrent_SymbolNO)			/*A��������š����ź͵�������Ĭ�϶�ͬʱ����*/
			{
				if(V_ucEvent_SymbolCstate[V_uci] == C_TwinkleDisplay)
				{
					V_ucDisplayBuffer[C_DisplayMsgType1] = (C_TwinkleDisplay | C_IcNegativeSign);
					V_ucDisplayBuffer[C_DisplayMsgType2] = (C_TwinkleDisplay | C_IcSign);
				}
				if(V_ucEvent_SymbolCstate[V_uci] == C_AlwaysDisplay)
				{
					V_ucDisplayBuffer[C_DisplayMsgType1] = (C_AlwaysDisplay | C_IcNegativeSign);
					V_ucDisplayBuffer[C_DisplayMsgType2] = (C_AlwaysDisplay | C_IcSign);
				}
				if(V_ucEvent_SymbolCstate[V_uci] == C_NotDisplay)
				{
					V_ucDisplayBuffer[C_DisplayMsgType1] = (C_NotDisplay | C_IcNegativeSign);
					V_ucDisplayBuffer[C_DisplayMsgType2] = (C_NotDisplay | C_IcSign);
				}
			}
			if(V_uci == C_CCurrentminus_SymbolNO)
			{
				continue;
			}
			if(V_uci == C_Reversephase_SymbolNO)		/*�������������Ի��߹ر�*/
			{
				if(V_ucEvent_SymbolCstate[V_uci] == C_AlwaysDisplay)
				{
					V_ucDisplayBuffer[C_DisplayMsgType1] = (C_AlwaysDisplay | C_NegativePhaseSign);
				}
				if(V_ucEvent_SymbolCstate[C_Reversephase_SymbolNO] == C_NotDisplay)
				{
					V_ucDisplayBuffer[C_DisplayMsgType1] = (C_NotDisplay | C_NegativePhaseSign);
				}
			}
			Str_Event_DisplayMsg.Parameter = &V_ucDisplayBuffer[0];
			InF_WriteMessege(&Str_Event_DisplayMsg);/*����Ϣ*/
			GV_ucEvent_SymbolHstate[V_uci] = V_ucEvent_SymbolCstate[V_uci];	/*����ʾ������ʷ״̬��ֵ*/
		}
	}
}
/***********************************************************************************
����ԭ�ͣ�void SF_AlarmDisplay_Judgemsg(void)
������������������
�������:
���������
���ز�����
����˵�����ж���Ϣ����ʱ����
���û��ƣ��ж���Ϣ����
��    ע��
***********************************************************************************/
void SF_AlarmDisplay_Judgemsg(void)
 {
	uchar8	V_ucAlarmModeReturnData[C_AlarmModeLength];	/*������ģʽ����*/
	ushort16 V_usBufferLength1 = C_Judge_20BufferLength, V_usEncode;
	uchar8	V_ucBellAlarmTemp[C_AlarmTempLength], V_ucAlarmOuputTemp[C_AlarmTempLength], V_ucBackLightAlarmTemp[C_AlarmTempLength];	/*��ǰ�����ͱ���ģʽ�ֵ����*/
	uchar8	V_ucDisplayBuffer[4];
    uchar8  V_ucBufferNull[C_AlarmTempLength] = {0};
    uchar8  V_ucEventNo;
    ulong64 V_ucAlarmCompareTemp, V_ucAlarmHstateCompareTemp;
    uchar8 V_ucBitNo, V_uc1ByteAlarmTemp, V_uc1ByteAlarmHstateTemp, V_ucSendMessageTemp=C_NULL;
	Str_Msg_Parameter	    Str_Event_DisplayMsg;
    uchar8  V_uci, *pV_ucAlarmTemp, *pV_ucHstateTemp, V_ucType, V_ucDisMode;

    PF_CopyDataBytes(&V_ucBufferNull[0], &GStr_BellAlarm.A0_Flag, C_AlarmTempLength);        /*״̬������*/
    PF_CopyDataBytes(&V_ucBufferNull[0], &GStr_Alarmoutput.A0_Flag, C_AlarmTempLength);
    PF_CopyDataBytes(&V_ucBufferNull[0], &GStr_BackLightAlarm.A0_Flag, C_AlarmTempLength);

	if(InF_GetData_ObjectManage(CAlarm_Status, &V_ucAlarmModeReturnData[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode))/*����ģʽ�ֲ��ɹ����˳�*(�ӵ͵��ߣ����⣬���������С����)*/
	{
		return;
	}
	for(V_ucEventNo = C_TotalVoltageLoseEventNo;V_ucEventNo <= C_SUnbanlanceCurrentEventNo;V_ucEventNo ++)
    {
        if(GV_ucEvent_Hstate[V_ucEventNo] == C_Happen_EventState)
        {		/*�¼�����*/
            *(CommunicateEventClearTable[V_ucEventNo].P_BackLightAlarm) |= CommunicateEventClearTable[V_ucEventNo].V_AlarmStart;	/*����״̬��λ*/
            *(CommunicateEventClearTable[V_ucEventNo].P_AlarmOuput) |= CommunicateEventClearTable[V_ucEventNo].V_AlarmStart;		/*�������״̬��λ*/
            *(CommunicateEventClearTable[V_ucEventNo].P_BellAlarm) |= CommunicateEventClearTable[V_ucEventNo].V_AlarmStart;		/*С������ǰ״̬��λ*/
        }
        else
        {
            if(V_ucEventNo == C_OverForwardActiveEventNo)
            {
                if(GV_ucEvent_Hstate[C_OverReverseActiveEventNo] == C_Happen_EventState)
                {
                    continue;
                }
            }
            if(V_ucEventNo == C_OverReverseActiveEventNo)
            {
                if(GV_ucEvent_Hstate[C_OverForwardActiveEventNo] == C_Happen_EventState)
                {
                    continue;
                }
            }
            *(CommunicateEventClearTable[V_ucEventNo].P_BackLightAlarm)&=CommunicateEventClearTable[V_ucEventNo].V_AlarmClose;	/*����״̬��λ*//*���ǳ�������*/
            *(CommunicateEventClearTable[V_ucEventNo].P_AlarmOuput)&=CommunicateEventClearTable[V_ucEventNo].V_AlarmClose;		/*�������״̬��λ*/
            *(CommunicateEventClearTable[V_ucEventNo].P_BellAlarm)&=CommunicateEventClearTable[V_ucEventNo].V_AlarmClose;		/*С������ǰ״̬��λ*/
        }
    }

    PF_CopyDataBytes(&GStr_BackLightAlarm.A0_Flag, &V_ucBackLightAlarmTemp[C_Judge_StartBuffer0], C_AlarmTempLength);
    PF_CopyDataBytes(&GStr_Alarmoutput.A0_Flag, &V_ucAlarmOuputTemp[C_Judge_StartBuffer0], C_AlarmTempLength);
    PF_CopyDataBytes(&GStr_BellAlarm.A0_Flag, &V_ucBellAlarmTemp[C_Judge_StartBuffer0], C_AlarmTempLength);

    V_ucBackLightAlarmTemp[0] &= V_ucAlarmModeReturnData[C_BacklightAlarm_ABC0ByteNo];
    V_ucBackLightAlarmTemp[1] &= V_ucAlarmModeReturnData[C_BacklightAlarm_ABC1ByteNo];
    V_ucBackLightAlarmTemp[2] &= V_ucAlarmModeReturnData[C_BacklightAlarm_ABC0ByteNo];
    V_ucBackLightAlarmTemp[3] &= V_ucAlarmModeReturnData[C_BacklightAlarm_ABC1ByteNo];
    V_ucBackLightAlarmTemp[4] &= V_ucAlarmModeReturnData[C_BacklightAlarm_ABC0ByteNo];
    V_ucBackLightAlarmTemp[5] &= V_ucAlarmModeReturnData[C_BacklightAlarm_ABC1ByteNo];
    V_ucBackLightAlarmTemp[6] &= V_ucAlarmModeReturnData[C_BacklightAlarm_T0ByteNo];
    V_ucBackLightAlarmTemp[7] &= V_ucAlarmModeReturnData[C_BacklightAlarm_T1ByteNo];

    V_ucAlarmOuputTemp[0] &= V_ucAlarmModeReturnData[C_Alarmoutput_ABC0ByteNo];
    V_ucAlarmOuputTemp[1] &= V_ucAlarmModeReturnData[C_Alarmoutput_ABC1ByteNo];
    V_ucAlarmOuputTemp[2] &= V_ucAlarmModeReturnData[C_Alarmoutput_ABC0ByteNo];
    V_ucAlarmOuputTemp[3] &= V_ucAlarmModeReturnData[C_Alarmoutput_ABC1ByteNo];
    V_ucAlarmOuputTemp[4] &= V_ucAlarmModeReturnData[C_Alarmoutput_ABC0ByteNo];
    V_ucAlarmOuputTemp[5] &= V_ucAlarmModeReturnData[C_Alarmoutput_ABC1ByteNo];
    V_ucAlarmOuputTemp[6] &= V_ucAlarmModeReturnData[C_Alarmoutput_T0ByteNo];
    V_ucAlarmOuputTemp[7] &= V_ucAlarmModeReturnData[C_Alarmoutput_T1ByteNo];

	V_ucBellAlarmTemp[0] &= V_ucAlarmModeReturnData[C_BellAlarm_ABC0ByteNo];
    V_ucBellAlarmTemp[1] &= V_ucAlarmModeReturnData[C_BellAlarm_ABC1ByteNo];
    V_ucBellAlarmTemp[2] &= V_ucAlarmModeReturnData[C_BellAlarm_ABC0ByteNo];
    V_ucBellAlarmTemp[3] &= V_ucAlarmModeReturnData[C_BellAlarm_ABC1ByteNo];
    V_ucBellAlarmTemp[4] &= V_ucAlarmModeReturnData[C_BellAlarm_ABC0ByteNo];
    V_ucBellAlarmTemp[5] &= V_ucAlarmModeReturnData[C_BellAlarm_ABC1ByteNo];
    V_ucBellAlarmTemp[6] &= V_ucAlarmModeReturnData[C_BellAlarm_T0ByteNo];
    V_ucBellAlarmTemp[7] &= V_ucAlarmModeReturnData[C_BellAlarm_T1ByteNo];

    for(V_uci = 0;V_uci < 2;V_uci ++)
    {
        if(V_uci == 0)/*С��������*/
        {
            pV_ucAlarmTemp = &V_ucBellAlarmTemp[0];
            pV_ucHstateTemp = &GV_ucBellAlarm_Hstate[0];

            V_ucType = C_AlarmSign;
            V_ucDisMode = C_TwinkleDisplay;
        }
        else if(V_uci == 1)/*�������*/
        {
            pV_ucAlarmTemp = &V_ucAlarmOuputTemp[0];
            pV_ucHstateTemp = &GV_ucAlarmoutput_Hstate[0];

            V_ucType = C_WarnOutPut;
            V_ucDisMode = C_AlwaysDisplay;
        }
        else/*�����*/
        {
            pV_ucAlarmTemp = &V_ucBackLightAlarmTemp[0];
            pV_ucHstateTemp = &GV_ucBackLightAlarm_Hstate[0];

            V_ucType = C_BackLED;
            V_ucDisMode = C_AlwaysDisplay;
        }
        if(PF_Campare_Data(pV_ucAlarmTemp, pV_ucHstateTemp, C_AlarmTempLength)!=C_Equal)
        {
            Str_Event_DisplayMsg.PowerFlag = C_PowerOn;
            Str_Event_DisplayMsg.SourceAddr = C_Msg_PowerNetworkMonitoring;
            Str_Event_DisplayMsg.DerictAddr = C_Msg_Display;
            Str_Event_DisplayMsg.Length = 4;
            V_ucDisplayBuffer[C_DisplayMsgPT1] = Pt_DisplayStatus;
            V_ucDisplayBuffer[C_DisplayMsgTime1H] = 0xFF;			/*��˸ʱ�䣬��ģ�鲻����������ʾ�������ճ���ʱ��FF������*/
            V_ucDisplayBuffer[C_DisplayMsgTime1L] = 0xFF;
            if(PF_Campare_Data(pV_ucAlarmTemp, &V_ucBufferNull[0], C_AlarmTempLength) == C_Equal)							/*��ǰ״̬Ϊ0��ȡ������*/
            {
                V_ucDisplayBuffer[C_DisplayMsgType1] = C_NotDisplay|C_AlarmSign;
                Str_Event_DisplayMsg.Parameter=&V_ucDisplayBuffer[C_DisplayMsgPT1];
                InF_WriteMessege(&Str_Event_DisplayMsg);/*����Ϣ*/
            }
            else
            {
                PF_Buffer8ToUlong64(&pV_ucAlarmTemp[0], &V_ucAlarmCompareTemp, C_AlarmTempLength);
                PF_Buffer8ToUlong64(&pV_ucHstateTemp[0], &V_ucAlarmHstateCompareTemp, C_AlarmTempLength);
                for(V_ucBitNo = C_NULL;V_ucBitNo < C_AlarmTempBitLength;V_ucBitNo ++)
                {
                    V_uc1ByteAlarmTemp = (V_ucAlarmCompareTemp>>V_ucBitNo)&C_Bit0_Start;
                    V_uc1ByteAlarmHstateTemp = (V_ucAlarmHstateCompareTemp>>V_ucBitNo)&C_Bit0_Start;
                    if( (V_uc1ByteAlarmTemp == C_CurrentBitAlarmHappen)
                       && (V_uc1ByteAlarmHstateTemp == C_NULL) )
                    {
                        V_ucSendMessageTemp = C_SendAlarmMessage;
                        break;
                    }
                }
                if(V_ucSendMessageTemp == C_SendAlarmMessage)
                {
                    V_ucDisplayBuffer[C_DisplayMsgType1] = V_ucDisMode | V_ucType;
                    Str_Event_DisplayMsg.Parameter = &V_ucDisplayBuffer[C_DisplayMsgPT1];
                    InF_WriteMessege(&Str_Event_DisplayMsg);/*����Ϣ*/
                    V_ucSendMessageTemp = C_NULL;             /*��Ϣ��ʶ��0*/
                }
            }
            PF_CopyDataBytes(&pV_ucAlarmTemp[0], &pV_ucHstateTemp[0], C_AlarmTempLength);
        }
        else if(V_uci == 1)/*���������Ҫ���Ӵ���*/
        {
            if(V_ucAlarmOuputTemp[6] &= 0x08)
            {
                if(GV_ucDirectionExchange == ReversecurrentHappen)
                {
                    Str_Event_DisplayMsg.PowerFlag = C_PowerOn;
                    Str_Event_DisplayMsg.SourceAddr = C_Msg_PowerNetworkMonitoring;
                    Str_Event_DisplayMsg.DerictAddr = C_Msg_Display;
                    Str_Event_DisplayMsg.Length = 4;
                    V_ucDisplayBuffer[C_DisplayMsgTime1H] = 0xFF;			/*��˸ʱ�䣬��ģ�鲻����������ʾ�������ճ���ʱ��FF������*/
                    V_ucDisplayBuffer[C_DisplayMsgTime1L] = 0xFF;
                    V_ucDisplayBuffer[C_DisplayMsgPT1] = Pt_DisplayStatus;
                    V_ucDisplayBuffer[C_DisplayMsgType1] = C_AlwaysDisplay | C_WarnOutPut;
                    Str_Event_DisplayMsg.Parameter = &V_ucDisplayBuffer[C_DisplayMsgPT1];
                    InF_WriteMessege(&Str_Event_DisplayMsg);/*����Ϣ*/
                    GV_ucDirectionExchange = C_NULL;
                }
            }
        }
    }
}
/***********************************************************************************
����ԭ�ͣ�void SF_PowerSupplyType(void)
�����������жϵ�ǰϵͳ�������ͣ��õ������״̬��
�����������
�����������
���ز�������
����˵����
���û��ƣ�ÿ�����
��    ע��
***********************************************************************************/
void SF_PowerSupplyType(void)
{
    uchar8  V_ucJudgeBuffer1[C_Judge_10BufferLength];
    ushort16 V_usBufferLength1 = C_Judge_10BufferLength, V_usEncode;

    if(InF_GetData_ObjectManage(CMeter_Work_State3, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode)==C_OK)/*�������״̬��3*/
    {
        V_usBufferLength1 = CLAuxi_Power_Sign;
        if(InF_GetData_ObjectManage(CAuxi_Power_Sign, &V_ucJudgeBuffer1[C_Judge_StartBuffer2], &V_usBufferLength1, &V_usEncode)==C_OK)/*������Դ����*/
        {
            if(V_ucJudgeBuffer1[C_Judge_StartBuffer2]==C_ACPowerFail)/*���и�����Դ*/
            {
                if(InF_GetPeripheralStatus(C_CheckAuPower)==C_Invalid)/*������Դ�е�*/
                {/*������Դ����*/
                    V_ucJudgeBuffer1[C_Judge_StartBuffer0]&=C_Bit2_End;
                    V_ucJudgeBuffer1[C_Judge_StartBuffer0]|=C_Bit1_Start;/*������Դ����*/
                }
                else
                {
                    V_ucJudgeBuffer1[C_Judge_StartBuffer0]&=C_Bit_MainPower;/*����Դ����*/
                }
            }
            else
            {
                V_ucJudgeBuffer1[C_Judge_StartBuffer0]&=C_Bit_MainPower;/*����Դ����*/
            }
            InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State3, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag);
        }
    }
}

/***********************************************************************************
����ԭ�ͣ�void SF_WR_Meter_Work_State1(void)
����������ʱ�ӹ����õ������״̬��1
�����������
�����������
���ز����� ��
����˵����ÿ���ж�ʱ�ӹ���״̬���������״̬��bit15����������1��δ������0��
���û��ƣ�ÿ�����
��    ע��
***********************************************************************************/
void SF_WR_Meter_Work_State1(void)
{
	uchar8 V_ucBuffer[2], V_ucData = C_RTC_OK;
	ushort16 V_uslen, V_usEncode;

	/*�����ݲ�ʱ�ӹ���״̬*/
	V_uslen = CLClock_FaultState;
	if( InF_GetData_ObjectManage(CClock_FaultState, &V_ucData, &V_uslen, &V_usEncode) != C_OK )
	{
		return;
	}
	/*�������ݲ�ʱ�ӹ���״̬��־�����ϻ����������ȴ����ݲ����ˢ�º���д*/
	V_uslen = CLMeter_Work_State1;
	if(InF_GetData_ObjectManage(CMeter_Work_State1, V_ucBuffer, &V_uslen, &V_usEncode) == C_OK)
	{
        if(V_ucData == C_RTC_OK)
	    {
		    V_ucBuffer[1] &= ~C_RTCERR_MeterWorkState;
	    }
	    else
	    {
		    V_ucBuffer[1] |= C_RTCERR_MeterWorkState;
	    }
	    InF_Write_Data(C_Msg_Dispatch, CMeter_Work_State1, V_ucBuffer, CLMeter_Work_State1, C_W_SafeFlag);
    }
    else
    {
      return;
    }
}
/*******************************************************************************
����ԭ�ͣ�void SF_MeterStatus_Judgemsg(void)
�����������õ������״̬��
�����������
�����������
���ز�������
����λ�ã�ÿ�����
��    ע��
*******************************************************************************/
void SF_MeterStatus_Judgemsg(void)
{
    uchar8 V_ucMeter_WorkState1Temp[C_MeterWorkState_Length] = {C_NULL, C_NULL};
    uchar8 V_ucMeter_WorkState4Temp[C_MeterWorkState_Length] = {C_NULL, C_NULL};
    uchar8 V_ucMeter_WorkState5Temp[C_MeterWorkState_Length] = {C_NULL, C_NULL};
    uchar8 V_ucMeter_WorkState6Temp[C_MeterWorkState_Length] = {C_NULL, C_NULL};
    uchar8 V_ucMeter_WorkState7Temp[C_MeterWorkState_Length] = {C_NULL, C_NULL};
    uchar8 V_ucEventNo, *pV_ucMeterNo = C_NULL;
	ushort16 V_usLen, V_usEncode;

    SF_PowerSupplyType( );		/*���ܱ�������*/

	for( V_ucEventNo = C_TotalVoltageLoseEventNo; V_ucEventNo <= C_MeterFaEventNo; V_ucEventNo++)
    {
		if(CommunicateEventClearTable[V_ucEventNo].P_State != 0)
		{
			if( ( V_ucEventNo == C_AFailcurrentEventNo )
			 || ( V_ucEventNo == C_BFailcurrentEventNo )
			 || ( V_ucEventNo == C_CFailcurrentEventNo )
			 || ( V_ucEventNo == C_SUnbanlanceCurrentEventNo )
			 || ( V_ucEventNo == C_OpenMeterCoverEventNo )
			 || ( V_ucEventNo == C_OpenTerminalCoverEventNo ) )
			{
				if(CommunicateEventClearTable[V_ucEventNo].P_State == CMeter_Work_State4)
				{
					pV_ucMeterNo = &V_ucMeter_WorkState4Temp[1];
				}

				if(CommunicateEventClearTable[V_ucEventNo].P_State == CMeter_Work_State5)
				{
					pV_ucMeterNo = &V_ucMeter_WorkState5Temp[1];
				}

				if(CommunicateEventClearTable[V_ucEventNo].P_State == CMeter_Work_State6)
				{
					pV_ucMeterNo = &V_ucMeter_WorkState6Temp[1];
				}

				if(CommunicateEventClearTable[V_ucEventNo].P_State == CMeter_Work_State7)
				{
					pV_ucMeterNo = &V_ucMeter_WorkState7Temp[1];
				}
			}
			else if(V_ucEventNo == C_MeterFaEventNo)
			{
				if(CommunicateEventClearTable[V_ucEventNo].P_State == CMeter_Work_State1)
				{
					V_usLen = CLMeter_Work_State1;
					if( InF_GetData_ObjectManage(CMeter_Work_State1, V_ucMeter_WorkState1Temp, &V_usLen, &V_usEncode) == C_OK )
					{
						pV_ucMeterNo = &V_ucMeter_WorkState1Temp[0];
					}	/*else ����ֵΪNUll*/
				}
			}
			else
			{
				if(CommunicateEventClearTable[V_ucEventNo].P_State == CMeter_Work_State4)
				{
					pV_ucMeterNo = &V_ucMeter_WorkState4Temp[0];
				}

				if(CommunicateEventClearTable[V_ucEventNo].P_State == CMeter_Work_State5)
				{
					pV_ucMeterNo = &V_ucMeter_WorkState5Temp[0];
				}

				if(CommunicateEventClearTable[V_ucEventNo].P_State == CMeter_Work_State6)
				{
					pV_ucMeterNo = &V_ucMeter_WorkState6Temp[0];
				}

				if(CommunicateEventClearTable[V_ucEventNo].P_State == CMeter_Work_State7)
				{
					pV_ucMeterNo = &V_ucMeter_WorkState7Temp[0];
				}

			}
			if(pV_ucMeterNo == C_NULL)
			{
				return;
			}
			if(GV_ucEvent_Hstate[V_ucEventNo] == C_Happen_EventState)
			{
				*pV_ucMeterNo |= CommunicateEventClearTable[V_ucEventNo].V_Happen;
			}
			else
			{
				if(V_ucEventNo==C_OverReverseActiveEventNo)
				{
					if( ( GV_ucEvent_Hstate[C_OverForwardActiveEventNo] == C_Happen_EventState)
					 || ( GV_ucEvent_Hstate[C_1OverIdleDemandEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_2OverIdleDemandEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_3OverIdleDemandEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_4OverIdleDemandEventNo] == C_Happen_EventState ) )
					{
						continue;
					}
				}
				if(V_ucEventNo == C_OverForwardActiveEventNo)
				{
					if( ( GV_ucEvent_Hstate[C_OverReverseActiveEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_1OverIdleDemandEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_2OverIdleDemandEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_3OverIdleDemandEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_4OverIdleDemandEventNo] == C_Happen_EventState ) )
					{
						continue;
					}
				}
				if(V_ucEventNo == C_1OverIdleDemandEventNo)
				{
					if( ( GV_ucEvent_Hstate[C_OverForwardActiveEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_OverReverseActiveEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_2OverIdleDemandEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_3OverIdleDemandEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_4OverIdleDemandEventNo] == C_Happen_EventState ) )
					{
						continue;
					}
				}
				if(V_ucEventNo == C_2OverIdleDemandEventNo)
				{
					if( ( GV_ucEvent_Hstate[C_OverForwardActiveEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_OverReverseActiveEventNo] == C_Happen_EventState)
					 || ( GV_ucEvent_Hstate[C_1OverIdleDemandEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_3OverIdleDemandEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_4OverIdleDemandEventNo] == C_Happen_EventState ) )
					{
						continue;
					}
				}
				if(V_ucEventNo == C_3OverIdleDemandEventNo)
				{
					if( ( GV_ucEvent_Hstate[C_OverForwardActiveEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_OverReverseActiveEventNo]==C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_1OverIdleDemandEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_2OverIdleDemandEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_4OverIdleDemandEventNo] == C_Happen_EventState ) )
					{
						continue;
					}
				}
				if(V_ucEventNo == C_4OverIdleDemandEventNo)
				{
					if( ( GV_ucEvent_Hstate[C_OverForwardActiveEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_OverReverseActiveEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_1OverIdleDemandEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_2OverIdleDemandEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_3OverIdleDemandEventNo] == C_Happen_EventState ) )
					{
						continue;
					}
				}
				*pV_ucMeterNo &= CommunicateEventClearTable[V_ucEventNo].V_End;
			}
		}
    }
    InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State1, &V_ucMeter_WorkState1Temp[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag);   /*�������״̬��1��ֵ*/
    InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State4, &V_ucMeter_WorkState4Temp[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag);   /*�������״̬��4��ֵ*/
    InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State5, &V_ucMeter_WorkState5Temp[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag);   /*�������״̬��5��ֵ*/
    InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State6, &V_ucMeter_WorkState6Temp[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag);   /*�������״̬��6��ֵ*/
    InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State7, &V_ucMeter_WorkState7Temp[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag);   /*�������״̬��7��ֵ*/
    SF_WR_Meter_Work_State1();
}

/*******************************************************************************
����ԭ�ͣ�void Inf_PowerupEventrestore(void)
�����������ϵ��¼���¼ģ���ʼ��
���������
���������
���ز�����
����˵�����Ե͹������¼�״̬�����жϣ������ϵ���Ҫ�ָ����¼�
���û��ƣ��ϵ��ʼ��ʱ����
��    ע��
*******************************************************************************/
void Inf_PowerupEventrestore(void)
{
	uchar8  V_ucJudgeBuffer1[C_Judge_20BufferLength] = {0};			/*�ϵ�ʱ��*/
	uchar8  V_ucJudgeBuffer3[C_Judge_20BufferLength] = {0};			/*�м��������*/
	uchar8  V_ucJudgeBuffer4[C_Judge_20BufferLength] = {0};			/*�͹���ʱ�仯��*/
	ushort16  V_usBufferLength1 = C_Judge_20BufferLength, V_usEncode;
	uchar8  V_ucEventNo = 0, V_ucSymbolNo = 0, V_ucAlarmNo = 0;
	ulong32 V_ulAddTimeTemp = 0, V_ulSubSec = 0, V_ulAddTime_H = 0;			/*�ۼ�ʱ�������ʱ����*/
	uchar8  V_ucReturnData = C_Error;
	uchar8  V_ucDataBuff[300] = {0};
	ushort16 V_usDataLen = 0, V_usOffset = 0;
	uchar8  V_ucEvent_Flag = 0;
	uchar8  V_ucPowerOnTimeTemp[CLDate_Week_Time] = {0};
	uchar8  V_ucV_ucEventState = 0;
	uchar8  V_uci, V_ucEvtNo, V_ucMsg;
    Str_CoverRecord_Type *pStr_strCoverRecord;

	if(InF_GetData_ObjectManage(CDate_Time, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) == C_OK)		/*��ϵͳ��ǰʱ��*/
	{
		PF_CopyDataBytes_698( V_ucJudgeBuffer1, V_ucPowerOnTimeTemp, CLDate_Week_Time );

		/*��Դ�쳣�ϵ��ʼ��*/
  		if( SF_Str_CheckCRC( C_PowerAbnormalEventNo ) == C_OK )
  		{
			/*��Դ�쳣CRC��ȷ������Ϊȫ0������������*/
			if(GStr_PowerabnormalStr.MeterState == C_Happen_EventMsg)
			{
				V_usBufferLength1 = CLPowerFa_Degree;
				InF_GetData_ObjectManage(CPowerFa_Degree, V_ucDataBuff, &V_usBufferLength1, &V_usEncode);							/*���¼����*/
				V_usOffset += 4;

				PF_CopyDataBytes(GStr_PowerabnormalStr.Time, &V_ucDataBuff[V_usOffset], C_EventTimeLength);	/*���¼�����ʱ�䣬����ʱ��Ϊ00000000000000*/
				V_usOffset += 7;
				V_usOffset += 7;
				V_usOffset += 1;
                V_usOffset += CLEventReport;/*�����ϱ�״̬ƫ��*/

				V_usDataLen = 300 - V_usOffset;		/*ʣ��buff����*/
				V_ucEvent_Flag = 0x01;
				if( Inf_GetRecordData(&V_ucDataBuff[V_usOffset], &V_usDataLen, CPowerFa_OADTab, V_ucEvent_Flag) == C_OK )							/*��ȡ����OAD����*/
				{
					V_usOffset += V_usDataLen;		/*�����ܳ���*/
					if( InF_Write_Data(C_Msg_PowerNetworkMonitoring, CPowerFa_Note_1, V_ucDataBuff, V_usOffset, C_W_SafeFlag) == C_OK )		/*�¼�����д����*/
					{
						Inf_EventReport_HP( C_PowerAbnormalEventNo, C_Happen_EventReport );
                        InF_ActiveReportSetting( ActiveReportTable[C_PowerAbnormalEventNo] );
					}

					V_usOffset = 11;
					PF_CopyDataBytes( &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucDataBuff[V_usOffset], C_EventTimeLength );			/*���¼�����ʱ��*/
					V_usOffset += 7;
					V_usOffset += 1;
                    V_usOffset += CLEventReport;/*�����ϱ�״̬ƫ��*/
					V_usDataLen = 300 - V_usOffset;		/*ʣ��buff����*/
					V_ucEvent_Flag = 0x02;
					if( Inf_GetRecordData( &V_ucDataBuff[V_usOffset], &V_usDataLen, CPowerFa_OADTab, V_ucEvent_Flag ) == C_OK )				/*��ȡ����OAD����*/
					{
						V_usOffset += V_usDataLen;		/*�����ܳ���*/
						if(InF_Write_Data(C_Msg_PowerNetworkMonitoring, CPowerFa_Note_1 + 0x00000001, V_ucDataBuff, V_usOffset, C_W_SafeFlag) == C_OK)	/*�¼�����д����*/
						{
							Inf_EventReport_HP(C_PowerAbnormalEventNo, C_End_EventReport);
						}
					}

					PF_CopyDataBytes( GStr_PowerabnormalStr.Time, &V_ucJudgeBuffer4[C_Judge_StartBuffer0], C_EventTimeLength );
					if( PF_TimeSub_Min_698( &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer4[C_Judge_StartBuffer0], &V_ulAddTimeTemp) != C_LessThan )
					{
						SF_Sub_Sec(V_ucJudgeBuffer1[C_Judge_StartBuffer0], V_ucJudgeBuffer4[C_Judge_StartBuffer0], &V_ulSubSec);
						V_ulAddTimeTemp *= 60;
						V_ulAddTimeTemp += V_ulSubSec;

						V_usBufferLength1 = 20;
						if( InF_GetData_ObjectManage( CPowerFa_Time, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_usBufferLength1 , &V_usEncode) == C_OK )
						{
							PF_BufferXToUlong32( V_ucJudgeBuffer3, &V_ulAddTime_H, C_AddTime_Length );		/*תHEX*/
							V_ulAddTimeTemp += V_ulAddTime_H;
							PF_Ulong32ToBufferX( &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_ulAddTimeTemp, C_AddTime_Length );
							InF_Write_Data( C_Msg_PowerNetworkMonitoring, CPowerFa_Time, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_AddTime_Length, C_W_SafeFlag );		/*�¼��ۼ�ʱ��д����*/
						}
					}
				}
				SF_Str_Clear(C_PowerAbnormalEventNo);				/*����*/
				GStr_PowerabnormalStr.MeterState=C_Null_EventMsg;		/*�͹���״̬���޶���*/
				SF_Str_CalCRC(C_PowerAbnormalEventNo);				/*�͹��Ľṹ����CRC*/
			}
  		}
  		else
		{
			SF_Str_Clear(C_PowerAbnormalEventNo);				/*����*/
			GStr_PowerabnormalStr.MeterState=C_Null_EventMsg;		/*�͹���״̬���޶���*/
			SF_Str_CalCRC(C_PowerAbnormalEventNo);				/*�͹��Ľṹ����CRC*/
		}

		GV_ucEvent_Hstate[C_PowerAbnormalEventNo] = C_End_EventState;				/*��Դ�쳣����*/
        /*����ǺͿ���ť�ǳ�ʼ���ϲ�����*/
        for(V_uci = 0;V_uci < 2;V_uci ++)
        {
            if(V_uci == 0)/*����ǳ�ʼ��*/
            {
                V_ucEvtNo = C_OpenMeterCoverEventNo;
                V_ucMsg = C_OpenMeterCoverLowPower;
                pStr_strCoverRecord = &GStr_OpenMeterCoverStr;
            }
            else/*����ť�ǳ�ʼ��*/
            {
                V_ucEvtNo = C_OpenTerminalCoverEventNo;
                V_ucMsg = C_OpenTerminalCoverLowPower;
                pStr_strCoverRecord = &GStr_OpenTerminalCoverStr;

                PF_CopyDataBytes_698( V_ucPowerOnTimeTemp, V_ucJudgeBuffer1, CLDate_Week_Time );
            }

            if( SF_Str_CheckCRC( V_ucEvtNo ) == C_OK )
            {
                V_usBufferLength1 = CLEnter_LowPower_Time;
                InF_GetData_ObjectManage( CEnter_LowPower_Time, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_usBufferLength1 , &V_usEncode);		/*����͹���ʱ��*/

                uchar8 TempFlag2 = C_OK;
                if( pStr_strCoverRecord->OpenCoverState == C_LowPowerHappen_EventMsg )
                {
                    PF_CopyDataBytes(pStr_strCoverRecord->HappenTime, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_EventTimeLength);
                    SF_AppendEventMessageLowPower(V_ucMsg, C_Happen_EventMsg);						/*�����¼�����д��Ϣ*/
                    GV_ucEvent_Hstate[V_ucEvtNo] = C_Happen_EventState;									/*��ʷ״̬��ֵ*/
                    TempFlag2 = C_Error;
                }

                if(pStr_strCoverRecord->CloseCoverState == C_LowPowerEnd_EventMsg)
                {
                    PF_CopyDataBytes(pStr_strCoverRecord->EndTime, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_EventTimeLength);
                    SF_AppendEventMessageLowPower(V_ucMsg, C_End_EventMsg);						/*�����¼�����д��Ϣ*/
                    TempFlag2 = C_Error;
                }

                if(TempFlag2 == C_OK)
                {
                    if(SF_Judge_EventIntegrity(V_ucEvtNo) == C_Happen_EventState)
                    {
                        GV_ucEvent_Hstate[V_ucEvtNo] = C_Happen_EventState;							/*��ʷ״̬��ֵ*/
                    }
                    else
                    {
                        GV_ucEvent_Hstate[V_ucEvtNo] = C_End_EventState;								/*��ʷ״̬��ֵ*/
                    }
                }

                if( (TempFlag2 == C_Error) || ( SF_Judge_EventIntegrity(V_ucEvtNo) == C_Happen_EventState ) )
                {
                    if( ( PF_TimeSub_Min_698(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_ulAddTimeTemp) != C_LessThan )
                        && ( InF_GetEnterLowPowerTimerUpdateFlag() == C_OK ) )
                    {
                            SF_Sub_Sec(V_ucJudgeBuffer1[C_Judge_StartBuffer0], V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_ulSubSec);
                            V_ulAddTimeTemp *= 60;
                            V_ulAddTimeTemp += V_ulSubSec;

                            PF_BufferXToUlong32(pStr_strCoverRecord->AddTime, &V_ulAddTime_H, C_AddTime_Length);
                            V_ulAddTime_H += V_ulAddTimeTemp;
                            PF_Ulong32ToBufferX(pStr_strCoverRecord->AddTime, &V_ulAddTime_H, C_AddTime_Length);
                            SF_Str_CalCRC(V_ucEvtNo);				/*�͹��Ľṹ����CRC*/
                    }
                }
            }
            else
            {
                SF_Str_Clear(V_ucEvtNo);						/*����*/
                pStr_strCoverRecord->OpenCoverState=C_Null_EventMsg;			/*�͹��Ŀ���״̬���޶���*/
                pStr_strCoverRecord->CloseCoverState=C_Null_EventMsg;			/*�͹���״̬�ϸǸ��޶���*/
                SF_Str_CalCRC(V_ucEvtNo);						/*�͹��Ľṹ����CRC*/
            }
        }
		/*ȫʧѹ�¼��ϵ��ʼ��*/
		PF_CopyDataBytes_698(V_ucPowerOnTimeTemp, V_ucJudgeBuffer1, CLDate_Week_Time);
		if( SF_Str_CheckCRC(C_TotalVoltageLoseEventNo) == C_OK )
		{
			if(GStr_TotalvoltageloseStr.MeterState == C_Happen_EventMsg)
			{
				PF_CopyDataBytes(GStr_TotalvoltageloseStr.Time, &V_ucJudgeBuffer4[C_Judge_StartBuffer0], C_EventTimeLength);

				if( PF_TimeSub_Min_698(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer4[C_Judge_StartBuffer0], &V_ulAddTimeTemp) != C_LessThan )
				{
					SF_Sub_Sec(V_ucJudgeBuffer1[C_Judge_StartBuffer0], V_ucJudgeBuffer4[C_Judge_StartBuffer0], &V_ulSubSec);
					V_ulAddTimeTemp *= 60;
					V_ulAddTimeTemp += V_ulSubSec;

					PF_Ulong32ToBufferX(GStr_TotalvoltageloseStr.AddTime, &V_ulAddTimeTemp, C_AddTime_Length);
					SF_AppendEventMessageLowPower(C_TotalVoltageLoseEventNo, C_Happen_EventMsg);						/*�����¼�����д��Ϣ*/
					SF_Str_CalCRC(C_TotalVoltageLoseEventNo);					/*�͹��Ľṹ����CRC*/
				}

				GV_ucEvent_Hstate[C_TotalVoltageLoseEventNo]=C_Happen_EventState;	/*��ʷ״̬��ֵ*/
			}
			else
			{
				if(GStr_TotalvoltageloseStr.MeterState == C_End_EventMsg)
				{
					PF_BufferXToUlong32(GStr_TotalvoltageloseStr.AddTime, &V_ulAddTimeTemp, C_AddTime_Length);
					V_ulAddTimeTemp += 60;		/*��60*/
					PF_Ulong32ToBufferX(GStr_TotalvoltageloseStr.AddTime, &V_ulAddTimeTemp, C_AddTime_Length);
					SF_Str_CalCRC(C_TotalVoltageLoseEventNo);		/*����CRC*/
					SF_AppendEventMessageLowPower(C_TotalVoltageLoseEventNo, C_End_EventMsg);		/*�����¼�����д��Ϣ*/
					GV_ucEvent_Hstate[C_TotalVoltageLoseEventNo] = C_End_EventState;		/*��ʷ״̬��ֵ*/
				}
				else
				{
					if( SF_Judge_EventIntegrity( C_TotalVoltageLoseEventNo ) == C_Happen_EventState )		/*��ʷ״̬Ϊ�������ۼ�ʱ����ϵ͹���ʱ��*/
					{
						if( InF_GetEnterLowPowerTimerUpdateFlag() == C_OK )
						{
							V_usBufferLength1 = C_Judge_20BufferLength;		/*V0.2�������ȸ�ֵ*/
							InF_GetData_ObjectManage(CEnter_LowPower_Time, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode);	/*�͹������ۼ�ʱ��*/

							SF_Sub_Sec(V_ucJudgeBuffer1[C_Judge_StartBuffer0], V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_ulSubSec);
							V_ucReturnData = PF_TimeSub_Min_698(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_ulAddTimeTemp);
							V_ulAddTimeTemp *= 60;
							V_ulAddTimeTemp += V_ulSubSec;

							if( (V_ucReturnData == C_GreaterThan) || (V_ucReturnData == C_Equal) )		/*�͹������ۼ�ʱ�����*/
							{
								PF_BufferXToUlong32(GStr_TotalvoltageloseStr.AddTime, &V_ulAddTime_H, C_AddTime_Length);
								V_ulAddTime_H += V_ulAddTimeTemp;
								PF_Ulong32ToBufferX(GStr_TotalvoltageloseStr.AddTime, &V_ulAddTime_H, C_AddTime_Length);
								SF_Str_CalCRC(C_TotalVoltageLoseEventNo);		/*�͹��Ľṹ����CRC*/
							}
						}

						GV_ucEvent_Hstate[C_TotalVoltageLoseEventNo] = C_Happen_EventState;		/*��ʷ״̬��ֵ*/
					}
					else
					{
						GV_ucEvent_Hstate[C_TotalVoltageLoseEventNo] = C_End_EventState;		/*��ʷ״̬��ֵ*/
					}
				}
			}
		}
		else
		{
			SF_Str_Clear(C_TotalVoltageLoseEventNo);			/*����*/
			GStr_TotalvoltageloseStr.MeterState = C_Null_EventMsg;		/*�͹���״̬���޶���*/
			SF_Str_CalCRC(C_TotalVoltageLoseEventNo);			/*�͹��Ľṹ����CRC*/
		}

		/*�����¼��ϵ��ʼ��*/
		if(SF_Str_CheckCRC(C_PowerfailEventNo) == C_OK)
		{
		    V_ucV_ucEventState = SF_Judge_EventIntegrity(C_PowerfailEventNo);		/*��ȡFlash�е����¼�����ʷ״̬*/

			if( (V_ucV_ucEventState == C_Happen_EventState)
				&&(GStr_PowerfailStr.MeterState == C_End_EventMsg) )
		    {
                GStr_PowerfailStr.MeterState = C_End_EventMsg;
		    }
		    else if( (V_ucV_ucEventState != C_Happen_EventState)
				&&(GStr_PowerfailStr.MeterState == C_Happen_EventMsg) )
		    {
                GStr_PowerfailStr.MeterState = C_Happen_EventMsg;
		    }
		    else
		    {
		        GStr_PowerfailStr.MeterState = C_Null_EventMsg;
		    }

			SF_Str_CalCRC(C_PowerfailEventNo);		/*�͹��Ľṹ����CRC*/

			if(GStr_PowerfailStr.MeterState == C_Happen_EventMsg)
			{
				PF_CopyDataBytes(GStr_PowerfailStr.Time, &V_ucJudgeBuffer4[C_Judge_StartBuffer0], C_EventTimeLength);
				if( PF_TimeSub_Min_698(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer4[C_Judge_StartBuffer0], &V_ulAddTimeTemp) != C_LessThan )
				{
					SF_Sub_Sec(V_ucJudgeBuffer1[C_Judge_StartBuffer0], V_ucJudgeBuffer4[C_Judge_StartBuffer0], &V_ulSubSec);
					V_ulAddTimeTemp *= 60;
					V_ulAddTimeTemp += (V_ulSubSec + 3);		/*�˴��ӱ���ʱ��2s�ӳ�ʼ��ʱ��1s*/

					PF_Ulong32ToBufferX(GStr_PowerfailStr.AddTime, &V_ulAddTimeTemp, C_AddTime_Length);
					SF_Str_CalCRC(C_PowerfailEventNo);		/*�͹��Ľṹ����CRC*/
				}

				SF_AppendEventMessageLowPower(C_PowerfailEventNo, C_Happen_EventMsg);		/*�����¼�����д��Ϣ*/
				GV_ucEvent_Hstate[C_PowerfailEventNo] = C_Happen_EventState;					/*��ʷ״̬��ֵ*/
			}
			else
			{
				if(GStr_PowerfailStr.MeterState == C_End_EventMsg)
				{
        			PF_BufferXToUlong32(GStr_PowerfailStr.AddTime, &V_ulAddTimeTemp, C_AddTime_Length);
					V_ulAddTimeTemp += 3;		/*�˴��ӱ���ʱ��3s*/
					PF_Ulong32ToBufferX(GStr_PowerfailStr.AddTime, &V_ulAddTimeTemp, C_AddTime_Length);
					SF_AppendEventMessageLowPower(C_PowerfailEventNo, C_End_EventMsg);		/*�����¼�����д��Ϣ*/
					SF_Str_CalCRC(C_PowerfailEventNo);									/*�͹��Ľṹ����CRC*/
					GV_ucEvent_Hstate[C_PowerfailEventNo] = C_End_EventState;				/*��ʷ״̬��ֵ*/
				}
				else
				{
					if( V_ucV_ucEventState == C_Happen_EventState )
					{
						if( InF_GetEnterLowPowerTimerUpdateFlag() == C_OK )
						{
							V_usBufferLength1 = C_Judge_20BufferLength;
							InF_GetData_ObjectManage(CEnter_LowPower_Time, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode);	/*���͹���ʱ��*/

							SF_Sub_Sec(V_ucJudgeBuffer1[C_Judge_StartBuffer0], V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_ulSubSec);
							V_ucReturnData = PF_TimeSub_Min_698(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_ulAddTimeTemp);
							V_ulAddTimeTemp *= 60;
							V_ulAddTimeTemp += (V_ulSubSec + 3);	/*�˴��ӱ���ʱ��3s*/

							if( (V_ucReturnData == C_GreaterThan) || (V_ucReturnData == C_Equal) )	/*�͹������ۼ�ʱ�����*/
							{
								PF_BufferXToUlong32(GStr_PowerfailStr.AddTime, &V_ulAddTime_H, C_AddTime_Length);
								V_ulAddTime_H += V_ulAddTimeTemp;
								PF_Ulong32ToBufferX(GStr_PowerfailStr.AddTime, &V_ulAddTime_H, C_AddTime_Length);
								SF_Str_CalCRC(C_PowerfailEventNo);	/*�͹��Ľṹ����CRC*/
							}
						}

						GV_ucEvent_Hstate[C_PowerfailEventNo] = C_Happen_EventState;		/*��ʷ״̬��ֵ*/
					}
#if 0
					else
					{
						GV_ucEvent_Hstate[C_PowerfailEventNo] = C_End_EventState;		/*��ʷ״̬��ֵ*/
					}
#endif
				}
			}
		}
		else
		{
			SF_Str_Clear(C_PowerfailEventNo);				/*����*/
			GStr_PowerfailStr.MeterState = C_Null_EventMsg;		/*�͹���״̬���޶���*/
			SF_Str_CalCRC(C_PowerfailEventNo);				/*�͹��Ľṹ����CRC*/
		}

		/*������Դʧ���ϵ��ʼ��*/
		V_usBufferLength1 = CLAuxi_Power_Sign;
		if(InF_GetData_ObjectManage(CAuxi_Power_Sign, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) == C_OK)	/*��������Դ����*/
		{
			if(V_ucJudgeBuffer3[C_Judge_StartBuffer0] == C_ACPowerFail)		/*��������Դ�ı�*/
			{
				if(SF_Str_CheckCRC(C_ACPowerFailEventNo) == C_OK)			/*�͹���CRC��ȷ*/
				{
					uchar8 TempFlag = C_OK;

					if(GStr_ACPowerFailStr.MeterState == C_Happen_EventMsg)
					{
						SF_AppendEventMessageLowPower(C_ACPowerFailEventNo, C_Happen_EventMsg);	/*�����¼�����д��Ϣ*/
						PF_CopyDataBytes(GStr_ACPowerFailStr.Time, &V_ucJudgeBuffer4[C_Judge_StartBuffer0], C_EventTimeLength);
					}
					else
					{
						if(SF_Judge_EventIntegrity(C_ACPowerFailEventNo) == C_Happen_EventState)	/*��ʷ״̬Ϊ�������ۼ�ʱ����ϵ͹���ʱ��*/
						{
							V_usBufferLength1 = C_Judge_20BufferLength;		/*V0.2�������ȸ�ֵ*/
							InF_GetData_ObjectManage(CEnter_LowPower_Time, &V_ucJudgeBuffer4[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode);	/*����͹���ʱ��*/
						}
						else
						{
							GV_ucEvent_Hstate[C_ACPowerFailEventNo] = C_End_EventState;		/*��ʷ״̬��ֵ*/
							TempFlag = C_Error;
						}
					}

					if(TempFlag == C_OK)
					{
						if(InF_GetEnterLowPowerTimerUpdateFlag() == C_OK)
						{
							SF_Sub_Sec(V_ucJudgeBuffer1[C_Judge_StartBuffer0], V_ucJudgeBuffer4[C_Judge_StartBuffer0], &V_ulSubSec);

							uchar8 V_ucReturnData;
							V_ucReturnData = PF_TimeSub_Min_698(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer4[C_Judge_StartBuffer0], &V_ulAddTimeTemp);
							V_ulAddTimeTemp *= 60;
							V_ulAddTimeTemp += V_ulSubSec;

							if( (V_ucReturnData == C_GreaterThan) || (V_ucReturnData == C_Equal) )		/*�͹������ۼ�ʱ�����*/
							{
								PF_BufferXToUlong32(GStr_ACPowerFailStr.AddTime, &V_ulAddTime_H, C_AddTime_Length);
								V_ulAddTime_H += (V_ulAddTimeTemp + 3);									/*�˴��ӱ���ʱ��2s�ӳ�ʼ��ʱ��1s*/
								PF_Ulong32ToBufferX(GStr_ACPowerFailStr.AddTime, &V_ulAddTime_H, C_AddTime_Length);
								SF_Str_CalCRC(C_ACPowerFailEventNo);								/*�͹��Ľṹ����CRC*/
							}
						}

						GV_ucEvent_Hstate[C_ACPowerFailEventNo] = C_Happen_EventState;					/*��ʷ״̬��ֵ*/
					}
				}
				else
				{
					SF_Str_Clear(C_ACPowerFailEventNo);				/*����*/
					GStr_ACPowerFailStr.MeterState = C_Null_EventMsg;	/*�͹���״̬���޶���*/
					SF_Str_CalCRC(C_ACPowerFailEventNo);			/*�͹��Ľṹ����CRC*/
				}
			}
		}
		else
		{
			SF_Str_Clear(C_ACPowerFailEventNo);						/*����*/
			GStr_ACPowerFailStr.MeterState = C_Null_EventMsg;				/*�͹���״̬���޶���*/
			SF_Str_CalCRC(C_ACPowerFailEventNo);					/*�͹��Ľṹ����CRC*/
		}

		/*ʱ�ӹ����ϵ��ʼ��*/
		PF_CopyDataBytes_698(V_ucPowerOnTimeTemp, V_ucJudgeBuffer1, CLDate_Week_Time);
		if(SF_Str_CheckCRC(C_ClockFaEventNo) == C_OK)
		{
			if( SF_Judge_EventIntegrity(C_ClockFaEventNo) == C_Happen_EventState )		/*��ȡFlash��ʱ�ӹ����¼�����ʷ״̬*/
			{
				GV_ucEvent_Hstate[C_ClockFaEventNo] = C_Happen_EventState;					/*��ʷ״̬��ֵ*/

				V_usBufferLength1 = CLBackTime_OneSec;
				InF_GetData_ObjectManage(CBackTime_OneSec, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode);		/*���籸��ʱ��*/

				if( PF_TimeSub_Min_698(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_ulAddTimeTemp) != C_LessThan )
				{
					SF_Sub_Sec(V_ucJudgeBuffer1[C_Judge_StartBuffer0], V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_ulSubSec);
					V_ucReturnData = PF_TimeSub_Min_698(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_ulAddTimeTemp);
					V_ulAddTimeTemp *= 60;
					V_ulAddTimeTemp += (V_ulSubSec + 3);										/*�˴��ӱ���ʱ��*/

					if( (V_ucReturnData == C_GreaterThan) || (V_ucReturnData == C_Equal) )		/*�͹������ۼ�ʱ�����*/
					{
						PF_BufferXToUlong32(GStr_ClockFaStr.AddTime, &V_ulAddTime_H, C_AddTime_Length);
						V_ulAddTime_H += V_ulAddTimeTemp;
						PF_Ulong32ToBufferX(GStr_ClockFaStr.AddTime, &V_ulAddTime_H, C_AddTime_Length);
						SF_Str_CalCRC(C_ClockFaEventNo);			                	/*�ṹ����CRC*/
					}
				}
			}
			else
			{
				GV_ucEvent_Hstate[C_ClockFaEventNo] = C_End_EventState;		/*��ʷ״̬��ֵ*/
			}
		}
		else
		{
			SF_Str_Clear(C_ClockFaEventNo);								/*����*/
			SF_Str_CalCRC(C_ClockFaEventNo);							/*�ṹ����CRC*/
		}

		for(V_ucEventNo = C_OverForwardActiveEventNo; V_ucEventNo <= C_NeutralCurrentAbnormalEventNo; V_ucEventNo++)
		{
            if(V_ucEventNo == C_ClockFaEventNo)
			{
				continue;
			}

			GV_ucEvent_JudgeTimer[V_ucEventNo] = C_NULL;	 				/*��ʱ������*/
			if( SF_Str_CheckCRC(V_ucEventNo) == C_OK )
			{
				if( SF_Judge_EventIntegrity(V_ucEventNo) == C_Happen_EventState )
				{
					SF_AppendEventMessage(V_ucEventNo, C_End_EventMsg, C_PowerRising);	/*�����¼�����д��Ϣ*/
					GV_ucEvent_Hstate[V_ucEventNo] = C_End_EventState;
				}
			}
			else
			{
				SF_Str_Clear(V_ucEventNo);
				SF_Str_CalCRC(V_ucEventNo);		  /*״̬λû���ã��Ժ��޸ģ���ʷ״̬λ������������Ϊ0*/
			}
		}

		GV_ucReversecurrentTimes = C_NULL;               /*�ϵ��ʼ��/����/�¼��رպ��һ���з��򣬲�����*/
		GV_ucDirectionExchange = C_NULL;

		/******************************�͹����¼���ʱ������*************************************************/
		GV_ucEvent_JudgeTimer[C_TotalVoltageLoseEventNo] = C_NULL;
		GV_ucEvent_JudgeTimer[C_ACPowerFailEventNo] = C_NULL;
		GV_ucEvent_JudgeTimer[C_PowerfailEventNo] = C_NULL;
		GV_ucEvent_JudgeTimer[C_OpenMeterCoverEventNo] = C_NULL;
		GV_ucEvent_JudgeTimer[C_OpenTerminalCoverEventNo] = C_NULL;
		GV_ucEvent_JudgeTimer[C_PowerAbnormalEventNo] = C_NULL;

		/******************************�㶨�ų��¼�*************************************************/
		GV_ucEvent_JudgeTimer[C_MagneticCheckEventNo] = C_NULL;	 				/*��ʱ������*/
		if(SF_Str_CheckCRC(C_MagneticCheckEventNo) == C_OK)
		{
			if(SF_Judge_EventIntegrity(C_MagneticCheckEventNo) == C_Happen_EventState)
			{
				SF_AppendEventMessage(C_MagneticCheckEventNo, C_End_EventMsg, C_PowerRising);	/*�����¼�����д��Ϣ*/
				GV_ucEvent_Hstate[C_MagneticCheckEventNo] = C_End_EventState;
			}
		}
		else
		{
			SF_Str_Clear(C_MagneticCheckEventNo);
			SF_Str_CalCRC(C_MagneticCheckEventNo);		/*״̬λû���ã��Ժ��޸ģ���ʷ״̬λ������������Ϊ0*/
		}
	}
  	else
	{
		for(V_ucEventNo = C_TotalVoltageLoseEventNo; V_ucEventNo <= C_SUnbanlanceCurrentEventNo; V_ucEventNo++)
		{												/*ȫ��*/
			GV_ucEvent_Hstate[V_ucEventNo] = C_End_EventState;	/*�ر�*/
			GV_ucEvent_JudgeTimer[V_ucEventNo] = C_NULL;
			SF_Str_Clear(V_ucEventNo);
			SF_Str_CalCRC(V_ucEventNo);
			/*��ʱ����״̬��û�����㣬��д��Ϣ��ȥ����*/
		}

		GV_ucReversecurrentTimes = C_NULL;                                             		/*�ϵ��ʼ��/����/�¼��رպ��һ���з��򣬲�����*/
		GV_ucDirectionExchange = C_NULL;
	}

	for(V_ucSymbolNo = C_AVoltage_SymbolNO; V_ucSymbolNo < C_EventSymbolLength; V_ucSymbolNo++)		/*�����ϵ��ʼ��*/
	{
		GV_ucEvent_SymbolHstate[V_ucSymbolNo] = 0xff;
	}

	for(V_ucAlarmNo = 0; V_ucAlarmNo < C_AlarmTempLength; V_ucAlarmNo++)                       		/*���������ϵ��ʼ��*/
	{
		GV_ucBackLightAlarm_Hstate[V_ucAlarmNo] = C_NULL;
		GV_ucAlarmoutput_Hstate[V_ucAlarmNo] = C_NULL;
		GV_ucBellAlarm_Hstate[V_ucAlarmNo] = C_NULL;
	}

	SF_SymbolDisplay_Judgemsg();            /*��ʼ������*/
	SF_AlarmDisplay_Judgemsg();             /*��ʼ������*/
	SF_MeterStatus_Judgemsg();
}

/***********************************************************************************
����ԭ�ͣ�void Inf_LowpowerACPowerFail(void)
�����������͹����¸�����Դʧ��
���������
���������
���ز�����
����˵�����жϵ͹����¸�����Դʧ��״̬
���û��ƣ�����͹���ʱ����
��    ע�����˿��ϸǣ������Ľ��͹��Ĳ���CRC;
***********************************************************************************/
void Inf_LowpowerACPowerFail(void)
{
	uchar8		V_ucEventMsg;
	uchar8		V_ucJudgeBuffer1[C_Judge_20BufferLength];
	uchar8		V_ucJudgeBuffer2[C_Judge_20BufferLength];
	ushort16    V_usBufferLength1 = C_Judge_20BufferLength, V_usEncode;

	if(SF_Str_CheckCRC(C_ACPowerFailEventNo) != C_OK)
	{
		SF_Str_Clear(C_ACPowerFailEventNo);
		GStr_ACPowerFailStr.MeterState = C_Null_EventMsg;		/*�͹���״̬���޶���*/
        SF_Str_CalCRC(C_ACPowerFailEventNo);
	}
	if(InF_GetData_ObjectManage(CAuxi_Power_Sign, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode)!=C_OK)/*������Դ����*/
	{
		return;
	}
	if(V_ucJudgeBuffer1[C_Judge_StartBuffer0] != C_ACPowerFail)/*����������Դ��ֱ���˳�*/
	{
		return;
	}
    if(SF_Judge_EventIntegrity(C_ACPowerFailEventNo) == C_Happen_EventState)
    {
        return;
    }
	else if(GStr_ACPowerFailStr.MeterState == C_Happen_EventMsg)
	{
		return;
	}
    else
    {
        V_ucEventMsg=C_Happen_EventMsg;
    }
	V_usBufferLength1 = C_Judge_20BufferLength;/*V0.2�������ȸ�ֵ*/
	if(V_ucEventMsg == C_Happen_EventMsg)
	{
		if(InF_GetData_ObjectManage(CDate_Time, &V_ucJudgeBuffer2[C_Judge_StartBuffer2], &V_usBufferLength1, &V_usEncode) != C_OK)/*��ȡ�¼�����ʱ��, �������ʲô���������˳�*/
		{
			return;
		}
        V_usBufferLength1 = CLMeter_Work_State7;
		if(InF_GetData_ObjectManage(CMeter_Work_State7, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) != C_OK)/*�������״̬��7*/
		{
			return;
		}
		V_ucJudgeBuffer2[C_Judge_StartBuffer0] |= C_Bit4_Start;/*bit4��1, ����0�ĵ�4λ*/
		if(InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State7, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag) != C_OK)/*�������״̬��7д���ݲ�*/
		{																					/*д�������״̬�֣������Ͳ�������*/
			return;
		}/*�����ݳɹ�����д���ݲ㣬д���ݲ�ɹ����ٲ����ṹ��*/
		GStr_ACPowerFailStr.MeterState = C_Happen_EventMsg;													/*�¼�״̬��ֵ*/
		PF_CopyDataBytes(&V_ucJudgeBuffer2[C_Judge_StartBuffer2], GStr_ACPowerFailStr.Time, C_EventTimeLength);/*�¼�����ʱ�̸�ֵ*/
        SF_Str_CalCRC(C_ACPowerFailEventNo);

		GV_ucEvent_Hstate[C_ACPowerFailEventNo] = C_Happen_EventState;/*��ʷ״̬��ֵ���ŵ����д�����������������ʷ״̬��*/
	}
}

/***********************************************************************************
����ԭ�ͣ�void Inf_PowerAbnormal(void)
�����������͹����µ�Դ�쳣
���������
���������
���ز�����
����˵�����жϵ͹����Ƿ��Դ�쳣
���û��ƣ�����͹���1Sʱ����
��    ע��
***********************************************************************************/
void Inf_PowerAbnormal(void)
{
	uchar8		V_ucJudgeBuffer1[C_Judge_20BufferLength];/*�жϷ�ֵ����*/
	uchar8		V_ucJudgeBuffer2[C_Judge_20BufferLength];/*�����ѹ����*/
	ushort16    V_usBufferLength1 = C_Judge_20BufferLength, V_usEncode;
	uchar8		V_ucRelayState;

	if(SF_Str_CheckCRC(C_PowerAbnormalEventNo)!=C_OK)
	{
		SF_Str_Clear(C_PowerAbnormalEventNo);
		GStr_PowerabnormalStr.MeterState=C_Null_EventMsg;	/*�͹���״̬���޶���*/
		SF_Str_CalCRC(C_PowerAbnormalEventNo);
	}
	V_ucRelayState = InF_RelayOpenStatus();	/*�̵���״̬*/
	if(V_ucRelayState != C_EventOK)/*������������բ״̬*/
	{
		return;
	}
	if(InF_GetData_ObjectManage(CVolage_Abnor_Vol, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode)!=C_OK)/*��Դ�쳣�жϵ�ѹ*/
	{
		return;
	}
    V_usBufferLength1 = C_Judge_20BufferLength;/*V0.2�������ȸ�ֵ*/
	if(InF_GetData_ObjectManage(CPhaseFF_Volage, &V_ucJudgeBuffer2[C_JudgeVolage_Buffer1], &V_usBufferLength1, &V_usEncode)!=C_OK)/*�������ѹ*/
	{
		return;
	}
	if( ( (PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeVolage_Buffer1], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_GreaterThan)/*���ֽ��ǵ�ѹ����*/
            && (PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeVolage_Buffer1], &V_ucJudgeBuffer1[C_Judge_StartBuffer2], C_Volage_Length) == C_LessThan) )/*���ֽ��ǵ�ѹ����*/
		|| ( (PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeVolage_Buffer2], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_GreaterThan)
            &&(PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeVolage_Buffer2], &V_ucJudgeBuffer1[C_Judge_StartBuffer2], C_Volage_Length) == C_LessThan) )
		||( ( (PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeVolage_Buffer3], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_GreaterThan)
            &&(PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeVolage_Buffer3], &V_ucJudgeBuffer1[C_Judge_StartBuffer2], C_Volage_Length) == C_LessThan)) ) )
	{
    V_usBufferLength1=C_Judge_20BufferLength;     /*V0.2�������ȸ�ֵ*/
    if(InF_GetData_ObjectManage(CDate_Time, &V_ucJudgeBuffer1[C_Judge_StartBuffer2], &V_usBufferLength1, &V_usEncode)!=C_OK)/*��ȡ�¼�����ʱ��*/
    {
        return;
    }
    GStr_PowerabnormalStr.MeterState = C_Happen_EventMsg;													/*�¼�����״̬��ֵ*/
    PF_CopyDataBytes(&V_ucJudgeBuffer1[C_Judge_StartBuffer2], GStr_PowerabnormalStr.Time, C_EventTimeLength);/*�¼�����ʱ�丳ֵ*/

    SF_Str_CalCRC(C_PowerAbnormalEventNo);
    GV_ucEvent_Hstate[C_PowerAbnormalEventNo] = C_Happen_EventState;				/*��ʷ״̬��ֵ���ŵ����д�����������������ʷ״̬��*/
	}
}

/***********************************************************************************
����ԭ�ͣ�void Inf_LowpowerTotalVoltagelose(void)
�����������͹�����ȫʧѹ
���������
���������
���ز�����
����˵�����͹�����60sʱ�жϵ�ǰ���ܱ�״̬
���û��ƣ�����͹���60Sʱ����
��    ע��
***********************************************************************************/
void Inf_LowpowerTotalVoltagelose(void)
{
	uchar8		V_ucEventMsg;
	uchar8		V_ucJudgeBuffer1[C_Judge_20BufferLength];/*ȫʧѹ����ʱ��������*/
	uchar8		V_ucJudgeBuffer2[C_Judge_20BufferLength];/*��������*/
	ushort16    V_usBufferLength1 = C_Judge_20BufferLength, V_usEncode;

	if(SF_Str_CheckCRC(C_TotalVoltageLoseEventNo) != C_OK)
	{
		SF_Str_Clear(C_TotalVoltageLoseEventNo);
		GStr_TotalvoltageloseStr.MeterState = C_Null_EventMsg;		/*�͹���״̬���޶���*/
		SF_Str_CalCRC(C_TotalVoltageLoseEventNo);
	}
	V_ucEventMsg = SF_Judge_Event_Statechange(C_TotalVoltageLoseEventNo, C_Judge_Time0);/*�ж�ȫʧѹ�Ƿ���*/
	if(V_ucEventMsg == C_Happen_EventMsg)
	{
		V_usBufferLength1 = C_Judge_20BufferLength;
		if(InF_GetData_ObjectManage(CPhaseFF_Curr, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) != C_OK)/*��ȡ�¼���������*/
        {
            return;
        }
		V_usBufferLength1 = C_Judge_20BufferLength; /*V0.2�������ȸ�ֵ*/
		if(InF_GetData_ObjectManage(CDate_Time, &V_ucJudgeBuffer2[C_Judge_StartBuffer2], &V_usBufferLength1, &V_usEncode) != C_OK)/*��ȡ�¼�����ʱ��*/
		{
			return;
		}
		PF_CopyDataBytes(&V_ucJudgeBuffer2[C_Judge_StartBuffer2], GStr_TotalvoltageloseStr.Time, C_EventTimeLength);/*��ȫʧѹ����ʱ�̸�ֵ*/
		PF_CopyDataBytes(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], GStr_TotalvoltageloseStr.NoVoltageCurrent, C_3Curr_Length);/*��ȫʧѹ������ֵ*/

        GStr_TotalvoltageloseStr.MeterState = C_Happen_EventMsg;/*ȫʧѹ�͹���״̬�÷���*/
		SF_Str_CalCRC(C_TotalVoltageLoseEventNo);			/*�͹��Ľṹ����CRC*/

		GV_ucEvent_Hstate[C_TotalVoltageLoseEventNo] = C_Happen_EventState;/*��ʷ״̬��ֵ*/
	}
 	else
 	{
 		if(V_ucEventMsg == C_End_EventMsg)
 		{
			if(InF_GetData_ObjectManage(CDate_Time, &V_ucJudgeBuffer2[C_Judge_StartBuffer2], &V_usBufferLength1, &V_usEncode) != C_OK)/*��ȡ�¼�����ʱ��*/
			{
				return;
			}
			PF_CopyDataBytes(&V_ucJudgeBuffer2[C_Judge_StartBuffer2], GStr_TotalvoltageloseStr.Time, C_EventTimeLength);/*��ȫʧѹ����ʱ�̸�ֵ*/
			GStr_TotalvoltageloseStr.MeterState = C_End_EventMsg;/*ȫʧѹ�͹��Ľṹ��״̬�ý���*/
			SF_Str_CalCRC(C_TotalVoltageLoseEventNo);			/*�͹��Ľṹ����CRC*/

			GV_ucEvent_Hstate[C_TotalVoltageLoseEventNo]=C_End_EventState;/*��ʷ״̬��ֵ*/
 		}
 	}
}
/*******************************************************************************
����ԭ�ͣ� uchar8 Inf_LowpowerPowerFail_No6VBat(void)
���������� �͹����µ��磬û��6V���
���������
���������
���ز����� C_Happen_V_ucEventState������͹��ķ������磬�ϱ���C_NULL�������·����ĵ��磬������ֵ��
����λ��:
��    ע��
*******************************************************************************/
uchar8 Inf_LowpowerPowerFail_No6VBat(void)
{
	uchar8		V_ucJudgeBuffer1[C_Judge_20BufferLength];     /*�¼�����ʱ��*/
	uchar8		V_ucJudgeBuffer2[C_Judge_20BufferLength];		/*�������״̬��7*/
	ushort16    V_usBufferLength1 = C_Judge_20BufferLength, V_usEncode;
    uchar8      V_ucPowerDownHstate = C_NULL, V_ucReturnFlag = C_NULL;

	if(SF_Str_CheckCRC(C_PowerfailEventNo)!=C_OK)
	{
		SF_Str_Clear(C_PowerfailEventNo);
	    GStr_PowerfailStr.MeterState = C_Null_EventMsg;	/*�͹���״̬���޶���*/
		SF_Str_CalCRC(C_PowerfailEventNo);
	}

	V_usBufferLength1 = CLDate_Week_Time;
    if( InF_GetData_ObjectManage( CDate_Time, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) == C_OK)       /*��ȡ�¼�����ʱ��*/
    {
		V_usBufferLength1 = CLMeter_Work_State7;
        if(InF_GetData_ObjectManage(CMeter_Work_State7, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) == C_OK)	/*�������״̬��7*/
		{
            V_ucJudgeBuffer2[C_Judge_StartBuffer0] |= C_Bit5_Start;				/*bit5��1, ����0�ĵ�5λ*/
            if(InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State7, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag) == C_OK)	/*�������״̬��7д���ݲ�*/
            {/*д�������״̬�֣������Ͳ�������*/
                V_ucPowerDownHstate =  Inf_GetPowerDownEventType(C_PowerfailEventNo);     /*������͹���ʱ��ǰ״̬���Ƿ����Ѿ����������ڵ͹����������ϱ�*/
                if(V_ucPowerDownHstate != C_Happen_EventState)                            /*���粻�����Ѿ�����*/
                {
                    V_ucReturnFlag = C_Happen_EventState;                                 /*��ʾ�͹����·������磬���򲻽����µ��������ϱ�*/
                }
                PF_CopyDataBytes(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], GStr_PowerfailStr.Time, C_EventTimeLength);        /*ʱ��ṹ�壬��ֵ*/
                GStr_PowerfailStr.MeterState = C_Happen_EventMsg;                            /*����͹���״̬�÷���*/
                SF_Str_CalCRC(C_PowerfailEventNo);			                            /*�͹��Ľṹ����CRC*/
                GV_ucEvent_Hstate[C_PowerfailEventNo] = C_Happen_EventState;                 /*��ʷ״̬��ֵ*/
            }/*�����ݳɹ�����д���ݲ㣬д���ݲ�ɹ����ٲ����ṹ��*/
		}
    }

    return V_ucReturnFlag;                                                        /*�����Ƿ���Ҫ�ϱ��ı�־*/
}


/*******************************************************************************
����ԭ�ͣ� uchar8 Inf_LowpowerPowerFail(void)
���������� �͹����µ���
���������
���������
���ز����� C_Happen_EventState:�������� ��C_End_V_ucEventState���������磻C_NULL�����ݳ������¼�
����λ�ã�
��    ע�� �͹��ĵ���
*******************************************************************************/
uchar8 Inf_LowpowerPowerFail(void)
{
	uchar8		V_ucEventState = C_NULL, V_ucReturnFlag = C_NULL;
	uchar8		V_ucJudgeBuffer1[C_Judge_20BufferLength];		/*�¼�����ʱ��*/
	uchar8		V_ucJudgeBuffer2[C_Judge_20BufferLength];		/*�������״̬��7*/
	ushort16    V_usBufferLength1 = C_Judge_20BufferLength, V_usEncode;
    uchar8      V_ucPowerDownHstate = C_NULL;

	if(SF_Str_CheckCRC(C_PowerfailEventNo) != C_OK)
	{
		SF_Str_Clear(C_PowerfailEventNo);
	    GStr_PowerfailStr.MeterState = C_Null_EventMsg;	/*�͹���״̬���޶���*/
		SF_Str_CalCRC(C_PowerfailEventNo);
	}
    V_ucPowerDownHstate =  Inf_GetPowerDownEventType(C_PowerfailEventNo);     /*���統ǰ״̬���Ƿ����Ѿ����������ڵ͹����������ϱ�*/
	V_ucEventState = SF_Get_Powerfail_Cstate(C_PowerfailEventNo, GV_ucEvent_Hstate[C_PowerfailEventNo]);	/*�жϵ����Ƿ���*/
	if(V_ucEventState == C_Happen_EventState)
	{
		if(InF_GetData_ObjectManage(CDate_Time, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) != C_OK)		/*��ȡ�¼�����ʱ��*/
		{
			return V_ucReturnFlag;
		}
        V_usBufferLength1 = CLMeter_Work_State7;
		if(InF_GetData_ObjectManage(CMeter_Work_State7, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) != C_OK)	/*�������״̬��7*/
		{
			return V_ucReturnFlag;
		}
		V_ucJudgeBuffer2[C_Judge_StartBuffer0] |= C_Bit5_Start;				/*bit5��1, ����0�ĵ�5λ*/
		if(InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State7, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag) != C_OK)	/*�������״̬��7д���ݲ�*/
		{																					/*д�������״̬�֣������Ͳ�������*/
			return V_ucReturnFlag;
		}/*�����ݳɹ�����д���ݲ㣬д���ݲ�ɹ����ٲ����ṹ��*/
		PF_CopyDataBytes(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], GStr_PowerfailStr.Time, C_EventTimeLength);			/*ʱ��ṹ�壬��ֵ*/
		GStr_PowerfailStr.MeterState = C_Happen_EventMsg;							/*ȫʧѹ�͹���״̬�÷���*/
		SF_Str_CalCRC(C_PowerfailEventNo);							/*�͹��Ľṹ����CRC*/
		GV_ucEvent_Hstate[C_PowerfailEventNo] = C_Happen_EventState;		/*��ʷ״̬��ֵ*/
        if(V_ucPowerDownHstate != C_Happen_EventState)
        {
            V_ucReturnFlag = V_ucEventState;
        }
	}
 	else
 	{
 		if(V_ucEventState == C_End_EventState)
 		{
			if(InF_GetData_ObjectManage(CDate_Time, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) != C_OK)		/*��ȡ�¼�����ʱ��*/
			{
				return V_ucReturnFlag;
			}
            V_usBufferLength1 = CLMeter_Work_State7;
			if(InF_GetData_ObjectManage(CMeter_Work_State7, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) != C_OK)	/*�������״̬��7*/
			{
				return V_ucReturnFlag;
			}
			V_ucJudgeBuffer2[C_Judge_StartBuffer0] &= C_Bit5_End;				/*bit5��0, ����1�ĵ�2λ*/
			if(InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State7, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag) != C_OK)	/*�������״̬��7д���ݲ�*/
			{																		/*д�������״̬�֣������Ͳ�������*/
				return V_ucReturnFlag;
			}/*�����ݳɹ�����д���ݲ㣬д���ݲ�ɹ����ٲ����ṹ��*/
			PF_CopyDataBytes(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], GStr_PowerfailStr.Time, C_EventTimeLength);		/*�¼��ṹ�壬ʱ�丳ֵ*/
			GStr_PowerfailStr.MeterState = C_End_EventMsg;						/*����͹��Ľṹ��״̬�ý���*/
			SF_Str_CalCRC(C_PowerfailEventNo);								/*�͹��Ľṹ����CRC*/
			GV_ucEvent_Hstate[C_PowerfailEventNo] = C_End_EventState;				/*��ʷ״̬��ֵ*/
            if(V_ucPowerDownHstate == C_Happen_EventState)
            {
                V_ucReturnFlag = V_ucEventState;
            }
 		}
 	}
	return V_ucReturnFlag;
}
#if (_DEBUG_DB)
/***********************************************************************************
����ԭ�ͣ�void Inf_LowpowerOpenMeterCover(void)
�����������͹����¿����
���������
���������
���ز�����
����˵�����͹�����60sʱ�жϵ��ܱ��ϸ�״̬������͹����ºϸ�һ�Σ����ٽ����ж�
���û��ƣ�����͹���ÿ�����
��    ע��
***********************************************************************************/
void Inf_LowpowerOpenMeterCover(void)
{
    uchar8		EventMsg;
	uchar8		V_ucJudgeBuffer1[C_Judge_20BufferLength];
//  uchar8      V_ucJudgeBuffer2[C_Judge_50BufferLength]={C_Null};
	uchar8		V_ucJudgeBuffer3[C_Judge_20BufferLength];
	uchar8		V_ucBufferLength1=C_Judge_20BufferLength;
//	ushort16	V_CRC;
//	if((PF_Check_CRC(&GStr_OpenMeterCoverStr.OpenCoverState, C_Str_CoverRecord_Length)!=C_OK)||(PF_Check_CRC(&GStr_OpenMeterCoverStr.OpenCoverState, C_Str_CoverRecord_Length)!=C_CrcErr_DataZero))
//	{
//		PF_CopyDataBytes(&V_ucJudgeBuffer2[C_Judge_StartBuffer0], &GStr_OpenMeterCoverStr.OpenCoverState, C_Str_CoverRecord_Length);/*CRC��������*/
//	}
	if(SF_Str_CheckCRC(C_OpenMeterCoverEventNo)!=C_OK)
	{
		SF_Str_Clear(C_OpenMeterCoverEventNo);
		GStr_OpenMeterCoverStr.OpenCoverState=C_Null_EventMsg;	/*�͹���״̬���޶���*/
		GStr_OpenMeterCoverStr.CloseCoverState=C_Null_EventMsg;	/*�͹���״̬���޶���*/
		SF_Str_CalCRC(C_OpenMeterCoverEventNo);
	}
    if(GStr_OpenMeterCoverStr.CloseCoverState!=C_NULL)/*�����������¼������˳�*/
    {
    	return;
    }
    EventMsg=SF_Judge_Event_Statechange(C_OpenMeterCoverEventNo, C_Judge_Time1);/*��1��*/
    if(EventMsg==C_Happen_EventMsg)
    {
		if(InF_Read_Data(CDate_Time, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucBufferLength1)!=C_OK)/*��ȡʱ�䲻�ɹ����˳�*/
		{
			return;
		}
		if(InF_Read_Data(CMeter_Work_State7, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_ucBufferLength1)!=C_OK)/*�������״̬��7*/
		{
			return;
		}
		V_ucJudgeBuffer3[C_Judge_StartBuffer1]|=C_Bit1_Start;/*bit8��1, ����0��1λ*/
		if(InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State7, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag)!=C_OK)/*�������״̬��7д���ݲ�*/
		{																		/*д�������״̬�֣������Ͳ�������*/
// 			PF_CopyDataBytes(&V_ucJudgeBuffer3[C_Judge_StartBuffer0], &GStr_ACPowerFailStr.MeterState, V_ClearLength);/*�������״̬��7д���ݴ�������*/
			return;
		}/*�����ݳɹ�����д���ݲ㣬д���ݲ�ɹ����ٲ����ṹ��*/
		GStr_OpenMeterCoverStr.OpenCoverState=C_LowPowerHappen_EventMsg;
		PF_CopyDataBytes(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], GStr_OpenMeterCoverStr.HappenTime, C_EventTimeLength);/*�¼��ṹ�壬ʱ�丳ֵ*/
		SF_Str_CalCRC(C_OpenMeterCoverEventNo);			/*�͹��Ľṹ����CRC*/
//		V_CRC=PF_Cal_CRC(&GStr_OpenMeterCoverStr.OpenCoverState, C_Str_CoverRecord_Length);/*����CRC*/
//		PF_Ushort16ToBuffer2(GStr_OpenMeterCoverStr.V_CRC, &V_CRC);
		GV_ucEvent_Hstate[C_OpenMeterCoverEventNo]=C_Happen_EventState;/*��ʷ״̬��ֵ*/
	}
	else
	{
		if(EventMsg==C_End_EventMsg)
		{
			if(InF_Read_Data(CDate_Week_Time, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucBufferLength1)!=C_OK)
			{
				return;
			}
			if(InF_Read_Data(CMeter_Work_State7, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_ucBufferLength1)!=C_OK)/*�������״̬��7*/
			{
				return;
			}
			V_ucJudgeBuffer3[C_Judge_StartBuffer1]&=C_Bit1_End;/*bit8��0, ����0��1λ*/
			if(InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State7, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag)!=C_OK)/*�������״̬��7д���ݲ�*/
			{																		/*д�������״̬�֣������Ͳ�������*/
	// 			PF_CopyDataBytes(&V_ucJudgeBuffer3[C_Judge_StartBuffer0], &GStr_ACPowerFailStr.MeterState, V_ClearLength);/*�������״̬��7д���ݴ�������*/
				return;
			}/*�����ݳɹ�����д���ݲ㣬д���ݲ�ɹ����ٲ����ṹ��*/
			GStr_OpenMeterCoverStr.CloseCoverState=C_LowPowerEnd_EventMsg;
			PF_CopyDataBytes(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], GStr_OpenMeterCoverStr.EndTime, C_EventTimeLength);/*�¼��ṹ�壬ʱ�丳ֵ*/
			SF_Str_CalCRC(C_OpenMeterCoverEventNo);			/*�͹��Ľṹ����CRC*/
//			V_CRC=PF_Cal_CRC(&GStr_OpenMeterCoverStr.OpenCoverState, C_Str_CoverRecord_Length);/*����CRC*/
//			PF_Ushort16ToBuffer2(GStr_OpenMeterCoverStr.V_CRC, &V_CRC);
			GV_ucEvent_Hstate[C_OpenMeterCoverEventNo]=C_End_EventState;/*��ʷ״̬��ֵ*/
		}
	}
}
#endif
/***********************************************************************************
����ԭ�ͣ�void Inf_LowpowerOpenCoverState(uchar8 V_ucEvtNo)
�����������͹����¿���ť���뿪��Ǵ���
���������V_ucEvtNo�¼��ţ�ֻ��ΪC_OpenMeterCoverEventNo��C_OpenTerminalCoverEventNo
�����������
���ز�������
����˵����V_ucEvtNoֻ��ΪC_OpenMeterCoverEventNo��C_OpenTerminalCoverEventNo
���û��ƣ�
��    ע��
**********************************************************************************/
void Inf_LowpowerOpenCoverState(uchar8 V_ucEvtNo)
{
    uchar8 V_ucEventMsg;
	uchar8 V_ucJudgeBuffer1[C_Judge_20BufferLength];
	uchar8 V_ucJudgeBuffer3[C_Judge_20BufferLength];
	ushort16 V_usBufferLength1 = C_Judge_20BufferLength, V_usEncode;
    Str_CoverRecord_Type *pStr_strCoverRecord;
    uchar8 V_ucBit;

    if(V_ucEvtNo == C_OpenMeterCoverEventNo)
    {
        pStr_strCoverRecord = &GStr_OpenMeterCoverStr;
        V_ucBit = C_Bit1_Start;/*bit8*/
    }
    else if(V_ucEvtNo == C_OpenTerminalCoverEventNo)
    {
        pStr_strCoverRecord = &GStr_OpenTerminalCoverStr;
        V_ucBit = C_Bit2_Start;/*bit9*/
    }
    else
    {
        return;
    }
	if(SF_Str_CheckCRC(V_ucEvtNo) != C_OK)
	{
		SF_Str_Clear(V_ucEvtNo);
		pStr_strCoverRecord->OpenCoverState = C_Null_EventMsg;	/*�͹���״̬���޶���*/
		pStr_strCoverRecord->CloseCoverState = C_Null_EventMsg;	/*�͹���״̬���޶���*/
		SF_Str_CalCRC(V_ucEvtNo);
	}
    if(pStr_strCoverRecord->CloseCoverState != C_NULL)/*�����������¼������˳�*/
    {
    	return;
    }
    V_ucEventMsg = SF_Judge_Event_Statechange(V_ucEvtNo, C_Judge_Time1);/*��1��*/
    if(V_ucEventMsg == C_Happen_EventMsg)
    {
		if(InF_GetData_ObjectManage(CDate_Time, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) != C_OK)/*��ȡʱ�䲻�ɹ����˳�*/
		{
			return;
		}
        V_usBufferLength1 = CLMeter_Work_State7;
		if(InF_GetData_ObjectManage(CMeter_Work_State7, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) != C_OK)/*�������״̬��7*/
		{
			return;
		}
		V_ucJudgeBuffer3[C_Judge_StartBuffer1] |= V_ucBit;/*bit8��1, ����0��1λ*/
		if(InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State7, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag) != C_OK)/*�������״̬��7д���ݲ�*/
		{																		/*д�������״̬�֣������Ͳ�������*/
            return;
		}/*�����ݳɹ�����д���ݲ㣬д���ݲ�ɹ����ٲ����ṹ��*/
		pStr_strCoverRecord->OpenCoverState = C_LowPowerHappen_EventMsg;
		PF_CopyDataBytes(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], pStr_strCoverRecord->HappenTime, C_EventTimeLength);/*�¼��ṹ�壬ʱ�丳ֵ*/
		SF_Str_CalCRC(V_ucEvtNo);			/*�͹��Ľṹ����CRC*/
		GV_ucEvent_Hstate[V_ucEvtNo] = C_Happen_EventState;/*��ʷ״̬��ֵ*/
	}
	else
	{
		if(V_ucEventMsg == C_End_EventMsg)
		{
			if(InF_GetData_ObjectManage(CDate_Time, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode)!=C_OK)
			{
				return;
			}
            V_usBufferLength1 = CLMeter_Work_State7;
			if(InF_GetData_ObjectManage(CMeter_Work_State7, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode)!=C_OK)/*�������״̬��7*/
			{
				return;
			}
			V_ucJudgeBuffer3[C_Judge_StartBuffer1] &= (~V_ucBit);
			if(InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State7, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag) != C_OK)/*�������״̬��7д���ݲ�*/
			{																		/*д�������״̬�֣������Ͳ�������*/
				return;
			}/*�����ݳɹ�����д���ݲ㣬д���ݲ�ɹ����ٲ����ṹ��*/
			pStr_strCoverRecord->CloseCoverState = C_LowPowerEnd_EventMsg;
			PF_CopyDataBytes(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], pStr_strCoverRecord->EndTime, C_EventTimeLength);/*�¼��ṹ�壬ʱ�丳ֵ*/
			SF_Str_CalCRC(V_ucEvtNo);			/*�͹��Ľṹ����CRC*/
			GV_ucEvent_Hstate[V_ucEvtNo] = C_End_EventState;/*��ʷ״̬��ֵ*/
		}
	}
}
#if (_DEBUG_DB)
/***********************************************************************************
����ԭ�ͣ�void Inf_LowpowerTerminalCoverState(void)
�����������͹����¿���ť��
���������
���������
���ز�����
����˵�����͹�����60sʱ�жϵ��ܱ��϶�ť��״̬������͹����º϶�ť��һ�Σ����ٽ����ж�
���û��ƣ�����͹���ÿ�����
��    ע��
**********************************************************************************/
void Inf_LowpowerTerminalCoverState(void)
{
    uchar8		EventMsg;
	uchar8		V_ucJudgeBuffer1[C_Judge_20BufferLength];
//  uchar8      V_ucJudgeBuffer2[C_Judge_50BufferLength]={C_Null};
	uchar8		V_ucJudgeBuffer3[C_Judge_20BufferLength];
	uchar8		V_ucBufferLength1=C_Judge_20BufferLength;
//	ushort16	V_CRC;
//	if((PF_Check_CRC(&GStr_OpenTerminalCoverStr.OpenCoverState, C_Str_CoverRecord_Length)!=C_OK)||(PF_Check_CRC(&GStr_OpenTerminalCoverStr.OpenCoverState, C_Str_CoverRecord_Length)!=C_CrcErr_DataZero))
//	{
//		PF_CopyDataBytes(&V_ucJudgeBuffer2[C_Judge_StartBuffer0], &GStr_OpenTerminalCoverStr.OpenCoverState, C_Str_CoverRecord_Length);/*CRC��������*/
//	}
	if(SF_Str_CheckCRC(C_OpenTerminalCoverEventNo)!=C_OK)
	{
		SF_Str_Clear(C_OpenTerminalCoverEventNo);
		GStr_OpenTerminalCoverStr.OpenCoverState=C_Null_EventMsg;	/*�͹���״̬���޶���*/
		GStr_OpenTerminalCoverStr.CloseCoverState=C_Null_EventMsg;	/*�͹���״̬���޶���*/
		SF_Str_CalCRC(C_OpenTerminalCoverEventNo);
	}
    if(GStr_OpenTerminalCoverStr.CloseCoverState!=C_NULL)/*�����������¼������˳�*/
    {
    	return;
    }
    EventMsg=SF_Judge_Event_Statechange(C_OpenTerminalCoverEventNo, C_Judge_Time1);/*��1��*/
    if(EventMsg==C_Happen_EventMsg)
    {
		if(InF_Read_Data(CDate_Time, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucBufferLength1)!=C_OK)/*��ȡʱ�䲻�ɹ����˳�*/
		{
			return;
		}
		if(InF_Read_Data(CMeter_Work_State7, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_ucBufferLength1)!=C_OK)/*�������״̬��7*/
		{
			return;
		}
		V_ucJudgeBuffer3[C_Judge_StartBuffer1]|=C_Bit2_Start;/*bit9��1, ����0��2λ*/
		if(InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State7, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag)!=C_OK)/*�������״̬��7д���ݲ�*/
		{																		/*д�������״̬�֣������Ͳ�������*/
// 			PF_CopyDataBytes(&V_ucJudgeBuffer3[C_Judge_StartBuffer0], &GStr_ACPowerFailStr.MeterState, V_ClearLength);/*�������״̬��7д���ݴ�������*/
			return;
		}/*�����ݳɹ�����д���ݲ㣬д���ݲ�ɹ����ٲ����ṹ��*/
		GStr_OpenTerminalCoverStr.OpenCoverState=C_LowPowerHappen_EventMsg;
		PF_CopyDataBytes(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], GStr_OpenTerminalCoverStr.HappenTime, C_EventTimeLength);/*�¼��ṹ�壬ʱ�丳ֵ*/
//		V_CRC=PF_Cal_CRC(&GStr_OpenTerminalCoverStr.OpenCoverState, C_Str_CoverRecord_Length);/*����CRC*/
//		PF_Ushort16ToBuffer2(GStr_OpenTerminalCoverStr.V_CRC, &V_CRC);
		SF_Str_CalCRC(C_OpenTerminalCoverEventNo);
		GV_ucEvent_Hstate[C_OpenTerminalCoverEventNo]=C_Happen_EventState;/*��ʷ״̬��ֵ*/
	}
	else
	{
		if(EventMsg==C_End_EventMsg)
		{
			if(InF_Read_Data(CDate_Time, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucBufferLength1)!=C_OK)
			{
				return;
			}
			if(InF_Read_Data(CMeter_Work_State7, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_ucBufferLength1)!=C_OK)/*�������״̬��7*/
			{
				return;
			}
			V_ucJudgeBuffer3[C_Judge_StartBuffer1]&=C_Bit2_End;/*bit10��0, ����0��2λ*/
			if(InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State7, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag)!=C_OK)/*�������״̬��7д���ݲ�*/
			{																		/*д�������״̬�֣������Ͳ�������*/
	// 			PF_CopyDataBytes(&V_ucJudgeBuffer3[C_Judge_StartBuffer0], &GStr_ACPowerFailStr.MeterState, V_ClearLength);/*�������״̬��7д���ݴ�������*/
				return;
			}/*�����ݳɹ�����д���ݲ㣬д���ݲ�ɹ����ٲ����ṹ��*/
			GStr_OpenTerminalCoverStr.CloseCoverState=C_LowPowerEnd_EventMsg;
			PF_CopyDataBytes(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], GStr_OpenTerminalCoverStr.EndTime, C_EventTimeLength);/*�¼��ṹ�壬ʱ�丳ֵ*/
		    SF_Str_CalCRC(C_OpenTerminalCoverEventNo);
//			V_CRC=PF_Cal_CRC(&GStr_OpenTerminalCoverStr.OpenCoverState, C_Str_CoverRecord_Length);/*����CRC*/
//			PF_Ushort16ToBuffer2(GStr_OpenTerminalCoverStr.V_CRC, &V_CRC);
			GV_ucEvent_Hstate[C_OpenTerminalCoverEventNo]=C_End_EventState;/*��ʷ״̬��ֵ*/
		}
	}
}
#endif
/**********************************************************************************
����ԭ�ͣ�void Inf_LowPowerMeterStatus(void)
�����������͹������õ������״̬��
�����������
�����������
���ز�������
����˵����
���û��ƣ�����͹��ĺ�1sʱ���ã�
��    ע��
**********************************************************************************/
void Inf_LowPowerMeterStatus(void)
{
    uchar8 V_ucMeter_WorkState4Temp[C_MeterWorkState_Length] = {C_NULL, C_NULL};
    uchar8 V_ucMeter_WorkState5Temp[C_MeterWorkState_Length] = {C_NULL, C_NULL};
    uchar8 V_ucMeter_WorkState6Temp[C_MeterWorkState_Length] = {C_NULL, C_NULL};
    uchar8 V_ucMeter_WorkState7Temp[C_MeterWorkState_Length] = {C_NULL, C_NULL};
    uchar8 V_ucReturnData;
    ushort16 V_usMeterStateLenth = C_MeterWorkState_Length, V_usEncode;

    InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State4, &V_ucMeter_WorkState4Temp[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag);/*�������״̬��4��ֵ*/
    InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State5, &V_ucMeter_WorkState5Temp[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag);/*�������״̬��5��ֵ*/
    InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State6, &V_ucMeter_WorkState6Temp[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag);/*�������״̬��6��ֵ*/

    V_ucReturnData = InF_GetData_ObjectManage(CMeter_Work_State7, V_ucMeter_WorkState7Temp, &V_usMeterStateLenth, &V_usEncode);
    if(V_ucReturnData == C_OK)
    {
        V_ucMeter_WorkState7Temp[0] &= 0x30;
        V_ucMeter_WorkState7Temp[1] &= C_Bit0_End;

        InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State7, &V_ucMeter_WorkState7Temp[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag);/*�������״̬��7��ֵ*/
    }
}

/***********************************************************************************
����ԭ�ͣ�void SF_CalAh_Judgemsg(void)
��������������Ah��
���������
���������
���ز�����
����˵����ÿ�����һ�Σ�����Ah��
���û��ƣ�
��    ע��
***********************************************************************************/
void SF_CalAh_Judgemsg(void)
{
	uchar8 	V_ucEventNo;
	uchar8	V_ucJudgeBuffer1[C_Judge_20BufferLength];
	ushort16 V_usBufferLength1 = C_Judge_20BufferLength, V_usEncode;

	for(V_ucEventNo = C_AlossvoltageEventNo;V_ucEventNo <= C_CLossphaseEventNo;V_ucEventNo ++)
	{
		if(SF_Str_CheckCRC(V_ucEventNo) != C_OK)/*����ṹ��CRC��������*/
		{
			SF_Str_Clear(V_ucEventNo);					/*�ṹ������*/
			SF_Str_CalCRC(V_ucEventNo);
		}
		else
		{
			if(GV_ucEvent_Hstate[V_ucEventNo] != C_Happen_EventState)
			{
				continue;
			}
			else
			{
				if(InF_GetData_ObjectManage(CPhaseFF_Curr, &V_ucJudgeBuffer1[C_JudgeCurr_Buffer1], &V_usBufferLength1, &V_usEncode) == C_OK)/*��ȡ�������*/
				{
                    PF_GetAbs(&V_ucJudgeBuffer1[C_JudgeCurr_Buffer1], &V_ucJudgeBuffer1[C_JudgeCurr_Buffer1], CLPhaseA_Curr);/*����ȡ����ֵ*/
                    PF_GetAbs(&V_ucJudgeBuffer1[C_JudgeCurr_Buffer2], &V_ucJudgeBuffer1[C_JudgeCurr_Buffer2], CLPhaseA_Curr);/*����ȡ����ֵ*/
                    PF_GetAbs(&V_ucJudgeBuffer1[C_JudgeCurr_Buffer3], &V_ucJudgeBuffer1[C_JudgeCurr_Buffer3], CLPhaseA_Curr);/*����ȡ����ֵ*/

                    SF_HEXAddBytes(&V_ucJudgeBuffer1[C_JudgeCurr_Buffer1], &V_ucJudgeBuffer1[C_JudgeCurr_Buffer2], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Curr_Length);/*A+B*/
                    SF_HEXAddBytes(&V_ucJudgeBuffer1[C_JudgeCurr_Buffer3], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Curr_Length);/*A+B+C*/

                    SF_HEXAddBytes(&V_ucJudgeBuffer1[C_JudgeCurr_Buffer1], Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_AAhAddr, Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_AAhAddr, C_Curr_Length);
                    SF_HEXAddBytes(&V_ucJudgeBuffer1[C_JudgeCurr_Buffer2], Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_BAhAddr, Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_BAhAddr, C_Curr_Length);
                    SF_HEXAddBytes(&V_ucJudgeBuffer1[C_JudgeCurr_Buffer3], Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_CAhAddr, Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_CAhAddr, C_Curr_Length);
                    SF_HEXAddBytes(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_TotalAhAddr, Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_TotalAhAddr, C_Curr_Length);

                    while(PF_Campare_Data(Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_AAhAddr, (uchar8 *)C_ucAhEquivalent, C_Curr_Length) != C_LessThan)/*A��AhдRAM��ַ*/
					{
						SF_HEXDECBytes(Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_AAhAddr, (uchar8 *)C_ucAhEquivalent, Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_AAhAddr, C_Curr_Length);				/*���ڣ���ȥ0.01Ah*/
						SF_HEXAddBytes(Str_RAMAhTable1[V_ucEventNo-C_AddAhBaseNo].P_AAhAddr, (uchar8 *)C_ucAddAh, Str_RAMAhTable1[V_ucEventNo-C_AddAhBaseNo].P_AAhAddr, C_Ah_Length);							/*RAM�����ݼ�0.01*/
					}
					while(PF_Campare_Data(Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_BAhAddr, (uchar8 *)C_ucAhEquivalent, C_Curr_Length) != C_LessThan)/*B��AhдRAM��ַ*/
					{
						SF_HEXDECBytes(Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_BAhAddr, (uchar8 *)C_ucAhEquivalent, Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_BAhAddr, C_Curr_Length);				/*���ڣ���ȥ0.01Ah*/
						SF_HEXAddBytes(Str_RAMAhTable1[V_ucEventNo-C_AddAhBaseNo].P_BAhAddr, (uchar8 *)C_ucAddAh, Str_RAMAhTable1[V_ucEventNo-C_AddAhBaseNo].P_BAhAddr, C_Ah_Length);							/*RAM�����ݼ�0.01*/
					}
					while(PF_Campare_Data(Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_CAhAddr, (uchar8 *)C_ucAhEquivalent, C_Curr_Length) != C_LessThan)/*C��AhдRAM��ַ*/
					{
						SF_HEXDECBytes(Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_CAhAddr, (uchar8 *)C_ucAhEquivalent, Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_CAhAddr, C_Curr_Length);				/*���ڣ���ȥ0.01Ah*/
						SF_HEXAddBytes(Str_RAMAhTable1[V_ucEventNo-C_AddAhBaseNo].P_CAhAddr, (uchar8 *)C_ucAddAh, Str_RAMAhTable1[V_ucEventNo-C_AddAhBaseNo].P_CAhAddr, C_Ah_Length);							/*RAM�����ݼ�0.01*/
					}
					while(PF_Campare_Data(Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_TotalAhAddr, (uchar8 *)C_ucAhEquivalent, C_Curr_Length) != C_LessThan)/*��AhдRAM��ַ*/
					{
						SF_HEXDECBytes(Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_TotalAhAddr, (uchar8 *)C_ucAhEquivalent, Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_TotalAhAddr, C_Curr_Length);				/*���ڣ���ȥ0.01Ah*/
						SF_HEXAddBytes(Str_RAMAhTable1[V_ucEventNo-C_AddAhBaseNo].P_TotalAhAddr, (uchar8 *)C_ucAddAh, Str_RAMAhTable1[V_ucEventNo-C_AddAhBaseNo].P_TotalAhAddr, C_Ah_Length);							/*RAM�����ݼ�0.01*/
					}
					SF_Str_CalCRC(V_ucEventNo);
				}
			}
		}
	}
}

/***********************************************************************************
����ԭ�ͣ�void SF_RenewalData_Judgemsg(void)
���������������¼���������������
���������
���������
���ز�����
����˵����ÿ�����һ�Σ�����Ah��
���û��ƣ�
��    ע��
***********************************************************************************/
void SF_RenewalData_Judgemsg(void)
{
	uchar8 	V_ucEventNo, V_ucTableNo, V_UnbalanceNo;
	uchar8	V_ucJudgeBuffer1[C_Judge_20BufferLength];
	uchar8	V_ucJudgeBuffer2[C_Judge_20BufferLength];
	ushort16 V_usBufferLength1 = C_Judge_20BufferLength, V_usEncode;
    uchar8  V_ucSign[2];

	for(V_ucEventNo = C_OverForwardActiveEventNo;V_ucEventNo <= C_4OverIdleDemandEventNo;V_ucEventNo ++)
	{
		if(SF_Str_CheckCRC(V_ucEventNo) != C_OK)/*����ṹ��CRC��������*/
		{
            SF_Str_Clear(V_ucEventNo);					/*�ṹ������*/
            SF_Str_CalCRC(V_ucEventNo);
		}
		if(GV_ucEvent_Hstate[V_ucEventNo] != C_Happen_EventState)
		{
			continue;
		}
        InF_GetData_ObjectManage(CCurr_AcDemand, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode);/*�й�����*/
        V_ucSign[0] = PF_GetAbs(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], CLCurr_AcDemand);/*��ȡ����ֵ������������ʶ*/

        V_usBufferLength1 = CLCurr_ReDemand;
        InF_GetData_ObjectManage(CCurr_ReDemand, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode);/*�޹�����*/

        V_ucSign[1] = PF_GetAbs(&V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], CLCurr_ReDemand);/*��ȡ����ֵ������������ʶ*/

        if( ((V_ucEventNo == C_OverForwardActiveEventNo) && (V_ucSign[0] != C_Minus))
          || ((V_ucEventNo == C_OverReverseActiveEventNo) && (V_ucSign[0] == C_Minus)) )
        {
            if(PF_Campare_Data(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], CommunicateReadTable[V_ucEventNo + C_OverDemandBaseNo].DataRAMAddr, C_Demand_Length) == C_GreaterThan)
            {
                V_usBufferLength1 = CLDate_Week_Time; /*V0.2�������ȸ�ֵ*/
                if(InF_GetData_ObjectManage(CDate_Time, &V_ucJudgeBuffer1[C_Judge_StartBuffer4], &V_usBufferLength1, &V_usEncode) == C_OK)
                {
                    PF_CopyDataBytes(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], CommunicateReadTable[V_ucEventNo + C_OverDemandBaseNo].DataRAMAddr, C_DemandTime_Length);
                    SF_Str_CalCRC(V_ucEventNo);
                }
            }
        }
        else if( ((V_ucEventNo==C_1OverIdleDemandEventNo) && (V_ucSign[0] != C_Minus) && (V_ucSign[1] != C_Minus))/*�й������޹���*/
           || ((V_ucEventNo==C_2OverIdleDemandEventNo) && (V_ucSign[0] == C_Minus) && (V_ucSign[1] != C_Minus))/*�й������޹���*/
           || ((V_ucEventNo==C_3OverIdleDemandEventNo) && (V_ucSign[0] == C_Minus) && (V_ucSign[1] == C_Minus))/*�й������޹���*/
           || ((V_ucEventNo==C_4OverIdleDemandEventNo) && (V_ucSign[0] != C_Minus) && (V_ucSign[1] == C_Minus)) )/*�й������޹���*/
        {
            if(PF_Campare_Data(&V_ucJudgeBuffer2[C_Judge_StartBuffer0], CommunicateReadTable[V_ucEventNo + C_OverDemandBaseNo].DataRAMAddr, C_Demand_Length) == C_GreaterThan)
            {
                V_usBufferLength1 = CLDate_Week_Time; /*V0.2�������ȸ�ֵ*/
                if(InF_GetData_ObjectManage(CDate_Time, &V_ucJudgeBuffer2[C_Judge_StartBuffer4], &V_usBufferLength1, &V_usEncode) == C_OK)
                {
                    PF_CopyDataBytes(&V_ucJudgeBuffer2[C_Judge_StartBuffer0], CommunicateReadTable[V_ucEventNo+C_OverDemandBaseNo].DataRAMAddr, C_DemandTime_Length);
                    SF_Str_CalCRC(V_ucEventNo);
                }
            }
        }
    }
	for(V_UnbalanceNo = 0;V_UnbalanceNo <= 2;V_UnbalanceNo ++)
	{
		if(V_UnbalanceNo < 2)
		{
			V_ucEventNo = V_UnbalanceNo + 27;
			V_ucTableNo = V_ucEventNo + C_UnbalanceBaseNo;
		}
		else
		{
			V_ucEventNo = V_UnbalanceNo + 47;
			V_ucTableNo = V_ucEventNo + C_SUnbalanceBaseNo;
		}

		if(SF_Str_CheckCRC(V_ucEventNo) != C_OK)/*����ṹ��CRC��������*/
		{
			SF_Str_Clear(V_ucEventNo);					/*�ṹ������*/
			SF_Str_CalCRC(V_ucEventNo);
		}
		if(GV_ucEvent_Hstate[V_ucEventNo] != C_Happen_EventState)
		{
			continue;
		}
		SF_Get_UnbalanceRate_RealTime(V_ucEventNo, &V_ucJudgeBuffer1[C_Judge_StartBuffer0]);
        if(PF_Campare_Data(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], CommunicateReadTable[V_ucTableNo].DataRAMAddr, C_Unbalance_Length) == C_GreaterThan)
        {
            PF_CopyDataBytes(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], CommunicateReadTable[V_ucTableNo].DataRAMAddr, C_Unbalance_Length);
            SF_Str_CalCRC(V_ucEventNo);
        }
	}
	SF_CalAh_Judgemsg();
}
/***********************************************************************************
����ԭ�ͣ�void SF_CalAddTime_Judgemsg(void)
���������������ۼ�ʱ��
���������
���������
���ز�����
����˵����ÿ���ӵ���һ�Σ������¼��ۼ�ʱ��
���û��ƣ�
��    ע��
***********************************************************************************/
void SF_CalAddTime_Judgemsg(void)
{
	uchar8  V_uci, EventNo;
	ulong32	V_AddTime;
//    uchar8  *P_AddTemp=(uchar8 *)C_ucAddOneMin;
	for(V_uci=C_TotalVoltageLoseEventNo;V_uci<=C_EventNum_AddTime38;V_uci++)	/*�¼���������е�ʱ�����*/
	{
		if(V_uci<=1)								/*ȫʧѹ�͸�����Դ*/
		{
			EventNo=V_uci;
		}
		else
		{
			EventNo=V_uci+C_AddTimeBaseNo;			/*������¼����ۼ�ʱ���ڱ���е�����������ж��¼������ָ��������Ų�11*/
		}
		if(SF_Str_CheckCRC(EventNo)!=C_OK)
		{
			SF_Str_Clear(EventNo);				/*�ṹ������*/
			SF_Str_CalCRC(EventNo);
		}
		if(GV_ucEvent_Hstate[EventNo]==C_Happen_EventState)
		{
			PF_BufferXToUlong32(CommunicateReadTable[V_uci].DataRAMAddr, &V_AddTime, C_AddTime_Length);	/*תHEX*/
			V_AddTime++;										/*��1*/
			PF_Ulong32ToBufferX(CommunicateReadTable[V_uci].DataRAMAddr, &V_AddTime, C_AddTime_Length);
			SF_Str_CalCRC(EventNo);		/*����CRC*/
		}
	}

	for(V_uci=C_EventNum_AddTime100;V_uci<=C_EventNum_AddTime113;V_uci++)	/*�����¼���������е�ʱ�����*/
	{
		if(V_uci<=C_EventNum_AddTime110)								/*�����¼��������*/
		{
			EventNo=V_uci - 98;
		}
		else
		{
			EventNo=V_uci - 61;
		}
		if(SF_Str_CheckCRC(EventNo)!=C_OK)
		{
			SF_Str_Clear(EventNo);				/*�ṹ������*/
			SF_Str_CalCRC(EventNo);
		}
		if(GV_ucEvent_Hstate[EventNo]==C_Happen_EventState)
		{
			PF_BufferXToUlong32(CommunicateReadTable[V_uci].DataRAMAddr, &V_AddTime, C_AddTime_Length);	/*תHEX*/
			V_AddTime++;										/*��1*/
			PF_Ulong32ToBufferX(CommunicateReadTable[V_uci].DataRAMAddr, &V_AddTime, C_AddTime_Length);
			SF_Str_CalCRC(EventNo);		/*����CRC*/
		}
	}

}
/***********************************************************************************
����ԭ�ͣ�void SF_WriteAddTime_Judgemsg(void)
���������������ۼ�ʱ��
����������¼���Ϣ��
�����������
���ز�������1
����˵�����¼�д�����е��ã��˴��������㣬����CRC(������ŵ�д������ȥд)
���û��ƣ�
��    ע��
***********************************************************************************/
void SF_WriteAddTime_Judgemsg(uchar8 EventNo)
{
	uchar8 V_uci, V_ucj;
	uchar8 V_ucJudgeBuffer1[C_Judge_10BufferLength];
	ushort16 V_usJudgeBufferLength1 = C_Judge_10BufferLength, V_usEncode;
	ulong32 V_ulAddTime1, V_ulAddTime2;

	if(SF_Judge_EventIntegrity(EventNo) == C_Happen_EventState)
	{
		for(V_uci = 0;V_uci < C_AddTimeDataNumbersLength;V_uci ++)
		{
			if(V_uci < 39)
			{
				V_ucj = V_uci;
			}
			else
			{
				V_ucj = V_uci +  61;
			}
			if(EventNo == CommunicateReadTable[V_ucj].EventNo)
			{
				if(InF_GetData_ObjectManage(CommunicateReadTable[V_ucj].DataCode, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) == C_OK)
				{
					PF_BufferXToUlong32(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ulAddTime1, C_AddTime_Length);	/*תHEX*/

                    PF_BufferXToUlong32(CommunicateReadTable[V_ucj].DataRAMAddr, &V_ulAddTime2, C_AddTime_Length);		/*תHEX*/

                    V_ulAddTime1 += V_ulAddTime2;

                    PF_Ulong32ToBufferX(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ulAddTime1, C_AddTime_Length);

                    InF_Write_Data(C_Msg_PowerNetworkMonitoring, CommunicateReadTable[V_ucj].DataCode, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], CommunicateReadTable[V_ucj].Length, C_W_SafeFlag);/*�¼��ۼ�ʱ��д����*/
					return;
				}
			}
		}
	}
}

/*******************************************************************************
����ԭ�ͣ�uchar8 Inf_Get_PowerDownEvent_Data(uchar8 V_ucEventNo, uchar8 *P_DataBuffer , ushort16 *P_DataLen)
�����������͹����»�ȡ��������
���������V_ucEventNo���¼���  P_DataBuffer������  P_DataLen������
���������
���ز����� C_Error������C_OK����ȷ��֡
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 Inf_Get_PowerDownEvent_Data(uchar8 V_ucEventNo, uchar8 *pV_DataBuffer , ushort16 *pV_DataLen)
{
	uchar8		V_ucJudgeBuffer1[C_Judge_300BufferLength] = {0}, V_ucJudgeBuffer2[C_Judge_10BufferLength] = {0};
	uchar8		V_uci, V_ucEvent_Flag, V_ucReturnFlag = C_Error;
	ushort16	V_usOffset = 0, V_usResidualLength, V_usJudgeBufferLength1, V_usBufferLength2 = C_Judge_10BufferLength, V_usEncode;

    for(V_uci = 0; V_uci < EventMappingTable_Len; V_uci++)
	{
		if(EventMappingTable[V_uci].EventNo == V_ucEventNo)
		{
			break;
		}
	}
	if(V_uci < EventMappingTable_Len)
	{
        if(InF_GetData_ObjectManage(CDate_Time, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usBufferLength2, &V_usEncode) == C_OK)		/*��ϵͳ��ǰʱ��*/
        {
            V_usJudgeBufferLength1 = 4;
            if(InF_GetData_ObjectManage(EventMappingTable[V_uci].Degree, V_ucJudgeBuffer1, &V_usJudgeBufferLength1, &V_usEncode) == C_OK)		/*���¼����*/
            {
                V_usOffset += 4;

                PF_CopyDataBytes(V_ucJudgeBuffer2, &V_ucJudgeBuffer1[V_usOffset], C_EventTimeLength);				/*���¼�����ʱ�䣬����ʱ��Ϊ00000000000000*//*��ȡ�¼�����ʱ��*/
                V_usOffset += CLDate_Week_Time;     /*����ʱ��*/
				memset(V_ucJudgeBuffer1 + V_usOffset, 0xAA, CLDate_Week_Time);
                V_usOffset += CLDate_Week_Time;     /*����ʱ��*/

                if(EventMappingTable[V_uci].SourceFlag == 0x01)		/*���з���Դ����*/
                {
                    V_usOffset += 1;
                }
                V_usOffset += CLEventReport;/*�����ϱ�״̬ƫ��*/

                V_usResidualLength = 300 - V_usOffset;				/*ʣ��buff����*/

                V_ucEvent_Flag = 0x01;

                if(Inf_GetRecordData(&V_ucJudgeBuffer1[V_usOffset], &V_usResidualLength, EventMappingTable[V_uci].OADTab, V_ucEvent_Flag) == C_OK)	/*��ȡ����OAD����*/
                {
                    V_usOffset += V_usResidualLength;			/*�����ܳ���*/
                    memcpy(pV_DataBuffer, V_ucJudgeBuffer1 , V_usOffset);
                    *pV_DataLen = V_usOffset;
                    V_ucReturnFlag = C_OK;
                }
            }
        }
	}
    return V_ucReturnFlag;
}
/*******************************************************************************
����ԭ�ͣ�void SF_Write_EventCurrentRelate(uchar8 V_ucEventNo, *pV_DataBuffer)
�����������¼�д��Ϣ����
���������
���������
���ز�����
����λ�ã�
��    ע�� �ж���Ϣ����ʱ����
*******************************************************************************/
void SF_Write_EventCurrentRelate(uchar8 V_ucEventNo, uchar8 *pV_DataBuffer)
{
	uchar8		V_ucJudgeBuffer1[C_Judge_300BufferLength] = {0};
	uchar8		V_uci, V_ucEvent_Flag;
	ushort16	V_usOffset = 0, V_usResidualLength;
	ushort16	V_usJudgeBufferLength1, V_usEncode;

	for(V_uci = 0; V_uci < EventMappingTable_Len; V_uci++)
	{
		if(EventMappingTable[V_uci].EventNo == V_ucEventNo)
		{
			break;
		}
	}

	if(V_uci >= EventMappingTable_Len)
	{
		return;
	}

	if(*(pV_DataBuffer + C_PTTime_Msgbuffer) == Pt_HappenTime)
	{
		if(SF_Judge_EventIntegrity(V_ucEventNo) != C_Happen_EventState)		/*�����ʷ״̬�з����޻ָ�, �˳�*/
		{
			V_usJudgeBufferLength1 = CLAll_Loss_Vol_Degree;
			InF_GetData_ObjectManage(EventMappingTable[V_uci].Degree, V_ucJudgeBuffer1, &V_usJudgeBufferLength1, &V_usEncode);			/*���¼����*/
			V_usOffset += CLEventDegree;

			PF_CopyDataBytes(pV_DataBuffer + 3, &V_ucJudgeBuffer1[V_usOffset], C_EventTimeLength);				/*���¼�����ʱ�䣬����ʱ��Ϊ00000000000000*//*��ȡ�¼�����ʱ��*/
			V_usOffset += CLDate_Time;
			V_usOffset += CLDate_Time;

			if(EventMappingTable[V_uci].SourceFlag == 0x01)		/*���з���Դ����*/
			{
				V_usOffset += CLEventSource;
			}
            V_usOffset += CLEventReport;/*�����ϱ�״̬ƫ��*/

			if((V_ucEventNo == C_OverForwardActiveEventNo)||
			   (V_ucEventNo == C_OverReverseActiveEventNo)||
			   (V_ucEventNo == C_1OverIdleDemandEventNo)||
			   (V_ucEventNo == C_2OverIdleDemandEventNo)||
			   (V_ucEventNo == C_3OverIdleDemandEventNo)||
			   (V_ucEventNo == C_4OverIdleDemandEventNo))
			{
				V_usOffset += C_OverDemandRenew_Length;
			}

			V_usResidualLength = 300 - V_usOffset;		/*ʣ��buff����*/
			V_ucEvent_Flag = 0x01;
			if(Inf_GetRecordData(&V_ucJudgeBuffer1[V_usOffset], &V_usResidualLength, EventMappingTable[V_uci].OADTab, V_ucEvent_Flag) != C_OK)	/*��ȡ����OAD����*/
			{
				return;
			}
			V_usOffset += V_usResidualLength;			/*�����ܳ���*/
			if(InF_Write_Data(C_Msg_PowerNetworkMonitoring, EventMappingTable[V_uci].WriteOAD, V_ucJudgeBuffer1, V_usOffset, C_W_SafeFlag) == C_OK)		/*�¼�����д����*/
			{
					Inf_EventReport_HP(V_ucEventNo, C_Happen_EventReport);
					InF_ActiveReportSetting(ActiveReportTable[V_ucEventNo]);
			}
		}
        if ( ( V_ucEventNo == C_PowerfailEventNo ) )
        {
            if(Inf_SatisfyPowerOnTime() != C_OK)         /*����ʱ����1Сʱ���緢��ʱ���㣬�����1Сʱ�Ĳ�����ȵ��������������*/
            {
                Inf_Clear_PowerOffShutAcReportTime();
            }
		}
	}
	else
	{
		if(*(pV_DataBuffer + C_PTTime_Msgbuffer) == Pt_EndTime)
		{
			if( ( SF_Str_CheckCRC(V_ucEventNo) ) == C_OK )
			{
				if(SF_Judge_EventIntegrity(V_ucEventNo) == C_Happen_EventState)		/*�����ʷ״̬���з����޻ָ�*/
				{
#if 0	/*���ݲ�Ŀǰд�����ͷ�������Ϊͬһ��ʶ��д�룬���Խ���ʱΪ������ԭ�����ݣ��˴���д���*/
					V_usJudgeBufferLength1 = CLLossA_Vol_Degree;
					InF_GetData_ObjectManage(EventMappingTable[V_uci].Degree, V_ucJudgeBuffer1, &V_usJudgeBufferLength1, &V_usEncode);
#endif
					V_usOffset += CLEventDegree;
#if 0	/*ͬ���棬д�ָ�ʱ����ʱ�䲻��д*/
					V_ulRead_OAD_Hp[0] = EventHappenEndTime[V_ucEventNo];
					V_ulRead_OAD_Hp[1] = CEventHPTime;
					V_ulRead_OAD_Hp[2] = 0xFFFFFFFF;

					V_ucBufferLen = C_EventTimeLength;
                    SF_ReadLastEvt(V_ulRead_OAD_Hp, &V_ucJudgeBuffer1[V_usOffset], &V_ucBufferLen, (uchar8)V_ulRead_OAD_Hp[0]);
#endif
					V_usOffset += CLDate_Time;
					PF_CopyDataBytes(pV_DataBuffer + 3, &V_ucJudgeBuffer1[V_usOffset], C_EventTimeLength);		/*���¼�����ʱ�䣬����ʱ��Ϊ00000000000000*/
					V_usOffset += CLDate_Time;

					if(EventMappingTable[V_uci].SourceFlag == 0x01)		/*���з���Դ����*/
					{
						V_usOffset += CLEventSource;
					}
                    V_usOffset += CLEventReport;/*�����ϱ�״̬ƫ��*/

					switch(V_ucEventNo)
					{
						case	C_OverForwardActiveEventNo:
								PF_CopyDataBytes(GStr_OverForwardActiveStr.Renewal, &V_ucJudgeBuffer1[V_usOffset], C_OverDemandRenew_Length);
								V_usOffset += C_OverDemandRenew_Length;
								break;
						case	C_OverReverseActiveEventNo:
								PF_CopyDataBytes(GStr_OverReverseActiveStr.Renewal, &V_ucJudgeBuffer1[V_usOffset], C_OverDemandRenew_Length);
								V_usOffset += C_OverDemandRenew_Length;
								break;
						case	C_1OverIdleDemandEventNo:
								PF_CopyDataBytes(GStr_Over1IdleDemandStr.Renewal, &V_ucJudgeBuffer1[V_usOffset], C_OverDemandRenew_Length);
								V_usOffset += C_OverDemandRenew_Length;
								break;
						case	C_2OverIdleDemandEventNo:
								PF_CopyDataBytes(GStr_Over2IdleDemandStr.Renewal, &V_ucJudgeBuffer1[V_usOffset], C_OverDemandRenew_Length);
								V_usOffset += C_OverDemandRenew_Length;
								break;
						case	C_3OverIdleDemandEventNo:
								PF_CopyDataBytes(GStr_Over3IdleDemandStr.Renewal, &V_ucJudgeBuffer1[V_usOffset], C_OverDemandRenew_Length);
								V_usOffset += C_OverDemandRenew_Length;
								break;
						case	C_4OverIdleDemandEventNo:
								PF_CopyDataBytes(GStr_Over4IdleDemandStr.Renewal, &V_ucJudgeBuffer1[V_usOffset], C_OverDemandRenew_Length);
								V_usOffset += C_OverDemandRenew_Length;
								break;
						default:
								break;
					}

					V_usResidualLength = 300 - V_usOffset;		/*ʣ��buff����*/
					V_ucEvent_Flag = 0x02;

					switch(V_ucEventNo)								/*�з������������ݵ��¼���������*/
					{
						case	C_AlossvoltageEventNo:
								V_ucEvent_Flag |= 0x10;
								break;
						case	C_BlossvoltageEventNo:
								V_ucEvent_Flag |= 0x20;
								break;
						case	C_ClossvoltageEventNo:
								V_ucEvent_Flag |= 0x30;
								break;
						case	C_ALessvoltageEventNo:
								V_ucEvent_Flag |= 0x40;
								break;
						case	C_BLessvoltageEventNo:
								V_ucEvent_Flag |= 0x50;
								break;
						case	C_CLessvoltageEventNo:
								V_ucEvent_Flag |= 0x60;
								break;
						case	C_AOvervoltageEventNo:
								V_ucEvent_Flag |= 0x70;
								break;
						case	C_BOvervoltageEventNo:
								V_ucEvent_Flag |= 0x80;
								break;
						case	C_COvervoltageEventNo:
								V_ucEvent_Flag |= 0x90;
								break;
						case	C_ALossphaseEventNo:
								V_ucEvent_Flag |= 0xA0;
								break;
						case	C_BLossphaseEventNo:
								V_ucEvent_Flag |= 0xB0;
								break;
						case	C_CLossphaseEventNo:
								V_ucEvent_Flag |= 0xC0;
								break;
						case	C_UnbanlanceVoltageEventNo:
								V_ucEvent_Flag |= 0xD0;
								break;
						case	C_UnbanlanceCurrentEventNo:
								V_ucEvent_Flag |= 0xE0;
								break;
						case	C_SUnbanlanceCurrentEventNo:
								V_ucEvent_Flag |= 0xF0;
								break;
						default:
								break;
					}
					if(Inf_GetRecordData(&V_ucJudgeBuffer1[V_usOffset], &V_usResidualLength, EventMappingTable[V_uci].OADTab, V_ucEvent_Flag) != C_OK)	/*��ȡ����OAD����*/
					{
						return;
					}
					V_usOffset += V_usResidualLength;			/*�����ܳ���*/
					if(InF_Write_Data(C_Msg_PowerNetworkMonitoring, EventMappingTable[V_uci].WriteOAD + 0x00000001, V_ucJudgeBuffer1, V_usOffset, C_W_SafeFlag) == C_OK)/*�¼�����д����*/
                    {
                        Inf_EventReport_HP(V_ucEventNo, C_End_EventReport);
                    }
				}
			}

            if ( ( V_ucEventNo == C_PowerfailEventNo ) )
            {
                Inf_Clear_PowerOffShutAcReportTime();                       /*�ϵ���1Сʱʱ����д�������ʱ���㣬���¿�ʼ��ʱ*/
            }
		}
	}
}

/***********************************************************************************
����ԭ�ͣ�uchar8 SF_EventClear_Judgemsg(uchar8 EventNo)
�������������㺯��
���������
���������
���ز�����
����˵�����¼�����ӿں���
���û��ƣ�ͨ������ʱ����
��    ע��
***********************************************************************************/
uchar8 SF_EventClear_Judgemsg(uchar8 EventNo)
{
	uchar8	V_uci;

	if( ( EventNo == C_AllEventNo ) || ( EventNo == C_ClockFaEventNo) )/*�����ʱ�ӹ����¼�, ����Ų����Ҫ������*/
	{
		InF_ExecuteClr_RTC();				/*ʱ�ӹ��ϱ�־*/
		InF_Clear_BroadTimeAbnormalTime();	/*��㲥Уʱ�쳣ʱ��*/
	}

	if(EventNo == C_AllEventNo)
	{
		for(EventNo = C_TotalVoltageLoseEventNo;EventNo <= C_NeutralCurrentAbnormalEventNo;EventNo++)
		{
			GV_ucEvent_Hstate[EventNo] = C_End_EventState;
			GV_ucEvent_JudgeTimer[EventNo] = C_NULL;

			SF_Str_Clear(EventNo);
			SF_Str_CalCRC(EventNo);
		}
	}
	else
	{
		for(V_uci = 0;V_uci < Str_698EventReport_Len;V_uci ++)		/*ȷ����Ӧ�¼�*/
		{
			if(EventNo == Str_698EventReport[V_uci].EventNo)
			{
				break;
			}
		}

		if(V_uci >= Str_698EventReport_Len)
		{
			return C_IDError;
		}

        Inf_ReportList(C_ReportChannelAll, EventNo, C_DeletReport);///�����ϱ�
        SF_Clear645_ReportNewAddNum(EventNo, C_EventCLEAR);//698����645��������645�����ϱ�

		if(EventNo <= C_NeutralCurrentAbnormalEventNo)
		{
			GV_ucEvent_Hstate[EventNo] = C_End_EventState;
			GV_ucEvent_JudgeTimer[EventNo] = C_NULL;

			SF_Str_Clear(EventNo);
			SF_Str_CalCRC(EventNo);
        }
        else
        {
           return(C_IDError);
        }
	}

	SF_MeterStatus_Judgemsg();
	return(C_OK);
}
/***********************************************************************************
����ԭ�ͣ�uchar8 Inf_ReadEventRenew(ulong32 *V_Data_Id, uchar8 *pV_Data, uchar8 pV_Data_Length)
����������ͨ�Ŷ�ȡ�¼����������е�����
���������
           *V_Data_Id     ֧�ֵ������ݶ�ȡ����ʽ1����OAD V_Data_Id[0]Ϊ���OAD��V_Data_Id[1]=0xFFFFFFFF��ʾ����
						��ʽ2��˫OAD V_Data_Id[0]Ϊ�����¼�OAD��V_Data_Id[1]Ϊ�������ݣ�V_Data_Id[2]=0xFFFFFFFF��ʾ����
           *pV_Data                      ��������ָ��
           *pV_Data_Length               ������pV_Data��󳤶�
��������� *pV_Data                      �������ݣ�
           *pV_Data_Length               �����ݵ�ʵ�ʳ���
���ز�����  C_IDError:��֧�ֶ�ȡ�����ݱ�ʶ��C_DataLenError���ݳ��ȴ�, C_OK:��ȷִ��
            InF_GetData_ObjectManage()���ܷ��ص��κ�ֵ
����˵����֧�����1���¼�����������Ah��/���ƽ����/���������ڼ����������ʱ�䣬���һ��ʧѹ��ʼʱ��/���һ��ʧѹ����ʱ��
          �¼����ۼ�ʱ�估ʧѹ�ܴ�����CommunicateReadTable[V_uci].DataCode��
���û��ƣ�ͨ�ŵ���
��    ע��*pV_Data_Length������ڵ�����ȡֵ���ȣ���Ȼ���ش���
***********************************************************************************/
uchar8 Inf_ReadEventRenew(ulong32 *V_Data_Id, uchar8 *pV_Data, uchar8 *pV_Data_Length)
{
	uchar8	V_ucJudgeBuffer1[C_Judge_30BufferLength] = {0};			/*ʧѹ�ܴ����ͷ���ʧѹ����, ʧѹ��ʱ��ͷ���ʧѹʱ��*/
    uchar8	V_ucJudgeBuffer2[C_Judge_10BufferLength] = {C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL};/*����ȫ0*/
	ushort16 V_usJudgeBufferLength1 = C_Judge_30BufferLength, V_usEncode;
	uchar8	V_ucReadDataNo;
    uchar8  V_ucMode;
    ulong32	V_ulReadOAD[3], V_ulADD1, V_ulADD2;
    ulong32	V_ulData_Read = 0xFFFFFFFF;
    uchar8	V_uci;
    ushort16 V_usDataLen;

	if(V_Data_Id[1] == 0xFFFFFFFF)
	{
		V_ulData_Read = V_Data_Id[0];
	}
	else if(V_Data_Id[2] == 0xFFFFFFFF)
	{
		for(V_uci = 0;V_uci < SpecialReadTable_Len;V_uci ++)
		{
			if(V_Data_Id[0] == SpecialReadTable[V_uci].EventOAD)
			{
				break;
			}
		}
		if(V_uci >= SpecialReadTable_Len)
		{
			return C_IDError;
		}
		switch(V_Data_Id[1])
		{
			case	C_TolAh_E:
			case	C_VolUnbalanceRate_E:
			case	C_CurUnbalanceRate_E:
			case	CPos_Ac_De_Over_1:
			case	CRev_Ac_De_Over_1:
			case	CQua1_Re_De_Over_1:
			case	CQua2_Re_De_Over_1:
			case	CQua3_Re_De_Over_1:
			case	CQua4_Re_De_Over_1:
				V_ulData_Read = SpecialReadTable[V_uci].TolAh;
				break;
			case	C_AAh_E:
				V_ulData_Read = SpecialReadTable[V_uci].AAh;
				break;
			case	C_BAh_E:
				V_ulData_Read = SpecialReadTable[V_uci].BAh;
				break;
			case	C_CAh_E:
				V_ulData_Read = SpecialReadTable[V_uci].CAh;
				break;
			default:
				return C_IDError;
				break;
		}
	}
	else
	{
		return C_IDError;
	}

	if( (V_ulData_Read==CLoss_Vol_Hp)
       || (V_ulData_Read==CLoss_Vol_End) )
	{
		if(*pV_Data_Length >= CommunicateReadTable[39].Length)/*���泤�ȴ����ṩ��buffer����*/
		{
			V_ulReadOAD[0] = CLossAVol_FF_1;
			V_ulReadOAD[2] = 0xFFFFFFFF;
			if(V_ulData_Read == CLoss_Vol_Hp)
			{
				V_ulReadOAD[1] = CEventHPTime;
			}
			else
			{
				V_ulReadOAD[1] = CEventEndTime;
			}
			V_usDataLen = C_EventTimeLength;
            if( (GV_ucEvent_Hstate[C_AlossvoltageEventNo] == C_Happen_EventState)
               && (V_ulReadOAD[1] == CEventEndTime) )
            {
                V_ulReadOAD[0] += 1;
            }
			V_ucMode = SF_ReadLastEvt(V_ulReadOAD, &V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1], &V_usDataLen, (uchar8)V_ulReadOAD[0]);
			if(V_ucMode == C_NoData)
			{
				V_ucMode = C_OK;
			}

			if(V_ucMode == C_OK)/*���1��A��ʧѹ����/����ʱ��*/
			{
				V_ulReadOAD[0] = CLossBVol_FF_1;
				V_usDataLen=C_EventTimeLength;
                if( (GV_ucEvent_Hstate[C_BlossvoltageEventNo] == C_Happen_EventState)
                   && (V_ulReadOAD[1] == CEventEndTime) )
                {
                    V_ulReadOAD[0] += 1;
                }
				V_ucMode = SF_ReadLastEvt(V_ulReadOAD, &V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1+C_EventTimeLength], &V_usDataLen, (uchar8)V_ulReadOAD[0]);
				if(V_ucMode == C_NoData)
				{
					V_ucMode = C_OK;
				}
				if(V_ucMode == C_OK)/*���1��B��ʧѹ����/����ʱ��*/
				{
					V_ulReadOAD[0] = CLossCVol_FF_1;
					V_usDataLen = C_EventTimeLength;
                    if( (GV_ucEvent_Hstate[C_ClossvoltageEventNo] == C_Happen_EventState)
                       && (V_ulReadOAD[1] == CEventEndTime) )
                    {
                        V_ulReadOAD[0] += 1;
                    }
					V_ucMode = SF_ReadLastEvt(V_ulReadOAD, &V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1 + C_EventTimeLength + C_EventTimeLength], &V_usDataLen, (uchar8)V_ulReadOAD[0]);
					if(V_ucMode == C_NoData)
					{
						V_ucMode = C_OK;
					}
					if(V_ucMode == C_OK)/*���1��C��ʧѹ����/����ʱ��*/
					{
						if(PF_Campare_Data(&V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1], &V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1 + C_EventTimeLength], C_EventTimeLength) == C_GreaterThan)
						{
							PF_CopyDataBytes(&V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1], pV_Data, C_EventTimeLength);
						}
						else
						{
							PF_CopyDataBytes(&V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1 + C_EventTimeLength], pV_Data, C_EventTimeLength);
						}
						if(PF_Campare_Data(&V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1 + C_EventTimeLength + C_EventTimeLength], pV_Data, C_EventTimeLength) == C_GreaterThan)
						{
							PF_CopyDataBytes(&V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1 + C_EventTimeLength + C_EventTimeLength], pV_Data, C_EventTimeLength);
						}
						if(PF_Campare_Data(pV_Data, V_ucJudgeBuffer2, C_EventTimeLength) == C_Equal)	/*ʱ��ȫ�㸳AA*/
						{
							for(V_uci = 0;V_uci < C_EventTimeLength;V_uci ++)
							{
								pV_Data[V_uci] = 0xAA;
							}
						}
						*pV_Data_Length = C_EventTimeLength;
					}
				}
			}
			return(V_ucMode);
		}
		else
		{
			return(C_DataLenError);
		}
	}
	if(V_ulData_Read == CLoss_Vol_Degree)			 		/*ʧѹ�ܴ���*/
	{
		if(*pV_Data_Length >= CommunicateReadTable[39].Length)/*���泤�ȴ����ṩ��buffer����*/
		{
			V_usJudgeBufferLength1 = C_Judge_30BufferLength;	/*V0.2�������ȸ�ֵ*/
			V_ucMode = InF_GetData_ObjectManage(CLossA_Vol_Degree, &V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1], &V_usJudgeBufferLength1, &V_usEncode);
			if(V_ucMode == C_OK)/*A��ʧѹ����*/
			{
                V_usJudgeBufferLength1 = CLLossA_Vol_Degree;
				V_ucMode = InF_GetData_ObjectManage(CLossB_Vol_Degree, &V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1 + CLLossA_Vol_Degree], &V_usJudgeBufferLength1, &V_usEncode);
				if(V_ucMode == C_OK)/*B��ʧѹ����*/
				{
                    V_usJudgeBufferLength1 = CLLossA_Vol_Degree;
					V_ucMode = InF_GetData_ObjectManage(CLossC_Vol_Degree, &V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1 + CLLossA_Vol_Degree * 2], &V_usJudgeBufferLength1, &V_usEncode);
					if(V_ucMode == C_OK)/*C��ʧѹ����*/
					{
						SF_HEXAddBytes(&V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1], &V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1 + CLLossA_Vol_Degree], &V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1], CLLoss_Vol_Degree);
						SF_HEXAddBytes(&V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1], &V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1 + CLLossA_Vol_Degree * 2], &V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1], CLLoss_Vol_Degree);

						PF_CopyDataBytes(&V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1], pV_Data, CLLoss_Vol_Degree);
						*pV_Data_Length = CommunicateReadTable[39].Length;/*�������ݳ���*/
					}
				}
			}
			return(V_ucMode);
		}
		else
		{
			return(C_DataLenError);
		}
	}
	else
	{
		if(V_ulData_Read == CLoss_Vol_Time)/*ʧѹ���ۼ�ʱ��*/
		{
			if(*pV_Data_Length >= CommunicateReadTable[40].Length)
			{
				if(SF_Str_CheckCRC(C_AlossvoltageEventNo) != C_OK)
				{
					SF_Str_Clear(C_AlossvoltageEventNo);
					SF_Str_CalCRC(C_AlossvoltageEventNo);
				}
				if(SF_Str_CheckCRC(C_BlossvoltageEventNo) != C_OK)
				{
					SF_Str_Clear(C_BlossvoltageEventNo);
					SF_Str_CalCRC(C_BlossvoltageEventNo);
				}
				if(SF_Str_CheckCRC(C_ClossvoltageEventNo) != C_OK)
				{
					SF_Str_Clear(C_ClossvoltageEventNo);
					SF_Str_CalCRC(C_ClossvoltageEventNo);
				}
				V_usJudgeBufferLength1 = C_Judge_30BufferLength;	/*V0.2�������ȸ�ֵ*/
				V_ucMode = InF_GetData_ObjectManage(CLossA_Vol_Time, &V_ucJudgeBuffer1[C_FourBytesJudge_Buffer1], &V_usJudgeBufferLength1, &V_usEncode);
				if(V_ucMode == C_OK)/*EE��A���ۼ�ʱ��, buffer3*/
				{
                    V_usJudgeBufferLength1 = CLLossB_Vol_Time;
					V_ucMode = InF_GetData_ObjectManage(CLossB_Vol_Time, &V_ucJudgeBuffer1[C_FourBytesJudge_Buffer2], &V_usJudgeBufferLength1, &V_usEncode);
					if(V_ucMode == C_OK)/*EE��B���ۼ�ʱ��*/
					{
                        V_usJudgeBufferLength1 = CLLossC_Vol_Time;
						V_ucMode = InF_GetData_ObjectManage(CLossC_Vol_Time, &V_ucJudgeBuffer1[C_FourBytesJudge_Buffer3], &V_usJudgeBufferLength1, &V_usEncode);
						if(V_ucMode == C_OK)/*EE��C���ۼ�ʱ��*/
						{
							PF_BufferXToUlong32(GStr_AlossvoltageStr.AddTime, &V_ulADD1, C_AddTime_Length);
							PF_BufferXToUlong32(GStr_BlossvoltageStr.AddTime, &V_ulADD2, C_AddTime_Length);
							V_ulADD1 += V_ulADD2;
							PF_BufferXToUlong32(GStr_ClossvoltageStr.AddTime, &V_ulADD2, C_AddTime_Length);
							V_ulADD1 += V_ulADD2;
							PF_BufferXToUlong32(&V_ucJudgeBuffer1[C_FourBytesJudge_Buffer1], &V_ulADD2, C_AddTime_Length);
							V_ulADD1 += V_ulADD2;
							PF_BufferXToUlong32(&V_ucJudgeBuffer1[C_FourBytesJudge_Buffer2], &V_ulADD2, C_AddTime_Length);
							V_ulADD1 += V_ulADD2;
							PF_BufferXToUlong32(&V_ucJudgeBuffer1[C_FourBytesJudge_Buffer3], &V_ulADD2, C_AddTime_Length);
							V_ulADD1 += V_ulADD2;
							PF_Ulong32ToBufferX(pV_Data, &V_ulADD1, C_AddTime_Length);

							*pV_Data_Length = CommunicateReadTable[40].Length;/*�������ݳ���*/
						}
					}
				}
				return(V_ucMode);	/*��������ݲ㲻�ɹ������ش���*/
			}
			else
			{
				return(C_DataLenError);
			}
		}
		else
		{
			for(V_ucReadDataNo = 0;V_ucReadDataNo < C_ReadDataLength;V_ucReadDataNo ++)
			{
				if(V_ulData_Read == CommunicateReadTable[V_ucReadDataNo].DataCode)
				{
					if(*pV_Data_Length >= CommunicateReadTable[V_ucReadDataNo].Length)
					{
						if(SF_Str_CheckCRC(CommunicateReadTable[V_ucReadDataNo].EventNo) != C_OK)
						{
							SF_Str_Clear(CommunicateReadTable[V_ucReadDataNo].EventNo);
							SF_Str_CalCRC(CommunicateReadTable[V_ucReadDataNo].EventNo);
						}
						if( (V_ucReadDataNo <= C_EventNum_AddTime38)
                           || ( (V_ucReadDataNo >= C_EventNum_AddTime100) && (V_ucReadDataNo <= C_EventNum_AddTime113) ) )
						{
							PF_CopyDataBytes(CommunicateReadTable[V_ucReadDataNo].DataRAMAddr, pV_Data, CommunicateReadTable[V_ucReadDataNo].Length);
							*pV_Data_Length = CommunicateReadTable[V_ucReadDataNo].Length;
							V_usJudgeBufferLength1 = C_AddTime_Length;
							V_ucMode = InF_GetData_ObjectManage(CommunicateReadTable[V_ucReadDataNo].DataCode, &V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1], &V_usJudgeBufferLength1, &V_usEncode);
							if(V_ucMode == C_OK)
							{
								PF_BufferXToUlong32(&V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1], &V_ulADD1, C_AddTime_Length);
								PF_BufferXToUlong32(pV_Data, &V_ulADD2, C_AddTime_Length);
								V_ulADD1 += V_ulADD2;
								PF_Ulong32ToBufferX(pV_Data, &V_ulADD1, C_AddTime_Length);
							}
							else
							{
								return(V_ucMode);
							}
						}
						else
						{
							V_usDataLen = C_Judge_30BufferLength;
							V_ucMode = SF_ReadLastEvt(V_Data_Id, pV_Data, &V_usDataLen, (uchar8)V_Data_Id[0]);
							if(V_ucMode == C_OK)
							{
								if(SF_Judge_EventIntegrity(CommunicateReadTable[V_ucReadDataNo].EventNo) == C_Happen_EventState)		/*�����ʷ״̬�з����޻ָ�, ���¼���¼�������ݸ��Ǵ����ݲ��ж�������һ������*/
								{
									PF_CopyDataBytes(CommunicateReadTable[V_ucReadDataNo].DataRAMAddr, pV_Data, CommunicateReadTable[V_ucReadDataNo].Length);
								}
								*pV_Data_Length = CommunicateReadTable[V_ucReadDataNo].Length;
							}
						}
						return(V_ucMode);
					}
					else
					{
						return(C_DataLenError);
					}
				}
			}
		}
		if((V_ulData_Read == CAll_Loss_Vol)
           || (V_ulData_Read == CAux_Pow_Down))
		{
			V_usJudgeBufferLength1 = C_Judge_30BufferLength;	/*V0.2�������ȸ�ֵ*/
			if(V_ulData_Read == CAll_Loss_Vol)
			{		/*V0.2�޸�*/
				V_ucMode = InF_GetData_ObjectManage(CommunicateReadTable[0].DataCode, &V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1+C_AddNumber_Length], &V_usJudgeBufferLength1, &V_usEncode);
				if(V_ucMode == C_OK)
				{
					V_usJudgeBufferLength1 = C_AddNumber_Length;
					V_ucMode = InF_GetData_ObjectManage(CAll_Loss_Vol_Degree, &V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1], &V_usJudgeBufferLength1, &V_usEncode);
					if(V_ucMode == C_OK)
					{
						PF_BufferXToUlong32(&V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1+C_AddNumber_Length], &V_ulADD1, C_AddTime_Length);
						PF_BufferXToUlong32(CommunicateReadTable[0].DataRAMAddr, &V_ulADD2, C_AddTime_Length);
						V_ulADD1 += V_ulADD2;
						PF_Ulong32ToBufferX(&V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1+C_AddNumber_Length], &V_ulADD1, C_AddTime_Length);
					}
				}
			}
			else
			{
				V_ucMode = InF_GetData_ObjectManage(CommunicateReadTable[1].DataCode, &V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1+C_AddNumber_Length], &V_usJudgeBufferLength1, &V_usEncode);
				if(V_ucMode == C_OK)
				{
					V_usJudgeBufferLength1 = C_AddNumber_Length;
					V_ucMode = InF_GetData_ObjectManage(CAux_Pow_Down_Degree, &V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1], &V_usJudgeBufferLength1, &V_usEncode);
					if(V_ucMode == C_OK)
					{
						PF_BufferXToUlong32(&V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1+C_AddNumber_Length], &V_ulADD1, C_AddTime_Length);
						PF_BufferXToUlong32(CommunicateReadTable[1].DataRAMAddr, &V_ulADD2, C_AddTime_Length);
						V_ulADD1 += V_ulADD2;
						PF_Ulong32ToBufferX(&V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1+C_AddNumber_Length], &V_ulADD1, C_AddTime_Length);
					}
				}
			}
			PF_CopyDataBytes(&V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1], pV_Data, C_AddTimeNumbers_Length);
			*pV_Data_Length = C_AddTimeNumbers_Length;/*�������ݳ���*/
			return(V_ucMode);
		}
		return(C_IDError);
	}
}

/***********************************************************************************
����ԭ�ͣ�uchar8 Inf_BackLightLimit(void)
������������ѹȫ�������ٽ��ѹ������������
�����������
�����������
���ز�����C_StatusError:��֧�ֶ�ȡ�����ݱ�ʶ
          C_OK:��ȷִ��
����˵����
���û��ƣ���ʾ����
��    ע��
***********************************************************************************/
uchar8 Inf_BackLightLimit(void)
{
	uchar8 V_ucJudgeBuffer1[C_Judge_10BufferLength];
	ushort16 V_usBufferLength1 = C_Judge_10BufferLength, V_usEncode;

	if(InF_GetData_ObjectManage(CAuxi_Power_Sign, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) == C_OK)/*������Դ����*/
	{
		if(V_ucJudgeBuffer1[C_Judge_StartBuffer0] == C_ACPowerFail)					/*�и�����Դ��δʧ�磬ֵΪ0x01*/
		{
			if(SF_Get_Event_Cstate(C_ACPowerFailEventNo, GV_ucEvent_Hstate[C_ACPowerFailEventNo]) == C_Happen_EventState)
			{
			    V_ucJudgeBuffer1[C_Judge_StartBuffer0] = C_ACPowerFailState;				/*������Դʧ�磬ֵΪ0x11*/
			}
		}
		V_ucJudgeBuffer1[C_Judge_StartBuffer1] = SF_Get_Event_Cstate(C_TotalVoltageLoseEventNo, GV_ucEvent_Hstate[C_TotalVoltageLoseEventNo]);
		V_ucJudgeBuffer1[C_Judge_StartBuffer2] = SF_Get_Event_Cstate(C_PowerfailEventNo, GV_ucEvent_Hstate[C_PowerfailEventNo]);

        if( ((V_ucJudgeBuffer1[C_Judge_StartBuffer0] == C_ACPowerFailState) || (V_ucJudgeBuffer1[C_Judge_StartBuffer0] == C_NoACPowerFail))
            && ((V_ucJudgeBuffer1[C_Judge_StartBuffer1] == C_Happen_EventState) || (V_ucJudgeBuffer1[C_Judge_StartBuffer2] == C_Happen_EventState)) )
		{
			return(C_StatusError);
		}
	}
	return(C_OK);
}


/***********************************************************************************
����ԭ�ͣ�void SF_Write_EventMsgFuction(Str_Msg_Parameter pStr_EventMsg)
�����������¼�д��Ϣ����
���������
���������
���ز�����
����˵�����ж���Ϣ����ʱ����
���û��ƣ��ж���Ϣ����
��    ע��
***********************************************************************************/
void SF_Write_EventMsgFuction(Str_Msg_Parameter *pStr_EventMsg)
{
	uchar8	V_ucEventNo;
	uchar8	V_ucMsg[C_Judge_20BufferLength];
	uchar8	V_ucMsgLength = pStr_EventMsg->Length;

	if(V_ucMsgLength == C_Event_MsgLength)
	{
		PF_CopyDataBytes(pStr_EventMsg->Parameter, &V_ucMsg[C_Judge_StartBuffer0], V_ucMsgLength);/*��ϵͳ�������������ݿ�������*/

        if(V_ucMsg[C_Judge_StartBuffer0] == PT_EventNo)
		{
			V_ucEventNo = V_ucMsg[1];			/*��ȡEventNo*/
            if(V_ucMsg[C_Judge_StartBuffer2] == Pt_EndTime)	/*�������״̬�ָ�ֵ, �ۼ�ʱ��*/
			{
                SF_WriteAddTime_Judgemsg(V_ucEventNo);/*�ۼ�ʱ������ݲ�*/
                if((V_ucEventNo == C_OpenMeterCoverEventNo)||(V_ucEventNo == C_OpenTerminalCoverEventNo))
                {
                    GV_ucEvent_Hstate[V_ucEventNo] = C_End_EventState;
                }
			}
            if((V_ucEventNo <= C_NeutralCurrentAbnormalEventNo)
               && (V_ucEventNo != C_PowerAbnormalEventNo))
            {
                SF_Write_EventCurrentRelate(V_ucEventNo, &V_ucMsg[C_Judge_StartBuffer0]);
            }
            else
            {
                return;
            }
			GV_ucEvent_JudgeTimer[V_ucEventNo] = C_NULL;	/*��ʱ������*/
            if(GV_ucEvent_Hstate[V_ucEventNo] == C_Happen_EventState)
            {
                if(V_ucEventNo == C_TotalVoltageLoseEventNo)
                {
                    GStr_TotalvoltageloseStr.MeterState = C_Null_EventMsg;
                }
                else if(V_ucEventNo == C_ACPowerFailEventNo)
                {
                    GStr_ACPowerFailStr.MeterState = C_Null_EventMsg;
                }
                else if(V_ucEventNo == C_OpenMeterCoverEventNo)
                {
                    GStr_OpenMeterCoverStr.OpenCoverState = C_Null_EventMsg;
                }
                else if(V_ucEventNo == C_OpenTerminalCoverEventNo)
                {
                    GStr_OpenTerminalCoverStr.OpenCoverState = C_Null_EventMsg;
                }
                else if(V_ucEventNo == C_PowerfailEventNo)
                {
                    GStr_PowerfailStr.MeterState = C_Null_EventMsg;
                }
                else
                {
                    return;
                }
                SF_Str_CalCRC(V_ucEventNo);			/*�¼��͹����·�����ʶ���㣬����CRC*/
                return;
            }
			SF_Str_Clear(V_ucEventNo);
			SF_Str_CalCRC(V_ucEventNo);			/*���㣬����CRC*/
		}
	}
}

/***********************************************************************************
����ԭ�ͣ�void InF_Event_Message(Str_Msg_Parameter	pStr_Msg)
������������Ϣ��������
���������
���������
���ز�����
����˵������Ϣ֡��������
���û��ƣ����ȵ���
��    ע��
***********************************************************************************/
void InF_Event_Message(Str_Msg_Parameter *pStr_Msg)
{
	uchar8	V_ucEventNo;
	ulong32	V_ulDataCode;

    if(pStr_Msg->PowerFlag != C_PowerOn)/*���Ŀ����Ϣ�����¼��ж���Ϣ���˳�*/
    {
       return;
    }
    if(pStr_Msg->DerictAddr != C_Msg_PowerNetworkMonitoring)/*���Ŀ����Ϣ�����¼��ж���Ϣ���ж��Ƿ�㲥����*/
    {
        if(pStr_Msg->DerictAddr == C_Msg_BroadcastAddress)  /*������壬���¼�ȫ�崦��*/
        {
            if(*pStr_Msg->Parameter == Pt_MeterClear)
            {
                V_ucEventNo = C_AllEventNo;
                SF_EventClear_Judgemsg(V_ucEventNo);		/*���㺯��*/
            }
            return;
        }
        return;
    }
    if(pStr_Msg->SourceAddr == C_Msg_Dispatch)/*ϵͳ����*/
    {
        if(*(pStr_Msg->Parameter) == Pt_Dispatch_Timing)			/*ʱ�ӱ仯*/
        {
            if(*((pStr_Msg->Parameter) + 1) == C_SystemSecondChange)	/*ϵͳ��仯*/
            {
                SF_Judge_Event_Msg();				/*�¼��ж�*/

                SF_RenewalData_Judgemsg();		/*�¼����������е�ʵʱ��*/

                SF_AlarmDisplay_Judgemsg();             /*��������*/

				SF_SymbolDisplay_Judgemsg();	/*������ʾ����*/

				SF_MeterStatus_Judgemsg();		/*д�������״̬��*/

				SF_CalAddTime_Judgemsg();/*�����ۼ�ʱ��*/
            }
            else
            {
                return;
            }
        }
        else
        {
            return;
        }
    }
    else
    {
        if(pStr_Msg->SourceAddr == C_Msg_Communication)	/*ͨ��*/
        {
            if(*pStr_Msg->Parameter == Pt_EventClearDI)
            {
                PF_BufferXToUlong32(pStr_Msg->Parameter + 1, &V_ulDataCode, C_DataCode_Length);
                if(V_ulDataCode == 0xFFFFFFFF)
                {
                    V_ucEventNo = C_AllEventNo;
                }
                else
                {
                    V_ucEventNo = InF_EventNumFind(V_ulDataCode);/*��ȡEventNo*/
                    if(V_ucEventNo > C_NeutralCurrentAbnormalEventNo)
                    {
                        return;
                    }
                }
                SF_EventClear_Judgemsg(V_ucEventNo);		/*���㺯��*/
            }
        }
        else
        {
            if(pStr_Msg->SourceAddr == C_Msg_PowerNetworkMonitoring)		/*�¼��ж���Ϣ*/
            {
                SF_Write_EventMsgFuction(pStr_Msg);					/*�¼�д����*/
            }
            else
            {
				return;
            }
        }
    }
}
/***********************************************************************************
����ԭ�ͣ�void SF_Sub_Sec(uchar8 V_ucSec1, uchar8 V_ucSec2, ulong32 *V_ulSubMins)
���������������������
���������V_ucSec1 ��һ������
          V_ucSec2 �ڶ�������
���������V_ulSubMins �������(Hex��ʽ)
���ز�����
����˵����
���û��ƣ�
��    ע��
***********************************************************************************/
void SF_Sub_Sec(uchar8 V_ucSec1, uchar8 V_ucSec2, ulong32 *V_ulSubMins)
{
	if(V_ucSec1 >= V_ucSec2)
	{
		*V_ulSubMins = V_ucSec1 - V_ucSec2;
	}
	else
	{
		*V_ulSubMins = V_ucSec1 + 60 - V_ucSec2;
	}
}

/***********************************************************************************
����ԭ�ͣ�ulong32    Inf_GetEventModeDI(uchar8 EventLine, uchar8 OADType)
���������������кŻ�ȡ�¼������ϱ�ģʽ��
���������EventLine  �к�
          OADType   ��ȡ�ı�־�����ϱ�ģʽ�ֻ����ϱ����ͣ�C_ReportMode ��ȡ�ϱ�ģʽ�֣�C_ReportType ��ȡ�ϱ�����


���������ushort16 *V_Data_Length���������ݳ���
���ز�����C_OK��C_Error
����˵����
���û��ƣ�
��    ע��
***********************************************************************************/
ulong32    Inf_GetEventModeDI(uchar8 EventLine, uchar8 OADType)
{
    uchar8 V_Nature;
    ulong32 V_EventModeDI;
    if(C_ReportMode == OADType)/*�ϱ�ģʽ�֣��Ƿ��ϱ�*/
    {
      if(((uchar8)(Str_698EventReport[EventLine].OIBANature)) == 0x02)
      {
          V_Nature = 0x08;
      }
      else
      {
          V_Nature = 0x0B;
      }
    }
    else                        /*�ϱ����ͣ������ϱ����Ǹ����ϱ�*/
    {
      if(((uchar8)(Str_698EventReport[EventLine].OIBANature)) == 0x02)
      {
          V_Nature = 0x0B;
      }
      else
      {
          V_Nature = 0x0F;
      }
    }

    V_EventModeDI = (((((0x00003000)|(((uchar8)(Str_698EventReport[EventLine].OIBANature>>8))))<<8)|V_Nature)<<8);
    return V_EventModeDI;
}
/*******************************************************************************
����ԭ�ͣ�void Inf_EventReport_HP(uchar8 EventNo, uchar8 State)
�����������¼�����ʱд�����ϱ����
���������EventNo���¼��� State��C_Happen_EventMsg �¼�����������C_End_EventMsg �¼��ָ�����
���������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
void Inf_EventReport_HP(uchar8 EventNo, uchar8 State)
{
	uchar8	V_ucMode, V_uci, V_ucPowerOffReportType = 0;
	ulong32 V_ulEventOAD;
    uchar8 V_ucMeterReportParameter = C_MeterReportClose, V_ucReturn = C_Error;
    ushort16 V_usDataLen, V_usEncode;

    for(V_uci = 0 ; V_uci < Str_698EventReport_Len ; V_uci++ )		/*ȷ����Ӧ�¼�*/
    {
        if(EventNo == Str_698EventReport[V_uci].EventNo)
        {
            break;
        }
    }
    if(V_uci >= Str_698EventReport_Len)
    {
        return;
    }

    V_usDataLen = CLLossVolage_Report_Mode;

    V_ulEventOAD = Inf_GetEventModeDI(V_uci, C_ReportMode);
    if( C_OK != InF_GetData_ObjectManage(V_ulEventOAD, &V_ucMode, &V_usDataLen , &V_usEncode) )		/*��ģʽ��*/
    {
        V_ucMode = C_ReportNull;								            /*Ĭ�ϲ��ϱ�*/
    }

    if( ( ( State == C_Happen_EventReport ) && ( ( V_ucMode == C_ReportHP ) || ( V_ucMode == C_ReportAll ) ) )			/*ģʽ��Ҫ�ϱ�*/
     || ( ( ( State == C_End_EventReport ) && ( ( EventNo < C_ProgramEventNo ) || ( EventNo == C_RelayFaEndEnEventNo ) ) ) &&( ( V_ucMode == C_ReportEed ) || ( V_ucMode == C_ReportAll ) ) ) )
    {
        if ( ( EventNo == C_PowerfailEventNo ) )   /*������������ϱ����ڵ͹����·����ģ���ô�Ͳ�д�ϱ����͹������Ѿ�д����*/
        {
            V_usDataLen = CLReport_Type;
            V_ucReturn = InF_GetData_ObjectManage( CPowerOff_Report_Type, &V_ucPowerOffReportType, &V_usDataLen, &V_usEncode);
            if( ( V_ucReturn == C_OK ) && ( V_ucPowerOffReportType  == C_ActiveReportType ) )
            {
                if ( GStr_PowerfailStr.MeterState == C_Happen_EventMsg ) /*�����ڵ͹����·���*/
                {
                    return;
                }

                if( ( Inf_SatisfyPowerOnTime() != C_OK ) )          /*����ϵ粻��1Сʱ���ߵ��ܱ�û�п����ϱ������ϱ�*/
                {
                    return;
                }
                if(State == C_Happen_EventReport)
                {
                    V_ucMeterReportParameter = Inf_MeterReportOpen(C_PowerOn, C_FirstNo);
                    if( ( InF_ValtageType() == C_OK) && ( V_ucMeterReportParameter == C_MeterReportOpen ) )      /*��ѹ����Ϊֱ�ӽ���ʽ*/
                    {
                        Inf_Event_REPORTONumDeal(C_NewReportFlag);                                  /*���緢��ֻд����*/
                    }
                    return;
                }
            }
        }
        Inf_ReportList(C_ReportChannelAll, EventNo, C_NewReport);
    }
}

#if(_DEBUG_DB)
/***************************************************************************************************************
����ԭ�ͣ�uchar8 Inf_GetEventData(uchar8 *V_Data, ushort16 *V_Data_Length, ulong32 V_OADTab, uchar8 V_ucEvent_Flag)
������������ȡ�¼���¼����
���������uchar8 *V_Data���������Ż���
          ushort16 *V_Data_Length����Ϊ���룬���������ó���
          ulong32 V_OADTab���¼�����OAD��ű�
          uchar8 V_Event_Flag���¼�����������־��0x01������0x02����
���������ushort16 *V_Data_Length���������ݳ���
���ز�����C_OK��C_Error
����˵����
����λ�ã�
��    ע��
****************************************************************************************************************/
uchar8 Inf_GetEventData(uchar8 *V_Data, ushort16 *V_Data_Length, ulong32 V_OADTab, uchar8 V_ucEvent_Flag)
{
    uchar8 V_ucTurn, V_uci= 0, V_uc645DINum;
	ushort16 V_usOADTab_Length;
	uchar8 P_Data_Length, DataLen;
	ushort16 V_usOAD[60], V_usOAD_Data, V_usOAD_State;
	ulong32 V_ul698OAD;
	ushort16 V_usOffset = 0;
	uchar8 V_ucType;
	ulong32 V_ulReadBuff[3] = {0};
	ushort16 V_usBuffMaxLen;
	uchar8 V_DataBuff[1024] = {0};
	uchar8 V_Relay_Data[13];
    ulong32 V32_i;
    uchar8	V_Buff_Zero[9] = {0};
    uchar8 V_ucLen_Temp;

	V_usOADTab_Length = 120;
	if(InF_ReadOADTab_Data(V_OADTab, (uchar8 *)&V_usOAD, &V_usOADTab_Length) != C_OK)
	{
		return C_Error;
	}

	V_usBuffMaxLen = *V_Data_Length;

	/*����OAD��˳����֯����*/
	for( V_ucTurn = 0; V_ucTurn < (V_usOADTab_Length / 2); V_ucTurn++)
	{
		V_usOAD_Data = V_usOAD[V_ucTurn] & 0x1FFF;
		V_usOAD_State = V_usOAD[V_ucTurn] >> 13;

		if(V_usOAD_Data > Str_FrozenConvert_Table_Len)
		{
			return C_Error;
		}

		V_ul698OAD = Str_FrozenConvert_Table[V_usOAD_Data].V_ulOAD;
		P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data].V_uc645Length;
		V_ucType = Str_FrozenConvert_Table[V_usOAD_Data].V_uc698Type;
		V_uc645DINum = Str_FrozenConvert_Table[V_usOAD_Data].V_uc698NextNum;

		if ( ( ( V_ucEvent_Flag & 0x0C ) == 0x04 )
          && ( ( V_usOAD_State == 0x0003 ) || ( V_usOAD_State == 0x0004 ) ) )
		{
			memset((V_DataBuff + V_usOffset), 0xAA, P_Data_Length);
			V_usOffset += P_Data_Length;
		}
		else if ( ( V_ul698OAD == CKey_State )
               && ( V_usOAD_State == 0x0001 )
			   && ( V_OADTab == CProgKD_OADTab ) )                 /*����ǰ��Կ״̬*/
        {
			if((V_ucEvent_Flag & 0x03) == 0x01)
			{
            	PF_CopyDataBytes(GV_KeyHState, (V_DataBuff + V_usOffset), CLKey_State_698);
			}
			V_usOffset += CLKey_State_698;
        }
		else if ( ( ( V_ul698OAD & 0xff000000 ) == 0x00000000 )    /*����*/
			    || ( V_ul698OAD == 0x202D0200 )                     /*͸֧���*/
                || ( ( V_ul698OAD & 0xFFFF0000 ) == 0x20310000 )    /*�¶��õ���*/
                || ( V_ul698OAD == 0x202C0201 )                     /*ʣ����*/
                || ( ( V_ul698OAD & 0xFFFF0000) == 0x20320000 ) )   /*���ݽ����õ���*/
		{
			if( V_ucType == C_array)    /*��Ҫ�����645��ʶ��*/
			{
				for( V_uci = 1; V_uci <= V_uc645DINum; V_uci++)
				{
					V_ul698OAD = Str_FrozenConvert_Table[V_usOAD_Data + V_uci].V_ulOAD;
					P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data + V_uci].V_uc645Length;
					if ( ( ( ( V_usOAD_State == 0x0001 ) || ( V_usOAD_State == 0x0002 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x01 ) )
                      || ( ( ( V_usOAD_State == 0x0003 ) || ( V_usOAD_State == 0x0004 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x02 ) ) )
					{
						if(InF_ReadEnergy_Protocol(V_ul698OAD, (V_DataBuff + V_usOffset), &P_Data_Length, C_Format_HEX) == C_OK)   /*��ȡ����*/
						{
							V_usOffset += P_Data_Length;
						}
						else
						{
							P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data + V_uci].V_uc645Length;
							memset((V_DataBuff + V_usOffset), 0xAA, P_Data_Length);
							V_usOffset += P_Data_Length;
						}
					}
					else
					{
						V_usOffset += P_Data_Length;
					}
				}
			}
			else
			{
				if ( ( ( ( V_usOAD_State == 0x0001 ) || ( V_usOAD_State == 0x0002 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x01 ) )
                  || ( ( ( V_usOAD_State == 0x0003 ) || ( V_usOAD_State == 0x0004 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x02 ) ) )
				{
					if(InF_ReadEnergy_Protocol(V_ul698OAD, (V_DataBuff + V_usOffset), &P_Data_Length, C_Format_HEX) == C_OK)     /*��ȡ����*/
					{
						V_usOffset += P_Data_Length;
					}
					else
					{
						P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data].V_uc645Length;
						memset((V_DataBuff + V_usOffset), 0xAA, P_Data_Length);
						V_usOffset += P_Data_Length;
					}
				}
				else
				{
					V_usOffset += P_Data_Length;
				}
			}
		}
		else if ( V_ul698OAD == 0x202C0200 )       /*Ǯ���ļ�*/
		{
			if ( ( ( ( V_usOAD_State == 0x0001 ) || ( V_usOAD_State == 0x0002 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x01 ) )
              || ( ( ( V_usOAD_State == 0x0003 ) || ( V_usOAD_State == 0x0004 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x02 ) ) )
			{
				V_ul698OAD = Str_FrozenConvert_Table[V_usOAD_Data + 1].V_ulOAD;
				P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data + 1].V_uc645Length;
				if(InF_ReadEnergy_Protocol(V_ul698OAD, (V_DataBuff + V_usOffset), &P_Data_Length, C_Format_BCD) == C_OK)    /*��ȡ����*/
				{
					V_usOffset += P_Data_Length;
				}
				else
				{
					P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data + 1].V_uc645Length;
					memset((V_DataBuff + V_usOffset), 0xAA, P_Data_Length);
					V_usOffset += P_Data_Length;
				}
				V_ul698OAD = Str_FrozenConvert_Table[V_usOAD_Data + 2].V_ulOAD;
				P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data + 2].V_uc645Length;

				/*��ESAM�еĹ������*/
				PF_BufferXToUlong32(&V_DataBuff[V_usOffset], &V32_i, 4);

				if( InF_S_GetPPNum( &V32_i ) == C_OK )
				{
					PF_Ulong32ToBufferX(&V_DataBuff[V_usOffset], &V32_i, 4);
					V_usOffset += P_Data_Length;
				}
				else
				{
					memset( (V_DataBuff + V_usOffset), 0xAA, P_Data_Length );
					V_usOffset += P_Data_Length;
				}
			}
			else
			{
				V_usOffset += P_Data_Length;
			}
		}
		else if ( V_ul698OAD == 0x202C0202 )       /*�������*/
		{
            /*��ESAM�еĹ������*/
			if ( ( ( ( V_usOAD_State == 0x0001) || ( V_usOAD_State == 0x0002 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x01 ) )
              || ( ( ( V_usOAD_State == 0x0003) || ( V_usOAD_State == 0x0004 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x02 ) ) )
			{
				PF_BufferXToUlong32(&V_DataBuff[V_usOffset], &V32_i, 4);
				if(InF_S_GetPPNum( &V32_i ) == C_OK)
				{
					/*hex��ʽת����BCD��ʽ*/
					DataLen = 4;
					PF_HextoBCDBytes(&V32_i, &V_DataBuff[V_usOffset], &DataLen);
					V_usOffset += P_Data_Length;
				}
				else
				{
					memset((V_DataBuff + V_usOffset), 0xAA, P_Data_Length);
					V_usOffset += P_Data_Length;
				}
			}
			else
			{
				V_usOffset += P_Data_Length;
			}
		}
		else if ( ( ( V_ul698OAD & 0xff000000 ) == 0x10000000 )
                || ( ( V_ul698OAD & 0xff000000 ) == 0x11000000 ) )   /*����*/
		{
			if( V_ucType == C_array)       /*��Ҫ�����645��ʶ��*/
			{
				for( V_uci = 1; V_uci <= V_uc645DINum; V_uci++)
				{
					V_ul698OAD = Str_FrozenConvert_Table[V_usOAD_Data + V_uci].V_ulOAD;
					P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data + V_uci].V_uc645Length;

					if ( ( ( ( V_usOAD_State == 0x0001 ) || ( V_usOAD_State == 0x0002 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x01 ) )
                      || ( ( ( V_usOAD_State == 0x0003 ) || ( V_usOAD_State == 0x0004 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x02 ) ) )
					{
						if ( InF_ReadDemand(V_ul698OAD, (V_DataBuff + V_usOffset), P_Data_Length) == C_OK )   /*��ȡ��������*/
						{
							V_usOffset += P_Data_Length;
						}
				 	 	else
						{
							P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data+V_uci].V_uc645Length;
							memset((V_DataBuff + V_usOffset), 0xAA, P_Data_Length);
							V_usOffset += P_Data_Length;
						}
					}
					else
					{
						V_usOffset += P_Data_Length;
					}
				}
			}
			else
			{
				if ( ( ( ( V_usOAD_State == 0x0001 ) || ( V_usOAD_State == 0x0002 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x01 ) )
                  || ( ( ( V_usOAD_State == 0x0003 ) || ( V_usOAD_State == 0x0004 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x02 ) ) )
				{
					if (InF_ReadDemand(V_ul698OAD, (V_DataBuff + V_usOffset), P_Data_Length) == C_OK)     /*��ȡ��������*/
					{
						V_usOffset += P_Data_Length;
					}
			 	 	else
					{
						P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data].V_uc645Length;
						memset((V_DataBuff + V_usOffset), 0xAA, P_Data_Length);
						V_usOffset += P_Data_Length;
					}
				}
				else
				{
					V_usOffset += P_Data_Length;
				}
			}
		}
		else if ( ( V_ul698OAD & 0xffff0000 ) == 0x20290000 )       /*��ʱ��*/
		{
			switch(V_ucEvent_Flag & 0xF0)
			{
				case	0x10:
						V_ulReadBuff[0] = CLossAVol_FF_1;
						break;
				case	0x20:
						V_ulReadBuff[0] = CLossBVol_FF_1;
						break;
				case	0x30:
						V_ulReadBuff[0] = CLossCVol_FF_1;
						break;
				case	0x40:
						V_ulReadBuff[0] = CLowAVol_FF_1;
						break;
				case	0x50:
						V_ulReadBuff[0] = CLowBVol_FF_1;
						break;
				case	0x60:
						V_ulReadBuff[0] = CLowCVol_FF_1;
						break;
				case	0x70:
						V_ulReadBuff[0] = COverAVol_FF_1;
						break;
				case	0x80:
						V_ulReadBuff[0] = COverBVol_FF_1;
						break;
				case	0x90:
						V_ulReadBuff[0] = COverCVol_FF_1;
						break;
				case	0xA0:
						V_ulReadBuff[0] = CBreakAVol_FF_1;
						break;
				case	0xB0:
						V_ulReadBuff[0] = CBreakBVol_FF_1;
						break;
				case	0xC0:
						V_ulReadBuff[0] = CBreakCVol_FF_1;
						break;
				default:
						break;
			}
			if(V_ucType == C_array)     /*��Ҫ�����645��ʶ��*/
			{
				for( V_uci = 1; V_uci <= V_uc645DINum; V_uci++)
				{
					V_ul698OAD = Str_FrozenConvert_Table[V_usOAD_Data+V_uci].V_ulOAD;
					P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data+V_uci].V_uc645Length;

					if ( ( ( ( V_usOAD_State == 0x0001 ) || ( V_usOAD_State == 0x0002 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x01 ) )
                      || ( ( ( V_usOAD_State == 0x0003 ) || ( V_usOAD_State == 0x0004 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x02 ) ) )
					{
						V_ulReadBuff[1] = V_ul698OAD;
						V_ulReadBuff[1] |= (ulong32)(V_usOAD_State << 13);
						V_ulReadBuff[2] = 0xFFFFFFFF;

						if( Inf_ReadEventRenew(V_ulReadBuff, (V_DataBuff + V_usOffset), &P_Data_Length) == C_OK )    /*��ȡ����*/
						{
							V_usOffset += P_Data_Length;
						}
						else
						{
							P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data+V_uci].V_uc645Length;
							memset((V_DataBuff + V_usOffset), 0xAA, P_Data_Length);
							V_usOffset += P_Data_Length;
						}
					}
					else
					{
						V_usOffset += P_Data_Length;
					}
				}
			}
			else
			{
				if ( ( ( ( V_usOAD_State == 0x0001 ) || ( V_usOAD_State == 0x0002 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x01 ) )
                  || ( ( ( V_usOAD_State == 0x0003 ) || ( V_usOAD_State == 0x0004 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x02 ) ) )
				{
					V_ulReadBuff[1] = V_ul698OAD;
					V_ulReadBuff[1] |= (ulong32)(V_usOAD_State << 13);
					V_ulReadBuff[2] = 0xFFFFFFFF;

					if(Inf_ReadEventRenew(V_ulReadBuff, V_DataBuff+V_usOffset, &P_Data_Length) == C_OK)     /*��ȡ����*/
					{
						V_usOffset += P_Data_Length;
					}
					else
					{
						P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data].V_uc645Length;
						memset((V_DataBuff + V_usOffset), 0xAA, P_Data_Length);
						V_usOffset += P_Data_Length;
					}
				}
				else
				{
					V_usOffset += P_Data_Length;
				}
			}
		}
		else if ( ( V_ul698OAD & 0xffff0000 ) == 0x20260000 )       /*��ѹ��ƽ��*/
		{
			if((V_ucEvent_Flag & 0xF0) == 0xD0)
			{
				V_ulReadBuff[0] = CNoBalVol_FF_1;
			}
			if ( ( ( ( V_usOAD_State == 0x0001 ) || ( V_usOAD_State == 0x0002 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x01 ) )
              || ( ( ( V_usOAD_State == 0x0003 ) || ( V_usOAD_State == 0x0004 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x02 ) ) )
			{
				V_ulReadBuff[1] = V_ul698OAD;
				V_ulReadBuff[1] |= (ulong32)(V_usOAD_State << 13);
				V_ulReadBuff[2] = 0xFFFFFFFF;

				if(Inf_ReadEventRenew(V_ulReadBuff, (V_DataBuff + V_usOffset), &P_Data_Length) == C_OK)   /*��ȡ����*/
				{
					V_usOffset += P_Data_Length;
				}
				else
				{
					P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data].V_uc645Length;
					memset((V_DataBuff + V_usOffset), 0xAA, P_Data_Length);
					V_usOffset += P_Data_Length;
				}
			}
			else
			{
				V_usOffset += P_Data_Length;
			}
		}
		else if ( ( V_ul698OAD & 0xffff0000) == 0x20270000 )        /*������ƽ��*/
		{
			if((V_ucEvent_Flag & 0xF0) == 0xE0)
			{
				V_ulReadBuff[0] = CNoBalCurr_FF_1;
			}
			else if((V_ucEvent_Flag & 0xF0) == 0xF0)
			{
				V_ulReadBuff[0] = CSevNoBalCurr_FF_1;
			}
			if ( ( ( ( V_usOAD_State == 0x0001 ) || ( V_usOAD_State == 0x0002 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x01 ) )
              || ( ( ( V_usOAD_State == 0x0003 ) || ( V_usOAD_State == 0x0004 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x02 ) ) )
			{
				V_ulReadBuff[1] = V_ul698OAD;
				V_ulReadBuff[1] |= (ulong32)(V_usOAD_State << 13);
				V_ulReadBuff[2] = 0xFFFFFFFF;

				if(Inf_ReadEventRenew(V_ulReadBuff, V_DataBuff+V_usOffset, &P_Data_Length) == C_OK)     /*��ȡ����*/
				{
					V_usOffset += P_Data_Length;
				}
				else
				{
					P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data].V_uc645Length;
					memset((V_DataBuff + V_usOffset), 0xAA, P_Data_Length);
					V_usOffset += P_Data_Length;
				}
			}
			else
			{
				V_usOffset += P_Data_Length;
			}
		}
		else if ( ( V_ul698OAD == CFirst_TZone_Data )
                || ( V_ul698OAD == CSec_TZone_Data )
				|| ( V_ul698OAD == CCurrent_Ladder_Table )
                || ( V_ul698OAD == CBackUp_Ladder_Table ) )
		{
			if ( ( ( ( V_usOAD_State == 0x0001 ) || ( V_usOAD_State == 0x0002 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x01 ) )
              || ( ( ( V_usOAD_State == 0x0003 ) || ( V_usOAD_State == 0x0004 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x02 ) ) )
			{
				if(InF_Read_Data(V_ul698OAD, (V_DataBuff + V_usOffset), &P_Data_Length) == C_OK)
				{
					V_usOffset += P_Data_Length;
				}
				else
				{
					P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data].V_uc645Length;
					memset((V_DataBuff + V_usOffset), 0xAA, P_Data_Length);
					V_usOffset += P_Data_Length;
				}
			}
			else
			{
				V_usOffset += P_Data_Length;
			}
		}
		else if ( ( V_ul698OAD == CVolA_Per_Pass_0_Freeze )
                || ( V_ul698OAD == CVolA_Per_Pass_0 )
                || ( V_ul698OAD == CVolB_Per_Pass_0_Freeze )
                || ( V_ul698OAD == CVolB_Per_Pass_0 )		   /*��ѹ�ϸ��ʺͽ����շ������⴦��*/
			    || ( V_ul698OAD == CVolC_Per_Pass_0_Freeze )
                || ( V_ul698OAD == CVolC_Per_Pass_0 )
                || ( V_ul698OAD == CSettle_Day1 )
                || ( V_ul698OAD == CSettle_Day2 )
                || ( V_ul698OAD == CSettle_Day3 ) )
		{
			if ( ( ( ( V_usOAD_State == 0x0001 ) || ( V_usOAD_State == 0x0002 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x01 ) )
              || ( ( ( V_usOAD_State == 0x0003 ) || ( V_usOAD_State == 0x0004 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x02 ) ) )
			{
				if(InF_Read_Data(V_ul698OAD, (V_DataBuff + V_usOffset), &P_Data_Length) == C_OK)
				{
					V_usOffset += P_Data_Length;
				}
				else
				{
					P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data].V_uc645Length;
					memset((V_DataBuff + V_usOffset), 0xAA, P_Data_Length);
					V_usOffset += P_Data_Length;
				}
			}
			else
			{
				V_usOffset += P_Data_Length;
			}
		}
		else if ( V_ul698OAD == C_RelayFa_State )                   /*���ɿ���״̬*/
		{
			if ( ( ( ( V_usOAD_State == 0x0001 ) || ( V_usOAD_State == 0x0002 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x01 ) )
              || ( ( ( V_usOAD_State == 0x0003 ) || ( V_usOAD_State == 0x0004 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x02 ) ) )
			{
				Inf_Get_ApplianceF205(V_ul698OAD, V_Relay_Data, &P_Data_Length);

                memcpy((V_DataBuff + V_usOffset), &V_Relay_Data[C_RelayDescrip_Offset], CLRelayDescrip);
                V_usOffset += CLRelayDescrip;

				V_DataBuff[V_usOffset] = V_Relay_Data[C_RelayCurrentState_Offset];
				V_usOffset += CLRelayCurrentState;

				V_DataBuff[V_usOffset] = V_Relay_Data[C_RelaySwitchNature_Offset];
				V_usOffset += CLRelaySwitchNature;

				V_DataBuff[V_usOffset] = V_Relay_Data[C_RelayWiringState_Offset];
				V_usOffset += CLRelayWiringState;
			}
			else
			{
				V_usOffset += P_Data_Length;
			}
		}
		else if ( ( V_ul698OAD == CPhaseFF_Curr )
		       && ( V_OADTab == CAll_Loss_Vol_OADTab )
			   && ( V_usOAD_State == 0x0001 )
			   && ( ( V_ucEvent_Flag & 0x03 ) == 0x01 ) )
		{
			if(PF_Campare_Data(GStr_TotalvoltageloseStr.NoVoltageCurrent, V_Buff_Zero, CLPhaseFF_Curr) != C_Equal)
			{
				PF_CopyDataBytes(GStr_TotalvoltageloseStr.NoVoltageCurrent, (V_DataBuff + V_usOffset), CLPhaseFF_Curr);
				V_usOffset += CLPhaseFF_Curr;
			}
			else
			{
				for( V_uci = 1; V_uci <= V_uc645DINum; V_uci++)
				{
					V_ul698OAD = Str_FrozenConvert_Table[V_usOAD_Data + V_uci].V_ulOAD;
					P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data + V_uci].V_uc645Length;
					if( InF_Read_Data(V_ul698OAD, (V_DataBuff + V_usOffset), &P_Data_Length) == C_OK )
					{
						V_usOffset += P_Data_Length;
					}
					else
					{
						P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data + V_uci].V_uc645Length;
						memset((V_DataBuff + V_usOffset), 0xAA, P_Data_Length);
						V_usOffset += P_Data_Length;
					}
				}
			}
		}
		else
		{
			if ( ( V_ucType == C_array ) || ( ( V_ucType == C_structure ) && ( V_uc645DINum != 1 ) ) )    /*��Ҫ�����(��ѹ�ϸ��ʺͽ����շ���ǰ�������⴦��)*/
			{
				for( V_uci = 1; V_uci <= V_uc645DINum; V_uci++)
				{
					V_ul698OAD = Str_FrozenConvert_Table[V_usOAD_Data + V_uci].V_ulOAD;
					P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data + V_uci].V_uc645Length;

					if ( ( ( ( V_usOAD_State == 0x0001 ) || ( V_usOAD_State == 0x0002 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x01 ) )
                      || ( ( ( V_usOAD_State == 0x0003 ) || ( V_usOAD_State == 0x0004 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x02 ) ) )
					{
						if((V_ul698OAD & 0xff000000) == 0x00000000)	  /*����*/
						{
							if(InF_ReadEnergy_Protocol(V_ul698OAD, (V_DataBuff + V_usOffset), &P_Data_Length, C_Format_HEX) == C_OK)    /*��ȡ����*/
							{
								V_usOffset += P_Data_Length;
							}
							else
							{
								P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data+V_uci].V_uc645Length;
								memset((V_DataBuff + V_usOffset), 0xAA, P_Data_Length);
								V_usOffset += P_Data_Length;
							}
						}
						else
						{
							if(InF_Read_Data(V_ul698OAD, (V_DataBuff + V_usOffset), &P_Data_Length) == C_OK)
							{
								V_usOffset += P_Data_Length;
							}
							else
							{
								P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data+V_uci].V_uc645Length;
                                if(V_ul698OAD == 0x20010204)
                                {
                                	P_Data_Length = 3;
                                }
								memset((V_DataBuff + V_usOffset), 0xAA, P_Data_Length);
								V_usOffset += P_Data_Length;
							}
						}
					}
					else
					{
						V_usOffset += P_Data_Length;
					}
				}
			}
			else
			{
				if ( ( ( ( V_usOAD_State == 0x0001 ) || ( V_usOAD_State == 0x0002 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x01 ) )
                  || ( ( ( V_usOAD_State == 0x0003 ) || ( V_usOAD_State == 0x0004 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x02 ) ) )
				{
                    if ( ( ( ( V_ul698OAD & 0xFFFFFF00 ) == CSec_TZone_Data ) && ( V_ul698OAD != CSec_TZone_Data ) )
                      || ( ( ( V_ul698OAD & 0xFFFFFF00 ) == CFirst_TZone_Data ) && ( V_ul698OAD != CFirst_TZone_Data ) ) )
                    {
                        V_ucLen_Temp = CLFirst_TZone_Data;
                        P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data].V_uc645Length;

                        if( InF_Read_Data( ( V_ul698OAD & 0xFFFFFF00 ), (V_DataBuff + V_usOffset), &V_ucLen_Temp) == C_OK )
                        {
                            V_DataBuff[V_usOffset] = V_DataBuff[V_usOffset + ( ((uchar8)(V_ul698OAD)) - 1) * 3];
                            V_DataBuff[V_usOffset + 1] = V_DataBuff[V_usOffset+( ((uchar8)(V_ul698OAD)) - 1 ) * 3 + 1];
                            V_DataBuff[V_usOffset + 2] = V_DataBuff[V_usOffset+( ((uchar8)(V_ul698OAD)) - 1 ) * 3 + 2];
                        }
                        else
                        {
							memset((V_DataBuff + V_usOffset), 0xAA, P_Data_Length);
							V_usOffset += P_Data_Length;
                        }
                        V_usOffset += P_Data_Length;
                    }
                    else
                    {
                        if(InF_Read_Data(V_ul698OAD, (V_DataBuff + V_usOffset), &P_Data_Length) == C_OK)
                        {
                            V_usOffset += P_Data_Length;
                        }
                        else
                        {
                            P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data].V_uc645Length;
    					    memset( (V_DataBuff + V_usOffset), 0xAA, P_Data_Length );
							V_usOffset += P_Data_Length;
                        }
                    }
				}
				else
				{
					V_usOffset += P_Data_Length;
				}
			}
		}
		if( (V_usOffset > V_usBuffMaxLen) || (V_usOffset > (1024 - 40) ) )	/*��󳤶Ȳ��ܳ�������Buff���Ⱥ�����Buff����*/
		{
			return	C_DataLenError;
		}
	}

	PF_CopyDataBytes_698(V_DataBuff, V_Data, V_usOffset);
	*V_Data_Length = V_usOffset;

	return C_OK;
}
#endif
/***********************************************************************************
����ԭ�ͣ�uchar8 Inf_ReadEventCurrentData_(ulong32 V_Data_Id, uchar8 *P_Data, uchar8 *P_Data_Length, V_Flag)
����������ͨ�Ŷ�ȡ�¼��ĵĵ�ǰֵ
���������
           V_Data_Id
           *P_Data                      ��������ָ��
           *P_Data_Length               ������P_Data��󳤶�
           V_Flag:V_Dgree:0x01;V_Time:0x02   ��������ʱ����ж�
��������� *P_Data                      �������ݣ�
           *P_Data_Length               �����ݵ�ʵ�ʳ���
���ز�����  C_IDError:��֧�ֶ�ȡ�����ݱ�ʶ��C_DataLenError���ݳ��ȴ�, C_OK:��ȷִ��
            InF_GetData_ObjectManage()���ܷ��ص��κ�ֵ
����˵����
���û��ƣ�ͨ�ŵ���
��    ע��*P_Data_Length������ڵ�����ȡֵ���ȣ���Ȼ���ش���  ����645����
***********************************************************************************/
uchar8 Inf_ReadEventCurrentData_JudgeDgreeOrTime(ulong32 V_ulData_Id, uchar8 *pV_ucData, uchar8 *pV_ucData_Length, uchar8 V_ucFlag)
{
	uchar8 V_ucReturn, V_uci;
    ulong32 V_ulData = 0, V_ulOAD[2];
    ushort16 V_usLen, V_usEncode;

    V_usLen = *pV_ucData_Length;

	switch(V_ucFlag)
	{
        case C_Degree:
            for(V_uci = 0;V_uci < CurrentDataReadTable_Len;V_uci ++)
            {
                if(V_ulData_Id == CurrentDataReadTable[V_uci].Degree)
                {
                    V_ucReturn = InF_GetData_ObjectManage(CurrentDataReadTable[V_uci].Degree, pV_ucData, &V_usLen, &V_usEncode);

                    *pV_ucData_Length = V_usLen;

                    if(V_ucReturn == C_OK)
                    {
                        *pV_ucData_Length -= 1;/*645����Ϊ��1�ֽ�*/
                    }
                    else
                    {
                        ;
                    }
                    break;
                }
            }
            if(V_uci >= CurrentDataReadTable_Len)
            {
                V_ucReturn = C_IDError;
            }
            break;

        case C_Time:
            for(V_uci=0;V_uci<CurrentDataReadTable_Len;V_uci++)
            {
                if(V_ulData_Id == CurrentDataReadTable[V_uci].AddTime)
                {
                    V_ulOAD[0] = CurrentDataReadTable[V_uci].AddTime;
                    V_ulOAD[1] = 0xFFFFFFFF;

                    V_ucReturn = Inf_ReadEventRenew(V_ulOAD, pV_ucData, pV_ucData_Length);
                    if(V_ucReturn == C_OK)
                    {
                        PF_BufferXToUlong32(pV_ucData, &V_ulData, *pV_ucData_Length);
                        V_ulData = V_ulData/60;/*�洢����Ϊs��hex 4�ֽڣ�ת��Ϊ�֣�BCD��3�ֽڣ�*/
                        if(V_ulData>0xF423F)
                        {
                            V_ulData = 0xF423F;
                        }
                        PF_HextoBCDBytes(&V_ulData, pV_ucData, pV_ucData_Length);
                        *pV_ucData_Length -= 1;
                    }
                    else
                    {
                        *pV_ucData_Length = 3;
                        memset(pV_ucData, 0x00, 3);
                    }
                    break;
                }
            }
            if(V_uci >= CurrentDataReadTable_Len)
            {
                V_ucReturn = C_IDError;
            }
            break;
        default:
            V_ucReturn = C_IDError;
        break;
	}
	return V_ucReturn;
}
/***********************************************************************************
����ԭ�ͣ�uchar8 Inf_ReadEventCurrentData_Com645(ulong32 V_Data_Id, uchar8 *P_Data, uchar8 *P_Data_Length)
����������ͨ�Ŷ�ȡ�¼��ĵĵ�ǰֵ
���������
           V_Data_Id
           *P_Data                      ��������ָ��
           *P_Data_Length               ������P_Data��󳤶�
           V_Flag                       �ж��������¼��Ĵ���
��������� *P_Data                      �������ݣ�
           *P_Data_Length               �����ݵ�ʵ�ʳ���
���ز�����  C_IDError:��֧�ֶ�ȡ�����ݱ�ʶ��C_DataLenError���ݳ��ȴ�, C_OK:��ȷִ��
            InF_GetData_ObjectManage()���ܷ��ص��κ�ֵ
����˵����
���û��ƣ�ͨ�ŵ���
��    ע��*P_Data_Length������ڵ�����ȡֵ���ȣ���Ȼ���ش���  ����645����
***********************************************************************************/
const	Str_EventTable_645ChangeTo698	TB_Str_EventTable_645ChangeTo698[] =
{
//  DI                                  OAD                 DILen
  {C_LossVol_Tol_Dgree_645,             CLoss_Vol_Degree,    (CLLoss_Vol_Degree-1)},
  {C_LossVol_Tol_Time_645,              CLoss_Vol_Time,      (CLLoss_Vol_Time-1)},
  {C_LossVol_Recent_HappenTime_645,     CLoss_Vol_Hp,        (CLLoss_Vol_Hp-1)},
  {C_LossVol_Recent_EndTime_645,        CLoss_Vol_End,       (CLLoss_Vol_End-1)},
};
#define TB_Str_EventTable_645ChangeTo698Len  (sizeof(TB_Str_EventTable_645ChangeTo698)/sizeof(Str_EventTable_645ChangeTo698))
uchar8 Inf_ReadEventCurrentData_Com645(ulong32 V_Data_Id, uchar8 *P_Data, uchar8 *P_Data_Length, uchar8 V_Flag)
{
	uchar8	V_ucLen, V_uci;
	uchar8  V_ucReturn, V_ucDataBuffer[CLAll_Loss_Vol_Current];
	ulong32 V_DataTemp[2];
	ulong32	V_Event_Num;
	V_ucLen = CLLoss_Vol_Hp;
    uchar8  V_TempBuff[CLAll_Loss_Vol_Current];

    if(V_Flag == C_Flag03)
    {
      if(V_Data_Id == 0x03050000)
      {
        V_DataTemp[0] = CAll_Loss_Vol_Current;
        V_DataTemp[1] = 0xFFFFFFFF;
        V_ucLen = CLAll_Loss_Vol_Current;
        V_ucReturn = Inf_ReadEventCurrentData(V_DataTemp[0], V_ucDataBuffer, &V_ucLen);
        if(V_ucReturn == C_OK)
		{
            PF_CopyDataBytes(V_ucDataBuffer, V_TempBuff, V_ucLen);
            //ȫʧѹ����
            PF_CopyDataBytes(&V_TempBuff[1], &V_ucDataBuffer[0], 3);//ȫʧѹ����
            //ȫʧѹ�ۼ�ʱ��
            PF_CopyDataBytes(&V_TempBuff[5], &V_ucDataBuffer[3], 4);//ȫʧѹ����
            PF_BufferXToUlong32(&V_ucDataBuffer[3], &V_Event_Num, 4);
            V_Event_Num = V_Event_Num/60;//�洢����Ϊs��hex 4�ֽڣ�ת��Ϊ�֣�BCD��3�ֽڣ�
            if(V_Event_Num>0xF423F)
            {
              V_Event_Num = 0xF423F;
            }
            V_ucLen = 3;//645�ۼ�ʱ��3�ֽ�
            PF_HextoBCDBytes(&V_Event_Num, &V_ucDataBuffer[3], &V_ucLen);
            V_ucLen = 3+3;//645�ۼƴ���3�ֽ�+�ۼ�ʱ��3�ֽ�
            PF_CopyDataBytes(V_ucDataBuffer, P_Data, V_ucLen);
		}

      }
      else
      {
        V_ucLen = CLLoss_Vol_Hp;
        V_ucReturn = Inf_ReadEventCurrentData_JudgeDgreeOrTime(V_Data_Id, P_Data, &V_ucLen, C_Degree);
      }
    }
    else if(V_Flag == C_Flag10)
    {
      if((V_Data_Id&0x00FF0000) != 0x00000000)  //DI2!=0
      {
        if((V_Data_Id&0x000000FF) == 0x00000001)///�����ܴ���
        {
          V_ucReturn = Inf_ReadEventCurrentData_JudgeDgreeOrTime(V_Data_Id, P_Data, &V_ucLen, C_Degree);
	    }
	    else if((V_Data_Id&0x000000FF) == 0x00000002)///�����ۼ�ʱ��
        {
         V_ucReturn = Inf_ReadEventCurrentData_JudgeDgreeOrTime(V_Data_Id, P_Data, &V_ucLen, C_Time);
        }
        else
        {
          V_ucReturn = C_IDError;
        }
      }
      else  //DI2=0
      {
        for(V_uci=0;V_uci<TB_Str_EventTable_645ChangeTo698Len;V_uci++)
        {
          if(V_Data_Id == TB_Str_EventTable_645ChangeTo698[V_uci].DI)
          {
            V_Data_Id = TB_Str_EventTable_645ChangeTo698[V_uci].OAD;
            break;
          }
        }
        if(V_uci<TB_Str_EventTable_645ChangeTo698Len)
        {
          V_DataTemp[0]=V_Data_Id;
          V_DataTemp[1]=0xFFFFFFFF;
          V_ucReturn = Inf_ReadEventRenew(V_DataTemp, V_ucDataBuffer, &V_ucLen);
          if(V_ucReturn==C_OK)
          {
            if(SF_JudgeAllAA(V_ucDataBuffer, V_ucLen) != C_OK)
            {
              if(V_Data_Id==CLoss_Vol_Time)
              {
				PF_BufferXToUlong32(V_ucDataBuffer, &V_Event_Num, V_ucLen);
                V_Event_Num = V_Event_Num/60;//�洢����Ϊs��hex 4�ֽڣ�ת��Ϊ�֣�BCD��3�ֽڣ�
                if(V_Event_Num>0xF423F)
                {
                  V_Event_Num = 0xF423F;
                }
                PF_HextoBCDBytes(&V_Event_Num, V_ucDataBuffer, &V_ucLen);

              }
            }
            else
            {
              memset(V_ucDataBuffer, 0x00, V_ucLen);
            }
            V_ucLen = TB_Str_EventTable_645ChangeTo698[V_uci].DILenth;
          }
          else
          {
              V_ucLen = TB_Str_EventTable_645ChangeTo698[V_uci].DILenth;
              memset(V_ucDataBuffer, 0x00, V_ucLen);
          }
          PF_CopyDataBytes(V_ucDataBuffer, P_Data, V_ucLen);

        }
        else
        {
          V_ucReturn = C_IDError;
        }
      }
  }
    else
    {
      if(((V_Data_Id&0x000000FF) == 0x00000001)||(CTrend_Rev_Degree == V_Data_Id))
      {
        if(CTrend_Rev_Degree == V_Data_Id)
        {
           V_Data_Id = CPowerT_Rev_Degree;
        }
        V_ucReturn = Inf_ReadEventCurrentData_JudgeDgreeOrTime(V_Data_Id, P_Data, &V_ucLen, C_Degree);
	  }
	  else if((V_Data_Id&0x000000FF) == 0x00000002)
      {
        V_ucReturn = Inf_ReadEventCurrentData_JudgeDgreeOrTime(V_Data_Id, P_Data, &V_ucLen, C_Time);
      }
      else
      {
        V_ucReturn = C_IDError;
      }
    }
   *P_Data_Length =  V_ucLen;
  return V_ucReturn;

}
/***********************************************************************************
����ԭ�ͣ�uchar8 Inf_ReadEventCurrentData(ulong32 V_ulData_Id, uchar8 *pV_ucData, uchar8 *pV_ucData_Length)
����������ͨ�Ŷ�ȡ�¼��ĵĵ�ǰֵ
���������
           V_ulData_Id
           *pV_ucData                      ��������ָ��
           *pV_ucData_Length               ������P_Data��󳤶�
��������� *pV_ucData                      �������ݣ�
           *pV_ucData_Length               �����ݵ�ʵ�ʳ���
���ز�����  C_IDError:��֧�ֶ�ȡ�����ݱ�ʶ��C_DataLenError���ݳ��ȴ�, C_OK:��ȷִ��
            InF_GetData_ObjectManage()���ܷ��ص��κ�ֵ
����˵����
���û��ƣ�ͨ�ŵ���
��    ע��*P_Data_Length������ڵ�����ȡֵ���ȣ���Ȼ���ش���
***********************************************************************************/
uchar8 Inf_ReadEventCurrentData(ulong32 V_ulData_Id, uchar8 *pV_ucData, uchar8 *pV_ucData_Length)
{
	uchar8	V_uci, V_ucj;
	uchar8	V_ucReturn, V_ucOffset;
	ushort16 V_usDatalength, V_usEncode;
	uchar8	V_ucData[20] = {0};
	uchar8	V_ucDataLen;
	ulong32	V_ulReadOAD[3];
	uchar8  V_ucFlag = 0;
	ulong32 V_ulEventAttri[5] = {0x00000001, 0x00000601, 0x00000701, 0x00000801, 0x00000901};

	for(V_uci = 0;V_uci < CurrentDataReadTable_Len;V_uci ++)
	{
		if(V_ulData_Id == CurrentDataReadTable[V_uci].EventOAD)
		{
            V_ucFlag = C_Type1;
			break;
		}
	}
    if(V_uci >= CurrentDataReadTable_Len)
    {
        for(V_uci = 0;V_uci < CurrentDataReadTable_Len;V_uci ++)
        {
            if( ((ushort16)V_ulData_Id == CurrentDataReadTable[V_uci].EventTimeStatus)
            	&&((V_ulData_Id&0xFFFF0000) == (CurrentDataReadTable[V_uci].EventOAD&0xFFFF0000)) )
            {
                V_ucFlag = C_Type2;
                break;
            }
        }
    }
    if(V_uci >= CurrentDataReadTable_Len)
    {
        return C_IDError;
    }
	V_ucOffset = 0;
	if(V_ucFlag == C_Type1)
	{
		if(CurrentDataReadTable[V_uci].Source != C_SourceNon)
		{
			V_ulReadOAD[0] = (V_ulData_Id & 0xFFFF0000) | 0x00000201;
			V_ulReadOAD[1] = CEventHPSource;
			V_ulReadOAD[2] = 0xFFFFFFFF;
			V_usDatalength = 20;

			V_ucReturn = SF_ReadLastEvt(V_ulReadOAD, V_ucData, &V_usDatalength, (uchar8)V_ulReadOAD[0]);
			if(V_ucReturn==C_OK)
			{
				V_ucOffset += (uchar8)V_usDatalength;
			}
			else if(C_NoData == V_ucReturn)
			{
				V_ucData[0] = 0;
				V_ucOffset += 1;
				V_ucReturn = C_OK;
			}
			else
			{
				return(V_ucReturn);
			}
		}
		V_usDatalength = 20 - V_ucOffset;
		V_ucReturn = InF_GetData_ObjectManage(CurrentDataReadTable[V_uci].Degree, V_ucData + V_ucOffset, &V_usDatalength, &V_usEncode);
		if(V_ucReturn == C_OK)
		{
			V_ucOffset += (uchar8)V_usDatalength;
		}
		else
		{
			return(V_ucReturn);
		}

		if(CurrentDataReadTable[V_uci].AddTime == C_NULL)
		{
			V_ucDataLen = 4;
			for(V_ucj = 0;V_ucj < V_ucDataLen;V_ucj ++)
			{
				*(V_ucData + V_ucOffset + V_ucj) = 0x00;
			}
			V_ucOffset += V_ucDataLen;
		}
		else
		{
			V_ulReadOAD[0] = CurrentDataReadTable[V_uci].AddTime;
			V_ulReadOAD[1] = 0xFFFFFFFF;
			V_ucDataLen = 20 - V_ucOffset;
			V_ucReturn = Inf_ReadEventRenew(V_ulReadOAD, V_ucData + V_ucOffset, &V_ucDataLen);
			if(V_ucReturn == C_OK)
			{
				V_ucOffset += V_ucDataLen;
			}
			else
			{
				return(V_ucReturn);
			}
		}
	}
	else if((V_ucFlag == C_Type2))
	{
		if(CurrentDataReadTable[V_uci].Source != C_SourceNon)
		{
			V_ulReadOAD[0] = (V_ulData_Id & 0xFFFF0000) | 0x00000201;
			V_ulReadOAD[1] = CEventHPSource;
			V_ulReadOAD[2] = 0xFFFFFFFF;
			V_usDatalength = 20;

			V_ucReturn = SF_ReadLastEvt(V_ulReadOAD, V_ucData, &V_usDatalength, (uchar8)V_ulReadOAD[0]);
			if(V_ucReturn == C_NoData)
			{
				V_ucData[0] = 0;
				V_usDatalength = 1;
				V_ucReturn = C_OK;
			}
			if(V_ucReturn == C_OK)
			{
				V_ucOffset += (uchar8)V_usDatalength;
			}
			else
			{
				return(V_ucReturn);
			}
		}
		if(CurrentDataReadTable[V_uci].Source != C_SourceNon)
		{
			V_ulReadOAD[0] = (V_ulData_Id & 0xFFFF0000) | 0x00000201;
		}
		else
		{
			V_ulReadOAD[0] = (V_ulData_Id & 0xFFFF0000) | V_ulEventAttri[(uchar8)V_ulData_Id];
		}
		V_ulReadOAD[1] = CEventHPTime;
		V_ulReadOAD[2] = 0xFFFFFFFF;
		V_usDatalength = 20;

		V_ucReturn = SF_ReadLastEvt(V_ulReadOAD, V_ucData+ V_ucOffset, &V_usDatalength, (uchar8)V_ulReadOAD[0]);

		if(V_ucReturn == C_NoData)
		{
			V_usDatalength = C_EventTimeLength;

			memset(V_ucData + V_ucOffset, 0xAA, C_EventTimeLength);
			V_ucReturn = C_OK;
		}
		if(V_ucReturn==C_OK)
		{
			V_ucOffset += (uchar8)V_usDatalength;
		}
		else
		{
			return(V_ucReturn);
		}
		if(CurrentDataReadTable[V_uci].Source != C_SourceNon)
		{
			V_ulReadOAD[0] = (V_ulData_Id & 0xFFFF0000) | 0x00000201;
		}
		else
		{
			V_ulReadOAD[0] = (V_ulData_Id & 0xFFFF0000) |V_ulEventAttri[(uchar8)V_ulData_Id];
		}
		V_ulReadOAD[1] = CEventEndTime;
		V_ulReadOAD[2] = 0xFFFFFFFF;
		V_usDatalength = 20;

		if(SF_Judge_EventIntegrity(CurrentDataReadTable[V_uci].EventNo)==C_Happen_EventState)		/*�����ʷ״̬���з����޻ָ�*/
		{
			V_ulReadOAD[0] += 1;
		}
		V_ucReturn = SF_ReadLastEvt(V_ulReadOAD, V_ucData+ V_ucOffset, &V_usDatalength, (uchar8)V_ulReadOAD[0]);

		if(V_ucReturn==C_NoData)
		{
			V_usDatalength = C_EventTimeLength;

			memset(V_ucData + V_ucOffset, 0xAA, C_EventTimeLength);
			V_ucReturn = C_OK;
		}
		if(V_ucReturn==C_OK)
		{
			V_ucOffset += (uchar8)V_usDatalength;
		}
		else
		{
			return(V_ucReturn);
		}
	}
	if(V_ucOffset > *pV_ucData_Length)
	{
		return	C_DataLenError;
	}

	PF_CopyDataBytes(V_ucData, pV_ucData, V_ucOffset);
	*pV_ucData_Length = V_ucOffset;

	return(V_ucReturn);
}

#if (_DEBUG_DB)
/**********************************************************************************************************
����ԭ�ͣ�uchar8 Inf_ReadEventLast_H(ulong32 V_Data_Id, uchar8 *P_Data, uchar8 *P_Data_Length)
����������ͨ�Ŷ�ȡ��һ���¼�
���������  *V_Data_Id��Ҫ��ȡ��OAD��V_Data_Id[1]Ϊ0xFFFFFFFF������ȡ��V_Data_Id[1]��Ϊ0xFFFFFFFFΪ��ѡ��ȡ
           *P_Data ��������ָ��
           *P_Data_Length ������P_Data��󳤶�
��������� *P_Data �������ݣ�
           *P_Data_Length �����ݵ�ʵ�ʳ���
���ز�����  C_IDError:��֧�ֶ�ȡ�����ݱ�ʶ��C_DataLenError���ݳ��ȴ�, C_OK:��ȷִ��
          InF_Read_Data()���ܷ��ص��κ�ֵ
����λ�ã�ͨ�ŵ���
��    ע��*P_Data_Length������ڵ�����ȡֵ���ȣ���Ȼ���ش���
***************************************************************************************************************/
uchar8 Inf_ReadEventLast_H(ulong32 *V_Data_OAD, uchar8 *P_Data, ushort16 *P_Data_Length, uchar8 V_timeFlash, uchar8 *pV_ucHappeningFlag)
{
	uchar8 V_ucTurn, V_uci, V_ucj, V_ucFixTime = 0, V_ucNextSign = 0;
	ushort16 V_usOADTab_Length, V_usDataLength;
	uchar8 V_Data_Length, V_ucReturn, V_ucOADFlag;
	ushort16 V_usOAD[C_EventMAXRelatedOAD], V_usOAD_Data, V_usOAD_State;
	ushort16 V_usOffset = 0;
	uchar8 i;
	ulong32 V_ulReadBuff[3] = {0};
	ushort16 V_usBuffMaxLen;
	uchar8 V_DataBuff[C_EventMAXLen] = {0};
	ushort16 V_usDataoffset = 0;
    uchar8 V_ucSpecicalDataLen = 0;
    uchar8 V_uck;
    uchar8 V_ucRateNum;

    Struct_FrozenConvert_Type Str_Encode;
    Struct_FrozenConvert_Type Str_EncodeNext;

	*pV_ucHappeningFlag = C_End_EventState;			/*Ĭ�ϲ�����*/
	for(V_uci = 0; V_uci < EventMappingTable_Len; V_uci++)
	{
		if(EventMappingTable[V_uci].WriteOAD == V_Data_OAD[0])
		{
			break;
		}
	}
	if(V_uci >= EventMappingTable_Len)
	{
		return C_OtherErr;
	}
	V_usDataLength = C_EventMAXLen;
	V_ucReturn = InF_ReadEventData(V_Data_OAD, &V_ucFixTime, V_DataBuff, &V_ucNextSign, &V_usDataLength, V_timeFlash);
	if(V_ucReturn != C_OK)
	{
		return V_ucReturn;
	}

    V_usOADTab_Length = C_EventMAXRelatedOADLen;
	if(InF_ReadOADTab_Data(EventMappingTable[V_uci].OADTab, (uchar8 *)&V_usOAD, &V_usOADTab_Length) != C_OK)
	{
		return C_Error;
	}

    /*�⼸���¼�һ��û�й����б�*/
	if ( ( ( V_Data_OAD[0] == CEven_Clear_Note_1 )
        || ( V_Data_OAD[0] == CProgram_Note_1 )
        || ( V_Data_OAD[0] == CProgPT_Note_1 )
        || ( V_Data_OAD[0] == CProgHol_Note_1 )
        || ( V_Data_OAD[0] == CAbnorC_Note_1)
        || ( V_Data_OAD[0] == CReturn_M_Note_1 ) )
       && ( V_usOADTab_Length == 0 ) )
	{
		PF_CopyDataBytes_698(V_DataBuff, P_Data, V_usDataLength);
		*P_Data_Length = V_usDataLength;
		return C_OK;
	}

/************************�ж��¼���¼��ǰ����״̬***************************/
	if( SF_Judge_EventIntegrity(EventMappingTable[V_uci].EventNo) == C_Happen_EventState )
	{
		*pV_ucHappeningFlag = C_Happen_EventState;			/*���ڷ���*/
	}

	V_usBuffMaxLen = *P_Data_Length;
	if( V_Data_OAD[1] == 0xFFFFFFFF )
	{

        V_usOffset += (CLEventDegree + CLEventHappenTime + CLEventEndTime);		/*�¼���š�����ʱ�䡢����ʱ��ƫ��*/
        V_usDataoffset += (CLEventDegree + CLEventHappenTime + CLEventEndTime);

        if( (*pV_ucHappeningFlag) == C_Happen_EventState )
        {
            memset((V_DataBuff + CLEventDegree + CLEventHappenTime), 0xAA, C_EventTimeLength);
        }

        if(EventMappingTable[V_uci].SourceFlag == C_SourceExist)
        {
            V_usOffset += CLEventSource;	 /*�¼�����Դƫ��*/
            V_usDataoffset += CLEventSource;
        }

        if ( ( V_Data_OAD[0] == CPos_Ac_De_Over_Note_1 )
          || ( V_Data_OAD[0] == CRev_Ac_De_Over_Note_1 )
          || ( V_Data_OAD[0] == CQua1_Re_De_Over_Note_1 )
          || ( V_Data_OAD[0] == CQua2_Re_De_Over_Note_1 )
          || ( V_Data_OAD[0] == CQua3_Re_De_Over_Note_1 )
          || ( V_Data_OAD[0] == CQua4_Re_De_Over_Note_1 ) )
        {
            if( (*pV_ucHappeningFlag) == C_Happen_EventState )		/*�����ʷ״̬���з����޻ָ�*/
            {
                switch(EventMappingTable[V_uci].EventNo)
                {
                    case	C_OverForwardActiveEventNo:
                            PF_CopyDataBytes(GStr_OverForwardActiveStr.Renewal, (V_DataBuff + V_usOffset), C_OverDemandRenew_Length);
                            break;
                    case	C_OverReverseActiveEventNo:
                            PF_CopyDataBytes(GStr_OverReverseActiveStr.Renewal, (V_DataBuff + V_usOffset), C_OverDemandRenew_Length);
                            break;
                    case	C_1OverIdleDemandEventNo:
                            PF_CopyDataBytes(GStr_Over1IdleDemandStr.Renewal, (V_DataBuff + V_usOffset), C_OverDemandRenew_Length);
                            break;
                    case	C_2OverIdleDemandEventNo:
                            PF_CopyDataBytes(GStr_Over2IdleDemandStr.Renewal, (V_DataBuff + V_usOffset), C_OverDemandRenew_Length);
                            break;
                    case	C_3OverIdleDemandEventNo:
                            PF_CopyDataBytes(GStr_Over3IdleDemandStr.Renewal, (V_DataBuff + V_usOffset), C_OverDemandRenew_Length);
                            break;
                    case	C_4OverIdleDemandEventNo:
                            PF_CopyDataBytes(GStr_Over4IdleDemandStr.Renewal, (V_DataBuff + V_usOffset), C_OverDemandRenew_Length);
                            break;
                    default:
                            break;
                }
            }
            V_usOffset += C_OverDemandRenew_Length;
            V_usDataoffset += C_OverDemandRenew_Length;
            PF_CopyDataBytes(V_DataBuff, P_Data, V_usDataoffset);
        }
        else
        {
            /*�����¼���¼��Ԫ���ݳ���ƫ��*/
            SF_Event_SpecificDataLenCal(V_Data_OAD[0], &V_ucSpecicalDataLen);
            V_usOffset += V_ucSpecicalDataLen;
            V_usDataoffset += V_ucSpecicalDataLen;
            PF_CopyDataBytes(V_DataBuff, P_Data, V_usDataoffset);
        }

		/*����OAD��˳����֯����*/
		for( V_ucTurn = 0; V_ucTurn < (V_usOADTab_Length / 2); V_ucTurn++)
		{
		    V_usOAD_Data = V_usOAD[V_ucTurn] & 0x1FFF;  /*���������б��е��к�*/
			V_usOAD_State = V_usOAD[V_ucTurn] >> 13;    /*�¼�����������*/

			if(V_usOAD_Data >= Str_FrozenConvert_Table_Len)
			{
				return C_Error;
			}

			V_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data].V_uc645Length;
            Str_Encode = Str_FrozenConvert_Table[V_usOAD_Data];
			SF_FrozenDataFF_NextNum(&Str_Encode, V_usOAD_Data);

            if((SF_FrozenData_JudgeRateNum(V_usOAD_Data, Str_Encode.V_ulOAD)) == C_Error)	    /*����������Ӧ��գ����ݲ㷵������0xBB*/
            {
                P_Data[V_usDataoffset] = C_NotSupportAOD_DataBB;
                V_usDataoffset += CL_NotSupportAOD_DataBB;
                V_usOffset += V_Data_Length;	/*ȫ�������ݳ���*/
            }
            else
            {
			    if(V_usOAD_State != 0x0003)       /*0x0003Ϊ�¼�����ǰ*/
			    {
				    if(V_usOAD_State == 0x0004)   /*0x0004Ϊ�¼�������*/
				    {
					    if( (*pV_ucHappeningFlag) == C_Happen_EventState)		/*�����ʷ״̬���з����޻ָ�*/
					    {
                            memset(&V_DataBuff[V_usOffset], 0xAA, V_Data_Length);
					    }
				    }
                    PF_CopyDataBytes_698(&V_DataBuff[V_usOffset], &P_Data[V_usDataoffset], Str_Encode.V_uc645Length);
                    V_usDataoffset += Str_Encode.V_uc645Length;       /*���ݷ������ĳ���*/
                    V_usOffset += V_Data_Length;                      /*ȫ�������ݳ���*/
			    }
			    else
			    {
				    if(Str_Encode.V_uc698Type == C_array)             /*��Ҫ�����645��ʶ��*/
				    {
					    for(i = 1; i <= Str_Encode.V_uc698NextNum; i++)
					    {
                            Str_EncodeNext = Str_FrozenConvert_Table[V_usOAD_Data + i];
                            V_Data_Length = Str_EncodeNext.V_uc645Length;
			                SF_FrozenDataFF_NextNum(&Str_EncodeNext, (V_usOAD_Data + i));

						    V_ulReadBuff[0] = V_Data_OAD[0];
						    V_ulReadBuff[1] = Str_EncodeNext.V_ulOAD;
						    V_ulReadBuff[1] |= (ulong32)(V_usOAD_State << 13);
						    V_ulReadBuff[2] = 0xFFFFFFFF;
						    if((Inf_ReadEventRenew(V_ulReadBuff, V_DataBuff+V_usOffset, &V_Data_Length)) != C_OK)   /*��ȡ����*/
						    {
							    V_Data_Length = Str_EncodeNext.V_uc645Length;
                                memset((V_DataBuff + V_usOffset), 0xAA, V_Data_Length);
						    }   /*else �����ݳɹ����Ѷ�������*/
		                    PF_CopyDataBytes_698(&V_DataBuff[V_usOffset], &P_Data[V_usDataoffset], Str_EncodeNext.V_uc645Length);
                            V_usDataoffset += Str_EncodeNext.V_uc645Length;     /*���ݷ������ĳ���*/
                            V_usOffset += V_Data_Length;                        /*ȫ�������ݳ���*/
					    }
				    }
				   else
				   {
					    V_ulReadBuff[0] = V_Data_OAD[0];
					    V_ulReadBuff[1] = Str_Encode.V_ulOAD;
					    V_ulReadBuff[1] |= (ulong32)(V_usOAD_State << 13);
					    V_ulReadBuff[2] = 0xFFFFFFFF;

					    if((Inf_ReadEventRenew(V_ulReadBuff, (V_DataBuff + V_usOffset), &V_Data_Length)) != C_OK)     /*��ȡ����*/
					    {
						    V_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data].V_uc645Length;
                            memset((V_DataBuff + V_usOffset), 0xAA, V_Data_Length);
					    }   /*else��ȡ��ȷ�������Ѷ���*/

                        PF_CopyDataBytes_698(&V_DataBuff[V_usOffset], &P_Data[V_usDataoffset], Str_Encode.V_uc645Length);
                        V_usDataoffset += Str_Encode.V_uc645Length;         /*���ݷ������ĳ���*/
                        V_usOffset += V_Data_Length;                        /*ȫ�������ݳ���*/
				   }
			   }
            }

			if((V_usDataoffset > V_usBuffMaxLen) || (V_usDataoffset > (1024 - 40)))	    /*��󳤶Ȳ��ܳ�������Buff���Ⱥ�����Buff����*/
			{
				return	C_DataLenError;
			}
		    *P_Data_Length = V_usDataoffset;
		}
    }
	else
	{
        V_ucj = 1;
		while(V_Data_OAD[V_ucj] != 0xFFFFFFFF)
		{
			V_ucOADFlag = 0;
			for(V_ucTurn = 0; V_ucTurn < (V_usOADTab_Length / 2); V_ucTurn++)
            {
				V_usOAD_Data = V_usOAD[V_ucTurn] & 0x1FFF;
				V_usOAD_State = V_usOAD[V_ucTurn] >> 13;
				if(V_usOAD_Data >= Str_FrozenConvert_Table_Len)
                {
					return C_Error;
                }

                Str_Encode = Str_FrozenConvert_Table[V_usOAD_Data];
			    SF_FrozenDataFF_NextNum(&Str_Encode, V_usOAD_Data);

				if(V_Data_OAD[V_ucj] == (Str_Encode.V_ulOAD | (ulong32)(V_usOAD_State << 13)))
				{
					if(V_usOAD_State != 0x0003)           /*0x0003Ϊ�¼�����ǰ*/
					{
						if(V_usOAD_State == 0x0004)       /*0x0004Ϊ�¼�������*/
						{
							if( (*pV_ucHappeningFlag) == C_Happen_EventState)		/*�����ʷ״̬���з����޻ָ�*/
							{
                                memset((V_DataBuff + V_usOffset), 0xAA, Str_Encode.V_uc645Length);
							}
						}
						V_usOffset += Str_Encode.V_uc645Length;
					}
					else
					{
						if(Str_Encode.V_uc698Type == C_array)   /*��Ҫ�������ʶ��*/
						{
							for(i = 1; i <= Str_Encode.V_uc698NextNum; i++)
							{
                                Str_EncodeNext = Str_FrozenConvert_Table[V_usOAD_Data + i];
			                    SF_FrozenDataFF_NextNum(&Str_EncodeNext, (V_usOAD_Data + i));
                                V_Data_Length = Str_EncodeNext.V_uc645Length;

								V_ulReadBuff[0] = V_Data_OAD[0];
								V_ulReadBuff[1] = Str_EncodeNext.V_ulOAD;
								V_ulReadBuff[1] |= (ulong32)(V_usOAD_State << 13);
								V_ulReadBuff[2] = 0xFFFFFFFF;

								if(Inf_ReadEventRenew(V_ulReadBuff, (V_DataBuff + V_usOffset), &V_Data_Length) == C_OK)     /*��ȡ����*/
								{
									V_usOffset += V_Data_Length;
								}
								else
								{
                                    memset((V_DataBuff + V_usOffset), 0xAA, Str_EncodeNext.V_uc645Length);
								}

							}
						}
						else
						{
							V_ulReadBuff[0] = V_Data_OAD[0];
							V_ulReadBuff[1] = Str_Encode.V_ulOAD;
							V_ulReadBuff[1] |= (ulong32)(V_usOAD_State << 13);
							V_ulReadBuff[2] = 0xFFFFFFFF;

							if(Inf_ReadEventRenew(V_ulReadBuff, (V_DataBuff + V_usOffset), &Str_Encode.V_uc645Length) == C_OK)    /*��ȡ����*/
							{
								V_usOffset += Str_Encode.V_uc645Length;
							}
							else
							{
                                Str_Encode = Str_FrozenConvert_Table[V_usOAD_Data];
			                    SF_FrozenDataFF_NextNum(&Str_Encode, V_usOAD_Data);

                                memset((V_DataBuff + V_usOffset), 0xAA, Str_Encode.V_uc645Length);
							}
						}
					}
					V_ucOADFlag = 0x68;
					if((V_usOffset > V_usBuffMaxLen) || (V_usOffset > (1024 - 40)))	/*��󳤶Ȳ��ܳ�������Buff���Ⱥ�����Buff����*/
					{
						return	C_DataLenError;
					}
					break;
				}
                else
                {
                    if(C_array == Str_Encode.V_uc698Type)
                    {
                        V_ucRateNum = InF_RateNumChangeToHex();
                        for(V_uck = 0; V_uck < (V_ucRateNum + 1); V_uck++)
                        {
                            if ( ( Str_FrozenConvert_Table[V_usOAD_Data + V_uck + 1].V_ulOAD & 0xFFFFFFF0 )
                              == ( Str_FrozenConvert_Table[V_usOAD_Data + V_uck].V_ulOAD & 0xFFFFFFF0 ) )
                            {
                                if( V_Data_OAD[V_ucj] == (Str_FrozenConvert_Table[V_usOAD_Data + V_uck + 1].V_ulOAD | (ulong32)(V_usOAD_State << 13)))
                                {
                                    if(V_usOAD_State != 0x0003)           /*0x0003Ϊ�¼�����ǰ*/
                                    {
                                        if(V_usOAD_State == 0x0004)       /*0x0004Ϊ�¼�������*/
                                        {
                                            if( (*pV_ucHappeningFlag) == C_Happen_EventState)		/*�����ʷ״̬���з����޻ָ�*/
                                            {
                                                memset((V_DataBuff + V_usOffset), 0xAA, Str_FrozenConvert_Table[V_usOAD_Data + V_uck + 1].V_uc645Length);
											}
                                        }
                                        V_usOffset += Str_FrozenConvert_Table[V_usOAD_Data + V_uck + 1].V_uc645Length;
                                    }
                                    else
                                    {
                                        V_ulReadBuff[0] = V_Data_OAD[0];
                                        V_ulReadBuff[1] = Str_FrozenConvert_Table[V_usOAD_Data + V_uck + 1].V_ulOAD;
                                        V_ulReadBuff[1] |= (ulong32)(V_usOAD_State << 13);
                                        V_ulReadBuff[2] = 0xFFFFFFFF;

                                        if(Inf_ReadEventRenew(V_ulReadBuff, (V_DataBuff + V_usOffset), &Str_Encode.V_uc645Length) == C_OK)    /*��ȡ����*/
                                        {
                                            V_usOffset += Str_FrozenConvert_Table[V_usOAD_Data + V_uck + 1].V_uc645Length;
                                        }
                                        else
                                        {
                                            memset((V_DataBuff + V_usOffset), 0xAA, Str_FrozenConvert_Table[V_usOAD_Data + V_uck + 1].V_uc645Length);
                                        }
                                    }
                                    V_ucOADFlag = 0x68;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            if(V_Data_OAD[V_ucj] == CEventNum)
            {
                V_usOffset += CLEventNum;
                V_ucOADFlag = 0x68;
            }
            else if(V_Data_OAD[V_ucj] == CEventHPTime)
            {
                V_usOffset += CLEventHPTime;
                V_ucOADFlag = 0x68;
            }
            else if(V_Data_OAD[V_ucj] == CEventEndTime)
            {
                if( (*pV_ucHappeningFlag)==C_Happen_EventState)
                {
                    memset((V_DataBuff + V_usOffset), 0xAA, C_EventTimeLength);
                }
                V_usOffset += CLEventHPTime;
                V_ucOADFlag = 0x68;
            }
            else if((V_Data_OAD[V_ucj] == CEventHPSource) && (EventMappingTable[V_uci].SourceFlag == C_SourceExist))
            {
                V_ulReadBuff[0] = V_Data_OAD[0];
                V_ulReadBuff[1] = CEventHPSource;
                V_ulReadBuff[2] = 0xFFFFFFFF;
                V_usDataLength = 20;
                V_ucFixTime = 0;
                V_ucNextSign = 0;
                if(InF_ReadEventData(V_ulReadBuff, &V_ucFixTime, (V_DataBuff + V_usOffset), &V_ucNextSign, &V_usDataLength, V_timeFlash) == C_OK)
                {
                    V_usOffset += V_usDataLength;
                }
                else
                {
                    *(V_DataBuff + V_usOffset) = 0xAA;
                    V_usOffset += 1;
                }
                V_ucOADFlag = 0x68;
            }
            else if( V_Data_OAD[V_ucj] == C_OverDemandRenew_Demand )
            {
                if ( ( V_Data_OAD[0] == CPos_Ac_De_Over_Note_1 )
                  || ( V_Data_OAD[0] == CRev_Ac_De_Over_Note_1 )
                  || ( V_Data_OAD[0] == CQua1_Re_De_Over_Note_1 )
                  || ( V_Data_OAD[0] == CQua2_Re_De_Over_Note_1 )
                  || ( V_Data_OAD[0] == CQua3_Re_De_Over_Note_1 )
                  || ( V_Data_OAD[0] == CQua4_Re_De_Over_Note_1 ) )
                {
                    if( (*pV_ucHappeningFlag) == C_Happen_EventState )		/*�����ʷ״̬���з����޻ָ�*/
                    {
                        switch(EventMappingTable[V_uci].EventNo)
                        {
                            case	C_OverForwardActiveEventNo:
                                    PF_CopyDataBytes(GStr_OverForwardActiveStr.Renewal, (V_DataBuff + V_usOffset), CLOverDemandRenew_Demand);
                                    break;
                            case	C_OverReverseActiveEventNo:
                                    PF_CopyDataBytes(GStr_OverReverseActiveStr.Renewal, (V_DataBuff + V_usOffset), CLOverDemandRenew_Demand);
                                    break;
                            case	C_1OverIdleDemandEventNo:
                                    PF_CopyDataBytes(GStr_Over1IdleDemandStr.Renewal, (V_DataBuff + V_usOffset), CLOverDemandRenew_Demand);
                                    break;
                            case	C_2OverIdleDemandEventNo:
                                    PF_CopyDataBytes(GStr_Over2IdleDemandStr.Renewal, (V_DataBuff + V_usOffset), CLOverDemandRenew_Demand);
                                    break;
                            case	C_3OverIdleDemandEventNo:
                                    PF_CopyDataBytes(GStr_Over3IdleDemandStr.Renewal, (V_DataBuff + V_usOffset), CLOverDemandRenew_Demand);
                                    break;
                            case	C_4OverIdleDemandEventNo:
                                    PF_CopyDataBytes(GStr_Over4IdleDemandStr.Renewal, (V_DataBuff + V_usOffset), CLOverDemandRenew_Demand);
                                    break;
                            default:
                                    break;
                        }
                    }
                    V_usOffset += CLOverDemandRenew_Demand;
                    V_usDataoffset += CLOverDemandRenew_Demand;
                }
            }
            else if( V_Data_OAD[V_ucj] == C_OverDemandRenew_HapTime )
            {
                if ( ( V_Data_OAD[0] == CPos_Ac_De_Over_Note_1 )
                  || ( V_Data_OAD[0] == CRev_Ac_De_Over_Note_1 )
                  || ( V_Data_OAD[0] == CQua1_Re_De_Over_Note_1 )
                  || ( V_Data_OAD[0] == CQua2_Re_De_Over_Note_1 )
                  || ( V_Data_OAD[0] == CQua3_Re_De_Over_Note_1 )
                  || ( V_Data_OAD[0] == CQua4_Re_De_Over_Note_1 ) )
                {
                    if( (*pV_ucHappeningFlag) == C_Happen_EventState )		/*�����ʷ״̬���з����޻ָ�*/
                    {
                        switch(EventMappingTable[V_uci].EventNo)
                        {
                            case	C_OverForwardActiveEventNo:
                                    PF_CopyDataBytes(GStr_OverForwardActiveStr.RenewalTime, (V_DataBuff + V_usOffset), CLOverDemandRenew_HapTime);
                                    break;
                            case	C_OverReverseActiveEventNo:
                                    PF_CopyDataBytes(GStr_OverReverseActiveStr.RenewalTime, (V_DataBuff + V_usOffset), CLOverDemandRenew_HapTime);
                                    break;
                            case	C_1OverIdleDemandEventNo:
                                    PF_CopyDataBytes(GStr_Over1IdleDemandStr.RenewalTime, (V_DataBuff + V_usOffset), CLOverDemandRenew_HapTime);
                                    break;
                            case	C_2OverIdleDemandEventNo:
                                    PF_CopyDataBytes(GStr_Over2IdleDemandStr.RenewalTime, (V_DataBuff + V_usOffset), CLOverDemandRenew_HapTime);
                                    break;
                            case	C_3OverIdleDemandEventNo:
                                    PF_CopyDataBytes(GStr_Over3IdleDemandStr.RenewalTime, (V_DataBuff + V_usOffset), CLOverDemandRenew_HapTime);
                                    break;
                            case	C_4OverIdleDemandEventNo:
                                    PF_CopyDataBytes(GStr_Over4IdleDemandStr.RenewalTime, (V_DataBuff + V_usOffset), CLOverDemandRenew_HapTime);
                                    break;
                            default:
                                    break;
                        }
                    }
                    V_usOffset += CLOverDemandRenew_HapTime;
                    V_usDataoffset += CLOverDemandRenew_HapTime;
                }
            }
            else if(V_Data_OAD[V_ucj] == CProgOADGather)
            {
                V_usOffset += CLProgOADGather;
                V_ucOADFlag = 0x68;
            }

			if(V_ucOADFlag == 0x68)	/*�Ѿ����ҵ���������һ��*/
			{
				V_ucj++;
				continue;
			}
			else
			{
				*(V_DataBuff + V_usOffset) = C_NotSupportAOD_DataBB;
				V_usOffset += 1;
				V_ucj++;
				if((V_usOffset > V_usBuffMaxLen) || (V_usOffset > (1024 - 40)))	    /*��󳤶Ȳ��ܳ�������Buff���Ⱥ�����Buff����*/
				{
                    return	C_DataLenError;
				}
			}
		}
		PF_CopyDataBytes_698(V_DataBuff, P_Data, V_usOffset);
		*P_Data_Length = V_usOffset;
	}
	return C_OK;
}
#endif

const Str_EvtFixRCSD_Type TB_FixRCSD[] = 
{
	{CAbnormalCard_CareNo,				CLAbnormalCard_CareNo},				/*�쳣�忨�����к�*/
	{CAbnormalCard_ErrorStatus,			CLAbnormalCard_ErrorStatus},		/*�쳣�忨����״̬��*/
	{CAbnormalCard_OrderHead,			CLAbnormalCard_OrderHead},			/*�쳣�忨�忨��������ͷ*/
	{CAbnormalCard_ErrorRespondStatus,	CLAbnormalCard_ErrorRespondStatus},	/*�쳣�忨�忨������Ӧ״̬*/
	{CRWTimeTable_OAD,					CLProgOAD},							/*ʱ�α���OAD*/
	{CRWTimeTable_ForwardData,			CLFirst_TZone_1PT_Data},			/*ʱ�α��̱��ǰ����*/
	{C_RWHoliday_OAD,					CLProgOAD},							/*�ڼ��ձ��OAD*/
	{CRWHoliday_ForwardData,			CLHolidy_PT_Table1},				/*�ڼ��ձ��ǰ�ڼ�������*/
	{C_OverDemandRenew_Demand,			CLCurr_AcDemand},					/*�������޷����ڼ��������*/
	{C_OverDemandRenew_HapTime,			CLDate_Time},						/*�������޷����ڼ������������ʱ��*/
	{CProgram_OADList,					(CLProgOAD + 1) * CProgOADNum},		/*����¼���¼����б�*/
	{CEventClear_OADList,				CLProgOAD},							/*�¼������¼�����б�*/
	{CReturnMoney_Charge,				CLAlam1_Money},						/*�˷��¼���¼�̶��б����˷ѽ��*/
};
#define C_TB_FixRCSD_Len	( sizeof(TB_FixRCSD) / sizeof(Str_EvtFixRCSD_Type) )
/**********************************************************************************************************
����ԭ�ͣ�SF_JudgeFixRCSD
�����������ж��¼���¼�̶��б����ݵĺϷ��ԣ�������ƫ�ƺͱ�־
���������V_ulOAD:��ѡOAD��V_ucDataBuff:��¼���ݻ��棻V_usOffset����ǰ��ѡOAD��Ӧ��ƫ�ƣ�V_ucOADFlag���Ƿ��ܲ鵽�̶��б�ı�־������Ϊ0
���������V_usOffset����ǰ��ѡOAD��Ӧ��ƫ�ƣ�V_ucOADFlag���Ƿ��ܲ鵽�̶��б�ı�־��0x68�ܲ鵽
���ز�������
����λ�ã��¼�ģ����¼���¼�ӿڵ���
��    ע��
***************************************************************************************************************/
void SF_JudgeFixRCSD(ulong32 V_ulOAD, uchar8 *V_ucDataBuff, ushort16 *V_usOffset, uchar8 *V_ucOADFlag)
{
	uchar8 V_uci;
	
	if(V_ucDataBuff[*V_usOffset] == C_NotSupportAOD_DataBB)
	{/*���ݲ�����ΪBB����ʾû�����ݣ�ֱ�ӷ���*/
		return;
	}
	for(V_uci = 0;V_uci < C_TB_FixRCSD_Len;V_uci ++)
	{
		if(V_ulOAD == TB_FixRCSD[V_uci].V_ulOAD)/*�鵽���󣬸�ֵƫ�ƺͱ�־*/
		{
			*V_usOffset += TB_FixRCSD[V_uci].V_ucLen;
			
			*V_ucOADFlag = 0x68;

			break;
		}
	}
}

/**********************************************************************************************************
����ԭ�ͣ�uchar8 Inf_ReadEventLast_1(Str_Read_T *pStr_Read, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, Str_SuppInfo *pStr_SuppInfo)
������������ȡ��һ���¼���¼����
���������pStr_ReadΪ��ȡ�����ṹ��
    pV_ucDataBufΪ��ȡ�����ַ
	*pV_usDataLenΪ��ȡ������󳤶�
	pV_ucSupplementaryInformationΪ������Ϣ�����ַ
	*pV_usSIDataLenΪ������Ϣ������󳤶�
���������*pV_ucDataBufΪ��ȡ����
	*pV_usDataLenΪ��ȡ����ʵ�ʳ���
	pV_ucSupplementaryInformationΪ������Ϣ����
	*pV_usSIDataLenΪ������Ϣ����ʵ�ʳ���
���ز�����C_OK��ȷ���������ؾ������
����λ�ã��¼�ģ����¼���¼�ӿڵ���
��    ע��*pV_usDataLen������ڵ�����ȡֵ���ȣ���Ȼ���ش���
***************************************************************************************************************/
uchar8 Inf_ReadEventLast_1(Str_Read_T *pStr_Read, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, Str_SuppInfo *pStr_SuppInfo)
{
	uchar8 V_ucTurn, V_uci;
	ushort16 V_usOADTab_Length, V_usDataLength;
	uchar8 V_ucData_Length, V_ucReturn, V_ucOADFlag;
	ushort16 V_usOAD[C_EventMAXRelatedOAD], V_usOAD_Data, V_usOAD_State;
	ushort16 V_usOffset = 0;
	uchar8 i;
	ulong32 V_ulReadBuff[5] = {0};
	ushort16 V_usBuffMaxLen;
	uchar8 V_ucDataBuff[C_EventMAXLen] = {0};
	ushort16 V_usDataoffset = 0, V_usi, V_usNum = pStr_Read->V_usROAD_Num;
    uchar8 V_ucSpecicalDataLen = 0;
    uchar8 V_uck;
    uchar8 V_ucHappeningFlag;
    ulong32 *pV_ulData_OAD;
    Struct_FrozenConvert_Type Str_Encode;
    Struct_FrozenConvert_Type Str_EncodeNext;

    pV_ulData_OAD = pStr_Read->pV_ulROAD;/*��ȡOAD�͹����б���ָ��*/

	V_ucHappeningFlag = C_End_EventState;			/*Ĭ�ϲ�����*/
	for(V_uci = 0; V_uci < EventMappingTable_Len; V_uci++)
	{
		if(EventMappingTable[V_uci].WriteOAD == pV_ulData_OAD[0])
		{
			break;
		}
	}
	if(V_uci >= EventMappingTable_Len)
	{
		return C_OtherErr;
	}
	V_usDataLength = C_EventMAXLen;
	V_ucReturn = InF_GetData_Record_DataBase(pStr_Read, V_ucDataBuff, &V_usDataLength, pStr_SuppInfo);
	if(V_ucReturn != C_OK)
	{
		return V_ucReturn;
	}

    V_usOADTab_Length = C_EventMAXRelatedOADLen;
	if(InF_ReadOADTab_Data(EventMappingTable[V_uci].OADTab, (uchar8 *)&V_usOAD, &V_usOADTab_Length) != C_OK)
	{
		return C_Error;
	}

    /*�⼸���¼�һ��û�й����б�*/
	if ( ( ( pV_ulData_OAD[0] == CEven_Clear_Note_1 )
        || ( pV_ulData_OAD[0] == CProgram_Note_1 )
        || ( pV_ulData_OAD[0] == CProgPT_Note_1 )
        || ( pV_ulData_OAD[0] == CProgHol_Note_1 )
        || ( pV_ulData_OAD[0] == CAbnorC_Note_1)
        || ( pV_ulData_OAD[0] == CReturn_M_Note_1 ) )
       && ( V_usOADTab_Length == 0 ) )
	{
		PF_CopyDataBytes_698(V_ucDataBuff, pV_ucDataBuf, V_usDataLength);
		*pV_usDataLen = V_usDataLength;
		return C_OK;
	}

/************************�ж��¼���¼��ǰ����״̬***************************/
	if( SF_Judge_EventIntegrity(EventMappingTable[V_uci].EventNo) == C_Happen_EventState )
	{
		V_ucHappeningFlag = C_Happen_EventState;			/*���ڷ���*/
		
		pStr_SuppInfo->V_ucLastFlag = C_Active_Happening;	/*��������ڷ�������ֵ���ڷ�����־��ͨ�ţ����ڱ���*/
	}

	V_usBuffMaxLen = *pV_usDataLen;
	if( pV_ulData_OAD[1] == 0xFFFFFFFF )
	{

        V_usOffset += (CLEventDegree + CLEventHappenTime + CLEventEndTime);		/*�¼���š�����ʱ�䡢����ʱ��ƫ��*/
        V_usDataoffset += (CLEventDegree + CLEventHappenTime + CLEventEndTime);

        if( (V_ucHappeningFlag == C_Happen_EventState)
		   && (pStr_Read -> V_ucReadMode == C_ComMode) )/*ͨ�Ŷ��Ÿ�ֵAA*/
        {
            memset((V_ucDataBuff + CLEventDegree + CLEventHappenTime), 0xAA, C_EventTimeLength);
        }

        if(EventMappingTable[V_uci].SourceFlag == C_SourceExist)
        {
            V_usOffset += CLEventSource;	 /*�¼�����Դƫ��*/
            V_usDataoffset += CLEventSource;
        }
        V_usOffset +=  CLEventReport;/*�����ϱ�״̬*/
        V_usDataoffset +=  CLEventReport;

        if ( ( pV_ulData_OAD[0] == CPos_Ac_De_Over_Note_1 )
          || ( pV_ulData_OAD[0] == CRev_Ac_De_Over_Note_1 )
          || ( pV_ulData_OAD[0] == CQua1_Re_De_Over_Note_1 )
          || ( pV_ulData_OAD[0] == CQua2_Re_De_Over_Note_1 )
          || ( pV_ulData_OAD[0] == CQua3_Re_De_Over_Note_1 )
          || ( pV_ulData_OAD[0] == CQua4_Re_De_Over_Note_1 ) )
        {
            if( (V_ucHappeningFlag) == C_Happen_EventState )		/*�����ʷ״̬���з����޻ָ�*/
            {
                switch(EventMappingTable[V_uci].EventNo)
                {
                    case	C_OverForwardActiveEventNo:
                            PF_CopyDataBytes(GStr_OverForwardActiveStr.Renewal, (V_ucDataBuff + V_usOffset), C_OverDemandRenew_Length);
                            break;
                    case	C_OverReverseActiveEventNo:
                            PF_CopyDataBytes(GStr_OverReverseActiveStr.Renewal, (V_ucDataBuff + V_usOffset), C_OverDemandRenew_Length);
                            break;
                    case	C_1OverIdleDemandEventNo:
                            PF_CopyDataBytes(GStr_Over1IdleDemandStr.Renewal, (V_ucDataBuff + V_usOffset), C_OverDemandRenew_Length);
                            break;
                    case	C_2OverIdleDemandEventNo:
                            PF_CopyDataBytes(GStr_Over2IdleDemandStr.Renewal, (V_ucDataBuff + V_usOffset), C_OverDemandRenew_Length);
                            break;
                    case	C_3OverIdleDemandEventNo:
                            PF_CopyDataBytes(GStr_Over3IdleDemandStr.Renewal, (V_ucDataBuff + V_usOffset), C_OverDemandRenew_Length);
                            break;
                    case	C_4OverIdleDemandEventNo:
                            PF_CopyDataBytes(GStr_Over4IdleDemandStr.Renewal, (V_ucDataBuff + V_usOffset), C_OverDemandRenew_Length);
                            break;
                    default:
                            break;
                }
            }
            V_usOffset += C_OverDemandRenew_Length;
            V_usDataoffset += C_OverDemandRenew_Length;
            PF_CopyDataBytes(V_ucDataBuff, pV_ucDataBuf, V_usDataoffset);
        }
        else
        {
            /*�����¼���¼��Ԫ���ݳ���ƫ��*/
            SF_Event_SpecificDataLenCal(pV_ulData_OAD[0], &V_ucSpecicalDataLen);
            V_usOffset += V_ucSpecicalDataLen;
            V_usDataoffset += V_ucSpecicalDataLen;
            PF_CopyDataBytes(V_ucDataBuff, pV_ucDataBuf, V_usDataoffset);
        }

		/*����OAD��˳����֯����*/
		for( V_ucTurn = 0; V_ucTurn < (V_usOADTab_Length / 2); V_ucTurn++)
		{
		    V_usOAD_Data = V_usOAD[V_ucTurn] & 0x1FFF;  /*���������б��е��к�*/
			V_usOAD_State = V_usOAD[V_ucTurn] >> 13;    /*�¼�����������*/

			if(V_usOAD_Data >= Str_FrozenConvert_Table_Len)
			{
				return C_Error;
			}

			V_ucData_Length = Str_FrozenConvert_Table[V_usOAD_Data].V_uc645Length;
            Str_Encode = Str_FrozenConvert_Table[V_usOAD_Data];
			SF_FrozenDataFF_NextNum(&Str_Encode, V_usOAD_Data);

            if((SF_FrozenData_JudgeRateNum(V_usOAD_Data, Str_Encode.V_ulOAD)) == C_Error)	    /*����������Ӧ��գ����ݲ㷵������0xBB*/
            {
                pV_ucDataBuf[V_usDataoffset] = C_NotSupportAOD_DataBB;
                V_usDataoffset += CL_NotSupportAOD_DataBB;
                V_usOffset += V_ucData_Length;	/*ȫ�������ݳ���*/
            }
            else
            {
			    if(V_usOAD_State != 0x0003)       /*0x0003Ϊ�¼�����ǰ*/
			    {
				    if(V_usOAD_State == 0x0004)   /*0x0004Ϊ�¼�������*/
				    {
					    if( (V_ucHappeningFlag) == C_Happen_EventState)		/*�����ʷ״̬���з����޻ָ�*/
					    {
                            memset(&V_ucDataBuff[V_usOffset], 0xAA, V_ucData_Length);
					    }
				    }
                    PF_CopyDataBytes_698(&V_ucDataBuff[V_usOffset], &pV_ucDataBuf[V_usDataoffset], Str_Encode.V_uc645Length);
                    V_usDataoffset += Str_Encode.V_uc645Length;       /*���ݷ������ĳ���*/
                    V_usOffset += V_ucData_Length;                      /*ȫ�������ݳ���*/
			    }
			    else
			    {
				    if(Str_Encode.V_uc698Type == C_array)             /*��Ҫ�����645��ʶ��*/
				    {
					    for(i = 1; i <= Str_Encode.V_uc698NextNum; i++)
					    {
                            Str_EncodeNext = Str_FrozenConvert_Table[V_usOAD_Data + i];
                            V_ucData_Length = Str_EncodeNext.V_uc645Length;
			                SF_FrozenDataFF_NextNum(&Str_EncodeNext, (V_usOAD_Data + i));

						    V_ulReadBuff[0] = pV_ulData_OAD[0];
						    V_ulReadBuff[1] = Str_EncodeNext.V_ulOAD;
						    V_ulReadBuff[1] |= (ulong32)(V_usOAD_State << 13);
						    V_ulReadBuff[2] = 0xFFFFFFFF;
						    if((Inf_ReadEventRenew(V_ulReadBuff, V_ucDataBuff+V_usOffset, &V_ucData_Length)) != C_OK)   /*��ȡ����*/
						    {
							    V_ucData_Length = Str_EncodeNext.V_uc645Length;
                                memset((V_ucDataBuff + V_usOffset), 0xAA, V_ucData_Length);
						    }   /*else �����ݳɹ����Ѷ�������*/
		                    PF_CopyDataBytes_698(&V_ucDataBuff[V_usOffset], &pV_ucDataBuf[V_usDataoffset], Str_EncodeNext.V_uc645Length);
                            V_usDataoffset += Str_EncodeNext.V_uc645Length;     /*���ݷ������ĳ���*/
                            V_usOffset += V_ucData_Length;                        /*ȫ�������ݳ���*/
					    }
				    }
				   else
				   {
					    V_ulReadBuff[0] = pV_ulData_OAD[0];
					    V_ulReadBuff[1] = Str_Encode.V_ulOAD;
					    V_ulReadBuff[1] |= (ulong32)(V_usOAD_State << 13);
					    V_ulReadBuff[2] = 0xFFFFFFFF;

					    if((Inf_ReadEventRenew(V_ulReadBuff, (V_ucDataBuff + V_usOffset), &V_ucData_Length)) != C_OK)     /*��ȡ����*/
					    {
						    V_ucData_Length = Str_FrozenConvert_Table[V_usOAD_Data].V_uc645Length;
                            memset((V_ucDataBuff + V_usOffset), 0xAA, V_ucData_Length);
					    }   /*else��ȡ��ȷ�������Ѷ���*/

                        PF_CopyDataBytes_698(&V_ucDataBuff[V_usOffset], &pV_ucDataBuf[V_usDataoffset], Str_Encode.V_uc645Length);
                        V_usDataoffset += Str_Encode.V_uc645Length;         /*���ݷ������ĳ���*/
                        V_usOffset += V_ucData_Length;                        /*ȫ�������ݳ���*/
				   }
			   }
            }

			if((V_usDataoffset > V_usBuffMaxLen) || (V_usDataoffset > (C_EventMAXLen - 40)))	    /*��󳤶Ȳ��ܳ�������Buff���Ⱥ�����Buff����*/
			{
				return	C_DataLenError;
			}
		}
		*pV_usDataLen = V_usDataoffset;/*���ȸ�ֵ����forѭ�����棬��ֹδ���ù����б�ʱ���س��ȴ���*/
    }
	else
	{
		V_usNum += 1;/*����OAD�Ĵ洢ƫ�ƴӵ�2����ʼ���˴���1*/
		for(V_usi = 1;V_usi < V_usNum;V_usi ++)
		{
			if(pV_ulData_OAD[V_usi] == 0xFFFFFFFF)
			{
				break;
			}
			V_ucOADFlag = 0;
			for(V_ucTurn = 0; V_ucTurn < (V_usOADTab_Length / 2); V_ucTurn++)
            {
				V_usOAD_Data = V_usOAD[V_ucTurn] & 0x1FFF;
				V_usOAD_State = V_usOAD[V_ucTurn] >> 13;
				if(V_usOAD_Data >= Str_FrozenConvert_Table_Len)
                {
					return C_Error;
                }

                Str_Encode = Str_FrozenConvert_Table[V_usOAD_Data];
			    SF_FrozenDataFF_NextNum(&Str_Encode, V_usOAD_Data);

				if(pV_ulData_OAD[V_usi] == (Str_Encode.V_ulOAD | (ulong32)(V_usOAD_State << 13)))
				{
					if(V_usOAD_State != 0x0003)           /*0x0003Ϊ�¼�����ǰ*/
					{
						if(V_usOAD_State == 0x0004)       /*0x0004Ϊ�¼�������*/
						{
							if( (V_ucHappeningFlag) == C_Happen_EventState)		/*�����ʷ״̬���з����޻ָ�*/
							{
                                memset((V_ucDataBuff + V_usOffset), 0xAA, Str_Encode.V_uc645Length);
							}
						}
						V_usOffset += Str_Encode.V_uc645Length;
					}
					else
					{
						if(Str_Encode.V_uc698Type == C_array)   /*��Ҫ�������ʶ��*/
						{
							for(i = 1; i <= Str_Encode.V_uc698NextNum; i++)
							{
                                Str_EncodeNext = Str_FrozenConvert_Table[V_usOAD_Data + i];
			                    SF_FrozenDataFF_NextNum(&Str_EncodeNext, (V_usOAD_Data + i));
                                V_ucData_Length = Str_EncodeNext.V_uc645Length;

								V_ulReadBuff[0] = pV_ulData_OAD[0];
								V_ulReadBuff[1] = Str_EncodeNext.V_ulOAD;
								V_ulReadBuff[1] |= (ulong32)(V_usOAD_State << 13);
								V_ulReadBuff[2] = 0xFFFFFFFF;

								if(Inf_ReadEventRenew(V_ulReadBuff, (V_ucDataBuff + V_usOffset), &V_ucData_Length) == C_OK)     /*��ȡ����*/
								{
									V_usOffset += V_ucData_Length;
								}
								else
								{
                                    memset((V_ucDataBuff + V_usOffset), 0xAA, Str_EncodeNext.V_uc645Length);
								}

							}
						}
						else
						{
							V_ulReadBuff[0] = pV_ulData_OAD[0];
							V_ulReadBuff[1] = Str_Encode.V_ulOAD;
							V_ulReadBuff[1] |= (ulong32)(V_usOAD_State << 13);
							V_ulReadBuff[2] = 0xFFFFFFFF;

							if(Inf_ReadEventRenew(V_ulReadBuff, (V_ucDataBuff + V_usOffset), &Str_Encode.V_uc645Length) == C_OK)    /*��ȡ����*/
							{
								V_usOffset += Str_Encode.V_uc645Length;
							}
							else
							{
                                Str_Encode = Str_FrozenConvert_Table[V_usOAD_Data];
			                    SF_FrozenDataFF_NextNum(&Str_Encode, V_usOAD_Data);

                                memset((V_ucDataBuff + V_usOffset), 0xAA, Str_Encode.V_uc645Length);
							}
						}
					}
					V_ucOADFlag = 0x68;
					if((V_usOffset > V_usBuffMaxLen) || (V_usOffset > (C_EventMAXLen - 40)))	/*��󳤶Ȳ��ܳ�������Buff���Ⱥ�����Buff����*/
					{
						return	C_DataLenError;
					}
					break;
				}
                else
                {
                    if(C_array == Str_Encode.V_uc698Type)
                    {
                        for(V_uck = 0; V_uck < 255; V_uck++)/*�˴���ѯ������ֵ���255��ʵ�ʿ϶����ᵽ�������жϵ���ʶ�벻ƥ����˳�*/
                        {
                            if ( ( Str_FrozenConvert_Table[V_usOAD_Data + V_uck + 1].V_ulOAD & 0xFFFFFFF0 )
                              == ( Str_FrozenConvert_Table[V_usOAD_Data + V_uck].V_ulOAD & 0xFFFFFFF0 ) )
                            {
                                if( SF_FrozenData_JudgeRateNum( V_usOAD_Data + V_uck + 1, pV_ulData_OAD[V_usi] ) == C_Error )
                                {/*���������������˳�*/
                                    break;
                                }
                                if( pV_ulData_OAD[V_usi] == (Str_FrozenConvert_Table[V_usOAD_Data + V_uck + 1].V_ulOAD | (ulong32)(V_usOAD_State << 13)))
                                {
                                    if(V_usOAD_State != 0x0003)           /*0x0003Ϊ�¼�����ǰ*/
                                    {
                                        if(V_usOAD_State == 0x0004)       /*0x0004Ϊ�¼�������*/
                                        {
                                            if( (V_ucHappeningFlag) == C_Happen_EventState)		/*�����ʷ״̬���з����޻ָ�*/
                                            {
                                                memset((V_ucDataBuff + V_usOffset), 0xAA, Str_FrozenConvert_Table[V_usOAD_Data + V_uck + 1].V_uc645Length);
											}
                                        }
                                        V_usOffset += Str_FrozenConvert_Table[V_usOAD_Data + V_uck + 1].V_uc645Length;
                                    }
                                    else
                                    {
                                        V_ulReadBuff[0] = pV_ulData_OAD[0];
                                        V_ulReadBuff[1] = Str_FrozenConvert_Table[V_usOAD_Data + V_uck + 1].V_ulOAD;
                                        V_ulReadBuff[1] |= (ulong32)(V_usOAD_State << 13);
                                        V_ulReadBuff[2] = 0xFFFFFFFF;

                                        if(Inf_ReadEventRenew(V_ulReadBuff, (V_ucDataBuff + V_usOffset), &Str_Encode.V_uc645Length) == C_OK)    /*��ȡ����*/
                                        {
                                            V_usOffset += Str_FrozenConvert_Table[V_usOAD_Data + V_uck + 1].V_uc645Length;
                                        }
                                        else
                                        {
                                            memset((V_ucDataBuff + V_usOffset), 0xAA, Str_FrozenConvert_Table[V_usOAD_Data + V_uck + 1].V_uc645Length);
                                        }
                                    }
                                    V_ucOADFlag = 0x68;
                                    break;
                                }
                            }
                            else/*��ѯ���ı�ʶ���Ѳ�����ͬ���������˳�*/
                            {
                                break;
                            }
                        }
                    }
                }
            }
            if(pV_ulData_OAD[V_usi] == CEventNum)
            {
                V_usOffset += CLEventNum;
                V_ucOADFlag = 0x68;
            }
            else if(pV_ulData_OAD[V_usi] == CEventHPTime)
            {
                V_usOffset += CLEventHPTime;
                V_ucOADFlag = 0x68;
            }
            else if(pV_ulData_OAD[V_usi] == CEventEndTime)
            {
                if( (V_ucHappeningFlag == C_Happen_EventState)
				   && (pStr_Read -> V_ucReadMode == C_ComMode) )/*ͨ�Ŷ��Ÿ�ֵAA*/
                {
                    memset((V_ucDataBuff + V_usOffset), 0xAA, C_EventTimeLength);
                }
                V_usOffset += CLEventHPTime;
                V_ucOADFlag = 0x68;
            }
            else if((pV_ulData_OAD[V_usi] == CEventHPSource) && (EventMappingTable[V_uci].SourceFlag == C_SourceExist))
            {
                V_ulReadBuff[0] = pV_ulData_OAD[0];
                V_ulReadBuff[1] = CEventHPSource;
                V_ulReadBuff[2] = 0xFFFFFFFF;

                V_usDataLength = 20;
                if(SF_ReadLastEvt(V_ulReadBuff, (V_ucDataBuff + V_usOffset), &V_usDataLength, (uchar8)V_ulReadBuff[0]) == C_OK)
                {
                    V_usOffset += V_usDataLength;
                }
                else
                {
                    *(V_ucDataBuff + V_usOffset) = 0xAA;
                    V_usOffset += 1;
                }
                V_ucOADFlag = 0x68;
            }
            else if( pV_ulData_OAD[V_usi] == C_OverDemandRenew_Demand )
            {
                if ( ( pV_ulData_OAD[0] == CPos_Ac_De_Over_Note_1 )
                  || ( pV_ulData_OAD[0] == CRev_Ac_De_Over_Note_1 )
                  || ( pV_ulData_OAD[0] == CQua1_Re_De_Over_Note_1 )
                  || ( pV_ulData_OAD[0] == CQua2_Re_De_Over_Note_1 )
                  || ( pV_ulData_OAD[0] == CQua3_Re_De_Over_Note_1 )
                  || ( pV_ulData_OAD[0] == CQua4_Re_De_Over_Note_1 ) )
                {
                    if( (V_ucHappeningFlag) == C_Happen_EventState )		/*�����ʷ״̬���з����޻ָ�*/
                    {
                        switch(EventMappingTable[V_uci].EventNo)
                        {
                            case	C_OverForwardActiveEventNo:
                                    PF_CopyDataBytes(GStr_OverForwardActiveStr.Renewal, (V_ucDataBuff + V_usOffset), CLOverDemandRenew_Demand);
                                    break;
                            case	C_OverReverseActiveEventNo:
                                    PF_CopyDataBytes(GStr_OverReverseActiveStr.Renewal, (V_ucDataBuff + V_usOffset), CLOverDemandRenew_Demand);
                                    break;
                            case	C_1OverIdleDemandEventNo:
                                    PF_CopyDataBytes(GStr_Over1IdleDemandStr.Renewal, (V_ucDataBuff + V_usOffset), CLOverDemandRenew_Demand);
                                    break;
                            case	C_2OverIdleDemandEventNo:
                                    PF_CopyDataBytes(GStr_Over2IdleDemandStr.Renewal, (V_ucDataBuff + V_usOffset), CLOverDemandRenew_Demand);
                                    break;
                            case	C_3OverIdleDemandEventNo:
                                    PF_CopyDataBytes(GStr_Over3IdleDemandStr.Renewal, (V_ucDataBuff + V_usOffset), CLOverDemandRenew_Demand);
                                    break;
                            case	C_4OverIdleDemandEventNo:
                                    PF_CopyDataBytes(GStr_Over4IdleDemandStr.Renewal, (V_ucDataBuff + V_usOffset), CLOverDemandRenew_Demand);
                                    break;
                            default:
                                    break;
                        }
                    }
                    V_usOffset += CLOverDemandRenew_Demand;
                    V_usDataoffset += CLOverDemandRenew_Demand;
					
					V_ucOADFlag = 0x68;
                }
            }
            else if( pV_ulData_OAD[V_usi] == C_OverDemandRenew_HapTime )
            {
                if ( ( pV_ulData_OAD[0] == CPos_Ac_De_Over_Note_1 )
                  || ( pV_ulData_OAD[0] == CRev_Ac_De_Over_Note_1 )
                  || ( pV_ulData_OAD[0] == CQua1_Re_De_Over_Note_1 )
                  || ( pV_ulData_OAD[0] == CQua2_Re_De_Over_Note_1 )
                  || ( pV_ulData_OAD[0] == CQua3_Re_De_Over_Note_1 )
                  || ( pV_ulData_OAD[0] == CQua4_Re_De_Over_Note_1 ) )
                {
                    if( (V_ucHappeningFlag) == C_Happen_EventState )		/*�����ʷ״̬���з����޻ָ�*/
                    {
                        switch(EventMappingTable[V_uci].EventNo)
                        {
                            case	C_OverForwardActiveEventNo:
                                    PF_CopyDataBytes(GStr_OverForwardActiveStr.RenewalTime, (V_ucDataBuff + V_usOffset), CLOverDemandRenew_HapTime);
                                    break;
                            case	C_OverReverseActiveEventNo:
                                    PF_CopyDataBytes(GStr_OverReverseActiveStr.RenewalTime, (V_ucDataBuff + V_usOffset), CLOverDemandRenew_HapTime);
                                    break;
                            case	C_1OverIdleDemandEventNo:
                                    PF_CopyDataBytes(GStr_Over1IdleDemandStr.RenewalTime, (V_ucDataBuff + V_usOffset), CLOverDemandRenew_HapTime);
                                    break;
                            case	C_2OverIdleDemandEventNo:
                                    PF_CopyDataBytes(GStr_Over2IdleDemandStr.RenewalTime, (V_ucDataBuff + V_usOffset), CLOverDemandRenew_HapTime);
                                    break;
                            case	C_3OverIdleDemandEventNo:
                                    PF_CopyDataBytes(GStr_Over3IdleDemandStr.RenewalTime, (V_ucDataBuff + V_usOffset), CLOverDemandRenew_HapTime);
                                    break;
                            case	C_4OverIdleDemandEventNo:
                                    PF_CopyDataBytes(GStr_Over4IdleDemandStr.RenewalTime, (V_ucDataBuff + V_usOffset), CLOverDemandRenew_HapTime);
                                    break;
                            default:
                                    break;
                        }
                    }
                    V_usOffset += CLOverDemandRenew_HapTime;
                    V_usDataoffset += CLOverDemandRenew_HapTime;
					
					V_ucOADFlag = 0x68;
                }
            }
			else
			{
				SF_JudgeFixRCSD(pV_ulData_OAD[V_usi], V_ucDataBuff, &V_usOffset, &V_ucOADFlag);/*�̶��б�Ϸ����ж�*/
			}
			if(V_ucOADFlag != 0x68)	/*û�鵽����ֵBB*/
			{
				*(V_ucDataBuff + V_usOffset) = C_NotSupportAOD_DataBB;
				V_usOffset += 1;
				
				if((V_usOffset > V_usBuffMaxLen) || (V_usOffset > (C_EventMAXLen - 40)))	    /*��󳤶Ȳ��ܳ�������Buff���Ⱥ�����Buff����*/
				{
                    return	C_DataLenError;
				}
			}
		}
		PF_CopyDataBytes_698(V_ucDataBuff, pV_ucDataBuf, V_usOffset);
		*pV_usDataLen = V_usOffset;
	}
	return C_OK;
}
#if (_DEBUG_DB)
/***************************************************************************************************************************************************************
����ԭ�ͣ�uchar8 Inf_ReadEventLast_N(ulong32 * P_Data_Id_OAD, uchar8 * P_FixTime, uchar8 * P_Data, uchar8 * V_ucNextSign, ushort16 * P_Data_Length, uchar8 V_timeFlash)
����������ͨ�Ŷ�ȡ��n���¼�������1�Σ���1���к�����������
���������*P_Data_Id_OAD����һ��OAD��ʾ��ȡ�������ͣ�
                         ����300D0201����ʾ��ȡȫʧѹ�¼������1�ֽ�00��ʾ��ʾ��ʱ���ȡ��
														 ��00��ʾ��ȡ��XX�μ�¼����ʱ* P_FixTime��V_BlockNum��Ч.
				         ����OAD˳��Ϊ�������Զ�ӦOAD˳�򣬵�����OADΪFFFFFFFF���ʾ��������¼��ȡ��¼OAD����(�����̶��б�)��
         *P_FixTime������ʱ���¼�飬12���ֽڡ�
                     ��ʱ�����䳭����ǰ6���ֽڱ�ʾ��ʼʱ�䣬��6���ֽڱ�ʾ����ʱ�䣬ʱ���ʽssmmhhDDMMYY
    				 ���̶�ʱ�䳭��ʱ��ǰ6���ֽ����6���ֽ���ͬ����ʱ������������֡ʱ��ǰ6���ֽ�Ϊ��һ���¼ʱ�䡣
        *V_NextSign����Ϊ�����������֡��ʶ��Bit5--Bit4��ʾ�Ƿ�Ϊ����֡��������Ϊ1ʱ��ʾΪ����֡��������1ʱ��ʾ���״γ�����
        * V_Length�������ݻ�������󳤶ȣ�
	     V_timeFlash:��ʾ����ʱ�䳭���¼���¼ʱ���Ǹ��ݷ���ʱ�䡢���ǽ���ʱ�䡣AA��ʾ����ʱ�䣬��������Ϊ����ʱ��
���������
        *P_FixTime����Ϊ�������ʱ�����к���֡ʱ��������һ����¼��?�¼ʱ�?ǰ6���ֽ�)��
        *V_Length����������ʵ�ʳ��ȣ�
        *P_Data�������ݴ�Ż��棻
        *V_NextSign����Ϊ�����������֡��ʶ��
                     Bit5--Bit4��ʾ�Ƿ�Ϊ����֡��������Ϊ1ʱ��ʾΪ����֡��������1ʱ��ʾ���״γ�����
    			    Bit0-Bit3��ʾ�����������ݰ������¼���¼����(���10��).
                   Bit7-Bit6:��ʾ���̶�ʱ������䳭�����ݣ����������Ƿ�������1����¼
    						1����ʾ�������ݰ������1����¼��0����ʾ�������ݲ��������1����¼�������¼���¼���1������¼���¼�ӿں���
    					   (�簲ʱ���������ڼ����ݲ�����Ϊ0)�������̶�ʱ������䳭�������1����¼����Ϊ�������ݵ����1����ʱ���ǰ����顣
���ز�����C_OK��C_IICError��C_SPIError��C_DataLenError��C_IDError��C_NoData��C_Error
����˵������ȡ��2-10/1000�������ݴ������ڴ�������ࡢ�����ࡢ���ʵ�۵����������صĵ������ݣ���������Ӧ���Լ������б��г����������ĵ���Ӧ��Ϊ�ա�
���û��ƣ�ͨ�ŵ���
��    ע��ֻ�а�����Ӧ���������Ҫ���ﴦ��ʵ�ʰ�ʱ�����䳭����������InF_ReadEventData�����д���
******************************************************************************************************************************************************************/
uchar8 Inf_ReadEventLast_N(ulong32 * P_Data_Id_OAD, uchar8 * P_FixTime, uchar8 * P_Data, uchar8 * V_ucNextSign, ushort16 * P_Data_Length, uchar8 V_timeFlash)
{
	uchar8		V_ucTurn, V_uci, V_ucj, V_uck, V_ucData_Length, V_ucReturn;
    uchar8      V_ucNextDataNumTol, V_ucReadEventDegree, V_ucNextDataLenTol;
    uchar8      V_DataBuff[C_EventMAXLen]={0};
	ushort16	V_usOADTab_Length, V_usOAD_Data, V_usDataLength;
	ushort16	V_usOAD[C_EventMAXRelatedOAD];
	ushort16	V_usOffset=0, V_usDataoffset = 0;;
	Struct_FrozenConvert_Type Str_Encode;
    Struct_FrozenConvert_Type Str_EncodeNext;
    ulong32     V_ulOADoffset;
    uchar8 V_ucSpecicalDataLen = 0;

    V_ulOADoffset = P_Data_Id_OAD[0] & 0x000000FF;
	for(V_uci = 0; V_uci<EventMappingTable_Len; V_uci++)
	{
		if(((EventMappingTable[V_uci].WriteOAD &0xFFFFFF00) | V_ulOADoffset) == P_Data_Id_OAD[0])
		{
			break;
	    }
	}
	if(V_uci>=EventMappingTable_Len)
	{
		 return C_OtherErr;
    }

	V_ucReturn = InF_ReadEventData(P_Data_Id_OAD, P_FixTime, V_DataBuff, V_ucNextSign, P_Data_Length, V_timeFlash);
	if(V_ucReturn != C_OK)
	{
		return V_ucReturn;
	}
    V_ucReadEventDegree = (*V_ucNextSign) & 0x0F;//bit0-bit3����ʾ��ȡ������

	V_usOADTab_Length = C_EventMAXRelatedOADLen;
	if(InF_ReadOADTab_Data(EventMappingTable[V_uci].OADTab, (uchar8 *)&V_usOAD, &V_usOADTab_Length)!=C_OK)
	{
		return C_Error;
	}
	if(P_Data_Id_OAD[1] == 0xFFFFFFFF)
	{
        for( V_uck = 0; V_uck < V_ucReadEventDegree; V_uck++)
        {
		    PF_CopyDataBytes_698( &V_DataBuff[V_usOffset], &P_Data[V_usDataoffset], (CLEventDegree + CLEventHappenTime + CLEventEndTime) );
		    V_usOffset += CLEventDegree + CLEventHappenTime + CLEventEndTime;		/*�¼���š�����ʱ�䡢����ʱ��ƫ��*/
            V_usDataoffset += CLEventDegree + CLEventHappenTime + CLEventEndTime;	/*�¼���š�����ʱ�䡢����ʱ��ƫ��*/
            if(EventMappingTable[V_uci].SourceFlag == C_SourceExist)
		    {
                P_Data[V_usDataoffset] = V_DataBuff[V_usOffset];
			    V_usOffset += CLEventSource;	/*�¼�����Դƫ��*/
                V_usDataoffset += CLEventSource;
		    }
            /*�����¼���¼��Ԫ���ݳ���ƫ��*/
            SF_Event_SpecificDataLenCal(P_Data_Id_OAD[0], &V_ucSpecicalDataLen);
            PF_CopyDataBytes(&V_DataBuff[V_usOffset], &P_Data[V_usDataoffset], V_ucSpecicalDataLen);
            V_usOffset += V_ucSpecicalDataLen;
            V_usDataoffset += V_ucSpecicalDataLen;

			/*����OAD��˳����֯����*/
			for( V_ucTurn = 0; V_ucTurn < (V_usOADTab_Length/2); V_ucTurn++ )
			{
			    V_usOAD_Data = V_usOAD[V_ucTurn] & 0x1FFF; //���������б��е��к�

				V_ucNextDataNumTol = Str_FrozenConvert_Table[V_usOAD_Data].V_uc698NextNum;
	            V_ucNextDataLenTol = Str_FrozenConvert_Table[V_usOAD_Data].V_uc645Length;

	            Str_Encode = Str_FrozenConvert_Table[V_usOAD_Data];
				SF_FrozenDataFF_NextNum( &Str_Encode, V_usOAD_Data );//����������ֵ���ݳ��ȼ����ݸ���

	            if( ( SF_FrozenData_JudgeRateNum(V_usOAD_Data, Str_Encode.V_ulOAD) ) == C_Error )//����������Ӧ��գ����ݲ㷵������0xBB
	            {
	                P_Data[V_usDataoffset] = C_NotSupportAOD_DataBB;
	                V_usDataoffset += CL_NotSupportAOD_DataBB;
	                V_usOffset += V_ucNextDataLenTol;//ȫ�������ݳ���
	            }
	            else
	            {
					 if( Str_Encode.V_uc698Type == C_array ) //��Ҫ�����645��ʶ��
					 {
						 for( V_ucj=1; V_ucj <= Str_Encode.V_uc698NextNum; V_ucj++ )
						 {
	                           Str_EncodeNext = Str_FrozenConvert_Table[ V_usOAD_Data + V_ucj ];
	                           V_ucData_Length = Str_EncodeNext.V_uc645Length;
				               SF_FrozenDataFF_NextNum( &Str_EncodeNext, (V_usOAD_Data + V_ucj) );

			                   PF_CopyDataBytes_698(&V_DataBuff[V_usOffset], &P_Data[V_usDataoffset], Str_EncodeNext.V_uc645Length);
	                           V_usDataoffset += Str_EncodeNext.V_uc645Length;//���ݷ������ĳ���
	                            V_usOffset += V_ucData_Length;
						 }
	                     if( V_ucj < V_ucNextDataNumTol)//���ݿ�ȫ������
	                     {
	                          for( ; V_ucj <= V_ucNextDataNumTol; V_ucj++ )
	                          {
	                               Str_EncodeNext = Str_FrozenConvert_Table[ V_usOAD_Data + V_ucj ];
	                               V_ucData_Length = Str_EncodeNext.V_uc645Length;
	                               V_usOffset += V_ucData_Length;
	                          }
	                     }
				     }
					 else
					 {
			             PF_CopyDataBytes_698(&V_DataBuff[V_usOffset], &P_Data[V_usDataoffset], Str_Encode.V_uc645Length);
	                     V_usDataoffset += Str_Encode.V_uc645Length;//���ݷ������ĳ���
	                     V_usOffset += V_ucNextDataLenTol;//ȫ�������ݳ���
					 }
	            }
			    *P_Data_Length = V_usDataoffset;
			}
            if(V_ucTurn == 0)
            {
                V_usDataLength = *P_Data_Length;
                PF_CopyDataBytes_698(V_DataBuff, P_Data, V_usDataLength);
            }
		}
    }
    else
    {
        V_usDataLength = *P_Data_Length;
		PF_CopyDataBytes_698(V_DataBuff, P_Data, V_usDataLength);
    }
	return C_OK;
}
#endif

/**********************************************************************************************************
����ԭ�ͣ�uchar8 Inf_ReadEventLast_X(Str_Read_T *pStr_Read, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, Str_SuppInfo *pStr_SuppInfo)
������������ȡ��N���¼���¼����(����)
���������pStr_ReadΪ��ȡ�����ṹ��
    pV_ucDataBufΪ��ȡ�����ַ
	*pV_usDataLenΪ��ȡ������󳤶�
	pV_ucSupplementaryInformationΪ������Ϣ�����ַ
	*pV_usSIDataLenΪ������Ϣ������󳤶�
���������*pV_ucDataBufΪ��ȡ����
	*pV_usDataLenΪ��ȡ����ʵ�ʳ���
	pV_ucSupplementaryInformationΪ������Ϣ����
	*pV_usSIDataLenΪ������Ϣ����ʵ�ʳ���
���ز�����C_OK��ȷ���������ؾ������
����λ�ã��¼�ģ����¼���¼�ӿڵ���
��    ע��*pV_usDataLen������ڵ�����ȡֵ���ȣ���Ȼ���ش���
***************************************************************************************************************/
uchar8 Inf_ReadEventLast_X(Str_Read_T *pStr_Read, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, Str_SuppInfo *pStr_SuppInfo)
{
	uchar8		V_ucTurn, V_uci, V_ucj, V_uck, V_ucData_Length, V_ucReturn;
    uchar8      V_ucNextDataNumTol, V_ucReadEventDegree, V_ucNextDataLenTol;
    uchar8      V_ucDataBuff[C_EventMAXLen]={0};
	ushort16	V_usOADTab_Length, V_usOAD_Data, V_usDataLength;
	ushort16	V_usOAD[C_EventMAXRelatedOAD];
	ushort16	V_usOffset=0, V_usDataoffset = 0;;
	Struct_FrozenConvert_Type Str_Encode;
    Struct_FrozenConvert_Type Str_EncodeNext;
    ulong32     V_ulOADoffset, *pV_Data_Id_OAD;
    uchar8 V_ucSpecicalDataLen = 0;

    pV_Data_Id_OAD = pStr_Read->pV_ulROAD;

    V_ulOADoffset = pStr_Read->pV_ulROAD[0] & 0x000000FF;
	for(V_uci = 0; V_uci<EventMappingTable_Len; V_uci++)
	{
		if(((EventMappingTable[V_uci].WriteOAD &0xFFFFFF00) | V_ulOADoffset) == pV_Data_Id_OAD[0])
		{
			break;
	    }
	}
	if(V_uci>=EventMappingTable_Len)
	{
		 return C_OtherErr;
    }

	V_ucReturn = InF_GetData_Record_DataBase(pStr_Read, V_ucDataBuff, pV_usDataLen, pStr_SuppInfo);
	if(V_ucReturn != C_OK)
	{
		return V_ucReturn;
	}
    V_ucReadEventDegree = pStr_SuppInfo->V_ucFrameNum;/*bit0-bit3����ʾ��ȡ������*/

	V_usOADTab_Length = C_EventMAXRelatedOADLen;
	if(InF_ReadOADTab_Data(EventMappingTable[V_uci].OADTab, (uchar8 *)&V_usOAD, &V_usOADTab_Length)!=C_OK)
	{
		return C_Error;
	}
	if(pV_Data_Id_OAD[1] == 0xFFFFFFFF)
	{
        for( V_uck = 0; V_uck < V_ucReadEventDegree; V_uck++)
        {
            PF_CopyDataBytes_698( &V_ucDataBuff[V_usOffset], &pV_ucDataBuf[V_usDataoffset], (CLEventDegree + CLEventHappenTime + CLEventEndTime) );
		    V_usOffset += CLEventDegree + CLEventHappenTime + CLEventEndTime;		/*�¼���š�����ʱ�䡢����ʱ��ƫ��*/
            V_usDataoffset += CLEventDegree + CLEventHappenTime + CLEventEndTime;	/*�¼���š�����ʱ�䡢����ʱ��ƫ��*/

            if(EventMappingTable[V_uci].SourceFlag == C_SourceExist)
		    {
                pV_ucDataBuf[V_usDataoffset] = V_ucDataBuff[V_usOffset];
			    V_usOffset += CLEventSource;	/*�¼�����Դƫ��*/
                V_usDataoffset += CLEventSource;
		    }
            pV_ucDataBuf[V_usDataoffset] = V_ucDataBuff[V_usOffset];

            V_usOffset +=  CLEventReport;/*�����ϱ�״̬*/
            V_usDataoffset +=  CLEventReport;
            /*�����¼���¼��Ԫ���ݳ���ƫ��*/
            SF_Event_SpecificDataLenCal(pV_Data_Id_OAD[0], &V_ucSpecicalDataLen);

            PF_CopyDataBytes(&V_ucDataBuff[V_usOffset], &pV_ucDataBuf[V_usDataoffset], V_ucSpecicalDataLen);

            V_usOffset += V_ucSpecicalDataLen;
            V_usDataoffset += V_ucSpecicalDataLen;

			/*����OAD��˳����֯����*/
			for( V_ucTurn = 0; V_ucTurn < (V_usOADTab_Length/2); V_ucTurn++ )
			{
			    V_usOAD_Data = V_usOAD[V_ucTurn] & 0x1FFF; /*���������б��е��к�*/

				V_ucNextDataNumTol = Str_FrozenConvert_Table[V_usOAD_Data].V_uc698NextNum;
	            V_ucNextDataLenTol = Str_FrozenConvert_Table[V_usOAD_Data].V_uc645Length;

	            Str_Encode = Str_FrozenConvert_Table[V_usOAD_Data];

                SF_FrozenDataFF_NextNum( &Str_Encode, V_usOAD_Data );/*����������ֵ���ݳ��ȼ����ݸ���*/

	            if( ( SF_FrozenData_JudgeRateNum(V_usOAD_Data, Str_Encode.V_ulOAD) ) == C_Error )/*����������Ӧ��գ����ݲ㷵������0xBB*/
	            {
	                pV_ucDataBuf[V_usDataoffset] = C_NotSupportAOD_DataBB;

                    V_usDataoffset += CL_NotSupportAOD_DataBB;
	                V_usOffset += V_ucNextDataLenTol;/*ȫ�������ݳ���*/
	            }
                else
	            {
                    if( Str_Encode.V_uc698Type == C_array ) /*��Ҫ�����645��ʶ��*/
                    {
                        for( V_ucj=1; V_ucj <= Str_Encode.V_uc698NextNum; V_ucj++ )
                        {
                            Str_EncodeNext = Str_FrozenConvert_Table[ V_usOAD_Data + V_ucj ];
                            V_ucData_Length = Str_EncodeNext.V_uc645Length;

                            SF_FrozenDataFF_NextNum( &Str_EncodeNext, (V_usOAD_Data + V_ucj) );

                            PF_CopyDataBytes_698(&V_ucDataBuff[V_usOffset], &pV_ucDataBuf[V_usDataoffset], Str_EncodeNext.V_uc645Length);

                            V_usDataoffset += Str_EncodeNext.V_uc645Length;/*���ݷ������ĳ���*/
                            V_usOffset += V_ucData_Length;
                        }
                        if( V_ucj < V_ucNextDataNumTol)/*���ݿ�ȫ������*/
                        {
                            for( ; V_ucj <= V_ucNextDataNumTol; V_ucj++ )
                            {
                                Str_EncodeNext = Str_FrozenConvert_Table[ V_usOAD_Data + V_ucj ];

                                V_ucData_Length = Str_EncodeNext.V_uc645Length;
                                V_usOffset += V_ucData_Length;
                            }
                        }
				     }
					 else
					 {
			             PF_CopyDataBytes_698(&V_ucDataBuff[V_usOffset], &pV_ucDataBuf[V_usDataoffset], Str_Encode.V_uc645Length);

                         V_usDataoffset += Str_Encode.V_uc645Length;/*���ݷ������ĳ���*/
	                     V_usOffset += V_ucNextDataLenTol;/*ȫ�������ݳ���*/
					 }
	            }
			    *pV_usDataLen = V_usDataoffset;
			}
            if(V_ucTurn == 0)
            {
                V_usDataLength = *pV_usDataLen;
                PF_CopyDataBytes_698(V_ucDataBuff, pV_ucDataBuf, V_usDataLength);
            }
		}
    }
    else
    {
        V_usDataLength = *pV_usDataLen;
		PF_CopyDataBytes_698(V_ucDataBuff, pV_ucDataBuf, V_usDataLength);
    }
	return C_OK;
}

/**********************************************************************************************************
����ԭ�ͣ�uchar8 InF_Get_EventModule(Str_Read_T *pStr_Read, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, uchar8 *pV_ucSupplementaryInformation, ushort16 *pV_usSIDataLen)
����������ͨ�Ŷ�ȡ�¼���¼����
���������pStr_ReadΪ��ȡ�����ṹ��
    pV_ucDataBufΪ��ȡ�����ַ
	*pV_usDataLenΪ��ȡ������󳤶�
	pV_ucSupplementaryInformationΪ������Ϣ�����ַ
	*pV_usSIDataLenΪ������Ϣ������󳤶�
���������*pV_ucDataBufΪ��ȡ����
	*pV_usDataLenΪ��ȡ����ʵ�ʳ���
	pV_ucSupplementaryInformationΪ������Ϣ����
	*pV_usSIDataLenΪ������Ϣ����ʵ�ʳ���
���ز�����C_OK��ȷ���������ؾ������
����λ�ã������������
��    ע��
***************************************************************************************************************/
uchar8 InF_Get_EventModule(Str_Read_T *pStr_Read, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, Str_SuppInfo *pStr_SuppInfo)
{
    uchar8 V_ucReturn = C_OtherErr;
	uchar8 V_ucNum, V_ucReadBuff[2];
	ushort16 V_usOffset, V_usLen;
	Str_Read_T Str_ReadOADTemp;
	Str_SuppInfo Str_SuppInfoTemp;
	
    if((pStr_Read->pV_ulROAD[0] & 0x000000FF) == 0x00000001)/*����һ�μ�¼����*/
    {
        V_ucReturn = Inf_ReadEventLast_1(pStr_Read, pV_ucDataBuf, pV_usDataLen, pStr_SuppInfo);
    }
    else/*����2-N��¼����*/
    {
        V_ucReturn = Inf_ReadEventLast_X(pStr_Read, pV_ucDataBuf, pV_usDataLen, pStr_SuppInfo);
		
		if( (V_ucReturn == C_OK)
			&& (pStr_SuppInfo -> V_ucFrameNum != C_InActive)/*����������*/
			&& (pStr_SuppInfo -> V_ucLastFlag == C_Active_LastEvent) )/*���������ݰ������һ��*/
		{
			V_ucNum = pStr_SuppInfo -> V_ucFrameNum;
			V_usLen = *pV_usDataLen  / V_ucNum;
			V_usOffset = V_usLen * (V_ucNum - 1);
			
			V_ucReadBuff[0] = 9;/*����9*/
    		V_ucReadBuff[1] = 1;/*��N��*/
			
			Str_ReadOADTemp.pV_ulROAD = pStr_Read -> pV_ulROAD;
			Str_ReadOADTemp.pV_ulROAD[0] = ((Str_ReadOADTemp.pV_ulROAD[0] & 0xFFFFFF00) | 0x01);
			Str_ReadOADTemp.pV_ucRST = V_ucReadBuff;
			Str_ReadOADTemp.V_usROAD_Num = 1;
			Str_ReadOADTemp.V_ucReadMode = C_OtherMode;
			Str_ReadOADTemp.V_ucChannelNo = 0xFF;
			
			Str_SuppInfoTemp.pV_usEncode = pStr_SuppInfo->pV_usEncode;
			
			V_ucReturn = Inf_ReadEventLast_1(pStr_Read, pV_ucDataBuf + V_usOffset, &V_usLen, &Str_SuppInfoTemp);
			
			if(V_ucReturn == C_OK)
			{
				pStr_SuppInfo->V_ucLastFlag = Str_SuppInfoTemp.V_ucLastFlag;
			}
		}
    }
    return V_ucReturn;
}
/*******************************************************************************
����ԭ�ͣ� uchar8 Inf_GetPowerDownEventType(uchar8 EventNo)
���������� ��ȡ�¼���ǰ״̬���������ǻָ�
���������
���������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 Inf_GetPowerDownEventType(uchar8 EventNo)
{
    uchar8 V_ucReturn = C_End_EventState;

    if(EventNo < C_EventNoLength)
    {
        V_ucReturn = GV_ucEvent_Hstate[EventNo];
    }

    return V_ucReturn;
}

/*******************************************************************************
����ԭ�ͣ�SF_FillEvtRenew
�������������¼�ʵʱ�������뻺����
���������V_usOffset����������OAD������public����е�ƫ��(�к�)��
        V_usOAD_State������OAD��������������
        *V_ucBuff���������ݻ�����׵�ַ;
        *V_usOffset����ǰ���ݴ����V_ucBuff�е��׵�ַƫ��
		V_ucEvent_Flag���¼�����������־����4λ0x01������0x02��������4λΪ�з��������������¼�������
��������� *V_ucBuff���������ݻ�����׵�ַ;
        *V_usOffset����ǰ���ݷźú��ƫ��
���ز�������
����λ�ã�Inf_GetRecordData�����¼���ǰ����ʱ����
��    ע��
*******************************************************************************/
void SF_FillEvtRenew(ushort16 V_usLineNum, ushort16 V_usOAD_State, uchar8 *pV_ucBuff, ushort16 *pV_usOffset, uchar8 V_ucEvtStatus, uchar8 V_ucEvent_Flag)
{
	ulong32 V_ulReadBuff[3] = {0}, V_ul698OAD;
	uchar8 V_ucData_Length, V_ucLen;
	
	V_ul698OAD = Str_FrozenConvert_Table[V_usLineNum].V_ulOAD;
	V_ucData_Length = Str_FrozenConvert_Table[V_usLineNum].V_uc645Length;
	
	if(V_ucEvtStatus == C_Need)
	{
		switch(V_ucEvent_Flag & 0xF0)
		{
			case	0x10:
				V_ulReadBuff[0] = CLossAVol_FF_1;
				break;
			case	0x20:
				V_ulReadBuff[0] = CLossBVol_FF_1;
				break;
			case	0x30:
				V_ulReadBuff[0] = CLossCVol_FF_1;
				break;
			case	0x40:
				V_ulReadBuff[0] = CLowAVol_FF_1;
				break;
			case	0x50:
				V_ulReadBuff[0] = CLowBVol_FF_1;
				break;
			case	0x60:
				V_ulReadBuff[0] = CLowCVol_FF_1;
				break;
			case	0x70:
				V_ulReadBuff[0] = COverAVol_FF_1;
				break;
			case	0x80:
				V_ulReadBuff[0] = COverBVol_FF_1;
				break;
			case	0x90:
				V_ulReadBuff[0] = COverCVol_FF_1;
				break;
			case	0xA0:
				V_ulReadBuff[0] = CBreakAVol_FF_1;
				break;
			case	0xB0:
				V_ulReadBuff[0] = CBreakBVol_FF_1;
				break;
			case	0xC0:
				V_ulReadBuff[0] = CBreakCVol_FF_1;
				break;
			case	0xD0:
				V_ulReadBuff[0] = CNoBalVol_FF_1;
				break;
			case	0xE0:
				V_ulReadBuff[0] = CNoBalCurr_FF_1;
				break;
			case	0xF0:
				V_ulReadBuff[0] = CSevNoBalCurr_FF_1;
				break;
			default:
				break;
		}
		V_ulReadBuff[1] = V_ul698OAD;
		V_ulReadBuff[1] |= (ulong32)(V_usOAD_State << 13);
		V_ulReadBuff[2] = 0xFFFFFFFF;
		
		V_ucLen = V_ucData_Length;
		if(Inf_ReadEventRenew(V_ulReadBuff, (pV_ucBuff + *pV_usOffset), &V_ucLen) != C_OK)   /*��ȡ����*/
		{
			memset((pV_ucBuff + *pV_usOffset), 0xAA, V_ucData_Length);
		}
	}
	*pV_usOffset += V_ucData_Length;
}

/*******************************************************************************
����ԭ�ͣ�SF_FillEvtComData
�������������¼���ͨ���ݣ���ʵʱ���ݣ����뻺����
���������V_usLineNum����������OAD������public����е�ƫ��(�к�)��
        *pV_ucBuff���������ݻ�����׵�ַ;
        *pV_usOffset����ǰ���ݴ����V_ucBuff�е��׵�ַƫ��
		V_ucEvtStatus�������Ƿ���Ҫ��ȡ��״̬
��������� *V_ucBuff���������ݻ�����׵�ַ;
        *V_usOffset����ǰ���ݷźú��ƫ��
���ز�������
����λ�ã�Inf_GetRecordData�����¼���ǰ����ʱ����
��    ע��
*******************************************************************************/
void SF_FillEvtComData(ushort16 V_usLineNum, uchar8 *pV_ucBuff, ushort16 *pV_usOffset, uchar8 V_ucEvtStatus)
{
	ulong32 V_ul698OAD;
	ushort16 V_usData_Length, V_usEncode;
	uchar8 V_ucData_Length;
	
	V_ul698OAD = Str_FrozenConvert_Table[V_usLineNum].V_ulOAD;
	V_ucData_Length = Str_FrozenConvert_Table[V_usLineNum].V_uc645Length;
	
	if(V_ucEvtStatus == C_Need)
	{
		V_usData_Length = V_ucData_Length;
		if(InF_GetData_ObjectManage(V_ul698OAD, (pV_ucBuff + *pV_usOffset), &V_usData_Length, &V_usEncode) != C_OK)   /*��ȡ����*/
		{
			memset((pV_ucBuff + *pV_usOffset), 0xAA, V_ucData_Length);
		}
	}
	*pV_usOffset += V_ucData_Length;
}

/*******************************************************************************
����ԭ�ͣ�uchar8 Inf_GetRecordData(uchar8 *V_ucData, ushort16 *V_ucLength, ulong32 V_OADTab, uchar8 V_ucTypeFlag)
������������ȡ�¼���¼�Ͷ�����������
���������*V_ucData���������Ż���
        *V_ucLength�����泤�ȣ�
        V_OADTab���¼�����OAD��ű���Ϊ������ø�OADΪ0x50FFFFFF;
        V_ucTypeFlag��Ϊ�¼�ʱ���¼�����������־����4λ0x01������0x02��������4λΪ�з��������������¼������֣�
                        Ϊ����ʱ����������
���������*V_ucData����ȡ���ݵĻ���;
        *V_ucLength����ȡ�����ݳ���;
���ز�����C_OK��C_Error
����λ�ã��¼���¼������
��    ע��
*******************************************************************************/
uchar8 Inf_GetRecordData(uchar8 *V_ucData, ushort16 *V_usLength, ulong32 V_ulOADTab, uchar8 V_ucTypeFlag)
{
    uchar8 V_ucTurn, V_uci= 0, V_uc645DINum;
	ushort16 V_usOADTab_Length;
	uchar8 V_ucData_Length;
	ushort16 V_usOAD[300], V_usOAD_Data, V_usOAD_State;
	ulong32 V_ul698OAD;
	ushort16 V_usOffset = 0;
	uchar8 V_ucType;
	ushort16 V_usBuffMaxLen;
	uchar8 V_ucDataBuff[C_EventMAXLen] = {0};
    uchar8 V_ucBuff_Zero[C_3Curr_Length] = {0};
    uchar8 V_ucCurrentTime[CLDate_Week_Time], V_ucBeginTime[CLDate_Week_Time], V_ucFrozenType, V_ucNum, V_usOADNum, V_ucMulti;
    ushort16 V_usData_Length, V_usEncode;
    ulong32 V_ulNum, V_ulOADNumDI, V_ulOADTable, V_ulSubDays, V_ulSubHours, V_ulSubMins, V_ulIntertime, V_ulFrozenNum, V_ulSubResult;
    uchar8 V_ucIntertimeFlag[96] = {0}, V_ucEvent_Flag, V_ucRecType, V_ucEvtStatus = C_NoNeed;

    V_usBuffMaxLen = *V_usLength;

    if( (V_ulOADTab & 0xFF000000) == C_FrzOAD )
    {
        V_ucRecType = C_Frz;
    }
    else
    {
        V_ucRecType = C_Evt;
    }
    /*�����������⴦��*/
    if(V_ucRecType == C_Frz)
    {
        V_usData_Length = CLDate_Week_Time;
        if( InF_GetData_ObjectManage(CDate_Time, &V_ucCurrentTime[0], &V_usData_Length, &V_usEncode) != C_OK )
        {
            return C_Error;
        }
        if(V_usBuffMaxLen < CLDate_Time)
        {
            return C_DataLenError;
        }
        PF_CopyDataBytes(&V_ucCurrentTime[0], V_ucDataBuff, CLDate_Week_Time);
        V_usOffset += CLDate_Week_Time;

        /*���ݶ������ͣ���ֵ��OAD��ʶ��*/
        V_ucFrozenType = V_ucTypeFlag;

        if( ( V_ucFrozenType & 0xf0 ) == C_Minute_Type )    /*���Ӷ���*/
        {
            V_ucNum = (V_ucFrozenType & 0x0f);    /*������*/
            V_usData_Length = 6 * C_FreezeMAXRelatedOAD;
            if( InF_GetMinFreezeNum_OADTab(V_ucNum, (uchar8 *)&V_usOAD, &V_usData_Length) != C_OK )
            {
                return C_Error;
            }
            V_usOADNum = V_usData_Length / 6;
            if(V_usOADNum > C_FreezeMAXRelatedOAD)
            {
                return C_Error;
            }
            V_ulNum = V_ucNum;
            V_ulNum <<= 21;
            V_ul698OAD = C_RelatedOAD_Min | V_ulNum;
        }
        else
        {
            switch (V_ucFrozenType)
            {
                case C_Immediate_Type:
                {
                    V_ulOADNumDI = CI_Free_OADTabLen_T;
                    V_ulOADTable = CI_Free_OADTab;
                    V_ul698OAD = C_RelatedOAD_Immid;
                }break;
                case C_Hour_Type:
                {
                    V_ulOADNumDI = CH_Free_OADTabLen_T;
                    V_ulOADTable = CH_Free_OADTab;
                    V_ul698OAD = C_RelatedOAD_Hour;
                }break;
                case C_Day_Type:
                case C_Day_Type_Add:
                {
                    V_ulOADNumDI = CD_Free_OADTabLen_T;
                    V_ulOADTable = CD_Free_OADTab;
                    V_ul698OAD = C_RelatedOAD_Day;
                }break;
                case C_Settlement_Type:
                {
                    V_ulOADNumDI = CSett_Free_OADTabLen_T;
                    V_ulOADTable = CSett_Free_OADTab;
                    V_ul698OAD = C_RelatedOAD_Settle;
                }break;
                case C_Month_Type:
                case C_Month_Type_Add:
                {
                    V_ulOADNumDI = CM_Free_OADTabLen_T;
                    V_ulOADTable = CM_Free_OADTab;
                    V_ul698OAD = C_RelatedOAD_Month;
                }break;
                case C_Change_TimeZone_Type:
                {
                    V_ulOADNumDI = CTZ_Free_OADTabLen_T;
                    V_ulOADTable = CTZ_Free_OADTab;
                    V_ul698OAD = C_RelatedOAD_TimeZone;
                }break;
                case C_Change_TimePeriod_Type:
                {
                    V_ulOADNumDI = CPT_Free_OADTabLen_T;
                    V_ulOADTable = CPT_Free_OADTab;
                    V_ul698OAD = C_RelatedOAD_TimeRegion;
                }break;
                case C_Change_Fate_Type:
                {
                    V_ulOADNumDI = CR_Free_OADTabLen_T;
                    V_ulOADTable = CR_Free_OADTab;
                    V_ul698OAD = C_RelatedOAD_RateTalbe;
                }break;
                case C_Change_Ladder_Type:
                {
                    V_ulOADNumDI = CL_Free_OADTabLen_T;
                    V_ulOADTable = CL_Free_OADTab;
                    V_ul698OAD = C_RelatedOAD_StepTable;
                }break;
                case C_YSettle_Type:
                {
                    V_ulOADNumDI = CYSettle_Free_OADTabLen_T;
                    V_ulOADTable = CYSettle_Free_OADTab;
                    V_ul698OAD = C_RelatedOAD_YSettle;
                }break;
                default:
                    return C_Error;
                break;
            }

            /*��OAD��OAD����*/
            V_usData_Length = CLTZ_Free_OADTabLen_T;
            if( InF_GetData_ObjectManage(V_ulOADNumDI, &V_usOADNum, &V_usData_Length, &V_usEncode) != C_OK )
            {
                return C_Error;
            }

            if(V_usOADNum > C_FreezeMAXRelatedOAD)
            {
                return C_Error;
            }


            V_usData_Length = 6 * V_usOADNum;
            if( InF_ReadOADTab_Data(V_ulOADTable, (uchar8 *)&V_usOAD, &V_usData_Length) != C_OK )
            {
                return C_Error;
            }
        }
        SF_GetFreeze_StartTime(V_ucBeginTime);

        for(V_ucTurn = 0; V_ucTurn < (V_usOADNum * 3); V_ucTurn++)
        {
            V_usOAD[V_ucTurn] &= 0x1FFF;

            if(V_usOAD[V_ucTurn + 1] == 0)
            {
                V_usOAD[V_ucTurn + 1] = 1;
            }

            if((V_ucFrozenType & 0xf0) == C_Minute_Type)    /*���Ӷ���*/
            {
                if(PF_TimeSub_Min_698(V_ucCurrentTime, V_ucBeginTime, &V_ulSubMins) == C_GreaterThan)
                {
                    PF_BufferXToUlong32((uchar8 *)&V_usOAD[V_ucTurn + 1], &V_ulIntertime, 2);
                    if(V_ulSubMins % V_ulIntertime)
                    {
                        V_ucIntertimeFlag[V_ucTurn / 3] = 0x68;
                    }
                }
            }
            else
            {
                switch (V_ucFrozenType)
                {
                    case C_Hour_Type:       /*Сʱ����*/
                    {
                        if(PF_TimeSub_Hour_698(V_ucCurrentTime, V_ucBeginTime, &V_ulSubHours) == C_GreaterThan)
                        {
                            PF_BufferXToUlong32((uchar8 *)&V_usOAD[V_ucTurn + 1], &V_ulIntertime, 2);
                            if(V_ulSubHours % V_ulIntertime)
                            {
                                V_ucIntertimeFlag[V_ucTurn / 3] = 0x68;
                            }
                        }
                    }break;
                    case C_Day_Type:        /*�ն���*/
                    {
                        if(PF_TimeSub_Day_698(V_ucCurrentTime, V_ucBeginTime, &V_ulSubDays) == C_GreaterThan)
                        {
                            if(V_ulSubDays % V_usOAD[V_ucTurn + 1])
                            {
                                V_ucIntertimeFlag[V_ucTurn / 3] = 0x68;
                            }
                        }
                    }break;
                    case C_Month_Type:      /*�¶���*/
                    {    /*����2��ʱ������*/
                        V_ulSubResult = 12 * (V_ucCurrentTime[5] - V_ucBeginTime[5]);

                        V_ulSubResult += V_ucCurrentTime[4];

                        V_ulSubResult -= V_ucBeginTime[4];

                        PF_BufferXToUlong32((uchar8 *)&V_usOAD[V_ucTurn+1], &V_ulIntertime, 2);

                        if(V_ulSubResult%V_ulIntertime)
                        {
                            V_ucIntertimeFlag[V_ucTurn/3] = 0x68;
                        }

                    }break;
                    case C_Change_TimeZone_Type:
                    case C_Immediate_Type:  /*˲ʱ����*/
                    case C_Change_TimePeriod_Type:
                    case C_Change_Fate_Type:
                    case C_Change_Ladder_Type:
                    case C_Settlement_Type: /*�����ն���*/
                    case C_Day_Type_Add:    /*�ն��Ჹ��*/
                    case C_YSettle_Type:    /*���ݽ��㶳��*/
                    case C_Month_Type_Add:  /*�¶��Ჹ��*/
                        break;
                    default:
                        return C_Error;
                    break;
                }
            }
            V_ucTurn += 2;
        }
        /*����һ�ζ���������ݣ���ֵ*/
        V_ucData_Length = 4;
        if(InF_ReadLaterFreezeNum(V_ul698OAD, (uchar8 *)&V_ulFrozenNum, &V_ucData_Length) != C_OK)
        {
            return C_Error;
        }
        if(V_usBuffMaxLen < ( V_usOffset + 4 ) )
        {
            return C_DataLenError;
        }
        PF_CopyDataBytes((uchar8 *)&V_ulFrozenNum, (V_ucDataBuff + V_usOffset), 4);
        V_usOffset += 4;

        for( V_ucTurn = 0; V_ucTurn < (V_usOADNum * 3); V_ucTurn++)
        {
            if(V_ucIntertimeFlag[V_ucTurn / 3] != 0x68)
            {
                break;
            }
            V_ucTurn += 2;
        }

        if( V_ucTurn >= (V_usOADNum * 3) )
        {
            return C_Error;
        }
        V_usOADTab_Length = V_usOADNum;/*��������б������ֵ*/
    }
    else/*�¼�����*/
    {
        V_usOADTab_Length = 120;
        if(InF_ReadOADTab_Data(V_ulOADTab, (uchar8 *)&V_usOAD, &V_usOADTab_Length) != C_OK)
        {
            return C_Error;
        }
        V_usOADTab_Length = (V_usOADTab_Length / 2);
    }

	/*����OAD��˳����֯����*/
	for( V_ucTurn = 0; V_ucTurn < V_usOADTab_Length; V_ucTurn++)
	{
        if(V_ucRecType == C_Frz)
        {
            V_ucMulti = 3 * V_ucTurn;/*����ÿ��洢6�ֽڣ�2*3��*/
        }
        else
        {
            V_ucMulti = V_ucTurn;/*�¼�ÿ��洢2�ֽڣ�2*1��*/
        }
		V_usOAD_Data = V_usOAD[V_ucMulti] & 0x1FFF;
		V_usOAD_State = V_usOAD[V_ucMulti] >> 13;

		if(V_usOAD_Data > Str_FrozenConvert_Table_Len)
		{
			return C_Error;
		}

		V_ul698OAD = Str_FrozenConvert_Table[V_usOAD_Data].V_ulOAD;
		V_ucData_Length = Str_FrozenConvert_Table[V_usOAD_Data].V_uc645Length;
		V_ucType = Str_FrozenConvert_Table[V_usOAD_Data].V_uc698Type;
		V_uc645DINum = Str_FrozenConvert_Table[V_usOAD_Data].V_uc698NextNum;

        if(V_ucRecType == C_Frz)/*�������д���*/
        {
            if(V_ucIntertimeFlag[V_ucTurn] == 0x68)/*���ᣬδ��ʱ�䣬��AA*/
            {
                for( V_uci = 0; V_uci < V_ucData_Length; V_uci++)
                {
                    *(V_ucDataBuff + V_usOffset) = 0xAA;
                    V_usOffset += 1;
                }
                if( V_usOffset > V_usBuffMaxLen )	    /*��󳤶Ȳ��ܳ�������Buff���Ⱥ�����Buff����*/
                {
                    return	C_DataLenError;
                }
                else
                {
                    continue;
                }
            }
            V_ucEvent_Flag = 0;/*����ʱ���¼���־��0*/

            V_ucEvtStatus = C_Need;/*����ȡ�����б���������ж��Ƿ���Ҫ��ȡ��������Ϊ�����ַ���������ͳһ����Ҫ*/
        }
        else/*�¼������д���*/
        {
            V_ucEvent_Flag = V_ucTypeFlag;

            if ( ( ( ( V_usOAD_State == 0x0001 ) || ( V_usOAD_State == 0x0002 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x01 ) )
                  || ( ( ( V_usOAD_State == 0x0003 ) || ( V_usOAD_State == 0x0004 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x02 ) ) )
            {
                V_ucEvtStatus = C_Need;/*����ȡ�����б���������ж��Ƿ���Ҫ��ȡ������ͳһ�ñ�־*/
            }
			else
			{
				V_ucEvtStatus = C_NoNeed;
			}
        }

        if ( ( ( V_ucEvent_Flag & 0x0C ) == 0x04 )
          && ( ( V_usOAD_State == 0x0003 ) || ( V_usOAD_State == 0x0004 ) ) )
		{
			memset((V_ucDataBuff + V_usOffset), 0xAA, V_ucData_Length);
			V_usOffset += V_ucData_Length;
		}
		else if ( ( V_ul698OAD == CKey_State )
               && ( V_usOAD_State == 0x0001 )
			   && ( V_ulOADTab == CProgKD_OADTab ) )                 /*����ǰ��Կ״̬*/
        {
			if((V_ucEvent_Flag & 0x03) == 0x01)
			{
            	PF_CopyDataBytes(GV_KeyHState, (V_ucDataBuff + V_usOffset), CLKey_State_698);
			}
			V_usOffset += CLKey_State_698;
        }
        else if( (V_ucRecType == C_Evt)
                && (V_ucEvent_Flag & 0xF0)/*�¼���¼����ʵʱ���ݵ�*/
				&& ( ( (V_ul698OAD & 0xffff0000) == 0x20290000)/*��ʱ��*/
					|| ((V_ul698OAD & 0xffff0000) == 0x20260000)/*��ѹ��ƽ��*/
					|| ((V_ul698OAD & 0xffff0000) == 0x20270000) ) )/*������ƽ��*/
        {
            if(V_ucType == C_array)     /*��Ҫ�����645��ʶ��*/
			{
				for( V_uci = 1; V_uci <= V_uc645DINum; V_uci++)
				{
                    SF_FillEvtRenew(V_usOAD_Data + V_uci, V_usOAD_State, V_ucDataBuff, &V_usOffset, V_ucEvtStatus, V_ucEvent_Flag);
				}
			}
			else
			{
				SF_FillEvtRenew(V_usOAD_Data, V_usOAD_State, V_ucDataBuff, &V_usOffset, V_ucEvtStatus, V_ucEvent_Flag);
			}
        }
		else if ( ( V_ul698OAD == CPhaseFF_Curr )
		       && ( V_ulOADTab == CAll_Loss_Vol_OADTab )
			   && ( V_usOAD_State == 0x0001 )
			   && ( ( V_ucEvent_Flag & 0x03 ) == 0x01 ) )
		{
			if(PF_Campare_Data(GStr_TotalvoltageloseStr.NoVoltageCurrent, V_ucBuff_Zero, CLPhaseFF_Curr) != C_Equal)
			{
				PF_CopyDataBytes(GStr_TotalvoltageloseStr.NoVoltageCurrent, (V_ucDataBuff + V_usOffset), CLPhaseFF_Curr);
				V_usOffset += CLPhaseFF_Curr;
			}
			else
			{
				for( V_uci = 1; V_uci <= V_uc645DINum; V_uci++)
				{
					SF_FillEvtComData(V_usOAD_Data + V_uci, V_ucDataBuff, &V_usOffset, C_Need);
				}
			}
		}
		else
		{
			if( ( ( V_ucType == C_array ) || ( ( V_ucType == C_structure ) && ( V_uc645DINum > 1 ) ) )    /*��Ҫ�����*/
				&& ( (V_ul698OAD != CFirst_TZone_Data)
					&& (V_ul698OAD != CSec_TZone_Data)
					&& (V_ul698OAD != C_RelayFa_State) ) )/*ʱ����ͼ̵����������Ҫforѭ����*/
			{
				for( V_uci = 1; V_uci <= V_uc645DINum; V_uci++)
				{
					SF_FillEvtComData(V_usOAD_Data + V_uci, V_ucDataBuff, &V_usOffset, V_ucEvtStatus);
				}
			}
			else
			{
				if(V_ucEvtStatus == C_Need)
				{
                    if ( ( ( ( V_ul698OAD & 0xFFFFFF00 ) == CSec_TZone_Data ) && ( V_ul698OAD != CSec_TZone_Data ) )
                      || ( ( ( V_ul698OAD & 0xFFFFFF00 ) == CFirst_TZone_Data ) && ( V_ul698OAD != CFirst_TZone_Data ) ) )
                    {
                        V_usData_Length = CLFirst_TZone_Data;
                        V_ucData_Length = Str_FrozenConvert_Table[V_usOAD_Data].V_uc645Length;

                        if( InF_GetData_ObjectManage( ( V_ul698OAD & 0xFFFFFF00 ), (V_ucDataBuff + V_usOffset), &V_usData_Length, &V_usEncode) == C_OK )
                        {
                            V_ucDataBuff[V_usOffset] = V_ucDataBuff[V_usOffset + ( ((uchar8)(V_ul698OAD)) - 1) * 3];
                            V_ucDataBuff[V_usOffset + 1] = V_ucDataBuff[V_usOffset+( ((uchar8)(V_ul698OAD)) - 1 ) * 3 + 1];
                            V_ucDataBuff[V_usOffset + 2] = V_ucDataBuff[V_usOffset+( ((uchar8)(V_ul698OAD)) - 1 ) * 3 + 2];
                        }
                        else
                        {
							memset((V_ucDataBuff + V_usOffset), 0xAA, V_ucData_Length);
							V_usOffset += V_ucData_Length;
                        }
                        V_usOffset += V_ucData_Length;
                    }
                    else
                    {
						SF_FillEvtComData(V_usOAD_Data, V_ucDataBuff, &V_usOffset, C_Need);
                    }
				}
				else
				{
					V_usOffset += V_ucData_Length;
				}
			}
		}
		if( (V_usOffset > V_usBuffMaxLen) || (V_usOffset > (C_EventMAXLen - 40) ) )	/*��󳤶Ȳ��ܳ�������Buff���Ⱥ�����Buff����*/
		{
			return	C_DataLenError;
		}
	}

	PF_CopyDataBytes_698(V_ucDataBuff, V_ucData, V_usOffset);
	*V_usLength = V_usOffset;

	return C_OK;
}


