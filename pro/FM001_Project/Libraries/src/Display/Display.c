/*******************************************************************************
Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     Display.c
Version:       V1
Author:        
Date:          2014-6-2
Description:   ��ʾ�����ļ� 
---------------------------------------------------------------------------------
History1:      ��1���޸�
����1. Date:   20211025
   	   Author: gjc
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
#include "Display.h"

/*******************************************************************************
����ԭ�ͣ�void InF_Display_Init(void)
�����������ϵ��ʼ���ӿں��������ȵ��á���ʼ����ʾģʽΪȫ�ԣ���ʾʱ��,״̬����ʾ��Կ��������Ų�������
        ����ԭ��״̬,��ʼ�����⡢��բָʾ��Ϊȫ��ʱ�䣬����ȫ��״̬����
�����������
�����������
���ز�������
����λ�ã�
��    ע��
*******************************************************************************/
void InF_Display_Init( void )
{	 
    Str_DisplaySignMesNum *pStr_DisplaySignMesNum;
	ushort16 V_usLen, V_usDataEncode;
    uchar8 V_i, V_j, V_ucALLDisTime;
#if(0)
    /*************************״̬�ַ���ʼ��*******************************/ 
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
    
    SF_TimingFreshSignMesNum();/*��ϢԴ��ʼ��*/
    
    GV_CardDisSign = C_NoCardDis;/*�ǲ忨��ʾ״̬*/
	 
    GV_KillZeroNum = 0;/*������*/
    V_usLen = CLPowerOn_Dis_All_Time;
    V_i = InF_Read_Data(CPowerOn_Dis_All_Time, &V_ucALLDisTime, &V_usLen, &V_usDataEncode);/*ȡ���ݲ��ϵ�ȫ��ʱ��*/
    /*PF_BCDtoHexBytes(&V_ucALLDisTime,&V_Hex,1); */       /*BCDתhex*/
    /*V_ucALLDisTime=(uchar8)V_Hex;*/
    V_ucALLDisTime <<= 1;   /*�ڲ���500ms��׼*/

    if ( ( C_OK != V_i ) || ( 0x00 == V_ucALLDisTime ) )  /*�����ݴ���*/
    {
        V_ucALLDisTime = C_DefaultDisplayTime5s;   /*ȡĬ��ȫ����ʾʱ�䣬5s*/
    }
	 
    for ( V_i = 0; V_i < GV_Str_DisplaySignLen; V_i++ )     /*״ָ̬ʾ�ַ������⡢ָʾ�ơ������̵�������*/
    {
        pStr_DisplaySignMesNum = (Str_DisplaySignMesNum *)(GV_Str_DisplaySign[V_i].PStr_DisplaySignMesNum);

        if ( C_RelayStatusLED == GV_Str_DisplaySign[V_i].StateNum )    /*��բָʾ��*/
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
            if ( C_BackLED == GV_Str_DisplaySign[V_i].StateNum )    /*�����*/
            {
                for ( V_j = 0; V_j < GV_Str_DisplaySign[V_i].Str_DisplaySignMesNumLen; V_j++ )
                {
                    pStr_DisplaySignMesNum[V_j].Timer = V_ucALLDisTime;
                }
            }
            else
            {
                if ( ( C_PublicKeySign == GV_Str_DisplaySign[V_i].StateNum ) 
                  || ( C_HoldUpSign == GV_Str_DisplaySign[V_i].StateNum ) )    /*��Կ�������֤���𣬲���������ԭ��״̬*/
                {
                    continue;
                }
                else    /*����״̬������ʼ��Ϊ����*/
                {
                    for ( V_j = 0; V_j < GV_Str_DisplaySign[V_i].Str_DisplaySignMesNumLen; V_j++ )
                    {
                        pStr_DisplaySignMesNum[V_j].Timer = C_NotDisplayNiu;
                    } 
                }
            }	
        }
    }
		 
    GV_Str_DisplayFlag.CodeID = C_ALLScreenDisplayDi;       /*��ʼ����ʾ״̬��ʶ*/
    GV_Str_DisplayFlag.P_ChieseTableNo = C_NULL;
    GV_Str_DisplayFlag.ChieseTableLineNo = 0;
    GV_Str_DisplayFlag.SV_DisplayDataOff = 0;
    GV_Str_DisplayFlag.Screen = 1;

    GV_Str_DisplayFlag.SV_usDisplayTimer = V_ucALLDisTime;
    GV_Str_DisplayFlag.SV_ucDisplayMode = C_ALLScreenDisplay;
    GV_Str_DisplayFlag.ParaNum = 0xFF;
    GV_Str_DisplayFlag.ParityTimer = 0x00;

    SF_DisAllData();        	  /*��ʾ������1���ڲ��ж��Ƿ���Ҫȫ����ʾ*/
               
    InF_WriteLCD(&GV_ucDisplayData[0], C_LCDLen, C_Notkillzero);  /*�ײ�������ʾ*/
    InF_SwithPeripherals(C_TripLed, C_On);      /*��բָʾ��*/
    InF_SwithPeripherals(C_BackLight, C_On);    /*����� */
    GV_TimingInitSignTime = 0;                   /*��ʱˢ��״̬�ַ�����Դ��ʱ����ʼ��*/ 
    GV_ShutBackLEDTime = 0;                      /*�ϵ米�����������ʱ��*/  
    /*GV_PowerOnChangeScreenFlag = 0;*/          /*������־*/

    for ( V_i = 0; V_i < CLChargeBal_BCD; V_i++ )/*ʣ��͸֧����ʼ��*/
    {
        GV_RemainMoney[0][V_i] = 0;
        GV_RemainMoney[1][V_i] = 0;		
    }

    InF_Clear_Engry_BorrowPoint();
}
/*******************************************************************************
����ԭ�ͣ�uchar8 InF_LocalAndRemoteMeterDiJudge( ulong32 V_ulDi )
�������������ݱ����жϵ�ǰ��ʶ���Ƿ�֧�ֱ��ء�Զ�̱�Զ�̱��ʶ�뱾�ر��У����Ե�����ΪԶ�̱�ʱ���б�ʶ���ж�
���������ulong32 V_ulDi�����жϱ�ʶ��
�����������
���ز�����uchar8,C_OK:��ʾ֧�ָñ�ʶ�룻C_IDError����ʾ��֧�ָñ�ʶ��
����λ�ã�
��    ע��
*******************************************************************************/                        
uchar8 InF_LocalAndRemoteMeterDiJudge( ulong32 V_ulDi )
{
    uchar8 V_uci;

    if(C_Meter_Type != C_L_SmartMeter)  /*Զ�̱�����ܱ�*/
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
                else  /*4λȫ�Ƚ�*/
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
    else    /*���ر�*/
    {
        return C_OK;
    }
}
/*******************************************************************************
����ԭ�ͣ�void InF_Display_WakeUpInit(void) 
����������ͣ�绽�ѳ�ʼ���ӿں��������ȵ��á���ʾģʽΪ�Զ�ѭ�Է�ʽ������Կ����������ԭ��״̬�⣬�����״̬��ʱ��ȫ������
�����������
�����������
���ز�����
����λ�ã�
��    ע��
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

    GV_CardDisSign = C_NoCardDis;   /*�ǲ忨��ʾ״̬*/

    GV_KillZeroNum = 0;         /*������*/
    GV_PowerOffDisState = C_ContinueReceive;         /*�͹�����ʾ״̬����ʼ��Ϊ��ʾ*/

    V_usLen = CLPer_Dis_Screen_Time;
    V_uci = InF_Read_Data(CPer_Dis_Screen_Time, &V_ucALLDisTime[0], &V_usLen, &V_usDataEncode);/*ȡ���ݲ��Զ�ѭ��ʱ��*/
    /*PF_BCDtoHexBytes(&V_ucALLDisTime,&V_Hex,1);*/        /*BCDתhex*/
    /*V_ucALLDisTime=(uchar8)V_Hex;*/
    PF_Buffer2ToUshort16(&V_ucALLDisTime[0], &V_usALLDisTime);
    V_usALLDisTime <<= 1;   /*�ڲ���500ms��׼*/

    if ( (C_OK != V_uci) || (0x00 == V_usALLDisTime) )  /*�����ݴ���*/
    {
        V_usALLDisTime = C_DefaultDisplayTime5s;   /*ȡĬ��ȫ����ʾʱ�䣬5s*/
    }
    GV_usPowerOffAutoDisScreenTime = V_usALLDisTime;   

    V_usLen = CLAuto_Dis_Screen_Num;
    V_uci = InF_Read_Data(CAuto_Dis_Screen_Num, &V_ucDisScreenNum, &V_usLen, &V_usDataEncode);/*ȡ���ݲ��Զ�ѭ������*/
    /*PF_BCDtoHexBytes(&V_ucDisScreenNum,&V_Hex,1); */             /*BCDתhex*/
    /*V_ucDisScreenNum=(uchar8)V_Hex;	*/
    if ( (C_OK != V_uci) || (0x00 == V_ucDisScreenNum) )
    {
        V_ucDisScreenNum = C_DefaultDisScreenNum;                   /*ȡĬ����ʾ����*/	    	 
    }	 
    GV_PowerOffAutoDisScreenNum = V_ucDisScreenNum;

    V_usPowerOffDisTime = V_usALLDisTime*V_ucDisScreenNum;           /*1��ѭ�����ڣ���ʾʱ��*/

    for ( V_uci = 0; V_uci < GV_Str_DisplaySignLen; V_uci++ )     /*״ָ̬ʾ�ַ�����*/
    {
        pStr_DisplaySignMesNum = (Str_DisplaySignMesNum *)GV_Str_DisplaySign[V_uci].PStr_DisplaySignMesNum;
        if ( (C_PublicKeySign == GV_Str_DisplaySign[V_uci].StateNum)
          || (C_HoldUpSign == GV_Str_DisplaySign[V_uci].StateNum) )    /*��Կ�������֤���𣬲���������ԭ��״̬*/
        {
            continue;
        }
        else    /*����״̬��ʱ������*/
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

    GV_Str_DisplayFlag.SV_usDisplayTimer = V_usPowerOffDisTime;    /*��ʼ����ʾ�ṹ��,1��ѭ��������ʾʱ��*/
    GV_Str_DisplayFlag.SV_ucDisplayMode = C_AutoDisplay;
    GV_Str_DisplayFlag.Screen = 0x00;                      /*ͳһ�ڵ͹���500ms�д���  */
    GV_Str_DisplayFlag.ParityTimer = 0x00;
   
#if(0)	 
    V_usLen = CLAuto_Dis_1ScreenCode;
    V_uci = InF_Read_Data(CAuto_Dis_1ScreenCode, &V_AutoDisNum[0], &V_usLen, &V_usDataEncode);/*ȡ���ݲ��Զ�ѭ����ʾ��1����ʾ����*/
    PF_Buffer4ToUlong32(&V_AutoDisNum[0], &V_Hex, 4);              /*��ʶ��ת��*/

    if ( (C_OK != V_uci) && (C_CrcErr_DataZero != V_uci) )
    {
        GV_Str_DisplayFlag.CodeID = C_DefaultDisDi;
        GV_Str_DisplayFlag.ParaNum = 0x00;
    }	 	 
    else
    {
        GV_Str_DisplayFlag.CodeID = V_Hex;
        V_uci = InF_Display_JudgeIDActive(V_Hex, V_AutoDisNum[4]);     /*�ж�DI����ʾ���Ƿ�Ϸ�*/
        if ( C_OK != V_uci )
        {
            GV_Str_DisplayFlag.CodeID = C_DefaultDisDi;
            V_AutoDisNum[4] = 0x00;
        }
        GV_Str_DisplayFlag.ParaNum = V_AutoDisNum[4];	    	  
    }
    SF_FindDisChieseTableNo();        /*������ʾȫ�ֽṹ�壬DI��Ӧ�ĺ��ֱ���к�*/

    SF_Disply();   /*��500ms����ʾ*/
#endif
}
/*******************************************************************************
����ԭ�ͣ�uchar8 InF_GetPowerOffDisplayState(void) 
�����������͹��Ļ�����ʾģʽ�£��������ȵ��ã���ȡ��ʾ��ǰ״̬(��ʾģ���ڲ��жϣ���ʾʱ���Ƿ񵽣�1��ѭ�����ڻ���
		 ��������30s��ģ���ڲ�����ʾ)�����ȸ��ݸ�״̬�жϣ��Ƿ��������ʾ��500ms��Ϣ
����������� 
�����������
���ز���������ͨѶ�궨��C_ContinueReceive��������ʾ״̬��C_AbortReceive����ʾ�ر�״̬
����λ�ã�
��    ע��
*******************************************************************************/                                     
uchar8 InF_GetPowerOffDisplayState( void )
{
    uchar8 V_ucPowerState;

    V_ucPowerState = InF_ReadPowerState();     /*��ȡ��ǰ�����״̬���е硢û��*/

    if ( C_PowerOn == V_ucPowerState )           /*�е�*/
    {
        GV_PowerOffDisState = C_ContinueReceive;/*����Ϊ��ʾģʽ*/
    }

    return  GV_PowerOffDisState;
}
/*******************************************************************************
����ԭ�ͣ�void SF_PowerOffDisplay500msTimer(void)
����������500ms��ʱ������ѭ��һ�����ڹر���ʾ���򰴼���ʾ��30s�޲����ر���ʾ������״̬�ַ�����ͬʱ�������õ�ǰ
		��ʾ״̬������ʾ�رջ��Ǽ�����ʾ��C_AbortReceive����������
�����������
�����������
���ز�����
����λ�ã�
��    ע��ʱ�䵽�ر���ʾ
*******************************************************************************/                                 
void  SF_PowerOffDisplay500msTimer( void )
{
    Str_DisplaySignMesNum *pStr_DisplaySignMesNum;
    ulong32 V_ulDi, V_ulRelatedDi;
	ushort16 V_usLen, V_usDataEncode;
    uchar8 V_uci, V_ucj;
    uchar8 V_ucAutoDisNum[CLAuto_Dis_1ScreenCode];

    if ( 0 == GV_Str_DisplayFlag.SV_usDisplayTimer )   /*��ʾ��ʱ��Ϊ�㣬����ʾ*/
    {
#if 0	/*test*/
        InF_SwitchOffLCD();
#endif
        GV_PowerOffDisState = C_AbortReceive;      /*�ر���ʾ*/  
	}
    else     /*��ʾʱ�䲻Ϊ��*/
    {
        if ( C_AutoDisplay == GV_Str_DisplayFlag.SV_ucDisplayMode )    /*�Զ�ѭ��ģʽ*/
        {
            if ( 0x00 == (GV_Str_DisplayFlag.SV_usDisplayTimer%GV_usPowerOffAutoDisScreenTime) )   /*�Ƿ���*/
            {
                GV_Str_DisplayFlag.Screen++;                            /*��ʾ������1*/

                if ( GV_Str_DisplayFlag.Screen > GV_PowerOffAutoDisScreenNum )	   /*�Զ���������,ѭ��1������*/
                {
                    /*InF_SwitchOffLCD(); */                       /*�ر���ʾ*/
                    GV_PowerOffDisState=C_AbortReceive;        /*�ر���ʾ*/
                }
                else             /*ѭ��*/
                {
                    V_usLen = CLAuto_Dis_1ScreenCode;
                    V_ulDi = CAuto_Dis_1ScreenCode&0xFFFFFF00;
                    V_ulDi = V_ulDi|GV_Str_DisplayFlag.Screen;
#if(0)
                    InF_Read_Data(V_ulDi,&V_ucAutoDisNum[0], &V_usLen, &V_usDataEncode);/*ȡ���ݲ��Զ�ѭ����ʾ��GV_Str_DisplayFlag.Screen����ʾ����*/
                    PF_Buffer4ToUlong32(&V_ucAutoDisNum[0], &V_ulDi, 4);              /*��ʶ��ת��*/

                    while ( InF_LocalAndRemoteMeterDiJudge(V_ulDi) )   /*��ʶ��֧�ֻ�1��ѭ������˳�ѭ��*/
                    {
                        GV_Str_DisplayFlag.Screen++;
                        if ( GV_Str_DisplayFlag.Screen > GV_PowerOffAutoDisScreenNum )	   /*�Զ���������,ѭ��1������*/
                        {
                            /*InF_SwitchOffLCD(); */                       /*�ر���ʾ*/
                            GV_PowerOffDisState = C_AbortReceive;        /*�ر���ʾ*/
                            break;
                        }
                        V_usLen = CLAuto_Dis_1ScreenCode;
                        V_ulDi = CAuto_Dis_1ScreenCode&0xFFFFFF00;
                        V_ulDi = V_ulDi|GV_Str_DisplayFlag.Screen;
                        InF_Read_Data(V_ulDi,&V_ucAutoDisNum[0], &V_usLen, &V_usDataEncode);/*ȡ���ݲ��Զ�ѭ����ʾ��GV_Str_DisplayFlag.Screen����ʾ����*/
                        PF_Buffer4ToUlong32(&V_ucAutoDisNum[0], &V_ulDi, 4);              /*��ʶ��ת��*/
                        PF_Buffer4ToUlong32(&V_ucAutoDisNum[C_DisRelatedOffset], &V_ulRelatedDi, 4);              /*��ʶ��ת��*/

                    }	 	  	  	  	 

                    V_usLen = CLAuto_Dis_1ScreenCode;
                    V_ulDi = CAuto_Dis_1ScreenCode&0xFFFFFF00;
                    V_ulDi = V_ulDi|GV_Str_DisplayFlag.Screen;

                    V_uci = InF_Read_Data(V_ulDi, &V_ucAutoDisNum[0], &V_usLen, &V_usDataEncode);/*ȡ���ݲ��Զ�ѭ����ʾ��GV_Str_DisplayFlag.Screen����ʾ����*/
                    PF_Buffer4ToUlong32(&V_ucAutoDisNum[0], &V_ulDi, 4);              /*��ʶ��ת��*/
                    PF_Buffer4ToUlong32(&V_ucAutoDisNum[C_DisRelatedOffset], &V_ulRelatedDi, 4);              /*��ʶ��ת��*/

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
                    V_uci = InF_Read_Data(V_ulDi, &V_ucAutoDisNum[0], &V_usLen, &V_usDataEncode);/*ȡ���ݲ��Զ�ѭ����ʾ��GV_Str_DisplayFlag.Screen����ʾ����*/
                    PF_Buffer4ToUlong32(&V_ucAutoDisNum[0], &V_ulDi, 4);        /*��ʶ��ת��*/
                    PF_Buffer4ToUlong32(&V_ucAutoDisNum[C_DisRelatedOffset], &V_ulRelatedDi, 4);              /*��ʶ��ת��*/
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
                    SF_FindDisChieseTableNo();        /*������ʾȫ�ֽṹ�壬DI��Ӧ�ĺ��ֱ���к�*/
                }
            }
            else         /*��ȫ���ж�*/            
            {
                V_uci = InF_Display_JudgeIDActive(GV_Str_DisplayFlag.CodeID, GV_Str_DisplayFlag.Related_CodeID, GV_Str_DisplayFlag.ParaNum);/*��ȫ���ж�*/
                if ( C_OK != V_uci )
                {
                    GV_Str_DisplayFlag.CodeID = C_DefaultDisDi;
                    GV_Str_DisplayFlag.Related_CodeID = C_DefaultDisDiRelated;
                    GV_Str_DisplayFlag.ParaNum = 0x00;
                    SF_FindDisChieseTableNo();        /*������ʾȫ�ֽṹ�壬DI��Ӧ�ĺ��ֱ���к�*/
                } 	  
            }
        }
        else         /*��ȫ���ж�*/             
        {
            V_uci = InF_Display_JudgeIDActive(GV_Str_DisplayFlag.CodeID, GV_Str_DisplayFlag.Related_CodeID, GV_Str_DisplayFlag.ParaNum);/*��ȫ���ж�*/
            if ( C_OK != V_uci )
            {
                GV_Str_DisplayFlag.CodeID = C_DefaultDisDi;
                GV_Str_DisplayFlag.Related_CodeID = C_DefaultDisDiRelated;
                GV_Str_DisplayFlag.ParaNum = 0x00;
                SF_FindDisChieseTableNo();        /*������ʾȫ�ֽṹ�壬DI��Ӧ�ĺ��ֱ���к�*/
            } 	  
        }
        GV_Str_DisplayFlag.SV_usDisplayTimer--;	    
    }
	 
    GV_Str_DisplayFlag.ParityTimer++;
    if( GV_Str_DisplayFlag.ParityTimer >= 4 )   /*��ż��ʱ��*/
    {
        GV_Str_DisplayFlag.ParityTimer = 0;	 	 
    }
    for ( V_uci = 0; V_uci < GV_Str_DisplaySignLen; V_uci++ )     /*״ָ̬ʾ�ַ������⡢ָʾ�ơ������̵�������*/
    {
        pStr_DisplaySignMesNum = (Str_DisplaySignMesNum *)GV_Str_DisplaySign[V_uci].PStr_DisplaySignMesNum;

        for ( V_ucj = 0; V_ucj < GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen; V_ucj++)
        {
            if ( (C_AlwaysDisplayNiu == pStr_DisplaySignMesNum[V_ucj].Timer)
              || (C_TwinkleDisplayNiu == pStr_DisplaySignMesNum[V_ucj].Timer)
              || (C_NotDisplayNiu == pStr_DisplaySignMesNum[V_ucj].Timer) )     /*���ԡ���˸������*/
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
����ԭ�ͣ�void SF_DisplayBorrowPoint_Rectify(void)
������������λ��ʾ����������ֹ��д���λλ����
	     ѭ�Ե�1�����жϴ洢С��λ���ͽ�����־�Ƚϣ�
		 ����ȣ�������С��λ�������㣬�����жϣ�
		 ��ȣ�������־��0��
�����������
�����������
���ز�������
����λ�ã���ʾ
��    ע��
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
����ԭ�ͣ�void SF_PowerOnDisplay500msTimer(void)
����������500ms��ʱ��������ʾ״̬�л���״̬�ַ���ʱ������ÿ500ms��ʾͳһˢ�¡��е�����£�����
		��բָʾ�ƣ���ʶ�벻ΪȫFFʱ(Һ���鿴ȫ����ʾ),��ʾ��Ϣ��բָʾ�ƶ�ʱ������(��500ms��ѯ�����) 
�����������
�����������
���ز�����
����λ�ã�
��    ע��
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
   
	/*V_DisSign = 0x55;*/    /*��ʶ����Ч���жϱ�־*/	 

	GV_TimingInitSignTime++;
	if(GV_TimingInitSignTime > C_TimingInitSignTime10min)  /*��ʱ����ˢ��״̬�ַ���ϢԴ*/
	{
		GV_TimingInitSignTime = 0;
		SF_TimingFreshSignMesNum();
	}	 
	 
	GV_ShutBackLEDTime++;                                /*��ʱ������������������е�ѹ�ж�*/ 
	if(GV_ShutBackLEDTime >= C_ShutBackLEDTime5s)
    {
        GV_ShutBackLEDTime = C_ShutBackLEDTime5s;
	}
	 
	GV_Str_DisplayFlag.ParityTimer++;
	if ( GV_Str_DisplayFlag.ParityTimer >= 4 )   			/*��ż��ʱ��*/
	{
        GV_Str_DisplayFlag.ParityTimer = 0;	 	 
	}
	 	 
    if ( 0 == GV_Str_DisplayFlag.SV_usDisplayTimer )   	/*��ʾ��ʱ��Ϊ�㣬�л�*/
	{
		V_usLen = CLPer_Dis_Screen_Time;
	    V_uci = InF_Read_Data(CPer_Dis_Screen_Time, &V_ucDisTime[0], &V_usLen, &V_usDataEncode);			/*ȡ���ݲ��Զ�ѭ��ʱ��*/
	    /*PF_BCDtoHexBytes(&V_ucDisTime, &V_Hex, 1);*/        /*BCDתhex*/
	    /*V_ucDisTime = (uchar8)V_Hex;*/
        PF_Buffer2ToUshort16(&V_ucDisTime[0], &V_usDisTime);
	    V_usDisTime <<= 1;   	    						/*�ڲ���500ms��׼*/
	    	    
	    if ( (C_OK != V_uci) || (0x00 == V_usDisTime) )
	    {
	    	V_usDisTime = C_DefaultDisplayTime5s;   		/*ȡĬ��ȫ����ʾʱ�䣬5s*/	    	 
	    }
	    
	    V_usLen = CLAuto_Dis_Screen_Num;
	    V_uci = InF_Read_Data(CAuto_Dis_Screen_Num, &V_ucDisScreenNum, &V_usLen, &V_usDataEncode);	/*ȡ���ݲ��Զ�ѭ������*/
	    /*PF_BCDtoHexBytes(&V_ucDisScreenNum, &V_Hex, 1); */   			/*BCDתhex*/
	    /*V_ucDisScreenNum = (uchar8)V_Hex;*/
	    
	    if ( (C_OK != V_uci) || (0x00 == V_ucDisScreenNum) )
	    {
			V_ucDisScreenNum = C_DefaultDisScreenNum;       			/*ȡĬ����ʾ����*/    	 
	    }

	    GV_Str_DisplayFlag.SV_usDisplayTimer = V_usDisTime;  			/*�Զ�����ʱ��*/
	    if ( C_AutoDisplay == GV_Str_DisplayFlag.SV_ucDisplayMode )    /*�Զ�ѭ��ģʽ*/
	    {
			GV_Str_DisplayFlag.Screen++;                            /*��ʾ������1*/
            if ( GV_Str_DisplayFlag.Screen > V_ucDisScreenNum )	        /*�Զ���������,ѭ��1������*/
            {
                GV_Str_DisplayFlag.Screen = 0x01;
                SF_DisplayBorrowPoint_Rectify();
            }
	    }
	    else
	    {
            GV_Str_DisplayFlag.SV_ucDisplayMode = C_AutoDisplay;    /*����Ϊ�Զ�ѭ��ģʽ*/
            GV_Str_DisplayFlag.Screen = 0x01;                       /*��һ��*/
	    }
	    
	    /*V_DisScreenNumTemp = GV_Str_DisplayFlag.Screen;*/  			 /*���ͱ�ʶ���Ƿ�֧���ж�*/
	   
	    V_usLen = CLAuto_Dis_1ScreenCode;
	    V_ulDi = CAuto_Dis_1ScreenCode & 0xFFFFFF00;
	    V_ulDi = V_ulDi | GV_Str_DisplayFlag.Screen;	    
	    V_uci = InF_Read_Data(V_ulDi, &V_ucAutoDisNum[0], &V_usLen, &V_usDataEncode);	/*ȡ���ݲ��Զ�ѭ����ʾ��GV_Str_DisplayFlag.Screen����ʾ����*/
	    PF_Buffer4ToUlong32(&V_ucAutoDisNum[0], &V_ulDi, 4);            /*��ʶ��ת��*/
#if(0)
		while ( InF_LocalAndRemoteMeterDiJudge(V_ulDi) )   				/*��ʶ��֧�ֻ�1��ѭ������˳�ѭ��*/
		{
			GV_Str_DisplayFlag.Screen++;
			if ( GV_Str_DisplayFlag.Screen > V_ucDisScreenNum )          /*��������������*/
			{
				GV_Str_DisplayFlag.Screen = 1;
				SF_DisplayBorrowPoint_Rectify( );
			}
			
			if ( V_DisScreenNumTemp == GV_Str_DisplayFlag.Screen )      /*ѭ��1������*/
			{
				V_DisSign = 0xaa;
				break;
			}
			
            V_usLen = CLAuto_Dis_1ScreenCode;
            V_ulDi = CAuto_Dis_1ScreenCode&0xFFFFFF00;
            V_ulDi = V_ulDi|GV_Str_DisplayFlag.Screen;	    
            V_uci = InF_Read_Data(V_ulDi, &V_ucAutoDisNum[0], &V_usLen, &V_usDataEncode);	/*ȡ���ݲ��Զ�ѭ����ʾ��GV_Str_DisplayFlag.Screen����ʾ����*/
            PF_Buffer4ToUlong32(&V_ucAutoDisNum[0], &V_ulDi, 4);          /*��ʶ��ת��*///
		}	 	  	  	  	 	 	  	 
	    	   
	    V_usLen = CLAuto_Dis_1ScreenCode;
	    V_ulDi = CAuto_Dis_1ScreenCode&0xFFFFFF00;
	    V_ulDi = V_ulDi|GV_Str_DisplayFlag.Screen;
	    
	    V_uci = InF_Read_Data(V_ulDi, &V_ucAutoDisNum[0], &V_usLen, &V_usDataEncode);		/*ȡ���ݲ��Զ�ѭ����ʾ��GV_Str_DisplayFlag.Screen����ʾ����*/
	    PF_Buffer4ToUlong32(&V_ucAutoDisNum[0], &V_ulDi, 4);              /*��ʶ��ת��*/
		PF_Buffer4ToUlong32(&V_ucAutoDisNum[C_DisRelatedOffset], &V_ulRelatedDI, 4);              /*��ʶ��ת��*/
 	 
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
        PF_Buffer4ToUlong32(&V_ucAutoDisNum[C_DisRelatedOffset], &V_ulRelatedDI, 4);              /*��ʶ��ת��*/
        
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
        SF_FindDisChieseTableNo();        /*������ʾȫ�ֽṹ�壬DI��Ӧ�ĺ��ֱ���к�*/
	    
	    /*GV_PowerOnChangeScreenFlag = 0x55;*/  /*������־*/
    }
    else     /*�л�ʱ��δ��*/
    {
        V_uci = InF_Display_JudgeIDActive(GV_Str_DisplayFlag.CodeID, GV_Str_DisplayFlag.Related_CodeID, GV_Str_DisplayFlag.ParaNum);/*��ȫ���ж�*/
        if ( C_OK != V_uci )
        {
            GV_Str_DisplayFlag.CodeID = C_DefaultDisDi;
            GV_Str_DisplayFlag.Related_CodeID = C_DefaultDisDiRelated;
            GV_Str_DisplayFlag.ParaNum = 0x00;
            SF_FindDisChieseTableNo();        /*������ʾȫ�ֽṹ�壬DI��Ӧ�ĺ��ֱ���к�*/
        } 	  
    }
    if ( 0 != GV_Str_DisplayFlag.SV_usDisplayTimer )
    {
        GV_Str_DisplayFlag.SV_usDisplayTimer--;
    }
	 
    for ( V_uci = 0; V_uci < GV_Str_DisplaySignLen; V_uci++ )     /*״ָ̬ʾ�ַ������⡢ָʾ�ơ������̵�������*/
    {
        pStr_DisplaySignMesNum = (Str_DisplaySignMesNum *)GV_Str_DisplaySign[V_uci].PStr_DisplaySignMesNum;

        for ( V_ucj = 0; V_ucj < GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen; V_ucj++)
        {
            if ( (C_AlwaysDisplayNiu == pStr_DisplaySignMesNum[V_ucj].Timer)
              || (C_TwinkleDisplayNiu == pStr_DisplaySignMesNum[V_ucj].Timer)
              || (C_NotDisplayNiu == pStr_DisplaySignMesNum[V_ucj].Timer) )     /*���ԡ���˸������*/
            {
                continue;
            }
            else
            {
                pStr_DisplaySignMesNum[V_ucj].Timer--;
                if ( C_RelayStatusLED == GV_Str_DisplaySign[V_uci].StateNum )   /*��բ��*/
                {
                    if ( C_ALLScreenDisplayDi != GV_Str_DisplayFlag.CodeID )  /*Һ���鿴��ȫ����ʾ*/
                    {	 	 		  
                        if ( C_Msg_Display == pStr_DisplaySignMesNum[V_ucj].SourceNo )
                        {
                            pStr_DisplaySignMesNum[V_ucj].Timer = 0;     /*����*/
                        }
                    }
                }       		 
            }
        }
    }	 	 
}
/*******************************************************************************
����ԭ�ͣ�uchar8 InF_Display_JudgeIDActive( ulong32 V_ulCodeID, ulong32 V_ulRelatedCodeID, uchar8 V_ucScreenNum )
�����������ж���ʾ��ʶ�뼰�ñ�ʶ���Ӧ����ʾ����Ƿ���ȷ������ʶ��ΪȫFFʱ��ֱ�ӷ���C_OK����������ʾ����ж�
���������ulong32 V_ulCodeID:���ж����ݱ�ʶ
        ulong32 V_ulRelatedCodeID:������ʾ�����ݱ�ʶ
		uchar8 V_ucScreenNum:�ñ�ʶ���Ӧ����ʾ���
�����������
���ز�����C_OK��ʾ��ʶ������ž���ȷ��C_IDError��ʶ���C_IDNumError��ʶ���Ӧ�����Ŵ� 
����λ�ã�����ʾ�ڲ��жϡ�ͨ���������Լ����Բ����ж�  
��    ע����ʾ��ŵ��жϣ����жϸ�����Ƿ񳬹��ñ�ʶ�����ķ�����
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
    if ( C_ALLScreenDisplayDi == V_ulCodeID )           /*��ʶ��ΪȫFF*/
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
	 	 	 
    for ( V_uci=0; V_uci<GV_Str_DisplayDI3TableLen; V_uci++ )  /*DI3�ж�*/
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
	 	 
    pStr_DisplayDI2Table = (Str_DisplayDI2Table *)GV_Str_DisplayDI3Table[V_uci].PDI2Table;  /*2�����ַ*/

    for ( V_ucj = 0; V_ucj < GV_Str_DisplayDI3Table[V_uci].DI2TableLen; V_ucj++ )  /*DI2�ж�*/
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

    pStr_DisplayDI1_0Table = (Str_DisplayDI1_0Table *)pStr_DisplayDI2Table[V_ucj].PDI1_0Table;  /*3�����ַ*/

    for ( V_uck = 0; V_uck < pStr_DisplayDI2Table[V_ucj].DI1_0TableLen; V_uck++ )  /*DI1\DI0����ʾ����ж�*/
    {
        if ( V_ucDi[1] == pStr_DisplayDI1_0Table[V_uck].DI1 )   /*��ͬDI0���*/
        {
	       
			/*#define C_DI0_Out0_ManyBorr_0  20*/     /*20��(���)����֧��DI0==00,�������ֱ����ȫ���ã������ƹ��ʳ��ޡ�ʧѹ��ʧ�������ݣ����㸨����ʾ���ʱ������ʾ��Ϊ20-20=0*/
			/*#define C_DI0_Out0_ManyBorr_4  24*/     /*24��(���)����֧��DI0==00,�������ֱ��û��ȫ�У�ֻ��ǰ24-20=4������ʱ�α�ʱ�����ڼ��յȣ����㸨����ʾ���ʱ������ʾ��Ϊ24-20=4*/
			/*#define C_DI0_Out0_ManyBorr_6  26*/     /*26��(���)����֧��DI0==00,�������ֱ��û��ȫ�У�ֻ��ǰ26-20=6��������ݱ��̼�¼�ȣ����㸨����ʾ���ʱ������ʾ��Ϊ26-20=6*/
			/*#define C_DI0_Out0_ManyBorr_1  21*/     /*21��(���)����֧��DI0==00,�������ֱ��û��ȫ�У�ֻ��ǰ21-20=1��������ʱ�α�ȣ����㸨����ʾ���ʱ������ʾ��Ϊ21-20=1*/
            /*case C_DI0_Out0_Many:*/    /*(���)����֧��DI0==00�������ֻ࣬��DI0���ֵ*/	       	  
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
		 	  
    if ( C_DI0_Out0_ManyBorr_0 != pStr_DisplayDI1_0Table[V_uck].DI0Character )/*������OAD*/
    {
        /*������������Ϊ00��������������1��2��ʼ������������0��*/
        if ( pStr_DisplayDI1_0Table[V_uck].MaxDisplayScreen == 1 )
        {
            if ( V_ucScreenNum != 0 )
            {
                return C_IDNumError;	 
            }
        }
        else
        {
            if ( (V_ucScreenNum > pStr_DisplayDI1_0Table[V_uck].MaxDisplayScreen)   /*����������,��ʾ������Ŵ�0��ʼ*/
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
        PF_Ulong32ToBuffer4(&V_ucDi[0], &V_ulRelatedCodeID, 4);/*�����б�*/

        V_ucDi[1] &= 0x0f;/*ȥ����������*/

        if ( C_ALLScreenDisplayDi == V_ulCodeID )           /*��ʶ��ΪȫFF*/
        {
            return C_IDNumError;	 
        }

        for ( V_uci = 0; V_uci < GV_Str_DisplayDI3TableLen; V_uci++ )  /*DI3�ж�*/
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

        pStr_DisplayDI2Table = (Str_DisplayDI2Table *)GV_Str_DisplayDI3Table[V_uci].PDI2Table;  /*2�����ַ*/

        for ( V_ucj = 0; V_ucj < GV_Str_DisplayDI3Table[V_uci].DI2TableLen; V_ucj++ )  /*DI2�ж�*/
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

        pStr_DisplayDI1_0Table = (Str_DisplayDI1_0Table *)pStr_DisplayDI2Table[V_ucj].PDI1_0Table;  /*3�����ַ*/

        for ( V_uck = 0; V_uck < pStr_DisplayDI2Table[V_ucj].DI1_0TableLen; V_uck++ )  /*DI1\DI0����ʾ����ж�*/
        {
            if ( V_ucDi[1] == pStr_DisplayDI1_0Table[V_uck].DI1 )   /*��ͬDI0���*/
            {
			       
            	/*#define C_DI0_Out0_ManyBorr_0  20*/     /*20��(���)����֧��DI0==00,�������ֱ����ȫ���ã������ƹ��ʳ��ޡ�ʧѹ��ʧ�������ݣ����㸨����ʾ���ʱ������ʾ��Ϊ20-20=0*/
            	/*#define C_DI0_Out0_ManyBorr_4  24*/     /*24��(���)����֧��DI0==00,�������ֱ��û��ȫ�У�ֻ��ǰ24-20=4������ʱ�α�ʱ�����ڼ��յȣ����㸨����ʾ���ʱ������ʾ��Ϊ24-20=4*/
            	/*#define C_DI0_Out0_ManyBorr_6  26*/     /*26��(���)����֧��DI0==00,�������ֱ��û��ȫ�У�ֻ��ǰ26-20=6��������ݱ��̼�¼�ȣ����㸨����ʾ���ʱ������ʾ��Ϊ26-20=6*/
            	/*#define C_DI0_Out0_ManyBorr_1  21*/     /*21��(���)����֧��DI0==00,�������ֱ��û��ȫ�У�ֻ��ǰ21-20=1��������ʱ�α�ȣ����㸨����ʾ���ʱ������ʾ��Ϊ21-20=1*/
                /*case C_DI0_Out0_Many: */   /*(���)����֧��DI0==00�������ֻ࣬��DI0���ֵ*/	       	  
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

        if ( C_DI0_Out0_ManyBorr_0 != pStr_DisplayDI1_0Table[V_uck].DI0Character )/*������OAD*/
        {
            /*������������Ϊ00��������������1��2��ʼ������������0��*/
            if ( pStr_DisplayDI1_0Table[V_uck].MaxDisplayScreen == 1 )
            {
                if ( V_ucScreenNum != 0 )
                {
                    return C_IDNumError;	 
                }
            }
            else
            {
                if ( (V_ucScreenNum > pStr_DisplayDI1_0Table[V_uck].MaxDisplayScreen)   /*����������,��ʾ������Ŵ�0��ʼ*/
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
����ԭ�ͣ�uchar8 SF_FindDisChieseScreenLen( uchar8 V_ucScreenMaxNum, uchar8 V_ucDICharacter )
������������ȡ�ñ�ʶ���Ӧ���ֱ���У�ʵ����������,����3�������
���������uchar8 V_ucScreenMaxNum:�ñ�ʶ��֧�������ʾ����
		uchar8 V_ucDICharacter:�ñ�ʶ������ 
�����������
���ز�����uchar8:�ñ�ʶ��ʵ����ʾ����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_FindDisChieseScreenLen( uchar8 V_ucScreenMaxNum, uchar8 V_ucDICharacter )
{
    uchar8 V_ucLen = 0;

    if ( V_ucDICharacter < C_DI0_Out0_ManyBorr )
    {
        V_ucLen = V_ucScreenMaxNum;         /*����ȫ�У��������⴦��*/
    }
    else
    {
        if ( (V_ucDICharacter >= C_DI0_Out0_ManyBorr)
          && (V_ucDICharacter < C_DI0_OutManyBorr) )   /*���������У������⴦��*/
        {
            V_ucLen = V_ucDICharacter - C_DI0_Out0_ManyBorr;  	 	  	 	  
        }
    }
    return V_ucLen; 	  	 	  
}
/*******************************************************************************
����ԭ�ͣ�void SF_FindDisChieseTableNo_General( Str_DisplayDI3Table Str_DisplayDI3Table, ulong32 V_ulCodeDi )
��������������1��2��3����񼰾�̬�ֲ���������ʾ�ṹ��DI����ʾ��ţ������Ҹ�DI��ʶ���Ӧ�Ľṹ��,�õ��ñ�ʶ��
		���ں��ֱ��ṹ�塢���ֱ��ṹ�����кż���ʾ����ƫ�ơ�
���������Str_DisplayDI3Table Str_DisplayDI3Table:������3����ṹ�����
        V_ulCodeDi����ʶ��
�����������
���ز�������
����λ�ã�
��    ע���������˺���ʹ��ע���ڲ������˶�
		 ͨ�ô���
         1������ʱ������Ŵ�1��ʼ�����������⣨4851 4852 �ز�������ſ���Ϊ00,01,02��
		 2���������������Ϊ0��
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
	  && ( GV_Str_DisplayFlag.ParaNum == 0 ) )	/*������Ϊ00��01��02������ʾ������ͬ����Ϊ������*/
    {
        V_ucDisplayParaNum = 1;
	}
	else
	{
		V_ucDisplayParaNum = GV_Str_DisplayFlag.ParaNum;
	}
	
	V_usLine = 0;             /*�������ֱ���к�*/
	V_usDisplayDataOff = 0;   /* ����ƫ��*/
       
	PF_Ulong32ToBuffer4(&V_ucDi[0], &V_ulCodeDi, 4);
		 
	GV_Str_DisplayFlag.P_ChieseTableNo = (Str_DisplayDI3Table).P_ChieseTable; 	/*�������ֽṹ��*/
		 
	V_usLineMax = (Str_DisplayDI3Table).ChieseTableLen; 	/*���ֱ���Ӧ������ݳ��ȣ��ж��Ƿ�Խ����*/
	
	pStr_DisplayDI2Table = (Str_DisplayDI2Table *)((Str_DisplayDI3Table).PDI2Table);  /*2�����ַ*/
   	 
	          	 
	for ( V_ucj = 0; V_ucj < (Str_DisplayDI3Table).DI2TableLen; V_ucj++ )		/*���ݱ�ʶ��DI2���㣬�������ֱ���к��ۼӣ�2����,���Ҹñ�ʶ�����ں��ֱ���к�*/
	{
		if ( V_ucDi[2] == pStr_DisplayDI2Table[V_ucj].DI2 )
		{
			break;	 	  	
		}
		else
		{
			pStr_DisplayDI1_0Table = (Str_DisplayDI1_0Table *)pStr_DisplayDI2Table[V_ucj].PDI1_0Table;
			for ( V_uck = 0; V_uck < pStr_DisplayDI2Table[V_ucj].DI1_0TableLen; V_uck++ )   /*�������ֱ���к��ۼ�,3����*/
			{
				V_ucDi1_0Len = SF_FindDisChieseScreenLen(pStr_DisplayDI1_0Table[V_uck].MaxDisplayScreen,pStr_DisplayDI1_0Table[V_uck].DI0Character);/*��ȡ�ñ�ʶ�룬��Ӧ���ֱ��ʵ����������*/
				V_usLine += V_ucDi1_0Len;	 	  	 	  
			}
		}	 	  
	}
	if ( V_ucj >= (Str_DisplayDI3Table).DI2TableLen )
	{
		return;        /*����������*/ 	 
	}
	 
	pStr_DisplayDI1_0Table = (Str_DisplayDI1_0Table *)pStr_DisplayDI2Table[V_ucj].PDI1_0Table;   
	for ( V_uck = 0; V_uck < pStr_DisplayDI2Table[V_ucj].DI1_0TableLen; V_uck++ )   /*���ݱ�ʶ��DI1���㣬���ֱ�����кţ�3����*/
    {   
		if ( V_ucDi[1] == pStr_DisplayDI1_0Table[V_uck].DI1 )   /*��ͬDI0���*/
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

				V_ucDi1_0Len = SF_FindDisChieseScreenLen(pStr_DisplayDI1_0Table[V_uck].MaxDisplayScreen, pStr_DisplayDI1_0Table[V_uck].DI0Character);		/*��ȡ�ñ�ʶ�룬��Ӧ���ֱ��ʵ����������*/
				V_usLine += V_ucDi1_0Len;	 	  	 	  	 	  	 	  	 	 
			}
		}
		else
		{
			V_ucDi1_0Len = SF_FindDisChieseScreenLen(pStr_DisplayDI1_0Table[V_uck].MaxDisplayScreen, pStr_DisplayDI1_0Table[V_uck].DI0Character);		/*��ȡ�ñ�ʶ�룬��Ӧ���ֱ��ʵ����������*/
			V_usLine += V_ucDi1_0Len;	 	  	 	  	 	  	 
		}
    }	 
	if ( V_uck >= pStr_DisplayDI2Table[V_ucj].DI1_0TableLen )
	{
        return;        /*����������*/	 
	}

 /***************************************������ʾ�кż�����ƫ�Ƶ�ַ����*******************************/
	 
	V_ucDi1_0Len = SF_FindDisChieseScreenLen(pStr_DisplayDI1_0Table[V_uck].MaxDisplayScreen, pStr_DisplayDI1_0Table[V_uck].DI0Character);			/*��ȡ�ñ�ʶ�룬��Ӧ���ֱ��ʵ����������*/
	
	if ( 0x00 == V_ucDi1_0Len )
	{
		return;   /*�ô�����ʵ�ʺ��ֱ���н��õĲ��ҽ��ñ������������*/
	}
	if ( V_ucDisplayParaNum > V_ucDi1_0Len )         /*��ʾ���>=������ʾ������������ʾ�кż�����ƫ�Ƶ�ַ����(�ڼ���)*/
	{
		if ( ( V_usLine + V_ucDi1_0Len - 1 ) >= V_usLineMax )     /*����������*/
		{
			return;	
		}
	 	else
	 	{
			for ( V_uci = 0; V_uci < V_ucDi1_0Len; V_uci++ )  		/*ƫ�Ƶ�ַ����*/
			{
				pV_ucChieseTable = (uchar8 *)(GV_Str_DisplayFlag.P_ChieseTableNo + (V_usLine + V_uci) * C_ChineseSignLen);  /*���ֱ��ṹ���ַ*/	 	     	  
				V_usDisplayDataOff += (pV_ucChieseTable[C_ChinaLineDataLenKillZero] & C_GetChinaDataLenBit0x07);		  /*��3λΪ��ʾ���ݳ���*/	 	  	 	     
			}
         	pV_ucChieseTable = (uchar8 *)(GV_Str_DisplayFlag.P_ChieseTableNo + (V_usLine + V_ucDi1_0Len - 1) * C_ChineseSignLen);  /*���ֱ��ṹ���ַ*/	 	     	  
	 	    V_usDisplayDataOff += (V_ucDisplayParaNum - V_ucDi1_0Len - 1) * (pV_ucChieseTable[C_ChinaLineDataLenKillZero] & C_GetChinaDataLenBit0x07);  /*ƫ�Ƽ��㣬���1�������ֱ����ͬ*/
	 	 }
	 	 V_usLine += (V_ucDi1_0Len - 1);	 	  
	 }
	else
	{
        if ( V_ucDi1_0Len == 1 )
		{
			pV_ucChieseTable = (uchar8 *)(GV_Str_DisplayFlag.P_ChieseTableNo + (V_usLine + (V_ucDisplayParaNum) ) * C_ChineseSignLen);  /*���ֱ��ṹ���ַ*/
		}
		else
		{
			pV_ucChieseTable = (uchar8 *)(GV_Str_DisplayFlag.P_ChieseTableNo + (V_usLine + (V_ucDisplayParaNum - 1) ) * C_ChineseSignLen);  /*���ֱ��ṹ���ַ*/
		}
		if ( C_NoOffset != pV_ucChieseTable[C_ChinaeseLineDataOffSet] )  /*�о���ƫ�Ƶ�ַ�Ļ������ֱ��϶�ȫ��*/
		{
			V_usDisplayDataOff = pV_ucChieseTable[C_ChinaeseLineDataOffSet];	/*ȡ����ƫ�Ƶ�ַ*/
		}
		else
		{
			if ( V_ucDi1_0Len > 1 )	/*һ����ʾ������ƫ��Ϊ0*/
			{
				if ( (V_usLine + V_ucDisplayParaNum - 1) >= V_usLineMax )
				{
					return;    /*����������*/
				}

				for ( V_uci = 0; V_uci < (V_ucDisplayParaNum - 1); V_uci++ )  /*ƫ�Ƶ�ַ����*/
				{
					pV_ucChieseTable = (uchar8 *)(GV_Str_DisplayFlag.P_ChieseTableNo + (V_usLine + V_uci) * C_ChineseSignLen);  /*���ֱ��ṹ���ַ*/
					V_usDisplayDataOff += (pV_ucChieseTable[C_ChinaLineDataLenKillZero] & C_GetChinaDataLenBit0x07);		  /*��3λΪ��ʾ���ݳ���*/	 	  	 	     
				}
			}
		}	
		  
		if ( V_ucDi1_0Len == 1 )
		{
			V_usLine += V_ucDisplayParaNum;	/*Ӧ����0��*/
		}
		else
		{
			V_usLine += V_ucDisplayParaNum - 1;
        }
    }
	 	 	 
    if ( V_usLine >= V_usLineMax )
    {
        return;     /*����������*/
    }	 
	 
    GV_Str_DisplayFlag.ChieseTableLineNo = V_usLine; 
    GV_Str_DisplayFlag.SV_DisplayDataOff = V_usDisplayDataOff; 
	 	 
}
/*******************************************************************************
����ԭ�ͣ�void SF_FindDisChieseTableNo(void) 
��������������1��2��3����񼰾�̬�ֲ���������ʾ�ṹ��DI����ʾ��ţ������Ҹ�DI��ʶ���Ӧ�Ľṹ��,�õ��ñ�ʶ��
		���ں��ֱ��ṹ�塢���ֱ��ṹ�����кż���ʾ����ƫ�ơ�  
�����������
�����������
���ز�������
����λ�ã�
��    ע��
���⴦������:
	����(��ͬ��ʾ���ݣ�ֻ���˶�ʱ���ᣬͬ˲ʱ���ᡢDI2���⴦������DI2=0)  
	�������޼�¼(ֻ��������ʾ�����������޹�������ʾ��λ��DI1���⴦������DI1=1)��
	��ѹ�ϸ���(ֻ�б��µ�ѹ�ϸ��ʣ�����ABC������ABC����ʾ��DI1���⴦������DI1=0)��  
	��̼�¼(���10���������ʶ�룬ֻ�����1����ǰ4��)��
	ʱ�α���(���ֱ��ֻ��ǰ4��,)��
	ʱ������(���ֱ��ֻ��ǰ4��,)
	�����ձ��(ͬ�й����״̬�ֱ�̡��޹����״̬��1��2��̣���ʾ�ַ��������⴦��DI1���⴦������DI1=7) 
	�ڼ��ձ��(���ֱ��ֻ��ǰ4��),���ʲ�������(ֻ��ǰ4��,��ʾ�����ַ���1-4),
	���ݱ���(��ǰ�׵�1-6����ֵ\��ǰ�׽��ݵ��1-7\��ǰ�����1-4������(ÿ��ֻ��1����һ����6�������⴦��) 
	����Ǽ�¼(ͬ����ť�ǣ�DI1���⴦������DI1=0D)��
	ʧѹ10��¼(ֻ��A��ʧѹ�����ֱ����"A""ʧѹ"��DI2���⴦������DI2=1����ʧѹ��,ͬǷѹ11����ѹ12������13��ֻ�м���
���ֱ��ƫ��ʱ��ת��ΪDI3=10���㣬��ʶ����жϲ��ñ�ʶ�룩����ʾ�ַ����⴦�� 
	ʧ��18(ֻ��A��ʧѹ�����ֱ���С�A������ʧ������ͬ����19������1A��DI2���⴦������DI2=1)����ʾ�ַ����⴦��
	��ѹ������(ֻ�е�ѹ������ͬ������������ʾ�����ȫһ���������������ʷ���1B������1C(���й��ʷ�����أ���ABC����ʾ����������)��DI2���⴦������DI2=1)�� ��ʾ�ַ����⴦�� 
	��ѹ��ƽ��(ͬ������ƽ�⡢�������ز�ƽ�⣬��ȫ���ò������⴦��),  
	��������1F(ֻ���ܹ�����������ABC�ࡰ��ʾ�������������ڲ�����DI2���⴦������DI2=0)����ʾ�ַ����⴦��
	��բ��¼(ֻ����բ��¼��ͬ��բ��¼���������⴦��),  
	����ʱ������ʱ�α�ֻ�е�1������ֻ�е�1�ף�ͬ�ڶ��ף�DI2���⴦������DI2=1��
	���ݱ�������ֻ�е�ǰ��,ͬ�����ף���ֻ�н���ֵ�����ݵ�ۡ������գ�DI1���⴦������DI2=4��
	���ʵ��(ͬ�����ף�DI1���⴦������DI1=1)��
*******************************************************************************/                                        
void SF_FindDisChieseTableNo( void )
{
    ulong32 V_ulDI32; 
    ushort16 V_usLine, V_usDisplayDataOff;
    uchar8 V_uci;
    uchar8 V_ucDi[4];

    V_usLine = 0;             /*�������ֱ���к�*/
    V_usDisplayDataOff = 0;   /* ����ƫ��*/
	 	 
    GV_Str_DisplayFlag.ChieseTableLineNo = V_usLine; 
    GV_Str_DisplayFlag.SV_DisplayDataOff = V_usDisplayDataOff; 
   
    if ( C_ALLScreenDisplayDi == GV_Str_DisplayFlag.CodeID )   /*��ʶ��ΪȫFF*/
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
	
    for ( V_uci = 0; V_uci < GV_Str_DisplayDI3TableLen; V_uci++ )  /*1����*/
    {
        if ( V_ucDi[3] == (GV_Str_DisplayDI3Table[V_uci].DI3) )/*�жϸ�4�ֽ�*/
        {
            break;	 	  	
        }
    }
    if (V_uci >= GV_Str_DisplayDI3TableLen )
    {
        return;                              /*����������*/	 	  
    }
    
#if(0)	 
	if ( ( (V_ucDi[3]&0xF0) == 0x30) || ( (V_ucDi[3]&0xF0) == 0x50 ) )
	{
		if ( (V_ucDi[3]&0xF0) == 0x50) && (V_ucDi[1] == 0x02) )
        /*�¼���¼�Ͷ������ʾ��ʽ���չ���OAD��ʽ*///
        {
            V_ulDI32 = GV_Str_DisplayFlag.Related_CodeID;
            PF_Ulong32ToBuffer4(&V_ucDi[0], &V_ulDI32, 4);
        }	
	}
#endif

	if ( GV_Str_DisplayFlag.Related_CodeID != 0xFFFFFFFF )/*�������б�*/
	{
        V_ulDI32 = GV_Str_DisplayFlag.Related_CodeID;
        PF_Ulong32ToBuffer4(&V_ucDi[0], &V_ulDI32, 4);
        V_ucDi[1] &= 0x0f;/*ȥ����������*/
        V_ulDI32 &= 0xffff0fff;/*ȥ����������*/


        for ( V_uci = 0; V_uci < GV_Str_DisplayDI3TableLen; V_uci++ )  /*1����*/
        {
            if ( V_ucDi[3] == (GV_Str_DisplayDI3Table[V_uci].DI3) )/*�жϸ�4�ֽ�*/
            {
                break;	 	  	
            }
        }
        if ( V_uci >= GV_Str_DisplayDI3TableLen )
        {
            return;                              /*����������*/	 	  
        }
	}

    SF_FindDisChieseTableNo_General(GV_Str_DisplayDI3Table[V_uci], V_ulDI32);     /*ͨ�������ݴ����������⴦��*/
 	 
}
/*******************************************************************************
����ԭ�ͣ�void SF_DisplyKey(uchar8 V_ucKeyType)
����������������ʾ����
���������uchar8 V_ucKeyType:�������� ��C_KeyUp���Ϸ�����C_KeyDown���·�����
�����������
���ز�������
����λ�ã�
��    ע���Ϸ����·�������������ʾ���������60s���رձ����̵���������������ǰΪȫ����ʾģʽʱ��״̬�ַ���������
		���е�û�紦���е�Һ����ʾʱ������Ϊ60s��û��Һ����ʾʱ������Ϊ30s 
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
    
       
    /*V_DisSign=0x55; */   /*��ʶ����Ч���жϱ�־*/

    V_ucPowerState = InF_ReadPowerState();     /*��ȡ��ǰ�����״̬���е硢û��*/
    if ( C_PowerOff == V_ucPowerState )          /*û�磬��ʾʱ������Ϊ30s*/
    {
        V_usLen = CLNEScreenDisplay;
        V_uci = InF_Read_Data(CNEScreenDisplay, &V_uctimer[0], &V_usLen, &V_usDataEncode);/*ȡ����ѭ��ʱ��*/
        /*PF_BCDtoHexBytes(&V_uctimer[0],&V_Hex,2);*/        /*BCDתhex*/
        PF_Buffer2ToUshort16(&V_uctimer[0], &V_usTempData);
        V_usTempData <<= 1;   	    /*�ڲ���500ms��׼*/
        if ( (C_OK != V_uci) || (0x00 == V_usTempData) )
        {
            V_usTempData = C_Display30s;                   /*������ʾʱ��*/ 
        }
        
        GV_Str_DisplayFlag.SV_usDisplayTimer = V_usTempData;
    }
    else    /*�е�����´���*/                          
    {
        for ( V_uci = 0; V_uci < GV_Str_DisplaySignLen; V_uci++ )     /*״ָ̬ʾ�ַ��������̵���,������,���ⶨʱ������*/
        {
            pStr_DisplaySignMesNum = (Str_DisplaySignMesNum *)GV_Str_DisplaySign[V_uci].PStr_DisplaySignMesNum;
            if ( (C_WarnOutPut == GV_Str_DisplaySign[V_uci].StateNum) || (C_Beeper == GV_Str_DisplaySign[V_uci].StateNum) )  /*�رձ����̵����������*/
            {
                for ( V_ucj = 0; V_ucj < GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen; V_ucj++ )
                {
                    pStr_DisplaySignMesNum[V_ucj].Timer = C_NotDisplayNiu;    /*��ʱ������*/
                }
            }
            if ( C_BackLED == GV_Str_DisplaySign[V_uci].StateNum )              /*�������ʱ��,60s*/
            {
                for ( V_ucj = 0; V_ucj < GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen; V_ucj++ )
                {
                    if ( C_Msg_Display == pStr_DisplaySignMesNum[V_ucj].SourceNo )
                    {
                        V_usLen = CLBacklightTime;
                        V_ucReturnFlag = InF_Read_Data(CBacklightTime, &V_uctimer[0], &V_usLen, &V_usDataEncode);/*ȡ����ѭ��ʱ��*/
                        PF_Buffer2ToUshort16(&V_uctimer[0], &V_usTempData);
                        if ( (C_OK != V_ucReturnFlag) || (0x00 == V_usTempData) )
                        {
                            pStr_DisplaySignMesNum[V_ucj].Timer = C_Display60s;                   /*������ʾʱ��*/
                        }
                        else
                        {
                            pStr_DisplaySignMesNum[V_ucj].Timer = 2 * V_usTempData + 1;  /*�ڲ���500ms��׼*/
                        }
                        break;	 	 
                    }
                }	
            }	 	    	   
        }

        V_usLen = CLPer_Dis_Screen_Time;
        V_uci = InF_Read_Data(CPerkey_Dis_Screen_Time, &V_uctimer[0], &V_usLen, &V_usDataEncode);/*ȡ����ѭ��ʱ��*/
        /*PF_BCDtoHexBytes(&V_uctimer[0],&V_Hex,1); */       /*BCDתhex*/
        PF_Buffer2ToUshort16(&V_uctimer[0], &V_usTempData);
        V_usTempData <<= 1;   	    /*�ڲ���500ms��׼*/
        if ( (C_OK != V_uci) || (0x00 == V_usTempData) )
        {
            V_usTempData = C_Display60s;                   /*������ʾʱ��*/ 
        }
        
        GV_Str_DisplayFlag.SV_usDisplayTimer = V_usTempData;
    }
	 
    V_usLen = CLKey_CycDis_Screen_Num;
    V_uci = InF_Read_Data(CKey_CycDis_Screen_Num, &V_ucDisScreenNum, &V_usLen, &V_usDataEncode);/*ȡ���ݲ㰴����ʾ����*/
    /*PF_BCDtoHexBytes(&V_ucDisScreenNum,&V_Hex,1); */             /*BCDתhex*/
    /*V_ucDisScreenNum=(uchar8)V_Hex;	*/ 
    if ( (C_OK != V_uci) || (0x00 == V_ucDisScreenNum) )
    {
        V_ucDisScreenNum = C_DefaultDisScreenNum;                   /*ȡĬ����ʾ����*/ 
    }                                                          /*����ȫ0*/

    if ( C_KeyDisplay == GV_Str_DisplayFlag.SV_ucDisplayMode )        /*������ʾģʽ*/
    {
        if ( C_KeyUp == V_ucKeyType )                                  /*�Ϸ���*/
        {
            GV_Str_DisplayFlag.Screen--;
            if ( 0 == GV_Str_DisplayFlag.Screen )                       /*��ʾ������ת*/
            {
                GV_Str_DisplayFlag.Screen = V_ucDisScreenNum;
            }	
#if(0)
            V_DisScreenNumTemp = GV_Str_DisplayFlag.Screen;

            V_usLen = CLKey_Dis_1ScreenCode;
            V_ulDi = CKey_Dis_1ScreenCode&0xFFFFFF00;
            V_ulDi = V_ulDi|GV_Str_DisplayFlag.Screen;
            InF_Read_Data(V_ulDi, &V_ucAutoDisNum[0], &V_usLen, &V_usDataEncode);/*ȡ���ݲ㰴����ʾ��GV_Str_DisplayFlag.Screen����ʾ����*/
            PF_Buffer4ToUlong32(&V_ucAutoDisNum[0], &V_ulDi, 4);              /*��ʶ��ת��*/

            while ( InF_LocalAndRemoteMeterDiJudge(V_ulDi) )   /*��ʶ��֧�ֻ�1��ѭ������˳�ѭ��*/
            {
                GV_Str_DisplayFlag.Screen--;
                if ( 0 == GV_Str_DisplayFlag.Screen )                       /*��ʾ������ת*/
                {
                    GV_Str_DisplayFlag.Screen = V_ucDisScreenNum;
                }
                if ( V_DisScreenNumTemp == GV_Str_DisplayFlag.Screen )   /*ѭ��1������*/
                {
                    V_DisSign = 0xaa;
                    break;
                }
                V_usLen = CLKey_Dis_1ScreenCode;
                V_ulDi = CKey_Dis_1ScreenCode&0xFFFFFF00;
                V_ulDi = V_ulDi|GV_Str_DisplayFlag.Screen;
                InF_Read_Data(V_ulDi, &V_ucAutoDisNum[0], &V_usLen, &V_usDataEncode);/*ȡ���ݲ㰴����ʾ��GV_Str_DisplayFlag.Screen����ʾ����*/
                PF_Buffer4ToUlong32(&V_ucAutoDisNum[0], &V_ulDi, 4);              /*��ʶ��ת��*/
            }	
#endif
        }
        else                                                       /*�·���*/
        {
            GV_Str_DisplayFlag.Screen++;
            if ( GV_Str_DisplayFlag.Screen > V_ucDisScreenNum )            /*��������������*/
            {
                GV_Str_DisplayFlag.Screen = 1;
            }
#if(0)
            V_DisScreenNumTemp = GV_Str_DisplayFlag.Screen;

            V_usLen = CLKey_Dis_1ScreenCode;
            V_ulDi = CKey_Dis_1ScreenCode&0xFFFFFF00;
            V_ulDi = V_ulDi|GV_Str_DisplayFlag.Screen;
            InF_Read_Data(V_ulDi, &V_ucAutoDisNum[0], &V_usLen, &V_usDataEncode);/*ȡ���ݲ㰴����ʾ��GV_Str_DisplayFlag.Screen����ʾ����*/
            PF_Buffer4ToUlong32(&V_ucAutoDisNum[0], &V_ulDi, 4);              /*��ʶ��ת��*/

            while ( InF_LocalAndRemoteMeterDiJudge(V_ulDi) )   /*��ʶ��֧�ֻ�1��ѭ������˳�ѭ��*/
            {
                GV_Str_DisplayFlag.Screen++;
                if ( GV_Str_DisplayFlag.Screen > V_ucDisScreenNum )            /*��������������*/
                {
                    GV_Str_DisplayFlag.Screen = 1;
                }
                if ( V_DisScreenNumTemp == GV_Str_DisplayFlag.Screen )   /*ѭ��1������*/
                {
                    V_DisSign = 0xaa;
                    break;
                }
                V_usLen = CLKey_Dis_1ScreenCode;
                V_ulDi = CKey_Dis_1ScreenCode&0xFFFFFF00;
                V_ulDi = V_ulDi|GV_Str_DisplayFlag.Screen;
                InF_Read_Data(V_ulDi, &V_ucAutoDisNum[0], &V_usLen, &V_usDataEncode);/*ȡ���ݲ㰴����ʾ��GV_Str_DisplayFlag.Screen����ʾ����*/
                PF_Buffer4ToUlong32(&V_ucAutoDisNum[0], &V_ulDi, 4);              /*��ʶ��ת��*/
            }
#endif
        }
    }
    else
    {
        GV_Str_DisplayFlag.SV_ucDisplayMode = C_KeyDisplay;        /*����Ϊ������ʾģʽ*/
        GV_Str_DisplayFlag.Screen = 1;
#if(0)	
        V_DisScreenNumTemp = GV_Str_DisplayFlag.Screen;	

        V_usLen = CLKey_Dis_1ScreenCode;
        V_ulDi = CKey_Dis_1ScreenCode&0xFFFFFF00;
        V_ulDi = V_ulDi|GV_Str_DisplayFlag.Screen;
        InF_Read_Data(V_ulDi, &V_ucAutoDisNum[0], &V_usLen, &V_usDataEncode);/*ȡ���ݲ㰴����ʾ��GV_Str_DisplayFlag.Screen����ʾ����*/
        PF_Buffer4ToUlong32(&V_ucAutoDisNum[0], &V_ulDi, 4);    /*��ʶ��ת��*/

        while ( InF_LocalAndRemoteMeterDiJudge(V_ulDi) )   /*��ʶ��֧�ֻ�1��ѭ������˳�ѭ��*/
        {
            GV_Str_DisplayFlag.Screen++;
            if ( GV_Str_DisplayFlag.Screen > V_ucDisScreenNum )            /*��������������*/
            {
                GV_Str_DisplayFlag.Screen = 1;
            }
            if ( V_DisScreenNumTemp == GV_Str_DisplayFlag.Screen )   /*ѭ��1������*/
            {
                V_DisSign = 0xaa;
                break;
            }
            V_usLen = CLKey_Dis_1ScreenCode;
            V_ulDi = CKey_Dis_1ScreenCode&0xFFFFFF00;
            V_ulDi = V_ulDi|GV_Str_DisplayFlag.Screen;
            InF_Read_Data(V_ulDi, &V_ucAutoDisNum[0], &V_usLen, &V_usDataEncode);/*ȡ���ݲ㰴����ʾ��GV_Str_DisplayFlag.Screen����ʾ����*/
            PF_Buffer4ToUlong32(&V_ucAutoDisNum[0], &V_ulDi, 4);              /*��ʶ��ת��*/
        }	 
#endif
    }	 

    V_usLen = CLKey_Dis_1ScreenCode;
    V_ulDi = CKey_Dis_1ScreenCode&0xFFFFFF00;
    V_ulDi = V_ulDi|GV_Str_DisplayFlag.Screen;

    V_uci = InF_Read_Data(V_ulDi, &V_ucAutoDisNum[0], &V_usLen, &V_usDataEncode);/*ȡ���ݲ㰴����ʾ��GV_Str_DisplayFlag.Screen����ʾ����*/
    PF_Buffer4ToUlong32(&V_ucAutoDisNum[0], &V_ulDi, 4);              /*��ʶ��ת��*/
    PF_Buffer4ToUlong32(&V_ucAutoDisNum[C_DisRelatedOffset], &V_ulRelatedDI, 4);              /*��ʶ��ת��*/
	 
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
        PF_Buffer4ToUlong32(&V_ucAutoDisNum[C_DisRelatedOffset], &V_ulDi, 4);              /*��ʶ��ת��*/
        GV_Str_DisplayFlag.Related_CodeID  = V_ulDi;
        GV_Str_DisplayFlag.ParaNum = 0x00;

        V_uci = InF_Display_JudgeIDActive(GV_Str_DisplayFlag.CodeID, GV_Str_DisplayFlag.Related_CodeID,V_ucAutoDisNum[C_DisScreenNumOffset]);  /*��ȫ���ж�*/

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
    SF_FindDisChieseTableNo();        /*������ʾȫ�ֽṹ�壬DI��Ӧ�ĺ��ֱ���к�*/
}
/*******************************************************************************
����ԭ�ͣ�void SF_CheckDisplay( ulong32 V_ulDi, ulong32 V_ulRelated_CodeID, uchar8 V_ucDisScreenNum, ushort16 V_usTimer )
����������Һ���鿴ģʽ�������⣬����ʱ��Ϊ10s����ΪȫFFʱ����բָʾ�ƣ�����ʱ��Ϊ10s���ڲ������ⶨʱ���� 
		�˳�Һ���鿴ģʽʱ���˳���ģʽָʾ�ƶ�ʱ������,��ʶ�벻ΪȫFFʱ,����Ϣָʾ�ƶ�ʱ��Ҳ����(��500ms��ѯ�����)
���������ulong32 V_ulDi:Һ���鿴���ݱ�ʾ�� 
        ulong32 V_ulRelated_CodeID��������ʾ���ʶ
        uchar8 V_ucDisScreenNum�������ݱ�ʾ��Ӧ����ʾ����� 
        ushort16 V_usTimer��Һ���鿴��ʾʱ��
�����������
���ز�������
����λ�ã�
��    ע��
*******************************************************************************/                                       
void SF_CheckDisplay( ulong32 V_ulDi,ulong32 V_ulRelated_CodeID, uchar8 V_ucDisScreenNum, ushort16 V_usTimer )
{
    ushort16 V_usHex, V_usLen, V_usDataEncode;
    uchar8 V_uci, V_ucj;
    uchar8 V_uctimer[2], V_ucReturnFlag;

    Str_DisplaySignMesNum *pStr_DisplaySignMesNum;

    for ( V_uci = 0; V_uci < GV_Str_DisplaySignLen; V_uci++ )     /*�������10s,��DIΪȫFF����բָʾ��Ҳ����10s*/
    {
        pStr_DisplaySignMesNum = (Str_DisplaySignMesNum *)GV_Str_DisplaySign[V_uci].PStr_DisplaySignMesNum;
        if ( C_BackLED == GV_Str_DisplaySign[V_uci].StateNum ) 
        {
            for ( V_ucj = 0; V_ucj < GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen; V_ucj++ )
            {
                if ( C_Msg_Display == pStr_DisplaySignMesNum[V_ucj].SourceNo )
                {
                    V_usLen = CLSViewBacklightTime;
                    V_ucReturnFlag = InF_Read_Data(CSViewBacklightTime, &V_uctimer[0], &V_usLen, &V_usDataEncode);/*ȡ����ѭ��ʱ��*/
                    PF_Buffer2ToUshort16(&V_uctimer[0], &V_usHex);
                    if ( (C_OK != V_ucReturnFlag) || (0x00 == V_usHex) )
                    {
                        pStr_DisplaySignMesNum[V_ucj].Timer = C_Display10s+1;                   /*������ʾʱ��*/ 
                    }
                    else
                    {
                        pStr_DisplaySignMesNum[V_ucj].Timer = 2 * V_usHex + 1;  /*�ڲ���500ms��׼*/
                    }
                    break;	 	 
                }
            }	 	   	  
        }       
	 	 	
        if ( C_RelayStatusLED == GV_Str_DisplaySign[V_uci].StateNum )   /*��բ��*/
        {
            if ( C_ALLScreenDisplayDi == V_ulDi )  /*ȫ����ʾ��ʶ��*/
            {
                for ( V_ucj = 0; V_ucj < GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen; V_ucj++)
                {
                    if ( C_Msg_Display == pStr_DisplaySignMesNum[V_ucj].SourceNo )
                    {
                        V_usLen = CLSViewBacklightTime;
                        V_ucReturnFlag = InF_Read_Data(CSViewBacklightTime, &V_uctimer[0], &V_usLen, &V_usDataEncode);/*ȡ����ѭ��ʱ��*/
                        PF_Buffer2ToUshort16(&V_uctimer[0], &V_usHex);
                        if ( (C_OK != V_ucReturnFlag) || (0x00 == V_usHex) )
                        {
                            pStr_DisplaySignMesNum[V_ucj].Timer = C_Display10s + 1;                   /*������ʾʱ��*/ 
                        }
                        else
                        {
                            pStr_DisplaySignMesNum[V_ucj].Timer = 2 * V_usHex + 1;  /*�ڲ���500ms��׼*/
                        }

                        break;	

                    }
                } 
            }
        }       
    }	
	 
    GV_Str_DisplayFlag.CodeID = V_ulDi;
    GV_Str_DisplayFlag.Related_CodeID = V_ulRelated_CodeID;
    GV_Str_DisplayFlag.SV_usDisplayTimer = 2*V_usTimer;    /*Һ���鿴��ʾʱ��,10s*/
    if ( GV_Str_DisplayFlag.SV_usDisplayTimer == 0 )
    {
        GV_Str_DisplayFlag.SV_usDisplayTimer = C_Display10s;/*Ĭ��10S*/
    }

    GV_Str_DisplayFlag.SV_ucDisplayMode = C_CheckDisplay;
    GV_Str_DisplayFlag.ParaNum = V_ucDisScreenNum;

    V_uci = InF_Display_JudgeIDActive(GV_Str_DisplayFlag.CodeID,GV_Str_DisplayFlag.Related_CodeID,GV_Str_DisplayFlag.ParaNum);  /*��ȫ���ж�*/

    if ( C_OK != V_uci )
    {
        GV_Str_DisplayFlag.CodeID = C_DefaultDisDi;
        GV_Str_DisplayFlag.Related_CodeID = C_DefaultDisDiRelated;
        GV_Str_DisplayFlag.ParaNum = 0x00;
    }

    SF_FindDisChieseTableNo();        /*������ʾȫ�ֽṹ�壬DI��Ӧ�ĺ��ֱ���к�*/
}
/*******************************************************************************
����ԭ�ͣ�void SF_DisplaySignMessage( Str_DisplayStatus *pV_ucBuffer, uchar8 V_ucSourceMesNum )
�����������ַ���ʾ�����ú�����������Ϣ��Ҫ��ʾ�ַ��Ĳ�������ֵΪ��ʾ�ڲ���̬������ʾ�ַ�
���������Str_DisplayStatus *pV_ucBuffer��״̬�ַ���ʾ���� 
		typedef struct 
		{ 
			ushort16 Time; ��ʾʱ�䣬����ܴ���65535/2�룬��ʾ�ڲ���500msΪ��׼ 
			uchar8 Type��
		}Str_DisplayStatus;
	uchar8 V_ucSourceMesNum:Դ��Ϣ��
�����������
���ز�������
����λ�ã�
��    ע������ʡ����ޡ��ź�ǿ��ͬһʱ��ֻ��һ����ʾ�������ַ���������ʱ����ֵ����һ��������ͬ����
		��ʱ������,�ź�ǿ���б��ʱ����1���ź�ǿ�ȣ�������1���ź� 
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
        ushort16 Time;/*Time����ʾ��ʾʱ�䣻*/
        uchar8 Type;  /*Type����ʾ�ַ�����ʾ��ʽ����ͬһ���ֽڣ����ֽڵĸ���λ��ʾ��ʾ��ʽ*/
                 /*(01:��˸��00���رգ�11����,����������ʾʱ��Ϊ0xFFFFʱ����ʾ���ԣ�*/
                 /*�о���ʱ��ֵʱ����ʾʱ�䰴����ʱ��)����6λ��ʾ��ʾ��ʾ�ַ�����(LED���̵������Ҳ��Ϊһ���ַ�)��*/
    }Str_DisplayStatus;
#endif	 
    V_ucSign = Str_Buffer.Type & 0x3F;   /*ȡ��6λ*/
	 
    switch ( Str_Buffer.Type&0xC0 )    /*ȡ��2λ*/
    {
        case C_TwinkleDisplay:                       /*��˸*/
        {
            V_usDisTime = C_TwinkleDisplayNiu;
            break;
        }
        case C_NotDisplay:                       /*����*/
        {
            V_usDisTime = C_NotDisplayNiu;
            break;
        }
        case C_AlwaysDisplay:                       /*���Ի�̶�ʱ��*/
        {
            if ( C_AlwaysDisplayNiu == (Str_Buffer).Time )   /*0xFFFF*/
            {
                V_usDisTime = C_AlwaysDisplayNiu;	 	  	 	  
            }	 	  	  
            else
            {
                V_usDisTime = (Str_Buffer).Time*2;	        /*����ܴ���65535/2�룬��ʾ�ڲ���500msΪ��׼*/
            }
            break;
        }
        default:
            V_usDisTime = C_NotDisplayNiu;
            break;
    }

    for ( V_uci = 0; V_uci < GV_Str_DisplaySignLen; V_uci++ )     /*״ָ̬ʾ�ַ�����ʱ������*/
    {
        if ( V_ucSign == GV_Str_DisplaySign[V_uci].StateNum )
        {
            break;	 	  	 	   	 
        }
    }
    if ( V_uci >= GV_Str_DisplaySignLen )
    {
        return;                                  /*����������*/	 	 	   
    }
	            
    pStr_DisplaySignMesNum = (Str_DisplaySignMesNum *)(GV_Str_DisplaySign[V_uci].PStr_DisplaySignMesNum);
    for ( V_ucj = 0; V_ucj < GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen; V_ucj++ )   /*����ʾ״̬�ַ���ʱ������*/
    {
        /*PV_Str_DisplaySignMesNum=(Str_DisplaySignMesNum *)(GV_Str_DisplaySign[V_uci].PStr_DisplaySignMesNum+V_ucj*sizeof(Str_DisplaySignMesNum));  */
        if ( V_ucSourceMesNum == pStr_DisplaySignMesNum[V_ucj].SourceNo )   /*��Ҫ������ʱ��*/
        {
            pStr_DisplaySignMesNum[V_ucj].Timer = V_usDisTime;   
            break;
        }	 	     
    }
    if ( V_ucj >= GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen )
    {
        return;                                  /*����������*/	 	 	   
    }
	 	 
    for ( V_uck = 0; V_uck < GV_Str_DisplaySignLen; V_uck++ )     /*���໥��״̬�ַ�����*/
    {
        if ( V_uck == V_uci )                               /*����ʾ״̬�ַ���ʱ���Ѵ���*/
        {  
            continue;	 	   	   
        }
        else
        {
            pStr_DisplaySignMesNum = (Str_DisplaySignMesNum *)GV_Str_DisplaySign[V_uck].PStr_DisplaySignMesNum;
            switch ( GV_Str_DisplaySign[V_uck].StateNum )
            {
                case C_Q1Sign:                    /*���޴���*/
                case C_Q2Sign:
                case C_Q3Sign:
                case C_Q4Sign:
                {
                    if ( (C_Q1Sign == V_ucSign) || (C_Q2Sign == V_ucSign)     /*���޴���*/	 	   	  
                      || (C_Q3Sign == V_ucSign) || (C_Q4Sign == V_ucSign) )
                    {	 
                        for ( V_ucj = 0; V_ucj < GV_Str_DisplaySign[V_uck].Str_DisplaySignMesNumLen; V_ucj++)   /*����ʾ״̬�ַ���ʱ������*/
                        {
                            if ( V_ucSourceMesNum == pStr_DisplaySignMesNum[V_ucj].SourceNo )   /*��Ҫ������ʱ��*/
                            {
                                pStr_DisplaySignMesNum[V_ucj].Timer = C_NotDisplayNiu;   
                                break;
                            }	 	     
                        }
                        if ( V_ucj >= GV_Str_DisplaySign[V_uck].Str_DisplaySignMesNumLen )	
                        {
                            return;                            /*����������*/ 	                 	  
                        }	 	
                    }
                    break;
                }
#if(0)
                case C_Step1Sign:                    /*���ݴ���*/
                case C_Step2Sign:
                case C_Step3Sign:
                case C_Step4Sign:
                {
                    if ( (C_Step1Sign == V_ucSign) || (C_Step2Sign == V_ucSign)     	   	  
                      || (C_Step3Sign == V_ucSign) || (C_Step4Sign == V_ucSign) )  
                    {
                        for ( V_ucj = 0; V_ucj < GV_Str_DisplaySign[V_uck].Str_DisplaySignMesNumLen; V_ucj++ )   /*����ʾ״̬�ַ���ʱ������*/
                        {
                            if ( V_ucSourceMesNum == pStr_DisplaySignMesNum[V_ucj].SourceNo )   /*��Ҫ������ʱ��*/
                            {
                                pStr_DisplaySignMesNum[V_ucj].Timer = C_NotDisplayNiu;   
                                break;
                            }	 	     
                        }
                        if ( V_ucj >= GV_Str_DisplaySign[V_uck].Str_DisplaySignMesNumLen )	
                        {
                            return;                            /*����������*/ 	                 	   
                        }	 	
                    }
                    break;
                }  	
                case C_Rate1Sign:                    /*���ʴ���*/
                case C_Rate2Sign:
                case C_Rate3Sign:
                case C_Rate4Sign:
                {
                    if ( (C_Rate1Sign == V_ucSign) || (C_Rate2Sign == V_ucSign)     	   	  
                      || (C_Rate3Sign == V_ucSign) || (C_Rate4Sign == V_ucSign) )
                    {  
                        for ( V_ucj = 0; V_ucj < GV_Str_DisplaySign[V_uck].Str_DisplaySignMesNumLen; V_ucj++ )   /*����ʾ״̬�ַ���ʱ������*/
                        {
                            if ( V_ucSourceMesNum == pStr_DisplaySignMesNum[V_ucj].SourceNo )   /*��Ҫ������ʱ��*/
                            {
                                pStr_DisplaySignMesNum[V_ucj].Timer = C_NotDisplayNiu;   
                                break;
                            }	 	     
                        }
                        if ( V_ucj >= GV_Str_DisplaySign[V_uck].Str_DisplaySignMesNumLen )	
                        {
                            return;                            /*����������*/ 	                 	 
                        }	 	
                    }
                    break;
                }
#endif
	             
                case C_GPRSSignalSign1:                    /*�ź�ǿ�ȴ���*/
                case C_GPRSSignalSign2:
                case C_GPRSSignalSign3:
                case C_GPRSSignalSign4:
                {
                    if ( (C_GPRSSignalSign1 == V_ucSign) || (C_GPRSSignalSign2 == V_ucSign)     	   	  
                      || (C_GPRSSignalSign3 == V_ucSign) || (C_GPRSSignalSign4 == V_ucSign) )
                    {
                        for ( V_ucj = 0; V_ucj < GV_Str_DisplaySign[V_uck].Str_DisplaySignMesNumLen; V_ucj++ )   /*����ʾ״̬�ַ���ʱ������*/
                        {
                            if ( V_ucSourceMesNum == pStr_DisplaySignMesNum[V_ucj].SourceNo )   /*��Ҫ������ʱ��*/
                            {
                                pStr_DisplaySignMesNum[V_ucj].Timer = C_NotDisplayNiu;   
                                break;
                            }	 	     
                        }
                        if ( V_ucj >= GV_Str_DisplaySign[V_uck].Str_DisplaySignMesNumLen )		
                        {
                            return;                            /*����������*/	                  	 
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
����ԭ�ͣ�void SF_DisplayDataSignDeal( uchar8 *pV_ucDisBuff )
������������Ҫ��ʾ�������ݴ������������¶ȡ���ϵ��ܡ�������������������ʡ�������������ǰ�������������λΪ
		����λ���¶ȡ����ܡ����ȡ��߶ȡ�γ����ʾ��-���ţ�����������ʾ�����򡱡�������ʾ���渳ֵ�ڸú����ڲ�����, 
		ͬʱ������ȥ������λ 
���������uchar8 *pV_ucDisBuff���账��������ʾ����
�����������
���ز�������
����λ�ã�
��    ע�����ݺ��ֱ���C_ChinaLineDataLenKillZero�е�3λ���жϸ������Ƿ���Ҫ����λ����ͬʱ�������ݳ����ж���
		���ǵ���������(�����ݳ���>=4ʱ���Ҳ��ǵ�ǰ����������ʾ��-��)��
		ʣ�������ʾ��Ҳ�ڸò��ִ���
*******************************************************************************/                                      
void SF_DisplayDataSignDeal( uchar8 *pV_ucDisBuff )              
{
    uchar8 *pV_ucChieseTable, V_ucDisDataSign, V_ucDataLen;
	 	 
    pV_ucChieseTable = (uchar8 * )(GV_Str_DisplayFlag.P_ChieseTableNo + GV_Str_DisplayFlag.ChieseTableLineNo * C_ChineseSignLen);  /*���ֱ��ṹ���ַ*/
    V_ucDisDataSign = (pV_ucChieseTable[C_ChinaLineDataLenKillZero] & C_NeedSignBit0x08);   		/*ȡ�����������Ƿ���Ҫ���Ŵ���*/
	 
    if ( 0x00 != V_ucDisDataSign )  /*��ʾ������Ҫ����λ����*/
    {
        V_ucDataLen = (pV_ucChieseTable[C_ChinaLineDataLenKillZero] & C_GetChinaDataLenBit0x07);  /*ȡ��ʾ���ݳ���*/
        if ( ( V_ucDataLen > C_PreScreenDisDataLen ) || (0 == V_ucDataLen ) )
	 	{
			return;  /*����������*/
	 	}
	 	
	 	if ( ( ( V_ucDataLen >= 4 ) && ( 0x01000000 != ( GV_Str_DisplayFlag.CodeID & 0xFF000000 ) ) )   	/*ֻ�е��������ȡ�γ�ȡ��������ݳ���>=4��������ʾ����������ʾ����*/
	 	  || ( CMeter_Temp == GV_Str_DisplayFlag.CodeID )                                 			/*�����¶ȴ���*/
	 	  || ( CMeter_Position_High == GV_Str_DisplayFlag.CodeID ) )                              	/*�߶�*/     
	 	{
            /*����8�ֽ�BCD����һ��*/
            if ( ( ( GV_Str_DisplayFlag.CodeID & 0xF0000F00) == 0x00000200 ) 
			  || ( ( GV_Str_DisplayFlag.CodeID & 0xF0000F00) == 0x00000400 ) 
			  || ( ( GV_Str_DisplayFlag.Related_CodeID & 0xF0000F00) == 0x00000200 ) 
			  || ( ( GV_Str_DisplayFlag.Related_CodeID & 0xF0000F00) == 0x00000400 ) )
            {
                V_ucDataLen = C_EnergyNature4BCDLen;
            }
		  
			if ( pV_ucDisBuff[V_ucDataLen - 1] & 0x80 )  						      /*ȡ���λ*/
			{
				GV_ucDisplayData[22] |= C_DisNegativeSign;   					  /*"-"��ʾ*/
				pV_ucDisBuff[V_ucDataLen-1] = pV_ucDisBuff[V_ucDataLen - 1] & 0x7F;     /*ȥ������λ*/
	 		}
	 	}
		else   /*���������ݣ����������������ʣ��������������ڹ���*/
		{
            if ( ( pV_ucDisBuff[V_ucDataLen-1] & 0x80 )   							/*ȡ���λ���������ݲ�����FF������ΪFF�������з���λ����*/
			  && ( 0xFF != pV_ucDisBuff[V_ucDataLen - 1]) )   						/*ֻ������������,�������ղ����ݿ���ΪFF*/
            {
                GV_ucDisplayData[17] |= C_DisFanXiang;   						/*"����"��ʾ*/
                pV_ucDisBuff[V_ucDataLen - 1] = pV_ucDisBuff[V_ucDataLen - 1] & 0x7F; /*ȥ������λ*/
            }	 	  	 
        }	 	  
    }	
	 
    if ( COverDraft_Hex_Cent == GV_Str_DisplayFlag.CodeID ) 	 	/*��ǰ͸֧�����ʾ"-"*/
    {
        GV_ucDisplayData[22] |= C_DisNegativeSign;   		/*"-"��ʾ*/
    }
}
/*******************************************************************************
����ԭ�ͣ�void SF_DisplyMainData( uchar8 V_ucMoneySign )
��������������Ļ������ʾ����,��������ʾ���ݡ���λ��С������ʾ����
���������uchar8 V_ucMoneySignʣ���͸֧������ǰ2s��ʾ�Ƿ������⴦��
�����������
���ز�������
����λ�ã�
��    ע��
*******************************************************************************/
void SF_DisplyMainData( uchar8 V_ucMoneySign )
{
    uchar8  *pV_ucChieseTable;
    ulong32 V_ulDI32;
    uchar8  V_ucDisBuff[C_EnergyNature4BCDLen] = {0}, V_ucDot;
	 
    if ( C_ALLScreenDisplayDi == GV_Str_DisplayFlag.CodeID )         /*��ʶ��ΪȫFF*/
    {
        return;   	 
    }
	 
    SF_GetDisplayData(&V_ucDisBuff[0]);                             /*��ȡ��Ҫ��ʾ�����ݣ�ÿ����ʾ�账���������5���ֽ�*/

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
    else        /*ȡ����ǰʣ�ࡢ͸֧���*/
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
	 
    SF_DisplayDataSignDeal(&V_ucDisBuff[0]);              			/*�������λ������λ�����ڲ�������-����ʾ*/
	 
    pV_ucChieseTable = (uchar8 *)(GV_Str_DisplayFlag.P_ChieseTableNo + GV_Str_DisplayFlag.ChieseTableLineNo * C_ChineseSignLen);   /*���ֱ��ṹ���ַ*/
    V_ucDot = pV_ucChieseTable[C_ChinaeseLineDot];          			/*ȡ��ʾС����λ��*/

	if ( GV_Str_DisplayFlag.Related_CodeID != 0xFFFFFFFF ) 			/*�������б�*/
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
	  || ( CY_Com_Ac_Tol_En_0 == V_ulDI32 ) )     /*������ʾС��λ��������ʾ���ݣ�����������ʾ����С����λ��;*/
	{
		if ( ( 0x00000200 == (V_ulDI32 & 0xF000FF00 ) )
          || ( 0x00000400 == (V_ulDI32 & 0xF000FF00 ) ) )
		{
		  	V_ucDot = SF_EnDePointAdjust(&V_ucDisBuff[0]);      /*����С������*/
		}
		else if ( ( CM_Com_Ac_Tol_En_0 == V_ulDI32 ) 
          || ( CY_Com_Ac_Tol_En_0 == V_ulDI32 ) )
		{
		  	V_ucDot = SF_EnDePointAdjust(&V_ucDisBuff[0]);      /*����С������*/
		}
        else if ( CCom_Ac_LastPulse_FF_0 == (V_ulDI32 & 0xF000FF00) )
        {
			GV_KillZeroNum = C_KillZero3;
        }
	}
	else if ( ( 0x10000000 == (V_ulDI32&0xF0000000) ) && (0x01 == GV_Str_DisplayFlag.ParaNum) ) /*�������ݣ��������3��ʱ�����������ݲŽ���С���㴦��*/
	{
		V_ucDot=SF_EnDePointAdjust(&V_ucDisBuff[0]);  /*����С������*/
	    GV_KillZeroNum += C_KillZero2;
	}
    else
    {	                                                     	    
        SF_KillZeroDeal(&V_ucDisBuff[0],V_ucDot);       /*���㴦��*/ 
        GV_KillZeroNum += C_KillZero2;
    }
	 
    SF_DotDisplayDeal(V_ucDot);                      				/*С������ʾ�������ݴ���*/

    SF_DisplayUnit(pV_ucChieseTable[C_ChinaeseLineUnit]);         /*��λ��ʾ������*/ 
    
    /*����ʾ���ݷŻ�����*/
    memcpy(GV_ucDisplayData, V_ucDisBuff, 4);		/*����ʾ���ݷŻ�����*/
    GV_ucDisplayData[C_MainDataHig_offset] = V_ucDisBuff[C_MainDataEn_offset4];
    
    /*GV_DispAllScreenMode = 0;*/
}
/**********************************************************************************************************
����ԭ�ͣ�void SF_DisplayRealatedOAD_RateJudge( ulong32 V_ulOAD, uchar8 *pV_ucData, ushort16 *pV_usDataLen )
������������ʾ���ã��жϵ��ܡ����������ʵ���Ƿ񳬷�����������������ʾΪ0                         
��������� V_ulOAD�����ܡ�����������OAD��                                                         
                   ���ᡢ�¼����������OAD���ݱ�ʶ                                                
          pV_ucData�����ݻ����ַ���������ʱע���С                                                 
          pV_usDataLen:���ݳ���                                                                 
���������pV_ucData�����ݻ����ַ���������ʱע���С                                                 
���ز�������                                                                                                                                                                          
����λ�ã�                                                                                        
��    ע��                                                                                        
************************************************************************************************************/                                         
void SF_DisplayRealatedOAD_RateJudge( ulong32 V_ulOAD, uchar8 *pV_ucData, ushort16 *pV_usDataLen )
{
    uchar8 V_ucOAD[C_DataCodeLen];
    uchar8 V_ucRateNum;
    
    PF_Ulong32ToBuffer4(V_ucOAD, &V_ulOAD, C_DataCodeLen);
	/*��ȡ������*/
    V_ucRateNum = InF_RateNumChangeToHex();
    
    switch ( V_ucOAD[C_O_DI3] )
    {
        case 0x00:  /*������*/
        case 0x10:  /*������*/
        {
            /*�жϷ������Ƿ񳬣�����������ʾΪ0*/
            if ( V_ucOAD[C_O_DI0]  > (V_ucRateNum + 1) )     /*��+����������1*/
            {
                memset(pV_ucData, 0x00, *pV_usDataLen);
            }
            
        }break;
        default:    /*ԭ���ݲ�����*/
        {
            break;
        }
    }
}
/*******************************************************************************
����ԭ�ͣ�void SF_DisplayData_LastPulseDeal( uchar8 *pV_ucDisplayData )
��������������β�����ݶ�ȡΪ1�ֽ�Hex��������Ϊ0.0000XX 
���������pV_ucDisplayData�����ݻ��� 
���������pV_ucDisplayData�����ݻ���
���ز�����
����λ�ã�
��    ע����������Ϊ1�ֽ�Hex���������ΪBCD��5�ֽڣ����λΪ����λ
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
����ԭ�ͣ�void SF_GetDisplayData( uchar8 *pV_ucDisplayData )                                                                        
��������: ��ʾ�����ݴ������ؽ�ȡ�������ʾ���ݣ����5�ֽ�.��ȷ����                                                              
���������uchar8 * pV_ucDisplayData:����ʾ���ݻ���                                                                                                                  
�����������                                                                                                                  
���ز����� ��                                                                                                                  
����λ�ã�                                                                                         
��    ע��У�������ȹ̶�ֵ0x0080          
          �����������֣�1�ֽ�,��ʾ��������,���������֣�ת��Ϊ������ʾֵ19200��2400��,3�ֽ����ݳ���
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
	  && ( ( 0x02 == V_ucDi[C_O_DI1] ) || ( 0x04 == V_ucDi[C_O_DI1] ) ) )   				/*��ǰ������*/
	{		
        if ( ( V_ulDi32 == 0x00110200 ) || ( V_ulDi32 == 0x00210200 ) 
          || ( V_ulDi32 == 0x00120200 ) || ( V_ulDi32 == 0x00220200 )
          || ( V_ulDi32 == 0x00130200 ) || ( V_ulDi32 == 0x00230200 ) )
        {
            V_ulDi32 = (V_ulDi32 & 0xFFFF00FF) | 0x00000401;	/*ʹ������4��ȡ*/
            /*V_ucReturn_Flag = InF_ReadEnergy_Protocol(V_ulDi32, &V_ucDisBuff[0], &V_ucDataLen, C_Format_BCD);*/   /*�������������*/
			V_ucReturn_Flag = InF_GetData_ObjectManage(V_ulDi32, &V_ucDisBuff[0], &V_usLen, &V_usDataEncode);
        }
        else
        {
            V_ulDi32 = (V_ulDi32 & 0xFFFF00FF) | 0x00000400;	/*ʹ������4��ȡ*/
            /*V_ucReturn_Flag = InF_ReadEnergy_Protocol(V_ulDi32, &V_ucDisBuff[0], &V_ucDataLen, C_Format_BCD);*/   /*�������������*/
			V_ucReturn_Flag = InF_GetData_ObjectManage(V_ulDi32, &V_ucDisBuff[0], &V_usLen, &V_usDataEncode);
			
			/*�жϷ������Ƿ񳬣�����������ʾΪ0*/
            if(V_ucReturn_Flag == C_OK)
            {
                SF_DisplayRealatedOAD_RateJudge(GV_Str_DisplayFlag.CodeID, &V_ucDisBuff[0], &V_usLen);
            }
        }
	}
    else if ( ( 0x00 == ( V_ucDi[C_O_DI3] & 0xf0 ) ) && ( 0x06 == V_ucDi[C_O_DI1] ) )   /*��ǰ�����࣬����β��*/
	{
		/*V_ucReturn_Flag = InF_ReadEnergy_Protocol(GV_Str_DisplayFlag.CodeID, &V_ucDisBuff[0], &V_ucDataLen, C_Format_HEX);*/   		/*�������������*/
		V_ucReturn_Flag = InF_GetData_ObjectManage(GV_Str_DisplayFlag.CodeID, &V_ucDisBuff[0], &V_usLen, &V_usDataEncode);
        
        /* �жϷ������Ƿ񳬣�����������ʾΪ0 */
        if(V_ucReturn_Flag == C_OK)
        {
            /*SF_DisplayData_LastPulseDeal(&V_ucDisBuff[0]);
            V_usLen = C_DisEnergyCommPulseLastLen;*/
            SF_DisplayRealatedOAD_RateJudge(GV_Str_DisplayFlag.CodeID, &V_ucDisBuff[0], &V_usLen);
        }
	}
	else if ( 0x10 == ( V_ucDi[C_O_DI3] & 0xf0 ) )     								/*��ǰ�������Ƕ�ȡ�����ӿں���*/
	{
		/*V_ucReturn_Flag = InF_ReadDemand(GV_Str_DisplayFlag.CodeID, &V_ucDisBuff[0], V_ucDataLen);*/   /*����ͳһ9���ֽ�*/
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
            /*�жϷ������Ƿ񳬣�����������ʾΪ0*/
            SF_DisplayRealatedOAD_RateJudge(GV_Str_DisplayFlag.CodeID, &V_ucDisBuff[0], &V_usLen);
        }

    }
	else if ( ( 0x20 == (V_ucDi[C_O_DI3] & 0xf0)) || ( 0x40 == (V_ucDi[C_O_DI3] & 0xf0 ) ) )		/*�������α���*/
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
				/*V_ucReturn_Flag = InF_ReadEnergy_Protocol(GV_Str_DisplayFlag.CodeID, &V_ucDisBuff[0],&V_ucDataLen, C_Format_BCD);*/   /*�������������*/
				V_ucReturn_Flag = InF_GetData_ObjectManage(GV_Str_DisplayFlag.CodeID, &V_ucDisBuff[0], &V_usLen, &V_usDataEncode);
			}
			else
			{
			  	V_ucReturn_Flag = InF_Read_Data(GV_Str_DisplayFlag.CodeID, &V_ucDisBuff[0], &V_usLen, &V_usDataEncode);  
			}
		}
		else if ( GV_Str_DisplayFlag.CodeID == CPluse_Wide )                     /*У�������ȣ�ȡ�̶�ֵ*/
#endif
        if ( GV_Str_DisplayFlag.CodeID == CPluse_Wide )                     /*У�������ȣ�ȡ�̶�ֵ*/
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
					/*BCDת��*/
	       		 	V_ucDataLen = 1;
				 	V_ulTemp = V_ucDisBuff[GV_Str_DisplayFlag.SV_DisplayDataOff];
	       		 	PF_HextoBCDBytes(&V_ulTemp, &V_ucDisBuff[GV_Str_DisplayFlag.SV_DisplayDataOff], &V_ucDataLen);
				}	
			}	
			if ( GV_Str_DisplayFlag.CodeID == CMeter_Position_High )  /*���ܱ�λ����Ϣ:�߶�*/   
			{
				if ( V_ucReturn_Flag == C_OK )
                {
                    /*���ݷ�ת*/
                    V_ulTemp = PF_Buffer4ToUlong32_698(&V_ucDisBuff[0]);
                    /*BCDת��*/
                    V_ucDataLen = 4;
                    PF_HextoBCDBytes(&V_ulTemp, V_ucDisBuff, &V_ucDataLen);
				}
			}
#endif
            if( (GV_Str_DisplayFlag.CodeID & 0xFFFFFF00) == 0x40110200 )/*���������ܲ���ʾ��ʱ�α��ڵ�λ*/
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
                V_usLen -= 1;/*�ܲ���ʾ�����ȼ�1*/
            }
            
            /*�����ա�ʱ�������ݸ��ֽ���ǰ�����⴦��-���ݰ��ֽڵߵ�*/
            if( ( (GV_Str_DisplayFlag.CodeID & 0xFFFFFF00) == 0x41160200 )
              ||( (GV_Str_DisplayFlag.CodeID & 0xFFFFFF00) == 0x40140200 )
              ||( (GV_Str_DisplayFlag.CodeID & 0xFFFFFF00) == 0x40150200 ) )
            {
                PF_OneDataReversed(V_ucDisBuff, V_ucDisBuff, (uchar8)V_usLen);
            }
            
            /*ʱ�α����ݽ��������ݸ��ֽ���ǰ�����⴦��-ÿ3�ֽڵߵ�*/
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
	else if ( 0x30 == (V_ucDi[C_O_DI3] & 0xf0 ) )										/*�¼���¼*/
	{
		if ( ( GV_Str_DisplayFlag.Related_CodeID) != 0xFFFFFFFF )					/*�й�������*/
   		{
			V_ucDi[4] = GV_Str_DisplayFlag.ParaNum;
   			  	 	  	 	  	       			
   			PF_Buffer4ToUlong32(V_ucDi, V_ulRelateOI, 4);
        	V_ulRelateOI[1] = GV_Str_DisplayFlag.Related_CodeID;
			V_ulRelateOI[2] = 0xFFFFFFFF;	
            
			V_ucReturn_Flag = Inf_ReadEventRenew(&V_ulRelateOI[0], &V_ucDisBuff[0], &V_ucDataLen);    /*���¼���¼�ӿں���*/
            V_usLen = V_ucDataLen;
            
			if ( V_ucReturn_Flag != C_OK )
			{
                /*V_usDate = C_RAM_Max;
  	            V_ucReturn_Flag = InF_ReadEventData(V_ulRelateOI, &V_ucDate, &V_ucDisBuff[0], &V_ucDate, &V_usDate, 0x68); */
				Str_ReadRecord.pV_ulROAD = &V_ulRelateOI[0];
                V_ucTemp[0] = 9;/*����9*/
                V_ucTemp[1] = V_ucDi[C_O_DI0];/*��ȡ�ϼ���*/
				Str_ReadRecord.pV_ucRST = &V_ucTemp[0];
				Str_ReadRecord.V_usROAD_Num = 1;/*��������1��*/
				Str_ReadRecord.V_ucReadMode = 3;/*��ʾģ���ȡ*/
				Str_ReadRecord.V_ucChannelNo = 0xFF;/*��ͨ�Ŷ�ȡ*/
				Str_SuppInfo.pV_usEncode = &V_usDataEncode;
				V_ucReturn_Flag = InF_GetData_Record(&Str_ReadRecord, &V_ucDisBuff[0], &V_usLen, &Str_SuppInfo);
			}
            if ( V_ucReturn_Flag == C_OK )
            {
                /*�жϷ������Ƿ񳬣�����������ʾΪ0*/
                SF_DisplayRealatedOAD_RateJudge(GV_Str_DisplayFlag.Related_CodeID, &V_ucDisBuff[0], &V_usDataLenMax);
#if(0)
				if ( ( V_ucDisBuff[GV_Str_DisplayFlag.SV_DisplayDataOff] == C_NotSupportAOD_Data)   /*û������Ĭ���㡢���������¼�����00000000AAAAAAAA*/
				  || ( ( V_ucDisBuff[0] == C_NotSupportAOD_DataBB ) && ( V_usDate == CL_NotSupportAOD_DataBB ) ) )
#endif
				if(Str_SuppInfo.V_ucFrameNum == 0)
				{
					memset(V_ucDisBuff, 0x00, V_usLen);
				}
				
                if ( (GV_Str_DisplayFlag.Related_CodeID & 0xFF000000) == 0x00000000 )			/*�������б�*/
                {
                    if ( (GV_Str_DisplayFlag.Related_CodeID & 0x00000F00) == 0x00000200 )		/*�¼�����Ϊ2λС�����ܣ�������ʾλ��Ϊ4λС�����ܣ�����λ��0*/
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
                    else if( (GV_Str_DisplayFlag.Related_CodeID & 0x00000F00) == CCom_Ac_LastPulse_FF_0 )		/*����β��*/
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

				else if ( (GV_Str_DisplayFlag.Related_CodeID & 0XFFFFff00) == 0x20220200 )			/*�¼���¼�����ΪBCD������Ӧ�ü�1*/
				{
					PF_Buffer4ToUlong32(V_ucDisBuff,&V_ulTemp,4);
					if ( V_ulTemp!=0 )
					{
						V_ucTemp[0] = 1;
						memset(&V_ucTemp[1],0x00,3);
						PF_BCDDECBytes(V_ucDisBuff, V_ucTemp, V_ucDisBuff, 4);
					}
				}
				else if ( ( GV_Str_DisplayFlag.Related_CodeID == 0x201E0200 )					/*�¼�����������ʱ��ֱ��7�ֽ�תBCD*/
                  || ( GV_Str_DisplayFlag.Related_CodeID == 0x20200200 ) )
				{
					V_ucDisBuff[6] = 0x20;
				}
#endif
            }
   		}
   		else/*û�й�������*/
   		{
            
   			PF_Buffer4ToUlong32(V_ucDi, V_ulRelateOI, 4);
            V_ulRelateOI[1] = 0xFFFFFFFF;

			if ( ( (V_ucDi[2] <= 0x08) || (V_ucDi[2] == 0x0B) )
			  && ( (V_ucDi[1] == 10) || (V_ucDi[1] == 14) ) )/*��24,����10����ǰֵ��¼��*/
			{
				if ( V_ulRelateOI[0]==0x30000a01 )/*���ۼƴ������ۼ�ʱ�䣬��Ҫת����ʶ�����⴦��*/
				{
					V_ulRelateOI[0] = 0x30000D01;/*ʧѹ�ܴ���*/
					V_ucReturn_Flag = Inf_ReadEventRenew(&V_ulRelateOI[0], &V_ucDisBuff[0], &V_ucDataLen);
					V_ulRelateOI[0] = 0x30000D02;/*ʧѹ�ۼ�ʱ��*/
					V_ucReturn_Flag = Inf_ReadEventRenew(&V_ulRelateOI[0], &V_ucDisBuff[4], &V_ucDataLen);
                    V_usLen = V_ucDataLen;
				}
				else if ( V_ulRelateOI[0]==0x30000E01 )
				{
					V_ulRelateOI[0] = 0x30000D03;/*����ʱ��*/
					V_ucReturn_Flag = Inf_ReadEventRenew(&V_ulRelateOI[0], &V_ucDisBuff[0], &V_ucDataLen);
					V_ulRelateOI[0] = 0x30000D04;/*����ʱ��*/
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
					if ( V_ucDisBuff[GV_Str_DisplayFlag.SV_DisplayDataOff] == 0xAA )   /*û������Ĭ���㡢���������¼�00000000AAAAAAAA*/
					{
                        memset(V_ucDisBuff, 0x00, V_usLen);
					}
				}
			}
			else if ( ( (V_ucDi[2] >= 0x0c) || (V_ucDi[2] == 0x09) || (V_ucDi[2] == 0x0A) )
			  && (V_ucDi[1] == 7) )/*��7,����7����ǰֵ��¼��(9���ֽ�)*/
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
                V_ucReturn_Flag = Inf_ReadEventRenew(&V_ulRelateOI[0], &V_ucDisBuff[0], &V_ucDataLen);    /*���¼���¼�ӿں���*/
                V_usLen = V_ucDataLen;
			
                if ( V_ucReturn_Flag != C_OK )
                {
                    V_ucReturn_Flag = InF_GetData_ObjectManage(GV_Str_DisplayFlag.CodeID, &V_ucDisBuff[0], &V_usLen, &V_usDataEncode);	
                }
                if ( V_ucDisBuff[0] == 0xAA )   /*û������Ĭ����*/
                {
                    memset(V_ucDisBuff, 0x00, V_usLen);
                }
            } 
        } 
/**************������************************/
#if(0)
		/*�ۼ�ʱ��ΪHEX��ʽ����Ҫת����BCD��ʽ*/
		if ( (V_ucDi[2]<=0x08) || (V_ucDi[2]==0x0B) )/*��24*/
		{
			if ( (V_ucDi[1] == 0x0A) )
			{
				PF_Buffer4ToUlong32(&V_ucDisBuff[4], &V_ulDi32,4);
				V_ucDataLen = 4;
				PF_HextoBCDBytes( &V_ulDi32, &V_ucDisBuff[4], &V_ucDataLen); /*�¼��ۼ�ʱ�����ݲ�hex��ʽ��ת����BCD��ʽ*/
			}
            else if ( (V_ucDi[1] == 0x0D) && (V_ucDi[0] == 2) )
            {
                
                PF_Buffer4ToUlong32(&V_ucDisBuff[0], &V_ulDi32, 4);
				V_ucDataLen = 4;
				PF_HextoBCDBytes( &V_ulDi32, &V_ucDisBuff[0], &V_ucDataLen); /*�¼��ۼ�ʱ�����ݲ�hex��ʽ��ת����hex��ʽ*/

            }
		}
		else
		{
			if ( V_ucDi[1] == 0x07 )/*��7*/
			{
                
				PF_Buffer4ToUlong32(&V_ucDisBuff[5], &V_ulDi32,4);
				V_ucDataLen = 4;
				PF_HextoBCDBytes(&V_ulDi32, &V_ucDisBuff[5], &V_ucDataLen);
                 /*�¼��ۼ�ʱ�����ݲ�hex��ʽ��ת����hex��ʽ*/
			}
		}
#endif
/**************************************/
    }	 
	else if ( 0x50 == (V_ucDi[C_O_DI3] & 0xf0 ) )										/*����*/	
	{
		V_ucDi[4] = GV_Str_DisplayFlag.ParaNum;
  	       			  	 	  	 	  	       			
  	    PF_Buffer4ToUlong32(V_ucDi, V_ulRelateOI, 4);
        V_ulRelateOI[1] = GV_Str_DisplayFlag.Related_CodeID;
		V_ulRelateOI[2] = 0xFFFFFFFF;		
		
		Str_ReadRecord.pV_ulROAD = &V_ulRelateOI[0];
        V_ucTemp[0] = 9;/*����9*/
        V_ucTemp[1] = V_ucDi[C_O_DI0];/*��ȡ�ϼ���*/
        Str_ReadRecord.pV_ucRST = &V_ucTemp[0];
		Str_ReadRecord.V_usROAD_Num = 1;/*��������1��*/
		Str_ReadRecord.V_ucReadMode = 3;/*��ʾģ���ȡ*/
		Str_ReadRecord.V_ucChannelNo = 0xFF;/*��ͨ�Ŷ�ȡ*/
		Str_SuppInfo.pV_usEncode = &V_usDataEncode;
		V_ucReturn_Flag = InF_GetData_Record(&Str_ReadRecord, &V_ucDisBuff[0], &V_usLen, &Str_SuppInfo);
  	    /*V_ucReturn_Flag = InF_ReadFreezeData(V_ulRelateOI,&V_ucDate, &V_ucDisBuff[0], &V_usDate, &Len, V_ucDate, &V_ucFreezeTime,C_698Mode);*/ 
		if ( V_ucReturn_Flag == C_OK )
		{
            /*�жϷ������Ƿ񳬣�����������ʾΪ0*/
            SF_DisplayRealatedOAD_RateJudge(GV_Str_DisplayFlag.Related_CodeID, &V_ucDisBuff[0], &V_usDataLenMax);
            
			if( ( GV_Str_DisplayFlag.Related_CodeID & 0xFF000000) != 0x00000000 )
			{
				if ( V_ucDisBuff[0] == 0xAA )
				{
					memset(V_ucDisBuff, 0x00, V_usLen);			/*�������8���ֽ�*/
				}
			}

            if ( ( GV_Str_DisplayFlag.Related_CodeID & 0xFF000000) == 0x00000000 )		/*�������б�*/
            {
				
                if ( ( GV_Str_DisplayFlag.Related_CodeID & 0x00000F00) == 0x00000200 )	/*��������Ϊ2λС�����ܣ�������ʾλ��Ϊ4λС�����ܣ�����λ��0*/
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
                else if ( (GV_Str_DisplayFlag.Related_CodeID & 0x00000F00) == CCom_Ac_LastPulse_FF_0 )		/*����β��*/
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
            else if ( (GV_Str_DisplayFlag.Related_CodeID&0XFFFFff00) == 0x20230200 )/*�������hex��,Ҫ��1*/
            {
                PF_Buffer4ToUlong32(V_ucDisBuff, &V_ulTemp, 4);
                if ( V_ulTemp != 0 )
                {
                    V_ulTemp -= 1;
                    V_ucDataLen = 4;
                    PF_HextoBCDBytes(&V_ulTemp, V_ucDisBuff, &V_ucDataLen);
                }
            }
            else if ( GV_Str_DisplayFlag.Related_CodeID == 0x20210200 )/*������ʾʱ��*/
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

		if ( 0xF2000200 == (GV_Str_DisplayFlag.CodeID&0xFF00FF00) )  /*�����������֣�1�ֽڣ�*/         	   
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
                    V_ucDisBuff[1] = 0x96;	/*Ĭ��9600*/
                }
            } 
		}
		V_ucDisBuff[0] = 0x00;                      	  
	}

	if ( (C_OK != V_ucReturn_Flag) && (C_CrcErr_DataZero != V_ucReturn_Flag) )  /*����������*/
	{
        memset(&V_ucDisBuff[GV_Str_DisplayFlag.SV_DisplayDataOff], 0, 8);
		return;
	}
   
	 /************�������ݽ�ȡ����***************/
    if ( GV_Str_DisplayFlag.SV_DisplayDataOff >= C_RAM_Max )   /*�������������������*/
    {
        return;	 	 
    }
	
    pV_ucChieseTable = (uchar8 * )(GV_Str_DisplayFlag.P_ChieseTableNo + GV_Str_DisplayFlag.ChieseTableLineNo * C_ChineseSignLen);  /*���ֱ��ṹ���ַ*/
    V_ucDataLen = pV_ucChieseTable[C_ChinaLineDataLenKillZero] & C_GetChinaDataLenBit0x07;   /*ȡ��4λ��ʾ���ݳ���*/
    V_ucChangeSign = pV_ucChieseTable[C_ChinaLineDataLenKillZero] & C_NeedSignBit0x08;   /*�����Ƿ������*/
    V_ucChangeType = pV_ucChieseTable[C_ChinaeseLineUnit] & 0xF0;/*����ת������*/
    
	 
    if ( V_ucDataLen > C_PreScreenDisDataLen )                  /*�������������������*/
    {
        return;	 	  
    }
    if ( (GV_Str_DisplayFlag.SV_DisplayDataOff + V_ucDataLen) >= C_RAM_Max )  /*Ҫ���������������������*/
    {
        return;
    }
	 
	 /*����8�ֽ�BCD����һ��*/
    if ( ( ( GV_Str_DisplayFlag.CodeID & 0xF0000F00) == 0x00000200 ) 
      || ( ( GV_Str_DisplayFlag.CodeID & 0xF0000F00) == 0x00000400 ) 
      || ( ( GV_Str_DisplayFlag.Related_CodeID & 0xF0000F00) == 0x00000200 ) 
      || ( ( GV_Str_DisplayFlag.Related_CodeID & 0xF0000F00) == 0x00000400 ) )
    {
        V_ucDataLen = C_EnergyNature4BCDLen;
    }
    
    PF_Ushort16ToBuffer2(V_ucTemp, &V_usLen);
    V_ucDataHexLen = (V_ucTemp[0] - GV_Str_DisplayFlag.SV_DisplayDataOff);
	 
    /*PF_CopyDataBytes(&V_ucDisBuff[GV_Str_DisplayFlag.SV_DisplayDataOff], pV_ucDisplayData, V_ucDataLen);*/    /*���ݿ���*/
    SF_DispDataChange(&V_ucDisBuff[GV_Str_DisplayFlag.SV_DisplayDataOff], pV_ucDisplayData, V_ucDataHexLen, V_ucDataLen, V_ucChangeSign, V_ucChangeType);
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_EnBorrowPoint( ulong32 V_ulOAD, uchar8 *pV_ucDisplayData )
�������������ܽ�λ��ʾ�жϼ�����
���������V_ulOAD:��ʶ�룻pV_ucDisplayData��λ����������
�����������
���ز�������λ�����ʾ��С��λ��
����λ�ã�
��    ע��1������������5�ֽ�HEX���޷���, �鿴�Ƿ���ʾ��Χ������ʾ��Χ�󣬽�λ��ʾ
             6+4=7+3=8+2=9+1=10+0��
          2)����999999.9999����1λ
            ����9999999.9999����2λ
            ����99999999.9999����3λ
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
	} /*else ������ѭ�Կ�ʼ����*/
    
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
����ԭ�ͣ�uchar8 SF_EnDePointAdjust( uchar8 *pV_ucDisplayData )
��������������������С��λ�������������ݲ�洢��ʾС��λ����������ʾ���ݣ�ͬʱ������Ҫ��ʾ��С��λ��
���������uchar8 *pV_ucDisplayData:����С����λ��������������ݻ�
�����������
���ز�����uchar8:������ʾ��С��λ����0����ʾ��С���㣬1����ʾ1��С���㣬������
����λ�ã�
��    ע���������������1�����������ݺ����ڲ����и�λ���㴦���е����຺�ֱ��ʱ�������λ�������㴦��.
          ͬʱ�ú����жԵ�ǰ͸֧����ǰʣ���������.��ȫ�ֱ���������������д����õ��������������
          ��������ʾ4λС��ʱ���������������ж� 
         �ж��ڽ�λС����ʾ�������£���ǰ��ʾС��λ��LCD����С��λ���Ĺ�ϵ�����Ȱ���LCD����С��λ����ʾ
        ��LCD����С��λ����Ƚ�λ���С��λС�������������ǰ��ս�λ��С��λ��ʾ��
*******************************************************************************/
uchar8 SF_EnDePointAdjust( uchar8 *pV_ucDisplayData )
{
	ulong64 V_ul64Data, V_ul64Compare;
	ulong32 V_ulDemand32 = 0, V_ulDI32;
	ushort16 V_usLen, V_usDataEncode;
    uchar8  V_uci, V_ucj, V_ucDot/*, V_ucBuffer*/;
	/*uchar8  V_DeBuff[3] = {0};*/
    uchar8  V_ucBorrowPoint;
	
    if ( GV_Str_DisplayFlag.Related_CodeID != 0xFFFFFFFF )    /*�������б�*/
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
      || ( CY_Com_Ac_Tol_En_0 == V_ulDI32 ) )   /*��������*/     
    {
        if ( ( CChargeBal_Hex_Cent == V_ulDI32 ) || ( COverDraft_Hex_Cent == V_ulDI32 ) )   /*��ǰ͸֧����ǰʣ�����������ִ��*/
        {
            V_ucDot = C_DotNum_2;      /*2λС��*/
            return V_ucDot;	 	  	 
        }
  	  
        V_usLen = CLEnergy_Decimal_Num;
	 	V_uci = InF_Read_Data(CEnergy_Decimal_Num, &V_ucDot, &V_usLen, &V_usDataEncode);		/*��ʾ����С��λ��*/
		
		if ( 0x00000000 == (V_ulDI32 & 0xFF000000 ) )
		{
			V_ucBorrowPoint = SF_EnBorrowPoint(V_ulDI32, pV_ucDisplayData);         /*��ȡ��λ�����ʾС��λ��*/
					
			if ( V_ucDot > V_ucBorrowPoint )     /*��λ��ʵ������ʾ��С��λ��<��������ʾ����С��λ��������λ����ʾ*/
			{
				V_ucDot = V_ucBorrowPoint;
			}
		}
		else
		{
			;   /*�¶��õ������������õ�С��λ��*/
		}
		
		PF_Buffer8ToUlong64(pV_ucDisplayData, &V_ul64Data, C_EnergyNature4BCDLen);
        
        switch( V_ucDot ) 
        {
	 	  	 case C_DotNum_4:           /*3λС��*/
	 	  	 {
	 	  	 	 V_ul64Data >>= 0; 
				 
	 	  	 }break;
	 	  	 case C_DotNum_3:           /*3λС��*/
	 	  	 {
	 	  	 	 V_ul64Data >>= 4; 
				 
	 	  	 }break;
	 	  	 case C_DotNum_1:           /*1λС��*/
	 	  	 {
	 	  	 	 V_ul64Data >>= 12; 
	 	  	 }break;	
	 	  	 case C_DotNum_0:           /*0λС��*/
	 	  	 {
	 	  	 	 V_ul64Data >>= 16; 
	 	  	 }break;	 	  	 	 
	 	  	 default:             /*Ĭ����ʾ2λС��*/
	 	  	 {
	 	  	 	 V_ucDot = C_DotNum_2;         /*Ĭ����λС��*/
				 V_ul64Data >>= 8; 
             }break;
		}
		
		V_ucj = 10 - 1 - V_ucDot;    		/* ��0ʱ��Ҫ�жϼ�����λ */

		GV_KillZeroNum = 0;
		V_ul64Compare = 0xf000000000;   /* 5���ֽڣ������λ��ʼ�ж� */
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
    else      /*��������*/
    {
        V_usLen = CLPower_Decimal_Num;
        V_uci = InF_Read_Data(CPower_Decimal_Num, &V_ucDot, &V_usLen, &V_usDataEncode);/*��ʾ����С��λ��*/
        if ( C_PreScreenDisDataLen < 4 )  /*��ʾ���ݴ�Ż��泤��*/
        {
            return 4;      /*����������*/
        } 

        PF_Buffer4ToUlong32(pV_ucDisplayData, &V_ulDemand32, 4);
#if(0)
        switch( V_ucDot ) 
        {
            case 0x06:           /*6λС��*/
            {
                if ( 0x00 == ( pV_ucDisplayData[3] & 0xF0 ) )  /*��4λ����1����*/ 
                {
                    GV_KillZeroNum = C_KillZero1;
                }	 
                else
                {
                    GV_KillZeroNum = 0;	 	  	 	  	 	 	  	 	  	 
                }
                break;	 	  	 	  
            }
            case 0x05:           /*5λС��*/
            {
                for ( V_uci = 0; V_uci < 3; V_uci++)
                {
                    pV_ucDisplayData[V_uci] >>= 4;
                    V_ucBuffer = (pV_ucDisplayData[V_uci+1] << 4);    
                    pV_ucDisplayData[V_uci] = (pV_ucDisplayData[V_uci]|V_ucBuffer);
                }
                pV_ucDisplayData[3] >>= 4;  /*��4���ֽ�*/

                GV_KillZeroNum = C_KillZero1;             /*��1����*/
                if ( 0x00 == pV_ucDisplayData[3] )             /*��2����*/
                {
                    GV_KillZeroNum = C_KillZero2;
                }
                break;	 	  	 	  
            }
            case 0x03:           /*3λС��*/
            {
                V_ulDemand32 >>= 4;   /*ȥ����1λС��*/

                GV_KillZeroNum = C_KillZero1;             /*��1����*/

                PF_Ulong32ToBuffer4(pV_ucDisplayData, &V_ulDemand32, 4);	 	  	 	                      

                if ( 0x00 == pV_ucDisplayData[2] )             /*��2����*/
                {
                    GV_KillZeroNum = C_KillZero2;
                }
                break;	 	  	 	  
            }	 	  	 
            case 0x02:           /*2λС��*/
            {                
                V_ulDemand32 >>= 8;   /*ȥ����2λС��*/
                
                GV_KillZeroNum = C_KillZero2;/*��2����*/

                PF_Ulong32ToBuffer4(pV_ucDisplayData, &V_ulDemand32, 4);	 	  	 	

                if ( 0x00 == (pV_ucDisplayData[1]&0xF0) ) /*��4λ����2����*/ 
                {
                    GV_KillZeroNum = C_KillZero3;
                }
                break;	 	  	 	  
            }
            case 0x01:           /*1λС��*/
            {
                V_ulDemand32 >>= 12;   /*ȥ����3λС��*/

                GV_KillZeroNum = C_KillZero3;             /*��3����*/

                PF_Ulong32ToBuffer4(pV_ucDisplayData, &V_ulDemand32, 4);	 	  	 	

                if ( 0x00 == pV_ucDisplayData[1] )             /*��4����*/ 
                {
                    GV_KillZeroNum = C_KillZero4;
                }
                break;	 	  	 	  
            }
            case 0x00:           /*0λС��*/
            {
                V_ulDemand32 >>= 16;   /*ȥ����4λС��*/

                GV_KillZeroNum = C_KillZero4;             /*��4����*/

                PF_Ulong32ToBuffer4(pV_ucDisplayData, &V_ulDemand32, 4);	 	  	 	

                if ( 0x00 == (pV_ucDisplayData[0] & 0xF0) )             /*��5����*/ 
                {
                    GV_KillZeroNum = C_KillZero5;
                }
                break;	 	  	 	  
            }
            default:             /*Ĭ��4λС��*/
            {
                V_ucDot = 4;                                               /*Ĭ��4λС��*/		 	  	 	  

                if ( (pV_ucDisplayData[0] > 0x49) && (0xFF != pV_ucDisplayData[0]) ) /*���������ж�,ͬʱ�������ݲ�����FF����2��3��������*/
                {
                    V_DeBuff[0] = 0x01;
                    PF_BCDAddBytes(&pV_ucDisplayData[1], &V_DeBuff[0],&pV_ucDisplayData[1], 3);
                }	 	  	 	  

                for (V_uci = 0; V_uci < 3; V_uci++ )    /*ȥ����0���ֽ�*/
                {
                    pV_ucDisplayData[V_uci] = pV_ucDisplayData[V_uci+1];
                }
                GV_KillZeroNum = 0;
                if ( 0x00 == (pV_ucDisplayData[2]&0xF0) )   /*��1����*/
                {
                    GV_KillZeroNum = C_KillZero1;                 
                }
                break;
            }
        }	
#endif    
        switch( V_ucDot ) 
        {
	 	  	 case C_DotNum_3:           /*3λС��*/
	 	  	 {
	 	  	 	 V_ulDemand32 >>= 4; 
				 
	 	  	 }break;
             case C_DotNum_2:           /*2λС��*/
             {
	 	  	 	 V_ucDot = C_DotNum_2;         /*Ĭ����λС��*/
				 V_ulDemand32 >>= 8; 
             }break;
	 	  	 case C_DotNum_1:           /*1λС��*/
	 	  	 {
	 	  	 	 V_ulDemand32 >>= 12; 
	 	  	 }break;	
	 	  	 case C_DotNum_0:           /*0λС��*/
	 	  	 {
	 	  	 	 V_ulDemand32 >>= 16; 
	 	  	 }break;	 	  	 	 
	 	  	 default:             /*Ĭ����ʾ4λС��*/
	 	  	 {
	 	  	 	 V_ulDemand32 >>= 0; 
                 V_ucDot = 4;
             }break;
		}
		
		V_ucj = 8 - 1 - V_ucDot;    		/* ��0ʱ��Ҫ�жϼ�����λ */

		GV_KillZeroNum = 0;
		V_ul64Compare = 0xf0000000;   /* 4���ֽڣ������λ��ʼ�ж� */
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
����ԭ�ͣ�void SF_DotDisplayDeal( uchar8 V_ucDot ) 
��������������С������ʾ����(������ ������ʾ)��ͬʱ��С������ʾ������ʾ����
���������uchar8 V_ucDot��0����С���㣬1��8P 1��С���㡣����
����������� 
���ز������� 
����λ�ã�
��    ע��
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
����ԭ�ͣ�void SF_KillZeroDealPreEn( uchar8 *pV_ucDisData,uchar8 V_ucDot )
������������ȷ����С��λ��(XX.XXXX)����ʾ���㴦��������ʾ���������������ֵȫ�ֱ���GV_KillZeroNum
���������uchar8 pV_ucDisData����ʾ�����ݻ���ָ�룻uchar8 V_ucDot����ʾ������С�������
�����������
���ز�������
����λ�ã�
��    ע��ע�⵱��4λ������Ϊ1ʱ(XXXX XX.XXXX)��С����ǰ(XX.XXXX)��λ����������
*******************************************************************************/                                     
void SF_KillZeroDealPreEn( uchar8 *pV_ucDisData, uchar8 V_ucDot )
{
    uchar8 V_uci, V_ucj = 0;
	
    if ( 0x04 != V_ucDot )
    {
        return;
    }
    for ( V_uci = C_MainDataEn_offset4; V_uci > C_MainDataEn_offset2; V_uci-- )/*����0Ϊ0.0000*/
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
    if ( GV_KillZeroNum > C_KillZero6 ) /*����������,�����5��0*/ 
    {
        GV_KillZeroNum = 0;                         	  
    }
}
/*******************************************************************************
����ԭ�ͣ�void SF_KillZeroDeal( uchar8 *pV_ucDisData, uchar8 V_ucDot )
������������ʾ���㴦��������ʾ���������������ֵȫ�ֱ���GV_KillZeroNum   
���������uchar8 *pV_ucDisData����ʾ�����ݻ���ָ�룻uchar8 V_ucDot����ʾ������С������� 
����������� 
���ز������� 
����λ�ã�
��    ע�����������㴦��ģ����С����ǰ����ǰ�������е���ȫ�����㣬��0000.005���������ʵ��Ϊ0.005
*******************************************************************************/                                      
void SF_KillZeroDeal( uchar8 *pV_ucDisData, uchar8 V_ucDot )
{
    uchar8 *pV_ucChieseTable;
    uchar8 V_uci,V_ucDataLen, V_ucKillZeroNum;
    uchar8 V_ucDataBuff, V_ucDataLenByte, V_ucj;
    uchar8 V_ucDataBuffByte;
	 	 
    pV_ucChieseTable = (uchar8 * )(GV_Str_DisplayFlag.P_ChieseTableNo+GV_Str_DisplayFlag.ChieseTableLineNo*C_ChineseSignLen);  /*���ֱ��ṹ���ַ*/
    V_ucDataLen = pV_ucChieseTable[C_ChinaLineDataLenKillZero];   /*ȡ��4λ��ʾ���ݳ���*/

   
    V_ucDataLen &= C_GetChinaDataLenBit0x07;    /*ȡ��4λҪ��ʾ���ݳ���*/
    V_ucDataLenByte = 2*V_ucDataLen;  /*�ߡ���4λ���ֿ��ж����㣬���ݳ���*/

    V_ucKillZeroNum = pV_ucChieseTable[C_ChinaLineDataLenKillZero];  /*Ҫ��ʾ��������*/
   
    V_ucKillZeroNum &= 0xF0;    /*ȡ��4λ������С��λ��*/
    V_ucKillZeroNum >>= 4;
   
    GV_KillZeroNum = (V_ucKillZeroNum & 0x07);  /*ȡ�����������*/
    
    if ( 0x08 == (V_ucKillZeroNum & 0x08 ))    /*��4λ�жϣ�Ϊ1��ʾ���������������㣬���Ը����ݲ������������жϴ���*/
    {                                 /*�����Ʊ�Ÿ�4λ��ֻ��ǰ4���㣬ʵ�����ݲ��ж�*/
        return;
    }	       
    else                              /*�����������ж�*/
    {
        if ( V_ucDot >= V_ucDataLenByte )   /*����������*/
        {
            return;   	  	 
        }
        else                   /*��λ�������*/
        {
            for ( V_uci = 0; V_uci < (V_ucDataLenByte-V_ucDot-1); V_uci++ )  /*���ж���������λ��*/
            {
                V_ucj = V_uci/2;
                V_ucDataBuff = pV_ucDisData[V_ucDataLen-1-V_ucj];    /*ȡ�ж���������*/

                if ( 0x00 == (V_uci%2) )  /*ÿ�����ݷָߡ���4λ���ֱ��ж�,*/
                {                  /*�棺ȡ��4λ�����жϡ�ż��ȡ��4λ�����ж�*/
                    V_ucDataBuffByte = (V_ucDataBuff&0xF0);
                    if ( 0x00 != V_ucDataBuffByte )          /*��Ϊ0���˳�����������λ�����ж�*/
                    {
                        break;
                    }
                    else
                    {
                        GV_KillZeroNum++;   	  	 	  	 	  
                    }
                }
                else        /*���ݵ�4λ�ж�*/
                {
                    V_ucDataBuffByte = (V_ucDataBuff & 0x0F);
                    if ( 0x00 != V_ucDataBuffByte )          /*��Ϊ0���˳�����������λ�����ж�*/
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
    if ( GV_KillZeroNum > C_KillZero7 ) /*����������*///
    {
        GV_KillZeroNum=0;                         	  
    }
}
/*******************************************************************************
����ԭ�ͣ�void SF_DisplayUnit( uchar8 V_ucDisUnit )
������������λ��ʾ����ͬʱ����λ��ʾ������ʾ����
���������uchar8 V_ucDisUnit����ʾ��λ��� 
		#define C_DiskWNum                  1 
		#define C_DiskWhNum                 2 
		#define C_DiskvarNum                3
		#define C_DiskvarhNum               4 
		#define C_DisVNum                   5 
		#define C_DisANum                   6
		#define C_DiskVANum                 7
		#define C_DisYuanNum                8   "Ԫ"
		#define C_DisWanYuanNum             9   "��Ԫ"
		#define C_DisAhNum                  10
		#define C_DiskVAhNum                11 
		#define C_DisYuankwhNum             12   "Ԫ/kwh"  
		#define C_DisVANum                  13   "VA"
�����������
���ز�������
����λ�ã�
��    ע��
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
����ԭ�ͣ�void SF_DisplayChinaese(void)                                            
��������������������ʾ�������ݸ������ֱ����д��ʾ���棬�ڲ��Ե�����������ǰ�������жϴ������¼��ϼ�
          �£�ͬʱ����DI0��������ʾ�������������漰�����뵱ǰ������ʱ�ұ�ʶ�����У�ֻ�е�ǰ��ʱ����Ӧ���� 
          ����С���ǰ���롰�ϡ���Ϊ�㡣��ǰʣ�����ǰ͸֧���������ݱ�ʶ���������к��ֱ��ʱ�������¼���                                                                 
          ¼,ֻ�С��ϼ�����û�С���ǰ��ʱ�����ֱ����Ҫ�С��ϡ������ݡ��ϡ���λ�жϣ��Ƿ���Ҫ��ʾ���ϼ���   
�����������                                                                                               
�����������                                                                                               
���ز����� ��                                                                                               
����λ�ã�                                                                                                 
��    ע��                                                                                                 
*****************************************************************************************************************/                                       
void SF_DisplayChinaese( void )
{
    ulong32 V_ulDi0Hex;
    ulong32 V_ulDi32, V_ulRelatedDI;
    uchar8	*pV_ucChieseTable;
    uchar8	V_uci, V_ucDataBuff, V_ucDi[4];
    uchar8	V_ucDi0BCD;
    uchar8	V_ucRelated_CodeID[4];
   
    if ( C_ALLScreenDisplayDi == GV_Str_DisplayFlag.CodeID )   /*��ʶ��ΪȫFF*/
    {
        return;   	 
    }
    pV_ucChieseTable = (uchar8 *)(GV_Str_DisplayFlag.P_ChieseTableNo + GV_Str_DisplayFlag.ChieseTableLineNo * C_ChineseSignLen);  /*���ֱ��ṹ���ַ*/
    V_ucDataBuff = pV_ucChieseTable[0];          /*���ֱ���һ���ֽ�*/

    V_ulDi32 = GV_Str_DisplayFlag.CodeID;
	PF_Ulong32ToBuffer4(&V_ucDi[0], &V_ulDi32, C_DataCodeLen);
    
    if ( ( 0x00 == ( V_ucDi[3] & 0xf0 ) )
      || ( 0x10 == ( V_ucDi[3] & 0xf0 ) ) )  /*���������������*/
	{
        V_ucDataBuff |= C_DisCurr;
        
		if ( V_ucDi[0] != 0 )
	    {
			V_ulDi0Hex = V_ucDi[0] - 1;         /*���ʵ��ܣ����ʺź�������1*/
	    }
	    else
	    {
			V_ulDi0Hex = 0;                    /*������*/
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
            if ( V_ulDi0Hex > 12 )              /*����12��ʱ��ֱ�ӹ̶�Ϊ12��Ŀǰ���������ݣ�û����ʾ�ϡ�����*/
            {
                V_ulDi0Hex = 12;         	 	 
            }
#endif
			PF_HextoBCDBytes(&V_ulDi0Hex,&V_ucDi0BCD,&V_uci);
		 
            V_ucDataBuff |= C_DisLast;                          /*���ϡ���ʾ*/
            V_ucDataBuff &= (~C_DisCurr);			              /*��ʾ���ϡ�����ʾ��ǰ*/
            GV_ucDisplayData[9] = V_ucDi0BCD;                   /*��ʾ �ڼ�*/
            
            if ( ( V_ucDi[3] == 0x50 )
              && ( ( V_ucDi[2] == 0x05) || (V_ucDi[2] == 0x06) ) )  /*��һ��������ʾ��*/
            {
                V_ucDataBuff |= C_DisMonth;                       /*���ϡ���ʾ*/
            }
            
            V_ulRelatedDI = GV_Str_DisplayFlag.Related_CodeID;
            PF_Ulong32ToBuffer4(&V_ucRelated_CodeID[0], &V_ulRelatedDI, C_DataCodeLen);
            
            if ( V_ucRelated_CodeID[0] != 0 )
            {
                V_ulDi0Hex = V_ucRelated_CodeID[0] - 1;         /*���ʵ��ܣ����ʺź�������1*/
            }
            else
            {
                V_ulDi0Hex = 0;                                 /*������*/
            }
            
            V_ucDi0BCD = PF_HextoBCDOneBytes(V_ulDi0Hex);
            GV_ucDisplayData[C_EngyRate18_offset] = V_ucDi0BCD;
		}
		else
		{
            if ( C_DisLast == (V_ucDataBuff & C_DisLast) )	    /*ȡ���ϡ�λ����״̬*/
            {
                GV_ucDisplayData[9] = 1;                /*��ʾ �ڼ�*/   	  	 
            }
		}
	}
	
    for (V_uci = 0; V_uci < 4; V_uci++ )                        /*��������ʾ���渳ֵ*/
    {
        GV_ucDisplayData[18 + V_uci] = pV_ucChieseTable[1 + V_uci];
    }
    
    if ( ( V_ulDi32 & 0xffff0000 ) == 0x30000000 )
	{
		GV_ucDisplayData[20] |= C_DisLossVol;           /*��ʧѹ����ʾ*/
	}

	if ( ( V_ulDi32 & 0xffff0000 ) == 0x30040000 )
	{
	 	GV_ucDisplayData[20] |= C_DisLossCurr;          /*��ʧ������ʾ*/	 	  	 	  	 
	}

	if ( ( V_ucDi[2] <= 8 ) && ( V_ucDi[3] == 0x30 ) )
	{
		if ( V_ucDi[1] == 0x07 )
		{
            GV_ucDisplayData[19] |= C_DisAPhase;          /*��A����ʾ*/	  	 	  
		}
		else if ( V_ucDi[1] == 0x08 )
		{
            GV_ucDisplayData[19] |= C_DisB;               /*��B����ʾ*/	 	  	 	  	 	  	 	  	 
		}
		else if ( V_ucDi[1] == 0x09 )
		{
            GV_ucDisplayData[19] |= C_DisC;               /*��c����ʾ*/	 	  	 	  	 	  	 	  	 	 	  	 	  	 	  
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
        GV_ucDisplayData[C_RecordNum_offset] = V_ucDi0BCD;                   /*��ʾ �ڼ�*/
    }
    else
    {
        ;
    }
    
    GV_ucDisplayData[17] |= V_ucDataBuff;
}
/*******************************************************************************
����ԭ�ͣ�void SF_DisplayDI(void)  
����������DI�������ʾ��DI hex��BCD��ʽ��ϣ���ʾ���hex��ʽ,����ʾ��Ŵ���255ʱ����Ź̶���ʾΪ255 
����������� 
����������� 
���ز������� 
����λ�ã�
��    ע��
*******************************************************************************/                                
void SF_DisplayDI( void )
{
    ulong32 V_ulDi32;
    uchar8 V_ucDi[5], V_uci;

    if ( C_ALLScreenDisplayDi == GV_Str_DisplayFlag.CodeID )   /*��ʶ��ΪȫFF*/
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
����ԭ�ͣ�void SF_StateDisVolageLimt(uchar8 V_ucStateNum)
����������״̬�ַ���ʾ����Ҫ���е�ѹ�����жϣ�������Դ��ѹ����һ����ֵʱ��״̬�ַ���������������Դ����ʱ����
		���ǵ�ѹ���ơ������ϵ�ʱû�е�ѹ���ƣ�Ŀǰ��״̬�ַ���������
���������uchar8 V_ucStateNum:�账��״̬�ַ��궨�壬Ŀǰ�����б��⣻
		C_BackLED�����⣻  
�����������
���ز�������
����λ�ã�
��    ע�����ϵ�5s�ڣ���������������е�ѹ�ж�   
*******************************************************************************/                                       
void SF_StateDisVolageLimt( uchar8 V_ucStateNum )
{	 
    if ( C_BackLED == V_ucStateNum )  /*���⴦��*/
    {
        if ( GV_ShutBackLEDTime < C_ShutBackLEDTime5s )   /*�ϵ��ʼ��������5s������������жϵ�ѹ*/
        {
            InF_SwithPeripherals(C_BackLight, C_On);
            return;
        }
    }
	 	  	 	  
    if ( C_OK == Inf_BackLightLimit() )  /*��ѹ����Ҫ��Ŀǰ�ǡ�60%Un���������⡢�����̵���*/
    {
        switch( V_ucStateNum )
        {
            case C_BackLED:   /*����*/
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
    else   /*��ѹ������*/
    {
        switch( V_ucStateNum )
        {
            case C_BackLED:   /*����*/
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
����ԭ�ͣ�void SF_WranRelayAction(void) 
���������������̵�����������Դ��ѹ�жϣ����ü̵���ģ��ӿں���������ѹ����Ҫ��ʱ�����������̵�������
�����������
�����������
���ز�������
����λ�ã�
��    ע��
*******************************************************************************/                                       
void SF_WranRelayAction( void )
{	 
	ushort16 V_usLen, V_usDataEncode;
    uchar8 V_ucReturn_Flag, V_ucBuf[2];
   
    V_usLen = 2;
    V_ucReturn_Flag = InF_Read_Data(CMeter_Work_State3, &V_ucBuf[0], &V_usLen, &V_usDataEncode);
   
    if ( ( C_OK == V_ucReturn_Flag ) && ( (V_ucBuf[0]&0x06) == 0x02 ) )/*������Դ����*/
    {
        InF_SwithPeripherals(C_WarnOut, C_On);
    }
    else
    {
        if ( C_VoltageOk == InF_JudgeVolage_Relay() )  /*���ü̵���ģ��ӿں��������е�ѹ�ж�*/
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
����ԭ�ͣ�void SF_DisplayStateSign(void) 
������������ʾ״̬�ַ�����ѹ�����������ŷ��ţ����¼���¼ģ���·���˸ʱ����˸���ȣ�����·�����ʱ�����ԡ�
		���(��������ģ��)���ǳ��ԣ����ԣ�����������˸Ϊ������ȼ������Ϊ���ԣ����Ϊ���ԡ��ò��ִ���
		���(��������ģ��)���ǳ��ԣ����ԣ�����������˸Ϊ������ȼ������Ϊ���ԣ����Ϊ���ԡ��ò��ִ���
�����������
�����������
���ز�������
����λ�ã�
��    ע��
*******************************************************************************/                                      
void SF_DisplayStateSign( void )
{
    Str_DisplaySignMesNum *pStr_DisplaySignMesNum;
    uchar8 *pV_ucDisStateBuff;
    uchar8 V_uci, V_ucj;
   
    for ( V_uci=0; V_uci<GV_Str_DisplaySignLen; V_uci++ )
    {
        pStr_DisplaySignMesNum = (Str_DisplaySignMesNum *)GV_Str_DisplaySign[V_uci].PStr_DisplaySignMesNum;
        pV_ucDisStateBuff = GV_Str_DisplaySign[V_uci].PDisplyBuff;   /*��ʾ�����ַ*/
   	  
        switch( GV_Str_DisplaySign[V_uci].StateNum )
        {
            case C_UaSign:    /*��ѹ������������ ��ʾ���ţ����⴦��*/
            case C_UbSign:
            case C_UcSign:
            case C_IaSign:
            case C_IbSign:
            case C_IcSign:
            case C_IaNegativeSign:
            case C_IbNegativeSign:
            case C_IcNegativeSign:   	  	 	
            {   	  	 	  
                for ( V_ucj = 0; V_ucj < GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen; V_ucj++ ) /*�¼���¼����˸����*/
                {
                    if ( C_Msg_PowerNetworkMonitoring == pStr_DisplaySignMesNum[V_ucj].SourceNo )
                    {
                        if ( C_TwinkleDisplayNiu == pStr_DisplaySignMesNum[V_ucj].Timer ) /*�¼���¼����˸����*/
                        {
                            if ( (C_IaNegativeSign == GV_Str_DisplaySign[V_uci].StateNum)
                              || (C_IbNegativeSign == GV_Str_DisplaySign[V_uci].StateNum)  /* ��-������ʾ����ѧ���¼���¼����������˸ʱ����-����һ��*/                                       
                              || (C_IcNegativeSign == GV_Str_DisplaySign[V_uci].StateNum) )   /* û���жϵ�ǰ���ʷ���,��ʾģ���жϣ���������-���Ÿö�ʱ���Ƿ�Ϊ�㣬�粻���㣬˵���Ƿ�������˸*/ 
                            {
                                if ( C_NotDisplayNiu != pStr_DisplaySignMesNum[V_ucj+1].Timer )  /*������-����ʾʱ�䲻��0����˸*/
                                {
                                    if ( GV_Str_DisplayFlag.ParityTimer < 2 )   /*��ż��ʱ���������ԣ�ż������*/
                                    {
                                        (*pV_ucDisStateBuff) |= GV_Str_DisplaySign[V_uci].DisplyBuffBit;
                                    }   	  	 	     	 	   	  	 
                                }
                            }	                                                          
                            else         /*��ѹ������״̬�ַ�����*/
                            {
                                if ( GV_Str_DisplayFlag.ParityTimer < 2 )   /*��ż��ʱ���������ԣ�ż������*/
                                {
                                    (*pV_ucDisStateBuff) |= GV_Str_DisplaySign[V_uci].DisplyBuffBit;
                                }   	  	 	     	 	   	  
                            }   	  	 	     	 	   
                            break;   	  	 	  	 	  	 
                        }
                        else
                        {
                            if ( C_NotDisplayNiu == pStr_DisplaySignMesNum[V_ucj].Timer ) /*�¼���¼������*/
                            {
                                break;              /*ÿ500ms,��ʾͳһˢ�£���ʾ��������*/   	  	 	  	 	  	 	  
                            }
                        }	   	  	 	  	 	  
                    }   	  	 	  	 	  
                }
				
                if ( GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen == V_ucj )  /*û��������������,��Ϊ����*/
                {
                    for ( V_ucj = 0; V_ucj < GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen; V_ucj++ )
                    {
                        if ( C_Msg_PowerNetworkMonitoring == pStr_DisplaySignMesNum[V_ucj].SourceNo )  /*��ʵ�ò��ֲ����жϣ������¼�ָʾ�������������ʣ����ǳ��ԡ�Ŀǰ�¼�û�з�������������Ϣ����ʾ*/
                        {
                            if ( C_NotDisplayNiu != pStr_DisplaySignMesNum[V_ucj].Timer ) /*��ʾʱ�䲻Ϊ��*/
                            {
                                if ( (C_IaNegativeSign == GV_Str_DisplaySign[V_uci].StateNum)
                                  || (C_IbNegativeSign == GV_Str_DisplaySign[V_uci].StateNum)  /* ��-������ʾ����ѧ���¼���¼����������˸ʱ����-����һ��  */                                     
                                  || (C_IcNegativeSign == GV_Str_DisplaySign[V_uci].StateNum) )   /* û���жϵ�ǰ���ʷ���,��ʾģ���жϣ���������-���Ÿö�ʱ���Ƿ�Ϊ�㣬�粻���㣬˵���Ƿ�������˸*/ 
                                {
                                    if ( C_NotDisplayNiu != pStr_DisplaySignMesNum[V_ucj+1].Timer )  /*������-����ʾʱ�䲻��0,������ϢԴ���¼���¼��ϢԴ����1��*/
                                    {
                                        (*pV_ucDisStateBuff) |= GV_Str_DisplaySign[V_uci].DisplyBuffBit;
                                    }
                                }
                                else   /*��ѹ������״̬�ַ�����*/
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
            case C_RelayStatusLED:   /*�����Ƿ���ȫ��ģʽ,��բָʾ�ơ�������*/
            {
                if ( C_ALLScreenDisplay == GV_Str_DisplayFlag.SV_ucDisplayMode )
                {
                    InF_SwithPeripherals(C_BackLight, C_On);  /*ȫ�Բ����е�ѹ����*/
                    InF_SwithPeripherals(C_TripLed, C_On);
                }
                else
                {
                    for ( V_ucj = 0; V_ucj < GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen; V_ucj++ )
                    {
                        if ( C_TwinkleDisplayNiu == pStr_DisplaySignMesNum[V_ucj].Timer ) /*��˸����*/
                        { 
                            if ( GV_Str_DisplayFlag.ParityTimer < 2 )   /*��ż��ʱ���������ԣ�ż������*/
                            {
                                if ( C_BackLED == GV_Str_DisplaySign[V_uci].StateNum )
                                {
                                    SF_StateDisVolageLimt(C_BackLED);  /*��ѹ����*/
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
                    if ( GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen == V_ucj )  /*û��������������*/
                    {
                        for ( V_ucj = 0; V_ucj < GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen; V_ucj++ )
                        {
                            if ( C_NotDisplayNiu != pStr_DisplaySignMesNum[V_ucj].Timer ) /*��ʾʱ�䲻Ϊ��*/
                            { 
                                if ( C_BackLED == GV_Str_DisplaySign[V_uci].StateNum )
                                {
                                    SF_StateDisVolageLimt(C_BackLED);  /*��ѹ����*/
                                }
                                else
                                {
                                    InF_SwithPeripherals(C_TripLed, C_On);
                                }
                                break;
                            }
                        }
                    }
                    if ( GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen == V_ucj )  /*û��������������*/
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
                    if ( C_TwinkleDisplayNiu == pStr_DisplaySignMesNum[V_ucj].Timer ) /*��˸,����*/
                    { 
                        if ( GV_Str_DisplayFlag.ParityTimer < 2 )   /*��ż��ʱ���������ԣ�ż������*/
                        {
                            if ( (C_WarnOutPut == GV_Str_DisplaySign[V_uci].StateNum)
                              || (C_Beeper == GV_Str_DisplaySign[V_uci].StateNum) )   /*�������������̵���*/
                            {
                                if ( C_Beeper == GV_Str_DisplaySign[V_uci].StateNum )
                                {
                                    ;/*InF_SwithPeripherals(C_Beep,C_On);*/  /*��������������ֱ���������ṩ�ӿں���*/
                                }
                                else
                                {
                                    SF_WranRelayAction();
									/*SF_StateDisVolageLimt(C_WarnOutPut); */ /*��ѹ����*/
                                }
                            }
                            else   /*����״̬�ַ�*/
                            {
                                (*pV_ucDisStateBuff) |= GV_Str_DisplaySign[V_uci].DisplyBuffBit;
                            }
                        }
                        else
                        {
                            if ( (C_WarnOutPut == GV_Str_DisplaySign[V_uci].StateNum)
                              || (C_Beeper==GV_Str_DisplaySign[V_uci].StateNum) )   /*�������������̵���*/
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
                if ( GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen == V_ucj )  /*û��������������*/
                {
                    for ( V_ucj = 0; V_ucj < GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen; V_ucj++ )
                    {
                        if ( C_NotDisplayNiu != pStr_DisplaySignMesNum[V_ucj].Timer ) /*��ʾʱ�䲻Ϊ��*/
                        { 
                            if ( (C_WarnOutPut == GV_Str_DisplaySign[V_uci].StateNum)
                              || (C_Beeper == GV_Str_DisplaySign[V_uci].StateNum) )   /*�������������̵���*/
                            {
                                if ( C_Beeper == GV_Str_DisplaySign[V_uci].StateNum )
                                {
                                    ;/*InF_SwithPeripherals(C_Beep,C_On);*/
                                }
                                else
                                {
                                    SF_WranRelayAction();
									/*SF_StateDisVolageLimt(C_WarnOutPut);*/  /*��ѹ����*/
                                }    	  	 	      	  	  
                            }
                            else   /*����״̬�ַ�*/
                            {
                                (*pV_ucDisStateBuff) |= GV_Str_DisplaySign[V_uci].DisplyBuffBit;
                            }
                            break;
                        }
                    }
                }
                if ( GV_Str_DisplaySign[V_uci].Str_DisplaySignMesNumLen == V_ucj )  /*û��������������,״̬�ַ���ʾ����������*/
                {
                    if ( (C_WarnOutPut == GV_Str_DisplaySign[V_uci].StateNum)
                      || (C_Beeper == GV_Str_DisplaySign[V_uci].StateNum) )   /*�������������̵���*/
                    {
                        if ( C_Beeper == GV_Str_DisplaySign[V_uci].StateNum )
                        {
                            ;/*InF_SwithPeripherals(C_Beep,C_Off);*/
                        }
                        else              /*�����̵���*/
                        {
                            InF_SwithPeripherals(C_WarnOut,C_Off);           /*�ر���ʾ*/ 
                        }
                    }    
                }
            }
        }
    }
}
/*******************************************************************************
����ԭ�ͣ�uchar8 InF_AlarmState(void)
��������������״̬�����ǵ�ǰ�Ƿ���ȫ��ģʽ
�����������
�����������
���ز�������
����λ�ã�
��    ע��20141104,������������Ҫ����ѹ��������������ʾ��ֻ�����¼���ʾ��������ʵʱ����ʾ
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
            if ( C_NotDisplayNiu != pStr_DisplaySignMesNum[V_ucj].Timer ) /*��ʾʱ�䲻Ϊ��*/
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
����ԭ�ͣ�void SF_DisAllData(void)
���������������ڲ��ж�ȫ����ʾ����Һ���鿴(ȫFF)����ʾ����ȫ����1
�����������
�����������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/                                     
void SF_DisAllData( void )
{	 
#if(0)
    if ( C_ALLScreenDisplay == GV_Str_DisplayFlag.SV_ucDisplayMode )  /*ȫ����ʾ*/
    {
        memset(&GV_ucDisplayData[0], 0xFF, C_DisplayDataByte);
        memset(&GV_ucDisplayData[0], 0x88, 9);
        GV_ucDisplayData[9] = 0x18;
        GV_ucDisplayData[C_Ladder8_offset] = 0x08;
        GV_ucDisplayData[C_EngyRate18_offset] = 0x18;
        GV_ucDisplayData[C_Rate18_offset] = 0x18;
        GV_ucDisplayData[C_MainDataHig_offset] = 0x88;
        /*GV_DispAllScreenMode = 0xFF;*/        /*����ȫ����ʾģʽ*/
    }
    else
    {
        if ( C_CheckDisplay == GV_Str_DisplayFlag.SV_ucDisplayMode )  /*Һ���鿴*/
        {
            if ( (C_ALLScreenDisplayDi == GV_Str_DisplayFlag.CodeID)
              && (0xFF == GV_Str_DisplayFlag.ParaNum) )   /*��ʶ��ȫFF*/
            {
                memset(&GV_ucDisplayData[0], 0xFF, C_DisplayDataByte);
                memset(&GV_ucDisplayData[0], 0x88, 9);
                GV_ucDisplayData[9] = 0x18;
                GV_ucDisplayData[C_Ladder8_offset] = 0x08;
                GV_ucDisplayData[C_EngyRate18_offset] = 0x18;
                GV_ucDisplayData[C_Rate18_offset] = 0x18;
                GV_ucDisplayData[C_MainDataHig_offset] = 0x88;
                /*GV_DispAllScreenMode = 0xFF;*/     /*����ȫ����ʾģʽ*/
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
����ԭ�ͣ�void SF_CardAbnormalDisDeal(Str_DisplayStatus *pV_ucBuffer)
�����������忨�쳣��ʾ����
���������Str_DisplayStatus *pV_ucBuffer���忨�쳣�ַ���ʾ����
			typedef struct
			{ 
				ushort16 Time; ��ʾʱ�䣬����ܴ���65535/2�룬��ʾ�ڲ���500msΪ��׼
				uchar8 Type��    BCD��ʽ  
			}Str_DisplayStatus; 
�����������
���ز�������
����λ�ã�
��    ע����ȫ�ֱ�����ǰ��ʾ״̬Ϊ�忨�쳣��ʾ״̬C_CardAbnormalDisplay;ͬʱ��ֵ��ʾ����GV_CardAbnDisplayNum
*******************************************************************************/                                       
void SF_CardAbnormalDisDeal( Str_DisplayStatus *pV_ucBuffer )
{
    GV_Str_DisplayFlag.SV_usDisplayTimer = ((*pV_ucBuffer).Time*2);    /*�쳣������ʾʱ��*/
    GV_Str_DisplayFlag.SV_ucDisplayMode = C_CardAbnormalDisplay;     /*�쳣�忨��ʾģʽ*/ 
    GV_CardAbnDisplayNum = (*pV_ucBuffer).Type;                         /*��ʾ��������û������*/ 
}
/*******************************************************************************
����ԭ�ͣ�void SF_DisplayCardAbnormal(void) 
�����������忨�쳣��ʾ���ݻ��洦��ERR--XX 
�����������
�����������
���ز�������
����λ�ã�
��    ע����ʾ���渳ֵ 
*******************************************************************************/                                      
void SF_DisplayCardAbnormal( void )
{
    GV_KillZeroNum = C_SF_Err;          /*�ײ�������ں�����FF��ʾΪ�쳣������ʾ*/

    GV_ucDisplayData[0] = GV_CardAbnDisplayNum;   /*��ʾ�쳣����*/
    GV_ucDisplayData[2] = C_DisE;                 /*��ʾ�쳣����*/
    GV_ucDisplayData[2] |= C_DisR;
    GV_ucDisplayData[1] = (C_DisR << 4);            /*��ʾ�쳣����*/
    GV_ucDisplayData[1] |= C_DisHenggang;         /*��ʾ�쳣����*/	 
}
/*******************************************************************************
����ԭ�ͣ�void SF_ClearDisplyBuff( void )
��������������ʾ�������ݼ��������ȫ�ֱ�����ÿ500ms��1������
�����������
�����������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/                                       
void SF_ClearDisplyBuff( void )
{
    memset(GV_ucDisplayData,0x00,C_DisplayDataByte);

    GV_KillZeroNum=0;                        /*��С����*/
}
/*******************************************************************************
����ԭ�ͣ�void SF_DisLTData(void ) 
������������ʾ���ʺ�/���ݺ� ����
�����������
�����������
���ز�������
����λ�ã�
��    ע��
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
����ԭ�ͣ�void InF_Display_Message( Str_Msg_Parameter *pStr_Msg_Parameter )
������������ʾ��Ϣ���� 
���������Str_Msg_Parameter *pStr_Msg_Parameter,����Ϣ�������ݽṹ�壬���ȷ���
		typedef struct
		{
			uchar8 PowerFlag;
			uchar8 SourceAddr;
			uchar8 DerictAddr;
			uchar8 Length;
			uchar8 *Parameter;
		}Str_Msg_Parameter;
����������� 
���ز�����
����λ�ã�
��    ע��C_ParameterMaxLen:40 ��Ϣ���ݲ�����󻺴棬������Ҫ�޸ģ����ֻ�ܷ�10��PT(4�ֽڲ���)
*******************************************************************************/                                  
void InF_Display_Message( Str_Msg_Parameter *pStr_Msg_Parameter )
{
    Str_Msg_Parameter Str_Msg_Parameter;
    Str_DisplayStatus Str_DisSign;
    ulong32 V_ulDi,V_ulRelatedDi;
    ushort16 V_usDisTime;
    uchar8 V_ucParameter[C_ParameterMaxLen],V_ucDisBuff[10];
    uchar8 V_uci;
    uchar8 V_ucPt;    /*��������*/
    uchar8 V_ucMoneySign=0;
    uchar8 V_ucDisStateSign;

    Str_Msg_Parameter.PowerFlag = pStr_Msg_Parameter->PowerFlag;
    Str_Msg_Parameter.SourceAddr = pStr_Msg_Parameter->SourceAddr;
    Str_Msg_Parameter.DerictAddr = pStr_Msg_Parameter->DerictAddr;
    Str_Msg_Parameter.Length = pStr_Msg_Parameter->Length;
    Str_Msg_Parameter.Parameter = pStr_Msg_Parameter->Parameter;   /*�ô�������δ���*/    
     
    if ( C_Msg_Display != Str_Msg_Parameter.DerictAddr )
    {
        return;   	 
    }

    if ( ( Str_Msg_Parameter.Length > C_ParameterMaxLen ) || ( 0 == Str_Msg_Parameter.Length ) )
    {
        return;   /*����������*/
    }
	 
    for ( V_uci = 0; V_uci < Str_Msg_Parameter.Length; V_uci++ )
    {
        V_ucParameter[V_uci] = Str_Msg_Parameter.Parameter[V_uci];/*�Ƿ��������ݳ��Ȳ���*/
    }
   
    if ( C_Msg_Card == Str_Msg_Parameter.SourceAddr )  /*��������Ϣ*/
    {
        if ( C_L_SmartMeter == C_Meter_Type )  /*ֻ�б��ر�Ž��п���ʾ��ش���*/
        {
            GV_CardDisSign = C_CardDis;   	  	 
        }
    }
      
    while( Str_Msg_Parameter.Length )   /*Pt����*/
    {
        V_ucPt = V_ucParameter[0];
        switch( V_ucPt )
        {
            case Pt_Dispatch_Timing:  /*500ms��ˢ����ʾ*/
            {
                if ( Str_Msg_Parameter.Length < 2 )  /*�����Ͱ������������ݳ���*/
                {
                    return;    /*����������*/
                }
                if ( C_HalfSecond == V_ucParameter[1] )  /*ÿ500msˢ����ʾ*/
                {
                    Str_Msg_Parameter.Length -= 2;     /*��Pt�������ݳ���*/
                    for ( V_uci = 0; V_uci < Str_Msg_Parameter.Length; V_uci++ )/*����ƫ��*/
                    {
                        V_ucParameter[V_uci] = V_ucParameter[V_uci+2];
                    }

                    if ( C_PowerOff == Str_Msg_Parameter.PowerFlag )   /*�͹���*/
                    {
                        SF_PowerOffDisplay500msTimer();   
                    }
                    else
                    {   
                        SF_PowerOnDisplay500msTimer();
                    }
   	  	 	  	 	/********��ʾ����***********/
                    SF_ClearDisplyBuff();  /*��ʾ��������*/

                    if ( C_CardAbnormalDisplay != GV_Str_DisplayFlag.SV_ucDisplayMode ) /*�쳣�忨��ʾģʽ*/
                    {
                        SF_DisplyMainData(V_ucMoneySign);   /*��������ʾ8λ����*/

                        SF_DisplayChinaese();  /*����������ʾ*/

                        SF_DisplayDI();        /*DI�������ʾ*/	 
                    }
                    else
                    {
                        SF_DisplayCardAbnormal();  /*���쳣��ʾ���봦��*/
                    }
    	  	 	   
                    SF_DisplayStateSign();  /*״̬�ַ���ʾ*/
                    if ( C_PowerOff != Str_Msg_Parameter.PowerFlag )   /*�͹���*/
                    {
                        SF_DisLTData();
                    }
                    else
                    {
                        ;
                    }
                    SF_DisAllData();        /*��ʾ������1���ڲ��ж��Ƿ���Ҫȫ����ʾ*/
               
                    InF_WriteLCD(&GV_ucDisplayData[0], C_LCDLen, GV_KillZeroNum);  /*�ײ�������ʾ*/
                }
                else
                {
                    return;
                }
                break;
            }
            case Pt_Dispatch_Key:  /*����*/
            {
                if ( Str_Msg_Parameter.Length < 2 )
                {
                    return;    /*����������*/
                }
                if ( (C_KeyUp == V_ucParameter[1]) || (C_KeyDown == V_ucParameter[1]) )   /*�ϡ��·���*/
                {
                    Str_Msg_Parameter.Length -= 2;     /*��Pt�������ݳ���*/

                    SF_DisplyKey(V_ucParameter[1]);  /*������ʾ����*/      	  	 	  	 

                    for ( V_uci = 0; V_uci < Str_Msg_Parameter.Length; V_uci++ )/*����ƫ��*/
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
            case Pt_DisplayID:  /*Һ���鿴*/
            {
                if ( Str_Msg_Parameter.Length < 12 )
                {
                    return;    /*����������*/ 
                }

                PF_Buffer4ToUlong32(&V_ucParameter[1], &V_ulDi, 4);
                PF_Buffer4ToUlong32(&V_ucParameter[5], &V_ulRelatedDi, 4);	
                ushort16 V_usTimer;
                PF_Buffer2ToUshort16(&V_ucParameter[6+4], &V_usTimer);
                SF_CheckDisplay(V_ulDi,V_ulRelatedDi, V_ucParameter[9], V_usTimer);      /*Һ���鿴����*/

                if ( GV_Str_DisplayFlag.CodeID == CChargeBal_Hex_Cent )
                {
                    SF_GetDisplayData(&V_ucDisBuff[0]);                   /*��ȡ��Ҫ��ʾ�����ݣ�ÿ����ʾ�账���������5���ֽ�*/
                    PF_CopyDataBytes(&V_ucDisBuff[0], &GV_RemainMoney[0][0], CLChargeBal_BCD);
                }
                Str_Msg_Parameter.Length -= 12;     /*��Pt�������ݳ���*/   	  	 	     	  	 	  
                for ( V_uci = 0; V_uci < Str_Msg_Parameter.Length; V_uci++ )/*����ƫ��*/
                {
                    V_ucParameter[V_uci] = V_ucParameter[V_uci + 12];
                } 
                break;	  	 	  	 
            }
            case Pt_DisplayStatus:  /*״̬�ַ�����*/
            {
                if ( Str_Msg_Parameter.Length < 4 )
                {
                    return;    /*����������*/
                }

                PF_Buffer2ToUshort16(&V_ucParameter[2], &V_usDisTime);

                Str_DisSign.Time = V_usDisTime;
                Str_DisSign.Type = V_ucParameter[1];

                V_ucDisStateSign = Str_DisSign.Type&0x3F;
                if ( (V_ucDisStateSign == C_DoingSign) || (V_ucDisStateSign == C_SuccessSign) || (V_ucDisStateSign == C_ReadCardSign) )/*��ʾ�ɹ��������������⴦����ʾ��ֵǰʣ����2s����*/
                {
                    V_ucMoneySign = C_MoneySign;
                }           

                SF_DisplaySignMessage(&Str_DisSign, Str_Msg_Parameter.SourceAddr);/*״̬��ʾ�ַ�����*/

                Str_Msg_Parameter.Length -= 4;     /*��Pt�������ݳ���*/  	  	 	     	  	 	  
                for ( V_uci = 0; V_uci < Str_Msg_Parameter.Length; V_uci++ )/*����ƫ��*/
                {
                    V_ucParameter[V_uci] = V_ucParameter[V_uci+4];
                }
                break; 	  	 	  	 
            }
            case Pt_ERRXXDisplay:  /*���쳣��ʾ*/
            {
                if ( Str_Msg_Parameter.Length < 4 )
                {
                    return;    /*����������*/
                }

                PF_Buffer2ToUshort16(&V_ucParameter[2], &V_usDisTime); 

                Str_DisSign.Time = V_usDisTime;
                Str_DisSign.Type = V_ucParameter[1];

                SF_CardAbnormalDisDeal(&Str_DisSign);      /*�忨�쳣��ʾ����*/

                Str_Msg_Parameter.Length -= 4;     /*��Pt�������ݳ���*/ 	  	 	     	  	 	  
                for ( V_uci = 0; V_uci < Str_Msg_Parameter.Length; V_uci++ )/*����ƫ��*/
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
        if(Str_Msg_Parameter.Length < 2)  /*���������������ݳ��ȱ��룾2*/
        {
            Str_Msg_Parameter.Length = 0;
        }   	  
    }
   
    if ( C_CardDis == GV_CardDisSign )   /*�忨��ʾ��1·������*/
    {
        GV_CardDisSign = C_NoCardDis;

        SF_ClearDisplyBuff();  /*��ʾ��������*/

        if ( C_CardAbnormalDisplay != GV_Str_DisplayFlag.SV_ucDisplayMode ) /*�쳣�忨��ʾģʽ*/
        {
            SF_DisplyMainData(V_ucMoneySign);   /*�忨��ʾ���ɹ����������С�����������������ʾ8λ����*/
            V_ucMoneySign = 0;  	     	 

            SF_DisplayChinaese();  /*����������ʾ*/

            SF_DisplayDI();        /*DI�������ʾ*/	 
        }
        else
        {
            SF_DisplayCardAbnormal();  /*���쳣��ʾ���봦��*/
        }

        SF_DisplayStateSign();  /*״̬�ַ���ʾ*/
        SF_DisLTData();
        SF_DisAllData();        /*��ʾ������1���ڲ��ж��Ƿ���Ҫȫ����ʾ*/

        InF_WriteLCD(&GV_ucDisplayData[0], C_LCDLen, GV_KillZeroNum);  /*�ײ�������ʾ*/  	  
    }	   
}
/*******************************************************************************
����ԭ�ͣ�void SF_TimingFreshSignMesNum(void)
������������ʱˢ��ȫ�ֱ���״̬�ַ���ϢԴ���������ݿɿ���
�����������
�����������
���ز�����
����λ�ã�
��    ע�����ϵ�SF_PowerOnDisplay500msTimer�ж�ʱˢ��
*******************************************************************************/                                   
void SF_TimingFreshSignMesNum( void )
{	 
	/*************************״̬�ַ���ϢԴˢ��*******************************/
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
����ԭ�ͣ�void SF_ReadDispBuff( uchar8 *pV_ucdatabuff )
��������������ʾ״̬ 
����������� 
����������� 
���ز�����
����λ�ã�
��    ע��
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
����ԭ�ͣ�SF_DispAllScreenMode(void) 
����������Һ��ȫ��ģʽ
�����������
�����������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8  SF_DispAllScreenMode( void )
{
    return GV_DispAllScreenMode;
}
#endif
/*******************************************************************************
����ԭ�ͣ�void InF_Card_DispDynamicSign( void )
�����������忨��������ʾ------�������ַ�����
�����������
�����������
���ز�����
����λ�ã�Cardģ��ʹ��
��    ע��
*******************************************************************************/
void InF_Card_DispDynamicSign( void )
{	
	SF_ClearDisplyBuff();/*����ʾ����*/
	SF_DisplayStateSign();/*�ַ�����*/
	SF_DisLTData();/*��ʾLT*/
	InF_WriteLCD_DispDynamicSign(&GV_ucDisplayData[0],9);/*��ʾ��������------*/
}

/*******************************************************************************
����ԭ�ͣ�void SF_DispDataChange(uchar8 *pV_ucDispHexBuff, uchar8 *pV_ucDispBcdBuff, uchar8 V_ucHexDataLen, uchar8 V_ucBcdDataLen, uchar8 V_ucSign, uchar8 V_ucType)
�������������ݷ��ż�ת����ʽ����HEX����ת��ΪBCD
���������pV_ucDispHexBuff����ת����HEX����
          V_ucHexDataLen��HEX���ݳ���
          V_ucBcdDataLen��BCD���ݳ���  
          V_ucSign���Ƿ��з���λ
          V_ucType��ת������
���������pV_ucDispBcdBuff��ת�����BCD����
���ز�����
����λ�ã�
��    ע��
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
    if( V_ucHexDataLen < V_ucBcdDataLen )/*���ȵ�ֻ�е���*/
    {
        if( V_ucType == 0 )/*Ĭ������HEXתBCD*/
        {
            PF_Buffer8ToUlong64(&pV_ucDispHexBuff[0], &V_ul64Data, V_ucHexDataLen);
            if(( V_ucSign != 0 ) && (pV_ucDispHexBuff[V_ucHexDataLen - 1] & 0x80) )/*�з���λ�ĸ���*/
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
    else/*���ڵ��ڣ�ת����BCD���Ƚ�ȡ*/
    {
        if( V_ucType == 0 )/*Ĭ������HEXתBCD*/
        {
            PF_Buffer8ToUlong64(&pV_ucDispHexBuff[0], &V_ul64Data, V_ucBcdDataLen);
            if(( V_ucSign != 0 ) && (pV_ucDispHexBuff[V_ucHexDataLen - 1] & 0x80) )/*�з���λ�ĸ���*/
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
        else if( V_ucType == C_NoNeedChange )/*���ݲ���Ҫת��*/
        {
            PF_CopyDataBytes(pV_ucDispHexBuff, pV_ucDispBcdBuff, V_ucBcdDataLen);
        }
        else if( V_ucType == C_NeedSingleByteChange )/*���ݵ��ֽ�ת��*/
        {    
            for( V_uci = 0; V_uci<V_ucBcdDataLen; V_uci++)
            {
                if(pV_ucDispHexBuff[V_uci] <= 0x63)/*��1�ֽڲ�ת��*/
                {
                    pV_ucDispBcdBuff[V_uci] = PF_HextoBCDOneBytes(pV_ucDispHexBuff[V_uci]);
                }
                else
                {
                    pV_ucDispBcdBuff[V_uci] = pV_ucDispHexBuff[V_uci];
                }
            }
        }
        else if( V_ucType == C_NeedDataChange )/*���ݰ����ڸ�ʽת��*/
        {
            if((V_ucBcdDataLen < 2) || (V_ucHexDataLen < 2))
            {
                memset(pV_ucDispBcdBuff, 0, V_ucBcdDataLen);
            }
            else
            {
                for( V_uci = 0; V_uci<(V_ucHexDataLen-2); V_uci++)
                {
                    if(pV_ucDispHexBuff[V_uci] <= 0x63)/*��1�ֽڲ�ת��*/
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