
///*****************************************************************************************///
///*Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     EsamDrive.c
///*Version:       V1
///*Date:          2014-3-12
///*Description:   EsamоƬ�������ļ�
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
#include "EsamDrive.h"
#include "SPI.h"
#include "Dispatch.h"

ulong32	SV_ulTemp_Esam;	///*�ñ����������мĴ����Ķ�->�޸�->д*///

extern void SF_Execute_EsamErr(uchar8 P_Buff);


///**************************************************************************************************///
///*Function��uchar8 SF_ReceiveDataFromEsam(uchar8 *P_ucReceiveDataBuffer,ushort16 V_ucReceiveDataLen)*///
///*Description���Ӵ��ڽ���ESAM������������															*///
///*Input��		P_ucReceiveDataBuffer�������ݻ���buffer�׵�ַ,V_ucReceiveDataLen��Ҫ�������ݵĳ���	*///
///*Output��	����V_ucReceiveDataLen�ֽڵ�����д��P_ucReceiveDataBufferbuffer��					*///
///*Calls��		��ʱ��ESAMͣ�д��Ϣ����															*///
///*Called By��	ESAM�շ����ݴ���������															*///
///*Influence��																						*///
///*Tips��																							*///
///*Others��																						*///
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

		P_ucReceiveDataBuffer[V_InteractionLen] = v_buff;		///*ȡ���ݵ�������*///
		V_InteractionLen++;
	}

	return C_OK;
}


///**************************************************************************************///
///*Function��void SF_SendDataToEsam(uchar8 *P_ucSendDataBuffer,ushort16 V_ucSendDataLen)	*///
///*Description��	�Ӵ��ڷ������ݵ�ESAMģ��											*///
///*Input��	P_ucSendDataBuffer��������buffer�׵�ַ��V_ucSendDataLen�������ݳ���			*///
///*Output��																			*///
///*Calls��																				*///
///*Called By��																			*///
///*Influence��																			*///
///*Tips��																				*///
///*Others��																			*///
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
///*����ԭ�ͣ�void InF_Deactivation_7816_Esam(void)
///*����������ʵ��ESAM��ͣ��
///*�����������
///*�����������
///*���ز�������
///*�������ܣ�
///*����ʱ����
///*��ע��
///************************************************************************///
void InF_Deactivation_7816_Esam(void)
{
	///*��λ->ͣʱ��->����������->�رյ�Դ*///
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

//	InF_EsamChipSelect();	/* ��������,CS���߻���©������ESAM��Դ,���Խ�CS�������� */
}

///************************************************************************///
///*����ԭ�ͣ�uchar8  INF_WarmRest_7816_Esam(void)
///*����������ʵ��ESAM���ȸ�λ
///*�����������
///*���������ESAM�����к�
///*���ز�����C_ok ��λ����;C_Error��λ�쳣;
///*�������ܣ�MCU����ESAM��Rst����ʵ�ֶ�ESAM���ȸ�λ
///*����ʱ����
///*��ע��
///************************************************************************///
uchar8  INF_WarmRest_7816_Esam(void)///
{
	return C_OK;
//	ushort16 i;
////	uchar8 p_temp[20];
//	uchar8 v_temp;
////	ulong32 V_Delay;
//
//	///*���ô���*///
////	InF_InitCommUartForDispatch(C_ESAM,C_bps_2400,C_CommDataLen8,C_SerStp_2,C_parity_Even);
//	DF_SPI_Configuration();
//
//	///*ʱ�����ʹ��*///
////	EsamClock_Output_EN();
//
//	///*Esam��λ*///
////	Esam_Reset();
//	///*��ʱԼ200us*///
//	for(i=0;i<100;i++)
//	{
//		InF_Delay_2us();
//	}
//
////	InF_EsamChipSelect();///*ʹ��SPIƬѡ�źţ��ڲ�����ʱ
//
//	///*Esamʹ��*///
////	Esam_EN();
//
//	///*���ڽ���ʹ��*///
////	InF_CommUart_RecEnableForDispatch( C_ESAM );
//
////	v_temp = SF_ReceiveDataFromEsam(&p_temp[0],C_Esam_Len_ResetAck);				///*���ո�λ���13�ֽ�*///
//
////	EsamClock_Output_DIS();
//	///*�жϸ�λ�����5�ֽ�:3b 69 00 00 41/43����ȷ��Esam�޹���*///
////	if( (p_temp[0] == C_FirstByte_ATR) && (p_temp[1] == C_SecondByte_ATR)
////		&& (p_temp[2] == C_ThirdByte_ATR) && (p_temp[3] == C_FourthByte_ATR) )
////	//	&& ((p_temp[4] == C_FifthByte_ATR41) || (p_temp[4] == C_FifthByte_ATR43)))
////	{
//		v_temp = C_OK;
////	}
////	else	///*����ȷ��Esam����*///
////	{
////		v_temp = C_Error;
////	}
//
////	SF_Execute_EsamErr( v_temp );
//
////	///��ʱTcsd 6us
////	for( V_Delay=0;V_Delay<C_Esam_Tcsd6us;V_Delay++)
////	{
////		InF_Delay_2us();
////	}
////	//dis CS
////	InF_EsamChipDeselect();///*�ڲ�����ʱ	TCSH
//
//	return v_temp;
}
ushort16 INF_SendData_7816_Esam(uchar8*P_SendBuffer,uchar8 V_Datalen,uchar8 *pResponse,uchar8 *pMaxResponseLen)
{
    return C_OK;
}

///************************************************************************///
///*����ԭ��:void SF_ColdReset_7816_Esam_No(void)
///*��������:ESAM�ϵ縴λ��Ϣ����:�临λ
///*�������:��
///*�������:ESAM��λ���13�ֽ�Ӧ��
///*���ز���:C_OK ��λ�ɹ�;C_Error��λʧ��
///*����ʱ����
///*��ע:
///************************************************************************///
void SF_ColdReset_7816_Esam_No(void)///����ESAM����ȡ���к����
{
	///*��ESAMͣ��*///
	InF_Deactivation_7816_Esam();
	///*��ʱԼ5ms��VESAM 0.8V��20ms��0.5V��30ms��0.3V��45ms��0.2V*///
	InF_Delay_us(30000);///*��ʱ30ms
	///*�򿪵�Դ*///
	SwitchOn_EsamPower();
	///*��ʱԼ2ms*///
	InF_Delay_us(2000);
	InF_EsamChipDeselect();		/* ȡ��Ƭѡ */
	///*��ʱԼ2ms��ע����ʱ*///
	InF_Delay_us(2000);
	DF_SPI_Configuration();///*��������SPI
	InF_Delay_us(100000);///*��ʱ100ms
}
///************************************************************************///
///*����ԭ��:void SF_ColdReset_7816_Esam_PowerNo(void)
///*��������:ESAM�ϵ縴λ��Ϣ����:�临λ
///*�������:��
///*�������:ESAM��λ���13�ֽ�Ӧ��
///*���ز���:C_OK ��λ�ɹ�;C_Error��λʧ��
///*����ʱ����
///*��ע:ESAM�ٴ��ϵ��������ʱ30ms
///************************************************************************///
void SF_ColdReset_7816_Esam_PowerNo(void)///����ESAM����ȡ���к����
{
	///*�򿪵�Դ*///
	SwitchOn_EsamPower();
	///*��ʱԼ2ms*///
	InF_Delay_us(2000);
	InF_EsamChipDeselect();		/* ȡ��Ƭѡ */
	///*��ʱԼ2ms��ע����ʱ*///
	InF_Delay_us(2000);
	DF_SPI_Configuration();///*��������SPI
	InF_Delay_us(30000);///*��ʱ30ms
}
///***********************************************************************************************///
///*����ԭ��:ushort16 INF_SendData_7816_Esam(uchar8*P_SendBuffer,ushort16 V_Datalen,uchar8 *pResponse,ushort16 *pMaxResponseLen)
///*�����������˺���������ESAM��������
///*���������
///* P_SendBuffer:���������ݵ��׵�ַ(������55��LRC1);
///* V _DataLen:��Ŵ��������ݳ���
///* pResponse:�����Ӧ���ݵ��׵�ַ�����ESAM�ȷ��ص�����
///* pMaxResponseLen:��Ϊ���������ʾ���뻺������ݳ��ȣ���Ϊ�������ʱ�������Ӧ���ݳ��ȣ����Ȳ�����SW1��SW2
///*P_SendBuffer��pResponse������ȣ�����SW1��SW2����ΪResponse����
///*�������:ESAM��Ӧ�����ݼ����ȣ�����SW1��SW2�ڴ˺����ڲ�����ʱ�������У������
///*���ز���:61xx���ݽ�������;C_Security_Err���ݽ����쳣;MaxResponseLen_ERR ��󳤶Ȳ���,SW1/SW2(SW1Ϊ���ֽ�)
///*��������:�������������������ݷ��͸�ESAM��������ESAM��Ӧ�����ݺ����ݳ���.�ڲ��ж����ݳ��ȡ�55���ձ�־��У�������ж�
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
	if((SV_ulTemp_ESAM&ESAMPOWERSET)==ESAMPOWERSET)///*��Դ�򿪵���Ч
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
	///*���ô���*///
//	InF_InitCommUartForDispatch(C_ESAM,C_bps_2400,C_CommDataLen8,C_SerStp_2,C_parity_Even);
//	DF_SPI_Configuration();
	///*ȡҪ���͵ĳ���*///
	V_TxDataLen = V_Datalen;
	///************************************************************************///
	///*�����Ҫ���͵ĳ��ȡ���ESAM���ճ����ж�*///
	if( V_TxDataLen < C_Len_APDU_4 )
	{
		return C_Security_MaxLenErr;
	}
//	else///*�������ݳ����жϣ�����ȶ�����
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
	///*��ʱԼ200us*///
	for(V_Delay=0;V_Delay<100;V_Delay++)
	{
		InF_Delay_2us();
	}
	///**************��֯��������*************************///
	V_SendSign=C_Esam_TxRxSign55;

	V_LRC1=P_SendBuffer_temp[0];
	for(V_i=1;V_i<V_TxDataLen;V_i++)///*����У������
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
	///*****************���ݷ��͡�����*****************///
	for(V_RetryTime=0;V_RetryTime<C_Esam_RetryTime;V_RetryTime++)///*�����쳣�ط�
	{///**************���ݷ���
		//CS
		InF_EsamChipSelect();///*�ڲ�����ʱ��ʵ����ʱ68usҪ��50@100us ����ֵ60��Tcsl

		///*��1�ֽڵ�55��ESAM*///
		SF_SendDataToEsam(&V_SendSign,1);
		///*������ESAM*///
		SF_SendDataToEsam(&P_SendBuffer_temp[0],V_TxDataLen);		///*�ַ���Ч����ʱ��6.8us�����8.6us��Ҫ��1.5@10us
		///*��LRC��ESAM*///
		SF_SendDataToEsam(&V_LRC1,1);
		///��ʱTcsd 6us��ʵ��6.8usҪ��3@10  ʵ��10.44��ԭC_Esam_Tcsd6usΪ4�� ������ֵ5us
		for( V_Delay=0;V_Delay<C_Esam_Tcsd6us;V_Delay++)
		{
			InF_Delay_2us();
		}
		//dis CS
		InF_EsamChipDeselect();///*�ڲ�����ʱ	TCSH	ʵ��31.2usҪ��10@50������ֵ10us
///***********���ݽ���
		for(V_i=0;V_i<2;V_i++)///*У����쳣Ŀǰѭ������2���ж�
		{
			//CS
			InF_EsamChipSelect();///*�ڲ�����ʱ		TCSL		Ҫ��ֵ50@100,ʵ��ֵ63.1������ֵ60us
			//*55��־λ
			V_ulDelay=0;
			SF_ReceiveDataFromEsam(&V_ucBuffer[0],1);
			while(V_ucBuffer[0]!=C_Esam_TxRxSign55)
			{///��ʱTq 37.1us		15@100������ֵ20us
				for( V_Delay=0;V_Delay<C_Esam_Tq20us;V_Delay++)
				{
					InF_Delay_2us();
					V_ulDelay++;
				}
				if( V_ulDelay > C_Esam_1S )							///*�����ʱ1s*///
				{
					uchar8 v_buffTemp[CLESAM_FaultState];
					ushort16 V_DatalenTemp;
					V_DatalenTemp=CLESAM_FaultState;
					InF_Read_Data(CESAM_FaultState,&v_buffTemp[0],&V_DatalenTemp,&V_usDataEncode);
					if(C_Esam_ERR!=v_buffTemp[0])///*ESAM����
					{
					V_ucBuffer[0] = Pt_ResetEsam;			///*���͸�λ��Ϣ��ESAMģ��*///
					Dispatch_SendMessage(C_Msg_Esam,V_ucBuffer,Pt_ResetEsam_Len+1);
					}
					///*ESAM������*///
					SF_Execute_EsamErr( C_Error );
//					__enable_irq();
					return C_Security_OverTime;
				}
				SF_ReceiveDataFromEsam(&V_ucBuffer[0],1);
			}
			//*����4���ֽ� SW1 SW2 Len1 Len2
			if(SF_ReceiveDataFromEsam(V_ucRxBufHead,C_Len_APDU_4)==C_OK)
			{
                V_ucBuffer[0]=V_ucRxBufHead[3];
				V_ucBuffer[1]=V_ucRxBufHead[2];

				PF_Buffer2ToUshort16(&V_ucBuffer[0],&V_ResponseDataLen);
				if(V_ResponseDataLen>*pMaxResponseLen)///*��ȫ�ж�
				{
//					__enable_irq();
					return C_Security_MaxLenErr;
				}
				///*����ʣ������
// 				for( V_Delay=0;V_Delay<100;V_Delay++)
//				{
//					InF_Delay_2us();
//				}
				if(V_ResponseDataLen<C_Len_Esam_Max)///*�������ݳ��������жϣ���ֹ���ݳ����쳣
				{
					SF_ReceiveDataFromEsam(&pResponse_temp[0],V_ResponseDataLen);
					SF_ReceiveDataFromEsam(&V_ucBuffer[0],1);	///LRC2		�ֿ�����ֹpResponse_temp	���渲��
//					V_ucBuffer[0] = pResponse_temp[V_ResponseDataLen];
		            ///��ʱTcsd 6us
					for( V_Delay=0;V_Delay<C_Esam_Tcsd6us;V_Delay++)
					{
						InF_Delay_2us();
					}
					//dis CS
					InF_EsamChipDeselect();///*�ڲ�����ʱ	TCSH
					//LRC2 �ж�
					V_LRC2 = V_ucRxBufHead[0];
					V_LRC2 ^= V_ucRxBufHead[1];
					V_LRC2 ^= V_ucRxBufHead[2];
					V_LRC2 ^= V_ucRxBufHead[3];

					for(V_j=0;V_j<V_ResponseDataLen;V_j++)///*����У������
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
					InF_EsamChipDeselect();///*�ڲ�����ʱ	TCSH
				}
			}
			else///���������쳣
			{
				//dis CS
				InF_EsamChipDeselect();///*�ڲ�����ʱ	TCSH
			}
		}
		///*****�ж�SW�Ƿ�Ϊ6A90,ESAM LRCУ�����,����������ط�
		if((V_ucRxBufHead[0]!=0x6A)&&(V_ucRxBufHead[1]!=0x90))
		{
			break;
		}
	}
///*�������ݴ���
	v_temp = V_ucRxBufHead[0];
	v_temp <<= 8;
	v_temp |= (ushort16)V_ucRxBufHead[1];
//	if(C_Security_CommandOk==v_temp)///*SWΪ9000
//	{
		if(V_i<2)///*����ESAM���ݣ�LRCУ������
		{
			//P_Buff=C_OK;	///*ESAM����*///
		}
		else
		{
			//P_Buff=C_Error;	///*ESAM����*///
			v_temp=C_Security_Err;
		}
//	}
//	else///*SW��9000
//	{
//		P_Buff = C_Error;	///*ESAM����*///
//	}
//	if(P_Buff==C_Error)///*ESAM����*///
//	{
//			V_ucBuffer[0] = Pt_ResetEsam;			///*���͸�λ��Ϣ��ESAMģ��*///
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
///*����ԭ��:void InF_InitEsamPowerOn(void)
///*��������:ESAM�ϵ縴λ��Ϣ����:�临λ
///*�������:P_Msg_Parameter: ͳһ��Str_Msg_Parameter�ͱ���
///*��Ϣ��Դ:SourceAddr= C_Msg_Dispatch,������
///*Ŀ����Ϣ:DerictAddr = C_Msg_Esam;Len = 0
///*���������Esam���к�
///*���ز���:C_ok ��λ�ɹ�;C_Error��λʧ��
///*����ʱ���������ϵ��ʼ��ESAMʱ
///*��ע:
///************************************************************************///
void InF_InitEsamPowerOn(void)
{

	uchar8 V_ucBuffer[5];
	ushort16 V_len,V_usDataEncode;
	///*�����ݲ������ʷ״̬*///
	V_len = CLESAM_FaultState;
	if( InF_Read_Data(CESAM_FaultState,&Str_ESAM_Status.HStatus,&V_len,&V_usDataEncode) != C_OK )
	{
		Str_ESAM_Status.HStatus = C_Esam_OK;
	}
	///************************************************************************///
	InF_Deactivation_7816_Esam();			///*ESAMͣ��*///
	V_ucBuffer[0] = Pt_ResetEsam;			///*���͸�λ��Ϣ��ESAMģ��*///
	Dispatch_SendMessage(C_Msg_Esam,V_ucBuffer,Pt_ResetEsam_Len+1);
	///************************************************************************///
	///*�������ݲ�ESAM����״̬��־�����ϻ����������ȴ����ݲ����ˢ�º���д*///
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
///*����ԭ��:void SF_ColdReset_7816_Esam(uchar8 *P_Buff)
///*��������:ESAM�ϵ縴λ��Ϣ����:�临λ
///*�������:��
///*�������:ESAM��λ���13�ֽ�Ӧ��
///*���ز���:C_OK ��λ�ɹ�;C_Error��λʧ��
///*����ʱ����
///*��ע:
///************************************************************************///
uchar8 SF_ColdReset_7816_Esam(uchar8 *P_Buff)///����ESAM���к����
{
//	ulong32 i;
//	uchar8 *p_temp;
	uchar8 v_temp=C_Error;
//	ulong32 V_Delay;
	uchar8 V_Data[10];
	ushort16 V_Datalen,V_ResponseDataLen,V_ReturnData;

//	///*��ESAMͣ��*///
//	InF_Deactivation_7816_Esam();
//	///*��ʱԼ5ms��VESAM 0.8V��20ms��0.5V��30ms��0.3V��45ms��0.2V*///
//	InF_Delay_us(30000);///*��ʱ30ms
//	///*�򿪵�Դ*///
//	SwitchOn_EsamPower();
//	///*��ʱԼ2ms*///
//	InF_Delay_us(2000);
//	InF_EsamChipDeselect();		/* ȡ��Ƭѡ */
//	///*��ʱԼ2ms��ע����ʱ*///
//	InF_Delay_us(2000);
//	DF_SPI_Configuration();///*��������SPI
//	InF_Delay_us(100000);///*��ʱ100ms
	SF_ColdReset_7816_Esam_No();

	V_Data[0]=0x80;
	V_Data[1]=0x36;
	V_Data[2]=0x00;
	V_Data[3]=0x02;
	V_Data[4]=0x00;
	V_Data[5]=0x00;
	V_Datalen=6;
	V_ResponseDataLen=8;

	V_ReturnData=INF_SendData_698_Esam(&V_Data[0],V_Datalen,P_Buff,&V_ResponseDataLen);///*��ȡESAM���к�*///

	if((V_ReturnData==C_Security_CommandOk)&&(V_ResponseDataLen==8))///*ESAM���к����ݳ���Ϊ8*///
	{
		v_temp = C_OK;
	}
	else
	{
		v_temp = C_Error;
	}
	///*���ô���*///
	//InF_InitCommUartForDispatch(C_ESAM,C_bps_2400,C_CommDataLen8,C_SerStp_2,C_parity_Even);
//	DF_SPI_Configuration();

	///*ʱ�����ʹ��*///
	//EsamClock_Output_EN();

	///*��ʱԼ200us*///
//	for(i=0;i<100;i++)
//	{
//		InF_Delay_2us();
//	}
//
//	InF_EsamChipSelect();///*�ڲ�����ʱ		TCSL

	///*Esam��λ*///
//	Esam_EN();

	///*��ʱԼ20us�����õ�Ƭ���Ĵ��ڣ�׼����������*///
	//for(i=0;i<10;i++)
	//{
	//	InF_Delay_2us();
	//}

	///*���ڽ���ʹ��*///
	//InF_CommUart_RecEnableForDispatch( C_ESAM );

//	p_temp = P_Buff;
//	v_temp = SF_ReceiveDataFromEsam(&p_temp[0],C_Esam_Len_ResetAck);				///*���ո�λ���13�ֽ�*///

//	EsamClock_Output_DIS();
	///*�жϸ�λ�����5�ֽ�:3b 69 00 00 41/43����ȷ��Esam�޹���*///
//	if( (p_temp[0] == C_FirstByte_ATR) && (p_temp[1] == C_SecondByte_ATR)
//		&& (p_temp[2] == C_ThirdByte_ATR) && (p_temp[3] == C_FourthByte_ATR) )
//	//	&& ((p_temp[4] == C_FifthByte_ATR41) || (p_temp[4] == C_FifthByte_ATR43)))
//	{
//		v_temp = C_OK;
//	}
//	else	///*����ȷ��Esam����*///
//	{
//		v_temp = C_Error;
//	}
//	///*���������*///
////	{
////		InF_CommUart_TxdDataForDispatch( C_ESAM,buff[i]);
////		while( !(SFR_ESAMCOM->SR & USART_FLAG_TC) )
////		{
////			;
////		}
////		SFR_ESAMCOM->SR &= ~USART_FLAG_TC;
////	}
//		///��ʱTcsd 6us
//	for( V_Delay=0;V_Delay<C_Esam_Tcsd6us;V_Delay++)
//	{
//		InF_Delay_2us();
//	}
//	//dis CS
//	InF_EsamChipDeselect();///*�ڲ�����ʱ	TCSH
   return v_temp;
}

///************************************************************************///
///*����ԭ��:void InF_ExecuteClr_Esam(void)
///*��������:�������ʱ������ESAM���ϱ�־�Ĵ���
///*�������:
///*���������
///*���ز���:��
///*����ʱ����
///*��ע:
///*����˵����
///************************************************************************///
void InF_ExecuteClr_Esam(void)
{
	uchar8 V_ucBuffer[CLMeter_Work_State1];
	ushort16 V_len,V_usDataEncode;
	Str_ESAM_Status.HStatus = C_Esam_OK;
	///*��ʷ״̬д���ݲ�*///
	InF_Write_Data(C_Msg_Esam,CESAM_FaultState,&Str_ESAM_Status.HStatus,CLESAM_FaultState,C_W_SafeFlag);
	///*�������ݲ�ESAM����״̬��־�����ϻ����������ȴ����ݲ����ˢ�º���д*///
	V_len = CLMeter_Work_State1;
	InF_Read_Data(CMeter_Work_State1,&V_ucBuffer[0],&V_len,&V_usDataEncode);

	V_ucBuffer[1] &= ~C_ESAMERR_MeterWorkState;

	InF_Write_Data(C_Msg_Dispatch,CMeter_Work_State1,&V_ucBuffer[0],CLMeter_Work_State1,C_W_SafeFlag);
}

///************************************************************************///
///*����ԭ��:void SF_Execute_EsamErr(uchar8 P_Buff)
///*��������:����ESAM���ϱ�־
///*�������:��ǰ����ESAM�ɹ���ʧ�ܱ�־��C_OK��C_Error
///*�������������ǰ����ESAM�ɹ�/ʧ�ܱ�־ˢ�����ݲ㣬���ݴ˽��������ϱ�
///*���ز���:��
///*����ʱ����
///*��ע:
///*����˵����
///************************************************************************///
void SF_Execute_EsamErr(uchar8 P_Buff)
{
	uchar8 V_ucBuffer[CLMeter_Work_State1];
	ushort16 V_len,V_usDataEncode;

	if( Str_ESAM_Status.HStatus == C_OK )
	{
		if( P_Buff != C_OK )
		{///*״̬�����仯:��Ϊ����,����ʷ״̬,�����ϱ�,����ʷ״̬д�����ݲ�*///
			Str_ESAM_Status.HStatus = C_Esam_ERR;
			//InF_ActiveReportSetting(C_Times_ESAMErr);
			Inf_WriteMeterStatus8(C_ESAMErroEventNo);
			InF_Write_Data(C_Msg_Esam,CESAM_FaultState,&Str_ESAM_Status.HStatus,CLESAM_FaultState,C_W_SafeFlag);
		}
	}
	else
	{
		if( P_Buff == C_OK )
		{///*״̬�����仯:��Ϊ����,����ʷ״̬������ʷ״̬д�����ݲ�*///
			Str_ESAM_Status.HStatus = C_Esam_OK;
			InF_Write_Data(C_Msg_Esam,CESAM_FaultState,&Str_ESAM_Status.HStatus,CLESAM_FaultState,C_W_SafeFlag);
		}
	}
	///************************************************************************///
	///*�������ݲ�ESAM����״̬��־�����ϻ����������ȴ����ݲ����ˢ�º���д*///
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
///*����ԭ��:uchar8 EsamPowerOnRest_Message(Str_Msg_Parameter * P_Msg_Parameter)
///*��������:ESAM�ϵ縴λ��Ϣ����:�临λ
///*�������:P_Msg_Parameter: ͳһ��Str_Msg_Parameter�ͱ���
///*��Ϣ��Դ:SourceAddr= C_Msg_Dispatch,������
///*Ŀ����Ϣ:DerictAddr = C_Msg_Esam;Len = 0
///*���������Esam���к�
///*���ز���:C_ok ��λ�ɹ�;C_Error��λʧ��
///*����ʱ���������ϵ��ʼ��ESAMʱ
///*��ע:
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

	v_temp = SF_ColdReset_7816_Esam(&V_ucBuffer[0]);		///*�临λ*����698���й�oESAM///

	SF_Execute_EsamErr( v_temp );							///*����ESAM���ϼ������ϱ�*///

	if( v_temp == C_OK )
	{
		///*����ͨ��ģ�鵽ӿں�����������*///
		InF_S_GetMeterNum_ReworkDL();
		///*����ͨ��ģ��Ľӿں�����������Կ״̬*///
		InF_S_GetKeyStatus_ReworkKeyStatus();
	}
	if(C_ESAMPower == C_ESAMPower_Close)///*�ϵ��ESAM��Դ��ֻ�����ã��������������á�
	{
//		uchar8 V_DataBuff[5];
//		V_DataBuff[4] = CLComm_Way;
//		if( InF_Read_Data(CComm_Way,&V_DataBuff[0],&V_DataBuff[4]) == C_OK )
//		{
//			if( V_DataBuff[0] == C_MeterType_Module )
//			{
				InF_Deactivation_7816_Esam();		///*ͣ��ESAM*///
//			}
//		}
	}
	return v_temp;
}


///************************************************************************///
///*����ԭ��:uchar8 InF_SwitchEsam(uchar8 V_Act)
///*��������:����ESAM
///*�������:V_Act=C_On����ESAM��=C_Off����ESAM
///*�����������
///*���ز���:C_OK�������ɹ�;C_Error����ʧ��
///*����ʱ������ͨ��ģ�����
///*��ע:�������֤��ʱ����Ҫ����,�����֤������ʱ�ر�
///*����˵��������ΪC_ON��ԭ�����ڴ򿪣���ֱ���˳���ԭ�����ڹرգ����临λһ��
///*          ����ΪC_Off��ֱ�ӹر�
///*          ���뺯�������жϱ�־��CRC�Ƿ���ȷ������ȷ���临λһ��
///************************************************************************///
//uchar8 InF_SwitchEsam(uchar8 V_Act)
//{
////#define	C_Esam_StatusWork					0x6886	///*Esam���ڹ���״̬*///
////#define	C_Esam_StatusDeactivation			0x5aa6	///*Esam����ͣ��״̬*///
//	uchar8 v_return;
//	ushort16 v_tepm;
//	uchar8 buff[20];					///*���ڸ�λESAM���13�ֽ�Ӧ��*///
//	///*�ж�Esam״̬��CRC�Ƿ���ȷ������ȷ��ֱ�ӽ����临λ*///
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
//		///*������ʷ״̬��ȷ���������Ķ���*///
//		if( (Str_EsamStatus.Hstatus[0] == C_Esam_StatusWorkL) && (Str_EsamStatus.Hstatus[1] == C_Esam_StatusWorkH) )
//		{
//			if( V_Act == C_On )
//			{
//				v_return = C_OK;					///*ԭ�����ڹ���״̬������Ҫ����ֱ���˳�*///
//			}
//			else									///*ԭ�����ڹ���״̬������Ҫ�أ�����ͣ��*///
//			{
//				InF_Deactivation_7816_Esam();
//				Str_EsamStatus.Hstatus[0] = C_Esam_StatusDeactivationL;
//				Str_EsamStatus.Hstatus[1] = C_Esam_StatusDeactivationH;
//				v_tepm = PF_Cal_CRC(Str_EsamStatus.Hstatus,C_Esam_Len_Status);
//				PF_Ushort16ToBuffer2(Str_EsamStatus.ESAMCRC,&v_tepm);
//				v_return = C_OK;
//			}
//		}
//		else			///*ԭ�����ڹر�״̬*///
//		{
//			if( V_Act == C_Off )
//			{										///*ԭ�����ڹر�״̬������Ҫ�ر�*///
//				InF_Deactivation_7816_Esam();
//				Str_EsamStatus.Hstatus[0] = C_Esam_StatusDeactivationL;
//				Str_EsamStatus.Hstatus[1] = C_Esam_StatusDeactivationH;
//				v_tepm = PF_Cal_CRC(Str_EsamStatus.Hstatus,C_Esam_Len_Status);
//				PF_Ushort16ToBuffer2(Str_EsamStatus.ESAMCRC,&v_tepm);
//				v_return = C_OK;
//			}
//			else									///*ԭ�����ڹر�״̬������Ҫ���������临λ*///
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
