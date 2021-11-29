
///*****************************************************************************************///
///*Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     LoadProfile.c
///*Version:       V1
///*Date:          2014-3-12
///*Description:   ���ɼ�¼�����ļ�
///*Function List: 
///*****************************************************************************************///
///*History1:      ��1���޸�
///*����1. Date:
///*   	   Author:
///*       Modification:
		///***********************************************///
///*����2. Date:
///*   	   Author:
///*       Modification:
		///*********************************************************************************///
///*History2:      ��2���޸�
///*����1. Date:
///*   	   Author:
///*       Modification:
		///***********************************************///
///*����2. Date:
///*   	   Author:
///*       Modification:
///*****************************************************************************************///

#include "Public.h"
#include "LoadProfile.h"

 ///*���ฺ������ʱ����*///
const ulong32 C_TimeInteCode[6] = 
{
	CLoad_Rec1_Inte_Time,
	CLoad_Rec2_Inte_Time,
	CLoad_Rec3_Inte_Time,
	CLoad_Rec4_Inte_Time,
	CLoad_Rec5_Inte_Time,
	CLoad_Rec6_Inte_Time
};    

const Str_LoadDataType Str_LoadData[]=
{
	///*��ѹ��������Ƶ��*///
	CPhaseA_Volage, 		CLPhaseA_Volage,    	C_VariableType,
	CPhaseB_Volage, 		CLPhaseB_Volage,     	C_VariableType,
	CPhaseC_Volage,  		CLPhaseC_Volage,     	C_VariableType,           
	CPhaseA_Curr,    		CLPhaseA_Curr,       	C_VariableType,
	CPhaseB_Curr,    		CLPhaseB_Curr,       	C_VariableType,
	CPhaseC_Curr,    		CLPhaseC_Curr,       	C_VariableType,
	CElecNet_Freq,   		CLElecNet_Freq,      	C_VariableType,
	///*�С��޹�����*///
	CInstant_TolAcPow,      CLInstant_TolAcPow,     C_VariableType,
	CInstantA_AcPow,        CLInstantA_AcPow,       C_VariableType,
	CInstantB_AcPow,        CLInstantB_AcPow,       C_VariableType,
	CInstantC_AcPow,        CLInstantC_AcPow,       C_VariableType,
	CInstant_TolRePow,      CLInstant_TolRePow,     C_VariableType,
	CInstantA_RePow,        CLInstantA_RePow,       C_VariableType,
	CInstantB_RePow,        CLInstantB_RePow,       C_VariableType,
	CInstantC_RePow,        CLInstantC_RePow,       C_VariableType,
	///*��������*///
	CTol_PowerFactor,       CLTol_PowerFactor,      C_VariableType,
	CPhaseA_PowerFactor,    CLPhaseA_PowerFactor,   C_VariableType,
	CPhaseB_PowerFactor,    CLPhaseB_PowerFactor,   C_VariableType,
	CPhaseC_PowerFactor,    CLPhaseC_PowerFactor,   C_VariableType,
	///*�С��޹��ܵ���*///
	CPos_Ac_Tol_En_0,       CLPos_Ac_Tol_En_0,      C_EnergyType,
	CRev_Ac_Tol_En_0,       CLRev_Ac_Tol_En_0,      C_EnergyType,
	CCom_Re1_Tol_En_0,      CLCom_Re1_Tol_En_0,     C_EnergyType,
	CCom_Re2_Tol_En_0,      CLCom_Re2_Tol_En_0,     C_EnergyType,
	///*�������޹��ܵ���*///
	CQua1_Re_Tol_En_0,      CLQua1_Re_Tol_En_0,     C_EnergyType,
	CQua2_Re_Tol_En_0,      CLQua2_Re_Tol_En_0,     C_EnergyType,
	CQua3_Re_Tol_En_0,      CLQua3_Re_Tol_En_0,     C_EnergyType,
	CQua4_Re_Tol_En_0,      CLQua4_Re_Tol_En_0,     C_EnergyType,
	///*��ǰ����*///
	CCurr_AcDemand,			CLCurr_AcDemand,        C_DemandType,
	CCurr_ReDemand,			CLCurr_ReDemand,        C_DemandType
};
	
const uchar8 C_TypeNum[]={7,8,4,4,4,2};///*ÿһ�ฺ��������������������*///

///******************************************************************************************///
///*Function:void  Msg_LoadProfile(Str_Msg_Parameter V_Msg)				 					*///
///*Description:���ɼ�¼������															*///
///*Input:	�ж���Ϣ�����ṹ��V_Msg�еĲ�����C_SystemMinChange��ʾÿ���ӵ��ȴ���			*///
///*Output: ��									  									        *///
///*Return:	��	                                 											*///
///*Calls:																					*///
///*Called By:��ÿ���ӵ��ȴ���																*///
///*Influence:																				*///
///*Author:																					*///
///*Tips: 														                            *///
///*Others:																					*///
///******************************************************************************************///
void Msg_LoadProfile(Str_Msg_Parameter *V_Msg)
{
	uchar8 V_ucCurrentTime[CLDate_Time];///*��ǰʱ�仺��,YYMMDDhhmmss*///
	uchar8 V_ucLength_CurrentT = CLDate_Time;
	uchar8 V_ucLoadStartTime[CLLoad_Rec_Time_Year+1];///*������ʼʱ�仺��,�Ȳ�������*///
	uchar8 V_ucLength_LoadStartT = CLLoad_Rec_Time_Year;
	uchar8 V_ucLoadMode,V_ucModeTemp=0;///*����ģʽ��*///
	uchar8 V_ucLength_LoadMode = CLLoad_Rec_Mode;
	ulong32 V_ulSubMins;///*��ǰʱ���븺����ʼʱ��ķ��Ӳ�*///
	uchar8 V_ucTimeInte[2];///*ʱ��������*///
	uchar8 V_ucLength_TimeInte = CLLoad_Rec1_Inte_Time;
	uchar8 i,V_ucTemp=1;
	uchar8 V_ucDataTemp[104];///*�������ݻ�����,���Ϊ104�ֽ�*///
	uchar8 V_ucLen_LoadWrite;///*д���ݲ㳤��*///
	uchar8 V_ucWrSafeFlag=C_W_SafeFlag_1;
	
	if(SF_LoadProfile_ParseMessage(V_Msg) == C_Error)///*��Ϣ��������,ֱ�ӷ���*///
	{
		return;
	}
	if(InF_Read_Data(CDate_Time,V_ucCurrentTime,&V_ucLength_CurrentT) != C_OK)///*����ǰʱ��,��ʧ�����˳�*///
	{
		return;
	}
	if(PF_DataTimeActive(V_ucCurrentTime,C_DT_Start_ss,CLDate_Time) != C_OK)
	{///*��ǰʱ�䲻�Ϸ���Ҳ�������ɼ�¼*///
		return;
	}
	V_ucLoadStartTime[C_Sec] = 0;///*������ʼʱ���븳ֵ0*///
//	if(InF_Read_Data(CLoad_Rec_Time_Year,&V_ucLoadStartTime[C_Minute],&V_ucLength_LoadStartT) != C_OK)
//	{
//		return;
//	}
	if((InF_Read_Data(CLoad_Rec_Time_Year,&V_ucLoadStartTime[C_Minute],&V_ucLength_LoadStartT) != C_OK)///*��������ʼʱ�䣬��ʧ��*///
		||(PF_DataTimeActive(&V_ucLoadStartTime[C_Minute],C_DT_Start_mm,CLLoad_Rec_Time_Year) != C_OK))///*��ʱ�䲻�Ϸ�,Ĭ��Ϊ2000��1��1��*///
	{///*ʱ�䲻�Ϸ�,Ĭ��Ϊ2000��1��1��*///
		V_ucLoadStartTime[C_Minute] = 0x00;
		V_ucLoadStartTime[C_Hour] = 0x00;
		V_ucLoadStartTime[C_Day] = 0x01;
		V_ucLoadStartTime[C_Month] = 0x01;
		V_ucLoadStartTime[C_Year] = 0x00;
	}
	if(PF_Campare_Data(&V_ucCurrentTime[C_Minute],&V_ucLoadStartTime[C_Minute],CLLoad_Rec_Time_Year) == C_LessThan)
	{///*��ǰʱ�䲻�ȸ�����ʼʱ���,ֱ���˳�*///����ݹ㶫���Ժ���Խ�����޸ĵ�ʱ�����ʱ��Ҳ��¼���ݡ�
		return;
	}
	if(InF_Read_Data(CLoad_Rec_Mode,&V_ucLoadMode,&V_ucLength_LoadMode) != C_OK)
	{///*����ģʽ�ֶ�ȡʧ��,Ĭ��Ϊ3F*///
		V_ucLoadMode = 0x3F;
	}
	V_ucWrSafeFlag |= C_W_SafeFlag_2;
	
	PF_TimeSub_Min(&V_ucLoadStartTime[C_Sec],&V_ucCurrentTime[C_Sec],&V_ulSubMins);///*���㵱ǰʱ���븺����ʼʱ��ķ��Ӳ�*///
	
	for (i=0;i<6;i++)
	{
		if(InF_Read_Data(C_TimeInteCode[i],V_ucTimeInte,&V_ucLength_TimeInte) != C_OK)
		{
			V_ucTimeInte[0] = 0x15;///*��ȡʧ��,Ĭ��Ϊ15����*///
		}
		V_ucTimeInte[0] = ((V_ucTimeInte[0]>>4)*10) + (V_ucTimeInte[0]&0x0F);
		
		if((V_ucTimeInte[0] != 0)&&((V_ulSubMins%V_ucTimeInte[0]) == 0))///*ʱ������,������ʱģʽ��Ϊ1*///
		{
			V_ucModeTemp |= (V_ucTemp << i);
		}
	}
	V_ucLoadMode &= V_ucModeTemp;
	
	if(V_ucLoadMode != 0)
	{
		V_ucLen_LoadWrite = SF_GetData_LoadProfile(V_ucLoadMode,&V_ucCurrentTime[C_Minute],V_ucDataTemp);///*ȡ��������*///
		
		V_ucWrSafeFlag |= C_W_SafeFlag_3;
		///*06FE0000���ɼ�¼����*///
		uchar8 V_NumLen=3,i;
		uchar8 V_ucNum[3];
		ulong32 V_ulLoadWriteNum;
		
		if(InF_Read_Data(CLoadWriteNum,V_ucNum,&V_NumLen)!=C_OK)
		{
			 for(i=0;i<3;i++)
			   {
			   	  V_ucNum[i]=0;
			   }	
		}
		PF_Buffer4ToUlong32(V_ucNum,&V_ulLoadWriteNum,V_NumLen);
		V_ulLoadWriteNum++;
		PF_Ulong32ToBuffer4(V_ucNum,&V_ulLoadWriteNum,V_NumLen);
		InF_Write_Data(C_Msg_LoadProfile,CLoadWriteNum,V_ucNum,CLLoadWriteNum,V_ucWrSafeFlag);///*д���ݲ�*///

		InF_Write_Data(C_Msg_LoadProfile,CLoad_Write,V_ucDataTemp,V_ucLen_LoadWrite,V_ucWrSafeFlag);///*д���ݲ�*///
	}
	
}

///******************************************************************************************///
///*Function:uchar8 SF_LoadProfile_ParseMessage(Str_Msg_Parameter * P_Msg_Parameter)			*///
///*Description:����ģ����Ϣ�������														*///
///*Input:	P_Msg_Parameter �C��Ϣ�ṹ��														*///
///*Output: 													 					        *///
///*Return:	C_OK-��Ϣ������ȷ,����з����ж�/C_Error-��Ϣ��������,���账��					*///
///*Calls:																					*///
///*Called By:																				*///
///*Influence:																				*///
///*Author:																					*///
///*Tips: 
///* ���2�� SourceAddr= ���ȡ�����ÿ���Ӵ���
///*                            DerictAddr = C_Msg_Deal_MultiRates
///*                            Len = 2
///*                            ������Pt_Dispatch_Timing��ȡֵC_SystemMinChange
///******************************************************************************************///
uchar8 SF_LoadProfile_ParseMessage(Str_Msg_Parameter *P_Msg_Parameter)
{
	uchar8 *pParm;
	 
	if(P_Msg_Parameter->PowerFlag != C_PowerOn)///*����ʱֱ�ӷ��ش���,���账��*///
	{
		return C_Error;
	}
	///*�����������,����������÷����������*///
	pParm = P_Msg_Parameter->Parameter;
	
	if(*pParm == Pt_Dispatch_Timing)
	{
		if(P_Msg_Parameter->Length ==(Pt_Dispatch_Timing_Len+1))
		{
			return C_OK;
		}
	}
	return C_Error;
}

///******************************************************************************************///
///*Function:uchar8 SF_GetData_LoadProfile (uchar8 V_ucMode,uchar8 *p_ucDateTime,uchar8 *P_buffer)*///
///*Description:ȡ���ɼ�¼����																*///
///*Input:	V_ucMode ģʽ�֣�Ϊ���ɼ�¼ģʽ�֣�0x04000901������ʱģʽ�������ֵ������ָʾ	*///
///*				��ǰʵ����Ҫȡ�ĸ������ݣ�ͬʱ�������ݲ㣬�����ж����ݳ��ȺϷ���		*///
///*		p_ucDate��ǰʱ�䣬5�ֽڣ�������ʱ��												*///
///*		P_buffer���������																*///
///*Output: ��									  									        *///
///*Return:	��	                                 											*///
///*Calls:																					*///
///*Called By:Msg_LoadProfile																*///
///*Influence:																				*///
///*Author:																					*///
///*Tips:����ģʽ�֣���ȡ�������ɸ��ɼ�¼���ݿ飬���������ݲ�д���ɽӿں����������ݴ������ݲ�*///
///*Others:																					*///
///******************************************************************************************///
uchar8 SF_GetData_LoadProfile(uchar8 V_ucMode,uchar8 *p_ucDateTime,uchar8 *P_buffer)
{
	uchar8 i,j,V_ucAddTemp=0,V_ucTemp=1;
	uchar8 V_ucLength_Load;
	uchar8 *P_ucData;///*���ݻ���ָ����ʱ����*///
	uchar8 V_ucLen=0;///*���ɼ�¼����*///
	
	P_buffer[C_Mode] = V_ucMode;///*��ֵģʽ��*///
	
	P_buffer[C_A0] = 0xA0;///*��ֵ�����ֽ�A0*///
	P_buffer[C_A0+1] = 0xA0;
	
	PF_CopyDataBytes(p_ucDateTime,&P_buffer[C_Time],C_LoadTimeLen);///*��ʱ�丳ֵ��ʱ����*///
	V_ucLen += C_LoadTimeLen;///*�ۼƸ��ɼ�¼����*///
	
	P_ucData = &P_buffer[C_Data];///*��ֵ��ʱ����ָ��*///
	
	for(i=0;i<6;i++)
	{		
		if(V_ucMode & (V_ucTemp<<i))
		{
			for(j=0;j<C_TypeNum[i];j++)
			{
				V_ucLength_Load = Str_LoadData[V_ucAddTemp].V_ucLength;					
				///*���ݲ�ͬ��������,���ò�ͬ��������ȡ����*///
				if(Str_LoadData[V_ucAddTemp].V_ucDataType == C_EnergyType)///*��������*///
				{
					InF_ReadEnergy_Protocol(Str_LoadData[V_ucAddTemp].V_ulDI,P_ucData,V_ucLength_Load);
				}
				else///*˲ʱ������*///
				{
					InF_Read_Data(Str_LoadData[V_ucAddTemp].V_ulDI,P_ucData,&V_ucLength_Load);
				}
				P_ucData += V_ucLength_Load;///*�ۼ�����ָ��*///
				V_ucLen += V_ucLength_Load;///*�ۼƸ��ɼ�¼����*///
				
				V_ucAddTemp ++;///*���ڶ�λ�������*///
			}
		}
		else
		{
			V_ucAddTemp += C_TypeNum[i];///*���ڶ�λ�������*///
		}
		*P_ucData = 0xAA;///*��ֵAA���ۼ�ָ��*///
		P_ucData ++;
		V_ucLen ++;	
	}
	P_buffer[C_Length] = V_ucLen;///*��ֵ���ɼ�¼����*///
	
	*P_ucData = SF_CalCS(&P_buffer[C_A0],V_ucLen+3);///*����CS*///
	
	*(P_ucData+1) = 0xE5;
	
	V_ucLen += 6;///*�����ݳ���=1+2+1+L+2(ģʽ��+A0A0+����+L+CS+E5) *///
	return V_ucLen;
}

///******************************************************************************************///
///*Function:uchar8 SF_CalCS(uchar8 *P_buffer,uchar8 V_ucLen)								*///
///*Description:����CS																		*///
///*Input:	*P_buffer �����CS���ݵ��׵�ַ  V_ucLen �����CS���ݵĳ���						*///
///*Output: ��									  									        *///
///*Return:	V_ucCS CS��ֵ                          											*///
///*Calls:																					*///
///*Called By:SF_GetData_LoadProfile														*///
///*Influence:																				*///
///*Author:																					*///
///*Tips:																					*///
///*Others:																					*///
///******************************************************************************************///
uchar8 SF_CalCS(uchar8 *P_buffer,uchar8 V_ucLen)
{
	uchar8 i;
	uchar8 V_ucCS = 0;
	for( i=0;i<V_ucLen;i++)
	{
		V_ucCS += *(P_buffer+i);
	}
	return V_ucCS;
}


const Str_LoadReadStatus Str_LoadStatus[]=
{
	///*��ѹ��*///
	CVoltageA_Load,			CGivenTimeRec1_Load,	 8,		CLVoltageA_Load,
	CVoltageB_Load,			CGivenTimeRec1_Load,     10,    CLVoltageB_Load,			
	CVoltageC_Load,			CGivenTimeRec1_Load,     12,    CLVoltageC_Load,			
	CVoltageBlock_Load,		CGivenTimeRec1_Load,     8,     CLVoltageBlock_Load,		
	///*������*///
	CCurrentA_Load,			CGivenTimeRec1_Load,     14,    CLCurrentA_Load,			
	CCurrentB_Load,			CGivenTimeRec1_Load,     17,    CLCurrentB_Load,			
	CCurrentC_Load,			CGivenTimeRec1_Load,     20,    CLCurrentC_Load,			
	CCurrentBlock_Load,		CGivenTimeRec1_Load,     14,    CLCurrentBlock_Load,		
	///*�й�������*///
	CActPowerT_Load,		CGivenTimeRec2_Load,     9,     CLActPowerT_Load,		
	CActPowerA_Load,		CGivenTimeRec2_Load,     12,    CLActPowerA_Load,		
	CActPowerB_Load,		CGivenTimeRec2_Load,     15,    CLActPowerB_Load,		
	CActPowerC_Load,		CGivenTimeRec2_Load,     18,    CLActPowerC_Load,		
	CActPowerBlock_Load,	CGivenTimeRec2_Load,     9,     CLActPowerBlock_Load,	
	///*�޹�������*///
	CReActPowerT_Load,		CGivenTimeRec2_Load,     21,    CLReActPowerT_Load,		
	CReActPowerA_Load,		CGivenTimeRec2_Load,     24,    CLReActPowerA_Load,		
	CReActPowerB_Load,		CGivenTimeRec2_Load,     27,    CLReActPowerB_Load,		
	CReActPowerC_Load,		CGivenTimeRec2_Load,     30,    CLReActPowerC_Load,		
	CReActPowerBlock_Load,	CGivenTimeRec2_Load,     21,    CLReActPowerBlock_Load,	
	///*����������*///
	CPowFactorT_Load,		CGivenTimeRec3_Load,     10,    CLPowFactorT_Load,		
	CPowFactorA_Load,		CGivenTimeRec3_Load,     12,    CLPowFactorA_Load,		
	CPowFactorB_Load,		CGivenTimeRec3_Load,     14,    CLPowFactorB_Load,		
	CPowFactorC_Load,		CGivenTimeRec3_Load,     16,    CLPowFactorC_Load,		
	CPowFactorBlock_Load,	CGivenTimeRec3_Load,     10,    CLPowFactorBlock_Load,	
	///*���޹��ܵ�����*///
	CPosActEnergyT_Load,	CGivenTimeRec4_Load,     11,    CLPosActEnergyT_Load,	
	CRevActEnergyT_Load,	CGivenTimeRec4_Load,     15,    CLRevActEnergyT_Load,	
	CComReAct1T_Load,		CGivenTimeRec4_Load,     19,    CLComReAct1T_Load,		
	CComReAct2T_Load,		CGivenTimeRec4_Load,     23,    CLComReAct2T_Load,		
	CTotEnergyBlock_Load,	CGivenTimeRec4_Load,     11,    CLTotEnergyBlock_Load,	
	///*�������޹�������*///
	CReActQuad1_Load,		CGivenTimeRec5_Load,     12,    CLReActQuad1_Load,		
	CReActQuad2_Load,		CGivenTimeRec5_Load,     16,    CLReActQuad2_Load,		
	CReActQuad3_Load,		CGivenTimeRec5_Load,     20,    CLReActQuad3_Load,		
	CReActQuad4_Load,		CGivenTimeRec5_Load,     24,    CLReActQuad4_Load,		
	CReActQuadTBlock_Load,	CGivenTimeRec5_Load,     12,    CLReActQuadTBlock_Load,	
	///*��ǰ������*///
	CActDemand_Load,		CGivenTimeRec6_Load,     13,    CLActDemand_Load,		
	CReActDemand_Load,		CGivenTimeRec6_Load,     16,    CLReActDemand_Load,		
	CDemandBlock_Load,		CGivenTimeRec6_Load,     13,    CLDemandBlock_Load		
};

///*�����ж��·�����*///
const uchar8 C_MonthNum[12]={31,28,31,30,31,30,31,31,30,31,30,31};


///******************************************************************************************///
///*Function:uchar8 InF_SeqRead_LoadProfile							 						*///
///*Description:�˺���Ϊͨ��ģ����и��ɼ�¼��������ʱ���ã����������ݴ����ݲ��ȡ����֯�󣬴���ͨ��ģ��*///
///*Input:	V_ulDataId-���ݱ�ʶ
///*		* P_ucTime-��ȡ���ɼ�¼����ʼʱ�䣬5�ֽڣ�mmhhDDMMYY��
///*		* P_ucBlockNum-���賭������
///*		* P_ucData-���ݻ�����
///*		*P_ucGVBuffer-��ŵ���ȫ�ֱ����Ļ����׵�ַ��������ʱʹ��,����ʱ���ڲ�����.�����ǵ�������ʱ���ô�������
///*		*P_ucLength�����ݻ���������
///*		P_ucFollowFlag��ʾ�Ƿ�Ϊ���ɶ�ȡ�ĵ�һ֡,��Ϊ��һ֡,�轫��ʶ��͹�һʱ��������ݻ�����,C_FirstFrame/C_FollowFrame
///*Output: * P_ucTime-��Ϊ�������ʱ�����غ���֡���ȡ�ĸ��ɼ�¼ʱ��
///*		* P_ucBlockNum-��Ϊ�������ʱ������ֵΪ��������ʣ����������ں���֡����,Ϊ0��ʾ�޺���֡,hex��ʽ��
///*		* P_ucData-��������
///*		*P_ucGVBuffer-�������,�ڶ����ܸ��ɼ�¼ʱ��������ʵ�ʼ�¼���ݣ������ܷ���˴�
///*		*P_ucLength����������ݳ���
///*Return:	C_OK-�����ɹ�,C_NoData-������,C_Error-��ȡ����	                 				*///
///*Calls:																					*///
///*Called By:ͨ���յ�������������ʱ����,����֡Ҳ���øú���									*///
///*Influence:																				*///
///*Author:																					*///
///*Tips:����*P_ucBlockNum��ֵ���ж��Ƿ��к���֡				                            *///
///*Others:																					*///
///******************************************************************************************///
uchar8 InF_SeqRead_LoadProfile(ulong32 V_ulDataId,uchar8 *P_ucTime,uchar8 *P_ucData,uchar8 *P_ucGVBuffer,uchar8 *P_ucBlockNum,uchar8 *P_ucLength,uchar8 P_ucFollowFlag)
{
	uchar8 V_ucStartTime[CLLoad_Rec_Time_Year+1],V_ucCurrentTime[CLDate_Time];///*���縺�ɼ�¼ʱ��͵�ǰʱ��*///
	uchar8 V_ucFirstTime[C_LoadTLength+1],V_ucEndTime[C_LoadTLength+1];///*����������һ��ͽ�ֹ��ʱ��*///
	ulong32 V_ulLoadTypeID,V_ulSubMins;
	uchar8 V_ucDataLength,V_ucReturnTemp,V_ucFlag=0;
	uchar8 V_ucReadNum,V_ucIntTime,V_ucLength,i;
	uchar8 V_ucParaTime[CLLoad_Rec_Time_Year+1];
	uchar8 V_ucTableLen = sizeof(Str_LoadStatus)/sizeof(Str_LoadReadStatus);
	
	if(PF_DataTimeActive(P_ucTime,C_DT_Start_mm,CLLoad_Rec_Time_Year) != C_OK)///*��ȡʱ�䲻�Ϸ�,����������*///
	{
		return C_NoData;
	}
	V_ucFirstTime[C_Sec]=0;///*��λ��0,ʱ�����ʱʹ��*///
	V_ucEndTime[C_Sec]=0;
	
	for(i=0;i<V_ucTableLen;i++)
	{
		if(V_ulDataId == Str_LoadStatus[i].V_ulDataId)
		{
			V_ulLoadTypeID = Str_LoadStatus[i].V_ulTypeId;///*��ֵ���ͱ�ʶ��*///
		
			V_ucDataLength = Str_LoadStatus[i].V_ucDataLen;///*��ֵ���ݳ���*///
			
			break;
		}
	}
	if(i>=V_ucTableLen)
	{
		return C_Error;
	}
	V_ucIntTime = SF_GetIntTime_LoadProfile(V_ulLoadTypeID);///*��ü��ʱ��*///
	
	if(V_ucIntTime == 0)///*���ʱ��Ϊ0,�򷵻�������*///
	{
		return C_NoData;
	}
	if(P_ucFollowFlag == C_FirstFrame)///*��һ֡ȡ��һʱ��*///
	{
		V_ucStartTime[C_Sec] = 0;///*��λ����*///
		V_ucParaTime[C_Sec] = 0;
		if(SF_StartTime_LoadProfile(V_ulLoadTypeID,&V_ucStartTime[C_Minute],&V_ucParaTime[C_Minute],V_ucIntTime) != C_OK)///*ȡ���縺�ɼ�¼ʱ��*///
		{
			return C_NoData;
		}
		V_ucLength = CLDate_Time;
		InF_Read_Data(CDate_Time,V_ucCurrentTime,&V_ucLength);///*��ȡ��ǰʱ��*///
		
		V_ucFlag = SF_FirstTime_LoadProfile(V_ulLoadTypeID,&V_ucIntTime,P_ucTime,&V_ucStartTime[C_Sec],&V_ucParaTime[C_Sec],&V_ucFirstTime[C_Minute]);///*��ȡ��һʱ��*///

		SF_MinsAdd_LoadProfile(P_ucTime,(*P_ucBlockNum)*V_ucIntTime-1,&V_ucEndTime[C_Minute]);///*�������ֹʱ��*///

		if(PF_Campare_Data(&V_ucEndTime[C_Minute],&V_ucCurrentTime[C_Minute],C_LoadTimeLen) == C_GreaterThan)
		{
			PF_CopyDataBytes(&V_ucCurrentTime[C_Minute],&V_ucEndTime[C_Minute],C_LoadTimeLen);
			
			V_ucFlag = C_ReCal;
		}
		V_ucReturnTemp = PF_Campare_Data(&V_ucFirstTime[C_Minute],&V_ucEndTime[C_Minute],C_LoadTimeLen);
		
		if(V_ucReturnTemp == C_GreaterThan)
		{///*��һ������ʱ����ڽ�ֹʱ�䣬����������*///
			return C_NoData;
		}
		else if(V_ucReturnTemp == C_Equal)
		{
			*P_ucBlockNum = 1;
		}
		else if(V_ucFlag == C_ReCal)
		{
			PF_TimeSub_Min(V_ucEndTime,V_ucFirstTime,&V_ulSubMins);///*�����һʱ��ͽ�ֹʱ���ʱ���*///

			*P_ucBlockNum = V_ulSubMins/V_ucIntTime + 1;///*�����һʱ�������ܳ�������*///

		}
		V_ucReadNum =(*P_ucLength - CLLoad_Rec_Time_Year)/V_ucDataLength;///*��ֵ��֡��ȡ����*///
		
		if(*P_ucBlockNum > V_ucReadNum)
		{
			(*P_ucBlockNum) -= V_ucReadNum;///*�������֡���ȡ�Ŀ���*///
			
			SF_MinsAdd_LoadProfile(&V_ucFirstTime[C_Minute],V_ucReadNum*V_ucIntTime,P_ucTime);///*�������֡������ʼʱ��*///
		}
		else
		{
			V_ucReadNum = *P_ucBlockNum;
			
			*P_ucBlockNum = 0;///*�޺���֡*///
		}
		*P_ucLength = V_ucReadNum*V_ucDataLength + CLLoad_Rec_Time_Year;///*�����֡�����ݳ���*///
	}
	else///*����֡��ʼʱ�伴Ϊ��һ������ʱ��*///
	{
		PF_CopyDataBytes(P_ucTime,&V_ucFirstTime[C_Minute],C_LoadTLength);
		
		V_ucReadNum =(*P_ucLength)/V_ucDataLength;///*��ֵ��֡��ȡ����*///
		
		if(*P_ucBlockNum > V_ucReadNum)
		{
			(*P_ucBlockNum) -= V_ucReadNum;///*�������֡���ȡ�Ŀ���*///
			
			SF_MinsAdd_LoadProfile(&V_ucFirstTime[C_Minute],V_ucReadNum*V_ucIntTime,P_ucTime);///*�������֡������ʼʱ��*///
		}
		else
		{
			V_ucReadNum = *P_ucBlockNum;
			
			*P_ucBlockNum = 0;///*�޺���֡*///
		}
		*P_ucLength = V_ucReadNum*V_ucDataLength;///*�����֡�����ݳ���*///
	}
	if(SF_GetSeqData_LoadProfile(&V_ulDataId,&V_ucFirstTime[C_Minute],&V_ucReadNum,&V_ucIntTime,P_ucFollowFlag,P_ucGVBuffer,P_ucData)!=C_OK)///*��ȡ��������*///
	{
		return C_Error;///*���ض�ȡ����*///
	}
	return C_OK;
}

///******************************************************************************************///
///*Function:uchar8 SF_GetIntTime_LoadProfile												*///
///*Description:���ݱ�ʶ������ʱ��														*///
///*Input:	V_ulLoadID ĳ�ฺ�ɶ�Ӧ�Ķ�ȡ��ʶ��												*///
///*Output: ��									  									        *///
///*Return:	���ʱ��	                          											*///
///*Calls:																					*///
///*Called By:SF_SepRead_LoadProfile														*///
///*Influence:																				*///
///*Author:																					*///
///*Tips:																					*///
///*Others:																					*///
///******************************************************************************************///
uchar8 SF_GetIntTime_LoadProfile(ulong32 V_ulLoadID)
{
	uchar8 V_ucIntTime[2];///*���ʱ��*///
	ulong32 V_ulAddress;
	uchar8 V_ucLength=CLLoad_Rec1_Inte_Time;
	
	switch(V_ulLoadID)
	{
		case CGivenTimeRec1_Load:
			V_ulAddress = CLoad_Rec1_Inte_Time;
			break;
		case CGivenTimeRec2_Load:
			V_ulAddress = CLoad_Rec2_Inte_Time;
			break;
		case CGivenTimeRec3_Load:
			V_ulAddress = CLoad_Rec3_Inte_Time;
			break;
		case CGivenTimeRec4_Load:
			V_ulAddress = CLoad_Rec4_Inte_Time;
			break;
		case CGivenTimeRec5_Load:
			V_ulAddress = CLoad_Rec5_Inte_Time;
			break;
		case CGivenTimeRec6_Load:
			V_ulAddress = CLoad_Rec6_Inte_Time;
			break;
		default:
			return 0;
	}
	InF_Read_Data(V_ulAddress,V_ucIntTime,&V_ucLength);///*�����ʱ��*///
	
	if(V_ucIntTime[0] > 0x60)///*���ݲ��Ϸ�,Ĭ��Ϊ0*///
	{
		return 0;
	}
	V_ucIntTime[0] = ((V_ucIntTime[0] >> 4) * 10) + (V_ucIntTime[0] & 0x0f);///*תHEX*///
	
	return V_ucIntTime[0];
}

///******************************************************************************************///
///*Function:uchar8 SF_StartTime_LoadProfile												*///
///*Description:ȡ����һ�θ��ɼ�¼ʱ��͸�����ʼʱ��Ľ���ʱ���							*///
///*Input:	V_ulDataId-���ݱ�ʶ
///*		V_ucIntTime-���ʱ��
///*Output: * P_ucStartTime �C������縺�ɼ�¼ʱ��									        *///
///*		*P_ucLoadParaTime-���ɼ�¼��ʼʱ��
///*Return:C_OK,C_NoData							                      					*///
///*Calls:																					*///
///*Called By:																				*///
///*Influence:																				*///
///*Author:																					*///
///*Tips:																					*///
///*Others:																					*///
///******************************************************************************************///
uchar8 SF_StartTime_LoadProfile(ulong32 V_ulDataId,uchar8 *P_ucStartTime,uchar8 *P_ucLoadParaTime,uchar8 V_ucIntTime)
{
	uchar8 V_ucStartTime[CLLoad_Rec_Time_Year],i;
	uchar8 V_ucDataTemp[C_LoadMaxLen],V_ucNum_RdLoad = 1,V_ucLength;
	uchar8 v_i=0;
	
	
	V_ucLength = C_LoadMaxLen;///*��ȡ���縺�ɼ�¼*///
	for(i=0;i<CLLoad_Rec_Time_Year;i++)
	{
		V_ucStartTime[i] = 0;
	}
	if(InF_ReadLoadData(V_ulDataId-1,V_ucStartTime,V_ucDataTemp,&V_ucNum_RdLoad,&V_ucLength,C_Msg_LoadReadEarlyData) != C_OK)
	{
		return C_NoData;
	}
	V_ucLength = CLLoad_Rec_Time_Year;
	InF_Read_Data(CLoad_Rec_Time_Year,P_ucLoadParaTime,&V_ucLength);///*��������ʼʱ��*///

	if(PF_DataTimeActive(P_ucLoadParaTime,C_DT_Start_mm,CLLoad_Rec_Time_Year) != C_OK)
	{///*ʱ�䲻�Ϸ�,Ĭ��Ϊ2000��1��1��*///
		P_ucLoadParaTime[C_Minute_L] = 0x00;
		P_ucLoadParaTime[C_Hour_L] = 0x00;
		P_ucLoadParaTime[C_Day_L] = 0x01;
		P_ucLoadParaTime[C_Month_L] = 0x01;
		P_ucLoadParaTime[C_Year_L] = 0x00;
	}
//	SF_MinsAdd_LoadProfile(P_ucLoadParaTime,V_ucIntTime,V_ucStartTime);///*ʵ�ʵ�һ����Ӹ�����ʼʱ���һ�����ʱ�俪ʼ��*///
	SF_MinsAdd_LoadProfile(P_ucLoadParaTime,v_i,V_ucStartTime);///*���ݹ㶫�����޸ģ���¼��ʼ��������*///
	
	if(PF_Campare_Data(&V_ucDataTemp[C_TimeOffset],V_ucStartTime,C_LoadTimeLen) == C_GreaterThan)
	{///*ȡ���ɼ�¼��ʼʱ���������ɼ�¼ʱ��Ľϴ�ֵ����Ϊ����ʵ�ʵ�һ����¼ʱ��*///
		PF_CopyDataBytes(&V_ucDataTemp[C_TimeOffset],P_ucStartTime,C_LoadTimeLen);
	}
	else
	{
		PF_CopyDataBytes(V_ucStartTime,P_ucStartTime,C_LoadTimeLen);
	}
	return C_OK;
}		

///******************************************************************************************///
///*Function:uchar8 SF_FirstTime_LoadProfile												*///
///*Description:������ʼʱ������ݲ��ʵ�ʸ��ɼ�¼��,ȡ����һʱ��							*///
///*Input:	V_ulDataId-���ݱ�ʶ
///*		*P_ucInteTime-���ʱ��
///*		* P_ucReadStartTime -��ȡ���ɼ�¼����ʼʱ�䣬5�ֽڣ�YYMMDDhhmm��
///*		*P_ucStartTime-���縺�ɼ�¼�¼�,6�ֽ�
///*		*P_ucParaTime-������ʼʱ��
///*		* P_SendTime �C�������,����ʱ���׵�ַ,5�ֽ�
///*Output: * P_SendTime �Cʵ�ʷ��������е�һ�����ɼ�¼�ļ�¼ʱ��					        *///
///*Return:	V_ucflag,Ϊ0��ʾ�������¼��������C_ReCal��ʾ�����¼���        					*///
///*Calls:																					*///
///*Called By:SF_SepRead_LoadProfile														*///
///*Influence:																				*///
///*Author:																					*///
///*Tips:																					*///
///*Others:																					*///
///******************************************************************************************///
uchar8 SF_FirstTime_LoadProfile(ulong32 V_ulDataId,uchar8 *P_ucInteTime,uchar8 *P_ucReadStartTime,uchar8 *P_ucStartTime,uchar8 *P_ucParaTime,uchar8 *P_ucSendTime)
{
	uchar8 V_ucTimeBuff[CLLoad_Rec_Time_Year+1];///*��һʱ���м��������*///
	uchar8 V_ucflag=0,V_ucIntTime=*P_ucInteTime;///*���ʱ��*///
	ulong32 V_ulSubMins;

	V_ucTimeBuff[C_Sec] = 0;///*������ʱ����Ϊ6�ֽ�*///
	PF_CopyDataBytes(P_ucReadStartTime,&V_ucTimeBuff[C_Minute],CLLoad_Rec_Time_Year);
	
	if(PF_Campare_Data(&V_ucTimeBuff[C_Minute],&P_ucStartTime[C_Minute],C_LoadTimeLen) == C_LessThan)///*����ʱ������縺�ɼ�¼ʱ��*///
	{
		PF_CopyDataBytes(&P_ucStartTime[C_Minute],&V_ucTimeBuff[C_Minute],CLLoad_Rec_Time_Year);
		
		V_ucflag = C_ReCal;
	}
	PF_TimeSub_Min(V_ucTimeBuff,P_ucParaTime,&V_ulSubMins);///*ȡ����ʱ���븺����ʼʱ���ֵ*///
	
	if(((V_ulSubMins%V_ucIntTime) != 0)&&(V_ucIntTime != 0))///*��ֵ�����������ʱ��,������ȡ���һ��������*///
	{
		V_ulSubMins = V_ucIntTime - (V_ulSubMins%V_ucIntTime);
		
		SF_MinsAdd_LoadProfile(&V_ucTimeBuff[C_Minute],V_ulSubMins,&V_ucTimeBuff[C_Minute]);
		
		V_ucflag = C_ReCal;
	}
	PF_CopyDataBytes(&V_ucTimeBuff[C_Minute],P_ucSendTime,CLLoad_Rec_Time_Year);
	
	return V_ucflag;
}

///******************************************************************************************///
///*Function:void SF_MinsAdd_LoadProfile													*///
///*Description:�ڸ�ʽYYMMDDhhmm��ʱ�����ۼӷ�����											*///
///*Input:	*P_ucSourceTime-���ۼӵ�ԭʼʱ��,��ʼʱ��Ϊ��,5�ֽڳ���
///*		V_ulAddMins-�ۼӵķ�����,����ֵ���Ϊ4��,16����
///*Output: *P_ucResultTime �C����ۼӺ��ʱ��										        *///
///*Return:��                         											*///
///*Calls:																					*///
///*Called By:																				*///
///*Influence:																				*///
///*Author:																					*///
///*Tips:1.���ڴ�����������Ϊ1�ֽڳ���,������Ĭ��Ϊ20XX��;
///*	2.*P_ucSourceTime��*P_ucResultTime��Ϊͬһ��ַ;
///*	3.�ۼӵ�ʱ�䲻�ܳ���һ����ʱ��(28��)												*///
///*Others:	�˺���רΪ���������ۼӷ���ʹ��,���������Ϊ96Сʱ,�ʴ˺����ۼӷ����Ϊһ����*///
///******************************************************************************************///
void SF_MinsAdd_LoadProfile(uchar8 *P_ucSourceTime,ulong32 V_ulAddMins,uchar8 *P_ucResultTime)
{
	uchar8 V_ucTemp,V_ucMthTemp;
	uchar8 V_ucTimeBuff[C_LoadTLength];
	ulong32 V_ulCalTemp,V_ulTemp,V_ulYearTemp;

	
	SF_DECtoHEXByte(&P_ucSourceTime[0],&V_ucTemp);
	
	V_ulCalTemp = V_ulAddMins + V_ucTemp;///*�ӷ��ӿ�ʼ�ۼ�*///
	
	V_ulTemp = V_ulCalTemp%60;
	
	PF_Ulong32ToBuffer4(&V_ucTemp,&V_ulTemp,1);
	
	V_ucTimeBuff[C_Minute_L] = SF_HEXtoDECByte(V_ucTemp);	///*��ֵ����*///
	
	if(V_ulCalTemp >= 60)
	{
		V_ulCalTemp /= 60;		

		SF_DECtoHEXByte(&P_ucSourceTime[1],&V_ucTemp);
		
		V_ulCalTemp += V_ucTemp;///*�ۼ�Сʱ*///
		
		V_ulTemp = V_ulCalTemp%24;
		
		PF_Ulong32ToBuffer4(&V_ucTemp,&V_ulTemp,1);
		
		V_ucTimeBuff[C_Hour_L] = SF_HEXtoDECByte(V_ucTemp);	///*��ֵСʱ*///
		
		if(V_ulCalTemp >= 24)
		{
			V_ulCalTemp /= 24;		
	
			SF_DECtoHEXByte(&P_ucSourceTime[2],&V_ucTemp);
			
			V_ulCalTemp += V_ucTemp;///*�ۼ���*///
			
			if(P_ucSourceTime[3] == 2)///*2�����ж�����*///
			{
				SF_DECtoHEXByte(&P_ucSourceTime[4],&V_ucTemp);
				
				V_ulYearTemp = V_ucTemp + 2000;///*�������ǰ��,Ĭ��Ϊ20XX��*///
				
				if(((V_ulYearTemp%4)==0))///*20XX��ֻҪ��4������������*///
				{
					V_ucMthTemp = 29;
				}
				else
				{
					V_ucMthTemp = 28;
				}
			}
			else
			{
				SF_DECtoHEXByte(&P_ucSourceTime[3],&V_ucTemp);
				
				V_ucMthTemp = C_MonthNum[V_ucTemp-1];
			}
			if(V_ulCalTemp==V_ucMthTemp)
			{
				V_ulTemp = V_ulCalTemp;
			}
			else
			{
				V_ulTemp = V_ulCalTemp%V_ucMthTemp;
			}
			PF_Ulong32ToBuffer4(&V_ucTemp,&V_ulTemp,1);
			
			V_ucTimeBuff[C_Day_L] = SF_HEXtoDECByte(V_ucTemp);///*��ֵ��*///
			
			if(V_ulCalTemp > V_ucMthTemp)///*���ڵ�ǰ�µ�����*///
			{
				V_ulCalTemp /= V_ucMthTemp;		
		
				SF_DECtoHEXByte(&P_ucSourceTime[3],&V_ucTemp);
				
				V_ulCalTemp += V_ucTemp;///*�ۼ���*///
				
				if(V_ulCalTemp==12)
				{
					V_ulTemp = 12;
				}
				else
				{
					V_ulTemp = V_ulCalTemp%12;
				}
				PF_Ulong32ToBuffer4(&V_ucTemp,&V_ulTemp,1);
				
				V_ucTimeBuff[C_Month_L] = SF_HEXtoDECByte(V_ucTemp);///*��ֵ��*///
				
				if(V_ulCalTemp > 12)///*���ڵ�ǰ�µ�����*///
				{
					SF_DECtoHEXByte(&P_ucSourceTime[4],&V_ucTemp);
					
					V_ucTemp++;
			
					V_ucTimeBuff[C_Year_L] = SF_HEXtoDECByte(V_ucTemp);///*��ֵ��*///		
				}
				else
				{
					V_ucTimeBuff[C_Year_L] = P_ucSourceTime[4];///*��ֵ��*///	
				}
			}
			else
			{
				V_ucTimeBuff[C_Month_L] = P_ucSourceTime[3];///*��ֵ��*///
				
				V_ucTimeBuff[C_Year_L] = P_ucSourceTime[4];///*��ֵ��*///	
			}
		}
		else
		{
			V_ucTimeBuff[C_Day_L] = P_ucSourceTime[2];///*��ֵ��*///
			
			V_ucTimeBuff[C_Month_L] = P_ucSourceTime[3];///*��ֵ��*///
		
			V_ucTimeBuff[C_Year_L] = P_ucSourceTime[4];///*��ֵ��*///
		}
	}
	else
	{
		V_ucTimeBuff[C_Hour_L] = P_ucSourceTime[1];///*��ֵСʱ*///
		
		V_ucTimeBuff[C_Day_L] = P_ucSourceTime[2];///*��ֵ��*///
		
		V_ucTimeBuff[C_Month_L] = P_ucSourceTime[3];///*��ֵ��*///
		
		V_ucTimeBuff[C_Year_L] = P_ucSourceTime[4];///*��ֵ��*///	
	}
	PF_CopyDataBytes(V_ucTimeBuff,P_ucResultTime,C_LoadTLength);///*���ۼӺ�ʱ�䴫��Ŀ���ַ*///
}

///******************************************************************************************///
///*Function:uchar8 SF_GetSeqData_LoadProfile												*///
///*Description:��ȡ���ݲ�ָ�������ĸ�������,û���ݵĲ�����Ӧ����											*///
///*Input:	*V_ulDataId-���б����е����ݱ�ʶ
///*		* P_ucStartTime -��ȡ���ɼ�¼����ʼʱ�䣬5�ֽڣ�YYMMDDhhmm��
///*		* P_ucBlockNum-�������賭������
///*		*P_ucIntTime-���ʱ��
///*		P_ucFollowFlag--�Ƿ�Ϊ��һ֡
///*		* P_ucGVBuffer��ȫ�ֱ���,����ʱ���ڲ���������
///*		* P_ucDataTemp �C�������,���ݻ�����
///*Output: * P_ucGVBuffer���������,�������ĵ������ݷ���˴�
///*		* P_ucDataTemp �C�������,���ݻ�����
///*Return:C_OK��C_Error                         											*///
///*Calls:																					*///
///*Called By:																				*///
///*Influence:																				*///
///*Author:																					*///
///*Tips:																					*///
///*Others:																					*///
///******************************************************************************************///
uchar8 SF_GetSeqData_LoadProfile(ulong32 *V_ulDataId,uchar8 *P_ucStartTime,uchar8 *P_ucBlockNum,uchar8 *P_ucIntTime,uchar8 P_ucFollowFlag,uchar8 *P_ucGVBuffer,uchar8 *P_ucDataTemp)
{
	uchar8 V_ucDataLen=0;///*�����������ݳ���,ͬʱ����ƫ����*///
	uchar8 V_ucReadTime[C_LoadTLength];
	uchar8 V_ucDataTemp[C_LoadMaxLen],V_ucLength_Load=C_LoadMaxLen,V_ucNum_RdLoad=1;;///*�������ݻ�����*///
	ulong32 V_ulLoadTypeID;///*��Ӧ�ĸ������ͱ�ʶ��*////
	ulong32 V_ulTemp;
	uchar8 V_ucDataLength,V_ucOffset,V_ucBlockNum=*P_ucBlockNum;
	uchar8 i,j,V_ucTemp,V_ucReturnTemp=0;
	uchar8 V_ucFirstReadFlag = 0x11;///*�ں���֡��ָʾ��һ�ζ����ݱ�־,�ڶ����ݳ�ʱ�ж�,����һ�ζ�ʱ��C_FirstFrame,����ΪC_OtherFrame*///
	uchar8 V_ucTableLen = sizeof(Str_LoadStatus)/sizeof(Str_LoadReadStatus);
	uchar8 V_ucData[C_LoadMaxLen];
	
	PF_CopyDataBytes(P_ucStartTime,V_ucReadTime,C_LoadTLength);///*��ֵ����ʱ��*///
	
	for(i=0;i<V_ucTableLen;i++)
	{
		if((*V_ulDataId) == Str_LoadStatus[i].V_ulDataId)
		{
			V_ulLoadTypeID = Str_LoadStatus[i].V_ulTypeId;///*��ֵ���ͱ�ʶ��*///
		
			V_ucDataLength = Str_LoadStatus[i].V_ucDataLen;///*��ֵ���ݳ���*///
			
			V_ucOffset = Str_LoadStatus[i].V_ucOffset;///*��ֵƫ����*///
			
			break;
		}
	}
	if(i >= V_ucTableLen)
	{
		return C_Error;
	}
	if(P_ucFollowFlag == C_FirstFrame)///*��һ֡,�轫��ʶ���ʱ����뻺��*///
	{
		V_ucFirstReadFlag = 0xFF;///*����һ֡ʱ,���������ݲ��ΪC_OtherFrame,�˴���ΪFF*///
		
		PF_CopyDataBytes(V_ucReadTime,&P_ucDataTemp[V_ucDataLen],CLLoad_Rec_Time_Year);///*����ʼ��ʱ����뻺��*///
		V_ucDataLen += C_LoadTLength;	
		
		if(InF_ReadLoadData(V_ulLoadTypeID,V_ucReadTime,V_ucDataTemp,&V_ucNum_RdLoad,&V_ucLength_Load,C_FirstFrame)!=C_OK)
		{
			V_ucReturnTemp = 0xAA;
		}
		///*�Ƚϸ��ɼ�¼��ʱ����֮ǰ���õĶ�ȡʱ���С��ϵ*///
		V_ucTemp = PF_Campare_Data(&V_ucDataTemp[C_TimeOffset],V_ucReadTime,CLLoad_Rec_Time_Year);
		
		if(V_ucTemp == C_Equal)///*��ǰʱ��͸��ɼ�¼ʱ�����ʱ,ֱ�Ӹ�ֵ����*///
		{///*���������ݷ��뻺��*///
			PF_CopyDataBytes(&V_ucDataTemp[V_ucOffset],&P_ucDataTemp[V_ucDataLen],V_ucDataLength);	
			
			if(SF_JudgeType_LoadProfile(*V_ulDataId)==C_LoadType_Energy)///*����������,�轫���ݷ���ȫ�ֱ�����*///
			{
				PF_CopyDataBytes(&V_ucDataTemp[V_ucOffset],P_ucGVBuffer,V_ucDataLength);
			}
			V_ucDataLen += V_ucDataLength;///*�������ݳ���*///
		
			V_ucBlockNum --;///*���������*///
		
			SF_MinsAdd_LoadProfile(V_ucReadTime,*P_ucIntTime,V_ucReadTime);///*���³���ʱ��*///
		}
		if((V_ucTemp != C_Equal) || (V_ucReturnTemp == 0xAA))
		{///*��������ʱ���Ҫ��ʱ�䲻��,�������ܸ���ʱ,��ǰ��ȡ���һ�θ��ɼ�¼����*///
			if(SF_JudgeType_LoadProfile(*V_ulDataId) == C_LoadType_Energy)
			{
				V_ucLength_Load=C_LoadMaxLen;
				V_ucNum_RdLoad = 1;
				
				if(InF_ReadLastTimeLoadData(V_ulLoadTypeID,V_ucReadTime,V_ucData,&V_ucNum_RdLoad,&V_ucLength_Load)!= C_OK)///*��ǰ�������ظ��ɼ�¼*///
				{///*��ǰ�����ݣ���������*///
					for(i=0;i<V_ucDataLength;i++)
					{
						V_ucData[V_ucOffset + i] = 0;
					}
				}
				///*�����ݷ���ȫ�ֱ���*///
				PF_CopyDataBytes(&V_ucData[V_ucOffset],P_ucGVBuffer,V_ucDataLength);
			}
			if(V_ucReturnTemp == 0xAA)///*��������������������,��ȫ����*///
			{
				for(i=0;i<V_ucBlockNum;i++)
				{
					SF_FillData_LoadProfile(*V_ulDataId,P_ucGVBuffer,&P_ucDataTemp[V_ucDataLen],V_ucDataLength);///*������*///
					V_ucDataLen +=V_ucDataLength;///*�ۼӳ���*///
				}
				return C_OK;
			}
			else///*�貹����*///
			{
				SF_FillData_LoadProfile(*V_ulDataId,P_ucGVBuffer,&P_ucDataTemp[V_ucDataLen],V_ucDataLength);///*������*///
				
				V_ucDataLen +=V_ucDataLength;///*�ۼӳ���*///
				i = 1;
				
				PF_Buffer4ToUlong32(P_ucIntTime,&V_ulTemp,1);///*�����ʱ��תulong32,�����ۼӶ�ȡʱ��*///
		
				for(;i<V_ucBlockNum;i++)
				{
					SF_MinsAdd_LoadProfile(V_ucReadTime,V_ulTemp,V_ucReadTime);///*�ۼ�ʱ����*///
					
					V_ucTemp = PF_Campare_Data(&V_ucDataTemp[C_TimeOffset],V_ucReadTime,CLLoad_Rec_Time_Year);
			
					if(V_ucTemp == C_Equal)///*��������ݸ�ֵ*///
					{
						PF_CopyDataBytes(&V_ucDataTemp[V_ucOffset],&P_ucDataTemp[V_ucDataLen],V_ucDataLength);
						V_ucDataLen +=V_ucDataLength;///*�ۼӳ���*///
						
						SF_MinsAdd_LoadProfile(V_ucReadTime,*P_ucIntTime,V_ucReadTime);///*���³���ʱ��*///
						
						if(SF_JudgeType_LoadProfile(*V_ulDataId)==C_LoadType_Energy)///*����������,�轫���ݷ���ȫ�ֱ�����*///
						{
							PF_CopyDataBytes(&V_ucDataTemp[V_ucOffset],P_ucGVBuffer,V_ucDataLength);
						}
                        i++;
						break;
					}
					else if(V_ucTemp == C_LessThan)///*���ݲ㷵��ʱ��С���ۼ�ʱ��,�˳�jѭ��,�������ۼ�ʱ�为��*///
					{
						break;
					}
					else///*���ݲ㷵��ʱ������ۼ�ʱ��,�����jѭ���ۼӼ��ʱ��*///
					{
						SF_FillData_LoadProfile(*V_ulDataId,P_ucGVBuffer,&P_ucDataTemp[V_ucDataLen],V_ucDataLength);///*������*///
						V_ucDataLen +=V_ucDataLength;///*�ۼӳ���*///
						
						continue;
					}
				}
				V_ucBlockNum -= i;///*���������*///
			}
		}
	}
	for(i=0;i<V_ucBlockNum;i++)///*iѭ��*///
	{
		V_ucLength_Load = C_LoadMaxLen;
		V_ucNum_RdLoad = 1;
		
		if(V_ucFirstReadFlag == 0x11)///*������֡�״ζ����ݲ�ʱ,����C_FirstFrame��*///
		{
			V_ucFirstReadFlag = 0xFF;
			
			V_ucTemp = InF_ReadLoadData(V_ulLoadTypeID,V_ucReadTime,V_ucDataTemp,&V_ucNum_RdLoad,&V_ucLength_Load,C_FirstFrame);
		}
		else
		{
			V_ucTemp = InF_ReadLoadData(V_ulLoadTypeID,V_ucReadTime,V_ucDataTemp,&V_ucNum_RdLoad,&V_ucLength_Load,C_OtherFrame);
		}
		if(V_ucTemp != C_OK)
		{
			for(j=0;j<(V_ucBlockNum-i);j++)
			{
				SF_FillData_LoadProfile(*V_ulDataId,P_ucGVBuffer,&P_ucDataTemp[V_ucDataLen],V_ucDataLength);///*������*///
				V_ucDataLen +=V_ucDataLength;///*�ۼӳ���*///
			}
			return C_OK;
		}
		///*�Ƚϸ��ɼ�¼��ʱ����֮ǰ���õĶ�ȡʱ���С��ϵ*///
		V_ucTemp = PF_Campare_Data(&V_ucDataTemp[C_TimeOffset],V_ucReadTime,CLLoad_Rec_Time_Year);
		
		if(V_ucTemp == C_Equal)///*����ʱ��Ͷ�ȡʱ����ͬ,�����ݷ��뻺������ȫ�ֱ�����*///
		{
			PF_CopyDataBytes(&V_ucDataTemp[V_ucOffset],&P_ucDataTemp[V_ucDataLen],V_ucDataLength);
			V_ucDataLen +=V_ucDataLength;///*�ۼӳ���*///
			
			SF_MinsAdd_LoadProfile(V_ucReadTime,*P_ucIntTime,V_ucReadTime);///*���³���ʱ��*///
			
			if(SF_JudgeType_LoadProfile(*V_ulDataId)==C_LoadType_Energy)///*����������,�轫���ݷ���ȫ�ֱ�����*///
			{
				PF_CopyDataBytes(&V_ucDataTemp[V_ucOffset],P_ucGVBuffer,V_ucDataLength);
			}
		}
		else
		{
			SF_FillData_LoadProfile(*V_ulDataId,P_ucGVBuffer,&P_ucDataTemp[V_ucDataLen],V_ucDataLength);///*������*///
			
			V_ucDataLen +=V_ucDataLength;///*�ۼӳ���*///
			i++;
			
			PF_Buffer4ToUlong32(P_ucIntTime,&V_ulTemp,1);///*�����ʱ��תulong32,�����ۼӶ�ȡʱ��*///
			
			for(;i<V_ucBlockNum;i++)///*jѭ��*///
			{
				SF_MinsAdd_LoadProfile(V_ucReadTime,V_ulTemp,V_ucReadTime);///*�ۼ�ʱ����*///
				
				V_ucTemp = PF_Campare_Data(&V_ucDataTemp[C_TimeOffset],V_ucReadTime,CLLoad_Rec_Time_Year);
		
				if(V_ucTemp == C_Equal)///*��������ݸ�ֵ*///
				{
					PF_CopyDataBytes(&V_ucDataTemp[V_ucOffset],&P_ucDataTemp[V_ucDataLen],V_ucDataLength);
					V_ucDataLen +=V_ucDataLength;///*�ۼӳ���*///
					
					SF_MinsAdd_LoadProfile(V_ucReadTime,*P_ucIntTime,V_ucReadTime);///*���³���ʱ��*///
					
					if(SF_JudgeType_LoadProfile(*V_ulDataId)==C_LoadType_Energy)///*����������,�轫���ݷ���ȫ�ֱ�����*///
					{
						PF_CopyDataBytes(&V_ucDataTemp[V_ucOffset],P_ucGVBuffer,V_ucDataLength);
					}
					break;
				}
				else if(V_ucTemp == C_LessThan)///*���ݲ㷵��ʱ��С���ۼ�ʱ��,�˳�jѭ��,�������ۼ�ʱ�为��*///
				{
					i--;
					
					break;
				}
				else///*���ݲ㷵��ʱ������ۼ�ʱ��,�����jѭ���ۼӼ��ʱ��*///
				{
					SF_FillData_LoadProfile(*V_ulDataId,P_ucGVBuffer,&P_ucDataTemp[V_ucDataLen],V_ucDataLength);///*������*///
					V_ucDataLen +=V_ucDataLength;///*�ۼӳ���*///
					
					continue;
				}
			}
		}	
	}
	return C_OK;
}

///******************************************************************************************///
///*Function:void  SF_FillData_LoadProfile													*///
///*Description:�����ݺ���																	*///
///*Input:	V_ulDataId-���ȡ���ݵ����ݱ�ʶ
///*		* P_ucGVBuffer �C��ŵ�����ʱ���ݵ�ȫ�ֱ���
///*		*P_ucDataTemp-�������,�������ݷ��ڴ˴�
///*		V_ucLength-�������,�������ݵĳ���
///*Output: *P_ucDataTemp-�������,�������ݷ��ڴ˴�
///*Return:��			                         											*///
///*Calls:																					*///
///*Called By:																				*///
///*Influence:																				*///
///*Author:																					*///
///*Tips:																					*///
///*Others:																					*///
///******************************************************************************************///
void SF_FillData_LoadProfile(ulong32 V_ulDataId,uchar8 *P_ucGVBuffer,uchar8 *P_ucDataTemp,uchar8 V_ucLength)
{
	uchar8 V_ucTemp[16];
	uchar8 i;
		
	if(SF_JudgeType_LoadProfile(V_ulDataId)==C_LoadType_Energy)///*����������,��ȡȫ�ֱ��������ݽ��в���*///
	{
		PF_CopyDataBytes(P_ucGVBuffer,P_ucDataTemp,V_ucLength);	
	}
	else///*˲ʱ����FF*///
	{
		for(i=0;i<V_ucLength;i++)
		{
			V_ucTemp[i] = 0xFF;	
		}
		PF_CopyDataBytes(V_ucTemp,P_ucDataTemp,V_ucLength);	
	}
}

///****************************************************************************************///
///*Function��uchar8 SF_JudgeType_LoadProfile										     *///
///*Description�����ݱ�ʶ��,�ж�Ҫ���ȡ�ĸ�������       								  *///
///*Input��*V_ulID-�������ɼ�¼�ı�ʶ��													  *///
///*Output����																			  *///
///*Return:			                         										*///
///*Calls��																				  *///
///*Called By��																			  *///
///*Influence����																		  *///
///*Tips��																				  *///
///*Others��																			  *///
///*Author:																				  *///
///****************************************************************************************///
uchar8 SF_JudgeType_LoadProfile(ulong32 V_ulID)
{
	if((V_ulID &0x00000600)==0x00000600)///*����������061006XX��061007XX,��2�ֽڵ�2/3λΪ1*///
	{
		return C_LoadType_Energy;
	}
	else
	{
		return C_LoadType_Variable;
	}
}

///****************************************************************************************///
///*Function��void SF_DECtoHEXByte(uchar8 *V_ucSourceData,uchar8 *V_ucResultData)	     *///
///*Description��1�ֽ�10������ת��Ϊ1�ֽ�16������       								  *///
///*Input��10��������ַV_ucSourceData,ת����16��������ַV_ucResultData					  *///
///*Output����																			  *///
///*Calls��																				  *///
///*Called By��																			  *///
///*Influence����																		  *///
///*Tips��																				  *///
///*Others��																			  *///
///*Author:																				  *///
///****************************************************************************************///
void SF_DECtoHEXByte(uchar8 *V_ucSourceData,uchar8 *V_ucResultData)
{
	*V_ucResultData = ((*V_ucSourceData >> 4) * 10) + (*V_ucSourceData & 0x0f);
}

///************************************************************************************************************************************///
///*Function��uchar8 SF_HEXtoDECByte																                         */// 
///*Description����1��16����BCD��, ת��Ϊ10������																				  *///
///*Input��HEXdata-hex��ʽ����										 							  *///
///*Output����																								  *///
///*Return:ʮ����BCD                         											*///
///*Calls��																															  *///
///*Called By��																														  *///
///*Influence���� 																													  *///
///*Tips���˺�����֧��������ʱ�ֵ�ת��,���ֵΪ99,�ʷ���ֵΪuchar8												 *///
///*Others��																														  *///
///*Author:																												  *///
///************************************************************************************************************************************///
uchar8 SF_HEXtoDECByte(uchar8 HEXdata)  
{
	ushort16 i;	
	
	i=HEXdata/10;
	
	i=i<<4;
	
	i+=HEXdata%10;

	return(i);		
}
