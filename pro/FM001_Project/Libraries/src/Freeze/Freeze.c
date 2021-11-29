///*****************************************************************************************///
///*Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     Freeze.c
///*Version:       V1
///*Date:          2014-3-12
///*Description:   ���ᴦ��
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
#include "Freeze.h"

Str_FreezeTimerTable FreezeTimerTable;

void SF_GetFreeze_StartTime(uchar8 *pFreezeTime)
{
#if 0	/*ԭ������*/
	uchar8 PDataLength;
	PDataLength=V_ucLen;
	if(InF_Read_Data(V_ulFreeStartTimeDI, &pFreezeTime[6-PDataLength], &PDataLength)!=C_OK)
	{
		pFreezeTime[0] = 0x00;
		pFreezeTime[1] = 0x00;
		pFreezeTime[2] = 0x00;
		pFreezeTime[3] = 0x01;
		pFreezeTime[4] = 0x01;
		pFreezeTime[5] = 0x00;
	}

	if((PF_DataTimeActive(pFreezeTime,C_DT_Start_ss,C_DT_Len_ss) != C_OK))
		{
#endif
			pFreezeTime[0] = 0x00;
			pFreezeTime[1] = 0x00;
			pFreezeTime[2] = 0x00;
			pFreezeTime[3] = 0x01;
			pFreezeTime[4] = 0x01;
			pFreezeTime[5] = 0xD0;
			pFreezeTime[6] = 0x07;

#if 0	/*ԭ������*/
		}
#endif
}

/*******************************************************************************
����ԭ�ͣ�void InF_FreezeDayAfterPowerUp (Void)
�����������ϵ�󴥷���7���ն�����Ϣ����Ϣ���ݰ���6���ֽڵĲ��ն�����ʼʱ��
�����������
�����������
���ز�������
����λ�ã�
��    ע��
*******************************************************************************/
void InF_FreezeDayAfterPowerUp(void)
{
	ushort16 PDataLength, V_usDataEncode;
	uchar8 V_uc7DayAddTime[CLEnter_LowPower_Time];
   	Str_Msg_Parameter	Str_Msg_Freeze;

   	PDataLength = CLEnter_LowPower_Time;
   	if( (InF_Read_Data(CEnter_LowPower_Time, &V_uc7DayAddTime[0], &PDataLength, &V_usDataEncode) == C_OK)
	   && (PF_DataTimeActive_698(&V_uc7DayAddTime[0], C_DT_Start_ss, CLEnter_LowPower_Time) == C_OK) )
   	{
   		V_uc7DayAddTime[0] = Pt_7DayAdd_FreezeTime;
		
		Str_Msg_Freeze.SourceAddr = C_Msg_Freeze;	/*Դ��Ϣ��*/
		Str_Msg_Freeze.DerictAddr = C_Msg_Freeze;	/*Ŀ����Ϣ��*/
		Str_Msg_Freeze.Length = Pt_7DayAdd_FreezeTime_Len + 1;		/*Parameter�ĳ���*/
		Str_Msg_Freeze.Parameter = &V_uc7DayAddTime[0];	/*����*/

		InF_WriteMessege(&Str_Msg_Freeze);
   	}
    return;
}


/*******************************************************************************
����ԭ�ͣ�void InF_FreezeSwitch(ulong32 V_ulDataCode, uchar8 *V_ucSwich_Time)
����������дԼ������
���������V_ulDataCode   Լ�������л�ʱ��ı�ʶ��
          V_ucSwich_Time   ���õ��л�ʱ��
�����������
���ز�������
����λ�ã�
��    ע��
*******************************************************************************/
void InF_FreezeSwitch(ulong32 V_ulDataCode, uchar8 *V_ucSwich_Time)
{
    uchar8 V_ucDataBuff[C_FreezeMAXLen];
	ushort16 V_usDataLength;

    V_usDataLength = C_FreezeMAXLen;

	switch(V_ulDataCode)
	{
		case CChange_TZ_Time:
		{
			if ( Inf_GetRecordData( V_ucDataBuff, &V_usDataLength, C_FrzOAD, C_Change_TimeZone_Type ) == C_OK )
			{
				PF_CopyDataBytes(&V_ucSwich_Time[0], &V_ucDataBuff[0], CLDate_Time);
				InF_Write_Data(C_Msg_Freeze, C_RelatedOAD_TimeZone, &V_ucDataBuff[0], V_usDataLength, C_W_SafeFlag);
			}
		}break;
		case CChange_PT_Time:
		{
            if ( Inf_GetRecordData( V_ucDataBuff, &V_usDataLength, C_FrzOAD, C_Change_TimePeriod_Type ) == C_OK )
			{
				PF_CopyDataBytes(&V_ucSwich_Time[0], &V_ucDataBuff[0], CLDate_Time);
				InF_Write_Data(C_Msg_Freeze,C_RelatedOAD_TimeRegion, &V_ucDataBuff[0], V_usDataLength, C_W_SafeFlag);
			}
		}break;
		case CChange_Rate:
		{
            if ( Inf_GetRecordData( V_ucDataBuff, &V_usDataLength, C_FrzOAD, C_Change_Fate_Type) == C_OK)
			{
				PF_CopyDataBytes(&V_ucSwich_Time[0], &V_ucDataBuff[0], CLDate_Time);
				InF_Write_Data(C_Msg_Freeze, C_RelatedOAD_RateTalbe, &V_ucDataBuff[0], V_usDataLength, C_W_SafeFlag);
			}
		}break;
		case CChange_Ladder:
		{
            if ( Inf_GetRecordData(V_ucDataBuff, &V_usDataLength, C_FrzOAD, C_Change_Ladder_Type) == C_OK)
			{
				PF_CopyDataBytes(&V_ucSwich_Time[0], &V_ucDataBuff[0], CLDate_Time);
				InF_Write_Data(C_Msg_Freeze,C_RelatedOAD_StepTable, &V_ucDataBuff[0], V_usDataLength, C_W_SafeFlag);
			}
		}break;
		default:
		 break;
	}
	return;
}

/*****************************************************************************************
����ԭ�ͣ� void Msg_Freeze(Str_Msg_Parameter *P_Msg)
����������������Ϣ����
��������� P_Msg,���յ���Ϣ
��������� ��
���ز����� ��
����λ�ã���Ϣ����
��    ע:
*****************************************************************************************/
#define C_698Free_OADTabCycleOffset     1          /*����OAD�б�����������ƫ��*/
void Msg_Freeze(Str_Msg_Parameter *P_Msg)
{
	uchar8 i, V_ucNum;
	uchar8 *pParm;
	uchar8 V_ucCurrentTime[CLDate_Time];
	uchar8 V_ucFreezeTime[CLDate_Time] = {0};
	uchar8 V_ucSettleDay[CLDate_Time*2];
	uchar8 V_ucDataBuff[C_FreezeMAXLen] = {0}; /*buffer�����*/
	ushort16 V_usDataLength = C_FreezeMAXLen;
	ushort16 PDataLength, V_usDataEncode;
	uchar8 V_uc7DayAddTime[CLDate_Time];
	uchar8	V_ucTemp;
	uchar8	V_ucLastFreezeTime[16];
	uchar8	V_ucNowFreezeTime[CLDate_Time*2];
	Str_Msg_Parameter Str_Msg_Freeze;
	uchar8  V_Msg_Parameter[2];
	ulong32	V_Data_Id_OAD[3], V_ulNum = 0;
	ushort16 V_Data_Len;
	uchar8 V_ucResult;
    ushort16 V_usOAD[100 * 3] = {0};
    uchar8 V_ucBeginTime[CLDate_Time] = {0}, V_ucNowFreezeTime_B[CLDate_Time], V_Num, V_usOADNum;
    ulong32 V_FreezeNum;
    ushort16 V_usNum = 0;
    ushort16 V_usRemainder = 0, V_usTemp = 0, V_usi;
    uchar8	V_ucFlag = C_NoAddSettleFreezeFlag;
    uchar8	V_ucPowerOffTime[CLDate_Time*2];
    ulong32 V_uldaynum = 0, V_uldaynum1 = 0, V_ulSubDays = 0, V_ulSubDays_L = 0;

	if(P_Msg->PowerFlag != C_PowerOn)
	{
		return;
	}
	pParm = P_Msg->Parameter;

	if ( (*pParm == Pt_Dispatch_Timing)
	  && (P_Msg->Length == Pt_Dispatch_Timing_Len + 1)
	  && (*(pParm + 1) == C_SystemSecondChange) )         /*������仯*/
	{
		/*˲ʱ���ᶨʱ��*/
		if( PF_Check_CRC( (uchar8 *)&FreezeTimerTable.FreezeTimer, 4) == C_OK )   /*�ж�CRC*/
		{
			if( FreezeTimerTable.FreezeTimer != 0 )
			{
				FreezeTimerTable.FreezeTimer--;
				FreezeTimerTable.V_CRC16 = PF_Cal_CRC( (uchar8 *)&FreezeTimerTable.FreezeTimer, 2 );
				if(FreezeTimerTable.FreezeTimer == 0)
				{
                    V_usDataLength = C_FreezeMAXLen;
					if( Inf_GetRecordData(V_ucDataBuff, &V_usDataLength, C_FrzOAD, C_Immediate_Type) == C_OK )
					{
						InF_Write_Data(C_Msg_Freeze, C_RelatedOAD_Immid, &V_ucDataBuff[0], V_usDataLength, C_W_SafeFlag);
					}
				}
			}
         }
	}

	if ( (*pParm == Pt_Dispatch_Timing)
	  && (P_Msg->Length == Pt_Dispatch_Timing_Freeze_Len + 1)
	  && (*(pParm + 1) == C_SystemMinChange))             /*����1min*/
	{
		PDataLength = CLDate_Time;
		InF_Read_Data(CDate_Time, &V_ucCurrentTime[0], &PDataLength, &V_usDataEncode);

		if( PF_Campare_Data(&V_ucCurrentTime[0], (pParm+2), CLDate_Time) == C_LessThan )       /*����¼�ĵ�����*/
		{
			return;
		}
		/*���Ӷ���(ÿ���Ӷ�����)*/
		SF_GetFreeze_StartTime( &V_ucFreezeTime[0] );
		PDataLength = 2;

		if(PF_Campare_Data(&V_ucCurrentTime[0], &V_ucFreezeTime[0], CLDate_Time) != C_LessThan)
		{
		    /*���Ӷ���8�ַ����ֱ�洢*/
			V_ucNum = InF_GetMinFreezeTolNum();          /*��ȡ���Ӷ����ܵķ�����,1-8��Ч*/
			if( (V_ucNum >= 1) && (V_ucNum <= 8) )
			{
				for( i = 0; i < V_ucNum; i++)
				{
                    V_usDataLength = C_FreezeMAXLen;
					if( (Inf_GetRecordData(V_ucDataBuff, &V_usDataLength, C_FrzOAD, (C_Minute_Type + i)) ) == C_OK)
					{
						if(PF_Campare_Data(&V_ucDataBuff[0], (pParm + 2), CLDate_Time) == C_GreaterThan)     /*����¼�õ�����*/
						{
							PF_CopyDataBytes((pParm + 2), &V_ucDataBuff[0], CLDate_Time);
						}
						V_ulNum = i;
						V_ulNum <<= 21;         /*DI2�ĸ�3λ������Ӷ���ķ�����*/
						V_ucDataBuff[0] = 0;    /*���Ӷ��ᡢ��Ϊ0*/
						InF_Write_Data(C_Msg_Freeze, (C_RelatedOAD_Min|V_ulNum), V_ucDataBuff, V_usDataLength, C_W_SafeFlag);
					}
				}
			}
		}
	}
	else if ( (*pParm == Pt_Dispatch_Timing)
		   && (P_Msg->Length == Pt_Dispatch_Timing_Freeze_Len + 1)
		   && (*(pParm + 1) == C_SystemHourChange))       /*Сʱ�仯*/
	{
		PDataLength = CLDate_Time;
		InF_Read_Data(CDate_Time, &V_ucCurrentTime[0], &PDataLength,&V_usDataEncode);

		if(PF_Campare_Data(&V_ucCurrentTime[0], (pParm + 2), CLDate_Time) == C_LessThan)     /*����¼�ĵ�����*/
		{
			return;
		}
		V_ucCurrentTime[0] = 0;    /*�����*/
		V_ucCurrentTime[1] = 0;    /*���ӹ���*/

		/*Сʱ����*/
		SF_GetFreeze_StartTime(&V_ucFreezeTime[0]);
		if(PF_Campare_Data(&V_ucCurrentTime[0], &V_ucFreezeTime[0], CLDate_Time) != C_LessThan)
		{
			V_ucFreezeTime[0] = 0;     /*�����*/
			V_ucFreezeTime[1] = 0;     /*���ӹ���*/

            V_usDataLength = C_FreezeMAXLen;
            if((Inf_GetRecordData(V_ucDataBuff, &V_usDataLength, C_FrzOAD, C_Hour_Type)) == C_OK)
            {
                if(PF_Campare_Data(&V_ucDataBuff[0], (pParm + 2), CLDate_Time) == C_GreaterThan)    /*����¼�ĵ�����*/
                {
                    PF_CopyDataBytes( (pParm + 2), &V_ucDataBuff[0], CLDate_Time );
                }
                V_ucDataBuff[0] = 0;      /*Сʱ���ᡢ��Ϊ0*/
                V_ucDataBuff[1] = 0;      /*Сʱ���ᡢ��Ϊ0*/
                InF_Write_Data(C_Msg_Freeze, C_RelatedOAD_Hour, V_ucDataBuff, V_usDataLength, C_W_SafeFlag);
            }
		}
	}
	else if ( (*pParm == Pt_Dispatch_Timing)
		   && (P_Msg->Length == Pt_Dispatch_Timing_Freeze_Len + 1)
		   && (*(pParm + 1) == C_SystemDateChange) )      /*�ձ仯*/
	{
		PDataLength = CLDate_Time;
		InF_Read_Data(CDate_Time, &V_ucCurrentTime[0], &PDataLength, &V_usDataEncode);

		if( PF_Campare_Data(&V_ucCurrentTime[0], (pParm + 2), CLDate_Time) == C_LessThan )      /*����¼�ĵ�����*/
		{
			return;
		}
		memset(&V_ucCurrentTime[0], 0x00, 3);    /*�롢�֡�ʱ����*/

		/*�ն���*/
		SF_GetFreeze_StartTime(&V_ucFreezeTime[0]);
		/*ʱ���ж�:������ʼʱ��*/
		if(PF_Campare_Data(&V_ucCurrentTime[1], &V_ucFreezeTime[1], CLD_Free_StartTime) != C_LessThan)
		{
			memset(&V_ucFreezeTime[0], 0x00, 3);    /*�롢�֡�ʱ����*/

            V_usDataLength = C_FreezeMAXLen;
            if((Inf_GetRecordData(V_ucDataBuff, &V_usDataLength, C_FrzOAD, C_Day_Type)) == C_OK)
            {
                if(PF_Campare_Data(&V_ucDataBuff[0], (pParm + 2), CLDate_Time) == C_GreaterThan)     /*����¼�ĵ�����*/
                {
                    PF_CopyDataBytes((pParm+2), &V_ucDataBuff[0], CLDate_Time);
                }
                memset(&V_ucDataBuff[0], 0x00, 3);    /*�롢�֡�ʱ����*/

                InF_Write_Data(C_Msg_Freeze,C_RelatedOAD_Day, &V_ucDataBuff[0], V_usDataLength, C_W_SafeFlag);

                InF_ClearVoltageQR_Data_D();
            }
		}

		Str_Msg_Freeze.SourceAddr = C_Msg_Freeze;	        /*Դ��Ϣ��*/
		Str_Msg_Freeze.DerictAddr = C_Msg_DemandMetering;	/*Ŀ����Ϣ��*/
		Str_Msg_Freeze.Length = Pt_DemandStatus_Len + 1;	/*Parameter�ĳ���*/
		V_Msg_Parameter[0] = Pt_DemandStatus;		        /*����*/
		V_Msg_Parameter[1] = C_DataFreeze;		            /*����*/
		Str_Msg_Freeze.Parameter = V_Msg_Parameter;	        /*����*/

		InF_WriteMessege(&Str_Msg_Freeze);
	}
	else if( (*pParm == Pt_Dispatch_Timing)
		  && (P_Msg->Length == Pt_Dispatch_Timing_Freeze_Len + 1)
		  && (*(pParm + 1) == C_SystemMonthChange) )      /*�±仯*/
	{
		PDataLength = CLDate_Time;
		InF_Read_Data(CDate_Time, &V_ucCurrentTime[0], &PDataLength, &V_usDataEncode);

		if( PF_Campare_Data(&V_ucCurrentTime[0], (pParm + 2), CLDate_Time) == C_LessThan )     /*����¼�ĵ�����*/
		{
			return;
		}
		memset(&V_ucCurrentTime[0], 0x00, 3);  /*�롢�֡�ʱ����*/
		V_ucCurrentTime[3] = 1;                /*�չ���*/

		/*�¶���*/
		SF_GetFreeze_StartTime(&V_ucFreezeTime[0]);
		/*ʱ���ж�:������ʼʱ��*/
		if( PF_Campare_Data(&V_ucCurrentTime[1], &V_ucFreezeTime[1], CLD_Free_StartTime) != C_LessThan )
		{
			memset(&V_ucFreezeTime[0], 0x00, 3);     /*�롢�֡�ʱ����*/
			V_ucFreezeTime[3] = 1;                   /*�չ���*/

            V_usDataLength = C_FreezeMAXLen;
            if((Inf_GetRecordData(V_ucDataBuff, &V_usDataLength, C_FrzOAD, C_Month_Type)) == C_OK)
            {
                if( PF_Campare_Data(&V_ucDataBuff[0], (pParm + 2), CLDate_Time) == C_GreaterThan)    /*����¼�ĵ�����*/
                {
                    PF_CopyDataBytes((pParm + 2), &V_ucDataBuff[0], CLDate_Time);
                }
                memset(&V_ucDataBuff[0], 0x00, 3);   /*�¶����롢�֡�ʱ����*/
                V_ucDataBuff[3] = 1;                 /*�¶��ᡢ��Ϊ1*/
                InF_Write_Data(C_Msg_Freeze, C_RelatedOAD_Month, &V_ucDataBuff[0], V_usDataLength, C_W_SafeFlag);
            }
		}
	}
#if 0
	else if((*pParm == Pt_Dispatch_Timing) && (P_Msg->Length == Pt_Dispatch_Timing_Len+1)&&(*(pParm+1)==C_SystemYearChange))///*��仯*///
	{
		PDataLength=CLDate_Time;
		InF_Read_Data(CDate_Time,&V_ucCurrentTime[0],&PDataLength);

		V_ucCurrentTime[0] = 0; /*�����*/
		V_ucCurrentTime[1] = 0; /*���ӹ���*/
		V_ucCurrentTime[2] = 0; /*Сʱ����*/
		V_ucCurrentTime[3] = 1; /*�չ���*/
		V_ucCurrentTime[4] = 1; /*�¹���*/

		/*�궳��*/
		SF_GetFreeze_StartTime(CY_Free_StartTime, &V_ucFreezeTime[0], (uchar8)CLY_Free_StartTime);
		/*ʱ���ж�:������ʼʱ��*/
        if(PF_Campare_Data(&V_ucCurrentTime[1], &V_ucFreezeTime[1], CLD_Free_StartTime) != C_LessThan)
        {
            V_ucFreezeTime[0] = 0;  /*�����*/
            V_ucFreezeTime[1] = 0;  /*���ӹ���*/
            V_ucFreezeTime[2] = 0;  /*Сʱ����*/
            V_ucFreezeTime[3] = 1;  /*�չ���*/
            V_ucFreezeTime[4] = 1;  /*�¹���*/

            /*���ʱ���ж�*/
            PDataLength=CLM_Free_OADTabLen_T;
            if(InF_Read_Data(CM_Free_OADTabLen_T, &V_uc_Num_interval[0], &PDataLength) == C_OK)
            {
                PF_Buffer4ToUlong32(&V_uc_Num_interval[2], &V_ulInterval,2);


                /*����2��ʱ����*/
                PF_BCDDECBytes(&V_ucCurrentTime[5], &V_ucFreezeTime[5], (uchar8 * )&V_ulSubResult, 1);

                if(V_ulInterval == 0)   /*�����ʱ��Ϊ0.Ĭ��1*/
                {
                    V_ulInterval = 1;
                }

                if(V_ulSubResult % V_ulInterval == 0)
                {
                    V_usDataLength = C_FreezeMAXLen;
                    if( ( Inf_GetRecordData(V_ucDataBuff, &V_usDataLength, C_FrzOAD, C_Year_Type ) ) == C_OK)
                    {
                        InF_Write_Data(C_Msg_Freeze, C_RelatedOAD_Year, &V_ucDataBuff[0], V_usDataLength, C_W_SafeFlag);
                    }
                }
            }
        }

	}
#endif

	else if( (*pParm == Pt_MsgFreezeImmediately) && (P_Msg->Length == Pt_MsgFreezeImmediately_Len + 1) )    /*ͨ��˲ʱ����*/
    {
        V_usDataLength = C_FreezeMAXLen;
		if( Inf_GetRecordData(V_ucDataBuff, &V_usDataLength, C_FrzOAD, C_Immediate_Type) == C_OK )
		{
			InF_Write_Data(C_Msg_Freeze, C_RelatedOAD_Immid, &V_ucDataBuff[0], V_usDataLength, C_W_SafeFlag);
		}
	}
	else if( (*pParm == Pt_7DayAdd_FreezeTime) && (P_Msg->Length == Pt_7DayAdd_FreezeTime_Len + 1))         /*��7���ն���*/
	{
		if(P_Msg->SourceAddr == C_Msg_Communication)
		{
			return;
		}

		PF_CopyDataBytes( pParm, &V_uc7DayAddTime[0], Pt_7DayAdd_FreezeTime_Len);

		PDataLength = CLDate_Time;
		if( InF_Read_Data(CDate_Time, &V_ucCurrentTime[0], &PDataLength, &V_usDataEncode) == C_OK )
		{
			if( (PF_DataTimeActive_698(V_ucCurrentTime, C_DT_Start_ss, CLDate_Time) != C_OK) )
			{
                return;
			}
#if 0
			PDataLength = CLDay_Freeze_Time;

			if(InF_Read_Data(CDay_Freeze_Time,&V_ucFreezeTime[0],&PDataLength)==C_OK)
			V_ucFreezeTime[1] = 0;
			V_ucFreezeTime[2] = 0;
			if(PF_Campare_Data(&V_ucFreezeTime[0],&V_uc7DayAddTime[1],CLDay_Freeze_Time)==C_GreaterThan)
			{
                SF_GetNextDay(&V_uc7DayAddTime[3],0);	/*������1*/
			}
            SF_AddMonthFreeze(V_ucCurrentTime, V_uc7DayAddTime);   /*���¶���:20�淶����Ҫ�ϵ粹�¶���*/
#endif

			/*��OAD��OAD����*/
			PDataLength = CLD_Free_OADTabLen_T;
			if(InF_Read_Data(CD_Free_OADTabLen_T, &V_usOADNum, &PDataLength, &V_usDataEncode) != C_OK)
			{
				return;
			}

			if( (V_usOADNum > C_FreezeMAXRelatedOAD) || (V_usOADNum == 0) )   /*����96����û�й����б�*/
			{
				return;
			}

			V_Data_Len = C_698Free_OADTabDataType * V_usOADNum;
			if( InF_ReadOADTab_Data(CD_Free_OADTab, (uchar8 *)&V_usOAD, &V_Data_Len) != C_OK )    /*���ն�������*/
			{
				return;
			}
			SF_GetFreeze_StartTime(V_ucBeginTime);/*�ն�����ʼʱ����ȥ����ֱ��Ĭ��2000��1��1��*/

			if( PF_TimeSub_Day_698(V_ucCurrentTime, V_ucBeginTime, &V_ulSubDays) != C_GreaterThan )    /*���㵱ǰʱ�����ն�����ʼʱ���������*/
			{
				return;
			}
			if ( V_usOAD[C_698Free_OADTabCycleOffset] == 0 )
			{
				V_usOAD[C_698Free_OADTabCycleOffset] = 1;
			}

			V_usRemainder = (ushort16)(V_ulSubDays % V_usOAD[C_698Free_OADTabCycleOffset]);    /*�����������������*/

			PF_CopyDataBytes(&V_ucCurrentTime[0], V_ucNowFreezeTime, CLDate_Time);
			memset(V_ucNowFreezeTime, 0x00, 3);

			for(V_usTemp = 0; V_usTemp < V_usRemainder; V_usTemp++)    /*�������һ�β��ն���ʱ��*/
			{
				SF_GetNextDay(&V_ucNowFreezeTime[3], 0);
			}

			/*20150804�޸�Ϊ�ϵ���ж���Ҫ�������һ�ζ���ʱ�����һ�ն���ʱ����ͬ�򲻽��в��� lzy*/
			V_Data_Id_OAD[0] = C_RelatedOAD_Day_1;
			V_Data_Id_OAD[1] = CFreeTime;
			V_Data_Id_OAD[2] = 0xFFFFFFFF;
			V_Data_Len = 16;
			V_ucResult = Inf_Read_FrozenData_OneOAD(V_Data_Id_OAD, V_ucLastFreezeTime, &V_Data_Len);

            if( V_ucResult == C_OK)  /*���ݶ�����ȷ�űȽ�*/
            {
                if ( PF_Campare_Data(V_ucNowFreezeTime, V_ucLastFreezeTime, CLDate_Time) != C_GreaterThan )
                {
                    return;   /*��ͬ��С���򲻲�����*/
                }
                else
                {
                    ;  /*���ڣ��򲹶���*/
                }
            }
            else if( V_ucResult == C_NoData )   /*�����ݣ��򲹶���*/
            {
               ;
            }
            else    /*�����쳣����CRC�ȣ���������*/
            {
                return;
            }

			if( PF_TimeSub_Day_698(V_ucNowFreezeTime, V_uc7DayAddTime, &V_ulSubDays_L) != C_GreaterThan)    /*�������һ�β��ն���ʱ������͹���ʱ���������*/
			{
				return;
			}
			V_usNum = (ushort16)(V_ulSubDays_L / V_usOAD[C_698Free_OADTabCycleOffset]);

            if(V_usNum > 6)
            {
                V_Num = 6;
            }
            else
            {
                V_Num = (uchar8)V_usNum;
            }

			PF_CopyDataBytes(V_ucNowFreezeTime, V_ucNowFreezeTime_B, CLDate_Time);

			for(V_ucTemp = 0; V_ucTemp < V_Num; V_ucTemp++)    /*��������һ�β��ն���ʱ��*/
			{
				for(V_usi = 0; V_usi < V_usOAD[C_698Free_OADTabCycleOffset]; V_usi++)
				{
					SF_GetNextDay(&V_ucNowFreezeTime_B[3], 0);
				}
			}

			PDataLength = CLSettle_Day1;
			if ( InF_Read_Data(CSettle_Day1, &V_ucSettleDay[2], &PDataLength, &V_usDataEncode) != C_OK )
            {
                memset(&V_ucSettleDay[2], 0x00, CLSettle_Day1);
            }
			PF_OneDataReversed(&V_ucSettleDay[2], &V_ucSettleDay[2], CLSettle_Day1);/*���������ݲ�˳���յͣ�ʱ�ߣ������*/
			V_ucSettleDay[0] = 0x00;
			V_ucSettleDay[1] = 0x00;

			PF_CopyDataBytes( pParm, &V_ucPowerOffTime[0], Pt_7DayAdd_FreezeTime_Len);

			if( PF_Campare_Data(&V_ucPowerOffTime[4], &V_ucNowFreezeTime_B[4], C_YYMMLen) == C_Equal)       /*�ꡢ�����*/
			{
				if ( (PF_Campare_Data(&V_ucSettleDay[0], &V_ucNowFreezeTime_B[0], C_DDhhmmssLen) == C_LessThan)
				  && (PF_Campare_Data(&V_ucSettleDay[0], &V_ucPowerOffTime[0], C_DDhhmmssLen) != C_LessThan) )  /*�������µ�һ��������С�ڲ�����������������*/
				{
					V_ucFlag = C_NeedAddSettleFreezeFlag;
				}
			}
			else if( PF_Campare_Data(&V_ucPowerOffTime[4], &V_ucNowFreezeTime_B[4], C_YYMMLen) == C_LessThan ) /*�ꡢ�´�*/
			{
				PF_BufferXToUlong32(&V_ucNowFreezeTime_B[5], &V_uldaynum, 2);
				V_uldaynum = V_uldaynum * 12 + V_ucNowFreezeTime_B[4];
				
				PF_BufferXToUlong32(&V_ucPowerOffTime[5], &V_uldaynum1, 2);
				V_uldaynum1 = V_uldaynum1 * 12 + V_ucPowerOffTime[4];
				
				if ( ( (V_uldaynum == (V_uldaynum1 + 1))
						&& ( (PF_Campare_Data(V_ucNowFreezeTime_B, V_ucSettleDay, C_DDhhmmssLen) == C_GreaterThan)
							|| ( PF_Campare_Data(V_ucPowerOffTime, V_ucSettleDay, C_DDhhmmssLen) != C_GreaterThan) ) )
				    || ( V_uldaynum > (V_uldaynum1 + 1) ) )
				{
					V_ucFlag = C_NeedAddSettleFreezeFlag;
				}
			}

            V_usDataLength = C_FreezeMAXLen;
            if ( Inf_GetRecordData(V_ucDataBuff, &V_usDataLength, C_FrzOAD, C_Day_Type_Add) != C_OK )
            {
                return;
            }

            if(V_ucFlag == C_NeedAddSettleFreezeFlag)     /*�����������*/
			{
                V_usDataLength = C_FreezeMAXLen;
				Inf_GetFrozenData_Settle23(V_ucDataBuff, &V_usDataLength, 0x00, CD_Free_OADTab);
			}
			PF_CopyDataBytes(V_ucNowFreezeTime_B, V_ucDataBuff, CLDate_Time);
			PF_CopyDataBytes(&V_ucDataBuff[4], &V_ucSettleDay[4], C_YYMMLen);    /*��ֵ����һ��������ʱ������*/

			for(V_ucTemp = 0; V_ucTemp < (V_Num + 1); V_ucTemp++)
			{
#if 0
				if(C_Meter_Type == C_L_SmartMeter)
				{
					SF_GetFrozenDataLocal_Freeze(V_ucDataBuff1);
					InF_Write_Data(C_Msg_Freeze,CChargeBal_Free_1,V_ucDataBuff1,CLChargeBal_Free_1,C_W_SafeFlag);
				}
#endif
				InF_Write_Data(C_Msg_Freeze, C_RelatedOAD_Day, &V_ucDataBuff[0], V_usDataLength, C_W_SafeFlag);	 /*д��������*/

				InF_ClearVoltageQR_Data_D();

				if(V_ucTemp == 0)		/*д����һ�ζ�������»�ȡ�������ݣ����յ�ѹ�ϸ�����������*/
				{
					if(V_ucFlag == C_NeedAddSettleFreezeFlag)
					{
                        V_usDataLength = C_FreezeMAXLen;
						Inf_GetFrozenData_Settle23(V_ucDataBuff, &V_usDataLength, 0x00, CD_Free_OADTab);
					}
					else
					{
                        V_usDataLength = C_FreezeMAXLen;
						if( Inf_GetRecordData(V_ucDataBuff, &V_usDataLength, C_FrzOAD, C_Day_Type_Add) != C_OK )
                        {
                            break;
                        }
						PF_Buffer4ToUlong32(&V_ucDataBuff[CLDate_Time], &V_FreezeNum, 4);
						V_FreezeNum--;
						PF_Ulong32ToBuffer4(&V_ucDataBuff[CLDate_Time], &V_FreezeNum, 4);
					}
					PF_CopyDataBytes(V_ucNowFreezeTime_B, V_ucDataBuff, CLDate_Time);
				}
				/**************************�������ж�**************************************/
				PF_CopyDataBytes(&V_ucDataBuff[0], &V_ucSettleDay[CLDate_Time], CLDate_Time);
				for(V_usi = 0; V_usi < V_usOAD[C_698Free_OADTabCycleOffset]; V_usi++)
				{
					SF_GetNextDay(&V_ucDataBuff[3], 1);
				}
				if(V_ucSettleDay[4] != V_ucDataBuff[4])	  /*�±仯*/
				{
					PF_CopyDataBytes(&V_ucDataBuff[4], &V_ucSettleDay[4], C_YYMMLen);   /*ȡ�ꡢ�·�*/
				}
				if ((PF_Campare_Data(&V_ucDataBuff[0],V_ucSettleDay,CLDate_Time) == C_GreaterThan)	    /*�������ն���ʱ�����һ��������ͬ*/
				 && (PF_Campare_Data(&V_ucSettleDay[CLDate_Time],V_ucSettleDay,CLDate_Time) != C_GreaterThan))
				{
                    V_usDataLength = C_FreezeMAXLen;
					Inf_GetFrozenData_Settle23(V_ucDataBuff, &V_usDataLength, 0x00, CD_Free_OADTab);
				}
				PF_Buffer4ToUlong32(&V_ucDataBuff[CLDate_Time], &V_FreezeNum, 4);
				V_FreezeNum++;
				PF_Ulong32ToBuffer4(&V_ucDataBuff[CLDate_Time], &V_FreezeNum, 4);
			}
		}
	}
	return;
}

/*******************************************************************************
����ԭ�ͣ�void SF_GetNextDay(uchar8 *P_ucDay,uchar8 V_ucMode)
����������������1����1
���������*P_ucDay �����׵�ַ,�ӵ͵���Ϊ�����꣨698 hex��ʽ����V_ucMode Ϊ0��ʾ������1��Ϊ1��ʾ������1  
���������*P_ucDay �����׵�ַ
���ز�������
����λ�ã�
��    ע��
*******************************************************************************/
void SF_GetNextDay(uchar8 *P_ucDay,uchar8 V_ucMode)
{
	ushort16 V_usYear;
	
	if(V_ucMode == 0)
	{
		if(*P_ucDay > 1)
		{
			/*������1*/
			*P_ucDay -= 1;
		}
		else
		{
			if(*(P_ucDay + 1) > 1)
			{
				/*�·ݼ�1*/
				*(P_ucDay + 1) -= 1;
				
				*P_ucDay = PF_BCDtoHexOneByte(Day[*(P_ucDay + 1)]);
				if( *(P_ucDay+1) == 2)
				{
					PF_Buffer2ToUshort16(P_ucDay + 2,&V_usYear);
					
					if( ( ( (V_usYear % 4) == 0) && ((V_usYear % 100) !=0) )
						|| ((V_usYear % 400) == 0) )
					{
						*P_ucDay = 29;
					}
				}
			}
			else
			{
				*P_ucDay = 31;
				*(P_ucDay + 1) = 12;
				/*��ݼ�1*/
				PF_Buffer2ToUshort16(P_ucDay + 2,&V_usYear);
				V_usYear -= 1;
				PF_Ushort16ToBuffer2(P_ucDay + 2,&V_usYear);
			}
		}
	}
	else
	{
		if( *P_ucDay < PF_BCDtoHexOneByte( Day[P_ucDay[1]]) )
		{
			/*������1*/
			*P_ucDay += 1;
		}
		else
		{
			if(( *(P_ucDay + 1) == 2) && (*P_ucDay == 28))
			{
				PF_Buffer2ToUshort16(P_ucDay + 2,&V_usYear);
					
				if( ( ( (V_usYear % 4) == 0) && ((V_usYear % 100) != 0) )
					|| ((V_usYear % 400) == 0) )
				{
					*P_ucDay = 29;
				}
				else
				{
					*P_ucDay = 1;
					*(P_ucDay + 1) = 3;
				}
			}
			else
			{
				if(*(P_ucDay + 1) < 12)
				{
					/*�·ݼ�1*/
					*(P_ucDay + 1) += 1;

					*P_ucDay = 1;
				}
				else
				{
					*P_ucDay = 1;
					*(P_ucDay + 1) = 1;
					/*��ݼ�1*/
					PF_Buffer2ToUshort16(P_ucDay + 2,&V_usYear);
					V_usYear += 1;
					PF_Ushort16ToBuffer2(P_ucDay + 2,&V_usYear);
				}
			}
		}
	}
}
