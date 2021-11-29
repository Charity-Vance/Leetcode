
///*****************************************************************************************///
///*Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     Timer.c
///*Version:       V1
///*Date:          2014-3-12
///*Description:   ��ʱ�������ļ�
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
#include "Timer.h"
#include "IO.h"
#include "Dispatch.h"
#include "MCUConfig.h"
#include "uart.h"



void InF_DealWith5ms(void);
void InF_Delay_us(ulong32 Delay_Num);
//uchar8 InF_SwithMultiFunction(uchar8 Peripherals);
///***********************************************************************************///
///*Function�����������ж�*///
///*Description��5ms�ж�һ��,ֱ�Ӳ���ȫ�ֱ�������++*///
///*Input��*///
///*Output��*///
///*Calls��*///
///*Called By��*///
///*Influence��*///
///*Tips��*///
///*Others��*///
///*Author:zhiyong.gu*///
///***********************************************************************************///
extern uchar8 GV_ucEvenHarmonicDelayTimer;
void TickTimer_IRQHandler(void)
{
	uchar8 V_ExternalRelayStatus = 0;

	TickTimer->ETxIF |= C_TimerStatus_RESET;		///*���жϱ�־����*///
	///*****************************************///
	///*50ms������*///
	if( GV_ucEvenHarmonicDelayTimer != 0 )
	{
		GV_ucEvenHarmonicDelayTimer--;
	}
	if( SV_PowerDownReportTime <= ( C_Interval_1000ms * 3 ) )
	{
		SV_PowerDownReportTime++;
	}
	
	///*****************************************///
	///*100ms������*///
	if( SV_TimerBasedTickTimer_100ms <= C_Interval_100ms )
	{
		SV_TimerBasedTickTimer_100ms++;
	}
	///*****************************************///
	///*500ms������*///
	if( SV_TimerBasedTickTimer_500ms <= C_Interval_500ms )
	{
		SV_TimerBasedTickTimer_500ms++;
//		if(SV_TimerBasedTickTimer_500ms%2)
//		{ 
//			SwitchOn_BackLight();///test niu,5ms
//		}
//		else
//		{
//			SwitchOff_BackLight();///test niu
//		}		
	}

	///*****************************************///
	///*1000ms������*///
	if( SV_TimerBasedTickTimer_1000ms <= C_Interval_1000ms )
	{
		SV_TimerBasedTickTimer_1000ms++;
	}
	///*****************************************///
	///*Ѳ��������*///
	if( SV_TimerCruise <= C_Interval_5000ms )
	{
		SV_TimerCruise++;
	}
	///*���Ӽ�����*///
	if( SV_TimerCheckMcu < C_Interval_1min )
	{
		SV_TimerCheckMcu++;
	}
	///**************************************///
	///*�ϵ�������ȡ�ⲿ�����߹���100ms*///
	if( SV_TimerShut100ms != 0 )
	{
		SV_TimerShut100ms--;
	}
	///*�ϵ�����3s:�ϵ���ѹ��ʵʱ��δˢ��,Ϊ����Ը��ɼ�¼/�¼���¼/��ѹ�ϸ��ʵȵ�Ӱ��,��Щ������Ҫ����3s*///
	if( SV_TimerShutRealTimeData != 0 )
	{
		SV_TimerShutRealTimeData--;
	}
	///**************************************///
	///*ι����ʱ��*///
//	SV_TimerFeedWatchdog++;
	if( SV_TimerFeedWatchdog <= C_WatchDog_Feed )
	{
		SV_TimerFeedWatchdog++;
		FeedWatchDog();
	}
	///**************************************///
	if( SV_Timer_Delay >= (C_TimerSwitch_16+C_Interval_5ms) )
	{
		SV_Timer_Delay -= C_Interval_5ms;
	}
	else
	{
		SV_Timer_Delay = 0;
	}
	///**************************************///
	///*�����������塢ʱ��Ͷ������Ĵ���*///
	if(  SV_Timer_MultiFunction > C_TimerSwitch_8 )
	{
		SV_Timer_MultiFunction--;
		if( SV_Timer_MultiFunction == C_TimerSwitch_8 )
		{
			///*�رն๦���������*///
			DF_MultiFunction_Close();
			SV_Timer_MultiFunction = C_Interval_0ms;
		}
		else
		{
			SV_Timer_MultiFunction |= C_TimerSwitch_8;
		}
	}
	///**************************************///
	///*�̵��������źŴ�����������/���ü̵���*///
	if( SV_InternalRelayActTime > C_TimerSwitch_16 )		///*���ø��ɿ��ض���ʱ��*///
	{
		SV_InternalRelayActTime--;
		if( SV_InternalRelayActTime == C_TimerSwitch_16 )
		{
			DF_InternalRelayHold();
			SV_InternalRelayActTime = C_Interval_0ms;
		}
	}
	
	if( SV_ExternalRelayActTime > C_TimerSwitch_16 )
	{
		SV_ExternalRelayActTime--;
		if( SV_ExternalRelayActTime == C_TimerSwitch_16 )
		{
			SwitchOn_ExternalRelay();						///*���ÿ����ź�Ϊ����ʽ�����巢����̵���ʵ�ʴ���ͨ*///
			SV_ExternalRelayActTime = C_Interval_0ms;
		}
	}
	///**************************************///
	///*�ز�ģ�顢GPRSģ�顢΢����ģ��ĸ�λ����*///
	if( SV_Timer_ModuleReset > C_TimerSwitch_8 )
	{
		SV_Timer_ModuleReset--;
		if( SV_Timer_ModuleReset == C_TimerSwitch_8 )
		{
			DF_SwitchOn_ModuleEn();
			SV_Timer_ModuleReset = C_Interval_0ms;
		}
	}
	///**************************************///
	///*���������*///
	if( SV_BeeperAct == C_AlwaysDisplay )
	{
		if( SV_BeeperTime == 0xffff )
		{
			//SV_BeeperCycle = 0;
		}
		else if( SV_BeeperTime >= C_Interval_5ms )
		{
			SV_BeeperTime -= C_Interval_5ms;
			//SV_BeeperCycle = 0;
		}
		else
		{
			SV_BeeperTime = 0;
			SV_BeeperAct = C_NotDisplay;
			//SV_BeeperCycle = 0;
			DF_SwitchOff_Beeper();
		}
	}
	else if( SV_BeeperAct == C_TwinkleDisplay )
	{
		if( SV_BeeperTime >= C_Interval_5ms )
		{
			SV_BeeperTime -= C_Interval_5ms;
			if( SV_BeeperCycle == 0 )			///*��˸ʱ��Ϊ0,����Ϊһֱ��,ֱ����ʱ��Ϊ0*///
			{
				;
			}
			else
			{
				if( SV_BeeperReverseTime >= C_Interval_5ms )
				{
					SV_BeeperReverseTime -= C_Interval_5ms;
				}
				else
				{
					SV_BeeperReverseTime = (SV_BeeperCycle/2 + SV_BeeperCycle%2);
					DF_ReversePhase_Beeper();
				}
			}
		}
		else
		{
			SV_BeeperTime = 0;
			SV_BeeperAct = C_NotDisplay;
			//SV_BeeperCycle = 0;
			DF_SwitchOff_Beeper();
		}
	}
	else
	{
		SV_BeeperAct = C_NotDisplay;
		SV_BeeperTime = 0;
		SV_BeeperCycle = 0;
		//DF_SwitchOff_Beeper();
	}
	///**************************************///
	///**************************************///
	///*��ѯ�Ϸ�����*///
	if( Str_KeyUp.Timer <= C_Interval_50ms )
	{
		Str_KeyUp.Timer++;
		if( DF_GetIOStatus(C_KeyUp) == Str_KeyUp.HStatus )	///*��ǰ״̬����ʷ״̬��ͬ*///
		{
			Str_KeyUp.Timer = 0;
		}
	}
	if( Str_KeyUpPermit.Timer <= C_Interval_3000ms )
	{
		Str_KeyUpPermit.Timer++;
		if( DF_GetIOStatus(C_KeyUp) == Str_KeyUpPermit.HStatus )	///*��ǰ״̬����ʷ״̬��ͬ*///
		{
			Str_KeyUpPermit.Timer = 0;
		}
	}
	///**************************************///
	///*��ѯ�·�����*///
	if( Str_KeyDown.Timer <= C_Interval_50ms )
	{
		Str_KeyDown.Timer++;
		if( DF_GetIOStatus(C_KeyDown) == Str_KeyDown.HStatus )	///*��ǰ״̬����ʷ״̬��ͬ*///
		{
			Str_KeyDown.Timer = 0;
		}
	}
	if( Str_KeyDownPermit.Timer <= C_Interval_3000ms )
	{
		Str_KeyDownPermit.Timer++;
		if( DF_GetIOStatus(C_KeyDown) == Str_KeyDownPermit.HStatus )	///*��ǰ״̬����ʷ״̬��ͬ*///
		{
			Str_KeyDownPermit.Timer = 0;
		}
	}
	///**************************************///
	///*��ѯ��̰���*///
//	if( Str_KeyPrg.Timer <= C_Interval_50ms )
//	{
//		Str_KeyPrg.Timer++;
//		if( DF_GetIOStatus(C_KeyPrg) == Str_KeyPrg.HStatus )	///*��ǰ״̬����ʷ״̬��ͬ*///
//		{
//			Str_KeyPrg.Timer = 0;
//		}
//	}
	///**************************************///
	///*��ѯ����ǰ���*///
	if( Str_KeyOpenCover.Timer <= C_Interval_50ms )
	{
		Str_KeyOpenCover.Timer++;
	}
	if( DF_GetIOStatus(C_KeyOpenCover) == Str_KeyOpenCover.HStatus )	///*��ǰ״̬����ʷ״̬��ͬ*///
	{
		Str_KeyOpenCover.Timer = 0;
	}
	///**************************************///
	///*��ѯ��β�ǰ���*///
	if( Str_KeyOpenTerminal.Timer <= C_Interval_50ms )
	{
		Str_KeyOpenTerminal.Timer++;
	}
	if( DF_GetIOStatus(C_KeyOpenTerminal) == Str_KeyOpenTerminal.HStatus )	///*��ǰ״̬����ʷ״̬��ͬ*///
	{
		Str_KeyOpenTerminal.Timer = 0;
	}
	///**************************************///
	///*��ѯ�ų�������*///
	if( Str_Magnetic.Timer <= C_Interval_50ms )
	{
		Str_Magnetic.Timer++;
	}
	if( DF_GetIOStatus(C_Magnetic) == Str_Magnetic.HStatus )	///*��ǰ״̬����ʷ״̬��ͬ*///
	{
		Str_Magnetic.Timer = 0;
	}
	///**************************************///
	///*������Դ������*///
	if( Str_CheckAuPower.Timer <= C_Interval_50ms )
	{
		Str_CheckAuPower.Timer++;
	}
	if( DF_GetIOStatus(C_CheckAuPower) == Str_CheckAuPower.HStatus )	///*��ǰ״̬����ʷ״̬��ͬ*///
	{
		Str_CheckAuPower.Timer = 0;
	}
	///**************************************///
	///*����оƬIRQ�жϼ�����*///
//	if( Str_MeterICIRQ.Timer <= C_Interval_50ms )
//	{
//		Str_MeterICIRQ.Timer++;
//	}
//	if( DF_GetIOStatus(C_MeterICIRQ) == Str_MeterICIRQ.HStatus )	///*��ǰ״̬����ʷ״̬��ͬ*///
//	{
//		Str_MeterICIRQ.Timer = 0;
//	}
	///**************************************///
	///*�̵���״̬������*///
	if( Str_RelayStatus.Timer <= C_Interval_50ms )
	{
		Str_RelayStatus.Timer++;
	}
	if( DF_GetIOStatus(C_RelayStatus) == Str_RelayStatus.HStatus )	///*��ǰ״̬����ʷ״̬��ͬ*///
	{
		Str_RelayStatus.Timer = 0;
	}
	/**************************************/
	/*���ü̵���״̬������*/	
	V_ExternalRelayStatus = DF_GetIOStatus(C_ExternalRelayStatus);
	if( Str_ExternalRelayStatus.Timer < C_ExRelayInvaildNum )
	{
		if(V_ExternalRelayStatus == C_Invalid)				/*����е͵�ƽ���ͽ��д����ۼ�*/
		{
			Str_ExternalRelayStatus.Timer++;
		}
	}
	///**************************************///
	///*ģ�鷢��״ָ̬ʾ������*///
	if( Str_ModuleStatus.Timer <= C_Interval_50ms )
	{
		Str_ModuleStatus.Timer++;
	}
	if( DF_GetIOStatus(C_ModuleStatus) == Str_ModuleStatus.HStatus )	///*��ǰ״̬����ʷ״̬��ͬ*///
	{
		Str_ModuleStatus.Timer = 0;
	}
	///*****************************************///
	///*�忨״̬���*///
	if(Str_CardStatus.Timer <= C_Interval_50ms)
	{
		Str_CardStatus.Timer++;
	}
	if( DF_GetIOStatus(C_CardStatus) == Str_CardStatus.HStatus )	///*��ǰ״̬����ʷ״̬��ͬ*///
	{
		Str_CardStatus.Timer = 0;
	}
	///*****************************************///
}

///***********************************************************************************///
///*Function���������Ķ�ʱ����ʼ*///
///*Description���ϵ��ʼ��ʱ���á����Ѻ����*///
///*Input��*///
///*Output��*///
///*Calls��*///
///*Called By��*///
///*Influence��*///
///*Tips��*///
///*Others��*///
///*Author:zhiyong.gu*///
///***********************************************************************************///
void InF_TickTimerStart(void)
{
	TickTimerClock_EN;						///*ϵͳʱ���ṩ����ʱ�����޷�Ƶ=ϵͳʱ��*///
	TickTimer->ETxCR = C_TIM_CR1_CLEAR;				///*���ƼĴ�������*///
	
	TickTimer->ETxINSEL = 0;				///*�����ź�ѡ����ƣ�APBCLK*///
	TickTimer->ETxPESCALE1 = 0x00000001;			///*Ԥ��Ƶ�Ĵ�����2��Ƶ*///  
	TickTimer->ETxPESCALE2 = 0;			///*Ԥ��Ƶ�Ĵ���������Ƶ*///  
	TickTimer->ETxIE &= C_TIM_UIE_DIS;	///*�жϽ�ֹ*///          
	TickTimer->ETxIF |= C_TimerStatus_RESET;	///*���жϱ�־*///  
	TickTimer->ETxIVR = C_TickTimerCounter;
	
	TickTimer->ETxCR |= C_CardBaudRateTimerETxCR;		///*���ƼĴ������ã�PWM��ֹ����ʱģʽ*///
	///*******************************************************///
	TickTimer->ETxCR |= C_TIM_CR1_CEN;	///*��ʽ������ʱ����ʼ����*///
	TickTimer->ETxIE |= C_TIM_UIE_EN;		///*ʹ���ж�*///
	///*******************************************************///
	NVIC_EnableIRQ(TickTimer_Interrupt);	///*���������ж�ʹ��*///	
}

///***********************************************************************************///
///*Function���������Ķ�ʱ��ֹͣ*///
///*Description������͹���ʱ���á��ӻ���״̬����͹��ĵ���*///
///*Input��*///
///*Output��*///
///*Calls��*///
///*Called By��*///
///*Influence��ֹͣ��������ϵͳʱ�ӵĹ�������ֹ�жϣ��Ӷ���ʡ����*///
///*Tips��*///
///*Others��*///
///*Author:zhiyong.gu*///
///***********************************************************************************///
void InF_TickTimerStop(void)
{
	TickTimer->ETxCR &= (~C_TIM_CR1_CEN);			///*ֹͣ����*///
	TickTimer->ETxIF |= C_TimerStatus_RESET;	///*���жϱ�־*///
	TickTimerClock_DIS;												///*ϵͳʱ��ֹͣ�ṩ����ʱ��*///
	NVIC_DisableIRQ(TickTimer_Interrupt);			///*���������жϽ�ֹ*///
}

///**************************************************************************************///
///*Function:���������*///
///*Description:���������졢�رա����������Է�����*///
///*Input: BeeperOutType:C_AlwaysDisplay: ����
///*					 C_NotDisplay:    �ر�
///*					 C_TwinkleDisplay:���������Է�����*///
///*       BeeperOutTime:������ʱ��(��msΪ��λ,hex��ʽ,ffffΪ�����򳣱�,0Ϊ������)
///*					 ����5��������ʱ,ȥ������.С��5ʱ������
///*					 BeeperOutType=C_TwinkleDisplay,������ִ�к�,�����Թرս���
///*					 BeeperOutType=C_AlwaysDisplay,��BeeperOutTimeʱ���ر�,BeeperOutCycle��Ч
///*					 BeeperOutType=C_NotDisplay,ֱ�ӹر�,BeeperOutTime��BeeperOutCycle����Ч
///*	   BeeperOutCycle:����1�����ڵ�ʱ��(��msΪ��λ, hex��ʽ)
///*					  BeeperOutTypeΪC_AlwaysDisplay��C_NotDisplayʱ��Ч
///*					  ���BeeperOutCycle=1000��BeeperOutTime<500,����BeeperOutTimeʱ���ر�;�Դ�����
///*Output:����Ӧ�Ķ�ʱ��������������*///
///*Return:��
///*Tips:����������5ms�Ļ�������,�����ʱ���붯��ʱ�����������5ms
///*	 ���ñ��������������������,��ʱ����ص���5ms���������ﴦ��
///*     ����ڷ����������ڼ䱾�����ֱ�����,�������µ��õĲ������¿�ʼ�Է���������*///
///**************************************************************************************///
void InF_BeeperOut(uchar8 BeeperOutType,ushort16 BeeperOutTime,ushort16 BeeperOutCycle)
{
	switch(BeeperOutType)
	{
		case C_NotDisplay:				///*�رշ�����,����������ڲ���*///
		{
			SV_BeeperAct = C_NotDisplay;
			SV_BeeperTime = 0;
			SV_BeeperCycle = 0;
			DF_SwitchOff_Beeper();
			break;
		}
		case C_AlwaysDisplay:			///*��������*///
		{
			if(BeeperOutTime != 0)
			{
				SV_BeeperAct = C_AlwaysDisplay;
				SV_BeeperTime = BeeperOutTime;
				SV_BeeperCycle = 0;
				DF_SwitchOn_Beeper();
			}
			else						///*������ʱ��Ϊ0ֱ�ӹرշ�����*///
			{
				SV_BeeperAct = C_NotDisplay;
				SV_BeeperTime = 0;
				SV_BeeperCycle = 0;
				DF_SwitchOff_Beeper();
			}
			break;
		}
		case C_TwinkleDisplay:			///*����������*///
		{
			if(BeeperOutTime >= 2)
			{
				SV_BeeperAct = C_TwinkleDisplay;
				SV_BeeperTime = BeeperOutTime;
				SV_BeeperCycle = BeeperOutCycle;
				SV_BeeperReverseTime = (BeeperOutCycle/2);
				DF_SwitchOn_Beeper();
			}
			else
			{
				SV_BeeperAct = C_NotDisplay;
				SV_BeeperTime = 0;
				SV_BeeperCycle = 0;
				DF_SwitchOff_Beeper();
			}
			break;
		}
		default:
			break;
	}
}

/**********************************************************************************************************
����ԭ��: uchar8 InF_GetPeripheralStatus(uchar8 Peripheral)		
��������: �����õ��Ŀ���״̬����ȡ������												           
�������: 	    	
�������:   						       					
���ز���:
											C_Valid			C_Invalid		C_Error	
C_KeyUp   			�Ϸ���                  ����            �ɿ�                  	
C_KeyDown   		�·���                  ����            �ɿ�                  	
C_KeyPrg   			��̼�                  ����            �ɿ�                  	
C_KeyOpenCover   	�����                  �ϸ�            ����                  	
C_KeyOpenTerminal	����β��                �ϸ�            ����                  	
C_CheckAuPower   	������Դ���            ����            δ����                 	
C_Magnetic       	�ų����                �дų�          �޴ų�                 	
C_MeterICIRQ     	����оƬIRQ�ж�         ���ж�          ���ж�                	
C_RelayStatus    	�̵���״̬���          �̵���ͨ        �Ͽ�                   	
C_ModuleStatus   	ģ�鷢��״ָ̬ʾ        ģ�鷢��        δ����                 	
C_CardStatus		�忨״̬���			�в忨			�޲忨 
C_ExternalRelayStatus ���ü̵������        ͨ              ��
����λ��: 																		
��    ע:	
        1.�����Ϸ���/�·���/��̼�/�忨,���жϵ�״̬����ЧC_Invalid��תΪ��ЧC_Validʱ,
            ͬʱ����Ϣ������Ӧ��ģ��,����ȥ����ʱ������
            �ú������������޸�,��20141028��ʱ����������2�β���Ч,�Գ�����е���,����ȥ��ʱ�䵽,
            ��������û��ִ�а�����Ϣ����,��ĳ������ģ������˱�����,�����̾��п��ܶ���Ϣ,���Խ����˱��ε���
        2.���ϵ�������ȡ����״̬�Ĺ���100ms��100ms�ڶ�ȡ����״̬��
            ����ʱ��100ms���ٸ����ú���һ����ȷ�Ŀ���״̬
        3.C_ExternalRelayStatus���ü̵���״̬����ֹSF_GetRelay0nOffStatus����ĺ�������
*********************************************************************************************************/
uchar8 InF_GetPeripheralStatus(uchar8 Peripheral)
{
	uchar8	V_ucReturn = C_Error;						/*����ֵ��ʼΪ������*/
	ulong32	i;
	uchar8 V_ucBuffer[2];
	/*******************************************************/
	/*�ж�100ms���ϵ����ʱ���Ƿ�*/
	for(i = 0; i < 100; i++)									/*�����ʱ100ms*/
	{
		if( SV_TimerShut100ms == 0 )
		{
			break;
		}
		InF_Delay_us(1000);
	}
	/*******************************************************/
	switch( Peripheral )
	{
		/*******************************************************/
		case C_KeyUp:									/*�Ϸ���״̬*/
		{
			if( Str_KeyUp.Timer >= C_Interval_50ms )
			{
				if(Str_KeyUp.HStatus == C_Valid )
				{
					Str_KeyUp.HStatus = C_Invalid;
				}
				else
				{
					Str_KeyUp.HStatus = C_Valid;
					/*����Ч��Ϊ��Ч,����Ϣ����ʾģ��*/
					V_ucBuffer[0] = Pt_Dispatch_Key;
					V_ucBuffer[1] = C_KeyUp;
					Dispatch_SendMessage(C_Msg_Display, V_ucBuffer, Pt_Dispatch_Key_Len + 1);
				}
				Str_KeyUp.Timer = 0;
			}
			V_ucReturn = Str_KeyUp.HStatus;
			break;
		}
		/*******************************************************/
		case C_KeyUpForRelay:									/*�Ϸ���״̬*/
		{
			if( Str_KeyUpPermit.Timer >= C_Interval_3000ms )
			{
				if(Str_KeyUpPermit.HStatus == C_Valid )
				{
					Str_KeyUpPermit.HStatus = C_Invalid;
				}
				else
				{
					Str_KeyUpPermit.HStatus = C_Valid;
					/*����Ч��Ϊ��Ч,����Ϣ���̵���ģ��*/
					V_ucBuffer[0] = Pt_Dispatch_Key;
					V_ucBuffer[1] = C_Key3s;
					Dispatch_SendMessage(C_Msg_Deal_RelayStatus, V_ucBuffer, Pt_Dispatch_Key_Len + 1);
				}
				Str_KeyUpPermit.Timer = 0;
			}
			V_ucReturn = Str_KeyUpPermit.HStatus;
			break;
		}
		/*******************************************************/
		case C_KeyDown:									/*�·���״̬*/
		{
			if( Str_KeyDown.Timer >= C_Interval_50ms )
			{
				if(Str_KeyDown.HStatus == C_Valid )
				{
					Str_KeyDown.HStatus = C_Invalid;
				}
				else
				{
					Str_KeyDown.HStatus = C_Valid;
					/*����Ч��Ϊ��Ч,����Ϣ����ʾģ��*/
					V_ucBuffer[0] = Pt_Dispatch_Key;
					V_ucBuffer[1] = C_KeyDown;
					Dispatch_SendMessage(C_Msg_Display, V_ucBuffer, Pt_Dispatch_Key_Len + 1);
				}
				Str_KeyDown.Timer = 0;
			}
			V_ucReturn = Str_KeyDown.HStatus;
			break;
		}
		/*******************************************************/
		case C_KeyDownForRelay:									/*�·���״̬*/
		{
			if( Str_KeyDownPermit.Timer >= C_Interval_3000ms )
			{
				if(Str_KeyDownPermit.HStatus == C_Valid )
				{
					Str_KeyDownPermit.HStatus = C_Invalid;
				}
				else
				{
					Str_KeyDownPermit.HStatus = C_Valid;
					/*����Ч��Ϊ��Ч,����Ϣ���̵���ģ��*/
					V_ucBuffer[0] = Pt_Dispatch_Key;
					V_ucBuffer[1] = C_Key3s;
					Dispatch_SendMessage(C_Msg_Deal_RelayStatus, V_ucBuffer, Pt_Dispatch_Key_Len + 1);
				}
				Str_KeyDownPermit.Timer = 0;
			}
			V_ucReturn = Str_KeyDownPermit.HStatus;
			break;
		}
		/******************************************************/
		case C_KeyOpenCover:							/*�����״̬*/
		{
			if( InF_ReadPowerState() == C_PowerOn )
			{
				if( Str_KeyOpenCover.Timer >= C_Interval_50ms )
				{
					if(Str_KeyOpenCover.HStatus == C_Valid )
					{
						Str_KeyOpenCover.HStatus = C_Invalid;
					}
					else
					{
						Str_KeyOpenCover.HStatus = C_Valid;
					}
					Str_KeyOpenCover.Timer = 0;
				}
				V_ucReturn = Str_KeyOpenCover.HStatus;
			}
			else
			{
				V_ucReturn = DF_GetIOStatus(C_KeyOpenCover);
			}
			break;
		}
		/*******************************************************/
		case C_KeyOpenTerminal:							/*����β��*/
		{
			if( InF_ReadPowerState() == C_PowerOn )
			{
				if( Str_KeyOpenTerminal.Timer >= C_Interval_50ms )
				{
					if(Str_KeyOpenTerminal.HStatus == C_Valid )
					{
						Str_KeyOpenTerminal.HStatus = C_Invalid;
					}
					else
					{
						Str_KeyOpenTerminal.HStatus = C_Valid;
					}
					Str_KeyOpenTerminal.Timer = 0;
				}
				V_ucReturn = Str_KeyOpenTerminal.HStatus;
			}
			else
			{
				V_ucReturn = DF_GetIOStatus(C_KeyOpenTerminal);
			}
			break;
		}
		/*******************************************************/
		case C_CheckAuPower:							/*������Դ������*/
		{
			if( Str_CheckAuPower.Timer >= C_Interval_50ms )
			{
				if(Str_CheckAuPower.HStatus == C_Valid )
				{
					Str_CheckAuPower.HStatus = C_Invalid;
				}
				else
				{
					Str_CheckAuPower.HStatus = C_Valid;
				}
				Str_CheckAuPower.Timer = 0;
			}
			V_ucReturn = Str_CheckAuPower.HStatus;
			break;
		}
		/*******************************************************/
		case C_Magnetic:								/*�ų����*/
		{
			if( Str_Magnetic.Timer >= C_Interval_50ms )
			{
				if(Str_Magnetic.HStatus == C_Valid )
				{
					Str_Magnetic.HStatus = C_Invalid;
				}
				else
				{
					Str_Magnetic.HStatus = C_Valid;
				}
				Str_Magnetic.Timer = 0;
			}
			V_ucReturn = Str_Magnetic.HStatus;
			break;
		}
		/*******************************************************/
		case C_MeterICIRQ:								/*����оƬIRQ����*/
		{
			if( Str_MeterICIRQ.Timer >= C_Interval_50ms )
			{
				if(Str_MeterICIRQ.HStatus == C_Valid )
				{
					Str_MeterICIRQ.HStatus = C_Invalid;
				}
				else
				{
					Str_MeterICIRQ.HStatus = C_Valid;
				}
				Str_MeterICIRQ.Timer = 0;
			}
			V_ucReturn = Str_MeterICIRQ.HStatus;
			break;
		}
		/*******************************************************/
		case C_RelayStatus:								/*���ü̵���״̬*/
		{
			if( Str_RelayStatus.Timer >= C_Interval_50ms )
			{
				if(Str_RelayStatus.HStatus == C_Valid )
				{
					Str_RelayStatus.HStatus = C_Invalid;
				}
				else
				{
					Str_RelayStatus.HStatus = C_Valid;
				}
				Str_RelayStatus.Timer = 0;
			}
			V_ucReturn = Str_RelayStatus.HStatus;
			break;
		}
        /*******************************************************/
		case C_ExternalRelayStatus:							            /*���ü̵���״̬*/
		{
			if( Str_ExternalRelayStatus.Timer >= C_ExRelayInvaildNum )  /*������ü̵���״̬������SF_GetRelay0nOffStatus()������������ֹ����*/
			{
                Str_ExternalRelayStatus.HStatus = C_Valid;              /*�е͵�ƽ����20��˵���̵���ͨ*/
			}
            else
            {
                Str_ExternalRelayStatus.HStatus = C_Invalid;            /*һֱ�ߵ�ƽ˵���̵�����*/
            }
            V_ucReturn = Str_ExternalRelayStatus.HStatus;
            Str_ExternalRelayStatus.Timer = 0;
			break;
		}
		/*******************************************************/
		case C_ModuleStatus:							/*ģ������ͨ��״̬*/
		{
			if( Str_ModuleStatus.Timer >= C_Interval_50ms )
			{
				if(Str_ModuleStatus.HStatus == C_Valid )
				{
					Str_ModuleStatus.HStatus = C_Invalid;
				}
				else
				{
					Str_ModuleStatus.HStatus = C_Valid;
				}
				Str_ModuleStatus.Timer = 0;
			}
			V_ucReturn = Str_ModuleStatus.HStatus;
			break;
		}
		/*******************************************************/
		case C_CardStatus:							/*���޲忨״̬���*/
		{
			if( Str_CardStatus.Timer >= C_Interval_50ms )
			{
				if(Str_CardStatus.HStatus == C_Valid )
				{
					Str_CardStatus.HStatus = C_Invalid;
				}
				else
				{
					Str_CardStatus.HStatus = C_Valid;
					/*����Ч��Ϊ��Ч,����Ϣ��������ģ��*/
					V_ucBuffer[0] = Pt_CardFlag;
					V_ucBuffer[1] = C_InsertCard;
					Dispatch_SendMessage(C_Msg_Card, V_ucBuffer, Pt_Dispatch_Key_Len + 1);
				}
				Str_CardStatus.Timer = 0;
			}
			V_ucReturn = Str_CardStatus.HStatus;
			break;
		}
		default:
			;
			break;
		/*******************************************************/
	}
	return V_ucReturn;
}

///**************************************************************************************///
///*����ԭ�ͣ�uchar8 InF_RelayAct(uchar8 C_Act)											*///
///*�����������̵��������ӿں���                                                        *///
///*���������C_On����ʾ�̵����պϣ�C_Off����ʾ�̵����Ͽ�                               *///
///*������������ø��ɿ���:�����Ǳպϻ��ǶϿ�,ushort16 SV_InternalRelayActTime��ֵ      *///
///*	                   C_InternalRelayActTime=400ms��򿪼�ʱ������                 *///
///*          ���ø��ɿ���:�Ͽ���������ȡ���ݲ�ĵ������������1�����ÿ��ؿ��Ʒ�ʽȷ��  *///
///*                       ������ʽ����ƽʽ������ʽ�Ͽ���������Чʱ��ͨ����ȡ���ݲ��   *///
///*                       ����ʱ�丳ֵ���ö�ʱ�������أ���ƽʽ�Ͽ�/�պ϶�ֱ�Ӳ������ߣ�*///
///*                       �����ö�ʱ����                                               *///
///*          �պ϶�����ֱ���ͷſ��ߡ�                                                  *///
///*          ���ÿ��ض�ʱ��ushort16 SV_ExternalRelayTimer�����ء�                      *///
///*���ز�����C_Ok����ȷִ�У�C_Error����ڴ���                                         *///
///*����λ�ã��ú����ɷѿ�ģ�����                                                      *///
///*����˵����1�����ø���������ʱ��ֻ��Ҫ��ȷ�Ǽ̵����պϻ��ǶϿ�                       *///
///**************************************************************************************///
uchar8 InF_RelayAct(uchar8 C_Act)
{
	uchar8 V_ucTemp = C_Error;	///*����ֵ��Ϊ������ڲ�������ʱ�ŷ��ش���ֻҪ��ڲ�����ȷ�ͷ�����ȷ*///
	uchar8 V_DataBuff[4];
	ushort16 V_usLen, V_usDataEncode;
	
	switch( C_Act )
	{
 		///***********************************************************///
		case C_On:
		{
			DF_RelayControl(C_On);
			//SV_InternalRelayActTime = (C_TimerSwitch_16|C_Interval_400ms);	///*���ø��ɿ��ض���ʱ��*///
            SV_InternalRelayActTime = (C_TimerSwitch_16|C_Interval_150ms);	///*���ø��ɿ��ض���ʱ��,ͬ���ɶ���Ϊ150ms*///
			SV_ExternalRelayActTime = C_Interval_0ms;						///*���ø��ɿ��أ��պ�ʱ����Ҫ��ʱ*///
			V_ucTemp = C_OK;
			break;
		}
 		///***********************************************************///
		case C_Off:
		{
			V_ucTemp = C_OK;
			DF_RelayControl(C_Off);
			//SV_InternalRelayActTime = (C_TimerSwitch_16|C_Interval_400ms);			///*���ø��ɿ��ض���ʱ��*///
            SV_InternalRelayActTime = (C_TimerSwitch_16|C_Interval_150ms);			///*���ø��ɿ��ض���ʱ��,ͬ���ɶ���Ϊ150ms*///
			///*�����ݲ��ȡ������ʽ*///
			V_usLen = CLMeter_Work_Char1;
			if( InF_Read_Data(CMeter_Work_Char1,&V_DataBuff[0],&V_usLen, &V_usDataEncode) == C_OK )
			{
				if( (V_DataBuff[0] & C_PulseMode) == 0 )					///*����ʽ*///
				{
					///*��ȡ������*///
					V_usLen = CLExtern_Relay_PulW;
					if( InF_Read_Data(CExtern_Relay_PulW,&V_DataBuff[0],&V_usLen, &V_usDataEncode) == C_OK )
					{
						SV_ExternalRelayActTime = V_DataBuff[1];
						SV_ExternalRelayActTime <<=8;
						SV_ExternalRelayActTime += V_DataBuff[0];
						SV_ExternalRelayActTime |= C_TimerSwitch_16;
					}
					else			///*Ĭ��Ϊ400ms*///
					{
						SV_ExternalRelayActTime = C_Interval_400ms;
						SV_ExternalRelayActTime |= C_TimerSwitch_16;
					}
				}
				else				///*��ƽʽ*///
				{
					SV_ExternalRelayActTime = C_Interval_0ms;
				}
			}
			break;
		}
 		///***********************************************************///
		default:
			;
		break;
	}
	
	return V_ucTemp;
}

///**********************************************************************************///
///*Function���๦�ܶ��������ʱ����ֵ*///
///**********************************************************************************///
void SF_Set_MultiFunctionTimer(uchar8 Timer)
{
	SV_Timer_MultiFunction = Timer;
}

///***********************************************************************************///
///*Function���ⲿ����/�豸�Ŀ���
///*Description��
///*Input��
///*												C_On			C_Off			*///
///*C_BackLight				����            		������			�ر���			*///
///*C_TripLed               ��բָʾ��              ָʾ����		ָʾ����        *///
///*C_Beep                  ������                  ��������		��������        *///
///*C_WarnOut               �����̵���              �б������		�ޱ������      *///
///*C_FlashPower            Flash��Դ����           �򿪵�Դ		�رյ�Դ        *///
///*C_CapCharge             �������ݳ�����        ������		�رճ��        *///
///*C_CapDischarge          �������ݷŵ����        ����ŵ�		��ֹ�ŵ�        *///
///*C_WakeUpPower           6V��ص�Դ����          �򿪵�Դ		�رյ�Դ        *///
///*C_BattDischarge         6V��ط��ۻ�����        ��			�ر�            *///
///*C_EventOut              �����ϱ�                �����ϱ�		�ر��ϱ�        *///
///*C_ModuleReset           ģ�鸴λ                ģ�鸴λ		ģ��ʹ��        *///
///*C_ModuleSet             ģ������                ģ������		�����ͷ�        *///
///*C_InfraPower			������յ�Դ			�򿪵�Դ		�رյ�Դ		*///
///*C_EsamPower             ESAM��Դ                �򿪵�Դ		�رյ�Դ        *///
///*C_CardPower             CARD��Դ                �򿪵�Դ		�رյ�Դ        *///
///*C_EsamReset				ESAM��λ  				ESAM��λ		ESAMʹ��  		*///
///*C_CardSck               ��ʱ��ʹ��              ��ʱ��ʹ��		��ʱ�ӽ�ֹ      *///
///*C_CardReset             ����λ                  ����λ			��ʹ��          *///
///*Output��
///*Return��C_Error:��ڲ�������C_OK:��ȷִ��
///*Calls��
///*Called By��
///*Influence���ú����������ж������
///*Tips��
///*Others��
///***********************************************************************************///
uchar8 InF_SwithPeripherals(uchar8 Peripherals,uchar8 Act)
{
	uchar8 V_ucTemp = C_Error;	///*����ֵ��Ϊ������ڲ�������ʱ�ŷ��ش���ֻҪ��ڲ�����ȷ�ͷ�����ȷ*///
		
	switch(Peripherals)			///*�����ĸ��������豸*///
	{
 		case C_BackLight:		///*�����������:����Ҫ��ʱ��*///
		{
 			switch(Act)
 			{
 				case C_On:		///*�������*///
 				{
 					SwitchOn_BackLight();
 					V_ucTemp = C_OK;
 					break;
 				}
 				case C_Off:		///*����Ϩ��*///
 				{
 					SwitchOff_BackLight();
 					V_ucTemp = C_OK;
 					break;
 				}
 				default:
 					;
 				break;
 			}
 			break;
		}
 		///***********************************************************///
 		case C_TripLed:			///*��բָʾ��*///
		{
 			switch(Act)
 			{
 				case C_On:		///*��բ�Ƶ���*///
 				{
 					SwitchOn_TripLed();
 					V_ucTemp = C_OK;
 					break;
 				}
 				case C_Off:		///*��բ��Ϩ��*///
 				{
 					SwitchOff_TripLed();
 					V_ucTemp = C_OK;
 					break;
 				}
 				default:
 					;
 				break;
 			}
 			break;
		}
 		///***********************************************************///
 		///***********************************************************///
 		case C_Beep:			///*������*///
		{
 			switch(Act)
 			{
 				case C_On:		///*��������*///
 				{
 					DF_SwitchOn_Beeper();
 					V_ucTemp = C_OK;
 					break;
 				}
 				case C_Off:		///*�������ر�*///
 				{
 					DF_SwitchOff_Beeper();
 					V_ucTemp = C_OK;
 					break;
 				}
 				default:
 					;
 				break;
 			}
 			break;
		}
 		///***********************************************************///
 		case C_WarnOut:			///*�������*///
		{
 			switch(Act)
 			{
 				case C_On:		///*�����̵����պ�*///
 				{
 					SwitchOn_WarnOut();
 					V_ucTemp = C_OK;
 					break;
 				}
 				case C_Off:		///*�����̵����Ͽ�*///
 				{
 					SwitchOff_WarnOut();
 					V_ucTemp = C_OK;
 					break;
 				}
 				default:
 					;
 				break;
 			}
 			break;
		}
 		///***********************************************************///
 		case C_FlashPower:		///*Flash��Դ����*///
		{
 			switch(Act)
 			{
 				case C_On:		///*Flash��Դ��*///
 				{
 					SwitchOn_FlashPower();
 					V_ucTemp = C_OK;
 					break;
 				}
 				case C_Off:		///*Flash��Դ�ر�*///
 				{
 					SwitchOff_FlashPower();
 					V_ucTemp = C_OK;
 					break;
 				}
 				default:
 					;
 				break;
 			}
 			break;
		}
 		///***********************************************************///
 		case C_CapCharge:		///*�������ݳ�����*///
		{
 			switch(Act)
 			{
 				case C_On:		///*�������ݳ��ʹ��*///
 				{
 					SuperCapCharge_En();
 					V_ucTemp = C_OK;
 					break;
 				}
 				case C_Off:		///*�������ݳ���ֹ*///
 				{
 					SuperCapCharge_Dis();
 					V_ucTemp = C_OK;
 					break;
 				}
 				default:
 					;
 				break;
 			}
 			break;
		}
 		///***********************************************************///
 		case C_CapDischarge:	///*�������ݷŵ����*///
		{
 			switch(Act)
 			{
 				case C_On:		///*�������ݷŵ�ʹ��*///
 				{
 					SwitchOn_SuperCapPower();
 					V_ucTemp = C_OK;
 					break;
 				}
 				case C_Off:		///*�������ݷŵ��ֹ*///
 				{
 					SwitchOff_SuperCapPower();
 					V_ucTemp = C_OK;
 					break;
 				}
 				default:
 					;
 				break;
 			}
 			break;
		}
 		///***********************************************************///
 		case C_WakeUpPower:		///*6V��ص�Դ����*///
		{
 			switch(Act)
 			{
 				case C_On:		///*6V��ص�Դ���ƣ���*///
 				{
 					SwitchOn_WakeUpPower();
 					V_ucTemp = C_OK;
 					break;
 				}
 				case C_Off:		///*6V��ص�Դ���ƣ��ر�*///
 				{
 					SwitchOff_WakeUpPower();
 					V_ucTemp = C_OK;
 					break;
 				}
 				default:
 					;
 				break;
 			}
 			break;
		}
 		///***********************************************************///
 		case C_BattDischarge:	///*6V��ط��ۻ�����*///
		{
 			switch(Act)
 			{
 				case C_On:		///*6V��ط��ۻ����ƣ��ŵ�*///
 				{
// 					SwitchOn_PreventBlunt();
 					V_ucTemp = C_OK;
 					break;
 				}
 				case C_Off:		///*6V��ط��ۻ����ƣ��رշŵ�*///
 				{
// 					SwitchOff_PreventBlunt();
 					V_ucTemp = C_OK;
 					break;
 				}
 				default:
 					;
 				break;
 			}
 			break;
		}
 		///***********************************************************///
 		case C_EventOut:		///*�����ϱ�*///
		{
 			switch(Act)
 			{
 				case C_On:		///*�����ϱ�*///
 				{
 					EventOut_EN();
 					V_ucTemp = C_OK;
 					break;
 				}
 				case C_Off:		///*�ر������ϱ�*///
 				{
 					EventOut_DIS();
 					V_ucTemp = C_OK;
 					break;
 				}
 				default:
 					;
 				break;
 			}
 			break;
		}
 		///***********************************************************///
 		case C_ModuleReset:		///*ģ�鸴λ*///
		{
 			switch(Act)
 			{
 				case C_On:		///*��λģ��*///
 				{
 					DF_SwitchOff_ModuleEn();
 					SV_Timer_ModuleReset = (C_Interval_300ms|C_TimerSwitch_8);
 					V_ucTemp = C_OK;
 					break;
 				}
 				case C_Off:		///*ʹ��ģ��*///
 				{
 					DF_SwitchOn_ModuleEn();
 					V_ucTemp = C_OK;
 					break;
 				}
 				default:
 					;
 				break;
 			}
 			break;
		}
 		///***********************************************************///
 		case C_ModuleSet:		///*ģ������*///
		{
 			switch(Act)
 			{
 				case C_On:		///*ģ������*///
 				{
 					ModuleSet_EN();
 					V_ucTemp = C_OK;
 					break;
 				}
 				case C_Off:		///*ģ�������ͷ�*///
 				{
 					ModuleSet_DIS();
 					V_ucTemp = C_OK;
 					break;
 				}
 				default:
 					;
 				break;
 			}
 			break;
		}
 		///***********************************************************///
 		case C_InfraPower:		///*������յ�Դ*///
		{
 			switch(Act)
 			{
 				case C_On:		///*������յ�Դ����*///
 				{
 					SwitchOn_InfrarxPower();
 					V_ucTemp = C_OK;
 					break;
 				}
 				case C_Off:		///*������յ�Դ���ر�*///
 				{
 					SwitchOff_InfrarxPower();
 					V_ucTemp = C_OK;
 					break;
 				}
 				default:
 					;
 				break;
 			}
 			break;
		}
 		///***********************************************************///
// 		case C_EsamPower:		///*ESAM��Դ*///
//		{
// 			switch(Act)
// 			{
// 				case C_On:		///*ESAM��Դ����*///
// 				{
// 					SwitchOn_EsamPower();
// 					V_ucTemp = C_OK;
// 					break;
// 				}
// 				case C_Off:		///*ESAM��Դ���ر�*///
// 				{
// 					SwitchOff_EsamPower();
// 					V_ucTemp = C_OK;
// 					break;
// 				}
// 				default:
// 					;
// 				break;
// 			}
// 			break;
//		}
// 		///***********************************************************///
// 		case C_CardPower:		///*CARD��Դ*///
//		{
// 			switch(Act)
// 			{
// 				case C_On:		///*CARD��Դ����*///
// 				{
// 					SwitchOn_CardPower();
// 					V_ucTemp = C_OK;
// 					break;
// 				}
// 				case C_Off:		///*CARD��Դ���ر�*///
// 				{
// 					SwitchOff_CardPower();
// 					V_ucTemp = C_OK;
// 					break;
// 				}
// 				default:
// 					;
// 				break;
// 			}
// 			break;
//		}
// 		///***********************************************************///
// 		case C_EsamReset:		///*ESAM��λ*///
//		{
// 			switch(Act)
// 			{
// 				case C_On:		///*ESAM��λ*///
// 				{
// 					Esam_Reset();
// 					V_ucTemp = C_OK;
// 					break;
// 				}
// 				case C_Off:		///*ESAMʹ��*///
// 				{
// 					Esam_EN();
// 					V_ucTemp = C_OK;
// 					break;
// 				}
// 				default:
// 					;
// 				break;
// 			}
// 			break;
//		}
// 		///***********************************************************///
// 		case C_CardSck:			///*��ʱ��ʹ��*///
//		{
// 			switch(Act)
// 			{
// 				case C_On:		///*��ʱ��ʹ��*///
// 				{
// 					CardSck_EN();
// 					V_ucTemp = C_OK;
// 					break;
// 				}
// 				case C_Off:		///*��ʱ�ӽ�ֹ*///
// 				{
// 					CardSck_DIS();
// 					V_ucTemp = C_OK;
// 					break;
// 				}
// 				default:
// 					;
// 				break;
// 			}
// 			break;
//		}
// 		///***********************************************************///
// 		case C_CardReset:		///*����λ*///
//		{
// 			switch(Act)
// 			{
// 				case C_On:		///*����λ*///
// 				{
// 					Card_Reset();
// 					V_ucTemp = C_OK;
// 					break;
// 				}
// 				case C_Off:		///*��ʹ��*///
// 				{
// 					Card_EN();
// 					V_ucTemp = C_OK;
// 					break;
// 				}
// 				default:
// 					;
// 				break;
// 			}
// 			break;
//		}
 		///***********************************************************///
 		///***********************************************************///
 		case C_MeterICPower:		///*����оƬ��Դ*///
		{
 			switch(Act)
 			{
 				case C_On:		///*����λ*///
 				{
 					DF_SwitchOn_EMeterIcPower();
 					V_ucTemp = C_OK;
 					break;
 				}
 				case C_Off:		///*��ʹ��*///
 				{
 					DF_SwitchOff_EMeterIcPower();
 					V_ucTemp = C_OK;
 					break;
 				}
 				default:
 					;
 				break;
 			}
 			break;
		}
 		///***********************************************************///
 		
 		
 		
 		
 		default:
 			;
 			break;
	}
	return V_ucTemp;
}
/*******************************************************************************
����ԭ�ͣ� ulong32 Inf_PowerDownTime(void)
��������������͹��ķ��������ϱ��õĶ�ʱ��
���������
���������
���ز����� ��ʱ����ֵ
����λ�ã� 
��    ע�� 
*******************************************************************************/
ulong32 Inf_PowerDownTime(void)
{
    return SV_PowerDownReportTime;
}
/*******************************************************************************
����ԭ�ͣ� void Inf_ClearPowerDownTime(void)
��������������͹��ķ��������ϱ��õĶ�ʱ������
���������
���������
���ز����� 
����λ�ã� 
��    ע�� 
*******************************************************************************/
void Inf_ClearPowerDownTime(void)
{
    SV_PowerDownReportTime = 0;
}
/*******************************************************************************
����ԭ�ͣ� ulong32 Inf_Get_PowerOffShutAcReportTime(void)
�����������ϵ���1Сʱ��־
���������
���������
���ز����� ��ʱ����ֵ
����λ�ã� 
��    ע�� 
*******************************************************************************/
ulong32 Inf_Get_PowerOffShutAcReportTime(void)
{
    return SV_PowerOffShutAcReportTime;
}
/*******************************************************************************
����ԭ�ͣ� uchar8 Inf_SatisfyPowerOnTime(void)
����������������1Сʱ����OK�����㷵�ش���
���������
���������
���ز����� OK:��һСʱ��C_Error������һСʱ
����λ�ã� 
��    ע�� 
*******************************************************************************/
uchar8 Inf_SatisfyPowerOnTime(void)
{
    uchar8  V_Return = C_Error;
    
    if(SV_PowerOffShutAcReportTime >= C_Interval_1hour)
    {
        V_Return = C_OK;
    }
    return V_Return;
}
/*******************************************************************************
����ԭ�ͣ� void Inf_Clear_PowerOffShutAcReportTime(void)
�����������ϵ���1Сʱ��ʱ������
���������
���������
���ز����� 
����λ�ã� 
��    ע�� 
*******************************************************************************/
void Inf_Clear_PowerOffShutAcReportTime(void)
{
    SV_PowerOffShutAcReportTime = 0;
}
///***********************************************************************************///
///*Function��*///
///*Description���ϵ��ʼ��ʱ����,���ڳ�ʼ��������ʱ��*///
///*Input��*///
///*Output��*///
///*Calls��*///
///*Called By��*///
///*Influence��*///
///*Tips��*///
///*Others��*///
///*Author:zhiyong.gu*///
///***********************************************************************************///
void InF_InitTimer(void)
{
	SV_TimerBasedTickTimer_1000ms = 0;			///*���ڻ������Ķ�ʱ����1s��ʱ��*///
	SV_TimerBasedTickTimer_500ms = 0;			///*���ڻ������Ķ�ʱ����500ms��ʱ��*///
	SV_TimerBasedTickTimer_100ms = 0;			///*���ڻ������Ķ�ʱ����100ms��ʱ��*///
	SV_TimerShut100ms = C_Interval_100ms;		///*����100ms��ʱ��*///
	SV_TimerShutRealTimeData = C_ShutRealTimeData;	///*����2s��ʱ��*///
	
	SV_TimerFeedWatchdog = 0;					///*���Ź���ʱ������*///
	
	Str_KeyUp.Timer = 0;						///*�Ϸ���*///
	Str_KeyDown.Timer = 0;						///*�·���*///
	Str_KeyPrg.Timer = 0;						///*��̼�*///
	Str_KeyOpenCover.Timer = 0;					///*�����*///
	Str_KeyOpenTerminal.Timer = 0;				///*����β��*///
	SV_PowerDownReportTime = 0x00;				///*�͹������ϱ�ʱ������*///
	Str_CheckAuPower.Timer = 0;					///*������Դ������*///
	Str_Magnetic.Timer = 0;						///*�ų����*///
	Str_MeterICIRQ.Timer = 0;					///*����оƬIRQ����*///
	Str_RelayStatus.Timer = 0;					///*�̵���״̬*///
	Str_ExternalRelayStatus.Timer = 0;			///*���ü̵���״̬*///
	Str_ModuleStatus.Timer = 0;					///*ģ������ͨ��״̬*///
	Str_CardStatus.Timer = 0;					///*�忨״̬*///
	Str_KeyUpPermit.Timer = 0;					///*�Ϸ�����բ����3s*///
	Str_KeyDownPermit.Timer = 0;				///*�·�����բ����3s*///
	
	Str_KeyUp.HStatus = C_Valid;				///*�Ϸ���*///
	Str_KeyDown.HStatus = C_Valid;				///*�·���*///
	Str_KeyPrg.HStatus = C_Invalid;				///*��̼�*///
	Str_KeyOpenCover.HStatus = C_Invalid;		///*�����*///
	Str_KeyOpenTerminal.HStatus = C_Invalid;	///*����β��*///
	Str_CheckAuPower.HStatus = C_Invalid;		///*������Դ������*///
	Str_Magnetic.HStatus = C_Invalid;			///*�ų����*///
	Str_MeterICIRQ.HStatus = C_Invalid;			///*����оƬIRQ����*///
	Str_RelayStatus.HStatus = C_Invalid;		///*�̵���״̬*///
	Str_ExternalRelayStatus.HStatus = C_Invalid;		///*���ü̵����ߵ͵�ƽ��Ĭ�ϸߵ�ƽ�����20m��״̬û�б仯���ǶϿ�*///  
	
	Str_ModuleStatus.HStatus = C_Invalid;		///*ģ������ͨ��״̬*///
	Str_CardStatus.HStatus = C_Invalid;			///*�忨״̬*///
	Str_KeyUpPermit.HStatus = C_Invalid;		///*�Ϸ�����բ����3s*///
	Str_KeyDownPermit.HStatus = C_Invalid;		///*�·�����բ����3s*///

//	SV_TimerFeedWatchdog = 0;					///*���Ź���ʱ������*///

	SV_TimerPowerOn = 0;						///*�ϵ��ʱ������������Ƶ�����µ�*///
		
//	SF_LowpowerTimerStop();						///*�͹��Ļ�������ֹͣ*///

	SV_BeeperAct = C_NotDisplay;
	SV_BeeperTime = 0;
	SV_BeeperCycle = 0;
	SV_BeeperReverseTime = 0;
	
	SV_Timer_Delay = 0;
	
	SF_GetMeterType();
	SV_RCHFTemp=0;///*�¶�����
	
	if(C_Cap_OpenAfter30min == C_Cap_OpenAfter30min_En)	
	{
		SV_usSuperCapCharge_Time = C_PowerOn_30min;						/*�ϵ��ʱ�������ڿ����������ݳ��*/		
	}
	else
	{
		SV_usSuperCapCharge_Time = C_PowerOn_3s;						/*�ϵ��ʱ�������ڿ����������ݳ��*/	
	}

	
	
//	Str_KeyUp.Timer = C_InitialValue_150ms;				///*�Ϸ���*///
//	Str_KeyDown.Timer = C_InitialValue_150ms;			///*�·���*///
//	Str_KeyPrg.Timer = C_InitialValue_150ms;			///*��̼�*///
//	Str_KeyOpenCover.Timer = C_InitialValue_150ms;		///*�����*///
//	Str_KeyOpenTerminal.Timer = C_InitialValue_150ms;	///*����β��*///
//	Str_CheckAuPower.Timer = C_InitialValue_150ms;		///*������Դ������*///
//	Str_Magnetic.Timer = C_InitialValue_150ms;			///*�ų����*///
//	Str_MeterICIRQ.Timer = C_InitialValue_150ms;		///*����оƬIRQ����*///
//	Str_RelayStatus.Timer = C_InitialValue_150ms;		///*�̵���״̬*///
//	Str_ModuleStatus.Timer = C_InitialValue_150ms;		///*ģ������ͨ��״̬*///
//	Str_CardStatus.Timer = C_InitialValue_150ms;		///*�忨״̬*///
//	
//	Str_KeyUpPermit.Timer = C_InitialValue_3150ms;		///*�Ϸ�����բ����3s*///
//	Str_KeyDownPermit.Timer = C_InitialValue_3150ms;	///*�·�����բ����3s*///

}

///**************************************************************************************************///
///*����ԭ�ͣ�void InF_Delay_us(ulong32 Delay_Num)                                                  *///
///*���������Delay_Num����ʱ���ݡ�����ʱ��usΪ��ʱ��λ����ʱ��,�ò�����ʹ�������н��к궨�壬      *///
///*������ͨ���ļ��С�����ڲ���Ϊ16���������ɵ����߽���ת��                                        *///
///*�����������                                                                                    *///
///*���ز�������                                                                                    *///
///*����˵������usΪ��λ������ʱ������ʱ���ڸýӿں��������ȡ�                                      *///
///*��    ע��                                                                                      *///
	///*1������ʱ�����迼�ǽ�/������ʱ�䡢���ö�ʱ��ʱ�䡢����ָ��ִ��ʱ�䣨��Ҫ����)��             *///
	///*2������ʱ�������ر��жϣ��������ʱ�����з����ж���ʱʱ��ͳ���Ԥ�ڣ����ڵײ����û��Ӱ�죩 *///
	///*3���ú����Ͻ��жϵ���																	    *///
	///*4����Ϊ������ִ��ʱ��Ĺ�ϵ������ʱ�����������50us���ϵ���ʱ                 		    *///
	///*5) �����ʱ���ܳ���1048575us
///**************************************************************************************************///
#define C_Delay_1us 16000000/1000000

void InF_Delay_us(ulong32 Delay_Num)
{
	ulong32 V_Delay_Num;
	ulong64 V_Temp;
//	SwitchOn_BackLight();
	if((0 == Delay_Num)||(Delay_Num>1048575))///*����V_Temp���ܴ���0xFFFFFF��Fcpu 22020096���õ�1048575
	{
		return;
	}
	///*SysTick��ʱ��ԴΪFcpu/2����22020096/2  MHz*///
	V_Temp=Delay_Num;
	V_Temp=V_Temp*C_Delay_1us;
	
	if(V_Temp>0xFFFFFF)///*����SysTick ������ֻ��24 λ���û��豣֤ticks ���ܳ���0xFFFFFF��
	{
		return;
	}
	V_Delay_Num=(ulong32)V_Temp;
//	SysTick_Config(V_Delay_Num);///*�⺯��
	SysTick->CTRL = 0;
	SysTick->LOAD = V_Delay_Num-1;		
	SysTick->VAL = 0;
	SysTick->CTRL |= SysTick_ENABLE;

	while( (SysTick->CTRL & SysTick_COUNTFLAG) != SysTick_COUNTFLAG )
	{
		if( 0 == SysTick->LOAD )
		{
			break;
		}
	}
	
	SysTick->CTRL = 0;
//	SwitchOff_BackLight();
}

///**************************************************************************************************///
///*����ԭ�ͣ�uchar8 InF_Delay_us_Start(ulong32 Delay_Num)                                                  *///
///*���������Delay_Num����ʱ���ݡ�����ʱ��usΪ��ʱ��λ����ʱ��,�ò�����ʹ�������н��к궨�壬      *///
///*������ͨ���ļ��С�����ڲ���Ϊ16���������ɵ����߽���ת��                                        *///
///*�����������                                                                                    *///
///*���ز�������                                                                                    *///
///*����˵������usΪ��λ������ʱ���ú���������ʱ                                    *///
///*��    ע��                                                                                      *///
	///*1������ʱ�����迼�ǽ�/������ʱ�䡢���ö�ʱ��ʱ�䡢����ָ��ִ��ʱ�䣨��Ҫ����)��             *///
	///*2������ʱ�������ر��жϣ��������ʱ�����з����ж���ʱʱ��ͳ���Ԥ�ڣ����ڵײ����û��Ӱ�죩 *///
	///*3���ú����Ͻ��жϵ���																	    *///
	///*4����Ϊ������ִ��ʱ��Ĺ�ϵ������ʱ�����������50us���ϵ���ʱ                 		    *///
	///*5) �����ʱ���ܳ���761904us
///**************************************************************************************************///
void InF_Delay_us_Start(ulong32 Delay_Num)
{
	ulong32 V_Delay_Num;
	ulong64 V_Temp;
	
	if((0 == Delay_Num)||(Delay_Num>1048575))///*����V_Temp���ܴ���0xFFFFFF��Fcpu 22020096���õ�761904
	{
		return;
	}
	///*SysTick��ʱ��ԴΪFcpu/2����22020096/2  MHz*///
	V_Temp=Delay_Num;
	V_Temp=V_Temp*C_Delay_1us;
	
	if(V_Temp>0xFFFFFF)///*����SysTick ������ֻ��24 λ���û��豣֤ticks ���ܳ���0xFFFFFF��
	{
		return;
	}
	V_Delay_Num=(ulong32)V_Temp;
//	SysTick_Config(V_Delay_Num);///*�⺯��
	SysTick->CTRL = 0;
	SysTick->LOAD = V_Delay_Num-1;		
	SysTick->VAL = 0;
	SysTick->CTRL |= SysTick_ENABLE;
}

void InF_Delay_us_Stop( void )
{
	///*SysTick��ʱ��ԴΪHCLK����ϵͳ������Ϊ2MHz*///
	//SysTick->CTRL &= SysTick_CLKSource_HCLK_Div8;
	SysTick->CTRL = 0;
	SysTick->VAL = 0;

}
///**************************************************************************************************///
///*����ԭ�ͣ�uchar8 InF_Delay_us_Finish( void )                                                  *///
///*�����������      *///
///*�����������                                                                                    *///
///*���ز�����C_OK:��ʱʱ�䵽;C_Error:��ʱδ��                                                                                    *///
///*����˵������usΪ��λ������ʱ�����øú���ʱ������ʱʱ���Ƿ�                                    *///
///*��    ע��                                                                                      *///
	///*1����ʱδ��,ֻ���ر�־             *///
	///*2����ʱʱ�䵽���رն�ʱ��,��������ʱʱ�䵽��־                 		    *///
///**************************************************************************************************///
uchar8 InF_Delay_us_Finish( void )
{
	
	if( (SysTick->CTRL & SysTick_COUNTFLAG) != SysTick_COUNTFLAG )
	{
		return C_Error;
	}
	else
	{
		SysTick->CTRL = 0;
		return C_OK;
	}
}

///**************************************************************************************************///
///*����ԭ�ͣ�void InF_SysTickDelay_1s(void)                                                  *///
///*�����������      *///
///*�����������                                                                                    *///
///*���ز�������                                                                                    *///
///*����˵������systick��ʱ��������Ϊ1s��ʱ������CARD/ESAMͨ�ŵĳ�ʱ����                            *///
///*��    ע��                                                                                      *///
	///*1���ú�������ʱ�����ʱ������Ϊ1s             *///
	///*2��1s������������־SysTick_COUNTFLAG *///
	///*3���ú����Ͻ��жϵ���																	    *///
///**************************************************************************************************///
void InF_SysTickDelay_1s(void)
{
	///*SysTick��ʱ��ԴΪHCLK����ϵͳ������Ϊ2MHz*///
	//SysTick->CTRL &= SysTick_CLKSource_HCLK_Div8;
	SysTick->CTRL = 0;
	SysTick->LOAD = 16000000;		///*1s��ʱ*///
	SysTick->VAL = 0;
	SysTick->CTRL |= SysTick_ENABLE;
	///*test
//	SwitchOn_TripLed();///*test
//	while( (SysTick->CTRL & SysTick_COUNTFLAG) != SysTick_COUNTFLAG )
//	{
//		if( 0 == SysTick->LOAD )
//		{
//			break;
//		}
//	}
//	SwitchOff_TripLed();///*test
}

///**************************************************************************************************///
///*����ԭ�ͣ�void InF_Delay_1s(void)                                                  *///
///*�����������      *///
///*�����������                                                                                    *///
///*���ز�����C_OK:��ʱʱ��δ��;C_Error:��ʱʱ���ѵ�                                                *///
///*����˵������systick��ʱ��������Ϊ1s��ʱ������CARD/ESAMͨ�ŵĳ�ʱ����                            *///
///*��    ע��                                                                                      *///
	///*1���ú�������ʱ�����ʱ������Ϊ1s             *///
	///*2��1s������������־SysTick_COUNTFLAG *///
	///*3���ú����Ͻ��жϵ���																	    *///
///**************************************************************************************************///
uchar8 InF_JudgeDelay_1s(void)
{
	if( SysTick->CTRL & SysTick_COUNTFLAG )
	{
		SysTick->CTRL = 0;
		return C_Error;
	}
	else
	{
		if( 0 == SysTick->LOAD )
		{
			SysTick->CTRL = 0;
			return C_Error;
		}
	}
	return C_OK;
}
///**************************************************************************************************///
///*����ԭ�ͣ�void InF_Delay_2us                                                                    *///
///*�����������                                                                                    *///
///*�����������                                                                                    *///
///*���ز�������                                                                                    *///
///*����˵������ʱ2us������ʱ���ڸýӿں��������ȡ�                                                 *///
///**************************************************************************************************///
void InF_Delay_2us(void)
{
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
}

///************************************************************************///
///*����ԭ��:void InF_ClrWatchDogTimer(void)*///
///*��������:�����Ź�*///
///*�������:��*///
///*�������:��*///
///*���ز���:�����ˣ�����C_Error��û�е��磬����C_OK*///
///*����ʱ����*///
///*��ע:*///
///************************************************************************///
void InF_ClrWatchDogTimer(void)
{
//	if( SV_TimerFeedWatchdog < C_WatchDog_FeedOut )
//	{
		SV_TimerFeedWatchdog = 0;
//	}
}

/*******************************************************************************
����ԭ�ͣ�void InF_DealWith5ms(void)
������������
�����������
�����������
���ز�������
����λ�ã�������ÿ��ѭ�������øú���������5ms�Ƿ񵽵��жϣ��������5ms��ص�һ�Ѵ���
��    ע��
*******************************************************************************/
void InF_DealWith5ms(void)
{
	uchar8 V_ucBuffer[5];
	ushort16 usTemp, V_usDataEncode;
	ulong32 ulTemp;
	uchar8 ucTemp[CLMeter_Temp];
    
	/**********************************/
	/*����100ms����������һ����ʱ��6.42ms*/
		
	if( SV_TimerBasedTickTimer_100ms >= C_Interval_100ms )
	{
		SV_TimerBasedTickTimer_100ms = 0;
#if 0		
		if(GV_ucGetADC_Flag == C_GetADC_On)
		{
#endif
            SF_ADC_Set(C_ADC_CmpAndJec);
#if 0		
        }
#endif

        /*2020��׼�����ϱ�2005*/
        {
            V_ucBuffer[0] = Pt_Dispatch_Timing;
            V_ucBuffer[1] = C_100MS;
            Dispatch_SendMessage(C_Msg_Communication, V_ucBuffer, (Pt_Dispatch_Timing_Len + 1));
        }
	}
	
	/**********************************/
	/*���洦��500ms�����ڵ����飺����500ms��ʱ��ֱ�ӱ�����*/
	if( SV_TimerBasedTickTimer_500ms >= C_Interval_500ms )
	{
		SV_TimerBasedTickTimer_500ms = 0;
        
		/*500ms��������Ϣ����ʾģ�顢ͨ��ģ�顢�̵���ģ�顢����ģ�顢���ȶ�ȡRTC�����ܼ���*/
		V_ucBuffer[0] = Pt_Dispatch_Timing;
		V_ucBuffer[1] = C_HalfSecond;
        
		Dispatch_SendMessage(C_Msg_Dispatch, V_ucBuffer, (Pt_Dispatch_Timing_Len + 1) );
		
		Dispatch_SendMessage(C_Msg_Display, V_ucBuffer, (Pt_Dispatch_Timing_Len + 1) );
		
		Dispatch_SendMessage(C_Msg_Communication, V_ucBuffer, (Pt_Dispatch_Timing_Len + 1) );
		
		Dispatch_SendMessage(C_Msg_Deal_RelayStatus, V_ucBuffer, (Pt_Dispatch_Timing_Len + 1) );
		
		Dispatch_SendMessage(C_Msg_MeterIC, V_ucBuffer, (Pt_Dispatch_Timing_Len + 1) );
		
		Dispatch_SendMessage(C_Msg_EnergyMetering, V_ucBuffer, (Pt_Dispatch_Timing_Len + 1) );
		
		SF_GetMeterType();		/*��ȡ���ͨ������:ģ����Ƿ�ģ���*/
		SF_UartOvertime();		/*���ڳ�ʱ����*/
	}
    
	/**************************************/
	if( SV_TimerBasedTickTimer_1000ms >= C_Interval_1000ms )
	{
		SV_TimerBasedTickTimer_1000ms = 0;
        
		/*1s��������Ϣ��A/Dת��ģ�飬���е�ص�ѹ����*/
		V_ucBuffer[0] = Pt_Dispatch_Timing;
		V_ucBuffer[1] = C_SecondChange;
		Dispatch_SendMessage(C_Msg_BatteryVoltagleMetering, V_ucBuffer, (Pt_Dispatch_Timing_Len + 1));
        
		/*ȫʧѹ����ģ��:ȫʧѹ���е��ʱ��Ҳ��,�ڴ����ʱ��������е粻����,��Դ����PowerOff�Ŵ���*/
		Dispatch_SendMessage(C_Msg_AllLossVoltage, V_ucBuffer, (Pt_AllLossVoltage_Len + 1) );
		
        if( InF_ReadPowerState() == C_PowerOn )
		{
			if(SV_TimerPowerOn < C_PowerOn_3s)			/*�ϵ��ʱ���Ƿ���3s*/
			{
				SV_TimerPowerOn++;			
			}
					
			if(SV_usSuperCapCharge_Time != 0x00)			/*�ϵ��ʱ���Ƿ���30min*/
			{
				SV_usSuperCapCharge_Time--;
				if( SV_usSuperCapCharge_Time == 0x00 )		/*�ϵ�30min�����е�������*/
				{
					DF_SwitchOn_SuperCapCharge(  );	    /*�������ݳ�硢�رշŵ�*/
					DF_SwitchOff_SuperCapPower(  );
				}
			}			
		}
		
		if(Inf_SatisfyPowerOnTime() != C_OK)                            /*�����ϱ�1Сʱ����ʱ��*/ 
		{
			if( C_OK == Inf_BackLightLimit() )                          /*��ѹ����Ҫ��Ŀǰ�ǡ�60%Un���������⡢�����̵���*/
			{
				SV_PowerOffShutAcReportTime++;         
			}
		}
		
		/*****************������չ�������Ϣ����*********************/
		V_ucBuffer[0] = Pt_Dispatch_Timing;
		Dispatch_SendMessage(C_Msg_DataProcess_External, V_ucBuffer, (Pt_DataProcess_Len + 1));
	}
	
	/**************************************/
	if( SV_TimerCruise >= C_Interval_5000ms )
	{
		SV_TimerCruise = 0;
	
		/*����Ϣ�����ݲ㣬����5sѲ������Ѳ�������Լ�����20min���ۼӱ������(�˴�����)*/
		V_ucBuffer[0] = Pt_Dispatch_Timing;
		Dispatch_SendMessage(C_Msg_DataProcess, V_ucBuffer, (Pt_DataProcess_Len + 1));
	
		InF_S_Dispatch_5s();		               /*��ȫģ��ÿ5s��һ��*/
	
		if( InF_ReadPowerState(  ) == C_PowerOn )  /*����32.768����RCHFУ��*/
		{						
			usTemp = CLMeter_Temp;
			if(InF_Read_Data(CMeter_Temp, &ucTemp[0], &usTemp, &V_usDataEncode) == C_OK)
			{
				if(ucTemp[1] & 0x80)						/*����*/
				{
					ucTemp[1] &= 0x7F;
				}	
	
				PF_BCDtoHexBytes(&ucTemp[0], &ulTemp, CLMeter_Temp);
				usTemp = (ushort16)ulTemp;

				if(SV_RCHFTemp > usTemp)
				{
					if( (SV_RCHFTemp - usTemp) >= 0x50 )	/*������5��*/
					{
						SV_RCHFTemp = usTemp;
						RCHF_Adj_Proc( );
					}					
				}
				else 
				{
					if((usTemp - SV_RCHFTemp) >= 0x50)
					{
						SV_RCHFTemp = usTemp;
						RCHF_Adj_Proc();
					}
				}
			}
			else 
			{
				RCHF_Adj_Proc();
			}
		}
	}
    
	/**************************************/
	if( SV_TimerCheckMcu >= C_Interval_1min )
	{
		SV_TimerCheckMcu = 0;
	
		/*���mcu�Ƿ�����������ֱ�ӵ��ýӿں���*/
		InF_SystemMonitor();
	
		/*ÿminУ��һ��RTC��SFR�Ƿ�����:ֱ�ӵ��ýӿں���*/
		InF_CheckRTC();
	
		/*����Ϣ������,����ÿ����һ�ε�RCУ׼*/
		V_ucBuffer[0] = Pt_CalibrateRC;
		Dispatch_SendMessage(C_Msg_CalibrateRC,V_ucBuffer,Pt_CalibrateRC_Len+1);
	}
    
	/**************************************/
	/*�����Ƕ��Ϸ���/�·���/��̼�/�忨�Ĵ���
	ֱ�ӵ���InF_GetPeripheralStatus( uchar8 )����,�ڴ˺�����,��������4������,
	ֱ���ж�ȥ��ʱ���Ƿ�,���ȥ��ʱ�䵽,��HStatus��ת,���жϷ�ת���״̬
	�����תΪ��Ч״̬,�򽫶�ʱ������,ͬʱ����Ϣ�������ģ��*/
	
	InF_GetPeripheralStatus( C_KeyUp );				/*�Ϸ�:���Ը���ʾģ��*/
	InF_GetPeripheralStatus( C_KeyUpForRelay );		/*�Ϸ�:����3s���̵���ģ��*/
	
	InF_GetPeripheralStatus( C_KeyDown );			/*�·�:���Ը���ʾģ��*/
	InF_GetPeripheralStatus( C_KeyDownForRelay );	/*�·�:����3s���̵���ģ��*/

#if 0	
	InF_GetPeripheralStatus( C_KeyPrg );			/*���:��ͨ��ģ��*/
#endif
	
	InF_GetPeripheralStatus( C_CardStatus );		/*�忨:��������ģ��*/

#if 0	
	if( Str_KeyUp.Timer >= C_Interval_50ms )
	{
		Str_KeyUp.Timer = 0;
		/*���Ϸ���������Ϣ����ʾģ��*/
		if( InF_GetPeripheralStatus( C_KeyUp ) == C_Valid )
		{
			V_ucBuffer[0] = Pt_Dispatch_Key;
			V_ucBuffer[1] = C_KeyUp;
			Dispatch_SendMessage(C_Msg_Display,V_ucBuffer,Pt_Dispatch_Key_Len+1);
		}
	}
	if( Str_KeyUpPermit.Timer >= C_Interval_3000ms )
	{
		Str_KeyUpPermit.Timer = 0;
		/*���Ϸ���3s��Ϣ���̵���ģ��*/
		if( InF_GetPeripheralStatus( C_KeyUpForRelay ) == C_Valid )
		{
			V_ucBuffer[0] = Pt_Dispatch_Key;
			V_ucBuffer[1] = C_Key3s;
			Dispatch_SendMessage(C_Msg_Deal_RelayStatus,V_ucBuffer,Pt_Dispatch_Key_Len+1);
		}
	}
	/**************************************/
	/*�·�������*///
	if( Str_KeyDown.Timer >= C_Interval_50ms )
	{
		Str_KeyDown.Timer = 0;
		/*���·���������Ϣ����ʾģ��*/
		if( InF_GetPeripheralStatus( C_KeyDown ) == C_Valid )
		{
			V_ucBuffer[0] = Pt_Dispatch_Key;
			V_ucBuffer[1] = C_KeyDown;
			Dispatch_SendMessage(C_Msg_Display,V_ucBuffer,Pt_Dispatch_Key_Len+1);
		}
	}
	if( Str_KeyDownPermit.Timer >= C_Interval_3000ms )
	{
		Str_KeyDownPermit.Timer = 0;
		/*���·���3s��Ϣ���̵���ģ��*/
		if( InF_GetPeripheralStatus( C_KeyDownForRelay ) == C_Valid )
		{
			V_ucBuffer[0] = Pt_Dispatch_Key;
			V_ucBuffer[1] = C_Key3s;
			Dispatch_SendMessage(C_Msg_Deal_RelayStatus,V_ucBuffer,Pt_Dispatch_Key_Len+1);
		}
	}
	/**************************************/
	/*��̼�����*/
	if( Str_KeyPrg.Timer >= C_Interval_50ms )
	{
		Str_KeyPrg.Timer = 0;
		/*����̼�������Ϣ����ʾģ��*/
		if( InF_GetPeripheralStatus( C_KeyPrg ) == C_Valid )
		{
			V_ucBuffer[0] = Pt_Dispatch_Key;
			V_ucBuffer[1] = C_KeyPrg;
			Dispatch_SendMessage(C_Msg_Communication,V_ucBuffer,Pt_Dispatch_Key_Len+1);
		}
	}
	/**************************************/
	/*�忨����*///
	if( Str_CardStatus.Timer >= C_Interval_50ms )
	{
		Str_CardStatus.Timer = 0;
		/*���в忨��Ϣ��ͨ��ģ��*/
		if( InF_GetPeripheralStatus( C_CardStatus ) == C_Valid )
		{
			V_ucBuffer[0] = Pt_CardFlag;
			V_ucBuffer[1] = C_InsertCard;
			Dispatch_SendMessage(C_Msg_Card,V_ucBuffer,Pt_Dispatch_Key_Len+1);
		}
	}
#endif
	/**************************************/
}

///***********************************************************************************///
///*Function���͹��Ļ��������ж�*///
///*Description��5ms�ж�һ��,ֱ�Ӳ���ȫ�ֱ�������++*///
///***********************************************************************************///
void LowpowerTimer_IRQHandler(void)
{
	LowpowerTimer->LPTIF |= 0x00000007;	///*���жϱ�־*///
	///*****************************************///
	///*****************************************///
	///*500ms������*///
	if( SV_TimerBasedTickTimer_500ms <= C_Interval_500ms )
	{
		SV_TimerBasedTickTimer_500ms++;
//		if(SV_TimerBasedTickTimer_500ms%2)
//		{ 
//			SwitchOn_BackLight();///test niu,5ms
//		}
//		else
//		{
//			SwitchOff_BackLight();///test niu
//		}	
	}
	///*****************************************///
	///*1000ms������:ͣ�绽��ʱ����Ҫs�仯��Ϣ(���s�仯�������е�ʱ���ת���ͳ������ݳ�����)*///
	if( SV_TimerBasedTickTimer_1000ms <= C_Interval_1000ms )
	{
		SV_TimerBasedTickTimer_1000ms++;
	}
	///*���Ӽ�����*///
	if( SV_TimerCheckMcu < C_Interval_1min )
	{
		SV_TimerCheckMcu++;
	}
	///**************************************///
	///*�ϵ�������ȡ�ⲿ�����߹���100ms*///
	SV_TimerShut100ms = 0;
	///**************************************///
	///*ι����ʱ��*///
//	SV_TimerFeedWatchdog++;
	if( SV_TimerFeedWatchdog <= C_WatchDog_Feed )
	{
		SV_TimerFeedWatchdog++;
		FeedWatchDog();
	}
	///**************************************///
	///*��ѯ�Ϸ�����*///
	if( Str_KeyUp.Timer <= C_Interval_50ms )
	{
		Str_KeyUp.Timer++;
		if( DF_GetIOStatus(C_KeyUp) == Str_KeyUp.HStatus )	///*��ǰ״̬����ʷ״̬��ͬ*///
		{
			Str_KeyUp.Timer = 0;
		}
	}
	///**************************************///
	///*��ѯ�·�����*///
	if( Str_KeyDown.Timer <= C_Interval_50ms )
	{
		Str_KeyDown.Timer++;
		if( DF_GetIOStatus(C_KeyDown) == Str_KeyDown.HStatus )	///*��ǰ״̬����ʷ״̬��ͬ*///
		{
			Str_KeyDown.Timer = 0;
		}
	}
	///**************************************///
	///*��ѯ����ǰ���*///
	if( Str_KeyOpenCover.Timer <= C_Interval_50ms )
	{
		Str_KeyOpenCover.Timer++;
	}
	if( DF_GetIOStatus(C_KeyOpenCover) == Str_KeyOpenCover.HStatus )	///*��ǰ״̬����ʷ״̬��ͬ*///
	{
		Str_KeyOpenCover.Timer = 0;
	}
	///**************************************///
	///*��ѯ��β�ǰ���*///
	if( Str_KeyOpenTerminal.Timer <= C_Interval_50ms )
	{
		Str_KeyOpenTerminal.Timer++;
	}
	if( DF_GetIOStatus(C_KeyOpenTerminal) == Str_KeyOpenTerminal.HStatus )	///*��ǰ״̬����ʷ״̬��ͬ*///
	{
		Str_KeyOpenTerminal.Timer = 0;
	}
	///**************************************///
}

///***********************************************************************************///
///*Function��ͣ�绽�Ѻ�Ļ������Ķ�ʱ����ʼ*///
///*Description�����Ѻ����*///
///***********************************************************************************///
void SF_LowpowerTimerStart(void)
{
	LowpowerTimerClock_EN;						///*ϵͳʱ���ṩ����ʱ�����޷�Ƶ=ϵͳʱ��*///
	LowpowerTimer->LPTCFG = 0x00000400;		///*2��Ƶ��LSCLK����ʱ��*///
	
	LowpowerTimer->LPTCMP = C_LowpowerTimerCounter;	
	LowpowerTimer->LPTTARGET = C_LowpowerTimerCounter;	///*5ms�Ľ��ļ��*///
	LowpowerTimer->LPTIE &= C_TIM_UIE_DIS;		///*��ֹ�ж�*///
	LowpowerTimer->LPTIF |= 0x00000007;
	///*******************************************************///
	LowpowerTimer->LPTCTRL |= C_TimerCounter_EN;	///*��ʽ������ʱ����ʼ����*///
	LowpowerTimer->LPTIE |= C_TIM_UIE_EN;		///*ʹ���ж�*///
	///*******************************************************///
	NVIC_EnableIRQ(LowpowerTimer_Interrupt);	///*���������ж�ʹ��*///	
}

///***********************************************************************************///
///*Function���������Ķ�ʱ��ֹͣ*///
///*Description������͹���ʱ���á��ӻ���״̬����͹��ĵ���*///
///*Influence��ֹͣ��������ϵͳʱ�ӵĹ�������ֹ�жϣ��Ӷ���ʡ����*///
///***********************************************************************************///
void SF_LowpowerTimerStop(void)
{	
	LowpowerTimer->LPTCTRL &= (~C_TimerCounter_EN);		///*��ʱ��ֹͣ����*///
	
	LowpowerTimerClock_DIS;							///*ϵͳʱ��ֹͣ�ṩ����ʱ��*///
	if (LowpowerTimer->LPTIE != 0x00000000)
	{
		LowpowerTimer->LPTIE=0x00000000;
	}	
	if (LowpowerTimer->LPTIF != 0x00000000)
	{
		LowpowerTimer->LPTIF|=0x00000007;
	}				
	if (LowpowerTimer->LPTCTRL != 0x00000000)
	{
		LowpowerTimer->LPTCTRL=0x00000000;
	}
	NVIC_DisableIRQ(LowpowerTimer_Interrupt);		///*���������жϽ�ֹ*///	
}

///**************************************************************************************///
///*Function:�������߻�ȡ��ʱ����*///
///*Description:*///
///*Input: Method:C_StartTimer:������ʱ��
///*			  C_GetTimer:��ȡ��ʱ��ʣ��Ķ�ʱֵ
///*       time:��ʱֵ,��msΪ��λ, hex��ʽ
///*			Method=C_StartTimerʱ,������ʱ
///*			Method=C_GetTimerʱ,time��Ч
///*Output:��*///
///*Return:����ʣ���ʱֵ,��Method=C_StartTimerʱֱ�ӷ����������time
///*Tips:time����ֵ����ܳ���32767(��32.767s),���������ǿ��תΪ32767
///**************************************************************************************///
ushort16 InF_OprateTimer(uchar8 Method,ushort16 time)
{
	switch(Method)
	{
		case C_StartTimer:
			if(time >= 32767)
			{
				SV_Timer_Delay = 32767;
			}
			else
			{
				SV_Timer_Delay = time;
			}
			SV_Timer_Delay |= C_TimerSwitch_16;
			break;
		///**************************************************///
		case C_GetTimer:
			
			break;
		///**************************************************///
		default:
			SV_Timer_Delay = 0;
			break;
	}
	return (SV_Timer_Delay & ~C_TimerSwitch_16 );
}

///**********************************************************///
///*����ϵ��ʱ����־����5s����C_OK������5s����C_Error*///
///**********************************************************///
uchar8 InF_GetPowerOnTimer(void)
{
	if(SV_TimerPowerOn < C_PowerOn_3s)			///*�ϵ��ʱ���Ƿ���5s*///
	{
		return C_Error;
	}
	else
	{
		return C_OK;
	}
}

///**********************************************************///
///*���ϵ��ʱ����־*///
///**********************************************************///
void SF_ClrPowerOnTimer(void)
{
	SV_TimerPowerOn = 0;
}


///***********************************************************************************///
///*Function���͹����º��⻽��1200�����ʶ�ʱ����ʼ��*///
///***********************************************************************************///
//void SF_InfarWakeupTimerInit(void)
//{
//	InfraWakeupTimerClock_EN;								///*ϵͳʱ���ṩ����ʱ�����޷�Ƶ=ϵͳʱ��*///
//	InfraWakeupTimer->CR1 = C_TIM_CR1_CLEAR;				///*���ƼĴ�������*///
//	InfraWakeupTimer->CR1 |= C_TIM_CR1_URS;					///*ֻ������Ų����ж�*///
//	InfraWakeupTimer->CR1 |= C_TIM_CR1_ARPE;
//	InfraWakeupTimer->CR2 = C_TIM_CR1_CLEAR;				///*���ƼĴ�������*///
//	InfraWakeupTimer->DIER &= C_TIM_UIE_DIS;				///*��ֹ�ж�*///
//	InfraWakeupTimer->SR &= C_TimerStatus_UIF_RESET;
//
//	InfraWakeupTimer->ARR = C_InfraWakeupTimerCounter;		///*833us�Ľ��ļ��*///
//	InfraWakeupTimer->PSC = TIM_Prescaler_0;				///*����Ƶ*///
//	
//	InfraWakeupTimer->EGR = C_TIM_EGR_CLEAR;
//}
///***********************************************************************************///
///*Function���͹����º��⻽��1200�����ʶ�ʱ����ֹ*///
///***********************************************************************************///
//void SF_InfarWakeupTimer_Disable(void)
//{
//	InfraWakeupTimer->CR1 = C_TIM_CR1_CLEAR;				///*���ƼĴ�������*///
//	InfraWakeupTimer->DIER &= C_TIM_UIE_DIS;				///*��ֹ�ж�*///
//	NVIC_DisableIRQ(InfraWakeupTimer_Interrupt);			///*�жϽ�ֹ*///
//	///*******************************************************///
//	InfraWakeupTimerClock_DIS;								///*ϵͳʱ�ӹر�*///
//}

///***********************************************************************************///
///*Function���͹����º��⻽��1200�����ʶ�ʱ����*///
///***********************************************************************************///
void SF_InfarWakeupTimer_Start(void)
{
//	InfraWakeupTimer->SR &= C_TimerStatus_UIF_RESET;
//	InfraWakeupTimer->CR1 |= C_TIM_CR1_URS;					///*ֻ������Ų����ж�*///
//	InfraWakeupTimer->CR1 |= C_TimerCounter_EN;				///*��ʽ������ʱ����ʼ����*///
//	InfraWakeupTimer->DIER |= C_TIM_UIE_EN;					///*ʹ���ж�*///
//	NVIC_EnableIRQ(InfraWakeupTimer_Interrupt);				///*�ж�ʹ��*///
}

///***********************************************************************************///
///*Function���͹����º��⻽��1200�����ʶ�ʱ��ֹͣ*///
///***********************************************************************************///
void SF_InfarWakeupTimerStop(void)
{
//	InfraWakeupTimer->CR1 = C_TIM_CR1_CLEAR;				///*���ƼĴ�������*///
//	InfraWakeupTimer->DIER &= C_TIM_UIE_DIS;				///*��ֹ�ж�*///
//	NVIC_DisableIRQ(InfraWakeupTimer_Interrupt);			///*�жϽ�ֹ*///
	///*******************************************************///
}

///***********************************************************************************///
///*Function������߱���ʱ��:�ú���ר�Ÿ��͹����µ���*///
///***********************************************************************************///
void SF_ClrShutTime(void)
{
	SV_TimerShut100ms = 0;
}

///***********************************************************************************///
///*Function���ж��ϵ��ʵʱ������ʱ���Ƿ�*///
///*�ú����ж��ϵ��Ĵ����Ƿ�Ϊ0,��Ϊ0����C_Error,Ϊ0����C_OK,Ϊ�Ƿ�ֵ���㶨ʱ��������C_OK
///***********************************************************************************///
uchar8 SF_Shut_RealTimeData(void)
{
	if( SV_TimerShutRealTimeData == 0 )
	{
		return C_OK;
	}
	else if( SV_TimerShutRealTimeData > C_ShutRealTimeData )
	{///*�������ֵ,��Ϊʱ�䵽,�����Ĵ�������*///
		SV_TimerShutRealTimeData = 0;
		return C_OK;
	}
	else
	{
		return C_Error;
	}
}
///***********************************************************************************///
///*Function�������������1000ms��ʱ��*///
///*Description:����ȫʧѹʱ,��Ϊ����оƬ��д���ʼ���ݺ���Ҫ��ʱ2s���ܶ�ȡRMS
///*            �����д��ʼ���ݺ�,��Ҫ����ʱʱ������,���¼�ʱ
///***********************************************************************************///
void SF_ClrSV_TimerBasedTickTimer_1000ms(void)
{
	SV_TimerBasedTickTimer_1000ms = 0;
}


///***********************************************************************************///
///*Function����ͨ�ų�ʱ��ʱ������*///
///*��Ƭ��������16M,��������3.579545M,���մ�Ƶ�����õ�Ƭ���Ķ�ʱ��
///*��ڲ���˵��:
///*			Timer_Init		C_Init				��Ҫ��ʼ����ʱ��
///*							C_NotInit			����Ҫ��ʼ����ʱ��:ֱ�����ö�ʱ�����ľͿ�����
///*			ETU_Number		C_9600_ETU			9600��ETU
///*							C_1_3_ETU			1/3��ETU
///*							C_1_2_ETU			1/2��ETU
///*							C_1_ETU				1��ETU
///*							C_1_Piont_5_ETU		1.5��ETU
///*							C_2_ETU				2��ETU
///*							C_2_Piont_5_ETU		2.5��ETU
///*							C_16_ETU			16��ETU
///*							C_20_ETU			20��ETU
///*����˵��:��ʱ��������ڲ������ã���������ʱ*///
///*ע    ��:�ú����������룬��Ҫע��*///
///***********************************************************************************///
void SF_CardBaudRateTimerInit( uchar8 Timer_Init,uchar8 ETU_Number )
{
	if( C_Init == Timer_Init )
	{
		CardBaudRateTimerClock_EN;								///*ϵͳʱ���ṩ����ʱ�����޷�Ƶ=ϵͳʱ��*///
		CardBaudRateTimer->ETxCR = C_TIM_CR1_CLEAR;				///*���ƼĴ�������*///
		CardBaudRateTimer->ETxINSEL = 0;				///*�����ź�ѡ����ƣ�APBCLK*///
		CardBaudRateTimer->ETxPESCALE1 = 0;			///*Ԥ��Ƶ�Ĵ���������Ƶ*///
		CardBaudRateTimer->ETxPESCALE2 = 0;			///*Ԥ��Ƶ�Ĵ���������Ƶ*///
		CardBaudRateTimer->ETxIE &= C_TIM_UIE_DIS;	///*�жϽ�ֹ*///
		CardBaudRateTimer->ETxIF |= C_TimerStatus_RESET;	///*���жϱ�־*///
		
		CardBaudRateTimer->ETxCR |= C_CardBaudRateTimerETxCR;		///*���ƼĴ������ã�PWM��ֹ����ʱģʽ*///
	}

	switch(ETU_Number)
	{
		case C_4ms:
		{
			CardBaudRateTimer->ETxIVR = C_CardBaudRateTimerCounter_4ms;
			CardBaudRateTimer->ETxCR |= C_TIM_CR1_CEN;					///*��ʽ������ʱ����ʼ����*///
			CardBaudRateTimer->ETxIF |= C_TimerStatus_OVIF_RESET;
			break;
		}
		case C_1_3_ETU:
		{
			CardBaudRateTimer->ETxIVR = C_CardBaudRateTimerCounter_1_3_ETU;
			CardBaudRateTimer->ETxCR |= C_TIM_CR1_CEN;					///*��ʽ������ʱ����ʼ����*///
			CardBaudRateTimer->ETxIF |= C_TimerStatus_OVIF_RESET;
			break;
		}
		case C_1_2_ETU:
		{
			CardBaudRateTimer->ETxIVR = C_CardBaudRateTimerCounter_1_2_ETU;
			CardBaudRateTimer->ETxCR |= C_TIM_CR1_CEN;					///*��ʽ������ʱ����ʼ����*///
			CardBaudRateTimer->ETxIF |= C_TimerStatus_OVIF_RESET;
			break;
		}
		case C_1_ETU:
		{
			CardBaudRateTimer->ETxIVR = C_CardBaudRateTimerCounter_1_ETU;
			CardBaudRateTimer->ETxCR |= C_TIM_CR1_CEN;					///*��ʽ������ʱ����ʼ����*///
			CardBaudRateTimer->ETxIF |= C_TimerStatus_OVIF_RESET;
			break;
		}
		case C_1_Piont_5_ETU:
		{
			CardBaudRateTimer->ETxIVR = C_CardBaudRateTimerCounter_1_Piont_5_ETU;
			CardBaudRateTimer->ETxCR |= C_TIM_CR1_CEN;					///*��ʽ������ʱ����ʼ����*///
			CardBaudRateTimer->ETxIF |= C_TimerStatus_OVIF_RESET;
			break;
		}
		case C_2_ETU:
		{
			CardBaudRateTimer->ETxIVR = C_CardBaudRateTimerCounter_2_ETU;
			CardBaudRateTimer->ETxCR |= C_TIM_CR1_CEN;					///*��ʽ������ʱ����ʼ����*///
			CardBaudRateTimer->ETxIF |= C_TimerStatus_OVIF_RESET;
			break;
		}
		case C_2_Piont_5_ETU:
		{
			CardBaudRateTimer->ETxIVR = C_CardBaudRateTimerCounter_2_Piont_5_ETU;
			CardBaudRateTimer->ETxCR |= C_TIM_CR1_CEN;					///*��ʽ������ʱ����ʼ����*///
			CardBaudRateTimer->ETxIF |= C_TimerStatus_OVIF_RESET;
			break;
		}
		case C_16_ETU:
		{
			CardBaudRateTimer->ETxIVR = C_CardBaudRateTimerCounter_16_ETU;
			CardBaudRateTimer->ETxCR |= C_TIM_CR1_CEN;					///*��ʽ������ʱ����ʼ����*///
			CardBaudRateTimer->ETxIF |= C_TimerStatus_OVIF_RESET;
			break;
		}
		case C_20_ETU:
		{
			CardBaudRateTimer->ETxIVR = C_CardBaudRateTimerCounter_20_ETU;
			CardBaudRateTimer->ETxCR |= C_TIM_CR1_CEN;					///*��ʽ������ʱ����ʼ����*///
			CardBaudRateTimer->ETxIF |= C_TimerStatus_OVIF_RESET;
			break;
		}
		default:
		{
			CardBaudRateTimer->ETxIF |= C_TimerStatus_OVIF_RESET;
			CardBaudRateTimer->ETxCR &= (~C_TIM_CR1_CEN);			///*ֹͣ����*///
			break;
		}
	}
}

///***********************************************************************************///
///*Function����ͨ��ETU��ʱ����*///
///***********************************************************************************///
void SF_CardBaudRateTimer_Start(void)
{
//	CardBaudRateTimer->SR &= C_TimerStatus_UIF_RESET;
//	CardBaudRateTimer->CR1 |= C_TIM_CR1_CEN;					///*��ʽ������ʱ����ʼ����*///
}

///***********************************************************************************///
///*Function����ͨ��ETU��ʱ��ֹͣ*///
///***********************************************************************************///
void SF_CardBaudRateTimerStop(void)
{
	CardBaudRateTimer->ETxCR &= (~C_TIM_CR1_CEN);			///*ֹͣ����*///
	CardBaudRateTimer->ETxIF |= C_TimerStatus_RESET;		///*���жϱ�־*///
	CardBaudRateTimerClock_DIS;
}


///***********************************************************************************///
///*Function����ͨ����ʱETU_Number��ETU*///
///*ETU_Number:��ʾ��Ҫ��ʱETU�ĸ���
///*            �ú�������0.5ETU�Ķ�ʱ�������ʱ,�ں����ڲ�����ڲ���*2
///***********************************************************************************///
void SF_CardTimerDelay_N_ETU( uchar8 ETU_Number )
{
	ushort16 i,j;
	
	j = 2*ETU_Number;
	
	for(i=0;i<j;i++)
	{
		while( !(CardBaudRateTimer->ETxIF & C_TimerStatus_OVIF_RESET) )
		{
			;
		}
		CardBaudRateTimer->ETxIF |= C_TimerStatus_OVIF_RESET;///*���жϱ�־
	}
}

