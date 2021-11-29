
///*****************************************************************************************///
///*Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     uart.c
///*Version:       V1
///*Date:          2014-3-12
///*Description:   ��������
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
#include "uart.h"
#include "IO.h"
#include "Timer.h"
#include "EsamDrive.h"
#include "CardDrive.h"
#include "fm32l0xx_rcc.h"
#include "LowPower.h"

///*�жϷ������궨��*///


static uchar8	SV_InterruptMsg_485_1;				///*��1·485������װ�ؽ�����־*///
static uchar8	SV_InterruptMsg_485_2;				///*��2·485������װ�ؽ�����־*///
static uchar8	SV_InterruptMsg_Ir;					///*���⣺����װ�ؽ�����־*///
static uchar8	SV_InterruptMsg_Modular;			///*ģ�飺����װ�ؽ�����־*///
static uchar8	SV_InitUartMsg_485_1;				///*��1·485������װ�س�ʼ����־*///
static uchar8	SV_InitUartMsg_485_2;				///*��2·485������װ�س�ʼ����־*///
static uchar8	SV_InitUartMsg_Ir;					///*���⣺����װ�س�ʼ����־*///
static uchar8	SV_InitUartMsg_Modular;				///*ģ�飺����װ�س�ʼ����־*///
static uchar8	SV_MeterType;						///*���ܱ�����:ģ�����ģ���*///
static uchar8	SV_Overtime_485_1;					///*��1·485��Ӧ���ڳ�ʱ��ʱ��*///
static uchar8	SV_Overtime_485_2;					///*��2·485��Ӧ���ڳ�ʱ��ʱ��*///
static uchar8	SV_Overtime_Ir;						///*�����Ӧ���ڳ�ʱ��ʱ��*///
///*��Ϊ��2·485��ģ�鹲��һ·Ӳ������,����ģ�鳬ʱ��ʱ������Ҫ*///
//static uchar8	SV_Overtime_Modular;				///*ģ���Ӧ���ڳ�ʱ��ʱ��*///

//uchar8 SV_485_1_timer;
//uchar8 SV_485_1_int;
//uchar8 SV_485_1_dispatch;


//ulong32 SV_Uart_RxCounter;		//�����ֽ���
//ulong32 SV_Uart_TxCounter;		//�����ֽ���
//ulong32 SV_Uart_RxIntterupt;	//�жϴ���
//ulong32 SV_Uart_TxIntterupt;	//�жϴ���
//ulong32 SV_Uart_RxErr;			//�������
//ulong32 SV_Uart_TxErr;			//�������
//ulong32 SV_Uart_ComPass;
//ulong32 SV_Uart_ComTx;
//ulong32 SV_Uart_ComMsg;
//
//void InF_ComMsg(void)
//{
//	SV_Uart_ComMsg++;
//}
//void InF_ComPass(void)
//{
//	SV_Uart_ComPass++;
//}
//
//void InF_ComTx(void)
//{
//	SV_Uart_ComTx++;
//}
//
//void InF_Inti_UartTemp(void)
//{
//	SV_Uart_RxCounter =0;		//�����ֽ���
//	SV_Uart_TxCounter =0;		//�����ֽ���
//	SV_Uart_RxIntterupt =0;		//�жϴ���
//	SV_Uart_TxIntterupt =0;		//�жϴ���
//	SV_Uart_RxErr =0;			//�������
//	SV_Uart_TxErr =0;			//�������
//	SV_Uart_ComPass =0;			//�������
//	SV_Uart_ComTx =0;			//�������
//	SV_Uart_ComMsg = 0;
//}


///**********************************************************************************///
///*Description�����ڳ�ʱ����,�����ʱ��������λ����*///
///*Input����
///*Output:�����Ƿ�ʱȷ���Ƿ��ʼ������*///
///*Influence��
///* 1.�ú������������е���,ÿ500ms����һ��,���������ģ��ִ��ʱ�䳬��500ms,
///*   ��ú���ִ�м��Ҳ����500ms
///* 2.�ú���ֻ�����������е���,����ĵ��жϵ���,ֻ���ñ�־�ص��������ٳ�ʼ������
///**********************************************************************************///
void SF_UartOvertime(void)
{
	///*��1·485��Ӧ�Ĵ��ڳ�ʱ��ʱ��*///
	SV_Overtime_485_1++;
	if( SV_Overtime_485_1 >= C_Uart_OverTime )
	{
		InF_InitComm(C_RS485_1);
	}
	///*��2·485��Ӧ�Ĵ��ڳ�ʱ��ʱ��*///
	SV_Overtime_485_2++;
	if( SV_Overtime_485_2 >= C_Uart_OverTime )
	{
		///*���ݵ������ȷ����ʼ����һ·ͨ��*///
		if(SV_MeterType != C_MeterType_Module)
		{
			InF_InitComm(C_RS485_2);
		}
		else
		{
			InF_InitComm(C_Module);
		}
	}
	///*�����Ӧ�Ĵ��ڳ�ʱ��ʱ��*///
	SV_Overtime_Ir++;
	if( SV_Overtime_Ir >= C_Uart_OverTime )
	{
		InF_InitComm(C_IR);
	}
}
///**********************************************************************************///
///*Description��ȡ���ܱ�ͨ������:�Ƿ�Ϊģ���*///
///*Input����
///*Output��SV_MeterType=C_MeterType_Module��ʾΪģ���,����Ϊ��ģ���*///
///*Influence���ϵ��ʼ������1��,��������0.5s����1��*///
///**********************************************************************************///
void SF_GetMeterType(void)
{
	uchar8 V_DataBuff[5];
	ushort16 V_usLen, V_usDataEncode;
	
	V_usLen = CLComm_Way;
	if( InF_Read_Data(CComm_Way,&V_DataBuff[0],&V_usLen, &V_usDataEncode) == C_OK )
	{
		if( V_DataBuff[0] == C_MeterType_Module )
		{
			SV_MeterType = C_MeterType_Module;
		}
		else
		{
			SV_MeterType = 0;
		}
	}
	else
	{
		SV_MeterType = 0;
	}
}
///**********************************************************************************///
///*Description��ȡ���ܱ�ͨ������:�Ƿ�Ϊģ���*///
///*Input����
///*Output��SV_MeterType=C_MeterType_Module��ʾΪģ���,����Ϊ��ģ���*///
///*Influence��������ģ�����*///
///**********************************************************************************///
uchar8 Inf_GetMeterType(void)
{
  return SV_MeterType;
}


///**********************************************************************************///
///*Function��*///
///*Description�������ȸ����ж�ȫ�ֱ�־,�ж��Ƿ񴥷�ͨ�Ž���ģ��*///
///*Input����
///*Output����־��������ֱ�ӵ���ͨ�Ž���ģ��ӿں���,Ȼ�󽫱�־��Ϊ��̬*///
///*Calls��*///
///*Called By�������ȸ����Ƿ���һ֡���ݱ�־����*///
///*Influence�����õĵط���Դ��Ϣ�š�Ŀ����Ϣ�š�����������ú���øú���*///
///*�ú���ÿ��ѭ������һ�Σ���д�ú�����Ŀ���ǣ����ж��ﲻ���÷���Ϣ������*///
///*�ж���ֻ���ñ�־�����������������ﴦ��������ģ��ӿں�������ʼ�����ڵ��ӿں���*///
///**********************************************************************************///
void InF_Dispatch_CommInterruptMessage(void)
{
	uchar8 V_ucBuffer[5];
	Str_Msg_Parameter SStr_Msg_Parameter;
	
	///*����ȡ��ǰ��Դ״̬,���ݸ����õĺ���*///
	SStr_Msg_Parameter.PowerFlag = InF_ReadPowerState();
	
	///*���ڽ�����Ϣ����*///
	if( SV_InterruptMsg_485_1 == C_Uart_Parse )
	{
		SV_InterruptMsg_485_1 = C_Uart_Normal;
		V_ucBuffer[0] = Pt_Comm_No;
		V_ucBuffer[1] = C_RS485_1;
////		Dispatch_SendMessage(C_Msg_Communication,V_ucBuffer,Pt_Comm_No_Len+1);
		SStr_Msg_Parameter.SourceAddr = C_Msg_Dispatch;	///*Դ��ַ��Ȼ��������*///
		SStr_Msg_Parameter.DerictAddr = C_Msg_Communication;
		SStr_Msg_Parameter.Parameter = &V_ucBuffer[0];
		SStr_Msg_Parameter.Length = Pt_Comm_No_Len+1;
		Comm_ParseMessage(&SStr_Msg_Parameter);
	}

	if( SV_InterruptMsg_485_2 == C_Uart_Parse )
	{
		SV_InterruptMsg_485_2 = C_Uart_Normal;
		V_ucBuffer[0] = Pt_Comm_No;
		V_ucBuffer[1] = C_RS485_2;
////		Dispatch_SendMessage(C_Msg_Communication,V_ucBuffer,Pt_Comm_No_Len+1);
		SStr_Msg_Parameter.SourceAddr = C_Msg_Dispatch;	///*Դ��ַ��Ȼ��������*///
		SStr_Msg_Parameter.DerictAddr = C_Msg_Communication;
		SStr_Msg_Parameter.Parameter = &V_ucBuffer[0];
		SStr_Msg_Parameter.Length = Pt_Comm_No_Len+1;
		Comm_ParseMessage(&SStr_Msg_Parameter);
	}

	if( SV_InterruptMsg_Ir == C_Uart_Parse )
	{
		SV_InterruptMsg_Ir = C_Uart_Normal;
		V_ucBuffer[0] = Pt_Comm_No;
		V_ucBuffer[1] = C_IR;
////		Dispatch_SendMessage(C_Msg_Communication,V_ucBuffer,Pt_Comm_No_Len+1);
		SStr_Msg_Parameter.SourceAddr = C_Msg_Dispatch;	///*Դ��ַ��Ȼ��������*///
		SStr_Msg_Parameter.DerictAddr = C_Msg_Communication;
		SStr_Msg_Parameter.Parameter = &V_ucBuffer[0];
		SStr_Msg_Parameter.Length = Pt_Comm_No_Len+1;
		Comm_ParseMessage(&SStr_Msg_Parameter);
	}

	if( SV_InterruptMsg_Modular == C_Uart_Parse )
	{
		SV_InterruptMsg_Modular = C_Uart_Normal;
		V_ucBuffer[0] = Pt_Comm_No;
		V_ucBuffer[1] = C_Module;
////		Dispatch_SendMessage(C_Msg_Communication,V_ucBuffer,Pt_Comm_No_Len+1);
		SStr_Msg_Parameter.SourceAddr = C_Msg_Dispatch;	///*Դ��ַ��Ȼ��������*///
		SStr_Msg_Parameter.DerictAddr = C_Msg_Communication;
		SStr_Msg_Parameter.Parameter = &V_ucBuffer[0];
		SStr_Msg_Parameter.Length = Pt_Comm_No_Len+1;
		Comm_ParseMessage(&SStr_Msg_Parameter);
	}
	
	///*���ڳ�ʼ����Ϣ����*///
	if( SV_InitUartMsg_485_1 == C_Uart_Init )
	{
		SV_InitUartMsg_485_1 = C_Uart_Normal;
		InF_InitComm(C_RS485_1);
	}
	if( SV_InitUartMsg_485_2 == C_Uart_Init )
	{
		SV_InitUartMsg_485_2 = C_Uart_Normal;
		InF_InitComm(C_RS485_2);
	}
	if( SV_InitUartMsg_Ir == C_Uart_Init )
	{
		SV_InitUartMsg_Ir = C_Uart_Normal;
		InF_InitComm(C_IR);
	}
	
	if( SV_InitUartMsg_Modular == C_Uart_Init )
	{
		SV_InitUartMsg_Modular = C_Uart_Normal;
		InF_InitComm(C_Module);
	}
}


///***********************************************************************************///
///*Function��������ⷢ�͵�38KHz�ĵ����ź�*///
///*Description������ͨ�ŷ���ǰ����*///
///*Input��*///
///*Output��*///
///*Calls��*///
///*Called By��*///
///*Influence��*///
///*Tips��*///
///*Others��*///
///***********************************************************************************///
void SF_InfraModulatedSignalConfig(void)
{
//	InfraTimerClock_EN;						///*ϵͳʱ���ṩ��38kHz��ʱ�����޷�Ƶ=ϵͳʱ��*///
//	Select_InfraIO_PWM;						///*����������ΪPWM�������*///
//	InfraTimer->CR1 = C_TIM_CR1_CLEAR;		///*���ƼĴ�������*///
//	
//	InfraTimer->ARR = C_InfraTimerCounter;	///*37.736kHz*///
//	InfraTimer->CCR1 = C_InfraTimerCounter;
//	InfraTimer->DIER &= C_TIM_UIE_DIS;		///*��ֹ�ж�*///
//	InfraTimer->SMCR = C_TIM_SMCR_CLEAR;	///*�üĴ����ڶ�ʱ������PWM���ʱ����*///
//	InfraTimer->CCER &= C_TIM_OUTPUT_DIS;	///*OC1��ЧʱΪ�ߣ�OC1������Ϊ��Ч*///
//	InfraTimer->PSC = TIM_Prescaler_0;		///*����Ƶ*///
//	InfraTimer->CCMR1 = 0x0040;				///*ǿ������ߵ�ƽ*///
//	
//	InfraTimer->CCER = 0x0003;
//	InfraTimer->EGR = C_TIM_EGR_CLEAR;
//	InfraTimer->SR &= C_TimerStatus_UIF_RESET;
//	InfraTimer->SR &= C_TimerStatus_CCIF_RESET;
}


///***********************************************************************************///
///*Function��������ⷢ�͵�38KHz�ĵ����ź�*///
///*Description������ͨ�ŷ���ǰ����*///
///*Input��*///
///*Output��*///
///*Calls��*///
///*Called By��*///
///*Influence��*///
///*Tips��*///
///*Others��*///
///***********************************************************************************///
void SF_InfraModulatedSignalOutput(void)
{
	SFR_INFRA->TXSTA |= USART_TEIREN_En;				///* ʹ�ܺ��ⷢ�͵���*///
	///*******************************************************///
}
///***********************************************************************************///
///*Function���رպ��ⷢ�͵�38KHz�����ź�*///
///*Description������ȫ���������ر�*///
///*Input��*///
///*Output��*///
///*Calls��*///
///*Called By��*///
///*Influence��*///
///*Tips��*///
///*Others��*///
///***********************************************************************************///
void SF_InfraModulatedSignalOff(void)
{
	SFR_INFRA->TXSTA &= USART_TEIREN_Dis;				///*��ֹ���ⷢ�͵���*///
}
///***********************************************************************************///
///*Function���͹����º��⻽�Ѵ��ڳ�ʼ��*///
///*Description������ȫ���������ر�*///
///*Input��*///
///*Output��*///
///*Calls��*///
///*Called By��*///
///*Influence��*///
///*Tips��*///
///*Others��*///
///***********************************************************************************///
void SF_InfarWakeupTimerInit(void)
{
	ulong32 V_UsartDataBuff;
	SV_InterruptMsg_Ir = C_Uart_Normal;			///*������־��Ϊ��̬*///
	SV_InitUartMsg_Ir = C_Uart_Normal;
				
	SF_InfraModulatedSignalOff();
	Enable_ComUart_Clock;///*ʹ��commUart			
	Enable_Infra_Clock;		///*����ʱ��ʹ��*///
	Select_Infra_AFMode;	///*�����߹�������AF����*///
	Select_Infra_IO_Type;	///*�����������������������������*///
				
	UART->IRCON = USART_IRCONn_WakeUp;///*38k,1:1

	if(((SFR_INFRA->RXSTA&USART_WordLength_9b_Parity_No) != USART_WordLength_8bNo)
			&&((SFR_INFRA->RXSTA&USART_WordLength_9b_Parity_No) != USART_WordLength_8bOdd))
		{ 
			SFR_INFRA->RXSTA &= (~USART_WordLength_9b_Parity_No);
			SFR_INFRA->RXSTA |= USART_WordLength_8bEven;
		}
		///*******************************************************///
	SFR_INFRA->RXSTA &= (~USART_ParityErrInt_EN);	///*��ֹ�����ж�...*///
	///*******************************************************///
	SFR_INFRA->SPBRG = USART_bps_1200_Wakeup;				///*1200*///
	///*******************************************************///
	SFR_INFRA->RXSTA &= (~(USART_FLAG_FE | USART_FLAG_PE|USART_FLAG_ORE));
	V_UsartDataBuff = SFR_INFRA->RXREG;				///*�建��*///
	V_UsartDataBuff = SFR_INFRA->RXSTA;				///*��״̬��*///
	V_UsartDataBuff = SFR_INFRA->RXBUFSTA;
//				SFR_INFRA->DR = V_UsartDataBuff;				///*�建��*///
	Start_Infra_Rx;									///*��ʼ����*///
		///*******************************************************///
	NVIC_EnableIRQ(Infra_IRQn);						///*�����ж�ʹ��*///
}
///***********************************************************************************///
///*Function���͹��Ļ��Ѻ��������ⷢ�͵�38KHz�ĵ����ź�*///
///*Description������ͨ�ŷ���ǰ����*///
///***********************************************************************************///
void SF_InfraModulatedSignalOutput_Wakeup(void)
{
//	InfraTimerClock_EN;						///*ϵͳʱ���ṩ��38kHz��ʱ�����޷�Ƶ=ϵͳʱ��*///
//	Select_InfraIO_PWM;						///*����������ΪPWM�������*///
//	InfraTimer->CR1 = C_TIM_CR1_CLEAR;		///*���ƼĴ�������*///
//	
//	InfraTimer->ARR = C_InfraTimerCounter_Wakeup;	///*37.736kHz*///
//	InfraTimer->CCR1 = C_InfraTimerCounter_Wakeup;
//	InfraTimer->DIER &= C_TIM_UIE_DIS;		///*��ֹ�ж�*///
//	InfraTimer->SMCR = C_TIM_SMCR_CLEAR;	///*�üĴ����ڶ�ʱ������PWM���ʱ����*///
//	InfraTimer->CCER &= C_TIM_OUTPUT_DIS;	///*OC1��ЧʱΪ�ߣ�OC1������Ϊ��Ч*///
//	InfraTimer->PSC = TIM_Prescaler_0;		///*����Ƶ*///
//	InfraTimer->CCMR1 = 0x0030;				///*TIMx_CNT��TIMx_CCR1���ʱ���߷�ת*///
//	
//	InfraTimer->CCER = 0x0003;
//	InfraTimer->EGR = C_TIM_EGR_CLEAR;
//	InfraTimer->SR &= C_TimerStatus_UIF_RESET;
//	InfraTimer->SR &= C_TimerStatus_CCIF_RESET;
//	///*******************************************************///
//	InfraTimer->CR1 |= C_TimerCounter_EN;	///*��ʽ������ʱ����ʼ����*///
//	///*******************************************************///
}


///*********************************************************************************///
///*����ԭ�ͣ�void InF_InitCommUartForInterrupt(uchar8 CommNum)*///
///*���������*///
///*	CommNum��ͨѶͨ���š�ȡֵ��C_RS485_1��C_RS485_2��C_IR��C_Module��C_ESAM��C_Card��*///
///*�����������*///
///*���ز�������*///
///*����˵����*///
///*	1�����ж����ʼ�����ڣ�*///
///*	2���ú����ڷ��ͽ�����ֱ�����ж�����á�*///
///*	1����������ForDispatch��ʾ���������е��ã�ForInterrupt��ʾ���ж�����á�*///
///*	2�����ں��⴮�ڣ�����38kHz�����źŵ��ر��ź�������ܡ�*///
///*********************************************************************************///
void InF_InitCommUartForInterrupt(uchar8 CommNum)
{
	ulong32 V_UsartDataBuff;
	
	Enable_ComUart_Clock;///*ʹ��commUart
	
	switch(CommNum)
	{
		case C_RS485_1:
		{
			SV_InterruptMsg_485_1 = C_Uart_Normal;		///*������־��Ϊ��̬*///
			SV_InitUartMsg_485_1 = C_Uart_Normal;
			
			Enable_485_1_Receive;	///*ʹ485оƬ�����ڽ���̬��3���ʽ*///
			Enable_485_1_Clock;		///*��1·485ʱ��ʹ��*///
//			Select_485_1_UartMode;	///*ѡ��AF����ΪUart����*///
			Select_485_1_AFMode;	///*�����߹�������AF����*///
			Select_485_1_IO_Type;	///*�����������������������������*///
			
			///*******************************************************///
//			if( (SFR_FIRST485->TXSTA&USART_StopBits_2) != USART_StopBits_1 )
//			{
//				SFR_FIRST485->TXSTA |= USART_StopBits_2;
//			}
			///*******************************************************///
			///*�ַ���Ȳ���8λ����9λ,���Բ���Ҫ����*///
			//if( (SFR_FIRST485->CR1&USART_WordLength_9b) != USART_WordLength_9b )
			//{
			//	SFR_FIRST485->CR1 |= USART_WordLength_8b;
			//}
			///*******************************************************///
			if(((SFR_FIRST485->RXSTA&USART_WordLength_9b_Parity_No) != USART_WordLength_8bNo)
					&&((SFR_FIRST485->RXSTA&USART_WordLength_9b_Parity_No) != USART_WordLength_8bOdd))
			{
				SFR_FIRST485->RXSTA &= (~USART_WordLength_9b_Parity_No);
				SFR_FIRST485->RXSTA |= USART_WordLength_8bEven;
			}
			///*******************************************************///
			SFR_FIRST485->RXSTA &= (~USART_ParityErrInt_EN);	///*��ֹ�����ж�...*///
			///*******************************************************///
			if( (SFR_FIRST485->SPBRG!=USART_bps_38400) 
				&& (SFR_FIRST485->SPBRG!=USART_bps_19200) 
				&& (SFR_FIRST485->SPBRG!=USART_bps_2400)
				&&(SFR_FIRST485->SPBRG!=USART_bps_4800)
				&&(SFR_FIRST485->SPBRG!=USART_bps_1200)
				&&(SFR_FIRST485->SPBRG!=USART_bps_600)
				&&(SFR_FIRST485->SPBRG!=USART_bps_300) )
			{
				SFR_FIRST485->SPBRG = USART_bps_9600;		///*9600*///
			}
			///*******************************************************///
			SFR_FIRST485->RXSTA &= (~(USART_FLAG_FE | USART_FLAG_PE|USART_FLAG_ORE));
			V_UsartDataBuff = SFR_FIRST485->RXREG;				///*�建��*///
			V_UsartDataBuff = SFR_FIRST485->RXSTA;				///*��״̬��*///
			V_UsartDataBuff = SFR_FIRST485->RXBUFSTA;
//			SFR_FIRST485->RXREG = V_UsartDataBuff;				///*�建��*///
			Start_First485_Rx;								///*��ʼ����*///
			///*******************************************************///
			NVIC_EnableIRQ(First485_IRQn);					///*�����ж�ʹ��*///
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_RS485_2:
		{
			if(C_SmartMeter==C_Meter_Type)///*����hex���ݸ��ݱ����ж�
			{
				SV_InterruptMsg_485_2 = C_Uart_Normal;		///*������־��Ϊ��̬*///
				SV_InitUartMsg_485_2 = C_Uart_Normal;
				
				Enable_485_2_Receive;	///*ʹ485оƬ�����ڽ���̬��3���ʽ*///
				Enable_485_2_Clock;		///*��2·485ʱ��ʹ��*///
				Select_485_2_AFMode;	///*�����߹�������AF����*///
				Select_485_2_IO_Type;	///*�������������������������*///				
				
	//			if( (SFR_SECOND485->TXSTA&USART_StopBits_2) != USART_StopBits_1 )
	//			{
	//				SFR_SECOND485->TXSTA |= USART_StopBits_2;
	//			}
				///*******************************************************///
				///*�ַ���Ȳ���8λ����9λ,���Բ���Ҫ����*///
				//if( (SFR_SECOND485->CR1&USART_WordLength_9b) != USART_WordLength_9b )
				//{
				//	SFR_SECOND485->CR1 |= USART_WordLength_8b;
				//}
				///*******************************************************///
				///*******************************************************///
				if(((SFR_SECOND485->RXSTA&USART_WordLength_9b_Parity_No) != USART_WordLength_8bNo)
						&&((SFR_SECOND485->RXSTA&USART_WordLength_9b_Parity_No) != USART_WordLength_8bOdd))
				{
					SFR_SECOND485->RXSTA &= (~USART_WordLength_9b_Parity_No);
					SFR_SECOND485->RXSTA |= USART_WordLength_8bEven;
				}
				///*******************************************************///
				SFR_SECOND485->RXSTA &= (~USART_ParityErrInt_EN);	///*��ֹ�����ж�...*///
				///*******************************************************///
				if( (SFR_SECOND485->SPBRG!=USART_bps_38400) 
					&& (SFR_SECOND485->SPBRG!=USART_bps_19200) 
					&& (SFR_SECOND485->SPBRG!=USART_bps_2400)
					&&(SFR_SECOND485->SPBRG!=USART_bps_4800)
					&&(SFR_SECOND485->SPBRG!=USART_bps_1200)
					&&(SFR_SECOND485->SPBRG!=USART_bps_600)
					&&(SFR_SECOND485->SPBRG!=USART_bps_300) )
				{
					SFR_SECOND485->SPBRG = USART_bps_9600;		///*9600*///
				}
				///*******************************************************///
				SFR_SECOND485->RXSTA &= (~(USART_FLAG_FE | USART_FLAG_PE|USART_FLAG_ORE));
				V_UsartDataBuff = SFR_SECOND485->RXREG;				///*�建��*///
				V_UsartDataBuff = SFR_SECOND485->RXSTA;				///*��״̬��*///
				V_UsartDataBuff = SFR_SECOND485->RXBUFSTA;			
	//			SFR_SECOND485->DR = V_UsartDataBuff;				///*�建��*///
				Start_Second485_Rx;			///*��ʼ����*///
				///*******************************************************///
				NVIC_EnableIRQ(Second485_IRQn);					///*�����ж�ʹ��*///
				///*******************************************************///						
			}
			else 
			{
				///*******************************************************///
				NVIC_DisableIRQ(Second485_IRQn);					///*�����жϽ�ֹ*///
				///*******************************************************///	
				if(C_R_SmartMeter==C_Meter_Type)///*���ر��ӿڵ������ã�Զ�̱�����Ϊ��©�����
				{
					Select_485_2_ComIO_Type;
				}				
			}
			break;
		}
		///*******************************************************///
		case C_IR:
		{
			if( InF_ReadPowerState() == C_PowerOn )
			{	
				SV_InterruptMsg_Ir = C_Uart_Normal;			///*������־��Ϊ��̬*///
				SV_InitUartMsg_Ir = C_Uart_Normal;
				
				SF_InfraModulatedSignalOff();
				
				Enable_Infra_Clock;		///*����ʱ��ʹ��*///
				Select_Infra_AFMode;	///*�����߹�������AF����*///
				Select_Infra_IO_Type;	///*�����������������������������*///
				
				UART->IRCON = USART_IRCONn;///*38k,1:1
				///*******************************************************///
//				if( (SFR_INFRA->TXSTA&USART_StopBits_2) != USART_StopBits_1 )
//				{
//					SFR_INFRA->TXSTA |= USART_StopBits_2;
//				}				
				///*******************************************************///
				///*�ַ���Ȳ���8λ����9λ,���Բ���Ҫ����*///
				//if( (SFR_INFRA->CR1&USART_WordLength_9b) != USART_WordLength_9b )
				//{
				//	SFR_INFRA->CR1 |= USART_WordLength_8b;
				//}
				///*******************************************************///
				if(((SFR_INFRA->RXSTA&USART_WordLength_9b_Parity_No) != USART_WordLength_8bNo)
						&&((SFR_INFRA->RXSTA&USART_WordLength_9b_Parity_No) != USART_WordLength_8bOdd))
				{
					SFR_INFRA->RXSTA &= (~USART_WordLength_9b_Parity_No);
					SFR_INFRA->RXSTA |= USART_WordLength_8bEven;
				}
				///*******************************************************///
				SFR_INFRA->RXSTA &= (~USART_ParityErrInt_EN);	///*��ֹ�����ж�...*///
				///*******************************************************///
				SFR_INFRA->SPBRG = USART_bps_1200;				///*1200*///
				///*******************************************************///
				SFR_INFRA->RXSTA &= (~(USART_FLAG_FE | USART_FLAG_PE|USART_FLAG_ORE));
				V_UsartDataBuff = SFR_INFRA->RXREG;				///*�建��*///
				V_UsartDataBuff = SFR_INFRA->RXSTA;				///*��״̬��*///
				V_UsartDataBuff = SFR_INFRA->RXBUFSTA;
//				SFR_INFRA->DR = V_UsartDataBuff;				///*�建��*///
				Start_Infra_Rx;									///*��ʼ����*///
				///*******************************************************///
				NVIC_EnableIRQ(Infra_IRQn);						///*�����ж�ʹ��*///
				///*******************************************************///
				break;
			}
			else
			{
				SV_InterruptMsg_Ir = C_Uart_Normal;			///*������־��Ϊ��̬*///
				SV_InitUartMsg_Ir = C_Uart_Normal;
				
				SF_InfraModulatedSignalOff();
				
				Enable_Infra_Clock;		///*����ʱ��ʹ��*///
				Select_Infra_AFMode;	///*�����߹�������AF����*///
				Select_Infra_IO_Type;	///*�����������������������������*///
				
				UART->IRCON = USART_IRCONn_WakeUp;///*38k,1:1
				///*******************************************************///
//				if( (SFR_INFRA->TXSTA&USART_StopBits_2) != USART_StopBits_1 )
//				{
//					SFR_INFRA->TXSTA |= USART_StopBits_2;
//				}				
				///*******************************************************///
				///*�ַ���Ȳ���8λ����9λ,���Բ���Ҫ����*///
				//if( (SFR_INFRA->CR1&USART_WordLength_9b) != USART_WordLength_9b )
				//{
				//	SFR_INFRA->CR1 |= USART_WordLength_8b;
				//}
				///*******************************************************///
				if(((SFR_INFRA->RXSTA&USART_WordLength_9b_Parity_No) != USART_WordLength_8bNo)
						&&((SFR_INFRA->RXSTA&USART_WordLength_9b_Parity_No) != USART_WordLength_8bOdd))
				{
					SFR_INFRA->RXSTA &= (~USART_WordLength_9b_Parity_No);
					SFR_INFRA->RXSTA |= USART_WordLength_8bEven;
				}
				///*******************************************************///
				SFR_INFRA->RXSTA &= (~USART_ParityErrInt_EN);	///*��ֹ�����ж�...*///
				///*******************************************************///
				SFR_INFRA->SPBRG = USART_bps_1200_Wakeup;				///*1200*///
				///*******************************************************///
				SFR_INFRA->RXSTA &= (~(USART_FLAG_FE | USART_FLAG_PE|USART_FLAG_ORE));
				V_UsartDataBuff = SFR_INFRA->RXREG;				///*�建��*///
				V_UsartDataBuff = SFR_INFRA->RXSTA;				///*��״̬��*///
				V_UsartDataBuff = SFR_INFRA->RXBUFSTA;
//				SFR_INFRA->DR = V_UsartDataBuff;				///*�建��*///
				Start_Infra_Rx;									///*��ʼ����*///
				///*******************************************************///
				NVIC_EnableIRQ(Infra_IRQn);						///*�����ж�ʹ��*///
				///*******************************************************///
				break;
			}
		}
		///*******************************************************///
		case C_Module:
		{
			if(C_SmartMeter!=C_Meter_Type)///*����hex���ݸ��ݱ����ж�,Զ�̼�����
			{
				SV_InterruptMsg_Modular = C_Uart_Normal;	///*������־��Ϊ��̬*///
				SV_InitUartMsg_Modular = C_Uart_Normal;
				
	//			Enable_485_2_Receive;	///*ʹ485оƬ�����ڽ���̬��3���ʽ*///
				Enable_Modular_Clock;		///*��2·485ʱ��ʹ��*///
	//			Select_Modular_UartMode;	///*ѡ��AF����ΪUart����*///
				Select_Modular_AFMode;	///*�����߹�������AF����*///
				Select_Modular_IO_Type;	///*�������������������������*///
				
	//			if( (SFR_SECOND485->TXSTA&USART_StopBits_2) != USART_StopBits_1 )
	//			{
	//				SFR_SECOND485->TXSTA |= USART_StopBits_2;
	//			}
				///*******************************************************///
				///*�ַ���Ȳ���8λ����9λ,���Բ���Ҫ����*///
				//if( (SFR_SECOND485->CR1&USART_WordLength_9b) != USART_WordLength_9b )
				//{
				//	SFR_SECOND485->CR1 |= USART_WordLength_8b;
				//}
				///*******************************************************///
				if(((SFR_MODULAR->RXSTA&USART_WordLength_9b_Parity_No) != USART_WordLength_8bNo)
						&&((SFR_MODULAR->RXSTA&USART_WordLength_9b_Parity_No) != USART_WordLength_8bOdd))
				{
					SFR_MODULAR->RXSTA &= (~USART_WordLength_9b_Parity_No);
					SFR_MODULAR->RXSTA |= USART_WordLength_8bEven;
				}
				///*******************************************************///
				SFR_MODULAR->RXSTA &= (~USART_ParityErrInt_EN);	///*��ֹ�����ж�...*///
				///*******************************************************///
				if((SFR_MODULAR->SPBRG!=USART_bps_38400) 
					&&(SFR_MODULAR->SPBRG!=USART_bps_19200) 
					&&(SFR_MODULAR->SPBRG!=USART_bps_2400)
					&&(SFR_MODULAR->SPBRG!=USART_bps_4800)
					&&(SFR_MODULAR->SPBRG!=USART_bps_1200)
					&&(SFR_MODULAR->SPBRG!=USART_bps_600)
					&&(SFR_MODULAR->SPBRG!=USART_bps_300))
				{
					SFR_MODULAR->SPBRG = USART_bps_9600;		///*�̶�9600*///
				}
				///*******************************************************///
				SFR_MODULAR->RXSTA &= (~(USART_FLAG_FE | USART_FLAG_PE|USART_FLAG_ORE));
				V_UsartDataBuff = SFR_MODULAR->RXREG;				///*�建��*///
				V_UsartDataBuff = SFR_MODULAR->RXSTA;				///*��״̬��*///
				V_UsartDataBuff = SFR_MODULAR->RXBUFSTA;			
	//			SFR_SECOND485->DR = V_UsartDataBuff;				///*�建��*///
	            
	            ///*2020��׼�����ϱ�2005*///
	            if(Inf_Comm_REPORTFlag())
	            {
	                Inf_Comm_REPORTFlagClear(0);         ///*�����ϱ���־����*///
	                Start_ModularReport_Rx;
	            }
	            else
	            {
	                Start_Modular_Rx;								///*��ʼ����*///
	            }
				///*******************************************************///
				NVIC_EnableIRQ(Modular_IRQn);					///*�����ж�ʹ��*///
				///*******************************************************///
	
	//            Inf_Comm_ClearModuleCommuniFlag();
	            if(Inf_Comm_GetModuleCommuniFlag() == (C_CommuniSafeWorld1|C_CommuniSafeWorld2|C_CommuniSafeWorld3))
	            {
	                Inf_Comm_InitModuleCommuniFlag(C_CommuniSafeWorld4);    ///*ͨ�Ž���*///
	            }
			}
			else 
			{
				///*******************************************************///
				NVIC_DisableIRQ(Modular_IRQn);					///*�����жϽ�ֹ*///
				///*******************************************************///	
				Select_Modular_ComIO_Type;///*��Զ�̱�����Ϊ��ͨIO��©�����
			}
			break;
		}
		///*******************************************************///
//		case C_ESAM:
//		{
//			NVIC_EnableIRQ(Esam_IRQn);				///*�����ж�ʹ��*///
//			
//			Enable_ESAM_Clock;						///*����ʱ��ʹ��*///
//			
//			EsamCLK_Init();
//			Select_ESAMClk_UartMode;				///*ѡ��AF������ΪUart����*///
//			
////			Set_ESAMIO_OutType;						///*�����߿�©����*///
////			Select_ESAMIO_UartMode;					///*ѡ��AF������ΪUart����*///
//			
//			Select_ESAMIO_UartMode;
//			
//			SFR_ESAMCOM->CR1 = USART_CR1_RESET;
//			SFR_ESAMCOM->CR2 = USART_CR2_RESET;
//			
//			SFR_ESAMCOM->CR1 |= USART_USART_EN;			///*Uart Enable*///
//			///*******************************************************///
//			///*����ֹͣλ*///
//			SFR_ESAMCOM->CR2 = USART_StopBits_15;	///*1.5��ֹͣλ*///
//			///*******************************************************///
//			///*����λ��������*///
//			SFR_ESAMCOM->CR1 |= USART_WordLength_9b;
//			///*******************************************************///
//			///*У��λ���ã�żУ��*///
//			SFR_ESAMCOM->CR1 |= USART_Parity_Even;
//			///*******************************************************///
//			SFR_ESAMCOM->CR3 &= USART_CR3_RESET;	///*��ֹ�����ж�...*///
//			///*******************************************************///
//			///*���ò�����*///
//			SFR_ESAMCOM->BRR = ESAM_bps;
//			///*******************************************************///
//			SFR_ESAMCOM->GTPR |= USART_GuardTime;		///*����ʱ�估��Ƶϵ��*///
//			SFR_ESAMCOM->GTPR |= USART_Prescaler;
//			SFR_ESAMCOM->CR3 |= USART_SmartCard_EN;		///*Uart ������Smartcardģʽ*///
//			SFR_ESAMCOM->CR3 |= USART_NACK_EN;			///*NACK��ʽ*///
//			
//			//SFR_ESAMCOM->CR1 |= USART_TCIE_EN;		///*ʹ�ܷ����ж�*///
//			//SFR_ESAMCOM->CR1 |= USART_TE_Set;			///*����ʹ��*///
//			SFR_ESAMCOM->CR1 &= USART_RE_DIS;			///*���ս�ֹ*///
//			SFR_ESAMCOM->CR1 &= USART_REIE_Reset_UART1;		///*�����жϽ�ֹ*///
//			
//			V_UsartDataBuff = SFR_ESAMCOM->DR;			///*�建��*///
//			V_UsartDataBuff = SFR_ESAMCOM->SR;			///*��״̬��*///
//			SFR_ESAMCOM->DR = V_UsartDataBuff;			///*�建��*///
//			
//			SFR_ESAMCOM->SR = USART_SR_RESET;
//			///*******************************************************///
//			NVIC_EnableIRQ(Esam_IRQn);					///*�����ж�ʹ��*///
//			///*******************************************************///
//			break;
//		}
		///*******************************************************///
		case C_Card:
		{
//			NVIC_EnableIRQ(Card_IRQn);				///*�����ж�ʹ��*///
//			
//			Enable_CARD_Clock;						///*����ʱ��ʹ��*///
//			
//			Select_CARDIO_UartMode;
//			
//			SFR_CARDCOM->CR1 = USART_CR1_RESET;
//			SFR_CARDCOM->CR2 = USART_CR2_RESET;
//			
//			SFR_CARDCOM->CR1 |= USART_USART_EN;			///*Uart Enable*///
//			///*******************************************************///
//			///*����ֹͣλ*///
//			SFR_CARDCOM->CR2 = USART_StopBits_15;	///*1.5��ֹͣλ*///
//			///*******************************************************///
//			///*����λ��������*///
//			SFR_CARDCOM->CR1 |= USART_WordLength_9b;
//			///*******************************************************///
//			///*У��λ���ã�żУ��*///
//			SFR_CARDCOM->CR1 |= USART_Parity_Even;
//			///*******************************************************///
//			SFR_CARDCOM->CR3 &= USART_CR3_RESET;	///*��ֹ�����ж�...*///
//			///*******************************************************///
//			///*���ò�����*///
//			SFR_CARDCOM->BRR = ESAM_bps;
//			///*******************************************************///
//			SFR_CARDCOM->GTPR |= USART_GuardTime;		///*����ʱ�估��Ƶϵ��*///
//			SFR_CARDCOM->GTPR |= USART_Prescaler;
//			SFR_CARDCOM->CR3 |= USART_SmartCard_EN;		///*Uart ������Smartcardģʽ*///
//			SFR_CARDCOM->CR3 |= USART_NACK_EN;			///*NACK��ʽ*///
//			
//			//SFR_CARDCOM->CR1 |= USART_TCIE_EN;		///*ʹ�ܷ����ж�*///
//			//SFR_CARDCOM->CR1 |= USART_TE_Set;			///*����ʹ��*///
//			SFR_CARDCOM->CR1 &= USART_RE_DIS;			///*���ս�ֹ*///
//			SFR_CARDCOM->CR1 &= USART_REIE_Reset_UART1;		///*�����жϽ�ֹ*///
//			
//			V_UsartDataBuff = SFR_CARDCOM->DR;			///*�建��*///
//			V_UsartDataBuff = SFR_CARDCOM->SR;			///*��״̬��*///
//			SFR_CARDCOM->DR = V_UsartDataBuff;			///*�建��*///
//			
//			SFR_CARDCOM->SR = USART_SR_RESET;
			///*******************************************************///
//			NVIC_DisableIRQ(Card_IRQn);					///*�����ж�ʹ��*///
			///*******************************************************///
			break;
		}
		///*******************************************************///
		default:
			;
		break;
	}
}

//uchar8 DF_Init_485_1_Com(void)
//{
//	uchar8 temp = C_OK;
//	if( SFR_FIRST485->BRR != 0x1a0b )
//	{
//		SFR_FIRST485->BRR = 0x1a0b;
//		temp = 1;
//	}
//	if( SFR_FIRST485->CR1 != 0x3424 )
//	{
//		SFR_FIRST485->CR1 = 0x3424;
//		temp |= 2;
//	}
//	if( SFR_FIRST485->CR2 != 0x2000 )
//	{
//		SFR_FIRST485->CR2 = 0x2000;
//		temp |= 4;
//	}
//	if( SFR_FIRST485->CR3 != 0x0000 )
//	{
//		SFR_FIRST485->CR3 = 0x0000;
//		temp |= 8;
//	}
//	
//	return temp;
//}

//uchar8 DF_Init_485_1(uchar8 bps,uchar8 DataLen,uchar8 StpLen,uchar8 parityChk)
//{
//    ulong32 V_UsartDataBuff;
//			SV_InterruptMsg_485_1 = C_Uart_Normal;		///*������־��Ϊ��̬*///
//			SV_InitUartMsg_485_1 = C_Uart_Normal;
//			
//			Enable_485_1_Receive;	///*ʹ485оƬ�����ڽ���̬*///
//			Enable_485_1_Clock;		///*��1·485ʱ��ʹ��*///
//			Select_485_1_UartMode;	///*ѡ��AF����ΪUart����*///
//			Select_485_1_AFMode;	///*�����߹�������AF����*///
//			Select_485_1_IO_Type;	///*�����������������������������*///
//			
//			SFR_FIRST485->CR1 = USART_CR1_RESET;
//			SFR_FIRST485->CR2 = USART_CR2_RESET;
//			
//			SFR_FIRST485->CR1 |= USART_USART_EN;			///*Uart Enable*///
//			///*******************************************************///
//			if(StpLen == C_SerStp_1)			///*����ֹͣλ*///
//			{
//				SFR_FIRST485->CR2 = USART_StopBits_1;
//			}
//			else if(StpLen == C_SerStp_2)
//			{
//				SFR_FIRST485->CR2 = USART_StopBits_2;
//			}
//			else
//			{
//				return C_Error;
//			}
//			///*******************************************************///
//			if(DataLen == C_CommDataLen8)		///*����λ��������*///
//			{
//				SFR_FIRST485->CR1 |= USART_WordLength_9b;
//			}
//			else if(DataLen == C_CommDataLen7)
//			{
//				SFR_FIRST485->CR1 |= USART_WordLength_8b;
//			}
//			else
//			{
//				return C_Error;
//			}
//			///*******************************************************///
//			if(parityChk == C_parity_Even)		///*У��λ����*///
//			{
//				SFR_FIRST485->CR1 |= USART_Parity_Even;
//			}
//			else if(parityChk == C_parity_Odd)
//			{
//				SFR_FIRST485->CR1 |= USART_Parity_Odd;
//			}
//			else if(parityChk == C_parity_None)
//			{
//				SFR_FIRST485->CR1 |= USART_Parity_No;
//			}
//			else
//			{
//				return C_Error;
//			}
//			///*******************************************************///
//			SFR_FIRST485->CR3 &= USART_CR3_RESET;	///*��ֹ�����ж�...*///
//			///*******************************************************///
//			switch(bps)							///*���ò�����*///
//			{
//				case C_bps_38400:
//					SFR_FIRST485->BRR = USART_bps_38400;	///*38400*///
//					break;
//					
//				case C_bps_19200:
//					SFR_FIRST485->BRR = USART_bps_19200;	///*19200*///
//					break;
//					
//				case C_bps_9600:
//					SFR_FIRST485->BRR = USART_bps_9600;		///*9600*///
//					break;
//					
//				case C_bps_4800:
//					SFR_FIRST485->BRR = USART_bps_4800;		///*4800*///
//					break;
//					
//				case C_bps_1200:
//					SFR_FIRST485->BRR = USART_bps_1200;		///*1200*///
//					break;
//					
//				case C_bps_600:
//					SFR_FIRST485->BRR = USART_bps_600;		///*600*///
//					break;
//					
//				case C_bps_300:
//					SFR_FIRST485->BRR = USART_bps_300;		///*300*///
//					break;
//					
//				default:
//					SFR_FIRST485->BRR = USART_bps_2400;		///*2400*///
//					break;
//			}
//			///*******************************************************///
//			SFR_FIRST485->SR = USART_SR_RESET;
//			V_UsartDataBuff = SFR_FIRST485->DR;			///*�建��*///
//			V_UsartDataBuff = SFR_FIRST485->SR;			///*��״̬��*///
//			SFR_FIRST485->DR = V_UsartDataBuff;			///*�建��*///
//			
//			Start_First485_Rx;								///*��ʼ����*///
//			///*******************************************************///
//			NVIC_EnableIRQ(First485_IRQn);					///*�����ж�ʹ��*///
//			///*******************************************************///
//    return C_OK;
//}
///************************************************************************************************************************///

///*����ԭ�ͣ�uchar8 InF_InitCommUartForDispatch(uchar8 CommNum,uchar8 bps,uchar8 DataLen,uchar8 StpLen,uchar8 parityChk)*///
///*���������                                                                                                           *///
///*	CommNum��ͨѶͨ���š�ȡֵ��C_RS485_1��C_RS485_2��C_IR��C_Module��C_ESAM��C_Card��                                *///
///*	bps�������ʡ�ȡֵ��C_bps_300, C_bps_1200, C_bps_2400, C_bps_4800, C_bps_9600��C_bps_19200, C_bps_38400           *///
///*	DataLen������λ����ȡֵC_CommDataLen7, C_CommDataLen8                                                            *///
///*	SerStp��ֹͣλ����ȡֵ1��2                                                                                       *///
///*	parityChk��ȡֵC_parity_None����У�飩, C_parity_Even��żУ�飩, C_parity_Odd����У�飩                          *///
///*�����������                                                                                                         *///
///*���ز�����C_Ok��C_Error����ڴ���                                                                                  *///
///*����˵����                                                                                                           *///
///*	1�����������������ô��ڣ�                                                                                        *///
///*	2������645Э��رմ��ڷ����жϣ��򿪽����жϣ�����7816Э��رմ��ڷ����жϣ��رս����жϡ�                       *///
///*	3�����������Ҫ����Ӧ��IF��־�ֹ����㡣                                                                          *///
///*���û��ƣ�                                                                                                           *///
///*	1���ú��������Ȳ�ֱ�ӵ��á�                                                                                      *///
///*	2�����ϵ��ʼ���ӿں������ã����γ�ʼ��485_1��485_2��IR��Module��Esam��SmartCard��ʹ�õ�Uart�ڡ�                 *///
///*	3���ṩ����ʱ�����ͽ����Ⱥ������á�                                                                              *///
///*��    ע��                                                                                                           *///
///*	1����������ForDispatch��ʾ���������е��ã�ForInterrupt��ʾ���ж�����á�                                         *///
///*	2�����ں��⴮�ڣ�����38kHz�����źŵ��ر��ź�������ܡ�                                                           *///
///************************************************************************************************************************///
uchar8 InF_InitCommUartForDispatch(uchar8 CommNum,uchar8 bps,uchar8 DataLen,uchar8 StpLen,uchar8 parityChk)
{
	uchar8 return_value = C_OK;
    ulong32 V_UsartDataBuff;
	
	Enable_ComUart_Clock;///*ʹ��commUart      
	switch(CommNum)
	{
		case C_RS485_1:
		{
			SV_InterruptMsg_485_1 = C_Uart_Normal;		///*������־��Ϊ��̬*///
			SV_InitUartMsg_485_1 = C_Uart_Normal;
			SV_Overtime_485_1 = 0;			///*��ʱ��ʱ������*///
			
			Enable_485_1_Receive;	///*ʹ485оƬ�����ڽ���̬*///
			Enable_485_1_Clock;		///*��1·485ʱ��ʹ��*///
			Select_485_1_AFMode;	///*�����߹�������AF����*///
			Select_485_1_IO_Type;	///*�����������������������������*///
			
			///*******************************************************///
			SFR_FIRST485->TXSTA &= (~USART_StopBits_2);
			if(StpLen == C_SerStp_1)			/*����ֹͣλ*///
			{
				SFR_FIRST485->TXSTA |= USART_StopBits_1;
			}
			else if(StpLen == C_SerStp_2)
			{
				SFR_FIRST485->TXSTA |= USART_StopBits_2;
			}
			else
			{
				return C_Error;
			}
			///*******************************************************///
			SFR_FIRST485->RXSTA &= USART_WordLength_Even_Reset;
//			if(DataLen == C_CommDataLen8)		/*����λ��������,��żУ��*///
//			{
//				if(parityChk == C_parity_None)
//				{
//					SFR_FIRST485->RXSTA |= USART_WordLength_9b_Parity_No;
//				}
//				else
//				{
//					return C_Error;
//				}
//			}
//			else 
//			{
				if(DataLen == C_CommDataLen8)
				{
					if(parityChk == C_parity_Even)
					{
						SFR_FIRST485->RXSTA |= USART_WordLength_8bEven;
					}
					else
					{
						if(parityChk == C_parity_Odd)
						{
							SFR_FIRST485->RXSTA |= USART_WordLength_8bOdd;
						}	
						else 
						{
							SFR_FIRST485->RXSTA |= USART_WordLength_8bNo;
						}			
					}
				}
				else
				{
					return C_Error;
				}				
//			}

			///*******************************************************///
			SFR_FIRST485->RXSTA &= (~USART_ParityErrInt_EN);	///*��ֹ�����ж�...*///
			///*******************************************************///
			switch(bps)							///*���ò�����*///
			{
				case C_bps_38400:
					SFR_FIRST485->SPBRG = USART_bps_38400;	///*38400*///
					break;
					
				case C_bps_19200:
					SFR_FIRST485->SPBRG = USART_bps_19200;	///*19200*///
					break;
					
				case C_bps_2400:
					SFR_FIRST485->SPBRG = USART_bps_2400;		///*2400*///
					break;
					
				case C_bps_4800:
					SFR_FIRST485->SPBRG = USART_bps_4800;		///*4800*///
					break;
					
				case C_bps_1200:
					SFR_FIRST485->SPBRG = USART_bps_1200;		///*1200*///
					break;
					
				case C_bps_600:
					SFR_FIRST485->SPBRG = USART_bps_600;		///*600*///
					break;
					
				case C_bps_300:
					SFR_FIRST485->SPBRG = USART_bps_300;		///*300*///
					break;
					
				default:
					SFR_FIRST485->SPBRG = USART_bps_9600;		///*9600*///
					break;
			}
			///*******************************************************///
			SFR_FIRST485->RXSTA &= (~(USART_FLAG_FE | USART_FLAG_PE|USART_FLAG_ORE));
			V_UsartDataBuff = SFR_FIRST485->RXREG;				///*�建��*///
			V_UsartDataBuff = SFR_FIRST485->RXSTA;				///*��״̬��*///
			V_UsartDataBuff = SFR_FIRST485->RXBUFSTA;
//			SFR_FIRST485->RXREG = V_UsartDataBuff;				///*�建��*///
			
			Start_First485_Rx;								///*��ʼ����*///
			///*******************************************************///
			NVIC_EnableIRQ(First485_IRQn);					///*�����ж�ʹ��*///
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_RS485_2:
///*		case C_Module:
		{
			if(C_SmartMeter==C_Meter_Type)///*����hex���ݸ��ݱ����ж�
			{
				///*��·������־����ʼ��*///
				SV_InterruptMsg_485_2 = C_Uart_Normal;		///*������־��Ϊ��̬*///
				SV_InitUartMsg_485_2 = C_Uart_Normal;
				SV_InterruptMsg_Modular = C_Uart_Normal;	///*������־��Ϊ��̬*///
				SV_InitUartMsg_Modular = C_Uart_Normal;
				SV_Overtime_485_2 = 0;			///*��ʱ��ʱ������*///
				
				Enable_485_2_Receive;	///*ʹ485оƬ�����ڽ���̬��3���ʽ*///
				Enable_485_2_Clock;		///*��2·485ʱ��ʹ��*///
				Select_485_2_AFMode;	///*�����߹�������AF����*///
				Select_485_2_IO_Type;	///*�������������������������*///
				
				
				SFR_SECOND485->TXSTA &= (~USART_StopBits_2);
				///*******************************************************///
				if(StpLen == C_SerStp_1)			/*����ֹͣλ*///
				{
					SFR_SECOND485->TXSTA |= USART_StopBits_1;
				}
				else if(StpLen == C_SerStp_2)
				{
					SFR_SECOND485->TXSTA |= USART_StopBits_2;
				}
				else
				{
					return C_Error;
				}
				///*******************************************************///
				SFR_SECOND485->RXSTA &= USART_WordLength_Even_Reset;
	//			if(DataLen == C_CommDataLen8)		/*����λ��������,��żУ��*///
	//			{
	//				if(parityChk == C_parity_None)
	//				{
	//					SFR_SECOND485->RXSTA |= USART_WordLength_9b_Parity_No;
	//				}
	//				else
	//				{
	//					return C_Error;
	//				}
	//			}
	//			else 
	//			{
					if(DataLen == C_CommDataLen8)
					{
						if(parityChk == C_parity_Even)
						{
							SFR_SECOND485->RXSTA |= USART_WordLength_8bEven;
						}
						else
						{
							if(parityChk == C_parity_Odd)
							{
								SFR_SECOND485->RXSTA |= USART_WordLength_8bOdd;
							}	
							else 
							{
								SFR_SECOND485->RXSTA |= USART_WordLength_8bNo;
							}			
						}
					}
					else
					{
						return C_Error;
					}				
	//			}
				///*******************************************************///
				SFR_SECOND485->RXSTA &= (~USART_ParityErrInt_EN);	///*��ֹ�����ж�...*///
				///*******************************************************///
				switch(bps)							///*���ò�����*///
				{
					case C_bps_38400:
						SFR_SECOND485->SPBRG = USART_bps_38400;	///*38400*///
						break;
						
					case C_bps_19200:
						SFR_SECOND485->SPBRG = USART_bps_19200;	///*19200*///
						break;
						
					case C_bps_2400:
						SFR_SECOND485->SPBRG = USART_bps_2400;		///*2400*///
						break;
						
					case C_bps_4800:
						SFR_SECOND485->SPBRG = USART_bps_4800;		///*4800*///
						break;
						
					case C_bps_1200:
						SFR_SECOND485->SPBRG = USART_bps_1200;		///*1200*///
						break;
						
					case C_bps_600:
						SFR_SECOND485->SPBRG = USART_bps_600;		///*600*///
						break;
						
					case C_bps_300:
						SFR_SECOND485->SPBRG = USART_bps_300;		///*300*///
						break;
						
					default:
						SFR_SECOND485->SPBRG = USART_bps_9600;		///*9600*///
						break;
				}
				///*******************************************************///
				SFR_SECOND485->RXSTA &= (~(USART_FLAG_FE | USART_FLAG_PE|USART_FLAG_ORE));
				V_UsartDataBuff = SFR_SECOND485->RXREG;			///*�建��*///
				V_UsartDataBuff = SFR_SECOND485->RXSTA;			///*��״̬��*///
				V_UsartDataBuff = SFR_SECOND485->RXBUFSTA;
	//			SFR_SECOND485->DR = V_UsartDataBuff;			///*�建��*///
				Start_Second485_Rx;			///*��ʼ����*///
				///*******************************************************///
				NVIC_EnableIRQ(Second485_IRQn);					///*�����ж�ʹ��*///
				///*******************************************************///
			}
			else 
			{
				///*******************************************************///
				NVIC_DisableIRQ(Second485_IRQn);					///*�����жϽ�ֹ*///
				///*******************************************************///	
				if(C_R_SmartMeter==C_Meter_Type)///*���ر��ӿڵ������ã�Զ�̱�����Ϊ��©�����
				{
					Select_485_2_ComIO_Type;
				}	
			}
			break;
		}
		case C_Module:
		{
			if(C_SmartMeter!=C_Meter_Type)///*����hex���ݸ��ݱ����ж�,Զ�̼�����
			{
				///*��·������־����ʼ��*///
				SV_InterruptMsg_485_2 = C_Uart_Normal;		///*������־��Ϊ��̬*///
				SV_InitUartMsg_485_2 = C_Uart_Normal;
				SV_InterruptMsg_Modular = C_Uart_Normal;	///*������־��Ϊ��̬*///
				SV_InitUartMsg_Modular = C_Uart_Normal;
				SV_Overtime_485_2 = 0;			///*��ʱ��ʱ������*///
				
	///*			Enable_485_2_Receive;	///*ʹ485оƬ�����ڽ���̬��3���ʽ*///
				Enable_Modular_Clock;		///*��2·485ʱ��ʹ��*///
				Select_Modular_AFMode;	///*�����߹�������AF����*///
				Select_Modular_IO_Type;	///*�������������������������*///
				
				
				SFR_MODULAR->TXSTA &= (~USART_StopBits_2);
				///*******************************************************///
				if(StpLen == C_SerStp_1)			/*����ֹͣλ*///
				{
					SFR_MODULAR->TXSTA |= USART_StopBits_1;
				}
				else if(StpLen == C_SerStp_2)
				{
					SFR_MODULAR->TXSTA |= USART_StopBits_2;
				}
				else
				{
					return C_Error;
				}
				///*******************************************************///
				SFR_MODULAR->RXSTA &= USART_WordLength_Even_Reset;
	//			if(DataLen == C_CommDataLen8)		/*����λ��������,��żУ��*///
	//			{
	//				if(parityChk == C_parity_None)
	//				{
	//					SFR_SECOND485->RXSTA |= USART_WordLength_9b_Parity_No;
	//				}
	//				else
	//				{
	//					return C_Error;
	//				}
	//			}
	//			else 
	//			{
					if(DataLen == C_CommDataLen8)
					{
						if(parityChk == C_parity_Even)
						{
							SFR_MODULAR->RXSTA |= USART_WordLength_8bEven;
						}
						else
						{
							if(parityChk == C_parity_Odd)
							{
								SFR_MODULAR->RXSTA |= USART_WordLength_8bOdd;
							}	
							else 
							{
								SFR_MODULAR->RXSTA |= USART_WordLength_8bNo;
							}			
						}
					}
					else
					{
						return C_Error;
					}				
	//			}
				///*******************************************************///
				switch(bps)							///*���ò�����*///
				{
					case C_bps_38400:
						SFR_MODULAR->SPBRG = USART_bps_38400;	///*38400*///
						break;
						
					case C_bps_19200:
						SFR_MODULAR->SPBRG = USART_bps_19200;	///*19200*///
						break;
						
					case C_bps_2400:
						SFR_MODULAR->SPBRG = USART_bps_2400;		///*2400*///
						break;
						
					case C_bps_4800:
						SFR_MODULAR->SPBRG = USART_bps_4800;		///*4800*///
						break;
						
					case C_bps_1200:
						SFR_MODULAR->SPBRG = USART_bps_1200;		///*1200*///
						break;
						
					case C_bps_600:
						SFR_MODULAR->SPBRG = USART_bps_600;		///*600*///
						break;
						
					case C_bps_300:
						SFR_MODULAR->SPBRG = USART_bps_300;		///*300*///
						break;
						
					default:
						SFR_MODULAR->SPBRG = USART_bps_9600;		///*9600*///
						break;
				}
				
	//			SFR_MODULAR->SPBRG = USART_bps_9600;		///*�̶�9600*///
				///*******************************************************///
				SFR_MODULAR->RXSTA &= (~(USART_FLAG_FE | USART_FLAG_PE|USART_FLAG_ORE));
				V_UsartDataBuff = SFR_MODULAR->RXREG;			///*�建��*///
				V_UsartDataBuff = SFR_MODULAR->RXSTA;			///*��״̬��*///
				V_UsartDataBuff = SFR_MODULAR->RXBUFSTA;
	//			SFR_SECOND485->DR = V_UsartDataBuff;			///*�建��*///
	            ///*2020��׼�����ϱ�*///
	            if(Inf_Comm_REPORTFlag() != C_ReportNULL)           ///*���ܴ����¼��ϱ����ߵ����ϱ�*///
	            {
	                Start_ModularReport_Rx;     //*��ʼ���ղ��ط���*///
	            }
	            else
	            {
	                Start_Modular_Rx;			///*��ʼ����*///
	            }
	            //Inf_Comm_InitModuleCommuniFlag(C_CommuniSafeWorld1|C_CommuniSafeWorld2|C_CommuniSafeWorld3|C_CommuniSafeWorld4);
	            Inf_Comm_ClearModuleCommuniFlag(0);
#if 0
                Inf_Comm_REPORTFlagClear(0);            /*���ܳ�ʼ������Ϊ���ͨ�Ŵ��󣬾ͻ��ʼ��������ʱ����ܴ����ϱ�������*/
#endif
				///*******************************************************///
				NVIC_EnableIRQ(Modular_IRQn);					///*�����ж�ʹ��*///
				///*******************************************************///
			}
			else 
			{
				///*******************************************************///
				NVIC_DisableIRQ(Modular_IRQn);					///*�����жϽ�ֹ*///
				///*******************************************************///	
				Select_Modular_ComIO_Type;///*��Զ�̱�����Ϊ��ͨIO��©�����
			}
			break;
		}		
		///*******************************************************///
		case C_IR:
		{
			if( InF_ReadPowerState() == C_PowerOn )
			{	
				SV_InterruptMsg_Ir = C_Uart_Normal;			///*������־��Ϊ��̬*///
				SV_InitUartMsg_Ir = C_Uart_Normal;
				SV_Overtime_Ir = 0;			///*��ʱ��ʱ������*///
				
				SF_InfraModulatedSignalOff();
				
				Enable_Infra_Clock;		///*����ʱ��ʹ��*///
				Select_Infra_AFMode;	///*�����߹�������AF����*///
				Select_Infra_IO_Type;	///*�����������������������������*///
				
				UART->IRCON = USART_IRCONn;///*38k,1:1
				SFR_INFRA->TXSTA &= (~USART_StopBits_2);
				///*******************************************************///
				if(StpLen == C_SerStp_1)			/*����ֹͣλ*///
				{
					SFR_INFRA->TXSTA |= USART_StopBits_1;
				}
				else if(StpLen == C_SerStp_2)
				{
					SFR_INFRA->TXSTA |= USART_StopBits_2;
				}
				else
				{
					return C_Error;
				}
				///*******************************************************///
			SFR_INFRA->RXSTA &= USART_WordLength_Even_Reset;
//			if(DataLen == C_CommDataLen8)		/*����λ��������,��żУ��*///
//			{
//				if(parityChk == C_parity_None)
//				{
//					SFR_INFRA->RXSTA |= USART_WordLength_9b_Parity_No;
//				}
//				else
//				{
//					return C_Error;
//				}
//			}
//			else 
//			{
				if(DataLen == C_CommDataLen8)
				{
					if(parityChk == C_parity_Even)
					{
						SFR_INFRA->RXSTA |= USART_WordLength_8bEven;
					}
					else
					{
						if(parityChk == C_parity_Odd)
						{
							SFR_INFRA->RXSTA |= USART_WordLength_8bOdd;
						}	
						else 
						{
							SFR_INFRA->RXSTA |= USART_WordLength_8bNo;
						}			
					}
				}
				else
				{
					return C_Error;
				}				
//			}
				///*******************************************************///
				SFR_INFRA->RXSTA &= (~USART_ParityErrInt_EN);	///*��ֹ�����ж�...*///
				///*******************************************************///
				SFR_INFRA->SPBRG = USART_bps_1200;				///*1200*///
				///*******************************************************///
				SFR_INFRA->RXSTA &= (~(USART_FLAG_FE | USART_FLAG_PE|USART_FLAG_ORE));
				V_UsartDataBuff = SFR_INFRA->RXREG;				///*�建��*///
				V_UsartDataBuff = SFR_INFRA->RXSTA;				///*��״̬��*///
				V_UsartDataBuff = SFR_INFRA->RXBUFSTA;
//				SFR_INFRA->DR = V_UsartDataBuff;				///*�建��*///
				Start_Infra_Rx;									///*��ʼ����*///
				///*******************************************************///
				NVIC_EnableIRQ(Infra_IRQn);						///*�����ж�ʹ��*///
				///*******************************************************///
				break;
			}
			else
			{
				SV_InterruptMsg_Ir = C_Uart_Normal;			///*������־��Ϊ��̬*///
				SV_InitUartMsg_Ir = C_Uart_Normal;
				
				SF_InfraModulatedSignalOff();
				
				Enable_Infra_Clock;		///*����ʱ��ʹ��*///
				Select_Infra_AFMode;	///*�����߹�������AF����*///
				Select_Infra_IO_Type;	///*�����������������������������*///
				
				UART->IRCON = USART_IRCONn_WakeUp;///*38k,1:1
				SFR_INFRA->TXSTA &= (~USART_StopBits_2);
				///*******************************************************///
				if(StpLen == C_SerStp_1)			/*����ֹͣλ*///
				{
					SFR_INFRA->TXSTA |= USART_StopBits_1;
				}
				else if(StpLen == C_SerStp_2)
				{
					SFR_INFRA->TXSTA |= USART_StopBits_2;
				}
				else
				{
					return C_Error;
				}
				///*******************************************************///
			SFR_INFRA->RXSTA &= USART_WordLength_Even_Reset;
//			if(DataLen == C_CommDataLen8)		/*����λ��������,��żУ��*///
//			{
//				if(parityChk == C_parity_None)
//				{
//					SFR_INFRA->RXSTA |= USART_WordLength_9b_Parity_No;
//				}
//				else
//				{
//					return C_Error;
//				}
//			}
//			else 
//			{
				if(DataLen == C_CommDataLen8)
				{
					if(parityChk == C_parity_Even)
					{
						SFR_INFRA->RXSTA |= USART_WordLength_8bEven;
					}
					else
					{
						if(parityChk == C_parity_Odd)
						{
							SFR_INFRA->RXSTA |= USART_WordLength_8bOdd;
						}	
						else 
						{
							SFR_INFRA->RXSTA |= USART_WordLength_8bNo;
						}			
					}
				}
				else
				{
					return C_Error;
				}				
//			}
				///*******************************************************///
				SFR_INFRA->RXSTA &= (~USART_ParityErrInt_EN);	///*��ֹ�����ж�...*///
				///*******************************************************///
				SFR_INFRA->SPBRG = USART_bps_1200_Wakeup;				///*1200*///
				///*******************************************************///
				SFR_INFRA->RXSTA &= (~(USART_FLAG_FE | USART_FLAG_PE|USART_FLAG_ORE));
				V_UsartDataBuff = SFR_INFRA->RXREG;				///*�建��*///
				V_UsartDataBuff = SFR_INFRA->RXSTA;				///*��״̬��*///
				V_UsartDataBuff = SFR_INFRA->RXBUFSTA;
//				SFR_INFRA->DR = V_UsartDataBuff;				///*�建��*///
				Start_Infra_Rx;									///*��ʼ����*///
				///*******************************************************///
				NVIC_EnableIRQ(Infra_IRQn);						///*�����ж�ʹ��*///
				///*******************************************************///
				break;
			}
		}
		///*******************************************************///
//		case C_ESAM:
//		{
////			NVIC_EnableIRQ(Esam_IRQn);				///*�����ж�ʹ��*///
//			
//			Enable_ESAM_Clock;						///*����ʱ��ʹ��*///
//			
//			EsamCLK_Init();
//			Select_ESAMClk_UartMode;				///*ѡ��AF������ΪUart����*///
//			
////			Set_ESAMIO_OutType;						///*�����߿�©����*///
////			Select_ESAMIO_UartMode;					///*ѡ��AF������ΪUart����*///
//			
//			Select_ESAMIO_UartMode;
//			
//			SFR_ESAMCOM->CR1 = USART_CR1_RESET;
//			SFR_ESAMCOM->CR2 = USART_CR2_RESET;
//			
//			SFR_ESAMCOM->CR1 |= USART_USART_EN;			///*Uart Enable*///
//			///*******************************************************///
//			///*����ֹͣλ*///
//			SFR_ESAMCOM->CR2 = USART_StopBits_15;	///*1.5��ֹͣλ*///
//			///*******************************************************///
//			///*����λ��������*///
//			SFR_ESAMCOM->CR1 |= USART_WordLength_9b;
//			///*******************************************************///
//			///*У��λ���ã�żУ��*///
//			SFR_ESAMCOM->CR1 |= USART_Parity_Even;
//			///*******************************************************///
//			SFR_ESAMCOM->CR3 &= USART_CR3_RESET;	///*��ֹ�����ж�...*///
//			///*******************************************************///
//			///*���ò�����*///
//			SFR_ESAMCOM->BRR = ESAM_bps;
//			///*******************************************************///
//			SFR_ESAMCOM->GTPR |= USART_GuardTime;		///*����ʱ�估��Ƶϵ��*///
//			SFR_ESAMCOM->GTPR |= USART_Prescaler;
//			SFR_ESAMCOM->CR3 |= USART_SmartCard_EN;		///*Uart ������Smartcardģʽ*///
//			SFR_ESAMCOM->CR3 |= USART_NACK_EN;			///*NACK��ʽ*///
//			
//			//SFR_ESAMCOM->CR1 |= USART_TCIE_EN;		///*ʹ�ܷ����ж�*///
//			//SFR_ESAMCOM->CR1 |= USART_TE_Set;			///*����ʹ��*///
//			SFR_ESAMCOM->CR1 &= USART_RE_DIS;			///*���ս�ֹ*///
//			SFR_ESAMCOM->CR1 &= USART_REIE_Reset_UART1;		///*�����жϽ�ֹ*///
//			
//			V_UsartDataBuff = SFR_ESAMCOM->DR;			///*�建��*///
//			V_UsartDataBuff = SFR_ESAMCOM->SR;			///*��״̬��*///
//			SFR_ESAMCOM->DR = V_UsartDataBuff;			///*�建��*///
//			
//			SFR_ESAMCOM->SR = USART_SR_RESET;
//			///*******************************************************///
//			NVIC_EnableIRQ(Esam_IRQn);					///*�����ж�ʹ��*///
//			///*******************************************************///
//			break;
//		}
		///*******************************************************///
		case C_Card:
		{
//			NVIC_EnableIRQ(Card_IRQn);				///*�����ж�ʹ��*///
			
//			Enable_CARD_Clock;						///*����ʱ��ʹ��*///
//			
//			Select_CARDIO_UartMode;
//			
//			SFR_CARDCOM->CR1 = USART_CR1_RESET;
//			SFR_CARDCOM->CR2 = USART_CR2_RESET;
//			
//			SFR_CARDCOM->CR1 |= USART_USART_EN;			///*Uart Enable*///
//			///*******************************************************///
//			///*����ֹͣλ*///
//			SFR_CARDCOM->CR2 = USART_StopBits_15;	///*1.5��ֹͣλ*///
//			///*******************************************************///
//			///*����λ��������*///
//			SFR_CARDCOM->CR1 |= USART_WordLength_9b;
//			///*******************************************************///
//			///*У��λ���ã�żУ��*///
//			SFR_CARDCOM->CR1 |= USART_Parity_Even;
//			///*******************************************************///
//			SFR_CARDCOM->CR3 &= USART_CR3_RESET;	///*��ֹ�����ж�...*///
//			///*******************************************************///
//			///*���ò�����*///
//			SFR_CARDCOM->BRR = ESAM_bps;
//			///*******************************************************///
//			SFR_CARDCOM->GTPR |= USART_GuardTime;		///*����ʱ�估��Ƶϵ��*///
//			SFR_CARDCOM->GTPR |= USART_Prescaler;
//			SFR_CARDCOM->CR3 |= USART_SmartCard_EN;		///*Uart ������Smartcardģʽ*///
//			SFR_CARDCOM->CR3 |= USART_NACK_EN;			///*NACK��ʽ*///
//			
//			//SFR_CARDCOM->CR1 |= USART_TCIE_EN;		///*ʹ�ܷ����ж�*///
//			//SFR_CARDCOM->CR1 |= USART_TE_Set;			///*����ʹ��*///
////			SFR_CARDCOM->CR1 &= USART_RE_DIS;			///*���ս�ֹ*///
////			SFR_CARDCOM->CR1 &= USART_REIE_Reset_UART1;		///*�����жϽ�ֹ*///
//			
//			V_UsartDataBuff = SFR_CARDCOM->DR;			///*�建��*///
//			V_UsartDataBuff = SFR_CARDCOM->SR;			///*��״̬��*///
//			SFR_CARDCOM->DR = V_UsartDataBuff;			///*�建��*///
//			
//			SFR_CARDCOM->SR = USART_SR_RESET;
//			///*******************************************************///
//			NVIC_DisableIRQ(Card_IRQn);					///*�����ж�ʹ��*///
			///*******************************************************///
			break;
		}
		///*******************************************************///
		default:
			return_value = C_Error;
		break;
	}
	return return_value;
}

///***************************************************************************************************///
///*����ԭ�ͣ�uchar8 InF_CommUart_RecDisableForInterrupt (uchar8 CommNum)                            *///
///*��ڲ�����CommNum��ͨѶͨ���š�ȡֵ��ȡֵ��C_RS485_1��C_RS485_2��C_IR��C_Module��C_ESAM��C_Card��*///
///*�����������                                                                                     *///
///*���ز�����C_Ok��C_Error����ڴ���                                                              *///
///*����˵�����رմ��ڽ��գ����������ж�ʹ��                                                         *///
///*��    ע����������ForDispatch��ʾ���������е��ã�ForInterrupt��ʾ���ж�����á�                  *///
///***************************************************************************************************///
uchar8 InF_CommUart_RecDisableForInterrupt(uchar8 CommNum)
{
	uchar8 return_value = C_OK;
//	ulong32 V_UsartDataBuff = 0;
	
	switch(CommNum)
	{
		case C_RS485_1:
		{
			///*******************************************************///
			Stop_First485_Rx;								///*ֹͣ����*///
			return_value = SFR_FIRST485->RXREG;			///*���յ����ݶ��뻺��*///
			return_value = C_OK;
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_RS485_2:
		{
			///*******************************************************///
			Stop_Second485_Rx;								///*ֹͣ����*///
			return_value = SFR_SECOND485->RXREG;			///*���յ����ݶ��뻺��*///
			return_value = C_OK;
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_IR:
		{
			///*******************************************************///
			Stop_Infra_Rx;									///*ֹͣ����*///
			return_value = SFR_INFRA->RXREG;			///*���յ����ݶ��뻺��*///
			return_value = C_OK;
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_Module:
		{
			///*******************************************************///
			Stop_Modular_Rx;								///*ֹͣ����*///
			return_value = SFR_MODULAR->RXREG;			///*���յ����ݶ��뻺��*///
			return_value = C_OK;
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_ESAM:
		{
			
			break;
		}
		///*******************************************************///
		case C_Card:
		{
			
			break;
		}
		///*******************************************************///
		default:
			return_value = C_Error;
		break;
	}
	return return_value;
}

///***************************************************************************************************///
///*����ԭ�ͣ�uchar8 InF_CommUart_RecDisableForDispatch (uchar8 CommNum)                             *///
///*��ڲ�����CommNum��ͨѶͨ���š�ȡֵ��ȡֵ��C_RS485_1��C_RS485_2��C_IR��C_Module��C_ESAM��C_Card��*///
///*�����������                                                                                     *///
///*���ز�����C_Ok��C_Error����ڴ���                                                              *///
///*����˵�����رմ��ڽ��գ����������ж�ʹ��                                                         *///
///*��    ע����������ForDispatch��ʾ���������е��ã�ForInterrupt��ʾ���ж�����á�                  *///
///***************************************************************************************************///
uchar8 InF_CommUart_RecDisableForDispatch(uchar8 CommNum)
{
	uchar8 return_value = C_OK;
//	ulong32 V_UsartDataBuff = 0;
	
	switch(CommNum)
	{
		case C_RS485_1:
		{
			///*******************************************************///
			Stop_First485_Rx;								///*ֹͣ����*///
			return_value = SFR_FIRST485->RXREG;			///*���յ����ݶ��뻺��*///
			return_value = C_OK;
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_RS485_2:
		{
			///*******************************************************///
			Stop_Second485_Rx;								///*ֹͣ����*///
			return_value = SFR_SECOND485->RXREG;			///*���յ����ݶ��뻺��*///
			return_value = C_OK;
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_IR:
		{
			///*******************************************************///
			Stop_Infra_Rx;									///*ֹͣ����*///
			return_value = SFR_INFRA->RXREG;			///*���յ����ݶ��뻺��*///
			return_value = C_OK;
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_Module:
		{
			///*******************************************************///
			Stop_Modular_Rx;								///*ֹͣ����*///
			return_value = SFR_MODULAR->RXREG;			///*���յ����ݶ��뻺��*///
			return_value = C_OK;
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_ESAM:			/* ESAM����SPI�ڲ��� */
		{
			
			break;
		}
		///*******************************************************///
		case C_Card:
		{
			
			break;
		}
		///*******************************************************///
		default:
			return_value = C_Error;
		break;
	}
	return return_value;
}

///***********************************************************************************///
///*����ԭ�ͣ�uchar8 InF_CommUart_RecEnableForInterrupt (uchar8 CommNum)             *///
///*��ڲ�����CommNum��ͨѶͨ���š�ȡֵ��C_ESAM��C_Card��                            *///
///*�����������                                                                     *///
///*���ز�����C_Ok��C_Error����ڴ���                                              *///
///*����˵���������ڽ��գ����������ж�ʹ�ܣ��رմ��ڷ��ͣ����������жϡ�           *///
///*��    ע��                                                                       *///
///*	1������645Э�飬���ܱ��Ǵ�ģʽ����˳�ʼ������ʱ���ܱ�ʹ��ڵȴ�����״̬��   *///
///*	   ����7816Э�飬���ܱ�����ģʽ����ʱ�����ǹرյģ�                          *///
///*	   �����Ҫ�ṩһ���ӿں���ʹ�ܴ��ڴ��ڽ���״̬���򿪽����жϣ��رշ��͹��ܡ�*///
///*	2�����ں��⴮�ڣ���Ҫ�ر�38kHz�����ź�������ܡ�                             *///
///*	3����������ForDispatch��ʾ���������е��ã�ForInterrupt��ʾ���ж�����á�     *///
///***********************************************************************************///
uchar8 InF_CommUart_RecEnableForInterrupt(uchar8 CommNum)
{
	uchar8 return_value = C_OK;

	switch(CommNum)
	{
		case C_RS485_1:
		{
			Enable_485_1_Receive;
			///*******************************************************///
			Start_First485_Rx;								///*��ʼ����*///
			///*******************************************************///
			NVIC_EnableIRQ(First485_IRQn);					///*�����ж�ʹ��*///
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_RS485_2:
		{
			if(C_SmartMeter==C_Meter_Type)
			{
				Enable_485_2_Receive;
				///*******************************************************///
				Start_Second485_Rx;								///*��ʼ����*///
				///*******************************************************///
				NVIC_EnableIRQ(Second485_IRQn);					///*�����ж�ʹ��*///
				///*******************************************************///
			}
			break;
		}
		///*******************************************************///
		case C_IR:
		{
			SF_InfraModulatedSignalOff();
			///*******************************************************///
			Start_Infra_Rx;									///*��ʼ����*///
			///*******************************************************///
			NVIC_EnableIRQ(Infra_IRQn);						///*�����ж�ʹ��*///
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_Module:			///*ģ�����2·RS485����*///
		{
			if(C_SmartMeter!=C_Meter_Type)///*����hex���ݸ��ݱ����ж�,Զ�̼�����
			{
				///*******************************************************///
				Start_Modular_Rx;								///*��ʼ����*///
				///*******************************************************///
				NVIC_EnableIRQ(Modular_IRQn);					///*�����ж�ʹ��*///
				///*******************************************************///
			}
			break;
		}
		///*******************************************************///
//		case C_ESAM:
//		{
//			///*******************************************************///
//			SFR_ESAMCOM->CR1 &= USART_TCIE_DIS;				///*��ֹ�����ж�*///
//			SFR_ESAMCOM->CR1 &= USART_TE_Reset;				///*���ͽ�ֹ*///
//			SFR_ESAMCOM->CR1 |= USART_RE_EN;				///*����ʹ��*///
//			//SFR_ESAMCOM->CR1 |= USART_REIE_Set_UART1;				///*�����ж�ʹ��*///
//			SFR_ESAMCOM->SR &= (~USART_FLAG_RXNE);			///*������жϱ�־*///
//			///*******************************************************///
//			NVIC_DisableIRQ(Esam_IRQn);						///*�����ж�ʹ��*///
//			///*******************************************************///
//			break;
//		}
		///*******************************************************///
		case C_Card:
		{
			///*******************************************************///
//			SFR_CARDCOM->CR1 &= USART_TCIE_DIS;				///*��ֹ�����ж�*///
//			SFR_CARDCOM->CR1 &= USART_TE_Reset;				///*���ͽ�ֹ*///
//			SFR_CARDCOM->CR1 |= USART_RE_EN;				///*����ʹ��*///
//			//SFR_CARDCOM->CR1 |= USART_REIE_Set_UART1;				///*�����ж�ʹ��*///
//			SFR_CARDCOM->SR &= (~USART_FLAG_RXNE);			///*������жϱ�־*///
			///*******************************************************///
//			NVIC_DisableIRQ(Card_IRQn);						///*�����ж�ʹ��*///
			///*******************************************************///
			break;
		}
		///*******************************************************///
		default:
			return_value = C_Error;
		break;
	}
	return return_value;
}

///***********************************************************************************///
///*����ԭ�ͣ�uchar8 InF_CommUart_RecEnableForDispatch (uchar8 CommNum)              *///
///*��ڲ�����CommNum��ͨѶͨ���š�ȡֵ��C_ESAM��C_Card��                            *///
///*�����������                                                                     *///
///*���ز�����C_Ok��C_Error����ڴ���                                              *///
///*����˵���������ڽ��գ����������ж�ʹ�ܣ��رմ��ڷ��ͣ����������жϡ�           *///
///*��    ע��                                                                       *///
///*	1������645Э�飬���ܱ��Ǵ�ģʽ����˳�ʼ������ʱ���ܱ�ʹ��ڵȴ�����״̬��   *///
///*	   ����7816Э�飬���ܱ�����ģʽ����ʱ�����ǹرյģ�                          *///
///*	   �����Ҫ�ṩһ���ӿں���ʹ�ܴ��ڴ��ڽ���״̬���򿪽����жϣ��رշ��͹��ܡ�*///
///*	2�����ں��⴮�ڣ���Ҫ�ر�38kHz�����ź�������ܡ�                             *///
///*	3����������ForDispatch��ʾ���������е��ã�ForInterrupt��ʾ���ж�����á�     *///
///***********************************************************************************///
uchar8 InF_CommUart_RecEnableForDispatch(uchar8 CommNum)
{
	uchar8 return_value = C_OK;
//	uchar8 V_UsartDataBuff;

	switch(CommNum)
	{
		case C_RS485_1:
		{
			Enable_485_1_Receive;
			///*******************************************************///
			Start_First485_Rx;								///*��ʼ����*///
			///*******************************************************///
			NVIC_EnableIRQ(First485_IRQn);					///*�����ж�ʹ��*///
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_RS485_2:
		{
			if(C_SmartMeter==C_Meter_Type)
			{
				Enable_485_2_Receive;
				///*******************************************************///
				Start_Second485_Rx;								///*��ʼ����*///
				///*******************************************************///
				NVIC_EnableIRQ(Second485_IRQn);					///*�����ж�ʹ��*///
				///*******************************************************///
			}
			break;
		}
		///*******************************************************///
		case C_IR:
		{
			SF_InfraModulatedSignalOff();
			///*******************************************************///
			Start_Infra_Rx;									///*��ʼ����*///
			///*******************************************************///
			NVIC_EnableIRQ(Infra_IRQn);						///*�����ж�ʹ��*///
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_Module:			///*ģ�����2·RS485����*///
		{
			if(C_SmartMeter!=C_Meter_Type)///*����hex���ݸ��ݱ����ж�,Զ�̼�����
			{
				///*******************************************************///
				Start_Modular_Rx;								///*��ʼ����*///
				///*******************************************************///
				NVIC_EnableIRQ(Modular_IRQn);					///*�����ж�ʹ��*///
				///*******************************************************///
			}
			break;
		}
		///*******************************************************///
//		case C_ESAM:
//		{
//			///*******************************************************///
//			SFR_ESAMCOM->CR1 &= USART_TCIE_DIS;				///*��ֹ�����ж�*///
//			SFR_ESAMCOM->CR1 &= USART_TE_Reset;				///*���ͽ�ֹ*///
//			SFR_ESAMCOM->CR1 |= USART_RE_EN;				///*����ʹ��*///
//			//SFR_ESAMCOM->CR1 |= USART_REIE_Set_UART1;				///*�����ж�ʹ��*///
//			SFR_ESAMCOM->SR &= (~USART_FLAG_RXNE);			///*������жϱ�־*///
//			///*******************************************************///
//			NVIC_EnableIRQ(Esam_IRQn);						///*�����ж�ʹ��*///
//			///*******************************************************///
//			break;
//		}
		///*******************************************************///
		case C_Card:
		{
			///*******************************************************///
//			V_UsartDataBuff = SFR_CARDCOM->SR;			///*��״̬��*///
//			V_UsartDataBuff = SFR_CARDCOM->DR;			///*�建��*///
//			SFR_CARDCOM->CR1 &= USART_TCIE_DIS;				///*��ֹ�����ж�*///
//			SFR_CARDCOM->CR1 &= USART_TE_Reset;				///*���ͽ�ֹ*///
//			SFR_CARDCOM->CR1 |= USART_RE_EN;				///*����ʹ��*///
//			//SFR_CARDCOM->CR1 |= USART_REIE_Set_UART1;				///*�����ж�ʹ��*///
////			SFR_CARDCOM->SR &= (~USART_FLAG_RXNE);			///*������жϱ�־*///
			///*******************************************************///
//			NVIC_DisableIRQ(Card_IRQn);						///*�����ж�ʹ��*///
			///*******************************************************///
			break;
		}
		///*******************************************************///
		default:
			return_value = C_Error;
		break;
	}
	return return_value;
}

///*********************************************************************************************///
///*����ԭ�ͣ�uchar8 InF_CommUart_TxdDataForInterrupt (uchar8 CommNum,uchar8 TxdData)          *///
///*��ڲ�����CommNum��ͨѶͨ���š�ȡֵ��C_RS485_1��C_RS485_2��C_IR��C_Module��C_ESAM��C_Card��*///
///*          TxdData�����ڱ��η����ֽ�                                                        *///
///*�����������                                                                               *///
///*���ز�����C_Ok��C_Error����ڴ���                                                        *///
///*����˵�����رմ��ڽ��ռ������ж�ʹ�ܣ�����һ���ֽ����ݣ����򿪴��ڷ����ж�ʹ�ܡ�           *///
///*���û��ƣ�                                                                                 *///
///*	1��ͨѶ���������У��ж��з�����Ϣ��־�������������͡�                                  *///
///*	2����ͨѶ�����ж��У����á�                                                            *///
///*	3�����ں��⴮�ڣ�����1�ֽ�ʱ����Ҫʹ��38kHz�����źš�                                  *///
///*	4����������ForDispatch��ʾ���������е��ã�ForInterrupt��ʾ���ж�����á�               *///
///*********************************************************************************************///
uchar8 InF_CommUart_TxdDataForInterrupt(uchar8 CommNum,uchar8 TxdData)
{
	uchar8 return_value = C_OK;

	switch(CommNum)
	{
		case C_RS485_1:
		{
			Enable_485_1_Transmit;	///*ʹ485оƬ�����ڷ���̬��3���ʽ*///
			///*******************************************************///
//			SFR_FIRST485->SR = USART_SR_RESET;
//			SFR_FIRST485->CR1 |= USART_USART_EN;			///*Uart Enable*///
			///*******************************************************///
			Stop_First485_Rx;								///*������ֹ*///
			///*******************************************************///
			Start_First485_Tx;								///*��ʼ����*///
			///*******************************************************///
			SFR_FIRST485->TXREG = TxdData;						///*�������봮�����ݼĴ���*///
			///*******************************************************///
			NVIC_EnableIRQ(First485_IRQn);					///*�����ж�ʹ��*///
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_RS485_2:
		{
			if(C_SmartMeter==C_Meter_Type)///*����hex���ݸ��ݱ����ж�
			{
				Enable_485_2_Transmit;	/*ʹ485оƬ�����ڷ���̬��3���ʽ*///
				/*******************************************************///
	//			SFR_SECOND485->SR = USART_SR_RESET;
	//			SFR_SECOND485->CR1 |= USART_USART_EN;			/*Uart Enable*///
				/*******************************************************///
				Stop_Second485_Rx;								/*������ֹ*///
				/*******************************************************///
				Start_Second485_Tx;								/*��ʼ����*///
				/*******************************************************///
				SFR_SECOND485->TXREG = TxdData;					/*�������봮�����ݼĴ���*///
				/*******************************************************///
				NVIC_EnableIRQ(Second485_IRQn);					/*�����ж�ʹ��*///
				/*******************************************************///
			}
			break;
		}
		/*******************************************************///
		case C_IR:
		{
//			if( InF_ReadPowerState() == C_PowerOn )
			{
				/*******************************************************///
//				SFR_INFRA->SR = USART_SR_RESET;
//				SFR_INFRA->CR1 |= USART_USART_EN;				/*Uart Enable*///
				/*******************************************************///
				Stop_Infra_Rx;									/*������ֹ*///
				/*******************************************************///
				/*******************************************************///
				SF_InfraModulatedSignalOutput();				/*PWM���*///
				/*******************************************************///
				Start_Infra_Tx;									/*��ʼ����*///
				/*******************************************************///
				/*******************************************************///
				SFR_INFRA->TXREG = TxdData;						/*�������봮�����ݼĴ���*///
				/*******************************************************///
				NVIC_EnableIRQ(Infra_IRQn);						/*�����ж�ʹ��*///
				/*******************************************************///
				break;
			}
//			else
//			{
//				/*******************************************************///
//				SFR_INFRA->SR = USART_SR_RESET;
//				SFR_INFRA->CR1 |= USART_USART_EN;				/*Uart Enable*///
//				/*******************************************************///
//				Stop_Infra_Rx;									/*������ֹ*///
//				/*******************************************************///
//				/*******************************************************///
//				SF_InfraModulatedSignalOutput_Wakeup();			/*PWM���*///
//				/*******************************************************///
//				Start_Infra_Tx;									/*��ʼ����*///
//				/*******************************************************///
//				/*******************************************************///
//				SFR_INFRA->DR = TxdData;						/*�������봮�����ݼĴ���*///
//				/*******************************************************///
//				NVIC_EnableIRQ(Infra_IRQn);						/*�����ж�ʹ��*///
//				/*******************************************************///
//				break;
//			}
		}
		/*******************************************************///
		case C_Module:				/*ģ�����2·RS485����*///
		{
			if(C_SmartMeter!=C_Meter_Type)///*����hex���ݸ��ݱ����ж�,Զ�̼�����
			{
				/*******************************************************///
	//			SFR_SECOND485->SR = USART_SR_RESET;
	//			SFR_SECOND485->CR1 |= USART_USART_EN;			/*Uart Enable*///
				/*******************************************************///
				Stop_Modular_Rx;								/*������ֹ*///
				/*******************************************************///
				Start_Modular_Tx;								/*��ʼ����*///
				/*******************************************************///
				SFR_MODULAR->TXREG = TxdData;					/*�������봮�����ݼĴ���*///
				/*******************************************************///
				NVIC_EnableIRQ(Modular_IRQn);					/*�����ж�ʹ��*///
				/*******************************************************///
			}
			break;
		}
		///*******************************************************///
//		case C_ESAM:
//		{
//			///*******************************************************///
//			SFR_ESAMCOM->CR1 |= USART_TE_Set;				///*����ʹ��*///
//			//SFR_ESAMCOM->CR1 |= USART_TXEIE_EN_UART1;				///*�����ж�ʹ��*///
//			
//			SFR_ESAMCOM->CR1 &= USART_RE_DIS;				///*���ս�ֹ*///
//			SFR_ESAMCOM->CR1 &= USART_REIE_Reset_UART1_UART1;			///*�����жϽ�ֹ*///
//			///*******************************************************///
//			SFR_ESAMCOM->DR = TxdData;						///*�������봮�����ݼĴ���*///
//			///*******************************************************///
//			NVIC_EnableIRQ(Esam_IRQn);						///*�����ж�ʹ��*///
//			///*******************************************************///
//			break;
//		}
		///*******************************************************///
		case C_Card:
		{
			///*******************************************************///
//			SFR_CARDCOM->CR1 |= USART_TE_Set;				///*����ʹ��*///
//			//SFR_CARDCOM->CR1 |= USART_TXEIE_EN_UART1;				///*�����ж�ʹ��*///
//			
//			SFR_CARDCOM->CR1 &= USART_RE_DIS;				///*���ս�ֹ*///
//			SFR_CARDCOM->CR1 &= USART_REIE_Reset_UART1;			///*�����жϽ�ֹ*///
//			///*******************************************************///
//			SFR_CARDCOM->DR = TxdData;						///*�������봮�����ݼĴ���*///
			///*******************************************************///
//			NVIC_DisableIRQ(Card_IRQn);						///*�����ж�ʹ��*///
			///*******************************************************///
			break;
		}
		///*******************************************************///
		default:
			return_value = C_Error;
		break;
	}
	return return_value;
}
///*********************************************************************************************///
///*����ԭ�ͣ�uchar8 InF_CommUart_TxdDataForDispatch (uchar8 CommNum,uchar8 TxdData)           *///
///*��ڲ�����CommNum��ͨѶͨ���š�ȡֵ��C_RS485_1��C_RS485_2��C_IR��C_Module��C_ESAM��C_Card��*///
///*          TxdData�����ڱ��η����ֽ�                                                        *///
///*�����������                                                                               *///
///*���ز�����C_Ok��C_Error����ڴ���                                                        *///
///*����˵�����رմ��ڽ��ռ������ж�ʹ�ܣ�����һ���ֽ����ݣ����򿪴��ڷ����ж�ʹ�ܡ�           *///
///*���û��ƣ�                                                                                 *///
///*	1��ͨѶ���������У��ж��з�����Ϣ��־�������������͡�                                  *///
///*	2����ͨѶ�����ж��У����á�                                                            *///
///*	3�����ں��⴮�ڣ�����1�ֽ�ʱ����Ҫʹ��38kHz�����źš�                                  *///
///*	4����������ForDispatch��ʾ���������е��ã�ForInterrupt��ʾ���ж�����á�               *///
///*********************************************************************************************///
//uchar8 InF_CommUart_TxdDataForDispatch(uchar8 CommNum,uchar8 TxdData)
uchar8 InF_CommUart_TxdDataForDispatch(uchar8 CommNum,uchar8 TxdData,uchar8 ReportMode)
{
	uchar8 return_value = C_OK;

	switch(CommNum)
	{
		case C_RS485_1:
		{
			Enable_485_1_Transmit;	///*ʹ485оƬ�����ڷ���̬��3���ʽ*///
			///*******************************************************///
///*			SFR_FIRST485->SR = USART_SR_RESET;
///			SFR_FIRST485->CR1 |= USART_USART_EN;			///*Uart Enable*///*/
			///*******************************************************///
			Stop_First485_Rx;								///*������ֹ*///
			///*******************************************************///
			Start_First485_Tx;								///*��ʼ����*///
			///*******************************************************///
			SFR_FIRST485->TXREG = TxdData;						///*�������봮�����ݼĴ���*///
			///*******************************************************///
			NVIC_EnableIRQ(First485_IRQn);					///*�����ж�ʹ��*///
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_RS485_2:
		{
			if(C_SmartMeter==C_Meter_Type)///*����hex���ݸ��ݱ����ж�
			{
				Enable_485_2_Transmit;	///*ʹ485оƬ�����ڷ���̬��3���ʽ*///
				///*******************************************************///
	///			SFR_SECOND485->SR = USART_SR_RESET;
	///			SFR_SECOND485->CR1 |= USART_USART_EN;			///*Uart Enable*///
				///*******************************************************///
				Stop_Second485_Rx;								///*������ֹ*///
				///*******************************************************///
				Start_Second485_Tx;								///*��ʼ����*///
				///*******************************************************///
				SFR_SECOND485->TXREG = TxdData;					///*�������봮�����ݼĴ���*///
				///*******************************************************///
				NVIC_EnableIRQ(Second485_IRQn);					///*�����ж�ʹ��*///
				///*******************************************************///
			}
			break;
		}
		///*******************************************************///
		case C_IR:
		{
///			if( InF_ReadPowerState() == C_PowerOn )
			{
				///*******************************************************///
///				SFR_INFRA->SR = USART_SR_RESET;
///				SFR_INFRA->CR1 |= USART_USART_EN;				///*Uart Enable*///
				///*******************************************************///
				Stop_Infra_Rx;									///*������ֹ*///
				///*******************************************************///
				///*******************************************************///
				SF_InfraModulatedSignalOutput();				///*PWM���*///
				///*******************************************************///
				Start_Infra_Tx;									///*��ʼ����*///
				///*******************************************************///
				///*******************************************************///
				SFR_INFRA->TXREG = TxdData;						///*�������봮�����ݼĴ���*///
				///*******************************************************///
				NVIC_EnableIRQ(Infra_IRQn);						///*�����ж�ʹ��*///
				///*******************************************************///
				break;
			}
//			else
//			{
//				///*******************************************************///
//				SFR_INFRA->SR = USART_SR_RESET;
//				SFR_INFRA->CR1 |= USART_USART_EN;				///*Uart Enable*///
//				///*******************************************************///
//				Stop_Infra_Rx;									///*������ֹ*///
//				///*******************************************************///
//				///*******************************************************///
//				SF_InfraModulatedSignalOutput_Wakeup();			///*PWM���*///
//				///*******************************************************///
//				Start_Infra_Tx;									///*��ʼ����*///
//				///*******************************************************///
//				///*******************************************************///
//				SFR_INFRA->TXREG = TxdData;						///*�������봮�����ݼĴ���*///
//				///*******************************************************///
//				NVIC_EnableIRQ(Infra_IRQn);						///*�����ж�ʹ��*///
//				///*******************************************************///
//				break;
//			}
		}
		///*******************************************************///
		case C_Module:				///*ģ�����2·RS485����*///
		{
			if(C_SmartMeter!=C_Meter_Type)///*����hex���ݸ��ݱ����ж�,Զ�̼�����
			{
				///*******************************************************///
	//			SFR_SECOND485->SR = USART_SR_RESET;
	//			SFR_SECOND485->CR1 |= USART_USART_EN;			///*Uart Enable*///
				///*******************************************************///
	            if(ReportMode != C_ActiveReportFlag)
	            {
	                Stop_Modular_Rx;								///*������ֹ*///
	            }
				///*******************************************************///
				Start_Modular_Tx;								///*��ʼ����*///
				///*******************************************************///
				SFR_MODULAR->TXREG = TxdData;					///*�������봮�����ݼĴ���*///
				///*******************************************************///
				NVIC_EnableIRQ(Modular_IRQn);					///*�����ж�ʹ��*///
				///*******************************************************///
			}
			break;
		}
		///*******************************************************///
//		case C_ESAM:
//		{
//			///*******************************************************///
//			SFR_ESAMCOM->CR1 |= USART_TE_Set;				///*����ʹ��*///
//			//SFR_ESAMCOM->CR1 |= USART_TXEIE_EN_UART1;				///*�����ж�ʹ��*///
//			
//			SFR_ESAMCOM->CR1 &= USART_RE_DIS;				///*���ս�ֹ*///
//			SFR_ESAMCOM->CR1 &= USART_REIE_Reset_UART1;			///*�����жϽ�ֹ*///
//			///*******************************************************///
//			SFR_ESAMCOM->DR = TxdData;						///*�������봮�����ݼĴ���*///
//			///*******************************************************///
//			NVIC_EnableIRQ(Esam_IRQn);						///*�����ж�ʹ��*///
//			///*******************************************************///
//			break;
//		}
		///*******************************************************///
		case C_Card:
		{
			///*******************************************************///
//			SFR_CARDCOM->CR1 |= USART_TE_Set;				///*����ʹ��*///
//			//SFR_CARDCOM->CR1 |= USART_TXEIE_EN_UART1;				///*�����ж�ʹ��*///
//			
//			SFR_CARDCOM->CR1 &= USART_RE_DIS;				///*���ս�ֹ*///
//			SFR_CARDCOM->CR1 &= USART_REIE_Reset_UART1;			///*�����жϽ�ֹ*///
//			///*******************************************************///
//			SFR_CARDCOM->DR = TxdData;						///*�������봮�����ݼĴ���*///
			///*******************************************************///
//			NVIC_DisableIRQ(Card_IRQn);						///*�����ж�ʹ��*///
			///*******************************************************///
			break;
		}
		///*******************************************************///
		default:
			return_value = C_Error;
		break;
	}
	return return_value;
}

///***************************************************************************************************///
///*����ԭ�ͣ�void SF_CommUart_TxDisableForInterrupt(uchar8 CommNum)                            *///
///*��ڲ�����CommNum��ͨѶͨ���š�ȡֵ��ȡֵ��C_RS485_1��C_RS485_2��C_IR��C_Module��C_ESAM��C_Card��*///
///*�����������                                                                                     *///
///*���ز�����C_Ok��C_Error����ڴ���                                                              *///
///*����˵�����رմ��ڷ��ͣ����������ж�ʹ��                                                         *///
///*��    ע����������ForDispatch��ʾ���������е��ã�ForInterrupt��ʾ���ж�����á�                  *///
///***************************************************************************************************///
void SF_CommUart_TxDisableForInterrupt(uchar8 CommNum)
{
//  ulong32 V_UsartDataBuff = 0;
	switch(CommNum)
	{
		case C_RS485_1:
		{
			///*******************************************************///
			Stop_First485_Tx;								///*��ֹ����*///
//			SFR_FIRST485->TXREG = V_UsartDataBuff;				///*�建��*///
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_RS485_2:
		{
			///*******************************************************///
			Stop_Second485_Tx;								///*��ֹ����*///
//			SFR_SECOND485->TXREG = V_UsartDataBuff;			///*�建��*///
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_IR:
		{
			SF_InfraModulatedSignalOff();				///*�رպ�������ź�*///
			///*******************************************************///
			Stop_Infra_Tx;								///*��ֹ����*///
//			SFR_INFRA->TXREG = V_UsartDataBuff;			///*�建��*///
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_Module:			///*ģ�����2·RS485����*///
		{
			///*******************************************************///
			Stop_Modular_Tx;								///*��ֹ����*///
//			SFR_SECOND485->TXREG = V_UsartDataBuff;			///*�建��*///
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_ESAM:
		{
			
			break;
		}
		///*******************************************************///
		case C_Card:
		{
			
			break;
		}
		///*******************************************************///
		default:
		break;
	}
}


///***************************************************************************************************///
///*����ԭ�ͣ�uchar8 SF_CommUart_TxDisableForDispatch(uchar8 CommNum)                            *///
///*��ڲ�����CommNum��ͨѶͨ���š�ȡֵ��ȡֵ��C_RS485_1��C_RS485_2��C_IR��C_Module��C_ESAM��C_Card��*///
///*�����������                                                                                     *///
///*���ز�����C_Ok��C_Error����ڴ���                                                              *///
///*����˵�����رմ��ڷ��ͣ����������ж�ʹ��                                                         *///
///*��    ע����������ForDispatch��ʾ���������е��ã�ForInterrupt��ʾ���ж�����á�                  *///
///***************************************************************************************************///
void SF_CommUart_TxDisableForDispatch(uchar8 CommNum)
{
//  ulong32 V_UsartDataBuff = 0;
	switch(CommNum)
	{
		case C_RS485_1:
		{
			///*******************************************************///
			Stop_First485_Tx;								///*��ֹ����*///
//			SFR_FIRST485->TXREG = V_UsartDataBuff;				///*�建��*///
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_RS485_2:
		{
			///*******************************************************///
			Stop_Second485_Tx;								///*��ֹ����*///
//			SFR_SECOND485->TXREG = V_UsartDataBuff;			///*�建��*///
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_IR:
		{
			SF_InfraModulatedSignalOff();				///*�رպ�������ź�*///
			///*******************************************************///
			Stop_Infra_Tx;								///*��ֹ����*///
//			SFR_INFRA->TXREG = V_UsartDataBuff;			///*�建��*///
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_Module:			///*ģ�����2·RS485����*///
		{
			///*******************************************************///
			Stop_Modular_Tx;								///*��ֹ����*///
//			SFR_SECOND485->TXREG = V_UsartDataBuff;			///*�建��*///
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_ESAM:
		{
			
			break;
		}
		///*******************************************************///
		case C_Card:
		{
			
			break;
		}
		///*******************************************************///
		default:
		break;
	}
}

///***********************************************************************************///
///*Function����1·RS485�жϷ������:����/����Ϊͬһ���ж�������ַ*///
///*Description��*///
///*Input��*///
///*Output��*///
///*Calls��*///
///*Called By��*///
///*Influence��*///
///*Tips��*///
///*Others��*///
///***********************************************************************************///
void First485_IRQHandler(void)
{
	uchar8 V_UsartDataBuff;								///*���ڻ������/���͵�һ���ֽ�*///
	
	SV_Overtime_485_1 = 0;			///*��ʱ��ʱ������*///
	
	if(UART->UARTIF & USART_FLAG_RXNE1)				///*�ж��Ƿ�����ж�*///
	{
		if( ( SFR_FIRST485->RXSTA & (USART_FLAG_FE | USART_FLAG_PE|USART_FLAG_ORE) ) == 0 )	///*�ж��Ƿ��н��մ���*///
		{
			V_UsartDataBuff = SFR_FIRST485->RXREG;			///*���յ����ݶ��뻺��*///
			switch( INF_Comm_RecForInt(C_RS485_1,V_UsartDataBuff) )		//*�����յ�1�ֽ����ݽ�ͨ��ģ�鴦�����õ�����ֵ*///
			{
				case C_ContinueReceive:					///*��������*///
				{
					break;
				}
				///*******************************************************///
				case C_CorrectFrame:					///*�յ���ȷ֡*///
				{
					///*�յ���ȷ֡����Ҫ�رս���/���͹��ܣ�������������Ϣ*///
					InF_CommUart_RecDisableForInterrupt(C_RS485_1);
					///*����������Ϣ*///
					///*��Ϊ�ж��ﲻ�ܷ���Ϣ������ý�����־���������в�ñ�־�ٷ���������Ϣ*///
					SV_InterruptMsg_485_1 = C_Uart_Parse;
					break;
				}
				///*******************************************************///
				case C_AbortReceive:					///*�˳�����*///
				{
					///*������ʼ������*///
					InF_CommUart_RecDisableForInterrupt(C_RS485_1);
					SV_InitUartMsg_485_1 = C_Uart_Init;
					break;
				}
				///*******************************************************///
				default:
					///*����ֵ��׼ȷ��ͬ����ʼ������*///
					InF_CommUart_RecDisableForInterrupt(C_RS485_1);
					SV_InitUartMsg_485_1 = C_Uart_Init;
				break;
			}
		}
		else
		{
			///*���մ��󣬳�ʼ������*///
			InF_CommUart_RecDisableForInterrupt(C_RS485_1);
			SV_InitUartMsg_485_1 = C_Uart_Init;
		}
	}
	///*************************************************///
	else if(UART->UARTIF & USART_FLAG_TC1)			///*�ж��Ƿ����ж�*///
	{
		switch( INF_Comm_TxdForInt(C_RS485_1,&V_UsartDataBuff) )
		{
			case C_ContinueTransmit:
				SFR_FIRST485->TXREG = V_UsartDataBuff;
			break;
			///*******************************************************///
			case C_AbortTransmit:
			///*������ɣ���ʼ������*///
				SF_CommUart_TxDisableForInterrupt(C_RS485_1);
				InF_InitCommUartForInterrupt(C_RS485_1);
			break;
				///*******************************************************///
			case C_AbortTransmit_SetBPS:				///*�޸Ĳ������˳�*///
				SF_CommUart_TxDisableForInterrupt(C_RS485_1);
				SV_InitUartMsg_485_1 = C_Uart_Init;
				break;
			///*******************************************************///
			default:
				SF_CommUart_TxDisableForInterrupt(C_RS485_1);
				InF_InitCommUartForInterrupt(C_RS485_1);
			break;
			
		}
		UART->UARTIF = USART_FLAG_TC1;
	}
	///*************************************************///
	else
	{
		///*������жϣ���ʼ������*///
		SF_CommUart_TxDisableForInterrupt(C_RS485_1);
		InF_CommUart_RecDisableForInterrupt(C_RS485_1);
		SV_InitUartMsg_485_1 = C_Uart_Init;
	}
}

///***********************************************************************************///
///*Function����2·RS485�жϷ������:����/����Ϊͬһ���ж�������ַ*///
///*Description��*///
///*Input��*///
///*Output��*///
///*Calls��*///
///*Called By��*///
///*Influence��*///
///*Tips��*///
///*Others��*///
///***********************************************************************************///
///#if	( C_PcbVersion == C_Pcb2457 )///*-M��
void Modular_IRQHandler(void)
{
	if(C_SmartMeter!=C_Meter_Type)///*����hex���ݸ��ݱ����ж�,Զ�̼�����
	{
		uchar8 V_UsartDataBuff;					///*���ڻ������/���͵�һ���ֽ�*///
		uchar8 V_ChanelNo;						///*ͨ����*////
		uchar8 *P_ChanelParse,*P_ChanelInit;	///*ָ��ͨ�������Ĵ���,ͨ����ʼ���Ĵ���*///
	
	    uchar8 V_UReportDataBuf;                ///*���������ϱ��ķ���1���ֽ�*///
	
		///*******************************************************///
		///*��Ϊ��2·485��ģ�鹲�ô���,�����ж���Ҫ���������ֱ���,�����յ����ݴ��ݸ�ͨ�Ž���ģ��*///
	//	if(SV_MeterType != C_MeterType_Module)
	//	{
	//		V_ChanelNo = C_RS485_2;					///*��ֵͨ����*///
	//		P_ChanelParse = &SV_InterruptMsg_485_2;	///*ָ�������־�Ĵ�����ַ*///
	//		P_ChanelInit = &SV_InitUartMsg_485_2;	///*ָ���ʼ����־�Ĵ�����ַ*///
	//	}
	//	else
	//	{
			V_ChanelNo = C_Module;
			P_ChanelParse = &SV_InterruptMsg_Modular;
			P_ChanelInit = &SV_InitUartMsg_Modular;
	//	}
		///*******************************************************///
		SV_Overtime_485_2 = 0;			///*��ʱ��ʱ������*///
		///*******************************************************///
	
	        ///*************************************************///
	    if((UART->UARTIF & USART_FLAG_RXNE0)||(UART->UARTIF & USART_FLAG_TC0))
	    {
		///*******************************************************///
	        if(UART->UARTIF & USART_FLAG_TC0)			///*�ж��Ƿ����ж�*///
	        {
	            if(Inf_Comm_REPORTFlag() != C_ReportNULL)           ///*���ܴ����¼��ϱ����ߵ����ϱ�*///
	            {
	//                Inf_Comm_InitModuleCommuniFlag();               ///*����ʱ���ñ�־�����������ϱ�����*///
	                switch( INF_Comm_TxdForInt_698Report(V_ChanelNo,&V_UReportDataBuf))
	                {
	                    case C_ContinueTransmit:
	                        SFR_MODULAR->TXREG = V_UReportDataBuf;
	                    break;
	                    ///*******************************************************///
	                    case C_AbortTransmit:
	                        ///*������ɣ���ʼ������*///
	                        SF_CommUart_TxDisableForInterrupt(V_ChanelNo);
	                        //InF_InitCommUartForInterrupt(V_ChanelNo);
	                        Inf_Comm_REPORTFlagClear(C_ActiveReportEndFlag);         ///*�����ϱ���־����*///
	                    break;
	                    ///*******************************************************///
	//                    case C_AbortTransmit_SetBPS:				///*�޸Ĳ������˳�*///
	//                        SF_CommUart_TxDisableForInterrupt(V_ChanelNo);
	//                        *P_ChanelInit = C_Uart_Init;
	//                        break;
	                    ///*******************************************************///
	                    default:
	                        SF_CommUart_TxDisableForInterrupt(V_ChanelNo);
	                        //InF_InitCommUartForInterrupt(V_ChanelNo);
	                    break;
	                }
	            }
	            else
	            {
	                switch( INF_Comm_TxdForInt(V_ChanelNo,&V_UsartDataBuff) )
	                {
	                    case C_ContinueTransmit:
	                        SFR_MODULAR->TXREG = V_UsartDataBuff;
	                    break;
	                    ///*******************************************************///
	                    case C_AbortTransmit:
	                        ///*������ɣ���ʼ������*///
	                        SF_CommUart_TxDisableForInterrupt(V_ChanelNo);
	                        InF_InitCommUartForInterrupt(V_ChanelNo);
	                    break;
	                    ///*******************************************************///
	                    case C_AbortTransmit_SetBPS:				///*�޸Ĳ������˳�*///
	                        SF_CommUart_TxDisableForInterrupt(V_ChanelNo);
	                        *P_ChanelInit = C_Uart_Init;
	                        break;
	                    ///*******************************************************///
	                    default:
	                        SF_CommUart_TxDisableForInterrupt(V_ChanelNo);
	                        InF_InitCommUartForInterrupt(V_ChanelNo);
	                    break;
	                }
	            }
	            
	            UART->UARTIF = USART_FLAG_TC0;
	        }
			if(UART->UARTIF & USART_FLAG_RXNE0)				///*�ж��Ƿ�����ж�*///
			{
		        V_UsartDataBuff = SFR_MODULAR->RXREG;			///*���յ����ݶ��뻺��*///
		        if( ( SFR_MODULAR->RXSTA & (USART_FLAG_FE | USART_FLAG_PE|USART_FLAG_ORE) ) == 0 )	///*�ж��Ƿ��н��մ���*///
		        {
		            if(Inf_Comm_InitModuleCommuniFlag(C_CommuniSafeWorld1))    ///*ͨ�Ž���*///
		            {
		                return;
		            }
					switch( INF_Comm_RecForInt(V_ChanelNo,V_UsartDataBuff) )		//*�����յ�1�ֽ����ݽ�ͨ��ģ�鴦�����õ�����ֵ*///
					{
						case C_ContinueReceive:					///*��������*///
						{
							break;
						}
						///*******************************************************///
						case C_CorrectFrame:					///*�յ���ȷ֡*///
						{
							///*�յ���ȷ֡����Ҫ�رս���/���͹��ܣ�������������Ϣ*///
							InF_CommUart_RecDisableForInterrupt(V_ChanelNo);
							///*����������Ϣ*///
							///*��Ϊ�ж��ﲻ�ܷ���Ϣ������ý�����־���������в�ñ�־�ٷ���������Ϣ*///
							*P_ChanelParse = C_Uart_Parse;
							break;
						}
						///*******************************************************///
						case C_AbortReceive:					///*�˳�����*///
						{
							///*������ʼ������*///
							InF_CommUart_RecDisableForInterrupt(V_ChanelNo);
							*P_ChanelInit = C_Uart_Init;
							break;
						}
						///*******************************************************///
						default:
							///*����ֵ��׼ȷ��ͬ����ʼ������*///
							InF_CommUart_RecDisableForInterrupt(V_ChanelNo);
							*P_ChanelInit = C_Uart_Init;
						break;
					}
				}
				else
				{
					///*���մ��󣬳�ʼ������*///
					InF_CommUart_RecDisableForInterrupt(V_ChanelNo);
					*P_ChanelInit = C_Uart_Init;
				}
			}
		}
		///*************************************************///
		else if(UART->UARTIF & USART_FLAG_TC0)			///*�ж��Ƿ����ж�*///
		{
			switch( INF_Comm_TxdForInt(V_ChanelNo,&V_UsartDataBuff) )
			{
				case C_ContinueTransmit:
					SFR_MODULAR->TXREG = V_UsartDataBuff;
				break;
				///*******************************************************///
				case C_AbortTransmit:
					///*������ɣ���ʼ������*///
					SF_CommUart_TxDisableForInterrupt(V_ChanelNo);
					InF_InitCommUartForInterrupt(V_ChanelNo);
				break;
				///*******************************************************///
				case C_AbortTransmit_SetBPS:				///*�޸Ĳ������˳�*///
					SF_CommUart_TxDisableForInterrupt(V_ChanelNo);
					*P_ChanelInit = C_Uart_Init;
					break;
				///*******************************************************///
				default:
					SF_CommUart_TxDisableForInterrupt(V_ChanelNo);
					InF_InitCommUartForInterrupt(V_ChanelNo);
				break;
			}
			UART->UARTIF = USART_FLAG_TC0;
		}
		///*************************************************///
		else
		{
			///*������жϣ���ʼ������*///
			SF_CommUart_TxDisableForInterrupt(V_ChanelNo);
			InF_CommUart_RecDisableForInterrupt(V_ChanelNo);
			*P_ChanelInit = C_Uart_Init;
		}
	}
	else 
	{
		uchar8 V_UsartDataBuff;					///*���ڻ������/���͵�һ���ֽ�*///
		NVIC_DisableIRQ(Modular_IRQn);
		V_UsartDataBuff = SFR_MODULAR->RXREG;			///*���յ����ݶ��뻺��*///
		UART->UARTIF =(USART_FLAG_TC0|USART_FLAG_RXNE0);		
	}
}
///*���ܱ�
void Second485_IRQHandler(void)
{
	if(C_SmartMeter==C_Meter_Type)///*����hex���ݸ��ݱ����жϣ������жϹر�
	{
		uchar8 V_UsartDataBuff;					///*���ڻ������/���͵�һ���ֽ�*///
		uchar8 V_ChanelNo;						///*ͨ����*////
		uchar8 *P_ChanelParse,*P_ChanelInit;	///*ָ��ͨ�������Ĵ���,ͨ����ʼ���Ĵ���*///
		///*******************************************************///
		///*��Ϊ��2·485��ģ�鹲�ô���,�����ж���Ҫ���������ֱ���,�����յ����ݴ��ݸ�ͨ�Ž���ģ��*///
	//	if(SV_MeterType != C_MeterType_Module)
	//	{
			V_ChanelNo = C_RS485_2;					///*��ֵͨ����*///
			P_ChanelParse = &SV_InterruptMsg_485_2;	///*ָ�������־�Ĵ�����ַ*///
			P_ChanelInit = &SV_InitUartMsg_485_2;	///*ָ���ʼ����־�Ĵ�����ַ*///
	//	}
	//	else
	//	{
	//		V_ChanelNo = C_Module;
	//		P_ChanelParse = &SV_InterruptMsg_Modular;
	//		P_ChanelInit = &SV_InitUartMsg_Modular;
	//	}
		///*******************************************************///
		SV_Overtime_485_2 = 0;			///*��ʱ��ʱ������*///
		///*******************************************************///
		if(UART->UARTIF & USART_FLAG_RXNE5)				///*�ж��Ƿ�����ж�*///
		{
			if( ( SFR_SECOND485->RXSTA & (USART_FLAG_FE | USART_FLAG_PE|USART_FLAG_ORE) ) == 0 )	///*�ж��Ƿ��н��մ���*///
			{
				V_UsartDataBuff = SFR_SECOND485->RXREG;			///*���յ����ݶ��뻺��*///
				switch( INF_Comm_RecForInt(V_ChanelNo,V_UsartDataBuff) )		//*�����յ�1�ֽ����ݽ�ͨ��ģ�鴦�����õ�����ֵ*///
				{
					case C_ContinueReceive:					///*��������*///
					{
						break;
					}
					///*******************************************************///
					case C_CorrectFrame:					///*�յ���ȷ֡*///
					{
						///*�յ���ȷ֡����Ҫ�رս���/���͹��ܣ�������������Ϣ*///
						InF_CommUart_RecDisableForInterrupt(V_ChanelNo);
						///*����������Ϣ*///
						///*��Ϊ�ж��ﲻ�ܷ���Ϣ������ý�����־���������в�ñ�־�ٷ���������Ϣ*///
						*P_ChanelParse = C_Uart_Parse;
						break;
					}
					///*******************************************************///
					case C_AbortReceive:					///*�˳�����*///
					{
						///*������ʼ������*///
						InF_CommUart_RecDisableForInterrupt(V_ChanelNo);
						*P_ChanelInit = C_Uart_Init;
						break;
					}
					///*******************************************************///
					default:
						///*����ֵ��׼ȷ��ͬ����ʼ������*///
						InF_CommUart_RecDisableForInterrupt(V_ChanelNo);
						*P_ChanelInit = C_Uart_Init;
					break;
				}
			}
			else
			{
				///*���մ��󣬳�ʼ������*///
				InF_CommUart_RecDisableForInterrupt(V_ChanelNo);
				*P_ChanelInit = C_Uart_Init;
			}
		}
		///*************************************************///
		else if(UART->UARTIF & USART_FLAG_TC5)			///*�ж��Ƿ����ж�*///
		{
			switch( INF_Comm_TxdForInt(V_ChanelNo,&V_UsartDataBuff) )
			{
				case C_ContinueTransmit:
					SFR_SECOND485->TXREG = V_UsartDataBuff;
				break;
				///*******************************************************///
				case C_AbortTransmit:
					///*������ɣ���ʼ������*///
					SF_CommUart_TxDisableForInterrupt(V_ChanelNo);
					InF_InitCommUartForInterrupt(V_ChanelNo);
				break;
				///*******************************************************///
				case C_AbortTransmit_SetBPS:				///*�޸Ĳ������˳�*///
					SF_CommUart_TxDisableForInterrupt(V_ChanelNo);
					*P_ChanelInit = C_Uart_Init;
					break;
				///*******************************************************///
				default:
					SF_CommUart_TxDisableForInterrupt(V_ChanelNo);
					InF_InitCommUartForInterrupt(V_ChanelNo);
				break;
			}
			UART->UARTIF = USART_FLAG_TC5;
		}
		///*************************************************///
		else
		{
			///*������жϣ���ʼ������*///
			SF_CommUart_TxDisableForInterrupt(V_ChanelNo);
			InF_CommUart_RecDisableForInterrupt(V_ChanelNo);
			*P_ChanelInit = C_Uart_Init;
		}		
	}
	else 
	{
		uchar8 V_UsartDataBuff;					///*���ڻ������/���͵�һ���ֽ�*///
		NVIC_DisableIRQ(Second485_IRQn);		
		V_UsartDataBuff = SFR_SECOND485->RXREG;			///*���յ����ݶ��뻺��*///
		UART->UARTIF =(USART_FLAG_TC5|USART_FLAG_RXNE5);
	}
}
/*******************************************************************************
����ԭ�ͣ�void SF_InfarWakeupTimer_Disable(void)
�����������͹����º��⻽�Ѵ����жϽ�ֹ
��������� 
���������
���ز����� 
����λ�ã� 
��    ע�� 
*******************************************************************************/
void SF_InfarWakeupTimer_Disable(void)
{
	SFR_INFRA->RXSTA &= (~(USART_FLAG_FE | USART_FLAG_PE | USART_FLAG_ORE));
	NVIC_DisableIRQ(Infra_IRQn);			/*��ֹ�ж�*/

#if 0
	Disable_ComUart_Clock;                  /*�ر�commUartʱ��*/
#endif
    
	Disable_Infra_Clock;					/*ϵͳʱ�ӹر�*/
	
	IO_INFRARX->BSETH = INFRARX_SET;
	IO_INFRARX->MODER &=	INFRARX_IN_MODE;	
	IO_INFRARX->MODER |=	INFRARX_OUT_MODE;
	IO_INFRARX->OTYPER |= INFRARX_OUTPUT_OD;
	
	IO_INFRARX->BSETH = INFRARX_SET;	
}
///***********************************************************************************///
///*Function�����⴮���жϷ������:����/����Ϊͬһ���ж�������ַ*///
///*Description��*///
///*Input��*///
///*Output��*///
///*Calls��*///
///*Called By��*///
///*Influence��*///
///*Tips��*///
///*Others��*///
///***********************************************************************************///
void Infra_IRQHandler(void)
{
	uchar8 V_UsartDataBuff;								///*���ڻ������/���͵�һ���ֽ�*///

	SV_Overtime_Ir = 0;			///*��ʱ��ʱ������*///
	
	if((InF_ReadPowerState() == C_PowerOn)||(Str_LowPower_Infra.WakeupState == C_Enable))///*�е�����״̬�����ں��⻽��״̬
	{
		if(UART->UARTIF & USART_FLAG_RXNE4)				///*�ж��Ƿ�����ж�*///
		{
			if( ( SFR_INFRA->RXSTA & (USART_FLAG_FE | USART_FLAG_PE|USART_FLAG_ORE) ) == 0)	///*�ж��Ƿ��н��մ���*///
			{
				V_UsartDataBuff = (uchar8)SFR_INFRA->RXREG;			///*���յ����ݶ��뻺��*///
				switch( INF_Comm_RecForInt(C_IR,V_UsartDataBuff) )		//*�����յ�1�ֽ����ݽ�ͨ��ģ�鴦�����õ�����ֵ*///
				{
					case C_ContinueReceive:					///*��������*///
					{
						break;
					}
					///*******************************************************///
					case C_CorrectFrame:					///*�յ���ȷ֡*///
					{
						///*�յ���ȷ֡����Ҫ�رս���/���͹��ܣ�������������Ϣ*///
						InF_CommUart_RecDisableForInterrupt(C_IR);
						///*����������Ϣ*///
						///*��Ϊ�ж��ﲻ�ܷ���Ϣ������ý�����־���������в�ñ�־�ٷ���������Ϣ*///
						SV_InterruptMsg_Ir = C_Uart_Parse;
						break;
					}
					///*******************************************************///
					case C_AbortReceive:					///*�˳�����*///
					{
						///*������ʼ������*///
						InF_CommUart_RecDisableForInterrupt(C_IR);
						SV_InitUartMsg_Ir = C_Uart_Init;
						break;
					}
					///*******************************************************///
					default:
						///*����ֵ��׼ȷ��ͬ����ʼ������*///
						InF_CommUart_RecDisableForInterrupt(C_IR);
						SV_InitUartMsg_Ir = C_Uart_Init;
					break;
				}
			}
			else
			{
				///*���մ��󣬳�ʼ������*///
				InF_CommUart_RecDisableForInterrupt(C_IR);
				SV_InitUartMsg_Ir = C_Uart_Init;
			}
		}
		///*************************************************///
		else if(UART->UARTIF & USART_FLAG_TC4)			///*�ж��Ƿ����ж�*///
		{
			if( INF_Comm_TxdForInt(C_IR,&V_UsartDataBuff) == C_ContinueTransmit )
			{
				SFR_INFRA->TXREG = V_UsartDataBuff;
			}
			else
			{
				///*������ɣ���ʼ������*///
				SF_CommUart_TxDisableForInterrupt(C_IR);
				InF_InitCommUartForInterrupt(C_IR);
			}
			UART->UARTIF = USART_FLAG_TC4;
		}
		///*************************************************///
		else
		{
			///*������жϣ���ʼ������*///
			SF_CommUart_TxDisableForInterrupt(C_IR);
			InF_CommUart_RecDisableForInterrupt(C_IR);
			SV_InitUartMsg_Ir = C_Uart_Init;
		}
	}
	else  ///*�͹��ģ����⻽���ж�
	{
		if(UART->UARTIF & USART_FLAG_RXNE4)				///*�ж��Ƿ�����ж�*///
		{
			if( ( SFR_INFRA->RXSTA & (USART_FLAG_FE | USART_FLAG_PE|USART_FLAG_ORE) ) == 0)	///*�ж��Ƿ��н��մ���*///
			{
//				SwitchOn_BackLight();///*test
				SV_Wakeup_Flag = C_InfraWakeup_Flag;

				V_UsartDataBuff = (uchar8)SFR_INFRA->RXREG;			///*���յ����ݶ��뻺��*///
				if( (V_UsartDataBuff == 0x68)||(V_UsartDataBuff == 0x11)||(V_UsartDataBuff == 0x04) )
				{
					SV_Wakeup_Data <<= 8;
					SV_Wakeup_Data |= (ulong32)V_UsartDataBuff;
					SV_Wakeup_Data &= 0x00ffffff;					
					if( (SV_Wakeup_Data == 0x00681104)||(SV_Wakeup_Data == 0x00110468)||(SV_Wakeup_Data == 0x00046811) )
					{
						SF_InfarWakeupTimer_Disable();			
					}
				}
				else
				{
					SV_Wakeup_Flag = 0;
					SV_Wakeup_Data = 0;
					SF_InfarWakeupTimer_Disable();				
				}
			}
			else
			{
				SV_Wakeup_Flag = 0;
				SV_Wakeup_Data = 0;
				SF_InfarWakeupTimer_Disable();	
			}
		}
		///*************************************************///
		else
		{
			///*������жϣ��رմ���*///
			SV_Wakeup_Flag = 0;
			SV_Wakeup_Data = 0;
			SF_InfarWakeupTimer_Disable();	
		}						
	}	
}

///***********************************************************************************///
///*Function��ESAM�����жϷ������:����/����Ϊͬһ���ж�������ַ*///
///*Description��*///
///*Input��*///
///*Output��*///
///*Calls��*///
///*Called By��*///
///*Influence��*///
///*Tips��*///
///*Others��*///
///***********************************************************************************///
//void Esam_IRQHandler(void)
//{
//	
//}

///***********************************************************************************///
///*Function����ESAM����1���ֽ�*///
///*Description��*///
///*Input���������ݵĵ�ַָ��*///
///*Output������ESAM���յ������ݷŵ�����ĵ�ַ��*///
///*Return��C_OK�����ճɹ���C_Error��δ�ܽ��յ�����ʱ*///
///***********************************************************************************///
//uchar8 SF_RecOneByteFrom_Esam(uchar8 *P_Buff)
//{
//	ulong32 V_ulDelay = 0;
//	
//	while( (SFR_ESAMCOM->SR & USART_FLAG_RXNE) != USART_FLAG_RXNE )	///*��1�ֽڽ������*///
//	{
//		InF_Delay_2us();
//		V_ulDelay++;
//		if( V_ulDelay > C_Esam_9600ETU )							///*�����ʱ9600ETU*///
//		{
//			return C_Error;
//		}
//	}
//	*P_Buff = SFR_ESAMCOM->DR;
//	
//	return C_OK;
//}

///***********************************************************************************///


///***********************************************************************************///
///*Function����ESAM����1���ֽ�*///
///*Description��*///
///*Input��Ҫ���͵�����*///
///*Output������ESAM���յ������ݷŵ�����ĵ�ַ��*///
///*Return��C_OK�����ͳɹ���C_Error���ط�3���Բ��ܳɹ�*///
///***********************************************************************************///
//uchar8 SF_SendOneByteTo_Esam(uchar8 data)
//{
//	ulong32 V_ulDelay = 0;
//	
////	for(v_times=0;v_times<3;v_times++)
////	{
//		InF_CommUart_TxdDataForDispatch( C_ESAM,data );					///*������������*///
//		
//		while( (SFR_ESAMCOM->SR & USART_FLAG_TC) != USART_FLAG_TC )	///*��1�ֽڷ������*///
//		{
//			InF_Delay_2us();
//			V_ulDelay++;
//			if( V_ulDelay > (C_Esam_20ETU+C_Esam_20ETU) )				///*�����ʱ40ETU*///
//			{
//				return C_Error;
//			}
//		}
//		
////		if( !(SFR_ESAMCOM->SR & USART_FLAG_PE) )			///*��У�������ֱ���˳�*///
////		{
////			break;
////		}
////	}
////	if(v_times>=3)
////	{
////		return C_Error;
////	}
////	else
////	{
//		return C_OK;
////	}
//}


///***********************************************************************************///
///*Function����CARD����1���ֽ�*///
///*Description��*///
///*Input���������ݵĵ�ַָ��*///
///*Output������CARD���յ������ݷŵ�����ĵ�ַ��*///
///*Return��C_OK�����ճɹ���C_Error��δ�ܽ��յ�����ʱ*///
///***********************************************************************************///
uchar8 SF_RecOneByteFrom_Card(uchar8 *P_Buff)
{
	ushort16 v_r_data = 0;		///*���յ�����*///
	uchar8 i,j,k,v_temp0,v_temp1,v_check;
	uchar8	buf[2];
	uchar8 v_delay;
	
	
	for(k=0;k<3;k++)
	{
		SF_CardBaudRateTimerInit( C_Init,C_4ms );			///*4ms��ʼ��ʱ:���ڳ�ʱ����*///
		CardDataIO_R();			///*��������Ϊ����*///
		v_delay = 0;
		
		//IO_BEEP->BSRR = BEEPSET;
		while( 1 )
		{
			if( !(IO_CARDDATA->IDR & CARDDATA_SELECT) )		///*ֻҪ��⵽������Ϊ�ͣ��˳�ѭ��*///
			{
				SF_CardBaudRateTimerInit( C_Init,C_1_2_ETU );			///*��ʱ1/2��ETU*///
	            //IO_BEEP->BSRR = BEEPSET;
				break;
			}
			if( CardBaudRateTimer->ETxIF & C_TimerStatus_OVIF_RESET )			///*9600ETU��ʱ��־��ʱ��־������*///
			{
				CardBaudRateTimer->ETxIF |= C_TimerStatus_OVIF_RESET;
				v_delay++;
				if( v_delay >=250 )						///*4ms*250=1s,Լ9600��ETU*///
				{
					SF_CardBaudRateTimerStop();						///*��ʱֹͣ*///
					//IO_BEEP->BSRR = BEEPRESET;
					return( C_NoData );		///*���س�ʱ*///
				}
			}
		}
		while( !(CardBaudRateTimer->ETxIF & C_TimerStatus_OVIF_RESET))
		{
			;
		}
		CardBaudRateTimer->ETxIF |= C_TimerStatus_OVIF_RESET;///*���жϱ�־
	//IO_BEEP->BSRR = BEEPRESET;
		
		v_check = 0;
		v_r_data = 0;
		for(i=0;i<9;i++)		///*����9λ����λ*///
		{
			SF_CardTimerDelay_N_ETU( 1 );		///*��ѯ:��ʱ1ETU����û�У����������������1ETU����*///
			
			//if( i%2 == 0 )
			//{
			//IO_BEEP->BSRR = BEEPSET;
			//}
			//else
			//{
			//IO_BEEP->BSRR = BEEPRESET;
			//}
			v_temp0 = 0;
			v_temp1 = 0;
			for(j=0;j<3;j++)		///*3ȡ2*///
			{
				if( IO_CARDDATA->IDR & CARDDATA_SELECT )
				{
					v_temp1++;			///*����Ϊ�ߵĴ���*///
				}
				else
				{
					v_temp0++;			///*����Ϊ�͵Ĵ���*///
				}
			}
			v_r_data>>=1;
			if( v_temp1 > v_temp0 )
			{
				v_r_data |= 0x0100;
				v_check++;
			}
		}
		
		//SF_CardBaudRateTimerInit( C_Init,C_1_Piont_5_ETU );			///*��ʱ1.5��ETU,��ACK*///
		//
		//while( !(CardBaudRateTimer->SR & C_TIM_SR_UIF) )
		//{
		//	;
		//}
		SF_CardTimerDelay_N_ETU( 1 );
		if( v_check%2 == 0 )		///*��żУ���*///
		{
			//CardDataIO_T_1();					///*У��λ��ȷ,���͸�*///
			//SF_CardBaudRateTimerInit( C_NotInit,C_1_Piont_5_ETU );		///*1.5ETU*///
			
			PF_Ushort16ToBuffer2(buf,&v_r_data);
			*P_Buff = buf[0];
			
			//while( !(CardBaudRateTimer->SR & C_TIM_SR_UIF) )
			//{
			//	;
			//}
			CardDataIO_R();			///*��������Ϊ����:�൱�ڷ���,������Ϊ�˽�Լʱ��,��©����һ����ʼλ*///
			SF_CardBaudRateTimerStop();
					//IO_BEEP->BSRR = BEEPRESET;
			return(C_OK);
		}
		else		///*��żУ���*///
		{
			CardDataIO_T_0();					///*У��λ����,���͵�*///
			SF_CardBaudRateTimerInit( C_Init,C_1_Piont_5_ETU );
			while( !(CardBaudRateTimer->ETxIF & C_TimerStatus_OVIF_RESET) )
			{
				;
			}
			CardDataIO_R();
		}
		//SF_CardBaudRateTimerInit( C_NotInit,C_1_Piont_5_ETU );
		//while( !(CardBaudRateTimer->SR & C_TIM_SR_UIF) )
		//{
		//	;
		//}
	}
	SF_CardBaudRateTimerStop();
					//IO_BEEP->BSRR = BEEPRESET;
	return( C_Error );
}

///***********************************************************************************///


///***********************************************************************************///
///*Function����CARD����1���ֽ�*///
///*Description��*///
///*Input��Ҫ���͵�����*///
///*Output������CARD���յ������ݷŵ�����ĵ�ַ��*///
///*Return��C_OK�����ͳɹ���C_Error���ط�3���Բ��ܳɹ�*///
///***********************************************************************************///
uchar8 SF_SendOneByteTo_Card(uchar8 data)
{
	ushort16 v_t_data,v_t_data_buf;
	uchar8 i,j,k,v_temp0,v_temp1;
	uchar8	buf[2];
	
	///*��У��*///
	v_temp0 = data;
	buf[1] = 0;
	for(i=0;i<8;i++)
	{
		buf[1] += (v_temp0&0x01);
		v_temp0 >>= 1;
	}
	buf[1] &= 0x01;
	buf[0] = data;
	PF_Buffer2ToUshort16(buf,&v_t_data_buf);
	v_t_data_buf <<= 1;
	v_t_data_buf &= 0x03fe;
	///*���ˣ�buf�ĵ�10λΪҪ���͵�����,bit0����ʼλ*///
	
	
	for(k=0;k<3;k++)
	{
		SF_CardBaudRateTimerInit( C_Init,C_1_2_ETU );		///*1/2��ETU*///
		v_t_data = v_t_data_buf;
		
		for(i=0;i<10;i++)
		{
			if( v_t_data & 0x0001 )
			{
				CardDataIO_T_1();
			}
			else
			{
				CardDataIO_T_0();
			}
			v_t_data >>= 1;
			SF_CardTimerDelay_N_ETU( 1 );
		}
		
		CardDataIO_R();		///*����ת����*///
		
		SF_CardTimerDelay_N_ETU( 1 );
		///*���ˣ���11��ETU*///
		
		//SF_CardBaudRateTimerInit( C_NotInit,C_2_ETU );	///*��2��ETU����ʱ*///
		
		v_temp0 = 0;
		v_temp1 = 0;
		for(j=0;j<3;j++)		///*3ȡ2*///
		{
			if( IO_CARDDATA->IDR & CARDDATA_SELECT )
			{
				v_temp1++;			///*����Ϊ�ߵĴ���*///
			}
			else
			{
				v_temp0++;			///*����Ϊ�͵Ĵ���*///
			}
		}
		SF_CardTimerDelay_N_ETU( 2 );
		
		SF_CardBaudRateTimerStop();
		///*���ˣ�����ʼλ������ܹ�13ETU*///
		
		if( v_temp1 > v_temp0 )
		{
			return( C_OK );
		}
	}
	return( C_Error ); 
}
