/*********************************************************************************
Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     Demand.c
Version:       V1
Author:        
Date:          2014-3-12
Description:   ������������ļ�
----------------------------------------------------------------------------------
History1:      ��1���޸�
����1. Date:   20211019
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
*********************************************************************************/

#include "Public.h"
#include "Demand.h"

/*--------------------------------------------------------------------------*/
/* ȫ�ֱ��� */
/*--------------------------------------------------------------------------*/
ushort16 SV_usActiveRateDemandIntervalTimer_T;						/* ���й������������ڶ�ʱ�� */
ushort16 SV_usReactiveRateDemandIntervalTimer_T;					/* ���޹������������ڶ�ʱ�� */
uchar8	 SV_ucActiveDemandIntervalTimer_T;							/* ���й��������ڶ�ʱ�� */
uchar8	 SV_ucReactiveDemandIntervalTimer_T;						/* ���޹��������ڶ�ʱ�� */
uchar8	 SV_ucActiveDemandIntervalTimer_SePhase[3];					/* �����й��������ڶ�ʱ��,�ֱ��ӦA��B��C */
uchar8	 SV_ucReactiveDemandIntervalTimer_SePhase[3];				/* �����޹��������ڶ�ʱ��,�ֱ��ӦA��B��C */
			                                                           
ulong32	 SV_ulActivePower_T[C_1minAvaragePowerNum]@".DataProcessADDR";					/* ����1min�й�ƽ�����ʣ����60min���� */
ulong32	 SV_ulReactivePower_T[C_1minAvaragePowerNum]@".DataProcessADDR";				/* ����1min�� ��ƽ�����ʣ����60min���� */
ulong32	 SV_ulActivePower_SePhase[3][C_1minAvaragePowerNum];		/* ����1min�й�ƽ�����ʣ����60min����,�ֱ��ӦA��B��C */
ulong32	 SV_ulReactivePower_SePhase[3][C_1minAvaragePowerNum];		/* ����1min�� ��ƽ�����ʣ����60min����,�ֱ��ӦA��B��C */

uchar8   SV_ucPowerDirection;						  				/* 1minƽ�������ۼӺͷ��� */

uchar8	 SV_ucDemandSafe;							  				/* ����������ȫ��־�� */
/*--------------------------------------------------------------------------*/

/* ������� */
const ulong32 C_ComDemandCodeTable[ ][2]=
{
	CCom_Re1_De_FF_0,		CQua1_Re_De_FF_0,
	CCom_Re2_De_FF_0,		CQua1_Re_De_FF_0,
	
	CComA_Re1_De_FF_0,		CQua1A_Re_De_FF_0,
	CComA_Re2_De_FF_0,		CQua1A_Re_De_FF_0,
	
	CComB_Re1_De_FF_0,		CQua1B_Re_De_FF_0,
	CComB_Re2_De_FF_0,		CQua1B_Re_De_FF_0,
	
	CComC_Re1_De_FF_0,		CQua1C_Re_De_FF_0,
	CComC_Re2_De_FF_0,		CQua1C_Re_De_FF_0
};
#define C_DemandCodeTableLen   ( (sizeof(C_ComDemandCodeTable) / 2 ) / sizeof(ulong32) )

const SStr_DemandPowerAddr_Type C_ComDemandRAMAddeTable[ ]=
{
	{SV_ulActivePower_T,							COneMin_AcPower_Pre},
	{SV_ulActivePower_SePhase[C_APhasePosition],	COneMin_AcPower_A_Pre},
	{SV_ulActivePower_SePhase[C_BPhasePosition],	COneMin_AcPower_B_Pre},
	{SV_ulActivePower_SePhase[C_CPhasePosition],	COneMin_AcPower_C_Pre},
	{SV_ulReactivePower_T,							COneMin_RePower_Pre},
	{SV_ulReactivePower_SePhase[C_APhasePosition],	COneMin_RePower_A_Pre},
	{SV_ulReactivePower_SePhase[C_BPhasePosition],	COneMin_RePower_B_Pre},
	{SV_ulReactivePower_SePhase[C_CPhasePosition],	COneMin_RePower_C_Pre}
};
#define C_PowerTypeNum	( ( sizeof( C_ComDemandRAMAddeTable ) ) / sizeof( SStr_DemandPowerAddr_Type ) )

/* ��ǰ�������ݱ�ʶ�жϱ�־ */
const uchar8 C_ActiveCodeIDTable[3]   = { C_A_ActiveCodeID, C_B_ActiveCodeID, C_C_ActiveCodeID };
const uchar8 C_ReactiveCodeIDTable[3] = { C_A_ReactiveCodeID, C_B_ReactiveCodeID, C_C_ReactiveCodeID };

/*******************************************************************************
����ԭ�ͣ�void InF_DemandInit(void)
�����������ϵ���������ڲ���̬������ʼ��
�����������
�����������
���ز�������
����λ�ã������ϵ��ʼ��ʱ����	
��    ע��
*******************************************************************************/
void InF_DemandInit(void)
{	
	/* �����������ڶ�ʱ����ʼ�� */
	SF_InitDemandTimer(C_DemandPowerUp);	
	
	/* ���½���1minƽ�����ʳ�ʼ�� */
	memset(SV_ulActivePower_T,         0x00, sizeof( SV_ulActivePower_T ) );
	memset(SV_ulReactivePower_T,       0x00, sizeof( SV_ulReactivePower_T ) );
	memset(SV_ulActivePower_SePhase,   0x00, sizeof( SV_ulActivePower_SePhase ) );
	memset(SV_ulReactivePower_SePhase, 0x00, sizeof( SV_ulReactivePower_SePhase ) );
		
	SV_ucPowerDirection	= 0;
	
	/* ��ȫ�ֽ����� */
	SV_ucDemandSafe = 0;
	
	/* ��ǰ�������� */
	SF_Clear_CurrentDemand( );	/* ����ǰ�������� */
}

/*******************************************************************************
����ԭ�ͣ�void SF_Set_DemandInternal(uchar8 V_ucDemand, uchar8 V_ucTDemandTimerInitFlag) 
������������ʼ������������ʱ��
���������V_ucDemand:�������ڣ�
		  V_ucTDemandTimerInitFlag:���й������޹�������ʱ���Ƿ��ʼ����־��
									C_TDemandTimerInit_Flag����ʼ�����й������޹�������ʱ��
									C_TDemandTimerNoInit_Flag������ʼ�����й������޹�������ʱ��
�����������
���ز�������
����λ�ã���ʼ������������ʱ����	
��    ע��
*******************************************************************************/
void SF_Set_DemandInternal(uchar8 V_ucDemand, uchar8 V_ucTDemandTimerInitFlag) 
{
	uchar8 V_uci;
	
	if( V_ucTDemandTimerInitFlag == C_TDemandTimerInit_Flag)
	{
		SV_usActiveRateDemandIntervalTimer_T   = 0x0100;
		SV_usReactiveRateDemandIntervalTimer_T = 0x0100;	
	}
	
	SV_usActiveRateDemandIntervalTimer_T   = (SV_usActiveRateDemandIntervalTimer_T & 0xFF00) + V_ucDemand;
	SV_usReactiveRateDemandIntervalTimer_T = (SV_usReactiveRateDemandIntervalTimer_T & 0xFF00) + V_ucDemand;	/*���ʶ�ʱ��������������Ĭ����������+1*/
	SV_ucActiveDemandIntervalTimer_T   = V_ucDemand;
	SV_ucReactiveDemandIntervalTimer_T = V_ucDemand;
	
	for( V_uci = 0; V_uci < 3; V_uci++ )
	{
		SV_ucActiveDemandIntervalTimer_SePhase[V_uci] = V_ucDemand;
		SV_ucReactiveDemandIntervalTimer_SePhase[V_uci] = V_ucDemand;
	}
}

/**********************************************************************************************************
����ԭ�ͣ�void SF_InitDemandTimer(uchar8 V_ucFlay)
������������ʼ����������
���������V_ucFlay = C_ReworkTime��ʾ�޸�ʱ��,
				   = C_ReDemand_Cycle��ʾ�޸������������,
 				   = C_MeterClear��ʾ�������,=C_DemandClear��ʾ��������,
 				   = C_Settlement��ʾ��������,=C_RatesChanged���ʸı�,
                   = C_DemandPowerUp��ʾ�ϵ�,=C_DerictionChange_AT�����й����ʷ���ı�,
                   = C_DerictionChange_RT�����޹����ʸı�,
                   = C_DerictionChange_AA��ʾA���й����ʸı䣬
                   = C_DerictionChange_AB��ʾB���й����ʷ���ı�,
				   = C_DerictionChange_AC��ʾC���й����ʷ���ı䣬
				   = C_DerictionChange_RA��ʾA���޹����ʷ���ı�,
                   = C_DerictionChange_RB��ʾB���޹����ʷ���ı䣬
                   = C_DerictionChange_RC��ʾC���޹����ʷ���ı�,
                   = C_Settlement_ReSettle_Day1��ʾ�޸ĵ�һ�����գ�������,
�����������
���ز�������
����λ�ã�����������Ҫ���¼���ʱ����
��    ע��
*********************************************************************************************************/
void SF_InitDemandTimer(uchar8 V_ucFlay)
{
	uchar8	 V_ucDemand, V_uci, V_ucBuffer[CLDate_Time];
	ushort16 V_usLen, V_usDataEncode;

    /* �������ݲ�ӿں�������������������� */
	V_usDataEncode = 0;
	V_usLen = CLDemand_Cycle;
	if( InF_Read_Data(CDemand_Cycle, &V_ucDemand, &V_usLen, &V_usDataEncode) != C_OK )
	{
		V_ucDemand = C_NormalDemandInterval;					/* ����������ڶ�����Ĭ��15min */
	}
	
	V_usDataEncode = 0;
	V_usLen = CLDate_Time;
	InF_Read_Data(CDate_Time, V_ucBuffer, &V_usLen, &V_usDataEncode);
	
	V_uci = 0;
    if(V_ucFlay != C_Settlement)           /* �޸ĵ�һ������C_Settlement_ReSettle_Day1��Ҫ���� */
	{
        if(V_ucBuffer[0] > 1)			   
        {
            V_uci = 1;
        }
    }
    else
    {
        ;    /* ��������C_Settlement���ж��� */
    }
    
	if( (V_ucFlay == C_DemandClear)          /* �޸�ʱ�䡢�޸��������ڡ��������㡢������� */
	 || ( (V_ucFlay >= C_DerictionChange_AT) && (V_ucFlay <= C_DerictionChange_RC) ) )   /* ���ʷ���ı䣬������ʱ��Ҳֱ�Ӽ�1 */
	{
		V_uci = 1;
	}
	
	V_ucDemand += V_uci;					/* ����������ڼ���i����ʾ���������������ڼ�1 */

	memset(&V_ucBuffer[0], 0x00, CL_Demand);
	
	switch(V_ucFlay)
	{
		case C_DemandPowerUp:
		{
			SF_Set_DemandInternal(V_ucDemand, C_TDemandTimerInit_Flag);		/* ��ʼ����ʱ�� */
        }break;
		case C_ReworkTime:
		case C_ReDemand_Cycle:
		case C_MeterClear:
		case C_DemandClear:
		/*case C_Settlement:	���㲻�ģ�������ԭ�����죬����buffer����*/
		{
			SF_Set_DemandInternal(V_ucDemand, C_TDemandTimerNoInit_Flag);	/* ��ʼ����ʱ�� */
			
            SF_Clear_CurrentDemand();	            /* ����ǰ�������� */
		
			/* ���½���������buffer��1min�ۼӺͼ��������� */
			memset(SV_ulActivePower_T,         0x00, sizeof( SV_ulActivePower_T ) );
			memset(SV_ulReactivePower_T,       0x00, sizeof( SV_ulReactivePower_T ) );
			memset(SV_ulActivePower_SePhase,   0x00, sizeof( SV_ulActivePower_SePhase ) );
			memset(SV_ulReactivePower_SePhase, 0x00, sizeof( SV_ulReactivePower_SePhase ) );
						
		}break;
		case C_Settlement:
        case C_Settlement_ReSettle_Day1:
		{
			
			SF_Set_DemandInternal(V_ucDemand, C_TDemandTimerNoInit_Flag);	/* ��ʼ����ʱ�� */
            SF_Clear_CurrentDemand();	           /* ����ǰ�������� */
            
		}break;
		case C_RatesChanged:
		{
			V_usDataEncode = 0;
			V_usLen = CLCurr_Rate_No;
			if( InF_Read_Data(CCurr_Rate_No, V_ucBuffer, &V_usLen, &V_usDataEncode ) != C_OK)
			{
				V_ucBuffer[0] = C_NormalRate;
			}
			
			if( (V_ucBuffer[0] == 0) || (V_ucBuffer[0] > C_MaxRatesNum) )
			{
				V_ucBuffer[0] = C_NormalRate;
			}
						
			SV_usActiveRateDemandIntervalTimer_T = 0;
			SV_usActiveRateDemandIntervalTimer_T |= (ushort16)V_ucBuffer[0];
			SV_usActiveRateDemandIntervalTimer_T <<= 8;
			SV_usActiveRateDemandIntervalTimer_T += V_ucDemand;
			SV_usReactiveRateDemandIntervalTimer_T = 0;
			SV_usReactiveRateDemandIntervalTimer_T |= (ushort16)V_ucBuffer[0];
			SV_usReactiveRateDemandIntervalTimer_T <<= 8;
			SV_usReactiveRateDemandIntervalTimer_T += V_ucDemand;
			
		}break;
		case C_DerictionChange_AT:
		{
			SV_usActiveRateDemandIntervalTimer_T = (SV_usActiveRateDemandIntervalTimer_T & 0xFF00) + V_ucDemand;
			SV_usReactiveRateDemandIntervalTimer_T = (SV_usActiveRateDemandIntervalTimer_T & 0xFF00) + V_ucDemand;	/*���ʶ�ʱ��������������Ĭ����������+1*/
			SV_ucActiveDemandIntervalTimer_T = V_ucDemand;
			SV_ucReactiveDemandIntervalTimer_T = V_ucDemand;

            SF_Clear_CurrentDemand();	/* ����ǰ�������� */
            
		}break;
		case C_DerictionChange_RT:
		{
			SV_usReactiveRateDemandIntervalTimer_T = (SV_usActiveRateDemandIntervalTimer_T & 0xFF00) + V_ucDemand;	/*���ʶ�ʱ��������������Ĭ����������+1*/
			SV_ucReactiveDemandIntervalTimer_T = V_ucDemand;
			
            InF_Write_Data(C_Msg_DemandMetering,CCurr_ReDemand, &V_ucBuffer[0], CCurr_AcDemandLen, C_W_SafeFlag);	/*��ǰ�޹���������*/
            
		}break;
		case C_DerictionChange_AA:
		{
			SV_ucActiveDemandIntervalTimer_SePhase[C_APhasePosition] = V_ucDemand;
			SV_ucReactiveDemandIntervalTimer_SePhase[C_APhasePosition] = V_ucDemand;
			
		}break;
		case C_DerictionChange_AB:
		{
			SV_ucActiveDemandIntervalTimer_SePhase[C_BPhasePosition] = V_ucDemand;
			SV_ucReactiveDemandIntervalTimer_SePhase[C_BPhasePosition] = V_ucDemand;
			
		}break;
		case C_DerictionChange_AC:
		{
			SV_ucActiveDemandIntervalTimer_SePhase[C_CPhasePosition] = V_ucDemand;
			SV_ucReactiveDemandIntervalTimer_SePhase[C_CPhasePosition] = V_ucDemand;
			
		}break;
		case C_DerictionChange_RA:
		{
			
			SV_ucReactiveDemandIntervalTimer_SePhase[C_APhasePosition] = V_ucDemand;
			
		}break;
		case C_DerictionChange_RB:
		{
			
			SV_ucReactiveDemandIntervalTimer_SePhase[C_BPhasePosition] = V_ucDemand;
			
		}break;
		case C_DerictionChange_RC:
		{
			
			SV_ucReactiveDemandIntervalTimer_SePhase[C_CPhasePosition] = V_ucDemand;
			
		}break;
		default:
		break;
	}
}

/****************************************************************************************************************************
����ԭ�ͣ�void SF_1minPerPowerSum_Direction(uchar8 V_ucCurrentDeriction, uchar8 V_ucDerictionFlag, uchar8 V_ucDemandTimerClearFlag)
�����������ж�1minƽ�����ʷ��򣬷���ı��������ڶ�ʱ������
���������V_ucCurrentDeriction����ǰ���ʷ���
		  V_ucDerictionFlag����ǰ���ʶ�Ӧλ��
		  V_ucDemandTimerClearFlag��������ʱ�������־��
�����������
���ز�������
����λ�ã�����ģ��ÿ1s����1��
��    ע��
*****************************************************************************************************************************/
void SF_1minPerPowerSum_Direction(uchar8 V_ucCurrentDeriction, uchar8 V_ucDerictionFlag, uchar8 V_ucDemandTimerClearFlag)
{
	if( ( V_ucCurrentDeriction & V_ucDerictionFlag ) != ( SV_ucPowerDirection & V_ucDerictionFlag ) )
	{
		SF_InitDemandTimer(V_ucDemandTimerClearFlag);			/* ���ú����������й�����������ڽ��г�ʼ�� */
		SV_ucPowerDirection &= (~V_ucDerictionFlag);
		SV_ucPowerDirection |= (V_ucCurrentDeriction & V_ucDerictionFlag);
	}
}

/*******************************************************************************
����ԭ�ͣ�void InF_PowerChanggeInitDemand(Str_RealtimePower_Type *pStr_RealtimePower)
�����������жϹ��ʷ����仯���������仯�������������ʱ������  
���������pStr_RealtimePowerָ��ʵʱ���ʽṹ��
�����������
���ز�������
����λ�ã�����ģ��ÿ1s����1��
��    ע��
*******************************************************************************/
void InF_PowerChanggeInitDemand(Str_RealtimePower_Type *pStr_RealtimePower)
{
	/* ���й����ʴ��� */
	SF_1minPerPowerSum_Direction( pStr_RealtimePower->Deriction, C_DerictActive_T, C_DerictionChange_AT );

	/* ���޹����ʴ��� */
	SF_1minPerPowerSum_Direction( pStr_RealtimePower->Deriction, C_DerictReactive_T, C_DerictionChange_RT);
	
	/* A���й����ʴ��� */
	SF_1minPerPowerSum_Direction( pStr_RealtimePower->Deriction, C_DerictActive_A, C_DerictionChange_AA);
	
	/* B���й����ʴ��� */
	SF_1minPerPowerSum_Direction( pStr_RealtimePower->Deriction, C_DerictActive_B, C_DerictionChange_AB);
	
	/* C���й����ʴ��� */
	SF_1minPerPowerSum_Direction( pStr_RealtimePower->Deriction, C_DerictActive_C, C_DerictionChange_AC);
	
	/* A���޹����ʴ��� */
	SF_1minPerPowerSum_Direction( pStr_RealtimePower->Deriction, C_DerictReactive_A, C_DerictionChange_RA);
	
	/* B���޹����ʴ��� */
	SF_1minPerPowerSum_Direction( pStr_RealtimePower->Deriction, C_DerictReactive_B, C_DerictionChange_RB);
	
	/* C���޹����ʴ��� */
	SF_1minPerPowerSum_Direction( pStr_RealtimePower->Deriction, C_DerictReactive_C, C_DerictionChange_RC);
}

/*******************************************************************************
����ԭ�ͣ�void SF_DemandMetering(ulong32 V_ulMaxDemandCode, ulong32 V_ulCurrentDemandCode, ulong32 *P_ulDemand)
�����������������������Ϣ����
���������V_ulMaxDemandCode:��ǰ������������ݱ�ʶ��
         V_ulCurrentDemandCode����ǰ���������ݱ�ʶ��
		 P_ulDemand��1minƽ�����������׵�ַ
����������� 
���ز�����C_OK��ȷ����C_Error��������г���
����λ�ã�������Ϣ1min����1�Σ�����ģ����ʸı䴥����ͨ���޸�ʱ�䡢�޸��������ڡ�������㼰�������㴥��
��    ע������ģ��ͬ��һ�����ս������ʱ���� 
*******************************************************************************/
void SF_DemandMetering(ulong32 V_ulMaxDemandCode, ulong32 V_ulCurrentDemandCode, ulong32 *pV_ulDemand)
{
	uchar8   V_ucBuffer[CL_DemandAndTime], V_ucLastDemand[CL_DemandAndTime];
	uchar8   V_uci, V_ucDemandInternal = 0, V_ucReworkFlay, V_ucRemainder;
	ulong64  V_ullDemandAdd;
	ushort16 V_usLen, V_usDataEncode;
	
	/* ��ȡ����������� */
	V_usDataEncode = 0;
	V_usLen = CLDemand_Cycle;
	if( InF_Read_Data(CDemand_Cycle, &V_ucDemandInternal, &V_usLen, &V_usDataEncode) != C_OK )
	{
		V_ucDemandInternal = C_NormalDemandInterval;
	}
	
	/* 6λС���������� */
	V_ullDemandAdd = 0;
	
	for( V_uci = 0; V_uci < V_ucDemandInternal; V_uci++ )
	{
		if( ( pV_ulDemand[V_uci] & 0x80000000 ) == 0x80000000 )
		{
			V_ullDemandAdd += ( ( ~pV_ulDemand[V_uci] ) + 1 );
		}
		else
		{
			V_ullDemandAdd += pV_ulDemand[V_uci];
		}
	}
	
	V_ullDemandAdd /= V_ucDemandInternal;
	
	/* 4λС���������㣬���������� */
	V_ucRemainder = V_ullDemandAdd % 100;
	V_ullDemandAdd /= 100;
	if( V_ucRemainder > 49 )  /* �������� */
	{
		V_ullDemandAdd += 1;
	}
	
	PF_Ulong64ToBuffer8(V_ucBuffer, &V_ullDemandAdd, CL_Demand);

	/* �ж������Ƿ���Ҫ���� */
	V_ucReworkFlay = 0;
	V_usDataEncode = 0;
	V_usLen = CL_DemandAndTime;
	if( InF_Read_Data( V_ulMaxDemandCode, &V_ucLastDemand[0], &V_usLen, &V_usDataEncode ) != C_OK )
	{
		V_ucReworkFlay = C_ReworkDemand;
	}
	else
	{
		if( PF_Campare_Data(V_ucBuffer, V_ucLastDemand, CL_Demand) == C_GreaterThan )
		{
			V_ucReworkFlay = C_ReworkDemand;
		}
	}
	
	/* �������´��� */
	if( C_ReworkDemand == V_ucReworkFlay )
	{
		/* ��ȡ���ݲ㵱ǰ����ʱ�� */
		V_usDataEncode = 0;
		V_usLen = CLDate_Time;
		InF_Read_Data(CDate_Time, &V_ucBuffer[CL_Demand], &V_usLen, &V_usDataEncode);
		
		V_ucBuffer[CL_Demand] = 0x00;  /* ��Ĭ��Ϊ0 */
		
		InF_Write_Data(C_Msg_DemandMetering, V_ulMaxDemandCode, V_ucBuffer, CL_DemandAndTime, SV_ucDemandSafe);
	}
	
	/******************************* ���µ�ǰ����������д���ݲ� *****************/
	if( V_ulCurrentDemandCode != NULL )				/* ��Ҫ���µ�ǰ���� */
	{		
		if( CCurr_AcDemand == V_ulCurrentDemandCode )
		{
			if( ( SV_ucPowerDirection & C_DerictActive_T ) == C_DerictActive_T )
			{
				V_ullDemandAdd = (~V_ullDemandAdd) + 1;
			}
		}
		else
		{
			if( ( SV_ucPowerDirection & C_DerictReactive_T ) == C_DerictReactive_T )
			{
				V_ullDemandAdd = (~V_ullDemandAdd) + 1;
			}
		}
		
		PF_Ulong64ToBuffer8(V_ucBuffer, &V_ullDemandAdd, CL_Demand);
		InF_Write_Data(C_Msg_DemandMetering, V_ulCurrentDemandCode, V_ucBuffer, CCurr_AcDemandLen, SV_ucDemandSafe);
	}
}

/*******************************************************************************************************
����ԭ�ͣ�void SF_DemandTimerClearDealWith(uchar8 V_ucClearType)
�������������������ʱ�����㴦��
���������V_ucClearType��������������־��
		  C_Settlement ��Ȼ�����㣬
          C_DemandClear ͨ���������㣬
          C_ReworkTime ͨ���޸�ʱ��
		  C_ReDemand_Cycle ͨ���޸�����������ڣ�
          C_MeterClear ������㣬
          C_RatesChanged ���ʱ��
		  C_DemandPowerUp �ϵ�������ʱ������
�����������
���ز�������
����λ�ã�������Ϣ1min����1�Σ�����ģ����ʸı䴥����ͨ���޸�ʱ�䡢�޸��������ڡ�������㼰�������㴥��
          ����ģ��ͬ��һ�����ս������ʱ����
��    ע��
*********************************************************************************************************/
void SF_DemandTimerClearDealWith(uchar8 V_ucClearType)
{
	if(SV_ucDemandSafe != C_W_SafeFlag)
	{
		return;
	}
	switch(V_ucClearType)						/* �ж���Ϣ���� */
	{
		case C_Settlement:			         	/* ��Ȼ�������� */
		case C_Settlement_ReSettle_Day1:     	/* �޸Ľ����ս��� */
		case C_ReworkTime:			         	/* �޸�ʱ�� */
		case C_RatesChanged:			     	/* �����ж� */
		case C_DemandPowerUp:			      	/* �ϵ� */
		/*case C_DataFreeze:*/			        /* ���ն��� */
		case C_DemandClear:			        	/* ͨ�� */
		case C_ReDemand_Cycle:		        	/* �޸������������ */
		case C_MeterClear:			        	/* ������� */
		{
			SF_InitDemandTimer( V_ucClearType );
			
		}break;
		default:
		 break;
	}
}

/*******************************************************************************
����ԭ�ͣ�ulong32 SF_GetDemandCodeNum(uchar8 V_ucDemandType)
������������ȡ���������ʶ��	
���������V_ucDemandTypeΪ��ȡ��ʶ������
		 C_T_ActiveCodeID�����й���ʶ�룬C_T_ReactiveCodeID�����޹���ʶ��
		 C_A_ActiveCodeID A���й���ʶ�룬C_A_ReactiveCodeID A���޹���ʶ��
		 C_B_ActiveCodeID B���й���ʶ�룬C_B_ReactiveCodeID B���޹���ʶ��
		 C_C_ActiveCodeID C���й���ʶ�룬C_C_ReactiveCodeID C���޹���ʶ��
�����������
���ز�������ǰӦ���ۼӵ�������ʶ��
����λ�ã�����������������ȡ��Ӧ��ʶ��ʱ����
��    ע��
*******************************************************************************/
ulong32 SF_GetDemandCodeNum(uchar8 V_ucDemandType)
{
	ulong32 V_ulDemandID;
	
	switch(V_ucDemandType)
	{
		case C_T_ActiveCodeID:
		{
			if( ( SV_ucPowerDirection & 0x08 ) == 0x08 )
			{
				V_ulDemandID = CRev_Ac_Tol_De_0;
			}
			else
			{
				V_ulDemandID = CPos_Ac_Tol_De_0;
			}
		}break;
		case C_T_ReactiveCodeID:
		{
			if( ( SV_ucPowerDirection & 0x08 ) == 0x08 )
			{
				if( ( SV_ucPowerDirection & 0x80 ) == 0x80 )
				{
					V_ulDemandID = CQua3_Re_Tol_De_0;
				}
				else
				{
					V_ulDemandID = CQua2_Re_Tol_De_0;
				}
			}
			else
			{
				if( ( SV_ucPowerDirection & 0x80 ) == 0x80 )
				{
					V_ulDemandID = CQua4_Re_Tol_De_0;
				}
				else
				{
					V_ulDemandID = CQua1_Re_Tol_De_0;
				}
			}
		}break;
		case C_A_ActiveCodeID:
		{
			if( ( SV_ucPowerDirection & 0x01 ) == 0x01 )
			{
				V_ulDemandID = CRevA_Ac_De_0;
			}
			else
			{
				V_ulDemandID = CPosA_Ac_De_0;
			}
		}break;
		case C_A_ReactiveCodeID:
		{
			if( ( SV_ucPowerDirection & 0x01 ) == 0x01 )
			{
				if( ( SV_ucPowerDirection & 0x10 ) == 0x10 )
				{
					V_ulDemandID = CQua3A_Re_De_0;
				}
				else
				{
					V_ulDemandID = CQua2A_Re_De_0;
				}
			}
			else
			{
				if( ( SV_ucPowerDirection & 0x10 ) == 0x10 )
				{
					V_ulDemandID = CQua4A_Re_De_0;
				}
				else
				{
					V_ulDemandID = CQua1A_Re_De_0;
				}
			}
		}break;
		case C_B_ActiveCodeID:
		{
			if( ( SV_ucPowerDirection & 0x02 ) == 0x02)
			{
				V_ulDemandID = CRevB_Ac_De_0;
			}
			else
			{
				V_ulDemandID = CPosB_Ac_De_0;
			}
		}break;
		case C_B_ReactiveCodeID:
		{
			if( ( SV_ucPowerDirection & 0x02 ) == 0x02 )
			{
				if( ( SV_ucPowerDirection & 0x20 ) == 0x20 )
				{
					V_ulDemandID = CQua3B_Re_De_0;
				}
				else
				{
					V_ulDemandID = CQua2B_Re_De_0;
				}
			}
			else
			{
				if( ( SV_ucPowerDirection & 0x20 ) == 0x20 )
				{
					V_ulDemandID = CQua4B_Re_De_0;
				}
				else
				{
					V_ulDemandID = CQua1B_Re_De_0;
				}
			}
		}break;
		case C_C_ActiveCodeID:
		{
			if( ( SV_ucPowerDirection & 0x04 ) == 0x04 )
			{
				V_ulDemandID = CRevC_Ac_De_0;
			}
			else
			{
				V_ulDemandID = CPosC_Ac_De_0;
			}
		}break;
		case C_C_ReactiveCodeID:
		{
			if( ( SV_ucPowerDirection & 0x04 ) == 0x04 )
			{
				if( ( SV_ucPowerDirection & 0x40 ) == 0x40 )
				{
					V_ulDemandID = CQua3C_Re_De_0;
				}
				else
				{
					V_ulDemandID = CQua2C_Re_De_0;
				}
			}
			else
			{
				if( ( SV_ucPowerDirection & 0x40 ) == 0x40 )
				{
					V_ulDemandID = CQua4C_Re_De_0;
				}
				else
				{
					V_ulDemandID = CQua1C_Re_De_0;
				}
			}
		}break;
		default:
		{
			V_ulDemandID = 0xFFFFFFFF;
		}break;
	}
	return V_ulDemandID;
}

/*******************************************************************************
����ԭ�ͣ�uchar8 InF_DemandMetering_Message(Str_Msg_Parameter *pStr_Msg_Parameter)
�����������������������Ϣ����
���������pStr_Msg_Parameterָ����Ϣ��ȡ���ŵľ�̬����
����������� 
���ز�����C_OK��ȷ����C_Error��������г���
����λ�ã�������Ϣ1min����1�Σ�����ģ����ʸı䴥����ͨ���޸�ʱ�䡢�޸��������ڡ�������㼰�������㴥��
          ����ģ��ͬ��һ�����ս������ʱ���� 
��    ע��
*******************************************************************************/
uchar8 InF_DemandMetering_Message(Str_Msg_Parameter *pStr_Msg_Parameter)
{
	uchar8  V_ucBuffer[30], V_ucLen, V_uci, V_ucj, V_ucSlipTime;
	ulong32 V_ulDemandCode;
	ulong32 *pV_ulAddr;
	ushort16 V_usLen, V_usDataEncode;
	
	/* �жϵ����־�Ƿ�Ϊ�е磬����ֱ�ӷ��ش��� */
	if( pStr_Msg_Parameter->PowerFlag != C_PowerOn )
	{
		return C_Error;
	}
	
	SV_ucDemandSafe = C_W_SafeFlag_1;
	V_ucLen = pStr_Msg_Parameter->Length + 1;
	
	PF_CopyDataBytes( pStr_Msg_Parameter->Parameter, V_ucBuffer, V_ucLen );		/* ����Ϣ���ݴ�ȫ�ֱ�����copy���� */
		
	if( ( V_ucBuffer[0] == Pt_DemandStatus )
	 || ( V_ucBuffer[0] == Pt_ParaMetersChange)
	 || ( V_ucBuffer[0] == Pt_MeterClear ) )				/* �ǵ���1min��ʱ������������Ҫ���ж�ʱ�����㴦��� */
	{
		SV_ucDemandSafe |= C_W_SafeFlag_2;
		if(V_ucBuffer[0] == Pt_MeterClear)					/* ���������Ϣ���ͣ�Ϊͨ�Ź㲥�·��ģ�û�в���ֵ�����︳ֵΪ�������� */
		{
			V_ucBuffer[1] = C_DemandClear;
		}
		SV_ucDemandSafe |= C_W_SafeFlag_3;
		SF_DemandTimerClearDealWith( V_ucBuffer[1] );
	}
	else if( V_ucBuffer[0] == Pt_Dispatch_Timing )
	{
		SV_ucDemandSafe |= C_W_SafeFlag_2;
		if( V_ucBuffer[1] == C_SystemMinChange )			/* ����min�仯 */
		{
			/* ����1minƽ������ */
			for( V_uci = 0; V_uci < C_PowerTypeNum; V_uci++)
			{
				/* ���������λ */
				pV_ulAddr = C_ComDemandRAMAddeTable[V_uci].PowerAvarageAddr;
				for( V_ucj = ( C_1minAvaragePowerNum - 1 ); V_ucj > 0; V_ucj--)
				{
					*(pV_ulAddr + V_ucj) = *(pV_ulAddr + V_ucj - 1);
				}
				
				/* ��1minƽ�����ʣ�6λС���� */
				V_usLen = CL1minPerPower;
				V_usDataEncode = 0;
				if( InF_GetData_ObjectManage( C_ComDemandRAMAddeTable[V_uci].AvaragePowerCode, V_ucBuffer, &V_usLen, &V_usDataEncode) == C_OK )
				{
					PF_BufferXToUlong32(V_ucBuffer, pV_ulAddr, CL1minPerPower);
				}	
				
			}
						
 			/* ��ȡ����ʱ�� */
			V_usDataEncode = 0;
		 	V_usLen = CLSliding_Time;
		 	if( InF_Read_Data(CSliding_Time, &V_ucSlipTime, &V_usLen, &V_usDataEncode) != C_OK )
		 	{
		 		V_ucSlipTime = C_NormalSlipTime;
		 	}

			SV_ucDemandSafe |= C_W_SafeFlag_3;
			
			/********************** �����й����� *******************************************/
			V_ulDemandCode = SF_GetDemandCodeNum( C_T_ActiveCodeID );
			
			/* �������й��������� */
			if( SV_ucActiveDemandIntervalTimer_T > 0 )
			{
				SV_ucActiveDemandIntervalTimer_T--;
				if( SV_ucActiveDemandIntervalTimer_T == 0 )	   				/* ����������� */
				{
					SV_ucActiveDemandIntervalTimer_T = V_ucSlipTime;		/* ��ʱ��������ʱ�� */
					SF_DemandMetering(V_ulDemandCode, CCurr_AcDemand, SV_ulActivePower_T);
					InF_MultiFunctionOutput(C_DemandPulse);
				}
			}
			
			/* �����й������������� */
			if( ( SV_usActiveRateDemandIntervalTimer_T & 0xFF ) > 0 )
			{
				SV_usActiveRateDemandIntervalTimer_T--;
				if( ( SV_usActiveRateDemandIntervalTimer_T & 0xFF ) == 0 )				/* ����������� */
				{
					SV_usActiveRateDemandIntervalTimer_T |= (ushort16)V_ucSlipTime;		/* ��ʱ��������ʱ�� */
					SF_DemandMetering( V_ulDemandCode + ( SV_usActiveRateDemandIntervalTimer_T >> 8 ), NULL, SV_ulActivePower_T);
				}
			}
			
			/*********************** �����޹����� ******************************************/
			V_ulDemandCode = SF_GetDemandCodeNum( C_T_ReactiveCodeID );
			
			/* �������޹��������� */
			if( SV_ucReactiveDemandIntervalTimer_T > 0 )
			{
				SV_ucReactiveDemandIntervalTimer_T--;
				if( SV_ucReactiveDemandIntervalTimer_T == 0 )							/* ����������� */
				{
					SV_ucReactiveDemandIntervalTimer_T = V_ucSlipTime;					/* ��ʱ��������ʱ�� */
					SF_DemandMetering(V_ulDemandCode, CCurr_ReDemand, SV_ulReactivePower_T);
				}
			}
			
			/* �����޹������������� */
			if( ( SV_usReactiveRateDemandIntervalTimer_T & 0xFF ) > 0 )
			{
				SV_usReactiveRateDemandIntervalTimer_T--;
				if( ( SV_usReactiveRateDemandIntervalTimer_T & 0xFF ) == 0 )			/* ����������� */
				{
					SV_usReactiveRateDemandIntervalTimer_T |= (ushort16)V_ucSlipTime;	/* ��ʱ��������ʱ�� */
					SF_DemandMetering( V_ulDemandCode + ( SV_usActiveRateDemandIntervalTimer_T >> 8 ), NULL, SV_ulReactivePower_T);
				}
			}
			
			/*************************** �����й����� ***************************************/			
			for( V_uci = 0; V_uci < 3; V_uci++)
			{
				V_ulDemandCode = SF_GetDemandCodeNum( C_ActiveCodeIDTable[V_uci] );
				
				/* �����й��������� */
				if( SV_ucActiveDemandIntervalTimer_SePhase[V_uci] > 0 )
				{
					SV_ucActiveDemandIntervalTimer_SePhase[V_uci]--;
					if( SV_ucActiveDemandIntervalTimer_SePhase[V_uci] == 0 )				/*�����������*/
					{
						SV_ucActiveDemandIntervalTimer_SePhase[V_uci] = V_ucSlipTime;		/*��ʱ��������ʱ��*/
						SF_DemandMetering(V_ulDemandCode, NULL, SV_ulActivePower_SePhase[V_uci]);
					}
				}
								
				V_ulDemandCode = SF_GetDemandCodeNum( C_ReactiveCodeIDTable[V_uci] );				
				/* �����޹��������� */
				if( SV_ucReactiveDemandIntervalTimer_SePhase[V_uci] > 0 )
				{
					SV_ucReactiveDemandIntervalTimer_SePhase[V_uci]--;
					if( SV_ucReactiveDemandIntervalTimer_SePhase[V_uci] == 0 )				/* ����������� */
					{
						SV_ucReactiveDemandIntervalTimer_SePhase[V_uci] = V_ucSlipTime;		/* ��ʱ��������ʱ�� */
						SF_DemandMetering(V_ulDemandCode, NULL, SV_ulReactivePower_SePhase[V_uci]);
					}
				}
			}			
		}
	}
	SV_ucDemandSafe = 0;
    return C_OK;
}

/*****************************************************************************************
����ԭ�ͣ�uchar8 SF_ReadDemand_Com_Single( ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen )
�������������������
���������V_ulOAD����ȡ��������OAD��
          pV_ucDataBuf����ȡ���ݴ�ŵĻ�����׵�ַ��
          *pV_usDataLen����ȡ�����ݴ�ŵĻ������󳤶ȣ�
���������pV_ucDataBuf����ȡ�����ݵ��׵�ַ��
          *pV_usDataLen����ȡ�����ݵĳ��ȣ�
���ز�����C_OK��ʾ��ȡ�ɹ���C_IDError��ʾ���ݱ�ʶ���C_CRCError���ݲ�CRC��C_DataLenError��ʾ���ݳ��ȴ�
		 C_NoAccess��ʾ��Ȩ�ޣ�C_SafeFlagError��ʾ��ȫ��־��C_Error��ʾ��������
����λ�ã���ȡ����
��    ע����SF_ReadDemand_Com��������
		  SF_ReadDemand_Com���ж��Ƿ��Ǽ��ϣ�ѭ����ȡ��	
		  SF_ReadDemand_Com_Singleֻ�ܵ�����ȡ��������	
**************************************************************************************************/
uchar8 SF_ReadDemand_Com_Single( ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen )
{
	uchar8  V_uci, V_ucOAD[C_DataCodeLen];
	uchar8  V_ucBuffer1[CL_DemandAndTime], V_ucBuffer2[CL_DemandAndTime];
	uchar8  V_ucMode, V_ucReturn, V_ucDeriction;
	ushort16 V_usLen, V_usDataEncode;
	ulong32 V_ulTemp, V_ulCodeID;
	
	PF_Ulong32ToBufferX(V_ucOAD, &V_ulOAD, C_DataCodeLen);		/* ����ʶ��ת��Ϊ���� */

	/* ��ȡ��ȡ���ݲ�����ݱ�ʶ */
	V_ulTemp = V_ulOAD & 0xFFFFFF00;
	
	for( V_uci = 0; V_uci < C_DemandCodeTableLen; V_uci++ )
	{
		if( C_ComDemandCodeTable[V_uci][0] == V_ulTemp )
		{
			V_ulCodeID = C_ComDemandCodeTable[V_uci][1] | ( V_ulOAD & 0x000000FF );
			break;
		}
	}   
	if(V_uci >= C_DemandCodeTableLen)		/* û�в��ҵ����ݱ�ʶ�룬Ӧ�����ݱ�ʾ�� */
	{
		return C_IDError;
	}

	/********************* ��ȡ����޹���������Ĵ��� ***************************/
	/* ���ȶ�ȡ����޹�ģʽ�� */
	V_usDataEncode = 0;
	V_usLen = CLReactive_Com_State1;
	if( ( V_ucOAD[2] & 0xF0 ) == 0x40 )				  /* ����޹�2 */
	{
		if( InF_Read_Data( CReactive_Com_State2, &V_ucMode, &V_usLen, &V_usDataEncode ) != C_OK )
		{
			V_ucMode = C_NormalCom2Mode;
		}
	}
	else											 /* ����޹�1 */
	{
		if( InF_Read_Data( CReactive_Com_State1, &V_ucMode, &V_usLen, &V_usDataEncode ) != C_OK )
		{
			V_ucMode = C_NormalCom1Mode;
		}
	}	
	
	memset( V_ucBuffer1, 0x00, CL_DemandAndTime );
	/*********************** ����ģʽ�ֶ�ȡ��Ӧ�����޹�������� ************************/
	for( V_uci = 0; V_uci < 4; V_uci++)
	{
		if( ( ( V_ucMode & 0x03 )== 0 ) || ( ( V_ucMode & 0x03 ) == 0x03 ) )		/* �ж�ģʽ���Ƿ���Ч�����Ӳ��� �� �ּ��ּ� */
		{
			V_ucMode >>= 2;
			continue;
		}
		else
		{
			V_ulTemp = V_ulCodeID + C_GetNextQuadrantDemand * V_uci;
			V_usDataEncode = 0;
			V_usLen = CL_DemandAndTime;
			V_ucReturn = InF_Read_Data( V_ulTemp, V_ucBuffer2, &V_usLen, &V_usDataEncode);
			if( V_ucReturn == C_OK )
			{
				/******* �Ƚ��޹�������С�����������ֵ���䷽�� *******/
				if( PF_Campare_Data( V_ucBuffer2, V_ucBuffer1, CL_Demand) == C_GreaterThan )
				{
					PF_CopyDataBytes( V_ucBuffer2, V_ucBuffer1, CL_DemandAndTime);
					if( ( V_uci == 0 ) || ( V_uci == 1 ) )		/* 698����޹���������������Ÿ��������жϣ����������Ǹ��� */
					{
						V_ucDeriction = C_DeActiveDirection;
					}
					else
					{
						V_ucDeriction = C_DeReactiveDirection;
					}
				}
			}
			else
			{
				return V_ucReturn;
			}
			
			V_ucMode>>= 2;
		}
	}
	
	/*************** ������������������봦�� *****************/
	if( *pV_usDataLen < CL_DemandAndTime )
	{
		return C_DataLenError;
	}
	else
	{
		PF_BufferXToUlong32( V_ucBuffer1, &V_ulTemp, CL_Demand );		
		if( V_ucDeriction == C_DeReactiveDirection )
		{
			V_ulTemp = (~V_ulTemp) + 1;
		}
		PF_Ulong32ToBufferX(V_ucBuffer1, &V_ulTemp, CL_Demand);
		
		*pV_usDataLen = CL_DemandAndTime;
		PF_CopyDataBytes_698(V_ucBuffer1, pV_ucDataBuf, *pV_usDataLen);
	}
	
    return C_OK;
	
}

/**************************************************************************************************
����ԭ�ͣ�uchar8 SF_ReadDemand_Com( ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen )
�������������������
���������V_ulOAD����ȡ��������OAD��
          pV_ucDataBuf����ȡ���ݴ�ŵĻ�����׵�ַ��
          *pV_usDataLen����ȡ�����ݴ�ŵĻ������󳤶ȣ�
���������pV_ucDataBuf����ȡ�����ݵ��׵�ַ��
          *pV_usDataLen����ȡ�����ݵĳ��ȣ�
���ز�����C_OK��ʾ��ȡ�ɹ���C_IDError��ʾ���ݱ�ʶ���C_CRCError���ݲ�CRC��C_DataLenError��ʾ���ݳ��ȴ�
		 C_NoAccess��ʾ��Ȩ�ޣ�C_SafeFlagError��ʾ��ȫ��־��C_Error��ʾ��������
����λ�ã���ȡ�������������ʱ��
��    ע���������������ʱ�����ݸ�ʽ��4�ֽ�HEX��4λС������λkW��+7�ֽ�ʱ�䣨date_time_s��ʽ��ss�̶�00��
**************************************************************************************************/
uchar8 SF_ReadDemand_Com( ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen )
{
	uchar8  V_ucTimes, V_uci, V_ucReturn;
	ushort16 V_usDataLen = 0, V_usDataOffset = 0;
   
    if( ( V_ulOAD & 0x000F00FF ) == 0x00000000 ) 		/* ���϶�ȡ */
    {
    	V_ucTimes = C_RatesNumTol;
		V_ulOAD += C_GetNextRatesDemand;

	}
	else if( ( ( V_ulOAD & 0x000F0000 ) != 0x00000000 ) && ( ( V_ulOAD & 0x000000FF ) == 0x00000000 )  )	/* ��������00���� */
	{
    	V_ucTimes = 1;
		V_ulOAD += C_GetNextRatesDemand;
	}
	else			 /* ������ȡ */
	{
		V_ucTimes = 1;
	}
    
    for( V_uci = 0; V_uci < V_ucTimes; V_uci++)
    {
    	if( *pV_usDataLen < V_usDataLen )
    	{
    		return C_DataLenError;
    	}
		
		*pV_usDataLen -= V_usDataLen;
    	V_usDataLen = *pV_usDataLen;
    	V_ucReturn = SF_ReadDemand_Com_Single(V_ulOAD, &pV_ucDataBuf[V_usDataOffset], &V_usDataLen);
    	if( V_ucReturn != C_OK)
    	{
    		return V_ucReturn;
    	}
        V_usDataOffset += V_usDataLen;
		V_ulOAD += C_GetNextRatesDemand;
	}
	*pV_usDataLen = V_usDataOffset;
	return V_ucReturn;        
}

/*****************************************************************************************
����ԭ�ͣ�uchar8 SF_ReadDemand_Other_Single( ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen )
�������������������
���������V_ulOAD����ȡ��������OAD��
          pV_ucDataBuf����ȡ���ݴ�ŵĻ�����׵�ַ��
          *pV_usDataLen����ȡ�����ݴ�ŵĻ������󳤶ȣ�
���������pV_ucDataBuf����ȡ�����ݵ��׵�ַ��
          *pV_usDataLen����ȡ�����ݵĳ��ȣ�
���ز�����C_OK��ʾ��ȡ�ɹ���C_IDError��ʾ���ݱ�ʶ���C_CRCError���ݲ�CRC��C_DataLenError��ʾ���ݳ��ȴ�
		 C_NoAccess��ʾ��Ȩ�ޣ�C_SafeFlagError��ʾ��ȫ��־��C_Error��ʾ��������
����λ�ã���ȡ����
��    ע����SF_ReadDemand_Other��������
		  SF_ReadDemand_Other���ж��Ƿ��Ǽ��ϣ�ѭ����ȡ��	
		  SF_ReadDemand_Other_Singleֻ�ܵ�����ȡ��������	
**************************************************************************************************/
uchar8 SF_ReadDemand_Other_Single( ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen )
{
	uchar8  V_ucReturn;
	ushort16 V_usLen, V_usDataEncode;
	
	
	if( *pV_usDataLen < CL_DemandAndTime )
	{
		return C_DataLenError;
	}
	else
	{	
		V_usDataEncode = 0;
		V_usLen = CL_DemandAndTime;
		V_ucReturn = InF_Read_Data( V_ulOAD, pV_ucDataBuf, &V_usLen, &V_usDataEncode );
		if( V_ucReturn != C_OK ) 
		{
			return V_ucReturn;
		}
		*pV_usDataLen = V_usLen;
	}
	
	return C_OK;
}
/**************************************************************************************************
����ԭ�ͣ�uchar8 SF_ReadDemand_Other( ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen )
�������������������
���������V_ulOAD����ȡ��������OAD��
          pV_ucDataBuf����ȡ���ݴ�ŵĻ�����׵�ַ��
          *pV_usDataLen����ȡ�����ݴ�ŵĻ������󳤶ȣ�
���������pV_ucDataBuf����ȡ�����ݵ��׵�ַ��
          *pV_usDataLen����ȡ�����ݵĳ��ȣ�
���ز�����C_OK��ʾ��ȡ�ɹ���C_IDError��ʾ���ݱ�ʶ���C_CRCError���ݲ�CRC��C_DataLenError��ʾ���ݳ��ȴ�
		 C_NoAccess��ʾ��Ȩ�ޣ�C_SafeFlagError��ʾ��ȫ��־��C_Error��ʾ��������
����λ�ã���ȡ�������������ʱ��
��    ע���������������ʱ�����ݸ�ʽ��4�ֽ�HEX��4λС������λkW��+7�ֽ�ʱ�䣨date_time_s��ʽ��ss�̶�00��
**************************************************************************************************/
uchar8 SF_ReadDemand_Other( ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen )
{
	uchar8  V_ucTimes, V_uci, V_ucReturn;
	ushort16 V_usDataLen = 0, V_usDataOffset = 0;
   
    if( ( V_ulOAD & 0x000F00FF ) == 0x00000000 ) 		/* ���϶�ȡ */
    {
    	V_ucTimes = C_RatesNumTol;
		V_ulOAD += C_GetNextRatesDemand;

	}
	else if( ( ( V_ulOAD & 0x000F0000 ) != 0x00000000 ) && ( ( V_ulOAD & 0x000000FF ) == 0x00000000 )  ) /* ��������00���� */
	{
    	V_ucTimes = 1;
		V_ulOAD += C_GetNextRatesDemand;
	}
	else			 /* ������ȡ */
	{
		V_ucTimes = 1;
	}
    
    for( V_uci = 0; V_uci < V_ucTimes; V_uci++)
    {
    	if( *pV_usDataLen < V_usDataLen )
    	{
    		return C_DataLenError;
    	}
		
		*pV_usDataLen -= V_usDataLen;
    	V_usDataLen = *pV_usDataLen;
    	V_ucReturn = SF_ReadDemand_Other_Single(V_ulOAD, &pV_ucDataBuf[V_usDataOffset], &V_usDataLen);
    	if( V_ucReturn != C_OK)
    	{
    		return V_ucReturn;
    	}
        V_usDataOffset += V_usDataLen;
		V_ulOAD += C_GetNextRatesDemand;
	}
	*pV_usDataLen = V_usDataOffset;
	
	return V_ucReturn;        
}

/*******************************************************************************
����ԭ�ͣ�uchar8 SF_GetDemand_Type(ulong32 V_ulOAD)
������������ȡ�������ݵ�����
���������V_ulOADΪ��ȡ������OAD
�����������
���ز������������ݵ�����
		  C_De_OADGetTpye_Com:	���������
		  C_De_OADGetTpye_Other:��������
����λ�ã��������ӿ�
��    ע��
*******************************************************************************/
uchar8 SF_GetDemand_Type(ulong32 V_ulOAD)
{
	uchar8 V_ucDemandType;
		
	if( ( ( V_ulOAD & 0xFFF00000 ) == 0x10300000 )		/* ����޹�1������� */
     || ( ( V_ulOAD & 0xFFF00000 ) == 0x10400000 ) ) 	/* ����޹�2������� */	
	{
		V_ucDemandType = C_De_OADGetTpye_Com;
	}
	else
	{
		V_ucDemandType = C_De_OADGetTpye_Other;
	}
	
	return V_ucDemandType;
}

/*******************************************************************************************************************************
����ԭ�ͣ�uchar8 InF_Get_DemandModule(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, ushort16 *pV_usDataEncode)
�������������������ȡ�ӿں���
���������V_ulOAD:���ݱ�ʶ�룻
          pV_ucDataBuf:��Ŷ�ȡ���ݵĻ�����׵�ַ��
          pV_usDataLen:��ȡ���ݻ������󳤶ȣ�
          *p_usDataEncode:�����ڲ����룻
���������pV_ucDataBuf:��ȡ���������ݵ��׵�ַ��
          *pV_usDataLen:��ȡ�����ݳ��ȣ�
          p_usDataEncode:�����ڲ����룻
���ز�����C_OK��ʾ��ȡ�ɹ���C_IDError��ʾ���ݱ�ʶ���C_CRCError���ݲ�CRC��C_DataLenError��ʾ���ݳ��ȴ�
		 C_NoAccess��ʾ��Ȩ�ޣ�C_SafeFlagError��ʾ��ȫ��־��C_Error��ʾ��������
����λ�ã�������Ҫ��ȡ�������ݵ�ģ��
��    ע����������޹������з����������������޷������ݡ� 
		  /---------------------------------------------------------------------------/
			����ģ������ṩ�����ݸ�ʽ
		  /---------------------------------------------------------------------------/
		  /-�������������ʱ��--------------------------------------------------------/
		  *	4�ֽ�HEX��4λС������λkW��+7�ֽ�ʱ�䣨date_time_s��ʽ��ss�̶�00��
		  /---------------------------------------------------------------------------/
********************************************************************************************************************************/
uchar8 InF_Get_DemandModule(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, ushort16 *pV_usDataEncode)
{
	uchar8 V_ucDemandType;
	uchar8 V_ucReturn;
	
	V_ucDemandType = SF_GetDemand_Type( V_ulOAD );
	
	if( V_ucDemandType == C_De_OADGetTpye_Com )
	{
		V_ucReturn = SF_ReadDemand_Com( V_ulOAD, pV_ucDataBuf, pV_usDataLen);
	}
	else if( V_ucDemandType == C_De_OADGetTpye_Other )
	{
		V_ucReturn = SF_ReadDemand_Other( V_ulOAD, pV_ucDataBuf, pV_usDataLen);
	}
	else
	{
		V_ucReturn = C_Error;
	}
	
	return V_ucReturn;
}
							 
/*******************************************************************************
����ԭ�ͣ�void InF_LowPower_DemandInit(void)
�����������͹����µ�ǰ����\1minƽ����������
�����������
�����������
���ز�������
����λ�ã��͹��Ĵ������ڽ���͹���ǰ����
��    ע��
*******************************************************************************/
void InF_LowPower_DemandInit(void)
{
	SF_Clear_CurrentDemand( );	/*����ǰ��������*/
}

/*******************************************************************************
����ԭ�ͣ�void SF_Clear_CurrentDemand(void)
��������������ǰ1����ƽ����������
�����������
�����������
���ز�������
����λ�ã��ϵ��ʼ�������������ؼơ��͹���
��    ע��
*******************************************************************************/
void SF_Clear_CurrentDemand(void)
{
	uchar8 V_ucData[CL_Demand];
	
	memset(&V_ucData[0], 0x00, CL_Demand);
	InF_Write_Data(C_Msg_DemandMetering, CCurr_AcDemand, &V_ucData[0], CLCurr_AcDemand, C_W_SafeFlag);		/* ��ǰ�й����� */
	InF_Write_Data(C_Msg_DemandMetering, CCurr_ReDemand, &V_ucData[0], CLCurr_ReDemand, C_W_SafeFlag);		/* ��ǰ�޹����� */
}




