
///*****************************************************************************************///
///*Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     CardDrive.c
///*Version:       V1
///*Date:          2014-3-12
///*Description:   �ⲿ���ܿ��������ļ�
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
#include "CardDrive.h"
#include "EsamDrive.h"
#include "uart.h"
#include "Timer.h"
///*���ģ��7816*///
///***********************************************************************************///
///*����ԭ�ͣ�����Դ����					    									 *///
///***********************************************************************************///
void DF_Switch_CardPower(uchar8 Act)
{
	if(C_L_SmartMeter==C_Meter_Type)///*���ر���Զ�����ܱ���߳�ͻ
	{
		switch( Act )
		{
			case C_On:	///*�򿪵�Դ*///
			{
				SwitchOn_CardPower();
				break;
			}
			default:	///*�رյ�Դ*///
			{
				SwitchOff_CardPower();
				break;
			}
		}		
	}
}
///***********************************************************************************///
///*����ԭ�ͣ���ʱ�ӿ���					    									 *///
///***********************************************************************************///
void DF_Switch_CardSck(uchar8 Act)
{
	switch( Act )
	{
		case C_On:	///*����ʱ��*///
		{
			SwitchOn_CardSck();
			break;
		}
		default:	///*�ж�ʱ��*///
		{
			SwitchOff_CardSck();
			break;
		}
	}
}
///***********************************************************************************///
///*����ԭ�ͣ�����λ����					    									 *///
///***********************************************************************************///
void DF_Switch_CardEn(uchar8 Act)
{
	if(C_L_SmartMeter==C_Meter_Type)///*���ر���Զ�����ܱ���߳�ͻ
	{
		switch( Act )
		{
			case C_On:	///*��ʹ��*///
			{
				Card_EN();
				break;
			}
			default:	///*����λ*///
			{
				Card_Reset();
				break;
			}
		}		
	}
}

///**************************************************************************************************///
///*Function��uchar8 SF_ReceiveDataFromCard(uchar8 *P_ucReceiveDataBuffer,uchar8 V_ucReceiveDataLen)*///
///*Description���Ӵ��ڽ���CARD������������															*///
///*Input��		P_ucReceiveDataBuffer�������ݻ���buffer�׵�ַ,V_ucReceiveDataLen��Ҫ�������ݵĳ���	*///
///*Output��	����V_ucReceiveDataLen�ֽڵ�����д��P_ucReceiveDataBufferbuffer��					*///
///*Calls��		��ʱ��CARDͣ�д��Ϣ����															*///
///*Called By��	CARD�շ����ݴ���������															*///
///*Influence��																						*///
///*Tips��																							*///
///*Others��																						*///
///**************************************************************************************************///
uchar8 SF_ReceiveDataFromCard(uchar8 *P_ucReceiveDataBuffer,uchar8 V_ucReceiveDataLen)
{
	uchar8 V_InteractionLen;
	uchar8 v_buff;
	
	CardDataIO_R();				///*����������Ϊ����*///
	
	V_InteractionLen = 0;
	while( V_InteractionLen < V_ucReceiveDataLen )
	{
		if( SF_RecOneByteFrom_Card(&v_buff) != C_OK )
		{
			return C_Error;
		}
		
		P_ucReceiveDataBuffer[V_InteractionLen] = v_buff;		///*ȡ���ݵ�������*///
		V_InteractionLen++;
	}
	
	return C_OK;
}


///**************************************************************************************///
///*Function��void SF_SendDataToCard(uchar8 *P_ucSendDataBuffer,uchar8 V_ucSendDataLen)	*///
///*Description��	�Ӵ��ڷ������ݵ�CARDģ��											*///
///*Input��	P_ucSendDataBuffer��������buffer�׵�ַ��V_ucSendDataLen�������ݳ���			*///
///*Output��																			*///
///*Calls��																				*///
///*Called By��																			*///
///*Influence��																			*///
///*Tips��																				*///
///*Others��																			*///
///**************************************************************************************///
void SF_SendDataToCard(uchar8 *P_ucSendDataBuffer,uchar8 V_ucSendDataLen)
{
	uchar8 V_InteractionLen;
	CardDataIO_T_1();		///*����������Ϊ����,�����͸�*///
	
	V_InteractionLen = 0;
	while( V_InteractionLen < V_ucSendDataLen )
	{
		SF_SendOneByteTo_Card(P_ucSendDataBuffer[V_InteractionLen]);
		V_InteractionLen ++;
	}
}
///************************************************************************///
///*����ԭ�ͣ�void CardIO_Init(void)
///*��������������ʼ��IO��ͻ�����ܱ��ر�
///*�����������
///*�����������
///*���ز�������
///*�������ܣ�
///*����ʱ����
///*��ע��
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
///*����ԭ�ͣ�void InF_Deactivation_7816_Card(void)
///*����������ʵ�����ܿ���ͣ��
///*�����������
///*�����������
///*���ز�������
///*�������ܣ�
///*����ʱ������ȫģ���������ɺ����
///*��ע��
///************************************************************************///
void InF_Deactivation_7816_Card(void)
{
	///*��λ->ͣʱ��->����������->�رյ�Դ*///
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
///*����ԭ�ͣ�uchar8 INF_WarmReset_7816_Card(uchar8 *P_CardNo)*///
///*����������ʵ��Card���ȸ�λ*///
///*���������*P_CardNo:�����кŴ�ŵ�ַ*///
///*���������CARD�����к�:������������ݴ���ڵ͵�ַ����8�ֽ�*///
///*���ز�����C_ok ��λ����;C_Error��λ�쳣;*///
///*�������ܣ�MCU����Card��Rst����ʵ�ֶ�CARD���ȸ�λ*///
///*����ʱ����*///
///*��ע��*///
///************************************************************************///
uchar8 INF_WarmReset_7816_Card(uchar8 *P_CardNo)
{
	uchar8 p_temp[20];
	uchar8 v_temp;
	
	///*Card��λ*///
	DF_Switch_CardEn(C_Off);
	///*��ʱԼ2��ETU:datasheetҪ����ʱ400ʱ������*///
	SF_CardBaudRateTimerInit(C_Init,C_1_2_ETU);		///*0.5��etu��ʱ������*///
	SF_CardTimerDelay_N_ETU( 2 );
	
	///*Cardʹ��*///
	DF_Switch_CardEn(C_On);
	
	///*���ڽ���ʹ��*///
	//InF_CommUart_RecEnableForDispatch( C_Card );
	
	//__disable_irq();
    DisIRQ_ExceptETIM4();
	v_temp = SF_ReceiveDataFromCard(&p_temp[0],C_Esam_Len_ResetAck);				///*���ո�λ���13�ֽ�*///
	//__enable_irq();
	EnIRQ_ExceptETIM4();
	PF_CopyDataBytes(&p_temp[5],P_CardNo,C_Len_SerialNumber);
	///*�жϸ�λ�����5�ֽ�:3b 69 00 00 41/43����ȷ��CARD�޹���*///
	//if( (p_temp[0] == C_FirstByte_ATR) && (p_temp[1] == C_SecondByte_ATR)
	//	&& (p_temp[2] == C_ThirdByte_ATR) && (p_temp[3] == C_FourthByte_ATR)
	//	&& ((p_temp[4] == C_FifthByte_ATR41) || (p_temp[4] == C_FifthByte_ATR43)))
	//{
	//	///*���������кŴ���*///
	//	PF_CopyDataBytes(&p_temp[5],P_CardNo,C_Len_SerialNumber);
	//	v_temp = C_OK;
	//}
	//else	///*����ȷ��CARD����*///
	//{
	//	v_temp = C_Error;
	//}
	return v_temp;
}

///************************************************************************///
///*����ԭ��:uchar8 INF_ColdReset_7816_Card(uchar8 *P_CardNo)
///*����������ʵ��Card���临λ*///
///*���������*P_CardNo:�����кŴ�ŵ�ַ*///
///*���������CARD�����к�:������������ݴ���ڵ͵�ַ����8�ֽ�*///
///*���ز�����C_OK����λ�ɹ���C_Error����λʧ�ܣ��쳣�忨֮�ࣩ*///
///*�������ܣ�*///
///*����ʱ���������ȼ�⵽�忨���������Ϸ���Ϣ����ȫģ�飬��ȫģ����ñ������Կ������临λ*///
///*��    ע������Դ��������ʱ�ӣ�ƽʱ�رղ���������⵽�忨��Կ������临λ��*///
///*		  ����Դ/��ʱ��ʹ�ܣ���������ɺ���Ҫͣ���������Ϊ�˽��ͳ�̬�µ��ܱ��EMI��*///
///************************************************************************///
uchar8 INF_ColdReset_7816_Card(uchar8 *P_CardNo)
{
	uchar8 V_ucBuffer[20];
	uchar8 v_return;
	
	
	///*��cardͣ��*///
	InF_Deactivation_7816_Card();
	
	SF_CardBaudRateTimerInit(C_Init,C_1_2_ETU);		///*0.5��etu��ʱ������*///
	///*��ʱԼ10ms:Լ100ETU*///
//	SwitchOn_TripLed();
	SF_CardTimerDelay_N_ETU( 100 );
//	SwitchOff_TripLed();
	///*�򿪵�Դ*///
	DF_Switch_CardPower(C_On);
	///*��ʱԼ5ms��Լ48ETU*///
	SF_CardTimerDelay_N_ETU( 48 );

	///*cardʱ��ʹ��*///
	DF_Switch_CardSck(C_On);
	

	///*��ʱԼ5ms��Լ48ETU*///
	SF_CardTimerDelay_N_ETU( 48 );
	//__disable_irq();
    DisIRQ_ExceptETIM4();
	///*card��λ*///
	DF_Switch_CardEn(C_On); 
	
//	__disable_irq();
	v_return = SF_ReceiveDataFromCard(&V_ucBuffer[0],C_Esam_Len_ResetAck);				///*���ո�λ���13�ֽ�*///
//	__enable_irq();
	EnIRQ_ExceptETIM4();
	if( v_return == C_OK )				///*��ȡ�ɹ������������к�*///
	{
		PF_CopyDataBytes(&V_ucBuffer[5],P_CardNo,C_Len_SerialNumber);
	}
	///*�жϸ�λ�����5�ֽ�:3b 69 00 00 41/43����ȷ��CARD�޹���*///
	//if( (V_ucBuffer[0] == C_FirstByte_ATR) && (V_ucBuffer[1] == C_SecondByte_ATR)
	//	&& (V_ucBuffer[2] == C_ThirdByte_ATR) && (V_ucBuffer[3] == C_FourthByte_ATR)
	//	&& ((V_ucBuffer[4] == C_FifthByte_ATR41) || (V_ucBuffer[4] == C_FifthByte_ATR43)))
	//{
	//	///*��card���кŴ���*///
	//	///*���������кŴ���*///
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
///*����ԭ�ͣ�ushort16 INF_SendData_7816_Card(uchar8*P_SendBuffer,uchar8 V _DataLen,uchar8 *pResponse,uchar8 *pMaxResponseLen)*///
///*�������ܣ�����ȫģ�鴫�������ݷ��͸�card������card��Ӧ�����ݺ����ݳ��ȡ�*///
///*���������P_SendBuffer�����������ݵ��׵�ַ��*///
///*		  V _DataLen����Ŵ��������ݳ���;*///
///*		  pResponse �������Ӧ���ݵ��׵�ַ*///
///*		  pMaxResponseLen�����ڴ����Ӧ������󳤶ȵĵ�ַ�����Ȳ�����SW1/SW2��*///
///*ע1��	�����ڲ�����ʱ����ֱ�Ӷ����������������Ӱ�����������*///
///*ע2��	*P_SendBuffer ��*pResponse���Ը��ã�ָ��ͬһ������������������ʱ������ָ��Ӧ��ȡ�*///
///*�������������Ӧ����:������������ݴ���ڵ͵�ַ�����ݲ�����SW1/SW2*///
///*		  ����Ӧ���ݵĳ��ȣ����Ȳ�����SW1/SW2*///
///*���ز���������ֵΪ����SW1/SW2��SW1Ϊ���ֽڣ�������������쳣����C_Security_Err��ʾ�����쳣��*///
///*		        ΪC_Security_MaxLenErr��ʾ��󳤶ȴ���*///
///*��    ע���ӿ���ȡ���ݣ��߶��߽����ݷ��뵽pResponse����*///
///*�궨���б�*///
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
	///*���ô���*///
//	InF_InitCommUartForDispatch(C_Card,C_bps_2400,C_CommDataLen8,C_SerStp_2,C_parity_Even);

	InF_Delay_us(3000);
	///*ȡҪ���͵ĳ���*///
	V_TxDataLen = V_DataLen;
	///************************************************************************///
	///*�����Ҫ���͵ĳ��ȡ���CARD���ճ����ж�*///
	if( V_TxDataLen < C_Len_APDU_5 )
	{
		return C_Security_MaxLenErr;
	}
	else if( V_TxDataLen == C_Len_APDU_5 )				///*��5�ֽڣ����1�����2��Ӧ���ֽ���һ������*///
	{
		V_ResponseDataLen = P_SendBuffer_temp[C_Len_APDU_5-1] + C_Len_APDU_2;	///*���1�����2*///
	}
	else												///*������5�ֽ�*///
	{
		if( V_TxDataLen == (P_SendBuffer_temp[C_Len_APDU_5-1] +5) )
		{
			V_ResponseDataLen = C_Len_APDU_2;			///*���3*///
		}
		else if( V_TxDataLen == (P_SendBuffer_temp[C_Len_APDU_5-1] +6) )
		{
			V_ResponseDataLen = P_SendBuffer_temp[C_Len_APDU_5-1]+2;	///*���4*///
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
	///*��5�ֽڵ�����ͷ��CARD*///
	SF_SendDataToCard(P_SendBuffer_temp,C_Len_APDU_5);
	
	InF_SysTickDelay_1s();				///*��SysTick����Ϊ1s���*///
	while(1)
	{
		if( SF_ReceiveDataFromCard(&V_ucBuffer[0],1) != C_OK )	///*��һ���ֽ�*///
		{
			//__enable_irq();
            EnIRQ_ExceptETIM4();
			return C_Security_OverTime;
		}
		
		if( V_ucBuffer[0] == 0x60 )	///*��Ӧ��60������������ʱ*///
		{
			if( InF_JudgeDelay_1s() == C_Error )	///*�ж�9600ETU��ʱ�Ƿ�:1s*///
			{
				//__enable_irq();
                EnIRQ_ExceptETIM4();
				return C_Security_OverTime;
			}
		}
		else				///*��Ӧ������ݲ���60���˳�ѭ��*///
		{
			break;
		}
	}
	
	if( V_ucBuffer[0] != P_SendBuffer[1] )	///*��60�ҷ�INS,�����ж��Ƿ�ΪSW1/SW2*///
	{	///*����INS�����յ�����SW1���ٽ���1�����ݣ�SW2*///
		if( ((V_ucBuffer[0]&0xf0)==0x60) || ((V_ucBuffer[0]&0xf0)==0x90) )
		{
			if( SF_ReceiveDataFromCard(&V_ucBuffer[1],1) != C_OK )
			{
				v_temp = C_Security_OverTime;
			}
			else
			{
				///*SW1��SW2*///
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
		if( (V_DataLen-C_Len_APDU_5) > 0)				///*�ж��Ƿ���Ҫ��ʣ���ֽ�*///
		{
			SF_CardBaudRateTimerInit(C_Init,C_16_ETU);	///*��ʱ16��ETU*///
			while( !(CardBaudRateTimer->ETxIF & C_TimerStatus_OVIF_RESET))
			{
				;
			}
			SF_CardBaudRateTimerStop();
			
			SF_SendDataToCard(&P_SendBuffer_temp[C_Len_APDU_5],V_DataLen-C_Len_APDU_5);	///*����ʣ������*///
		}
		
		////if( SF_ReceiveDataFromEsam(&pResponse_temp[0],V_ResponseDataLen) != C_OK )	///*����ESAM���ص�����*///
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
				*pMaxResponseLen = V_ResponseDataLen-C_Len_APDU_2;		///*��������еĳ���*///

				///*�ж�SW1��SW2*///
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
///*����ԭ�� 	Card_InitBackUpBaseTimer
///*��������	�����رո��жϣ�����ر����ж�
///*�������	��
///*������� 	��
///*���ز���	��
///*ȫ�ֱ��� 	��
///*������ע	
///****************************************************************************///
void DisIRQ_ExceptETIM4(void)
{
  NVIC_DisableIRQ(LPTIM_IRQn);
  NVIC_DisableIRQ(ETIM1_IRQn);
  NVIC_DisableIRQ(ETIM2_IRQn);
  }
///****************************************************************************///
///*����ԭ�� 	EnIRQ_ExceptETIM4
///*��������	�����򿪸��жϣ���������ж�
///*�������	��
///*������� 	��
///*���ز���	��
///*ȫ�ֱ��� 	��
///*������ע	
///****************************************************************************///
void EnIRQ_ExceptETIM4(void)
{
  NVIC_EnableIRQ(LPTIM_IRQn);
  NVIC_EnableIRQ(ETIM1_IRQn);
  NVIC_EnableIRQ(ETIM2_IRQn);
}







