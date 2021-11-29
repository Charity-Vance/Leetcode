/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    AppRelayControl.c                                                                 
**** Brief:       继电器控制                                                       
**** Author:      peter.he@chint.com                                                                 
**** Version:     V1.0                                                                               
**** Date:        2016-7-14                                                                          
****                                                                                                 
**** note:修改历史记录列表，每条修改记录应包括修改日期、修改者                                          
**** 1.  Author:                                                                                     
****     Version:                                                                                    
****     Date :                                                                                      
**** 2.  Author:                                                                                     
****     Version:                                                                                       
****     Date:
****                                                                                        
****  addtogroup:Library                                                             
**********************************************************************************************************/

/*--------------------------------- 文件功能说明 -------------------------------------------------------*/
/*
 *  该文件所有函数的前缀为 ApiMoney_
 *  文件主函数和对外函数需放在文件的首部，并且主函数需要放在第一个位置;
 *  函数注释采用标准模板，函数内部注释采用//;
 *  对于注释较多的部分，可以增加一个注释符，然后详细说明放在文件的尾部;
 *--------------------------------- 文件功能说明 -------------------------------------------------------*/
 
/**有形参的函数格式:*/
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    xx任务处理函数
 *
 *  @param    xx :
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
/**无形参的函数格式:*/
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    上电所有口线配置成初始状态，后面可根据需要开启和配置
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
 
 
/*----------------< 包含文件 >----------------------------------*/
#include "..\SourceFiles\PUB\Include.h"

/*----------------< 宏定义区 >----------------------------------*/


/*----------------< 常量定义 >----------------------------------*/


/*----------------< 变量定义 >----------------------------------*/


/*----------------< 函数声明 >----------------------------------*/
void ApiRelay_ControlProcess(void);	    	
void ApiRelay_SubtractMoneyRelayJudge(void);
void Api_PowerLoadLimitedCheck(void);

/*----------------< 函数定义 >----------------------------------*/

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    继电器控制函数
 *
 *  @return   xx
 *
 *  @note     xx
 *  ///待补充
 *  /
/*------------------------------------------------------------------------------------------------------*/
 void ApiRelay_ControlProcess(void)
{

	if(	GStr_Flag.ucRunState3 &F_RUN_LowVoltage )
	{
//		if(F_KEY_ACKTION_DOWN!=(GStr_Flag.ucFactoryKey&F_KEY_ACKTION_DOWN))
		if((GStr_Flag.ucMeterMode&F_FACTORY_MODE)!=F_FACTORY_MODE)
		{
			return;
		}
	}
	if(GStr_Counter.ucRelayDelay_Cnt)
	{
		return;
	}
	if((GStr_Flag.ucRunState1&F_RUN_OVER_DEMAND)||((GStr_Flag.ucRunState1&F_RUN_L2_ALRAM)&&(0==(GStr_Flag.ucRunState&F_RUN_CLOSE_L2)))
		||((GStr_Flag.ucRunState1&F_RUN_REMAIND_ZERO)&&(0==(GStr_Flag.ucRunState&F_RUN_CLOSE_ZERO)))||(GStr_Flag.ucRunState&F_RUN_OVER_DRAFTRELAY)
	     ||(GStr_Flag.ucRunState&F_RUN_DISABLE_CLOSE)||(GStr_Flag.ucRunState&F_RUN_COMM_RELAYOFF))
	///过载、过二级报警、过零、透支过限值、不允许合闸状态
	{
		if(GStr_Flag.ucRunState1&F_RUN_OVER_DEMAND)  ///过载直接跳闸不受保电限制
		{	
			RelayDrv_Openrelay();
			GStr_Counter.ucRelayDelay_Cnt = RelayOnce_Delaytimer;///3s置位
			LibPub_MemSetBytes(GA_ucRelayOperCode,0xFF,4);///过载拉闸的操作者代码为FFFFFFFF
			ApiEvent_WriteRecord(C_OpenRelay);///做拉闸事件记录
			GStr_Flag.ucRunState1 &=~F_RUN_OVER_DEMAND;///跳闸后请过载标志
			GStr_Flag.ucRunState2 |=F_RUN_RELAY_STATE;
			GStr_Flag.ucRunState1 |=F_RUN_OVER_DEMAND_CLOSE; ///过载跳闸后，自动恢复合闸标志，该状态下可以发送合闸命令和保电命令。
		}
		else if(GStr_Flag.ucRunState1&F_RUN_OVER_DEMAND_CLOSE)///处于超负荷自动合闸时间内,若发生其他跳闸事件，不操作
		{
			if(!(GStr_Flag.ucRunState2&F_RUN_RELAY_STATE))///如果是合闸状态
			{
				RelayDrv_Openrelay();
				GStr_Counter.ucRelayDelay_Cnt = RelayOnce_Delaytimer;///3s置位
				LibPub_MemSetBytes(GA_ucRelayOperCode,0xFF,4);///过载拉闸的操作者代码为FFFFFFFF
				ApiEvent_WriteRecord(C_OpenRelay);///做拉闸事件记录
				GStr_Flag.ucRunState2 |=F_RUN_RELAY_STATE;
			}
//			else
//			{
//				RelayDrv_Openrelay();
//			}
		}
		else
		{
			if(F_RUN_KEEP_ELEC!=(GStr_Flag.ucRunState&F_RUN_KEEP_ELEC))///其他情况下保电不动作
			{
				if((!(GStr_Flag.ucRunState2&F_RUN_RELAY_STATE))
					||((GStr_Flag.ucRunState2&F_RUN_RELAY_STATE)&&(GStr_Flag.ucRunState2&F_RUN_Current_State)))
				///处于合闸状态  或者处于跳闸状态但仍有0.01kwh脉冲出现
				{
					RelayDrv_Openrelay();
					GStr_Counter.ucRelayDelay_Cnt = RelayOnce_Delaytimer;///3s置位
					if(!(GStr_Flag.ucRunState&F_RUN_COMM_RELAYOFF))///不是通信跳闸//这里也不是过载跳闸，剩下的即为费控跳闸
					{
						LibPub_MemSetBytes(GA_ucRelayOperCode,0xFF,4);///费控拉闸的操作者代码为FFFFFFFF
					}
					ApiEvent_WriteRecord(C_OpenRelay);///做拉闸事件记录
					GStr_Flag.ucRunState2 |=F_RUN_RELAY_STATE;
					GStr_Flag.ucRunState2 &=~ F_RUN_Current_State;///跳闸之后走字标志清零，如再置1，说明跳闸失败
				}
			}
			else    //保电发合闸命令
			{
				if(GStr_Flag.ucRunState2&F_RUN_RELAY_STATE)///如果是跳闸状态，发合闸命令
				{
					RelayDrv_Closerelay()   ;
					GStr_Counter.ucRelayDelay_Cnt = RelayOnce_Delaytimer;///3s置位
					ApiEvent_WriteRecord(C_CloseRelay);///做拉闸事件记录
					GStr_Flag.ucRunState &=~F_RUN_COMM_RELAYOFF;  ///清通信跳闸
					GStr_Flag.ucRunState2 &=~F_RUN_RELAY_STATE;///清继电器跳闸标志	
					LibPub_WriteDataToE2prom(LIB_E2P_RUN_STATE,0,&GStr_Flag.ucRunState);	
				}
//				else
//				{
//					RelayDrv_Closerelay()   ;///拉合闸总线防止继电器状态错误不做事件记录
//				}
			}
		}

	}
	else
	{	
		if(GStr_Flag.ucRunState1&F_RUN_OVER_DEMAND_CLOSE)  ///如果是过载跳闸后的恢复合闸状态，
		{
			if(!(GStr_Flag.ucRunState2&F_RUN_RELAY_STATE))///如果是合闸状态
			{
				RelayDrv_Openrelay();
				GStr_Counter.ucRelayDelay_Cnt = RelayOnce_Delaytimer;///3s置位
				LibPub_MemSetBytes(GA_ucRelayOperCode,0xFF,4);///过载拉闸的操作者代码为FFFFFFFF
				ApiEvent_WriteRecord(C_OpenRelay);///做拉闸事件记录
				GStr_Flag.ucRunState2 |=F_RUN_RELAY_STATE;
			}
//			else
//			{
//				RelayDrv_Openrelay();			
//			}
			
		}
		else 
		{
			if(GStr_Flag.ucRunState2&F_RUN_RELAY_STATE)///如果是跳闸状态，发合闸命令
			{
				GStr_Flag.ucRunState &=~F_RUN_COMM_RELAYOFF;  ///清通信跳闸
				GStr_Flag.ucRunState2 &=~F_RUN_RELAY_STATE;///清继电器跳闸标志	
				RelayDrv_Closerelay();
				GStr_Counter.ucRelayDelay_Cnt = RelayOnce_Delaytimer;///3s置位
				#if ( METER_TYPE == METER_TYPE_DTSY666)
				///处理外控
				#endif
				ApiEvent_WriteRecord(C_CloseRelay);///做合闸事件记录
			}
			else
			{
//				if(GStr_Flag.ucRelayOnFlag)
//				{
//					GStr_Flag.ucRelayOnFlag=0;
//					RelayDrv_Closerelay()   ;//防止继电器状态错，恢复一下继电器///不做事件记录
//					GStr_Counter.ucRelayDelay_Cnt = RelayOnce_Delaytimer;///3s置位
////					ApiEvent_WriteRecord(C_CloseRelay);///做合闸事件记录
//				}
//				#if ( METER_TYPE == METER_TYPE_DTSY666)
//				///处理外控
//				#endif
			}
		}
	}
	
	if(GStr_Flag.ucRunState2&F_RUN_RELAY_STATE) 
	{
		GStr_Flag.ucRunState|=F_RUN_RELAY_STATE_EE;
		LibPub_WriteDataToE2prom(LIB_E2P_RUN_STATE,0,&GStr_Flag.ucRunState);
	}
	else
	{
		GStr_Flag.ucRunState&=~F_RUN_RELAY_STATE_EE;
		LibPub_WriteDataToE2prom(LIB_E2P_RUN_STATE,0,&GStr_Flag.ucRunState);
	}
}

///***********************************************************************************///
///*SubtractMoneyRelayJudge                                                          *///
///*Description：根据剩余金额和透支金额判断报警状态和继电器状态                         *///
///*Input：                                                                          *///      
///*                                                                                 *///
///*                                                                                 *///
///*Output：返回值 无                                                                *///
///*                                                                                 *///
///*Calls：                                                                          *///
///*Called By：                                                                      *///
///*Influence：                                                                      *///
///*Tips：                                                                           *///
///*Others：                                                                         *///
///*Author:chenshou                                                                  *///
///***********************************************************************************///    	    	
void ApiRelay_SubtractMoneyRelayJudge(void)
{
	uchar8  V_Buff[25];
	uchar8  V_B_OverDraftLockRelayflag;
	uchar8  V_B_OverDraftLockRelayflag1;
	ulong32 V_ulBuff[2];
	
	V_B_OverDraftLockRelayflag = 0;
	V_B_OverDraftLockRelayflag1 = 0;
	///* 报警金额1(0-3)、报警金额2(4-7)、囤积金额(8-11)、透支金额(12-15)、合闸允许金额(16-19)、过载功率(20-23) *///
	LibPub_ReadDataFromE2prom( LIB_E2P_Money_Para,0,&V_Buff[0]);
	
	///*判断透支金额
	if( GStr_Flag.ucRunState&F_RUN_OVER_DRAFTRELAY )///*透支溢出标志*///
	{
		V_ulBuff[0]= LibPub_Buffer4ToUlong32(&V_Buff[16]);   ///合闸允许金额
		V_ulBuff[1]=LibPub_Buffer4ToUlong32(&GStr_Money.ucaRemainMoney[0]);///剩余金额
		if(V_ulBuff[1])
		{
			if(V_ulBuff[0]>=V_ulBuff[1])///*剩余金额<=合闸允许金额则继续跳闸*///
	    	{
	    		V_B_OverDraftLockRelayflag = 1;    ///*置透支溢出锁死标志*///
				if(GStr_Flag.ucRunState &F_RUN_DISABLE_CLOSE)  V_B_OverDraftLockRelayflag1=1;
	    	}
			else //合闸允许金额<剩余金额
			{
				V_B_OverDraftLockRelayflag=0;
				V_B_OverDraftLockRelayflag1=0;
				GStr_Flag.ucRunState&=~F_RUN_OVER_DRAFTRELAY;///清透支超限和不允许合闸标志
				GStr_Flag.ucRunState&=~F_RUN_DISABLE_CLOSE;///清透支超限和不允许合闸标志
			}
		}
		else
	    {
	    	V_B_OverDraftLockRelayflag = 1;    ///*充值完以后剩余金额小于0置透支溢出锁死标志*///
			if(GStr_Flag.ucRunState &F_RUN_DISABLE_CLOSE)V_B_OverDraftLockRelayflag1=1;
	    }
	}
	
	///*判断报警金额
	V_ulBuff[0]= LibPub_Buffer4ToUlong32(&V_Buff[0]);///一级报警金额
	V_ulBuff[1]=LibPub_Buffer4ToUlong32(&GStr_Money.ucaRemainMoney[0]);///剩余金额
	if(V_ulBuff[0]>=V_ulBuff[1])///*报警金额1是否大于剩余金额*///
	{
		GStr_Flag.ucRunState1 |=F_RUN_L1_ALRAM;  ///*置1级报警标志*///
		V_ulBuff[0]= LibPub_Buffer4ToUlong32(&V_Buff[4]);///二级报警金额
		if(V_ulBuff[0]>=V_ulBuff[1])///*报警金额2是否大于剩余金额*///
		{
			if((GStr_Flag.ucRunState1&F_RUN_L2_ALRAM) == 0)
			{
				GStr_Flag.ucRunState1 |= F_RUN_L2_ALRAM; 	       ///*置2级报警标志*///
//				(*(ulong32 *)&GA_ucDelayOperCode[0]) = 0xFFFFFFFF; ///*这里要跳闸了，操作者代码是FFFFFFFF*///
			}
			if(V_ulBuff[1] == 0)	///*剩余金额为零，有透支*///
			{
				if((GStr_Flag.ucRunState1&F_RUN_REMAIND_ZERO) == 0)
				{
					GStr_Flag.ucRunState1 |= F_RUN_REMAIND_ZERO; ///*置剩余金额为0标志*///
//					(*(ulong32 *)&GA_ucDelayOperCode[0]) = 0xFFFFFFFF; ///*这里要跳闸了，操作者代码是FFFFFFFF*///
				}
				V_ulBuff[0]= LibPub_Buffer4ToUlong32(&GStr_Money.ucaTickMoney[0]);///透支金额
				if(V_ulBuff[0]!=0)///*透支金额不为0///
				{
					if((GStr_Flag.ucRunState1&F_RUN_OVER_DRAFT) == 0)
					{
						GStr_Flag.ucRunState1 |=F_RUN_OVER_DRAFT ;///置透支状态
					}
				}
				else
				{
					GStr_Flag.ucRunState1 &=~F_RUN_OVER_DRAFT;
				}
                V_ulBuff[1]= LibPub_Buffer4ToUlong32(&V_Buff[12]);   ///透支金额门限
				if(V_ulBuff[0]>= V_ulBuff[1])///*透支金额是否大于透支门限金额*///
        		{
        			GStr_Flag.ucRunState |= F_RUN_OVER_DRAFTRELAY;     ///*置透支溢出标志*///
//        			(*(ulong32 *)&GA_ucDelayOperCode[0]) = 0xFFFFFFFF; ///*这里要跳闸了，操作者代码是FFFFFFFF*///
        		}
				else
				{
					GStr_Flag.ucRunState &= ~F_RUN_OVER_DRAFTRELAY;          ///*清透支溢出标志*///  
				}
			}
			else
		    {
				GStr_Flag.ucRunState1 &= ~F_RUN_OVER_DRAFT;            ///*清透支标志*///
				GStr_Flag.ucRunState &= ~F_RUN_OVER_DRAFTRELAY; 		  ///*清透支溢出标志*///
				GStr_Flag.ucRunState1 &= ~F_RUN_REMAIND_ZERO; 
				GStr_Flag.ucRunState &=~F_RUN_DISABLE_CLOSE;	   ///请不允许合闸标志
		    }
		}
		else
		{
			GStr_Flag.ucRunState1 &= 0xE1;  ///*清掉除1级报警外的所有报警*/// 		
		}
	} 
	else
	{
		GStr_Flag.ucRunState1 &= 0xE0;  ///*清掉所有的报警*///
		GStr_Flag.ucRunState &=~F_RUN_DISABLE_CLOSE;	   ///请不允许合闸标志
	}
	
	if(V_B_OverDraftLockRelayflag == 1)
	{
		GStr_Flag.ucRunState |= F_RUN_OVER_DRAFTRELAY;      ///*置透支溢出标志*///
	}
	if(V_B_OverDraftLockRelayflag1 == 1)
	{
		GStr_Flag.ucRunState |=F_RUN_DISABLE_CLOSE;			///*充值后若未达到合闸允许金额限值则不能合闸*///
	}
	
	if(GStr_Flag.ucRunState& F_RUN_OVER_DRAFTRELAY)
	{
		GStr_Flag.ucRunState |=F_RUN_DISABLE_CLOSE;
	}
	LibPub_WriteDataToE2prom(LIB_E2P_RUN_STATE,0,&GStr_Flag.ucRunState);	
//	ApiRelay_ControlProcess();
//	if(GV_ucInitOperateRelay==0x00)
//	{
//		RelayServe(&GStr_ControlWord_CH2,C_AARelay_CH2);	   
//		//RelayServe(&GStr_ControlWordOUT,C_55OutsideRelay);
//		GV_ucRelayDelayTimer=C_RelayDelayTimer;
//	}
//	else
//	{
//		GV_ucInitOperateRelay=0x00;
//	}
	//操作继电器  需补充

}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    功率超限跳闸检测   1S一次
              低电压检测
 *
 *  @return   xx
 *
 *  @note     xx
 *  ///待补充
 *  /
/*------------------------------------------------------------------------------------------------------*/
void Api_PowerLoadLimitedCheck(void)
{
	ulong32 v_ulTemp;
	uchar8  v_ucTemp[4];
	
	#if(METER_TYPE!=METER_TYPE_DTSY666)
	if(GStr_UIPGroup.ulVoltage[0]<=1650)///220V的75%为低电压标志
	#else
	if((GStr_UIPGroup.ulVoltage[0]<=1650)&&(GStr_UIPGroup.ulVoltage[1]<=1650)&&(GStr_UIPGroup.ulVoltage[2]<=1650))///220V的75%为低电压标志
	#endif
	{
		GStr_Flag.ucRunState3 |=F_RUN_LowVoltage;  ///低于75%Un标志
	}
	else
	{
		GStr_Flag.ucRunState3 &=~F_RUN_LowVoltage;  
	}

	#if(METER_TYPE==METER_TYPE_DTSY666)
	if( (GStr_UIPGroup.ulVoltage[0] >= API_Relayact_Voltage)||(GStr_UIPGroup.ulVoltage[1] >= API_Relayact_Voltage)||(GStr_UIPGroup.ulVoltage[2] >= API_Relayact_Voltage) )	///高于API_Relayact_Voltage
	{
		GStr_Flag.ucRunState3 |= F_RUN_Relayact_Voltage;  //电压高于API_Relayact_Voltage，则置F_RUN_Relayact_Voltage标志
	}
	else
	{
		GStr_Flag.ucRunState3 &= ~F_RUN_Relayact_Voltage;  
	}
	#endif

	if(_FALSE==LibPub_ZeroCheck(&GStr_MoneyPara.ucaOverLoadVal[0], 3))
	{	
			v_ucTemp[0]=0;
			LibPub_MemCopyBytes( &GStr_MoneyPara.ucaOverLoadVal[0], &v_ucTemp[1],3);
			v_ulTemp=LibPub_DECtoHEXBytes(v_ucTemp,4);///过载功率转换成HEX
			#if(METER_TYPE==METER_TYPE_DTSY666)
			if((GStr_UIPGroup.ulPower[0]>=v_ulTemp) ||(GStr_UIPGroup.ulPower[1]>=v_ulTemp)||(GStr_UIPGroup.ulPower[2]>=v_ulTemp) ) ///分相功率大于等于过载功率
			#else
			if(GStr_UIPGroup.ulPower[0]>=v_ulTemp)
			#endif	
			{ 
				GStr_Monitor.ucPowerLimitNum++;   
			}
			else
			{ 
				GStr_Monitor.ucPowerLimitNum = 0; 
			}
		///1s判定一次，若10次均大于过载功率  则直接拉闸
			if( GStr_Monitor.ucPowerLimitNum >= 10 )								
			{
				GStr_Monitor.ucPowerLimitNum = 0;

				GStr_Flag.ucRunState1 |=F_RUN_OVER_DEMAND;  ///置过载跳闸标志
				ApiRelay_ControlProcess();
				GStr_Monitor.ulOverDemandCloseTime=LibPub_GetTimerBeat();///过载跳闸后去系统时间
		//		(*(ulong32 *)&GA_ucDelayOperCode[0]) = 0xFFFFFFFF;                    ///*操作者代码*///		

			}	 
	}
	else///过载功率为0，不开启过载功能
	{
			GStr_Flag.ucRunState1 &=~F_RUN_OVER_DEMAND;
	}
}
