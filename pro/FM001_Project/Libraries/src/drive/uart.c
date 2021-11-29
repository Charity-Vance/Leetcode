
///*****************************************************************************************///
///*Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     uart.c
///*Version:       V1
///*Date:          2014-3-12
///*Description:   串口配置
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
#include "uart.h"
#include "IO.h"
#include "Timer.h"
#include "EsamDrive.h"
#include "CardDrive.h"
#include "fm32l0xx_rcc.h"
#include "LowPower.h"

///*中断服务程序宏定义*///


static uchar8	SV_InterruptMsg_485_1;				///*第1路485：用于装载解析标志*///
static uchar8	SV_InterruptMsg_485_2;				///*第2路485：用于装载解析标志*///
static uchar8	SV_InterruptMsg_Ir;					///*红外：用于装载解析标志*///
static uchar8	SV_InterruptMsg_Modular;			///*模块：用于装载解析标志*///
static uchar8	SV_InitUartMsg_485_1;				///*第1路485：用于装载初始化标志*///
static uchar8	SV_InitUartMsg_485_2;				///*第2路485：用于装载初始化标志*///
static uchar8	SV_InitUartMsg_Ir;					///*红外：用于装载初始化标志*///
static uchar8	SV_InitUartMsg_Modular;				///*模块：用于装载初始化标志*///
static uchar8	SV_MeterType;						///*电能表类型:模块表或非模块表*///
static uchar8	SV_Overtime_485_1;					///*第1路485对应串口超时定时器*///
static uchar8	SV_Overtime_485_2;					///*第2路485对应串口超时定时器*///
static uchar8	SV_Overtime_Ir;						///*红外对应串口超时定时器*///
///*因为第2路485和模块共用一路硬件串口,所以模块超时定时器不需要*///
//static uchar8	SV_Overtime_Modular;				///*模块对应串口超时定时器*///

//uchar8 SV_485_1_timer;
//uchar8 SV_485_1_int;
//uchar8 SV_485_1_dispatch;


//ulong32 SV_Uart_RxCounter;		//接收字节数
//ulong32 SV_Uart_TxCounter;		//发送字节数
//ulong32 SV_Uart_RxIntterupt;	//中断次数
//ulong32 SV_Uart_TxIntterupt;	//中断次数
//ulong32 SV_Uart_RxErr;			//错误次数
//ulong32 SV_Uart_TxErr;			//错误次数
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
//	SV_Uart_RxCounter =0;		//接收字节数
//	SV_Uart_TxCounter =0;		//发送字节数
//	SV_Uart_RxIntterupt =0;		//中断次数
//	SV_Uart_TxIntterupt =0;		//中断次数
//	SV_Uart_RxErr =0;			//错误次数
//	SV_Uart_TxErr =0;			//错误次数
//	SV_Uart_ComPass =0;			//错误次数
//	SV_Uart_ComTx =0;			//错误次数
//	SV_Uart_ComMsg = 0;
//}


///**********************************************************************************///
///*Description：串口超时处理,如果超时则立即复位串口*///
///*Input：无
///*Output:根据是否超时确定是否初始化串口*///
///*Influence：
///* 1.该函数在主流程中调用,每500ms调用一次,如果有其他模块执行时间超过500ms,
///*   则该函数执行间隔也超过500ms
///* 2.该函数只能在主流程中调用,如果改到中断调用,只能置标志回到主流程再初始化串口
///**********************************************************************************///
void SF_UartOvertime(void)
{
	///*第1路485对应的串口超时定时器*///
	SV_Overtime_485_1++;
	if( SV_Overtime_485_1 >= C_Uart_OverTime )
	{
		InF_InitComm(C_RS485_1);
	}
	///*第2路485对应的串口超时定时器*///
	SV_Overtime_485_2++;
	if( SV_Overtime_485_2 >= C_Uart_OverTime )
	{
		///*根据电表类型确定初始化哪一路通道*///
		if(SV_MeterType != C_MeterType_Module)
		{
			InF_InitComm(C_RS485_2);
		}
		else
		{
			InF_InitComm(C_Module);
		}
	}
	///*红外对应的串口超时定时器*///
	SV_Overtime_Ir++;
	if( SV_Overtime_Ir >= C_Uart_OverTime )
	{
		InF_InitComm(C_IR);
	}
}
///**********************************************************************************///
///*Description：取电能表通信类型:是否为模块表*///
///*Input：无
///*Output：SV_MeterType=C_MeterType_Module表示为模块表,否则为非模块表*///
///*Influence：上电初始化调用1次,主流程中0.5s调用1次*///
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
///*Description：取电能表通信类型:是否为模块表*///
///*Input：无
///*Output：SV_MeterType=C_MeterType_Module表示为模块表,否则为非模块表*///
///*Influence：给其他模块调用*///
///**********************************************************************************///
uchar8 Inf_GetMeterType(void)
{
  return SV_MeterType;
}


///**********************************************************************************///
///*Function：*///
///*Description：主调度根据中断全局标志,判断是否触发通信解析模块*///
///*Input：无
///*Output：标志成立，则直接调用通信解析模块接口函数,然后将标志置为常态*///
///*Calls：*///
///*Called By：主调度根据是否有一帧数据标志调用*///
///*Influence：调用的地方将源消息号、目的消息号、数据域都整理好后调用该函数*///
///*该函数每个循环调用一次，编写该函数的目的是：在中断里不调用发消息函数，*///
///*中断里只是置标志，出来后在主调度里处理：解析掉模块接口函数，初始化串口掉接口函数*///
///**********************************************************************************///
void InF_Dispatch_CommInterruptMessage(void)
{
	uchar8 V_ucBuffer[5];
	Str_Msg_Parameter SStr_Msg_Parameter;
	
	///*首先取当前电源状态,传递给调用的函数*///
	SStr_Msg_Parameter.PowerFlag = InF_ReadPowerState();
	
	///*串口解析消息处理*///
	if( SV_InterruptMsg_485_1 == C_Uart_Parse )
	{
		SV_InterruptMsg_485_1 = C_Uart_Normal;
		V_ucBuffer[0] = Pt_Comm_No;
		V_ucBuffer[1] = C_RS485_1;
////		Dispatch_SendMessage(C_Msg_Communication,V_ucBuffer,Pt_Comm_No_Len+1);
		SStr_Msg_Parameter.SourceAddr = C_Msg_Dispatch;	///*源地址必然是主调度*///
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
		SStr_Msg_Parameter.SourceAddr = C_Msg_Dispatch;	///*源地址必然是主调度*///
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
		SStr_Msg_Parameter.SourceAddr = C_Msg_Dispatch;	///*源地址必然是主调度*///
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
		SStr_Msg_Parameter.SourceAddr = C_Msg_Dispatch;	///*源地址必然是主调度*///
		SStr_Msg_Parameter.DerictAddr = C_Msg_Communication;
		SStr_Msg_Parameter.Parameter = &V_ucBuffer[0];
		SStr_Msg_Parameter.Length = Pt_Comm_No_Len+1;
		Comm_ParseMessage(&SStr_Msg_Parameter);
	}
	
	///*串口初始化消息处理*///
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
///*Function：输出红外发送的38KHz的调制信号*///
///*Description：红外通信发送前调用*///
///*Input：*///
///*Output：*///
///*Calls：*///
///*Called By：*///
///*Influence：*///
///*Tips：*///
///*Others：*///
///***********************************************************************************///
void SF_InfraModulatedSignalConfig(void)
{
//	InfraTimerClock_EN;						///*系统时钟提供给38kHz定时器：无分频=系统时钟*///
//	Select_InfraIO_PWM;						///*将口线配置为PWM输出功能*///
//	InfraTimer->CR1 = C_TIM_CR1_CLEAR;		///*控制寄存器清零*///
//	
//	InfraTimer->ARR = C_InfraTimerCounter;	///*37.736kHz*///
//	InfraTimer->CCR1 = C_InfraTimerCounter;
//	InfraTimer->DIER &= C_TIM_UIE_DIS;		///*禁止中断*///
//	InfraTimer->SMCR = C_TIM_SMCR_CLEAR;	///*该寄存器在定时器用作PWM输出时无用*///
//	InfraTimer->CCER &= C_TIM_OUTPUT_DIS;	///*OC1有效时为高，OC1暂配置为无效*///
//	InfraTimer->PSC = TIM_Prescaler_0;		///*不分频*///
//	InfraTimer->CCMR1 = 0x0040;				///*强制输出高电平*///
//	
//	InfraTimer->CCER = 0x0003;
//	InfraTimer->EGR = C_TIM_EGR_CLEAR;
//	InfraTimer->SR &= C_TimerStatus_UIF_RESET;
//	InfraTimer->SR &= C_TimerStatus_CCIF_RESET;
}


///***********************************************************************************///
///*Function：输出红外发送的38KHz的调制信号*///
///*Description：红外通信发送前调用*///
///*Input：*///
///*Output：*///
///*Calls：*///
///*Called By：*///
///*Influence：*///
///*Tips：*///
///*Others：*///
///***********************************************************************************///
void SF_InfraModulatedSignalOutput(void)
{
	SFR_INFRA->TXSTA |= USART_TEIREN_En;				///* 使能红外发送调制*///
	///*******************************************************///
}
///***********************************************************************************///
///*Function：关闭红外发送的38KHz调制信号*///
///*Description：红外全部发送完后关闭*///
///*Input：*///
///*Output：*///
///*Calls：*///
///*Called By：*///
///*Influence：*///
///*Tips：*///
///*Others：*///
///***********************************************************************************///
void SF_InfraModulatedSignalOff(void)
{
	SFR_INFRA->TXSTA &= USART_TEIREN_Dis;				///*禁止红外发送调制*///
}
///***********************************************************************************///
///*Function：低功耗下红外唤醒串口初始化*///
///*Description：红外全部发送完后关闭*///
///*Input：*///
///*Output：*///
///*Calls：*///
///*Called By：*///
///*Influence：*///
///*Tips：*///
///*Others：*///
///***********************************************************************************///
void SF_InfarWakeupTimerInit(void)
{
	ulong32 V_UsartDataBuff;
	SV_InterruptMsg_Ir = C_Uart_Normal;			///*解析标志置为常态*///
	SV_InitUartMsg_Ir = C_Uart_Normal;
				
	SF_InfraModulatedSignalOff();
	Enable_ComUart_Clock;///*使能commUart			
	Enable_Infra_Clock;		///*串口时钟使能*///
	Select_Infra_AFMode;	///*将口线功能配置AF功能*///
	Select_Infra_IO_Type;	///*口线输入无上下拉、输出推挽配置*///
				
	UART->IRCON = USART_IRCONn_WakeUp;///*38k,1:1

	if(((SFR_INFRA->RXSTA&USART_WordLength_9b_Parity_No) != USART_WordLength_8bNo)
			&&((SFR_INFRA->RXSTA&USART_WordLength_9b_Parity_No) != USART_WordLength_8bOdd))
		{ 
			SFR_INFRA->RXSTA &= (~USART_WordLength_9b_Parity_No);
			SFR_INFRA->RXSTA |= USART_WordLength_8bEven;
		}
		///*******************************************************///
	SFR_INFRA->RXSTA &= (~USART_ParityErrInt_EN);	///*禁止出错中断...*///
	///*******************************************************///
	SFR_INFRA->SPBRG = USART_bps_1200_Wakeup;				///*1200*///
	///*******************************************************///
	SFR_INFRA->RXSTA &= (~(USART_FLAG_FE | USART_FLAG_PE|USART_FLAG_ORE));
	V_UsartDataBuff = SFR_INFRA->RXREG;				///*清缓存*///
	V_UsartDataBuff = SFR_INFRA->RXSTA;				///*清状态字*///
	V_UsartDataBuff = SFR_INFRA->RXBUFSTA;
//				SFR_INFRA->DR = V_UsartDataBuff;				///*清缓存*///
	Start_Infra_Rx;									///*开始接收*///
		///*******************************************************///
	NVIC_EnableIRQ(Infra_IRQn);						///*串口中断使能*///
}
///***********************************************************************************///
///*Function：低功耗唤醒后的输出红外发送的38KHz的调制信号*///
///*Description：红外通信发送前调用*///
///***********************************************************************************///
void SF_InfraModulatedSignalOutput_Wakeup(void)
{
//	InfraTimerClock_EN;						///*系统时钟提供给38kHz定时器：无分频=系统时钟*///
//	Select_InfraIO_PWM;						///*将口线配置为PWM输出功能*///
//	InfraTimer->CR1 = C_TIM_CR1_CLEAR;		///*控制寄存器清零*///
//	
//	InfraTimer->ARR = C_InfraTimerCounter_Wakeup;	///*37.736kHz*///
//	InfraTimer->CCR1 = C_InfraTimerCounter_Wakeup;
//	InfraTimer->DIER &= C_TIM_UIE_DIS;		///*禁止中断*///
//	InfraTimer->SMCR = C_TIM_SMCR_CLEAR;	///*该寄存器在定时器用作PWM输出时无用*///
//	InfraTimer->CCER &= C_TIM_OUTPUT_DIS;	///*OC1有效时为高，OC1暂配置为无效*///
//	InfraTimer->PSC = TIM_Prescaler_0;		///*不分频*///
//	InfraTimer->CCMR1 = 0x0030;				///*TIMx_CNT与TIMx_CCR1相等时口线翻转*///
//	
//	InfraTimer->CCER = 0x0003;
//	InfraTimer->EGR = C_TIM_EGR_CLEAR;
//	InfraTimer->SR &= C_TimerStatus_UIF_RESET;
//	InfraTimer->SR &= C_TimerStatus_CCIF_RESET;
//	///*******************************************************///
//	InfraTimer->CR1 |= C_TimerCounter_EN;	///*正式启动定时器开始计数*///
//	///*******************************************************///
}


///*********************************************************************************///
///*函数原型：void InF_InitCommUartForInterrupt(uchar8 CommNum)*///
///*输入参数：*///
///*	CommNum：通讯通道号。取值：C_RS485_1、C_RS485_2、C_IR、C_Module、C_ESAM、C_Card。*///
///*输出参数：无*///
///*返回参数：无*///
///*功能说明：*///
///*	1）在中断里初始化串口；*///
///*	2）该函数在发送结束后直接在中断里调用。*///
///*	1）函数名中ForDispatch表示供主流程中调用，ForInterrupt表示供中断里调用。*///
///*	2）对于红外串口，配置38kHz调制信号但关闭信号输出功能。*///
///*********************************************************************************///
void InF_InitCommUartForInterrupt(uchar8 CommNum)
{
	ulong32 V_UsartDataBuff;
	
	Enable_ComUart_Clock;///*使能commUart
	
	switch(CommNum)
	{
		case C_RS485_1:
		{
			SV_InterruptMsg_485_1 = C_Uart_Normal;		///*解析标志置为常态*///
			SV_InitUartMsg_485_1 = C_Uart_Normal;
			
			Enable_485_1_Receive;	///*使485芯片工作于接收态：3光耦方式*///
			Enable_485_1_Clock;		///*第1路485时钟使能*///
//			Select_485_1_UartMode;	///*选择AF功能为Uart功能*///
			Select_485_1_AFMode;	///*将口线功能配置AF功能*///
			Select_485_1_IO_Type;	///*口线输入无上下拉、输出推挽配置*///
			
			///*******************************************************///
//			if( (SFR_FIRST485->TXSTA&USART_StopBits_2) != USART_StopBits_1 )
//			{
//				SFR_FIRST485->TXSTA |= USART_StopBits_2;
//			}
			///*******************************************************///
			///*字符宽度不是8位就是9位,所以不需要配置*///
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
			SFR_FIRST485->RXSTA &= (~USART_ParityErrInt_EN);	///*禁止出错中断...*///
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
			V_UsartDataBuff = SFR_FIRST485->RXREG;				///*清缓存*///
			V_UsartDataBuff = SFR_FIRST485->RXSTA;				///*清状态字*///
			V_UsartDataBuff = SFR_FIRST485->RXBUFSTA;
//			SFR_FIRST485->RXREG = V_UsartDataBuff;				///*清缓存*///
			Start_First485_Rx;								///*开始接收*///
			///*******************************************************///
			NVIC_EnableIRQ(First485_IRQn);					///*串口中断使能*///
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_RS485_2:
		{
			if(C_SmartMeter==C_Meter_Type)///*程序hex兼容根据表型判断
			{
				SV_InterruptMsg_485_2 = C_Uart_Normal;		///*解析标志置为常态*///
				SV_InitUartMsg_485_2 = C_Uart_Normal;
				
				Enable_485_2_Receive;	///*使485芯片工作于接收态：3光耦方式*///
				Enable_485_2_Clock;		///*第2路485时钟使能*///
				Select_485_2_AFMode;	///*将口线功能配置AF功能*///
				Select_485_2_IO_Type;	///*口线输入上拉、输出推挽配置*///				
				
	//			if( (SFR_SECOND485->TXSTA&USART_StopBits_2) != USART_StopBits_1 )
	//			{
	//				SFR_SECOND485->TXSTA |= USART_StopBits_2;
	//			}
				///*******************************************************///
				///*字符宽度不是8位就是9位,所以不需要配置*///
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
				SFR_SECOND485->RXSTA &= (~USART_ParityErrInt_EN);	///*禁止出错中断...*///
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
				V_UsartDataBuff = SFR_SECOND485->RXREG;				///*清缓存*///
				V_UsartDataBuff = SFR_SECOND485->RXSTA;				///*清状态字*///
				V_UsartDataBuff = SFR_SECOND485->RXBUFSTA;			
	//			SFR_SECOND485->DR = V_UsartDataBuff;				///*清缓存*///
				Start_Second485_Rx;			///*开始接收*///
				///*******************************************************///
				NVIC_EnableIRQ(Second485_IRQn);					///*串口中断使能*///
				///*******************************************************///						
			}
			else 
			{
				///*******************************************************///
				NVIC_DisableIRQ(Second485_IRQn);					///*串口中断禁止*///
				///*******************************************************///	
				if(C_R_SmartMeter==C_Meter_Type)///*本地表卡接口单独配置，远程表配置为开漏输出高
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
				SV_InterruptMsg_Ir = C_Uart_Normal;			///*解析标志置为常态*///
				SV_InitUartMsg_Ir = C_Uart_Normal;
				
				SF_InfraModulatedSignalOff();
				
				Enable_Infra_Clock;		///*串口时钟使能*///
				Select_Infra_AFMode;	///*将口线功能配置AF功能*///
				Select_Infra_IO_Type;	///*口线输入无上下拉、输出推挽配置*///
				
				UART->IRCON = USART_IRCONn;///*38k,1:1
				///*******************************************************///
//				if( (SFR_INFRA->TXSTA&USART_StopBits_2) != USART_StopBits_1 )
//				{
//					SFR_INFRA->TXSTA |= USART_StopBits_2;
//				}				
				///*******************************************************///
				///*字符宽度不是8位就是9位,所以不需要配置*///
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
				SFR_INFRA->RXSTA &= (~USART_ParityErrInt_EN);	///*禁止出错中断...*///
				///*******************************************************///
				SFR_INFRA->SPBRG = USART_bps_1200;				///*1200*///
				///*******************************************************///
				SFR_INFRA->RXSTA &= (~(USART_FLAG_FE | USART_FLAG_PE|USART_FLAG_ORE));
				V_UsartDataBuff = SFR_INFRA->RXREG;				///*清缓存*///
				V_UsartDataBuff = SFR_INFRA->RXSTA;				///*清状态字*///
				V_UsartDataBuff = SFR_INFRA->RXBUFSTA;
//				SFR_INFRA->DR = V_UsartDataBuff;				///*清缓存*///
				Start_Infra_Rx;									///*开始接收*///
				///*******************************************************///
				NVIC_EnableIRQ(Infra_IRQn);						///*串口中断使能*///
				///*******************************************************///
				break;
			}
			else
			{
				SV_InterruptMsg_Ir = C_Uart_Normal;			///*解析标志置为常态*///
				SV_InitUartMsg_Ir = C_Uart_Normal;
				
				SF_InfraModulatedSignalOff();
				
				Enable_Infra_Clock;		///*串口时钟使能*///
				Select_Infra_AFMode;	///*将口线功能配置AF功能*///
				Select_Infra_IO_Type;	///*口线输入无上下拉、输出推挽配置*///
				
				UART->IRCON = USART_IRCONn_WakeUp;///*38k,1:1
				///*******************************************************///
//				if( (SFR_INFRA->TXSTA&USART_StopBits_2) != USART_StopBits_1 )
//				{
//					SFR_INFRA->TXSTA |= USART_StopBits_2;
//				}				
				///*******************************************************///
				///*字符宽度不是8位就是9位,所以不需要配置*///
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
				SFR_INFRA->RXSTA &= (~USART_ParityErrInt_EN);	///*禁止出错中断...*///
				///*******************************************************///
				SFR_INFRA->SPBRG = USART_bps_1200_Wakeup;				///*1200*///
				///*******************************************************///
				SFR_INFRA->RXSTA &= (~(USART_FLAG_FE | USART_FLAG_PE|USART_FLAG_ORE));
				V_UsartDataBuff = SFR_INFRA->RXREG;				///*清缓存*///
				V_UsartDataBuff = SFR_INFRA->RXSTA;				///*清状态字*///
				V_UsartDataBuff = SFR_INFRA->RXBUFSTA;
//				SFR_INFRA->DR = V_UsartDataBuff;				///*清缓存*///
				Start_Infra_Rx;									///*开始接收*///
				///*******************************************************///
				NVIC_EnableIRQ(Infra_IRQn);						///*串口中断使能*///
				///*******************************************************///
				break;
			}
		}
		///*******************************************************///
		case C_Module:
		{
			if(C_SmartMeter!=C_Meter_Type)///*程序hex兼容根据表型判断,远程及卡表
			{
				SV_InterruptMsg_Modular = C_Uart_Normal;	///*解析标志置为常态*///
				SV_InitUartMsg_Modular = C_Uart_Normal;
				
	//			Enable_485_2_Receive;	///*使485芯片工作于接收态：3光耦方式*///
				Enable_Modular_Clock;		///*第2路485时钟使能*///
	//			Select_Modular_UartMode;	///*选择AF功能为Uart功能*///
				Select_Modular_AFMode;	///*将口线功能配置AF功能*///
				Select_Modular_IO_Type;	///*口线输入上拉、输出推挽配置*///
				
	//			if( (SFR_SECOND485->TXSTA&USART_StopBits_2) != USART_StopBits_1 )
	//			{
	//				SFR_SECOND485->TXSTA |= USART_StopBits_2;
	//			}
				///*******************************************************///
				///*字符宽度不是8位就是9位,所以不需要配置*///
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
				SFR_MODULAR->RXSTA &= (~USART_ParityErrInt_EN);	///*禁止出错中断...*///
				///*******************************************************///
				if((SFR_MODULAR->SPBRG!=USART_bps_38400) 
					&&(SFR_MODULAR->SPBRG!=USART_bps_19200) 
					&&(SFR_MODULAR->SPBRG!=USART_bps_2400)
					&&(SFR_MODULAR->SPBRG!=USART_bps_4800)
					&&(SFR_MODULAR->SPBRG!=USART_bps_1200)
					&&(SFR_MODULAR->SPBRG!=USART_bps_600)
					&&(SFR_MODULAR->SPBRG!=USART_bps_300))
				{
					SFR_MODULAR->SPBRG = USART_bps_9600;		///*固定9600*///
				}
				///*******************************************************///
				SFR_MODULAR->RXSTA &= (~(USART_FLAG_FE | USART_FLAG_PE|USART_FLAG_ORE));
				V_UsartDataBuff = SFR_MODULAR->RXREG;				///*清缓存*///
				V_UsartDataBuff = SFR_MODULAR->RXSTA;				///*清状态字*///
				V_UsartDataBuff = SFR_MODULAR->RXBUFSTA;			
	//			SFR_SECOND485->DR = V_UsartDataBuff;				///*清缓存*///
	            
	            ///*2020标准主动上报2005*///
	            if(Inf_Comm_REPORTFlag())
	            {
	                Inf_Comm_REPORTFlagClear(0);         ///*主动上报标志清零*///
	                Start_ModularReport_Rx;
	            }
	            else
	            {
	                Start_Modular_Rx;								///*开始接收*///
	            }
				///*******************************************************///
				NVIC_EnableIRQ(Modular_IRQn);					///*串口中断使能*///
				///*******************************************************///
	
	//            Inf_Comm_ClearModuleCommuniFlag();
	            if(Inf_Comm_GetModuleCommuniFlag() == (C_CommuniSafeWorld1|C_CommuniSafeWorld2|C_CommuniSafeWorld3))
	            {
	                Inf_Comm_InitModuleCommuniFlag(C_CommuniSafeWorld4);    ///*通信结束*///
	            }
			}
			else 
			{
				///*******************************************************///
				NVIC_DisableIRQ(Modular_IRQn);					///*串口中断禁止*///
				///*******************************************************///	
				Select_Modular_ComIO_Type;///*非远程表配置为普通IO开漏输出高
			}
			break;
		}
		///*******************************************************///
//		case C_ESAM:
//		{
//			NVIC_EnableIRQ(Esam_IRQn);				///*串口中断使能*///
//			
//			Enable_ESAM_Clock;						///*串口时钟使能*///
//			
//			EsamCLK_Init();
//			Select_ESAMClk_UartMode;				///*选择AF功能且为Uart功能*///
//			
////			Set_ESAMIO_OutType;						///*数据线开漏配置*///
////			Select_ESAMIO_UartMode;					///*选择AF功能且为Uart功能*///
//			
//			Select_ESAMIO_UartMode;
//			
//			SFR_ESAMCOM->CR1 = USART_CR1_RESET;
//			SFR_ESAMCOM->CR2 = USART_CR2_RESET;
//			
//			SFR_ESAMCOM->CR1 |= USART_USART_EN;			///*Uart Enable*///
//			///*******************************************************///
//			///*配置停止位*///
//			SFR_ESAMCOM->CR2 = USART_StopBits_15;	///*1.5个停止位*///
//			///*******************************************************///
//			///*数据位长度配置*///
//			SFR_ESAMCOM->CR1 |= USART_WordLength_9b;
//			///*******************************************************///
//			///*校验位配置：偶校验*///
//			SFR_ESAMCOM->CR1 |= USART_Parity_Even;
//			///*******************************************************///
//			SFR_ESAMCOM->CR3 &= USART_CR3_RESET;	///*禁止出错中断...*///
//			///*******************************************************///
//			///*配置波特率*///
//			SFR_ESAMCOM->BRR = ESAM_bps;
//			///*******************************************************///
//			SFR_ESAMCOM->GTPR |= USART_GuardTime;		///*保护时间及分频系数*///
//			SFR_ESAMCOM->GTPR |= USART_Prescaler;
//			SFR_ESAMCOM->CR3 |= USART_SmartCard_EN;		///*Uart 工作于Smartcard模式*///
//			SFR_ESAMCOM->CR3 |= USART_NACK_EN;			///*NACK方式*///
//			
//			//SFR_ESAMCOM->CR1 |= USART_TCIE_EN;		///*使能发送中断*///
//			//SFR_ESAMCOM->CR1 |= USART_TE_Set;			///*发送使能*///
//			SFR_ESAMCOM->CR1 &= USART_RE_DIS;			///*接收禁止*///
//			SFR_ESAMCOM->CR1 &= USART_REIE_Reset_UART1;		///*接收中断禁止*///
//			
//			V_UsartDataBuff = SFR_ESAMCOM->DR;			///*清缓存*///
//			V_UsartDataBuff = SFR_ESAMCOM->SR;			///*清状态字*///
//			SFR_ESAMCOM->DR = V_UsartDataBuff;			///*清缓存*///
//			
//			SFR_ESAMCOM->SR = USART_SR_RESET;
//			///*******************************************************///
//			NVIC_EnableIRQ(Esam_IRQn);					///*串口中断使能*///
//			///*******************************************************///
//			break;
//		}
		///*******************************************************///
		case C_Card:
		{
//			NVIC_EnableIRQ(Card_IRQn);				///*串口中断使能*///
//			
//			Enable_CARD_Clock;						///*串口时钟使能*///
//			
//			Select_CARDIO_UartMode;
//			
//			SFR_CARDCOM->CR1 = USART_CR1_RESET;
//			SFR_CARDCOM->CR2 = USART_CR2_RESET;
//			
//			SFR_CARDCOM->CR1 |= USART_USART_EN;			///*Uart Enable*///
//			///*******************************************************///
//			///*配置停止位*///
//			SFR_CARDCOM->CR2 = USART_StopBits_15;	///*1.5个停止位*///
//			///*******************************************************///
//			///*数据位长度配置*///
//			SFR_CARDCOM->CR1 |= USART_WordLength_9b;
//			///*******************************************************///
//			///*校验位配置：偶校验*///
//			SFR_CARDCOM->CR1 |= USART_Parity_Even;
//			///*******************************************************///
//			SFR_CARDCOM->CR3 &= USART_CR3_RESET;	///*禁止出错中断...*///
//			///*******************************************************///
//			///*配置波特率*///
//			SFR_CARDCOM->BRR = ESAM_bps;
//			///*******************************************************///
//			SFR_CARDCOM->GTPR |= USART_GuardTime;		///*保护时间及分频系数*///
//			SFR_CARDCOM->GTPR |= USART_Prescaler;
//			SFR_CARDCOM->CR3 |= USART_SmartCard_EN;		///*Uart 工作于Smartcard模式*///
//			SFR_CARDCOM->CR3 |= USART_NACK_EN;			///*NACK方式*///
//			
//			//SFR_CARDCOM->CR1 |= USART_TCIE_EN;		///*使能发送中断*///
//			//SFR_CARDCOM->CR1 |= USART_TE_Set;			///*发送使能*///
//			SFR_CARDCOM->CR1 &= USART_RE_DIS;			///*接收禁止*///
//			SFR_CARDCOM->CR1 &= USART_REIE_Reset_UART1;		///*接收中断禁止*///
//			
//			V_UsartDataBuff = SFR_CARDCOM->DR;			///*清缓存*///
//			V_UsartDataBuff = SFR_CARDCOM->SR;			///*清状态字*///
//			SFR_CARDCOM->DR = V_UsartDataBuff;			///*清缓存*///
//			
//			SFR_CARDCOM->SR = USART_SR_RESET;
			///*******************************************************///
//			NVIC_DisableIRQ(Card_IRQn);					///*串口中断使能*///
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
//			SV_InterruptMsg_485_1 = C_Uart_Normal;		///*解析标志置为常态*///
//			SV_InitUartMsg_485_1 = C_Uart_Normal;
//			
//			Enable_485_1_Receive;	///*使485芯片工作于接收态*///
//			Enable_485_1_Clock;		///*第1路485时钟使能*///
//			Select_485_1_UartMode;	///*选择AF功能为Uart功能*///
//			Select_485_1_AFMode;	///*将口线功能配置AF功能*///
//			Select_485_1_IO_Type;	///*口线输入无上下拉、输出推挽配置*///
//			
//			SFR_FIRST485->CR1 = USART_CR1_RESET;
//			SFR_FIRST485->CR2 = USART_CR2_RESET;
//			
//			SFR_FIRST485->CR1 |= USART_USART_EN;			///*Uart Enable*///
//			///*******************************************************///
//			if(StpLen == C_SerStp_1)			///*配置停止位*///
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
//			if(DataLen == C_CommDataLen8)		///*数据位长度配置*///
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
//			if(parityChk == C_parity_Even)		///*校验位配置*///
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
//			SFR_FIRST485->CR3 &= USART_CR3_RESET;	///*禁止出错中断...*///
//			///*******************************************************///
//			switch(bps)							///*配置波特率*///
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
//			V_UsartDataBuff = SFR_FIRST485->DR;			///*清缓存*///
//			V_UsartDataBuff = SFR_FIRST485->SR;			///*清状态字*///
//			SFR_FIRST485->DR = V_UsartDataBuff;			///*清缓存*///
//			
//			Start_First485_Rx;								///*开始接收*///
//			///*******************************************************///
//			NVIC_EnableIRQ(First485_IRQn);					///*串口中断使能*///
//			///*******************************************************///
//    return C_OK;
//}
///************************************************************************************************************************///

///*函数原型：uchar8 InF_InitCommUartForDispatch(uchar8 CommNum,uchar8 bps,uchar8 DataLen,uchar8 StpLen,uchar8 parityChk)*///
///*输入参数：                                                                                                           *///
///*	CommNum：通讯通道号。取值：C_RS485_1、C_RS485_2、C_IR、C_Module、C_ESAM、C_Card。                                *///
///*	bps：波特率。取值：C_bps_300, C_bps_1200, C_bps_2400, C_bps_4800, C_bps_9600、C_bps_19200, C_bps_38400           *///
///*	DataLen：数据位数。取值C_CommDataLen7, C_CommDataLen8                                                            *///
///*	SerStp：停止位数。取值1，2                                                                                       *///
///*	parityChk：取值C_parity_None（无校验）, C_parity_Even（偶校验）, C_parity_Odd（奇校验）                          *///
///*输出参数：无                                                                                                         *///
///*返回参数：C_Ok，C_Error（入口错误）                                                                                  *///
///*功能说明：                                                                                                           *///
///*	1）按照输入条件配置串口；                                                                                        *///
///*	2）对于645协议关闭串口发送中断，打开接收中断；对于7816协议关闭串口发送中断，关闭接收中断。                       *///
///*	3）配置完成需要将相应的IF标志手工清零。                                                                          *///
///*调用机制：                                                                                                           *///
///*	1）该函数主调度不直接调用。                                                                                      *///
///*	2）由上电初始化接口函数调用，依次初始化485_1、485_2、IR、Module、Esam、SmartCard所使用的Uart口。                 *///
///*	3）提供给超时、发送结束等函数调用。                                                                              *///
///*备    注：                                                                                                           *///
///*	1）函数名中ForDispatch表示供主流程中调用，ForInterrupt表示供中断里调用。                                         *///
///*	2）对于红外串口，配置38kHz调制信号但关闭信号输出功能。                                                           *///
///************************************************************************************************************************///
uchar8 InF_InitCommUartForDispatch(uchar8 CommNum,uchar8 bps,uchar8 DataLen,uchar8 StpLen,uchar8 parityChk)
{
	uchar8 return_value = C_OK;
    ulong32 V_UsartDataBuff;
	
	Enable_ComUart_Clock;///*使能commUart      
	switch(CommNum)
	{
		case C_RS485_1:
		{
			SV_InterruptMsg_485_1 = C_Uart_Normal;		///*解析标志置为常态*///
			SV_InitUartMsg_485_1 = C_Uart_Normal;
			SV_Overtime_485_1 = 0;			///*超时定时器清零*///
			
			Enable_485_1_Receive;	///*使485芯片工作于接收态*///
			Enable_485_1_Clock;		///*第1路485时钟使能*///
			Select_485_1_AFMode;	///*将口线功能配置AF功能*///
			Select_485_1_IO_Type;	///*口线输入无上下拉、输出推挽配置*///
			
			///*******************************************************///
			SFR_FIRST485->TXSTA &= (~USART_StopBits_2);
			if(StpLen == C_SerStp_1)			/*配置停止位*///
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
//			if(DataLen == C_CommDataLen8)		/*数据位长度配置,奇偶校验*///
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
			SFR_FIRST485->RXSTA &= (~USART_ParityErrInt_EN);	///*禁止出错中断...*///
			///*******************************************************///
			switch(bps)							///*配置波特率*///
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
			V_UsartDataBuff = SFR_FIRST485->RXREG;				///*清缓存*///
			V_UsartDataBuff = SFR_FIRST485->RXSTA;				///*清状态字*///
			V_UsartDataBuff = SFR_FIRST485->RXBUFSTA;
//			SFR_FIRST485->RXREG = V_UsartDataBuff;				///*清缓存*///
			
			Start_First485_Rx;								///*开始接收*///
			///*******************************************************///
			NVIC_EnableIRQ(First485_IRQn);					///*串口中断使能*///
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_RS485_2:
///*		case C_Module:
		{
			if(C_SmartMeter==C_Meter_Type)///*程序hex兼容根据表型判断
			{
				///*两路解析标志都初始化*///
				SV_InterruptMsg_485_2 = C_Uart_Normal;		///*解析标志置为常态*///
				SV_InitUartMsg_485_2 = C_Uart_Normal;
				SV_InterruptMsg_Modular = C_Uart_Normal;	///*解析标志置为常态*///
				SV_InitUartMsg_Modular = C_Uart_Normal;
				SV_Overtime_485_2 = 0;			///*超时定时器清零*///
				
				Enable_485_2_Receive;	///*使485芯片工作于接收态：3光耦方式*///
				Enable_485_2_Clock;		///*第2路485时钟使能*///
				Select_485_2_AFMode;	///*将口线功能配置AF功能*///
				Select_485_2_IO_Type;	///*口线输入上拉、输出推挽配置*///
				
				
				SFR_SECOND485->TXSTA &= (~USART_StopBits_2);
				///*******************************************************///
				if(StpLen == C_SerStp_1)			/*配置停止位*///
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
	//			if(DataLen == C_CommDataLen8)		/*数据位长度配置,奇偶校验*///
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
				SFR_SECOND485->RXSTA &= (~USART_ParityErrInt_EN);	///*禁止出错中断...*///
				///*******************************************************///
				switch(bps)							///*配置波特率*///
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
				V_UsartDataBuff = SFR_SECOND485->RXREG;			///*清缓存*///
				V_UsartDataBuff = SFR_SECOND485->RXSTA;			///*清状态字*///
				V_UsartDataBuff = SFR_SECOND485->RXBUFSTA;
	//			SFR_SECOND485->DR = V_UsartDataBuff;			///*清缓存*///
				Start_Second485_Rx;			///*开始接收*///
				///*******************************************************///
				NVIC_EnableIRQ(Second485_IRQn);					///*串口中断使能*///
				///*******************************************************///
			}
			else 
			{
				///*******************************************************///
				NVIC_DisableIRQ(Second485_IRQn);					///*串口中断禁止*///
				///*******************************************************///	
				if(C_R_SmartMeter==C_Meter_Type)///*本地表卡接口单独配置，远程表配置为开漏输出高
				{
					Select_485_2_ComIO_Type;
				}	
			}
			break;
		}
		case C_Module:
		{
			if(C_SmartMeter!=C_Meter_Type)///*程序hex兼容根据表型判断,远程及卡表
			{
				///*两路解析标志都初始化*///
				SV_InterruptMsg_485_2 = C_Uart_Normal;		///*解析标志置为常态*///
				SV_InitUartMsg_485_2 = C_Uart_Normal;
				SV_InterruptMsg_Modular = C_Uart_Normal;	///*解析标志置为常态*///
				SV_InitUartMsg_Modular = C_Uart_Normal;
				SV_Overtime_485_2 = 0;			///*超时定时器清零*///
				
	///*			Enable_485_2_Receive;	///*使485芯片工作于接收态：3光耦方式*///
				Enable_Modular_Clock;		///*第2路485时钟使能*///
				Select_Modular_AFMode;	///*将口线功能配置AF功能*///
				Select_Modular_IO_Type;	///*口线输入上拉、输出推挽配置*///
				
				
				SFR_MODULAR->TXSTA &= (~USART_StopBits_2);
				///*******************************************************///
				if(StpLen == C_SerStp_1)			/*配置停止位*///
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
	//			if(DataLen == C_CommDataLen8)		/*数据位长度配置,奇偶校验*///
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
				switch(bps)							///*配置波特率*///
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
				
	//			SFR_MODULAR->SPBRG = USART_bps_9600;		///*固定9600*///
				///*******************************************************///
				SFR_MODULAR->RXSTA &= (~(USART_FLAG_FE | USART_FLAG_PE|USART_FLAG_ORE));
				V_UsartDataBuff = SFR_MODULAR->RXREG;			///*清缓存*///
				V_UsartDataBuff = SFR_MODULAR->RXSTA;			///*清状态字*///
				V_UsartDataBuff = SFR_MODULAR->RXBUFSTA;
	//			SFR_SECOND485->DR = V_UsartDataBuff;			///*清缓存*///
	            ///*2020标准主动上报*///
	            if(Inf_Comm_REPORTFlag() != C_ReportNULL)           ///*可能处于事件上报或者掉电上报*///
	            {
	                Start_ModularReport_Rx;     //*开始接收不关发送*///
	            }
	            else
	            {
	                Start_Modular_Rx;			///*开始接收*///
	            }
	            //Inf_Comm_InitModuleCommuniFlag(C_CommuniSafeWorld1|C_CommuniSafeWorld2|C_CommuniSafeWorld3|C_CommuniSafeWorld4);
	            Inf_Comm_ClearModuleCommuniFlag(0);
#if 0
                Inf_Comm_REPORTFlagClear(0);            /*不能初始化，因为如果通信错误，就会初始化串口这时候可能处于上报过程中*/
#endif
				///*******************************************************///
				NVIC_EnableIRQ(Modular_IRQn);					///*串口中断使能*///
				///*******************************************************///
			}
			else 
			{
				///*******************************************************///
				NVIC_DisableIRQ(Modular_IRQn);					///*串口中断禁止*///
				///*******************************************************///	
				Select_Modular_ComIO_Type;///*非远程表配置为普通IO开漏输出高
			}
			break;
		}		
		///*******************************************************///
		case C_IR:
		{
			if( InF_ReadPowerState() == C_PowerOn )
			{	
				SV_InterruptMsg_Ir = C_Uart_Normal;			///*解析标志置为常态*///
				SV_InitUartMsg_Ir = C_Uart_Normal;
				SV_Overtime_Ir = 0;			///*超时定时器清零*///
				
				SF_InfraModulatedSignalOff();
				
				Enable_Infra_Clock;		///*串口时钟使能*///
				Select_Infra_AFMode;	///*将口线功能配置AF功能*///
				Select_Infra_IO_Type;	///*口线输入无上下拉、输出推挽配置*///
				
				UART->IRCON = USART_IRCONn;///*38k,1:1
				SFR_INFRA->TXSTA &= (~USART_StopBits_2);
				///*******************************************************///
				if(StpLen == C_SerStp_1)			/*配置停止位*///
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
//			if(DataLen == C_CommDataLen8)		/*数据位长度配置,奇偶校验*///
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
				SFR_INFRA->RXSTA &= (~USART_ParityErrInt_EN);	///*禁止出错中断...*///
				///*******************************************************///
				SFR_INFRA->SPBRG = USART_bps_1200;				///*1200*///
				///*******************************************************///
				SFR_INFRA->RXSTA &= (~(USART_FLAG_FE | USART_FLAG_PE|USART_FLAG_ORE));
				V_UsartDataBuff = SFR_INFRA->RXREG;				///*清缓存*///
				V_UsartDataBuff = SFR_INFRA->RXSTA;				///*清状态字*///
				V_UsartDataBuff = SFR_INFRA->RXBUFSTA;
//				SFR_INFRA->DR = V_UsartDataBuff;				///*清缓存*///
				Start_Infra_Rx;									///*开始接收*///
				///*******************************************************///
				NVIC_EnableIRQ(Infra_IRQn);						///*串口中断使能*///
				///*******************************************************///
				break;
			}
			else
			{
				SV_InterruptMsg_Ir = C_Uart_Normal;			///*解析标志置为常态*///
				SV_InitUartMsg_Ir = C_Uart_Normal;
				
				SF_InfraModulatedSignalOff();
				
				Enable_Infra_Clock;		///*串口时钟使能*///
				Select_Infra_AFMode;	///*将口线功能配置AF功能*///
				Select_Infra_IO_Type;	///*口线输入无上下拉、输出推挽配置*///
				
				UART->IRCON = USART_IRCONn_WakeUp;///*38k,1:1
				SFR_INFRA->TXSTA &= (~USART_StopBits_2);
				///*******************************************************///
				if(StpLen == C_SerStp_1)			/*配置停止位*///
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
//			if(DataLen == C_CommDataLen8)		/*数据位长度配置,奇偶校验*///
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
				SFR_INFRA->RXSTA &= (~USART_ParityErrInt_EN);	///*禁止出错中断...*///
				///*******************************************************///
				SFR_INFRA->SPBRG = USART_bps_1200_Wakeup;				///*1200*///
				///*******************************************************///
				SFR_INFRA->RXSTA &= (~(USART_FLAG_FE | USART_FLAG_PE|USART_FLAG_ORE));
				V_UsartDataBuff = SFR_INFRA->RXREG;				///*清缓存*///
				V_UsartDataBuff = SFR_INFRA->RXSTA;				///*清状态字*///
				V_UsartDataBuff = SFR_INFRA->RXBUFSTA;
//				SFR_INFRA->DR = V_UsartDataBuff;				///*清缓存*///
				Start_Infra_Rx;									///*开始接收*///
				///*******************************************************///
				NVIC_EnableIRQ(Infra_IRQn);						///*串口中断使能*///
				///*******************************************************///
				break;
			}
		}
		///*******************************************************///
//		case C_ESAM:
//		{
////			NVIC_EnableIRQ(Esam_IRQn);				///*串口中断使能*///
//			
//			Enable_ESAM_Clock;						///*串口时钟使能*///
//			
//			EsamCLK_Init();
//			Select_ESAMClk_UartMode;				///*选择AF功能且为Uart功能*///
//			
////			Set_ESAMIO_OutType;						///*数据线开漏配置*///
////			Select_ESAMIO_UartMode;					///*选择AF功能且为Uart功能*///
//			
//			Select_ESAMIO_UartMode;
//			
//			SFR_ESAMCOM->CR1 = USART_CR1_RESET;
//			SFR_ESAMCOM->CR2 = USART_CR2_RESET;
//			
//			SFR_ESAMCOM->CR1 |= USART_USART_EN;			///*Uart Enable*///
//			///*******************************************************///
//			///*配置停止位*///
//			SFR_ESAMCOM->CR2 = USART_StopBits_15;	///*1.5个停止位*///
//			///*******************************************************///
//			///*数据位长度配置*///
//			SFR_ESAMCOM->CR1 |= USART_WordLength_9b;
//			///*******************************************************///
//			///*校验位配置：偶校验*///
//			SFR_ESAMCOM->CR1 |= USART_Parity_Even;
//			///*******************************************************///
//			SFR_ESAMCOM->CR3 &= USART_CR3_RESET;	///*禁止出错中断...*///
//			///*******************************************************///
//			///*配置波特率*///
//			SFR_ESAMCOM->BRR = ESAM_bps;
//			///*******************************************************///
//			SFR_ESAMCOM->GTPR |= USART_GuardTime;		///*保护时间及分频系数*///
//			SFR_ESAMCOM->GTPR |= USART_Prescaler;
//			SFR_ESAMCOM->CR3 |= USART_SmartCard_EN;		///*Uart 工作于Smartcard模式*///
//			SFR_ESAMCOM->CR3 |= USART_NACK_EN;			///*NACK方式*///
//			
//			//SFR_ESAMCOM->CR1 |= USART_TCIE_EN;		///*使能发送中断*///
//			//SFR_ESAMCOM->CR1 |= USART_TE_Set;			///*发送使能*///
//			SFR_ESAMCOM->CR1 &= USART_RE_DIS;			///*接收禁止*///
//			SFR_ESAMCOM->CR1 &= USART_REIE_Reset_UART1;		///*接收中断禁止*///
//			
//			V_UsartDataBuff = SFR_ESAMCOM->DR;			///*清缓存*///
//			V_UsartDataBuff = SFR_ESAMCOM->SR;			///*清状态字*///
//			SFR_ESAMCOM->DR = V_UsartDataBuff;			///*清缓存*///
//			
//			SFR_ESAMCOM->SR = USART_SR_RESET;
//			///*******************************************************///
//			NVIC_EnableIRQ(Esam_IRQn);					///*串口中断使能*///
//			///*******************************************************///
//			break;
//		}
		///*******************************************************///
		case C_Card:
		{
//			NVIC_EnableIRQ(Card_IRQn);				///*串口中断使能*///
			
//			Enable_CARD_Clock;						///*串口时钟使能*///
//			
//			Select_CARDIO_UartMode;
//			
//			SFR_CARDCOM->CR1 = USART_CR1_RESET;
//			SFR_CARDCOM->CR2 = USART_CR2_RESET;
//			
//			SFR_CARDCOM->CR1 |= USART_USART_EN;			///*Uart Enable*///
//			///*******************************************************///
//			///*配置停止位*///
//			SFR_CARDCOM->CR2 = USART_StopBits_15;	///*1.5个停止位*///
//			///*******************************************************///
//			///*数据位长度配置*///
//			SFR_CARDCOM->CR1 |= USART_WordLength_9b;
//			///*******************************************************///
//			///*校验位配置：偶校验*///
//			SFR_CARDCOM->CR1 |= USART_Parity_Even;
//			///*******************************************************///
//			SFR_CARDCOM->CR3 &= USART_CR3_RESET;	///*禁止出错中断...*///
//			///*******************************************************///
//			///*配置波特率*///
//			SFR_CARDCOM->BRR = ESAM_bps;
//			///*******************************************************///
//			SFR_CARDCOM->GTPR |= USART_GuardTime;		///*保护时间及分频系数*///
//			SFR_CARDCOM->GTPR |= USART_Prescaler;
//			SFR_CARDCOM->CR3 |= USART_SmartCard_EN;		///*Uart 工作于Smartcard模式*///
//			SFR_CARDCOM->CR3 |= USART_NACK_EN;			///*NACK方式*///
//			
//			//SFR_CARDCOM->CR1 |= USART_TCIE_EN;		///*使能发送中断*///
//			//SFR_CARDCOM->CR1 |= USART_TE_Set;			///*发送使能*///
////			SFR_CARDCOM->CR1 &= USART_RE_DIS;			///*接收禁止*///
////			SFR_CARDCOM->CR1 &= USART_REIE_Reset_UART1;		///*接收中断禁止*///
//			
//			V_UsartDataBuff = SFR_CARDCOM->DR;			///*清缓存*///
//			V_UsartDataBuff = SFR_CARDCOM->SR;			///*清状态字*///
//			SFR_CARDCOM->DR = V_UsartDataBuff;			///*清缓存*///
//			
//			SFR_CARDCOM->SR = USART_SR_RESET;
//			///*******************************************************///
//			NVIC_DisableIRQ(Card_IRQn);					///*串口中断使能*///
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
///*函数原型：uchar8 InF_CommUart_RecDisableForInterrupt (uchar8 CommNum)                            *///
///*入口参数：CommNum：通讯通道号。取值：取值：C_RS485_1、C_RS485_2、C_IR、C_Module、C_ESAM、C_Card。*///
///*输出参数：无                                                                                     *///
///*返回参数：C_Ok，C_Error（入口错误）                                                              *///
///*功能说明：关闭串口接收，包括接收中断使能                                                         *///
///*备    注：函数名中ForDispatch表示供主流程中调用，ForInterrupt表示供中断里调用。                  *///
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
			Stop_First485_Rx;								///*停止接收*///
			return_value = SFR_FIRST485->RXREG;			///*接收的数据读入缓存*///
			return_value = C_OK;
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_RS485_2:
		{
			///*******************************************************///
			Stop_Second485_Rx;								///*停止接收*///
			return_value = SFR_SECOND485->RXREG;			///*接收的数据读入缓存*///
			return_value = C_OK;
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_IR:
		{
			///*******************************************************///
			Stop_Infra_Rx;									///*停止接收*///
			return_value = SFR_INFRA->RXREG;			///*接收的数据读入缓存*///
			return_value = C_OK;
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_Module:
		{
			///*******************************************************///
			Stop_Modular_Rx;								///*停止接收*///
			return_value = SFR_MODULAR->RXREG;			///*接收的数据读入缓存*///
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
///*函数原型：uchar8 InF_CommUart_RecDisableForDispatch (uchar8 CommNum)                             *///
///*入口参数：CommNum：通讯通道号。取值：取值：C_RS485_1、C_RS485_2、C_IR、C_Module、C_ESAM、C_Card。*///
///*输出参数：无                                                                                     *///
///*返回参数：C_Ok，C_Error（入口错误）                                                              *///
///*功能说明：关闭串口接收，包括接收中断使能                                                         *///
///*备    注：函数名中ForDispatch表示供主流程中调用，ForInterrupt表示供中断里调用。                  *///
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
			Stop_First485_Rx;								///*停止接收*///
			return_value = SFR_FIRST485->RXREG;			///*接收的数据读入缓存*///
			return_value = C_OK;
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_RS485_2:
		{
			///*******************************************************///
			Stop_Second485_Rx;								///*停止接收*///
			return_value = SFR_SECOND485->RXREG;			///*接收的数据读入缓存*///
			return_value = C_OK;
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_IR:
		{
			///*******************************************************///
			Stop_Infra_Rx;									///*停止接收*///
			return_value = SFR_INFRA->RXREG;			///*接收的数据读入缓存*///
			return_value = C_OK;
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_Module:
		{
			///*******************************************************///
			Stop_Modular_Rx;								///*停止接收*///
			return_value = SFR_MODULAR->RXREG;			///*接收的数据读入缓存*///
			return_value = C_OK;
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_ESAM:			/* ESAM采用SPI口操作 */
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
///*函数原型：uchar8 InF_CommUart_RecEnableForInterrupt (uchar8 CommNum)             *///
///*入口参数：CommNum：通讯通道号。取值：C_ESAM、C_Card。                            *///
///*输出参数：无                                                                     *///
///*返回参数：C_Ok，C_Error（入口错误）                                              *///
///*功能说明：允许串口接收，包括接收中断使能；关闭串口发送，包括发送中断。           *///
///*备    注：                                                                       *///
///*	1）对于645协议，电能表是从模式，因此初始化串口时电能表就处于等待接收状态；   *///
///*	   对于7816协议，电能表是主模式，此时接收是关闭的，                          *///
///*	   因此需要提供一个接口函数使能串口处于接收状态并打开接收中断，关闭发送功能。*///
///*	2）对于红外串口，需要关闭38kHz调制信号输出功能。                             *///
///*	3）函数名中ForDispatch表示供主流程中调用，ForInterrupt表示供中断里调用。     *///
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
			Start_First485_Rx;								///*开始接收*///
			///*******************************************************///
			NVIC_EnableIRQ(First485_IRQn);					///*串口中断使能*///
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
				Start_Second485_Rx;								///*开始接收*///
				///*******************************************************///
				NVIC_EnableIRQ(Second485_IRQn);					///*串口中断使能*///
				///*******************************************************///
			}
			break;
		}
		///*******************************************************///
		case C_IR:
		{
			SF_InfraModulatedSignalOff();
			///*******************************************************///
			Start_Infra_Rx;									///*开始接收*///
			///*******************************************************///
			NVIC_EnableIRQ(Infra_IRQn);						///*串口中断使能*///
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_Module:			///*模块与第2路RS485共用*///
		{
			if(C_SmartMeter!=C_Meter_Type)///*程序hex兼容根据表型判断,远程及卡表
			{
				///*******************************************************///
				Start_Modular_Rx;								///*开始接收*///
				///*******************************************************///
				NVIC_EnableIRQ(Modular_IRQn);					///*串口中断使能*///
				///*******************************************************///
			}
			break;
		}
		///*******************************************************///
//		case C_ESAM:
//		{
//			///*******************************************************///
//			SFR_ESAMCOM->CR1 &= USART_TCIE_DIS;				///*禁止发送中断*///
//			SFR_ESAMCOM->CR1 &= USART_TE_Reset;				///*发送禁止*///
//			SFR_ESAMCOM->CR1 |= USART_RE_EN;				///*接收使能*///
//			//SFR_ESAMCOM->CR1 |= USART_REIE_Set_UART1;				///*接收中断使能*///
//			SFR_ESAMCOM->SR &= (~USART_FLAG_RXNE);			///*清接收中断标志*///
//			///*******************************************************///
//			NVIC_DisableIRQ(Esam_IRQn);						///*串口中断使能*///
//			///*******************************************************///
//			break;
//		}
		///*******************************************************///
		case C_Card:
		{
			///*******************************************************///
//			SFR_CARDCOM->CR1 &= USART_TCIE_DIS;				///*禁止发送中断*///
//			SFR_CARDCOM->CR1 &= USART_TE_Reset;				///*发送禁止*///
//			SFR_CARDCOM->CR1 |= USART_RE_EN;				///*接收使能*///
//			//SFR_CARDCOM->CR1 |= USART_REIE_Set_UART1;				///*接收中断使能*///
//			SFR_CARDCOM->SR &= (~USART_FLAG_RXNE);			///*清接收中断标志*///
			///*******************************************************///
//			NVIC_DisableIRQ(Card_IRQn);						///*串口中断使能*///
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
///*函数原型：uchar8 InF_CommUart_RecEnableForDispatch (uchar8 CommNum)              *///
///*入口参数：CommNum：通讯通道号。取值：C_ESAM、C_Card。                            *///
///*输出参数：无                                                                     *///
///*返回参数：C_Ok，C_Error（入口错误）                                              *///
///*功能说明：允许串口接收，包括接收中断使能；关闭串口发送，包括发送中断。           *///
///*备    注：                                                                       *///
///*	1）对于645协议，电能表是从模式，因此初始化串口时电能表就处于等待接收状态；   *///
///*	   对于7816协议，电能表是主模式，此时接收是关闭的，                          *///
///*	   因此需要提供一个接口函数使能串口处于接收状态并打开接收中断，关闭发送功能。*///
///*	2）对于红外串口，需要关闭38kHz调制信号输出功能。                             *///
///*	3）函数名中ForDispatch表示供主流程中调用，ForInterrupt表示供中断里调用。     *///
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
			Start_First485_Rx;								///*开始接收*///
			///*******************************************************///
			NVIC_EnableIRQ(First485_IRQn);					///*串口中断使能*///
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
				Start_Second485_Rx;								///*开始接收*///
				///*******************************************************///
				NVIC_EnableIRQ(Second485_IRQn);					///*串口中断使能*///
				///*******************************************************///
			}
			break;
		}
		///*******************************************************///
		case C_IR:
		{
			SF_InfraModulatedSignalOff();
			///*******************************************************///
			Start_Infra_Rx;									///*开始接收*///
			///*******************************************************///
			NVIC_EnableIRQ(Infra_IRQn);						///*串口中断使能*///
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_Module:			///*模块与第2路RS485共用*///
		{
			if(C_SmartMeter!=C_Meter_Type)///*程序hex兼容根据表型判断,远程及卡表
			{
				///*******************************************************///
				Start_Modular_Rx;								///*开始接收*///
				///*******************************************************///
				NVIC_EnableIRQ(Modular_IRQn);					///*串口中断使能*///
				///*******************************************************///
			}
			break;
		}
		///*******************************************************///
//		case C_ESAM:
//		{
//			///*******************************************************///
//			SFR_ESAMCOM->CR1 &= USART_TCIE_DIS;				///*禁止发送中断*///
//			SFR_ESAMCOM->CR1 &= USART_TE_Reset;				///*发送禁止*///
//			SFR_ESAMCOM->CR1 |= USART_RE_EN;				///*接收使能*///
//			//SFR_ESAMCOM->CR1 |= USART_REIE_Set_UART1;				///*接收中断使能*///
//			SFR_ESAMCOM->SR &= (~USART_FLAG_RXNE);			///*清接收中断标志*///
//			///*******************************************************///
//			NVIC_EnableIRQ(Esam_IRQn);						///*串口中断使能*///
//			///*******************************************************///
//			break;
//		}
		///*******************************************************///
		case C_Card:
		{
			///*******************************************************///
//			V_UsartDataBuff = SFR_CARDCOM->SR;			///*清状态字*///
//			V_UsartDataBuff = SFR_CARDCOM->DR;			///*清缓存*///
//			SFR_CARDCOM->CR1 &= USART_TCIE_DIS;				///*禁止发送中断*///
//			SFR_CARDCOM->CR1 &= USART_TE_Reset;				///*发送禁止*///
//			SFR_CARDCOM->CR1 |= USART_RE_EN;				///*接收使能*///
//			//SFR_CARDCOM->CR1 |= USART_REIE_Set_UART1;				///*接收中断使能*///
////			SFR_CARDCOM->SR &= (~USART_FLAG_RXNE);			///*清接收中断标志*///
			///*******************************************************///
//			NVIC_DisableIRQ(Card_IRQn);						///*串口中断使能*///
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
///*函数原型：uchar8 InF_CommUart_TxdDataForInterrupt (uchar8 CommNum,uchar8 TxdData)          *///
///*入口参数：CommNum：通讯通道号。取值：C_RS485_1、C_RS485_2、C_IR、C_Module、C_ESAM、C_Card。*///
///*          TxdData：串口本次发送字节                                                        *///
///*输出参数：无                                                                               *///
///*返回参数：C_Ok，C_Error（入口错误）                                                        *///
///*功能说明：关闭串口接收及接收中断使能，发送一个字节数据，并打开串口发送中断使能。           *///
///*调用机制：                                                                                 *///
///*	1）通讯解析函数中，判断有发送消息标志，调用启动发送。                                  *///
///*	2）在通讯发送中断中，调用。                                                            *///
///*	3）对于红外串口，发送1字节时，需要使能38kHz调制信号。                                  *///
///*	4）函数名中ForDispatch表示供主流程中调用，ForInterrupt表示供中断里调用。               *///
///*********************************************************************************************///
uchar8 InF_CommUart_TxdDataForInterrupt(uchar8 CommNum,uchar8 TxdData)
{
	uchar8 return_value = C_OK;

	switch(CommNum)
	{
		case C_RS485_1:
		{
			Enable_485_1_Transmit;	///*使485芯片工作于发送态：3光耦方式*///
			///*******************************************************///
//			SFR_FIRST485->SR = USART_SR_RESET;
//			SFR_FIRST485->CR1 |= USART_USART_EN;			///*Uart Enable*///
			///*******************************************************///
			Stop_First485_Rx;								///*接收终止*///
			///*******************************************************///
			Start_First485_Tx;								///*开始发送*///
			///*******************************************************///
			SFR_FIRST485->TXREG = TxdData;						///*数据送入串口数据寄存器*///
			///*******************************************************///
			NVIC_EnableIRQ(First485_IRQn);					///*串口中断使能*///
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_RS485_2:
		{
			if(C_SmartMeter==C_Meter_Type)///*程序hex兼容根据表型判断
			{
				Enable_485_2_Transmit;	/*使485芯片工作于发送态：3光耦方式*///
				/*******************************************************///
	//			SFR_SECOND485->SR = USART_SR_RESET;
	//			SFR_SECOND485->CR1 |= USART_USART_EN;			/*Uart Enable*///
				/*******************************************************///
				Stop_Second485_Rx;								/*接收终止*///
				/*******************************************************///
				Start_Second485_Tx;								/*开始发送*///
				/*******************************************************///
				SFR_SECOND485->TXREG = TxdData;					/*数据送入串口数据寄存器*///
				/*******************************************************///
				NVIC_EnableIRQ(Second485_IRQn);					/*串口中断使能*///
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
				Stop_Infra_Rx;									/*接收终止*///
				/*******************************************************///
				/*******************************************************///
				SF_InfraModulatedSignalOutput();				/*PWM输出*///
				/*******************************************************///
				Start_Infra_Tx;									/*开始发送*///
				/*******************************************************///
				/*******************************************************///
				SFR_INFRA->TXREG = TxdData;						/*数据送入串口数据寄存器*///
				/*******************************************************///
				NVIC_EnableIRQ(Infra_IRQn);						/*串口中断使能*///
				/*******************************************************///
				break;
			}
//			else
//			{
//				/*******************************************************///
//				SFR_INFRA->SR = USART_SR_RESET;
//				SFR_INFRA->CR1 |= USART_USART_EN;				/*Uart Enable*///
//				/*******************************************************///
//				Stop_Infra_Rx;									/*接收终止*///
//				/*******************************************************///
//				/*******************************************************///
//				SF_InfraModulatedSignalOutput_Wakeup();			/*PWM输出*///
//				/*******************************************************///
//				Start_Infra_Tx;									/*开始发送*///
//				/*******************************************************///
//				/*******************************************************///
//				SFR_INFRA->DR = TxdData;						/*数据送入串口数据寄存器*///
//				/*******************************************************///
//				NVIC_EnableIRQ(Infra_IRQn);						/*串口中断使能*///
//				/*******************************************************///
//				break;
//			}
		}
		/*******************************************************///
		case C_Module:				/*模块与第2路RS485共用*///
		{
			if(C_SmartMeter!=C_Meter_Type)///*程序hex兼容根据表型判断,远程及卡表
			{
				/*******************************************************///
	//			SFR_SECOND485->SR = USART_SR_RESET;
	//			SFR_SECOND485->CR1 |= USART_USART_EN;			/*Uart Enable*///
				/*******************************************************///
				Stop_Modular_Rx;								/*接收终止*///
				/*******************************************************///
				Start_Modular_Tx;								/*开始发送*///
				/*******************************************************///
				SFR_MODULAR->TXREG = TxdData;					/*数据送入串口数据寄存器*///
				/*******************************************************///
				NVIC_EnableIRQ(Modular_IRQn);					/*串口中断使能*///
				/*******************************************************///
			}
			break;
		}
		///*******************************************************///
//		case C_ESAM:
//		{
//			///*******************************************************///
//			SFR_ESAMCOM->CR1 |= USART_TE_Set;				///*发送使能*///
//			//SFR_ESAMCOM->CR1 |= USART_TXEIE_EN_UART1;				///*发送中断使能*///
//			
//			SFR_ESAMCOM->CR1 &= USART_RE_DIS;				///*接收禁止*///
//			SFR_ESAMCOM->CR1 &= USART_REIE_Reset_UART1_UART1;			///*接收中断禁止*///
//			///*******************************************************///
//			SFR_ESAMCOM->DR = TxdData;						///*数据送入串口数据寄存器*///
//			///*******************************************************///
//			NVIC_EnableIRQ(Esam_IRQn);						///*串口中断使能*///
//			///*******************************************************///
//			break;
//		}
		///*******************************************************///
		case C_Card:
		{
			///*******************************************************///
//			SFR_CARDCOM->CR1 |= USART_TE_Set;				///*发送使能*///
//			//SFR_CARDCOM->CR1 |= USART_TXEIE_EN_UART1;				///*发送中断使能*///
//			
//			SFR_CARDCOM->CR1 &= USART_RE_DIS;				///*接收禁止*///
//			SFR_CARDCOM->CR1 &= USART_REIE_Reset_UART1;			///*接收中断禁止*///
//			///*******************************************************///
//			SFR_CARDCOM->DR = TxdData;						///*数据送入串口数据寄存器*///
			///*******************************************************///
//			NVIC_DisableIRQ(Card_IRQn);						///*串口中断使能*///
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
///*函数原型：uchar8 InF_CommUart_TxdDataForDispatch (uchar8 CommNum,uchar8 TxdData)           *///
///*入口参数：CommNum：通讯通道号。取值：C_RS485_1、C_RS485_2、C_IR、C_Module、C_ESAM、C_Card。*///
///*          TxdData：串口本次发送字节                                                        *///
///*输出参数：无                                                                               *///
///*返回参数：C_Ok，C_Error（入口错误）                                                        *///
///*功能说明：关闭串口接收及接收中断使能，发送一个字节数据，并打开串口发送中断使能。           *///
///*调用机制：                                                                                 *///
///*	1）通讯解析函数中，判断有发送消息标志，调用启动发送。                                  *///
///*	2）在通讯发送中断中，调用。                                                            *///
///*	3）对于红外串口，发送1字节时，需要使能38kHz调制信号。                                  *///
///*	4）函数名中ForDispatch表示供主流程中调用，ForInterrupt表示供中断里调用。               *///
///*********************************************************************************************///
//uchar8 InF_CommUart_TxdDataForDispatch(uchar8 CommNum,uchar8 TxdData)
uchar8 InF_CommUart_TxdDataForDispatch(uchar8 CommNum,uchar8 TxdData,uchar8 ReportMode)
{
	uchar8 return_value = C_OK;

	switch(CommNum)
	{
		case C_RS485_1:
		{
			Enable_485_1_Transmit;	///*使485芯片工作于发送态：3光耦方式*///
			///*******************************************************///
///*			SFR_FIRST485->SR = USART_SR_RESET;
///			SFR_FIRST485->CR1 |= USART_USART_EN;			///*Uart Enable*///*/
			///*******************************************************///
			Stop_First485_Rx;								///*接收终止*///
			///*******************************************************///
			Start_First485_Tx;								///*开始发送*///
			///*******************************************************///
			SFR_FIRST485->TXREG = TxdData;						///*数据送入串口数据寄存器*///
			///*******************************************************///
			NVIC_EnableIRQ(First485_IRQn);					///*串口中断使能*///
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_RS485_2:
		{
			if(C_SmartMeter==C_Meter_Type)///*程序hex兼容根据表型判断
			{
				Enable_485_2_Transmit;	///*使485芯片工作于发送态：3光耦方式*///
				///*******************************************************///
	///			SFR_SECOND485->SR = USART_SR_RESET;
	///			SFR_SECOND485->CR1 |= USART_USART_EN;			///*Uart Enable*///
				///*******************************************************///
				Stop_Second485_Rx;								///*接收终止*///
				///*******************************************************///
				Start_Second485_Tx;								///*开始发送*///
				///*******************************************************///
				SFR_SECOND485->TXREG = TxdData;					///*数据送入串口数据寄存器*///
				///*******************************************************///
				NVIC_EnableIRQ(Second485_IRQn);					///*串口中断使能*///
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
				Stop_Infra_Rx;									///*接收终止*///
				///*******************************************************///
				///*******************************************************///
				SF_InfraModulatedSignalOutput();				///*PWM输出*///
				///*******************************************************///
				Start_Infra_Tx;									///*开始发送*///
				///*******************************************************///
				///*******************************************************///
				SFR_INFRA->TXREG = TxdData;						///*数据送入串口数据寄存器*///
				///*******************************************************///
				NVIC_EnableIRQ(Infra_IRQn);						///*串口中断使能*///
				///*******************************************************///
				break;
			}
//			else
//			{
//				///*******************************************************///
//				SFR_INFRA->SR = USART_SR_RESET;
//				SFR_INFRA->CR1 |= USART_USART_EN;				///*Uart Enable*///
//				///*******************************************************///
//				Stop_Infra_Rx;									///*接收终止*///
//				///*******************************************************///
//				///*******************************************************///
//				SF_InfraModulatedSignalOutput_Wakeup();			///*PWM输出*///
//				///*******************************************************///
//				Start_Infra_Tx;									///*开始发送*///
//				///*******************************************************///
//				///*******************************************************///
//				SFR_INFRA->TXREG = TxdData;						///*数据送入串口数据寄存器*///
//				///*******************************************************///
//				NVIC_EnableIRQ(Infra_IRQn);						///*串口中断使能*///
//				///*******************************************************///
//				break;
//			}
		}
		///*******************************************************///
		case C_Module:				///*模块与第2路RS485共用*///
		{
			if(C_SmartMeter!=C_Meter_Type)///*程序hex兼容根据表型判断,远程及卡表
			{
				///*******************************************************///
	//			SFR_SECOND485->SR = USART_SR_RESET;
	//			SFR_SECOND485->CR1 |= USART_USART_EN;			///*Uart Enable*///
				///*******************************************************///
	            if(ReportMode != C_ActiveReportFlag)
	            {
	                Stop_Modular_Rx;								///*接收终止*///
	            }
				///*******************************************************///
				Start_Modular_Tx;								///*开始发送*///
				///*******************************************************///
				SFR_MODULAR->TXREG = TxdData;					///*数据送入串口数据寄存器*///
				///*******************************************************///
				NVIC_EnableIRQ(Modular_IRQn);					///*串口中断使能*///
				///*******************************************************///
			}
			break;
		}
		///*******************************************************///
//		case C_ESAM:
//		{
//			///*******************************************************///
//			SFR_ESAMCOM->CR1 |= USART_TE_Set;				///*发送使能*///
//			//SFR_ESAMCOM->CR1 |= USART_TXEIE_EN_UART1;				///*发送中断使能*///
//			
//			SFR_ESAMCOM->CR1 &= USART_RE_DIS;				///*接收禁止*///
//			SFR_ESAMCOM->CR1 &= USART_REIE_Reset_UART1;			///*接收中断禁止*///
//			///*******************************************************///
//			SFR_ESAMCOM->DR = TxdData;						///*数据送入串口数据寄存器*///
//			///*******************************************************///
//			NVIC_EnableIRQ(Esam_IRQn);						///*串口中断使能*///
//			///*******************************************************///
//			break;
//		}
		///*******************************************************///
		case C_Card:
		{
			///*******************************************************///
//			SFR_CARDCOM->CR1 |= USART_TE_Set;				///*发送使能*///
//			//SFR_CARDCOM->CR1 |= USART_TXEIE_EN_UART1;				///*发送中断使能*///
//			
//			SFR_CARDCOM->CR1 &= USART_RE_DIS;				///*接收禁止*///
//			SFR_CARDCOM->CR1 &= USART_REIE_Reset_UART1;			///*接收中断禁止*///
//			///*******************************************************///
//			SFR_CARDCOM->DR = TxdData;						///*数据送入串口数据寄存器*///
			///*******************************************************///
//			NVIC_DisableIRQ(Card_IRQn);						///*串口中断使能*///
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
///*函数原型：void SF_CommUart_TxDisableForInterrupt(uchar8 CommNum)                            *///
///*入口参数：CommNum：通讯通道号。取值：取值：C_RS485_1、C_RS485_2、C_IR、C_Module、C_ESAM、C_Card。*///
///*输出参数：无                                                                                     *///
///*返回参数：C_Ok，C_Error（入口错误）                                                              *///
///*功能说明：关闭串口发送，包括发送中断使能                                                         *///
///*备    注：函数名中ForDispatch表示供主流程中调用，ForInterrupt表示供中断里调用。                  *///
///***************************************************************************************************///
void SF_CommUart_TxDisableForInterrupt(uchar8 CommNum)
{
//  ulong32 V_UsartDataBuff = 0;
	switch(CommNum)
	{
		case C_RS485_1:
		{
			///*******************************************************///
			Stop_First485_Tx;								///*终止发送*///
//			SFR_FIRST485->TXREG = V_UsartDataBuff;				///*清缓存*///
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_RS485_2:
		{
			///*******************************************************///
			Stop_Second485_Tx;								///*终止发送*///
//			SFR_SECOND485->TXREG = V_UsartDataBuff;			///*清缓存*///
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_IR:
		{
			SF_InfraModulatedSignalOff();				///*关闭红外调制信号*///
			///*******************************************************///
			Stop_Infra_Tx;								///*终止发送*///
//			SFR_INFRA->TXREG = V_UsartDataBuff;			///*清缓存*///
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_Module:			///*模块与第2路RS485共用*///
		{
			///*******************************************************///
			Stop_Modular_Tx;								///*终止发送*///
//			SFR_SECOND485->TXREG = V_UsartDataBuff;			///*清缓存*///
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
///*函数原型：uchar8 SF_CommUart_TxDisableForDispatch(uchar8 CommNum)                            *///
///*入口参数：CommNum：通讯通道号。取值：取值：C_RS485_1、C_RS485_2、C_IR、C_Module、C_ESAM、C_Card。*///
///*输出参数：无                                                                                     *///
///*返回参数：C_Ok，C_Error（入口错误）                                                              *///
///*功能说明：关闭串口发送，包括发送中断使能                                                         *///
///*备    注：函数名中ForDispatch表示供主流程中调用，ForInterrupt表示供中断里调用。                  *///
///***************************************************************************************************///
void SF_CommUart_TxDisableForDispatch(uchar8 CommNum)
{
//  ulong32 V_UsartDataBuff = 0;
	switch(CommNum)
	{
		case C_RS485_1:
		{
			///*******************************************************///
			Stop_First485_Tx;								///*终止发送*///
//			SFR_FIRST485->TXREG = V_UsartDataBuff;				///*清缓存*///
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_RS485_2:
		{
			///*******************************************************///
			Stop_Second485_Tx;								///*终止发送*///
//			SFR_SECOND485->TXREG = V_UsartDataBuff;			///*清缓存*///
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_IR:
		{
			SF_InfraModulatedSignalOff();				///*关闭红外调制信号*///
			///*******************************************************///
			Stop_Infra_Tx;								///*终止发送*///
//			SFR_INFRA->TXREG = V_UsartDataBuff;			///*清缓存*///
			///*******************************************************///
			break;
		}
		///*******************************************************///
		case C_Module:			///*模块与第2路RS485共用*///
		{
			///*******************************************************///
			Stop_Modular_Tx;								///*终止发送*///
//			SFR_SECOND485->TXREG = V_UsartDataBuff;			///*清缓存*///
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
///*Function：第1路RS485中断服务程序:接收/发送为同一个中断向量地址*///
///*Description：*///
///*Input：*///
///*Output：*///
///*Calls：*///
///*Called By：*///
///*Influence：*///
///*Tips：*///
///*Others：*///
///***********************************************************************************///
void First485_IRQHandler(void)
{
	uchar8 V_UsartDataBuff;								///*用于缓存接收/发送的一个字节*///
	
	SV_Overtime_485_1 = 0;			///*超时定时器清零*///
	
	if(UART->UARTIF & USART_FLAG_RXNE1)				///*判断是否接收中断*///
	{
		if( ( SFR_FIRST485->RXSTA & (USART_FLAG_FE | USART_FLAG_PE|USART_FLAG_ORE) ) == 0 )	///*判断是否有接收错误*///
		{
			V_UsartDataBuff = SFR_FIRST485->RXREG;			///*接收的数据读入缓存*///
			switch( INF_Comm_RecForInt(C_RS485_1,V_UsartDataBuff) )		//*将接收的1字节数据交通信模块处理，并得到返回值*///
			{
				case C_ContinueReceive:					///*继续接收*///
				{
					break;
				}
				///*******************************************************///
				case C_CorrectFrame:					///*收到正确帧*///
				{
					///*收到正确帧，需要关闭接收/发送功能，并发布解析消息*///
					InF_CommUart_RecDisableForInterrupt(C_RS485_1);
					///*发布解析消息*///
					///*因为中断里不能发消息，因此置解析标志，主流程中查该标志再发布解析消息*///
					SV_InterruptMsg_485_1 = C_Uart_Parse;
					break;
				}
				///*******************************************************///
				case C_AbortReceive:					///*退出接收*///
				{
					///*出错，初始化串口*///
					InF_CommUart_RecDisableForInterrupt(C_RS485_1);
					SV_InitUartMsg_485_1 = C_Uart_Init;
					break;
				}
				///*******************************************************///
				default:
					///*返回值不准确，同样初始化串口*///
					InF_CommUart_RecDisableForInterrupt(C_RS485_1);
					SV_InitUartMsg_485_1 = C_Uart_Init;
				break;
			}
		}
		else
		{
			///*接收错误，初始化串口*///
			InF_CommUart_RecDisableForInterrupt(C_RS485_1);
			SV_InitUartMsg_485_1 = C_Uart_Init;
		}
	}
	///*************************************************///
	else if(UART->UARTIF & USART_FLAG_TC1)			///*判断是否发送中断*///
	{
		switch( INF_Comm_TxdForInt(C_RS485_1,&V_UsartDataBuff) )
		{
			case C_ContinueTransmit:
				SFR_FIRST485->TXREG = V_UsartDataBuff;
			break;
			///*******************************************************///
			case C_AbortTransmit:
			///*发送完成，初始化串口*///
				SF_CommUart_TxDisableForInterrupt(C_RS485_1);
				InF_InitCommUartForInterrupt(C_RS485_1);
			break;
				///*******************************************************///
			case C_AbortTransmit_SetBPS:				///*修改波特率退出*///
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
		///*误进入中断，初始化串口*///
		SF_CommUart_TxDisableForInterrupt(C_RS485_1);
		InF_CommUart_RecDisableForInterrupt(C_RS485_1);
		SV_InitUartMsg_485_1 = C_Uart_Init;
	}
}

///***********************************************************************************///
///*Function：第2路RS485中断服务程序:接收/发送为同一个中断向量地址*///
///*Description：*///
///*Input：*///
///*Output：*///
///*Calls：*///
///*Called By：*///
///*Influence：*///
///*Tips：*///
///*Others：*///
///***********************************************************************************///
///#if	( C_PcbVersion == C_Pcb2457 )///*-M表
void Modular_IRQHandler(void)
{
	if(C_SmartMeter!=C_Meter_Type)///*程序hex兼容根据表型判断,远程及卡表
	{
		uchar8 V_UsartDataBuff;					///*用于缓存接收/发送的一个字节*///
		uchar8 V_ChanelNo;						///*通道号*////
		uchar8 *P_ChanelParse,*P_ChanelInit;	///*指向通道解析寄存器,通道初始化寄存器*///
	
	    uchar8 V_UReportDataBuf;                ///*用于主动上报的发送1个字节*///
	
		///*******************************************************///
		///*因为第2路485和模块共用串口,所以中断需要区分是哪种表型,将接收的数据传递给通信解析模块*///
	//	if(SV_MeterType != C_MeterType_Module)
	//	{
	//		V_ChanelNo = C_RS485_2;					///*赋值通道号*///
	//		P_ChanelParse = &SV_InterruptMsg_485_2;	///*指向解析标志寄存器地址*///
	//		P_ChanelInit = &SV_InitUartMsg_485_2;	///*指向初始化标志寄存器地址*///
	//	}
	//	else
	//	{
			V_ChanelNo = C_Module;
			P_ChanelParse = &SV_InterruptMsg_Modular;
			P_ChanelInit = &SV_InitUartMsg_Modular;
	//	}
		///*******************************************************///
		SV_Overtime_485_2 = 0;			///*超时定时器清零*///
		///*******************************************************///
	
	        ///*************************************************///
	    if((UART->UARTIF & USART_FLAG_RXNE0)||(UART->UARTIF & USART_FLAG_TC0))
	    {
		///*******************************************************///
	        if(UART->UARTIF & USART_FLAG_TC0)			///*判断是否发送中断*///
	        {
	            if(Inf_Comm_REPORTFlag() != C_ReportNULL)           ///*可能处于事件上报或者掉电上报*///
	            {
	//                Inf_Comm_InitModuleCommuniFlag();               ///*接收时，置标志，用于主动上报闭锁*///
	                switch( INF_Comm_TxdForInt_698Report(V_ChanelNo,&V_UReportDataBuf))
	                {
	                    case C_ContinueTransmit:
	                        SFR_MODULAR->TXREG = V_UReportDataBuf;
	                    break;
	                    ///*******************************************************///
	                    case C_AbortTransmit:
	                        ///*发送完成，初始化串口*///
	                        SF_CommUart_TxDisableForInterrupt(V_ChanelNo);
	                        //InF_InitCommUartForInterrupt(V_ChanelNo);
	                        Inf_Comm_REPORTFlagClear(C_ActiveReportEndFlag);         ///*主动上报标志清零*///
	                    break;
	                    ///*******************************************************///
	//                    case C_AbortTransmit_SetBPS:				///*修改波特率退出*///
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
	                        ///*发送完成，初始化串口*///
	                        SF_CommUart_TxDisableForInterrupt(V_ChanelNo);
	                        InF_InitCommUartForInterrupt(V_ChanelNo);
	                    break;
	                    ///*******************************************************///
	                    case C_AbortTransmit_SetBPS:				///*修改波特率退出*///
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
			if(UART->UARTIF & USART_FLAG_RXNE0)				///*判断是否接收中断*///
			{
		        V_UsartDataBuff = SFR_MODULAR->RXREG;			///*接收的数据读入缓存*///
		        if( ( SFR_MODULAR->RXSTA & (USART_FLAG_FE | USART_FLAG_PE|USART_FLAG_ORE) ) == 0 )	///*判断是否有接收错误*///
		        {
		            if(Inf_Comm_InitModuleCommuniFlag(C_CommuniSafeWorld1))    ///*通信接收*///
		            {
		                return;
		            }
					switch( INF_Comm_RecForInt(V_ChanelNo,V_UsartDataBuff) )		//*将接收的1字节数据交通信模块处理，并得到返回值*///
					{
						case C_ContinueReceive:					///*继续接收*///
						{
							break;
						}
						///*******************************************************///
						case C_CorrectFrame:					///*收到正确帧*///
						{
							///*收到正确帧，需要关闭接收/发送功能，并发布解析消息*///
							InF_CommUart_RecDisableForInterrupt(V_ChanelNo);
							///*发布解析消息*///
							///*因为中断里不能发消息，因此置解析标志，主流程中查该标志再发布解析消息*///
							*P_ChanelParse = C_Uart_Parse;
							break;
						}
						///*******************************************************///
						case C_AbortReceive:					///*退出接收*///
						{
							///*出错，初始化串口*///
							InF_CommUart_RecDisableForInterrupt(V_ChanelNo);
							*P_ChanelInit = C_Uart_Init;
							break;
						}
						///*******************************************************///
						default:
							///*返回值不准确，同样初始化串口*///
							InF_CommUart_RecDisableForInterrupt(V_ChanelNo);
							*P_ChanelInit = C_Uart_Init;
						break;
					}
				}
				else
				{
					///*接收错误，初始化串口*///
					InF_CommUart_RecDisableForInterrupt(V_ChanelNo);
					*P_ChanelInit = C_Uart_Init;
				}
			}
		}
		///*************************************************///
		else if(UART->UARTIF & USART_FLAG_TC0)			///*判断是否发送中断*///
		{
			switch( INF_Comm_TxdForInt(V_ChanelNo,&V_UsartDataBuff) )
			{
				case C_ContinueTransmit:
					SFR_MODULAR->TXREG = V_UsartDataBuff;
				break;
				///*******************************************************///
				case C_AbortTransmit:
					///*发送完成，初始化串口*///
					SF_CommUart_TxDisableForInterrupt(V_ChanelNo);
					InF_InitCommUartForInterrupt(V_ChanelNo);
				break;
				///*******************************************************///
				case C_AbortTransmit_SetBPS:				///*修改波特率退出*///
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
			///*误进入中断，初始化串口*///
			SF_CommUart_TxDisableForInterrupt(V_ChanelNo);
			InF_CommUart_RecDisableForInterrupt(V_ChanelNo);
			*P_ChanelInit = C_Uart_Init;
		}
	}
	else 
	{
		uchar8 V_UsartDataBuff;					///*用于缓存接收/发送的一个字节*///
		NVIC_DisableIRQ(Modular_IRQn);
		V_UsartDataBuff = SFR_MODULAR->RXREG;			///*接收的数据读入缓存*///
		UART->UARTIF =(USART_FLAG_TC0|USART_FLAG_RXNE0);		
	}
}
///*智能表
void Second485_IRQHandler(void)
{
	if(C_SmartMeter==C_Meter_Type)///*程序hex兼容根据表型判断，无用中断关闭
	{
		uchar8 V_UsartDataBuff;					///*用于缓存接收/发送的一个字节*///
		uchar8 V_ChanelNo;						///*通道号*////
		uchar8 *P_ChanelParse,*P_ChanelInit;	///*指向通道解析寄存器,通道初始化寄存器*///
		///*******************************************************///
		///*因为第2路485和模块共用串口,所以中断需要区分是哪种表型,将接收的数据传递给通信解析模块*///
	//	if(SV_MeterType != C_MeterType_Module)
	//	{
			V_ChanelNo = C_RS485_2;					///*赋值通道号*///
			P_ChanelParse = &SV_InterruptMsg_485_2;	///*指向解析标志寄存器地址*///
			P_ChanelInit = &SV_InitUartMsg_485_2;	///*指向初始化标志寄存器地址*///
	//	}
	//	else
	//	{
	//		V_ChanelNo = C_Module;
	//		P_ChanelParse = &SV_InterruptMsg_Modular;
	//		P_ChanelInit = &SV_InitUartMsg_Modular;
	//	}
		///*******************************************************///
		SV_Overtime_485_2 = 0;			///*超时定时器清零*///
		///*******************************************************///
		if(UART->UARTIF & USART_FLAG_RXNE5)				///*判断是否接收中断*///
		{
			if( ( SFR_SECOND485->RXSTA & (USART_FLAG_FE | USART_FLAG_PE|USART_FLAG_ORE) ) == 0 )	///*判断是否有接收错误*///
			{
				V_UsartDataBuff = SFR_SECOND485->RXREG;			///*接收的数据读入缓存*///
				switch( INF_Comm_RecForInt(V_ChanelNo,V_UsartDataBuff) )		//*将接收的1字节数据交通信模块处理，并得到返回值*///
				{
					case C_ContinueReceive:					///*继续接收*///
					{
						break;
					}
					///*******************************************************///
					case C_CorrectFrame:					///*收到正确帧*///
					{
						///*收到正确帧，需要关闭接收/发送功能，并发布解析消息*///
						InF_CommUart_RecDisableForInterrupt(V_ChanelNo);
						///*发布解析消息*///
						///*因为中断里不能发消息，因此置解析标志，主流程中查该标志再发布解析消息*///
						*P_ChanelParse = C_Uart_Parse;
						break;
					}
					///*******************************************************///
					case C_AbortReceive:					///*退出接收*///
					{
						///*出错，初始化串口*///
						InF_CommUart_RecDisableForInterrupt(V_ChanelNo);
						*P_ChanelInit = C_Uart_Init;
						break;
					}
					///*******************************************************///
					default:
						///*返回值不准确，同样初始化串口*///
						InF_CommUart_RecDisableForInterrupt(V_ChanelNo);
						*P_ChanelInit = C_Uart_Init;
					break;
				}
			}
			else
			{
				///*接收错误，初始化串口*///
				InF_CommUart_RecDisableForInterrupt(V_ChanelNo);
				*P_ChanelInit = C_Uart_Init;
			}
		}
		///*************************************************///
		else if(UART->UARTIF & USART_FLAG_TC5)			///*判断是否发送中断*///
		{
			switch( INF_Comm_TxdForInt(V_ChanelNo,&V_UsartDataBuff) )
			{
				case C_ContinueTransmit:
					SFR_SECOND485->TXREG = V_UsartDataBuff;
				break;
				///*******************************************************///
				case C_AbortTransmit:
					///*发送完成，初始化串口*///
					SF_CommUart_TxDisableForInterrupt(V_ChanelNo);
					InF_InitCommUartForInterrupt(V_ChanelNo);
				break;
				///*******************************************************///
				case C_AbortTransmit_SetBPS:				///*修改波特率退出*///
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
			///*误进入中断，初始化串口*///
			SF_CommUart_TxDisableForInterrupt(V_ChanelNo);
			InF_CommUart_RecDisableForInterrupt(V_ChanelNo);
			*P_ChanelInit = C_Uart_Init;
		}		
	}
	else 
	{
		uchar8 V_UsartDataBuff;					///*用于缓存接收/发送的一个字节*///
		NVIC_DisableIRQ(Second485_IRQn);		
		V_UsartDataBuff = SFR_SECOND485->RXREG;			///*接收的数据读入缓存*///
		UART->UARTIF =(USART_FLAG_TC5|USART_FLAG_RXNE5);
	}
}
/*******************************************************************************
函数原型：void SF_InfarWakeupTimer_Disable(void)
功能描述：低功耗下红外唤醒串口中断禁止
输入参数： 
输出参数：
返回参数： 
调用位置： 
备    注： 
*******************************************************************************/
void SF_InfarWakeupTimer_Disable(void)
{
	SFR_INFRA->RXSTA &= (~(USART_FLAG_FE | USART_FLAG_PE | USART_FLAG_ORE));
	NVIC_DisableIRQ(Infra_IRQn);			/*禁止中断*/

#if 0
	Disable_ComUart_Clock;                  /*关闭commUart时钟*/
#endif
    
	Disable_Infra_Clock;					/*系统时钟关闭*/
	
	IO_INFRARX->BSETH = INFRARX_SET;
	IO_INFRARX->MODER &=	INFRARX_IN_MODE;	
	IO_INFRARX->MODER |=	INFRARX_OUT_MODE;
	IO_INFRARX->OTYPER |= INFRARX_OUTPUT_OD;
	
	IO_INFRARX->BSETH = INFRARX_SET;	
}
///***********************************************************************************///
///*Function：红外串口中断服务程序:接收/发送为同一个中断向量地址*///
///*Description：*///
///*Input：*///
///*Output：*///
///*Calls：*///
///*Called By：*///
///*Influence：*///
///*Tips：*///
///*Others：*///
///***********************************************************************************///
void Infra_IRQHandler(void)
{
	uchar8 V_UsartDataBuff;								///*用于缓存接收/发送的一个字节*///

	SV_Overtime_Ir = 0;			///*超时定时器清零*///
	
	if((InF_ReadPowerState() == C_PowerOn)||(Str_LowPower_Infra.WakeupState == C_Enable))///*有电正常状态，或处于红外唤醒状态
	{
		if(UART->UARTIF & USART_FLAG_RXNE4)				///*判断是否接收中断*///
		{
			if( ( SFR_INFRA->RXSTA & (USART_FLAG_FE | USART_FLAG_PE|USART_FLAG_ORE) ) == 0)	///*判断是否有接收错误*///
			{
				V_UsartDataBuff = (uchar8)SFR_INFRA->RXREG;			///*接收的数据读入缓存*///
				switch( INF_Comm_RecForInt(C_IR,V_UsartDataBuff) )		//*将接收的1字节数据交通信模块处理，并得到返回值*///
				{
					case C_ContinueReceive:					///*继续接收*///
					{
						break;
					}
					///*******************************************************///
					case C_CorrectFrame:					///*收到正确帧*///
					{
						///*收到正确帧，需要关闭接收/发送功能，并发布解析消息*///
						InF_CommUart_RecDisableForInterrupt(C_IR);
						///*发布解析消息*///
						///*因为中断里不能发消息，因此置解析标志，主流程中查该标志再发布解析消息*///
						SV_InterruptMsg_Ir = C_Uart_Parse;
						break;
					}
					///*******************************************************///
					case C_AbortReceive:					///*退出接收*///
					{
						///*出错，初始化串口*///
						InF_CommUart_RecDisableForInterrupt(C_IR);
						SV_InitUartMsg_Ir = C_Uart_Init;
						break;
					}
					///*******************************************************///
					default:
						///*返回值不准确，同样初始化串口*///
						InF_CommUart_RecDisableForInterrupt(C_IR);
						SV_InitUartMsg_Ir = C_Uart_Init;
					break;
				}
			}
			else
			{
				///*接收错误，初始化串口*///
				InF_CommUart_RecDisableForInterrupt(C_IR);
				SV_InitUartMsg_Ir = C_Uart_Init;
			}
		}
		///*************************************************///
		else if(UART->UARTIF & USART_FLAG_TC4)			///*判断是否发送中断*///
		{
			if( INF_Comm_TxdForInt(C_IR,&V_UsartDataBuff) == C_ContinueTransmit )
			{
				SFR_INFRA->TXREG = V_UsartDataBuff;
			}
			else
			{
				///*发送完成，初始化串口*///
				SF_CommUart_TxDisableForInterrupt(C_IR);
				InF_InitCommUartForInterrupt(C_IR);
			}
			UART->UARTIF = USART_FLAG_TC4;
		}
		///*************************************************///
		else
		{
			///*误进入中断，初始化串口*///
			SF_CommUart_TxDisableForInterrupt(C_IR);
			InF_CommUart_RecDisableForInterrupt(C_IR);
			SV_InitUartMsg_Ir = C_Uart_Init;
		}
	}
	else  ///*低功耗，红外唤醒判断
	{
		if(UART->UARTIF & USART_FLAG_RXNE4)				///*判断是否接收中断*///
		{
			if( ( SFR_INFRA->RXSTA & (USART_FLAG_FE | USART_FLAG_PE|USART_FLAG_ORE) ) == 0)	///*判断是否有接收错误*///
			{
//				SwitchOn_BackLight();///*test
				SV_Wakeup_Flag = C_InfraWakeup_Flag;

				V_UsartDataBuff = (uchar8)SFR_INFRA->RXREG;			///*接收的数据读入缓存*///
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
			///*误进入中断，关闭串口*///
			SV_Wakeup_Flag = 0;
			SV_Wakeup_Data = 0;
			SF_InfarWakeupTimer_Disable();	
		}						
	}	
}

///***********************************************************************************///
///*Function：ESAM串口中断服务程序:接收/发送为同一个中断向量地址*///
///*Description：*///
///*Input：*///
///*Output：*///
///*Calls：*///
///*Called By：*///
///*Influence：*///
///*Tips：*///
///*Others：*///
///***********************************************************************************///
//void Esam_IRQHandler(void)
//{
//	
//}

///***********************************************************************************///
///*Function：从ESAM接收1个字节*///
///*Description：*///
///*Input：接收数据的地址指针*///
///*Output：将从ESAM接收到的数据放到输入的地址中*///
///*Return：C_OK：接收成功；C_Error：未能接收到，超时*///
///***********************************************************************************///
//uchar8 SF_RecOneByteFrom_Esam(uchar8 *P_Buff)
//{
//	ulong32 V_ulDelay = 0;
//	
//	while( (SFR_ESAMCOM->SR & USART_FLAG_RXNE) != USART_FLAG_RXNE )	///*等1字节接收完成*///
//	{
//		InF_Delay_2us();
//		V_ulDelay++;
//		if( V_ulDelay > C_Esam_9600ETU )							///*最多延时9600ETU*///
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
///*Function：向ESAM发送1个字节*///
///*Description：*///
///*Input：要发送的数据*///
///*Output：将从ESAM接收到的数据放到输入的地址中*///
///*Return：C_OK：发送成功；C_Error：重发3次仍不能成功*///
///***********************************************************************************///
//uchar8 SF_SendOneByteTo_Esam(uchar8 data)
//{
//	ulong32 V_ulDelay = 0;
//	
////	for(v_times=0;v_times<3;v_times++)
////	{
//		InF_CommUart_TxdDataForDispatch( C_ESAM,data );					///*发送序列数据*///
//		
//		while( (SFR_ESAMCOM->SR & USART_FLAG_TC) != USART_FLAG_TC )	///*等1字节发送完成*///
//		{
//			InF_Delay_2us();
//			V_ulDelay++;
//			if( V_ulDelay > (C_Esam_20ETU+C_Esam_20ETU) )				///*最多延时40ETU*///
//			{
//				return C_Error;
//			}
//		}
//		
////		if( !(SFR_ESAMCOM->SR & USART_FLAG_PE) )			///*无校验错误则直接退出*///
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
///*Function：从CARD接收1个字节*///
///*Description：*///
///*Input：接收数据的地址指针*///
///*Output：将从CARD接收到的数据放到输入的地址中*///
///*Return：C_OK：接收成功；C_Error：未能接收到，超时*///
///***********************************************************************************///
uchar8 SF_RecOneByteFrom_Card(uchar8 *P_Buff)
{
	ushort16 v_r_data = 0;		///*接收的数据*///
	uchar8 i,j,k,v_temp0,v_temp1,v_check;
	uchar8	buf[2];
	uchar8 v_delay;
	
	
	for(k=0;k<3;k++)
	{
		SF_CardBaudRateTimerInit( C_Init,C_4ms );			///*4ms开始计时:用于超时控制*///
		CardDataIO_R();			///*口线配置为接收*///
		v_delay = 0;
		
		//IO_BEEP->BSRR = BEEPSET;
		while( 1 )
		{
			if( !(IO_CARDDATA->IDR & CARDDATA_SELECT) )		///*只要检测到数据线为低，退出循环*///
			{
				SF_CardBaudRateTimerInit( C_Init,C_1_2_ETU );			///*延时1/2个ETU*///
	            //IO_BEEP->BSRR = BEEPSET;
				break;
			}
			if( CardBaudRateTimer->ETxIF & C_TimerStatus_OVIF_RESET )			///*9600ETU超时标志定时标志起来了*///
			{
				CardBaudRateTimer->ETxIF |= C_TimerStatus_OVIF_RESET;
				v_delay++;
				if( v_delay >=250 )						///*4ms*250=1s,约9600个ETU*///
				{
					SF_CardBaudRateTimerStop();						///*定时停止*///
					//IO_BEEP->BSRR = BEEPRESET;
					return( C_NoData );		///*返回超时*///
				}
			}
		}
		while( !(CardBaudRateTimer->ETxIF & C_TimerStatus_OVIF_RESET))
		{
			;
		}
		CardBaudRateTimer->ETxIF |= C_TimerStatus_OVIF_RESET;///*清中断标志
	//IO_BEEP->BSRR = BEEPRESET;
		
		v_check = 0;
		v_r_data = 0;
		for(i=0;i<9;i++)		///*连收9位数据位*///
		{
			SF_CardTimerDelay_N_ETU( 1 );		///*查询:延时1ETU到了没有，在这个函数中死等1ETU出来*///
			
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
			for(j=0;j<3;j++)		///*3取2*///
			{
				if( IO_CARDDATA->IDR & CARDDATA_SELECT )
				{
					v_temp1++;			///*口线为高的次数*///
				}
				else
				{
					v_temp0++;			///*口线为低的次数*///
				}
			}
			v_r_data>>=1;
			if( v_temp1 > v_temp0 )
			{
				v_r_data |= 0x0100;
				v_check++;
			}
		}
		
		//SF_CardBaudRateTimerInit( C_Init,C_1_Piont_5_ETU );			///*延时1.5个ETU,发ACK*///
		//
		//while( !(CardBaudRateTimer->SR & C_TIM_SR_UIF) )
		//{
		//	;
		//}
		SF_CardTimerDelay_N_ETU( 1 );
		if( v_check%2 == 0 )		///*奇偶校验对*///
		{
			//CardDataIO_T_1();					///*校验位正确,发送高*///
			//SF_CardBaudRateTimerInit( C_NotInit,C_1_Piont_5_ETU );		///*1.5ETU*///
			
			PF_Ushort16ToBuffer2(buf,&v_r_data);
			*P_Buff = buf[0];
			
			//while( !(CardBaudRateTimer->SR & C_TIM_SR_UIF) )
			//{
			//	;
			//}
			CardDataIO_R();			///*口线配置为接收:相当于发高,这样是为了节约时间,不漏掉下一个起始位*///
			SF_CardBaudRateTimerStop();
					//IO_BEEP->BSRR = BEEPRESET;
			return(C_OK);
		}
		else		///*奇偶校验错*///
		{
			CardDataIO_T_0();					///*校验位错误,发送低*///
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
///*Function：向CARD发送1个字节*///
///*Description：*///
///*Input：要发送的数据*///
///*Output：将从CARD接收到的数据放到输入的地址中*///
///*Return：C_OK：发送成功；C_Error：重发3次仍不能成功*///
///***********************************************************************************///
uchar8 SF_SendOneByteTo_Card(uchar8 data)
{
	ushort16 v_t_data,v_t_data_buf;
	uchar8 i,j,k,v_temp0,v_temp1;
	uchar8	buf[2];
	
	///*算校验*///
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
	///*至此，buf的低10位为要发送的数据,bit0是起始位*///
	
	
	for(k=0;k<3;k++)
	{
		SF_CardBaudRateTimerInit( C_Init,C_1_2_ETU );		///*1/2个ETU*///
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
		
		CardDataIO_R();		///*口线转接收*///
		
		SF_CardTimerDelay_N_ETU( 1 );
		///*至此，已11个ETU*///
		
		//SF_CardBaudRateTimerInit( C_NotInit,C_2_ETU );	///*起动2个ETU的延时*///
		
		v_temp0 = 0;
		v_temp1 = 0;
		for(j=0;j<3;j++)		///*3取2*///
		{
			if( IO_CARDDATA->IDR & CARDDATA_SELECT )
			{
				v_temp1++;			///*口线为高的次数*///
			}
			else
			{
				v_temp0++;			///*口线为低的次数*///
			}
		}
		SF_CardTimerDelay_N_ETU( 2 );
		
		SF_CardBaudRateTimerStop();
		///*至此，从起始位到这里，总共13ETU*///
		
		if( v_temp1 > v_temp0 )
		{
			return( C_OK );
		}
	}
	return( C_Error ); 
}
