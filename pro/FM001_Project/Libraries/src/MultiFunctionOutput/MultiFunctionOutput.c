/********************************************************************************************
Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     MultiFunctionOutput.c
Version:       V1
Author:        
Date:          2014-3-12
Description:   �๦�ܶ˿����
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
#include "MultiFunctionOutput.h"
#include "IO.h"
#include "timer.h"

static uchar8 GV_ucMultiFunctionOutput;             /*���ڶ๦�����������*/
                                                    /*C_SecondPulseOutput��������*/
                                                    /*C_DemandPulseOutput��������������*/
                                                    /*C_RatePulseOutput��ʱ��Ͷ������*/

/*******************************************************************************
����ԭ��: void InF_MultiFunctionOutput_Init(void)
��������: �๦������ϵ��ʼ���Ĵ���
�������: ��
�������: �๦��������ϵ��Ĭ��Ϊ������
���ز���: ��
����λ��: ���ϵ��ʼ������
��    ע: �ϵ���������壬���������ֳ�ʼ��Ϊ������
*******************************************************************************/
void InF_MultiFunctionOutput_Init(void)
{
	GV_ucMultiFunctionOutput = C_SecondPulseOutput;
	
	DF_MultiFunction_SelectSecondPulse();
	DF_MultiFunction_OutputSecondPulse();
	
	SF_Set_MultiFunctionTimer(C_Interval_0ms);
}

/*******************************************************************************
����ԭ��: uchar8 InF_ModifyFunctionWord(uchar8 V_Data)
��������: ͨ������ģʽ��ʱֱ�ӵ��ñ�������ͨ��ģ�鲻��Ҫ�ж�����Ϊʲô�������
�������: V_ucData��λ�����õ����ݣ�ԭʼ���ݣ�����Ҫת����ͨ��ģ����Բ��жϺϷ���	
�������: �๦�ܶ���������������Ĺ���˵��
���ز���: C_OK�����������ȷ��C_DataError���������ݴ���	
����λ��: ͨ�ŵ���
��    ע: ͨ���޸Ķ๦��ģʽ��ʱ�����ñ�����									
         �ڱ������ڲ����ж��Ƿ��޸�Ϊ������										
         ����Ϊ�����壺����תΪ�������������������������						
         ����Ϊ�������壺������תΪ��������ĳ�̬								
         ����Ϊ�Ƿ�ֵ��ԭ�����ʲô���廹���ʲô���壬������C_DataError���������ݴ���
*******************************************************************************/
uchar8 InF_ModifyFunctionWord(uchar8 V_ucData)
{
	uchar8 V_ucreturn = C_OK;       /*����ֵ��Ϊ��ȷ*/
	switch ( V_ucData )
	{
		case C_SecondPulseOutput:
		{
			GV_ucMultiFunctionOutput = C_SecondPulseOutput;	/*ģʽ���л�*/
			DF_MultiFunction_SelectSecondPulse();			/*ѡ�������壺�������������*/
		}break;
        
		case C_DemandPulseOutput:
		{
			GV_ucMultiFunctionOutput = C_DemandPulseOutput;	/*ģʽ���л�*/
			DF_MultiFunction_SelectDemandPulse();			/*ѡ�������������壺�������������������*/
		}break;
        
		case C_RatePulseOutput:
		{
			GV_ucMultiFunctionOutput = C_RatePulseOutput;   /*ģʽ���л�*/
			DF_MultiFunction_SelectRatePulse();				/*ѡ��ʱ��Ͷ�����壺�������ʱ��Ͷ������*/
		}break;
        
		default:
		{
			V_ucreturn = C_DataError;
		}break;
	}
	return V_ucreturn;
}

/*******************************************************************************
����ԭ��: InF_MultiFunctionOutput
��������: �๦�����
�������: C_SecondPulse�����������
          C_DemandPulse�����������������
          C_RatePulse��  ʱ��Ͷ���������
�������: ��
���ز���: ��
����λ��: �������������ж�
��    ע: ������ģ�顢����ģ����øú���ʱ������Ҫ��������������壬ֻ�ܵ��ñ������Ϳ�����
          �ڱ������ڲ�����RAM�еĶ๦�����������ʽ����ȷ�������������
*******************************************************************************/
void InF_MultiFunctionOutput(uchar8 V_ucFunction)
{
	if ( (C_SecondPulseOutput == GV_ucMultiFunctionOutput) && (C_SecondPulse == V_ucFunction) )
	{
		DF_MultiFunction_SelectSecondPulse();
		SF_Set_MultiFunctionTimer(C_Interval_0ms);
	}
	
	if ( (C_DemandPulseOutput == GV_ucMultiFunctionOutput) && (C_DemandPulse == V_ucFunction) )
	{
		DF_MultiFunction_SelectDemandPulse();
		DF_MultiFunction_OutputDemandPulse();
		SF_Set_MultiFunctionTimer(C_TimerSwitch_8|C_Interval_80ms);
	}
	
	if ( (C_RatePulseOutput == GV_ucMultiFunctionOutput) && (C_RatePulse == V_ucFunction) )
	{
		DF_MultiFunction_SelectRatePulse();
		DF_MultiFunction_OutputDemandPulse();
		SF_Set_MultiFunctionTimer(C_TimerSwitch_8 | C_Interval_80ms);
	}
}

/*******************************************************************************
����ԭ��: uchar8 InF_ModifyFunctionStatus(void)	
��������: 698��ȡ��ǰ�๦�����״̬
�������: ��
�������: ��
���ز���: V_return���๦�����״̬
����λ��: 
��    ע: 
*******************************************************************************/
uchar8 InF_ModifyFunctionStatus(void)
{
	uchar8 V_ucreturn = C_SecondPulseOutput;			/*����ֵ��Ϊ������*/
	switch ( GV_ucMultiFunctionOutput )
	{
		case C_SecondPulseOutput:
		{
			V_ucreturn = C_SecondPulseOutput;			/*ģʽ���л�*/
		}break;
        
		case C_DemandPulseOutput:
		{
			V_ucreturn = C_DemandPulseOutput;			/*ģʽ���л�*/
		}break;
        
		case C_RatePulseOutput:
		{
			V_ucreturn = C_RatePulseOutput;				/*ģʽ���л�*/
		}break;
        
		default:
		{
			V_ucreturn = C_SecondPulseOutput;
		}break;
	}
	return V_ucreturn;
}





