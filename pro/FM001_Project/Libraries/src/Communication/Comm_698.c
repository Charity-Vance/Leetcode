/*******************************************************************************
Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     Comm_698.c
Version:       V1
Author:        jiangzs
Date:          2016-8-21
Description:   ͨ�Ŵ��������ļ�
---------------------------------------------------------------------------------
History1:      ��1���޸�
����1. Date:   202109
   	   Author: LZY/FXY
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
#include "Comm_698.h"
#include "Communication.h"
#include "DI_698.h"
#include "SecurityCommunication.h"
#include "EventRecord.h"
uchar8 GV_NewReport1[C_NewReportLen + 2];					/*33201F01*/
uchar8 GV_NewReport2[C_NewReportLen + 2];					/*33201F02*/
uchar8 GV_NewReport3[C_NewReportLen + 2];					/*33201F03*/
uchar8 GV_MeterStatus81[CLDrive_Report_Mode + 2];			/*�������״̬��1*/
uchar8 GV_MeterStatus82[CLDrive_Report_Mode + 2];			/*�������״̬��2*/
uchar8 GV_MeterStatus83[CLDrive_Report_Mode + 2];			/*�������״̬��3*/
uchar8 GV_KeyHState[CLKey_State_698];						/*���ܱ���ʷ��Կ״̬��*/

/*2020��׼�����ϱ�2005*/
uchar8 GV_WriteReportFlag;									/*�ϱ��¼�д��*/
uchar8 GV_MeterStatusReportNO83[CLMeterStatusNum+2];		/*ģ��ͨ���ĵ������״̬�ֵ��¼����ϱ�����*/
uchar8 GV_ModuleCommuni_Flag;
uchar8 GV_RNByte;											/*RN�ڻ����е�λ��*/
uchar8 GV_NeedReport_PowerDown;								/*��������ϱ�*/

const ushort16 C_CommRxMaxLen[4]=							/*ÿ��ͨ����������ֽ���*/
{
	C_IRMaxLen,C_RS485_1MaxLen,C_RS485_2MaxLen,C_ModuleMaxLen
};

const Str_OtherEventMapping_Type OtherEventMappingTable[]=
{
	{C_ESAMErroEventNo,              1},					/*ESAM��*/
	{C_CardErrorEventNo,             2},					/*�ڿ���ʼ������*/
	{C_RTCBatLowVolEventNo,          3},					/*ʱ�ӵ�ص�ѹ��*/
	{C_ProgrammErrorEventNo,         4},					/*�ڲ��������*/
	{C_MemoryCorrEventNo,            5},					/*�洢����*/
	{C_PowerBatLowVolEventNo,        8},					/*ͣ�糬���ص�ѹ��*/
	{C_OverdraftEventNo,             9},					/*͸֧*/
	{C_RelayOpenEventNo,			 14},					/*��բ*/
	{C_RelayCloseEventNo,            15},					/*��բ*/
};
#define OtherEventMappingTable_Len  ( sizeof(OtherEventMappingTable) / sizeof(Str_OtherEventMapping_Type) )
extern void Dispatch_SendMessage(uchar8 MsgDerictAddr, uchar8 *P_Parameter, uchar8 ParameterLen);

#define C_ObjectNO_Len	5
const uchar8 C_ObjectNO[C_ObjectNO_Len] = {1, 2, 5, 7, 9};

#define C_RelatedOADBuf_Len	800								/*���ᡢ��¼���������б��ȡ����*/

extern uchar8 GV_ESAMAction9_SIDP1P2;

/*******************************************************************************
����ԭ�ͣ�uchar8 SF_GetReportOI(uchar8 *P_Buf,uchar8 *P_NumOI,uchar8 V_Len)
������������ȡ33200300�����ݣ������ϱ������¼���OI�б�
���������   V_Len����󳤶ȣ�
���������   P_Buf��OI�б�P_NumOI��OI������
���ز��������Ϊ���󣬱�ʾ�����������С��
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_GetReportOI(uchar8 *P_Buf, uchar8 *P_NumOI, uchar8 V_Len)
{
	uchar8	 i, j = 0, V_Mode = 0;
	ushort16 V_DataLen = CLLossVolage_Report_Mode, V_ucDataLen = 0, V_usDataEncode;
	uchar8	 V_ucDataTemp = 0;
	ulong32	 V_OADTemp;

	for( i = 0; i < Str_698EventReport_Len; i++ )						/*ȷ����Ӧ�¼�*/
	{
		if( Str_698EventReport[i].StatusBit == 0x01 )					/*��Ҫ�ж��ϱ�ģʽ��*/
		{
			if( Str_698EventReport[i].EventNo == C_ACPowerFailEventNo )	/*������Դ����*/
			{
				V_ucDataLen = CLAuxi_Power_Sign;
				if( ( InF_Read_Data( CAuxi_Power_Sign, &V_ucDataTemp, &V_ucDataLen, &V_usDataEncode) != C_OK )
				 || ( V_ucDataTemp == C_NoACPowerFail ) )
				{
					continue;
				}
			}
			if( Str_698EventReport[i].EventNo == C_NeutralCurrentAbnormalEventNo )		/*���ߵ�������*/
			{
				V_ucDataLen = CLZero_Current_Sign;
				if( InF_Read_Data( CZero_Current_Sign, &V_ucDataTemp, &V_ucDataLen, &V_usDataEncode) == C_OK )
				{
					if( V_ucDataTemp == C_ZeroCurrentOff )
					{
						continue;
					}
				}
			}
			if( ( Str_698EventReport[i].EventNo == C_RelayOpenEventNo )			/*��բ*/
			 || ( Str_698EventReport[i].EventNo == C_RelayCloseEventNo )		/*��բ*/
			 || ( Str_698EventReport[i].EventNo == C_RelayFaEndEnEventNo ) )	/*���ɿ�������*/
			{
				if( C_Meter_Type == C_SmartMeter )								/*���ܱ�������բ����*/
				{
					continue;
				}
			}

			if( ( Str_698EventReport[i].EventNo == C_ProgTParaEventNo )			/*���ʲ�������*/
			 || ( Str_698EventReport[i].EventNo == C_ProgLadEventNo )			/*���ݱ���*/
			 || ( Str_698EventReport[i].EventNo == C_AbnorCEventNo )			/*�쳣�忨*/
			 || ( Str_698EventReport[i].EventNo == C_BuyCurrEventNo )			/*����*/
			 || ( Str_698EventReport[i].EventNo == C_ReturnMoneyEventNo ) )		/*�˷�*/
			{
				if( C_Meter_Type != C_L_SmartMeter )							/*Զ�̺����ܱ���������*/
				{
					continue;
				}
			}

			V_OADTemp = Inf_GetEventModeDI( i, C_ReportMode );
			InF_Read_Data( V_OADTemp, &V_Mode, &V_DataLen, &V_usDataEncode);					/*��ģʽ��*/
			if( ( V_Mode == 1 ) || ( V_Mode == 2 ) || ( V_Mode == 3 ) )
			{
				if( ( ( j + 1 ) * 2 ) > V_Len )
				{
					return C_OtherErr_DAR;
				}
				P_Buf[j*2] = 0x30;
				P_Buf[j*2+1] = (uchar8)(Str_698EventReport[i].OIBANature >> 8);
				*P_NumOI = j + 1;
				j++;
		    }
		}
	}
	if(j == 0) /*���鲻���������Ҫ��ֵ0,Ҳ����û����Ҫ�ϱ����б������Բ鵽����������Ѿ�����*/
	{
		*P_NumOI = 0;
	}

    return C_OK_DAR;
}
/*******************************************************************************
����ԭ�ͣ�void Inf_CleanAllMeterStatus8(void)
����������������¼�����ʱ���ã���������״̬��8
���������
���������   ��
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
void Inf_CleanAllMeterStatus8(void)
{
    ushort16    V_CRC;

    memset(GV_MeterStatus81,0x00,CLDrive_Report_State+2);
    V_CRC=PF_Cal_CRC_698(GV_MeterStatus81,CLDrive_Report_State);
    PF_Ushort16ToBuffer2(&GV_MeterStatus81[CLDrive_Report_Mode],&V_CRC);

    memset(GV_MeterStatus82,0x00,CLDrive_Report_State+2);
    V_CRC=PF_Cal_CRC_698(GV_MeterStatus82,CLDrive_Report_State);
    PF_Ushort16ToBuffer2(&GV_MeterStatus82[CLDrive_Report_Mode],&V_CRC);

    memset(GV_MeterStatus83,0x00,CLDrive_Report_State+2);
    V_CRC=PF_Cal_CRC_698(GV_MeterStatus83,CLDrive_Report_State);
    PF_Ushort16ToBuffer2(&GV_MeterStatus83[CLDrive_Report_Mode],&V_CRC);

    /*2020��׼�����ϱ�2005*/
    memset(GV_MeterStatusReportNO83,0x00,CLMeterStatusNum+2);
    V_CRC=PF_Cal_CRC_698(GV_MeterStatusReportNO83,CLMeterStatusNum);
    PF_Ushort16ToBuffer2(&GV_MeterStatusReportNO83[CLMeterStatusNum],&V_CRC);
}
/*******************************************************************************
����ԭ�ͣ�uchar8	InF_OtherEventOADFind(uchar8 V_EventNo)
�����������������ݱ�ʾ�����¼��ڵ������״̬���е�bit�����¼���¼��ͨ��ģ����
���������V_EventNo���¼���
���������   ��
���ز�����V_Bit��C_BitError������¼�λ����������Ŀǰ���ڵ��¼�λ
����λ�ã�
��    ע������д�����ϱ�״̬��8ʱ�ж�����һλ
*******************************************************************************/
uchar8 InF_OtherEventOADFind(uchar8 V_EventNo)
{
    uchar8  V_i, V_Bit;
    Str_OtherEventMapping_Type	*pV_Test;

	V_Bit = C_BitError;
	for( V_i = 0; V_i < OtherEventMappingTable_Len; V_i++)
	{
		pV_Test = (Str_OtherEventMapping_Type	*)&OtherEventMappingTable[V_i];
		if( V_EventNo == pV_Test->EventNo )
		{
			V_Bit = pV_Test->WriteBit;
			break;
		}
	}
	return V_Bit;
}
/*******************************************************************************
����ԭ�ͣ�uchar8  Inf_GetMeter8(uchar8 V_EventNo)
��������������ͨ�����ر�ͨ���ĸ����ϱ�״̬��8���ϱ����ͣ����滹�����������Ƿ���Ҫ�����ϱ�
���������V_Channel��ͨ���ţ�  V_ucBufLen�������ݻ��棬��С4���ֽڣ�  ReportType���ϱ����ͣ�
			 P_Numdata����ͨ�������б�Ŀǰû���õ�����NumLen�������ϱ�����
���������*P_Data����������
���ز�����uchar8��EventNum,C_IDError
����λ�ã�
��    ע���¼���¼ģ�飬���ڻ�ȡNum�ţ�ͨ��ģ�������жϱ�ʶ���Ƿ���ȷ
*******************************************************************************/
uchar8  Inf_GetMeter8(uchar8 V_Channel, uchar8 *P_Data, uchar8 V_ucBufLen, uchar8 ReportType, uchar8 *P_Numdata, uchar8 *NumLen)
{
	uchar8      *V_ChannelTemp, V_Temp = C_OtherErr_DAR;
	ushort16    V_CRC, V_DataLen, V_usDataEncode;
	uchar8      i, V_Type = 0;

	if(V_ucBufLen >= 4)
	{
		switch(V_Channel)
		{
			case	C_ReportChannel1:
					V_ChannelTemp = GV_MeterStatus81;
					break;
			case	C_ReportChannel2:
					V_ChannelTemp = GV_MeterStatus82;
					break;
			case	C_ReportChannel3:
					V_ChannelTemp = GV_MeterStatus83;
					break;
			default:
					return C_Error;
		}

		if( PF_Check_CRC_698( V_ChannelTemp, CLDrive_Report_State + 2 ) == C_OK )
		{
			if( Is_Buf_AllZero( V_ChannelTemp, CLDrive_Report_State ) != C_OK )
			{
				V_DataLen = CLReport_Type;
				InF_Read_Data(CDrive_Report_Type, &V_Type, &V_DataLen, &V_usDataEncode);

				if( ReportType == C_ActiveReportFlag )            		/*����Ǵ��������ϱ�*/
				{
					if( C_ActiveReportType == V_Type )					/*����ϱ������������ϱ�*/
					{
						if( V_Channel == C_Module )						/*����������ϱ�������ģ��ͨ���ͷ���OK*/
						{
							V_Temp = C_ActiveReportType;
						}
					}
				}
				else
				{
					if( C_FollowReportType == V_Type )					/*����Ǹ����ϱ�*/
					{
						V_Temp = C_FollowReportType;
					}
				}
			}
		}
		else
		{
			memset( V_ChannelTemp, 0x00, CLDrive_Report_State );
			V_CRC=PF_Cal_CRC_698( V_ChannelTemp, CLDrive_Report_State );
			PF_Ushort16ToBuffer2( V_ChannelTemp + CLDrive_Report_State, &V_CRC );

			/*2020��׼�����ϱ�2005*/
			if( ReportType == C_ActiveReportFlag )
			{
				memset( GV_MeterStatusReportNO83, 0x00, CLMeterStatusNum + 2 );
				V_CRC = PF_Cal_CRC_698( GV_MeterStatusReportNO83, CLMeterStatusNum );
				PF_Ushort16ToBuffer2( &GV_MeterStatusReportNO83[CLMeterStatusNum], &V_CRC);
			}
		}

		if( ReportType == C_ActiveReportFlag )
		{
			PF_CopyDataBytes_698( GV_MeterStatusReportNO83,   P_Numdata, CLMeterStatusNum );
			for( i = 0; i < CLMeterStatusNum; i++ )
			{
				if( ( *(GV_MeterStatusReportNO83 + i ) ) > C_ActiveReportMaxNum )
				{
					*( GV_MeterStatusReportNO83 + i ) = 0;
				}
				if( ( *(GV_MeterStatusReportNO83 + i ) ) > 0 )
				{
					( *(GV_MeterStatusReportNO83 + i) )--;
					(*NumLen)++;
				}
			}
			V_CRC = PF_Cal_CRC_698( GV_MeterStatusReportNO83, CLMeterStatusNum );
			PF_Ushort16ToBuffer2( &GV_MeterStatusReportNO83[CLMeterStatusNum], &V_CRC );
		}
		PF_CopyDataBytes_698(V_ChannelTemp, P_Data, CLDrive_Report_State);
	}
	return V_Temp;
}
/*******************************************************************************
����ԭ�ͣ�void Inf_WriteMeterStatus8(uchar8 EventNo)
�����������¼�����ʱд�����ϱ����
���������EventNo���¼���
			State��C_Happen_EventMsg �¼���������
�����������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
void Inf_WriteMeterStatus8(uchar8 EventNo)
{
	uchar8		V_EventBit, V_MeterMode[CLDrive_Report_Mode + 2] = {0}, V_BufferLen1 = 1;
	uchar8		V_MeterMode8[(CLDrive_Report_Mode + 2)];
    ulong32		V_ValueTemp = 0, V_StateTemp = 0, V_MeterMode8Temp;
    ushort16	V_CRC, V_BufferLen2 = CLDrive_Report_Mode, V_usDataEncode;
    uchar8		*pMeterStatus8;

	if( ( InF_Read_Data( CDrive_Report_Mode, V_MeterMode8, &V_BufferLen2, &V_usDataEncode ) != C_OK )
	  ||( Is_Buf_AllZero( V_MeterMode8, CLDrive_Report_Mode ) == C_OK ) )
	{
		return;
	}
	V_MeterMode[0]=C_bit_string;
	SF_DataExchangeTo698_BasicData( V_MeterMode, V_MeterMode8, 32, CLDrive_Report_Mode );

	V_EventBit = InF_OtherEventOADFind(EventNo);
	if(V_EventBit == C_BitError)
	{
		return;
	}
	V_MeterMode8Temp = PF_Buffer4ToUlong32_698(V_MeterMode8);
	V_StateTemp = 0x80000000 >> V_EventBit;
	V_MeterMode8Temp = V_MeterMode8Temp & V_StateTemp;            /*�Ƿ���Ҫд�ϱ�״̬��*/
	if( V_MeterMode8Temp != 0 )
	{
    	for( V_BufferLen1 = C_ReportChannel1; V_BufferLen1 < C_ReportChannel3; V_BufferLen1++ )
    	{
    		switch(V_BufferLen1)
    		{
    			case C_ReportChannel1:
    				pMeterStatus8 = GV_MeterStatus81;
    				break;
    			case C_ReportChannel2:
    				pMeterStatus8 = GV_MeterStatus82;
    				break;
    			case C_ReportChannel3:
    				pMeterStatus8 = GV_MeterStatus83;
    				break;
				default:
					continue;
    		}
			if( PF_Check_CRC_698( pMeterStatus8, CLDrive_Report_State + 2 ) == C_OK )		/*�����Ӧ�ĵ������״̬��crc���ԣ�ֱ�Ӹ�ֵ0*/
			{
				V_ValueTemp = PF_Buffer4ToUlong32_698(pMeterStatus8);
			}
			V_ValueTemp = V_ValueTemp | V_StateTemp;										/*�����Ӧλģʽ�ֲ�Ϊ0���õ������״̬��*/
			PF_Ulong32ToBuffer4_698( pMeterStatus8, &V_ValueTemp, CLDrive_Report_State );
			V_CRC = PF_Cal_CRC_698( pMeterStatus8, CLDrive_Report_State );
			PF_Ushort16ToBuffer2( &pMeterStatus8[CLDrive_Report_State], &V_CRC );

		/*2020��׼�����ϱ�2005*/
			if( V_BufferLen1 == C_ReportChannel3 )
			{
				memset( (GV_MeterStatusReportNO83 + V_EventBit), C_ActiveReportMaxNum, 1);	/*��Ӧ���ֽ��������ϱ�����*/
				V_CRC=PF_Cal_CRC_698( GV_MeterStatusReportNO83, CLMeterStatusNum );
				PF_Ushort16ToBuffer2( &GV_MeterStatusReportNO83[CLMeterStatusNum], &V_CRC );
			}
		}
	}
}
/*******************************************************************************
����ԭ�ͣ�void Inf_CleanMeterStatus8(uchar8 *P_Confirma,uchar8 V_Channel)
��������������������״̬��8
���������P_Confirma���������״̬��8��7F���� �� V_Channel��ͨ����
�����������
���ز�����
����λ�ã�
��    ע����ͨ�����·�����������
*******************************************************************************/
void Inf_CleanMeterStatus8(uchar8 *P_Confirma, uchar8 V_Channel)
{
	uchar8      *V_ChannelTemp;
	ulong32     V_ChannelData,V_ConfirmaTemp;
	ushort16    V_CRC;

    V_ConfirmaTemp = PF_Buffer4ToUlong32_698(P_Confirma);							 /*ȷ���ϱ�״̬��*/
	if(V_ConfirmaTemp != 0)
	{
		switch(V_Channel)
		{
			case    C_ReportChannel1:
					V_ChannelTemp = GV_MeterStatus81;
					break;
			case    C_ReportChannel2:
					V_ChannelTemp = GV_MeterStatus82;
					break;
			case    C_ReportChannel3:
					V_ChannelTemp = GV_MeterStatus83;
					break;
			default:
		        return;
		}
		if( PF_Check_CRC_698( V_ChannelTemp, CLDrive_Report_State + 2 ) != C_OK )	/*�����Ӧ�ĵ������״̬��crc���ԣ�ֱ�Ӹ�ֵ0*/
		{
			memset( V_ChannelTemp, 0x00, CLDrive_Report_State + 2 );
		}
		V_ChannelData = PF_Buffer4ToUlong32_698( V_ChannelTemp );
		V_ChannelData = V_ChannelData & ( ~V_ConfirmaTemp );
		PF_Ulong32ToBuffer4_698( V_ChannelTemp, &V_ChannelData, CLDrive_Report_State );
		V_CRC = PF_Cal_CRC_698( V_ChannelTemp, CLDrive_Report_State );
		PF_Ushort16ToBuffer2( &V_ChannelTemp[CLDrive_Report_State], &V_CRC );
	}
}
/*******************************************************************************
����ԭ�ͣ� Inf_CleanMeterStatus8_Relay
���������� ��645�ϱ�ʱ��698��״̬��8
��������� EventNo���¼���
��������� ��
���ز����� ��
����λ��:
��    ע��
*******************************************************************************/
void Inf_CleanMeterStatus8_Relay(uchar8 EventNo)
{
	uchar8 C_MeterStatus8[CLDrive_Report_Mode] = {0};

	if(EventNo == C_RelayOpenEventNo)
	{
		C_MeterStatus8[C_MeterStatus_RelayWord_Offset] = 0x02;
	}
	else if(EventNo == C_RelayCloseEventNo)           	/*��բ*/
	{
		C_MeterStatus8[C_MeterStatus_RelayWord_Offset] = 0x01;
	}
	else if(EventNo == C_PowerBatLowVolEventNo)
	{
		C_MeterStatus8[C_MeterStatus_RelayWord_Offset] = 0x80;
	}
	else                  								/*C_RTCBatLowVolEventNo*/
	{
		C_MeterStatus8[C_MeterStatus_RelayWord_Offset - 1] = 0x10;
	}

	Inf_CleanMeterStatus8(C_MeterStatus8, C_ReportChannel1);
	Inf_CleanMeterStatus8(C_MeterStatus8, C_ReportChannel2);
	Inf_CleanMeterStatus8(C_MeterStatus8, C_ReportChannel3);
}
/*******************************************************************************
����ԭ�ͣ�uchar8 InF_GETListData(uchar8 Channel,uchar8 *P_NumOAD,uchar8 *P_EventNo,uchar8 Len,
			uchar8 *P_RemainReportNO,uchar8 *P_RemainReportNum,uchar8 ReportType)
������������ȡ�ϱ��б��OAD��OI
���������      P_NumOAD��OAD�б�      P_EventNo���¼����б�  Len��������С���ȣ�
�����������
���ز�����������Ȳ�������ͨ���Ų��ԣ����ش���
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 InF_GETListData(uchar8 Channel, uchar8 *P_NumOAD, uchar8 *P_EventNo, uchar8 Len, uchar8 *P_RemainReportNO, uchar8 *P_RemainReportNum, uchar8 ReportType)
{
	uchar8      *P_NoTemp, V_Num;
	ushort16    V_Crc;

	*P_RemainReportNum = 0;
	*P_NumOAD = 0;
	if( ( Channel == C_ReportChannelAll ) || ( Len < C_NewReportMaxNum ) )
	{
		return C_OtherErr_DAR;
	}
	switch(Channel)
	{
		case	C_ReportChannel1:
				P_NoTemp = &GV_NewReport1[0];
				break;
		case	C_ReportChannel2:
				P_NoTemp = &GV_NewReport2[0];
				break;
		case	C_ReportChannel3:
				P_NoTemp = &GV_NewReport3[0];
				break;
		default:
				return C_ObjectNotExist_DAR;      					/*����δ����*/
	}

	if( ( PF_Check_CRC( P_NoTemp, C_NewReportLen + 2 ) != C_OK ) || ( ( *( P_NoTemp + C_NewReportNumByte ) > Len ) ) )
	{
		*P_RemainReportNum = 0;
		*P_NumOAD = 0;
		memset( P_NoTemp, 0x00, C_NewReportCRCLen );
		V_Crc = PF_Cal_CRC( P_NoTemp, C_NewReportLen );
		PF_Ushort16ToBuffer2( P_NoTemp + C_NewReportLen, &V_Crc );
	}
	else
	{
		for( V_Num = 0; V_Num < ( *(P_NoTemp + C_NewReportNumByte ) ); V_Num++ )
		{
			if(C_ActiveReportFlag == ReportType)									/*��ȡ���������ϱ�*/
			{
				if( ( C_ActiveReportType == ( *(P_NoTemp + V_Num * 3 + 2) ) ) )		/*ÿ���ϱ��ĸ�ʽΪEVENTNO+����+����*/
				{
					*(P_EventNo + (*P_NumOAD) ) = *(P_NoTemp + V_Num * 3 );
					*(P_RemainReportNO + V_Num ) = *(P_NoTemp + 1 + V_Num * 3 );	/*ʣ���ϱ�����*/
					if( ( *(P_RemainReportNO + V_Num ) ) != 0 )
					{
						(*P_RemainReportNum)++;
					}
					(*P_NumOAD)++;
				}
			}
			else if( C_NoActiveReportFlag == ReportType )							/*��ȡ���Ǹ����ϱ�*/
			{
				if( ( C_FollowReportType == ( *(P_NoTemp + V_Num * 3 + 2 ) ) ) )
				{
					*(P_EventNo + (*P_NumOAD ) ) = *( P_NoTemp + V_Num * 3 );
					(*P_NumOAD)++;
				}
			}
			else
			{
				*(P_EventNo + (*P_NumOAD) ) = *(P_NoTemp + V_Num * 3 );				/*�������ϱ��б�*/
				(*P_NumOAD)++;
			}
		}
		if( (*P_RemainReportNum) != 0 )
		{
			Inf_DealReportNum( P_NoTemp, V_Num );
			V_Crc = PF_Cal_CRC( P_NoTemp, C_NewReportLen );
			PF_Ushort16ToBuffer2( P_NoTemp + C_NewReportLen, &V_Crc );
		}
	}
	return C_OK;
}
/*******************************************************************************
����ԭ�ͣ� Inf_EventReport_Sign
���������� ������ʱд�����ϱ����
��������� Type������¼�ͻ��Ƕ��������ݣ��¼���   CommChannel:ͨ����  EventNo���¼���  ��ReportType���ϱ�����
��������� ��
���ز����� ��
����λ��:
��    ע��
*******************************************************************************/
void Inf_EventReport_Sign(uchar8 Type, uchar8 CommChannel, uchar8 EventNo, uchar8 ReportType)
{
    uchar8	i, V_NumOAD, V_EventNo[C_NewReportMaxNum], V_RemainReportNO[C_NewReportMaxNum], V_RemainReportNum;

    if(InF_GETListData(CommChannel, &V_NumOAD, V_EventNo, C_NewReportMaxNum, V_RemainReportNO, &V_RemainReportNum, Type) != C_OK)
    {
        return;
    }
    if(Type == C_ReadRecord)                /*����¼����ж�OAD��������ֱ���ϱ�*/
    {
        for(i = 0; i < V_NumOAD; i++)
        {
            if(EventNo == V_EventNo[i])     /*��������¼����б����¼���ͬ��ֱ��ɾ��*/
            {
                Inf_ReportList(CommChannel, V_EventNo[i], C_DeletReport);
				SF_Clear645_ReportNewAddNum(V_EventNo[i], C_ReadRecord);		/*��645�ϱ�*/
            }
        }
#if 0		/*���չ���Ҫ�����Ӧ��Ҳ���Բ�Ӧ������֮ǰ�������ǲ�Ӧ�������ٱ�עһ��*/
        if( ( EventNo == C_PowerfailEventNo ) && ( CommChannel == C_Module ) )
        {
            Inf_Event_REPORTONumDeal(0);      /*������ʱ��������������Ϊ���緢������дlist����������Ҫ����һ��*/
        }
#endif
    }
}
/*******************************************************************************
����ԭ�ͣ�uchar8 Inf_ReportGetEventNo(Str_Comm_698_RW *pV_698RWPara,uchar8 *V_ReadSign,uchar8 *V_EventNo,uchar8 *V_OADNum)
�������������ݱ�ʶ����ߵ�ǰ�����Ƿ�Ϊ��¼�ͣ�����Ǽ�¼�ͣ������¼���
���������pV_698RWPara��ͨ�����ݣ�
���������V_ReadSign����¼�ͻ����������ͣ�V_EventNo���¼��ţ�V_OADNum���¼�������
���ز�����C_ReadOther����ȡ�������ͣ�C_OK���������¼���¼��
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 Inf_ReportGetEventNo(Str_Comm_698_RW *pV_698RWPara, uchar8 *V_ReadSign, uchar8 *V_EventNo, uchar8 *V_OADNum)
{
    uchar8		V_645DINum, i, j, V_Result, V_Flag;
    ulong32     OAD;
    Str_Type645DI_Class V_DIFor645[2];

    *V_ReadSign = C_ReadOther;
    *V_OADNum = 0;

	if( ( pV_698RWPara->ServiceFlag_First == C_GET_Request )
	&& ( ( pV_698RWPara->ServiceFlag_Second == C_GETRecord_Request ) || ( pV_698RWPara->ServiceFlag_Second == C_GETRecordList_Request ) ) )
	{
		OAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD;
		V_Result = SF_Judge_OINature( pV_698RWPara, V_DIFor645, &V_645DINum, C_Read );		/*����������*/

		for( j = 0; j < C_Event_OIBTableLen; j++ )
		{
			if( ( (ushort16)(OAD >> 16) ) == ( (Event_OIBTable[j].OIB) | 0x3000 ) )
			{
				V_Flag = Event_OIBTable[j].TypeClass;										/*7���24��*/
				break;
			}
		}
		if( ( j < C_Event_OIBTableLen ) && ( V_Result ==C_OK ) )
		{
			if( ( ( V_Flag == C_SplitPhaseEvent_Class ) && ( ( (uchar8)( (OAD >> 8 ) ) == C_SplitPhaseEvent_6Attri )
			|| ( (uchar8)( ( OAD >> 8 ) ) == C_SplitPhaseEvent_7Attri ) || ( (uchar8)( ( OAD >>8 ) ) == C_SplitPhaseEvent_8Attri ) || ( (uchar8)( ( OAD >> 8 ) ) == C_SplitPhaseEvent_9Attri ) ) )
			|| ( (V_Flag == C_Event_Class) && ( ( (uchar8)( ( OAD >> 8 ) ) == C_Event_2Attri ) ) ) )/*�¼���¼��������¼*/
			{
				for( i = 0; i < Str_698EventReport_Len; i++)
				{
					if( ( (ushort16)( OAD >> 8 ) ) == Str_698EventReport[i].OIBANature )
					{
						break;
					}
				}
				if(i < Str_698EventReport_Len)
				{
					*V_ReadSign = C_ReadRecord;
					*V_EventNo = Str_698EventReport[i].EventNo;
					*V_OADNum = 1;
				}
			}
		}
	}
	return C_OK;
}
/*******************************************************************************
����ԭ�ͣ�void SF_GetErrorNo(uchar8 *ReturnFlag)
������������ȡ�������ͣ���645��������תΪ698
���������
������������Լ��������͵ģ�  	        C_OtherErr_DAR:��������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
void SF_GetErrorNo(uchar8 *ReturnFlag)
{
	uchar8 k;

	for( k = 0; k < GV_698And645_ErrSwichLen; k++ )
	{
		if(*ReturnFlag <= C_ESAMLCError)
		{
			break;
		}
		if( *ReturnFlag == GV_698And645_ErrSwich[k].Err_645 )
		{
			*ReturnFlag = GV_698And645_ErrSwich[k].Err_698;
			break;
		}
	}
	if( k == GV_698And645_ErrSwichLen )
	{
		*ReturnFlag = C_OtherErr_DAR;
	}
}
/*******************************************************************************
����ԭ�ͣ�uchar8 GetCommMeterAddressType_698(uchar8 *P_Addr,ushort16 *P_AddrLen)
����������ͨ��ģ��ͨ�ŵ�ַ�ж�
���������ͨ�ŵ�ַ�׵�ַ
���������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 GetCommMeterAddressType_698(uchar8 *P_Addr, ushort16 *P_AddrLen)
{
	uchar8   V_AddrType;
	ushort16 i, V_AddrLen, V_usDataEncode;
	uchar8   V_ANum;
	uchar8   V_Addr[16];

	V_AddrType = P_Addr[0] & C_AddrTpyeBits;
	V_AddrLen = ( P_Addr[0] & C_AddrLenBits ) + 1;

	*P_AddrLen = V_AddrLen;
	if((P_Addr[0]&C_LogicAddrBits) != 0)
	{
		return C_AdrressError;
	}

	if(C_AddrTypePtoAll == V_AddrType)			/*�㲥��ַ*/
	{
		for( i = 0; i < V_AddrLen; i++ )
		{
			if( P_Addr[1 + i] != 0xAA )
			{
				return C_AdrressError;
			}
		}
	}
	else if( C_AddrTypePtoM == V_AddrType )		/*�鲥��ַ*/
	{
		i = 16;
		if( InF_Read_Data( CMulticastAddr, V_Addr, &i, &V_usDataEncode ) != C_OK )								/*��ȡ�鲥��ַ:40050200*/
		{
			return C_AdrressError;
		}
		if( PF_Campare_Data( &P_Addr[1], V_Addr, V_AddrLen ) != C_Equal )
		{
			return C_AdrressError;
		}
	}
	else	/*ͨ���ַ���ߵ�����ַ*/
	{
		i = 16;
		if( ( InF_Read_Data( CComm_Address, V_Addr, &i, &V_usDataEncode ) != C_OK ) || ( i != V_AddrLen ) )		/*��ȡͨ�ŵ�ַ:40010200*/
		{
			return C_AdrressError;
		}
		V_ANum = 0;
		for( i = 0; i < V_AddrLen; i++ )
		{
			if( ( ( P_Addr[1 + i] & 0x0F ) == ( V_Addr[i] & 0x0F ) ) || ( ( P_Addr[1 + i] & 0x0F ) == 0x0A ) )
			{
				if( ( P_Addr[1 + i] & 0x0F ) == 0x0A )
				{
					V_ANum += 1;
				}
			}
			else
			{
				return C_AdrressError;
			}
            if( ( ( P_Addr[1 + i] & 0xF0 ) == ( V_Addr[i] & 0xF0 ) ) || ( ( P_Addr[1 + i] & 0xF0 ) ) == 0xA0 )
			{
				if( ( P_Addr[1 + i] & 0xF0 ) == 0xA0 )
				{
					V_ANum += 1;
				}
			}
			else
			{
				return C_AdrressError;
			}

		}
		if( V_ANum == 0 )							/*������ַ*/
		{
			if( V_AddrType != C_AddrTypePtoP )
			{
				return C_AdrressError;
			}
		}
		else										/*ͨ���ַ*/
		{
			if( V_AddrType != C_AddrTypePtoX )
			{
				return C_AdrressError;
			}

			for( i = 0; i < V_AddrLen; i++ )    	/*ͨ���ַ���Ȱѵ�ַ��ֵΪʵ�ʵ�ַ*/
			{
				P_Addr[1 + i] = V_Addr[i];
			}
		}
	}
    P_Addr[0] = P_Addr[0] & 0x3F | C_AddrTypePtoP;	/*�ĳɵ�����ַ*/
	return V_AddrType;
}
/*******************************************************************************
����ԭ�ͣ� uchar8	IfFrameOkSetV_698Frame(Str_Comm_645 *pV_698Frame,Str_Comm_Parm *pStr_Comm_Parm_Address)
������������֡�Ϸ����ж�:����ͨ�ŵ�ַ�жϡ�֡���ȡ�֡FCS�ж�
���������֡�����ṹ���ַ��ͨ�Ż���ṹ���ַ
���������֡�Ƿ�Ϸ�
���ز�����
����λ�ã�
��	ע��
*******************************************************************************/
 uchar8	IfFrameOkSetV_698Frame(Str_Comm_645 *pV_698Frame, Str_Comm_Parm *pStr_Comm_Parm_Address)
{
	ushort16	V_FrameLen, V_AddrLen;

/*�ж�ͨ������������1��68��HCS,Len��16��־*/
	if( CommRecFlag != C_CommRecFlagForInt_Ok )
	{
		return(C_Error);
	}
	else
	{
		SV_Comm_Parse_Local.RecFlag = CommRecFlag;
	}
/***************ȡ����****************/
	V_FrameLen = ( CommBuff[C_CLenH_OFS_ForRx_698] & 0x3F );
	V_FrameLen <<= 8;
	V_FrameLen |= CommBuff[C_CLenL_OFS_ForRx_698];

    SF_GetCommChanelCurrentLen(pV_698Frame->ChannelNo);			/*��ȡ��ͨ����ǰͨ��������*/
    if(V_FrameLen > Com_Conect.ClientRxMaxLen)
    {
    	return(C_Error);
    }

/*����FCs�Ƿ���ȷ,���Ȱ���L+ C+ Addr+ HCS +data+ FCS*/
	if( PF_Check_CRC_698(&CommBuff[C_CLenL_OFS_ForRx_698], V_FrameLen ) != C_OK )
	{
		return(C_Error);
	}

/*ע����ֻ�жϱ�ź�FCS��68��16����ͨ���ж����жϹ���*/
/*�ж�ͨ�ŵ�ַ*/
	pV_698Frame->AddressFlag = GetCommMeterAddressType_698( &CommBuff[C_CAddr_OFS_ForRx_698], &V_AddrLen );
	if(pV_698Frame->AddressFlag == C_AdrressError)
	{
		return(C_Error);
	}

	pV_698Frame->C = CommBuff[C_CControl_OFS_ForRx_698];
/*2020��׼�����ϱ�2005*/
	if( ( CommBuff[C_CControl_OFS_ForRx_698] & C_ServerStart_DIR ) != C_ClientStart_DIR )	/*���ǿͻ��˷��������������ϱ���Ӧ��Ӧ��*/
	{
		return(C_Error);
	}
	/*���ݳ��Ȱ���68��*/

	/*ȡ�ͻ�����ַ*/
	pV_698Frame->ClientAddr = CommBuff[C_CAddr_OFS_ForRx_698 + V_AddrLen + 1];

	if( ( (pV_698Frame->ClientAddr) & 0xf0 ) == Termal_Address )
	{
		SV_Comm_Parse_Local.ClientAddrFlag = Termal_Address;	/*�ն�*/
	}
	else
	{
		SV_Comm_Parse_Local.ClientAddrFlag = Master_Address;	/*��վ*/
	}


	/*�����򳤶ȼ�������copy��ע�����ﳤ�Ȳ���Ҫ-0x33��������Ҫ-0x33*/
	pV_698Frame->DataLen_698 = V_FrameLen;
	pV_698Frame->SecurityAddr = &CommBuff[C_CAddr_OFS_ForRx_698 + V_AddrLen + 2 + 2 ];
	pV_698Frame->AddrLen = V_AddrLen;							/*����SA��ַ����*/
    pV_698Frame->APDULen = V_FrameLen - 9 - V_AddrLen;

	if( ( pV_698Frame->C & C_Scramble_Flag ) == C_Scramble_Flag )
	{
		for( V_FrameLen = 0; V_FrameLen < pV_698Frame->APDULen; V_FrameLen++ )
		{
			pV_698Frame->SecurityAddr[V_FrameLen] = pV_698Frame->SecurityAddr[V_FrameLen] - 0x33;
		}
	}
	return(C_OK);
}
/*******************************************************************************
����ԭ�ͣ�uchar8 Security_Authentication(Str_Comm_645 * pV_698Frame)
������������ȫȨ���ж�:�ж��Ƿ�ȫ���䣬����԰�ȫȨ�޽����ж�
���������֡�����ṹ���ַ
���������֡��ȫ�Ƿ�Ϸ�
���ز��������ذ�ȫȨ���Ƿ�����Ҫ��C_OK��ʾ����Ȩ��Ҫ��
����λ�ã�Comm_Parse_698
��    ע��
*******************************************************************************/
uchar8 Security_Authentication(Str_Comm_645 * pV_698Frame)
{
	uchar8	*P_SIDMAC;
	uchar8	V_ucReturn, i;

	V_ucReturn = C_OK;

	if( ( ( pV_698Frame->SecurityAddr[0] ) == C_SECURITY_Request )
     || ( ( pV_698Frame->SecurityAddr[0]) == ( C_SECURITY_Request | 0x80 ) ) )
	{
		pV_698Frame->SECURITYFlay[0] = pV_698Frame->SecurityAddr[0] ;   			/*��ȫ����*/
		pV_698Frame->SECURITYFlay[1] = pV_698Frame->SecurityAddr[1] ;   			/*���Ļ�������*/
		if( ( pV_698Frame->SecurityAddr[2] ) & 0x80 )
		{
			pV_698Frame->APDULen = 0;
			for(i = 0; i < ( (pV_698Frame->SecurityAddr[2]) & 0x7F ); i++)
			{
				pV_698Frame->APDULen <<= 8;
				pV_698Frame->APDULen |= pV_698Frame->SecurityAddr[3 + i];
			}
			pV_698Frame->P_APDUStart = &(pV_698Frame->SecurityAddr[3 + ( (pV_698Frame->SecurityAddr[2]) & 0x7F )] );
		}
		else
		{
			pV_698Frame->APDULen = pV_698Frame->SecurityAddr[2] ;
			pV_698Frame->P_APDUStart = &(pV_698Frame->SecurityAddr[3]);
		}

		/****************���а�ȫ��֤�����������������Ҫ����********************/
		P_SIDMAC = (pV_698Frame->P_APDUStart) + (pV_698Frame->APDULen);				/*ȡ��ȫ��֤������ʼ��ַ*/

		/*������֤��Ϣ����*/
		pV_698Frame->SICMAC_Type = *P_SIDMAC;										/*���ݰ�ȫ������֤��Ϣ��ת��Ȩ��*/
		if( ( pV_698Frame->SecurityAddr[0] ) == ( C_SECURITY_Request | 0x80 ) )		/*�����ϱ�Ӧ��*/
		{
			pV_698Frame->RNSICBit = MAC_698;										/*����+MAC,05*/
		}
		else
		{
			if( pV_698Frame->SECURITYFlay[1] == 0x00 )
			{
				pV_698Frame->RNSICBit = 0x04;										/*����+MAC*/
			}
			else
			{
				if(*P_SIDMAC == 0x00)
				{
					pV_698Frame->RNSICBit = 0x01;									/*����+MAC*/
				}
				else
				{
					pV_698Frame->RNSICBit = 0x02;									/*����*/
				}
			}
		}

		if(pV_698Frame->RNSICBit == MAC_698)										/*����+MAC,0x05*/
		{
			uchar8      V_APDU[50], V_APDU2[C_RNLen], V_EncryptType = 0;
			ushort16    V_Len = 0;
			memset(V_APDU, 0x00, 50);
			memset(V_APDU2, 0xFF, C_RNLen);

			memcpy(V_APDU + V_Len, &SV_REPORTCommBuff[GV_RNByte], C_RNLen);
			V_Len += C_RNLen;
			V_Len += 4;                         									/*4��0x00*/
			memcpy(V_APDU + V_Len, pV_698Frame->P_APDUStart, pV_698Frame->APDULen);
			V_Len += pV_698Frame->APDULen;
			memcpy(V_APDU + V_Len, P_SIDMAC + 3, *(P_SIDMAC + 2) );
			V_Len += ( *(P_SIDMAC + 2) );
			if( PF_Campare_Data ( &SV_REPORTCommBuff[GV_RNByte], V_APDU2, C_RNLen ) == C_Equal )
			{
				V_ucReturn = C_OK;
			}
			else
			{
				V_ucReturn = INF_S_Encrypt_698(V_APDU, &V_Len, pV_698Frame->RNSICBit, V_EncryptType, &pV_698Frame->RN_Data[0], &pV_698Frame->RN_Data[0], SV_Comm_Parse_Local.ClientAddrFlag);
			}
		}
		else
		{
            /*���������*/
			if(*P_SIDMAC == RN_698)
			{
				if((P_SIDMAC[1]+2) < C_Comm_RNData_MaxLen)
				{
					for(i = 0;i < (P_SIDMAC[1] + 2); i++)
					{
						pV_698Frame->RN_Data[i] = P_SIDMAC[i];
					}
	            }
			}
            /*���а�ȫ�����жϼ���ȫ��֤*/
            /*��֤����ESAM��֤ʧ��C_ESAMErr_DAR*/
			if( ( ( ( SV_Comm_Parse_Local.ClientAddrFlag == Termal_Address ) && ( Com_Conect.ConectOverTime_termal == 0 ) )
				|| ( ( SV_Comm_Parse_Local.ClientAddrFlag == Master_Address ) && ( Com_Conect.ConectOverTime== 0 ) ) )
				&& ( ( pV_698Frame->RNSICBit == 0x01 ) || ( pV_698Frame->RNSICBit == 0x02 ) )
				&& ( pV_698Frame->AddressFlag != C_AddrTypePtoAll ) )			/*���Ĺ㲥���������֤*/
			 {
				return(C_SymmetryDecodeErr_DAR);								/*���ڲ��ܸ�λesam,�������ж�*/
			}
			else
			{
				V_ucReturn = INF_S_Decrypt_698(pV_698Frame->P_APDUStart, &pV_698Frame->APDULen, *P_SIDMAC, (P_SIDMAC + 1) );
			}
        }
	}
	else
	{
		pV_698Frame->P_APDUStart = &(pV_698Frame->SecurityAddr[0]);
		pV_698Frame->SECURITYFlay[0] = 0;
		if( ( pV_698Frame->SecurityAddr[0] ) == C_CONNECT_Request )
		{
			Com_Conect.Com_Right = Str_ConnRightType[C_NullSecyrityConnect];	/*����**�Գ���ԿȨ���ڽ���Ӧ������ʱ�ж�*/
		}
		if( InF_ConectTimer_DealNoTimer() != C_TimerEnable )					/*�������ESAMʱ�䣬����û��ʱ��ֱ����*/
		{
			pV_698Frame->RNSICBit = Str_ConnRightType[C_NullSecyrityConnect];	/*����*�Գ���ԿȨ���ڽ���Ӧ������ʱ�ж�*/
		}
		else
		{
			pV_698Frame->RNSICBit = 0x08;										/*���Ĵ���*/
		}
	}
	return V_ucReturn;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_GetFixedLen(uchar8 *P)
�������������ع̶����ȵ����ݵ����ݳ���
���������
���������P�����ص�ǰ�������͵��ֽ���
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_GetFixedLen(uchar8 *P)
{
	uchar8 i, V_Len = 0;
	for( i = 0; i < C_DataTypeTable1_Len; i++ )
	{
		if(*P == DataTypeTable1[i][0])
		{
			V_Len = DataTypeTable1[i][1];
			if(P[0] == C_CSD)								/*��಻�ܳ���80��OAD*/
			{
				if(P[1] == 0x01)
				{
					V_Len += (P[V_Len + 1] * 4 + 1);
				}
			}
			return(V_Len);
		}
	}
	return(V_Len);
}
/*******************************************************************************
����ԭ�ͣ�ushort16 SF_GetLengthFieldLen(uchar8 *P,uchar8 *P_a)
�������������������ֽ���
���������
���������
���ز�����������������1������0���ֽڣ�
����λ�ã�
��    ע��
*******************************************************************************/
ushort16 SF_GetLengthFieldLen(uchar8 *P, uchar8 *P_a)
{
	ushort16	V_LenRegion;
	uchar8 i;

	V_LenRegion = 0;
	if( ( (*P) | 0x7F ) == 0xFF )		/*������*/
	{
		*P_a = ( (*P) & 0x7F ) + 1;
		if( *P_a > 3 )
		{
			return C_NULL;				/*������ȴ���3�ֽڣ�Ӧ�𳤶�0����ʾ���ȴ���*/
		}
		for( i = 1; i < *P_a; i++ )
		{
			V_LenRegion <<= 8;
			V_LenRegion |= P[i];
		}
	}
	else
	{
		V_LenRegion = P[0];
		*P_a = 1;
	}
	return(V_LenRegion);
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_GetDataLenIncludeType(uchar8 *pDataBuf,ushort16 *pDataLen)
�����������������͵ĳ��ȣ��̶������Լ�������C_bit_string��C_octet_string��C_visible_string��C_TSA��C_SID��C_SID_MAC����
���������pDataBuf���������͵�������ʼ��ַ��
���������pDataLen�����ݳ���
���ز�����������������1������0���ֽڣ��C
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_GetDataLenIncludeType(uchar8 *pDataBuf, ushort16 *pDataLen)
{

	if( pDataBuf[0] == C_bit_string )
	{
		if( pDataBuf[1] < 0x81 )
		{
			*pDataLen = pDataBuf[1] / 8 + 2;
			if( pDataBuf[1] % 8 )
			{
				*pDataLen++;
			}
		}
		else
		{
			if( ( pDataBuf[1] & 0x7F ) == 1 )
			{
				*pDataLen = pDataBuf[2] / 8;
				*pDataLen = *pDataLen + 3;
				if( pDataBuf[2] % 8 )
				{
					*pDataLen++;
				}
			}
			else
			{
				*pDataLen = pDataBuf[2];
				*pDataLen <<= 8;
				*pDataLen |= pDataBuf[3];
				if( (*pDataLen) % 8 )
				{
				    *pDataLen = (*pDataLen) / 8 + 5;
				}
				else
				{
					*pDataLen = (*pDataLen) / 8 + 4;
				}
			}
		}
	}
	else if( ( pDataBuf[0] == C_octet_string )
		  || ( pDataBuf[0] == C_visible_string )
		  || ( pDataBuf[0] == C_TSA ) )				/*��������*/

	{
		if(pDataBuf[1] < 0x81)
		{
			*pDataLen = pDataBuf[1] + 2;
		}
		else
		{
			if((pDataBuf[1]&0x7F) == 1)
			{
				*pDataLen = pDataBuf[2];
				*pDataLen = *pDataLen + 3;
			}
			else
			{
				*pDataLen = pDataBuf[2];
				*pDataLen <<= 8;
				*pDataLen |= pDataBuf[3];
				*pDataLen = *pDataLen + 4;
			}
		}
	}
    else if( ( pDataBuf[0] == C_SID ) || ( pDataBuf[0] == C_SID_MAC ) )
    {
        *pDataLen = 4 + 1;
        uchar8		V_Num = 1, V_i;
        ushort16	V_TempLen;
        if( pDataBuf[0] == C_SID_MAC )
        {
            V_Num=2;
        }
        for(V_i = 0; V_i < V_Num; V_i++ )
        {
            if(pDataBuf[*pDataLen] < 0x81 )
            {
                *pDataLen += pDataBuf[*pDataLen] + 1;
            }
            else
            {
                if( ( pDataBuf[*pDataLen] & 0x7F ) == 1 )
                {
                    *pDataLen += pDataBuf[*pDataLen + 1] + 2;
                }
                else
                {
                    V_TempLen = pDataBuf[*pDataLen + 1];
                    V_TempLen <<= 8;
                    V_TempLen |= pDataBuf[*pDataLen + 2];
                    *pDataLen += V_TempLen +3;
                }
            }
        }
    }
	else 	/*�̶�����*/
	{
		*pDataLen = SF_GetFixedLen(pDataBuf) + 1;
	}
	if(*pDataLen == 1)
	{
		return C_Error;
	}
	else
	{
		return C_OK;
	}
}
/*******************************************************************************
����ԭ�ͣ�ushort16 SF_GetDataTypeLen(uchar8 *P)
�����������жϵ�ǰ���������м����ֽڣ��������ͣ�
���������
������������ص�ǰ�������͵��ֽ���
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
ushort16 SF_GetDataTypeLen(uchar8 *P)
{
	uchar8 	V_No, V_No2, V_No3, V_FieldLen, i;
	uchar8 	V_Temp1, V_Temp2, V_ZoneLen;
	ushort16	V_usLen, V_usOff, V_Len = 0;

	V_Len = SF_GetFixedLen(P);
	if(V_Len == 0)
	{
		switch(*P)
		{
			case 	C_array:
			case	C_structure:
			{
				V_usOff = 1;
				V_No = P[V_usOff];																	/*ȡ�������*/
				V_usOff++;
				for( i = 0; i < V_No; i++ )
				{
					if(P[V_usOff] == C_NULL)
					{
						V_usOff += 1;
					}
					else if(SF_GetDataLenIncludeType( &P[V_usOff], &V_usLen ) == C_OK )
					{
						V_usOff += V_usLen;
					}
					else  if( ( P[V_usOff] == C_array ) || ( P[V_usOff] == C_structure ) )			/*˵���ǽṹ���������*/
					{
						uchar8 i_i;

						V_usOff++;
						V_No2 = P[V_usOff];
						V_usOff++;
						for( i_i = 0; i_i < V_No2; i_i++ )
						{
							if( P[V_usOff] == C_NULL )
		                    {
		                        V_usOff += 1;
		                    }
							else if(SF_GetDataLenIncludeType( &P[V_usOff], &V_usLen ) == C_OK )
							{
								V_usOff += V_usLen;
							}
							else if( ( P[V_usOff] == C_array ) || ( P[V_usOff] == C_structure ) )	/*˵���ǽṹ���������*/
							{
								uchar8 i_ii;

								V_usOff++;
								V_No3 = P[V_usOff];
								V_usOff++;
								for( i_ii = 0; i_ii < V_No3; i_ii++ )
								{
									if(P[V_usOff] == C_NULL)
									{
										V_usOff += 1;
									}
									else if(SF_GetDataLenIncludeType( &P[V_usOff], &V_usLen ) == C_OK )
									{
										V_usOff += V_usLen;
									}
									else 															/*������3��Ƕ��*/
									{
										return 0;
									}
								}
							}
							else
							{
								return 0;
							}
						}
					}
					else
					{
						return 0;
					}
				}
				V_Len = V_usOff;										/*��ʽ������+���ȣ�������+������+���ݣ�����+���ݣ�*/
			}break;

			case 	C_bit_string:
			{
				V_ZoneLen = SF_GetLengthFieldLen(P + 1, &V_FieldLen);	/*��ʽ������+����+����*/
				V_Temp1 = V_ZoneLen % 8;
				if(V_Temp1 != 0)
				{
					V_Temp1 = 1;
				}
				V_Len = V_ZoneLen / 8 + V_Temp1;
				V_Len = V_Len + ( V_FieldLen + 1 );
			}break;
			case 	C_octet_string:
			case 	C_visible_string:
			case 	C_UTF8_string:
			{
				V_ZoneLen = SF_GetLengthFieldLen(P + 1, &V_FieldLen );	/*��ʽ������+����+����*/
				V_Len = V_ZoneLen + ( V_FieldLen + 1 );
			}break;

			case 	C_ROAD:												/*��ʽ��OAD+Array(OAD)*/
			{
				V_ZoneLen = SF_GetLengthFieldLen( P + 4, &V_FieldLen );
				V_Len = V_ZoneLen * 4 + ( V_FieldLen + 4 );
			}break;

			case 	C_TSA:
			case 	C_MAC:												/*��ʽ������+����*/
			case 	C_RN:
			{
				V_ZoneLen=SF_GetLengthFieldLen(P+1,&V_FieldLen);
				V_Len=V_ZoneLen+V_FieldLen+1;
			}break;

			case 	C_CSD:
			{
				if(*P == 0)												/*ѡ����0AD����ROAD*/
				{
					V_Len = 5;
				}
				else
				{
					V_ZoneLen = SF_GetLengthFieldLen( P + 5, &V_FieldLen );
					V_Len = V_ZoneLen * 4 + ( V_FieldLen + 5 );
				}
			}break;

			case 	C_SID:												/*��ʽ����ʶ��+��������*/
			{
				V_ZoneLen = SF_GetLengthFieldLen( P + 5, &V_FieldLen );
				V_Len = V_ZoneLen + ( V_FieldLen + 5 );
			}break;

			case 	C_SID_MAC:											/*��ʽ��SID+MAC*/
			{
				V_ZoneLen = SF_GetLengthFieldLen( P + 5, &V_FieldLen );	/*SID*/
				V_Len = V_ZoneLen+(V_FieldLen+5);
				V_Temp1 = SF_GetLengthFieldLen( P + V_Len, &V_Temp2);	/*MAC*/
				V_Len = V_ZoneLen + ( V_FieldLen + 5 ) + V_Temp1 + V_Temp2;
			}break;

			case 	C_RCSD:
			{
				if(*P == 0)
				{
					V_Len = 1;
				}
				else
				{
					if( *(P + 1) == 0 )									/*ѡ����0AD����ROAD*/
					{
						V_Len = 5;
					}
					else
					{
						V_ZoneLen = SF_GetLengthFieldLen( P + 6, &V_FieldLen );
						V_Len = V_ZoneLen * 4 + ( V_FieldLen + 6 );
					}
					V_Len = V_Len * (*P);
				}
			}break;

			default:
				V_Len = 0;
				break;
		}
	}
	else
	{
		V_Len += 1;														/*�������������ֽ���1*/
	}
	return(V_Len);
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_GETAPDU_Decode(Str_Comm_645 * pV_698Frame,Str_Comm_698_RW *pV_698RWPara)
������������һ����APDU���н���
���������֡�����ṹ���ַpV_698Frame����������ṹ��pV_698RWPara
�����������
���ز��������ذ�ȫȨ���Ƿ�����Ҫ��C_OK��ʾ����Ȩ��Ҫ��
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_GETAPDU_Decode(Str_Comm_645 * pV_698Frame, Str_Comm_698_RW *pV_698RWPara)
{
	uchar8	i, j, V_Len;
	ushort16	V_DataOff = 0, V_ucFrame;

	switch(pV_698Frame->P_APDUStart[1])
	{
		case C_GETNormal_Request:
		case C_GETNormalList_Request:
			pV_698RWPara->Next_OINO = 0;					/*��һ֡����֡���*/
			pV_698RWPara->Current_FrameNO = 0;				/*��ǰ֡���*/
			pV_698RWPara->ResponedNum = 0;
			pV_698RWPara->HaveEncodeNum = 0;
			pV_698RWPara->ResponedRelationNum = 0;
			pV_698RWPara->EndFrame =0;
			pV_698RWPara->FrameNUM = 0;
			pV_698RWPara->LastServiceFlag_Second = 0;		/*������֡ʱ����һ֡2�����󱣴�*/
			pV_698RWPara->CurrentOADEnd = 0;

			if(pV_698Frame->P_APDUStart[1] == C_GETNormal_Request)
			{
				pV_698RWPara->RWOI_Num = 1;
				V_DataOff = C_GETNormal_Request_Off;
			}
			else
			{
				pV_698RWPara->RWOI_Num = pV_698Frame->P_APDUStart[C_GETNormal_Request_Off];
				V_DataOff = C_GETNormal_Request_Off + 1;
			}
			if( ( pV_698RWPara->RWOI_Num > C_MaxReadListNum ) || ( pV_698RWPara->RWOI_Num == 0 ) )
			{
				pV_698RWPara->Rd_OI[0].Rd_Result = C_Service_OtherFault;
				return  C_OverStep_DAR;
			}
			for( i = 0; i < pV_698RWPara->RWOI_Num; i++ )
			{
			/*******************ȡ��ȡ���ݶ�������*********************/
				pV_698RWPara->Rd_OI[i].RdOI.OAD = PF_Buffer4ToUlong32_698(&pV_698Frame->P_APDUStart[V_DataOff]);

				V_DataOff += 4;
				pV_698RWPara->Wt_OI[i].WtOI = 0;
				pV_698RWPara->Wt_OI[i].Wt_Result = C_OK;
				pV_698RWPara->Rd_OI[i].Rd_Result = C_OK;
				pV_698RWPara->Wt_OI[i].Wt_Data = C_NULL;
				pV_698RWPara->Rd_OI[i].RdOI.CurrentFrameNum = 0;	/*�ñ�ʶ��û�ж����־*/
			}
			pV_698Frame->TimeTageByte = V_DataOff;					/*��¼ʱ���ǩ��ʼ��ַ*/
			break;

		case C_GETRecord_Request:
		case C_GETRecordList_Request:
			pV_698RWPara->Next_OINO = 0;							/*��һ֡����֡���*/
			pV_698RWPara->Current_FrameNO = 0;						/*��ǰ֡���*/
			pV_698RWPara->ResponedNum = 0;
			pV_698RWPara->HaveEncodeNum = 0;
			pV_698RWPara->ResponedRelationNum = 0;
			pV_698RWPara->EndFrame =0;
			pV_698RWPara->FrameNUM = 0;
			pV_698RWPara->LastServiceFlag_Second = 0;				/*������֡ʱ����һ֡2�����󱣴�*/
			pV_698RWPara->CurrentOADEnd = 0;

			if(pV_698Frame->P_APDUStart[1] == C_GETRecord_Request)
			{
				pV_698RWPara->RWOI_Num = 1;
				V_DataOff = C_GETNormal_Request_Off;
			}
			else
			{
				pV_698RWPara->RWOI_Num = pV_698Frame->P_APDUStart[C_GETNormal_Request_Off];
				V_DataOff = C_GETNormal_Request_Off + 1;
			}
            if( ( pV_698RWPara->RWOI_Num > C_MaxReadListNum ) || ( pV_698RWPara->RWOI_Num == 0 ) )
            {
				pV_698RWPara->Rd_OI[0].Rd_Result = C_APDUDecode_Fault;
                pV_698RWPara->ResponedNum = 1;
				return C_ServiceType_Err;							/*�������Ͳ��ԣ�Ӧ��ܾ���д*/
            }
			for( i = 0; i < pV_698RWPara->RWOI_Num; i++ )
			{
			/*******************ȡ��ȡ���ݶ�������*********************/
				pV_698RWPara->Rd_OI[i].RdOI.OAD = PF_Buffer4ToUlong32_698(&pV_698Frame->P_APDUStart[V_DataOff]);
				V_DataOff += 4;
			/*******************ȡ��ȡ���ݼ�¼ѡ�񷽷�*********************/
				pV_698RWPara->Rd_OI[i].Rd_RecordSelect[0] = pV_698Frame->P_APDUStart[V_DataOff];
				V_DataOff++;
				if(pV_698RWPara->Rd_OI[i].Rd_RecordSelect[0] == C_RSDSelector9)
				{
					pV_698RWPara->Rd_OI[i].Rd_RecordSelect[1] = pV_698Frame->P_APDUStart[V_DataOff];
					V_DataOff++;
				}
				else if(pV_698RWPara->Rd_OI[i].Rd_RecordSelect[0] == C_RSDSelector1)
				{
					PF_CopyDataBytes(&pV_698Frame->P_APDUStart[V_DataOff], &pV_698RWPara->Rd_OI[i].Rd_RecordSelect[1], 4);
					V_DataOff += 4;
					pV_698RWPara->Rd_OI[i].Rd_RecordSelect[5] = pV_698Frame->P_APDUStart[V_DataOff];	/*��������*/
					V_Len = SF_GetDataTypeLen(&pV_698Frame->P_APDUStart[V_DataOff]);					/*�������ͻ�ȡ����*/
					V_DataOff++;

					for( j = 0; j < ( V_Len - 1 ); j++ )
					{
						pV_698RWPara->Rd_OI[i].Rd_RecordSelect[6 + j] = pV_698Frame->P_APDUStart[V_DataOff];
						V_DataOff++;
					}
                    pV_698Frame->TimeTageByte = V_DataOff;												/*��¼ʱ���ǩ��ʼ��ַ*/
				}
				else if(pV_698RWPara->Rd_OI[i].Rd_RecordSelect[0] == C_RSDSelector2)
				{
					uchar8 V_SelectDecodeOff = 1;

					PF_CopyDataBytes( &pV_698Frame->P_APDUStart[V_DataOff], &pV_698RWPara->Rd_OI[i].Rd_RecordSelect[V_SelectDecodeOff], 4 );
					V_DataOff += 4;
					V_SelectDecodeOff += 4;
					pV_698RWPara->Rd_OI[i].Rd_RecordSelect[V_SelectDecodeOff] = pV_698Frame->P_APDUStart[V_DataOff];	/*��������*/
					V_Len = SF_GetDataTypeLen(&pV_698Frame->P_APDUStart[V_DataOff]);									/*�������ͻ�ȡ����*/
					V_DataOff++;

					for( j = 1; j < V_Len; j++ )
					{
						pV_698RWPara->Rd_OI[i].Rd_RecordSelect[V_SelectDecodeOff + j] = pV_698Frame->P_APDUStart[V_DataOff];
						V_DataOff++;
					}
					V_SelectDecodeOff += V_Len;
					pV_698RWPara->Rd_OI[i].Rd_RecordSelect[V_SelectDecodeOff] = pV_698Frame->P_APDUStart[V_DataOff];	/*��������*/
					V_Len = SF_GetDataTypeLen(&pV_698Frame->P_APDUStart[V_DataOff]);									/*�������ͻ�ȡ����*/
					V_DataOff++;

					for( j = 1; j < V_Len; j++)
					{
						pV_698RWPara->Rd_OI[i].Rd_RecordSelect[V_SelectDecodeOff + j] = pV_698Frame->P_APDUStart[V_DataOff];
						V_DataOff++;
					}
					V_SelectDecodeOff += V_Len;
					pV_698RWPara->Rd_OI[i].Rd_RecordSelect[V_SelectDecodeOff] = pV_698Frame->P_APDUStart[V_DataOff];	/*��������*/
					V_DataOff++;
					if( pV_698RWPara->Rd_OI[i].Rd_RecordSelect[V_SelectDecodeOff] == C_TI )
					{
						V_Len = SF_GetDataTypeLen(&pV_698RWPara->Rd_OI[i].Rd_RecordSelect[V_SelectDecodeOff++]);		/*�������ͻ�ȡ����*/
						for( j = 0; j < ( V_Len - 1 ); j++ )
						{
							pV_698RWPara->Rd_OI[i].Rd_RecordSelect[V_SelectDecodeOff + j] = pV_698Frame->P_APDUStart[V_DataOff];
							V_DataOff++;
						}
						V_SelectDecodeOff += ( V_Len - 1 );
					}
					else if( pV_698RWPara->Rd_OI[i].Rd_RecordSelect[V_SelectDecodeOff] == 0 )
					{
						;
					}
					else
					{
						V_Len = SF_GetDataTypeLen(&pV_698RWPara->Rd_OI[i].Rd_RecordSelect[V_SelectDecodeOff++]);		/*�������ͻ�ȡ����*/
						for( j = 0; j < ( V_Len - 1 ); j++ )
						{
							pV_698RWPara->Rd_OI[i].Rd_RecordSelect[V_SelectDecodeOff + j] = pV_698Frame->P_APDUStart[V_DataOff];
							V_DataOff++;
						}
						V_SelectDecodeOff += (V_Len - 1);
                        pV_698RWPara->Rd_OI[i].Rd_Result = C_TypeErr_DAR;
					}
				}
				else
				{
                    pV_698Frame->TimeTageByte = V_DataOff;							/*��¼ʱ���ǩ��ʼ��ַ*/
                    pV_698RWPara->Rd_OI[i].Rd_RecordRelatedOINum = 0;
                    pV_698RWPara->Rd_OI[i].Rd_Result = C_ForbidenRW;
                    pV_698RWPara->ResponedNum = 1;
					return C_ForbidenRW;		/*Ŀǰ��֧�ַ���1��9���ֶ�ȡ�����������ܾ���ȡ*/
				}
			/*******************ȡ��ȡ���ݼ�¼������������*********************/
				pV_698RWPara->Rd_OI[i].Rd_RecordRelatedOINum = pV_698Frame->P_APDUStart[V_DataOff];						/*������������*/
				V_DataOff++;
                if( pV_698RWPara->Rd_OI[i].Rd_RecordRelatedOINum > C_MaxRCSDNum )
                {
                    pV_698RWPara->Rd_OI[i].Rd_Result = C_Service_OtherFault;
					return C_ServiceType_Err;		/*ֻ֧����ѡΪOAD*/
                }
				for( j = 0; j < pV_698RWPara->Rd_OI[i].Rd_RecordRelatedOINum ; j++ )
				{
					pV_698RWPara->Rd_OI[i].Rd_RecordRelatedOIType = pV_698Frame->P_APDUStart[V_DataOff];				/*������������*/
					V_DataOff++;
					V_Len = 0;
					if( pV_698RWPara->Rd_OI[i].Rd_RecordRelatedOIType != 0 )		/*�����������Ա�ʶ���ǵ����������ԣ��򷵻ش�*/
					{
						return C_ForbidenRW;										/*��ʱ�����ǹ�����������Ϊ��¼����*/
					}
					pV_698RWPara->Rd_OI[i].Rd_RecordRelatedOI[j] = PF_Buffer4ToUlong32_698(&pV_698Frame->P_APDUStart[V_DataOff]);

					V_Len += 4;
					V_DataOff += 4;
				}

				pV_698RWPara->Wt_OI[i].WtOI = 0;
				pV_698RWPara->Wt_OI[i].Wt_Result = C_OK;
				pV_698RWPara->Rd_OI[i].Rd_Result = C_OK;
				pV_698RWPara->Wt_OI[i].Wt_Data = C_NULL;
				pV_698RWPara->Rd_OI[i].RdOI.CurrentFrameNum=0;
			}
			pV_698Frame->TimeTageByte = V_DataOff;									/*��¼ʱ���ǩ��ʼ��ַ*/
			break;

		case C_GETNext_Request:
			V_DataOff = C_GETNormal_Request_Off;
			V_ucFrame = pV_698Frame->P_APDUStart[V_DataOff];
			V_ucFrame <<= 8;
			V_ucFrame |= pV_698Frame->P_APDUStart[V_DataOff + 1];
			if( pV_698RWPara->FrameNUM != V_ucFrame )								/*Ӧ�ò�֡����ж�*/
			{
				return C_FrameNoErr;												/*Ӧ��֡�����Ч*/
			}
			for( i = 0; i < pV_698RWPara->RWOI_Num; i++ )
			{
				pV_698RWPara->Wt_OI[i].WtOI = 0;
				pV_698RWPara->Wt_OI[i].Wt_Result = C_OK;
				pV_698RWPara->Rd_OI[i].Rd_Result = C_OK;
				pV_698RWPara->Wt_OI[i].Wt_Data = C_NULL;
				pV_698RWPara->Rd_OI[i].RdOI.CurrentFrameNum = 0;
			}
            pV_698Frame->TimeTageByte = V_DataOff + 2;								/*��¼ʱ���ǩ��ʼ��ַ*/
			break;

		default:
			pV_698Frame->TimeTageByte = V_DataOff;									/*��¼ʱ���ǩ��ʼ��ַ*/
			pV_698RWPara->Rd_OI[0].Rd_Result = C_ServiceType_Fault;
			return C_ServiceType_Err;												/*�������Ͳ��ԣ�Ӧ��ܾ���д*/
			break;
	}
	return C_OK;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_SETAPDU_Decode(Str_Comm_645 * pV_698Frame,Str_Comm_698_RW *pV_698RWPara)
������������һ��дAPDU���н���
���������֡�����ṹ���ַpV_698Frame����������ṹ��pV_698RWPara
���������֡�Ƿ�Ϸ�
���ز��������ذ�ȫȨ���Ƿ�����Ҫ��C_OK��ʾ����Ȩ��Ҫ��
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_SETAPDU_Decode(Str_Comm_645 * pV_698Frame, Str_Comm_698_RW *pV_698RWPara)
{
	uchar8	i;
	ushort16	V_DataOff = 0;

	switch(pV_698Frame->P_APDUStart[1])
	{
		case C_SETNormal_Request:
		case C_SETNormalList_Request:
		case C_SETGETNormalList_Request:
			pV_698RWPara->Next_OINO = 0;				/*��һ֡����֡���*/
			pV_698RWPara->Current_FrameNO = 0;			/*��ǰ֡���*/
			pV_698RWPara->ResponedNum = 0;
			pV_698RWPara->ResponedRelationNum = 0;
			if(pV_698Frame->P_APDUStart[1] == C_SETNormal_Request)
			{
				pV_698RWPara->RWOI_Num = 1;
				V_DataOff = C_GETNormal_Request_Off;
			}
			else
			{
				pV_698RWPara->RWOI_Num = pV_698Frame->P_APDUStart[C_GETNormal_Request_Off];
				V_DataOff = C_GETNormal_Request_Off + 1;
			}
			if((pV_698RWPara->RWOI_Num>C_MaxReadListNum)||(pV_698RWPara->RWOI_Num == 0))
            {
				pV_698RWPara->Rd_OI[0].Rd_Result = C_APDUDecode_Fault;
				return C_ServiceType_Err;				/*�������֧��OAD������Ӧ���쳣����-��������*/
            }
			for(i=0;i<pV_698RWPara->RWOI_Num;i++)
			{
			/*******************ȡд���ݶ�������*********************/
				pV_698RWPara->Wt_OI[i].WtOI = PF_Buffer4ToUlong32_698(&pV_698Frame->P_APDUStart[V_DataOff]);

				V_DataOff += 4;
				pV_698RWPara->Wt_OI[i].DataLen = SF_GetDataTypeLen(&pV_698Frame->P_APDUStart[V_DataOff]);

				pV_698RWPara->Wt_OI[i].Wt_Data = &pV_698Frame->P_APDUStart[V_DataOff];
				V_DataOff += pV_698RWPara->Wt_OI[i].DataLen;
                if(pV_698RWPara->Wt_OI[i].DataLen == 0)
                {
                    V_DataOff++;
                }
				pV_698RWPara->Wt_OI[i].Wt_Result = C_OK;

				if(pV_698Frame->P_APDUStart[1] != C_SETGETNormalList_Request)
				{
					continue;							/*�������ú��ȡ��ʽ�������*/
				}
			/*****************����Զ����ݶ�����н���*******************/
				pV_698RWPara->Rd_OI[i].RdOI.OAD = PF_Buffer4ToUlong32_698(&pV_698Frame->P_APDUStart[V_DataOff]);
				V_DataOff += 4;
			/************************ȡ��ʱʱ��****************************/
				pV_698RWPara->W_R_DelayTime = pV_698Frame->P_APDUStart[V_DataOff];

				V_DataOff += 1;

				pV_698RWPara->Rd_OI[i].Rd_Result = C_OK;
			}
            pV_698Frame->TimeTageByte = V_DataOff;		/*��¼ʱ���ǩ��ʼ��ַ*/
			break;
		default:
			pV_698Frame->TimeTageByte = V_DataOff;		/*��¼ʱ���ǩ��ʼ��ַ*/
			pV_698RWPara->Rd_OI[0].Rd_Result = C_ServiceType_Fault;
			return C_ServiceType_Err;					/*�������Ͳ��ԣ�Ӧ��ܾ���д*/
			break;
	}
	return C_OK;
}
/*2020��׼���������ϱ�202005*/
/*******************************************************************************
����ԭ�ͣ�void Inf_ConfirmInitiativeReport(uchar8 V_Flag)
�������������ϱ�����ȷ��
���������V_Flag��C_ReportAddListClear��33200200��C_FollowStatusClear��20150200
�����������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
void Inf_ConfirmInitiativeReport(uchar8 V_Flag)
{
    uchar8   i, V_ZeroVariable[4] = {0xFF, 0xFF, 0xFF, 0xFF};
    ushort16 V_CRC;
    ulong32  V_TurnTemp = 0x80000000, V_MeterStatusReportTemp = 0x00000000;

	if( ( V_Flag & C_ReportAddListClear ) == C_ReportAddListClear )			/*��33200200*/
	{
		Inf_DeletReport(C_Module, C_ExceptPowerFailListEventNo);			/*�����ϱ�ȷ�ϲ������*/
	}
	if( ( V_Flag & C_FollowStatusClear ) == C_FollowStatusClear )			/*��ģ��ͨ����20150200*/
	{
		for( i = 0; i < CLMeterStatusNum; i++ )
		{
			if( GV_MeterStatusReportNO83[i] != C_ActiveReportMaxNum )		/*���������������3�Σ����Ǹշ����ģ���������*/
			{
				V_MeterStatusReportTemp |= V_TurnTemp;
				memset( GV_MeterStatusReportNO83 + i, 0x00, 1 );			/*�Ѿ��ϱ��Ĵ�������*/
			}
			V_TurnTemp = V_TurnTemp >> 1;
		}
		V_CRC = PF_Cal_CRC_698( GV_MeterStatusReportNO83, CLMeterStatusNum );
		PF_Ushort16ToBuffer2( &GV_MeterStatusReportNO83[CLMeterStatusNum], &V_CRC );

		PF_Ulong32ToBuffer4_698( V_ZeroVariable, &V_MeterStatusReportTemp, CLDrive_Report_State );
		Inf_CleanMeterStatus8( V_ZeroVariable, C_Module );
	}
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_REPORTAPDU_Decode(Str_Comm_645 * pV_698Frame,Str_Comm_698_RW *pV_698RWPara)
������������һ���ϱ�APDU���н���
���������֡�����ṹ���ַpV_698Frame����������ṹ��pV_698RWPara
���������
���ز��������ܵĴ�������
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_REPORTAPDU_Decode(Str_Comm_645 * pV_698Frame, Str_Comm_698_RW *pV_698RWPara)
{
	uchar8	i;
	ushort16	V_DataOff;

	switch(pV_698Frame->P_APDUStart[1])
	{
		case C_REPORTNormalList_Request:
		case C_REPORTRecordList_Request:
			pV_698RWPara->Next_OINO = 0;							/*��һ֡����֡���*/
			pV_698RWPara->Current_FrameNO = 0;						/*��ǰ֡���*/
			pV_698RWPara->ResponedNum = 0;
			pV_698RWPara->ResponedRelationNum = 0;
			pV_698RWPara->EndFrame =0;
			pV_698RWPara->FrameNUM = 0;
			pV_698RWPara->LastServiceFlag_Second = 0;				/*������֡ʱ����һ֡2�����󱣴�*/
			pV_698RWPara->CurrentOADEnd = 0;

            pV_698RWPara->RWOI_Num = pV_698Frame->P_APDUStart[C_GETNormal_Request_Off];
            V_DataOff = C_GETNormal_Request_Off + 1;

            if( ( pV_698RWPara->RWOI_Num>C_MaxReadListNum ) || ( pV_698RWPara->RWOI_Num == 0 ) )
            {
               pV_698RWPara->Rd_OI[0].Rd_Result = C_Service_OtherFault;
                return  C_OverStep_DAR;
            }
			for( i = 0; i < pV_698RWPara->RWOI_Num; i++ )
			{
			/*******************ȡ��ȡ���ݶ�������*********************/
				pV_698RWPara->Rd_OI[i].RdOI.OAD = PF_Buffer4ToUlong32_698(&pV_698Frame->P_APDUStart[V_DataOff]);
				V_DataOff += 4;
				pV_698RWPara->Wt_OI[i].WtOI = 0;
				pV_698RWPara->Wt_OI[i].Wt_Result = C_OK;
				pV_698RWPara->Rd_OI[i].Rd_Result = C_OK;
				pV_698RWPara->Wt_OI[i].Wt_Data = C_NULL;
				pV_698RWPara->Rd_OI[i].RdOI.CurrentFrameNum = 0;	/*�ñ�ʶ��û�ж����־*/
			}
            pV_698Frame->TimeTageByte = V_DataOff;					/*��¼ʱ���ǩ��ʼ��ַ*/
            break;

		default:
			pV_698Frame->TimeTageByte = V_DataOff;					/*��¼ʱ���ǩ��ʼ��ַ*/
			pV_698RWPara->Rd_OI[0].Rd_Result = C_ServiceType_Fault;
			return C_ServiceType_Err;								/*�������Ͳ��ԣ�Ӧ��ܾ���д*/
			break;
    }
    return C_OK;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 Inf_Event_REPORTONumDeal(uchar8 Type)
�������������������ϱ���������
���������Type�������ϱ��������������Ǹ����ϱ�
�����������
���ز�����V_Return:��������0������C_OK;
����λ�ã�
��    ע���²������磬�ϱ�������ֵΪ3�Σ�������ȡʱ��-(����������Ϊ�˵͹��ġ������ϵ�ĵط�Ҳ�Ѿ��ж��˲�д�б�)
*******************************************************************************/
uchar8 Inf_Event_REPORTONumDeal(uchar8 Type)
{
    uchar8 V_Return = C_OtherErr_DAR;
    ushort16 V_usCRC, V_usDataLen = 1;
    if( PF_Check_CRC( SV_PowerfailReportONum, V_usDataLen + 2 ) != C_OK )
    {
		SV_PowerfailReportONum[0] = 0;
    }
    if( C_NewReportFlag == Type )
    {
        if( Inf_SatisfyPowerOnTime() == C_OK )						/*�ϵ���1Сʱ*/
        {
            SV_PowerfailReportONum[0] = C_ActiveReportMaxNum;       /*����·����¼�����ֵΪ3��*/
        }
    }
    else if( 0 == Type )
    {
        SV_PowerfailReportONum[0] = 0;                          	/*����·����¼�����ֵΪ3��*/
    }
    else
    {
        if( ( SV_PowerfailReportONum[0] <= C_ActiveReportMaxNum ) && ( SV_PowerfailReportONum[0] > 0 ) )
        {
			SV_PowerfailReportONum[0]--;
			V_Return = C_OK;
        }
        else
        {
			SV_PowerfailReportONum[0] = 0;
        }
    }

    V_usCRC = PF_Cal_CRC( SV_PowerfailReportONum, V_usDataLen );
    PF_Ushort16ToBuffer2( SV_PowerfailReportONum + 1, &V_usCRC );
    return V_Return;
}
/*******************************************************************************
����ԭ�ͣ� uchar8 Inf_Event_REPORTONumGet(void)
���������� ���ص��������ϱ�����
���������
���������
���ز�����SV_PowerfailReportONum[0] ����;
����λ��:
��    ע�� �ж�CRC�ͺϷ��ԣ�
*******************************************************************************/
uchar8 Inf_Event_REPORTONumGet(void)
{
    ushort16 V_usCRC, V_usDataLen = 1;

	if( ( PF_Check_CRC(SV_PowerfailReportONum, V_usDataLen + 2) != C_OK )
	 || ( SV_PowerfailReportONum[0] > C_ActiveReportMaxNum ) )
	{
		SV_PowerfailReportONum[0] = 0;
		V_usCRC = PF_Cal_CRC(SV_PowerfailReportONum, V_usDataLen);
    	PF_Ushort16ToBuffer2(SV_PowerfailReportONum + 1, &V_usCRC);
	}

	return SV_PowerfailReportONum[0];
}
/*******************************************************************************
����ԭ�ͣ� void Report_Service_Deal(Str_Comm_698_RW *pV_698RWPara,uchar8 *pV_DataBuf,ushort16 V_BufLen,uchar8 *pV_NextFrFlag)
���������� ��һ���ϱ�APDU���н���
��������� ֡�����ṹ���ַpV_698Frame����������ṹ��pV_698RWPara
���������
���ز�����
����λ��:
��    ע��
*******************************************************************************/
void Report_Service_Deal(Str_Comm_698_RW *pV_698RWPara, uchar8 *pV_DataBuf, ushort16 V_BufLen, uchar8 *pV_NextFrFlag)
{
    uchar8 V_EventNum;
    uchar8 V_GetNoFlag = 0, V_OADNum = 0, V_OADNo = 0, V_ReadSign = 0, V_EventNoTemp[4] = {0};

    if(pV_698RWPara->ServiceFlag_Second == C_REPORTNormalList_Request)
    {
        if(pV_698RWPara->RWOI_Num == 1)								/*33200200��20150200���ϱ�*/
        {
            if(pV_698RWPara->Rd_OI[0].RdOI.OAD == CDrive_Report_State)
            {
                Inf_ConfirmInitiativeReport(C_FollowStatusClear);
            }
            else if(pV_698RWPara->Rd_OI[0].RdOI.OAD == CNewReportList)
            {
           		Inf_ConfirmInitiativeReport(C_ReportAddListClear);
            }
        }
        else if(pV_698RWPara->RWOI_Num == 2)						/*33200200��20150200���ϱ�*/
        {
            if( ( (pV_698RWPara->Rd_OI[0].RdOI.OAD == CDrive_Report_State) && (pV_698RWPara->Rd_OI[1].RdOI.OAD == CNewReportList) )
             || ( (pV_698RWPara->Rd_OI[1].RdOI.OAD == CDrive_Report_State) && (pV_698RWPara->Rd_OI[0].RdOI.OAD == CNewReportList) ) )
            {
                Inf_ConfirmInitiativeReport(C_ReportAddListClear | C_FollowStatusClear);
            }
        }
    }
    else if(pV_698RWPara->ServiceFlag_Second == C_REPORTRecordList_Request)
    {
        pV_698RWPara->ServiceFlag_First = C_GET_Request;
        pV_698RWPara->ServiceFlag_Second = C_GETRecordList_Request;
        if(pV_698RWPara->RWOI_Num > C_NewReportMaxNum)
        {
          pV_698RWPara->RWOI_Num = C_NewReportMaxNum;				/*����·����¼���¼���ݴ���70����ֵ70�����֧��70����*/
        }
        pV_698RWPara->ResponedNum = 0;
        for(V_EventNum = 0; V_EventNum < pV_698RWPara->RWOI_Num; V_EventNum++)
        {
            pV_698RWPara->Rd_OI[V_EventNum].Rd_RecordSelect[0] = C_RSDSelector9;
            pV_698RWPara->Rd_OI[V_EventNum].Rd_RecordSelect[1] = 1;
            V_GetNoFlag = Inf_ReportGetEventNo(pV_698RWPara, &V_ReadSign, V_EventNoTemp, &V_OADNum);
            if(V_GetNoFlag == C_OK)
            {
                for(V_OADNo = 0; V_OADNo < V_OADNum; V_OADNo++)
                {
                    Inf_EventReport_Sign(V_ReadSign, pV_698RWPara->ChannelNo, V_EventNoTemp[V_OADNo], C_ActiveReportFlag);
                }
            }
            pV_698RWPara->ResponedNum++;
        }
    }
#if 0
    Comm_AppendMsg(CMsg_InitComm);
#endif
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_JudgeACTIONRightLen(ulong32 V_ulOI,uchar8 *P_DataBuf,uchar8	*P_DataLen)
������������һ������APDU���н���
���������֡�����ṹ���ַpV_698Frame����������ṹ��pV_698RWPara
���������֡�Ƿ�Ϸ�
���ز��������ذ�ȫȨ���Ƿ�����Ҫ��C_OK��ʾ����Ȩ��Ҫ��
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_JudgeACTIONRightLen(ulong32 V_ulOI, uchar8 *P_DataBuf, uchar8	*P_DataLen)
{
	uchar8 V_Len;

	V_Len = *P_DataBuf;
	return V_Len;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_ACTIONAPDU_Decode(Str_Comm_645 * pV_698Frame,Str_Comm_698_RW *pV_698RWPara)
������������һ������APDU���н���
���������֡�����ṹ���ַpV_698Frame����������ṹ��pV_698RWPara
���������֡�Ƿ�Ϸ�
���ز��������ذ�ȫȨ���Ƿ�����Ҫ��C_OK��ʾ����Ȩ��Ҫ��
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_ACTIONAPDU_Decode(Str_Comm_645 * pV_698Frame, Str_Comm_698_RW *pV_698RWPara)
{
	uchar8		i;
	ushort16	V_DataOff = 0;
	switch(pV_698Frame->P_APDUStart[1])
	{
		case C_ACTIONNormal_Request:
		case C_ACTIONNormalList_Request:
		case C_ACTIONGETList_Request:
			pV_698RWPara->Next_OINO = 0;						/*��һ֡����֡���*/
			pV_698RWPara->Current_FrameNO = 0;					/*��ǰ֡���*/
			pV_698RWPara->ResponedNum = 0;
			pV_698RWPara->ResponedRelationNum = 0;
			if(pV_698Frame->P_APDUStart[1] == C_ACTIONNormal_Request)
			{
				pV_698RWPara->RWOI_Num = 1;
				V_DataOff = C_GETNormal_Request_Off;
			}
			else
			{
				pV_698RWPara->RWOI_Num = pV_698Frame->P_APDUStart[C_GETNormal_Request_Off];
				V_DataOff = C_GETNormal_Request_Off + 1;
			}
			if( ( pV_698RWPara->RWOI_Num > C_MaxReadListNum ) || ( pV_698RWPara->RWOI_Num == 0 ) )
            {
				pV_698RWPara->Rd_OI[0].Rd_Result = C_APDUDecode_Fault;
				return C_ServiceType_Err;						/*����֧�ָ�����Ӧ����������*/
            }
			for( i = 0; i < pV_698RWPara->RWOI_Num; i++ )
			{
			/*******************ȡд���ݶ�������*********************/
				pV_698RWPara->Wt_OI[i].WtOI = PF_Buffer4ToUlong32_698(&pV_698Frame->P_APDUStart[V_DataOff]);
				V_DataOff += 4;

				pV_698RWPara->Wt_OI[i].DataLen = SF_GetDataTypeLen(&pV_698Frame->P_APDUStart[V_DataOff]);	/*���ݳ�����Ҫ����*/
				pV_698RWPara->Wt_OI[i].Wt_Data = &pV_698Frame->P_APDUStart[V_DataOff];
				V_DataOff += pV_698RWPara->Wt_OI[i].DataLen;
				if( pV_698RWPara->Wt_OI[i].DataLen == 0 )		/*��ʾ����Ϊ�գ�ʱ���ǩ��ʼ�ĵط���1�ֽڿյ�ƫ�Ƽ���ȥ*/
				{
					V_DataOff++;
				}
				pV_698Frame->TimeTageByte = V_DataOff;			/*��¼ʱ���ǩ��ʼ��ַ*/

				pV_698RWPara->Wt_OI[i].Wt_Result = C_OK;
				if( pV_698Frame->P_APDUStart[1] != C_ACTIONGETList_Request )
				{
					continue;									/*�������ú��ȡ��ʽ�������*/
				}
			/*****************����Զ����ݶ�����н���*******************/
				pV_698RWPara->Rd_OI[i].RdOI.OAD = PF_Buffer4ToUlong32_698(&pV_698Frame->P_APDUStart[V_DataOff]);
				V_DataOff += 4;
			/************************ȡ��ʱʱ��****************************/
				pV_698RWPara->W_R_DelayTime = pV_698Frame->P_APDUStart[V_DataOff];
				V_DataOff += 1;
				pV_698RWPara->Rd_OI[i].Rd_Result = C_OK;
			}
			pV_698Frame->TimeTageByte = V_DataOff;				/*��¼ʱ���ǩ��ʼ��ַ*/
			break;

		default:
			pV_698Frame->TimeTageByte = V_DataOff;				/*��¼ʱ���ǩ��ʼ��ַ*/
			pV_698RWPara->Rd_OI[0].Rd_Result = C_ServiceType_Fault;
			return C_ServiceType_Err;							/*�������Ͳ��ԣ�Ӧ��ܾ���д*/
			break;
	}
	return C_OK;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_CONNECT_Decode(Str_Comm_645 * pV_698Frame,Str_Comm_698_RW *pV_698RWPara)
��������������Ӧ������APDU���н���
���������֡�����ṹ���ַpV_698Frame,pV_698RWPara��Ӧ��������֤������Ϣ
			��Ÿýṹ��ָ��ĵ�һ��дOAD��Ӧ�ĵ�ַ�ռ�
			���ݳ��Ȱ���:��ȫ����1�ֽ�,�����������ͼ�����
���������֡�Ƿ�Ϸ�
���ز��������ذ�ȫȨ���Ƿ�����Ҫ��C_OK��ʾ����Ȩ��Ҫ��
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_CONNECT_Decode(Str_Comm_645 * pV_698Frame, Str_Comm_698_RW *pV_698RWPara)
{
	uchar8	 V_Offset;
	uchar8   V_ClientAddr = 0;
	ushort16 V_Len = CLClientAddr, V_usDataEncode;
    uchar8 ProtVersion8[CLAppProInformation] = {0};

	V_Offset = 2;
	/*д�ͻ�����ַ*/
	InF_Read_Data( CClientAddr, &V_ClientAddr, &V_Len, &V_usDataEncode );
	if( V_ClientAddr != pV_698Frame->ClientAddr )
	{
		InF_Write_Data( C_Msg_Communication, CClientAddr,&pV_698Frame->ClientAddr, 1, C_W_SafeFlag );
	}

    V_Len = CLAppProInformation;
    InF_Read_Data( CAppProInformation, ProtVersion8, &V_Len, &V_usDataEncode );
	Com_Conect.ProtocolVersion = PF_Buffer2ToLong16_698(ProtVersion8);

	V_Offset += 2;
	PF_CopyDataBytes( &pV_698Frame->P_APDUStart[V_Offset], Com_Conect.ProtocolConformance, C_ProtocolConformance_Len );
	V_Offset += C_ProtocolConformance_Len;

    uchar8 V_Uniformity[C_FunctionConformance_Len] = {0};
    V_Len = CLAppProConsistency;
	if( ( InF_Read_Data( CAppProConsistency, V_Uniformity, &V_Len, &V_usDataEncode ) != C_OK )
	 || ( PF_Campare_Data( Com_Conect.ProtocolConformance, V_Uniformity, V_Len ) != C_Equal ) )
	{
		InF_Write_Data( C_Msg_Communication, CAppProConsistency, Com_Conect.ProtocolConformance, V_Len, C_W_SafeFlag );
	}
	PF_CopyDataBytes( &pV_698Frame->P_APDUStart[V_Offset], Com_Conect.FunctionConformance, C_FunctionConformance_Len );
	V_Offset += C_FunctionConformance_Len;
	V_Len = CLAppFunConsistency;
	if( ( InF_Read_Data( CAppFunConsistency, V_Uniformity, &V_Len, &V_usDataEncode ) != C_OK )
	 || ( PF_Campare_Data( Com_Conect.FunctionConformance, V_Uniformity, V_Len ) != C_Equal ) )
    {
        InF_Write_Data( C_Msg_Communication, CAppFunConsistency, Com_Conect.FunctionConformance, V_Len, C_W_SafeFlag );
    }

    uchar8 V_DataBuf[10];
    ushort16    V_CompareTemp = 0;

	Com_Conect.ClientRxMaxLen = PF_Buffer2ToLong16_698(&pV_698Frame->P_APDUStart[V_Offset]);	/*�ͻ����������ߴ�*/
	V_Offset += 2;
	if( C_CommRxMaxLen[pV_698Frame->ChannelNo] < Com_Conect.ClientRxMaxLen )
	{
		Com_Conect.ClientRxMaxLen = C_CommRxMaxLen[pV_698Frame->ChannelNo];
	}
	Com_Conect.CurrentConectAPDULen_Rx = Com_Conect.ClientRxMaxLen;								/*���浱ǰӦ������Э�̳ߴ�*/
	V_Len = CLAppMaxReAPDU;
	InF_Read_Data( CAppMaxReAPDU, V_DataBuf, &V_Len, &V_usDataEncode );                            				/*�����������ճߴ�*/
	V_CompareTemp = PF_Buffer2ToLong16_698(V_DataBuf);
	if( V_CompareTemp != Com_Conect.ClientRxMaxLen )
	{
		V_DataBuf[0] = (uchar8)(Com_Conect.ClientRxMaxLen>>8);
		V_DataBuf[1] = (uchar8)Com_Conect.ClientRxMaxLen;
		InF_Write_Data( C_Msg_Communication, CAppMaxReAPDU, (uchar8 *)V_DataBuf, 2, C_W_SafeFlag );
	}

	/*************��ǰͨ��ͨ���ߴ�***************/
	Com_Conect.ClientTxMaxLen = PF_Buffer2ToLong16_698(&pV_698Frame->P_APDUStart[V_Offset]);	/*�ͻ����������ߴ�*/
	V_Offset += 2;
    if(C_CommRxMaxLen[pV_698Frame->ChannelNo] < Com_Conect.ClientTxMaxLen)
    {
        Com_Conect.ClientTxMaxLen = C_CommRxMaxLen[pV_698Frame->ChannelNo];
    }
    Com_Conect.CurrentConectAPDULen_Tx = Com_Conect.ClientTxMaxLen;								/*���浱ǰӦ������Э�̳ߴ�*/
    V_Len = CLAppMaxSeAPDU;
	InF_Read_Data(CAppMaxSeAPDU, V_DataBuf, &V_Len, &V_usDataEncode );                            					/*����������ͳߴ�*/
    V_CompareTemp = PF_Buffer2ToLong16_698(V_DataBuf);
    if(V_CompareTemp != Com_Conect.ClientTxMaxLen)
    {
        V_DataBuf[0] = (uchar8)(Com_Conect.ClientTxMaxLen>>8);
        V_DataBuf[1] = (uchar8)Com_Conect.ClientTxMaxLen;
        InF_Write_Data(C_Msg_Communication, CAppMaxSeAPDU,V_DataBuf,2, C_W_SafeFlag);
    }
	Com_Conect.ClientRxMaxLenNum = pV_698Frame->P_APDUStart[V_Offset];
	V_Offset += 1;
    V_Len = CLAppMaxHandleAPDU;
	if(InF_Read_Data(CAppMaxHandleAPDU, V_DataBuf, &V_Len, &V_usDataEncode) != C_OK)                           	/*����������ͳߴ�*/
	{
		V_DataBuf[0] = 0x07;
		V_DataBuf[1] = 0xD0;
	}
    V_CompareTemp = PF_Buffer2ToLong16_698(V_DataBuf);
	Com_Conect.ClientAPDUMax = PF_Buffer2ToLong16_698(&pV_698Frame->P_APDUStart[V_Offset]);
	V_Offset += 2;
    if( V_CompareTemp < Com_Conect.ClientAPDUMax )
    {
        Com_Conect.ClientAPDUMax = V_CompareTemp;
    }
	if( SV_Comm_Parse_Local.ClientAddrFlag == Termal_Address )
	{
		Com_Conect.ConectOverTime_termal = PF_Buffer4ToUlong32_698(&pV_698Frame->P_APDUStart[V_Offset]);
	}
	else
	{
		Com_Conect.ConectOverTime = PF_Buffer4ToUlong32_698(&pV_698Frame->P_APDUStart[V_Offset]);
	}
	V_Offset += 4;

	Com_Conect.Com_NO = pV_698Frame->ChannelNo;
	Com_Conect.Com_Right = pV_698Frame->P_APDUStart[V_Offset];									/*���氲ȫȨ��*/

	if( ( Com_Conect.ConectOverTime == 0 ) && ( SV_Comm_Parse_Local.ClientAddrFlag == Master_Address ) )
	{
		Com_Conect.Com_Right = 0;																/*���ʱ��=0����ȫȨ��Ϊ0*/
	}
	if( ( Com_Conect.ConectOverTime_termal == 0 ) && ( SV_Comm_Parse_Local.ClientAddrFlag == Termal_Address ) )
	{
		Com_Conect.Com_Right = 0;																/*���ʱ��=0����ȫȨ��Ϊ0*/
	}
	Com_Conect.CRC16 = PF_Cal_CRC( (uchar8 *)&Com_Conect.ConectOverTime, C_ConectStruct_Len );

	pV_698RWPara->RWOI_Num = 1;
	pV_698RWPara->Wt_OI[0].WtOI = 0;
	pV_698RWPara->Wt_OI[0].Wt_Data = &pV_698Frame->P_APDUStart[V_Offset];
	pV_698RWPara->Wt_OI[0].Wt_Result = 0;														/*���Ƚ����Ĭ����ȷ*/
	if(pV_698RWPara->Wt_OI[0].Wt_Data[0] == C_NullSecyrityConnect)								/*��������*/
	{
		pV_698RWPara->Wt_OI[0].DataLen = 1;														/*��ȫ����1�ֽ�*/
		V_Offset += 1;
	}
	else if(pV_698RWPara->Wt_OI[0].Wt_Data[0] == C_PasswordSecurityConnect)						/*һ������*/
	{
		pV_698RWPara->Wt_OI[0].DataLen = pV_698RWPara->Wt_OI[0].Wt_Data[1] + 2;
		V_Offset += pV_698RWPara->Wt_OI[0].DataLen;
	}
	else																						/*�Գ���Կ��������ǩ��*/
	{
		pV_698RWPara->Wt_OI[0].DataLen = pV_698RWPara->Wt_OI[0].Wt_Data[1] + 2 + 1 + pV_698RWPara->Wt_OI[0].Wt_Data[pV_698RWPara->Wt_OI[0].Wt_Data[1] + 2];
		V_Offset += pV_698RWPara->Wt_OI[0].DataLen;
	}
    pV_698Frame->TimeTageByte = V_Offset;														/*��¼ʱ���ǩ��ʼ��ַ*/

	if(SV_Comm_Parse_Local.ClientAddrFlag ==Termal_Address)										/*�ն�*/
	{
		if( ( ( Com_Conect.ConectOverTime_termal !=0 ) )										/*����һ����Ч��*/
		 && ( ( pV_698RWPara->Wt_OI[0].Wt_Data[0] == C_NullSecyrityConnect )
		   || ( pV_698RWPara->Wt_OI[0].Wt_Data[0] == C_PasswordSecurityConnect ) ) )			/*Ӧ��������Чʱ�������ǰ��һ��������߹��������ȸ�λESAM*/
		{
			RELEASE_Service_Deal(Termal_Address);
		}
	}
	else																						/*��վ*/
	{
		if( ( ( Com_Conect.ConectOverTime != 0 ) )												/*����һ����Ч��*/
		 && ( ( pV_698RWPara->Wt_OI[0].Wt_Data[0] == C_NullSecyrityConnect )
		   || ( pV_698RWPara->Wt_OI[0].Wt_Data[0] == C_PasswordSecurityConnect ) ) )			/*Ӧ��������Чʱ�������ǰ��һ��������߹��������ȸ�λESAM*/
	    {
	        RELEASE_Service_Deal(Master_Address);
	    }

	}

	return C_OK;
}
/*�ú��������ǰʱ�����2000��1��1��0��0�ֵ��ղ�ֵ*/
/*ÿ����ʼ���������*/
/*******************************************************************************
����ԭ�ͣ�ulong32 SF_CalcAbsDay(uchar8 *P_HDMY)
�����������ú��������ǰʱ�����2000��1��1��0��0�ֵ��ղ�ֵ
���������
�����������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
const ushort16 gui_MonthBeginDay[12] = {0, 31, 59, 90,120, 151, 181, 212, 243, 273, 304, 334};
ulong32 SF_CalcAbsDay(uchar8 *P_HDMY)
{/*��2000��1��1��Ϊ��׼�����ڵ���������,���ʱ�䲻����2000��֮ǰ(��ʵ2000����00��ʾ,�������϶���ȥ)*/
	ulong32 ucYear, ucMonth, ucDay;

	PF_BCDtoHexBytes(&P_HDMY[3], &ucYear, 1);		/*��ת����Hex*/
	PF_BCDtoHexBytes(&P_HDMY[2], &ucMonth, 1);		/*��ת����Hex*/
	PF_BCDtoHexBytes(&P_HDMY[1], &ucDay, 1);		/*��ת����Hex8*/

	ucMonth = ucMonth-1;
	ucDay = ucDay-1;
	if( ( ucYear & 0x03 ) == 0 )					/*�ж��Ƿ���������2��*/
	{
		if( ucMonth >= 2 )
		{
			ucDay++;								/*�ټ�һ��*/
		}
	}
	else
	{
		ucDay++;									/*���������00�����¶������һ��*/
	}
	/*year >> 2,�Ǽ��Ϲ�ȥ����4��������һ��*/
	return ( ucYear * 365 + gui_MonthBeginDay[ucMonth] + (ucDay + ( ucYear >> 2 ) ) );
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_CalcAbsYM(uchar8 *P_HDMY1,uchar8 *P_HDMY2,ulong32 *P_YearNum,ulong32 *P_MonthNum)
�����������ú����������ʱ�������²�ֵ
���������
�����������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_CalcAbsYM(uchar8 *P_HDMY1,uchar8 *P_HDMY2,ulong32 *P_YearNum,ulong32 *P_MonthNum)
{
	ulong32	V_ulYear1, V_ulMonth1, V_ulYear2, V_ulMonth2;
	uchar8	V_ucFlag;

	PF_Buffer4ToUlong32(&P_HDMY1[CDate_Time_YYL_O],&V_ulYear1,2);	/*YYYY*/
	V_ulMonth1 = P_HDMY1[CDate_Time_MM_O];
	
	PF_Buffer4ToUlong32(&P_HDMY2[CDate_Time_YYL_O],&V_ulYear2,2);	/*YYYY*/
	V_ulMonth2 = P_HDMY2[CDate_Time_MM_O];

	if( V_ulYear1 > V_ulYear2 )
	{
		*P_YearNum = V_ulYear1 - V_ulYear2;
		*P_MonthNum = (*P_YearNum) * 12 + V_ulMonth1 - V_ulMonth2;
		V_ucFlag = C_GreaterThan;
	}
	else if( V_ulYear1 < V_ulYear2 )
	{
		*P_YearNum = V_ulYear2 - V_ulYear1;
		*P_MonthNum = (*P_YearNum) * 12 + V_ulMonth2 - V_ulMonth1;
		V_ucFlag = C_LessThan;
	}
	else
	{
		*P_YearNum = 0;
		if( V_ulMonth1 > V_ulMonth2 )
		{
			*P_MonthNum = V_ulMonth1 - V_ulMonth2;
			V_ucFlag = C_GreaterThan;
		}
		else
		{
			*P_MonthNum = V_ulMonth2 - V_ulMonth1;
			V_ucFlag = C_LessThan;
		}
	}
	return V_ucFlag;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 Is_IR_Comm_ResponseErr_698(Str_Comm_645 * pV_698Frame,Str_Comm_698_RW *pV_698RWPara)
��������������Ȩ���ж�
���������֡�����ṹ���ַpV_698Frame����������ṹ��pV_698RWPara
���������֡�Ƿ�Ϸ�
���ز��������ذ�ȫȨ���Ƿ�����Ҫ��C_OK��ʾ����Ȩ��Ҫ��
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 Is_IR_Comm_ResponseErr_698(Str_Comm_645 * pV_698Frame, Str_Comm_698_RW *pV_698RWPara)
{
	uchar8	i, j, V_Buf2[C_TimerExceed10minLen];

	memset( V_Buf2, 0, C_TimerExceed10minLen );
	if( pV_698Frame->PowerFlag == C_PowerOff )
	{		/*�����ڼ�,���������֤��Ч��������*/
		if(JudgeTimerExceed10min(&IR_AuthT) == C_TimerEnable)
		{	/*ͣ���ڼ䣬���ԭ�Ⱥ�����֤��Ч����ȡ��������֤����ʱ�ᷢ*/
			/*�������֤������Ϣ*/
			DealWith_IR_Auth_Timer( C_Set_TimerExceed10min, V_Buf2 );
		}
		if( JudgeTimerExceed10min(&ID_AuthT_T) == C_TimerEnable )
		{	/*ͣ���ڼ䣬���ԭ�Ⱥ�����֤��Ч����ȡ��������֤����ʱ�ᷢ*/
			/*�������֤������Ϣ*/
			DealWith_ID_Auth_T_Timer( C_Set_TimerExceed10min, V_Buf2 );
		}
	}


	/*�ն˺���ͨ�����Ӧ��03�ܾ���д*/
	if( ( pV_698Frame->ChannelNo == C_IR ) && ( SV_Comm_Parse_Local.ClientAddrFlag == Termal_Address ) )
	{
		for( j = 0; j < (pV_698RWPara->RWOI_Num); j++ )
		{
			pV_698RWPara->Rd_OI[j].Rd_Result = C_RWForbid_DAR;
			pV_698RWPara->Wt_OI[j].Wt_Result = C_RWForbid_DAR;
			pV_698RWPara->ResponedNum++;		/*�Ѿ�Ӧ�����1*/
		}
		return	C_OK;
	}
	if( ( pV_698Frame->ChannelNo == C_IR ) && ( JudgeTimerExceed10min(&IR_AuthT) != C_TimerEnable ) )
	{
/*������֤��Ч���ж��Ƿ�������ͨ�ŵ�����*/
/*���Ӽ�����������*/
		if(pV_698RWPara->ServiceFlag_First == C_GET_Request)							/*��ȡ����*/
		{
            for( i = 0; i < pV_698RWPara->RWOI_Num; i++ )
            {
                pV_698RWPara->ResponedNum++;											/*�Ѿ�Ӧ�����1*/
                if( ( pV_698RWPara->Rd_OI[i].RdOI.OAD & 0xFF000000 ) == 0x00000000 )
				{/*��ǰ���������ʣ���͸֧���*/
                	pV_698RWPara->Rd_OI[i].Rd_Result = C_OK;
                	continue;
				}
				if( ( pV_698RWPara->Rd_OI[i].RdOI.OAD & 0xFFFF0000 ) == 0x40000000 )	/*����400005XX �㲥Уʱ����*/
				{
					pV_698RWPara->Rd_OI[i].Rd_Result = C_OK;
					continue;
				}

				switch(pV_698RWPara->Rd_OI[i].RdOI.OAD)
				{
					case	CMeter_Num:													/*���*/
					case	CComm_Address:												/*ͨ�ŵ�ַ*/
					case	CSoftw_Record_Number:										/*������*/
					case	CChargeBal_Hex_Cent:
					case	COverDraft_Hex_Cent:
					case	CM_Com_Ac_Tol_En_0:											/*��ǰ�¶�����й����ۼ��õ���*/
					case	CY_Com_Ac_Tol_En_0:											/*���ݽ����õ���*/
                         	pV_698RWPara->Rd_OI[i].Rd_Result = C_OK;
                    break;
					default:
                            pV_698RWPara->Rd_OI[i].Rd_Result = C_RWForbid_DAR;
					break;
	            }
			}
		}
		else if(pV_698RWPara->ServiceFlag_First == C_ACTION_Request)					/*��������*/
		{
            for( i = 0; i < pV_698RWPara->RWOI_Num; i++ )
            {
                pV_698RWPara->ResponedNum++;											/*�Ѿ�Ӧ�����1*/
				switch(pV_698RWPara->Wt_OI[i].WtOI)
				{
					case	CDI_IRCReq:													/*������֤��������*/
					case	CDI_IR_ExtAuth:												/*������֤����*/
					case	0x80008300:													/*��������բ*/
							pV_698RWPara->Wt_OI[i].Wt_Result = C_OK;
                            break;
					default:
							pV_698RWPara->Wt_OI[i].Wt_Result = C_RWForbid_DAR;
                            break;
                }
			}
		}
		else
		{
			for( j = 0; j < (pV_698RWPara->RWOI_Num); j++ )
			{
                pV_698RWPara->Rd_OI[j].Rd_Result = C_RWForbid_DAR;
                pV_698RWPara->Wt_OI[j].Wt_Result = C_RWForbid_DAR;
				pV_698RWPara->ResponedNum++;											/*�Ѿ�Ӧ�����1*/
			}
		}
	}
	return	C_OK;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 Is_MAC_Judge_698(Str_Comm_645 * pV_698Frame,Str_Comm_698_RW *pV_698RWPara)
���������������ж�
���������֡�����ṹ���ַpV_698Frame����������ṹ��pV_698RWPara
���������֡�Ƿ�Ϸ�
���ز��������ذ�ȫȨ���Ƿ�����Ҫ��C_OK��ʾ����Ȩ��Ҫ��
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 Is_MAC_Judge_698(Str_Comm_645 * pV_698Frame, Str_Comm_698_RW *pV_698RWPara)
{
	uchar8	i, j, V_result;

	if( InF_JudgeIJTimer() == C_OK )													/*���ڲ��ж�MAC����*/
	{
		return	C_OK;
	}
	if( ( pV_698Frame->RNSICBit == 0x08 ) || ( pV_698Frame->RNSICBit == 0x04 ) )		/*���Ļ�������+RN���ж�MAC����*/
	{
		return	C_OK;
	}
	if( Comm_DealwithSPTVariable(C_JudgeSPTVariable) != C_SPT_Num_Over )
	{
		for( i = 0; i < pV_698RWPara->RWOI_Num; i++ )
		{
			if( ( pV_698RWPara->ServiceFlag_First ) == C_ACTION_Request )				/*��������*/
			{
				if( ( (pV_698RWPara->Wt_OI[i].WtOI) & 0xff000000 ) == 0x80000000 )		/*����������1*/
				{
					/*�ÿ����������״̬��*/
					uchar8	V_usERRState[2] = {0};

					InF_Write_Data( C_Msg_Communication, CControl_ExecuteState, V_usERRState, CLControl_ExecuteState, C_W_SafeFlag );			/*��������ִ��״̬��*/
					V_result = InF_Write_Data( C_Msg_Communication, CControl_ErrorState, V_usERRState, CLControl_ErrorState, C_W_SafeFlag );	/*�����������״̬��*/
				}
			}
		}
		return	C_OK;		/*200�ι���*/
	}
	for( i = 0; i < pV_698RWPara->RWOI_Num; i++ )
	{
		if( ( pV_698RWPara->ServiceFlag_First ) == C_ACTION_Request )					/*��������*/
		{
			if( ( (pV_698RWPara->Wt_OI[i].WtOI) & 0xff000000 ) == 0x80000000 )			/*����������1*/
			{
				/*�ÿ����������״̬��*/
				uchar8	V_usERRState[2] = {0};

				InF_Write_Data(C_Msg_Communication, CControl_ExecuteState, V_usERRState, CLControl_ExecuteState, C_W_SafeFlag);			/*��������ִ��״̬��*/
				V_usERRState[0] = 0x01;
				V_result = InF_Write_Data(C_Msg_Communication, CControl_ErrorState, V_usERRState, CLControl_ErrorState, C_W_SafeFlag);	/*�����������״̬��*/
			}
		}
	}
	for( i = 0; i < pV_698RWPara->RWOI_Num; i++ )
	{
		if( pV_698RWPara->ServiceFlag_First == C_ACTION_Request )						/*��������*/
		{
			if( ( (pV_698RWPara->Wt_OI[i].WtOI) != 0xF1000300 )							/*���ݻس�������*/
			 && ( (pV_698RWPara->Wt_OI[i].WtOI) != 0x80008300 ) )						/*���ĺ�բ������*/
			{
				V_result = C_MeterSafeguard_DAR;
				goto ReturnFlag;
			}
			else
			{
				V_result = C_OK;
				continue;
			}
		}
		else if( pV_698RWPara->ServiceFlag_First == C_SET_Request )						/*��������*/
		{
			if( pV_698RWPara->Wt_OI[i].WtOI != CGPS_Signal )
			{
				V_result = C_MeterSafeguard_DAR;
				goto ReturnFlag;
			}
			else
			{
				V_result = C_OK;
				continue;
			}
		}
		else
		{
			V_result = C_OK;
			continue;
		}
ReturnFlag:
		if( V_result != C_OK )
		{
			for( j = 0; j < (pV_698RWPara->RWOI_Num); j++ )
			{
				pV_698RWPara->Rd_OI[j].Rd_Result = V_result;
				pV_698RWPara->Wt_OI[j].Wt_Result = V_result;
				pV_698RWPara->Wt_OI[j].DataLen = 0;
				pV_698RWPara->ResponedNum++;											/*�Ѿ�Ӧ�����1*/
			}
			return	(V_result);
		}
		}
	return	(V_result);
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_APDU_Decode(Str_Comm_645 * pV_698Frame,Str_Comm_698_RW *pV_698RWPara)
������������һ��APDU���н���
���������֡�����ṹ���ַpV_698Frame����������ṹ��pV_698RWPara
���������֡�Ƿ�Ϸ�
���ز��������ذ�ȫȨ���Ƿ�����Ҫ��C_OK��ʾ����Ȩ��Ҫ��
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_APDU_Decode(Str_Comm_645 * pV_698Frame, Str_Comm_698_RW *pV_698RWPara)
{
	uchar8		V_return;
	uchar8		V_Mode, V_TITemp[4] = {0}, V_TimeBuf645[CLDate_Time + 2] = {0} ;
	ulong32		V_ulCurrTime698, V_ulTransTime698, V_Max, V_Min, V_Result, V_Coefficient, V_YearNum, V_MonthNum, V_TIParameter;
	ushort16	V_Len, V_BufLen = 8, V_usDataEncode;
	uchar8		V_Flag, V_TimeBuf698[CLDate_Time + 4], V_ucReturn;
	ulong32		V_ulHour, V_ulMin, V_ulSecond, V_ulDays;
	uchar8		V_ucTimeBase[CLDate_Time] = {0x00, 0x00, 0x00, 0x01, 0x01, 0xD0, 0x07 };

	pV_698RWPara->ServiceFlag_First = pV_698Frame->P_APDUStart[0];
	pV_698RWPara->ServiceFlag_Second = pV_698Frame->P_APDUStart[1];						/*ȡ�ڶ�����������*/
	pV_698RWPara->PIID = pV_698Frame->P_APDUStart[2];
    pV_698RWPara->ChannelNo = pV_698Frame->ChannelNo;
	switch(pV_698RWPara->ServiceFlag_First)
	{
		case C_GET_Request:
			V_return = SF_GETAPDU_Decode(pV_698Frame, pV_698RWPara);
			break;
		case C_SET_Request:
		case C_ACTION_Request:
			V_return = SF_SETAPDU_Decode(pV_698Frame, pV_698RWPara);
			break;
		case C_REPORT_Response:					/*2020��׼�����ϱ�2005*/
			V_return = SF_REPORTAPDU_Decode(pV_698Frame, pV_698RWPara);
			break;
		case C_CONNECT_Request:
			if( ( SV_Comm_Parse_Local.ClientAddrFlag == Termal_Address ) && ( Com_Conect.ConectOverTime == 0 )
			 || ( SV_Comm_Parse_Local.ClientAddrFlag == Master_Address ) && ( Com_Conect.ConectOverTime_termal== 0 ) )
			{
				INF_StopCommProgState();		/*������̼�¼*/
			}

			pV_698RWPara->ServiceFlag_Second = 0;
			pV_698RWPara->PIID = pV_698Frame->P_APDUStart[1];
			V_return = SF_CONNECT_Decode(pV_698Frame, pV_698RWPara);
			break;
		case C_RELEASE_Request:
			pV_698RWPara->ServiceFlag_Second = 0;
			pV_698RWPara->PIID = pV_698Frame->P_APDUStart[1];

			if(SV_Comm_Parse_Local.ClientAddrFlag == Termal_Address)
			{
				Com_Conect.ConectOverTime_termal = 0;														/*����Ӧ������ʣ��ʱ������*/
			}
			else
			{
				Com_Conect.ConectOverTime = 0;																/*����Ӧ������ʣ��ʱ������*/
			}

            Com_Conect.CRC16 = PF_Cal_CRC((uchar8 *)&Com_Conect.ConectOverTime, C_ConectStruct_Len);		/*����Ӧ������ʱ��*/

			pV_698Frame->TimeTageByte = 2;  																/*�¼���ǩ����λ�ù̶�*/
			pV_698RWPara->RWOI_Num = 0;
			V_return = C_OK;
			break;
		default:
			pV_698RWPara->Rd_OI[0].Rd_Result = C_ServiceType_Fault;
			V_return = C_ServiceType_Err;																	/*������������*/
			break;
	}
	if(V_return != C_ServiceType_Err)																		/*���Ƿ������ʹ�*/
	{
		if(pV_698Frame->TimeTageByte >= pV_698Frame->APDULen)
		{
			pV_698RWPara->Rd_OI[0].Rd_Result = C_APDUDecode_Fault;
			V_return = C_ServiceType_Err;																	/*������������*/
			return V_return;
		}
		else
		{
			if( (pV_698Frame->P_APDUStart[pV_698Frame->TimeTageByte]) ==0x01 )
			{
				if( (pV_698Frame->TimeTageByte + 11) != pV_698Frame->APDULen )
				{
					pV_698RWPara->Rd_OI[0].Rd_Result = C_APDUDecode_Fault;
					V_return = C_ServiceType_Err;															/*������������*/
					return V_return;
				}
			}
			else
			{
				if( ( pV_698Frame->TimeTageByte + 1 ) != pV_698Frame->APDULen )
				{
					pV_698RWPara->Rd_OI[0].Rd_Result = C_APDUDecode_Fault;
					V_return = C_ServiceType_Err;															/*������������*/
					return V_return;
				}
			}
		}
	}
	if(V_return == C_OK)
	{
	    if( ( pV_698Frame->P_APDUStart[pV_698Frame->TimeTageByte] ) ==0x01 )
	    {
	        V_Len = (pV_698Frame->APDULen)- (pV_698Frame->TimeTageByte);
			/*��ʱ���ǩת��ΪС�˸�ʽ�����͵��ʱ�����Ƚ�*/
			PF_OneDataReversed(&(pV_698Frame->P_APDUStart[pV_698Frame->TimeTageByte + 1]), V_TimeBuf698, 7);
	        V_Mode = InF_Read_Data( CDate_Time, &V_TimeBuf645[0], &V_BufLen, &V_usDataEncode );
	        V_Flag = PF_DataTimeActive_698(V_TimeBuf698, 0, 6);
            (pV_698RWPara->TimeTag[0]) = C_TimeTagOn;
            PF_CopyDataBytes(&pV_698Frame->P_APDUStart[pV_698Frame->TimeTageByte], &pV_698RWPara->TimeTag[1], 11);
	        if(V_Mode != C_OK)
	        {
	            V_return = C_OtherErr_DAR;
	        }
	        else if( ( V_Len != 11 ) || ( V_Flag != C_OK ) )
	        {
	            V_return = C_TimeTagInvalid;
	        }
	        else
	        {
				if( ( (pV_698Frame->P_APDUStart[pV_698Frame->TimeTageByte + 8]) == 4 )	/*TI��λΪ��*/
				 || ( (pV_698Frame->P_APDUStart[pV_698Frame->TimeTageByte + 8]) == 5 ) )/*TI��λΪ��*/
				{
				    V_ucReturn = SF_CalcAbsYM(V_TimeBuf645, V_TimeBuf698, &V_YearNum, &V_MonthNum);/*�������x��x��*/
				    if( ( pV_698Frame->P_APDUStart[pV_698Frame->TimeTageByte + 8] )  == 4 )/*TI��λΪ��*/
				    {
				        V_Result = V_MonthNum;			/*Hex*/
				    }
				    else
				    {
				        V_Result = V_YearNum;
				    }
				    V_Coefficient = 1;
				}
				else
				{
					PF_TimeSub_Day_698(V_ucTimeBase,V_TimeBuf645, &V_ulDays);/*������ʱ����2000.1.1 00:00:00���x��*/
					V_ulCurrTime698 = V_ulDays;

					PF_TimeSub_Day_698(V_ucTimeBase,V_TimeBuf698, &V_ulDays);/*����ʱ���ǩ��2000.1.1 00:00:00���x��*/
					V_ulTransTime698 = V_ulDays;

					V_ulHour = V_TimeBuf645[C_hh_O];
					V_ulMin = V_TimeBuf645[C_mm_O];
					V_ulSecond = V_TimeBuf645[C_ss_O];
					V_ulCurrTime698 = V_ulCurrTime698 * 60 * 60 * 24 		/*��->��*/
									+ V_ulHour * 60 * 60 				/*ʱ->��*/
									+ V_ulMin * 60 						/*��->��*/
									+ V_ulSecond;						/*��*/
									
					V_ulHour = V_TimeBuf698[C_hh_O];
					V_ulMin = V_TimeBuf698[C_mm_O];
					V_ulSecond = V_TimeBuf698[C_ss_O];
					V_ulTransTime698 = V_ulTransTime698 * 60 * 60 * 24 		/*��->��*/
									+ V_ulHour * 60 * 60 				/*ʱ->��*/
									+ V_ulMin * 60 						/*��->��*/
									+ V_ulSecond;						/*��*/
					if(V_ulCurrTime698 > V_ulTransTime698)
				    {
						V_Max = V_ulCurrTime698;
						V_Min = V_ulTransTime698;
						V_ucReturn = C_GreaterThan;
				    }
				    else
				    {
						V_Max = V_ulTransTime698;
						V_Min = V_ulCurrTime698;
						V_ucReturn = C_LessThan;
				    }
				    switch(pV_698Frame->P_APDUStart[pV_698Frame->TimeTageByte+8])
				   {
				        case    0:
				                V_Coefficient = 1;      	/**��*/
				                break;
				        case    1:                      	/**����*/
				                V_Coefficient = 60;
				                break;
				        case    2:                       	/**Сʱ*/
				                V_Coefficient = 60*60;
				                break;
				        case    3:                      	/**��*/
				                V_Coefficient = 60*60*24;
				                break;
				        default:
				                V_Coefficient = 1;
				                break;
				    }
				    V_Result = (V_Max-V_Min);
				}
				memset(V_TITemp, 0x00, 4);
				V_TITemp[2] = pV_698Frame->P_APDUStart[pV_698Frame->TimeTageByte+9];
				V_TITemp[3] = pV_698Frame->P_APDUStart[pV_698Frame->TimeTageByte+10];
				V_TIParameter = PF_Buffer4ToUlong32_698(V_TITemp)*V_Coefficient;
				if( ( V_Result > V_TIParameter ) && ( V_ucReturn == C_GreaterThan ) )
				{
				    V_return = C_TimeTagInvalid;
				}
	        }
            if(V_return != C_OK)
            {
                uchar8 V_ucNum;

                for( V_ucNum = 0; V_ucNum < pV_698RWPara->RWOI_Num; V_ucNum++ )
                {
                    pV_698RWPara->Wt_OI[V_ucNum].DataLen = 0;
                    pV_698RWPara->Rd_OI[V_ucNum].Rd_Result = V_return;
                    pV_698RWPara->Wt_OI[V_ucNum].Wt_Result = V_return;
                }
                pV_698RWPara->ResponedNum = pV_698RWPara->RWOI_Num;
            }
	    }
	    else
	    {
	        pV_698RWPara->TimeTag[0] = 0;
	    }
	}

	return V_return;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 InF_ConectTimer_DealNoTimer(void)
����������ֻ�ж�Ӧ�����ӳ�ʱʱ���Ƿ�ʱ
�����������
�����������
���ز�������
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 InF_ConectTimer_DealNoTimer(void)
{
	uchar8 Flag = C_TimerEnable;

	if( ( Com_Conect.ConectOverTime == 0 ) && ( Com_Conect.ConectOverTime_termal == 0 ) )
	{
		return C_TimerDisable;
	}
	return Flag;
}
/*******************************************************************************
����ԭ�ͣ�ulong32 SF_GetEsamReminTime(uchar8 V_ClientAddr)
����������ESAMʣ��ʱЧ
���������
���������V_RemainTime��ʣ��ʱ��
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
ulong32 SF_GetEsamReminTime(uchar8 V_ClientAddr)
{
	ushort16 V_BufRemainLen, V_usDataEncode;
	ulong32 V_RemainTime = 0;

	V_BufRemainLen = 4;
	if(V_ClientAddr == Termal_Address)																								/*�ն�*/
	{
		InF_GetData_ObjectManage(C_Remain_termal, (uchar8 *)&V_RemainTime, &V_BufRemainLen, &V_usDataEncode);			/*��ȡESAM��Ӧ������ʣ��ʱ��*/
	}
	else
	{
		InF_GetData_ObjectManage(CID_Auth_Remain_Time, (uchar8 *)&V_RemainTime, &V_BufRemainLen, &V_usDataEncode);		/*��ȡESAM��Ӧ������ʣ��ʱ��*/
	}

    return  (V_RemainTime);
}
/*******************************************************************************
����ԭ�ͣ�void InF_Clear698ConectTimer(void)
����������645����Ӧ������ʱ��698Ӧ�����Ӷ�ʱ��
���������
�����������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
void InF_Clear698ConectTimer(void)
{
    GV_ComConect_Timer = 0;
    GV_GEsam_1min = 0;
    Com_Conect.ConectOverTime = 0;
    Com_Conect.CRC16 = PF_Cal_CRC((uchar8 *)&Com_Conect.ConectOverTime, C_ConectStruct_Len);	/*����Ӧ������ʱ��*/
}
/*******************************************************************************
����ԭ�ͣ� InF_ConectTimer_Deal
���������� Ӧ������ʱ�䴦��
���������
��������� ��
���ز����� C_TimerEnable ʱ����Ч��C_TimerDisable ʱ����Ч��
����λ��:
��    ע��
*******************************************************************************/
uchar8 InF_ConectTimer_Deal(void)
{
	ushort16  DataLen, V_usDataEncode;
	uchar8    MeterRunState3[2], MeterRunState3Old[2], V_ucBuffer[10], Flag = C_TimerEnable;
    ulong32   V_RemainTime = 0;

	DataLen = CLMeter_Work_State3;
	InF_Read_Data(CMeter_Work_State3, MeterRunState3, &DataLen, &V_usDataEncode );	    				/*����������*/
	if( (Com_Conect.ConectOverTime == 0) && (ID_AuthT_Timer == 0) )	    				/*��վ*/
	{
		MeterRunState3Old[CO_IDAuth] = MeterRunState3[CO_IDAuth];
		MeterRunState3[CO_IDAuth] = MeterRunState3[CO_IDAuth] & (~CB_IDAuth);
		if(MeterRunState3Old[CO_IDAuth] != MeterRunState3[CO_IDAuth])   				/*�仯д*/
		{
			InF_Write_Data(C_Msg_Communication, CMeter_Work_State3, MeterRunState3, CLMeter_Work_State3, C_W_SafeFlag);
		}
	}
	if((Com_Conect.ConectOverTime_termal == 0) && (ID_AuthT_Timer == 0) )				/*�ն�*/
	{
		MeterRunState3Old[CO_IDAuth_T] = MeterRunState3[CO_IDAuth_T];
		MeterRunState3[CO_IDAuth_T] = MeterRunState3[CO_IDAuth_T] & (~CB_IDAuth_T);
		if(MeterRunState3Old[CO_IDAuth_T] != MeterRunState3[CO_IDAuth_T])   			/*�仯д*/
		{
			InF_Write_Data(C_Msg_Communication, CMeter_Work_State3, MeterRunState3, CLMeter_Work_State3, C_W_SafeFlag);
		}
	}
	if((Com_Conect.ConectOverTime == 0)&&(Com_Conect.ConectOverTime_termal == 0) && (ID_AuthT_Timer == 0))
	{
		return C_TimerDisable;
	}

	GV_ComConect_Timer++;
    GV_GEsam_1min++;

	if(GV_ComConect_Timer >1)					/*500msӦ�����Ӷ�ʱ������һ�Σ�ÿs��ʱ����1*/
	{
		GV_ComConect_Timer = 0;

		if(Com_Conect.ConectOverTime != 0)
		{
			Com_Conect.ConectOverTime--;
		}
		if(Com_Conect.ConectOverTime_termal != 0)
		{
			Com_Conect.ConectOverTime_termal--;
		}
	}
    else
    {
        if(GV_GEsam_1min > 119)    				/*60s�ж�һ��ESAMʱ���Ӧ��������Чʱ����С�������Чʱ��>ESAMʱ�䣬��ESAMʱ�串��*/
        {
            GV_GEsam_1min = 0;
            V_RemainTime = SF_GetEsamReminTime(Master_Address);
			if(Com_Conect.ConectOverTime > V_RemainTime * 60)
			{
				Com_Conect.ConectOverTime = V_RemainTime * 60;
			}
			V_RemainTime = SF_GetEsamReminTime(Termal_Address);
			if(Com_Conect.ConectOverTime_termal > V_RemainTime * 60)
			{
				Com_Conect.ConectOverTime_termal = V_RemainTime * 60;
			}

        }
    }

	if( (Com_Conect.ConectOverTime == 0 )
	 && (Com_Conect.ConectOverTime_termal == 0)
	 && (JudgeTimerExceed10min(&ID_AuthT_T) != C_TimerEnable) )
	{
		V_ucBuffer[0] = Pt_ResetEsam;			/*���͸�λ��Ϣ��ESAMģ��*/
		Dispatch_SendMessage(C_Msg_Esam, V_ucBuffer, Pt_ResetEsam_Len + 1);
        Flag = C_TimerDisable;
        GV_ComConect_Timer = 0;
        GV_GEsam_1min = 0;
	}

    Com_Conect.CRC16 = PF_Cal_CRC( (uchar8 *)&Com_Conect.ConectOverTime, C_ConectStruct_Len);	/*����Ӧ������ʱ��*/
	return Flag;
}
/*******************************************************************************
����ԭ�ͣ� InF_JudgeESAMConTimer
���������� �ж�Ӧ������ʱ����Ч���
��������� V_Flag    C_ResetDealConectTime      ����Ӧ������ʱ��
                     C_ReworkDealConectTime     ͬ��Ӧ������ʱ��
                     C_PowerUpDealConectTime	�ϵ紦��Ӧ������ʱ��
                     C_SynDealConectTime        ��ʱˢ��Ӧ������ʱ��
           ClientAddr �ն˵�ַ������վ��ַ��
��������� ��
���ز����� ��
����λ��:
��    ע��
*******************************************************************************/
void InF_JudgeESAMConTimer(uchar8 V_Flag, uchar8 ClientAddr)
{
	uchar8  MeterRunState3[2], MeterRunState3Old[2], buf[4], V_DataBuf[CLAppStaticTimeout];
	ushort16  DataLen, V_Len, V_usDataEncode;
	ulong32 *p_ConectOverTime, V_RemainTime = 0, V_CompareTime = 0;

	GV_ComConect_Timer = 0;
    GV_GEsam_1min = 0;

	if(ClientAddr == Termal_Address)
	{
		p_ConectOverTime =  &Com_Conect.ConectOverTime_termal;
	}
	else
	{
		p_ConectOverTime =  &Com_Conect.ConectOverTime;
	}

    if(C_PowerUpDealConectTime == V_Flag)									/*�ϵ��ʼ������ֱ�Ӷ�ȡESAM���ݣ�ֱ�ӽ�ESAM��ȡ��Ž����ֵ0*/
    {
    	V_RemainTime = 0;
    }
    else
    {
    	V_RemainTime = SF_GetEsamReminTime(ClientAddr);
    }

	if(V_Flag == C_ReworkDealConectTime)
	{
		if(*p_ConectOverTime > V_RemainTime * 60)
        {
            *p_ConectOverTime = V_RemainTime * 60;
        }
	    V_Len = CLAppStaticTimeout;

		if(ClientAddr == Termal_Address)
		{
			InF_Read_Data(CAppStaticTimeout_termal, V_DataBuf, &V_Len, &V_usDataEncode );		/*��̬��ʱʱ���ն�*/

            V_CompareTime = PF_Buffer4ToUlong32_698(V_DataBuf);
            if(V_CompareTime != *p_ConectOverTime)
            {
                PF_Ulong32ToBuffer4_698(V_DataBuf, p_ConectOverTime, 4);
                InF_Write_Data(C_Msg_Communication, CAppStaticTimeout_termal, V_DataBuf, 4, C_W_SafeFlag);
            }
		}
		else
		{
	        InF_Read_Data(CAppStaticTimeout, V_DataBuf, &V_Len, &V_usDataEncode );			/*��̬��ʱʱ��*/

	        V_CompareTime = PF_Buffer4ToUlong32_698(V_DataBuf);
	        if(V_CompareTime != *p_ConectOverTime)
	        {
	            PF_Ulong32ToBuffer4_698(V_DataBuf, p_ConectOverTime, 4);
	            InF_Write_Data(C_Msg_Communication, CAppStaticTimeout, V_DataBuf, 4, C_W_SafeFlag);
	        }
		}
	}
	else
	{
		if(V_Flag == C_SynDealConectTime)
		{
			*p_ConectOverTime = V_RemainTime * 60;
		}
		else
		{
			*p_ConectOverTime = 0;
		}
	}
    Com_Conect.CRC16 = PF_Cal_CRC((uchar8 *)&Com_Conect.ConectOverTime, C_ConectStruct_Len);	/*����Ӧ������ʱ��*/

    /*698����645������645�����֤*/
    memset(buf,0,C_TimerExceed10minLen);
    DealWith_ID_Auth_Timer(C_Set_TimerExceed10min, &buf[0]);

	DataLen = CLMeter_Work_State3;
	InF_Read_Data(CMeter_Work_State3, MeterRunState3, &DataLen, &V_usDataEncode);								/*����������*/

	if(ClientAddr != Termal_Address)															/*��վ*/
	{
		MeterRunState3Old[CO_IDAuth] = MeterRunState3[CO_IDAuth];
		MeterRunState3[CO_IDAuth] = MeterRunState3[CO_IDAuth] & (~CB_IDAuth);

		if(Com_Conect.ConectOverTime != 0)														/*����һ·��Ч������״̬��*/
		{
			MeterRunState3[CO_IDAuth] = MeterRunState3[CO_IDAuth] |CB_IDAuth;
		}
		if(MeterRunState3Old[CO_IDAuth] != MeterRunState3[CO_IDAuth])       					/*�仯д*/
		{
			InF_Write_Data(C_Msg_Communication, CMeter_Work_State3, MeterRunState3, CLMeter_Work_State3, C_W_SafeFlag);
		}
	}
	else																						/*�ն�*/
	{
		MeterRunState3Old[CO_IDAuth_T] = MeterRunState3[CO_IDAuth_T];
		MeterRunState3[CO_IDAuth_T] = MeterRunState3[CO_IDAuth_T] & (~CB_IDAuth_T);

		if(Com_Conect.ConectOverTime_termal != 0)												/*����һ·��Ч������״̬��*/
		{
			MeterRunState3[CO_IDAuth_T] = MeterRunState3[CO_IDAuth_T] | CB_IDAuth_T;
		}
		if(MeterRunState3Old[CO_IDAuth_T] != MeterRunState3[CO_IDAuth_T])   					/*�仯д*/
		{
            InF_Write_Data(C_Msg_Communication, CMeter_Work_State3, MeterRunState3, CLMeter_Work_State3, C_W_SafeFlag);
		}
	}
}

/*******************************************************************************
����ԭ�ͣ�void SF_NewReport(uchar8 channel,uchar8 EventNo,uchar8 V_Flag)
�����������¼�����ʱд33201F00
���������EventNo���¼���
		State��C_Happen_EventMsg �¼�����������C_End_EventMsg �¼��ָ�����
�����������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
void SF_NewReport(uchar8 channel, uchar8 EventNo, uchar8 V_Flag)
{
    uchar8		V_EventLine, i = 0, j = 0, *V_NewReportTemp, V_Temp[C_NewReportCRCLen] = {0};
	ushort16	V_Crc,V_Len = C_NewReportLen, V_DataLen = CLLossVolage_Report_Mode, V_usDataEncode;
    uchar8		V_Type = C_FollowReportType, V_Mode = 0;
    ulong32		V_EventOAD;
    uchar8		V_MeterReportParameter = C_MeterReportClose;

	switch(channel)
	{
		case	C_ReportChannel1:
				V_NewReportTemp = &GV_NewReport1[0];
				break;
		case	C_ReportChannel2:
				V_NewReportTemp = &GV_NewReport2[0];
				break;
		case	C_ReportChannel3:
				V_NewReportTemp = &GV_NewReport3[0];
				break;
		default:
                return;
	}

    if( PF_Check_CRC( V_NewReportTemp, V_Len + 2 ) != C_OK )						/*����������˲����㣬ֱ���Ƚ��ȳ�*/
	{
		for( i = 0; i < V_Len; i++ )
		{
			V_NewReportTemp[i] = 0;
		}
	}

    i = 0;
    for( V_EventLine = 0; V_EventLine < Str_698EventReport_Len; V_EventLine++ )		/*ȷ����Ӧ�¼�*/
    {
        if(EventNo == Str_698EventReport[V_EventLine].EventNo)
        {
            break;
        }
    }
    if( V_EventLine >= Str_698EventReport_Len )
    {
        return;
    }
    V_DataLen = CLReport_Type;
    V_EventOAD = Inf_GetEventModeDI(V_EventLine, C_ReportType);							/*��ȡ�ϱ�����*/
    InF_Read_Data(V_EventOAD, &V_Type, &V_DataLen, &V_usDataEncode );										/*��״̬�֣����û�гɹ���Ĭ�������ϱ�*/
    if( ( V_Type != C_FollowReportType ) && ( V_Type != C_ActiveReportType ) )      	/*ֻ����0������1*/
    {
        V_Type = C_FollowReportType;
    }
    if(EventNo != C_TolClearEventNo)
    {
        if( ( EventNo != C_EventClearEventNo )
		  || ( ( EventNo == C_EventClearEventNo )
			 && ( ( C_OK == InF_Read_Data(CEventClear_Report_Mode, &V_Mode, &V_DataLen, &V_usDataEncode ) )
			   && ( ( V_Mode == C_ReportHP ) || ( V_Mode == C_ReportAll ) ) ) ) )		/*��ģʽ��*/
    	{
            V_Temp[i * 3] = EventNo;
            /*2020��׼�����ϱ�2005*/
            V_MeterReportParameter = Inf_MeterReportOpen(C_PowerOn, C_FirstNo); 		/*�ж��Ƿ����ϱ�ͨ���͵��ܱ������ϱ�����ģ��ͨ��*/

            if( ( V_MeterReportParameter == C_MeterReportOpen ) && ( V_Type == C_ActiveReportType ) && ( channel == C_Module ) )
            {/*���ܱ����������ϱ����¼������ϱ������緢���⣬�����ĸ�ֵ3���ϱ�����*/
                if(EventNo != C_PowerfailEventNo)
                {
                    V_Temp[i * 3 + 1] = C_ActiveReportMaxNum;	                    	/*����ֵ�����������ϱ�����*/
                }
                else
                {
                    if ( GStr_PowerfailStr.MeterState != C_Happen_EventMsg )             	/*�����ڵ͹����·���*/
                    {
                        Inf_Event_REPORTONumDeal(C_NewReportFlag);              		/*������ϱ�����������¼����������ְ��¼��ϱ��ֵ����ϱ��Ͱ��б���Ҳ��3��*/
                    }
                    else
                    {
                        V_Temp[i * 3 + 1] = 0;											/*���緢���������ﴦ��*/
                    }
                }
            }
            else
            {
                V_Temp[i * 3 + 1] = 0;									/*����ֵ*/
            }

            V_Temp[i * 3 + 2] = V_Type;
            i++;
        }
        for( j = 0; j < (*(V_NewReportTemp + C_NewReportNumByte) ); j++ )
        {
            if( ( EventNo == V_NewReportTemp[j * 3] )
             || ( ( EventNo == C_EventClearEventNo ) && ( V_NewReportTemp[j * 3] != C_TolClearEventNo ) && (V_Flag == C_CleanOtherEvent ) ) )
            {
                continue;
            }
            V_Temp[i * 3] = V_NewReportTemp[j * 3];
            V_Temp[i * 3 + 1]=V_NewReportTemp[j * 3 + 1];
            V_Temp[i * 3 + 2]=V_NewReportTemp[j * 3 + 2];
            i++;
            if(i >= C_NewReportMaxNum)									/*����¼��ĸ����������ĸ��������˳�*/
            {
                break;
            }
        }
        V_Temp[C_NewReportNumByte] = i;
    }
    else
    {
    	if( ( C_OK == InF_Read_Data(CTolClear_Report_Mode, &V_Mode, &V_DataLen, &V_usDataEncode ) ) && ( ( V_Mode == C_ReportHP ) || ( V_Mode == C_ReportAll ) ) )		/*��ģʽ��*/
    	{
	        if( (InF_JudgeKeyStatus() == C_StateOfOfficialKey ) && ( InF_JudgeIJTimer() == C_Error ) )	/*���ǲ�����Կ(��Կ)���߳���*/
	        {
	            V_Temp[i * 3] = EventNo;
	            if( ( channel == C_Module ) && ( C_ActiveReportType == V_Type ) )
	            {
	                V_Temp[i * 3 + 1] = C_ActiveReportMaxNum;			/*���������ϱ�����*/
	            }
	            else
	            {
	                V_Temp[i * 3 + 1] = 0;                              /*���������ϱ�����*/
	            }
	            V_Temp[i * 3 + 2] = V_Type;;
	            V_Temp[C_NewReportNumByte] = 1;
	        }
	    }
    }
	PF_CopyDataBytes_698(V_Temp, V_NewReportTemp, V_Len);
	V_Crc = PF_Cal_CRC(V_NewReportTemp, V_Len);
	PF_Ushort16ToBuffer2(&V_NewReportTemp[V_Len], &V_Crc);

    if(channel == C_Module)
    {
        if(EventNo == C_PowerfailEventNo)                              /*�������ϱ�����ʱ��ʱ��*/
        {
            Inf_Comm_REPORTFlagClear(C_NewReportFlag_EventType);
        }
        else
        {
            Inf_Comm_REPORTFlagClear(C_NewReportFlag_Other);
        }
    }
}
/*******************************************************************************
����ԭ�ͣ�void SF_DeletReport(uchar8 channel,uchar8 EventNo)
�����������¼�����ʱд33201F00
���������EventNo���¼���
		State��C_Happen_EventMsg �¼�����������C_End_EventMsg �¼��ָ�����
�����������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
void SF_DeletReport(uchar8 channel, uchar8 EventNo)
{
	uchar8		*V_NewReportTemp, i = 0, j = 0, V_Temp[C_NewReportCRCLen] = {0};
	ushort16	V_Crc, V_Len = C_NewReportLen;

	switch(channel)
	{
        case    C_ReportChannel1:
				V_NewReportTemp = &GV_NewReport1[0];
				break;
		case	C_ReportChannel2:
				V_NewReportTemp = &GV_NewReport2[0];
				break;
		case	C_ReportChannel3:
				V_NewReportTemp = &GV_NewReport3[0];
				break;
		default:
				return;
	}
	if( ( PF_Check_CRC(V_NewReportTemp, V_Len + 2) != C_OK ) || ( *(V_NewReportTemp+C_NewReportNumByte) > C_NewReportMaxNum ) || ( EventNo == C_ListEventNo ) )/*2020��׼�����ϱ�2005*/
	{
		for( i = 0; i < V_Len; i++ )
		{
			V_NewReportTemp[i] = 0;
		}
	}
	i = 0;
	if(EventNo == C_ExceptPowerFailListEventNo)                /*������ϱ�ȷ��33200200��������ڵ����ϱ��������������*�����������¼�*/
	{
		for( j = 0; j < (*(V_NewReportTemp+C_NewReportNumByte)); j++ )
		{
			if( ( V_NewReportTemp[j * 3 + 1] == C_ActiveReportMaxNum ) || ( V_NewReportTemp[j * 3 + 2] == C_FollowReportType ) )
			{
				V_Temp[i * 3] = V_NewReportTemp[j * 3];
				V_Temp[i * 3 + 1] = V_NewReportTemp[j * 3 + 1];
				V_Temp[i * 3 + 2] = V_NewReportTemp[j * 3 + 2];
				i++;
			}
		}
	}
	else
	{
		for( j = 0; j < ( *(V_NewReportTemp + C_NewReportNumByte ) ); j++ )
		{
			if(EventNo != V_NewReportTemp[j * 3] )
			{
				V_Temp[i * 3] = V_NewReportTemp[j * 3];
				V_Temp[i * 3 + 1] = V_NewReportTemp[j * 3 + 1];
				V_Temp[i * 3 + 2] = V_NewReportTemp[j * 3 + 2];
				i++;
			}
		}
	}

	V_Temp[C_NewReportNumByte] = i;
	PF_CopyDataBytes_698(V_Temp, V_NewReportTemp, V_Len);
	V_Crc = PF_Cal_CRC(V_NewReportTemp, V_Len);
	PF_Ushort16ToBuffer2(&V_NewReportTemp[V_Len], &V_Crc);
	if( ( EventNo == C_PowerfailEventNo ) && ( channel == C_Module ) )
	{
		Inf_Event_REPORTONumDeal(0);   							/*������ʱ����������*/
	}
}
/*******************************************************************************
����ԭ�ͣ�void Inf_NewReport(uchar8 channel,uchar8 EventNo,uchar8 V_Flag)
�����������¼�����ʱд33201F00
���������EventNo���¼���
			State��C_Happen_EventMsg �¼���������	C_End_EventMsg �¼��ָ�����
�����������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
void Inf_NewReport(uchar8 channel, uchar8 EventNo, uchar8 V_Flag)
{
	if( channel == C_ReportChannelAll )
	{
		SF_NewReport(C_ReportChannel1, EventNo,V_Flag);
		SF_NewReport(C_ReportChannel2, EventNo,V_Flag);
		SF_NewReport(C_ReportChannel4, EventNo,V_Flag); 		/*����ͨ�����ϱ�*/
		SF_NewReport(C_ReportChannel3, EventNo,V_Flag);
	}
}
/*******************************************************************************
����ԭ�ͣ�void Inf_DeletReport(uchar8 channel,uchar8 EventNo)
�����������¼�����ʱд33201F00
���������EventNo���¼���
			State��C_Happen_EventMsg �¼���������	��C_End_EventMsg �¼��ָ�����
�����������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
void Inf_DeletReport(uchar8 channel, uchar8 EventNo)
{
	if(channel == C_ReportChannelAll)
	{
		SF_DeletReport(C_ReportChannel1, EventNo);
		SF_DeletReport(C_ReportChannel2, EventNo);
		SF_DeletReport(C_ReportChannel3, EventNo);
		SF_DeletReport(C_ReportChannel4, EventNo);
	}
	else if(channel == C_ReportChannel1)
	{
		SF_DeletReport(C_ReportChannel1, EventNo);
	}
	else if(channel == C_ReportChannel2)
	{
		SF_DeletReport(C_ReportChannel2, EventNo);
	}
	else if(channel == C_ReportChannel3)
	{
		SF_DeletReport(C_ReportChannel3, EventNo);
	}
	else if(channel == C_ReportChannel4)
	{
		SF_DeletReport(C_ReportChannel4, EventNo);
	}
}
/*******************************************************************************
����ԭ�ͣ�void Inf_ReportList(uchar8 channel,uchar8 EventNo,uchar8 Action)
�����������¼�����ʱд33201F00
���������channel:ͨ���� EventNo���¼���
�����������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
void Inf_ReportList(uchar8 channel, uchar8 EventNo, uchar8 Action)
{
	if(Action == C_NewReport)
	{
		Inf_NewReport(channel, EventNo, C_CleanOtherEvent);
	}
	else if(Action == C_DeletReport)
	{
		Inf_DeletReport(channel, EventNo);
	}
}

/*****************************************************************************************
����ԭ�ͣ�uchar8 SF_Judge_ServiceRight(Str_Comm_698_RW *pV_698RWPara, Str_Comm_645 *pV_698Frame)
�������������ݶ����ʶ�жϵ�ǰ�����Ƿ�Ȩ������
���������pV_698RWPara����������ṹ��
          pV_698Frame��֡�����ṹ���ַ
��������� �����ݴ��pV_698Frame->Data,������д���ݽ�����pV_698RWPara->Wt_OI
���ز����� ���ذ�ȫȨ���Ƿ�����Ҫ��C_OK��ʾ����Ȩ��Ҫ��
����λ�ã�
��    ע:
*****************************************************************************************/
uchar8 SF_Judge_ServiceRight(Str_Comm_698_RW *pV_698RWPara, Str_Comm_645 *pV_698Frame)
{
	ushort16	V_OI;
	uchar8		V_SerRequestPer, V_ServiceType, k;
	uchar8		i, V_ulFlageTemp, V_DataTemp[2], V_result = 0;
	ushort16	V_ulModeTemp, V_ulDisplacement;
    uchar8		V_Num, V_ReadWriteFlag;

	V_SerRequestPer = pV_698Frame->RNSICBit;					/*��ȫ����*/
	V_ServiceType = pV_698RWPara->ServiceFlag_First;			/*��������*/

    if( V_ServiceType == C_CONNECT_Request )					/*Ӧ������ʱ��ֱ��Ȩ�޸�ֵΪOK*/
	{
        if(pV_698Frame->AddressFlag == C_AddrTypePtoP)
        {
            pV_698RWPara->Wt_OI[0].Wt_Result = C_OK;
            pV_698RWPara->Rd_OI[0].Rd_Result = C_OK;
        }
        else
        {
            pV_698RWPara->Wt_OI[0].Wt_Result = C_OtherErr_DAR;
            pV_698RWPara->Rd_OI[0].Rd_Result = C_OtherErr_DAR;
        }
		return	C_OK;
	}

	if( pV_698RWPara->ServiceFlag_Second == C_GETNext_Request )	/*������֡û�б�ʶ�룬�жϰ�ȫȨ���Ƿ�����֡��ͬ����ͬ����C_OK,��ͬ����C_SCMismatch_DAR*/
	{
		pV_698RWPara->lastRNSICBit = pV_698Frame->RNSICBit;

		if( pV_698Frame->RNSICBit == pV_698RWPara->firstRNSICBit )
		{
			return C_OK;
		}
		else
		{
			pV_698RWPara->FrameNUM ++;	            			/*Ӧ�ò�֡���+1*/

			for( k = 0; k< (pV_698RWPara->RWOI_Num); k++ )
			{
				pV_698RWPara->Rd_OI[k].Rd_Result = C_SCMismatch_DAR;
			}
			return C_SCMismatch_DAR;
		}
	}
	else
	{
		pV_698RWPara->firstRNSICBit = pV_698Frame->RNSICBit;
		pV_698RWPara->lastRNSICBit = pV_698Frame->RNSICBit;
	}

	if( InF_JudgeIJTimer( ) == C_OK )
	{
        for( k = 0; k < ( pV_698RWPara->RWOI_Num ); k++)
		{
            pV_698RWPara->Wt_OI[k].Wt_Result = C_OK;
            pV_698RWPara->Rd_OI[k].Rd_Result = C_OK;
        }
		return	C_OK;
	}

	if( ( pV_698Frame->C & 0x20 ) == 0x20 )	    				/*��֡��־*/
	{
		return	C_OK;
	}

    V_ReadWriteFlag = 0;

    if ( ( ( V_ServiceType == C_SET_Request ) || ( V_ServiceType == C_ACTION_Request ) )
      && ( ( pV_698RWPara->ServiceFlag_Second ) == C_SETGETNormalList_Request ) )		/*������������һ��ֵ����03*/
    {
        V_Num = 2;
    }
    else
    {
        V_Num = 1;
    }

	for( k = 0; k < ( pV_698RWPara->RWOI_Num ); k++)
	{
        if ( ( ( V_ServiceType == C_GET_Request ) && ( pV_698RWPara->Rd_OI[k].Rd_Result != C_OK ) )
          || ( ( V_ServiceType != C_GET_Request ) && ( pV_698RWPara->Wt_OI[k].Wt_Result != C_OK ) ) )
        {
            continue;
        }

        for( V_ReadWriteFlag = 0; V_ReadWriteFlag < V_Num; V_ReadWriteFlag++)
        {
            if(V_ReadWriteFlag != 0)
            {
                V_ServiceType = C_GET_Request;
            }

            if(pV_698Frame->AddressFlag == C_AddrTypePtoAll)							/*�㲥*/
            {
                if ( ( pV_698RWPara->ServiceFlag_First == C_ACTION_Request )
                  && ( ( pV_698RWPara->Wt_OI[0].WtOI == CBroadcastTimeM )
                    || ( pV_698RWPara->Wt_OI[k].WtOI == 0x50000300 )
                    || ( pV_698RWPara->Wt_OI[k].WtOI == 0xF2077F00 )
                    || ( pV_698RWPara->Wt_OI[k].WtOI == 0xF3000500 )
                    || ( pV_698RWPara->Wt_OI[k].WtOI == 0xF3010500 )
                    || ( pV_698RWPara->Wt_OI[k].WtOI == 0xF3000600 )
                    || ( pV_698RWPara->Wt_OI[k].WtOI == 0xF3010600 ) ) )
                {
                    pV_698RWPara->Wt_OI[k].Wt_Result = C_OK;
                }
                else
                {
                    pV_698RWPara->Wt_OI[k].Wt_Result = C_RWForbid_DAR;
                    continue;
                }
            }
            else
            {
                if ( ( pV_698Frame->AddressFlag != C_AddrTypePtoP )
                  && ( pV_698Frame->AddressFlag != C_AddrTypePtoM )
                  && ( pV_698RWPara->ServiceFlag_First != C_GET_Request ) )				/*���ǵ�����ַ���鲥��ַ�����ҷ������Ͳ��Ƕ�*/
                {
                    pV_698RWPara->Wt_OI[k].Wt_Result = C_RWForbid_DAR;
                    continue;
                }
            }

            if ( ( pV_698RWPara->Wt_OI[k].WtOI == 0x80008300 )
              || ( pV_698RWPara->Wt_OI[k].WtOI == 0x20157F00 ) )   						/*���ĺ�բ����ȷ���ϱ�״̬��*/
            {
                pV_698RWPara->Wt_OI[k].Wt_Result = C_OK;
                continue;
            }

            if ( ( pV_698RWPara->Wt_OI[k].WtOI == CDI_IRCReq )          				/*�����ѯ����*/
              || ( pV_698RWPara->Wt_OI[k].WtOI == CDI_IR_ExtAuth ) )
            {
                if(V_ServiceType == C_ACTION_Request)
                {
                    pV_698RWPara->Wt_OI[k].Wt_Result = C_OK;
                    continue;
                }
            }

            if ( ( ( V_ServiceType == C_SET_Request ) && ( pV_698RWPara->Wt_OI[k].WtOI == CGPS_Signal ) )
              || ( ( V_ServiceType == C_GET_Request ) && ( pV_698RWPara->Rd_OI[k].RdOI.OAD == CGPS_Signal ) ) )
            {
                pV_698RWPara->Wt_OI[k].Wt_Result = C_OK;
                continue;
            }

            switch( V_ServiceType )
            {
                case	C_GET_Request:
                {
                    V_ulDisplacement = 12;
                    V_OI = ( pV_698RWPara->Rd_OI[k].RdOI.OAD >> 16 );
                }break;
                case	C_SET_Request:
                {
                    V_ulDisplacement = 8;
                    V_OI = ( pV_698RWPara->Wt_OI[k].WtOI >> 16 );
                }break;
                case	C_ACTION_Request:
                {
                    V_ulDisplacement = 4;
                    V_OI = ( pV_698RWPara->Wt_OI[k].WtOI >> 16 );
                }break;
                default:
                {
                    V_ulDisplacement = 0;
                    V_OI = (pV_698RWPara->Rd_OI[k].RdOI.OAD >> 16);
                }break;
            }

            V_ulFlageTemp = V_SerRequestPer;

            if( SF_Judge_SetServiceRight(V_OI, &V_ulModeTemp) == C_OK )
            {
                V_ulModeTemp = (V_ulModeTemp >> V_ulDisplacement);
                PF_Ushort16ToBuffer2(V_DataTemp, &V_ulModeTemp);
            }
            else
            {
                for( i = 0; i < GV_SafeModeParameters1Len; i++)
                {
                    if( V_OI == GV_SafeModeParameters1[i].DI )
                    {
                         V_ulModeTemp = ( GV_SafeModeParameters1[i].Mode >> V_ulDisplacement );
                         PF_Ushort16ToBuffer2(V_DataTemp, &V_ulModeTemp);
                         break;
                    }
                }

                if( i >= GV_SafeModeParameters1Len )
                {
                    for( i = 0; i < GV_SafeModeParameters2Len; i++)
                    {
                        if ( ( V_OI | GV_SafeModeParameters2[i].DefaultDI ) == GV_SafeModeParameters2[i].DI )
                        {
                             V_ulModeTemp = ( GV_SafeModeParameters2[i].Mode >> V_ulDisplacement );
                             PF_Ushort16ToBuffer2(V_DataTemp, &V_ulModeTemp);
                             break;
                         }
                    }

                    if(i >= GV_SafeModeParameters2Len)
                    {
                        V_ulModeTemp = 0x4110 >> V_ulDisplacement;	   		/*��������֧�����ļ�MAC��ȡ�����ã�������֧��*/
                        PF_Ushort16ToBuffer2(V_DataTemp, &V_ulModeTemp);
                    }
                }
            }

            if ( ( ( ( V_ulModeTemp & 0x0F ) == 0x00 ) && ( V_ServiceType == C_SET_Request ) )
               ||( ( ( V_ulModeTemp & 0x0F ) == 0x00 ) && ( V_ServiceType == C_ACTION_Request ) ) )
            {
                pV_698RWPara->ResponedNum++;								/*�Ѿ�Ӧ�����1*/
                V_result = C_RWForbid_DAR;
            }
            else
            {
                if ( ( V_OI != CDate_Week_698 ) || ( V_ServiceType != C_ACTION_Request ) )
                {
                    for( i = 0; i < 4; i++)
                    {
                        if( (V_DataTemp[0] & (8 >> i) ) != 0 )
                        {
                            break;
                        }
                    }

                    if( i == 0 )
                    {
                        V_DataTemp[0] |= 0x0F;
                    }
                    else if( i == 1 )
                    {
                        V_DataTemp[0] |= 0x07;
                    }
                    else if( i == 2 )
                    {
                        V_DataTemp[0] |= 0x03;
                    }
                }
                else    													/*�㲥Уʱ�������Ȩ��*/
                {
                    ;
                }

                if( (V_DataTemp[0] & V_ulFlageTemp) != 0x00 )
                {
                    V_result = C_OK;

                    if ( ( ( pV_698RWPara->Wt_OI[k].WtOI == C_IRAuth_Timer )  &&  ( V_ServiceType == C_SET_Request ) )	/*���ú���ʱЧ*/
                     ||  ( ( ( pV_698RWPara->Wt_OI[k].WtOI == C_ImmidMethod_TriggerOnce )
                          || ( pV_698RWPara->Wt_OI[k].WtOI == C_ImmidMethod_AddOneRelatedOAD )
                          || ( pV_698RWPara->Wt_OI[k].WtOI == C_ImmidMethod_DelOneRelatedOAD )
                          || ( pV_698RWPara->Wt_OI[k].WtOI == C_ImmidMethod_AddManyRelatedOAD )
                          || ( pV_698RWPara->Wt_OI[k].WtOI == C_ImmidMethod_DelAllRelatedOAD ) )
                       && ( V_ServiceType == C_ACTION_Request ) ) )
                    {
                        if ( ( pV_698Frame->RNSICBit == 0x04 )         		/*ͨ���� ����+������֤ ��ʽ*/
                          && ( pV_698Frame->SICMAC_Type == RN_698 ) )  		/*������+RN��Ӧ��ȫ��֤��ƥ��*/
                        {
                            pV_698RWPara->ResponedNum++;					/*�Ѿ�Ӧ�����1*/
                            V_result = C_SCMismatch_DAR;
                        }													/*else֧������+SID_MAC������*/
                    }														/*else OK*/
                }
                else
                {
                    pV_698RWPara->ResponedNum++;							/*�Ѿ�Ӧ�����1*/
                    V_result = C_SCMismatch_DAR;
                }
            }

            if(V_ServiceType == C_GET_Request)
            {
                pV_698RWPara->Rd_OI[k].Rd_Result = V_result;

            }
            else
            {
				pV_698RWPara->Wt_OI[k].Wt_Result = V_result;
                if(V_result != C_OK)
                {
                    pV_698RWPara->Wt_OI[k].DataLen = 0;
                }
            }

            if(V_ReadWriteFlag != 0)
            {
                V_ServiceType = pV_698RWPara->ServiceFlag_First;
            }
        }
	}

	return C_OK;
}
/*******************************************************************************
����ԭ�ͣ�uchar8	SF_Judge_SetServiceRight(ushort16 V_OI,ushort16 *V_ulMode)
����������ȡ���ݲ�����OIȨ��
���������OI����Ȩ�޲���
���������
���ز�����	OI���ҽ��C_OK��ʾ��ӦOI������Ȩ�ޣ�����û����Ȩ��
����λ�ã�
��    ע��
*******************************************************************************/
uchar8	SF_Judge_SetServiceRight(ushort16 V_OI, ushort16 *V_ulMode)
{
	uchar8	  V_usNum, V_Data[1024] = {0}, k;
	uchar8	  V_ucTurn = 0;
	ushort16  V_usLen, V_usDataEncode;
	ushort16  V_ulOITemp;

	V_usLen = CLSafeModeParaNat3_Num;
	V_ucTurn = InF_Read_Data(CSafeModeParaNat3_Num, &V_usNum, &V_usLen, &V_usDataEncode);
	if( V_ucTurn != C_OK )
	{
		return V_ucTurn;
	}
	V_usLen = CLSafeModeParaNat3;
	V_ucTurn = InF_ReadOADTab_Data(CSafeModeParaNat3, V_Data, &V_usLen);
	if( V_ucTurn != C_OK )
	{
		return V_ucTurn;
	}

	for( k = 0; k < V_usNum; k++ )
	{
		PF_Buffer2ToUshort16(&V_Data[k * 4], &V_ulOITemp);
		if( V_OI == V_ulOITemp )
		{
			PF_Buffer2ToUshort16(&V_Data[k * 4 + 2], V_ulMode);
			break;
		}
	}
	if(k < V_usNum)
	{
		V_ucTurn = C_OK;
	}
	else
	{
		V_ucTurn = C_Error;
	}
	return V_ucTurn;
}
/*******************************************************************************
����ԭ�ͣ�void PF_HexToBCD698(uchar8 *BCDBuffer,ulong32 *HexBuffer,uchar8 BCDLen)
����������1��long32������
���������BCDBufferΪBCD�����ֽڵ�ַ,HexBufferΪHEX����ַ,BCDLenΪBCD�����ݳ���
������������HexBuffer��ַ��ʼ��ת��������
���ز�����
����λ�ã�
��    ע��BCD������󳤶Ȳ��ܴ���4,���ݳ��ȴ���4�ֽڰ���4�ֽ�ת��
*******************************************************************************/
void PF_HexToBCD698(uchar8 *BCDBuffer, ulong32 *HexBuffer, uchar8 BCDLen)
{
	uchar8	i, V_ucData[5], j;
	ulong32	V_ulData;

	V_ulData = *HexBuffer;
	for( j = 0; j < 5; j++ )
	{
		if(V_ulData == 0)
		{
			break;
		}
		V_ucData[j] = V_ulData % 10;
		V_ulData /= 10;
		i = V_ulData % 10;
		i <<= 4;
		V_ucData[j] |= i;
		V_ulData /= 10;
	}
	for( ; j < 5; j++ )
	{
		V_ucData[j] = 0;
	}
	PF_CopyDataBytes(V_ucData, BCDBuffer, BCDLen);
}
/*******************************************************************************
����ԭ�ͣ�ushort16	SF_DataExchangeTo698_Where(uchar8 *pV_698Data,uchar8 *pV_645Data,ulong32 OAD)
����������λ����Ϣ��������ת��
����������������ݽṹ��
���������ת��������ݣ���Ž����ṹ��
���ز��������ݳ���
����λ�ã�
��    ע��
*******************************************************************************/
ushort16 SF_DataExchangeTo698_Where(uchar8 *pV_698Data, uchar8 *pV_645Data, ulong32 OAD)
{
	uchar8 V_698Offset = 0, i, j;

	/*************����\γ��*************/
    if( ( OAD & 0xFF ) == 0 )
    {
        for( j = 0; j < 2; j++ )
        {
			pV_698Data[V_698Offset] = C_structure;
			V_698Offset++;
			pV_698Data[V_698Offset] = 4;
			V_698Offset++;
			pV_698Data[V_698Offset] = C_enum;
			V_698Offset++;
            pV_698Data[V_698Offset] = pV_645Data[j * 4];
            V_698Offset++;
			for( i = 0; i < 3; i++ )
			{
				pV_698Data[V_698Offset] = C_unsigned;
				V_698Offset++;
                pV_698Data[V_698Offset] = pV_645Data[1 + i + j * 4];
				V_698Offset++;
			}
        }
        /*************�߶�*************/
        pV_698Data[V_698Offset] = C_double_long_unsigned;
		V_698Offset++;
        PF_CopyDataBytes(&pV_645Data[i + 1 + ( j - 1 ) * 4], &pV_698Data[V_698Offset], 4);
        V_698Offset += 4;
    }
    else if( ( OAD & 0xFF ) < 3)
    {
		pV_698Data[V_698Offset] = C_enum;
		V_698Offset++;
        pV_698Data[V_698Offset] = pV_645Data[0];
        V_698Offset++;
		for( i = 0; i < 3; i++ )
		{
			pV_698Data[V_698Offset] = C_unsigned;
			V_698Offset++;
            pV_698Data[V_698Offset] = pV_645Data[i + 1];
			V_698Offset++;
        }
    }
    else
    {
	/*************�߶�*************/
		PF_CopyDataBytes(&pV_645Data[0], &pV_698Data[V_698Offset], 4);
		V_698Offset += 4;
    }
	return V_698Offset;
}
/*******************************************************************************
����ԭ�ͣ�ushort16	SF_DataExchangeTo698_Ladder(uchar8 *pV_698Data,uchar8 *pV_645Data,uchar8 V_Off)
�������������ݵ����������ת��
����������������ݽṹ��
���������ת��������ݣ���Ž����ṹ��
���ز��������ݳ���
����λ�ã�
��    ע��
*******************************************************************************/
ushort16	SF_DataExchangeTo698_Ladder(uchar8 *pV_698Data, uchar8 *pV_645Data, uchar8 V_Off)
{
	uchar8		V_698Offset = 0, i, j;
	ushort16	V_usLen698;

	/*************����ֵ*************/
	if(V_Off == 0)
	{
		pV_698Data[V_698Offset] = C_array;
		V_698Offset++;
		pV_698Data[V_698Offset] = 6;
		V_698Offset++;
		for( i = 0; i < 6; i++ )
		{
			pV_698Data[V_698Offset] = C_double_long_unsigned;
			V_698Offset++;
			V_usLen698 = SF_DataExchangeTo698_BasicData(&pV_698Data[V_698Offset - 1], &pV_645Data[4 * i], 4, 4);
			V_698Offset += V_usLen698;
		}
		/*************���ݵ��*************/
		pV_698Data[V_698Offset] = C_array;
		V_698Offset++;
		pV_698Data[V_698Offset] = 7;
		V_698Offset++;
		for( i = 0; i < 7; i++ )
		{
			pV_698Data[V_698Offset] = C_double_long_unsigned;
			V_698Offset++;
			V_usLen698 = SF_DataExchangeTo698_BasicData(&pV_698Data[V_698Offset - 1], &pV_645Data[24 + 4 * i], 4, 4);
			V_698Offset += V_usLen698;
		}
		/*************������*************/
		pV_698Data[V_698Offset] = C_array;
		V_698Offset++;
		pV_698Data[V_698Offset] = 4;
		V_698Offset++;
		for( i = 0; i < 4; i++ )
		{
			pV_698Data[V_698Offset] = C_structure;
			V_698Offset++;
			pV_698Data[V_698Offset] = 3;
			V_698Offset++;
			for( j = 0; j < 3; j++ )
			{
				pV_698Data[V_698Offset] = C_unsigned;
				V_698Offset++;
				V_usLen698 = SF_DataExchangeTo698_BasicData(&pV_698Data[V_698Offset - 1], &pV_645Data[52 + ( 3 * i ) + j], 1, 1);
				V_698Offset += V_usLen698;
			}
		}
	}
	else if(V_Off == 1)
	{
		for( i = 0 ; i < 6; i++ )
		{
			pV_698Data[V_698Offset] = C_double_long_unsigned;
			V_698Offset++;
			V_usLen698 = SF_DataExchangeTo698_BasicData(&pV_698Data[V_698Offset - 1], &pV_645Data[4 * i], 4, 4);
			V_698Offset += V_usLen698;
		}
	}
	else if(V_Off == 2)
	{
	/*************���ݵ��*************/
		for( i = 0; i < 7; i++ )
		{
			pV_698Data[V_698Offset] = C_double_long_unsigned;
			V_698Offset++;
			V_usLen698 = SF_DataExchangeTo698_BasicData(&pV_698Data[V_698Offset - 1], &pV_645Data[4 * i], 4, 4);
			V_698Offset += V_usLen698;
		}
	}
	else if( V_Off == 3 )
	{
	/*************������*************/
		for( i = 0; i < 4; i++ )
		{
			pV_698Data[V_698Offset] = C_structure;
			V_698Offset++;
			pV_698Data[V_698Offset] = 3;
			V_698Offset++;
			for( j = 0; j < 3; j++ )
			{
				pV_698Data[V_698Offset] = C_unsigned;
				V_698Offset++;
				V_usLen698 = SF_DataExchangeTo698_BasicData(&pV_698Data[V_698Offset - 1], &pV_645Data[( 3 * i ) + j], 1, 1);
				V_698Offset += V_usLen698;
			}
		}
	}
	return V_698Offset;
}
/*******************************************************************************
����ԭ�ͣ�uchar8	SF_DataExchangeTo645_Where(Str_Comm_698_RW *pV_698RWPara,Str_DI0_DataType_PaTable	*p_TableAddr)
����������λ����Ϣ��������ת��
����������������ݽṹ��
���������ת��������ݣ���Ž����ṹ��
���ز��������ݳ���
����λ�ã�
��    ע��
*******************************************************************************/
uchar8	SF_DataExchangeTo645_Where(Str_Comm_698_RW *pV_698RWPara, Str_DI0_DataType_PaTable	*p_TableAddr)
{
	ushort16	V_Off = 0, V_ucLen = 20, V_usDataEncode;
	uchar8		*P_DataAddr, i, V_DataOff;
	uchar8		V_ucDataBuff[20] = {0};

	P_DataAddr = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data;
	V_DataOff = (uchar8)(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI);			/*ȡ������ƫ��*/

	if( V_DataOff == 0 )
	{
		V_Off += 2;
		if(P_DataAddr[V_Off] != C_structure)
		{
			return C_TypeErr_DAR;
		}
		V_Off += 2;
		for( i = 0; i < 8; i++ )
		{
			if( ( i == 0 ) || ( i == 4 ) )
			{
				if( P_DataAddr[V_Off] != C_enum )
				{
					return C_TypeErr_DAR;
				}
			}
			else
			{
				if( P_DataAddr[V_Off] != C_unsigned )
				{
					return C_TypeErr_DAR;
				}
			}
			V_Off++;

            V_ucDataBuff[i] = P_DataAddr[V_Off];
			V_Off++;
			if( i == 3 )
			{
				if(P_DataAddr[V_Off] != C_structure)
				{
					return C_TypeErr_DAR;
				}
				V_Off += 2;
			}
		}
		if( P_DataAddr[V_Off] != C_double_long_unsigned )
		{
			return C_TypeErr_DAR;
		}
		V_Off++;

        PF_CopyDataBytes(&P_DataAddr[V_Off], &V_ucDataBuff[i], 4);
		PF_CopyDataBytes(V_ucDataBuff, &P_DataAddr[0], 12);
		V_Off = 12;
	}
	else if( ( V_DataOff == 0x01 ) || ( V_DataOff == 0x02 ) )
	{
		if(P_DataAddr[V_Off] != C_structure)
		{
			return C_TypeErr_DAR;
		}
		V_Off += 2;
		for( i = 0; i < 4; i++ )
		{
			if( i == 0 )
			{
				if( P_DataAddr[V_Off] != C_enum )
				{
					return C_TypeErr_DAR;
				}
			}
			else
			{
				if( P_DataAddr[V_Off] != C_unsigned )
				{
					return C_TypeErr_DAR;
				}
			}
			V_Off++;

            V_ucDataBuff[i] = P_DataAddr[V_Off];
			V_Off++;

		}
		PF_CopyDataBytes(V_ucDataBuff, &P_DataAddr[0], 4);
		V_Off = 4;
		InF_Read_Data(CMeter_Position, V_ucDataBuff, &V_ucLen, &V_usDataEncode);					/*��ȡ���ݲ�λ����Ϣ����������һ��д���ݲ� */
		PF_CopyDataBytes(&P_DataAddr[0], &V_ucDataBuff[(V_DataOff - 1) * 4], 4);
		PF_CopyDataBytes(V_ucDataBuff, &P_DataAddr[0], CLMeter_Position);
	}
	else if( V_DataOff == 3 )
	{
		if(P_DataAddr[V_Off] != C_double_long_unsigned)
		{
			return C_TypeErr_DAR;
		}
		V_Off++;

		PF_CopyDataBytes(&P_DataAddr[V_Off], V_ucDataBuff, 4);
		PF_CopyDataBytes(V_ucDataBuff, &P_DataAddr[0], 4);
		V_Off = 4;
		InF_Read_Data(CMeter_Position, V_ucDataBuff, &V_ucLen, &V_usDataEncode);					/*��ȡ���ݲ�λ����Ϣ����������һ��д���ݲ� */
		PF_CopyDataBytes(&P_DataAddr[0], &V_ucDataBuff[(V_DataOff - 1) * 4], 4);
		PF_CopyDataBytes(V_ucDataBuff,  &P_DataAddr[0], CLMeter_Position);
	}
	else
	{
		return C_ObjectUndefine_DAR;
	}

	return C_OK;
}
/*******************************************************************************
����ԭ�ͣ�uchar8	SF_DataExchangeTo645_Ladder(Str_Comm_698_RW *pV_698RWPara,Str_Num_DataType_PaTable	*p_TableAddr,ushort16 *P_uc645Len)
�������������ʵ����������ת��
����������������ݽṹ��
���������ת��������ݣ���Ž����ṹ��
���ز��������ݳ���
����λ�ã�
��    ע��
*******************************************************************************/
uchar8	SF_DataExchangeTo645_Ladder(Str_Comm_698_RW *pV_698RWPara, Str_Num_DataType_PaTable	*p_TableAddr, ushort16 *P_uc645Len)
{
	ushort16	V_Off = 0, V_Off645 = 0;
	uchar8		i, j;
	uchar8		*P_DataAddr, V_DataOff;
	V_DataOff = (uchar8)(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI);			/*ȡ������ƫ��*/
	P_DataAddr = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data;
	if( V_DataOff == 0 )
	{
		if(P_DataAddr[V_Off] != C_structure)
		{
			return C_OtherErr_DAR;
		}
		V_Off++;
		if(P_DataAddr[V_Off] != 3)								/*3��*/
		{
			return C_OtherErr_DAR;
		}
		V_Off++;												/*��������ֽڵ���*/
/*����*/
		if(P_DataAddr[V_Off] != C_array)
		{
			return C_TypeErr_DAR;
		}
		V_Off++;												/*��������ֽڵ���*/
		if(P_DataAddr[V_Off] != 6)								/*6������*/
		{
			return C_TypeErr_DAR;
		}
		V_Off++;												/*��������ֽڵ���*/
		for( i = 0; i < 6; i++ )
		{
			if(P_DataAddr[V_Off] != C_double_long_unsigned)
			{
				return C_TypeErr_DAR;
			}
			j = 4;
			SF_DataExchangeTo645_BasicData(&P_DataAddr[V_Off], &P_DataAddr[V_Off645], 4, &j);
			V_Off645 += 4;
			V_Off = V_Off + 4 + 1;
		}
/*���ݵ��*/
		if(P_DataAddr[V_Off] != C_array)
		{
			return C_TypeErr_DAR;
		}
		V_Off++;												/*��������ֽڵ���*/
		if(P_DataAddr[V_Off] != 7)								/*7�����ݵ��*/
		{
			return C_TypeErr_DAR;
		}
		V_Off++;												/*��������ֽڵ���*/
		for( i = 0 ; i < 7; i++ )
		{
			if(P_DataAddr[V_Off] != C_double_long_unsigned)
			{
				return C_TypeErr_DAR;
			}
			j = 4;
			SF_DataExchangeTo645_BasicData(&P_DataAddr[V_Off], &P_DataAddr[V_Off645], 4, &j);
			V_Off645 += 4;
			V_Off = V_Off + 4 + 1;
		}
/*���ݽ�����*/
		if(P_DataAddr[V_Off] != C_array)
		{
			return C_TypeErr_DAR;
		}
		V_Off++;												/*��������ֽڵ���*/
		if(P_DataAddr[V_Off] != 4)								/*4��������*/
		{
			return C_TypeErr_DAR;
		}
		V_Off++;												/*��������ֽڵ���*/
		for( i = 0; i < 4; i++ )
		{
			if(P_DataAddr[V_Off] != C_structure)
			{
				return C_TypeErr_DAR;
			}
			V_Off++;
			if(P_DataAddr[V_Off] != 3)							/*3��*/
			{
				return C_OtherErr_DAR;
			}
			V_Off++;											/*��������ֽڵ���*/
			if(P_DataAddr[V_Off] != C_unsigned)					/*��*/
			{
				return C_OtherErr_DAR;
			}
			j = 1;
			SF_DataExchangeTo645_BasicData(&P_DataAddr[V_Off], &P_DataAddr[V_Off645], 1, &j);
			V_Off645 += 1;
			V_Off = V_Off + 1 + 1;
			if(P_DataAddr[V_Off] != C_unsigned)					/*��*/
			{
				return C_OtherErr_DAR;
			}
			j = 1;
			SF_DataExchangeTo645_BasicData(&P_DataAddr[V_Off], &P_DataAddr[V_Off645], 1, &j);
			V_Off645 += 1;
			V_Off = V_Off + 1 + 1;
			if(P_DataAddr[V_Off] != C_unsigned)					/*ʱ*/
			{
				return C_OtherErr_DAR;
			}
			j = 1;
			SF_DataExchangeTo645_BasicData(&P_DataAddr[V_Off], &P_DataAddr[V_Off645], 1, &j);
			V_Off645 += 1;
			V_Off = V_Off + 1 + 1;
			/*OneDataReversed(&P_DataAddr[V_Off645 - 3], &P_DataAddr[V_Off645 - 3], 3);*/
		}
	}
	else 														/*���Ǽ��ϲ�����д*/
	{
		return C_RWForbid_DAR;
	}
	*P_uc645Len = (uchar8)V_Off645;
	return C_OK;
}
/*******************************************************************************
����ԭ�ͣ�uchar8	SF_DataExchangeTo645_Fate(Str_Comm_698_RW *pV_698RWPara,Str_Num_DataType_PaTable	*p_TableAddr,ushort16 *P_uc645Len)
�������������ʵ����������ת��
����������������ݽṹ��
���������ת��������ݣ���Ž����ṹ��
���ز��������ݳ���
����λ�ã�
��    ע��
*******************************************************************************/
uchar8	SF_DataExchangeTo645_Fate(Str_Comm_698_RW *pV_698RWPara, Str_Num_DataType_PaTable	*p_TableAddr, ushort16 *P_uc645Len)
{
	ushort16	V_Off = 0, V_Off645 = 0;
	uchar8		i, j;
	uchar8		*P_DataAddr, V_DataOff;
	Str_DI0_DataType_PaTable *pNextTable;

	V_DataOff = (uchar8)(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI);		/*ȡ������ƫ��*/
	P_DataAddr = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data;
	pNextTable = (Str_DI0_DataType_PaTable *)(p_TableAddr->P_DataType);
	if( V_DataOff == 0 )
	{
		if(P_DataAddr[V_Off] == C_array)
		{
			V_Off++;
		}
		if(P_DataAddr[V_Off] != p_TableAddr->DataNum)								/*����������4��Ӧ�����*/
		{
			return C_OtherErr_DAR;
		}
		V_Off++;																	/*��������ֽڵ���*/
		for( i = 0; i < p_TableAddr->DataNum; i++ )
		{
			if(pNextTable[i].DataType != P_DataAddr[V_Off])
			{
				return C_TypeErr_DAR;
			}
			j = pNextTable[i].DataLen_645;
			SF_DataExchangeTo645_BasicData(&P_DataAddr[V_Off], &P_DataAddr[V_Off645], ((pNextTable[i].DataLen_698) & 0x7F), &j);
			V_Off645 += pNextTable[i].DataLen_645;
			V_Off = V_Off + ( (pNextTable[i].DataLen_698) & 0x7F ) + 1;
		}
	}
	else
	{
		if(pNextTable[V_DataOff - 1].DataType != P_DataAddr[V_Off])
		{
			return C_TypeErr_DAR;
		}
		j = pNextTable[V_DataOff-1].DataLen_645;
		SF_DataExchangeTo645_BasicData(&P_DataAddr[V_Off], &P_DataAddr[V_Off645], ((pNextTable[V_DataOff - 1].DataLen_698) & 0x7F), &j);
		V_Off645 += pNextTable[V_DataOff - 1].DataLen_645;
		V_Off = V_Off + ( (pNextTable[V_DataOff - 1].DataLen_698) & 0x7F ) + 1;
	}
	*P_uc645Len = (uchar8)V_Off645;
	return C_OK;
}
/*******************************************************************************
����ԭ�ͣ�uchar8	SF_DataExchangeTo645_LCD(Str_Comm_698_RW *pV_698RWPara,Str_Num_DataType_PaTable	*p_TableAddr,ushort16 *P_uc645Len)
������������ʾ������������ת��
����������������ݽṹ��
���������ת��������ݣ���Ž����ṹ��
���ز��������ݳ���
����λ�ã�
��    ע��
*******************************************************************************/
uchar8	SF_DataExchangeTo645_LCD(Str_Comm_698_RW *pV_698RWPara, Str_Num_DataType_PaTable	*p_TableAddr, ushort16 *P_uc645Len)
{
	ushort16	V_Off = 0, V_Off645 = 0;
	uchar8		i, j;
	uchar8		*P_DataAddr, V_DataOff;
	Str_DI0_DataType_PaTable *pNextTable;

	V_DataOff = (uchar8)(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI);			/*ȡ������ƫ��*/
	P_DataAddr = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data;
	pNextTable = (Str_DI0_DataType_PaTable *)(p_TableAddr->P_DataType);
	if( V_DataOff == 0 )
	{
		if(P_DataAddr[V_Off] == C_structure)
		{
			V_Off++;
		}
		V_Off++;	/*�ṹ������ֽڵ���*/

		for( i = 0; i < p_TableAddr->DataNum; i++ )
		{
			if( pNextTable[i].DataType != P_DataAddr[V_Off] )
			{
				return C_TypeErr_DAR;
			}
			j = pNextTable[i].DataLen_645;

			if( ( ( pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI & 0xFFFFFF00 ) == COther_Money )
			 || ( ( pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI & 0xFFFFFF00 ) == CAlam_Money ) )
			{
				if( PF_Buffer4ToUlong32_698(&P_DataAddr[V_Off + 1]) > C_MoneyLimit )
				{
					return C_OtherErr_DAR;
				}
			}

			SF_DataExchangeTo645_BasicData(&P_DataAddr[V_Off], &P_DataAddr[V_Off645], ( (pNextTable[i].DataLen_698) & 0x7F ), &j );
			V_Off645 += pNextTable[i].DataLen_645;
			V_Off = V_Off + ((pNextTable[i].DataLen_698) & 0x7F) + 1;
		}
	}
	else
	{
		if( pNextTable[V_DataOff - 1].DataType != P_DataAddr[V_Off] )
		{
			return C_TypeErr_DAR;
		}
		j = pNextTable[V_DataOff - 1].DataLen_645;

		if( ( ( pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI & 0xFFFFFF00 ) == COther_Money )
		 || ( ( pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI & 0xFFFFFF00 ) == CAlam_Money ) )
		{
			if( PF_Buffer4ToUlong32_698(&P_DataAddr[V_Off + 1]) > C_MoneyLimit )
			{
				return C_OtherErr_DAR;
			}
		}

		SF_DataExchangeTo645_BasicData(&P_DataAddr[V_Off], &P_DataAddr[V_Off645], ((pNextTable[V_DataOff - 1].DataLen_698) & 0x7F), &j);
		V_Off645 += pNextTable[V_DataOff - 1].DataLen_645;
		V_Off = V_Off + ((pNextTable[V_DataOff - 1].DataLen_698) & 0x7F) + 1;
	}
	*P_uc645Len = (uchar8)V_Off645;
	return C_OK;
}
/*******************************************************************************
����ԭ�ͣ�uchar8	SF_DataExchangeTo645_Zone(Str_Comm_698_RW *pV_698RWPara,Str_Type645DI_Class *pV_645,Str_Num_DataType_PaTable	*p_TableAddr,ushort16 *P_uc645Len)
����������ʱ���������������ת��
����������������ݽṹ��
���������ת��������ݣ���Ž����ṹ��
���ز��������ݳ���
����λ�ã�
��    ע��
*******************************************************************************/
uchar8	SF_DataExchangeTo645_Zone(Str_Comm_698_RW *pV_698RWPara, Str_Type645DI_Class *pV_645, Str_Num_DataType_PaTable	*p_TableAddr, ushort16 *P_uc645Len)
{
	ushort16	V_Off = 0, V_Off645 = 0, V_usDataEncode, V_ucLen = CLSec_TZone_Data, V_DataOff;
	uchar8		V_ucDataNum, i, k, V_DataTemp[3];
	uchar8		*P_DataAddr;
	uchar8	V_ucDataBuff[CLSec_TZone_Data] = {0};
	ulong32 V_OAD;

	P_DataAddr = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data;
	if(P_DataAddr[V_Off] == C_array)
	{
		V_Off++;
	    V_ucDataNum = P_DataAddr[V_Off];						/*ȡ�������*/
		V_Off++;
	}
    else if(P_DataAddr[V_Off] == C_structure)
    {
        V_ucDataNum = 1;
    }
    else
    {
    	return C_TypeErr_DAR;
    }
	if(V_ucDataNum > 14)
	{
		return C_SeasonNum_OV_DAR;
	}
	for( k = 0; k < V_ucDataNum; k++ )
	{
		V_Off += 2;												/*�ṹ��ͽṹ�����2���ֽ�ƫ��*/
		for( i = p_TableAddr->DataNum; i > 0; i-- )
		{
			if( P_DataAddr[V_Off] != C_unsigned )
			{
					return C_TypeErr_DAR;
			}
			V_Off++;
			V_DataTemp[3 - i] = P_DataAddr[V_Off];
			V_Off +=1;											/*unsignedһ���ֽ� ����һ���ֽ�*/

		}
		PF_CopyDataBytes(V_DataTemp, &P_DataAddr[V_Off645], p_TableAddr->DataNum);
        PF_CopyDataBytes(V_DataTemp, &pV_645->TZone_Data[V_Off645], p_TableAddr->DataNum);
		V_Off645 += p_TableAddr->DataNum;
	}
	*P_uc645Len = (uchar8)V_Off645;

	V_DataOff = (uchar8)(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI);
	if(V_DataOff !=0)
	{
		V_OAD = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI&0xFFFFFF00;
		if( InF_Read_Data(V_OAD, V_ucDataBuff, &V_ucLen, &V_usDataEncode) == C_OK )		/*��ȡʱ�������ݣ���������һ��д���ݲ� */
		{
			PF_CopyDataBytes(&P_DataAddr[0], &V_ucDataBuff[(V_DataOff - 1) * 3], 3);
            PF_CopyDataBytes(V_ucDataBuff, pV_645->TZone_Data, CLSec_TZone_Data);
		}
		else
		{
			for( k = 1; k < 14; k++ )
			{
				PF_CopyDataBytes(&P_DataAddr[0], &P_DataAddr[k * 3], 3);
			}
		}
		*P_uc645Len=CLSec_TZone_Data;
	}
	return C_OK;
}
/*******************************************************************************
����ԭ�ͣ�uchar8	SF_DataExchangeTo645_SettleDay(Str_Comm_698_RW *pV_698RWPara,Str_Num_DataType_PaTable	*p_TableAddr,ushort16 *P_uc645Len)
���������������ղ�����������ת��
����������������ݽṹ��
���������ת��������ݣ���Ž����ṹ��
���ز��������ݳ���
����λ�ã�
��    ע��
*******************************************************************************/
uchar8	SF_DataExchangeTo645_SettleDay(Str_Comm_698_RW *pV_698RWPara, Str_Num_DataType_PaTable	*p_TableAddr, ushort16 *P_uc645Len)
{
	ushort16	V_Off = 0, V_Off645 = 0;
	uchar8		V_ucDataNum, i, k, V_DataTemp[3];
	uchar8		*P_DataAddr;

	P_DataAddr = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data;
	if(P_DataAddr[V_Off] == C_array)
	{
		V_Off++;
		V_ucDataNum = P_DataAddr[V_Off];				/*ȡ�������*/
		if(V_ucDataNum > 3)
		{
			return C_TypeErr_DAR;
		}
		V_Off++;
		if(P_DataAddr[V_Off] == C_structure)
		{
			V_Off++;
		}
		else
		{
			return C_TypeErr_DAR;
		}
	}
	else if(P_DataAddr[V_Off] == C_structure)
	{
		V_Off++;
		V_ucDataNum = 1;
	}
	else
	{
		return C_TypeErr_DAR;
	}
	for( k = 0; k < V_ucDataNum; k++ )
	{
		for( i = p_TableAddr->DataNum; i > 0; i-- )
		{
			V_Off +=1;									/*unsignedһ���ֽ� ����һ���ֽ�*/
			if(P_DataAddr[V_Off] != C_unsigned)
			{
				return C_TypeErr_DAR;
			}
			V_Off++;
			if(P_DataAddr[V_Off] == 0xFF)
			{
				V_DataTemp[i - 1] = P_DataAddr[V_Off];
			}
			else
			{
				V_DataTemp[2 - i] = P_DataAddr[V_Off];
			}
		}
		PF_CopyDataBytes(V_DataTemp, &P_DataAddr[V_Off645], p_TableAddr->DataNum);
		V_Off645 += p_TableAddr->DataNum;
		if( ( V_ucDataNum != 1 ) && ( k != ( V_ucDataNum - 1 ) ) )
		{
			V_Off++;
			if(P_DataAddr[V_Off] == C_structure)
			{
				V_Off++;
			}
			else
			{
				return C_TypeErr_DAR;
			}
		}
	}
	*P_uc645Len = (uchar8)V_Off645;
	return C_OK;
}
/*******************************************************************************
����ԭ�ͣ�uchar8	SF_DataExchangeTo645_EventPa(Str_Comm_698_RW *pV_698RWPara,Str_EventPara_Type *p_TableAddr,ushort16 *P_uc645Len,uchar8 V_Num)
�����������¼���¼������������ת��
����������������ݽṹ��
���������ת��������ݣ���Ž����ṹ��
���ز��������ݳ���
����λ�ã�
��    ע��
*******************************************************************************/
uchar8	SF_DataExchangeTo645_EventPa(Str_Comm_698_RW *pV_698RWPara, Str_EventPara_Type *p_TableAddr, ushort16 *P_uc645Len, uchar8 V_Num)
{
	ushort16	V_Off = 0, V_Off645 = 0;
	uchar8		V_ucDataNum, k,V_DataOff, m, V_uc698Len;
	uchar8		*P_DataAddr;

	V_DataOff = (uchar8)(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI);		/*ȡ������ƫ��*/
	P_DataAddr = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data;
	if( V_DataOff == 0 )
	{
		if( P_DataAddr[V_Off] != C_structure )
		{
			return C_TypeErr_DAR;
		}
	}
	if( P_DataAddr[V_Off] == C_structure )
	{
		V_Off++;
		V_ucDataNum = P_DataAddr[V_Off];											/*ȡ�ṹ����Ԫ�ظ���*/
		V_Off++;
	}
	else
	{
		V_ucDataNum = 1;
	}
	if(V_ucDataNum == 0)
	{
		return C_TypeErr_DAR;
	}

	for(k = 0; k < (V_ucDataNum); k++ )												/*���ò������һ������ʱʱ�䣬��ת��Ϊbcd*/
	{
		if( V_DataOff == 0 )
		{
			m = k;
		}
		else
		{
			m = V_DataOff - 1;
		}
		if( P_DataAddr[V_Off] != p_TableAddr[m].DataTpye698 )
		{
			return C_TypeErr_DAR;
		}

		V_uc698Len = SF_GetFixedLen(&p_TableAddr[m].DataTpye698);
		SF_DataExchangeTo645_BasicData(&P_DataAddr[V_Off], &P_DataAddr[V_Off645], V_uc698Len, &V_uc698Len );
		V_Off = V_Off + V_uc698Len + 1;

		V_Off645 += p_TableAddr[m].Len645;
	}

	*P_uc645Len = (uchar8)V_Off645;
	return C_OK;
}
/*******************************************************************************
����ԭ�ͣ�uchar8	SF_DataExchangeTo645_ZoneTime(Str_Comm_698_RW *pV_698RWPara,Str_Num_DataType_PaTable	*p_TableAddr,ushort16 *P_uc645Len)
����������ʱ�α������������ת��
����������������ݽṹ��
���������ת��������ݣ���Ž����ṹ��
���ز��������ݳ���
����λ�ã�
��    ע��
*******************************************************************************/
uchar8	SF_DataExchangeTo645_ZoneTime(Str_Comm_698_RW *pV_698RWPara, Str_Num_DataType_PaTable	*p_TableAddr, ushort16 *P_uc645Len)
{
	ushort16	V_Off = 0, V_Off645 = 0;
	uchar8		i, j, V_DataTemp[3];
	uchar8		*P_DataAddr;

	P_DataAddr = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data;

	if( ( pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI & 0x000000FF ) != 0x00000000 )
	{
		if(P_DataAddr[V_Off] == C_array)
		{
			V_Off++;
		}
		j = P_DataAddr[V_Off];									/*ȡ�������*/

		if( j > 14 )
		{
			return C_TypeErr_DAR;
		}
		for( ; j > 0; j-- )
		{
			V_Off += 1;
			if( P_DataAddr[V_Off] != C_structure )
			{
					return C_TypeErr_DAR;
			}
			V_Off += 1;
			i = P_DataAddr[V_Off];
			if( i != 3 )
			{
				return C_TypeErr_DAR;
			}
			for( ; i > 0; i-- )
			{
				V_Off +=1;										/*unsignedһ���ֽ� ����һ���ֽ�*/
				if(P_DataAddr[V_Off] !=C_unsigned)
				{
					return C_TypeErr_DAR;
				}
				V_Off++;
				V_DataTemp[3 - i] = P_DataAddr[V_Off];
			}
			PF_CopyDataBytes(V_DataTemp, &P_DataAddr[V_Off645], p_TableAddr->DataNum -  2);
			V_Off645 += (p_TableAddr->DataNum - 2);
		}

	}
	else
	{
		return C_RWForbid_DAR;
	}

	*P_uc645Len = (uchar8)V_Off645;
	return C_OK;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_SetSafeModeParaNat3PerOI(Str_Comm_698_RW *pV_698RWPara,uchar8 V_ucOINum)
������������ȫģʽ������������ת��
����������������ݽṹ��
���������ת��������ݣ���Ž����ṹ��
���ز��������ݳ���
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_SetSafeModeParaNat3PerOI(Str_Comm_698_RW *pV_698RWPara, uchar8 V_ucOINum)
{
	ushort16	i, V_usOI, V_ulSecurity;
	uchar8		V_Data[1024] = {0}, V_ReturnData, V_usNumADD;
	ushort16	V_usOff = 0;
	uchar8		*P_DataAddr;

	if( ( pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI & 0x000000FF ) != 0x00000000 )
	{
		return C_RWForbid_DAR;					/* �ܾ���д */
	}
	P_DataAddr = pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data;

	if( P_DataAddr[V_usOff] == 0x01 )
	{
		V_usOff ++;
		V_usNumADD = P_DataAddr[V_usOff];
		V_usOff++;
	}
	else
	{
		return C_TypeErr_DAR;					/* ���Ͳ�ƥ�� */
	}
	for( i = 0; i < V_usNumADD; i++ )
	{
		if( P_DataAddr[V_usOff] != C_structure )
		{
			return C_TypeErr_DAR;				/* ���Ͳ�ƥ�� */
		}
		V_usOff +=2;
		if( P_DataAddr[V_usOff] != C_OI )
		{
			return C_TypeErr_DAR;				/* ���Ͳ�ƥ�� */
		}
		V_usOff ++;
		V_usOI = P_DataAddr[V_usOff];
		V_usOI <<= 8;
		V_usOff ++;
		V_usOI |= P_DataAddr[V_usOff];

		V_usOff ++;
		if(P_DataAddr[V_usOff]!=C_long_unsigned)
		{
			return	C_TypeErr_DAR;				/* ���Ͳ�ƥ�� */
		}
		V_usOff ++;
		V_ulSecurity = P_DataAddr[V_usOff];
		V_ulSecurity <<= 8;
		V_usOff ++;
		V_ulSecurity |= P_DataAddr[V_usOff];
		V_usOff ++;

		PF_Ushort16ToBuffer2(&V_Data[i * 4], &V_usOI);
		PF_Ushort16ToBuffer2(&V_Data[i * 4 + 2], &V_ulSecurity);

	}

	uchar8 V_ucBuff[4], V_Opcode[4] = {0};

	PF_Ulong32ToBuffer4(V_ucBuff, &pV_698RWPara->Wt_OI[V_ucOINum].WtOI, 4);
	INF_Append_ProgRecordDI(V_Opcode, V_ucBuff, &SV_Comm_Parse.ProgRecord, pV_698RWPara->ServiceFlag_First);
	V_ReturnData = InF_Write_Data(C_Msg_Communication, CSafeModeParaNat3_Num, &V_usNumADD, CLSafeModeParaNat3_Num, C_W_SafeFlag);
	if(V_ReturnData == C_OK)
	{
		V_ReturnData = InF_Write_Data(C_Msg_Communication, pV_698RWPara->Wt_OI[V_ucOINum].WtOI, V_Data, CLSafeModeParaNat3, C_W_SafeFlag);
	}
	return V_ReturnData;
}

/*******************************************************************************
����ԭ�ͣ�ushort16	SF_DataExchangeTo645_BasicData(uchar8 *pV_698data,uchar8 *pV_645data,uchar8 V_ucLen698,uchar8 *V_ucLen645)
����������698��ʽת��645
��������� V_ucLen645Ϊ645���ݳ��ȣ�  pV_698dataִ��698ת�����׵�ַ
			�õ�ַ��Ż����������ͣ�pV_645dataִ��645�����׵�ַ
�����������
���ز��������ص�ǰ�������͵��ֽ���
����λ�ã�
��    ע��
*******************************************************************************/
ushort16	SF_DataExchangeTo645_BasicData(uchar8 *pV_698data,uchar8 *pV_645data,uchar8 V_ucLen698,uchar8 *V_ucLen645)
{
	ushort16	V_Off645 = 0;
	uchar8		i, j;
	uchar8 		V_ucDataType = 0, V_uc698Offset = 1;

	V_Off645 = V_ucLen698;
	V_ucDataType = pV_698data[0];

	switch(V_ucDataType)				/*��������*/
	{
		case C_octet_string:
		case C_visible_string:
		{
			V_uc698Offset = 2;
			V_Off645 = pV_698data[1];	/*ƫ��һ�������ݳ���*/
		}break;

		case C_bit_string:				/*��A-XDR�������������Ӧ���ǴӸ�λ��ʼ�����λ��0����Ŀǰ��λ���Ǵӵ�λ��ʼ�����λ��0.�Ȱ�����λ�������ʽ����*/
		{
			V_uc698Offset = 2;
			V_Off645 = V_ucLen698 - 2;
			for(i = 0; i < V_Off645; i++ )
			{
				pV_645data[i] = 0;
				for(j = 0; j < 8; j++ )
				{
					pV_645data[i] <<= 1;
					if( ( ( pV_698data[2 + i] >> j ) & 0x01 ) == 0x01 )
					{
						pV_645data[i] |= 1;
					}
				}
			}
		}break;

		default:
			break;
	}
	if( ( V_ucLen698 == 0 ) || ( V_ucDataType == C_bit_string) )
	{
		;																			/*���������0������bit-string���Ͳ���*/
	}
	else
	{
		PF_OneDataReversed (pV_698data + V_uc698Offset, pV_645data, V_Off645);		/*���ݵߵ�*/
	}

	return V_Off645;
}
/******************************************************************************************
����ԭ�ͣ�ushort16 SF_DataExchangeTo645_ActionData(uchar8 *pV_698data,uchar8 *pV_645data,uchar8 V_ucOIB,uchar8 V_ucActuralLen)
����������698��ʽת��645
��������� pV_698dataִ��698ת�����׵�ַ��
          pV_645dataִ��645�����׵�ַ
          V_ucLen645Ϊ645���ݳ��ȣ�
          V_ucOIBΪOIB
		 V_ucActuralLen���ݳ���698
�����������
���ز��������ݳ��ȣC
����λ�ã�
��    ע��
******************************************************************************************/
ushort16 SF_DataExchangeTo645_ActionData(uchar8 *pV_698data, uchar8 *pV_645data, uchar8 V_ucOIB, uchar8 V_ucActuralLen)
{
    ulong32 V_ulData;
	ushort16 V_Off645 = 0;
	uchar8 i, j, V_Temp[10] = {0}, V_Len = 4;
	uchar8 V_DataTemp[80], V_Num;

	PF_CopyDataBytes(pV_698data, V_DataTemp, 64);

	switch(V_ucOIB)
	{
		case 0x00:
        {
			PF_CopyDataBytes(pV_698data, V_Temp, 7);
			V_Temp[0] = *(pV_698data + 1);
			V_Temp[1] = *(pV_698data);
			PF_Buffer4ToUlong32(V_Temp, &V_ulData, 2);					/*�������ֽ�*/
			V_Len = 2;
			PF_HextoBCDBytes(&V_ulData, (pV_645data + 5), &V_Len);

			for( i = 2; i < 7; i++)
			{
				PF_Buffer4ToUlong32( (V_Temp + i), &V_ulData, 1);	    /*��������1���ֽ�*/
				V_Len = 1;
				PF_HextoBCDBytes(&V_ulData, (pV_645data + 7 - 1 - i), &V_Len);
			}

			V_Off645 = 7;

		}break;

		case 0x08:
		case 0x09:
		case 0x0A:
		case 0x0B:														/*645��ʱ���ʽΪ������ʱ����*/
        {
			V_Off645 = 7;

			for( i = 1 ; i < 6; i++)
			{
				V_DataTemp[i] = *(pV_698data + 6 - i);
			}

			if ( ( V_DataTemp[1] == 0 )
              && ( V_DataTemp[2] == 0 )
              && ( V_DataTemp[3] == 0 )
              && ( V_DataTemp[4] == 0 )
              && ( V_DataTemp[5] == 0 ) )
			{
				V_DataTemp[6] = 0;
				V_DataTemp[0] = 0xFF;
			}
			else if ( ( V_DataTemp[1] == 0xFF )
                    && ( V_DataTemp[2] == 0xFF )
                    && ( V_DataTemp[3] == 0xFF )
                    && ( V_DataTemp[4] == 0xFF )
                    && ( V_DataTemp[5] == 0xFF ) )
			{
				V_DataTemp[6] = 0xFF;
				V_DataTemp[0] = 0xFF;
			}
			else if ( ( V_DataTemp[1] == 0x99 )
                    && ( V_DataTemp[2] == 0x99 )
                    && ( V_DataTemp[3] == 0x99 )
                    && ( V_DataTemp[4] == 0x99 )
                    && ( V_DataTemp[5] ==0x99 ) )
			{
				V_DataTemp[6] = 0x99;
				V_DataTemp[0] = 0xFF;
			}
			else
			{
				V_DataTemp[6] = 0x20;
				V_DataTemp[0] = 0xFF;
			}
			PF_CopyDataBytes_698(V_DataTemp, pV_645data, V_Off645);

		}break;

		case 0x02:
		{
            V_Off645 = 8;

			for( i = 0; i < V_Off645; i++)
			{
				V_DataTemp[i] = *(pV_698data + V_Off645 - i);
			}

			PF_CopyDataBytes_698(V_DataTemp, pV_645data, V_Off645);
		}break;

		case 0x03:
        {
			V_Off645 = 6;

			for( i = 0; i < V_Off645; i++)
			{
				V_DataTemp[i] = *(pV_698data + V_Off645 - i);
			}

			PF_CopyDataBytes_698(V_DataTemp, pV_645data, V_Off645);

		}break;

		case 0x1C:
		case 0x1D:
		{
            V_Off645 = 4;
			V_DataTemp[3] = 0x00;										/*��ѹ���������������û�е�λ���㣬ԭ��Ϊ2λС��*/

			for( i = 0; i < (V_Off645 - 1); i++)
			{
				V_DataTemp[i] = *(pV_698data + (V_Off645 - 1) - i);
			}

			PF_CopyDataBytes_698(V_DataTemp, pV_645data, V_Off645);
		}break;

		case 0x18:
		case 0x19:
		{
			V_Off645 = CLBackUp_Rate1_Price;
			V_Num = V_ucActuralLen / CLBackUp_Rate1_Price;
			if(V_Num >= C_MaxRatesNum)
			{
				V_Num = C_MaxRatesNum;									/*ֻ�ߵ�12�����ʵ��*/
			}

			for( j = 0; j < V_Num; j++ )
			{
				for( i = 0; i < V_Off645; i++ )
				{
					V_DataTemp[i] = *(pV_698data + V_Off645 + j * CLBackUp_Rate1_Price - i);
				}

				PF_CopyDataBytes_698(V_DataTemp, (pV_645data + j * CLBackUp_Rate1_Price), V_Off645);
			}

			V_Off645 = CLBackUp_RateFF_Price;

			if(V_ucActuralLen < CLBackUp_RateFF_Price)					/*����4�����ʵ�ۣ����ʵ�۲�0*/
			{
				for( i = V_ucActuralLen; i < CLBackUp_RateFF_Price; i++)
				{
					pV_645data[i] = 0;
				}
			}

		}break;

		case 0x1A:
		case 0x1B:
		{
            V_Off645 = 4;

			for( j = 0; j < 13; j++)
			{
				for( i = 0; i < 4; i++)
				{
					V_DataTemp[i] = *(pV_698data + 4 + j * 4 - i);
				}
				PF_CopyDataBytes_698(V_DataTemp, pV_645data + j * 4, 4);
			}
			PF_CopyDataBytes_698(V_DataTemp, pV_645data + j * 4 + 6 * 4, 4);

			for( j = 0; j < 4; j++)
			{
				for(i = 0; i < 3; i++)
				{
					V_DataTemp[i] = *(pV_698data + 3 + j * 3 + 4 * 13 - i);
				}
				PF_CopyDataBytes_698(V_DataTemp, (pV_645data + j * 3 + 4 * 13), 3);
			}

			V_Off645 = 64;

		}break;

		case 0x1E:
		{
            V_Off645 = 4;

			for( j = 0; j < 2; j++)
			{
				for( i = 0; i < V_Off645; i++)
				{
					V_DataTemp[i] = *(pV_698data + V_Off645 + j * 4 - i);
				}

				PF_CopyDataBytes_698(V_DataTemp, (pV_645data + j * 4), V_Off645);
			}

		}break;

		default:
		break;
	}

	return V_Off645;
}
/*******************************************************************************
����ԭ�ͣ�void OneByteReverse(uchar8 *pV_Sourcedata)
����������һ���ֽڱ���bit0��bit7�ߵ�
���������
������������ص�ǰ�������͵��ֽ���
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
void OneByteReverse(uchar8 *pV_Sourcedata)
{
	uchar8 V_ucTemp = 0,i;

	for( i = 0; i < 8; i++)
	{
		V_ucTemp <<= 1;
		if( (*pV_Sourcedata) & ( 0x01 << i ) )
		{
			V_ucTemp |= 1;
		}
	}
	*pV_Sourcedata = V_ucTemp;
}
/*********************************************************************************
����ԭ�ͣ�ushort16	SF_DataExchangeTo698_BasicData(uchar8 *pV_698data, uchar8 *pV_645data, uchar8 V_ucLen698, uchar8 V_ucLen645)
������������ʽת��698
���������*pV_698data 698���ݻ��棬*pV_645data 645���ݻ��棻 V_ucLen698 698���ݳ��ȣ�V_ucLen645 645���ݳ��ȣ�
���������*pV_698data 698���ݻ���
���ز�����V_Off698 698 ���ݳ���
����˵����
���û��ƣ�
��    ע��
**********************************************************************************/
#if 0
ushort16 SF_DataExchangeTo698_BasicData(uchar8 *pV_698data, uchar8 *pV_645data, uchar8 V_ucLen698, uchar8 V_ucLen645)
{
	ushort16	V_Off698 = 0;
	uchar8		V_ucI, V_698ActualLen = 0, V_uc698Offset = 1;		/*������698����ĵ�ַƫ��*/

	V_Off698 = V_ucLen645;

	switch(pV_698data[0])
	{
		case C_octet_string:
		case C_visible_string:
	    {
			V_Off698 = V_ucLen645;
    		V_uc698Offset = 2;
        }break;

		case C_bit_string:          									/*bit_stringҪ���ȷ�bit0*/
	    {
			V_698ActualLen = V_ucLen645;

    		for(V_ucI = 0; V_ucI < V_ucLen645; V_ucI++)
    		{
    			OneByteReverse(pV_645data + V_ucI);
    		}
    		if(V_ucLen645 > 31)
    		{
				V_uc698Offset = 4;
    		}
    		else if(V_ucLen645 > 15)
    		{
				V_uc698Offset = 3;
    		}
    		else
    		{
				V_uc698Offset = 2;
    		}
        }break;

		default:
		break;
	}

	if(V_Off698 != 0)
	{
		PF_OneDataReversed (pV_645data, pV_698data + V_uc698Offset, V_Off698);
	}

	return V_Off698;
}
#endif
#if 1
ushort16 SF_DataExchangeTo698_BasicData(uchar8 *pV_698data, uchar8 *pV_645data, uchar8 V_ucLen698, uchar8 V_ucLen645)
{
	ushort16	V_Off698 = V_ucLen645;
	uchar8		V_ucI, V_698ActualLen = 0, V_uc698Offset = 1;								/*������698����ĵ�ַƫ��*/

	if(V_ucLen645 == 0)
	{
		V_Off698 = 0;
	}

	switch(pV_698data[0])
	{
		case C_date_time_s:																	/*28**645��ʱ���ʽΪ������ʱ����*/
	    {
			V_698ActualLen = 7;
	    }break;

		case C_date_time:																	/*25*/
		{
			V_698ActualLen = 10;
		}break;

		case C_date:				           												/*26*/
		{
			V_698ActualLen = 5;
	    }break;

		case C_time:				    													/*27*/
	    {
			V_698ActualLen = 3;
        }break;

		case C_integer:
	    {
			V_698ActualLen = 1;
	    }break;

		case C_long:																		/*16*/
		case C_long_unsigned:
		{
			V_698ActualLen = 2;
		}break;

		case C_long64:																		/*20*/
		case C_float64:
		case C_long64_unsigned:
	    {
			V_698ActualLen = 8;
        }break;

		case C_float32:
		case C_double_long:
		case C_double_long_unsigned:
	    {
			V_698ActualLen = 4;
        }break;

		case C_enum:
		case C_bool:
		case C_unsigned:
	    {
			V_698ActualLen = 1;
	    }break;

		case C_OAD:
		case C_OMD:
	    {
    		V_698ActualLen = 4;
        }break;

		case C_octet_string:
		case C_visible_string:
	    {
			V_698ActualLen = V_ucLen698;
    		V_uc698Offset = 2;
        }break;

		case C_bit_string:          									/*bit_stringҪ���ȷ�bit0*/
	    {
			V_698ActualLen = V_ucLen645;

    		for(V_ucI = 0; V_ucI < V_ucLen645; V_ucI++)
    		{
    			OneByteReverse(pV_645data + V_ucI);
    		}
    		if(V_ucLen645 > 31)
    		{
				V_uc698Offset = 4;
    		}
    		else if(V_ucLen645 > 15)
    		{
				V_uc698Offset = 3;
    		}
    		else
    		{
				V_uc698Offset = 2;
    		}
        }break;

		default:
		break;
	}
	memset(pV_698data + V_uc698Offset, 0x00, V_698ActualLen);								/*�������������0x00*/	
	if( ( V_ucLen698 == 0 ) || ( pV_698data[0] == C_bit_string) )
	{
		memcpy(pV_698data + V_uc698Offset + ( V_Off698 - V_ucLen645), pV_645data, V_ucLen645);																												/*���������0������bit-string���Ͳ���*/
	}
	else
	{
		V_Off698 = V_698ActualLen;
		if( ( pV_698data[0] == C_long ) || ( pV_698data[0] == C_long64 )
		 || ( pV_698data[0] == C_float64 ) || ( pV_698data[0] == C_float32 ) || ( pV_698data[0] == C_double_long ) )	/*������λ����Ҫ��0xFF*/
		{
			if( pV_645data[V_ucLen645 - 1] & 0x80 == 0x80 )
			{
				memset(pV_698data + V_uc698Offset, 0xFF, V_698ActualLen);					/*����Ǹ�������0xFF*/
			}
		}
		if(V_ucLen645 > V_Off698 )
		{
			V_ucLen645 = V_Off698;				/*Ŀǰֻ�й�������������ʱ�Ȳ��ܡ���ΪҪ����698���һ���ֽ�*/
		}
		PF_OneDataReversed (pV_645data, pV_698data + V_uc698Offset + ( V_Off698 - V_ucLen645), V_ucLen645);
	}

	return V_Off698;
}
#endif
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_GetRateNum(uchar8 V_ucMaxNum)
������������ȡ����������Ԫ�ظ�������+��������
���������������������ֵ
���������
���ز���������������Ԫ�ظ���
����λ�ã�
��    ע������������+����
         �����ݲ�ɹ����������ݲ� ������+1��
         �����ݲ�ʧ�ܣ�������������4+1=5
*******************************************************************************/
uchar8 SF_GetRateNum(uchar8 V_ucMaxNum)
{
    uchar8  V_ucRateNum = C_RatesNumTol;

    if( ( V_ucMaxNum & C_WithOutSign ) == C_RatesNumTol )
    {
        V_ucRateNum = InF_RateNumChangeToHex();
        V_ucRateNum += 1; 							/*����+��*/
    }
    else
    {
        V_ucRateNum = V_ucMaxNum & C_WithOutSign;
    }
    return V_ucRateNum;
}
/*******************************************************************************
����ԭ�ͣ� SF_Judge_OINature
���������� ���ݶ������Ի�ȡ���Զ�Ӧ��������
��������� OperationMode:���β�������:������C_Read;д:C_Set;����:C_OPERATION
��������� ����OAD/OMD ����Ч��
���ز����� ��
����λ��:
��    ע��
*******************************************************************************/
uchar8 SF_Judge_OINature(Str_Comm_698_RW *pV_698RWPara, Str_Type645DI_Class *P_DIFor645, uchar8 *P_645DINum, uchar8 OperationMode)
{
	uchar8	V_OIA, V_OIB, V_Nature, V_DataOff, V_Day_Time_Num, V_ucChannelNum, V_ucDataoff = 0;
	uchar8	V_return = C_OK, V_Temp, i, j, V_ucNum = 0, V_645Off = 0, V_698Off = 0;
    uchar8  V_ucDataBuffer[CLPulse_Constant] = {0}, V_ucReturn, V_usLen698, *pDataAddr;
    ulong32 V_ulData;
    uchar8  V_Flag,V_NumOAD,V_NumOI,Len=C_NewReportMaxNum,V_LenOI = C_NewReportMaxNum * 2, V_EventOI[C_NewReportMaxNum * 2];
    uchar8  V_RemainReportNO[C_NewReportMaxNum], V_RemainReportNum, V_EventNo[C_NewReportMaxNum];
	Str_DI0_DataType_PaTable *p_TableAddr;
	ushort16 V_usOff, V_ucDataLen, V_usDataEncode, k, V_DoubleAgreementFlagLen = 0;
	uchar8	V_HolidayNum[1];
    ulong32 V_ulDispNumDI,V_ulChannelOAD;
	uchar8	V_DoubleAgreementReturn = C_Error, V_AgreementNum = 1;
	uchar8   V_ucClassNum,V_ucDataTemp[CLI_Free_OADTabLen_T], V_ucDispNum;
	ushort16 V_ucLen, PDataLength = 1;
	uchar8	V_ucData[255];

	if(OperationMode == C_Read)
	{
		V_OIA = (uchar8)(pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD >> 24);        /*ȡOIA*/
		V_OIB = (uchar8)(pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD >> 16);		/*ȡOIB*/
		V_Nature = (uchar8)(pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD >> 8);	    /*ȡ����*/
		V_DataOff = (uchar8)(pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD);		    /*ȡ������ƫ��*/
	}
	else	/*д�Ͳ���*/
	{
		V_OIA = (uchar8)(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI>>24);		        /*ȡOIA*/
		V_OIB = (uchar8)(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI>>16);		        /*ȡOIB*/
		V_Nature = (uchar8)(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI>>8);		    /*ȡ����*/
		V_DataOff = (uchar8)(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI);			    /*ȡ������ƫ��*/
	}

	P_DIFor645->IDNO = C_NULL;
	*P_645DINum = 0;
    if( ( V_Nature == C_Nature1_Name ) && ( pV_698RWPara->ServiceFlag_First == C_SET_Request ) )
    {
        V_return = C_RWForbid_DAR;					/*�ܾ���д*/
        *P_645DINum = 1;
        return V_return;
    }
    if( ( V_Nature == C_Nature1_Name ) && ( pV_698RWPara->ServiceFlag_First == C_GET_Request ) )
    {
        *P_645DINum = 1;
        return V_return;
    }

    if(V_Nature == 0x00)
    {
        return C_RWForbid_DAR;                      /*�ܾ���д*/
    }
	switch(V_OIA)
	{
		case C_ReportList:
		{
			if(pV_698RWPara->ServiceFlag_First != C_GET_Request)
			{
				V_return = C_RWForbid_DAR;	        /*�ܾ���д*/
				break;
			}
            if(V_OIB <= 0x15)
			{
                V_return = C_RWForbid_DAR;	        /*�ܾ���д*/
				break;
            }
            else if(V_OIB != 0x20)
            {
                V_return = C_ObjectUndefine_DAR;	/*����δ����*/
				break;
			}
			P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD;
			V_Temp = V_Nature&0x1F;	                /*ȡ���Ա��*/
			if(V_Temp > 3)                          /*���������ϱ�������Բ�����3*/
			{
				V_return = C_ObjectUndefine_DAR;	/*Ӧ������δ����*/
				break;
			}
			if(V_DataOff !=0)
			{
				pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_OAD ;
				pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;
				P_DIFor645->NextClassNO = C_NULL;
			}
			else
			{
				pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_array;

                if(V_Temp == 2)
                {
                    V_Flag = InF_GETListData(pV_698RWPara->ChannelNo, &V_NumOAD, V_EventNo, Len, V_RemainReportNO, &V_RemainReportNum, C_NoActiveReportFlag);

                    if(V_Flag == C_OK)
                    {
                    	pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = V_NumOAD;
                	}
                    else
                    {
                        V_return = C_ObjectNotExist_DAR;	/*Ӧ������δ����*/
                        break;
                    }
                }
                else if(V_Temp == 3)
                {
                    SF_GetReportOI(V_EventOI, &V_NumOI, V_LenOI);
                    pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = V_NumOI;
                }
				P_DIFor645->NextClassNO = C_NULL;
			}
            break;
		}
		case	C_EnergyOIA:
		{
			if(OperationMode != C_Read)
			{
				V_return = C_RWForbid_DAR;                  /*��ֹ��д*/
				break;
			}
			if(V_DataOff > C_RatesNumTol)
			{
				V_return = C_ObjectNotExist_DAR;            /*Ӧ�����Բ�����*/
				break;
			}
			P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD;
			V_Temp = V_Nature & 0x1F;                       /*ȡ���Ա��*/
			if(V_Temp > C_Nature7_LastNumPulseUnit)         /*����������Բ�����7*/
			{
				V_return = C_ObjectNotExist_DAR;            /*Ӧ�����Բ�����*/
				break;
			}

			P_DIFor645->MAXRecordTimes = 0;
			P_DIFor645->NextClassNO = C_NULL;
			P_DIFor645->NextClassNum = 0;
			for(i = 0; i < GV_Str_OIB_DI2_EnergyTableLen; i++)
			{
				if(V_OIB == GV_Str_OIB_DI2_EnergyTable[i].OIB)
				{
					/**************ȡ�����ʶ��*************/
					if( ( V_Temp == C_Nature2_Energy )
					 || ( V_Temp == C_Nature4_PreEnergy )
					 || ( V_Temp == C_Nature6_LastNumPulse ) )
					{
						if(V_Temp == C_Nature2_Energy)
						{
							if( ( GV_Str_OIB_DI2_EnergyTable[i].MaxNum & 0x80 ) == 0x80 )
							{
								P_DIFor645->DataType[0] = C_double_long;
							}
							else
							{
								P_DIFor645->DataType[0] = C_double_long_unsigned;
							}
							P_DIFor645->DataLen_698[0] = 4;
						}
						else if(V_Temp == C_Nature4_PreEnergy)
						{
							if( ( GV_Str_OIB_DI2_EnergyTable[i].MaxNum & 0x80 ) == 0x80 )
							{
								P_DIFor645->DataType[0] = C_long64;
							}
							else
							{
								P_DIFor645->DataType[0] = C_long64_unsigned;
							}
							P_DIFor645->DataLen_698[0] = 8;
						}
                        else    									/*����6������β��*/
                        {
                            /*�����жϴ���10000����������β������*/
                            V_ucDataLen = CLPulse_Constant;
                            V_ucReturn = InF_Read_Data(CPulse_Constant, V_ucDataBuffer, &V_ucDataLen, &V_usDataEncode);
                            if(V_ucReturn != C_OK)
                            {
                                memset(V_ucDataBuffer, 0x00, CLPulse_Constant);
                            }
                            PF_Buffer4ToUlong32(V_ucDataBuffer, &V_ulData, V_ucDataLen);
                            if(V_ulData <= C_CPulse_Constant10000)
                            {
                                V_return = C_ObjectUndefine_DAR;	/*����δ���壬�淶����*/
                                break;
                            }/*else����ִ��*/

							if( ( GV_Str_OIB_DI2_EnergyTable[i].MaxNum & 0x80 ) == 0x80 )
							{
								P_DIFor645->DataType[0] = C_integer;
							}
							else
							{
								P_DIFor645->DataType[0] = C_unsigned;
							}
							P_DIFor645->DataLen_698[0] = 1;
                        }
						if(V_DataOff != 0)
						{
							pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = P_DIFor645->DataType[0] ;
							pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;
							P_DIFor645->NextClassNO = C_NULL;
						}
						else
						{
							pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_array;


							pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = SF_GetRateNum(GV_Str_OIB_DI2_EnergyTable[i].MaxNum);
							P_DIFor645->NextClassNO = C_NULL;
						}
					}
					else
					{
						P_DIFor645->DataType[0] = C_Scaler_Unit;
						pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_Scaler_Unit;
						pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;
					}
					P_DIFor645->Unit_Scale[0] = GV_Str_OIB_DI2_EnergyTable[i].Unit_Energy;
					P_DIFor645->Unit_Scale[0] <<= 8;
					if(V_Temp < C_Nature4_PreEnergy)
					{
						P_DIFor645->Unit_Scale[0] |= 0xFE;			/*����2����-2*/
					}
                    else if(V_Temp == C_Nature7_LastNumPulseUnit)
                    {
						P_DIFor645->Unit_Scale[0] |= 0xFA;			/*����6����-6*/
                    }
					else    /*����4*/
					{
						P_DIFor645->Unit_Scale[0] |= 0xFC;
					}
					*P_645DINum = SF_GetRateNum(GV_Str_OIB_DI2_EnergyTable[i].MaxNum);
					if( ( V_Temp == C_Nature3_EnergyUnit ) ||( V_Temp == C_Nature5_PreEnergyUnit )
					  ||( V_Temp == C_Nature7_LastNumPulseUnit ) || ( V_DataOff != 0 ) )
					{
						if( ( ( V_Temp == C_Nature2_Energy ) || ( V_Temp == C_Nature4_PreEnergy ) || ( V_Temp == C_Nature6_LastNumPulse ) )
						&& ( V_DataOff > *P_645DINum ) )
						{
							V_return = C_ObjectUndefine_DAR;		/*Ӧ�����δ����*/
							break;
						}
						else
						{
							*P_645DINum = 1;
							P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD;
						}

					}
					else
					{
						P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD + 0x00000001;

						for(j = 1; j < (GV_Str_OIB_DI2_EnergyTable[i].MaxNum & 0x7F); j++)
						{
							P_DIFor645->DataType[j] = P_DIFor645->DataType[0];
						}
					}
					break;
				}
			}
			if(i >= GV_Str_OIB_DI2_EnergyTableLen)
			{
				V_return = C_ObjectNotExist_DAR;					/*Ӧ������δ����*/
				break;
			}
			break;
		}
		case	C_DemandOIA:
		{
			if(OperationMode != C_Read)
			{
				V_return = C_RWForbid_DAR;          				/*Ӧ������δ����*/
				break;
			}
			if(V_DataOff > C_RatesNumTol)
			{
				V_return = C_ObjectNotExist_DAR;    				/* ���󲻴��� */
				break;
			}

			P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD;
			V_Temp = V_Nature & 0x1F;               				/*ȡ���Ա��*/
			if(V_Temp > C_Nature3_DemandUnit)       				/*����������Բ�����3*/
			{
				V_return = C_ObjectUndefine_DAR;    				/*Ӧ������δ����*/
				break;
			}
			for(i = 0; i < GV_Str_OIB_DI2_EnergyTableLen; i++)
			{
				if(V_OIB == GV_Str_OIB_DI2_EnergyTable[i].OIB)
				{
					/**************ȡ�����ʶ��*************/
					P_DIFor645->MAXRecordTimes = 0;
					if(V_Temp == C_Nature2_Demand)
					{
						P_DIFor645->DataType[0] = C_structure;
						if(GV_Str_OIB_DI2_EnergyTable[i].MaxNum & 0x80)		/*�з�����*/
						{
							P_DIFor645->NextClassNO = (Str_DI0_DataType_PaTable *)&C_DemandTpyeTable[0];
						}
						else
						{
							P_DIFor645->NextClassNO = (Str_DI0_DataType_PaTable *)&C_DemandTpyeTable[2];
						}
						P_DIFor645->NextClassNum = 2;
						pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_array;
						pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = SF_GetRateNum(GV_Str_OIB_DI2_EnergyTable[i].MaxNum);
					}
					else
					{
						P_DIFor645->DataType[0] = C_Scaler_Unit;
						P_DIFor645->NextClassNO = C_NULL;
						P_DIFor645->NextClassNum = 0;
						pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_Scaler_Unit;
						pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;
					}
					P_DIFor645->Unit_Scale[0] = GV_Str_OIB_DI2_EnergyTable[i].Unit_Demand;
					P_DIFor645->Unit_Scale[0] <<= 8;
					P_DIFor645->Unit_Scale[0] |= 0xFC;
					P_DIFor645->DataLen_645[0] = CLPos_Ac_Tol_De_0;

					*P_645DINum = SF_GetRateNum(GV_Str_OIB_DI2_EnergyTable[i].MaxNum);
					if( ( V_Temp == C_Nature3_DemandUnit ) || ( V_DataOff != 0 ) )
					{
						if( ( V_Temp == C_Nature2_Demand ) && ( V_DataOff > *P_645DINum ) )
						{
							V_return = C_ObjectNotExist_DAR;				/*Ӧ������δ����*/
							break;
						}
						else
						{
							*P_645DINum = 1;
							if(V_DataOff != 0)
							{
								pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = P_DIFor645->DataType[0];
								pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 2;
								P_DIFor645->DataType[0] = C_NULL;
							}
							P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD;
						}

					}
					else
					{
						P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD + 0x00000001;
						for(j = 1; j < (GV_Str_OIB_DI2_EnergyTable[i].MaxNum & 0x7F); j++)
						{
							P_DIFor645->DataType[j] = P_DIFor645->DataType[0];
							P_DIFor645->DataLen_645[j] = P_DIFor645->DataLen_645[0];
						}
					}
					break;
				}
			}
			if(i >= GV_Str_OIB_DI2_EnergyTableLen)
			{
				V_return = C_ObjectNotExist_DAR;        					/*Ӧ������δ����*/
				break;
			}
			break;
		}
		case	C_VariableOIA20:
		{
			if( ( OperationMode == C_Operation )
			 && ( pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI == CRst_Report_State ) )			/*�����ϱ�ģʽ��*/
			{
				break;
			}
			else
			{
				if( ( OperationMode != C_Read )
				 && ( ( pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI != CDrive_Report_Mode)
				   && ( pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI != CDrive_Report_Type) ) )	/*�����ϱ�ģʽ�ֻ������ϱ�����*/
				{
					V_return = C_RWForbid_DAR;          /*Ӧ������δ����*/
					break;
				}
			}

			P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD;
			V_Temp = V_Nature&0x1F;                     /*ȡ���Ա��*/
			if(V_OIB == 0x15)
			{
				if( (V_Temp != 1) && (V_Temp != 2) && (V_Temp != 3) && (V_Temp != 4) && (V_Temp != 5) )
				{
					V_return = C_ObjectUndefine_DAR;	/*Ӧ������δ����*/
					break;
				}
			}
			else
			{
				if( (V_Temp > 3) && (V_OIB != 0x01) )
				{
					V_return = C_ObjectUndefine_DAR;	/*Ӧ������δ����*/
					break;
				}
				if( (V_Temp > 6) && (V_OIB ==0x01) )	/*˲ʱ��������Բ�����6*/
				{
					V_return = C_ObjectUndefine_DAR;	/*Ӧ������δ����*/
					break;
				}
				else
				{
					if(V_Temp == 0x04)                  /*��Ҫ�ж����ߵ����Ƿ���*/
					{
						memset(V_ucDataBuffer, 0x00, CLZero_Current_Sign);
						V_ucDataLen = CLZero_Current_Sign;
						if( InF_Read_Data(CZero_Current_Sign, V_ucDataBuffer, &V_ucDataLen, &V_usDataEncode) == C_OK )
						{
							if(V_ucDataBuffer[0] == C_ZeroCurrentOff)
							{
								V_return = C_ObjectUndefine_DAR;	/*Ӧ������δ����*/
								break;
							}
						}

					}
				}
			}

			for(i = 0; i < GV_Str_OIB_DI2_VariableTable01Len; i++)
			{
				if(V_OIB == GV_Str_OIB_DI2_VariableTable01[i].OIB)
				{
					/**************ȡ�����ʶ��*************/
					P_DIFor645->NextClassNO = C_NULL;
					P_DIFor645->NextClassNum = C_NULL;
					P_DIFor645->MAXRecordTimes = 0;
					if(GV_Str_OIB_DI2_VariableTable01[i].MaxNum != 1)
					{
						pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_array;
						pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = GV_Str_OIB_DI2_VariableTable01[i].MaxNum;
						if(GV_Str_OIB_DI2_VariableTable01[i].MaxNum == 2)
						{
							pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_structure;
						}
						if( ( V_DataOff == 0 ) && ( V_Temp != 4 ) && ( V_Temp !=6 ) )
						{
							P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD + 0x00000001;
						}
					}
					else
					{
                        if( ( ( OperationMode == C_Read ) && ( pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD == CDrive_Report_Type ) )
                         || ( ( OperationMode == C_SetUp ) && ( pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI == CDrive_Report_Type ) ) )
                        {
							pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_enum;	/*20150500��ö�����ͣ�����в���ӵ�������*/
                        }
                        else
                        {
							pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = GV_Str_OIB_DI2_VariableTable01[i].DataType;
                        }
                        pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;
					}

					if( ( ( OperationMode == C_Read ) && ( pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD == CDrive_Report_Type ) )
					|| ( ( OperationMode == C_SetUp ) && ( pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI== CDrive_Report_Type ) ) )
					{	/*20150500��ö�����ͣ�����в���ӵ�������*/
						P_DIFor645->DataType[0] = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType;
					}
					else
					{
						P_DIFor645->DataType[0] = GV_Str_OIB_DI2_VariableTable01[i].DataType;
					}
                    P_DIFor645->Unit_Scale[0] = GV_Str_OIB_DI2_VariableTable01[i].Unit;
					P_DIFor645->Unit_Scale[0] <<= 8;
					P_DIFor645->Unit_Scale[0] |= (GV_Str_OIB_DI2_VariableTable01[i].Conversion & 0x00ff);
                    *P_645DINum = GV_Str_OIB_DI2_VariableTable01[i].MaxNum;
					P_DIFor645->IDFlay = C_TableIDDisvaliable;
					P_DIFor645->IDNO = C_NULL;
					P_DIFor645->NextClassNO = C_NULL;
					P_DIFor645->NextClassNum = 0;
					P_DIFor645->DataLen_645[0] = SF_GetFixedLen(&P_DIFor645->DataType[0]);
					if(GV_Str_OIB_DI2_VariableTable01[i].MaxNum == 7)
					{
						P_DIFor645->DataLen_645[0] = 2;
						P_DIFor645->DataLen_698[0] = 16;
					}
					if( ( V_OIB == 0x40 ) || ( V_OIB == 0x41 ) )
					{

						P_DIFor645->DataLen_645[0] = 2;
						P_DIFor645->DataLen_698[0] = 16;
						pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 16;
					}
					if(V_OIB == 0x42)
					{

						P_DIFor645->DataLen_645[0] = 4;
						P_DIFor645->DataLen_698[0] = 32;
						pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 32;
					}
                    if(V_OIB == 0x15)
					{
                        if( ( ( OperationMode == C_Read ) && ( pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD == CDrive_Report_Type ) )
                         || ( ( OperationMode == C_SetUp ) && ( pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI== CDrive_Report_Type ) ) )
                        {
                        	P_DIFor645->DataLen_645[0] = 1;
                        	P_DIFor645->DataLen_698[0] = 1;
                        	pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;
                        	V_usLen698 = 1;
                       }
                       else
                       {
							P_DIFor645->DataLen_645[0] = 4;
							P_DIFor645->DataLen_698[0] = 32;
							pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 32;
							V_usLen698 = 6;
                       }

						if(OperationMode != C_Read)
						{
							if(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0] != pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType)
							{
								V_return = C_TypeErr_DAR;                   				/*Ӧ�����Ͳ�ƥ��*/
								break;
							}
							pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen
										= SF_DataExchangeTo645_BasicData(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data, &pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0], V_usLen698, &V_usLen698);
						}
					}
					else if( ( V_DataOff != 0 ) || ( V_Temp == 4 ) || ( V_Temp == 6 ) )		/*��ȡһ��������һ��������*/
					{
						pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = P_DIFor645->DataType[0];
						pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;
						if(GV_Str_OIB_DI2_VariableTable01[i].MaxNum == 7)
						{
							pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 16;
						}
						*P_645DINum = 1;
					}
					else
					{
						for(j = 1; j < GV_Str_OIB_DI2_VariableTable01[i].MaxNum; j++)
						{
							P_DIFor645->DataLen_645[j] = P_DIFor645->DataLen_645[0];
							P_DIFor645->DataType[j] = P_DIFor645->DataType[0];
							P_DIFor645->DataLen_698[j] = P_DIFor645->DataLen_698[0];
						}
					}
					break;
				}
			}
			if(i >= GV_Str_OIB_DI2_VariableTable01Len)
			{
				V_return = C_ObjectNotExist_DAR;        /*Ӧ������δ����*/
				break;
			}
			break;
		}
		case	C_VariableOIA21:
		{
			if(OperationMode != C_Read)
			{
				V_return = C_RWForbid_DAR;              /*Ӧ������δ����*/
				break;
			}
			P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD;
			V_Temp = V_Nature & 0x1F;                   /*ȡ���Ա��*/

			if(V_Temp > 3)
			{
				V_return = C_ObjectUndefine_DAR;        /*Ӧ������δ����*/
				break;
			}
			if(V_DataOff > 2)
			{
				V_return = C_ObjectUndefine_DAR;        /*Ӧ������δ����*/
				break;
			}
			for(i = 0; i < GV_Str_OIB_DI2_VariableTable02Len; i++)
			{
				if(V_OIB == GV_Str_OIB_DI2_VariableTable02[i].OIB)
				{
					break;
				}
			}
            if(i >= GV_Str_OIB_DI2_VariableTable02Len)
            {
                if( ( ( V_OIB <= 4 ) ) || ( ( V_OIB >= 0x10 ) && ( V_OIB <= 0x14 ) ) || ( ( V_OIB >= 0x20 ) && ( V_OIB <= 0x24 ) )
                 || ( V_OIB == 0x30 ) || ( V_OIB == 0x40 ) || ( V_OIB == 0x41 ) )
                {
                    V_return = C_ObjectNotExist_DAR;    /*Ӧ�����Բ�����*/
                }
                else
                {
                    V_return = C_ObjectUndefine_DAR;    /*Ӧ������δ����*/
                }
				break;
            }
			else
			{
				if(V_Temp == 2)                         /*��ȡ��ѹ�ϸ�������*/
				{
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_structure;

					if(V_DataOff == 0)
					{
                        pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 2;
						P_DIFor645->V_ucOAD += 1;
						P_DIFor645->DataType[0] = C_NULL;
						P_DIFor645->DataType[1] = C_NULL;
	                    *P_645DINum = 2;
						P_DIFor645->DataLen_645[0] = 16;
						P_DIFor645->DataLen_645[1] = 16;
						P_DIFor645->NextClassNO = (Str_DI0_DataType_PaTable	*)GV_Str_DI0_DataType_VolRateTable;
						P_DIFor645->NextClassNum = 6;
					}
					else
					{
                        pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 5;
						P_DIFor645->DataType[0] = C_NULL;
						P_DIFor645->DataLen_645[0] = 16;
	                    *P_645DINum = 1;
						P_DIFor645->NextClassNO = (Str_DI0_DataType_PaTable	*)&GV_Str_DI0_DataType_VolRateTable[1];
						P_DIFor645->NextClassNum = 5;
					}

					P_DIFor645->IDFlay = C_TableIDDisvaliable;
				}
                P_DIFor645->Unit_Scale[0] = 0xFE;
                P_DIFor645->Unit_Scale[0] <<= 8;
                P_DIFor645->Unit_Scale[0] |= 0;
			}
			break;
		}
		case	C_ParameterOIA40:
		{
			if(OperationMode == C_Operation)
			{
                if(V_Nature == 0x80)
                {
                    if(V_OIB != 6)
                    {
                        V_return = C_ObjectNotExist_DAR;    /*Ӧ������δ����*/
                        break;
                    }
                }
                else if(V_Nature == 0x7F)
                {
                    if( ( V_OIB != 0 ) && ( V_OIB != 6 ) )
                    {
                        V_return = C_ObjectNotExist_DAR;    /*Ӧ������δ����*/
                        break;
                    }
                }
                else
                {
                  if(((V_OIB != 0)
					&&(V_OIB != 0x02)
					&&(V_OIB != 0x03)
					&&(V_OIB != 0x08)
					&&(V_OIB != 0x09)
					&&(V_OIB != 0x0A)
					&&(V_OIB != 0x0B)
					&&(V_OIB < 0x18))||(V_OIB > 0x1E))		/*ʱ�估ESAM�в�������action����*/
    				{
    					V_return = C_RWForbid_DAR;          /*Ӧ������δ����*/
    					break;
    				}
                }
				if( ( V_OIB == 0 ) && ( V_Nature == 127 ) )
				{
					if(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0] != C_date_time_s)
					{
						V_return = C_TypeErr_DAR;           /*Ӧ�����Ͳ�ƥ��*/
						break;
					}
					V_usLen698 = SF_GetFixedLen(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data);
					if(V_usLen698==0)
					{
						V_usLen698 = SF_GetDataTypeLen(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data);
					}
					pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen
						= SF_DataExchangeTo645_BasicData(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data, pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data, V_usLen698, &V_usLen698);
					P_DIFor645->DataLen_645[0] = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen;
					break;
				}
			}
            if(OperationMode == C_Read)
            {
				P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD;
            }
            else
            {
                P_DIFor645->V_ucOAD = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI;
            }
			if( ( V_OIB == 0x00 ) && ( V_Nature == 0x05 ) )
			{
				P_DIFor645->MAXRecordTimes = 0;
				P_DIFor645->Unit_Scale[0] = C_NULL;
				P_DIFor645->Unit_Scale[0] <<= 8;
				P_DIFor645->Unit_Scale[0] |= C_NULL;
                P_DIFor645->NextClassNO = C_NULL;
				P_DIFor645->NextClassNum = 0;
                p_TableAddr = (Str_DI0_DataType_PaTable	*)GV_Str_Num_DataType_PaTable[13].P_DataType;
                if(OperationMode == C_Operation)
                {
					V_return = C_RWForbid_DAR;	            /*Ӧ��ܾ���д*/
					break;
                }
                else if(OperationMode == C_SetUp)
                {
                    if((P_DIFor645->V_ucOAD & 0x000000FF) == 0)
                    {
                        if( pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0] != C_structure )
                        {
                            V_return = C_TypeErr_DAR;	    /*Ӧ�����Ͳ�ƥ��*/
                            break;
                        }
                        else
                        {
                           if( pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[1] != 2 )   /*��������Ԫ��*/
                           {
								V_return = C_TypeErr_DAR;	/*Ӧ�����Ͳ�ƥ��*/
								break;
                           }
                        }
                    }
                }   /*else �� ����Ҫ�ж�*/

				if((P_DIFor645->V_ucOAD & 0x000000FF) == 0)
				{
                    V_645Off = 0;
                    V_698Off = 2;
                    *P_645DINum = 2;
                    for(k = 0; k < *P_645DINum; k++)
                    {
                        P_DIFor645->DataLen_645[k] = p_TableAddr[k].DataLen_645;
                        P_DIFor645->DataType[k] = p_TableAddr[k].DataType;
                    }
					P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD + 0x00000001;
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_structure;
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 2;
                }
                else
                {
                    V_645Off = 0;
                    V_698Off = 0;
                    *P_645DINum = 1;
					if((P_DIFor645->V_ucOAD & 0x000000FF) == 0x00000001)
					{
                        P_DIFor645->DataLen_645[0] = p_TableAddr[0].DataLen_645;
                        P_DIFor645->DataType[0] = p_TableAddr[0].DataType;
						pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_long_unsigned;
						pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;
					}
					else if((P_DIFor645->V_ucOAD & 0x000000FF) == 0x00000002)
					{
                        P_DIFor645->DataLen_645[0] = p_TableAddr[1].DataLen_645;
                        P_DIFor645->DataType[0] = p_TableAddr[1].DataType;
						pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_long_unsigned;
						pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;
					}
					else
					{
						V_return = C_ObjectUndefine_DAR;
						break;
              	  	}
                }
                pDataAddr = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data;
                if(OperationMode != C_Read)
                {
                    for(k = 0; k < *P_645DINum; k++)
                    {
                        if( pDataAddr[V_698Off] != P_DIFor645->DataType[k] )
                        {
                            V_return = C_TypeErr_DAR;	    			/*Ӧ�����Ͳ�ƥ��*/
                            break;
                        }   /*else Ϊ�Ϸ�*/

                        V_usLen698 = SF_GetFixedLen(&pDataAddr[V_698Off]);
                        pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen
                            = SF_DataExchangeTo645_BasicData(&pDataAddr[V_698Off], &pDataAddr[V_645Off], V_usLen698, (uchar8 *)&V_usLen698);
                        V_645Off += pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen;
                        V_698Off += V_usLen698+1;
                    }
                }
			}
			else
			{
				if( ( V_OIB == 0x10 ) && ( OperationMode != C_Read ) )
				{
					V_return = C_RWForbid_DAR;          /*Ӧ��ܾ���д*/
					break;
				}
				if(V_Nature > 2)                        /*�α���������Բ�����2*/
				{
					V_return = C_ObjectUndefine_DAR;    /*Ӧ������δ����*/
					break;
				}

				*P_645DINum = 1;
				for(i = 0; i < GV_Str_OIB_DI2_ParameterTable01Len; i++)
				{
					if(V_OIB == GV_Str_OIB_DI2_ParameterTable01[i].OIB)
					{
						/**************ȡ�����ʶ��*************/
						pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = GV_Str_OIB_DI2_ParameterTable01[i].DataType;
						P_DIFor645->MAXRecordTimes = 0;
						P_DIFor645->DataType[0] = GV_Str_OIB_DI2_ParameterTable01[i].DataType;
						P_DIFor645->Unit_Scale[0] = GV_Str_OIB_DI2_ParameterTable01[i].Unit;
						P_DIFor645->Unit_Scale[0] <<= 8;
						P_DIFor645->Unit_Scale[0] |= GV_Str_OIB_DI2_ParameterTable01[i].Conversion;

						if(OperationMode == C_SetUp)
						{
							if( ( pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0] != GV_Str_OIB_DI2_ParameterTable01[i].DataType )
							 && ( V_DataOff == 0 ) )
							{
								V_return = C_TypeErr_DAR;	/*Ӧ�����Ͳ�ƥ��*/
								break;
							}
						}
						for(j = 0; j < GV_Str_Num_DataType_PaTableLen; j++)
						{
							if(GV_Str_OIB_DI2_ParameterTable01[i].NxtDataTypeNum == GV_Str_Num_DataType_PaTable[j].DataTypeNum)
							{
								P_DIFor645->NextClassNO = (Str_DI0_DataType_PaTable	*)GV_Str_Num_DataType_PaTable[j].P_DataType;
								P_DIFor645->NextClassNum = GV_Str_Num_DataType_PaTable[j].DataNum;
								p_TableAddr = (Str_DI0_DataType_PaTable	*)GV_Str_Num_DataType_PaTable[j].P_DataType;
								break;
							}
						}
						if(j >= GV_Str_Num_DataType_PaTableLen)
						{
							P_DIFor645->NextClassNO = C_NULL;
							P_DIFor645->IDFlay = C_TableIDDisvaliable;
							P_DIFor645->NextClassNum = 0;
							*P_645DINum = 1;
							pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = P_DIFor645->DataType[0];
							pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;

						}

	                    if(V_OIB == 0x02)           /*���*/
	                    {
	                      P_DIFor645->DataLen_698[0] = 6;
	                    }
	                    else if(V_OIB == 0x01)      /*ͨ�ŵ�ַ*/
	                    {
	                      P_DIFor645->DataLen_698[0] = 6;
	                    }
	                    else if(V_OIB == 0x03)      /*�ͻ����*/
	                    {
	                      P_DIFor645->DataLen_698[0] = 6;
	                    }
						 else if(V_OIB == 0x22)     /*�忨״̬��*/
	                    {
	                      P_DIFor645->DataLen_698[0] = 2;
						  pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 16;
	                    }
			    		else if(V_OIB == 0x12)      /*������������*/
	                    {
	                      P_DIFor645->DataLen_698[0] = 1;
	                      pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 8;
	                    }

						if(P_DIFor645->NextClassNO != C_NULL)
						{
							*P_645DINum = 1;

							if(GV_Str_Num_DataType_PaTable[j].DataTypeNum == C_MeterPosition_DataTypeNum)   /*λ����Ϣ��������ת��*/
							{
								if( ( P_DIFor645->V_ucOAD & 0xFF ) == 0 )
								{
									pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_structure;
									pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 3;
                                }
                                else
                                {
									if( ( P_DIFor645->V_ucOAD & 0xFF ) < 3 )
									{
										pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_structure;
										pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 4;
									}
									else if( ( P_DIFor645->V_ucOAD & 0xFF ) == 3 )
									{
										pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_double_long_unsigned;
										pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;
									}
									else
									{
										V_return = C_ObjectUndefine_DAR;
										break;
                              	  	}

                                }
								if(OperationMode != C_Read)
								{
									V_return = SF_DataExchangeTo645_Where(pV_698RWPara,(Str_DI0_DataType_PaTable *)GV_Str_Num_DataType_PaTable[j].P_DataType);
									P_DIFor645->DataLen_645[0] = CLMeter_Position;
								}
							}
							else if(GV_Str_Num_DataType_PaTable[j].DataTypeNum == C_LCDParamete_DataTypeNum)    /*��ʾ��������ת��*/
							{
								*P_645DINum = 0;
								pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_structure;
								pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = GV_Str_Num_DataType_PaTable[j].DataNum;
								if(V_DataOff==0)
								{
									P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD + 0x00000001;

									for(k = 0; k < GV_Str_Num_DataType_PaTable[j].DataNum; k++)
									{
										P_DIFor645->DataLen_645[k] = p_TableAddr[k].DataLen_645;
										P_DIFor645->DataType[k] = p_TableAddr[k].DataType;

										*P_645DINum += 1;
									}
								}
								else if( ( V_DataOff == 0x01 ) || ( ( V_DataOff >= 0x05 ) && ( V_DataOff <= 0x07 ) ) )
								{
									P_DIFor645->DataLen_645[0] = 1;
									P_DIFor645->DataType[0] = C_unsigned;
									pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_unsigned;
									pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;
									*P_645DINum = 1;

								}
								else if( ( V_DataOff >= 0x02 ) && ( V_DataOff <= 0x04 ) )
								{
									P_DIFor645->DataLen_645[0] = 2;
									P_DIFor645->DataType[0] = C_long_unsigned;
									pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_long_unsigned;
									pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;
									*P_645DINum = 1;
								}
								else
								{
									V_return = C_ObjectUndefine_DAR;        /*Ӧ������δ����*/
									break;
								}

								P_DIFor645->NextClassNum = 0;
								P_DIFor645->NextClassNO = C_NULL;
								P_DIFor645->IDFlay = C_TableIDDisvaliable;
								P_DIFor645->MAXRecordTimes = 0;

								if(OperationMode != C_Read)
								{
									V_return = SF_DataExchangeTo645_LCD(pV_698RWPara, (Str_Num_DataType_PaTable *)&GV_Str_Num_DataType_PaTable[j], &pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen);
								}
							}
							else if(GV_Str_Num_DataType_PaTable[j].DataTypeNum == C_Fate_DataTypeNum)				/*��ǰ�׷��ʵ��*/
							{
								if(OperationMode == C_SetUp)
								{
									V_return = SF_DataExchangeTo645_Fate(pV_698RWPara, (Str_Num_DataType_PaTable *)&GV_Str_Num_DataType_PaTable[j], &pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen);
									P_DIFor645->DataLen_645[0] = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen;
								}
								else if(OperationMode == C_Read)
								{
                                    V_ucNum = InF_RateNumChangeToHex();

									if(V_DataOff==0)
									{
										P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD + 0x00000001;
										pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_array;
										pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = V_ucNum;     /*12������*/
										*P_645DINum = 0;

										for(k = 0; k < V_ucNum; k++)
										{
											P_DIFor645->DataLen_645[k] = p_TableAddr[k].DataLen_645;
											P_DIFor645->DataType[k] = p_TableAddr[k].DataType;
											P_DIFor645->NextClassNum = C_NULL;
											*P_645DINum += 1;
										}
									}
									else if(V_DataOff <= V_ucNum)
									{
										P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD ;
										pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_double_long_unsigned;
										*P_645DINum = 1;
										P_DIFor645->DataLen_645[0] = p_TableAddr[0].DataLen_645;
										P_DIFor645->DataType[0] = p_TableAddr[0].DataType;
										P_DIFor645->NextClassNum = C_NULL;
								    }
									else
									{
                                        V_return = C_ObjectNotExist_DAR;        									/*Ӧ������δ����*/
				                        break;
									}
								}
								else
								{
									if(OperationMode == C_Operation)
									{
										pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen
											= SF_DataExchangeTo645_ActionData(&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0], pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data, V_OIB, pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen);
										P_DIFor645->DataLen_645[0] = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen;
									}
								}
							}
							else if(GV_Str_Num_DataType_PaTable[j].DataTypeNum == C_Ladder_DataTypeNum)     		/*��ǰ�׽���*/
							{
								if(OperationMode == C_SetUp)
								{
									V_return = SF_DataExchangeTo645_Ladder(pV_698RWPara, (Str_Num_DataType_PaTable *)&GV_Str_Num_DataType_PaTable[j], &pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen);
									P_DIFor645->DataLen_645[0] = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen;
								}
								else if(OperationMode == C_Read)
								{
									if(V_DataOff == 0)
									{
										P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD ;
										pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_structure;
										pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 3;   		/*3��,����ֵ\���\������*/
										*P_645DINum = 1;
									}
									else if(V_DataOff <= 3)
									{
										P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD ;
										pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_array;
										*P_645DINum = 1;
										P_DIFor645->DataLen_645[0] = p_TableAddr[0].DataLen_645;
										P_DIFor645->DataType[0] = p_TableAddr[0].DataType;
										pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_array;
										P_DIFor645->NextClassNO = (Str_DI0_DataType_PaTable *)GV_Str_Num_DataType_PaTable[j].P_DataType;
										if(V_DataOff == 1)
										{
											pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 6;
										}
										else if(V_DataOff == 2)
										{
											pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 7;
										}
										else if(V_DataOff == 3)
										{
											pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 4;
										}
										else
										{
											V_return = C_ObjectUndefine_DAR;        								/*Ӧ������δ����*/
											break;
								        }
									}
								}
								else
								{
									if(OperationMode == C_Operation)
									{
										pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen
											= SF_DataExchangeTo645_ActionData(&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0], pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data, V_OIB, pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen);
										P_DIFor645->DataLen_645[0] = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen;
									}
								}
							}
							else if(GV_Str_Num_DataType_PaTable[j].DataTypeNum == C_Time_DataTypeNum)   			/*��ʱ�α���������ת��*/
							{
								*P_645DINum = 0;
								pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_array;

								if(OperationMode == C_Read)
								{
									k = 1;
									InF_Read_Data(CDay_Time_Num, &V_ucNum, &k, &V_usDataEncode);    									/*ʱ������Ϊ�������*/
									if(V_ucNum > 14)
									{
										V_ucNum = 14;
									}

									V_Day_Time_Num = V_ucNum;

									k=1;
									InF_Read_Data(CDay_Table_Num, &V_ucNum, &k, &V_usDataEncode);   									 /*ʱ����Ϊ�������*/
									if(V_ucNum > 8)
									{
										V_ucNum = 8;
									}
									*P_645DINum = V_ucNum;
									pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = V_ucNum;
								}
								else
								{
							      	*P_645DINum = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[1];
							      	V_Day_Time_Num = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[3];
								}
								if(V_DataOff == 0)
								{
									/*��ǰ�ס���������ʱ�α������д*/
									if( ( ( pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD == 0x40160200)
                                       || ( pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD == 0x40170200 ) )
									 && ( OperationMode != C_Read ) )
                                     {
                                       return C_RWForbid_DAR;
                                     }

									V_usOff = 0;
									P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD + 0x00000001;

									P_DIFor645->NextClassNO = (Str_DI0_DataType_PaTable *)GV_Str_Num_DataType_PaTable[j].P_DataType;
									P_DIFor645->NextClassNum = GV_Str_Num_DataType_PaTable[j].DataNum;
									P_DIFor645->IDFlay = C_TableIDDisvaliable;

									if(OperationMode != C_Read)
									{
										V_usOff = 3;
										if(InF_JudgeIJTimer() != C_OK)
										{
												return(C_Unauthorized_DAR);
										}
                  					}
									for(k = 0; k < *P_645DINum; k++)
									{
										if(OperationMode == C_Read)
										{
											P_DIFor645->DataLen_645[k] = V_Day_Time_Num * 3;
										}
										else
										{
											P_DIFor645->DataLen_645[k] = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[V_usOff] * 3;
											V_usOff = V_usOff + ( pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[V_usOff] * 8 ) + 2;
										}
										P_DIFor645->DataType[k] = C_array;

										P_DIFor645->MAXRecordTimes = 0;
									}
								}
								else
								{
									k = 1;
									InF_Read_Data(CDay_Time_Num, &V_ucNum, &k, &V_usDataEncode);     						/*ʱ������Ϊ�������*/
									if(V_ucNum > 14)
									{
										V_ucNum = 14;
									}
									pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = V_ucNum;
									pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_array;
									*P_645DINum = 1;
									if(OperationMode == C_Read)
									{
										P_DIFor645->DataLen_645[0] = V_Day_Time_Num * 3;
									}
									else
									{
										P_DIFor645->DataLen_645[0] = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[1] * 3;
									}
									P_DIFor645->DataType[0] = C_NULL;
									P_DIFor645->NextClassNO = (Str_DI0_DataType_PaTable *)GV_Str_Num_DataType_PaTable[j].P_DataType;
									P_DIFor645->NextClassNO++;
									P_DIFor645->NextClassNum = GV_Str_Num_DataType_PaTable[j].DataNum - 1;
									P_DIFor645->IDFlay = C_TableIDDisvaliable;
									P_DIFor645->MAXRecordTimes = 0;
								}
								if(OperationMode != C_Read)
								{

								    V_return = SF_DataExchangeTo645_ZoneTime(pV_698RWPara, (Str_Num_DataType_PaTable *)&GV_Str_Num_DataType_PaTable[j], &pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen);
								}
							}
							else if(GV_Str_Num_DataType_PaTable[j].DataTypeNum == C_ZoneTime_DataTypeNum)	/*ʱ�α���������ת��*/
							{
								*P_645DINum = 0;

								pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_structure;
								pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = GV_Str_Num_DataType_PaTable[j].DataNum;
								for(k = 0; k < GV_Str_Num_DataType_PaTable[j].DataNum; k++)
								{
									P_DIFor645->DataLen_645[k] = p_TableAddr[k].DataLen_645;
									P_DIFor645->DataType[k] = p_TableAddr[k].DataType;
									P_DIFor645->NextClassNum = 0;
									P_DIFor645->NextClassNO = C_NULL;
									P_DIFor645->IDFlay = C_TableIDDisvaliable;
									*P_645DINum += 1;
									P_DIFor645->MAXRecordTimes = 0;
								}
								if(V_DataOff == 0)
								{
									P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD + 0x00000001;
								}
								else if( ( V_DataOff >= 1) && ( V_DataOff <= 6 ) )
								{
									pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = p_TableAddr[V_DataOff - 1].DataType;
									pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;
									*P_645DINum = 1;
									P_DIFor645->DataType[0] = p_TableAddr[0].DataType;
									P_DIFor645->DataLen_645[0] = p_TableAddr[V_DataOff - 1].DataLen_645;
								}
								else
								{
									V_return = C_ObjectUndefine_DAR;        								/*Ӧ����������*/
									break;
								}
								if(OperationMode != C_Read)
								{

									V_return = SF_DataExchangeTo645_LCD(pV_698RWPara, (Str_Num_DataType_PaTable *)&GV_Str_Num_DataType_PaTable[j], &pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen);
								}
							}
							else if(GV_Str_Num_DataType_PaTable[j].DataTypeNum == C_AlarmLimit_DataTypeNum)	/*���������ֵ��������ת��*/
							{
                                *P_645DINum = 2;
                                for(k = 0; k < *P_645DINum; k++)
                                {
                                    P_DIFor645->DataLen_645[k] = 4;
                                    P_DIFor645->DataType[k] = C_double_long_unsigned;
                                    P_DIFor645->NextClassNum = 0;
                                    P_DIFor645->NextClassNO = C_NULL;
                                    P_DIFor645->IDFlay = C_TableIDDisvaliable;
                                    P_DIFor645->MAXRecordTimes = 0;
                                }
                                if(V_DataOff==0)
								{
									P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD + 0x00000001;
									pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_structure;
	                                pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 2;
								}
								else if( ( V_DataOff >= 1 ) && ( V_DataOff <= 2 ) )
								{
									pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_double_long_unsigned;
	                                pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;
	                                *P_645DINum =1;
								}
								else
								{
									V_return = C_ObjectUndefine_DAR;										/*Ӧ����������*/
									break;
								}

								if(OperationMode == C_Operation)
								{
									pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen
										= SF_DataExchangeTo645_ActionData(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data, pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data, V_OIB, pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen);
								}
								else if(OperationMode == C_SetUp)
								{

									V_return = SF_DataExchangeTo645_LCD(pV_698RWPara, (Str_Num_DataType_PaTable *)&GV_Str_Num_DataType_PaTable[j], &pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen);
								}
							}
							else if(GV_Str_Num_DataType_PaTable[j].DataTypeNum == C_OtherLimit_DataTypeNum)	/*���������ֵ��������ת��*/
							{
                                *P_645DINum = 3;
                                for(k = 0; k < *P_645DINum; k++)
                                {
                                    P_DIFor645->DataLen_645[k] = 4;
                                    P_DIFor645->DataType[k] = C_double_long_unsigned;
                                    P_DIFor645->NextClassNum = 0;
                                    P_DIFor645->NextClassNO = C_NULL;
                                    P_DIFor645->IDFlay = C_TableIDDisvaliable;
                                    P_DIFor645->MAXRecordTimes = 0;
								}
                                if(V_DataOff==0)
								{
									P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD + 0x00000001;
									pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_structure;
	                                pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 3;
								}
								else if( ( V_DataOff >= 1 ) && ( V_DataOff <= 3 ) )
								{
									pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_double_long_unsigned;
	                                pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;
	                                *P_645DINum =1;
								}
								else
								{
									V_return = C_ObjectUndefine_DAR;										/*Ӧ����������*/
									break;
								}
								if(OperationMode != C_Read)
								{

									V_return = SF_DataExchangeTo645_LCD(pV_698RWPara, (Str_Num_DataType_PaTable *)&GV_Str_Num_DataType_PaTable[j], &pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen);
								}
							}
							else if(GV_Str_Num_DataType_PaTable[j].DataTypeNum == C_Zone_DataTypeNum)		/*ʱ������������ת��*/
							{
								pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_array;
								if(OperationMode == C_Read)
								{
									k = 1;
									InF_Read_Data(CYear_Zone_Num, &V_ucNum, &k, &V_usDataEncode);							/*ʱ����Ϊ�������*/
									if(V_ucNum > 0x14)
									{
										V_ucNum = 0x14;
									}
									pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = PF_BCDtoHexOneByte(V_ucNum);
								}

								P_DIFor645->DataLen_645[0] = 3 * pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum;
								P_DIFor645->DataType[0] = C_structure;
								P_DIFor645->NextClassNum = GV_Str_Num_DataType_PaTable[j].DataNum;
								P_DIFor645->NextClassNO = (Str_DI0_DataType_PaTable*)GV_Str_Num_DataType_PaTable[j].P_DataType;
								*P_645DINum = 1;
								P_DIFor645->IDFlay = C_TableIDDisvaliable;
								P_DIFor645->MAXRecordTimes = 0;
								if(V_DataOff != 0)
								{
									pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_structure;
									pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 3;
									P_DIFor645->DataLen_645[0] = 3;
									P_DIFor645->DataType[0] = C_NULL;
								}
								if(OperationMode != C_Read)
								{
									V_return = SF_DataExchangeTo645_Zone(pV_698RWPara, P_DIFor645, (Str_Num_DataType_PaTable *)&GV_Str_Num_DataType_PaTable[j], &pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen);
									P_DIFor645->DataLen_645[0] = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen;
								}
							}
							else if(GV_Str_Num_DataType_PaTable[j].DataTypeNum == C_Holidy_DataTypeNum)		/*�ڼ�����������ת��*/
							{

								pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_array;
								if(OperationMode == C_Read)
								{
									k = CLHoliday_Num;
									InF_Read_Data(CHoliday_Num, V_HolidayNum, &k, &V_usDataEncode);    						/*�ڼ�����Ϊ�������*/
									if(V_HolidayNum[0] > 20)
									{
										V_HolidayNum[0] = 20;
									}
									pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = V_HolidayNum[0];

									if(V_DataOff == 0)
									{
										*P_645DINum = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum;
										if(*P_645DINum > 254)
										{
											*P_645DINum = 254;
										}
									}
									else
									{
										*P_645DINum = 1;
										pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_structure;
										pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = GV_Str_Num_DataType_PaTable[j].DataNum;

									}
								}

							}
							else if(GV_Str_Num_DataType_PaTable[j].DataTypeNum == C_VoltageOKPara)  		/*��ѹ�ϸ��ʲ�����������ת��*/
							{
								*P_645DINum = 4;
								P_DIFor645->NextClassNum = 0;
								P_DIFor645->NextClassNO = C_NULL;
								P_DIFor645->IDFlay = C_TableIDDisvaliable;
								P_DIFor645->MAXRecordTimes = 0;
								for(k = 0; k < *P_645DINum; k++)
                                {
                                    P_DIFor645->DataLen_645[k] = p_TableAddr[k].DataLen_645;;
                                    P_DIFor645->DataType[k] = p_TableAddr[k].DataType;

                                }
								V_698Off = 2;
								if(V_DataOff == 0)
								{
									P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD + 0x00000001;
									pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_structure;
	                                pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 4;
								}
								else if( ( V_DataOff >= 1 ) && ( V_DataOff <= 4 ) )
								{
									pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_long_unsigned;
	                                pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;
	                                P_DIFor645->DataType[0] = C_long_unsigned;
	                                *P_645DINum =1;
					 				V_698Off = 0;
								}
								else
								{
									V_return = C_ObjectUndefine_DAR;    /*Ӧ����������*/
									break;
								}

								pDataAddr = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data;

								if(OperationMode != C_Read)
								{
									for(k = 0; k < *P_645DINum; k++)
									{
										if(pDataAddr[V_698Off] != C_long_unsigned)
										{
											V_return = C_TypeErr_DAR;   /*���Ͳ�ƥ��*/
										    break;
										}
										V_usLen698 = SF_GetFixedLen(&pDataAddr[V_698Off]);
										pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen
											= SF_DataExchangeTo645_BasicData(&pDataAddr[V_698Off], &pDataAddr[V_645Off], V_usLen698,( uchar8 *)&V_usLen698);
										V_645Off += pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen;
										V_698Off += V_usLen698 + 1;
									}
								}
							}
							else    /*645��698һһ��Ӧ*/
							{
								if(OperationMode == C_Operation)
								{
									pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen
										= SF_DataExchangeTo645_ActionData(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data, pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data, V_OIB, pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen);
									P_DIFor645->DataLen_645[0] = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen;
								}
								else
								{
									V_usLen698 = SF_GetFixedLen(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data);
									if(V_usLen698 == 0)
									{
										V_usLen698 = SF_GetDataTypeLen(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data);
									}

									pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen
										= SF_DataExchangeTo645_BasicData(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data, pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data, V_usLen698, &V_usLen698);
									P_DIFor645->DataLen_645[0] = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen;
								}
							}
						}
						else
						{
							if(OperationMode == C_Operation)
							{
								pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen
									= SF_DataExchangeTo645_ActionData(&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0], pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data, V_OIB, pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen);
								P_DIFor645->DataLen_645[0] = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen;
							}
							else
							{
								if(OperationMode != C_Read)
								{
									V_usLen698 = SF_GetFixedLen(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data);
									if(V_usLen698 == 0)
									{
										V_usLen698 = SF_GetDataTypeLen(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data);
									}
									pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen
										= SF_DataExchangeTo645_BasicData(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data, pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data, V_usLen698, &V_usLen698);
									P_DIFor645->DataLen_645[0] = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen;
								}
							}
						}
						break;
					}
				}
				if(i >= GV_Str_OIB_DI2_ParameterTable01Len)
				{
					V_return = C_ObjectNotExist_DAR;	/*Ӧ������δ����*/
					break;
				}
			}
			break;
		}
		case	C_ParameterOIA41:
		{
			V_Temp = V_Nature&0x1F;						/*ȡ���Ա��*/
			P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD;

			if( ( V_Temp > 2 ) && ( V_OIB != 0x06 ) )	/*�α���������Բ�����5*/
			{
				V_return = C_ObjectUndefine_DAR;		/*Ӧ������δ����*/
				break;
			}

			*P_645DINum = 1;
			for(i = 0; i < GV_Str_OIB_DI2_ParameterTable02Len; i++)
			{
				if(V_OIB == GV_Str_OIB_DI2_ParameterTable02[i].OIB)
				{
					/**************ȡ�����ʶ��*************/
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = GV_Str_OIB_DI2_ParameterTable02[i].DataType;
					P_DIFor645->DataType[0] = GV_Str_OIB_DI2_ParameterTable02[i].DataType;
					P_DIFor645->Unit_Scale[0] = GV_Str_OIB_DI2_ParameterTable02[i].Unit;
					P_DIFor645->Unit_Scale[0] <<= 8;
					P_DIFor645->Unit_Scale[0] |= GV_Str_OIB_DI2_ParameterTable02[i].Conversion;
					P_DIFor645->MAXRecordTimes = 0;

					if( ( pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0] != GV_Str_OIB_DI2_ParameterTable02[i].DataType )
					 && ( V_DataOff == 0 ) && ( OperationMode == C_SetUp ) )
					{
						V_return = C_TypeErr_DAR;		/*Ӧ�����Ͳ�ƥ��*/
						break;
					}

					for(j = 0; j < GV_Str_Num_DataType_PaTableLen; j++)
					{
						if(GV_Str_OIB_DI2_ParameterTable02[i].NxtDataTypeNum == GV_Str_Num_DataType_PaTable[j].DataTypeNum)
						{
							P_DIFor645->NextClassNO = (Str_DI0_DataType_PaTable	*)GV_Str_Num_DataType_PaTable[j].P_DataType;
							P_DIFor645->NextClassNum = GV_Str_Num_DataType_PaTable[j].DataNum;
							break;
						}
					}
					if(j >= GV_Str_Num_DataType_PaTableLen)
					{
						P_DIFor645->NextClassNO = C_NULL;
						P_DIFor645->IDFlay = C_TableIDDisvaliable;
						P_DIFor645->NextClassNum = 0;
						*P_645DINum = 1;
						pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = P_DIFor645->DataType[0];
						pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;
					}
					if( ( V_OIB == 0x10 )           /*�������������1*/
					 || ( V_OIB == 0x12 )           /*�й���Ϸ�ʽ������*/
					 || ( V_OIB == 0x13 )           /*�޹���Ϸ�ʽ1������*/
					 || ( V_OIB == 0x14 ) )         /*�޹���Ϸ�ʽ2������*/
                    {
                        P_DIFor645->DataLen_698[0] = 1;
                        pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 8;
                    }
                    if( ( V_OIB == 0x04 )           /*���ѹ*/
					 || ( V_OIB == 0x05 )           /*�����*/
					 || ( ( V_OIB == 0x06 ) && ( V_Temp == 0x02 ) ) )   /*������*/
                    {
                        P_DIFor645->DataLen_698[0] = 6;
                        pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 6;
                    }
                    if( ( V_OIB == 0x06 ) && ( ( V_Temp == 0x03 ) || ( V_Temp == 0x04 ) ) )
                    {
                      P_DIFor645->DataLen_698[0] = 32;
                      pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 32;
                    }
                     if( ( V_OIB == 0x07 )          /*�й�׼ȷ�ȵȼ�*/
					  || ( V_OIB == 0x08 ) )        /*�޹�׼ȷ�ȵȼ�*/
					{
                        P_DIFor645->DataLen_698[0] = 4;
                        pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 4;
                    }
                    if(V_OIB == 0x03)               /*�ʲ��������*/
                    {
                        P_DIFor645->DataLen_698[0] = 32;
                        pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 32;
                    }
                    if(V_OIB == 0x0B)               /*���ܱ��ͺ�*/
                    {
                        P_DIFor645->DataLen_698[0] = 32;
                        pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 32;
                    }
		    		if(V_OIB == 0x11)               /*���������*/
                    {
                        P_DIFor645->DataLen_698[0] = 16;
                        pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 16;
                        if( ( OperationMode == C_SetUp ) && ( InF_JudgeIJTimer() != C_OK ) )
                        {
                            return C_RWForbid_DAR;
                        }
                    }
					if(P_DIFor645->NextClassNO != C_NULL)
					{
						if(GV_Str_Num_DataType_PaTable[j].DataTypeNum == C_SettleDay_DataTypeNum)   /*��������������ת��*/
						{
							pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_array;
							if(OperationMode == C_Read)
							{
								if(V_DataOff == 0)
								{
									P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD + 0x00000001;
									pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 3;
									*P_645DINum = 0;
									for(k = 0; k < pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum; k++)
									{
										P_DIFor645->DataLen_645[k] = 2;
										P_DIFor645->DataType[k] = C_structure;
										P_DIFor645->NextClassNum = GV_Str_Num_DataType_PaTable[j].DataNum;
										P_DIFor645->NextClassNO = (Str_DI0_DataType_PaTable *)GV_Str_Num_DataType_PaTable[j].P_DataType;
										P_DIFor645->IDFlay = C_TableIDDisvaliable;
										*P_645DINum += 1;
										P_DIFor645->MAXRecordTimes = 0;
									}
								}
								else
								{
									pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_structure;
									pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 2;
									*P_645DINum = 1;

									P_DIFor645->DataLen_645[0] = 2;
									P_DIFor645->DataType[0] = C_NULL;
									P_DIFor645->NextClassNum = GV_Str_Num_DataType_PaTable[j].DataNum;
									P_DIFor645->NextClassNO = (Str_DI0_DataType_PaTable *)GV_Str_Num_DataType_PaTable[j].P_DataType;

									P_DIFor645->IDFlay = C_TableIDDisvaliable;
									P_DIFor645->MAXRecordTimes = 0;
								}
							}
							else
							{
								if(V_DataOff == 0)
								{
									*P_645DINum = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[1];
									for(k = 0; k < *P_645DINum; k++)
									{
										P_DIFor645->DataLen_645[k] = 2;

									}
								}
								else
								{
									*P_645DINum = 1;
									P_DIFor645->DataLen_645[0] = 2;
								}
							}
							if(OperationMode != C_Read)
							{
								V_return = SF_DataExchangeTo645_SettleDay(pV_698RWPara, (Str_Num_DataType_PaTable *)&GV_Str_Num_DataType_PaTable[j], &pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen);
							}
						}
						else        /*645��698һһ��Ӧ*/
						{
							V_usLen698 = SF_GetFixedLen(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data);
							if(V_usLen698 == 0)
							{
								V_usLen698 = SF_GetDataTypeLen(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data);
							}
							pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen
								= SF_DataExchangeTo645_BasicData(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data, pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data, V_usLen698, &V_usLen698);
							P_DIFor645->DataLen_645[0] = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen;
						}
					}
					else
					{
						if(OperationMode != C_Read)
						{
							V_usLen698 = SF_GetFixedLen(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data);
							if(V_usLen698 == 0)
							{
								V_usLen698 = SF_GetDataTypeLen(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data);
							}
							pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen
								= SF_DataExchangeTo645_BasicData(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data, pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data, V_usLen698, &V_usLen698);
							P_DIFor645->DataLen_645[0] = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen;
						}
					}
					break;
				}
			}
			if(i >= GV_Str_OIB_DI2_ParameterTable02Len)
			{
				V_return = C_ObjectNotExist_DAR;    	/*Ӧ������δ����*/
				break;
			}
			break;
		}
		case	C_ParameterOIA43:						/*���ܱ��豸��Ϣ*/
		{
			V_Temp = V_Nature & 0x1F;					/*ȡ���Ա��*/
			if(V_OIB != 0)
			{
				V_return = C_ObjectUndefine_DAR;		/*Ӧ������δ����*/
				break;
			}

			if( ( OperationMode == C_Operation ) && ( V_Temp > 6 ) || ( ( OperationMode != C_Operation ) && ( V_Temp > 10 ) ) )	/*�������Բ�����6���������Բ�����10*/
			{
				V_return = C_ObjectUndefine_DAR;		/*Ӧ������δ����*/
				break;
			}
			if(OperationMode == C_Read)
			{
				if(V_Temp == 1)
				{
					V_return = C_OK_DAR;				/*��������ֻ�����*/
					break;
				}
			}
			else if(OperationMode == C_SetUp)
			{
				for(i=0;i<GV_Str_DataType_4300PaTableLen;i++)
				{
					if(V_Temp==GV_Str_DataType_4300PaTable[i].Temp)
					{
						break;
					}
				}
				if(i>=GV_Str_DataType_4300PaTableLen)
				{
					V_return = C_ObjectUndefine_DAR;	/*Ӧ������δ����*/
					break;
				}
				if((pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0]!=GV_Str_DataType_4300PaTable[i].DataType)
						&&(V_DataOff ==0))
				{
					V_return = C_TypeErr_DAR;			/*Ӧ�����Ͳ�ƥ��*/
					break;
				}
			}
			else if(OperationMode == C_Operation)
			{

				if(V_Temp == 3)							/*���ݳ�ʼ��*/
				{
					if(C_Meter_Type == C_L_SmartMeter)
					{
					  	V_return = C_RWForbid_DAR;		/*Ӧ����������*/
						break;
					}
				}
				else if(V_Temp == 5)					/*�¼���ʼ��*/
				{
				}
				else if(V_Temp == 6)					/*��������*/
				{
				}
				else
				{
					V_return = C_RWForbid_DAR;			/*�ܾ���д*/
					break;
				}
				if(pV_698RWPara->TimeTag[0]!=C_TimeTagOn)
				{
					V_return = C_TimeLabelInvalid_DAR;
					break;
				}
				break;
			}
			if(V_Temp == 3)
			{
				pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType =C_structure;
				pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = GV_Str_DI0_DataType_FactoryPaTableLen;
				*P_645DINum = GV_Str_DI0_DataType_FactoryPaTableLen;

				P_DIFor645->Unit_Scale[0] = C_NULL;
				P_DIFor645->NextClassNO = C_NULL;
				P_DIFor645->NextClassNum = 0;
				P_DIFor645->IDFlay = C_TableIDDisvaliable;
				P_DIFor645->MAXRecordTimes = 0;
                uchar8 V_AddTemp=0,V_Sum=3;
				for(i=0;i<GV_Str_DI0_DataType_FactoryPaTableLen;i++)
				{
                    if(OperationMode == C_SetUp)
                    {
                        P_DIFor645->DataLen_645[i] = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[V_Sum];
                        V_AddTemp = P_DIFor645->DataLen_645[i];
                        V_Sum = V_Sum+V_AddTemp+2;
                    }
                    else
                    {
						P_DIFor645->DataLen_645[i] = GV_Str_DI0_DataType_FactoryPaTable[i].DataLen_645;
                    }
					P_DIFor645->DataLen_698[i] = GV_Str_DI0_DataType_FactoryPaTable[i].DataLen_698;
					P_DIFor645->DataType[i] = GV_Str_DI0_DataType_FactoryPaTable[i].DataType;
				}
				if(V_DataOff==0)
				{
					P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD + 0x00000001;
				}
				else if((V_DataOff>=1)&&(V_DataOff<=6))
				{
					P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD;
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_visible_string;
                    pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = P_DIFor645->DataLen_698[V_DataOff-1];
                    P_DIFor645->DataType[0] = GV_Str_DI0_DataType_FactoryPaTable[V_DataOff-1].DataType;
                    *P_645DINum =1;
                    P_DIFor645->DataLen_645[0] = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[1];
					P_DIFor645->DataLen_698[0] = GV_Str_DI0_DataType_FactoryPaTable[V_DataOff-1].DataLen_698;
				}
				else
				{
					V_return = C_ObjectUndefine_DAR;	/*Ӧ����������*/
					break;
				}

				if(OperationMode != C_Read)
				{
					P_DIFor645->V_ucOAD = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI;
					if(V_DataOff == 0)
					{
						j=2;
					}
					else
					{
						j = 0;
					}
					V_Temp=0;
					uchar8 k=0;
					for(i=0;i<*P_645DINum;i++)
					{
						if(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[j]!=C_visible_string)
					{
							V_return = C_TypeErr_DAR;	/*Ӧ�����Ͳ�ƥ��*/
							break;
						}
						V_Temp = SF_GetFixedLen(&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[j]);
						if(V_Temp==0)
						{
							V_Temp = SF_GetDataTypeLen(&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[j]);
						}
						pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen
							= SF_DataExchangeTo645_BasicData(&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[j],&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[k],V_Temp,&V_Temp);

						j = (j + V_Temp);
						k += (V_Temp-2);
					}
					pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen = P_DIFor645->DataLen_645[0];
				}
			}
			else if(V_Temp == 2)
			{
				pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_visible_string;
				pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 32;

				P_DIFor645->DataLen_645[0] = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[1];
				*P_645DINum =1;
				P_DIFor645->V_ucOAD = CEquipmentDis;

				P_DIFor645->DataLen_698[0] = 32;
				*P_645DINum = 1;
				P_DIFor645->NextClassNO = C_NULL;
				P_DIFor645->NextClassNum = 0;
				P_DIFor645->DataType[0] = C_visible_string;

				P_DIFor645->IDFlay = C_TableIDDisvaliable;

				if(OperationMode != C_Read)
				{
					V_Temp = SF_GetFixedLen(&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0]);
					if(V_Temp==0)
					{
						V_Temp = SF_GetDataTypeLen(&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0]);
					}
					pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen
						= SF_DataExchangeTo645_BasicData(&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0],&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0],V_Temp,&V_Temp);

					pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen = P_DIFor645->DataLen_645[0];
				}
			}
			else if(V_Temp == 4)
			{
				pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_date_time_s;
				pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;

				P_DIFor645->DataLen_645[0] = 7;
				*P_645DINum =1;
				P_DIFor645->V_ucOAD = CProd_Date;

				P_DIFor645->DataLen_698[0] = 7;
				*P_645DINum = 1;
				P_DIFor645->NextClassNO = C_NULL;
				P_DIFor645->NextClassNum = 0;
				P_DIFor645->DataType[0] = C_date_time_s;

				P_DIFor645->IDFlay = C_TableIDDisvaliable;

				if(OperationMode != C_Read)
				{
					V_Temp = SF_GetFixedLen(&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0]);
					if(V_Temp==0)
					{
						V_Temp = SF_GetDataTypeLen(&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0]);
					}
					pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen
						= SF_DataExchangeTo645_BasicData(&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0],&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0],V_Temp,&V_Temp);

					pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen = P_DIFor645->DataLen_645[0];
				}
			}
			else if(V_Temp == 5)
			{
				if(OperationMode != C_Read)
				{
					V_return = C_RWForbid_DAR;			/*�ܾ���д*/
					break;
				}
				pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_array;
				pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = C_ObjectNO_Len;

				P_DIFor645->DataLen_645[0] = 2;
				*P_645DINum =6;
				P_DIFor645->V_ucOAD = 0x43000500;

				P_DIFor645->DataLen_698[0] = 2;
				*P_645DINum = 1;
				P_DIFor645->NextClassNO = C_NULL;
				P_DIFor645->NextClassNum = 0;
				P_DIFor645->DataType[0] = 0x50;

				P_DIFor645->IDFlay = C_TableIDDisvaliable;
			}
			else if(V_Temp == 6)
			{
				V_AgreementNum = 1;							/*��Э�飬ֻ��һ��Э��汾��*/
				if( OperationMode == C_Read )
				{
					/*����Э��汾��*/
					V_DoubleAgreementFlagLen = CLDoubleAgreementFlag;
					V_DoubleAgreementReturn = InF_Read_Data(CDoubleAgreementFlag, &V_AgreementNum, &V_DoubleAgreementFlagLen, &V_usDataEncode);
					if( ( V_DoubleAgreementReturn != C_OK ) || ( V_AgreementNum > GV_Str_DI0_DataType_CommProTableLen ) || ( V_AgreementNum == 0 ) )
					{
						V_AgreementNum = 1;					/*�����������������2���ߵ���0Ĭ��Ϊ1*/
					}
					if( V_DataOff > V_AgreementNum )
					{
						V_return = V_AgreementNum;			/*Ӧ�����Բ�����*/
						break;
					}
				}
				else if( OperationMode == C_SetUp )
				{
					if(V_DataOff != 0)						/*Ŀǰ����ֻ֧������0x00����*/
					{
						V_return = C_ObjectNotExist_DAR;	/*Ӧ�����Բ�����*/
						break;
					}
					if(V_DataOff == 0) 						/*����Ϊ0*/
					{
						V_AgreementNum = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[1];		/*������*/
						InF_Write_Data(C_Msg_Communication, CDoubleAgreementFlag, &V_AgreementNum, CLDoubleAgreementFlag, C_W_SafeFlag);	/*Э�����д���ݲ�*/
					}
				}
				else
				{
					;
				}
				pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_array;
				pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = V_AgreementNum;

				for(i = 0; i < V_AgreementNum; i++)
				{
					P_DIFor645->DataLen_645[i] = GV_Str_DI0_DataType_CommProTable[i].DataLen_645;
					P_DIFor645->DataLen_698[i] = GV_Str_DI0_DataType_CommProTable[i].DataLen_698;
					P_DIFor645->DataType[i] = GV_Str_DI0_DataType_CommProTable[i].DataType;
				}

				if(V_DataOff == 0) 							/*����Ϊ0*/
				{
					P_DIFor645->V_ucOAD = CMeter_CommPro1;
					*P_645DINum = V_AgreementNum;
					P_DIFor645->NextClassNO = (Str_DI0_DataType_PaTable *)&GV_Str_DI0_DataType_CommProTable[0];
					P_DIFor645->NextClassNum = 1;
#if 0
					if( ( pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[1] != V_AgreementNum ) && ( OperationMode == C_SetUp ) )
					{
						V_return = C_TypeErr_DAR;	/*Ӧ�����Ͳ�ƥ��*/
						break;
					}
#endif
				}
				else
				{
					P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD;
					*P_645DINum =1;
					P_DIFor645->NextClassNO = C_NULL;
					P_DIFor645->NextClassNum = 0;

					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_visible_string;
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = CLMeter_CommPro1;
				}

				if(OperationMode != C_Read)
				{
                    if(V_DataOff == 0) 						/*����Ϊ0*/
                    {
                      /*��1�����͵�λ��ƫ��,00:���飻01�����������02��ʼԪ��*/
                       j = C_Meter_CommPro_DataOff02;
                       for(i=0;i<V_AgreementNum;i++)
                       {
                          if(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[j]!=C_visible_string)
                          {
                              V_return = C_TypeErr_DAR;		/*Ӧ�����Ͳ�ƥ��*/
                              break;
                          }
                          V_Temp = SF_GetFixedLen(&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[j]);
                          if(V_Temp==0)
                          {
                              V_Temp = SF_GetDataTypeLen(&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[j]);
                          }
                          pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen
                              = SF_DataExchangeTo645_BasicData(&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[j],&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[V_ucDataoff],V_Temp,&V_Temp);
                          V_ucDataoff = V_Temp - C_TypeLen_Len-C_TypeLen;

                          P_DIFor645->DataLen_645[i] = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen;

                          /*��2�����͵�λ��ƫ��*/
                          j += V_Temp;
                       }
                    }
                    else
                    {
                        j = C_Meter_CommPro_DataOff00;
					if(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[j]!=C_visible_string)
					{
						V_return = C_TypeErr_DAR;			/*Ӧ�����Ͳ�ƥ��*/
						break;
					}
					V_Temp = SF_GetFixedLen(&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[j]);
					if(V_Temp==0)
					{
						V_Temp = SF_GetDataTypeLen(&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[j]);
					}
					pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen
						= SF_DataExchangeTo645_BasicData(&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[j],&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0],V_Temp,&V_Temp);

					P_DIFor645->DataLen_645[0] = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen;
                    }
				}
			}
			else if((V_Temp == 7)||(V_Temp == 8)||(V_Temp == 9))
			{
				if(V_Temp == 7)
				{
					P_DIFor645->V_ucOAD = CAllowFollowUpTell;
				}
				else if(V_Temp == 8)
				{
					P_DIFor645->V_ucOAD = CAllowAccordUpTell;
				}
				else
				{
					P_DIFor645->V_ucOAD = CAllowMasterCall;
				}
				if((pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0]!= C_bool)
					&&(OperationMode == C_SetUp))
				{
						V_return = C_TypeErr_DAR;			/*���Ͳ�ƥ��*/
						break;
				}
				pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_bool;
				pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;

				P_DIFor645->DataLen_645[0] = 1;
				*P_645DINum =1;

				P_DIFor645->DataLen_698[0] = 1;
				*P_645DINum = 1;
				P_DIFor645->NextClassNO = C_NULL;
				P_DIFor645->NextClassNum = 0;
				P_DIFor645->DataType[0] = C_bool;

				P_DIFor645->IDFlay = C_TableIDDisvaliable;

				if(OperationMode != C_Read)
				{
					P_DIFor645->V_ucOAD = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI;

					V_Temp = SF_GetFixedLen(&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0]);
					if(V_Temp==0)
					{
						V_Temp = SF_GetDataTypeLen(&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0]);
					}
					pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen
						= SF_DataExchangeTo645_BasicData(&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0],&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0],V_Temp,&V_Temp);

					pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen = P_DIFor645->DataLen_645[0];
				}
			}
			else if(V_Temp == 10)
            {
                if(OperationMode == C_SetUp)
                {
                    V_ucChannelNum = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[1];                 /*�������*/
                    pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0] = V_ucChannelNum;
                    pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen = 1;
                    if( V_ucChannelNum > (CLUpTellChannel / C_DataCodeLen) )    /*ֻ������3��*/
                    {
                        V_return = C_OtherErr_DAR;
                        break;
                    }
                    for(i = 0; i < V_ucChannelNum; i++)
                    {
                        if(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[2 + (i * 5)] !=  C_OAD)	/*�����ж� ����+����+OAD����+OAD��������2,ÿ��OAD4�ֽ�+1�ֽ�����������5*/
                        {
                            V_return = C_TypeErr_DAR;	    												/*���Ͳ�ƥ��*/
                            break;
                        }
                        else
                        {
                            V_ulChannelOAD = PF_Buffer4ToUlong32_698(&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[2 + (i * 5) + 1]);
                            PF_Ulong32ToBuffer4(&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[1+i*4],&V_ulChannelOAD,4);
                            pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen += 4;
                        }
                    }

                    if ( (V_return == C_TypeErr_DAR) || (V_return == C_OtherErr_DAR) )
                    {
                        break;
                    }

                }

                pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_array;
                P_DIFor645->MAXRecordTimes = 0;
                P_DIFor645->IDFlay = C_TableIDDisvaliable;
                P_DIFor645->DataType[0] = C_OAD;
                P_DIFor645->Unit_Scale[0] = C_NULL;
                P_DIFor645->DataType[1] = C_OAD;
                P_DIFor645->DataType[2] = C_OAD;
                pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum=1;
                P_DIFor645->DataLen_645[0] = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen;

                if(OperationMode != C_Read)
				{
					P_DIFor645->V_ucOAD = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI;
                }
                else
                {
                    P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD;
                }
                *P_645DINum = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum;
                if(V_DataOff != 0)
                {
                    pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_OAD;
                    pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 1;
                    P_DIFor645->DataType[0] = C_NULL;
                    *P_645DINum = 1;
                    V_return = C_RWForbid_DAR;		/*�ܾ���д*/
                    break;
                }
            }
			else
			{
				V_return = C_ObjectUndefine_DAR;	/*Ӧ������δ����*/
				break;
			}
			break;
		}
		case	C_PasswordrOIA44:					/*����*/
		{
			V_Temp = V_Nature&0x1F;					/*ȡ���Ա��*/

			if(V_Temp > 5)							/*�α���������Բ�����5*/
			{
				V_return = C_ObjectUndefine_DAR;	/*Ӧ������δ����*/
				break;
			}
			if(V_OIB > 0x01)
			{
				V_return = C_ObjectNotExist_DAR;	/*Ӧ������δ����*/
				break;
			}
			if(V_OIB == 0)							/*Ӧ������*/
			{
				if(((OperationMode == C_Read)&&(V_Nature == 2))||
                    (OperationMode == C_Operation)||((OperationMode == C_SetUp)&&((InF_JudgeIJTimer() != C_OK)||(V_Nature != 3))))
				{
			  		V_return = C_RWForbid_DAR;		/*�ܾ���д*/
					break;
				}
				if(V_Nature == 0x03)
				{
					P_DIFor645->DataLen_645[0] = 2;
					P_DIFor645->DataLen_645[1] = 2;
					P_DIFor645->DataLen_645[2] = 2;
					P_DIFor645->DataLen_645[3] = 2;
					P_DIFor645->DataLen_645[4] = 8;
					P_DIFor645->DataLen_645[5] = 16;
					P_DIFor645->DataLen_645[6] = 4;

					P_DIFor645->DataLen_698[0] = 2;
					P_DIFor645->DataLen_698[1] = 2;
					P_DIFor645->DataLen_698[2] = 2;
					P_DIFor645->DataLen_698[3] = 2;
					P_DIFor645->DataLen_698[4] = 64;
					P_DIFor645->DataLen_698[5] = 128;
					P_DIFor645->DataLen_698[6] = 4;

					P_DIFor645->DataType[0] = C_long_unsigned;
					P_DIFor645->DataType[1] = C_long_unsigned;
					P_DIFor645->DataType[2] = C_long_unsigned;
					P_DIFor645->DataType[3] = C_long_unsigned;
					P_DIFor645->DataType[4] = C_bit_string;
					P_DIFor645->DataType[5] = C_bit_string;
					P_DIFor645->DataType[6] = C_double_long_unsigned;
					*P_645DINum = 7;
					P_DIFor645->V_ucOAD = CAppProInformation;
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_structure;
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 7;

					P_DIFor645->NextClassNO = C_NULL;
					P_DIFor645->NextClassNum = 0;

					P_DIFor645->IDFlay = C_TableIDDisvaliable;
                    uchar8 V_Buf[50]={0},V_AddLen=2,V_TypeLen,k=0;
					if(V_DataOff==0)
					{
						P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD + 0x00000001;
                        if(OperationMode == C_SetUp)
                        {
                            for(i=0;i<*P_645DINum;i++)
                            {
                                if((pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[V_AddLen]) != P_DIFor645->DataType[i])
                                {
                                    V_return = C_RWForbid_DAR;	/*Ӧ��ܾ���д*/
                                    break;
                                }
                                if(i == 4)
                                {
                                    V_TypeLen=2;
                                }
                                else if(i == 5)
                                {
                                    V_TypeLen=3;
                                }
                                else
                                {
                                    V_TypeLen=1;
                                }
                                V_AddLen += V_TypeLen;
                                PF_CopyDataBytes(&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[V_AddLen],V_Buf,P_DIFor645->DataLen_645[i]);
                                PF_CopyDataBytes(V_Buf,&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[k],P_DIFor645->DataLen_645[i]);
                                V_AddLen += P_DIFor645->DataLen_645[i];
                                k += P_DIFor645->DataLen_645[i];
                            }
                        }
					}
					else if((V_DataOff>=1)&&(V_DataOff<=7))
					{
						P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD;
						pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = P_DIFor645->DataType[V_DataOff-1];
	                    pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = P_DIFor645->DataLen_698[V_DataOff-1];
	                     P_DIFor645->DataType[0] = P_DIFor645->DataType[V_DataOff-1];
	                     *P_645DINum =1;
                        P_DIFor645->DataLen_645[0] = P_DIFor645->DataLen_645[V_DataOff-1];
                        P_DIFor645->DataLen_698[0] = P_DIFor645->DataLen_698[V_DataOff-1];
                        if(V_DataOff == 5)
                        {
                            V_TypeLen=2;
                        }
                        else if(V_DataOff == 6)
                        {
                            V_TypeLen=3;
                        }
                        else
                        {
                            V_TypeLen=1;
                        }
                        PF_CopyDataBytes(&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[V_TypeLen],V_Buf,P_DIFor645->DataLen_645[0]);
                        PF_CopyDataBytes(V_Buf,pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data,P_DIFor645->DataLen_645[0]);
					}
					else
					{
						V_return = C_ObjectUndefine_DAR;		/*Ӧ����������*/
						break;
					}
				}
				else if(V_Nature == 0x04)
				{
					P_DIFor645->DataLen_645[0] = 1;

					P_DIFor645->DataType[0] = C_unsigned;
					*P_645DINum = 1;
					P_DIFor645->V_ucOAD = CClientAddr;
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_unsigned;
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;

					P_DIFor645->NextClassNO = C_NULL;
					P_DIFor645->NextClassNum = 0;

					P_DIFor645->IDFlay = C_TableIDDisvaliable;
				}
				else if(V_Nature == 0x05)
				{
					P_DIFor645->DataLen_645[0] = 1;

					P_DIFor645->DataType[0] = C_enum;
					*P_645DINum = 1;
					P_DIFor645->V_ucOAD = CConAutheMechanism;
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_enum;
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;

					P_DIFor645->NextClassNO = C_NULL;
					P_DIFor645->NextClassNum = 0;

					P_DIFor645->IDFlay = C_TableIDDisvaliable;
				}
			}
			else 									/*Ӧ����������*/
			{
				if(OperationMode != C_SetUp)
				{
					V_return = C_RWForbid_DAR;		/*�ܾ���д*/
					break;
				}
				if(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0]!=C_visible_string)
				{
					V_return = C_TypeErr_DAR;
					break;
				}
				*P_645DINum =1;
				P_DIFor645->V_ucOAD = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI;
				V_Temp = CL698Key;

				pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen
							= SF_DataExchangeTo645_BasicData(&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0],&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0],V_Temp,&V_Temp);
				P_DIFor645->DataLen_645[0] = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen;
			}
			break;
		}
		case	C_PasswordrOIA45:					/*�����ź�ǿ��*/
		{
			V_Temp = V_Nature&0x1F;					/*ȡ���Ա��*/
			if(V_Temp > 11)							/*�α���������Բ�����5*/
			{
				V_return = C_ObjectUndefine_DAR;	/*Ӧ������δ����*/
				break;
			}
			if(V_OIB != 0x00)
			{
				V_return = C_ObjectUndefine_DAR;	/*Ӧ������δ����*/
				break;
			}
			if(OperationMode == C_Read)
			{
				if(V_Temp==1)
				{
			  		V_return = C_OK_DAR;			/*�ɹ�*/
					break;
				}
			}
			if(OperationMode == C_Operation)
			{
				V_return = C_RWForbid_DAR;			/*�ܾ���д*/
				break;
			}
            if(OperationMode == C_SetUp)
			{
                if( ( V_Nature == 0x09 ) && ( pV_698RWPara->ChannelNo != C_Module ) )	/*ֻ��ģ��ͨ��д�ź�ǿ��*/
                {
                    V_return = C_RWForbid_DAR;      /*�ܾ���д*/
                    break;
                }
			}
			if(V_Temp!=9)
			{
				V_return = C_ObjectUndefine_DAR;	/*Ӧ������δ����*/
				break;
			}
			pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_long;
			pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;
			P_DIFor645->DataLen_645[0] = 2;
			*P_645DINum =1;
			P_DIFor645->V_ucOAD = CGPS_Signal;
			P_DIFor645->DataLen_698[0] = 2;
			P_DIFor645->NextClassNO = C_NULL;
			P_DIFor645->NextClassNum = 0;
			P_DIFor645->DataType[0] = C_long;
			P_DIFor645->IDFlay = C_TableIDDisvaliable;

			if(OperationMode != C_Read)
			{
				if(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0]!=C_long)
				{
					V_return = C_TypeErr_DAR;		/*���Ͳ�ƥ��*/
					break;
				}
				V_Temp = SF_GetFixedLen(&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0]);
				if(V_Temp==0)
				{
					V_Temp = SF_GetDataTypeLen(&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0]);
				}
				pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen
					= SF_DataExchangeTo645_BasicData(&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0],&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0],V_Temp,&V_Temp);
				pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen = P_DIFor645->DataLen_645[0];
			}
			break;
		}
		case	C_EventRecordOIA:					/*�¼���¼*/
		{
			if(OperationMode != C_Read)
			{
				P_DIFor645->V_ucOAD = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI;
			}
			else
			{
				P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD;
			}

			V_Temp = V_Nature&0x1F;					/*ȡ���Ա��*/

			if((pV_698RWPara->TimeTag[0]!=C_TimeTagOn)&&(OperationMode == C_Operation)&&(V_Temp == 0x01))
			{
				V_return = C_TimeLabelInvalid_DAR;
				break;
			}

			for(i=0;i<C_Event_OIBTableLen;i++)
			{
				if(V_OIB == Event_OIBTable[i].OIB)
				{
					break;
				}
			}
			if(i>=C_Event_OIBTableLen)
			{
				V_return = C_ObjectNotExist_DAR;	/*���󲻴���*/
				break;
			}
            if(V_OIB == CAux_Pow_Down_OIB)
            {
                V_ucDataLen = CLAuxi_Power_Sign;
                if(InF_Read_Data(CAuxi_Power_Sign, V_ucDataTemp, &V_ucDataLen, &V_usDataEncode) != C_OK)		/*������Դ����*/
                {
					V_return = C_ObjectNotExist_DAR;	/*���󲻴���*/
					break;
				}
				if(V_ucDataTemp == C_NoACPowerFail)		/*û�и�����Դ*/
				{
					V_return = C_ObjectNotExist_DAR;	/*���󲻴���*/
					break;
				}
            }
#if 0
            if(V_OIB == CNeutralCurrentAbnormal_OIB)    /*�ж����ߵ����Ƿ���*/
            {
				V_ucDataLen = CLZero_Current_Sign;
				if(InF_Read_Data(CZero_Current_Sign,&V_ucDataTemp,&V_ucDataLen) == C_OK)
				{
					if((V_ucDataTemp == C_ZeroCurrentOff)
						&&(InF_JudgeIJTimer() != C_OK))
					{
						V_return = C_ObjectNotExist_DAR;	/*���󲻴���*/
						break;
					}
				}
            }
#endif
			V_ucClassNum = Event_OIBTable[i].TypeClass;
			if(OperationMode == C_SetUp)
			{
				if(((V_ucClassNum == 7)&&((V_Temp != 6)&&(V_Temp != 8)&&(V_Temp != 3)&&(V_Temp != C_Event07ReportType)))	/*���ò���/�����ϱ�����/��������/�ϱ�����*/
					||((V_ucClassNum == 24)&&((V_Temp != 5)&&(V_Temp != 11)&&(V_Temp != 2)&&(V_Temp != C_Event24ReportType))))
				{
					V_return = C_RWForbid_DAR;		/*�ܾ���д*/
					break;
				}
			}
			if(OperationMode == C_Operation)
			{

				if(V_Temp == 4)						/*���һ����������*/
				{

				}
				else if(V_Temp == 5)				/*ɾ��һ����������*/
				{
				}
				else if(V_Temp == 1)				/*��¼����*/
				{
                	if(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0] != C_integer)
                	{
                		V_return = C_RWForbid_DAR;	/*�ܾ���д*/
                	}
				}
				else if(V_Temp ==0x0F)				/*ɾ����������*/
				{

				}
				else
				{
					V_return = C_RWForbid_DAR;		/*�ܾ���д*/
				}
				break;
			}

            if(((V_Temp == 9)&&(V_ucClassNum == 7))||((V_Temp == 12)&&(V_ucClassNum == 24)))
            {
                if(OperationMode != C_Read)
                {
                    V_return = C_RWForbid_DAR;		/*��7������9����24������12ֻ��������ҹ̶�Ϊ1*/
                    break;
                }
                else
                {
                    V_return = C_OK_DAR;			/*��7������9����24������12ֻ��������ҹ̶�Ϊ1*/
                    break;
                }
            }
			if(V_ucClassNum == 7)					/*�޷����¼���¼*/
			{
				if(V_OIB == 0x27)
				{
					if((V_Temp > 11)&&(V_Temp != 29))		/*������Բ�����10*/
					{
						V_return = C_ObjectUndefine_DAR;	/*Ӧ������δ����*/
						break;
					}
				}
				else
				{
					if(V_Temp > C_Event07ReportType)		/*������Բ�����11*/
					{
						V_return = C_ObjectUndefine_DAR;	/*Ӧ������δ����*/
						break;
					}
				}
			}
			else if(V_ucClassNum == 24)						/*�з����¼���¼*/
			{
				if((V_Temp > C_Event24ReportType)||((V_Temp == 13)&&(V_OIB != 0)))/*������Բ�����14��ʧѹ��¼������13,δ��������12*/
				{
					V_return = C_ObjectUndefine_DAR;		/*Ӧ������δ����*/
					break;
				}
			}
			else
			{
				V_return = C_ObjectTypeErr_DAR;				/*�ӿ��಻����*/
				break;
			}
			if((pV_698RWPara->ServiceFlag_Second < 3)		/*��ȡ��������*/
				||((pV_698RWPara->ServiceFlag_Second == 3)&&(OperationMode != C_Read)))
			{
			/******************��ȡ���ò���*******************/
				if(V_Temp == 13)	/*��ȡ��ʧѹ*/
				{
					if(V_OIB == 0)
					{
						P_DIFor645->NextClassNO = C_NULL;
						P_DIFor645->NextClassNum= 0;
						P_DIFor645->IDFlay = C_TableIDDisvaliable;
						P_DIFor645->DataType[0] = C_double_long_unsigned;
						P_DIFor645->MAXRecordTimes = 0;

						P_DIFor645->DataType[1] = C_double_long_unsigned;
						P_DIFor645->DataType[2] = C_date_time_s;
						P_DIFor645->DataType[3] = C_date_time_s;
						if(V_DataOff == 0x00)
						{
							P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD+0x00000001;
							pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_structure;
							pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 4;
							*P_645DINum = 4;
						}
						else if((V_DataOff >= 0x01)&&(V_DataOff <= 0x04))
						{
							pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = P_DIFor645->DataType[V_DataOff-1];
							pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;
							*P_645DINum = 1;
							P_DIFor645->DataType[0] = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType;
						}
						else
						{
							V_return = C_ObjectUndefine_DAR;			/*Ӧ������δ����*/
							break;
						}
						break;
					}
					else
					{
						V_return = C_ObjectUndefine_DAR;				/*Ӧ������δ����*/
						break;
					}
				}
				if( ( ( V_Temp == 6 ) &&( V_ucClassNum == 7 ) )			/*��ȡ���ò���*/
				 || ( ( V_Temp == 5 ) && ( V_ucClassNum == 24 ) ) )
				{

					Str_EventPara_Type *pParmAddr;
					uchar8	V_ParmNum;

					pParmAddr = (Str_EventPara_Type *)Event_OIBTable[i].ConfParaTableAddr;
					V_ParmNum =  Event_OIBTable[i].ConfParaNum;
					if(pParmAddr == C_NULL)
					{
						V_return = C_ObjectNotExist_DAR;				/*���󲻴���*/
						break;
					}
					*P_645DINum = 0;
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_structure;
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;

					for(j=0;j<V_ParmNum;j++)
					{
						P_DIFor645->DataType[j] = pParmAddr[j].DataTpye698;
						P_DIFor645->DataLen_645[j] = pParmAddr[j].Len645;
						P_DIFor645->NextClassNO = C_NULL;
						P_DIFor645->NextClassNum = 0;
						P_DIFor645->MAXRecordTimes = 0;
						P_DIFor645->IDFlay = C_TableIDDisvaliable;
						pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum++;
					}
					if(V_ucClassNum == 7)
					{
						P_DIFor645->DataType[C_MaxDataTypeNum-1] = 7;
					}
					else
					{
						P_DIFor645->DataType[C_MaxDataTypeNum-1] = 24;
					}
                    P_DIFor645->DataType[C_MaxDataTypeNum-2] = V_ParmNum;	/*���������ۼ�ʱ����ʱ�����ò����ĵڼ���λ��*/
					*P_645DINum = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum;
					if(V_DataOff == 0x00)
					{
                        P_DIFor645->V_ucOAD += 0x00000001;
					}
					else if((V_DataOff >= 0x01)&&(V_DataOff <= *P_645DINum))
					{
						pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = P_DIFor645->DataType[V_DataOff-1];
						pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;
						*P_645DINum = 1;
                        P_DIFor645->DataLen_645[0] = P_DIFor645->DataLen_645[V_DataOff-1];
                        if(OperationMode == C_Read)
                        {
                            P_DIFor645->DataType[0] = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType;
                        }
					}
					else
					{
						V_return = C_ObjectUndefine_DAR;					/*Ӧ������δ����*/
						break;
					}
					if(OperationMode == C_SetUp)
					{

						V_return= SF_DataExchangeTo645_EventPa(pV_698RWPara,pParmAddr,&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen,P_DIFor645->DataType[C_MaxDataTypeNum-2]);
					}
				}
				else if((((V_Temp == 8)||(C_07EventReportTypeAttribute == V_Temp))&&(V_ucClassNum == 7))	/*�ϱ�����*/
					||(((V_Temp == 11)||(C_24EventReportTypeAttribute == V_Temp))&&(V_ucClassNum == 24)))   /*2020��׼�ϱ���־���ϱ���ʽ*/
				{

					uchar8	V_Len=1;
					*P_645DINum = 1;
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_enum;
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;

					P_DIFor645->DataType[0] = C_enum;
					P_DIFor645->DataLen_645[0] = 1;
					P_DIFor645->DataLen_698[0] = 1;
					P_DIFor645->NextClassNO = C_NULL;
					P_DIFor645->NextClassNum = 0;
					P_DIFor645->MAXRecordTimes = 0;
					P_DIFor645->IDFlay = C_TableIDDisvaliable;

					if(OperationMode == C_SetUp)
					{
						if(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0]!=C_enum)
						{
							return C_TypeErr_DAR;
						}
						pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen
							= SF_DataExchangeTo645_BasicData(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data,pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data,V_Len,&V_Len);
					}
				}
				else if(((V_Temp == 3)&&(V_ucClassNum == 7))			/*��ȡ��������*/
					||((V_Temp == 2)&&(V_ucClassNum == 24)))
				{
			/******************��ȡ�¼���¼���������б�*******************/
					if(OperationMode != C_Read)
                    {
						V_return = C_OK_DAR;
					}
					else
					{
						P_DIFor645->DataType[0] = C_array;
						P_DIFor645->DataType[1] = C_OAD;
						P_DIFor645->DataLen_645[0] = 5;
						P_DIFor645->DataLen_645[1] = 5;
						P_DIFor645->NextClassNO = C_NULL;
						P_DIFor645->NextClassNum = 0;
						P_DIFor645->MAXRecordTimes = 0;
						P_DIFor645->IDFlay = C_TableIDDisvaliable;
						P_DIFor645->NextClassNO = 0;
						P_DIFor645->NextClassNum= 0;
						*P_645DINum = 1;
					}
				}
				else if(((V_Temp == 7)&&(V_ucClassNum == 7))			/*��ȡ��ǰֵ*/
					||((V_Temp == 10)&&(V_ucClassNum == 24)))
				{
			/******************��ȡ�¼���¼��ǰֵ*******************/
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_array;
                    P_DIFor645->MAXRecordTimes = 0;
                    P_DIFor645->IDFlay = C_TableIDValiable;
					P_DIFor645->DataType[0] = C_structure;
					P_DIFor645->Unit_Scale[0] = C_NULL;
					P_DIFor645->DataType[1] = C_structure;
					P_DIFor645->DataType[2] = C_structure;
					P_DIFor645->DataType[3] = C_structure;
					if(V_ucClassNum == 24)
					{

						P_DIFor645->NextClassNO = (Str_DI0_DataType_PaTable *)Event_Class24_CurrentRecTable;
						P_DIFor645->NextClassNum= 2;
                        pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 4;
                        P_DIFor645->DataLen_645[0] = 0;
                        P_DIFor645->DataLen_645[1] = 8;
                        P_DIFor645->DataLen_645[2] = 8;
                        P_DIFor645->DataLen_645[3] = 8;

					        *P_645DINum = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum;
                        if(V_DataOff == 0)
                        {
                            P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD + 0x00000001;
                            if((V_OIB == 0x0B)||(V_OIB == 0x07)||(V_OIB == CPFactorT_Over_OIB))
                            {
                                P_DIFor645->DataLen_645[0] = 8;
                            }
						}
						else
						{
                            if(V_DataOff == 0x01)
							{
                                if((V_OIB != 0x00)&&(V_OIB != 0x07)&&(V_OIB != 0x0B)&&((V_OIB != CPFactorT_Over_OIB)))
                                {
                                    return C_ObjectNotExist_DAR;
                                }
                                P_DIFor645->DataLen_645[0] = 8;
                           	}
                            else
                            {
                                P_DIFor645->DataLen_645[0] = 8;
                            }
                            pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_structure;
                            pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 2;
                            P_DIFor645->DataType[0] = C_NULL;
                            *P_645DINum = 1;
                        }
					}
					else
					{
						if((pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD&0xFFFFFF00) == 0x30230700)
						{
	                        if(V_DataOff > 0x02)
	                        {
	                            return C_ObjectNotExist_DAR;
	                        }
							if(pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD != 0x30230700)
							{
								pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_structure;
							}
							pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 2;
						}
						else
						{
	                        if(V_DataOff > 0x01)
	                        {
	                            return C_ObjectUndefine_DAR;
	                        }
	                        pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 1;
	                    }

						P_DIFor645->NextClassNO = (Str_DI0_DataType_PaTable *)Event_Class7_CurrentRecTable;
						P_DIFor645->NextClassNum= 4;
                        *P_645DINum = 1;
                        P_DIFor645->DataLen_645[0] = 9;
                        if(V_DataOff != 0x00)
						{
							if((pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD&0xFFFFFF00) == 0x30230700)
							{
                            	P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD;

                            }
                            else
							{
                            	P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD&0xFFFFFFFE;
                            }
							pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_structure;
							pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 2;

							P_DIFor645->DataType[0] = C_NULL;
							*P_645DINum = 1;
						}
					}
				}
				else if(((V_Temp == 5)&&(V_ucClassNum == 7))		/*��ȡ���ֵ*/
					||((V_Temp == 4)&&(V_ucClassNum == 24)))
				{
			/******************��ȡ�¼���¼����¼��*******************/
                    if((OperationMode != C_Read))
                    {
                        return C_RWForbid_DAR;
                    }
                    pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_long_unsigned;
                    if(V_OIB == CKey_Update_OIB)
                    {
                        pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 2;
                    }
                    else if((V_OIB == CBroadcastTime_OIB)||(CPow_Down_OIB == V_OIB))        /*������߹㲥Уʱ*/
                    {
                        pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 100;
                    }
                    else
                    {
                        pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 10;
                    }
                    *P_645DINum = 0;
                }
                else if(((V_Temp == 4)&&(V_ucClassNum == 7))								/*��ȡ��ǰ��¼����*/
                        ||((V_Temp == 3)&&(V_ucClassNum == 24)))
                {
                    if(V_OIB == 0x26)
                    {
                        P_DIFor645->MAXRecordTimes = 2;
                    }
                    else if((V_OIB == CBroadcastTime_OIB)||(V_OIB == CPow_Down_OIB))
                    {
                        P_DIFor645->MAXRecordTimes = 100;
                    }
                    else
                    {
                        P_DIFor645->MAXRecordTimes = 10;
                    }
    /******************��ȡ�¼���¼��ǰ����*******************/
					if(V_ucClassNum == 24)
					{
						pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 4;
						pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_structure;
						P_DIFor645->NextClassNO = C_NULL;
						P_DIFor645->NextClassNum= 0;
						P_DIFor645->IDFlay = C_TableIDDisvaliable;
						P_DIFor645->DataLen_645[0] = 2;
						P_DIFor645->Unit_Scale[0] = C_NULL;
						P_DIFor645->DataLen_645[0] = 2;
						*P_645DINum = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum;
						for(j=0;j<*P_645DINum;j++)
						{
							P_DIFor645->DataType[j] = C_long_unsigned;
						}

						if(V_DataOff !=0)
						{
							if( ( V_OIB == CTrend_Rev_OIB )			/*�й����ʷ���*/	
							|| ( V_OIB == CPFactorT_Over_OIB )		/*��������������*/
							|| ( V_OIB == CRe_ReDe_Over_OIB ) )		/*�޹���������*/
							{
								P_DIFor645->V_ucOAD = Event_OIBTable[i].RecordNum+(V_DataOff-1)*0x00000001;
							}
							else
							{
								if(V_DataOff ==0x01)
								{
									return C_ObjectUndefine_DAR;
								}
								P_DIFor645->V_ucOAD = Event_OIBTable[i].RecordNum+(V_DataOff-2)*0x00000001;
							}
							pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_long_unsigned;
							pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;
							*P_645DINum = 1;
						}
						else
						{
							P_DIFor645->IDNO = (i|C_ClassNum24All);
						}
					}
					else
					{
						if(V_DataOff > 0x01)
						{
							return C_ObjectUndefine_DAR;
						}
						pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_long_unsigned;
						pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;
						P_DIFor645->V_ucOAD =  Event_OIBTable[i].RecordNum;
						P_DIFor645->DataType[0] = C_long_unsigned;
						*P_645DINum = 1;
					}
				}
				else if ( ( V_Temp == 29 ) && ( V_ucClassNum == 7 ) )	   		/*��ȡ�Ƿ��忨�ܴ���,����29�����쳣�忨�¼���¼��������һ��*/
				{
                    if(V_DataOff > 0x01)
                    {
                        return C_ObjectUndefine_DAR;
                    }
                    pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_double_long_unsigned;
                    pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;
#if 0
				    P_DIFor645->V_ucOAD =  Event_OIBTable[i].RecordNum;
#endif
                    P_DIFor645->V_ucOAD =  CLawlessC_Degree;
                    P_DIFor645->DataType[0] = C_double_long_unsigned;
                    *P_645DINum = 1;
				}
                else if(((V_Temp == 10)&&(V_ucClassNum == 7))					/*��ȡ��ǰ��¼ʱ��״̬��¼��*/
					||((V_Temp == 14)&&(V_ucClassNum == 24)))
                {
			/*************************************/
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_array;
                    P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD;
                    P_DIFor645->MAXRecordTimes = 0;
                    P_DIFor645->IDFlay = C_TableIDValiable;
					P_DIFor645->DataType[0] = C_structure;
					P_DIFor645->Unit_Scale[0] = C_NULL;
					P_DIFor645->DataType[1] = C_structure;
					P_DIFor645->DataType[2] = C_structure;
					P_DIFor645->DataType[3] = C_structure;
					if(V_ucClassNum == 24)
					{
                        pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 4;
						P_DIFor645->NextClassNO = (Str_DI0_DataType_PaTable *)Event_Class24_14AttriTable;
						P_DIFor645->NextClassNum= 2;
                        P_DIFor645->DataLen_645[0] = 0;
						P_DIFor645->DataLen_645[1] = 14;
                        P_DIFor645->DataLen_645[2] = 14;
                        P_DIFor645->DataLen_645[3] = 14;


                        if(V_DataOff == 0)
						{
                            if((V_OIB==0x0B)||(V_OIB==0x07)||(V_OIB==CPFactorT_Over_OIB))
	                        {
	                                P_DIFor645->DataLen_645[0] = 14;
                            }
                            P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD + 0x00000001;
                            *P_645DINum = 4;
                        }
                        else
                        {
							if((V_DataOff == 0x01)&&((V_OIB != 0x07)&&(V_OIB != 0x0B)&&(V_OIB != CPFactorT_Over_OIB)))
							{
								V_return = C_ObjectNotExist_DAR;				/*���󲻴���*/
							}
							else
							{
								P_DIFor645->DataLen_645[0] = 14;
							}
							pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_structure;
							pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 2;

							P_DIFor645->DataType[0] = C_NULL;
							*P_645DINum = 1;
						}
	                }
					else
					{
						pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 1;
						P_DIFor645->NextClassNO = (Str_DI0_DataType_PaTable *)Event_Class7_10AttriTable;
						P_DIFor645->NextClassNum= 4;
                        P_DIFor645->DataLen_645[0] = 15;
                        *P_645DINum = 1;
						if((pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD&0xFFFFFF00) == 0x30230A00)
                        {
	                        if(V_DataOff > 0x02)
	                        {
	                            return C_ObjectNotExist_DAR;
	                        }
							if(pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD != 0x30230A00)
							{
								pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_structure;
							}
							pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 2;
						}
						else
						{
	                        if(V_DataOff > 0x01)
                            {
	                            return C_ObjectUndefine_DAR;
                            }
	                        pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 1;
	                    }
                        if(V_DataOff != 0)
                        {
                            P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD&0xFFFFFFFE;/*��������00ȥȡֵ*/
                            pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_structure;
                            pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 2;
                            P_DIFor645->DataType[0] = C_NULL;
                        }
					}
				}
                else if(((V_Temp == 2)&&(V_ucClassNum == 7))		/*�¼���¼��ܾ�ֱ�����Զ�ȡ,Ӧ��ܾ���д*/
					||(((V_Temp < 10)&&(V_Temp > 5))&&(V_ucClassNum == 24)))
                {
					return C_RWForbid_DAR;
				}
				else if(V_Temp == 1)
				{
					V_return = C_OK_DAR;							/*��������ֻ�����*/
					break;
				}
				else
				{
					V_return = C_ObjectUndefine_DAR;				/*����δ����*/
					break;
				}
				break;
			}
			else if((pV_698RWPara->ServiceFlag_Second == 3)||(pV_698RWPara->ServiceFlag_Second == 4))
			{
			/**************ȡѡ�񷽷�:�¼���¼��ʱֻ֧�ֶ�ȡ�ϵ�n�μ�¼***************/
				if((pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].Rd_RecordSelect[0] != 9)
					&&(pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].Rd_RecordSelect[0] != 1)
					&&(pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].Rd_RecordSelect[0] != 2))
				{
					V_return = C_ObjectTypeErr_DAR;					/*����ӿ��಻����*/
					break;
				}
				if(pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].Rd_RecordSelect[0] == 9)
				{
					if((pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD != 0x303C0200)&&(pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD != (CPow_Down_Note_1&0xFFFFFF00)))
					{
						if(pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].Rd_RecordSelect[1] > 10)
						{
							V_return = C_OverStep_DAR;				/*��ȡ����Խ��*/
							break;
						}
					}
					else
					{
					   if(pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].Rd_RecordSelect[1] > 100)
					   {
							V_return = C_OverStep_DAR;				/*��ȡ����Խ��*/
							break;
					   }

					}
				}
				if(V_ucClassNum == 7)								/*�޷����¼���¼*/
				{
					if(V_Temp != 2)									/*������Բ�����9*/
					{
						V_return = C_ObjectTypeErr_DAR;				/*Ӧ������δ����*/
						break;
					}
				}
				else if(V_ucClassNum == 24)							/*�з����¼���¼*/
				{
					if((V_Temp < 6)	||(V_Temp > 9))					/*������Բ�����12��ʧѹ��¼������13*/
					{
						V_return = C_ObjectTypeErr_DAR;				/*Ӧ������δ����*/
						break;
					}
                    if((V_OIB != CTrend_Rev_OIB)&&(V_OIB != CRe_ReDe_Over_OIB)&&(V_OIB != CPFactorT_Over_OIB)&&(V_Temp == 6))/*���ʷ����޹��������ޡ���������*/
                    {
                        V_return = C_ObjectUndefine_DAR;			/*Ӧ������δ����*/
						break;
                    }
				}
				else
				{
					V_return = C_ObjectTypeErr_DAR;					/*�ӿ��಻����*/
					break;
				}
			}

			break;
		}
		case	C_FrozeRecordOIA:									/*�����¼*/
		{
			V_Temp = V_Nature&0x1F;									/*ȡ���Ա��*/
			for(i=0;i<C_Freeze_OIBTableLen;i++)
			{
				if(V_OIB == Freeze_OIBTable[i].OIB)
				{
					break;
				}
			}
            if(i >= C_Freeze_OIBTableLen)
            {
                if((V_OIB == 0x01)||(V_OIB == 0x07))
                {
                    V_return = C_ObjectNotExist_DAR;				/*Ӧ�����Բ�����*/
                }
                else
                {
                    V_return = C_ObjectUndefine_DAR;				/*Ӧ������δ����*/
                }
                break;
            }
			if(OperationMode == C_Operation)
			{
				if((V_Temp < 3)||(V_Temp == 6)||((V_Temp == 3)&&(V_OIB != 0)))
				{
					V_return = C_RWForbid_DAR;						/*�ܾ���д*/
				}
				break;
			}
			if(V_Temp>3)
			{
					V_return = C_ObjectUndefine_DAR;				/*Ӧ������δ����*/
					break;
			}
			if((OperationMode != C_Read)&&(V_Temp != 3))
			{
				V_return = C_RWForbid_DAR;							/*��������ֻ�����*/
				break;
			}
			if(V_Temp == 3)											/*��ȡ���������б�*/
			{
                if((OperationMode == C_Read)&&(pV_698RWPara->ServiceFlag_Second != 3))
				{
				/******************��ȡ�¼���¼���������б�*******************/
					V_ucLen = CLI_Free_OADTabLen_T;
					V_return = InF_Read_Data(Freeze_OIBTable[i].RelatedOAD_T, V_ucDataTemp, &V_ucLen, &V_usDataEncode);	/*���������ڼ���������������*/
					if(V_return != C_OK)
					{
						V_ucDataTemp[0] = 0;

					}

					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_array;
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = V_ucDataTemp[0];
					P_DIFor645->NextClassNO = 0;
					P_DIFor645->NextClassNum= 0;
					P_DIFor645->MAXRecordTimes = 0;
					*P_645DINum = 1;
					break;
                }
				else
                {
                }
			}
			else if((V_Temp == 2)&&((pV_698RWPara->ServiceFlag_Second == 3)||(pV_698RWPara->ServiceFlag_Second == 4)||(pV_698RWPara->ServiceFlag_Second == 5)))
			{
				V_return = C_OK_DAR;				/*��������ֻ�����*/
				break;
			}
			else
			{
				V_return = C_ObjectTypeErr_DAR;		/*��������ֻ�����*/
				break;
			}
			break;
		}
		case	C_ESAMActionOIA:					/*ESAM���*/
		{
			P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD;
			if(V_OIB == 0)							/*ESAM��Ϣ*/
			{
				if(OperationMode == C_Read)
				{
					*P_645DINum = 1;
					if(((V_Nature>1)&&(V_Nature<5))||(V_Nature == 10)||(V_Nature == 18))
					{
						pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_octet_string;
					}
					if(V_Nature == 17)
					{
						pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_unsigned;
					}
					if((V_Nature == 5)||(V_Nature == 6)||(V_Nature == 14)||(V_Nature == 15)||(V_Nature == 19)||(V_Nature == 20))
					{
						if(OperationMode != C_Read)
						{
							return C_RWForbid_DAR;
						}
						pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_double_long_unsigned;
					}
					if(V_Nature == 21)
					{
						if(OperationMode != C_Read)
						{
							return C_RWForbid_DAR;
						}
						for(i=0;i<pV_698RWPara->RWOI_Num;i++)
						{
							if(V_DataOff !=0)
							{
								pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_double_long_unsigned ;
								pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;
								P_DIFor645->NextClassNO = C_NULL;
							}
							else
							{
								pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_structure;
								pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 2;
							}
						}
					}
					if(V_Nature == 7)
					{
						if(OperationMode != C_Read)
						{
							return C_RWForbid_DAR;
						}
						for(i=0;i<pV_698RWPara->RWOI_Num;i++)
						{
                            if(V_DataOff !=0)
                            {
                                pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_double_long_unsigned ;
                                pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;
                                P_DIFor645->NextClassNO = C_NULL;
                            }
                            else
                            {
							    pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_structure;
							    pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 3;
                            }
						}
					}
					else if((V_Nature >=8)&&(V_Nature <=13))	/*����8��13���ܾ���д*/
					{
						return C_RWForbid_DAR;
					}
				}
                else if(OperationMode == C_SetUp)
                {
					if(V_Nature == 14)
					{
						if(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0] == C_double_long_unsigned)
						{
							P_DIFor645->DataType[0] = C_double_long_unsigned;
							P_DIFor645->DataLen_645[0] = CL_double_long_unsigned;
							*P_645DINum = 1;
							V_usLen698 = CL_double_long_unsigned;
							pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen 
							= SF_DataExchangeTo645_BasicData(&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0],&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0],V_usLen698,&V_usLen698);
						}
						else
						{
							V_return = C_TypeErr_DAR;
							break;
						}
					}
					else
					{
						return C_RWForbid_DAR;
                	}
                }
				else
				{
                    if(V_Nature == ((uchar8)(C_ESAMF1000300>>8)))		/*ESAM���ݶ�ȡ*/
                    {
                        if(C_Meter_Type != C_L_SmartMeter)      		/*���Ǳ��ص��ܱ�*/
                        {
                            if((pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[4] == 0x05)			/*��ǰ�׵���ļ�*/
                                ||(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[4] == 0x06))		/*�����׵���ļ�*/
                            {
                                return C_ObjectNotExist_DAR;
                            }
                        }
                    }
					if((V_Nature > 14)||(V_Nature < 3)||(V_Nature == 8))
					{
						return C_RWForbid_DAR;
					}
					if((V_Nature == 11)||(V_Nature == 12))				/*ֻ�к���ͨ��֧�ֺ����ѯ����֤*/
					{
						if((pV_698RWPara->ChannelNo != C_IR)&&(InF_JudgeIJTimer() != C_OK)					/*����֧�ֺ�����֤*/
							&&(SV_Comm_Parse_Local.ClientAddrFlag != Termal_Address))						/*�����ն������֤*/
						{
							return C_RWForbid_DAR;
						}
					}
					ushort16 V_698Off,V_ucLen,V_645Off;
					uchar8 *pDataAddr;

					pDataAddr = &pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0];

					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_octet_string;
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;
					P_DIFor645->V_ucOAD = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI;
					P_DIFor645->DataType[0] = C_octet_string;
					P_DIFor645->DataLen_645[0] = 1;
					P_DIFor645->IDFlay = 0;
					P_DIFor645->NextClassNO = C_NULL;
					P_DIFor645->NextClassNum = 0;
					*P_645DINum = 1;

					if(pDataAddr[0] == C_structure)
					{
						i = pDataAddr[1];								/*ȡ�ṹ�����*/
						V_698Off = 2;
						V_645Off = 0;
						for(j=0;j<i;j++)
						{
							if(pDataAddr[V_698Off] == C_octet_string)
							{
								V_698Off++;
								pDataAddr[V_645Off] = pDataAddr[V_698Off];
								V_645Off++;
								V_ucLen = pDataAddr[V_698Off];
								V_698Off++;
								if(pDataAddr[V_645Off-1] > 0x80)
								{
									V_ucLen = 0;
									uchar8 k;
									for(k=0;k<(pDataAddr[V_645Off-1]&0x7F);k++)
									{
										V_ucLen<<=8;
										V_ucLen |= pDataAddr[V_698Off+k];
										pDataAddr[V_645Off+k] = pDataAddr[V_698Off+k];
									}
									V_698Off += (pDataAddr[V_645Off-1]&0x7F);
									V_645Off += (pDataAddr[V_645Off-1]&0x7F);
								}
								PF_CopyDataBytes_698(&pDataAddr[V_698Off], &pDataAddr[V_645Off], V_ucLen);
								V_645Off += V_ucLen;
								V_698Off += V_ucLen;
							}
							else if(pDataAddr[V_698Off] == C_SID_MAC)
							{
								pDataAddr[V_698Off] = 0;				/*����*/
								pDataAddr[V_645Off] = 4;				/*SID����*/
								V_645Off++;
								V_698Off++;
								PF_CopyDataBytes(&pDataAddr[V_698Off], &pDataAddr[V_645Off], 4);

								V_645Off += 4;
								V_698Off += 4;
								/***************ȡ��������*************/
								V_ucLen = pDataAddr[V_698Off];
								pDataAddr[V_645Off] = V_ucLen;			/*�������ݳ���*/
								V_645Off++;
								V_698Off++;
								PF_CopyDataBytes_698(&pDataAddr[V_698Off], &pDataAddr[V_645Off], V_ucLen);
								V_645Off += V_ucLen;
								V_698Off += V_ucLen;
								/***************ȡMAC*************/
								pDataAddr[V_645Off] = pDataAddr[V_698Off];
								V_ucLen = pDataAddr[V_698Off];
								V_698Off++;
								V_645Off++;
								PF_CopyDataBytes_698(&pDataAddr[V_698Off], &pDataAddr[V_645Off], V_ucLen);
								V_645Off += V_ucLen;
								V_698Off += V_ucLen;
							}
							else if(pDataAddr[V_698Off] == C_SID)
							{
							  	pDataAddr[V_698Off] = 0;				/*����*/
								pDataAddr[V_645Off] = 4;				/*SID����*/
								V_645Off++;
								V_698Off++;
								PF_CopyDataBytes(&pDataAddr[V_698Off], &pDataAddr[V_645Off], 4);

								V_645Off += 4;
								V_698Off += 4;
								/***************ȡ��������*************/
								V_ucLen = pDataAddr[V_698Off];
								pDataAddr[V_645Off] = V_ucLen;			/*�������ݳ���*/
								V_645Off++;
								V_698Off++;
								PF_CopyDataBytes_698(&pDataAddr[V_698Off], &pDataAddr[V_645Off], V_ucLen);
								V_645Off += V_ucLen;
								V_698Off += V_ucLen;
							}
						}
					}
				}
			}
			else if(V_OIB == 1)											/*ESAM��ȫģʽ*/
			{
				if(OperationMode == C_Operation)
				{
					if((V_Nature == 1)||(V_Nature == 127)||(V_Nature == 128)||(V_Nature == 129))
					{
							V_return = C_OK_DAR;						/*Ӧ������δ����*/
							break;
					}
					else
					{
						V_return = C_ObjectUndefine_DAR;				/*Ӧ������δ����*/
						break;
					}
				}
				else if(OperationMode == C_Read)
				{
					if(V_Nature>3)
					{
						return C_RWForbid_DAR;
					}
				}
				else
				{
					if(((V_Nature!=2)&&(V_Nature!=3))||((V_Nature==3)&&(V_DataOff != 0)))
					{
						return C_RWForbid_DAR;
					}
				}
				if(V_Nature == 3)
				{

				}
				else if(V_Nature == 2)
				{
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_enum;
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;

					P_DIFor645->DataType[0] = C_enum;
					P_DIFor645->DataLen_645[0] = 1;
					P_DIFor645->IDFlay = 0;
					P_DIFor645->NextClassNO = C_NULL;
					P_DIFor645->NextClassNum = 0;
					P_DIFor645->MAXRecordTimes = 0;
					*P_645DINum = 1;

					if(OperationMode != C_Read)
					{
						if(InF_JudgeIJTimer() != C_OK)
						{
								return C_RWForbid_DAR;
						}
						if(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0]!=C_enum)
						{
							V_return = C_TypeErr_DAR;
							break;
						}
						pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0] = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[1];	/*ö�����ͣ�������tagת��Ϊ���ȼ���*/
					}
				}
			}
			else
			{
				V_return = C_ObjectUndefine_DAR;					/*Ӧ������δ����*/
				break;
			}
			break;
		}
		case	C_ContralOIA:										/*�������*/
		{
			uchar8 V_698Off,V_645Off,k;
			ushort16	V_usLen698;
			uchar8 *pDataAddr;
			V_Temp = V_Nature&0x1F;									/*ȡ���Ա��*/
			pDataAddr = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data;
			P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD;
			if((pV_698RWPara->TimeTag[0]!=C_TimeTagOn)&&(OperationMode == C_Operation))
			{
				V_return = C_TimeLabelInvalid_DAR;
				break;
			}
			if(V_OIB == 0)											/*����բ���*/
			{
				if(OperationMode == C_Operation)
				{
					if((V_Nature == 127)||(V_Nature == 128))		/*�����������������*/
					{
						pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0] = 0;
						pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen = 0;
						pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Result = 0;
						*P_645DINum = 0;
					}
					else if((V_Nature == 129)||(V_Nature == 130)||(V_Nature == 131))		/*��բ��������*/
					{
						V_698Off = 0;
						V_645Off = 0;
						pDataAddr = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data;
						if(pDataAddr[V_698Off] == C_array)
						{
							V_698Off++;
							i=pDataAddr[V_698Off];					/*ȡ�������*/
							V_698Off++;
							for(;i>0;i--)
							{
								if(pDataAddr[V_698Off] == C_structure)
								{
									V_698Off++;
									j=pDataAddr[V_698Off];			/*ȡ�ṹ�����*/
									V_698Off++;
									for(k=0;k<j;k++)
									{
										V_usLen698 = SF_GetFixedLen(&pDataAddr[V_698Off]);
										if(V_usLen698==0)
										{
											V_usLen698 = SF_GetDataTypeLen(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data);
										}
										pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen
											= SF_DataExchangeTo645_BasicData(&pDataAddr[V_698Off],&pDataAddr[V_645Off],V_usLen698,(uchar8 *)&V_usLen698);
										V_645Off += pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen;
										V_698Off += (V_usLen698+1);
									}
									*P_645DINum = 0;
								}
								else
								{
									return C_TypeErr_DAR;			/*�������Ͳ���*/
								}
							}
							pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen = 1;
							pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Result = 0;
							*P_645DINum = 0;
						}
						else
						{
							return C_TypeErr_DAR;					/*�������Ͳ���*/
						}
					}

					else
					{
						return C_ObjectTypeErr_DAR;					/*�ӿ��಻ƥ��*/
					}
					break;
				}
				if(OperationMode == C_SetUp)
				{
					if(V_Nature != 2)								/*ֻ������2��֧������*/
					{
						return C_ObjectTypeErr_DAR;					/*�ӿ��಻ƥ��*/
					}

					P_DIFor645->IDFlay = C_NULL;

					P_DIFor645->NextClassNO = C_NULL;
					P_DIFor645->NextClassNum = 0;
					P_DIFor645->MAXRecordTimes = 0;


					if(V_DataOff ==0)
					{
						if((pDataAddr[0]!=C_structure)||(pDataAddr[2]!=C_double_long_unsigned)||(pDataAddr[7]!=C_long_unsigned))
						{
							return C_TypeErr_DAR;
						}
						P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD+0x00000001;
						P_DIFor645->DataLen_645[0] = 4;
						P_DIFor645->DataType[0] = C_double_long_unsigned;
						P_DIFor645->DataLen_645[1] =2;
						P_DIFor645->DataType[1] = C_long_unsigned;
						*P_645DINum = 2;
						V_698Off = 2;
						V_645Off = 0;

						for(i=0;i<*P_645DINum;i++)
						{
							V_usLen698 = SF_GetFixedLen(&pDataAddr[V_698Off]);
							pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen
								= SF_DataExchangeTo645_BasicData(&pDataAddr[V_698Off],&pDataAddr[V_645Off],V_usLen698,(uchar8 *)&V_usLen698);
							V_645Off += pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen;
							V_698Off += (V_usLen698+1);
						}
					}
					else if((V_DataOff ==0x01)||(V_DataOff ==0x02))
					{
						*P_645DINum = 1;
						if(V_DataOff ==0x01)
						{
							P_DIFor645->DataLen_645[0] = 4;
							P_DIFor645->DataType[0] = C_double_long_unsigned;
							if(pDataAddr[0]!=C_double_long_unsigned)
							{
								return C_TypeErr_DAR;
							}
						}
						if(V_DataOff ==0x02)
						{
							P_DIFor645->DataLen_645[0] = 2;
							P_DIFor645->DataType[0] = C_long_unsigned;
							if(pDataAddr[0]!=C_long_unsigned)
							{
								return C_TypeErr_DAR;
							}
						}
						V_698Off = 0;
						V_645Off = 0;
						V_usLen698 = SF_GetFixedLen(&pDataAddr[V_698Off]);
						pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen
								= SF_DataExchangeTo645_BasicData(&pDataAddr[V_698Off],&pDataAddr[V_645Off],V_usLen698,(uchar8 *)&V_usLen698);

					}
					else
					{
						V_return = C_ObjectUndefine_DAR;			/*Ӧ������δ����*/
						break;
					}
				}
				else
				{
					if(V_Nature>5)
					{

						return C_ObjectTypeErr_DAR;					/*�ӿ��಻ƥ��*/

					}
					if(V_Nature == 2)								/*ֻ������2��֧������*/
					{
						P_DIFor645->IDFlay = C_NULL;

						P_DIFor645->NextClassNO = C_NULL;
						P_DIFor645->NextClassNum = 0;
						P_DIFor645->MAXRecordTimes = 0;
						if(V_DataOff ==0)
						{
							P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD+0x00000001;
							pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_structure;
							pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 2;
							P_DIFor645->DataLen_645[0] = 4;
							P_DIFor645->DataType[0] = C_double_long_unsigned;
							P_DIFor645->Unit_Scale[0] = 36|0xFD00;
							P_DIFor645->DataLen_645[1] =2;
							P_DIFor645->DataType[1] = C_long_unsigned;
							P_DIFor645->Unit_Scale[1] = 0;
							*P_645DINum = 2;

						}
						else if((V_DataOff ==0x01)||(V_DataOff ==0x02))
						{

							pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;
							*P_645DINum = 1;
							if(V_DataOff ==0x01)
							{
								P_DIFor645->DataLen_645[0] = 4;
								P_DIFor645->DataType[0] = C_double_long_unsigned;
								pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_double_long_unsigned;
							}
							if(V_DataOff ==0x02)
							{
								P_DIFor645->DataLen_645[0] = 2;
								P_DIFor645->DataType[0] = C_long_unsigned;
								pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_long_unsigned;
							}
						}
						else
						{
							V_return = C_ObjectUndefine_DAR;	/*Ӧ������δ����*/
							break;
						}
					}
					else if(V_Nature == 3)
					{
						return C_ObjectUndefine_DAR;			/*����δ����*/
					}
					else if(V_Nature > 3)						/*ֻ������2��֧������*/
					{

						P_DIFor645->DataLen_645[0] = 1;
						P_DIFor645->DataType[0] = C_bit_string;
						P_DIFor645->IDFlay = C_NULL;

						P_DIFor645->NextClassNO = C_NULL;
						P_DIFor645->NextClassNum = 0;
						P_DIFor645->Unit_Scale[0] = 0;
						P_DIFor645->MAXRecordTimes = 0;
						P_DIFor645->DataLen_698[0] =8;
						*P_645DINum = 1;

						pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_bit_string;
						pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 8;
					}
				}
			}
			else if(V_OIB == 1)									/*�������*/
			{

				if(OperationMode == C_SetUp)
				{
					return C_ObjectNotExist_DAR;				/*Ӧ�����Բ�����*/
				}
				if(OperationMode == C_Operation)
				{
					if((V_Nature == 127)||(V_Nature == 128))
					{
						return C_OK;
					}
					else
					{
						return C_ObjectNotExist_DAR;			/*���󲻴���*/
					}
				}
				else if(OperationMode == C_Read)
				{
					if(V_Temp == 2)
					{
						pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_enum;
						pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;
                        P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD;
						P_DIFor645->DataType[0] = C_enum;
						P_DIFor645->DataLen_645[0] = 1;
						P_DIFor645->IDFlay = C_NULL;

						P_DIFor645->NextClassNO = C_NULL;
						P_DIFor645->NextClassNum = 0;
						P_DIFor645->Unit_Scale[0] = 0;
						P_DIFor645->MAXRecordTimes = 0;
						*P_645DINum = 1;
					}
					else
					{
						V_return = C_ObjectNotExist_DAR;		/*Ӧ�����Բ�����*/
						break;
					}
				}
			}
			else
			{
				return C_ObjectNotExist_DAR;
			}
			break;
		}
		case	C_ApplianceInOutOIA:							/*��������豸���*/
		{
			P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD;

			if((V_OIB > 0x0C)&&(V_OIB != 0x10))
			{
				return C_ObjectUndefine_DAR;					/*����δ����*/
			}
			else
			{
				if((V_OIB != 0x01)&&(V_OIB != 0x02)&&(V_OIB != 0x05)&&(V_OIB != 0x07)&&(V_OIB != 0x09))
				{
					return C_ObjectNotExist_DAR;				/*���󲻴���*/
				}
			}

			if(V_OIB == 0x01)
			{
				if(V_DataOff > 2)
				{
					return C_ObjectUndefine_DAR;				/*����δ����*/
				}
			}
			else
			{
				if(V_DataOff > 1)
				{
					return C_ObjectUndefine_DAR;				/*����δ����*/
				}
			}

			if(OperationMode == C_Read)
			{
				if(V_Nature > 2)
				{
					return C_ObjectUndefine_DAR;				/*����δ����*/
				}
			}
			else if(OperationMode == C_Operation)
			{
				if(V_OIB == 0x09)
				{
					if((V_Nature == 0x7F)||(V_Nature == 0x80))
					{
						return C_OK;							/*OK*/
					}
				}
				else
				{
					if(V_Nature == 0x7F)
					{
						return C_OK;							/*OK*/
					}
				}
			}
			else
			{
				return C_RWForbid_DAR;							/*�ܾ���д*/
			}

			if(V_DataOff==0)
			{
				pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_array;
				if(V_OIB == 0x01)
				{
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 2;
				}
				else
				{
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 1;
				}
				break;
			}
			else
			{
				if(V_OIB == 0x01)
				{
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_structure;
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 3;
				}
				else if(V_OIB == 0x02)
				{
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_structure;
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 2;
				}
				else if(V_OIB == 0x05)
				{
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_structure;
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 4;
				}
				else if(V_OIB == 0x06)
				{
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_enum;
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;
				}
				else if(V_OIB == 0x07)
				{
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_enum;
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;
				}
				else if(V_OIB == 0x09)
				{
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_structure;
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 3;
				}
				break;
			}
		}
		case	C_DisplayOIA:									/*��ʾ���*/
		{
			V_Temp = V_Nature&0x1F;								/*ȡ���Ա��*/
			P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD;
			if(V_Temp==02)
			{
				if(V_DataOff==0)
				{
					if(V_OIB==0)								/*ѭ��*/
					{
						V_ulDispNumDI = CAuto_Dis_Screen_Num;
					}
					else										/*����*/
					{
						V_ulDispNumDI = CKey_CycDis_Screen_Num;
					}
   					InF_Read_Data( V_ulDispNumDI, &V_ucDispNum, &PDataLength, &V_usDataEncode );
					if((V_ucDispNum == 0)||(V_ucDispNum>99))
					{
						V_ucDispNum = 1;
					}

					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_array;
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = V_ucDispNum;
				}
				else
				{
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_structure;
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 2;
				}
			}
			else if(V_Temp==03)
			{
				*P_645DINum = 1;
				P_DIFor645->DataLen_645[0] = 1;
				P_DIFor645->DataType[0] = C_long_unsigned;
				P_DIFor645->IDFlay = C_TableIDDisvaliable;
				P_DIFor645->NextClassNO = C_NULL;
				P_DIFor645->NextClassNum = 0;
				P_DIFor645->Unit_Scale[0] = 0;
				P_DIFor645->MAXRecordTimes = 0;
				P_DIFor645->DataLen_698[0] =2;
				pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_long_unsigned;
				pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 2;
			}
			else if(V_Temp==04)
			{
				*P_645DINum = 2;
				pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_structure;
				pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 2;
				P_DIFor645->DataLen_645[0] = 1;
				P_DIFor645->DataType[0] = C_unsigned;
				P_DIFor645->IDFlay = C_NULL;
				P_DIFor645->NextClassNO = C_NULL;
				P_DIFor645->NextClassNum = 0;
				P_DIFor645->Unit_Scale[0] = 0;
				P_DIFor645->MAXRecordTimes = 0;
				P_DIFor645->DataLen_698[0] =1;
				P_DIFor645->DataLen_645[1] = 1;
				P_DIFor645->DataType[1] = C_unsigned;

				if(V_DataOff==0)
				{
					P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD + 0x00000001;
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_structure;
                    pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 2;
				}
				else if((V_DataOff>=1)&&(V_DataOff<=2))
				{
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_unsigned;
					pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = 0;
					*P_645DINum =1;
				}
				else
				{
					V_return = C_ObjectUndefine_DAR;			/*Ӧ����������*/
					break;
				}

			}
			break;
		}
		case	C_FileTransferOIA:								/*�ļ�����*/
		{
            break;
		}
		case	C_ExternalOIA:									/*��չ������*/
		{
			if(OperationMode == C_Operation)
			{
				ushort16 V_usLen698;
				if( (V_Nature >= 128) && (V_Nature <= 130))		/*��֧��3������*/
				{
					if(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0] != C_octet_string)
					{
						V_return = C_TypeErr_DAR;				/*Ӧ�����Ͳ�ƥ��*/
						break;
					}
					V_usLen698 = SF_GetFixedLen(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data);
					if(V_usLen698==0)
					{
						V_usLen698 = SF_GetDataTypeLen(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data);
					}
					pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen
						= SF_DataExchangeTo645_BasicData(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data,pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data,V_usLen698,(uchar8 *)&V_usLen698);
					P_DIFor645->DataLen_645[0] = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen;
					V_return = C_OK;							/*Ӧ������δ����*/
					break;
				}
				else
				{
					V_return = C_ObjectUndefine_DAR;
				}
			}
			else if( OperationMode == C_Read )
			{
				P_DIFor645->V_ucOAD = pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD;
				pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.DataType = C_octet_string;
				V_ucDataLen = 255;
				InF_Read_Data( pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.OAD, V_ucData, &V_ucDataLen, &V_usDataEncode );
				pV_698RWPara->Rd_OI[pV_698RWPara->ResponedNum].RdOI.CarryNum = V_ucDataLen;
				

				P_DIFor645->MAXRecordTimes = 0;
				P_DIFor645->NextClassNO = C_NULL;
				P_DIFor645->NextClassNum = 0;

				P_DIFor645->DataType[0] = C_octet_string;
				P_DIFor645->DataLen_698[0] = (uchar8)V_ucDataLen;
				*P_645DINum =1;
				V_return = C_OK;
			}
			else
			{
				V_return = C_ObjectUndefine_DAR;
			}
            break;
		}
		default:
			return C_ObjectUndefine_DAR;						/*�������Ͳ��ԣ�Ӧ��ܾ���д*/
			break;
	}
	return V_return;
}
/*******************************************************************************
����ԭ�ͣ�char8 SF_GetAPDU_Encode(Str_Comm_Parm *pStr_Comm_Parm_Address, Str_Comm_698_RW *pV_698RWPara, uchar8 *P_Data)
�����������Զ�ȡ���ݽ��б���
��������������ݴ��pV_698Frame->Data,������д���ݽ�����pV_698RWPara->Wt_OI
�����������������ݴ��ͨ���շ�����
���ز��������ذ�ȫȨ���Ƿ�����Ҫ��C_OK��ʾ����Ȩ��Ҫ��
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_GetAPDU_Encode(Str_Comm_Parm *pStr_Comm_Parm_Address, Str_Comm_698_RW *pV_698RWPara, uchar8 *P_Data)
{
	ushort16	i, j;
	ushort16	V_DataOff, V_LenTemp;
	ushort16	V_DataListOffset, V_FrameDataLen = 0;
	uchar8		V_ucRecordNUMFlag;
	ushort16	V_DATALen;
	uchar8		V_ArrNum;

	CommAPDUBuf[CommAPDUOffset] = (pV_698RWPara->ServiceFlag_First)|0x80;
	CommAPDUOffset++;
	CommAPDULen++;

	if(pV_698RWPara->FrameNUM  !=0)
	{
		CommAPDUBuf[CommAPDUOffset] = C_GETNext_Request;								/*����Ӧ��*/
		if(pV_698RWPara->FrameNUM == 1)
		{
			pV_698RWPara->LastServiceFlag_Second = pV_698RWPara->ServiceFlag_Second;	/*������һ֡2������*/
		}
	}
	else
	{
		CommAPDUBuf[CommAPDUOffset] = pV_698RWPara->ServiceFlag_Second;
	}

	CommAPDUOffset++;
	CommAPDULen++;
	CommAPDUBuf[CommAPDUOffset] = pV_698RWPara->PIID;									/*PIID*/
	CommAPDUOffset++;
	CommAPDULen++;

	if(pV_698RWPara->FrameNUM != 0)
	{/*���ﲻ����û�к������Ȱ����к���ģʽ���б���*/
		CommAPDUBuf[CommAPDUOffset] = pV_698RWPara->EndFrame;							/*����ĩ֡��־*/
		CommAPDUOffset++;
		CommAPDULen++;
		CommAPDUBuf[CommAPDUOffset] = (pV_698RWPara->FrameNUM)>>8;						/*֡��Ÿ��ֽ�*/
		CommAPDUOffset++;
		CommAPDULen++;
		CommAPDUBuf[CommAPDUOffset] = pV_698RWPara->FrameNUM;							/*֡���*/
		CommAPDUOffset++;
		CommAPDULen++;

		if(pV_698RWPara->firstRNSICBit != pV_698RWPara->lastRNSICBit)
		{
			CommAPDUBuf[CommAPDUOffset] = 0;
			CommAPDUOffset++;
			CommAPDULen++;
			CommAPDUBuf[CommAPDUOffset] = C_SCMismatch_DAR;
			CommAPDUOffset++;
			CommAPDULen++;
			pV_698RWPara->Next_OINO = 0;												/*��һ֡����֡���*/
			pV_698RWPara->Current_FrameNO = 0;											/*��ǰ֡���*/
			pV_698RWPara->ResponedNum = 0;
			pV_698RWPara->ResponedRelationNum = 0;
			pV_698RWPara->EndFrame =0;
			pV_698RWPara->FrameNUM = 0;
			pV_698RWPara->LastServiceFlag_Second = 0;									/*������֡ʱ����һ֡2�����󱣴�*/
			pV_698RWPara->CurrentOADEnd = 0;
			return C_OK;
		}

		if( (pV_698RWPara->LastServiceFlag_Second == C_GETNormal_Request)
			||(pV_698RWPara->LastServiceFlag_Second == C_GETNormalList_Request) )
		{
			CommAPDUBuf[CommAPDUOffset] = 1;
			CommAPDUOffset++;
			CommAPDULen++;
		}
		else if( (pV_698RWPara->LastServiceFlag_Second == C_GETRecord_Request)
			||(pV_698RWPara->LastServiceFlag_Second == C_GETRecordList_Request) )
		{
			CommAPDUBuf[CommAPDUOffset] = 2;
			CommAPDUOffset++;
			CommAPDULen++;
		}

		pV_698RWPara->ServiceFlag_Second = C_GETNext_Request;
	}

	switch(pV_698RWPara->ServiceFlag_Second)
	{
		case C_GETNext_Request:
		{
			if( (pV_698RWPara->LastServiceFlag_Second == C_GETNormal_Request)
				||(pV_698RWPara->LastServiceFlag_Second == C_GETNormalList_Request) )
			{
				goto GETNormalFlag;
			}
			else																		/*����¼������*/
			{
				goto GETRecordFlag;
			}
		}
		case C_GETNormal_Request:
		case C_GETNormalList_Request:
GETNormalFlag:
		{
			V_DataOff = 0;

			if( (pV_698RWPara->ServiceFlag_Second == C_GETNormalList_Request)			/*��ȡ���OAD����OAD�������б���*/
				||(pV_698RWPara->ServiceFlag_Second == C_GETNext_Request)
				||(pV_698RWPara->FrameNUM != 0) )
			{
				V_DataListOffset = CommAPDUOffset;
				CommAPDUBuf[CommAPDUOffset] = pV_698RWPara->ResponedNum - pV_698RWPara->HaveEncodeNum;
				CommAPDUOffset++;
				CommAPDULen++;
			}

			if(pV_698RWPara->ServiceFlag_Second != C_GETNext_Request)
			{
				pV_698RWPara->HaveEncodeNum= 0;
			}

			for(i = pV_698RWPara->HaveEncodeNum; i < pV_698RWPara->ResponedNum; i ++)
			{
				/*******************�Զ�ȡ���ݶ������Ա�ʶ���б���**************/
				PF_Ulong32ToBuffer4_698(&CommAPDUBuf[CommAPDUOffset], &pV_698RWPara->Rd_OI[i].RdOI.OAD, 4);
				CommAPDUOffset += 4;
				CommAPDULen += 4;
				V_FrameDataLen += 4;
				/*******************�Զ�ȡ���ݽ��б���**************************/
				if(pV_698RWPara->Rd_OI[i].Rd_Result == C_OK)
				{
					ushort16 V_DataLen;
					uchar8 V_Offset;

					V_DataLen = SF_GetLengthFieldLen(&P_Data[V_DataOff],&V_Offset);
					/*�ڶ����ݱ�������ȷ�����������ݱ���󲻻ᳬ����Χ*/
					if( (CommAPDUOffset + V_DataLen - 14) < C_FrameMaxLen_698 )
					{
						CommAPDUBuf[CommAPDUOffset] = C_GetResponseOK;
						CommAPDUOffset++;
						CommAPDULen++;
						CommAPDUBuf[CommAPDUOffset] = pV_698RWPara->Rd_OI[i].RdOI.DataType;
						CommAPDUOffset++;
						CommAPDULen++;

						if( (pV_698RWPara->Rd_OI[i].RdOI.DataType == C_array)
							||(pV_698RWPara->Rd_OI[i].RdOI.DataType == C_bit_string)
							||(pV_698RWPara->Rd_OI[i].RdOI.DataType == C_visible_string)
							||(pV_698RWPara->Rd_OI[i].RdOI.DataType == C_structure) )
						{
							V_LenTemp = SF_DataLen_AXDR_Encode(&CommAPDUBuf[CommAPDUOffset], pV_698RWPara->Rd_OI[pV_698RWPara->HaveEncodeNum].RdOI.CarryNum);
							CommAPDUOffset += V_LenTemp;
							CommAPDULen += V_LenTemp;
                            if(pV_698RWPara->Rd_OI[pV_698RWPara->HaveEncodeNum].RdOI.CarryNum == 0)
                            {
                                V_DataOff += (V_DataLen + V_Offset);
                                pV_698RWPara->HaveEncodeNum++;
                                continue;
                            }
						}

						if(pV_698RWPara->Rd_OI[i].RdOI.DataType == C_octet_string)	/*�Գ��Ƚ��б���*/
						{
							CommAPDUBuf[CommAPDUOffset] = P_Data[V_DataOff];
							CommAPDUOffset++;
							CommAPDULen++;
						}

						if( ( (pV_698RWPara->Rd_OI[i].RdOI.OAD == 0x30000D03)
							|| (pV_698RWPara->Rd_OI[i].RdOI.OAD == 0x30000D04) )
						 && ( V_DataLen == 1) )
						{
							CommAPDUOffset--;
							PF_CopyDataBytes_698(&P_Data[V_DataOff+V_Offset], &CommAPDUBuf[CommAPDUOffset], V_DataLen);
						}
						else
						{
							PF_CopyDataBytes_698(&P_Data[V_DataOff+V_Offset], &CommAPDUBuf[CommAPDUOffset], V_DataLen);
						}

						CommAPDUOffset += V_DataLen;
						CommAPDULen += V_DataLen;
						V_DataOff += (V_DataLen + V_Offset);

						if( ( (pV_698RWPara->Rd_OI[i].RdOI.OAD&0xFFFFFF00) == 0x33200200 )
							&& (pV_698RWPara->Rd_OI[i].RdOI.OAD != 0x33200200) )
						{
							if(V_DataLen == 0x00)
							{
								CommAPDUBuf[CommAPDUOffset - 1] = 0x00;
							}
						}
						if( (pV_698RWPara->FrameNUM != 0)
							&& (pV_698RWPara->Rd_OI[pV_698RWPara->HaveEncodeNum].RdOI.CurrentFrameNum != 0) )	/*һ����ʶ��û�б��꣬����һ��APDU*/
						{
						}
						else
						{
							pV_698RWPara->HaveEncodeNum ++;		/*���Ǻ���֡���ò���*/
						}
					}
					else										/*���򲻻���������*/
					{
						CommAPDUOffset -= 4;
						CommAPDULen -= 4;
						CommAPDUBuf[V_DataListOffset] = i;
#if 0
						CommAPDUBuf[CommAPDUOffset] = C_NULL;
						CommAPDUOffset++;
						CommAPDULen++;
						CommAPDUBuf[V_DataListOffset] = i+1;
#endif
						break;
					}

					if( pV_698RWPara->Next_OINO != (pV_698RWPara->Current_FrameNO) )
					{
						break;
					}
				}
				else
				{
					CommAPDUBuf[CommAPDUOffset] = C_GetResponseERR;
					CommAPDUOffset++;
					CommAPDUBuf[CommAPDUOffset] = pV_698RWPara->Rd_OI[i].Rd_Result;
					CommAPDUOffset++;
					CommAPDULen += 2;
                    pV_698RWPara->HaveEncodeNum++;
				}
			}
		}break;
		case C_GETRecord_Request:
		case C_GETRecordList_Request:
GETRecordFlag:
		{
			V_DataOff = 0;

			if( (pV_698RWPara->ServiceFlag_Second == C_GETRecordList_Request)		/*��ȡ���record*/
				||(pV_698RWPara->ServiceFlag_Second == C_GETNext_Request)
				||(pV_698RWPara->FrameNUM != 0) )
			{
				V_DataListOffset = CommAPDUOffset;
				CommAPDUBuf[CommAPDUOffset] = pV_698RWPara->ResponedNum - pV_698RWPara->HaveEncodeNum;
				CommAPDUOffset++;
				CommAPDULen++;
			}

			if(pV_698RWPara->ServiceFlag_Second != C_GETNext_Request)
			{
				pV_698RWPara->HaveEncodeNum = 0;
			}

			for(i = pV_698RWPara->HaveEncodeNum; i < pV_698RWPara->ResponedNum; i ++)
			{
				V_FrameDataLen = CommAPDUOffset;									/*��¼������¼��APDU�е���ʼƫ�Ƶ�ַ*/
				V_ucRecordNUMFlag = 0;
				if( (CommAPDUOffset +4-14) > (C_Comm_Data_MaxLen_698 - 9) )
				{
					break;
				}
				/*******************�Զ�ȡ���ݶ������Ա�ʶ���б���**************/
				PF_Ulong32ToBuffer4_698(&CommAPDUBuf[CommAPDUOffset], &pV_698RWPara->Rd_OI[i].RdOI.OAD, 4);
				CommAPDUOffset += 4;
				CommAPDULen += 4;
				/*******************RCSD�������������б���б���****************/
				if(pV_698RWPara->Rd_OI[i].Rd_Result != C_RWForbid_DAR)
				{
					if(pV_698RWPara->Rd_OI[i].Rd_RecordRelatedOINum != 0)
					{
						if( (CommAPDUOffset + pV_698RWPara->Rd_OI[i].Rd_RecordRelatedOINum * 5 + 1 - 14) > (C_Comm_Data_MaxLen_698 - 9) )
						{
							CommAPDULen -= (CommAPDUOffset - V_FrameDataLen);
							CommAPDUOffset = V_FrameDataLen;											/*��ԭ������¼����ǰƫ��*/
							break;
						}

						CommAPDUBuf[CommAPDUOffset] = pV_698RWPara->Rd_OI[i].Rd_RecordRelatedOINum;		/*���������б����*/
						CommAPDUOffset ++;
						CommAPDULen ++;

						for(j = 0; j < pV_698RWPara->Rd_OI[i].Rd_RecordRelatedOINum; j ++)
						{
							CommAPDUBuf[CommAPDUOffset] = 0;											/*������������*/
							CommAPDUOffset++;
							PF_Ulong32ToBuffer4_698(&CommAPDUBuf[CommAPDUOffset], &pV_698RWPara->Rd_OI[i].Rd_RecordRelatedOI[j], 4);
							CommAPDUOffset += 4;
							CommAPDULen += 5;
						}
					}
					else
					{
						if( (pV_698RWPara->Rd_OI[i].RdOI.OAD&0xFF000000) == 0x50000000 )
						{
							V_DATALen = 0;

	                        if( ( C_Comm_Data_MaxLen_698 - 9 ) > ( CommAPDUOffset - 14 ) )
	                        {
	                            V_DATALen =  ( C_Comm_Data_MaxLen_698 - 9 ) - (CommAPDUOffset - 14 );
	                        }

							if( SF_FreezeOADRead(pV_698RWPara->Rd_OI[i], &CommAPDUBuf[CommAPDUOffset], &V_DATALen, 1, &V_ArrNum) != C_OK )
							{
                                V_DATALen = 0;
                            }

                            if(V_DATALen == 0)
                            {
                                V_DATALen = 1;
                            }

                            if( ( CommAPDUOffset + V_DATALen - 14 ) > ( C_Comm_Data_MaxLen_698 - 9 ) )
                            {
                                CommAPDULen -= (CommAPDUOffset - V_FrameDataLen);
                                CommAPDUOffset = V_FrameDataLen;										/*��ԭ������¼����ǰƫ��*/
                                break;
                            }

                            if(V_DATALen == 1)
                            {
                                CommAPDUBuf[CommAPDUOffset] = 0;
                                pV_698RWPara->Rd_OI[i].Rd_Result = C_OverStep_DAR;
                            }

                            CommAPDUOffset += V_DATALen;
                            CommAPDULen += V_DATALen;
						}
						else
						{
                        	V_DATALen = 0;

							if( ( C_Comm_Data_MaxLen_698 - 9 ) > CommAPDUOffset )
                            {
                                V_DATALen = ( ( C_Comm_Data_MaxLen_698 - 9 ) - CommAPDUOffset );
                            }

							if(SF_EventOADRead(pV_698RWPara->Rd_OI[i],&CommAPDUBuf[CommAPDUOffset],&V_DATALen,1,&V_ArrNum) != C_OK)
                            {
                                V_DATALen = 0;
                            }

                            if(V_DATALen == 0)
                            {
                                V_DATALen = 1;
                            }

                            if ( ( CommAPDUOffset + V_DATALen - 14 ) > ( C_Comm_Data_MaxLen_698 - 9 ) )
                            {
                                CommAPDULen -= (CommAPDUOffset - V_FrameDataLen);
                                CommAPDUOffset = V_FrameDataLen;			/*��ԭ������¼����ǰƫ��*/
                                break;
                            }

                            if(V_DATALen == 1)
                            {
                                CommAPDUBuf[CommAPDUOffset] = 0;
                                pV_698RWPara->Rd_OI[i].Rd_Result = C_OverStep_DAR;
                            }

							CommAPDUOffset += V_DATALen;
							CommAPDULen += V_DATALen;
						}
					}
					V_FrameDataLen = CommAPDUOffset;						/*������������б��ƫ��*/
				}
				else
				{
					CommAPDUBuf[CommAPDUOffset] = 0;						/*������������*/
					CommAPDUOffset++;
					CommAPDULen++;
				}

				pV_698RWPara->ResponedRelationNum = 0;

				if(pV_698RWPara->Rd_OI[i].Rd_Result == C_OK)
				{
					/*******************��ȡ���ݽ��б���***********************/
					CommAPDUBuf[CommAPDUOffset] = 0x01;							/*�Խ��ѡ����б���*/
					CommAPDUOffset ++;
					CommAPDULen ++;

					ushort16	V_DataLen;
					uchar8		V_LengthLen;

					V_DataLen = SF_GetLengthFieldLen(&P_Data[V_DataOff], &V_LengthLen);

					if( (CommAPDUOffset + V_DataLen-14) > (C_Comm_Data_MaxLen_698 - 9) )
					{
						CommAPDULen -= (CommAPDUOffset - V_FrameDataLen);
						CommAPDUOffset = V_FrameDataLen;								/*��ԭ������¼����ǰƫ��*/
						CommAPDUBuf[CommAPDUOffset] = 0x00;								/*���ݷŲ���*/
						CommAPDUOffset++;
						CommAPDUBuf[CommAPDUOffset] = C_OverStep_DAR;					/*Խ��*/
						CommAPDUOffset++;
						CommAPDULen += 2;
						V_ucRecordNUMFlag = 1;
						break;
					}

					V_DataOff += V_LengthLen;

					if(P_Data[V_DataOff-V_LengthLen] != 0)								/*��ʾ��ȡ�����¼���¼,���ǿ�*/
					{
						if( ((pV_698RWPara->Rd_OI[i].RdOI.OAD&0xFF000000) != 0x50000000)
							&&((pV_698RWPara->Rd_OI[i].RdOI.OAD&0xFF000000) != 0x30000000) )	/*�����¼�ļ�¼�����ڶ��������Ѿ����룬������֧�ּ��ϻ���structOAD��record��*/
						{
							CommAPDUBuf[CommAPDUOffset] = 1;							/*��¼�������б���*/
							CommAPDUOffset++;
							CommAPDULen++;
						}

						if( (CommAPDUOffset + V_DataLen) < C_FrameMaxLen_698 )			/*ȷ��������ܳ�*/
						{
							PF_CopyDataBytes_698(&P_Data[V_DataOff], &CommAPDUBuf[CommAPDUOffset], V_DataLen);
							CommAPDUOffset += V_DataLen;
							CommAPDULen += V_DataLen;
							V_DataOff += V_DataLen;
							pV_698RWPara->ResponedRelationNum++;
						}
						else
						{
							pV_698RWPara->Next_OINO = (pV_698RWPara->Current_FrameNO) + 1;
							break;
						}
					}
					else
					{
						CommAPDUBuf[CommAPDUOffset] = 0;								/*�Խ��ѡ����б���*/
						CommAPDUOffset++;
						CommAPDULen++;
					}

					if(pV_698RWPara->HaveEncodeNum == (pV_698RWPara->ResponedNum-1))	/*�к���֡(��ʱ������recordlist���)*/
					{
						if(pV_698RWPara->CurrentOADEnd != 0x0f)
						{
							pV_698RWPara->HaveEncodeNum++;
						}
					}
					else
					{
						pV_698RWPara->HaveEncodeNum++;
					}
				}
				else
				{
					CommAPDUBuf[CommAPDUOffset] = C_GetResponseERR;
					CommAPDUOffset++;
					CommAPDUBuf[CommAPDUOffset] = pV_698RWPara->Rd_OI[i].Rd_Result;
					CommAPDUOffset++;
					CommAPDULen += 2;
				}
			}

			if((pV_698RWPara->ServiceFlag_Second == C_GETRecordList_Request))			/*��ȡ���record*/
			{
				CommAPDUBuf[V_DataListOffset] = i + V_ucRecordNUMFlag;
			}

			if(pV_698RWPara->Next_OINO == (pV_698RWPara->Current_FrameNO))
			{
				pV_698RWPara->Next_OINO = 0;
			}
		}break;
		default:
		{
			return C_ForbidenRW;	/*�������Ͳ��ԣ�Ӧ��ܾ���д*/
		}break;
	}
	return C_OK;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_SetAPDU_Encode(Str_Comm_Parm * pStr_Comm_Parm_Address,Str_Comm_698_RW *pV_698RWPara,uchar8 *P_Data)
���������������ý�����б���
��������������ݴ��pV_698Frame->Data,������д���ݽ�����pV_698RWPara->Wt_OI
���������	��������ݴ��ͨ���շ�����
���ز��������ذ�ȫȨ���Ƿ�����Ҫ��C_OK��ʾ����Ȩ��Ҫ��
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_SetAPDU_Encode(Str_Comm_Parm * pStr_Comm_Parm_Address, Str_Comm_698_RW *pV_698RWPara, uchar8 *P_Data)
{
	uchar8		i;
	ushort16	V_DataOff;

	CommAPDUBuf[CommAPDUOffset] = (pV_698RWPara->ServiceFlag_First) | 0x80;
	CommAPDUOffset++;
	CommAPDUBuf[CommAPDUOffset] = pV_698RWPara->ServiceFlag_Second;
	CommAPDUOffset++;
	CommAPDUBuf[CommAPDUOffset] = pV_698RWPara->PIID;
	CommAPDUOffset++;
	CommAPDULen += 3;
	switch(pV_698RWPara->ServiceFlag_Second)
	{
		case C_SETNormal_Request:
		case C_SETNormalList_Request:
		case C_SETGETNormalList_Request:
			V_DataOff = 0;
			if(C_SETNormal_Request != pV_698RWPara->ServiceFlag_Second)
			{
				CommAPDUBuf[CommAPDUOffset] = pV_698RWPara->RWOI_Num;
				CommAPDUOffset++;
				CommAPDULen += 1;
			}

			pV_698RWPara->ResponedNum = 0;
			pV_698RWPara->HaveEncodeNum = 0;
			for( i = 0; i < pV_698RWPara->RWOI_Num; i++ )
			{
				if(pV_698RWPara->ServiceFlag_First == C_SET_Request)
				{
	                if(pV_698RWPara->Wt_OI[i].WtOI == CComm_Address)
	                {
	                    if(pV_698RWPara->Wt_OI[i].Wt_Result == C_OK)
	                    {
		                    uchar8 k;

		                    for( k = 0; k < pV_698RWPara->Wt_OI[i].DataLen; k++ )
		                    {
		                        CommAPDUBuf[9 + k] = pV_698RWPara->Wt_OI[i].Wt_Data[k];
		                    }
		                    InF_Get_Comm_Address(SV_Comm_Address, 0x00);		/*����ͨ���е�ͨ�ŵ�ַ*/
		                }
	                }
			/*******************���������ݶ������Ա�ʶ���б���*********************/
					PF_Ulong32ToBuffer4_698(&CommAPDUBuf[CommAPDUOffset], &pV_698RWPara->Wt_OI[i].WtOI, 4);
					CommAPDUOffset += 4;
			/*******************�����ý�����б���*********************/
					CommAPDUBuf[CommAPDUOffset] = pV_698RWPara->Wt_OI[i].Wt_Result;
					CommAPDUOffset++;
					CommAPDULen += 5;
				}
				else
				{
			/*******************���������ݶ������Ա�ʶ���б���*********************/
					uchar8 V_data[500];

					PF_CopyDataBytes_698(pV_698RWPara->Wt_OI[i].Wt_Data, V_data, pV_698RWPara->Wt_OI[i].DataLen);

					PF_Ulong32ToBuffer4_698(&CommAPDUBuf[CommAPDUOffset], &pV_698RWPara->Wt_OI[i].WtOI, 4);
					CommAPDUOffset += 4;
					CommAPDULen += 4;
					if( pV_698RWPara->Wt_OI[i].DataLen != 0 )					/*������Ϊ��ȡESAM����*/
					{

						CommAPDUBuf[CommAPDUOffset] = pV_698RWPara->Wt_OI[i].Wt_Result;
						CommAPDUOffset++;
						CommAPDUBuf[CommAPDUOffset] = 1;						/*��ʾ�з�������*/
						CommAPDUOffset++;
						PF_CopyDataBytes_698(V_data, &CommAPDUBuf[CommAPDUOffset], pV_698RWPara->Wt_OI[i].DataLen);

						CommAPDUOffset += pV_698RWPara->Wt_OI[i].DataLen;
						CommAPDULen += (2 + pV_698RWPara->Wt_OI[i].DataLen);
					}
					else
					{
			/*******************�����ý�����б���*********************/

						CommAPDUBuf[CommAPDUOffset] = pV_698RWPara->Wt_OI[i].Wt_Result;
						CommAPDUOffset++;
						CommAPDUBuf[CommAPDUOffset] = 0; 						/*��ʾû�з�������*/
						CommAPDUOffset++;
						CommAPDULen += 2;
					}
				}
				if(C_SETGETNormalList_Request != pV_698RWPara->ServiceFlag_Second)
				{
					pV_698RWPara->ResponedNum++;
					pV_698RWPara->HaveEncodeNum++;
					continue;
				}
		/*******************�Զ�ȡ���ݶ������Ա�ʶ���б���*********************/
				PF_Ulong32ToBuffer4_698(&CommAPDUBuf[CommAPDUOffset], &pV_698RWPara->Rd_OI[i].RdOI.OAD, 4);
				CommAPDUOffset += 4;
				CommAPDULen += 4;
				if(pV_698RWPara->Rd_OI[i].Rd_Result == C_OK)
				{
					ushort16 V_DataLen;
					uchar8 V_Offset;

					V_DataLen = SF_GetLengthFieldLen(&P_Data[V_DataOff], &V_Offset);
					if( ( CommAPDUOffset + P_Data[V_DataOff] ) <C_FrameMaxLen )
					{
						CommAPDUBuf[CommAPDUOffset] = C_GetResponseOK;
						CommAPDUOffset++;
						CommAPDUBuf[CommAPDUOffset] = pV_698RWPara->Rd_OI[i].RdOI.DataType;
						CommAPDUOffset++;
						CommAPDULen += 2;
						if( ( pV_698RWPara->Rd_OI[i].RdOI.DataType == C_array )
						 || ( pV_698RWPara->Rd_OI[i].RdOI.DataType == C_bit_string )
						 || ( pV_698RWPara->Rd_OI[i].RdOI.DataType == C_visible_string )
						 || ( pV_698RWPara->Rd_OI[i].RdOI.DataType == C_structure ) )
						{
							CommAPDUBuf[CommAPDUOffset] = pV_698RWPara->Rd_OI[i].RdOI.CarryNum;
							if( ( CommAPDUBuf[CommAPDUOffset] == 0x80 )
							 && ( pV_698RWPara->Rd_OI[i].RdOI.DataType == C_bit_string ) )
							{
								CommAPDUBuf[CommAPDUOffset] = 0x81;
								CommAPDUOffset++;
								CommAPDULen += 1;
								CommAPDUBuf[CommAPDUOffset] = 0x80;
							}
							CommAPDUOffset++;
							CommAPDULen += 1;
							if( pV_698RWPara->Rd_OI[i].RdOI.CarryNum == 0 )
							{
								V_DataOff += (V_DataLen + V_Offset);
								pV_698RWPara->HaveEncodeNum++;
								continue;
							}
						}
						if( pV_698RWPara->Rd_OI[i].RdOI.DataType == C_octet_string )	/*�Գ��Ƚ��б���*/
						{
							CommAPDUBuf[CommAPDUOffset] = P_Data[V_DataOff];
							CommAPDUOffset++;
							CommAPDULen += 1;
						}
						PF_CopyDataBytes_698(&P_Data[V_DataOff + V_Offset], &CommAPDUBuf[CommAPDUOffset], V_DataLen);
						CommAPDUOffset += V_DataLen;
						CommAPDULen += V_DataLen;
						V_DataOff += (V_DataLen + V_Offset);
						pV_698RWPara->ResponedNum++;
						pV_698RWPara->HaveEncodeNum++;
					}
					else
					{
						pV_698RWPara->Next_OINO = (pV_698RWPara->Current_FrameNO) + 1;
						break;
					}
					if(pV_698RWPara->Next_OINO != (pV_698RWPara->Current_FrameNO))
					{
						break;
					}
				}
				else
				{
					CommAPDUBuf[CommAPDUOffset] = C_GetResponseERR;
					CommAPDUOffset++;
					CommAPDUBuf[CommAPDUOffset] = pV_698RWPara->Rd_OI[i].Rd_Result;
					CommAPDUOffset++;
					CommAPDULen += 2;
				}
			}
			pV_698RWPara->Next_OINO = 0;
			break;

		default:
			return C_ForbidenRW;		/*�������Ͳ��ԣ�Ӧ��ܾ���д*/
			break;
	}
	return C_OK;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_ActionAPDU_Encode(Str_Comm_Parm * pV_698Frame,Str_Comm_698_RW *pV_698RWPara,uchar8 *P_Data)
�����������Բ���������б���
��������������ݴ��pV_698Frame->Data,������д���ݽ�����pV_698RWPara->Wt_OI
�����������������ݴ��ͨ���շ�����
���ز��������ذ�ȫȨ���Ƿ�����Ҫ��C_OK��ʾ����Ȩ��Ҫ��
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_ActionAPDU_Encode(Str_Comm_Parm * pV_698Frame, Str_Comm_698_RW *pV_698RWPara, uchar8 *P_Data)
{
	uchar8		i;
	ushort16	V_DataOff;

	pV_698Frame->Buff[pV_698Frame->Offset] = (pV_698RWPara->ServiceFlag_First) | 0x80;
	pV_698Frame->Offset++;
	pV_698Frame->Buff[pV_698Frame->Offset] = pV_698RWPara->ServiceFlag_Second;
	pV_698Frame->Offset++;
	pV_698Frame->Buff[pV_698Frame->Offset] = pV_698RWPara->PIID;
	pV_698Frame->Offset++;
	switch(pV_698RWPara->ServiceFlag_Second)
	{
		case C_ACTIONNormal_Request:
		case C_ACTIONNormalList_Request:
		case C_ACTIONGETList_Request:
			V_DataOff = 0;
			if( ( pV_698RWPara->ServiceFlag_Second == C_ACTIONNormalList_Request ) || ( pV_698RWPara->ServiceFlag_Second == C_ACTIONGETList_Request ) )		/*��ȡ���OAD����OAD�������б���*/
			{
				pV_698Frame->Buff[pV_698Frame->Offset] = pV_698RWPara->RWOI_Num;
				pV_698Frame->Offset++;
			}
			pV_698RWPara->ResponedNum = 0;
			pV_698RWPara->HaveEncodeNum = 0;
			for( i = 0; i < pV_698RWPara->RWOI_Num; i++ )
			{
		/*******************���������ݶ������Ա�ʶ���б���*********************/
				uchar8 V_data[500];

				PF_CopyDataBytes_698(pV_698RWPara->Wt_OI[i].Wt_Data, V_data, pV_698RWPara->Wt_OI[i].DataLen);

				PF_Ulong32ToBuffer4_698(&pV_698Frame->Buff[pV_698Frame->Offset], &pV_698RWPara->Wt_OI[i].WtOI, 4);
				pV_698Frame->Offset += 4;
				if(pV_698RWPara->Wt_OI[i].DataLen != 0)				/*������Ϊ��ȡESAM����*/
				{
					pV_698Frame->Buff[pV_698Frame->Offset] = pV_698RWPara->Wt_OI[i].Wt_Result;
					pV_698Frame->Offset++;
					pV_698Frame->Buff[pV_698Frame->Offset] = 1; 	/*��ʾ�з�������*/
					pV_698Frame->Offset++;
					PF_CopyDataBytes_698(V_data, &pV_698Frame->Buff[pV_698Frame->Offset], pV_698RWPara->Wt_OI[i].DataLen);

					pV_698Frame->Offset += pV_698RWPara->Wt_OI[i].DataLen;
				}
				else
				{
		/*******************�����ý�����б���*********************/
					pV_698Frame->Buff[pV_698Frame->Offset] = pV_698RWPara->Wt_OI[i].Wt_Result;
					pV_698Frame->Offset++;
					pV_698Frame->Buff[pV_698Frame->Offset] = 0; 	/*��ʾû�з�������*/
					pV_698Frame->Offset++;
				}
				if(C_ACTIONGETList_Request != pV_698RWPara->ServiceFlag_Second)
				{
					pV_698RWPara->ResponedNum++;
					pV_698RWPara->HaveEncodeNum++;
					continue;
				}
		/*******************�Զ�ȡ���ݶ������Ա�ʶ���б���*********************/
				PF_Ulong32ToBuffer4_698(&pV_698Frame->Buff[pV_698Frame->Offset], &pV_698RWPara->Rd_OI[i].RdOI.OAD, 4);
				pV_698Frame->Offset += 4;
				if(pV_698RWPara->Rd_OI[i].Rd_Result == C_OK)
				{
					ushort16 V_DataLen;
					uchar8 V_Offset;

					V_DataLen = SF_GetLengthFieldLen(&P_Data[V_DataOff], &V_Offset);

					if( ( pV_698Frame->Offset + P_Data[V_DataOff] ) <C_FrameMaxLen )
					{
						pV_698Frame->Buff[pV_698Frame->Offset] = C_GetResponseOK;
						pV_698Frame->Offset++;
						pV_698Frame->Buff[pV_698Frame->Offset] = pV_698RWPara->Rd_OI[i].RdOI.DataType;
						pV_698Frame->Offset++;

						if( ( pV_698RWPara->Rd_OI[i].RdOI.DataType == C_array )
						 || ( pV_698RWPara->Rd_OI[i].RdOI.DataType == C_bit_string )
						 || ( pV_698RWPara->Rd_OI[i].RdOI.DataType == C_visible_string )
						 || ( pV_698RWPara->Rd_OI[i].RdOI.DataType == C_structure ) )
						{
							pV_698Frame->Buff[pV_698Frame->Offset] = pV_698RWPara->Rd_OI[i].RdOI.CarryNum;
							pV_698Frame->Offset++;
							if(pV_698RWPara->Rd_OI[i].RdOI.CarryNum == 0)
							{
								V_DataOff += (V_DataLen + V_Offset);
								pV_698RWPara->HaveEncodeNum++;
								continue;
							}
						}
						if(pV_698RWPara->Rd_OI[i].RdOI.DataType == C_octet_string)	/*�Գ��Ƚ��б���*/
						{
							pV_698Frame->Buff[pV_698Frame->Offset] = P_Data[V_DataOff];
							pV_698Frame->Offset++;
						}


						PF_CopyDataBytes_698(&P_Data[V_DataOff + V_Offset], &pV_698Frame->Buff[pV_698Frame->Offset], V_DataLen);
						pV_698Frame->Offset +=V_DataLen;
						V_DataOff += (V_DataLen + V_Offset);
						pV_698RWPara->ResponedNum++;
						pV_698RWPara->HaveEncodeNum++;
					}
					else
					{
						pV_698RWPara->Next_OINO = (pV_698RWPara->Current_FrameNO) + 1;
						break;
					}
					if(pV_698RWPara->Next_OINO != (pV_698RWPara->Current_FrameNO))
					{
						break;
					}
				}
				else
				{
					pV_698Frame->Buff[pV_698Frame->Offset] = C_GetResponseERR;
					pV_698Frame->Offset++;
					pV_698Frame->Buff[pV_698Frame->Offset] = pV_698RWPara->Rd_OI[i].Rd_Result;
					pV_698Frame->Offset++;
				}
			}
			pV_698RWPara->Next_OINO = 0;
			break;

		default:
			return C_ForbidenRW;		/*�������Ͳ��ԣ�Ӧ��ܾ���д*/
			break;
	}
	return C_OK;
}
/*******************************************************************************
����ԭ�ͣ�void SF_GetFactoryInfomation(uchar8 *P_Data,uchar8 V_GetFlag)
������������ȡ������Ϣ
���������P_Data������Ϣ��ŵ�ַ��V_GetFlagΪ��ȡ����
			V_GetFlag=0��ʾ������ţ�=1��ʾ��Ҫ��������
�����������������ݴ�ų�����Ϣ
���ز��������ذ�ȫȨ���Ƿ�����Ҫ��C_OK��ʾ����Ȩ��Ҫ��
����λ�ã�
��    ע��
*******************************************************************************/
void SF_GetFactoryInfomation(uchar8 *P_Data, uchar8 V_GetFlag)
{
	uchar8		V_LineNum = 0, V_DataOff = 0;
	ushort16	V_Len, V_usDataEncode;

	V_Len = CLFactory_Number;
	InF_Read_Data(CFactory_Number, &P_Data[V_DataOff], &V_Len, &V_usDataEncode);
	PF_OneDataReversed( &P_Data[V_DataOff],   &P_Data[V_DataOff], GV_Str_DI0_DataType_FactoryPaTable[V_LineNum].DataLen_698);
	V_DataOff += V_Len;
	V_LineNum++;

/**************����汾��0x04800001**************/
	V_Len = CLFactory_Softw_Version;
	InF_Read_Data(CFactory_Softw_Version, &P_Data[V_DataOff], &V_Len, &V_usDataEncode);
	PF_OneDataReversed( &P_Data[V_DataOff],   &P_Data[V_DataOff], GV_Str_DI0_DataType_FactoryPaTable[V_LineNum].DataLen_698);
	V_DataOff += V_Len;
	V_LineNum++;

/**************��������汾����**************/
	V_Len = CLFactory_Softw_VersionDate;
	InF_Read_Data(CFactory_Softw_VersionDate, &P_Data[V_DataOff], &V_Len, &V_usDataEncode);
	PF_OneDataReversed( &P_Data[V_DataOff],   &P_Data[V_DataOff], GV_Str_DI0_DataType_FactoryPaTable[V_LineNum].DataLen_698);
	V_DataOff += V_Len;
	V_LineNum++;
/**************Ӳ���汾��0x04800002**************/
	V_Len = CLFactory_Hardw_Version;
	InF_Read_Data(CFactory_Hardw_Version, &P_Data[V_DataOff], &V_Len, &V_usDataEncode);
	PF_OneDataReversed( &P_Data[V_DataOff],   &P_Data[V_DataOff], GV_Str_DI0_DataType_FactoryPaTable[V_LineNum].DataLen_698);
	V_DataOff += V_Len;
	V_LineNum++;

/**************Ӳ���汾����0x0400040C**************/
	V_Len = CLFactory_Hardw_VersionDate;
	InF_Read_Data(CFactory_Hardw_VersionDate, &P_Data[V_DataOff], &V_Len, &V_usDataEncode);
	PF_OneDataReversed( &P_Data[V_DataOff],   &P_Data[V_DataOff], GV_Str_DI0_DataType_FactoryPaTable[V_LineNum].DataLen_698);
	V_DataOff += V_Len;
	V_LineNum++;

/**************������չ��Ϣ0x04800004**************/
	V_Len = CLFactory_ExternSign;
	InF_Read_Data(CFactory_ExternSign, &P_Data[V_DataOff], &V_Len, &V_usDataEncode);
	PF_OneDataReversed( &P_Data[V_DataOff], &P_Data[V_DataOff], V_Len);
	V_DataOff += V_Len;
	V_LineNum++;
}
/*******************************************************************************
����ԭ�ͣ�uchar8	SF_ConectRequest_Encode(Str_Comm_Parm * pStr_Comm_Parm_Address,Str_Comm_698_RW *pV_698RWPara,uchar8 *P_Data)
����������Ӧ����������Ӧ�����
��������������ݴ��pV_698Frame->Data,������д���ݽ�����pV_698RWPara->Wt_OI
�����������������ݴ��ͨ���շ�����
���ز��������ذ�ȫȨ���Ƿ�����Ҫ��C_OK��ʾ����Ȩ��Ҫ��
����λ�ã�
��    ע��
*******************************************************************************/
uchar8	SF_ConectRequest_Encode(Str_Comm_Parm * pStr_Comm_Parm_Address, Str_Comm_698_RW *pV_698RWPara, uchar8 *P_Data)
{
/*******************�������ͱ���******************/
	CommAPDUBuf[CommAPDUOffset] = (pV_698RWPara->ServiceFlag_First) | 0x80;
	CommAPDUOffset++;
	CommAPDUBuf[CommAPDUOffset] = pV_698RWPara->PIID;
	CommAPDUOffset++;
	CommAPDULen += 2;
/*********************��ȡ������Ϣ********************/
	SF_GetFactoryInfomation(&CommAPDUBuf[CommAPDUOffset], 0);
	CommAPDUOffset += CLFactoryInfomation;
	CommAPDULen += CLFactoryInfomation;
/*********************Э��һ������Ϣ********************/
	CommAPDUBuf[CommAPDUOffset] = (uchar8)(Com_Conect.ProtocolVersion >> 8);
	CommAPDUOffset++;
	CommAPDUBuf[CommAPDUOffset] = (uchar8)(Com_Conect.ProtocolVersion);
	CommAPDUOffset++;
	CommAPDULen += 2;
	PF_CopyDataBytes(Com_Conect.ProtocolConformance, &CommAPDUBuf[CommAPDUOffset], C_ProtocolConformance_Len);
	CommAPDUOffset += C_ProtocolConformance_Len;
	PF_CopyDataBytes(Com_Conect.FunctionConformance, &CommAPDUBuf[CommAPDUOffset], C_FunctionConformance_Len);
	CommAPDUOffset += C_FunctionConformance_Len;
	CommAPDULen += C_ProtocolConformance_Len;
	CommAPDULen += C_FunctionConformance_Len;
	PF_Ushort16ToBuffer2_698(&CommAPDUBuf[CommAPDUOffset], &Com_Conect.ClientTxMaxLen);
	CommAPDUOffset += 2;

	PF_Ushort16ToBuffer2_698(&CommAPDUBuf[CommAPDUOffset], &Com_Conect.ClientRxMaxLen);
	CommAPDUOffset += 2;

	CommAPDUBuf[CommAPDUOffset] = (uchar8)(Com_Conect.ClientRxMaxLenNum);
	CommAPDUOffset++;

	PF_Ushort16ToBuffer2_698(&CommAPDUBuf[CommAPDUOffset], &Com_Conect.ClientAPDUMax);
	CommAPDUOffset += 2;

	if(SV_Comm_Parse_Local.ClientAddrFlag== Termal_Address)
	{
		PF_Ulong32ToBuffer4_698(&CommAPDUBuf[CommAPDUOffset], &Com_Conect.ConectOverTime_termal, 4);
	}
	else
	{
		PF_Ulong32ToBuffer4_698(&CommAPDUBuf[CommAPDUOffset], &Com_Conect.ConectOverTime, 4);
	}
	CommAPDUOffset += 4;
	CommAPDULen += 11;

	if( ( Com_Conect.ClientTxMaxLen < 40 )
	 || ( Com_Conect.ClientRxMaxLen < 40 ) )
	{
		pV_698RWPara->Wt_OI[0].Wt_Result = 0xFF;					/*��������*/
		Com_Conect.ClientTxMaxLen = C_ClientTxMaxLen;
		if(SV_Comm_Parse_Local.ClientAddrFlag == Termal_Address)	/*�ն�*/
		{
			Com_Conect.ConectOverTime_termal= 0;
		}
		else

		{
			Com_Conect.ConectOverTime = 0;
		}

        Com_Conect.CRC16 = PF_Cal_CRC((uchar8 *)&Com_Conect.ConectOverTime, C_ConectStruct_Len);		/*����Ӧ������ʱ��*/
	}
	CommAPDUBuf[CommAPDUOffset] = pV_698RWPara->Wt_OI[0].Wt_Result;										/*��֤���*/
	CommAPDUOffset++;
	CommAPDULen += 1;

	if(pV_698RWPara->Wt_OI[0].Wt_Result)
	{
		CommAPDUBuf[CommAPDUOffset] = 0;
		CommAPDUOffset++;
		CommAPDULen += 1;
	}
	else
	{
		if(Com_Conect.Com_Right != C_NullSecyrityConnect)
		{
			if(pV_698RWPara->Wt_OI[0].DataLen == 0)
			{
				CommAPDUBuf[CommAPDUOffset] = 0;
				CommAPDUOffset++;
				CommAPDULen += 1;
			}
			else
			{
				CommAPDUBuf[CommAPDUOffset] = 1;
				CommAPDUOffset++;
				CommAPDULen += 1;
				PF_CopyDataBytes_698(&P_Data[0], &CommAPDUBuf[CommAPDUOffset], pV_698RWPara->Wt_OI[0].DataLen);
				CommAPDUOffset += pV_698RWPara->Wt_OI[0].DataLen;
				CommAPDULen += pV_698RWPara->Wt_OI[0].DataLen;
			}
		}
        else
        {
            CommAPDUBuf[CommAPDUOffset] = 0;
            CommAPDUOffset++;
			CommAPDULen += 1;
        }
	}
	return C_OK;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_GetChannelVaild(uchar8 V_usChannel)
���������������ݽ��б���
��������������ݴ��pV_698Frame->Data,������д���ݽ�����pV_698RWPara->Wt_OI
�����������������ݴ��ͨ���շ�����
���ز��������ذ�ȫȨ���Ƿ�����Ҫ��C_OK��ʾ����Ȩ��Ҫ��
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_GetChannelVaild(uchar8 V_usChannel)
{
    uchar8      i, j, V_ChannelNum, k = 0, V_Flag = 0, V_ChannelNO[3] = {C_RS485_1, C_RS485_2, C_Module}, V_Temp[CLUpTellChannel] = {0};
    ulong32     V_Result = C_Error, V_OADBuf, V_OADTemp[3] = {0}, V_OAD[3] = {COne485_Baud, CTwo485_Baud, CModular_Baud};
	ushort16	V_ucLen = CLUpTellChannel, V_usDataEncode;

    V_Flag = InF_Read_Data(CUpTellChannel, V_Temp, &V_ucLen, &V_usDataEncode);
    V_ChannelNum = V_Temp[0];
    if(V_Flag == C_OK)
    {
        for( i = 0; i < V_ChannelNum; i++ )
        {
            PF_Buffer4ToUlong32(V_Temp + i * 4 + 1, &V_OADTemp[i], CL_OAD);
            for( j = 0; j < 3;j ++ )
            {
                V_OADBuf = V_OAD[j];
                if( ( V_Temp[i * 4 + 1] == 0 ) && ( V_Temp[i * 4 + 4] == 0xF2 ) )
                {
                    V_OADBuf = V_OAD[j] & 0xFFFFFFF0;
                }
                if(V_OADTemp[i] == V_OADBuf)
                {
                    if(V_usChannel == V_ChannelNO[j])
                    {
                        k++;
                        break;
                    }

                }
            }
        }
        if(k != 0)
        {
            V_Result = C_OK;
        }
    }
    return V_Result;
}
/*******************************************************************************
����ԭ�ͣ�void Inf_GetReportData(uchar8 *pReportBufStart,ushort16 *pReportLen,uchar8 CommChannelNo,uchar8 ReportType)
�����������Ը����ϱ����б���
���������pReportBufStart�����ϱ��׵�ַ,pReportLen�����ϱ����ȵ�ַ��CommChannelNoͨ��ͨ��
���������*pReportBufStart�����ϱ���Ϣ��*pReportLen�����ϱ�����
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
void Inf_GetReportData(uchar8 *pReportBufStart, ushort16 *pReportLen, uchar8 CommChannelNo, uchar8 ReportType)
{
    uchar8      V_Flag, V_NumPosition = 0, V_3320Program = 0x68, V_Buf[CLDrive_Report_State] = {0}, V_ReportNumByte = 0, V_Len = CLDrive_Report_State;
    ushort16    V_usLen = CLDrive_Report_State, V_usReportLen = 0, V_BufferLen1 = 1, V_usDataEncode;
    uchar8      V_Num, V_len = C_NewReportMaxNum, V_EventNo[C_NewReportMaxNum] = {0};
	ulong32 	V_OAD = C_OADError, V_DataTemp;
	uchar8      V_ChannelVaildFlag, V_FollowFlag = C_Error, V_AllowFollowTemp = 0;
    uchar8      i, V_RemainReportNO[C_NewReportMaxNum], V_RemainReportNum, V_ActiveReportMaxLen = C_REPORTListMaxLen;
    uchar8      V_Meter8ReportNo[CLMeterStatusNum], V_Meter8ReportNum = 0;

    if(ReportType == C_ActiveReportFlag)
    {
        V_FollowFlag = InF_Read_Data(CAllowAccordUpTell, &V_AllowFollowTemp, &V_BufferLen1, &V_usDataEncode);	/*�����ϱ�*/
        memset(V_RemainReportNO, 0x00, C_NewReportMaxNum);
    }
    else
    {
        V_FollowFlag = InF_Read_Data(CAllowFollowUpTell, &V_AllowFollowTemp, &V_BufferLen1, &V_usDataEncode);	/*�����ϱ�*/
    }

    V_ChannelVaildFlag = SF_GetChannelVaild(CommChannelNo);										/*����ϱ�ͨ��û�п��������ش���*/
	InF_GETListData(CommChannelNo, &V_Num, V_EventNo, V_len, V_RemainReportNO, &V_RemainReportNum, ReportType);
    V_Flag = Inf_GetMeter8(CommChannelNo, V_Buf, V_Len, ReportType, V_Meter8ReportNo, &V_Meter8ReportNum);
    if( ( V_FollowFlag != C_OK ) || ( V_AllowFollowTemp == 0 ) || ( V_ChannelVaildFlag != C_OK )
      || ( ( ReportType == C_NoActiveReportFlag ) && ( V_Num == 0 ) && ( V_Flag != C_FollowReportType ) )        /*�����ϱ�ʱ��3320Ϊ�գ�����2015Ϊ�ջ���Ϊ�����ϱ�*/
      || ( ( ReportType == C_ActiveReportFlag ) && ( ( V_Num == 0 ) || ( V_RemainReportNum == 0 ) ) && ( ( V_Flag != C_ActiveReportType ) || ( V_Meter8ReportNum == 0 ) ) ) )/*�Ƿ���������ϱ�*/
	{
		pReportBufStart[V_usReportLen] = 0;			/*���ϱ�*/
		V_usReportLen++;
	}
    else
	{
        if(ReportType == C_ActiveReportFlag)		/*�����ϱ�*/
        {
            pReportBufStart[V_usReportLen] = 1;		/*����1��*/
            V_ReportNumByte=V_usReportLen;
            V_usReportLen++;
        }
        else
        {
            pReportBufStart[V_usReportLen] = 1;		/*�����ϱ�*/
            V_usReportLen++;
            pReportBufStart[V_usReportLen] = 1;		/*�����ϱ�����1*/
            V_usReportLen++;
            pReportBufStart[V_usReportLen] = 1;		/*����1��*/
            V_ReportNumByte=V_usReportLen;
            V_usReportLen++;
        }

		if(ReportType == C_ActiveReportFlag) 		/*�����ϱ�*/
		{
            if( ( V_RemainReportNum != 0 ) || ( ( V_Num != 0 ) && ( V_Meter8ReportNum != 0 ) ) )	/*3320����Ҫ�ϱ��Ļ��ߣ�3320��Ϊ�ղ���Ҫ�ϱ�����2015��Ҫ�ϱ���*/
            {
                if(V_Meter8ReportNum != 0)
                {
                    V_ActiveReportMaxLen -= C_CodeOADlen;					/*���20150200��Ҫ�ϱ�����ô����ĳ���-5*/
                }
                for( i = 0; i < V_Num; i++ )
                {
                    V_OAD = InF_EventOADFind(V_EventNo[i]) & 0xFFFFFF00;	/*��ȡOAD,�����ĳ�00*/
                    if(V_OAD != C_OADError)
                    {
                        if(V_3320Program == 0x68)
                        {
                            V_DataTemp = 0x33200200;
                            PF_Ulong32ToBuffer4_698(&pReportBufStart[V_usReportLen], &V_DataTemp, 4);
                            V_usReportLen += 4;
                            V_ActiveReportMaxLen -= 4;
                            pReportBufStart[V_usReportLen] = 1;				/*DATA*/
                            V_usReportLen++;
                            V_ActiveReportMaxLen -= 1;
                            pReportBufStart[V_usReportLen] = 1;				/*array*/
                            V_usReportLen++;
                            V_ActiveReportMaxLen -= 1;
                            V_NumPosition = V_usReportLen;
                            pReportBufStart[V_NumPosition] = 1;				/*�ϱ�����++*/
                            V_usReportLen++;
                            V_ActiveReportMaxLen -= 1;

                            V_3320Program = 0x86;
                        }
                        else
                        {
                            pReportBufStart[V_NumPosition]++;				/*�ϱ�����++*/
                            V_3320Program = 0x86;
                        }

                        if( ( V_ActiveReportMaxLen / C_CodeOADlen ) > 0 )
                        {
                            pReportBufStart[V_usReportLen] = 0x51;			/*0AD*/
                            V_usReportLen++;
                            PF_Ulong32ToBuffer4_698(&pReportBufStart[V_usReportLen], &V_OAD, 4);	/*��һ��OAD�����ϱ�*/
                            V_usReportLen += 4;
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            }
        }
        else            /*�����ϱ�*/
        {
            if(V_Num != 0)
            {
                V_OAD = InF_EventOADFind(V_EventNo[0]) & 0xFFFFFF00;		/*��ȡOAD,�����ĳ�00*/
                if(V_OAD != C_OADError)
                {
                    V_DataTemp = 0x33200201;
                    PF_Ulong32ToBuffer4_698(&pReportBufStart[V_usReportLen], &V_DataTemp, 4);
                    V_usReportLen += 4;
                    pReportBufStart[V_usReportLen] = 1;						/*DATA*/
                    V_usReportLen++;
                    pReportBufStart[V_usReportLen] = 0x51;					/*0AD*/
                    V_usReportLen++;
                    PF_Ulong32ToBuffer4_698(&pReportBufStart[V_usReportLen], &V_OAD, 4);			/*��һ��OAD�����ϱ�*/
                    V_usReportLen = V_usReportLen + 4;
                }
            }
        }
        if(V_Flag != C_OtherErr_DAR)    /*����ֵ�������ϱ����߸����ϱ�*/
        {
            if( ( ( ( ( V_Meter8ReportNum != 0 ) && ( V_Num != 0 ) ) || ( V_RemainReportNum != 0 ) ) && ( ReportType == C_ActiveReportFlag ) )
			  || ( ( V_Num != 0 ) && ( ReportType == C_NoActiveReportFlag ) ) )
            {
                pReportBufStart[V_ReportNumByte]++;                     /*��������ϱ���3320���������ϱ�3320��2015����Ҫ�����ϱ�*/
            }
              V_DataTemp = 0x20150200;
              PF_Ulong32ToBuffer4_698(&pReportBufStart[V_usReportLen], &V_DataTemp, 4);
              V_usReportLen += 4;
              pReportBufStart[V_usReportLen] = 0x01;
              V_usReportLen++;
              pReportBufStart[V_usReportLen] = 0x04;
              V_usReportLen++;
              pReportBufStart[V_usReportLen] = 0x20;
              V_usReportLen++;
              PF_CopyDataBytes_698(V_Buf, &pReportBufStart[V_usReportLen], V_usLen);
              V_usReportLen = V_usReportLen + 4;
        }
	}
	*pReportLen = V_usReportLen;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_APDU_Encode(Str_Comm_645 * pV_698Frame,Str_Comm_698_RW *pV_698RWPara)
���������������ݽ��б���
��������������ݴ��pV_698Frame->Data,������д���ݽ�����pV_698RWPara->Wt_OI
�����������������ݴ��ͨ���շ�����
���ز��������ذ�ȫȨ���Ƿ�����Ҫ��C_OK��ʾ����Ȩ��Ҫ��
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_APDU_Encode(Str_Comm_645 * pV_698Frame, Str_Comm_698_RW *pV_698RWPara)
{
	Str_Comm_Parm *pStr_Comm_Parm_Address;
	ushort16	V_DataLen, i;
	uchar8		V_return, V_SecurityLenoff, V_First68Off = 4, V_DataOff;
    ushort16 	V_usTemp, V_usLen;

	/*��ȡͨ����ַ*/
	pStr_Comm_Parm_Address = Get_Str_Comm_Parm_Pointer(pV_698Frame->ChannelNo);
	if( pV_698Frame->C & 0x20 )										/*��֡�����־*/
	{
		goto	DerictorAnswerFlag;
	}
    CommAPDUOffset = 0;
    CommAPDULen = 0;
	memset(&CommAPDUBuf[CommAPDUOffset], 0xFE, 4);					/*ǰ���ֽ�FE*/
    CommAPDUOffset += 4;
    CommAPDUBuf[CommAPDUOffset] = 0x68;								/*��ʼ��68*/
    CommAPDUOffset++;
    CommAPDUBuf[CommAPDUOffset] = 0;								/*L_L*/
    CommAPDUOffset++;
    CommAPDUBuf[CommAPDUOffset] = 0;								/*L_H*/
    CommAPDUOffset++;
    CommAPDUBuf[CommAPDUOffset] = (0x80 | pV_698Frame->C);			/*������C*/
    CommAPDUOffset++;
    PF_CopyDataBytes(&CommBuff[4], &CommAPDUBuf[CommAPDUOffset], pV_698Frame->AddrLen + 4);	/*��ַ��֡ͷУ��*/
    CommAPDUOffset += (pV_698Frame->AddrLen + 4);					/*ƫ�Ƶ�ַ��HCS���һ���ֽ�*/
    for( i = 0; i < C_MaxReadListNum; i++ )
    {
        SF_GetErrorNo(&pV_698RWPara->Rd_OI[i].Rd_Result);
        SF_GetErrorNo(&pV_698RWPara->Wt_OI[i].Wt_Result);
    }
/************************��ȫ����***********************/
	if( pV_698Frame->SECURITYFlay[0] == 0x10 )
	{
		CommAPDUBuf[CommAPDUOffset] = (pV_698Frame->SECURITYFlay[0] | 0x80);
		CommAPDUOffset++;
		CommAPDULen++;
		if(pV_698Frame->MAC_Verify == C_OK)
		{
			CommAPDUBuf[CommAPDUOffset] = pV_698Frame->SECURITYFlay[1];
			CommAPDUOffset++;
			CommAPDUBuf[CommAPDUOffset] = 0;						/*����Ϊ0*/
			V_SecurityLenoff = CommAPDUOffset;						/*�ݴ氲ȫ����ƫ��*/
			CommAPDUOffset++;
			CommAPDULen+=2;
		}
		else
		{
			CommAPDUBuf[CommAPDUOffset] = 0x02;						/*�쳣Ӧ��*/
			CommAPDUOffset++;
			CommAPDUBuf[CommAPDUOffset] = pV_698Frame->MAC_Verify;	/*�쳣Ӧ��*/
			CommAPDUOffset++;
			CommAPDUBuf[CommAPDUOffset] = 0x00;						/*��֤Ӧ��*/
			CommAPDUOffset++;
			CommAPDULen+=3;
			goto DerictorAnswerFlag;

		}
	}
/************************APDU����**************************/
	switch(pV_698RWPara->ServiceFlag_First)
	{
		case C_GET_Request:
			V_return = SF_GetAPDU_Encode(pStr_Comm_Parm_Address, pV_698RWPara, pV_698Frame->Data);
			break;
		case C_SET_Request:
		case C_ACTION_Request:
			V_return = SF_SetAPDU_Encode(pStr_Comm_Parm_Address, pV_698RWPara, pV_698Frame->Data);
			break;
		case C_RELEASE_Request:
			CommAPDUBuf[CommAPDUOffset] = (pV_698RWPara->ServiceFlag_First) | 0x80;
			CommAPDUOffset++;
			CommAPDULen++;
			CommAPDUBuf[CommAPDUOffset] = pV_698RWPara->PIID;		/*PIID*/
			CommAPDUOffset++;
			CommAPDULen++;
			CommAPDUBuf[CommAPDUOffset] = 0;						/*�Ͽ����ӳɹ�*/
			CommAPDUOffset++;
			CommAPDULen++;
			InF_JudgeESAMConTimer(C_ResetDealConectTime, SV_Comm_Parse_Local.ClientAddrFlag);
			break;
		case C_CONNECT_Request:
			V_return = SF_ConectRequest_Encode(pStr_Comm_Parm_Address, pV_698RWPara,pV_698Frame->Data);
			break;
		case C_Default_Request:
			CommAPDUBuf[CommAPDUOffset] = (pV_698RWPara->ServiceFlag_First) | 0x80;
			CommAPDUOffset++;
			CommAPDULen++;
			CommAPDUBuf[CommAPDUOffset] = pV_698RWPara->PIID;		/*PIID*/
			CommAPDUOffset++;
			CommAPDULen++;
			CommAPDUBuf[CommAPDUOffset] = pV_698RWPara->Rd_OI[0].Rd_Result;		/*��������*/
			CommAPDUOffset++;
			CommAPDULen++;
			break;
		default:
			V_return = C_ForbidenRW;
			break;
	}
/************************�����ϱ�����***********************/
	Inf_GetReportData(&CommAPDUBuf[CommAPDUOffset], &V_usLen, pV_698Frame->ChannelNo,C_NoActiveReportFlag);

	CommAPDUOffset += V_usLen;
	CommAPDULen += V_usLen;
/************************ʱ���ǩ����**************************/
	if(pV_698RWPara->TimeTag[0]==C_TimeTagOn)
    {
		CommAPDUBuf[CommAPDUOffset] = 0x01;							/*ʱ���ǩ*/
		CommAPDUOffset++;
		CommAPDULen++;

		PF_CopyDataBytes(&pV_698RWPara->TimeTag[2], &CommAPDUBuf[CommAPDUOffset], 10);
		CommAPDUOffset += 10;
		CommAPDULen += 10;
	}
	else
	{
		CommAPDUBuf[CommAPDUOffset] = 0;							/*��ʱ���ǩ*/
		CommAPDUOffset++;
		CommAPDULen++;
	}

/************************SID_MAC����**************************/
		if( pV_698Frame->SECURITYFlay[0] == 0x10 )
		{
			ushort16 	V_APDULenTemp, V_APDULenTemp_Plain;
			uchar8		V_MACFlay;
			uchar8		V_EncryptType;
			uchar8		V_ucEnOffset = 0;

			/***********���ĳ���*************/
			V_APDULenTemp = (CommAPDUOffset - V_SecurityLenoff - 1) ;
			V_APDULenTemp_Plain = V_APDULenTemp;
			if(V_APDULenTemp > 255)
			{
				for( i = 0; i < V_APDULenTemp; i++ )
				{
					CommAPDUBuf[CommAPDUOffset + 2 - 1 - i] = CommAPDUBuf[CommAPDUOffset - 1 - i];
				}
				CommAPDUBuf[V_SecurityLenoff] = 0x82;
				CommAPDUBuf[V_SecurityLenoff + 1] = (uchar8)(V_APDULenTemp >> 8);
				CommAPDUBuf[V_SecurityLenoff + 2] = (uchar8)(V_APDULenTemp);
				CommAPDUOffset += 2;
				CommAPDULen += 2;
				V_ucEnOffset = 2;
			}
			else if(V_APDULenTemp > 127)
			{
				for( i = 0; i < ( CommAPDUOffset - V_SecurityLenoff - 1 ); i++ )
				{
					CommAPDUBuf[CommAPDUOffset + 1 - 1 - i] = CommAPDUBuf[CommAPDUOffset - 1 - i];
				}
				CommAPDUBuf[V_SecurityLenoff] = 0x81;
				CommAPDUBuf[V_SecurityLenoff + 1] = (uchar8)(V_APDULenTemp);
				CommAPDUOffset += 1;
				CommAPDULen += 1;
				V_ucEnOffset = 1;
			}
			else
			{
				CommAPDUBuf[V_SecurityLenoff] = CommAPDUOffset - V_SecurityLenoff - 1;	/*����Ϊ0*/
			}
			/***********��ȫ��֤����***********/
			V_MACFlay = pV_698Frame->SICMAC_Type;					/*û���������Ҳ��Ҫ��mac*/
			if(pV_698Frame->SECURITYFlay[1] == 1)					/*����*/
			{
				if(pV_698Frame->SICMAC_Type == 0)					/*����+ MAC*/
				{
					V_EncryptType =Secret_MAC ;
				}
				else if(pV_698Frame->SICMAC_Type == 3)				/*����*/
				{
					V_EncryptType = Secret;
				}
				V_MACFlay = 2;
			}
			else													/*����*/
			{
				if(pV_698Frame->SICMAC_Type == 1)					/*RN*/
				{
					V_EncryptType = 0x01;
				}
				else												/*����+MAC*/
				{
					V_EncryptType = Plain_MAC;
				}
			}
			V_return = INF_S_Encrypt_698(&CommAPDUBuf[V_SecurityLenoff + 1 + V_ucEnOffset], &V_APDULenTemp, pV_698Frame->SICMAC_Type, V_EncryptType, &pV_698Frame->RN_Data[0], &pV_698Frame->RN_Data[0], SV_Comm_Parse_Local.ClientAddrFlag);
			if( ( V_return != C_OK ) && ( V_return != C_RequestTimeOut_DAR ) )
			{
				CommAPDUOffset = V_SecurityLenoff - 1;
				CommAPDUBuf[CommAPDUOffset] = 0x02;
				CommAPDUOffset++;
                if( ( SF_GetEsamIDFlag() != C_OK ) && ( pV_698Frame->ChannelNo != C_IR )
                 && ( SF_Judge_CuerrntIDFlag() == C_OK ) )				/*���������֤Ȩ��,��û�������֤ͨ��*/
                {
                    CommAPDUBuf[CommAPDUOffset] = C_Unauthorized_DAR;	/*����������֤���õ�����*/
                }
                else
                {
                    CommAPDUBuf[CommAPDUOffset] = V_return;	            /*������Ϣ*/
                }
				CommAPDUOffset++;
				CommAPDUBuf[CommAPDUOffset] = 0;						/*����֤��Ϣ*/
				CommAPDUOffset++;
				CommAPDULen = 4;
			}
			else
			{
				if(V_MACFlay == 0x02)
				{
					if(V_APDULenTemp > 255)
					{
						if(V_APDULenTemp_Plain < 256)
						{
							for( i = 0; i < V_APDULenTemp; i++ )
							{
								CommAPDUBuf[V_SecurityLenoff + 2 + V_APDULenTemp - i] = CommAPDUBuf[V_SecurityLenoff + 2 + V_APDULenTemp - 1 - i];
							}
						}
						CommAPDUBuf[V_SecurityLenoff] = 0x82;
						CommAPDUBuf[V_SecurityLenoff + 1] = (uchar8)(V_APDULenTemp >> 8);
						CommAPDUBuf[V_SecurityLenoff + 2] = (uchar8)V_APDULenTemp;
						CommAPDUOffset = V_SecurityLenoff + V_APDULenTemp + 3;
						CommAPDULen = V_APDULenTemp + 5;
					}
					else if(V_APDULenTemp > 127)
					{
						if(V_APDULenTemp_Plain < 128)
						{
							for( i = 0; i < V_APDULenTemp; i++ )
							{
								CommAPDUBuf[V_SecurityLenoff + 1 + V_APDULenTemp - i] = CommAPDUBuf[V_SecurityLenoff + 1 + V_APDULenTemp - 1 - i];
							}
						}
						CommAPDUBuf[V_SecurityLenoff] = 0x81;
						CommAPDUBuf[V_SecurityLenoff + 1] = (uchar8)V_APDULenTemp;
						CommAPDUOffset = V_SecurityLenoff + V_APDULenTemp + 2;
						CommAPDULen = V_APDULenTemp + 4;
					}
					else
					{
						CommAPDUBuf[V_SecurityLenoff] = (uchar8)V_APDULenTemp;
						CommAPDUOffset = V_SecurityLenoff + V_APDULenTemp + 1;
						CommAPDULen = V_APDULenTemp + 3;
					}
					if(pV_698Frame->SICMAC_Type == 0)
					{
						CommAPDUBuf[CommAPDUOffset] = 1;		/*����֤��Ϣ*/
						CommAPDUOffset++;
						CommAPDUBuf[CommAPDUOffset] = 0;		/*Mac��֤*/
						CommAPDUOffset++;
						CommAPDUBuf[CommAPDUOffset] = 4;		/*MAC����*/
						CommAPDUOffset++;
						if(V_return == C_RequestTimeOut_DAR)	/*ESAM��֤��ͨ��������4�ֽ�ȫ0xFF*/
						{
							memset(&CommAPDUBuf[CommAPDUOffset], 0xff, 4);
						}
						else
						{
							PF_CopyDataBytes(&pV_698Frame->RN_Data[0], &CommAPDUBuf[CommAPDUOffset], 4);
						}
						CommAPDUOffset += 4;
						CommAPDULen+=7;
					}
					else	/*����֤��Ϣ*/
					{
						CommAPDUBuf[CommAPDUOffset] = 0;		/*Mac��֤*/
						CommAPDUOffset++;
						CommAPDULen++;
					}
				}
				else if( ( V_MACFlay == 0x01 ) || ( V_MACFlay == 0 ) )
				{
					CommAPDUBuf[CommAPDUOffset] = 1;			/*����֤��Ϣ*/
					CommAPDUOffset++;
					CommAPDUBuf[CommAPDUOffset] = 0;			/*Mac��֤*/
					CommAPDUOffset++;
					CommAPDUBuf[CommAPDUOffset] = 4;			/*MAC����*/
					CommAPDUOffset++;
					if(V_return == C_RequestTimeOut_DAR)		/*ESAM��֤��ͨ��������4�ֽ�ȫ0xFF*/
					{
						memset(&CommAPDUBuf[CommAPDUOffset], 0xff, 4);
					}
					else
					{
						PF_CopyDataBytes(&pV_698Frame->RN_Data[0], &CommAPDUBuf[CommAPDUOffset], 4);
					}
					CommAPDUOffset += 4;
					CommAPDULen += 7;
				}
			}
		}
DerictorAnswerFlag:
/************************��֡�����ж�***************************/
	V_usTemp = PF_Cal_CRC((uchar8 *)&Com_Conect.ConectOverTime, C_ConectStruct_Len);
	if( ( Com_Conect.CRC16 != V_usTemp ) || ( Com_Conect.ClientTxMaxLen < 40 ) )
	{
		SF_GetCommChanelCurrentLen(pV_698Frame->ChannelNo);
	}

	if( pV_698Frame->C & 0x20 )								/*�Ѿ����ڷ�֡����״̬*/
	{
		if(CommDeriction == C_SeverseToClient)				/*����������ķ�֡*/
		{
			ushort16 V_usDataRemainedLen;

			V_DataOff = CommAPDUOffset - CommAPDULen;		/*֡ͷ����*/
			for( i = 0; i < V_DataOff; i++ )				/*��֡ͷ�������ͻ���*/
			{
				CommBuff[i]  = CommAPDUBuf[i];
			}
			CommFrameNum++;
			V_usDataRemainedLen = CommAPDULen-CommFrameNum*(Com_Conect.ClientTxMaxLen - 23);
			CommBuff[V_DataOff] = (uchar8)(CommFrameNum);
			if( V_usDataRemainedLen <= (Com_Conect.ClientTxMaxLen - 23) )	/*����Ҫ��֡��*/
			{
				CommBuff[7] |= 0x20;							/*���������ӵĺ�����־*/
				CommBuff[V_DataOff + 1] = 0x40;
				pV_698RWPara->Next_OINO = 0;
				CommAPDULen = 0;
				CommDeriction = 0;
			}
			else
			{
				V_usDataRemainedLen = (Com_Conect.ClientTxMaxLen - 23);
				CommBuff[7] |= 0x20;							/*���������ӵĺ�����־*/
				CommBuff[V_DataOff + 1] = 0xc0;
				pV_698RWPara->Next_OINO = pV_698RWPara->Current_FrameNO + 1;
			}
			for(i = 0; i < V_usDataRemainedLen; i++ )			/*�����ݿ������ͻ���*/
			{
				CommBuff[V_DataOff + i + 2]  = CommAPDUBuf[V_DataOff + i + (Com_Conect.ClientTxMaxLen - 23) * CommFrameNum];
			}
			CommLen = V_DataOff + V_usDataRemainedLen + 2;
			if(V_usDataRemainedLen <= (Com_Conect.ClientTxMaxLen - 23) )
			{
				CommFrameNum = 0;
			}
		}
		else
		{
			V_First68Off = 0;
			CommLen = ( (pV_698Frame->AddrLen) + 2 + 1 + 2 ) + 1 + V_First68Off + 2;
			CommBuff[V_First68Off + 3] = (0x80 | pV_698Frame->C);
			CommBuff[CommLen] = ((uchar8)(CommFrameNum));
			CommLen += 1;
			CommBuff[CommLen] = 0x80;
			CommLen += 1;
		}
	}
	else	/*��Ҫ�ж��Ƿ���Ҫ��֡����*/
	{
		V_DataOff = CommAPDUOffset - CommAPDULen;				/*֡ͷ����*/
		for( i = 0; i < V_DataOff; i++ )						/*��֡ͷ�������ͻ���*/
		{
			CommBuff[i]  = CommAPDUBuf[i];
		}
		if( CommAPDULen > (Com_Conect.ClientTxMaxLen - 23) )	/*��Ҫ��֡*/
		{
			CommBuff[V_First68Off + 3] |= 0x20;					/*���������ӵĺ�����־*/
			CommDeriction = C_SeverseToClient;					/*Ӧ�ò㷢���֡*/
			CommFrameNum = 0;
			CommBuff[V_DataOff] = (uchar8)(CommFrameNum);
			CommBuff[V_DataOff + 1] = 0;
			for( i = 0; i < ( Com_Conect.ClientTxMaxLen - 23 ); i++ )	/*�����ݿ������ͻ���*/
			{
				CommBuff[V_DataOff + i + 2]  = CommAPDUBuf[V_DataOff + i];
			}
			CommLen = V_DataOff + ( Com_Conect.ClientTxMaxLen - 23 ) + 2;
			pV_698RWPara->Next_OINO = pV_698RWPara->Current_FrameNO + 1;
		}
		else	/*����Ҫ��֡*/
		{
			for( ; i < CommAPDUOffset; i++ )					/*�����ݿ������ͻ���*/
			{
				CommBuff[i]  = CommAPDUBuf[i];
			}
			CommLen = CommAPDUOffset;
			CommDeriction = 0;									/*����Ҫ��֡���֡��־*/
		}
	}

/************************֡����**************************/
	V_DataLen = (CommLen) - 1 + 2 - V_First68Off;				/*ȥ��1�ֽ�68������2�ֽ�FCS*/
	PF_Ushort16ToBuffer2(&CommBuff[1 + V_First68Off], &V_DataLen);

/************************����HCS**************************/
	V_DataLen = PF_Cal_CRC_698(&CommBuff[1 + V_First68Off], ( (pV_698Frame->AddrLen) + 2 + 1 + 2 ) );
	PF_Ushort16ToBuffer2(&CommBuff[( (pV_698Frame->AddrLen) + 2 + 1 + 2 ) + 1 + V_First68Off], &V_DataLen);

/************************���봦��*************************/
	if( ( ( CommBuff[1 + V_First68Off + 2] ) & C_Scramble_Flag ) == C_Scramble_Flag )
	{
		V_DataLen = ( (pV_698Frame->AddrLen) + 2 + 1 + 2 ) + 1 + V_First68Off + 2;
		for( i = V_DataLen; i < (CommLen); i++ )
		{
			CommBuff[i] += 0x33;
		}
	}
/************************����FCS**************************/
	V_DataLen = PF_Cal_CRC_698(&CommBuff[1 + V_First68Off], ((CommLen) - 1 - V_First68Off));
	PF_Ushort16ToBuffer2(&CommBuff[CommLen], &V_DataLen);

/************************֡������**************************/
	CommLen += 2;
	CommBuff[CommLen] = 0x16;
	CommLen = (CommLen) + 1;

	return V_return;
}
#if 0
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_EnergyTo698(ulong32 V_ulOAD, uchar8 *pV_ucOriginalData, uchar8 *pV_ucExchangedData, uchar8 V_ucLen)
������������������ת��Ϊ����698Э���ʽ����
���������V_ulOADΪ������������2��4��6��OAD
			pV_ucOriginalData��ָ��ԭʼ�����׵�ַ�����ݸ�ʽ��
								����2Ϊ4�ֽ�hex�����ֽ���ǰ�����ֽڵ����λΪ����λ
								����4Ϊ5�ֽ�hex�����ֽ���ǰ�����ֽڵ����λΪ����λ
								����6Ϊ1�ֽ�hex�����λΪ����λ
			pV_ucExchangedData��ָ��ת���������׵�ַ�����ݸ�ʽ��
								����2Ϊ4�ֽ�hex�����ֽ���ǰ�����ֽڵ����λΪ����λ
								����4Ϊ8�ֽ�hex�����ֽ���ǰ�����ֽڵ����λΪ����λ
								����6Ϊ1�ֽ�hex�����λΪ����λ
�����������������ݴ��ͨ���շ�����
			pV_ucExchangedData��ָ��ת���������׵�ַ�����ݸ�ʽ��
								����2Ϊ4�ֽ�hex�����ֽ���ǰ�����ֽڵ����λΪ����λ
								����4Ϊ8�ֽ�hex�����ֽ���ǰ�����ֽڵ����λΪ����λ
								����6Ϊ1�ֽ�hex�����λΪ����λ
���ز���������ת��������ݳ���
����λ�ã�
��    ע�����ڵ��ܣ�������������Ϊ�з����������޷��������ڲ�ͳһ�����λ����Ϊ����λ��
		�����޷����������λʼ��Ϊ0�������з������������λ
*******************************************************************************/
uchar8 SF_EnergyTo698(ulong32 V_ulOAD, uchar8 *pV_ucOriginalData, uchar8 *pV_ucExchangedData, uchar8 V_ucLen)
{
	uchar8 V_ucLen_T = 0;

	if( ( (V_ulOAD & 0xF000FF00) == 0x00000200)					/*����2���ܣ�4�ֽ�hex����ֱ�Ӹ��Ƶ����*/
	 && ( V_ucLen == C_EnergyCommLen) )
	{
		memcpy(pV_ucExchangedData, pV_ucOriginalData, V_ucLen);
		V_ucLen_T = V_ucLen;
	}
	else if( ( ( V_ulOAD & 0xF000FF00 ) == 0x00000400 )			/*����4���ܣ�5�ֽ�hex������չΪ8�ֽ�hex�����*/
		  && ( V_ucLen == C_AccurateEnergyCommLen) )
	{
		if( (pV_ucOriginalData[0]&0x80) == 0x80)
		{
			memset(pV_ucExchangedData, 0xFF, 3);
		}
		else
		{
			memset(pV_ucExchangedData, 0x00, 3);
		}
		memcpy( (pV_ucExchangedData + 3), pV_ucOriginalData, V_ucLen);
		V_ucLen_T = V_ucLen + 3;
	}
	else if( ( ( V_ulOAD&0xF000FF00 ) == 0x00000600 )			/*����6���ܣ�1�ֽ�hex����ֱ�Ӹ��Ƶ����*/
		  && ( V_ucLen == C_EnergyCommPulseLastLen ) )
	{
		pV_ucExchangedData[0] = pV_ucOriginalData[0];
		V_ucLen_T = V_ucLen;
	}

	return V_ucLen_T;
}
#endif

/*******************************************************************************
����ԭ�ͣ�uchar8 SF_GetAPDU_Read(Str_Type645DI_Class *P_DIFor645,uchar8 *P_645DINum,uchar8 *P_DataBuf,ushort16 *P_DataOff,uchar8 V_UpperType,uchar8 V_Flag)
���������������ݴ���
���������ת�����645���ݱ�ʶ�룬���ݱ�ʶ���������ȡ���ݴ��buffer
				V_UpperTypeΪOI��Ӧ����������
�����������������ݴ��ͨ���շ�����
���ز��������ذ�ȫȨ���Ƿ�����Ҫ��C_OK��ʾ����Ȩ��Ҫ��
����λ�ã�
��    ע��*P_DataOff �Ƿ�Ҫ���ڶ�ȡ���ݳ���+4�ֽ�OAD����,uchar8 V_Flag �����ж��Ƿ���Ҫ�ж�ʣ�೤�Ȳ���4�ֽ����
*******************************************************************************/
uchar8 SF_GetAPDU_Read(Str_Type645DI_Class *P_DIFor645, uchar8 *P_645DINum, uchar8 *P_DataBuf, ushort16 *P_DataOff, uchar8 V_UpperType, uchar8 V_Flag)
{
	uchar8	 i, k, V_return, V_ucLen645, V_ucLen645_P, V_Str_NUM, V_ucDataOff645;
	ushort16 V_DataOff, V_Len, V_usLen698, j, m, V_ucLen;
	uchar8	 V_DataTemp[300];
	ulong32	 V_ulDataTemp[2];
	ushort16 V_usDataLen[30] = {0}, V_usDataEncode[30] = {0x00};
	uchar8 V_ucTempLen;
	
	V_DataOff = 1;
	V_Len = *P_DataOff;
	if( ( P_DIFor645->V_ucOAD == CSafeModePara ) && ( InF_JudgeIJTimer() != C_OK ) )
	{
		P_DataBuf[0] = 0x01;           				/*����Ϊ1*/
		P_DataBuf[V_DataOff] = 0x01;    			/*��������Ϊ1*/
		V_DataOff++;
		*P_DataOff = 2;
		return C_OK;
	}
	else if(P_DIFor645->V_ucOAD == 0x43000500)		/*���豸*/
	{
		for( i = 0; i < C_ObjectNO_Len; i++ )
		{
			P_DataBuf[V_DataOff + i * 3] = 0x50;	/*OI��������*/
			P_DataBuf[V_DataOff + i * 3 + 1] = 0xF2;
			P_DataBuf[V_DataOff + i * 3 + 2] = C_ObjectNO[i];
		}
		V_DataOff += (C_ObjectNO_Len * 3);
		V_return = C_OK;
	}

	else if( ( P_DIFor645->V_ucOAD & 0xFFFFFF00 ) == 0x30230700 )
	{
		uchar8 V_NumTimes = 1;
		ulong32 V_ul30230700OAD;

		if(P_DIFor645->V_ucOAD == 0x30230700)
		{
			V_NumTimes = 2;
			P_DataBuf[0] = 24;
			V_ul30230700OAD = CProgReC1_Degree;
		}
		else if(P_DIFor645->V_ucOAD == 0x30230701)
		{
			V_ul30230700OAD = CProgReC1_Degree;
			P_DataBuf[0] = 10;
		}
		else
		{
			V_ul30230700OAD = CProgReC2_Degree;
			P_DataBuf[0] = 10;
		}
		for( k = 0; k < V_NumTimes; k++ )
		{
            if(V_NumTimes == 2)
			{
				P_DataBuf[V_DataOff] = C_structure;
				V_DataOff++;
				P_DataBuf[V_DataOff] = 0x02;
				V_DataOff++;
			}
			P_DataBuf[V_DataOff] = C_enum;
			V_DataOff++;
			if(V_NumTimes == 2)
			{
				P_DataBuf[V_DataOff] = k;
				V_DataOff++;
			}
			else
			{
				P_DataBuf[V_DataOff] = (uchar8)(P_DIFor645->V_ucOAD);
				V_DataOff++;
			}
			P_DataBuf[V_DataOff] = C_structure;
			V_DataOff++;
			P_DataBuf[V_DataOff] = 0x02;
			V_DataOff++;
			P_DataBuf[V_DataOff] = C_double_long_unsigned;
			V_DataOff++;
			V_ucLen = 20;
			if( InF_Read_Data( V_ul30230700OAD + k, V_DataTemp, &V_ucLen, V_usDataEncode ) != C_OK )
			{
				memset(&V_DataTemp[0], 0x00, 4);
				V_ucLen = 4;
	        };
			P_DataBuf[V_DataOff] = V_DataTemp[3];
			V_DataOff++;
			P_DataBuf[V_DataOff] = V_DataTemp[2];
			V_DataOff++;
			P_DataBuf[V_DataOff] = V_DataTemp[1];
			V_DataOff++;
			P_DataBuf[V_DataOff] = V_DataTemp[0];
			V_DataOff++;
			P_DataBuf[V_DataOff] = C_double_long_unsigned;
			V_DataOff++;

			memset(&P_DataBuf[V_DataOff], 0x00, 4);
			V_DataOff += 4;
		}
		V_return = C_OK;
	}
    else
	{
		for( i = 0; i < *P_645DINum; i++ )
		{
			if(V_Len > 255)
			{
				V_ucLen = 255;
			}
			else
			{
				V_ucLen = (uchar8)V_Len;
			}
			if( ( P_DIFor645->V_ucOAD & 0xFF000000 ) == 0x00000000 )			/*���ܶ�ȡ*/
			{
				if( ( P_DIFor645->DataType[i] == C_double_long ) || ( P_DIFor645->DataType[i] == C_double_long_unsigned ) )		/*��ͨ���ܣ�����2����*/
				{
					V_ucLen = C_EnergyCommLen;
				}
                else if( ( P_DIFor645->DataType[i] == C_integer ) || ( P_DIFor645->DataType[i] == C_unsigned ) )				/*����β��������6����*/
                {
					V_ucLen = C_EnergyCommPulseLastLen;
                }
				else															/*��ȷ���ܣ�����4����*/
				{
					V_ucLen = C_AccurateEnergyCommLen;
				}
				V_return = InF_GetData_ObjectManage(P_DIFor645->V_ucOAD, V_DataTemp, &V_ucLen, V_usDataEncode);
			}
			else if( ( ( P_DIFor645->V_ucOAD & 0xFFFF0000 ) == 0x202C0000 )
					|| ( ( P_DIFor645->V_ucOAD & 0xFFFF0000 ) == 0x202D0000 )
					|| ( ( P_DIFor645->V_ucOAD & 0xFFFF0000 ) == 0x20310000 )
					|| ( ( P_DIFor645->V_ucOAD & 0xFFFF0000 ) == 0x20320000 ) )	/*���ܶ�ȡ*/
			{
				V_ucLen = 4;
				V_return = InF_GetData_ObjectManage(P_DIFor645->V_ucOAD, V_DataTemp, &V_ucLen, V_usDataEncode);
			}
			else if( ( ( P_DIFor645->V_ucOAD & 0xFF000000 ) == 0x10000000 )
                  && ( ( P_DIFor645->V_ucOAD != CLossA_Vol_Degree ) &&( P_DIFor645->V_ucOAD != CLossB_Vol_Degree )&& ( P_DIFor645->V_ucOAD != CLossC_Vol_Degree ) )
                  && ( ( P_DIFor645->V_ucOAD != CLossA_Vol_Time ) && ( P_DIFor645->V_ucOAD != CLossB_Vol_Time ) && ( P_DIFor645->V_ucOAD != CLossC_Vol_Time ) ) )	/*���������ȡ*/
			{
				V_ucLen = CLPos_Ac_Tol_De_0;
				V_return = InF_GetData_ObjectManage(P_DIFor645->V_ucOAD, V_DataTemp, &V_ucLen, V_usDataEncode);
			}
			else if( ( ( P_DIFor645->V_ucOAD & 0xFFFF0000 ) == ( CPhaseFF_Curr &  0xFFFF0000 ) )				/*����*/
				  || ( ( P_DIFor645->V_ucOAD & 0xFFFF0000 ) == ( COneMin_AcPower_FF &  0xFFFF0000 ) )			/*1����ƽ���й�����*/
				  || ( ( P_DIFor645->V_ucOAD & 0xFFFF0000 ) == ( COneMin_RePower_FF &  0xFFFF0000 ) ) )			/*1����ƽ���޹�����*/
			{
				V_ucLen = CLOneMin_RePower_FF;																	/*�����ù��ʳ��ȣ�16*/
				V_return = InF_GetData_ObjectManage(P_DIFor645->V_ucOAD, V_DataTemp, &V_ucLen, V_usDataEncode);
			}
			else if( ( P_DIFor645->V_ucOAD == 0x80010200 ) || ( P_DIFor645->V_ucOAD == 0x80000400 ) || ( P_DIFor645->V_ucOAD == 0x80000500 ) )	/*����״̬/����״̬/�̵�������״̬*/
			{
				V_return = C_OK;
				V_ucLen = CLMeter_Work_State3;
				V_return = InF_GetData_ObjectManage(P_DIFor645->V_ucOAD, P_DataBuf + V_DataOff, &V_ucLen, V_usDataEncode);
				V_DataOff++;
				V_Len --;
				continue;
			}
			else if(P_DIFor645->V_ucOAD == 0x40100200)								/*������Ԫ��*/
			{
				uchar8 V_ucLineType;

				V_ucLen = CLLine_Type;
				V_ulDataTemp[0]= CLine_Type;
				V_return = InF_Read_Data(V_ulDataTemp[0], &V_ucLineType, &V_ucLen, V_usDataEncode);
				if(V_ucLineType == 0)
				{
					V_DataTemp[0] = 2;
				}
				else
				{
					V_DataTemp[0] = 3;
				}
			}
			else if(P_DIFor645->V_ucOAD == CPluse_Wide)								/*������*/
			{
				V_ucLen = CLPluse_Wide;
				V_DataTemp[0]= C_PluseWide;
				V_return = C_OK;
			}
			else
			{
				V_ulDataTemp[1] = 0xFFFFFFFF;
				if(P_DIFor645->IDFlay == C_TableIDValiable)							/*�¼���¼��ǰֵ*/
				{
					V_ulDataTemp[0] = P_DIFor645->V_ucOAD;
					V_return = Inf_ReadEventCurrentData(V_ulDataTemp[0], V_DataTemp, (uchar8 *)&V_ucLen);
					if((V_return == C_IDError))
					{
						V_return = InF_Read_Data(P_DIFor645->V_ucOAD, V_DataTemp, &V_ucLen, V_usDataEncode);
					}
					if(V_return == C_NoData)
					{
						P_DataBuf[0] = 0x01;										/*����Ϊ1*/
						V_DataOff = V_DataOff + V_ucLen;
						P_DIFor645->V_ucOAD += 0x00000001;
						V_return = C_OK;
						break;
					}
					if(P_DIFor645->NextClassNO == (Str_DI0_DataType_PaTable *)Event_Class7_10AttriTable)
					{
						if(InF_JudgeNoEndTimeEvent(P_DIFor645->V_ucOAD) == C_OK)	/*û�н���ʱ��*/
						{
							memset(&V_DataTemp[C_EndTimeOffset], 0xAA, 7);			/*����ʱ�����ݸ�ֵAA*/
						}
					}
				}
				else if( ( P_DIFor645->IDNO & 0xC0 )==C_ClassNum24All )				/*�¼���24��ǰ��¼��*/
				{
					uchar8 V_OIB;

					V_OIB = Event_OIBTable[P_DIFor645->IDNO & 0x3F].OIB;

					if( ( V_OIB == CTrend_Rev_OIB )			/*�й����ʷ���*/	
					|| ( V_OIB == CPFactorT_Over_OIB )		/*��������������*/
					|| ( V_OIB == CRe_ReDe_Over_OIB ) )		/*�޹���������*/	
					{
						P_DIFor645->V_ucOAD = Event_OIBTable[P_DIFor645->IDNO & 0x3F].RecordNum + i * 0x00000001;
					}
					else
					{
						if( i== 0 )
						{
							P_DataBuf[V_DataOff] = 0;
							V_DataOff++;
							continue;
						}
						P_DIFor645->V_ucOAD = Event_OIBTable[P_DIFor645->IDNO & 0x3F].RecordNum + ( i - 1 ) * 0x00000001;
					}
					V_ulDataTemp[0] = P_DIFor645->V_ucOAD;
					V_return = Inf_ReadEventRenew(V_ulDataTemp, V_DataTemp, (uchar8 *)&V_ucLen);
					if(V_return != C_OK)
					{
						V_return = InF_Read_Data(P_DIFor645->V_ucOAD, V_DataTemp, &V_ucLen, V_usDataEncode);
					}
				}
	        	else if( ( P_DIFor645->V_ucOAD & 0xFFFFFF00 )==0x30000D00 )
	        	{

					V_ulDataTemp[0] = P_DIFor645->V_ucOAD;
					V_return = Inf_ReadEventRenew(V_ulDataTemp, V_DataTemp, (uchar8 *)&V_ucLen);
					if(V_return == C_IDError)
					{
						V_return = InF_Read_Data(P_DIFor645->V_ucOAD, V_DataTemp, &V_ucLen, V_usDataEncode);
					}
	        	}
                else if( ( P_DIFor645->V_ucOAD & 0xFF00FFFF ) == 0xf3000402 )		/*���������ܾ���д*/
                {
                  V_ucLen = 1;
                  V_DataTemp[0] = 99;												/*����ҪBCDתHEX*/
                  V_return = C_OK;
                }
				else
				{
					V_return = InF_Read_Data(P_DIFor645->V_ucOAD, V_DataTemp, &V_ucLen, V_usDataEncode);
					if( ( P_DIFor645->V_ucOAD ) == CInset_Card_State )				/*�忨״̬�֡���ȡ����δ֪*/
					{
						InF_WriteCardStatus(C_CardStatusUnknow);
					}
				}
			}
			/*���������ʧ�ܣ���ֱ��Ӧ�����*/
			if(V_return != C_OK)
			{
				V_ucLen = 0;	/*Ӧ��Ӧ������Ϊ0,��ֹ��ֵ255��,ָ�뱻�ı䣬����λ*/
			}
			if( ( P_DIFor645->V_ucOAD & 0xFFFFFF00 ) == CMeter_Position )
			{
				V_usLen698 = SF_DataExchangeTo698_Where(&P_DataBuf[V_DataOff], V_DataTemp, P_DIFor645->V_ucOAD);
				V_DataOff += V_usLen698;
				V_Len -= V_DataOff;
				continue;
			}
            if( ( ( (P_DIFor645->V_ucOAD) & 0xffffff00 ) == CCurrent_Ladder_Table ) || ( ( (P_DIFor645->V_ucOAD) & 0xffffff00 ) == CBackUp_Ladder_Table ) )
            {
                V_usLen698 = SF_DataExchangeTo698_Ladder(&P_DataBuf[V_DataOff], V_DataTemp, (uchar8)P_DIFor645->V_ucOAD);
                V_DataOff += V_usLen698;
				V_Len -= V_DataOff;
                continue;
            }
            if( ( P_DIFor645->V_ucOAD == CCurrent_RateFF_Price ) || ( P_DIFor645->V_ucOAD == CBackUp_RateFF_Price ) )
			{
				V_DataOff += V_usLen698;
				V_Len -= V_DataOff;
				continue;
			}
			V_ucLen645 = 0;
			if( P_DIFor645->NextClassNum != C_NULL )
			{
				V_ucLen645_P = 0;
				for( j = 0; j < P_DIFor645->NextClassNum; j++ )
				{
					V_ucLen645_P += P_DIFor645->NextClassNO[j].DataLen_645;
				}
	            if( ( P_DIFor645->NextClassNO == Event_Class24_CurrentRecTable ) || ( P_DIFor645->NextClassNO == Event_Class24_14AttriTable ) )/*��24���������*/
	            {
	                if(P_DIFor645->DataLen_645[i] == 0)
	                {
	                    P_DataBuf[V_DataOff] = 0;
	                    V_DataOff++;
	                }
	            }
				V_Str_NUM = P_DIFor645->DataLen_645[i] / V_ucLen645_P;


				if(P_DIFor645->DataType[i] == C_array)
				{
					P_DataBuf[V_DataOff] = C_array;
					V_DataOff++;
					P_DataBuf[V_DataOff] = V_Str_NUM;
					V_DataOff++;
				}

				V_ucDataOff645 = 0;
				for( ; V_Str_NUM > 0; V_Str_NUM-- )
				{
					if( ( P_DIFor645->DataType[i] != C_NULL ) && ( P_DIFor645->DataType[i] != C_array ) )
					{
						P_DataBuf[V_DataOff] = P_DIFor645->DataType[i];			/*��1�ֽ���������*/
						V_DataOff++;
					}
					if( ( P_DIFor645->DataType[i] == C_structure ) )
					{
						P_DataBuf[V_DataOff] = P_DIFor645->NextClassNum;		/*��Ҫ�����ָ������߽ṹ��������б���*/
						if( ( P_DIFor645->NextClassNO == (Str_DI0_DataType_PaTable *)Event_Class7_CurrentRecTable ) || ( P_DIFor645->NextClassNO == (Str_DI0_DataType_PaTable *)Event_Class7_10AttriTable ) )
	                    {
							P_DataBuf[V_DataOff] = 2;
	                    }
	                    V_DataOff++;
					}
					if( ( V_ucLen % V_ucLen645_P ) == 0 )						/*�������ݸ�ʽת��*/
					{
						for( j = 0; j < P_DIFor645->NextClassNum; j++ )
						{
							V_ucLen645 = 0;
							if(P_DIFor645->NextClassNO[j].DataType == C_array)
							{
								continue;
							}
							if(P_DIFor645->NextClassNO[j].DataType == C_structure)
							{
								P_DataBuf[V_DataOff] = P_DIFor645->NextClassNO[j].DataType;
								V_DataOff++;
								P_DataBuf[V_DataOff] = P_DIFor645->NextClassNum - j - 1;
								V_DataOff++;
								continue;
							}
							if(P_DIFor645->NextClassNO[j].DataType == C_NULL)
							{
								P_DataBuf[V_DataOff] = P_DIFor645->NextClassNO[j].DataType;
								V_DataOff++;
								continue;
							}
							for( k = 0; k < j; k++ )
							{
								V_ucLen645 += P_DIFor645->NextClassNO[k].DataLen_645;
							}
							if((P_DIFor645->V_ucOAD&0xFF000000) == 0x10000000)			/*�����������Ҫ���ݵߵ�*/
							{
								P_DataBuf[V_DataOff] = P_DIFor645->NextClassNO[j].DataType;
								V_usLen698 = SF_GetDataTypeLen(&P_DataBuf[V_DataOff]);
								if( ( V_DataOff + V_usLen698 ) < *P_DataOff )			/*��ֹ���һ�����ݼ�OAD4�ֽں�*/
								{
                                    if( ( ( ( V_DataOff + V_usLen698 ) + 4 ) >= *P_DataOff ) && ( V_Flag == C_Read_FlagNor ) )
                                    {
                                        return C_MaxResponseLen_ERR;
                                    }
									V_usLen698 = SF_DataExchangeTo698_BasicData(&(P_DataBuf[V_DataOff]), &V_DataTemp[V_ucDataOff645 + V_ucLen645], 10, P_DIFor645->NextClassNO[j].DataLen_645);
									if(j == 1)
									{
										P_DataBuf[V_DataOff+V_usLen698] = 0x00;
									}
									V_DataOff += (V_usLen698 + 1);
								}
								else
								{
									return C_MaxResponseLen_ERR;
								}
							}
							else if( ( P_DIFor645->V_ucOAD & 0xFFFFFF00 ) == CMeter_CommPro )
							{
								V_usLen698 = GV_Str_DI0_DataType_CommProTable[j].DataLen_698;
								P_DataBuf[V_DataOff] = V_usLen698;
								if( ( V_DataOff + V_usLen698 ) < *P_DataOff )
								{
									if( ( ( ( V_DataOff + V_usLen698 ) + 4 ) >= *P_DataOff ) && ( V_Flag == C_Read_FlagNor ) )/*��ֹ���һ�����ݼ�OAD4�ֽں�*/
									{
										return C_MaxResponseLen_ERR;
									}
									V_usLen698 = SF_DataExchangeTo698_BasicData(&(P_DataBuf[V_DataOff - C_TypeLen]), &V_DataTemp[V_ucDataOff645], V_usLen698, P_DIFor645->NextClassNO[j].DataLen_645);
									                                     /*698�����Ϳ�ʼ���룬645��������ʼ��ʼ����*/
									V_DataOff += (V_usLen698 + C_TypeLen_Len);
								}
								else
								{
									return C_MaxResponseLen_ERR;
								}
							}
							else
							{
								if(SF_JudgeAllAA( &V_DataTemp[V_ucDataOff645 + V_ucLen645], P_DIFor645->NextClassNO[j].DataLen_645 ) == C_OK )
								{
									P_DataBuf[V_DataOff] = 0;
									V_DataOff ++;
									continue;
								}
								P_DataBuf[V_DataOff] = P_DIFor645->NextClassNO[j].DataType;
								V_usLen698 = SF_GetDataTypeLen(&P_DataBuf[V_DataOff]);
								if( ( V_DataOff + V_usLen698 ) < *P_DataOff )
								{
									if( ( ( ( V_DataOff + V_usLen698 ) + 4 )  >= *P_DataOff ) && ( V_Flag == C_Read_FlagNor ) )/*��ֹ���һ�����ݼ�OAD4�ֽں�*/
									{
										return C_MaxResponseLen_ERR;
									}
									V_usLen698 = SF_DataExchangeTo698_BasicData(&(P_DataBuf[V_DataOff]), &V_DataTemp[V_ucDataOff645 + V_ucLen645], 10, P_DIFor645->NextClassNO[j].DataLen_645);
									V_DataOff += (V_usLen698 + 1);
								}
								else
								{
									return C_MaxResponseLen_ERR;
								}
							}
						}
						V_ucDataOff645 += V_ucLen645_P;
					}
					else		/*��ȡ�������ʽת����Ӧ����һͬ�����д���Ӧ��*/
					{
						return C_ObjectNotExist_DAR;								/*����ƥ��*/
					}
				}
			}
			else
			{
				if( ( SF_JudgeAllAA( &V_DataTemp[V_ucLen645], V_ucLen ) == C_OK )
				  && ( ( P_DIFor645->V_ucOAD & 0xF0000000 ) != 0x40000000 )
				  && ( ( P_DIFor645->V_ucOAD & 0xFF000000 ) != 0x00000000 ) )		/*���ӵ���OAD���ж�ȫAA*/
				{
					P_DataBuf[V_DataOff] = 0;
					V_DataOff ++;
					V_usLen698 = 0;
					V_ucLen645 += V_ucLen;
					continue;
				}
				P_DataBuf[V_DataOff] = P_DIFor645->DataType[i];						/*��1�ֽ���������*/
				if( ( P_DataBuf[V_DataOff] == C_octet_string ) || ( P_DataBuf[V_DataOff] == C_visible_string )
				  ||( P_DataBuf[V_DataOff] == C_bit_string ) )
				{
					V_ucTempLen = 0;
					V_usLen698 = P_DIFor645->DataLen_698[i];
					if(V_usLen698 > 255)
					{
						P_DataBuf[V_DataOff + 1] = 0x82;
						P_DataBuf[V_DataOff + 2] = (uchar8)(V_usLen698 >> 8);
						P_DataBuf[V_DataOff + 3] = (uchar8)(V_usLen698);
						V_ucTempLen = 2;
					}
					else if(P_DIFor645->DataLen_698[i] > 127)
					{
						P_DataBuf[V_DataOff + 1] = 0x81;
						P_DataBuf[V_DataOff + 2] = P_DIFor645->DataLen_698[i];
						V_ucTempLen = 1;
					}
					else
					{
						P_DataBuf[V_DataOff + 1] = P_DIFor645->DataLen_698[i];
					}
					if( ( V_DataOff + V_usLen698) < *P_DataOff )
					{
						if( ( ( ( V_DataOff + V_usLen698 ) + 4 ) >= *P_DataOff ) && ( V_Flag == C_Read_FlagNor ) )/*��ֹ���һ�����ݼ�OAD4�ֽں�*/
						{
							return C_MaxResponseLen_ERR;
						}

						if( P_DIFor645->MAXRecordTimes != 0 )
						{
							if( V_DataTemp[V_ucLen645] > P_DIFor645->MAXRecordTimes )
							{
								V_DataTemp[V_ucLen645] = P_DIFor645->MAXRecordTimes;
							}
							else
							{
								for( m = 1; m < V_ucLen; m++ )
								{
									if( V_DataTemp[m+V_ucLen645] > 0 )
									{
										break;
									}
								}
								if( m != V_ucLen )
								{
									V_DataTemp[V_ucLen645] = P_DIFor645->MAXRecordTimes;

									for( m = 1; m < V_ucLen; m++ )
									{
										V_DataTemp[m + V_ucLen645] = 0;
									}
								}
							}
						}
						V_usLen698 = SF_DataExchangeTo698_BasicData(&(P_DataBuf[V_DataOff]), &V_DataTemp[V_ucLen645], V_usLen698, V_ucLen);

						if( P_DataBuf[V_DataOff] == V_UpperType )
						{
							PF_CopyDataBytes_698(&(P_DataBuf[V_DataOff+2]), &(P_DataBuf[V_DataOff]), V_usLen698);
							V_DataOff += (V_usLen698);
						}
						else
						{
							V_DataOff += (V_usLen698 + 2 + V_ucTempLen);
						}
						V_ucLen645 += V_ucLen;
	                    V_ucLen = V_usLen698;
					}
					else
					{
						return C_MaxResponseLen_ERR;
					}
				}
				else
				{
					V_usLen698 = SF_GetDataTypeLen(&P_DataBuf[V_DataOff]);
					if(V_usLen698 == 0)
					{
						V_usLen698 = P_DIFor645->DataLen_698[i];
					}
					if( ( V_DataOff + V_usLen698 ) < *P_DataOff )
					{
                        if( ( ( ( V_DataOff + V_usLen698 ) + 4 ) >= *P_DataOff ) && ( V_Flag == C_Read_FlagNor ) )/*��ֹ���һ�����ݼ�OAD4�ֽں�*/
                        {
                            return C_MaxResponseLen_ERR;
                        }
						if( P_DIFor645->MAXRecordTimes != 0 )
						{
                            ulong32 V_ulHexTemp;
                            uchar8 V_ucLength;

                            PF_Buffer4ToUlong32(&V_DataTemp[V_ucLen645], &V_ulHexTemp, 4);

							if( V_ulHexTemp >= (ulong32)P_DIFor645->MAXRecordTimes )
							{
                                V_ulHexTemp = (ulong32)P_DIFor645->MAXRecordTimes;
                                V_ucLength = 0x04;
                                PF_Ulong32ToBuffer4(&V_DataTemp[V_ucLen645], &V_ulHexTemp, V_ucLength);
							}
							else
							{
								for( m = 1; m < V_ucLen; m++ )
								{
									if( V_DataTemp[m + V_ucLen645] > 0 )
									{
										break;
									}
								}
								if( m != V_ucLen )
								{
									V_DataTemp[V_ucLen645] = P_DIFor645->MAXRecordTimes;

									for( m = 1; m < V_ucLen; m++ )
									{
										V_DataTemp[m + V_ucLen645] = 0;
									}
								}
							}
						}
						if( ( ( (uchar8)( (P_DIFor645->V_ucOAD) >> 24 ) ) == 0x30 ) && ( ( (uchar8)( P_DIFor645->V_ucOAD ) ) == ( P_DIFor645->DataType[C_MaxDataTypeNum - 2] ) ) )
						{
							if( ( ( ( (uchar8)((P_DIFor645->V_ucOAD) >> 8 ) ) == 6 ) && ( ( P_DIFor645->DataType[C_MaxDataTypeNum-  1] ) == 7 ) )
							   ||( ( ( (uchar8)((P_DIFor645->V_ucOAD) >> 8) ) == 5 ) && ( ( P_DIFor645->DataType[C_MaxDataTypeNum - 1]) == 24 ) ) )
							{
								P_DataBuf[V_DataOff + 1] = V_DataTemp[V_ucLen645];
								V_usLen698 = 1;
							}
							else
							{
								V_usLen698 = SF_DataExchangeTo698_BasicData(&(P_DataBuf[V_DataOff]), &V_DataTemp[V_ucLen645], 10, V_ucLen);
							}
						}
						else if ( ( P_DIFor645->V_ucOAD == CAux_Pow_Down_Delay_T ) || ( P_DIFor645->V_ucOAD == CReversedVoltage_Delay_T )
							   || ( P_DIFor645->V_ucOAD == CReversedCurrent_Delay_T ) || ( P_DIFor645->V_ucOAD == CClockFa_Delay_T )
							   || ( P_DIFor645->V_ucOAD == CMeterFa_Delay_T ) )
						{
							P_DataBuf[V_DataOff + 1] = V_DataTemp[V_ucLen645];
							V_usLen698 = 1;
						}
						else if( ( P_DIFor645->V_ucOAD == CNoBal_Vol_Lim )
							  || ( P_DIFor645->V_ucOAD == CNoBal_Curr_Lim )
							  || ( P_DIFor645->V_ucOAD == CSeriNoBal_Curr_Lim ) )
						{
							P_DataBuf[V_DataOff] = 0x12;
							V_usLen698 = SF_DataExchangeTo698_BasicData(&(P_DataBuf[V_DataOff]), &V_DataTemp[V_ucLen645], 10, V_ucLen);
							P_DataBuf[V_DataOff] = 0x10;
						}
                        else if( P_DIFor645->V_ucOAD == CClientAddr )
                        {
                            P_DataBuf[V_DataOff] = C_unsigned;
                            P_DataBuf[V_DataOff + 1] = V_DataTemp[0];
                            V_usLen698 = 1;
                            V_ucLen = 1;
                        }
                        else if( P_DIFor645->V_ucOAD == CConAutheMechanism )
                        {
                            P_DataBuf[V_DataOff] = C_enum;
                            P_DataBuf[V_DataOff + 1] = V_DataTemp[0];
                            V_usLen698 = 1;
                            V_ucLen = 1;
                        }
                        else if( ( P_DIFor645->V_ucOAD & 0xFF000F00 ) == CCom_Ac_LastPulse_FF_0 )
                        {
                            P_DataBuf[V_DataOff + 1] = V_DataTemp[V_ucLen645];
                            V_usLen698 = C_EnergyCommPulseLastLen;
                            V_ucLen = C_EnergyCommPulseLastLen;
                        }
#if 0
                        else if( ( P_DIFor645->V_ucOAD & 0xFF000000 ) == 0x00000000 ) 		/*���ܽ������⴦��*/
                        {
                            V_usLen698 = SF_EnergyTo698(P_DIFor645->V_ucOAD, &V_DataTemp[V_ucLen645], &(P_DataBuf[V_DataOff + 1]), V_ucLen);
                        }
#endif
						else
						{
							V_usLen698 = SF_DataExchangeTo698_BasicData(&(P_DataBuf[V_DataOff]), &V_DataTemp[V_ucLen645], 10, V_ucLen);
						}
						if(P_DataBuf[V_DataOff] == V_UpperType)
						{
							PF_CopyDataBytes_698(&(P_DataBuf[V_DataOff + 1]), &(P_DataBuf[V_DataOff]), V_usLen698);
							V_DataOff += (V_usLen698);
						}
						else
						{
							V_DataOff += (V_usLen698 + 1);
						}
						V_ucLen645 += V_ucLen;
					}
					else
					{
						return C_MaxResponseLen_ERR;
					}
				}
			}
			if(V_return == C_OK)
			{
				V_Len -= (V_usLen698 + 1);
			}
			else if(V_return == C_MaxResponseLen_ERR)	/* ���Ȳ���ֱ���˳�*/
			{
				break;
			}
			P_DIFor645->V_ucOAD += 0x00000001;
		}
	}
	if(V_return != C_MaxResponseLen_ERR)				/*���ǿռ䲻����ʣ�೤�ȼ�ȥ��OAD��ȡ���ݳ���*/
	{
		if(V_DataOff >= 256)
		{
			for( j = 0; j < V_DataOff; j++ )
			{
				P_DataBuf[V_DataOff - j + 1] = P_DataBuf[V_DataOff - j - 1];
			}
			P_DataBuf[2] = (uchar8)( V_DataOff - 1 );
			P_DataBuf[1] = (uchar8)( ( V_DataOff - 1 ) >> 8 );
			P_DataBuf[0] = 0x82;
			V_DataOff += 2;
		}
		else if(V_DataOff > 127)
		{
			for( j = 0; j < V_DataOff; j++ )
			{
				P_DataBuf[V_DataOff - j] = P_DataBuf[V_DataOff - j - 1];
			}
			P_DataBuf[1] = (uchar8)(V_DataOff - 1);
			P_DataBuf[0] = 0x81;
			V_DataOff += 1;
		}
		else
		{
			P_DataBuf[0] = (uchar8)(V_DataOff - 1);
		}

		*P_DataOff = V_DataOff;
	}
	return V_return;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 InF_Judge_EventOAD_OP(ulong32 V_OAD,uchar8 *pEventLineNO)
�����������ж��Ƿ�����¼���¼������������,�����¼���¼��Ӧ����кŷ���
����������������Ա�ʶ��
������������ӳɹ�C_OK,ʧ��C_Err
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 InF_Judge_EventOAD_OP(ulong32 V_OAD, uchar8 *pEventLineNO)
{
	ushort16	i;
	uchar8		V_usObject;

	V_usObject = (uchar8)(V_OAD >> 16);			/*ȡ�����ʶ*/

	for( i = 0; i < C_Event_OIBTableLen; i++ )
	{
		if( V_usObject == Event_OIBTable[i].OIB )
		{
			*pEventLineNO = i;
			break;
		}
	}
	if( i < C_Event_OIBTableLen )
	{
		if( ( V_OAD & 0xFFFFFF00 ) == ( Event_OIBTable[i].RelatedOAD & 0xFFFFFF00 ) )
		{
			return C_OK;
		}
		else
		{
			return C_Error;
		}
	}
	else
	{
		return C_Error;
	}
}
/*******************************************************************************
����ԭ�ͣ�uchar8 InF_Judge_FreezeOAD_OP(ulong32 V_OAD,uchar8 *pEventLineNO)
�����������ж��Ƿ�����¼���¼������������,�����¼���¼��Ӧ����кŷ���
����������������Ա�ʶ��
������������ӳɹ�C_OK,ʧ��C_Err
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 InF_Judge_FreezeOAD_OP(ulong32 V_OAD, uchar8 *pEventLineNO)
{
	ushort16	i;
	uchar8		V_usObject;

	V_usObject = (uchar8)(V_OAD >> 16);			/*ȡ�����ʶ*/
    *pEventLineNO = 0;
	for( i = 0; i < C_Freeze_OIBTableLen; i++ )
	{
		if(V_usObject == Freeze_OIBTable[i].OIB)
		{
			break;
		}
	}
	if(i < C_Event_OIBTableLen)
	{
		if( ( V_OAD & 0xFFFFFF00 ) == ( 0x50000000 | 0x00000300 | ( V_usObject << 16 ) ) )
		{
			return C_OK;
		}
		else
		{
			return C_Error;
		}
	}
	else
	{
		return C_Error;
	}
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_EventOADADD(WtOI_Rt_T V_OAD)
��������������һ����������
���������V_OAD��ȡ����
���������
���ز��������ӳɹ�C_OK,ʧ��C_Err
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_EventOADADD(WtOI_Rt_T V_OAD)
{
	ushort16	i, V_usLen, V_usDataEncode;
	Str_Event_OIB1	Str_EventInfo;
	uchar8	V_Data[C_RelatedOADBuf_Len], V_usNum;
	ulong32	V_ulRelatedOAD;
	uchar8	V_usObject, V_ucTurn, V_ucNature;
	uchar8	W_Safe_Flag = C_W_SafeFlag_1;
	Str_Comm_645 V_645Frame;

	V_usObject = (uchar8)(V_OAD.WtOI >> 16);												/*ȡ�����ʶ*/

	for( i = 0; i < C_Event_OIBTableLen; i++ )
	{
		if( V_usObject == Event_OIBTable[i].OIB )
		{
			break;
		}
	}
	Str_EventInfo = Event_OIBTable[i];
	V_usLen = CLLoss_Vol_OADTabLen;
	V_ucTurn = InF_Read_Data(Str_EventInfo.RelatedOAD_T, &V_usNum, &V_usLen, &V_usDataEncode);	/*��������������*/
	if( V_ucTurn != C_OK )
	{
		V_usNum = 0;
	}
	if( V_usNum >= C_EventMAXRelatedOAD )
	{
		V_ucTurn = C_OtherErr_DAR;
		return V_ucTurn;
	}
	W_Safe_Flag = W_Safe_Flag | C_W_SafeFlag_2;

	V_usLen = 120;
	V_ucTurn = InF_ReadOADTab_Data(Str_EventInfo.RelatedOAD, V_Data, &V_usLen);
	if(V_ucTurn != C_OK)
	{
		V_usNum = 0;
	}
	W_Safe_Flag = W_Safe_Flag | C_W_SafeFlag_3;

	if( ( V_usLen == ( V_usNum * 2 ) ) || ( V_usNum == 0 ) )								/*����OAD���������ݳ��ȶ�Ӧ*/
	{
		V_ulRelatedOAD = PF_Buffer4ToUlong32_698(&V_OAD.Wt_Data[1]);
		V_ucNature = (uchar8)(V_ulRelatedOAD >> 8);
		V_ucNature &= 0xE0;
		V_ulRelatedOAD &= 0xFFFF1FFF;														/*��������������*/

		for( i = 0; i < Str_FrozenConvert_Table_Len; i++)
		{
			if(Str_FrozenConvert_Table[i].V_ulOAD == V_ulRelatedOAD)
			{
				break;
			}
		}
	}
	if(i < Str_FrozenConvert_Table_Len)
	{
		V_Data[V_usNum * 2] = (uchar8)i;
		V_Data[V_usNum * 2 + 1] = (uchar8)(i >> 8);
		V_Data[V_usNum * 2 + 1] |= V_ucNature;
		if( SF_JudgeSameRealatedOAD( V_Data, &V_Data[V_usNum * 2], V_usNum, 0 ) != C_OK )
		{
			return C_OtherErr_DAR;
		}
		V_usNum++;

		V_ucTurn = InF_Write_Data(C_Msg_Communication, Str_EventInfo.RelatedOAD, V_Data, V_usNum * 2, W_Safe_Flag);

		V_ucTurn = InF_Write_Data(C_Msg_Communication, Str_EventInfo.RelatedOAD_T, &V_usNum, CLI_Free_OADTabLen_T, W_Safe_Flag);
	}
	else
	{
		V_ucTurn = C_OtherErr_DAR;
	}

	if(V_ucTurn == C_OK)
	{
		SF_EventClear_698(V_OAD.WtOI, &V_645Frame, C_NotProgram);
	}
	return V_ucTurn;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_EventOADDelete(WtOI_Rt_T V_OAD)
����������ɾ��һ����������
���������V_OAD��ȡ����
������������ӳɹ�C_OK,ʧ��C_Err
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_EventOADDelete(WtOI_Rt_T V_OAD)
{
	ushort16	i, V_usLen, V_usOADNO, j, V_usDataEncode;
	Str_Event_OIB1	Str_EventInfo;
	uchar8	V_Data[C_RelatedOADBuf_Len], V_usNum, V_DataTemp[C_RelatedOADBuf_Len], V_Flag = 0;
	ulong32 V_ulRelatedOAD, V_OADTemp;
	uchar8	V_usObject, V_ucTurn;
	uchar8	W_Safe_Flag = C_W_SafeFlag_1;
    Str_Comm_645 V_645Frame;
    uchar8 V_Attribute = 0, k = 0;

	V_usObject = (uchar8)(V_OAD.WtOI >> 16);			/*ȡ�����ʶ*/

	for( i = 0; i < C_Event_OIBTableLen; i++ )
	{
		if(V_usObject==Event_OIBTable[i].OIB)
		{
			break;
		}
	}
	Str_EventInfo = Event_OIBTable[i];
	V_usLen = CLLoss_Vol_OADTabLen;
	V_ucTurn = InF_Read_Data(Str_EventInfo.RelatedOAD_T, &V_usNum, &V_usLen, &V_usDataEncode);
	if( V_ucTurn == C_OK )
	{
		W_Safe_Flag = W_Safe_Flag | C_W_SafeFlag_2;

		V_usLen = 120;
		V_ucTurn = InF_ReadOADTab_Data(Str_EventInfo.RelatedOAD, V_Data, &V_usLen);
		if( V_ucTurn == C_OK )
		{
			W_Safe_Flag = W_Safe_Flag | C_W_SafeFlag_3;

			if( V_usLen == ( V_usNum * 2 ) )					/*����OAD���������ݳ��ȶ�Ӧ*/
			{
				if( V_OAD.Wt_Data[0] != C_OAD )
				{
					return C_TypeErr_DAR;
				}
				V_ulRelatedOAD = PF_Buffer4ToUlong32_698(&V_OAD.Wt_Data[1]);
                V_OADTemp = V_ulRelatedOAD;
				V_ulRelatedOAD &= 0xFFFF1FFF;					/*��������������*/
				for( i = 0; i < Str_FrozenConvert_Table_Len; i++ )
				{
					if(Str_FrozenConvert_Table[i].V_ulOAD == V_ulRelatedOAD)
					{
						V_usOADNO = i;
						break;
					}
				}
				if(i >= Str_FrozenConvert_Table_Len)
				{
					V_ucTurn = C_OtherErr_DAR;
					return V_ucTurn;
				}
			}
			for( i = 0; i < ( V_usNum * 2 ); i++ )
			{
                PF_Buffer2ToUshort16(&V_Data[i], &j);
                V_Attribute = (uchar8)( ( j >> 8 ) & 0xE0 );	/*��ȡ�¼������б��е��¼�����*/
                j &= 0x1FFF;
                if( ( j == V_usOADNO ) && ( V_Attribute == ( ( (uchar8)( V_OADTemp >> 8 ) ) & 0xE0 ) ) )
				{
					i += 1;
                    V_Flag++;
                    continue;
				}
                V_DataTemp[k] = V_Data[i];
                V_DataTemp[k + 1] = V_Data[i + 1];
                i += 1;
                k += 2;
			}
			if(V_Flag != 0)
			{
                V_usNum = V_usNum - V_Flag;
				V_ucTurn = InF_Write_Data(C_Msg_Communication, Str_EventInfo.RelatedOAD, V_DataTemp, V_usNum * 2, W_Safe_Flag);
				V_ucTurn = InF_Write_Data(C_Msg_Communication, Str_EventInfo.RelatedOAD_T, &V_usNum, CLI_Free_OADTabLen_T, W_Safe_Flag);
			}
			else
			{
				V_ucTurn = C_OtherErr_DAR;
				return V_ucTurn;
			}
		}
	}

	if(V_ucTurn != C_OK)
	{
		V_ucTurn = C_OtherErr_DAR;
	}
	if(V_ucTurn == C_OK)
	{
		SF_EventClear_698(V_OAD.WtOI, &V_645Frame, C_NotProgram);
	}
	return V_ucTurn;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_EventOADDeleteAll(WtOI_Rt_T V_OAD)
����������ɾ����������
���������V_OAD��ȡ����
������������ӳɹ�C_OK,ʧ��C_Err
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_EventOADDeleteAll(WtOI_Rt_T V_OAD)
{
	ushort16	i;
	Str_Event_OIB1	Str_EventInfo;
	uchar8	V_Data[C_RelatedOADBuf_Len] = {0};
	uchar8	V_usObject, V_ucTurn;
	uchar8	W_Safe_Flag = C_W_SafeFlag_1;
	Str_Comm_645 V_645Frame;

	if( InF_JudgeIJTimer() != C_OK )
	{
		return C_OtherErr_DAR;
	}
	V_usObject = (uchar8)(V_OAD.WtOI >> 16);	/*ȡ�����ʶ*/

	for( i = 0; i < C_Event_OIBTableLen; i++ )
	{
		if( V_usObject == Event_OIBTable[i].OIB )
		{
			break;
		}
	}
	Str_EventInfo = Event_OIBTable[i];

	W_Safe_Flag = W_Safe_Flag | C_W_SafeFlag_2;
	W_Safe_Flag = W_Safe_Flag | C_W_SafeFlag_3;
	V_ucTurn = InF_Write_Data(C_Msg_Communication, Str_EventInfo.RelatedOAD, V_Data, C_EventMAXRelatedOAD * 2, W_Safe_Flag);
	if(V_ucTurn != C_OK)
	{
		V_ucTurn = C_OtherErr_DAR;
		return V_ucTurn;
	}
	V_ucTurn = InF_Write_Data(C_Msg_Communication, Str_EventInfo.RelatedOAD_T, V_Data, CLVariableAssociatedOADNum, W_Safe_Flag);

	if(V_ucTurn == C_OK)
	{
		SF_EventClear_698(V_OAD.WtOI,&V_645Frame,C_NotProgram);
	}

	return V_ucTurn;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_FreezeOADADD(WtOI_Rt_T V_OAD)
��������������һ����������
���������	V_OAD��ȡ����
������������ӳɹ�C_OK,ʧ��C_Err
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_FreezeOADADD(WtOI_Rt_T V_OAD)
{
	ushort16	i, V_usLen, V_usAddOADTime, V_ulStoreNum, V_usDataEncode;
	Str_Event_OIB2	Str_FreezeInfo;
	uchar8	V_Data[C_RelatedOADBuf_Len], V_usNum;
	ulong32	V_ulRelatedOAD;
	uchar8	V_usObject, V_ucTurn, V_ucNature;
	uchar8	W_Safe_Flag = C_W_SafeFlag_1;

	V_usObject = (uchar8)(V_OAD.WtOI >> 16);											/*ȡ�����ʶ*/

	for( i = 0; i < C_Freeze_OIBTableLen; i++ )
	{
		if( V_usObject == Freeze_OIBTable[i].OIB )
		{
			break;
		}
	}
	Str_FreezeInfo = Freeze_OIBTable[i];
	V_usLen = CLI_Free_OADTabLen_T;
	V_ucTurn = InF_Read_Data(Str_FreezeInfo.RelatedOAD_T, &V_usNum, &V_usLen, &V_usDataEncode);/*��������������*/
	if( V_ucTurn != C_OK )
	{
		V_usNum = 0;
	}
	if( V_usNum >= C_FreezeMAXRelatedOAD )
	{
		V_ucTurn = C_OtherErr_DAR;
		return V_ucTurn;
	}

	W_Safe_Flag = W_Safe_Flag | C_W_SafeFlag_2;

	V_usLen = V_usNum * 6;
	V_ucTurn = InF_ReadOADTab_Data(Str_FreezeInfo.RelatedOAD, V_Data, &V_usLen);
	if(V_ucTurn != C_OK)
	{
		V_usLen = 0;
		V_usNum = 0;
	}
	W_Safe_Flag = W_Safe_Flag | C_W_SafeFlag_3;

	if( V_usLen == ( V_usNum * 6 ) )													/*����OAD���������ݳ��ȶ�Ӧ*/
	{
		if( V_OAD.Wt_Data[0] != C_structure )
		{
			return	C_TypeErr_DAR;
		}
		if( V_OAD.Wt_Data[2] != C_long_unsigned )
		{
			return	C_TypeErr_DAR;
		}
		V_usAddOADTime = V_OAD.Wt_Data[3];
		V_usAddOADTime <<= 8;
		V_usAddOADTime |= V_OAD.Wt_Data[4];
		if( V_OAD.Wt_Data[5] != C_OAD )
		{
			return	C_TypeErr_DAR;
		}

		V_ulRelatedOAD = PF_Buffer4ToUlong32_698(&V_OAD.Wt_Data[6]);
		V_ucNature = (uchar8)( V_ulRelatedOAD >> 8 );
		V_ucNature &= 0xE0;
		V_ulRelatedOAD &= 0xFFFF1FFF;													/*��������������*/

		if( V_OAD.Wt_Data[10] != C_long_unsigned )
		{
			return	C_TypeErr_DAR;
		}
		V_ulStoreNum = V_OAD.Wt_Data[11];
		V_ulStoreNum <<= 8;
		V_ulStoreNum |= V_OAD.Wt_Data[12];

		for( i = 0; i < Str_FrozenConvert_Table_Len; i++ )
		{
			if( Str_FrozenConvert_Table[i].V_ulOAD == V_ulRelatedOAD )
			{
				break;
			}
		}
	}
	if( i < Str_FrozenConvert_Table_Len )
	{
		/*���˷��Ӷ��ᣬ�������᷽���ű���Ϊ0*/
		if( V_usObject  != 2 )
		{
			if( V_ucNature != 0 )
			{
				return C_RWForbid_DAR;
			}
		}
		V_Data[V_usNum * 6] = (uchar8)i;
		V_Data[V_usNum * 6 + 1] = (uchar8)(i >> 8);
		V_Data[V_usNum * 6 + 1] |= V_ucNature;
		if( SF_JudgeSameRealatedOAD( V_Data, &V_Data[V_usNum * 6], V_usNum, 1 ) != C_OK )
		{
			return C_RWForbid_DAR;
		}
		PF_Ushort16ToBuffer2(&V_Data[V_usNum *   6 + 1 + 1], &V_usAddOADTime);
		PF_Ushort16ToBuffer2(&V_Data[V_usNum * 6 + 1 + 1 + 2], &V_ulStoreNum);
		/*���Ӷ��ᡢ����һ�µģ�Ҫ�󶳽�����һ�£����������Զ��ᣬ��������һ��*/
		if( SF_JudgeSameRealatedOADCycle( V_Data, &V_Data[V_usNum * 6], V_usNum, (uchar8)V_usObject ) != C_OK )
		{
			return C_RWForbid_DAR;
		}
		/*���Ӷ��ᡢ����һ�µģ�Ҫ��洢���һ�£����������Զ��ᣬ����洢���һ��*/
		if(SF_JudgeSameRealatedOADStoreNum( V_Data, &V_Data[V_usNum * 6], V_usNum, (uchar8)V_usObject ) != C_OK )
		{
			return C_RWForbid_DAR;
		}
		V_usNum++;

		V_ucTurn = InF_Write_Data(C_Msg_Communication, Str_FreezeInfo.RelatedOAD_T, &V_usNum, CLI_Free_OADTabLen_T, W_Safe_Flag);
		V_ucTurn = InF_Write_Data(C_Msg_Communication, Str_FreezeInfo.RelatedOAD, V_Data, V_usNum * 6, W_Safe_Flag);
	}
	else
	{
		V_ucTurn = C_OtherErr_DAR;
	}

	if(V_ucTurn == C_OK)
	{
		V_ucTurn = SF_Clear_Freeze(C_ClearMeterSafeFlag, V_usObject);
	}
	return V_ucTurn;
}
/*******************************************************************************
����ԭ�� SF_FreezeOADSet
�������� ���ù�������
������� V_ucFlag 0x68��ʾ06������������;
				  0x00��ʾ07������ӹ������ԣ�
������� ���ӳɹ�C_OK,ʧ��C_Err
���ز���
ȫ�ֱ��� SV_Comm_Parse/SV_Comm_Parse_Local
������ע
*******************************************************************************/
uchar8 SF_FreezeOADSet(WtOI_Rt_T V_OAD, uchar8 V_ucFlag)
{
	ushort16 i, j, V_usNumADD, V_usLen, V_usOADTime, V_ulStoreNum, V_usDataEncode;
	Str_Event_OIB2 Str_FreezeInfo;
	uchar8 V_Data[C_RelatedOADBuf_Len], V_usNum;
	ulong32 V_ulRelatedOAD;
	uchar8 V_usObject, V_ucTurn, V_ucNature;
	uchar8 W_Safe_Flag = C_W_SafeFlag_1;
	ushort16 V_usOff = 0;

    if( ( (uchar8)(V_OAD.WtOI) ) != 0x00 )
	{
		return C_RWForbid_DAR;
	}

	V_usObject = (uchar8)(V_OAD.WtOI >> 16);		/*ȡ�����ʶ*/

	for( i = 0; i < C_Freeze_OIBTableLen; i ++ )
	{
		if(V_usObject == Freeze_OIBTable[i].OIB)
		{
			break;
		}
	}
	Str_FreezeInfo = Freeze_OIBTable[i];
	V_usLen = CLI_Free_OADTabLen_T;
	V_ucTurn = InF_Read_Data(Str_FreezeInfo.RelatedOAD_T, &V_usNum, &V_usLen, &V_usDataEncode);
	if( V_ucTurn != C_OK )
	{
		V_usNum = 0;
	}

	if( V_ucFlag != 0x68 )							/*set��������ʱ�����ж�ԭ�й�������OAD����*/
	{
		if( V_usNum > C_FreezeMAXRelatedOAD )
		{
			V_ucTurn = C_RWForbid_DAR;
			return V_ucTurn;
		}
	}

	W_Safe_Flag = W_Safe_Flag | C_W_SafeFlag_2;
	V_usLen = V_usNum * 6;
	V_ucTurn = InF_ReadOADTab_Data(Str_FreezeInfo.RelatedOAD, V_Data, &V_usLen);
	if( V_ucTurn != C_OK )
	{
		V_usLen = 0;
	}

	W_Safe_Flag = W_Safe_Flag | C_W_SafeFlag_3;
	if( V_usLen != ( V_usNum * 6 ) )				/*����OAD���������ݳ��ȶ�Ӧ*/
	{
		V_usNum = 0;
	}

	if( V_ucFlag == 0x68 )							/*set��������ʱ��������ԭ���Ĺ������ԣ�ֱ������*/
	{
		V_usNum =0;
	}

	i = V_usNum;

	if( V_OAD.Wt_Data[V_usOff] == 0x01 )
	{
		V_usOff ++;
		V_usNumADD = V_OAD.Wt_Data[V_usOff];
		V_usOff++;
	}
	else
	{
		return	C_TypeErr_DAR;
	}

	if( ( V_usNumADD + V_usNum ) > C_FreezeMAXRelatedOAD )
	{
		V_ucTurn = C_OtherErr_DAR;
		return V_ucTurn;
	}

	for( ; i < ( V_usNumADD + V_usNum ); i++ )
	{
		if( V_OAD.Wt_Data[V_usOff] != C_structure )
		{
			return	C_TypeErr_DAR;
		}

		V_usOff += 2;

		if( V_OAD.Wt_Data[V_usOff] != C_long_unsigned )
		{
			return C_TypeErr_DAR;
		}

		V_usOff ++;
		V_usOADTime = V_OAD.Wt_Data[V_usOff];
		V_usOADTime <<= 8;
		V_usOff ++;
		V_usOADTime |= V_OAD.Wt_Data[V_usOff];		/*��������*/

		V_usOff ++;
		if( V_OAD.Wt_Data[V_usOff] != C_OAD )
		{
			return	C_TypeErr_DAR;
		}

		V_usOff ++;
		V_ulRelatedOAD = PF_Buffer4ToUlong32_698(&V_OAD.Wt_Data[V_usOff]);	/*�������ŵ�OAD���ݱ�ʶ*/

		V_usOff += 3;
		V_ucNature = (uchar8)(V_ulRelatedOAD >> 8);
		V_ucNature &= 0xE0;							/*���᷽����*/

		V_ulRelatedOAD &= 0xFFFF1FFF;				/*�������������ֵõ�����OAD���ݱ�ʶ*/

		V_usOff ++;
		if( V_OAD.Wt_Data[V_usOff] != C_long_unsigned )
		{
			return	C_TypeErr_DAR;
		}

		V_usOff ++;
		V_ulStoreNum = V_OAD.Wt_Data[V_usOff];
		V_ulStoreNum <<= 8;
		V_usOff ++;
		V_ulStoreNum |= V_OAD.Wt_Data[V_usOff];		/*�洢���*/

		V_usOff ++;

		for( j = 0; j < Str_FrozenConvert_Table_Len; j ++ )
		{
			if(Str_FrozenConvert_Table[j].V_ulOAD == V_ulRelatedOAD)
			{
				break;
			}
		}

		if( j < Str_FrozenConvert_Table_Len )
		{
			/*���˷��Ӷ��ᣬ�������᷽���ű���Ϊ0*/
			if( V_usObject != 2 )
			{
				if( V_ucNature != 0 )
				{
					return C_RWForbid_DAR;
				}
			}

			/*�ж���ӵĹ���OAD�Ƿ���ͬ*/
			V_Data[i * 6] = (uchar8)j;
			V_Data[i * 6 + 1] = (uchar8)(j >> 8);
			V_Data[i * 6 + 1] |= V_ucNature;
			if( SF_JudgeSameRealatedOAD( V_Data, &V_Data[i * 6], i, 1 ) != C_OK )
			{
				return C_RWForbid_DAR;
			}

			PF_Ushort16ToBuffer2(&V_Data[i * 6 + 1 + 1], &V_usOADTime);				/*��������*/
			PF_Ushort16ToBuffer2(&V_Data[i * 6 + 1 + 1 + 2], &V_ulStoreNum);		/*�洢���*/

			switch(V_usObject)
			{
				case 0x00:							/*�������Զ��᣺˲ʱ����*/
				{
					if(V_ulStoreNum > 3)			/*�洢���*/
					{
						return C_RWForbid_DAR;
					}
				}break;

				case 0x02:							/*�����Զ��᣺���Ӷ���*/
				{
					if(V_ulStoreNum > 35040)		/*�洢���*/
					{
						return C_RWForbid_DAR;
					}
				}break;

				case 0x03:							/*�����Զ��᣺Сʱ����(���㶳��)*/
				{
					if(V_ulStoreNum > 254)			/*�洢���*/
					{
						return C_RWForbid_DAR;
					}
				}break;

				case 0x04:							/*�����Զ��᣺�ն���*/
				{
					if(V_ulStoreNum > 365)			/*�洢���*/
					{
						return C_RWForbid_DAR;
					}
				}break;

				case 0x05:							/*�������Զ��᣺�����ն���*/
				{
					if(V_ulStoreNum > 12)			/*�洢���*/
					{
						return C_RWForbid_DAR;
					}
				}break;

				case 0x06:							/*�������Զ��᣺�¶���*/
				{
					if(V_ulStoreNum > 24)			/*�洢���*/
					{
						return C_RWForbid_DAR;
					}
				}break;

				case 0x08:							/*�������Զ��᣺�л�����*/
				case 0x09:
				case 0x0A:
				case 0x0B:
				{
					if(V_ulStoreNum > 2)			/*�洢���*/
					{
						return C_RWForbid_DAR;
					}
				}break;

				case 0x11:							/*�������Զ��᣺���ݽ��㶳��*/
				{
					if(V_ulStoreNum > 4)			/*�洢���*/
					{
						return C_RWForbid_DAR;
					}
				}break;

				default:
				{
					return C_RWForbid_DAR;
				}break;
			}

			/*���Ӷ��ᡢ������һ�µģ�Ҫ�󶳽�����һ�£����������Զ��ᣬ��������һ��*/
			if( SF_JudgeSameRealatedOADCycle( V_Data, &V_Data[i * 6], i, (uchar8)V_usObject ) != C_OK )
			{
				return C_RWForbid_DAR;
			}

			/*���Ӷ��ᡢ����һ�µģ�Ҫ��洢���һ�£����������Զ��ᣬ����洢���һ��*/
			if( SF_JudgeSameRealatedOADStoreNum( V_Data, &V_Data[i * 6], i, (uchar8)V_usObject) != C_OK )
			{
				return C_RWForbid_DAR;
			}
		}
		else
		{
			V_ucTurn = C_OtherErr_DAR;
			return V_ucTurn;
		}
	}

	V_usNum += V_usNumADD;
	V_ucTurn = InF_Write_Data(C_Msg_Communication, Str_FreezeInfo.RelatedOAD_T, &V_usNum, CLI_Free_OADTabLen_T, W_Safe_Flag);
	V_ucTurn = InF_Write_Data(C_Msg_Communication, Str_FreezeInfo.RelatedOAD, V_Data, (V_usNum) * 6, W_Safe_Flag);

	if(V_ucTurn == C_OK)
	{
		V_ucTurn = SF_Clear_Freeze(C_ClearMeterSafeFlag, V_usObject);
	}

	return V_ucTurn;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_FreezeOADDelete(WtOI_Rt_T V_OAD)
����������ɾ��һ����������
���������V_OAD��ȡ����
������������ӳɹ�C_OK,ʧ��C_Err
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_FreezeOADDelete(WtOI_Rt_T V_OAD)
{
	ushort16	i, V_usLen, V_usOADNO, j, V_usDataEncode;
	Str_Event_OIB2	Str_FreezeInfo;
	uchar8	V_Data[C_RelatedOADBuf_Len], V_usNum;
	ulong32 V_ulRelatedOAD;
	uchar8	V_usObject, V_ucTurn;
	uchar8	W_Safe_Flag = C_W_SafeFlag_1;

	V_usObject = (uchar8)(V_OAD.WtOI >> 16);		/*ȡ�����ʶ*/

	for( i = 0; i < C_Freeze_OIBTableLen; i++ )
	{
		if( V_usObject == Freeze_OIBTable[i].OIB )
		{
			break;
		}
	}
	Str_FreezeInfo = Freeze_OIBTable[i];
	V_usLen = CLI_Free_OADTabLen_T;
	V_ucTurn = InF_Read_Data(Str_FreezeInfo.RelatedOAD_T, &V_usNum, &V_usLen, &V_usDataEncode );
	if( V_ucTurn == C_OK )
	{
		W_Safe_Flag = W_Safe_Flag | C_W_SafeFlag_2;

		V_usLen = V_usNum * 6;
		V_ucTurn = InF_ReadOADTab_Data(Str_FreezeInfo.RelatedOAD, V_Data, &V_usLen);
		if(V_ucTurn == C_OK)
		{
			W_Safe_Flag = W_Safe_Flag | C_W_SafeFlag_3;

			if( V_usLen == ( V_usNum * 6 ) )			/*����OAD���������ݳ��ȶ�Ӧ*/
			{
				if( V_OAD.Wt_Data[0] != C_OAD )
				{
					V_ucTurn = C_TypeErr_DAR;
					return V_ucTurn;
				}
				V_ulRelatedOAD = PF_Buffer4ToUlong32_698(&V_OAD.Wt_Data[1]);
				V_ulRelatedOAD &= 0xFFFF1FFF;			/*��������������*/
				for( i = 0; i < Str_FrozenConvert_Table_Len; i++ )
				{
					if( Str_FrozenConvert_Table[i].V_ulOAD == V_ulRelatedOAD )
					{
						V_usOADNO = i;
						break;
					}
				}
				if( i >= Str_FrozenConvert_Table_Len )
				{
					V_ucTurn = C_OtherErr_DAR;
					return V_ucTurn;
				}
			}
			for( i = 0; i < ( V_usNum * 6 ); i++ )
			{
				j = V_Data[i + 1];
				j &= 0x1F;
				j <<=8;
				j |= V_Data[i];
				if( j == V_usOADNO )
				{
					break;
				}
				i += 5;
			}
			if( i < ( V_usNum * 6 ) )
			{
				for( ; i < ( V_usNum * 6 ); i++ )
				{
					V_Data[i] = V_Data[i + 6] ;
				}
				V_usNum--;
				V_ucTurn = InF_Write_Data(C_Msg_Communication, Str_FreezeInfo.RelatedOAD_T, &V_usNum, CLI_Free_OADTabLen_T, W_Safe_Flag);
				V_ucTurn = InF_Write_Data(C_Msg_Communication, Str_FreezeInfo.RelatedOAD, V_Data, V_usNum * 6, W_Safe_Flag);
			}
			else
			{
				V_ucTurn = C_OtherErr_DAR;
				return V_ucTurn;
			}
		}
	}

	if(V_ucTurn != C_OK)
	{
		V_ucTurn = C_OtherErr_DAR;
	}
	if(V_ucTurn == C_OK)
	{
		V_ucTurn = SF_Clear_Freeze(C_ClearMeterSafeFlag, V_usObject);
	}
	return V_ucTurn;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_FreezeOADDeleteAll(WtOI_Rt_T V_OAD)
����������ɾ����������
���������	V_OAD��ȡ����
������������ӳɹ�C_OK,ʧ��C_Err
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_FreezeOADDeleteAll(WtOI_Rt_T V_OAD)
{
	ushort16	i, V_usLen, V_usDataEncode;
	Str_Event_OIB2	Str_FreezeInfo;
	uchar8	V_Data[C_RelatedOADBuf_Len] = {0}, V_usNum;
	uchar8	V_usObject, V_ucTurn;
	uchar8	W_Safe_Flag = C_W_SafeFlag_1;

	if( V_OAD.Wt_Data[0] != 0 )
	{
		return C_OtherErr_DAR;
	}
	V_usObject = (uchar8)(V_OAD.WtOI >> 16);		/*ȡ�����ʶ*/

	for( i = 0; i < C_Freeze_OIBTableLen; i++ )
	{
		if( V_usObject == Freeze_OIBTable[i].OIB )
		{
			break;
		}
	}
	Str_FreezeInfo = Freeze_OIBTable[i];
	V_usLen = CLI_Free_OADTabLen_T;
	V_ucTurn = InF_Read_Data(Str_FreezeInfo.RelatedOAD_T, &V_usNum, &V_usLen, &V_usDataEncode);
	if( V_ucTurn != C_OK )
	{
		V_usNum = C_FreezeMAXRelatedOAD;
	}

	W_Safe_Flag = W_Safe_Flag | C_W_SafeFlag_2;
	W_Safe_Flag = W_Safe_Flag | C_W_SafeFlag_3;
	V_ucTurn = InF_Write_Data(C_Msg_Communication, Str_FreezeInfo.RelatedOAD_T, V_Data, CLI_Free_OADTabLen_T, W_Safe_Flag);
	V_ucTurn = InF_Write_Data(C_Msg_Communication, Str_FreezeInfo.RelatedOAD, V_Data, C_FreezeMAXRelatedOAD * 6, W_Safe_Flag);

	if( V_ucTurn == C_OK )
	{
		V_ucTurn = SF_Clear_Freeze(C_ClearMeterSafeFlag, V_usObject);
	}
	return V_ucTurn;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_SecurityOIDeleteAll(WtOI_Rt_T V_OAD)
����������ɾ������
���������V_OAD��ȡ����
������������ӳɹ�C_OK,ʧ��C_Err
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_SecurityOIDeleteAll(WtOI_Rt_T V_OAD)
{
	uchar8	V_Data[1024] = {0};
	uchar8	V_ucTurn;
	uchar8	W_Safe_Flag = C_W_SafeFlag_1;

	W_Safe_Flag = W_Safe_Flag | C_W_SafeFlag_2;
	W_Safe_Flag = W_Safe_Flag | C_W_SafeFlag_3;
	V_ucTurn = InF_Write_Data(C_Msg_Communication, CSafeModeParaNat3, V_Data, CLSafeModeParaNat3, W_Safe_Flag);
	if(V_ucTurn != C_OK)
	{
		V_ucTurn = C_OtherErr_DAR;
		return V_ucTurn;
	}
	V_ucTurn = InF_Write_Data(C_Msg_Communication, CSafeModeParaNat3_Num, V_Data, CLSafeModeParaNat3_Num, W_Safe_Flag);

	return V_ucTurn;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_SecurityOIDelete(WtOI_Rt_T V_OAD)
����������ɾ��һ������
���������V_OAD��ȡ����
������������ӳɹ�C_OK,ʧ��C_Err
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_SecurityOIDelete(WtOI_Rt_T V_OAD)
{
	ushort16	i, V_usLen, V_usDataEncode;
	uchar8	V_Data[1024] = {0}, V_usNum;
	uchar8	V_ucTurn;
	uchar8	W_Safe_Flag = C_W_SafeFlag_1;


	V_usLen = CLSafeModeParaNat3_Num;
	V_ucTurn = InF_Read_Data(CSafeModeParaNat3_Num, &V_usNum, &V_usLen, &V_usDataEncode);
	if( V_ucTurn != C_OK )
	{
		V_ucTurn = C_OtherErr_DAR;
		return V_ucTurn;
	}

	W_Safe_Flag = W_Safe_Flag | C_W_SafeFlag_2;

	V_usLen = CLSafeModeParaNat3;
	V_ucTurn = InF_ReadOADTab_Data(CSafeModeParaNat3, V_Data, &V_usLen);
	if( V_ucTurn == C_OK )
	{
		W_Safe_Flag = W_Safe_Flag | C_W_SafeFlag_3;
		if( V_OAD.Wt_Data[0] != C_OI )
		{
			V_ucTurn = C_OtherErr_DAR;
			return V_ucTurn;
		}

		for( i = 0; i < ( V_usNum * 4 ); i++ )
		{
			if( ( V_OAD.Wt_Data[1] == V_Data[i + 1] ) && ( V_OAD.Wt_Data[2] == V_Data[i] ) )
			{
				break;
			}
			i += 3;
		}
		if( i < ( V_usNum * 4 ) )
		{
			for( ; i < ( V_usNum * 4 ); i++ )
			{
				V_Data[i] = V_Data[i + 4] ;
			}
			V_usNum--;
			V_ucTurn = InF_Write_Data(C_Msg_Communication, CSafeModeParaNat3, V_Data, CLSafeModeParaNat3, W_Safe_Flag);
            if( V_ucTurn != C_OK )
            {
                V_ucTurn = C_OtherErr_DAR;
                return V_ucTurn;
            }
			V_ucTurn = InF_Write_Data(C_Msg_Communication, CSafeModeParaNat3_Num, &V_usNum, CLSafeModeParaNat3_Num, W_Safe_Flag);
		}
		else
		{
			V_ucTurn = C_OtherErr_DAR;
			return V_ucTurn;
		}
	}

	if(V_ucTurn != C_OK)
	{
		V_ucTurn = C_OtherErr_DAR;
	}

	return V_ucTurn;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_SecurityOISet(WtOI_Rt_T V_OAD)
�������������ù�������
���������V_OAD��ȡ����
�����������
���ز��������ӳɹ�C_OK,ʧ��C_Err
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_SecurityOISet(WtOI_Rt_T V_OAD)
{
	ushort16	i, V_usNumADD, V_usLen, V_usDataEncode;
	uchar8	V_usNum, V_Data[1024] = {0}, j = 0,V_MaxLen = CLSafeModeParaNat3 / 4;
	uchar8	V_ucTurn;
	uchar8	W_Safe_Flag = C_W_SafeFlag_1;

	V_usLen = CLSafeModeParaNat3_Num;
	V_ucTurn = InF_Read_Data(CSafeModeParaNat3_Num, &V_usNum, &V_usLen, &V_usDataEncode);
    if( V_usNum == V_MaxLen )
    {
        V_ucTurn = C_OtherErr_DAR;
        return V_ucTurn;
    }
	if( ( V_ucTurn != C_OK ) || ( V_usNum > V_MaxLen ) )
	{
		V_usNum = 0;
	}
	W_Safe_Flag = W_Safe_Flag | C_W_SafeFlag_2;
	V_usLen = CLSafeModeParaNat3;
	V_ucTurn = InF_ReadOADTab_Data(CSafeModeParaNat3, V_Data, &V_usLen);
	if( V_ucTurn != C_OK )
	{
		V_usLen = 0;
	}
	W_Safe_Flag = W_Safe_Flag | C_W_SafeFlag_3;

	if( V_OAD.Wt_Data[0] == 0x01 )
	{
		V_usNumADD = V_OAD.Wt_Data[1];
	}
	else
	{
		V_usNumADD = 0x01;
	}
	for( i = 0; i < V_usNumADD; i++ )
	{
		if( ( V_OAD.Wt_Data[i * 8 + 4] != C_OI ) || ( V_OAD.Wt_Data[i * 8 + 7] != C_long_unsigned ) )
		{
			V_ucTurn = C_OtherErr_DAR;
			return V_ucTurn;
		}

        for( j = 0; j < V_usNum; j++ )
		{
            if( ( V_OAD.Wt_Data[i * 8 + 4 + 2] == V_Data[j * 4] ) && ( V_OAD.Wt_Data[i * 8 + 3 + 2] == V_Data[j * 4 + 1] ) )
            {
                V_Data[j* 4 + 2] = V_OAD.Wt_Data[i * 8 + 7 + 2];
                V_Data[j * 4 + 3] = V_OAD.Wt_Data[i * 8 + 6 + 2];
                break;
		}
        }
        if( ( j >= V_usNum ) || ( V_usNum == 0 ) )
		{
            V_Data[j * 4] = V_OAD.Wt_Data[i * 8 + 4 + 2];
            V_Data[j * 4 + 1] = V_OAD.Wt_Data[i * 8 + 3 + 2];
            V_Data[j * 4 + 2] = V_OAD.Wt_Data[i * 8 + 7 + 2];
            V_Data[j * 4 + 3] = V_OAD.Wt_Data[i * 8 + 6 + 2];
            V_usNum = V_usNum + 1;                    /*����һ��OI*/
		}

	}
	V_ucTurn = InF_Write_Data(C_Msg_Communication, CSafeModeParaNat3, V_Data, CLSafeModeParaNat3, W_Safe_Flag);
	V_ucTurn = InF_Write_Data(C_Msg_Communication, CSafeModeParaNat3_Num, &V_usNum, CLSafeModeParaNat3_Num, W_Safe_Flag);

	return V_ucTurn;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_SecurityOIADD(WtOI_Rt_T V_OAD)
�������������ù�������
���������V_OAD��ȡ����
�����������
���ز��������ӳɹ�C_OK,ʧ��C_Err
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_SecurityOIADD(WtOI_Rt_T V_OAD)
{
	ushort16	V_usLen, V_usDataEncode;
	uchar8	V_usNum, V_Data[CLSafeModeParaNat3] = {0};
	uchar8	V_ucTurn, i = 0;
	uchar8	W_Safe_Flag = C_W_SafeFlag_1, V_MaxLen = CLSafeModeParaNat3 / 4;

	V_usLen = CLSafeModeParaNat3_Num;
	V_ucTurn = InF_Read_Data(CSafeModeParaNat3_Num, &V_usNum, &V_usLen, &V_usDataEncode);
    if( V_usNum == V_MaxLen )
    {
		V_ucTurn = C_OtherErr_DAR;
		return V_ucTurn;
    }
	if( ( V_ucTurn != C_OK ) || ( V_usNum > V_MaxLen ) )
	{
		V_usNum = 0;
	}
	W_Safe_Flag = W_Safe_Flag | C_W_SafeFlag_2;
	V_usLen = CLSafeModeParaNat3;
	V_ucTurn = InF_ReadOADTab_Data(CSafeModeParaNat3, V_Data, &V_usLen);
	if( V_ucTurn != C_OK )
	{
		V_usLen = 0;
	}
	W_Safe_Flag = W_Safe_Flag | C_W_SafeFlag_3;

	if( V_OAD.Wt_Data[0] != C_structure )
	{
		V_ucTurn = C_OtherErr_DAR;
		return V_ucTurn;
	}
	if( V_OAD.Wt_Data[1] != 0x02 )
	{
		V_ucTurn = C_OtherErr_DAR;
		return V_ucTurn;
	}
	if( V_OAD.Wt_Data[2] != C_OI )
	{
		V_ucTurn = C_OtherErr_DAR;
		return V_ucTurn;
	}

	if( V_OAD.Wt_Data[5] != C_long_unsigned )
	{
		V_ucTurn = C_OtherErr_DAR;
		return V_ucTurn;
	}
    for( i = 0; i < V_usNum; i++ )
	{
        if( ( V_OAD.Wt_Data[4] == V_Data[i * 4] ) && ( V_OAD.Wt_Data[3] == V_Data[i * 4 + 1] ) )
        {
            V_Data[i * 4 + 2] = V_OAD.Wt_Data[7];
            V_Data[i * 4 + 3] = V_OAD.Wt_Data[6];
            break;
        }
    }
    if( ( i >= V_usNum ) || ( V_usNum == 0 ) )
    {
        V_Data[i * 4] = V_OAD.Wt_Data[4];
        V_Data[i * 4 + 1] = V_OAD.Wt_Data[3];
        V_Data[i * 4 + 2] = V_OAD.Wt_Data[7];
        V_Data[i * 4 + 3] = V_OAD.Wt_Data[6];
        V_usNum = V_usNum + 1;                    /*����һ��OI*/
	}
	V_ucTurn = InF_Write_Data(C_Msg_Communication, CSafeModeParaNat3, V_Data, CLSafeModeParaNat3, W_Safe_Flag);
	V_ucTurn = InF_Write_Data(C_Msg_Communication, CSafeModeParaNat3_Num, &V_usNum, CLSafeModeParaNat3_Num, W_Safe_Flag);
	return V_ucTurn;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_GetMinFreezeCycle(ulong32 *p_datacode, uchar8 V_ucDatacodeBufLen, uchar8 *pDataPlan, ushort16 *pDataCycle)
������������ȡ���Ӷ���Ķ�������
���������p_datacode			:Ҫ��ȡ����OAD��RCSD
���������*pDataPlan �����ţ� *pDataCycle����
���ز������������߿鳭��ʱ�����Ƿ�һ�£�C_OKһ�£�C_Error��һ��
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_GetMinFreezeCycle(ulong32 *p_datacode, uchar8 V_ucDatacodeBufLen, uchar8 *pDataPlan, ushort16 *pDataCycle)
{
	ushort16 V_usLen, V_usOADNO, V_usDataEncode;
	Str_Event_OIB2 Str_FreezeInfo;
	uchar8 V_Data[C_RelatedOADBuf_Len], V_ucTurn, V_usNum, i, j, V_ucSamFlag = C_Error;/*V_ucSamFlag�����ʼ��ΪC_Error*/
	ulong32 V_OADTemp;
    ushort16 V_ucCycleTime = 0x000F;
	uchar8 V_ucDatacodeNum = 0, V_ucFindFlag = C_Error;

	*pDataPlan = 0;	/*�����ų�ʼ��Ϊ0*/

	/*��ȡ698��������б����*/
	Str_FreezeInfo = Freeze_OIBTable[C_MinFreez];
	V_usLen = CLMin_Free_OADTabLen_T;
	V_ucTurn = InF_Read_Data(Str_FreezeInfo.RelatedOAD_T, &V_usNum, &V_usLen, &V_usDataEncode);

	/*��ȡ698��������б��ڱ���е���š�����(����������)���洢���*/
	V_usLen = V_usNum * C_RelatedOADTabLen;
	V_ucTurn = InF_ReadOADTab_Data(Str_FreezeInfo.RelatedOAD, V_Data, &V_usLen);
	if(V_ucTurn == C_OK)
	{
		for(V_ucDatacodeNum = 0; V_ucDatacodeNum < V_ucDatacodeBufLen; V_ucDatacodeNum++)
		{
			if( ( *(p_datacode + 1 + V_ucDatacodeNum) ) == 0xFFFFFFFF )
			{
				break;
			}

			if(V_ucFindFlag == C_OK)
			{
				break;
			}

			for( i = 0; i < V_usNum * C_RelatedOADTabLen; i = i + C_RelatedOADTabLen )
			{
				V_usOADNO = V_Data[i + C_FreezNumHig];
				V_usOADNO &= 0x1F;
				V_usOADNO <<= 8;
				V_usOADNO |= V_Data[i];

				V_OADTemp = Str_FrozenConvert_Table[V_usOADNO].V_ulOAD;
				if( ( V_OADTemp == *(p_datacode + 1 + V_ucDatacodeNum) )
				 || ( V_OADTemp == ( ( *(p_datacode + 1 + V_ucDatacodeNum) ) & 0xFFFFF0FF | 0x00000400 ) ) )
				{
					/*����*/
					V_ucCycleTime =  V_Data[i + C_FreezCycleHig];
					V_ucCycleTime &= 0x1F;
					V_ucCycleTime <<= 8;
					V_ucCycleTime |= V_Data[i + C_FreezCycleLow];

					/*����*/
					*pDataPlan = V_Data[i + C_FreezNumHig] & 0xE0;
					if(*pDataPlan == 0)
					{
						V_ucFindFlag = C_OK;
						break;
					}
				}
			}

			if( i == V_usNum * C_RelatedOADTabLen )	/*��ѹ������������ȡ���*/
			{
				for( j = 0; j < V_usNum * C_RelatedOADTabLen; j = j + C_RelatedOADTabLen )
				{
					V_usOADNO = V_Data[j + C_FreezNumHig];
					V_usOADNO &= 0x1F;
					V_usOADNO <<= 8;
					V_usOADNO |= V_Data[j];

					V_OADTemp = Str_FrozenConvert_Table[V_usOADNO].V_ulOAD;
					if(V_OADTemp == ( ( *(p_datacode + 1 + V_ucDatacodeNum) ) & 0xFFFFFFF0 ) )
					{
						/*����*/
						V_ucCycleTime = V_Data[j + C_FreezCycleHig];
						V_ucCycleTime &= 0x1F;
						V_ucCycleTime <<= 8;
						V_ucCycleTime |= V_Data[j + C_FreezCycleLow];

						/*����*/
						*pDataPlan = V_Data[j + C_FreezNumHig] & 0xE0;
						if(*pDataPlan == 0)
						{
							V_ucFindFlag = C_OK;
							break;
						}
					}
				}
			}
		}

		if(V_ucFindFlag == C_OK)
		{
			V_ucSamFlag = C_OK;
		}
		else
		{
			V_ucSamFlag = C_Error;
		}
	}
	else
	{
		V_ucSamFlag = C_Error;
	}

	*pDataCycle = V_ucCycleTime;
	return V_ucSamFlag;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_FreezeOADRead(RdOI_Para_T V_OAD,uchar8 *P_DataBuf,ushort16 *P_DataOff,uchar8 V_TimeOADFlay,uchar8 *pV_ArrayNum)
�������������������ݴ���
���������ת�����645���ݱ�ʶ�룬���ݱ�ʶ���������ȡ���ݴ��buffer
				V_UpperTypeΪOI��Ӧ����������
�����������������ݴ��ͨ���շ�����
���ز��������ذ�ȫȨ���Ƿ�����Ҫ��C_OK��ʾ����Ȩ��Ҫ��
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_FreezeOADRead(RdOI_Para_T V_OAD, uchar8 *P_DataBuf, ushort16 *P_DataOff, uchar8 V_TimeOADFlay, uchar8 *pV_ArrayNum)
{
	ushort16	V_usLen, V_usOADNO, V_usDataEncode;
	Str_Event_OIB2	Str_FreezeInfo;
	uchar8	V_Data[C_RelatedOADBuf_Len], W_Safe_Flag, V_ucTurn, V_OADNum, V_usObject, V_usNum;
	ulong32 V_OADTemp, V_ulNature = 0;
	ushort16 V_DataOff = 0, i;

	V_usObject = (uchar8)(V_OAD.RdOI.OAD >> 16);	/*ȡ�����ʶ*/

	W_Safe_Flag = C_W_SafeFlag_1;
	for( i = 0; i < C_Freeze_OIBTableLen; i++ )
	{
		if(V_usObject == Freeze_OIBTable[i].OIB)
		{
			break;
		}
	}
	Str_FreezeInfo = Freeze_OIBTable[i];			/*��ȡ������ز���*/
	V_usLen = CLI_Free_OADTabLen_T;
	V_ucTurn = InF_Read_Data(Str_FreezeInfo.RelatedOAD_T, &V_usNum, &V_usLen, &V_usDataEncode);
	if( V_ucTurn == C_OK )
	{
		if(V_TimeOADFlay == 1)
		{
			i = 5;
		}
		else if(V_TimeOADFlay == 2)
		{
			i = 4;
		}
		else if(V_TimeOADFlay == 0)
		{
			i = 13;
		}
		if( ( i * V_usNum ) > *P_DataOff )			/*�����������*13ÿ������ռ���ֽ�����������󻺴棬��ֱ��Ӧ��Խ��*/
		{
			*P_DataOff = 0;
			return C_MaxResponseLen_ERR;
		}
		W_Safe_Flag = W_Safe_Flag | C_W_SafeFlag_2;
		if(V_usObject == 0x00)						/*˲ʱ����Ķ�������Ϊ0�������������ö������ڴ洢*/
		{
			;
		}

		V_usLen = V_usNum * 6;
		V_ucTurn = InF_ReadOADTab_Data(Str_FreezeInfo.RelatedOAD, V_Data, &V_usLen);
		if( V_ucTurn == C_OK )
		{
			if(V_TimeOADFlay == 1)					/*��Ҫ�Է���ʱ�估������Ӧ��OAD���б���*/
			{
				memset(&P_DataBuf[V_DataOff], 0, 2);
				V_DataOff += 2;
				V_OADNum =2;
				V_OADTemp = 0x20230200;
				PF_Ulong32ToBuffer4_698(&P_DataBuf[V_DataOff] , &V_OADTemp, 4);
				V_DataOff += 4;
				P_DataBuf[V_DataOff] = 0;
				V_DataOff++;
				V_OADTemp = 0x20210200;
				PF_Ulong32ToBuffer4_698(&P_DataBuf[V_DataOff] , &V_OADTemp, 4);
				V_DataOff += 4;
			}
			else
			{
				V_OADNum = 0;
			}

			for( i = 0; i < V_usNum * 6; i++ )
			{
				V_usOADNO = V_Data[i + 1];
				V_ulNature = V_Data[i + 1];
				V_ulNature &= 0xE0;
				V_ulNature <<= 8;
				V_usOADNO &= 0x1F;
				V_usOADNO <<= 8;
				V_usOADNO |= V_Data[i];

				V_OADTemp = Str_FrozenConvert_Table[V_usOADNO].V_ulOAD;
				V_OADTemp |= V_ulNature;
				V_OADNum++;
				if(V_TimeOADFlay == 1)
				{
					P_DataBuf[V_DataOff] = 0;
					V_DataOff++;
				}
				else if(V_TimeOADFlay == 0)
				{
					P_DataBuf[V_DataOff] = C_structure;
					V_DataOff++;
					P_DataBuf[V_DataOff] = 3;
					V_DataOff++;
					P_DataBuf[V_DataOff] = C_long_unsigned;
					V_DataOff++;
					P_DataBuf[V_DataOff] = V_Data[i + 1 + 2];
					V_DataOff++;
					P_DataBuf[V_DataOff] = V_Data[i + 1 + 1];

					V_DataOff++;
	                P_DataBuf[V_DataOff] = C_OAD;
	                V_DataOff++;
				}
				if(V_TimeOADFlay != 2)
				{
					PF_Ulong32ToBuffer4_698(&P_DataBuf[V_DataOff] , &V_OADTemp, 4);
				}
				else
				{
					PF_Ulong32ToBuffer4(&P_DataBuf[V_DataOff] , &V_OADTemp, 4);
				}
				V_DataOff += 4;
				if(V_TimeOADFlay == 0)
				{
					P_DataBuf[V_DataOff] = C_long_unsigned;
					V_DataOff++;
					P_DataBuf[V_DataOff] = V_Data[i + 1 + 2 + 2];
					V_DataOff++;
					P_DataBuf[V_DataOff] = V_Data[i + 1 + 2 + 1];
					V_DataOff++;
				}
				i += 5;
			}
		}
		else
		{
			V_OADNum = 0;
		}
	}
	else
	{
		V_OADNum = 0;
	}
	if(V_TimeOADFlay == 1)
	{
		P_DataBuf[0] = V_OADNum;
	}
	*pV_ArrayNum = V_OADNum;
	*P_DataOff = V_DataOff;
	return C_OK;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_JudgeSameRealatedOAD(uchar8 *P_RealatedOADTab,uchar8 *P_AddOAD,uchar8 V_ucRealatedOADNum,uchar8 V_ucOIFlag)
�����������ж���ӹ��������Ƿ���ͬ
���������P_RealatedOADTab���ݲ���������б�P_AddOAD��ӹ����У�OIFlag���ֶ�����¼���־��01Ϊ���ᣬ00Ϊ�¼�
�����������
���ز���������C_OK��ʾ�������Բ�ͬ����������ͬ�Ĺ�������
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_JudgeSameRealatedOAD(uchar8 *P_RealatedOADTab, uchar8 *P_AddOAD, uchar8 V_ucRealatedOADNum, uchar8 V_ucOIFlag)
{
	ushort16	i;
	uchar8		V_ucMulti;

	if(V_ucOIFlag == 0x01)
	{
		V_ucMulti = 6;
	}
	else
	{
		V_ucMulti = 2;
	}
	for( i = 0; i < V_ucRealatedOADNum; i++ )
	{
		if( PF_Campare_Data( &P_RealatedOADTab[i * V_ucMulti], P_AddOAD, 2 ) == C_Equal )
		{
			break;
		}
	}
	if( i < V_ucRealatedOADNum )
	{
		return C_OtherErr_DAR;
	}
	else
	{
		return 	C_OK;
	}
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_JudgeSameRealatedOADCycle(uchar8 *P_RealatedOADTab,uchar8 *P_AddOAD,uchar8 V_ucRealatedOADNum,uchar8 V_ucOIFlag)
�����������ж���ӹ������Ե������Ƿ���ͬ����ͬ����������
���������P_RealatedOADTab���ݲ���������б�P_AddOAD��ӹ����У�OIFlag���ֶ�����¼���־��01Ϊ���ᣬ00Ϊ�¼�
�����������
���ز���������C_OK��ʾ�������Բ�ͬ����������ͬ�Ĺ�������
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_JudgeSameRealatedOADCycle(uchar8 *P_RealatedOADTab, uchar8 *P_AddOAD, uchar8 V_ucRealatedOADNum, uchar8 V_ucOIFlag)
{
	ushort16 i;
	uchar8 V_ProjectOldNum, V_ProjectCurrentNum;
	for( i = 0; i < V_ucRealatedOADNum; i++ )
	{
		if(V_ucOIFlag == 2)	/*���Ӷ���ֻ�ȶ���ͬ�����ŵĶ�������*/
		{
			V_ProjectOldNum = (P_RealatedOADTab[i * 6 + 1]) & 0xE0;
			V_ProjectCurrentNum = ( *(P_AddOAD + 1) ) & 0xE0;
			if(V_ProjectOldNum != V_ProjectCurrentNum)
			{
				continue;
			}
		}
		if( PF_Campare_Data( &P_RealatedOADTab[i *   6 + 2], P_AddOAD + 2, 2 ) != C_Equal )
		{
			break;
		}
	}
	if(i < V_ucRealatedOADNum)
	{
		return C_OtherErr_DAR;
	}
	else
	{
		return 	C_OK;
	}
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_JudgeSameRealatedOADStoreNum(uchar8 *P_RealatedOADTab,uchar8 *P_AddOAD,uchar8 V_ucRealatedOADNum,uchar8 V_ucOIFlag)
�����������ж���ӹ������ԵĴ洢����Ƿ���ͬ����ͬ����������
���������P_RealatedOADTab���ݲ���������б�P_AddOAD��ӹ����У�OIFlag���ֶ�����¼���־��01Ϊ���ᣬ00Ϊ�¼�
�����������
���ز���������C_OK��ʾ�������Բ�ͬ����������ͬ�Ĺ�������
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_JudgeSameRealatedOADStoreNum(uchar8 *P_RealatedOADTab, uchar8 *P_AddOAD, uchar8 V_ucRealatedOADNum, uchar8 V_ucOIFlag)
{
	ushort16 i;
	uchar8 V_ProjectOldNum, V_ProjectCurrentNum;
	for( i = 0; i < V_ucRealatedOADNum; i++ )
	{
		if(V_ucOIFlag == 2)	/*���Ӷ���ֻ�ȶ���ͬ�����ŵĶ�������*/
		{
			V_ProjectOldNum = (P_RealatedOADTab[i * 6 + 1]) & 0xE0;
			V_ProjectCurrentNum = ( *(P_AddOAD + 1) ) & 0xE0;
			if( V_ProjectOldNum != V_ProjectCurrentNum )
			{
				continue;
			}
		}
		if( PF_Campare_Data( &P_RealatedOADTab[i * 6 + 4], P_AddOAD + 4, 2 ) != C_Equal )
		{
			break;
		}
	}
	if( i < V_ucRealatedOADNum )
	{
		return C_OtherErr_DAR;
	}
	else
	{
		return 	C_OK;
	}
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_SecurityOIRead(uchar8 *P_DataBuf,ushort16 *P_DataOff,uchar8 *pV_ArrayNum)
��������������ȫģʽ����
�����������ȡ���ݴ��buffer
�����������������ݴ��ͨ���շ�����
���ز�����OI��������������ݳ���
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_SecurityOIRead( uchar8 *P_DataBuf, ushort16 *P_DataOff, uchar8 *pV_ArrayNum )
{
	ushort16	V_usLen, V_usDataEncode;
	uchar8		V_Data[1024], W_Safe_Flag, V_ucTurn, V_usNum;
	ushort16	V_DataOff = 0, i;

	W_Safe_Flag = C_W_SafeFlag_1;

	V_usLen = CLSafeModeParaNat3_Num;
	V_ucTurn = InF_Read_Data(CSafeModeParaNat3_Num, &V_usNum, &V_usLen, &V_usDataEncode);
	if( V_ucTurn == C_OK )
	{
		W_Safe_Flag = W_Safe_Flag | C_W_SafeFlag_2;

		V_usLen = CLSafeModeParaNat3;
		V_ucTurn = InF_ReadOADTab_Data(CSafeModeParaNat3, V_Data, &V_usLen);
		if( V_ucTurn == C_OK )
		{
			for( i = 0; i < V_usNum * 4; i++ )
			{
				P_DataBuf[V_DataOff] = C_structure;
				V_DataOff++;
				P_DataBuf[V_DataOff] = 2;
				V_DataOff++;
				P_DataBuf[V_DataOff] = C_OI;
				V_DataOff++;
				P_DataBuf[V_DataOff] = V_Data[i + 1];
				V_DataOff++;
				P_DataBuf[V_DataOff] = V_Data[i];

				V_DataOff++;
                P_DataBuf[V_DataOff] = C_long_unsigned;
                V_DataOff++;
                P_DataBuf[V_DataOff] = V_Data[i + 2 + 1];
				V_DataOff++;
				P_DataBuf[V_DataOff] = V_Data[i + 2];
				V_DataOff++;

				i += 3;
			}
		}
		else
		{
			return C_OtherErr_DAR;
		}
	}
	else
	{
		return C_OtherErr_DAR;
	}
	*pV_ArrayNum = V_usNum;
	*P_DataOff = V_DataOff;
    return C_OK;
}
/*******************************************************************************
����ԭ�ͣ�uchar8	SF_Get_AssociationList(ulong32 V_OAD, ulong32 *P_DataBuf, uchar8 Len, uchar8 *pV_ArrayNum)
������������ȡ�¼�/������б��̶��б�͹����б�
���������V_OAD���ж�ǰ3���ֽڣ����һ���ֽڵ��������жϣ�P_DataBuf:�����б�Len���жϻ����С��pV_ArrayNum���б�OAD������
���������P_DataBuf:�б�pV_ArrayNum���б�OAD������
���ز�����C_Ok����ȷ�����б�C_IDError��û��OAD��C_MaxResponseLen_ERR������̫С���Ų��£�C_Error:��������
����λ�ã�
��    ע��
*******************************************************************************/
uchar8	SF_Get_AssociationList(ulong32 V_OAD, ulong32 *P_DataBuf, uchar8 *pV_ArrayNum)
{
    uchar8  V_uci, V_ucJ, V_uck, V_usObject, V_Return = C_Error, V_OADBuf[4] = {0}, V_TotalNum = 0;
    ulong32 V_OADTemp = V_OAD;
	ushort16	V_usLen,V_usOADNO, V_usDataEncode;
	Str_Event_OIB1	Str_EventInfo;
	uchar8	V_Data[C_RelatedOADBuf_Len], V_ucTurn, V_usNum = 0;
	ulong32 V_ulNature=0;
	ushort16 V_DataOff = 0;
	Str_Event_SingleSpecificData *str_EventSpecialOAD;
    PF_Ulong32ToBuffer4_698(V_OADBuf, &V_OAD, 4);
    V_usObject = V_OADBuf[1];

    if(V_OADBuf[0] == 0x30)                    								/*�¼���*/
    {
        for(V_uci = 0; V_uci < C_Event_OIBTableLen; V_uci++)
        {
            if(V_usObject == Event_OIBTable[V_uci].OIB)
            {
                break;
            }
        }

        if( V_uci < C_Event_OIBTableLen )
        {
            V_OADTemp = C_Event_RecordNO;
            P_DataBuf[V_DataOff] = V_OADTemp;
            V_DataOff ++;
            V_OADTemp = C_EventStart_Moment;
            P_DataBuf[V_DataOff] = V_OADTemp;
            V_DataOff++;
            V_OADTemp = C_EventEnd_Moment;
            P_DataBuf[V_DataOff] = V_OADTemp;
            V_DataOff++;
            V_OADTemp = CEventHPSource;
            P_DataBuf[V_DataOff] = V_OADTemp;
            V_DataOff++;
            V_OADTemp = CUpdata_Status;
            P_DataBuf[V_DataOff] = V_OADTemp;
            V_DataOff++;

            for( V_ucJ = 0; V_ucJ < C_Event_SpecificDataLen; V_ucJ++ )		/*�����������ݵ��¼���¼����*/
            {
                if(V_usObject == Event_SpecificData[V_ucJ].OIB)
                {
                    break;
                }
            }
            if(V_ucJ < C_Event_SpecificDataLen)
            {
                for( V_uck = 0 ; V_uck < Event_SpecificData[V_ucJ].OADTableLenth; V_uck++)
                {
					str_EventSpecialOAD = (Str_Event_SingleSpecificData *)Event_SpecificData[V_ucJ].SpecificOADTableAddr;
                    V_OADTemp = str_EventSpecialOAD[V_uck].SpecialOAD;
                    P_DataBuf[V_DataOff] = V_OADTemp;
                    V_DataOff++;
                }
            }

            Str_EventInfo = Event_OIBTable[V_uci];	    					/*��ȡ�����б���ز���*/
            V_usLen = CLLoss_Vol_OADTabLen;
            V_ucTurn = InF_Read_Data(Str_EventInfo.RelatedOAD_T, &V_usNum, &V_usLen, &V_usDataEncode);

            V_TotalNum = V_DataOff + V_usNum;

            if( V_ucTurn == C_OK )
            {
                if( V_TotalNum <= *pV_ArrayNum )   							/*������ݲ����ڻ���*/
                {
                    V_usLen = C_EventMAXRelatedOADLen;
                    V_ucTurn = InF_ReadOADTab_Data(Str_EventInfo.RelatedOAD, V_Data, &V_usLen);

                    if( V_ucTurn == C_OK )
                    {
                        for( V_uci = 0; V_uci < V_usNum; V_uci++)
                        {
                            V_usOADNO = V_Data[V_uci * 2 + 1];
                            V_ulNature = V_Data[V_uci * 2 + 1];
                            V_ulNature &= 0xE0;
                            V_ulNature <<= 8;
                            V_usOADNO &= 0x1F;
                            V_usOADNO <<= 8;
                            V_usOADNO |= V_Data[V_uci * 2];

                            if(V_usOADNO >= Str_FrozenConvert_Table_Len)	/*���ڱ�񳤶ȣ���������*/
                            {
                                continue;
                            }
                            V_OADTemp = Str_FrozenConvert_Table[V_usOADNO].V_ulOAD;
                            V_OADTemp |= V_ulNature;

                            P_DataBuf[V_DataOff] = V_OADTemp;
                            V_DataOff++;
                        }
						V_Return = C_OK_DAR;
                    }
                    else
                    {
                        V_Return = C_OtherErr_DAR;
                    }
                }
                else
                {
                    V_Return = C_MaxResponseLen_ERR;
                }
            }
        }
        else
        {
            V_Return = C_IDError;
        }
    }
    else
    {
        V_Return = C_IDError;
    }
    *pV_ArrayNum = V_DataOff;
    return V_Return;
}
/*******************************************************************************
����ԭ�ͣ�uchar8	SF_EventOADRead(RdOI_Para_T V_OAD,uchar8 *P_DataBuf,ushort16 *P_DataOff,uchar8 V_TimeOADFlay,uchar8 *pV_ArrayNum)
�������������¼���¼��OAD�б���
���������ת�����645���ݱ�ʶ�룬���ݱ�ʶ���������ȡ���ݴ��buffer
				V_UpperTypeΪOI��Ӧ����������
�����������
���ز��������ذ�ȫȨ���Ƿ�����Ҫ��C_OK��ʾ����Ȩ��Ҫ��
����λ�ã�
��    ע��
*******************************************************************************/
uchar8	SF_EventOADRead(RdOI_Para_T V_OAD, uchar8 *P_DataBuf, ushort16 *P_DataOff, uchar8 V_TimeOADFlay, uchar8 *pV_ArrayNum)
{
	ushort16	V_usLen, V_usOADNO, V_usDataEncode;
	Str_Event_OIB1	Str_EventInfo;
	uchar8	V_Data[C_RelatedOADBuf_Len], W_Safe_Flag, V_ucTurn, V_OADNum, V_usObject, V_usNum;
	ulong32 V_OADTemp, V_ulNature = 0;
	ushort16 V_DataOff = 0, i;
    uchar8 j, k;
	Str_Event_SingleSpecificData *str_EventSpecialOAD;
	
	V_usObject = (uchar8)(V_OAD.RdOI.OAD >> 16);	/*ȡ�����ʶ*/

	W_Safe_Flag = C_W_SafeFlag_1;
	for( i = 0; i < C_Event_OIBTableLen; i++ )
	{
		if(V_usObject == Event_OIBTable[i].OIB)
		{
			break;
		}
	}
	Str_EventInfo = Event_OIBTable[i];				/*��ȡ������ز���*/
	V_usLen = CLLoss_Vol_OADTabLen;
	V_ucTurn = InF_Read_Data(Str_EventInfo.RelatedOAD_T, &V_usNum, &V_usLen, &V_usDataEncode);
	if( V_ucTurn == C_OK )
	{
		if(V_TimeOADFlay == 2)
		{
			i = 4;
		}
		else
		{
			i = 5;
		}
		if( ( i * V_usNum ) > *P_DataOff )
		{
			return C_MaxResponseLen_ERR;
		}
		W_Safe_Flag = W_Safe_Flag | C_W_SafeFlag_2;
		if(V_usObject == 0x00)						/*˲ʱ����Ķ�������Ϊ0�������������ö������ڴ洢*/
		{
		}

		V_usLen = 120;
		V_ucTurn = InF_ReadOADTab_Data(Str_EventInfo.RelatedOAD, V_Data, &V_usLen);
		if( V_ucTurn == C_OK )
		{
			if( V_TimeOADFlay == 1 )				/*��Ҫ�Է���ʱ�估������Ӧ��OAD���б���*/
			{
				P_DataBuf[V_DataOff] = 0;
				V_DataOff++;
				P_DataBuf[V_DataOff] = 0;
				V_DataOff++;
				V_OADNum =4;
				V_OADTemp = 0x20220200;
				PF_Ulong32ToBuffer4_698(&P_DataBuf[V_DataOff] , &V_OADTemp, 4);
				V_DataOff += 4;
				P_DataBuf[V_DataOff] = 0;
				V_DataOff++;
				V_OADTemp = 0x201E0200;
				PF_Ulong32ToBuffer4_698(&P_DataBuf[V_DataOff] , &V_OADTemp, 4);
				V_DataOff += 4;
				P_DataBuf[V_DataOff] = 0;
				V_DataOff++;
				V_OADTemp = 0x20200200;
				PF_Ulong32ToBuffer4_698(&P_DataBuf[V_DataOff] , &V_OADTemp, 4);
				V_DataOff += 4;
				if( ( Str_EventInfo.TypeClass == C_Event_Class ) || ( V_usObject == CRe_ReDe_Over_OIB ) )
				{
					P_DataBuf[V_DataOff] = 0;
					V_DataOff++;
					V_OADTemp = 0x20240200;
					PF_Ulong32ToBuffer4_698(&P_DataBuf[V_DataOff] , &V_OADTemp, 4);
					V_DataOff += 4;
					V_OADNum++;
				}
                P_DataBuf[V_DataOff] = 0;
                V_DataOff++;
                V_OADTemp = 0x33000200;
                PF_Ulong32ToBuffer4_698(&P_DataBuf[V_DataOff] , &V_OADTemp, 4);
                V_DataOff += 4;
				for( j = 0; j < C_Event_SpecificDataLen; j++ )	/*�����������ݵ��¼���¼����*/
				{
					if( V_usObject == Event_SpecificData[j].OIB )
					{
						break;
					}
				}
				if( j < C_Event_SpecificDataLen )
				{
					for( k = 0; k < Event_SpecificData[j].OADTableLenth; k++ )
					{
						P_DataBuf[V_DataOff] = 0;
						V_DataOff++;
						str_EventSpecialOAD = (Str_Event_SingleSpecificData *)Event_SpecificData[j].SpecificOADTableAddr;
						V_OADTemp = str_EventSpecialOAD[k].SpecialOAD;
						PF_Ulong32ToBuffer4_698(&P_DataBuf[V_DataOff] , &V_OADTemp, 4);
						V_DataOff += 4;
						V_OADNum++;
					}
				}
			}
			else
			{
				V_OADNum = 0;
			}

			for( i = 0; i < V_usNum; i++ )
			{
				V_usOADNO = V_Data[i * 2 + 1];
				V_ulNature = V_Data[i * 2 + 1];
				V_ulNature &= 0xE0;
				V_ulNature <<=8;
				V_usOADNO &= 0x1F;
				V_usOADNO <<= 8;
				V_usOADNO |= V_Data[i * 2];

				if( V_usOADNO >= Str_FrozenConvert_Table_Len )	/*���ڱ�񳤶ȣ���������*/
				{
					continue;
				}
				V_OADTemp = Str_FrozenConvert_Table[V_usOADNO].V_ulOAD;
				V_OADTemp |= V_ulNature;
				V_OADNum++;
				if(V_TimeOADFlay == 1)
				{
					P_DataBuf[V_DataOff] = 0;
					V_DataOff++;
				}
				else if(V_TimeOADFlay == 0)
				{
					P_DataBuf[V_DataOff] = C_OAD;
					V_DataOff++;
				}
				if(V_TimeOADFlay != 2)
				{
					PF_Ulong32ToBuffer4_698(&P_DataBuf[V_DataOff] , &V_OADTemp, 4);
				}
				else
				{
					PF_Ulong32ToBuffer4(&P_DataBuf[V_DataOff] , &V_OADTemp, 4);
				}
				V_DataOff += 4;
				if(V_TimeOADFlay == 0)
				{
				}
			}
		}
		else
		{
			V_OADNum = 0;
			if(V_TimeOADFlay == 1)
			{
				P_DataBuf[0] = V_OADNum;
			}
			*pV_ArrayNum = V_OADNum;
			*P_DataOff = V_DataOff;
			return C_OtherErr_DAR;
		}
	}
	else
	{
		V_OADNum = 0;
		if(V_TimeOADFlay == 1)
		{
			P_DataBuf[0] = V_OADNum;
		}
		*pV_ArrayNum = V_OADNum;
		*P_DataOff = V_DataOff;

		return C_OtherErr_DAR;
	}
	if(V_TimeOADFlay == 1)
	{
		P_DataBuf[0] = V_OADNum;
	}
	*pV_ArrayNum = V_OADNum;
	*P_DataOff = V_DataOff;
	return C_OK;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_JugeDemadFF(uchar8 *P_DemandData,uchar8 V_ucLen)
�����������ж����������Ƿ�ȫFF
�������������������ʼ��ַ���ж����ݳ���
���������
���ز�����C_OK��ʾ����ȫFF��������ʾ����ȫFF
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_JugeDemadFF(uchar8 *P_DemandData, uchar8 V_ucLen)
{
	uchar8 ReturnFlag = C_OtherErr, i;

	for( i = 0; i < V_ucLen; i++ )
	{
		if( *( P_DemandData + i ) != 0xFF )
		{
			break;
		}
	}
	if( i >= V_ucLen )
	{
		ReturnFlag = C_OK;
	}

	return ReturnFlag;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_CalculateTI(uchar8 FreezeType,uchar8 V_Unit)
�����������ж�TI
���������	FreezeType�������� V_Unit�����λ
�����������
���ز�����ת���Ƿ�ɹ�����ת���󳬳�2�ֽڼ�����ش���
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_CalculateTI(uchar8 FreezeType, uchar8 V_Unit)
{
    uchar8 V_ucRetrun = C_OK;

	if( V_Unit > 5 )
	{
		V_ucRetrun = C_TypeErr_DAR;
		return V_ucRetrun;
	}
    if( ( FreezeType != 0 ) && ( FreezeType != 0x05 ) && ( FreezeType < 0x08 ) )
    {
/*��λ�ж�*/
		if( FreezeType < 5 )		/*���ӡ�ʱ���ն���*/
		{
			if( V_Unit != FreezeType - 1 )
			{
				V_ucRetrun = C_RWForbid_DAR;
			}
		}
		else						/*�¡��궳��*/
		{
			if( V_Unit != FreezeType - 2 )
			{
				V_ucRetrun = C_RWForbid_DAR;
			}
		}
	}
	return V_ucRetrun;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_MaxLenSubAndJudge(ushort16 *pV_MaxLen, uchar8 V_DataFlag)
����������
���������
���������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_MaxLenSubAndJudge(ushort16 *pV_MaxLen, uchar8 V_DataFlag)
{
	ushort16 V_DataLen;

	if( ( V_DataFlag == C_NULL ) && ( *pV_MaxLen > 1 ) )
	{
		*pV_MaxLen = ( (*pV_MaxLen) - 1 );
		return C_OK;
	}
	V_DataLen = SF_GetDataTypeLen(&V_DataFlag);
	if( V_DataLen > (*pV_MaxLen) )
	{
		return C_Error;
	}
	else
	{
		*pV_MaxLen -= V_DataLen;
		return C_OK;
	}
}
/*******************************************************************************
����ԭ�ͣ�uchar8 InF_RateNumChangeToHex(void)
����������������������������Hex��ʽ
�����������
�����������
���ز�������������Hex
����λ�ã�
��    ע�������ݲ�ɹ�����������Χ��1-4����Hex��
			�����ݲ�ʧ�ܣ���������4��Hex��
*******************************************************************************/
uchar8 InF_RateNumChangeToHex(void)
{
    uchar8   V_ucRateNum = 0;
	ushort16 V_ucRateNumLen, V_usDataEncode;

    V_ucRateNumLen = CLRate_Num;
    if( InF_Read_Data( CRate_Num, &V_ucRateNum, &V_ucRateNumLen, &V_usDataEncode ) != C_OK )		/*������Ϊ�������*/
    {
		V_ucRateNum = C_MaxRatesNum;
    }/*elseΪ����������ֵ*/
	if( V_ucRateNum > C_MaxRatesNum)
	{
		V_ucRateNum = C_MaxRatesNum;
	}
    return V_ucRateNum;
}
/*******************************************************************************
����ԭ�ͣ�void SF_FrozenDataFF_NextNum(Struct_FrozenConvert_Type *str_Encode, ushort16 V_usLineNum)
���������������ᶳ�������п����ݣ�������Ԫ�صĸ������ݷ�����Ӧ��
���������V_usLineNum:�����к�Str_FrozenConvert_Table[V_usLineNum]��
         str_Encode:��ֵ���ȣ����������ͣ��¼��������¼����͵����ڱ���Ľṹ���ַ��
���������str_Encode:���ݷ����������ģ����ȣ����������ͣ��¼��������¼����͵����ڱ���Ľṹ���ַ��
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
void SF_FrozenDataFF_NextNum(Struct_FrozenConvert_Type *str_Encode, ushort16 V_usLineNum)
{
    uchar8 V_ucRateNum;

    V_ucRateNum = InF_RateNumChangeToHex();

    if( Str_FrozenConvert_Table[V_usLineNum].V_uc698RateNumMethod == C_NeedRateNum_FF )
    {
        str_Encode->V_uc698NextNum = V_ucRateNum + 1;																			/*��+���ʣ�����+1*/
        str_Encode->V_uc645Length =  (str_Encode->V_uc698NextNum) * (Str_FrozenConvert_Table[V_usLineNum + 1].V_uc645Length);	/*�����*����*/
    }
    else if(Str_FrozenConvert_Table[V_usLineNum].V_uc698RateNumMethod == C_NeedRateNumPrice_FF)
    {
        str_Encode->V_uc698NextNum = V_ucRateNum;
        str_Encode->V_uc645Length =  (str_Encode->V_uc698NextNum) * (Str_FrozenConvert_Table[V_usLineNum + 1].V_uc645Length);	/*�����*����*/
    }
    /*else��������ʹ�ñ��������*/
}

/****************************************************************************
����ԭ�� ��	SF_Get_Active_OAD
����������	�ж�ȫAA��BB�Ƿ�Ϊ���ܵ���Ч����
�������	V_ulReadOAD��ȡ����OAD�� Ϊ��¼�����б���߹̶��б�OAD
			pV_ulSetAndFixedOADΪ����/�¼���¼�̶�OAD+���ù���OAD��ȫ��OAD
			V_ucDataTypeΪV_ulReadOAD�����ڲ���ȡ�Ķ�Ӧ����������
			V_ucHappeningFlagΪ�¼���¼������־�����¼���¼��ȡʱ����
��������� 	��
���ز�����	AA/BB�Ǳ�ʾNULL����Ϊ�������ݣ�����C_AAorBBIsActive��ʾΪ��Ч��������
							C_AAorBBIsDisactive��ʾ��Ч���ݣ���NULL
����λ�ã�
��ע��
****************************************************************************/
uchar8 SF_Get_Active_OAD(ulong32 V_ulReadOAD, ulong32 *pV_ulSetAndFixedOAD, uchar8 V_ucDataType, uchar8 V_ucHappeningFlag)
{
	uchar8 V_ucReturn = C_AAorBBIsDisactive, i = 0, j = 0, V_ucRateNum;
	uchar8 V_ucOIB;
	uchar8 V_ucOAD_Num = (uchar8)pV_ulSetAndFixedOAD[0];

	for( j = 0; j < V_ucOAD_Num; j++ )
	{
		if( ( V_ulReadOAD & 0xFFFFFF00 ) == (pV_ulSetAndFixedOAD[j + 1] & 0xFFFFFF00 ) )
		{
			break;
		}
		else if( ( V_ulReadOAD & 0xFF000000 ) == 0x00000000 )									/*����*/
		{
			if( ( V_ulReadOAD & 0xFFFFE000 ) == ( pV_ulSetAndFixedOAD[j + 1] & 0xFFFFE000 ) )	/*�����Ż��߶�ȡ��¼״̬��ͬ*/
			{
				if( ( pV_ulSetAndFixedOAD[j] & 0x00001F00 ) == 0x00000400 )						/*���ù�������Ϊ��������4*/
				{
					if( ( ( V_ulReadOAD & 0x00001F00) == 0x00000200 )
					 || ( (V_ulReadOAD & 0x00001F00) == 0x00000400 ) )							/*��ȡ����Ϊ����2��������4*/
					{
						break;
					}
				}
				else if( ( pV_ulSetAndFixedOAD[j] & 0x00001F00 ) == 0x00000200)					/*���ù�������Ϊ��������2*/
				{
					if( ( V_ulReadOAD & 0x00001F00 ) == 0x00000200 )							/*��ȡ����Ϊ����2*/
					{
						break;
					}
				}
			}
		}
	}
	if( j < V_ucOAD_Num )
	{
		if( ( C_Active_Happening == V_ucHappeningFlag )				/*�����¼���¼�����ʱ�䷢���ڼ����������AAΪ��Ч����*/
		  && ( ( ( V_ulReadOAD & 0x0000E000 ) == 0x00008000 )		/*��������Ϊ��Ч���ݣ�ֱ�����*/
			   || ( V_ulReadOAD == 0x20200200 ) ) )					/*�¼���¼����ʱ��*/
		{
				V_ucReturn = C_AAorBBIsDisactive;
		}
		else
		{
			if( ( V_ulReadOAD & 0xFF000000 ) == 0x00000000 )		/*����*/
			{
				/****************��ȡ������*******************/
				V_ucOIB = (uchar8)(V_ulReadOAD >> 16);
				for( i = 0; i < GV_Str_OIB_DI2_EnergyTableLen; i++ )
				{
					if(V_ucOIB == GV_Str_OIB_DI2_EnergyTable[i].OIB)
					{
						break;
					}
				}
				V_ucRateNum = SF_GetRateNum(GV_Str_OIB_DI2_EnergyTable[i].MaxNum);
				if( ( ( pV_ulSetAndFixedOAD[j + 1] & 0x000000FF ) == 0x00000000 )							/*���ú���*/
				 || ( ( pV_ulSetAndFixedOAD[j + 1] & 0x000000FF ) == ( V_ulReadOAD & 0x000000FF ) ) )		/*���÷���������ȡ�����������������*/
				{
					if( ( (uchar8)( V_ulReadOAD & 0x000000FF ) ) <=   V_ucRateNum )
					{
						V_ucReturn = C_AAorBBIsActive;
					}
				}
			}
			else
			{
				if( C_bit_string == V_ucDataType)					/*�ַ������͵ı���Ϊhex��ʽ����Ϊ������ȷ*/
				{
					V_ucReturn = C_AAorBBIsActive;
				}
			}
		}
	}
	return V_ucReturn;
}
/*******************************************************************************
����ԭ��:SF_GetAPDU_FreezeRead
��������:���������ݴ���
�������:ת�����645���ݱ�ʶ�룬���ݱ�ʶ���������ȡ���ݴ��buffer
			V_UpperTypeΪOI��Ӧ����������
�������:��������ݴ��ͨ���շ�����
���ز���:���ذ�ȫȨ���Ƿ�����Ҫ��C_OK��ʾ����Ȩ��Ҫ��
				C_
����λ��:SV_Comm_Parse/SV_Comm_Parse_Local
��ע��
*******************************************************************************/
#define C_MAXRelatedOAD_Event  (C_EventMAXRelatedOAD + 5)
uchar8 SF_GetAPDU_FreezeRead(RdOI_Para_T *V_OAD, uchar8 *P_DataBuf, ushort16 *P_DataOff, uchar8 NextFrameFlage)
{
	uchar8		V_ucRetrun = C_OK, V_usObject;
	ulong32		V_ReadOAD, V_SelectOAD;
	ushort16	V_usDataLen, V_usReadRecordNum, V_usIntervalTime, i, j, k, m, V_DataOff645, V_DataOff, V_RelatedOADNum;
	ulong32		V_ulReadOADBuf[C_MAXRelatedOAD];
	uchar8		V_DataTemp[1536];
	Str_DI0_DataType_PaTable *p_TableAddr;
	ushort16	V_DataLenMax;
	ushort16	V_DataOffTemp;
	ulong32		V_ulReadOADBuf_All[C_MAXRelatedOAD];
    ulong32		V_ulPlan;
    uchar8		V_ucFixedOADNum = 0;
	uchar8 V_2021No = 0xFF, V_2023No = 0xFF;
	uchar8 		V_SaveFreezeTimeBuf[C_SaveFreezeTimeBufLen];
	ulong32 	SubSeconds;
	Str_Read_T	V_EventRead;
	Str_SuppInfo V_ucSupplementaryInformation;
	ushort16    V_ucSuppleInformationTemp[C_MAXRelatedOAD_Event * 3] = {0};		/*һ����־��ı������Ҫ2���ֽڣ��ٶ���һ���ֽ�����*/
	uchar8		V_ucRSTTemp[25] = {0};
	Struct_FrozenConvert_Type Str_Encode;
	uchar8		V_ucLen;
	uchar8		V_ucOverAPDUFlay = 0;
	
	V_ucSupplementaryInformation.pV_usEncode = &V_ucSuppleInformationTemp[0];
	V_EventRead.pV_ucRST = &V_ucRSTTemp[0];				/*����¼�ķ�����0/1/2/9*/
	for( i = 0; i < C_MAXRelatedOAD; i++ )
	{
		V_ulReadOADBuf_All[i] = 0xFFFFFFFF;
	}

	V_usObject = (uchar8)(V_OAD->RdOI.OAD >> 16);		/*ȡ�����ʶ*/
	for( i = 0; i < C_Freeze_OIBTableLen; i++ )
	{
		if(V_usObject == Freeze_OIBTable[i].OIB)
		{
			break;
		}
	}

	V_DataLenMax = *P_DataOff;
	V_ucRSTTemp[C_RST_Method_O] = V_OAD->Rd_RecordSelect[C_GetSelect_Method_O];
	/***************************��ѡ�񷽷�����*****************************/
	switch(V_OAD->Rd_RecordSelect[C_GetSelect_Method_O])				/*��ѡȡ����*/
	{
		case 9:
		{
			V_usReadRecordNum = 1;
			V_ReadOAD = ( V_OAD->RdOI.OAD & 0xFFFF0000 ) | V_OAD->Rd_RecordSelect[C_GetSelect_OADOrNum_O];
			V_ucRSTTemp[C_RST_OADOrNum_O] = V_OAD->Rd_RecordSelect[C_GetSelect_OADOrNum_O];
		}break;

		case 1:
		case 2:
		{
			if(V_OAD->Rd_RecordSelect[C_GetSelect_TI_O] == 0)
			{
				V_usIntervalTime = 0;
			}
			else
			{
				V_usIntervalTime = V_OAD->Rd_RecordSelect[C_GetSelect_TIInter_O];
				V_usIntervalTime <<= 8;
				V_usIntervalTime |= V_OAD->Rd_RecordSelect[C_GetSelect_TIInter_O + 1];
			}
			V_ReadOAD = (V_OAD->RdOI.OAD & 0xFFFF0000);
			PF_OneDataReversed(&V_OAD->Rd_RecordSelect[C_GetSelect_OADOrNum_O], &V_ucRSTTemp[C_RST_OADOrNum_O], CL_OAD);
		}break;
		case 0:
		{
			V_usReadRecordNum = Freeze_OIBTable[i].MaxFrozenNum;
			V_ReadOAD = (V_OAD->RdOI.OAD & 0xFFFF0000) | 1;
			V_usIntervalTime = 0;
		}break;
		default:
		{
			V_ucRetrun = C_OtherErr_DAR;			/*����ѡ�񷽷�Ӧ����������*/
					return V_ucRetrun;
		}break;
	}
#if 0	
	if(NextFrameFlage != C_GETNext_Request)
#endif
	{
		switch(V_OAD->Rd_RecordSelect[0])				/*��ѡȡ����*/
		{
			case 1:
			case 2:
			{
				V_SelectOAD = PF_Buffer4ToUlong32_698(&V_OAD->Rd_RecordSelect[C_GetSelect_OADOrNum_O]);
				/*******************������ѡ�񷽷���ʱ��ת��Ϊ645******************/
                if(V_OAD->Rd_RecordSelect[C_GetSelect_Data1_O] != 0x1C)
                {
                    V_ucRetrun = C_TypeErr_DAR;
					return V_ucRetrun;
                }

				SF_DataExchangeTo645_BasicData(&V_OAD->Rd_RecordSelect[C_GetSelect_Data1_O], &V_ucRSTTemp[C_RST_Timer1_O], CL_date_time_s, (uchar8 *)&j);

				V_usReadRecordNum = 1;					/*����ʱ���ȡһ�������¼(ceshi)*/
				if(V_OAD->Rd_RecordSelect[C_GetSelect_Method_O] == 2)
				{
	                if(V_OAD->Rd_RecordSelect[C_GetSelect_Data2_O] != 0x1C)
	                {
	                    V_ucRetrun = C_TypeErr_DAR;
						return V_ucRetrun;
	                }

					SF_DataExchangeTo645_BasicData(&V_OAD->Rd_RecordSelect[C_GetSelect_Data2_O], &V_ucRSTTemp[C_RST_Timer2_O], CL_date_time_s, (uchar8 *)&j);

					if(V_OAD->Rd_RecordSelect[C_GetSelect_TI_O] == C_TI)
					{
						V_ucRetrun = SF_CalculateTI(V_usObject, V_OAD->Rd_RecordSelect[C_GetSelect_TIUnit_O]);
						if(V_ucRetrun != C_OK)
						{
							V_ucRetrun = C_RWForbid_DAR;
							return V_ucRetrun;
							break;
						}
					}
					else if(V_OAD->Rd_RecordSelect[C_GetSelect_TI_O] == 0)
					{
						V_usIntervalTime = 0;
					}
					else
					{
						V_ucRetrun = C_TypeErr_DAR;
						return V_ucRetrun;
						break;
					}

					V_usReadRecordNum = 0;
					if(PF_TimeSub_Second_698(&V_ucRSTTemp[C_RST_Timer2_O], &V_ucRSTTemp[C_RST_Timer1_O], &SubSeconds) != C_GreaterThan)
					{
						V_ucRetrun = C_OtherErr_DAR;
						return V_ucRetrun;
						break;
					}
				}
				V_ReadOAD = (V_OAD->RdOI.OAD & 0xFFFF0000);

			}break;
        }
	}
	PF_Ushort16ToBuffer2(&V_ucRSTTemp[C_RST_TIInter_O],&V_usIntervalTime);
	/***************************��ѡ�񷽷�����*****************************/
	V_ulReadOADBuf[0] = V_ReadOAD;

	V_RelatedOADNum = V_OAD->Rd_RecordRelatedOINum;

	if( V_RelatedOADNum > (C_MAXRelatedOAD - 1) )
	{
		V_RelatedOADNum = (C_MAXRelatedOAD - 1);
	}

	/********************���ӻ�ȡ��������б�****************************/
	V_ulReadOADBuf_All[1] = CFreeNum;
	V_ulReadOADBuf_All[2] = CFreeTime;
	j = 0;
	V_DataOff = ( (C_MAXRelatedOAD - 1) * 4);
	SF_FreezeOADRead(*V_OAD, (uchar8 *)&V_ulReadOADBuf_All[3], &V_DataOff, 2, (uchar8 *)&j);
	V_ulReadOADBuf_All[0] = (j + 2);				/*��һ���������й���OAD����*/

	/************************************************/
	i = 0;
	if(V_RelatedOADNum != 0)
	{
		j = 0;
		V_ulPlan = 0xFFFFFFFF;
		for( ; i < V_RelatedOADNum; i++ )
		{
			j++;
			V_ulReadOADBuf[j] = V_OAD->Rd_RecordRelatedOI[i];
			if(V_OAD->Rd_RecordRelatedOI[i] == CFreeTime)			/*����ʱ��*/
			{
				V_2021No = j;
				continue;
			}

			if(V_OAD->Rd_RecordRelatedOI[i] == CFreeNum)			/*����ʱ��Ͷ��������������������б�*/
			{
				V_2023No = j;
				continue;
			}

			if(0xFFFFFFFF == V_ulPlan)
			{
				V_ulPlan = (V_ulReadOADBuf[j] & 0x0000E000);
			}

			if( V_ulPlan != (V_OAD->Rd_RecordRelatedOI[i] & 0x0000E000) )
			{
				V_ucRetrun = C_ForbidenRW;
				return V_ucRetrun;
			}
		}

		if(V_2021No != 0xFF)
		{
			V_ulReadOADBuf[V_2021No] &= 0xFFFF1FFF;
		}

		if(V_2023No != 0xFF)
		{
			V_ulReadOADBuf[V_2023No] &= 0xFFFF1FFF;
		}
	}
	else								/*��ȡ���õ�OAD*/
	{
		if(V_usObject == 2)				/*���Ӷ��᲻�����ȡRCSDΪ0����ȡ*/
		{
			V_ucRetrun = C_ForbidenRW;
            return V_ucRetrun;
		}

		V_ulPlan = 0;					/*������¼��ȡʱ�����Ƿ��Ӷ��ᣬ��ʱ���Ժ�ֻ����0;*/
		memcpy( (uchar8 *)&V_ulReadOADBuf[1], (uchar8 *)&V_ulReadOADBuf_All[1], (V_ulReadOADBuf_All[0] * 4) );
		V_RelatedOADNum = (uchar8 )V_ulReadOADBuf_All[0];
		j = V_RelatedOADNum;
	}

	if( j > (C_FreezeMAXRelatedOAD + 2) )
	{
		V_ucRetrun = C_OverStep_DAR;	/*��ѡ����50��Ӧ��Խ��*/
		return V_ucRetrun;
	}

	if( j < (C_MAXRelatedOAD - 1) )		/*û���õ���ֱ�����oxFFFFFFFF*/
	{
		for( ; j < (C_MAXRelatedOAD - 1); j++)
		{
			V_ulReadOADBuf[j+1] = 0xFFFFFFFF;
		}
	}

	V_DataLenMax -= ( (V_RelatedOADNum + V_ucFixedOADNum) * 5 );		/*��ȥOAD������Ҫ�ĸ���*/

	/*********************ȥ�����ȡ�����Ų�ͬ��OAD*****************************/
	j = (uchar8)V_ulReadOADBuf_All[0];		/*��һ���������й���OAD����*/
	for(i = 2; i < j; i++)
	{
		if( (V_ulReadOADBuf_All[i + 1] & 0x0000E000) != V_ulPlan)
		{
			for(k = (i + 1); k < j; k++ )
			{
				V_ulReadOADBuf_All[k] = V_ulReadOADBuf_All[k + 1];		/*��ЧOAD��ǰ�ƶ�һ��*/
			}

			V_ulReadOADBuf_All[0] -= 1;
		}
	}
	/*************************���ýӿں�����ȡ�����¼**************************/
	V_usDataLen = 1536;
	memset(V_SaveFreezeTimeBuf, 0x00, C_SaveFreezeTimeBufLen);				/*����ȥ���󽫻����е���������*/

	V_EventRead.pV_ulROAD = V_ulReadOADBuf;									/*����¼�����OAD�б�ֵ*/
	V_EventRead.V_usROAD_Num = j;											/*����¼�Ĺ���OAD�ĸ���*/
	V_EventRead.V_ucReadMode = C_ComMode;									/*ͨ�Ŷ�ȡ*/
#if 0
	if( ( V_ucRSTTemp[0] == 1 ) || ( V_ucRSTTemp[0] == 2 ) )
	{
		if( V_SelectOAD == CDate_Time )
		{
			V_SelectOAD = CFreeTime;												/*�����л��·���ǰʱ���OAD������ȡ������ת�ɶ���ʱ���·�*/
			PF_Ulong32ToBuffer4(&V_EventRead.pV_ulROAD[1], &V_SelectOAD, CL_OAD);	/*OAD*/
		}
	}
#endif
	V_ucSupplementaryInformation.pV_usEncode = (ushort16 *)V_SaveFreezeTimeBuf;
	V_SaveFreezeTimeBuf[0] = 0x68;
	V_ucRetrun =  InF_GetData_Record(&V_EventRead, V_DataTemp, &V_usDataLen, &V_ucSupplementaryInformation);

	/*************************���б���*****************************************/
	if( ( V_ucSupplementaryInformation.V_ucNxtFrame == 1 ) && ( V_ucRetrun == C_OK ) )	/*����֡*/
	{
		V_ucRetrun = C_MaxResponseLen_ERR;
	}

	if( ( V_ucRetrun == C_OK ) || ( V_ucRetrun == C_MaxResponseLen_ERR ) )
	{
		V_DataOff645 = 0;
		V_DataOff = 3;
		V_usReadRecordNum = V_ucSupplementaryInformation.V_ucFrameNum;					/*���Զ������ļ�¼����*/
		if(V_DataOff > V_DataLenMax)
		{
			return C_OverStep_DAR;
		}

		V_DataLenMax -= 3;
		P_DataBuf[V_DataOff] = V_usReadRecordNum;								/*��ֵ����,����Ҫ�޸�*/
		V_DataOff++;
		V_DataLenMax--;
		if(V_DataOff > V_DataLenMax)
		{
			return C_OverStep_DAR;
		}

		for( k = 0; k < V_usReadRecordNum ; k++ )
		{
			/*���ݲ��4����ʵ��ֻ�ܱ���3�������*/
			V_DataOffTemp = V_DataOff;													/*�ݴ���һ���Ѿ����������ƫ��*/

			i=0;
			for( ; i < V_RelatedOADNum; i++ )
			{
				for( j = 0; j < Str_FrozenConvert_Table_Len; j++ )
				{
					if(V_usObject == 2)		/*���Ӷ������⴦��*/
					{
						if(V_OAD->Rd_RecordRelatedOINum == 0)			/*��ѡ����Ϊ0����ʾ��ȡ������*/
						{
							if( ( V_ulReadOADBuf[i + 1] & 0xFFFF1FFF ) == Str_FrozenConvert_Table[j].V_ulOAD )
							{
								Str_Encode = Str_FrozenConvert_Table[j];
								SF_FrozenDataFF_NextNum(&Str_Encode, j);
								break;
							}
						}
						else
						{
							if( ( V_OAD->Rd_RecordRelatedOI[i] & 0xFFFF1FFF ) == Str_FrozenConvert_Table[j].V_ulOAD )
							{
								Str_Encode = Str_FrozenConvert_Table[j];
								SF_FrozenDataFF_NextNum(&Str_Encode, j);
								break;
							}
						}

					}
					else
					{
						if( ( V_ulReadOADBuf[i + 1] & 0xFFFF1FFF ) == Str_FrozenConvert_Table[j].V_ulOAD )
						{
							Str_Encode = Str_FrozenConvert_Table[j];
							SF_FrozenDataFF_NextNum(&Str_Encode, j);
							break;
						}
					}
				}

				if(j >= Str_FrozenConvert_Table_Len)
				{
					if( V_ulReadOADBuf[i + 1] == 0x20210200 )
					{
						if( SF_MaxLenSubAndJudge( &V_DataLenMax, C_date_time_s ) != C_OK )
						{
							V_ucOverAPDUFlay = 0x68;
							goto DataOrganize;
						}

						P_DataBuf[V_DataOff] = C_date_time_s;
						V_ucLen = SF_DataExchangeTo698_BasicData(&P_DataBuf[V_DataOff], &V_DataTemp[V_DataOff645], 8, CLDate_Time);
						V_DataOff645 += CLDate_Time;
						V_DataOff += (V_ucLen + 1);
					}
					else if( V_ulReadOADBuf[i + 1] == 0x20230200 )
					{
						if( SF_MaxLenSubAndJudge( &V_DataLenMax, C_double_long_unsigned ) != C_OK )
						{
							V_ucOverAPDUFlay = 0x68;
							goto DataOrganize;
						}

						P_DataBuf[V_DataOff] = C_double_long_unsigned;
						V_DataOff++;
						P_DataBuf[V_DataOff] = V_DataTemp[V_DataOff645 + 3];
						V_DataOff++;
						P_DataBuf[V_DataOff] = V_DataTemp[V_DataOff645 + 2];
						V_DataOff++;
						P_DataBuf[V_DataOff] = V_DataTemp[V_DataOff645 + 1];
						V_DataOff++;
						P_DataBuf[V_DataOff] = V_DataTemp[V_DataOff645];
						V_DataOff++;
						V_DataOff645 += 4;
					}
					else
					{
						if( SF_MaxLenSubAndJudge( &V_DataLenMax, C_NULL ) != C_OK )
						{
							V_ucOverAPDUFlay = 0x68;
							goto DataOrganize;
						}
						P_DataBuf[V_DataOff] = 0;
						V_DataOff ++;
						if(V_DataTemp[V_DataOff645] == C_NotSupportAOD_DataBB)
						{
							V_DataOff645 ++;
						}
					}
					continue;
				}

				if( ( SF_JudgeAllAA(&V_DataTemp[V_DataOff645], Str_Encode.V_uc645Length ) == C_OK )
				 && ( SF_Get_Active_OAD(V_ulReadOADBuf[i + 1] | V_ulPlan, &V_ulReadOADBuf_All[0], Str_Encode.V_uc698Type, C_End_EventState ) == C_AAorBBIsDisactive ) )	/*��Ч*/
				{
					if( SF_MaxLenSubAndJudge( &V_DataLenMax, C_NULL ) != C_OK )
					{
						V_ucOverAPDUFlay = 0x68;
						goto DataOrganize;
					}
					P_DataBuf[V_DataOff] = 0;
					V_DataOff ++;
					V_DataOff645 += Str_Encode.V_uc645Length;
					continue;
				}
				else if( ( V_DataTemp[V_DataOff645] == C_NotSupportAOD_DataBB )
					 &&  ( SF_Get_Active_OAD(V_ulReadOADBuf[i + 1] | V_ulPlan, &V_ulReadOADBuf_All[0], Str_Encode.V_uc698Type, C_End_EventState ) == C_AAorBBIsDisactive ) )	/*��Ч*/
				{
					if( SF_MaxLenSubAndJudge( &V_DataLenMax, C_NULL ) != C_OK )
					{
						V_ucOverAPDUFlay = 0x68;
						goto DataOrganize;
					}
					P_DataBuf[V_DataOff] = 0;
					V_DataOff ++;
					V_DataOff645 += 1;
					continue;
				}

				uchar8 V_645Len, V_us698Len;

				if( ( Str_Encode.V_ulOAD & 0xfff00000 ) == 0x21300000 )			/*��ѹ�ϸ������⴦��*/
				{
					if(V_DataLenMax < 23)
					{
						V_ucOverAPDUFlay = 0x68;
						goto DataOrganize;
					}

					V_DataLenMax -= 23;
					SF_Encode_VolRates(&Str_Encode, P_DataBuf, V_DataTemp, &V_DataOff, &V_DataOff645);
				}
				else if( ( Str_Encode.V_uc698Type == C_array ) || ( Str_Encode.V_uc698Type == C_structure ) )
				{
					if( SF_JugeDemadFF( &V_DataTemp[0 + V_DataOff645], CLPos_Ac_Tol_De_0 ) == C_OK )
					{
						if( SF_MaxLenSubAndJudge( &V_DataLenMax, C_NULL ) != C_OK )
						{
							V_ucOverAPDUFlay = 0x68;
							goto DataOrganize;
						}
						P_DataBuf[V_DataOff] = C_NULL;
						V_DataOff++;
						V_DataOff645 += Str_Encode.V_uc645Length;
					}
					else
					{
						if( SF_MaxLenSubAndJudge( &V_DataLenMax, C_unsigned ) != C_OK )
						{
							V_ucOverAPDUFlay = 0x68;
							goto DataOrganize;
						}

						if( ( Str_Encode.V_uc698Type == Str_Encode.V_uc698NextType ) && ( Str_Encode.V_uc698Type == C_structure ) )
						{
							if(V_DataLenMax >= 2)
							{
								V_DataLenMax -= 2;
							}
							else
							{
								V_ucOverAPDUFlay = 0x68;
								goto DataOrganize;
							}
						}
						else
						{
							P_DataBuf[V_DataOff] = Str_Encode.V_uc698Type;
							V_DataOff++;
							P_DataBuf[V_DataOff] = Str_Encode.V_uc698NextNum;
							V_DataOff++;
						}

						uchar8 V_DataLenTemp;

		                V_DataLenTemp = Str_Encode.V_uc645Length / Str_Encode.V_uc698NextNum;
						for( j = 0; j < Str_Encode.V_uc698NextNum; j++ )
						{
							if( SF_MaxLenSubAndJudge( &V_DataLenMax, C_NULL ) != C_OK )
							{
								V_ucOverAPDUFlay = 0x68;
								goto DataOrganize;
							}

							P_DataBuf[V_DataOff] = Str_Encode.V_uc698NextType;
							V_DataOff++;
							if( Str_Encode.V_uc698NextType == C_structure )			/*�������ֻ���������*/
							{
								if( SF_JugeDemadFF( &V_DataTemp[0 + V_DataOff645], CLPos_Ac_Tol_De_0 ) == C_OK )
								{
									if( SF_MaxLenSubAndJudge( &V_DataLenMax, C_NULL ) != C_OK )
									{
										V_ucOverAPDUFlay = 0x68;
										goto DataOrganize;
									}
									P_DataBuf[V_DataOff] = C_NULL;
									V_DataOff++;
								}
								else
								{
									if( SF_MaxLenSubAndJudge(&V_DataLenMax, C_NULL ) != C_OK )
									{
										V_ucOverAPDUFlay = 0x68;
										goto DataOrganize;
									}

									P_DataBuf[V_DataOff] = 2;
									V_DataOff++;
									if( SF_MaxLenSubAndJudge( &V_DataLenMax, C_double_long_unsigned ) != C_OK )
									{
										V_ucOverAPDUFlay = 0x68;
										goto DataOrganize;
									}

									P_DataBuf[V_DataOff] = C_double_long_unsigned;
									if( ( ( Str_Encode.V_ulOAD & 0x00F00000 ) == 0x00300000 )
									 || ( ( Str_Encode.V_ulOAD & 0x00F00000 ) == 0x00400000 ) )
									{
										P_DataBuf[V_DataOff] = C_double_long;
									}

									V_645Len = CL_double_long;
									V_us698Len = SF_DataExchangeTo698_BasicData(&P_DataBuf[V_DataOff], &V_DataTemp[0 + V_DataOff645], 4, V_645Len);
									V_DataOff += (V_us698Len + 1);
									if( SF_MaxLenSubAndJudge( &V_DataLenMax, C_date_time_s ) != C_OK )
									{
										V_ucOverAPDUFlay = 0x68;
										goto DataOrganize;
									}

									P_DataBuf[V_DataOff] = C_date_time_s;
									V_645Len = CL_date_time_s;
									V_us698Len = SF_DataExchangeTo698_BasicData(&P_DataBuf[V_DataOff], &V_DataTemp[V_us698Len + V_DataOff645], 10, V_645Len);
									if( ( P_DataBuf[V_DataOff + V_us698Len] == 0xFF ) && ( P_DataBuf[V_DataOff + V_us698Len - 1] != 0xFF ) )
									{
										P_DataBuf[V_DataOff+V_us698Len] = 0x00;
									}

									V_DataOff += (V_us698Len + 1);
								}

							}
							else if(Str_Encode.V_uc698NextType == C_TZone)		/*ʱ����*/
							{
								V_DataOff--;
								p_TableAddr = (Str_DI0_DataType_PaTable*)GV_Str_DI0_DataType_ZPaTable;

								if( SF_MaxLenSubAndJudge( &V_DataLenMax, C_unsigned ) != C_OK )
								{
									V_ucOverAPDUFlay = 0x68;
									goto DataOrganize;
								}

								P_DataBuf[V_DataOff] = C_structure;
								V_DataOff++;
								P_DataBuf[V_DataOff] = 3;
								V_DataOff++;
								for( m = 0; m < 3; m++ )
								{
									if( SF_MaxLenSubAndJudge( &V_DataLenMax, p_TableAddr[m].DataType ) != C_OK )
									{
										V_ucOverAPDUFlay = 0x68;
										goto DataOrganize;
									}

									P_DataBuf[V_DataOff] = p_TableAddr[m].DataType;
									SF_DataExchangeTo698_BasicData(&P_DataBuf[V_DataOff], &V_DataTemp[V_DataOff645 + m], p_TableAddr[m].DataLen_698, p_TableAddr[m].DataLen_645);
									V_DataOff += p_TableAddr[m].DataLen_698;
									V_DataOff++;
								}
							}
							else if( Str_Encode.V_uc698NextType == C_SettleDay )	/*������*/
							{
								V_DataOff--;
								if( Str_Encode.V_ulOAD != 0x41160200 )
								{
									V_DataOff -= 2;
								}

								p_TableAddr = (Str_DI0_DataType_PaTable*)GV_Str_DI0_DataType_SDPaTable;
								if( SF_MaxLenSubAndJudge( &V_DataLenMax, C_unsigned ) != C_OK )
								{
									V_ucOverAPDUFlay = 0x68;
									goto DataOrganize;
								}

								P_DataBuf[V_DataOff] = C_structure;
								V_DataOff++;
								P_DataBuf[V_DataOff] = 2;
								V_DataOff++;
								for( m = 0; m < 2; m++ )
								{
									if( SF_MaxLenSubAndJudge( &V_DataLenMax, p_TableAddr[m].DataType ) != C_OK )
									{
										V_ucOverAPDUFlay = 0x68;
										goto DataOrganize;
									}

									P_DataBuf[V_DataOff] = p_TableAddr[m].DataType;
									SF_DataExchangeTo698_BasicData(&P_DataBuf[V_DataOff], &V_DataTemp[V_DataOff645 + m], p_TableAddr[m].DataLen_698, p_TableAddr[m].DataLen_645);
									V_DataOff += p_TableAddr[m].DataLen_698;
									V_DataOff++;
								}
							}
							else
							{
								V_us698Len = SF_GetDataTypeLen(&P_DataBuf[V_DataOff - 1]);
								if( ( Str_Encode.V_ulOAD & 0xFF000F00 ) == CCom_Ac_LastPulse_FF_0 )
                                {
                                    P_DataBuf[V_DataOff] = V_DataTemp[V_DataOff645];
                                    V_us698Len = C_EnergyCommPulseLastLen;
                                }
#if 0
								else if( ( Str_Encode.V_ulOAD & 0xFF000000 ) == 0x00000000 )		/*����*/
								{
									V_us698Len = SF_EnergyTo698(Str_Encode.V_ulOAD, &V_DataTemp[V_DataOff645], &(P_DataBuf[V_DataOff]), V_DataLenTemp);
								}
#endif
                                else
                                {
                                    V_us698Len = SF_DataExchangeTo698_BasicData(&(P_DataBuf[V_DataOff - 1]), &V_DataTemp[V_DataOff645], V_us698Len, V_DataLenTemp);
								}

								if(V_DataLenMax < V_us698Len)
								{
                                    V_ucOverAPDUFlay = 0x68;
									goto DataOrganize;
								}

								V_DataLenMax -= V_us698Len;
                                V_DataOff += (V_us698Len);
							}

							V_DataOff645 += V_DataLenTemp;
						}
					}
				}
				else
				{
					P_DataBuf[V_DataOff] = Str_Encode.V_uc698Type;
					V_us698Len = SF_GetDataTypeLen(&P_DataBuf[V_DataOff]);
					if( ( P_DataBuf[V_DataOff] == C_bit_string )
					 || ( P_DataBuf[V_DataOff] == C_visible_string ) )
					{
						V_DataOff++;
						P_DataBuf[V_DataOff] = Str_Encode.V_uc698NextNum;
						V_DataOff--;
						V_us698Len = Str_Encode.V_uc698NextNum;
					}

                    if( ( Str_Encode.V_ulOAD & 0xFF000F00 ) == CCom_Ac_LastPulse_FF_0 )
                    {
                        P_DataBuf[V_DataOff + 1] = V_DataTemp[V_DataOff645];
                        V_us698Len = C_EnergyCommPulseLastLen;
                    }
#if 0
					else if( ( Str_Encode.V_ulOAD & 0xFF000000) == 0x00000000 )		/*����*/
					{
						V_us698Len = SF_EnergyTo698(Str_Encode.V_ulOAD, &V_DataTemp[V_DataOff645], &(P_DataBuf[V_DataOff + 1]), Str_Encode.V_uc645Length);
					}
#endif
                    else
                    {
                        V_us698Len = SF_DataExchangeTo698_BasicData(&(P_DataBuf[V_DataOff]), &V_DataTemp[V_DataOff645], V_us698Len, Str_Encode.V_uc645Length);
					}

                    if( ( P_DataBuf[V_DataOff] == C_bit_string )
					 || ( P_DataBuf[V_DataOff] == C_visible_string ) )
					{
						V_DataOff++;
					}

					V_DataOff += (V_us698Len + 1);
					if( V_DataLenMax < ( V_us698Len + 1 ) )
					{
						V_ucOverAPDUFlay = 0x68;
						goto DataOrganize;
					}

					V_DataLenMax -= (V_us698Len + 1);
					V_DataOff645 += Str_Encode.V_uc645Length;
				}
			}
		}

DataOrganize:
		if(V_ucRetrun == C_MaxResponseLen_ERR)
		{
			if( ( V_usReadRecordNum - k ) < (C_SaveFreezeTimeNum - 1) )
			{
				/*��ֵ��һ����ʱ��*/
				SF_MinsAdd_LoadProfile(&V_SaveFreezeTimeBuf[( V_usReadRecordNum - k ) * C_FreezeTimeLen + 2], 1, &V_SaveFreezeTimeBuf[( V_usReadRecordNum - k ) * C_FreezeTimeLen + 2]);	/*��һ����*/
				PF_OneDataReversed(&V_SaveFreezeTimeBuf[( V_usReadRecordNum - k ) * C_FreezeTimeLen + 1], &V_OAD->Rd_RecordSelect[6], C_FreezeTimeLen);
				InF_WriteFreezeData( V_usReadRecordNum - k + 1 );
			}
		}

		if(V_ucOverAPDUFlay == 0x68)
		{
			if(k == 0)
			{
				V_DataOff = 0;
				P_DataBuf[V_DataOff] = 0;
				V_DataOff ++;
				*P_DataOff = V_DataOff;
				V_ucRetrun = C_OK;
				return V_ucRetrun;
			}
			else
			{
				P_DataBuf[3] = k;
				V_ucRetrun = C_MaxResponseLen_ERR;
				V_DataOff = V_DataOffTemp;		/*��ֵ��һ����¼����ƫ�Ƶ�ַ*/
				if( ( V_usReadRecordNum - k - 1 ) < ( C_SaveFreezeTimeNum - 1 ) )
				{
					SF_MinsAdd_LoadProfile(&V_SaveFreezeTimeBuf[( V_usReadRecordNum - k ) * C_FreezeTimeLen + 2], 1, &V_SaveFreezeTimeBuf[( V_usReadRecordNum - k ) * C_FreezeTimeLen + 2]);	/*��һ����*/
					PF_OneDataReversed(&V_SaveFreezeTimeBuf[( V_usReadRecordNum - k ) * C_FreezeTimeLen + 1], &V_OAD->Rd_RecordSelect[6], C_FreezeTimeLen);
					InF_WriteFreezeData( V_usReadRecordNum - k );
				}
			}
		}

		if( ( V_ucRetrun == C_OK ) || ( V_ucRetrun == C_MaxResponseLen_ERR) )
		{
			if( ( V_DataOff - 3 ) >= 256 )
			{
				P_DataBuf[0] = 0x82;
				P_DataBuf[1] = (uchar8)( ( V_DataOff - 3 ) >> 8);
				P_DataBuf[2] = (uchar8)( ( V_DataOff - 3 ) );
				*P_DataOff = V_DataOff;
			}
			else if( ( V_DataOff - 3 ) > 127 )
			{
				for( i = 0; i < ( V_DataOff - 3 ); i++ )
				{
					P_DataBuf[2 + i] = P_DataBuf[3 + i];
				}
				P_DataBuf[0] = 0x81;
				P_DataBuf[1] = (uchar8)( ( V_DataOff - 3 ) );
				*P_DataOff = V_DataOff - 1;
			}
			else
			{
				for( i = 0; i < ( V_DataOff - 3 ); i++ )
				{
					P_DataBuf[1 + i] = P_DataBuf[3 + i];
				}
				P_DataBuf[0] = (uchar8)( ( V_DataOff - 3 ) );
				*P_DataOff = V_DataOff - 2;
			}
		}
		else
		{
			V_ucRetrun = C_OtherErr_DAR;
		}
	}
    else if( V_ucRetrun == C_NoData )
    {
        V_DataOff = 0;
        P_DataBuf[V_DataOff] = 0;
        V_DataOff ++;
        *P_DataOff = V_DataOff;
        V_ucRetrun = C_OK;
    }
    else if(V_ucRetrun == C_RWForbid_DAR)
    {
		;
	}
	else
	{
		V_ucRetrun = C_OtherErr_DAR;
	}

	return V_ucRetrun;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 InF_JudgeNoEndTimeEvent(ulong32 V_EventOAD)
�����������ж��¼���¼�Ƿ�û�н���ʱ��
�����������ȡ��¼OAD
�����������
���ز�����	C_OK��ʾû�н���ʱ�䣬C_Error��ʾ�н���ʱ��
����λ�ã�
��    ע��
*******************************************************************************/

#define C_EventNoEndTime_OIB_Len  20
const uchar8 C_EventNoEndTime_OIB[C_EventNoEndTime_OIB_Len] =
{
	0x12, 0x13, 0x14, 0x15, 0x17, 0x18, 0x19,
	0x1A, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25,
	0x26, 0x27, 0x28, 0x29, 0x51
};
uchar8 InF_JudgeNoEndTimeEvent(ulong32 V_EventOAD)
{
	uchar8 i;

	for( i = 0; i < C_EventNoEndTime_OIB_Len; i++ )
	{
		if( C_EventNoEndTime_OIB[i] == ( (uchar8)( V_EventOAD >> 16 ) ) )
		{
			return C_OK;
		}
	}
	return C_Error;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_Event_SingleReadFF(ulong32 *V_ulReadOADBuf,uchar8 V_Line,uchar8 *P_DataBuf,ushort16 *P_DataLength)
�������������¼����ݴ���
���������	V_Line:1���������;V_MaxLen_Tab2_2����������
������������ݴ��ͨ���շ����棬���ݳ���
���ز��������ػ�ȡ�����Ƿ�ɹ�
����λ�ã�
��    ע��698����645Э�����ӣ��������¼�֧��
*******************************************************************************/
uchar8 SF_Event_SingleReadFF(ulong32 *V_ulReadOADBuf, uchar8 V_Line, uchar8 *P_DataBuf, ushort16 *P_DataLength)
{/*645Э�鴦�������޸� lzy 20211102*/
#if 0
	uchar8		j, V_timeFlash = 0x68, V_MaxLen_Tab2;
	ushort16	V_ucDataLenIn, V_ucDataOffIn, V_Dataoff = 0, V_usDataLen, V_usDataEncode, V_ucLength;
	uchar8		V_DataTemp[C_Comm_Data_MaxLen - CLen_DI], V_ucDataBuff = 0;
	uchar8		  V_ucRetrun, V_ucJudgeAll00 = 0;
	Str_EventChange_Table2 *PStr_Table2;
    uchar8		V_Line_Type;
    uchar8		V_BCDAddResult[3];
    ulong32		V_ulDataHex, V_ulOADTZ;
    uchar8		V_ucWire, V_ucHappening_Flag = C_End_EventState;

 	V_ucRetrun = C_Error;
    V_MaxLen_Tab2 = EventTable1_OADChange698[V_Line].TableLen;
	/*û���õ���ֱ�����oxFFFFFFFF*/
	 for( j = 1; j < C_OADNum; j++)
	 {
		 V_ulReadOADBuf[j] = 0xFFFFFFFF;
	 }
	 for( j = 0; j < V_MaxLen_Tab2; j++ )
	 {
	 	PStr_Table2 = (Str_EventChange_Table2*)(EventTable1_OADChange698[V_Line].PStr_EventChange_Table2);
	 	V_ulReadOADBuf[1] =  PStr_Table2[j].RelateOAD_645;


		/*��1�����ݶ��¼���¼�ӿں���*/
		V_usDataLen = C_Comm_Data_MaxLen-CLen_DI;
		if(V_ulReadOADBuf[1] == CRelayOpen_OpeCode_1)
		{
			SF_Event_Relay_JudgeAll00(V_ulReadOADBuf[0], &V_ucJudgeAll00);
			V_ucDataLenIn = CLRelayOpen_OpeCode_1;
			if(V_ucJudgeAll00 == C_ALL00_Flag)
			{
				memset(V_DataTemp, 0x00, V_ucDataLenIn);
			}
			else
			{
				memset(V_DataTemp, 0xFF, V_ucDataLenIn);
			}
            V_ucRetrun = C_OK;
		}
		else if(V_ulReadOADBuf[1] == C_HP_TolPowerCon) /*���������ʷ���Ĭ��00*/
		{
			V_DataTemp[0] = 0;
		}
		else
		{
			if( ( V_ulReadOADBuf[0] & 0x000000FF ) == 0x00000001 )
			{
				V_ucRetrun = Inf_ReadEventLast_H(V_ulReadOADBuf, V_DataTemp, &V_usDataLen, V_timeFlash, &V_ucHappening_Flag);
			}
			else
			{
				V_ucRetrun = InF_ReadEventData(V_ulReadOADBuf, &V_ucDataBuff, V_DataTemp, &V_ucDataBuff, &V_usDataLen,V_timeFlash);
			}
		}
		if( ( V_ucRetrun == C_OK ) && ( SF_JudgeAllAA( V_DataTemp, V_usDataLen ) != C_OK )
           && ( V_DataTemp[0] != 0xBB))
		{
			if( ( (V_ulReadOADBuf[1]&0xFF000000) == 0x00000000) && (V_usDataLen == 4) )		/*��������Ϊ645�¼���¼�еĵ��ܾ�Ϊ�ܵ��ܣ��޷��ʵ��ܣ������ж��˳���4�ֽ�*/
			{
				SF_EnergyT0_645(V_DataTemp, V_DataTemp, &V_usDataLen, 4, (uchar8)( V_ulReadOADBuf[1] >> 16 ) );
			}
			if( PStr_Table2[j].ReadFlag == C_NormalRead)
			{
				V_ucDataLenIn = PStr_Table2[j].DataLen;
				PF_CopyDataBytes_698(V_DataTemp, &P_DataBuf[V_Dataoff], V_ucDataLenIn);
				V_Dataoff += V_ucDataLenIn;
			}
            else if(PStr_Table2[j].ReadFlag == C_ReadDeal_E)
            {
                V_DataTemp[C_TolLoss_CurrOffsetASign] &= 0x7F;
                V_DataTemp[C_TolLoss_CurrOffsetBSign] &= 0x7F;
                V_DataTemp[C_TolLoss_CurrOffsetCSign] &= 0x7F;

                V_ucDataLenIn = CLLine_Type;
                InF_Read_Data(CLine_Type, &V_Line_Type, &V_ucDataLenIn, &V_usDataEncode);					/*����������*/
                if(V_Line_Type == C_3P3W)
                {
                    V_ucWire = 2;
                    memset(&V_DataTemp[C_TolLoss_CurrOffsetB], 0x00, CLPhaseA_Curr);
                }
                else
                {
                    V_ucWire = 3;
                }

                PF_BCDAddBytes(&V_DataTemp[C_TolLoss_CurrOffsetA], &V_DataTemp[C_TolLoss_CurrOffsetB], V_BCDAddResult, CLPhaseA_Curr);
                PF_BCDAddBytes(V_BCDAddResult, &V_DataTemp[C_TolLoss_CurrOffsetC], V_BCDAddResult, CLPhaseA_Curr);
                PF_BCDtoHexBytes(V_BCDAddResult, &V_ulDataHex, CLPhaseA_Curr);
                V_ulDataHex = V_ulDataHex / V_ucWire;
                V_ucDataLenIn = CLPhaseA_Curr;
                PF_HextoBCDBytes(&V_ulDataHex, V_BCDAddResult,(uchar8 *)&V_ucDataLenIn);
                PF_CopyDataBytes_698(V_BCDAddResult, &P_DataBuf[V_Dataoff], V_ucDataLenIn);
                V_Dataoff += V_ucDataLenIn;
            }
            else if(PStr_Table2[j].ReadFlag == C_ReadDeal_F)
            {
              V_ucDataLenIn = PStr_Table2[j].DataLen;
              P_DataBuf[V_Dataoff] = V_DataTemp[C_RelayFa_State_Offset];
              V_Dataoff += V_ucDataLenIn;
            }
            else if(PStr_Table2[j].ReadFlag == C_ReadDeal_G)   /*ʱ�����̼�¼���ݵ���*/
            {
            	/*ʱ�����̼�¼�У�������ʱ��������λ�õ���*/
                PF_CopyDataBytes(V_DataTemp, &P_DataBuf[V_Dataoff + CLProgTZ_CurrentPart_Note_OnlyData], CLProgTZ_CurrentPart_Note_OnlyData);

                /*��ȡ�¼���¼�е�ǰ��ʱ����*/
                V_ulOADTZ = CProgTZ_CurrentPart_Degree;
                V_ulOADTZ = V_ulOADTZ|(V_ulReadOADBuf[0] & 0x000000FF);
                V_ucLength = CLProgTZ_CurrentPart_Note_1;
                InF_Read_Data(V_ulOADTZ, V_DataTemp, &V_ucLength, &V_usDataEncode);
                PF_CopyDataBytes(&V_DataTemp[C_TZData_offset_645], &P_DataBuf[V_Dataoff], CLProgTZ_CurrentPart_Note_OnlyData);
              	V_Dataoff = V_Dataoff + CLProgTZ_CurrentPart_Note_OnlyData + CLProgTZ_CurrentPart_Note_OnlyData;
            }
			else
			{
				V_ucDataOffIn = ( PStr_Table2[j].ReadFlag - 1)* (PStr_Table2[j].DataLen);
				V_ucDataLenIn = PStr_Table2[j].DataLen;
				PF_CopyDataBytes_698(&V_DataTemp[V_ucDataOffIn], &P_DataBuf[V_Dataoff],V_ucDataLenIn);
				V_Dataoff +=V_ucDataLenIn;
			}
		}
		else
		{
			if( PStr_Table2[j].ReadFlag == C_NormalRead )
      		{
				V_ucDataLenIn = PStr_Table2[j].DataLen;
				memset(V_DataTemp, 0x00, V_ucDataLenIn);
				PF_CopyDataBytes_698(&V_DataTemp[0], &P_DataBuf[V_Dataoff], V_ucDataLenIn);
				V_Dataoff += V_ucDataLenIn;
      		}
      		else
     		{
				V_ucDataLenIn = PStr_Table2[j].DataLen;
        		memset(V_DataTemp, 0x00, V_ucDataLenIn);
				PF_CopyDataBytes_698(&V_DataTemp[0], &P_DataBuf[V_Dataoff], V_ucDataLenIn);
				V_Dataoff +=V_ucDataLenIn;
      		}
		}
	 }
	 *P_DataLength = V_Dataoff;
#endif
	return C_OK;
}
/*******************************************************************************
����ԭ�ͣ�void SF_Event_Relay_JudgeAll00(ulong32 V_ulOAD,uchar8 *p_VFlag)
��������������բ�¼��ж��¼�����ʱ���Ƿ�ȫ0
���������V_ulOAD:�¼���OAD
���������ȫ0������0x55,��ȫ0�����أ�0xAA
���ز�����
����λ�ã�
��    ע��698����645Э�����ӣ�������բ�¼������������ߴ������
*******************************************************************************/
void SF_Event_Relay_JudgeAll00(ulong32 V_ulOAD, uchar8 *p_VFlag)
{/*645Э�鴦�������޸� lzy 20211102*/
#if 0
	ulong32 V_ucBuffer[3];
	uchar8 V_timeFlash = 0x68, V_DataTemp[CLEventHPTime];
	uchar8 V_Data_1 = 0, V_Return, i, V_ucHappening_Flag = C_End_EventState;
	ushort16 V_usDataLen;

	V_ucBuffer[0] = V_ulOAD;
	V_ucBuffer[1] = CEventHPTime;
	V_ucBuffer[2] = 0xFFFFFFFF;

	/*��1�����ݶ��¼���¼�ӿں���*/
	V_usDataLen = CLEventHPTime;
	if( ( V_ucBuffer[0] & 0x000000FF ) == 0x00000001 )
	{
		V_Return = Inf_ReadEventLast_H(V_ucBuffer,V_DataTemp, &V_usDataLen, V_timeFlash, &V_ucHappening_Flag);
	}
	else
	{
		V_Return = InF_ReadEventData(V_ucBuffer, &V_Data_1, V_DataTemp, &V_Data_1, &V_usDataLen, V_timeFlash);
	}
	if( ( V_Return == C_OK ) && ( SF_JudgeAllAA( V_DataTemp, V_usDataLen) != C_OK  )
	&&  ( V_DataTemp[0] != 0xBB ) )
	{
		for( i = 0; i < V_usDataLen; i++ )
		{
			if( V_DataTemp[i] != 0 )
			{
				*p_VFlag = C_NoALL00_Flag;
				return ;
			}
		}
	}
	*p_VFlag = C_ALL00_Flag;
#endif
	return;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_Event_SingleRead(Str_Comm_645 *pV_645Frame,ulong32 *V_ulReadOADBuf,uchar8 V_Line,uchar8 *P_DataBuf,ushort16 *P_DataLength)
�������������¼����ݴ���
���������V_Line:1���������;V_MaxLen_Tab2_2����������
������������ݴ��ͨ���շ����棬���ݳ���
���ز��������ػ�ȡ�����Ƿ�ɹ�
����λ�ã�
��    ע��698����645Э�����ӣ��������¼�֧��
*******************************************************************************/
uchar8 SF_Event_SingleRead(Str_Comm_645 *pV_645Frame, ulong32 *V_ulReadOADBuf, uchar8 V_Line, uchar8 *P_DataBuf, ushort16 *P_DataLength)
{/*645Э�鴦�������޸� lzy 20211102*/
#if 0
	uchar8 j, V_timeFlash = 0x68, V_MaxLen_Tab2;
	ushort16 V_Dataoff = 0, V_usDataLen;
	uchar8 V_DataTemp[C_Comm_Data_MaxLen-CLen_DI], V_ucBuffer[4], V_ucDataBuff = 0;
	uchar8 V_ucDataOffIn, V_ucDataLenIn, V_ucRetrun, V_ucJudgeAll00 = 0, V_ucHappening_Flag = C_End_EventState;
	Str_EventChange_Table2 *PStr_Table2;

 	V_ucRetrun = C_Error;
	V_MaxLen_Tab2 = EventTable1_OADChange698[V_Line].TableLen;
	PF_Ulong32ToBuffer4(V_ucBuffer, &pV_645Frame->DI, 4);

	/*û���õ���ֱ�����oxFFFFFFFF*/
	 for( j = 1; j < C_OADNum; j++ )
	 {
		 V_ulReadOADBuf[j] = 0xFFFFFFFF;
	 }
	 for( j = 0; j < V_MaxLen_Tab2; j++ )
	 {
	 	if( ( j + 1 ) == V_ucBuffer[1] )	/*����ϵ��ӦDI1*/
	 	{
	 		PStr_Table2 = (Str_EventChange_Table2*)(EventTable1_OADChange698[V_Line].PStr_EventChange_Table2);
	 		V_ulReadOADBuf[1] =  PStr_Table2[j].RelateOAD_645;

			if(V_ulReadOADBuf[1] == CRelayOpen_OpeCode_1)
			{
				SF_Event_Relay_JudgeAll00(V_ulReadOADBuf[0], &V_ucJudgeAll00);
				V_ucDataLenIn = CLRelayOpen_OpeCode_1;
				if(V_ucJudgeAll00 == C_ALL00_Flag)
				{
					memset(V_DataTemp, 0x00, V_ucDataLenIn);
				}
				else
				{
					memset(V_DataTemp, 0xFF, V_ucDataLenIn);
				}
				PF_CopyDataBytes_698(&V_DataTemp[0], &P_DataBuf[V_Dataoff], V_ucDataLenIn);
				V_ucRetrun = C_OK;
				*P_DataLength = V_ucDataLenIn;
				break;
			}

			/*��1�����ݶ��¼���¼�ӿں���*/
			V_usDataLen = C_Comm_Data_MaxLen - CLen_DI;
			if( ( V_ulReadOADBuf[0]&0x000000FF) == 0x00000001)
			{
				V_ucRetrun = Inf_ReadEventLast_H(V_ulReadOADBuf, V_DataTemp, &V_usDataLen, V_timeFlash, &V_ucHappening_Flag);
			}
			else
			{
                V_ucRetrun = InF_ReadEventData(V_ulReadOADBuf, &V_ucDataBuff, V_DataTemp, &V_ucDataBuff, &V_usDataLen, V_timeFlash);
			}
            if( ( V_ucRetrun == C_OK ) && ( SF_JudgeAllAA( V_DataTemp, V_usDataLen ) != C_OK )
               && ( V_DataTemp[0] != 0xBB ) )
			{
				if( ( ( V_ulReadOADBuf[1] & 0xFF000000 ) == 0x00000000 ) && ( V_usDataLen == 4 ) )	/*��������Ϊ645�¼���¼�еĵ��ܾ�Ϊ�ܵ��ܣ��޷��ʵ��ܣ������ж��˳���4�ֽ�*/
				{
					SF_EnergyT0_645(V_DataTemp, V_DataTemp, &V_usDataLen, 4, (uchar8)( V_ulReadOADBuf[1] >> 16 ) );
				}
				if( PStr_Table2[j].ReadFlag == C_NormalRead)
				{
                    V_ucDataOffIn = PStr_Table2[j].DataLen;
					PF_CopyDataBytes_698(V_DataTemp, &P_DataBuf[V_Dataoff], V_ucDataOffIn);
					V_Dataoff += V_ucDataOffIn;
				}
				else
				{
					V_ucDataOffIn = ( PStr_Table2[j].ReadFlag - 1) * (PStr_Table2[j].DataLen);
					V_ucDataLenIn = PStr_Table2[j].DataLen;
					PF_CopyDataBytes_698(&V_DataTemp[V_ucDataOffIn], &P_DataBuf[V_Dataoff], V_ucDataLenIn);
					V_Dataoff += V_ucDataLenIn;
				}
			}
			else
			{
				if( PStr_Table2[j].ReadFlag == C_NormalRead)
                {
				 	V_ucDataLenIn = PStr_Table2[j].DataLen;
				 	memset(V_DataTemp, 0x00, V_ucDataLenIn);
				 	PF_CopyDataBytes_698(&V_DataTemp[0], &P_DataBuf[V_Dataoff], V_ucDataLenIn);
				 	V_Dataoff += V_ucDataLenIn;
                }
                else
                {
					V_ucDataLenIn = PStr_Table2[j].DataLen;
                    memset(V_DataTemp, 0x00, V_ucDataLenIn);
					PF_CopyDataBytes_698(&V_DataTemp[0], &P_DataBuf[V_Dataoff], V_ucDataLenIn);
					V_Dataoff += V_ucDataLenIn;
                }
			}
	 		*P_DataLength = V_Dataoff;
			V_ucRetrun = C_OK;
			break;
		}
	}
	return V_ucRetrun;
#endif
    return C_OK;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_Read_DemandEvent(ulong32 V_ulDI, uchar8 V_ucDI0,uchar8 *P_DataBuf,uchar8 *P_DataLength)
�����������������¼����ݴ���
���������	V_ulDI :645DI V_ucDI0:DI0
������������ݴ��ͨ���շ����棬���ݳ���
���ز�����	���ػ�ȡ�����Ƿ�ɹ�
����λ�ã�
��    ע��698����645Э�����ӣ��������¼�֧��
*******************************************************************************/
uchar8 SF_Read_DemandEvent(ulong32 V_ulDI, uchar8 V_ucDI0, uchar8 *P_DataBuf, uchar8 *P_DataLength)
{/*645Э�鴦�������޸� lzy 20211102*/
#if 0
	uchar8 j, V_timeFlash = 0x68;
	ushort16 V_Dataoff = 0, V_usDataLen;
	uchar8 V_DataTemp[C_Comm_Data_MaxLen - CLen_DI], V_ucDataBuff = 0;
	uchar8 V_ucDataLenIn, V_ucRetrun = C_Error, V_ucJudgeAll00 = 0, V_ucHappening_Flag = C_End_EventState;
    ulong32 V_ulReadOADBuf[3];

    V_ulReadOADBuf[0] = 0x30140200 | V_ucDI0;
    V_ulReadOADBuf[2] = 0xFFFFFFFF;											/*û���õ���ֱ�����oxFFFFFFFF*/

	if( ( V_ulDI & 0xFFFFFFF0 ) == ( CDe_Clear_NoteE_1 & 0xFFFFFFF0 ) )
	{
		for( j = 0; j < EventTable2_RelateOAD14_E1_Len; j++ )
		{
			V_ulReadOADBuf[1] =  EventTable2_RelateOAD14_E1[j].RelateOAD_645;
			if(V_ulReadOADBuf[1] == CRelayOpen_OpeCode_1)
			{
				SF_Event_Relay_JudgeAll00(V_ulReadOADBuf[0], &V_ucJudgeAll00);
				V_ucDataLenIn = CLRelayOpen_OpeCode_1;
				if(V_ucJudgeAll00 == C_ALL00_Flag)
				{
					memset(V_DataTemp, 0x00, V_ucDataLenIn);
				}
				else
				{
					memset(V_DataTemp, 0xFF, V_ucDataLenIn);
				}
				PF_CopyDataBytes_698(&V_DataTemp[0], &P_DataBuf[V_Dataoff], V_ucDataLenIn);
				V_Dataoff += V_ucDataLenIn;
				continue;
			}

			/*��1�����ݶ��¼���¼�ӿں���*/
			V_usDataLen = C_Comm_Data_MaxLen - CLen_DI;
			if( ( V_ulReadOADBuf[0] & 0x000000FF ) == 0x00000001 )
			{
				V_ucRetrun = Inf_ReadEventLast_H(V_ulReadOADBuf, V_DataTemp, &V_usDataLen, V_timeFlash, &V_ucHappening_Flag);
			}
			else
			{
                V_ucRetrun = InF_ReadEventData(V_ulReadOADBuf, &V_ucDataBuff, V_DataTemp, &V_ucDataBuff, &V_usDataLen, V_timeFlash);
			}

            if( ( V_ucRetrun == C_OK ) && ( SF_JudgeAllAA( V_DataTemp, V_usDataLen ) != C_OK )
			 && ( V_DataTemp[0] != 0xBB ) && ( V_usDataLen != 0x01 ) )			/*���������¼���¼�в��漰�����ܣ���˲����޸�*/
			{
                if(V_ulReadOADBuf[1] == CEventHPTime)
                {
                  V_usDataLen -= 1;
                }
				PF_CopyDataBytes_698(V_DataTemp, &P_DataBuf[V_Dataoff], V_usDataLen);
				V_Dataoff += V_usDataLen;

			}
			else
			{
				V_ucDataLenIn = EventTable2_RelateOAD14_E1[j].DataLen;
				memset(V_DataTemp, 0x00, V_ucDataLenIn);
				PF_CopyDataBytes_698(&V_DataTemp[0], &P_DataBuf[V_Dataoff], V_ucDataLenIn);
				V_Dataoff += V_ucDataLenIn;
			}
      }
      if(j == EventTable2_RelateOAD14_E1_Len)
      {
        V_ucRetrun = C_OK;
      }

    }
    else if( ( V_ulDI & 0xFFFFFFF0 ) == ( CDe_Clear_NoteF_1 & 0xFFFFFFF0 ) )
    {
      for( j = 0; j < EventTable2_RelateOAD14_F1_Len; j++ )
      {
          V_ulReadOADBuf[1] =  EventTable2_RelateOAD14_F1[j].RelateOAD_645;
          if(V_ulReadOADBuf[1] == CRelayOpen_OpeCode_1)
          {
              SF_Event_Relay_JudgeAll00(V_ulReadOADBuf[0],&V_ucJudgeAll00);
              V_ucDataLenIn = CLRelayOpen_OpeCode_1;
              if(V_ucJudgeAll00 == C_ALL00_Flag)
              {
                memset(V_DataTemp, 0x00, V_ucDataLenIn);
              }
              else
              {
                memset(V_DataTemp, 0xFF, V_ucDataLenIn);
              }
              PF_CopyDataBytes_698(&V_DataTemp[0], &P_DataBuf[V_Dataoff], V_ucDataLenIn);
             V_Dataoff += V_ucDataLenIn;
             continue;
          }

			/*��1�����ݶ��¼���¼�ӿں���*/
			V_usDataLen = C_Comm_Data_MaxLen - CLen_DI;
			if( ( V_ulReadOADBuf[0] & 0x000000FF ) == 0x00000001 )
			{
				V_ucRetrun = Inf_ReadEventLast_H(V_ulReadOADBuf, V_DataTemp, &V_usDataLen, V_timeFlash, &V_ucHappening_Flag);
			}
			else
			{
                V_ucRetrun = InF_ReadEventData(V_ulReadOADBuf, &V_ucDataBuff, V_DataTemp, &V_ucDataBuff, &V_usDataLen, V_timeFlash);
			}

            if( ( V_ucRetrun == C_OK ) && ( SF_JudgeAllAA( V_DataTemp, V_usDataLen ) != C_OK )
			 && ( V_DataTemp[0] != 0xBB ) && ( V_usDataLen != 0x01 ) )			/*���������¼�в��漰�����ܣ���˲����޸�*/
			{
				if(V_ulReadOADBuf[1] == CEventHPTime)
                {
                  V_usDataLen -= 1;
                }
				PF_CopyDataBytes_698(V_DataTemp, &P_DataBuf[V_Dataoff], V_usDataLen);
				V_Dataoff += V_usDataLen;

			}
			else
			{
				V_ucDataLenIn = EventTable2_RelateOAD14_F1[j].DataLen;
				memset(V_DataTemp, 0x00, V_ucDataLenIn);
				PF_CopyDataBytes_698(&V_DataTemp[0], &P_DataBuf[V_Dataoff], V_ucDataLenIn);
				V_Dataoff += V_ucDataLenIn;
			}
        }
      if(j == EventTable2_RelateOAD14_F1_Len)
      {
        V_ucRetrun = C_OK;
      }
    }
    else
    {
      V_ucRetrun = C_IDError;
    }
    if((*P_DataLength) >= V_Dataoff)
    {
      *P_DataLength = V_Dataoff;
    }
    else /*�����֡*/
    {
      V_ucRetrun = C_DataLenError;
    }
    return V_ucRetrun;
#endif
    return C_OK;
}
/*******************************************************************************
����ԭ�ͣ�void SF_ChangeOADToDI_Pro(ulong32 V_ulOAD,ulong32 *V_ulDI)
��������������¼���¼��698OAD���ݱ�ʶת��Ϊ645���ݱ�ʶ
���������V_ulOAD 698���ݱ�ʶ��
���������V_ulDI 645���ݱ�ʶ
���ز�����
����λ�ã�
��    ע���ڱ��ת����δ���ҵ��Ļ�ȫFF���¼����������ת�����ֽڻ�FF,���ڿ�������
*******************************************************************************/
void SF_ChangeOADToDI_Pro(ulong32 V_ulOAD, ulong32 *V_ulDI)
{
	uchar8 V_ucDataBuff[4], i;
	PF_Ulong32ToBuffer4(V_ucDataBuff, &V_ulOAD, 4);
	switch(V_ucDataBuff[3])
	{
		case C_ParameterOIA40:
			for( i = 0; i < ParaChange_OADToDI_Table40_Len; i++ )
			{
				if(V_ulOAD == ParaChange_OADToDI_Table40[i].OAD)
				{
					*V_ulDI = ParaChange_OADToDI_Table40[i].DI;
					return;
				}
			}
			break;
		case C_ParameterOIA41:
			for( i = 0; i < ParaChange_OADToDI_Table41_Len; i++ )
			{
				if(V_ulOAD == ParaChange_OADToDI_Table41[i].OAD)
				{
					*V_ulDI = ParaChange_OADToDI_Table41[i].DI;
					return;
				}
			}
			break;
		case C_ParameterOIA43:
			if(V_ulOAD == CProd_Date)
			{
				*V_ulDI = CProd_Date_645;
				return;
			}
			break;
		case C_EventRecordOIA:
			for( i = 0; i < ParaChange_OADToDI_Table30_Len; i++ )
			{
				if(V_ulOAD == ParaChange_OADToDI_Table30[i].OAD)
				{
					*V_ulDI = ParaChange_OADToDI_Table30[i].DI;
					return;
				}
			}
			break;
		default:
			break;
	}
	*V_ulDI = 0xFFFFFFFF;
	return;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_ReadCurrEventFF_645(ulong32 DI,uchar8 *P_DataBuf,uchar8 *P_DataLength)
�������������¼������ݴ���
���������645���ݱ�ʶ��DI
���������P_DataBuf���ݴ��ͨ���շ����棬P_DataLength���ݳ��ȵ�ַ
���ز����� ���ػ�ȡ�����Ƿ�C_OK(����Ҫ��֡)����C_DataLenError����Ҫ��֡����C_Error��OAD����ȷ��
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_ReadCurrEventFF_645(ulong32 DI, uchar8 *P_DataBuf, uchar8 *P_DataLength)
{
	uchar8 V_Line;
	uchar8 V_ucBuffer[4];
	ulong32 V_ulReadOADBuf[3];
	uchar8 V_ucRetrun = C_Error;
    ushort16 V_ucDataLen;

  	V_ucDataLen =  C_Comm_Data_MaxLen - CLen_DI;
	PF_Ulong32ToBuffer4(V_ucBuffer, &DI, 4);
	for( V_Line = 0; V_Line < EventTable1_OADChange698_Len; V_Line++ )
	{
        if( ( EventTable1_OADChange698[V_Line].DI & 0xFFFF0000 ) == ( DI & 0xFFFF0000 ) )
        {
			V_ucBuffer[1] = EventTable1_OADChange698[V_Line].Nature;
			V_ucBuffer[2] = EventTable1_OADChange698[V_Line].OIB;
			V_ucBuffer[3] = 0x30; /*Ŀǰ֧�ֵ��¼����Ϊ0x30*/
			PF_Buffer4ToUlong32(V_ucBuffer, V_ulReadOADBuf, 4);
			break;
        }
    }
	if(V_Line == EventTable1_OADChange698_Len)
	{
		return V_ucRetrun;
	}
	V_ucRetrun = SF_Event_SingleReadFF(V_ulReadOADBuf, V_Line, P_DataBuf, &V_ucDataLen);

	if( (*P_DataLength) >= V_ucDataLen )
	{
		*P_DataLength = V_ucDataLen;
		V_ucRetrun = C_OK;
	}
	else /*�����֡*/
	{
		V_ucRetrun = C_DataLenError;
	}
    return V_ucRetrun;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_GetAPDU_EventRead_645(Str_Comm_645 *pV_645Frame,uchar8 *P_DataBuf,ushort16 *P_DataLength)
�������������¼����ݴ���
���������	645���ݱ�ʶ��
������������ݴ��ͨ���շ����棬���ݳ���
���ز��������ػ�ȡ�����Ƿ�ɹ�
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_GetAPDU_EventRead_645(Str_Comm_645 *pV_645Frame, uchar8 *P_DataBuf, ushort16 *P_DataLength)
{
	uchar8 V_Line, i, j;
	uchar8 V_ucBuffer[4];
	ulong32 V_ulReadOADBuf[3];
	uchar8 V_ucRetrun = C_Error;
    ushort16 V_ucDataLen;
    ulong32 V_ulDI;

  	V_ucDataLen =  C_Comm_Data_MaxLen - CLen_DI;
	PF_Ulong32ToBuffer4(V_ucBuffer, &pV_645Frame->DI, 4);
	for( V_Line = 0; V_Line < EventTable1_OADChange698_Len; V_Line++ )
	{
        if( ( pV_645Frame->DI & 0xFFFF0000 ) == 0x03300000 )
        {
            if( ( EventTable1_OADChange698[V_Line].DI & 0xFFFFFF00 ) == ( pV_645Frame->DI & 0xFFFFFF00 ) )
            {
                V_ucBuffer[1] = EventTable1_OADChange698[V_Line].Nature;
                V_ucBuffer[2] = EventTable1_OADChange698[V_Line].OIB;
                V_ucBuffer[3] = 0x30; 		/*Ŀǰ֧�ֵ��¼����Ϊ0x30*/
                PF_Buffer4ToUlong32(V_ucBuffer, V_ulReadOADBuf, 4);
                break;
            }
        }
        else
        {
            if( ( pV_645Frame->DI & 0xFFFF0000 ) == CTrend_Rev_Degree )
            {
                if( ( EventTable1_OADChange698[V_Line].DI & 0xFFFF0000 ) == ( CPowerT_Rev_Degree & 0xFFFF0000 ) )
                {
                    V_ucBuffer[1] = EventTable1_OADChange698[V_Line].Nature;
                    V_ucBuffer[2] = EventTable1_OADChange698[V_Line].OIB;
                    V_ucBuffer[3] = 0x30; 	/*Ŀǰ֧�ֵ��¼����Ϊ0x30*/
                    PF_Buffer4ToUlong32(V_ucBuffer, V_ulReadOADBuf, 4);
                    break;
                }
            }
            else if( ( EventTable1_OADChange698[V_Line].DI & 0xFFFF0000 ) == ( pV_645Frame->DI & 0xFFFF0000 ) )
            {
                V_ucBuffer[1] = EventTable1_OADChange698[V_Line].Nature;
                V_ucBuffer[2] = EventTable1_OADChange698[V_Line].OIB;
                V_ucBuffer[3] = 0x30; 		/*Ŀǰ֧�ֵ��¼����Ϊ0x30*/
                PF_Buffer4ToUlong32(V_ucBuffer, V_ulReadOADBuf, 4);
                break;
            }
        }
	}
	if(V_Line == EventTable1_OADChange698_Len)
	{
		return V_ucRetrun;
	}
	V_ulDI = pV_645Frame->DI & 0xFFFFFF00;
	for( j = 0; j < C_EventRead_NeedTol_Len; j++ )
	{
		if(V_ulDI == C_EventRead_NeedTol[j])
		{
			break;
		}
	}
    if( ( pV_645Frame->Data[C_O_DI1] == 0xFF ) || ( j < C_EventRead_NeedTol_Len ) )
	{
		V_ucRetrun = SF_Event_SingleReadFF(V_ulReadOADBuf, V_Line, P_DataBuf, &V_ucDataLen);
        if( ( ( pV_645Frame->Data[C_O_DI3] == 0x1D ) || ( pV_645Frame->Data[C_O_DI3] == 0x1E ) ) /*����բ��¼����Ϊ0ʱ�������ߴ���Ϊ0*/
         || ( ( ( V_ulDI & 0xFFFFFF00 ) == 0x03300000 ) && ( pV_645Frame->Data[C_O_DI1] >0x00 ) && ( pV_645Frame->Data[C_O_DI1] < 0x05 ) ) )   /*������*/
        {
          /*����ʱ��ȫ0�������ߴ��룬��0*/
			for( i = 0; i < ( CLEventHPTime - 1 ); i++ )	/*645����ʱ��6�ֽ�*/
			{
				if( *(P_DataBuf + i) != 0 )
				{
					break;
				}
			}
			if( i == ( CLEventHPTime - 1 ) )
			{
				memset(P_DataBuf + ( CLEventHPTime - 1), 0x00, 4);
			}
        }
	}
	else
	{
		V_ucRetrun = SF_Event_SingleRead(pV_645Frame, V_ulReadOADBuf, V_Line, P_DataBuf, &V_ucDataLen);
	}
	*P_DataLength = V_ucDataLen;
	return V_ucRetrun;
}
/*******************************************************************************
����ԭ�ͣ�void SF_Event_SpecificDataLenCal(ulong32 V_ulROAD, uchar8 *V_ucDataLen)
���������������¼���Ԫ�����׼�¼���Ԫ��ͬ���ֵ����ݳ��ȼ���
���������V_ulROAD���¼���¼��ROAD
���������*V_ucDataLen���������ݵĳ���
���ز�������
����λ�ã��ú�����Inf_ReadEventLast_N��Inf_ReadEventLast_H�ӿں�������
��    ע����׼�¼���Ԫ���ݳ��ȷ���0
          �Ǳ�׼�¼���ԪΪ����ĳ���
*******************************************************************************/
void SF_Event_SpecificDataLenCal(ulong32 V_ulROAD, uchar8 *V_ucSpecicalDataLen)
{
    uchar8 V_uci, V_ucj;
    uchar8 V_ucOAD[C_DataCodeLen] = {0};
    uchar8 V_ucDataLen = 0;
    uchar8 V_ucSpecificNum;
    Str_DI0_DataType_PaTable *ptr_DI0_DataType_PaTable = NULL;

    PF_Ulong32ToBuffer4(V_ucOAD, &V_ulROAD, C_DataCodeLen);

    for( V_uci = 0; V_uci < C_Event_SpecificDataLen; V_uci++ )
    {
        if(V_ucOAD[C_O_DI2] == Event_SpecificData[V_uci].OIB)
        {
            ptr_DI0_DataType_PaTable = (Str_DI0_DataType_PaTable *)Event_SpecificData[V_uci].SpecificDataTableAddr;
            V_ucSpecificNum = Event_SpecificData[V_uci].TableLenth;
            break;
        }
    }
    if(V_uci < C_Event_SpecificDataLen)
    {
        for( V_ucj = 0; V_ucj < V_ucSpecificNum; V_ucj++)
        {
            V_ucDataLen += ptr_DI0_DataType_PaTable[V_ucj].DataLen_645;
        }

        /*����¼��洢1�ֽ�����+40�ֽ�OAD*/
        if(Event_SpecificData[V_uci].OIB == CProgram_OIB)
        {
            V_ucDataLen += C_TypeLen;
            V_ucDataLen += ( (C_DataCodeLen + C_TypeLen) * (CProgOADNum - 1) );	/*�����Ѿ�����1����һ��10��*/
        }
        else if(Event_SpecificData[V_uci].OIB == CProgPT_OIB)
        {
            V_ucDataLen += ( CLSec_TZone_Data - 3 );  							/*�����Ѿ�����1����һ��14��ÿ��3�ֽ�*/
        }   /*else�����*/
    }
    else
    {
        ;
    }

    *V_ucSpecicalDataLen = V_ucDataLen;
}
/*******************************************************************************
����ԭ�ͣ�void SF_Event_SpecificDataLenCal(ulong32 V_ulROAD, uchar8 *V_ucDataLen)
���������������¼���Ԫ�����׼�¼���Ԫ��ͬ���ֵ����ݳ��ȼ���
���������V_ulROAD���¼���¼��ROAD
���������*V_ucDataLen���������ݵĳ���
���ز�������
����λ�ã��ú�����Inf_ReadEventLast_N��Inf_ReadEventLast_H�ӿں�������
��    ע����׼�¼���Ԫ���ݳ��ȷ���0
          �Ǳ�׼�¼���ԪΪ����ĳ���
*******************************************************************************/
uchar8 SF_GetSpecialEventContent( ulong32 SpecialOAD, ushort16 *p_DataLenMax, ushort16 *p_DataOff, ushort16 *p_DataOff645, uchar8 *p_DataTemp, uchar8 *p_DataBuf)
{
	uchar8 i, j, m, t, k, V_ucLen;
	uchar8 V_ucOverAPDUFlay = C_IDError;
	Str_DI0_DataType_PaTable *p_TableAddr;
	Str_Event_SingleSpecificData *str_EventSpecialOAD;
	ulong32 V_ulProgOAD[CProgOADNum];	
	
	for( i = 0; i < C_Event_SpecificDataLen; i++ )       	/*�����������ݵ��¼���¼����*/
	{
		str_EventSpecialOAD = (Str_Event_SingleSpecificData *)Event_SpecificData[i].SpecificOADTableAddr;
		for(j = 0; j < Event_SpecificData[i].OADTableLenth; j++)
		{
			if( SpecialOAD == ( str_EventSpecialOAD[j].SpecialOAD ) )
			{
				V_ucOverAPDUFlay = C_OK;
				break;
			}			
		}
		if(V_ucOverAPDUFlay == C_OK)
		{
			break;
		}
	}
	if(V_ucOverAPDUFlay == C_OK)
	{
		p_TableAddr = (Str_DI0_DataType_PaTable*)Event_SpecificData[i].SpecificDataTableAddr;
		for( m = str_EventSpecialOAD[j].LineNo; m < Event_SpecificData[i].TableLenth; m++ )
		{
			if(*p_DataLenMax == 0)
			{
				V_ucOverAPDUFlay = 0x68;
			}

			(*p_DataLenMax)--;
			p_DataBuf[*p_DataOff] = p_TableAddr[m].DataType;

			if(p_TableAddr[m].DataLen_698 != 0)
			{
				if(*p_DataLenMax < p_TableAddr[m].DataLen_698)
				{
					V_ucOverAPDUFlay = 0x68;
					return V_ucOverAPDUFlay;
				}
				(*p_DataLenMax) -= p_TableAddr[m].DataLen_698;

				V_ucLen = SF_DataExchangeTo698_BasicData(&p_DataBuf[*p_DataOff], &p_DataTemp[*p_DataOff645], p_TableAddr[m].DataLen_698, p_TableAddr[m].DataLen_645);

				if ( ( C_octet_string == p_DataBuf[*p_DataOff] )
				  || ( C_visible_string == p_DataBuf[*p_DataOff] ) )
				{
					if((*p_DataLenMax) == 0)
					{
						V_ucOverAPDUFlay = 0x68;
						return V_ucOverAPDUFlay;
					}
					(*p_DataLenMax)--;
					(*p_DataOff)++;
					p_DataBuf[*p_DataOff] = p_TableAddr[m].DataLen_698;
				}
				*p_DataOff += V_ucLen;
				*p_DataOff645 += p_TableAddr[m].DataLen_645;
			}

			if(*p_DataLenMax == 0)
			{
				V_ucOverAPDUFlay = 0x68;
				return V_ucOverAPDUFlay;
			}
			(*p_DataLenMax)--;
			(*p_DataOff)++;
			if( ( SpecialOAD != CRWTimeTable_ForwardData ) 				/*�����һ�����ݲ���Ҫ���룬ֱ���˳�*/
			 && ( SpecialOAD != CRWHoliday_ForwardData )
			 && ( SpecialOAD != CEventClear_OADList ) )					/*����ǽڼ��ձ�̻���ʱ�α��̻��ߵ�����������������˳�Ҫ��������*/	
			{
				break;
			}
		}
		if ( ( Event_SpecificData[i].OIB == CPos_De_Over_OIB )
		  || ( Event_SpecificData[i].OIB == CRe_De_Over_OIB )
		  || ( Event_SpecificData[i].OIB == CRe_ReDe_Over_OIB ) )		/*���������¼���¼��Ԫ*/
		{
			if(SpecialOAD == C_OverDemandRenew_HapTime)				/*����ǳ����ڼ����������ʱ�䣬����0*/
			{
				p_DataBuf[*p_DataOff - 1] = 0x00;				
			}
		}
		else if(Event_SpecificData[i].OIB == CProgram_OIB)					/*��̼�¼*/
		{
			for( k = 0; k < CProgOADNum; k++ )
			{
				PF_Buffer4ToUlong32(&p_DataTemp[*p_DataOff645 + k * CLProgTypeOADGather + 1], &V_ulProgOAD[k], 4);
				if(V_ulProgOAD[k] == 0xFFFFFFFF)
				{
					break;
				}
			}
			if(k > 0)
			{
				p_DataBuf[*p_DataOff] = k;									/*��ֵ�������*/
				(*p_DataOff)++;
				for( t = 0; t < k; t++ )
				{
					if( (*p_DataLenMax) < ( CL_OAD + 1 ) )
						{
							V_ucOverAPDUFlay = 0x68;
							return V_ucOverAPDUFlay;
						}
					(*p_DataLenMax) -= ( CL_OAD + 1);
						p_DataBuf[(*p_DataOff)] = p_DataTemp[*p_DataOff645];
						*p_DataOff645 += 1; 				/*1�ֽ�����*/
					SF_DataExchangeTo698_BasicData(&p_DataBuf[(*p_DataOff)], &p_DataTemp[*p_DataOff645], CL_OAD, CL_OAD);
					*p_DataOff += CL_OAD;
					*p_DataOff645 += CL_OAD;
						(*p_DataOff)++;
				}
			}
			*p_DataOff645 += ( ( CProgOADNum - k ) * CLProgTypeOADGather );
		}
		if(SpecialOAD == CRWTimeTable_ForwardData)					/*ʱ�α���*/
		{
			*p_DataOff645 -= 3;
			*p_DataOff -= 8;
			for( t = 0; t < p_TableAddr[2].DataType; t++ )
			{
				for( m = 3; m < Event_SpecificData[i].TableLenth; m++ )
				{
					if( (*p_DataLenMax) < ( p_TableAddr[m].DataLen_698 + 1 ) )
					{
						V_ucOverAPDUFlay = 0x68;
						return V_ucOverAPDUFlay;
					}
					*p_DataLenMax -= (p_TableAddr[m].DataLen_698 + 1);
					p_DataBuf[*p_DataOff] = p_TableAddr[m].DataType;
					SF_DataExchangeTo698_BasicData(&p_DataBuf[*p_DataOff], &p_DataTemp[*p_DataOff645], p_TableAddr[m].DataLen_698, p_TableAddr[m].DataLen_645);
					*p_DataOff += p_TableAddr[m].DataLen_698;
					*p_DataOff645 += p_TableAddr[m].DataLen_645;
					(*p_DataOff)++;
				}
			}
		}
	}
	return V_ucOverAPDUFlay;	
}
/************************************************************************************************************************
����ԭ��:  uchar8 SF_GetAPDU_EventRead(RdOI_Para_T *V_OAD, uchar8 *P_DataBuf, ushort16 *P_DataOff, uchar8 NextFrameFlage)
��������: ���¼����ݴ���
�������: V_OAD��ת�����645���ݱ�ʶ�룬���ݱ�ʶ���������ȡ���ݴ��buffer
�������: ��������ݴ��ͨ���շ�����
���ز���: ���ذ�ȫȨ���Ƿ�����Ҫ��C_OK��ʾ����Ȩ��Ҫ��
����λ��:
��    ע:
****************************************************************************************************************************/
uchar8 SF_GetAPDU_EventRead(RdOI_Para_T *V_OAD, uchar8 *P_DataBuf, ushort16 *P_DataOff, uchar8 NextFrameFlage)
{
	uchar8 V_ucRetrun = C_OK, V_usObject;
	ulong32 V_ReadOAD;
	ushort16 V_usDataLen, i, j, k, m, n, V_DataOff645, V_DataOff, V_RelatedOADNum, V_DataLenMax, V_DataOff645Temp = 0, V_DataOffTemp;
	ulong32	V_ulReadOADBuf[C_MAXRelatedOAD_Event];
	uchar8   V_DataTemp[1024], V_usReadRecordNum = 0;
    ulong32 V_ulProgOAD[CProgOADNum];
    uchar8 V_ucFixedOADNum;
    uchar8 V_ucLen, t;
    uchar8 V_ucOverAPDUFlay = 0;
    uchar8 V_645Len, V_us698Len;
    uchar8 V_I, V_ucPerDataLen, V_ucTemp;
	ulong32 V_ulReadOADBuf_All[C_MAXRelatedOAD_Event];
	ushort16   V_ucSuppleInformationTemp[C_MAXRelatedOAD_Event * 3] = {0};		/*һ����־��ı������Ҫ2���ֽڣ��ٶ���һ���ֽ�����*/
	ulong32  SubSeconds;
	uchar8   V_ucRSTTemp[20] = {0};
	Str_Event_OIB1 Str_EventInfo;
	Str_DI0_DataType_PaTable *p_TableAddr;
    Struct_FrozenConvert_Type Str_Encode;
	Str_Read_T V_EventRead;
	Str_SuppInfo V_ucSupplementaryInformation;

	V_ucSupplementaryInformation.pV_usEncode = &V_ucSuppleInformationTemp[0];
	V_EventRead.pV_ucRST = &V_ucRSTTemp[0];				/*����¼�ķ�����0/1/2/9*/
	V_usObject = (uchar8)(V_OAD->RdOI.OAD >> 16);	/*ȡ�����ʶ*/

	for( i = 0; i < C_Event_OIBTableLen; i++)
	{
		if(V_usObject == Event_OIBTable[i].OIB)
		{
			break;
		}
	}

	Str_EventInfo = Event_OIBTable[i];	    			/*��ȡ��ز���*/

	V_DataLenMax = *P_DataOff;		        			/*�����Զ�ȡ����*/

/***************************��ѡ�񷽷�����*****************************/
	switch( V_OAD->Rd_RecordSelect[0] )	   			 	/*��ѡȡ����*/
	{
		case 9:
		{
			V_usReadRecordNum = 1;
			V_ReadOAD = (V_OAD->RdOI.OAD & 0xFFFFFF00) | V_OAD->Rd_RecordSelect[1];
		}break;
		case 1:
		case 2:
		{
			V_ReadOAD = (V_OAD->RdOI.OAD & 0xFFFFFF00);
		}break;
		case 0:
		{
			V_usReadRecordNum = 10;
			V_ReadOAD = (V_OAD->RdOI.OAD & 0xFFFFFF00) | 1;
		}break;
		default:
			V_ucRetrun = C_OtherErr_DAR;				/*����ѡ�񷽷�Ӧ����������*/
			return V_ucRetrun;
			break;
	}
	V_ucRSTTemp[0] = V_OAD->Rd_RecordSelect[0];
	if( NextFrameFlage != C_GETNext_Request )
	{
		switch(V_OAD->Rd_RecordSelect[0])				/*��ѡȡ����*/
		{
			case 1:
			case 2:
			{	/************ȡѡ��OAD************/

				/*ȥ���ж�OAD�Ĵ��룬Ų�����ݲ���*/
                if(V_OAD->Rd_RecordSelect[5] != 0x1C)
                {
                    V_ucRetrun = C_TypeErr_DAR;
					return V_ucRetrun;
                }

				/*******************������ѡ�񷽷���ʱ��ת��Ϊ645******************/
				SF_DataExchangeTo645_BasicData(&V_OAD->Rd_RecordSelect[5], &V_ucRSTTemp[1 + CL_OAD], CL_date_time_s, (uchar8 *)&j);
				V_usReadRecordNum = 1;	    			/*����ʱ���ȡһ�������¼(ceshi)*/
				if(V_OAD->Rd_RecordSelect[0] == 2)
				{
	                if(V_OAD->Rd_RecordSelect[13] != 0x1C)
	                {
	                    V_ucRetrun = C_TypeErr_DAR;
						return V_ucRetrun;
	                }
					SF_DataExchangeTo645_BasicData(&V_OAD->Rd_RecordSelect[13], &V_ucRSTTemp[1 + CL_OAD + CL_date_time_s], CL_date_time_s, (uchar8 *)&j);
					V_usReadRecordNum = 0;
					if(PF_TimeSub_Second_698(&V_ucRSTTemp[1 + CL_OAD + CL_date_time_s], &V_ucRSTTemp[1 + CL_OAD], &SubSeconds) != C_GreaterThan)
					{
						V_ucRetrun = C_OtherErr_DAR;
						return V_ucRetrun;
						break;
					}
				}
				else									/*����1��������ʱ��һ��*/
				{
					PF_CopyDataBytes(&V_ucRSTTemp[1 + CL_OAD], &V_ucRSTTemp[1 + CL_OAD + CL_date_time_s], CL_date_time_s);
				}
			}break;
			case 9:
				V_ucRSTTemp[1] = V_OAD->Rd_RecordSelect[1];
				break;
		}
	}
/********************��ȡ��¼������ЧOAD*********************/
	V_I = C_EventMAXRelatedOAD + 20;
	SF_Get_AssociationList(V_ReadOAD, &V_ulReadOADBuf_All[1], &V_I);
	V_ulReadOADBuf_All[0] = V_I;
/***************************��ѡ�񷽷�����*****************************/
	V_ulReadOADBuf[0] = V_ReadOAD;

	V_RelatedOADNum = V_OAD->Rd_RecordRelatedOINum;

	if(V_RelatedOADNum > C_MaxRCSDNum )
	{
		V_RelatedOADNum = C_MaxRCSDNum;
	}
	i = 0;
	V_ucFixedOADNum = 0;

	if(V_RelatedOADNum != 0)
	{
		j = 0;
		for(    ; i < V_RelatedOADNum; i++)
		{
			j++;
			V_ulReadOADBuf[j] = V_OAD->Rd_RecordRelatedOI[i];
		}
		V_ucFixedOADNum = V_RelatedOADNum;
	}
	else																			/*��ȡ���õ�OAD*/
	{
		j = 0;
		SF_EventOADRead(*V_OAD, (uchar8 *)&V_ulReadOADBuf[1], &V_DataOff, 2, &V_ucFixedOADNum);
		V_ucFixedOADNum += 6;
	}
	if(j > C_EventMAXRelatedOAD)
	{
		V_ucRetrun = C_OverStep_DAR;	    										/*��ѡ����60��Ӧ��Խ��*/
		return V_ucRetrun;
	}

	if(j < (C_MAXRelatedOAD_Event - 1))												/*û���õ���ֱ�����oxFFFFFFFF*/
	{
		for(    ; j < (C_MAXRelatedOAD_Event - 1); j++)
		{
			V_ulReadOADBuf[j + 1] = 0xFFFFFFFF;
		}
	}

	if( V_DataLenMax > ( V_ucFixedOADNum * 5 ) )
    {
        V_DataLenMax -= V_ucFixedOADNum * 5;										/*��ȥ���������б���Ҫ���ֽ���*/
    }
    else
    {
		return C_OverStep_DAR;
    }
/*************************���ýӿں�����ȡ�����¼***************************/
	V_EventRead.pV_ulROAD = V_ulReadOADBuf;											/*����¼�����OAD�б�ֵ*/
	V_EventRead.V_usROAD_Num = V_RelatedOADNum;										/*����¼�Ĺ���OAD�ĸ���*/
	V_EventRead.V_ucReadMode = C_ComMode;											/*ͨ�Ŷ�ȡ*/
	if( ( V_ucRSTTemp[0] == 1 ) || ( V_ucRSTTemp[0] == 2 ) )
	{
		if( V_ulReadOADBuf[0] == CDate_Time )
		{
			V_ulReadOADBuf[0] = CEventHPTime;											/*�����л��·���ǰʱ���OAD������ȡ������ת���¼�����ʱ���·�*/
		}
		PF_OneDataReversed(&V_OAD->Rd_RecordSelect[1], &V_EventRead.pV_ucRST[1], CL_OAD);		/*����1�ͷ���2����ֵOAD*/
	}
	V_usDataLen = 1024;
	if( InF_ReadPowerState() == C_PowerOff )										/*�͹����µ����ϱ���֡*/
	{
		V_ucRetrun = Inf_Get_PowerDownEvent_Data(C_PowerfailEventNo, V_DataTemp, &V_usDataLen);
	}
	else																			/*��1�����ݶ��¼���¼�ӿں���*/
	{
		V_ucRetrun =  InF_GetData_Record(&V_EventRead, V_DataTemp, &V_usDataLen, &V_ucSupplementaryInformation);
	}
	if( ( V_ulReadOADBuf[0] & 0x000000FF ) == 0x00000001 )
	{
		if(V_ulReadOADBuf[1] == 0xFFFFFFFF) 										/*����ѡʱ��������ȡRAM; ����ѡ�����ݲ��д���*/
		{
			InF_RD_ProgRecordReg(V_ulReadOADBuf[0], V_DataTemp);
		}
	}
/*************************���б���********************************/
	if( ( V_ucSupplementaryInformation.V_ucNxtFrame ==  C_Active_NxtFrame ) && ( V_ucRetrun == C_OK ) )	/*�к���֡����*/
	{
		V_ucRetrun = C_MaxResponseLen_ERR;
	}

	if((V_ucRetrun == C_OK) || (V_ucRetrun == C_MaxResponseLen_ERR))									/*�к���֡Ҳ��Ҫ����*/
	{
		V_DataOff645 = 0;
		V_DataOff = 3;
		V_usReadRecordNum = V_ucSupplementaryInformation.V_ucFrameNum;									/*��ֵ�������ļ�¼����*/	
		if(V_DataOff > V_DataLenMax)
		{
			V_DataLenMax -= 3;
			return C_OverStep_DAR;
		}
		P_DataBuf[V_DataOff] = V_usReadRecordNum;   													/*��ֵ����,����Ҫ�޸�*/
		V_DataOff++;
		if(V_DataOff > V_DataLenMax)
		{
			return C_OverStep_DAR;
		}
		V_DataLenMax--;

		for( k = 0; k < V_usReadRecordNum; k++)
		{
            /*���ݲ��4����ʵ��ֻ�ܱ���3�������*/
			V_DataOff645Temp = V_DataOff645;        					/*�ݴ汾����¼����ʼƫ��*/
			V_DataOffTemp = V_DataOff;              					/*�ݴ���һ���Ѿ����������ƫ��*/
			if(V_OAD->Rd_RecordRelatedOINum == 0)						/*���ȶ���ż�����ʱ����б���*/
			{
				V_RelatedOADNum = 0;
				n = ((C_MAXRelatedOAD_Event - 1) * 4);
	            SF_EventOADRead(*V_OAD, (uchar8 *)&V_ulReadOADBuf[1], &n, 2, (uchar8 *)&V_RelatedOADNum);

				if(SF_MaxLenSubAndJudge(&V_DataLenMax, C_double_long_unsigned) != C_OK)
				{
                    V_ucOverAPDUFlay = 0x68;
					goto DataOrganize;
				}

	            P_DataBuf[V_DataOff] = C_double_long_unsigned;
				V_ucLen = SF_DataExchangeTo698_BasicData(&P_DataBuf[V_DataOff], &V_DataTemp[V_DataOff645], 4, 4);
				V_DataOff += (V_ucLen + 1);
				V_DataOff645 += 4;      								/*4�ֽڶ����ۼƴ���*/

				if(SF_MaxLenSubAndJudge(&V_DataLenMax, C_date_time_s) != C_OK)
				{
                    V_ucOverAPDUFlay = 0x68;
					goto DataOrganize;
				}

				P_DataBuf[V_DataOff] = C_date_time_s;
				V_ucLen = SF_DataExchangeTo698_BasicData(&P_DataBuf[V_DataOff], &V_DataTemp[V_DataOff645], 8, 7);
				V_DataOff += (V_ucLen + 1);
				V_DataOff645 = V_DataOff645 + 7;						/*7�ֽ�ʱ��*/

				if( ( InF_JudgeNoEndTimeEvent(V_ulReadOADBuf[0]) == C_OK)
                 || ( V_DataTemp[V_DataOff645] == 0xAA ) )
				{
					if(V_DataLenMax == 0)
					{
                        V_ucOverAPDUFlay = 0x68;
						goto DataOrganize;
					}

					P_DataBuf[V_DataOff] = C_NULL;
					V_DataOff++;
					V_DataLenMax--;
				}
				else
				{
					if(SF_MaxLenSubAndJudge(&V_DataLenMax, C_date_time_s) != C_OK)
					{
                        V_ucOverAPDUFlay = 0x68;
						goto DataOrganize;
					}

					P_DataBuf[V_DataOff] = C_date_time_s;
					V_ucLen = SF_DataExchangeTo698_BasicData(&P_DataBuf[V_DataOff], &V_DataTemp[V_DataOff645], 8, 7);
					V_DataOff += (V_ucLen + 1);
				}
				V_DataOff645 += 7;
				if ( ( Str_EventInfo.TypeClass == C_Event_Class )		/*�¼���¼����Դ*/
                  || ( V_usObject == CRe_ReDe_Over_OIB ) )
				{
					if(V_usObject == 0x23)
					{
						if(V_DataLenMax == 0)
						{
                            V_ucOverAPDUFlay = 0x68;
							goto DataOrganize;
						}
						P_DataBuf[V_DataOff] = C_enum;
						V_DataOff++;
						V_DataLenMax--;
					}

					if(V_DataLenMax == 0)
					{
                        V_ucOverAPDUFlay = 0x68;
						goto DataOrganize;
					}
					P_DataBuf[V_DataOff] = V_DataTemp[V_DataOff645];
					V_DataOff++;
					V_DataOff645++;
					V_DataLenMax--;
				}
				
                P_DataBuf[V_DataOff] = V_DataTemp[V_DataOff645];		/*�¼���¼�ϱ�״̬�����ڴ��ڼ�¼��*/
                V_DataOff++;
				V_DataOff645++;
				V_DataLenMax--;
				
				for( i = 0; i < C_Event_SpecificDataLen; i++ )       	/*�����������ݵ��¼���¼����*/
				{
					if(V_usObject == Event_SpecificData[i].OIB)
					{
						break;
					}
				}

				if(i < C_Event_SpecificDataLen)
				{
					p_TableAddr = (Str_DI0_DataType_PaTable*)Event_SpecificData[i].SpecificDataTableAddr;
					for( m = 0; m < Event_SpecificData[i].TableLenth; m++ )
					{
						if(V_DataLenMax == 0)
						{
                            V_ucOverAPDUFlay = 0x68;
							goto DataOrganize;
						}

                        if( ( V_usObject == CProgram_OIB ) && ( m == 2 ) )
                        {
                            break;
                        }

						V_DataLenMax--;
						P_DataBuf[V_DataOff] = p_TableAddr[m].DataType;

						if(p_TableAddr[m].DataLen_698 != 0)
						{
							if(V_DataLenMax < p_TableAddr[m].DataLen_698)
							{
                                V_ucOverAPDUFlay = 0x68;
								goto DataOrganize;
							}
							V_DataLenMax -= p_TableAddr[m].DataLen_698;

							if( ( V_usObject == CAbnorC_OIB ) && ( m == 3 ) )	/* �쳣�忨�¼��еĴ���״̬�֣�����תΪDEC�����⴦�� */
							{
								P_DataBuf[V_DataOff + 2] = V_DataTemp[V_DataOff645];
								P_DataBuf[V_DataOff + 1] = V_DataTemp[V_DataOff645 + 1];
								V_ucLen = 0x02;
							}
							else
							{
								V_ucLen = SF_DataExchangeTo698_BasicData(&P_DataBuf[V_DataOff], &V_DataTemp[V_DataOff645], p_TableAddr[m].DataLen_698, p_TableAddr[m].DataLen_645);
							}

							if ( ( C_octet_string == P_DataBuf[V_DataOff] )
							  || ( C_visible_string == P_DataBuf[V_DataOff] ) )
							{
								if(V_DataLenMax == 0)
								{
                                    V_ucOverAPDUFlay = 0x68;
									goto DataOrganize;
								}
								V_DataLenMax--;
								V_DataOff++;
								P_DataBuf[V_DataOff] = p_TableAddr[m].DataLen_698;
							}
							V_DataOff += V_ucLen;
							V_DataOff645 += p_TableAddr[m].DataLen_645;
						}

						if(V_DataLenMax == 0)
						{
                            V_ucOverAPDUFlay = 0x68;
							goto DataOrganize;
						}
						V_DataLenMax--;
						V_DataOff++;
					}
					if ( ( V_usObject == CPos_De_Over_OIB )
					  || ( V_usObject == CRe_De_Over_OIB )
					  || ( V_usObject == CRe_ReDe_Over_OIB ) )		/*���������¼���¼��Ԫ*/
					{
						P_DataBuf[V_DataOff - 1] = 0x00;			/*�����ڼ����������ʱ������0*/
					}

					if(V_usObject == CProgram_OIB)					/*��̼�¼*/
					{
						for( j = 0; j < CProgOADNum; j++ )
						{
							PF_Buffer4ToUlong32(&V_DataTemp[V_DataOff645 + j * CLProgTypeOADGather + 1], &V_ulProgOAD[j], 4);
							if(V_ulProgOAD[j] == 0xFFFFFFFF)
							{
								break;
							}
						}
						if(j > 0)
						{
							P_DataBuf[V_DataOff - 1] = j;			/*��ֵ�������*/
							for( t = 0; t < j; t++ )
							{
								for( m = 2; m < Event_SpecificData[i].TableLenth; m++ )
								{
									if( V_DataLenMax < ( p_TableAddr[m].DataLen_698 + 1 ) )
									{
                                        V_ucOverAPDUFlay = 0x68;
										goto DataOrganize;
									}
									V_DataLenMax -= (p_TableAddr[m].DataLen_698 + 1);
									P_DataBuf[V_DataOff] = V_DataTemp[V_DataOff645];
                                    V_DataOff645 += 1; 				/*1�ֽ�����*/
									SF_DataExchangeTo698_BasicData(&P_DataBuf[V_DataOff], &V_DataTemp[V_DataOff645], p_TableAddr[m].DataLen_698, p_TableAddr[m].DataLen_645);
									V_DataOff += p_TableAddr[m].DataLen_698;
									V_DataOff645 += p_TableAddr[m].DataLen_645;
									V_DataOff++;
								}
							}
						}
						V_DataOff645 += ((CProgOADNum - j) * CLProgTypeOADGather);
					}
					if(V_usObject == CProgPT_OIB)					/*ʱ�α���*/
					{
						V_DataOff645 -= 3;
						V_DataOff -= 8;
						for( t = 0; t < p_TableAddr[2].DataType; t++ )
						{
							for( m = 3; m < Event_SpecificData[i].TableLenth; m++ )
							{
								if( V_DataLenMax < ( p_TableAddr[m].DataLen_698 + 1 ) )
								{
                                    V_ucOverAPDUFlay = 0x68;
									goto DataOrganize;
								}
								V_DataLenMax -= (p_TableAddr[m].DataLen_698 + 1);
								P_DataBuf[V_DataOff] = p_TableAddr[m].DataType;
								SF_DataExchangeTo698_BasicData(&P_DataBuf[V_DataOff], &V_DataTemp[V_DataOff645], p_TableAddr[m].DataLen_698, p_TableAddr[m].DataLen_645);
								V_DataOff += p_TableAddr[m].DataLen_698;
								V_DataOff645 += p_TableAddr[m].DataLen_645;
								V_DataOff++;
							}
						}

					}
#if 0/*20����ԭ�д��룬û���ã�ȥ��*/
					if(V_usObject == CProgHol_OIB)					/*�ڼ��ձ��*/
					{
						V_DataOff645 -= 4;
						V_DataOff -= 8;
						V_DataLenMax += 8;
						if(V_DataLenMax < 8)
						{
                            V_ucOverAPDUFlay = 0x68;
							goto DataOrganize;
						}
						V_DataLenMax -= 8;
						P_DataBuf[V_DataOff] = C_date;
						SF_DataExchangeTo698_BasicData(&P_DataBuf[V_DataOff], &V_DataTemp[V_DataOff645 - 1], 5, 5);
						V_DataOff += 5;
						V_DataOff++;
						P_DataBuf[V_DataOff] = C_unsigned;
						V_DataOff++;
						P_DataBuf[V_DataOff] = V_DataTemp[V_DataOff645 - 1];
						V_DataOff645 += 4;
						V_DataOff++;
					}
#endif
				}
			}
			for( i = 0; i < V_RelatedOADNum; i++ )
			{
				for( j = 0; j < Str_FrozenConvert_Table_Len; j++ )
				{
					if(V_OAD->Rd_RecordRelatedOINum == 0)		/*��ѡ����Ϊ0����ʾ��ȡ������*/
					{
						if((V_ulReadOADBuf[i + 1] & 0xFFFF1FFF) == Str_FrozenConvert_Table[j].V_ulOAD)
						{
							Str_Encode = Str_FrozenConvert_Table[j];
                            SF_FrozenDataFF_NextNum(&Str_Encode, j);
							break;
						}
					}
					else
					{
						if((V_OAD->Rd_RecordRelatedOI[i] & 0xFFFF1FFF) == Str_FrozenConvert_Table[j].V_ulOAD)
						{
							Str_Encode = Str_FrozenConvert_Table[j];
                            SF_FrozenDataFF_NextNum(&Str_Encode, j);
							break;
						}
					}
				}
				if( j >= Str_FrozenConvert_Table_Len )
				{
					if(V_OAD->Rd_RecordRelatedOI[i] == CEventHPTime)				/*�¼���¼����ʱ��*/
					{
						if(V_DataLenMax < 8)
						{
                            V_ucOverAPDUFlay = 0x68;
							goto DataOrganize;
						}
						V_DataLenMax -= 8;
						P_DataBuf[V_DataOff] = C_date_time_s;
						V_ucLen = SF_DataExchangeTo698_BasicData(&P_DataBuf[V_DataOff], &V_DataTemp[V_DataOff645], 8, CL_date_time_s);
						V_DataOff645 += CL_date_time_s;
						V_DataOff += (V_ucLen + 1);
					}
					else if(V_OAD->Rd_RecordRelatedOI[i] == CEventNum)				/*�¼���¼���*/
					{
						if(V_DataLenMax < 5)
						{
                            V_ucOverAPDUFlay = 0x68;
							goto DataOrganize;
						}
						V_DataLenMax -= 5;
						P_DataBuf[V_DataOff] = C_double_long_unsigned;
						V_ucLen = SF_DataExchangeTo698_BasicData(&P_DataBuf[V_DataOff], &V_DataTemp[V_DataOff645], 4, 4);
						V_DataOff += (V_ucLen + 1);
						V_DataOff645 += 4;
					}
					else if(V_OAD->Rd_RecordRelatedOI[i] == CEventEndTime)			/*�¼�����ʱ��*/
					{
						if ( ( InF_JudgeNoEndTimeEvent(V_ulReadOADBuf[0]) == C_OK )
                          || ( V_DataTemp[V_DataOff645] == 0xAA ) )
						{
							if(V_DataLenMax < 1)
							{
                                V_ucOverAPDUFlay = 0x68;
								goto DataOrganize;
							}
							V_DataLenMax -= 1;
							P_DataBuf[V_DataOff] = C_NULL;
							V_DataOff++;
						}
						else
						{
							if(V_DataLenMax < 8)
							{
                                V_ucOverAPDUFlay = 0x68;
								goto DataOrganize;
							}
							V_DataLenMax -= 8;
							P_DataBuf[V_DataOff] = C_date_time_s;
							V_ucLen = SF_DataExchangeTo698_BasicData(&P_DataBuf[V_DataOff], &V_DataTemp[V_DataOff645], 8, CL_date_time_s);
							V_DataOff += (V_ucLen + 1);
						}
						V_DataOff645 += 7;
					}
					else if(V_OAD->Rd_RecordRelatedOI[i] == CEventHPSource)
					{
						if(V_DataLenMax < 1)
						{
							V_ucOverAPDUFlay = 0x68;
							goto DataOrganize;
						}
						V_DataLenMax -= 1;
						if( (Str_EventInfo.TypeClass == C_Event_Class) || (V_usObject == 0x0B) )
						{
							if(V_usObject == 0x24)
							{
								V_DataLenMax -= 1;
								P_DataBuf[V_DataOff] = C_enum;
								V_DataOff++;
							}
							P_DataBuf[V_DataOff] = V_DataTemp[V_DataOff645];
						}
						else
						{
							P_DataBuf[V_DataOff] = C_NULL;
						}
						V_DataOff++;
						V_DataOff645++;
					}
					else if(V_OAD->Rd_RecordRelatedOI[i] == CUpdata_Status)				/*�¼���¼�ϱ�״̬�����ڴ��ڼ�¼��*/
					{
						P_DataBuf[V_DataOff] = V_DataTemp[V_DataOff645];		
						V_DataOff++;
						V_DataOff645++;
						V_DataLenMax--;
					}
#if 0
                    else if( ( V_OAD->Rd_RecordRelatedOI[i] == CProgOADGather ) 			/*��̼�¼�¼���Ԫ*/
						  || ( V_OAD->Rd_RecordRelatedOI[i] == CEventClear_OADList ) )		/*�¼���¼�����¼���Ԫ*/
                    {
						for( j = 0; j < CProgOADNum; j++ )
						{
							PF_Buffer4ToUlong32(&V_DataTemp[V_DataOff645 + j * CLProgTypeOADGather + 1], &V_ulProgOAD[j], C_DataCodeLen);

                            if(V_ulProgOAD[j] == 0xFFFFFFFF)
							{
								break;
							}
						}
						if( j <= CProgOADNum )
						{
                            if(V_DataLenMax < (CLProgTypeOADGather * j))
                            {
                                V_ucOverAPDUFlay = 0x68;
                                goto DataOrganize;
                            }

                            V_DataLenMax -= (CLProgTypeOADGather * j);
							P_DataBuf[V_DataOff] = C_array;  	/*��ֵ�������*/
                            V_DataOff++;
							P_DataBuf[V_DataOff] = j;       	/*��ֵ�������*/
                            V_DataOff++;
                            for( m = 0; m < j; m++ )
                            {
                                P_DataBuf[V_DataOff] = V_DataTemp[V_DataOff645];
                                V_DataOff645 += C_TypeLen;		/*1�ֽ�����*/
                                SF_DataExchangeTo698_BasicData(&P_DataBuf[V_DataOff], &V_DataTemp[V_DataOff645], C_DataCodeLen, CLProgTypeOADGather);
                                V_DataOff645 += C_DataCodeLen;
                                V_DataOff += CLProgTypeOADGather;
                            }
                            V_DataOff645 += CLProgOADGather - (CLProgTypeOADGather * j);
                        }
                    }
                    else if( V_OAD->Rd_RecordRelatedOI[i] == C_OverDemandRenew_Demand ) 			/*���������ڼ��������*/
                    {
						if(V_DataLenMax < ( CL_double_long_unsigned + 1 ) )
						{
                            V_ucOverAPDUFlay = 0x68;
							goto DataOrganize;
						}
						V_DataLenMax -= ( CL_double_long_unsigned + 1 );
						P_DataBuf[V_DataOff] = C_date_time_s;
						V_ucLen = SF_DataExchangeTo698_BasicData(&P_DataBuf[V_DataOff], &V_DataTemp[V_DataOff645], 8, CL_date_time_s);
						V_DataOff645 += CL_date_time_s;
						V_DataOff += (V_ucLen + 1);
                    }
#endif
					else
					{
						V_ucOverAPDUFlay = SF_GetSpecialEventContent( V_OAD->Rd_RecordRelatedOI[i], &V_DataLenMax, &V_DataOff, &V_DataOff645, V_DataTemp, P_DataBuf);
						if(V_ucOverAPDUFlay == 0x68)
						{
							goto DataOrganize;						
						}
						else if(V_ucOverAPDUFlay == C_IDError)
						{
							if(V_DataLenMax < 1)
							{
								V_ucOverAPDUFlay = 0x68;
								goto DataOrganize;
							}
							V_DataLenMax -= 1;
							P_DataBuf[V_DataOff] = 0;
							V_DataOff ++;

							if(V_DataTemp[V_DataOff645] == C_NotSupportAOD_DataBB)
							{
								V_DataOff645 ++;
							}
						}						
					}
					continue;
				}
				if( ( SF_JudgeAllAA(&V_DataTemp[V_DataOff645], Str_Encode.V_uc645Length) == C_OK )
					&& (SF_Get_Active_OAD(V_ulReadOADBuf[i + 1], &V_ulReadOADBuf_All[0], Str_Encode.V_uc698Type, V_ucSupplementaryInformation.V_ucLastFlag) == C_AAorBBIsDisactive) )	/*��Ч*/
				{
                    if(V_DataLenMax < 1)
                    {
                        V_ucOverAPDUFlay = 0x68;
                        goto DataOrganize;
                    }
                    V_DataLenMax -= 1;
					P_DataBuf[V_DataOff] = 0;
					V_DataOff ++;
					V_DataOff645 += Str_Encode.V_uc645Length;
					continue;
				}
				if( (V_DataTemp[V_DataOff645] == C_NotSupportAOD_DataBB)
					&& (SF_Get_Active_OAD(V_ulReadOADBuf[i + 1], &V_ulReadOADBuf_All[0], Str_Encode.V_uc698Type, V_ucSupplementaryInformation.V_ucLastFlag) == C_AAorBBIsDisactive) )	/*��Ч*/
				{
                    if(V_DataLenMax < 1)
                    {
                        V_ucOverAPDUFlay = 0x68;
                        goto DataOrganize;
                    }
                    V_DataLenMax -= 1;
					P_DataBuf[V_DataOff] = 0;
					V_DataOff ++;
					V_DataOff645 += 1;
					continue;
				}

				if((Str_Encode.V_ulOAD & 0xfff00000) == 0x21300000)		/*��ѹ�ϸ������⴦��*/
				{
					if(V_DataLenMax < 23)
					{
						V_ucOverAPDUFlay = 0x68;
						goto DataOrganize;
					}
					V_DataLenMax -= 23;
					SF_Encode_VolRates(&Str_Encode, P_DataBuf, V_DataTemp, &V_DataOff, &V_DataOff645);
				}
				else if(Str_Encode.V_ulOAD == C_RelayFa_State)			/*�̵���״̬���⴦��*/
				{
                    if(V_DataLenMax < 11)
                    {
                        V_ucOverAPDUFlay = 0x68;
                        goto DataOrganize;
                    }
                    V_DataLenMax -= 11;
					P_DataBuf[V_DataOff] = Str_Encode.V_uc698Type;
					V_DataOff++;
					P_DataBuf[V_DataOff] = Str_Encode.V_uc698NextNum;
					V_DataOff++;
					P_DataBuf[V_DataOff] = C_visible_string;
					V_DataOff++;
					P_DataBuf[V_DataOff] = CLRelayDescrip;
					V_DataOff ++;
                    memcpy(&P_DataBuf[V_DataOff], &V_DataTemp[V_DataOff645], CLRelayDescrip);
					V_DataOff += CLRelayDescrip;
					V_DataOff645 += CLRelayDescrip;
					P_DataBuf[V_DataOff] = C_enum;
					V_DataOff++;
					P_DataBuf[V_DataOff] = V_DataTemp[V_DataOff645];
					V_DataOff++;
					V_DataOff645 += 1;
					P_DataBuf[V_DataOff] = C_enum;
					V_DataOff++;
					P_DataBuf[V_DataOff] = V_DataTemp[V_DataOff645];
					V_DataOff++;
					V_DataOff645 += 1;
					P_DataBuf[V_DataOff] = C_enum;
					V_DataOff++;
					P_DataBuf[V_DataOff] = V_DataTemp[V_DataOff645];
					V_DataOff++;
					V_DataOff645 += 1;
				}
				else if(Str_Encode.V_uc698Type == C_Ladder_Table)		/*���ݱ�����*/
				{
                    if(V_DataLenMax < 83)
                    {
                        V_ucOverAPDUFlay = 0x68;
                        goto DataOrganize;
                    }
                    V_DataLenMax -= 83;
					for( j = 0; j < ProgLadder_SpecificDataLen; j++ )
					{
						P_DataBuf[V_DataOff] = ProgLadder_SpecificData[j].DataType;
						if ( ( ProgLadder_SpecificData[j].DataType == C_structure ) && ( j != 0 ) )
						{
							V_DataOff++;
							j++;
							P_DataBuf[V_DataOff] = ProgLadder_SpecificData[j].DataType;	    /*�ṹ�����*/
							V_DataOff++;
							V_I = ProgLadder_SpecificData[j].DataType;
							j++;
							for( V_I = 0; V_I < ProgLadder_SpecificData[j].DataType; V_I++ )
							{
								P_DataBuf[V_DataOff] = ProgLadder_SpecificData[j].DataType;	/*�ṹ��Ԫ������*/
								if( V_DataTemp[V_DataOff645 + V_I] == 0xFF )
								{
									V_DataOff++;
									P_DataBuf[V_DataOff] = V_DataTemp[V_DataOff645 + V_I];
									V_DataOff++;
								}
								else
								{
									V_us698Len = SF_DataExchangeTo698_BasicData(&(P_DataBuf[V_DataOff]), &V_DataTemp[V_DataOff645 + V_I], 1, 1);
									V_DataOff += (V_us698Len + 1);
								}
								j++;
							}

							V_DataOff645 += 3;
							j--;
						}
						else
						{
							if(ProgLadder_SpecificData[j].DataLen_698 == 0)
							{
								V_DataOff++;
								continue;
							}
							V_us698Len = SF_DataExchangeTo698_BasicData(&(P_DataBuf[V_DataOff]),&V_DataTemp[V_DataOff645],ProgLadder_SpecificData[j].DataLen_698,ProgLadder_SpecificData[j].DataLen_645);
							V_DataOff += (V_us698Len + 1);
							V_DataOff645 += ProgLadder_SpecificData[j].DataLen_645;
						}
					}
				}
				else if((Str_Encode.V_uc698Type == C_array) || (Str_Encode.V_uc698Type == C_structure))
				{
                    if(V_DataLenMax < 2)
                    {
                        V_ucOverAPDUFlay = 0x68;
                        goto DataOrganize;
                    }
                    V_DataLenMax -= 2;
                    if ( ( Str_Encode.V_uc698Type == Str_Encode.V_uc698NextType )
                      && ( Str_Encode.V_uc698Type == C_structure ) )
                    {
                        if(V_DataLenMax >= 2)
                        {
                            V_DataLenMax -= 2;
                        }
                        else
                        {
                            V_ucOverAPDUFlay = 0x68;
                            goto DataOrganize;
                        }
                    }
                    else
                    {
                        P_DataBuf[V_DataOff] = Str_Encode.V_uc698Type;
                        V_DataOff++;
                        P_DataBuf[V_DataOff] = Str_Encode.V_uc698NextNum;
                        V_DataOff++;
                    }

					for( j = 0; j < Str_Encode.V_uc698NextNum; j++ )
					{
						if(V_DataLenMax < 1)
						{
                            V_ucOverAPDUFlay = 0x68;
							goto DataOrganize;
						}
						V_DataLenMax -= 1;
						P_DataBuf[V_DataOff] = Str_Encode.V_uc698NextType;
						V_DataOff++;
						if(Str_Encode.V_uc698NextType == C_structure)					/*�������ֻ���������*/
						{
							if(V_DataLenMax < 14)
							{
                                V_ucOverAPDUFlay = 0x68;
								goto DataOrganize;
							}
							V_DataLenMax -= 14;
							P_DataBuf[V_DataOff] = 2;
							V_DataOff++;
							P_DataBuf[V_DataOff] = C_double_long_unsigned;
							if ( ( ( Str_Encode.V_ulOAD & 0x00F00000 ) == 0x00300000 )
							  || ( ( Str_Encode.V_ulOAD & 0x00F00000 ) == 0x00400000 ) )
							{
								P_DataBuf[V_DataOff] = C_double_long;
							}
							if(SF_JugeDemadFF(&V_DataTemp[0 + V_DataOff645], CLPos_Ac_Tol_De_0) == C_OK)
							{
								V_DataOff++;
								memset(&P_DataBuf[V_DataOff], 0xFF, 4);
								V_DataOff += 4;
								P_DataBuf[V_DataOff] = C_date_time_s;
								V_DataOff++;
								memset(&P_DataBuf[V_DataOff], 0xFF, 7);
								V_DataOff += 7;
							}
							else
							{
								V_645Len = CL_double_long;

								V_us698Len = SF_DataExchangeTo698_BasicData(&(P_DataBuf[V_DataOff]), &V_DataTemp[ 0 + V_DataOff645], CL_double_long, V_645Len);
								V_DataOff += (V_us698Len + 1);
								P_DataBuf[V_DataOff] = C_date_time_s;
								V_645Len = CL_date_time_s;
								V_us698Len = SF_DataExchangeTo698_BasicData(&(P_DataBuf[V_DataOff]),&V_DataTemp[CL_double_long + V_DataOff645], CL_date_time_s, V_645Len);
								if ( ( P_DataBuf[V_DataOff + V_us698Len] == 0xFF)
                                  && ( P_DataBuf[V_DataOff + V_us698Len - 1] != 0xFF ) )
								{
									P_DataBuf[V_DataOff + V_us698Len] = 0x00;
								}
								V_DataOff += (V_us698Len + 1);
							}
						}
						else if(Str_Encode.V_uc698NextType == C_TZone)		/*ʱ����*/
						{
							V_DataOff--;
							p_TableAddr = (Str_DI0_DataType_PaTable*)GV_Str_DI0_DataType_ZPaTable;
							if(V_DataLenMax < 8)
							{
								V_ucOverAPDUFlay = 0x68;
								goto DataOrganize;
							}
							V_DataLenMax -= 8;
							P_DataBuf[V_DataOff] = C_structure;
							V_DataOff++;
							P_DataBuf[V_DataOff] = 3;
							V_DataOff++;
							for( m = 0; m < 3; m++ )
							{
								P_DataBuf[V_DataOff] = p_TableAddr[m].DataType;
								SF_DataExchangeTo698_BasicData(&P_DataBuf[V_DataOff], &V_DataTemp[V_DataOff645 + m], p_TableAddr[m].DataLen_698, p_TableAddr[m].DataLen_645);
								V_DataOff += p_TableAddr[m].DataLen_698;
								V_DataOff++;
							}
						}
						else if(Str_Encode.V_uc698NextType == C_SettleDay)	/*������*/
						{
							V_DataOff--;
							if(Str_Encode.V_ulOAD != 0x41160200)
							{
								V_DataOff -= 2;
							}

							p_TableAddr = (Str_DI0_DataType_PaTable*)GV_Str_DI0_DataType_SDPaTable;

							if(V_DataLenMax < 6)
							{
								V_ucOverAPDUFlay = 0x68;
								goto DataOrganize;
							}
							V_DataLenMax -= 6;
							P_DataBuf[V_DataOff] = C_structure;
							V_DataOff++;
							P_DataBuf[V_DataOff] = 2;
							V_DataOff++;
							for( m = 0; m < 2; m++)
							{
								P_DataBuf[V_DataOff] = p_TableAddr[m].DataType;
								SF_DataExchangeTo698_BasicData(&P_DataBuf[V_DataOff], &V_DataTemp[V_DataOff645 + m], p_TableAddr[m].DataLen_698, p_TableAddr[m].DataLen_645);
								V_DataOff += p_TableAddr[m].DataLen_698;
								V_DataOff++;
							}
						}
						else
						{
							V_ucPerDataLen = Str_Encode.V_uc645Length / Str_Encode.V_uc698NextNum;
							V_us698Len = SF_GetDataTypeLen(&P_DataBuf[V_DataOff - 1]);
							if(V_DataLenMax < V_us698Len)
							{
                                V_ucOverAPDUFlay = 0x68;
								goto DataOrganize;
							}
							V_DataLenMax -= V_us698Len;
                            if((Str_Encode.V_ulOAD & 0xFF000F00) == CCom_Ac_LastPulse_FF_0)
	                        {
	                             P_DataBuf[V_DataOff] =  V_DataTemp[V_DataOff645];
                                 V_us698Len = C_EnergyCommPulseLastLen;
	                        }
#if 0
							else if( (Str_Encode.V_ulOAD & 0xFF000000) == 0x00000000)		/*����*/
							{
								V_us698Len = SF_EnergyTo698(Str_Encode.V_ulOAD, &V_DataTemp[V_DataOff645], &(P_DataBuf[V_DataOff]), V_ucPerDataLen);
							}
#endif
                            else
                            {
                                V_us698Len = SF_DataExchangeTo698_BasicData(&(P_DataBuf[V_DataOff - 1]), &V_DataTemp[V_DataOff645], V_us698Len, V_ucPerDataLen);
                            }
                            V_DataOff += (V_us698Len);
						}
						V_DataOff645 += (Str_Encode.V_uc645Length/Str_Encode.V_uc698NextNum);
					}
				}
				else if(Str_Encode.V_uc698NextType == C_TZone)								/*ʱ����*/
				{
					p_TableAddr = (Str_DI0_DataType_PaTable*)GV_Str_DI0_DataType_ZPaTable;
					if(V_DataLenMax < 8)
					{
						V_ucOverAPDUFlay = 0x68;
						goto DataOrganize;
					}
					V_DataLenMax -= 8;
					P_DataBuf[V_DataOff] = C_structure;
					V_DataOff++;
					P_DataBuf[V_DataOff] = 3;
					V_DataOff++;
					for( m = 0; m < 3; m++)
					{
						P_DataBuf[V_DataOff] = p_TableAddr[m].DataType;
						SF_DataExchangeTo698_BasicData(&P_DataBuf[V_DataOff], &V_DataTemp[V_DataOff645 + m], p_TableAddr[m].DataLen_698, p_TableAddr[m].DataLen_645);
						V_DataOff += p_TableAddr[m].DataLen_698;
						V_DataOff++;
					}
				}
				else
				{
					P_DataBuf[V_DataOff] = Str_Encode.V_uc698Type;
					V_us698Len = SF_GetDataTypeLen(&P_DataBuf[V_DataOff]);
					if(V_DataLenMax < (V_us698Len + 1))
					{
                        V_ucOverAPDUFlay = 0x68;
                        goto DataOrganize;
					}
					V_DataLenMax -= (V_us698Len + 1);
					if ( ( P_DataBuf[V_DataOff] == C_bit_string )
					  || ( P_DataBuf[V_DataOff] == C_visible_string )
                      || ( P_DataBuf[V_DataOff] == C_octet_string ) )
					{
						V_DataOff++;
						P_DataBuf[V_DataOff] = Str_Encode.V_uc698NextNum;
						V_DataOff--;
						V_us698Len =Str_Encode.V_uc698NextNum;
					}

                    if((Str_Encode.V_ulOAD & 0xFF000F00) == CCom_Ac_LastPulse_FF_0)
                    {
                        P_DataBuf[V_DataOff + 1] = V_DataTemp[V_DataOff645];
                        V_us698Len = C_EnergyCommPulseLastLen;
                    }
#if 0
					else if( (Str_Encode.V_ulOAD & 0xFF000000) == 0x00000000)		/*����*/
					{
						V_us698Len = SF_EnergyTo698(Str_Encode.V_ulOAD, &V_DataTemp[V_DataOff645], &(P_DataBuf[V_DataOff + 1]), Str_Encode.V_uc645Length);
					}
#endif
                    else
                    {
                        V_us698Len = SF_DataExchangeTo698_BasicData(&(P_DataBuf[V_DataOff]), &V_DataTemp[V_DataOff645], V_us698Len, Str_Encode.V_uc645Length);
					}

                    if ( ( P_DataBuf[V_DataOff] == C_bit_string )
					  || ( P_DataBuf[V_DataOff] == C_visible_string )
                      || ( P_DataBuf[V_DataOff] == C_octet_string ) )
					{
						if(V_DataLenMax < 1)
						{
                            V_ucOverAPDUFlay = 0x68;
							goto DataOrganize;
						}
						V_DataLenMax -= 1;
						V_DataOff++;
					}
					V_DataOff += (V_us698Len + 1);
					V_DataOff645 += Str_Encode.V_uc645Length;
				}
			}
		}
DataOrganize:
		if(V_ucRetrun == C_MaxResponseLen_ERR)
		{
			PF_CopyDataBytes(&V_DataTemp[V_DataOff645Temp], &V_OAD->Rd_RecordSelect[5], 6); /*��ֵ��һ����ʱ��*/
			V_ucTemp = 0x01;
			PF_BCDAddBytes(&V_OAD->Rd_RecordSelect[5], &V_ucTemp, &V_OAD->Rd_RecordSelect[5], 1);
			if(V_OAD->Rd_RecordSelect[5] == 0x60)
			{
				V_OAD->Rd_RecordSelect[5] = 0x00;
				SF_MinsAdd_LoadProfile(&V_OAD->Rd_RecordSelect[6], 1, &V_OAD->Rd_RecordSelect[6]);
			}
		}
		if(V_ucOverAPDUFlay == 0x68)
		{
			if(k == 0)
			{
				V_DataOff = 0;
				P_DataBuf[V_DataOff] = 0;
				V_DataOff ++;
				*P_DataOff = V_DataOff;
				V_ucRetrun = C_OK;
				return V_ucRetrun;
			}
			else
			{
                V_ucRetrun = C_MaxResponseLen_ERR;
                V_DataOff = V_DataOffTemp;    														/*��ֵ��һ����¼����ƫ�Ƶ�ַ*/
                PF_CopyDataBytes(&V_DataTemp[V_DataOff645Temp], &V_OAD->Rd_RecordSelect[5], 6);		/*��ֵ��һ����ʱ��*/
			}
		}
		if( ( V_ucRetrun == C_OK ) || ( V_ucRetrun == C_MaxResponseLen_ERR ) )						/*�к���֡Ҳ��Ҫ����*/
		{
			if((V_DataOff - 3) >= 256)
			{
				P_DataBuf[0] = 0x82;
				P_DataBuf[1] = (uchar8)((V_DataOff - 3) >> 8);
				P_DataBuf[2] = (uchar8)((V_DataOff - 3));
				*P_DataOff = V_DataOff;
			}
			else if((V_DataOff - 3) > 127)
			{
				for( i = 0; i < (V_DataOff - 3); i++ )
				{
					P_DataBuf[2 + i] = P_DataBuf[3 + i];
				}
				P_DataBuf[0] = 0x81;
				P_DataBuf[1] = (uchar8)((V_DataOff - 3));
				*P_DataOff = V_DataOff - 1;
			}
			else
			{
				for( i = 0; i < (V_DataOff - 3);i++ )
				{
					P_DataBuf[1 + i] = P_DataBuf[3 + i];
				}
				P_DataBuf[0] = (uchar8)((V_DataOff - 3));
				*P_DataOff = V_DataOff - 2;
			}
		}
		else
		{
			V_ucRetrun = C_OtherErr_DAR;
		}
	}
    else if(V_ucRetrun == C_NoData)
    {
        V_DataOff = 0;
        P_DataBuf[V_DataOff] = 0;
        V_DataOff ++;
        *P_DataOff = V_DataOff;
        V_ucRetrun = C_OK;
    }
	else
	{
		V_ucRetrun = C_OtherErr_DAR;
	}

	return V_ucRetrun;
}
/*******************************************************************************
����ԭ�ͣ�Str_Comm_698_RW	* Get_Str_698RWParm_Pointer(uchar8 CommNo)
����������698��Լͨ�Ž�������������ṹ���ַ
���������	CommNoͨ����
�����������
���ز�������ַ����
����λ�ã�
��    ע��
*******************************************************************************/
Str_Comm_698_RW	* Get_Str_698RWParm_Pointer(uchar8 CommNo)
{
	Str_Comm_698_RW	*pStr_698RWParm_Address;
	switch(CommNo)
		{
			case		C_RS485_2:
				pStr_698RWParm_Address = &SV_RS485_2_698RWParm;
				break;
			case		C_IR:
				pStr_698RWParm_Address = &SV_IR_698RWParm;
				break;
			case		C_Module:
				pStr_698RWParm_Address = &SV_Module_698RWParm;
				break;
			default:
				pStr_698RWParm_Address = &SV_RS485_1_698RWParm;
				break;
		}
	return(pStr_698RWParm_Address);
}
/*******************************************************************************
����ԭ�ͣ�ushort16 Inf_Comm_REPORTFlag(void)
������������ȡ�ϱ�״̬
���������
�����������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
ushort16 Inf_Comm_REPORTFlag(void)
{
    return SV_ReportSend.ReportFlag;
}

/*******************************************************************************
����ԭ�ͣ�uchar8 Inf_Copy_RportStr(uchar8 *P_Buf)
�����������ϱ��ṹ��ŵ�uchar8����
���������
���������
���ز����� ����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 Inf_Copy_RportStr(uchar8 *P_Buf, uchar8 V_Type)
{
	uchar8 V_Offset = 0;

    if(V_Type == C_ReportToTempVariable)
    {
        PF_Ushort16ToBuffer2_698(P_Buf + V_Offset, &SV_ReportSend.ReportLen);
        V_Offset = V_Offset + 2;
        PF_Ushort16ToBuffer2_698(P_Buf + V_Offset, &SV_ReportSend.ReportFlag);
        V_Offset = V_Offset + 2;
        PF_Ushort16ToBuffer2_698(P_Buf+V_Offset, &SV_ReportSend.Last_ReportLen);
        V_Offset = V_Offset + 2;
        memcpy(P_Buf + V_Offset, &SV_ReportSend.ReportOffset, 1);
        V_Offset++;
        memcpy(P_Buf + V_Offset, &SV_ReportSend.ReportOTimer, 1);
        V_Offset++;
        memcpy(P_Buf + V_Offset, &SV_ReportSend.PowerDown_ReportOTimer, 1);
        V_Offset++;
        memcpy(P_Buf + V_Offset, &SV_ReportSend.ReportClearNum, 1);
        V_Offset++;
        memcpy(P_Buf + V_Offset, SV_ReportSend.V_CRC, 2);
        V_Offset = V_Offset + 2;
    }
    else
    {
        SV_ReportSend.ReportLen = PF_Buffer2ToLong16_698(P_Buf + V_Offset);
        V_Offset = V_Offset + 2;
        SV_ReportSend.ReportFlag = PF_Buffer2ToLong16_698(P_Buf + V_Offset);
        V_Offset = V_Offset + 2;
        SV_ReportSend.Last_ReportLen = PF_Buffer2ToLong16_698(P_Buf + V_Offset);
        V_Offset = V_Offset + 2;
        memcpy(&SV_ReportSend.ReportOffset, P_Buf + V_Offset, 1);
        V_Offset++;
        memcpy(&SV_ReportSend.ReportOTimer, P_Buf + V_Offset, 1);
        V_Offset++;
        memcpy(&SV_ReportSend.PowerDown_ReportOTimer, P_Buf + V_Offset, 1);
        V_Offset++;
        memcpy(&SV_ReportSend.ReportClearNum, P_Buf + V_Offset, 1);
        V_Offset++;
        memcpy(SV_ReportSend.V_CRC, P_Buf + V_Offset, 2);
        V_Offset = V_Offset + 2;
    }

	return V_Offset;
}

/*******************************************************************************
����ԭ�ͣ�void SF_Deal_ReportCRC(uchar8 Type)
�������������ϱ��ṹ��CRC�Ƿ���ȷ
���������
���������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
void SF_Deal_ReportCRC(uchar8 Type)
{
    ushort16 V_CRC, V_CRCLen = CL_SV_ReportParm;
    uchar8   V_Temp[CL_SV_ReportParm], V_Return = C_OK;

	Inf_Copy_RportStr(V_Temp, C_ReportToTempVariable);					/*��report�ṹ�������ݿ�������ʱ����*/

    if(C_Check == Type)
    {
        V_Return = PF_Check_CRC_698(V_Temp, V_CRCLen);
        if( ( V_Return != C_OK )                        				/*���CRC����*/
          ||( ( SV_ReportSend.ReportFlag != C_ReportFlag)				/*�����ϱ���־���ǵ����ϱ�����Ҳ���������¼��ϱ�����Ҳ���ǿ�*/
           && ( SV_ReportSend.ReportFlag != C_PowerDownReportFlag )
           && ( SV_ReportSend.ReportFlag != C_ReportNULL ) ) )
        {
            memset(V_Temp, 0x00, V_CRCLen);             				/*�Ȳ���CRC��*/
            Inf_Copy_RportStr(V_Temp, C_TempVariableToReport); 			/*��ʱ����������report�ṹ����*/
            V_Return = C_CRCError;                      				/*����ϱ���־���Ϸ���������λ����CRC*/
        }
    }
    if( ( C_CountCRC == Type ) || ( V_Return != C_OK ) )
    {
        V_CRC = PF_Cal_CRC_698(V_Temp, V_CRCLen - 2);
        PF_Ushort16ToBuffer2(SV_ReportSend.V_CRC, &V_CRC);
    }
}
/*******************************************************************************
����ԭ�ͣ�uchar8 Inf_Comm_REPORTOTimeDeal(uchar8 *Time,uchar8 Threshold)
���������������ϱ���ȷ��ʱ��
���������
�����������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 Inf_Comm_REPORTOTimeDeal(uchar8 *Time, uchar8 Threshold)
{
    if((*Time) > Threshold)
    {
        (*Time) = Threshold;
    }
    if((*Time) > 0)
    {
        (*Time)--;
    }
    return (*Time);
}
/*******************************************************************************
����ԭ�ͣ�uchar8  Inf_Comm_ReportNum(uchar8 Type)
������������ȡ�ϱ�����
���������
�����������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8  Inf_Comm_ReportNum(uchar8 Type)
{
	uchar8 V_Return = 0;

	SF_Deal_ReportCRC(C_Check);
	if(C_OtherActiveReportInit == Type)
	{
		V_Return = Inf_Comm_REPORTOTimeDeal(&SV_ReportSend.ReportOTimer, C_ReportOTimer);
	}
	else if(C_EventTypeActiveReportInit == Type)
	{
		V_Return = Inf_Comm_REPORTOTimeDeal(&SV_ReportSend.PowerDown_ReportOTimer, C_ReportOTimer);
	}
	else if(C_ReportMaxNum_Remin == Type)
	{
		V_Return = Inf_Comm_REPORTOTimeDeal(&SV_ReportSend.ReportClearNum, C_ReportMaxDealNum);
	}
	Inf_CalReportCRC();
	return V_Return;
}
/*******************************************************************************
����ԭ�ͣ� uchar8 Inf_Comm_REPORTFlagClear(uchar8 ClearMode)
���������� ���ϱ��Ľṹ����и�ֵ
���������
���������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 Inf_Comm_REPORTFlagClear(uchar8 ClearMode)
{
    uchar8 V_Return;

    SF_Deal_ReportCRC(C_Check);
    if(ClearMode == C_ActiveReportEndFlag)                              	/*ͨ�ŷ�������֮�󣬳�ʼ���´��ϱ�ʱ�䣨���10sû��ȷ���ٴ��ϱ����3�Σ�*/
    {
        SV_ReportSend.ReportClearNum = 0;                               	/*����������ͳ������2.5S����*/
        if(SV_ReportSend.ReportFlag == C_PowerDownReportFlag)           	/*���������ϱ��ǵ��绹�������¼�*/
        {
            if(Inf_GetPowerDownEventType(C_PowerfailEventNo) == C_Happen_EventState)
            {
                SV_ReportSend.PowerDown_ReportOTimer = C_ReportOTimer1s;	/*���緢����1S���ϱ�*/
            }
            else
            {
                SV_ReportSend.PowerDown_ReportOTimer = C_ReportOTimer;  	/*10S֮�����ϱ�*/
            }
        }
        else
        {
          SV_ReportSend.ReportOTimer = C_ReportOTimer;                 		/*Ŀǰ���ʱ�仹û���ã�Ҫ��500mû��ȷ�Ͼ����ϱ���һ��ѭ����500ms*/
        }
        SV_ReportSend.ReportFlag = C_ReportNULL;                       		/*״̬����*/
    }
    else if(ClearMode == C_EventTypeActiveReportInit)                  		/*����ǵ����ʼ���ɵ�ǰΪ�����ϱ�״̬*/
    {
        SV_ReportSend.ReportFlag = C_PowerDownReportFlag;
        SV_ReportSend.ReportClearNum = C_ReportMaxDealNum;
    }
    else if(ClearMode == C_OtherActiveReportInit)
    {
        SV_ReportSend.ReportFlag = C_ReportFlag;
        SV_ReportSend.ReportClearNum = C_ReportMaxDealNum;
    }
    else if(ClearMode == C_ReportMaxNum_Remin)
    {
        V_Return = Inf_Comm_REPORTOTimeDeal(&SV_ReportSend.ReportClearNum, C_ReportMaxDealNum);
        if(V_Return == 0)
        {
          SV_ReportSend.ReportFlag = C_ReportNULL;			/*���������ͨ��Ӳ������û�з���ȥ��2.5��״̬����*/
        }
    }
    else if(ClearMode == C_NewReportFlag_EventType)			/*���������ϱ��ǵ��绹�������¼�*/
    {
      SV_ReportSend.PowerDown_ReportOTimer = 0;				/*����·����˵����ϱ�����ô10s��ʱ����*/
    }
    else if(ClearMode == C_NewReportFlag_Other)				/*���ϱ�10s��ʱ*/
    {
      SV_ReportSend.ReportOTimer = 0;						/*����·������¼��ϱ�*/
    }
    else
    {
        SV_ReportSend.ReportOffset = 0;
        SV_ReportSend.ReportLen = 0;
        SV_ReportSend.ReportFlag = C_ReportNULL;

        SV_ReportSend.ReportOTimer = 0;
        SV_ReportSend.PowerDown_ReportOTimer = 0;
        SV_ReportSend.ReportClearNum = 0;  					/*����������ͳ������2.5S����*/
    }
	Inf_CalReportCRC();

    return V_Return;										/*��Ҫ��Ϊ�˻�ȡ3�������������ϱ������������ϱ�֮��ͨ��û�з���ȥ�Ĵ���*/
}
/*******************************************************************************
����ԭ�ͣ�void CommMSg_StartTxd_698(uchar8 CommNo)
������������ͨ��Ӧ��
���������	CommNoͨ���ţ�pV_698FrameΪ�������ڽṹ��
�����������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
void CommMSg_StartTxd_698(uchar8 CommNo)
{
	Str_Comm_Parm 	*pStr_Comm_Parm_Address;

	pStr_Comm_Parm_Address = Get_Str_Comm_Parm_Pointer(CommNo);
	if(pStr_Comm_Parm_Address == C_NULL)
	{
		return;						/*ͨ������ʵ�ʲ����ܡ������ˣ�Ҳ�����ͣ�ֱ���˳���*/
	}

    CommOffset = 0;
    CommRecFlag = 0;
    CommOTimer = 0;
    if(CommNo == C_Module)  		/*ģ��ͨ��*/
    {
        if(Inf_Comm_InitModuleCommuniFlag(C_CommuniSafeWorld2))	    /*ͨ�Ž�����*/
        {
            return;
        }

        ushort16 V_ReportFlag1;

        V_ReportFlag1 = Inf_Comm_REPORTFlag();

        if(V_ReportFlag1 == 0)  	/*û��ͨ�ű�־������ͨ�ţ�������ϱ���ͻ*/
        {
            Inf_Comm_REPORTFlagClear(0);
        }
        else
        {
            {         				/*���2.5S�ڷ��ֻ�û���ϱ��ɹ������㲢������ε�ͨ��*/
                return;
            }
        }

		Inf_Comm_InitModuleCommuniFlag(C_CommuniSafeWorld3);
    }
    InF_CommUart_TxdDataForDispatch(CommNo, CommBuff[CommOffset], C_NoActiveReportFlag);
    CommOffset++;
}
/*******************************************************************************
����ԭ�ͣ�void Inf_WriteMeterStatus8(uchar8 EventNo)
�����������¼�����ʱд�����ϱ����
���������EventNo���¼���
			State��C_Happen_EventMsg �¼���������
�����������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 Inf_Comm_InitModuleCommuniFlag(uchar8 Key)
{
    uchar8 V_Return = C_SafeFlagError;

    if(Key == C_CommuniSafeWorld1)
    {
        GV_ModuleCommuni_Flag = 0;
    }
    if( ( ( Key == C_CommuniSafeWorld3 ) && ( GV_ModuleCommuni_Flag != ( C_CommuniSafeWorld1 | C_CommuniSafeWorld2 ) ) )
	  || ( ( Key == C_CommuniSafeWorld4 ) && ( GV_ModuleCommuni_Flag != ( C_CommuniSafeWorld1 | C_CommuniSafeWorld2 | C_CommuniSafeWorld3 )  ) ) )
    {
        V_Return = Key;
    }
    else
    {
        GV_ModuleCommuni_Flag |= Key;
        V_Return = C_OK;
    }
    return V_Return;
}
/*******************************************************************************
����ԭ�ͣ�void Inf_WriteMeterStatus8(uchar8 EventNo)
�����������¼�����ʱд�����ϱ����
���������EventNo���¼���
			State��C_Happen_EventMsg �¼���������
�����������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
void Inf_Comm_ClearModuleCommuniFlag(uchar8 V_ModuleFlag)
{
    if(V_ModuleFlag == C_CommunicationEnd)
    {
        if(GV_ModuleCommuni_Flag == C_CommunicationEnd)
        {
          GV_ModuleCommuni_Flag = 0xFF;
        }
    }
    else if(V_ModuleFlag == 0xFF)
    {
        if(GV_ModuleCommuni_Flag == 0xFF)
        {
            GV_ModuleCommuni_Flag = C_NoCommunication;
        }
    }
    else if(V_ModuleFlag == 0x00)
    {
        GV_ModuleCommuni_Flag = C_NoCommunication;
    }

}
/*******************************************************************************
����ԭ�ͣ�void Inf_WriteMeterStatus8(uchar8 EventNo)
�����������¼�����ʱд�����ϱ����
���������EventNo���¼���
			State��C_Happen_EventMsg �¼���������
�����������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 Inf_Comm_GetModuleCommuniFlag(void)
{
    return GV_ModuleCommuni_Flag;
}
/*******************************************************************************
����ԭ�ͣ�void CommMSg_StartTxd_698REPORT(uchar8 CommNo,uchar8 ReportType)
������������ͨ��Ӧ��
���������	CommNoͨ���ţ�pV_698FrameΪ�������ڽṹ��
�����������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
void CommMSg_StartTxd_698REPORT(uchar8 CommNo, uchar8 ReportType)
{
    uchar8 *p_SendAddress;

	SV_ReportSend.ReportOffset = 0;
    p_SendAddress = SV_REPORTCommBuff;

	InF_CommUart_TxdDataForDispatch(CommNo, p_SendAddress[SV_ReportSend.ReportOffset], C_ActiveReportFlag);
	Inf_Comm_REPORTFlagClear(ReportType);
	SV_ReportSend.ReportOffset++;
    Inf_CalReportCRC();
}
/*******************************************************************************
����ԭ�ͣ�void Connect_Service_Deal(Str_Comm_698_RW *pV_698RWPara, uchar8 *pV_DataBuf, ushort16 V_BufLen, uchar8 *pV_NextFrFlag)
��������������Ӧ������
���������pV_698RWPara��ͨ�Žṹ�壻
         pV_DataBuf���������ݣ�
         V_BufLen�����ݳ���
�����������
���ز�������
����λ�ã�
��    ע��
*******************************************************************************/
void Connect_Service_Deal(Str_Comm_698_RW *pV_698RWPara, uchar8 *pV_DataBuf, ushort16 V_BufLen, uchar8 *pV_NextFrFlag)
{
	ushort16 V_ucLen, V_len, V_Len, V_usDataEncode;
	uchar8 V_DataBuf[40], V_DataBuf1[40], i;
    uchar8  V_Mechanism = 0;
/*******************������֤��Ϣ��֤����֯Ӧ����Ϣ*******************/
	if( ( pV_698RWPara->Wt_OI[0].WtOI == 0 ) && ( pV_698RWPara->Wt_OI[0].Wt_Result == C_OK ) )
	{
		if(pV_698RWPara->Wt_OI[0].Wt_Data[0] == C_NullSecyrityConnect)	            /*��������*/
		{
			pV_698RWPara->Wt_OI[0].Wt_Result = C_OK;
		}
		else if(pV_698RWPara->Wt_OI[0].Wt_Data[0] == C_PasswordSecurityConnect)	    		/*һ������*/
		{
			/*�����ж������Ƿ�������Ǳ���ֱ�ӷ����������*/
			if(Comm_DealwithSPTVariable(C_JudgeKeyErr | 0x80) == C_KeyErr_Num_Over)
			{
				pV_698RWPara->Wt_OI[0].Wt_Result = C_OtherErr_DAR;          				/*��������Ӧ����������*/
			}
			else
			{
				V_ucLen = 40;
				pV_698RWPara->Wt_OI[0].Wt_Result = C_OK;
				if(InF_Read_Data(C698Key, &V_DataBuf[0], &V_ucLen, &V_usDataEncode) == C_OK)					/*������ */
				{
					if(pV_698RWPara->Wt_OI[0].Wt_Data[1] <= 40)
					{
						for( i = 0; i < pV_698RWPara->Wt_OI[0].Wt_Data[1]; i++ )
						{
							V_DataBuf1[i] = V_DataBuf[pV_698RWPara->Wt_OI[0].Wt_Data[1] - i - 1];
						}
						if(PF_Campare_Data(&V_DataBuf1[0],&pV_698RWPara->Wt_OI[0].Wt_Data[2],pV_698RWPara->Wt_OI[0].Wt_Data[1]) != C_Equal)
						{
							pV_698RWPara->Wt_OI[0].Wt_Result = C_PasswordErr_DAR;
							if(InF_JudgeIJTimer() != C_OK)									/*�������������*/
							{
								Comm_DealwithSPTVariable(C_KeyErrNumAdd | C_Key02Flag);		/*ʹ��02���������*/
							}
						}
						else
						{
							Comm_DealwithSPTVariable(C_ClrKeyErrNum | C_Key02Flag);
						}
					}
				}
				else
				{
					pV_698RWPara->Wt_OI[0].Wt_Result = C_PasswordErr_DAR;
				}
			}
			pV_698RWPara->Wt_OI[0].DataLen = 0;
		}
        else if(pV_698RWPara->Wt_OI[0].Wt_Data[0] == C_SignatureSecurityConnect)			/*����ǩ��*/
        {
			pV_698RWPara->Wt_OI[0].Wt_Result = C_SignErr_DAR;
			pV_698RWPara->Wt_OI[0].DataLen = 0;
        }
		else if(pV_698RWPara->Wt_OI[0].Wt_Data[0] == C_SymmetrySecurityConnect)	    		/*�Գ���Կ*/
		{
			pV_698RWPara->Wt_OI[0].DataLen = 50;
			V_len = 60;
			pV_698RWPara->Wt_OI[0].Wt_Result = InF_S_Authentication_698(&pV_698RWPara->Wt_OI[0].Wt_Data[1], &V_len, SV_Comm_Parse_Local.ClientAddrFlag);
			if(pV_698RWPara->Wt_OI[0].Wt_Result != C_OK)
			{
				if(pV_698RWPara->Wt_OI[0].Wt_Result == C_RequestTimeOut_DAR)
				{
					pV_698RWPara->Wt_OI[0].Wt_Result = C_ESAMCommFault_DAR;
				}
				else
				{
					pV_698RWPara->Wt_OI[0].Wt_Result = C_SymmDecodeErr_DAR;
				}
			}
			pV_698RWPara->Wt_OI[0].DataLen = (uchar8)V_len;

			InF_JudgeESAMConTimer(C_ReworkDealConectTime, SV_Comm_Parse_Local.ClientAddrFlag);
		}
        else    /*�쳣���*/
        {
			pV_698RWPara->Wt_OI[0].Wt_Result = C_OtherErr_DAR;
			pV_698RWPara->Wt_OI[0].DataLen = 0;
        }
		PF_CopyDataBytes_698(&pV_698RWPara->Wt_OI[0].Wt_Data[1], pV_DataBuf, pV_698RWPara->Wt_OI[0].DataLen);
	}
    if(pV_698RWPara->Wt_OI[0].Wt_Result == C_OK)
    {
		V_Len = CLConAutheMechanism;
        InF_Read_Data(CConAutheMechanism, &V_Mechanism, &V_Len, &V_usDataEncode);
        if(V_Mechanism != pV_698RWPara->Wt_OI[0].Wt_Data[0])
        {
            InF_Write_Data(C_Msg_Communication, CConAutheMechanism, &pV_698RWPara->Wt_OI[0].Wt_Data[0], 1, C_W_SafeFlag);
        }
		if(SV_Comm_Parse_Local.ClientAddrFlag == Termal_Address)			/*�ն������֤ʧЧ*/
		{
			memset( V_DataBuf, 0, C_TimerExceed10minLen );
			DealWith_ID_Auth_T_Timer(C_Set_TimerExceed10min, &V_DataBuf[0]);
		}
    }
	Comm_AppendMsg(CMsg_Txd);
}
/*******************************************************************************
����ԭ�ͣ�void RELEASE_Service_Deal(uchar8 Client_Addr)
�����������Ͽ�Ӧ�����ӣ���Ӧ������ʣ��ʱ������
���������	CommNoͨ���ţ�PowerFlagΪ�����־
�����������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
void RELEASE_Service_Deal(uchar8 Client_Addr)
{
	uchar8 V_ucBuffer[20];
	uchar8 V_ResetFlage = 0;

	if(Client_Addr == Termal_Address)
	{
		Com_Conect.ConectOverTime_termal = 0;
		if( ( Com_Conect.ConectOverTime == 0)								/*��վӦ������*/
		 && ( JudgeTimerExceed10min( &IR_AuthT ) != C_TimerEnable )			/*���������֤*/
		 && ( JudgeTimerExceed10min( &ID_AuthT_T ) != C_TimerEnable ) )		/*�ն������֤*/
		{
			V_ResetFlage = C_Valid;
		}
	}
	else
	{
		Com_Conect.ConectOverTime = 0;
		if( ( Com_Conect.ConectOverTime_termal == 0 )
		 && ( JudgeTimerExceed10min( &IR_AuthT ) != C_TimerEnable )			/*���������֤*/
		 && ( JudgeTimerExceed10min( &ID_AuthT_T ) != C_TimerEnable ) )		/*�ն�Ӧ�����Ӻ������֤����Ч*/
		{
			V_ResetFlage = C_Valid;
		}
	}

	Com_Conect.CRC16 = PF_Cal_CRC((uchar8 *)&Com_Conect.ConectOverTime, C_ConectStruct_Len);		/*����Ӧ������ʱ��*/

	if(V_ResetFlage == C_Valid)												/*����0����λesam*/
	{
		V_ucBuffer[0] = Pt_ResetEsam;										/*���͸�λ��Ϣ��ESAMģ��*/
		Dispatch_SendMessage(C_Msg_Esam, V_ucBuffer, Pt_ResetEsam_Len+1);
	}
	Comm_AppendMsg(CMsg_Txd);
}
/*******************************************************************************
����ԭ�ͣ�uchar8 INF_RELEASE_Service_Deal_Card(void)
�����������Ͽ�Ӧ�����ӣ���Ӧ������ʣ��ʱ������
���������CommNoͨ���ţ�PowerFlagΪ�����־
�����������
���ز�������ַ����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 INF_RELEASE_Service_Deal_Card(void)
{
	uchar8 V_ucBuffer[20], V_ucReturnData;

	Com_Conect.ConectOverTime_termal = 0;									/*�ն�Ӧ������ʱ������*/
	Com_Conect.ConectOverTime = 0;											/*��վӦ������ʱ������*/
	Com_Conect.CRC16 = PF_Cal_CRC((uchar8 *)&Com_Conect.ConectOverTime, C_ConectStruct_Len);

	memset( V_ucBuffer, 0, C_TimerExceed10minLen );
	DealWith_IR_Auth_Timer(C_Set_TimerExceed10min, &V_ucBuffer[0]);			/*������֤��Ч*/
	DealWith_ID_Auth_T_Timer(C_Set_TimerExceed10min, &V_ucBuffer[0]);		/*�ն���֤��Ч*/

	V_ucReturnData = SF_ColdReset_7816_Esam(&V_ucBuffer[0]);				/*�临λ*698����ESAM���к�*/

	return V_ucReturnData;
}
/*******************************************************************************
����ԭ�ͣ�void	SF_Get_OADClassNO(ulong32 V_OAD,uchar8 *pClassNum,uchar8 *pDataType,uchar8 ServiceFlag)
�������������ݶ���OAD��ȡ��Ӧ�����༰���ݻ�ȡ��ʽ
���������s
�����������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
#define	C_OI_Data			0x01		/*��ȡ������*/
#define	C_ScaleUnit_Data	0x02		/*��ȡ��λ������*/
#define	C_DataBase_Data		0x03		/*��ȡ���ݲ�����*/
#define	C_RelatedOAD_Data	0x04		/*��ȡ���������б�*/
#define	C_FixedTimes_Data	0x05		/*��ȡ�̶�������¼����*/
#define	C_EventRecord_Data	0x06		/*��ȡ�̶�������¼����*/
#define C_Event7ActiveSign	0x68        /*��7������9*/
#define C_Event24ActiveSign	0x86        /*��24������12*/

void	SF_Get_OADClassNO(ulong32 V_OAD, uchar8 *pClassNum, uchar8 *pDataType, uchar8 ServiceFlag)
{
	uchar8 V_OIA, V_OIB, V_Natural, i;

	V_OIA = (uchar8)(V_OAD >> 24);
	V_OIB = (uchar8)(V_OAD >> 16);
	V_Natural = (uchar8)(V_OAD >> 8);
	V_Natural &= 0x1F;

	*pDataType = C_NULL;
	if(V_Natural == 1)
	{
		*pDataType = C_OI_Data;
        return;
	}
	switch(V_OIA)
	{
		case C_EnergyOIA:
		{
			*pClassNum = 1;
			if( ( V_Natural == C_Nature2_Energy )
             || ( V_Natural == C_Nature4_PreEnergy )
             || ( V_Natural == C_Nature6_LastNumPulse ) )
			{
				*pDataType = C_DataBase_Data;
			}
			else if( ( V_Natural == C_Nature3_EnergyUnit )
                  || ( V_Natural == C_Nature5_PreEnergyUnit )
                  || ( V_Natural == C_Nature7_LastNumPulseUnit ) )
			{
				*pDataType = C_ScaleUnit_Data;
			}
			break;
		}
		case C_DemandOIA:
		{
			*pClassNum = 2;
			if(V_Natural == 2)
			{
				*pDataType = C_DataBase_Data;
			}
			else if(V_Natural == 3)
			{
				*pDataType = C_ScaleUnit_Data;
			}
			break;
		}
		case C_ParameterOIA40:
		{
			*pClassNum = 8;
            if(V_OIB == 0x00)
            {
                if( ( V_Natural == 2 ) || ( V_Natural == 5 ) )
                {
                    *pDataType = C_DataBase_Data;
                }
            }
            else
            {
                if(V_Natural == 2)
                {
                    *pDataType = C_DataBase_Data;
                }
            }
			break;
		}
		case C_ParameterOIA41:
		{
			*pClassNum = 8;
			if(V_Natural == 2)
			{
				*pDataType = C_DataBase_Data;
			}
			break;
		}
		case	C_ParameterOIA43:		/*���ܱ��豸��Ϣ*/
		{
			*pClassNum = 19;
			if(V_Natural > 1)
			{
				*pDataType = C_DataBase_Data;
			}
			break;
		}
		case	C_PasswordrOIA44:		/*����*/
		{
			*pClassNum = 20;
			if(V_Natural > 1)
			{
				*pDataType = C_DataBase_Data;
			}
            break;
		}
		case C_VariableOIA20:
		{
			if( ( V_Natural == 2 ) || ( V_Natural == 4 ) )
			{
				*pDataType = C_DataBase_Data;
			}
			else if(V_Natural == 3)
			{
				*pDataType = C_ScaleUnit_Data;
			}
			for( i = 0; i < GV_Str_OIB_DI2_VariableTable01Len; i++ )
			{
				if(V_OIB == GV_Str_OIB_DI2_VariableTable01[i].OIB)
				{
					/**************ȡ�����ʶ��*************/
					*pClassNum = GV_Str_OIB_DI2_VariableTable01[i].ClassType;
				}
			}
			break;
		}
		case C_VariableOIA21:
		{
			*pClassNum = 8;
			if(V_Natural == 2)
			{
				*pDataType = C_DataBase_Data;
			}
			else if(V_Natural == 3)
			{
				*pDataType = C_ScaleUnit_Data;
			}
			break;
		}
		case C_EventRecordOIA:
		{
			uchar8 V_ucClassNum;
			for( i = 0; i < C_Event_OIBTableLen; i++ )
			{
				if(V_OIB == Event_OIBTable[i].OIB)
				{
					break;
				}
			}
			if( i < C_Event_OIBTableLen )
			{
				V_ucClassNum = Event_OIBTable[i].TypeClass & 0x3F;
				*pClassNum = V_ucClassNum;
				/*******************��ȡ���ò���********************/
				if( ( ( V_Natural == 5 ) && ( V_ucClassNum == 7 ) )					/*��ȡ����¼����*/
				 || ( ( V_Natural == 4 ) && ( V_ucClassNum == 24 ) ) )
				{
					*pDataType = C_FixedTimes_Data;
				}
				else if( ( ( V_Natural == 3 ) && ( V_ucClassNum == 7 ) )			/*��ȡ��������*/
					  || ( ( V_Natural == 2 ) && ( V_ucClassNum == 24 ) ) )
				{
					*pDataType = C_RelatedOAD_Data;
				}
				else if( ( ( V_Natural == 2 ) && ( V_ucClassNum == 7 ) )			/*��ȡ��������*/
					|| ( ( ( V_Natural >= 6 ) && ( V_Natural <= 9 ) ) && ( V_ucClassNum == 24 ) ) )
				{
					*pDataType = C_EventRecord_Data;
				}
				else if( ( V_Natural == 9 ) && ( V_ucClassNum == 7 ) )				/*��ȡ��Ч��־*/
				{
					*pDataType = C_Event7ActiveSign;
				}
				else if( ( V_Natural == 12 ) && ( V_ucClassNum == 24 ) )			/*��ȡ��Ч��־*/
	            {
					*pDataType = C_Event24ActiveSign;
	            }
				else if(V_Natural != 1)
				{
					*pDataType = C_DataBase_Data;
				}
			}
			break;
		}
		case C_FrozeRecordOIA:
		{
			*pClassNum = C_Freeze_Class;
			/*******************��ȡ���ò���********************/
			if(V_Natural == 3)	/*��ȡ��������*/
			{
              if(ServiceFlag == C_GETRecord_Request)
              {
				*pDataType = C_DataBase_Data;
              }
              else
              {
				*pDataType = C_RelatedOAD_Data;
              }
			}
			else if(V_Natural != 1)
			{
				*pDataType = C_DataBase_Data;
			}
                        break;
		}
		case C_ESAMActionOIA:
		{
			*pClassNum = C_Parameter_Class;
			/*******************��ȡ���ò���********************/
			if( ( V_Natural == 3 ) && ( V_OIB == 0x01 ) )		/*��ȡ��������*/
			{
				*pDataType = C_RelatedOAD_Data;
			}
			else if(V_Natural != 1)
			{
				*pDataType = C_DataBase_Data;
			}
                        break;
		}
		case C_ReportList:
			*pClassNum = C_Parameter_Class;
			if( ( V_Natural == 2 ) || ( V_Natural == 3 ) )
			{
				*pDataType = C_RelatedOAD_Data;
			}
			break;
		case	C_ExternalOIA:									/*��չ������*/
		{
			*pDataType = C_DataBase_Data;
			*pClassNum = C_Parameter_Class;
            break;
		}
		default:
			break;
	}
}
/*******************************************************************************
����ԭ�ͣ�void Get_Service_Deal(Str_Comm_698_RW *pV_698RWPara, uchar8 *pV_DataBuf, ushort16 V_BufLen, uchar8 *pV_NextFrFlag)
�������������ݽ����Ķ����ʶ
���������pV_698RWPara:ͨ�Žṹ��
         pV_DataBuf�����ݻ���
         pV_NextFrFlag
���������pV_DataBuf������
         V_BufLen�����ݳ���
���ز�������
����λ�ã�ͨ��
��    ע��
*******************************************************************************/
void Get_Service_Deal(Str_Comm_698_RW *pV_698RWPara, uchar8 *pV_DataBuf, ushort16 V_BufLen, uchar8 *pV_NextFrFlag)
{
	uchar8 i, j, V_645DINum;
	ushort16 V_DataOff, V_BufRemainLen;
	Str_Type645DI_Class V_DIFor645[2] = {0};
	uchar8 V_ucItemNum;
	uchar8    k, V_Num = 0, V_Temp[CLUpTellChannel] = {0};
	ushort16  V_ucLen = CLUpTellChannel, V_usDataEncode;
	uchar8  V_DataTemp[50] = {0};
	ulong32 V_OADTemp;
	uchar8 V_NumOAD, V_NumOI, V_EventOI[C_NewReportMaxNum * 2] = {0}, V_Len = C_NewReportMaxNum * 2;
	uchar8 V_EventNo[C_NewReportMaxNum] = {0}, V_OADLen = 4, Len = C_NewReportMaxNum;
	ushort16 V_BytesLen;
	ulong32 V_EventOAD;
	uchar8 V_Circle, V_ReportReadOAD, V_Flag = 0;
	uchar8 V_RemainReportNO[C_NewReportMaxNum], V_RemainReportNum;
	uchar8 V_GetNoFlag = 0, V_OADNum = 0, V_OADNo= 0, V_ReadSign = 0;
	uchar8 V_ZeroTemp[CLDrive_Report_State] = {0}, *V_ChannelTemp;
	ushort16 V_usDataLen = CLDrive_Report_State;	
	
	*pV_NextFrFlag = 0;
	switch(pV_698RWPara->ServiceFlag_Second)
	{
		case C_GETNormal_Request:
		case C_GETNormalList_Request:
		case C_GETRecord_Request:
		case C_GETRecordList_Request:
			if(C_GETNext_Request != pV_698RWPara->ServiceFlag_Second)
			{
				pV_698RWPara->Next_OINO = 0;	            /*��һ֡����֡���*/
				pV_698RWPara->Current_FrameNO = 0;	        /*��ǰ֡���*/
				pV_698RWPara->ResponedNum = 0;
				pV_698RWPara->HaveEncodeNum = 0;
				pV_698RWPara->ResponedRelationNum = 0;
				pV_698RWPara->EndFrame = 0;		            /*Ӧ�ò�֡�������*/
				pV_698RWPara->FrameNUM = 0;		            /*Ӧ�ò�ĩ֡�������*/
				pV_698RWPara->LastServiceFlag_Second = 0;   /*Ӧ�ò㱣������һ֡��������*/
				pV_698RWPara->CurrentOADEnd = 0;
			}
		case C_GETNext_Request:
		{
			if(C_GETNext_Request == pV_698RWPara->ServiceFlag_Second)
			{
				pV_698RWPara->ResponedNum = pV_698RWPara->HaveEncodeNum;	/*�Ѿ�����������ȸ�ֵ�����Ѿ�Ӧ�����*/
			}

			V_DataOff = 0;

			for( i = pV_698RWPara->ResponedNum; i < pV_698RWPara->RWOI_Num; i++)
			{
                memset(&V_DIFor645[0], 0x00, Str_Type645DI_ClassLen);
                memset(&V_DIFor645[1], 0x00, Str_Type645DI_ClassLen);

                V_GetNoFlag = Inf_ReportGetEventNo(pV_698RWPara, &V_ReadSign, V_EventNo, &V_OADNum);

                if(V_GetNoFlag == C_OK)
                {
                    for(V_OADNo = 0; V_OADNo < V_OADNum; V_OADNo++)
                    {
                        Inf_EventReport_Sign(V_ReadSign, pV_698RWPara->ChannelNo, V_EventNo[V_OADNo], C_ReadReportFlag);
                    }
                }
                /*******************ȡ��ȡ���ݶ�������*********************/
                if(pV_698RWPara->Rd_OI[i].Rd_Result == C_OK)
                {
                    pV_698RWPara->Rd_OI[i].Rd_Result = JudgeMeterType(pV_698RWPara->Rd_OI[i].RdOI.OAD);
                    if(pV_698RWPara->Rd_OI[i].Rd_Result == C_OK)
                    {
                        V_BufRemainLen = C_Comm_Data_MaxLen_698 - V_DataOff - C_EnCodeMaxLen - (pV_698RWPara->RWOI_Num * 5);	/**/

                        pV_698RWPara->Rd_OI[i].Rd_Result = SF_Judge_OINature(pV_698RWPara,V_DIFor645,&V_645DINum,C_Read);   	/*����������*/

                        if(pV_698RWPara->Rd_OI[i].Rd_Result == C_OK)
                        {
                            if((pV_698RWPara->Rd_OI[i].RdOI.OAD & 0xFFFF0000) == 0xF1000000)	    							/*ESAM����*/
                            {
                                if(pV_698RWPara->ServiceFlag_Second > 2)														/*��ʾ����¼���ߺ���֡*/
                                {
                                    pV_698RWPara->Rd_OI[i].Rd_Result = C_RWForbid_DAR;
                                }
                                else
                                {
                                    if(pV_698RWPara->Rd_OI[i].RdOI.OAD == 0xF1000100)
                                    {
                                        pV_698RWPara->Rd_OI[i].RdOI.DataType = C_octet_string;
                                        pV_DataBuf[V_DataOff] = 0x02;
                                        pV_DataBuf[V_DataOff+1] = 0xF1;
                                        pV_DataBuf[V_DataOff+2] = 0x00;
                                        V_DataOff += 3;
                                    }
                                    else
                                    {
                                        if(pV_698RWPara->Rd_OI[i].RdOI.DataType == C_structure)
                                        {
                                            V_BufRemainLen -= 7;
											pV_698RWPara->Rd_OI[i].Rd_Result = InF_GetData_ObjectManage(pV_698RWPara->Rd_OI[i].RdOI.OAD, &pV_DataBuf[V_DataOff+7], &V_BufRemainLen, &V_usDataEncode);
											PF_OneDataReversed(&pV_DataBuf[V_DataOff + 7], &pV_DataBuf[V_DataOff + 7], V_BufRemainLen);
                                            if(pV_698RWPara->Rd_OI[i].RdOI.OAD == 0xF1001500)     /*�ն˻Ự����*/
                                            {
                                                V_ucItemNum = 2;
                                            }
                                            else if(pV_698RWPara->Rd_OI[i].RdOI.OAD ==0xF1000700)
                                            {
                                                V_ucItemNum = 3;
                                            }
                                            else	/*��ʱ�ò���*/
                                            {
                                                V_ucItemNum =2;
                                            }

                                            if(pV_698RWPara->Rd_OI[i].Rd_Result == C_OK)
                                            {
												pV_DataBuf[V_DataOff] = (uchar8)(V_BufRemainLen + V_ucItemNum);
												V_DataOff++;

												for(j = 0; j < V_ucItemNum; j++)
												{
													pV_DataBuf[V_DataOff] = C_double_long_unsigned;
													V_DataOff++;
													PF_CopyDataBytes(&pV_DataBuf[V_DataOff + 5 - j], &pV_DataBuf[V_DataOff], 4);
													V_DataOff += 4;
												}
											}
										}
                                        else
                                        {
                                        	V_OADTemp = pV_698RWPara->Rd_OI[i].RdOI.OAD;
                                        	
											if( ( pV_698RWPara->Rd_OI[i].RdOI.OAD == CInfra_Auth_Remain_Time )
											 && ( SV_Comm_Parse_Local.ClientAddrFlag == Termal_Address ) )			/*������֤ʣ��ʱ��   *�ն�*/
											{
												V_OADTemp = CID_Auth_T_Remain_Time;
											}
											pV_698RWPara->Rd_OI[i].Rd_Result = InF_GetData_ObjectManage(V_OADTemp, &pV_DataBuf[V_DataOff + 1], &V_BufRemainLen, &V_usDataEncode);
											
											if( ( ( pV_698RWPara->Rd_OI[i].RdOI.OAD == CID_Auth_Remain_Time )&&( Com_Conect.ConectOverTime == 0 ) )		/*��ȡ����6 ��վʣ��ʱ��ȫ�ֱ���Ϊ0�����0*/
											||( ( pV_698RWPara->Rd_OI[i].RdOI.OAD == C_Remain_termal )&&( Com_Conect.ConectOverTime_termal == 0 ) ) )	/*��ȡ����21����2 �ն�ʣ��ʱ��ȫ�ֱ���Ϊ0�����0*/
											{
												memset( &pV_DataBuf[V_DataOff + 1], 0x00, V_BufRemainLen );		
											}
											
											PF_OneDataReversed(&pV_DataBuf[V_DataOff + 1], &pV_DataBuf[V_DataOff + 1], V_BufRemainLen);
                                            if(pV_698RWPara->Rd_OI[i].Rd_Result == C_OK)
                                            {
	                                            pV_DataBuf[V_DataOff] = (uchar8)V_BufRemainLen;
	                                            V_DataOff++;
	                                            V_DataOff += V_BufRemainLen;
                                            }
                                        }
                                    }
                                }
                                V_BufRemainLen = 0;
                            }
                            else if((pV_698RWPara->Rd_OI[i].RdOI.OAD &0xFF00FF00) == 0xF2000200)	/*��������豸�����*/
                            {
                                pV_698RWPara->Rd_OI[i].Rd_Result = 	SF_GetAPDU_ApplianceInOutRead(pV_698RWPara->Rd_OI[i], &pV_DataBuf[V_DataOff],V_DataOff,&V_BufRemainLen);
                            }
                            else if((pV_698RWPara->Rd_OI[i].RdOI.OAD &0xFF00FF00) == 0xF3000200)	/*ֻ����ʾ���ȡ�ڴ˴�����ʾ������ʱ�䲻�ڴ˴�����*/
                            {
                                pV_698RWPara->Rd_OI[i].Rd_Result = SF_GetAPDU_DISPRead(pV_698RWPara->Rd_OI[i], &pV_DataBuf[V_DataOff],V_DataOff,&V_BufRemainLen);
                            }
                            else if((pV_698RWPara->Rd_OI[i].RdOI.OAD &0xFFFFFF00) == 0x40110200)	/*�������ն�ȡ��������*/
                            {
                                pV_698RWPara->Rd_OI[i].Rd_Result = SF_GetAPDU_HolidyRead((RdOI_Para_T *)&pV_698RWPara->Rd_OI[i], &pV_DataBuf[V_DataOff],V_DataOff,V_645DINum,&V_BufRemainLen);
                            }
							else if( (pV_698RWPara->Rd_OI[i].RdOI.OAD &0xFFFF0000) == 0xFF860000)	/*��չ�����ȡ��������*/
                            {
                                pV_698RWPara->Rd_OI[i].Rd_Result = InF_Read_Data(pV_698RWPara->Rd_OI[i].RdOI.OAD, &pV_DataBuf[V_DataOff + 1], &V_BufRemainLen, &V_usDataEncode);
								pV_698RWPara->Rd_OI[i].RdOI.DataType = C_octet_string;
								pV_DataBuf[V_DataOff] = (uchar8)V_BufRemainLen;
								V_DataOff++;
								V_DataOff += (uchar8)V_BufRemainLen;
                                V_BufRemainLen = 0;
                            }
                            else
                            {
								uchar8 V_ClassNum, V_DataType;
                                SF_Get_OADClassNO(pV_698RWPara->Rd_OI[i].RdOI.OAD,&V_ClassNum, &V_DataType,pV_698RWPara->ServiceFlag_Second);
                                if( V_DataType == C_OI_Data )	                					/*��ȡ�߼���*/
                                {
                                    pV_698RWPara->Rd_OI[i].RdOI.DataType = C_octet_string;
                                    pV_DataBuf[V_DataOff] = 2;
                                    V_DataOff++;
                                    pV_DataBuf[V_DataOff] = (uchar8)(pV_698RWPara->Rd_OI[i].RdOI.OAD >> 24);
                                    V_DataOff++;
                                    pV_DataBuf[V_DataOff] = (uchar8)(pV_698RWPara->Rd_OI[i].RdOI.OAD >> 16);
                                    V_DataOff++;
                                    V_BufRemainLen = 0;
                                }
                                else if( V_DataType == C_ScaleUnit_Data )	    					/*��ȡ��λ������*/
                                {
                                    pV_698RWPara->Rd_OI[i].RdOI.DataType = C_Scaler_Unit;
                                    pV_DataBuf[V_DataOff] = 2;
                                    V_DataOff++;
                                    PF_Ushort16ToBuffer2(&pV_DataBuf[V_DataOff], &V_DIFor645->Unit_Scale[0]);
                                    V_DataOff += 2;
                                    V_BufRemainLen = 0;
                                }
                                else if( ( V_DataType == C_Event7ActiveSign ) || ( V_DataType == C_Event24ActiveSign ) )	/*����Ч��־*/
                                {
                                    pV_698RWPara->Rd_OI[i].RdOI.DataType = C_bool;
                                    memset(&pV_DataBuf[V_DataOff], 1, 2);
                                    V_DataOff += 2;
                                    V_BufRemainLen = 0;
                                }
                                else if( V_DataType == C_RelatedOAD_Data )							/*��ȡ���������б�*/
                                {
                                    pV_698RWPara->Rd_OI[i].RdOI.CarryNum= 0;
                                    pV_DataBuf[V_DataOff] = 0;
									ushort16 V_OffsetTemp = V_BufRemainLen, V_DeepLen;
									uchar8 V_OIA, V_OIC, V_TableNo;
                                    V_OIA = (uchar8)(pV_698RWPara->Rd_OI[i].RdOI.OAD >> 24);
                                    V_OIC = (uchar8)(pV_698RWPara->Rd_OI[i].RdOI.OAD >> 8);

                                    if(V_OIA == C_ReportList)
                                    {
                                        if(V_OIC == 0x02)
                                        {
                                            InF_GETListData(pV_698RWPara->ChannelNo, &V_NumOAD, V_EventNo, Len, V_RemainReportNO, &V_RemainReportNum, C_ReadReportFlag);
                                            V_ReportReadOAD = (uchar8)(pV_698RWPara->Rd_OI[i].RdOI.OAD);
                                            if(V_ReportReadOAD != 0)
                                            {
                                                if(V_ReportReadOAD > V_NumOAD)
                                                {
                                                    V_NumOAD = 0;
                                                    V_Flag = 1;   /*������*/
                                                }
                                                else
                                                {
                                                    V_NumOAD = 1;
                                                    V_EventNo[0] = V_EventNo[V_ReportReadOAD - 1];
                                                }
                                            }

                                            pV_698RWPara->Rd_OI[i].RdOI.CarryNum = V_NumOAD;

                                            if(V_ReportReadOAD == 0x00)
                                            {
                                                pV_698RWPara->Rd_OI[i].RdOI.DataType = C_array;
                                                V_BytesLen = V_NumOAD;
                                                V_BytesLen *= 5;
                                            }
                                            else
                                            {
                                                pV_698RWPara->Rd_OI[i].RdOI.DataType = C_OAD;
                                                V_BytesLen = 4;
                                            }

                                            if(V_Flag == 0)
                                            {
                                                V_DataOff += SF_DataLen_AXDR_Encode(&pV_DataBuf[V_DataOff], V_BytesLen);
                                                for(V_Circle = 0; V_Circle < V_NumOAD; V_Circle++)
                                                {
                                                    pV_DataBuf[V_DataOff] = C_OAD;
                                                    V_DataOff++;
                                                    V_EventOAD=InF_EventOADFind(V_EventNo[V_Circle]);
                                                    V_EventOAD = V_EventOAD & 0xFFFFFF00;
                                                    PF_Ulong32ToBuffer4_698(&pV_DataBuf[V_DataOff], &V_EventOAD, V_OADLen);
                                                    V_DataOff += 4;
                                                }
                                                if(V_ReportReadOAD != 0x00)
                                                {
                                                    PF_CopyDataBytes_698(&pV_DataBuf[2], &pV_DataBuf[1], V_BytesLen);
                                                }
                                            }
                                            else
                                            {
                                                pV_DataBuf[V_DataOff] = 0;
                                                V_DataOff++;
                                            }
                                        }
                                        else
                                        {
                                            SF_GetReportOI(V_EventOI, &V_NumOI, V_Len);
                                            pV_698RWPara->Rd_OI[i].RdOI.CarryNum = V_NumOI;
                                            V_BytesLen = V_NumOI * 3;
                                            V_DataOff += SF_DataLen_AXDR_Encode(&pV_DataBuf[V_DataOff], V_BytesLen);
                                            for(V_Circle = 0; V_Circle < V_NumOI; V_Circle++)
                                            {
                                                pV_DataBuf[V_DataOff] = C_OI;
                                                V_DataOff++;
                                                pV_DataBuf[V_DataOff] = V_EventOI[V_Circle * 2];
                                                V_DataOff++;
                                                pV_DataBuf[V_DataOff] = V_EventOI[V_Circle * 2 + 1];
                                                V_DataOff++;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        if(V_OIA == C_ESAMActionOIA)
                                        {
                                            if(SF_SecurityOIRead(&pV_DataBuf[V_DataOff+1],&V_OffsetTemp,&V_TableNo)!=C_OK)
                                            {
                                                pV_698RWPara->Rd_OI[i].Rd_Result = C_OtherErr_DAR;	/*���ݲ�CRC���󣬷���FF*/
                                                pV_698RWPara->ResponedNum++;
                                                continue;
                                            }
                                            pV_698RWPara->Rd_OI[i].RdOI.CarryNum = V_TableNo;
                                            pV_698RWPara->Rd_OI[i].RdOI.DataType = C_array;
                                        }
                                        else if(V_OIA == C_FrozeRecordOIA)
                                        {
                                            pV_698RWPara->Rd_OI[i].Rd_Result = SF_FreezeOADRead(pV_698RWPara->Rd_OI[i],&pV_DataBuf[V_DataOff+1], &V_OffsetTemp, 0, &V_TableNo);

                                            if(V_TableNo == 0)
                                            {
                                                pV_698RWPara->Rd_OI[i].RdOI.CarryNum = V_TableNo;
                                                pV_698RWPara->Rd_OI[i].RdOI.DataType = 0;
                                            }
                                            else
                                            {
                                                pV_698RWPara->Rd_OI[i].RdOI.CarryNum = V_TableNo;
                                                pV_698RWPara->Rd_OI[i].RdOI.DataType = C_array;
                                            }
                                        }
                                        else
                                        {
                                            pV_698RWPara->Rd_OI[i].Rd_Result = SF_EventOADRead(pV_698RWPara->Rd_OI[i],&pV_DataBuf[V_DataOff+1], &V_OffsetTemp, 0, &V_TableNo);
                                            if(pV_698RWPara->Rd_OI[i].Rd_Result == C_OtherErr_DAR)
                                            {
                                                pV_698RWPara->ResponedNum++;
                                                continue;
                                            }

                                            if(V_TableNo == 0)
                                            {
                                                pV_698RWPara->Rd_OI[i].RdOI.CarryNum = V_TableNo;
                                                pV_698RWPara->Rd_OI[i].RdOI.DataType = 0;
                                            }
                                            else
                                            {
                                                pV_698RWPara->Rd_OI[i].RdOI.CarryNum = V_TableNo;
                                                pV_698RWPara->Rd_OI[i].RdOI.DataType = C_array;
                                            }

                                        }
                                        if(pV_698RWPara->Rd_OI[i].Rd_Result == C_OK)
                                        {
                                            if(V_OffsetTemp >= 256)
                                            {
                                                for(V_DeepLen = 0;V_DeepLen<V_OffsetTemp;V_DeepLen++)
                                                {
                                                    pV_DataBuf[V_DataOff+2+V_OffsetTemp-V_DeepLen] = pV_DataBuf[V_DataOff+V_OffsetTemp-V_DeepLen];
                                                }
                                                pV_DataBuf[V_DataOff+0] = 0x82;
                                                PF_Ushort16ToBuffer2_698(&pV_DataBuf[V_DataOff+1],&V_OffsetTemp);
                                                V_OffsetTemp += 3;
                                            }
                                            else if(V_OffsetTemp > 127)
                                            {
                                                for(V_DeepLen = 0;V_DeepLen<V_OffsetTemp;V_DeepLen++)
                                                {
                                                    pV_DataBuf[V_DataOff+1+V_OffsetTemp-V_DeepLen] = pV_DataBuf[V_DataOff+V_OffsetTemp-V_DeepLen];
                                                }
                                                pV_DataBuf[V_DataOff+0] = 0x81;
                                                pV_DataBuf[V_DataOff+1] = (uchar8)V_OffsetTemp;
                                                V_OffsetTemp += 2;
                                            }
                                            else
                                            {
                                                pV_DataBuf[V_DataOff] = (uchar8)V_OffsetTemp;
                                                V_OffsetTemp += 1;
                                            }
                                            if( ( V_OffsetTemp + V_DataOff + C_EnCodeMaxLen + pV_698RWPara->RWOI_Num * 4 ) <= C_Comm_Data_MaxLen_698 )
                                            {
                                                V_DataOff += V_OffsetTemp;
                                            }
                                            else
                                            {
                                                pV_698RWPara->Rd_OI[i].Rd_Result = C_MaxResponseLen_ERR;
                                            }
                                        }
                                    }
                                    V_BufRemainLen = 0;
                                }
                                else if(V_DataType == C_FixedTimes_Data)		/*��ȡ����¼��*/
                                {
                                    pV_698RWPara->Rd_OI[i].RdOI.DataType = C_long_unsigned;
                                    pV_DataBuf[V_DataOff] = 2;
                                    V_DataOff++;
                                    pV_DataBuf[V_DataOff] = 0;
                                    V_DataOff++;
                                    if((pV_698RWPara->Rd_OI[i].RdOI.OAD & 0xFFFFFF00) == 0x30260500)
                                    {
                                        pV_DataBuf[V_DataOff] = 2;
                                    }
                                    else
                                    {
                                        pV_DataBuf[V_DataOff] = pV_698RWPara->Rd_OI[i].RdOI.CarryNum;
                                    }
                                    V_DataOff++;
                                    V_BufRemainLen = 0;
                                }
                                else if(V_DataType == C_EventRecord_Data)   	/*��ȡ�¼���¼��*/
                                {
                                    pV_698RWPara->Rd_OI[i].Rd_Result = SF_GetAPDU_EventRead(&pV_698RWPara->Rd_OI[i], &pV_DataBuf[V_DataOff], &V_BufRemainLen,pV_698RWPara->ServiceFlag_Second);
                                }
                                else
                                {
                                    if((pV_698RWPara->Rd_OI[i].RdOI.OAD&0xFF000000) == 0x50000000)
                                    {
                                        pV_698RWPara->Rd_OI[i].Rd_Result = SF_GetAPDU_FreezeRead(&pV_698RWPara->Rd_OI[i], &pV_DataBuf[V_DataOff], &V_BufRemainLen,pV_698RWPara->ServiceFlag_Second);
                                        if(pV_698RWPara->Rd_OI[i].Rd_Result == C_MaxResponseLen_ERR)
                                        {
                                            pV_698RWPara->CurrentOADEnd =0x0F;	/*��OAD��һ�η����к���֡Ϊ0x0F,�ǵ�һ��FF*/
                                        }
									}
                                    else if(pV_698RWPara->Rd_OI[i].RdOI.OAD == CDrive_Report_State)		/*����������ϱ�״̬��*/
                                    {
                                        pV_DataBuf[V_DataOff] = pV_698RWPara->Rd_OI[i].RdOI.DataType;
                                        V_DataOff++;
										V_usDataLen = CLDrive_Report_State;
                                        switch(pV_698RWPara->ChannelNo)
                                        {
                                            case C_ReportChannel1:
                                            {
                                                V_ChannelTemp = GV_MeterStatus81;
                                            }break;
                                            case C_ReportChannel2:
                                            {
                                                V_ChannelTemp = GV_MeterStatus82;
                                            }break;
                                            case C_ReportChannel3:
                                            {
                                                V_ChannelTemp = GV_MeterStatus83;
                                            }break;

                                            default:
                                            {
                                                pV_698RWPara->Rd_OI[i].Rd_Result = C_ObjectNotExist_DAR;	/* ����δ���� */
                                                pV_698RWPara->ResponedNum++;
                                            } continue;
                                        }
                                        if( PF_Check_CRC_698( V_ChannelTemp, V_usDataLen + 2 ) == C_OK )
                                        {
                                            PF_CopyDataBytes_698(V_ChannelTemp,&pV_DataBuf[V_DataOff],V_usDataLen);
                                        }
                                        else
                                        {
                                            PF_CopyDataBytes_698(V_ZeroTemp,&pV_DataBuf[V_DataOff],V_usDataLen);
                                        }
                                        pV_698RWPara->Rd_OI[i].Rd_Result = C_OK;
                                        V_BufRemainLen = CLDrive_Report_State;
                                    }
                                    else if(pV_698RWPara->Rd_OI[i].RdOI.OAD == CUpTellChannel)        		/*������ϱ�ͨ��*/
                                    {
                                        pV_698RWPara->Rd_OI[i].Rd_Result = InF_Read_Data(CUpTellChannel, V_Temp, &V_ucLen, &V_usDataEncode);

                                        if( V_BufRemainLen >= (V_Temp[0] * 5 + 1) )
                                        {
                                            if(pV_698RWPara->Rd_OI[i].Rd_Result == C_OK)
                                            {
                                                pV_698RWPara->Rd_OI[i].RdOI.CarryNum = V_Temp[0];
                                                pV_DataBuf[V_DataOff] = V_Temp[0] * 5;
                                                V_DataOff++;
                                                for( k = 0; k < V_Temp[0]; k++)
                                                {
                                                    pV_DataBuf[V_DataOff] = C_OAD;
                                                    V_DataOff++;
                                                    PF_OneDataReversed (&V_Temp[1 + 4 * k], &pV_DataBuf[V_DataOff], 4);
                                                    V_DataOff += 4;
                                                }
                                            }
                                        }
                                        else
                                        {
                                            pV_698RWPara->Rd_OI[i].Rd_Result = C_MaxResponseLen_ERR;
                                        }
                                        V_BufRemainLen = 0;
                                    }
                                    else if( ( pV_698RWPara->Rd_OI[i].RdOI.OAD & 0xFFFFFFF0 ) == 0x30230A00 )	/*������޹���������ֱ�̵�����10*/
                                    {
                                       pV_698RWPara->Rd_OI[i].Rd_Result = SF_PrograReactivePowerState(pV_698RWPara->Rd_OI[i].RdOI.OAD, &pV_DataBuf[V_DataOff], &V_BufRemainLen);
                                    }
                                    else if( ( pV_698RWPara->Rd_OI[i].RdOI.OAD & 0xFFFFFFF0 ) == 0x44000300 )
                                    {
										V_OADTemp = pV_698RWPara->Rd_OI[i].RdOI.OAD;
                                        if(V_BufRemainLen < 46)												/*��������������*/
                                        {
                                            pV_698RWPara->Rd_OI[i].Rd_Result = C_MaxResponseLen_ERR;
                                        }
                                        else
                                        {
                                            if( ( (uchar8)pV_698RWPara->Rd_OI[i].RdOI.OAD ) == 0x00 )
                                            {
                                                pV_DataBuf[V_DataOff] = 46;
                                                V_DataOff++;
                                                for(V_Num = 0; V_Num < V_645DINum; V_Num++)
                                                {
                                                    V_ucLen = V_DIFor645->DataLen_645[V_Num];
                                                    V_OADTemp += 0x00000001;
                                                    if(V_OADTemp == CAppStaticTimeout)    					/*��̬��ʱʱ��*/
                                                    {
                                                        if(SV_Comm_Parse_Local.ClientAddrFlag == Termal_Address)	/*�ն˶���̬��ʱʱ��*/
                                                        {
                                                            V_OADTemp = CAppStaticTimeout_termal;
                                                        }
                                                    }
                                                    pV_698RWPara->Rd_OI[i].Rd_Result = InF_Read_Data(V_OADTemp,V_DataTemp, &V_ucLen, &V_usDataEncode);
                                                    if(pV_698RWPara->Rd_OI[i].Rd_Result == C_OK)
                                                    {
                                                        pV_DataBuf[V_DataOff] = V_DIFor645->DataType[V_Num];
                                                        V_DataOff++;
                                                        if(V_OADTemp == 0x44000306)
                                                        {
                                                            pV_DataBuf[V_DataOff] = 0x81;
                                                            V_DataOff++;
                                                        }
                                                        if(V_DIFor645->DataType[V_Num] == C_bit_string)
                                                        {
                                                            pV_DataBuf[V_DataOff] = V_DIFor645->DataLen_698[V_Num];
                                                            V_DataOff++;
                                                        }
                                                        PF_CopyDataBytes(V_DataTemp,&pV_DataBuf[V_DataOff],V_ucLen);
                                                        V_DataOff += V_ucLen;
                                                    }
                                                    else
                                                    {
                                                        break;
                                                    }
                                                }
                                            }
                                            else
                                            {
                                                V_ucLen = V_DIFor645->DataLen_645[0];
                                                pV_DataBuf[V_DataOff] = V_ucLen;
                                                V_DataOff++;
                                                if(V_OADTemp == CAppStaticTimeout)          					/*��̬��ʱʱ��*/
                                                {
                                                    if(SV_Comm_Parse_Local.ClientAddrFlag ==Termal_Address)		/*�ն˶���̬��ʱʱ��*/
                                                    {
                                                        V_OADTemp = CAppStaticTimeout_termal;
                                                    }
                                                }
                                                pV_698RWPara->Rd_OI[i].Rd_Result = InF_Read_Data(V_OADTemp, V_DataTemp, &V_ucLen, &V_usDataEncode);
                                                PF_CopyDataBytes(V_DataTemp, &pV_DataBuf[V_DataOff], V_ucLen);
                                                V_DataOff += V_ucLen;
                                            }
                                        }
                                        V_BufRemainLen = 0;
                                    }
                                    else
                                    {
                                        pV_698RWPara->Rd_OI[i].Rd_Result = SF_GetAPDU_Read(V_DIFor645,&V_645DINum,&pV_DataBuf[V_DataOff],&V_BufRemainLen,pV_698RWPara->Rd_OI[i].RdOI.DataType,C_Read_FlagNor);
                                    }
                                }
                            }
                            if(pV_698RWPara->Rd_OI[i].Rd_Result == C_OK)
                            {
                                pV_698RWPara->CurrentOADEnd = 0;    				/*��OAD�Ѿ����꣬����*/
                                if(pV_698RWPara->FrameNUM != 0)     				/*���һ֡*/
                                {
                                    if(i == (pV_698RWPara->RWOI_Num - 1))
                                    {
                                        pV_698RWPara->FrameNUM ++;					/*Ӧ�ò�֡���+1*/
                                        pV_698RWPara->EndFrame = C_LastFrameOK;     /*��֡��ĩ֡��־*/
                                        if(pV_698RWPara->CurrentOADEnd == 0xF0)     /*��������һ֡*/
                                        {
                                            pV_698RWPara->ResponedNum--;            /*����ͳһ������++*/
                                        }
                                    }
                                }

                                V_DataOff += V_BufRemainLen;
                            }
                            else if(pV_698RWPara->Rd_OI[i].Rd_Result == C_MaxResponseLen_ERR)
                            {
                                if(pV_698RWPara->CurrentOADEnd == 0x0F) 			/*��ǰ��ʶ���һ��û�ж�������*/
                                {
                                    pV_698RWPara->ResponedNum++;					/*�Ѿ�Ӧ�����1*/
                                }
                                pV_698RWPara->FrameNUM ++;	           				/*Ӧ�ò�֡���+1*/
                                pV_698RWPara->EndFrame = C_LastFrameErr;
                                V_DataOff += V_BufRemainLen;
                                pV_698RWPara->Rd_OI[i].Rd_Result =C_OK; 			/*��ֹ������*/
                                break;
                            }
                        }
                    }
                }
                pV_698RWPara->ResponedNum++;										/*�Ѿ�Ӧ�����1*/
            }
		}break;
		default:
		 break;
	}

	Comm_AppendMsg(CMsg_Txd);
}
/*******************************************************************************
����ԭ�ͣ�uchar8	JudgeMeterType(ulong32 V_ulOAD)
�����������жϱ�������Ƿ�֧�ָ�����
���������pV_645Frame				:���յ�������֡
�����������
���ز�����	C_OK֧��/C_Error��֧��
����λ�ã�
��    ע��	ע�⣬����ԷǷ���ʶ�벻�����жϡ��Ƿ���ʶ��
				������ͨ��ģ����������л�����жϵġ�
*******************************************************************************/
#define	CLen_TB_698OnlyLocalSupport		27
const	ushort16	TB_698OnlyLocalSupport[CLen_TB_698OnlyLocalSupport] =
	{0x201A, 0x201B, 0x201C, 0x202C, 0x202D, 0x2032, 0x202E, 0x3024, 0x3025, 0x3027,
	 0x3028, 0x3029, 0x400A, 0x400B, 0x400D, 0x4018, 0x4019, 0x401A, 0x401B, 0x401E, 0x401F, 0x4022,
	 0x5007, 0x500A, 0x500A, 0x500B, 0x5011};

uchar8	JudgeMeterType(ulong32 V_ulOAD)
{
	uchar8	i;
	ushort16 V_OI;

	V_OI = (ushort16)(V_ulOAD >> 16);
/*������*/
	/*�����ر��������֧�֣������������ܱ��ѿر�֧��*/
	if(C_Meter_Type == C_L_SmartMeter)
	{
		return(C_OK);
	}
	/*�ѿر�����ܱ�*/


	for( i = 0; i < CLen_TB_698OnlyLocalSupport; i++ )
	{/*ʣ����ȷ���Ƿ��Ϊ���ر�֧��*/
		if(V_OI == TB_698OnlyLocalSupport[i])
		{
			return(C_ObjectNotExist_DAR);
		}
	}
	return(C_OK);

}
/*******************************************************************************
����ԭ�ͣ�void Inf_Get_ApplianceF205(ulong32 V_OAD,uchar8 *P_DataBuf,uchar8 *V_Len)
������������ȡ��������豸�����
���������	OAD����ȡ���ݴ��buffer
�����������������ݴ��ͨ���շ�����
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
void Inf_Get_ApplianceF205(ulong32 V_OAD, uchar8 *P_DataBuf, uchar8 *V_Len)
{
    uchar8   V_ucOff = 0;
	ushort16 P_Data_Length = 0, V_usDataEncode;

    if( ( (uchar8)V_OAD ) ==0 )
    {
        P_DataBuf[V_ucOff] = C_structure;
        V_ucOff++;
        P_DataBuf[V_ucOff] = 4;
        V_ucOff++;
    }
    P_DataBuf[V_ucOff] = C_visible_string;
    V_ucOff++;
    P_DataBuf[V_ucOff] = 5;
    V_ucOff++;
    P_DataBuf[V_ucOff] = 82;		/*"R"*/
    V_ucOff++;
    P_DataBuf[V_ucOff] = 69;		/*"E"*/
    V_ucOff++;
    P_DataBuf[V_ucOff] = 76;		/*"L"*/
    V_ucOff++;
    P_DataBuf[V_ucOff] = 65;		/*"A"*/
    V_ucOff++;
    P_DataBuf[V_ucOff] = 89;		/*"Y"*/
    V_ucOff++;
    P_DataBuf[V_ucOff] = C_enum;
    V_ucOff++;
    P_DataBuf[V_ucOff] = InF_RelayOpenStatus_698();
    V_ucOff++;
    P_DataBuf[V_ucOff] = C_enum;
    V_ucOff++;
    P_Data_Length = CLMeter_Work_Char1;
    InF_Read_Data(CMeter_Work_Char1, &P_DataBuf[V_ucOff], &P_Data_Length, &V_usDataEncode);		/*��ȡ�̵���״̬ */
    P_DataBuf[V_ucOff] = (P_DataBuf[V_ucOff] & 0x01);
    V_ucOff++;
    P_DataBuf[V_ucOff] = C_enum;
    V_ucOff++;
	if(C_Meter_Type == C_SmartMeter)
    {
        P_DataBuf[V_ucOff] = 1;
    }
    else
    {
        P_DataBuf[V_ucOff] = 0;
    }
    V_ucOff++;
    *V_Len = V_ucOff;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_GetAPDU_ApplianceInOutRead(RdOI_Para_T V_OAD,uchar8 *P_DataBuf,uchar8 V_ucOff,ushort16 *P_DataOff)
������������ȡ��������豸�����
���������	OAD����ȡ���ݴ��buffer
�����������������ݴ��ͨ���շ�����
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_GetAPDU_ApplianceInOutRead(RdOI_Para_T V_OAD, uchar8 *P_DataBuf, uchar8 V_ucOff, ushort16 *P_DataOff)
{
	uchar8 V_OB, V_DataNo, V_ucRetrun = 0, V_Len = 0;
	uchar8 V_ucoffLen = 0;

    V_ucOff=1;
	V_OB = (uchar8)(V_OAD.RdOI.OAD >> 16);
	V_DataNo = (uchar8)(V_OAD.RdOI.OAD);
	if(V_OB == 0x01)			/*485*/
	{
		if(V_DataNo == 0)
		{
			P_DataBuf[V_ucOff] = C_structure;
			V_ucOff++;
			P_DataBuf[V_ucOff] = 3;
			V_ucOff++;
			V_ucoffLen = SF_GetAPDU_BpsRead(0xF2010201, &P_DataBuf[V_ucOff]);
			V_ucOff = V_ucOff + V_ucoffLen;
			P_DataBuf[V_ucOff] = C_structure;
			V_ucOff++;
			P_DataBuf[V_ucOff] = 3;
			V_ucOff++;
			V_ucoffLen = SF_GetAPDU_BpsRead(0xF2010202, &P_DataBuf[V_ucOff]);
			V_ucOff = V_ucOff + V_ucoffLen;
		}
		else
		{
			V_ucoffLen = SF_GetAPDU_BpsRead(V_OAD.RdOI.OAD, &P_DataBuf[V_ucOff]);
			V_ucOff = V_ucOff + V_ucoffLen;
		}
	}
	else if(V_OB == 0x02)		/*����*/
	{
        if(V_DataNo == 0)
		{
			P_DataBuf[V_ucOff] = C_structure;
			V_ucOff++;
			P_DataBuf[V_ucOff] = 2;
			V_ucOff++;
        }
		V_ucoffLen = SF_GetAPDU_BpsRead(V_OAD.RdOI.OAD,&P_DataBuf[V_ucOff]);
        V_ucOff = V_ucOff+V_ucoffLen;
		V_ucOff=V_ucOff-2;
	}
	else if(V_OB == 0x05)		/*�̵������*/
	{
        Inf_Get_ApplianceF205(V_OAD.RdOI.OAD, &P_DataBuf[V_ucOff], &V_Len);
        V_ucOff = V_ucOff+V_Len;
	}
	else if(V_OB == 0x06)		/*�澯���*/
	{
        if(V_DataNo == 0)
        {
            P_DataBuf[V_ucOff] = C_enum;
            V_ucOff++;
        }
		P_DataBuf[V_ucOff] = InF_AlarmState();
		V_ucOff++;
	}
	else if(V_OB == 0x07)		/*�๦�ܶ���*/
	{
      if(V_DataNo==0)
      {
        P_DataBuf[V_ucOff]=C_enum;
        V_ucOff++;
      }
		P_DataBuf[V_ucOff]= InF_ModifyFunctionStatus();
        V_ucOff++;
	}
	else if(V_OB == 0x09)		/*�ز�*/
	{
        if(V_DataNo == 0)
		{
			P_DataBuf[V_ucOff] = C_structure;
			V_ucOff++;
			P_DataBuf[V_ucOff] = 3;
			V_ucOff++;
        }
		V_ucoffLen = SF_GetAPDU_BpsRead(V_OAD.RdOI.OAD, &P_DataBuf[V_ucOff]);
        V_ucOff = V_ucOff + V_ucoffLen;
		V_ucOff = V_ucOff - 2;
	}
	else
	{
		V_ucRetrun = C_ObjectUndefine_DAR;
	}
	P_DataBuf[0] = V_ucOff - 1;
	*P_DataOff = V_ucOff;

	return V_ucRetrun;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_GetAPDU_DISPRead(RdOI_Para_T V_OAD,uchar8 *P_DataBuf,ushort16 V_ucOff,ushort16 *P_DataOff)
����������
���������OAD����ȡ���ݴ��buffer
�����������������ݴ��ͨ���շ�����
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_GetAPDU_DISPRead(RdOI_Para_T V_OAD, uchar8 *P_DataBuf, ushort16 V_ucOff, ushort16 *P_DataOff)
{
	uchar8 V_OIB, V_DataNo, V_ucRetrun = C_OtherErr_DAR;
    ulong32 V_ulDispNumDI, V_ulDispDI, V_ulDispOAD;
	uchar8	V_ucDispNum;
	uchar8	i;
	uchar8	V_uc698OI[10];
    ushort16 PDataLength, j, V_usDataEncode;

    V_ucOff = 1;
	V_OIB = (uchar8)(V_OAD.RdOI.OAD >> 16);
	V_DataNo = (uchar8)(V_OAD.RdOI.OAD);

	if(V_OIB == 0)			/*ѭ��*/
	{
		V_ulDispNumDI = CAuto_Dis_Screen_Num;
		V_ulDispDI = CAuto_Dis_1ScreenCode;
	}
	else					/*����*/
	{
		V_ulDispNumDI = CKey_CycDis_Screen_Num;
		V_ulDispDI = CKey_Dis_1ScreenCode;
	}
	PDataLength = 1;
	InF_Read_Data(V_ulDispNumDI, &V_ucDispNum, &PDataLength, &V_usDataEncode);
	if( ( V_ucDispNum == 0 ) || ( V_ucDispNum > 99 ) )
	{
		V_ucDispNum = 1;
	}
	if(V_DataNo != 0x00)
	{
		V_ucDispNum = 1;
		V_ulDispDI = V_OAD.RdOI.OAD;
	}

	for( i = 0; i < V_ucDispNum; i++ )
	{
		V_ulDispOAD = V_ulDispDI  + 0x00000001 * i;
		PDataLength = CLKey_Dis_1ScreenCode;
		if( InF_Read_Data( V_ulDispOAD, V_uc698OI, &PDataLength, &V_usDataEncode ) == C_OK )
		{
			if(V_DataNo == 0)	/*���಻��Ҫ����*/
			{
				if( *P_DataOff < ( V_ucOff + 2 ) )
				{
					*P_DataOff = 0;
					return C_MaxResponseLen_ERR;
				}
				P_DataBuf[V_ucOff] = C_structure;
				V_ucOff++;
				P_DataBuf[V_ucOff] = 2;
				V_ucOff++;
			}
			if( *P_DataOff < ( V_ucOff + 1 ) )
			{
				*P_DataOff = 0;
				return C_MaxResponseLen_ERR;
			}
			P_DataBuf[V_ucOff] = 0x5B;
			V_ucOff++;

			if( ( V_uc698OI[4] == 0xFF ) && ( V_uc698OI[5] == 0xFF )
			 && ( V_uc698OI[6] == 0xFF ) && ( V_uc698OI[7] == 0xFF ) )
			{
				if( *P_DataOff < ( V_ucOff + 7 ) )
				{
					*P_DataOff = 0;
					return C_MaxResponseLen_ERR;
				}
				P_DataBuf[V_ucOff] = 0x00;
				V_ucOff++;
				P_DataBuf[V_ucOff] = V_uc698OI[3];
				V_ucOff++;
				P_DataBuf[V_ucOff] = V_uc698OI[2];
				V_ucOff++;
				P_DataBuf[V_ucOff] = V_uc698OI[1];
				V_ucOff++;
				P_DataBuf[V_ucOff] = V_uc698OI[0];
				V_ucOff++;
				P_DataBuf[V_ucOff] = 0x11;
				V_ucOff++;
				P_DataBuf[V_ucOff] = V_uc698OI[8];
				V_ucOff++;
				V_ucRetrun = C_OK_DAR;
			}
			else
			{
				if( *P_DataOff < ( V_ucOff + 12 ) )
				{
					*P_DataOff = 0;
					return C_MaxResponseLen_ERR;
				}
				P_DataBuf[V_ucOff] = 0x01;
				V_ucOff++;
				P_DataBuf[V_ucOff] = V_uc698OI[3];
				V_ucOff++;
				P_DataBuf[V_ucOff] = V_uc698OI[2];
				V_ucOff++;
				P_DataBuf[V_ucOff] = V_uc698OI[1];
				V_ucOff++;
				P_DataBuf[V_ucOff] = V_uc698OI[0];
				V_ucOff++;
				P_DataBuf[V_ucOff] = 0x01;
				V_ucOff++;
				P_DataBuf[V_ucOff] = V_uc698OI[7];
				V_ucOff++;
				P_DataBuf[V_ucOff] = V_uc698OI[6];
				V_ucOff++;
				P_DataBuf[V_ucOff] = V_uc698OI[5];
				V_ucOff++;
				P_DataBuf[V_ucOff] = V_uc698OI[4];
				V_ucOff++;
				P_DataBuf[V_ucOff] = 0x11;
				V_ucOff++;
				P_DataBuf[V_ucOff] = V_uc698OI[8];
				V_ucOff++;
				V_ucRetrun = C_OK_DAR;

			}

		}
		else
		{
			if( *P_DataOff < ( V_ucOff + 1 ) )
			{
				*P_DataOff = 0;
				return C_MaxResponseLen_ERR;
			}
			P_DataBuf[V_ucOff] = C_NULL;
			V_ucOff++;
		}

	}

	if(V_ucOff >= 256)
	{
		if( *P_DataOff < ( V_ucOff + 2 ) )
		{
			*P_DataOff = 0;
			return C_MaxResponseLen_ERR;
		}
		for( j = 0; j < V_ucOff; j++ )
		{
			P_DataBuf[V_ucOff - j + 1] = P_DataBuf[V_ucOff - j - 1];
		}
		P_DataBuf[2] = (uchar8)(V_ucOff - 1);
		P_DataBuf[1] = (uchar8)((V_ucOff - 1) >> 8);
		P_DataBuf[0] = 0x82;
		V_ucOff += 2;
	}
	else if(V_ucOff > 127)
	{
		if(*P_DataOff < (V_ucOff + 1))
		{
			*P_DataOff = 0;
			return C_MaxResponseLen_ERR;
		}
		for( j = 0; j < V_ucOff; j++ )
		{
			P_DataBuf[V_ucOff - j] = P_DataBuf[V_ucOff - j - 1];
		}
		P_DataBuf[1] = (uchar8)(V_ucOff - 1);
		P_DataBuf[0] = 0x81;
		V_ucOff += 1;
	}
	else
	{
		P_DataBuf[0] = (uchar8)(V_ucOff - 1);
	}
	*P_DataOff = V_ucOff;
	return V_ucRetrun;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_GetAPDU_HolidyRead(RdOI_Para_T *V_OAD,uchar8 *P_DataBuf,ushort16 V_ucOff,uchar8 V_DINum,ushort16 *P_DataOff)
����������
���������OAD����ȡ���ݴ��buffer
�����������������ݴ��ͨ���շ�����
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_GetAPDU_HolidyRead(RdOI_Para_T *V_OAD, uchar8 *P_DataBuf, ushort16 V_ucOff, uchar8 V_DINum, ushort16 *P_DataOff)
{
	uchar8 V_DataOff, V_ucRetrun = 0;
    ulong32 V_ulDI, V_ul645DI;
	uchar8	k, m = 0;
	uchar8	V_ucData[10] = {0x00};
	ushort16 PDataLength = 6, V_uc698Len, j, V_usDataEncode;

	memset(V_ucData, 0xFF, 10);
	V_DataOff = (uchar8)(V_OAD->RdOI.OAD);
	V_ucOff = 1;
	if(V_DataOff == 0)
	{
		V_ulDI = 0x40110201;
		k = V_OAD->RdOI.CurrentFrameNum;			/*��һ�εĽڼ������*/

		for( ; k < V_DINum; k++ )
		{
			if( ( V_ucOff + 10 ) < *P_DataOff )
			{
				m++;
				V_ul645DI = V_ulDI + 0x00000001 * k;
				InF_Read_Data(V_ul645DI, V_ucData, &PDataLength, &V_usDataEncode);
				P_DataBuf[V_ucOff] = C_structure;
				V_ucOff++;
				P_DataBuf[V_ucOff] = 2;
				V_ucOff++;
				P_DataBuf[V_ucOff] = C_date;

				V_uc698Len = SF_DataExchangeTo698_BasicData(&P_DataBuf[V_ucOff], &V_ucData[0], CL_date, CL_date);
				V_ucOff += V_uc698Len;
				V_ucOff ++;
				P_DataBuf[V_ucOff] = C_unsigned;
				V_ucOff ++;
				P_DataBuf[V_ucOff] = V_ucData[CL_date];
				V_ucOff++;
			}
			else
			{
				V_OAD->RdOI.CurrentFrameNum = k;	/*������һ�εĽڼ������*/
				V_OAD->RdOI.CarryNum = m;
			    break;
            }

		}
	}
	else
	{
		V_ul645DI = V_OAD->RdOI.OAD;
		InF_Read_Data(V_ul645DI, V_ucData, &PDataLength, &V_usDataEncode);

		P_DataBuf[V_ucOff] = C_date;

		V_uc698Len = SF_DataExchangeTo698_BasicData(&P_DataBuf[V_ucOff], &V_ucData[0], CL_date, CL_date);
		V_ucOff += V_uc698Len;
		V_ucOff ++;
		P_DataBuf[V_ucOff] = C_unsigned;
		V_ucOff ++;
		P_DataBuf[V_ucOff] = V_ucData[CL_date];
		V_ucOff++;

	}

	if(V_ucOff >= 256)
	{
		for( j = 0; j < V_ucOff; j++ )
		{
			P_DataBuf[V_ucOff - j + 1] = P_DataBuf[V_ucOff - j - 1];
		}
		P_DataBuf[2] = (uchar8)(V_ucOff - 1);
		P_DataBuf[1] = (uchar8)( ( V_ucOff - 1) >> 8 );
		P_DataBuf[0] = 0x82;
		V_ucOff += 2;
	}
	else if(V_ucOff > 127)
	{
		for( j = 0; j < V_ucOff; j++ )
		{
			P_DataBuf[V_ucOff - j] = P_DataBuf[V_ucOff - j - 1];
		}
		P_DataBuf[1] = (uchar8)(V_ucOff - 1);
		P_DataBuf[0] = 0x81;
		V_ucOff += 1;
	}
	else
	{
		P_DataBuf[0] = (uchar8)(V_ucOff - 1);
	}
	*P_DataOff = V_ucOff;
	return V_ucRetrun;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_GetAPDU_BpsRead(ulong32 V_OAD,uchar8 *P_DataBuf)
������������ȡ��������豸�����
���������	OAD����ȡ���ݴ��buffer
�����������������ݴ��ͨ���շ�����
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_GetAPDU_BpsRead(ulong32 V_OAD, uchar8 *P_DataBuf)
{
	ushort16	V_ucDataLen = CLOne485_Baud, V_usDataEncode;
	uchar8 V_ucOff = 0;
	uchar8 i, k = 0;
	ulong32 V_OADTemp;
    ulong64 V_ASCIITemp = 0;

	P_DataBuf[V_ucOff] = C_visible_string;
	V_ucOff++;
	V_OADTemp = V_OAD;

    switch (V_OADTemp)
	{
        case COne485_Baud:
            V_ASCIITemp = 0x313538345352;
            k = 6;
            break;
        case CTwo485_Baud:
            V_ASCIITemp = 0x323538345352;
            k = 6;
            break;
        case CMod_InFr_Baud:
            V_ASCIITemp = 0x4152464E49;
            k = 5;
            break;
        case CModular_Baud:
            V_ASCIITemp = 0;
            k = 3;
            break;
        case 0xF2020200:
            V_ASCIITemp = 0x4152464E49;
            k = 5;
            break;
        case 0xF2090200:
            V_ASCIITemp = 0;
            k = 1;
            break;
        default:
            V_ASCIITemp = 0x313538345352;
            k = 6;
            break;
	}
	P_DataBuf[V_ucOff] = k;
	V_ucOff++;
    for( i = 0; i < k; i++ )
	{
        if( ( V_ASCIITemp >> ( i * 8 ) ) == 0x20 )
        {
            break;
		}
        P_DataBuf[V_ucOff] = V_ASCIITemp >> ( i * 8 );
		V_ucOff++;
	}
	P_DataBuf[V_ucOff] = 0x5F;
	V_ucOff++;
	if( V_OAD == 0xF2010201 )
	{
		InF_Read_Data(COne485_Baud, &P_DataBuf[V_ucOff], &V_ucDataLen, &V_usDataEncode);
		V_ucOff += V_ucDataLen;
	}
	else if( V_OAD == 0xF2010202 )
	{
		InF_Read_Data(CTwo485_Baud, &P_DataBuf[V_ucOff], &V_ucDataLen, &V_usDataEncode);
		V_ucOff += V_ucDataLen;
	}
	else if( ( V_OAD == 0xF2020200 ) || ( V_OAD == 0xF2020201 ) )
	{
		P_DataBuf[V_ucOff] = 2;
		V_ucOff++;
		P_DataBuf[V_ucOff] = 2;
		V_ucOff++;
		P_DataBuf[V_ucOff] = 8;
		V_ucOff++;
		P_DataBuf[V_ucOff] = 1;
		V_ucOff++;
		P_DataBuf[V_ucOff] = 0;
		V_ucOff++;
	}
	else if( ( V_OAD == 0xF2090200 ) || ( V_OAD == 0xF2090201 ) )
	{
		InF_Read_Data(CModular_Baud, &P_DataBuf[V_ucOff], &V_ucDataLen, &V_usDataEncode);
		V_ucOff += V_ucDataLen;
		P_DataBuf[V_ucOff] = C_NULL;
		V_ucOff++;
	}
	P_DataBuf[V_ucOff] = C_enum;
	V_ucOff++;
	P_DataBuf[V_ucOff] = 0;
	V_ucOff++;
	return V_ucOff;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_CombDataTo645Type_W(uchar8 *P_698Data,Str_Comm_645 *pV_645Frame,uchar8 V_Len_645)
��������������645��ʽ��֯����
���������Str_Comm_698_RW�ж�Ӧ��ȡ���ݶ���OI���������͵�
���������pV_698RWParaдOI�����ý�������óɹ�Ϊ0������ʧ��������Ӧ������ʧ��ԭ��
���ز����������Ƿ���ȷ��C_OK��ʾ��ȡ�ɹ���������ʾ�������
����λ�ã�
��    ע��
*******************************************************************************/
void SF_CombDataTo645Type_W(uchar8 *P_698Data, Str_Comm_645 *pV_645Frame, uchar8 V_Len_645)
{
	/*L*/
	pV_645Frame->DataLen = CLen_DI+CLen_OpCode+CLen_CommPW +V_Len_645;
	/*DI*/
	PF_Ulong32ToBuffer4(&pV_645Frame->Data[CDI_O_V_645],&(pV_645Frame->DI),4);
	/*���� д����ʱ���ж�����  ���벿�ֲ���ֵ*/

	/*�����ߴ���645��ȡʱȫ����ֵFF�����ø�ֵ lzy20210930*/

	/*��������*/
    PF_CopyDataBytes(P_698Data,&(pV_645Frame->Data[C_Data_OFS_14]),V_Len_645);

    /*ȥ����������ֵ��������ֻ�������ݸ�ֵ�����жϺϷ���*/
}
/*******************************************************************************
����ԭ�ͣ�void SF_698SetLCDPara_Deal645(Str_Comm_645 *pV_645Frame)
����������д698LCD����ͬ��645�������������1
���������*pV_645Frame:���յ�������֡
�����������
���ز����� ��
����λ�ã�698д
��    ע��LCD�������������������д�͵���д
*******************************************************************************/
void SF_698SetLCDPara_Deal645(Str_Comm_645 *pV_645Frame)
{
    ushort16 V_ucMeter_Work_Len = CLMeter_Work_Char1, V_usDataEncode;
    uchar8   V_ucMeter_Work_Type = 0, V_ucReturn;

    if(pV_645Frame->DI == C1And2Display)
    {
        V_ucReturn = InF_Read_Data(CMeter_Work_Char1_645, &V_ucMeter_Work_Type, &V_ucMeter_Work_Len, &V_usDataEncode);	/*��������*/
        if(V_ucReturn != C_OK)
        {
            V_ucMeter_Work_Type = 0;
        }
        V_ucMeter_Work_Type &= 0xFD;
        V_ucMeter_Work_Type |= (pV_645Frame->Data[CData_14O_V_645] << 1);
        InF_Write_Data(C_Msg_Communication, CMeter_Work_Char1_645, &V_ucMeter_Work_Type, CLMeter_Work_Char1_645, C_W_SafeFlag);
    }
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_SetParm(Str_Comm_645 *pV_645Frame, ulong32 V_ulLastDI, ulong32 V_ulNextDI, uchar8 V_WriteEventFlag,
			ulong32 V_ulProgOAD, uchar8 OperationFlag)
����������ͨ��698 set����(��̼�¼����������¼�������)
���������pV_645Frame				:���յ�������֡
�����������
���ز��������ô�������
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_SetParm(Str_Comm_645 *pV_645Frame, ulong32 V_ulLastDI, ulong32 V_ulNextDI, uchar8 V_WriteEventFlag, ulong32 V_ulProgOAD, uchar8 OperationFlag)
{
	uchar8 V_ReturnData = C_OK;
	uchar8 *pData, DataLen, V_ucI, V_ucBuff[4];
    uchar8 V_uci, V_ucSet645ReportModeFlag = C_NoNeedSet645ReportMode;

	ulong32 ExtMsgType, DestMsgAddress, V_CommMsgNo;
	Str_WrParmTable WrParmTable;

	if(OperationFlag == C_SetUp)  /*����һ����������ⲻ����ͨ��set�������ã���Ҫaction ESAM��ִ��*/
	{
		if(InF_JudgeIJTimer() != C_OK)
		{
			switch( ( pV_645Frame->DI ) & 0xFFFFFF00 )
			{
				case    CCustomer_Num:          /*�ͻ����*/
				case	CMeter_Num:             /*���*/
				case	CRatio_Curr_Tran:       /*���������*/
				case	CRatio_Vol_Tran:        /*���������*/
				case	0x401E0200:             /*�������*/
				case	CChange_Rate:           /*���׷��ʵ���л�ʱ��*/
				case	CChange_Ladder:         /*���׽��ݵ���л�ʱ��*/
				case	CCurrent_RateFF_Price:  /*��ǰ�׷��ʱ�*/
				case	CBackUp_RateFF_Price:   /*�����׷��ʱ�*/
				case	CCurrent_Ladder_Table:  /*��ǰ�׽��ݱ�*/
				case	CBackUp_Ladder_Table:   /*�����׽��ݱ�*/
				{
					return(C_Unauthorized_DAR);
				}

				default:
				break;					        /*ע��������break������һ���ж�*/
			}
		}
	}
	if(InF_JudgeIJTimer() != C_OK)
	{
		switch( ( pV_645Frame->DI ) & 0xFFFFFF00 )
		{
			case CRated_Vol:            		/*���ѹ*/
			case CRated_Curr:           		/*�����*/
			case CMax_Curr:             		/*������*/
 			case CMin_Curr:			    		/*��С����*/
            case CTurn_Curr:					/*ת�۵���*/
			case CActive_Accur_Deg:				/*�й�׼ȷ�ȵȼ�*/
			case CReactive_Accur_Deg:			/*�޹�׼ȷ�ȵȼ�*/
			case CMeter_Ac_Const:				/*����й�����*/
			case CMeter_Re_Const:				/*������޹�����*/
			case CMeter_Model:					/*����ͺ�*/
			case CProd_Date:					/*��������*/
			case CProt_Version_Num:	   			/*Э��汾��*/
			case CSoftw_Record_Number:  		/*���������*/
			case CLine_Num:             		/*������Ԫ��*/
			case CPluse_Wide:           		/*������*/
			case 0x43000500:            		/*���豸�б�*/
			case CMeter_CommPro:		 		/*֧�ֹ�Լ�б�*/
			case 0x43000300:            		/*�汾��Ϣ�����̴��룬����汾�ţ�����汾���ڣ�Ӳ���汾�ţ�Ӳ���汾���ڣ�������չ��Ϣ��*/
			case 0x44000300:            		/*Ӧ���ﾳ��Ϣ��Э��汾��Ϣ��������APDU�ߴ磬�����APDU�ߴ磬���ɴ���APDU�ߴ磬Э��һ���Կ� ������һ���Կ� ����̬��ʱʱ�䣩*/
			case CEquipmentDis:
			case CFirst_TZone_Data:      		/*��ǰ��ʱ����*/
			case 0x40160200:            		/*��ǰ��ʱ�α�*/
			case CInset_Card_State:      		/*�忨״̬��*/
			{
				return(C_RWForbid_DAR);
			}

			default:
			break;								/*ע��������break������һ���ж�*/
		}
	}

	/*���*/
	V_ReturnData = LookFor_WrParmTable(pV_645Frame, &WrParmTable);
	if( V_ReturnData != C_OK )
	{	/*��ʶ�벻�ԣ�Ӧ����������*/
		return C_ObjectNotExist_DAR;
	}

	/*���ȡ����ݺϷ����ж�*/
	V_ReturnData = Is_SetParmData_Ok(pV_645Frame, &WrParmTable);
	if(V_ReturnData !=C_OK)
	{
		return V_ReturnData;
	}

	/*�����ܱ���¼��������Ҫע��:
      ���ǵ�pV_645Frame->DI�б仯�������û������б�ʶ��*/
    if(V_WriteEventFlag == C_NeedWriteEventRecord)
    {
        PF_Ulong32ToBuffer4(V_ucBuff, &V_ulProgOAD, 4);
        INF_Append_ProgRecordDI(&pV_645Frame->Data[COpcode_14O_V_645], V_ucBuff, &SV_Comm_Parse.ProgRecord, OperationFlag);
    }

/*�ж��Ƿ��Ǿ��ж�������¼��ı����Ŀ�����������⶯������Ŀ
    �ǣ�����ö�Ӧ�Ĵ�����
    ����ֱ��д���ݲ�*/
	SV_Comm_Parse_Local.SafeControlFlag = SV_Comm_Parse_Local.SafeControlFlag | C_W_SafeFlag_3;
	pData = &pV_645Frame->Data[CData_14O_V_645];
	DataLen = pV_645Frame->DataLen - (CLen_DI + CLen_OpCode + CLen_CommPW);
    if(pV_645Frame->DI==CDrive_Report_Mode)
    {
       SF_DriveReportSet_Change(C_ProtocolType_698, pData, DataLen);
    }
    if( pV_645Frame->DI == C1And2Display )
    {
        SF_698SetLCDPara_Deal645(pV_645Frame);
    }

    if(pV_645Frame->Data[3] == 0x30)
    {
        for(V_uci = 0; V_uci < C_Event_OIBTableLen; V_uci++)
        {
            if(pV_645Frame->Data[2] == Event_OIBTable[V_uci].OIB)
            {
                if(Event_OIBTable[V_uci].TypeClass == C_SplitPhaseEvent_Class)
                {
                    if(pV_645Frame->Data[1] == 0x0B) 	 /*��24������11�ϱ���ʶ*/
                    {
                        V_ucSet645ReportModeFlag = C_NeedSet645ReportMode;
                    }
                }
                else if(Event_OIBTable[V_uci].TypeClass == C_Event_Class)
                {
                    if(pV_645Frame->Data[1] == 0x08)  	/*��7������8�ϱ���ʶ*/
                    {
                        V_ucSet645ReportModeFlag = C_NeedSet645ReportMode;
                    }
                }
                else
                {
                    ; 									/*����Ҫдģʽ�֣�ĿǰҲ������*/
                }
                break;
            }
        }
        if(V_ucSet645ReportModeFlag == C_NeedSet645ReportMode)
        {
            V_ucBuff[0] = pV_645Frame->Data[2];
            V_ucBuff[1] = *pData;
            SF_DriveReportSet_Change(C_ProtocolType_698, V_ucBuff, DataLen+CL_OI2Len);
        }   /*��������Ҫд*/
    }
	switch(WrParmTable.Method & C_HaveIPEventType)
	{
		case C_HaveIPEvent_GPRSSignal:					/*����GPRS�ź�*/
        {
			/*���Ѹ�λGPRS�źű�־*/
			SV_Comm_Parse.RstModuleParm.IsSet_GPRS_Signal = C_Flag_Ok;
			SetGPRSSignal( &pV_645Frame->Data[CData_14O_V_645] );
        }break;

		case C_HaveIPEvent_ProgParm:					/*�ж�������¼�*/
		{
			HaveIPEvent(pV_645Frame);
		}break;

		case C_HaveIPEvent_Invalid:						/*�����⴦��ֱ��д���ݲ�*/
		{
			V_ReturnData = InF_Write_Data(C_Msg_Communication,   pV_645Frame->DI, pData, (ushort16)DataLen, SV_Comm_Parse_Local.SafeControlFlag);
		}break;

		default:
			return C_OtherErr;
	}
/*����������Ϣ����?    �У��򴥷���Ӧ����Ϣ*/
	ExtMsgType = WrParmTable.Method & C_ExtMsgType;
	DestMsgAddress = (WrParmTable.Method & C_ExtMsgDestAddress);
	switch(ExtMsgType)
	{  /*�����ⲿ��Ϣ*/
		case	C_ExtMsgType_Invalid:					/*���ⲿ��Ϣ��Ҫ����*/
			break;

		case	C_ExtMsg_ReWorkTime:					/*ʱ�Ӹ�����Ϣ����*/
			SetRTC_AppendMsg(DestMsgAddress, pV_645Frame);
		break;

		case	C_ExtMsg_ReSettle_Day1:					/*���õ�1������*/
			ReSettle_Day1_AppendMsg(DestMsgAddress, pV_645Frame);
		break;

		case	C_ExtMsg_SetKeyNum:						/*������Կ��������������Կ���¼����Ϣ*/
			Comm_A_MsgToDispatchQueue_UpKeyR(PT_CMsg_UpdKey_Rv_PWOn);
		break;

		/*������Ϣ��������ͳһ�����������������ģ���ʶ��ΪPt_ParaMetersChange*/
		/*���������ExtMsgType����Ŀ�ĵ�ַ����DestMsgAddress��*/
		case	C_ExtMsg_ReMultiRatesParm:				/*ʱ�η������������*/
			SetParm_14_AppendMsg(C_ReMultiRatesParm, DestMsgAddress);
		break;

		case	C_ExtMsg_ReDemand_Cycle:				/*�������ڸ���*/
			SetParm_14_AppendMsg(C_ReDemand_Cycle, DestMsgAddress);
		break;

		case	C_ExtMsg_ReLocalWarningPara:			/*���ñ��ر�������*/
			SetParm_14_AppendMsg(C_ReworkWarningPara, DestMsgAddress);
		break;

		default:
		break;											/*�������ܵ�����.*/
	}

	/*�����ڲ���Ϣ��־�����ж�Ӧ����Ϣ����*/
	for( V_ucI = 0; V_ucI < C_MessageMaxNum; V_ucI++ )
	{
		V_CommMsgNo = Comm_FetchMsg();
		if(V_CommMsgNo == CMsg_Null)
		{
			break;
		}
		switch(V_CommMsgNo)
		{
			case CMsg_ProgTimePeriod:		    		/*ʱ�α����Ϣ*/
				Have_IPEvent_Prog_698(CProgPT_Note_1, CProgPT_Degree, pV_645Frame);
            break;

			case CMsg_ProgSeason:			    		/*ʱ������*/
				Have_IPEvent_Prog_698(CProgTZ_Note_1, CProgTZ_Degree, pV_645Frame);
			break;

			case CMsg_ProgWeekRest:	            		/*�����ձ��*/
				Have_IPEvent_Prog_698(CProgWRe_Note_1, CProgWRe_Degree, pV_645Frame);
				break;

			case CMsg_ProgHoliday:			    		/*�������ձ��*/
				Have_IPEvent_Prog_698(CProgHol_Note_1, CProgHol_Degree, pV_645Frame);
			break;

			case CMsg_ProgCombPState:		    		/*�й����״̬�ֱ��*/
				Have_IPEvent_Prog_698(CProgAcC_Note_1, CProgAcC_Degree, pV_645Frame);
			break;

			case CMsg_ProgCombQ1State:	        		/*�޹����״̬��1���*/
				Have_IPEvent_Prog_698(CProgReC_Note_1, CProgReC_Degree,pV_645Frame);
			break;

			case CMsg_ProgCombQ2State:	        		/*�޹����״̬��2���*/
				Have_IPEvent_Prog_698(CProgReC_Note_1, CProgReC_Degree,pV_645Frame);
			break;

			case CMsg_ProgSetADate:		        		/*������1-3���*/
            {
                if(V_ulLastDI == 0xFFFFFFFF)   			/*����д��ֻ��¼һ���¼���¼*/
				{
				    Have_IPEvent_Prog_698(CProgSettD_Note_1, CProgSettD_Degree, pV_645Frame);
				}
				else
				{
					V_ReturnData = InF_Write_Data(C_Msg_Communication, pV_645Frame->DI, pData, (ushort16)DataLen, SV_Comm_Parse_Local.SafeControlFlag);
				}
            }break;

			case CMsg_ProgDateTime:		        		/*Уʱ��¼.Уʱ��¼�������⣬��˲���ר�÷���*/
				Have_IPEvent_Prog_698(CAdjTime_Note_1, CAdjTime_Degree, pV_645Frame);
			break;

			case CMsg_ProgStepTariff:	        		/*���ݱ��̼�¼��ͨ��ֻ�������ױ�̼�¼����ǰ�׽���ֻ�п�����������*/
				Have_IPEvent_Prog_698(CProgLad_Note_1, CProgLad_Degree, pV_645Frame);
			break;

			case CMsg_ProgRate:							/*���ʵ�۱�̼�¼��ͨ��ֻ�������ף���ǰ�׷��ʵ��ֻ�п�����������*/
				Have_IPEvent_Prog_698(CProgTPara_Note_1, CProgTPara_Degree, pV_645Frame);
			break;

			default:
			break;
		}
	}
	return V_ReturnData;
}
/*******************************************************************************
����ԭ��:void SF_Write_BroadTimeAbnormalTime(void)
��������	:д�㲥Уʱ�쳣ʱ�ӹ���ʱ��
�������	:
�������:
���ز���	:��
ȫ�ֱ���:
������ע:
*******************************************************************************/
void SF_Write_BroadTimeAbnormalTime(uchar8 *P_SystemTime)
{
	InF_Write_Data(C_Msg_Communication, CClock_FaultTime, P_SystemTime, CLClock_FaultTime, C_W_SafeFlag);	/*�㲥Уʱ�쳣ʱ��ǰʱ��д�����ݲ�*/
}
/*******************************************************************************
����ԭ��:void SF_Clear_BroadTimeAbnormalTime(void)
��������	:д�㲥Уʱ�쳣ʱ�ӹ���ʱ��Ϊ0
�������	:
�������:
���ز���	:��
ȫ�ֱ���:
������ע:
*******************************************************************************/
void InF_Clear_BroadTimeAbnormalTime(void)
{
	uchar8	V_Buf[CLClock_FaultTime] = {0};

	InF_Write_Data(C_Msg_Communication, CClock_FaultTime, V_Buf, CLClock_FaultTime, C_W_SafeFlag);  		/*����㲥Уʱ�쳣*/
}
/*******************************************************************************
����ԭ�ͣ�void		Have_IPEvent_Prog_698(ulong32 V_ulProgOAD,ulong32 V_ulProgTimesOAD,Str_Comm_645 *pV_645Frame)
����������ӵ�ж�������¼���Ŀ��̣���ɶ�Ӧ�¼���¼���������д���ݲ㣩
		�����ǣ�ʱ�Ρ�ʱ���������ա��������ա���ϡ������ա������׷��ʱ������׽��ݱ���
���������	pProgTable			:��Ӧ�¼���¼Щ�ı���ַ
			State��C_Happen_EventMsg �¼���������
			TabLineNum			:������ܵ�����
			*pV_645Frame			:�յ���645��Ϣ֡(�Ѿ��������Ƿ������̵��ж�)
�����������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
void Have_IPEvent_Prog_698(ulong32 V_ulProgOAD, ulong32 V_ulProgTimesOAD, Str_Comm_645 *pV_645Frame)
{
	uchar8	V_ReturnData;
	uchar8	buf[C_Buf_MaxLen];
	ushort16	buf_O_CanWrite = 0, V_ucRelateoff, i;		/*��������д���ݵ�ƫ��*/
	ushort16	LenFor_Data = C_Buf_MaxLen;					/*�������ɱ�д���ܵĳ���*/
	uchar8	V_OIB, V_ucLastTime[7];
	Str_Event_OIB1 Str_EventInfo;
	ushort16 V_ucLen, V_usDataEncode;
    ulong32 V_Subs;
	uchar8 V_ucResultFlag;
	uchar8 V_ucDataBuf[CLProgPT_NoteC_1];
    uchar8 V_ucPTNum,V_ucOffset = 0;
    ulong32 V_ulPTOAD;

	V_ucLen = CLDate_Time;
	InF_Read_Data(CDate_Time, V_ucLastTime, &V_ucLen, &V_usDataEncode);	/*����ʱ��*/
	/*�������¼�ѭ��ǰ�����ȶ�ȡ��̴�����ʱ�䣨����ʱ��ͽ���ʱ����ͬ�����¼�����Դ���ϱ�״̬*/
	buf_O_CanWrite = SF_GetProgFixedData_698(V_ulProgTimesOAD, buf);

	V_OIB = (V_ulProgOAD >> 16);
	if( pV_645Frame->DI == CReactive_Com_State2 )
	{
		buf[buf_O_CanWrite - 2] = 0x01;						/*����޹�2��̷���ԴΪ1*/
	}

/*ʱ�α�͹������ձ�̼�¼��������OAD+��������*/
	if( ( V_ulProgOAD == CProgPT_Note_1 )
	 || ( V_ulProgOAD == CProgHol_Note_1 ) )
	{
		PF_CopyDataBytes(&pV_645Frame->Data[CDI_O_V_645], &buf[buf_O_CanWrite], 4);
		buf_O_CanWrite += 4;
		LenFor_Data = C_Buf_MaxLen - buf_O_CanWrite;
		InF_Read_Data((pV_645Frame->DI), &buf[buf_O_CanWrite], &LenFor_Data, &V_usDataEncode);
		buf_O_CanWrite += (uchar8)LenFor_Data;
	}

/*ȡ���������б��е�����*/
	for( i = 0; i < C_Event_OIBTableLen; i++ )
	{
		if( V_OIB == Event_OIBTable[i].OIB )
		{
			break;
		}
	}
	if( i >= C_Event_OIBTableLen )
	{
		return;
	}
	Str_EventInfo = Event_OIBTable[i];						/*��ȡ��ز���*/
	V_ucRelateoff = buf_O_CanWrite;
	LenFor_Data = C_Buf_MaxLen-V_ucRelateoff;
	if( Inf_GetRecordData( &buf[V_ucRelateoff], &LenFor_Data, Str_EventInfo.RelatedOAD, 0x01 ) == C_OK )	/*ȡ��������*/
	{
		buf_O_CanWrite += 	LenFor_Data;
	}
	V_ReturnData = InF_Write_Data(C_Msg_Communication, V_ulProgOAD, buf, buf_O_CanWrite, (SV_Comm_Parse_Local.SafeControlFlag) );

	if(V_ReturnData != C_OK)
	{
		;													/*�������Ӧ���ǲ����ܳ��ֵġ�*/
	}
/********************************************************************/
    /*/ɽ��˫Э�����ӣ�ʱ����ʱ�α�洢*/
    PF_CopyDataBytes(V_ucLastTime, V_ucDataBuf, CLDate_Time - 1);
    V_ucOffset = CLDate_Time-1;
    memset(&V_ucDataBuf[V_ucOffset], 0xFF, CLRelayOpen_OpeCode_1);
    V_ucOffset += CLRelayOpen_OpeCode_1;
    if(V_ulProgOAD == CProgPT_Note_1) 						/*ʱ�α�*/
    {
		V_ucLen = CLProgPT_NoteC_1;
		/**********��ǰ�����ݴ���**********/
		/*����ǰ����ʱ�α�,0X40160201-0X40160204*/
		V_ulPTOAD = 0x40160201;
		for( i = 0; i < C_PTProgEventNum; i++ )
		{
			if(InF_Read_Data(V_ulPTOAD, &V_ucDataBuf[V_ucOffset], &V_ucLen, &V_usDataEncode) != C_OK)
			{
				memset(&V_ucDataBuf[V_ucOffset], 0x00, CLFirst_TZone_Data);
			}
			V_ucOffset += V_ucLen;
			V_ulPTOAD ++;
		}
		InF_Write_Data(C_Msg_Communication, CProgPT_NoteC_1, V_ucDataBuf, CLProgPT_NoteC_1, (SV_Comm_Parse_Local.SafeControlFlag));

		/*����ǰ����ʱ�α�,0X40160205-0X40160208*/
		V_ucOffset = 0;
		for( i = 0; i < C_PTProgEventNum; i++ )
		{
			if(InF_Read_Data(V_ulPTOAD, &V_ucDataBuf[V_ucOffset], &V_ucLen, &V_usDataEncode) != C_OK)
			{
				memset(&V_ucDataBuf[V_ucOffset], 0x00, CLFirst_TZone_Data);
			}
			V_ucOffset += V_ucLen;
			V_ulPTOAD ++;
		}
      InF_Write_Data(C_Msg_Communication, CProgPT_NoteD_1, V_ucDataBuf, CLProgPT_NoteD_1, (SV_Comm_Parse_Local.SafeControlFlag));

      /**********���������ݴ���**********/
      V_ucPTNum = buf[C_PTNum_Offset];
      if(V_ucPTNum <= C_PTProgEventNum)
      {
        /*����������ʱ�α�,0X40170201-0X40170204*/
      	V_ulPTOAD = 0x40170201;
      	V_ucOffset = 0;
      	for( i = 0; i < C_PTProgEventNum; i++ )
      	{
      		if( ( i + 1 ) == V_ucPTNum ) 					/*��ʱ���Ǵ�1��ʼ��i��0��ʼ*/
      	    {
      			PF_CopyDataBytes(&buf[C_PTData_Offset], &V_ucDataBuf[V_ucOffset], V_ucLen);

        	}
        	else
        	{
        		if( InF_Read_Data( V_ulPTOAD, &V_ucDataBuf[V_ucOffset], &V_ucLen, &V_usDataEncode ) != C_OK )
      			{
        			memset(&V_ucDataBuf[V_ucOffset], 0x00, CLFirst_TZone_Data);
        		}
        	}
        	V_ucOffset += V_ucLen;
        	V_ulPTOAD ++;
  	  	}
        InF_Write_Data(C_Msg_Communication, CProgPT_NoteE_1, V_ucDataBuf, CLProgPT_NoteE_1, (SV_Comm_Parse_Local.SafeControlFlag));

         /*����������ʱ�α�,0X40160205-0X40160208*/
         V_ucOffset = 0;
         for( i = 0; i < C_PTProgEventNum; i++ )
         {
            if( InF_Read_Data(V_ulPTOAD, &V_ucDataBuf[V_ucOffset], &V_ucLen, &V_usDataEncode ) != C_OK )
            {
              memset(&V_ucDataBuf[V_ucOffset], 0x00, CLFirst_TZone_Data);
            }
            V_ucOffset += V_ucLen;
            V_ulPTOAD ++;
          }
        InF_Write_Data(C_Msg_Communication, CProgPT_NoteF_1, V_ucDataBuf, CLProgPT_NoteF_1, (SV_Comm_Parse_Local.SafeControlFlag));
      }
      else
      {
        /*����������ʱ�α�,0X40170201-0X40170204*/
      	V_ulPTOAD = 0x40170201;
      	V_ucOffset = 0;
      	for( i = 0; i < C_PTProgEventNum; i++ )
      	{
            if( InF_Read_Data(V_ulPTOAD, &V_ucDataBuf[V_ucOffset], &V_ucLen, &V_usDataEncode ) != C_OK )
      		{
        		memset(&V_ucDataBuf[V_ucOffset], 0x00, CLFirst_TZone_Data);
        	}
        	V_ucOffset += V_ucLen;
        	V_ulPTOAD ++;
  	  	}
        InF_Write_Data(C_Msg_Communication, CProgPT_NoteE_1, V_ucDataBuf, CLProgPT_NoteE_1, (SV_Comm_Parse_Local.SafeControlFlag));
        /*����������ʱ�α�,0X40170205-0X40170208*/
      	V_ucOffset = 0;
      	for( i = 0; i < C_PTProgEventNum; i++ )
      	{
      		if( ( i + 1 ) == V_ucPTNum ) 						/*��ʱ���Ǵ�1��ʼ��i��0��ʼ*/
      	    {
      			PF_CopyDataBytes(&buf[C_PTData_Offset], &V_ucDataBuf[V_ucOffset], V_ucLen);

        	}
        	else
        	{
        		if( InF_Read_Data( V_ulPTOAD, &V_ucDataBuf[V_ucOffset], &V_ucLen, &V_usDataEncode ) != C_OK )
      			{
        			memset(&V_ucDataBuf[V_ucOffset], 0x00, CLFirst_TZone_Data);
        		}
        	}
        	V_ucOffset += V_ucLen;
        	V_ulPTOAD ++;
  	  	}
        InF_Write_Data(C_Msg_Communication, CProgPT_NoteF_1, V_ucDataBuf, CLProgPT_NoteF_1, (SV_Comm_Parse_Local.SafeControlFlag));
      }
    }
    if(V_ulProgOAD == CProgTZ_Note_1)/*ʱ����*/
    {
		V_ucLen = CLFirst_TZone_Data;
		if( InF_Read_Data( 0x40140200, &V_ucDataBuf[CLDate_Time - 1], &V_ucLen, &V_usDataEncode ) == C_OK )
		{
			InF_Write_Data(C_Msg_Communication, CProgTZ_CurrentPart_Note_1, V_ucDataBuf, CLProgTZ_CurrentPart_Note_1, (SV_Comm_Parse_Local.SafeControlFlag));
		}
	}
/********************************************************************/
/*����ǰ�¼���¼�Ѿ�д�꣬���Ա����,����������������*/
	if( ( V_ulProgOAD != CTol_Clear_Note_1 ) && ( V_ulProgOAD !=CDe_Clear_Note_1 ) && ( V_ulProgOAD !=CProgKD_Note_1 ) )
	{
		if(SV_Comm_Parse_Local.RecFlag == C_CommRecFlagForInt_Ok)
		{
			/*�ж������̱�־��ȷ*/
			if(SV_Comm_Parse_Local.SafeControlFlag==C_W_SafeFlag)
			{
				/*�������������̱�־��ȷ*/
				if( pV_645Frame->DataLen < ( 4 + 4 + 4 ) )
				{
					return;
				}
				LenFor_Data = pV_645Frame->DataLen - ( 4 + 4 + 4 );		/*4  4�ֽ�DI��4�ֽ�OpCode��4�ֽ�PW*/
                if( ( pV_645Frame->DI == CCurrent_RateFF_Price ) || ( pV_645Frame->DI == CCurrent_Ladder_Table ) )
				{
					InF_Write_Data(C_Msg_Card, (pV_645Frame->DI), &(pV_645Frame->Data[C_Data_OFS_14]), (ushort16) LenFor_Data, (SV_Comm_Parse_Local.SafeControlFlag));
                }
                else
                {
                    if(pV_645Frame->DI == CBroadcastTimeM)
                    {
                        V_ReturnData = InF_Write_Data(C_Msg_Communication, CDate_Time, &pV_645Frame->Data[CBoardCastData_O_V_645 + C_ss_O], CLDate_Time, SV_Comm_Parse_Local.SafeControlFlag);
						if(V_ReturnData == C_OK)
						{
							InF_Write_Data(C_Msg_Communication, CBackTime_OneSec, &(pV_645Frame->Data[CBoardCastData_O_V_645 + C_ss_O]), CLBackTime_OneSec, (SV_Comm_Parse_Local.SafeControlFlag));
							SF_SetRTCErrState(C_RTC_OK);
						}
                    }
                    else if(pV_645Frame->DI == CDate_Time)
                    {
                        V_ucResultFlag = InF_Write_Data(C_Msg_Communication, CDate_Time, &(pV_645Frame->Data[C_Data_OFS_14]), (ushort16) LenFor_Data, (SV_Comm_Parse_Local.SafeControlFlag));
                        if(V_ucResultFlag == C_OK)
                        {
                            InF_Write_Data(C_Msg_Communication, CBackTime_OneSec, &(pV_645Frame->Data[C_Data_OFS_14]), CLBackTime_OneSec, (SV_Comm_Parse_Local.SafeControlFlag));
                            SF_SetRTCErrState(C_RTC_OK);
                        }
                    }
                    else
                    {
                        V_ucResultFlag = InF_Write_Data(C_Msg_Communication, (pV_645Frame->DI), &(pV_645Frame->Data[C_Data_OFS_14]), (ushort16) LenFor_Data, (SV_Comm_Parse_Local.SafeControlFlag));
                    }
                }
			}
		}

	}

	LenFor_Data = CLDate_Time;
	InF_Read_Data(CDate_Time,&buf[CLEventNum+CLEventHPTime], &LenFor_Data, &V_usDataEncode);				/*����ʱ��*/
	/*Уʱ��¼/�㲥Уʱ���ж��޸ĺ�ʱ����޸�ǰʱ��С���������ݲ�ӿں������Ǽ�¼������*/
	if( ( V_ulProgOAD == CAdjTime_Note_1 )
	||( V_ulProgOAD == CBroadcastTime_Note_1 ) )
	{
		if( PF_Campare_Data(V_ucLastTime, &buf[CLEventNum+CLEventHPTime], CLDate_Time) == C_GreaterThan )
		{
			InF_ChangeTime_LoadProfileCover();
		}
		if(V_ulProgOAD == CAdjTime_Note_1)/*Уʱ��¼*/
		{
			Inf_EventReport_HP(C_AdjTimeEventNo,C_Happen_EventReport);
			InF_ActiveReportSetting(C_Times_ReworkTime);
		}
		else if( V_ulProgOAD == CBroadcastTime_Note_1 )/*�㲥Уʱ*/
		{
			Inf_EventReport_HP(C_BroadcastTimeEventNo, C_Happen_EventReport);
		}
		if( PF_Campare_Data(&V_ucLastTime[CDate_Time_DD_O], &buf[CLEventNum + CLEventHPTime + CDate_Time_DD_O], C_DT_Len_DD_698) != C_Equal )
		{
			Clear_BDSC_RecentClock();						/*�㲥Уʱʱ������*/
			InF_Clear_BroadTimeAbnormalTime();				/*�㲥Уʱ�������Сƫ��������쳣��־����*/
		}
	}

	LenFor_Data = C_Buf_MaxLen - V_ucRelateoff;
    buf_O_CanWrite = V_ucRelateoff;
	if( Inf_GetRecordData(&buf[V_ucRelateoff], &LenFor_Data, Str_EventInfo.RelatedOAD, 0x02 ) == C_OK )	/*ȡ��������*/
	{
		buf_O_CanWrite += 	LenFor_Data;
	}
	V_ReturnData = InF_Write_Data(C_Msg_Communication, V_ulProgOAD + 1, buf, buf_O_CanWrite, (SV_Comm_Parse_Local.SafeControlFlag));

	if(V_ReturnData != C_OK)
	{
		;									/*�������Ӧ���ǲ����ܳ��ֵġ�*/
	}

	if(CProgReC_Note_1 == V_ulProgOAD)
	{
		V_ucLen = CLProgReC1_Degree;
		if(pV_645Frame->DI == 0x41130200)	/*����޹�1�����ֱ��*/
		{
			if(InF_Read_Data(CProgReC1_Degree , (uchar8 *)&V_Subs, &V_ucLen, &V_usDataEncode) != C_OK)
			{
				V_Subs = 1;
			}
			else
			{
				V_Subs++;
			}
			InF_Write_Data(C_Msg_Communication, CProgReC1_Degree , (uchar8 *)&V_Subs, CLProgReC1_Degree, (SV_Comm_Parse_Local.SafeControlFlag));
		}
		else								/*����޹�2�����ֱ��*/
		{
			if(InF_Read_Data(CProgReC2_Degree , (uchar8 *)&V_Subs, &V_ucLen, &V_usDataEncode) != C_OK)
			{
				V_Subs = 1;
			}
			else
			{
				V_Subs++;
			}
			InF_Write_Data(C_Msg_Communication, CProgReC2_Degree , (uchar8 *)&V_Subs, CLProgReC1_Degree, (SV_Comm_Parse_Local.SafeControlFlag));
		}
	}
	return;
}
/*******************************************************************************
����ԭ�ͣ�uchar8		SF_GetProgFixedData_698(ulong32 V_ulProgTimesOAD,uchar8 *P_Data)
����������
���������
�������������ʵ�����ݳ���
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_GetProgFixedData_698(ulong32 V_ulProgTimesOAD, uchar8 *P_Data)
{
	uchar8	buf_O_CanWrite = 0, V_EndTime[7] = {0};
	ushort16	LenFor_Data = C_Comm_Buf_MaxLen, V_usDataEncode;					/*�������ɱ�д���ܵĳ���*/

	/*�������¼�ѭ��ǰ�����ȶ�ȡ��̴���+1��ʱ�䣨����ʱ��ͽ���ʱ����ͬ��*/
	InF_Read_Data(V_ulProgTimesOAD, &P_Data[buf_O_CanWrite], &LenFor_Data, &V_usDataEncode);/*��������*/
	buf_O_CanWrite += LenFor_Data;

	LenFor_Data = C_Comm_Buf_MaxLen - buf_O_CanWrite;
	InF_Read_Data(CDate_Time, &P_Data[buf_O_CanWrite], &LenFor_Data, &V_usDataEncode);			/*����ʱ��*/
	buf_O_CanWrite += LenFor_Data;													/*���ݲ㷵дʵ�ʳ��ȵ�LenFor_Data*/

	PF_CopyDataBytes(V_EndTime, &P_Data[buf_O_CanWrite], LenFor_Data);				/*����ʱ��*/
	buf_O_CanWrite += LenFor_Data;

	P_Data[buf_O_CanWrite] = 0x00;	/*����Դ*/
	buf_O_CanWrite += 1;

	P_Data[buf_O_CanWrite] = 0x00;	/*�ϱ�״̬*/
	buf_O_CanWrite += 1;

	return buf_O_CanWrite;
}
/*******************************************************************************
����ԭ�� uchar8 Set_Service_PerOI��Str_Comm_698_RW *pV_698RWPara��
�������� �ͻ�������һ���������Ժ���
������� Str_Comm_698_RW�ж�Ӧ��ȡ���ݶ���OI���������͵�
������� pV_698RWParaдOI�����ý�������óɹ�Ϊ0������ʧ��������Ӧ������ʧ��ԭ��
���ز��� �����Ƿ���ȷ��C_OK��ʾ��ȡ�ɹ���������ʾ�������C_
ȫ�ֱ���
������ע
*******************************************************************************/
uchar8 SF_SetPerOI(Str_Comm_698_RW *pV_698RWPara, uchar8 V_ucOINum, Str_Comm_645 *pV_645Frame)
{
	uchar8 ReturnFlag, V_ucBuff[4];
	uchar8 V_uc645DINum, V_ucDataLen, V_ucOffset=0;
    uchar8 V_LineNO, i, V_ucFlag = 0;
    uchar8 V_OADOffset_T, V_Len_645, V_Len_645_R, V_ErrorOAD_Off = 0;
    ushort16 j;
    ulong32 V_Event_ROAD_T, V_ulOAD, V_ulLastDI = 0xFFFFFFFF, V_ulNextDI = 0xFFFFFFFF;
	Str_Type645DI_Class V_DIFor645[2] = {0};
    Str_Comm_645 V_645Frame;

    /*OI-DI*/
    ReturnFlag = JudgeMeterType(pV_698RWPara->Wt_OI[V_ucOINum].WtOI);
    if(ReturnFlag != C_OK)	/*�ж��Ƿ��Ǳ��ر������*/
    {
        pV_698RWPara->Wt_OI[V_ucOINum].DataLen = 0;
    }
    else
    {   /*OI-DI*/
        if( ( pV_698RWPara->Wt_OI[V_ucOINum].WtOI & 0xFF000000 ) == 0xF3000000 )					/*��ʾ���*/
        {
            ReturnFlag = SF_SetDispPerOI(pV_698RWPara, V_ucOINum, pV_645Frame);
        }
        else if( ( pV_698RWPara->Wt_OI[V_ucOINum].WtOI & 0xFFFFFF00 ) == 0x40110200 )				/*��������*/
        {
            if( pV_698RWPara->Wt_OI[V_ucOINum].WtOI == 0x40110200 )
            {
                ReturnFlag = C_RWForbid_DAR;
                pV_698RWPara->Wt_OI[V_ucOINum].Wt_Result = ReturnFlag;
            }
            else
            {
                ReturnFlag = SF_SetHolidyPerOI(pV_698RWPara, V_ucOINum, pV_645Frame);
            }
        }
        else if( pV_698RWPara->Wt_OI[V_ucOINum].WtOI == CSafeModeParaNat3 )							/*��ȫģʽ����*/
        {
            ReturnFlag = SF_SetSafeModeParaNat3PerOI(pV_698RWPara, V_ucOINum);
        }
        else
        {
			ReturnFlag = SF_Judge_OINature(pV_698RWPara, &V_DIFor645[0], &V_uc645DINum, C_SetUp);	/*д����*/

            if(ReturnFlag != C_OK)
            {
                pV_698RWPara->Wt_OI[V_ucOINum].Wt_Result = ReturnFlag;
            }
            else
            {
				pV_645Frame->DI = pV_698RWPara->Wt_OI[V_ucOINum].WtOI;

                 /*����645��ʽ��֯����*/
                if(InF_Judge_EventOAD_OP(pV_645Frame->DI, &V_LineNO) == C_OK)						/*д�¼���¼��������*/
                {
					if( ( (uchar8)pV_645Frame->DI ) != 0 )
					{
						ReturnFlag = C_RWForbid_DAR;
						pV_698RWPara->Wt_OI[V_ucOINum].Wt_Result = ReturnFlag;
						return ReturnFlag;
					}

					V_Len_645 = 1;
					V_OADOffset_T = 0;

                    if(pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[0] != C_array)						/*�������ݲ��������ʽ��Ӧ�����Ͳ�ƥ��*/
                    {
                        ReturnFlag = C_TypeErr_DAR;
                        pV_698RWPara->Wt_OI[V_ucOINum].Wt_Result = ReturnFlag;
                        return ReturnFlag;
                    }

                    if(pV_698RWPara->Wt_OI[V_ucOINum].WtOI == CTol_Clear_OADTab)					/*˽Կ״̬�²��������õ�������¼��Ĺ����б�*/
                    {
                        if( (InF_JudgeKeyStatus() == C_StateOfOfficialKey) && (InF_JudgeIJTimer() != C_OK) )	  /*��ʽ��Կ*/
                        {
                            ReturnFlag = C_RWForbid_DAR;
                            pV_698RWPara->Wt_OI[V_ucOINum].Wt_Result = ReturnFlag;
                            return ReturnFlag;
                        }
                    }

                    if((pV_645Frame->DI & 0x000000FF) == 0)
                    {
                        V_Len_645 = pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[1];
                        V_OADOffset_T = 2;
                    }

                    V_Len_645_R = V_Len_645;
                    for( i = 0; i < V_Len_645; i++)
					{
                        if( pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_OADOffset_T + (i * 5)] != C_OAD )
                        {
                            ReturnFlag = C_TypeErr_DAR;
                            pV_698RWPara->Wt_OI[V_ucOINum].Wt_Result = ReturnFlag;
                            return ReturnFlag;
                        }
                        V_Event_ROAD_T = PF_Buffer4ToUlong32_698(&pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_OADOffset_T + (i * 5) + 1]);
                        V_Event_ROAD_T &= 0xFFFF1FFF;

                        for( j = 0; j < Str_FrozenConvert_Table_Len; j++)
                        {
                            if(V_Event_ROAD_T == Str_FrozenConvert_Table[j].V_ulOAD)
                            {
                                break;
                            }
                        }

                        if(j < Str_FrozenConvert_Table_Len)
                        {
                            pV_645Frame->Data[C_Data_OFS_14 + (i * 2) - V_ErrorOAD_Off] = (uchar8)j;
                            pV_645Frame->Data[C_Data_OFS_14 + (i * 2) + 1-V_ErrorOAD_Off] = ((uchar8)(j >> 8)) |(pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_OADOffset_T + (i * 5) + 3] & 0xE0);
                        }
                        else
                        {
                            V_ErrorOAD_Off += 2;
                            V_Len_645_R--;
                        }
					}

                    pV_645Frame->DataLen = V_Len_645_R * 2;

                    ReturnFlag = InF_Write_Data(C_Msg_Communication, pV_645Frame->DI, &pV_645Frame->Data[C_Data_OFS_14], pV_645Frame->DataLen, C_W_SafeFlag);
                    if(ReturnFlag == C_OK)
                    {
                        ReturnFlag = InF_Write_Data(C_Msg_Communication, Event_OIBTable[V_LineNO].RelatedOAD_T, &V_Len_645_R, CLI_Free_OADTabLen_T, C_W_SafeFlag);
                        if(ReturnFlag == C_OK)
                        {
                            SF_EventClear_698(pV_645Frame->DI, &V_645Frame, C_NotProgram);
                            {
                                PF_Ulong32ToBuffer4(V_ucBuff,&pV_698RWPara->Wt_OI[V_ucOINum].WtOI,4);
                                INF_Append_ProgRecordDI(&pV_645Frame->Data[COpcode_14O_V_645],V_ucBuff,&SV_Comm_Parse.ProgRecord,pV_698RWPara->ServiceFlag_First);
                            }
                        }
                    }
                }
                else if(InF_Judge_FreezeOAD_OP(pV_645Frame->DI,&V_LineNO) == C_OK)      /*д�����¼��������*/
                {
                    ReturnFlag = SF_FreezeOADSet(pV_698RWPara->Wt_OI[V_ucOINum],0x68);
                    if(ReturnFlag == C_OK)      										/*��¼�ܱ���¼���¼*/
                    {
                        PF_Ulong32ToBuffer4(V_ucBuff, &pV_698RWPara->Wt_OI[V_ucOINum].WtOI, 4);
                        INF_Append_ProgRecordDI(&pV_645Frame->Data[COpcode_14O_V_645], V_ucBuff, &SV_Comm_Parse.ProgRecord, pV_698RWPara->ServiceFlag_First);
                    }
                }
                else
                {
                    if(V_uc645DINum == 1)
                    {
                        pV_645Frame->DI = pV_698RWPara->Wt_OI[V_ucOINum].WtOI;
						if( ( pV_645Frame->DI == 0x41160200 ) || ( pV_645Frame->DI == CMeter_CommPro )
                         || ( pV_645Frame->DI == 0x300F0600 ) || ( pV_645Frame->DI == 0x30100600 ) || (pV_645Frame->DI == 0x30110600 )
                         || ( pV_645Frame->DI == 0x302E0600 ) || ( pV_645Frame->DI == 0x302F0600 ) )
                        {
                            pV_645Frame->DI += 1;
                        }

                        if( ( (pV_645Frame->DI & 0xFFFFFF00 ) == CSec_TZone_Data )
                         || ( ( pV_645Frame->DI & 0xFFFFFF00 ) == CFirst_TZone_Data )
                         || ( ( pV_645Frame->DI & 0xFFFFFF00 ) == CMeter_Position ) )
                        {
                            pV_645Frame->DI = (pV_645Frame->DI & 0xFFFFFF00);
                        }

                        V_ucDataLen = V_DIFor645->DataLen_645[0];
                        V_ucOffset = 0;

                        if( ( (pV_645Frame->DI&0xFFFFFF00) != 0x40140200 ) && ( (pV_645Frame->DI&0xFFFFFF00) != 0x40150200 ) )
                        {
                            SF_CombDataTo645Type_W((pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data + V_ucOffset), pV_645Frame, V_ucDataLen);
                        }
                        else
                        {
                            SF_CombDataTo645Type_W(V_DIFor645[0].TZone_Data, pV_645Frame, V_ucDataLen);
                        }

                        if(pV_645Frame->DI == CGPS_Signal)   /*���������GPRS�źŲ�д��̼�¼*/
                        {
                            V_ucFlag = C_NotWriteEventRecord;
                        }
                        else
                        {
                            V_ucFlag = C_NeedWriteEventRecord;
                        }

                        ReturnFlag = SF_SetParm(pV_645Frame, V_ulLastDI, V_ulNextDI, V_ucFlag, pV_698RWPara->Wt_OI[V_ucOINum].WtOI, C_SetUp);

                    }
                    else
                    {
                        ReturnFlag = SF_Judge_Para(pV_698RWPara, &V_DIFor645[0], V_uc645DINum, V_ucOINum);
                        if( (ReturnFlag == C_OK) && ( (V_uc645DINum <= 10) ) )
                        {
                            V_ulOAD = pV_698RWPara->Wt_OI[V_ucOINum].WtOI;
                            V_ucOffset = 0;

                            for( j = 0; j < V_uc645DINum; j++)
                            {
                                if(j == 0)
                                {
                                    V_ulLastDI = 0xFFFFFFFF;
                                    V_ulNextDI = V_ulOAD | (j + 2);
                                }
                                else if(j == (V_uc645DINum - 1))
                                {
                                    V_ulLastDI = V_ulOAD | j;
                                    V_ulNextDI =	0xFFFFFFFF;
                                    V_ucFlag = C_NeedWriteEventRecord;
                                }
                                else
                                {
                                    V_ulLastDI = V_ulOAD | j;
                                    V_ulNextDI = V_ulOAD | ( j + 2);
                                }
                                pV_645Frame->DI = V_ulOAD | ( j + 1);
                                V_ucDataLen = V_DIFor645->DataLen_645[j];
                                SF_CombDataTo645Type_W((pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data+V_ucOffset), pV_645Frame, V_ucDataLen);

                                V_ucOffset += V_ucDataLen;
                                ReturnFlag = SF_SetParm(pV_645Frame, V_ulLastDI, V_ulNextDI, V_ucFlag, pV_698RWPara->Wt_OI[V_ucOINum].WtOI, C_SetUp);

                                if(ReturnFlag != C_OK)
                                {
                                    break;
                                }
                            }
                    	}
                	}
                }
                pV_698RWPara->Wt_OI[V_ucOINum].Wt_Result = ReturnFlag;
			}
		}
	}
	pV_698RWPara->Wt_OI[V_ucOINum].Wt_Result = ReturnFlag;
    return 	ReturnFlag;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_Judge_Para(Str_Comm_698_RW *pV_698RWPara,Str_Type645DI_Class *V_DIFor645,uchar8 V_uc645DINum,uchar8 V_ucOINum)
�����������������ò���ʱѭ���жϲ����Ϸ���
���������
�����������
���ز���������C_OK��ʾ���в������Ϸ�
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_Judge_Para(Str_Comm_698_RW *pV_698RWPara, Str_Type645DI_Class *V_DIFor645, uchar8 V_uc645DINum, uchar8 V_ucOINum)
{
	Str_Comm_645	V_645Frame;
	ulong32 V_ulOAD;
	uchar8 V_ucOffset = 0,V_ucDataLen, j, ReturnFlag = C_OtherErr_DAR;
	Str_WrParmTable	WrParmTable;

	V_ulOAD = pV_698RWPara->Wt_OI[V_ucOINum].WtOI;
	for( j = 0; j < V_uc645DINum; j++ )
	{
		/*DI*/
		V_645Frame.DI = V_ulOAD|(j+1);
		V_ucDataLen = V_DIFor645->DataLen_645[j];
		SF_CombDataTo645Type_W((pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data+V_ucOffset),&V_645Frame,V_ucDataLen);

        ReturnFlag = LookFor_WrParmTable(&V_645Frame,&WrParmTable);
        if(ReturnFlag != C_OK)
        {//��ʶ�벻�ԣ�Ӧ����������
            return ReturnFlag;
        }
        //���ȡ����ݺϷ����ж�
        ReturnFlag = Is_SetParmData_Ok(&V_645Frame,&WrParmTable);
        V_ucOffset += V_ucDataLen;

		if(ReturnFlag !=C_OK)
		{
			break;
		}
	}
    return 	ReturnFlag;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_SetHolidyPerOI(Str_Comm_698_RW *pV_698RWPara,uchar8 V_ucOINum,Str_Comm_645 *pV_645Frame)
�����������ͻ�������һ���������Ժ���
���������	Str_Comm_698_RW�ж�Ӧ��ȡ���ݶ���OI���������͵�
���������pV_698RWParaдOI�����ý�������óɹ�Ϊ0������ʧ��������Ӧ������ʧ��ԭ��
���ز����������Ƿ���ȷ��C_OK��ʾ��ȡ�ɹ���������ʾ�������
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_SetHolidyPerOI(Str_Comm_698_RW *pV_698RWPara, uchar8 V_ucOINum, Str_Comm_645 *pV_645Frame)
{
	uchar8	ReturnFlag = C_ObjectUndefine_DAR;
	ulong32 V_ulLastDI = 0xFFFFFFFF;
	ulong32 V_ulNextDI = 0xFFFFFFFF;
	uchar8	V_ucFlag = 0;

	ushort16	V_Off=0;
	uchar8	*P_DataAddr;

	P_DataAddr = pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data;

	if( ( P_DataAddr[V_Off] != C_structure ) || ( P_DataAddr[V_Off + 1] != 0x02 ) )
	{
		return C_TypeErr_DAR;
	}
	V_Off += 2;
	if( ( P_DataAddr[V_Off] != C_date ) || ( P_DataAddr[V_Off + 6] != C_unsigned ) )
	{
		return C_TypeErr_DAR;
	}

    PF_OneDataReversed (&P_DataAddr[3], pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data, CL_date);	/*���ݵߵ��ȹ�������CBB.a ����� lzy 20210930*/

   // PF_CopyDataBytes(&P_DataAddr[3], pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data, CL_date);
	pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[CL_date] = P_DataAddr[9];

	V_ucFlag = C_NeedWriteEventRecord;

	pV_645Frame->DI = pV_698RWPara->Wt_OI[V_ucOINum].WtOI;
    SF_CombDataTo645Type_W( ( pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data ), pV_645Frame, CL_date + 1 );

	ReturnFlag = SF_SetParm(pV_645Frame, V_ulLastDI, V_ulNextDI,V_ucFlag, pV_698RWPara->Wt_OI[V_ucOINum].WtOI, C_SetUp);


	pV_698RWPara->Wt_OI[V_ucOINum].Wt_Result = ReturnFlag;

    return 	ReturnFlag;
}
/*******************************************************************************
����ԭ�ͣ�void SF_ClearOtherDisplayParm(uchar8 V_ucDisPlayNum,ulong32 V_ulDI)
���������������ò�������Ĳ�������
���������	V_ucDisPlayNum���Ѿ����õ�������V_ulDI���Ѿ������˵�DI���һ����
�����������
���ز�������/1
����λ�ã�
��    ע����ʼд0��DIӦ��������DI����һ����������V_ucDisPlayNum~99��
*******************************************************************************/
void SF_ClearOtherDisplayParm(uchar8 V_ucDisPlayNum, ulong32 V_ulDI)
{
	uchar8 V_ucData[CLKey_Dis_1ScreenCode] = {0}, i;

	memset(&V_ucData[C_DisplayDI2_offset], 0xFF, C_OADLen);
	for( i = V_ucDisPlayNum; i < C_DisplayNumMax; i++ )
	{
		V_ulDI += C_DisplayDICal;
		if( ( V_ulDI & 0x000000FF )> ( CKey_Dis_99ScreenCode & 0x000000FF ) )
		{
			break;
		}
		InF_Write_Data(C_Msg_Communication, V_ulDI, V_ucData, CLKey_Dis_1ScreenCode, C_W_SafeFlag);
	}
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_SetDispPerOI(Str_Comm_698_RW *pV_698RWPara,uchar8 V_ucOINum,Str_Comm_645 *pV_645Frame)
�����������ͻ�������һ���������Ժ���
���������Str_Comm_698_RW�ж�Ӧ��ȡ���ݶ���OI���������͵�
���������	pV_698RWParaдOI�����ý�������óɹ�Ϊ0������ʧ��������Ӧ������ʧ��ԭ��
���ز����������Ƿ���ȷ��C_OK��ʾ��ȡ�ɹ���������ʾ�������
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_SetDispPerOI(Str_Comm_698_RW *pV_698RWPara, uchar8 V_ucOINum, Str_Comm_645 *pV_645Frame)
{
	uchar8   ReturnFlag = C_ObjectUndefine_DAR;

	ushort16 i, j, k, V_uc698Off = 0, V_ucOff = 0;
	ulong32	V_ulDispOIB,V_ulData = 0;
	ulong32 V_ulLastDI = 0xFFFFFFFF;
	ulong32 V_ulNextDI = 0xFFFFFFFF;
	uchar8	V_ucDataLen,V_ucFlag = 0;
	ulong32 V_ulRelatedOI = 0;
	uchar8	V_ucDispOAD[11];

	V_ulDispOIB = pV_698RWPara->Wt_OI[V_ucOINum].WtOI & 0x00FF0000;
	if( ( pV_698RWPara->Wt_OI[V_ucOINum].WtOI & 0xFF00FF00 ) == 0xF3000200 )	/*��ʾ����*/
	{
		if(V_ulDispOIB == 0)		/*ѭ��*/
		{
			pV_645Frame->DI  = 0xF3000200;
		}
		else						/*����*/
		{
			pV_645Frame->DI  = 0xF3010200;
		}

		if ( ( pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[0] == C_array)
		&& ( ( pV_698RWPara->Wt_OI[V_ucOINum].WtOI & 0x000000FF ) == 0 ) )
		{
			k = pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[1];
		}
		else if ( ( pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[0] == C_structure )
			   && ( ( pV_698RWPara->Wt_OI[V_ucOINum].WtOI & 0x000000FF ) != 0 ) )
		{
			k = 1;
		}
		else
		{
			return	C_TypeErr_DAR;	/* ���Ͳ�ƥ��*/
		}

		if(k > 99)
		{
			return 	C_OtherErr_DAR;
		}

		V_uc698Off += 1;
		for(j = 0; j < k; j++)
		{
			if(pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[0] == 0x01)
			{
				V_uc698Off += 1;
				if(pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_uc698Off] != C_structure)
				{
					return	C_TypeErr_DAR;	/* ���Ͳ�ƥ��*/
				}

				V_uc698Off += 2;

				if(pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_uc698Off] != C_CSD)
				{
					return	C_TypeErr_DAR;	/* ���Ͳ�ƥ��*/
				}
				V_uc698Off += 1;
			}
			else
			{
				V_uc698Off += 1;
				if(pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_uc698Off]!=C_CSD)
				{
					return	C_TypeErr_DAR;	/* ���Ͳ�ƥ��*/
				}
				V_uc698Off += 1;
			}

			if(pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_uc698Off] == 0x00)
			{
				V_uc698Off++;
				for(i = 0; i < 4; i++)
				{
					V_ulData <<= 8;
					V_ulData |= (ulong32)pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_uc698Off];
					V_uc698Off++;
				}

				PF_Ulong32ToBuffer4(V_ucDispOAD, &V_ulData, 4);
				PF_Ulong32ToBuffer4(&V_ucDispOAD[4], &V_ulLastDI, 4);
				if(pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_uc698Off] != C_unsigned)
				{
					return	C_TypeErr_DAR;	/* ���Ͳ�ƥ��*/
				}
				V_uc698Off += 1;
				V_ucDispOAD[8] = pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_uc698Off];
			}
			else if(pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_uc698Off] == 0x01)
			{
				V_uc698Off += 1;
				for(i = 0; i < 4; i++)
				{
					V_ulData <<= 8;
					V_ulData |= (ulong32)pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_uc698Off];
					V_uc698Off++;
				}
				PF_Ulong32ToBuffer4(V_ucDispOAD, &V_ulData, 4);
				V_uc698Off++;

				for(i = 0; i < 4; i++)
				{
					V_ulRelatedOI <<= 8;
					V_ulRelatedOI |= (ulong32)pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_uc698Off];
					V_uc698Off++;
				}
				PF_Ulong32ToBuffer4(&V_ucDispOAD[4], &V_ulRelatedOI, 4);
				if(pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_uc698Off] != C_unsigned)
				{
					return	C_TypeErr_DAR;	/* ���Ͳ�ƥ��*/
				}
			    V_uc698Off += 1;
				V_ucDispOAD[8] = pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_uc698Off];
			}
			else
			{
				return	C_TypeErr_DAR;		/* ���Ͳ�ƥ��*/
			}
			pV_645Frame->DI =pV_698RWPara->Wt_OI[V_ucOINum].WtOI + 1 + j;

			if(k == 1)
			{
				pV_645Frame->DI = pV_698RWPara->Wt_OI[V_ucOINum].WtOI;
			}
			if(((pV_698RWPara->Wt_OI[V_ucOINum].WtOI & 0x000000FF) == 0) && (pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[1] == 0x01))
			{
				pV_645Frame->DI = (pV_698RWPara->Wt_OI[V_ucOINum].WtOI | 0x00000001);
			}
			V_ucDataLen = CLAuto_Dis_1ScreenCode;

			SF_CombDataTo645Type_W(V_ucDispOAD, pV_645Frame, V_ucDataLen);

            if(j == (k - 1))
            {
                V_ucFlag = C_NeedWriteEventRecord;
            }
            else
            {
                V_ucFlag = 0;
            }
            ReturnFlag = SF_SetParm(pV_645Frame,V_ulLastDI, V_ulNextDI, V_ucFlag, pV_698RWPara->Wt_OI[V_ucOINum].WtOI, C_SetUp);

			if(ReturnFlag != C_OK)
			{
				break;
			}
		}
		if( ( j == k ) && ( ( pV_698RWPara->Wt_OI[V_ucOINum].WtOI & 0x000000FF ) == 0 ) )		/*����û�����óɹ��Ĳ����������*/
        {
			SF_ClearOtherDisplayParm(j,pV_645Frame->DI);
		}
	}
	else if((pV_698RWPara->Wt_OI[V_ucOINum].WtOI & 0xFF00FFFF) == 0xF3000300)	/*��ʾʱ��*/
	{
		if(V_ulDispOIB == 0)			/*ѭ��*/
		{
			pV_645Frame->DI = CPer_Dis_Screen_Time;
		}
		else							/*����*/
		{
			pV_645Frame->DI =CPerkey_Dis_Screen_Time;
		}
		if(pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[0] != C_long_unsigned)
		{
			return	C_TypeErr_DAR;		/* ���Ͳ�ƥ��*/
		}
		V_ucDataLen = CLPer_Dis_Screen_Time;

        V_ucDispOAD[0] = pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[2];
        V_ucDispOAD[1] = pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[1];
		SF_CombDataTo645Type_W(V_ucDispOAD, pV_645Frame, V_ucDataLen);

		V_ucFlag = C_NeedWriteEventRecord;
		ReturnFlag = SF_SetParm(pV_645Frame, V_ulLastDI, V_ulNextDI, V_ucFlag, pV_698RWPara->Wt_OI[V_ucOINum].WtOI, C_SetUp);

	}
	else if((pV_698RWPara->Wt_OI[V_ucOINum].WtOI & 0xFF00FF00) == 0xF3000400)		/*��ʾ����*/
	{
		if(V_ulDispOIB == 0)			/*ѭ��*/
		{
			pV_645Frame->DI = 0xF3000400;
		}
		else							/*����*/
		{
			pV_645Frame->DI = 0xF3010400;
		}
		if((pV_698RWPara->Wt_OI[V_ucOINum].WtOI & 0xFF00FFFF) != 0xF3000401)		/*����00������02ֻ��*/
		{
			return C_RWForbid_DAR;
		}
        if(pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[0] != C_unsigned)
		{
			return C_TypeErr_DAR;		/*ֻ������������1��unsigned����*/
		}
		V_ucOff+=1;

		V_ucDispOAD[0] = pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_ucOff];



		pV_645Frame->DI = pV_698RWPara->Wt_OI[V_ucOINum].WtOI;

		if(pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_ucOff]>99)
		{
			return C_OtherErr_DAR;		/*������΢����һ��*/
		}

		V_ucDataLen = 1;
		SF_CombDataTo645Type_W(V_ucDispOAD,pV_645Frame,V_ucDataLen);

        V_ucFlag = C_NeedWriteEventRecord;

        ReturnFlag = SF_SetParm(pV_645Frame,V_ulLastDI,V_ulNextDI,V_ucFlag,pV_698RWPara->Wt_OI[V_ucOINum].WtOI,C_SetUp);

	}
	else
	{
		ReturnFlag = C_ObjectUndefine_DAR;
	}

	pV_698RWPara->Wt_OI[V_ucOINum].Wt_Result = ReturnFlag;

    return 	ReturnFlag;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_ActionDispPerOI(Str_Comm_698_RW *pV_698RWPara,uchar8 V_ucOINum,Str_Comm_645 *pV_645Frame)
�����������ͻ�������һ���������Ժ���
���������Str_Comm_698_RW�ж�Ӧ��ȡ���ݶ���OI���������͵�
�������: pV_698RWParaдOI�����ý�������óɹ�Ϊ0������ʧ��������Ӧ������ʧ��ԭ��
���ز�����C_OK��ʾ��ȡ�ɹ���������ʾ�������
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_ActionDispPerOI(Str_Comm_698_RW *pV_698RWPara, uchar8 V_ucOINum, Str_Comm_645 *pV_645Frame)
{
	uchar8	ReturnFlag = C_ObjectUndefine_DAR;
	uchar8	i, V_uc698Off = 0;
	uchar8  V_ucDisplayMsg[20];
	uchar8	V_ucMethod, V_OIB;
	ulong32 V_ulData = 0, V_ulDI, V_ulRelatedDI;
	uchar8 V_DI[9] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

	V_ucMethod = (uchar8)(pV_698RWPara->Wt_OI[V_ucOINum].WtOI >> 8);
	V_OIB = (uchar8)(pV_698RWPara->Wt_OI[V_ucOINum].WtOI >> 16);					/*ȡ������ƫ��*/
	if( ( V_ucMethod == 3 ) && ( V_OIB == 0X01 ) )
	{
		if(pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[0] != 0x00)
		{
			ReturnFlag=C_ObjectTypeErr_DAR;
			return 	ReturnFlag;
		}
		V_ucDisplayMsg[0] = Pt_Dispatch_Key;
		V_ucDisplayMsg[1] = C_KeyDown;												/*�·�*/
		Comm_SendMsg(&V_ucDisplayMsg[0], (Pt_Dispatch_Key_Len + 1), C_Msg_Display);
		ReturnFlag = C_OK;
	}
	else if((V_ucMethod==4)&&(V_OIB == 0X01))
	{
		if(pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[0]!=0x00)
		{
				ReturnFlag=C_ObjectTypeErr_DAR;
				return 	ReturnFlag;
		}
		V_ucDisplayMsg[0] = Pt_Dispatch_Key;
		V_ucDisplayMsg[1] = C_KeyUp;
		Comm_SendMsg(&V_ucDisplayMsg[0],(Pt_Dispatch_Key_Len+1),C_Msg_Display);
		ReturnFlag=C_OK;
	}
	else if(V_ucMethod==5)
	{
		V_uc698Off =0;
		if(pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_uc698Off]!=C_structure)			/*����struct*/
		{
			return  C_TypeErr_DAR;
		}
		V_uc698Off++;
		if(pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_uc698Off]!=3)					/*Ԫ�ز���*/
		{
			return  C_TypeErr_DAR;
		}
		V_uc698Off++;
		if(pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_uc698Off]!=C_CSD)				/*���Ͳ���*/
		{
			return  C_TypeErr_DAR;
		}
		V_uc698Off++;
		if(pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_uc698Off]==0x00)
		{
			V_uc698Off++;
			for(i=0;i<4;i++)
			{
				V_ulData<<=8;
				V_ulData |= (ulong32)pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_uc698Off];
				V_uc698Off++;
			}
			PF_Ulong32ToBuffer4(V_DI,&V_ulData,4);
			/*������ж�*/
			if(pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_uc698Off]!=C_unsigned)		/*���Ͳ���*/
			{
				return  C_TypeErr_DAR;
			}
			V_uc698Off +=1;
			V_DI[8] = pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_uc698Off];
			V_ulData = 0;
			V_uc698Off +=1;
			/*��ʾʱ���ж�*/
			if(pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_uc698Off]!=C_long_unsigned)	/*���Ͳ���*/
			{
				return  C_TypeErr_DAR;
			}
			V_uc698Off +=1;
                        V_ulData = 0;/*/ǰ���Ѿ���ֵ����Ϊ0*/
			V_ulData |= (ulong32)pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_uc698Off];
			V_ulData<<=8;
			V_uc698Off +=1;
			V_ulData |= (ulong32)pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_uc698Off];
		}
		else if(pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_uc698Off]==0x01)
		{
			ulong32 V_ulRelatedOI = 0;
			V_uc698Off++;
			for(i=0;i<4;i++)
			{
				V_ulData<<=8;
				V_ulData |= (ulong32)pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_uc698Off];
				V_uc698Off++;
			}
			PF_Ulong32ToBuffer4(V_DI,&V_ulData,4);
			V_uc698Off++;
			for(i=0;i<4;i++)
			{
				V_ulRelatedOI<<=8;
				V_ulRelatedOI |= (ulong32)pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_uc698Off];
				V_uc698Off++;
			}
			PF_Ulong32ToBuffer4(&V_DI[4],&V_ulRelatedOI,4);
			/*������ж�*/
			if(pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_uc698Off]!=C_unsigned)		/*���Ͳ���*/
			{
				return  C_TypeErr_DAR;
			}
			V_uc698Off +=1;
			V_DI[8] = pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_uc698Off];

			V_uc698Off +=1;
			/*��ʾʱ���ж�*/
			if(pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_uc698Off]!=C_long_unsigned)	/*���Ͳ���*/
			{
				return  C_TypeErr_DAR;
			}
			V_uc698Off +=1;
			V_ulData = 0;/*/ǰ���Ѿ���ֵ����Ϊ0*/
			V_ulData |= (ulong32)pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_uc698Off];
			V_ulData<<=8;
			V_uc698Off +=1;
			V_ulData |= (ulong32)pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_uc698Off];
		}
		else
		{
			return C_TypeErr_DAR;
		}
		PF_Buffer4ToUlong32(V_DI, &V_ulDI, 4);
		PF_Buffer4ToUlong32(&V_DI[4], &V_ulRelatedDI, 4);
		if(InF_LocalAndRemoteMeterDiJudge(V_ulDI) != C_OK)							/*���ر���ز����ж�*/
		{
			return C_ObjectNotExist_DAR;
		}
		if(InF_Display_JudgeIDActive(V_ulDI,V_ulRelatedDI,V_DI[8]) != C_OK)			/*��ʾ��Ч���ж�*/
		{
			return C_ObjectNotExist_DAR;
		}
		V_ucDisplayMsg[0] = Pt_DisplayID;
		PF_CopyDataBytes(V_DI,&V_ucDisplayMsg[1],9);
		PF_CopyDataBytes((uchar8 *)&V_ulData,&V_ucDisplayMsg[10],2);				/*Һ���鿴ʱ������·�hex���ʽ*/
		Comm_SendMsg(&V_ucDisplayMsg[0],(Pt_DisplayID_Len+1),C_Msg_Display);
		ReturnFlag=C_OK;
	}
	else if(V_ucMethod==6)
	{
		if(pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[0] != C_long_unsigned)			/*�����жϡ���ֹ��ʱ��������ֵ*/
		{
			return C_TypeErr_DAR;
		}
		V_ulData = 0;
		V_uc698Off =1;
		V_ulData |= (ulong32)pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_uc698Off];
		V_ulData<<=8;
		V_uc698Off +=1;
		V_ulData |= (ulong32)pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_uc698Off];

		V_ucDisplayMsg[0] = Pt_DisplayID;
		PF_CopyDataBytes(V_DI,&V_ucDisplayMsg[1],9);
		PF_CopyDataBytes((uchar8 *)&V_ulData,&V_ucDisplayMsg[10],2);
		Comm_SendMsg(&V_ucDisplayMsg[0],(Pt_DisplayID_Len+1),C_Msg_Display);
		ReturnFlag=C_OK;
	}
	else if((V_OIB == 0x00)&&((V_ucMethod == 3)||(V_ucMethod == 4)))
	{
		ReturnFlag = C_RWForbid_DAR;
	}
	else
	{
		ReturnFlag = C_ObjectUndefine_DAR;
	}
    return 	ReturnFlag;
}
/*******************************************************************************
����ԭ�ͣ�uchar8	SF_ReadAfterSet(Str_Comm_698_RW *pV_698Frame,Str_Comm_645 *pV_645Frame)
����������
���������
�����������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8	SF_ReadAfterSet(Str_Comm_698_RW *pV_698Frame,Str_Comm_645 *pV_645Frame)
{
	uchar8 i,j,V_ucOffset=0;
	Str_Type645DI_Class	V_DIFor645[2]={0};
	ulong32	V_ulDI;
	uchar8 *P_ucData;
	uchar8	ReturnFlag = C_OtherErr_DAR,V_uc645DINum;

	P_ucData = &pV_645Frame->Data[0]; 															/*���ú��ȡ���ݷ����*/

	for( i = 0; i < (pV_698Frame->RWOI_Num); i++ )
	{

		if( SF_Judge_OINature(pV_698Frame, &V_DIFor645[0], &V_uc645DINum, C_SetUp ) != C_OK )/*set*/
		{
			pV_698Frame->Rd_OI[i].Rd_Result = C_ObjectUndefine_DAR;
		}
		else
		{
				/*����645��ʽ��֯����*/
			if(V_uc645DINum==1)
			{
				/*DI*/
				V_ulDI = V_DIFor645->V_ucOAD;
				ReturnFlag = SF_ReadAfterSetForPerDI(P_ucData+V_ucOffset,V_ulDI,V_DIFor645->DataLen_645[0]);
				V_ucOffset = V_ucOffset+V_DIFor645->DataLen_645[0]+1;
			}
			else
			{
				for(j=0;j<V_uc645DINum;j++)
				{
					/*DI*/
					V_ulDI = V_DIFor645->V_ucOAD+j;
					ReturnFlag = SF_ReadAfterSetForPerDI(P_ucData+V_ucOffset,V_ulDI,V_DIFor645->DataLen_645[j]);
					V_ucOffset = V_ucOffset+V_DIFor645->DataLen_645[j]+1;

					if(ReturnFlag !=C_OK)
					{
						break;
					}
				}
			}
			pV_698Frame->Rd_OI[i].Rd_Result = ReturnFlag;
			pV_698Frame->ResponedNum++;
		}
	}
	return ReturnFlag;
}
/*******************************************************************************
����ԭ�ͣ�uchar8	SF_Read_TZone_PTReg(uchar8 *P_ucData,ulong32	LimitDI,ulong32	V_ulDI)
����������11�����ȡʱ����ʱ�α�����
���������pV_645Frame				:�յ�������֡
			LimitDI						:����DI������ʱ����(04000201)����ʱ����(04000203)
�����������
���ز�����
����λ�ã�
��    ע�����뱾������DI3�϶�����05
*******************************************************************************/
uchar8	SF_Read_TZone_PTReg(uchar8 *P_ucData,ulong32	LimitDI,ulong32	V_ulDI)
{
	uchar8	V_ucDataBuff[60];
	uchar8	V_ReturnData;
	uchar8	LimintData[4];
	ushort16	LenFor_Data, DataLen = 1, V_usDataEncode;

/*��ȡ��ʱ��������ʱ������1�ֽڡ�����Ĭ��14��*/
	V_ReturnData = InF_Read_Data(LimitDI, &LimintData[0], &DataLen, &V_usDataEncode);
	if(V_ReturnData!=C_OK)
	{
		LimintData[0] = 14;
	}
	else
	{
		LimintData[0] = PF_BCDtoHexOneByte(LimintData[0]);
		if(LimintData[0] > 14)
			{
				LimintData[0] = 14;
			}
	}

	LenFor_Data = CLFirst_TZone_Data;

	V_ReturnData = InF_Read_Data(V_ulDI, V_ucDataBuff, &LenFor_Data, &V_usDataEncode);
	PF_CopyDataBytes(V_ucDataBuff,P_ucData,LimintData[0]);

	return V_ReturnData;
}
/*******************************************************************************
����ԭ�ͣ�uchar8	SF_ReadAfterSetForPerDI(uchar8 *P_ucData,ulong32 V_ulDI,uchar8 V_ucDILen)
����������
���������
���������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8	SF_ReadAfterSetForPerDI(uchar8 *P_ucData,ulong32 V_ulDI,uchar8 V_ucDILen)
{
	ushort16	LenFor_Data, V_usDataEncode;		/*�������ɱ�д���ܵĳ���*/
	uchar8	V_ReturnData = C_OK;					/*Ĭ����������ȷ��*/

	LenFor_Data = V_ucDILen ;

/*ʱ����ʱ�α����ʱ������Ŀ��ʱ�α���Ŀ����Ӧ��*/
	ulong32	LimitDI;
	if((V_ulDI == CFirst_TZone_Data)||(V_ulDI == CSec_TZone_Data))
	{
		LimitDI = CYear_Zone_Num;
		V_ReturnData = SF_Read_TZone_PTReg(P_ucData,LimitDI,V_ulDI);
	}
	else if(((V_ulDI >= CFirst_TZone_1PT_Data)&&(V_ulDI<=CFirst_TZone_8PT_Data))
		||((V_ulDI >= CSec_TZone_1PT_Data)&&(V_ulDI<=CSec_TZone_8PT_Data)))
	{
		LimitDI = CDay_Time_Num;
		V_ReturnData = SF_Read_TZone_PTReg(P_ucData,LimitDI,V_ulDI);
	}
	else/*���������ݲ㣬�������ݲ㷵��ֵ��ӦӦ��*/
	{
		V_ReturnData = InF_Read_Data(V_ulDI, P_ucData, &LenFor_Data, &V_usDataEncode);
	}
	return V_ReturnData;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_Set_Service_PerOI(Str_Comm_698_RW *pV_698RWPara,Str_Comm_645 *pV_645Frame)
�����������ͻ�������һ���������Ժ���
���������	Str_Comm_698_RW�ж�Ӧ��ȡ���ݶ���OI���������͵�
���������pV_698RWParaдOI�����ý�������óɹ�Ϊ0������ʧ��������Ӧ������ʧ��ԭ��
���ز����������Ƿ���ȷ��C_OK��ʾ��ȡ�ɹ���������ʾ�������
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_Set_Service_PerOI(Str_Comm_698_RW *pV_698RWPara,Str_Comm_645 *pV_645Frame)
{
	uchar8	ReturnFlag = C_OtherErr_DAR;
	uchar8	V_ucOINum=0;

    if(pV_698RWPara->Wt_OI[0].Wt_Result == C_OK)
    {
		if(pV_698RWPara->ServiceFlag_Second != C_SETNormal_Request)/*��������һ���������Է�����������*/
		{
			pV_698RWPara->Wt_OI[0].Wt_Result = ReturnFlag;
			return ReturnFlag;
		}
		pV_698RWPara->ResponedNum = 0;
		ReturnFlag = SF_SetPerOI(pV_698RWPara,V_ucOINum,pV_645Frame);
		pV_698RWPara->Wt_OI[0].Wt_Result = ReturnFlag;
    }
    else
    {
        ReturnFlag = pV_698RWPara->Wt_OI[0].Wt_Result;
    }
    pV_698RWPara->ResponedNum = 0;
	return ReturnFlag;

}
/*******************************************************************************
����ԭ�ͣ�void SF_Set_Service_MultiOI(Str_Comm_698_RW *pV_698RWPara,Str_Comm_645 *pV_645Frame)
�����������ͻ������ö���������Ժ���
���������Str_Comm_698_RW�ж�Ӧ��ȡ���ݶ���OI���������͵�
���������pV_698RWParaдOI�����ý�������óɹ�Ϊ0������ʧ��������Ӧ������ʧ��ԭ��
���ز����������Ƿ���ȷ��C_OK��ʾ��ȡ�ɹ���������ʾ�������
����λ�ã�
��    ע��
*******************************************************************************/
void SF_Set_Service_MultiOI(Str_Comm_698_RW *pV_698RWPara,Str_Comm_645 *pV_645Frame)
{
	uchar8	i;

	pV_698RWPara->ResponedNum = 0;
	for(i=0;i<(pV_698RWPara->RWOI_Num);i++)
	{
		/**OI-DI*/
        if(pV_698RWPara->Wt_OI[i].Wt_Result == C_OK)
        {
			SF_SetPerOI(pV_698RWPara,i,pV_645Frame);
        }
		pV_698RWPara->ResponedNum++;
	}
	return;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_SetRd_Service_MultiOI(Str_Comm_698_RW *pV_698RWPara,uchar8 *pV_DataBuf,uchar8 V_BufLen,uchar8 *pV_NextFrFlag,Str_Comm_645 *pV_645Frame)
�����������ͻ������ú��ȡ�������Ժ�����������ֻ���ã���ȡ�ں������⺯���д���
���������Str_Comm_698_RW�ж�Ӧ��ȡ���ݶ���OI���������͵�
���������pV_698RWParaдOI�����ý�������óɹ�Ϊ0������ʧ��������Ӧ������ʧ��ԭ��
���ز����������Ƿ���ȷ��C_OK��ʾ��ȡ�ɹ���������ʾ�������
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_SetRd_Service_MultiOI(Str_Comm_698_RW *pV_698RWPara,uchar8 *pV_DataBuf,uchar8 V_BufLen,uchar8 *pV_NextFrFlag,Str_Comm_645 *pV_645Frame)
{
	uchar8	ReturnFlag = C_OtherErr;
	uchar8	i;

	pV_698RWPara->ResponedNum = 0;
	for(i=0;i<(pV_698RWPara->RWOI_Num);i++)
	{
		/*OI-DI*/
        if(pV_698RWPara->Wt_OI[i].Wt_Result == C_OK)
        {
			ReturnFlag = SF_SetPerOI(pV_698RWPara,i,pV_645Frame);
        }
		pV_698RWPara->ResponedNum++;

	}
	SV_ReadAfterSetTimer = (pV_698RWPara->W_R_DelayTime)*2;
	return ReturnFlag;
}
/*******************************************************************************
����ԭ�ͣ�void Set_Service_Deal(Str_Comm_698_RW *pV_698RWPara,uchar8 *pV_DataBuf,ushort16 V_BufLen,uchar8 *pV_NextFrFlag,Str_Comm_645 *pV_645Frame)
����������д��������
���������pV_698RWPara�����OI��Žṹ�壬pV_DataBufΪ�������
				V_BufLenΪ���ݳ��ȣ�pV_NextFrFlagΪ������־����������Ŀǰû�к���
�����������
���ز�������ַ����
����λ�ã�
��    ע��
*******************************************************************************/
void Set_Service_Deal(Str_Comm_698_RW *pV_698RWPara,uchar8 *pV_DataBuf,ushort16 V_BufLen,uchar8 *pV_NextFrFlag,Str_Comm_645 *pV_645Frame)
{
	switch(pV_698RWPara->ServiceFlag_Second)
	{
		case C_SETNormal_Request:
			SF_Set_Service_PerOI(pV_698RWPara,pV_645Frame);
			break;
		case C_SETNormalList_Request:
			SF_Set_Service_MultiOI(pV_698RWPara,pV_645Frame);
			break;
		case C_SETGETNormalList_Request:
			SF_SetRd_Service_MultiOI(pV_698RWPara,pV_DataBuf,V_BufLen,pV_NextFrFlag,pV_645Frame);
			break;
		default:
			break;
	}
	Comm_AppendMsg(CMsg_Txd);
}
/*******************************************************************************
����ԭ�ͣ�uchar8 S_ValidCheck(uchar8 *p_Data,Str_Comm_645 *pV_645Frame)
����������һ������Ϸ����ж�
���������	p_Data:	������������׵�ַ
�����������
���ز�����Ӧ��ɹ�:C_OK;��ȫ��֤ʧ��:C_SCErr_DAR;��������:C_Error;
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 S_ValidCheck(uchar8 *p_Data,Str_Comm_645 *pV_645Frame)
{
	uchar8	buf[CLen_S_BufMaxLen]={0};
	uchar8	ValidDataLen, V_ucParaOffset;
	ushort16 V_usDataLen;
	uchar8 V_ucI, V_ucTemp[12], V_ucJ;
	ulong32 V_ulTemp;

	V_usDataLen = SF_GetLengthFieldLen(p_Data, &V_ucParaOffset);

	pV_645Frame->DI = PF_Buffer4ToUlong32_698(p_Data+V_ucParaOffset);
	pV_645Frame->DataLen = V_usDataLen - 5;				/*ȥ��OAD���ȣ����ж����ݺϷ���*/
	PF_CopyDataBytes(p_Data+V_ucParaOffset+5, buf, pV_645Frame->DataLen);/*ȡ���ж�����*/

	if( JudgeMeterType(pV_645Frame->DI) != C_OK )/*�жϱ���*/
	{
		return(C_ObjectNotExist_DAR);
	}

	if(InF_JudgeKeyStatus() == C_StateOfOfficialKey)	/*˽Կ�²��������ñ�š��ͻ����*/
	{
		if((pV_645Frame->DI == CCustomer_Num)||(pV_645Frame->DI == CMeter_Num))
		{
			return(C_RWForbid_DAR);
		}
	}
/*�Ƿ�Ϊ1��������ж�*/
	if(InF_S_Is_ParmPlainTextMAC(pV_645Frame->DI,&ValidDataLen) != C_OK)
	{
		return(C_RWForbid_DAR);
	}

	if(InF_JudgeIJTimer() != C_OK)   /*����.*/
	{
		switch( ( pV_645Frame->DI ) & 0xFFFFFF00 )
		{
			case	CCurrent_RateFF_Price:  /*��ǰ�׷��ʱ�*/
			case	CCurrent_Ladder_Table:  /*��ǰ�׽��ݱ�*/
			{
				return(C_Unauthorized_DAR);
			}

			default:
			break;					        /*ע��������break������һ���ж�*/
		}
	}

/*�ж�������Ч��.*/
	if( ( pV_645Frame->DI == CChange_Rate ) || ( pV_645Frame->DI == CChange_Ladder ) )
	{
		PF_OneDataReversed(buf, buf, pV_645Frame->DataLen);	/*���->С��*/
		if( ( PF_Is_Buf_AllFixedData( buf, 0x00, 5 ) == C_OK )
		|| ( PF_Is_Buf_AllFixedData( buf, 0x99, 5 ) == C_OK )
		|| ( PF_Is_Buf_AllFixedData( buf, 0xFF, 5 ) == C_OK )				/*�л�ʱ�������0XFF*/
		|| ( PF_DataTimeActive( buf, C_DT_Start_mm, 5 ) == C_OK ) )
		{
			return(C_OK);
		}
		else
		{
			return(C_OtherErr_DAR);
		}
	}
	else if(pV_645Frame->DI == CBackUp_Ladder_Table)
	{
		/*����ֵ�ͽ��ݵ���Ƿ�ΪBCD���ж�*/
		if( PF_Judge_BCD(52,buf ) != C_OK )
		{
			return(C_OtherErr_DAR);
		}
		DataReversed(CBackUp_Ladder_Table,buf,17);	/*���->С��*/
/*���ݱ�Ϸ����жϺ�06�����һ������InF_DV_Ladder����Ҫ��bcd��ʽת��Ϊhex��ʽ*/
		for(V_ucI = 0; V_ucI < (6 + 7); V_ucI ++)
		{
			PF_BCDtoHexBytes( &buf[V_ucI*4], &V_ulTemp, 4 );
			PF_Ulong32ToBuffer4( &buf[V_ucI*4], &V_ulTemp, 4 );
		}
		PF_CopyDataBytes( &buf[52], V_ucTemp, 12 );/*ȡ���ж�����*/
		for(V_ucI = 0; V_ucI < 4; V_ucI ++)
		{
			buf[52 + V_ucI*3] = V_ucTemp[V_ucI*3 + 2];	
			buf[52 + V_ucI*3 + 1] = V_ucTemp[V_ucI*3 + 1];	
			buf[52 + V_ucI*3 + 2] = V_ucTemp[V_ucI*3];	
			for( V_ucJ = 0; V_ucJ < 3; V_ucJ++ )
			{
				if( buf[52 + V_ucI*3 + V_ucJ] != 0xFF )
				{
					if( PF_Judge_BCD(1,&buf[52 + V_ucI*3 + V_ucJ] ) != C_OK )
					{
						return(C_OtherErr_DAR);
					}	
					buf[52 + V_ucI*3 + V_ucJ] = PF_BCDtoHexOneByte(buf[52 + V_ucI*3 + V_ucJ]);
				}	
			}	
		}
		if( InF_DV_Ladder( buf ) != C_OK )
		{
			return(C_OtherErr_DAR);
		}
		else
		{
			return(C_OK);
		}
	}
	else
	{
		/*�Ƿ�ΪBCD���ж�*/
		if( PF_Judge_BCD(pV_645Frame->DataLen,buf ) != C_OK )
		{
			return(C_OtherErr_DAR);
		}
		else
		{
			return C_OK;	
		}		
	}
}

/********************************************************************************************
��������uchar8 Action_Service_PerOI(Str_Comm_698_RW *pV_698RWPara, Str_Comm_645 *pV_645Frame)
����˵�����ͻ��˲���һ���������Ժ���
���������Str_Comm_698_RW�ж�Ӧ��ȡ���ݶ���OI���������͵�
���������pV_698RWParaдOI�����ý�������óɹ�Ϊ0������ʧ��������Ӧ������ʧ��ԭ��
���ز����������Ƿ���ȷ��C_OK��ʾ��ȡ�ɹ���������ʾ�������
����λ�ã�
��    ע��
*********************************************************************************************/
#define C_EsamReturnDataLen	512		/*��ʱ��512���ֽڣ��������esam�ļ��и������ļ�����Ҫ��������*/
uchar8 Action_Service_PerOI(Str_Comm_698_RW *pV_698RWPara, Str_Comm_645 *pV_645Frame)
{
	uchar8 V_ucj, buf[10];
	uchar8 V_ucReturnFlag = C_Error;
	Str_Type645DI_Class V_DIFor645[2] = {0};
	uchar8 V_645DINum, V_ucActionNO, V_ucOffset;
	ushort16 V_ESAMDataLen, V_ucDataLen, V_usDataEncode,V_usLen = C_EsamReturnDataLen;
	ulong32 V_ulLastDI = 0xFFFFFFFF;
	ulong32 V_ulNextDI = 0xFFFFFFFF;
	uchar8 V_ucFlag = 0;
    uchar8 V_ucDI[4];
    uchar8 V_ucCode[4];
    ulong32 V_ulDI;
    ushort16 V_BufRemainLen;
    uchar8 V_ucParaOffset;
    ulong32 V_ulAction_OAD_Temp;
    uchar8	V_ucData[C_EsamReturnDataLen];

    if(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Result !=  C_OK)
	{
		pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen = 0;
		return pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Result;
	}

	V_ucReturnFlag = SF_Judge_OINature(pV_698RWPara,V_DIFor645, &V_645DINum, C_Operation);  /*����*/
	V_DIFor645->V_ucOAD = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI;
	if(V_ucReturnFlag != C_OK)
	{
		pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Result = V_ucReturnFlag;
		pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen = 0;
		return V_ucReturnFlag;
	}

    pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Result = JudgeMeterType(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI);
    if(pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Result != C_OK)    				/*�ж��Ƿ��Ǳ��ر������*/
    {
		V_ucReturnFlag = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Result;

		pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen = 0;
		return V_ucReturnFlag;
    }

	if((V_DIFor645->V_ucOAD & 0xFFFF0000) == 0xF1000000)									/*ESAM��ز���*/
	{
		/*дһ����������ݺϷ��Ե��ж�*/
		if((V_DIFor645->V_ucOAD & 0xFFFFFF00) == 0xF1000400)
		{
			V_ucReturnFlag = S_ValidCheck(&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0], pV_645Frame);
			if(V_ucReturnFlag != C_OK)
			{
				pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Result = V_ucReturnFlag;
				pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen = 0;
				return V_ucReturnFlag;
			}
		}

        V_BufRemainLen = CLKey_State_698;
        InF_GetData_ObjectManage(CKey_State, GV_KeyHState, &V_BufRemainLen, &V_usDataEncode);				/*��ȡESAM����Կ�汾��Ϣ*/

        V_ESAMDataLen = 0;  /*���ݻس�����ļ������ȴ���255*/
		V_ucReturnFlag = INF_S_ActionEsam_698(V_DIFor645->V_ucOAD,&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0], &V_ESAMDataLen, V_ucData, &V_usLen, SV_Comm_Parse_Local.ClientAddrFlag);
		if( V_ucReturnFlag != C_OK )		/*�����ȫģ��Ӧ��ʧ�ܣ�����ֱ�Ӹ�ֵΪ0*/
		{
			V_usLen = 0;
		}
		pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Result = V_ucReturnFlag;
		pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen = V_usLen;
		if( V_DIFor645->V_ucOAD != 0xF1000400 )
		{
			PF_CopyDataBytes_698(&V_ucData[0], &pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0], V_usLen);	
		}
		if(V_ucReturnFlag == C_OK)
		{
			V_ucActionNO = (uchar8)(V_DIFor645->V_ucOAD >> 8);
			switch(V_ucActionNO)
			{
				case C_ESAMAction_NO4:	/*��������*/
				{
					/*���ʱ����128�ֽڣ�����125�ֽ�*/
					V_ucDataLen = SF_GetLengthFieldLen(&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0], &V_ucParaOffset);  

					V_ulAction_OAD_Temp = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI;
					
					pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI = PF_Buffer4ToUlong32_698(&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[V_ucParaOffset]);

					pV_645Frame->DI = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI;
					V_ucDataLen = (uchar8)V_usLen;
                    V_ucOffset = 0;
					if( pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI == CAlam_Money )
					{
						for( V_ucj = 0; V_ucj < 2; V_ucj++ )
						{
							pV_645Frame->DI = pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI + 0x00000001 + V_ucj;
							V_ucDataLen = 4;
							SF_CombDataTo645Type_W(&V_ucData[V_ucOffset], pV_645Frame, V_ucDataLen);

							V_ucOffset += V_ucDataLen;
							if( V_ucj == 1 )
							{
								V_ucFlag = C_NeedWriteEventRecord;	
							}
							else
							{
								V_ucFlag = C_NotWriteEventRecord;		
							}
							V_ucReturnFlag = SF_SetParm(pV_645Frame, V_ulLastDI, V_ulNextDI, V_ucFlag, pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI, C_Operation);

							if(V_ucReturnFlag !=C_OK)
							{
								break;
							}
						}	
					}
					else
					{
						SF_CombDataTo645Type_W(V_ucData,pV_645Frame, V_ucDataLen);
						V_ucFlag=C_NeedWriteEventRecord;
						V_ucReturnFlag = SF_SetParm(pV_645Frame,V_ulLastDI,V_ulNextDI, V_ucFlag, pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI, C_Operation);	
					}

					pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen = 0;
					pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Result = V_ucReturnFlag;
					pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI = V_ulAction_OAD_Temp;

				}break;
				case C_ESAMAction_NO6:	/*Ǯ������(��������ֵ���˷�)*/
				{

					pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen = 0;

					if(MoneyClient_Table.V_CanRecharge == C_Can_EPurchase)	/*���Գ�ֵ*/
					{
						InF_PurchaseDL(MoneyClient_Table.V_ulMoney, C_W_SafeFlag);
					}

					if(MoneyClient_Table.V_ucOpenFlag == 2)
					{
						ReturnMoney_698();
					}
					/*����Զ�̿�����־��ͬʱд���ݲ�ͻ����*/
					if(MoneyClient_Table.V_ucOpenFlag == 0)
					{
						InF_Write_Data(C_Msg_Communication, CCustomer_Num, (uchar8 *)&(MoneyClient_Table.V_ucClientNum), CLCustomer_Num, C_W_SafeFlag);
						InF_DealWith_L_R_OAAFlag(C_Set_Method_R, C_HaveOpenAnAccount);
					}

				}break;
				case C_ESAMAction_NO7:	/*��Կ����*/
				{
                    pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen = 0;

					if(InF_JudgeKeyStatus() == C_StateOfOfficialKey)
					{   /*ȫ��ʽ��Կ����C_PublicKeySign��*/
						Comm_SendMsgToDisp(C_PublicKeySign, C_NotDisplay, C_Duration_Alway);
					}
					else
					{   /*��C_PublicKeySign��*/
						Comm_SendMsgToDisp(C_PublicKeySign, C_AlwaysDisplay, C_Duration_Alway);
					}
					pV_645Frame->DI = 0xFFFFFFFF;
					SV_Comm_Parse_Local.SafeControlFlag = SV_Comm_Parse_Local.SafeControlFlag | C_W_SafeFlag_3;
					Have_IPEvent_Prog_698(CProgKD_Note_1,CProgKD_Degree, pV_645Frame);
                    Inf_EventReport_HP(C_Key_UpdateEventNo, C_Happen_EventReport);
				}break;
				case C_ESAMAction_NOA:	/*Ǯ����ʼ��*/
				{
                    InF_S_GetMeterNum_ReworkDL();   /*698esamǮ����ʼ�����esam�ڿͻ����ֱ�ӳ�ʼ��Ϊ0,ͬ������esam�еĿͻ����*/
                    /*Ǯ����ʼ��������Ҫ��Զ�̡����ؿ���״̬���忨Ƭ���к�*/
                    memset(buf, 0x00, CL_UserCardNo);
					InF_Write_Data(C_Msg_Communication, C_UserCardNo, buf, CL_UserCardNo,C_W_SafeFlag);

					InF_DealWith_L_R_OAAFlag(C_Set_Method_L, C_HaveNoOpenAnAccount);
					InF_DealWith_L_R_OAAFlag(C_Set_Method_R, C_HaveNoOpenAnAccount);

					SF_MeterInit();
					
				}break;
				case C_ESAMAction_NO5:								/*Э��ʧЧ*/
				{
					PF_CopyDataBytes_698(&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[1], buf, pV_698RWPara->Wt_OI[0].DataLen);
					pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen=SF_DataExchangeTo698_BasicData(&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0], &buf[0], 8, 6);
					pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen += 1;
					pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Result = C_OK;
					V_ucReturnFlag = C_OK;

					/*ֻЭ��ʧЧ�ͻ�����һ·��Ӧ������*/
					if(SV_Comm_Parse_Local.ClientAddrFlag == Termal_Address)
					{
                        Com_Conect.ConectOverTime_termal = 0;		/*����Ӧ������ʣ��ʱ������*/
					}
					else
					{
						Com_Conect.ConectOverTime = 0;		        /*����Ӧ������ʣ��ʱ������*/
					}


            		Com_Conect.CRC16 = PF_Cal_CRC((uchar8 *)&Com_Conect.ConectOverTime, C_ConectStruct_Len);		/*����Ӧ������ʱ��*/

					RELEASE_Service_Deal(SV_Comm_Parse_Local.ClientAddrFlag);
				}break;
				case C_ESAMAction_NOB:	/*������֤����*/
				{
					/*�������ú�����֤ʱЧΪ��Ч*/
					memset( buf, 0, C_TimerExceed10minLen );
					if(SV_Comm_Parse_Local.ClientAddrFlag == Termal_Address)		/*�ն������֤*/
					{
						DealWith_ID_Auth_T_Timer(C_Set_TimerExceed10min, &buf[0]);
					}
					else
					{
						DealWith_IR_Auth_Timer(C_Set_TimerExceed10min, &buf[0]);
					}

					/*������֤���������֤ʧЧ*/
					if(SV_Comm_Parse_Local.ClientAddrFlag != Termal_Address)		/*�ն������֤�ɹ����ʧЧԭ����Ӧ�����ӣ������֤����ʱ���ı�ԭ������״̬*/
					{
						InF_JudgeESAMConTimer(C_ResetDealConectTime, SV_Comm_Parse_Local.ClientAddrFlag);		/*��״̬��3ˢ��*/
					}

				}break;
				case C_ESAMAction_NOC:												/*������֤*/
				{
					/*ֻ�嶨ʱ�����ܸ�λesam,�����������֤֮������+���������mac����6985*/
					InF_JudgeESAMConTimer(C_ResetDealConectTime,SV_Comm_Parse_Local.ClientAddrFlag);			/*��״̬��3ˢ��*/
				}break;
				case C_ESAMAction_NO9:	/*����Э��ʱЧ(��վ+�ն�)+�����ն˵�ַ+�㲥������+�����֤����Ȩ��*/
				{
					if(GV_ESAMAction9_SIDP1P2 ==C_SID_P1P2_01)						/*������վЭ��ʱЧ*/
					{
						/*ɾ��ԭ����ȡesam�е�ʣ��ʱ�䣬���溯����ͳһ����*/
						InF_JudgeESAMConTimer(C_SynDealConectTime, Master_Address);									/*ˢ��RAM��ESAMʣ��ʱ��*/
					}
					else if(GV_ESAMAction9_SIDP1P2 == C_SID_P1P2_04)												/*�����ն�Э��ʱЧ*/
					{
						/*ɾ��ԭ����ȡesam�е�ʣ��ʱ�䣬���溯����ͳһ����*/
						InF_JudgeESAMConTimer(C_SynDealConectTime, Termal_Address);									/*ˢ��RAM��ESAMʣ��ʱ��*/
					}
					else if(GV_ESAMAction9_SIDP1P2 == C_SID_P1P2_07)												/*����ն������֤ʱЧʣ��ʱ��*/
					{
						memset( buf, 0, C_TimerExceed10minLen );
						DealWith_ID_Auth_T_Timer(C_Set_TimerExceed10min, &buf[0]);
					}
					V_ulDI = 0xF1000900;
					PF_Ulong32ToBuffer4(V_ucDI, &V_ulDI, 4);
					INF_Append_ProgRecordDI(V_ucCode,V_ucDI, &SV_Comm_Parse.ProgRecord, pV_698RWPara->ServiceFlag_First);

				}break;
				default :
				{
					break;
				}
			}
		}

	}
	else if((V_DIFor645->V_ucOAD & 0xFFFF0000) == 0xFF860000)	/*����������*/
	{
		V_ucActionNO = (uchar8)(V_DIFor645->V_ucOAD >> 8);
		if( (V_ucActionNO >= 128) && (V_ucActionNO <= 130) )
		{
			V_ucReturnFlag = InF_Write_Data(C_Msg_Communication, V_DIFor645->V_ucOAD,&pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Data[0], V_DIFor645->DataLen_645[0], C_W_SafeFlag);
		}
		else
		{
			;
		}
        pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen = 0;
		pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].Wt_Result = V_ucReturnFlag;
	}
	else
	{
		pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].DataLen = 0;
		V_ucReturnFlag = SF_ActionPerOI(pV_698RWPara, pV_645Frame, pV_698RWPara->ResponedNum);
	}
	return V_ucReturnFlag;
}
/*******************************************************************************
����ԭ�ͣ�void Action_Service_Read_MultiOI(Str_Comm_698_RW *pV_698RWPara,Str_Comm_645 *pV_645Frame)
�����������ͻ��˲������ȡ�������Ժ���������ֻ��������ȡ�ٺ��溯������
���������Str_Comm_698_RW�ж�Ӧ��ȡ���ݶ���OI���������͵�
���������pV_698RWParaдOI�����ý�������óɹ�Ϊ0������ʧ��������Ӧ������ʧ��ԭ��
���ز����������Ƿ���ȷ��C_OK��ʾ��ȡ�ɹ���������ʾ�������
����λ�ã�
��    ע��
*******************************************************************************/
void Action_Service_Read_MultiOI(Str_Comm_698_RW *pV_698RWPara,Str_Comm_645 *pV_645Frame)
{
	uchar8	i;

	pV_698RWPara->ResponedNum = 0;
	for(i=0;i<(pV_698RWPara->RWOI_Num);i++)
	{
        if(pV_698RWPara->Wt_OI[i].Wt_Result == C_OK)
        {
            Action_Service_PerOI(pV_698RWPara,pV_645Frame);
        }
		pV_698RWPara->ResponedNum++;
	}
}
/*******************************************************************************
����ԭ�ͣ�void Action_Service_MultiOI(Str_Comm_698_RW *pV_698RWPara,Str_Comm_645 *pV_645Frame)
�����������ͻ��˲�������������Ժ���
���������Str_Comm_698_RW�ж�Ӧ��ȡ���ݶ���OI���������͵�
���������pV_698RWParaдOI�����ý�������óɹ�Ϊ0������ʧ��������Ӧ������ʧ��ԭ��
���ز����������Ƿ���ȷ��C_OK��ʾ��ȡ�ɹ���������ʾ�������
����λ�ã�
��    ע��
*******************************************************************************/
void Action_Service_MultiOI(Str_Comm_698_RW *pV_698RWPara,Str_Comm_645 *pV_645Frame)
{
	uchar8	i;

	pV_698RWPara->ResponedNum = 0;
	for(i=0;i<(pV_698RWPara->RWOI_Num);i++)
	{
        if(pV_698RWPara->Wt_OI[i].Wt_Result ==  C_OK)
        {
            Action_Service_PerOI(pV_698RWPara,pV_645Frame);
        }
		pV_698RWPara->ResponedNum++;
	}
}
/*******************************************************************************
����ԭ�ͣ�uchar8 ActionRd_Service_MultiOI(Str_Comm_698_RW *pV_698RWPara,uchar8 *pV_DataBuf,uchar8 V_BufLen,
			uchar8 *pV_NextFrFlag,Str_Comm_645 *pV_645Frame)
�����������ͻ��˲���һ���������Ժ���
���������Str_Comm_698_RW�ж�Ӧ��ȡ���ݶ���OI���������͵�
���������pV_698RWParaдOI�����ý�������óɹ�Ϊ0������ʧ��������Ӧ������ʧ��ԭ��
���ز����������Ƿ���ȷ��C_OK��ʾ��ȡ�ɹ���������ʾ�������
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 ActionRd_Service_MultiOI(Str_Comm_698_RW *pV_698RWPara,uchar8 *pV_DataBuf,uchar8 V_BufLen,uchar8 *pV_NextFrFlag,Str_Comm_645 *pV_645Frame)
{
	uchar8	i;
	uchar8	ReturnFlag = C_OtherErr_DAR;

	pV_698RWPara->ResponedNum = 0;
	for(i=0;i<(pV_698RWPara->RWOI_Num);i++)
	{
		ReturnFlag = SF_ActionPerOI(pV_698RWPara,pV_645Frame,i);
		pV_698RWPara->ResponedNum++;
	}
	SV_ReadAfterSetTimer = (pV_698RWPara->W_R_DelayTime)*2;
	return ReturnFlag;
}
/*******************************************************************************
����ԭ�ͣ�void Action_Service_Deal(Str_Comm_698_RW *pV_698RWPara,uchar8 *pV_DataBuf,
			ushort16 V_BufLen,uchar8 *pV_NextFrFlag,Str_Comm_645 *pV_645Frame)
�����������ͻ��˲�������
���������pV_698RWPara�����OI��Žṹ�壬pV_DataBufΪ�������
				V_BufLenΪ���ݳ��ȣ�pV_NextFrFlagΪ������־�����ڲ���Ŀǰû�к���
���������ͨ��ȫ�ֱ���������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
void Action_Service_Deal(Str_Comm_698_RW *pV_698RWPara,uchar8 *pV_DataBuf,ushort16 V_BufLen,uchar8 *pV_NextFrFlag,Str_Comm_645 *pV_645Frame)
{
	*pV_NextFrFlag = 0;

	pV_698RWPara->ResponedNum = 0;
	switch(pV_698RWPara->ServiceFlag_Second)
	{
		case C_ACTIONNormal_Request:
			Action_Service_PerOI(pV_698RWPara,pV_645Frame);
			break;
		case C_ACTIONNormalList_Request:
			Action_Service_MultiOI(pV_698RWPara,pV_645Frame);
			break;
		case C_ACTIONGETList_Request:
			Action_Service_Read_MultiOI(pV_698RWPara,pV_645Frame);
			break;
		default:
			break;
	}
	Comm_AppendMsg(CMsg_Txd);
}
/*******************************************************************************
����ԭ�ͣ�void SF_DemandClear(void)
��������������������������Ӧ��
���������
�����������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
void SF_DemandClear(void)
{
	uchar8	MsgData[2];

	/*��������ɹ�,����������Ϣ��ͬʱ����������ɹ���������Ӧģ��*/
	SV_Comm_Parse_Local.SafeControlFlag = SV_Comm_Parse_Local.SafeControlFlag|C_W_SafeFlag_3;
	Comm_AppendMsg(CMsg_DemandClear);

	MsgData[0] = Pt_DemandStatus;
	MsgData[1] = C_DemandClear;
	Comm_SendMsg(MsgData, (Pt_DemandStatus_Len+1), C_Msg_DemandMetering);
	InF_ActiveReportSetting(C_Times_DemandClear);		/*���������ϱ�����*/
	Inf_EventReport_HP(C_DemandClearEventNo,C_Happen_EventReport);
}
/*******************************************************************************
����ԭ�ͣ�void	SF_MeterInit(void)
����������ͨ���������Ǯ����ʼ���ȵ���
�����������
�����������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
void	SF_MeterInit( void )
{
	uchar8	MsgData;

	SV_Comm_Parse_Local.MeterClearFlag = SV_Comm_Parse_Local.MeterClearFlag |C_ClearMeterSafeFlag_1;
	SV_Comm_Parse_Local.MeterClearFlag = SV_Comm_Parse_Local.MeterClearFlag |C_W_SafeFlag_2;

	/*��������Ϸ����жϳɹ�*/
	SV_Comm_Parse_Local.MeterClearFlag = SV_Comm_Parse_Local.MeterClearFlag |C_ClearMeterSafeFlag_3;
	SV_Comm_Parse_Local.SafeControlFlag = SV_Comm_Parse_Local.SafeControlFlag|C_W_SafeFlag_3;
	Comm_AppendMsg(CMsg_MeterClear);
	/*������Ҫ��������Ϣ,�����ۣ����㲥����*/
	MsgData = Pt_MeterClear;
	Comm_SendMsg(&MsgData, (Pt_MeterClear_Len+1), C_Msg_BroadcastAddress);

	Clear_BDSC_RecentClock();						/*�㲥Уʱʱ������*/
  
/*2020��׼�����ϱ�2005*/
	Inf_Comm_ClearModuleCommuniFlag(0xF0);  		/*ͨ�ű�ʶ����*/
	Inf_Comm_REPORTFlagClear(0);        			/*�����ϱ�����*/
	Inf_Event_REPORTONumDeal(0);            		/*�����ϱ�����*/
}

/*******************************************************************************
����ԭ�ͣ�void	SF_MeterClear(Str_Comm_645 *pV_645Frame)
����������ͨ���������������Ӧ��
���������*pV_645Frame				:���յ�������֡
�����������
���ز�����
����λ�ã�
��    ע��MeterClearFlag��־�ڱ���������2������2��Ȩ���жϺ�������һ��
*******************************************************************************/
void	SF_MeterClear(Str_Comm_645 *pV_645Frame)
{
	SF_MeterInit();
	MoneyClient_Table.V_ulMoney = 0;				/*���ر���ʼ���Ϊ0*/
/*****��ͨ��֡��Զ��Ǯ����ʼ�������Ӧ����buffer����,��ֹ��������ΪԤ�ý��д��ʣ����******/
	memset(&pV_645Frame->Data[CData_OtherO_V_645+C_InitM_O_ChgBlHC], 0, 4);    
}

/*******************************************************************************
����ԭ�ͣ�uchar8 SF_EventClear(Str_Comm_645 *pV_645Frame,ulong32 V_ulOAD)
��������������¼��������������Ӧ��
���������*pV_645Frame				:���յ�������֡��V_ulOAD������������¼�OMD
�����������
���ز�����C_OtherErr:��־�����C_OK������ɹ���
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_EventClear(Str_Comm_645 *pV_645Frame,ulong32 V_ulOAD)
{
	uchar8	Err,i,V_CommMsgNo;
	uchar8	MsgData[Pt_EventClearDI_Len+1];
	ulong32	EventDI;

/*�߼��жϺ󣬽�����Ӧ�¼�������Ӧ��*/
	Err = C_OK;
	PF_Buffer4ToUlong32(&pV_645Frame->Data[C_O_EventClear_DI], &EventDI, CLen_DI);

	if((InF_EventNumFind(EventDI)!=C_IDError)||(EventDI == 0xFFFFFFFF))
	{
		/*�¼���¼���������жϺϷ�*/
		SV_Comm_Parse_Local.SafeControlFlag = SV_Comm_Parse_Local.SafeControlFlag|C_W_SafeFlag_3;

		/*�¼���������ɹ�,������Ϣ��ͬʱ������ɹ���������Ӧģ��*/
		Comm_AppendMsg(CMsg_EventClear);
		MsgData[0] = Pt_EventClearDI;
		PF_CopyDataBytes(&pV_645Frame->Data[C_O_EventClear_DI],&MsgData[1],4);
		Comm_SendMsg(MsgData,(Pt_CodeID_Len+1), C_Msg_PowerNetworkMonitoring);
		Comm_SendMsg(MsgData, (Pt_CodeID_Len+1), C_Msg_Deal_RelayStatus);
		Comm_SendMsg(MsgData, (Pt_CodeID_Len+1), C_Msg_Dispatch);
		/*��RAM�б�̼�¼����*/
		/*ֻ���¼���¼����������̼�¼��ʱ��Ž���̼�¼���г�ʼ��*/
		if((EventDI == 0xFFFFFFFF)||(((EventDI&0xFFFFFF00) == CProgram_Degree)))
		{
			INF_Init_Str_ProgRecord(&SV_Comm_Parse.ProgRecord);
		}
        if(EventDI == 0xFFFFFFFF)
        {
        	Inf_CleanAllMeterStatus8();
            Inf_NewReport(C_ReportChannelAll,C_EventClearEventNo,C_CleanOtherEvent);
            Inf_Event_REPORTONumDeal(0);            /*�����ϱ�����*/
            /*��������ѷ����ϱ��������¼����㣬������������*/
            SF_Clear645_ReportNewAddNum(C_EventClearEventNo,C_EventCLEAR);
            InF_ActiveReportSetting(C_Times_EventClear);
		}
        else
        {
            Inf_NewReport(C_ReportChannelAll,C_EventClearEventNo,C_JustAddECleanNo);
            InF_ActiveReportSetting(C_Times_EventClear);
        }
	}
	else
	{
		/*������¼�DI����*/
		Err = C_OtherErr;
	}
		/*�����ڲ���Ϣ��־�����ж�Ӧ����Ϣ����*/
	for(i=0;i<C_MessageMaxNum;i++)
	{
		V_CommMsgNo = Comm_FetchMsg();
		if(V_CommMsgNo == CMsg_Null)
		{
			break;
		}
		switch(V_CommMsgNo)
		{
			case		CMsg_EventClear:			/*�¼���¼������Ϣ����*/
				InF_EventNote_Clear(C_Msg_Communication, EventDI, SV_Comm_Parse_Local.SafeControlFlag);
				if(V_ulOAD != 0x00000000)
				{
					Have_IPEvent_EventClear(pV_645Frame,V_ulOAD);
				}
				break;
			default:
				break;
		}
	}

	return Err;
}
/*******************************************************************************
����ԭ�ͣ�uchar8	SF_BroadcastSetClock(Str_Comm_645 *pV_645Frame)
������������ɹ㲥Уʱ
���������*pV_645Frame				:���յ�������֡
�����������
���ز�����C_OKУʱ�ɹ�����������ֵ����������
����λ�ã�
��    ע��
*******************************************************************************/
uchar8	SF_BroadcastSetClock(Str_Comm_645 *pV_645Frame)
{
	uchar8	V_SystemDate_Time[CLDate_Time] = {0};
	uchar8	V_CMPDate_Time[20] = {0};	/*֮ǰ�Ƕ��㲥Уʱ�쳣�¼����Ի��濪200������ֻ��ʱ��*/
	uchar8	Err = C_OK;
	uchar8	Temp[4];
	ulong32 V_SecondDIFValue,TimeOffset_Min,TimeOffset_Max;
	uchar8	V_ucReturn;
	ushort16	DataLen, V_usDataEncode;
	uchar8	V_ucMsg[CLDate_Time*2 + 1];

/*��ϵͳʱ��*/
	DataLen = CLDate_Time;
	if(InF_Read_Data(CDate_Time, V_SystemDate_Time, &DataLen, &V_usDataEncode) != C_OK)
	{
		/*���ʱ�Ӷ�����������ֻ�ܽ���ʱ�����ã��޷��㲥Уʱ*/
		Err = C_OtherErr;
		return Err;
	}
/*�жϹ㲥Уʱʱ���Ƿ�Ϸ�*/
	if(PF_DataTimeActive_698(&pV_645Frame->Data[CBoardCastData_O_V_645 + C_ss_O], C_DT_Start_ss, CLDate_Time)	!= C_OK)
	{
		Err = C_OtherErr;
		return Err;
	}

	/*��ȡ��СУʱƫ��*/
	DataLen = CLBroadcastTimeOffset_Min;
	V_ucReturn = InF_Read_Data(CBroadcastTimeOffset_Min, &Temp[0], &DataLen, &V_usDataEncode);
	PF_Buffer4ToUlong32(Temp, &TimeOffset_Min, 2);
	if(V_ucReturn != C_OK)
	{
		TimeOffset_Min = 60;	/*Ĭ��60s*/
	}

	/*��ȡ���Уʱƫ��  */
	DataLen = CLBroadcastTimeOffset_Max;
	V_ucReturn = InF_Read_Data(CBroadcastTimeOffset_Max, &Temp[2], &DataLen, &V_usDataEncode);
	PF_Buffer4ToUlong32(&Temp[2], &TimeOffset_Max, 2);
	if( V_ucReturn != C_OK )
	{
		TimeOffset_Max = 300;	/*Ĭ��300s*/
	}

    PF_TimeSub_Second_698(&pV_645Frame->Data[CBoardCastData_O_V_645 + C_ss_O], V_SystemDate_Time, &V_SecondDIFValue);

	if( ( pV_645Frame->RNSICBit == 0x04 ) || ( pV_645Frame->RNSICBit == 0x08 ) )				/*����Уʱ*/
	{
        /*�жϵ�����û�й㲥Уʱ�������Ĺ㲥Уʱһ��һ�Ρ�*/
        if((SV_Comm_Parse.BDSC_RecentClock[CDate_Time_DD_O] ==  V_SystemDate_Time[CDate_Time_DD_O])
            &&(SV_Comm_Parse.BDSC_RecentClock[CDate_Time_MM_O] == V_SystemDate_Time[CDate_Time_MM_O])
            &&(SV_Comm_Parse.BDSC_RecentClock[CDate_Time_YYL_O] == V_SystemDate_Time[CDate_Time_YYL_O])
            &&(SV_Comm_Parse.BDSC_RecentClock[CDate_Time_YYH_O] == V_SystemDate_Time[CDate_Time_YYH_O]))
        {
            Err = C_OtherErr;
            return Err;
        }

		if( ( V_SecondDIFValue < TimeOffset_Min ) || ( V_SecondDIFValue > TimeOffset_Max ) )	/*С����СУʱƫ��,�������Уʱƫ��,����Уʱ����Ӧ*/
        {
            if(V_SecondDIFValue > TimeOffset_Max)		/*2020���ӣ����ķ�ʽ�㲥Уʱ���㲥Уʱ��Уʱ��Χ�������Уʱƫ���ʱ�ӹ��ϣ�*/
            {
				/*��ȡ��һ�ι㲥Уʱ�쳣����ʱ��*/
				DataLen = CLClock_FaultTime;
				InF_Read_Data(CClock_FaultTime, &V_CMPDate_Time[0], &DataLen, &V_usDataEncode);

				/*�㲥Уʱ�쳣�¼���¼һ������һ��*/
				if( ( V_CMPDate_Time[CDate_Time_DD_O] !=  V_SystemDate_Time[CDate_Time_DD_O] )
				|| ( V_CMPDate_Time[CDate_Time_MM_O] != V_SystemDate_Time[CDate_Time_MM_O] )
				|| ( V_CMPDate_Time[CDate_Time_YYL_O] != V_SystemDate_Time[CDate_Time_YYL_O] ) )
				{
					/*��¼ʱ�ӹ���״̬*/
					SF_SetRTCErrState(C_RTC_ERR);
					SF_Write_BroadTimeAbnormalTime(V_SystemDate_Time);							/*д���һ�ι㲥Уʱ�쳣ʱ�ӹ���ʱ��*/

				}
            }
            Err = C_OtherErr;
            return Err;
        }

        /*���Ĺ㲥Уʱ��׼���졣*/
        if( ( pV_645Frame->Data[CBoardCastData_O_V_645+CDate_Time_DD_O] !=  V_SystemDate_Time[CDate_Time_DD_O] )
		 || ( pV_645Frame->Data[CBoardCastData_O_V_645+CDate_Time_MM_O] !=  V_SystemDate_Time[CDate_Time_MM_O] )
		 || ( pV_645Frame->Data[CBoardCastData_O_V_645+CDate_Time_YYL_O] !=  V_SystemDate_Time[CDate_Time_YYL_O] )
		 || ( pV_645Frame->Data[CBoardCastData_O_V_645+CDate_Time_YYH_O] !=  V_SystemDate_Time[CDate_Time_YYH_O] ) )
        {
            Err = C_OtherErr;
            return Err;
        }
#if 0/****************�˴���������,Ϊ2020Э��Ը�����������,DB**********/
        /*�ж�ϵͳʱ���Ƿ���00:00�������Уʱƫ���������㲥Уʱ*/
        memset(&V_CMPDate_Time[C_ss_O], 0, 3);

        V_CMPDate_Time[CDate_Time_DD_O] = V_SystemDate_Time[CDate_Time_DD_O];
        V_CMPDate_Time[CDate_Time_MM_O] = V_SystemDate_Time[CDate_Time_MM_O];
        V_CMPDate_Time[CDate_Time_YY_O] = V_SystemDate_Time[CDate_Time_YY_O];

        PF_TimeSub_Second_698(V_CMPDate_Time, V_SystemDate_Time, &V_SecondDIFValue);

        if((V_SecondDIFValue < TimeOffset_Max)||(V_SecondDIFValue >= (86400-TimeOffset_Max)))
        {
            /*��㸽�����Уʱƫ��*/
            Err = C_OtherErr;
            return Err;
        }
#endif
        /*���Ĺ㲥Уʱ��׼������ա�*/
        DataLen = CLSettle_Day1;
        memset(&V_CMPDate_Time[C_ss_O],0x00,0x04);
        if( InF_Read_Data( CSettle_Day1, &V_CMPDate_Time[C_hh_O], &DataLen, &V_usDataEncode ) == C_OK )
		{
			if( ( ( PF_Campare_Data( &V_SystemDate_Time[C_ss_O], &V_CMPDate_Time[C_ss_O], 0x04 ) != C_GreaterThan )
                && ( PF_Campare_Data( &pV_645Frame->Data[CBoardCastData_O_V_645 + C_ss_O], &V_CMPDate_Time[C_ss_O], 0x04 ) != C_LessThan ) )
			 || ( ( PF_Campare_Data( &V_SystemDate_Time[C_ss_O], &V_CMPDate_Time[C_ss_O], 0x04) != C_LessThan)
               &&(PF_Campare_Data( &pV_645Frame->Data[CBoardCastData_O_V_645 + C_ss_O], &V_CMPDate_Time[C_ss_O], 0x04 ) != C_GreaterThan ) ) )
           {
                Err = C_OtherErr;
                return Err;
           }
		}
        if( InF_Read_Data( CSettle_Day2, &V_CMPDate_Time[C_hh_O], &DataLen, &V_usDataEncode ) == C_OK )
		{
			if( ( ( PF_Campare_Data(&V_SystemDate_Time[C_ss_O], &V_CMPDate_Time[C_ss_O], 0x04 ) != C_GreaterThan )
                && ( PF_Campare_Data(&pV_645Frame->Data[CBoardCastData_O_V_645 + C_ss_O], &V_CMPDate_Time[C_ss_O], 0x04) != C_LessThan ) )
			 || ( ( PF_Campare_Data(&V_SystemDate_Time[C_ss_O], &V_CMPDate_Time[C_ss_O], 0x04) != C_LessThan)
               &&(PF_Campare_Data(&pV_645Frame->Data[CBoardCastData_O_V_645 + C_ss_O], &V_CMPDate_Time[C_ss_O], 0x04) != C_GreaterThan ) ) )
           {
                Err = C_OtherErr;
                return Err;
           }
		}
        if( InF_Read_Data( CSettle_Day3, &V_CMPDate_Time[C_hh_O], &DataLen, &V_usDataEncode ) == C_OK )
		{
			if( ( ( PF_Campare_Data( &V_SystemDate_Time[C_ss_O], &V_CMPDate_Time[C_ss_O], 0x04 ) != C_GreaterThan )
                && ( PF_Campare_Data( &pV_645Frame->Data[CBoardCastData_O_V_645 + C_ss_O], &V_CMPDate_Time[C_ss_O], 0x04 ) != C_LessThan ) )
			  ||( ( PF_Campare_Data( &V_SystemDate_Time[C_ss_O], &V_CMPDate_Time[C_ss_O], 0x04 ) != C_LessThan )
               &&( PF_Campare_Data( &pV_645Frame->Data[CBoardCastData_O_V_645 + C_ss_O], &V_CMPDate_Time[C_ss_O], 0x04 ) != C_GreaterThan ) ) )
           {
                Err = C_OtherErr;
                return Err;
           }
        }
        /*ˢ�����һ�����Ĺ㲥Уʱʱ�䣬���Ĺ㲥Уʱһ��һ�Σ����Ĺ㲥Уʱ��������*/
        PF_CopyDataBytes(&pV_645Frame->Data[CBoardCastData_O_V_645 + C_ss_O], &SV_Comm_Parse.BDSC_RecentClock[C_ss_O], CLDate_Time);
    }
	else
    {
        if( ( pV_645Frame->RNSICBit == 0x01 ) || ( pV_645Frame->RNSICBit == 0x02 ) )	/*����Уʱ*/
        {
            if(V_SecondDIFValue < TimeOffset_Min)										/*С����СУʱƫ��,����Уʱ����Ӧ*/
            {
                Err = C_OtherErr;
                return Err;
            }
        }
        else
        {
            Err = C_OtherErr;
            return Err;
        }
    }

    /*д�㲥Уʱ�¼���¼*/
	pV_645Frame->DI = CBroadcastTimeM;
	pV_645Frame->DataLen = CLDate_Time+C_Data_OFS_14;
	SV_Comm_Parse_Local.SafeControlFlag = SV_Comm_Parse_Local.SafeControlFlag | C_W_SafeFlag_3;
    Have_IPEvent_Prog_698(CBroadcastTime_Note_1, CBroadcastTime_Degree, pV_645Frame);

	/*������Ϣ������ģ��*/
	Comm_SendMsgForUpdataParm(C_ReworkTime, C_Msg_DemandMetering);

	Comm_SendMsgForUpdataParm(C_ReworkTime, C_Msg_Deal_MultiRates);

	/*���޸�ǰʱ��(7�ֽڣ�CDate_Time��ʽ)��������Ϣ������ģ��*/
	PF_CopyDataBytes(V_SystemDate_Time,&V_ucMsg[1],CLDate_Time);
	V_ucMsg[0] = Pt_7DayAdd_FreezeTime;
	Comm_SendMsg(&V_ucMsg[0], (Pt_7DayAdd_FreezeTime_Len+1),C_Msg_Freeze);
	
#if 0	/*�޸�ʱ����������ѹ�ϸ��� �ѿ������¶��᲻�ϸ�*/
	/*���޸�ǰ��ʱ��(7�ֽڣ�CDate_Time��ʽ)��������Ϣ����ѹ�ϸ���ģ��*/
	PF_CopyDataBytes(&pV_645Frame->Data[CBoardCastData_O_V_645+C_ss_O],&V_ucMsg[CLDate_Time+1],CLDate_Time);
	V_ucMsg[0] = Pt_VRQTimeChange;
	Comm_SendMsg(V_ucMsg, (CLDate_Time*2+1),C_Msg_VoltageQualifiedRateMetering);
#endif
	
	Err = C_OK;
	return Err;
}
/*******************************************************************************
����ԭ�ͣ�uchar8	SF_SetBaudrate_698(uchar8 V_ucOAD[4], uchar8 *V_ucBps, Str_Comm_645 *pV_645Frame, Str_Comm_698_RW *pV_698RWPara)
��������������������
���������V_ucOAD���õĲ����ʱ�־�룻V_ucBps�����õ����ݣ�pV_645Frame��pV_698RWParaͨ��ȫ�ֱ���
�����������
���ز�����C_OK���óɹ�������������
����λ�ã�
��    ע��
*******************************************************************************/
uchar8	SF_SetBaudrate_698(uchar8 V_ucOAD[4], uchar8 *V_ucBps, Str_Comm_645 *pV_645Frame, Str_Comm_698_RW *pV_698RWPara)
{
	uchar8	V_ucOperCode[4] = {0, 0, 0, 0};
	ulong32 V_ulLastDI = 0xFFFFFFFF;
	ulong32 V_ulNextDI = 0xFFFFFFFF;
	uchar8	V_ucFlag = C_NeedWriteEventRecord;
	uchar8	V_ucReturnFlag = C_OK;

	/*�����ߴ���*/
	PF_CopyDataBytes(V_ucOperCode, pV_645Frame->Opcode, 4);
	PF_CopyDataBytes(V_ucOperCode, &pV_645Frame->Data[COpCode_OtherO_V_645], 4);

	pV_645Frame->DataLen = CLen_DI + CLen_OpCode + CLen_CommPW + CLOne485_Baud;

	PF_CopyDataBytes(V_ucBps, &(pV_645Frame->Data[C_Data_OFS_14]), CLOne485_Baud);

	if(V_ucOAD[3] == 0xF2)
	{
        if(V_ucOAD[2] == 0x01)
        {
            if(V_ucOAD[0] == 0x01)
            {
                pV_645Frame->DI = COne485_Baud;
            }
            else if(V_ucOAD[0] == 0x02)
            {
                pV_645Frame->DI = CTwo485_Baud;
            }
            else
            {
                V_ucReturnFlag = C_OtherErr;
            }
        }
        else if(V_ucOAD[2] == 0x09)
        {
            if( ( V_ucOAD[0] == 0x01 ) || ( V_ucOAD[0] == 0xFD ) )
            {
                pV_645Frame->DI = CModular_Baud;
            }
            else
            {
                 V_ucReturnFlag = C_OtherErr;
            }

            if(V_ucOAD[0] == 0xFD)
            {
                V_ucFlag = C_NotWriteEventRecord;
            }
        }
        if(V_ucReturnFlag != C_OK)
        {
			return V_ucReturnFlag;
		}
		PF_Ulong32ToBuffer4(&pV_645Frame->Data[CDI_O_V_645], &(pV_645Frame->DI), 4);
		V_ucReturnFlag = SF_SetParm(pV_645Frame, V_ulLastDI, V_ulNextDI, V_ucFlag, pV_698RWPara->Wt_OI[pV_698RWPara->ResponedNum].WtOI, pV_698RWPara->ServiceFlag_First);
		if(V_ucReturnFlag == C_OK)
		{
			SV_SetBPS_Flag = C_OK;
		}
	}
	return V_ucReturnFlag;
}
/*******************************************************************************
����ԭ�ͣ�void SF_698ActionF205_Deal645(uchar8 *pData)
��������������698�̵������ͬ��645�������������1
���������*pV_645Frame:���յ�������֡
�����������
���ز�������
����λ�ã�698����
��    ע��
*******************************************************************************/
void SF_698ActionF205_Deal645(uchar8 V_ucData)
{
    uchar8   V_ucMeter_Work_Type = 0;
    uchar8   V_ucReturn;
	ushort16 V_ucMeter_Work_Len = CLMeter_Work_Char1, V_usDataEncode;

    V_ucReturn = InF_Read_Data(CMeter_Work_Char1_645, &V_ucMeter_Work_Type, &V_ucMeter_Work_Len, &V_usDataEncode);	/*��������*/
    if(V_ucReturn != C_OK)
    {
        V_ucMeter_Work_Type = 0;
    }
    V_ucMeter_Work_Type &= 0xFE;
    V_ucMeter_Work_Type |= ((~(V_ucData & 0x01)) & 0x01);
    InF_Write_Data(C_Msg_Communication, CMeter_Work_Char1_645, &V_ucMeter_Work_Type, CLMeter_Work_Char1_645, C_W_SafeFlag);
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_ActionPerOI(Str_Comm_698_RW *pV_698RWPara,Str_Comm_645 *pV_645Frame,uchar8 V_ucOINum)
�����������ͻ��˲���һ���������Ժ���
���������Str_Comm_698_RW�ж�Ӧ��ȡ���ݶ���OI���������͵�
���������pV_698RWParaдOI�����ý�������óɹ�Ϊ0������ʧ��������Ӧ������ʧ��ԭ��
���ز����������Ƿ���ȷ��C_OK��ʾ��ȡ�ɹ���������ʾ�������
����λ�ã�
��    ע��
*******************************************************************************/
const Str_ReportEventNo TB_MeterStatusEventNo[C_MeterStatus_EventNum]=
{
  /*645��bitλ    698���¼���*/
  {C_Report_Bit3,     C_RTCBatLowVolEventNo},			/*ʱ�ӵ�ص�ѹ��*/
  {C_Report_Bit8,     C_PowerBatLowVolEventNo}, 		/*ͣ�糬���ص�ѹ��*/
  {C_Report_Bit14,    C_RelayOpenEventNo},				/*��բ*/
  {C_Report_Bit15,    C_RelayCloseEventNo},				/*��բ*/
};
uchar8 SF_ActionPerOI(Str_Comm_698_RW *pV_698RWPara, Str_Comm_645 *pV_645Frame, uchar8 V_ucOINum)
{
	uchar8	ReturnFlag = C_ObjectUndefine_DAR;
	uchar8	V_ucOperCode[4] = {0, 0, 0, 0};
	uchar8	V_ucOIA, V_ucOIB, V_ucMethod;
	ushort16 V_usOrderExcuteStatus;
	uchar8 V_ucOrderType = 0;
	ulong32	V_ulData;
	uchar8 V_EventDI[4] = {0xFF, 0xFF, 0xFF, 0xFF};
	ushort16 V_ulOff, V_ulLen;
	uchar8 V_ucDataBuffer[300];
	uchar8 V_ucMeterStatusEvent;
	uchar8 k, V_ucEventNo, V_BUFF[2];
    ushort16 V_usMeterStatus = 0, V_ucLen, V_usDataEncode;

	V_ucOIA = (uchar8)(pV_698RWPara->Wt_OI[V_ucOINum].WtOI >> 24);
	V_ucOIB = (uchar8)(pV_698RWPara->Wt_OI[V_ucOINum].WtOI >> 16);
	V_ucMethod = (uchar8)(pV_698RWPara->Wt_OI[V_ucOINum].WtOI >> 8);
	switch(V_ucOIA)
	{
		case		0x43:
			if(V_ucOIB == 0x00)
			{
				/*�����ߴ���*/
				PF_CopyDataBytes(V_ucOperCode, pV_645Frame->Opcode, 4);
				PF_CopyDataBytes(V_ucOperCode, &pV_645Frame->Data[COpCode_OtherO_V_645], 4);

				if( pV_698RWPara->Wt_OI[0].Wt_Data[0] != 0x00 )
				{
					ReturnFlag = C_TypeErr_DAR;
					break;
				}

				if(V_ucMethod == 0x03)/*�����������*/
				{
					if(InF_JudgeKeyStatus() == C_StateOfOfficialKey)  		/*��ʽ��Կ���������㣬��ȫ�淶*/
					{
						ReturnFlag = C_Unauthorized_DAR;
						break;
					}
					else
					{
						SF_MeterClear(pV_645Frame);
						ReturnFlag = C_OK;
					}
				}

				else if(V_ucMethod == 0x05)/*�¼���¼����*/
				{
					PF_CopyDataBytes(V_EventDI, &pV_645Frame->Data[C_O_EventClear_DI], 4);
					ReturnFlag = SF_EventClear(pV_645Frame,pV_698RWPara->Wt_OI[V_ucOINum].WtOI);
				}
				else if(V_ucMethod == 0x06)/*��������*/
				{
					SF_DemandClear();
					ReturnFlag = C_OK;
				}
			}
			break;
		case		0x40:		/*�㲥Уʱ*/
			PF_CopyDataBytes(pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data, &pV_645Frame->Data[CBoardCastData_O_V_645], 7);
			ReturnFlag = SF_BroadcastSetClock(pV_645Frame);
			break;
		case		0x50:		/*��������*/
			if( ( V_ucMethod == 0x03 ) && ( V_ucOIB != 0x00 ) )				/*ֻ��˲ʱ�����֧�ִ���һ�������¼*/
			{
				ReturnFlag = C_OtherErr;
				break;
			}
			if(V_ucMethod == 0x03)
			{
				/*˲ʱ���ᷢ����Ϣ*/
				uchar8	MsgParm;
				ushort16 V_usDelayTime;

				if(pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[0] != C_long_unsigned)
				{
					ReturnFlag = C_OtherErr;
					break;
				}
 				V_usDelayTime = pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[1];	/*	��ֵ˲ʱ������ʱʱ��*/
				V_usDelayTime <<= 8;
				V_usDelayTime |= (ushort16)pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[2];
				FreezeTimerTable.FreezeTimer = V_usDelayTime;
				FreezeTimerTable.V_CRC16 = PF_Cal_CRC((uchar8 *)&FreezeTimerTable.FreezeTimer, 2);
				if(V_usDelayTime == 0)		/*	��������*/
				{
					MsgParm = Pt_MsgFreezeImmediately;
					Comm_SendMsg(&MsgParm, (Pt_MsgFreezeImmediately_Len + 1), C_Msg_Freeze);
				}
				ReturnFlag = C_OK;
			}
			else if(V_ucMethod ==0x04)		/*����һ����������*/
			{
				ReturnFlag = SF_FreezeOADADD(pV_698RWPara->Wt_OI[V_ucOINum]);
				if(ReturnFlag == C_OK)		/*��¼�ܱ���¼���¼*/
				{
					uchar8 V_ucBuff[4];

					PF_Ulong32ToBuffer4(V_ucBuff, &pV_698RWPara->Wt_OI[V_ucOINum].WtOI, 4);
					INF_Append_ProgRecordDI(&pV_645Frame->Data[COpcode_14O_V_645], V_ucBuff, &SV_Comm_Parse.ProgRecord, pV_698RWPara->ServiceFlag_First);
				}
			}
			else if(V_ucMethod == 0x05)		/*ɾ��һ����������*/
			{
				ReturnFlag = SF_FreezeOADDelete(pV_698RWPara->Wt_OI[V_ucOINum]);
				if(ReturnFlag == C_OK)		/*��¼�ܱ���¼���¼*/
				{
					uchar8 V_ucBuff[4];

					PF_Ulong32ToBuffer4(V_ucBuff, &pV_698RWPara->Wt_OI[V_ucOINum].WtOI, 4);
					INF_Append_ProgRecordDI(&pV_645Frame->Data[COpcode_14O_V_645], V_ucBuff, &SV_Comm_Parse.ProgRecord, pV_698RWPara->ServiceFlag_First);
				}
			}
			else if(V_ucMethod ==0x07)		/*�������ù��������б�*/
			{
				ReturnFlag = SF_FreezeOADSet(pV_698RWPara->Wt_OI[V_ucOINum], 0x00);
				if(ReturnFlag == C_OK)		/*��¼�ܱ���¼���¼*/
				{
					uchar8 V_ucBuff[4];
					PF_Ulong32ToBuffer4(V_ucBuff, &pV_698RWPara->Wt_OI[V_ucOINum].WtOI, 4);
					INF_Append_ProgRecordDI(&pV_645Frame->Data[COpcode_14O_V_645], V_ucBuff, &SV_Comm_Parse.ProgRecord, pV_698RWPara->ServiceFlag_First);
				}
			}
			else if(V_ucMethod ==0x08)		/*ɾ�����������б�*/
			{
				ReturnFlag = SF_FreezeOADDeleteAll(pV_698RWPara->Wt_OI[V_ucOINum]);
				if(ReturnFlag == C_OK)		/*��¼�ܱ���¼���¼*/
				{
					uchar8 V_ucBuff[4];

					PF_Ulong32ToBuffer4(V_ucBuff, &pV_698RWPara->Wt_OI[V_ucOINum].WtOI, 4);
					INF_Append_ProgRecordDI(&pV_645Frame->Data[COpcode_14O_V_645], V_ucBuff, &SV_Comm_Parse.ProgRecord, pV_698RWPara->ServiceFlag_First);
				}
			}
			break;
		case		0xF0:		/*����ȶ�*/
			if(V_ucMethod == 10)
			{
				ReturnFlag = Comm_SoftwareCampare_698(pV_698RWPara->Wt_OI[V_ucOINum], V_ucDataBuffer, &V_ulLen);
				if(ReturnFlag == C_OK)
				{
					V_ulOff = 0;
					pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_ulOff] = 0x02;
					V_ulOff++;
					pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_ulOff] = 0x01;
					V_ulOff++;
					pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_ulOff] = 0x09;
					V_ulOff++;
					V_ulOff += SF_DataLen_AXDR_Encode(&pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_ulOff], V_ulLen);
					PF_CopyDataBytes_698(V_ucDataBuffer, &pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[V_ulOff], V_ulLen);
					pV_698RWPara->Wt_OI[V_ucOINum].DataLen = V_ulOff + V_ulLen;
					PF_CopyDataBytes_698(&pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[0], V_ucDataBuffer, pV_698RWPara->Wt_OI[V_ucOINum].DataLen);

				}
			}
			break;
		case		0x80:		/*���ɿ��ؿ���*/
		{

			if(C_Meter_Type == C_SmartMeter)
			{
				ReturnFlag = C_RWForbid_DAR;
				break;
			}

			if(V_ucOIB == 0x00)
			{
				if(V_ucMethod == 127)						/*�����澯*/
				{
					V_ucOrderType = C_Alarm_comm;
				}
				else if(V_ucMethod == 128)					/*�������*/
				{
					V_ucOrderType = C_Alarm_Release_comm;
				}
				else if(V_ucMethod == 129)					/*��բ*/
				{
					if( SF_JugeRelayOAD( pV_698RWPara, V_ucOINum   ) != C_OK )
					{
						ReturnFlag = C_No_Request_data;
						break;
					}
					PF_Buffer4ToUlong32(&pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[5], &V_ulData, 2);
          			if(V_ulData == 0)
					{
						V_ucOrderType = C_Relay_Open_comm;	/* ��բ */
						V_ulData = pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[4];
					}
					else
					{
						if(pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[7] == 0x00)	/* 0��ʾfalse */
						{
							V_ucOrderType = C_AlarmOpenRelay_Allow_comm;		/* ��բ�Զ��ָ�����ʱʱ�䵽��բ���� */
						}
						else
						{
							V_ucOrderType = C_AlarmOpenRelay_Direct_comm;		/* ��բ�Զ��ָ�����ʱʱ�䵽ֱ�Ӻ�բ�� */
						}
					}
				}
				else if(V_ucMethod == 130)					/*��բ*/
				{
					if( SF_JugeRelayOAD( pV_698RWPara, V_ucOINum ) != C_OK )
					{
						ReturnFlag = C_No_Request_data;
						break;
					}
					if( pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[4] == 0 )
					{
						V_ucOrderType = C_Relay_Close_Allow_comm;				/* ��բ���� */
					}
					else if( pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[4] == 1 )
					{
						V_ucOrderType = C_Relay_Close_Direct_comm;				/* ֱ�Ӻ�բ */
					}
				}
				else if( V_ucMethod == 131 )				/*���ĺ�բ*/
				{
					if( SF_JugeRelayOAD( pV_698RWPara, V_ucOINum) != C_OK )
					{
						ReturnFlag = C_No_Request_data;
						break;
					}
					V_ucLen = CL698Key;
					InF_Read_Data(C698Key, &V_ucDataBuffer[0], &V_ucLen, &V_usDataEncode);		/*���� */
					/*�������*/
					if( Comm_DealwithSPTVariable( C_JudgeKeyErr | 0x80 ) == C_KeyErr_Num_Over )
					{
						SF_RenewRelayControlStutas();
						ReturnFlag = C_Unauthorized_DAR;
						break;
					}
					if( PF_Campare_Data( V_ucDataBuffer, &pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[5], CL698Key ) != C_Equal )
					{
						if( InF_JudgeIJTimer() != C_OK )								/*�������������*/
						{
							Comm_DealwithSPTVariable(C_KeyErrNumAdd | C_Key02Flag);		/*ʹ��02���������*/
						}
						SF_RenewRelayControlStutas();
						ReturnFlag = C_Unauthorized_DAR;
						break;
					}
					else
					{
						Comm_DealwithSPTVariable(C_ClrKeyErrNum | C_Key02Flag);
					}
					if(pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[4] == 0)
					{
						V_ucOrderType = C_Relay_Close_Allow_comm;						/* ��բ���� */
					}
					else if(pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[4] == 1)
					{
						V_ucOrderType = C_Relay_Close_Direct_comm;						/* ֱ�Ӻ�բ */
					}
				}
			}
			else if(V_ucOIB == 0x01)
			{
				if(V_ucMethod == 127)				/*Ͷ�뱣��*/
				{
					V_ucOrderType = C_Protect_Current_comm;
				}
				else if(V_ucMethod == 128)			/*�������*/
				{
					V_ucOrderType = C_Protect_Current_Release_comm;
				}
			}
			/*���ü̵���ģ��Ľӿں�����*/
			ReturnFlag = InF_DealwithComRelayOrder(V_ucOrderType, V_ucOperCode, V_ulData, &V_usOrderExcuteStatus, C_UsedBy698);
			break;
		}
		case		0x30:
		{
			if(V_ucMethod == 1)
			{
				ReturnFlag = SF_EventClear_698(pV_698RWPara->Wt_OI[V_ucOINum].WtOI, pV_645Frame, C_Program);
				break;
			}
			else if(V_ucMethod == 0x04)				/*����һ����������*/
			{
				if( ( pV_698RWPara->Wt_OI[V_ucOINum].WtOI & 0xffff0000 ) == 0x30130000 )			/*˽Կ״̬�²����������������¼��Ĺ����б�*/
				{
					if( ( InF_JudgeKeyStatus() == C_StateOfOfficialKey ) && ( InF_JudgeIJTimer() != C_OK ) )	/*��ʽ��Կ*/
					{
						ReturnFlag = C_RWForbid_DAR;
                        break;
					}
				}
				ReturnFlag = SF_EventOADADD(pV_698RWPara->Wt_OI[V_ucOINum]);
				if(ReturnFlag == C_OK)				/*��¼�ܱ���¼���¼*/
				{
					uchar8 V_ucBuff[4];

					PF_Ulong32ToBuffer4(V_ucBuff, &pV_698RWPara->Wt_OI[V_ucOINum].WtOI, 4);
					INF_Append_ProgRecordDI(&pV_645Frame->Data[COpcode_14O_V_645], V_ucBuff, &SV_Comm_Parse.ProgRecord, pV_698RWPara->ServiceFlag_First);
				}
			}
			else if(V_ucMethod == 0x05)				/*ɾ��һ����������*/
			{
				if( ( pV_698RWPara->Wt_OI[V_ucOINum].WtOI & 0xffff0000 ) == 0x30130000 )			/*˽Կ״̬�²����������������¼��Ĺ����б�*/
				{
					if( ( InF_JudgeKeyStatus() == C_StateOfOfficialKey ) && ( InF_JudgeIJTimer() != C_OK ) )	/*��ʽ��Կ*/
					{
						ReturnFlag = C_RWForbid_DAR;
                        break;
					}
				}
				ReturnFlag = SF_EventOADDelete(pV_698RWPara->Wt_OI[V_ucOINum]);
				if(ReturnFlag == C_OK)				/*��¼�ܱ���¼���¼*/
				{
					uchar8 V_ucBuff[4];

					PF_Ulong32ToBuffer4(V_ucBuff, &pV_698RWPara->Wt_OI[V_ucOINum].WtOI, 4);
					INF_Append_ProgRecordDI(&pV_645Frame->Data[COpcode_14O_V_645], V_ucBuff, &SV_Comm_Parse.ProgRecord, pV_698RWPara->ServiceFlag_First);
				}
			}
			else if(V_ucMethod == 0x0F)				/*ɾ����������*/
			{
				ReturnFlag = SF_EventOADDeleteAll(pV_698RWPara->Wt_OI[V_ucOINum]);
			}

		}
        break;
		case		0xF1:							/*��ȫģʽ����*/

			if(V_ucMethod == 0x01)					/*��λʱ���������3*/
			{
				ReturnFlag = SF_SecurityOIDeleteAll(pV_698RWPara->Wt_OI[V_ucOINum]);
			}
			else if(V_ucMethod == 127)				/*������ʽ��ȫģʽ�����������ʶ��Ȩ�ޣ�*/
			{
				ReturnFlag = SF_SecurityOIADD(pV_698RWPara->Wt_OI[V_ucOINum]);
			}
			else if(V_ucMethod == 128)				/*ɾ����ʽ��ȫģʽ�����������ʶ��*/
			{
				ReturnFlag = SF_SecurityOIDelete(pV_698RWPara->Wt_OI[V_ucOINum]);
			}
			else if(V_ucMethod == 129)				/*����������ʽ��ȫģʽ������array ��ȫģʽ������*/
			{
				ReturnFlag = SF_SecurityOISet(pV_698RWPara->Wt_OI[V_ucOINum]);
			}
            if(ReturnFlag == C_OK)
            {
				uchar8 V_ucBuff[4];

				PF_Ulong32ToBuffer4(V_ucBuff, &pV_698RWPara->Wt_OI[V_ucOINum].WtOI, 4);
				INF_Append_ProgRecordDI(&pV_645Frame->Data[COpcode_14O_V_645], V_ucBuff, &SV_Comm_Parse.ProgRecord, pV_698RWPara->ServiceFlag_First);
            }
			break;
		case		0xF2:
		{
			uchar8 V_oad[4];

			if( ( V_ucMethod != 127 ) && ( ( V_ucMethod == 128 ) && ( V_ucOIB != 0x09 ) ) )
			{
				ReturnFlag = C_ObjectTypeErr_DAR;						/* ����ӿ��಻����*/
				break;
			}

			if( ( V_ucOIB == 0x01 ) || ( V_ucOIB == 0x09 ) )			/*RS485����ģ��*/
			{
				if( ( pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[0] != C_structure )
				 || ( pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[2] != C_OAD )
				 || ( pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[7] != C_COMDCB ) )
				{
					ReturnFlag = C_TypeErr_DAR;							/* ���Ͳ�ƥ��*/
                    break;
				}
				PF_OneDataReversed(&pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[3], V_oad, 4);

				if( ( ( V_ucOIB == 0x01 ) && ( V_oad[2] != 0x01 ) ) || ( ( V_ucOIB == 0x09 ) && ( V_oad[2] != 0x09 ) ) || ( ( V_ucOIB == 0x09 ) && ( V_oad[0] == 0x00 ) ) )
				{
					ReturnFlag = C_Baud_NotModified_DAR;				/* ͨ�����ʲ����޸�*/
					break;
				}

				if( ( V_ucOIB == 0x09 ) && ( V_oad[1] == 0x02 ) && ( V_oad[0] == 0xFD ) && ( pV_698RWPara->ChannelNo != C_Module ) )
                {
                       ReturnFlag = C_OtherErr_DAR;						/* ����ģ��ӿڽ��в�����Э��Ӧ����������*/
                       break;
                }

				ReturnFlag = SF_SetBaudrate_698(V_oad, &pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[8], pV_645Frame, pV_698RWPara);
			}
			else if(V_ucOIB == 0x02)									/*����*/
			{
				ReturnFlag = C_Baud_NotModified_DAR;					/* ͨ�����ʲ����޸�*/
			}
			else if(V_ucOIB == 0x05)									/*�̵������*/
			{
				if( ( pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[0] != C_structure )
				 || ( pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[2] != C_OAD )
				 || ( pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[7] != C_enum ) )
				{
					ReturnFlag = C_TypeErr_DAR;							/* ���Ͳ�ƥ��*/
                    break;
				}
				if( ( pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[3] == 0xF2 )
                 && ( pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[4] == 0x05 )
                 && ( pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[5] == 0x02 )
                 && ( pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[6] <= 1 ) )
               	{
					ushort16 V_Meter_Work_Len = 1, V_usDataEncode;
					uchar8 	V_Meter_Work_Type = 0, V_ucDI[4];
    				uchar8 	V_ucCode[4];

					if( ( pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[8] == 0x00 ) || ( pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[8] == 0x01 ) )
					{
						InF_Read_Data(CMeter_Work_Char1, &V_Meter_Work_Type, &V_Meter_Work_Len, &V_usDataEncode);	/*��������*/
						V_Meter_Work_Type &= 0xFE;
						V_Meter_Work_Type |= pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[8];
						ReturnFlag = InF_Write_Data(C_Msg_Communication, CMeter_Work_Char1, &V_Meter_Work_Type, 1, C_W_SafeFlag);
						if(ReturnFlag == C_OK)
						{
                            SF_698ActionF205_Deal645(V_Meter_Work_Type);
						    PF_Ulong32ToBuffer4(V_ucDI, &pV_698RWPara->Wt_OI[V_ucOINum].WtOI, 4);
							INF_Append_ProgRecordDI(V_ucCode,V_ucDI, &SV_Comm_Parse.ProgRecord, pV_698RWPara->ServiceFlag_First);
						}
					}
					else
					{
						ReturnFlag = C_OtherErr_DAR;
					}
				}
				else
				{
               		ReturnFlag = C_OtherErr_DAR;			/* ����*/
                    break;
				}
				break;
			}
			else if(V_ucOIB == 0x07)						/*�๦�ܶ���*/
			{
                if( ( pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[0] != C_structure )
				 || ( pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[2] != C_OAD )
				 || ( pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[7] != C_enum ) )
				{
					ReturnFlag = C_TypeErr_DAR;				/* ���Ͳ�ƥ��*/
                    break;
				}
                if( ( pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[3] == 0xF2 )
                 && ( pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[4] == 0x07 )
                 && ( pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[5] == 0x02 )
                 && ( pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[6] <= 1 ) )
                {
					ReturnFlag = InF_ModifyFunctionWord(pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[8]);
				}
                else
                {
					ReturnFlag = C_OtherErr_DAR;
                }
			}
			break;
		}
		case		0xF3:
		{
			ReturnFlag = SF_ActionDispPerOI(pV_698RWPara, V_ucOINum, pV_645Frame);
			break;
		}
        case        0x20:
        {
            if( ( pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[0] == 4 ) && ( pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[1] == 32 ) )
            {
            Inf_CleanMeterStatus8(&pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[2], pV_698RWPara->ChannelNo);
            /*******************************************/
           /*698����645��������645�����ϱ�,ʱ�ӵ�غ�ͣ�����*****************/
            V_BUFF[0] = pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[C_MeterStatus_Relay_Offset];
            V_BUFF[1] = pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[C_MeterStatus_Offset];
            PF_Buffer2ToUshort16(V_BUFF, &V_usMeterStatus);
            if( ( V_usMeterStatus & 0x1083 ) != 0 )
            {
				for(V_ucMeterStatusEvent = 0; V_ucMeterStatusEvent < ( 2 * 8); V_ucMeterStatusEvent++ )/*2*8:���ֽڣ�һ�ֽ�8λ*/
                {
            		if(V_usMeterStatus & 0x8000) 				/*���ϱ�������*/
                    {
            			for( k = 0; k < C_MeterStatus_EventNum; k++ )
            			{
            				if(V_ucMeterStatusEvent == TB_MeterStatusEventNo[k].BitN0)
            				{
            					V_ucEventNo = TB_MeterStatusEventNo[k].EventN0;
            					SF_Clear645_ReportNewAddNum(V_ucEventNo, C_2015CLEAR);
            				}
            			}
            		}
                    V_usMeterStatus <<= 1;
                }
            }
            ReturnFlag = C_OK_DAR;
            }
            else
            {
                ReturnFlag = C_TypeErr_DAR;
            }
            break;
        }
		default:			/*Ӧ����������*/
			ReturnFlag = C_OtherErr_DAR;
			break;
	}
	pV_698RWPara->Wt_OI[V_ucOINum].Wt_Result = ReturnFlag;
	if(V_ucOIA != 0xF0)
	{
		pV_698RWPara->Wt_OI[V_ucOINum].DataLen = 0;
	}
	return ReturnFlag;

}
/*******************************************************************************
����ԭ�ͣ�void SF_RenewRelayControlStutas(void)
��������������¼���¼���㹦��
���������
�����������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
void SF_RenewRelayControlStutas(void)
{
	ushort16	V_usRelayRelayStatus = 0, V_usOrderExcuteStatus = 0;
	uchar8	V_ucDataBuffer[10] = {0};

	V_usOrderExcuteStatus |= C_PasswordError_failure;																	/*������δ��Ȩ */
	PF_Ushort16ToBuffer2(V_ucDataBuffer, &V_usRelayRelayStatus);
	PF_Ushort16ToBuffer2(&V_ucDataBuffer[2], &V_usOrderExcuteStatus);
	InF_Write_Data(C_Msg_Communication, CControl_ExecuteState, V_ucDataBuffer, CLControl_ExecuteState, C_W_SafeFlag);	/*��������ִ��״̬��*/
	InF_Write_Data(C_Msg_Communication, CControl_ErrorState, &V_ucDataBuffer[2], CLControl_ErrorState, C_W_SafeFlag);	/*�����������״̬��*/
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_EventClear_698(ulong32 V_ulOAD,Str_Comm_645 *pV_645Frame,uchar8 V_ProgFlag)
��������������¼���¼���㹦��
���������
�����������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_EventClear_698(ulong32 V_ulOAD, Str_Comm_645 *pV_645Frame, uchar8 V_ProgFlag)
{
	uchar8 V_ucClassNum, V_uc645Num = 0, i, V_ucOIB, ReturnFlag = C_OtherErr_DAR;
	ulong32	V_ul645DI[5], V_ulData;

	V_ucOIB = (uchar8)(V_ulOAD >> 16);
	/*�����ߴ���*/
	for( i = 0; i < C_Event_OIBTableLen; i++ )
	{
		if(V_ucOIB == Event_OIBTable[i].OIB)
		{
			break;
		}
	}
	if( i == C_Event_OIBTableLen )
	{
		return C_OtherErr_DAR;

	}
    /*��������¼����¼������¼�����ʹ�÷���1������ִ�з����¼�����*/
    if( ( V_ulOAD == CTol_Clear_Note_MethodOne ) || ( V_ulOAD == CEven_Clear_Note_MethodOne ) )
    {
		ReturnFlag = C_OtherErr_DAR;
		return ReturnFlag;
    }
	V_ucClassNum = Event_OIBTable[i].TypeClass & 0x3F;
	if(V_ucClassNum == 7)	/*�޷����¼���¼*/
	{
		for( i = 0; i < Str_EvenClearTable698To645_Len; i++ )
		{
			if(V_ucOIB == Str_EvenClearTable698To645[i].V_OIB)
			{
				break;
			}
		}
		if(i == Str_EvenClearTable698To645_Len)
		{
			ReturnFlag = C_OtherErr_DAR;
			return ReturnFlag;
		}
		V_ul645DI[0] = Str_EvenClearTable698To645[i].V_DI;
		V_uc645Num = 1;
	}
	else if(V_ucClassNum == 24)	/*�з����¼���¼*/
	{
		for( i = 0; i < Str_EvenClearTable698To645_Len; i++ )
		{
			if(V_ucOIB == Str_EvenClearTable698To645[i].V_OIB)
			{
				break;
			}
		}
		if(i == Str_EvenClearTable698To645_Len)
		{
			ReturnFlag = C_OtherErr_DAR;
			return ReturnFlag;
		}
		V_ulData = Str_EvenClearTable698To645[i].V_DI & 0xFFFF00FF;
		if( ( V_ucOIB==CLow_Vol_OIB )		/*698-Ƿѹ*/
		 || ( V_ucOIB==COver_Vol_OIB )      /*698-��ѹ*/
		 || ( V_ucOIB==CBreak_Vol_OIB )     /*698-����*/
		 || ( V_ucOIB==CLoss_Curr_OIB )     /*698-ʧ��*/
		 || ( V_ucOIB==COver_Curr_OIB )     /*698-����*/
		 || ( V_ucOIB==CBreak_Curr_OIB )    /*698-����*/
		 || ( V_ucOIB==COver_Lo_OIB ) )   	/*698-����*/
		{
			V_ulData = Str_EvenClearTable698To645[i].V_DI & 0xFFFF00FF;
			V_ul645DI[0] = V_ulData | 0x00000700;
			V_ul645DI[1] = V_ulData | 0x00000800;
			V_ul645DI[2] = V_ulData | 0x00000900;
			V_uc645Num = 3;
		}
		else if(V_ucOIB == CLoss_Vol_OIB)	/*698-ʧѹ*/
		{
			V_ulData = Str_EvenClearTable698To645[i].V_DI & 0xFFFF00FF;
			V_ul645DI[0] = V_ulData;
			V_ul645DI[1] = V_ulData | 0x00000700;
			V_ul645DI[2] = V_ulData | 0x00000800;
			V_ul645DI[3] = V_ulData | 0x00000900;
			V_uc645Num = 4;
		}
		else if( ( V_ucOIB == CRe_ReDe_Over_OIB )
			  || ( V_ucOIB == CTrend_Rev_OIB )
			  || ( V_ucOIB == CPFactorT_Over_OIB ) )
		{
			V_ulData = Str_EvenClearTable698To645[i].V_DI & 0xFFFF00FF;
			V_ul645DI[0] = V_ulData | 0x00000600;
			V_ul645DI[1] = V_ulData | 0x00000700;
			V_ul645DI[2] = V_ulData | 0x00000800;
			V_ul645DI[3] = V_ulData | 0x00000900;
			V_uc645Num = 4;
		}
		else
		{
			ReturnFlag = C_OtherErr_DAR;
			return ReturnFlag;
		}
	}
	for( i = 0; i < V_uc645Num; i++)
	{
		V_ulData = 0x00000000;
		if( ( i == ( V_uc645Num - 1 ) ) && ( V_ProgFlag == C_Program ) )
		{
			V_ulData = 	V_ulOAD;
		}
		PF_Ulong32ToBuffer4(&pV_645Frame->Data[C_O_EventClear_DI], &V_ul645DI[i], 4);

		ReturnFlag = SF_EventClear(pV_645Frame, V_ulData);
	}
	return ReturnFlag;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_EventClear_698_Dou645(Str_Comm_645 *pV_645Frame,uchar8 V_ProgFlag)
��������������¼���¼���㹦��
���������
�����������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_EventClear_698_Dou645(Str_Comm_645 *pV_645Frame, uchar8 V_ProgFlag)
{
	uchar8 V_ucClassNum, V_uc645Num, i, V_ucOIB, ReturnFlag;
	ulong32	V_ul645DI[5], V_ulData;
	ulong32 V_ulOAD = 0;
	uchar8 j;

	PF_Buffer4ToUlong32(&pV_645Frame->Data[C_O_EventClear_DI], &V_ulOAD, 4);
	for( j = 0; j < Pstr_ParaChange_Event_Len; j++)
	{
		if(V_ulOAD == Pstr_ParaChange_Event[j].DI)
		{
			V_ulOAD = Pstr_ParaChange_Event[j].OAD;
            break;
		}
	}
	if(j == Pstr_ParaChange_Event_Len)
	{
		ReturnFlag = C_Unauthorized_645;
		return ReturnFlag;
	}

	V_ucOIB = (uchar8)(V_ulOAD >> 16);
	/*�����ߴ���*/
	for( i = 0; i < C_Event_OIBTableLen; i++)
	{
		if(V_ucOIB == Event_OIBTable[i].OIB)
		{
			break;
		}
	}
	if(i == C_Event_OIBTableLen)
	{
		ReturnFlag = C_OtherErr_645;
	}
	V_ucClassNum = Event_OIBTable[i].TypeClass & 0x3F;
	if(V_ucClassNum == 7)	/*�޷����¼���¼*/
	{
		for( i = 0; i < Str_EvenClearTable698To645_Len; i++ )
		{
			if(V_ucOIB == i)
			{
				break;
			}
		}
		if(i == Str_EvenClearTable698To645_Len)
		{
			ReturnFlag = C_OtherErr_645;
			return ReturnFlag;
		}
		V_ul645DI[0] = Str_EvenClearTable698To645[i].V_DI;
		V_uc645Num=1;
	}
	else
	{
		ReturnFlag = C_Unauthorized_645;
		return ReturnFlag;
	}
	for( i = 0; i < V_uc645Num; i++ )
	{
		V_ulData = 0x00000000;
		if( ( i == ( V_uc645Num - 1 ) ) && ( V_ProgFlag == C_Program ) )
		{
			V_ulData = 	V_ulOAD;
		}
		PF_Ulong32ToBuffer4(&pV_645Frame->Data[C_O_EventClear_DI], &V_ul645DI[i], 4);

		ReturnFlag = SF_EventClear(pV_645Frame, V_ulData);
	}
	return ReturnFlag;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 Comm_SoftwareCampare_698(WtOI_Rt_T V_OAD,uchar8 *V_ucBuff,ushort16 *V_Len)
�����������������ȶԹ���
���������
�����������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 Comm_SoftwareCampare_698(WtOI_Rt_T V_OAD, uchar8 *V_ucBuff, ushort16 *V_Len)
{
	uchar8 V_ucKeyNum, V_ucCPUNum;
	ulong32 V_ulDataAddr, V_ulFactorAddr;
	uchar8 *P_DataAddr;
	uchar8 V_ucFactorBuffer[C_L_FactorLen];
	uchar8 V_ucRandBuffer[C_L_RandLen];
	uchar8 V_ucDataBuffer[C_L_PlainDataLen_698];
	ushort16 V_usReturn, i, j, V_usOffset, V_ulCipherLen, V_ulLen;

	V_ucCPUNum = V_OAD.Wt_Data[3];									/*ȡCPU���*/
	V_ucKeyNum = V_OAD.Wt_Data[5];									/*ȡ��Կ�������*/
	V_ulFactorAddr = PF_Buffer4ToUlong32_698(&V_OAD.Wt_Data[7]);	/*ȡ��ɢ���ӵ�ַ*/
	V_ulDataAddr = PF_Buffer4ToUlong32_698(&V_OAD.Wt_Data[12]);		/*ȡ���������ݵ�ַ*/
	V_ulCipherLen = PF_Buffer2ToLong16_698(&V_OAD.Wt_Data[17]);		/*ȡ���������ݳ���*/
	if( ( V_ulCipherLen > C_L_PlainDataLen_698 ) || ( ( V_ulCipherLen % 64 ) != 0 ) )
	{
        V_usReturn = C_OtherErr_DAR;
		return 	V_usReturn;
	}

	if(V_ucCPUNum != C_CPUNum)										/*CPUֻ��1������ű���Ϊ0*/
	{
		V_usReturn = C_OtherErr_DAR;
		return 	V_usReturn;
	}
	/*/698�޸ĵ�ַ���ƣ���ʼ��ַС��FLASH��ʼ��ַ�İ���00Ӧ��������е���ʼ��ַ����FLASH�ռ�����ַ��*/
	/*/����"��ַ����Χ"Ӧ������������һ֡����Ч�ռ䣬����698Э��涨�Ĳ�λ������*/
	if( ( V_ulDataAddr > C_MaxCodeSpace ) || ( V_ulFactorAddr > C_MaxCodeSpace ) )	/*��ַ����������ռ��ַ*/
	{
		return 	C_FWAddressErr_DAR;
	}
/**********************ȡ��ɢ���ӣ��������������*******************************/
	P_DataAddr = (uchar8 *)V_ulFactorAddr;
#if(C_MinCodeSpace != 0)
	if(V_ulFactorAddr < C_MinCodeSpace)				/*��ɢ����С������ַ�ռ䣬����в����ݲ���*/
	{
		if((V_ulFactorAddr+C_L_FactorLen) <= C_MinCodeSpace)
		{
			i = (C_L_FactorLen);					/*����ȫ��С�ڳ���ռ��ַ����Ч����ΪC_L_FactorLen*/
		}
		else
		{
			i = C_MinCodeSpace - V_ulFactorAddr;	/*������Ч���ݵĳ���*/
		}
		for( j = 0; j < i; j++ )					/*��Ч���ݲ�0*/
		{
			V_ucFactorBuffer[j] = 0;
		}
		i = (C_L_FactorLen - i);					/*��Ч���ݳ���*/
		PF_CopyDataBytes_698(&P_DataAddr[j], &V_ucFactorBuffer[j], i);			/*��Ч���ݸ��Ƶ���ʱbuffer*/
	}
	else if( ( V_ulFactorAddr + C_L_FactorLen ) > ( C_MaxCodeSpace+1 ) )		/*��ɢ����+���ȴ�������ַ�ռ䣬����в����ݲ���*/
#else
	if( ( V_ulFactorAddr + C_L_FactorLen ) > ( C_MaxCodeSpace + 1 ) )			/*��ɢ����+���ȴ�������ַ�ռ䣬����в����ݲ���*/
#endif
	{
		i = (V_ulFactorAddr + C_L_FactorLen ) - C_MaxCodeSpace - 1;				/*������Ч���ݵĳ���*/
		i = (C_L_FactorLen - i);												/*��Ч���ݳ���*/
		PF_CopyDataBytes_698(P_DataAddr, V_ucFactorBuffer, i);					/*��Ч���ݸ��Ƶ���ʱbuffer*/

		V_ucFactorBuffer[i] = 0x80;												/*��Ч���ݺ�ĵ�һ���ֽڲ�0x80*/
		i++;
		for( ; i < C_L_FactorLen; i++ )											/*��Ч���ݺ�ڶ����ֽڿ�ʼ��0x00*/
		{
			V_ucFactorBuffer[i] = 0;
		}
	}
	else
	{
		PF_CopyDataBytes(P_DataAddr, V_ucFactorBuffer, C_L_FactorLen);
	}
	for( i = 0; i < C_L_FactorData; i++ )
	{
		V_ucFactorBuffer[i] = V_ucFactorBuffer[i] ^ V_ucFactorBuffer[i + C_L_FactorData];
	}
/**********************ȡ��������������������*******************************/
	P_DataAddr = (uchar8 *)V_ulDataAddr;
#if(C_MinCodeSpace != 0)
	if(V_ulDataAddr < C_MinCodeSpace)				/*�����С������ַ�ռ䣬����в����ݲ���*/
	{
		if( ( V_ulDataAddr + C_L_RandLen ) <= C_MinCodeSpace )
		{
			i = (C_L_RandLen);						/*����ȫ��С�ڳ���ռ��ַ����Ч����ΪC_L_FactorLen*/
		}
		else
		{
			i = C_MinCodeSpace - V_ulDataAddr;		/*������Ч���ݵĳ���*/
		}
		for(j = 0; j < i; j++ )						/*��Ч���ݲ�0*/
		{
			V_ucRandBuffer[j] = 0;
		}
		i = (C_L_RandLen - i);						/*��Ч���ݳ���*/
		PF_CopyDataBytes_698(&P_DataAddr[j], &V_ucRandBuffer[j], i);	/*��Ч���ݸ��Ƶ���ʱbuffer*/
	}
	else if( ( V_ulDataAddr + C_L_RandLen ) > ( C_MaxCodeSpace + 1 ) )	/*��ɢ����+���ȴ�������ַ�ռ䣬����в����ݲ���*/
#else
	if( ( V_ulDataAddr + V_ulCipherLen ) > ( C_MaxCodeSpace + 1 ) )		/*��ɢ����+���ȴ�������ַ�ռ䣬����в����ݲ���*/
#endif
	{
		i = (V_ulDataAddr + C_L_RandLen) - C_MaxCodeSpace - 1;			/*������Ч���ݵĳ���*/
		i = (C_L_RandLen - i);											/*��Ч���ݳ���*/
		PF_CopyDataBytes_698(P_DataAddr, V_ucRandBuffer, i);			/*��Ч���ݸ��Ƶ���ʱbuffer*/
		V_ucRandBuffer[i] = 0x80;										/*��Ч���ݺ�ĵ�һ���ֽڲ�0x80*/
		i++;
		for( ;i < C_L_RandLen; i++ )									/*��Ч���ݺ�ڶ����ֽڿ�ʼ��0x00*/
		{
			V_ucRandBuffer[i] = 0;
		}
	}
	else
	{
		PF_CopyDataBytes(P_DataAddr, V_ucRandBuffer, C_L_RandLen);
	}
	for( j = 1; j < 4; j++ )
	{
		for( i = 0; i < C_L_RandData; i++ )
 		{
 			V_ucRandBuffer[i] = V_ucRandBuffer[i] ^ V_ucRandBuffer[i + j * C_L_RandData];
		}
	}
/**********************ȡ���������ݣ��������������*******************************/
	P_DataAddr = (uchar8 *)V_ulDataAddr;
#if(C_MinCodeSpace != 0)
	if(V_ulDataAddr < C_MinCodeSpace)				/*����������С������ַ�ռ䣬����в����ݲ���*/
	{
		if( ( V_ulDataAddr + V_ulCipherLen ) <= C_MinCodeSpace )
		{
			i = (V_ulCipherLen);					/*����ȫ��С�ڳ���ռ��ַ����Ч����ΪC_L_FactorLen*/
		}
		else
		{
			i = C_MinCodeSpace - V_ulDataAddr;		/*������Ч���ݵĳ���*/
		}
		for( j = 0; j < i; j++ )					/*��Ч���ݲ�0*/
		{
			V_ucDataBuffer[j] = 0;
		}
		i = (V_ulCipherLen - i);					/*��Ч���ݳ���*/
		PF_CopyDataBytes_698(&P_DataAddr[j], &V_ucDataBuffer[j], i);		/*��Ч���ݸ��Ƶ���ʱbuffer*/
	}
	else if( ( V_ulDataAddr + V_ulCipherLen ) > ( C_MaxCodeSpace + 1 ) )	/*��ɢ����+���ȴ�������ַ�ռ䣬����в����ݲ���*/
#else
	if( ( V_ulDataAddr + V_ulCipherLen ) > ( C_MaxCodeSpace + 1 ) )			/*��ɢ����+���ȴ�������ַ�ռ䣬����в����ݲ���*/
#endif
	{
		i = ( V_ulDataAddr + V_ulCipherLen ) - C_MaxCodeSpace - 1;			/*������Ч���ݵĳ���*/
		i = ( V_ulCipherLen - i );											/*��Ч���ݳ���*/
		for( j = 0; j < i; j++ )											/*��Ч���ݸ��Ƶ���ʱbuffer*/
		{
			V_ucDataBuffer[j] = P_DataAddr[j];
		}
		V_ucDataBuffer[i] = 0x80;											/*��Ч���ݺ�ĵ�һ���ֽڲ�0x80*/
		i++;
		for( ; i < V_ulCipherLen; i++ )										/*��Ч���ݺ�ڶ����ֽڿ�ʼ��0x00*/
		{
			V_ucDataBuffer[i] = 0;
		}
	}
	else
	{
		for( i = 0; i < V_ulCipherLen; i++ )
		{
			V_ucDataBuffer[i] = P_DataAddr[i];
		}
	}
	V_ulLen = V_ulCipherLen / 4;
	for( j = 0; j < 3; j++ )
	{
		V_usOffset = j * V_ulLen;
		V_usOffset += V_ulLen;
		for( i = 0;i < V_ulLen; i++ )
		{
			V_ucDataBuffer[i] = V_ucDataBuffer[i] ^ V_ucDataBuffer[V_usOffset];
			V_usOffset++;
		}
	}
/***************���ܴ��������ݣ��ں������Ѿ������˵ߵ�������ⲿ����Ҫ�ٴν������ݸߵ��ֽڵߵ�*************/
	V_usReturn = InF_S_Software_Campare_698(V_ucDataBuffer, V_ucFactorBuffer, V_ucKeyNum, &V_ulLen, V_ucRandBuffer);
	*V_Len = V_ulLen;
	PF_CopyDataBytes_698(V_ucDataBuffer, V_ucBuff, V_ulLen);
	return 	V_usReturn;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_JugeRelayOAD(Str_Comm_698_RW *pV_698RWPara,uchar8 V_ucOINum)
�����������ͻ��˲���һ���������Ժ���
���������Str_Comm_698_RW�ж�Ӧ��ȡ���ݶ���OI���������͵�
���������pV_698RWParaдOI�����ý�������óɹ�Ϊ0������ʧ��������Ӧ������ʧ��ԭ��
���ز����������Ƿ���ȷ��C_OK��ʾ��ȡ�ɹ���������ʾ�������
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_JugeRelayOAD(Str_Comm_698_RW *pV_698RWPara, uchar8 V_ucOINum)
{
	uchar8 ReturnFlag = C_Unauthorized;

	if( ( pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[3] == 0xF2 )
	 && ( pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[2] == 0x05 )
	 && ( pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[1] == 0x02 )
	 && ( pV_698RWPara->Wt_OI[V_ucOINum].Wt_Data[0] == 0x01 ) )
	{
		ReturnFlag = C_OK;
	}
	return ReturnFlag;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_DealFramePart(Str_Comm_645 *p_698Frame,Str_Comm_Parm 	*pStr_Comm_Parm_Address)
������������֡���䴦��
���������p_698Frameָ��698����֡��ַ
�����������
���ز�������ַ����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_DealFramePart(Str_Comm_645 *p_698Frame, Str_Comm_Parm 	*pStr_Comm_Parm_Address)
{
	ushort16 V_Offset, V_FrameFlag;
	ushort16	V_DataLen;

	if( ( p_698Frame->C & 0x20 ) == 0x20 )						/*��֡��־*/
	{
		/*�����ж��Ƿ��һ֡*/
		V_Offset = 7 + p_698Frame->AddrLen;
		V_FrameFlag = p_698Frame->SecurityAddr[1];
		V_FrameFlag <<= 8;
		V_FrameFlag |= (ushort16)p_698Frame->SecurityAddr[0];
		p_698Frame->SecurityAddr[1] = 0x80;
		p_698Frame->FrameBlockFlag = V_FrameFlag | 0x8000;		/*�����֡��־,����Ӧ���־��1*/
		if( ( V_FrameFlag & 0xC000 ) == 0x00 )					/*��һ֡*/
		{
			CommFrameNum = 0;
			CommAPDUOffset = 0;
			if( ( p_698Frame->C & 0x80 ) == 0 )					/*�ͻ��˷���*/
			{
				CommDeriction = C_ClientToSeverse;				/*�ͻ��˷����֡*/
			}
		}

		if( C_SeverseToClient != CommDeriction )
		{
			CommDeriction = C_ClientToSeverse;					/*�ͻ��˷����֡*/
			if( ( ( CommFrameNum + 1 ) != ( V_FrameFlag & 0x0FFF ) )
			   &&( ( V_FrameFlag&0xC000 ) != 0x00 ) )
			{
				CommFrameNum = 0;
				CommAPDULen = 0;
				return C_Error;
			}
			CommFrameNum = V_FrameFlag & 0x0FFF;				/*�����֡���*/
			V_DataLen = p_698Frame->DataLen_698- V_Offset - 2 - 2;
			if( ( CommAPDUOffset + V_DataLen ) > 2000 )
			{
				return C_Error;
			}
			PF_CopyDataBytes_698(&p_698Frame->SecurityAddr[2], &CommAPDUBuf[CommAPDUOffset], V_DataLen);
			CommAPDUOffset += V_DataLen;
			CommAPDULen = CommAPDUOffset;
			if( ( V_FrameFlag & 0xC000 ) == 0x4000 )			/*��֡�������һ֡*/
			{
				p_698Frame->APDULen = CommAPDUOffset;
				p_698Frame->SecurityAddr = CommAPDUBuf;
				p_698Frame->C &= 0xDF;							/*ȡ����֡��־*/
				CommDeriction = 0;
				return C_DecodeFlay;
			}
		}
		else
		{
			if( ( ( V_FrameFlag & 0x0FFF ) + 1 ) * ( Com_Conect.ClientTxMaxLen - 23 ) < CommAPDULen )	/*С��1��APDU����Ӧ�𣬷���Ӧ�����*/
			{
				CommFrameNum = (V_FrameFlag & 0x0FFF);			/*ȡ֡���*/
			}
			else
			{
				return C_Error;
			}
		}

	}
	else
	{
		CommFrameNum = 0;
		CommAPDULen = 0;
	}
	if( ( ( CommFrameNum * Com_Conect.ClientTxMaxLen ) > C_APDUMaxLen )		/*û֡��������ֽ���*֡��Ŵ������APDU*/
	 && ( C_SeverseToClient == CommDeriction ) )
	{
		CommFrameNum = 0;
		CommAPDULen = 0;
		return C_Error;
	}
	return C_OK;
}
/*********************************************************************************
����ԭ�ͣ�void Comm_Parse_698(uchar8 CommNo,uchar8	PowerFlag)
����������698��Լͨ�Ž�������
���������CommNoͨ���ţ�PowerFlagΪ�����־
�����������
���ز�����
����˵����
���û��ƣ�
��    ע��
**********************************************************************************/
void Comm_Parse_698(uchar8 CommNo, uchar8	PowerFlag)
{
	Str_Comm_645	V_698Frame;
	Str_Comm_645	V_645Frame;
	Str_Comm_Parm 	*pStr_Comm_Parm_Address;
	Str_Comm_698_RW *pV_698RWPara;
	uchar8	i, V_NextFrFlag;
	uchar8	CanParse = C_OK;
	ulong32	V_CommMsgNo, V_CompareTime = 0;
	uchar8	V_HaveMsgTx = C_Error;
    uchar8  V_DataBuf[CLAppStaticTimeout] = {0};
	ushort16 V_Len = CLAppStaticTimeout, V_usDataEncode;

/*����������ȫ�ֱ�����ʼ��*/
	Comm_ParseInit();
	SV_SetBPS_Flag = C_Error;			/*Ĭ�ϲ�������BPS*/

/*���е絽ͣ����أ���Ӧ��ֱ���˳���*/
	if(PowerFlag == C_PowerFalling)
	{
		return;
	}
	if(CommNo == C_Module)
	{
	  	SV_ModuleResetTimer24h = C_ModuleResetTimer24h;
	}

/*��ȡͨ����������ָ��*/
	SV_Comm_Parse_Local.SafeControlFlag = SV_Comm_Parse_Local.SafeControlFlag | C_W_SafeFlag_1;

	pStr_Comm_Parm_Address = Get_Str_Comm_Parm_Pointer(CommNo);
	if(pStr_Comm_Parm_Address == C_NULL)
	{
		Comm_ParseInit();
		return;		            		/*ͨ������ʵ�ʲ����ܡ������ˣ�Ҳ�����ͣ�ֱ���˳���*/
	}
	else
	{
		V_698Frame.ChannelNo = CommNo;
	}

/*��������֡��������Ϸ�����V_645Frame*/
	if( IfFrameOkSetV_698Frame( &V_698Frame, pStr_Comm_Parm_Address ) != C_OK )
	{
		InF_InitComm(CommNo);
		Comm_ParseInit();
		return;
	}

	/***************************��̬��ʱʱ��***************************/
	if(SV_Comm_Parse_Local.ClientAddrFlag == Master_Address)
	{
		InF_Read_Data(CAppStaticTimeout, V_DataBuf, &V_Len, &V_usDataEncode);            /*��̬��ʱʱ��*/
	}
	else
	{
		InF_Read_Data(CAppStaticTimeout_termal, V_DataBuf, &V_Len, &V_usDataEncode);     /*��̬��ʱʱ���ն�*/
	}

    V_CompareTime = PF_Buffer4ToUlong32_698(V_DataBuf);


	if(SV_Comm_Parse_Local.ClientAddrFlag == Termal_Address)
	{
        if(Com_Conect.ConectOverTime_termal != 0)
		{
			Com_Conect.ConectOverTime_termal = V_CompareTime;
			Com_Conect.CRC16 = PF_Cal_CRC((uchar8 *)&Com_Conect.ConectOverTime, C_ConectStruct_Len);    /*����Ӧ������ʱ��*/
		}
	}
	else
	{
        if(Com_Conect.ConectOverTime != 0)                              /*Ӧ��������Ч*/
        {
            Com_Conect.ConectOverTime = V_CompareTime;
            Com_Conect.CRC16 = PF_Cal_CRC((uchar8 *)&Com_Conect.ConectOverTime, C_ConectStruct_Len);    /*����Ӧ������ʱ��*/
        }
	}

	/***************************��֡����***************************/
	pV_698RWPara = Get_Str_698RWParm_Pointer(CommNo);                   /*ȡ����ṹ���ַ*/
	if( ( V_698Frame.C & 0x20 ) == 0x20 )                               /*��֡��־*/
	{
		CanParse = SF_DealFramePart(&V_698Frame, pStr_Comm_Parm_Address);
		if(CanParse == C_Error)
		{
			pV_698RWPara->ServiceFlag_First = C_Default_Request;
			pV_698RWPara->Rd_OI[0].Rd_Result = C_APDUDecode_Fault;
			V_698Frame.C &= 0xDF;                                       /*ȡ����֡��־*/
			CanParse = C_ServiceType_Err;
		}
		else if( CanParse != C_DecodeFlay )
		{
			Comm_AppendMsg(CMsg_Txd);
			goto AnsworDerictor;
		}
		else
		{
			CanParse = C_OK;
		}
	}
	else
	{
		;
	}

	/******************************************************/
	V_698Frame.PowerFlag = PowerFlag;
	V_698Frame.MAC_Verify = Security_Authentication(&V_698Frame);   	/*�ж��Ƿ�ȫ���䣬�ǰ�ȫ��������а�ȫ��֤*/

	if(V_698Frame.MAC_Verify != C_OK)
	{
		/*��֯Ӧ��ESAM��֤ʧ��*/
        CanParse = V_698Frame.MAC_Verify;
        if( V_698Frame.P_APDUStart[0] != C_REPORT_Response )   			/*�����ϱ���Ӧ*/
        {
            Comm_AppendMsg(CMsg_Txd);
        }
	}
/************************************************/
	if(CanParse == C_OK)
	{
		CanParse = SF_APDU_Decode(&V_698Frame, pV_698RWPara);			/*��APDU���н���*/
    }
/*����Ȩ���ж�*/
	if(CanParse == C_OK)
	{
		CanParse = Is_IR_Comm_ResponseErr_698(&V_698Frame, pV_698RWPara);
    }
/*�����֤Ȩ���ж�*/
	if(CanParse == C_OK)
	{
		CanParse = Is_ID_Comm_ResponseErr_698(&V_698Frame, pV_698RWPara);
    }
/*MAC����Ȩ���ж�*/
	if(CanParse == C_OK)
	{
		CanParse = Is_MAC_Judge_698(&V_698Frame, pV_698RWPara);
    }
/*��ȫȨ���ж�*/
	if(CanParse == C_OK)
	{
		CanParse = SF_Judge_ServiceRight(pV_698RWPara, &V_698Frame);	/*Ȩ����֤*/
	}

	if(CanParse == C_OK)												/*���и���������*/
	{
		SV_Comm_Parse_Local.SafeControlFlag = SV_Comm_Parse_Local.SafeControlFlag | C_W_SafeFlag_2;

		switch(pV_698RWPara->ServiceFlag_First)
		{
			case C_CONNECT_Request:     								/*����Ӧ������*/
				Connect_Service_Deal(pV_698RWPara, V_698Frame.Data,C_Comm_Data_MaxLen, &V_NextFrFlag);
			break;

			case C_GET_Request:		    								/*������*/
				Get_Service_Deal(pV_698RWPara, V_698Frame.Data, C_Comm_Data_MaxLen, &V_NextFrFlag);
			break;

			case C_SET_Request:		    								/*����*/
            {
                Set_Service_Deal(pV_698RWPara, V_698Frame.Data, C_Comm_Data_MaxLen, &V_NextFrFlag, &V_645Frame);
				if(pV_698RWPara->ServiceFlag_Second == C_SETGETNormalList_Request)
				{
                    pV_698RWPara->ServiceFlag_First = C_GET_Request;
                    pV_698RWPara->ServiceFlag_Second = C_GETNormal_Request;
					Get_Service_Deal(pV_698RWPara, V_698Frame.Data, C_Comm_Data_MaxLen, &V_NextFrFlag);
                    pV_698RWPara->ServiceFlag_First = C_SET_Request;
                    pV_698RWPara->ServiceFlag_Second = C_SETGETNormalList_Request;
				}
            }break;

			case C_RELEASE_Request:	    								/*�Ͽ�Ӧ������*/
				RELEASE_Service_Deal(SV_Comm_Parse_Local.ClientAddrFlag);
			break;

			case C_ACTION_Request:										/*����*/
            {
                V_645Frame.RNSICBit = V_698Frame.RNSICBit;     			/*���Ļ�������*/
                Action_Service_Deal(pV_698RWPara, V_698Frame.Data, C_Comm_Data_MaxLen, &V_NextFrFlag, &V_645Frame);
                if(pV_698RWPara->ServiceFlag_Second == C_ACTIONGETList_Request)
                {
                    pV_698RWPara->ServiceFlag_First = C_GET_Request;
                    pV_698RWPara->ServiceFlag_Second = C_GETNormal_Request;
                    Get_Service_Deal(pV_698RWPara, V_698Frame.Data, C_Comm_Data_MaxLen, &V_NextFrFlag);
                    pV_698RWPara->ServiceFlag_First = C_ACTION_Request;
                    pV_698RWPara->ServiceFlag_Second = C_SETGETNormalList_Request;
                }
            }break;
			case C_REPORT_Response:    									/*�ϱ�*/
            {
                Report_Service_Deal(pV_698RWPara, V_698Frame.Data, C_Comm_Data_MaxLen, &V_NextFrFlag);
#if 0
                V_HaveMsgTx = C_OK;
#endif
                break;
            }

			default:                									/*��֧�ֵķ���ֱ���˳�*/
			break;
		}
	}
	else
	{
		if(CanParse == C_ServiceType_Err)
		{
			pV_698RWPara->ServiceFlag_First = C_Default_Request;
		}
        if( ( V_698Frame.P_APDUStart[0] != C_REPORT_Response ) && ( ( V_698Frame.C & 0xC0 ) != 0x00 ) )  /*�����ϱ���Ӧ(�������ģ�*/
        {
            Comm_AppendMsg(CMsg_Txd);
        }
	}

AnsworDerictor:
	LightenCommSign(CommNo,PowerFlag);

/*�����ڲ���Ϣ��־�����ж�Ӧ����Ϣ����*/
	for(i = 0; i < C_MessageMaxNum; i++)
	{
		V_CommMsgNo = Comm_FetchMsg();

		if(V_CommMsgNo == CMsg_Null)
		{
			break;
		}

		switch(V_CommMsgNo)
		{
			case    CMsg_Txd:				                        	/*��������*/
            {
                if( ( V_698Frame.AddressFlag == C_AddrTypePtoP ) || ( V_698Frame.AddressFlag == C_AddrTypePtoX ) )		/*ֻ�е�����ҪӦ��*/
                {
                    V_HaveMsgTx = C_OK;
                    SF_APDU_Encode(&V_698Frame, pV_698RWPara);			/*���б���*/
                    CommMSg_StartTxd_698(CommNo);
                }
                else
                {
                    InF_InitComm(CommNo);
                }
            }break;

			case	CMsg_InitComm:										/*��ʼ��������Ϣ*/
				InF_InitComm(CommNo);
			break;

			case	CMsg_MeterClear:									/*���������Ϣ����*/
				Have_IPEvent_MeterClear(&V_645Frame);
			break;

            case	CMsg_DemandClear:									/*���������Ϣ����*/
				Have_IPEvent_DemandClear(&V_645Frame);
			break;

            default:
			break;
		}
	}

/*����Comm_ParseInit�˳�����*/
	if(V_HaveMsgTx == C_Error)
    {/*�������еĵط���ֱ���˳��ģ�û�д���������Ϣ������������������
     û�з�����Ϣ���ͳ�ʼ������*/
        InF_InitComm(CommNo);
    }

	Comm_ParseInit();
	return;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_JudgeAllAA(uchar8 *P_DataBuf,uchar8 P_DataLen)
�����������ж�ָ�����������Ƿ�ΪȫAA
���������	*P_DataBuf	�����׵�ַ P_DataLen	���ݳ���
�����������
���ز�����	C_OK������ΪȫAA
		C_Error�����ݲ�ΪȫAA
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_JudgeAllAA(uchar8 *P_DataBuf, uchar8 P_DataLen)
{
	uchar8	V_i, V_NumAA = 0;
	if(P_DataLen == 0)
	{
		return C_Error;
	}
	for( V_i = 0; V_i < P_DataLen; V_i++ )
	{
		if( *( P_DataBuf + V_i ) == 0xAA )
		{
			V_NumAA++;
		}
	}
	if(V_NumAA == P_DataLen)
	{
		return C_OK;
	}
	else
	{
		return C_Error;
	}
}
/*******************************************************************************
����ԭ�ͣ�void SF_Encode_VolRates(Struct_FrozenConvert_Type *pStr_Encode,uchar8 *pDataBuf,
			uchar8 *pData645Buf,ushort16 *pV_DataOff,ushort16 *pV_DataOff645)
����������	V_ulOAD_VRΪ��ѹ�ϸ���OAD��pDataBuf��������ݴ��buf�׵�ַ��pData645Buf����ǰ�����׵�ַ
			pV_DataOffΪ�����ƫ�ƣ�pV_DataOff645Ϊ����ǰ����ƫ��
���������*pDataBufΪ��������ݣ�*pV_DataOffΪ���������ƫ�ƣ�*pV_DataOff645Ϊ�����645����ƫ��
�����������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
void SF_Encode_VolRates(Struct_FrozenConvert_Type *pStr_Encode, uchar8 *pDataBuf, uchar8 *pData645Buf, ushort16 *pV_DataOff, ushort16 *pV_DataOff645)
{
	uchar8	V_Degree, j;
	ushort16 V_us698Len;

	pDataBuf[(*pV_DataOff)] = pStr_Encode->V_uc698Type;
	(*pV_DataOff)++;
	pDataBuf[(*pV_DataOff)] = pStr_Encode->V_uc698NextNum;
	(*pV_DataOff)++;

	if( ( (pStr_Encode->V_ulOAD) & 0x0000000F ) == 0x00000000 )
	{
		V_Degree = 2;
	}
	else
	{
		V_Degree = 1;
		(*pV_DataOff) = (*pV_DataOff) - 2;
	}

	for( j = 0; j < V_Degree; j++ )
	{
		pDataBuf[(*pV_DataOff)] = C_structure;
		(*pV_DataOff)++;
		pDataBuf[(*pV_DataOff)] = 5;
		(*pV_DataOff)++;

		pDataBuf[(*pV_DataOff)] = C_double_long_unsigned;		/*��ѹ���ʱ��*/
		V_us698Len = SF_GetDataTypeLen(&pDataBuf[(*pV_DataOff)]);
		V_us698Len = SF_DataExchangeTo698_BasicData(&(pDataBuf[(*pV_DataOff)]), &pData645Buf[(*pV_DataOff645)], V_us698Len, CLPer_Pass_MonitorTime);
		(*pV_DataOff) += (V_us698Len + 1);
		(*pV_DataOff645) += CLPer_Pass_MonitorTime;

		pDataBuf[(*pV_DataOff)] = C_long_unsigned;				/*��ѹ�ϸ���*/
		V_us698Len = SF_GetDataTypeLen(&pDataBuf[(*pV_DataOff)]);
		V_us698Len = SF_DataExchangeTo698_BasicData(&(pDataBuf[(*pV_DataOff)]), &pData645Buf[(*pV_DataOff645)], V_us698Len, CLPer_Pass_PassRate);
		(*pV_DataOff) += (V_us698Len + 1);
		(*pV_DataOff645) += CLPer_Pass_PassRate;

		pDataBuf[(*pV_DataOff)] = C_long_unsigned;				/*��ѹ������*/
		V_us698Len = SF_GetDataTypeLen(&pDataBuf[(*pV_DataOff)]);
		V_us698Len = SF_DataExchangeTo698_BasicData(&(pDataBuf[(*pV_DataOff)]), &pData645Buf[(*pV_DataOff645)], V_us698Len, CLPer_Pass_OverRate);
		(*pV_DataOff) += (V_us698Len + 1);
		(*pV_DataOff645) += CLPer_Pass_OverRate;

		pDataBuf[(*pV_DataOff)] = C_double_long_unsigned;		/*��ѹ������ʱ��*/
		V_us698Len = SF_GetDataTypeLen(&pDataBuf[(*pV_DataOff)]);
		V_us698Len = SF_DataExchangeTo698_BasicData(&(pDataBuf[(*pV_DataOff)]), &pData645Buf[(*pV_DataOff645)], V_us698Len, CLPer_Pass_OverUpTime);
		(*pV_DataOff) += (V_us698Len + 1);
		(*pV_DataOff645) += CLPer_Pass_OverUpTime;

		pDataBuf[(*pV_DataOff)] = C_double_long_unsigned;		/*��ѹ������ʱ��*/
		V_us698Len = SF_GetDataTypeLen(&pDataBuf[(*pV_DataOff)]);
		V_us698Len = SF_DataExchangeTo698_BasicData(&(pDataBuf[(*pV_DataOff)]), &pData645Buf[(*pV_DataOff645)], V_us698Len, CLPer_Pass_OverLowTime);
		(*pV_DataOff) += (V_us698Len + 1);
		(*pV_DataOff645) += CLPer_Pass_OverLowTime;

	}
}
/*******************************************************************************
����ԭ�ͣ�void Get_30230AState(uchar8 V_Flag,uchar8 *P_DataBuf,uchar8 *V_Len)
�����������������һ��ʱ��
���������*P_DataBuf	�����׵�ַ
		P_DataLen	���ݳ���
�����������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
void Get_30230AState(uchar8 V_Flag, uchar8 *P_DataBuf, uchar8 *V_Len)
{
    ulong32     V_EventNo[4] = {0x30230201, 0x201E0200, 0x20240200, 0xFFFFFFFF};
    uchar8      i,P_DataBuf645[10] = {0}, V_ucRetrun = C_Error;
    ushort16    V_usDataLen = 10;
    uchar8      V_Len698 = 8, V_Len645 = 7;
	Str_Read_T V_EventRead;
	Str_SuppInfo V_ucSupplementaryInformation;
	ushort16    V_ucSuppleInformationTemp[C_MAXRelatedOAD_Event * 3] = {0};		/*һ����־��ı������Ҫ2���ֽڣ��ٶ���һ���ֽ�����*/
	uchar8		V_ucRST[2]	= {0x09, 0x01};

	V_ucSupplementaryInformation.pV_usEncode = &V_ucSuppleInformationTemp[0];
    *V_Len = 1;
	V_EventRead.pV_ulROAD = &V_EventNo[0];				/*ODA��ֵ*/
	V_EventRead.pV_ucRST = &V_ucRST[0];					/*������ֵ*/
    for( i = 0; i < 10; i++ )
    {
		V_ucRetrun =  InF_GetData_Record(&V_EventRead, P_DataBuf645, &V_usDataLen, &V_ucSupplementaryInformation);
        if(V_ucRetrun == C_NoData)
        {
            break;
        }
        else
        {
            if(V_ucRetrun ==  C_OK)
            {
                if(V_Flag == P_DataBuf645[7])
                {
                    P_DataBuf[0] = C_date_time_s;
                    *V_Len = (uchar8)SF_DataExchangeTo698_BasicData(P_DataBuf, P_DataBuf645, V_Len698, V_Len645);
                    break;
                }
            }
            V_EventNo[0] += 0x00000001;
			V_ucRST[1] = V_ucRST[1] + 1;
        }
    }
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_PrograReactivePowerState(ulong32 V_Data_Id_OAD,uchar8 *P_DataBuf,ushort16 *V_Len)
����������	3023��0A���Եı���
���������*P_DataBuf	�����׵�ַ
		P_DataLen	���ݳ���
�����������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_PrograReactivePowerState(ulong32 V_Data_Id_OAD, uchar8 *P_DataBuf, ushort16 *V_Len)
{
    uchar8 i, V_DataOff = 0, V_Flag0 = 0, V_Flag1 = 1, V_Temp0[10] = {0}, V_Temp1[10] = {0}, V_Len0 = 8, V_Len1 = 8;

    if(*V_Len < 32)
    {
        return C_MaxResponseLen_ERR;
    }
    Get_30230AState(V_Flag0, V_Temp0, &V_Len0);
    Get_30230AState(V_Flag1, V_Temp1, &V_Len1);
    V_DataOff++;
    for( i = 0; i < 2; i++ )
    {
        if(V_Data_Id_OAD == 0x30230A00)
        {
            P_DataBuf[V_DataOff] = 2;
            V_DataOff++;
            P_DataBuf[V_DataOff] = 2;
            V_DataOff++;
        }
        P_DataBuf[V_DataOff] = C_enum;
        V_DataOff++;
        if( ( i == 0 ) && ( V_Data_Id_OAD != 0x30230A02 ) )
        {
            P_DataBuf[V_DataOff] = 0;               					/*�޹�1����Դ*/
        }
        else
        {
            P_DataBuf[V_DataOff] = 1;              						/*�޹�2����Դ*/
        }
        V_DataOff++;
        P_DataBuf[V_DataOff] = 2;
        V_DataOff++;
        P_DataBuf[V_DataOff] = 2;
        V_DataOff++;
        if(V_Data_Id_OAD == 0x30230A02)
        {
            i = 1;
        }
        if(i == 0)
        {
            if(V_Len0 == 1)
            {
                P_DataBuf[V_DataOff] = 0;
                V_DataOff++;
            }
            else
            {
                PF_CopyDataBytes(V_Temp0, &P_DataBuf[V_DataOff], 8);	/*����ʱ��*/
                V_DataOff += 8;
            }
        }
        else if(i == 1)
        {
            if(V_Len1 == 1)
            {
                P_DataBuf[V_DataOff] = 0;
                V_DataOff++;
            }
            else
            {
                PF_CopyDataBytes(V_Temp1, &P_DataBuf[V_DataOff], 8);
                V_DataOff += 8;
            }
        }
        P_DataBuf[V_DataOff] = 0;                   					/*����ʱ��*/
        V_DataOff++;
        if(V_Data_Id_OAD == 0x30230A01)
        {
            break;
        }
    }
    *V_Len = V_DataOff;
    P_DataBuf[0] = V_DataOff - 1;
    return C_OK;
}
/*******************************************************************************
����ԭ�ͣ�void SF_GetCommChanelCurrentLen(uchar8	V_ucChanelNo)
������������ȡ��ǰͨ��ͨ�ŵĳ���
���������V_ucChanelNoͨ���ţ�Com_Conect
�����������
���ز�����ͨ��Ĭ�ϳ���
����λ�ã�
��    ע��
*******************************************************************************/
void SF_GetCommChanelCurrentLen(uchar8	V_ucChanelNo)
{
	/**********�жϵ�ǰͨ��Ӧ�������Ƿ���Ч***********/
	if( ( InF_ConectTimer_DealNoTimer() == C_TimerEnable )					/*Ӧ��������Ч*/
	 && ( V_ucChanelNo == Com_Conect.Com_NO ) )
	{
		Com_Conect.ClientTxMaxLen = Com_Conect.CurrentConectAPDULen_Tx;
		Com_Conect.ClientRxMaxLen = Com_Conect.CurrentConectAPDULen_Rx;
	}
	else
	{
		Com_Conect.ClientTxMaxLen = C_CommRxMaxLen[V_ucChanelNo];
		Com_Conect.ClientRxMaxLen = C_CommRxMaxLen[V_ucChanelNo];
	}
	Com_Conect.CRC16 = PF_Cal_CRC((uchar8 *)&Com_Conect.ConectOverTime, C_ConectStruct_Len);
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_DataLen_AXDR_Encode(uchar8 *pV_DataBuf,ushort16 V_DataLen)
�����������Բ��������ݳ��Ƚ��б���
���������	pV_DataBuf���ȱ����������ʼ��ַ��V_DataLen���ݳ���
���������	*pV_DataBuf���ȱ�����
���ز��������ȱ�����ռ�ֽ���
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_DataLen_AXDR_Encode(uchar8 *pV_DataBuf, ushort16 V_DataLen)
{
	if(V_DataLen > 255)
	{
		pV_DataBuf[0] = 0x82;
		pV_DataBuf[1] = (uchar8)(V_DataLen >> 8);
		pV_DataBuf[2] = (uchar8)(V_DataLen);
		return 3;
	}
	else if(V_DataLen > 127)
	{
		pV_DataBuf[0] = 0x81;
		pV_DataBuf[1] = V_DataLen;
		return 2;
	}
	else
	{
		pV_DataBuf[0] = V_DataLen;
		return 1;
	}
}
/*******************************************************************************
����ԭ�ͣ�void SF_OverAPDU_DealWith(uchar8 *pV_return, ushort16 *pV_DataOff, ushort16 V_LastDataOff, uchar8 *pV_NextTimeNew, uchar8 *pV_NextTimeOld)
����������
���������
���������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
void SF_OverAPDU_DealWith(uchar8 *pV_return, ushort16 *pV_DataOff, ushort16 V_LastDataOff, uchar8 *pV_NextTimeNew, uchar8 *pV_NextTimeOld)
{
	*pV_return = C_MaxResponseLen_ERR;
	*pV_DataOff = V_LastDataOff;										/*��ֵ��һ����¼����ƫ�Ƶ�ַ*/
	PF_CopyDataBytes(pV_NextTimeOld, pV_NextTimeNew, 6);				/*��ֵ��һ����ʱ��*/
}
/*******************************************************************************
����ԭ�ͣ�void InF_WriteFreezeTimeToBufer(uchar8 *pV_FreezeTimeBuf,uchar8 *pV_CurrentTime,uchar8 V_Mode)
���������������һ����ȡ������д�뻺��
���������	pV_DataBuf���N������ʱ�仺����ڣ�pV_CurrentTime��ǰ����ʱ���׵�ַ
			pV_DataBuf[0]����Ƿ���Ҫ����ʱ���־,0x68��ʾ��Ҫ����ʱ��
���������*pV_DataBuf���N������ʱ�䣬��ʽΪ�ꡢ�¡��ա�ʱ���֡��룬��������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
void InF_WriteFreezeTimeToBufer(uchar8 *pV_FreezeTimeBuf, uchar8 *pV_CurrentTime, uchar8 V_Mode)
{
	uchar8 i, V_LenTemp;

    if(V_Mode == C_645Mode)
    {
        V_LenTemp = C_645FreezeMAXRelatedOAD;
    }
    else
    {
        V_LenTemp = C_SaveFreezeTimeNum;
    }
	if(pV_FreezeTimeBuf[0] == 0x68)
	{
        for( i = 0; i < ( V_LenTemp - 1 ); i++ )
		{
            PF_CopyDataBytes(&pV_FreezeTimeBuf[(V_LenTemp - i - 2) * C_FreezeTimeLen + 1], &pV_FreezeTimeBuf[(V_LenTemp - i - 1) * C_FreezeTimeLen + 1], C_FreezeTimeLen);
		}
		PF_CopyDataBytes(pV_CurrentTime, &pV_FreezeTimeBuf[1], C_FreezeTimeLen);
	}
}
/*******************************************************************************
����ԭ�ͣ�void Inf_DealReportNum(uchar8 *p_ReportNo,uchar8 Len)
���������������ϱ�
���������
�����������
���ز�����
����λ�ã�
��    ע�������ϱ���֡
*******************************************************************************/
void Inf_DealReportNum(uchar8 *p_ReportNo,uchar8 Len)
{
    uchar8 i;

    for( i = 0; i < Len; i++ )
    {
        if( ( *(p_ReportNo + 1 + i * C_OneReportLen ) ) > C_ActiveReportMaxNum )		/*����ϱ�ʣ�����>Լ���ϱ�����������ֱ������*/
        {
            ( *(p_ReportNo + 1 + i * C_OneReportLen ) ) = 0;
        }
        if( ( *(p_ReportNo + 1 + i * C_OneReportLen ) ) > 0 )
        {
            ( *(p_ReportNo + 1 + i * C_OneReportLen ) ) --;
        }
    }
}
/*******************************************************************************
����ԭ�ͣ�void Inf_CommReport(uchar8  PowerFlag)
���������������ϱ�
���������
�����������
���ز�����
����λ�ã�
��    ע�������ϱ���֡
*******************************************************************************/
void Inf_CommReport(uchar8  PowerFlag)
{
    uchar8 V_ReportBufTemp[C_ModuleMaxLen], V_ReportAPDUTemp[C_ModuleMaxLen];
	ushort16	V_DataLen, i, V_ReportAPDUOffset, V_ReportAPDULen;
	uchar8	   V_SecurityLenoff, V_First68Off = 4;
    ushort16    V_Len, V_usLen = 0, V_usDataEncode;
    uchar8      RN_Data[C_RNLen], MAC_Data[C_MACLen];

    memset(RN_Data, 0xFF, C_RNLen);
    memset(MAC_Data, 0xFF, C_MACLen);
    if(PowerFlag != C_PowerOn)
    {
        return;
    }
    if(C_MeterType_Module != Inf_GetMeterType())        		/*���û��ģ��ı��ϱ�*/
    {
        return;
    }
    if( ( GV_ModuleCommuni_Flag != C_NoCommunication ) || ( Inf_Comm_REPORTFlag() !=C_ReportNULL ) )   /*���ͨ��ģ���ڽ��շ��͹�����*/
    {
        return;
    }
    if( 0 != Inf_Comm_ReportNum(C_OtherActiveReportInit) )				/*10s��ʱ���У���һ��ѭ����*/
    {
        return;
    }
    /*����255��������ȣ���������������208*/
    /*�ж��Ƿ�����Ҫ���͵����ݣ��Ƿ�3���ϱ��Ѿ����*/
    memset(V_ReportAPDUTemp, 0x00, C_ModuleMaxLen);
    Inf_GetReportData(V_ReportAPDUTemp, &V_usLen, C_Module, C_ActiveReportFlag);

    if(V_usLen == 1)
    {
        return;
    }

    V_ReportAPDUOffset = 0;
    V_ReportAPDULen = 0;
	memset(&SV_REPORTCommBuff[V_ReportAPDUOffset], 0xFE, 4);			/*ǰ���ֽ�FE*/
    V_ReportAPDUOffset += 4;

    SV_REPORTCommBuff[V_ReportAPDUOffset] = 0x68;						/*��ʼ��68*/
    V_ReportAPDUOffset++;
    SV_REPORTCommBuff[V_ReportAPDUOffset] = 0;							/*L_L*/
    V_ReportAPDUOffset++;
    SV_REPORTCommBuff[V_ReportAPDUOffset] = 0;							/*L_H*/
    V_ReportAPDUOffset++;
    SV_REPORTCommBuff[V_ReportAPDUOffset] = (C_ServerStart_DIR | 0x03);	/*������C*/
    V_ReportAPDUOffset++;
    SV_REPORTCommBuff[V_ReportAPDUOffset] = 0x05;						/*��ַ�����ȸ�ֵ5*/
    V_ReportAPDUOffset++;

    V_Len = 12;
    if( InF_Read_Data( CComm_Address, &SV_REPORTCommBuff[V_ReportAPDUOffset], &V_Len, &V_usDataEncode ) != C_OK )
    {
        return;                                                 		/*ͨ�ŵ�ַ*/
    }
    SV_REPORTCommBuff[V_ReportAPDUOffset - 1] = (V_Len - 1);			/*��ַ����*/
    V_ReportAPDUOffset += V_Len;
    SV_REPORTCommBuff[V_ReportAPDUOffset] = 0x00;						/*CA��ַ*/
    V_ReportAPDUOffset++;

    V_ReportAPDUOffset += 2;											/*ƫ�Ƶ�ַ��HCS���һ���ֽ�*/

/************************��ȫ����***********************/
    SV_REPORTCommBuff[V_ReportAPDUOffset] = 0x10;
	V_ReportAPDUOffset++;
	{
		SV_REPORTCommBuff[V_ReportAPDUOffset] = 0x00;     				/*����*/
		V_ReportAPDUOffset++;

        V_ReportBufTemp[V_ReportAPDUOffset] = 0;						/*����Ϊ0*/
        V_SecurityLenoff = V_ReportAPDUOffset;							/*�ݴ氲ȫ����ƫ��*/
        V_ReportAPDUOffset++;
	}
/************************APDU����**************************/
	V_ReportBufTemp[V_ReportAPDUOffset] = C_REPORT_Response | 0x80;	    /*�����ϱ�*/
    V_ReportAPDUOffset++;
    V_ReportAPDULen++;
	V_ReportBufTemp[V_ReportAPDUOffset] = C_REPORTNormalList_Request;	/*�����ϱ�����*/
    V_ReportAPDUOffset++;
    V_ReportAPDULen++;
    V_ReportBufTemp[V_ReportAPDUOffset] = 0x01;	                        /*PIID*/
    V_ReportAPDUOffset++;
    V_ReportAPDULen++;

    memcpy(&V_ReportBufTemp[V_ReportAPDUOffset], V_ReportAPDUTemp, V_usLen);	/*�����ϱ������ݰ�������*/
	V_ReportAPDUOffset += V_usLen;
	V_ReportAPDULen += V_usLen;
/************************�����ϱ�����***********************/
    V_ReportBufTemp[V_ReportAPDUOffset] = 0x00;							/*�޸����ϱ�*/
	V_ReportAPDUOffset++;
	V_ReportAPDULen++;
/************************ʱ���ǩ����**************************/
    V_ReportBufTemp[V_ReportAPDUOffset] = 0;							/*��ʱ���ǩ*/
    V_ReportAPDUOffset++;
    V_ReportAPDULen++;

/************************SID_MAC����**************************/

    ushort16 V_APDULenTemp, V_APDULenTemp_Plain;
    uchar8	V_EncryptType;
    uchar8	V_ucEnOffset = 0;

    /***********���ĳ���*************/
    V_APDULenTemp = (V_ReportAPDUOffset - V_SecurityLenoff - 1) ;
    V_APDULenTemp_Plain = V_APDULenTemp;
    if(V_APDULenTemp_Plain > 255)
    {
        for( i = 0; i < V_APDULenTemp; i++ )
        {
            V_ReportBufTemp[V_ReportAPDUOffset + 2 - 1 - i] = V_ReportBufTemp[V_ReportAPDUOffset - 1 - i];
        }
        SV_REPORTCommBuff[V_SecurityLenoff] = 0x82;
        SV_REPORTCommBuff[V_SecurityLenoff + 1] = (uchar8)(V_APDULenTemp >> 8);
        SV_REPORTCommBuff[V_SecurityLenoff + 2] = (uchar8)(V_APDULenTemp);
        V_ReportAPDUOffset += 2;
        V_ReportAPDULen += 2;
        V_ucEnOffset = 2;
    }
    else if(V_APDULenTemp > 127)
    {
        for( i = 0; i < (V_ReportAPDUOffset - V_SecurityLenoff - 1); i++ )
        {
            V_ReportBufTemp[V_ReportAPDUOffset + 1 - 1 - i] = V_ReportBufTemp[V_ReportAPDUOffset - 1 - i];
        }
        SV_REPORTCommBuff[V_SecurityLenoff] = 0x81;
        SV_REPORTCommBuff[V_SecurityLenoff + 1] = (uchar8)(V_APDULenTemp);
        V_ReportAPDUOffset += 1;
        V_ReportAPDULen += 1;
        V_ucEnOffset = 1;
    }
    else
    {
        SV_REPORTCommBuff[V_SecurityLenoff] = V_ReportAPDUOffset - V_SecurityLenoff - 1;	/*��֤һ��*/
    }
    /***********��ȫ��֤����***********/
	V_EncryptType = 0x11;
    INF_S_Encrypt_698(&V_ReportBufTemp[V_SecurityLenoff + 1 + V_ucEnOffset], &V_APDULenTemp, RN_MAC_698, V_EncryptType, RN_Data, MAC_Data, SV_Comm_Parse_Local.ClientAddrFlag);

    /*���ESAM����Ҳ�ϱ���RN+MAC��ȫ0��ȥ*/
    V_ReportBufTemp[V_ReportAPDUOffset] = 0x02;
    V_ReportAPDUOffset++;
    V_ReportBufTemp[V_ReportAPDUOffset] = C_RNLen;
    V_ReportAPDUOffset++;
    GV_RNByte = V_ReportAPDUOffset;    									/*��¼�����ϱ�RN��ʼλ��*/
    memcpy(&V_ReportBufTemp[V_ReportAPDUOffset], RN_Data, C_RNLen);
    V_ReportAPDUOffset += C_RNLen;
    V_ReportBufTemp[V_ReportAPDUOffset] = C_MACLen;
    V_ReportAPDUOffset++;
    memcpy(&V_ReportBufTemp[V_ReportAPDUOffset], MAC_Data, C_MACLen);
    V_ReportAPDUOffset += C_MACLen;

    for( i = ( V_SecurityLenoff + 1 ); i < V_ReportAPDUOffset; i++ )	/*�����ݿ������ͻ���*/
    {
        SV_REPORTCommBuff[i]  = V_ReportBufTemp[i];
    }
/************************֡����**************************/
	V_DataLen = (V_ReportAPDUOffset) - 1 + 2 - V_First68Off;			/*ȥ��1�ֽ�68������2�ֽ�FCS*/
	PF_Ushort16ToBuffer2(&SV_REPORTCommBuff[1 + V_First68Off], &V_DataLen);
/************************����HCS**************************/
	V_DataLen = PF_Cal_CRC_698(&SV_REPORTCommBuff[1 + V_First68Off], ( V_Len + 2 + 1 + 2 ) );
	PF_Ushort16ToBuffer2(&SV_REPORTCommBuff[( V_Len + 2 + 1 + 2 ) + 1 + V_First68Off], &V_DataLen);
/************************����FCS**************************/
	V_DataLen = PF_Cal_CRC_698(&SV_REPORTCommBuff[1 + V_First68Off], ((V_ReportAPDUOffset) - 1-V_First68Off));
	PF_Ushort16ToBuffer2(&SV_REPORTCommBuff[V_ReportAPDUOffset], &V_DataLen);
/************************֡������**************************/
	V_ReportAPDUOffset += 2;
	SV_REPORTCommBuff[V_ReportAPDUOffset] = 0x16;
	V_ReportAPDUOffset += 1;

	SV_ReportSend.ReportLen = V_ReportAPDUOffset;
	Inf_CalReportCRC();
	CommMSg_StartTxd_698REPORT(C_Module, C_OtherActiveReportInit);
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_OrganizationEventReportData(ulong32 EventOAD,uchar8 *P_CommAPDUBuf,ushort16 *V_CommAPDULen)
�����������¼����������ϱ���֯���ݣ�Ŀǰֻ�е��磩
���������EventNo���¼���
			State��C_Happen_EventMsg �¼���������
�����������
���ز�����
����λ�ã�
��    ע�������ϱ���֡
*******************************************************************************/
uchar8 SF_OrganizationEventReportData(ulong32 EventOAD, uchar8 *P_CommAPDUBuf, ushort16 *V_CommAPDULen)
{
    uchar8              V_ReportAPDUTemp[C_ModuleMaxLen];
    uchar8              V_ArrNum, V_CommAPDUOffset=0;
    ushort16            V_usLen, V_DATALen = ((C_Comm_Data_MaxLen_698 - 9) - V_CommAPDUOffset);
    Str_Comm_698_RW     pV_698RWPara;
    ushort16	        V_DataLen, V_DataOff = 0;
    uchar8	        	V_LengthLen;

    pV_698RWPara.Rd_OI[0].RdOI.OAD = (EventOAD & 0xFFFFFFFE);                /*��1�ε���OAD����ֵ,����Ϊ0*/
    pV_698RWPara.Rd_OI[0].Rd_RecordSelect[0] = C_RSDSelector9;               /*����9��ȡ����*/
    pV_698RWPara.Rd_OI[0].Rd_RecordSelect[1] = 0x01;                         /*��1��*/
    pV_698RWPara.ServiceFlag_Second = C_GETRecord_Request;                   /*��һ�μ�¼*/
    pV_698RWPara.FrameNUM = 0;                                               /*û�к���֡*/
    pV_698RWPara.ResponedNum = 1;
    pV_698RWPara.Rd_OI[0].Rd_Result = C_OK;
    pV_698RWPara.Rd_OI[0].RdOI.CarryNum = 0;
    V_usLen = C_REPORTListMaxLen;
    pV_698RWPara.Rd_OI[0].Rd_RecordRelatedOINum = 0;
    pV_698RWPara.ResponedRelationNum = 0;
    pV_698RWPara.CurrentOADEnd = 0;
    pV_698RWPara.Current_FrameNO = 0;
    pV_698RWPara.HaveEncodeNum = 0;
    pV_698RWPara.Rd_OI[0].Rd_Result = SF_GetAPDU_EventRead(&pV_698RWPara.Rd_OI[0], V_ReportAPDUTemp, &V_usLen, pV_698RWPara.ServiceFlag_Second);	/*���ݳ���+�����¼�+����*/

    if(pV_698RWPara.Rd_OI[0].Rd_Result == C_OK)
    {
		SF_EventOADRead(pV_698RWPara.Rd_OI[0],P_CommAPDUBuf + V_CommAPDUOffset, &V_DATALen, 1, &V_ArrNum);
		if(V_DATALen == 0)
		{
			V_DATALen = 1;
		}

		V_CommAPDUOffset += V_DATALen;
		(*V_CommAPDULen) += V_DATALen;

		/*******************��ȡ���ݽ��б���*********************/
		P_CommAPDUBuf[V_CommAPDUOffset] = 0x01;								/*�Խ��ѡ����б���*/
		V_CommAPDUOffset++;
		(*V_CommAPDULen)++;

		V_DataLen = SF_GetLengthFieldLen(V_ReportAPDUTemp, &V_LengthLen);

		V_DataOff += V_LengthLen;											/*V_DataOff == 0*/
		if(V_ReportAPDUTemp[V_DataOff - V_LengthLen] != 0)					/*��ʾ��ȡ�����¼���¼,���ǿ�*/
		{
			if( (V_CommAPDUOffset + V_DataLen) < C_REPORTListMaxLen )		/*ȷ��������ܳ�*/
			{
				PF_CopyDataBytes_698(&V_ReportAPDUTemp[V_DataOff], &P_CommAPDUBuf[V_CommAPDUOffset], V_DataLen);
				V_CommAPDUOffset += V_DataLen;
				(*V_CommAPDULen) += V_DataLen;
				V_DataOff += V_DataLen;
				pV_698RWPara.ResponedRelationNum++;
			}
			else
			{
				pV_698RWPara.Next_OINO = (pV_698RWPara.Current_FrameNO) + 1;
			}
		}
		else
		{
			P_CommAPDUBuf[V_CommAPDUOffset] = 0;							/*�Խ��ѡ����б���*/
			V_CommAPDUOffset++;
			(*V_CommAPDULen)++;
		}
		if(pV_698RWPara.HaveEncodeNum == (pV_698RWPara.ResponedNum - 1))	/*/�к���֡(��ʱ������recordlist���)*/
		{
			if(pV_698RWPara.CurrentOADEnd != 0x0f)
			{
				pV_698RWPara.HaveEncodeNum++;
			}
		}
		else
		{
			pV_698RWPara.HaveEncodeNum++;
		}
    }
    else
    {
		P_CommAPDUBuf[V_CommAPDUOffset] = C_GetResponseERR;
		V_CommAPDUOffset++;
		P_CommAPDUBuf[V_CommAPDUOffset] = pV_698RWPara.Rd_OI[0].Rd_Result;
		V_CommAPDUOffset++;
		(*V_CommAPDULen) += 2;
    }

    if(pV_698RWPara.Next_OINO == (pV_698RWPara.Current_FrameNO))
    {
		pV_698RWPara.Next_OINO = 0;
    }
    return pV_698RWPara.Rd_OI[0].Rd_Result;
}
/*******************************************************************************
����ԭ�ͣ� void Inf_MeterReportOpen(uchar8  PowerFlag, uchar8 SendNo)
�������������ܱ��Ƿ��ϱ�ͨ���������Ƿ������ϱ��������Ƿ���ģ���
���������
���������
���ز����� C_MeterReportClose 0x86:��������C_MeterReportOpen 0x68:����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 Inf_MeterReportOpen(uchar8  PowerFlag, uchar8 SendNo)
{
    uchar8	V_FollowFlag;
    uchar8	V_ChannelVaildFlag, V_AllowFollowTemp = 0;
	ushort16 V_BufferLen1 = CLAllowAccordUpTell, V_usDataEncode;

    if( ( PowerFlag == C_PowerOn ) || ( ( PowerFlag == C_PowerOff ) && ( SendNo == C_FirstNo ) ) )
    {
        V_FollowFlag = InF_Read_Data(CAllowAccordUpTell, &V_AllowFollowTemp, &V_BufferLen1, &V_usDataEncode);			/*�����ϱ�*/
        V_ChannelVaildFlag = SF_GetChannelVaild(C_Module);												/*����ϱ�ͨ��û�п��������ش���*/
        if( ( ( V_AllowFollowTemp == 1 ) && ( V_FollowFlag == C_OK ) ) && ( V_ChannelVaildFlag == C_OK ) )
        {
            if( C_MeterType_Module == Inf_GetMeterType() )												/*ֻ��ģ����ϱ�*/
            {
                GV_NeedReport_PowerDown = C_MeterReportOpen;
            }
            else
            {
                GV_NeedReport_PowerDown = C_MeterReportClose;
            }
        }
        else
        {
            GV_NeedReport_PowerDown = C_MeterReportClose;
        }
    }
    return GV_NeedReport_PowerDown;
}
/*******************************************************************************
����ԭ�ͣ� uchar8 Inf_EventTypeCommReport(uchar8  PowerFlag, uchar8 SendNo)
�����������¼����������ϱ���Ŀǰֻ�е��磩
���������
���������
���ز�����
����λ�ã�
��    ע�� �����ϱ���֡
*******************************************************************************/
uchar8 Inf_EventTypeCommReport(uchar8  PowerFlag, uchar8 SendNo)
{
	uchar8		V_ReportBufTemp[C_ModuleMaxLen], V_ReportAPDUTemp[C_ModuleMaxLen];
	uchar8		V_FunctionReturn = 0;
	ushort16	V_DataLen, i, V_ReportAPDUOffset, V_ReportAPDULen;
	uchar8		V_SecurityLenoff, V_First68Off = 4;
	ushort16	V_Len, V_usLen = 0, V_usDataEncode;
	uchar8		RN_Data[C_RNLen], MAC_Data[C_MACLen];
	ulong32		V_EventOAD = CPow_Down_Note_1;
	ushort16	V_APDULenTemp, V_APDULenTemp_Plain;
	uchar8		V_EncryptType;
	uchar8		V_ucEnOffset = 0;

	 memset(RN_Data, 0xFF, C_RNLen);
	memset(MAC_Data, 0xFF, C_MACLen);
	memset(V_ReportAPDUTemp, 0x00, C_ModuleMaxLen);

    Inf_MeterReportOpen(PowerFlag, SendNo);
    if(GV_NeedReport_PowerDown == 0x68)
    {
        if( ( ( PowerFlag == C_PowerOn ) && (0 == Inf_Comm_ReportNum( C_EventTypeActiveReportInit ) ) )			/*10s��ʱ���У���һ��ѭ����*/
         || ( PowerFlag == C_PowerOff ) )
        {
            /*�������͹���ʱ���ϵ��ͣ���ϱ�û�б��꣬��������*/
            if( ( GV_ModuleCommuni_Flag == C_NoCommunication ) && ( Inf_Comm_REPORTFlag() == C_ReportNULL ) )	/*���ͨ��ģ�鲻���ڽ��շ��͹����в���û�з��������¼��ϱ�*/
            {
                if( ( Inf_Event_REPORTONumDeal(C_ActiveReportFlag) == C_OK ) )
                {
                    if(SendNo == C_FirstNo)
                    {
                        V_ReportAPDUOffset = 0;
                        V_ReportAPDULen = 0;
                        memset(&SV_REPORTCommBuff[V_ReportAPDUOffset], 0xFE, 4);					/*ǰ���ֽ�FE*/
                        V_ReportAPDUOffset += 4;
                        SV_REPORTCommBuff[V_ReportAPDUOffset] = 0x68;								/*��ʼ��68*/
                        V_ReportAPDUOffset++;
                        SV_REPORTCommBuff[V_ReportAPDUOffset] = 0;									/*L_L*/
                        V_ReportAPDUOffset++;
                        SV_REPORTCommBuff[V_ReportAPDUOffset] = 0;									/*L_H*/
                        V_ReportAPDUOffset++;
                        SV_REPORTCommBuff[V_ReportAPDUOffset] = (C_ServerStart_DIR | 0x03);			/*������C*/
                        V_ReportAPDUOffset++;
                        SV_REPORTCommBuff[V_ReportAPDUOffset] = 0x05;								/*��ַ�����ȸ�ֵ5*/
                        V_ReportAPDUOffset++;
                        V_Len = 12;
                        if( InF_Read_Data(CComm_Address, &SV_REPORTCommBuff[V_ReportAPDUOffset], &V_Len, &V_usDataEncode) == C_OK )
                        {
                            SV_REPORTCommBuff[V_ReportAPDUOffset-1] = (V_Len - 1);					/*��ַ����*/
                            V_ReportAPDUOffset += V_Len;
                            SV_REPORTCommBuff[V_ReportAPDUOffset] = 0x00;							/*CA��ַ*/
                            V_ReportAPDUOffset++;
                            V_ReportAPDUOffset += 2;												/*ƫ�Ƶ�ַ��HCS���һ���ֽ�*/

                            if( ( PowerFlag == C_PowerOn ) && ( SF_Judge_EventIntegrity(C_PowerfailEventNo) != C_Happen_EventState ) )  /*�ϵ粢�Ҳ��ǵ��緢�����������RN�ϱ�*/
                            {
                                SV_REPORTCommBuff[V_ReportAPDUOffset] = 0x10;
                                V_ReportAPDUOffset++;
                                {
                                    SV_REPORTCommBuff[V_ReportAPDUOffset] = 0x00;					/*����*/
                                    V_ReportAPDUOffset++;
                                    V_ReportBufTemp[V_ReportAPDUOffset] = 0;						/*����Ϊ0*/
                                    V_SecurityLenoff = V_ReportAPDUOffset;							/*�ݴ氲ȫ����ƫ��*/
                                    V_ReportAPDUOffset++;
                                }
                            }
                            else
                            {
                                V_SecurityLenoff = V_ReportAPDUOffset - 1;							/*�ݴ氲ȫ����ƫ��*/
                            }
                            V_ReportBufTemp[V_ReportAPDUOffset] = C_REPORT_Response | 0x80;			/*�����ϱ�*/
                            V_ReportAPDUOffset++;
                            V_ReportAPDULen++;
                            V_ReportBufTemp[V_ReportAPDUOffset] = C_REPORTRecordList_Request;		/*�����ϱ�����,�¼�����*/
                            V_ReportAPDUOffset++;
                            V_ReportAPDULen++;
                            V_ReportBufTemp[V_ReportAPDUOffset] = 0x01;	                        	/*PIID*/
                            V_ReportAPDUOffset++;
                            V_ReportAPDULen++;
                            V_ReportBufTemp[V_ReportAPDUOffset] = 0x01;	                        	/*�ϱ��¼�1��*/
                            V_ReportAPDUOffset++;
                            V_ReportAPDULen++;
                            PF_Ulong32ToBuffer4_698(&V_ReportBufTemp[V_ReportAPDUOffset], &V_EventOAD, C_OADLen);      	/*���1�ε���OAD*/
                            V_ReportAPDUOffset = V_ReportAPDUOffset + C_OADLen;
                            V_ReportAPDULen = V_ReportAPDULen + C_OADLen;


                            SF_OrganizationEventReportData(V_EventOAD,V_ReportAPDUTemp,&V_usLen);		/*���������ϱ�����*/

                            memcpy(&V_ReportBufTemp[V_ReportAPDUOffset],V_ReportAPDUTemp,V_usLen);		/*�����ϱ������ݰ�������*/

                            V_ReportAPDUOffset += V_usLen;
                            V_ReportAPDULen += V_usLen;
                            V_ReportBufTemp[V_ReportAPDUOffset] = 0x00;									/*�޸����ϱ�*/
                            V_ReportAPDUOffset++;
                            V_ReportAPDULen++;
                            V_ReportBufTemp[V_ReportAPDUOffset] = 0;									/*��ʱ���ǩ*/
                            V_ReportAPDUOffset++;
                            V_ReportAPDULen++;
                            V_APDULenTemp = (V_ReportAPDUOffset - V_SecurityLenoff - 1) ;
                            V_APDULenTemp_Plain = V_APDULenTemp;
                            if(V_APDULenTemp_Plain > 255)
                            {
                                for(i = 0; i < V_APDULenTemp; i++)
                                {
                                  V_ReportBufTemp[V_ReportAPDUOffset + 2 - 1 - i] = V_ReportBufTemp[V_ReportAPDUOffset - 1 - i];
                                }
                                SV_REPORTCommBuff[V_SecurityLenoff] = 0x82;
                                SV_REPORTCommBuff[V_SecurityLenoff + 1] = (uchar8)(V_APDULenTemp >> 8);
                                SV_REPORTCommBuff[V_SecurityLenoff + 2] = (uchar8)(V_APDULenTemp);
                                V_ReportAPDUOffset += 2;
                                V_ReportAPDULen += 2;
                                V_ucEnOffset = 2;
                            }
                            else if(V_APDULenTemp > 127)
                            {
                                for(i = 0; i < (V_ReportAPDUOffset - V_SecurityLenoff - 1); i++)
                                {
                                    V_ReportBufTemp[V_ReportAPDUOffset + 1 - 1 - i] = V_ReportBufTemp[V_ReportAPDUOffset - 1 - i];
                                }
                                SV_REPORTCommBuff[V_SecurityLenoff] = 0x81;
                                SV_REPORTCommBuff[V_SecurityLenoff + 1] = (uchar8)(V_APDULenTemp);
                                V_ReportAPDUOffset += 1;
                                V_ReportAPDULen += 1;
                                V_ucEnOffset = 1;
                            }
                            else
                            {
                                SV_REPORTCommBuff[V_SecurityLenoff] = V_ReportAPDUOffset - V_SecurityLenoff - 1;	/*��֤һ��*/
                            }
                            if( ( PowerFlag == C_PowerOn ) && ( SF_Judge_EventIntegrity(C_PowerfailEventNo) != C_Happen_EventState ) )  /*�ϵ粢�Ҳ��ǵ��緢�����������RN�ϱ�*/
                            {
                                V_EncryptType = 0x11;
                                INF_S_Encrypt_698(&V_ReportBufTemp[V_SecurityLenoff + 1 + V_ucEnOffset], &V_APDULenTemp, RN_MAC_698, V_EncryptType, RN_Data, MAC_Data, SV_Comm_Parse_Local.ClientAddrFlag);
                                V_ReportBufTemp[V_ReportAPDUOffset] = 0x02;
                                V_ReportAPDUOffset++;
                                V_ReportBufTemp[V_ReportAPDUOffset] = C_RNLen;
                                V_ReportAPDUOffset++;
                                GV_RNByte = V_ReportAPDUOffset;     						/*��¼�����ϱ�RN��ʼλ��*/
                                memcpy(&V_ReportBufTemp[V_ReportAPDUOffset], RN_Data, C_RNLen);
                                V_ReportAPDUOffset += C_RNLen;
                                V_ReportBufTemp[V_ReportAPDUOffset] = C_MACLen;
                                V_ReportAPDUOffset++;
                                memcpy(&V_ReportBufTemp[V_ReportAPDUOffset], MAC_Data, C_MACLen);
                                V_ReportAPDUOffset += C_MACLen;
                            }

                            for(i = (V_SecurityLenoff + 1); i < V_ReportAPDUOffset; i++)	/*�����ݿ������ͻ���*/
                            {
                                SV_REPORTCommBuff[i]  = V_ReportBufTemp[i];
                            }

                            V_DataLen = (V_ReportAPDUOffset) - 1 + 2 - V_First68Off;		/*ȥ��1�ֽ�68������2�ֽ�FCS*/
                            PF_Ushort16ToBuffer2(&SV_REPORTCommBuff[1 + V_First68Off], &V_DataLen);
                            V_DataLen = PF_Cal_CRC_698(&SV_REPORTCommBuff[1 + V_First68Off], (V_Len + 2 + 1 + 2));
                            PF_Ushort16ToBuffer2(&SV_REPORTCommBuff[(V_Len + 2 + 1 + 2) + 1 + V_First68Off], &V_DataLen);
                            V_DataLen = PF_Cal_CRC_698(&SV_REPORTCommBuff[1 + V_First68Off], ((V_ReportAPDUOffset) - 1 - V_First68Off));
                            PF_Ushort16ToBuffer2(&SV_REPORTCommBuff[V_ReportAPDUOffset], &V_DataLen);
                            V_ReportAPDUOffset += 2;
                            SV_REPORTCommBuff[V_ReportAPDUOffset] = 0x16;
                            V_ReportAPDUOffset += 1;
                            SV_ReportSend.ReportLen = V_ReportAPDUOffset;

                            SV_ReportSend.Last_ReportLen = V_ReportAPDUOffset;  			/*������*/
                        }
                    }
                    else
                    {
                        SV_ReportSend.ReportLen = SV_ReportSend.Last_ReportLen;  			/*��ֵ�ϴε��ϱ�����*/
                    }

                    Inf_CalReportCRC();
                    V_FunctionReturn = C_EventTypeActiveReportInit;
                    CommMSg_StartTxd_698REPORT(C_Module, C_EventTypeActiveReportInit);
                }
            }
        }
    }

	return V_FunctionReturn;
}
/*******************************************************************************
����ԭ�ͣ�void InF_InitASaveData(uchar8	PowerFlag,uchar8 V_Channel)
�������������籣���ϱ�����/�ϵ�ָ�
���������
�����������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
void InF_InitASaveData(uchar8	PowerFlag,uchar8 V_Channel)
{
    uchar8      i, V_SaveDataTemp[CLNewReportList + 2];
    uchar8      *V_ChannelTemp;
    ushort16    V_CRC, V_Len=CLNewReportList, V_usDataEncode;
    switch(V_Channel)
    {
        case    C_ReportChannel1:
                V_ChannelTemp = GV_NewReport1;
                break;
        case    C_ReportChannel2:
                V_ChannelTemp = GV_NewReport2;
                break;
        case    C_ReportChannel3:
                V_ChannelTemp = GV_NewReport3;
                break;
        default:
                break;
    }
    memset(V_SaveDataTemp,0x00,CLNewReportList);
    if(PowerFlag == C_PowerOff)   											/*���籣������*/
    {
        for(i = 0; i < V_ChannelTemp[C_NewReportNumByte]; i++ )
        {
            V_SaveDataTemp[i * 2] = V_ChannelTemp[i * 3];
            V_SaveDataTemp[i * 2 + 1] = V_ChannelTemp[i * 3 + 1];
        }
        V_SaveDataTemp[C_NewReportSaveNumByte] = V_ChannelTemp[C_NewReportNumByte];
        V_CRC=PF_Cal_CRC_698(V_SaveDataTemp, CLNewReportList);
        PF_Ushort16ToBuffer2(&V_SaveDataTemp[CLNewReportList], &V_CRC);		/*1��CRC�Լ���*/
        InF_Write_Data(C_Msg_Communication, CNewReportList, V_SaveDataTemp, CLNewReportList + 2, C_W_SafeFlag);
    }
    else if(PowerFlag == C_PowerOn)  										/*�ϵ�ָ�����*/
    {
        if( InF_Read_Data( CNewReportList, V_SaveDataTemp, &V_Len, &V_usDataEncode ) == C_OK )
        {
            memset(V_ChannelTemp, 0x00, C_NewReportLen + 2);
            for(i = 0; i < V_SaveDataTemp[C_NewReportSaveNumByte]; i++ )
            {
                V_ChannelTemp[i * 3] = V_SaveDataTemp[i * 2];
                V_ChannelTemp[i * 3 + 1] = V_SaveDataTemp[i * 2 + 1];
            }
            V_ChannelTemp[C_NewReportNumByte] = V_SaveDataTemp[C_NewReportSaveNumByte];
            V_CRC=PF_Cal_CRC_698(V_ChannelTemp, C_NewReportLen);
            PF_Ushort16ToBuffer2(&V_ChannelTemp[C_NewReportLen], &V_CRC);
        }
    }
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_GetEsamIDFlag(void)
����������ESAM�����֤Ȩ�޿�����־�ж�
���������
�����������
���ز�����C_OK��ʾδ������C_Error��ʾ����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_GetEsamIDFlag(void)
{
	ushort16 V_BufRemainLen, V_usDataEncode;
	uchar8 V_Data[6] = {0};
	uchar8 V_ucReturn = C_OK;

	V_BufRemainLen = 1;
	V_ucReturn = InF_GetData_ObjectManage(CAuthenticationEnabled, (uchar8 *)&V_Data[0], &V_BufRemainLen, &V_usDataEncode);	/*��ȡESAM�������֤Ȩ�޿�����־*/
	if(V_ucReturn != C_OK)
	{
		V_BufRemainLen = 1;
		V_ucReturn = InF_GetData_ObjectManage(CAuthenticationEnabled, (uchar8 *)&V_Data[0], &V_BufRemainLen, &V_usDataEncode);	/*��ȡESAM�������֤Ȩ�޿�����־*/
	}
	if(V_ucReturn != C_OK)
	{
		V_ucReturn = C_OK;
	}
	else
	{
		if(V_Data[0] == 1)
		{
			V_ucReturn = C_Error;
		}
		else
		{
			V_ucReturn = C_OK;
		}
	}
    return  V_ucReturn;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_Judge_CuerrntIDFlag(void)
����������
���������
�����������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_Judge_CuerrntIDFlag(void)
{
	uchar8 V_ucReturn = C_OK;
	if(SV_Comm_Parse_Local.ClientAddrFlag == Termal_Address)		/*��ǰΪ�ն�ͨ��*/
	{
		if( ( JudgeTimerExceed10min(&ID_AuthT_T) != C_TimerEnable ) && ( Com_Conect.ConectOverTime_termal == 0 ) )	/*û�������֤��Ӧ������*/
		{
			V_ucReturn = C_OK;
		}
		else
		{
			V_ucReturn = C_Error;
		}
	}
	else
	{
		if(Com_Conect.ConectOverTime == 0)							/*û��Ӧ������*/
		{
			V_ucReturn = C_OK;
		}
		else
		{
			V_ucReturn = C_Error;
		}
	}
    return  V_ucReturn;
}
/*******************************************************************************
����ԭ�ͣ�uchar8 Is_ID_Comm_ResponseErr_698(Str_Comm_645 * pV_698Frame,Str_Comm_698_RW *pV_698RWPara)
��������������Ȩ���ж�
���������֡�����ṹ���ַpV_698Frame����������ṹ��pV_698RWPara
���������֡�Ƿ�Ϸ�
���ز��������ذ�ȫȨ���Ƿ�����Ҫ��C_OK��ʾ����Ȩ��Ҫ��
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 Is_ID_Comm_ResponseErr_698(Str_Comm_645 * pV_698Frame, Str_Comm_698_RW *pV_698RWPara)
{
	uchar8	i, V_ucSetNum, V_Buf2[C_TimerExceed10minLen];

	if(pV_698Frame->PowerFlag == C_PowerOff)
	{/*�����ڼ�,���������֤��Ч��������*/
		if(JudgeTimerExceed10min(&ID_AuthT_T) == C_TimerEnable)
		{/*ͣ���ڼ䣬���ԭ�Ⱥ�����֤��Ч����ȡ��������֤����ʱ�ᷢ*/
		/*�������֤������Ϣ*/
			memset( V_Buf2, 0, C_TimerExceed10minLen );
			DealWith_ID_Auth_T_Timer(C_Set_TimerExceed10min, V_Buf2);
		}
	}
	if(SF_GetEsamIDFlag() != C_OK)									/*���������֤Ȩ��*/
	{
		if( ( pV_698Frame->ChannelNo != C_IR ) && ( SF_Judge_CuerrntIDFlag() == C_OK ) )
		{
			if(pV_698RWPara->ServiceFlag_First == C_GET_Request)	/*��ȡ����*/
			{
	            for( i = 0; i < pV_698RWPara->RWOI_Num; i++ )
	            {
	                pV_698RWPara->ResponedNum++;					/*�Ѿ�Ӧ�����1*/
	                if( (pV_698RWPara->Rd_OI[i].RdOI.OAD & 0xFF000000) == 0x00000000 )
					{/*��ǰ���������ʣ���͸֧���*/
                        pV_698RWPara->Rd_OI[i].Rd_Result = C_OK;
                        continue;
					}
	                if( (pV_698RWPara->Rd_OI[i].RdOI.OAD & 0xFFFF0000) == 0xF1000000 )
					{/*ESAM������Կ��Զ�*/
                        pV_698RWPara->Rd_OI[i].Rd_Result = C_OK;
                        continue;
					}
                    if( (pV_698RWPara->Rd_OI[i].RdOI.OAD & 0xFF000000) == 0xF2000000 )
					{	/*ESAM������Կ��Զ�*/
                        pV_698RWPara->Rd_OI[i].Rd_Result = C_OK;
                        continue;
					}
	                if( (pV_698RWPara->Rd_OI[i].RdOI.OAD & 0xFFFF0000) == 0xF1010000 )
					{/*��ǰ���������ʣ���͸֧���*/
						pV_698RWPara->Rd_OI[i].Rd_Result = C_OK;
						continue;
					}
					if( (pV_698RWPara->Rd_OI[i].RdOI.OAD & 0xFFFF0000) == 0x40000000 )	/*����400005XX �㲥Уʱ����*/
					{
						pV_698RWPara->Rd_OI[i].Rd_Result = C_OK;
						continue;
					}
					switch(pV_698RWPara->Rd_OI[i].RdOI.OAD)
					{
						case		CMeter_Num:					/*���*/
						case		CComm_Address:				/*ͨ�ŵ�ַ*/
						case		CSoftw_Record_Number:		/*������*/
						case		CDate_Time:			/*��������-ʱ��*/
	                    case        CChargeBal_Hex_Cent:
	                    case        COverDraft_Hex_Cent:
						case        CM_Com_Ac_Tol_En_0:			/*��ǰ�¶�����й����ۼ��õ���*/
						case        CY_Com_Ac_Tol_En_0:			/*���ݽ����õ���*/
	                         	pV_698RWPara->Rd_OI[i].Rd_Result = C_OK;
	                    break;
						default:
	                            pV_698RWPara->Rd_OI[i].Rd_Result = C_Unauthorized_DAR;
								break;
	                }
				}
			}
			else if(pV_698RWPara->ServiceFlag_First == C_ACTION_Request)				/*��������*/
			{
	            for( i = 0; i < pV_698RWPara->RWOI_Num; i++ )
	            {
	                pV_698RWPara->ResponedNum++;										/*�Ѿ�Ӧ�����1*/
                    if( (pV_698RWPara->Wt_OI[i].WtOI & 0xFF000000) == 0xF2000000 )
                    {/*��������豸�ӿ�*/
                        pV_698RWPara->Wt_OI[i].Wt_Result = C_OK;
                        continue;
                    }
					switch(pV_698RWPara->Wt_OI[i].WtOI)
					{
						case		CDI_IRCReq:						/*������֤��������*/
						case		CDI_IR_ExtAuth:					/*������֤����*/
                            if(SV_Comm_Parse_Local.ClientAddrFlag == Master_Address)	/*��վ��֧�������֤*/
                            {
                                pV_698RWPara->Wt_OI[i].Wt_Result = C_RWForbid_DAR;
                            }
                            else
                            {
                                pV_698RWPara->Wt_OI[i].Wt_Result = C_OK;
                            }
                            break;
						case		0x80008300:						/*��������բ*/
							pV_698RWPara->Wt_OI[i].Wt_Result = C_OK;
	                        break;
                            case		0x50000300:					/*˲ʱ����*/
                                pV_698RWPara->Wt_OI[i].Wt_Result = C_OK;
	                        break;
                        case		0x40007F00:						/*�㲥Уʱ*/
							pV_698RWPara->Wt_OI[i].Wt_Result = C_OK;
	                        break;
                         case		0x20157F00:						/*�����ϱ�ȷ��֡*/
							pV_698RWPara->Wt_OI[i].Wt_Result = C_OK;
	                        break;
						default:
							pV_698RWPara->Wt_OI[i].Wt_Result = C_Unauthorized_DAR;
	                        break;
	                }
				}
			}
			else
			{
				for( V_ucSetNum = 0; V_ucSetNum < (pV_698RWPara->RWOI_Num); V_ucSetNum++ )
				{
                    pV_698RWPara->ResponedNum++;										/*�Ѿ�Ӧ�����1*/
                    if(pV_698RWPara->Wt_OI[V_ucSetNum].WtOI == 0x45000900)        		/*�ź�ǿ��*/
                    {
                        pV_698RWPara->Wt_OI[V_ucSetNum].Wt_Result = C_OK;
                    }
                    else
                    {
                        pV_698RWPara->Rd_OI[V_ucSetNum].Rd_Result = C_Unauthorized_DAR;
                        pV_698RWPara->Wt_OI[V_ucSetNum].Wt_Result = C_Unauthorized_DAR;
                    }
				}
			}
		}
	}
	return	C_OK;
}


