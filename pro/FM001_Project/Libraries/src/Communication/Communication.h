
/****************************************************************************************
Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     communication.h
Author		jiangzs
Version:       V1
Date:          2014-3-12
Description:   ͨ�Ŵ��������ļ�
Function List:
---------------------------------------------------------------------------------
History1:      ��1���޸�
����1. Date:
   	   Author:
       Modification:
---------------------------------------------------------------------------------
����2. Date:
   	   Author:
       Modification:
	---------------------------------------------------------------------------------
History2:      ��2���޸�
����1. Date:
   	   Author:
       Modification:
---------------------------------------------------------------------------------
����2. Date:
   	   Author:
       Modification:
***************************************************************************************/
#ifndef	__communication_H
#define	__communication_H

#include	"Public.h"
#include   "SecurityCommunication.h"

extern		uchar8	SV_SetBPS_Flag;								/*C_OK����BPS��C_Error����ͨ������*/
extern		uchar8 SV_Comm_Address[CLComm_Address + 2];			/*ͨ�ŵ�ַ*/
extern      ulong32 SV_ModuleResetTimer24h;   					/*24hģ��ͨ����λ*/

#define		C_ModuleResetTimer24h ( 24 * 60 * 60 * 1000 / 500 )	/*24hģ��ͨ����λ*/

/******************** �궨��************************************************************/
/*ʱ�������*/
#define	C_Sec						0			/*��*/
#define	C_Minute					1			/*��*/
#define	C_Hour						2			/*ʱ*/
#define	C_Day						3			/*��*/
#define	C_Month						4			/*��*/
#define	C_Year						5			/*��*/

#define	C_LoadTimeLen				5			/*���ɼ�¼ʱ��ĳ���*/
#define C_ReCal						0x78		/*����ֹʱ��ȵ�ǰʱ��󣬿���������*/
#define C_LoadTLength				5      		/*���ɼ�¼ʱ�䳤��*/
#define	C_EnergyLenForComm			4			/*ͨ�ŵ���һ�㳤��*/
#define	C_DemandLenForComm	    	8			/*ͨ������һ�㳤��3+5*/

#define C_CAddr_OFS_ForRx_698	    0x04		/*��ַ��ʼƫ��*/
#define C_CLenL_OFS_ForRx_698	    0x01		/*���ȵ��ֽ�ƫ��*/
#define C_CLenH_OFS_ForRx_698	    0x02		/*���ȸ��ֽ�ƫ��*/
#define C_CControl_OFS_ForRx_698	0x03		/*������ƫ��*/

/*645����Ӧ��Err��־*/
#define	C_RateNum_OV				0x40		/*��������*/
#define	C_PeriodNum_OV				0x41		/*��ʱ������*/
#define	C_SeasonNum_OV				0x42		/*��ʱ������*/
#define	C_Baud_NotModified			0x43		/*ͨ�����ʲ��ܸ���*/
#define	C_Unauthorized				0x44		/*δ��Ȩ/�����*/
#define	C_No_Request_data			0x45		/*����������*/
#define	C_OtherErr					0x46		/*��������*/
/**************************************************/
/*******************698����645����*****************/
#define	C_PeriodNum_OV_645			0x20		/*��ʱ������*/
#define	C_SeasonNum_OV_645			0x10		/*��ʱ������*/
#define	C_Baud_NotModified_645		0x08		/*ͨ�����ʲ��ܸ���*/
#define	C_Unauthorized_645			0x04		/*δ��Ȩ/�����*/
#define	C_No_Request_data_645		0x02		/*����������*/
#define	C_OtherErr_645				0x01		/*��������*/

#define	C_1200						2
#define	C_2400						3
#define	C_4800						4
#define	C_9600						6

#define	C_JudgeDI0FF  				0x000000FF
#define CL_EventFF_AALen   			1           /*��10���¼����ݿ飬��AA��AA����1�ֽ�*/

/****************************************************/

#define	C_Cal_LenErr				0xA0		/*У���ȴ���*/
#define	C_Cal_PWCanNotRD			0xA1		/*У��ʱ�����ܱ�У�����������*/
#define	C_Cal_IDErr					0xA2		/*У��ʱ����ʶ�����*/
#define	C_Cal_SPIErr				0xA3		/*У��ʱ��SPI����*/
#define	C_Cal_NOStartErr			0xA4		/*У��ʱ��δ����У�����*/
#define	C_Cal_PWOkButSetCPW			0xA5		/*�����ù�У�����룬�ظ�����У������*/
#define	C_Cal_WrMICOtherErr			0xA6		/*У��ʱд����оƬ��������*/
#define	C_Cal_WrDataErr				0xA7		/*У��ʱд���ݲ�У��Ĵ�������*/
#define	C_Cal_PW_Err				0xA8		/*У��ʱ�����*/
#define	C_Cal_NoErr					0xA9		/*У��ʱ��Ŵ���*/
#define	C_Cal_SafeFlagErr			0xAA		/*У��ʱ��ȫ�ֽڴ���*/
#define	C_YSettle_All99				0x68		/*����������ó�ȫ99*/
/*����ͨ�Ż�����ƫ��*/
#define	C_68_1_OFS_ForRx			0x00		/*ͨѶ�����������������ݽ���ʱ��1��68ƫ��*/
#define	C_CAddr_OFS_ForRx			0x01		/*ͨѶ�����������������ݽ���ʱͨ�ŵ�ַƫ��*/
#define	C_68_2_OFS_ForRx			0x07		/*ͨѶ�����������������ݽ���ʱ��2��68ƫ��	*/
#define	C_C_OFS_ForRx				0x08		/*ͨѶ�����������������ݽ���ʱCƫ��	*/
#define	C_L_OFS_ForRx				0x09		/*ͨѶ�����������������ݽ���ʱLƫ��	*/
#define	C_Data_OFS_ForRx			0x0A		/*ͨѶ�����������������ݽ���ʱ����ƫ��*/

#define	C_FE_OFS_ForTx				0x00		/*ͨѶ�����������������ݷ���ʱFEƫ��	*/
#define	C_68_1_OFS_ForTx			0x04		/*ͨѶ�����������������ݷ���ʱ��1��68ƫ��*/
#define	C_CAddr_OFS_ForTx			0x05		/*ͨ�Ž����������������ݷ���ʱͨ�ŵ�ַƫ��*/
#define	C_68_2_OFS_ForTx			0x0B		/*ͨѶ�����������������ݷ���ʱ��2��68ƫ��	*/
#define	C_C_OFS_ForTx				0x0C		/*ͨѶ�����������������ݷ���ʱCƫ��	*/
#define	C_L_OFS_ForTx				0x0D		/*ͨѶ�����������������ݷ���ʱLƫ��	*/
#define	C_Data_OFS_ForTx			0x0E		/*ͨѶ�����������������ݷ���ʱ����ƫ��*/

/******************698��������ƫ��**************************/
#define	C_First68_OFFSet_698		0x00		/*698֡��һ��68*/
#define	C_LH_OFFSet_698		    	0x02		/*698֡���ȸ��ֽ�*/
#define	C_LL_OFFSet_698		    	0x01		/*698֡���ȸ��ֽ�*/
#define	C_C_OFFSet_698				0x03		/*698֡�����ֽ�*/
#define	C_AF_OFFSet_698		    	0x04		/*698֡�е�ַ��ʼ�ֽ�:�Ͱ��ֽ�Ϊ��������ַ*/
#define	C_AddressFirst_698			0x05		/*698֡�е�ַ��һ���ֽ�*/


/*V_645Frame.Data������ƫ�Ƶ�ַ*/
#define	C_DI_OFS					0x00
#define	C_PW_OFS_14					0x04
#define	C_OPCode_OFS_14				0x08
#define	C_Data_OFS_14				0x0C
/*�����ر�־*/
#define	C_MeterAddress				0x68
#define	C_Broadcast					0x99
#define	C_Condense_AA_All			0xAA
#define	C_Condense_AA				0x0A
#define	C_AdrressError				0xFF
/*��Կ���*/
#define	CLen_Key					32			/*��Կ����*/
#define	C_TestKey					0x68		/*��Կ״̬Ϊ������Կ*/
#define	C_OfficialKey				0x86		/*��Կ״̬Ϊ��ʽ��Կ*/
#define	C_InitUpdataKeyState		0x00		/*��Կ״̬Ϊδ���¹�״̬,����3����Կ�ȿɱ�ʾ������Կ״̬���ֿɱ�ʾ������Կ״̬*/
#define	C_UpdataKeyProcess			0xFF		/*��Կ���¹�����,ֻ�ܱ�ʾ������Կ��һ��״̬*/
/*������*/
#define	C_SPT_Num_Over				0xE1		/*ָʾ��ȫ������*/
#define	C_KeyErr_Num_Over			0xE2		/*ָʾ������������*/
/*��Ϣ��־(��ע��ͨѶ�е���Ϣ��־�����ð�λ��ʽ�����ȡֵ��λȡֵ)*/
#define	C_MessageMaxNum				15			/*��Ϣ����	*/
#define	CMsg_Txd					0x00000001	/*������Ϣ	*/
#define	CMsg_InitComm				0x00000002	/*��ʼ��ͨ�ſ���Ϣ	*/
#define	CMsg_MeterClear				0x00000004	/*���������Ϣ	�յ�1A����ʱ����*/
#define	CMsg_DemandClear			0x00000008	/*����������Ϣ	�յ�19����ʱ����*/
#define	CMsg_EventClear				0x00000010	/*�¼�������Ϣ	�յ�1B����ʱ����*/
#define	CMsg_ProgTimePeriod			0x00000020	/*ʱ�α�����Ϣ	"�յ�14����1��ʱ�α���04010001-04010008��*/
												/*��2��ʱ�α���04020001-04020008"*/
#define	CMsg_ProgSeason				0x00000040	/*ʱ��������Ϣ	"�յ�14����1��ʱ������04010000*/
												/*��2��ʱ������04020000"*/
#define	CMsg_ProgWeekRest			0x00000080	/*�����ձ����Ϣ	�յ�14�������ձ��04000802*/
#define	CMsg_ProgHoliday			0x00000100	/*�������ձ����Ϣ	�յ�14���������ձ��04030001-040300FE*/
#define	CMsg_ProgCombPState			0x00000200	/*���״̬�ֱ����Ϣ	�յ�14�����״̬�֣��й����޹�1��2�����04000601-04000603*/
#define	CMsg_ProgCombQ1State		0x00000400
#define	CMsg_ProgCombQ2State		0x00000800
#define	CMsg_ProgSetADate			0x00001000	/*�����ձ����Ϣ	�յ�14����1-3�����ձ��04000B01-04000B03*/
#define	CMsg_ProgRate				0x00002000	/*���ʱ�����Ϣ	�յ�14�������׷��ʵ�۱��040501FF*/
#define	CMsg_ProgStepTariff			0x00004000	/*���ݱ�����Ϣ	�յ�14�������׽��ݵ�۱��040605FF*/
#define	CMsg_ProgDateTime			0x00008000	/*Уʱ��¼��Ϣ*/
#define	CMsg_PurchaseToDL			0x00010000	/*���ݲ��ֵ��Ϣ�����յ�Զ�̿�������ͳ�ֵ����ʱ����*/
#define	CMsg_ReturnMoney			0x00020000	/*�˷���Ϣ�����յ��˷�����ʱ����*/
#define	CMsg_BroadcastTime			0x00040000	/*�㲥Уʱ��¼��Ϣ*/
/*ͨ�Ž���������غ�*/
#define	C_First68_Ok				0x01
#define	C_Second68_Ok				0x04
#define	C_Len_Ok					0x10
#define	C_CS_Ok				    	0x20
#define	C_16_Ok						0x40
#define	C_CommRecFlagForInt_Ok		(C_First68_Ok | C_Second68_Ok | C_Len_Ok | C_CS_Ok | C_16_Ok)
#define	C_Comm_Buf_MaxLen			220
#define	C_Comm_Data_MaxLen			200			/*�������ݳ����Ϊ200*/
#define	C_Comm_FixedRxLen			12			/* 2��68+6�����+C+L+CS+16 = 12*/
#define	C_Comm_FixedTxLen			16			/*����4��FE*/
#define	C_Comm_RNData_MaxLen		35			/*���������*/
#define	C_CLenCS16_645	        	2		    /*cs,0x16����*/

#define	C_Comm_Buf_MaxLen_698		2020
#define	C_Comm_Data_MaxLen_698		2000		/*�������ݳ����Ϊ200*/
/*�¼���¼������ƫ��*/
#define	C_O_ProgClock				0
#define	C_O_OperateCode				6
#define	C_O_EventData				10

/*�������״̬����صĺ�*/
#define	CB_RemoteOAccount			0x80		/*Զ�̿�����bit15*/
#define	CO_RemoteOAccount			1			/*Զ�̿����ڵ������״̬��3�ĸ��ֽ�*/
#define	CB_LocalOAccount			0x40		/*���ؿ�����bit14*/
#define	CO_LocalOAccount			1			/*�ڵ������״̬��3�ĸ��ֽ�*/
#define	CB_IDAuth					0x20		/*�����֤״̬��bit13*/
#define	CO_IDAuth					1			/*�ڵ������״̬��3�ĸ��ֽ�*/
#define	CB_IRAuth					0x08		/*������֤��bit3*/
#define	CO_IRAuth					0			/*�ڵ������״̬��3�ĵ��ֽ�*/
#define	CB_IRAuth_T					0x04		/*�ն������֤��bit10*/
#define	CO_IRAuth_T					1			/*�ڵ������״̬��3�ĸ��ֽ�*/
#define	CB_IDAuth_T					0x08		/*�ն˰�ȫ��֤״̬��bit11*/
#define	CO_IDAuth_T					1			/*�ڵ������״̬��3�ĸ��ֽ�*/
/*������  */
#define	C_Duration_Alway			0xFFFF
#define	C_Duration_3s_L				0x03
#define	C_Duration_3s_H				0x00
#define	C_NoNxtFrame				0x00
#define	C_HaveNxtFrame				0x68

#define	C_SupperPW_OK				0x68

/*������ʱ���ʽ*/
#define	CDate_WW_Time_WW_O			3
#define	CDate_WW_Time_DD_O			4
#define	CDate_WW_Time_MM_O			5
#define	CDate_WW_Time_YY_O			6

#define C_FramePartValueLen			512		/*��·���֡��Ч���ݳ���*/
#define C_FramePartMaxLen			530		/*��·���֡���ͻ���*/
#define	C_FrameMaxLen				2048	/*һ֡������󳤶�*/
#define	C_APDUMaxLen				2000	/*APDU��󳤶�*/
#define	C_FrameMaxLen_698			2000	/*һ֡������󳤶�*/
/*********************����Ϊȫ�־�̬�����Ķ���*****************************************/
/*�ж�����645Э���698Э���ж�ʹ��*/
typedef struct
{
	ushort16    Len;						/*ͨѶ֡�ܳ��ȡ�����ʱ���յ�645����ʱ�ã�����ʱ����������ʱ��*/
	uchar8      RecFlag;					/*ͨѶ�����жϺϷ���־����Чʱ���ϣ�C_First68_Ok��*/
                                    		/*C_Second68_Ok��C_Len_Ok��C_cs_Ok��C_16_Ok��ȫ���Ϸ������ֽ�*/
                                    		/*ΪC_CommRecFlagForInt_Ok */
	uchar8	    ProtocolType;	    		/*��Լ����*/
}Str_Comm_Judge;
/*****ͨ��ͨ�Ż�����******/
typedef struct
{
	ushort16	Offset;						/*ͨѶ���ա�����ʱ��ƫ������ע�����ʱ���ܷ��ͻ��ǽ�*/
											/*�ն�����ʹ���ٵ���ָ��*/
	ushort16	FrameNum;					/*֡��ţ��Ѿ����յ�֡���*/
	ushort16	APDULen;					/*APDU����*/
	ushort16	APDUOffset;					/*APDUƫ��*/
	uchar8	Buff[C_FramePartMaxLen];		/*����ʱ��������FE������ʱ����4��FE*/
	uchar8	Buff_APDU[C_FrameMaxLen];		/*����ʱ��������FE������ʱ����4��FE*/
	uchar8	OTimer;							/*ͨѶ��ʱ��ʱ���Ӷ�ʱ��*/
	uchar8	AddrLen;						/*ͨѶ��ַ����*/
	uchar8	CommDeriction;					/*��֡�����߱�־*/
    Str_Comm_Judge Comm_Judge645; 			/*/645Э���жϽṹ��*/
    Str_Comm_Judge Comm_Judge698; 			/*/698Э���жϽṹ��*/
}Str_Comm_Parm;
#define	C_Comm_OTime				5		/*��ʱ��ʱ��ֵ*/
static	Str_Comm_Parm				SV_RS485_1_Comm_Parm @".DataProcessADDR";
static	Str_Comm_Parm				SV_RS485_2_Comm_Parm @".DataProcessADDR";
static	Str_Comm_Parm				SV_IR_Comm_Parm @".DataProcessADDR";
static	Str_Comm_Parm				SV_Module_Parm @".DataProcessADDR";

/*2020��׼�����ϱ�2005*/
#define CLMeterStatusNum (CLDrive_Report_Mode * 8)  /*ģ��ͨ���ĵ������״̬�ֵ��¼����ϱ�����*/
extern  uchar8 SV_REPORTCommBuff[C_ModuleMaxLen];
typedef struct
{
    ushort16    ReportLen;              	/*�����ϱ�����֡����*/
    ushort16    ReportFlag;             	/*��ǰ�Ƿ��������ϱ�����״̬*/
    ushort16    Last_ReportLen;         	/*�ϴη��͵ĳ���*/
    uchar8      ReportOffset;           	/*�����ϱ��ѷ���֡����*/
    uchar8      ReportOTimer;           	/*100ms��ʱ����ȥ����*/
    uchar8      PowerDown_ReportOTimer; 	/*�����ϱ���ȴ��ٴ��ϱ�ʱ��*/
    uchar8      ReportClearNum;         	/*�������ͨ��ʱ����2.5S��û�������ϱ��ɹ���������*/
    uchar8      V_CRC[2];
}Str_Report_Parm;
extern  Str_Report_Parm SV_ReportSend;
extern  uchar8  SV_PowerfailReportONum[3];
#define CL_SV_ReportParm      		sizeof(Str_Report_Parm)
#define C_ReportToTempVariable      0x68	/*report�ṹ�忽��������*/
#define C_TempVariableToReport      0x86	/*����������report�ṹ��*/

/*��д*/
#define	CommOffset		    pStr_Comm_Parm_Address->Offset
#define	CommLen		        pStr_Comm_Parm_Address->Comm_Judge698.Len
#define	CommBuff		    pStr_Comm_Parm_Address->Buff
#define	CommRecFlag	        pStr_Comm_Parm_Address->Comm_Judge698.RecFlag
#define	CommOTimer		    pStr_Comm_Parm_Address->OTimer
#define	CommAddrLen		    pStr_Comm_Parm_Address->AddrLen
#define	CommProtocolType	pStr_Comm_Parm_Address->Comm_Judge698.ProtocolType
#define CommAPDUOffset		pStr_Comm_Parm_Address->APDUOffset
#define CommAPDUBuf			pStr_Comm_Parm_Address->Buff_APDU
#define CommAPDULen			pStr_Comm_Parm_Address->APDULen
#define CommFrameNum		pStr_Comm_Parm_Address->FrameNum
#define CommDeriction		pStr_Comm_Parm_Address->CommDeriction
#define	CommLen645		    pStr_Comm_Parm_Address->Comm_Judge645.Len
#define	CommRecFlag645	    pStr_Comm_Parm_Address->Comm_Judge645.RecFlag
#define	CommProtocolType645	pStr_Comm_Parm_Address->Comm_Judge645.ProtocolType
/*�궨��*/
#define	C_ProtocolType_698			0x98	/*698Э��*/
#define	C_ProtocolType_NOT698		0x89	/*����698Э��*/
#define	C_ProtocolType_645			0x45	/*645Э��*/
#define	C_ProtocolType_NOT645		0x54	/*����645Э��*/
#define	C_ProtocolType_Init  		0x00	/*δ�ж�645Э�飬Ҳδ�ж�698Э�飬��ʼ��ֵ*/

/******����֡****************/
#define	LClockLen					5		/*���ɼ�¼��ʱ��Ϊ������ʱ��5�ֽ�*/
#define	CLen_CREnergy				16		/*���������ܼ���Ϊ�������й��ܣ�����޹�1��2��16�ֽ�*/
typedef struct
{
	ulong32	DataCode;						/*�������ʶ�롣ע���������ܵ��������ʶ��*/
	uchar8	FrameNo;						/*֡��ţ���ʾ��һ֡������վ�·���֡��š�*/
											/*11-1���к���֡��1*/
	uchar8	HaveReport;						/*�������ϱ���־C_Error��ʾδ�����ϱ���C_OK��ʾ�������ϱ�20140707����*/
	uchar8	FrameFinished;					/*C_OK��ʾ����֡�����ѽ�����C_Error��ʾ����֡����δ����*/
	ulong32	Nxt_DataCode;					/*��һ֡�������ݱ�ʶ��*/
	uchar8	LNxt_Fix_Time[LClockLen];		/*��һ֡���ɼ�¼��Ч���ݿ�ļ�¼ʱ��*/
	uchar8	LNxt_BlockNum;					/*��һ֡���ɼ�¼��Ҫ�������ݿ����*/
	uchar8	LNxt_CREnergy[CLen_CREnergy];	/*��һ֡���������ܼ���*/
	uchar8	Sub_DataCode;					/*���η������ݱ�ʶ��*/
	uchar8	LSub_Fix_Time[LClockLen];		/*���θ��ɼ�¼��Ч���ݿ�ļ�¼ʱ��*/
	uchar8	LSub_BlockNum;					/*���θ��ɼ�¼��Ҫ�������ݿ����*/
	uchar8	LSub_CREnergy[CLen_CREnergy];	/*�������������ܼ���*/
    uchar8  TotalBlockNum;					/*�ܶ������ݿ����*/
    uchar8  ReadedBlockNum;					/*�Ѿ����ߵĸ���*/
}Str_Comm_NxtFrame;
											/*ע1��DataCode��FrameNoΪ�ܵĺ���֡ʹ�õı�����*/
											/*ע2����Nxt�ģ���һ֡ʹ�õ��ķ����������11-1��������ʼ����*/
											/*ע3����Sub�ģ�����ʹ�õ��ķ����������12�����г�ʼ����Ϊ�����ܹ��ض�������֡��*/
static	Str_Comm_NxtFrame			SV_CommNxtFrame_RS485_1;
static	Str_Comm_NxtFrame			SV_CommNxtFrame_RS485_2;
static	Str_Comm_NxtFrame			SV_CommNxtFrame_IR;
static	Str_Comm_NxtFrame			SV_CommNxtFrame_Module;

#define	NxtF_DataCode				pStr_Comm_NxtFrame->DataCode
#define	NxtF_FrameNo				pStr_Comm_NxtFrame->FrameNo
#define	NxtF_HaveReport				pStr_Comm_NxtFrame->HaveReport
#define	NxtF_FrameFinished			pStr_Comm_NxtFrame->FrameFinished
#define	NxtF_Nxt_DataCode			pStr_Comm_NxtFrame->Nxt_DataCode
#define	NxtF_LNxt_Fix_Time			pStr_Comm_NxtFrame->LNxt_Fix_Time
#define	NxtF_LNxt_BlockNum			pStr_Comm_NxtFrame->LNxt_BlockNum
#define	NxtF_LNxt_CREnergy			pStr_Comm_NxtFrame->LNxt_CREnergy
#define	NxtF_Sub_DataCode			pStr_Comm_NxtFrame->Sub_DataCode
#define	NxtF_LSub_Fix_Time			pStr_Comm_NxtFrame->LSub_Fix_Time
#define	NxtF_LSub_BlockNum			pStr_Comm_NxtFrame->LSub_BlockNum
#define	NxtF_LSub_CREnergy			pStr_Comm_NxtFrame->LSub_CREnergy
#define NxtF_LNxt_ReadedBlockNum    pStr_Comm_NxtFrame->ReadedBlockNum
#define NxtF_LNxt_TotalBlockNum     pStr_Comm_NxtFrame->TotalBlockNum
/* 20140629���ۣ������÷����ʶ�������ȵ�������̫�˷ѿռ��ˡ�*/
/*���ǳ���������ݲ�����ݲ��ܳ��ȹ����������᷵��ʵ�ʳ��ȵ��ص㡣*/
typedef struct							/*�ܵ��������ʶ���*/
{
	ulong32  DataCode;					/*�ܵ��������ʶ�룬����DI0����������������Ч����11�������ж�*/
	ulong32	*pTB_SubDI;					/*�������ݱ�ʶ����ܱ���ַ��*/
	uchar8	SubDINum;					/*�����ʶ�������������ж��Ƿ񵽱��β��*/
	uchar8	Method;						/*ʹ��2����ķ�������2������*/
}Str_TBNxtFrame;
#define	C_Freeze_Method			01
#define	C_Prog_SubDI_LBit4		02		/*�����ʶ��ʹ�õ�4λ��Ϊ������������ȹ̶�Ϊ0x0A*/
#define	C_CarryingSubDI			03		/*�����ʶ��DI0�����������*/
#define	C_Event_Method			04  	/*�¼�����*/

/*����ķ����ʶ����ܶ��壨8�ඳ�ᣬʹ��һ�ű�񣬳����н���������DI2�����������ȥ����*/
#define	C_FreezeSubDILen		12
extern const	ulong32 		TB_FreezeSubDI[C_FreezeSubDILen];				/*��1�ζ�ʱ�����������*/

/*���㶳��*/
#define	C_HFreezeSubDILen		3
extern const	ulong32 		TB_HFreezeSubDI[C_HFreezeSubDILen];				/*��1�����㶳���������*/

/*�����¼���¼*/
#define	C_DCLREvent_SubDILen	2
extern const	ulong32	TB_DCLREvent_SubDI[C_DCLREvent_SubDILen];
/*ʱ�α���¼���¼*/
#define	C_ProgPT_SubDILen		4
extern const	ulong32	TB_ProgPT_SubDI[C_ProgPT_SubDILen];
/*�ڼ��ձ���¼�*/
#define	C_ProgHol_SubDILen	6
extern const	ulong32	TB_ProgHol_SubDI[C_ProgHol_SubDILen];
/*У���̼�¼*/
/*��ע��������Ҫע�⣬����������254�У�*/
/*��ʵ���ڵ�1�ű��У�����ʵ����Ч�����ʶ����ĿC_MeterICDataNum_T*/
#define	C_CalMReg_SubDILen	255
extern const	ulong32	TB_CalMReg_SubDI[C_CalMReg_SubDILen];
/*ʧ���¼���¼*/
#define	C_LossA_Curr_SubDILen		10
extern const	ulong32	TB_LossA_Curr_SubDI[C_LossA_Curr_SubDILen];

#define	C_LossB_Curr_SubDILen		10
extern const	ulong32	TB_LossB_Curr_SubDI[C_LossB_Curr_SubDILen];

#define	C_LossC_Curr_SubDILen		10
extern const	ulong32	TB_LossC_Curr_SubDI[C_LossC_Curr_SubDILen];

/*�����¼���¼*/
#define	C_OverA_Curr_SubDILen		10
extern const	ulong32	TB_OverA_Curr_SubDI[C_OverA_Curr_SubDILen];

#define	C_OverB_Curr_SubDILen		10
extern const	ulong32	TB_OverB_Curr_SubDI[C_OverB_Curr_SubDILen];

#define	C_OverC_Curr_SubDILen		10
extern const	ulong32	TB_OverC_Curr_SubDI[C_OverC_Curr_SubDILen];

/* 1����*/
#define	C_TBNxtFrameNum				11
extern const	Str_TBNxtFrame		TB_NxtFrame[C_TBNxtFrameNum];
/********************�������ʶ���ȡ�Ķ��������*********************************/
typedef struct					/*�ܵ��������ʶ���1����*/
{
	ulong32	DataCode;			/*�ܵ��������ʶ�룬�����ǲ��������ġ�*/
	ulong32	*pTB_SubDI;			/*�������ݱ�ʶ����ܱ���ַ��*/
	uchar8	SubDINum;			/*�����ʶ�������������ж��Ƿ񵽱��β��*/
}Str_TBCarryingSubDI_1;

/*�������ʶ�����2����*/
/*���ʵ��FF��ȡ�����ʶ��*/
#define			CLen_TB_RateFF_Price		12
extern const	ulong32	TB_Current_RateFF_Price[CLen_TB_RateFF_Price];
extern const	ulong32	TB_BackUp_RateFF_Price[CLen_TB_RateFF_Price];
/*�������״̬��*/
#define			CLen_TB_MeterStatus			8
extern const	ulong32	TB_MeterStatus[CLen_TB_MeterStatus];
/*�������й���1-4�޹����������ܴ���*/
#define			CLen_TB_De_Over_Degree		6
extern const	ulong32	TB_De_Over_Degree[CLen_TB_De_Over_Degree];

/*�������ʶ�����1����*/
#define			CLen_TBCarryingSubDI_1		4
extern	const	Str_TBCarryingSubDI_1		TBCarryingSubDI_1[CLen_TBCarryingSubDI_1];

#define			Pstr_ParaChange_Event_Len	27
extern const 	Str_ParaChange_OADToDI_Table Pstr_ParaChange_Event[Pstr_ParaChange_Event_Len];

/******ͨ�Ž���ȫ�ֱ���***/
typedef struct
{
	uchar8	SafeControlFlag;				/*��ȫ���Ʊ�־*/
	uchar8	MeterClearFlag;					/*��������־*/
	ulong32	MessageFlag;					/*��Ϣ��־��1λ��ʾ1����Ϣ����ע1*/
	uchar8	RecFlag;						/*ͨ�����ձ�־�û������ġ�*/
	uchar8	ClientAddrFlag;					/*ͨ�����ձ�־�û������ġ�*/
}Str_Comm_Parse_Local;
extern	Str_Comm_Parse_Local SV_Comm_Parse_Local;
/*ע1��ʹ��Comm_AppendMsg��Comm_FetchMsg����ͻ�ȡһ����Ϣ��־��*/

/*200�ι���ṹ��*/
typedef struct
{
	uchar8	Key0204_ErrNum;					/*02/04������������*/
	uchar8	Key04_ErrNum;					/*04������������*/
	uchar8	Num;							/*SafePendingThreshold��200�ι������*/
	uchar8	RecentClock[7];					/*���һ��SPT�����������ʱ�䣬�����жϿ���������־*/
	ushort16	Crc;
}Str_SPT;

#define	CLen_Str_SPT				12			/*����CRC��10���ֽڳ�*/
#define	C_SPTNum_Threshold			200			/*����ֵ*/
#define	C_Key0204_ErrThreshold		3			/*02/04��������������ֵ��*/

#define	C_KeyErrNumAdd				0x04		/*����������++*/
#define	C_JudgeKeyErr				0x05		/*�ж������������Ƿ�?*/
#define	C_ClrKeyErrNum				0x06		/*��Ϊ������3������������������ķ���*/
#define	C_Key02Flag					0x80		/*02�����봦���־*/
#define	C_Key04Flag					0x40		/*04�����봦���־*/
#define	C_SPTFlag					0x00		/*SPT�����봦���־*/

/*����10min�еĶ�ʱ������׼Ϊ500ms.*/
typedef struct
{
	uchar8		BaseTimer;						/* ������ʱ����Ϊ16������	*/
	ulong32		Timer;							/*����1minTimer��Ϊ10��������*/
	ushort16	Crc;
}Str_TimerExceed10min;
#define	C_StrTimerExceed10minLen	7
#define	C_TimerExceed10minLen		4
#define	C_Timer_Base_10minLen		5
#define	C_TimerDisable				0x00
#define	C_TimerEnable				0x68
#define	C_BaseTimer					120			/*������ʱ����ֵ����500ms����һ�οۼ�����Ϊ1min*/
												/* �����2.5s����һ�οۼ�����Ϊ5min��*/
#define	C_ProgKeyTime_L				0x40
#define	C_ProgKeyTime_H 			0x02		/*��̿��س�ֵ240���ӣ�4Сʱ*/
/*����ģ�鸴λ�ṹ��*/
#define	C_Flag_Ok					0x68		/*��־��ȷ*/
#define	C_Flag_Err					0x00		/*��־����*/
typedef struct
{
	uchar8	IsSet_GPRS_Signal;
	uchar8	IsRstModuleFlag;
}Str_RstModule;

#define	ProgOpClock				pProgRecord->FixedData
#define	ProgDI					pProgRecord->DI
#define	ProgCrc					pProgRecord->Crc

#define	ProgOpClock_645			pProgRecord_645->Opclock
#define	ProgOpCode_645			pProgRecord_645->OpCode
#define	ProgDI_645				pProgRecord_645->DI
#define	ProgCrc_645				pProgRecord_645->Crc


#define	C_Timer_1min			120
typedef struct
{
	uchar8						Timer_1min;					/*ͨ�ö�ʱ����1min*/
   	Str_SPT 					SPTVariable;				/*SafePendingThreshold��200�ι������*/
	Str_TimerExceed10min		ID_Authentication_Timer; 	/*�����֤ʣ��ʱ�䶨ʱ������ֵ�ɰ�ȫģ�������֤  �ӿں������ڲ�������*/
	Str_TimerExceed10min		IR_Authentication_Timer;	/*������֤��Ч��ʱ������ֵ�̶�Ϊ30min*/
	uchar8						SI_JBaseTimer;
	Str_TimerExceed10min		SI_JTimer;
	Str_TimerExceed10min		ProgramKey_Timer;			/*��̿���*/
	Str_TimerExceed10min		ID_Authentication_T_Timer;	/*�ն������֤��Ч��ʱ������ֵ�̶�Ϊ30min*/
	Str_RstModule				RstModuleParm;				/*��λģ����ز���*/
	uchar8						BDSC_RecentClock[7];		/*broadcastSetClck�����һ�ι㲥Уʱʱ�� YYMMDDhhmmss*/
	Str_ProgRecord				ProgRecord;					/*ͨѶģ�鶵�ı�̼�¼��Ҫȫ�ֱ�����������ģ���� ������Ƴ��ڲ�����*/
    Str_ProgRecord_645			ProgRecord_645;  			/*645��̼�¼����*/
	ushort16					Init_GPRS_DisplayTimer;		/*GPRS�ź�ǿ��,20min��д�ź�ǿ�����ź�ǿ������,������ʾ*/
	Str_TimerExceed10min		IR_Authentication_Timer_645;
}Str_Comm_Parse;

#define	C_SI_JBTimer_2500		5
extern Str_Comm_Parse			SV_Comm_Parse;

/*��д*/
#define	KEY02ErrNum				SV_Comm_Parse.SPTVariable.Key0204_ErrNum
#define	KEY04ErrNum				SV_Comm_Parse.SPTVariable.Key04_ErrNum
#define	SPTNum					SV_Comm_Parse.SPTVariable.Num
#define	SPTRecentClock			SV_Comm_Parse.SPTVariable.RecentClock
#define	SPTCrc					SV_Comm_Parse.SPTVariable.Crc

/*��д�����֤�����⡢��̿��ض��ǻ���500ms�������ġ�*/
#define	ID_AuthT				SV_Comm_Parse.ID_Authentication_Timer
#define	ID_AuthT_BaseTimer		SV_Comm_Parse.ID_Authentication_Timer.BaseTimer
#define	ID_AuthT_Timer			SV_Comm_Parse.ID_Authentication_Timer.Timer
#define	ID_AuthT_Crc			SV_Comm_Parse.ID_Authentication_Timer.Crc

#define	IR_AuthT				SV_Comm_Parse.IR_Authentication_Timer
#define	IR_AuthT_BaseTimer		SV_Comm_Parse.IR_Authentication_Timer.BaseTimer
#define	IR_AuthT_Timer			SV_Comm_Parse.IR_Authentication_Timer.Timer
#define	IR_AuthT_Crc			SV_Comm_Parse.IR_Authentication_Timer.Crc

#define	ProgKey_Timer			SV_Comm_Parse.ProgramKey_Timer
#define	ProgKeyT_BaseTimer		SV_Comm_Parse.ProgramKey_Timer.BaseTimer
#define	ProgKeyT_Timer			SV_Comm_Parse.ProgramKey_Timer.Timer
#define	ProgKeyT_Crc			SV_Comm_Parse.ProgramKey_Timer.Crc
#define	GPRS_DisplayTimer		SV_Comm_Parse.Init_GPRS_DisplayTimer

#define	ID_AuthT_T				SV_Comm_Parse.ID_Authentication_T_Timer
#define ID_AuthT_T_BaseTimer	SV_Comm_Parse.ID_Authentication_T_Timer.BaseTimer
#define	ID_AuthT_T_Timer		SV_Comm_Parse.ID_Authentication_T_Timer.Timer
#define	ID_AuthT_T_Crc			SV_Comm_Parse.ID_Authentication_T_Timer.Crc

/*698����645Э�飬���ⶨʱ��*/
#define	IR_AuthT_645			SV_Comm_Parse.IR_Authentication_Timer_645
#define	IR_AuthT_BaseTimer_645	SV_Comm_Parse.IR_Authentication_Timer_645.BaseTimer
#define	IR_AuthT_Timer_645		SV_Comm_Parse.IR_Authentication_Timer_645.Timer
#define	IR_AuthT_Crc_645		SV_Comm_Parse.IR_Authentication_Timer_645.Crc


/*��д����IJ��ʱ������2500ms*/
#define	SI_JTimer_BSOn2500		SV_Comm_Parse.SI_JTimer
#define	SI_JT_BaseTimer			SV_Comm_Parse.SI_JTimer.BaseTimer
#define	SI_JT_Timer				SV_Comm_Parse.SI_JTimer.Timer
#define	SI_JT_Crc				SV_Comm_Parse.SI_JTimer.Crc
#define	SI_JBaseTimer_2500		SV_Comm_Parse.SI_JBaseTimer			/*��IJ�������ģ�2.5s*/

#define	C_SI_JTimerHaveCRC_Len		7								/*SI_JTimer�ṹ�峤��BaseTimer+Timer+Crc*/
#define	C_SI_JTimer_Len				5								/*SI_JTimer�ṹ�峤��BaseTimer+Timer*/

#define	C_Init_GPRS_DisplayTimer	2400							/*��ʱ�ǻ���500ms��,������ﶨʱ2400,20����*/
/********* 645�����ݴ�ṹ��************/
typedef struct
{
	ulong32		DI;									/*698�����ݶ����ʶOI*/
	uchar8		*SecurityAddr;						/*��ȫ������ʼ��ַ,Frame��HCS������������ʼ��ַ*/
	uchar8		*P_APDUStart;						/*APDU��ʼ��ַ*/
	ushort16	DataLen_698;						/*���ܺ����������ݳ���*/
	ushort16	APDULen;							/*APDU�ܳ���*/
	ushort16	FrameBlockFlag;						/*��֡��־*/
	uchar8		Opcode[4];
	uchar8		AddrLen;							/*SA��ַ����*/
	uchar8		C;
	uchar8		StandardFlay;						/*��Լ��־*/
	uchar8		SECURITYFlay[3];					/*�Ƿ�ȫ�����־*/
	uchar8		SICMAC_Type;						/*��ȫ��֤���*/
	uchar8		DataLen;							/*���ܺ����������ݳ���*/
    uchar8		Data[C_Comm_Data_MaxLen_698];		/*��������������ԭʼ���������ݣ�����DI������*/
	uchar8		RN_Data[C_Comm_RNData_MaxLen];		/*��������������ԭʼ���������ݣ�����DI������*/
	uchar8		AddressFlag;						/* ȡֵC_MeterAddress,C_Broadcast,C_CondenseAll��C_Condense */
	uchar8		ChannelNo;							/*ͨ�����ݴ�*/
	uchar8		PowerFlag;							/*���ȹ����ĵ�Դ״̬�ݴ�*/
	uchar8		MAC_Verify;							/*��ȫ��֤���*/
	uchar8		ClientAddr;							/*�ͻ�����ַ*/
	uchar8		RNSICBit;							/*Ȩ����ռbitλ*/
    ushort16  	TimeTageByte;     					/*ʱ���ǩ���ڵ��ֽ�*/
}Str_Comm_645;

#define	CLen_DI						C_DataCodeLen
#define	CLen_OpCode					4
#define	CLen_CommPW					4
/*Data[C_Comm_Data_MaxLen]�е�ƫ��*/
#define	CDI_O_V_645					C_DI_OFS			/*V_645Frame��DIƫ��*/
#define	CPW_SpecialO_V_645			0					/*������������ƫ��*/
#define	CBoardCastData_O_V_645		0					/*�㲥Уʱʱ����ƫ��*/
#define	CFreezeParm_O_V_645			0					/*������������ƫ��*/
#define	C17SetBpsData_O_V_645		0					/*17��������bpsʱ������ʼƫ��*/
#define	C1DData_O_V_645				0					/* 1D�������ö๦�����ʱ������ʼƫ��*/

#define	COpCode_OtherO_V_645		4					/*03������������OPcode*/
#define	CData_OtherO_V_645			8					/*03������������data��ʼ��ƫ��*/
#define	CMaxRMNLen_OtherV_645		(C_Comm_Data_MaxLen - 8)

#define	CPW_14OV_645				C_PW_OFS_14			/*14����������*/
#define	COpcode_14O_V_645			C_OPCode_OFS_14		/*14������OpCode*/
#define	CData_14O_V_645				C_Data_OFS_14		/*14���������ݿ�ʼƫ��*/
#define	CMaxRMNLen_14V_645			(C_Comm_Data_MaxLen - 12)

#define	C_O_EventClear_DI			8

#define	C_11_SData					4
#define	C_O_FrameNo					4

#define	C_O_SF_Data					4					/*����ģʽ����ʱ�����ݿ�ʼƫ�Ƶ�ַ*/

#define	C_O_PW_Cal					2					/*У��ʱ�����뿪ʼƫ��*/
#define	C_O_Data_Cal				6					/*У��ʱ��ʵ��У�����ݿ�ʼƫ��*/
#define	C_DILen_Cal					2					/*У������ݿ�ʼƫ��*/
/*���������ȥ�����롢����������Ч���ݿ�ʼƫ�ƶ���*/
#define	C_R1_O						0
#define	C_R2_O						1
#define	C_R3_O						2
#define	C_R9_O						8
/*֡��ʽ3��ƫ��*/
#define	C_F3_O_BlockNum				4
#define	C_F3_O_GivenClock			5
/*���ɼ�¼��ض���*/
#define C_DataAANum					6

/************�ж�������¼��ı����ṹ��*********/
typedef struct
{
	ulong32	ProgramDI;          	/*�¼���¼д�ı�ʶ��*/
	ulong32	GetDataDI_First;		/*��ȡ���ݵĵ� 1����ʶ��*/
	ulong32	GetDataDI_End;			/*��ȡ���ݵ����һ����ʶ��*/
}Str_ProgTable;

/***********���������Ŀ�Ϸ����жϽṹ��*********/
typedef struct
{
	ulong32	ParmDI;					/*������ʶ��*/
	ulong32	Method;					/*��������ע1*/
}Str_WrParmTable;
/*ע1: ����ϸ����ĵ�<������Ч�Լ���������>*/
/*Method������Bit31-Bit28*/
#define		C_HaveIPEventType				0xF0000000		/*ȡֵ����*/
/*��Ϊ���ֶ�ֻ��16��ȡֵ��Χ�����6��12�վ�����������¼��ϲ�һ��������*/
/*�ڸ÷������жϱ�ʶ�룬Ȼ����в�ͬ��Ϣ������*/
#define		C_HaveIPEvent_Invalid			0x00000000
#define		C_HaveIPEvent_ProgParm			0x10000000		/*�ж�������¼�*/
#define		C_HaveIPEvent_ReturnMoney		0x20000000		/*�˷��¼���¼*/
#define		C_HaveIPEvent_RstReportState	0x30000000		/*��λ�����ϱ�״̬��,*/
															/*����˵��λ�����ϱ�״̬���б���¼���������Ҫ���⴦������д���ݲ�*/
#define		C_HaveIPEvent_GPRSSignal		0x40000000
/*Method������Bit28-Bit24*/
#define		C_ExtMsgType					0x0F000000		/*ȡֵ����*/
#define		C_ExtMsgType_Invalid			0x00000000		/*�޶���Ϣ����*/
#define		C_ExtMsg_ReWorkTime				0x01000000		/*ʱ�Ӹ�����Ϣ����,�赥����д����*/
#define		C_ExtMsg_ReSettle_Day1			0x02000000		/*��1�����ո��ģ���Ҫ�ж��޸�ǰ��������Ƿ���ͬ����ͬ�򲻷���Ϣ����ͬ����Ϣ������ģ��*/
#define		C_ExtMsg_SetKeyNum				0x03000000		/*������Կ��������Ϣ��������Կ���*/

#define		C_ExtMsg_ReLocalWarningPara 	0x0D000000		/*���ñ��ر�����ز���*/
#define		C_ExtMsg_ReMultiRatesParm		0x0E000000		/*ʱ�η�����������ģ�Other����ͳһ����*/
#define		C_ExtMsg_ReDemand_Cycle			0x0F000000		/*�������ڸ���,Other����ͳһ����*/
/*Method������Bit23-Bit16  */
#define		C_ExtMsgDA_StartBit				0x00010000		/*��ʼλ*/
#define		C_ExtMsgDA_MaxNum				8				/*�����8����Ϣ��ַ���Է���*/
#define		C_ExtMsgDestAddress				0x00FF0000		/*ȡֵ����*/
#define		C_ExtMsgDA_Demand				0x00010000		/*Bit16:������Ϣ*/
#define		C_ExtMsgDA_MultiRates			0x00020000		/*Bit17:����ʱ���ж���Ϣ*/
#define		C_ExtMsgDA_Settle				0x00040000		/*Bit18:����ģ��*/
#define		C_ExtMsgDA_EnergyMetering		0x00080000		/*Bit19:����ģ��*/
/*Method������Bit15-Bit13*/
#define		C_DataValidMethodType			0x0000E000		/*ȡֵ����*/
#define		C_DataValid_NoLimit				0x00002000		/*ͨ�÷���1���������ơ�Bit12-Bit8ֵ��Ч*/
#define		C_DataValidBCD_Range			0x00004000		/*ͨ�÷���2��BCD����ΧAA-BB��Bit12-Bit8��BCD��Χ����1-32��*/
#define		C_DataValidOnlyBCD				0x00006000		/*ͨ�÷���3��BCD��������Χ���ơ�Bit12-Bit8ֵ��Ч*/
#define		C_DataValidHex_Range			0x00008000		/*ͨ�÷���4��HEX����ΧAA-BB��Bit12-Bit8��HEX��Χ����1-32��*/
#define		C_DataValidSpecialMethod		0x0000E000		/*���ⷽ������Ҫ����ר�ú��������жϣ�Bit12-Bit8�����ⷽ�����*/
/*Method������Bit12-Bit8*/
#define		C_DataValidMethod				0x00001F00		/*ȡֵ����*/
/*������ⷽ�� C_DataValidSpecialMethod*/
#define		C_DV_Date_Time					0x00000100		/*���ⷽ��֮����ʱ���ж�*/
#define		C_DV_Demand_Cycle				0x00000200		/*���ⷽ��֮��������*/
#define		C_DV_Sliding_Time				0x00000300		/*���ⷽ��֮��������*/
#define		C_DV_SwitchingTime				0x00000400		/*���ⷽ��֮�л�ʱ��(������ʱ��)�ж�*/
#define		C_DV_Comm_Address				0x00000500		/*���ⷽ��֮���ַ(BCD,����ȫ0x99)*/
#define		C_DV_Bps						0x00000600		/*���ⷽ��֮�����ʵ�����*/
#define		C_DV_Hour_Freeze				0x00000700		/*���ⷽ��֮���㶳��ģʽ�ֵ��ж�*/
#define		C_DV_HF_InteTime				0x00000800		/*���ⷽ��֮���㶳����ʱ���ж�*/
#define		C_DV_Settle_Day					0x00000900		/*���ⷽ��֮��������Ч��*/
#define		C_DV_Return_Money				0x00000A00		/*���ⷽ��֮�˷ѽ�������Ҫ�жϹ������ˣ��������ش���*/
#define		C_DV_DayFreezeClock				0x00000B00		/*���ⷽ��֮�ն���ʱ���ж�*/
#define		C_DV_Season						0x00000C00		/*���ⷽ��֮ʱ���жϷ���*/
#define		C_DV_TimePeriod					0x00000D00		/*���ⷽ��֮ʱ���жϷ���*/
#define		C_DV_Ladder						0x00000E00		/*���ⷽ��֮���ݱ��жϷ���*/
#define		C_DV_DiplayItemSet				0x00000F00		/*���ⷽ��֮��ʾ��Ŀ����(���ԡ�����)*/
#define		C_DV_HolidaySet					0x00001000		/*���ⷽ��֮������������*/
#define		C_DV_RstReport_State			0x00001100		/*���ⷽ��֮�����ϱ�״���ֵĸ�λ*/
#define		C_DV_Eventpara					0x00001200		/*���ⷽ��֮�¼��жϲ���*/
#define		C_DV_Position					0x00001300		/*���ⷽ��֮���ܱ�λ����Ϣ*/
#define		C_DV_Date_Time_645				0x00001400		/*���ⷽ��֮����ʱ��,645��0x04000101/0x04000102�ж�*/
#define		C_DV_ReportChannel				0x00001500		/*���ⷽ��֮�ϱ�ͨ���ж�*/
/*���ͨ�÷���4  C_DataValidHex_Range*/
#define		C_DV_HexRange_1_14				0x00000100		/*Hex��Χ:1-14*/
#define		C_DV_HexRange_1_8				0x00000200		/*Hex��Χ:1-8*/
#define		C_DV_HexRange_Rates				0x00000300		/*Hex��Χ:1-12 �������жϷ���*/
#define		C_DV_HexRange_0_20				0x00000400		/*Hex��Χ:0-20*/
#define		C_DV_HexRange_0_6				0x00000500		/*Hex��Χ:0-6*/
#define		C_DV_HexRange_1_99				0x00000600		/*Hex��Χ:1-99*/
#define		C_DV_HexRange_5_20				0x00000700		/*Hex��Χ:5-20*/
#define		C_DV_HexRange_0_4				0x00000800		/*Hex��Χ:0-4*/
#define		C_DV_HexRange_5_30				0x00000900		/*Hex��Χ:5-30*/
#define		C_DV_HexRange_0_60				0x00000A00		/*Hex��Χ:0-60*/
#define		C_DV_HexRange_0_1				0x00000B00		/*Hex��Χ:0-1*/
#define		C_DV_HexRange_0_3				0x00000C00		/*Hex��Χ:0-3*/
#define		C_DV_HexRange_1_32				0x00000D00		/*Hex��Χ:1-32*/

/*Method������Bit7-Bit0*/
#define		C_IsAddFixedDataLen				0x00000080		/*ȡֵ����*/
#define		C_AddFixedDataLen				0x00000080		/*october��visiblestring��bitstring��ʽ���ݲ���̶�����0x00*/
#define		C_UnAddFixedDataLen				0x00000000		/*���ð��̶����Ȳ���0x00*/

#define		C_DataLenFixedFlag				0x00000040		/*ȡֵ����*/
#define		C_DataLenFixed_OK				0x00000040		/*���ݳ��ȹ̶����̶�ʱ���ȱ���С��63��������Ϊ���̶�*/
#define		C_DataLenUnsized				0x00000000		/*���ݳ��Ȳ��̶�*/

#define		C_DataLenFixed					0x0000003F		/*ȡֵ����*/
#define		C_UnsizedLen_Method				0x0000003F		/*ȡֵ����*/
#define		C_UnsizedLen_LSTime				0x00000001		/*�������жϷ���-���ɼ�¼��ʼʱ��*/
#define		C_UnsizedLen_PW			    	0x00000002		/*���룬��Ҫ�����ȸĳ�03����*/
#define		C_UnsizedLen_S_PT				0x00000003		/*ʱ����ʱ�α����жϷ���*/
#define		C_UnsizedLen_Date				0x00000004		/*�������ã��жϳ����Ƿ���ȷ�����������Ϊ0400010C��ʽ*/
#define		C_UnsizedLen_Time				0x00000005		/*ʱ�����ã��жϳ����Ƿ���ȷ�����������Ϊ0400010C��ʽ*/
#define		C_UnsizedLen_BackUpLadder		0x00000006		/*���ñ����׽��ݱ���������ȴ���63�ֽڣ���Ҫ���⴦��*/
#define		C_UnsizedLen_BackUpRateFFPrice	0x00000007		/*���ñ����׷��ʵ�����ݿ����������Ӧ��С��132�ֽڣ����ܱ�4����*/
#define		C_UnsizedLen_ReportChannel		0x00000008	    /*�ϱ�ͨ�����ȣ�����13�ֽڸ�λ��0*/
/*698����645����*/
#define 	C_NeedChangeTo698 				0x55
#define 	C_Normal645 					0x00
#define 	C_ASCII_A   					0x41   			/*A��Ӧ��ASCII��0x41*/
#define 	C_ASCII_0   					0x30   			/*0��Ӧ��ASCII��0x30*/
#define 	C_ASCII_9   					0x39   			/*9��Ӧ��ASCII��0x39*/

#define 	C_2015CLEAR 					0x01 			/*/2015ȷ���ϱ�*/
#define 	C_EventCLEAR 					0x02 			/*/2015ȷ���ϱ�*/

#define 	C_ProgramEventClearDI  			0x033000FF

#define 	C_BCDMax_OneBit  				0x63   			/*1�ֽ�BCD���99�������ж�HexתBCD���Ƿ�����1�ֽ�*/
#define 	C_BCDMax         				0x99   			/*1�ֽ�BCD���0x99*/
#define 	C_BCDMax_TwoBit  				0x270F 			/*2�ֽ�BCD���9999�������ж�HexתBCD���Ƿ�����2�ֽ�*/

typedef struct
{
	uchar8	DI2;        		/*645DI2*/
	uchar8  OIB;				/*698OIB */
}Str_DI2ToOIB;


typedef struct
{
	uchar8	BitN0;        		/*bitλ*/
	uchar8  EventN0;			/*�¼���*/
}Str_ReportEventNo;

/*698�����ϱ�״̬��*/
#define C_Report_Bit0	 		0        	/*���ɿ�������*/
#define C_Report_Bit3    		3		  	/*ʱ�ӵ�ص�ѹ��*/
#define C_Report_Bit7    		7		  	/*ʱ�ӹ���*/
#define C_Report_Bit8    		8		  	/*ͣ�糭����Ƿѹ*/
#define C_Report_Bit10   		10			/*����*/
#define C_Report_Bit11   		11		  	/*����ť��*/
#define C_Report_Bit12   		12         	/*�㶨�ų����� */
#define C_Report_Bit13   		13         	/*��Դ�쳣 */
#define C_Report_Bit14   		14         	/*��բ  */
#define C_Report_Bit15   		15         	/*��բ  */
#define C_Report_Bit16   		16         	/*A��ʧѹ */
#define C_Report_Bit17   		17       	/*A��Ƿѹ*/
#define C_Report_Bit18   		18       	/*A���ѹ */
#define C_Report_Bit19   		19         	/*A��ʧ�� */
#define C_Report_Bit20   		20         	/*A����� */
#define C_Report_Bit21   		22       	/*A�๦�ʷ���*/
#define C_Report_Bit22   		23       	/*A�����*/
#define C_Report_Bit32   		32         	/*B��ʧѹ */
#define C_Report_Bit33   		33       	/*B��Ƿѹ*/
#define C_Report_Bit34   		34       	/*B���ѹ */
#define C_Report_Bit35   		35         	/*B��ʧ�� */
#define C_Report_Bit36   		36         	/*B�����*/
#define C_Report_Bit38   		38       	/*B�๦�ʷ���*/
#define C_Report_Bit39   		39       	/*B����� */
#define C_Report_Bit48   		48         	/*C��ʧѹ*/
#define C_Report_Bit49   		49         	/*C��Ƿѹ*/
#define C_Report_Bit50   		50         	/*C���ѹ */
#define C_Report_Bit51   		51         	/*C��ʧ�� */
#define C_Report_Bit52   		52         	/*C����� */
#define C_Report_Bit54   		54         	/*C�๦�ʷ��� */
#define C_Report_Bit55   		55         	/*C�����*/
#define C_Report_Bit64   		64         	/*��ѹ������*/
#define C_Report_Bit66   		66         	/*��ѹ��ƽ��*/
#define C_Report_Bit69   		69         	/*���� */
#define C_Report_Bit73   		73         	/*˫Э���е����й����ʷ���*/
#define C_Report_Bit74   		74         	/*ȫʧѹ*/
#define C_Report_Bit80   		80         	/*��� */
#define C_Report_Bit81   		81         	/*�������*/
#define C_Report_Bit82   		82         	/*��������*/
#define C_Report_Bit83   		83         	/*�¼����� */
#define C_Report_Bit84   		84          /*Уʱ */

#define C_MeterStatus_Bit0   	0
#define C_MeterStatus_Bit1   	1

#define C_WordLen   			8
#define C_ReportStateJudge   	1  							/*���������ϱ�״̬����λ�ж���*/
extern const Str_ReportEventNo 	TB_ReportEventNo[CReport_645_Judge_Num];

/*********************�����ϱ���ر����ͺ궨��***************************************/
#define	C_ReportStateNum		96
#define	C_ReportStateByteNum	12
static	uchar8	SV_ReportNewAddNum[C_ReportStateNum + 2];	/*96�ֽ������ϱ�����*/
typedef struct
{
	uchar8		State[C_ReportStateByteNum];				/*12�ֽ����ϱ��ֽ��������ϱ�Ϊ1*/
	ushort16	Timer;										/*�����ϱ�״̬���Զ���λ��ʱʱ��  ����500ms  ���ʱ�䣬������磬�򲻰�������ʱ��*/
	ushort16 	CRC16;
}Str_HaveReport;
static	Str_HaveReport	SV_HaveReportState;

typedef struct
{
    uchar8 		ReportMode645_Bit;							/*645�����ϱ�ģʽ��bit*/
    uchar8 		OIB;										/*698���¼���OIB*/
    uchar8 		Nature;										/*698���ϱ���ʶ��Ӧ������*/
    uchar8 		Report698_2015_Bit;							/*698��2015�е�bit(����2015��ΪNULL)*/
}Str_DriveReport_Change;
extern const Str_DriveReport_Change Pstr_DriveReport_Change[];

/*645�����ϱ�ģʽ��*/
#define		C_ReportMode645_Bit0        0					/*���ɿ���������   */
#define		C_ReportMode645_Bit1        1           		/*ESAM����         */
#define		C_ReportMode645_Bit2        2           		/*�ڿ���ʼ������  */
#define		C_ReportMode645_Bit3        3           		/*ʱ�ӵ�ص�ѹ��*/
#define		C_ReportMode645_Bit4        4           		/*�ڲ��������   */
#define		C_ReportMode645_Bit5        5           		/*�洢�����ϻ��� */
#define		C_ReportMode645_Bit6        6           		/*����    */
#define		C_ReportMode645_Bit7        7           		/*ʱ�ӹ��� */
#define		C_ReportMode645_Bit8        8           		/*ͣ�糭����Ƿѹ */
#define		C_ReportMode645_Bit9        9           		/*͸֧״̬  */
#define		C_ReportMode645_Bit10		10          		/*����� */
#define		C_ReportMode645_Bit11       11          		/*����ť�� */
#define		C_ReportMode645_Bit12       12          		/*�㶨�ų�����  */
#define		C_ReportMode645_Bit13       13          		/*��Դ�쳣 */
#define		C_ReportMode645_Bit14       14          		/*��բ�ɹ�*/
#define		C_ReportMode645_Bit15       15          		/*��բ�ɹ�*/
#define		C_ReportMode645_Bit16       16          		/*ʧѹ   */
#define		C_ReportMode645_Bit17       17          		/*Ƿѹ   */
#define		C_ReportMode645_Bit18       18          		/*��ѹ   */
#define		C_ReportMode645_Bit19       19          		/*ʧ��   */
#define		C_ReportMode645_Bit20       20          		/*����   */
#define		C_ReportMode645_Bit21       21          		/*����   */
#define		C_ReportMode645_Bit22       22          		/*���ʷ���*/
#define		C_ReportMode645_Bit23       23          		/*����*/
#define		C_ReportMode645_Bit24       24          		/*���� */
#define		C_ReportMode645_Bit25       25          		/*���� */
#define		C_ReportMode645_Bit26       26          		/*����*/
#define		C_ReportMode645_Bit27       27          		/*���� */
#define		C_ReportMode645_Bit28       28          		/*���� */
#define		C_ReportMode645_Bit29       29          		/*���� */
#define		C_ReportMode645_Bit30       30          		/*���� */
#define		C_ReportMode645_Bit31       31          		/*��ѹ������*/
#define		C_ReportMode645_Bit32       32          		/*����������*/
#define		C_ReportMode645_Bit33       33          		/*��ѹ��ƽ��*/
#define		C_ReportMode645_Bit34       34          		/*������ƽ��*/
#define		C_ReportMode645_Bit35       35          		/*������Դʧ��*/
#define		C_ReportMode645_Bit36       36          		/*���� */
#define		C_ReportMode645_Bit37       37          		/*��������  698��Ϊ����3009������300A���޹�30 */
#define		C_ReportMode645_Bit38       38          		/*�ܹ������������� */
#define		C_ReportMode645_Bit39       39          		/*�������ز�ƽ�� */
#define		C_ReportMode645_Bit40       40          		/*�������� 698�����������ڹ��ʷ�����  */
#define		C_ReportMode645_Bit41       41          		/*ȫʧѹ*/
#define		C_ReportMode645_Bit42       42          		/*����*/
#define		C_ReportMode645_Bit43       43          		/*���� */
#define		C_ReportMode645_Bit44       44          		/*���� */
#define		C_ReportMode645_Bit45       45          		/*����  */
#define		C_ReportMode645_Bit46       46          		/*���� */
#define		C_ReportMode645_Bit47       47          		/*���� */
#define		C_ReportMode645_Bit48       48          		/*��� */
#define		C_ReportMode645_Bit49       49          		/*�������*/
#define		C_ReportMode645_Bit50       50          		/*��������*/
#define		C_ReportMode645_Bit51       51          		/*�¼�����*/
#define		C_ReportMode645_Bit52       52          		/*Уʱ  */
#define		C_ReportMode645_Bit53       53          		/*ʱ�α��� */
#define		C_ReportMode645_Bit54       54          		/*ʱ������*/
#define		C_ReportMode645_Bit55       55          		/*�����ձ��*/
#define		C_ReportMode645_Bit56       56          		/*�ڼ��ձ�� */
#define		C_ReportMode645_Bit57       57          		/*�й���Ϸ�ʽ��� */
#define		C_ReportMode645_Bit58       58          		/*�޹���Ϸ�ʽ1��� 698ֻ���޹���Ϸ�ʽ���*/
#define		C_ReportMode645_Bit59       59          		/*�޹���Ϸ�ʽ2���*/
#define		C_ReportMode645_Bit60       60          		/*�����ձ�� */
#define		C_ReportMode645_Bit61       61          		/*���ʲ�������*/
#define		C_ReportMode645_Bit62       62          		/*���ݱ���  */
#define		C_ReportMode645_Bit63       63          		/*��Կ����  */

/*698�����ϱ�ģʽ��2015 */
#define		C_Report698_2015_Bit1      	1   				/*ESAM����*/
#define		C_Report698_2015_Bit3      	3 					/*ʱ�ӵ�ص�ѹ��*/
#define		C_Report698_2015_Bit5      	5 					/*�洢�����ϻ���*/
#define		C_Report698_2015_Bit8      	8 					/*ͣ�糭����Ƿѹ*/
#define		C_Report698_2015_Bit9      	9 					/*͸֧״̬*/
#define		C_Report698_2015_Bit14     	14					/*��բ�ɹ�*/
#define		C_Report698_2015_Bit15     	15					/*��բ�ɹ�*/
#define		C_Report698_2015_Bit30     	30					/*���ü̵��������ź� ��*/
#define		C_Report698_2015_Bit31     	31					/*���ü̵��������ź� ͨ*/

#define 	CL_OI2Len 					0x01  				/*OI2����*/

#define 	C_SeverseToClient			0x89
#define 	C_ClientToSeverse			0x98

typedef  struct
{
	ulong32 ChannelOAD;
}Str_ChannelOAD;

/********************* ����Ϊ�ڲ�����ԭ�� ************************************************/
/*ͨ���ڲ���ȡ��Ϣ��־*/
void		Comm_AppendMsg(ulong32	MsgNum);
ulong32		Comm_FetchMsg(void);
/*ͨ�Ž������������*/
Str_Comm_Parm	* Get_Str_Comm_Parm_Pointer(uchar8 CommNo);
void		Comm_WR_TxData_ToCtrbyte(Str_Comm_Parm *pStr_Comm_Parm_Address, uchar8 Rx_CtrByte);
void		Comm_Response_Set_ReadErr(uchar8  Err, Str_Comm_645 *pV_645Frame);
void		Comm_Response_03_Err(ushort16  SERR, Str_Comm_645 *pV_645Frame);
void		Comm_11_03Response_Normal(Str_Comm_645 *pV_645Frame, uchar8	*pData,uchar8 DataLen);
void		Comm_Response_FromP_Normal(Str_Comm_645 * pV_645Frame, uchar8	*pData,uchar8 DataLen);
void		Comm_IfHaveNxtFrame_Set_C(Str_Comm_645 * pV_645Frame);
void		Comm_SetFrameNo(uchar8	CommNo, uchar8	FrameNo);
void		CommMSg_StartTxd(uchar8 	CommNo);

/*��������10min��ʱ��*/
uchar8		TimerExceed10min_Dec(Str_TimerExceed10min *pTimerExceed10min);
uchar8		JudgeTimerExceed10min(Str_TimerExceed10min *pTimerExceed10min);
uchar8		SetTimerExceed10min(Str_TimerExceed10min *pTimerExceed10min,uchar8 *pVMinTimer);
void		DealWith_ID_Auth_Timer(uchar8 Method,uchar8 *pVTimer);
void		DealWith_IR_Auth_Timer(uchar8 Method,uchar8 *pVTimer);
void		DealWith_IR_Auth_Timer_645(uchar8 Method,uchar8 *pVTimer);
void		DealWith_SI_J_Timer(uchar8	Method,uchar8	*pVTimer);
uchar8		Is_IR_Comm_ResponseErr_645(Str_Comm_645	*pV_645Frame);
void		DealWith_ProgKey_Timer(uchar8	Method,uchar8	*pVTimer);
void		ProgKey_Message(void);

/*����֡*/
void		Init_SV_CommNxtFrame (uchar8	CommNo);
void		Set_SV_CommNxtFrame (uchar8 CommNo,Str_Comm_NxtFrame *pNxtFrame);
uchar8		Get_SV_CommNxtFrame (uchar8 CommNo, Str_Comm_NxtFrame *pNxtFrame);

/*�͵��ȴ򽻵��ķ�����Ϣ*/
void		Comm_SendMsg(uchar8 *pParm,uchar8 ParmLen,uchar8 DestMsg);
void		Comm_SendMsgToDisp(uchar8 DispSign,uchar8	DispMode,ushort16 Duration);
void		LightenCommSign(uchar8	CommNo,uchar8	PowerFlag);
void		Comm_A_MsgToDispatchQueue_UpKeyR(uchar8 PT_Type);
void		Comm_SendMsgForUpdataParm(uchar8	ParmType,uchar8	DestMsg);

/*��Կ����*/
uchar8		Get_AllTemporaryKeyState(void);
void		Init_AllTemporaryKeyState(void);
void		Comm_UpdataKey_Review(uchar8	PT_Type);
/*���*/
void		Have_IPEvent_Prog(Str_ProgTable *pProgTable,uchar8 TabLineNum,Str_Comm_645 *pV_645Frame);
void		Have_IPEvent_MeterClear(Str_Comm_645 *pV_645Frame );
void		Have_IPEvent_DemandClear(Str_Comm_645 *pV_645Frame);
void		Have_IPEvent_EventClear(Str_Comm_645 *pV_645Frame,ulong32 V_ulOAD);
void		Have_IPEvent_ProgDateTime(Str_Comm_645 *pV_645Frame);
void		Have_IPEvent_ProgRate(Str_Comm_645 *pV_645Frame);
/*�����ϱ���غ���*/
uchar8		Is_EnableReport(uchar8	V_ucBitNum);
uchar8		J_ReportNAN_Null_IfErrSetZero(void);
uchar8		Judge_ReportWithNxtFrame(void);
void		Init_SV_ReportNewAddNum(void);
void		Rst_SV_ReportNewAddNum(uchar8	*pRstState);
void		Init_SV_HaveReportState(void);
void		Set_SV_HaveReportState(uchar8	*pHaveReportState);
void		Set_ReportStateFrame(uchar8	*pReportStateFrame,uchar8	*pReportLen);
void 		Write_SV_ReportNewAddNum(uchar8 *ReportNewAddNum);
void 		Write_SV_HaveReportState(uchar8 *HaveReportState);
void		DealWithEventReportIO(void);
/*����*/
void 		Comm_ParseInit(void);
void		Comm_Parse(uchar8 CommNo,uchar8	PowerFlag);

uchar8		Cal_645CS(uchar8	*pStartByte,uchar8 BygteLen);
uchar8		Cal_645CS_CommRec(uchar8	*pStartByte,uchar8 BygteLen);
uchar8		GetCommMeterAddressType(uchar8	*pCommMAdrress);
uchar8		IfFrameOkSetV_645Frame(Str_Comm_645 *pV_645Frame,Str_Comm_Parm 	*pStr_Comm_Parm_Address);
uchar8		Is_IR_Comm_ResponseErr(Str_Comm_645	*pV_645Frame);
uchar8		If_AddressFlagOK_ResponseErr(Str_Comm_645 *pV_645Frame);
uchar8		Is_ID_Auth_Ok_ResponseErr(Str_Comm_645	*pV_645Frame);
uchar8		Is_SPT_NotOver_ResponseErr(Str_Comm_645	*pV_645Frame);
uchar8		Is_PW_OK(uchar8	*pCommPW);
uchar8		IsMeterTypeSupport(Str_Comm_645 *pV_645Frame);

/*�����������*/
void		Comm_SetCommAddress(Str_Comm_645 *pV_645Frame);
void		Comm_CondenseAAReadMAddress(Str_Comm_645 *pV_645Frame);
void		Comm_MeterClear(Str_Comm_645 *pV_645Frame);
uchar8		Comm_98MeterClear(Str_Comm_645 *pV_645Frame);
uchar8		Comm_02MeterClear(Str_Comm_645 *pV_645Frame);
void		Comm_DemandClear(Str_Comm_645 *pV_645Frame);
uchar8		Comm_04DemandClear(Str_Comm_645 *pV_645Frame);
uchar8		Comm_98DemandClear(Str_Comm_645 *pV_645Frame);
void		Comm_EventClear(Str_Comm_645 *pV_645Frame);
uchar8		Comm_02EventClear(Str_Comm_645 *pV_645Frame);
uchar8		Comm_98EventClear(Str_Comm_645 *pV_645Frame);
void		Comm_SetPassword(Str_Comm_645 *pV_645Frame);
void		Comm_BroadcastSetClock(Str_Comm_645 *pV_645Frame);
void 		Clear_BDSC_RecentClock(void);
void		Comm_FreezingOrder_C16(Str_Comm_645 *pV_645Frame);
void		Comm_Set_BPSr_C17(Str_Comm_645 *pV_645Frame);
uchar8		Is_CommBPS_OK(uchar8	CommNo,uchar8 bps);
ulong32		Get_CommBpsDataCode(uchar8	CommNo);
void		Comm_MultFOut(Str_Comm_645 *pV_645Frame);
void		Comm_MeterCalibration(Str_Comm_645 *pV_645Frame);
void		Cal_SetPassword(Str_Comm_645 *pV_645Frame);
void		Cal_WriteCalStartClock(Str_Comm_645 *pV_645Frame);
uchar8		Write_OneCalRegToData(uchar8 CalRegInData_No,uchar8	*pCalReg);
void		Cal_ClearAllCalReg(Str_Comm_645 *pV_645Frame);
void		Comm_Cal_Read(Str_Comm_645 *pV_645Frame);
void		Comm_LoadSwitch_Control(Str_Comm_645 *pV_645Frame);
ushort16	Comm_98LoadSwitch_Control(Str_Comm_645 *pV_645Frame);
ushort16	Comm_02LoadSwitch_Control(Str_Comm_645 *pV_645Frame);
void		Comm_LoadS_Ctr_Reponse(uchar8 ReposneType,ushort16 V_usOrderExcuteStatus,
			uchar8	ReposneLen,Str_Comm_645 *pV_645Frame);
void		Comm_SetInFactoryState(Str_Comm_645 *pV_645Frame);
void		Comm_RecoverRamData(Str_Comm_645 *pV_645Frame);
void		In_Out_FactoryState(Str_Comm_645 *pV_645Frame);
void		Set_InFactoryState(Str_Comm_645 *pV_645Frame);
void		Act_InFactoryState(Str_Comm_645 *pV_645Frame);

/*14�������*/
void		Comm_14SetParm(Str_Comm_645 *pV_645Frame);
uchar8		Is_ParmType_3(ulong32	DI,Str_WrParmTable *pWrParmTable,uchar8 V_ucCommNum);
uchar8		Comm_14_04SetParm(Str_Comm_645 *pV_645Frame,Str_WrParmTable *pWrParmTable,uchar8 V_Flag);
uchar8		Comm_14_98SetParm(Str_Comm_645 *pV_645Frame,Str_WrParmTable *pWrParmTable,uchar8 V_Flag);
uchar8		Comm_14_99SetParm(Str_Comm_645 *pV_645Frame,Str_WrParmTable *pWrParmTable);
uchar8		Is_SetParmData_Ok(Str_Comm_645 *pV_645Frame,Str_WrParmTable *pWrParmTable);
uchar8		LookFor_WrParmTable(Str_Comm_645 *pV_645Frame,Str_WrParmTable *pWrParmTable);
uchar8		Is_14_DataLenOk(Str_Comm_645 *pV_645Frame,Str_WrParmTable *pWrParmTable);
uchar8		IsPW_Len_Auth(Str_Comm_645 *pV_645Frame);
uchar8		Adjust_UnsizedLen_S_PT(Str_Comm_645 *pV_645Frame);
uchar8		Adjust_BackUpRateFFPriceLen(Str_Comm_645 *pV_645Frame);
uchar8		Adjust_ReportChannel( Str_Comm_645 *pV_645Frame );
uchar8		Adjust_BackUpLadderLen(Str_Comm_645 *pV_645Frame);
uchar8		Adjust_DateLen(Str_Comm_645 *pV_645Frame);
uchar8		Adjust_TimeLen(Str_Comm_645 *pV_645Frame);
uchar8		Is_14_DataValid(Str_Comm_645 *pV_645Frame,Str_WrParmTable *pWrParmTable);
uchar8		DV_HexRange(Str_Comm_645 *pV_645Frame,uchar8	HexMin,uchar8 HexMax);
uchar8		DV_Date_Time(Str_Comm_645 *pV_645Frame);
uchar8		DV_Date_Time_645(Str_Comm_645 *pV_645Frame);
uchar8		DV_Demand_Cycle(Str_Comm_645 *pV_645Frame);
uchar8		DV_Sliding_Time(Str_Comm_645 *pV_645Frame);
uchar8		DV_SwitchingTime(Str_Comm_645 *pV_645Frame);
uchar8		DV_Comm_Address(uchar8 *pComm_Address);
uchar8		DV_Bps(Str_Comm_645 *pV_645Frame);
uchar8		DV_Settle_Day(Str_Comm_645 *pV_645Frame);
uchar8		DV_Return_Money(Str_Comm_645 *pV_645Frame);
uchar8		DV_Season(Str_Comm_645 *pV_645Frame);
uchar8		Is_TZone_Data_OK(uchar8	*pTZone_Data);
uchar8		DV_TimePeriod(Str_Comm_645 *pV_645Frame);
uchar8		Is_TimePeriod_Data_OK(uchar8	*pTimePeriod_Data);
uchar8		DV_Ladder(Str_Comm_645 *pV_645Frame);
uchar8		InF_DV_Ladder(uchar8	*pLadderData);
uchar8		Is_YSettle_OK(uchar8	*pYSettle);
uchar8		DV_HolidaySet(Str_Comm_645 *pV_645Frame);
uchar8		DV_RstReport_State(Str_Comm_645 *pV_645Frame);
uchar8		DV_ReportChannel(Str_Comm_645 *pV_645Frame);
void		SetParm_14_AppendMsg(uchar8 ParmType, ulong32 DestMsgAddressType);
void		SetRTC_AppendMsg(ulong32 DestMsgAddressType,Str_Comm_645 *pV_645Frame);
void		ReSettle_Day1_AppendMsg(ulong32 DestMsgAddressType,Str_Comm_645 *pV_645Frame);
void		SetGPRSSignal(uchar8 *V_GPRSSignal);
void 		SF_Comm_GPRSDisplay(void);
void		ReturnMoney(Str_Comm_645 *pV_645Frame);
void		HaveIPEvent(Str_Comm_645 *pV_645Frame);
/*11 12��������*/
void		Comm_11_Read(Str_Comm_645 *pV_645Frame);
void		Comm_ReadEnergyReg(Str_Comm_645 *pV_645Frame);
void		ReadEnergyReg_00ZZFF00(Str_Comm_645 *pV_645Frame);
void		ReadEnergyReg_00ZZZZFF(Str_Comm_645 *pV_645Frame);
uchar8		Is_EventReg_DI0FFOK(Str_Comm_645 *pV_645Frame);
void 		Comm_ReadDemandReg(Str_Comm_645 * pV_645Frame);
void		Comm_ReadDemandReg_01ZZFFZZ(Str_Comm_645 *pV_645Frame);
void		Comm_ReadDemandReg_01ZZZZFF(Str_Comm_645 *pV_645Frame);
void		Comm_ReadFreezeReg_11(Str_Comm_645 *pV_645Frame);
uchar8		IsFreezeDataEnableRead (ulong32 DataCode);
uchar8		ReadFreezeReg_NxtFrame (Str_Comm_NxtFrame *pSV_CommNxtFrame,Str_Comm_645 *pV_645Frame,uchar8 TB_NxtFrame_LineNo);
uchar8		ReadProgRecordReg_NxtFrame (Str_Comm_NxtFrame *pSV_CommNxtFrame,Str_Comm_645 *pV_645Frame,uchar8 TB_NxtFrame_LineNo);
uchar8		ReadCurrFFRecordReg_NxtFrame (Str_Comm_NxtFrame *pSV_CommNxtFrame,Str_Comm_645 *pV_645Frame,uchar8 TB_NxtFrame_LineNo);
void		NormalReadingLoadCurve_11(Str_Comm_645 *pV_645Frame);
void		SeqReadingLoadCurve_11(Str_Comm_645 *pV_645Frame);
void		Comm_ReadNxtFrameParse(Str_Comm_645 *pV_645Frame);
void		Comm_ReadNxtFrame(Str_Comm_645 *pV_645Frame,Str_Comm_NxtFrame	*pStr_Comm_NxtFrame);
uchar8		SeqReadingLoadCurve(Str_Comm_645 *pV_645Frame,Str_Comm_NxtFrame	*pStr_Comm_NxtFrame);
uchar8		NormalReadingLoadCurve(Str_Comm_645 *pV_645Frame,Str_Comm_NxtFrame	*pStr_Comm_NxtFrame);
uchar8		Is_NormalReadingLoadCurve(ulong32	DataCode);
uchar8		Is_SeqReadingLoadCurve(ulong32	DataCode);
uchar8		IsIn_TBCarryingSubDI_1(ulong32 DataCode,uchar8 *pTBCarryingSubDI_1_Line);
void		R_CarryingSubDIReg(Str_Comm_645 *pV_645Frame,Str_TBCarryingSubDI_1 *pCarryingSubDI);
void		Comm_Read_P_V_Reg(Str_Comm_645 *pV_645Frame);
void		Comm_Read_TZone_PTReg(Str_Comm_645 *pV_645Frame,ulong32	LimitDI);
void		Comm_Read_EventReg(Str_Comm_645 *pV_645Frame);
void		Read_EventRegWithNxtFrame(Str_Comm_645 *pV_645Frame);
uchar8		Is_Pre1_RFF_VoltageEvent(ulong32	DataCode);
void		RD_Pre1_FF_VoltageEvent(Str_Comm_645 *pV_645Frame);
void		RD_Pre1_FF_NoBalEvent(Str_Comm_645 *pV_645Frame);
void		RD_ProgRecordReg(Str_Comm_645 *pV_645Frame);
void		Comm_LCD_View(Str_Comm_645 *pV_645Frame);
/*03�������*/
void		Comm_SecurityParse(Str_Comm_645 *pV_645Frame);
void		Comm_Authentication(Str_Comm_645	*pV_645Frame);
void		Comm_Certification_Invaliad(Str_Comm_645	*pV_645Frame);
void		Comm_IRCertification_Request(Str_Comm_645	*pV_645Frame);
void		Comm_IRCertification_Instruction(Str_Comm_645	*pV_645Frame);
void		Comm_WriteCertificationTime(Str_Comm_645	*pV_645Frame);
void		Comm_Key_V_Mac(Str_Comm_645	*pV_645Frame);
void		Comm_WriteESAMPara_PlainTextMAC(Str_Comm_645	*pV_645Frame);
void		Comm_WriteESAMPara_CipherTextMAC(Str_Comm_645	*pV_645Frame);
void		Comm_DataExcerption(Str_Comm_645	*pV_645Frame);
void		Comm_S_GetStatus(Str_Comm_645	*pV_645Frame);
void		Comm_Init_Money(Str_Comm_645	*pV_645Frame);
void		Comm_OpenChgBL(Str_Comm_645	*pV_645Frame);
/*��ʱ��Ϣ����*/
void		Comm_500ms_Execute(uchar8		PowerFlag);
/*����*/
ushort16	GetAutoDispCycleTime(void);
void		DealWith_RstModule(uchar8	IsPowerOnFlag);

extern void  OneDataReversed(uchar8 *pSBuf, uchar8 *pDBuf,uchar8 Len);
extern void OneByteReverse(uchar8 *pV_Sourcedata);

/*�ܵı�̼�¼���*/
void		INF_Init_Str_ProgRecord (Str_ProgRecord		*pProgRecord);
uchar8	Get_ProgRecord1InRam(uchar8	*pProgRecordInRam,Str_ProgRecord *pProgRecord);

uchar8 SF_GetAPDU_EventRead_645(Str_Comm_645 *pV_645Frame,uchar8 *P_DataBuf,ushort16 *P_DataLength);

void	SF_Clear645_ReportNewAddNum(uchar8 V_ucEventNo,uchar8 V_ucFlag);

/***********698����645����*****************************************************/
#define C_DataOffset_Time 			4   			/*698�¼������¼���¼���¼�����ʱ��ƫ��*/
#define C_DataOffset_OAD  			19  			/*698�¼������¼���¼���¼����ݱ�ʶƫ��*/
#define C_EventClr_Len  			( 6 + 4 + 4 ) 	/*645�¼������¼���ȣ�6����ʱ�� 4�����ߴ��� 4���ݱ�ʶ��*/
#define C_EventClr_Offset  			10  			/*645�����ϱ�״̬���еĵ������bit81����ƫ��*/
#define C_NoChangeEvent 			0xFF   			/*645��698�����ת���ı�־Pstr_DriveReport_Change*/

#define	C_O_CPUNum					0				/*CPU���ƫ��*/
#define	C_O_EncryptKeyNum			1				/*��Կ����ƫ��*/
#define	C_O_FactorAddress			2				/*��ɢ���ӵ�ַƫ��*/
#define	C_O_DataAddress				6				/*��������ƫ��*/
#define	C_CPUNum					0				/*CPU���*/
#define	C_SafeSpace_StartAddr		0				/*��������ʼ��ַ*/
#define	C_SafeSpace_EndAddr			0				/*������������ַ*/
#define	C_MinCodeSpace				0x00000000		/*��С�����ַ*/
#define	C_MaxCodeSpace				0x0007ffff		/*�������ַ*/
#define	C_L_FactorLen				0x10			/*��ɢ���ӳ���*/
#define	C_L_FactorData				0x8				/*��ɢ���ӷֶ�ƫ��*/
#define	C_L_PlainDataLen			0x100			/*���������ݳ���*/
#define	C_L_CipherData				0x40			/*�������ݳ���*/
#define	C_L_PlainDataLen_698		0x400			/*���������ݳ���*/

#define	C_L_RandLen				    0x40			/*���������*/
#define	C_L_RandData				0x10			/*�����������ݳ���*/

#define C_Buf_MaxLen 				2000

void Comm_SoftwareCampare(Str_Comm_645	*pV_645Frame);
void Comm_Parse_698(uchar8 CommNo, uchar8	PowerFlag);
uchar8 InF_ConectTimer_Deal(void);
uchar8 InF_Judge_EventOAD_OP(ulong32 V_OAD, uchar8 *pEventLineNO);

#define	C_TB_ProgTimePeriod_Len 	0x04
extern	const	Str_ProgTable		TB_ProgTimePeriod[C_TB_ProgTimePeriod_Len];

#define	C_TB_ProgSeason_Len			0x01
extern	const	Str_ProgTable 		TB_ProgSeason[C_TB_ProgSeason_Len];
/*������*/
#define	C_TB_ProgWeekRest_Len		0x01
extern	const	Str_ProgTable		TB_ProgWeekRest[C_TB_ProgWeekRest_Len];
/*������1-3����ͬһ�����*/
#define	C_TB_ProgSetADate_Len		0x01
extern	const	Str_ProgTable		TB_ProgSetADate[C_TB_ProgSetADate_Len];

/*�й����״̬��*/
#define	C_TB_ProgCombState_P_Len	0x01
extern	const	Str_ProgTable		TB_ProgCombState_P[C_TB_ProgCombState_P_Len];
/*�޹����״̬��1*/
#define	C_TB_ProgCombState_Q1_Len	0x01
extern	const	Str_ProgTable		TB_ProgCombState_Q1[C_TB_ProgCombState_Q1_Len];
/*�޹����״̬��2*/
#define	C_TB_ProgCombState_Q2_Len	0x01
extern	const	Str_ProgTable		TB_ProgCombState_Q2[C_TB_ProgCombState_Q2_Len];
/*�޹����״̬��698*/
#define	C_TB_ProgCombState_Q698_Len	0x01
extern const	Str_ProgTable		TB_ProgCombState_Q698[C_TB_ProgCombState_Q698_Len];
/*���ݱ��̼�¼*/
#define	C_TB_StepTariffEvent_Len	1
extern	const	Str_ProgTable		TB_StepTariffEvent[C_TB_StepTariffEvent_Len];

extern void InF_JudgeESAMConTimer(uchar8 V_Flag,uchar8 ClientAddr);
extern uchar8 InF_JudgeConectTimer(void);
extern uchar8 InF_GEsamTimer_Deal(void);
uchar8 DV_Eventpara(Str_Comm_645 *pV_645Frame);
extern void	Have_IPEvent_Prog_698(ulong32 V_ulProgOAD,ulong32 V_ulProgTimesOAD,Str_Comm_645 *pV_645Frame);
extern uchar8 SF_GetProgFixedData_698(ulong32 V_ulProgTimesOAD,uchar8 *P_Data);
uchar8 DV_Position(Str_Comm_645 *pV_645Frame);
void   ReturnMoney_698();
extern uchar8 InF_ConectTimer_DealNoTimer(void);
uchar8 InF_RD_ProgRecordReg(ulong32 V_ulDI,uchar8 *P_Buffer);

#define C_ResetDealConectTime		0x86	/*����Ӧ������ʱ��*/
#define C_ReworkDealConectTime		0x68	/*ͬ��Ӧ������ʱ��*/
#define C_PowerUpDealConectTime		0x45	/*�ϵ紦��Ӧ������ʱ��*/
#define C_SynDealConectTime			0x0		/*��ʱˢ��Ӧ������ʱ��*/
/*����΢ʱ�ӵ�У*/
union B16_B08
{
	unsigned char B08[2];
};
union B16_B08_2						/*С�˴洢(51Ϊ���)*/
{
	unsigned short	B16;
	unsigned char	B08[2];
};

struct TEMPERATURE_FRM
{
	uchar8		Offset[8];				/*�¶ȵ���ϵ��8�ֽ�*/
	uchar8		RtcTMode;				/*RTC��������ģʽ��0x55:����ģʽ��0xAA���²���ֵģʽ����������ͨģʽ*/
	uchar8		krh;					/*����ϵ�������޵�ֵ*/
	uchar8		krl;
	union B16_B08 	Crc16;				/*CRCУ����*/
};
extern struct	TEMPERATURE_FRM		Tpara;


struct RTC_TRIMA_FRM
{
	ushort16	PTAT_Value[21];			/*�¶�ADC*/
	union B16_B08 	Crc16;				/*CRCУ����*/
};
struct RTC_TRIMV_FRM
{
	short16	Trim_Value[21];				/*����ֵ*/
	union B16_B08 	Crc16;				/*CRCУ����*/
};

struct RTC_TRIM_FRM
{
	struct RTC_TRIMA_FRM	TAdc;
	struct RTC_TRIMV_FRM	TVal;
	short16					TestTrim;
	uchar8					TempFlag;	/*������¶ȱ�־ 0=���£�1=���£�2=����*/
	float					CFixTrim;	/*����������*/
};

extern struct	RTC_TRIM_FRM	RTC_RT;
/*2020��׼�����ϱ�2005*/
#define C_ReportInit        0xFF
#define C_ReportInitTime    ( ( C_ShutRealTimeData / 200 + C_PowerFail_Judge_Time ) + 4 )   /*1s����һ��,����ʱ��Ϊ���ܱ��ܱ���ʱ��+�����ж�ʱ��+4���ϵ����10s*/
void Comm_SendMsgToComm(void);
void CommMSg_StartTxd_698(uchar8 CommNo);
extern void Card_DispDynamicSign(void);
extern ConectRequest_Type	Com_Conect;			/*ͨ��Ӧ�����ӽṹ��*/

extern uchar8 Inf_ReadEventCurrentData_Com645(ulong32 V_Data_Id,uchar8 *P_Data,uchar8 *P_Data_Length,uchar8 V_Flag);
uchar8 SF_Event_SingleRead(Str_Comm_645 *pV_645Frame,ulong32 *V_ulReadOADBuf,uchar8 V_Line,uchar8 *P_DataBuf,ushort16 *P_DataLength);
uchar8 SF_GetAPDU_EventRead_645_Pro(Str_Comm_645 *pV_645Frame,uchar8 *P_DataBuf,ushort16 *P_DataLength);
extern uchar8 SF_SetParm(Str_Comm_645 *pV_645Frame,ulong32 V_ulLastDI,ulong32 V_ulNextDI,uchar8 V_WriteEventFlag,ulong32 V_ulProgOAD,uchar8 OperationFlag);
extern uchar8 SF_JugeDemadFF(uchar8 *P_DemandData,uchar8 V_ucLen);
extern void DataReversed(ulong32 ReversedMethod,uchar8 *pData,uchar8 R_ItemNum);
uchar8 SF_GetFrozenData_SettleFreeze_645(Str_Comm_645 *pV_645Frame,uchar8 *V_ucResultData,ushort16 *V_ucResultDataLength);
extern uchar8 SF_GetMinFreezeCycle(ulong32 *p_datacode, uchar8 V_ucDatacodeBufLen, uchar8 *pDataPlan, ushort16 *pDataCycle);
extern void	SF_MeterClear(Str_Comm_645 *pV_645Frame);
extern uchar8 SF_EventClear(Str_Comm_645 *pV_645Frame,ulong32 V_ulOAD);
extern void SF_DemandClear(void);
extern uchar8 SF_Read_DemandEvent(ulong32 V_ulDI, uchar8 V_ucDI0,uchar8 *P_DataBuf,uchar8 *P_DataLength);
extern void SF_Event_Relay_JudgeAll00(ulong32 V_ulOAD,uchar8 *p_VFlag);
extern uchar8 SF_JudgeAllAA(uchar8 *P_DataBuf,uchar8 P_DataLen);
extern uchar8 SF_EventClear_698_Dou645(Str_Comm_645 *pV_645Frame,uchar8 V_ProgFlag);
extern uchar8	SF_Deal_Comm_98SetParm(Str_Comm_645 *pV_645Frame);
extern void	SF_Clear645_ReportNewAddNum_EventClear();
extern void Inf_CleanMeterStatus8_Relay(uchar8 EventNo);
extern uchar8	Get_ProgRecord1InRam_645(uchar8	*pProgRecordInRam,Str_ProgRecord_645 *pProgRecord_645);
extern void	INF_Append_ProgRecordDI_645 (uchar8 *pOpCode,uchar8 *pProgDI,Str_ProgRecord_645 *pProgRecord_645);
extern void	INF_Init_Str_ProgRecord_645 (Str_ProgRecord_645		*pProgRecord_645);
extern void  RD_ProgRecordReg_645(Str_Comm_645 *pV_645Frame);
extern uchar8 SF_ReadCurrEventFF_645(ulong32 DI,uchar8 *P_DataBuf,uchar8 *P_DataLength);
extern void SF_EnergyT0_645(uchar8 *pV_ucBuf, uchar8 *pV_ucBuf_Exchanged, ushort16 *pV_usLen, uchar8 V_ucPerLen, uchar8 V_ucOIB_698);
extern uchar8  SF_GetMinFreezeProNum(ulong32 V_Data_Id_OAD, uchar8 *pV_Cycle);

#endif

