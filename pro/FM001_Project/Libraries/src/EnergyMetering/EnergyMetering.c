/********************************************************************************
Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     EnergyMetering.c
Version:       V1
Author:        jiangzs
Date:          2014-3-12
Description:   ���ܴ����ļ�
---------------------------------------------------------------------------------
History1:      ��1���޸�
����1. Date:   20219016
       Author: fy
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
#include "EnergyMetering.h"


/*--------------------------------------------------------------------------*/
/*ȫ�ֱ���*/
/*--------------------------------------------------------------------------*/
static uchar8 SV_ucEnergySafeFlag;
static uchar8 SV_ucMoneyToPurchaseFlag[3];		/*��ֵ��־,�����ֽ�CRC,CRC������Ϊû�й���*/
/*--------------------------------------------------------------------------*/

/*��ϵ��ܺ���������ʶ��ת��*/
const ulong32 C_CurrentEnergyCode[ ][2]=
{	/*ͨ�����ݱ�ʶ��				���ݲ����ݱ�ʶ*/
	CCom_Ac_PreEn_FF_0,		CPos_Ac_En_PreFF_0,         /*����й��ܵ���*/
	
	CCom_Re1_PreEn_FF_0,	CQua1_Re_PreEn_FF_0,	    /*����޹�1�ܵ���*/
	CCom_Re2_PreEn_FF_0,	CQua1_Re_PreEn_FF_0,	    /*����޹�2�ܵ���*/
	
	C_Fre_AComRe1PreEn, 	C_Fre_AQuadrant1PreEn,		/*A������޹�1����*/
	C_Fre_AComRe2PreEn, 	C_Fre_AQuadrant1PreEn,		/*A������޹�2����*/

	C_Fre_BComRe1PreEn, 	C_Fre_BQuadrant1PreEn,		/*B������޹�1����*/
	C_Fre_BComRe2PreEn, 	C_Fre_BQuadrant1PreEn,		/*B������޹�2����*/
	
	C_Fre_CComRe1PreEn, 	C_Fre_CQuadrant1PreEn,		/*C������޹�1����*/
	C_Fre_CComRe2PreEn, 	C_Fre_CQuadrant1PreEn,		/*C������޹�2����*/
};  
#define C_EnergyCodeNum   ( (sizeof(C_CurrentEnergyCode) / 2 ) / sizeof(ulong32) )
 
/*��ϵ���*/
const uchar8 C_ComEnergyCode[ ]=
{
	0x00, 0x30, 0x40
};
#define C_ComDI2Num   ( ( sizeof(C_ComEnergyCode) ) / sizeof(uchar8) )


const uchar8 C_RCom1EnergyCode[ ]=
{
	0x30, 0x31, 0x32, 0x33
};
#define C_RCom1DI2Num   ( ( sizeof(C_RCom1EnergyCode) ) / sizeof(uchar8) )


/***************************************************************************************************
����ԭ�ͣ�void SF_SendMessege(uchar8 V_ucMsgDerictAddr, uchar8 *pV_ucBuffer, uchar8 V_ucMsgLen)
����������������Ϣ
���������V_ucMsgDerictAddr,Ŀ�ĵ�ַ��
          pV_ucBuffer��������Ϣ���ʹ�ŵ�ַ��
		  V_ucMsgLen����Ϣ���ȣ�V_ucMsgLen�����Ѿ�����1�ֽڵ���Ϣ���͵ĳ��ȣ���˺����ڲ�����Ҫ�ټ�1
�����������
���ز�������
����λ�ã�
��    ע��
***************************************************************************************************/
void SF_SendMessege(uchar8 V_ucMsgDerictAddr, uchar8 *pV_ucBuffer, uchar8 V_ucMsgLen)
{
	Str_Msg_Parameter Str_Message;
	
	Str_Message.SourceAddr = C_Msg_EnergyMetering;
	Str_Message.DerictAddr = V_ucMsgDerictAddr;
	Str_Message.Length     = V_ucMsgLen;
	Str_Message.Parameter  = pV_ucBuffer;
	Str_Message.PowerFlag  = C_PowerOn;
	
	InF_WriteMessege(&Str_Message);		/*������Ϣ*/
}
/***************************************************************************************************
����ԭ�ͣ�void SF_Read_PulseConstant(ulong64 *pV_ullPulseConstant)
������������ȡ�������峣����hex��ʽ����ȡ���ݲ���Ĭ��1000����
���������pV_ullPulseConstant:ָ���ȡ���峣�������ַ
���������*pV_ullPulseConstant��8�ֽ����峣��
���ز�������
����λ�ã����ܶ�ȡ�ӿں�������	
��    ע��
***************************************************************************************************/
void SF_Read_PulseConstant(ulong64 *pV_ullPulseConstant)
{
	uchar8   V_ucTurn;
	uchar8   V_ucBuffer[4];
	ushort16 V_usLen, V_usDataEncode;
	
	V_usDataEncode = 0;
	V_usLen = CLPulse_Constant;
	V_ucTurn = InF_Read_Data(CPulse_Constant, V_ucBuffer, &V_usLen, &V_usDataEncode);
    PF_Buffer8ToUlong64(V_ucBuffer, pV_ullPulseConstant, CLPulse_Constant);
	if( ( V_ucTurn != C_OK ) || ( *pV_ullPulseConstant == 0xFFFFFFFF ) )
	{
		*pV_ullPulseConstant = 1000;
	}
}
#if(_DEBUG_FY) /*ƴ�Ӻ�ȥ��*/
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_ReadEnergy_MethodJudge(ulong32 V_ulDataCode, uchar8 V_ucMethod)
���������������ܷ����ж�
���������V_ulDataCode��OAD��698OAD��
		 V_ucMethod��V_ ucMethod����Ϊϣ����ȡ�����ݸ�ʽ��C_Format_BCDΪBCD��ʽ��C_Format_HEXΪhex��ʽ��������ʽ������չ��
���������pV_ullMaxEnergy�������ݵ����ֵ
���ز�������ȡ������C_Nature2BCD,����2BCD
				   C_Nature4BCD,����4BCD
				   C_Nature2HEX,����2HEX
				   C_Nature4HEX,����4HEX
				   C_Nature6HEX,����6HEX
				   C_ErrorMethod,�쳣����
����λ�ã���ȡ����
��    ע��
*******************************************************************************/
uchar8 SF_ReadEnergy_MethodJudge(ulong32 V_ulDataCode, uchar8 V_ucMethod, ulong64 *pV_ullMaxEnergy)
{
	uchar8 V_ucReturn = C_ErrorMethod;
	
	if ( ( V_ulDataCode & 0xFF00FF00) == 0x00000200)
	{
		if(V_ucMethod == C_Format_BCD)
		{
			V_ucReturn = C_Nature2BCD;
		}
		else if ( V_ucMethod == C_Format_HEX )
		{
			V_ucReturn = C_Nature2HEX;
		}
		
		*pV_ullMaxEnergy = C_ConEnergyToZero_Nature2;
	}
	else if ( ( V_ulDataCode & 0xFF00FF00) == 0x00000400) 
	{
		if(V_ucMethod == C_Format_BCD)
		{
			V_ucReturn = C_Nature4BCD;
		}
		else if ( V_ucMethod == C_Format_HEX )
		{
			V_ucReturn = C_Nature4HEX;
		}
		*pV_ullMaxEnergy = C_ConEnergyToZero_Nature4;
	}
	else if ( ( V_ulDataCode & 0xFF00FF00) == 0x00000600)
	{
		if ( V_ucMethod == C_Format_HEX )
		{
			V_ucReturn = C_Nature6HEX;
		}
		*pV_ullMaxEnergy = C_ConEnergyToZero_Nature6;
	}
	else 
	{
		if ( V_ucMethod == C_Format_BCD )
		{
			V_ucReturn = C_Nature2BCD;
		}
	}

	return V_ucReturn;
}
#endif
/**********************************************************************************************************
����ԭ��: uchar8 SF_ReadConEnergy_Pulse_Single(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen) 		
��������: ������ȡ��ǰ��ϵ��ܽӿں���
�������: V_ulDataCode:Ϊ��ȡ���ܱ�ʶ��;
		  pV_ucBuffer:��ȡ���ݵĻ�����׵�ַ
		  *pV_usLen: ��ȡ���ݵ���󻺴�ĳ���
�������: pV_ucBuffer:��ȡ���ݵĻ�����׵�ַ
		  *pV_usLen: ��ȡ���ݵĳ���
���ز���: C_OK��ʾ��ȡ�ɹ���
          C_IDError��ʾ���ݱ�ʶ���
          C_CRCError���ݲ�CRC��
          C_DataLenError��ʾ���ݳ��ȴ�
          C_NoAccess��ʾ��Ȩ�ޣ�
          C_SafeFlagError��ʾ��ȫ��־��
          C_Error��ʾ��������
����λ��: ���ܶ�ȡ�ӿں�������
��    ע: ��SF_ReadConEnergy_Pulse��������
          SF_ReadConEnergy_Pulse���ж��Ƿ��Ǽ��ϣ�ѭ����ȡ;
          SF_ReadConEnergy_Pulse_Singleֻ�ܵ�����ȡ;

		  /---------------------------------------------------------------------------/
		  *		*	OAD����2		*	OAD����4			*		OAD����6		  *				
		  *-------------------------------------------------*-------------------------*
		  *	HEX	*	4�ֽڣ�2λС��	*	5�ֽڣ�4λС��		*		1�ֽ�			  *
		  /---------------------------------------------------------------------------/

*********************************************************************************************************/
uchar8 SF_ReadConEnergy_Pulse_Single(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen)
{
	ulong64 V_ullActiveData = 0, V_ullReactiveData = 0, V_ullTemp;
	ulong32 V_ulCodeTemp, V_ulCodeCal;
	uchar8  V_uci, V_ucOAD[C_DataCodeLen], V_ucNum, V_ucMode, V_ucModeTemp;
	ulong64 *pV_ullData;
	ushort16 V_usLen, V_usDataEncode;
	
	PF_Ulong32ToBufferX(V_ucOAD, &V_ulDataCode, C_DataCodeLen);		/*����ʶ��ת��Ϊ����*/
	
	/*�����ж���Ҫ��ȡ�����ݱ�ʶ*/
	V_ulCodeTemp = ( V_ulDataCode & 0xFFFF0000 ) | 0x00000400;
	for( V_uci = 0; V_uci < C_EnergyCodeNum; V_uci++ )
	{
		if( C_CurrentEnergyCode[V_uci][0] == V_ulCodeTemp )
		{
			V_ulCodeTemp = C_CurrentEnergyCode[V_uci][1] | ( V_ulDataCode & 0x000000FF );
			break;
		}
	}   
	if(V_uci >= C_EnergyCodeNum)		/*û�в��ҵ����ݱ�ʶ�룬Ӧ�����ݱ�ʾ��*/
	{
		return C_IDError;
	}
	   
	/*��ȡ���ݲ�����й�ģʽ��*/
	V_usDataEncode = 0;
	V_usLen = CLActive_Com_State;
	if( V_ucOAD[C_O_DI2] == 0x00 )		/*����й��ܵ���*/
	{
		if( InF_Read_Data( CActive_Com_State, &V_ucMode, &V_usLen, &V_usDataEncode) != C_OK )	
		{
			V_ucMode = 0x05;			/*ģʽ�ֶ�ȡ���ݲ����Ĭ�����ӷ�*/
		}
		V_ucMode &= 0x0F;				/*����й�ģʽ�ָ�4λ��Ч*/
	}
	else
	{
        /*��ȡ����޹�ģʽ��*/
		for( V_uci = 0; V_uci < C_RCom1DI2Num; V_uci++ )
		{
			if( C_RCom1EnergyCode[V_uci] == V_ucOAD[C_O_DI2] )
			{
				break;
			}
		}
		if( V_uci < C_RCom1DI2Num )
		{
			if( InF_Read_Data( CReactive_Com_State1, &V_ucMode, &V_usLen, &V_usDataEncode ) != C_OK )	
			{
				V_ucMode = 0x41;				/*ģʽ�ֶ�ȡ���ݲ����Ĭ��1��4�������*/
			}
		}
		else
		{
			if( InF_Read_Data( CReactive_Com_State2, &V_ucMode, &V_usLen, &V_usDataEncode ) != C_OK )	
			{
				V_ucMode = 0x14;				/*ģʽ�ֶ�ȡ���ݲ����Ĭ��2��3�������*/
			}
		}
	}
	
	if( ( ( V_ucOAD[C_O_DI2] == 0x40 )
	   || ( V_ucOAD[C_O_DI2] == 0x30 )
	   || ( V_ucOAD[C_O_DI2] == 0x00 ) )
	   && ( V_ucOAD[C_O_DI0] == 0x01 ) )  		/*������ϵ��ܵ��ܵ��ܣ���Ҫ��ȡ12���ʵ����ۼӵõ�*/
	{
		V_ucNum = C_MaxRatesNum;
	    V_ulCodeTemp += C_GetNextRatesEnergy;
	}
	else if( ( ( V_ulCodeTemp & 0x000F0000 ) != 0x00000000 ) && ( V_ucOAD[C_O_DI0] == 0x00 ) )		/*��������00����*/
	{
		V_ucNum = 1;
	    V_ulCodeTemp += C_GetNextRatesEnergy;
	}
	else
	{
		V_ucNum = 1;
	}
	
	/*���¶�ȡ�ۼӵ���ϵ��ܵĵ�������*/
	for( V_uci = 0; V_uci < 4; V_uci++ )								/*�й���2�������Ҫ��ϣ��޹���4�飨4�����ޣ�������Ҫ��ϡ�ѭ��4�Ρ��й�ģʽ�ָ�4λ�ڱ���������ǿ�Ƴ�0*/
	{
		V_ucModeTemp = ( V_ucMode >> ( V_uci * 2 ) ) & 0x03;
		if( ( V_ucModeTemp == 0x03 ) || ( V_ucModeTemp == 0x00 ) )		/*ģʽ�ֶ�Ӧ��һ����ܼȼ��ּ����߲��Ӳ�������ϵ��ܲ���Ҫ����*/
		{
			continue;
		}
		
		if( V_ucModeTemp == 0x01 )				/*�õ����ۼӵ���ϵ���*/
		{
			pV_ullData = &V_ullActiveData;	 	/*ȡ�������ʱ���ܵ�ַ*/
		}
		else					             	/*��ϵ��ܼ�ȥ�õ���*/
		{
			pV_ullData = &V_ullReactiveData;	/*ȡ��ȥ����ʱ���ܵ�ַ*/
		}
		
		V_ullTemp  = 0;
		V_ulCodeCal = V_ulCodeTemp + C_GetNextQuadrantEnergy * V_uci;
		
		V_ucModeTemp = SF_ReadTotalEnergy( V_ulCodeCal, &V_ullTemp, V_ucNum, C_GetNextRatesEnergy );
		if( V_ucModeTemp != C_OK)
		{
			return V_ucModeTemp;	  			/*��ȡ�������ݳ����򷵻���Ӧ�Ĵ�������*/
		}
		*pV_ullData += V_ullTemp;
	}
		
	
	/*���¼�����ϵ���*/
	if( V_ullActiveData >= V_ullReactiveData )	/*��ϵ�����������ܲ�С�ڷ������*/
	{
		V_ullActiveData = V_ullActiveData - V_ullReactiveData;
		V_ucMode = C_ActiveDirection;
	}
	else
	{
		V_ullActiveData = V_ullReactiveData - V_ullActiveData;
		V_ucMode = C_ReactiveDirection;
	}
	
	SF_Read_PulseConstant(&V_ullTemp);	        						/*��ȡ�������峣ulong64��ʽ*/
    
	/*����HEX��ʽ�����ݲ����С��6λ*/
	V_ullActiveData *= C_EnergyChangeEquivalent;	/*���ﲻ�����*/
	V_ullActiveData /= V_ullTemp;	

    V_ucModeTemp = SF_DealEnergyPoint(V_ucOAD[C_O_DI1], &V_ullActiveData, &V_usLen);
    if( V_ucModeTemp != C_OK)
    {
        return V_ucModeTemp;
    }       
	
	if( *pV_usLen < V_usLen )
	{
		return C_DataLenError;
	}
	else
	{
	    *pV_usLen = V_usLen;
        
		if(V_ucMode == C_ReactiveDirection)
		{
			V_ullActiveData = (~V_ullActiveData) + 1;
		}
		
		PF_Ulong64ToBuffer8(pV_ucBuffer, &V_ullActiveData, *pV_usLen);
		return C_OK;
	}
}

/********************************************************************************************************
����ԭ��: uchar8 SF_ReadMonthEnergy(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen)		
��������: ��ȡ�¶��õ���
�������: V_ulDataCode��Ϊ��ȡ���ܱ�ʶ�룻
		  pV_ucBuffer��ָ���ȡ���ݴ�ŵ��׵�ַ��
		  *pV_usLen��   ��ȡ���ݵ���󻺴�ĳ��ȣ�
�������: pV_ucBuffer����ȡ�ĵ��ܵ��׵�ַ��
          *pV_usLen��  ��ȡ�����ݳ��ȣ�
���ز���: C_OK����ʾ��ȡ�ɹ���
          C_IDError����ʾ���ݱ�ʶ���
          C_CRCError�����ݲ�CRC��
          C_DataLenError����ʾ���ݳ��ȴ�
          C_NoAccess����ʾ��Ȩ�ޣ�
          C_SafeFlagError����ʾ��ȫ��־��
          C_Error����ʾ��������
����λ��: ���ܶ�ȡ�ӿں�������
��    ע:���¶��õ���=�������й���-��1���������й��ܣ� ��� �������й���-��1���㷴���й��ܣ���
          �����ṩ�����ݸ�ʽ��4�ֽ�HEX��2λС��
*********************************************************************************************************/
uchar8 SF_ReadMonthEnergy(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen)
{
	uchar8  V_ucTurn, V_ucMode;
	uchar8  V_ucBuffer[5];
	ulong64 V_ullActiveEnergy, V_ullReactiveEnergy, V_ullTemp;
	ushort16 V_usLen, V_usDataEncode;

	/****************��ȡ��ǰ�����й��ܵ���������****************/
	V_ullActiveEnergy = 0;
	
	V_ucTurn = SF_ReadTotalEnergy(CPos_Ac_T1_PreEn_0, &V_ullActiveEnergy, C_MaxRatesNum, C_GetNextRatesEnergy );
	if( V_ucTurn != C_OK )
	{
		return V_ucTurn; 
	}
	
	/**********��ȡ��һ����ʱ�������й��ܵ�����������*************/
	V_usDataEncode = 0;
	V_usLen = CLM_Pos_Ac_Tol_En_Pul_1;
	V_ucTurn = InF_Read_Data(CM_Pos_Ac_Tol_En_Pul_1, V_ucBuffer, &V_usLen, &V_usDataEncode);	
	if( V_ucTurn != C_OK )
	{
		return V_ucTurn;
	}
	
	PF_Buffer8ToUlong64(V_ucBuffer, &V_ullTemp, CLM_Pos_Ac_Tol_En_Pul_1);
	V_ullActiveEnergy -= V_ullTemp;		/*��ǰ�����й��ܵ��ܼ�ȥ��һ����ʱ�������й��ܵ���*/

	/****************��ȡ��ǰ�����й��ܵ���������****************/
	V_ullReactiveEnergy = 0;

	V_ucTurn = SF_ReadTotalEnergy(CRev_Ac_T1_PreEn_0, &V_ullReactiveEnergy, C_MaxRatesNum, C_GetNextRatesEnergy );
	if( V_ucTurn != C_OK )
	{
		return V_ucTurn;
	}

	/**********��ȡ��һ����ʱ�̷����й��ܵ�����������*************/
	V_usDataEncode = 0;
	V_usLen = CLM_Rev_Ac_Tol_En_Pul_1;
	V_ucTurn = InF_Read_Data(CM_Rev_Ac_Tol_En_Pul_1, V_ucBuffer, &V_usLen, &V_usDataEncode);	
	if( V_ucTurn != C_OK )
	{
		return V_ucTurn;
	}
	PF_Buffer8ToUlong64(V_ucBuffer, &V_ullTemp, CLM_Rev_Ac_Tol_En_Pul_1);
	V_ullReactiveEnergy -= V_ullTemp;	/*��ǰ�����й��ܵ��ܼ�ȥ��һ����ʱ�̷����й��ܵ���*/
	
	/**********��ȡ����й�ģʽ��*************/
	V_usDataEncode = 0;
	V_usLen = CLActive_Com_State;
	if( InF_Read_Data(CActive_Com_State, &V_ucMode, &V_usLen, &V_usDataEncode) != C_OK )
	{
		V_ucMode = 0x05;	/*ģʽ�ֶ�ȡ���ݲ����Ĭ�����ӷ�*/
	}
	V_ucMode &= 0x05;		/*698�¶��õ��������������**����й�ģʽ�ָ�4λ��Ч*/
		
	/**********************�������ģʽ�ּ��㵱ǰ������������й��ۼ��õ���**********************/
	V_ullTemp = 0;
	
	if( ( V_ucMode & 0x03 ) == 0x01 )		/*�������Ϊ��*/
	{
		V_ullTemp = V_ullActiveEnergy;
	}
	
	if( ( V_ucMode & 0x0C ) == 0x04 )		/*�������Ϊ��*/
	{
		V_ullTemp += V_ullReactiveEnergy;
	}
	/*else �������ӡ����ӣ��Ѹ�ֵ0*/
	
	/*************************�¶��õ�����λС��******************************/
	SF_Read_PulseConstant(&V_ullReactiveEnergy);	  /*��ȡ�������峣����ulong64��ʽ*/
	V_ullTemp *= C_EnergyChangeEquivalent_Hundred;				/*���ﲻ�����*/
	V_ullTemp /= V_ullReactiveEnergy;
				
	if( *pV_usLen <  CLM_Com_Ac_Tol_En_0 )
	{
		return C_DataLenError;
	}	
	
	*pV_usLen = CLM_Com_Ac_Tol_En_0;
	PF_Ulong64ToBuffer8(pV_ucBuffer, &V_ullTemp, CLM_Com_Ac_Tol_En_0);
	
	return C_OK;
}

/***********************************************************************************************************
����ԭ�ͣ�uchar8 SF_ReadSettlementCycleEnergy_L(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen)
������������ȡ���ݽ�����ܽӿں���
���������V_ulDataCode��Ϊ��ȡ���ܱ�ʶ�룻
		  pV_ucBuffer��ָ���ȡ���ݻ�����׵�ַ��
          *pV_usLen����ȡ���ݻ������󳤶ȣ�	
���������pV_ucBuffer����ȡ�ĵ������ݵ��׵�ַ��
		  *pV_usLen����ȡ�����ݵĳ���
���ز�����C_OK��ʾ��ȡ�ɹ���C_IDError��ʾ���ݱ�ʶ���C_CRCError���ݲ�CRC��C_DataLenError��ʾ���ݳ��ȴ�
		  C_NoAccess��ʾ��Ȩ�ޣ�C_SafeFlagError��ʾ��ȫ��־��C_Error��ʾ��������	
����λ�ã����ܶ�ȡ�ӿں�������	
��    ע��
***********************************************************************************************************/
uchar8 SF_ReadSettlementCycleEnergy_L(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen)
{
	uchar8 V_ucTurn;
	uchar8 V_ucBuffer[6];
	ulong64 V_ullEnergyPulse, V_ullReactiveEnergy;
	ushort16 V_usLen, V_usDataEncode;
		
	/****************��ȡ���ݽ����õ���****************/
	V_usDataEncode = 0;
	V_usLen = C_EnergyPulseLen;
	V_ucTurn = InF_Read_Data(V_ulDataCode, V_ucBuffer, &V_usLen, &V_usDataEncode);
	if( V_ucTurn != C_OK )
	{
		return V_ucTurn;
	}
	PF_Buffer8ToUlong64(V_ucBuffer, &V_ullEnergyPulse, C_EnergyPulseLen);
	
	/*************************���ݽ����õ���Ϊ2λС��******************************/
	SF_Read_PulseConstant(&V_ullReactiveEnergy);				  /*��ȡ�������峣��ulong64��ʽ*/
	
	V_ullEnergyPulse *= C_EnergyChangeEquivalent_Hundred;			/*���ﲻ�����*/
	V_ullEnergyPulse /= V_ullReactiveEnergy;
	
	if( *pV_usLen < CLY_Com_Ac_Tol_En_0 )
	{
		return C_DataLenError;
	}
	else
	{
		*pV_usLen = CLY_Com_Ac_Tol_En_0;
		PF_Ulong64ToBuffer8(pV_ucBuffer, &V_ullEnergyPulse, CLY_Com_Ac_Tol_En_0);
	}
	return C_OK;
}
/**************************************************************************************************
����ԭ�ͣ�uchar8 SF_ReadSettlementCycleEnergy(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen)
���������������ݽ�����ܴ���
���������V_ulDataCode:��Ҫ��ȡ�Ľ�����ݱ�ʶ��
          pV_ucBuffer�� ���ݴ�ŵ��׵�ַ��
          *pV_usLen��   ���ݻ������󳤶ȣ�
���������pV_ucBuffer�� ��ŵĶ�ȡ�Ľ�����ݵ��׵�ַ��
          pV_usLen��    ��ȡ�����ݳ��ȣ�
���ز�����C_OK,��ȡ�ɹ�;��������;
����λ�ã���ȡ���ݼ�����ܵĽӿ�;
��    ע�����ݽ�����ܽ����ر�֧��
          �����ṩ�����ݸ�ʽ��4�ֽ�HEX��2λС��
***************************************************************************************************/
uchar8 SF_ReadSettlementCycleEnergy(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen)
{
	uchar8 V_ucReturn;
	
	if( C_Meter_Type == C_L_SmartMeter )		/*���طѿر�*/
	{
		V_ucReturn = SF_ReadSettlementCycleEnergy_L( V_ulDataCode, pV_ucBuffer, pV_usLen );
	}
	else										/*���ܱ����Զ�̷ѿر�*/
	{
		V_ucReturn = C_IDError;
	}
	
	return V_ucReturn;
}

/***************************************************************************************************
����ԭ�ͣ�uchar8 SF_ReadRemainingMoney_L(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen)
������������ȡ��ǰʣ���͸֧���ӿں���
���������V_ulDataCode:Ϊ��ȡ����ʶ��;
		  pV_ucBuffer:ָ���ȡ���ݴ�ŵ�ַ;
		  *pV_usLen:��ڱ�ʾ��ȡ���ݵ���󻺴泤��;
���������pV_ucbuffer:��Ŷ�ȡ�Ľ�����ݵ��׵�ַ;
          *pV_usLen:��ȡ�����ݳ���;
���ز�����C_OK��ʾ��ȡ�ɹ���C_IDError��ʾ���ݱ�ʶ���C_CRCError���ݲ�CRC��C_DataLenError��ʾ���ݳ��ȴ�
		  C_NoAccess��ʾ��Ȩ�ޣ�C_SafeFlagError��ʾ��ȫ��־��C_Error��ʾ��������
����λ�ã����ܶ�ȡ�ӿں�������
��    ע�����طѿر�ʣ���͸֧����
          /---------------------------------------------------------------------------/
            �����ṩ�����ݸ�ʽ
          /---------------------------------------------------------------------------/
          *	4�ֽ�HEX��2λС��,0.01Ԫ
          * CChargeBal_Hex_Cent 0x202C0201
          * COverDraft_Hex_Cent 0x202D0200
          /---------------------------------------------------------------------------/
         
***************************************************************************************************/
uchar8 SF_ReadRemainingMoney_L(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen)
{
	ulong64 V_ullMoney;
	uchar8  V_ucBuffer[5], V_ucReturn;
	ushort16 V_usLen, V_usDataEncode;
	
	/****************��ȡ���ݲ���/���ݽ������****************/
	V_usDataEncode = 0;
	V_usLen = CLChargeBal_Hex_Full;
	V_ucReturn = InF_Read_Data(V_ulDataCode, V_ucBuffer, &V_usLen, &V_usDataEncode);		
	if( V_ucReturn != C_OK )
	{
		return V_ucReturn;
	}
	
	/*��ȡ0.01Ԫ�Ľ��*/
	PF_Buffer8ToUlong64( V_ucBuffer, &V_ullMoney, CLChargeBal_Hex_Full );
	V_ullMoney /= C_MoneyChangeEquivalent;
	PF_Ulong64ToBuffer8( V_ucBuffer, &V_ullMoney, CLChargeBal_Hex_Cent );
	
	V_usLen = CLChargeBal_Hex_Cent;
	
	if( *pV_usLen <  V_usLen )
	{
		return C_DataLenError;
	}
	else
	{
		*pV_usLen = V_usLen;
		PF_CopyDataBytes_698(V_ucBuffer, pV_ucBuffer, *pV_usLen);
	}
	
	return C_OK;
}

/**************************************************************************************************
����ԭ�ͣ�uchar8 SF_ReadRemainingMoney(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen)
����������������
���������V_ulDataCode:��Ҫ��ȡ�Ľ�����ݱ�ʶ��
          pV_ucBuffer�� ���ݴ�ŵ��׵�ַ��
          *pV_usLen��   ���ݻ������󳤶ȣ�
���������pV_ucBuffer�� ��ŵĶ�ȡ�Ľ�����ݵ��׵�ַ��
          *pV_usLen��    ��ȡ�����ݳ��ȣ�
���ز�����C_OK,��ȡ�ɹ�;��������;
����λ�ã���ȡ���Ľӿ�;
��    ע�� ʣ���͸֧���
***************************************************************************************************/
uchar8 SF_ReadRemainingMoney(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen)
{
	uchar8 V_ucReturn;
	
	if( C_Meter_Type == C_L_SmartMeter )		/*���طѿر�*/
	{
		V_ucReturn = SF_ReadRemainingMoney_L( V_ulDataCode, pV_ucBuffer, pV_usLen );
	}
	else										/*���ܱ����Զ�̷ѿر�*/
	{
		V_ucReturn = C_IDError;
	}
	
	return V_ucReturn;
}

/***********************************************************************************************************************
����ԭ�ͣ�uchar8 SF_DealEnergyPoint(uchar8 V_ucNature, ulong64 *pV_ullEnergyPulse, uchar8 *pV_ucBuffer, ushort16 *pV_usLen)
����������������������Ϊ��Ӧ�����Ե�����Ҫ��С��λ��
���������V_ucNature���������ԣ�OAD�е����ԣ�����2������4������6;
          V_ullEnergyPulse:��������6λС����
���������pV_usLen�����������ݵĳ��ȣ�
���ز�����C_OK���ɹ���C_NoAccess���޴����ԣ�Ӧ����Ȩ�ޣ�
����λ�ã�������
��    ע������2��2λС����
          ����4��4λС����
          ����6;
************************************************************************************************************************/
uchar8 SF_DealEnergyPoint(uchar8 V_ucNature, ulong64 *pV_ullEnergyPulse, ushort16 *pV_usLen)
{
	if( V_ucNature == 0x02 )					/*����2��2λС��*/
	{
		*pV_usLen = C_EnergyNature2HEXLen;
		
		/*������HEX��ʽ��С��λ��Ϊ2λ*/
		*pV_ullEnergyPulse /= 10000;
		
		if( *pV_ullEnergyPulse > C_ConEnergyToZero_Nature2 )
		{
			*pV_ullEnergyPulse %= C_ConEnergyToZero_Nature2;
		}
		
	}
	else if( V_ucNature == 0x04 )				/*����4��4λС��*/
	{
		*pV_usLen = C_EnergyNature4HEXLen;
		
		/*������HEX��ʽ��С��λ��Ϊ4λ*/
		*pV_ullEnergyPulse /= 100;
		
		if( *pV_ullEnergyPulse > C_ConEnergyToZero_Nature4 )
		{
			*pV_ullEnergyPulse %= C_ConEnergyToZero_Nature4;
		}

		
	}
	else if( V_ucNature == 0x06 )				/*����6,����β��*/
	{
		*pV_usLen = C_EnergyCommPulseLastLen;
		*pV_ullEnergyPulse %= 100;

	}
	else/*�쳣*/
	{
		return C_NoAccess;
	}

    return C_OK;
}


/**************************************************************************************************
����ԭ��: uchar8 SF_ReadEnergy_Single(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen)   				
��������: ��ȡ��ǰ���ܽӿں���													            	
�������: V_ulDataCode:Ϊ��ȡ���ܱ�ʶ��;
		  pV_ucBuffer:ָ���ȡ���ݴ�ŵ��׵�ַ;
          *pV_usLen:��ȡ�������Ļ��泤��;		    	
�������: pV_ucbuffer:��ȡ�ĵ������ݵ��׵�ַ;  	
		  *pV_usLen:��ȡ���ݵĳ��ȣ�
���ز���: C_OK��ʾ��ȡ�ɹ���
		  C_IDError��ʾ���ݱ�ʶ���
		  C_CRCError���ݲ�CRC��
		  C_DataLenError��ʾ���ݳ��ȴ�
		  C_NoAccess��ʾ��Ȩ�ޣ�
		  C_SafeFlagError��ʾ��ȫ��־��
		  C_Error��ʾ��������						
����λ��: ���ܶ�ȡ�ӿں�������																			
��    ע: ��ȡ���������;	
		  ��SF_ReadEnergy��������
		  SF_ReadEnergy_Single���ж� �Ƿ��Ǽ��ϣ�ѭ����ȡ;
		  SF_ReadEnergyֻ�ܵ�����ȡ;	

		  /---------------------------------------------------------------------------/
		  *		*	OAD����2		*	OAD����4			*		OAD����6		  *				
		  *-------------------------------------------------*-------------------------*
		  *	HEX	*	4�ֽڣ�2λС��	*	5�ֽڣ�4λС��		*		1�ֽ�			  *
		  /---------------------------------------------------------------------------/
***************************************************************************************************/
uchar8 SF_ReadEnergy_Single(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen)
{
	uchar8 V_ucReturn, V_ucNum;
	uchar8 V_ucOAD[C_DataCodeLen];
	ulong32 V_ulCodeTemp;
	ulong64 V_ullEnergyPulse, V_ullTemp;
	ushort16 V_usLen = 0;

	/*����ת��Ϊ���ڶ�ȡ�����������ݾݱ�ʶ*/
	
	PF_Ulong32ToBufferX(V_ucOAD, &V_ulDataCode, C_DataCodeLen);	 
	V_ulCodeTemp  = ( V_ulDataCode & 0xFFFF00FF ) | 0x00000400;
	
	if( ( ( V_ucOAD[C_O_DI2] < 0x90 ) && ( ( V_ucOAD[C_O_DI2] & 0x0F ) == 0x00 ) )				/*��ȡ�����ܵ���*/
	 && ( V_ucOAD[C_O_DI0] == 0x01 ) )	  
	{
		V_ucNum = C_MaxRatesNum;
        V_ulCodeTemp += C_GetNextRatesEnergy;
	}
	else if( ( ( V_ulCodeTemp & 0x000F0000 ) != 0x00000000 ) && ( V_ucOAD[C_O_DI0] == 0x00 ) )	/*��ȡ����00��������*/
	{
		V_ucNum = 1;
        V_ulCodeTemp += C_GetNextRatesEnergy;
	}
	else
	{
		V_ucNum = 1;
	}
	
	V_ullEnergyPulse = 0;
	V_ucReturn = SF_ReadTotalEnergy( V_ulCodeTemp, &V_ullEnergyPulse, V_ucNum, C_GetNextRatesEnergy );
	if( V_ucReturn != C_OK)
	{
		return V_ucReturn;	  						/*��ȡ�������ݳ����򷵻���Ӧ�Ĵ�������*/
	}		
	
	/*����ת��ΪHEX��ʽ������С������6λ*/
	SF_Read_PulseConstant(&V_ullTemp);				/*��ȡ�������峣����ulong64��ʽ*/
	V_ullEnergyPulse *= C_EnergyChangeEquivalent;	/*���ﲻ�����*/
	V_ullEnergyPulse /= V_ullTemp;
	
    V_ucReturn = SF_DealEnergyPoint(V_ucOAD[C_O_DI1], &V_ullEnergyPulse, &V_usLen);
    if( V_ucReturn != C_OK)
    {
        return V_ucReturn;                            
    }       


	if( *pV_usLen < V_usLen )
	{
		return C_DataLenError;
	}
	else
	{
		*pV_usLen = V_usLen;
                
		PF_Ulong64ToBuffer8(pV_ucBuffer, &V_ullEnergyPulse, *pV_usLen);
	}
	
	return C_OK;	
}
#if(_DEBUG)  /*�Բ�ʹ�ã�ƴ��ȥ��*/
/*******************************************************************************************************************
����ԭ�ͣ�uchar8 InF_ReadEnergy_Protocol (ulong32 V_ulOAD, uchar8 *pV_ucBuf, ushort8 *pV_ucLen, uchar8 V_ucMethod)
����������ͳһ��ȡ���ܽӿڣ�����BCD��HEX���ݶ�ȡ��
		  �ú�����������OAD�����ݶ�ȡ�����������ݲ��ȡ����������ת��Ϊָ����ʽ��������д��pV_ucBufָ���Ļ��棬
		  ��ʵ��Ӧ��ģ�����ʱĬ�ϲ���698��OAD���øýӿں���
���������V_ulOAD�� ��ǰ�������й��ܼ����ʡ��������޹��ܼ����ʡ�
					����й��ܼ����ʡ�����޹�1��2�ܼ����ʡ�
					�����������й����������޹��ܣ�
					�����ϰ�������2������4������6��	
					ʣ���͸֧���¶��õ��������������õ�����
		  pV_ucBuf ����ȡ���ݻ����׵�ַ��ָ�򻺴���͵�ַ
		 *pV_usLen���������󳤶�
		 V_ ucMethod����Ϊϣ����ȡ�����ݸ�ʽ��C_Format_BCDΪBCD��ʽ��C_Format_HEXΪhex��ʽ��������ʽ������չ��
���������*pV_ucBuf��������ݣ�*pV_usLenΪʵ�ʵ������ݳ���
���ز�����C_OK��ʾ��ȡ�ɹ���C_IDError��ʾ���ݱ�ʶ���C_CRCError���ݲ�CRC��C_DataLenError��ʾ���ݳ��ȴ�
		  C_NoAccess��ʾ��Ȩ�ޣ�C_SafeFlagError��ʾ��ȫ��־��C_Error��ʾ��������
����λ�ã�ͨ�ţ�645/698�����¼���¼�����ᡢ��ȫ�����㡢���ܡ�������ʾ
��    ע��
			/---------------------------------------------------------------------------/
			*		*	OAD����2		*	OAD����4			*		OAD����6		*				
			*---------------------------------------------------*-----------------------*
			*	BCD	*	4�ֽڣ�2λС��	*	8�ֽڣ�4λС��		*		��	        	*	
			*---------------------------------------------------*-----------------------*
			*	HEX	*	4�ֽڣ�2λС��	*	5�ֽڣ�4λС��		*		1�ֽ�			*
			/----------------------------------------------------------------------------/
*******************************************************************************************************************/
uchar8 InF_ReadEnergy_Protocol (ulong32 V_ulOAD, uchar8 *pV_ucBuf, uchar8 *pV_ucLen, uchar8 V_ucMethod)
{
//	uchar8 V_ucDI[C_DataCodeLen], V_uci;
////	uchar8 V_ucBuffer[250];
//	ulong32 V_ulEnergyCode_T;
//	
//	V_ulEnergyCode_T = V_ulOAD;
//	
//#if 0
//	if((V_ulOAD & 0xFF0F0000) != 0)
//	{
//		if((V_ulOAD & 0x00000F00) == 0x400)
//		{
//			V_ulEnergyCode_T = (V_ulEnergyCode_T & 0xFFFFF0FF | 0x200);
//		}
//	}
//#endif
//	
//	/*ʣ����Ĵ���*/
//	if ( /*(V_ulOAD == CChargeBal_BCD)
//	  || (V_ulOAD == COverDraft_BCD)
//	  ||*/ (V_ulOAD == CChargeBal_Hex_Cent)
//      || (V_ulOAD == COverDraft_Hex_Cent)
//	  || (V_ulOAD == CChargeBal_Hex_Full)
//	  || (V_ulOAD == COverDraft_Hex_Full)
//	  || (V_ulOAD == CChargeBal_Hex_Deal)
//	  || (V_ulOAD == COverDraft_Hex_Deal) )	   /*��ȡʣ����/͸֧���*/
//	{
//		V_ucLenTemp = *pV_ucLen;
//		//V_ucTurn = SF_ReadRemainingMoney(V_ulOAD, V_ucBuffer, &V_ucLenTemp);
////		if(V_ucTurn != C_OK)
////		{
////			return V_ucTurn;
////		}
////		else
////		{
////			PF_CopyDataBytes(V_ucBuffer, pV_ucBuf, *pV_ucLen);
////		}
//	}
//	else
//	{
//		/*�ж϶�ȡ��������*/
//		PF_Ulong32ToBufferX(V_ucDI, &V_ulEnergyCode_T, C_DataCodeLen);
//		for(V_uci = 0; V_uci < C_ComDI2Num; V_uci++)
//		{
//			if(C_ComEnergyCode[V_uci] == V_ucDI[C_O_DI2])
//			{
//				break;
//			}
//		}
//		/*��ȡ��ϵ���*/
//		if( (V_uci < C_ComDI2Num) && (V_ucDI[C_O_DI3] != 0x20) )	  /*��ϵ��ܵĴ���*/
//		{
//			V_ucLenTemp = *pV_ucLen;
//			//V_ucTurn = SF_ReadConEnergy_Pulse(V_ulEnergyCode_T, V_ucBuffer, &V_ucLenTemp, V_ucMethod);
////			if(V_ucTurn != C_OK)
////			{
////				return V_ucTurn;
////			}
////			else
////			{
////				if(*pV_ucLen >= V_ucLenTemp)
////				{
////					*pV_ucLen = V_ucLenTemp;
////					PF_CopyDataBytes(V_ucBuffer, pV_ucBuf, *pV_ucLen);
////				}
////				else
////				{
////					return C_DataLenError;
////				}
////			} 
//		}
//		/*��ȡ�¶��ۼ��õ���*/
//		else if(V_ulEnergyCode_T == CM_Com_Ac_Tol_En_0)	    /*�¶ȼ��õ����ļ���*/
//		{
//			V_ucLenTemp = *pV_ucLen;
//			//V_ucTurn = SF_ReadSettlementCycleEnergy(V_ulEnergyCode_T, V_ucBuffer, &V_ucLenTemp);
//			//if(V_ucTurn != C_OK)
//			//{
//			//	return V_ucTurn;
//			//}
//			//else
//			//{
//			//	PF_CopyDataBytes(V_ucBuffer, pV_ucBuf, V_ucLenTemp);
//			//}
//		}
//		/*��ȡ��������*/
//		else
//		{
//			V_ucLenTemp = *pV_ucLen;
//			//V_ucTurn = SF_ReadEnergy(V_ulEnergyCode_T, V_ucBuffer, &V_ucLenTemp, V_ucMethod);
//			//if(V_ucTurn != C_OK)
////			{
////				return V_ucTurn;
////			}
////			else
////			{
////				if(*pV_ucLen >= V_ucLenTemp)
////				{
////					*pV_ucLen = V_ucLenTemp;
////					PF_CopyDataBytes(V_ucBuffer, pV_ucBuf, V_ucLenTemp);
////				}
////				else
////				{
////					return C_DataLenError;
////				}
////			}
//		}
//	}
    return C_OK;
}
#endif
/**************************************************************************************************************************
����ԭ�ͣ�uchar8 SF_ReadTotalEnergy(ulong32 V_ulPulOAD, ulon64 *pV_ullTolEnergy, uchar8 V_ucCalNum, ulong32 V_ulOADRegular )
�������������ܵ���
���������V_ulPulOAD:����1��������OAD��A��������OAD��
          pV_ullTolEnergy:�ܵ��ܵ�ַ��
          V_ucCalNum:��Ҫ�ۼӵĸ�����C_MaxRatesNum��12���ʣ�C_OnePhase:1�ࣻC_ThreePhase:3��;
          V_ulOADRegular:OAD����Ĺ��ɣ�����ѭ����ȡ������;
          	C_GetNextRatesEnergy��0x00000001����ȡ��һ�����ʵ��ܣ�
          	C_GetNextPhaseEnergy: 0x00010000,��ȡ��һ��������ܣ�
���������pV_ullTolEnergy:�ܵ��ܵ�ַ��
���ز�����C_OK���ɹ�; C_Error:��ȡ������ʧ�ܣ�
����λ�ã�����ģ��
��    ע���ܵ���Ϊ����õ���
**************************************************************************************************************************/
uchar8 SF_ReadTotalEnergy(ulong32 V_ulPulOAD, ulong64 *pV_ullTolEnergy, uchar8 V_ucCalNum, ulong32 V_ulOADRegular )
{
	uchar8  V_uci, V_ucReturn = C_Error;
	uchar8  V_ucBuffer[C_EnergyPulseLen] = {0};
    ushort16 V_usLen, V_usDataEncode;	
	ulong64 V_ullEnergyPulse = 0, V_ullTemp = 0;
	
	for(V_uci = 0; V_uci < V_ucCalNum; V_uci++)
	{
		V_usDataEncode = 0;
		V_usLen = C_EnergyPulseLen;
		V_ucReturn = InF_Read_Data(V_ulPulOAD, V_ucBuffer, &V_usLen, &V_usDataEncode);		
		if( V_ucReturn != C_OK )
		{
			return V_ucReturn;
		}
		PF_Buffer8ToUlong64(V_ucBuffer, &V_ullTemp, C_EnergyPulseLen);
		V_ullEnergyPulse += V_ullTemp;
        V_ulPulOAD += V_ulOADRegular;
	}
	
	*pV_ullTolEnergy = V_ullEnergyPulse;
	return V_ucReturn;
}

/*******************************************************************************
����ԭ�ͣ�uchar8 SF_GetEnergy_Type(ulong32 V_ulOAD)
������������ȡ�������ݵ�����
���������V_ulOADΪ��ȡ��OAD
�����������
���ز������������ݵ�����
		  C_En_OADGetTpye_Money:����ࣨʣ���͸֧��
		  C_En_OADGetTpye_Com:	��ϵ�����
		  C_En_OADGetTpye_Month:�¶��õ���
		  C_En_OADGetTpye_StepSettle�����ݽ������
		  C_En_OADGetTpye_Other:��������
����λ�ã������ܡ����ӿ�
��    ע��
*******************************************************************************/
uchar8 SF_GetEnergy_Type(ulong32 V_ulOAD)
{
	uchar8 V_ucEnergyType;
	uchar8 V_ucOAD[C_DataCodeLen];
	uchar8 V_uci;
		
	if( ( V_ulOAD == CChargeBal_Hex_Cent )		/*ʣ���͸֧����Э����ͬ���ݱ�ʶ*/
     || ( V_ulOAD == COverDraft_Hex_Cent ) )
	{
		V_ucEnergyType = C_En_OADGetTpye_Money;
	}
	else if( V_ulOAD == CM_Com_Ac_Tol_En_0 )	/*�¶��õ���*/
	{
		V_ucEnergyType = C_En_OADGetTpye_Month;
	}
	else if( V_ulOAD == CY_Com_Ac_Tol_En_0 )	/*���ݽ����õ���*/
	{
		V_ucEnergyType = C_En_OADGetTpye_StepSettle;
	}	
	else
	{
		PF_Ulong32ToBufferX(V_ucOAD, &V_ulOAD, C_DataCodeLen);
		
		for(V_uci = 0; V_uci < C_ComDI2Num; V_uci++)
		{
			V_ucOAD[C_O_DI2] = V_ucOAD[C_O_DI2] & 0xF0;
			if( C_ComEnergyCode[V_uci] == V_ucOAD[C_O_DI2] )
			{
				break;
			}
		}
		if(V_uci < C_ComDI2Num)					 /*��ϵ���*/
		{
			V_ucEnergyType = C_En_OADGetTpye_Com;
		}
		else
		{
			V_ucEnergyType = C_En_OADGetTpye_Other;
		}	
	}
	
	return V_ucEnergyType;
}

/**********************************************************************************************************
����ԭ��: uchar8 SF_ReadConEnergy_Pulse(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen)  		
��������: ��ȡ��ǰ��ϵ��ܽӿں���
�������: V_ulDataCode:Ϊ��ȡ���ܱ�ʶ��,
          pV_ucBuffer:ָ���ȡ���ݴ�ŵ��׵�ַ,
          *pV_usLen:��󻺴泤�ȣ�	    	
�������: pV_ucbuffer:��Ŷ�ȡ�������ݵ��׵�ַ��
		  *pV_usLen:��ȡ���ݵĳ��ȣ�
���ز���: C_OK��ʾ��ȡ�ɹ���
          C_IDError��ʾ���ݱ�ʶ���
          C_CRCError���ݲ�CRC��
          C_DataLenError��ʾ���ݳ��ȴ�
          C_NoAccess��ʾ��Ȩ�ޣ�
          C_SafeFlagError��ʾ��ȫ��־��
          C_Error��ʾ��������
����λ��: ���ܶ�ȡ�ӿں�������
��    ע: ��SF_ReadConEnergy_Pulse��������
		  SF_ReadConEnergy_Pulse���ж��Ƿ��Ǽ��ϣ�ѭ����ȡ��
		  SF_ReadConEnergy_Pulse_Singleֻ�ܵ�����ȡ��������
*********************************************************************************************************/
uchar8 SF_ReadConEnergy_Pulse(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen)
{
	uchar8  V_ucTimes, V_uci, V_ucReturn;
	ushort16 V_usDataLen = 0, V_usDataOffset = 0;
   
    if( ( V_ulDataCode & 0x000F00FF ) == 0x00000000 ) 		/*���϶�ȡ*/
    {
    	V_ucTimes = C_RatesNumTol;
		V_ulDataCode += C_GetNextRatesEnergy;   			/*���ϣ����ݱ�ʶ������1��ʼ��*/
	}
	else			 /*������ȡ�ܵ��ܡ����ʵ��ܡ�������ܣ�00������01������*/
	{
		V_ucTimes = 1;
	}
    
    for( V_uci = 0; V_uci < V_ucTimes; V_uci++)
    {

        if( *pV_usLen < V_usDataLen )
        {
            return C_DataLenError;
        }
        
		*pV_usLen -= V_usDataLen;
    	V_usDataLen = *pV_usLen;
    	V_ucReturn = SF_ReadConEnergy_Pulse_Single(V_ulDataCode, &pV_ucBuffer[V_usDataOffset], &V_usDataLen);
    	if( V_ucReturn != C_OK)
    	{
    		return V_ucReturn;
    	}
        V_usDataOffset += V_usDataLen;
		V_ulDataCode += C_GetNextRatesEnergy;
	}
	*pV_usLen = V_usDataOffset;
	
	return V_ucReturn;        
}

/**********************************************************************************************************
����ԭ��: uchar8 SF_ReadEnergy(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen) 		
��������: ��ȡ��ǰ���ܽӿں���													           
�������: V_ulDataCode:Ϊ��ȡ���ܱ�ʶ��,
          pV_ucBuffer:ָ���ȡ���ݴ�ŵ��׵�ַ,
          *pV_usLen:��󻺴泤�ȣ�	    	
�������: pV_ucbuffer:��Ŷ�ȡ�������ݵ��׵�ַ��
		  *pV_usLen:��ȡ���ݵĳ��ȣ�
���ز���: C_OK��ʾ��ȡ�ɹ���
          C_IDError��ʾ���ݱ�ʶ���
          C_CRCError���ݲ�CRC��
          C_DataLenError��ʾ���ݳ��ȴ�
          C_NoAccess��ʾ��Ȩ�ޣ�
          C_SafeFlagError��ʾ��ȫ��־��
          C_Error��ʾ��������						
����λ��: ���ܶ�ȡ�ӿں�������																			
��    ע: ��SF_ReadConEnergy_Pulse��������
		  SF_ReadEnergy���ж��Ƿ��Ǽ��ϣ�ѭ����ȡ��	
		  SF_ReadConEnergy_Pulse_Singleֻ�ܵ�����ȡ��������																			                
*********************************************************************************************************/
uchar8 SF_ReadEnergy(ulong32 V_ulDataCode, uchar8 *pV_ucBuffer, ushort16 *pV_usLen)
{
	uchar8  V_ucTimes, V_uci, V_ucReturn;
	ushort16 V_usDataLen = 0, V_usDataOffset = 0;
   
    if( ( V_ulDataCode & 0x000F00FF ) == 0x00000000 ) 		/*���϶�ȡ*/
    {
    	V_ucTimes = C_RatesNumTol;
		V_ulDataCode += C_GetNextRatesEnergy;

	}
	else			 /*������ȡ*/
	{
		V_ucTimes = 1;
	}
    
    for( V_uci = 0; V_uci < V_ucTimes; V_uci++)
    {
    	if( *pV_usLen < V_usDataLen )
    	{
    		return C_DataLenError;
    	}
		
    	*pV_usLen -= V_usDataLen;
    	V_usDataLen = *pV_usLen;
    	V_ucReturn = SF_ReadEnergy_Single(V_ulDataCode, &pV_ucBuffer[V_usDataOffset], &V_usDataLen);
    	if( V_ucReturn != C_OK)
    	{
    		return V_ucReturn;
    	}
        V_usDataOffset += V_usDataLen;
		V_ulDataCode += C_GetNextRatesEnergy;
	}
	
	*pV_usLen = V_usDataOffset;
	return V_ucReturn;        
}

/**********************************************************************************************************************************
����ԭ�ͣ�uchar8 InF_Get_EnergyModule(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, ushort16 *pV_usDataEncode)
���������������ܡ����ӿ�
���������V_ulOAD:��Ҫ��ȡ��OAD��
          pV_ucDataBuf:��ȡ���ݵĻ�����׵�ַ
         *pV_usDataLen:��ȡ���ݵĻ������󳤶ȣ�
���������pV_ucDataBuf:��ȡ���ݵĻ�����׵�ַ
		 *pV_usDataLen:��ȡ����ʵ�ʳ��ȣ�
         *pV_usDataEncode:�����ڲ����룻
���ز�����C_OK,��ȡ�ɹ�;��������;
����λ�ã���������
��    ע��/---------------------------------------------------------------------------/
            ����ģ������ṩ�����ݸ�ʽ
          /---------------------------------------------------------------------------/
          /-���----------------------------------------------------------------------/
          * 4�ֽ�HEX��2λС��,0.01Ԫ
          * CChargeBal_Hex_Cent 0x202C0201
          * COverDraft_Hex_Cent 0x202D0200
          /---------------------------------------------------------------------------/
          /-�¶��õ��������ݽ����õ���------------------------------------------------/
          * 4�ֽ�HEX��2λС����0.01Ԫ
          /-��ǰ����------------------------------------------------------------------/
          * ����2,4�ֽ�HEX��2λС��
          * ����4,5�ֽ�HEX��4λС��
          * ����6,1�ֽ�HEX
          /---------------------------------------------------------------------------/
************************************************************************************************************************************/
uchar8 InF_Get_EnergyModule(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, ushort16 *pV_usDataEncode)
{
	uchar8 V_ucEnergyType;
	uchar8 V_ucReturn;
	
	V_ucEnergyType = SF_GetEnergy_Type( V_ulOAD );
	
	if( V_ucEnergyType == C_En_OADGetTpye_Money )			/*���*/
	{
		V_ucReturn = SF_ReadRemainingMoney( V_ulOAD, pV_ucDataBuf, pV_usDataLen );
		
	}
	else if( V_ucEnergyType == C_En_OADGetTpye_Month )		/*�¶��õ���*/
	{		
		V_ucReturn = SF_ReadMonthEnergy( V_ulOAD, pV_ucDataBuf, pV_usDataLen );	
		
	}
	else if( V_ucEnergyType == C_En_OADGetTpye_StepSettle )	/*���ݽ����õ���*/
	{
		V_ucReturn = SF_ReadSettlementCycleEnergy( V_ulOAD, pV_ucDataBuf, pV_usDataLen );
		
	}	
	else if( V_ucEnergyType == C_En_OADGetTpye_Com )		/*��ϵ���*/
	{
		V_ucReturn = SF_ReadConEnergy_Pulse( V_ulOAD, pV_ucDataBuf, pV_usDataLen );
		
	}
	else if( V_ucEnergyType == C_En_OADGetTpye_Other )		/*��������*/
	{
		V_ucReturn = SF_ReadEnergy( V_ulOAD,  pV_ucDataBuf, pV_usDataLen );
		
	}
	else
	{
		V_ucReturn = C_Error;
		
	}
	
	return V_ucReturn;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_SetOverDraft_Meter_Work_State(uchar8 V_ucState, uchar8 V_ucSafeFlag)
����������д�������״̬��1��͸֧״̬λ 
���������V_ucState:C_SetOverDraft:��λ��C_ClrOverDraft:��λ��
          V_ucSafeFlag:д���ݲ�İ�ȫ��־��SV_ucEnergySafeFlag�����ܰ�ȫ��־��C_W_SafeFlag��д��ȫ
�����������  
���ز�����C_OK,д�ɹ���C_Error��дʧ�ܣ� 
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_SetOverDraft_Meter_Work_State(uchar8 V_ucState, uchar8 V_ucSafeFlag)
{
	uchar8   V_ucBuffer[2];
	ushort16 V_usLen, V_usDataEncode;
	
	V_usDataEncode = 0;
	V_usLen = CLMeter_Work_State1;
	if( InF_Read_Data(CMeter_Work_State1, V_ucBuffer, &V_usLen, &V_usDataEncode) != C_OK )
	{
		return C_Error;
	}
	
	if(V_ucState == C_SetOverDraft)
	{
		V_ucBuffer[1] |= C_SetOverDraft;	/*͸֧״̬��λ����1*/
	}
	else
	{
		V_ucBuffer[1] &= C_ClrOverDraft;	/*͸֧״̬��λ����0*/
	}
	
	if( InF_Write_Data(C_Msg_EnergyMetering, CMeter_Work_State1, V_ucBuffer, CLMeter_Work_State1, V_ucSafeFlag ) != C_OK )
	{
		return C_Error;
	}
	
	return C_OK;
}

/*******************************************************************************
����ԭ�ͣ�void SF_EnergyInit_R(void)
�����������ϵ���ܾ�̬������ʼ��  
����������� 
�����������  
���ز������� 
����λ�ã������ϵ��ʼ��ʱ����
��    ע���Ǳ��ر��ϵ��ʼ��ֻ��Ҫ����ȫ��־���㼴��	
*******************************************************************************/
void SF_EnergyInit_R(void)
{
    SV_ucEnergySafeFlag = 0;	/*��ȫ��־����*/
	
	SF_SetOverDraft_Meter_Work_State( C_ClrOverDraft, C_W_SafeFlag );
	
}

/*******************************************************************************
����ԭ�ͣ�void SF_EnergyInit_L(void)
�����������ϵ���ܾ�̬������ʼ�� 
�����������
�����������
���ز�������
����λ�ã������ϵ��ʼ��ʱ����	
��    ע�����ر��ϵ��ʼ������ȫ��־���㣬ͬʱ��ȡʣ�����͸֧����ж��Ƿ���Ҫ���͡�͸֧����ʾ����ʾ
*******************************************************************************/
void SF_EnergyInit_L(void)
{
	ulong64 V_ullRemainingMoney, V_ullOverdraftMoney;
	
    SV_ucEnergySafeFlag = 0;		/*��ȫ��־����*/
	
	/******************��ȡ���ݲ�ʣ���͸֧���************************************/	
	if( SF_Get_RMoney_DMoney(&V_ullRemainingMoney, &V_ullOverdraftMoney) != C_OK )
	{
		return;
	}
	
	/*********************�жϱ�����Ԥ��բ������͸֧��������բ״̬***********************/
	SF_JudgeWarningStatus(V_ullRemainingMoney, V_ullRemainingMoney, 0, V_ullOverdraftMoney, C_RenewDerict);	/*����۷�ǰ͸֧���д��0����֤͸֧��Ϊ0��ʱ�����͸֧����*/

}

/********************************************************************************************
����ԭ�ͣ�void InF_EnergyInit(void)
�����������ϵ���ܾ�̬������ʼ�� 
�����������
�����������
���ز�������
����λ�ã������ϵ��ʼ��ʱ����
��    ע�������ϵ��ʼ�����ã�����Ҫ���ֱ��طѿر����Զ�̷ѿر����ܱ������ڲ�����������
**********************************************************************************************/
void InF_EnergyInit(void)
{
	if( C_Meter_Type == C_L_SmartMeter )	/*���طѿص��ܱ�*/
	{
		SF_EnergyInit_L( );
	}
	else
	{
		SF_EnergyInit_R( );
	}
}

/********************************************************************************************************
����ԭ�ͣ�uchar8 SF_ReadEnergy_Settlement_L(void)
�������������ڽ���ģ�飬���ݽ����õ���������
�����������
�����������
���ز�����C_OK��ʾ��ȡ�ɹ���C_IDError��ʾ���ݱ�ʶ���C_CRCError���ݲ�CRC��C_DataLenError��ʾ���ݳ��ȴ�
		  C_NoAccess��ʾ��Ȩ�ޣ�C_SafeFlagError��ʾ��ȫ��־��C_Error��ʾ��������
����λ�ã�����ģ����н������ڵ��ܽ���ʱ����
��    ע��
*******************************************************************************************************/
uchar8 SF_ReadEnergy_Settlement_L(void)
{
	ulong64  V_ullEnergy, V_ullTemp;
	uchar8   V_ucTurn, V_ucBuffer[C_EnergyPulseLen], V_ucSageFlay = 0;
	ushort16 V_usLen, V_usDataEncode;
			
	V_ucSageFlay |= C_W_SafeFlag_1;
	
	/*******************��ȡ���ݲ���ݽ����õ���������********************************/
	V_ullEnergy = 0;
	V_usDataEncode = 0;
	V_usLen = C_EnergyPulseLen;
	V_ucTurn = InF_Read_Data(CY_Com_Ac_Tol_En_0, V_ucBuffer, &V_usLen, &V_usDataEncode);
	if( V_ucTurn != C_OK )
	{
		return V_ucTurn;
	}
	PF_Buffer8ToUlong64(V_ucBuffer, &V_ullEnergy, C_EnergyPulseLen);
	
	V_ucSageFlay |= C_W_SafeFlag_2;

	/********************����ת�棬����0.01�ȣ�β����д���ݲ�*************************/
	SF_Read_PulseConstant(&V_ullTemp);							/*��ȡ�������峣��ulong64��ʽ*/
	
	V_ullTemp /= C_EnergyChangeEquivalent_Hundred;
	V_ullEnergy = V_ullEnergy % V_ullTemp;						/*����0.01�ȵ���������д���ݲ�*/
	PF_Ulong64ToBuffer8(V_ucBuffer, &V_ullEnergy, C_EnergyPulseLen);
	
	V_ucSageFlay |= C_W_SafeFlag_3;
	
	V_ucTurn = InF_Write_Data(C_Msg_EnergyMetering, CY_Com_Ac_Tol_En_0, V_ucBuffer, C_EnergyPulseLen, V_ucSageFlay);	/*����0.01�ȵ�����������д���ݲ�*/
    return V_ucTurn;
}

/********************************************************************************************************
����ԭ�ͣ�uchar8 InF_ReadEnergy_Settlement(void)
�������������ڽ���ģ�飬���ݽ����õ���������
�����������
�����������
���ز�����C_OK��ʾ��ȡ�ɹ���C_IDError��ʾ���ݱ�ʶ���C_CRCError���ݲ�CRC��C_DataLenError��ʾ���ݳ��ȴ�
          C_NoAccess��ʾ��Ȩ�ޣ�C_SafeFlagError��ʾ��ȫ��־��C_Error��ʾ��������
����λ�ã�����ģ����н��ݽ���ʱ����
��    ע������ģ�����ʱ��ȡ������ܵ��ã��������ֱ��ͣ������ڲ����ݲ�ͬ���ͽ��в�ͬ�Ĵ���
          ֻ�б��ر���еĽ��ݽ������ʹ�ã�Զ�̱���ݽ�����ܲ���Ҫ���ݽ���
*******************************************************************************************************/
uchar8 InF_ReadEnergy_Settlement(void)
{
	uchar8 V_ucReturn;
	
	if( C_Meter_Type == C_L_SmartMeter )	/*���طѿر�*/
	{
		V_ucReturn = SF_ReadEnergy_Settlement_L( );
        SF_UpdateCurrentPrice();  			/*���ر����������жϵ�ǰ���ݡ����ʡ���ǰ�������*/
	}
	else									/*���ܱ����Զ�̷ѿص��ܱ�����Ҫ���ݽ���*/
	{
		V_ucReturn = C_NoAccess;
	}
	return V_ucReturn;
}

/********************************************************************************************************************
����ԭ�ͣ�uchar8 InF_MoneyToPurchase(ulong32 V_ulBuyMoney, uchar8 V_ucPurchaseFlag, uchar8 V_ucSafeFlag)
��������������ֵ��Զ�̳�ֵ��Ǯ����ʼ������ӿں�����
		  ���ڹ���ǰ��ʣ�����뱨����͸֧���ޡ���բ�������ϵ�жϣ����������ʣ���͸֧��д���ݲ�
���������V_ulBuyMoneyΪ��ֵ���,�����ǵ�λΪ�ֵ�hex��ʽ��
		  V_ucPurchaseFlag,�����־��C_Money_Purchase ��ֵ��C_Money_Init Ǯ����ʼ����
		  V_ucSafeFlag:Ϊ��ȫ��־ 
�����������
���ز�����C_OK��ʾ��ȡ�ɹ���C_IDError��ʾ���ݱ�ʶ���C_CRCError���ݲ�CRC��C_DataLenError��ʾ���ݳ��ȴ�
          C_NoAccess��ʾ��Ȩ�ޣ�C_SafeFlagError��ʾ��ȫ��־��C_Error��ʾ��������
����λ�ã�ͨ�š�������ģ���ֵ��Ǯ����ʼ��ʱ����	
��    ע��
********************************************************************************************************************/
uchar8 InF_MoneyToPurchase(ulong32 V_ulBuyMoney, uchar8 V_ucPurchaseFlag, uchar8 V_ucSafeFlag)
{
	ulong64 V_ullRemainingMoney, V_ullRemainingMoney_L, V_ullOverdraftMoney, V_ullOverdraftMoney_L, V_ullBuyMoney, V_ullRellyOnThreshold;
	ulong32 V_ulTemp;
	uchar8  V_ucTurn, V_ucBuffer[6];
	ulong64 V_ullOverDraftThresdHold;
	ushort16 V_usLen, V_usDataEncode;

	SF_SetMoneyToPurchaseFlag( C_MoneyToPurchase );	/*���Ƚ������־��1*/
	
	/***********************������Ĵ���********************************/
	V_ullBuyMoney = V_ulBuyMoney;
	V_ullBuyMoney *= C_MoneyChangeEquivalent;			/*ת��Ϊ�����ݲ���ͬ��ʽ,0.0001�ֵ�hex��ʽ*/
	
	/******************��ȡ���ݲ�ʣ���͸֧���***********************/
	V_ucTurn = SF_Get_RMoney_DMoney(&V_ullRemainingMoney, &V_ullOverdraftMoney); 
	if(V_ucTurn != C_OK)
	{
		return V_ucTurn;
	}
	
	/******************���㹺����ʣ���͸֧���**********************************/
	if( V_ullRemainingMoney > 0 )
	{
		V_ullRemainingMoney_L = V_ullRemainingMoney + V_ullBuyMoney;			/*ʣ�������ԭ��ʣ����+������*/
		V_ullOverdraftMoney_L = 0;												/*͸֧������0*/
	}
	else	/*ʣ����Ϊ0*/
	{
		if(V_ullOverdraftMoney > V_ullBuyMoney)									/*͸֧�����ڹ�����*/
		{
			V_ullOverdraftMoney_L = V_ullOverdraftMoney - V_ullBuyMoney;
			V_ullRemainingMoney_L = 0;
		}
		else
		{
			V_ullRemainingMoney_L = V_ullBuyMoney - V_ullOverdraftMoney;
			V_ullOverdraftMoney_L = 0;
		}
	}
	
	/*���ϣ����V_ullRemainingMoney_L(��ֵ���ʣ����)��V_ullOverdraftMoney_L����ֵ���͸֧��*/
	/***********************������Ԥ��բ������͸֧��������բ״̬�ж�*******************************/
	SF_JudgeWarningStatus(V_ullRemainingMoney, V_ullRemainingMoney_L, V_ullOverdraftMoney, V_ullOverdraftMoney_L, C_RenewDerict);

	/*****************************���͹���ɹ���־���̵���ģ��*************************************/
	V_ucBuffer[0] = Pt_RelayStateFlag;
	V_ucBuffer[1] = C_PurchaseOK;
	SF_SendMessege(C_Msg_Deal_RelayStatus, V_ucBuffer, ( Pt_RelayStateFlag_Len + 1 ) );	/*���͹���ɹ���Ϣ*/

	/******************��ȡ��բ��������ֵ��ת��Ϊ�����ݲ�洢��ʽ��ͬ����************************/
	if( V_ucPurchaseFlag == C_Money_Purchase )
	{
		V_usDataEncode = 0;
		V_usLen = CLClose_Relay_Money;
		V_ucTurn = InF_Read_Data(CClose_Relay_Money, V_ucBuffer, &V_usLen, &V_usDataEncode);
		if( V_ucTurn != C_OK )		/*���ݲ��ȡ��������ȷĬ������Ϊ0*/
		{
			memset(V_ucBuffer, 0x00, CLClose_Relay_Money);
		}
		PF_BufferXToUlong32(V_ucBuffer, &V_ulTemp, CLClose_Relay_Money);
		V_ullRellyOnThreshold = V_ulTemp;
		V_ullRellyOnThreshold *= C_MoneyChangeEquivalent;
		
		/******************�ж��Ƿ���Ҫ����բ������Ϣ***************************/
		if(V_ullRemainingMoney_L > V_ullRellyOnThreshold)	/*�����ʣ������ں�բ��������ͺ�բ������Ϣ���̵���ģ��*/
		{
			V_ucBuffer[0] = Pt_RelayStateFlag;
			V_ucBuffer[1] = C_Relay_Close_Direct;
			SF_SendMessege(C_Msg_Deal_RelayStatus, V_ucBuffer, (Pt_RelayStateFlag_Len + 1) );		/*���ͺ�բ������Ϣ*/
		}
	}
	else if( V_ucPurchaseFlag == C_Money_Init )
	{
		/*****************͸֧�������,��λ0.01Ԫ��BCD��ʽ����Ҫת��Ϊ0.01Ԫ��hex��ʽ******************/
		V_usDataEncode = 0;
		V_usLen = CLOverDraft_Money;
		if( InF_Read_Data(COverDraft_Money, V_ucBuffer, &V_usLen, &V_usDataEncode ) != C_OK )			/*���ݲ��ȡ��������ȷĬ������Ϊ0*/
		{
			memset(V_ucBuffer, 0x00, CLOverDraft_Money);
		}
		PF_BufferXToUlong32(V_ucBuffer, &V_ulTemp, CLOverDraft_Money);
		V_ullOverDraftThresdHold = V_ulTemp;
		
		/******************�ж��Ƿ���Ҫ��������բ��Ϣ***************************/
		if ( ( V_ullOverDraftThresdHold != 0 )								/*͸֧���޲���0*/
		  || ( ( V_ullRemainingMoney_L / C_MoneyChangeEquivalent ) > 0 ) )	/*ʣ�������0*/
		{
			V_ucBuffer[0] = Pt_RelayStateFlag;
			V_ucBuffer[1] = C_Relay_Close_Direct_Init;
			SF_SendMessege(C_Msg_Deal_RelayStatus, V_ucBuffer, ( Pt_RelayStateFlag_Len + 1 ) );		/*����������բ��Ϣ*/
		}

	}
	else
	{
		return C_Error;
	}
	/***********************��ʣ���͸֧��д���ݲ�**********************************/
	PF_Ulong64ToBuffer8(V_ucBuffer, &V_ullRemainingMoney_L, C_EnergyPulseLen);	 /*ʣ����*/
	V_ucTurn = InF_Write_Data(C_Msg_EnergyMetering,CChargeBal_Hex_Full, V_ucBuffer, CLChargeBal_Hex_Full, V_ucSafeFlag);
	if(V_ucTurn != C_OK)
	{
		return V_ucTurn;
	}

	PF_Ulong64ToBuffer8(V_ucBuffer, &V_ullOverdraftMoney_L, C_EnergyPulseLen);	 /*͸֧���*/
	V_ucTurn = InF_Write_Data(C_Msg_EnergyMetering, COverDraft_Hex_Full, V_ucBuffer, CLOverDraft_Hex_Full, V_ucSafeFlag);
	if(V_ucTurn != C_OK)
	{
		return V_ucTurn;
	}

	/***********************���ۼƹ�����д���ݲ�**********************************/
	V_usDataEncode = 0;
	V_usLen = CLBuyCurr_TMoney;
	V_ucTurn = InF_Read_Data( CBuyCurr_TMoney, V_ucBuffer, &V_usLen, &V_usDataEncode );			/*�ۼƹ�����*/
	if( V_ucTurn != C_OK )
	{
		return V_ucTurn;
	}
	PF_BufferXToUlong32(V_ucBuffer, &V_ulTemp, CLBuyCurr_TMoney);
	
	if( V_ucPurchaseFlag == C_Money_Init )	/*Ǯ����ʼ���ۼƹ�����Ϊ0*/
	{
		V_ulTemp =  0;
	}
	
	V_ulTemp += V_ulBuyMoney;
	
	PF_Ulong32ToBufferX(V_ucBuffer, &V_ulTemp, CLBuyCurr_TMoney);
	V_ucTurn = InF_Write_Data(C_Msg_EnergyMetering, CBuyCurr_TMoney, V_ucBuffer, CLBuyCurr_TMoney, V_ucSafeFlag);
	if( V_ucTurn != C_OK )
	{
		return V_ucTurn;
	}
    return C_OK;
}

/*******************************************************************************
����ԭ�ͣ�uchar8 SF_Judge_CurrentStep_Type(uchar8 *pV_ucBuffer)
�����������жϵ�ǰ�����Ľ���״̬�Ƿ���Ч	
���������pV_ucBufferָ���һ������ݲ����׵�ַ   
�����������
���ز�����C_ValidStep��Ч���ݣ�C_InValidStep��Ч����
����λ�ã����ܴ�����Ϣ���ã���0.01�Ƚ�λʱ����
��    ע�����ݽ����գ�����ʱ�������ڵ��ֽڣ�ʱ�ڸ��ֽ�
*******************************************************************************/
uchar8 SF_Judge_CurrentStep_Type(uchar8 *pV_ucBuffer)
{
	uchar8 V_uci;
	uchar8 V_ucBuffer[C_StepSettlementLen];

	for( V_uci = 0; V_uci < C_StepSettlementNum; V_uci++)
	{
		PF_OneDataReversed ( &pV_ucBuffer[V_uci * C_StepSettlementLen], V_ucBuffer, C_StepSettlementLen );
		if( PF_DataTimeActive_698( V_ucBuffer, C_DT_Start_hh, C_StepSettlementLen ) == C_OK)	/*ѭ���ж�4���������Ƿ���Ч��ֻҪ��1����Ч��ִ�������*/
		{
			return C_ValidStep;
		}
	}
	
	/*�����һ���ݽ������н��ա�ʱ��Ч������Ϊ99��FF�����Դ�ÿ�¸���ʱִ�н��ݽ���*/
	if( ( pV_ucBuffer[C_FirstStepSettle_MonthOffset] == 0x63 )	
	 || ( pV_ucBuffer[C_FirstStepSettle_MonthOffset] == 0xFF ) )
	{
		PF_OneDataReversed ( &pV_ucBuffer[C_FirstStepSettle_DayOffset], V_ucBuffer, ( C_StepSettlementLen - 1 ) );
		if( PF_DataTimeActive_698(V_ucBuffer, C_DT_Start_hh, 2) == C_OK )		/*ѭ���ж�4���������Ƿ���Ч��ֻҪ��1����Ч��ִ���½���*/
		{
			return C_ValidStep;
		}
	}
    return C_InValidStep;
}

/********************************************************************************************************************************
����ԭ�ͣ�void SF_Judge_CurrentStep(ulong32 V_ulEnergy_F, ulong32 *pV_ulEnergyPrice, uchar8 *pV_ucStepPara, uchar8 V_ucCurStepType)
�����������жϵ�ǰ�����Ľ��ݺţ����ݺŸı����㵱ǰ���ݵ�۷�д���ݲ�
���������V_ulEnergy_F����ǰ���ܣ�
          pV_ulEnergyPrice����ǰ���ݵ�۴�ŵ�ַ��
          pV_ucStepPara�����ݱ������ַ��
          V_ucCurStepType��C_ValidStep ��Ч���ݣ�C_InValidStep����Ч���ݣ�
���������pV_ulEnergyPrice�����ص�ǰ���ݵ�ۣ�
���ز�������
����λ�ã�����500ms��ʱ������,�е��ܴ���ģ�����
��    ע��V_ulEnergy_F = V_ulEnergyʱ�������жϵ�ǰ��ۡ����ݵ�ۣ�����д���ݲ㣬�����ݴ��RAM��ʵʱˢ�� 
********************************************************************************************************************************/
void SF_Judge_CurrentStep(ulong32 V_ulEnergy_F, ulong32 *pV_ulEnergyPrice, uchar8 *pV_ucStepPara, uchar8 V_ucCurStepType)
{
	ulong32  V_ulStepPara;
	ulong32  V_ulStepPrice;
	uchar8   V_ucBuffer[20], V_uci, V_ucLastStep, V_ucStepNum;
	ushort16 V_usLen, V_usDataEncode;
	
	memset(&V_ucBuffer[0], 0xFF, 20);
	
	/******************���ݲ���*******************/
	if ( ( PF_Is_Buf_AllFixedData(pV_ucStepPara, 0x00, C_MaxStepEnergyLen) == C_OK )	/* ��ǰ������Ч,ȫΪ0�����ﲻ������Ч���ݵ���� */
	  || ( V_ucCurStepType == C_InValidStep ) )											/* �����ǽ��ݱ������Ч����� */
	{
        V_ucStepNum = 0;	/*���ݺ�����*/
		InF_Write_Data(C_Msg_EnergyMetering, CCurr_Step_No, &V_ucStepNum, CLCurr_Step_No, C_W_SafeFlag);
		
		V_ucBuffer[0] = Pt_DisplayStatus;
		V_ucBuffer[1] = C_LSign | C_NotDisplay;
		V_ucBuffer[2] = 0xFF;
		V_ucBuffer[3] = 0xFF;
		V_uci = Pt_DisplayStatus_Len + 1;

		SF_SendMessege(C_Msg_Display, V_ucBuffer, V_uci);	/*���͵�ǰ���ݺ���Ϣ����ʾ*/
		
		/*********���ݵ������*********/
		memset(&V_ucBuffer[0], 0x00, 4);
	}
	else
	{
		V_ucLastStep = 0;
		V_usDataEncode = 0;
		V_usLen  = CLStep_Num;
		if( InF_Read_Data(CStep_Num, &V_ucBuffer[0], &V_usLen, &V_usDataEncode) == C_OK )
		{
			if( V_ucBuffer[0] > C_MaxStepNum )
			{
				V_ucBuffer[0] = C_MaxStepNum;
			}
		}
		else
		{
			V_ucBuffer[0] = C_MaxStepNum;
		}
		
		for( V_uci = 0; V_uci < V_ucBuffer[0]; V_uci++)
		{
			PF_BufferXToUlong32( &pV_ucStepPara[V_uci * CLCurr_Ladder_Price], &V_ulStepPara, CLCurr_Ladder_Price );
			if( V_ulEnergy_F >= V_ulStepPara )					    /* ˵�������ۼ�ǰ�������ڸý��� */
			{
				V_ucLastStep = V_uci + 1;
			}
			else
			{
				break;
			}
			
			/************ �ж���һ������ֵ�Ƿ���ڵ�ǰ�жϵĽ���ֵ����������ֱ���˳� **************/
			if( PF_Campare_Data( &pV_ucStepPara[(V_uci + 1) * CLCurr_Ladder_Price ], &pV_ucStepPara[V_uci * CLCurr_Ladder_Price], CLCurr_Ladder_Price) != C_GreaterThan )
			{
				break;
			}
		}
		
		V_ucStepNum = V_ucLastStep + 1;						/* ��ʵ����Ҫ��ʾ�Ľ��ݺţ���1 */
        InF_Write_Data(C_Msg_EnergyMetering, CCurr_Step_No, &V_ucStepNum, CLCurr_Step_No, C_W_SafeFlag);
		
		V_ucBuffer[0] = Pt_DisplayStatus;
		V_ucBuffer[1] = C_LSign | C_AlwaysDisplay;
		V_ucBuffer[2] = 0xFF;
		V_ucBuffer[3] = 0xFF;
		V_uci = Pt_DisplayStatus_Len + 1;
		SF_SendMessege(C_Msg_Display, V_ucBuffer, V_uci); 		/*���͵�ǰ���ݺ���Ϣ����ʾ*/
		
		/********************����ǰ���ݵ�۷�д���ݲ�********************************/
		PF_CopyDataBytes( &pV_ucStepPara[C_StepChargeStartAddr + V_ucLastStep * CLCurr_Ladder_Price], V_ucBuffer, CLCurr_Ladder_Price);
	}
	
	InF_Write_Data(C_Msg_EnergyMetering, CCurr_Ladder_Price, V_ucBuffer, CLCurr_Ladder_Price, C_W_SafeFlag);
	
	PF_BufferXToUlong32( &V_ucBuffer[0], &V_ulStepPrice, CLCurr_Ladder_Price );		/* ���ݵ�۷��� */
	*pV_ulEnergyPrice = V_ulStepPrice;
	
	return;
}

/****************************************************************************************************************************
����ԭ�ͣ�void SF_GetWarningPara(ulong64 *pV_ullWarningMoney1, ulong64 *pV_ullWarningMoney2, ulong64 *pV_ullOverDraftThresdHold)
������������ȡ�������1���������2��͸֧���ޣ���������ת��Ϊ�����ݲ�����ͬ�ĸ�ʽ����0.0001�ֵĸ�ʽ
���������pV_ullWarningMoney1��ת���󱨾����1��ŵ�ַ��
          pV_ullWarningMoney2��ת���󱨾����2��ŵ�ַ��
		  pV_ullOverDraftThresdHold��ת����͸֧���޴�ŵ�ַ	��
���������*pV_ullWarningMoney1Ϊ�������1����ʽΪ��λ�Ƿֵ�hex��ʽ��
		  *pV_ullWarningMoney2Ϊ�������2����ʽΪ��λ�Ƿֵ�hex��ʽ��
		  *pV_ullOverDraftThresdHoldΪ͸֧���ޣ���ʽΪ��λ�Ƿֵ�hex��ʽ��
���ز�������	
����λ�ã����ر��жϵ�ǰ����״̬������բ״̬ʱ���ã��ϵ��ʼ�������硢�˷ѡ���ѿۼ������	
��    ע��
****************************************************************************************************************************/
void SF_GetWarningPara(ulong64 *pV_ullWarningMoney1, ulong64 *pV_ullWarningMoney2, ulong64 *pV_ullOverDraftThresdHold)
{
	uchar8   V_ucBuffer[CLAlam1_Money], V_ucReturn;
	ushort16 V_usLen, V_usDataEncode;
	
	/***************** �������1,��λ0.01Ԫhex��ʽ ********************/
	V_usDataEncode = 0;
	V_usLen = CLAlam1_Money;
	V_ucReturn = InF_Read_Data(CAlam1_Money, V_ucBuffer, &V_usLen, &V_usDataEncode);
	if( V_ucReturn != C_OK )		/* ���ݲ��ȡ��������ȷĬ������Ϊ0 */
	{
		*pV_ullWarningMoney1 = 0;
	}
	else
	{
		PF_Buffer8ToUlong64(V_ucBuffer, pV_ullWarningMoney1, CLAlam1_Money);
	}
	
	/***************** �������2,��λ0.01Ԫhex��ʽ ********************/
	V_usDataEncode = 0;
	V_usLen = CLAlam2_Money;
	V_ucReturn = InF_Read_Data(CAlam2_Money, V_ucBuffer, &V_usLen, &V_usDataEncode);
	if( V_ucReturn != C_OK )		/* ���ݲ��ȡ��������ȷĬ������Ϊ0 */
	{
		*pV_ullWarningMoney2 = 0;
	}
	else
	{
		PF_Buffer8ToUlong64(V_ucBuffer, pV_ullWarningMoney2, CLAlam2_Money);
	}
	
	/***************** ͸֧�������,��λ0.01Ԫhex��ʽ *****************/
	V_usDataEncode = 0;
	V_usLen = CLOverDraft_Money;
	V_ucReturn = InF_Read_Data(COverDraft_Money, V_ucBuffer, &V_usLen, &V_usDataEncode);
	if( V_ucReturn != C_OK )		/* ���ݲ��ȡ��������ȷĬ������Ϊ0 */
	{
		*pV_ullOverDraftThresdHold = 0;
	}
	else
	{
		PF_Buffer8ToUlong64(V_ucBuffer, pV_ullOverDraftThresdHold, CLOverDraft_Money);
	}
}

/*******************************************************************************
����ԭ�ͣ�void SF_JudgeWarningStatus(ulong64 V_ullRemainMoney, ulong64 V_ullRemainMoney_New, ulong64 V_ullOverDraftMoney, ulong64 V_ullOverDraftMoney_New, uchar8 V_ucRenewFlay)
�����������ж��Ƿ���Ҫ������Ԥ��բ������������բ����ǰ͸֧״̬��������Ϣ����Ӧģ��
���������V_ullRemainMoney���۷�ǰ��ʣ���
         V_ullRemainMoney_New���۷Ѻ��ʣ���
         V_ullOverDraftMoney���۷�ǰ��͸֧��						
		 V_ullOverDraftMoney_New���۷Ѻ��͸֧��						
		 V_ucRenewFlay���Ƿ�ֱ�Ӹ��±�־��C_RenewDerict��ֱ�Ӹ��£�C_RenewRederict���ж�״̬�仯���£�	
�����������
���ز�������
����λ�ã����ر��жϵ�ǰ����״̬����բ״̬ʱ���ã��ϵ��ʼ�������硢�˷ѡ���ѿۼ������
��    ע��1��ע�⣬����ʱ�����жϱ���1��2���Ƿ񷢺�բ��Ϣ�ڵ��ñ������ĵط�ʵ�֡�
          2�����н��ĵ�λΪ0.000001Ԫ��hex��ʽ
*******************************************************************************/
void SF_JudgeWarningStatus(ulong64 V_ullRemainMoney, ulong64 V_ullRemainMoney_New, ulong64 V_ullOverDraftMoney, ulong64 V_ullOverDraftMoney_New, uchar8 V_ucRenewFlay)
{
	ulong64 V_ullWarningMoney1, V_ullWarningMoney2, V_ullOverDraftThresdHold;
    ulong64 V_ullRemainMoney_Cent, V_ullRemainMoney_New_Cent;   /*�Է�Ϊ��λ�Ŀ۷�ǰ���ʣ����*/
    ulong64 V_ullOverDraftMoney_New_Cent;  						/*�Է�Ϊ��λ�Ŀ۷�ǰ���͸֧���*/
	uchar8  V_ucBuffer[20], V_ucWarningStaus;
	
	/* ��ȡ���ݲ㱨�����1��2��͸֧���� */
	SF_GetWarningPara(&V_ullWarningMoney1, &V_ullWarningMoney2, &V_ullOverDraftThresdHold);
	
	/* ��������Ϣ��־�ֽڣ���ʼ��Ϊ0��������Ϣ */
	V_ucWarningStaus = C_NoMessage;
	
	/* ��ʣ���͸֧���ת��Ϊ�Է�Ϊ��λ��hex��ʽ */
    V_ullRemainMoney_Cent = V_ullRemainMoney / C_MoneyChangeEquivalent;
    V_ullRemainMoney_New_Cent = V_ullRemainMoney_New / C_MoneyChangeEquivalent;
    V_ullOverDraftMoney_New_Cent = V_ullOverDraftMoney_New / C_MoneyChangeEquivalent;
	
	/*********************************************************************************************/
	/************************* �ж��Ƿ���Ҫ���� ***************************/
	/* �����V_ucWarningStaus������ȡֵC_ReleaseWarning1Message��C_Warning1Message��C_NoMessage */
	
	if( V_ullWarningMoney1 != 0 )	    /* �������1����Ϊ0��������Ƿ�ѱ��� */
	{
		if( V_ucRenewFlay == C_RenewDerict )
		{
			if( V_ullRemainMoney_New_Cent <= V_ullWarningMoney1 )	/* ���ͱ�����ʾ���̵���ģ�� */
			{
				V_ucWarningStaus = C_Warning1Message;				/* ���������1������Ϣ */
			}
			else
			{
				V_ucWarningStaus = C_ReleaseWarning1Message;		/* ���������1�����Ϣ */
			}
		}
		else
		{	/*����ֱ�ӣ���ô��ץԭʣ������ڱ���1����ʣ����С�ڵ��ڱ���1�����*/
			if( ( V_ullRemainMoney_Cent > V_ullWarningMoney1 ) && ( V_ullRemainMoney_New_Cent <= V_ullWarningMoney1 ) )		/*���ͱ�����ʾ���̵���ģ��*/
			{
				V_ucWarningStaus = C_Warning1Message;				/*���������1������Ϣ*/
			}
		}
	}
	else
	{	/* �������1����0 */
		if( V_ucRenewFlay == C_RenewDerict )
		{
			if( V_ullRemainMoney_New_Cent > 0 )						/*���ͱ�����ʾ���̵���ģ��*/
			{
				V_ucWarningStaus = C_ReleaseWarning1Message;		/*���������1�����Ϣ*/
			}
		}
	}
	
	/************************* �ж��Ƿ���ҪԤ��բ���� ***************************/
	/* �����V_ucWarningStaus������ȡֵC_ReleaseWarning1Message��C_Warning1Message��C_NoMessage, C_Warning2Message */
	
	if( V_ullRemainMoney_New_Cent > V_ullWarningMoney2 )	/* ʣ������ڱ������2,�����־���� */
	{
		SF_SetMoneyToPurchaseFlag( C_NoMoneyToPurchase );
	}
	
	if( V_ullWarningMoney2 != 0 )							/* �������2����Ϊ0����������բ���� */
	{
		if( V_ucRenewFlay == C_RenewDerict )
		{
			if( V_ullRemainMoney_New_Cent <= V_ullWarningMoney2 )			/*����һ����բ��Ϣ��ʾ���̵���ģ��*/
			{
				if( SF_CheckMoneyToPurchaseFlag( ) != C_MoneyToPurchase )	/*û�й����־*/
				{
					V_ucWarningStaus = C_Warning2Message;					/*���������2������Ϣ*/
				}
				else
				{
					V_ucWarningStaus = C_Warning1Message;					/*���������1������Ϣ*/
				}
			}
		}
		else
		{	/*����ֱ�ӣ���ô��ץԭʣ������ڱ���2����ʣ����С�ڵ��ڱ���2�����*/
			if( ( V_ullRemainMoney_Cent > V_ullWarningMoney2 ) && ( V_ullRemainMoney_New_Cent <= V_ullWarningMoney2 ) )	
			{
				V_ucWarningStaus = C_Warning2Message;						/*���������2������Ϣ*/
			}
		}
	}
	
	/**************************�ж�ʣ�����Ƿ����***********************************************/
	/*ʣ�������0����ô͸֧����=0��ֱ����բ�����򷢱���2,���ﲻ���Ǳ������2�Ƿ�Ϊ0����Ҫ��������բ����*/
	 /*����͸֧���޺���բ�������жϣ�ͬʱ���������2�������ٷ���բ���Ḳ���������������ﲻ�ж�͸֧����*/
	if( V_ucRenewFlay == C_RenewDerict )
	{	/*�������if���ǿ����ϵ�ʱ���������2=0��ʣ�����0��Ϣ�����ѷ��������̵���ģ��δִ�������*/
		if( V_ullRemainMoney_New_Cent == 0 )		/*ʣ����Ϊ0,��û�й����־*/
		{
			if( SF_CheckMoneyToPurchaseFlag( ) != C_MoneyToPurchase )		/*û�й����־*/
			{
				V_ucWarningStaus = C_Warning2Message;	/*���������2������Ϣ*/
			}
			else
			{
				V_ucWarningStaus = C_Warning1Message;	/*���������1������Ϣ*/
			}
		}
	}
	else
	{	/*�������2����0���������أ�ԭʣ���Ϊ0����ʣ����Ϊ0*/
		if( ( V_ullRemainMoney_Cent > 0 ) && ( V_ullRemainMoney_New_Cent == 0 ) )
		{
			V_ucWarningStaus = C_Warning3Message;		/* ���������2������Ϣ�������ʾ�������2�����ǿ��0�ģ�����һ������ı��� */
		}
	}
	
	/*************************�ж��Ƿ���Ҫ������բ***************************/
	/*************************��բ�����أ�����ֱ����*************************/
	if( V_ullRemainMoney_New_Cent == 0 )
	{	/*��բ����ǰʣ����϶�Ϊ0��͸֧���޿��Բ��ж��Ƿ�Ϊ0*/
		if( V_ullOverDraftMoney_New_Cent >= V_ullOverDraftThresdHold )	/*����������բ��Ϣ��ʾ���̵���ģ��*/
		{
			V_ucWarningStaus = C_RelayOffMessage;
		}
	}
	
	/*****************************������ݷ���Ϣ��־����Ϣ���̵���ģ��******************************/
	V_ucBuffer[0] = Pt_RelayStateFlag; 	
	switch( V_ucWarningStaus )
	{
		case C_Warning1Message:
		{
			V_ucBuffer[1] = C_Alarm;
		}break;
		case C_ReleaseWarning1Message:
		{
			V_ucBuffer[1] = C_Alarm_Release;
		}break;
		case C_Warning2Message:
		{
			V_ucBuffer[1] = C_AlarmOpenRelay;
		}break;
		case C_Warning3Message:
		{
			V_ucBuffer[10] = Pt_RelayStateFlag;				/*ʣ������0��������Ҫ�ȷ�һ����բ������Ϣ*/
			V_ucBuffer[11] = C_Relay_Close_Direct;
		    SF_SendMessege(C_Msg_Deal_RelayStatus, &V_ucBuffer[10], (Pt_RelayStateFlag_Len + 1) );	/*���ͱ�����Ϣ����ʾ*/	
			V_ucBuffer[1] = C_AlarmOpenRelay;
		}break;
		case C_RelayOffMessage:
		{
			V_ucBuffer[1] = C_Relay_OpenNow;
		}break;
		default:
			break;
	}
	if(V_ucWarningStaus != C_NoMessage)
	{
		SF_SendMessege(C_Msg_Deal_RelayStatus, V_ucBuffer, (Pt_RelayStateFlag_Len + 1) );			/*���ͱ�����Ϣ����ʾ*/	
	}
	
	/*************************�ж��Ƿ�͸֧,͸֧����Ϣ����ʾģ��***************************/
	memset(&V_ucBuffer[0], 0xFF, 4);
	
	V_ucBuffer[0] = Pt_DisplayStatus;
	if( V_ucRenewFlay == C_RenewDerict )	/*ֱ�Ӹ��±�־�����ж�״̬�仯��ֻ���ݵ�ǰ״̬���и��±�־������Ϣ*/
	{
		if(V_ullOverDraftMoney_New > 0)
		{		
			SF_SetOverDraft_Meter_Work_State( C_SetOverDraft, SV_ucEnergySafeFlag );
		}
		else
		{
			SF_SetOverDraft_Meter_Work_State( C_ClrOverDraft, C_W_SafeFlag );
		}
	}
	else
	{	/*����ֱ�ӣ���ץ�Ӳ�͸֧��͸֧����*/
		if( ( V_ullOverDraftMoney  == 0 ) && ( V_ullOverDraftMoney_New > 0 ) )						/*����͸֧��ʾ�ַ�����ʾģ��*/
		{
			if( SF_SetOverDraft_Meter_Work_State( C_SetOverDraft, SV_ucEnergySafeFlag ) == C_OK )
            {
				Inf_WriteMeterStatus8( C_OverdraftEventNo );
            }
		}
		else if( ( ( V_ullOverDraftMoney / C_MoneyChangeEquivalent ) < V_ullOverDraftThresdHold ) && ( V_ullOverDraftMoney_New_Cent >= V_ullOverDraftThresdHold ) )		/*����͸֧��ʾ�ַ�����ʾģ��*/
		{
			SF_SetOverDraft_Meter_Work_State( C_SetOverDraft, SV_ucEnergySafeFlag );
		}
	}
}

/*************************************************************************************************************************
����ԭ�ͣ�uchar8 SF_Chargeback(ulong64 *pV_ullEnergy_F, ulong64 *pV_ullEnergy, uchar8 *pV_ucStepPara, uchar8 V_ucCurStepType)
�������������ݵ�ۿ۷ѣ���ˢ�µ�ǰ����
���������pV_ullEnergy_F���ۼ�ǰ���ܵ�ַ��
         pV_ullEnergy���ۼӺ���ܵ�ַ��
         pV_ucStepPara�����ݱ������ַ��
         V_ucCurStepType��C_ValidStep ��Ч���ݣ�C_InValidStep����Ч���ݣ�
�����������
���ز��������޿۷ѱ�־��C_SubMoneyFlag����ʾ�п۷ѱ�־��C_NoSubMoneyFlag����ʾ�޿۷ѱ�־��
����λ�ã����طѿر�۷ѵ���
��    ע��
*************************************************************************************************************************/
uchar8 SF_Chargeback(ulong64 *pV_ullEnergy_F, ulong64 *pV_ullEnergy, uchar8 *pV_ucStepPara, uchar8 V_ucCurStepType)
{
	ulong64 V_ullRemainMoney, V_ullRemainMoney_New, V_ullOverDraftMoney, V_ullOverDraftMoney_New;
	ulong64 V_ullFeeDeduction;	 /* ÿ0.01�ȿ۷Ѵ���=��ǰ���*��ѹ���������*������������� */
	ulong32 V_ulEnergy_F, V_ulEnergy;
	ulong32 V_ulCurrentPrice;
	uchar8  V_ucBuffer[8], V_ucj, V_ucEnergyTemp;
	ulong64 V_ullTemp1, V_ullTemp2, V_ullPulseConstant;
	
	/****************** ���峣�� *******************/
	SF_Read_PulseConstant(&V_ullPulseConstant);			  			/* ��ȡ�������峣�� ulong64��ʽ*/

	/******************* �ж��Ƿ���۷� ************/
	V_ullTemp1 = (*pV_ullEnergy_F) * C_EnergyChangeEquivalent_Hundred;		/*���ﲻ���������λ0.01*/
	V_ullTemp2 = (*pV_ullEnergy) * C_EnergyChangeEquivalent_Hundred;	
	
	/*������ܣ�0.01��*/
	V_ulEnergy_F = (ulong32)(V_ullTemp1 / V_ullPulseConstant);
	V_ulEnergy = (ulong32)(V_ullTemp2 / V_ullPulseConstant);
	
	if(V_ulEnergy > V_ulEnergy_F)							/*��ǰ���ܴ����ϴδ���ʱ����*/
	{
		/*********��ȡʣ���͸֧����λ0.000001Ԫ*********************/
		if( SF_Get_RMoney_DMoney( &V_ullRemainMoney, &V_ullOverDraftMoney ) != C_OK )
		{
			return ( C_NoSubMoneyFlag );
		}
		
		/********��ȡ��ѹ������������ȣ����Ի���Ϊ0��Ĭ��Ϊ1**********/
		V_ullFeeDeduction = SF_Get_V_I_Ratio( );
		
		/*********************** ���½��п۷� ***************************/	
		V_ucEnergyTemp = (uchar8)(V_ulEnergy - V_ulEnergy_F);
		for( V_ucj = 0; V_ucj < V_ucEnergyTemp; V_ucj++)
		{
			/********* �����жϿ۷�ǰ���������Ľ��� *********/
			SF_Judge_CurrentStep( (V_ulEnergy_F + V_ucj), &V_ulCurrentPrice, pV_ucStepPara, V_ucCurStepType);
			
			/****************** ��ǰ���ݵ���Ƿ�Ϊ0��Ϊ0��ִ�н��ݣ����۷ѣ�ֱ�ӷ����޿۷ѱ�־ *********/
			if( V_ulCurrentPrice == 0 )
			{
				return ( C_NoSubMoneyFlag );
			}
			
			/******************���ȿ۳�0.01�ȵ��ܽ��,ʣ���λ0.000001Ԫ,hex��ʽ*******************/
			/******************��ǰ��۵�λ0.0001Ԫ��hex��ʽ�����۷ѵ�λΪ0.01�ȣ��������ֱ���������*/
			if( V_ullRemainMoney >= ( V_ullFeeDeduction * V_ulCurrentPrice ) )
			{
				V_ullRemainMoney_New = V_ullRemainMoney - ( V_ullFeeDeduction * V_ulCurrentPrice );
				V_ullOverDraftMoney_New = 0;
			}
			else if(V_ullRemainMoney > 0)
			{
				V_ullRemainMoney_New = 0;
				V_ullOverDraftMoney_New = ( V_ullFeeDeduction * V_ulCurrentPrice ) - V_ullRemainMoney;
			}
			else
			{
				V_ullRemainMoney_New = 0;
				V_ullOverDraftMoney_New = V_ullOverDraftMoney + ( V_ullFeeDeduction * V_ulCurrentPrice );
			}
			
			V_ullRemainMoney = V_ullRemainMoney_New;
			V_ullOverDraftMoney = V_ullOverDraftMoney_New;
		}
		
		/***********************���µ�ʣ���͸֧��д���ݲ�******************************/
		PF_Ulong64ToBuffer8(V_ucBuffer, &V_ullRemainMoney, CLCurr_Money);
		InF_Write_Data(C_Msg_EnergyMetering, CChargeBal_Hex_Cent, V_ucBuffer, CLCurr_Money, SV_ucEnergySafeFlag);
		
		PF_Ulong64ToBuffer8(V_ucBuffer, &V_ullOverDraftMoney, CLCurr_Money);
		InF_Write_Data(C_Msg_EnergyMetering, COverDraft_Hex_Cent, V_ucBuffer, CLCurr_Money, SV_ucEnergySafeFlag);
		
		return ( C_SubMoneyFlag );
	}
    return  ( C_NoSubMoneyFlag );
}

/*******************************************************************************
����ԭ�ͣ�uchar8 SF_JudgePulseActive(Struct_Energy_Type *pStr_Energy)
�����������жϼ���оƬ���������������ĺϷ���
���������Str_Energy��������ṹ���ַ
�����������
���ز�����C_OK����Ϸ���C_ERR����Ƿ�
����λ�ã�������Ϣ�������е���
��    ע��
*******************************************************************************/
uchar8 SF_JudgePulseActive(Struct_Energy_Type *pStr_Energy)
{
	uchar8 V_ucFlay;

	if( SV_ucEnergySafeFlag != ( C_W_SafeFlag_2 | C_W_SafeFlag_1 ) )
	{
		return C_SafeFlagError;
	}
	
	V_ucFlay = C_OK;
		
	/*************************����Ϸ����ж�*******************************/
	if( pStr_Energy->V_usActiveEnergy_T > C_Pluse_Most__Lim )
	{
		V_ucFlay = C_Error;
	}
	
	if( pStr_Energy->V_usActiveEnergy_A > C_Pluse_Most__Lim )
	{
		V_ucFlay = C_Error;
	}
	
	if( pStr_Energy->V_usActiveEnergy_B > C_Pluse_Most__Lim )
	{
		V_ucFlay = C_Error;
	}
	
	if( pStr_Energy->V_usActiveEnergy_C > C_Pluse_Most__Lim )
	{
		V_ucFlay = C_Error;
	}
	
	if( pStr_Energy->V_usReactiveEnergy_T > C_Pluse_Most__Lim )
	{
		V_ucFlay = C_Error;
	}
	
	if( pStr_Energy->V_usReactiveEnergy_A > C_Pluse_Most__Lim )
	{
		V_ucFlay = C_Error;
	}
	
	if( pStr_Energy->V_usReactiveEnergy_B > C_Pluse_Most__Lim )
	{
		V_ucFlay = C_Error;
	}
	
	if( pStr_Energy->V_usReactiveEnergy_C > C_Pluse_Most__Lim )
	{
		V_ucFlay = C_Error;
	}
	
	/*************************�г���ľ����㣬���ش���**************************************/
	if( V_ucFlay == C_Error )
	{
		pStr_Energy->V_usActiveEnergy_T = 0;
		pStr_Energy->V_usActiveEnergy_A = 0;
		pStr_Energy->V_usActiveEnergy_B = 0;
		pStr_Energy->V_usActiveEnergy_C = 0;
		pStr_Energy->V_usReactiveEnergy_T = 0;
		pStr_Energy->V_usReactiveEnergy_A = 0;
		pStr_Energy->V_usReactiveEnergy_B = 0;
		pStr_Energy->V_usReactiveEnergy_C = 0;
		return V_ucFlay;
	}
	return C_OK;
}

/*******************************************************************************
����ԭ�ͣ�void SF_Adjust_EnergyPulse(Struct_Energy_Type *pV_StrEnergy)
��������������������Ĩƽ
���������pV_StrEnergy��������ṹ���ַ
�����������
���ز�������
����λ�ã�������Ϣ�������е���
��    ע��
*******************************************************************************/
void SF_Adjust_EnergyPulse(Struct_Energy_Type *pV_StrEnergy)
{
	ulong64  V_ullForward_T, V_ullReverse_T, V_ullForward_ABC, V_ullReverse_ABC, V_ullTemp;
	ushort16 *pV_usTemp;
	uchar8   V_ucPhaseFlay;
	
	if( SV_ucEnergySafeFlag != ( C_W_SafeFlag_2 | C_W_SafeFlag_1 ) )
	{
		return;
	}
	
	if ( ( pV_StrEnergy->V_usActiveEnergy_A == 0 )
	  && ( pV_StrEnergy->V_usActiveEnergy_B == 0 )
	  && ( pV_StrEnergy->V_usActiveEnergy_C == 0 ) )		/*�й����������������Ϊ0�򲻽����й��������*/
	{
		goto DealReverseEnergyPulse;
	}

	/**********************��ȡ�����й���������************************/	
	V_ullForward_T = 0;
	if ( SF_ReadTotalEnergy(CPos_Ac_T1_PreEn_0, &V_ullForward_T, C_MaxRatesNum, C_GetNextRatesEnergy ) != C_OK )
	{
		return;		/*�����ݳ��ֲ��ɹ�����ֱ���˳����������������*/
	}
	
	/**********************��ȡ�����й���������************************/	
	V_ullReverse_T = 0;
	if ( SF_ReadTotalEnergy(CRev_Ac_T1_PreEn_0, &V_ullReverse_T, C_MaxRatesNum, C_GetNextRatesEnergy ) != C_OK )
	{
		return;		/*�����ݳ��ֲ��ɹ�����ֱ���˳����������������*/
	}

	
	/**********************��ȡ���������й���������************************/
	V_ullForward_ABC = 0;
	if ( SF_ReadTotalEnergy(CPosA_Ac_PreEn_0, &V_ullForward_ABC, 3, C_GetNextPhaseEnergy ) != C_OK )
	{
		return;		/*�����ݳ��ֲ��ɹ�����ֱ���˳����������������*/
	}

	/**********************��ȡ���෴���й���������************************/
	V_ullReverse_ABC = 0;
	if ( SF_ReadTotalEnergy(CRevA_Ac_PreEn_0, &V_ullReverse_ABC, 3, C_GetNextPhaseEnergy ) != C_OK )
	{
		return;		/*�����ݳ��ֲ��ɹ�����ֱ���˳����������������*/
	}

	
/*************************������оƬ�����ĵ�ǰ�����ۼ���ȥ*****************************
����:	                    														  
V_ullForward_T/V_ullReverse_T		�ܵ�������������                                  
V_ullForward_ABC/V_ullReverse_ABC	ABC����������������                               
**************************************************************************************/
	if( ( pV_StrEnergy->V_ucPowerDeriction & C_ActiveDeriction_T ) == 0x00 )
	{
		V_ullForward_T += pV_StrEnergy->V_usActiveEnergy_T;		/*�����й������������ϼ���оƬ�����������й�������*/
	}
	else
	{
		V_ullReverse_T += pV_StrEnergy->V_usActiveEnergy_T;		/*reverse total pulse add reverse pulse from meterIC*/
	}
	
	if( ( pV_StrEnergy->V_ucPowerDeriction & C_ActiveDeriction_A ) == 0x00 )
	{
		V_ullForward_ABC += pV_StrEnergy->V_usActiveEnergy_A;	/*�����й������������ϼ���оƬ�����������й�������*/
	}
	else
	{
		V_ullReverse_ABC += pV_StrEnergy->V_usActiveEnergy_A;	/*reverse total pulse add reverse pulse from meterIC*/
	}
	
	if( ( pV_StrEnergy->V_ucPowerDeriction & C_ActiveDeriction_B ) == 0x00 )
	{
		V_ullForward_ABC += pV_StrEnergy->V_usActiveEnergy_B;	/*�����й������������ϼ���оƬ�����������й�������*/
	}
	else
	{
		V_ullReverse_ABC += pV_StrEnergy->V_usActiveEnergy_B;	/*reverse total pulse add reverse pulse from meterIC*/
	}
	
	if( ( pV_StrEnergy->V_ucPowerDeriction & C_ActiveDeriction_C ) == 0x00 )
	{
		V_ullForward_ABC += pV_StrEnergy->V_usActiveEnergy_C;	/*�����й������������ϼ���оƬ�����������й�������*/
	}
	else
	{
		V_ullReverse_ABC += pV_StrEnergy->V_usActiveEnergy_C;	/*reverse total pulse add reverse pulse from meterIC*/
	}
	
/****************************�����ܺͷ������������****************************
����:           															  
V_ullForward_T/V_ullReverse_T		�ܵ�������������                          
V_ullForward_ABC/V_ullReverse_ABC	ABC����������������                       
*****************************************************************************/
	if(V_ullForward_T >= V_ullReverse_T)			/*���������������������ֵ*/
	{
		V_ullForward_T -= V_ullReverse_T;
		V_ullReverse_T = 0;
	}
	else
	{
		V_ullReverse_T -= V_ullForward_T;
		V_ullForward_T = 0;
	}
	
	if(V_ullForward_ABC >= V_ullReverse_ABC)		/*���������������������ֵ*/
	{
		V_ullForward_ABC -= V_ullReverse_ABC;
		V_ullReverse_ABC = 0;
	}
	else
	{
		V_ullReverse_ABC -= V_ullForward_ABC;
		V_ullForward_ABC = 0;
	}
	
/****************************�����ִܷ����͵Ĳ�ֵ*********************************
�������������δ���������������ܡ��ִ����������������:						
1�������ܡ��ִ�������������ֵ���ò�ֵ����һ�����ж��Ƿ���3�����岹����ֵʹ�á�  
2���ó��������岹������(��ϸ�ɲμ����˼·-����Ĩƽԭ��)��                      
	������������4��:��ʵ��ֻ��2�ֿ��ܣ���+1����-1������-1����+1����             
		a����ǰ�������巽��Ϊ����������+1                                       
		b����ǰ�������巽��Ϊ����������-1                                       
		c����ǰ�������巽��Ϊ����������+1                                       
		d����ǰ�������巽��Ϊ����������-1                                       
����:(���¼Ĵ������ȱ�ʾ�˴��������������ֱ�ʾ�����ͷ���)                       
V_ullForward_T/V_ullReverse_T		�ܵ�������������������                      
V_ullForward_ABC/V_ullReverse_ABC	ABC����������������������                   
ע�⣬���ϴ�����Ϊ�����������������������,����������Ϊ0                        
      ������Ϊ����������ڷ����������У�����������Ϊ0                           
���:���ڱ��ζ��벻�жϷ��෽����˸��ݵ���Ĩƽԭ��������ֵ:                
V_ullForward_T������ͷ�����������������Ͳ�ֵ����ʾ��+1����-1��                
	��:�ִܷ�����ͬ������>��;ͬ������<��;��Ϊ������Ϊ��                         
V_ullForward_ABC:����ͷ�����������������Ͳ�ֵ����ʾ��-1����+1����             
	��:�ִܷ�����ͬ������<��;ͬ������>��;��Ϊ������Ϊ��                         
*********************************************************************************/
	if( ( V_ullForward_T != 0 ) && ( V_ullForward_ABC != 0 ) )			/*���������ݾ�Ϊ����*/
	{
		if(V_ullForward_T >= V_ullForward_ABC)
		{
			V_ullForward_T -= V_ullForward_ABC;
			V_ullForward_ABC = 0;
		}
		else
		{
			V_ullForward_ABC -= V_ullForward_T;
			V_ullForward_T = 0;
		}
	}
	else if( ( V_ullReverse_T != 0 ) && ( V_ullReverse_ABC != 0 ) )		/*���������ݾ�Ϊ����*/
	{
		if(V_ullReverse_T > V_ullReverse_ABC)
		{
			V_ullForward_ABC = V_ullReverse_T - V_ullReverse_ABC;
		}
		else
		{
			V_ullForward_T = V_ullReverse_ABC - V_ullReverse_T;
		}
	}
	else	/*��ֵ��������෽��ͬ*/
	{
		if( ( V_ullForward_T > 0 ) || ( V_ullReverse_ABC > 0 ) )	/*�����������Ϊ�����ֵ���ڷ��������ֵ�����*/
		{
			V_ullForward_T += V_ullReverse_ABC;
		}
		else
		{
			V_ullForward_ABC += V_ullReverse_T;
		}
	}
/**********************ȷ������һ����������********************************
���ܣ������ζ�����оƬ�������������ѡ����							 
����:��ǰ����������ṹ�� pV_StrEnergy                                
���:                                                                
pV_usTemp			:�����������ԭʼ��������ָ��                    
V_ucPhaseFlay	:�����������ָʾ�������жϸ��������Ǹ�ʹ��          
	2��4��8����A��B��C,��������!Ӧ����1��2��4���ú�!               
ע�⣺1������Ĭ����A�������2������ǰ��ȫ0ֱ�����ߣ�                 
	��˵������ǲ������*pV_usTemp=0���                              
*************************************************************************/
	pV_usTemp = &(pV_StrEnergy->V_usActiveEnergy_A);
	V_ucPhaseFlay = C_ActiveDeriction_A;
	if( pV_StrEnergy->V_usActiveEnergy_A < pV_StrEnergy->V_usActiveEnergy_B )
	{
		pV_usTemp = &(pV_StrEnergy->V_usActiveEnergy_B);
		V_ucPhaseFlay = C_ActiveDeriction_B;
		if(pV_StrEnergy->V_usActiveEnergy_B < pV_StrEnergy->V_usActiveEnergy_C)
		{
			pV_usTemp = &(pV_StrEnergy->V_usActiveEnergy_C);
			V_ucPhaseFlay = C_ActiveDeriction_C;
		}
	}
	else
	{
		if(pV_StrEnergy->V_usActiveEnergy_A < pV_StrEnergy->V_usActiveEnergy_C)
		{
			pV_usTemp = &(pV_StrEnergy->V_usActiveEnergy_C);
			V_ucPhaseFlay = C_ActiveDeriction_C;
		}
	}
	
/********************����*****************************************************
���룺pV_usTemp ������������ָ��								  
     V_ucPhaseFlay ���������ָʾ��                              
V_ullForward_T������ͷ�����������������Ͳ�ֵ����ʾ��+1����-1��          
	��:�ִܷ�����ͬ������>��;ͬ������<��;��Ϊ������Ϊ��                   
V_ullForward_ABC:����ͷ�����������������Ͳ�ֵ����ʾ��-1����+1����       
	��:�ִܷ�����ͬ������<��;ͬ������>��;��Ϊ������Ϊ��                   
*****************************************************************************/
	if( V_ullForward_T >= 3 )				 /*���������ȷ���������֮�Ͷ���3��*/
	{
		/**********�жϷ������������廹�Ƿ�������**********/
		if( ( pV_StrEnergy->V_ucPowerDeriction & V_ucPhaseFlay ) == V_ucPhaseFlay )
		{
			*pV_usTemp -= 1;
		}
		else
		{
			*pV_usTemp += 1;
		}
	}
	else if( V_ullForward_ABC >= 3 )
	{
		/**********�жϷ������������廹�Ƿ�������**********/
		if( ( pV_StrEnergy->V_ucPowerDeriction & V_ucPhaseFlay) == V_ucPhaseFlay )
		{
			*pV_usTemp += 1;
		}
		else
		{
			*pV_usTemp -= 1;
		}
	}
/***********************************����Ϊ�޹��������*********************************************/
DealReverseEnergyPulse:
	if ( ( pV_StrEnergy->V_usReactiveEnergy_A == 0 )
	  && ( pV_StrEnergy->V_usReactiveEnergy_B == 0 )
	  && ( pV_StrEnergy->V_usReactiveEnergy_C == 0 ) )	   /*�޹����������Ϊ0�Ͳ������޹��������*/
	{
		return;
	}
	
	/**********************��ȡ�����޹���������************************/
	V_ullForward_T = 0;		
	if ( SF_ReadTotalEnergy(CQua1_Re_T1_PreEn_0, &V_ullForward_T, C_MaxRatesNum, C_GetNextRatesEnergy ) != C_OK )
	{
		return;		/*�����ݳ��ֲ��ɹ�����ֱ���˳����������������*/
	}
	
	V_ullTemp = 0;
	if ( SF_ReadTotalEnergy(CQua2_Re_T1_PreEn_0, &V_ullTemp, C_MaxRatesNum, C_GetNextRatesEnergy ) != C_OK )
	{
		return;		/*�����ݳ��ֲ��ɹ�����ֱ���˳����������������*/
	}
	V_ullForward_T += V_ullTemp;
	
	/**********************��ȡ�����޹���������************************/
	V_ullReverse_T = 0;
	if ( SF_ReadTotalEnergy(CQua4_Re_T1_PreEn_0, &V_ullReverse_T, C_MaxRatesNum, C_GetNextRatesEnergy ) != C_OK )
	{
		return;		/*�����ݳ��ֲ��ɹ�����ֱ���˳����������������*/
	}
	
	V_ullTemp = 0;
	if ( SF_ReadTotalEnergy(CQua3_Re_T1_PreEn_0, &V_ullTemp, C_MaxRatesNum, C_GetNextRatesEnergy ) != C_OK )
	{
		return;		/*�����ݳ��ֲ��ɹ�����ֱ���˳����������������*/
	}
	
	V_ullReverse_T += V_ullTemp;
	/**********************��ȡ���������޹���������************************/
	V_ullForward_ABC = 0;
	if ( SF_ReadTotalEnergy(CQua1A_Re_PreEn_0, &V_ullForward_ABC, 3, C_GetNextPhaseEnergy ) != C_OK )
	{
		return;		/*�����ݳ��ֲ��ɹ�����ֱ���˳����������������*/
	}
	
	V_ullTemp = 0;
	if ( SF_ReadTotalEnergy(CQua2A_Re_PreEn_0, &V_ullTemp, 3, C_GetNextPhaseEnergy ) != C_OK )
	{
		return;		/*�����ݳ��ֲ��ɹ�����ֱ���˳����������������*/
	}
	
	V_ullForward_ABC += V_ullTemp;
		
	/**********************��ȡ���෴���޹���������************************/
	V_ullReverse_ABC = 0;
	if ( SF_ReadTotalEnergy(CQua4A_Re_PreEn_0, &V_ullReverse_ABC, 3, C_GetNextPhaseEnergy ) != C_OK )
	{
		return;		/*�����ݳ��ֲ��ɹ�����ֱ���˳����������������*/
	}
	
	V_ullTemp = 0;
	if ( SF_ReadTotalEnergy(CQua3A_Re_PreEn_0, &V_ullTemp, 3, C_GetNextPhaseEnergy ) != C_OK )
	{
		return;		/*�����ݳ��ֲ��ɹ�����ֱ���˳����������������*/
	}
	
	V_ullReverse_ABC += V_ullTemp;
	
/*************************������оƬ�����ĵ�ǰ�����ۼ���ȥ******************************
����:																				  
V_ullForward_T/V_ullReverse_T		�ܵ�������������        						  
V_ullForward_ABC/V_ullReverse_ABC	ABC����������������     						  
*************************************************************************************/
	if( ( pV_StrEnergy->V_ucPowerDeriction & C_ReactiveEDeriction_T ) == 0x00 )
	{
		V_ullForward_T += pV_StrEnergy->V_usReactiveEnergy_T;	/*�����޹������������ϼ���оƬ�����������޹�������*/
	}
	else
	{
		V_ullReverse_T += pV_StrEnergy->V_usReactiveEnergy_T;	/*reverse total pulse add reverse pulse from meterIC*/
	}
	
	if( ( pV_StrEnergy->V_ucPowerDeriction & C_ReactiveEDeriction_A ) == 0x00 )
	{
		V_ullForward_ABC += pV_StrEnergy->V_usReactiveEnergy_A;	/*�����޹������������ϼ���оƬ�����������޹�������*/
	}
	else
	{
		V_ullReverse_ABC += pV_StrEnergy->V_usReactiveEnergy_A;	/*reverse total pulse add reverse pulse from meterIC*/
	}
	
	if( ( pV_StrEnergy->V_ucPowerDeriction & C_ReactiveEDeriction_B ) == 0x00 )
	{
		V_ullForward_ABC += pV_StrEnergy->V_usReactiveEnergy_B;	/*�����޹������������ϼ���оƬ�����������޹�������*/
	}
	else
	{
		V_ullReverse_ABC += pV_StrEnergy->V_usReactiveEnergy_B;	/*reverse total pulse add reverse pulse from meterIC*/
	}
	
	if( ( pV_StrEnergy->V_ucPowerDeriction & C_ReactiveEDeriction_C ) == 0x00 )
	{
		V_ullForward_ABC += pV_StrEnergy->V_usReactiveEnergy_C;	/*�����޹������������ϼ���оƬ�����������޹�������*/
	}
	else
	{
		V_ullReverse_ABC += pV_StrEnergy->V_usReactiveEnergy_C;	/*reverse total pulse add reverse pulse from meterIC*/
	}
	
/****************************�����ܺͷ������������********************************
����:																			 
V_ullForward_T/V_ullReverse_T		�ܵ�������������                             
V_ullForward_ABC/V_ullReverse_ABC	ABC����������������                          
*********************************************************************************/
	if( V_ullForward_T >= V_ullReverse_T )		/*���������������������ֵ*/
	{
		V_ullForward_T -= V_ullReverse_T;
		V_ullReverse_T = 0;
	}
	else
	{
		V_ullReverse_T -= V_ullForward_T;
		V_ullForward_T = 0;
	}
	
	if( V_ullForward_ABC >= V_ullReverse_ABC )	/*���������������������ֵ*/
	{
		V_ullForward_ABC -= V_ullReverse_ABC;
		V_ullReverse_ABC = 0;
	}
	else
	{
		V_ullReverse_ABC -= V_ullForward_ABC;
		V_ullForward_ABC = 0;
	}
	
/****************************�����ִܷ����͵Ĳ�ֵ***********************************
�������������δ���������������ܡ��ִ����������������:						
1�������ܡ��ִ�������������ֵ���ò�ֵ����һ�����ж��Ƿ���3�����岹����ֵʹ�á�  
2���ó��������岹������(��ϸ�ɲμ����˼·-����Ĩƽԭ��)��                      
	������������4��:��ʵ��ֻ��2�ֿ��ܣ���+1����-1������-1����+1����             
		a����ǰ�������巽��Ϊ����������+1                                       
		b����ǰ�������巽��Ϊ����������-1                                       
		c����ǰ�������巽��Ϊ����������+1                                       
		d����ǰ�������巽��Ϊ����������-1                                       
����:(���¼Ĵ������ȱ�ʾ�˴��������������ֱ�ʾ�����ͷ���)                       
V_ullForward_T/V_ullReverse_T		�ܵ�������������������                      
V_ullForward_ABC/V_ullReverse_ABC	ABC����������������������                   
ע�⣬���ϴ�����Ϊ�����������������������,����������Ϊ0                        
      ������Ϊ����������ڷ����������У�����������Ϊ0                           
���:���ڱ��ζ��벻�жϷ��෽����˸��ݵ���Ĩƽԭ��������ֵ:                
V_ullForward_T������ͷ�����������������Ͳ�ֵ����ʾ��+1����-1��                
		��:�ִܷ�����ͬ������>��;ͬ������<��;��Ϊ������Ϊ��                     
V_ullForward_ABC:����ͷ�����������������Ͳ�ֵ����ʾ��-1����+1����             
		��:�ִܷ�����ͬ������<��;ͬ������>��;��Ϊ������Ϊ��                     
*********************************************************************************/
	if( ( V_ullForward_T != 0 ) && ( V_ullForward_ABC != 0 ) )		  /*���������ݾ�Ϊ����*/
	{
		if( V_ullForward_T >= V_ullForward_ABC )
		{
			V_ullForward_T -= V_ullForward_ABC;
			V_ullForward_ABC = 0;
		}
		else
		{
			V_ullForward_ABC -= V_ullForward_T;
			V_ullForward_T = 0;
		}
	}
	else if( ( V_ullReverse_T != 0 ) && ( V_ullReverse_ABC != 0 ) )  /*���������ݾ�Ϊ������*/
	{
		if(V_ullReverse_T > V_ullReverse_ABC)
		{
			V_ullForward_ABC = V_ullReverse_T - V_ullReverse_ABC;
		}
		else
		{
			V_ullForward_T = V_ullReverse_ABC - V_ullReverse_T;
		}
	}
	else	/*��ֵ��������෽��ͬ*/
	{
		if(V_ullForward_T > 0)
		{
			V_ullForward_T += V_ullReverse_ABC;
		}
		else
		{
			V_ullForward_ABC += V_ullReverse_T;
		}
	}
/**********************ȷ������һ����������*******************************
���ܣ������ζ�����оƬ�������������ѡ����							 
����:��ǰ����������ṹ�� pV_StrEnergy								
���:																
pV_usTemp			:�����������ԭʼ��������ָ��					
V_ucPhaseFlay	:�����������ָʾ�������жϸ��������Ǹ�ʹ��  		
	2��4��8����A��B��C,��������!Ӧ����1��2��4���ú�!				
ע�⣺1������Ĭ����A�������2������ǰ��ȫ0ֱ�����ߣ���˵������ǲ���
	����*pV_usTemp=0���												
*********************ȷ������һ����������********************************/
	pV_usTemp = &(pV_StrEnergy->V_usReactiveEnergy_A);
	V_ucPhaseFlay = C_ReactiveEDeriction_A;
	if( pV_StrEnergy->V_usReactiveEnergy_A < pV_StrEnergy->V_usReactiveEnergy_B )
	{
		pV_usTemp = &(pV_StrEnergy->V_usReactiveEnergy_B);
		V_ucPhaseFlay = C_ReactiveEDeriction_B;
		if( pV_StrEnergy->V_usReactiveEnergy_B < pV_StrEnergy->V_usReactiveEnergy_C )
		{
			pV_usTemp = &(pV_StrEnergy->V_usReactiveEnergy_C);
			V_ucPhaseFlay = C_ReactiveEDeriction_C;
		}
	}
	else
	{
		if( pV_StrEnergy->V_usReactiveEnergy_A < pV_StrEnergy->V_usReactiveEnergy_C )
		{
			pV_usTemp = &(pV_StrEnergy->V_usReactiveEnergy_C);
			V_ucPhaseFlay = C_ReactiveEDeriction_C;
		}
	}
/***********************************����******************************************************
���룺pV_usTemp			������������ָ��												  
		V_ucPhaseFlay		���������ָʾ��												
V_ullForward_T������ͷ�����������������Ͳ�ֵ��											
				��ʾ��+1����-1����:�ִܷ�����ͬ������>��;ͬ������<��;��Ϊ������Ϊ��			
V_ullForward_ABC:����ͷ�����������������Ͳ�ֵ����ʾ��-1����+1������:�ִܷ�����ͬ������<��;
			ͬ������>��;��Ϊ������Ϊ��														
*********************************************************************************************/
	if(V_ullForward_T >= 3)		/*���������ȷ���������֮�Ͷ���3��*/
	{
		/**********�жϷ������������廹�Ƿ�������**********/
		if( ( pV_StrEnergy->V_ucPowerDeriction & V_ucPhaseFlay ) == V_ucPhaseFlay )
		{
			*pV_usTemp -= 1;
		}
		else
		{
			*pV_usTemp += 1;
		}
	}
	else if( V_ullForward_ABC >= 3 )
	{
		/**********�жϷ������������廹�Ƿ�������**********/
		if( ( pV_StrEnergy->V_ucPowerDeriction & V_ucPhaseFlay ) == V_ucPhaseFlay )
		{
			*pV_usTemp += 1;
		}
		else
		{
			*pV_usTemp -= 1;
		}
	}
}

/*******************************************************************************
����ԭ�ͣ�uchar8 SF_SettlementEnergy_Metering_L(Struct_Energy_Type *pStr_Energy)
�������������طѿر���ݽ������������
���������Str_Energyָ���������ṹ�� 
�����������
���ز�������û�п۷ѱ�־ָʾ��
		  C_SubMoneyFlag���п۷ѱ�־��
          C_NoSubMoneyFlag���޿۷ѱ�־��
����λ�ã�������Ϣ�������е���
��    ע��
*******************************************************************************/
uchar8 SF_SettlementEnergy_Metering_L(Struct_Energy_Type *pStr_Energy)
{
	ulong64 V_ullEnergy, V_ullEnergy_F;
	uchar8  V_ucBuffer[80], V_ucCurrentStepType, V_ucFlayTemp;
	uchar8  V_ucTemp[10];
    uchar8  V_ReturnData;
	ushort16 V_usLen, V_usDataEncode;

	if( pStr_Energy->V_usActiveEnergy_T == 0 )
	{
		return C_NoSubMoneyFlag ;		 /*�����й���������Ϊ0ֱ�ӷ����޿۷�*/
	}
	
	/**********************��ȡ��ǰ�׽��ݱ���������жϵ�ǰ��������*******/
	V_usDataEncode = 0;
	V_usLen = CLCurrent_Ladder_Table;
	if( InF_Read_Data( CCurrent_Ladder_Table, V_ucBuffer, &V_usLen, &V_usDataEncode ) == C_OK )		/*��ȡ��ǰ�׽��ݱ����*/
	{
		V_ucCurrentStepType = SF_Judge_CurrentStep_Type( &V_ucBuffer[C_StepSettlementStartAddr] );		/*�жϵ�ǰ��������*/
	}
	else
	{
		V_ucCurrentStepType = C_InValidStep;
	}
		
	/**********************��ǰ���ݽ����õ���********************/
	V_usDataEncode = 0;
	V_usLen  = C_EnergyPulseLen;
	V_ucFlayTemp = InF_Read_Data(CY_Com_Ac_Tol_En_0, V_ucTemp, &V_usLen, &V_usDataEncode);
	if( V_ucFlayTemp == C_OK )
	{
		PF_Buffer8ToUlong64(V_ucTemp, &V_ullEnergy_F, C_EnergyPulseLen);
		V_ullEnergy = V_ullEnergy_F + pStr_Energy->V_usActiveEnergy_T;
		PF_Ulong64ToBuffer8(V_ucTemp, &V_ullEnergy, C_EnergyPulseLen);
		InF_Write_Data(C_Msg_EnergyMetering, CY_Com_Ac_Tol_En_0, V_ucTemp, C_EnergyPulseLen, SV_ucEnergySafeFlag);
			
		V_ReturnData = SF_Chargeback(&V_ullEnergy_F, &V_ullEnergy, V_ucBuffer, V_ucCurrentStepType);		/*���п۷�*/
        
		return V_ReturnData;
	}
	
	return C_NoSubMoneyFlag;		
}

/*******************************************************************************
����ԭ�ͣ�void SF_Energy_Metering(void)
�������������ܴ�����
�����������
�����������
���ز�������
����λ�ã�������Ϣ�������е���
��    ע��
*******************************************************************************/
void SF_Energy_Metering(void)
{
	ulong64  V_ullEnergy;
	ulong32  V_ulID = 1;
	uchar8   V_ucBuffer[5], V_ucRateNo, V_ucFlayTemp;
	ulong64	 V_ullRateEnergy_F, V_ullRateEnergy;
	ushort16 V_usLen, V_usDataEncode;		
	ulong64  V_ullRemainMoney, V_ullRemainMoney_New, V_ullOverDraftMoney, V_ullOverDraftMoney_New;
	uchar8	 V_ucSubMoneyFlag1, V_ucSubMoneyFlag2;
	Struct_Energy_Type Str_Pulse;
	
	if( SV_ucEnergySafeFlag != C_W_SafeFlag_1 )
	{
		return;
	}
	
 	if( InF_Read_MeterIC_EnergyData( &Str_Pulse ) != C_OK )		/*����оƬ�����ݲ��ɹ�*/
	{
		return;
	}
	
	SV_ucEnergySafeFlag |= C_W_SafeFlag_2;
	
	if( SF_JudgePulseActive( &Str_Pulse ) != C_OK )				/*����оƬ���ݷǷ�*/
	{
		return;
	}
	
	SF_Adjust_EnergyPulse(&Str_Pulse);							/*�����������*/
	
	/**************��ȡ���ݲ㵱ǰ����***********************************/
	V_usDataEncode = 0;
	V_usLen = CLCurr_Rate_No;
	if( InF_Read_Data(CCurr_Rate_No, &V_ucRateNo, &V_usLen, &V_usDataEncode) != C_OK )
	{
		V_ucRateNo = 1;
	}
	
	if( ( V_ucRateNo == 0 ) || ( V_ucRateNo > C_MaxRatesNum ) )	/*��ǰ���ʷǷ���Ĭ�ϼ����*/
	{
		V_ucRateNo = 1;
	}
	
	SV_ucEnergySafeFlag |= C_W_SafeFlag_3;
	
	/************��ȡ��ǰ���ݲ���ʵ����Ա㱾�ر���п۷�****************/
	V_ullRateEnergy_F = SF_Get_RateEnergyForChargeback( V_ucRateNo );
	
	/************���½��������ۼӵ��ܵ�������****************************/
	if( Str_Pulse.V_usActiveEnergy_T > 0 )			 		/*�����й����岻Ϊ0*/
	{
		if( ( Str_Pulse.V_ucPowerDeriction & C_ActiveDeriction_T ) == 0 )
		{
			V_ulID = CPos_Ac_T1_PreEn_0 + C_GetNextRatesEnergy * ( V_ucRateNo - 1 );
		}
		else
		{
			V_ulID = CRev_Ac_T1_PreEn_0 + C_GetNextRatesEnergy * ( V_ucRateNo - 1 );
		}
		
		V_usDataEncode = 0;
		V_usLen  = C_EnergyPulseLen;
		V_ucFlayTemp = InF_Read_Data(V_ulID, V_ucBuffer, &V_usLen, &V_usDataEncode);
		if( V_ucFlayTemp == C_OK ) 
		{
			PF_Buffer8ToUlong64(V_ucBuffer, &V_ullEnergy, C_EnergyPulseLen);
			V_ullEnergy += Str_Pulse.V_usActiveEnergy_T;
			PF_Ulong64ToBuffer8(V_ucBuffer, &V_ullEnergy, C_EnergyPulseLen);
			InF_Write_Data( C_Msg_EnergyMetering, V_ulID, V_ucBuffer, C_EnergyPulseLen, SV_ucEnergySafeFlag );
		}
		else
		{	/*���������ܣ�ֱ���˳�����������������һ���ۼӡ�����оƬ�ڵı��ζ����ĵ���ȫ��������*/
			return;
		}
	}
	
	if( Str_Pulse.V_usActiveEnergy_A > 0 )					/*A���й����岻Ϊ0*/
	{
		if( ( Str_Pulse.V_ucPowerDeriction & C_ActiveDeriction_A ) == 0 )
		{
			V_ulID = CPosA_Ac_PreEn_0;
		}
		else
		{
			V_ulID = CRevA_Ac_PreEn_0;
		}
		
		V_usDataEncode = 0;
		V_usLen  = C_EnergyPulseLen;
		V_ucFlayTemp = InF_Read_Data(V_ulID, V_ucBuffer, &V_usLen, &V_usDataEncode);
		if( V_ucFlayTemp == C_OK )
		{
			PF_Buffer8ToUlong64(V_ucBuffer, &V_ullEnergy, C_EnergyPulseLen);
			V_ullEnergy += Str_Pulse.V_usActiveEnergy_A;
			PF_Ulong64ToBuffer8(V_ucBuffer, &V_ullEnergy, C_EnergyPulseLen);
			InF_Write_Data(C_Msg_EnergyMetering, V_ulID, V_ucBuffer, C_EnergyPulseLen, SV_ucEnergySafeFlag);
		}
		else
		{	/*���������ܣ�ֱ���˳�����������������һ���ۼӡ�����оƬ�ڵı��ζ����ĵ���ȫ��������*/
			return;
		}
	}
	
	if( Str_Pulse.V_usActiveEnergy_B > 0 )					/*B���й����岻Ϊ0*/
	{
		if( ( Str_Pulse.V_ucPowerDeriction & C_ActiveDeriction_B ) == 0 )
		{
			V_ulID = CPosB_Ac_PreEn_0;
		}
		else
		{
			V_ulID = CRevB_Ac_PreEn_0;
		}
		
		V_usDataEncode = 0;
		V_usLen = C_EnergyPulseLen;
		V_ucFlayTemp = InF_Read_Data(V_ulID, V_ucBuffer, &V_usLen, &V_usDataEncode);
		if( V_ucFlayTemp == C_OK )
		{
			PF_Buffer8ToUlong64(V_ucBuffer, &V_ullEnergy, C_EnergyPulseLen);
			V_ullEnergy += Str_Pulse.V_usActiveEnergy_B;
			PF_Ulong64ToBuffer8(V_ucBuffer, &V_ullEnergy, C_EnergyPulseLen);
			InF_Write_Data(C_Msg_EnergyMetering, V_ulID, V_ucBuffer, C_EnergyPulseLen, SV_ucEnergySafeFlag);
		}
		else
		{	/*���������ܣ�ֱ���˳�����������������һ���ۼӡ�����оƬ�ڵı��ζ����ĵ���ȫ��������*/
			return;
		}
	}
	
	if( Str_Pulse.V_usActiveEnergy_C > 0 )					/*C���й����岻Ϊ0*/
	{
		if( ( Str_Pulse.V_ucPowerDeriction & C_ActiveDeriction_C ) == 0 )
		{
			V_ulID = CPosC_Ac_PreEn_0;
		}
		else
		{
			V_ulID = CRevC_Ac_PreEn_0;
		}
		
		V_usDataEncode = 0;
		V_usLen = C_EnergyPulseLen;
		V_ucFlayTemp = InF_Read_Data(V_ulID, V_ucBuffer, &V_usLen, &V_usDataEncode);
		if( V_ucFlayTemp == C_OK )
		{
			PF_Buffer8ToUlong64(V_ucBuffer, &V_ullEnergy, C_EnergyPulseLen);
			V_ullEnergy += Str_Pulse.V_usActiveEnergy_C;
			PF_Ulong64ToBuffer8(V_ucBuffer, &V_ullEnergy, C_EnergyPulseLen);
			InF_Write_Data(C_Msg_EnergyMetering, V_ulID, V_ucBuffer, C_EnergyPulseLen, SV_ucEnergySafeFlag);
		}
		else
		{	/*���������ܣ�ֱ���˳�����������������һ���ۼӡ�����оƬ�ڵı��ζ����ĵ���ȫ��������*/
			return;
		}
	}
	
	/*******************�޹����ܴ���************************/
	if( Str_Pulse.V_usReactiveEnergy_T > 0 )				/*�����޹����岻Ϊ0*/
	{
		if( ( Str_Pulse.V_ucPowerDeriction & C_ReactiveDeriction_T ) == 0x00 )							/*��1����*/
		{
			V_ulID = CQua1_Re_T1_PreEn_0 + C_GetNextRatesEnergy * ( V_ucRateNo - 1 );
		}
		else if( ( Str_Pulse.V_ucPowerDeriction & C_ReactiveDeriction_T ) == C_ActiveDeriction_T )		/*��2����*/
		{
			V_ulID = CQua2_Re_T1_PreEn_0 + C_GetNextRatesEnergy * ( V_ucRateNo - 1 );
		}
		else if( ( Str_Pulse.V_ucPowerDeriction & C_ReactiveDeriction_T ) == C_ReactiveDeriction_T )	/*��3����*/
		{
			V_ulID = CQua3_Re_T1_PreEn_0 + C_GetNextRatesEnergy * ( V_ucRateNo - 1 );
		}
		else												/*��4����*/
		{
			V_ulID = CQua4_Re_T1_PreEn_0 + C_GetNextRatesEnergy * ( V_ucRateNo - 1 );
		}
		
		V_usDataEncode = 0;
		V_usLen  = C_EnergyPulseLen;
		V_ucFlayTemp = InF_Read_Data(V_ulID, V_ucBuffer, &V_usLen, &V_usDataEncode );
		if( V_ucFlayTemp == C_OK ) 
		{
			PF_Buffer8ToUlong64(V_ucBuffer, &V_ullEnergy, C_EnergyPulseLen);
			V_ullEnergy += Str_Pulse.V_usReactiveEnergy_T;
			PF_Ulong64ToBuffer8(V_ucBuffer, &V_ullEnergy, C_EnergyPulseLen);
			InF_Write_Data(C_Msg_EnergyMetering, V_ulID, V_ucBuffer, C_EnergyPulseLen, SV_ucEnergySafeFlag);
		}
		else
		{	/*���������ܣ�ֱ���˳�����������������һ���ۼӡ�����оƬ�ڵı��ζ����ĵ���ȫ��������*/
			return;
		}
	}
	
	if( Str_Pulse.V_usReactiveEnergy_A > 0 )				/*�����޹����岻Ϊ0*/
	{
		if( ( Str_Pulse.V_ucPowerDeriction & C_ReactiveDeriction_A ) == 0x00 )							/*��1����*/
		{
			V_ulID = CQua1A_Re_PreEn_0;
		}
		else if( ( Str_Pulse.V_ucPowerDeriction & C_ReactiveDeriction_A ) == C_ActiveDeriction_A )		/*��2����*/
		{
			V_ulID = CQua2A_Re_PreEn_0;
		}
		else if( ( Str_Pulse.V_ucPowerDeriction & C_ReactiveDeriction_A ) == C_ReactiveDeriction_A )	/*��3����*/
		{
			V_ulID = CQua3A_Re_PreEn_0;
		}
		else												/*��4����*/
		{
			V_ulID = CQua4A_Re_PreEn_0;
		}
		
		V_usDataEncode = 0;
		V_usLen  = C_EnergyPulseLen;
		V_ucFlayTemp = InF_Read_Data(V_ulID, V_ucBuffer, &V_usLen, &V_usDataEncode);
		if( V_ucFlayTemp == C_OK ) 
		{
			PF_Buffer8ToUlong64(V_ucBuffer, &V_ullEnergy, C_EnergyPulseLen);
			V_ullEnergy += Str_Pulse.V_usReactiveEnergy_A;
			PF_Ulong64ToBuffer8(V_ucBuffer, &V_ullEnergy, C_EnergyPulseLen);
			InF_Write_Data(C_Msg_EnergyMetering, V_ulID, V_ucBuffer, C_EnergyPulseLen, SV_ucEnergySafeFlag);
		}
		else
		{	/*���������ܣ�ֱ���˳�����������������һ���ۼӡ�����оƬ�ڵı��ζ����ĵ���ȫ��������*/
			return;
		}
	}
	
	if( Str_Pulse.V_usReactiveEnergy_B > 0 )				/*�����޹����岻Ϊ0*/
	{
		if( ( Str_Pulse.V_ucPowerDeriction & C_ReactiveDeriction_B ) == 0x00 )						/*��1����*/
		{
			V_ulID = CQua1B_Re_PreEn_0;
		}
		else if( ( Str_Pulse.V_ucPowerDeriction & C_ReactiveDeriction_B ) == C_ActiveDeriction_B)	/*��2����*/
		{
			V_ulID = CQua2B_Re_PreEn_0;
		}
		else if( ( Str_Pulse.V_ucPowerDeriction & C_ReactiveDeriction_B ) == C_ReactiveDeriction_B)	/*��3����*/
		{
			V_ulID = CQua3B_Re_PreEn_0;
		}
		else												/*��4����*/
		{
			V_ulID = CQua4B_Re_PreEn_0;
		}
		
		V_usDataEncode = 0;
		V_usLen = C_EnergyPulseLen;
		V_ucFlayTemp = InF_Read_Data(V_ulID, V_ucBuffer, &V_usLen, &V_usDataEncode);
		if( V_ucFlayTemp == C_OK ) 
		{
			PF_Buffer8ToUlong64(V_ucBuffer, &V_ullEnergy, C_EnergyPulseLen);
			V_ullEnergy += Str_Pulse.V_usReactiveEnergy_B;
			PF_Ulong64ToBuffer8(V_ucBuffer, &V_ullEnergy, C_EnergyPulseLen);
			InF_Write_Data(C_Msg_EnergyMetering, V_ulID, V_ucBuffer, C_EnergyPulseLen, SV_ucEnergySafeFlag);
		}
		else
		{	/*���������ܣ�ֱ���˳�����������������һ���ۼӡ�����оƬ�ڵı��ζ����ĵ���ȫ��������*/
			return;
		}
	}
	
	if( Str_Pulse.V_usReactiveEnergy_C > 0 )				/*�����޹����岻Ϊ0*/
	{
		if( ( Str_Pulse.V_ucPowerDeriction & C_ReactiveDeriction_C ) == 0x00 )						 /*��1����*/
		{
			V_ulID = CQua1C_Re_PreEn_0;
		}
		else if( ( Str_Pulse.V_ucPowerDeriction & C_ReactiveDeriction_C ) == C_ActiveDeriction_C )	 /*��2����*/
		{
			V_ulID = CQua2C_Re_PreEn_0;
		}
		else if( ( Str_Pulse.V_ucPowerDeriction & C_ReactiveDeriction_C ) == C_ReactiveDeriction_C ) /*��3����*/
		{
			V_ulID = CQua3C_Re_PreEn_0;
		}
		else													/*��4����*/
		{
			V_ulID = CQua4C_Re_PreEn_0;
		}
		
		V_usDataEncode = 0;
		V_usLen = C_EnergyPulseLen;
		V_ucFlayTemp = InF_Read_Data(V_ulID, V_ucBuffer, &V_usLen, &V_usDataEncode);
		if( V_ucFlayTemp == C_OK )
		{
			PF_Buffer8ToUlong64(V_ucBuffer, &V_ullEnergy, C_EnergyPulseLen);
			V_ullEnergy += Str_Pulse.V_usReactiveEnergy_C;
			PF_Ulong64ToBuffer8(V_ucBuffer, &V_ullEnergy, C_EnergyPulseLen);
			InF_Write_Data(C_Msg_EnergyMetering, V_ulID, V_ucBuffer, C_EnergyPulseLen, SV_ucEnergySafeFlag);
		}
		else
		{	/*���������ܣ�ֱ���˳�����������������һ���ۼӡ�����оƬ�ڵı��ζ����ĵ���ȫ��������*/
			return;
		}
	}
	
	if(C_Meter_Type != C_L_SmartMeter)
	{	/*�Ǳ��أ��õ����Ĵ���Ŀǰ���õ����ͽ����õ������ڷǱ��أ�ͨ������õ�������ֱ�ӷ��ء�*/
		return;		/*Զ�̷ѿر�����ܱ�ֱ�ӷ���*/
	}
	else
	{
		/****************************���ر�۷Ѽ���������****************************************/
		
		/*��ȡ�۷�ǰ��ʣ���͸֧���*/
		if( SF_Get_RMoney_DMoney(&V_ullRemainMoney, &V_ullOverDraftMoney) != C_OK )
		{
			return;
		}
		
		V_usDataEncode = 0;
		V_usLen = CLRate_Num;
		if( InF_Read_Data(CRate_Num, &V_ucFlayTemp, &V_usLen, &V_usDataEncode) != C_OK )
		{
			V_ucFlayTemp = 1;		/*��������������Ĭ�������۷�*/
		}
		
		if( V_ucFlayTemp != 0 )
		{
			/*���ʵ��ܿ۷�*/	
			V_ullRateEnergy = SF_Get_RateEnergyForChargeback( V_ucRateNo );
			V_ucSubMoneyFlag1 = SF_RateChargeback(V_ullRateEnergy_F, V_ullRateEnergy, V_ucRateNo);
		}
		else   
		{
			/*ȥ���ʱ���������0�����۷�*/
			V_ucSubMoneyFlag1 = C_NoSubMoneyFlag;
		}
		/*�õ������ۼӼ����ݵ�۵Ŀۼ���*/
		V_ucSubMoneyFlag2 = SF_SettlementEnergy_Metering_L( &Str_Pulse );
		
		/*���б���1��2��͸֧���޴���*/
		if( ( V_ucSubMoneyFlag1 == C_SubMoneyFlag ) || ( V_ucSubMoneyFlag2 == C_SubMoneyFlag ) )
		{
			if( SF_Get_RMoney_DMoney( &V_ullRemainMoney_New, &V_ullOverDraftMoney_New ) != C_OK )
			{
				return;
			}
			
			SF_JudgeWarningStatus(V_ullRemainMoney, V_ullRemainMoney_New, V_ullOverDraftMoney, V_ullOverDraftMoney_New, C_RenewRederict);
			
			/*ˢ�µ�ǰ���*/
			SF_WriteCurrentPrice( );
		}
	}
}

/************************************************************************************************
����ԭ�ͣ�uchar8 SF_RateChargeback(ulong64 V_ullEnergy_F, ulong64 V_ullEnergy, uchar8 V_ucRateNo)
������������ɷ��ʵ�ۿ۷�
���������V_ullEnergy_F���ۼ�ǰ����(������)��
          V_ullEnergy���ۼӺ���� (������)��
          V_ucRateNo ���ʺţ�
�����������
���ز�����C_SubMoneyFlag:��ʾ�۷ѱ�־��
         C_NoSubMoneyFlag����ʾ�޿۷ѱ�־��
����λ�ã����طѿر�۷ѵ���
��    ע��V_ucRateNo ���ʺţ����ñ������ĵط�����ȷ��1-12֮�䣬�����ڲ����жϷ��ʺŵĺϷ���
*************************************************************************************************/
uchar8 SF_RateChargeback(ulong64 V_ullEnergy_F, ulong64 V_ullEnergy, uchar8 V_ucRateNo)
{
	ulong64 V_ullRemainMoney, V_ullRemainMoney_New, V_ullOverDraftMoney, V_ullOverDraftMoney_New;
	ulong64 V_ullFeeDeduction;	    /* ÿ0.01�ȿ۷Ѵ���=��ǰ���*��ѹ���������*������������� */
	ulong64 V_ullPulseConstant;
	ulong32 V_ulCurrentPrice;
	uchar8  V_ucBuffer[8];
	ulong64 V_ullNeedChargebackMoney;
	ushort16 V_usLen, V_usDataEncode;
	
	/****************** ���峣�� ***************************************/
	SF_Read_PulseConstant(&V_ullPulseConstant);											/* ��ȡ�������峣��ulong64��ʽ */
	
	/***************** �ж��Ƿ���۷� **********************************/
	V_ullEnergy_F *= C_EnergyChangeEquivalent_Hundred;			/* ���ﲻ���������λ0.01��*/
	V_ullEnergy *= C_EnergyChangeEquivalent_Hundred;
	
	/* ������ܣ�0.01�� */
	V_ullEnergy_F = V_ullEnergy_F / V_ullPulseConstant;
	V_ullEnergy = V_ullEnergy / V_ullPulseConstant;
	
	if(V_ullEnergy > V_ullEnergy_F)								/* ��0.01�Ƚ�λ����Ҫ�۷Ѳ��� */
	{
		if( SF_Get_RMoney_DMoney( &V_ullRemainMoney, &V_ullOverDraftMoney ) != C_OK )
		{
			return(C_NoSubMoneyFlag);
		}
		
		/********************��ȡ���ʵ�۲�����ǰ���ʵ�۷�д���ݲ�******************/
		/*���V_ulCurrentPrice����λΪ0.0001Ԫ/kWh����0.01��/kWh*/
		V_usDataEncode = 0;
		V_usLen = CLCurr_Rate_Price; 
		if( InF_Read_Data( ( CCurrent_RateFF_Price & 0xFFFFFF00 ) | V_ucRateNo , &V_ucBuffer[0], &V_usLen, &V_usDataEncode ) != C_OK )
		{
			/*Ĭ��0.5Ԫ*/
            memset(&V_ucBuffer[0], 0x00, 4);
			V_ucBuffer[0] = 0x88;
			V_ucBuffer[1] = 0x13;
		}  
		else
		{
			;
		}
		
		InF_Write_Data(C_Msg_EnergyMetering, CCurr_Rate_Price, &V_ucBuffer[0], CLCurr_Rate_Price, C_W_SafeFlag);	/*�������ݲ㵱ǰ���ʵ��*/
		
		PF_BufferXToUlong32(V_ucBuffer, &V_ulCurrentPrice, CLCurr_Rate_Price);
		
		/******************** ��ȡ��ѹ��������������� ******************/
		V_ullFeeDeduction = SF_Get_V_I_Ratio( );
		
		/******************** ���п۷� **********************************/	
		V_ullNeedChargebackMoney = V_ulCurrentPrice * (V_ullEnergy - V_ullEnergy_F);	/*0.01�ȿ۷ѽ��*/
		V_ullNeedChargebackMoney *= V_ullFeeDeduction;		/* ���Ա�Ⱥ�Ŀ۷ѽ�� */
		
		if( V_ullRemainMoney != 0 )
		{	/*����ʣ���Ϊ0*/
			if(V_ullRemainMoney >= V_ullNeedChargebackMoney)
			{
				V_ullRemainMoney_New = V_ullRemainMoney - V_ullNeedChargebackMoney;
				V_ullOverDraftMoney_New = 0;
			}
			else
			{
				V_ullRemainMoney_New = 0;
				V_ullOverDraftMoney_New = V_ullNeedChargebackMoney - V_ullRemainMoney;
			}
		}
		else
		{	/*�ۼ�ǰʣ����Ϊ0*/
			V_ullRemainMoney_New = 0;
			V_ullOverDraftMoney_New = V_ullOverDraftMoney + V_ullNeedChargebackMoney;
		}
		
		/***********************���µ�ʣ���͸֧��д���ݲ�******************************/
		PF_Ulong64ToBuffer8(V_ucBuffer, &V_ullRemainMoney_New, CLCurr_Money);
		InF_Write_Data(C_Msg_EnergyMetering, CChargeBal_Hex_Cent, V_ucBuffer, CLCurr_Money, SV_ucEnergySafeFlag);
		
		PF_Ulong64ToBuffer8(V_ucBuffer, &V_ullOverDraftMoney_New, CLCurr_Money);
		InF_Write_Data(C_Msg_EnergyMetering, COverDraft_Hex_Cent, V_ucBuffer, CLCurr_Money, SV_ucEnergySafeFlag);
		
		return(C_SubMoneyFlag);
	}
	else
	{	/*û��0.01�Ƚ�λ������Ҫ�۷Ѳ���*/
		return(C_NoSubMoneyFlag);
	}
}

/*******************************************************************************
����ԭ�ͣ�void SF_WriteCurrentPrice(void)
�����������������ݲ���ʵ�ۺͽ��ݵ�ۣ�д���ݲ㵱ǰ���
�����������
�����������
���ز�������
����λ�ã����طѿر�۷ѵ���
��    ע��
*******************************************************************************/
void SF_WriteCurrentPrice(void)
{
	uchar8   V_ucBuffer[4];
	ulong32  V_ulCurr_Rate_Price = 0, V_ulCurr_Price_Temp = 0; 
	ushort16 V_usLen, V_usDataEncode;
	
	/*�����ʵ��*/
	V_usDataEncode = 0;
	V_usLen = CLCurr_Rate_Price;
	InF_Read_Data(CCurr_Rate_Price, V_ucBuffer, &V_usLen, &V_usDataEncode);
	PF_BufferXToUlong32(V_ucBuffer, &V_ulCurr_Rate_Price, CLCurr_Rate_Price);
	
	/*�����ݵ��*/
	V_usDataEncode = 0;
	V_usLen = CLCurr_Ladder_Price;
	InF_Read_Data(CCurr_Ladder_Price, V_ucBuffer, &V_usLen, &V_usDataEncode);
	PF_BufferXToUlong32(V_ucBuffer, &V_ulCurr_Price_Temp, CLCurr_Ladder_Price);

	/*����*/
	V_ulCurr_Price_Temp += V_ulCurr_Rate_Price;	/*��ǰ���ʵ��+��ǰ���ݵ�۵õ���ǰ���*/
	PF_Ulong32ToBufferX(V_ucBuffer, &V_ulCurr_Price_Temp, CLCurr_Price);
	
	InF_Write_Data(C_Msg_EnergyMetering, CCurr_Price, &V_ucBuffer[0], CLCurr_Price, C_W_SafeFlag);		   /*��ǰ��۷�д���ݲ�*/	
}

/*******************************************************************************
����ԭ�ͣ�ulong64 SF_Get_V_I_Ratio(void)
������������ȡ��ѹ������������ȳ˻�
�����������
�����������
���ز�����64λ������
����λ�ã����طѿر�۷ѵ���
��    ע��
*******************************************************************************/
ulong64 SF_Get_V_I_Ratio(void)
{
	uchar8  V_ucReturn, V_ucBuffer[10];
	ulong64 V_ullFeeDeduction;
	ulong32 V_ulTemp;
	ushort16 V_usLen, V_usDataEncode;
	
	/**************��ȡ��ѹ������������ȣ����Ի���Ϊ0��Ĭ��Ϊ1****************/
	V_usDataEncode = 0;
	V_usLen = CLRatio_Vol_Tran;
	V_ucReturn = InF_Read_Data(CRatio_Vol_Tran, V_ucBuffer, &V_usLen, &V_usDataEncode);
	if( V_ucReturn != C_OK )				 /*���ݲ��ȡ��������ȷĬ������Ϊ1*/
	{
		V_ullFeeDeduction = 1;
	}
	else
	{
		PF_BufferXToUlong32(V_ucBuffer, &V_ulTemp, CLRatio_Vol_Tran);		/*���������ת��Ϊhex��ʽ*/
		V_ullFeeDeduction = V_ulTemp;	
		if(V_ullFeeDeduction == 0)
		{
			V_ullFeeDeduction = 1;
		}
	}
	
	V_usDataEncode = 0;
	V_usLen = CLRatio_Curr_Tran;
	V_ucReturn = InF_Read_Data(CRatio_Curr_Tran, V_ucBuffer, &V_usLen, &V_usDataEncode);
	if( V_ucReturn != C_OK )			/*���ݲ��ȡ��������ȷĬ������Ϊ1*/
	{
		V_ulTemp = 1;
	}
	else
	{
		PF_BufferXToUlong32(V_ucBuffer, &V_ulTemp, CLRatio_Curr_Tran);		/*���������ת��Ϊhex��ʽ*/
		if(V_ulTemp == 0)
		{
			V_ulTemp = 1;
		}
	}
	
	V_ullFeeDeduction *= V_ulTemp;		/*��ѹ����������������*/
	
    return V_ullFeeDeduction;
}

/*******************************************************************************
����ԭ�ͣ�ulong64 SF_Get_RateEnergyForChargeback(uchar8 V_ucRateNo)
�������������ݷ��ʺţ���ȡ���ݲ�ķ��ʵ�����������
���������V_ucRateNo:���ʺ�
�����������
���ز�����8�ֽ�������
����λ�ã����طѿر�۷ѵ���
��    ע��1�������������������ۼ�0��
		 2��������ʵ��ܲ��á���+�����ķ�ʽ�����������״̬�֡�
		 3��V_ucRateNo�ڵ�����������ĵط�����ȷ����1-12֮�䣬�����ڲ����жϷ��ʺźϷ���
*******************************************************************************/
ulong64 SF_Get_RateEnergyForChargeback(uchar8 V_ucRateNo)
{
	ulong64	V_ullRateEnergy = 0;
	ulong64	V_ullRev_RateEnergy = 0;
	ulong32	V_ulOAD;
	uchar8	V_ucBuffer[C_EnergyPulseLen];
	ushort16 V_usLen, V_usDataEncode;	
	
	/*�������������*/
	V_ulOAD = CPos_Ac_T1_PreEn_0 + C_GetNextRatesEnergy * ( V_ucRateNo - 1 );
	V_usDataEncode = 0;
	V_usLen = C_EnergyPulseLen;
	if( InF_Read_Data(V_ulOAD, V_ucBuffer, &V_usLen, &V_usDataEncode) != C_OK )
	{
		memset(V_ucBuffer, 0x00, C_EnergyPulseLen);
	}	
	PF_Buffer8ToUlong64(V_ucBuffer, &V_ullRateEnergy, C_EnergyPulseLen);
	
	/*�������������*/		
	V_ulOAD = CRev_Ac_T1_PreEn_0 + C_GetNextRatesEnergy * ( V_ucRateNo - 1 );
	V_usDataEncode = 0;
	V_usLen = C_EnergyPulseLen;
	if( InF_Read_Data(V_ulOAD, V_ucBuffer, &V_usLen, &V_usDataEncode) != C_OK)
	{
		memset(V_ucBuffer, 0x00, C_EnergyPulseLen);
	}	
	PF_Buffer8ToUlong64(V_ucBuffer, &V_ullRev_RateEnergy, C_EnergyPulseLen);
	
	/*��+��*/
	V_ullRateEnergy = V_ullRateEnergy + V_ullRev_RateEnergy;

	return(V_ullRateEnergy);
		
}

/*******************************************************************************
����ԭ�ͣ�uchar8 SF_Get_RMoney_DMoney(ulong64 *pV_ullRemainMoney, ulong64 *pV_ullOverDraftMoney)
������������ȡ���ݲ㵱ǰ��ʣ���͸֧���
���������pV_ullRemainMoney:ʣ����Ļ����ַ��
          pV_ullOverDraftMoney:͸֧�����ַ
���������*pV_ullRemainMoney:ʣ�����λΪ0.000001Ԫ��ʽHex
          *pV_ullOverDraftMoney:͸֧����λΪ0.000001Ԫ��ʽHex
���ز�����C_OK/C_Error
����λ�ã����طѿر�۷ѵ���
��    ע��
*******************************************************************************/
uchar8 SF_Get_RMoney_DMoney(ulong64 *pV_ullRemainMoney, ulong64 *pV_ullOverDraftMoney)
{
	uchar8 V_ucReturn;
	uchar8 V_ucBuffer[10];
	ushort16 V_usLen, V_usDataEncode;		
	
	/*****************ʣ�����λ0.000001Ԫ***********************/
	V_usDataEncode = 0;
	V_usLen = CLCurr_Money;
	V_ucReturn = InF_Read_Data( CChargeBal_Hex_Cent, V_ucBuffer, &V_usLen, &V_usDataEncode );
	if( V_ucReturn != C_OK ) 	   
	{
		return C_Error;
	}
	else
	{
		PF_Buffer8ToUlong64(V_ucBuffer, pV_ullRemainMoney, CLCurr_Money); 		/*ʣ����ת��Ϊulong64��ʽ*/
	}
	
	/*****************͸֧����λ0.000001Ԫ***********************/
	V_usDataEncode = 0;
	V_usLen = CLCurr_Money;
	V_ucReturn = InF_Read_Data( COverDraft_Hex_Cent, V_ucBuffer, &V_usLen, &V_usDataEncode );
	if(V_ucReturn != C_OK) 			
	{
		return C_Error;
	}
	else
	{
		PF_Buffer8ToUlong64(V_ucBuffer, pV_ullOverDraftMoney, CLCurr_Money);     /*͸֧���ת��Ϊulong64��ʽ*/
	}
	return(C_OK);
}

/*******************************************************************************
����ԭ�ͣ�uchar8 InF_EnergyMetering_Message(Str_Msg_Parameter *pStr_Msg_Parameter)
����������������Ϣ������
���������pStr_Msg_Parameterָ����Ϣ��ȡ���ŵľ�̬����
����������� 
���ز�����C_OK��ȷ����C_Error��������д���
����λ�ã�����500ms��ʱ�������õ���
��    ע��
*******************************************************************************/
uchar8 InF_EnergyMetering_Message(Str_Msg_Parameter *pStr_Msg_Parameter)
{
	SV_ucEnergySafeFlag = 0;
	
	if( pStr_Msg_Parameter->PowerFlag != C_PowerOn )
	{
		return C_Error;
	}
	
	if ( ( pStr_Msg_Parameter->SourceAddr 	== C_Msg_Dispatch )
	  && ( pStr_Msg_Parameter->DerictAddr 	== C_Msg_EnergyMetering )
	  && ( pStr_Msg_Parameter->Parameter[0] == Pt_Dispatch_Timing ) )			/*��ϢԴ��ַ��Ŀ�ĵ�ַ����Ϣ���;���ȷ����ȫ��־��1*/
	{
		SV_ucEnergySafeFlag |= C_W_SafeFlag_1;
		SF_Energy_Metering( );
	}
	else if ( ( pStr_Msg_Parameter->DerictAddr 	  == C_Msg_EnergyMetering )		/*Ŀ����ϢΪ���ܼ���*/
		    && ( pStr_Msg_Parameter->Parameter[0] == Pt_ParaMetersChange ) 	
			&& ( pStr_Msg_Parameter->Parameter[1] == C_ReworkWarningPara ) )	/*�����ı���Ϣ����*/
	{	
		SV_ucEnergySafeFlag |= C_W_SafeFlag_1;	
		SF_ReworkWarningPara( );	
	}	
	else if ( ( ( pStr_Msg_Parameter->DerictAddr	== C_Msg_EnergyMetering )	/*Ŀ����ϢΪ���ܼ���*/
		      && ( pStr_Msg_Parameter->Parameter[0] == Pt_RatePrice ) )			/*ÿ���Ӹ��·��ʡ����ݡ���ǰ���*/
		   || ( ( pStr_Msg_Parameter->DerictAddr 	== C_Msg_BroadcastAddress )	/*�㲥��Ϣ*/
		      && ( pStr_Msg_Parameter->Parameter[0] == Pt_MeterClear ) && ( C_Meter_Type == C_L_SmartMeter ) ) )	/*���������Ϣ��Ϊ���ر�*/
	{
		SF_UpdateCurrentPrice( );
	}
	else
	{
		return C_Error;
	}

	SV_ucEnergySafeFlag = 0;
	
    return C_OK;
}

/*******************************************************************************
����ԭ�ͣ�uchar8 InF_ReturnMoneyFromPurchase(ulong32 V_ulBuyMoney, uchar8 V_ucSafeFlag)
�����������˷Ѵ������˷Ѻ�ʣ���͸֧��д���ݲ�
���������V_ulBuyMoney,�˷ѽ�hex��ʽ����λ0.01Ԫ;
		  V_ucSafeFlag,��ȫ��־;
�����������
���ز�����C_OK��ʾ�˷ѳɹ���ʣ���͸֧������������բ�����Ѿ��ɹ�
          C_NoAccess��ʾ��Ȩ�ޣ�C_SafeFlagError��ʾ��ȫ��־��C_Error��ʾ��������
����λ�ã�ͨ���˷�ʱ����
��    ע��
*******************************************************************************/
uchar8 InF_ReturnMoneyFromPurchase(ulong32 V_ulBuyMoney, uchar8 V_ucSafeFlag)
{
	ulong64 V_ullRemainingMoney, V_ullRemainingMoney_L, V_ullOverdraftMoney;
	ulong64 V_ullReturnMoney;
	uchar8  V_ucTurn, V_ucBuffer[6];
    
    if( V_ucSafeFlag != C_W_SafeFlag )
    {
        return C_SafeFlagError;
    }
	
	/***********************�˷ѽ��Ĵ���********************************/
	V_ullReturnMoney = V_ulBuyMoney;
	V_ullReturnMoney *= C_MoneyChangeEquivalent;	  /*ת��Ϊ�����ݲ���ͬ��ʽ,0.0001�ֵ�hex��ʽ*/
	
	/******************��ȡ���ݲ�ʣ�����λ0.0001�ֵ�hex��ʽ*********************************/
	/******************��ȡ���ݲ�͸֧����λ0.0001�ֵ�hex��ʽ*********************************/
	V_ucTurn = SF_Get_RMoney_DMoney(&V_ullRemainingMoney, &V_ullOverdraftMoney); 
	if(V_ucTurn != C_OK)
	{
		return V_ucTurn;
	}

    /******************�ж��Ƿ������˷�**********************************************************/
    if ( ( V_ullReturnMoney > V_ullRemainingMoney )      		/*�˷ѽ�����ԭ��ʣ����*/
      || ( V_ullOverdraftMoney > 0 ) )                   		/*͸֧��Ϊ0*/
    {
        return C_NoAccess;
    }
	
    /******************�����˷Ѻ�ʣ�����λ0.0001�ֵ�hex��ʽ*********************************/
    V_ullRemainingMoney_L = V_ullRemainingMoney - V_ullReturnMoney;
    V_ullOverdraftMoney = 0;    /*͸֧���Ϊ0*/
	
	/*************�жϱ�����Ԥ��բ������͸֧��������բ״̬,��ڲ���Ϊ��λ0.000001Ԫ��hex��ʽ****/
	SF_JudgeWarningStatus(V_ullRemainingMoney, V_ullRemainingMoney_L, 0, V_ullOverdraftMoney, C_RenewDerict);	/*�۷�ǰ͸֧���ֱ��д0����Ϊ������ʣ���������²����˷ѣ���˿۷�ǰ͸֧���һ��Ϊ0*/

	/***********************��ʣ���͸֧��д���ݲ㣬��λ0.0001�ֵ�hex��ʽ**************/
	PF_Ulong64ToBuffer8(V_ucBuffer,&V_ullRemainingMoney_L, C_EnergyPulseLen);		/*ʣ����*/
	V_ucTurn = InF_Write_Data(C_Msg_EnergyMetering, CChargeBal_Hex_Full, V_ucBuffer, CLChargeBal_Hex_Full, V_ucSafeFlag);
	if(V_ucTurn != C_OK)
	{
		return C_Error;
	}

	PF_Ulong64ToBuffer8(V_ucBuffer, &V_ullOverdraftMoney, C_EnergyPulseLen);		/*͸֧���*/
	V_ucTurn = InF_Write_Data(C_Msg_EnergyMetering, COverDraft_Hex_Full, V_ucBuffer, CLOverDraft_Hex_Full, V_ucSafeFlag);
	if(V_ucTurn != C_OK)
	{
		return C_Error;
	}
	return C_OK;
}

/*******************************************************************************
����ԭ�ͣ�void SF_ReworkWarningPara(void)
���������������޸ĺ��жϵ�ǰ������͸֧����բ״̬
�����������	
�����������	
���ز�������	
����λ�ã�����ģ����Ϣ������
��    ע��
*******************************************************************************/
void SF_ReworkWarningPara(void)
{
	ulong64  V_ullRemainingMoney, V_ullOverdraftMoney;
	uchar8   V_ucBuffer[CLCurrent_Ladder_Table];
	ushort16 V_usLen, V_usDataEncode;
        	
	/******************��ȡ���ݲ�ʣ���͸֧���,��λ0.000001Ԫ��hex��ʽ************************/
	V_usDataEncode = 0;
	V_usLen = C_EnergyPulseLen;
	if( InF_Read_Data( CChargeBal_Hex_Cent, V_ucBuffer, &V_usLen, &V_usDataEncode) != C_OK )	/*ʣ����*/
	{
		return;
	}
	PF_Buffer8ToUlong64(V_ucBuffer, &V_ullRemainingMoney, C_EnergyPulseLen);
	SV_ucEnergySafeFlag |= C_W_SafeFlag_2;
	
	V_usDataEncode = 0;
	V_usLen = C_EnergyPulseLen;
	if( InF_Read_Data(COverDraft_Hex_Cent, V_ucBuffer, &V_usLen, &V_usDataEncode) != C_OK )		/*͸֧���*/
	{
		return;
	}
	PF_Buffer8ToUlong64(V_ucBuffer, &V_ullOverdraftMoney, C_EnergyPulseLen);
	SV_ucEnergySafeFlag |= C_W_SafeFlag_3;
	
	/*********************�жϱ�����Ԥ��բ������͸֧��������բ״̬***********************/
	if( SV_ucEnergySafeFlag != ( C_W_SafeFlag_1 | C_W_SafeFlag_2 | C_W_SafeFlag_3 ) )
	{
		return;
	}
	
	SF_JudgeWarningStatus(V_ullRemainingMoney, V_ullRemainingMoney, 0, V_ullOverdraftMoney, C_RenewDerict);		/*����۷�ǰ͸֧���д��0����֤͸֧��Ϊ0��ʱ�����͸֧����*/
}

/*******************************************************************************
����ԭ�ͣ�void SF_UpdateCurrentPrice(void)
�����������������ݲ㵱ǰ���ʵ�ۡ����ݵ�ۡ���ǰ���
�����������	
�����������	
���ز�������	
����λ�ã�����ģ����Ϣ������
��    ע��
*******************************************************************************/
void SF_UpdateCurrentPrice(void)
{
	uchar8  V_ucBuffer[CLCurrent_Ladder_Table];
    uchar8  V_ucCurrentStepType, V_ucEnergy[10];
    ulong32 V_ulEnergy_F, V_ulCurrentPrice;
	uchar8	V_ucRateNo;
	ushort16 V_usLen, V_usDataEncode = 0;
        
	/* ��ȡ��ǰ�׽��ݱ���������жϵ�ǰ�������� */
	V_usDataEncode = 0;
	V_usLen = CLCurrent_Ladder_Table;
	if( InF_Read_Data(CCurrent_Ladder_Table, V_ucBuffer, &V_usLen, &V_usDataEncode) == C_OK )		/* ��ȡ��ǰ�׽��ݱ���� */
	{
		V_ucCurrentStepType = SF_Judge_CurrentStep_Type(&V_ucBuffer[C_StepSettlementStartAddr]);	/* �жϵ�ǰ�������� */
	}
	else
	{
		V_ucCurrentStepType = C_InValidStep;
	}
	
	/* ���ݵ�ǰ�������Ͷ�ȡ��Ӧ���� */
	V_ulEnergy_F = 0;
	V_usLen  = CLY_Com_Ac_Tol_En_0;
	if( V_ucCurrentStepType == C_ValidStep )					/* ��ȡ���ݽ����õ��� */
	{
		if( InF_Get_EnergyModule(CY_Com_Ac_Tol_En_0, V_ucEnergy, &V_usLen, &V_usDataEncode) == C_OK )
		{
			PF_BufferXToUlong32(V_ucEnergy, &V_ulEnergy_F, CLY_Com_Ac_Tol_En_0);
		}
		else
		{
			V_ulEnergy_F = 0;	
		}
	}
	
	/* �������ݲ㵱ǰ���ݵ�ۼ�ˢ����ʾ */
	SF_Judge_CurrentStep(V_ulEnergy_F, &V_ulCurrentPrice, V_ucBuffer, V_ucCurrentStepType);
	
	/* �ж��Ƿ���ȥ���ʣ�ȥ���ʱ��۷ѣ���ǰ���ʵ��Ϊ0 */
	V_usDataEncode = 0;
	V_usLen = CLRate_Num;
	if( InF_Read_Data( CRate_Num, &V_ucRateNo, &V_usLen, &V_usDataEncode) != C_OK )
	{
		V_ucRateNo = 1;
	}	
	
	if( V_ucRateNo == 0 )  
	{
		memset( V_ucBuffer, 0x00, CLCurr_Rate_Price );
	}
	else
	{
	
		/* �������ݲ���ʵ�� */
		/* ��ȡ��ǰ���� */
		V_usDataEncode = 0;
		V_usLen = CLCurr_Rate_No;
		if( InF_Read_Data(CCurr_Rate_No, &V_ucRateNo, &V_usLen, &V_usDataEncode) != C_OK )
		{
			V_ucRateNo = 1;
		}
		if( ( V_ucRateNo == 0 ) || ( V_ucRateNo > C_MaxRatesNum ) )
		{
			V_ucRateNo = 1;
		}
		
		/* ����ǰ���ʵ�۷�д���ݲ� */
		V_usDataEncode = 0;
		V_usLen = CLCurr_Rate_Price;	
		if( InF_Read_Data( ( CCurrent_RateFF_Price & 0xFFFFFF00 ) | V_ucRateNo, V_ucBuffer, &V_usLen, &V_usDataEncode ) != C_OK )
		{
			memset(V_ucBuffer, 0x00, 4);	/*����������Ĭ��0.5Ԫ*/
			V_ucBuffer[0] = 0x88;
			V_ucBuffer[1] = 0x13;
		}
		
	}
	
	InF_Write_Data(C_Msg_EnergyMetering, CCurr_Rate_Price, V_ucBuffer, CLCurr_Rate_Price, C_W_SafeFlag);
	
	/* ˢ�����ݲ�ĵ�ǰ��� */
	SF_WriteCurrentPrice( );
}

/*******************************************************************************
����ԭ�ͣ�uchar8 SF_CheckMoneyToPurchaseFlag(void)
���������������־SV_ucMoneyToPurchaseFlag CRC��־У�飻��У������򹺵��־���㡣
���������SV_ucMoneyToPurchaseFlag,ȫ�ֹ����־��
�����������
���ز������Ƿ񹺵�:C_MoneyToPurchase����,C_NoMoneyToPurchaseû�й���
����λ�ã�����ģ�鱨���жϺ���	
��    ע���ñ�־�ڹ����ʱ��������,��⵽��������ڱ������2������
*******************************************************************************/
uchar8 SF_CheckMoneyToPurchaseFlag(void)
{
	if( PF_Check_CRC(SV_ucMoneyToPurchaseFlag, ( C_MoneyToPurchaseFlagLen + 2 ) ) != C_OK )
	{
		SF_SetMoneyToPurchaseFlag( C_NoMoneyToPurchase );		/* �����־���� */
	}
	
	if( SV_ucMoneyToPurchaseFlag[0] == C_MoneyToPurchase )
	{
		return C_MoneyToPurchase;
	}
	else
	{
		return C_NoMoneyToPurchase;
	}
}

/*******************************************************************************
����ԭ�ͣ�void SF_SetMoneyToPurchaseFlag(uchar8 V_ucPurchaseFlag)
�����������ù����־���幺���־
���������V_ucPurchaseFlag: C_MoneyToPurchase,���磻C_NoMoneyToPurchase��δ���磻
�����������
���ز�������
����λ�ã���ֵ��Ǯ����ʼ�����жϱ���״̬
��    ע��
*******************************************************************************/
void SF_SetMoneyToPurchaseFlag(uchar8 V_ucPurchaseFlag)
{
	ushort16 V_usCRC;
	
	SV_ucMoneyToPurchaseFlag[0] = V_ucPurchaseFlag;
	V_usCRC = PF_Cal_CRC(SV_ucMoneyToPurchaseFlag, C_MoneyToPurchaseFlagLen);
	PF_Ushort16ToBuffer2(&SV_ucMoneyToPurchaseFlag[1], &V_usCRC);	
}

