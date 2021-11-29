
///*****************************************************************************************///
///*Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     LowPower.c
///*Version:       V1
///*Date:          2014-3-12
///*Description:   �͹��Ĵ���
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
#include "LowPower.h"
#include "IO.h"
#include "Timer.h"
#include "uart.h"
#include "MCUConfig.h"
#include "FM33A0XX.h"
#include "ADC.h"

extern void SF_SystemClockInPowerOff(void);
extern void SF_PeriSetupPowerOff(void);
extern void SF_IOSetupPowerOff(void);
extern void SF_IOSetupPowerOff_UsedCAP(void);
extern void SF_RTCWakeUpInit(void);
extern void SF_SoftRTCWakeupMode(void);
extern void SF_SoftRTCInit(void);
extern void SF_EnterLowPower(void);
extern void SF_WritePowerMode_PowerOff(void);
extern void SF_WriteLopwerTime(ulong32 v_di,uchar8 v_lenbuf);
extern void SF_Cal_BattWorktime(void);


static uchar8 SV_PowerFlag;					///*��ǰ��Դ״̬��־*///

//static Str_Msg_Parameter Str_Msg_Parameter_PowerFalling;	///*����ȫ�ֵ���Ϣ�ṹ�壬���ڴ�ŵ��ȶ�ȡ����Ϣ������Ϣ*///



static uchar8 SV_Wakeup_Time_CNT;			///*3s���һ�����޺��⻽��*///
uchar8 SV_Wakeup_Flag;				///*�к����жϱ�־*///
//static uchar8 SV_Wakeup_Bit_CNT;			///*���⻽��1200���յ���λ������*///
//static uchar8 SV_Wakeup_CS;					///*�������ʱУ��Ĵ���*///
//static uchar8 SV_Wakeup_RecData;			///*�����յ���1�ֽ�*///
ulong32 SV_Wakeup_Data;				///*���⻽���յ������ݣ�68 11 04*///

//static uchar8 SV_CalibrateRC_State;			///*У׼RC����������*///
//static ulong32 SV_CalibrateRC;				///*1s���ѼĴ���*///

static ulong32 SV_LowPower_7Day;					///*ͣ��7���ʱ������Ϊ��λ�ļ�ʱ*///

static Str_LowPower_Type	Str_LowPower_KeyUp;		///*�Ϸ����ڵ͹����µ�״̬*///
static Str_LowPower_Type	Str_LowPower_KeyDown;	///*�·����ڵ͹����µ�״̬*///
Str_LowPower_Type	Str_LowPower_Infra;		///*�����ڵ͹����µ�״̬*///

static ushort16 SV_LowPower_RTC83min;					///*ͣ������£�RTC��Уÿ83min����һ��*///

uchar8 SV_ucEnterLowPowerTimer_UpdateFlag;
///***********************************************************************************///
///*Function������4M�������ĳ�ʼ��������У׼����RC��1s��ʱ��*///
///***********************************************************************************///
void SF_CalibrateRCTimerInit(void)
{
//	CalibrateRCTimerClock_EN;								///*ϵͳʱ���ṩ����ʱ�����޷�Ƶ=ϵͳʱ��*///
//	CalibrateRCTimer->CR1 = C_TIM_CR1_CLEAR;				///*���ƼĴ�������*///
//	CalibrateRCTimer->CR1 |= C_TIM_CR1_URS;					///*ֻ������Ų����ж�*///
//	CalibrateRCTimer->CR1 |= C_TIM_CR1_ARPE;
//	CalibrateRCTimer->CR2 = C_TIM_CR1_CLEAR;				///*���ƼĴ�������*///
//	CalibrateRCTimer->DIER &= C_TIM_UIE_DIS;				///*��ֹ�ж�*///
//	CalibrateRCTimer->SR &= C_TimerStatus_UIF_RESET;
//
//	CalibrateRCTimer->ARR = C_CalibrateRCTimerCounter;		///**///
//	CalibrateRCTimer->PSC = TIM_Prescaler_16000;			///*16*1000��Ƶ*///
//
//	CalibrateRCTimer->EGR = C_TIM_EGR_CLEAR;
//
//	CalibrateRCTimer->SR &= C_TimerStatus_UIF_RESET;
//	CalibrateRCTimer->CR1 |= C_TIM_CR1_URS;					///*ֻ������Ų����ж�*///
//	CalibrateRCTimer->CNT = 0;
//	CalibrateRCTimer->CR1 |= C_TimerCounter_EN;				///*��ʽ������ʱ����ʼ����*///
//	NVIC_DisableIRQ(CalibrateRCTimer_Interrupt);			///*�жϽ�ֹ*///
}
///***********************************************************************************///
///*Function������У׼RC�񵴵Ķ�ʱ��ֹͣ*///
///***********************************************************************************///
void SF_CalibrateRCTimer_Disable(void)
{
//	CalibrateRCTimer->CR1 = C_TIM_CR1_CLEAR;				///*���ƼĴ�������*///
//	CalibrateRCTimer->DIER &= C_TIM_UIE_DIS;				///*��ֹ�ж�*///
//	NVIC_DisableIRQ(CalibrateRCTimer_Interrupt);			///*�жϽ�ֹ*///
//	///*******************************************************///
//	CalibrateRCTimerClock_DIS;								///*ϵͳʱ�ӹر�*///
}

///************************************************************************///
///*����ԭ��:void Msg_CalibrateRC(Str_Msg_Parameter *P_Msg_Parameter)
///*��������:����У׼RC1s��ʱ����ʹ��
///*�������:P_Msg_Parameter: ͳһ��Str_Msg_Parameter�ͱ���
///*��Ϣ��Դ:SourceAddr= C_Msg_Dispatch,����
///*Ŀ����Ϣ:DerictAddr = C_Msg_CalibrateRC;Len = 0
///*�������:
///*���ز���:��
///*����ʱ��:ÿminУ׼һ��
///*��ע:
///************************************************************************///
void Msg_CalibrateRC(Str_Msg_Parameter *P_Msg_Parameter)
{
//	uchar8 V_ucBuffer[20];
//
//	PF_CopyDataBytes(P_Msg_Parameter->Parameter,V_ucBuffer,4);
//	if( (P_Msg_Parameter->DerictAddr != C_Msg_CalibrateRC) || (V_ucBuffer[0] != Pt_CalibrateRC) )
//	{
//		return;
//	}
//
//	///*������������:��������У׼�������ж�����*///
//	SV_CalibrateRC_State = 0x68;
}

///************************************************************************///
///*����ԭ��:void Msg_CalibrateRC(Str_Msg_Parameter *P_Msg_Parameter)
///*��������:У׼RC��
///*�������:P_Msg_Parameter: ͳһ��Str_Msg_Parameter�ͱ���
///*��Ϣ��Դ:SourceAddr= C_Msg_Dispatch,����
///*Ŀ����Ϣ:DerictAddr = C_Msg_CalibrateRC;Len = 0
///*�������:
///*���ز���:��
///*����ʱ��:ÿminУ׼һ��
///*��ע:
///************************************************************************///
void InF_CalibrateRC(void)
{
//	SV_CalibrateRC_State = 0;			///*У׼����������*///
//	SV_CalibrateRC = C_1sTimer;			///*��ST�Դ���RTC�����жϼĴ�����ʼֵ*///
//	SF_SoftRTCInit();					///*�ڲ���ʱ�����ã����ڶ�ʱ���ѣ�ÿ�뻽��һ��*///
//	SF_RTCWakeUpInit();
}

///**************************************************************///
///*Function��void InF_ExcuteMessage_PowerFalling(void)*///
///*Description������ʱ������Ϣ�����е���Ϣȡ������֪ͨ����ģ��*///
///*Input����*///
///*Output����*///
///*Calls��*///
///*Called By��*///
///*Influence��*///
///*Tips��*///
///*Others��*///
///**************************************************************///
void InF_ExcuteMessage_PowerFalling(void)
{
	//uchar8 temp;

	while(1)
	{
		if( C_Error == InF_Dealwith_MessageSqueue() )
		{
			break;
		}
	}
}

///***********************************************************************************///
///*Function���͹����º��⻽���ⲿ�ж����á����ⲿ�ж�ʹ��*///
///***********************************************************************************///
void SF_InfraWakeup_En(void)
{
//	IO_INFRARX->MODER &= INFRARX_IN_MODE;				///*����ģʽ*///
//	IO_INFRARX->PUPDR &= INFRARX_NOPUPD;				///*�ر�������*///
//	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
//
//	SYSCFG->InfraWakeup_ConfigRegister &= (~InfraWakeup_Configration_Select);
//	SYSCFG->InfraWakeup_ConfigRegister |= InfraWakeup_Configration_Select;
//
//	EXTI->IMR |= InfraWakeup_NoMask;
//	EXTI->RTSR &= ~InfraWakeup_Rising;					///*��ֹ�������ж�*///
//	EXTI->FTSR |= InfraWakeup_Falling;					///*�½����ж�*///
//	EXTI->PR |= InfraWakeup_Trigger;					///*���жϱ�־*///
//	NVIC_EnableIRQ(InfraWakeup_IRQn);					///*�ж�ʹ��*///
}

///***********************************************************************************///
///*Function���͹����º��⻽���ⲿ�ж����á�����ֹ*///
///***********************************************************************************///
void SF_InfraWakeup_Dis(void)
{
//	EXTI->IMR &= (~InfraWakeup_NoMask);
//	EXTI->PR |= InfraWakeup_Trigger;					///*���жϱ�־*///
//	NVIC_DisableIRQ(InfraWakeup_IRQn);					///*�жϽ�ֹ*///
}

/*******************************************************************************
����ԭ�ͣ� uchar8 InF_Read_LowpowerLive(void)
���������� �Ƿ��������͹����µ��¼����ϱ�����Ҫ��ͣ����ػ��߳��������е磻
���������
��������� ��
���ز����� C_OK��ͣ������е���߳��������е磻C_Error��������û�е粢�ҳ�������û�е�
����λ��:
��    ע��
*******************************************************************************/
uchar8 InF_Read_LowpowerLive(void)
{
    uchar8 V_ucBuffer[CLCap_Vol] = {0}, V_BattDataBuff[CLMeter_Work_State1 + 1] = {0}, V_EleCapacitorReadFlag = C_Error;
    uchar8 V_LowpowerLive = 0, V_ucMeterWorkReadFlag = C_Error;
    ushort16 V_usEleCapacitor = 0, V_usLen, V_usDataEncode;

/*�����ݲ��ȡͣ�绽�ѵ��״̬*/
    V_usLen = CLMeter_Work_State1;
    V_ucMeterWorkReadFlag = InF_Read_Data(CMeter_Work_State1, &V_BattDataBuff[0], &V_usLen, &V_usDataEncode);

/*�����ݲ��ȡ��������״̬*/
    V_usLen = CLCap_Vol;
	V_EleCapacitorReadFlag = InF_Read_Data(CCap_Vol, V_ucBuffer, &V_usLen, &V_usDataEncode);                         		/*�������ݵ�ѹֵ*/
    PF_Buffer2ToUshort16(V_ucBuffer, &V_usEleCapacitor);                                                    /*��ѹֵת��ushort16��ʽ*/

    if( ( V_ucMeterWorkReadFlag == C_OK ) && ( ( V_BattDataBuff[0] & 0x08 ) == 0 ) )                        /*ͣ������е�*/
    {
        V_LowpowerLive |= C_BattPower;
    }
    if( ( V_EleCapacitorReadFlag == C_OK ) && (V_usEleCapacitor > C_CapReport_LowerLimit ) )                /*�������ݴ���3V*/
    {
        V_LowpowerLive |= C_EleCapacitor;
    }

    return V_LowpowerLive;
}

///***********************************************************************************///
///*Function�������ж�*///
///*Description���ڵ����ж��������������־50�Σ���45������Ϊ����*///
///***********************************************************************************///
void PowerDown_IRQHandler(void)
{
	uchar8 V_CheckTimes = 0;
	uchar8 V_CheckCounter = 0;

	ANAC->SVDSIF|=0x00000003;	///*���жϱ�־*///
	if(((ANAC->SVDALM)&ANAC_SVDALM_SVDALM_B_ENABLE) == ANAC_SVDALM_SVDALM_B_DISABLE)///*����,�����ж���Ӧ��while���ʱ��
	{
//		SwitchOn_BackLight();	///*test
//		Set_PowerDown_Input();///*����Ϊ��ͨIO��

		while( V_CheckTimes < C_CheckPowerDownTimes )
		{
	    	V_CheckTimes++;

	    	if(((ANAC->SVDALM)&ANAC_SVDALM_SVDALM_B_ENABLE) == ANAC_SVDALM_SVDALM_B_DISABLE)
	    	{
	    		V_CheckCounter++;
				}
		}
		if( V_CheckCounter >= C_CheckPowerDownCounter )
		{
			///*��ͣ�绽�ѵ�Դ*///
    		DF_SwitchOn_WakeUpPower();
    		///*�򿪼���оƬ��Դ������6V����Ƿ��ж��򿪣����崦���ʱ����˵*///
    		DF_SwitchOn_EMeterIcPower();
    		///*��Flash��Դ*///
    		DF_SwitchOn_FlashPower();
    		///*�رճ��*///
				DF_SwitchOff_SuperCapCharge();
    		///*�������ݹ���*///
    		DF_SwitchOn_SuperCapPower();
		InF_Deactivation_7816_Esam();
		///*�ر���բ��:��ֹ�������к���ʱ��ϳ�ʱ����,��բ�Ƴ�ʱ�䲻Ϩ��*///
    		DF_SwitchOff_TripLed();
//		SwitchOff_BackLight();///*test
		}
	}
}

///***********************************************************************************///
///*Function����ǰ��Դ״̬*///
///***********************************************************************************///
uchar8 InF_ReadPowerState()
{
	if( (SV_PowerFlag != C_PowerOff) && (SV_PowerFlag != C_PowerFalling) && (SV_PowerFlag != C_PowerRising) )
	{
		SV_PowerFlag = C_PowerOn;
	}
	return SV_PowerFlag;
}

///**********************************************************************************///
///*Function����⵱ǰ��Դ״̬														*///
///*Description������Դ�Ƿ���磬�����ж�N�Σ�����M�ο��ߵ�����Ϊ����				*///
///*Input��powerflag = 	C_PowerOn�� ��ʾ�е��ʱ�����Ƿ����:�����50��,45�ε���Ϊ����*///
///*Input��			 = 	C_PowerOff����ʾ�����ʱ�����Ƿ�����:�����6��,4�ε���Ϊ���ڵ���*///
///*Output����ֵSV_PowerFlag�����ñ�������											*///
///*	C_PowerOn:     �����е�״̬													*///
///*	C_PowerFalling:��������														*///
///*	C_PowerOff:    ���ڵ���״̬													*///
///*	C_PowerRising: ��������														*///
///*Calls��																			*///
///*Called By��																		*///
///*Influence��																		*///
///*Tips��																			*///
///*Others��																		*///
///*Author:																			*///
///**********************************************************************************///
uchar8 SF_Check_PowerDown(uchar8 powerflag)
{
	uchar8 checktimes_threshold,checkcounter_threshold;
	uchar8 V_CheckTimes = 0;
	uchar8 V_CheckCounter = 0;
//	SwitchOn_Beep();///*test
//	Set_PowerDown_Input();///*����Ϊ��ͨIO��

	if( powerflag == C_PowerOn )
	{
		checktimes_threshold = C_CheckPowerDownTimes;
		checkcounter_threshold = C_CheckPowerDownCounter;
	}
	else
	{
		checktimes_threshold = C_CheckPowerOnTimes;
		checkcounter_threshold = C_CheckPowerOnCounter;
	}

	while( V_CheckTimes < checktimes_threshold )
	{
	    	V_CheckTimes++;

 	   	if( ((ANAC->SVDALM)&ANAC_SVDALM_SVDALM_B_ENABLE) == ANAC_SVDALM_SVDALM_B_DISABLE )///*���磬SVD�ڲ��˲���ĵ�ѹ����־
	    	{
	    		V_CheckCounter++;
		}
	}

	if( V_CheckCounter >= checkcounter_threshold )
	{
		if( SV_PowerFlag == C_PowerOn )
		{
			///*�رձ��⡢�򿪵�ء���Flash��Դ���򿪺�����յ�Դ*///
//			InF_SwithPeripherals(C_BackLight,C_Off);
//			DF_SwitchOn_WakeUpPower();
//    		DF_SwitchOn_EMeterIcPower();
//    		DF_SwitchOn_FlashPower();

			SV_PowerFlag = C_PowerFalling;		///*��Դ�����ر䣺��������*///
		}
		else
		{
			SV_PowerFlag = C_PowerOff;
		}
	}
	else
	{
		if( SV_PowerFlag == C_PowerOff )
		{
			SV_PowerFlag = C_PowerRising;		///*����*///
		}
		else
		{
			SV_PowerFlag = C_PowerOn;			///*��Դδ�����ر䣺δ��������*///
		}
//		DF_ConfigPowerDownInterrupt();///*����Ϊ�ж�
	}

	return SV_PowerFlag;
}

///**********************************************************************************///
///*Function���͹����¼���Ƿ�����   												*///
///*Description������Դ�Ƿ���磬�����ж�5�Σ�����4�ο��ߵ�����Ϊ����			    *///
///**********************************************************************************///
//uchar8 SF_Check_PowerDown(void)
//{
//	uchar8 V_CheckTimes = 0;
//	uchar8 V_CheckCounter = 0;
//
//	while( V_CheckTimes < 6 )
//	{
//    	V_CheckTimes++;
//
//    	if( DF_GetIOStatus_MainPower() == C_Invalid )
//    	{
//    		V_CheckCounter++;
//		}
//	}
//
//	if( V_CheckCounter >= 4 )
//	{
//		if( SV_PowerFlag == C_PowerOn )
//		{
//			SV_PowerFlag = C_PowerFalling;		///*��Դ�����ر䣺��������*///
//		}
//		else
//		{
//			SV_PowerFlag = C_PowerOff;
//		}
//	}
//	else
//	{
//		if( SV_PowerFlag == C_PowerOff )
//		{
//			SV_PowerFlag = C_PowerRising;		///*����*///
//		}
//		else
//		{
//			SV_PowerFlag = C_PowerOn;			///*��Դδ�����ر䣺δ��������*///
//		}
//	}
//	return SV_PowerFlag;
//}

///************************************************************************///
///*����ԭ��:uchar8 SF_KeyLock(void)*///
///*��������:������������:ÿ0.5s������һ��*///
///************************************************************************///
void SF_KeyLock(void)
{
	if( InF_GetPeripheralStatus(C_KeyUp) == C_Valid )
	{
		if( Str_LowPower_KeyUp.Times >= C_KeyLockCNT )
		{
			Str_LowPower_KeyUp.Wakeup_En = C_Disable;
		}
		else
		{
			Str_LowPower_KeyUp.Times++;
		}
	}
	else
	{
		Str_LowPower_KeyUp.Times = 0;
		Str_LowPower_KeyUp.Wakeup_En = C_Enable;
	}

	if( InF_GetPeripheralStatus(C_KeyDown) == C_Valid )
	{
		if( Str_LowPower_KeyDown.Times >= C_KeyLockCNT )
		{
			Str_LowPower_KeyDown.Wakeup_En = C_Disable;
		}
		else
		{
			Str_LowPower_KeyDown.Times++;
		}
	}
	else
	{
		Str_LowPower_KeyDown.Times = 0;
		Str_LowPower_KeyDown.Wakeup_En = C_Enable;
	}
}

/***************************************************************************************
����ԭ��: void SF_NeedToReport(uchar8 V_ReportFlag, uchar8 *V_ReportDataFramesNo)
��������: ����ϵ粻��1Сʱ���ߵ����ֱ�ӽ���ʽ���ϱ���������µ������ϱ�����Ϊ3���������͹��ĵ�ʱ���ǵ�һ֡��ô�Ͳ�������ֱ֡�ӷ��ͻ���������
�������: V_ReportFlag���Ƿ���磻V_ReportDataFramesNo���Ƿ��һ֡
�������: ��
���ز���:
����λ��:V_ReportDataFramesNo�������·������¼����óɲ��ǵ�һ֡
��    ע:
****************************************************************************************/
void SF_NeedToReport(uchar8 V_ReportFlag, uchar8 *V_ReportDataFramesNo)
{
    uchar8 V_Mode = C_ReportNull, V_PowerOffReportType = 0, V_MeterReportMode = C_MeterReportClose;
    uchar8 V_Return = C_Error;
	ushort16 V_DataLen = CLLossVolage_Report_Mode, V_usDataEncode;

    if(Inf_SatisfyPowerOnTime() == C_OK)                    /*�ϱ�1hour����*/
    {
        if(Inf_Event_REPORTONumGet() == 0)                  /*������·����ĵ���(�ϱ�����Ϊ0���������¸�ֵ3�Ρ�������ϱ�ʣ�����*/
        {
            if(V_ReportFlag  == C_Happen_EventState )       /*�����¼,����ǵ��綯��*/
            {
				V_DataLen = CLPowerOff_Report_Mode;
                V_Return = InF_Read_Data(CPowerOff_Report_Mode, &V_Mode, &V_DataLen , &V_usDataEncode);     /*�������ϱ�ģʽ���Ƿ���*/
                if(V_Return == C_OK)
                {
                    if( ( V_Mode == C_ReportHP ) || ( V_Mode == C_ReportAll ) )		/*���翪���ϱ�*/
                    {
                        V_DataLen = CLReport_Type;
                        V_Return = InF_Read_Data( CPowerOff_Report_Type, &V_PowerOffReportType, &V_DataLen, &V_usDataEncode);   /*���������ϱ�*/

                        if(V_Return == C_OK)
                        {
                            if(V_PowerOffReportType  == C_ActiveReportType )
                            {
                                if(InF_ValtageType() == C_OK)       /*��ѹ����Ϊֱ�ӽ���ʽ*/
                                {
                                    V_MeterReportMode = Inf_MeterReportOpen(C_PowerOff, C_FirstNo);     /*���ܱ������ϱ�����*/
                                    if(V_MeterReportMode == C_MeterReportOpen)
                                    {
                                        Inf_Event_REPORTONumDeal(C_NewReportFlag);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    else
    {
        Inf_Event_REPORTONumDeal(0);            /*�����������ϱ�û�з������͹��ģ�Ҳ���㲻���ϱ����淶Ҫ��*/
        Inf_Clear_PowerOffShutAcReportTime();   /*����ʱ����1Сʱ���緢��ʱ���㣬�����1Сʱ�Ĳ�����ȵ��������������*/
    }

    if(Inf_Event_REPORTONumGet() < C_ActiveReportMaxNum)      /*��������˲��д���ϱ�����ôֱ�ӷ�������֡��������֡*/
    {
        (*V_ReportDataFramesNo)++;
    }
}
/***************************************************************************************
����ԭ��: uchar8 InF_CheckPowerAndExcute(void)
��������: ����Ƿ���磬������磬���е��紦�����е͹���ǰ��Ĵ�����û�е���ֱ���˳�
�������: ��
�������: ��
���ز���: �����ˣ�����C_Error��û�е��磬����C_OK
����λ��:
��    ע:
****************************************************************************************/
uchar8 InF_CheckPowerAndExcute(void)
{
	uchar8 V_DataBuff[20];
	ushort16 V_Delay;
	uchar8 wakeupbattflag;	     /*���޻��ѵ�ر�־*/
	uchar8 v_keystatus, v_keytimes;
	uchar8 checkpower;
	uchar8 V_InfrarxFlag = C_Disable;
    uchar8 V_ReportDataFramesNo = C_FirstNo , V_ReportFlag = C_NULL; /*ͣ���ϱ��õ�����ʱ�������Ƿ��һ֡���Ƿ���Ҫ�ϱ�*/
    ushort16 V_AddNum = 0;
    uchar8 V_PowerStatus = 0;
	ushort16 V_usLen, V_usDataEncode;

	checkpower = SF_Check_PowerDown( C_PowerOn );

#if 0   /*test*/
	SwitchOn_TripLed();
#endif

	if( (checkpower == C_PowerOn) || (checkpower == C_PowerRising) )
	{
		/*�ر�ͣ�绽�ѵ�Դ*/
		DF_SwitchOff_WakeUpPower();

		/*�رռ���оƬ��Դ*/
		DF_SwitchOff_EMeterIcPower();

		/*�ر�Flash��Դ*/
		DF_SwitchOff_FlashPower();

		DF_SwitchOff_LCDPower();

        /*������������ʹ�ã��������������*/
		SwitchOn_KEYPU_PowerOn();

#if 0	/*test*/
		SwitchOff_TripLed();
#endif

		return C_PowerOn;
	}

#if 0	/*test*/
	SwitchOn_TripLed();
#endif

	/**********************************************************/
	/*һ���жϵ����磬������ֹȫ���ж�(21�淶��Ҫ���������ϱ����������ﲻ��ȫ���ж�)*/
//	__disable_irq();

    	/*�ر���͹����޹ص��ж�*/
	NVIC_DisableIRQ( Esam_IRQn );
	NVIC_DisableIRQ( First485_IRQn );
	NVIC_DisableIRQ( Second485_IRQn );
	NVIC_DisableIRQ( Card_IRQn );
	NVIC_DisableIRQ( Infra_IRQn );
	NVIC_DisableIRQ( LowpowerTimer_Interrupt );
	NVIC_DisableIRQ( PowerDown_IRQn );

	/*ͣ�簴���������費ʹ�ã����߿�©�����*/
	SwitchOff_KEYPU_PowerOff();

	/*�򿪻��ѵ�Դ*/
	DF_SwitchOn_WakeUpPower();

	/*��Flash��Դ*/
	DF_SwitchOn_FlashPower();
	/*����г������ݣ���򿪳������ݽ��й���*/

#if 1
	DF_SwitchOff_SuperCapCharge();
	DF_SwitchOn_SuperCapPower();
#endif

	/*�رձ���*/
	InF_SwithPeripherals(C_BackLight, C_Off);

	InF_SwithPeripherals(C_TripLed, C_Off);

#if 0	/*test*/
	 SwitchOn_BackLight();
#endif

	/*�ر�Һ������*/
	InF_SwitchOffLCD();

#if 0	/*test*/
	SwitchOff_TripLed();
#endif

	InF_Deactivation_7816_Esam();

	/*�ر�ADCת��*/
	InF_ADC_OFF();

	/*��ֹ6V��ط��ۻ��ŵ�*/
	DF_SwitchOff_PreventBlunt();

	/*�ر�Һ����ʾ��Դ*/
	DF_SwitchOff_LCDPower();

	/*������Ϣ����:�����������Ϣȡ�ղ�������ȥ*/
	InF_ExcuteMessage_PowerFalling();
	SV_PowerFlag = C_PowerOff;

	/**********************************************************/
	/*д���͹���ʱ��*/
	SV_ucEnterLowPowerTimer_UpdateFlag = C_EnterLowPowerTimer_NoUpdate;
	if( InF_GetPowerOnTimer() == C_OK )
	{	/*����ϵ粻��3s,����ΪƵ�����µ�,�����½��͹���ʱ��;�������*/
		/*��������Ŀ����Ϊ�˽��̨���ϵ������,�п��ܻᶶ��,���ĳЩ�¼���Ϊʱ�䶪ʧ����¼���ʧ*/
		SF_WriteLopwerTime(CEnter_LowPower_Time, CLEnter_LowPower_Time);
		SV_ucEnterLowPowerTimer_UpdateFlag = C_EnterLowPowerTimer_Update;
	}
#if 0
	SwitchOff_BackLight();
#endif
	/**********************************************************/
	/*�����Դ�쳣�¼���¼*/
    V_PowerStatus = InF_Read_LowpowerLive();
    if( V_PowerStatus != C_NoPower )      /*��ͣ����ػ��߳������ݴ���3V*/
    {
        if( InF_GetPowerOnTimer() == C_OK )         /*�ϵ���3s�ٵ������*/
        {
			/*�򿪼���оƬ��Դ�����ڵ�Դ�쳣�¼���¼*/
			DF_SwitchOn_EMeterIcPower();

#if 0	/*test*/
			SwitchOn_BackLight();
#endif
			/*��ʱ1s*/
			for(V_Delay = 0; V_Delay < 1000; V_Delay++)
			{
				InF_Delay_us(1000);
			}

#if 0	/*test*/
			SwitchOff_BackLight();
#endif

			if( SF_Check_PowerDown( C_PowerOff ) == C_PowerOff )      /*��ǰ���ڵ���״̬������Դ�쳣��¼�������¼*/
            {
                if( ( InF_PowerDownReadData_MeterIC() == C_OK )         /*�͹����¶�ȡ�������������¼��ж�*/
                 && ( ( V_PowerStatus == C_BattPower ) || ( V_PowerStatus == C_BothBattAndCapacitor ) ) )/*ͣ������е� ���� ͣ����غͳ������ݶ��е�*/
                {
                    Inf_PowerAbnormal();                                /*��Դ�쳣��¼*/
                }
                else
                {
                    ;                                                   /*������Դ�쳣*/
                }

                V_ReportFlag =	Inf_LowpowerPowerFail_No6VBat();		/*�����¼*/
                SF_NeedToReport(V_ReportFlag, &V_ReportDataFramesNo);
            }
		}
        else
        {
            ;                                                           /*������Դ�쳣�͵����¼*/
        }
	}

	SV_PowerFlag = C_PowerOff;
	MeterIC_Reset();				/*��λ����оƬ:��ֹ��Vcc,�Ӷ����׹رռ���оƬ*/
	DF_SwitchOff_EMeterIcPower();
#if 0
	SF_ClrPowerOnTimer();
#endif
	InF_ClearHexVarregtype_MeterIC(C_ClearCurrData);

	/**********************************************************/
	/*������Դʧ���¼*///
	Inf_LowpowerACPowerFail();

	/**********************************************************/
	InF_LowPower_IR_Inti();
	InF_LowPower_DemandInit();

	/**********************************************************/
	InF_SwitchOffLCD();

	/*�رյ�Դ*/
	DF_SwitchOff_FlashPower();
	DF_SwitchOff_InfrarxPower();

#if 0
	DF_SwitchOff_SuperCapPower();
#endif

	DF_SwitchOff_LCDPower();

	/**********************************************************/
    if( ( InF_GetPowerOnTimer() == C_OK )	&& ( V_PowerStatus != C_NoPower ) )  /*��ͣ����ػ��߳������ݴ���3V*//*�ϵ���3s�ٵ������*/
    {
/*�͹����µ����ϱ�����֡����*/
        Inf_ClearPowerDownTime();
        if(Inf_Event_REPORTONumGet() != 0 )                                     /*��Ҫ�ϱ�*/
        {
 //       	InF_WatchDog_Init();
            do
            {
                if( ( Inf_Comm_GetModuleCommuniFlag() == C_NoCommunication ) && ( Inf_Comm_REPORTFlag() == C_ReportNULL ) )   /*���ͨ��ģ�����*/
                {
                   break;
                }
				InF_Delay_us(10000);                                        /*��ʱ10mS*/

                if(V_AddNum > C_HardDelay_100 * 1)                     /*�������û�������˳�����ѭ��3��+����1�룬ǿ���˳�*/
                {
                    break;
                }
				else
				{
					V_AddNum++;
				}
            }while(Inf_PowerDownTime() <= ( C_Interval_1000ms * 1 ) );           /*1S֮�����Ƿ���*/
            V_AddNum = 0;
            Inf_ClearPowerDownTime();
            do
            {
                if(Inf_Event_REPORTONumGet() == 0 )
                {
                    InF_Delay_us(1000000);                                        /*��ʱ1S*/
                    break;
                }
                if( ( Inf_PowerDownTime() % C_Interval_1000ms ) == 0 )
                {
                    InF_Delay_us(10000);                                        /*��ʱ10mS*/

                    if(V_AddNum > C_HardDelay_100 * 4)                     /*�������û�������˳�����ѭ��3��+����1�룬ǿ���˳�*/
                    {
                        break;
                    }
					else
					{
                    	V_AddNum++;
					}
                    InF_InitComm(C_Module);
                    Inf_EventTypeCommReport(C_PowerOff, V_ReportDataFramesNo);    /*����֡��֯����*/
                    V_ReportDataFramesNo++;
                }
            }while(Inf_PowerDownTime() <= ( C_Interval_1000ms * 3 ) );           /*3S֮�����Ƿ���Ӧ��֡*/
        }
    }

	SF_ClrPowerOnTimer();		/*�ϵ���3�붨ʱ���ŵ��ϱ�֮��*/

    DF_SwitchOff_SuperCapPower();
	/**********************************************************/
	/*�����⻽��������������������(�Ϸ����·�)������͹��ĺ�ļ�ʱ�������ۼӼ�ʱ��(�����ۼƷ�����)����*/
	SF_EnterLowPower();

	/**********************************************************/
	InF_TickTimerStop();
	/*InF_BackUpBaseTimerStop();*/
	/**********************************************************/
	/*���͹���ǰˢ��һ�ε������״̬��4/5/6/�Լ�7�����¼���¼��ص�״̬*/
	Inf_LowPowerMeterStatus();

	/*�ر���͹����޹ص��ж�*/
	NVIC_DisableIRQ( Esam_IRQn );
	NVIC_DisableIRQ( First485_IRQn );
	NVIC_DisableIRQ( Second485_IRQn );
	NVIC_DisableIRQ( Card_IRQn );
	NVIC_DisableIRQ( Infra_IRQn );
	NVIC_DisableIRQ( TickTimer_Interrupt );
	NVIC_DisableIRQ( LowpowerTimer_Interrupt );
	NVIC_DisableIRQ( PowerDown_IRQn );

	SF_SoftRTCInit();			/*�ڲ���ʱ�����ã����ڶ�ʱ���ѣ�ÿ�뻽��һ��*/
	SF_RTCWakeUpInit();

#if 0
	IWDT->IWDTCFG |= 0x00000004;
#endif

	__enable_irq();

	/**********************************************************/
Lowpower_Sleep:

	if(C_Cap_WhetherUsed == C_Cap_WhetherUsed_En)
    {
		SF_IOSetupPowerOff_UsedCAP();
    }
    else
    {
		SF_IOSetupPowerOff();
    }

	SF_PeriSetupPowerOff();

	SF_SystemClockInPowerOff();

	/*�忴�Ź���ʱ��,��ι��*/
	InF_ClrWatchDogTimer();
	FeedWatchDog();

#if 0   /*test*/
	goto Lowpower_Sleep;
#endif

	/*���Ѻ��л�ϵͳʱ��Ϊ2M*/
	/**********************************************************/
	/*ÿs����һ�Σ����м�ʱ*/

#if 0   /*test*/
	SwitchOn_Beep();
#endif

	Str_LowPower_Infra.WakeupState = C_Disable;
	if( SV_LowPower_7Day < C_InfraWakeup_7Day )
	{
		SV_LowPower_7Day++;
		Str_LowPower_Infra.Wakeup_En = C_Enable;
	}
	else
	{
		Str_LowPower_Infra.Wakeup_En = C_Disable;
	}

	SV_LowPower_RTC83min++;		/*�͹���RTCʱ�ӵ�У����ʱ����1sΪ������λ*/

	if( SV_LowPower_RTC83min >= C_LowPower_RTC83min )
	{
		SV_LowPower_RTC83min = 0;

#if 0	/*test*/
		SwitchOn_Beep();		/*test 27ms*/
#endif

		InF_TempAdc_CmpAndJec();

#if 0	/*test*/
		SwitchOff_Beep();
#endif

	}

	/**********************************************************/
	if( !(RCC->PERCLKCON1 & RCC_PERRCCCON1_PDCCKEN_ON) )	/*IO��ʱ��ʹ��*/
	{
		RCC->PERCLKCON1 |= RCC_PERRCCCON1_PDCCKEN_ON;
	}

#if 0
/*test*/
	if( (IO_MCUSECOND->MODER & MCUSECOND_ANALOG_MODE) != MCUSECOND_SELECT_AF)
	{
		IO_MCUSECOND->MODER &= MCUSECOND_IN_MODE;
		IO_MCUSECOND->MODER |= MCUSECOND_SELECT_AF;
	}
	if( (IO_MCUSECOND->INEN & MCUSECOND_IN_On) == MCUSECOND_IN_On)
	{
		IO_MCUSECOND->INEN &= MCUSECOND_IN_Off;
	}
	if( (IO_MCUSECOND->PUPDR & MCUSECOND_PULLUP) == MCUSECOND_PULLUP)
	{
		IO_MCUSECOND->PUPDR &= MCUSECOND_NOPUPD;
	}
	if( (IO_MCUSECOND->OTYPER & MCUSECOND_OUTPUT_OD) != MCUSECOND_OUTPUT_OD)
	{
		IO_SECOND->OTYPER |= MCUSECOND_OUTPUT_OD;
	}
	if( (IO_MCUSECOND->OTYPER & MCUSECOND_OUTPUT_OD) != MCUSECOND_OUTPUT_OD)
	{
		IO_SECOND->OTYPER |= MCUSECOND_OUTPUT_OD;
	}

	GPIO->FOUTSEL = 0x00000002;
   	SwitchOn_BackLight();	/*test*/
	Set_PowerDown_Input();
	if( SF_Check_PowerDown( C_PowerOff ) == C_PowerRising )		/*�ж��Ƿ�����*/
	{
		goto Lowpower_Exit;
	}
#endif

	checkpower = SF_Check_PowerDown( C_PowerOff );

#if 0    /*test*/
	InF_Delay_us(1000);
#endif

	if( (checkpower == C_PowerOn) || (checkpower == C_PowerRising) )
	{
		goto Lowpower_Exit;
	}

	/**********************************************************/
	/*�ж��Ƿ���ͣ�����*/
	wakeupbattflag = C_Disable;			/*������Ϊ�޻��ѵ��*/
	Set_WakeupBatt_Input();

	if( Read_WakeupBatt() )
	{
		wakeupbattflag = C_Enable;		/*����Ϊ�ߣ���Ϊ�е��*/
        DF_SwitchOn_WakeUpPower();      /*��6V��أ�����Ϊ�������*/
	}
    else
    {
        DF_SwitchOn_WakeUpPower_NoBatter();     /*û��6V��أ����͹��ģ�����Ϊ��©�����*/
    }

#if 0    /*test*/
	wakeupbattflag = C_Disable;
#endif

	/**********************************************************/
	/*���û�л��ѵ�أ����ܻ��ѡ�����ȫʧѹ/�����¼����������Ǽ�¼*/
	if( wakeupbattflag != C_Enable )
	{
		SV_Wakeup_Time_CNT = 0;			/*3s���һ�����޺��⻽��*/
        /****ɽ��Ҫ��ͣ����ȫʧѹ/ͣ���¼��������Ǽ�¼***/
		/**********************************************************/
		/*���������Ǽ�¼:*///
		SF_ClrShutTime();				/*�尴������ʱ��*/
		SET_KEYOPENCOVER_INPUT();
		SET_KEYOPENTERMINAL_INPUT();
		Inf_LowpowerOpenCoverState(C_OpenTerminalCoverEventNo);
		Inf_LowpowerOpenCoverState(C_OpenMeterCoverEventNo);
#if 0
		/**********************************************************/
		/*Ȼ����ȫʧѹ/ͣ���¼��ж�,ɽ������*///
		if( SV_LowPower_7Day == C_AllLossTime )
		{
			Inf_LowpowerPowerFail_No6VBat();		/*�����¼*/
		}
#endif
		/**********************************************************/
		goto Lowpower_Sleep;
	}
	else
	{
		/**********************************************************/
		/*���������Ǽ�¼:*/
		SF_ClrShutTime();				/*�尴������ʱ��*/
		SET_KEYOPENCOVER_INPUT();
		SET_KEYOPENTERMINAL_INPUT();
		Inf_LowpowerOpenCoverState(C_OpenTerminalCoverEventNo);
		Inf_LowpowerOpenCoverState(C_OpenMeterCoverEventNo);

		/**********************************************************/
		/*Ȼ����ȫʧѹ/ͣ���¼��ж�*/
		if( SV_LowPower_7Day == C_AllLossPrepare )
        {
			/*������оƬ��Դ*/
			DF_SwitchOn_EMeterIcPower();

#if 0	/*test*/
			SwitchOn_BackLight();
#endif

            /*��ʱ100msд��У������*/
			InF_Delay_us(50000);	/*���Ѻ�����8M*/

#if 0	/*test*/
			SwitchOff_BackLight();
#endif
			InF_PowerDownInitial_MeterIC();
		}

		if( SV_LowPower_7Day == C_AllLossTime )
		{
			if( InF_PowerDownReadData_MeterIC() == C_OK )
			{
#if 0
				Inf_LowpowerPowerFail();		    /*�����¼*/
#endif

				Inf_LowpowerTotalVoltagelose();	    /*ȫʧѹ*/
				InF_ClearHexVarregtype_MeterIC(C_ClearCurrData);
			}

			DF_SwitchOff_EMeterIcPower();	/*�رռ���оƬ��Դ*/
			MeterIC_Reset();				/*��λ����оƬ:��ֹ��Vcc*/
		}

		if( SV_LowPower_7Day > C_AllLossTime )
		{
			DF_SwitchOff_EMeterIcPower();	/*ȷ���رռ���оƬ��Դ*/
		}
		/**********************************************************/

		/**********************************************************/
		/*������⻽��:���ȿ���Դ��ʹ���ⲿ�ж�*/
		SV_Wakeup_Flag = 0;
		SV_Wakeup_Data = 0;					/*���⻽���յ����������㣺68 11 04*/
		Str_LowPower_Infra.WakeupState = C_Disable;

		if( Str_LowPower_Infra.Wakeup_En == C_Enable )
		{
			SV_Wakeup_Time_CNT++;
			if( SV_Wakeup_Time_CNT >= C_InfraWakeup_Interval )	    /*����Ƿ�3sһ�εĺ��⻽���ж�*/
			{
				/*�򿪺�����յ�Դ*/
				DF_SwitchOn_InfrarxPower();
				V_InfrarxFlag = C_Enable;
				SV_Wakeup_Time_CNT = 0;

				/*ʹ�ܺ�����տ����ⲿ�ж�*/
				SF_InfarWakeupTimerInit();  /*�͹��ĺ��⴮������*/
			}
		}

		/**********************************************************/
		/*Ȼ������������:�Ϸ���/�·�������*/
		SET_KEYUP_INPUT();
		SET_KEYDOWN_INPUT();
		v_keytimes = 0;

		do
		{
			v_keystatus = DF_GetIOStatus( C_KeyUp );
			v_keytimes++;
		}while( (v_keystatus == C_Valid) && (v_keytimes < (C_CheckKeyTimes + 1)) );

		if( v_keytimes >= C_CheckKeyTimes )
		{
			if( Str_LowPower_KeyUp.Wakeup_En == C_Enable )
			{
				goto Lowpower_Wakeup;
			}
		}
		else
		{
			Str_LowPower_KeyUp.Wakeup_En = C_Enable;	/*�жϵ��ް���������*/
		}

		v_keytimes = 0;
		do
		{
			v_keystatus = DF_GetIOStatus( C_KeyDown );
			v_keytimes++;
		}while( (v_keystatus == C_Valid) && (v_keytimes < (C_CheckKeyTimes + 1)) );

		if( v_keytimes >= C_CheckKeyTimes )
		{
			if( Str_LowPower_KeyDown.Wakeup_En == C_Enable )
			{
				goto Lowpower_Wakeup;
			}
		}
		else
		{
			Str_LowPower_KeyDown.Wakeup_En = C_Enable;	    /*�жϵ��ް���������*/
		}

		/**********************************************************/
		if( Str_LowPower_Infra.Wakeup_En == C_Enable )
		{
			if(C_Enable == V_InfrarxFlag)     /*�����Դ��*/
			{
				V_InfrarxFlag = C_Disable;

#if 0    /*test*/
                SwitchOn_Beep();
#endif

                /*��ʱ�ȴ�30ms*/
                for(V_Delay = 0; V_Delay < 25000; V_Delay++)		/*@2.097MHz*/
                {
                    __NOP();
                }

#if 0    /*test*/
                SwitchOff_Beep();
#endif

                /*�ж��Ƿ��к����ж��ź�*/
                /*����У��ȴ�������ɣ�û�У��رպ�����յ�Դ����������*/
                if( SV_Wakeup_Flag == C_InfraWakeup_Flag )      /*�к����ж��źţ������ʱ200ms(ʵ��198ms)*/
                {
                    for(V_Delay = 0; V_Delay < 10200; V_Delay++)		/*@2.097MHz*/
                    {
                        if ( ( SV_Wakeup_Data == 0x00681104 )
                          || ( SV_Wakeup_Data == 0x00110468 )
                          || ( SV_Wakeup_Data == 0x00046811 ) )
                        {
                            break;
                        }
                    }

                    if ( ( SV_Wakeup_Data == 0x00681104 )
                      || ( SV_Wakeup_Data == 0x00110468 )
                      || ( SV_Wakeup_Data == 0x00046811 ) )
                    {
                        SV_Wakeup_Data = 0;
                        SV_Wakeup_Flag = 0;

                        /*�رպ�����յ�Դ����ֹ�����жϡ���ֹ����ʱ��*/
                        DF_SwitchOff_InfrarxPower();
                        SF_InfraWakeup_Dis();
                        SF_InfarWakeupTimer_Disable();

                        goto Lowpower_Wakeup;
                    }
                }
			}
		}

#if 0
		else	/*�޺����ж��ź�*/
#endif

		{
			SV_Wakeup_Flag = 0;
			SV_Wakeup_Data = 0;

			/*�رպ�����յ�Դ����ֹ�����жϡ���ֹ����ʱ��*/
			DF_SwitchOff_InfrarxPower();
			SF_InfraWakeup_Dis();
			SF_InfarWakeupTimer_Disable();
		}

		/**********************************************************/
		goto Lowpower_Sleep;
	}

/*���ܱ�����*/
Lowpower_Wakeup:

	Str_LowPower_Infra.WakeupState = C_Enable;      /*����ͨ���ж���*/

	if( RCC->SYSCLKSEL != 0x00000000 )     /*���Ѻ�����8M*/
	{
		RCC->SYSCLKSEL = 0x00000000;
	}

	SF_InfraWakeup_Dis();
	SF_InfarWakeupTimer_Disable();
	InF_Delay_us(500);					/*��Ϊʱ��Դ��Լ2������˸ú�����ʱԼ1ms*/
	SF_LowpowerTimerStart();			/*���û����ڼ�Ļ�������:��Ϊ��������ϵ��ʵ��Լ4.998ms*/

#if 0   /*test*/
	if((IO_MCUSECOND->MODER & MCUSECOND_ANALOG_MODE) != MCUSECOND_SELECT_AF)
	{
		IO_MCUSECOND->MODER &= MCUSECOND_IN_MODE;
		IO_MCUSECOND->MODER |= MCUSECOND_SELECT_AF;
	}
	if((IO_MCUSECOND->INEN & MCUSECOND_IN_On) == MCUSECOND_IN_On)
	{
		IO_MCUSECOND->INEN &= MCUSECOND_IN_Off;
	}
	if((IO_MCUSECOND->PUPDR & MCUSECOND_PULLUP) == MCUSECOND_PULLUP)
	{
		IO_MCUSECOND->PUPDR &= MCUSECOND_NOPUPD;
	}
	if((IO_MCUSECOND->OTYPER & MCUSECOND_OUTPUT_OD) != MCUSECOND_OUTPUT_OD)
	{
		IO_SECOND->OTYPER |= MCUSECOND_OUTPUT_OD;
	}
	if((IO_MCUSECOND->OTYPER & MCUSECOND_OUTPUT_OD) != MCUSECOND_OUTPUT_OD)
	{
		IO_SECOND->OTYPER |= MCUSECOND_OUTPUT_OD;
	}
	GPIO->FOUTSEL = 0x00000002;
	NVIC_DisableIRQ(RTC_WKUP_IRQn);			/*���Ѻ��ֹ��RTC��ʱ�ж�*/
#endif

	/*��Flash��Դ��LCD��Դ*/		/*�������ڳ���ִ��ʱ��Ĳ���*/
	DF_SwitchOn_LCDPower();			/*��Һ����ʾ��Դ*/

#if 0   /*test*/
    SwitchOn_BackLight();
#endif

	DF_SwitchOn_FlashPower();
	DF_SwitchOn_InfrarxPower();
	InF_Delay_us(1000);

#if 0   /*test*/
    SwitchOff_BackLight();
#endif

	/*��ʼ��LCD����оƬ:ֱ�ӵ�InF*/
	InF_InitLCD();

#if 0   /*test*/
    SwitchOn_BackLight();
#endif

	InF_Delay_us(1000);

#if 0   /*test*/
        SwitchOff_BackLight();
#endif

	InF_InitLCD();
	/*�͹����³�ʼ����ʾ*/
	InF_Display_WakeUpInit();
	InF_InitTimer();

	/*��ʼ������ͨ��*/
	InF_InitComm(C_IR);

	/*��J-Tag��������Ϊʹ��*/
	InF_JTagEnable();

    /**********************************************************/
    /*���µ������״̬��3�еĹ��緽ʽ*/
	V_usLen = CLMeter_Work_State3;
	InF_Read_Data(CMeter_Work_State3, &V_DataBuff[0], &V_usLen, &V_usDataEncode);

	V_DataBuff[0] &= C_PowerSupplyInit;
	V_DataBuff[0] |= C_PowerSupply;
	InF_Write_Data(C_Msg_Dispatch, CMeter_Work_State3, &V_DataBuff[0], CLMeter_Work_State3, C_W_SafeFlag);

	/*Ȼ����ȫʧѹ/ͣ���¼��ж�*/
	while(1)
	{

#if 0
        if( SF_Check_PowerDown( C_PowerOn ) == C_PowerRising )
        {
            goto Lowpower_Exit;
        }
#endif

		checkpower = SF_Check_PowerDown( C_PowerOn );

#if 0   /*test*/
		SwitchOn_BackLight();
#endif

		if( (checkpower == C_PowerOn) || (checkpower == C_PowerRising) )
		{
			goto Lowpower_Exit;
		}

		/*�����Ź�*/
		InF_ClrWatchDogTimer();

		/**********************************************************/
		/*�ж��Ƿ���ͣ�����*/
		wakeupbattflag = C_Disable;			/*������Ϊ�޻��ѵ��*/
		Set_WakeupBatt_Input();

		if( Read_WakeupBatt() != WAKEBATT_SELECT )
		{
			/*�ر�Һ����Flash��Դ��LCD��Դ������6V���*/
			InF_SwitchOffLCD();
			DF_SwitchOff_FlashPower();
			DF_SwitchOff_InfrarxPower();
			DF_SwitchOff_LCDPower();	            /*�ر�Һ����ʾ��Դ*/
            DF_SwitchOff_WakeUpPower_NoBatter();    /*û��6V�������Ϊ��©�����*/
			goto Lowpower_Sleep;
		}
		/**********************************************************/

		/**********************************************************/
		/*ÿ��ѭ������һ��5ms�¼����ú����н���ʱ��ص���Ϣ����*/
		InF_DealWith5ms();

		/*�жϻ���ʱ���Ƿ�*/
		if( InF_GetPowerOffDisplayState() != C_ContinueReceive )
		{
			/*����ʱ�䵽��ֹͣ�͹���5ms��ʱ������͹���*/
			SF_LowpowerTimerStop();

			/*�ر�Һ����Flash��Դ��LCD��Դ*/
			InF_SwitchOffLCD();
			DF_SwitchOff_FlashPower();
			DF_SwitchOff_InfrarxPower();
			DF_SwitchOff_LCDPower();			/*�ر�Һ����ʾ��Դ*/
			goto Lowpower_Sleep;
		}

		/**********************************************************/
		/*�����ڽ��������ڳ�ʼ�����ж����ñ�־�������̸��ݱ�־����Ϣ*/
		InF_Dispatch_CommInterruptMessage();

		/**********************************************************/
		/*������Ϣ����*/
		InF_Dealwith_MessageSqueue();
	}
	/**********************************************************/

Lowpower_Exit:			/*�˳��͹��ĳ���*/

#if 0   /*test*/
	SwitchOn_Beep();
#endif

	SF_LowpowerTimerStop();
	NVIC_DisableIRQ( RTC_IRQn );

	/**********************************************************/
	/*д���ݲ�����͹���ʱ��*/
	SF_WriteLopwerTime(CExit_LowPower_Time, CLExit_LowPower_Time);

	/**********************************************************/
	/*д�ڲ���ع���ʱ�䣺�����͹���ʱ���ֵ����ԭ��������*/
	if( InF_GetEnterLowPowerTimerUpdateFlag() == C_OK )
	{
		SF_Cal_BattWorktime();
	}
	/**********************************************************/

#if 0    /*test*/
	SwitchOff_Beep();
#endif

	RCC->SOFTRST = 0x5C5CAABB;

	return C_PowerRising;
}
/************************************************************************
*����ԭ��:void SF_WriteLopwerTime(void)
*��������:�͹�����д�����͹���ʱ��
************************************************************************/
void SF_WriteLopwerTime(ulong32 v_di,uchar8 v_lenbuf)
{
	uchar8 V_DataBuff[10];
	ushort16 V_usLen, V_usDataEncode;
	/*���ȶ�ȡ��ǰʱ��*/
	V_usLen = CLDate_Time;
	InF_Read_Data(CDate_Time, &V_DataBuff[0], &V_usLen, &V_usDataEncode);
	if( PF_DataTimeActive_698(&V_DataBuff[0], C_DT_Start_ss, CLDate_Time) != C_OK )
	{
		memset(&V_DataBuff[0], 0x00, CLDate_Time);
	}
	InF_Write_Data(C_Msg_Dispatch,v_di, &V_DataBuff[0], v_lenbuf, C_W_SafeFlag);
}

///************************************************************************///
///*����ԭ��:void SF_WriteBattWorkTime(void)
///*��������:д��ع���ʱ��
///************************************************************************///
void SF_WriteBattWorkTime(void)
{

}
/*******************************************************************************
��ý����͹���ʱ����±�־���Ѹ��·���C_OK��δ���·���C_Error
*******************************************************************************/
uchar8 InF_GetEnterLowPowerTimerUpdateFlag(void)
{
	if(SV_ucEnterLowPowerTimer_UpdateFlag == C_EnterLowPowerTimer_Update)
	{
		return C_OK;
	}
	else
	{
		return C_Error;
	}
}
///************************************************************************///
///*����ԭ��:void SF_PeriSetupPowerOff(void)
///*��������:�͹����µ�Ƭ�����������
///*����ʱ��:�ڵ͹�����ѭ���У�ÿ��ѭ��������
///************************************************************************///
void SF_PeriSetupPowerOff(void)
{
	if(UART0->RXSTA!=0x00000000)
	{
		UART0->RXSTA&= 0xFFFFFFFE;
	}
	if(UART0->TXSTA!=0x00000002)
	{
		UART0->TXSTA &= 0xFFFFFF87;
	}
	if(UART1->RXSTA!=0x00000000)
	{
		UART1->RXSTA&= 0xFFFFFFFE;
	}
	if(UART1->TXSTA!=0x00000002)
	{
		UART1->TXSTA &= 0xFFFFFF87;
	}
	if(UART2->RXSTA!=0x00000000)
	{
		UART2->RXSTA&= 0xFFFFFFFE;
	}
	if(UART2->TXSTA!=0x00000002)
	{
		UART2->TXSTA &= 0xFFFFFF87;
	}
	if(UART3->RXSTA!=0x00000000)
	{
		UART3->RXSTA&= 0xFFFFFFFE;
	}
	if(UART3->TXSTA!=0x00000002)
	{
		UART3->TXSTA &= 0xFFFFFF87;
	}
	if(UART4->RXSTA!=0x00000000)
	{
		UART4->RXSTA&= 0xFFFFFFFE;
	}
	if(UART4->TXSTA!=0x00000002)
	{
		UART4->TXSTA &= 0xFFFFFF87;
	}
	if(UART5->RXSTA!=0x00000000)
	{
		UART5->RXSTA&= 0xFFFFFFFE;
	}
	if(UART5->TXSTA!=0x00000002)
	{
		UART5->TXSTA &= 0xFFFFFF87;
	}
	///*��Դ����*///
	if(PMU->WKPFLAG!=0x00000000)
	{
		PMU->WKPFLAG|=0x000001FF;
	}
	if(PMU->LPREIF!=0x00000000)
	{
		PMU->LPREIF|=0x00000003;
	}
	///*HardFault*///
	if(SCU->HDFFLAG != 0x00000000)
	{
		SCU->HDFFLAG |= 0x0000007F;
	}

	WWDT->WWDTCON=0x000000AC;
	if(WWDT->WWDTIF != 0x00000000)
	{
		WWDT->WWDTIF |= 0x00000001;
	}
	///*Clock*///
	if(ANAC->FDETIE != 0x00000000)
	{
		ANAC->FDETIE= 0x00000000;
	}
	if(ANAC->FDETIF != 0x00000000)
	{
		ANAC->FDETIF |= 0x00000001;
	}

	///*ģ��Ƚ���*///
	if(ANAC->COMP1CR!=0x00000000)
	{
		ANAC->COMP1CR &= 0xfffffffE;
	}
	if(ANAC->COMP2CR!=0x00000000)
	{
		ANAC->COMP2CR &= 0xfffffffE;
	}
	if(ANAC->COMPIF!=0x00000000)
	{
		ANAC->COMPIF|=0x00000003;
	}
	///*I2C*///
	if(I2C->I2CCTRL!=0x00006000)
	{
		I2C->I2CCTRL=0x00006000;
	}
	if(I2C->I2CIR!=0x00000000)
	{
		I2C->I2CIR=0x00000001;
	}
	if(I2C->I2CERR!=0x00000000)
	{
		I2C->I2CERR=0x00000007;
	}
	///*HSPI*///
	if(HSPI->SPICR2!=0x00000054)
	{
		HSPI->SPICR2=0x00000054;
	}
	if(HSPI->SPIIE!=0x00000000)
	{
		HSPI->SPIIE=0x00000000;
	}
	if((HSPI->SPIIF&0x00000018)!=0x00000000)
	{
		HSPI->SPIIF|=0x00000018;
	}
	///*SPI*///
	if(SPI1->SPICR2!=0x00000054)
	{
		SPI1->SPICR2=0x00000054;
	}
	if((SPI1->SPIIF&0x00000018)!=0x00000000)
	{
		SPI1->SPIIF|=0x00000018;
	}
	if(SPI2->SPICR2!=0x00000054)
	{
		SPI2->SPICR2=0x00000054;
	}
	if((SPI2->SPIIF&0x00000018)!=0x00000000)
	{
		SPI2->SPIIF|=0x00000018;
	}
	///*7816*///
	if (U78160->U7816CTRL != 0x00000000)
	{
		U78160->U7816CTRL=0x00000000;
	}
	if (U78160->U7816IF != 0x00000002)
	{
		U78160->U7816IF|=0x00000005;
	}
	if (U78160->U7816ERR != 0x00000000)
	{
		U78160->U7816ERR|=0x0000000F;
	}
	if (U78161->U7816CTRL != 0x00000000)
	{
		U78161->U7816CTRL=0x00000000;
	}
	if (U78161->U7816IF != 0x00000002)
	{
		U78161->U7816IF|=0x00000005;
	}
	if (U78161->U7816ERR != 0x00000000)
	{
		U78161->U7816ERR|=0x0000000F;
	}
	///*DMA*///
	if (DMA->GLOBALCTRL != 0x00000000)
	{
		DMA->GLOBALCTRL=0x00000000;
	}

	///*CRC*///
	if (CRC->FLSCRCEN != 0x00000000)
	{
		CRC->FLSCRCEN=0x00000000;
	}
	///*ETIME*///
	if (ETIM1->ETxCR != 0x00000000)
	{
		ETIM1->ETxCR=0x00000000;
	}
	if (ETIM1->ETxIF != 0x00000000)
	{
		ETIM1->ETxIF|=0x0000000F;
	}
	if (ETIM2->ETxCR != 0x00000000)
	{
		ETIM2->ETxCR=0x00000000;
	}
	if (ETIM2->ETxIF != 0x00000000)
	{
		ETIM2->ETxIF|=0x0000000F;
	}
	if (ETIM3->ETxCR != 0x00000000)
	{
		ETIM3->ETxCR=0x00000000;
	}
	if (ETIM3->ETxIF != 0x00000000)
	{
		ETIM3->ETxIF|=0x0000000F;
	}
	if (ETIM4->ETxCR != 0x00000000)
	{
		ETIM4->ETxCR=0x00000000;
	}
	if (ETIM4->ETxIF != 0x00000000)
	{
		ETIM4->ETxIF|=0x0000000F;
	}
	///*BTIME*///
	if (BTIM1->BTCR1 != 0x00000000)
	{
		BTIM1->BTCR1=0x00000000;
	}
	if (BTIM1->BTIF != 0x00000000)
	{
		BTIM1->BTIF|=0x0000001F;
	}
	if (BTIM2->BTCR1 != 0x00000000)
	{
		BTIM2->BTCR1=0x00000000;
	}
	if (BTIM2->BTIF != 0x00000000)
	{
		BTIM2->BTIF|=0x0000001F;
	}
	///*LCD*///
	if (LCD->DISPCTRL != 0x00000000)
	{
		LCD->DISPCTRL=0x00000000;
	}
	if (LCD->LCDTEST != 0x00000000)
	{
		LCD->LCDTEST=0x00000000;
	}
	if (LCD->DISPIF != 0x00000000)
	{
		LCD->DISPIF|=0x00000003;
	}
	if (LCD->COM_EN != 0x00000000)
	{
		LCD->COM_EN=0x00000000;
	}
	if (LCD->SEG_EN0 != 0x00000000)
	{
		LCD->SEG_EN0=0x00000000;
	}
	if (LCD->SEG_EN1 != 0x00000000)
	{
		LCD->SEG_EN1=0x00000000;
	}
	if (LCD->LCDBSTCON != 0x00000040)
	{
		LCD->LCDBSTCON=0x00000040;
	}
	///*ADC*///
	if (ANAC->ADCCON != 0x00000000)
	{
		ANAC->ADCCON=0x00000000;
	}
	if (ANAC->ADCIF != 0x00000000)
	{
		ANAC->ADCIF|=0x00000001;
	}
	if(LPTIM->LPTCTRL != 0x00000000)
	{
		LPTIM->LPTCTRL=0x00000000;
	}
	if (LPTIM->LPTIE != 0x00000000)
	{
		LPTIM->LPTIE=0x00000000;
	}
	if (LPTIM->LPTIF != 0x00000000)
	{
		LPTIM->LPTIF|=0x00000007;
	}
	///**********SVD���************///
	if(ANAC->SVDCFG !=	0x000000F8)///*��ʹ�ܣ����������˲�,���Թ���
	{
		ANAC->SVDCFG = 0x000000F8;
	}
	if(ANAC->SVDCON !=	0x00000001)
	{
		ANAC->SVDCON = 0x00000001;
	}
	if((ANAC->SVDSIF&0x00000003)!=0)///*���жϱ�־
	{
		ANAC->SVDSIF|=0x00000003;
	}
	if (!(ANAC->BORCON&ANAC_BORCFG_OFF_BOR_ENABLE))
	{
		ANAC->BORCON|=ANAC_BORCFG_OFF_BOR_ENABLE;
	}
	if (!(ANAC->PDRCON&ANAC_PDRCFG_PDREN_ENABLE))
	{
		ANAC->PDRCON=ANAC_PDRCFG_PDREN_ENABLE;
	}
	if (RCC->PLLCON&RCC_PLLCON_PLLEN_ON)
	{
		RCC->PLLCON &= (~RCC_PLLCON_PLLEN_ON);
	}
	if (!(RCC->RCLPCON&RCC_RCLPCON_RCLP_EN_B_OFF))
	{
		RCC->RCLPCON |= RCC_RCLPCON_RCLP_EN_B_OFF;
	}
	SysTick->CTRL = 0;

	///*�͹��ĵ�Դ����
	if(PMU->LPREIE != 0x00000000)
	{
		PMU->LPREIE = 0x00000000;
	}
	if(RCC->SYSCLKSEL != 0x80000000)///*���Ѻ�����8M
	{
		RCC->SYSCLKSEL = 0x80000000;
	}
	if(ANAC->ADCINSEL&ANAC_ANATESTSEL_BUF4TST_EN_ENABLE)
	{
		ANAC->ADCINSEL &=(~ANAC_ANATESTSEL_BUF4TST_EN_ENABLE);
	}

	if(PMU->LPMCFG != 0x00060602)
	{
		PMU->LPMCFG = 0x00060602;
	}

	if(RCC->PERCLKCON1!=0x800000FC)///*ʱ�ӳ�ʼ��
	{
		RCC->PERCLKCON1=0x800000FC;
	}
	if(RCC->PERCLKCON2!=0x00060000)
	{
		RCC->PERCLKCON2=0x00060000;
	}
	if(RCC->PERCLKCON3!=0x00000000)
	{
		RCC->PERCLKCON3=0x00000000;
	}
	if(RCC->PERCLKCON4!=0x00000000)
	{
		RCC->PERCLKCON4=0x00000000;
	}
}
/**************************************************************************************************
����ԭ��: void SF_IOSetupPowerOff(void)
��������: �͹����µ�Ƭ�����������
�������: ��
�������: ��
����λ��: �ڵ͹�����ѭ���У�ÿ��ѭ��������
��    ע: ********************û����������£�����Ϊ��©�����
          *******����ܽ���������*********
**************����оƬ������ȫʧѹ�ж���*************************************
������λ�ܽ�:�ڸò�������Ϊ���Ը�λ�ܽŽ����κβ��������������ã��ڽ���͹���ʱ������Ϊ��λ״̬��
*****�ڵ͹��ĳ����У���ʼ����ȫʧѹʱ��58sʱ����򿪸�λ�ܽţ�Ȼ��ȫʧѹ��ɺ�60s�����ո�λ�ùܽţ�
������Դ���ƹܽţ�����ȫʧѹ��������Դ�ڸò��ֲ�������ά��֮ǰ״̬��
***�ɵ͹������н�������û�رյ�Դ������ȫʧѹ60s��Ҳ��رռ�����Դ��
6V��Դ���ƹܽ�:����Ϊ6V��Դ��Ч����ͣ���������Ϊ��������ߣ���ͣ���������Ϊ��©�����
**************************************************************************************************/
void SF_IOSetupPowerOff(void)
{
	ulong32 VL_DataBuff;

	if( !( RCC->PERCLKCON1 & RCC_PERRCCCON1_PDCCKEN_ON ) )
	{
		RCC->PERCLKCON1 |= RCC_PERRCCCON1_PDCCKEN_ON;
	}

	/*�ر�����ʹ��*/
	GPIOA->INEN &= 0xFFFF0002;    /*ȥ��������λ�ܽ�*/
	GPIOB->INEN  = 0x00000000;
	GPIOC->INEN &= 0xFFFF4400;    /*ȥ��������Դ���Ƽ�6V���ʹ�ܹܽ�*/
	GPIOD->INEN  = 0x00000000;
	GPIOE->INEN  = 0x00000000;
	GPIOF->INEN  = 0x00000800;    /*������*/
	GPIOG->INEN  = 0x00000000;

    /*�ر�����ʹ��*/
	GPIOA->PUPDR &= 0xFFFF0002;    /*ȥ��������λ�ܽ�*/
	GPIOB->PUPDR  = 0x00000000;
	GPIOC->PUPDR &= 0xFFFF4400;    /*ȥ��������Դ���Ƽ�6V���ʹ�ܹܽ�*/
	GPIOD->PUPDR  = 0x00000000;
	GPIOE->PUPDR  = 0x00000000;
	GPIOF->PUPDR  = 0x00000000;
	GPIOG->PUPDR  = 0x00000000;

    /*�򿪿�©ʹ��*/
	GPIOA->OTYPER |= 0x0000FFFD;	/*ȥ��������λ�ܽ�*/
	GPIOB->OTYPER  = 0x0000FFFF;
	GPIOC->OTYPER |= 0x0000BBFF;	/*ȥ��������Դ���Ƽ�6V���ʹ�ܹܽ�*/
	GPIOD->OTYPER  = 0x0000FFFF;
	GPIOE->OTYPER  = 0x0000FFFF;
	GPIOF->OTYPER  = 0x0000FFFF;
	GPIOG->OTYPER  = 0x0000FFFF;

    /*�����*/
	GPIOA->BSETH = 0x0000FFFD;	    /*ȥ��������λ�ܽ�*/
	GPIOB->BSETH = 0x0000FFFF;
	GPIOC->BSETH = 0x0000BBFF;	    /*ȥ��������Դ���Ƽ�6V���ʹ�ܹܽ�*/
	GPIOD->BSETH = 0x0000FFFF;
	GPIOE->BSETH = 0x0000FFFF;
	GPIOF->BSETH = 0x0000FFFF;
	GPIOG->BSETH = 0x0000FFFF;

	/*����Ϊ���*/
	VL_DataBuff=GPIOA->MODER;
	VL_DataBuff &= 0x0000000C;
	VL_DataBuff	|= 0x55555551;
	GPIOA->MODER = VL_DataBuff;	    /*ȥ��������λ�ܽ�*/
	GPIOB->MODER = 0x55555555;

	VL_DataBuff  = GPIOC->MODER;
	VL_DataBuff &= 0x30300000;
	VL_DataBuff	|= 0x45455555;
	GPIOC->MODER = VL_DataBuff;	   /*ȥ��������Դ���Ƽ�6V���ʹ�ܹܽ�*/

	GPIOD->MODER = 0x55555555;
	GPIOE->MODER = 0x55555555;
	GPIOF->MODER = 0x55D55555;	   /*������PF11����Ϊģ�����룬���Ĳ���*/

    #if ( 0 == _DEBUG )
	{
		GPIOG->MODER = 0x55555555;
	}
	#else
	{
		GPIOG->MODER = 0x555A5555;
	}
	#endif

	GPIO->PINWKEN	= 0x00000000;
}
/***************************************************************************************************
����ԭ��: void SF_IOSetupPowerOff_UsedCAP(void)
��������: �͹����µ�Ƭ�����������
�������: ��
�����������
���ز���: �ڵ͹�����ѭ���У�ÿ��ѭ��������
��    ע:********************û����������£�����Ϊ��©�����
        *******����ܽ���������*********
        **************����оƬ������ȫʧѹ�ж���*************************************
������λ�ܽ�:�ڸò�������Ϊ���Ը�λ�ܽŽ����κβ��������������ã��ڽ���͹���ʱ������Ϊ��λ״̬��
*****�ڵ͹��ĳ����У���ʼ����ȫʧѹʱ��58sʱ����򿪸�λ�ܽţ�Ȼ��ȫʧѹ��ɺ�60s�����ո�λ�ùܽţ�
������Դ���ƹܽţ�����ȫʧѹ��������Դ�ڸò��ֲ�������ά��֮ǰ״̬��
***�ɵ͹������н�������û�رյ�Դ������ȫʧѹ60s��Ҳ��رռ�����Դ��
6V��Դ���ƹܽ�:����Ϊ6V��Դ��Ч����ͣ���������Ϊ��������ߣ���ͣ���������Ϊ��©�����
�������ݹܽţ��г�������ʱ�����������
***************************************************************************************************/
void SF_IOSetupPowerOff_UsedCAP(void)
{
	ulong32 VL_DataBuff;

	if( !(RCC->PERCLKCON1 & RCC_PERRCCCON1_PDCCKEN_ON) )
	{
		RCC->PERCLKCON1 |= RCC_PERRCCCON1_PDCCKEN_ON;
	}
	/*�ر�����ʹ��*/
	GPIOA->INEN &= 0xFFFF2002;	    /*ȥ��������λ�ܽż��������ݷŵ�ܽ�*/
	GPIOB->INEN  = 0x00000000;
	GPIOC->INEN &= 0xFFFF4400;	    /*ȥ��������Դ���Ƽ�6V���ʹ�ܹܽ�*/
	GPIOD->INEN  = 0x00000000;
	GPIOE->INEN  = 0x00000000;
	GPIOF->INEN  = 0x00000800;     /*������*/
	GPIOG->INEN  = 0x00000000;

    /*�ر�����ʹ��*/
	GPIOA->PUPDR &= 0xFFFF2002;	    /*ȥ��������λ�ܽż��������ݷŵ�ܽ�*/
	GPIOB->PUPDR  = 0x00000000;
	GPIOC->PUPDR &= 0xFFFF4400;	    /*ȥ��������Դ���Ƽ�6V���ʹ�ܹܽ�*/
	GPIOD->PUPDR  = 0x00000000;
	GPIOE->PUPDR  = 0x00000000;
	GPIOF->PUPDR  = 0x00000000;
	GPIOG->PUPDR  = 0x00000000;

    /*�򿪿�©ʹ��*/
	GPIOA->OTYPER |= 0x0000DFFD;    /*ȥ��������λ�ܽż��������ݷŵ�ܽ�*/
	GPIOB->OTYPER  = 0x0000FFFF;
	GPIOC->OTYPER |= 0x0000BBFF;    /*ȥ��������Դ���Ƽ�6V���ʹ�ܹܽ�*/
	GPIOD->OTYPER  = 0x0000FFFF;
	GPIOE->OTYPER  = 0x0000FFFF;
	GPIOF->OTYPER  = 0x0000FFFF;
	GPIOG->OTYPER  = 0x0000FFFF;

    /*�����*/
	GPIOA->BSETH = 0x0000DFFD;	    /*ȥ��������λ�ܽż��������ݷŵ�ܽ�*/
	GPIOB->BSETH = 0x0000FFFF;
	GPIOC->BSETH = 0x0000BBFF;	    /*ȥ��������Դ���Ƽ�6V���ʹ�ܹܽ�*/
	GPIOD->BSETH = 0x0000FFFF;
	GPIOE->BSETH = 0x0000FFFF;
	GPIOF->BSETH = 0x0000FFFF;
	GPIOG->BSETH = 0x0000FFFF;

    /*����Ϊ���*/
	VL_DataBuff=GPIOA->MODER;
	VL_DataBuff &= 0x0C00000C;
	VL_DataBuff	|= 0x51555551;
	GPIOA->MODER = VL_DataBuff;	    /*ȥ��������λ�ܽż��������ݷŵ�ܽ�*/
	GPIOB->MODER = 0x55555555;

	VL_DataBuff=GPIOC->MODER;
	VL_DataBuff &= 0x30300000;
	VL_DataBuff	|= 0x45455555;
	GPIOC->MODER = VL_DataBuff;	    /*ȥ��������Դ���Ƽ�6V���ʹ�ܹܽ�*/

	GPIOD->MODER = 0x55555555;
	GPIOE->MODER = 0x55555555;
	GPIOF->MODER = 0x55D55555;	   /*������PF11����Ϊģ�����룬���Ĳ���*/

    #if ( 0 == _DEBUG )
	{
		GPIOG->MODER = 0x55555555;
	}
	#else
	{
		GPIOG->MODER = 0x555A5555;
	}
	#endif

	GPIO->PINWKEN	= 0x00000000;

	DF_SwitchOn_SuperCapPower();
}
///************************************************************************///
///*����ԭ��:void SF_SystemClockInPowerOff(void)
///*��������:�͹�����ϵͳʱ�ӵ�����
///*����ʱ��:�ڵ͹�����ѭ���У�ÿ��ѭ��������
///************************************************************************///
#define		CR_DS_MASK		0xfffffffc
void SF_SystemClockInPowerOff(void)
{
	__NOP();
	__NOP();

	/* Request Wait For Interrupt */
	__WFI();

	__NOP();
	__NOP();
}


///************************************************************************///
///*����ԭ��:void SF_RTCWakeUpInit(void)
///*��������:�͹����µ�Ƭ�����������
///*����ʱ��:�ڵ͹�����ѭ���У�ÿ��ѭ��������
///************************************************************************///
void SF_RTCWakeUpInit(void)
{
	if (RTC->RTCIF != 0x00000000)
	{
		RTC->RTCIF|=0x00001FFF;
	}
	RTC->RTCIE=0x00000008; ///*�����ж�ʹ��
	NVIC_EnableIRQ(RTC_IRQn);
}


///************************************************************************///
///*����ԭ��:void RTC_WKUP_IRQHandler(void)
///*��������:�͹�����RTC��ʱ�ж�:1s�ж�һ��,�������е�ʱ����ʱ����1s����У׼
///*         ����У׼ֵ��д��SFR,ֻ�����У׼ֵ,�ڵ����У׼ֵ��д��SFR
///*����ʱ��:
///************************************************************************///
void RTC_WKUP_IRQHandler(void)
{
//	ulong32 temp;
//	EXTI->PR |= LINE20TRIGGER;
//	RTC->ISR &= (ulong32)~RTC_ISR_WUTF;
//////	GPIOA->ODR ^= 0x00000001;
//	if( SV_PowerFlag == C_PowerOn )		///*�е��ʱ���У׼*///
//	{
//		if( SV_CalibrateRC_State == 0x86 )
//		{
//			SV_CalibrateRC_State = 0;
//			temp = CalibrateRCTimer->CNT;		///*ȡ������4M�ļ���ֵ����λms*///
//			temp = 1000000/temp;				///*��׼1s��4M����ֵ֮��ı������Ŵ�1000����ʵ��Ϊ��Уֵ*///
//			SV_CalibrateRC = RTC->WUTR;			///*����RC��������Ƶ��(38k)��1s��ʱ���ļ���ֵ��ĿǰΪ2375*///
//			SV_CalibrateRC = SV_CalibrateRC*temp;
//			SV_CalibrateRC = SV_CalibrateRC/1000;	///*����ֻ��Ҫ����Уֵ�����,*///
//													///*��ͣ�����͹��ĺ�,ֱ�ӽ��������д��,�˴���д*///
//			SF_CalibrateRCTimer_Disable();		///*ͣ��16λ��ʱ��*///
//		}
//		else if( SV_CalibrateRC_State == 0x68)
//		{
//			SV_CalibrateRC_State = 0x86;
//			SF_CalibrateRCTimerInit();				///*����16λ������*///
//		}
//	}
}

///***********************************************************************************///
///*Function���͹����º���1200�����ʴ���*///
///*Description��*///
///***********************************************************************************///
void InfraWakeupTimer_IRQHandler(void)
{
//	ulong32 databuf;
//////	GPIOA->ODR ^= 0x00000001;
//	SV_Wakeup_Flag = C_InfraWakeup_Flag;
//
//	databuf = (IO_INFRARX->IDR & INFRARX_SELECT);	///*ȡ��������ź�*///
//	InfraWakeupTimer->SR = C_TimerStatus_RESET;		///*���жϱ�־����*///
//	///*****************************************///
//	if( SV_Wakeup_Bit_CNT <= 7 )	///*����λ��8λ��ֻ���ղ���У��*///
//	{
//		SV_Wakeup_Bit_CNT++;
//		if( databuf )
//		{
//			SV_Wakeup_RecData >>= 1;
//			SV_Wakeup_RecData |= 0x80;
//			SV_Wakeup_CS++;
//		}
//		else
//		{
//			SV_Wakeup_RecData >>= 1;
//			SV_Wakeup_RecData &= 0x7f;
//		}
//	}
//	else if( SV_Wakeup_Bit_CNT == 8 )	///*У��λ*///
//	{
//		SV_Wakeup_Bit_CNT = 0;
//
//		SV_Wakeup_Flag = 0;
//		SV_Wakeup_Data = 0;
//		SF_InfarWakeupTimer_Disable();
//		SF_InfraWakeup_Dis();
//		if( ((databuf)&&((SV_Wakeup_CS&0x01) == 0x01))
//			||((!(databuf))&&((SV_Wakeup_CS&0x01) == 0x00)) )
//		{
//			if( (SV_Wakeup_RecData == 0x68)||(SV_Wakeup_RecData == 0x11)||(SV_Wakeup_RecData == 0x04) )
//			{
//				SV_Wakeup_Flag = C_InfraWakeup_Flag;
//
//				SV_Wakeup_Data <<= 8;
//				SV_Wakeup_Data |= SV_Wakeup_RecData;
//				SV_Wakeup_Data &= 0x00ffffff;
//
//				if( (SV_Wakeup_Data == 0x00681104)||(SV_Wakeup_Data == 0x00110468)||(SV_Wakeup_Data == 0x00046811) )
//				{
//					//SF_InfarWakeupTimer_Disable();
//					//SF_InfraWakeup_Dis();
//
//				}
//				else
//				{
//					//SF_InfarWakeupTimer_Disable();
//					SF_InfraWakeup_En();
//				}
//			}
//			//else
//			//{
//				//SV_Wakeup_Flag = 0;
//				//SV_Wakeup_Data = 0;
//				//SF_InfarWakeupTimer_Disable();
//				//SF_InfraWakeup_Dis();
//			//}
//		}
//		//else
//		//{
//			//SV_Wakeup_Flag = 0;
//			//SV_Wakeup_Data = 0;
//			//SF_InfarWakeupTimer_Disable();
//			//SF_InfraWakeup_Dis();
//		//}
//	}
//	else
//	{
//		SV_Wakeup_Flag = 0;
//		SV_Wakeup_Data = 0;
//		SF_InfarWakeupTimer_Disable();
//		SF_InfraWakeup_Dis();
//	}
}

///************************************************************************///
///*����ԭ��:void SF_SoftRTCInit(void)
///*��������:��ʱ�ӳ�ʼ��
///*����ʱ��:��ʱ�����ڵ͹����µĶ�ʱ����
///************************************************************************///
void SF_SoftRTCInit(void)
{
	RCC->PERCLKCON1|=RCC_PERRCCCON1_RTCRCCEN_ON;	///*RTCʱ��ʹ��*///

	if (RTC->RTCIF != 0x00000000)
	{
		RTC->RTCIF|=0x00001FFF;
	}
}


///************************************************************************///
///*����ԭ��:void SF_SoftRTCWakeupMode(void)
///*��������:��ʱ�ӽ����ʼ��ģʽ
///*����ʱ��:
///************************************************************************///
void SF_SoftRTCWakeupMode(void)
{
//	ulong32 initcounter = 0x00;
//	ulong32 initstatus = 0x00;
//
//	/* Disable the write protection for RTC registers */
//	RTC->WPR = C_RTCRegWpr1;
//	RTC->WPR = C_RTCRegWpr2;
//
//	/* Check if the Initialization mode is set */
//	if ((RTC->ISR & RTC_ISR_INITF) == (ulong32)0x00000000)
//	{
//		/* Set the Initialization mode */
//		RTC->ISR = (ulong32)RTC_INIT_MASK;
//
//		/* Wait till RTC is in INIT state and if Time out is reached exit */
//		do
//		{
//			initstatus = RTC->ISR & RTC_ISR_INITF;
//			initcounter++;
//		} while((initcounter != INITMODE_TIMEOUT) && (initstatus == 0x00));
//	}
}

///************************************************************************///
///*����ԭ��:void SF_EnterLowPower(void)
///*��������:����͹���ǰ����Ҫ��ʼ��һЩ�����������7�����ƣ����������������Ƶ�
///*����ʱ��:
///************************************************************************///
void SF_EnterLowPower(void)
{
	Str_LowPower_KeyUp.Wakeup_En = C_Enable;
	Str_LowPower_KeyUp.Times = 0;

	Str_LowPower_KeyDown.Wakeup_En = C_Enable;
	Str_LowPower_KeyDown.Times = 0;

	SV_LowPower_7Day = 0;
	Str_LowPower_Infra.Wakeup_En = C_Enable;
	Str_LowPower_Infra.Times = 0;
	Str_LowPower_Infra.WakeupState = C_Disable;///*����δ����״̬
	SV_LowPower_RTC83min=0;
}

///************************************************************************///
///*����ԭ��:void InF_PowerOnDelay(void)
///*��������:�ϵ�̶���ʱ500ms
///*����ʱ��:
///************************************************************************///
void InF_PowerOnDelay(void)
{
	ushort16 v_delay;
	for(v_delay=0;v_delay<C_PowerOnDelay;v_delay++)
	{
		if( ((ANAC->SVDALM)&ANAC_SVDALM_SVDALM_B_ENABLE) == ANAC_SVDALM_SVDALM_B_ENABLE )	///*����еģ�����500�Σ�ÿ�μ��1ms. *///
		{
			InF_Delay_us(1000);
		}
		else
		{
			break;
		}
	}
}

/************************************************************************
*���������״̬��3�еĹ��緽ʽдΪ����ع��硱
************************************************************************/
void SF_WritePowerMode_PowerOff(void)
{
	uchar8 V_ucBuffer[10];
	ushort16 V_usLen, V_usDataEncode;

	V_usLen = CLMeter_Work_State3;
	InF_Read_Data(CMeter_Work_State3, &V_ucBuffer[0], &V_usLen, &V_usDataEncode);
	V_ucBuffer[0] &= C_PowerModeInit;
	V_ucBuffer[0] |= C_PowerMode;
	InF_Write_Data(C_Msg_Dispatch, CMeter_Work_State3, &V_ucBuffer[0], CLMeter_Work_State3, C_W_SafeFlag);
}

///************************************************************************///
///*����ԭ��:uchar8 SF_JudgeAllLoseVoltage(void)
///*��������:�ж��Ƿ����ȫʧѹ��������
///*����:��
///*���:SV_LowPower_7Day�����˼Ӳ���(�����������ͣ���ۼ�7��,��λΪ��)
///*����:C_AllLossPrepare:��ʾ��Ҫ׼����ȫʧѹ:�򿪼���оƬ��Դ,
///*     C_AllLossTime:��־����ȫʧѹ��¼
///*����ʱ��:�������ÿs����һ��
///************************************************************************///
uchar8 SF_JudgeAllLoseVoltage(void)
{
	SV_LowPower_7Day++;
	if( SV_LowPower_7Day == C_AllLossPrepare )
	{
		return C_AllLossPrepare;
	}
	else if( SV_LowPower_7Day == C_AllLossTime )
	{
		return C_AllLossTime;
	}
	else
	{
		return C_Error;
	}
}

///************************************************************************///
///*����ԭ��:void Msg_AllLoseVoltage(Str_Msg_Parameter * P_Msg_Parameter)
///*��������:����ȫʧѹ����
///*����:P_Msg_Parameterָ����Ϣ��ȡ���ŵı�����,
///*���:���������������ȫʧѹ��¼
///*����:C_AllLossPrepare:��ʾ��Ҫ׼����ȫʧѹ:�򿪼���оƬ��Դ,
///*     C_AllLossTime:��ʾ����ȫʧѹ��¼
///*����ʱ��:�������ÿs����һ��
///************************************************************************///
void Msg_AllLoseVoltage(Str_Msg_Parameter * P_Msg_Parameter)
{
	uchar8 v_databuf;

	SV_LowPower_RTC83min++;///*�͹���RTCʱ�ӵ�У����ʱ����1sΪ������λ
		if( SV_LowPower_RTC83min >= C_LowPower_RTC83min )
		{
			SV_LowPower_RTC83min=0;
			InF_TempAdc_CmpAndJec();
	}

	if( P_Msg_Parameter->DerictAddr == C_Msg_AllLossVoltage )
	{
		if(P_Msg_Parameter->PowerFlag == C_PowerOff )
		{
			v_databuf = SF_JudgeAllLoseVoltage();
			if( C_AllLossPrepare == v_databuf )
			{
				///*������оƬ��Դ*///
				DF_SwitchOn_EMeterIcPower();
				///*��ʱ100msд��У������*///
				InF_Delay_us(12500);				///*ʱ�Ӳ�Լ8�������100ms����ʱ����12500us��ֵ*///
				InF_PowerDownInitial_MeterIC();
				SF_ClrSV_TimerBasedTickTimer_1000ms();	///*��ʼ������оƬ��,���¿�ʼ��ʱ*///
			}
			else if( C_AllLossTime == v_databuf )
			{
				if( InF_PowerDownReadData_MeterIC() == C_OK )
				{
//					Inf_LowpowerPowerFail();		///*�����¼*///
					Inf_LowpowerTotalVoltagelose();	///*ȫʧѹ*///
					InF_ClearHexVarregtype_MeterIC(C_ClearCurrData);
				}
				DF_SwitchOff_EMeterIcPower();	///*�رռ���оƬ��Դ*///
				MeterIC_Reset();				///*��λ����оƬ:��ֹ��Vcc*///
			}


		}
	}
}

/***********************************************************************************
*Function�������ڲ���ع���ʱ��
*Description��
*Input�������͹���ʱ��,���ݲ���ڲ���ع���ʱ��
*Output���������ڲ���ع���ʱ��
*Calls��
*Called By���˳��͹���ʱ��һ��ʱ����ۼ�
*Influence��
*Tips��
*    1.�ڲ���ع���ʱ��,RAM����CRC,ʹ��ʱ���ж��Ƿ�ΪBCD��
*    2.��������͹���ʱ��Ƿ�,��Ĭ��Ϊ����ͣ���ڼ��ۼƵĹ���ʱ��Ϊ0
*    3.������ݲ���ڲ���ع���ʱ���BCD��,ֱ�ӽ���ʱ������
*Others��
*Author: 2014/11/5
***********************************************************************************/
void SF_Cal_BattWorktime(void)
{
	uchar8 V_Buffer_DataProcess[CLBatt_Work_Time];			/*���ݲ��������ʱ��*/
	uchar8 V_Buffer_Current[CLBatt_Work_Time];				/*���θ��ݽ����͹���ʱ�����ĵ�ع���ʱ��*/
	uchar8 V_Buffer_EnterLowPower[CLEnter_LowPower_Time];	/*���͹���ʱ��*/
	uchar8 V_Buffer_ExitLowPower[CLExit_LowPower_Time];		/*���͹���ʱ��*/

	ushort16 V_uslen, V_usDataEncode;
	ulong32 time;
	uchar8 V_ReturnFlag, V_len;

	/*���ȴ����ݲ�����ڲ���ع���ʱ��*/
	V_uslen = CLBatt_Work_Time;
	V_ReturnFlag=InF_Read_Data(CBatt_Work_Time, &V_Buffer_DataProcess[0], &V_uslen, &V_usDataEncode);
	if(C_OK!=V_ReturnFlag)
	{
		memset(&V_Buffer_Current[0],0x00,4);
		InF_Write_Data(C_Msg_Dispatch, CBatt_Work_Time, &V_Buffer_Current[0], CLBatt_Work_Time, C_W_SafeFlag);
		return;
	}
	/*�ж��ڲ���ع���ʱ���Ƿ�ΪBCD��*/
	if( PF_Judge_BCD(CLBatt_Work_Time, &V_Buffer_DataProcess[0]) == C_OK )
	{
		V_uslen = CLEnter_LowPower_Time;
		V_ReturnFlag=InF_Read_Data(CEnter_LowPower_Time, &V_Buffer_EnterLowPower[0], &V_uslen, &V_usDataEncode);
		if(C_OK!=V_ReturnFlag)
		{
			return;
		}
		V_uslen = CLExit_LowPower_Time;
		V_ReturnFlag=InF_Read_Data(CExit_LowPower_Time, &V_Buffer_ExitLowPower[0], &V_uslen, &V_usDataEncode);
		if(C_OK!=V_ReturnFlag)
		{
			return;
		}
		/*�жϽ����͹���ʱ���Ƿ�Ϸ�*/
#if 0
		if( (PF_DataTimeActive(V_Buffer_EnterLowPower, C_DT_Start_ss, CLEnter_LowPower_Time) == C_OK)
			&&(PF_DataTimeActive(V_Buffer_ExitLowPower, C_DT_Start_ss, CLExit_LowPower_Time) == C_OK) )
		{
#endif
			/*�����͹���ʱ�����:�ں������Ѿ����кϷ����ж���,����ǰ�治��Ҫ���кϷ����ж�*/
			if( PF_TimeSub_Min_698(V_Buffer_EnterLowPower, V_Buffer_ExitLowPower, &time) == C_LessThan )
			{
				V_len = 4;
				PF_HextoBCDBytes(&time, &V_Buffer_Current[0], &V_len);
				PF_BCDAddBytes(&V_Buffer_DataProcess[0], &V_Buffer_Current[0], &V_Buffer_Current[0], CLBatt_Work_Time);
				InF_Write_Data(C_Msg_Dispatch, CBatt_Work_Time, &V_Buffer_Current[0], CLBatt_Work_Time, C_W_SafeFlag);
			}
#if 0
		}
#endif
	}
	else
	{
		memset(&V_Buffer_Current[0], 0x00, 4);
		InF_Write_Data(C_Msg_Dispatch, CBatt_Work_Time, &V_Buffer_Current[0], CLBatt_Work_Time, C_W_SafeFlag);
	}
}

