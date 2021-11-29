
///*****************************************************************************************///
///*Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     EsamDrive.c
///*Version:       V1
///*Date:          2014-3-12
///*Description:   Esam芯片的驱动文件
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
#include "EsamDrive.h"
#include "SPI.h"
#include "Dispatch.h"

ulong32	SV_ulTemp_Esam;	///*该变量用于所有寄存器的读->修改->写*///

extern void SF_Execute_EsamErr(uchar8 P_Buff);


///**************************************************************************************************///
///*Function：uchar8 SF_ReceiveDataFromEsam(uchar8 *P_ucReceiveDataBuffer,ushort16 V_ucReceiveDataLen)*///
///*Description：从串口接收ESAM发过来的数据															*///
///*Input：		P_ucReceiveDataBuffer接收数据缓存buffer首地址,V_ucReceiveDataLen需要接收数据的长度	*///
///*Output：	接收V_ucReceiveDataLen字节的数据写入P_ucReceiveDataBufferbuffer中					*///
///*Calls：		延时、ESAM停活、写消息函数															*///
///*Called By：	ESAM收发数据处理函数调用															*///
///*Influence：																						*///
///*Tips：																							*///
///*Others：																						*///
///**************************************************************************************************///
uchar8 SF_ReceiveDataFromEsam(uchar8 *P_ucReceiveDataBuffer,ushort16 V_ucReceiveDataLen)
{
	ushort16 V_InteractionLen;
	uchar8 v_buff;

	V_InteractionLen = 0;
	while( V_InteractionLen < V_ucReceiveDataLen )
	{
		if( SF_RecOneByteFrom_Esam(&v_buff) != C_OK )
		{
			return C_Error;
		}

		P_ucReceiveDataBuffer[V_InteractionLen] = v_buff;		///*取数据到缓冲区*///
		V_InteractionLen++;
	}

	return C_OK;
}


///**************************************************************************************///
///*Function：void SF_SendDataToEsam(uchar8 *P_ucSendDataBuffer,ushort16 V_ucSendDataLen)	*///
///*Description：	从串口发送数据到ESAM模块											*///
///*Input：	P_ucSendDataBuffer发送数据buffer首地址，V_ucSendDataLen发送数据长度			*///
///*Output：																			*///
///*Calls：																				*///
///*Called By：																			*///
///*Influence：																			*///
///*Tips：																				*///
///*Others：																			*///
///**************************************************************************************///
void SF_SendDataToEsam(uchar8 *P_ucSendDataBuffer,ushort16 V_ucSendDataLen)
{
	ushort16 V_InteractionLen;

	V_InteractionLen = 0;
	while( V_InteractionLen < V_ucSendDataLen )
	{
		if(SF_SendOneByteTo_Esam(P_ucSendDataBuffer[V_InteractionLen])!=C_OK)
		{
			return;
		}
		V_InteractionLen++;
	}
}

///************************************************************************///
///*函数原型：void InF_Deactivation_7816_Esam(void)
///*函数描述：实现ESAM的停活
///*输入参数：无
///*输出参数：无
///*返回参数：无
///*函数功能：
///*调用时机：
///*备注：
///************************************************************************///
void InF_Deactivation_7816_Esam(void)
{
	///*复位->停时钟->拉低数据线->关闭电源*///
//	Esam_Reset();
//	InF_Delay_2us();
//	InF_Delay_2us();
//
//	EsamClock_Output_DIS();
//	InF_Delay_2us();
//	InF_Delay_2us();
//
//	EsamIO_Init();
//	InF_Delay_2us();
//	InF_Delay_2us();
	InF_DeadESAM_SPI_Initial();
	InF_Delay_2us();
	InF_Delay_2us();
	SwitchOff_EsamPower();
	InF_Delay_2us();
	InF_Delay_2us();

//	InF_EsamChipSelect();	/* 经过测试,CS口线会有漏电流到ESAM电源,所以将CS口线拉低 */
}

///************************************************************************///
///*函数原型：uchar8  INF_WarmRest_7816_Esam(void)
///*函数描述：实现ESAM的热复位
///*输入参数：无
///*输出参数：ESAM的序列号
///*返回参数：C_ok 复位正常;C_Error复位异常;
///*函数功能：MCU操做ESAM的Rst脚来实现对ESAM的热复位
///*调用时机：
///*备注：
///************************************************************************///
uchar8  INF_WarmRest_7816_Esam(void)///
{
	return C_OK;
//	ushort16 i;
////	uchar8 p_temp[20];
//	uchar8 v_temp;
////	ulong32 V_Delay;
//
//	///*配置串口*///
////	InF_InitCommUartForDispatch(C_ESAM,C_bps_2400,C_CommDataLen8,C_SerStp_2,C_parity_Even);
//	DF_SPI_Configuration();
//
//	///*时钟输出使能*///
////	EsamClock_Output_EN();
//
//	///*Esam复位*///
////	Esam_Reset();
//	///*延时约200us*///
//	for(i=0;i<100;i++)
//	{
//		InF_Delay_2us();
//	}
//
////	InF_EsamChipSelect();///*使能SPI片选信号，内部带延时
//
//	///*Esam使能*///
////	Esam_EN();
//
//	///*串口接收使能*///
////	InF_CommUart_RecEnableForDispatch( C_ESAM );
//
////	v_temp = SF_ReceiveDataFromEsam(&p_temp[0],C_Esam_Len_ResetAck);				///*接收复位后的13字节*///
//
////	EsamClock_Output_DIS();
//	///*判断复位后的首5字节:3b 69 00 00 41/43：正确则Esam无故障*///
////	if( (p_temp[0] == C_FirstByte_ATR) && (p_temp[1] == C_SecondByte_ATR)
////		&& (p_temp[2] == C_ThirdByte_ATR) && (p_temp[3] == C_FourthByte_ATR) )
////	//	&& ((p_temp[4] == C_FifthByte_ATR41) || (p_temp[4] == C_FifthByte_ATR43)))
////	{
//		v_temp = C_OK;
////	}
////	else	///*不正确则Esam故障*///
////	{
////		v_temp = C_Error;
////	}
//
////	SF_Execute_EsamErr( v_temp );
//
////	///延时Tcsd 6us
////	for( V_Delay=0;V_Delay<C_Esam_Tcsd6us;V_Delay++)
////	{
////		InF_Delay_2us();
////	}
////	//dis CS
////	InF_EsamChipDeselect();///*内部带延时	TCSH
//
//	return v_temp;
}
ushort16 INF_SendData_7816_Esam(uchar8*P_SendBuffer,uchar8 V_Datalen,uchar8 *pResponse,uchar8 *pMaxResponseLen)
{
    return C_OK;
}

///************************************************************************///
///*函数原型:void SF_ColdReset_7816_Esam_No(void)
///*函数功能:ESAM上电复位消息函数:冷复位
///*输入参数:无
///*输出参数:ESAM复位后的13字节应答
///*返回参数:C_OK 复位成功;C_Error复位失败
///*调用时机：
///*备注:
///************************************************************************///
void SF_ColdReset_7816_Esam_No(void)///测试ESAM不读取序列号输出
{
	///*将ESAM停活*///
	InF_Deactivation_7816_Esam();
	///*延时约5ms，VESAM 0.8V，20ms，0.5V；30ms，0.3V，45ms，0.2V*///
	InF_Delay_us(30000);///*延时30ms
	///*打开电源*///
	SwitchOn_EsamPower();
	///*延时约2ms*///
	InF_Delay_us(2000);
	InF_EsamChipDeselect();		/* 取消片选 */
	///*延时约2ms，注意延时*///
	InF_Delay_us(2000);
	DF_SPI_Configuration();///*重新配置SPI
	InF_Delay_us(100000);///*延时100ms
}
///************************************************************************///
///*函数原型:void SF_ColdReset_7816_Esam_PowerNo(void)
///*函数功能:ESAM上电复位消息函数:冷复位
///*输入参数:无
///*输出参数:ESAM复位后的13字节应答
///*返回参数:C_OK 复位成功;C_Error复位失败
///*调用时机：
///*备注:ESAM再次上电操作，延时30ms
///************************************************************************///
void SF_ColdReset_7816_Esam_PowerNo(void)///测试ESAM不读取序列号输出
{
	///*打开电源*///
	SwitchOn_EsamPower();
	///*延时约2ms*///
	InF_Delay_us(2000);
	InF_EsamChipDeselect();		/* 取消片选 */
	///*延时约2ms，注意延时*///
	InF_Delay_us(2000);
	DF_SPI_Configuration();///*重新配置SPI
	InF_Delay_us(30000);///*延时30ms
}
///***********************************************************************************************///
///*函数原型:ushort16 INF_SendData_7816_Esam(uchar8*P_SendBuffer,ushort16 V_Datalen,uchar8 *pResponse,ushort16 *pMaxResponseLen)
///*函数描述：此函数用于与ESAM交互数据
///*输入参数：
///* P_SendBuffer:待发送数据的首地址(不包括55及LRC1);
///* V _DataLen:存放待发送数据长度
///* pResponse:存放响应数据的首地址，存放ESAM先返回的数据
///* pMaxResponseLen:作为输入参数表示输入缓存的数据长度，作为输出参数时，存放响应数据长度：长度不包括SW1、SW2
///*P_SendBuffer与pResponse可以相等，并且SW1、SW2不作为Response数据
///*输出参数:ESAM响应的数据及长度，其中SW1、SW2在此函数内部的临时缓冲区中，不输出
///*返回参数:61xx数据交互正常;C_Security_Err数据交换异常;MaxResponseLen_ERR 最大长度不够,SW1/SW2(SW1为高字节)
///*函数功能:将主调函数传来的数据发送给ESAM，并返回ESAM响应的数据和数据长度.内部判断数据长度、55接收标志及校验数据判断
///************************************************************************///
ushort16 INF_SendData_698_Esam(uchar8*P_SendBuffer,ushort16 V_Datalen,uchar8 *pResponse,ushort16 *pMaxResponseLen)
{
	uchar8 *P_SendBuffer_temp,*pResponse_temp,V_ucBuffer_T[20];

	uchar8 V_ucBuffer[5],V_RetryTime,V_LRC1,V_LRC2,V_SendSign,V_ucRxBufHead[4];

	ushort16 V_TxDataLen,V_ResponseDataLen,V_i,V_j;

	ulong32 V_Delay,V_ulDelay;
	ulong32 SV_ulTemp_ESAM;

	ushort16 v_temp,V_usDataEncode,V_len;

	P_SendBuffer_temp = P_SendBuffer;
	pResponse_temp = pResponse;

	SV_ulTemp_ESAM=IO_ESAMPOWER->ODR;
	if((SV_ulTemp_ESAM&ESAMPOWERSET)==ESAMPOWERSET)///*电源打开低有效
	{
		SF_ColdReset_7816_Esam_PowerNo();
	}
	else
	{
		SV_ulTemp_ESAM=IO_ESAMPOWER->MODER;
		if((SV_ulTemp_ESAM&ESAMPOWER_ANOLOG)!=ESAMPOWER_OUT_MODE)
		{
			SF_ColdReset_7816_Esam_PowerNo();
		}
		else
		{
			SV_ulTemp_ESAM=IO_ESAMPOWER->OTYPER;
			if(SV_ulTemp_ESAM&ESAMPOWER_OUTPUT_OD)
			{
				SF_ColdReset_7816_Esam_PowerNo();
			}
			else
			{
				DF_SPI_Configuration();
			}
		}
	}
	///**********************************///
	///*配置串口*///
//	InF_InitCommUartForDispatch(C_ESAM,C_bps_2400,C_CommDataLen8,C_SerStp_2,C_parity_Even);
//	DF_SPI_Configuration();
	///*取要发送的长度*///
	V_TxDataLen = V_Datalen;
	///************************************************************************///
	///*输入的要发送的长度、从ESAM接收长度判断*///
	if( V_TxDataLen < C_Len_APDU_4 )
	{
		return C_Security_MaxLenErr;
	}
//	else///*发送数据长度判断，软件比对特殊
//		{
//			V_ucBuffer[0]=P_SendBuffer_temp[C_Esam_DataOff5_Len2];
//			V_ucBuffer[1]=P_SendBuffer_temp[C_Esam_DataOff4_Len1];
//
//			PF_Buffer2ToUshort16(&V_ucBuffer[0],&V_TxDataLen);
//			V_TxDataLen+=(C_Len_APDU_4+2);
//			if(V_TxDataLen!=V_Datalen)
//			{
//				return C_Security_MaxLenErr;
//			}
//		}
	if(*pMaxResponseLen< C_Len_APDU_4)
	{
		return C_Security_MaxLenErr;
	}
	///*延时约200us*///
	for(V_Delay=0;V_Delay<100;V_Delay++)
	{
		InF_Delay_2us();
	}
	///**************组织发送数据*************************///
	V_SendSign=C_Esam_TxRxSign55;

	V_LRC1=P_SendBuffer_temp[0];
	for(V_i=1;V_i<V_TxDataLen;V_i++)///*增加校验数据
	{
		V_LRC1=V_LRC1^P_SendBuffer_temp[V_i];
	}
	V_LRC1 = ~V_LRC1;

//	__disable_irq();

	if( Str_ESAM_Status.HStatus != C_OK )
	{
		V_len = CLMeter_Work_State1;
		InF_Read_Data(CMeter_Work_State1,&V_ucBuffer_T[0],&V_len,&V_usDataEncode);
		if(V_ucBuffer_T[1] & C_ESAMERR_MeterWorkState)
		{
			//InF_Deactivation_7816_Esam();
			SF_ColdReset_7816_Esam_No();
		}
	}
	///*****************数据发送、接收*****************///
	for(V_RetryTime=0;V_RetryTime<C_Esam_RetryTime;V_RetryTime++)///*数据异常重发
	{///**************数据发送
		//CS
		InF_EsamChipSelect();///*内部带延时，实测延时68us要求50@100us 典型值60，Tcsl

		///*发1字节的55给ESAM*///
		SF_SendDataToEsam(&V_SendSign,1);
		///*发数据ESAM*///
		SF_SendDataToEsam(&P_SendBuffer_temp[0],V_TxDataLen);		///*字符有效传输时间6.8us，最大8.6us，要求1.5@10us
		///*发LRC给ESAM*///
		SF_SendDataToEsam(&V_LRC1,1);
		///延时Tcsd 6us，实测6.8us要求3@10  实测10.44（原C_Esam_Tcsd6us为4） ，典型值5us
		for( V_Delay=0;V_Delay<C_Esam_Tcsd6us;V_Delay++)
		{
			InF_Delay_2us();
		}
		//dis CS
		InF_EsamChipDeselect();///*内部带延时	TCSH	实测31.2us要求10@50，典型值10us
///***********数据接收
		for(V_i=0;V_i<2;V_i++)///*校验和异常目前循环接收2次判断
		{
			//CS
			InF_EsamChipSelect();///*内部带延时		TCSL		要求值50@100,实测值63.1，典型值60us
			//*55标志位
			V_ulDelay=0;
			SF_ReceiveDataFromEsam(&V_ucBuffer[0],1);
			while(V_ucBuffer[0]!=C_Esam_TxRxSign55)
			{///延时Tq 37.1us		15@100，典型值20us
				for( V_Delay=0;V_Delay<C_Esam_Tq20us;V_Delay++)
				{
					InF_Delay_2us();
					V_ulDelay++;
				}
				if( V_ulDelay > C_Esam_1S )							///*最多延时1s*///
				{
					uchar8 v_buffTemp[CLESAM_FaultState];
					ushort16 V_DatalenTemp;
					V_DatalenTemp=CLESAM_FaultState;
					InF_Read_Data(CESAM_FaultState,&v_buffTemp[0],&V_DatalenTemp,&V_usDataEncode);
					if(C_Esam_ERR!=v_buffTemp[0])///*ESAM故障
					{
					V_ucBuffer[0] = Pt_ResetEsam;			///*发送复位消息给ESAM模块*///
					Dispatch_SendMessage(C_Msg_Esam,V_ucBuffer,Pt_ResetEsam_Len+1);
					}
					///*ESAM出错处理*///
					SF_Execute_EsamErr( C_Error );
//					__enable_irq();
					return C_Security_OverTime;
				}
				SF_ReceiveDataFromEsam(&V_ucBuffer[0],1);
			}
			//*接收4个字节 SW1 SW2 Len1 Len2
			if(SF_ReceiveDataFromEsam(V_ucRxBufHead,C_Len_APDU_4)==C_OK)
			{
                V_ucBuffer[0]=V_ucRxBufHead[3];
				V_ucBuffer[1]=V_ucRxBufHead[2];

				PF_Buffer2ToUshort16(&V_ucBuffer[0],&V_ResponseDataLen);
				if(V_ResponseDataLen>*pMaxResponseLen)///*安全判断
				{
//					__enable_irq();
					return C_Security_MaxLenErr;
				}
				///*接收剩余数据
// 				for( V_Delay=0;V_Delay<100;V_Delay++)
//				{
//					InF_Delay_2us();
//				}
				if(V_ResponseDataLen<C_Len_Esam_Max)///*接收数据长度增加判断，防止数据长度异常
				{
					SF_ReceiveDataFromEsam(&pResponse_temp[0],V_ResponseDataLen);
					SF_ReceiveDataFromEsam(&V_ucBuffer[0],1);	///LRC2		分开读防止pResponse_temp	缓存覆盖
//					V_ucBuffer[0] = pResponse_temp[V_ResponseDataLen];
		            ///延时Tcsd 6us
					for( V_Delay=0;V_Delay<C_Esam_Tcsd6us;V_Delay++)
					{
						InF_Delay_2us();
					}
					//dis CS
					InF_EsamChipDeselect();///*内部带延时	TCSH
					//LRC2 判断
					V_LRC2 = V_ucRxBufHead[0];
					V_LRC2 ^= V_ucRxBufHead[1];
					V_LRC2 ^= V_ucRxBufHead[2];
					V_LRC2 ^= V_ucRxBufHead[3];

					for(V_j=0;V_j<V_ResponseDataLen;V_j++)///*增加校验数据
					{
						V_LRC2=V_LRC2^pResponse_temp[V_j];
					}
					V_LRC2 = ~V_LRC2;
					if(V_LRC2==V_ucBuffer[0])
					{
						*pMaxResponseLen=V_ResponseDataLen;
						break;
					}
				}
				else
				{
					//dis CS
					InF_EsamChipDeselect();///*内部带延时	TCSH
				}
			}
			else///接收数据异常
			{
				//dis CS
				InF_EsamChipDeselect();///*内部带延时	TCSH
			}
		}
		///*****判断SW是否为6A90,ESAM LRC校验错误,如是则错误重发
		if((V_ucRxBufHead[0]!=0x6A)&&(V_ucRxBufHead[1]!=0x90))
		{
			break;
		}
	}
///*接收数据处理
	v_temp = V_ucRxBufHead[0];
	v_temp <<= 8;
	v_temp |= (ushort16)V_ucRxBufHead[1];
//	if(C_Security_CommandOk==v_temp)///*SW为9000
//	{
		if(V_i<2)///*接收ESAM数据，LRC校验正常
		{
			//P_Buff=C_OK;	///*ESAM正常*///
		}
		else
		{
			//P_Buff=C_Error;	///*ESAM出错*///
			v_temp=C_Security_Err;
		}
//	}
//	else///*SW非9000
//	{
//		P_Buff = C_Error;	///*ESAM出错*///
//	}
//	if(P_Buff==C_Error)///*ESAM出错*///
//	{
//			V_ucBuffer[0] = Pt_ResetEsam;			///*发送复位消息给ESAM模块*///
//			Dispatch_SendMessage(C_Msg_Esam,V_ucBuffer,Pt_ResetEsam_Len+1);
//	}
//	__enable_irq();
	if( Str_ESAM_Status.HStatus != C_OK )
	{
		SF_Execute_EsamErr( C_OK );
	}

//	EsamClock_Output_DIS();
//	__enable_irq();
	return v_temp;
}

///************************************************************************///
///*函数原型:void InF_InitEsamPowerOn(void)
///*函数功能:ESAM上电复位消息函数:冷复位
///*输入参数:P_Msg_Parameter: 统一的Str_Msg_Parameter型变量
///*消息来源:SourceAddr= C_Msg_Dispatch,，调度
///*目的消息:DerictAddr = C_Msg_Esam;Len = 0
///*输出参数：Esam序列号
///*返回参数:C_ok 复位成功;C_Error复位失败
///*调用时机：调度上电初始化ESAM时
///*备注:
///************************************************************************///
void InF_InitEsamPowerOn(void)
{

	uchar8 V_ucBuffer[5];
	ushort16 V_len,V_usDataEncode;
	///*从数据层读出历史状态*///
	V_len = CLESAM_FaultState;
	if( InF_Read_Data(CESAM_FaultState,&Str_ESAM_Status.HStatus,&V_len,&V_usDataEncode) != C_OK )
	{
		Str_ESAM_Status.HStatus = C_Esam_OK;
	}
	///************************************************************************///
	InF_Deactivation_7816_Esam();			///*ESAM停活*///
	V_ucBuffer[0] = Pt_ResetEsam;			///*发送复位消息给ESAM模块*///
	Dispatch_SendMessage(C_Msg_Esam,V_ucBuffer,Pt_ResetEsam_Len+1);
	///************************************************************************///
	///*更新数据层ESAM故障状态标志：故障或正常；首先从数据层读，刷新后再写*///
	V_len = CLMeter_Work_State1;
	InF_Read_Data(CMeter_Work_State1,&V_ucBuffer[0],&V_len,&V_usDataEncode);
	if(Str_ESAM_Status.HStatus == C_Esam_OK)
	{
		V_ucBuffer[1] &= ~C_ESAMERR_MeterWorkState;
	}
	else
	{
		V_ucBuffer[1] |= C_ESAMERR_MeterWorkState;
	}
	InF_Write_Data(C_Msg_Dispatch,CMeter_Work_State1,&V_ucBuffer[0],CLMeter_Work_State1,C_W_SafeFlag);
}



///************************************************************************///
///*函数原型:void SF_ColdReset_7816_Esam(uchar8 *P_Buff)
///*函数功能:ESAM上电复位消息函数:冷复位
///*输入参数:无
///*输出参数:ESAM复位后的13字节应答
///*返回参数:C_OK 复位成功;C_Error复位失败
///*调用时机：
///*备注:
///************************************************************************///
uchar8 SF_ColdReset_7816_Esam(uchar8 *P_Buff)///测试ESAM序列号输出
{
//	ulong32 i;
//	uchar8 *p_temp;
	uchar8 v_temp=C_Error;
//	ulong32 V_Delay;
	uchar8 V_Data[10];
	ushort16 V_Datalen,V_ResponseDataLen,V_ReturnData;

//	///*将ESAM停活*///
//	InF_Deactivation_7816_Esam();
//	///*延时约5ms，VESAM 0.8V，20ms，0.5V；30ms，0.3V，45ms，0.2V*///
//	InF_Delay_us(30000);///*延时30ms
//	///*打开电源*///
//	SwitchOn_EsamPower();
//	///*延时约2ms*///
//	InF_Delay_us(2000);
//	InF_EsamChipDeselect();		/* 取消片选 */
//	///*延时约2ms，注意延时*///
//	InF_Delay_us(2000);
//	DF_SPI_Configuration();///*重新配置SPI
//	InF_Delay_us(100000);///*延时100ms
	SF_ColdReset_7816_Esam_No();

	V_Data[0]=0x80;
	V_Data[1]=0x36;
	V_Data[2]=0x00;
	V_Data[3]=0x02;
	V_Data[4]=0x00;
	V_Data[5]=0x00;
	V_Datalen=6;
	V_ResponseDataLen=8;

	V_ReturnData=INF_SendData_698_Esam(&V_Data[0],V_Datalen,P_Buff,&V_ResponseDataLen);///*获取ESAM序列号*///

	if((V_ReturnData==C_Security_CommandOk)&&(V_ResponseDataLen==8))///*ESAM序列号数据长度为8*///
	{
		v_temp = C_OK;
	}
	else
	{
		v_temp = C_Error;
	}
	///*配置串口*///
	//InF_InitCommUartForDispatch(C_ESAM,C_bps_2400,C_CommDataLen8,C_SerStp_2,C_parity_Even);
//	DF_SPI_Configuration();

	///*时钟输出使能*///
	//EsamClock_Output_EN();

	///*延时约200us*///
//	for(i=0;i<100;i++)
//	{
//		InF_Delay_2us();
//	}
//
//	InF_EsamChipSelect();///*内部带延时		TCSL

	///*Esam复位*///
//	Esam_EN();

	///*延时约20us后配置单片机的串口，准备接收数据*///
	//for(i=0;i<10;i++)
	//{
	//	InF_Delay_2us();
	//}

	///*串口接收使能*///
	//InF_CommUart_RecEnableForDispatch( C_ESAM );

//	p_temp = P_Buff;
//	v_temp = SF_ReceiveDataFromEsam(&p_temp[0],C_Esam_Len_ResetAck);				///*接收复位后的13字节*///

//	EsamClock_Output_DIS();
	///*判断复位后的首5字节:3b 69 00 00 41/43：正确则Esam无故障*///
//	if( (p_temp[0] == C_FirstByte_ATR) && (p_temp[1] == C_SecondByte_ATR)
//		&& (p_temp[2] == C_ThirdByte_ATR) && (p_temp[3] == C_FourthByte_ATR) )
//	//	&& ((p_temp[4] == C_FifthByte_ATR41) || (p_temp[4] == C_FifthByte_ATR43)))
//	{
//		v_temp = C_OK;
//	}
//	else	///*不正确则Esam故障*///
//	{
//		v_temp = C_Error;
//	}
//	///*下面调试用*///
////	{
////		InF_CommUart_TxdDataForDispatch( C_ESAM,buff[i]);
////		while( !(SFR_ESAMCOM->SR & USART_FLAG_TC) )
////		{
////			;
////		}
////		SFR_ESAMCOM->SR &= ~USART_FLAG_TC;
////	}
//		///延时Tcsd 6us
//	for( V_Delay=0;V_Delay<C_Esam_Tcsd6us;V_Delay++)
//	{
//		InF_Delay_2us();
//	}
//	//dis CS
//	InF_EsamChipDeselect();///*内部带延时	TCSH
   return v_temp;
}

///************************************************************************///
///*函数原型:void InF_ExecuteClr_Esam(void)
///*函数功能:电表总清时，对于ESAM故障标志的处理
///*输入参数:
///*输出参数：
///*返回参数:无
///*调用时机：
///*备注:
///*功能说明：
///************************************************************************///
void InF_ExecuteClr_Esam(void)
{
	uchar8 V_ucBuffer[CLMeter_Work_State1];
	ushort16 V_len,V_usDataEncode;
	Str_ESAM_Status.HStatus = C_Esam_OK;
	///*历史状态写数据层*///
	InF_Write_Data(C_Msg_Esam,CESAM_FaultState,&Str_ESAM_Status.HStatus,CLESAM_FaultState,C_W_SafeFlag);
	///*更新数据层ESAM故障状态标志：故障或正常；首先从数据层读，刷新后再写*///
	V_len = CLMeter_Work_State1;
	InF_Read_Data(CMeter_Work_State1,&V_ucBuffer[0],&V_len,&V_usDataEncode);

	V_ucBuffer[1] &= ~C_ESAMERR_MeterWorkState;

	InF_Write_Data(C_Msg_Dispatch,CMeter_Work_State1,&V_ucBuffer[0],CLMeter_Work_State1,C_W_SafeFlag);
}

///************************************************************************///
///*函数原型:void SF_Execute_EsamErr(uchar8 P_Buff)
///*函数功能:处理ESAM故障标志
///*输入参数:当前操作ESAM成功、失败标志：C_OK、C_Error
///*输出参数：将当前操作ESAM成功/失败标志刷新数据层，并据此进行主动上报
///*返回参数:无
///*调用时机：
///*备注:
///*功能说明：
///************************************************************************///
void SF_Execute_EsamErr(uchar8 P_Buff)
{
	uchar8 V_ucBuffer[CLMeter_Work_State1];
	ushort16 V_len,V_usDataEncode;

	if( Str_ESAM_Status.HStatus == C_OK )
	{
		if( P_Buff != C_OK )
		{///*状态发生变化:变为故障,置历史状态,主动上报,将历史状态写入数据层*///
			Str_ESAM_Status.HStatus = C_Esam_ERR;
			//InF_ActiveReportSetting(C_Times_ESAMErr);
			Inf_WriteMeterStatus8(C_ESAMErroEventNo);
			InF_Write_Data(C_Msg_Esam,CESAM_FaultState,&Str_ESAM_Status.HStatus,CLESAM_FaultState,C_W_SafeFlag);
		}
	}
	else
	{
		if( P_Buff == C_OK )
		{///*状态发生变化:变为正常,置历史状态并将历史状态写入数据层*///
			Str_ESAM_Status.HStatus = C_Esam_OK;
			InF_Write_Data(C_Msg_Esam,CESAM_FaultState,&Str_ESAM_Status.HStatus,CLESAM_FaultState,C_W_SafeFlag);
		}
	}
	///************************************************************************///
	///*更新数据层ESAM故障状态标志：故障或正常；首先从数据层读，刷新后再写*///
	V_len = CLMeter_Work_State1;
	InF_Read_Data(CMeter_Work_State1,&V_ucBuffer[0],&V_len,&V_usDataEncode);
	if(Str_ESAM_Status.HStatus == C_Esam_OK)
	{
		V_ucBuffer[1] &= ~C_ESAMERR_MeterWorkState;
	}
	else
	{
		V_ucBuffer[1] |= C_ESAMERR_MeterWorkState;
	}
	InF_Write_Data(C_Msg_Dispatch,CMeter_Work_State1,&V_ucBuffer[0],CLMeter_Work_State1,C_W_SafeFlag);
}
///************************************************************************///
///*函数原型:uchar8 EsamPowerOnRest_Message(Str_Msg_Parameter * P_Msg_Parameter)
///*函数功能:ESAM上电复位消息函数:冷复位
///*输入参数:P_Msg_Parameter: 统一的Str_Msg_Parameter型变量
///*消息来源:SourceAddr= C_Msg_Dispatch,，调度
///*目的消息:DerictAddr = C_Msg_Esam;Len = 0
///*输出参数：Esam序列号
///*返回参数:C_ok 复位成功;C_Error复位失败
///*调用时机：调度上电初始化ESAM时
///*备注:
///************************************************************************///
uchar8 EsamPowerOnRest_Message(Str_Msg_Parameter *P_Msg_Parameter)
{
	uchar8 V_ucBuffer[20];
	uchar8 v_temp;

	PF_CopyDataBytes(P_Msg_Parameter->Parameter,V_ucBuffer,4);
	if( (P_Msg_Parameter->DerictAddr != C_Msg_Esam) || (V_ucBuffer[0] != Pt_ResetEsam) )
	{
		return C_Error;
	}

	v_temp = SF_ColdReset_7816_Esam(&V_ucBuffer[0]);		///*冷复位*测试698序列哈oESAM///

	SF_Execute_EsamErr( v_temp );							///*处理ESAM故障及主动上报*///

	if( v_temp == C_OK )
	{
		///*调用通信模块到涌诤瀵数，处理表号*///
		InF_S_GetMeterNum_ReworkDL();
		///*调用通信模块的接口函数，处理密钥状态*///
		InF_S_GetKeyStatus_ReworkKeyStatus();
	}
	if(C_ESAMPower == C_ESAMPower_Close)///*上电关ESAM电源，只送样用，正常生产不启用。
	{
//		uchar8 V_DataBuff[5];
//		V_DataBuff[4] = CLComm_Way;
//		if( InF_Read_Data(CComm_Way,&V_DataBuff[0],&V_DataBuff[4]) == C_OK )
//		{
//			if( V_DataBuff[0] == C_MeterType_Module )
//			{
				InF_Deactivation_7816_Esam();		///*停活ESAM*///
//			}
//		}
	}
	return v_temp;
}


///************************************************************************///
///*函数原型:uchar8 InF_SwitchEsam(uchar8 V_Act)
///*函数功能:开关ESAM
///*输入参数:V_Act=C_On：开ESAM；=C_Off，关ESAM
///*输出参数：无
///*返回参数:C_OK：操作成功;C_Error操作失败
///*调用时机：供通信模块调用
///*备注:在身份认证的时候需要调用,身份认证结束或超时关闭
///*功能说明：输入为C_ON：原来处于打开，则直接退出；原来处于关闭，则冷复位一下
///*          输入为C_Off：直接关闭
///*          进入函数首先判断标志的CRC是否正确，不正确则冷复位一下
///************************************************************************///
//uchar8 InF_SwitchEsam(uchar8 V_Act)
//{
////#define	C_Esam_StatusWork					0x6886	///*Esam处于工作状态*///
////#define	C_Esam_StatusDeactivation			0x5aa6	///*Esam处于停活状态*///
//	uchar8 v_return;
//	ushort16 v_tepm;
//	uchar8 buff[20];					///*用于复位ESAM后的13字节应答*///
//	///*判断Esam状态的CRC是否正确，不正确，直接进行冷复位*///
//	if( PF_Check_CRC(&Str_EsamStatus.Hstatus[0],C_Esam_Len_Status+2) != C_OK )
//	{
//		SF_ColdReset_7816_Esam(&buff[0]);
//		Str_EsamStatus.Hstatus[0] = C_Esam_StatusWorkL;
//		Str_EsamStatus.Hstatus[1] = C_Esam_StatusWorkH;
//		v_tepm = PF_Cal_CRC(Str_EsamStatus.Hstatus,C_Esam_Len_Status);
//		PF_Ushort16ToBuffer2(Str_EsamStatus.ESAMCRC,&v_tepm);
//		v_return = C_OK;
//	}
//	else
//	{
//		///*根据历史状态，确定接下来的动作*///
//		if( (Str_EsamStatus.Hstatus[0] == C_Esam_StatusWorkL) && (Str_EsamStatus.Hstatus[1] == C_Esam_StatusWorkH) )
//		{
//			if( V_Act == C_On )
//			{
//				v_return = C_OK;					///*原来处于工作状态，现在要开，直接退出*///
//			}
//			else									///*原来处于工作状态，现在要关，进行停活*///
//			{
//				InF_Deactivation_7816_Esam();
//				Str_EsamStatus.Hstatus[0] = C_Esam_StatusDeactivationL;
//				Str_EsamStatus.Hstatus[1] = C_Esam_StatusDeactivationH;
//				v_tepm = PF_Cal_CRC(Str_EsamStatus.Hstatus,C_Esam_Len_Status);
//				PF_Ushort16ToBuffer2(Str_EsamStatus.ESAMCRC,&v_tepm);
//				v_return = C_OK;
//			}
//		}
//		else			///*原来处于关闭状态*///
//		{
//			if( V_Act == C_Off )
//			{										///*原来处于关闭状态，现在要关闭*///
//				InF_Deactivation_7816_Esam();
//				Str_EsamStatus.Hstatus[0] = C_Esam_StatusDeactivationL;
//				Str_EsamStatus.Hstatus[1] = C_Esam_StatusDeactivationH;
//				v_tepm = PF_Cal_CRC(Str_EsamStatus.Hstatus,C_Esam_Len_Status);
//				PF_Ushort16ToBuffer2(Str_EsamStatus.ESAMCRC,&v_tepm);
//				v_return = C_OK;
//			}
//			else									///*原来处于关闭状态，现在要开，进行冷复位*///
//			{
//				SF_ColdReset_7816_Esam(&buff[0]);
//				Str_EsamStatus.Hstatus[0] = C_Esam_StatusWorkL;
//				Str_EsamStatus.Hstatus[1] = C_Esam_StatusWorkH;
//				v_tepm = PF_Cal_CRC(Str_EsamStatus.Hstatus,C_Esam_Len_Status);
//				PF_Ushort16ToBuffer2(Str_EsamStatus.ESAMCRC,&v_tepm);
//				v_return = C_OK;
//			}
//		}
//	}
//	return v_return;
//}
