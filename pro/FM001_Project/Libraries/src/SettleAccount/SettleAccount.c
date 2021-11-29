/*******************************************************************************
Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     SettleAccount.c
Version:       V1
Author:        
Date:          2014-3-12
Description:   结算
---------------------------------------------------------------------------------
History1:      第1次修改
内容1. Date:   20219016
   	   Author: fy
       Modification:
	   ---------------------------------------------------------------------------
内容2. Date:
   	   Author:
       Modification:
----------------------------------------------------------------------------------
History2:      第2次修改
内容1. Date:
   	   Author:
       Modification:
	   ---------------------------------------------------------------------------
内容2. Date:
   	   Author:
       Modification:
******************************************************************************/
#include "Public.h"
#include "SettleAccount.h"


/*****************************************************************************************
函数原型：Void InF_SettleAccountsAfterPowerUp(Void)                    
功能描述：上电结算初始化                                                 
输入参数：无                                                                     
输出参数：无                                                                    
返回参数：无                                                                     
调用位置：调度                                                             
备    注：                                                                    
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
	    
		Str_Msg_SettleAccounts.SourceAddr = C_Msg_SettleAccounts;	    	/*源消息号*/
		Str_Msg_SettleAccounts.DerictAddr = C_Msg_SettleAccounts;	    	/*目的消息号*/
	        
	    if( PF_Check_CRC(&SV_FristCheckDayChange[0], 4 ) == C_OK)       	/*修改第1结算日消息*/
	    {
			Str_Msg_SettleAccounts.Length = Pt_ParaMetersChange_Len + 1 + CLEnter_LowPower_Time;		/*Parameter的长度*/
			V_ucSettleAdd_Time[0] = SV_FristCheckDayChange[0];
			V_ucSettleAdd_Time[1] = SV_FristCheckDayChange[1];
			PF_CopyDataBytes(&V_ucEnterLowPowerTime[0], &V_ucSettleAdd_Time[2], CLEnter_LowPower_Time);
			Str_Msg_SettleAccounts.Parameter = &V_ucSettleAdd_Time[0];	   	/*参数*/
			
			InF_WriteMessege(&Str_Msg_SettleAccounts);
			
			memset(SV_FristCheckDayChange, 0xFF, 4);
	    }
				
	    if( PF_Check_CRC(&SV_StepSwitch[0], 10) == C_OK )                 	/*阶梯切换消息*/
	    {
	    	Str_Msg_SettleAccounts.Length = Pt_StepSwitchFlag_Len + 1;    	/*Parameter的长度*/
			Str_Msg_SettleAccounts.Parameter = &SV_StepSwitch[0];         	/*参数*/
				
			InF_WriteMessege(&Str_Msg_SettleAccounts);
			
			memset(SV_StepSwitch, 0xFF, 10 );
	    }
		
	    /*************上电发掉电不结算消息，是否需要不结算，在消息处理函数中判断**************/	    	    
	    Str_Msg_SettleAccounts.Length = Pt_SettleAdd_Time_Len + 1;		  	/*Parameter的长度*/
		V_ucSettleAdd_Time[0] = Pt_SettleAdd_Time;
		PF_CopyDataBytes(&V_ucEnterLowPowerTime[0], &V_ucSettleAdd_Time[1], CLEnter_LowPower_Time);
		Str_Msg_SettleAccounts.Parameter = &V_ucSettleAdd_Time[0];	      	/*参数*/
			
		InF_WriteMessege(&Str_Msg_SettleAccounts);
		
	}
	return;
    
}

/****************************************************************************************************
函数原型：void Msg_Freeze(Str_Msg_Parameter *P_Msg)	                 
功能描述：结算消息处理                                                
输入参数：P_Msg,消息结构体                                                                  
输出参数：无                                                                 
返回参数：无                                                                  
调用位置：调度                                                          
备    注：无                                                                
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
				PF_CopyDataBytes(pParm, &SV_FristCheckDayChange[0], 2);  	/*[0]:消息号；[1]:消息类型*/
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
		&& ( *(pParm+1) == C_SystemMinChange) ) /*调度1min*/
	{
        V_usLen = CLDate_Time;
        V_usDataEncode = C_pNULL_NoCode;
        InF_Read_Data(CDate_Time, &V_ucCurrentTime[0], &V_usLen, &V_usDataEncode);          /*读取当前时间 */
		
		if( PF_Campare_Data(&V_ucCurrentTime[0], (pParm + 2), CLDate_Time) == C_LessThan)   /*不记录改点数据*/
		{
			return;
		}
		if( *(pParm + 3) == 0)      /*小时变化才需要判断*/
		{
			SF_DealwithMin_SettleAccounts(pParm + 4);		

		}
		
	}
	else if ( ( ( *pParm == Pt_ParaMetersChange ) && ( *(pParm + 1) == C_ReSettle_Day1 ) )
			&& ( ( P_Msg->Length == Pt_ParaMetersChange_Len + 1 ) || ( P_Msg->Length == Pt_ParaMetersChange_Len + 1 + CLEnter_LowPower_Time ) ) )         /*修改第1结算日消息*/
	{						
        V_usLen = CLDate_Time;
        V_usDataEncode = C_pNULL_NoCode;
        InF_Read_Data(CDate_Time, &V_ucCurrentTime[0], &V_usLen, &V_usDataEncode);          /*读取当前时间*/
		
		if(P_Msg->Length == Pt_ParaMetersChange_Len + 1 + CLEnter_LowPower_Time)                        		/*长度大于2，认为带有时间*/
		{
			PF_CopyDataBytes(pParm + 2, &V_ucCurrentTime[0], CLEnter_LowPower_Time);  		/*用消息参数中的时间覆盖之前读取时间*/
		}

		V_usDataLength = C_FreezeMAXLen;
		if(Inf_GetRecordData(V_ucDataBuff1, &V_usDataLength, C_FrzOAD, C_Settlement_Type) == C_OK)
		{
			PF_CopyDataBytes(&V_ucCurrentTime[2], (V_ucDataBuff1 + 2), 5);        /*结算时间 */
			InF_Write_Data(C_Msg_Freeze,C_RelatedOAD_Settle, &V_ucDataBuff1[0], V_usDataLength,C_W_SafeFlag);
		}
		
		InF_Demand_Clear(C_Msg_SettleAccounts, C_W_SafeFlag);	              /*过第1结算日需量转存后清零*/
		SF_MsgSend_SettleAccounts_ReSettle_Day1();                            /*给需量模块发过第1结算日消息*/
#if 0
		InF_ReadEnergy_Settlement( );       /*取当前结算周期内组合有功总累计用电量写数据层 */
		InF_Write_Data(C_Msg_SettleAccounts,CSC_Com_Ac_Tol_En_1, &V_ucDataBuff1[4], (CLSC_Com_Ac_Tol_En_1 + 1), C_W_SafeFlag);
		
		SF_GetRevEnergy_Pul_SettleAccounts(&V_ucDataBuff1[4]);                /*取当前结算周期正、反向有功电量写数据层*/
		InF_Write_Data(C_Msg_SettleAccounts,CSC_Rev_Ac_Tol_En_Pul_1, &V_ucDataBuff1[4], CLSC_Rev_Ac_Tol_En_Pul_1, C_W_SafeFlag);
		SF_GetPosEnergy_Pul_SettleAccounts(&V_ucDataBuff1[4]);
		InF_Write_Data(C_Msg_SettleAccounts,CSC_Pos_Ac_Tol_En_Pul_1, &V_ucDataBuff1[4], CLSC_Pos_Ac_Tol_En_Pul_1, C_W_SafeFlag);
				
		InF_ReadEnergy_Settlement( );      /*取当前月度组合有功总累计用电量写数据层*/
		InF_Write_Data(C_Msg_SettleAccounts,CM_Com_Ac_Tol_En_1, &V_ucDataBuff1[4], CLM_Com_Ac_Tol_En_1 + 1, C_W_SafeFlag);
#endif
		SF_GetRevEnergy_Pul_SettleAccounts(&V_ucDataBuff1[5]);      			/*取当前月度累计正、反向有功电量写数据层*/
		InF_Write_Data(C_Msg_SettleAccounts,CM_Rev_Ac_Tol_En_Pul_1, &V_ucDataBuff1[5], CLM_Rev_Ac_Tol_En_Pul_1, C_W_SafeFlag);
		SF_GetPosEnergy_Pul_SettleAccounts(&V_ucDataBuff1[5]);
		InF_Write_Data(C_Msg_SettleAccounts,CM_Pos_Ac_Tol_En_Pul_1, &V_ucDataBuff1[5], CLM_Pos_Ac_Tol_En_Pul_1, C_W_SafeFlag);

	}
#if 0		/*卡模块不再发消息*/
	else if ( ( *pParm == Pt_YearCheckDayChange ) 
			&& (( P_Msg->Length == Pt_YearCheckDayChange_Len + 1) || ( P_Msg->Length == Pt_YearCheckDayChange_Len + 1 + CLEnter_LowPower_Time)) )  /*卡处理修改当前套年结算日消息*/
	{
		if( C_Meter_Type == C_L_SmartMeter )        /*本地表进行年结算日 */
		{
			V_Data_Id_OAD[0] = CProgLad_Note_1;
			V_Data_Id_OAD[1] = 0x401A2200;
			V_Data_Id_OAD[2] = 0xFFFFFFFF;
			V_Data_1 = 0;
			V_Data_Len = CLCurrent_Ladder_Table;
			InF_ReadEventData(V_Data_Id_OAD, &V_Data_1, V_ucDataBuff1, &V_Data_1, &V_Data_Len, 0x68);      /*读取上一次结算时间 */
            
            V_usLen = CLCurrent_Ladder_Table;
            V_usDataEncode = C_pNULL_NoCode;
			InF_Read_Data(CCurrent_Ladder_Table, &V_ucDataBuff1[150], &V_usLen, &V_usDataEncode);           /*读取年结算日 */	
		
			if( PF_Campare_Data(&V_ucDataBuff1[C_StepSettlementStartAddr], &V_ucDataBuff1[150+C_StepSettlementStartAddr], C_StepSettlementTotalLen) == C_Equal )
			{
				return;	
			}
			
            V_usLen = CLDate_Time;
            V_usDataEncode = C_pNULL_NoCode;
			InF_Read_Data(CDate_Time, &V_ucCurrentTime[0], &V_usLen, &V_usDataEncode);                      /*读取当前时间 */
			
			if( P_Msg->Length == Pt_YearCheckDayChange_Len + 1 + CLEnter_LowPower_Time )                        				/*长度5，认为带有时间*/
			{
				PF_CopyDataBytes((pParm + 1), &V_ucCurrentTime[0], CLEnter_LowPower_Time);  				/*用消息参数中的时间覆盖之前读取时间*/		
			}
			
			SF_FreezeYSettle(&V_ucCurrentTime[1], 6);
			
            InF_ReadEnergy_Settlement( );   /*取当前年结算周期内组合有功总累计用电量写数据层*/
		}	
	}
#endif
	else if ( ( *pParm == Pt_StepSwitchFlag ) 
			&& ( P_Msg->Length == Pt_StepSwitchFlag_Len + 1))   	/*费率判断消息*/
	{
		if(C_Meter_Type == C_L_SmartMeter)   						/*本地表进行年结算日 */
		{

			if( *(pParm + 1) == C_Step_SetttleChange)        		/*阶梯结算日 */	
			{
				SF_FreezeYSettle((pParm + 2), 6);
				InF_ReadEnergy_Settlement( ); 						/*取阶梯结算用电量写数据层*/					
			}  /*else 不补阶梯结算冻结*/

#if 0
			if( *(pParm + 1) == C_Step_YToY) /*年阶梯切换为年阶梯 */	
			{
			
				PF_CopyDataBytes((pParm + 3), &V_ucDataBuff1[0], 4); /*将消息参数中的时间放入年结算电能前面 */
				SF_FreezeYSettle((pParm + 2), 6);
				InF_ReadEnergy_Settlement( ); /*取当前年结算周期内组合有功总累计用电量写数据层*/					
			}
			else if(*(pParm + 1) == C_Step_YToM)  /*年阶梯切换为月阶梯*/
			{
				PF_CopyDataBytes((pParm + 3), &V_ucDataBuff1[0], 4);    /*将消息参数中的时间放入年结算电能前面*/
				SF_FreezeYSettle((pParm + 2), 6);
				V_usDataLength = C_FreezeMAXLen;
				if( Inf_GetRecordData(V_ucDataBuff1, &V_usDataLength, C_FrzOAD, C_Settlement_Type) == C_OK)
				{
					PF_CopyDataBytes((pParm + 3), (V_ucDataBuff1+2), 4); /*结算时间 */
					InF_Write_Data(C_Msg_Freeze, C_RelatedOAD_Settle, &V_ucDataBuff1[0], V_usDataLength, C_W_SafeFlag);
				}
				InF_ReadEnergy_Settlement( );  /*取当前年结算周期内组合有功总累计用电量写数据层*/

				InF_Demand_Clear(C_Msg_SettleAccounts, C_W_SafeFlag);	/*过第1结算日需量转存后清零*/
				SF_MsgSend_SettleAccounts();                            /*给需量模块发过第1结算日消息*/
				
				InF_ReadEnergy_Settlement( );   /*取当前结算周期内组合有功总累计用电量写数据层 */
				InF_Write_Data(C_Msg_SettleAccounts, CSC_Com_Ac_Tol_En_1, &V_ucDataBuff1[4], CLSC_Com_Ac_Tol_En_0 + 1, C_W_SafeFlag);
				
				SF_GetRevEnergy_Pul_SettleAccounts(&V_ucDataBuff1[4]);    /*取当前结算周期正、反向有功电量写数据层*/
				InF_Write_Data(C_Msg_SettleAccounts, CSC_Rev_Ac_Tol_En_Pul_1, &V_ucDataBuff1[4], CLSC_Rev_Ac_Tol_En_Pul_1, C_W_SafeFlag);
				SF_GetPosEnergy_Pul_SettleAccounts(&V_ucDataBuff1[4]);
				InF_Write_Data(C_Msg_SettleAccounts, CSC_Pos_Ac_Tol_En_Pul_1, &V_ucDataBuff1[4], CLSC_Pos_Ac_Tol_En_Pul_1, C_W_SafeFlag);
		 
				
				
				InF_ReadEnergy_Settlement( );    /*取当前月度组合有功总累计用电量写数据层*/
				InF_Write_Data(C_Msg_SettleAccounts, CM_Com_Ac_Tol_En_1, &V_ucDataBuff1[4], CLM_Com_Ac_Tol_En_0 + 1, C_W_SafeFlag);
				
				SF_GetRevEnergy_Pul_SettleAccounts(&V_ucDataBuff1[4]);   /*取当前月度累计正、反向有功电量写数据层 *///
				InF_Write_Data(C_Msg_SettleAccounts,CM_Rev_Ac_Tol_En_Pul_1, &V_ucDataBuff1[4], CLM_Rev_Ac_Tol_En_Pul_1, C_W_SafeFlag);
				SF_GetPosEnergy_Pul_SettleAccounts(&V_ucDataBuff1[4]);
				InF_Write_Data(C_Msg_SettleAccounts, CM_Pos_Ac_Tol_En_Pul_1, &V_ucDataBuff1[4], CLM_Pos_Ac_Tol_En_Pul_1, C_W_SafeFlag);
			}
			else if( *(pParm + 1) == C_Step_MToY )      /*月阶梯切换为年阶梯*/
			{
				V_usDataLength = C_FreezeMAXLen;
				if(Inf_GetRecordData(V_ucDataBuff1, &V_usDataLength, C_FrzOAD, C_Settlement_Type) == C_OK)
				{
					PF_CopyDataBytes(pParm+3, (V_ucDataBuff1 + 2), 4);       /*结算时间 */
					InF_Write_Data(C_Msg_Freeze,C_RelatedOAD_Settle, &V_ucDataBuff1[0], V_usDataLength, C_W_SafeFlag);
				}

				InF_Demand_Clear(C_Msg_SettleAccounts,C_W_SafeFlag);	/*过第1结算日需量转存后清零*/
				SF_MsgSend_SettleAccounts();     /*给需量模块发过第1结算日消息*/
				
				InF_ReadEnergy_Settlement( );    /*取当前结算周期内组合有功总累计用电量写数据层*/
				InF_Write_Data(C_Msg_SettleAccounts,CSC_Com_Ac_Tol_En_1,&V_ucDataBuff1[4],CLSC_Com_Ac_Tol_En_0+1,C_W_SafeFlag);
				
				SF_GetRevEnergy_Pul_SettleAccounts(&V_ucDataBuff1[4]);      /*取当前结算周期正、反向有功电量写数据层 */
				InF_Write_Data(C_Msg_SettleAccounts, CSC_Rev_Ac_Tol_En_Pul_1, &V_ucDataBuff1[4], CLSC_Rev_Ac_Tol_En_Pul_1, C_W_SafeFlag);
				SF_GetPosEnergy_Pul_SettleAccounts(&V_ucDataBuff1[4]);
				InF_Write_Data(C_Msg_SettleAccounts, CSC_Pos_Ac_Tol_En_Pul_1, &V_ucDataBuff1[4], CLSC_Pos_Ac_Tol_En_Pul_1, C_W_SafeFlag);
		
				InF_ReadEnergy_Settlement( );   /*取当前月度组合有功总累计用电量写数据层*/
				InF_Write_Data(C_Msg_SettleAccounts, CM_Com_Ac_Tol_En_1, &V_ucDataBuff1[4], CLM_Com_Ac_Tol_En_0 + 1, C_W_SafeFlag);
				
				SF_GetRevEnergy_Pul_SettleAccounts(&V_ucDataBuff1[4]);       /*取当前月度累计正、反向有功电量写数据层 */
				InF_Write_Data(C_Msg_SettleAccounts, CM_Rev_Ac_Tol_En_Pul_1, &V_ucDataBuff1[4], CLM_Rev_Ac_Tol_En_Pul_1, C_W_SafeFlag);
				SF_GetPosEnergy_Pul_SettleAccounts(&V_ucDataBuff1[4]);
				InF_Write_Data(C_Msg_SettleAccounts, CM_Pos_Ac_Tol_En_Pul_1, &V_ucDataBuff1[4], CLM_Pos_Ac_Tol_En_Pul_1, C_W_SafeFlag);
			}
#endif
		}	
	}
	else if ( ( *pParm == Pt_SettleAdd_Time)
			&& ( P_Msg->Length == Pt_SettleAdd_Time_Len + 1 ) )    /*补结算日消息*/
	{
		if( P_Msg->SourceAddr == C_Msg_Communication)
		{
			return;	
		}
		
		V_Data_Id_OAD[0] = 0x50050201;
		V_Data_Id_OAD[1] = CFreeTime;
		V_Data_Id_OAD[2] = 0xFFFFFFFF;
		V_Data_Len = 16;
		
		V_ucFlag = Inf_Read_FrozenData_OneOAD(V_Data_Id_OAD, V_ucSettle_Time_1, &V_Data_Len);       /*读取上一次结算时间*/
		
		if( ( *(pParm + 1) == 0x00 ) 
		 && ( *(pParm + 1 + 1) == 0x00 ) 
		 && ( ( ( V_ucFlag == C_OK) && (PF_Campare_Data(&V_ucSettle_Time_1[2], (pParm + 1 + 2), 5) != C_Equal ) )   
			|| ( V_ucFlag == C_NoData ) ) )                       /*00分00秒掉电时判断掉电时间是否已经结算,1)时间不等2）无数据*/
		{
			SF_DealwithMin_SettleAccounts(pParm + 1 + 2);	
		}
		
        V_usLen = CLDate_Time;
        V_usDataEncode = C_pNULL_NoCode;
        InF_Read_Data(CDate_Time, &V_ucCurrentTime[0], &V_usLen, &V_usDataEncode);          /*读取当前时间 */
		
		SF_SettleAdd_SettleAccounts((pParm + 1), &V_ucCurrentTime[0]);	
	}
	return;
}

/****************************************************************************************************
函数原型：void SF_DealwithMin_SettleAccounts(uchar8 Settle_Time[4])	                 
功能描述：调度1min触发处理                                                
输入参数：Settle_Time：时间地址（年月日时）                                                                  
输出参数：无                                                                 
返回参数：无                                                                  
调用位置：调度                                                          
备    注：无                                                                
***************************************************************************************************/
void SF_DealwithMin_SettleAccounts(uchar8 Settle_Time[4])
{
	uchar8 V_ucDataBuff[C_FreezeMAXLen];
	uchar8 V_ucDataBuff1[582];
	ushort16 V_usDataLength = C_FreezeMAXLen, V_usLen, V_usDataEncode;
	uchar8 V_SettleTime[CLDate_Time];
	
	V_usLen = CLSettle_Day1;	
	
	PF_CopyDataBytes(&Settle_Time[0], V_ucDataBuff1, 5);                          /*结算时间,年月日时 */
    
    V_usDataEncode = C_pNULL_NoCode;	
    if( InF_Read_Data(CSettle_Day1, V_SettleTime, &V_usLen, &V_usDataEncode) == C_OK )          /*读取第1结算日 */
	{
		PF_OneDataReversed(V_SettleTime, V_SettleTime, (uchar8)V_usLen);
		if( PF_Campare_Data(&V_SettleTime[0], &Settle_Time[0], 2) == C_Equal )    /*是否到第1结算日 */
		{
            V_usDataLength = C_FreezeMAXLen;            
			if( Inf_GetRecordData(V_ucDataBuff, &V_usDataLength, C_FrzOAD, C_Settlement_Type) == C_OK )
			{
				if( PF_Campare_Data(&V_ucDataBuff[2], Settle_Time, 5) == C_GreaterThan)  /*不记录改点数据*/
				{
					PF_CopyDataBytes(Settle_Time, &V_ucDataBuff[2], 5);
				}
                
				V_ucDataBuff[0]=0;  /*秒为0*/
				V_ucDataBuff[1]=0;  /*分为0*/
				InF_Write_Data(C_Msg_Freeze, C_RelatedOAD_Settle, &V_ucDataBuff[0], V_usDataLength, C_W_SafeFlag);
			}
            
			InF_Demand_Clear(C_Msg_SettleAccounts, C_W_SafeFlag);	/*过第1结算日需量转存后清零*/
			SF_MsgSend_SettleAccounts();                            /*给需量模块发过第1结算日消息*/
#if 0
			InF_ReadEnergy_Settlement( );      /*取当前结算周期内组合有功总累计用电量写数据层 */
			InF_Write_Data(C_Msg_SettleAccounts, CSC_Com_Ac_Tol_En_1, &V_ucDataBuff1[4], (CLSC_Com_Ac_Tol_En_0 + 1), C_W_SafeFlag);
			
			SF_GetRevEnergy_Pul_SettleAccounts(&V_ucDataBuff1[4]);  /*取当前结算周期正、反向有功电量写数据层 */
			InF_Write_Data(C_Msg_SettleAccounts,CSC_Rev_Ac_Tol_En_Pul_1, &V_ucDataBuff1[4], CLSC_Rev_Ac_Tol_En_Pul_1, C_W_SafeFlag);
			SF_GetPosEnergy_Pul_SettleAccounts(&V_ucDataBuff1[4]);
			InF_Write_Data(C_Msg_SettleAccounts,CSC_Pos_Ac_Tol_En_Pul_1, &V_ucDataBuff1[4], CLSC_Pos_Ac_Tol_En_Pul_1, C_W_SafeFlag);
		
			InF_ReadEnergy_Settlement( );         /*取当前月度组合有功总累计用电量写数据层 */
			InF_Write_Data(C_Msg_SettleAccounts,CM_Com_Ac_Tol_En_1,&V_ucDataBuff1[4], (CLM_Com_Ac_Tol_En_0 + 1), C_W_SafeFlag);
#endif
			SF_GetRevEnergy_Pul_SettleAccounts(&V_ucDataBuff1[5]);   /*取当前月度累计正、反向有功电量写数据层 *///
			InF_Write_Data(C_Msg_SettleAccounts,CM_Rev_Ac_Tol_En_Pul_1, &V_ucDataBuff1[5], CLM_Rev_Ac_Tol_En_Pul_1, C_W_SafeFlag);
			SF_GetPosEnergy_Pul_SettleAccounts(&V_ucDataBuff1[5]);
			InF_Write_Data(C_Msg_SettleAccounts,CM_Pos_Ac_Tol_En_Pul_1, &V_ucDataBuff1[5], CLM_Pos_Ac_Tol_En_Pul_1, C_W_SafeFlag);
		}	
	}
    if( InF_Read_Data(CSettle_Day2, &V_SettleTime[2], &V_usLen, &V_usDataEncode) == C_OK)       /*读取第2结算日 */
	{
		PF_OneDataReversed(&V_SettleTime[2], &V_SettleTime[2], (uchar8)V_usLen);
		if ( ( PF_Campare_Data(&V_SettleTime[2], &V_SettleTime[0], 2) != C_Equal )
          && ( PF_Campare_Data(&V_SettleTime[2], &Settle_Time[0], 2) == C_Equal ) )
		{
#if 0
			InF_ReadEnergy_Settlement( );    /*取当前结算周期内组合有功总累计用电量写数据层 */
			InF_Write_Data(C_Msg_SettleAccounts,CSC_Com_Ac_Tol_En_1,&V_ucDataBuff1[4],CLSC_Com_Ac_Tol_En_0+1,C_W_SafeFlag);
#endif
            V_usDataLength = C_FreezeMAXLen;
            if(Inf_GetFrozenData_Settle23(V_ucDataBuff,&V_usDataLength,0xFF,CSett_Free_OADTab) == C_OK)
			{
				if(PF_Campare_Data(&V_ucDataBuff[2], Settle_Time, 5) == C_GreaterThan)          /*不记录改点数据*/
				{
					PF_CopyDataBytes(Settle_Time, &V_ucDataBuff[2], 5);
				}
				V_ucDataBuff[0]=0;  /*秒为0*/
				V_ucDataBuff[1]=0;  /*分为0*/
				InF_Write_Data(C_Msg_Freeze,C_RelatedOAD_Settle, &V_ucDataBuff[0], V_usDataLength, C_W_SafeFlag);
			}           
		}
	}
    if( InF_Read_Data(CSettle_Day3, &V_SettleTime[4], &V_usLen, &V_usDataEncode) == C_OK)       /*读取第3结算日 */
	{
		PF_OneDataReversed(&V_SettleTime[4], &V_SettleTime[4], (uchar8)V_usLen);
		if ( ( PF_Campare_Data(&V_SettleTime[4], &V_SettleTime[0], 2) != C_Equal )
          && ( PF_Campare_Data(&V_SettleTime[4], &V_SettleTime[2], 2) != C_Equal )
          && ( PF_Campare_Data(&V_SettleTime[4], &Settle_Time[0], 2) == C_Equal ) )
		{
#if 0
			InF_ReadEnergy_Settlement( );        /*取当前结算周期内组合有功总累计用电量写数据层 */
			InF_Write_Data(C_Msg_SettleAccounts, CSC_Com_Ac_Tol_En_1, &V_ucDataBuff1[4], (CLSC_Com_Ac_Tol_En_0 + 1), C_W_SafeFlag);
#endif
            V_usDataLength = C_FreezeMAXLen;
            if(Inf_GetFrozenData_Settle23(V_ucDataBuff, &V_usDataLength, 0xFF, CSett_Free_OADTab) == C_OK)
			{
				if(PF_Campare_Data(&V_ucDataBuff[2], Settle_Time, 5) == C_GreaterThan)  /*不记录改点数据*/
				{
					PF_CopyDataBytes(Settle_Time, &V_ucDataBuff[2], 5);
				}
				V_ucDataBuff[0]=0;  /*秒为0*/
				V_ucDataBuff[1]=0;  /*分为0*/
				InF_Write_Data(C_Msg_Freeze, C_RelatedOAD_Settle, &V_ucDataBuff[0], V_usDataLength, C_W_SafeFlag);
			}			
		}
	}
	
	if( C_Meter_Type == C_L_SmartMeter )    /*本地表进行年结算日判断 */
	{
		SF_DealwithYear_SettleAccounts(V_ucDataBuff1);	
	}
	return;	
}
/*****************************************************************************************
函数原型：void SF_SettleAdd_SettleAccounts (uchar8 *StartTime, uchar8 *EndTime)                           	                		   	
功能描述：停电跨结算日或者特殊地方要求修改时间跨过结算日的需要补结算                                                     				
输入参数： *StartTime 补结算开始时间；                                                                  
	      *EndTime 补结算结束时间；                                                                       
输出参数： 无                                                                       										
返回参数： 无                                                                                 
调用位置：                                                                             
备    注:                                                                           
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
	if( InF_Read_Data(CSettle_Day1, &V_ucSettlementTime[0], &V_usLen, &V_usDataEncode) == C_OK )            /*读取第1结算日 */
	{
		V_ucNum++;	
		PF_OneDataReversed(V_ucSettlementTime, V_ucSettlementTime, 2);
		V_ucSettlementTime[2] = 1;
		
		if( InF_Read_Data(CSettle_Day2, &V_ucSettlementTime[3], &V_usLen, &V_usDataEncode) == C_OK )        /*读取第2结算日 */
		{
			
			PF_OneDataReversed(&V_ucSettlementTime[3], &V_ucSettlementTime[3], 2);
			V_ucSettlementTime[5] = 2;
			V_ucNum++;
			
            if( InF_Read_Data(CSettle_Day3, &V_ucSettlementTime[6], &V_usLen, &V_usDataEncode) == C_OK )    /*读取第3结算日 */
			{
				PF_OneDataReversed(&V_ucSettlementTime[6], &V_ucSettlementTime[6], 2);
				V_ucSettlementTime[8] = 3;
				V_ucNum++;	
			}	
		}
		
		V_times = SF_JudgeAndOrder_SettleAccounts(&V_ucSettlementTime[0], 3, V_ucNum);		
	}
			
	if( ( V_times > 0 ) && ( V_times <= 3 ) )	/*结算日个数*/
	{
			
        if( PF_TimeSub_Hour_698(V_ucEndTime, Start_Time, &SubHours) != C_GreaterThan )    /*当前时间小于等于补结算开始时间不补结算*/
        {
            return;	
        }
        
        if( PF_Campare_Data(&V_ucEndTime[4], &Start_Time[4], 3) == C_Equal )          /*未跨月只查找当前月*/
        {
            for( i = 0; i < V_times; i++ )	/*查找需要补的结算日 */
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
            
            for(i = 0; i < V_times; i++)	/* 从1日0点开始，最多三个 */
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
                for( i = 0; i < V_times; i++ )	/* 从停电开始到月末24点的冻结数，最多三个 */
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
			V_ucFlag = Inf_Read_FrozenData_OneOAD(V_Data_Id_OAD, V_ucLastSettlementTime, &V_Data_Len);   /*读取上一次结算时间，单个OAD读冻结时间不支持，返回一个BB，冻结时间采用返回的固定数据中的冻结时间 */
			
            if ( ( ( V_ucFlag == C_OK ) && ( PF_Campare_Data(&V_ucLastSettlementTime[2], &V_ucSettleTime[14][0], CLSettle_Time_1) != C_Equal ) )      /*当前要补的结算时间与上一相同则不补*/
              || ( V_ucFlag == C_NoData) )    /*第1次冻结就是补冻结*/
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
						InF_ReadEnergy_Settlement( );              /*取当前结算周期内组合有功总累计用电量写数据层*/
						InF_Write_Data(C_Msg_SettleAccounts,CSC_Com_Ac_Tol_En_1, &V_ucDataBuff1[0], (CLSC_Com_Ac_Tol_En_0 + 1), C_W_SafeFlag);
						
						SF_GetRevEnergy_Pul_SettleAccounts(&V_ucDataBuff1[0]);          /*取当前结算周期正、反向有功电量写数据层*/
						InF_Write_Data(C_Msg_SettleAccounts,CSC_Rev_Ac_Tol_En_Pul_1, &V_ucDataBuff1[0], CLSC_Rev_Ac_Tol_En_Pul_1, C_W_SafeFlag);
						
                        SF_GetPosEnergy_Pul_SettleAccounts(&V_ucDataBuff1[0]);
						InF_Write_Data(C_Msg_SettleAccounts,CSC_Pos_Ac_Tol_En_Pul_1, &V_ucDataBuff1[0], CLSC_Pos_Ac_Tol_En_Pul_1, C_W_SafeFlag);
#endif
						if(V_ucSettleDaySequence[15 - V_ucValidSettleDay + i] == 1)
						{
							InF_Write_Data(C_Msg_Freeze, C_RelatedOAD_Settle, &V_ucDemandData1[0], V_usDataLength, C_W_SafeFlag);   /*需量数据写数据层 */
							
                            if(V_ucDemandClearFlag != C_DemandClearFlag)
							{
								V_ucDemandClearFlag = C_DemandClearFlag;
								InF_Demand_Clear(C_Msg_SettleAccounts, C_W_SafeFlag);	/*过第1结算日需量转存后清零*/					
								
                                V_usDataLength = C_FreezeMAXLen;
                                Inf_GetFrozenData_Settle23(V_ucDemandData1, &V_usDataLength, 0x00, CSett_Free_OADTab);
								
                                PF_Buffer4ToUlong32(&V_ucDemandData1[7], &V_SettleAccountNum, 4);
								V_SettleAccountNum--;
								PF_Ulong32ToBuffer4(&V_ucDemandData1[7], &V_SettleAccountNum, 4);
							}
#if 0
							InF_ReadEnergy_Settlement( );     /*取当前月度组合有功总累计用电量写数据层 */
							InF_Write_Data(C_Msg_SettleAccounts, CM_Com_Ac_Tol_En_1, &V_ucDataBuff1[0], (CLM_Com_Ac_Tol_En_0 + 1), C_W_SafeFlag);
#endif
							SF_GetRevEnergy_Pul_SettleAccounts(&V_ucDataBuff1[0]);              /*取当前月度累计正、反向有功电量写数据层 */
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
	
	if(C_Meter_Type == C_L_SmartMeter)    		/*本地表进行年结算日判断 */
	{
		SF_DealwithYearAdd_SettleAccounts(StartTime, EndTime);	
	}
	return;	
}

/*******************************************************************************
函数原型：void SF_DealwithYear_SettleAccounts(uchar8 *pV_ucSettle_Time)
功能描述：判断是否到阶梯结算日，到阶梯结算日则转存阶梯结算用电量
输入参数：pV_ucSettle_Time:阶梯结算日缓存（月日时）
输出参数：无
返回参数：无
调用位置：
备    注：
*******************************************************************************/
void SF_DealwithYear_SettleAccounts(uchar8 *pV_ucSettle_Time)
{
	uchar8 V_ucSettlementTime[C_StepSettlementTotalLen];
	uchar8 V_ucDataBuff1[CLCurrent_Ladder_Table];
	uchar8 V_uci;
    ushort16 V_usLen, V_usDataEncode;
      
    V_usLen = CLCurrent_Ladder_Table;
    V_usDataEncode = C_pNULL_NoCode;
	if( InF_Read_Data(CCurrent_Ladder_Table, &V_ucDataBuff1[0], &V_usLen, &V_usDataEncode) == C_OK )  /* 读取阶梯结算日 */
	{
		PF_CopyDataBytes(&V_ucDataBuff1[C_StepSettlementStartAddr], V_ucSettlementTime, C_StepSettlementTotalLen);
		for(V_uci = 0; V_uci < C_StepSettlementNum; V_uci++)
		{
			PF_OneDataReversed(&V_ucSettlementTime[V_uci * C_StepSettlementLen], &V_ucSettlementTime[V_uci * C_StepSettlementLen], C_StepSettlementLen);
		}
		
		PF_CopyDataBytes(&pV_ucSettle_Time[0], &V_ucDataBuff1[0], C_StepSettlementLen);
		
		if( ( V_ucSettlementTime[2] == 0xFF ) || ( V_ucSettlementTime[2] == 0x63 ) )				  /* 年结算日月无效 */
		{
			if( PF_Campare_Data( &V_ucSettlementTime[0], &pV_ucSettle_Time[0], 2 ) == C_Equal )		  /* 是否到第1年结算日(月无效) */
			{
				SF_FreezeYSettle(&pV_ucSettle_Time[0], 5);
				InF_ReadEnergy_Settlement( );
			}
			return;
		}
		
		if( PF_Campare_Data(&V_ucSettlementTime[0], &pV_ucSettle_Time[0], C_StepSettlementLen) == C_Equal )				  /* 是否到第1年结算日 */	
		{
			SF_FreezeYSettle(&pV_ucSettle_Time[0], 5);
			InF_ReadEnergy_Settlement( );		/* 取当前年结算周期内组合有功总累计用电量写数据层 */						
		}
		
		if( ( PF_Campare_Data(&V_ucSettlementTime[C_StepSettlementLen], &pV_ucSettle_Time[0], C_StepSettlementLen ) == C_Equal )
		 && ( PF_Campare_Data(&V_ucSettlementTime[C_StepSettlementLen], &V_ucSettlementTime[0], C_StepSettlementLen ) != C_Equal ) )		  /* 是否到第2年结算日 */	
		{
			SF_FreezeYSettle(&pV_ucSettle_Time[0], 5);
			InF_ReadEnergy_Settlement( );		/* 取当前年结算周期内组合有功总累计用电量写数据层 */
				
		}
		
		if( ( PF_Campare_Data(&V_ucSettlementTime[6], &pV_ucSettle_Time[0], C_StepSettlementLen) == C_Equal )
		 && ( PF_Campare_Data(&V_ucSettlementTime[6], &V_ucSettlementTime[0], C_StepSettlementLen) != C_Equal )
		 && ( PF_Campare_Data(&V_ucSettlementTime[6], &V_ucSettlementTime[3], C_StepSettlementLen) != C_Equal ) )		  /* 是否到第3年结算日 */
		{
			SF_FreezeYSettle(&pV_ucSettle_Time[0], 5);
			InF_ReadEnergy_Settlement( );		/* 取当前年结算周期内组合有功总累计用电量写数据层 */
				
		}
		
		if( ( PF_Campare_Data(&V_ucSettlementTime[9], &pV_ucSettle_Time[0], C_StepSettlementLen) == C_Equal )
		 && ( PF_Campare_Data(&V_ucSettlementTime[9], &V_ucSettlementTime[0], C_StepSettlementLen) != C_Equal )
		 && ( PF_Campare_Data(&V_ucSettlementTime[9], &V_ucSettlementTime[3], C_StepSettlementLen) != C_Equal )
		 && ( PF_Campare_Data(&V_ucSettlementTime[9], &V_ucSettlementTime[6], C_StepSettlementLen) != C_Equal ) )		  /* 是否到第4年结算日 */
		{
			SF_FreezeYSettle(&pV_ucSettle_Time[0], 5);
			InF_ReadEnergy_Settlement( );		/* 取当前年结算周期内组合有功总累计用电量写数据层 */
				
		}				
	}
}
///******************************************************************************************///
///*Function：	void SF_DealwithYearAdd_SettleAccounts (uchar8 *StartTime,uchar8 *EndTime)                            	                		   	*///
///*Description：判断是否到年结算日，到年结算日则转存年度用电量                                                     				*///
///*Input：    *StartTime 补结算开始时间；                                                                  *///
///*			    *EndTime 补结算结束时间；                                                                  *///
///*Calls：                                                                                 *///
///*Called By：                                                                             *///
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
	if( InF_Read_Data(CCurrent_Ladder_Table, &V_ucDataBuff1[0], &V_usLen, &V_usDataEncode) == C_OK )    /* 读取年结算日 */
	{
		PF_CopyDataBytes(&V_ucDataBuff1[C_StepSettlementStartAddr], V_ucSettlementTime, C_StepSettlementTotalLen);
		
		for( V_uci= 0; V_uci < C_StepSettlementNum; V_uci++)
		{
			PF_OneDataReversed(&V_ucSettlementTime[V_uci * C_StepSettlementLen], &V_ucSettlementTime[V_uci * C_StepSettlementLen], C_StepSettlementLen);
		}
		
		if( ( V_ucSettlementTime[C_StepSettlementDay_MM] == 0xFF ) || ( V_ucSettlementTime[C_StepSettlementDay_MM] == 0x63 ) )					/*年结算日月无效 */
		{
			if( PF_TimeSub_Hour_698(V_ucEndTime, Start_Time, &SubHours) != C_GreaterThan )					/* 当前时间小于等于补结算开始时间不补结算 */
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
			if( PF_TimeSub_Hour_698(V_ucEndTime, Start_Time, &SubHours) != C_GreaterThan )			/* 当前时间小于等于补结算开始时间不补结算 */
			{
				return;	
			}
			
			
			PF_Buffer2ToUshort16(&V_ucEndTime[5], &V_usYearEnd);
			PF_Buffer2ToUshort16(&Start_Time[5],  &V_usYearStart);
			
			if( ( V_usYearEnd == V_usYearStart ) && ( V_Times <= 4 ) )
			{
				for( i = 0; i < V_Times; i++ )													/*查找需要补的结算日 */
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
			
				for( i = 0; i < V_Times; i++ )					/* 从1日0点开始 */
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
						PF_CopyDataBytes(&V_ucSettleTime[5 - V_ucValidSettleDay + i][0],V_ucDataBuff1, 5);		/*结算时间 */
						SF_FreezeYSettle(V_ucDataBuff1, 5);
						InF_ReadEnergy_Settlement( );					    /*取当前年结算周期内组合有功总累计用电量写数据层 */
					}
						
				}
			}
		}
	}	
		
}

///******************************************************************************************///
///*Function：	uchar8 SF_JudgeAndOrder_SettleAccounts(uchar8 *P_ucData,uchar8 V_ucLen,uchar8 V_ucNum)	                            	                		   	*///
///*Description： 对不同长度数组进行合法性判断，同时进行排序                                                    				*///
///*Input：         P_ucData数组起始地址，V_ucLen数据长度，V_ucNum为数组个数                                                             *///
///*Output：       有效数值个数                                                                *///										*///
///*Calls：                                                                                 *///
///*Called By：                                                                             *///
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
				V_ucTemp++;	///*结算日合法，加1*///	
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
						V_ucTemp++;	///*结算日合法，加1*///	
					}
				}
			}
			
		}
	}
	
	V_ucActiveNum = V_ucTemp;
	///**********结算日排序********///
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
函数原型：void SF_GetPosEnergy_Pul_SettleAccounts_Part(uchar8 *pV_ucResultData, ulong32 V_ulRate1PulseOAD)
功能描述：获取总脉冲数
输入参数：pV_ucResultData：存放数据的缓存；
		 V_ulRate1PulseOAD：数据标识
输出参数：pV_ucResultData：脉冲数数据；
返回参数：无
调用位置：结算电能
备    注：
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
        InF_Read_Data(V_ulRate1PulseOAD + 0x00000001 * i, &V_ucDataBuff[0], &V_usLen, &V_usDataEncode);  /* 读取费率脉冲数 */
		PF_Buffer8ToUlong64(V_ucDataBuff, &V_ulTemp1, CLPos_Ac_T2_En_Pul_0);
		V_ulTemp += V_ulTemp1;
	}
	
	PF_Ulong64ToBuffer8(pV_ucResultData, &V_ulTemp, 8);
	
	return;	
}

/*******************************************************************************
函数原型：获取正向有功总脉冲数
功能描述：获取正向有功总脉冲数
输入参数：V_ucResultData：读取电能后存放的数据缓存
输出参数：V_ucResultData：存放正向有功总脉冲数
返回参数：无
调用位置：
备    注：
*******************************************************************************/
void SF_GetPosEnergy_Pul_SettleAccounts(uchar8 *V_ucResultData)
{
	SF_GetPosEnergy_Pul_SettleAccounts_Part(V_ucResultData, CPos_Ac_T1_PreEn_0);
	return;
}

/*******************************************************************************
函数原型：获取反向有功总脉冲数
功能描述：获取反向有功总脉冲数
输入参数：V_ucResultData：读取电能后存放的数据缓存
输出参数：V_ucResultData：存放正向有功总脉冲数
返回参数：
调用位置：
备    注：
*******************************************************************************/
void SF_GetRevEnergy_Pul_SettleAccounts(uchar8 *V_ucResultData)
{
	SF_GetPosEnergy_Pul_SettleAccounts_Part(V_ucResultData, CRev_Ac_T1_PreEn_0);
	return;
}
///******************************************************************************************///
///*Function：	void SF_MsgSend_Relay(uchar8 *V_ucParm,uchar8 V_ucParmLen,uchar8 V_ucDerictAddr)                            	                		   	*///
///*Description：   发送消息                                                				*///
///*Input：                                                                      *///
///*                                                                   *///
///*                                         *///
///*Output：     																																  *///
///*		   																														 				*///
///*Calls：                                                                                 *///
///*Called By：                                                                             *///
///*Author:                                                                           *///
///******************************************************************************************///
void SF_MsgSend_SettleAccounts(void)
{
	uchar8 V_ucDataBuff[2];
	Str_Msg_Parameter	Str_Msg_SettleAccounts;
	
	V_ucDataBuff[0]=Pt_DemandStatus;
	V_ucDataBuff[1]=C_Settlement;
	 
//	Str_Msg_SettleAccounts.PowerFlag = C_PowerOn;///*掉电标志，用于各个消息处理模块自行判断是否进行掉电保存，C_PowerDown表示掉电准备进入低功耗，C_PowerOn表示有电*///
	Str_Msg_SettleAccounts.SourceAddr = C_Msg_SettleAccounts;///*源消息号*///
	Str_Msg_SettleAccounts.DerictAddr = C_Msg_DemandMetering;///*目的消息号*///
	Str_Msg_SettleAccounts.Length = Pt_DemandStatus_Len+1;///*长度*///
	Str_Msg_SettleAccounts.Parameter = V_ucDataBuff;///*参数*///
	InF_WriteMessege(&Str_Msg_SettleAccounts);///*写消息函数*///
}
/******************************************************************************************
函数原型：void SF_MsgSend_SettleAccounts_ReSettle_Day1(void)                          
功能描述：发送消息 ，修改第一结算日                                               	
输入参数：无                                                                         
输出参数：无																			
返回参数：无                                                                         
调用位置：Msg_SettleAccounts                                                         
备    注：                                                                                 
*******************************************************************************************/
void SF_MsgSend_SettleAccounts_ReSettle_Day1(void)
{
	uchar8 V_ucDataBuff[2];
	Str_Msg_Parameter Str_Msg_SettleAccounts;
	
	V_ucDataBuff[0] = Pt_DemandStatus;
	V_ucDataBuff[1] = C_Settlement_ReSettle_Day1;
	 
	Str_Msg_SettleAccounts.SourceAddr = C_Msg_SettleAccounts;    /*源消息号*/
	Str_Msg_SettleAccounts.DerictAddr = C_Msg_DemandMetering;    /*目的消息号*/
	Str_Msg_SettleAccounts.Length = Pt_DemandStatus_Len + 1;     /*长度*/
	Str_Msg_SettleAccounts.Parameter = V_ucDataBuff;             /*参数*/
	InF_WriteMessege( &Str_Msg_SettleAccounts );                 /*写消息函数*/
}
/*******************************************************************************
函数原型：uchar8 Inf_GetFrozenData_Settle23(uchar8 *V_ucData, ushort16 *V_ucResultDataLength, uchar8 V_Demand, ulong32 V_OADTable)
功能描述：获取冻结数据
输入参数：V_ulDataCode   约定冻结切换时间的标识码  
          Swich_Time   设置的切换时间  
输出参数：无
返回参数：C_OK, C_Error, C_DataLenError
调用位置：
备    注：数据格式:mmhhDDMMYYYY+XXXXXXXX(冻结数据)+DATA 
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
	/*赋值时间*/
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
        
		/*读上一次冻结序号数据，赋值*/
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
	
	/*读OAD及OAD个数*/
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
	
	/*按照OAD的顺序组织数据*/
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

		if ( ( ( V_ul645DI & 0xff000000 ) == 0x00000000 )       /*电能*/
		  || ( ( V_ul645DI & 0xFFFF0000 ) == 0x202D0000 )       /*透支金额*/
          || ( ( V_ul645DI & 0xFFFF0000 ) == 0x20310000 )       /*月度用电量*/
		  || ( V_ul645DI == 0x202C0201 )                        /*剩余金额*/
		  || ( ( V_ul645DI & 0xFFFF0000 ) == 0x20320000 ) )     /*阶梯结算用电量*/	
		{
            if( V_ucType == C_array)    /*需要读多个645标识码*/
            {
                for(i = 1; i <= V_uc645DINum; i++)
                {
                    V_ul645DI = Str_FrozenConvert_Table[V_usOAD[V_ucTurn] + i].V_ulOAD;
                    P_usData_Length = Str_FrozenConvert_Table[V_usOAD[V_ucTurn] + i].V_uc645Length;
                    if(InF_GetData_ObjectManage(V_ul645DI, (V_ucResultData + V_usOffset), &P_usData_Length, 0) == C_OK)   /*读取电能*/
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
                if(InF_GetData_ObjectManage(V_ul645DI, (V_ucResultData + V_usOffset), &P_usData_Length, 0)  == C_OK)  /*读取电能*/
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
        else if (V_ul645DI == 0x202C0200)    /*钱包文件*/
        {
            V_ul645DI = Str_FrozenConvert_Table[V_usOAD[V_ucTurn] + 1].V_ulOAD;
            P_Data_Length = Str_FrozenConvert_Table[V_usOAD[V_ucTurn] + 1].V_uc645Length;
            if( InF_GetData_ObjectManage(V_ul645DI, (V_ucResultData + V_usOffset), &P_usData_Length, 0) == C_OK)    /*读取电能*/
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
            /*读ESAM中的购电次数*/
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
        else if (V_ul645DI == 0x202C0202)    /*购电次数*/
        {
            /*读ESAM中的购电次数*/
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
               || ( ( V_ul645DI & 0xff000000 ) == 0x11000000 ) )     /*需量*/
        {
            if( V_ucType == C_array)        /*需要读多个645标识码*/
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
                || ( V_ul645DI == CVolB_Per_Pass_0 )		/*电压合格率和结算日分项特殊处理*/
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
            if( ( V_ucType == C_array ) || ( (V_ucType == C_structure) && ( V_uc645DINum != 0 ) ) )     /*需要读多个(电压合格率和结算日分项前面已特殊处理)*/
            {
                for( i = 1; i <= V_uc645DINum; i++)
                {
                    V_ul645DI = Str_FrozenConvert_Table[V_usOAD[V_ucTurn] + i].V_ulOAD;
                    P_Data_Length = Str_FrozenConvert_Table[V_usOAD[V_ucTurn] + i].V_uc645Length;
                    V_usLen = Str_FrozenConvert_Table[V_usOAD[V_ucTurn] + i].V_uc645Length; 
                      
                    if( (V_ul645DI & 0xff000000) == 0x00000000 )	   /*电能*/
                    {
                        if(InF_GetData_ObjectManage(V_ul645DI, (V_ucResultData + V_usOffset), &P_usData_Length, 0) == C_OK)      /*读取电能*/
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
		if( V_usOffset > V_usDataLenMax )	    /*最大长度不能超过输入Buff长度和自身Buff长度*/
		{
			return	C_DataLenError;
		}
	}
	PF_CopyDataBytes_698(V_ucResultData, V_ucData, V_usOffset);
	*V_ucResultDataLength = V_usOffset;
	
	return C_OK;
}

///******************************************************************************************///
///*Function：	uchar8 Inf_Read_FrozenData_OneOAD(ulong32 *V_Data_Id_OAD,ushort16 *V_Length)	*///
///*Description：获取上N次冻结单个OAD数据							*///
///*Input：ulong32 *V_Data_Id_OAD 冻结及数据OAD；ushort16 *V_Length缓存长度                     *///
///*Output：ushort16 *V_Length 读取数据长度							*///										*///
///*Calls：                                                                                 *///
///*Called By：                                                                             *///
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
函数原型：void SF_FreezeYSettle(uchar8 *Swich_Time, uchar8 Len)
功能描述：年冻结（后期改为阶梯结算冻结）
输入参数：Len 数据长度  
          Swich_Time   设置的切换时间  
输出参数：无
返回参数：无
调用位置：
备    注：
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



