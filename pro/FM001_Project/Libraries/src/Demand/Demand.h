/*******************************************************************************
Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     Demand.h
Version:       V1
Author:        
Date:          2014-3-12
Description:   ���������ļ�
---------------------------------------------------------------------------------
History1:      ��1���޸�
����1. Date:   20219016
   	   Author: fy
       Modification:
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

#ifndef	__Demand_H
#define	__Demand_H


/*---------------------------------------------------------------------------*/
/*�ṹ�嶨��*/
/*---------------------------------------------------------------------------*/
typedef struct
{
	ulong32	*PowerAvarageAddr;			/*����������ŵ�ַ*/
	ulong32 AvaragePowerCode;			/*��Ҫ����1minƽ������ʾ��*/
}SStr_DemandPowerAddr_Type;

/*---------------------------------------------------------------------------*/
/*�궨��*/
/*---------------------------------------------------------------------------*/
#define C_1minAvaragePowerNum		60					/*��¼1minƽ�����ʸ���*/
			
#define C_NormalDemandInterval		15					/*Ĭ����������*/
#define	C_NormalSlipTime			1					/*Ĭ�ϻ���ʱ��*/
#define	C_NormalRate				1					/*Ĭ�Ϸ���*/
			
#define C_DerictionChange_AT		0x08				/*�����й����ʷ���ı�*/
#define C_DerictionChange_RT		0x09				/*�����޹����ʷ���ı�*/
#define	C_DerictionChange_AA		0x0A				/*A���й����ʷ���ı�*/
#define	C_DerictionChange_AB		0x0B				/*B���й����ʷ���ı�*/
#define	C_DerictionChange_AC		0x0C				/*C���й����ʷ���ı�*/
#define	C_DerictionChange_RA		0x0D				/*A���޹����ʷ���ı�*/
#define	C_DerictionChange_RB		0x0E				/*B���޹����ʷ���ı�*/
#define	C_DerictionChange_RC		0x0F				/*C���޹����ʷ���ı�*/
			
#define C_DerictActive_T			0x08				/*�й��ܷ����־��*/
#define C_DerictActive_A			0x01				/*�й�A�෽���־��*/
#define C_DerictActive_B			0x02				/*�й�B�෽���־��*/
#define C_DerictActive_C			0x04				/*�й�C�෽���־��*/
#define C_DerictReactive_T			0x80				/*�޹��ܷ����־��*/
#define C_DerictReactive_A			0x10				/*�޹�A�෽���־��*/
#define C_DerictReactive_B			0x20				/*�޹�B�෽���־��*/
#define C_DerictReactive_C			0x40				/*�޹�C�෽���־��*/
			
#define C_NormalCom1Mode			0x41				/*����޹�1Ĭ��ģʽ��*/
#define C_NormalCom2Mode			0x14				/*����޹�2Ĭ��ģʽ��*/
			
#define C_ReworkDemand				0x68		

#define CCurr_AcDemandLen			4						
#define CL_DemandAndTime			11					/*�������������ʱ�����ݲ㳤��*/
#define CL_Demand					4					/*�������������ʱ������������*/
						
#define C_T_ActiveCodeID			0x01				/*�����й���ʶ��*/
#define C_T_ReactiveCodeID			0x02				/*�����޹���ʶ��*/
#define C_A_ActiveCodeID 			0x03				/*A���й���ʶ��*/
#define C_A_ReactiveCodeID 			0x04				/*A���޹���ʶ��*/
#define C_B_ActiveCodeID 			0x05				/*B���й���ʶ��*/
#define C_B_ReactiveCodeID 			0x06				/*B���޹���ʶ��*/
#define C_C_ActiveCodeID 			0x07				/*C���й���ʶ��*/
#define C_C_ReactiveCodeID 			0x08				/*C���޹���ʶ��*/
				
#define C_GetNextRatesDemand		0x00000001			/*��ȡ��һ������������ʶ��*/
#define C_GetNextQuadrantDemand		0x00100000		    /*��ȡ��һ������������ʶ��*/

#define C_DeActiveDirection 		0x00				/*����*/
#define C_DeReactiveDirection		0x80				/*����*/

/*������ȡ����*/							
#define C_De_OADGetTpye_Com			0x01				/*���������*/
#define C_De_OADGetTpye_Other		0x02				/*����������*/

/*��ʼ�����й�\���޹�������ʱ����־*/
#define C_TDemandTimerInit_Flag		0x01				/*��ʼ�����й������޹�������ʱ��*/
#define C_TDemandTimerNoInit_Flag	0x00				/*����ʼ�����й������޹�������ʱ��*/

#define CL1minPerPower              4					/*1minƽ�����ʳ���*/

/*�������ڶ�ʱ����ABC���������е�λ��*/
#define C_APhasePosition            0					/*�������ڶ�ʱ����A��λ��*/
#define C_BPhasePosition            1					/*�������ڶ�ʱ����B��λ��*/
#define C_CPhasePosition            2					/*�������ڶ�ʱ����C��λ��*/

/*---------------------------------------------------------------------------*/
/*��������*/
/*---------------------------------------------------------------------------*/
void SF_InitDemandTimer(uchar8 V_ucFlay);
void SF_Clear_CurrentDemand(void);

#endif
