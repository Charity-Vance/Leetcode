/*********************************************************************************
Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     Demand.c
Version:       V1
Author:        
Date:          2014-3-12
Description:   最大需量处理文件
----------------------------------------------------------------------------------
History1:      第1次修改
内容1. Date:   20211019
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
*********************************************************************************/

#include "Public.h"
#include "Demand.h"

/*--------------------------------------------------------------------------*/
/* 全局变量 */
/*--------------------------------------------------------------------------*/
ushort16 SV_usActiveRateDemandIntervalTimer_T;						/* 总有功费率需量周期定时器 */
ushort16 SV_usReactiveRateDemandIntervalTimer_T;					/* 总无功费率需量周期定时器 */
uchar8	 SV_ucActiveDemandIntervalTimer_T;							/* 总有功需量周期定时器 */
uchar8	 SV_ucReactiveDemandIntervalTimer_T;						/* 总无功需量周期定时器 */
uchar8	 SV_ucActiveDemandIntervalTimer_SePhase[3];					/* 分相有功需量周期定时器,分别对应A、B、C */
uchar8	 SV_ucReactiveDemandIntervalTimer_SePhase[3];				/* 分相无功需量周期定时器,分别对应A、B、C */
			                                                           
ulong32	 SV_ulActivePower_T[C_1minAvaragePowerNum]@".DataProcessADDR";					/* 合相1min有功平均功率，存放60min数据 */
ulong32	 SV_ulReactivePower_T[C_1minAvaragePowerNum]@".DataProcessADDR";				/* 合相1min无 功平均功率，存放60min数据 */
ulong32	 SV_ulActivePower_SePhase[3][C_1minAvaragePowerNum];		/* 分相1min有功平均功率，存放60min数据,分别对应A、B、C */
ulong32	 SV_ulReactivePower_SePhase[3][C_1minAvaragePowerNum];		/* 分相1min无 功平均功率，存放60min数据,分别对应A、B、C */

uchar8   SV_ucPowerDirection;						  				/* 1min平均功率累加和方向 */

uchar8	 SV_ucDemandSafe;							  				/* 需量计量安全标志字 */
/*--------------------------------------------------------------------------*/

/* 组合需量 */
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

/* 当前需量数据标识判断标志 */
const uchar8 C_ActiveCodeIDTable[3]   = { C_A_ActiveCodeID, C_B_ActiveCodeID, C_C_ActiveCodeID };
const uchar8 C_ReactiveCodeIDTable[3] = { C_A_ReactiveCodeID, C_B_ReactiveCodeID, C_C_ReactiveCodeID };

/*******************************************************************************
函数原型：void InF_DemandInit(void)
功能描述：上电最大需量内部静态变量初始化
输入参数：无
输出参数：无
返回参数：无
调用位置：调度上电初始化时调用	
备    注：
*******************************************************************************/
void InF_DemandInit(void)
{	
	/* 进行需量周期定时器初始化 */
	SF_InitDemandTimer(C_DemandPowerUp);	
	
	/* 以下进行1min平均功率初始化 */
	memset(SV_ulActivePower_T,         0x00, sizeof( SV_ulActivePower_T ) );
	memset(SV_ulReactivePower_T,       0x00, sizeof( SV_ulReactivePower_T ) );
	memset(SV_ulActivePower_SePhase,   0x00, sizeof( SV_ulActivePower_SePhase ) );
	memset(SV_ulReactivePower_SePhase, 0x00, sizeof( SV_ulReactivePower_SePhase ) );
		
	SV_ucPowerDirection	= 0;
	
	/* 安全字节清零 */
	SV_ucDemandSafe = 0;
	
	/* 当前需量清零 */
	SF_Clear_CurrentDemand( );	/* 将当前需量清零 */
}

/*******************************************************************************
函数原型：void SF_Set_DemandInternal(uchar8 V_ucDemand, uchar8 V_ucTDemandTimerInitFlag) 
功能描述：初始化所有需量定时器
输入参数：V_ucDemand:需量周期；
		  V_ucTDemandTimerInitFlag:总有功、总无功需量定时器是否初始化标志，
									C_TDemandTimerInit_Flag，初始化总有功、总无功需量定时器
									C_TDemandTimerNoInit_Flag，不初始化总有功、总无功需量定时器
输出参数：无
返回参数：无
调用位置：初始化所有需量定时器用	
备    注：
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
	SV_usReactiveRateDemandIntervalTimer_T = (SV_usReactiveRateDemandIntervalTimer_T & 0xFF00) + V_ucDemand;	/*费率定时器清理，需量周期默认需量周期+1*/
	SV_ucActiveDemandIntervalTimer_T   = V_ucDemand;
	SV_ucReactiveDemandIntervalTimer_T = V_ucDemand;
	
	for( V_uci = 0; V_uci < 3; V_uci++ )
	{
		SV_ucActiveDemandIntervalTimer_SePhase[V_uci] = V_ucDemand;
		SV_ucReactiveDemandIntervalTimer_SePhase[V_uci] = V_ucDemand;
	}
}

/**********************************************************************************************************
函数原型：void SF_InitDemandTimer(uchar8 V_ucFlay)
功能描述：初始化需量周期
输入参数：V_ucFlay = C_ReworkTime表示修改时间,
				   = C_ReDemand_Cycle表示修改最大需量周期,
 				   = C_MeterClear表示电表清零,=C_DemandClear表示需量清零,
 				   = C_Settlement表示过结算日,=C_RatesChanged费率改变,
                   = C_DemandPowerUp表示上电,=C_DerictionChange_AT合相有功功率方向改变,
                   = C_DerictionChange_RT合相无功功率改变,
                   = C_DerictionChange_AA表示A相有功功率改变，
                   = C_DerictionChange_AB表示B相有功功率方向改变,
				   = C_DerictionChange_AC表示C相有功功率方向改变，
				   = C_DerictionChange_RA表示A相无功功率方向改变,
                   = C_DerictionChange_RB表示B相无功功率方向改变，
                   = C_DerictionChange_RC表示C相无功功率方向改变,
                   = C_Settlement_ReSettle_Day1表示修改第一结算日，过结算,
输出参数：无
返回参数：无
调用位置：需量周期需要重新计量时调用
备    注：
*********************************************************************************************************/
void SF_InitDemandTimer(uchar8 V_ucFlay)
{
	uchar8	 V_ucDemand, V_uci, V_ucBuffer[CLDate_Time];
	ushort16 V_usLen, V_usDataEncode;

    /* 调用数据层接口函数，读出最大需量周期 */
	V_usDataEncode = 0;
	V_usLen = CLDemand_Cycle;
	if( InF_Read_Data(CDemand_Cycle, &V_ucDemand, &V_usLen, &V_usDataEncode) != C_OK )
	{
		V_ucDemand = C_NormalDemandInterval;					/* 最大需量周期读错，则默认15min */
	}
	
	V_usDataEncode = 0;
	V_usLen = CLDate_Time;
	InF_Read_Data(CDate_Time, V_ucBuffer, &V_usLen, &V_usDataEncode);
	
	V_uci = 0;
    if(V_ucFlay != C_Settlement)           /* 修改第一结算日C_Settlement_ReSettle_Day1需要判秒 */
	{
        if(V_ucBuffer[0] > 1)			   
        {
            V_uci = 1;
        }
    }
    else
    {
        ;    /* 过结算日C_Settlement不判断秒 */
    }
    
	if( (V_ucFlay == C_DemandClear)          /* 修改时间、修改需量周期、需量清零、电表清零 */
	 || ( (V_ucFlay >= C_DerictionChange_AT) && (V_ucFlay <= C_DerictionChange_RC) ) )   /* 功率方向改变，需量定时器也直接加1 */
	{
		V_uci = 1;
	}
	
	V_ucDemand += V_uci;					/* 最大需量周期加上i，表示不是整分需量周期加1 */

	memset(&V_ucBuffer[0], 0x00, CL_Demand);
	
	switch(V_ucFlay)
	{
		case C_DemandPowerUp:
		{
			SF_Set_DemandInternal(V_ucDemand, C_TDemandTimerInit_Flag);		/* 初始化定时器 */
        }break;
		case C_ReworkTime:
		case C_ReDemand_Cycle:
		case C_MeterClear:
		case C_DemandClear:
		/*case C_Settlement:	结算不改，还按照原来昨天，不做buffer清零*/
		{
			SF_Set_DemandInternal(V_ucDemand, C_TDemandTimerNoInit_Flag);	/* 初始化定时器 */
			
            SF_Clear_CurrentDemand();	            /* 将当前需量清零 */
		
			/* 以下将需量计算buffer、1min累加和及次数清零 */
			memset(SV_ulActivePower_T,         0x00, sizeof( SV_ulActivePower_T ) );
			memset(SV_ulReactivePower_T,       0x00, sizeof( SV_ulReactivePower_T ) );
			memset(SV_ulActivePower_SePhase,   0x00, sizeof( SV_ulActivePower_SePhase ) );
			memset(SV_ulReactivePower_SePhase, 0x00, sizeof( SV_ulReactivePower_SePhase ) );
						
		}break;
		case C_Settlement:
        case C_Settlement_ReSettle_Day1:
		{
			
			SF_Set_DemandInternal(V_ucDemand, C_TDemandTimerNoInit_Flag);	/* 初始化定时器 */
            SF_Clear_CurrentDemand();	           /* 将当前需量清零 */
            
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
			SV_usReactiveRateDemandIntervalTimer_T = (SV_usActiveRateDemandIntervalTimer_T & 0xFF00) + V_ucDemand;	/*费率定时器清理，需量周期默认需量周期+1*/
			SV_ucActiveDemandIntervalTimer_T = V_ucDemand;
			SV_ucReactiveDemandIntervalTimer_T = V_ucDemand;

            SF_Clear_CurrentDemand();	/* 将当前需量清零 */
            
		}break;
		case C_DerictionChange_RT:
		{
			SV_usReactiveRateDemandIntervalTimer_T = (SV_usActiveRateDemandIntervalTimer_T & 0xFF00) + V_ucDemand;	/*费率定时器清理，需量周期默认需量周期+1*/
			SV_ucReactiveDemandIntervalTimer_T = V_ucDemand;
			
            InF_Write_Data(C_Msg_DemandMetering,CCurr_ReDemand, &V_ucBuffer[0], CCurr_AcDemandLen, C_W_SafeFlag);	/*当前无功需量清零*/
            
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
函数原型：void SF_1minPerPowerSum_Direction(uchar8 V_ucCurrentDeriction, uchar8 V_ucDerictionFlag, uchar8 V_ucDemandTimerClearFlag)
功能描述：判断1min平均功率方向，方向改变需量周期定时器清零
输入参数：V_ucCurrentDeriction：当前功率方向；
		  V_ucDerictionFlag：当前功率对应位；
		  V_ucDemandTimerClearFlag：需量定时器清零标志；
输出参数：无
返回参数：无
调用位置：计量模块每1s调用1次
备    注：
*****************************************************************************************************************************/
void SF_1minPerPowerSum_Direction(uchar8 V_ucCurrentDeriction, uchar8 V_ucDerictionFlag, uchar8 V_ucDemandTimerClearFlag)
{
	if( ( V_ucCurrentDeriction & V_ucDerictionFlag ) != ( SV_ucPowerDirection & V_ucDerictionFlag ) )
	{
		SF_InitDemandTimer(V_ucDemandTimerClearFlag);			/* 调用函数将合相有功最大需量周期进行初始化 */
		SV_ucPowerDirection &= (~V_ucDerictionFlag);
		SV_ucPowerDirection |= (V_ucCurrentDeriction & V_ucDerictionFlag);
	}
}

/*******************************************************************************
函数原型：void InF_PowerChanggeInitDemand(Str_RealtimePower_Type *pStr_RealtimePower)
功能描述：判断功率发生变化，若发生变化，则进行需量定时器清零  
输入参数：pStr_RealtimePower指向实时功率结构体
输出参数：无
返回参数：无
调用位置：计量模块每1s调用1次
备    注：
*******************************************************************************/
void InF_PowerChanggeInitDemand(Str_RealtimePower_Type *pStr_RealtimePower)
{
	/* 总有功功率处理 */
	SF_1minPerPowerSum_Direction( pStr_RealtimePower->Deriction, C_DerictActive_T, C_DerictionChange_AT );

	/* 总无功功率处理 */
	SF_1minPerPowerSum_Direction( pStr_RealtimePower->Deriction, C_DerictReactive_T, C_DerictionChange_RT);
	
	/* A相有功功率处理 */
	SF_1minPerPowerSum_Direction( pStr_RealtimePower->Deriction, C_DerictActive_A, C_DerictionChange_AA);
	
	/* B相有功功率处理 */
	SF_1minPerPowerSum_Direction( pStr_RealtimePower->Deriction, C_DerictActive_B, C_DerictionChange_AB);
	
	/* C相有功功率处理 */
	SF_1minPerPowerSum_Direction( pStr_RealtimePower->Deriction, C_DerictActive_C, C_DerictionChange_AC);
	
	/* A相无功功率处理 */
	SF_1minPerPowerSum_Direction( pStr_RealtimePower->Deriction, C_DerictReactive_A, C_DerictionChange_RA);
	
	/* B相无功功率处理 */
	SF_1minPerPowerSum_Direction( pStr_RealtimePower->Deriction, C_DerictReactive_B, C_DerictionChange_RB);
	
	/* C相无功功率处理 */
	SF_1minPerPowerSum_Direction( pStr_RealtimePower->Deriction, C_DerictReactive_C, C_DerictionChange_RC);
}

/*******************************************************************************
函数原型：void SF_DemandMetering(ulong32 V_ulMaxDemandCode, ulong32 V_ulCurrentDemandCode, ulong32 *P_ulDemand)
功能描述：最大需量处理消息函数
输入参数：V_ulMaxDemandCode:当前最大需量的数据标识；
         V_ulCurrentDemandCode：当前需量的数据标识；
		 P_ulDemand：1min平均功率数据首地址
输出参数：无 
返回参数：C_OK正确处理，C_Error处理过程中出错
调用位置：调度消息1min触发1次，费率模块费率改变触发，通信修改时间、修改需量周期、电表清零及需量清零触发
备    注：结算模块同第一结算日结算操作时触发 
*******************************************************************************/
void SF_DemandMetering(ulong32 V_ulMaxDemandCode, ulong32 V_ulCurrentDemandCode, ulong32 *pV_ulDemand)
{
	uchar8   V_ucBuffer[CL_DemandAndTime], V_ucLastDemand[CL_DemandAndTime];
	uchar8   V_uci, V_ucDemandInternal = 0, V_ucReworkFlay, V_ucRemainder;
	ulong64  V_ullDemandAdd;
	ushort16 V_usLen, V_usDataEncode;
	
	/* 读取最大需量周期 */
	V_usDataEncode = 0;
	V_usLen = CLDemand_Cycle;
	if( InF_Read_Data(CDemand_Cycle, &V_ucDemandInternal, &V_usLen, &V_usDataEncode) != C_OK )
	{
		V_ucDemandInternal = C_NormalDemandInterval;
	}
	
	/* 6位小数需量计算 */
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
	
	/* 4位小数需量计算，需四舍五入 */
	V_ucRemainder = V_ullDemandAdd % 100;
	V_ullDemandAdd /= 100;
	if( V_ucRemainder > 49 )  /* 四舍五入 */
	{
		V_ullDemandAdd += 1;
	}
	
	PF_Ulong64ToBuffer8(V_ucBuffer, &V_ullDemandAdd, CL_Demand);

	/* 判断需量是否需要更新 */
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
	
	/* 需量更新处理 */
	if( C_ReworkDemand == V_ucReworkFlay )
	{
		/* 读取数据层当前日期时间 */
		V_usDataEncode = 0;
		V_usLen = CLDate_Time;
		InF_Read_Data(CDate_Time, &V_ucBuffer[CL_Demand], &V_usLen, &V_usDataEncode);
		
		V_ucBuffer[CL_Demand] = 0x00;  /* 秒默认为0 */
		
		InF_Write_Data(C_Msg_DemandMetering, V_ulMaxDemandCode, V_ucBuffer, CL_DemandAndTime, SV_ucDemandSafe);
	}
	
	/******************************* 更新当前需量，并返写数据层 *****************/
	if( V_ulCurrentDemandCode != NULL )				/* 需要更新当前需量 */
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
函数原型：void SF_DemandTimerClearDealWith(uchar8 V_ucClearType)
功能描述：最大需量定时器清零处理
输入参数：V_ucClearType，最大需量清零标志：
		  C_Settlement 自然过结算，
          C_DemandClear 通信需量清零，
          C_ReworkTime 通信修改时间
		  C_ReDemand_Cycle 通信修改最大需量周期，
          C_MeterClear 电表清零，
          C_RatesChanged 费率变更
		  C_DemandPowerUp 上电需量定时器清零
输出参数：无
返回参数：无
调用位置：调度消息1min触发1次，费率模块费率改变触发，通信修改时间、修改需量周期、电表清零及需量清零触发
          结算模块同第一结算日结算操作时触发
备    注：
*********************************************************************************************************/
void SF_DemandTimerClearDealWith(uchar8 V_ucClearType)
{
	if(SV_ucDemandSafe != C_W_SafeFlag)
	{
		return;
	}
	switch(V_ucClearType)						/* 判断消息类型 */
	{
		case C_Settlement:			         	/* 自然过结算日 */
		case C_Settlement_ReSettle_Day1:     	/* 修改结算日结算 */
		case C_ReworkTime:			         	/* 修改时间 */
		case C_RatesChanged:			     	/* 费率判断 */
		case C_DemandPowerUp:			      	/* 上电 */
		/*case C_DataFreeze:*/			        /* 过日冻结 */
		case C_DemandClear:			        	/* 通信 */
		case C_ReDemand_Cycle:		        	/* 修改最大需量周期 */
		case C_MeterClear:			        	/* 电表清零 */
		{
			SF_InitDemandTimer( V_ucClearType );
			
		}break;
		default:
		 break;
	}
}

/*******************************************************************************
函数原型：ulong32 SF_GetDemandCodeNum(uchar8 V_ucDemandType)
功能描述：获取最大需量标识码	
输入参数：V_ucDemandType为获取标识码类型
		 C_T_ActiveCodeID合相有功标识码，C_T_ReactiveCodeID合相无功标识码
		 C_A_ActiveCodeID A相有功标识码，C_A_ReactiveCodeID A相无功标识码
		 C_B_ActiveCodeID B相有功标识码，C_B_ReactiveCodeID B相无功标识码
		 C_C_ActiveCodeID C相有功标识码，C_C_ReactiveCodeID C相无功标识码
输出参数：无
返回参数：当前应该累加的需量标识码
调用位置：进行最大需量计算获取对应标识码时调用
备    注：
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
函数原型：uchar8 InF_DemandMetering_Message(Str_Msg_Parameter *pStr_Msg_Parameter)
功能描述：最大需量处理消息函数
输入参数：pStr_Msg_Parameter指向消息读取后存放的静态变量
输出参数：无 
返回参数：C_OK正确处理，C_Error处理过程中出差
调用位置：调度消息1min触发1次，费率模块费率改变触发，通信修改时间、修改需量周期、电表清零及需量清零触发
          结算模块同第一结算日结算操作时触发 
备    注：
*******************************************************************************/
uchar8 InF_DemandMetering_Message(Str_Msg_Parameter *pStr_Msg_Parameter)
{
	uchar8  V_ucBuffer[30], V_ucLen, V_uci, V_ucj, V_ucSlipTime;
	ulong32 V_ulDemandCode;
	ulong32 *pV_ulAddr;
	ushort16 V_usLen, V_usDataEncode;
	
	/* 判断掉电标志是否为有电，不是直接返回错误 */
	if( pStr_Msg_Parameter->PowerFlag != C_PowerOn )
	{
		return C_Error;
	}
	
	SV_ucDemandSafe = C_W_SafeFlag_1;
	V_ucLen = pStr_Msg_Parameter->Length + 1;
	
	PF_CopyDataBytes( pStr_Msg_Parameter->Parameter, V_ucBuffer, V_ucLen );		/* 把消息数据从全局变量中copy处来 */
		
	if( ( V_ucBuffer[0] == Pt_DemandStatus )
	 || ( V_ucBuffer[0] == Pt_ParaMetersChange)
	 || ( V_ucBuffer[0] == Pt_MeterClear ) )				/* 非调度1min定时处理这里是需要进行定时器清零处理的 */
	{
		SV_ucDemandSafe |= C_W_SafeFlag_2;
		if(V_ucBuffer[0] == Pt_MeterClear)					/* 电表清零消息类型，为通信广播下发的，没有参数值，这里赋值为需量清零 */
		{
			V_ucBuffer[1] = C_DemandClear;
		}
		SV_ucDemandSafe |= C_W_SafeFlag_3;
		SF_DemandTimerClearDealWith( V_ucBuffer[1] );
	}
	else if( V_ucBuffer[0] == Pt_Dispatch_Timing )
	{
		SV_ucDemandSafe |= C_W_SafeFlag_2;
		if( V_ucBuffer[1] == C_SystemMinChange )			/* 调度min变化 */
		{
			/* 更新1min平均功率 */
			for( V_uci = 0; V_uci < C_PowerTypeNum; V_uci++)
			{
				/* 当量向后移位 */
				pV_ulAddr = C_ComDemandRAMAddeTable[V_uci].PowerAvarageAddr;
				for( V_ucj = ( C_1minAvaragePowerNum - 1 ); V_ucj > 0; V_ucj--)
				{
					*(pV_ulAddr + V_ucj) = *(pV_ulAddr + V_ucj - 1);
				}
				
				/* 读1min平均功率（6位小数） */
				V_usLen = CL1minPerPower;
				V_usDataEncode = 0;
				if( InF_GetData_ObjectManage( C_ComDemandRAMAddeTable[V_uci].AvaragePowerCode, V_ucBuffer, &V_usLen, &V_usDataEncode) == C_OK )
				{
					PF_BufferXToUlong32(V_ucBuffer, pV_ulAddr, CL1minPerPower);
				}	
				
			}
						
 			/* 读取滑差时间 */
			V_usDataEncode = 0;
		 	V_usLen = CLSliding_Time;
		 	if( InF_Read_Data(CSliding_Time, &V_ucSlipTime, &V_usLen, &V_usDataEncode) != C_OK )
		 	{
		 		V_ucSlipTime = C_NormalSlipTime;
		 	}

			SV_ucDemandSafe |= C_W_SafeFlag_3;
			
			/********************** 合相有功需量 *******************************************/
			V_ulDemandCode = SF_GetDemandCodeNum( C_T_ActiveCodeID );
			
			/* 合相总有功需量计算 */
			if( SV_ucActiveDemandIntervalTimer_T > 0 )
			{
				SV_ucActiveDemandIntervalTimer_T--;
				if( SV_ucActiveDemandIntervalTimer_T == 0 )	   				/* 计算最大需量 */
				{
					SV_ucActiveDemandIntervalTimer_T = V_ucSlipTime;		/* 定时器给滑差时间 */
					SF_DemandMetering(V_ulDemandCode, CCurr_AcDemand, SV_ulActivePower_T);
					InF_MultiFunctionOutput(C_DemandPulse);
				}
			}
			
			/* 合相有功费率需量计算 */
			if( ( SV_usActiveRateDemandIntervalTimer_T & 0xFF ) > 0 )
			{
				SV_usActiveRateDemandIntervalTimer_T--;
				if( ( SV_usActiveRateDemandIntervalTimer_T & 0xFF ) == 0 )				/* 计算最大需量 */
				{
					SV_usActiveRateDemandIntervalTimer_T |= (ushort16)V_ucSlipTime;		/* 定时器给滑差时间 */
					SF_DemandMetering( V_ulDemandCode + ( SV_usActiveRateDemandIntervalTimer_T >> 8 ), NULL, SV_ulActivePower_T);
				}
			}
			
			/*********************** 合相无功需量 ******************************************/
			V_ulDemandCode = SF_GetDemandCodeNum( C_T_ReactiveCodeID );
			
			/* 合相总无功需量计算 */
			if( SV_ucReactiveDemandIntervalTimer_T > 0 )
			{
				SV_ucReactiveDemandIntervalTimer_T--;
				if( SV_ucReactiveDemandIntervalTimer_T == 0 )							/* 计算最大需量 */
				{
					SV_ucReactiveDemandIntervalTimer_T = V_ucSlipTime;					/* 定时器给滑差时间 */
					SF_DemandMetering(V_ulDemandCode, CCurr_ReDemand, SV_ulReactivePower_T);
				}
			}
			
			/* 合相无功费率需量计算 */
			if( ( SV_usReactiveRateDemandIntervalTimer_T & 0xFF ) > 0 )
			{
				SV_usReactiveRateDemandIntervalTimer_T--;
				if( ( SV_usReactiveRateDemandIntervalTimer_T & 0xFF ) == 0 )			/* 计算最大需量 */
				{
					SV_usReactiveRateDemandIntervalTimer_T |= (ushort16)V_ucSlipTime;	/* 定时器给滑差时间 */
					SF_DemandMetering( V_ulDemandCode + ( SV_usActiveRateDemandIntervalTimer_T >> 8 ), NULL, SV_ulReactivePower_T);
				}
			}
			
			/*************************** 分相有功需量 ***************************************/			
			for( V_uci = 0; V_uci < 3; V_uci++)
			{
				V_ulDemandCode = SF_GetDemandCodeNum( C_ActiveCodeIDTable[V_uci] );
				
				/* 分相有功需量计算 */
				if( SV_ucActiveDemandIntervalTimer_SePhase[V_uci] > 0 )
				{
					SV_ucActiveDemandIntervalTimer_SePhase[V_uci]--;
					if( SV_ucActiveDemandIntervalTimer_SePhase[V_uci] == 0 )				/*计算最大需量*/
					{
						SV_ucActiveDemandIntervalTimer_SePhase[V_uci] = V_ucSlipTime;		/*定时器给滑差时间*/
						SF_DemandMetering(V_ulDemandCode, NULL, SV_ulActivePower_SePhase[V_uci]);
					}
				}
								
				V_ulDemandCode = SF_GetDemandCodeNum( C_ReactiveCodeIDTable[V_uci] );				
				/* 分相无功需量计算 */
				if( SV_ucReactiveDemandIntervalTimer_SePhase[V_uci] > 0 )
				{
					SV_ucReactiveDemandIntervalTimer_SePhase[V_uci]--;
					if( SV_ucReactiveDemandIntervalTimer_SePhase[V_uci] == 0 )				/* 计算最大需量 */
					{
						SV_ucReactiveDemandIntervalTimer_SePhase[V_uci] = V_ucSlipTime;		/* 定时器给滑差时间 */
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
函数原型：uchar8 SF_ReadDemand_Com_Single( ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen )
功能描述：读组合需量
输入参数：V_ulOAD：读取的需量的OAD；
          pV_ucDataBuf：读取数据存放的缓存的首地址；
          *pV_usDataLen：读取的数据存放的缓存的最大长度；
输出参数：pV_ucDataBuf：读取的数据的首地址；
          *pV_usDataLen：读取的数据的长度；
返回参数：C_OK表示读取成功，C_IDError表示数据标识码错，C_CRCError数据层CRC错，C_DataLenError表示数据长度错
		 C_NoAccess表示无权限，C_SafeFlagError表示安全标志错，C_Error表示其他错误
调用位置：读取需量
备    注：与SF_ReadDemand_Com函数区别：
		  SF_ReadDemand_Com会判断是否是集合，循环读取；	
		  SF_ReadDemand_Com_Single只能单个读取，读集合	
**************************************************************************************************/
uchar8 SF_ReadDemand_Com_Single( ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen )
{
	uchar8  V_uci, V_ucOAD[C_DataCodeLen];
	uchar8  V_ucBuffer1[CL_DemandAndTime], V_ucBuffer2[CL_DemandAndTime];
	uchar8  V_ucMode, V_ucReturn, V_ucDeriction;
	ushort16 V_usLen, V_usDataEncode;
	ulong32 V_ulTemp, V_ulCodeID;
	
	PF_Ulong32ToBufferX(V_ucOAD, &V_ulOAD, C_DataCodeLen);		/* 将标识码转换为数组 */

	/* 获取读取数据层的数据标识 */
	V_ulTemp = V_ulOAD & 0xFFFFFF00;
	
	for( V_uci = 0; V_uci < C_DemandCodeTableLen; V_uci++ )
	{
		if( C_ComDemandCodeTable[V_uci][0] == V_ulTemp )
		{
			V_ulCodeID = C_ComDemandCodeTable[V_uci][1] | ( V_ulOAD & 0x000000FF );
			break;
		}
	}   
	if(V_uci >= C_DemandCodeTableLen)		/* 没有查找到数据标识码，应答数据表示错 */
	{
		return C_IDError;
	}

	/********************* 读取组合无功最大需量的处理 ***************************/
	/* 首先读取组合无功模式字 */
	V_usDataEncode = 0;
	V_usLen = CLReactive_Com_State1;
	if( ( V_ucOAD[2] & 0xF0 ) == 0x40 )				  /* 组合无功2 */
	{
		if( InF_Read_Data( CReactive_Com_State2, &V_ucMode, &V_usLen, &V_usDataEncode ) != C_OK )
		{
			V_ucMode = C_NormalCom2Mode;
		}
	}
	else											 /* 组合无功1 */
	{
		if( InF_Read_Data( CReactive_Com_State1, &V_ucMode, &V_usLen, &V_usDataEncode ) != C_OK )
		{
			V_ucMode = C_NormalCom1Mode;
		}
	}	
	
	memset( V_ucBuffer1, 0x00, CL_DemandAndTime );
	/*********************** 根据模式字读取相应象限无功最大需量 ************************/
	for( V_uci = 0; V_uci < 4; V_uci++)
	{
		if( ( ( V_ucMode & 0x03 )== 0 ) || ( ( V_ucMode & 0x03 ) == 0x03 ) )		/* 判断模式字是否有效，不加不减 或 又加又减 */
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
				/******* 比较无功需量大小，并保存最大值及其方向 *******/
				if( PF_Campare_Data( V_ucBuffer2, V_ucBuffer1, CL_Demand) == C_GreaterThan )
				{
					PF_CopyDataBytes( V_ucBuffer2, V_ucBuffer1, CL_DemandAndTime);
					if( ( V_uci == 0 ) || ( V_uci == 1 ) )		/* 698组合无功最大需量的正负号根据象限判断，三四象限是负号 */
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
	
	/*************** 最大需量方向、四舍五入处理 *****************/
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
函数原型：uchar8 SF_ReadDemand_Com( ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen )
功能描述：读组合需量
输入参数：V_ulOAD：读取的需量的OAD；
          pV_ucDataBuf：读取数据存放的缓存的首地址；
          *pV_usDataLen：读取的数据存放的缓存的最大长度；
输出参数：pV_ucDataBuf：读取的数据的首地址；
          *pV_usDataLen：读取的数据的长度；
返回参数：C_OK表示读取成功，C_IDError表示数据标识码错，C_CRCError数据层CRC错，C_DataLenError表示数据长度错
		 C_NoAccess表示无权限，C_SafeFlagError表示安全标志错，C_Error表示其他错误
调用位置：读取最大需量及发生时间
备    注：最大需量及发生时间数据格式：4字节HEX（4位小数，单位kW）+7字节时间（date_time_s格式，ss固定00）
**************************************************************************************************/
uchar8 SF_ReadDemand_Com( ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen )
{
	uchar8  V_ucTimes, V_uci, V_ucReturn;
	ushort16 V_usDataLen = 0, V_usDataOffset = 0;
   
    if( ( V_ulOAD & 0x000F00FF ) == 0x00000000 ) 		/* 集合读取 */
    {
    	V_ucTimes = C_RatesNumTol;
		V_ulOAD += C_GetNextRatesDemand;

	}
	else if( ( ( V_ulOAD & 0x000F0000 ) != 0x00000000 ) && ( ( V_ulOAD & 0x000000FF ) == 0x00000000 )  )	/* 分相索引00需量 */
	{
    	V_ucTimes = 1;
		V_ulOAD += C_GetNextRatesDemand;
	}
	else			 /* 单独读取 */
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
函数原型：uchar8 SF_ReadDemand_Other_Single( ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen )
功能描述：读组合需量
输入参数：V_ulOAD：读取的需量的OAD；
          pV_ucDataBuf：读取数据存放的缓存的首地址；
          *pV_usDataLen：读取的数据存放的缓存的最大长度；
输出参数：pV_ucDataBuf：读取的数据的首地址；
          *pV_usDataLen：读取的数据的长度；
返回参数：C_OK表示读取成功，C_IDError表示数据标识码错，C_CRCError数据层CRC错，C_DataLenError表示数据长度错
		 C_NoAccess表示无权限，C_SafeFlagError表示安全标志错，C_Error表示其他错误
调用位置：读取需量
备    注：与SF_ReadDemand_Other函数区别：
		  SF_ReadDemand_Other会判断是否是集合，循环读取；	
		  SF_ReadDemand_Other_Single只能单个读取，读集合	
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
函数原型：uchar8 SF_ReadDemand_Other( ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen )
功能描述：读组合需量
输入参数：V_ulOAD：读取的需量的OAD；
          pV_ucDataBuf：读取数据存放的缓存的首地址；
          *pV_usDataLen：读取的数据存放的缓存的最大长度；
输出参数：pV_ucDataBuf：读取的数据的首地址；
          *pV_usDataLen：读取的数据的长度；
返回参数：C_OK表示读取成功，C_IDError表示数据标识码错，C_CRCError数据层CRC错，C_DataLenError表示数据长度错
		 C_NoAccess表示无权限，C_SafeFlagError表示安全标志错，C_Error表示其他错误
调用位置：读取最大需量及发生时间
备    注：最大需量及发生时间数据格式：4字节HEX（4位小数，单位kW）+7字节时间（date_time_s格式，ss固定00）
**************************************************************************************************/
uchar8 SF_ReadDemand_Other( ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen )
{
	uchar8  V_ucTimes, V_uci, V_ucReturn;
	ushort16 V_usDataLen = 0, V_usDataOffset = 0;
   
    if( ( V_ulOAD & 0x000F00FF ) == 0x00000000 ) 		/* 集合读取 */
    {
    	V_ucTimes = C_RatesNumTol;
		V_ulOAD += C_GetNextRatesDemand;

	}
	else if( ( ( V_ulOAD & 0x000F0000 ) != 0x00000000 ) && ( ( V_ulOAD & 0x000000FF ) == 0x00000000 )  ) /* 分相索引00需量 */
	{
    	V_ucTimes = 1;
		V_ulOAD += C_GetNextRatesDemand;
	}
	else			 /* 单独读取 */
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
函数原型：uchar8 SF_GetDemand_Type(ulong32 V_ulOAD)
功能描述：获取需量数据的类型
输入参数：V_ulOAD为读取的需量OAD
输出参数：无
返回参数：电能数据的类型
		  C_De_OADGetTpye_Com:	组合需量类
		  C_De_OADGetTpye_Other:其他需量
调用位置：读需量接口
备    注：
*******************************************************************************/
uchar8 SF_GetDemand_Type(ulong32 V_ulOAD)
{
	uchar8 V_ucDemandType;
		
	if( ( ( V_ulOAD & 0xFFF00000 ) == 0x10300000 )		/* 组合无功1最大需量 */
     || ( ( V_ulOAD & 0xFFF00000 ) == 0x10400000 ) ) 	/* 组合无功2最大需量 */	
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
函数原型：uchar8 InF_Get_DemandModule(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, ushort16 *pV_usDataEncode)
功能描述：最大需量读取接口函数
输入参数：V_ulOAD:数据标识码；
          pV_ucDataBuf:存放读取数据的缓存的首地址；
          pV_usDataLen:读取数据缓存的最大长度；
          *p_usDataEncode:数据内部编码；
输出参数：pV_ucDataBuf:读取的需量数据的首地址；
          *pV_usDataLen:读取的数据长度；
          p_usDataEncode:数据内部编码；
返回参数：C_OK表示读取成功，C_IDError表示数据标识码错，C_CRCError数据层CRC错，C_DataLenError表示数据长度错
		 C_NoAccess表示无权限，C_SafeFlagError表示安全标志错，C_Error表示其他错误
调用位置：所有需要读取需量数据的模块
备    注：需量组合无功需量有方向，其他需量都是无方向数据。 
		  /---------------------------------------------------------------------------/
			需量模块对外提供的数据格式
		  /---------------------------------------------------------------------------/
		  /-最大需量及发生时间--------------------------------------------------------/
		  *	4字节HEX（4位小数，单位kW）+7字节时间（date_time_s格式，ss固定00）
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
函数原型：void InF_LowPower_DemandInit(void)
功能描述：低功耗下当前需量\1min平均功率清零
输入参数：无
输出参数：无
返回参数：无
调用位置：低功耗处理函数在进入低功耗前调用
备    注：
*******************************************************************************/
void InF_LowPower_DemandInit(void)
{
	SF_Clear_CurrentDemand( );	/*将当前需量清零*/
}

/*******************************************************************************
函数原型：void SF_Clear_CurrentDemand(void)
功能描述：将当前1分钟平均功率清零
输入参数：无
输出参数：无
返回参数：无
调用位置：上电初始化、需量周期重计、低功耗
备    注：
*******************************************************************************/
void SF_Clear_CurrentDemand(void)
{
	uchar8 V_ucData[CL_Demand];
	
	memset(&V_ucData[0], 0x00, CL_Demand);
	InF_Write_Data(C_Msg_DemandMetering, CCurr_AcDemand, &V_ucData[0], CLCurr_AcDemand, C_W_SafeFlag);		/* 当前有功需量 */
	InF_Write_Data(C_Msg_DemandMetering, CCurr_ReDemand, &V_ucData[0], CLCurr_ReDemand, C_W_SafeFlag);		/* 当前无功需量 */
}




