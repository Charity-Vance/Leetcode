
///*****************************************************************************************///
///*Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     CardDrive.c
///*Version:       V1
///*Date:          2014-3-12
///*Description:   外部智能卡的驱动文件
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
#include "CardDrive.h"
#include "EsamDrive.h"
#include "uart.h"
#include "Timer.h"
///*软件模拟7816*///
///***********************************************************************************///
///*函数原型：卡电源控制					    									 *///
///***********************************************************************************///
void DF_Switch_CardPower(uchar8 Act)
{
	if(C_L_SmartMeter==C_Meter_Type)///*本地表与远程智能表口线冲突
	{
		switch( Act )
		{
			case C_On:	///*打开电源*///
			{
				SwitchOn_CardPower();
				break;
			}
			default:	///*关闭电源*///
			{
				SwitchOff_CardPower();
				break;
			}
		}		
	}
}
///***********************************************************************************///
///*函数原型：卡时钟控制					    									 *///
///***********************************************************************************///
void DF_Switch_CardSck(uchar8 Act)
{
	switch( Act )
	{
		case C_On:	///*供给时钟*///
		{
			SwitchOn_CardSck();
			break;
		}
		default:	///*切断时钟*///
		{
			SwitchOff_CardSck();
			break;
		}
	}
}
///***********************************************************************************///
///*函数原型：卡复位控制					    									 *///
///***********************************************************************************///
void DF_Switch_CardEn(uchar8 Act)
{
	if(C_L_SmartMeter==C_Meter_Type)///*本地表与远程智能表口线冲突
	{
		switch( Act )
		{
			case C_On:	///*卡使能*///
			{
				Card_EN();
				break;
			}
			default:	///*卡复位*///
			{
				Card_Reset();
				break;
			}
		}		
	}
}

///**************************************************************************************************///
///*Function：uchar8 SF_ReceiveDataFromCard(uchar8 *P_ucReceiveDataBuffer,uchar8 V_ucReceiveDataLen)*///
///*Description：从串口接收CARD发过来的数据															*///
///*Input：		P_ucReceiveDataBuffer接收数据缓存buffer首地址,V_ucReceiveDataLen需要接收数据的长度	*///
///*Output：	接收V_ucReceiveDataLen字节的数据写入P_ucReceiveDataBufferbuffer中					*///
///*Calls：		延时、CARD停活、写消息函数															*///
///*Called By：	CARD收发数据处理函数调用															*///
///*Influence：																						*///
///*Tips：																							*///
///*Others：																						*///
///**************************************************************************************************///
uchar8 SF_ReceiveDataFromCard(uchar8 *P_ucReceiveDataBuffer,uchar8 V_ucReceiveDataLen)
{
	uchar8 V_InteractionLen;
	uchar8 v_buff;
	
	CardDataIO_R();				///*数据线配置为接收*///
	
	V_InteractionLen = 0;
	while( V_InteractionLen < V_ucReceiveDataLen )
	{
		if( SF_RecOneByteFrom_Card(&v_buff) != C_OK )
		{
			return C_Error;
		}
		
		P_ucReceiveDataBuffer[V_InteractionLen] = v_buff;		///*取数据到缓冲区*///
		V_InteractionLen++;
	}
	
	return C_OK;
}


///**************************************************************************************///
///*Function：void SF_SendDataToCard(uchar8 *P_ucSendDataBuffer,uchar8 V_ucSendDataLen)	*///
///*Description：	从串口发送数据到CARD模块											*///
///*Input：	P_ucSendDataBuffer发送数据buffer首地址，V_ucSendDataLen发送数据长度			*///
///*Output：																			*///
///*Calls：																				*///
///*Called By：																			*///
///*Influence：																			*///
///*Tips：																				*///
///*Others：																			*///
///**************************************************************************************///
void SF_SendDataToCard(uchar8 *P_ucSendDataBuffer,uchar8 V_ucSendDataLen)
{
	uchar8 V_InteractionLen;
	CardDataIO_T_1();		///*数据线配置为发送,并发送高*///
	
	V_InteractionLen = 0;
	while( V_InteractionLen < V_ucSendDataLen )
	{
		SF_SendOneByteTo_Card(P_ucSendDataBuffer[V_InteractionLen]);
		V_InteractionLen ++;
	}
}
///************************************************************************///
///*函数原型：void CardIO_Init(void)
///*函数描述：卡初始化IO冲突，智能表本地表
///*输入参数：无
///*输出参数：无
///*返回参数：无
///*函数功能：
///*调用时机：
///*备注：
///************************************************************************///
void CardIO_Init(void)
{
	ulong32 i;
	if(C_L_SmartMeter==C_Meter_Type)
	{
		IO_CARDDATA->PUPDR &= CARDDATA_NOPUPD;
		IO_CARDDATA->OTYPER |= CARDDATA_OUTPUT_OD;
		IO_CARDDATA->BSETH = CARDDATASET;
		i = IO_CARDDATA->MODER;
		i &= CARDDATA_IN_MODE;
		i |= CARDDATA_OUT_MODE;
		IO_CARDDATA->MODER = i;
		IO_CARDDATA->BSETH = CARDDATASET;		
	}
}			
///************************************************************************///
///*函数原型：void InF_Deactivation_7816_Card(void)
///*函数描述：实现智能卡的停活
///*输入参数：无
///*输出参数：无
///*返回参数：无
///*函数功能：
///*调用时机：安全模块操作卡完成后调用
///*备注：
///************************************************************************///
void InF_Deactivation_7816_Card(void)
{
	///*复位->停时钟->拉低数据线->关闭电源*///
	DF_Switch_CardEn(C_Off);
	InF_Delay_2us();
	InF_Delay_2us();
	
	DF_Switch_CardSck(C_Off);
	InF_Delay_2us();
	InF_Delay_2us();
	
	CardIO_Init();
	InF_Delay_2us();
	InF_Delay_2us();
	
	DF_Switch_CardPower(C_Off);
	InF_Delay_2us();
	InF_Delay_2us();
}

///************************************************************************///
///*函数原型：uchar8 INF_WarmReset_7816_Card(uchar8 *P_CardNo)*///
///*函数描述：实现Card的热复位*///
///*输入参数：*P_CardNo:卡序列号存放地址*///
///*输出参数：CARD的序列号:卡先输出的数据存放在低地址，共8字节*///
///*返回参数：C_ok 复位正常;C_Error复位异常;*///
///*函数功能：MCU操作Card的Rst脚来实现对CARD的热复位*///
///*调用时机：*///
///*备注：*///
///************************************************************************///
uchar8 INF_WarmReset_7816_Card(uchar8 *P_CardNo)
{
	uchar8 p_temp[20];
	uchar8 v_temp;
	
	///*Card复位*///
	DF_Switch_CardEn(C_Off);
	///*延时约2个ETU:datasheet要求延时400时钟周期*///
	SF_CardBaudRateTimerInit(C_Init,C_1_2_ETU);		///*0.5个etu定时器配置*///
	SF_CardTimerDelay_N_ETU( 2 );
	
	///*Card使能*///
	DF_Switch_CardEn(C_On);
	
	///*串口接收使能*///
	//InF_CommUart_RecEnableForDispatch( C_Card );
	
	//__disable_irq();
    DisIRQ_ExceptETIM4();
	v_temp = SF_ReceiveDataFromCard(&p_temp[0],C_Esam_Len_ResetAck);				///*接收复位后的13字节*///
	//__enable_irq();
	EnIRQ_ExceptETIM4();
	PF_CopyDataBytes(&p_temp[5],P_CardNo,C_Len_SerialNumber);
	///*判断复位后的首5字节:3b 69 00 00 41/43：正确则CARD无故障*///
	//if( (p_temp[0] == C_FirstByte_ATR) && (p_temp[1] == C_SecondByte_ATR)
	//	&& (p_temp[2] == C_ThirdByte_ATR) && (p_temp[3] == C_FourthByte_ATR)
	//	&& ((p_temp[4] == C_FifthByte_ATR41) || (p_temp[4] == C_FifthByte_ATR43)))
	//{
	//	///*将卡的序列号传出*///
	//	PF_CopyDataBytes(&p_temp[5],P_CardNo,C_Len_SerialNumber);
	//	v_temp = C_OK;
	//}
	//else	///*不正确则CARD故障*///
	//{
	//	v_temp = C_Error;
	//}
	return v_temp;
}

///************************************************************************///
///*函数原型:uchar8 INF_ColdReset_7816_Card(uchar8 *P_CardNo)
///*函数描述：实现Card的冷复位*///
///*输入参数：*P_CardNo:卡序列号存放地址*///
///*输出参数：CARD的序列号:卡先输出的数据存放在低地址，共8字节*///
///*返回参数：C_OK：复位成功，C_Error：复位失败（异常插卡之类）*///
///*函数功能：*///
///*调用时机：主调度检测到插卡动作后，马上发消息给安全模块，安全模块调用本函数对卡进行冷复位*///
///*备    注：卡电源（包括卡时钟）平时关闭不工作，检测到插卡后对卡进行冷复位后，*///
///*		  卡电源/卡时钟使能，卡操作完成后需要停活（这样做是为了降低常态下电能表的EMI）*///
///************************************************************************///
uchar8 INF_ColdReset_7816_Card(uchar8 *P_CardNo)
{
	uchar8 V_ucBuffer[20];
	uchar8 v_return;
	
	
	///*将card停活*///
	InF_Deactivation_7816_Card();
	
	SF_CardBaudRateTimerInit(C_Init,C_1_2_ETU);		///*0.5个etu定时器配置*///
	///*延时约10ms:约100ETU*///
//	SwitchOn_TripLed();
	SF_CardTimerDelay_N_ETU( 100 );
//	SwitchOff_TripLed();
	///*打开电源*///
	DF_Switch_CardPower(C_On);
	///*延时约5ms：约48ETU*///
	SF_CardTimerDelay_N_ETU( 48 );

	///*card时钟使能*///
	DF_Switch_CardSck(C_On);
	

	///*延时约5ms：约48ETU*///
	SF_CardTimerDelay_N_ETU( 48 );
	//__disable_irq();
    DisIRQ_ExceptETIM4();
	///*card复位*///
	DF_Switch_CardEn(C_On); 
	
//	__disable_irq();
	v_return = SF_ReceiveDataFromCard(&V_ucBuffer[0],C_Esam_Len_ResetAck);				///*接收复位后的13字节*///
//	__enable_irq();
	EnIRQ_ExceptETIM4();
	if( v_return == C_OK )				///*读取成功，传出卡序列号*///
	{
		PF_CopyDataBytes(&V_ucBuffer[5],P_CardNo,C_Len_SerialNumber);
	}
	///*判断复位后的首5字节:3b 69 00 00 41/43：正确则CARD无故障*///
	//if( (V_ucBuffer[0] == C_FirstByte_ATR) && (V_ucBuffer[1] == C_SecondByte_ATR)
	//	&& (V_ucBuffer[2] == C_ThirdByte_ATR) && (V_ucBuffer[3] == C_FourthByte_ATR)
	//	&& ((V_ucBuffer[4] == C_FifthByte_ATR41) || (V_ucBuffer[4] == C_FifthByte_ATR43)))
	//{
	//	///*将card序列号传出*///
	//	///*将卡的序列号传出*///
	//	PF_CopyDataBytes(&V_ucBuffer[5],P_CardNo,C_Len_SerialNumber);
	//	v_return = C_OK;
	//}
	//else
	//{
	//	v_return = C_Error;
	//}
	return v_return;
}

///************************************************************************///
///*函数原型：ushort16 INF_SendData_7816_Card(uchar8*P_SendBuffer,uchar8 V _DataLen,uchar8 *pResponse,uchar8 *pMaxResponseLen)*///
///*函数功能：将安全模块传来的数据发送给card，返回card响应的数据和数据长度。*///
///*输入参数：P_SendBuffer：待发送数据的首地址；*///
///*		  V _DataLen：存放待发送数据长度;*///
///*		  pResponse ：存放响应数据的首地址*///
///*		  pMaxResponseLen：用于存放响应数据最大长度的地址（长度不包括SW1/SW2）*///
///*注1、	函数内部处理时，不直接对输入参数操作（不影响输入参数）*///
///*注2、	*P_SendBuffer 与*pResponse可以复用（指向同一个缓冲区）；当复用时，两个指针应相等。*///
///*输出参数：卡响应数据:卡先输出的数据存放在低地址，数据不包括SW1/SW2*///
///*		  卡响应数据的长度：长度不包括SW1/SW2*///
///*返回参数：返回值为卡的SW1/SW2（SW1为高字节）；如果操作卡异常，则C_Security_Err表示数据异常、*///
///*		        为C_Security_MaxLenErr表示最大长度错误*///
///*备    注：从卡读取数据，边读边将数据放入到pResponse区。*///
///*宏定义列表：*///
///************************************************************************///
ushort16 INF_SendData_7816_Card(uchar8 *P_SendBuffer,uchar8 V_DataLen,uchar8 *pResponse,uchar8 *pMaxResponseLen)
{
	uchar8 *P_SendBuffer_temp,*pResponse_temp;
	uchar8 V_ucBuffer[5];
	uchar8 V_TxDataLen,V_ResponseDataLen,Buff;
	ushort16 v_temp;
	
	P_SendBuffer_temp = P_SendBuffer;
	pResponse_temp = pResponse;
	
	///**********************************///
	///*配置串口*///
//	InF_InitCommUartForDispatch(C_Card,C_bps_2400,C_CommDataLen8,C_SerStp_2,C_parity_Even);

	InF_Delay_us(3000);
	///*取要发送的长度*///
	V_TxDataLen = V_DataLen;
	///************************************************************************///
	///*输入的要发送的长度、从CARD接收长度判断*///
	if( V_TxDataLen < C_Len_APDU_5 )
	{
		return C_Security_MaxLenErr;
	}
	else if( V_TxDataLen == C_Len_APDU_5 )				///*发5字节，情况1与情况2的应答字节数一样处理*///
	{
		V_ResponseDataLen = P_SendBuffer_temp[C_Len_APDU_5-1] + C_Len_APDU_2;	///*情况1、情况2*///
	}
	else												///*发超过5字节*///
	{
		if( V_TxDataLen == (P_SendBuffer_temp[C_Len_APDU_5-1] +5) )
		{
			V_ResponseDataLen = C_Len_APDU_2;			///*情况3*///
		}
		else if( V_TxDataLen == (P_SendBuffer_temp[C_Len_APDU_5-1] +6) )
		{
			V_ResponseDataLen = P_SendBuffer_temp[C_Len_APDU_5-1]+2;	///*情况4*///
		}
		else
		{
			return C_Security_MaxLenErr;
		}
	}
	///************************************************************************///
	if( (V_ResponseDataLen - 2) > *pMaxResponseLen )
	{
		return C_Security_MaxLenErr;
	}
	///**********************************///
	
	//__disable_irq();
	DisIRQ_ExceptETIM4();
	///*发5字节的命令头给CARD*///
	SF_SendDataToCard(P_SendBuffer_temp,C_Len_APDU_5);
	
	InF_SysTickDelay_1s();				///*将SysTick配置为1s溢出*///
	while(1)
	{
		if( SF_ReceiveDataFromCard(&V_ucBuffer[0],1) != C_OK )	///*收一个字节*///
		{
			//__enable_irq();
            EnIRQ_ExceptETIM4();
			return C_Security_OverTime;
		}
		
		if( V_ucBuffer[0] == 0x60 )	///*卡应答60，代表卡请求延时*///
		{
			if( InF_JudgeDelay_1s() == C_Error )	///*判断9600ETU超时是否到:1s*///
			{
				//__enable_irq();
                EnIRQ_ExceptETIM4();
				return C_Security_OverTime;
			}
		}
		else				///*卡应答的数据不是60，退出循环*///
		{
			break;
		}
	}
	
	if( V_ucBuffer[0] != P_SendBuffer[1] )	///*非60且非INS,则再判断是否为SW1/SW2*///
	{	///*不是INS，则收到的是SW1，再接收1个数据：SW2*///
		if( ((V_ucBuffer[0]&0xf0)==0x60) || ((V_ucBuffer[0]&0xf0)==0x90) )
		{
			if( SF_ReceiveDataFromCard(&V_ucBuffer[1],1) != C_OK )
			{
				v_temp = C_Security_OverTime;
			}
			else
			{
				///*SW1、SW2*///
				v_temp = V_ucBuffer[0];
				v_temp <<= 8;
				v_temp |= (ushort16)V_ucBuffer[1];
			}
		}
		else
		{
			v_temp = C_Security_Err;
		}
	}
	else
	{
		if( (V_DataLen-C_Len_APDU_5) > 0)				///*判断是否还需要发剩余字节*///
		{
			SF_CardBaudRateTimerInit(C_Init,C_16_ETU);	///*延时16个ETU*///
			while( !(CardBaudRateTimer->ETxIF & C_TimerStatus_OVIF_RESET))
			{
				;
			}
			SF_CardBaudRateTimerStop();
			
			SF_SendDataToCard(&P_SendBuffer_temp[C_Len_APDU_5],V_DataLen-C_Len_APDU_5);	///*发送剩余数据*///
		}
		
		////if( SF_ReceiveDataFromEsam(&pResponse_temp[0],V_ResponseDataLen) != C_OK )	///*接收ESAM返回的数据*///
		Buff = SF_ReceiveDataFromCard(&pResponse_temp[0],V_ResponseDataLen-C_Len_APDU_2);
		if( Buff != C_OK )
		{
			v_temp = C_Security_OverTime;
		}
		else
		{
			if( SF_ReceiveDataFromCard(&V_ucBuffer[0],C_Len_APDU_2) != C_OK )
			{
				v_temp = C_Security_OverTime;
			}
			else
			{
				*pMaxResponseLen = V_ResponseDataLen-C_Len_APDU_2;		///*输出参数中的长度*///

				///*判断SW1、SW2*///
				v_temp = V_ucBuffer[0];
				v_temp <<= 8;
				v_temp |= (ushort16)V_ucBuffer[1];
			}
		}
	}
	
	//__enable_irq();
    EnIRQ_ExceptETIM4();
	return v_temp;
}
///****************************************************************************///
///*函数原型 	Card_InitBackUpBaseTimer
///*函数功能	单个关闭各中断，代替关闭总中断
///*输入参数	无
///*输出参数 	无
///*返回参数	无
///*全局变量 	无
///*函数备注	
///****************************************************************************///
void DisIRQ_ExceptETIM4(void)
{
  NVIC_DisableIRQ(LPTIM_IRQn);
  NVIC_DisableIRQ(ETIM1_IRQn);
  NVIC_DisableIRQ(ETIM2_IRQn);
  }
///****************************************************************************///
///*函数原型 	EnIRQ_ExceptETIM4
///*函数功能	单个打开各中断，代替打开总中断
///*输入参数	无
///*输出参数 	无
///*返回参数	无
///*全局变量 	无
///*函数备注	
///****************************************************************************///
void EnIRQ_ExceptETIM4(void)
{
  NVIC_EnableIRQ(LPTIM_IRQn);
  NVIC_EnableIRQ(ETIM1_IRQn);
  NVIC_EnableIRQ(ETIM2_IRQn);
}







