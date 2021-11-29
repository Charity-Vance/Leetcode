/*******************************************************************************
Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     SettleAccount.c
Version:       V1
Author:        
Date:          2014-3-12
Description:   ����
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
#include "Public.h"
#include "SettleAccount.h"


/*****************************************************************************************
����ԭ�ͣ�Void InF_SettleAccountsAfterPowerUp(Void)                    
�����������ϵ�����ʼ��                                                 
�����������                                                                     
�����������                                                                    
���ز�������                                                                     
����λ�ã�����                                                             
��    ע��                                                                    
*****************************************************************************************/
void InF_SettleAccountsAfterPowerUp(void)
{
    ushort16 V_usLen, V_usDataEncode;
	uchar8 V_ucSettleAdd_Time[15];
	uchar8 V_ucEnterLowPowerTime[CLEnter_LowPower_Time];
   	Str_Msg_Parameter Str_Msg_SettleAccounts;
   	
    V_usLen = CLEnter_LowPower_Time;
    V_usDataEncode = C_pNULL_NoCode;
    if( InF_Read_Data(CEnter_LowPower_Time, &V_ucEnterLowPowerTime[0], &V_usLen, &V_usDataEncode) == C_OK )
    {
	    if(PF_DataTimeActive_698(&V_ucEnterLowPowerTime[0], C_DT_Start_ss, CLEnter_LowPower_Time) != C_OK)
	    {
	    	return;	
	    }
	    
		Str_Msg_SettleAccounts.SourceAddr = C_Msg_SettleAccounts;	    	/*Դ��Ϣ��*/
		Str_Msg_SettleAccounts.DerictAddr = C_Msg_SettleAccounts;	    	/*Ŀ����Ϣ��*/
	        
	    if( PF_Check_CRC(&SV_FristCheckDayChange[0], 4 ) == C_OK)       	/*�޸ĵ�1��������Ϣ*/
	    {
			Str_Msg_SettleAccounts.Length = Pt_ParaMetersChange_Len + 1 + CLEnter_LowPower_Time;		/*Parameter�ĳ���*/
			V_ucSettleAdd_Time[0] = SV_FristCheckDayChange[0];
			V_ucSettleAdd_Time[1] = SV_FristCheckDayChange[1];
			PF_CopyDataBytes(&V_ucEnterLowPowerTime[0], &V_ucSettleAdd_Time[2], CLEnter_LowPower_Time);
			Str_Msg_SettleAccounts.Parameter = &V_ucSettleAdd_Time[0];	   	/*����*/
			
			InF_WriteMessege(&Str_Msg_SettleAccounts);
			
			memset(SV_FristCheckDayChange, 0xFF, 4);
	    }
				
	    if( PF_Check_CRC(&SV_StepSwitch[0], 10) == C_OK )                 	/*�����л���Ϣ*/
	    {
	    	Str_Msg_SettleAccounts.Length = Pt_StepSwitchFlag_Len + 1;    	/*Parameter�ĳ���*/
			Str_Msg_SettleAccounts.Parameter = &SV_StepSwitch[0];         	/*����*/
				
			InF_WriteMessege(&Str_Msg_SettleAccounts);
			
			memset(SV_StepSwitch, 0xFF, 10 );
	    }
		
	    /*************�ϵ緢���粻������Ϣ���Ƿ���Ҫ�����㣬����Ϣ���������ж�**************/	    	    
	    Str_Msg_SettleAccounts.Length = Pt_SettleAdd_Time_Len + 1;		  	/*Parameter�ĳ���*/
		V_ucSettleAdd_Time[0] = Pt_SettleAdd_Time;
		PF_CopyDataBytes(&V_ucEnterLowPowerTime[0], &V_ucSettleAdd_Time[1], CLEnter_LowPower_Time);
		Str_Msg_SettleAccounts.Parameter = &V_ucSettleAdd_Time[0];	      	/*����*/
			
		InF_WriteMessege(&Str_Msg_SettleAccounts);
		
	}
	return;
    
}

/****************************************************************************************************
����ԭ�ͣ�void Msg_Freeze(Str_Msg_Parameter *P_Msg)	                 
����������������Ϣ����                                                
���������P_Msg,��Ϣ�ṹ��                                                                  
�����������                                                                 
���ز�������                                                                  
����λ�ã�����                                                          
��    ע����                                                                
***************************************************************************************************/
void Msg_SettleAccounts(Str_Msg_Parameter *P_Msg)
{
	uchar8 *pParm;
	uchar8 V_ucDataBuff1[C_FreezeMAXLen];
	uchar8 V_ucCurrentTime[CLDate_Time], V_ucSettle_Time_1[16];
	ushort16 V_usDataCRC, V_usDataLength = C_FreezeMAXLen;
	ushort16 V_Data_Len, V_usLen, V_usDataEncode;
	ulong32 V_Data_Id_OAD[3];
	uchar8 V_ucFlag;
	
	pParm = P_Msg->Parameter;
	if( (P_Msg->PowerFlag == C_PowerOff) || (P_Msg->PowerFlag == C_PowerFalling) )
	{
		if( P_Msg->SourceAddr == C_Msg_SettleAccounts )
		{
			return;	
		}
		else
		{
			if( *pParm == Pt_Dispatch_Timing )
			{
				return;	
			}
			else if( *pParm == Pt_ParaMetersChange )
			{
				PF_CopyDataBytes(pParm, &SV_FristCheckDayChange[0], 2);  	/*[0]:��Ϣ�ţ�[1]:��Ϣ����*/
				V_usDataCRC = PF_Cal_CRC(SV_FristCheckDayChange, 2);
				PF_Ushort16ToBuffer2(&SV_FristCheckDayChange[2], &V_usDataCRC); 	
			}
			else if( *pParm == Pt_StepSwitchFlag )
			{
				PF_CopyDataBytes(pParm, &SV_StepSwitch[0], (Pt_StepSwitchFlag_Len + 1) );
				V_usDataCRC = PF_Cal_CRC(SV_StepSwitch, (Pt_StepSwitchFlag_Len + 1));
				PF_Ushort16ToBuffer2(&SV_StepSwitch[(Pt_StepSwitchFlag_Len + 1)], &V_usDataCRC);		
			}
		}
		return;
	}
	
	if ( (*pParm == Pt_Dispatch_Timing) 
		&& ( P_Msg->Length == Pt_Dispatch_Timing_Freeze_Len + 1 ) 
		&& ( *(pParm+1) == C_SystemMinChange) ) /*����1min*/
	{
        V_usLen = CLDate_Time;
        V_usDataEncode = C_pNULL_NoCode;
        InF_Read_Data(CDate_Time, &V_ucCurrentTime[0], &V_usLen, &V_usDataEncode);          /*��ȡ��ǰʱ�� */
		
		if( PF_Campare_Data(&V_ucCurrentTime[0], (pParm + 2), CLDate_Time) == C_LessThan)   /*����¼�ĵ�����*/
		{
			return;
		}
		if( *(pParm + 3) == 0)      /*Сʱ�仯����Ҫ�ж�*/
		{
			SF_DealwithMin_SettleAccounts(pParm + 4);		

		}
		
	}
	else if ( ( ( *pParm == Pt_ParaMetersChange ) && ( *(pParm + 1) == C_ReSettle_Day1 ) )
			&& ( ( P_Msg->Length == Pt_ParaMetersChange_Len + 1 ) || ( P_Msg->Length == Pt_ParaMetersChange_Len + 1 + CLEnter_LowPower_Time ) ) )         /*�޸ĵ�1��������Ϣ*/
	{						
        V_usLen = CLDate_Time;
        V_usDataEncode = C_pNULL_NoCode;
        InF_Read_Data(CDate_Time, &V_ucCurrentTime[0], &V_usLen, &V_usDataEncode);          /*��ȡ��ǰʱ��*/
		
		if(P_Msg->Length == Pt_ParaMetersChange_Len + 1 + CLEnter_LowPower_Time)                        		/*���ȴ���2����Ϊ����ʱ��*/
		{
			PF_CopyDataBytes(pParm + 2, &V_ucCurrentTime[0], CLEnter_LowPower_Time);  		/*����Ϣ�����е�ʱ�串��֮ǰ��ȡʱ��*/
		}

		V_usDataLength = C_FreezeMAXLen;
		if(Inf_GetRecordData(V_ucDataBuff1, &V_usDataLength, C_FrzOAD, C_Settlement_Type) == C_OK)
		{
			PF_CopyDataBytes(&V_ucCurrentTime[2], (V_ucDataBuff1 + 2), 5);        /*����ʱ�� */
			InF_Write_Data(C_Msg_Freeze,C_RelatedOAD_Settle, &V_ucDataBuff1[0], V_usDataLength,C_W_SafeFlag);
		}
		
		InF_Demand_Clear(C_Msg_SettleAccounts, C_W_SafeFlag);	              /*����1����������ת�������*/
		SF_MsgSend_SettleAccounts_ReSettle_Day1();                            /*������ģ�鷢����1��������Ϣ*/
#if 0
		InF_ReadEnergy_Settlement( );       /*ȡ��ǰ��������������й����ۼ��õ���д���ݲ� */
		InF_Write_Data(C_Msg_SettleAccounts,CSC_Com_Ac_Tol_En_1, &V_ucDataBuff1[4], (CLSC_Com_Ac_Tol_En_1 + 1), C_W_SafeFlag);
		
		SF_GetRevEnergy_Pul_SettleAccounts(&V_ucDataBuff1[4]);                /*ȡ��ǰ�����������������й�����д���ݲ�*/
		InF_Write_Data(C_Msg_SettleAccounts,CSC_Rev_Ac_Tol_En_Pul_1, &V_ucDataBuff1[4], CLSC_Rev_Ac_Tol_En_Pul_1, C_W_SafeFlag);
		SF_GetPosEnergy_Pul_SettleAccounts(&V_ucDataBuff1[4]);
		InF_Write_Data(C_Msg_SettleAccounts,CSC_Pos_Ac_Tol_En_Pul_1, &V_ucDataBuff1[4], CLSC_Pos_Ac_Tol_En_Pul_1, C_W_SafeFlag);
				
		InF_ReadEnergy_Settlement( );      /*ȡ��ǰ�¶�����й����ۼ��õ���д���ݲ�*/
		InF_Write_Data(C_Msg_SettleAccounts,CM_Com_Ac_Tol_En_1, &V_ucDataBuff1[4], CLM_Com_Ac_Tol_En_1 + 1, C_W_SafeFlag);
#endif
		SF_GetRevEnergy_Pul_SettleAccounts(&V_ucDataBuff1[5]);      			/*ȡ��ǰ�¶��ۼ����������й�����д���ݲ�*/
		InF_Write_Data(C_Msg_SettleAccounts,CM_Rev_Ac_Tol_En_Pul_1, &V_ucDataBuff1[5], CLM_Rev_Ac_Tol_En_Pul_1, C_W_SafeFlag);
		SF_GetPosEnergy_Pul_SettleAccounts(&V_ucDataBuff1[5]);
		InF_Write_Data(C_Msg_SettleAccounts,CM_Pos_Ac_Tol_En_Pul_1, &V_ucDataBuff1[5], CLM_Pos_Ac_Tol_En_Pul_1, C_W_SafeFlag);

	}
#if 0		/*��ģ�鲻�ٷ���Ϣ*/
	else if ( ( *pParm == Pt_YearCheckDayChange ) 
			&& (( P_Msg->Length == Pt_YearCheckDayChange_Len + 1) || ( P_Msg->Length == Pt_YearCheckDayChange_Len + 1 + CLEnter_LowPower_Time)) )  /*�������޸ĵ�ǰ�����������Ϣ*/
	{
		if( C_Meter_Type == C_L_SmartMeter )        /*���ر����������� */
		{
			V_Data_Id_OAD[0] = CProgLad_Note_1;
			V_Data_Id_OAD[1] = 0x401A2200;
			V_Data_Id_OAD[2] = 0xFFFFFFFF;
			V_Data_1 = 0;
			V_Data_Len = CLCurrent_Ladder_Table;
			InF_ReadEventData(V_Data_Id_OAD, &V_Data_1, V_ucDataBuff1, &V_Data_1, &V_Data_Len, 0x68);      /*��ȡ��һ�ν���ʱ�� */
            
            V_usLen = CLCurrent_Ladder_Table;
            V_usDataEncode = C_pNULL_NoCode;
			InF_Read_Data(CCurrent_Ladder_Table, &V_ucDataBuff1[150], &V_usLen, &V_usDataEncode);           /*��ȡ������� */	
		
			if( PF_Campare_Data(&V_ucDataBuff1[C_StepSettlementStartAddr], &V_ucDataBuff1[150+C_StepSettlementStartAddr], C_StepSettlementTotalLen) == C_Equal )
			{
				return;	
			}
			
            V_usLen = CLDate_Time;
            V_usDataEncode = C_pNULL_NoCode;
			InF_Read_Data(CDate_Time, &V_ucCurrentTime[0], &V_usLen, &V_usDataEncode);                      /*��ȡ��ǰʱ�� */
			
			if( P_Msg->Length == Pt_YearCheckDayChange_Len + 1 + CLEnter_LowPower_Time )                        				/*����5����Ϊ����ʱ��*/
			{
				PF_CopyDataBytes((pParm + 1), &V_ucCurrentTime[0], CLEnter_LowPower_Time);  				/*����Ϣ�����е�ʱ�串��֮ǰ��ȡʱ��*/		
			}
			
			SF_FreezeYSettle(&V_ucCurrentTime[1], 6);
			
            InF_ReadEnergy_Settlement( );   /*ȡ��ǰ���������������й����ۼ��õ���д���ݲ�*/
		}	
	}
#endif
	else if ( ( *pParm == Pt_StepSwitchFlag ) 
			&& ( P_Msg->Length == Pt_StepSwitchFlag_Len + 1))   	/*�����ж���Ϣ*/
	{
		if(C_Meter_Type == C_L_SmartMeter)   						/*���ر����������� */
		{

			if( *(pParm + 1) == C_Step_SetttleChange)        		/*���ݽ����� */	
			{
				SF_FreezeYSettle((pParm + 2), 6);
				InF_ReadEnergy_Settlement( ); 						/*ȡ���ݽ����õ���д���ݲ�*/					
			}  /*else �������ݽ��㶳��*/

#if 0
			if( *(pParm + 1) == C_Step_YToY) /*������л�Ϊ����� */	
			{
			
				PF_CopyDataBytes((pParm + 3), &V_ucDataBuff1[0], 4); /*����Ϣ�����е�ʱ�������������ǰ�� */
				SF_FreezeYSettle((pParm + 2), 6);
				InF_ReadEnergy_Settlement( ); /*ȡ��ǰ���������������й����ۼ��õ���д���ݲ�*/					
			}
			else if(*(pParm + 1) == C_Step_YToM)  /*������л�Ϊ�½���*/
			{
				PF_CopyDataBytes((pParm + 3), &V_ucDataBuff1[0], 4);    /*����Ϣ�����е�ʱ�������������ǰ��*/
				SF_FreezeYSettle((pParm + 2), 6);
				V_usDataLength = C_FreezeMAXLen;
				if( Inf_GetRecordData(V_ucDataBuff1, &V_usDataLength, C_FrzOAD, C_Settlement_Type) == C_OK)
				{
					PF_CopyDataBytes((pParm + 3), (V_ucDataBuff1+2), 4); /*����ʱ�� */
					InF_Write_Data(C_Msg_Freeze, C_RelatedOAD_Settle, &V_ucDataBuff1[0], V_usDataLength, C_W_SafeFlag);
				}
				InF_ReadEnergy_Settlement( );  /*ȡ��ǰ���������������й����ۼ��õ���д���ݲ�*/

				InF_Demand_Clear(C_Msg_SettleAccounts, C_W_SafeFlag);	/*����1����������ת�������*/
				SF_MsgSend_SettleAccounts();                            /*������ģ�鷢����1��������Ϣ*/
				
				InF_ReadEnergy_Settlement( );   /*ȡ��ǰ��������������й����ۼ��õ���д���ݲ� */
				InF_Write_Data(C_Msg_SettleAccounts, CSC_Com_Ac_Tol_En_1, &V_ucDataBuff1[4], CLSC_Com_Ac_Tol_En_0 + 1, C_W_SafeFlag);
				
				SF_GetRevEnergy_Pul_SettleAccounts(&V_ucDataBuff1[4]);    /*ȡ��ǰ�����������������й�����д���ݲ�*/
				InF_Write_Data(C_Msg_SettleAccounts, CSC_Rev_Ac_Tol_En_Pul_1, &V_ucDataBuff1[4], CLSC_Rev_Ac_Tol_En_Pul_1, C_W_SafeFlag);
				SF_GetPosEnergy_Pul_SettleAccounts(&V_ucDataBuff1[4]);
				InF_Write_Data(C_Msg_SettleAccounts, CSC_Pos_Ac_Tol_En_Pul_1, &V_ucDataBuff1[4], CLSC_Pos_Ac_Tol_En_Pul_1, C_W_SafeFlag);
		 
				
				
				InF_ReadEnergy_Settlement( );    /*ȡ��ǰ�¶�����й����ۼ��õ���д���ݲ�*/
				InF_Write_Data(C_Msg_SettleAccounts, CM_Com_Ac_Tol_En_1, &V_ucDataBuff1[4], CLM_Com_Ac_Tol_En_0 + 1, C_W_SafeFlag);
				
				SF_GetRevEnergy_Pul_SettleAccounts(&V_ucDataBuff1[4]);   /*ȡ��ǰ�¶��ۼ����������й�����д���ݲ� *///
				InF_Write_Data(C_Msg_SettleAccounts,CM_Rev_Ac_Tol_En_Pul_1, &V_ucDataBuff1[4], CLM_Rev_Ac_Tol_En_Pul_1, C_W_SafeFlag);
				SF_GetPosEnergy_Pul_SettleAccounts(&V_ucDataBuff1[4]);
				InF_Write_Data(C_Msg_SettleAccounts, CM_Pos_Ac_Tol_En_Pul_1, &V_ucDataBuff1[4], CLM_Pos_Ac_Tol_En_Pul_1, C_W_SafeFlag);
			}
			else if( *(pParm + 1) == C_Step_MToY )      /*�½����л�Ϊ�����*/
			{
				V_usDataLength = C_FreezeMAXLen;
				if(Inf_GetRecordData(V_ucDataBuff1, &V_usDataLength, C_FrzOAD, C_Settlement_Type) == C_OK)
				{
					PF_CopyDataBytes(pParm+3, (V_ucDataBuff1 + 2), 4);       /*����ʱ�� */
					InF_Write_Data(C_Msg_Freeze,C_RelatedOAD_Settle, &V_ucDataBuff1[0], V_usDataLength, C_W_SafeFlag);
				}

				InF_Demand_Clear(C_Msg_SettleAccounts,C_W_SafeFlag);	/*����1����������ת�������*/
				SF_MsgSend_SettleAccounts();     /*������ģ�鷢����1��������Ϣ*/
				
				InF_ReadEnergy_Settlement( );    /*ȡ��ǰ��������������й����ۼ��õ���д���ݲ�*/
				InF_Write_Data(C_Msg_SettleAccounts,CSC_Com_Ac_Tol_En_1,&V_ucDataBuff1[4],CLSC_Com_Ac_Tol_En_0+1,C_W_SafeFlag);
				
				SF_GetRevEnergy_Pul_SettleAccounts(&V_ucDataBuff1[4]);      /*ȡ��ǰ�����������������й�����д���ݲ� */
				InF_Write_Data(C_Msg_SettleAccounts, CSC_Rev_Ac_Tol_En_Pul_1, &V_ucDataBuff1[4], CLSC_Rev_Ac_Tol_En_Pul_1, C_W_SafeFlag);
				SF_GetPosEnergy_Pul_SettleAccounts(&V_ucDataBuff1[4]);
				InF_Write_Data(C_Msg_SettleAccounts, CSC_Pos_Ac_Tol_En_Pul_1, &V_ucDataBuff1[4], CLSC_Pos_Ac_Tol_En_Pul_1, C_W_SafeFlag);
		
				InF_ReadEnergy_Settlement( );   /*ȡ��ǰ�¶�����й����ۼ��õ���д���ݲ�*/
				InF_Write_Data(C_Msg_SettleAccounts, CM_Com_Ac_Tol_En_1, &V_ucDataBuff1[4], CLM_Com_Ac_Tol_En_0 + 1, C_W_SafeFlag);
				
				SF_GetRevEnergy_Pul_SettleAccounts(&V_ucDataBuff1[4]);       /*ȡ��ǰ�¶��ۼ����������й�����д���ݲ� */
				InF_Write_Data(C_Msg_SettleAccounts, CM_Rev_Ac_Tol_En_Pul_1, &V_ucDataBuff1[4], CLM_Rev_Ac_Tol_En_Pul_1, C_W_SafeFlag);
				SF_GetPosEnergy_Pul_SettleAccounts(&V_ucDataBuff1[4]);
				InF_Write_Data(C_Msg_SettleAccounts, CM_Pos_Ac_Tol_En_Pul_1, &V_ucDataBuff1[4], CLM_Pos_Ac_Tol_En_Pul_1, C_W_SafeFlag);
			}
#endif
		}	
	}
	else if ( ( *pParm == Pt_SettleAdd_Time)
			&& ( P_Msg->Length == Pt_SettleAdd_Time_Len + 1 ) )    /*����������Ϣ*/
	{
		if( P_Msg->SourceAddr == C_Msg_Communication)
		{
			return;	
		}
		
		V_Data_Id_OAD[0] = 0x50050201;
		V_Data_Id_OAD[1] = CFreeTime;
		V_Data_Id_OAD[2] = 0xFFFFFFFF;
		V_Data_Len = 16;
		
		V_ucFlag = Inf_Read_FrozenData_OneOAD(V_Data_Id_OAD, V_ucSettle_Time_1, &V_Data_Len);       /*��ȡ��һ�ν���ʱ��*/
		
		if( ( *(pParm + 1) == 0x00 ) 
		 && ( *(pParm + 1 + 1) == 0x00 ) 
		 && ( ( ( V_ucFlag == C_OK) && (PF_Campare_Data(&V_ucSettle_Time_1[2], (pParm + 1 + 2), 5) != C_Equal ) )   
			|| ( V_ucFlag == C_NoData ) ) )                       /*00��00�����ʱ�жϵ���ʱ���Ƿ��Ѿ�����,1)ʱ�䲻��2��������*/
		{
			SF_DealwithMin_SettleAccounts(pParm + 1 + 2);	
		}
		
        V_usLen = CLDate_Time;
        V_usDataEncode = C_pNULL_NoCode;
        InF_Read_Data(CDate_Time, &V_ucCurrentTime[0], &V_usLen, &V_usDataEncode);          /*��ȡ��ǰʱ�� */
		
		SF_SettleAdd_SettleAccounts((pParm + 1), &V_ucCurrentTime[0]);	
	}
	return;
}

/****************************************************************************************************
����ԭ�ͣ�void SF_DealwithMin_SettleAccounts(uchar8 Settle_Time[4])	                 
��������������1min��������                                                
���������Settle_Time��ʱ���ַ��������ʱ��                                                                  
�����������                                                                 
���ز�������                                                                  
����λ�ã�����                                                          
��    ע����                                                                
***************************************************************************************************/
void SF_DealwithMin_SettleAccounts(uchar8 Settle_Time[4])
{
	uchar8 V_ucDataBuff[C_FreezeMAXLen];
	uchar8 V_ucDataBuff1[582];
	ushort16 V_usDataLength = C_FreezeMAXLen, V_usLen, V_usDataEncode;
	uchar8 V_SettleTime[CLDate_Time];
	
	V_usLen = CLSettle_Day1;	
	
	PF_CopyDataBytes(&Settle_Time[0], V_ucDataBuff1, 5);                          /*����ʱ��,������ʱ */
    
    V_usDataEncode = C_pNULL_NoCode;	
    if( InF_Read_Data(CSettle_Day1, V_SettleTime, &V_usLen, &V_usDataEncode) == C_OK )          /*��ȡ��1������ */
	{
		PF_OneDataReversed(V_SettleTime, V_SettleTime, (uchar8)V_usLen);
		if( PF_Campare_Data(&V_SettleTime[0], &Settle_Time[0], 2) == C_Equal )    /*�Ƿ񵽵�1������ */
		{
            V_usDataLength = C_FreezeMAXLen;            
			if( Inf_GetRecordData(V_ucDataBuff, &V_usDataLength, C_FrzOAD, C_Settlement_Type) == C_OK )
			{
				if( PF_Campare_Data(&V_ucDataBuff[2], Settle_Time, 5) == C_GreaterThan)  /*����¼�ĵ�����*/
				{
					PF_CopyDataBytes(Settle_Time, &V_ucDataBuff[2], 5);
				}
                
				V_ucDataBuff[0]=0;  /*��Ϊ0*/
				V_ucDataBuff[1]=0;  /*��Ϊ0*/
				InF_Write_Data(C_Msg_Freeze, C_RelatedOAD_Settle, &V_ucDataBuff[0], V_usDataLength, C_W_SafeFlag);
			}
            
			InF_Demand_Clear(C_Msg_SettleAccounts, C_W_SafeFlag);	/*����1����������ת�������*/
			SF_MsgSend_SettleAccounts();                            /*������ģ�鷢����1��������Ϣ*/
#if 0
			InF_ReadEnergy_Settlement( );      /*ȡ��ǰ��������������й����ۼ��õ���д���ݲ� */
			InF_Write_Data(C_Msg_SettleAccounts, CSC_Com_Ac_Tol_En_1, &V_ucDataBuff1[4], (CLSC_Com_Ac_Tol_En_0 + 1), C_W_SafeFlag);
			
			SF_GetRevEnergy_Pul_SettleAccounts(&V_ucDataBuff1[4]);  /*ȡ��ǰ�����������������й�����д���ݲ� */
			InF_Write_Data(C_Msg_SettleAccounts,CSC_Rev_Ac_Tol_En_Pul_1, &V_ucDataBuff1[4], CLSC_Rev_Ac_Tol_En_Pul_1, C_W_SafeFlag);
			SF_GetPosEnergy_Pul_SettleAccounts(&V_ucDataBuff1[4]);
			InF_Write_Data(C_Msg_SettleAccounts,CSC_Pos_Ac_Tol_En_Pul_1, &V_ucDataBuff1[4], CLSC_Pos_Ac_Tol_En_Pul_1, C_W_SafeFlag);
		
			InF_ReadEnergy_Settlement( );         /*ȡ��ǰ�¶�����й����ۼ��õ���д���ݲ� */
			InF_Write_Data(C_Msg_SettleAccounts,CM_Com_Ac_Tol_En_1,&V_ucDataBuff1[4], (CLM_Com_Ac_Tol_En_0 + 1), C_W_SafeFlag);
#endif
			SF_GetRevEnergy_Pul_SettleAccounts(&V_ucDataBuff1[5]);   /*ȡ��ǰ�¶��ۼ����������й�����д���ݲ� *///
			InF_Write_Data(C_Msg_SettleAccounts,CM_Rev_Ac_Tol_En_Pul_1, &V_ucDataBuff1[5], CLM_Rev_Ac_Tol_En_Pul_1, C_W_SafeFlag);
			SF_GetPosEnergy_Pul_SettleAccounts(&V_ucDataBuff1[5]);
			InF_Write_Data(C_Msg_SettleAccounts,CM_Pos_Ac_Tol_En_Pul_1, &V_ucDataBuff1[5], CLM_Pos_Ac_Tol_En_Pul_1, C_W_SafeFlag);
		}	
	}
    if( InF_Read_Data(CSettle_Day2, &V_SettleTime[2], &V_usLen, &V_usDataEncode) == C_OK)       /*��ȡ��2������ */
	{
		PF_OneDataReversed(&V_SettleTime[2], &V_SettleTime[2], (uchar8)V_usLen);
		if ( ( PF_Campare_Data(&V_SettleTime[2], &V_SettleTime[0], 2) != C_Equal )
          && ( PF_Campare_Data(&V_SettleTime[2], &Settle_Time[0], 2) == C_Equal ) )
		{
#if 0
			InF_ReadEnergy_Settlement( );    /*ȡ��ǰ��������������й����ۼ��õ���д���ݲ� */
			InF_Write_Data(C_Msg_SettleAccounts,CSC_Com_Ac_Tol_En_1,&V_ucDataBuff1[4],CLSC_Com_Ac_Tol_En_0+1,C_W_SafeFlag);
#endif
            V_usDataLength = C_FreezeMAXLen;
            if(Inf_GetFrozenData_Settle23(V_ucDataBuff,&V_usDataLength,0xFF,CSett_Free_OADTab) == C_OK)
			{
				if(PF_Campare_Data(&V_ucDataBuff[2], Settle_Time, 5) == C_GreaterThan)          /*����¼�ĵ�����*/
				{
					PF_CopyDataBytes(Settle_Time, &V_ucDataBuff[2], 5);
				}
				V_ucDataBuff[0]=0;  /*��Ϊ0*/
				V_ucDataBuff[1]=0;  /*��Ϊ0*/
				InF_Write_Data(C_Msg_Freeze,C_RelatedOAD_Settle, &V_ucDataBuff[0], V_usDataLength, C_W_SafeFlag);
			}           
		}
	}
    if( InF_Read_Data(CSettle_Day3, &V_SettleTime[4], &V_usLen, &V_usDataEncode) == C_OK)       /*��ȡ��3������ */
	{
		PF_OneDataReversed(&V_SettleTime[4], &V_SettleTime[4], (uchar8)V_usLen);
		if ( ( PF_Campare_Data(&V_SettleTime[4], &V_SettleTime[0], 2) != C_Equal )
          && ( PF_Campare_Data(&V_SettleTime[4], &V_SettleTime[2], 2) != C_Equal )
          && ( PF_Campare_Data(&V_SettleTime[4], &Settle_Time[0], 2) == C_Equal ) )
		{
#if 0
			InF_ReadEnergy_Settlement( );        /*ȡ��ǰ��������������й����ۼ��õ���д���ݲ� */
			InF_Write_Data(C_Msg_SettleAccounts, CSC_Com_Ac_Tol_En_1, &V_ucDataBuff1[4], (CLSC_Com_Ac_Tol_En_0 + 1), C_W_SafeFlag);
#endif
            V_usDataLength = C_FreezeMAXLen;
            if(Inf_GetFrozenData_Settle23(V_ucDataBuff, &V_usDataLength, 0xFF, CSett_Free_OADTab) == C_OK)
			{
				if(PF_Campare_Data(&V_ucDataBuff[2], Settle_Time, 5) == C_GreaterThan)  /*����¼�ĵ�����*/
				{
					PF_CopyDataBytes(Settle_Time, &V_ucDataBuff[2], 5);
				}
				V_ucDataBuff[0]=0;  /*��Ϊ0*/
				V_ucDataBuff[1]=0;  /*��Ϊ0*/
				InF_Write_Data(C_Msg_Freeze, C_RelatedOAD_Settle, &V_ucDataBuff[0], V_usDataLength, C_W_SafeFlag);
			}			
		}
	}
	
	if( C_Meter_Type == C_L_SmartMeter )    /*���ر������������ж� */
	{
		SF_DealwithYear_SettleAccounts(V_ucDataBuff1);	
	}
	return;	
}
/*****************************************************************************************
����ԭ�ͣ�void SF_SettleAdd_SettleAccounts (uchar8 *StartTime, uchar8 *EndTime)                           	                		   	
����������ͣ�������ջ�������ط�Ҫ���޸�ʱ���������յ���Ҫ������                                                     				
��������� *StartTime �����㿪ʼʱ�䣻                                                                  
	      *EndTime ���������ʱ�䣻                                                                       
��������� ��                                                                       										
���ز����� ��                                                                                 
����λ�ã�                                                                             
��    ע:                                                                           
*****************************************************************************************/
void SF_SettleAdd_SettleAccounts (uchar8 *StartTime, uchar8 *EndTime)
{
	uchar8 V_ucMonths, i, j, V_times = 0, V_ucNum = 0;
	uchar8 V_ucSettleDaySequence[15] = {0}, V_ucValidSettleDay = 0;
	uchar8 V_ucEndTime[CLDate_Time], V_ucSettlementTime[9] = {0}, Start_Time[CLDate_Time];
	ulong32 SubHours;
	uchar8 V_ucSettleTime[15][5];
	uchar8 V_ucDataBuff1[10];
	uchar8 V_ucDemandData1[C_FreezeMAXLen];
	uchar8 V_ucDemandData23[C_FreezeMAXLen];

 	ushort16 V_usDataLength = C_FreezeMAXLen, V_usLen, V_usDataEncode;
 	uchar8 V_ucDemandClearFlag = 0x00;
 	uchar8 V_ucLastSettlementTime[16];
	ushort16 V_Data_Len;
	ulong32 V_Data_Id_OAD[3];
    ulong32	V_SettleAccountNum;
	uchar8 V_SettleAccountTime[7] = {0};
    uchar8 V_ucFlag;
	ulong32 V_ulCurMonthNum = 0, V_ulStartTimeMonthNum = 0, V_ulTemp = 0;
	ushort16 V_usYear = 0;
	
	PF_CopyDataBytes(StartTime, &Start_Time[0], CLDate_Time);
	PF_CopyDataBytes(EndTime, &V_ucEndTime[0], CLDate_Time);
	
    V_usLen = 2;
    V_usDataEncode = C_pNULL_NoCode; 
	if( InF_Read_Data(CSettle_Day1, &V_ucSettlementTime[0], &V_usLen, &V_usDataEncode) == C_OK )            /*��ȡ��1������ */
	{
		V_ucNum++;	
		PF_OneDataReversed(V_ucSettlementTime, V_ucSettlementTime, 2);
		V_ucSettlementTime[2] = 1;
		
		if( InF_Read_Data(CSettle_Day2, &V_ucSettlementTime[3], &V_usLen, &V_usDataEncode) == C_OK )        /*��ȡ��2������ */
		{
			
			PF_OneDataReversed(&V_ucSettlementTime[3], &V_ucSettlementTime[3], 2);
			V_ucSettlementTime[5] = 2;
			V_ucNum++;
			
            if( InF_Read_Data(CSettle_Day3, &V_ucSettlementTime[6], &V_usLen, &V_usDataEncode) == C_OK )    /*��ȡ��3������ */
			{
				PF_OneDataReversed(&V_ucSettlementTime[6], &V_ucSettlementTime[6], 2);
				V_ucSettlementTime[8] = 3;
				V_ucNum++;	
			}	
		}
		
		V_times = SF_JudgeAndOrder_SettleAccounts(&V_ucSettlementTime[0], 3, V_ucNum);		
	}
			
	if( ( V_times > 0 ) && ( V_times <= 3 ) )	/*�����ո���*/
	{
			
        if( PF_TimeSub_Hour_698(V_ucEndTime, Start_Time, &SubHours) != C_GreaterThan )    /*��ǰʱ��С�ڵ��ڲ����㿪ʼʱ�䲻������*/
        {
            return;	
        }
        
        if( PF_Campare_Data(&V_ucEndTime[4], &Start_Time[4], 3) == C_Equal )          /*δ����ֻ���ҵ�ǰ��*/
        {
            for( i = 0; i < V_times; i++ )	/*������Ҫ���Ľ����� */
            {
                if ( ( PF_Campare_Data(&Start_Time[2], &V_ucSettlementTime[(V_times - 1 - i) * 3], 2) == C_LessThan )
                  && ( PF_Campare_Data(&V_ucEndTime[2], &V_ucSettlementTime[(V_times - 1 - i) * 3], 2) != C_LessThan ) )
                {
                    if(V_ucValidSettleDay < 15)
                    {
                        V_ucValidSettleDay++;
                        V_ucSettleTime[15 - V_ucValidSettleDay][0] = V_ucSettlementTime[(V_times - 1 - i) * 3];       
                        V_ucSettleTime[15 - V_ucValidSettleDay][1] = V_ucSettlementTime[(V_times - 1 - i) * 3 + 1];
                        V_ucSettleTime[15 - V_ucValidSettleDay][2] = V_ucEndTime[4];
                        V_ucSettleTime[15 - V_ucValidSettleDay][3] = V_ucEndTime[5];
						V_ucSettleTime[15 - V_ucValidSettleDay][4] = V_ucEndTime[6];
                        V_ucSettleDaySequence[15 - V_ucValidSettleDay] = V_ucSettlementTime[(V_times - 1 - i) * 3 + 2];
                    }
                }
            }	
		}
        else
        {		
			V_ulTemp = 0;
			PF_BufferXToUlong32(&V_ucEndTime[5], &V_ulCurMonthNum, 2);
			PF_BufferXToUlong32(&V_ucEndTime[4], &V_ulTemp, 1);			
			V_ulCurMonthNum = V_ulCurMonthNum * 12 + V_ulTemp;
			
			V_ulTemp = 0;
			PF_BufferXToUlong32(&Start_Time[5], &V_ulStartTimeMonthNum, 2);
			PF_BufferXToUlong32(&Start_Time[4], &V_ulTemp, 1);			
			V_ulStartTimeMonthNum = V_ulStartTimeMonthNum * 12 + V_ulTemp;
			
            V_ucMonths = (uchar8)( (V_ulCurMonthNum - V_ulStartTimeMonthNum) - 1) ;
            
            for(i = 0; i < V_times; i++)	/* ��1��0�㿪ʼ��������� */
            {
                if( PF_Campare_Data(&V_ucEndTime[2], &V_ucSettlementTime[(V_times - 1 - i) * 3], 2) != C_LessThan )
                {
                    if(V_ucValidSettleDay < 15)
                    {
                        V_ucValidSettleDay++;
                        V_ucSettleTime[15 - V_ucValidSettleDay][0] = V_ucSettlementTime[(V_times - 1 - i) * 3];
                        V_ucSettleTime[15 - V_ucValidSettleDay][1] = V_ucSettlementTime[(V_times - 1 - i) * 3 + 1];
                        V_ucSettleTime[15 - V_ucValidSettleDay][2] = V_ucEndTime[4];
                        V_ucSettleTime[15 - V_ucValidSettleDay][3] = V_ucEndTime[5];
                        V_ucSettleTime[15 - V_ucValidSettleDay][4] = V_ucEndTime[6];						
                        V_ucSettleDaySequence[15 - V_ucValidSettleDay] = V_ucSettlementTime[(V_times - 1 - i) * 3 + 2];
                    }
                }
            }
				
            for(j = 0; j < V_ucMonths; j++)
            {
                if(V_ucEndTime[4] == 0x01)
                {
                    V_ucEndTime[4] = 12;
                    PF_Buffer2ToUshort16(&V_ucEndTime[5], &V_usYear);
					V_usYear -= 1;
					PF_Ushort16ToBuffer2(&V_ucEndTime[5], &V_usYear);
                }
                else
                {
                    
					V_ucEndTime[4] -= 1;
                }
                
                for(i = 0; i < V_times; i++)	
                {
                    if(V_ucValidSettleDay < 15)
                    {
                        V_ucValidSettleDay++;
                        V_ucSettleTime[15 - V_ucValidSettleDay][0] = V_ucSettlementTime[(V_times - 1 - i) * 3];
                        V_ucSettleTime[15 - V_ucValidSettleDay][1] = V_ucSettlementTime[(V_times - 1 - i) * 3 + 1];
                        V_ucSettleTime[15 - V_ucValidSettleDay][2] = V_ucEndTime[4];
                        V_ucSettleTime[15 - V_ucValidSettleDay][3] = V_ucEndTime[5];
                        V_ucSettleTime[15 - V_ucValidSettleDay][4] = V_ucEndTime[6];						
                        V_ucSettleDaySequence[15 - V_ucValidSettleDay] = V_ucSettlementTime[(V_times - 1 - i) * 3 + 2];
                        if(V_ucValidSettleDay > 14)
                        {
                            goto StartSettle;
                        }
                    }
                }
            }
					
            if(V_ucValidSettleDay < 15)
            {
                for( i = 0; i < V_times; i++ )	/* ��ͣ�翪ʼ����ĩ24��Ķ�������������� */
                {
                    if( PF_Campare_Data(&Start_Time[2], &V_ucSettlementTime[(V_times - 1 - i) * 3], 2) == C_LessThan )
                    {
                        if(V_ucValidSettleDay < 15)
                        {
                            V_ucValidSettleDay++;
                            V_ucSettleTime[15 - V_ucValidSettleDay][0] = V_ucSettlementTime[(V_times - 1 - i) * 3];
                            V_ucSettleTime[15 - V_ucValidSettleDay][1] = V_ucSettlementTime[(V_times - 1 - i) * 3 + 1];
                            V_ucSettleTime[15 - V_ucValidSettleDay][2] = Start_Time[4];
                            V_ucSettleTime[15 - V_ucValidSettleDay][3] = Start_Time[5];
                            V_ucSettleTime[15 - V_ucValidSettleDay][4] = Start_Time[6];							
                            V_ucSettleDaySequence[15 - V_ucValidSettleDay] = V_ucSettlementTime[(V_times - 1 - i) * 3 + 2];
                            if(V_ucValidSettleDay > 14)
                            {
                                break;
                            }
                        }
                    }
                }
            }	
				
		}
		StartSettle:
			
            V_Data_Id_OAD[0] = 0x50050201;
			V_Data_Id_OAD[1] = CFreeTime;
			V_Data_Id_OAD[2] = 0xFFFFFFFF;
			V_Data_Len = 16;
			V_ucFlag = Inf_Read_FrozenData_OneOAD(V_Data_Id_OAD, V_ucLastSettlementTime, &V_Data_Len);   /*��ȡ��һ�ν���ʱ�䣬����OAD������ʱ�䲻֧�֣�����һ��BB������ʱ����÷��صĹ̶������еĶ���ʱ�� */
			
            if ( ( ( V_ucFlag == C_OK ) && ( PF_Campare_Data(&V_ucLastSettlementTime[2], &V_ucSettleTime[14][0], CLSettle_Time_1) != C_Equal ) )      /*��ǰҪ���Ľ���ʱ������һ��ͬ�򲻲�*/
              || ( V_ucFlag == C_NoData) )    /*��1�ζ�����ǲ�����*/
			{
                V_usDataLength = C_FreezeMAXLen;
				if( Inf_GetRecordData(V_ucDemandData1, &V_usDataLength, C_FrzOAD, C_Settlement_Type) != C_OK )
                {
                    return;
                }
				V_usDataLength = C_FreezeMAXLen;
                Inf_GetFrozenData_Settle23(V_ucDemandData23, &V_usDataLength, 0xFF, CSett_Free_OADTab);
                
				if( V_ucValidSettleDay > 15 )
				{
					V_ucValidSettleDay = 15;
				}
                
				for(i = 0; i < V_ucValidSettleDay; i++)
				{
					
					if( V_ucSettleDaySequence[15 - V_ucValidSettleDay + i] )
					{
						PF_CopyDataBytes(&V_ucSettleTime[15 - V_ucValidSettleDay+i][0], &V_SettleAccountTime[2], 5);
						PF_CopyDataBytes(&V_SettleAccountTime[0], &V_ucDemandData1[0], 7);
						PF_CopyDataBytes(&V_SettleAccountTime[0], &V_ucDemandData23[0], 7);
#if 0
						InF_ReadEnergy_Settlement( );              /*ȡ��ǰ��������������й����ۼ��õ���д���ݲ�*/
						InF_Write_Data(C_Msg_SettleAccounts,CSC_Com_Ac_Tol_En_1, &V_ucDataBuff1[0], (CLSC_Com_Ac_Tol_En_0 + 1), C_W_SafeFlag);
						
						SF_GetRevEnergy_Pul_SettleAccounts(&V_ucDataBuff1[0]);          /*ȡ��ǰ�����������������й�����д���ݲ�*/
						InF_Write_Data(C_Msg_SettleAccounts,CSC_Rev_Ac_Tol_En_Pul_1, &V_ucDataBuff1[0], CLSC_Rev_Ac_Tol_En_Pul_1, C_W_SafeFlag);
						
                        SF_GetPosEnergy_Pul_SettleAccounts(&V_ucDataBuff1[0]);
						InF_Write_Data(C_Msg_SettleAccounts,CSC_Pos_Ac_Tol_En_Pul_1, &V_ucDataBuff1[0], CLSC_Pos_Ac_Tol_En_Pul_1, C_W_SafeFlag);
#endif
						if(V_ucSettleDaySequence[15 - V_ucValidSettleDay + i] == 1)
						{
							InF_Write_Data(C_Msg_Freeze, C_RelatedOAD_Settle, &V_ucDemandData1[0], V_usDataLength, C_W_SafeFlag);   /*��������д���ݲ� */
							
                            if(V_ucDemandClearFlag != C_DemandClearFlag)
							{
								V_ucDemandClearFlag = C_DemandClearFlag;
								InF_Demand_Clear(C_Msg_SettleAccounts, C_W_SafeFlag);	/*����1����������ת�������*/					
								
                                V_usDataLength = C_FreezeMAXLen;
                                Inf_GetFrozenData_Settle23(V_ucDemandData1, &V_usDataLength, 0x00, CSett_Free_OADTab);
								
                                PF_Buffer4ToUlong32(&V_ucDemandData1[7], &V_SettleAccountNum, 4);
								V_SettleAccountNum--;
								PF_Ulong32ToBuffer4(&V_ucDemandData1[7], &V_SettleAccountNum, 4);
							}
#if 0
							InF_ReadEnergy_Settlement( );     /*ȡ��ǰ�¶�����й����ۼ��õ���д���ݲ� */
							InF_Write_Data(C_Msg_SettleAccounts, CM_Com_Ac_Tol_En_1, &V_ucDataBuff1[0], (CLM_Com_Ac_Tol_En_0 + 1), C_W_SafeFlag);
#endif
							SF_GetRevEnergy_Pul_SettleAccounts(&V_ucDataBuff1[0]);              /*ȡ��ǰ�¶��ۼ����������й�����д���ݲ� */
							InF_Write_Data(C_Msg_SettleAccounts,CM_Rev_Ac_Tol_En_Pul_1, &V_ucDataBuff1[0], CLM_Rev_Ac_Tol_En_Pul_1, C_W_SafeFlag);
							SF_GetPosEnergy_Pul_SettleAccounts(&V_ucDataBuff1[0]);
							InF_Write_Data(C_Msg_SettleAccounts,CM_Pos_Ac_Tol_En_Pul_1, &V_ucDataBuff1[0], CLM_Pos_Ac_Tol_En_Pul_1, C_W_SafeFlag);
						}
						else
						{
							InF_Write_Data(C_Msg_Freeze, C_RelatedOAD_Settle, &V_ucDemandData23[0], V_usDataLength, C_W_SafeFlag);
							
						}
						PF_Buffer4ToUlong32(&V_ucDemandData1[7], &V_SettleAccountNum, 4);
						V_SettleAccountNum++;
						PF_Ulong32ToBuffer4(&V_ucDemandData1[7], &V_SettleAccountNum, 4);
						PF_Ulong32ToBuffer4(&V_ucDemandData23[7], &V_SettleAccountNum, 4);
					}
				}	
			}				

	}
	
	if(C_Meter_Type == C_L_SmartMeter)    		/*���ر������������ж� */
	{
		SF_DealwithYearAdd_SettleAccounts(StartTime, EndTime);	
	}
	return;	
}

/*******************************************************************************
����ԭ�ͣ�void SF_DealwithYear_SettleAccounts(uchar8 *pV_ucSettle_Time)
�����������ж��Ƿ񵽽��ݽ����գ������ݽ�������ת����ݽ����õ���
���������pV_ucSettle_Time:���ݽ����ջ��棨����ʱ��
�����������
���ز�������
����λ�ã�
��    ע��
*******************************************************************************/
void SF_DealwithYear_SettleAccounts(uchar8 *pV_ucSettle_Time)
{
	uchar8 V_ucSettlementTime[C_StepSettlementTotalLen];
	uchar8 V_ucDataBuff1[CLCurrent_Ladder_Table];
	uchar8 V_uci;
    ushort16 V_usLen, V_usDataEncode;
      
    V_usLen = CLCurrent_Ladder_Table;
    V_usDataEncode = C_pNULL_NoCode;
	if( InF_Read_Data(CCurrent_Ladder_Table, &V_ucDataBuff1[0], &V_usLen, &V_usDataEncode) == C_OK )  /* ��ȡ���ݽ����� */
	{
		PF_CopyDataBytes(&V_ucDataBuff1[C_StepSettlementStartAddr], V_ucSettlementTime, C_StepSettlementTotalLen);
		for(V_uci = 0; V_uci < C_StepSettlementNum; V_uci++)
		{
			PF_OneDataReversed(&V_ucSettlementTime[V_uci * C_StepSettlementLen], &V_ucSettlementTime[V_uci * C_StepSettlementLen], C_StepSettlementLen);
		}
		
		PF_CopyDataBytes(&pV_ucSettle_Time[0], &V_ucDataBuff1[0], C_StepSettlementLen);
		
		if( ( V_ucSettlementTime[2] == 0xFF ) || ( V_ucSettlementTime[2] == 0x63 ) )				  /* �����������Ч */
		{
			if( PF_Campare_Data( &V_ucSettlementTime[0], &pV_ucSettle_Time[0], 2 ) == C_Equal )		  /* �Ƿ񵽵�1�������(����Ч) */
			{
				SF_FreezeYSettle(&pV_ucSettle_Time[0], 5);
				InF_ReadEnergy_Settlement( );
			}
			return;
		}
		
		if( PF_Campare_Data(&V_ucSettlementTime[0], &pV_ucSettle_Time[0], C_StepSettlementLen) == C_Equal )				  /* �Ƿ񵽵�1������� */	
		{
			SF_FreezeYSettle(&pV_ucSettle_Time[0], 5);
			InF_ReadEnergy_Settlement( );		/* ȡ��ǰ���������������й����ۼ��õ���д���ݲ� */						
		}
		
		if( ( PF_Campare_Data(&V_ucSettlementTime[C_StepSettlementLen], &pV_ucSettle_Time[0], C_StepSettlementLen ) == C_Equal )
		 && ( PF_Campare_Data(&V_ucSettlementTime[C_StepSettlementLen], &V_ucSettlementTime[0], C_StepSettlementLen ) != C_Equal ) )		  /* �Ƿ񵽵�2������� */	
		{
			SF_FreezeYSettle(&pV_ucSettle_Time[0], 5);
			InF_ReadEnergy_Settlement( );		/* ȡ��ǰ���������������й����ۼ��õ���д���ݲ� */
				
		}
		
		if( ( PF_Campare_Data(&V_ucSettlementTime[6], &pV_ucSettle_Time[0], C_StepSettlementLen) == C_Equal )
		 && ( PF_Campare_Data(&V_ucSettlementTime[6], &V_ucSettlementTime[0], C_StepSettlementLen) != C_Equal )
		 && ( PF_Campare_Data(&V_ucSettlementTime[6], &V_ucSettlementTime[3], C_StepSettlementLen) != C_Equal ) )		  /* �Ƿ񵽵�3������� */
		{
			SF_FreezeYSettle(&pV_ucSettle_Time[0], 5);
			InF_ReadEnergy_Settlement( );		/* ȡ��ǰ���������������й����ۼ��õ���д���ݲ� */
				
		}
		
		if( ( PF_Campare_Data(&V_ucSettlementTime[9], &pV_ucSettle_Time[0], C_StepSettlementLen) == C_Equal )
		 && ( PF_Campare_Data(&V_ucSettlementTime[9], &V_ucSettlementTime[0], C_StepSettlementLen) != C_Equal )
		 && ( PF_Campare_Data(&V_ucSettlementTime[9], &V_ucSettlementTime[3], C_StepSettlementLen) != C_Equal )
		 && ( PF_Campare_Data(&V_ucSettlementTime[9], &V_ucSettlementTime[6], C_StepSettlementLen) != C_Equal ) )		  /* �Ƿ񵽵�4������� */
		{
			SF_FreezeYSettle(&pV_ucSettle_Time[0], 5);
			InF_ReadEnergy_Settlement( );		/* ȡ��ǰ���������������й����ۼ��õ���д���ݲ� */
				
		}				
	}
}
///******************************************************************************************///
///*Function��	void SF_DealwithYearAdd_SettleAccounts (uchar8 *StartTime,uchar8 *EndTime)                            	                		   	*///
///*Description���ж��Ƿ�������գ������������ת������õ���                                                     				*///
///*Input��    *StartTime �����㿪ʼʱ�䣻                                                                  *///
///*			    *EndTime ���������ʱ�䣻                                                                  *///
///*Calls��                                                                                 *///
///*Called By��                                                                             *///
///*Author:                                                                           *///
///******************************************************************************************///
void SF_DealwithYearAdd_SettleAccounts (uchar8 *StartTime, uchar8 *EndTime)
{
	uchar8  i, j, V_ucYears, V_ucValidSettleDay = 0;
	uchar8  V_Times = 0;
	uchar8  V_ucEndTime[CLDate_Time], V_ucSettlementTime[12], Start_Time[CLDate_Time];
	uchar8  V_ucSettleTime[5][5];
	uchar8  V_ucDataBuff1[CLCurrent_Ladder_Table];
	ulong32 SubHours;
    ushort16 V_usLen, V_usDataEncode;
	uchar8	V_ucMonth, V_Num,V_uci;
	ushort16 V_usYearEnd = 0,  V_usYearStart = 0;
	
	PF_CopyDataBytes(StartTime, &Start_Time[0], CLDate_Time);
	PF_CopyDataBytes(EndTime, &V_ucEndTime[0], CLDate_Time);
	
    V_usLen = CLCurrent_Ladder_Table;
    V_usDataEncode = C_pNULL_NoCode;
	if( InF_Read_Data(CCurrent_Ladder_Table, &V_ucDataBuff1[0], &V_usLen, &V_usDataEncode) == C_OK )    /* ��ȡ������� */
	{
		PF_CopyDataBytes(&V_ucDataBuff1[C_StepSettlementStartAddr], V_ucSettlementTime, C_StepSettlementTotalLen);
		
		for( V_uci= 0; V_uci < C_StepSettlementNum; V_uci++)
		{
			PF_OneDataReversed(&V_ucSettlementTime[V_uci * C_StepSettlementLen], &V_ucSettlementTime[V_uci * C_StepSettlementLen], C_StepSettlementLen);
		}
		
		if( ( V_ucSettlementTime[C_StepSettlementDay_MM] == 0xFF ) || ( V_ucSettlementTime[C_StepSettlementDay_MM] == 0x63 ) )					/*�����������Ч */
		{
			if( PF_TimeSub_Hour_698(V_ucEndTime, Start_Time, &SubHours) != C_GreaterThan )					/* ��ǰʱ��С�ڵ��ڲ����㿪ʼʱ�䲻������ */
			{
				return;	
			}
			
			V_Num = 1;
			V_ucSettlementTime[C_StepSettlementDay_MM] = V_ucEndTime[C_DT_Start_MM];
			if( ( V_ucEndTime[C_DT_Start_NN] == Start_Time[C_DT_Start_NN] ) && ( V_ucEndTime[C_DT_Start_NN_H] == Start_Time[C_DT_Start_NN_H] ) )
			{
				V_ucMonth = &V_ucEndTime[C_DT_Start_MM] - &Start_Time[C_DT_Start_MM];
				V_ucMonth += 1;
				for(i = 0; i < V_ucMonth; i++)
				{
					if( ( PF_Campare_Data(&Start_Time[C_DT_Start_hh], &V_ucSettlementTime[0], 3) == C_LessThan )
					 && ( PF_Campare_Data(&V_ucEndTime[C_DT_Start_hh], &V_ucSettlementTime[0], 3) != C_LessThan ) )
					{
						if(V_ucValidSettleDay < 5)
						{
							V_ucValidSettleDay++;
							PF_CopyDataBytes(V_ucSettlementTime, &V_ucSettleTime[5 - V_ucValidSettleDay][0], 3);
							V_ucSettleTime[5 - V_ucValidSettleDay][3] = V_ucEndTime[5];
							V_ucSettleTime[5 - V_ucValidSettleDay][4] = V_ucEndTime[6];
							if(V_ucValidSettleDay > 3)
							{
								goto StartSettle;
							}
						}
					}
					V_ucSettlementTime[2] -= V_Num;
				}
			}
			else
			{
				V_ucMonth = V_ucEndTime[4];
				for(i = 0; i < V_ucMonth; i++)
				{
					if(PF_Campare_Data(&V_ucEndTime[2], &V_ucSettlementTime[0], 3) != C_LessThan)
					{
						if(V_ucValidSettleDay < 5)
						{
							V_ucValidSettleDay++;
							PF_CopyDataBytes(V_ucSettlementTime,&V_ucSettleTime[5 - V_ucValidSettleDay][0],3);
							V_ucSettleTime[5 - V_ucValidSettleDay][3] = V_ucEndTime[5];
							V_ucSettleTime[5 - V_ucValidSettleDay][4] = V_ucEndTime[6];
							if(V_ucValidSettleDay > 3)
							{
								goto StartSettle;
							}
						}
					}
					V_ucSettlementTime[2] -= V_Num;
				}

				V_ucSettlementTime[2] = 12;
				
				PF_Buffer2ToUshort16(&V_ucEndTime[5], &V_usYearEnd);
				V_usYearEnd -= V_Num;
				PF_Ushort16ToBuffer2(&V_ucEndTime[5], &V_usYearEnd);
				
				for(i = 0; i < 5; i++)
				{
					if(PF_Campare_Data(&Start_Time[2],&V_ucSettlementTime[0],3) == C_LessThan)
					{
						if(V_ucValidSettleDay < 5)
						{
							V_ucValidSettleDay++;
							PF_CopyDataBytes(V_ucSettlementTime,&V_ucSettleTime[5 - V_ucValidSettleDay][0],3);
							V_ucSettleTime[5 - V_ucValidSettleDay][3] = V_ucEndTime[5];
							V_ucSettleTime[5 - V_ucValidSettleDay][4] = V_ucEndTime[6];
							if(V_ucValidSettleDay > 3)
							{
								goto StartSettle;
							}
						}
					}
					
					V_ucSettlementTime[2] -= V_Num;
				}
			}
			goto StartSettle;
		}
		V_Times = SF_JudgeAndOrder_SettleAccounts(&V_ucSettlementTime[0],3,4);
		
		if( ( V_Times > 0 ) && ( V_Times <= 12 ) )
		{
			if( PF_TimeSub_Hour_698(V_ucEndTime, Start_Time, &SubHours) != C_GreaterThan )			/* ��ǰʱ��С�ڵ��ڲ����㿪ʼʱ�䲻������ */
			{
				return;	
			}
			
			
			PF_Buffer2ToUshort16(&V_ucEndTime[5], &V_usYearEnd);
			PF_Buffer2ToUshort16(&Start_Time[5],  &V_usYearStart);
			
			if( ( V_usYearEnd == V_usYearStart ) && ( V_Times <= 4 ) )
			{
				for( i = 0; i < V_Times; i++ )													/*������Ҫ���Ľ����� */
				{
					if((PF_Campare_Data(&Start_Time[2], &V_ucSettlementTime[(V_Times - 1 - i) * 3], 3) == C_LessThan)
						&& (PF_Campare_Data(&V_ucEndTime[2], &V_ucSettlementTime[(V_Times - 1 - i) * 3], 3) != C_LessThan))
					{
						if(V_ucValidSettleDay < 5)
						{
							V_ucValidSettleDay++;
							PF_CopyDataBytes(&V_ucSettlementTime[(V_Times - 1 - i) * 3],&V_ucSettleTime[5 - V_ucValidSettleDay][0],3);
							V_ucSettleTime[5 - V_ucValidSettleDay][3] = V_ucEndTime[5];
							if(V_ucValidSettleDay > 3)
							{
								goto StartSettle;
							}
						}
					}
				}	
			}
			else if( ( V_usYearEnd > V_usYearStart ) && ( V_Times <= 4 ) )
			{
				V_ucYears = (uchar8)(V_usYearStart - V_usYearStart - 1);
			
				for( i = 0; i < V_Times; i++ )					/* ��1��0�㿪ʼ */
				{
					if( PF_Campare_Data(&V_ucEndTime[2], &V_ucSettlementTime[(V_Times - 1 - i) * 3], 3 ) != C_LessThan )
					{
						if(V_ucValidSettleDay < 5)
						{
							V_ucValidSettleDay++;
							PF_CopyDataBytes(&V_ucSettlementTime[(V_Times - 1 - i) * 3], &V_ucSettleTime[5 - V_ucValidSettleDay][0], 3);
							V_ucSettleTime[5 - V_ucValidSettleDay][3] = V_ucEndTime[5];
							V_ucSettleTime[5 - V_ucValidSettleDay][4] = V_ucEndTime[6];
							if(V_ucValidSettleDay > 3)
							{
								goto StartSettle;
							}
						}
					}
				}
			
				for(j = 0; j < V_ucYears; j++)
				{
					V_usYearEnd -= 1;
					PF_Ushort16ToBuffer2(&V_ucEndTime[5], &V_usYearEnd);
					
					for(i = 0; i < V_Times; i++)	
					{
						if( ( V_ucValidSettleDay < 5)&&(V_Times <= 4 ) )
						{
							V_ucValidSettleDay++;
							PF_CopyDataBytes(&V_ucSettlementTime[(V_Times - 1 - i) * 3], &V_ucSettleTime[5 - V_ucValidSettleDay][0], 3);
							V_ucSettleTime[5 - V_ucValidSettleDay][3] = V_ucEndTime[5];
							V_ucSettleTime[5 - V_ucValidSettleDay][4] = V_ucEndTime[6];
							if(V_ucValidSettleDay > 3)
							{
								goto StartSettle;
							}
						}
					}
				}
				
				if((V_ucValidSettleDay < 5)&&(V_Times <= 4))
				{
					for(i = 0; i < V_Times; i++)	
					{
						if(PF_Campare_Data(&Start_Time[2], &V_ucSettlementTime[(V_Times - 1 - i) * 3], 3) == C_LessThan)
						{
							if(V_ucValidSettleDay < 5)
							{
								V_ucValidSettleDay++;
								PF_CopyDataBytes(&V_ucSettlementTime[(V_Times - 1 - i) * 3],&V_ucSettleTime[5 - V_ucValidSettleDay][0],3);
								V_ucSettleTime[5 - V_ucValidSettleDay][3] = Start_Time[5];								
								V_ucSettleTime[5 - V_ucValidSettleDay][4] = Start_Time[6];
								if(V_ucValidSettleDay > 3)
								{
									break;
								}
							}
						}
					}
				}	
			}
			StartSettle:
			{
				for(i=0;i<V_ucValidSettleDay;i++)
				{
					if(V_ucValidSettleDay <= 5)
					{
						PF_CopyDataBytes(&V_ucSettleTime[5 - V_ucValidSettleDay + i][0],V_ucDataBuff1, 5);		/*����ʱ�� */
						SF_FreezeYSettle(V_ucDataBuff1, 5);
						InF_ReadEnergy_Settlement( );					    /*ȡ��ǰ���������������й����ۼ��õ���д���ݲ� */
					}
						
				}
			}
		}
	}	
		
}

///******************************************************************************************///
///*Function��	uchar8 SF_JudgeAndOrder_SettleAccounts(uchar8 *P_ucData,uchar8 V_ucLen,uchar8 V_ucNum)	                            	                		   	*///
///*Description�� �Բ�ͬ����������кϷ����жϣ�ͬʱ��������                                                    				*///
///*Input��         P_ucData������ʼ��ַ��V_ucLen���ݳ��ȣ�V_ucNumΪ�������                                                             *///
///*Output��       ��Ч��ֵ����                                                                *///										*///
///*Calls��                                                                                 *///
///*Called By��                                                                             *///
///*Author:                                                                           *///
///******************************************************************************************///

uchar8 SF_JudgeAndOrder_SettleAccounts(uchar8 *P_ucData,uchar8 V_ucLen,uchar8 V_ucNum)
{
	uchar8	V_ucBuffer[16],V_ucActiveNum=0,V_ucTemp = 0,i,j,V_ucCompareNum;

	if(V_ucNum==4)
	{
		V_ucCompareNum=3;	
	}
	else 
	{
		V_ucCompareNum=2;	
	}

	for(i=0;i<V_ucNum;i++)
	{
		if(((*(P_ucData+i*V_ucLen) != 0x63) && (*(P_ucData+i*V_ucLen+1)!= 0x63))
			&&((*(P_ucData+i*V_ucLen) != 0xff) && (*(P_ucData+i*V_ucLen+1)!= 0xff))
			&&((*(P_ucData+i*V_ucLen) != 0x00) || (*(P_ucData+i*V_ucLen+1)!= 0x00)))
//			&&((i==0)||((i>0)&&(PF_Campare_Data(P_ucData+i*V_ucLen,P_ucData+(i-1)*V_ucLen,V_ucCompareNum)!=C_Equal))))
		{
			if(i==0)
			{
				PF_CopyDataBytes(P_ucData+i*V_ucLen,&V_ucBuffer[V_ucTemp*V_ucLen],V_ucLen);
				V_ucTemp++;	///*�����պϷ�����1*///	
			}
			else
			{
				for(j=0;j<i;j++)
				{
					if(PF_Campare_Data(P_ucData+i*V_ucLen,P_ucData+j*V_ucLen,V_ucCompareNum)==C_Equal)	
					{
						break;	
					}
					if(j==i-1)
					{
						PF_CopyDataBytes(P_ucData+i*V_ucLen,&V_ucBuffer[V_ucTemp*V_ucLen],V_ucLen);
						V_ucTemp++;	///*�����պϷ�����1*///	
					}
				}
			}
			
		}
	}
	
	V_ucActiveNum = V_ucTemp;
	///**********����������********///
	if(V_ucActiveNum != 0)
	{
		PF_CopyDataBytes(&V_ucBuffer[0],P_ucData,V_ucLen*V_ucTemp);
		for(i=0;i<(V_ucTemp-1);i++)
		{
			for(j=i;j<(V_ucTemp-1);j++)
			{
				if(PF_Campare_Data(&P_ucData[V_ucLen+j*V_ucLen],&P_ucData[i*V_ucLen],V_ucCompareNum)==C_LessThan)
				{
					PF_CopyDataBytes(&P_ucData[i*V_ucLen],&V_ucBuffer[0],V_ucLen);
					PF_CopyDataBytes(&P_ucData[V_ucLen+j*V_ucLen],&P_ucData[i*V_ucLen],V_ucLen);
					PF_CopyDataBytes(&V_ucBuffer[0],&P_ucData[V_ucLen+j*V_ucLen],V_ucLen);
				}
			}
		}
	}
	return V_ucActiveNum;
}

/*******************************************************************************
����ԭ�ͣ�void SF_GetPosEnergy_Pul_SettleAccounts_Part(uchar8 *pV_ucResultData, ulong32 V_ulRate1PulseOAD)
������������ȡ��������
���������pV_ucResultData��������ݵĻ��棻
		 V_ulRate1PulseOAD�����ݱ�ʶ
���������pV_ucResultData�����������ݣ�
���ز�������
����λ�ã��������
��    ע��
*******************************************************************************/
void SF_GetPosEnergy_Pul_SettleAccounts_Part(uchar8 *pV_ucResultData, ulong32 V_ulRate1PulseOAD)
{
	uchar8 V_ucDataBuff[8], i;
	ulong64 V_ulTemp;
	ulong64 V_ulTemp1;
    ushort16 V_usLen, V_usDataEncode;
	
	V_ulTemp = 0;
	for(i = 0; i < C_MaxRatesNum; i++)
	{
		memset(V_ucDataBuff, 0x00, 8);
		V_ulTemp1 = 0;
        
        V_usLen = CLPos_Ac_T2_En_Pul_0;
        V_usDataEncode = C_pNULL_NoCode;
        InF_Read_Data(V_ulRate1PulseOAD + 0x00000001 * i, &V_ucDataBuff[0], &V_usLen, &V_usDataEncode);  /* ��ȡ���������� */
		PF_Buffer8ToUlong64(V_ucDataBuff, &V_ulTemp1, CLPos_Ac_T2_En_Pul_0);
		V_ulTemp += V_ulTemp1;
	}
	
	PF_Ulong64ToBuffer8(pV_ucResultData, &V_ulTemp, 8);
	
	return;	
}

/*******************************************************************************
����ԭ�ͣ���ȡ�����й���������
������������ȡ�����й���������
���������V_ucResultData����ȡ���ܺ��ŵ����ݻ���
���������V_ucResultData����������й���������
���ز�������
����λ�ã�
��    ע��
*******************************************************************************/
void SF_GetPosEnergy_Pul_SettleAccounts(uchar8 *V_ucResultData)
{
	SF_GetPosEnergy_Pul_SettleAccounts_Part(V_ucResultData, CPos_Ac_T1_PreEn_0);
	return;
}

/*******************************************************************************
����ԭ�ͣ���ȡ�����й���������
������������ȡ�����й���������
���������V_ucResultData����ȡ���ܺ��ŵ����ݻ���
���������V_ucResultData����������й���������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
void SF_GetRevEnergy_Pul_SettleAccounts(uchar8 *V_ucResultData)
{
	SF_GetPosEnergy_Pul_SettleAccounts_Part(V_ucResultData, CRev_Ac_T1_PreEn_0);
	return;
}
///******************************************************************************************///
///*Function��	void SF_MsgSend_Relay(uchar8 *V_ucParm,uchar8 V_ucParmLen,uchar8 V_ucDerictAddr)                            	                		   	*///
///*Description��   ������Ϣ                                                				*///
///*Input��                                                                      *///
///*                                                                   *///
///*                                         *///
///*Output��     																																  *///
///*		   																														 				*///
///*Calls��                                                                                 *///
///*Called By��                                                                             *///
///*Author:                                                                           *///
///******************************************************************************************///
void SF_MsgSend_SettleAccounts(void)
{
	uchar8 V_ucDataBuff[2];
	Str_Msg_Parameter	Str_Msg_SettleAccounts;
	
	V_ucDataBuff[0]=Pt_DemandStatus;
	V_ucDataBuff[1]=C_Settlement;
	 
//	Str_Msg_SettleAccounts.PowerFlag = C_PowerOn;///*�����־�����ڸ�����Ϣ����ģ�������ж��Ƿ���е��籣�棬C_PowerDown��ʾ����׼������͹��ģ�C_PowerOn��ʾ�е�*///
	Str_Msg_SettleAccounts.SourceAddr = C_Msg_SettleAccounts;///*Դ��Ϣ��*///
	Str_Msg_SettleAccounts.DerictAddr = C_Msg_DemandMetering;///*Ŀ����Ϣ��*///
	Str_Msg_SettleAccounts.Length = Pt_DemandStatus_Len+1;///*����*///
	Str_Msg_SettleAccounts.Parameter = V_ucDataBuff;///*����*///
	InF_WriteMessege(&Str_Msg_SettleAccounts);///*д��Ϣ����*///
}
/******************************************************************************************
����ԭ�ͣ�void SF_MsgSend_SettleAccounts_ReSettle_Day1(void)                          
����������������Ϣ ���޸ĵ�һ������                                               	
�����������                                                                         
�����������																			
���ز�������                                                                         
����λ�ã�Msg_SettleAccounts                                                         
��    ע��                                                                                 
*******************************************************************************************/
void SF_MsgSend_SettleAccounts_ReSettle_Day1(void)
{
	uchar8 V_ucDataBuff[2];
	Str_Msg_Parameter Str_Msg_SettleAccounts;
	
	V_ucDataBuff[0] = Pt_DemandStatus;
	V_ucDataBuff[1] = C_Settlement_ReSettle_Day1;
	 
	Str_Msg_SettleAccounts.SourceAddr = C_Msg_SettleAccounts;    /*Դ��Ϣ��*/
	Str_Msg_SettleAccounts.DerictAddr = C_Msg_DemandMetering;    /*Ŀ����Ϣ��*/
	Str_Msg_SettleAccounts.Length = Pt_DemandStatus_Len + 1;     /*����*/
	Str_Msg_SettleAccounts.Parameter = V_ucDataBuff;             /*����*/
	InF_WriteMessege( &Str_Msg_SettleAccounts );                 /*д��Ϣ����*/
}
/*******************************************************************************
����ԭ�ͣ�uchar8 Inf_GetFrozenData_Settle23(uchar8 *V_ucData, ushort16 *V_ucResultDataLength, uchar8 V_Demand, ulong32 V_OADTable)
������������ȡ��������
���������V_ulDataCode   Լ�������л�ʱ��ı�ʶ��  
          Swich_Time   ���õ��л�ʱ��  
�����������
���ز�����C_OK, C_Error, C_DataLenError
����λ�ã�
��    ע�����ݸ�ʽ:mmhhDDMMYYYY+XXXXXXXX(��������)+DATA 
*******************************************************************************/
uchar8 Inf_GetFrozenData_Settle23(uchar8 *V_ucData, ushort16 *V_ucResultDataLength, uchar8 V_Demand, ulong32 V_OADTable)
{
	uchar8 i = 0, j = 0, V_uc645DINum;
	uchar8 V_ucCurrentTime[CLDate_Time], P_Data_Length;
	ushort16 P_usData_Length, V_ucTurn, V_usLen, V_usDataEncode;
	ushort16 V_usOAD[300];
	ulong32	V_ul645DI,V_ulOADNumDI, V_ulOADTable, V_ulFrozenNum;
	ushort16 V_usOffset=0;
	uchar8 V_usOADNum, V_ucType;
    ushort16 V_usDataLenMax;
    uchar8 V_ucResultData[C_FreezeMAXLen];
	ushort16 V_usLen1;

    V_usDataLenMax = *V_ucResultDataLength;
	/*��ֵʱ��*/
	if(V_OADTable == CSett_Free_OADTab)
	{
        V_usLen = CLDate_Time;
        V_usDataEncode = C_pNULL_NoCode;
        if( InF_Read_Data(CDate_Time, &V_ucCurrentTime[0], &V_usLen, &V_usDataEncode) != C_OK)
		{
			return C_Error;	
		}
                
        if(V_usDataLenMax < CLDate_Time)
        {
            return C_DataLenError;
        }
        
        PF_CopyDataBytes(&V_ucCurrentTime[0], V_ucResultData, CLDate_Time);
        V_ulOADNumDI = CSett_Free_OADTabLen_T;
        V_ulOADTable = CSett_Free_OADTab;
        V_ul645DI = C_RelatedOAD_Settle;
        V_usOffset = CLDate_Time;
        
		/*����һ�ζ���������ݣ���ֵ*/
		P_Data_Length = 4;
		if(InF_ReadLaterFreezeNum(V_ul645DI, (uchar8 *)&V_ulFrozenNum, &P_Data_Length) != C_OK)
		{
			return C_Error;
		}
		V_ulFrozenNum += 1;
        
        if(V_usDataLenMax < (V_usOffset + 4) )
        {
            return C_DataLenError;
        }
        PF_CopyDataBytes((uchar8 *)&V_ulFrozenNum, (V_ucResultData+V_usOffset), 4);
	}
	else
	{
		V_ulOADNumDI = CD_Free_OADTabLen_T;
		V_ulOADTable = CD_Free_OADTab;
		V_ul645DI = C_RelatedOAD_Day;
		V_usOffset = CLDate_Time;
		if(V_usDataLenMax < (V_usOffset + 4) )
		{
			return C_DataLenError;
		}
		PF_CopyDataBytes(V_ucData, V_ucResultData, 10);
	}
	
	V_usOffset += 4;
	
	/*��OAD��OAD����*/
    V_usLen = CLSett_Free_OADTabLen_T;
    V_usDataEncode = C_pNULL_NoCode;
	if( InF_Read_Data(V_ulOADNumDI, &V_usOADNum, &V_usLen, &V_usDataEncode) != C_OK)
	{
		return C_Error;
	}

	if(V_usOADNum > C_FreezeMAXRelatedOAD)
	{
		return C_Error;
	}
	
	P_usData_Length = 6 * V_usOADNum;
	if(InF_ReadOADTab_Data(V_ulOADTable, (uchar8 *)&V_usOAD, &P_usData_Length) != C_OK)
	{
		return C_Error;
	}
	
	for( V_ucTurn = 0; V_ucTurn < (V_usOADNum * 3); V_ucTurn++)
	{
		V_usOAD[V_ucTurn] &= 0x1FFF;

		V_ucTurn += 2;	
	}
	
	/*����OAD��˳����֯����*/
	for( V_ucTurn = 0; V_ucTurn < (V_usOADNum * 3); V_ucTurn++)
	{
		if(V_usOAD[V_ucTurn] > Str_FrozenConvert_Table_Len)
		{
			return C_Error;
		}
		
		V_ul645DI = Str_FrozenConvert_Table[V_usOAD[V_ucTurn]].V_ulOAD;
		P_Data_Length = Str_FrozenConvert_Table[V_usOAD[V_ucTurn]].V_uc645Length;
        V_usLen = Str_FrozenConvert_Table[V_usOAD[V_ucTurn]].V_uc645Length; 
		V_ucType = Str_FrozenConvert_Table[V_usOAD[V_ucTurn]].V_uc698Type;
		V_uc645DINum = Str_FrozenConvert_Table[V_usOAD[V_ucTurn]].V_uc698NextNum;

		if ( ( ( V_ul645DI & 0xff000000 ) == 0x00000000 )       /*����*/
		  || ( ( V_ul645DI & 0xFFFF0000 ) == 0x202D0000 )       /*͸֧���*/
          || ( ( V_ul645DI & 0xFFFF0000 ) == 0x20310000 )       /*�¶��õ���*/
		  || ( V_ul645DI == 0x202C0201 )                        /*ʣ����*/
		  || ( ( V_ul645DI & 0xFFFF0000 ) == 0x20320000 ) )     /*���ݽ����õ���*/	
		{
            if( V_ucType == C_array)    /*��Ҫ�����645��ʶ��*/
            {
                for(i = 1; i <= V_uc645DINum; i++)
                {
                    V_ul645DI = Str_FrozenConvert_Table[V_usOAD[V_ucTurn] + i].V_ulOAD;
                    P_usData_Length = Str_FrozenConvert_Table[V_usOAD[V_ucTurn] + i].V_uc645Length;
                    if(InF_GetData_ObjectManage(V_ul645DI, (V_ucResultData + V_usOffset), &P_usData_Length, 0) == C_OK)   /*��ȡ����*/
                    {
                        V_usOffset += P_usData_Length;
                    }
                    else
                    {
                        P_Data_Length = Str_FrozenConvert_Table[V_usOAD[V_ucTurn] + i].V_uc645Length;
 
                        for(j = 0; j < P_Data_Length; j++)
                        {
                            *(V_ucResultData + V_usOffset) = 0xAA;
                            V_usOffset += 1;
                        }
                    }
                }
            }
            else
            {
                if(InF_GetData_ObjectManage(V_ul645DI, (V_ucResultData + V_usOffset), &P_usData_Length, 0)  == C_OK)  /*��ȡ����*/
                {
                    V_usOffset += P_usData_Length;
                }
                else
                {
                    P_Data_Length = Str_FrozenConvert_Table[V_usOAD[V_ucTurn]].V_uc645Length;

                    for( j = 0; j < P_Data_Length; j++)
                    {
                        *(V_ucResultData + V_usOffset) = 0xAA;
                        V_usOffset += 1;
                    }
                }
            
            }
		}
        else if (V_ul645DI == 0x202C0200)    /*Ǯ���ļ�*/
        {
            V_ul645DI = Str_FrozenConvert_Table[V_usOAD[V_ucTurn] + 1].V_ulOAD;
            P_Data_Length = Str_FrozenConvert_Table[V_usOAD[V_ucTurn] + 1].V_uc645Length;
            if( InF_GetData_ObjectManage(V_ul645DI, (V_ucResultData + V_usOffset), &P_usData_Length, 0) == C_OK)    /*��ȡ����*/
            {
                V_usOffset += P_usData_Length;
            }
            else
            {
                P_Data_Length = Str_FrozenConvert_Table[V_usOAD[V_ucTurn] + 1].V_uc645Length;
                for(j = 0; j < P_Data_Length; j++)
                {
                    *(V_ucResultData + V_usOffset) = 0xAA;
                    V_usOffset += 1;
                }
            }
            
            V_ul645DI = Str_FrozenConvert_Table[V_usOAD[V_ucTurn] + 2].V_ulOAD;
            P_Data_Length = Str_FrozenConvert_Table[V_usOAD[V_ucTurn] + 2].V_uc645Length;
            /*��ESAM�еĹ������*/
			V_usLen1 = P_Data_Length;
			if( InF_GetData_ObjectManage(V_ul645DI, &V_ucResultData[V_usOffset], &V_usLen1, 0) == C_OK )
            {
                V_usOffset += V_usLen1;
            }
            else
            {
                P_Data_Length = Str_FrozenConvert_Table[V_usOAD[V_ucTurn] + 2].V_uc645Length;
                for(j = 0; j < P_Data_Length; j++)
                {
                    *(V_ucResultData + V_usOffset) = 0xAA;
                    V_usOffset += 1;
                }
            }
            

        }
        else if (V_ul645DI == 0x202C0202)    /*�������*/
        {
            /*��ESAM�еĹ������*/
			V_usLen1 = P_Data_Length;
            if( InF_GetData_ObjectManage(V_ul645DI, &V_ucResultData[V_usOffset], &V_usLen1, 0) == C_OK )
            {
                V_usOffset += V_usLen1;
            }
            else
            {
                for( j = 0; j < P_Data_Length; j++)
                {
                    *(V_ucResultData + V_usOffset) = 0xAA;
                    V_usOffset += 1;
                }
            }	
        }
        else if ( ( ( V_ul645DI & 0xff000000 ) == 0x10000000)
               || ( ( V_ul645DI & 0xff000000 ) == 0x11000000 ) )     /*����*/
        {
            if( V_ucType == C_array)        /*��Ҫ�����645��ʶ��*/
            {
                for( i = 1; i <= V_uc645DINum; i++)
                {
                    V_ul645DI = Str_FrozenConvert_Table[V_usOAD[V_ucTurn] + i].V_ulOAD;
                    P_Data_Length = Str_FrozenConvert_Table[V_usOAD[V_ucTurn] + i].V_uc645Length;			
                    P_Data_Length = Str_FrozenConvert_Table[V_usOAD[V_ucTurn] + i].V_uc645Length;

                    for( j = 0; j < P_Data_Length; j++)
                    {
                        *(V_ucResultData + V_usOffset) = V_Demand;
                        V_usOffset += 1;
                    }
                }
            }
            else
            {
                P_Data_Length = Str_FrozenConvert_Table[V_usOAD[V_ucTurn]].V_uc645Length;

                for( j  =0; j < P_Data_Length; j++)
                {
                    *(V_ucResultData + V_usOffset) = V_Demand;
                    V_usOffset += 1;
                }
            }
        }
        else if ( ( V_ul645DI == CVolA_Per_Pass_0_Freeze )
                || ( V_ul645DI == CVolA_Per_Pass_0 )
                || ( V_ul645DI == CVolB_Per_Pass_0_Freeze )
                || ( V_ul645DI == CVolB_Per_Pass_0 )		/*��ѹ�ϸ��ʺͽ����շ������⴦��*/
                || ( V_ul645DI == CVolC_Per_Pass_0_Freeze )
                || ( V_ul645DI == CVolC_Per_Pass_0 )
                || ( V_ul645DI == CSettle_Day1 )
                || ( V_ul645DI == CSettle_Day2 )
                || ( V_ul645DI == CSettle_Day3 ) )
        {
            if( InF_GetData_ObjectManage(V_ul645DI, (V_ucResultData + V_usOffset), &V_usLen, &V_usDataEncode) == C_OK )
            {
                V_usOffset += V_usLen;
            }
            else
            {
                P_Data_Length = Str_FrozenConvert_Table[V_usOAD[V_ucTurn]].V_uc645Length;

                for(j = 0; j < P_Data_Length; j++)
                {
                    *(V_ucResultData + V_usOffset) = 0xAA;
                    V_usOffset += 1;
                }
            }
        }
        else
        {
            if( ( V_ucType == C_array ) || ( (V_ucType == C_structure) && ( V_uc645DINum != 0 ) ) )     /*��Ҫ�����(��ѹ�ϸ��ʺͽ����շ���ǰ�������⴦��)*/
            {
                for( i = 1; i <= V_uc645DINum; i++)
                {
                    V_ul645DI = Str_FrozenConvert_Table[V_usOAD[V_ucTurn] + i].V_ulOAD;
                    P_Data_Length = Str_FrozenConvert_Table[V_usOAD[V_ucTurn] + i].V_uc645Length;
                    V_usLen = Str_FrozenConvert_Table[V_usOAD[V_ucTurn] + i].V_uc645Length; 
                      
                    if( (V_ul645DI & 0xff000000) == 0x00000000 )	   /*����*/
                    {
                        if(InF_GetData_ObjectManage(V_ul645DI, (V_ucResultData + V_usOffset), &P_usData_Length, 0) == C_OK)      /*��ȡ����*/
                        {
                            V_usOffset += P_usData_Length;
                        }
                        else
                        {	 
                            P_Data_Length = Str_FrozenConvert_Table[V_usOAD[V_ucTurn] + i].V_uc645Length;
                            for(j = 0; j < P_Data_Length; j++)
                            {
                                *(V_ucResultData + V_usOffset) = 0xAA;
                                V_usOffset += 1;
                            }
                        }
                    }
                    else
                    {
                        if( InF_Read_Data(V_ul645DI, (V_ucResultData + V_usOffset), &V_usLen, &V_usDataEncode) == C_OK )
                        {
                            V_usOffset += V_usLen;
                        }
                        else
                        {
                            P_Data_Length = Str_FrozenConvert_Table[V_usOAD[V_ucTurn]+i].V_uc645Length;

                            for( j = 0; j < P_Data_Length; j++)
                            {
                                *(V_ucResultData + V_usOffset) = 0xAA;
                                V_usOffset += 1;
                            }
                        }
                    
                    }
                }
            }
            else
            {
                if(InF_Read_Data(V_ul645DI, (V_ucResultData + V_usOffset), &V_usLen, &V_usDataEncode) == C_OK)
                {
                    V_usOffset += V_usLen;
                }
                else
                {
                    P_Data_Length = Str_FrozenConvert_Table[V_usOAD[V_ucTurn]].V_uc645Length;

                    for(j = 0; j < P_Data_Length; j++)
                    {
                        *(V_ucResultData + V_usOffset) = 0xAA;
                        V_usOffset += 1;
                    }
                }
            }
		}	

		V_ucTurn += 2;
		if( V_usOffset > V_usDataLenMax )	    /*��󳤶Ȳ��ܳ�������Buff���Ⱥ�����Buff����*/
		{
			return	C_DataLenError;
		}
	}
	PF_CopyDataBytes_698(V_ucResultData, V_ucData, V_usOffset);
	*V_ucResultDataLength = V_usOffset;
	
	return C_OK;
}

///******************************************************************************************///
///*Function��	uchar8 Inf_Read_FrozenData_OneOAD(ulong32 *V_Data_Id_OAD,ushort16 *V_Length)	*///
///*Description����ȡ��N�ζ��ᵥ��OAD����							*///
///*Input��ulong32 *V_Data_Id_OAD ���ἰ����OAD��ushort16 *V_Length���泤��                     *///
///*Output��ushort16 *V_Length ��ȡ���ݳ���							*///										*///
///*Calls��                                                                                 *///
///*Called By��                                                                             *///
///*Author:											*///
///******************************************************************************************///
uchar8 Inf_Read_FrozenData_OneOAD(ulong32 *V_Data_Id_OAD,uchar8 *V_Data,ushort16 *V_Length)
{
	uchar8		V_Data_1,V_Return;
	ushort16	V_Data_2;
	uchar8 	V_ucFreezeTime = 0;

	V_Data_1 = 0;
	V_Data_2 = 0;
	V_Return = InF_ReadFreezeData(V_Data_Id_OAD,&V_Data_1,V_Data,&V_Data_2,V_Length,V_Data_2,&V_ucFreezeTime,C_698Mode);
	return V_Return;
}
/*******************************************************************************
����ԭ�ͣ�void SF_FreezeYSettle(uchar8 *Swich_Time, uchar8 Len)
�����������궳�ᣨ���ڸ�Ϊ���ݽ��㶳�ᣩ
���������Len ���ݳ���  
          Swich_Time   ���õ��л�ʱ��  
�����������
���ز�������
����λ�ã�
��    ע��
*******************************************************************************/
void SF_FreezeYSettle(uchar8 *Swich_Time, uchar8 Len)
{
	uchar8 V_ucDataBuff[C_FreezeMAXLen], V_Swich_Time[7] = {0};
	ushort16 V_usDataLength = C_FreezeMAXLen;

	if(Len == 6)
	{
		PF_CopyDataBytes(&Swich_Time[0], &V_Swich_Time[1], 6);
	}
	else
	{
		PF_CopyDataBytes(&Swich_Time[0], &V_Swich_Time[2], 5);
	}
    
    V_usDataLength = C_FreezeMAXLen;
	if(Inf_GetRecordData(V_ucDataBuff, &V_usDataLength, C_FrzOAD, C_YSettle_Type) == C_OK)
	{
		PF_CopyDataBytes(&V_Swich_Time[0], &V_ucDataBuff[0], 7);
		InF_Write_Data(C_Msg_Freeze, C_RelatedOAD_YSettle, &V_ucDataBuff[0], V_usDataLength, C_W_SafeFlag);
	}
}



