/*******************************************************************************
Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     Display.c
Version:       V1
Author:        
Date:          2014-6-2
Description:   显示处理文件 
---------------------------------------------------------------------------------
History1:      第1次修改
内容1. Date:   20211025
   	   Author: gjc
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
#include "Display.h"

/*******************************************************************************
函数原型：void InF_Display_Init(void)
功能描述：上电初始化接口函数，调度调用。初始化显示模式为全显，显示时间,状态量显示公钥、挂起符号不做处理，
        保持原有状态,初始化背光、跳闸指示灯为全显时间，其余全部状态清零
输入参数：无
输出参数：无
返回参数：无
调用位置：
备    注：
*******************************************************************************/
void InF_Display_Init( void )
{	 
    Str_DisplaySignMesNum *pStr_DisplaySignMesNum;
	ushort16 V_usLen, V_usDataEncode;
    uchar8 V_i, V_j, V_ucALLDisTime;
#if(0)
    /*************************状态字符初始化*******************************/ 
    GV_Str_DisplaySignMesNum_AxisSign[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_AxisSign[0].SourceNo = C_Msg_Communication;

    GV_Str_DisplaySignMesNum_Q1Sign[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_Q1Sign[0].SourceNo = C_Msg_MeterIC;

    GV_Str_DisplaySignMesNum_Q2Sign[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_Q2Sign[0].SourceNo = C_Msg_MeterIC;

    GV_Str_DisplaySignMesNum_Q3Sign[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_Q3Sign[0].SourceNo = C_Msg_MeterIC;

    GV_Str_DisplaySignMesNum_Q4Sign[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_Q4Sign[0].SourceNo = C_Msg_MeterIC;

    GV_Str_DisplaySignMesNum_LSign[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_LSign[0].SourceNo = C_Msg_EnergyMetering;

    GV_Str_DisplaySignMesNum_TSign[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_TSign[0].SourceNo = C_Msg_Deal_MultiRates;

    GV_Str_DisplaySignMesNum_GPRSSign[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_GPRSSign[0].SourceNo = C_Msg_Communication;

    GV_Str_DisplaySignMesNum_GPRSSignalSign1[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_GPRSSignalSign1[0].SourceNo = C_Msg_Communication;

    GV_Str_DisplaySignMesNum_GPRSSignalSign2[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_GPRSSignalSign2[0].SourceNo = C_Msg_Communication;

    GV_Str_DisplaySignMesNum_GPRSSignalSign3[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_GPRSSignalSign3[0].SourceNo = C_Msg_Communication;

    GV_Str_DisplaySignMesNum_GPRSSignalSign4[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_GPRSSignalSign4[0].SourceNo = C_Msg_Communication;

    GV_Str_DisplaySignMesNum_ModuleComSign[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_ModuleComSign[0].SourceNo = C_Msg_Communication;

    GV_Str_DisplaySignMesNum_ComSign[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_ComSign[0].SourceNo = C_Msg_Communication;

    GV_Str_DisplaySignMesNum_ComChannel1Sign[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_ComChannel1Sign[0].SourceNo = C_Msg_Communication;

    GV_Str_DisplaySignMesNum_ComChannel2Sign[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_ComChannel2Sign[0].SourceNo = C_Msg_Communication;

    GV_Str_DisplaySignMesNum_ProgramEnableSign[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_ProgramEnableSign[0].SourceNo = C_Msg_Communication;

    GV_Str_DisplaySignMesNum_HoldUpSign[0].SourceNo = C_Msg_Communication;

    GV_Str_DisplaySignMesNum_PublicKeySign[0].SourceNo = C_Msg_Communication;

    for ( V_i = 0; V_i < GV_Str_DisplaySignMesNum_AlarmSignLen; V_i++ )
    {
        GV_Str_DisplaySignMesNum_AlarmSign[V_i].Timer = C_NotDisplayNiu;
    }
    GV_Str_DisplaySignMesNum_AlarmSign[0].SourceNo = C_Msg_PowerNetworkMonitoring;
    GV_Str_DisplaySignMesNum_AlarmSign[1].SourceNo = C_Msg_Deal_RelayStatus;
    GV_Str_DisplaySignMesNum_AlarmSign[2].SourceNo = C_Msg_BatteryVoltagleMetering;

    GV_Str_DisplaySignMesNum_ReadCardSign[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_ReadCardSign[0].SourceNo = C_Msg_Card;

    GV_Str_DisplaySignMesNum_DoingSign[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_DoingSign[0].SourceNo = C_Msg_Card;

    GV_Str_DisplaySignMesNum_SuccessSign[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_SuccessSign[0].SourceNo = C_Msg_Card;

    GV_Str_DisplaySignMesNum_FailSign[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_FailSign[0].SourceNo = C_Msg_Card;

    for ( V_i = 0; V_i < GV_Str_DisplaySignMesNum_PurchaseSignLen; V_i++ )
    {
        GV_Str_DisplaySignMesNum_PurchaseSign[V_i].Timer = C_NotDisplayNiu;
    }
    GV_Str_DisplaySignMesNum_PurchaseSign[0].SourceNo = C_Msg_Deal_RelayStatus;
    GV_Str_DisplaySignMesNum_PurchaseSign[1].SourceNo = C_Msg_Communication;
    GV_Str_DisplaySignMesNum_PurchaseSign[2].SourceNo = C_Msg_EnergyMetering;

    GV_Str_DisplaySignMesNum_OverdrawSign[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_OverdrawSign[0].SourceNo = C_Msg_EnergyMetering;

    GV_Str_DisplaySignMesNum_RealayOpenSign[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_RealayOpenSign[0].SourceNo = C_Msg_Deal_RelayStatus;

    GV_Str_DisplaySignMesNum_UaSign[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_UaSign[0].SourceNo = C_Msg_PowerNetworkMonitoring;
    GV_Str_DisplaySignMesNum_UaSign[1].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_UaSign[1].SourceNo = C_Msg_MeterIC;

    GV_Str_DisplaySignMesNum_UbSign[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_UbSign[0].SourceNo = C_Msg_PowerNetworkMonitoring;
    GV_Str_DisplaySignMesNum_UbSign[1].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_UbSign[1].SourceNo = C_Msg_MeterIC;

    GV_Str_DisplaySignMesNum_UcSign[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_UcSign[0].SourceNo = C_Msg_PowerNetworkMonitoring;
    GV_Str_DisplaySignMesNum_UcSign[1].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_UcSign[1].SourceNo = C_Msg_MeterIC;

    GV_Str_DisplaySignMesNum_NegativePhaseSign[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_NegativePhaseSign[0].SourceNo = C_Msg_PowerNetworkMonitoring;

    GV_Str_DisplaySignMesNum_IaNegativeSign[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_IaNegativeSign[0].SourceNo = C_Msg_PowerNetworkMonitoring;
    GV_Str_DisplaySignMesNum_IaNegativeSign[1].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_IaNegativeSign[1].SourceNo = C_Msg_MeterIC;

    GV_Str_DisplaySignMesNum_IaSign[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_IaSign[0].SourceNo = C_Msg_PowerNetworkMonitoring;
    GV_Str_DisplaySignMesNum_IaSign[1].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_IaSign[1].SourceNo = C_Msg_MeterIC;

    GV_Str_DisplaySignMesNum_IbNegativeSign[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_IbNegativeSign[0].SourceNo = C_Msg_PowerNetworkMonitoring;
    GV_Str_DisplaySignMesNum_IbNegativeSign[1].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_IbNegativeSign[1].SourceNo = C_Msg_MeterIC;

    GV_Str_DisplaySignMesNum_IbSign[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_IbSign[0].SourceNo = C_Msg_PowerNetworkMonitoring;
    GV_Str_DisplaySignMesNum_IbSign[1].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_IbSign[1].SourceNo = C_Msg_MeterIC;

    GV_Str_DisplaySignMesNum_IcNegativeSign[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_IcNegativeSign[0].SourceNo = C_Msg_PowerNetworkMonitoring;
    GV_Str_DisplaySignMesNum_IcNegativeSign[1].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_IcNegativeSign[1].SourceNo = C_Msg_MeterIC;

    GV_Str_DisplaySignMesNum_IcSign[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_IcSign[0].SourceNo = C_Msg_PowerNetworkMonitoring;
    GV_Str_DisplaySignMesNum_IcSign[1].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_IcSign[1].SourceNo = C_Msg_MeterIC;

    GV_Str_DisplaySignMesNum_TimeTable1Sign[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_TimeTable1Sign[0].SourceNo = C_Msg_Deal_MultiRates;

    GV_Str_DisplaySignMesNum_TimeTable2Sign[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_TimeTable2Sign[0].SourceNo = C_Msg_Deal_MultiRates;

    GV_Str_DisplaySignMesNum_RTCBatterySign[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_RTCBatterySign[0].SourceNo = C_Msg_BatteryVoltagleMetering;

    GV_Str_DisplaySignMesNum_PowerBatterySign[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_PowerBatterySign[0].SourceNo = C_Msg_BatteryVoltagleMetering;

    GV_Str_DisplaySignMesNum_HoardingSign[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_HoardingSign[0].SourceNo = C_Msg_Card;

    GV_Str_DisplaySignMesNum_HoardingSign[1].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_HoardingSign[1].SourceNo = C_Msg_Communication;	 

    GV_Str_DisplaySignMesNum_CurrentStep[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_CurrentStep[0].SourceNo = C_Msg_Deal_MultiRates;

    GV_Str_DisplaySignMesNum_BakStep[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_BakStep[0].SourceNo = C_Msg_Deal_MultiRates;

    for ( V_i = 0; V_i < GV_Str_DisplaySignMesNum_BackLEDLen; V_i++ )
    {
        GV_Str_DisplaySignMesNum_BackLED[V_i].Timer = C_NotDisplayNiu;
    }
    GV_Str_DisplaySignMesNum_BackLED[0].SourceNo = C_Msg_PowerNetworkMonitoring;
    GV_Str_DisplaySignMesNum_BackLED[1].SourceNo = C_Msg_Communication;
    GV_Str_DisplaySignMesNum_BackLED[2].SourceNo = C_Msg_Deal_RelayStatus;
    GV_Str_DisplaySignMesNum_BackLED[3].SourceNo = C_Msg_BatteryVoltagleMetering;
    GV_Str_DisplaySignMesNum_BackLED[4].SourceNo = C_Msg_Card;
    GV_Str_DisplaySignMesNum_BackLED[5].SourceNo = C_Msg_Display;

    for ( V_i = 0; V_i < GV_Str_DisplaySignMesNum_WarnOutPutLen; V_i++ )
    {
        GV_Str_DisplaySignMesNum_WarnOutPut[V_i].Timer = C_NotDisplayNiu;
    }
    GV_Str_DisplaySignMesNum_WarnOutPut[0].SourceNo = C_Msg_PowerNetworkMonitoring;
    GV_Str_DisplaySignMesNum_WarnOutPut[1].SourceNo = C_Msg_Deal_RelayStatus;
    GV_Str_DisplaySignMesNum_WarnOutPut[2].SourceNo = C_Msg_BatteryVoltagleMetering;
    GV_Str_DisplaySignMesNum_WarnOutPut[3].SourceNo = C_Msg_Communication;

    for ( V_i = 0; V_i < GV_Str_DisplaySignMesNum_BeeperLen; V_i++ )
    {
        GV_Str_DisplaySignMesNum_Beeper[V_i].Timer = C_NotDisplayNiu;
    }
    GV_Str_DisplaySignMesNum_Beeper[0].SourceNo = C_Msg_PowerNetworkMonitoring;
    GV_Str_DisplaySignMesNum_Beeper[1].SourceNo = C_Msg_Deal_RelayStatus;
    GV_Str_DisplaySignMesNum_Beeper[2].SourceNo = C_Msg_BatteryVoltagleMetering;
    GV_Str_DisplaySignMesNum_Beeper[3].SourceNo = C_Msg_Card;

    GV_Str_DisplaySignMesNum_RelayStatusLED[0].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_RelayStatusLED[0].SourceNo = C_Msg_Deal_RelayStatus;
    GV_Str_DisplaySignMesNum_RelayStatusLED[1].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_RelayStatusLED[1].SourceNo = C_Msg_Display;
    GV_Str_DisplaySignMesNum_RelayStatusLED[2].Timer = C_NotDisplayNiu;
    GV_Str_DisplaySignMesNum_RelayStatusLED[2].SourceNo = C_Msg_Communication;
#endif
    
    SF_TimingFreshSignMesNum();/*消息源初始化*/
    
    GV_CardDisSign = C_NoCardDis;/*非插卡显示状态*/
	 
    GV_KillZeroNum = 0;/*不灭零*/
    V_usLen = CLPowerOn_Dis_All_Time;
    V_i = InF_Read_Data(CPowerOn_Dis_All_Time, &V_ucALLDisTime, &V_usLen, &V_usDataEncode);/*取数据层上电全显时间*/
    /*PF_BCDtoHexBytes(&V_ucALLDisTime,&V_Hex,1); */       /*BCD转hex*/
    /*V_ucALLDisTime=(uchar8)V_Hex;*/
    V_ucALLDisTime <<= 1;   /*内部是500ms基准*/

    if ( ( C_OK != V_i ) || ( 0x00 == V_ucALLDisTime ) )  /*读数据错误*/
    {
        V_ucALLDisTime = C_DefaultDisplayTime5s;   /*取默认全屏显示时间，5s*/
    }
	 
    for ( V_i = 0; V_i < GV_Str_DisplaySignLen; V_i++ )     /*状态指示字符，背光、指示灯、报警继电器处理*/
    {
        pStr_DisplaySignMesNum = (Str_DisplaySignMesNum *)(GV_Str_DisplaySign[V_i].PStr_DisplaySignMesNum);

        if ( C_RelayStatusLED == GV_Str_DisplaySign[V_i].StateNum )    /*跳闸指示灯*/
        {
            for ( V_j = 0; V_j < GV_Str_DisplaySign[V_i].Str_DisplaySignMesNumLen; V_j++ )
            {
                if ( C_Msg_Display == pStr_DisplaySignMesNum[V_j].SourceNo )
                {
                    pStr_DisplaySignMesNum[V_j].Timer = V_ucALLDisTime;    
                    break;	 	 	       	   	  
                }
            } 
        }
        else
        {
            if ( C_BackLED == GV_Str_DisplaySign[V_i].StateNum )    /*背光灯*/
            {
                for ( V_j = 0; V_j < GV_Str_DisplaySign[V_i].Str_DisplaySignMesNumLen; V_j++ )
                {
                    pStr_DisplaySignMesNum[V_j].Timer = V_ucALLDisTime;
                }
            }
            else
            {
                if ( ( C_PublicKeySign == GV_Str_DisplaySign[V_i].StateNum ) 
                  || ( C_HoldUpSign == GV_Str_DisplaySign[V_i].StateNum ) )    /*公钥、身份认证挂起，不做处理保持原有状态*/
                {
                    continue;
                }
                else    /*其他状态变量初始化为不显*/
                {
                    for ( V_j = 0; V_j < GV_Str_DisplaySign[V_i].Str_DisplaySignMesNumLen; V_j++ )
                    {
                        pStr_DisplaySignMesNum[V_j].Timer = C_NotDisplayNiu;
                    } 
                }
            }	
        }
    }
		 
    GV_Str_DisplayFlag.CodeID = C_ALLScreenDisplayDi;       /*初始化显示状态标识*/
    GV_Str_DisplayFlag.P_ChieseTableNo = C_NULL;
    GV_Str_DisplayFlag.ChieseTableLineNo = 0;
    GV_Str_DisplayFlag.SV_DisplayDataOff = 0;
    GV_Str_DisplayFlag.Screen = 1;

    GV_Str_DisplayFlag.SV_usDisplayTimer = V_ucALLDisTime;
    GV_Str_DisplayFlag.SV_ucDisplayMode = C_ALLScreenDisplay;
    GV_Str_DisplayFlag.ParaNum = 0xFF;
    GV_Str_DisplayFlag.ParityTimer = 0x00;

    SF_DisAllData();        	  /*显示缓存置1，内部判断是否需要全屏显示*/
               
    InF_WriteLCD(&GV_ucDisplayData[0], C_LCDLen, C_Notkillzero);  /*底层驱动显示*/
    InF_SwithPeripherals(C_TripLed, C_On);      /*跳闸指示灯*/
    InF_SwithPeripherals(C_BackLight, C_On);    /*背光灯 */
    GV_TimingInitSignTime = 0;                   /*定时刷新状态字符数据源定时器初始化*/ 
    GV_ShutBackLEDTime = 0;                      /*上电背光点亮闭锁定时器*/  
    /*GV_PowerOnChangeScreenFlag = 0;*/          /*换屏标志*/

    for ( V_i = 0; V_i < CLChargeBal_BCD; V_i++ )/*剩余透支金额初始化*/
    {
        GV_RemainMoney[0][V_i] = 0;
        GV_RemainMoney[1][V_i] = 0;		
    }

    InF_Clear_Engry_BorrowPoint();
}
/*******************************************************************************
函数原型：uchar8 InF_LocalAndRemoteMeterDiJudge( ulong32 V_ulDi )
功能描述：根据表型判断当前标识码是否支持本地、远程表；远程表标识码本地表都有，所以当表型为远程表时进行标识码判断
输入参数：ulong32 V_ulDi：待判断标识码
输出参数：无
返回参数：uchar8,C_OK:表示支持该标识码；C_IDError：表示不支持该标识码
调用位置：
备    注：
*******************************************************************************/                        
uchar8 InF_LocalAndRemoteMeterDiJudge( ulong32 V_ulDi )
{
    uchar8 V_uci;

    if(C_Meter_Type != C_L_SmartMeter)  /*远程表或智能表*/
    {
        for ( V_uci = 0; V_uci < GV_LocalMeterDI_Len; V_uci++ )
        {
            if ( 0x02 == GV_Str_LocalMeterDI[V_uci].CompByteNum )
            {
                if ( ( V_ulDi & 0xFFFF0000 ) == ( GV_Str_LocalMeterDI[V_uci].LocalMeterDI & 0xFFFF0000 ) )
                {
                    break;
                }
            }
            else
            {
                if ( 0x03 == GV_Str_LocalMeterDI[V_uci].CompByteNum )
                {
                    if ( ( V_ulDi & 0xFFFFFF00 ) == ( GV_Str_LocalMeterDI[V_uci].LocalMeterDI & 0xFFFFFF00 ) )
                    {
                        break;
                    }	 	  	 	  	 
                }
                else  /*4位全比较*/
                {
                    if ( V_ulDi == GV_Str_LocalMeterDI[V_uci].LocalMeterDI )
                    {
                        break;
                    }
                }	 	  	 	  
            }
        }
        if ( V_uci < GV_LocalMeterDI_Len )
        {
            return C_IDError;
        }
        else
        {
            return C_OK;
        }	 	  	
    }
    else    /*本地表*/
    {
        return C_OK;
    }
}
/*******************************************************************************
函数原型：void InF_Display_WakeUpInit(void) 
功能描述：停电唤醒初始化接口函数，调度调用。显示模式为自动循显方式，除公钥、闭锁保持原有状态外，其余各状态定时器全部清零
输入参数：无
输出参数：无
返回参数：
调用位置：
备    注：
*******************************************************************************/                                    
void InF_Display_WakeUpInit( void )
{	 
    Str_DisplaySignMesNum *pStr_DisplaySignMesNum;
    ushort16  V_usPowerOffDisTime;
	ushort16 V_usLen, V_usDataEncode;
    ushort16 V_usALLDisTime;
    uchar8 V_uci,V_ucj, V_ucDisScreenNum;
    uchar8 V_ucALLDisTime[2];
    /*ulong32 V_Hex;*/
    /*uchar8 V_AutoDisNum[5];*/

    GV_CardDisSign = C_NoCardDis;   /*非插卡显示状态*/

    GV_KillZeroNum = 0;         /*不灭零*/
    GV_PowerOffDisState = C_ContinueReceive;         /*低功耗显示状态，初始化为显示*/

    V_usLen = CLPer_Dis_Screen_Time;
    V_uci = InF_Read_Data(CPer_Dis_Screen_Time, &V_ucALLDisTime[0], &V_usLen, &V_usDataEncode);/*取数据层自动循显时间*/
    /*PF_BCDtoHexBytes(&V_ucALLDisTime,&V_Hex,1);*/        /*BCD转hex*/
    /*V_ucALLDisTime=(uchar8)V_Hex;*/
    PF_Buffer2ToUshort16(&V_ucALLDisTime[0], &V_usALLDisTime);
    V_usALLDisTime <<= 1;   /*内部是500ms基准*/

    if ( (C_OK != V_uci) || (0x00 == V_usALLDisTime) )  /*读数据错误*/
    {
        V_usALLDisTime = C_DefaultDisplayTime5s;   /*取默认全屏显示时间，5s*/
    }
    GV_usPowerOffAutoDisScreenTime = V_usALLDisTime;   

    V_usLen = CLAuto_Dis_Screen_Num;
    V_uci = InF_Read_Data(CAuto_Dis_Screen_Num, &V_ucDisScreenNum, &V_usLen, &V_usDataEncode);/*取数据层自动循显屏数*/
    /*PF_BCDtoHexBytes(&V_ucDisScreenNum,&V_Hex,1); */             /*BCD转hex*/
    /*V_ucDisScreenNum=(uchar8)V_Hex;	*/
    if ( (C_OK != V_uci) || (0x00 == V_ucDisScreenNum) )
    {
        V_ucDisScreenNum = C_DefaultDisScreenNum;                   /*取默认显示屏数*/	    	 
    }	 
    GV_PowerOffAutoDisScreenNum = V_ucDisScreenNum;

    V_usPowerOffDisTime = V_usALLDisTime*V_ucDisScreenNum;           /*1个循显周期，显示时间*/

    for ( V_uci = 0; V_uci < GV_Str_DisplaySignLen; V_uci++ )     /*状态指示字符处理*/
    {
        pStr_DisplaySignMesNum = (Str_DisplaySignMesNum *)GV_Str_DisplaySign[V_uci].PStr_DisplaySignMesNum;
        if ( (C_PublicKeySign == GV_Str_DisplaySign[V_uci].StateNum)
          || (C_HoldUpSign == GV_Str_DisplaySign[V_uci].StateNum) )    /*公钥、身份认证挂起，不做处理保持原有状态*/
        {
            continue;
        }
        else    /*其他状态定时器清零*/
        {
            for ( V_ucj=0; V_ucj<GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen; V_ucj++ )
            {
                pStr_DisplaySignMesNum[V_ucj].Timer = C_NotDisplayNiu;
            }
        }	 	 
    }

    GV_Str_DisplayFlag.P_ChieseTableNo = C_NULL;
    GV_Str_DisplayFlag.ChieseTableLineNo = 0;
    GV_Str_DisplayFlag.SV_DisplayDataOff = 0;

    GV_Str_DisplayFlag.SV_usDisplayTimer = V_usPowerOffDisTime;    /*初始化显示结构体,1个循显周期显示时间*/
    GV_Str_DisplayFlag.SV_ucDisplayMode = C_AutoDisplay;
    GV_Str_DisplayFlag.Screen = 0x00;                      /*统一在低功耗500ms中处理  */
    GV_Str_DisplayFlag.ParityTimer = 0x00;
   
#if(0)	 
    V_usLen = CLAuto_Dis_1ScreenCode;
    V_uci = InF_Read_Data(CAuto_Dis_1ScreenCode, &V_AutoDisNum[0], &V_usLen, &V_usDataEncode);/*取数据层自动循显显示第1屏显示代码*/
    PF_Buffer4ToUlong32(&V_AutoDisNum[0], &V_Hex, 4);              /*标识码转换*/

    if ( (C_OK != V_uci) && (C_CrcErr_DataZero != V_uci) )
    {
        GV_Str_DisplayFlag.CodeID = C_DefaultDisDi;
        GV_Str_DisplayFlag.ParaNum = 0x00;
    }	 	 
    else
    {
        GV_Str_DisplayFlag.CodeID = V_Hex;
        V_uci = InF_Display_JudgeIDActive(V_Hex, V_AutoDisNum[4]);     /*判断DI及显示屏是否合法*/
        if ( C_OK != V_uci )
        {
            GV_Str_DisplayFlag.CodeID = C_DefaultDisDi;
            V_AutoDisNum[4] = 0x00;
        }
        GV_Str_DisplayFlag.ParaNum = V_AutoDisNum[4];	    	  
    }
    SF_FindDisChieseTableNo();        /*查找显示全局结构体，DI对应的汉字表格及行号*/

    SF_Disply();   /*在500ms中显示*/
#endif
}
/*******************************************************************************
函数原型：uchar8 InF_GetPowerOffDisplayState(void) 
功能描述：低功耗唤醒显示模式下，供主调度调用，获取显示当前状态(显示模块内部判断，显示时间是否到：1个循显周期或无
		 按键操作30s，模块内部关显示)。调度根据该状态判断，是否继续给显示发500ms消息
输入参数：无 
输出参数：无
返回参数：借用通讯宏定义C_ContinueReceive：继续显示状态；C_AbortReceive：显示关闭状态
调用位置：
备    注：
*******************************************************************************/                                     
uchar8 InF_GetPowerOffDisplayState( void )
{
    uchar8 V_ucPowerState;

    V_ucPowerState = InF_ReadPowerState();     /*获取当前电表工作状态，有电、没电*/

    if ( C_PowerOn == V_ucPowerState )           /*有电*/
    {
        GV_PowerOffDisState = C_ContinueReceive;/*设置为显示模式*/
    }

    return  GV_PowerOffDisState;
}
/*******************************************************************************
函数原型：void SF_PowerOffDisplay500msTimer(void)
功能描述：500ms定时器处理，循显一个周期关闭显示，或按键显示，30s无操作关闭显示。进行状态字符处理，同时返回设置当前
		显示状态，是显示关闭还是继续显示，C_AbortReceive供主调度用
输入参数：无
输出参数：无
返回参数：
调用位置：
备    注：时间到关闭显示
*******************************************************************************/                                 
void  SF_PowerOffDisplay500msTimer( void )
{
    Str_DisplaySignMesNum *pStr_DisplaySignMesNum;
    ulong32 V_ulDi, V_ulRelatedDi;
	ushort16 V_usLen, V_usDataEncode;
    uchar8 V_uci, V_ucj;
    uchar8 V_ucAutoDisNum[CLAuto_Dis_1ScreenCode];

    if ( 0 == GV_Str_DisplayFlag.SV_usDisplayTimer )   /*显示定时器为零，关显示*/
    {
#if 0	/*test*/
        InF_SwitchOffLCD();
#endif
        GV_PowerOffDisState = C_AbortReceive;      /*关闭显示*/  
	}
    else     /*显示时间不为零*/
    {
        if ( C_AutoDisplay == GV_Str_DisplayFlag.SV_ucDisplayMode )    /*自动循显模式*/
        {
            if ( 0x00 == (GV_Str_DisplayFlag.SV_usDisplayTimer%GV_usPowerOffAutoDisScreenTime) )   /*是否换屏*/
            {
                GV_Str_DisplayFlag.Screen++;                            /*显示屏数＋1*/

                if ( GV_Str_DisplayFlag.Screen > GV_PowerOffAutoDisScreenNum )	   /*自动轮显屏数,循显1个周期*/
                {
                    /*InF_SwitchOffLCD(); */                       /*关闭显示*/
                    GV_PowerOffDisState=C_AbortReceive;        /*关闭显示*/
                }
                else             /*循显*/
                {
                    V_usLen = CLAuto_Dis_1ScreenCode;
                    V_ulDi = CAuto_Dis_1ScreenCode&0xFFFFFF00;
                    V_ulDi = V_ulDi|GV_Str_DisplayFlag.Screen;
#if(0)
                    InF_Read_Data(V_ulDi,&V_ucAutoDisNum[0], &V_usLen, &V_usDataEncode);/*取数据层自动循显显示第GV_Str_DisplayFlag.Screen屏显示代码*/
                    PF_Buffer4ToUlong32(&V_ucAutoDisNum[0], &V_ulDi, 4);              /*标识码转换*/

                    while ( InF_LocalAndRemoteMeterDiJudge(V_ulDi) )   /*标识码支持或1个循环完毕退出循环*/
                    {
                        GV_Str_DisplayFlag.Screen++;
                        if ( GV_Str_DisplayFlag.Screen > GV_PowerOffAutoDisScreenNum )	   /*自动轮显屏数,循显1个周期*/
                        {
                            /*InF_SwitchOffLCD(); */                       /*关闭显示*/
                            GV_PowerOffDisState = C_AbortReceive;        /*关闭显示*/
                            break;
                        }
                        V_usLen = CLAuto_Dis_1ScreenCode;
                        V_ulDi = CAuto_Dis_1ScreenCode&0xFFFFFF00;
                        V_ulDi = V_ulDi|GV_Str_DisplayFlag.Screen;
                        InF_Read_Data(V_ulDi,&V_ucAutoDisNum[0], &V_usLen, &V_usDataEncode);/*取数据层自动循显显示第GV_Str_DisplayFlag.Screen屏显示代码*/
                        PF_Buffer4ToUlong32(&V_ucAutoDisNum[0], &V_ulDi, 4);              /*标识码转换*/
                        PF_Buffer4ToUlong32(&V_ucAutoDisNum[C_DisRelatedOffset], &V_ulRelatedDi, 4);              /*标识码转换*/

                    }	 	  	  	  	 

                    V_usLen = CLAuto_Dis_1ScreenCode;
                    V_ulDi = CAuto_Dis_1ScreenCode&0xFFFFFF00;
                    V_ulDi = V_ulDi|GV_Str_DisplayFlag.Screen;

                    V_uci = InF_Read_Data(V_ulDi, &V_ucAutoDisNum[0], &V_usLen, &V_usDataEncode);/*取数据层自动循显显示第GV_Str_DisplayFlag.Screen屏显示代码*/
                    PF_Buffer4ToUlong32(&V_ucAutoDisNum[0], &V_ulDi, 4);              /*标识码转换*/
                    PF_Buffer4ToUlong32(&V_ucAutoDisNum[C_DisRelatedOffset], &V_ulRelatedDi, 4);              /*标识码转换*/

                    if ( (C_OK != V_uci) && (C_CrcErr_DataZero != V_uci) )
                    {
                        GV_Str_DisplayFlag.CodeID = C_DefaultDisDi;
                        GV_Str_DisplayFlag.Related_CodeID = C_DefaultDisDiRelated;
                        GV_Str_DisplayFlag.ParaNum = 0x00;
                    }	              	 
                    else
                    {
                        V_uci = InF_Display_JudgeIDActive(V_ulDi, V_ulRelatedDi, V_ucAutoDisNum[8]);
                        if ( C_OK != V_uci )
                        {
                            GV_Str_DisplayFlag.CodeID = C_DefaultDisDi;
                            GV_Str_DisplayFlag.Related_CodeID = C_DefaultDisDiRelated;
                            GV_Str_DisplayFlag.ParaNum = 0x00;
                        }
                        else
                        {
                            GV_Str_DisplayFlag.CodeID = V_ulDi;
                            GV_Str_DisplayFlag.Related_CodeID = V_ulRelatedDi;
                            GV_Str_DisplayFlag.ParaNum = V_ucAutoDisNum[C_DisScreenNumOffset];
                        } 
                    }
#endif
                    V_uci = InF_Read_Data(V_ulDi, &V_ucAutoDisNum[0], &V_usLen, &V_usDataEncode);/*取数据层自动循显显示第GV_Str_DisplayFlag.Screen屏显示代码*/
                    PF_Buffer4ToUlong32(&V_ucAutoDisNum[0], &V_ulDi, 4);        /*标识码转换*/
                    PF_Buffer4ToUlong32(&V_ucAutoDisNum[C_DisRelatedOffset], &V_ulRelatedDi, 4);              /*标识码转换*/
                    if ( ( (C_OK != V_uci) && (C_CrcErr_DataZero != V_uci) )
                      || (InF_LocalAndRemoteMeterDiJudge(V_ulDi) == C_IDError)
                      || (InF_Display_JudgeIDActive(V_ulDi,V_ulRelatedDi,V_ucAutoDisNum[8]) != C_OK) )
                    {
                        GV_Str_DisplayFlag.CodeID = C_DefaultDisDi;
                        GV_Str_DisplayFlag.Related_CodeID = C_DefaultDisDiRelated;
                        GV_Str_DisplayFlag.ParaNum = 0x00;
                    }
                    else
                    {
                        GV_Str_DisplayFlag.CodeID = V_ulDi;
                        GV_Str_DisplayFlag.Related_CodeID  = V_ulRelatedDi;
                        GV_Str_DisplayFlag.ParaNum = V_ucAutoDisNum[C_DisScreenNumOffset];
                    }
                    SF_FindDisChieseTableNo();        /*查找显示全局结构体，DI对应的汉字表格及行号*/
                }
            }
            else         /*安全性判断*/            
            {
                V_uci = InF_Display_JudgeIDActive(GV_Str_DisplayFlag.CodeID, GV_Str_DisplayFlag.Related_CodeID, GV_Str_DisplayFlag.ParaNum);/*安全性判断*/
                if ( C_OK != V_uci )
                {
                    GV_Str_DisplayFlag.CodeID = C_DefaultDisDi;
                    GV_Str_DisplayFlag.Related_CodeID = C_DefaultDisDiRelated;
                    GV_Str_DisplayFlag.ParaNum = 0x00;
                    SF_FindDisChieseTableNo();        /*查找显示全局结构体，DI对应的汉字表格及行号*/
                } 	  
            }
        }
        else         /*安全性判断*/             
        {
            V_uci = InF_Display_JudgeIDActive(GV_Str_DisplayFlag.CodeID, GV_Str_DisplayFlag.Related_CodeID, GV_Str_DisplayFlag.ParaNum);/*安全性判断*/
            if ( C_OK != V_uci )
            {
                GV_Str_DisplayFlag.CodeID = C_DefaultDisDi;
                GV_Str_DisplayFlag.Related_CodeID = C_DefaultDisDiRelated;
                GV_Str_DisplayFlag.ParaNum = 0x00;
                SF_FindDisChieseTableNo();        /*查找显示全局结构体，DI对应的汉字表格及行号*/
            } 	  
        }
        GV_Str_DisplayFlag.SV_usDisplayTimer--;	    
    }
	 
    GV_Str_DisplayFlag.ParityTimer++;
    if( GV_Str_DisplayFlag.ParityTimer >= 4 )   /*奇偶定时器*/
    {
        GV_Str_DisplayFlag.ParityTimer = 0;	 	 
    }
    for ( V_uci = 0; V_uci < GV_Str_DisplaySignLen; V_uci++ )     /*状态指示字符，背光、指示灯、报警继电器处理*/
    {
        pStr_DisplaySignMesNum = (Str_DisplaySignMesNum *)GV_Str_DisplaySign[V_uci].PStr_DisplaySignMesNum;

        for ( V_ucj = 0; V_ucj < GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen; V_ucj++)
        {
            if ( (C_AlwaysDisplayNiu == pStr_DisplaySignMesNum[V_ucj].Timer)
              || (C_TwinkleDisplayNiu == pStr_DisplaySignMesNum[V_ucj].Timer)
              || (C_NotDisplayNiu == pStr_DisplaySignMesNum[V_ucj].Timer) )     /*常显、闪烁、不显*/
            {
                continue;
            }
            else
            {
                pStr_DisplaySignMesNum[V_ucj].Timer--;
            }
        }
    }	 	 
}
/*******************************************************************************
函数原型：void SF_DisplayBorrowPoint_Rectify(void)
功能描述：借位显示矫正处理，防止误写入借位位数。
	     循显第1屏，判断存储小数位数和矫正标志比较，
		 不相等，矫正和小数位数均清零，重新判断；
		 相等，矫正标志清0。
输入参数：无
输出参数：无
返回参数：无
调用位置：显示
备    注：
*******************************************************************************/
void SF_DisplayBorrowPoint_Rectify( void )
{
	ushort16 V_usLen, V_usDataEncode;
    uchar8 V_ucReturn1, V_ucReturn2, V_ucData, V_ucCorrectFlag = C_Error;
	uchar8 V_ucDisplayBorrowPoint_Flag;
	uchar8 V_ucDisplayBorrowPoint_RecFlag;
	
	V_usLen = CLDisplayBorrowPoint;
    V_ucReturn1 = InF_Read_Data(CDisplayBorrowPoint, &V_ucDisplayBorrowPoint_Flag, &V_usLen, &V_usDataEncode); 
	
	V_usLen = CLDisplayBorrowPoint_RecFlag;
    V_ucReturn2 = InF_Read_Data(CDisplayBorrowPoint_RecFlag, &V_ucDisplayBorrowPoint_RecFlag, &V_usLen, &V_usDataEncode); 
	
	if ( (V_ucReturn1 == C_OK) && (V_ucReturn2 == C_OK) )
	{
		if ( ( V_ucDisplayBorrowPoint_Flag == V_ucDisplayBorrowPoint_RecFlag )
		  && ( V_ucDisplayBorrowPoint_Flag < 5 ) )
		{
			V_ucCorrectFlag = C_OK;
		}
	}

	if( V_ucCorrectFlag == C_OK )
	{
		V_ucData = C_EnBorrowPoint_0;
		InF_Write_Data(C_Msg_Display, CDisplayBorrowPoint_RecFlag, &V_ucData, CLDisplayBorrowPoint_RecFlag, C_W_SafeFlag);
	}
	else
	{
		V_ucData = C_EnBorrowPoint_0;
    	InF_Write_Data(C_Msg_Display, CDisplayBorrowPoint, &V_ucData, CLDisplayBorrowPoint, C_W_SafeFlag);
    	InF_Write_Data(C_Msg_Display, CDisplayBorrowPoint_RecFlag, &V_ucData, CLDisplayBorrowPoint_RecFlag, C_W_SafeFlag);
	}
}
/*******************************************************************************
函数原型：void SF_PowerOnDisplay500msTimer(void)
功能描述：500ms定时器处理，显示状态切换及状态字符定时器处理，每500ms显示统一刷新。有电情况下，调用
		跳闸指示灯，标识码不为全FF时(液晶查看全屏显示),显示消息跳闸指示灯定时器清零(在500ms查询中完成) 
输入参数：无
输出参数：无
返回参数：
调用位置：
备    注：
*******************************************************************************/                                      
void SF_PowerOnDisplay500msTimer( void )
{
    Str_DisplaySignMesNum *pStr_DisplaySignMesNum;
    ulong32 /*V_Hex,*/V_ulDi, V_ulRelatedDI;
	ushort16 V_usLen, V_usDataEncode;
    ushort16 V_usDisTime;
    uchar8  V_ucDisTime[2], V_ucDisScreenNum, V_uci, V_ucj;
	uchar8  V_ucAutoDisNum[CLAuto_Dis_1ScreenCode];
	/*uchar8  V_DisSign, V_DisScreenNumTemp;*/
   
	/*V_DisSign = 0x55;*/    /*标识码有效性判断标志*/	 

	GV_TimingInitSignTime++;
	if(GV_TimingInitSignTime > C_TimingInitSignTime10min)  /*定时到，刷新状态字符消息源*/
	{
		GV_TimingInitSignTime = 0;
		SF_TimingFreshSignMesNum();
	}	 
	 
	GV_ShutBackLEDTime++;                                /*定时器到，背光点亮，进行电压判断*/ 
	if(GV_ShutBackLEDTime >= C_ShutBackLEDTime5s)
    {
        GV_ShutBackLEDTime = C_ShutBackLEDTime5s;
	}
	 
	GV_Str_DisplayFlag.ParityTimer++;
	if ( GV_Str_DisplayFlag.ParityTimer >= 4 )   			/*奇偶定时器*/
	{
        GV_Str_DisplayFlag.ParityTimer = 0;	 	 
	}
	 	 
    if ( 0 == GV_Str_DisplayFlag.SV_usDisplayTimer )   	/*显示定时器为零，切换*/
	{
		V_usLen = CLPer_Dis_Screen_Time;
	    V_uci = InF_Read_Data(CPer_Dis_Screen_Time, &V_ucDisTime[0], &V_usLen, &V_usDataEncode);			/*取数据层自动循显时间*/
	    /*PF_BCDtoHexBytes(&V_ucDisTime, &V_Hex, 1);*/        /*BCD转hex*/
	    /*V_ucDisTime = (uchar8)V_Hex;*/
        PF_Buffer2ToUshort16(&V_ucDisTime[0], &V_usDisTime);
	    V_usDisTime <<= 1;   	    						/*内部是500ms基准*/
	    	    
	    if ( (C_OK != V_uci) || (0x00 == V_usDisTime) )
	    {
	    	V_usDisTime = C_DefaultDisplayTime5s;   		/*取默认全屏显示时间，5s*/	    	 
	    }
	    
	    V_usLen = CLAuto_Dis_Screen_Num;
	    V_uci = InF_Read_Data(CAuto_Dis_Screen_Num, &V_ucDisScreenNum, &V_usLen, &V_usDataEncode);	/*取数据层自动循显屏数*/
	    /*PF_BCDtoHexBytes(&V_ucDisScreenNum, &V_Hex, 1); */   			/*BCD转hex*/
	    /*V_ucDisScreenNum = (uchar8)V_Hex;*/
	    
	    if ( (C_OK != V_uci) || (0x00 == V_ucDisScreenNum) )
	    {
			V_ucDisScreenNum = C_DefaultDisScreenNum;       			/*取默认显示屏数*/    	 
	    }

	    GV_Str_DisplayFlag.SV_usDisplayTimer = V_usDisTime;  			/*自动轮显时间*/
	    if ( C_AutoDisplay == GV_Str_DisplayFlag.SV_ucDisplayMode )    /*自动循显模式*/
	    {
			GV_Str_DisplayFlag.Screen++;                            /*显示屏数＋1*/
            if ( GV_Str_DisplayFlag.Screen > V_ucDisScreenNum )	        /*自动轮显屏数,循显1个周期*/
            {
                GV_Str_DisplayFlag.Screen = 0x01;
                SF_DisplayBorrowPoint_Rectify();
            }
	    }
	    else
	    {
            GV_Str_DisplayFlag.SV_ucDisplayMode = C_AutoDisplay;    /*设置为自动循显模式*/
            GV_Str_DisplayFlag.Screen = 0x01;                       /*第一屏*/
	    }
	    
	    /*V_DisScreenNumTemp = GV_Str_DisplayFlag.Screen;*/  			 /*表型标识码是否支持判断*/
	   
	    V_usLen = CLAuto_Dis_1ScreenCode;
	    V_ulDi = CAuto_Dis_1ScreenCode & 0xFFFFFF00;
	    V_ulDi = V_ulDi | GV_Str_DisplayFlag.Screen;	    
	    V_uci = InF_Read_Data(V_ulDi, &V_ucAutoDisNum[0], &V_usLen, &V_usDataEncode);	/*取数据层自动循显显示第GV_Str_DisplayFlag.Screen屏显示代码*/
	    PF_Buffer4ToUlong32(&V_ucAutoDisNum[0], &V_ulDi, 4);            /*标识码转换*/
#if(0)
		while ( InF_LocalAndRemoteMeterDiJudge(V_ulDi) )   				/*标识码支持或1个循环完毕退出循环*/
		{
			GV_Str_DisplayFlag.Screen++;
			if ( GV_Str_DisplayFlag.Screen > V_ucDisScreenNum )          /*超过最大键显屏数*/
			{
				GV_Str_DisplayFlag.Screen = 1;
				SF_DisplayBorrowPoint_Rectify( );
			}
			
			if ( V_DisScreenNumTemp == GV_Str_DisplayFlag.Screen )      /*循环1个周期*/
			{
				V_DisSign = 0xaa;
				break;
			}
			
            V_usLen = CLAuto_Dis_1ScreenCode;
            V_ulDi = CAuto_Dis_1ScreenCode&0xFFFFFF00;
            V_ulDi = V_ulDi|GV_Str_DisplayFlag.Screen;	    
            V_uci = InF_Read_Data(V_ulDi, &V_ucAutoDisNum[0], &V_usLen, &V_usDataEncode);	/*取数据层自动循显显示第GV_Str_DisplayFlag.Screen屏显示代码*/
            PF_Buffer4ToUlong32(&V_ucAutoDisNum[0], &V_ulDi, 4);          /*标识码转换*///
		}	 	  	  	  	 	 	  	 
	    	   
	    V_usLen = CLAuto_Dis_1ScreenCode;
	    V_ulDi = CAuto_Dis_1ScreenCode&0xFFFFFF00;
	    V_ulDi = V_ulDi|GV_Str_DisplayFlag.Screen;
	    
	    V_uci = InF_Read_Data(V_ulDi, &V_ucAutoDisNum[0], &V_usLen, &V_usDataEncode);		/*取数据层自动循显显示第GV_Str_DisplayFlag.Screen屏显示代码*/
	    PF_Buffer4ToUlong32(&V_ucAutoDisNum[0], &V_ulDi, 4);              /*标识码转换*/
		PF_Buffer4ToUlong32(&V_ucAutoDisNum[C_DisRelatedOffset], &V_ulRelatedDI, 4);              /*标识码转换*/
 	 
	    if ( ( (C_OK != V_uci) && (C_CrcErr_DataZero != V_uci) ) || (0xaa == V_DisSign) )
	    {
            GV_Str_DisplayFlag.CodeID = C_DefaultDisDi;
            GV_Str_DisplayFlag.Related_CodeID = C_DefaultDisDiRelated;
            GV_Str_DisplayFlag.ParaNum = 0x00;
	    }	    	 
	    else
	    {
            GV_Str_DisplayFlag.CodeID = V_ulDi;
            GV_Str_DisplayFlag.Related_CodeID = V_ulRelatedDI;

            V_uci = InF_Display_JudgeIDActive(V_ulDi, GV_Str_DisplayFlag.Related_CodeID, V_ucAutoDisNum[8]);
            if ( C_OK != V_uci )
            {
                GV_Str_DisplayFlag.CodeID = C_DefaultDisDi;
                GV_Str_DisplayFlag.Related_CodeID = C_DefaultDisDiRelated;
                V_ucAutoDisNum[8] = 0x00;
                GV_Str_DisplayFlag.ParaNum = 0x00;

            }
            GV_Str_DisplayFlag.ParaNum = V_ucAutoDisNum[8];	    	  
	    }
#endif
        PF_Buffer4ToUlong32(&V_ucAutoDisNum[C_DisRelatedOffset], &V_ulRelatedDI, 4);              /*标识码转换*/
        
        if ( ( (C_OK!=V_uci) && (C_CrcErr_DataZero != V_uci) )
          || (InF_LocalAndRemoteMeterDiJudge(V_ulDi) != C_OK)
          || (InF_Display_JudgeIDActive(V_ulDi, V_ulRelatedDI, V_ucAutoDisNum[8]) != C_OK) )
        {
            GV_Str_DisplayFlag.CodeID = C_DefaultDisDi;
            GV_Str_DisplayFlag.Related_CodeID = C_DefaultDisDiRelated;
            GV_Str_DisplayFlag.ParaNum = 0x00;
        }
        else
        {
            GV_Str_DisplayFlag.CodeID = V_ulDi;
            GV_Str_DisplayFlag.Related_CodeID  =  V_ulRelatedDI;
            GV_Str_DisplayFlag.ParaNum = V_ucAutoDisNum[8];	
        }
        SF_FindDisChieseTableNo();        /*查找显示全局结构体，DI对应的汉字表格及行号*/
	    
	    /*GV_PowerOnChangeScreenFlag = 0x55;*/  /*换屏标志*/
    }
    else     /*切换时间未到*/
    {
        V_uci = InF_Display_JudgeIDActive(GV_Str_DisplayFlag.CodeID, GV_Str_DisplayFlag.Related_CodeID, GV_Str_DisplayFlag.ParaNum);/*安全性判断*/
        if ( C_OK != V_uci )
        {
            GV_Str_DisplayFlag.CodeID = C_DefaultDisDi;
            GV_Str_DisplayFlag.Related_CodeID = C_DefaultDisDiRelated;
            GV_Str_DisplayFlag.ParaNum = 0x00;
            SF_FindDisChieseTableNo();        /*查找显示全局结构体，DI对应的汉字表格及行号*/
        } 	  
    }
    if ( 0 != GV_Str_DisplayFlag.SV_usDisplayTimer )
    {
        GV_Str_DisplayFlag.SV_usDisplayTimer--;
    }
	 
    for ( V_uci = 0; V_uci < GV_Str_DisplaySignLen; V_uci++ )     /*状态指示字符，背光、指示灯、报警继电器处理*/
    {
        pStr_DisplaySignMesNum = (Str_DisplaySignMesNum *)GV_Str_DisplaySign[V_uci].PStr_DisplaySignMesNum;

        for ( V_ucj = 0; V_ucj < GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen; V_ucj++)
        {
            if ( (C_AlwaysDisplayNiu == pStr_DisplaySignMesNum[V_ucj].Timer)
              || (C_TwinkleDisplayNiu == pStr_DisplaySignMesNum[V_ucj].Timer)
              || (C_NotDisplayNiu == pStr_DisplaySignMesNum[V_ucj].Timer) )     /*常显、闪烁、不显*/
            {
                continue;
            }
            else
            {
                pStr_DisplaySignMesNum[V_ucj].Timer--;
                if ( C_RelayStatusLED == GV_Str_DisplaySign[V_uci].StateNum )   /*跳闸灯*/
                {
                    if ( C_ALLScreenDisplayDi != GV_Str_DisplayFlag.CodeID )  /*液晶查看，全屏显示*/
                    {	 	 		  
                        if ( C_Msg_Display == pStr_DisplaySignMesNum[V_ucj].SourceNo )
                        {
                            pStr_DisplaySignMesNum[V_ucj].Timer = 0;     /*清零*/
                        }
                    }
                }       		 
            }
        }
    }	 	 
}
/*******************************************************************************
函数原型：uchar8 InF_Display_JudgeIDActive( ulong32 V_ulCodeID, ulong32 V_ulRelatedCodeID, uchar8 V_ucScreenNum )
功能描述：判断显示标识码及该标识码对应的显示序号是否正确。当标识码为全FF时，直接返回C_OK，不进行显示序号判断
输入参数：ulong32 V_ulCodeID:待判断数据标识
        ulong32 V_ulRelatedCodeID:关联显示项数据标识
		uchar8 V_ucScreenNum:该标识码对应的显示序号
输出参数：无
返回参数：C_OK表示标识码和屏号均正确，C_IDError标识码错，C_IDNumError标识码对应的屏号错 
调用位置：供显示内部判断、通信设置轮显及键显参数判断  
备    注：显示序号的判断，是判断该序号是否超过该标识码最大的分屏数
*******************************************************************************/                                       
uchar8 InF_Display_JudgeIDActive( ulong32 V_ulCodeID, ulong32 V_ulRelatedCodeID, uchar8 V_ucScreenNum )
{
    Str_DisplayDI2Table *pStr_DisplayDI2Table;
    Str_DisplayDI1_0Table *pStr_DisplayDI1_0Table;
    uchar8 V_uci, V_ucDi[5], V_ucj, V_uck;

    PF_Ulong32ToBuffer4(&V_ucDi[0], &V_ulCodeID, 4);

    V_ucDi[4] = V_ucScreenNum;
    /*
    if(SF_DIChangeToOI(V_ucDi,V_OAD) != C_OK)
    {
        return C_IDNumError;	
    }
    */
    if ( C_ALLScreenDisplayDi == V_ulCodeID )           /*标识码为全FF*/
    {
        if ( 0xFF == V_ucScreenNum )
        {
            return C_OK;	 	  	 
        }
        else
        {
            return C_IDNumError;	 	  	 
        }
    }
	 	 	 
    for ( V_uci=0; V_uci<GV_Str_DisplayDI3TableLen; V_uci++ )  /*DI3判断*/
    {
        if ( V_ucDi[3] == GV_Str_DisplayDI3Table[V_uci].DI3 )
        {
            break;	 	  	 
        }
    }
    if ( V_uci >= GV_Str_DisplayDI3TableLen )
    {
        return C_IDError;	 	  
    }
	 	 
    pStr_DisplayDI2Table = (Str_DisplayDI2Table *)GV_Str_DisplayDI3Table[V_uci].PDI2Table;  /*2级表地址*/

    for ( V_ucj = 0; V_ucj < GV_Str_DisplayDI3Table[V_uci].DI2TableLen; V_ucj++ )  /*DI2判断*/
    {
        if ( V_ucDi[2] == pStr_DisplayDI2Table[V_ucj].DI2 )
        {
            break;	 	  	 
        }
    }
    if ( V_ucj >= GV_Str_DisplayDI3Table[V_uci].DI2TableLen )
    {
        return C_IDError;	 	  
    }

    pStr_DisplayDI1_0Table = (Str_DisplayDI1_0Table *)pStr_DisplayDI2Table[V_ucj].PDI1_0Table;  /*3级表地址*/

    for ( V_uck = 0; V_uck < pStr_DisplayDI2Table[V_ucj].DI1_0TableLen; V_uck++ )  /*DI1\DI0及显示序号判断*/
    {
        if ( V_ucDi[1] == pStr_DisplayDI1_0Table[V_uck].DI1 )   /*不同DI0类别*/
        {
	       
			/*#define C_DI0_Out0_ManyBorr_0  20*/     /*20：(多次)，不支持DI0==00,辅助汉字表格完全借用，如类似功率超限、失压、失流类数据，计算辅助显示表格时，该显示屏为20-20=0*/
			/*#define C_DI0_Out0_ManyBorr_4  24*/     /*24：(多次)，不支持DI0==00,辅助汉字表格没有全列，只列前24-20=4屏，如时段表、时区表、节假日等，计算辅助显示表格时，该显示屏为24-20=4*/
			/*#define C_DI0_Out0_ManyBorr_6  26*/     /*26：(多次)，不支持DI0==00,辅助汉字表格没有全列，只列前26-20=6屏，如阶梯表编程记录等，计算辅助显示表格时，该显示屏为26-20=6*/
			/*#define C_DI0_Out0_ManyBorr_1  21*/     /*21：(多次)，不支持DI0==00,辅助汉字表格没有全列，只列前21-20=1屏，如日时段表等，计算辅助显示表格时，该显示屏为21-20=1*/
            /*case C_DI0_Out0_Many:*/    /*(多次)，不支持DI0==00；冻结类，只列DI0最大值*/	       	  
            if ( (C_DI0_Out0_Many == pStr_DisplayDI1_0Table[V_uck].DI0Character)
              || (C_DI0_Out0_ManyBorr_0 == pStr_DisplayDI1_0Table[V_uck].DI0Character)
              || (C_DI0_Out0_ManyBorr_1 == pStr_DisplayDI1_0Table[V_uck].DI0Character)
              || (C_DI0_Out0_ManyBorr_2 == pStr_DisplayDI1_0Table[V_uck].DI0Character) )
             /*|| (C_DI0_Out0_ManyBorr_4 == PV_Str_DisplayDI1_0Table[V_uck].DI0Character)*/
             /*|| (C_DI0_Out0_ManyBorr_6 == PV_Str_DisplayDI1_0Table[V_uck].DI0Character))*/
            {
                if ( (0x00 != V_ucDi[0]) && (V_ucDi[0] <= pStr_DisplayDI1_0Table[V_uck].DI0Max) )
                {
                    break;	       	  	 	 
                }
            }
            else if ( C_DI0_OutMany == pStr_DisplayDI1_0Table[V_uck].DI0Character )
            {
                if ( (V_ulCodeID == 0x00110200) || (V_ulCodeID == 0x00210200) 
                  || (V_ulCodeID == 0x00120200) || (V_ulCodeID == 0x00220200)
                  || (V_ulCodeID == 0x00130200) || (V_ulCodeID == 0x00230200) )
                {
                    V_ucDi[0] = 1;
                }
                if ( V_ucDi[0] == pStr_DisplayDI1_0Table[V_uck].DI0Max )
                {
                    break;	       	  	 	    	 
                }	       	  	 	 	  

            }
        }	
    }	
	 	  
    if ( V_uck >= pStr_DisplayDI2Table[V_ucj].DI1_0TableLen )
    {
        return C_IDError;	 	 
    }
		 	  
    if ( C_DI0_Out0_ManyBorr_0 != pStr_DisplayDI1_0Table[V_uck].DI0Character )/*带关联OAD*/
    {
        /*不分屏，屏数为00，分屏，屏数从1、2开始，不允许设置0屏*/
        if ( pStr_DisplayDI1_0Table[V_uck].MaxDisplayScreen == 1 )
        {
            if ( V_ucScreenNum != 0 )
            {
                return C_IDNumError;	 
            }
        }
        else
        {
            if ( (V_ucScreenNum > pStr_DisplayDI1_0Table[V_uck].MaxDisplayScreen)   /*不包括等于,显示设置序号从0开始*/
              || (V_ucScreenNum == 0) )
            {
                if ( V_ucScreenNum == 0 )
                {
                    if ( (V_ulCodeID == COne485_Baud) || (V_ulCodeID == CTwo485_Baud) || (V_ulCodeID == CModular_Baud) )
                    {
                        ;
                    }
                    else
                    {
                        return C_IDNumError;	 
                    }
                }
                else
                {
                    return C_IDNumError;	 	  	
                }
            }	
        }
    }
    else
    {
        PF_Ulong32ToBuffer4(&V_ucDi[0], &V_ulRelatedCodeID, 4);/*关联列表*/

        V_ucDi[1] &= 0x0f;/*去掉关联特征*/

        if ( C_ALLScreenDisplayDi == V_ulCodeID )           /*标识码为全FF*/
        {
            return C_IDNumError;	 
        }

        for ( V_uci = 0; V_uci < GV_Str_DisplayDI3TableLen; V_uci++ )  /*DI3判断*/
        {
            if ( V_ucDi[3] == GV_Str_DisplayDI3Table[V_uci].DI3 )
            {
                break;	 	  	 
            }
        }
        if ( V_uci >= GV_Str_DisplayDI3TableLen )
        {
            return C_IDError;	 	  
        }

        pStr_DisplayDI2Table = (Str_DisplayDI2Table *)GV_Str_DisplayDI3Table[V_uci].PDI2Table;  /*2级表地址*/

        for ( V_ucj = 0; V_ucj < GV_Str_DisplayDI3Table[V_uci].DI2TableLen; V_ucj++ )  /*DI2判断*/
        {
            if ( V_ucDi[2] == pStr_DisplayDI2Table[V_ucj].DI2 )
            {
                break;	 	  	 
            }
        }
        if ( V_ucj >= GV_Str_DisplayDI3Table[V_uci].DI2TableLen )
        {
            return C_IDError;	 	  
        }

        pStr_DisplayDI1_0Table = (Str_DisplayDI1_0Table *)pStr_DisplayDI2Table[V_ucj].PDI1_0Table;  /*3级表地址*/

        for ( V_uck = 0; V_uck < pStr_DisplayDI2Table[V_ucj].DI1_0TableLen; V_uck++ )  /*DI1\DI0及显示序号判断*/
        {
            if ( V_ucDi[1] == pStr_DisplayDI1_0Table[V_uck].DI1 )   /*不同DI0类别*/
            {
			       
            	/*#define C_DI0_Out0_ManyBorr_0  20*/     /*20：(多次)，不支持DI0==00,辅助汉字表格完全借用，如类似功率超限、失压、失流类数据，计算辅助显示表格时，该显示屏为20-20=0*/
            	/*#define C_DI0_Out0_ManyBorr_4  24*/     /*24：(多次)，不支持DI0==00,辅助汉字表格没有全列，只列前24-20=4屏，如时段表、时区表、节假日等，计算辅助显示表格时，该显示屏为24-20=4*/
            	/*#define C_DI0_Out0_ManyBorr_6  26*/     /*26：(多次)，不支持DI0==00,辅助汉字表格没有全列，只列前26-20=6屏，如阶梯表编程记录等，计算辅助显示表格时，该显示屏为26-20=6*/
            	/*#define C_DI0_Out0_ManyBorr_1  21*/     /*21：(多次)，不支持DI0==00,辅助汉字表格没有全列，只列前21-20=1屏，如日时段表等，计算辅助显示表格时，该显示屏为21-20=1*/
                /*case C_DI0_Out0_Many: */   /*(多次)，不支持DI0==00；冻结类，只列DI0最大值*/	       	  
                if ( (C_DI0_Out0_Many == pStr_DisplayDI1_0Table[V_uck].DI0Character)
                  || (C_DI0_Out0_ManyBorr_0 == pStr_DisplayDI1_0Table[V_uck].DI0Character)
                  || (C_DI0_Out0_ManyBorr_1 == pStr_DisplayDI1_0Table[V_uck].DI0Character)
                  || (C_DI0_Out0_ManyBorr_2 == pStr_DisplayDI1_0Table[V_uck].DI0Character) )
                /*|| (C_DI0_Out0_ManyBorr_4 == PV_Str_DisplayDI1_0Table[V_uck].DI0Character)*/
                /*|| (C_DI0_Out0_ManyBorr_6 == PV_Str_DisplayDI1_0Table[V_uck].DI0Character))*/
                {
                    if ( (0x00 != V_ucDi[0]) && (V_ucDi[0] <= pStr_DisplayDI1_0Table[V_uck].DI0Max) )
                    {
                        break;	       	  	 	 
                    }
                }
                else if ( C_DI0_OutMany == pStr_DisplayDI1_0Table[V_uck].DI0Character )
                {
                    if ( V_ucDi[0] == pStr_DisplayDI1_0Table[V_uck].DI0Max )
                    {
                        break;	       	  	 	    	 
                    }	       	  	 	 	  

                }
            }	
        }	
		 	  
        if ( V_uck >= pStr_DisplayDI2Table[V_ucj].DI1_0TableLen )
        {
            return C_IDError;	 	 
        }

        if ( C_DI0_Out0_ManyBorr_0 != pStr_DisplayDI1_0Table[V_uck].DI0Character )/*带关联OAD*/
        {
            /*不分屏，屏数为00，分屏，屏数从1、2开始，不允许设置0屏*/
            if ( pStr_DisplayDI1_0Table[V_uck].MaxDisplayScreen == 1 )
            {
                if ( V_ucScreenNum != 0 )
                {
                    return C_IDNumError;	 
                }
            }
            else
            {
                if ( (V_ucScreenNum > pStr_DisplayDI1_0Table[V_uck].MaxDisplayScreen)   /*不包括等于,显示设置序号从0开始*/
                  || (V_ucScreenNum == 0) )
                {
                    return C_IDNumError;	 	  	
                }	
            }
        }
    }
 	  
    return C_OK;
}
/*******************************************************************************
函数原型：uchar8 SF_FindDisChieseScreenLen( uchar8 V_ucScreenMaxNum, uchar8 V_ucDICharacter )
功能描述：获取该标识码对应汉字表格中，实际所列屏数,根据3级表计算
输入参数：uchar8 V_ucScreenMaxNum:该标识码支持最大显示屏数
		uchar8 V_ucDICharacter:该标识码特征 
输出参数：无
返回参数：uchar8:该标识码实际显示屏数
调用位置：
备    注：
*******************************************************************************/
uchar8 SF_FindDisChieseScreenLen( uchar8 V_ucScreenMaxNum, uchar8 V_ucDICharacter )
{
    uchar8 V_ucLen = 0;

    if ( V_ucDICharacter < C_DI0_Out0_ManyBorr )
    {
        V_ucLen = V_ucScreenMaxNum;         /*屏数全列，不用特殊处理*/
    }
    else
    {
        if ( (V_ucDICharacter >= C_DI0_Out0_ManyBorr)
          && (V_ucDICharacter < C_DI0_OutManyBorr) )   /*屏数部分列，需特殊处理*/
        {
            V_ucLen = V_ucDICharacter - C_DI0_Out0_ManyBorr;  	 	  	 	  
        }
    }
    return V_ucLen; 	  	 	  
}
/*******************************************************************************
函数原型：void SF_FindDisChieseTableNo_General( Str_DisplayDI3Table Str_DisplayDI3Table, ulong32 V_ulCodeDi )
功能描述：根据1、2、3级表格及静态局部变量，显示结构体DI及显示序号，来查找该DI标识码对应的结构体,得到该标识码
		所在汉字表格结构体、汉字表格结构体内行号及显示数据偏移。
输入参数：Str_DisplayDI3Table Str_DisplayDI3Table:待处理3级表结构体变量
        V_ulCodeDi：标识码
输出参数：无
返回参数：无
调用位置：
备    注：！！！此函数使用注意内部减法核对
		 通用处理
         1）分屏时，屏序号从1开始；波特率特殊（4851 4852 载波）屏序号可以为00,01,02；
		 2）不分屏，屏序号为0；
*******************************************************************************/
void SF_FindDisChieseTableNo_General( Str_DisplayDI3Table Str_DisplayDI3Table, ulong32 V_ulCodeDi )
{
    Str_DisplayDI2Table *pStr_DisplayDI2Table;
    Str_DisplayDI1_0Table *pStr_DisplayDI1_0Table;
    ushort16 V_usLineMax, V_usLine, V_usDisplayDataOff;
    uchar8 *pV_ucChieseTable;
    uchar8 V_uci, V_ucj, V_uck;
    uchar8 V_ucDi[4];
    uchar8 V_ucDi1_0Len;
    uchar8 V_ucDisplayParaNum;
	 
	if ( ( ( V_ulCodeDi == CModular_Baud ) || ( V_ulCodeDi == COne485_Baud ) || ( V_ulCodeDi == CTwo485_Baud ) )
	  && ( GV_Str_DisplayFlag.ParaNum == 0 ) )	/*波特率为00、01、02屏，显示内容相同，均为波特率*/
    {
        V_ucDisplayParaNum = 1;
	}
	else
	{
		V_ucDisplayParaNum = GV_Str_DisplayFlag.ParaNum;
	}
	
	V_usLine = 0;             /*辅助汉字表格行号*/
	V_usDisplayDataOff = 0;   /* 数据偏移*/
       
	PF_Ulong32ToBuffer4(&V_ucDi[0], &V_ulCodeDi, 4);
		 
	GV_Str_DisplayFlag.P_ChieseTableNo = (Str_DisplayDI3Table).P_ChieseTable; 	/*辅助汉字结构体*/
		 
	V_usLineMax = (Str_DisplayDI3Table).ChieseTableLen; 	/*汉字表格对应最大数据长度，判断是否越界用*/
	
	pStr_DisplayDI2Table = (Str_DisplayDI2Table *)((Str_DisplayDI3Table).PDI2Table);  /*2级表地址*/
   	 
	          	 
	for ( V_ucj = 0; V_ucj < (Str_DisplayDI3Table).DI2TableLen; V_ucj++ )		/*根据标识码DI2计算，辅助汉字表格行号累加，2级表,查找该标识码所在汉字表格行号*/
	{
		if ( V_ucDi[2] == pStr_DisplayDI2Table[V_ucj].DI2 )
		{
			break;	 	  	
		}
		else
		{
			pStr_DisplayDI1_0Table = (Str_DisplayDI1_0Table *)pStr_DisplayDI2Table[V_ucj].PDI1_0Table;
			for ( V_uck = 0; V_uck < pStr_DisplayDI2Table[V_ucj].DI1_0TableLen; V_uck++ )   /*辅助汉字表格行号累加,3级表*/
			{
				V_ucDi1_0Len = SF_FindDisChieseScreenLen(pStr_DisplayDI1_0Table[V_uck].MaxDisplayScreen,pStr_DisplayDI1_0Table[V_uck].DI0Character);/*获取该标识码，对应汉字表格实际所列屏数*/
				V_usLine += V_ucDi1_0Len;	 	  	 	  
			}
		}	 	  
	}
	if ( V_ucj >= (Str_DisplayDI3Table).DI2TableLen )
	{
		return;        /*正常不存在*/ 	 
	}
	 
	pStr_DisplayDI1_0Table = (Str_DisplayDI1_0Table *)pStr_DisplayDI2Table[V_ucj].PDI1_0Table;   
	for ( V_uck = 0; V_uck < pStr_DisplayDI2Table[V_ucj].DI1_0TableLen; V_uck++ )   /*根据标识码DI1计算，汉字表格内行号，3级表*/
    {   
		if ( V_ucDi[1] == pStr_DisplayDI1_0Table[V_uck].DI1 )   /*不同DI0类别*/
		{
			if ( V_ucDi[0] == pStr_DisplayDI1_0Table[V_uck].DI0Max )
			{
				break;
			}
			else
			{ 	  	 	   
				if ( ( C_DI0_Out0_Many == pStr_DisplayDI1_0Table[V_uck].DI0Character )
				  || ( C_DI0_Out0_ManyBorr_0 == pStr_DisplayDI1_0Table[V_uck].DI0Character)
				  || ( C_DI0_Out0_ManyBorr_2 == pStr_DisplayDI1_0Table[V_uck].DI0Character)
				  || ( C_DI0_Out0_ManyBorr_1 == pStr_DisplayDI1_0Table[V_uck].DI0Character) )
				{
					if ( V_ucDi[0] <= pStr_DisplayDI1_0Table[V_uck].DI0Max )
					{
						break;
					}
				}

				V_ucDi1_0Len = SF_FindDisChieseScreenLen(pStr_DisplayDI1_0Table[V_uck].MaxDisplayScreen, pStr_DisplayDI1_0Table[V_uck].DI0Character);		/*获取该标识码，对应汉字表格实际所列屏数*/
				V_usLine += V_ucDi1_0Len;	 	  	 	  	 	  	 	  	 	 
			}
		}
		else
		{
			V_ucDi1_0Len = SF_FindDisChieseScreenLen(pStr_DisplayDI1_0Table[V_uck].MaxDisplayScreen, pStr_DisplayDI1_0Table[V_uck].DI0Character);		/*获取该标识码，对应汉字表格实际所列屏数*/
			V_usLine += V_ucDi1_0Len;	 	  	 	  	 	  	 
		}
    }	 
	if ( V_uck >= pStr_DisplayDI2Table[V_ucj].DI1_0TableLen )
	{
        return;        /*正常不存在*/	 
	}

 /***************************************分屏显示行号及数据偏移地址计算*******************************/
	 
	V_ucDi1_0Len = SF_FindDisChieseScreenLen(pStr_DisplayDI1_0Table[V_uck].MaxDisplayScreen, pStr_DisplayDI1_0Table[V_uck].DI0Character);			/*获取该标识码，对应汉字表格实际所列屏数*/
	
	if ( 0x00 == V_ucDi1_0Len )
	{
		return;   /*该处查找实际汉字表格，有借用的查找借用表格，正常不存在*/
	}
	if ( V_ucDisplayParaNum > V_ucDi1_0Len )         /*显示序号>=所列显示屏数，分屏显示行号及数据偏移地址计算(节假日)*/
	{
		if ( ( V_usLine + V_ucDi1_0Len - 1 ) >= V_usLineMax )     /*正常不存在*/
		{
			return;	
		}
	 	else
	 	{
			for ( V_uci = 0; V_uci < V_ucDi1_0Len; V_uci++ )  		/*偏移地址计算*/
			{
				pV_ucChieseTable = (uchar8 *)(GV_Str_DisplayFlag.P_ChieseTableNo + (V_usLine + V_uci) * C_ChineseSignLen);  /*汉字表格结构体地址*/	 	     	  
				V_usDisplayDataOff += (pV_ucChieseTable[C_ChinaLineDataLenKillZero] & C_GetChinaDataLenBit0x07);		  /*低3位为显示数据长度*/	 	  	 	     
			}
         	pV_ucChieseTable = (uchar8 *)(GV_Str_DisplayFlag.P_ChieseTableNo + (V_usLine + V_ucDi1_0Len - 1) * C_ChineseSignLen);  /*汉字表格结构体地址*/	 	     	  
	 	    V_usDisplayDataOff += (V_ucDisplayParaNum - V_ucDi1_0Len - 1) * (pV_ucChieseTable[C_ChinaLineDataLenKillZero] & C_GetChinaDataLenBit0x07);  /*偏移计算，最后1屏往后汉字表格相同*/
	 	 }
	 	 V_usLine += (V_ucDi1_0Len - 1);	 	  
	 }
	else
	{
        if ( V_ucDi1_0Len == 1 )
		{
			pV_ucChieseTable = (uchar8 *)(GV_Str_DisplayFlag.P_ChieseTableNo + (V_usLine + (V_ucDisplayParaNum) ) * C_ChineseSignLen);  /*汉字表格结构体地址*/
		}
		else
		{
			pV_ucChieseTable = (uchar8 *)(GV_Str_DisplayFlag.P_ChieseTableNo + (V_usLine + (V_ucDisplayParaNum - 1) ) * C_ChineseSignLen);  /*汉字表格结构体地址*/
		}
		if ( C_NoOffset != pV_ucChieseTable[C_ChinaeseLineDataOffSet] )  /*有绝对偏移地址的话，汉字表格肯定全列*/
		{
			V_usDisplayDataOff = pV_ucChieseTable[C_ChinaeseLineDataOffSet];	/*取绝对偏移地址*/
		}
		else
		{
			if ( V_ucDi1_0Len > 1 )	/*一屏显示的数据偏移为0*/
			{
				if ( (V_usLine + V_ucDisplayParaNum - 1) >= V_usLineMax )
				{
					return;    /*正常不存在*/
				}

				for ( V_uci = 0; V_uci < (V_ucDisplayParaNum - 1); V_uci++ )  /*偏移地址计算*/
				{
					pV_ucChieseTable = (uchar8 *)(GV_Str_DisplayFlag.P_ChieseTableNo + (V_usLine + V_uci) * C_ChineseSignLen);  /*汉字表格结构体地址*/
					V_usDisplayDataOff += (pV_ucChieseTable[C_ChinaLineDataLenKillZero] & C_GetChinaDataLenBit0x07);		  /*低3位为显示数据长度*/	 	  	 	     
				}
			}
		}	
		  
		if ( V_ucDi1_0Len == 1 )
		{
			V_usLine += V_ucDisplayParaNum;	/*应该是0屏*/
		}
		else
		{
			V_usLine += V_ucDisplayParaNum - 1;
        }
    }
	 	 	 
    if ( V_usLine >= V_usLineMax )
    {
        return;     /*正常不存在*/
    }	 
	 
    GV_Str_DisplayFlag.ChieseTableLineNo = V_usLine; 
    GV_Str_DisplayFlag.SV_DisplayDataOff = V_usDisplayDataOff; 
	 	 
}
/*******************************************************************************
函数原型：void SF_FindDisChieseTableNo(void) 
功能描述：根据1、2、3级表格及静态局部变量，显示结构体DI及显示序号，来查找该DI标识码对应的结构体,得到该标识码
		所在汉字表格结构体、汉字表格结构体内行号及显示数据偏移。  
输入参数：无
输出参数：无
返回参数：无
调用位置：
备    注：
特殊处理数据:
	冻结(相同显示内容，只列了定时冻结，同瞬时冻结、DI2特殊处理，根据DI2=0)  
	需量超限记录(只列正向，显示不分正反向，无功，不显示单位，DI1特殊处理，根据DI1=1)、
	电压合格率(只列本月电压合格率，不列ABC，正常ABC不显示，DI1特殊处理，根据DI1=0)，  
	编程记录(最近10个数据项标识码，只列最近1个，前4屏)，
	时段表编程(汉字表格，只列前4屏,)，
	时区表编程(汉字表格，只列前4屏,)
	周休日编程(同有功组合状态字编程、无功组合状态字1、2编程，显示字符不用特殊处理，DI1特殊处理，根据DI1=7) 
	节假日编程(汉字表格，只列前4屏),费率参数表编程(只列前4屏,显示不区分费率1-4),
	阶梯表编程(当前套第1-6阶梯值\当前套阶梯电价1-7\当前套年第1-4结算日(每类只列1屏，一共列6屏：特殊处理) 
	开表盖记录(同开端钮盖，DI1特殊处理，根据DI1=0D)，
	失压10记录(只列A相失压，汉字表格不列"A""失压"，DI2特殊处理，根据DI2=1；“失压”,同欠压11、过压12、断相13，只有计算
汉字表格偏移时，转化为DI3=10计算，标识码的判断采用标识码）。显示字符特殊处理 
	失流18(只列A相失压，汉字表格不列“A”，“失流”，同过流19、断流1A，DI2特殊处理，根据DI2=1)。显示字符特殊处理
	电压逆相序(只列电压逆相序同电流逆相序，显示表格完全一样不单独处理；功率反向1B、过载1C(其中功率反向过载，”ABC相显示“单独处理)，DI2特殊处理，根据DI2=1)、 显示字符特殊处理 
	电压不平衡(同电流不平衡、电流严重不平衡，完全借用不用特殊处理),  
	功率因数1F(只列总功率因数，”ABC相“显示单独处理，程序内部处理，DI2特殊处理，根据DI2=0)，显示字符特殊处理
	跳闸记录(只列跳闸记录，同合闸记录，不用特殊处理),  
	参数时区表、日时段表（只列第1屏，且只列第1套，同第二套，DI2特殊处理，根据DI2=1）
	阶梯表单独处理（只列当前套,同备用套，且只列阶梯值、阶梯电价、结算日，DI1特殊处理，根据DI2=4）
	费率电价(同备用套，DI1特殊处理，根据DI1=1)、
*******************************************************************************/                                        
void SF_FindDisChieseTableNo( void )
{
    ulong32 V_ulDI32; 
    ushort16 V_usLine, V_usDisplayDataOff;
    uchar8 V_uci;
    uchar8 V_ucDi[4];

    V_usLine = 0;             /*辅助汉字表格行号*/
    V_usDisplayDataOff = 0;   /* 数据偏移*/
	 	 
    GV_Str_DisplayFlag.ChieseTableLineNo = V_usLine; 
    GV_Str_DisplayFlag.SV_DisplayDataOff = V_usDisplayDataOff; 
   
    if ( C_ALLScreenDisplayDi == GV_Str_DisplayFlag.CodeID )   /*标识码为全FF*/
    {
        return;   	 
    }
     
    V_ulDI32 = GV_Str_DisplayFlag.CodeID;
    if ( (V_ulDI32 == 0x00110200) || (V_ulDI32 == 0x00210200) 
      || (V_ulDI32 == 0x00120200) || (V_ulDI32 == 0x00220200)
      || (V_ulDI32 == 0x00130200) || (V_ulDI32 == 0x00230200) )
    {
        V_ulDI32 |= 0x00000001 ;
    }	 
    PF_Ulong32ToBuffer4(&V_ucDi[0], &V_ulDI32, 4);
	
    for ( V_uci = 0; V_uci < GV_Str_DisplayDI3TableLen; V_uci++ )  /*1级表*/
    {
        if ( V_ucDi[3] == (GV_Str_DisplayDI3Table[V_uci].DI3) )/*判断高4字节*/
        {
            break;	 	  	
        }
    }
    if (V_uci >= GV_Str_DisplayDI3TableLen )
    {
        return;                              /*正常不存在*/	 	  
    }
    
#if(0)	 
	if ( ( (V_ucDi[3]&0xF0) == 0x30) || ( (V_ucDi[3]&0xF0) == 0x50 ) )
	{
		if ( (V_ucDi[3]&0xF0) == 0x50) && (V_ucDi[1] == 0x02) )
        /*事件记录和冻结的显示格式按照关联OAD格式*///
        {
            V_ulDI32 = GV_Str_DisplayFlag.Related_CodeID;
            PF_Ulong32ToBuffer4(&V_ucDi[0], &V_ulDI32, 4);
        }	
	}
#endif

	if ( GV_Str_DisplayFlag.Related_CodeID != 0xFFFFFFFF )/*读关联列表*/
	{
        V_ulDI32 = GV_Str_DisplayFlag.Related_CodeID;
        PF_Ulong32ToBuffer4(&V_ucDi[0], &V_ulDI32, 4);
        V_ucDi[1] &= 0x0f;/*去掉关联特征*/
        V_ulDI32 &= 0xffff0fff;/*去掉关联特征*/


        for ( V_uci = 0; V_uci < GV_Str_DisplayDI3TableLen; V_uci++ )  /*1级表*/
        {
            if ( V_ucDi[3] == (GV_Str_DisplayDI3Table[V_uci].DI3) )/*判断高4字节*/
            {
                break;	 	  	
            }
        }
        if ( V_uci >= GV_Str_DisplayDI3TableLen )
        {
            return;                              /*正常不存在*/	 	  
        }
	}

    SF_FindDisChieseTableNo_General(GV_Str_DisplayDI3Table[V_uci], V_ulDI32);     /*通用类数据处理，不用特殊处理*/
 	 
}
/*******************************************************************************
函数原型：void SF_DisplyKey(uchar8 V_ucKeyType)
功能描述：按键显示处理
输入参数：uchar8 V_ucKeyType:按键类型 ，C_KeyUp：上翻建；C_KeyDown：下翻建；
输出参数：无
返回参数：无
调用位置：
备    注：上翻、下翻按键处理按键显示，背光点亮60s，关闭报警继电器及蜂鸣器，当前为全屏显示模式时，状态字符不做处理
		分有电没电处理，有电液晶显示时间设置为60s，没电液晶显示时间设置为30s 
*******************************************************************************/                                       
void SF_DisplyKey( uchar8 V_ucKeyType )
{
    Str_DisplaySignMesNum *pStr_DisplaySignMesNum;
    ulong32 V_ulDi, V_ulRelatedDI;
    ushort16 V_usTempData, V_usLen, V_usDataEncode;  
    uchar8 V_uci, V_ucj, V_ucDisScreenNum, V_uctimer[2];
    uchar8 V_ucAutoDisNum[CLKey_Dis_1ScreenCode];
    uchar8 V_ucPowerState;
    uchar8 /*V_uctimer[2], */V_ucReturnFlag;
    
       
    /*V_DisSign=0x55; */   /*标识码有效性判断标志*/

    V_ucPowerState = InF_ReadPowerState();     /*获取当前电表工作状态，有电、没电*/
    if ( C_PowerOff == V_ucPowerState )          /*没电，显示时间设置为30s*/
    {
        V_usLen = CLNEScreenDisplay;
        V_uci = InF_Read_Data(CNEScreenDisplay, &V_uctimer[0], &V_usLen, &V_usDataEncode);/*取按键循显时间*/
        /*PF_BCDtoHexBytes(&V_uctimer[0],&V_Hex,2);*/        /*BCD转hex*/
        PF_Buffer2ToUshort16(&V_uctimer[0], &V_usTempData);
        V_usTempData <<= 1;   	    /*内部是500ms基准*/
        if ( (C_OK != V_uci) || (0x00 == V_usTempData) )
        {
            V_usTempData = C_Display30s;                   /*按键显示时间*/ 
        }
        
        GV_Str_DisplayFlag.SV_usDisplayTimer = V_usTempData;
    }
    else    /*有电情况下处理*/                          
    {
        for ( V_uci = 0; V_uci < GV_Str_DisplaySignLen; V_uci++ )     /*状态指示字符，报警继电器,蜂鸣器,背光定时器处理*/
        {
            pStr_DisplaySignMesNum = (Str_DisplaySignMesNum *)GV_Str_DisplaySign[V_uci].PStr_DisplaySignMesNum;
            if ( (C_WarnOutPut == GV_Str_DisplaySign[V_uci].StateNum) || (C_Beeper == GV_Str_DisplaySign[V_uci].StateNum) )  /*关闭报警继电器或蜂鸣器*/
            {
                for ( V_ucj = 0; V_ucj < GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen; V_ucj++ )
                {
                    pStr_DisplaySignMesNum[V_ucj].Timer = C_NotDisplayNiu;    /*定时器清零*/
                }
            }
            if ( C_BackLED == GV_Str_DisplaySign[V_uci].StateNum )              /*背光电量时间,60s*/
            {
                for ( V_ucj = 0; V_ucj < GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen; V_ucj++ )
                {
                    if ( C_Msg_Display == pStr_DisplaySignMesNum[V_ucj].SourceNo )
                    {
                        V_usLen = CLBacklightTime;
                        V_ucReturnFlag = InF_Read_Data(CBacklightTime, &V_uctimer[0], &V_usLen, &V_usDataEncode);/*取按键循显时间*/
                        PF_Buffer2ToUshort16(&V_uctimer[0], &V_usTempData);
                        if ( (C_OK != V_ucReturnFlag) || (0x00 == V_usTempData) )
                        {
                            pStr_DisplaySignMesNum[V_ucj].Timer = C_Display60s;                   /*按键显示时间*/
                        }
                        else
                        {
                            pStr_DisplaySignMesNum[V_ucj].Timer = 2 * V_usTempData + 1;  /*内部是500ms基准*/
                        }
                        break;	 	 
                    }
                }	
            }	 	    	   
        }

        V_usLen = CLPer_Dis_Screen_Time;
        V_uci = InF_Read_Data(CPerkey_Dis_Screen_Time, &V_uctimer[0], &V_usLen, &V_usDataEncode);/*取按键循显时间*/
        /*PF_BCDtoHexBytes(&V_uctimer[0],&V_Hex,1); */       /*BCD转hex*/
        PF_Buffer2ToUshort16(&V_uctimer[0], &V_usTempData);
        V_usTempData <<= 1;   	    /*内部是500ms基准*/
        if ( (C_OK != V_uci) || (0x00 == V_usTempData) )
        {
            V_usTempData = C_Display60s;                   /*按键显示时间*/ 
        }
        
        GV_Str_DisplayFlag.SV_usDisplayTimer = V_usTempData;
    }
	 
    V_usLen = CLKey_CycDis_Screen_Num;
    V_uci = InF_Read_Data(CKey_CycDis_Screen_Num, &V_ucDisScreenNum, &V_usLen, &V_usDataEncode);/*取数据层按键显示屏数*/
    /*PF_BCDtoHexBytes(&V_ucDisScreenNum,&V_Hex,1); */             /*BCD转hex*/
    /*V_ucDisScreenNum=(uchar8)V_Hex;	*/ 
    if ( (C_OK != V_uci) || (0x00 == V_ucDisScreenNum) )
    {
        V_ucDisScreenNum = C_DefaultDisScreenNum;                   /*取默认显示屏数*/ 
    }                                                          /*包括全0*/

    if ( C_KeyDisplay == GV_Str_DisplayFlag.SV_ucDisplayMode )        /*按键显示模式*/
    {
        if ( C_KeyUp == V_ucKeyType )                                  /*上翻键*/
        {
            GV_Str_DisplayFlag.Screen--;
            if ( 0 == GV_Str_DisplayFlag.Screen )                       /*显示屏数翻转*/
            {
                GV_Str_DisplayFlag.Screen = V_ucDisScreenNum;
            }	
#if(0)
            V_DisScreenNumTemp = GV_Str_DisplayFlag.Screen;

            V_usLen = CLKey_Dis_1ScreenCode;
            V_ulDi = CKey_Dis_1ScreenCode&0xFFFFFF00;
            V_ulDi = V_ulDi|GV_Str_DisplayFlag.Screen;
            InF_Read_Data(V_ulDi, &V_ucAutoDisNum[0], &V_usLen, &V_usDataEncode);/*取数据层按键显示第GV_Str_DisplayFlag.Screen屏显示代码*/
            PF_Buffer4ToUlong32(&V_ucAutoDisNum[0], &V_ulDi, 4);              /*标识码转换*/

            while ( InF_LocalAndRemoteMeterDiJudge(V_ulDi) )   /*标识码支持或1个循环完毕退出循环*/
            {
                GV_Str_DisplayFlag.Screen--;
                if ( 0 == GV_Str_DisplayFlag.Screen )                       /*显示屏数翻转*/
                {
                    GV_Str_DisplayFlag.Screen = V_ucDisScreenNum;
                }
                if ( V_DisScreenNumTemp == GV_Str_DisplayFlag.Screen )   /*循环1个周期*/
                {
                    V_DisSign = 0xaa;
                    break;
                }
                V_usLen = CLKey_Dis_1ScreenCode;
                V_ulDi = CKey_Dis_1ScreenCode&0xFFFFFF00;
                V_ulDi = V_ulDi|GV_Str_DisplayFlag.Screen;
                InF_Read_Data(V_ulDi, &V_ucAutoDisNum[0], &V_usLen, &V_usDataEncode);/*取数据层按键显示第GV_Str_DisplayFlag.Screen屏显示代码*/
                PF_Buffer4ToUlong32(&V_ucAutoDisNum[0], &V_ulDi, 4);              /*标识码转换*/
            }	
#endif
        }
        else                                                       /*下翻键*/
        {
            GV_Str_DisplayFlag.Screen++;
            if ( GV_Str_DisplayFlag.Screen > V_ucDisScreenNum )            /*超过最大键显屏数*/
            {
                GV_Str_DisplayFlag.Screen = 1;
            }
#if(0)
            V_DisScreenNumTemp = GV_Str_DisplayFlag.Screen;

            V_usLen = CLKey_Dis_1ScreenCode;
            V_ulDi = CKey_Dis_1ScreenCode&0xFFFFFF00;
            V_ulDi = V_ulDi|GV_Str_DisplayFlag.Screen;
            InF_Read_Data(V_ulDi, &V_ucAutoDisNum[0], &V_usLen, &V_usDataEncode);/*取数据层按键显示第GV_Str_DisplayFlag.Screen屏显示代码*/
            PF_Buffer4ToUlong32(&V_ucAutoDisNum[0], &V_ulDi, 4);              /*标识码转换*/

            while ( InF_LocalAndRemoteMeterDiJudge(V_ulDi) )   /*标识码支持或1个循环完毕退出循环*/
            {
                GV_Str_DisplayFlag.Screen++;
                if ( GV_Str_DisplayFlag.Screen > V_ucDisScreenNum )            /*超过最大键显屏数*/
                {
                    GV_Str_DisplayFlag.Screen = 1;
                }
                if ( V_DisScreenNumTemp == GV_Str_DisplayFlag.Screen )   /*循环1个周期*/
                {
                    V_DisSign = 0xaa;
                    break;
                }
                V_usLen = CLKey_Dis_1ScreenCode;
                V_ulDi = CKey_Dis_1ScreenCode&0xFFFFFF00;
                V_ulDi = V_ulDi|GV_Str_DisplayFlag.Screen;
                InF_Read_Data(V_ulDi, &V_ucAutoDisNum[0], &V_usLen, &V_usDataEncode);/*取数据层按键显示第GV_Str_DisplayFlag.Screen屏显示代码*/
                PF_Buffer4ToUlong32(&V_ucAutoDisNum[0], &V_ulDi, 4);              /*标识码转换*/
            }
#endif
        }
    }
    else
    {
        GV_Str_DisplayFlag.SV_ucDisplayMode = C_KeyDisplay;        /*设置为按键显示模式*/
        GV_Str_DisplayFlag.Screen = 1;
#if(0)	
        V_DisScreenNumTemp = GV_Str_DisplayFlag.Screen;	

        V_usLen = CLKey_Dis_1ScreenCode;
        V_ulDi = CKey_Dis_1ScreenCode&0xFFFFFF00;
        V_ulDi = V_ulDi|GV_Str_DisplayFlag.Screen;
        InF_Read_Data(V_ulDi, &V_ucAutoDisNum[0], &V_usLen, &V_usDataEncode);/*取数据层按键显示第GV_Str_DisplayFlag.Screen屏显示代码*/
        PF_Buffer4ToUlong32(&V_ucAutoDisNum[0], &V_ulDi, 4);    /*标识码转换*/

        while ( InF_LocalAndRemoteMeterDiJudge(V_ulDi) )   /*标识码支持或1个循环完毕退出循环*/
        {
            GV_Str_DisplayFlag.Screen++;
            if ( GV_Str_DisplayFlag.Screen > V_ucDisScreenNum )            /*超过最大键显屏数*/
            {
                GV_Str_DisplayFlag.Screen = 1;
            }
            if ( V_DisScreenNumTemp == GV_Str_DisplayFlag.Screen )   /*循环1个周期*/
            {
                V_DisSign = 0xaa;
                break;
            }
            V_usLen = CLKey_Dis_1ScreenCode;
            V_ulDi = CKey_Dis_1ScreenCode&0xFFFFFF00;
            V_ulDi = V_ulDi|GV_Str_DisplayFlag.Screen;
            InF_Read_Data(V_ulDi, &V_ucAutoDisNum[0], &V_usLen, &V_usDataEncode);/*取数据层按键显示第GV_Str_DisplayFlag.Screen屏显示代码*/
            PF_Buffer4ToUlong32(&V_ucAutoDisNum[0], &V_ulDi, 4);              /*标识码转换*/
        }	 
#endif
    }	 

    V_usLen = CLKey_Dis_1ScreenCode;
    V_ulDi = CKey_Dis_1ScreenCode&0xFFFFFF00;
    V_ulDi = V_ulDi|GV_Str_DisplayFlag.Screen;

    V_uci = InF_Read_Data(V_ulDi, &V_ucAutoDisNum[0], &V_usLen, &V_usDataEncode);/*取数据层按键显示第GV_Str_DisplayFlag.Screen屏显示代码*/
    PF_Buffer4ToUlong32(&V_ucAutoDisNum[0], &V_ulDi, 4);              /*标识码转换*/
    PF_Buffer4ToUlong32(&V_ucAutoDisNum[C_DisRelatedOffset], &V_ulRelatedDI, 4);              /*标识码转换*/
	 
#if(0)
    if ( ( (C_OK != V_uci) && (C_CrcErr_DataZero != V_uci) ) || (0xaa == V_DisSign) )
    {
        GV_Str_DisplayFlag.CodeID = C_DefaultDisDi;
        GV_Str_DisplayFlag.Related_CodeID = C_DefaultDisDiRelated;
        GV_Str_DisplayFlag.ParaNum = 0x00;
    }	 	 
    else
    {
        GV_Str_DisplayFlag.CodeID = V_ulDi;
        PF_Buffer4ToUlong32(&V_ucAutoDisNum[C_DisRelatedOffset], &V_ulDi, 4);              /*标识码转换*/
        GV_Str_DisplayFlag.Related_CodeID  = V_ulDi;
        GV_Str_DisplayFlag.ParaNum = 0x00;

        V_uci = InF_Display_JudgeIDActive(GV_Str_DisplayFlag.CodeID, GV_Str_DisplayFlag.Related_CodeID,V_ucAutoDisNum[C_DisScreenNumOffset]);  /*安全性判断*/

        if ( C_OK != V_uci )
        {
            GV_Str_DisplayFlag.CodeID = C_DefaultDisDi;
            GV_Str_DisplayFlag.Related_CodeID = C_DefaultDisDiRelated;
            V_ucAutoDisNum[C_DisScreenNumOffset] = 0x00;
        }
        GV_Str_DisplayFlag.ParaNum = V_ucAutoDisNum[C_DisScreenNumOffset];	    	  
    }
#endif
    if ( ( (C_OK != V_uci) && (C_CrcErr_DataZero != V_uci) )
      || ( C_OK != InF_LocalAndRemoteMeterDiJudge(V_ulDi) )
      || ( InF_Display_JudgeIDActive(V_ulDi, V_ulRelatedDI, V_ucAutoDisNum[8]) != C_OK) )
    {
        GV_Str_DisplayFlag.CodeID = C_DefaultDisDi;
        GV_Str_DisplayFlag.Related_CodeID = C_DefaultDisDiRelated;
        GV_Str_DisplayFlag.ParaNum = 0x00;
    }
    else
    {
        GV_Str_DisplayFlag.CodeID = V_ulDi;
        GV_Str_DisplayFlag.Related_CodeID  =  V_ulRelatedDI;
        GV_Str_DisplayFlag.ParaNum = V_ucAutoDisNum[8];
    }
    SF_FindDisChieseTableNo();        /*查找显示全局结构体，DI对应的汉字表格及行号*/
}
/*******************************************************************************
函数原型：void SF_CheckDisplay( ulong32 V_ulDi, ulong32 V_ulRelated_CodeID, uchar8 V_ucDisScreenNum, ushort16 V_usTimer )
功能描述：液晶查看模式处理，背光，点亮时间为10s。当为全FF时，跳闸指示灯，点亮时间为10s，内部处理背光定时器。 
		退出液晶查看模式时，退出该模式指示灯定时器清零,标识码不为全FF时,该消息指示灯定时器也清零(在500ms查询中完成)
输入参数：ulong32 V_ulDi:液晶查看数据标示； 
        ulong32 V_ulRelated_CodeID：关联显示项标识
        uchar8 V_ucDisScreenNum：该数据标示对应的显示屏序号 
        ushort16 V_usTimer：液晶查看显示时间
输出参数：无
返回参数：无
调用位置：
备    注：
*******************************************************************************/                                       
void SF_CheckDisplay( ulong32 V_ulDi,ulong32 V_ulRelated_CodeID, uchar8 V_ucDisScreenNum, ushort16 V_usTimer )
{
    ushort16 V_usHex, V_usLen, V_usDataEncode;
    uchar8 V_uci, V_ucj;
    uchar8 V_uctimer[2], V_ucReturnFlag;

    Str_DisplaySignMesNum *pStr_DisplaySignMesNum;

    for ( V_uci = 0; V_uci < GV_Str_DisplaySignLen; V_uci++ )     /*背光点亮10s,如DI为全FF，跳闸指示灯也点亮10s*/
    {
        pStr_DisplaySignMesNum = (Str_DisplaySignMesNum *)GV_Str_DisplaySign[V_uci].PStr_DisplaySignMesNum;
        if ( C_BackLED == GV_Str_DisplaySign[V_uci].StateNum ) 
        {
            for ( V_ucj = 0; V_ucj < GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen; V_ucj++ )
            {
                if ( C_Msg_Display == pStr_DisplaySignMesNum[V_ucj].SourceNo )
                {
                    V_usLen = CLSViewBacklightTime;
                    V_ucReturnFlag = InF_Read_Data(CSViewBacklightTime, &V_uctimer[0], &V_usLen, &V_usDataEncode);/*取按键循显时间*/
                    PF_Buffer2ToUshort16(&V_uctimer[0], &V_usHex);
                    if ( (C_OK != V_ucReturnFlag) || (0x00 == V_usHex) )
                    {
                        pStr_DisplaySignMesNum[V_ucj].Timer = C_Display10s+1;                   /*按键显示时间*/ 
                    }
                    else
                    {
                        pStr_DisplaySignMesNum[V_ucj].Timer = 2 * V_usHex + 1;  /*内部是500ms基准*/
                    }
                    break;	 	 
                }
            }	 	   	  
        }       
	 	 	
        if ( C_RelayStatusLED == GV_Str_DisplaySign[V_uci].StateNum )   /*跳闸灯*/
        {
            if ( C_ALLScreenDisplayDi == V_ulDi )  /*全屏显示标识码*/
            {
                for ( V_ucj = 0; V_ucj < GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen; V_ucj++)
                {
                    if ( C_Msg_Display == pStr_DisplaySignMesNum[V_ucj].SourceNo )
                    {
                        V_usLen = CLSViewBacklightTime;
                        V_ucReturnFlag = InF_Read_Data(CSViewBacklightTime, &V_uctimer[0], &V_usLen, &V_usDataEncode);/*取按键循显时间*/
                        PF_Buffer2ToUshort16(&V_uctimer[0], &V_usHex);
                        if ( (C_OK != V_ucReturnFlag) || (0x00 == V_usHex) )
                        {
                            pStr_DisplaySignMesNum[V_ucj].Timer = C_Display10s + 1;                   /*按键显示时间*/ 
                        }
                        else
                        {
                            pStr_DisplaySignMesNum[V_ucj].Timer = 2 * V_usHex + 1;  /*内部是500ms基准*/
                        }

                        break;	

                    }
                } 
            }
        }       
    }	
	 
    GV_Str_DisplayFlag.CodeID = V_ulDi;
    GV_Str_DisplayFlag.Related_CodeID = V_ulRelated_CodeID;
    GV_Str_DisplayFlag.SV_usDisplayTimer = 2*V_usTimer;    /*液晶查看显示时间,10s*/
    if ( GV_Str_DisplayFlag.SV_usDisplayTimer == 0 )
    {
        GV_Str_DisplayFlag.SV_usDisplayTimer = C_Display10s;/*默认10S*/
    }

    GV_Str_DisplayFlag.SV_ucDisplayMode = C_CheckDisplay;
    GV_Str_DisplayFlag.ParaNum = V_ucDisScreenNum;

    V_uci = InF_Display_JudgeIDActive(GV_Str_DisplayFlag.CodeID,GV_Str_DisplayFlag.Related_CodeID,GV_Str_DisplayFlag.ParaNum);  /*安全性判断*/

    if ( C_OK != V_uci )
    {
        GV_Str_DisplayFlag.CodeID = C_DefaultDisDi;
        GV_Str_DisplayFlag.Related_CodeID = C_DefaultDisDiRelated;
        GV_Str_DisplayFlag.ParaNum = 0x00;
    }

    SF_FindDisChieseTableNo();        /*查找显示全局结构体，DI对应的汉字表格及行号*/
}
/*******************************************************************************
函数原型：void SF_DisplaySignMessage( Str_DisplayStatus *pV_ucBuffer, uchar8 V_ucSourceMesNum )
功能描述：字符显示处理，该函数把其他消息需要显示字符的参数，赋值为显示内部静态变量显示字符
输入参数：Str_DisplayStatus *pV_ucBuffer：状态字符显示变量 
		typedef struct 
		{ 
			ushort16 Time; 显示时间，最大不能大于65535/2秒，显示内部是500ms为基准 
			uchar8 Type；
		}Str_DisplayStatus;
	uchar8 V_ucSourceMesNum:源消息号
输出参数：无
返回参数：无
调用位置：
备    注：像费率、象限、信号强度同一时间只有一个显示，该类字符变量处理时，赋值其中一个，另外同类型
		则定时器清零,信号强度列表格时，上1级信号强度，包含下1级信号 
*******************************************************************************/                                        
void SF_DisplaySignMessage( Str_DisplayStatus *pV_ucBuffer, uchar8 V_ucSourceMesNum )
{
	 Str_DisplayStatus Str_Buffer;
	 Str_DisplaySignMesNum *pStr_DisplaySignMesNum;
	 ushort16 V_usDisTime = C_NotDisplayNiu;
	 uchar8 V_uci, V_ucj, V_ucSign, V_uck;

	 (Str_Buffer).Type=(*pV_ucBuffer).Type;
	 (Str_Buffer).Time=(*pV_ucBuffer).Time;
     
#if(0)
    typedef struct
    {
        ushort16 Time;/*Time：表示显示时间；*/
        uchar8 Type;  /*Type：显示字符与显示方式合用同一个字节，该字节的高两位表示显示方式*/
                 /*(01:闪烁；00：关闭；11常显,组合命令，当显示时间为0xFFFF时，表示常显，*/
                 /*有具体时间值时，显示时间按具体时间)，低6位表示表示显示字符内容(LED、继电器输出也作为一个字符)；*/
    }Str_DisplayStatus;
#endif	 
    V_ucSign = Str_Buffer.Type & 0x3F;   /*取低6位*/
	 
    switch ( Str_Buffer.Type&0xC0 )    /*取高2位*/
    {
        case C_TwinkleDisplay:                       /*闪烁*/
        {
            V_usDisTime = C_TwinkleDisplayNiu;
            break;
        }
        case C_NotDisplay:                       /*不显*/
        {
            V_usDisTime = C_NotDisplayNiu;
            break;
        }
        case C_AlwaysDisplay:                       /*常显或固定时间*/
        {
            if ( C_AlwaysDisplayNiu == (Str_Buffer).Time )   /*0xFFFF*/
            {
                V_usDisTime = C_AlwaysDisplayNiu;	 	  	 	  
            }	 	  	  
            else
            {
                V_usDisTime = (Str_Buffer).Time*2;	        /*最大不能大于65535/2秒，显示内部是500ms为基准*/
            }
            break;
        }
        default:
            V_usDisTime = C_NotDisplayNiu;
            break;
    }

    for ( V_uci = 0; V_uci < GV_Str_DisplaySignLen; V_uci++ )     /*状态指示字符，定时器处理*/
    {
        if ( V_ucSign == GV_Str_DisplaySign[V_uci].StateNum )
        {
            break;	 	  	 	   	 
        }
    }
    if ( V_uci >= GV_Str_DisplaySignLen )
    {
        return;                                  /*正常不存在*/	 	 	   
    }
	            
    pStr_DisplaySignMesNum = (Str_DisplaySignMesNum *)(GV_Str_DisplaySign[V_uci].PStr_DisplaySignMesNum);
    for ( V_ucj = 0; V_ucj < GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen; V_ucj++ )   /*需显示状态字符定时器处理*/
    {
        /*PV_Str_DisplaySignMesNum=(Str_DisplaySignMesNum *)(GV_Str_DisplaySign[V_uci].PStr_DisplaySignMesNum+V_ucj*sizeof(Str_DisplaySignMesNum));  */
        if ( V_ucSourceMesNum == pStr_DisplaySignMesNum[V_ucj].SourceNo )   /*需要操作定时器*/
        {
            pStr_DisplaySignMesNum[V_ucj].Timer = V_usDisTime;   
            break;
        }	 	     
    }
    if ( V_ucj >= GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen )
    {
        return;                                  /*正常不存在*/	 	 	   
    }
	 	 
    for ( V_uck = 0; V_uck < GV_Str_DisplaySignLen; V_uck++ )     /*其余互斥状态字符处理*/
    {
        if ( V_uck == V_uci )                               /*需显示状态字符定时器已处理*/
        {  
            continue;	 	   	   
        }
        else
        {
            pStr_DisplaySignMesNum = (Str_DisplaySignMesNum *)GV_Str_DisplaySign[V_uck].PStr_DisplaySignMesNum;
            switch ( GV_Str_DisplaySign[V_uck].StateNum )
            {
                case C_Q1Sign:                    /*象限处理*/
                case C_Q2Sign:
                case C_Q3Sign:
                case C_Q4Sign:
                {
                    if ( (C_Q1Sign == V_ucSign) || (C_Q2Sign == V_ucSign)     /*象限处理*/	 	   	  
                      || (C_Q3Sign == V_ucSign) || (C_Q4Sign == V_ucSign) )
                    {	 
                        for ( V_ucj = 0; V_ucj < GV_Str_DisplaySign[V_uck].Str_DisplaySignMesNumLen; V_ucj++)   /*需显示状态字符定时器处理*/
                        {
                            if ( V_ucSourceMesNum == pStr_DisplaySignMesNum[V_ucj].SourceNo )   /*需要操作定时器*/
                            {
                                pStr_DisplaySignMesNum[V_ucj].Timer = C_NotDisplayNiu;   
                                break;
                            }	 	     
                        }
                        if ( V_ucj >= GV_Str_DisplaySign[V_uck].Str_DisplaySignMesNumLen )	
                        {
                            return;                            /*正常不存在*/ 	                 	  
                        }	 	
                    }
                    break;
                }
#if(0)
                case C_Step1Sign:                    /*阶梯处理*/
                case C_Step2Sign:
                case C_Step3Sign:
                case C_Step4Sign:
                {
                    if ( (C_Step1Sign == V_ucSign) || (C_Step2Sign == V_ucSign)     	   	  
                      || (C_Step3Sign == V_ucSign) || (C_Step4Sign == V_ucSign) )  
                    {
                        for ( V_ucj = 0; V_ucj < GV_Str_DisplaySign[V_uck].Str_DisplaySignMesNumLen; V_ucj++ )   /*需显示状态字符定时器处理*/
                        {
                            if ( V_ucSourceMesNum == pStr_DisplaySignMesNum[V_ucj].SourceNo )   /*需要操作定时器*/
                            {
                                pStr_DisplaySignMesNum[V_ucj].Timer = C_NotDisplayNiu;   
                                break;
                            }	 	     
                        }
                        if ( V_ucj >= GV_Str_DisplaySign[V_uck].Str_DisplaySignMesNumLen )	
                        {
                            return;                            /*正常不存在*/ 	                 	   
                        }	 	
                    }
                    break;
                }  	
                case C_Rate1Sign:                    /*费率处理*/
                case C_Rate2Sign:
                case C_Rate3Sign:
                case C_Rate4Sign:
                {
                    if ( (C_Rate1Sign == V_ucSign) || (C_Rate2Sign == V_ucSign)     	   	  
                      || (C_Rate3Sign == V_ucSign) || (C_Rate4Sign == V_ucSign) )
                    {  
                        for ( V_ucj = 0; V_ucj < GV_Str_DisplaySign[V_uck].Str_DisplaySignMesNumLen; V_ucj++ )   /*需显示状态字符定时器处理*/
                        {
                            if ( V_ucSourceMesNum == pStr_DisplaySignMesNum[V_ucj].SourceNo )   /*需要操作定时器*/
                            {
                                pStr_DisplaySignMesNum[V_ucj].Timer = C_NotDisplayNiu;   
                                break;
                            }	 	     
                        }
                        if ( V_ucj >= GV_Str_DisplaySign[V_uck].Str_DisplaySignMesNumLen )	
                        {
                            return;                            /*正常不存在*/ 	                 	 
                        }	 	
                    }
                    break;
                }
#endif
	             
                case C_GPRSSignalSign1:                    /*信号强度处理*/
                case C_GPRSSignalSign2:
                case C_GPRSSignalSign3:
                case C_GPRSSignalSign4:
                {
                    if ( (C_GPRSSignalSign1 == V_ucSign) || (C_GPRSSignalSign2 == V_ucSign)     	   	  
                      || (C_GPRSSignalSign3 == V_ucSign) || (C_GPRSSignalSign4 == V_ucSign) )
                    {
                        for ( V_ucj = 0; V_ucj < GV_Str_DisplaySign[V_uck].Str_DisplaySignMesNumLen; V_ucj++ )   /*需显示状态字符定时器处理*/
                        {
                            if ( V_ucSourceMesNum == pStr_DisplaySignMesNum[V_ucj].SourceNo )   /*需要操作定时器*/
                            {
                                pStr_DisplaySignMesNum[V_ucj].Timer = C_NotDisplayNiu;   
                                break;
                            }	 	     
                        }
                        if ( V_ucj >= GV_Str_DisplaySign[V_uck].Str_DisplaySignMesNumLen )		
                        {
                            return;                            /*正常不存在*/	                  	 
                        } 	
                    }
                    break;
                } 
                default:
                    break;
            }
        }	 	    
    }
}
/*******************************************************************************
函数原型：void SF_DisplayDataSignDeal( uchar8 *pV_ucDisBuff )
功能描述：需要显示符号数据处理，包括表内温度、组合电能、组合需量、电流、功率、功率因数、当前需量，数据最高位为
		符号位，温度、电能、经度、高度、纬度显示“-”号，其余数据显示“反向”。符号显示缓存赋值在该函数内部处理, 
		同时数据项去除符号位 
输入参数：uchar8 *pV_ucDisBuff：需处理数据显示缓存
输出参数：无
返回参数：无
调用位置：
备    注：根据汉字表格第C_ChinaLineDataLenKillZero列第3位，判断该数据是否需要符号位处理，同时根据数据长度判断是
		否是电能类数据(当数据长度>=4时，且不是当前需量，则显示“-”)。
		剩余金额负号显示，也在该部分处理
*******************************************************************************/                                      
void SF_DisplayDataSignDeal( uchar8 *pV_ucDisBuff )              
{
    uchar8 *pV_ucChieseTable, V_ucDisDataSign, V_ucDataLen;
	 	 
    pV_ucChieseTable = (uchar8 * )(GV_Str_DisplayFlag.P_ChieseTableNo + GV_Str_DisplayFlag.ChieseTableLineNo * C_ChineseSignLen);  /*汉字表格结构体地址*/
    V_ucDisDataSign = (pV_ucChieseTable[C_ChinaLineDataLenKillZero] & C_NeedSignBit0x08);   		/*取待处理数据是否需要符号处理*/
	 
    if ( 0x00 != V_ucDisDataSign )  /*显示数据需要符号位处理*/
    {
        V_ucDataLen = (pV_ucChieseTable[C_ChinaLineDataLenKillZero] & C_GetChinaDataLenBit0x07);  /*取显示数据长度*/
        if ( ( V_ucDataLen > C_PreScreenDisDataLen ) || (0 == V_ucDataLen ) )
	 	{
			return;  /*正常不存在*/
	 	}
	 	
	 	if ( ( ( V_ucDataLen >= 4 ) && ( 0x01000000 != ( GV_Str_DisplayFlag.CodeID & 0xFF000000 ) ) )   	/*只有电量、经度、纬度、需量数据长度>=4，需量显示反向，其余显示负号*/
	 	  || ( CMeter_Temp == GV_Str_DisplayFlag.CodeID )                                 			/*表内温度处理*/
	 	  || ( CMeter_Position_High == GV_Str_DisplayFlag.CodeID ) )                              	/*高度*/     
	 	{
            /*电能8字节BCD与表格不一致*/
            if ( ( ( GV_Str_DisplayFlag.CodeID & 0xF0000F00) == 0x00000200 ) 
			  || ( ( GV_Str_DisplayFlag.CodeID & 0xF0000F00) == 0x00000400 ) 
			  || ( ( GV_Str_DisplayFlag.Related_CodeID & 0xF0000F00) == 0x00000200 ) 
			  || ( ( GV_Str_DisplayFlag.Related_CodeID & 0xF0000F00) == 0x00000400 ) )
            {
                V_ucDataLen = C_EnergyNature4BCDLen;
            }
		  
			if ( pV_ucDisBuff[V_ucDataLen - 1] & 0x80 )  						      /*取最高位*/
			{
				GV_ucDisplayData[22] |= C_DisNegativeSign;   					  /*"-"显示*/
				pV_ucDisBuff[V_ucDataLen-1] = pV_ucDisBuff[V_ucDataLen - 1] & 0x7F;     /*去除符号位*/
	 		}
	 	}
		else   /*其他类数据，需量，电流，功率，功率因数及视在功率*/
		{
            if ( ( pV_ucDisBuff[V_ucDataLen-1] & 0x80 )   							/*取最高位，并且数据不等于FF，数据为FF，不进行符号位处理*/
			  && ( 0xFF != pV_ucDisBuff[V_ucDataLen - 1]) )   						/*只有需量类数据,过结算日补数据可能为FF*/
            {
                GV_ucDisplayData[17] |= C_DisFanXiang;   						/*"反向"显示*/
                pV_ucDisBuff[V_ucDataLen - 1] = pV_ucDisBuff[V_ucDataLen - 1] & 0x7F; /*去除符号位*/
            }	 	  	 
        }	 	  
    }	
	 
    if ( COverDraft_Hex_Cent == GV_Str_DisplayFlag.CodeID ) 	 	/*当前透支金额显示"-"*/
    {
        GV_ucDisplayData[22] |= C_DisNegativeSign;   		/*"-"显示*/
    }
}
/*******************************************************************************
函数原型：void SF_DisplyMainData( uchar8 V_ucMoneySign )
功能描述：主屏幕数据显示处理,包含主显示数据、单位、小数点显示处理
输入参数：uchar8 V_ucMoneySign剩余金额、透支金额，购电前2s显示是否需特殊处理
输出参数：无
返回参数：无
调用位置：
备    注：
*******************************************************************************/
void SF_DisplyMainData( uchar8 V_ucMoneySign )
{
    uchar8  *pV_ucChieseTable;
    ulong32 V_ulDI32;
    uchar8  V_ucDisBuff[C_EnergyNature4BCDLen] = {0}, V_ucDot;
	 
    if ( C_ALLScreenDisplayDi == GV_Str_DisplayFlag.CodeID )         /*标识码为全FF*/
    {
        return;   	 
    }
	 
    SF_GetDisplayData(&V_ucDisBuff[0]);                             /*获取需要显示的数据，每屏显示需处理数据最大5个字节*/

    if ( V_ucMoneySign != C_MoneySign )
    {
        if ( GV_Str_DisplayFlag.CodeID == CChargeBal_Hex_Cent )
        {
            PF_CopyDataBytes(&V_ucDisBuff[0], &GV_RemainMoney[0][0], CLChargeBal_BCD);
        }
        if ( GV_Str_DisplayFlag.CodeID == COverDraft_Hex_Cent )
        {
            PF_CopyDataBytes(&V_ucDisBuff[0], &GV_RemainMoney[1][0], CLOverDraft_BCD);
        }   	 
    }
    else        /*取更新前剩余、透支金额*/
    {
        if ( GV_Str_DisplayFlag.CodeID == CChargeBal_Hex_Cent )
        {
            PF_CopyDataBytes(&GV_RemainMoney[0][0], &V_ucDisBuff[0], CLChargeBal_BCD);
        }
        if ( GV_Str_DisplayFlag.CodeID == COverDraft_Hex_Cent )
        {
            PF_CopyDataBytes(&GV_RemainMoney[1][0], &V_ucDisBuff[0], CLOverDraft_BCD);
        }   	    		
    }
	 
    SF_DisplayDataSignDeal(&V_ucDisBuff[0]);              			/*数据最高位，符号位处理；内部包括“-”显示*/
	 
    pV_ucChieseTable = (uchar8 *)(GV_Str_DisplayFlag.P_ChieseTableNo + GV_Str_DisplayFlag.ChieseTableLineNo * C_ChineseSignLen);   /*汉字表格结构体地址*/
    V_ucDot = pV_ucChieseTable[C_ChinaeseLineDot];          			/*取显示小数点位数*/

	if ( GV_Str_DisplayFlag.Related_CodeID != 0xFFFFFFFF ) 			/*读关联列表*/
	{
		V_ulDI32 = GV_Str_DisplayFlag.Related_CodeID;
		V_ulDI32 &= 0xffff0fff;
	}
    else
    {
        V_ulDI32 = GV_Str_DisplayFlag.CodeID;
    }

    if ( ( 0x00000000 == (V_ulDI32 & 0xF0000000 ) )
	  || ( CM_Com_Ac_Tol_En_0 == V_ulDI32 )
	  || ( CY_Com_Ac_Tol_En_0 == V_ulDI32 ) )     /*具体显示小数位，调整显示数据，返回最终显示数据小数点位数;*/
	{
		if ( ( 0x00000200 == (V_ulDI32 & 0xF000FF00 ) )
          || ( 0x00000400 == (V_ulDI32 & 0xF000FF00 ) ) )
		{
		  	V_ucDot = SF_EnDePointAdjust(&V_ucDisBuff[0]);      /*电能小数调整*/
		}
		else if ( ( CM_Com_Ac_Tol_En_0 == V_ulDI32 ) 
          || ( CY_Com_Ac_Tol_En_0 == V_ulDI32 ) )
		{
		  	V_ucDot = SF_EnDePointAdjust(&V_ucDisBuff[0]);      /*电能小数调整*/
		}
        else if ( CCom_Ac_LastPulse_FF_0 == (V_ulDI32 & 0xF000FF00) )
        {
			GV_KillZeroNum = C_KillZero3;
        }
	}
	else if ( ( 0x10000000 == (V_ulDI32&0xF0000000) ) && (0x01 == GV_Str_DisplayFlag.ParaNum) ) /*需量数据，需量需第3屏时，即需量数据才进行小数点处理*/
	{
		V_ucDot=SF_EnDePointAdjust(&V_ucDisBuff[0]);  /*需量小数调整*/
	    GV_KillZeroNum += C_KillZero2;
	}
    else
    {	                                                     	    
        SF_KillZeroDeal(&V_ucDisBuff[0],V_ucDot);       /*灭零处理*/ 
        GV_KillZeroNum += C_KillZero2;
    }
	 
    SF_DotDisplayDeal(V_ucDot);                      				/*小数点显示缓存数据处理*/

    SF_DisplayUnit(pV_ucChieseTable[C_ChinaeseLineUnit]);         /*单位显示处理函数*/ 
    
    /*主显示数据放缓存区*/
    memcpy(GV_ucDisplayData, V_ucDisBuff, 4);		/*主显示数据放缓存区*/
    GV_ucDisplayData[C_MainDataHig_offset] = V_ucDisBuff[C_MainDataEn_offset4];
    
    /*GV_DispAllScreenMode = 0;*/
}
/**********************************************************************************************************
函数原型：void SF_DisplayRealatedOAD_RateJudge( ulong32 V_ulOAD, uchar8 *pV_ucData, ushort16 *pV_usDataLen )
功能描述：显示调用，判断电能、需量、费率电价是否超费率数，超费率数显示为0                         
输入参数： V_ulOAD：电能、需量类输入OAD；                                                         
                   冻结、事件类输入关联OAD数据标识                                                
          pV_ucData：数据缓存地址，外面调用时注意大小                                                 
          pV_usDataLen:数据长度                                                                 
输出参数：pV_ucData：数据缓存地址，外面调用时注意大小                                                 
返回参数：无                                                                                                                                                                          
调用位置：                                                                                        
备    注：                                                                                        
************************************************************************************************************/                                         
void SF_DisplayRealatedOAD_RateJudge( ulong32 V_ulOAD, uchar8 *pV_ucData, ushort16 *pV_usDataLen )
{
    uchar8 V_ucOAD[C_DataCodeLen];
    uchar8 V_ucRateNum;
    
    PF_Ulong32ToBuffer4(V_ucOAD, &V_ulOAD, C_DataCodeLen);
	/*获取费率数*/
    V_ucRateNum = InF_RateNumChangeToHex();
    
    switch ( V_ucOAD[C_O_DI3] )
    {
        case 0x00:  /*电能类*/
        case 0x10:  /*需量类*/
        {
            /*判断费率数是否超，费率数超显示为0*/
            if ( V_ucOAD[C_O_DI0]  > (V_ucRateNum + 1) )     /*总+费率数，差1*/
            {
                memset(pV_ucData, 0x00, *pV_usDataLen);
            }
            
        }break;
        default:    /*原数据不处理*/
        {
            break;
        }
    }
}
/*******************************************************************************
函数原型：void SF_DisplayData_LastPulseDeal( uchar8 *pV_ucDisplayData )
功能描述：脉冲尾数数据读取为1字节Hex，但数据为0.0000XX 
输入参数：pV_ucDisplayData：数据缓存 
输出参数：pV_ucDisplayData：数据缓存
返回参数：
调用位置：
备    注：输入数据为1字节Hex；输出数据为BCD，5字节，最高位为符号位
*******************************************************************************/
#if(0)                                 
void SF_DisplayData_LastPulseDeal( uchar8 *pV_ucDisplayData )
{
    ulong32 V_ulData = 0;
    uchar8 V_ucBuffer[C_DisEnergyCommPulseLastLen] = {0}, V_ucDataLen;
    
    V_ucBuffer[0] = pV_ucDisplayData[0];
    V_ucDataLen = 4;
    
    if ( (pV_ucDisplayData[0] | 0x7F) == 0xFF )
    {
        V_ucBuffer[0] = (~V_ucBuffer[0]) + 1;
    }
    
    PF_Buffer4ToUlong32(V_ucBuffer, &V_ulData, V_ucDataLen);
    PF_HextoBCDBytes(&V_ulData, V_ucBuffer, &V_ucDataLen);

    if ( (pV_DisplayData[0] | 0x7F) == 0xFF )
    {
        V_ucBuffer[4] = 0x80;
    }
    
    PF_CopyDataBytes(V_ucBuffer, pV_ucDisplayData, C_DisEnergyCommPulseLastLen);
}
#endif
/***************************************************************************************************
函数原型：void SF_GetDisplayData( uchar8 *pV_ucDisplayData )                                                                        
功能描述: 显示主数据处理，返回截取后的需显示数据，最大5字节.精确电能                                                              
输入参数：uchar8 * pV_ucDisplayData:需显示数据缓存                                                                                                                  
输出参数：无                                                                                                                  
返回参数： 无                                                                                                                  
调用位置：                                                                                         
备    注：校表脉冲宽度固定值0x0080          
          波特率特征字（1字节,显示单独处理）,根据特征字，转化为具体显示值19200、2400等,3字节数据长度
***************************************************************************************************/   
void SF_GetDisplayData( uchar8 *pV_ucDisplayData )
{
	Str_Read_T Str_ReadRecord;
	Str_SuppInfo Str_SuppInfo;
    ulong64	V_ul64Data = 0;
    ulong32	V_ulDi32/*, V_ulTemp*/;
    ulong32	V_ulRelateOI[3];
    uchar8	*pV_ucChieseTable;
    ushort16 /*V_usDate = 0, Len = 255,*/ V_usLen = C_RAM_Max, V_usDataEncode;    
    ushort16	V_usDataLenMax = C_RAM_Max;
    uchar8	V_ucDisBuff[C_RAM_Max], V_ucTemp[20] = {0};
    uchar8	V_ucDi[5], V_ucReturn_Flag = C_OtherErr_DAR;
    uchar8	V_ucDataLen = C_RAM_Max,V_ucDataHexLen,V_ucChangeSign,V_ucChangeType;
    /*uchar8	V_ucDate = 0;
    uchar8	V_i,V_j;
    uchar8	V_ucDataLen  = C_RAM_Max;
	uchar8 	V_ucFreezeTime = 0;*/

    memset(V_ucDisBuff, 0x00, C_RAM_Max);	

    V_ulDi32 = GV_Str_DisplayFlag.CodeID;
    PF_Ulong32ToBuffer4(&V_ucDi[C_O_DI0], &V_ulDi32, 4);

     
    if ( ( 0x00 == ( V_ucDi[C_O_DI3] & 0xf0) )
	  && ( ( 0x02 == V_ucDi[C_O_DI1] ) || ( 0x04 == V_ucDi[C_O_DI1] ) ) )   				/*当前电量类*/
	{		
        if ( ( V_ulDi32 == 0x00110200 ) || ( V_ulDi32 == 0x00210200 ) 
          || ( V_ulDi32 == 0x00120200 ) || ( V_ulDi32 == 0x00220200 )
          || ( V_ulDi32 == 0x00130200 ) || ( V_ulDi32 == 0x00230200 ) )
        {
            V_ulDi32 = (V_ulDi32 & 0xFFFF00FF) | 0x00000401;	/*使用属性4读取*/
            /*V_ucReturn_Flag = InF_ReadEnergy_Protocol(V_ulDi32, &V_ucDisBuff[0], &V_ucDataLen, C_Format_BCD);*/   /*读电能相关数据*/
			V_ucReturn_Flag = InF_GetData_ObjectManage(V_ulDi32, &V_ucDisBuff[0], &V_usLen, &V_usDataEncode);
        }
        else
        {
            V_ulDi32 = (V_ulDi32 & 0xFFFF00FF) | 0x00000400;	/*使用属性4读取*/
            /*V_ucReturn_Flag = InF_ReadEnergy_Protocol(V_ulDi32, &V_ucDisBuff[0], &V_ucDataLen, C_Format_BCD);*/   /*读电能相关数据*/
			V_ucReturn_Flag = InF_GetData_ObjectManage(V_ulDi32, &V_ucDisBuff[0], &V_usLen, &V_usDataEncode);
			
			/*判断费率数是否超，费率数超显示为0*/
            if(V_ucReturn_Flag == C_OK)
            {
                SF_DisplayRealatedOAD_RateJudge(GV_Str_DisplayFlag.CodeID, &V_ucDisBuff[0], &V_usLen);
            }
        }
	}
    else if ( ( 0x00 == ( V_ucDi[C_O_DI3] & 0xf0 ) ) && ( 0x06 == V_ucDi[C_O_DI1] ) )   /*当前电量类，脉冲尾数*/
	{
		/*V_ucReturn_Flag = InF_ReadEnergy_Protocol(GV_Str_DisplayFlag.CodeID, &V_ucDisBuff[0], &V_ucDataLen, C_Format_HEX);*/   		/*读电能相关数据*/
		V_ucReturn_Flag = InF_GetData_ObjectManage(GV_Str_DisplayFlag.CodeID, &V_ucDisBuff[0], &V_usLen, &V_usDataEncode);
        
        /* 判断费率数是否超，费率数超显示为0 */
        if(V_ucReturn_Flag == C_OK)
        {
            /*SF_DisplayData_LastPulseDeal(&V_ucDisBuff[0]);
            V_usLen = C_DisEnergyCommPulseLastLen;*/
            SF_DisplayRealatedOAD_RateJudge(GV_Str_DisplayFlag.CodeID, &V_ucDisBuff[0], &V_usLen);
        }
	}
	else if ( 0x10 == ( V_ucDi[C_O_DI3] & 0xf0 ) )     								/*当前需量都是读取需量接口函数*/
	{
		/*V_ucReturn_Flag = InF_ReadDemand(GV_Str_DisplayFlag.CodeID, &V_ucDisBuff[0], V_ucDataLen);*/   /*需量统一9个字节*/
		V_ucReturn_Flag = InF_GetData_ObjectManage(GV_Str_DisplayFlag.CodeID, &V_ucDisBuff[0], &V_usLen, &V_usDataEncode);
        /*
		for ( V_j = 0; V_j < 3; V_j++)
		{
			if ( V_ucDisBuff[6+V_j] != 0 )
			{
				break;	
			}	
		}
		if ( V_j < 3 )
		{
			V_ucDisBuff[9] = 0x20;	
		}
        */
        if(V_ucReturn_Flag == C_OK)
        {
            /*判断费率数是否超，费率数超显示为0*/
            SF_DisplayRealatedOAD_RateJudge(GV_Str_DisplayFlag.CodeID, &V_ucDisBuff[0], &V_usLen);
        }

    }
	else if ( ( 0x20 == (V_ucDi[C_O_DI3] & 0xf0)) || ( 0x40 == (V_ucDi[C_O_DI3] & 0xf0 ) ) )		/*变量、参变量*/
	{
#if(0)
		if(0x20==V_ucDi[C_O_DI3])
		{
			if ( ( (0x2c == V_ucDi[2]) && (0x01 == V_ucDi[0]) )
			  || (0x2D == V_ucDi[2])
			  || (0x2E == V_ucDi[2])
			  || (0x31 == V_ucDi[2])
			  || (0x32 == V_ucDi[2]) )
			{
				/*V_ucReturn_Flag = InF_ReadEnergy_Protocol(GV_Str_DisplayFlag.CodeID, &V_ucDisBuff[0],&V_ucDataLen, C_Format_BCD);*/   /*读电能相关数据*/
				V_ucReturn_Flag = InF_GetData_ObjectManage(GV_Str_DisplayFlag.CodeID, &V_ucDisBuff[0], &V_usLen, &V_usDataEncode);
			}
			else
			{
			  	V_ucReturn_Flag = InF_Read_Data(GV_Str_DisplayFlag.CodeID, &V_ucDisBuff[0], &V_usLen, &V_usDataEncode);  
			}
		}
		else if ( GV_Str_DisplayFlag.CodeID == CPluse_Wide )                     /*校表脉冲宽度，取固定值*/
#endif
        if ( GV_Str_DisplayFlag.CodeID == CPluse_Wide )                     /*校表脉冲宽度，取固定值*/
       	{
       		V_ucDisBuff[0] = 0x80;
       		V_ucDisBuff[1] = 0x00;
       		V_ucReturn_Flag = C_OK;
       	}
		else
        {
		  	/*V_ucReturn_Flag = InF_Read_Data(GV_Str_DisplayFlag.CodeID, &V_ucDisBuff[0], &V_usLen, &V_usDataEncode);	*/
            V_ucReturn_Flag = InF_GetData_ObjectManage(GV_Str_DisplayFlag.CodeID, &V_ucDisBuff[0], &V_usLen, &V_usDataEncode);
#if(0)
			if ( (GV_Str_DisplayFlag.CodeID == CMeter_Position_Longitude) || (GV_Str_DisplayFlag.CodeID == CMeter_Position_Latitude) )
			{
				if ( V_ucReturn_Flag == C_OK )
				{
				 	if ( GV_Str_DisplayFlag.ParaNum != 0 )
					/*BCD转换*/
	       		 	V_ucDataLen = 1;
				 	V_ulTemp = V_ucDisBuff[GV_Str_DisplayFlag.SV_DisplayDataOff];
	       		 	PF_HextoBCDBytes(&V_ulTemp, &V_ucDisBuff[GV_Str_DisplayFlag.SV_DisplayDataOff], &V_ucDataLen);
				}	
			}	
			if ( GV_Str_DisplayFlag.CodeID == CMeter_Position_High )  /*电能表位置信息:高度*/   
			{
				if ( V_ucReturn_Flag == C_OK )
                {
                    /*数据翻转*/
                    V_ulTemp = PF_Buffer4ToUlong32_698(&V_ucDisBuff[0]);
                    /*BCD转换*/
                    V_ucDataLen = 4;
                    PF_HextoBCDBytes(&V_ulTemp, V_ucDisBuff, &V_ucDataLen);
				}
			}
#endif
            if( (GV_Str_DisplayFlag.CodeID & 0xFFFFFF00) == 0x40110200 )/*公共假日周不显示，时段表在低位*/
			{
				/*PF_CopyDataBytes(&V_ucDisBuff[2], &V_ucDisBuff[1], 3);*/
                V_ucDisBuff[0] = V_ucDisBuff[5];
                if ( V_ucDisBuff[3] == 0xFF )
                {
                	V_ucDisBuff[4] = 0xFF;
                }
				else if ( (V_ucDisBuff[3] == 0x00) && (V_ucDisBuff[2] == 0x00) && (V_ucDisBuff[1] == 0x00) )
				{
					V_ucDisBuff[4] = 0x00;
				}
                else
                {
                    /*V_ucDisBuff[4] = 0x20;*/
                }
                V_usLen -= 1;/*周不显示，长度减1*/
            }
            
            /*结算日、时区表数据高字节在前，特殊处理-数据按字节颠倒*/
            if( ( (GV_Str_DisplayFlag.CodeID & 0xFFFFFF00) == 0x41160200 )
              ||( (GV_Str_DisplayFlag.CodeID & 0xFFFFFF00) == 0x40140200 )
              ||( (GV_Str_DisplayFlag.CodeID & 0xFFFFFF00) == 0x40150200 ) )
            {
                PF_OneDataReversed(V_ucDisBuff, V_ucDisBuff, (uchar8)V_usLen);
            }
            
            /*时段表、阶梯结算日数据高字节在前，特殊处理-每3字节颠倒*/
            if( ( (GV_Str_DisplayFlag.CodeID & 0xFFFFFF00) == 0x40160200 )
             || ( (GV_Str_DisplayFlag.CodeID & 0xFFFFFF00) == 0x40170200 ) 
             || ( GV_Str_DisplayFlag.CodeID == 0x401A0203 )
             || ( GV_Str_DisplayFlag.CodeID == 0x401B0203 ) )
            {
                V_ucDataLen = 3;
                PF_OneDataReversed(&V_ucDisBuff[GV_Str_DisplayFlag.SV_DisplayDataOff], &V_ucDisBuff[GV_Str_DisplayFlag.SV_DisplayDataOff], V_ucDataLen);
            }
		}
    }
	else if ( 0x30 == (V_ucDi[C_O_DI3] & 0xf0 ) )										/*事件记录*/
	{
		if ( ( GV_Str_DisplayFlag.Related_CodeID) != 0xFFFFFFFF )					/*有关联属性*/
   		{
			V_ucDi[4] = GV_Str_DisplayFlag.ParaNum;
   			  	 	  	 	  	       			
   			PF_Buffer4ToUlong32(V_ucDi, V_ulRelateOI, 4);
        	V_ulRelateOI[1] = GV_Str_DisplayFlag.Related_CodeID;
			V_ulRelateOI[2] = 0xFFFFFFFF;	
            
			V_ucReturn_Flag = Inf_ReadEventRenew(&V_ulRelateOI[0], &V_ucDisBuff[0], &V_ucDataLen);    /*读事件记录接口函数*/
            V_usLen = V_ucDataLen;
            
			if ( V_ucReturn_Flag != C_OK )
			{
                /*V_usDate = C_RAM_Max;
  	            V_ucReturn_Flag = InF_ReadEventData(V_ulRelateOI, &V_ucDate, &V_ucDisBuff[0], &V_ucDate, &V_usDate, 0x68); */
				Str_ReadRecord.pV_ulROAD = &V_ulRelateOI[0];
                V_ucTemp[0] = 9;/*方法9*/
                V_ucTemp[1] = V_ucDi[C_O_DI0];/*读取上几次*/
				Str_ReadRecord.pV_ucRST = &V_ucTemp[0];
				Str_ReadRecord.V_usROAD_Num = 1;/*关联属性1个*/
				Str_ReadRecord.V_ucReadMode = 3;/*显示模块读取*/
				Str_ReadRecord.V_ucChannelNo = 0xFF;/*非通信读取*/
				Str_SuppInfo.pV_usEncode = &V_usDataEncode;
				V_ucReturn_Flag = InF_GetData_Record(&Str_ReadRecord, &V_ucDisBuff[0], &V_usLen, &Str_SuppInfo);
			}
            if ( V_ucReturn_Flag == C_OK )
            {
                /*判断费率数是否超，费率数超显示为0*/
                SF_DisplayRealatedOAD_RateJudge(GV_Str_DisplayFlag.Related_CodeID, &V_ucDisBuff[0], &V_usDataLenMax);
#if(0)
				if ( ( V_ucDisBuff[GV_Str_DisplayFlag.SV_DisplayDataOff] == C_NotSupportAOD_Data)   /*没有数据默认零、潮流反向事件特殊00000000AAAAAAAA*/
				  || ( ( V_ucDisBuff[0] == C_NotSupportAOD_DataBB ) && ( V_usDate == CL_NotSupportAOD_DataBB ) ) )
#endif
				if(Str_SuppInfo.V_ucFrameNum == 0)
				{
					memset(V_ucDisBuff, 0x00, V_usLen);
				}
				
                if ( (GV_Str_DisplayFlag.Related_CodeID & 0xFF000000) == 0x00000000 )			/*读关联列表*/
                {
                    if ( (GV_Str_DisplayFlag.Related_CodeID & 0x00000F00) == 0x00000200 )		/*事件数据为2位小数电能，设置显示位数为4位小数电能，后两位补0*/
                    {
                        /*
						if ( (V_ucDisBuff[0] | 0x7F) == 0xFF )
						{
							PF_Buffer8ToUlong64_698(V_ucDisBuff, &V_ul64Data, C_EnergyNature2HEXLen);
							V_ul64Data |= 0xFFFFFFFF00000000;
							V_ul64Data = (~V_ul64Data) + 1;
							V_ul64Data *= 100;
							V_ucDataLen = C_EnergyNature4BCDLen;
							PF_Hex64toBCDBytes(&V_ul64Data, V_ucDisBuff, &V_ucDataLen);
							V_ucDisBuff[C_EnergyNature4BCDLen - 1] |= 0x80;
						}
						else
						{
							PF_Buffer8ToUlong64_698(V_ucDisBuff, &V_ul64Data, C_EnergyNature2HEXLen);
							V_ul64Data *= 100;
							V_ucDataLen = C_EnergyNature4BCDLen;
							PF_Hex64toBCDBytes(&V_ul64Data, V_ucDisBuff, &V_ucDataLen);						
						}
                        */
                        PF_Buffer8ToUlong64(V_ucDisBuff, &V_ul64Data, C_EnergyNature2HEXLen);
                        V_ul64Data *= 100;
                        PF_Ulong64ToBuffer8(V_ucDisBuff, &V_ul64Data, C_EnergyNature4HEXLen);
                        V_usLen = C_EnergyNature4HEXLen;
                    }
#if(0)
					else if ( ( GV_Str_DisplayFlag.Related_CodeID & 0x00000F00) == 0x00000400 )
					{

						if ( (V_ucDisBuff[0] | 0x7F) == 0xFF )
						{
							PF_Buffer8ToUlong64_698(V_ucDisBuff, &V_ul64Data, C_EnergyNature4HEXLen);
							V_ul64Data |= 0xFFFFFF0000000000;
							V_ul64Data = (~V_ul64Data) + 1;
							V_ucDataLen = C_EnergyNature4BCDLen;
							PF_Hex64toBCDBytes(&V_ul64Data, V_ucDisBuff, &V_ucDataLen);
							V_ucDisBuff[C_EnergyNature4BCDLen - 1] |= 0x80;
						}
						else
						{
							PF_Buffer8ToUlong64_698(V_ucDisBuff, &V_ul64Data, C_EnergyNature4HEXLen);
							V_ucDataLen = C_EnergyNature4BCDLen;
							PF_Hex64toBCDBytes(&V_ul64Data, V_ucDisBuff, &V_ucDataLen);
						}
					}
                    else if( (GV_Str_DisplayFlag.Related_CodeID & 0x00000F00) == CCom_Ac_LastPulse_FF_0 )		/*脉冲尾数*/
                    {
                        SF_DisplayData_LastPulseDeal(&V_ucDisBuff[0]);
                        Len = C_DisEnergyCommPulseLastLen;
                    }
#endif
                }
#if(0)				
                else if ( (GV_Str_DisplayFlag.Related_CodeID & 0xFF000000) == 0x10000000 )
                {
                    PF_CopyDataBytes(V_ucDisBuff,V_ucTemp,8);
                    PF_CopyDataBytes(V_ucTemp,V_ucDisBuff+1,8);
                    *V_ucDisBuff = 0;
                }

				else if ( (GV_Str_DisplayFlag.Related_CodeID & 0XFFFFff00) == 0x20220200 )			/*事件记录的序号为BCD，次数应该减1*/
				{
					PF_Buffer4ToUlong32(V_ucDisBuff,&V_ulTemp,4);
					if ( V_ulTemp!=0 )
					{
						V_ucTemp[0] = 1;
						memset(&V_ucTemp[1],0x00,3);
						PF_BCDDECBytes(V_ucDisBuff, V_ucTemp, V_ucDisBuff, 4);
					}
				}
				else if ( ( GV_Str_DisplayFlag.Related_CodeID == 0x201E0200 )					/*事件发生、结束时间直接7字节转BCD*/
                  || ( GV_Str_DisplayFlag.Related_CodeID == 0x20200200 ) )
				{
					V_ucDisBuff[6] = 0x20;
				}
#endif
            }
   		}
   		else/*没有关联属性*/
   		{
            
   			PF_Buffer4ToUlong32(V_ucDi, V_ulRelateOI, 4);
            V_ulRelateOI[1] = 0xFFFFFFFF;

			if ( ( (V_ucDi[2] <= 0x08) || (V_ucDi[2] == 0x0B) )
			  && ( (V_ucDi[1] == 10) || (V_ucDi[1] == 14) ) )/*类24,属性10，当前值记录表*/
			{
				if ( V_ulRelateOI[0]==0x30000a01 )/*总累计次数和累计时间，需要转换标识码特殊处理*/
				{
					V_ulRelateOI[0] = 0x30000D01;/*失压总次数*/
					V_ucReturn_Flag = Inf_ReadEventRenew(&V_ulRelateOI[0], &V_ucDisBuff[0], &V_ucDataLen);
					V_ulRelateOI[0] = 0x30000D02;/*失压累计时间*/
					V_ucReturn_Flag = Inf_ReadEventRenew(&V_ulRelateOI[0], &V_ucDisBuff[4], &V_ucDataLen);
                    V_usLen = V_ucDataLen;
				}
				else if ( V_ulRelateOI[0]==0x30000E01 )
				{
					V_ulRelateOI[0] = 0x30000D03;/*发生时间*/
					V_ucReturn_Flag = Inf_ReadEventRenew(&V_ulRelateOI[0], &V_ucDisBuff[0], &V_ucDataLen);
					V_ulRelateOI[0] = 0x30000D04;/*结束时间*/
					V_ucReturn_Flag = Inf_ReadEventRenew(&V_ulRelateOI[0], &V_ucDisBuff[7], &V_ucDataLen);
                    V_usLen = V_ucDataLen;
				}
				else
				{
					V_ucReturn_Flag = Inf_ReadEventCurrentData(V_ulRelateOI[0], &V_ucDisBuff[0], &V_ucDataLen);
                    V_usLen = V_ucDataLen;
					if ( (V_ucReturn_Flag == C_IDError) )
					{
                        V_ucReturn_Flag = InF_GetData_ObjectManage(GV_Str_DisplayFlag.CodeID, &V_ucDisBuff[0], &V_usLen, &V_usDataEncode);
					}
					if ( V_ucDisBuff[GV_Str_DisplayFlag.SV_DisplayDataOff] == 0xAA )   /*没有数据默认零、潮流反向事件00000000AAAAAAAA*/
					{
                        memset(V_ucDisBuff, 0x00, V_usLen);
					}
				}
			}
			else if ( ( (V_ucDi[2] >= 0x0c) || (V_ucDi[2] == 0x09) || (V_ucDi[2] == 0x0A) )
			  && (V_ucDi[1] == 7) )/*类7,属性7，当前值记录表(9个字节)*/
			{
				V_ucReturn_Flag = Inf_ReadEventCurrentData(V_ulRelateOI[0], &V_ucDisBuff[0], &V_ucDataLen);
                V_usLen = V_ucDataLen;
				if ( (V_ucReturn_Flag == C_IDError) )
				{
					V_ucReturn_Flag = InF_GetData_ObjectManage(GV_Str_DisplayFlag.CodeID, &V_ucDisBuff[0], &V_usLen, &V_usDataEncode);
				}
			}
			else
			{
                V_ucReturn_Flag = Inf_ReadEventRenew(&V_ulRelateOI[0], &V_ucDisBuff[0], &V_ucDataLen);    /*读事件记录接口函数*/
                V_usLen = V_ucDataLen;
			
                if ( V_ucReturn_Flag != C_OK )
                {
                    V_ucReturn_Flag = InF_GetData_ObjectManage(GV_Str_DisplayFlag.CodeID, &V_ucDisBuff[0], &V_usLen, &V_usDataEncode);	
                }
                if ( V_ucDisBuff[0] == 0xAA )   /*没有数据默认零*/
                {
                    memset(V_ucDisBuff, 0x00, V_usLen);
                }
            } 
        } 
/**************待调试************************/
#if(0)
		/*累计时间为HEX格式，需要转换成BCD格式*/
		if ( (V_ucDi[2]<=0x08) || (V_ucDi[2]==0x0B) )/*类24*/
		{
			if ( (V_ucDi[1] == 0x0A) )
			{
				PF_Buffer4ToUlong32(&V_ucDisBuff[4], &V_ulDi32,4);
				V_ucDataLen = 4;
				PF_HextoBCDBytes( &V_ulDi32, &V_ucDisBuff[4], &V_ucDataLen); /*事件累计时间数据层hex格式，转换成BCD格式*/
			}
            else if ( (V_ucDi[1] == 0x0D) && (V_ucDi[0] == 2) )
            {
                
                PF_Buffer4ToUlong32(&V_ucDisBuff[0], &V_ulDi32, 4);
				V_ucDataLen = 4;
				PF_HextoBCDBytes( &V_ulDi32, &V_ucDisBuff[0], &V_ucDataLen); /*事件累计时间数据层hex格式，转换成hex格式*/

            }
		}
		else
		{
			if ( V_ucDi[1] == 0x07 )/*类7*/
			{
                
				PF_Buffer4ToUlong32(&V_ucDisBuff[5], &V_ulDi32,4);
				V_ucDataLen = 4;
				PF_HextoBCDBytes(&V_ulDi32, &V_ucDisBuff[5], &V_ucDataLen);
                 /*事件累计时间数据层hex格式，转换成hex格式*/
			}
		}
#endif
/**************************************/
    }	 
	else if ( 0x50 == (V_ucDi[C_O_DI3] & 0xf0 ) )										/*冻结*/	
	{
		V_ucDi[4] = GV_Str_DisplayFlag.ParaNum;
  	       			  	 	  	 	  	       			
  	    PF_Buffer4ToUlong32(V_ucDi, V_ulRelateOI, 4);
        V_ulRelateOI[1] = GV_Str_DisplayFlag.Related_CodeID;
		V_ulRelateOI[2] = 0xFFFFFFFF;		
		
		Str_ReadRecord.pV_ulROAD = &V_ulRelateOI[0];
        V_ucTemp[0] = 9;/*方法9*/
        V_ucTemp[1] = V_ucDi[C_O_DI0];/*读取上几次*/
        Str_ReadRecord.pV_ucRST = &V_ucTemp[0];
		Str_ReadRecord.V_usROAD_Num = 1;/*关联属性1个*/
		Str_ReadRecord.V_ucReadMode = 3;/*显示模块读取*/
		Str_ReadRecord.V_ucChannelNo = 0xFF;/*非通信读取*/
		Str_SuppInfo.pV_usEncode = &V_usDataEncode;
		V_ucReturn_Flag = InF_GetData_Record(&Str_ReadRecord, &V_ucDisBuff[0], &V_usLen, &Str_SuppInfo);
  	    /*V_ucReturn_Flag = InF_ReadFreezeData(V_ulRelateOI,&V_ucDate, &V_ucDisBuff[0], &V_usDate, &Len, V_ucDate, &V_ucFreezeTime,C_698Mode);*/ 
		if ( V_ucReturn_Flag == C_OK )
		{
            /*判断费率数是否超，费率数超显示为0*/
            SF_DisplayRealatedOAD_RateJudge(GV_Str_DisplayFlag.Related_CodeID, &V_ucDisBuff[0], &V_usDataLenMax);
            
			if( ( GV_Str_DisplayFlag.Related_CodeID & 0xFF000000) != 0x00000000 )
			{
				if ( V_ucDisBuff[0] == 0xAA )
				{
					memset(V_ucDisBuff, 0x00, V_usLen);			/*需量最大8个字节*/
				}
			}

            if ( ( GV_Str_DisplayFlag.Related_CodeID & 0xFF000000) == 0x00000000 )		/*读关联列表*/
            {
				
                if ( ( GV_Str_DisplayFlag.Related_CodeID & 0x00000F00) == 0x00000200 )	/*冻结数据为2位小数电能，设置显示位数为4位小数电能，后两位补0*/
                {
                    /*
					if ( (V_ucDisBuff[0] | 0x7F) == 0xFF )
					{
						PF_Buffer8ToUlong64_698(V_ucDisBuff, &V_ul64Data, C_EnergyNature2HEXLen);
						V_ul64Data |= 0xFFFFFFFF00000000;
						V_ul64Data = (~V_ul64Data) + 1;
						V_ul64Data *= 100;
						V_ucDataLen = C_EnergyNature4BCDLen;
						PF_Hex64toBCDBytes(&V_ul64Data, V_ucDisBuff, &V_ucDataLen);
						V_ucDisBuff[C_EnergyNature4BCDLen - 1] |= 0x80;
					}
					else
					{
						PF_Buffer8ToUlong64_698(V_ucDisBuff, &V_ul64Data, C_EnergyNature2HEXLen);
						V_ul64Data *= 100;
						V_ucDataLen = C_EnergyNature4BCDLen;
						PF_Hex64toBCDBytes(&V_ul64Data, V_ucDisBuff, &V_ucDataLen);						
					}
                    */
                    PF_Buffer8ToUlong64(V_ucDisBuff, &V_ul64Data, C_EnergyNature2HEXLen);
                    V_ul64Data *= 100;
                    PF_Ulong64ToBuffer8(V_ucDisBuff, &V_ul64Data, C_EnergyNature4HEXLen);
                    V_usLen = C_EnergyNature4HEXLen;
                    
                }
 #if(0)               
				else if ( ( GV_Str_DisplayFlag.Related_CodeID & 0x00000F00) == 0x00000400 )
				{
					if ( (V_ucDisBuff[0] | 0x7F) == 0xFF )
					{
						PF_Buffer8ToUlong64_698(V_ucDisBuff, &V_ul64Data, C_EnergyNature4HEXLen);
						V_ul64Data |= 0xFFFFFF0000000000;
						V_ul64Data = (~V_ul64Data) + 1;
						V_ucDataLen = C_EnergyNature4BCDLen;
						PF_Hex64toBCDBytes(&V_ul64Data, V_ucDisBuff, &V_ucDataLen);
						V_ucDisBuff[C_EnergyNature4BCDLen - 1] |= 0x80;
					}
					else
					{
						PF_Buffer8ToUlong64_698(V_ucDisBuff, &V_ul64Data, C_EnergyNature4HEXLen);
						V_ucDataLen = C_EnergyNature4BCDLen;
						PF_Hex64toBCDBytes(&V_ul64Data, V_ucDisBuff, &V_ucDataLen);
					}
				}
                else if ( (GV_Str_DisplayFlag.Related_CodeID & 0x00000F00) == CCom_Ac_LastPulse_FF_0 )		/*脉冲尾数*/
                {
                    SF_DisplayData_LastPulseDeal(&V_ucDisBuff[0]);
                    Len = C_DisEnergyCommPulseLastLen;
                }
#endif
            }
#if(0)
            else if ( (GV_Str_DisplayFlag.Related_CodeID & 0XFF000000) == 0x10000000 )
            {
                PF_CopyDataBytes(V_ucDisBuff, V_ucTemp, 8);
                PF_CopyDataBytes(V_ucTemp, V_ucDisBuff+1, 8);
				if ( SF_JugeDemadFF(V_ucDisBuff, CLPos_Ac_Tol_De_0) == C_OK )
				{
                	*V_ucDisBuff = 0xFF;
				}
				else
				{
                	*V_ucDisBuff = 0;
				}
            }
            else if ( (GV_Str_DisplayFlag.Related_CodeID&0XFFFFff00) == 0x20230200 )/*冻结序号hex码,要减1*/
            {
                PF_Buffer4ToUlong32(V_ucDisBuff, &V_ulTemp, 4);
                if ( V_ulTemp != 0 )
                {
                    V_ulTemp -= 1;
                    V_ucDataLen = 4;
                    PF_HextoBCDBytes(&V_ulTemp, V_ucDisBuff, &V_ucDataLen);
                }
            }
            else if ( GV_Str_DisplayFlag.Related_CodeID == 0x20210200 )/*冻结显示时间*/
			{
				V_ucDisBuff[6] = 0X20;
			}
#endif
        }
    }
	else if ( 0xF0 == (V_ucDi[C_O_DI3]&0xf0) )
	{  
	  	/*V_ucReturn_Flag = InF_Read_Data(GV_Str_DisplayFlag.CodeID,&V_ucDisBuff[0],&V_usLen, &V_usDataEncode);*/	
		V_ucReturn_Flag = InF_GetData_ObjectManage(GV_Str_DisplayFlag.CodeID, &V_ucDisBuff[0], &V_usLen, &V_usDataEncode);

		if ( 0xF2000200 == (GV_Str_DisplayFlag.CodeID&0xFF00FF00) )  /*波特率特征字（1字节）*/         	   
		{
            V_ucDisBuff[2] = 0x00;
            switch ( V_ucDisBuff[0] )
            {
                case 0:
                {
                    V_ucDisBuff[1] = 0x03;
                    break;
                } 
                case 1:
                {
                    V_ucDisBuff[1] = 0x06;
                    break;
                } 
                case 2:
                {
                    V_ucDisBuff[1] = 0x12;
                    break;
                }
                case 3:
                {
                    V_ucDisBuff[1] = 0x24;
                    break;
                } 
                case 4:
                {
                    V_ucDisBuff[1] = 0x48;
                    break;
                }
                case 6:
                {
                    V_ucDisBuff[1] = 0x96;
                    break;
                }
                case 7:
                {
                    V_ucDisBuff[1] = 0x92;
                    V_ucDisBuff[2] = 0x01;
                    break;
                }
                case 8:
                {
                    V_ucDisBuff[1] = 0x84;
                    V_ucDisBuff[2] = 0x03;
                    break;
                }

                default:
                {
                    V_ucDisBuff[1] = 0x96;	/*默认9600*/
                }
            } 
		}
		V_ucDisBuff[0] = 0x00;                      	  
	}

	if ( (C_OK != V_ucReturn_Flag) && (C_CrcErr_DataZero != V_ucReturn_Flag) )  /*正常不存在*/
	{
        memset(&V_ucDisBuff[GV_Str_DisplayFlag.SV_DisplayDataOff], 0, 8);
		return;
	}
   
	 /************以下数据截取处理***************/
    if ( GV_Str_DisplayFlag.SV_DisplayDataOff >= C_RAM_Max )   /*数据溢出，正常不存在*/
    {
        return;	 	 
    }
	
    pV_ucChieseTable = (uchar8 * )(GV_Str_DisplayFlag.P_ChieseTableNo + GV_Str_DisplayFlag.ChieseTableLineNo * C_ChineseSignLen);  /*汉字表格结构体地址*/
    V_ucDataLen = pV_ucChieseTable[C_ChinaLineDataLenKillZero] & C_GetChinaDataLenBit0x07;   /*取低4位显示数据长度*/
    V_ucChangeSign = pV_ucChieseTable[C_ChinaLineDataLenKillZero] & C_NeedSignBit0x08;   /*数据是否带符号*/
    V_ucChangeType = pV_ucChieseTable[C_ChinaeseLineUnit] & 0xF0;/*数据转换类型*/
    
	 
    if ( V_ucDataLen > C_PreScreenDisDataLen )                  /*数据溢出，正常不存在*/
    {
        return;	 	  
    }
    if ( (GV_Str_DisplayFlag.SV_DisplayDataOff + V_ucDataLen) >= C_RAM_Max )  /*要读数据溢出，正常不存在*/
    {
        return;
    }
	 
	 /*电能8字节BCD与表格不一致*/
    if ( ( ( GV_Str_DisplayFlag.CodeID & 0xF0000F00) == 0x00000200 ) 
      || ( ( GV_Str_DisplayFlag.CodeID & 0xF0000F00) == 0x00000400 ) 
      || ( ( GV_Str_DisplayFlag.Related_CodeID & 0xF0000F00) == 0x00000200 ) 
      || ( ( GV_Str_DisplayFlag.Related_CodeID & 0xF0000F00) == 0x00000400 ) )
    {
        V_ucDataLen = C_EnergyNature4BCDLen;
    }
    
    PF_Ushort16ToBuffer2(V_ucTemp, &V_usLen);
    V_ucDataHexLen = (V_ucTemp[0] - GV_Str_DisplayFlag.SV_DisplayDataOff);
	 
    /*PF_CopyDataBytes(&V_ucDisBuff[GV_Str_DisplayFlag.SV_DisplayDataOff], pV_ucDisplayData, V_ucDataLen);*/    /*数据拷贝*/
    SF_DispDataChange(&V_ucDisBuff[GV_Str_DisplayFlag.SV_DisplayDataOff], pV_ucDisplayData, V_ucDataHexLen, V_ucDataLen, V_ucChangeSign, V_ucChangeType);
}
/*******************************************************************************
函数原型：uchar8 SF_EnBorrowPoint( ulong32 V_ulOAD, uchar8 *pV_ucDisplayData )
功能描述：电能借位显示判断及处理
输入参数：V_ulOAD:标识码；pV_ucDisplayData借位调整后数据
输出参数：无
返回参数：借位后可显示的小数位数
调用位置：
备    注：1）输入数据是5字节HEX，无符号, 查看是否超显示范围，超显示范围后，借位显示
             6+4=7+3=8+2=9+1=10+0；
          2)大于999999.9999，借1位
            大于9999999.9999，借2位
            大于99999999.9999，借3位
*******************************************************************************/
uchar8 SF_EnBorrowPoint( ulong32 V_ulOAD, uchar8 *pV_ucDisplayData )
{
    ulong64 V_ullEnData = 0;
	ushort16 V_usLen, V_usDataEncode;
    uchar8 V_ucDot, V_ucDotOld = C_PreEnDisPoint, V_ucReturn;

    PF_Buffer8ToUlong64(pV_ucDisplayData, &V_ullEnData, C_EnergyNature4BCDLen);
    
    if ( V_ullEnData > C_EnBorrowPoint_Flag_4 )
    {
        V_ucDot = C_EnBorrowPoint_4;
    }
    else if ( V_ullEnData > C_EnBorrowPoint_Flag_3 )
    {
        V_ucDot = C_EnBorrowPoint_3;
    }
    else if ( V_ullEnData > C_EnBorrowPoint_Flag_2 )
    {
        V_ucDot = C_EnBorrowPoint_2;
    }
    else if ( V_ullEnData > C_EnBorrowPoint_Flag_1 )
    {
        V_ucDot = C_EnBorrowPoint_1;
    }
    else
    {
        V_ucDot = C_EnBorrowPoint_0;
    }
	
    V_usLen = CLDisplayBorrowPoint_RecFlag;
    V_ucReturn = InF_Read_Data(CDisplayBorrowPoint_RecFlag, &V_ucDotOld, &V_usLen, &V_usDataEncode); 
    if ( V_ucReturn == C_OK )
	{
        if ( V_ucDot > V_ucDotOld )
		{
            InF_Write_Data(C_Msg_Display, CDisplayBorrowPoint_RecFlag, &V_ucDot, (uchar8)V_usLen, C_W_SafeFlag);
		}
	} /*else 不处理循显开始会清*/
    
    V_usLen = CLDisplayBorrowPoint;
    V_ucReturn = InF_Read_Data(CDisplayBorrowPoint, &V_ucDotOld, &V_usLen, &V_usDataEncode); 
    if ( V_ucReturn == C_OK )
	{
        if ( V_ucDot > V_ucDotOld )
		{
            V_ucDotOld = V_ucDot;
            InF_Write_Data(C_Msg_Display, CDisplayBorrowPoint, &V_ucDot, (uchar8)V_usLen, C_W_SafeFlag);
		}
	}
	else
	{	
		V_ucDotOld = 0;
	}
    
    V_ucDotOld = C_PreEnDisPoint - V_ucDotOld;
    
    return V_ucDotOld;       
}
/*******************************************************************************
函数原型：uchar8 SF_EnDePointAdjust( uchar8 *pV_ucDisplayData )
功能描述：电量、需量小数位数处理，根据数据层存储显示小数位数，调整显示数据，同时返回需要显示的小数位数
输入参数：uchar8 *pV_ucDisplayData:根据小数点位数，调整后的数据缓
输出参数：无
返回参数：uchar8:返回显示的小数位数；0：表示无小数点，1：表示1个小数点，。。。
调用位置：
备    注：电量、需量类第1屏需量，数据函数内部进行高位灭零处理，列电量类汉字表格时，定义高位不作灭零处理.
          同时该函数中对当前透支金额及当前剩余金额不做处理.对全局变量灭零个数，进行处理，得到该数据灭零个数
          当需量显示4位小数时，进行四舍五入判断 
         判断在进位小数显示的条件下，当前显示小数位和LCD参数小数位数的关系，优先按照LCD参数小数位数显示
        （LCD参数小数位数需比进位后的小数位小，若比它大则还是按照进位后小数位显示）
*******************************************************************************/
uchar8 SF_EnDePointAdjust( uchar8 *pV_ucDisplayData )
{
	ulong64 V_ul64Data, V_ul64Compare;
	ulong32 V_ulDemand32 = 0, V_ulDI32;
	ushort16 V_usLen, V_usDataEncode;
    uchar8  V_uci, V_ucj, V_ucDot/*, V_ucBuffer*/;
	/*uchar8  V_DeBuff[3] = {0};*/
    uchar8  V_ucBorrowPoint;
	
    if ( GV_Str_DisplayFlag.Related_CodeID != 0xFFFFFFFF )    /*读关联列表*/
	{
        V_ulDI32 = GV_Str_DisplayFlag.Related_CodeID;
		V_ulDI32 &= 0xffff0fff;
	}
	else
	{
		V_ulDI32 = GV_Str_DisplayFlag.CodeID;
	}
    
   
    if ( ( 0x00000000 == (V_ulDI32 & 0xFF000000 ) ) 
      || ( CM_Com_Ac_Tol_En_0 == V_ulDI32 ) 
      || ( CY_Com_Ac_Tol_En_0 == V_ulDI32 ) )   /*电量数据*/     
    {
        if ( ( CChargeBal_Hex_Cent == V_ulDI32 ) || ( COverDraft_Hex_Cent == V_ulDI32 ) )   /*当前透支金额及当前剩余金额，正常不会执行*/
        {
            V_ucDot = C_DotNum_2;      /*2位小数*/
            return V_ucDot;	 	  	 
        }
  	  
        V_usLen = CLEnergy_Decimal_Num;
	 	V_uci = InF_Read_Data(CEnergy_Decimal_Num, &V_ucDot, &V_usLen, &V_usDataEncode);		/*显示电能小数位数*/
		
		if ( 0x00000000 == (V_ulDI32 & 0xFF000000 ) )
		{
			V_ucBorrowPoint = SF_EnBorrowPoint(V_ulDI32, pV_ucDisplayData);         /*获取借位后可显示小数位数*/
					
			if ( V_ucDot > V_ucBorrowPoint )     /*借位后实际能显示的小数位数<参数中显示电能小数位数，按借位的显示*/
			{
				V_ucDot = V_ucBorrowPoint;
			}
		}
		else
		{
			;   /*月度用电量，采用设置的小数位数*/
		}
		
		PF_Buffer8ToUlong64(pV_ucDisplayData, &V_ul64Data, C_EnergyNature4BCDLen);
        
        switch( V_ucDot ) 
        {
	 	  	 case C_DotNum_4:           /*3位小数*/
	 	  	 {
	 	  	 	 V_ul64Data >>= 0; 
				 
	 	  	 }break;
	 	  	 case C_DotNum_3:           /*3位小数*/
	 	  	 {
	 	  	 	 V_ul64Data >>= 4; 
				 
	 	  	 }break;
	 	  	 case C_DotNum_1:           /*1位小数*/
	 	  	 {
	 	  	 	 V_ul64Data >>= 12; 
	 	  	 }break;	
	 	  	 case C_DotNum_0:           /*0位小数*/
	 	  	 {
	 	  	 	 V_ul64Data >>= 16; 
	 	  	 }break;	 	  	 	 
	 	  	 default:             /*默认显示2位小数*/
	 	  	 {
	 	  	 	 V_ucDot = C_DotNum_2;         /*默认两位小数*/
				 V_ul64Data >>= 8; 
             }break;
		}
		
		V_ucj = 10 - 1 - V_ucDot;    		/* 灭0时需要判断几个高位 */

		GV_KillZeroNum = 0;
		V_ul64Compare = 0xf000000000;   /* 5个字节，从最高位开始判断 */
		for ( V_uci = 0; V_uci < V_ucj; V_uci++ )
        {
			if ( ( V_ul64Data & V_ul64Compare) == 0x00 )
			{
				GV_KillZeroNum++;
			}
			else
			{
				break;
			}

			V_ul64Compare = V_ul64Compare >> 4;
        }
        PF_Ulong64ToBuffer8(pV_ucDisplayData, &V_ul64Data, C_EnergyNature4BCDLen);
    }
    else      /*需量数据*/
    {
        V_usLen = CLPower_Decimal_Num;
        V_uci = InF_Read_Data(CPower_Decimal_Num, &V_ucDot, &V_usLen, &V_usDataEncode);/*显示需量小数位数*/
        if ( C_PreScreenDisDataLen < 4 )  /*显示数据存放缓存长度*/
        {
            return 4;      /*正常不存在*/
        } 

        PF_Buffer4ToUlong32(pV_ucDisplayData, &V_ulDemand32, 4);
#if(0)
        switch( V_ucDot ) 
        {
            case 0x06:           /*6位小数*/
            {
                if ( 0x00 == ( pV_ucDisplayData[3] & 0xF0 ) )  /*高4位，灭1个零*/ 
                {
                    GV_KillZeroNum = C_KillZero1;
                }	 
                else
                {
                    GV_KillZeroNum = 0;	 	  	 	  	 	 	  	 	  	 
                }
                break;	 	  	 	  
            }
            case 0x05:           /*5位小数*/
            {
                for ( V_uci = 0; V_uci < 3; V_uci++)
                {
                    pV_ucDisplayData[V_uci] >>= 4;
                    V_ucBuffer = (pV_ucDisplayData[V_uci+1] << 4);    
                    pV_ucDisplayData[V_uci] = (pV_ucDisplayData[V_uci]|V_ucBuffer);
                }
                pV_ucDisplayData[3] >>= 4;  /*第4个字节*/

                GV_KillZeroNum = C_KillZero1;             /*灭1个零*/
                if ( 0x00 == pV_ucDisplayData[3] )             /*灭2个零*/
                {
                    GV_KillZeroNum = C_KillZero2;
                }
                break;	 	  	 	  
            }
            case 0x03:           /*3位小数*/
            {
                V_ulDemand32 >>= 4;   /*去掉低1位小数*/

                GV_KillZeroNum = C_KillZero1;             /*灭1个零*/

                PF_Ulong32ToBuffer4(pV_ucDisplayData, &V_ulDemand32, 4);	 	  	 	                      

                if ( 0x00 == pV_ucDisplayData[2] )             /*灭2个零*/
                {
                    GV_KillZeroNum = C_KillZero2;
                }
                break;	 	  	 	  
            }	 	  	 
            case 0x02:           /*2位小数*/
            {                
                V_ulDemand32 >>= 8;   /*去掉低2位小数*/
                
                GV_KillZeroNum = C_KillZero2;/*灭2个零*/

                PF_Ulong32ToBuffer4(pV_ucDisplayData, &V_ulDemand32, 4);	 	  	 	

                if ( 0x00 == (pV_ucDisplayData[1]&0xF0) ) /*高4位，灭2个零*/ 
                {
                    GV_KillZeroNum = C_KillZero3;
                }
                break;	 	  	 	  
            }
            case 0x01:           /*1位小数*/
            {
                V_ulDemand32 >>= 12;   /*去掉低3位小数*/

                GV_KillZeroNum = C_KillZero3;             /*灭3个零*/

                PF_Ulong32ToBuffer4(pV_ucDisplayData, &V_ulDemand32, 4);	 	  	 	

                if ( 0x00 == pV_ucDisplayData[1] )             /*灭4个零*/ 
                {
                    GV_KillZeroNum = C_KillZero4;
                }
                break;	 	  	 	  
            }
            case 0x00:           /*0位小数*/
            {
                V_ulDemand32 >>= 16;   /*去掉低4位小数*/

                GV_KillZeroNum = C_KillZero4;             /*灭4个零*/

                PF_Ulong32ToBuffer4(pV_ucDisplayData, &V_ulDemand32, 4);	 	  	 	

                if ( 0x00 == (pV_ucDisplayData[0] & 0xF0) )             /*灭5个零*/ 
                {
                    GV_KillZeroNum = C_KillZero5;
                }
                break;	 	  	 	  
            }
            default:             /*默认4位小数*/
            {
                V_ucDot = 4;                                               /*默认4位小数*/		 	  	 	  

                if ( (pV_ucDisplayData[0] > 0x49) && (0xFF != pV_ucDisplayData[0]) ) /*四舍五入判断,同时需量数据不等于FF，即2、3结算需量*/
                {
                    V_DeBuff[0] = 0x01;
                    PF_BCDAddBytes(&pV_ucDisplayData[1], &V_DeBuff[0],&pV_ucDisplayData[1], 3);
                }	 	  	 	  

                for (V_uci = 0; V_uci < 3; V_uci++ )    /*去掉第0个字节*/
                {
                    pV_ucDisplayData[V_uci] = pV_ucDisplayData[V_uci+1];
                }
                GV_KillZeroNum = 0;
                if ( 0x00 == (pV_ucDisplayData[2]&0xF0) )   /*灭1个零*/
                {
                    GV_KillZeroNum = C_KillZero1;                 
                }
                break;
            }
        }	
#endif    
        switch( V_ucDot ) 
        {
	 	  	 case C_DotNum_3:           /*3位小数*/
	 	  	 {
	 	  	 	 V_ulDemand32 >>= 4; 
				 
	 	  	 }break;
             case C_DotNum_2:           /*2位小数*/
             {
	 	  	 	 V_ucDot = C_DotNum_2;         /*默认两位小数*/
				 V_ulDemand32 >>= 8; 
             }break;
	 	  	 case C_DotNum_1:           /*1位小数*/
	 	  	 {
	 	  	 	 V_ulDemand32 >>= 12; 
	 	  	 }break;	
	 	  	 case C_DotNum_0:           /*0位小数*/
	 	  	 {
	 	  	 	 V_ulDemand32 >>= 16; 
	 	  	 }break;	 	  	 	 
	 	  	 default:             /*默认显示4位小数*/
	 	  	 {
	 	  	 	 V_ulDemand32 >>= 0; 
                 V_ucDot = 4;
             }break;
		}
		
		V_ucj = 8 - 1 - V_ucDot;    		/* 灭0时需要判断几个高位 */

		GV_KillZeroNum = 0;
		V_ul64Compare = 0xf0000000;   /* 4个字节，从最高位开始判断 */
		for ( V_uci = 0; V_uci < V_ucj; V_uci++ )
        {
			if ( ( V_ulDemand32 & V_ul64Compare) == 0x00 )
			{
				GV_KillZeroNum++;
			}
			else
			{
				break;
			}

			V_ul64Compare = V_ul64Compare >> 4;
        }
        PF_Ulong32ToBuffer4(pV_ucDisplayData, &V_ulDemand32, 4);
    }
    return V_ucDot;
}

/*******************************************************************************
函数原型：void SF_DotDisplayDeal( uchar8 V_ucDot ) 
功能描述：广义小数点显示处理(包含“ ：”显示)，同时将小数点显示存入显示缓存
输入参数：uchar8 V_ucDot，0：无小数点，1：8P 1个小数点。。。
输出参数：无 
返回参数：无 
调用位置：
备    注：
*******************************************************************************/                                     
void SF_DotDisplayDeal( uchar8 V_ucDot )
{
    switch( V_ucDot )
    {
        case 0x01:  
        {
            GV_ucDisplayData[22] |= C_OneDot8P;
            break;
        }
        case 0x02:  
        {
            GV_ucDisplayData[24] |= C_TwoDot7P;
            break;
        }
        case 0x03:  
        {
            GV_ucDisplayData[24] |= C_ThreeDot6P;
            break;
        }
        case 0x04:  
        {
            GV_ucDisplayData[24] |= C_FourDot5P;
            break;
        }
        case 0x05:  
        {
            GV_ucDisplayData[24] |= C_FiveDot4P;
            break;
        }
        case 0x06:  
        {
            GV_ucDisplayData[24] |= C_SixDot3P;
            break;
        }
        case 0x07:  
        {
            GV_ucDisplayData[24] |= C_SevenDot2P;
            break;
        }
        case C_CoL15PDot:  /*COL1 5P*/
        {
            GV_ucDisplayData[24] |= (C_CoL1Dot|C_FourDot5P);
            break;
        }
        case C_CoL25P3P7PDot:  /*3P 5P COL2 7P*/
        {
            GV_ucDisplayData[24] |= (C_SixDot3P | C_FourDot5P | C_CoL2Dot | C_TwoDot7P);
            break;
        }
        case C_CoL27PDot:  /*COL2 7P*/
        {
            GV_ucDisplayData[24] |= (C_CoL2Dot | C_TwoDot7P);
            break;
        }
        case C_CoL2CoL15P7PDot:  /*COL1 5P COL2 7P*/
        {
            GV_ucDisplayData[24] |= (C_CoL1Dot | C_FourDot5P | C_CoL2Dot | C_TwoDot7P);
            break;
        }
        case C_CoL2CoL15P3P7PDot:  /*3P COL1 5P COL2 7P*/
        {
            GV_ucDisplayData[24] |= (C_SixDot3P | C_CoL1Dot | C_FourDot5P | C_CoL2Dot | C_TwoDot7P);
            break;
        }
        case C_5P7PDot:  /*5P 7P*/
        {
            GV_ucDisplayData[24] |= (C_FourDot5P | C_TwoDot7P);
            break;
        }
        case C_CoL15P7PDot:  /*COL1 5P 7P*/
        {
            GV_ucDisplayData[24] |= (C_CoL1Dot | C_FourDot5P | C_TwoDot7P);
            break;
        }
        case C_5P3P7PDot:  /*3P 5P 7P*/
        {
            GV_ucDisplayData[24] |= (C_SixDot3P | C_FourDot5P | C_TwoDot7P);
            break;
        }
        default:
            break;
    }
}
/*******************************************************************************
函数原型：void SF_KillZeroDealPreEn( uchar8 *pV_ucDisData,uchar8 V_ucDot )
功能描述：精确电能小数位数(XX.XXXX)，显示灭零处理，计算显示数据灭零个数，赋值全局变量GV_KillZeroNum
输入参数：uchar8 pV_ucDisData：显示主数据缓存指针；uchar8 V_ucDot：显示主数据小数点个数
输出参数：无
返回参数：无
调用位置：
备    注：注意当高4位数据有为1时(XXXX XX.XXXX)，小数点前(XX.XXXX)两位不可以灭零
*******************************************************************************/                                     
void SF_KillZeroDealPreEn( uchar8 *pV_ucDisData, uchar8 V_ucDot )
{
    uchar8 V_uci, V_ucj = 0;
	
    if ( 0x04 != V_ucDot )
    {
        return;
    }
    for ( V_uci = C_MainDataEn_offset4; V_uci > C_MainDataEn_offset2; V_uci-- )/*都是0为0.0000*/
    {
        if ( (pV_ucDisData[V_uci]&0xF0) == 0x00 )
        {
            GV_KillZeroNum = C_KillZero1 + V_ucj;
            V_ucj++;
            if ( (pV_ucDisData[V_uci]&0x0F) == 0x00 )
            {
                GV_KillZeroNum = C_KillZero1 + V_ucj;
                V_ucj++;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    if ( V_uci == C_MainDataEn_offset2 )
    {
        if ( (pV_ucDisData[C_MainDataEn_offset2]&0xF0) == 0x00 )
        {
            GV_KillZeroNum += C_KillZero1;
        }
    }
    if ( GV_KillZeroNum > C_KillZero6 ) /*正常不存在,最多灭5个0*/ 
    {
        GV_KillZeroNum = 0;                         	  
    }
}
/*******************************************************************************
函数原型：void SF_KillZeroDeal( uchar8 *pV_ucDisData, uchar8 V_ucDot )
功能描述：显示灭零处理，计算显示数据灭零个数，赋值全局变量GV_KillZeroNum   
输入参数：uchar8 *pV_ucDisData：显示主数据缓存指针；uchar8 V_ucDot：显示主数据小数点个数 
输出参数：无 
返回参数：无 
调用位置：
备    注：需特殊灭零处理的，则把小数点前，从前往后，所有的零全部灭零，如0000.005，则灭零后实际为0.005
*******************************************************************************/                                      
void SF_KillZeroDeal( uchar8 *pV_ucDisData, uchar8 V_ucDot )
{
    uchar8 *pV_ucChieseTable;
    uchar8 V_uci,V_ucDataLen, V_ucKillZeroNum;
    uchar8 V_ucDataBuff, V_ucDataLenByte, V_ucj;
    uchar8 V_ucDataBuffByte;
	 	 
    pV_ucChieseTable = (uchar8 * )(GV_Str_DisplayFlag.P_ChieseTableNo+GV_Str_DisplayFlag.ChieseTableLineNo*C_ChineseSignLen);  /*汉字表格结构体地址*/
    V_ucDataLen = pV_ucChieseTable[C_ChinaLineDataLenKillZero];   /*取低4位显示数据长度*/

   
    V_ucDataLen &= C_GetChinaDataLenBit0x07;    /*取低4位要显示数据长度*/
    V_ucDataLenByte = 2*V_ucDataLen;  /*高、低4位，分开判断灭零，数据长度*/

    V_ucKillZeroNum = pV_ucChieseTable[C_ChinaLineDataLenKillZero];  /*要显示数据特征*/
   
    V_ucKillZeroNum &= 0xF0;    /*取高4位，灭零小数位数*/
    V_ucKillZeroNum >>= 4;
   
    GV_KillZeroNum = (V_ucKillZeroNum & 0x07);  /*取具体灭零个数*/
    
    if ( 0x08 == (V_ucKillZeroNum & 0x08 ))    /*第4位判断，为1表示：该数据项需灭零，但对该数据不用特殊灭零判断处理，*/
    {                                 /*如类似表号高4位，只灭前4个零，实际数据不判断*/
        return;
    }	       
    else                              /*需特殊灭零判断*/
    {
        if ( V_ucDot >= V_ucDataLenByte )   /*正常不存在*/
        {
            return;   	  	 
        }
        else                   /*高位灭零计算*/
        {
            for ( V_uci = 0; V_uci < (V_ucDataLenByte-V_ucDot-1); V_uci++ )  /*需判断灭零数据位数*/
            {
                V_ucj = V_uci/2;
                V_ucDataBuff = pV_ucDisData[V_ucDataLen-1-V_ucj];    /*取判断整个数据*/

                if ( 0x00 == (V_uci%2) )  /*每个数据分高、低4位，分别判断,*/
                {                  /*奇：取低4位数据判断、偶：取高4位数据判断*/
                    V_ucDataBuffByte = (V_ucDataBuff&0xF0);
                    if ( 0x00 != V_ucDataBuffByte )          /*不为0，退出，后续数据位不再判断*/
                    {
                        break;
                    }
                    else
                    {
                        GV_KillZeroNum++;   	  	 	  	 	  
                    }
                }
                else        /*数据低4位判断*/
                {
                    V_ucDataBuffByte = (V_ucDataBuff & 0x0F);
                    if ( 0x00 != V_ucDataBuffByte )          /*不为0，退出，后续数据位不再判断*/
                    {
                        break;
                    }
                    else
                    {
                        GV_KillZeroNum++;   	  	 	  	 	  
                    }
                }   	  	 	  
            }
        }
    } 
    if ( GV_KillZeroNum > C_KillZero7 ) /*正常不存在*///
    {
        GV_KillZeroNum=0;                         	  
    }
}
/*******************************************************************************
函数原型：void SF_DisplayUnit( uchar8 V_ucDisUnit )
功能描述：单位显示处理，同时将单位显示存入显示缓存
输入参数：uchar8 V_ucDisUnit：显示单位序号 
		#define C_DiskWNum                  1 
		#define C_DiskWhNum                 2 
		#define C_DiskvarNum                3
		#define C_DiskvarhNum               4 
		#define C_DisVNum                   5 
		#define C_DisANum                   6
		#define C_DiskVANum                 7
		#define C_DisYuanNum                8   "元"
		#define C_DisWanYuanNum             9   "万元"
		#define C_DisAhNum                  10
		#define C_DiskVAhNum                11 
		#define C_DisYuankwhNum             12   "元/kwh"  
		#define C_DisVANum                  13   "VA"
输出参数：无
返回参数：无
调用位置：
备    注：
*******************************************************************************/                                       
void SF_DisplayUnit( uchar8 V_ucDisUnit )
{
    switch( V_ucDisUnit )
    {
        case C_DisNo:
        {
            break;
        }	
        case C_DiskWNum:  
        {
            GV_ucDisplayData[23] |= C_DiskW;
            break;
        }
        case C_DiskWhNum:  
        {
            GV_ucDisplayData[23] |= C_DiskWh;
            break;
        }
        case C_DiskvarNum:  
        {
            GV_ucDisplayData[23] |= C_Diskvar;
            break;
        }
        case C_DiskvarhNum:  
        {
            GV_ucDisplayData[23] |= C_Diskvarh;
            break;
        }
        case C_DisVNum:  
        {
            GV_ucDisplayData[23] |= C_DisV;
            break;
        }
        case C_DisANum:  
        {
            GV_ucDisplayData[23] |= C_DisA;
            break;
        }
        case C_DiskVANum:  
        {
            GV_ucDisplayData[23] |= C_DiskVA;
            break;
        }
        case C_DisYuanNum:  
        {
            GV_ucDisplayData[22] |= C_DisYuan;
            break;
        }
        case C_DisWanYuanNum:  
        {
            GV_ucDisplayData[22] |= C_DisWanYuan;
            break;
        }
        case C_DisAhNum:  
        {
            GV_ucDisplayData[23] |= C_DisAh;
            break;
        }
        case C_DiskVAhNum:  
        {
            GV_ucDisplayData[23] |= C_DiskVAh;
            break;
        }
        case C_DisYuankwhNum:  
        {
            GV_ucDisplayData[23] |= C_DiskWh;
            GV_ucDisplayData[22] |= C_DisYuan;
            break;
        }
        case C_DisVANum:  
        {
            GV_ucDisplayData[23] |= C_DisV;
            GV_ucDisplayData[23] |= C_DisA;
            break;
        }
        case C_DisWNum:
        {
            GV_ucDisplayData[23] |= C_DisW;
            break;

        }
        case C_DisvarNum:
        {
            GV_ucDisplayData[23] |= C_Disvar;
            break;

        }
        default:
            break;
    }
}
/***************************************************************************************************************
函数原型：void SF_DisplayChinaese(void)                                            
功能描述：辅助汉字显示处理，根据辅助汉字表格处理，写显示缓存，内部对电量、需量当前及结算判断处理、本月及上几
          月，同时根据DI0，进行显示次数调整。当涉及次数与当前都存在时且标识码表格中，只列当前次时，对应汉字 
          表格中“当前”与“上”均为零。当前剩余金额、当前透支金额根据数据标识单独处理。列汉字表格时，类似事件记                                                                 
          录,只有“上几”，没有“当前”时，则汉字表格中要列”上“。根据“上”该位判断，是否需要显示“上几”   
输入参数：无                                                                                               
输出参数：无                                                                                               
返回参数： 无                                                                                               
调用位置：                                                                                                 
备    注：                                                                                                 
*****************************************************************************************************************/                                       
void SF_DisplayChinaese( void )
{
    ulong32 V_ulDi0Hex;
    ulong32 V_ulDi32, V_ulRelatedDI;
    uchar8	*pV_ucChieseTable;
    uchar8	V_uci, V_ucDataBuff, V_ucDi[4];
    uchar8	V_ucDi0BCD;
    uchar8	V_ucRelated_CodeID[4];
   
    if ( C_ALLScreenDisplayDi == GV_Str_DisplayFlag.CodeID )   /*标识码为全FF*/
    {
        return;   	 
    }
    pV_ucChieseTable = (uchar8 *)(GV_Str_DisplayFlag.P_ChieseTableNo + GV_Str_DisplayFlag.ChieseTableLineNo * C_ChineseSignLen);  /*汉字表格结构体地址*/
    V_ucDataBuff = pV_ucChieseTable[0];          /*汉字表格第一个字节*/

    V_ulDi32 = GV_Str_DisplayFlag.CodeID;
	PF_Ulong32ToBuffer4(&V_ucDi[0], &V_ulDi32, C_DataCodeLen);
    
    if ( ( 0x00 == ( V_ucDi[3] & 0xf0 ) )
      || ( 0x10 == ( V_ucDi[3] & 0xf0 ) ) )  /*需量或电量类数据*/
	{
        V_ucDataBuff |= C_DisCurr;
        
		if ( V_ucDi[0] != 0 )
	    {
			V_ulDi0Hex = V_ucDi[0] - 1;         /*费率电能，费率号和索引差1*/
	    }
	    else
	    {
			V_ulDi0Hex = 0;                    /*电能总*/
	    }
       
		V_ucDi0BCD = PF_HextoBCDOneBytes(V_ulDi0Hex);
        GV_ucDisplayData[C_EngyRate18_offset] = V_ucDi0BCD;
    }
	if ( ( ( V_ucDi[3] & 0xf0) == 0x30 )
      || ( ( V_ucDi[3] & 0xf0) == 0x50 ) )
	{
        if ( GV_Str_DisplayFlag.Related_CodeID != 0xFFFFFFFF )
		{
            V_uci = 1;
            V_ulDi0Hex = (ulong32)V_ucDi[0];
#if 0
            if ( V_ulDi0Hex > 12 )              /*大于12次时，直接固定为12，目前冻结类数据，没有显示上“几”*/
            {
                V_ulDi0Hex = 12;         	 	 
            }
#endif
			PF_HextoBCDBytes(&V_ulDi0Hex,&V_ucDi0BCD,&V_uci);
		 
            V_ucDataBuff |= C_DisLast;                          /*“上”显示*/
            V_ucDataBuff &= (~C_DisCurr);			              /*显示“上”则不显示当前*/
            GV_ucDisplayData[9] = V_ucDi0BCD;                   /*显示 第几*/
            
            if ( ( V_ucDi[3] == 0x50 )
              && ( ( V_ucDi[2] == 0x05) || (V_ucDi[2] == 0x06) ) )  /*上一结算日显示月*/
            {
                V_ucDataBuff |= C_DisMonth;                       /*“上”显示*/
            }
            
            V_ulRelatedDI = GV_Str_DisplayFlag.Related_CodeID;
            PF_Ulong32ToBuffer4(&V_ucRelated_CodeID[0], &V_ulRelatedDI, C_DataCodeLen);
            
            if ( V_ucRelated_CodeID[0] != 0 )
            {
                V_ulDi0Hex = V_ucRelated_CodeID[0] - 1;         /*费率电能，费率号和索引差1*/
            }
            else
            {
                V_ulDi0Hex = 0;                                 /*电能总*/
            }
            
            V_ucDi0BCD = PF_HextoBCDOneBytes(V_ulDi0Hex);
            GV_ucDisplayData[C_EngyRate18_offset] = V_ucDi0BCD;
		}
		else
		{
            if ( C_DisLast == (V_ucDataBuff & C_DisLast) )	    /*取“上”位定义状态*/
            {
                GV_ucDisplayData[9] = 1;                /*显示 第几*/   	  	 
            }
		}
	}
	
    for (V_uci = 0; V_uci < 4; V_uci++ )                        /*主汉字显示缓存赋值*/
    {
        GV_ucDisplayData[18 + V_uci] = pV_ucChieseTable[1 + V_uci];
    }
    
    if ( ( V_ulDi32 & 0xffff0000 ) == 0x30000000 )
	{
		GV_ucDisplayData[20] |= C_DisLossVol;           /*“失压”显示*/
	}

	if ( ( V_ulDi32 & 0xffff0000 ) == 0x30040000 )
	{
	 	GV_ucDisplayData[20] |= C_DisLossCurr;          /*“失流”显示*/	 	  	 	  	 
	}

	if ( ( V_ucDi[2] <= 8 ) && ( V_ucDi[3] == 0x30 ) )
	{
		if ( V_ucDi[1] == 0x07 )
		{
            GV_ucDisplayData[19] |= C_DisAPhase;          /*“A”显示*/	  	 	  
		}
		else if ( V_ucDi[1] == 0x08 )
		{
            GV_ucDisplayData[19] |= C_DisB;               /*“B”显示*/	 	  	 	  	 	  	 	  	 
		}
		else if ( V_ucDi[1] == 0x09 )
		{
            GV_ucDisplayData[19] |= C_DisC;               /*“c”显示*/	 	  	 	  	 	  	 	  	 	 	  	 	  	 	  
		}
	}

    if ( ( (GV_Str_DisplayFlag.CodeID & 0xFFFFFF00) == (CCurrent_Rate1_Price & 0xFFFFFF00) )
      || ( (GV_Str_DisplayFlag.CodeID & 0xFFFFFF00) == (CBackUp_Rate1_Price & 0xFFFFFF00 ) ) )
    {
        V_ucDi0BCD = PF_HextoBCDOneBytes(V_ucDi[0]);
        GV_ucDisplayData[C_EngyRate18_offset] = V_ucDi0BCD;
    }
    else if ( ( GV_Str_DisplayFlag.CodeID == CCurrent_Ladder_Table_LadPri ) 
      || ( GV_Str_DisplayFlag.CodeID == CBackUp_Ladder_Table_LadPri ) )
    {
        V_ucDi0BCD = PF_HextoBCDOneBytes(GV_Str_DisplayFlag.ParaNum);
        GV_ucDisplayData[C_RecordNum_offset] = V_ucDi0BCD;                   /*显示 第几*/
    }
    else
    {
        ;
    }
    
    GV_ucDisplayData[17] |= V_ucDataBuff;
}
/*******************************************************************************
函数原型：void SF_DisplayDI(void)  
功能描述：DI及序号显示，DI hex与BCD格式混合，显示序号hex格式,当显示序号大于255时，序号固定显示为255 
输入参数：无 
输出参数：无 
返回参数：无 
调用位置：
备    注：
*******************************************************************************/                                
void SF_DisplayDI( void )
{
    ulong32 V_ulDi32;
    uchar8 V_ucDi[5], V_uci;

    if ( C_ALLScreenDisplayDi == GV_Str_DisplayFlag.CodeID )   /*标识码为全FF*/
    {
        return;   	 
    }
	 
    V_ulDi32 = GV_Str_DisplayFlag.CodeID;
    PF_Ulong32ToBuffer4(&V_ucDi[0], &V_ulDi32, 4);
    V_ucDi[4] = GV_Str_DisplayFlag.ParaNum;
	    
    for ( V_uci = 0; V_uci < 4; V_uci++)
    {
        GV_ucDisplayData[5 + V_uci] = V_ucDi[V_uci];
    }	 
    GV_ucDisplayData[4] = V_ucDi[4];
}
/*******************************************************************************
函数原型：void SF_StateDisVolageLimt(uchar8 V_ucStateNum)
功能描述：状态字符显示，需要进行电压限制判断；当主电源电压低于一定限值时，状态字符不动作。辅助电源供电时，不
		考虑电压限制。另，刚上电时没有电压限制；目前的状态字符包括背光
输入参数：uchar8 V_ucStateNum:需处理状态字符宏定义，目前处理有背光；
		C_BackLED：背光；  
输出参数：无
返回参数：无
调用位置：
备    注：刚上电5s内，背光点亮，不进行电压判断   
*******************************************************************************/                                       
void SF_StateDisVolageLimt( uchar8 V_ucStateNum )
{	 
    if ( C_BackLED == V_ucStateNum )  /*背光处理*/
    {
        if ( GV_ShutBackLEDTime < C_ShutBackLEDTime5s )   /*上电初始化，不到5s，背光点亮不判断电压*/
        {
            InF_SwithPeripherals(C_BackLight, C_On);
            return;
        }
    }
	 	  	 	  
    if ( C_OK == Inf_BackLightLimit() )  /*电压满足要求，目前是≥60%Un，点亮背光、报警继电器*/
    {
        switch( V_ucStateNum )
        {
            case C_BackLED:   /*背光*/
            {
                InF_SwithPeripherals(C_BackLight, C_On);
                break;
            }
            default:
            {
                break;	 	  	 	  
            }

        }
    }
    else   /*电压不满足*/
    {
        switch( V_ucStateNum )
        {
            case C_BackLED:   /*背光*/
            {
                InF_SwithPeripherals(C_BackLight, C_Off);
                break;
            }
            default:
            {
                break;	 	  	 	  
            }
        }	 	
    }
}
/*******************************************************************************
函数原型：void SF_WranRelayAction(void) 
功能描述：报警继电器动作，电源电压判断，调用继电器模块接口函数，当电压满足要求时，才允许报警继电器动作
输入参数：无
输出参数：无
返回参数：无
调用位置：
备    注：
*******************************************************************************/                                       
void SF_WranRelayAction( void )
{	 
	ushort16 V_usLen, V_usDataEncode;
    uchar8 V_ucReturn_Flag, V_ucBuf[2];
   
    V_usLen = 2;
    V_ucReturn_Flag = InF_Read_Data(CMeter_Work_State3, &V_ucBuf[0], &V_usLen, &V_usDataEncode);
   
    if ( ( C_OK == V_ucReturn_Flag ) && ( (V_ucBuf[0]&0x06) == 0x02 ) )/*辅助电源供电*/
    {
        InF_SwithPeripherals(C_WarnOut, C_On);
    }
    else
    {
        if ( C_VoltageOk == InF_JudgeVolage_Relay() )  /*调用继电器模块接口函数，进行电压判断*/
        {
            InF_SwithPeripherals(C_WarnOut, C_On);
        }
        else
        {
            InF_SwithPeripherals(C_WarnOut, C_Off);
        }   	  
    }
}
/*******************************************************************************
函数原型：void SF_DisplayStateSign(void) 
功能描述：显示状态字符，电压、电流、负号符号，当事件记录模块下发闪烁时，闪烁优先，其次下发不显时，则不显。
		最后(包括计量模块)都是常显，则常显；其他符号闪烁为最高优先级，其次为常显，最后为不显。该部分处理
		最后(包括计量模块)都是常显，则常显；其他符号闪烁为最高优先级，其次为常显，最后为不显。该部分处理
输入参数：无
输出参数：无
返回参数：无
调用位置：
备    注：
*******************************************************************************/                                      
void SF_DisplayStateSign( void )
{
    Str_DisplaySignMesNum *pStr_DisplaySignMesNum;
    uchar8 *pV_ucDisStateBuff;
    uchar8 V_uci, V_ucj;
   
    for ( V_uci=0; V_uci<GV_Str_DisplaySignLen; V_uci++ )
    {
        pStr_DisplaySignMesNum = (Str_DisplaySignMesNum *)GV_Str_DisplaySign[V_uci].PStr_DisplaySignMesNum;
        pV_ucDisStateBuff = GV_Str_DisplaySign[V_uci].PDisplyBuff;   /*显示缓存地址*/
   	  
        switch( GV_Str_DisplaySign[V_uci].StateNum )
        {
            case C_UaSign:    /*电压、电流、负号 显示符号，特殊处理*/
            case C_UbSign:
            case C_UcSign:
            case C_IaSign:
            case C_IbSign:
            case C_IcSign:
            case C_IaNegativeSign:
            case C_IbNegativeSign:
            case C_IcNegativeSign:   	  	 	
            {   	  	 	  
                for ( V_ucj = 0; V_ucj < GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen; V_ucj++ ) /*事件记录，闪烁优先*/
                {
                    if ( C_Msg_PowerNetworkMonitoring == pStr_DisplaySignMesNum[V_ucj].SourceNo )
                    {
                        if ( C_TwinkleDisplayNiu == pStr_DisplaySignMesNum[V_ucj].Timer ) /*事件记录，闪烁优先*/
                        {
                            if ( (C_IaNegativeSign == GV_Str_DisplaySign[V_uci].StateNum)
                              || (C_IbNegativeSign == GV_Str_DisplaySign[V_uci].StateNum)  /* “-”号显示处理，学云事件记录，发电流闪烁时，“-”号一起发*/                                       
                              || (C_IcNegativeSign == GV_Str_DisplaySign[V_uci].StateNum) )   /* 没有判断当前功率方向,显示模块判断，看计量“-”号该定时器是否为零，如不是零，说明是反向则闪烁*/ 
                            {
                                if ( C_NotDisplayNiu != pStr_DisplaySignMesNum[V_ucj+1].Timer )  /*计量“-”显示时间不等0，闪烁*/
                                {
                                    if ( GV_Str_DisplayFlag.ParityTimer < 2 )   /*奇偶定时器，奇数显，偶数不显*/
                                    {
                                        (*pV_ucDisStateBuff) |= GV_Str_DisplaySign[V_uci].DisplyBuffBit;
                                    }   	  	 	     	 	   	  	 
                                }
                            }	                                                          
                            else         /*电压、电流状态字符处理*/
                            {
                                if ( GV_Str_DisplayFlag.ParityTimer < 2 )   /*奇偶定时器，奇数显，偶数不显*/
                                {
                                    (*pV_ucDisStateBuff) |= GV_Str_DisplaySign[V_uci].DisplyBuffBit;
                                }   	  	 	     	 	   	  
                            }   	  	 	     	 	   
                            break;   	  	 	  	 	  	 
                        }
                        else
                        {
                            if ( C_NotDisplayNiu == pStr_DisplaySignMesNum[V_ucj].Timer ) /*事件记录，不显*/
                            {
                                break;              /*每500ms,显示统一刷新，显示缓存清零*/   	  	 	  	 	  	 	  
                            }
                        }	   	  	 	  	 	  
                    }   	  	 	  	 	  
                }
				
                if ( GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen == V_ucj )  /*没有满足上述条件,则为常显*/
                {
                    for ( V_ucj = 0; V_ucj < GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen; V_ucj++ )
                    {
                        if ( C_Msg_PowerNetworkMonitoring == pStr_DisplaySignMesNum[V_ucj].SourceNo )  /*其实该部分不用判断，假如事件指示，不灭或闪，则剩余就是常显。目前事件没有发生，发常显消息给显示*/
                        {
                            if ( C_NotDisplayNiu != pStr_DisplaySignMesNum[V_ucj].Timer ) /*显示时间不为零*/
                            {
                                if ( (C_IaNegativeSign == GV_Str_DisplaySign[V_uci].StateNum)
                                  || (C_IbNegativeSign == GV_Str_DisplaySign[V_uci].StateNum)  /* “-”号显示处理，学云事件记录，发电流闪烁时，“-”号一起发  */                                     
                                  || (C_IcNegativeSign == GV_Str_DisplaySign[V_uci].StateNum) )   /* 没有判断当前功率方向,显示模块判断，看计量“-”号该定时器是否为零，如不是零，说明是反向则闪烁*/ 
                                {
                                    if ( C_NotDisplayNiu != pStr_DisplaySignMesNum[V_ucj+1].Timer )  /*计量“-”显示时间不等0,计量消息源在事件记录消息源后面1个*/
                                    {
                                        (*pV_ucDisStateBuff) |= GV_Str_DisplaySign[V_uci].DisplyBuffBit;
                                    }
                                }
                                else   /*电压、电流状态字符处理*/
                                {
                                    (*pV_ucDisStateBuff) |= GV_Str_DisplaySign[V_uci].DisplyBuffBit;
                                }	                                                          
                            }
                        }
                    }
                }
                break;
            }
            case C_BackLED:
            case C_RelayStatusLED:   /*考虑是否处于全显模式,跳闸指示灯、报警灯*/
            {
                if ( C_ALLScreenDisplay == GV_Str_DisplayFlag.SV_ucDisplayMode )
                {
                    InF_SwithPeripherals(C_BackLight, C_On);  /*全显不进行电压限制*/
                    InF_SwithPeripherals(C_TripLed, C_On);
                }
                else
                {
                    for ( V_ucj = 0; V_ucj < GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen; V_ucj++ )
                    {
                        if ( C_TwinkleDisplayNiu == pStr_DisplaySignMesNum[V_ucj].Timer ) /*闪烁优先*/
                        { 
                            if ( GV_Str_DisplayFlag.ParityTimer < 2 )   /*奇偶定时器，奇数显，偶数不显*/
                            {
                                if ( C_BackLED == GV_Str_DisplaySign[V_uci].StateNum )
                                {
                                    SF_StateDisVolageLimt(C_BackLED);  /*电压限制*/
                                }
                                else
                                {
                                    InF_SwithPeripherals(C_TripLed, C_On);
                                }   	  	 	       	  	 
                            }
                            else
                            {
                                if ( C_BackLED == GV_Str_DisplaySign[V_uci].StateNum )
                                {
                                    InF_SwithPeripherals(C_BackLight, C_Off);
                                }
                                else
                                {
                                    InF_SwithPeripherals(C_TripLed, C_Off);
                                }
                            }
                            break;
                        }
                    }
                    if ( GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen == V_ucj )  /*没有满足上述条件*/
                    {
                        for ( V_ucj = 0; V_ucj < GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen; V_ucj++ )
                        {
                            if ( C_NotDisplayNiu != pStr_DisplaySignMesNum[V_ucj].Timer ) /*显示时间不为零*/
                            { 
                                if ( C_BackLED == GV_Str_DisplaySign[V_uci].StateNum )
                                {
                                    SF_StateDisVolageLimt(C_BackLED);  /*电压限制*/
                                }
                                else
                                {
                                    InF_SwithPeripherals(C_TripLed, C_On);
                                }
                                break;
                            }
                        }
                    }
                    if ( GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen == V_ucj )  /*没有满足上述条件*/
                    {
                        if ( C_BackLED == GV_Str_DisplaySign[V_uci].StateNum )
                        {
                            InF_SwithPeripherals(C_BackLight, C_Off);
                        }
                        else
                        {
                            InF_SwithPeripherals(C_TripLed, C_Off);
                        }
                    } 
                }
                break;
            }
            default:
            {
                for ( V_ucj = 0; V_ucj < GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen; V_ucj++ )
                {
                    if ( C_TwinkleDisplayNiu == pStr_DisplaySignMesNum[V_ucj].Timer ) /*闪烁,优先*/
                    { 
                        if ( GV_Str_DisplayFlag.ParityTimer < 2 )   /*奇偶定时器，奇数显，偶数不显*/
                        {
                            if ( (C_WarnOutPut == GV_Str_DisplaySign[V_uci].StateNum)
                              || (C_Beeper == GV_Str_DisplaySign[V_uci].StateNum) )   /*蜂鸣器、报警继电器*/
                            {
                                if ( C_Beeper == GV_Str_DisplaySign[V_uci].StateNum )
                                {
                                    ;/*InF_SwithPeripherals(C_Beep,C_On);*/  /*需求变更，蜂鸣器直接由驱动提供接口函数*/
                                }
                                else
                                {
                                    SF_WranRelayAction();
									/*SF_StateDisVolageLimt(C_WarnOutPut); */ /*电压限制*/
                                }
                            }
                            else   /*其他状态字符*/
                            {
                                (*pV_ucDisStateBuff) |= GV_Str_DisplaySign[V_uci].DisplyBuffBit;
                            }
                        }
                        else
                        {
                            if ( (C_WarnOutPut == GV_Str_DisplaySign[V_uci].StateNum)
                              || (C_Beeper==GV_Str_DisplaySign[V_uci].StateNum) )   /*蜂鸣器、报警继电器*/
                            {
                                if ( C_Beeper==GV_Str_DisplaySign[V_uci].StateNum )
                                {
                                    ;/*InF_SwithPeripherals(C_Beep,C_Off);*/
                                }
                                else
                                {
                                    InF_SwithPeripherals(C_WarnOut,C_Off);
                                }   	  	 	     	  	 	  
                            }
                        }
                        break;
                    }
                }
                if ( GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen == V_ucj )  /*没有满足上述条件*/
                {
                    for ( V_ucj = 0; V_ucj < GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen; V_ucj++ )
                    {
                        if ( C_NotDisplayNiu != pStr_DisplaySignMesNum[V_ucj].Timer ) /*显示时间不为零*/
                        { 
                            if ( (C_WarnOutPut == GV_Str_DisplaySign[V_uci].StateNum)
                              || (C_Beeper == GV_Str_DisplaySign[V_uci].StateNum) )   /*蜂鸣器、报警继电器*/
                            {
                                if ( C_Beeper == GV_Str_DisplaySign[V_uci].StateNum )
                                {
                                    ;/*InF_SwithPeripherals(C_Beep,C_On);*/
                                }
                                else
                                {
                                    SF_WranRelayAction();
									/*SF_StateDisVolageLimt(C_WarnOutPut);*/  /*电压限制*/
                                }    	  	 	      	  	  
                            }
                            else   /*其他状态字符*/
                            {
                                (*pV_ucDisStateBuff) |= GV_Str_DisplaySign[V_uci].DisplyBuffBit;
                            }
                            break;
                        }
                    }
                }
                if ( GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen == V_ucj )  /*没有满足上述条件,状态字符显示缓存已清零*/
                {
                    if ( (C_WarnOutPut == GV_Str_DisplaySign[V_uci].StateNum)
                      || (C_Beeper == GV_Str_DisplaySign[V_uci].StateNum) )   /*蜂鸣器、报警继电器*/
                    {
                        if ( C_Beeper == GV_Str_DisplaySign[V_uci].StateNum )
                        {
                            ;/*InF_SwithPeripherals(C_Beep,C_Off);*/
                        }
                        else              /*报警继电器*/
                        {
                            InF_SwithPeripherals(C_WarnOut,C_Off);           /*关闭显示*/ 
                        }
                    }    
                }
            }
        }
    }
}
/*******************************************************************************
函数原型：uchar8 InF_AlarmState(void)
功能描述：报警状态，考虑当前是否处于全显模式
输入参数：无
输出参数：无
返回参数：无
调用位置：
备    注：20141104,根据评审会议纪要，电压、电流、负号显示，只根据事件显示，不代表实时量显示
*******************************************************************************/                                       
uchar8 InF_AlarmState( void )
{
    Str_DisplaySignMesNum *pStr_DisplaySignMesNum;
    uchar8 V_uci,V_ucj;
    uchar8 V_ucReturnFlag = 0;
	
    for ( V_uci = 0; V_uci < GV_Str_DisplaySignLen; V_uci++ )
    {
        pStr_DisplaySignMesNum = (Str_DisplaySignMesNum *)GV_Str_DisplaySign[V_uci].PStr_DisplaySignMesNum;
        for ( V_ucj = 0; V_ucj < GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen; V_ucj++ )
        {
            if ( C_NotDisplayNiu != pStr_DisplaySignMesNum[V_ucj].Timer ) /*显示时间不为零*/
            { 
                if ( C_WarnOutPut == GV_Str_DisplaySign[V_uci].StateNum )
                {
                    V_ucReturnFlag = 1;   	  	 	      	  	  
                }	
            }
        }
    }
    return V_ucReturnFlag;
}
/*******************************************************************************
函数原型：void SF_DisAllData(void)
功能描述：函数内部判断全屏显示，或液晶查看(全FF)，显示缓存全部置1
输入参数：无
输出参数：无
返回参数：
调用位置：
备    注：
*******************************************************************************/                                     
void SF_DisAllData( void )
{	 
#if(0)
    if ( C_ALLScreenDisplay == GV_Str_DisplayFlag.SV_ucDisplayMode )  /*全屏显示*/
    {
        memset(&GV_ucDisplayData[0], 0xFF, C_DisplayDataByte);
        memset(&GV_ucDisplayData[0], 0x88, 9);
        GV_ucDisplayData[9] = 0x18;
        GV_ucDisplayData[C_Ladder8_offset] = 0x08;
        GV_ucDisplayData[C_EngyRate18_offset] = 0x18;
        GV_ucDisplayData[C_Rate18_offset] = 0x18;
        GV_ucDisplayData[C_MainDataHig_offset] = 0x88;
        /*GV_DispAllScreenMode = 0xFF;*/        /*数字全屏显示模式*/
    }
    else
    {
        if ( C_CheckDisplay == GV_Str_DisplayFlag.SV_ucDisplayMode )  /*液晶查看*/
        {
            if ( (C_ALLScreenDisplayDi == GV_Str_DisplayFlag.CodeID)
              && (0xFF == GV_Str_DisplayFlag.ParaNum) )   /*标识码全FF*/
            {
                memset(&GV_ucDisplayData[0], 0xFF, C_DisplayDataByte);
                memset(&GV_ucDisplayData[0], 0x88, 9);
                GV_ucDisplayData[9] = 0x18;
                GV_ucDisplayData[C_Ladder8_offset] = 0x08;
                GV_ucDisplayData[C_EngyRate18_offset] = 0x18;
                GV_ucDisplayData[C_Rate18_offset] = 0x18;
                GV_ucDisplayData[C_MainDataHig_offset] = 0x88;
                /*GV_DispAllScreenMode = 0xFF;*/     /*数字全屏显示模式*/
            }
        }
    }
#endif
    if ( ( C_ALLScreenDisplay == GV_Str_DisplayFlag.SV_ucDisplayMode )
      || ( ( C_CheckDisplay == GV_Str_DisplayFlag.SV_ucDisplayMode ) 
         &&( C_ALLScreenDisplayDi == GV_Str_DisplayFlag.CodeID )
         &&( 0xFF == GV_Str_DisplayFlag.ParaNum ) ) )
    {
        memset(&GV_ucDisplayData[0], 0xFF, C_DisplayDataByte);
        memset(&GV_ucDisplayData[0], 0x88, 9);
        GV_ucDisplayData[9] = 0x18;
        GV_ucDisplayData[C_Ladder8_offset] = 0x08;
        GV_ucDisplayData[C_EngyRate18_offset] = 0x18;
        GV_ucDisplayData[C_Rate18_offset] = 0x18;
        GV_ucDisplayData[C_MainDataHig_offset] = 0x88;      
    }
}
/*******************************************************************************
函数原型：void SF_CardAbnormalDisDeal(Str_DisplayStatus *pV_ucBuffer)
功能描述：插卡异常显示处理
输入参数：Str_DisplayStatus *pV_ucBuffer：插卡异常字符显示变量
			typedef struct
			{ 
				ushort16 Time; 显示时间，最大不能大于65535/2秒，显示内部是500ms为基准
				uchar8 Type；    BCD格式  
			}Str_DisplayStatus; 
输出参数：无
返回参数：无
调用位置：
备    注：置全局变量当前显示状态为插卡异常显示状态C_CardAbnormalDisplay;同时赋值显示变量GV_CardAbnDisplayNum
*******************************************************************************/                                       
void SF_CardAbnormalDisDeal( Str_DisplayStatus *pV_ucBuffer )
{
    GV_Str_DisplayFlag.SV_usDisplayTimer = ((*pV_ucBuffer).Time*2);    /*异常代码显示时间*/
    GV_Str_DisplayFlag.SV_ucDisplayMode = C_CardAbnormalDisplay;     /*异常插卡显示模式*/ 
    GV_CardAbnDisplayNum = (*pV_ucBuffer).Type;                         /*显示代码类型没有限制*/ 
}
/*******************************************************************************
函数原型：void SF_DisplayCardAbnormal(void) 
功能描述：插卡异常显示数据缓存处理，ERR--XX 
输入参数：无
输出参数：无
返回参数：无
调用位置：
备    注：显示缓存赋值 
*******************************************************************************/                                      
void SF_DisplayCardAbnormal( void )
{
    GV_KillZeroNum = C_SF_Err;          /*底层驱动入口函数，FF表示为异常代码显示*/

    GV_ucDisplayData[0] = GV_CardAbnDisplayNum;   /*显示异常代码*/
    GV_ucDisplayData[2] = C_DisE;                 /*显示异常代码*/
    GV_ucDisplayData[2] |= C_DisR;
    GV_ucDisplayData[1] = (C_DisR << 4);            /*显示异常代码*/
    GV_ucDisplayData[1] |= C_DisHenggang;         /*显示异常代码*/	 
}
/*******************************************************************************
函数原型：void SF_ClearDisplyBuff( void )
功能描述：清显示缓存数据及灭零个数全局变量，每500ms清1次数据
输入参数：无
输出参数：无
返回参数：
调用位置：
备    注：
*******************************************************************************/                                       
void SF_ClearDisplyBuff( void )
{
    memset(GV_ucDisplayData,0x00,C_DisplayDataByte);

    GV_KillZeroNum=0;                        /*清小数点*/
}
/*******************************************************************************
函数原型：void SF_DisLTData(void ) 
功能描述：显示费率号/阶梯号 数字
输入参数：无
输出参数：无
返回参数：无
调用位置：
备    注：
*******************************************************************************/                                        
void SF_DisLTData( void )
{
	ushort16 V_usLen, V_usDataEncode;
    uchar8 V_ucDataTemp=0;
	
    V_usLen = CLCurr_Rate_No;
    InF_Read_Data(CCurr_Rate_No, &V_ucDataTemp, &V_usLen, &V_usDataEncode);
    V_ucDataTemp = PF_HextoBCDOneBytes(V_ucDataTemp);
    GV_ucDisplayData[C_Rate18_offset] = V_ucDataTemp;
    if ( C_Meter_Type == C_L_SmartMeter )
    {
        V_usLen = CLCurr_Step_No;
        if ( InF_Read_Data(CCurr_Step_No, &V_ucDataTemp, &V_usLen, &V_usDataEncode) == C_OK )
        {
	        V_ucDataTemp = PF_HextoBCDOneBytes(V_ucDataTemp);
            GV_ucDisplayData[C_Ladder8_offset] = V_ucDataTemp;
        }
        else
        {
            GV_ucDisplayData[C_Ladder8_offset] = 0;
        }
    }
    else
    {
        GV_ucDisplayData[C_Ladder8_offset]=0;
    }
}
/*******************************************************************************
函数原型：void InF_Display_Message( Str_Msg_Parameter *pStr_Msg_Parameter )
功能描述：显示消息处理 
输入参数：Str_Msg_Parameter *pStr_Msg_Parameter,各消息参数传递结构体，调度发送
		typedef struct
		{
			uchar8 PowerFlag;
			uchar8 SourceAddr;
			uchar8 DerictAddr;
			uchar8 Length;
			uchar8 *Parameter;
		}Str_Msg_Parameter;
输出参数：无 
返回参数：
调用位置：
备    注：C_ParameterMaxLen:40 消息传递参数最大缓存，可能需要修改，最大只能放10个PT(4字节参数)
*******************************************************************************/                                  
void InF_Display_Message( Str_Msg_Parameter *pStr_Msg_Parameter )
{
    Str_Msg_Parameter Str_Msg_Parameter;
    Str_DisplayStatus Str_DisSign;
    ulong32 V_ulDi,V_ulRelatedDi;
    ushort16 V_usDisTime;
    uchar8 V_ucParameter[C_ParameterMaxLen],V_ucDisBuff[10];
    uchar8 V_uci;
    uchar8 V_ucPt;    /*参数类型*/
    uchar8 V_ucMoneySign=0;
    uchar8 V_ucDisStateSign;

    Str_Msg_Parameter.PowerFlag = pStr_Msg_Parameter->PowerFlag;
    Str_Msg_Parameter.SourceAddr = pStr_Msg_Parameter->SourceAddr;
    Str_Msg_Parameter.DerictAddr = pStr_Msg_Parameter->DerictAddr;
    Str_Msg_Parameter.Length = pStr_Msg_Parameter->Length;
    Str_Msg_Parameter.Parameter = pStr_Msg_Parameter->Parameter;   /*该处参数如何处理*/    
     
    if ( C_Msg_Display != Str_Msg_Parameter.DerictAddr )
    {
        return;   	 
    }

    if ( ( Str_Msg_Parameter.Length > C_ParameterMaxLen ) || ( 0 == Str_Msg_Parameter.Length ) )
    {
        return;   /*正常不存在*/
    }
	 
    for ( V_uci = 0; V_uci < Str_Msg_Parameter.Length; V_uci++ )
    {
        V_ucParameter[V_uci] = Str_Msg_Parameter.Parameter[V_uci];/*是否会出现数据长度不对*/
    }
   
    if ( C_Msg_Card == Str_Msg_Parameter.SourceAddr )  /*卡处理消息*/
    {
        if ( C_L_SmartMeter == C_Meter_Type )  /*只有本地表才进行卡显示相关处理*/
        {
            GV_CardDisSign = C_CardDis;   	  	 
        }
    }
      
    while( Str_Msg_Parameter.Length )   /*Pt解析*/
    {
        V_ucPt = V_ucParameter[0];
        switch( V_ucPt )
        {
            case Pt_Dispatch_Timing:  /*500ms，刷新显示*/
            {
                if ( Str_Msg_Parameter.Length < 2 )  /*该类型包括参数，数据长度*/
                {
                    return;    /*正常不存在*/
                }
                if ( C_HalfSecond == V_ucParameter[1] )  /*每500ms刷新显示*/
                {
                    Str_Msg_Parameter.Length -= 2;     /*该Pt类型数据长度*/
                    for ( V_uci = 0; V_uci < Str_Msg_Parameter.Length; V_uci++ )/*参数偏移*/
                    {
                        V_ucParameter[V_uci] = V_ucParameter[V_uci+2];
                    }

                    if ( C_PowerOff == Str_Msg_Parameter.PowerFlag )   /*低功耗*/
                    {
                        SF_PowerOffDisplay500msTimer();   
                    }
                    else
                    {   
                        SF_PowerOnDisplay500msTimer();
                    }
   	  	 	  	 	/********显示调用***********/
                    SF_ClearDisplyBuff();  /*显示缓存清零*/

                    if ( C_CardAbnormalDisplay != GV_Str_DisplayFlag.SV_ucDisplayMode ) /*异常插卡显示模式*/
                    {
                        SF_DisplyMainData(V_ucMoneySign);   /*主数据显示8位数字*/

                        SF_DisplayChinaese();  /*辅助汉字显示*/

                        SF_DisplayDI();        /*DI及序号显示*/	 
                    }
                    else
                    {
                        SF_DisplayCardAbnormal();  /*卡异常显示代码处理*/
                    }
    	  	 	   
                    SF_DisplayStateSign();  /*状态字符显示*/
                    if ( C_PowerOff != Str_Msg_Parameter.PowerFlag )   /*低功耗*/
                    {
                        SF_DisLTData();
                    }
                    else
                    {
                        ;
                    }
                    SF_DisAllData();        /*显示缓存置1，内部判断是否需要全屏显示*/
               
                    InF_WriteLCD(&GV_ucDisplayData[0], C_LCDLen, GV_KillZeroNum);  /*底层驱动显示*/
                }
                else
                {
                    return;
                }
                break;
            }
            case Pt_Dispatch_Key:  /*按键*/
            {
                if ( Str_Msg_Parameter.Length < 2 )
                {
                    return;    /*正常不存在*/
                }
                if ( (C_KeyUp == V_ucParameter[1]) || (C_KeyDown == V_ucParameter[1]) )   /*上、下翻键*/
                {
                    Str_Msg_Parameter.Length -= 2;     /*该Pt类型数据长度*/

                    SF_DisplyKey(V_ucParameter[1]);  /*按键显示处理*/      	  	 	  	 

                    for ( V_uci = 0; V_uci < Str_Msg_Parameter.Length; V_uci++ )/*参数偏移*/
                    {
                        V_ucParameter[V_uci] = V_ucParameter[V_uci + 2];
                    } 	  	 	  	 
                }
                else
                {
                    return;
                }
                break;
            }
            case Pt_DisplayID:  /*液晶查看*/
            {
                if ( Str_Msg_Parameter.Length < 12 )
                {
                    return;    /*正常不存在*/ 
                }

                PF_Buffer4ToUlong32(&V_ucParameter[1], &V_ulDi, 4);
                PF_Buffer4ToUlong32(&V_ucParameter[5], &V_ulRelatedDi, 4);	
                ushort16 V_usTimer;
                PF_Buffer2ToUshort16(&V_ucParameter[6+4], &V_usTimer);
                SF_CheckDisplay(V_ulDi,V_ulRelatedDi, V_ucParameter[9], V_usTimer);      /*液晶查看处理*/

                if ( GV_Str_DisplayFlag.CodeID == CChargeBal_Hex_Cent )
                {
                    SF_GetDisplayData(&V_ucDisBuff[0]);                   /*获取需要显示的数据，每屏显示需处理数据最大5个字节*/
                    PF_CopyDataBytes(&V_ucDisBuff[0], &GV_RemainMoney[0][0], CLChargeBal_BCD);
                }
                Str_Msg_Parameter.Length -= 12;     /*该Pt类型数据长度*/   	  	 	     	  	 	  
                for ( V_uci = 0; V_uci < Str_Msg_Parameter.Length; V_uci++ )/*参数偏移*/
                {
                    V_ucParameter[V_uci] = V_ucParameter[V_uci + 12];
                } 
                break;	  	 	  	 
            }
            case Pt_DisplayStatus:  /*状态字符处理*/
            {
                if ( Str_Msg_Parameter.Length < 4 )
                {
                    return;    /*正常不存在*/
                }

                PF_Buffer2ToUshort16(&V_ucParameter[2], &V_usDisTime);

                Str_DisSign.Time = V_usDisTime;
                Str_DisSign.Type = V_ucParameter[1];

                V_ucDisStateSign = Str_DisSign.Type&0x3F;
                if ( (V_ucDisStateSign == C_DoingSign) || (V_ucDisStateSign == C_SuccessSign) || (V_ucDisStateSign == C_ReadCardSign) )/*显示成功、读卡、中特殊处理；显示充值前剩余金额2s问题*/
                {
                    V_ucMoneySign = C_MoneySign;
                }           

                SF_DisplaySignMessage(&Str_DisSign, Str_Msg_Parameter.SourceAddr);/*状态显示字符处理*/

                Str_Msg_Parameter.Length -= 4;     /*该Pt类型数据长度*/  	  	 	     	  	 	  
                for ( V_uci = 0; V_uci < Str_Msg_Parameter.Length; V_uci++ )/*参数偏移*/
                {
                    V_ucParameter[V_uci] = V_ucParameter[V_uci+4];
                }
                break; 	  	 	  	 
            }
            case Pt_ERRXXDisplay:  /*卡异常显示*/
            {
                if ( Str_Msg_Parameter.Length < 4 )
                {
                    return;    /*正常不存在*/
                }

                PF_Buffer2ToUshort16(&V_ucParameter[2], &V_usDisTime); 

                Str_DisSign.Time = V_usDisTime;
                Str_DisSign.Type = V_ucParameter[1];

                SF_CardAbnormalDisDeal(&Str_DisSign);      /*插卡异常显示处理*/

                Str_Msg_Parameter.Length -= 4;     /*该Pt类型数据长度*/ 	  	 	     	  	 	  
                for ( V_uci = 0; V_uci < Str_Msg_Parameter.Length; V_uci++ )/*参数偏移*/
                {
                    V_ucParameter[V_uci] = V_ucParameter[V_uci+4];
                }
                break; 	  	 	  	 
            }   	  	 
            default:
            {
                return;         	
            }            	  	 
        }   	     	  
        if(Str_Msg_Parameter.Length < 2)  /*带参数，正常数据长度必须＞2*/
        {
            Str_Msg_Parameter.Length = 0;
        }   	  
    }
   
    if ( C_CardDis == GV_CardDisSign )   /*插卡显示，1路做到底*/
    {
        GV_CardDisSign = C_NoCardDis;

        SF_ClearDisplyBuff();  /*显示缓存清零*/

        if ( C_CardAbnormalDisplay != GV_Str_DisplayFlag.SV_ucDisplayMode ) /*异常插卡显示模式*/
        {
            SF_DisplyMainData(V_ucMoneySign);   /*插卡显示“成功、读卡、中”，不更新主数据显示8位数字*/
            V_ucMoneySign = 0;  	     	 

            SF_DisplayChinaese();  /*辅助汉字显示*/

            SF_DisplayDI();        /*DI及序号显示*/	 
        }
        else
        {
            SF_DisplayCardAbnormal();  /*卡异常显示代码处理*/
        }

        SF_DisplayStateSign();  /*状态字符显示*/
        SF_DisLTData();
        SF_DisAllData();        /*显示缓存置1，内部判断是否需要全屏显示*/

        InF_WriteLCD(&GV_ucDisplayData[0], C_LCDLen, GV_KillZeroNum);  /*底层驱动显示*/  	  
    }	   
}
/*******************************************************************************
函数原型：void SF_TimingFreshSignMesNum(void)
功能描述：定时刷新全局变量状态字符消息源，增加数据可靠性
输入参数：无
输出参数：无
返回参数：
调用位置：
备    注：在上电SF_PowerOnDisplay500msTimer中定时刷新
*******************************************************************************/                                   
void SF_TimingFreshSignMesNum( void )
{	 
	/*************************状态字符消息源刷新*******************************/
    GV_Str_DisplaySignMesNum_AxisSign[0].SourceNo = C_Msg_Communication;

    GV_Str_DisplaySignMesNum_Q1Sign[0].SourceNo = C_Msg_MeterIC;

    GV_Str_DisplaySignMesNum_Q2Sign[0].SourceNo = C_Msg_MeterIC;

    GV_Str_DisplaySignMesNum_Q3Sign[0].SourceNo = C_Msg_MeterIC;

    GV_Str_DisplaySignMesNum_Q4Sign[0].SourceNo = C_Msg_MeterIC;

    GV_Str_DisplaySignMesNum_LSign[0].SourceNo = C_Msg_EnergyMetering; 

    GV_Str_DisplaySignMesNum_TSign[0].SourceNo = C_Msg_Deal_MultiRates;

    GV_Str_DisplaySignMesNum_GPRSSign[0].SourceNo = C_Msg_Communication;

    GV_Str_DisplaySignMesNum_GPRSSignalSign1[0].SourceNo = C_Msg_Communication;

    GV_Str_DisplaySignMesNum_GPRSSignalSign2[0].SourceNo = C_Msg_Communication;

    GV_Str_DisplaySignMesNum_GPRSSignalSign3[0].SourceNo = C_Msg_Communication;

    GV_Str_DisplaySignMesNum_GPRSSignalSign4[0].SourceNo = C_Msg_Communication;

    GV_Str_DisplaySignMesNum_ModuleComSign[0].SourceNo = C_Msg_Communication;

    GV_Str_DisplaySignMesNum_ComSign[0].SourceNo = C_Msg_Communication;

    GV_Str_DisplaySignMesNum_ComChannel1Sign[0].SourceNo = C_Msg_Communication;

    GV_Str_DisplaySignMesNum_ComChannel2Sign[0].SourceNo = C_Msg_Communication;

    GV_Str_DisplaySignMesNum_ProgramEnableSign[0].SourceNo = C_Msg_Communication;

    GV_Str_DisplaySignMesNum_HoldUpSign[0].SourceNo = C_Msg_Communication;

    GV_Str_DisplaySignMesNum_PublicKeySign[0].SourceNo = C_Msg_Communication;

    GV_Str_DisplaySignMesNum_AlarmSign[0].SourceNo = C_Msg_PowerNetworkMonitoring;
    GV_Str_DisplaySignMesNum_AlarmSign[1].SourceNo = C_Msg_Deal_RelayStatus;
    GV_Str_DisplaySignMesNum_AlarmSign[2].SourceNo = C_Msg_BatteryVoltagleMetering;

    GV_Str_DisplaySignMesNum_ReadCardSign[0].SourceNo = C_Msg_Card;

    GV_Str_DisplaySignMesNum_DoingSign[0].SourceNo = C_Msg_Card;

    GV_Str_DisplaySignMesNum_SuccessSign[0].SourceNo = C_Msg_Card;

    GV_Str_DisplaySignMesNum_FailSign[0].SourceNo = C_Msg_Card;

    GV_Str_DisplaySignMesNum_PurchaseSign[0].SourceNo = C_Msg_Deal_RelayStatus;
    GV_Str_DisplaySignMesNum_PurchaseSign[1].SourceNo = C_Msg_Communication;
    GV_Str_DisplaySignMesNum_PurchaseSign[2].SourceNo = C_Msg_EnergyMetering;

    GV_Str_DisplaySignMesNum_OverdrawSign[0].SourceNo = C_Msg_EnergyMetering;

    GV_Str_DisplaySignMesNum_RealayOpenSign[0].SourceNo = C_Msg_Deal_RelayStatus;

    GV_Str_DisplaySignMesNum_UaSign[0].SourceNo = C_Msg_PowerNetworkMonitoring;
    GV_Str_DisplaySignMesNum_UaSign[1].SourceNo = C_Msg_MeterIC;

    GV_Str_DisplaySignMesNum_UbSign[0].SourceNo = C_Msg_PowerNetworkMonitoring;
    GV_Str_DisplaySignMesNum_UbSign[1].SourceNo = C_Msg_MeterIC;

    GV_Str_DisplaySignMesNum_UcSign[0].SourceNo = C_Msg_PowerNetworkMonitoring;
    GV_Str_DisplaySignMesNum_UcSign[1].SourceNo = C_Msg_MeterIC;

    GV_Str_DisplaySignMesNum_NegativePhaseSign[0].SourceNo = C_Msg_PowerNetworkMonitoring;

    GV_Str_DisplaySignMesNum_IaNegativeSign[0].SourceNo = C_Msg_PowerNetworkMonitoring;
    GV_Str_DisplaySignMesNum_IaNegativeSign[1].SourceNo = C_Msg_MeterIC;

    GV_Str_DisplaySignMesNum_IaSign[0].SourceNo = C_Msg_PowerNetworkMonitoring;
    GV_Str_DisplaySignMesNum_IaSign[1].SourceNo = C_Msg_MeterIC;

    GV_Str_DisplaySignMesNum_IbNegativeSign[0].SourceNo = C_Msg_PowerNetworkMonitoring;
    GV_Str_DisplaySignMesNum_IbNegativeSign[1].SourceNo = C_Msg_MeterIC;

    GV_Str_DisplaySignMesNum_IbSign[0].SourceNo = C_Msg_PowerNetworkMonitoring;
    GV_Str_DisplaySignMesNum_IbSign[1].SourceNo = C_Msg_MeterIC;

    GV_Str_DisplaySignMesNum_IcNegativeSign[0].SourceNo = C_Msg_PowerNetworkMonitoring;
    GV_Str_DisplaySignMesNum_IcNegativeSign[1].SourceNo = C_Msg_MeterIC;

    GV_Str_DisplaySignMesNum_IcSign[0].SourceNo = C_Msg_PowerNetworkMonitoring;
    GV_Str_DisplaySignMesNum_IcSign[1].SourceNo = C_Msg_MeterIC;

    GV_Str_DisplaySignMesNum_TimeTable1Sign[0].SourceNo = C_Msg_Deal_MultiRates;

    GV_Str_DisplaySignMesNum_TimeTable2Sign[0].SourceNo = C_Msg_Deal_MultiRates;

    GV_Str_DisplaySignMesNum_RTCBatterySign[0].SourceNo = C_Msg_BatteryVoltagleMetering;

    GV_Str_DisplaySignMesNum_PowerBatterySign[0].SourceNo = C_Msg_BatteryVoltagleMetering;

    GV_Str_DisplaySignMesNum_HoardingSign[0].SourceNo = C_Msg_Card;

    GV_Str_DisplaySignMesNum_HoardingSign[1].SourceNo = C_Msg_Communication;	 

    GV_Str_DisplaySignMesNum_CurrentStep[0].SourceNo = C_Msg_Deal_MultiRates;

    GV_Str_DisplaySignMesNum_BakStep[0].SourceNo = C_Msg_Deal_MultiRates;

    GV_Str_DisplaySignMesNum_BackLED[0].SourceNo = C_Msg_PowerNetworkMonitoring;
    GV_Str_DisplaySignMesNum_BackLED[1].SourceNo = C_Msg_Communication;
    GV_Str_DisplaySignMesNum_BackLED[2].SourceNo = C_Msg_Deal_RelayStatus;
    GV_Str_DisplaySignMesNum_BackLED[3].SourceNo = C_Msg_BatteryVoltagleMetering;
    GV_Str_DisplaySignMesNum_BackLED[4].SourceNo = C_Msg_Card;
    GV_Str_DisplaySignMesNum_BackLED[5].SourceNo = C_Msg_Display;

    GV_Str_DisplaySignMesNum_WarnOutPut[0].SourceNo = C_Msg_PowerNetworkMonitoring;
    GV_Str_DisplaySignMesNum_WarnOutPut[1].SourceNo = C_Msg_Deal_RelayStatus;
    GV_Str_DisplaySignMesNum_WarnOutPut[2].SourceNo = C_Msg_BatteryVoltagleMetering;
    GV_Str_DisplaySignMesNum_WarnOutPut[3].SourceNo = C_Msg_Communication;
    
    GV_Str_DisplaySignMesNum_Beeper[0].SourceNo = C_Msg_PowerNetworkMonitoring;
    GV_Str_DisplaySignMesNum_Beeper[1].SourceNo = C_Msg_Deal_RelayStatus;
    GV_Str_DisplaySignMesNum_Beeper[2].SourceNo = C_Msg_BatteryVoltagleMetering;
    GV_Str_DisplaySignMesNum_Beeper[3].SourceNo = C_Msg_Card;

    GV_Str_DisplaySignMesNum_RelayStatusLED[0].SourceNo = C_Msg_Deal_RelayStatus;
    GV_Str_DisplaySignMesNum_RelayStatusLED[1].SourceNo = C_Msg_Display;
    GV_Str_DisplaySignMesNum_RelayStatusLED[2].SourceNo = C_Msg_Communication;
}
#if(0)
/*******************************************************************************
函数原型：void SF_ReadDispBuff( uchar8 *pV_ucdatabuff )
功能描述：读显示状态 
输入参数：无 
输出参数：无 
返回参数：
调用位置：
备    注：
*******************************************************************************/    
void SF_ReadDispBuff( uchar8 *pV_ucdatabuff )
{
    uchar8  V_uci;
    for ( V_uci = 0; V_uci < C_DisplayDataByte; V_uci++ )
    {
        pV_ucdatabuff[V_uci] = GV_ucDisplayData[V_uci];
    }
}
/*******************************************************************************
函数原型：SF_DispAllScreenMode(void) 
功能描述：液晶全显模式
输入参数：无
输出参数：无
返回参数：
调用位置：
备    注：
*******************************************************************************/
uchar8  SF_DispAllScreenMode( void )
{
    return GV_DispAllScreenMode;
}
#endif
/*******************************************************************************
函数原型：void InF_Card_DispDynamicSign( void )
功能描述：插卡过程中显示------，其他字符保留
输入参数：无
输出参数：无
返回参数：
调用位置：Card模块使用
备    注：
*******************************************************************************/
void InF_Card_DispDynamicSign( void )
{	
	SF_ClearDisplyBuff();/*清显示缓存*/
	SF_DisplayStateSign();/*字符处理*/
	SF_DisLTData();/*显示LT*/
	InF_WriteLCD_DispDynamicSign(&GV_ucDisplayData[0],9);/*显示缓存增加------*/
}

/*******************************************************************************
函数原型：void SF_DispDataChange(uchar8 *pV_ucDispHexBuff, uchar8 *pV_ucDispBcdBuff, uchar8 V_ucHexDataLen, uchar8 V_ucBcdDataLen, uchar8 V_ucSign, uchar8 V_ucType)
功能描述：根据符号及转换格式，将HEX数据转换为BCD
输入参数：pV_ucDispHexBuff：待转换的HEX数据
          V_ucHexDataLen：HEX数据长度
          V_ucBcdDataLen：BCD数据长度  
          V_ucSign：是否有符号位
          V_ucType：转换类型
输出参数：pV_ucDispBcdBuff：转换后的BCD数据
返回参数：
调用位置：
备    注：
*******************************************************************************/
void SF_DispDataChange( uchar8 *pV_ucDispHexBuff, uchar8 *pV_ucDispBcdBuff, uchar8 V_ucHexDataLen, uchar8 V_ucBcdDataLen, uchar8 V_ucSign, uchar8 V_ucType )
{
    ulong64 V_ul64Data;
    ulong32 V_ulData;
    uchar8 V_uci, V_ucDataLen;
    
    if((V_ucHexDataLen == 0) || (V_ucBcdDataLen == 0))
    {
        return;
    }
    if( V_ucHexDataLen < V_ucBcdDataLen )/*不等的只有电能*/
    {
        if( V_ucType == 0 )/*默认整体HEX转BCD*/
        {
            PF_Buffer8ToUlong64(&pV_ucDispHexBuff[0], &V_ul64Data, V_ucHexDataLen);
            if(( V_ucSign != 0 ) && (pV_ucDispHexBuff[V_ucHexDataLen - 1] & 0x80) )/*有符号位的负数*/
            {      
                V_ul64Data |= (0xFFFFFFFFFFFFFFFF << (V_ucHexDataLen*8));
                V_ul64Data = ~V_ul64Data + 1;
                PF_Hex64toBCDBytes(&V_ul64Data, &pV_ucDispBcdBuff[0], &V_ucBcdDataLen);
                pV_ucDispBcdBuff[V_ucBcdDataLen - 1] |= 0x80;
            }
            else
            {
                PF_Hex64toBCDBytes(&V_ul64Data, &pV_ucDispBcdBuff[0], &V_ucBcdDataLen);
            }
        }
        else
        {
            memset(pV_ucDispBcdBuff, 0, V_ucBcdDataLen);
        }
    }
    else/*大于等于，转换后按BCD长度截取*/
    {
        if( V_ucType == 0 )/*默认整体HEX转BCD*/
        {
            PF_Buffer8ToUlong64(&pV_ucDispHexBuff[0], &V_ul64Data, V_ucBcdDataLen);
            if(( V_ucSign != 0 ) && (pV_ucDispHexBuff[V_ucHexDataLen - 1] & 0x80) )/*有符号位的负数*/
            {        
                V_ul64Data |= (0xFFFFFFFFFFFFFFFF << (V_ucBcdDataLen*8));
                V_ul64Data = ~V_ul64Data + 1;
                PF_Hex64toBCDBytes(&V_ul64Data, &pV_ucDispBcdBuff[0], &V_ucBcdDataLen);
                pV_ucDispBcdBuff[V_ucBcdDataLen - 1] |= 0x80;
            }
            else
            {
                PF_Hex64toBCDBytes(&V_ul64Data, &pV_ucDispBcdBuff[0], &V_ucBcdDataLen);
            }
        }
        else if( V_ucType == C_NoNeedChange )/*数据不需要转换*/
        {
            PF_CopyDataBytes(pV_ucDispHexBuff, pV_ucDispBcdBuff, V_ucBcdDataLen);
        }
        else if( V_ucType == C_NeedSingleByteChange )/*数据单字节转换*/
        {    
            for( V_uci = 0; V_uci<V_ucBcdDataLen; V_uci++)
            {
                if(pV_ucDispHexBuff[V_uci] <= 0x63)/*超1字节不转换*/
                {
                    pV_ucDispBcdBuff[V_uci] = PF_HextoBCDOneBytes(pV_ucDispHexBuff[V_uci]);
                }
                else
                {
                    pV_ucDispBcdBuff[V_uci] = pV_ucDispHexBuff[V_uci];
                }
            }
        }
        else if( V_ucType == C_NeedDataChange )/*数据按日期格式转换*/
        {
            if((V_ucBcdDataLen < 2) || (V_ucHexDataLen < 2))
            {
                memset(pV_ucDispBcdBuff, 0, V_ucBcdDataLen);
            }
            else
            {
                for( V_uci = 0; V_uci<(V_ucHexDataLen-2); V_uci++)
                {
                    if(pV_ucDispHexBuff[V_uci] <= 0x63)/*超1字节不转换*/
                    {
                        pV_ucDispBcdBuff[V_uci] = PF_HextoBCDOneBytes(pV_ucDispHexBuff[V_uci]);
                    }
                    else
                    {
                        pV_ucDispBcdBuff[V_uci] = pV_ucDispHexBuff[V_uci];
                    }
                }
                
                V_ucDataLen = 2;
                PF_Buffer4ToUlong32(&pV_ucDispHexBuff[V_ucHexDataLen-2], &V_ulData, 2);
                PF_HextoBCDBytes(&V_ulData, &pV_ucDispBcdBuff[V_ucHexDataLen-2], &V_ucDataLen);
            }
        }
        else
        {
            memset(pV_ucDispBcdBuff, 0, V_ucBcdDataLen);
        }
    }
}