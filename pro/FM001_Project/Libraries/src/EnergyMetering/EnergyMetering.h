/*******************************************************************************
Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     EnergyMetering.h
Version:       V1
Author:        
Date:          2014-3-12
Description:   ���ܴ����ļ�
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

#ifndef	__EnergyMetering_H
#define	__EnergyMetering_H

/*---------------------------------------------------------------------------*/
/*�궨��*/
/*---------------------------------------------------------------------------*/
#define C_ActiveDirection						0x00					/*����*/
#define C_ReactiveDirection						0x01					/*����*/

#define C_MoneyChangeEquivalent	    			10000					/*�������ݲ�洢����ʽת������*/
#define C_EnergyChangeEquivalent				1000000					/*���������ݲ�洢��������ʽת������*/
#define C_EnergyChangeEquivalent_Hundred		100						/*���������ݲ�洢��������ʽת������,100��*/

#define C_ValidStep								0x00					/*��Ч����*/
#define C_InValidStep							0x01					/*��Ч���ݣ�û�н��ݹ���*/

#define C_MaxStepNum							6						/*�����ݸ���*/
#define C_MaxStepEnergyLen						24						/*����ֵ��������*/
	   
#define CLCurr_Money							0x05					/*ʣ����\͸֧������ݲ㳤��*/
			
/*20�淶�����ܷ�Χ(6λС��)*/
#define C_ConEnergyToZero_Nature4				 0x7FFFFFFFFF			/*����4���ֵ��Χ*/
#define C_ConEnergyToZero_Nature2				 0x7FFFFFFF			    /*����2���ֵ��Χ*/


#define C_GetNextRatesEnergy					0x00000001				/*��ȡ��һ�����ʵ��ܱ�ʶ��*/
#define C_GetNextPhaseEnergy					0x00010000				/*��ȡ��һ��������ܱ�ʶ��*/
#define C_GetNextQuadrantEnergy					0x00100000		    	/*��ȡ��һ�����޵��ܱ�ʶ��*/

#define C_ActiveDeriction_T						0x08
#define C_ActiveDeriction_A						0x01
#define C_ActiveDeriction_B						0x02
#define C_ActiveDeriction_C						0x04
			
#define C_ReactiveDeriction_T					0x88
#define C_ReactiveDeriction_A					0x11
#define C_ReactiveDeriction_B					0x22
#define C_ReactiveDeriction_C					0x44
			
#define C_ReactiveEDeriction_T					( C_ReactiveDeriction_T & 0xF0 )
#define C_ReactiveEDeriction_A					( C_ReactiveDeriction_A & 0xF0 )
#define C_ReactiveEDeriction_B					( C_ReactiveDeriction_B & 0xF0 )
#define C_ReactiveEDeriction_C					( C_ReactiveDeriction_C & 0xF0 )

#define C_RenewDerict							0x68					/*ֱ�Ӹ���״̬��־*/
#define C_RenewRederict							0x86					/*��״̬�仯�Ÿ��±�־*/
							
#define C_NoMessage								0x00					/*������Ϣ*/
#define C_Warning1Message						0x01					/*������1��Ϣ��Ϣ*/
#define C_ReleaseWarning1Message				0x02					/*��ȡ������1��Ϣ��Ϣ*/
#define C_Warning2Message						0x03					/*������1��Ϣ��Ϣ*/
#define C_RelayOffMessage						0x04					/*��������բ��Ϣ��Ϣ*/
#define C_Warning3Message           			0x05    				/*ʣ������0����,��Ҫ�ȷ�һ����բ�����ٷ�һ������բ������Ϣ*/

#define	C_SubMoneyFlag							0x8A					/*�п۷ѱ�־*/
#define	C_NoSubMoneyFlag						0x00					/*�޿۷ѱ�־*/
							
#define C_MoneyToPurchase						0x68					/*����*/
#define C_NoMoneyToPurchase						0x00					/*û�й���*/
#define C_MoneyToPurchaseFlagLen				0x01					/*��־����*/

#if(_DEBUG_FY) /*ƴ�Ӻ�ȥ��*/
/*���ܶ�ȡ����*/						
#define C_Nature2BCD							0x01					/*����2BCD*/
#define C_Nature4BCD							0x02					/*����4BCD*/
#define C_Nature2HEX							0x03					/*����2HEX*/
#define C_Nature4HEX							0x04					/*����4HEX*/
#define C_Nature6HEX							0x05					/*����6HEX*/
#define C_ErrorMethod							0xFF					/*�쳣����*/
#endif	

/*���ܶ�ȡ����*/							
#define C_En_OADGetTpye_Money					0x01					/*�����*/
#define C_En_OADGetTpye_Month					0x02					/*�¶��õ���*/
#define C_En_OADGetTpye_StepSettle				0x03					/*���ݽ����õ���*/
#define C_En_OADGetTpye_Com						0x04					/*��ϵ���*/
#define C_En_OADGetTpye_Other					0x05					/*��������*/
			
/*���ݽ�����ƫ��*/			
#define C_FirstStepSettle_MonthOffset			0x00					/*��һ���ݽ��������µ�ƫ��*/
#define C_FirstStepSettle_DayOffset				0x01					/*��һ���ݽ��������յ�ƫ��*/

/*�������״̬��1��͸֧״̬*/
#define C_SetOverDraft							0x40					/*͸֧״̬��λ����1*/
#define C_ClrOverDraft							0xBF					/*͸֧״̬��λ����0*/

/*---------------------------------------------------------------------------*/
/*��������*/
/*---------------------------------------------------------------------------*/
void SF_Judge_CurrentStep(ulong32 V_ulEnergy_F, ulong32 *pV_ulEnergyPrice, uchar8 *pV_ucStepPara, uchar8 V_ucCurStepType);
void SF_JudgeWarningStatus(ulong64 V_ullRemainMoney, ulong64 V_ullRemainMoney_New, ulong64 V_ullOverDraftMoney, ulong64 V_ullOverDraftMoney_New, uchar8 V_ucRenewFlay);
void SF_ReworkWarningPara(void);
void SF_UpdateCurrentPrice(void);
void SF_WriteCurrentPrice(void);
void SF_SetMoneyToPurchaseFlag(uchar8 V_ucPurchaseFlag);


uchar8 SF_Judge_CurrentStep_Type(uchar8 *pV_ucBuffer);
uchar8 SF_RateChargeback(ulong64 V_ullEnergy_F, ulong64 V_ullEnergy, uchar8 V_ucRateNo);
uchar8 SF_Get_RMoney_DMoney(ulong64 *pV_ullRMoney, ulong64 *pV_ullDMoney);
uchar8 SF_CheckMoneyToPurchaseFlag(void);
uchar8 SF_ReadTotalEnergy(ulong32 V_ulPulOAD, ulong64 *pV_ullTolEnergy, uchar8 V_ucCalNum, ulong32 V_ulOADRegular );
uchar8 SF_DealEnergyPoint(uchar8 V_ucNature, ulong64 *pV_ullEnergyPulse, ushort16 *pV_usLen);
uchar8 SF_ReadConEnergy_Pulse(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen);


ulong64	SF_Get_V_I_Ratio(void);
ulong64 SF_Get_RateEnergyForChargeback(uchar8 V_ucRateNo);


#endif
