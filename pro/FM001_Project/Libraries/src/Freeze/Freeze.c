///*****************************************************************************************///
///*Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     Freeze.c
///*Version:       V1
///*Date:          2014-3-12
///*Description:   冻结处理
///*Function List:
///*****************************************************************************************///
///*History1:      第1次修改
///*内容1. Date:
///*   	   Author:
///*       Modification:
		///***********************************************///
///*内容2. Date:
///*   	   Author:
///*       Modification:
		///*********************************************************************************///
///*History2:      第2次修改
///*内容1. Date:
///*   	   Author:
///*       Modification:
		///***********************************************///
///*内容2. Date:
///*   	   Author:
///*       Modification:
///*****************************************************************************************///

#include "Public.h"
#include "Freeze.h"

Str_FreezeTimerTable FreezeTimerTable;

void SF_GetFreeze_StartTime(uchar8 *pFreezeTime)
{
#if 0	/*原来屏蔽*/
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

#if 0	/*原来屏蔽*/
		}
#endif
}

/*******************************************************************************
函数原型：void InF_FreezeDayAfterPowerUp (Void)
功能描述：上电后触发补7个日冻结消息，消息内容包括6个字节的补日冻结起始时间
输入参数：无
输出参数：无
返回参数：无
调用位置：
备    注：
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
		
		Str_Msg_Freeze.SourceAddr = C_Msg_Freeze;	/*源消息号*/
		Str_Msg_Freeze.DerictAddr = C_Msg_Freeze;	/*目的消息号*/
		Str_Msg_Freeze.Length = Pt_7DayAdd_FreezeTime_Len + 1;		/*Parameter的长度*/
		Str_Msg_Freeze.Parameter = &V_uc7DayAddTime[0];	/*参数*/

		InF_WriteMessege(&Str_Msg_Freeze);
   	}
    return;
}


/*******************************************************************************
函数原型：void InF_FreezeSwitch(ulong32 V_ulDataCode, uchar8 *V_ucSwich_Time)
功能描述：写约定冻结
输入参数：V_ulDataCode   约定冻结切换时间的标识码
          V_ucSwich_Time   设置的切换时间
输出参数：无
返回参数：无
调用位置：
备    注：
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
函数原型： void Msg_Freeze(Str_Msg_Parameter *P_Msg)
功能描述：冻结消息处理
输入参数： P_Msg,接收的消息
输出参数： 无
返回参数： 无
调用位置：消息处理
备    注:
*****************************************************************************************/
#define C_698Free_OADTabCycleOffset     1          /*冻结OAD列表中周期所在偏移*/
void Msg_Freeze(Str_Msg_Parameter *P_Msg)
{
	uchar8 i, V_ucNum;
	uchar8 *pParm;
	uchar8 V_ucCurrentTime[CLDate_Time];
	uchar8 V_ucFreezeTime[CLDate_Time] = {0};
	uchar8 V_ucSettleDay[CLDate_Time*2];
	uchar8 V_ucDataBuff[C_FreezeMAXLen] = {0}; /*buffer开最大*/
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
	  && (*(pParm + 1) == C_SystemSecondChange) )         /*调度秒变化*/
	{
		/*瞬时冻结定时器*/
		if( PF_Check_CRC( (uchar8 *)&FreezeTimerTable.FreezeTimer, 4) == C_OK )   /*判断CRC*/
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
	  && (*(pParm + 1) == C_SystemMinChange))             /*调度1min*/
	{
		PDataLength = CLDate_Time;
		InF_Read_Data(CDate_Time, &V_ucCurrentTime[0], &PDataLength, &V_usDataEncode);

		if( PF_Campare_Data(&V_ucCurrentTime[0], (pParm+2), CLDate_Time) == C_LessThan )       /*不记录改点数据*/
		{
			return;
		}
		/*分钟冻结(每分钟都冻结)*/
		SF_GetFreeze_StartTime( &V_ucFreezeTime[0] );
		PDataLength = 2;

		if(PF_Campare_Data(&V_ucCurrentTime[0], &V_ucFreezeTime[0], CLDate_Time) != C_LessThan)
		{
		    /*分钟冻结8种方案分别存储*/
			V_ucNum = InF_GetMinFreezeTolNum();          /*读取分钟冻结总的方案号,1-8有效*/
			if( (V_ucNum >= 1) && (V_ucNum <= 8) )
			{
				for( i = 0; i < V_ucNum; i++)
				{
                    V_usDataLength = C_FreezeMAXLen;
					if( (Inf_GetRecordData(V_ucDataBuff, &V_usDataLength, C_FrzOAD, (C_Minute_Type + i)) ) == C_OK)
					{
						if(PF_Campare_Data(&V_ucDataBuff[0], (pParm + 2), CLDate_Time) == C_GreaterThan)     /*不记录该点数据*/
						{
							PF_CopyDataBytes((pParm + 2), &V_ucDataBuff[0], CLDate_Time);
						}
						V_ulNum = i;
						V_ulNum <<= 21;         /*DI2的高3位代表分钟冻结的方案号*/
						V_ucDataBuff[0] = 0;    /*分钟冻结、秒为0*/
						InF_Write_Data(C_Msg_Freeze, (C_RelatedOAD_Min|V_ulNum), V_ucDataBuff, V_usDataLength, C_W_SafeFlag);
					}
				}
			}
		}
	}
	else if ( (*pParm == Pt_Dispatch_Timing)
		   && (P_Msg->Length == Pt_Dispatch_Timing_Freeze_Len + 1)
		   && (*(pParm + 1) == C_SystemHourChange))       /*小时变化*/
	{
		PDataLength = CLDate_Time;
		InF_Read_Data(CDate_Time, &V_ucCurrentTime[0], &PDataLength,&V_usDataEncode);

		if(PF_Campare_Data(&V_ucCurrentTime[0], (pParm + 2), CLDate_Time) == C_LessThan)     /*不记录改点数据*/
		{
			return;
		}
		V_ucCurrentTime[0] = 0;    /*秒归整*/
		V_ucCurrentTime[1] = 0;    /*分钟归整*/

		/*小时冻结*/
		SF_GetFreeze_StartTime(&V_ucFreezeTime[0]);
		if(PF_Campare_Data(&V_ucCurrentTime[0], &V_ucFreezeTime[0], CLDate_Time) != C_LessThan)
		{
			V_ucFreezeTime[0] = 0;     /*秒归整*/
			V_ucFreezeTime[1] = 0;     /*分钟归整*/

            V_usDataLength = C_FreezeMAXLen;
            if((Inf_GetRecordData(V_ucDataBuff, &V_usDataLength, C_FrzOAD, C_Hour_Type)) == C_OK)
            {
                if(PF_Campare_Data(&V_ucDataBuff[0], (pParm + 2), CLDate_Time) == C_GreaterThan)    /*不记录改点数据*/
                {
                    PF_CopyDataBytes( (pParm + 2), &V_ucDataBuff[0], CLDate_Time );
                }
                V_ucDataBuff[0] = 0;      /*小时冻结、秒为0*/
                V_ucDataBuff[1] = 0;      /*小时冻结、分为0*/
                InF_Write_Data(C_Msg_Freeze, C_RelatedOAD_Hour, V_ucDataBuff, V_usDataLength, C_W_SafeFlag);
            }
		}
	}
	else if ( (*pParm == Pt_Dispatch_Timing)
		   && (P_Msg->Length == Pt_Dispatch_Timing_Freeze_Len + 1)
		   && (*(pParm + 1) == C_SystemDateChange) )      /*日变化*/
	{
		PDataLength = CLDate_Time;
		InF_Read_Data(CDate_Time, &V_ucCurrentTime[0], &PDataLength, &V_usDataEncode);

		if( PF_Campare_Data(&V_ucCurrentTime[0], (pParm + 2), CLDate_Time) == C_LessThan )      /*不记录改点数据*/
		{
			return;
		}
		memset(&V_ucCurrentTime[0], 0x00, 3);    /*秒、分、时归整*/

		/*日冻结*/
		SF_GetFreeze_StartTime(&V_ucFreezeTime[0]);
		/*时间判断:大于起始时间*/
		if(PF_Campare_Data(&V_ucCurrentTime[1], &V_ucFreezeTime[1], CLD_Free_StartTime) != C_LessThan)
		{
			memset(&V_ucFreezeTime[0], 0x00, 3);    /*秒、分、时归整*/

            V_usDataLength = C_FreezeMAXLen;
            if((Inf_GetRecordData(V_ucDataBuff, &V_usDataLength, C_FrzOAD, C_Day_Type)) == C_OK)
            {
                if(PF_Campare_Data(&V_ucDataBuff[0], (pParm + 2), CLDate_Time) == C_GreaterThan)     /*不记录改点数据*/
                {
                    PF_CopyDataBytes((pParm+2), &V_ucDataBuff[0], CLDate_Time);
                }
                memset(&V_ucDataBuff[0], 0x00, 3);    /*秒、分、时归整*/

                InF_Write_Data(C_Msg_Freeze,C_RelatedOAD_Day, &V_ucDataBuff[0], V_usDataLength, C_W_SafeFlag);

                InF_ClearVoltageQR_Data_D();
            }
		}

		Str_Msg_Freeze.SourceAddr = C_Msg_Freeze;	        /*源消息号*/
		Str_Msg_Freeze.DerictAddr = C_Msg_DemandMetering;	/*目的消息号*/
		Str_Msg_Freeze.Length = Pt_DemandStatus_Len + 1;	/*Parameter的长度*/
		V_Msg_Parameter[0] = Pt_DemandStatus;		        /*参数*/
		V_Msg_Parameter[1] = C_DataFreeze;		            /*参数*/
		Str_Msg_Freeze.Parameter = V_Msg_Parameter;	        /*参数*/

		InF_WriteMessege(&Str_Msg_Freeze);
	}
	else if( (*pParm == Pt_Dispatch_Timing)
		  && (P_Msg->Length == Pt_Dispatch_Timing_Freeze_Len + 1)
		  && (*(pParm + 1) == C_SystemMonthChange) )      /*月变化*/
	{
		PDataLength = CLDate_Time;
		InF_Read_Data(CDate_Time, &V_ucCurrentTime[0], &PDataLength, &V_usDataEncode);

		if( PF_Campare_Data(&V_ucCurrentTime[0], (pParm + 2), CLDate_Time) == C_LessThan )     /*不记录改点数据*/
		{
			return;
		}
		memset(&V_ucCurrentTime[0], 0x00, 3);  /*秒、分、时归整*/
		V_ucCurrentTime[3] = 1;                /*日归整*/

		/*月冻结*/
		SF_GetFreeze_StartTime(&V_ucFreezeTime[0]);
		/*时间判断:大于起始时间*/
		if( PF_Campare_Data(&V_ucCurrentTime[1], &V_ucFreezeTime[1], CLD_Free_StartTime) != C_LessThan )
		{
			memset(&V_ucFreezeTime[0], 0x00, 3);     /*秒、分、时归整*/
			V_ucFreezeTime[3] = 1;                   /*日归整*/

            V_usDataLength = C_FreezeMAXLen;
            if((Inf_GetRecordData(V_ucDataBuff, &V_usDataLength, C_FrzOAD, C_Month_Type)) == C_OK)
            {
                if( PF_Campare_Data(&V_ucDataBuff[0], (pParm + 2), CLDate_Time) == C_GreaterThan)    /*不记录改点数据*/
                {
                    PF_CopyDataBytes((pParm + 2), &V_ucDataBuff[0], CLDate_Time);
                }
                memset(&V_ucDataBuff[0], 0x00, 3);   /*月冻结秒、分、时归整*/
                V_ucDataBuff[3] = 1;                 /*月冻结、日为1*/
                InF_Write_Data(C_Msg_Freeze, C_RelatedOAD_Month, &V_ucDataBuff[0], V_usDataLength, C_W_SafeFlag);
            }
		}
	}
#if 0
	else if((*pParm == Pt_Dispatch_Timing) && (P_Msg->Length == Pt_Dispatch_Timing_Len+1)&&(*(pParm+1)==C_SystemYearChange))///*年变化*///
	{
		PDataLength=CLDate_Time;
		InF_Read_Data(CDate_Time,&V_ucCurrentTime[0],&PDataLength);

		V_ucCurrentTime[0] = 0; /*秒归整*/
		V_ucCurrentTime[1] = 0; /*分钟归整*/
		V_ucCurrentTime[2] = 0; /*小时归整*/
		V_ucCurrentTime[3] = 1; /*日归整*/
		V_ucCurrentTime[4] = 1; /*月归整*/

		/*年冻结*/
		SF_GetFreeze_StartTime(CY_Free_StartTime, &V_ucFreezeTime[0], (uchar8)CLY_Free_StartTime);
		/*时间判断:大于起始时间*/
        if(PF_Campare_Data(&V_ucCurrentTime[1], &V_ucFreezeTime[1], CLD_Free_StartTime) != C_LessThan)
        {
            V_ucFreezeTime[0] = 0;  /*秒归整*/
            V_ucFreezeTime[1] = 0;  /*分钟归整*/
            V_ucFreezeTime[2] = 0;  /*小时归整*/
            V_ucFreezeTime[3] = 1;  /*日归整*/
            V_ucFreezeTime[4] = 1;  /*月归整*/

            /*间隔时间判断*/
            PDataLength=CLM_Free_OADTabLen_T;
            if(InF_Read_Data(CM_Free_OADTabLen_T, &V_uc_Num_interval[0], &PDataLength) == C_OK)
            {
                PF_Buffer4ToUlong32(&V_uc_Num_interval[2], &V_ulInterval,2);


                /*计算2个时间差几年*/
                PF_BCDDECBytes(&V_ucCurrentTime[5], &V_ucFreezeTime[5], (uchar8 * )&V_ulSubResult, 1);

                if(V_ulInterval == 0)   /*若间隔时间为0.默认1*/
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

	else if( (*pParm == Pt_MsgFreezeImmediately) && (P_Msg->Length == Pt_MsgFreezeImmediately_Len + 1) )    /*通信瞬时冻结*/
    {
        V_usDataLength = C_FreezeMAXLen;
		if( Inf_GetRecordData(V_ucDataBuff, &V_usDataLength, C_FrzOAD, C_Immediate_Type) == C_OK )
		{
			InF_Write_Data(C_Msg_Freeze, C_RelatedOAD_Immid, &V_ucDataBuff[0], V_usDataLength, C_W_SafeFlag);
		}
	}
	else if( (*pParm == Pt_7DayAdd_FreezeTime) && (P_Msg->Length == Pt_7DayAdd_FreezeTime_Len + 1))         /*补7个日冻结*/
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
                SF_GetNextDay(&V_uc7DayAddTime[3],0);	/*天数减1*/
			}
            SF_AddMonthFreeze(V_ucCurrentTime, V_uc7DayAddTime);   /*补月冻结:20规范不需要上电补月冻结*/
#endif

			/*读OAD及OAD个数*/
			PDataLength = CLD_Free_OADTabLen_T;
			if(InF_Read_Data(CD_Free_OADTabLen_T, &V_usOADNum, &PDataLength, &V_usDataEncode) != C_OK)
			{
				return;
			}

			if( (V_usOADNum > C_FreezeMAXRelatedOAD) || (V_usOADNum == 0) )   /*大于96个或没有关联列表*/
			{
				return;
			}

			V_Data_Len = C_698Free_OADTabDataType * V_usOADNum;
			if( InF_ReadOADTab_Data(CD_Free_OADTab, (uchar8 *)&V_usOAD, &V_Data_Len) != C_OK )    /*读日冻结周期*/
			{
				return;
			}
			SF_GetFreeze_StartTime(V_ucBeginTime);/*日冻结起始时间已去除，直接默认2000年1月1日*/

			if( PF_TimeSub_Day_698(V_ucCurrentTime, V_ucBeginTime, &V_ulSubDays) != C_GreaterThan )    /*计算当前时间与日冻结起始时间相差天数*/
			{
				return;
			}
			if ( V_usOAD[C_698Free_OADTabCycleOffset] == 0 )
			{
				V_usOAD[C_698Free_OADTabCycleOffset] = 1;
			}

			V_usRemainder = (ushort16)(V_ulSubDays % V_usOAD[C_698Free_OADTabCycleOffset]);    /*相差天数和周期余数*/

			PF_CopyDataBytes(&V_ucCurrentTime[0], V_ucNowFreezeTime, CLDate_Time);
			memset(V_ucNowFreezeTime, 0x00, 3);

			for(V_usTemp = 0; V_usTemp < V_usRemainder; V_usTemp++)    /*计算最近一次补日冻结时间*/
			{
				SF_GetNextDay(&V_ucNowFreezeTime[3], 0);
			}

			/*20150804修改为上电后判断需要补的最近一次冻结时间和上一日冻结时间相同则不进行补冻 lzy*/
			V_Data_Id_OAD[0] = C_RelatedOAD_Day_1;
			V_Data_Id_OAD[1] = CFreeTime;
			V_Data_Id_OAD[2] = 0xFFFFFFFF;
			V_Data_Len = 16;
			V_ucResult = Inf_Read_FrozenData_OneOAD(V_Data_Id_OAD, V_ucLastFreezeTime, &V_Data_Len);

            if( V_ucResult == C_OK)  /*数据读出正确才比较*/
            {
                if ( PF_Campare_Data(V_ucNowFreezeTime, V_ucLastFreezeTime, CLDate_Time) != C_GreaterThan )
                {
                    return;   /*相同、小于则不补冻结*/
                }
                else
                {
                    ;  /*大于，则补冻结*/
                }
            }
            else if( V_ucResult == C_NoData )   /*无数据，则补冻结*/
            {
               ;
            }
            else    /*其他异常，如CRC等，不补冻结*/
            {
                return;
            }

			if( PF_TimeSub_Day_698(V_ucNowFreezeTime, V_uc7DayAddTime, &V_ulSubDays_L) != C_GreaterThan)    /*计算最近一次补日冻结时间与进低功耗时间相差天数*/
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

			for(V_ucTemp = 0; V_ucTemp < V_Num; V_ucTemp++)    /*计算最早一次补日冻结时间*/
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
			PF_OneDataReversed(&V_ucSettleDay[2], &V_ucSettleDay[2], CLSettle_Day1);/*结算日数据层顺序日低，时高，需调换*/
			V_ucSettleDay[0] = 0x00;
			V_ucSettleDay[1] = 0x00;

			PF_CopyDataBytes( pParm, &V_ucPowerOffTime[0], Pt_7DayAdd_FreezeTime_Len);

			if( PF_Campare_Data(&V_ucPowerOffTime[4], &V_ucNowFreezeTime_B[4], C_YYMMLen) == C_Equal)       /*年、月相等*/
			{
				if ( (PF_Campare_Data(&V_ucSettleDay[0], &V_ucNowFreezeTime_B[0], C_DDhhmmssLen) == C_LessThan)
				  && (PF_Campare_Data(&V_ucSettleDay[0], &V_ucPowerOffTime[0], C_DDhhmmssLen) != C_LessThan) )  /*掉电年月第一个结算日小于补冻结年月需量清零*/
				{
					V_ucFlag = C_NeedAddSettleFreezeFlag;
				}
			}
			else if( PF_Campare_Data(&V_ucPowerOffTime[4], &V_ucNowFreezeTime_B[4], C_YYMMLen) == C_LessThan ) /*年、月大*/
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

            if(V_ucFlag == C_NeedAddSettleFreezeFlag)     /*需量相关清零*/
			{
                V_usDataLength = C_FreezeMAXLen;
				Inf_GetFrozenData_Settle23(V_ucDataBuff, &V_usDataLength, 0x00, CD_Free_OADTab);
			}
			PF_CopyDataBytes(V_ucNowFreezeTime_B, V_ucDataBuff, CLDate_Time);
			PF_CopyDataBytes(&V_ucDataBuff[4], &V_ucSettleDay[4], C_YYMMLen);    /*赋值补第一个结算日时间年月*/

			for(V_ucTemp = 0; V_ucTemp < (V_Num + 1); V_ucTemp++)
			{
#if 0
				if(C_Meter_Type == C_L_SmartMeter)
				{
					SF_GetFrozenDataLocal_Freeze(V_ucDataBuff1);
					InF_Write_Data(C_Msg_Freeze,CChargeBal_Free_1,V_ucDataBuff1,CLChargeBal_Free_1,C_W_SafeFlag);
				}
#endif
				InF_Write_Data(C_Msg_Freeze, C_RelatedOAD_Day, &V_ucDataBuff[0], V_usDataLength, C_W_SafeFlag);	 /*写冻结数据*/

				InF_ClearVoltageQR_Data_D();

				if(V_ucTemp == 0)		/*写最早一次冻结后重新获取冻结数据，把日电压合格率数据清零*/
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
				/**************************结算日判断**************************************/
				PF_CopyDataBytes(&V_ucDataBuff[0], &V_ucSettleDay[CLDate_Time], CLDate_Time);
				for(V_usi = 0; V_usi < V_usOAD[C_698Free_OADTabCycleOffset]; V_usi++)
				{
					SF_GetNextDay(&V_ucDataBuff[3], 1);
				}
				if(V_ucSettleDay[4] != V_ucDataBuff[4])	  /*月变化*/
				{
					PF_CopyDataBytes(&V_ucDataBuff[4], &V_ucSettleDay[4], C_YYMMLen);   /*取年、月份*/
				}
				if ((PF_Campare_Data(&V_ucDataBuff[0],V_ucSettleDay,CLDate_Time) == C_GreaterThan)	    /*补过的日冻结时间与第一结算日相同*/
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
函数原型：void SF_GetNextDay(uchar8 *P_ucDay,uchar8 V_ucMode)
功能描述：天数加1、减1
输入参数：*P_ucDay 日期首地址,从低到高为日月年（698 hex格式）；V_ucMode 为0表示天数减1；为1表示天数加1  
输出参数：*P_ucDay 日期首地址
返回参数：无
调用位置：
备    注：
*******************************************************************************/
void SF_GetNextDay(uchar8 *P_ucDay,uchar8 V_ucMode)
{
	ushort16 V_usYear;
	
	if(V_ucMode == 0)
	{
		if(*P_ucDay > 1)
		{
			/*天数减1*/
			*P_ucDay -= 1;
		}
		else
		{
			if(*(P_ucDay + 1) > 1)
			{
				/*月份减1*/
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
				/*年份减1*/
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
			/*天数加1*/
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
					/*月份加1*/
					*(P_ucDay + 1) += 1;

					*P_ucDay = 1;
				}
				else
				{
					*P_ucDay = 1;
					*(P_ucDay + 1) = 1;
					/*年份加1*/
					PF_Buffer2ToUshort16(P_ucDay + 2,&V_usYear);
					V_usYear += 1;
					PF_Ushort16ToBuffer2(P_ucDay + 2,&V_usYear);
				}
			}
		}
	}
}
