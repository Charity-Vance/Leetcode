/*******************************************************************************
Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     Comm_698.h
Version:       V1
Author:        jiangzs
Date:          2016-8-21
Description:   ͨ�Ŵ��������ļ�
---------------------------------------------------------------------------------
History1:      ��1���޸�
����1. Date:   20210928
   	   Author: lzy
       Modification:������ͳһƽ̨
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
#ifndef	__Comm_698_H
#define	__Comm_698_H

#include	"Public.h"
#include	"communication.h"
#include	"DI_698.h"
#include	"Public_Code.h"

typedef struct
{
	uchar8	Len;			/* ��ȫ���ݳ���*/
	uchar8	*Data;			/* ��ȫ���ݻ���*/
}SecurityData_Type;

typedef struct
{
	uchar8	Len;			/* ��ȫMAC ���ݳ���*/
	uchar8	*MAC;			/* ��ȫ���ݻ���*/
}SecurityMAC_Type;

typedef struct
{
	uchar8	SecurityAPDUType;			/* ��ȫ����*/
	SecurityData_Type	*SecurityData;	/* ��ȫ���ݻ���*/
	uchar8	SecurityMACType;			/*��ȫ������֤����*/
	SecurityMAC_Type	*SecurityMAC;	/* ��֤���ݻ���*/
}Security_APDU_Type;

typedef struct
{
	uchar8	PIID;						/* PIID*/
	ulong32	*OAD;						/* OAD*/
}GetReqNormal_Type;

typedef struct
{
	uchar8	PIID;						/* PIID*/
	uchar8	OADNum;						/* OAD����*/
	ulong32	*OAD;						/* OAD�����׵�ַ*/
}GetReqNormalList_Type;



typedef struct
{
	ulong32	OAD;						/* �����ʶ*/
	uchar8	*Data;						/* ������ֵ*/
}SelectType1_Type;

typedef struct
{
	ulong32	OAD;						/* �����ʶ*/
	uchar8	*StartData;					/* ��ʼֵ*/
	uchar8	*EndData;					/* ����ֵ*/
	uchar8	*InternalData;				/* ���ֵ*/
}SelectType2_Type;

typedef struct
{
	uchar8				SelectNum;		/* ѡ��������*/
	SelectType2_Type	*SelectType2;	/* ѡ�񷽷��׵�ַ*/
}SelectType3_Type;

typedef struct
{
	uchar8	RecordNum;					/*�ϵ�n����¼*/
}SelectType9_Type;

typedef struct
{
	uchar8	SelectType;					/* ѡ�񷽷�*/
	uchar8	*RSDData;					/* RSDѡ���Ӧ��������*/
}RSD_Type;

typedef struct
{
	ulong32	*OAD;						/* ��¼�����ʶ*/
	uchar8	RelationOADNum;				/* �����������Ը���*/
	ulong32	*RelationOAD;				/* �����������Ա�ʶ�׵�ַ*/
}RelationOAD_Type;

typedef struct
{
	ulong32				*OAD;			/* ��¼�����ʶ*/
	RelationOAD_Type	*RelatOAD;		/* ���������б��׵�ַ*/
}ROAD_Type;

typedef struct
{
	uchar8	CSDType;					/* CSD����*/
	uchar8	*CSDData;					/* CSD�����׵�ַ*/
}CSD_Type;

typedef struct
{
	uchar8		CSDNum;					/* CSD����*/
	CSD_Type	*CSD;					/* CSD�����׵�ַ*/
}RCSD_Type;


typedef struct
{
	ulong32		OAD;					/* OAD*/
	RSD_Type	RSD;					/* RSD*/
	RCSD_Type	RCSD;					/* RCSD*/
}GetRecord_Type;

typedef struct
{
	uchar8			PIID;				/* PIID*/
	GetRecord_Type	*GetRecord;			/* OAD*/
}GetReqRecord_Type;

typedef struct
{
	uchar8			PIID;				/* PIID*/
	uchar8			GetRecordNum;		/* GetRecord����*/
	GetRecord_Type	*GetRecord;			/* OAD�����׵�ַ*/
}GetReqRecordList_Type;

typedef struct
{
	uchar8		PIID;					/* PIID*/
	ushort16	GetRecordNum;			/* �ѽ��յ���ȷ֡���*/
}GetReqNext_Type;

typedef struct
{
	uchar8	GetAPDUType;				/* ��ȡ��������*/
	uchar8	*GetAPDUTData;				/* ��ȡ��������*/
}Get_APDU_Type;

typedef struct
{
	uchar8	SetAPDUType;				/* ��ȡ��������*/
	uchar8	*SetAPDUTData;				/* ��ȡ��������*/
}Set_APDU_Type;


typedef struct
{
	ulong32	OAD;						/* OAD*/
	uchar8	*Data;						/* Data*/
}SetData_Type;

typedef struct
{
	uchar8			PIID;				/* PIID*/
	SetData_Type	*SetData;			/*��������*/
}SetReqNormal_Type;

typedef struct
{
	uchar8			PIID;				/* PIID*/
	uchar8			OADNum;				/* OAD����*/
	SetData_Type	*SetData;			/* �������ݻ����׵�ַ*/
}SetReqNormalList_Type;

typedef struct
{
	ulong32	SetOAD;						/* ��������OAD*/
	uchar8	*Data;						/* Data*/
	ulong32	GetOAD;						/* ��ȡ���ݶ�������*/
	uchar8	DelayTime;					/* ��ʱ��ȡʱ��*/
}SetGetData_Type;

typedef struct
{
	uchar8			PIID;				/* PIID*/
	uchar8			OADNum;				/* OAD����*/
	SetGetData_Type	*SetGetData;		/* �������ݻ����׵�ַ*/
}SetGetReqNormalList_Type;



#define	C_ClientStart_DIR					0x00				/*�ͻ��˷���*/
#define	C_ServerStart_DIR					0x80				/*����������*/
#define	C_ClientStart_PRM					0x40				/*�ͻ��˷���*/
#define	C_Scramble_Flag						0x08				/*�����־λ��1��ʾ�����룬0��ʾû������*/
                                    		            		
#define	C_ProtocolConformance_Len			8					/*Э��һ���Գ���*/
#define	C_FunctionConformance_Len			16					/*����һ���Գ���*/
#define	C_TxRxMaxLen_Len					2					/*APDU����*/
#define	C_ConectStruct_Len					48					/*��ȫ�������ͽṹ�峤��*/
                                                        		
                                                        		
#define	C_ClientTxMaxLen					512					/*�ͻ�������֡���ߴ�512*/
/********* 698�����ݴ�ṹ��************/           			
ConectRequest_Type	Com_Conect;									/*ͨ��Ӧ�����ӽṹ��*/
uchar8	GV_ComConect_Timer;										/*S*/
uchar8	GV_GEsam_500Timer;										/*ESAM 500ms������*/
uchar8	GV_GEsam_1min;			    							/*1���Ӷ�ʱ��*/
#define	C_NullSecyrityConnect				0x00				/*��������*/
#define	C_PasswordSecurityConnect			0x01				/*һ������*/
#define	C_SymmetrySecurityConnect			0x02				/*�Գ���Կ*/
#define	C_SignatureSecurityConnect			0x03				/*����ǩ��*/

const uchar8 Str_ConnRightType[4] = {0x08, 0x04, 0x02, 0x01};	/*Ӧ�����Ӷ�Ӧ��Ȩ��,���Ŀ������κ�Ȩ�޲���*/
const uchar8 Str_ESafeTransType[4] = {0x00, 0x04, 0x04, 0x00};	/*���İ�ȫ�����Ӧ��Ȩ��*/
const uchar8 Str_CSafeTransType[4] = {0x01, 0x00, 0x00, 0x02};	/*���İ�ȫ�����Ӧ��Ȩ��*/


#define C_AddrTpyeBits						0xC0				/*��ַ���Ͷ�Ӧλ*/
#define C_LogicAddrBits						0x30				/*�߼���ַ���Ͷ�Ӧλ*/
#define C_AddrLenBits						0x0F				/*SA��ַ���ȶ�Ӧλ*/
                        					            		
#define C_AddrTypePtoP						0x00				/*������ַ*/
#define C_AddrTypePtoX						0x40				/*ͨ���ַ*/
#define C_AddrTypePtoM						0x80				/*�鲥��ַ*/
#define C_AddrTypePtoAll					0xC0				/*�㲥��ַ*/

#define C_SECURITY_Request					0x10				/*��ȫ����*/
#define C_CONNECT_Request					0x02				/*Ӧ������*/
#define C_RELEASE_Request					0x03				/*�Ͽ�Ӧ������*/
#define C_GET_Request						0x05				/*����������*/
#define C_SET_Request						0x06				/*д��������*/
//#define C_ACTION_Request					0x07				/*��������*/
#define C_REPORT_Response					0x08				/*�ϱ�Ӧ��*/
#define C_PROXY_Request						0x09				/*��������*/
                                			            		
#define C_Default_Request					0x6E				/*�쳣��Ӧ����*/


#define C_SETNormal_Request					0x01						/*����һ����������*/
#define C_SETNormalList_Request				0x02						/*���ö����������*/
#define C_SETGETNormalList_Request			0x03						/*���ú��ȡ��ȡ�����������*/
                                    		
#define C_ACTIONNormal_Request				C_SETNormal_Request			/*����һ����������*/
#define C_ACTIONNormalList_Request			C_SETNormalList_Request		/*���������������*/
#define C_ACTIONGETList_Request				C_SETGETNormalList_Request	/*�������ȡ��ȡ�����������*/
         

/*2020��׼�����ϱ�2005*/
#define C_07EventReportTypeAttribute		11							/*07���¼����ϱ���ʽ����*/
#define C_24EventReportTypeAttribute		15							/*24���¼����ϱ���ʽ����*/
#define C_ReportAddListClear				0x01						/*�����¼��б�����*/
#define C_FollowStatusClear					0x02						/*�����ϱ�״̬������*/
#define C_ListEventNo						0xFF						/*�����б����ʱ����0xFF*/
#define C_ExceptPowerFailListEventNo		0xFE						/*�����б����ʱ�����˵���������¼�����0xFE*/

#define C_REPORTNormalList_Request			0x01						/*�ϱ���������*/
#define C_REPORTRecordList_Request			0x02						/*�ϱ��¼����������*/
#define C_REPORTData_Request				0x03						/*�ϱ�͸������*/
#define C_REPORTListMaxLen					C_ModuleMaxLen-47			/*47=4��FE��+21(��ȫ����֡)+19(RN+MAX)+3(У��+16)*/
#define C_CodeOADlen						0x05						/*OAD���볤�ȣ�5���ֽ�*/
#define C_ReportOTimer						10							/*�����ϱ���ʱȷ��ʱ�䣬1Sһ�Σ�Ŀǰ��10s*/
#define C_ReportOTimer1s					1							/*���緢�������ϱ���ʱȷ��ʱ�䣬1S��*/
#define	C_SPI_500ms							25000						/*���ճ�ʱ��50ms,2us��׼*/
#define C_ReportMaxDealNum					2							/*500ms��һ�������ϱ��Ƿ��ڷ��ͣ����֧��2.5S*/ 

#define C_ESAMF1000300  					0xF1000300					/*ESAM���ݶ�ȡ����������*/

#define	C_ESAMAction_NO1					0x01						/*ESAM��λ*/
#define	C_ESAMAction_NO2					0x02						/*ESAMִ��*/
#define	C_ESAMAction_NO3					0x03						/*ESAM����*/
#define	C_ESAMAction_NO4					0x04						/*ESAM���ݸ���*/
#define	C_ESAMAction_NO5					0x05						/*Э��ʧЧ*/

#define	C_ESAMAction_NO6					0x06						/*ESAMǮ������*/
#define	C_ESAMAction_NO7					0x07						/*ESAM��Կ����*/
#define	C_ESAMAction_NOA					0x0A						/*ESAMǮ����ʼ��*/
#define	C_ESAMAction_NOB					0x0B						/*������֤����*/
#define	C_ESAMAction_NOC					0x0C						/*������֤*/
#define	C_ESAMAction_NO9					0x09						/*����Э��ʱЧ*/

#define	C_GETNormal_Request_Off				0x03						/*data��ʼ��ַ*/


#define	C_ForbidenRW						0x03						/*�ܾ���д*/
#define	C_FrameNoErr						14							/*֡��Ŵ�*/

#define	C_GetResponseOK						0x01						/*��������ȷӦ��*/
#define	C_GetResponseERR					0x00						/*�������쳣Ӧ��*/
#define	C_LastFrameErr						0x00						/*����ĩ֡��־*/
#define	C_LastFrameOK						0x01						/*ĩ֡��־*/
#define	C_TimeTagOn							0x68						/*��ʱ���ǩ��ʶ*/
#define C_TimeTagInvalid					0x20						/*ʱ���ǩ��Ч*/
#define	C_ServiceType_Err					0x89						/*�������Ͳ�ƥ��*/

#define C_MaxReadListNum					0x14						/*ReadList�������֧��OAD����*/

#define	C_APDUDecode_Fault					0x01						/*APDU�޷�����*/
#define	C_ServiceType_Fault					0x02						/*����֧��*/
#define	C_Service_OtherFault				0xFF						/*��������*/

#define	C_Read_Flag3000						0x01						/*3000��ȡ*/
#define	C_Read_FlagNor						0x00						/*������ȡ*/
#define C_EnCodeMaxLen						100							/*֡ͷ֡β+ʱ���ǩ+�����ϱ�+RN+������󳤶�Ԥ��*/

typedef struct
{
	ulong32		WtOI;							/*дOI*/
	uchar8		Wt_Result;						/*д�������*/
	ushort16	DataLen;						/*д�������ݳ���*/
	uchar8		*Wt_Data;						/*д���������׵�ַ*/
}WtOI_Rt_T;


typedef struct
{
	uchar8		PIID;							/*PIID*/
	uchar8		RWOI_Num;						/*��д��OI����*/
	RdOI_Para_T	Rd_OI[C_MaxReadListNum];		
	WtOI_Rt_T	Wt_OI[C_MaxReadListNum];		
	ulong32		W_R_DelayTime;					/*д���ݺ���ʱ��ȡʱ�䣬����ж��д��������ȡ��ʱȡ�����ʱ*/
	uchar8		ServiceFlag_Second;				/*�ڶ����������ͣ���һ���������ԡ���ȡ����������ԡ���ȡһ����¼���󡢶�ȡ�����¼���󡢶�ȡ��������*/
	uchar8		ServiceFlag_First;				/*��һ���������ͣ���һ���������ԡ���ȡ����������ԡ���ȡһ����¼���󡢶�ȡ�����¼���󡢶�ȡ��������*/
	uchar8		Current_FrameNO;				/*��ǰ֡���*/
	uchar8		ChannelNo;						/*ͨ����*/
	uchar8		Next_OINO;						/*��һ����ȡ��OI���*/
	uchar8		ResponedNum;					/*�Ѿ�Ӧ���OAD����*/
	uchar8		HaveEncodeNum;					/*�Ѿ�Ӧ���OAD����*/
	uchar8		ResponedRelationNum;			/*�Ѿ�Ӧ��Ĺ����������Ը���*/
	uchar8		TimeTag[9+3];					/*ʱ���ǩ����һ���ֽ�Ϊ0x68��ʾ�Ƿ���ʱ���ǩ������Ϊ��ʱ���ǩ*/
	uchar8		EndFrame;						/*Ӧ�ò�ĩ֡��־*/
	ushort16	FrameNUM;						/*Ӧ�ò��֡���*/
	uchar8		LastServiceFlag_Second;			/*����֡��������һ֡��������*/
	uchar8		CurrentOADEnd;					/*��ǰoad����֡��־*/			
	uchar8		firstRNSICBit;					/*��֡Ȩ����ռbitλ*/
	uchar8		lastRNSICBit;					/*����֡Ȩ����ռbitλ*/
}Str_Comm_698_RW;
static Str_Comm_698_RW  SV_RS485_1_698RWParm @".DataProcessADDR";
static Str_Comm_698_RW  SV_RS485_2_698RWParm @".DataProcessADDR";
static Str_Comm_698_RW  SV_IR_698RWParm @".DataProcessADDR";
static Str_Comm_698_RW  SV_Module_698RWParm @".DataProcessADDR";

/*****************************698.45���***********************************************/
#define	C_Len								0x80
#define	C_Num								0x40
#define	C_Type								0x20

typedef  struct
{
	uchar8 	DataType;								/*��������*/
	uchar8 	DataLen;								/*�¼����ͱ���*/
}Str_DataTpye_Type;

#define	C_SPECIAL1							0xF1	/*���⴦����1*/
#define	C_SPECIAL2							0xF2	/*���⴦����2*/
#define	C_SPECIAL3							0xF3	/*���⴦����3*/
#define	C_SPECIAL4							0xF4	/*���⴦����4*/
#define	C_SPECIAL5							0xF5	/*���⴦����5*/
#define	C_SPECIAL6							0xF6	/*���⴦����6*/
#define	C_SPECIAL7							0xF7	/*���⴦����7*/
const Str_DataTpye_Type	Str_DataTpye[] =
{//�������ͣ�				���������ص�
	{C_array,					C_Len|C_Num|C_Type},	/*[1]*/
	{C_structure,				C_NULL},				/*[2]*/
	{C_bool,					1},						/*[3]*/
	{C_bit_string,				C_Len},					/*[4]*/
	{C_double_long,				4},						/*[5]*/
	{C_double_long_unsigned,	4},						/*[6]*/
	{C_octet_string,			C_Len},					/*[9]*/
	{C_visible_string,			C_Len},					/*[10]*/
	{C_UTF8_string,				C_Len},					/*[12]*/
	{C_integer,					1},						/*[15]*/
	{C_long,					2},						/*[16]*/
	{C_unsigned,				1},						/*[17]*/
	{C_long_unsigned,			1},						/*[18]*/
	{C_long64,					8},						/*[20]*/
	{C_long64_unsigned,			8},						/*[21]*/
	{C_enum,					1},						/*[22]*/
	{C_float32,					4},						/*[23]*/
	{C_float64,					8},						/*[24]*/
	{C_date_time,				10},					/*[25]*/
	{C_date,					5},						/*[26]*/
	{C_time,					3},						/*[27]*/
	{C_OI,						2},						/*[80]*/
	{C_OAD,						4},						/*[81]*/
	{C_ROAD,					C_SPECIAL1},			/*[82]*/
	{C_OMD,						4},						/*[83]*/
	{C_TI,						3},						/*[84]*/
//	{C_TSA,						C_Len},					/*[85]*/
	{C_MAC,						C_Len},					/*[86]*/
	{C_RN,						C_Len},					/*[87]*/
	{C_Region,					C_SPECIAL2},			/*[88]*/
	{C_Scaler_Unit,				2},						/*[89]*/
	{C_RSD,						C_SPECIAL3},			/*[90]*/
	{C_CSD,						C_SPECIAL4},			/*[91]*/
	{C_SID,						C_SPECIAL5},			/*[93]*/
	{C_SID_MAC,					C_SPECIAL6},			/*[94]*/
	{C_COMDCB,					C_SPECIAL7},			/*[95]*/
	{C_RCSD,					C_Num|C_Type},			/*[96]*/
};
#define C_DataTypeTable1_Len			23

			
const uchar8 DataTypeTable1[C_DataTypeTable1_Len][2] = 
{
	C_bool,						CL_bool					,						/*[3]*/
	C_double_long,				CL_double_long		    ,						/*[5]*/
	C_double_long_unsigned,		CL_double_long_unsigned ,						/*[6]*/
	C_integer,					CL_integer				,						/*[15]*/
	C_long,						CL_long					,						/*[16]*/
	C_unsigned,					CL_unsigned				,						/*[17]*/
	C_long_unsigned,			CL_long_unsigned		,						/*[18]*/
	C_long64	,				CL_long64			    ,						/*[20]*/
	C_long64_unsigned,			CL_long64_unsigned		,						/*[21]*/
	C_enum,						CL_enum				    ,						/*[22]*/
	C_float32,					CL_float32			    ,						/*[23]*/
	C_float64,					CL_float64				,						/*[24]*/
	C_date_time,				CL_date_time			,						/*[25]*/
	C_date,						CL_date				    ,						/*[26]*/
	C_time,						CL_time				    ,						/*[27]*/
	C_date_time_s,				CL_date_time_s		    ,						/*[28]*/
	C_OI,						CL_OI					,						/*[80]*/
	C_OAD,						CL_OAD				    ,						/*[81]*/
	C_OMD,						CL_OMD				    ,						/*[83]*/
	C_TI,						CL_TI				    ,						/*[84]*/
  	C_Scaler_Unit	,			CL_Scaler_Unit	        ,						/*[89]*/
	C_CSD,						CL_CSD				    ,						/*[91]*/
	C_COMDCB,					CL_COMDCB               ,						/*[95]*/
	//C_NULL,					0,						/*[95]*/
};                                          			 
const uchar8 DataTypeTable2[17][2]=         			 
{                                           			 
	C_array,					0,						/*[1]*/
	C_structure,				0,						/*[2]*/
	C_bit_string,				0,						/*[4]*/
	C_octet_string,				0,						/*[9]*/
	C_visible_string,			0,						/*[10]*/
	C_UTF8_string	,			0,						/*[12]*/
	C_ROAD,						0,						/*[82]*/
	C_TSA,						0,						/*[85]*/
	C_MAC,						0,						/*[86]*/
  	C_RN,			     		0,						/*[87]*/
  	C_Region,					0,						/*[88]*/
	C_RSD,						0,						/*[90]*/
	C_CSD,						0,						/*[91]*/
	C_SID,						0,						/*[93]*/
	C_SID_MAC,              	0,						/*[94]*/
	C_COMDCB,              		0,						/*[95]*/
	C_RCSD,                    	0,						/*[96]*/
};                                                       
/*��궨��*/
#define	C_Energy_Class						1 				/* ������ */
#define	C_Demand_Class						2 				/* ���� */
#define	C_Variable_Class					3 				/* ������� */
#define	C_Power_Class						4 				/* ���� */
#define	C_DateVariables_Class				6 				/* ���ݱ��� */
#define	C_Event_Class						7 				/* �¼���¼*/
#define	C_Parameter_Class					8 				/* �������� */
#define	C_Freeze_Class						9 				/* ����*/
#define	C_Display_Class						17				/* ��ʾ */
#define	C_DeviceIO_Class					19				/* �豸�ӿ��� */
#define	C_Esam_Class						21				/* ESAM */
#define	C_InputAndOutput_Class				22				/* ������ */
#define	C_SplitPhaseEvent_Class				24				/* �����¼���¼ */

#define C_Event_2Attri						2				/*7�������2*/
#define C_SplitPhaseEvent_6Attri			6				/*24�������6*/
#define C_SplitPhaseEvent_7Attri			7				/*24�������7*/
#define C_SplitPhaseEvent_8Attri			8				/*24�������8*/
#define C_SplitPhaseEvent_9Attri			9				/*24�������9*/

/*�¼������ź궨��*/
#define	C_Energy_TableNum					1				/* ������ */
#define	C_Demand_TableNum					2				/* ������� */
#define	C_Variable_TableNum					3				/* ˲ʱ�� */
#define	C_Power_TableNum					4				/* ���� */
#define	C_DateVariables_TableNum			5				/* ������ */
#define	C_Event_TableNum					6				/* �¼���¼ */
#define	C_Parameter_TableNum				7				/* �α��� */
#define	C_Freeze_TableNum					8				/* ���� */
#define	C_Display_TableNum					9				/* ��ʾ */
#define	C_Esam_TableNum						10				/* ESAM��� */
#define	C_InputAndOutput_TableNum			11				/* ��������ӿ� */
#define	C_SplitPhaseEvent_TableNum			12				/* �����¼���¼ */

#define	C_DerictOIBClass					1				/* ֱ�Ӹ���OIBȷ��645��Ӧ���ݱ�ʶ�룬��������а������������� */
#define	C_DerictOIBNoClass					2				/* ֱ�Ӹ���OIBȷ��645��Ӧ���ݱ�ʶ�룬��������в��������������࣬����ֱ����1�����õ�����������*/
#define	C_ThirdTable						3				/* �����ɶ������õ��������ֻ�ܶ�Ӧĳ����Ķ��󣬾�����������ʾ��Ӧ�¼���� */


#define	C_EnergyOIA							0x00			/* ������ */
#define	C_DemandOIA							0x10			/* ���� */
#define	C_VariableOIA20						0x20			/* ˲ʱ�� */
#define	C_VariableOIA21						0x21			/* ˲ʱ�� */
#define	C_ParameterOIA40					0x40			/* �α��� */
#define	C_ParameterOIA41					0x41			/* �α��� */
#define	C_ParameterOIA43					0x43			/* �α��� */
#define	C_PasswordrOIA44					0x44			/* �α��� */
#define	C_PasswordrOIA45					0x45			/* �α��� */
#define	C_EventRecordOIA					0x30			/* �¼���¼ */
#define	C_FrozeRecordOIA					0x50			/* �����¼ */
#define	C_ESAMActionOIA						0xF1			/* ESAM������� */
#define	C_ContralOIA						0x80			/* ���Ʋ������ */
#define	C_ApplianceInOutOIA					0xF2			/* ��������豸��� */
#define	C_DisplayOIA						0xF3			/* ��ʾ */
#define C_ReportList						0x33			/*�����ϱ��¼��б�*/
#define C_FileTransferOIA					0xF0			/*�ļ�����*/
#define C_ExternalOIA						0xFF			/*��չ����OIA=0xFF*/
                                			
#define	C_Qua4_EnOIB						0x80			/* ��4�����޹����� */
#define	C_EnergyOIB_Tol						0x00			/* ��������жϣ��ų����ࣨbit0-bit3��*/
#define	C_CQua4_EnOIB						0x83			/* C���4�����޹����� */
//*�������� ����
#define	C_Nature1_Name						0x01			/*����1���߼���*/
//*�������� ����
#define	C_Nature2_Energy					0x02			/*��������2���ܼ����ʵ���*/
#define	C_Nature3_EnergyUnit				0x03			/*��������3�����㼰��λ*/
#define	C_Nature4_PreEnergy					0x04			/*��������4���ܼ����ʾ�ȷ����*/
#define	C_Nature5_PreEnergyUnit				0x05			/*��������5���߾��Ȼ��㼰��λ*/
#define	C_Nature6_LastNumPulse				0x06			/*��������6������β��*/
#define	C_Nature7_LastNumPulseUnit			0x07			/*��������7������β�����㼰��λ*/
//*�������� ����
#define	C_Nature2_Demand					0x02			/*�����������2���ܼ������������*/
#define	C_Nature3_DemandUnit				0x03			/*�����������3�����㼰��λ*/
//*ģ��汾��Ϣ���� ����
#define	C_Offset0_FactoryInf				0x00			/*ģ���б�����0��ģ���߼���ַ*/
#define	C_Offset1_FactoryInf				0x01			/*ģ���б�����1��ģ���߼���ַ*/
#define	C_Offset7_FactoryInf				0x07			/*ģ���б�����7��������չ��Ϣ*/


//*����10000
#define	C_CPulse_Constant10000				10000			/*����10000*/
                                			            	
#define	C_DisplayNumMax						99				/*��ʾ�������*/
#define	C_DisplayDICal						0x00000001		/*���ݱ�ʶ�ж���*/
#define	C_DisplayDI2_offset					4				/*������OADʱ���ڶ���OAD��ƫ��*/
#define	C_OADLen							4				/*OAD����4�ֽ�*/

//дͨ�Ź�Լ�б�����ƫ��
#define C_Meter_CommPro_DataOff00			0x00			/*����ƫ��λ��00*/
#define C_Meter_CommPro_DataOff02			0x02			/*����ƫ��λ��02*/
#define C_TypeLen_Len						0x01			/*����+�����У����ȵĳ���1�ֽ�*/

/*˫Э������*/
#define C_NoNeedSet645ReportMode			0x00			/*����Ҫ����645�����ϱ�ģʽ��*/
#define C_NeedSet645ReportMode				0x68			/*��Ҫ����645�����ϱ�ģʽ��*/



#define	C_TableIDDisvaliable				0x86			/*�¼�����еı�ʶ����Ч*/
#define	C_TableIDValiable					0x65			/*�¼�����еı�ʶ����Ч*/
#define	C_ClassNum24All						0x80			/*�¼�����еı�ʶ����Ч*/
#define C_MaxDataTypeNum					13				/*����������*/

typedef  struct
{
	ulong32						V_ucOAD;						/*oad�ױ�ʶ��*/
	ushort16					Unit_Scale[C_MaxDataTypeNum];
	ushort16					DataLen_645[C_MaxDataTypeNum];	/*645���ݳ���*/
	Str_DI0_DataType_PaTable	*NextClassNO;					/*�¼����ͱ���ַ*/
	uchar8						DataType[C_MaxDataTypeNum];		/*��������*/
	uchar8						NextClassNum;					/*�¼����͸���*/
	uchar8						IDFlay;							/*�Ƿ���Ҫ�¼�����б�ʶ���־*/
	uchar8						IDNO;							/*�¼���¼��24����ǰ��¼����Ӧ645������־*/
	uchar8						DataLen_698[C_MaxDataTypeNum];	/*�ĳ���ֻ������ݳ��Ȳ��̶�����������*/
	uchar8						MAXRecordTimes;					/*����¼������һ���¼���¼������Ϊ10�����ô���Ϊ0��ʾû������*/
    uchar8						TZone_Data[CLFirst_TZone_Data];	/*ʱ�����ݴ�����*/
	//uchar8	PointNum;										/*С����������߰��ֽ�Ϊ698С����������Ͱ��ֽ�Ϊ645С����*/
}Str_Type645DI_Class;											/*����ӳ����ʵ��698��645ͨ�Ź�Լ��ʶ���ӳ��*/

#define Str_Type645DI_ClassLen	sizeof(Str_Type645DI_Class)		/*�ṹ�峤��*/


typedef  struct
{
	uchar8	OIA;												/*OIA*/
	uchar8	SecondType;											/*�¼��������*/
	uchar8	TableNum;											/*�¼�������*/
	uchar8	ClassType;											/*�������*/
}Str_698SwitchTo645Table_First;									/*����ӳ����ʵ��698��645ͨ�Ź�Լ��ʶ���ӳ��*/



typedef  struct
{
	uchar8 OIB;													/*OIB*/
	//uchar8 DI2;												/*DI2*/
	uchar8 MaxNum;												/*bit0-bit6����������,bit7=0��ʾ�޷��ţ�bit7=1���з���*/
	uchar8 Unit_Energy;											/*��λ����*/
	uchar8 Unit_Demand;											/*��λ����*/
}Str_OIB_DI2_EnergyTable;										/*������������ӳ��*/
const Str_OIB_DI2_EnergyTable GV_Str_OIB_DI2_EnergyTable[] = 
{/*OIB   	MaxNum  Unit_En	Unit_De */
	{0x00,	0x8D,	33,		C_NULL},							/*����й�*/
	{0x10,	0x0D,	33,		28},								/*�����й�*/
	{0x11,	1,		33,		28},								/*A�������й�*/
	{0x12,	1,		33,		28},								/*B�������й�*/
	{0x13,	1,		33,		28},								/*C�������й�*/
	{0x20,	0x0D,	33,		28},								/*�����й�*/
	{0x21,	1,		33,		28},								/*A�෴���й�*/
	{0x22,	1,		33,		28},								/*B�෴���й�*/
	{0x23,	1,		33,		28},								/*C�෴���й�*/
	{0x30,	0x8D,	35,		32},								/*����޹�1*/
	{0x31,	0x81,	35,		32},								/*A������޹�1*/
	{0x32,	0x81,	35,		32},								/*B������޹�1*/
	{0x33,	0x81,	35,		32},								/*C������޹�1*/
	{0x40,	0x8D,	35,		32},								/*����޹�2*/
	{0x41,	0x81,	35,		32},								/*A������޹�2*/
	{0x42,	0x81,	35,		32},								/*B������޹�2*/
	{0x43,	0x81,	35,		32},								/*C������޹�2*/
	{0x50,	0x0D,	35,		32},								/*��һ�����޹�*/
	{0x51,	1,		35,		32},								/*A���һ�����޹�*/
	{0x52,	1,		35,		32},								/*B���һ�����޹�*/
	{0x53,	1,		35,		32},								/*C���һ�����޹�*/
	{0x60,	0x0D,	35,		32},								/*�ڶ������޹�*/
	{0x61,	1,		35,		32},								/*A��ڶ������޹�*/
	{0x62,	1,		35,		32},								/*B��ڶ������޹�*/
	{0x63,	1,		35,		32},								/*C��ڶ������޹�*/
	{0x70,	0x0D,	35,		32},								/*���������޹�*/
	{0x71,	1,		35,		32},								/*A����������޹�*/
	{0x72,	1,		35,		32},								/*B����������޹�*/
	{0x73,	1,		35,		32},								/*C����������޹�*/
	{0x80,	0x0D,	35,		32},								/*���������޹�*/
	{0x81,	1,		35,		32},								/*A����������޹�*/
	{0x82,	1,		35,		32},								/*B����������޹�*/
	{0x83,	1,		35,		32},								/*C����������޹�*/
};
#define	GV_Str_OIB_DI2_EnergyTableLen	( sizeof(GV_Str_OIB_DI2_EnergyTable) / sizeof(Str_OIB_DI2_EnergyTable) )

#define	C_WithOutSign						0x7F				/*ȥ��GV_Str_OIB_DI2_EnergyTable[].MaxNum�еķ��ţ�ȡ��ֵ*/

typedef  struct
{
	uchar8 OIB;													/*OIB*/
	uchar8 ClassType;											/*�������*/
	uchar8 DataType;											/*��������*/
	uchar8 MaxNum;												/*����������*/
	uchar8 Unit;												/*��λ����*/
	char8 Conversion;											/*����*/
}Str_OIB_DI2_VariableTable;										/*��ѹ�������ʵ�ӳ��*/

const Str_OIB_DI2_VariableTable GV_Str_OIB_DI2_VariableTable01[] = 
{   /*OIB   	ClassType				dataType				MaxNum	Unit	Conversion*/
	{0x00,	C_Variable_Class,		C_long_unsigned,			3,		38,		-1},		/*��ѹ*/
	{0x01,	C_Variable_Class,		C_double_long,				3,		36,		-3},		/*����*/
	{0x02,	C_Variable_Class,		C_long_unsigned,			3,		8,		-1},		/*��ѹ���*/
	{0x03,	C_Variable_Class,		C_long_unsigned,			3,		8,		-1},		/*��ѹ�������*/
	{0x04,	C_Power_Class,			C_double_long,				4,		27,		-1},		/*�й�����*/
	{0x05,	C_Power_Class,			C_double_long,				4,		31,		-1},		/*�޹�����*/
	{0x06,	C_Power_Class,			C_double_long,				4,		29,		-1},		/*���ڹ���*/
	{0x07,	C_Power_Class,			C_double_long,				4,		27,		-1},		/*һ����ƽ������*/
	{0x08,	C_Power_Class,			C_double_long,				4,		31,		-1},		/*һ����ƽ������*/
	{0x0A,	C_Power_Class,			C_long,						4,		255,	-3},		/*��������*/
	{0x0F,	C_DateVariables_Class,	C_long_unsigned,			1,		47,		-2},		/*����Ƶ��*/
	{0x10,	C_DateVariables_Class,	C_long,						1,		9,		-1},		/*�����¶�*/
	{0x11,	C_DateVariables_Class,	C_long_unsigned,			1,		38,		-2},		/*ʱ�ӵ�ص�ѹ*/
	{0x12,	C_DateVariables_Class,	C_long_unsigned,			1,		38,		-2},		/*ͣ�糭���ص�ѹ*/
	{0x13,	C_DateVariables_Class,	C_double_long_unsigned,		1,		6,		C_NULL},	/*ʱ�ӵ�ع���ʱ��*/
	{0x14,	C_DateVariables_Class,	C_bit_string,				7,		255,	C_NULL},	/*�������״̬��*/
	{0x17,	C_DateVariables_Class,	C_double_long,				1,		28,		-4},		/*��ǰ�й�����*/
	{0x18,	C_DateVariables_Class,	C_double_long,				1,		32,		-4},		/*��ǰ�޹�����*/
                                                            	
#if 0                                                       	
	{0x19,	C_DateVariables_Class,	C_double_long,				1,		30,		-4},		/*��ǰ��������*/
#endif                                                      	                    		
                                                            	                    		
	{0x1A,	C_DateVariables_Class,	C_double_long_unsigned,		1,		54,		-4},		/*��ǰ���*/
	{0x1B,	C_DateVariables_Class,	C_double_long_unsigned,		1,		54,		-4},		/*��ǰ���ʵ��*/
	{0x1C,	C_DateVariables_Class,	C_double_long_unsigned,		1,		54,		-4},		/*��ǰ���ݵ��*/
	{0x2C,	C_Parameter_Class,		C_double_long_unsigned,		2,		254,	-2},		/*��ǰǮ���ļ�*/
	{0x2D,	C_DateVariables_Class,	C_double_long_unsigned,		1,		10,		-2},		/*��ǰ͸֧���*/
	{0x2E,	C_DateVariables_Class,	C_double_long_unsigned,		1,		10,		-2},		/*�ۼƹ�����*/
	{0x40,	C_DateVariables_Class,	C_bit_string,				1,		255,	C_NULL},	/*��������ִ��״̬��*/
	{0x41,	C_DateVariables_Class,	C_bit_string,				1,		255,	C_NULL},	/*�����������״̬��*/
	{0x42,	C_DateVariables_Class,	C_bit_string,				1,		255,	C_NULL},	/*��������ִ��״̬��*/
	{0x31,	C_DateVariables_Class,	C_double_long_unsigned,		1,		33,		-2},		/*�¶��õ���*/
	{0x32,	C_DateVariables_Class,	C_double_long_unsigned,		1,		33,		-2},		/*���ݽ����õ���*/
    {0x15,  C_DateVariables_Class,  C_bit_string,				1,		255,	C_NULL},	/*�������״̬��8*/
};
#define GV_Str_OIB_DI2_VariableTable01Len ( sizeof(GV_Str_OIB_DI2_VariableTable01) / sizeof(Str_OIB_DI2_VariableTable) )

const Str_OIB_DI2_VariableTable GV_Str_OIB_DI2_VariableTable02[] = 
{/*OIB   	ClassType				dataType					MaxNum	Unit	Conversion*/
	{0x31,	C_DateVariables_Class,	C_structure,				2,		0xFF,		C_NULL},/*A���ѹ�ϸ���*/
	{0x32,	C_DateVariables_Class,	C_structure,				2,		0xFF,		C_NULL},/*B���ѹ�ϸ���*/
	{0x33,	C_DateVariables_Class,	C_structure,				2,		0xFF,		C_NULL},/*C���ѹ�ϸ���*/
};
#define GV_Str_OIB_DI2_VariableTable02Len ( sizeof(GV_Str_OIB_DI2_VariableTable02) / sizeof(Str_OIB_DI2_VariableTable) )



const Str_DI0_DataType_PaTable GV_Str_DI0_DataType_VolRateTable[] = 						/*��ѹ�ϸ���*/
{/*	DataType */
	{C_structure,					0x85,					0},
	{C_double_long_unsigned,		CLPer_Pass_MonitorTime,	CLPer_Pass_MonitorTime},		/*��ѹ���ʱ��*/
	{C_long_unsigned,				CLPer_Pass_PassRate,	CLPer_Pass_PassRate},			/*��ѹ�ϸ���*/
	{C_long_unsigned,				CLPer_Pass_OverRate,	CLPer_Pass_OverRate},			/*��ѹ������*/
	{C_double_long_unsigned,		CLPer_Pass_OverUpTime,	CLPer_Pass_OverUpTime},			/*��ѹ������ʱ��*/
	{C_double_long_unsigned,		CLPer_Pass_OverLowTime,	CLPer_Pass_OverLowTime}			/*��ѹ������ʱ��*/
};
#define GV_Str_DI0_DataType_VolRateTableLen ( sizeof(GV_Str_DI0_DataType_VolRateTable) / sizeof(Str_DI0_DataType_PaTable) )


/*����������ź궨��*/
#define C_MeterPosition_DataTypeNum					1					/*���ܱ�λ����Ϣ:���ȡ�γ�ȡ��߶�*/
#define C_LCDParamete_DataTypeNum					2					/*LCD����*/
#define C_ZoneTime_DataTypeNum						3					/*ʱ��ʱ����*/
#define	C_Holidy_DataTypeNum						4					/*��������*/
#define	C_Zone_DataTypeNum							5					/*��ǰ��ʱ����*/
#define	C_Time_DataTypeNum							7					/*��ǰ��ʱ�α�*/
#define	C_SettleDay_DataTypeNum						9					/*������*/
#define	C_VoltageOKPara								10					/*��ѹ�ϸ��ʲ���*/
#define	C_Display_DataTypeNum						6					/*��ʾ��*/
#define	C_DisplayNum_DataTypeNum					8					/*��ʾ����*/
#define	C_AlarmLimit_DataTypeNum					11					/*�������*/
#define	C_OtherLimit_DataTypeNum					12					/*��������*/
#define	C_Fate_DataTypeNum							13					/*��ǰ�׷��ʵ��*/
#define	C_Ladder_DataTypeNum						14					/*��ǰ�׽���*/
#define	C_BroadTime_DataTypeNum						15					/*�㲥Уʱ����*/
#define	C_FactoryInfTypeNum							16					/*ģ��汾��Ϣ����*/
#define	C_Meter_CommProNum							17					/*ͨ�Ź�Լ*/


typedef  struct
{
	uchar8 OIB;							/*OIB*/
	//uchar8	DI2;					/*DI2*/
	//ushort16	DI1DI0;					/*DI1DI0*/
	uchar8 Unit;						/*��λ����*/
	char8 Conversion;					/*����*/
	uchar8 DataType;					/*��������*/
	uchar8 NxtDataTypeNum;				/*�¼������������*/

}Str_OIB_DI2_ParameterTable01;			/*������ӳ��*/

const Str_OIB_DI2_ParameterTable01 GV_Str_OIB_DI2_ParameterTable01[] =
{/*OIB   	Unit		Conversion		DataType				NxtDataTypeNum	*/
	{0x00,	C_NULL,		C_NULL,			C_date_time_s,			C_NULL},						/*����ʱ��*/
	{0x01,	C_NULL,		C_NULL,			C_octet_string,			C_NULL}, 						/*ͨ�ŵ�ַ*/
	{0x02,	C_NULL,		C_NULL,			C_octet_string,			C_NULL},						/*���*/
	{0x03,	C_NULL,		C_NULL,			C_octet_string,			C_NULL},						/*�ͻ����*/
	{0x04,	C_NULL,		C_NULL,			C_structure,			C_MeterPosition_DataTypeNum},	/*�豸����λ��*/
//	{0x05,	C_NULL,		C_NULL,			C_array,				C_GroupAddress_DataTypeNum},	/*���ַ*/
	{0x07,	7,			C_NULL,			C_structure,			C_LCDParamete_DataTypeNum},		/*LCD����*/
	{0x08,	C_NULL,		C_NULL,			C_date_time_s,			C_NULL},						/*����ʱ�����л�ʱ��*/
	{0x09,	C_NULL,		C_NULL,			C_date_time_s,			C_NULL},						/*������ʱ�α��л�ʱ��*/
	{0x0A,	C_NULL,		C_NULL,			C_date_time_s,			C_NULL},						/*���׷�ʱ�����л�ʱ��*/
	{0x0B,	C_NULL,		C_NULL,			C_date_time_s,			C_NULL},						/*���׽��ݵ���л�ʱ��*/
	{0x0C,	C_NULL,		C_NULL,			C_structure,			C_ZoneTime_DataTypeNum},		/*ʱ��ʱ����*/
	{0x0D,	C_NULL,		C_NULL,			C_unsigned,				C_NULL},						/*������*/
//	{0x0F,	C_NULL,		C_NULL,			C_unsigned,				C_NULL},						/*��Կ������*/
	{0x10,	C_NULL,		C_NULL,			C_unsigned,				C_NULL},						/*������Ԫ��*/
	{0x11,	C_NULL,		C_NULL,			C_array,				C_Holidy_DataTypeNum},			/*�������ձ�*/
	{0x12,	C_NULL,		C_NULL,			C_bit_string,			C_NULL},						/*������������*/
	{0x13,	C_NULL,		C_NULL,			C_unsigned,				C_NULL},						/*�����ղ��õ���ʱ�α��*/
	{0x14,	C_NULL,		C_NULL,			C_array,				C_Zone_DataTypeNum},			/*��ǰ��ʱ����*/
	{0x15,	C_NULL,		C_NULL,			C_array,				C_Zone_DataTypeNum},			/*������ʱ����*/
	{0x16,	C_NULL,		C_NULL,			C_array,				C_Time_DataTypeNum},			/*��ǰ����ʱ�α�*/
	{0x17,	C_NULL,		C_NULL,			C_array,				C_Time_DataTypeNum},			/*��������ʱ�α�*/
	{0x18,	C_NULL,		C_NULL,			C_array,				C_Fate_DataTypeNum},			/*��ǰ�׷��ʵ��*/
	{0x19,	C_NULL,		C_NULL,			C_array,				C_Fate_DataTypeNum},			/*�����׷��ʵ��*/
	{0x1A,	C_NULL,		C_NULL,			C_structure,			C_Ladder_DataTypeNum},			/*��ǰ�׽��ݵ��*/
	{0x1B,	C_NULL,		C_NULL,			C_structure,			C_Ladder_DataTypeNum},			/*�����׽��ݵ��*/
	{0x1C,	C_NULL,		C_NULL,			C_double_long_unsigned,	C_NULL},						/*�������������*/
	{0x1D,	C_NULL,		C_NULL,			C_double_long_unsigned,	C_NULL},						/*��ѹ���������*/
	{0x1E,	C_NULL,		C_NULL,			C_structure,			C_AlarmLimit_DataTypeNum},		/*���������ֵ*/
	{0x1F,	C_NULL,		C_NULL,			C_structure,			C_OtherLimit_DataTypeNum},		/*���������ֵ*/
	{0x22,	C_NULL,		C_NULL,			C_bit_string,			C_NULL},						/*�忨״̬��*/
//	{0x23,	C_NULL,		C_NULL,			C_long_unsigned,		C_NULL},						/*��֤��Чʱ��*/
	{0x30,	38,			-2,				C_structure,			C_VoltageOKPara},				/*��ѹ�ϸ����*/
	{0x31,	C_NULL,		C_NULL,			C_array,				C_FactoryInfTypeNum},			/*ģ��汾��Ϣ*/
};
#define GV_Str_OIB_DI2_ParameterTable01Len ( sizeof(GV_Str_OIB_DI2_ParameterTable01) / sizeof(Str_OIB_DI2_ParameterTable01) )

const Str_OIB_DI2_ParameterTable01 GV_Str_OIB_DI2_ParameterTable02[] =
{/*OIB   	Unit		Conversion			DataType				NxtDataTypeNum */
	{0x00,	6,			0,			C_unsigned,					C_NULL},						/*�����������*/
	{0x01,	6,			0,			C_unsigned,					C_NULL},						/*����ʱ��*/
	{0x02,	56,			0,			C_unsigned,					C_NULL},						/*У��������*/
	{0x03,	C_NULL,		C_NULL,		C_visible_string,			C_NULL},						/*�ʲ��������*/
	{0x04,	C_NULL,		C_NULL,		C_visible_string,			C_NULL},						/*���ѹ*/
	{0x05,	C_NULL,		C_NULL,		C_visible_string,			C_NULL},						/*�����/��������*/
	{0x06,	C_NULL,		C_NULL,		C_visible_string,			C_NULL},						/*������*/
	{0x07,	C_NULL,		C_NULL,		C_visible_string,			C_NULL},						/*�й�׼ȷ�ȵȼ�*/
	{0x08,	C_NULL,		C_NULL,		C_visible_string,			C_NULL},						/*�޹�׼ȷ�ȵȼ�*/
	{0x09,	254,		0,			C_double_long_unsigned,		C_NULL},						/*���ܱ��й�����*/
	{0x0A,	254,		0,			C_double_long_unsigned,		C_NULL},						/*���ܱ��޹�����*/
	{0x0B,	C_NULL,		C_NULL,		C_visible_string,			C_NULL},						/*���ܱ��ͺ�*/
	{0x10,	C_NULL,		C_NULL,		C_bit_string,				C_NULL},						/*�������������1*/
	{0x11,	C_NULL,		C_NULL,		C_visible_string,			C_NULL},						/*���������*/
	{0x12,	C_NULL,		C_NULL,		C_bit_string,				C_NULL},						/*�й���Ϸ�ʽ������*/
	{0x13,	C_NULL,		C_NULL,		C_bit_string,				C_NULL},						/*�޹���Ϸ�ʽ1������*/
	{0x14,	C_NULL,		C_NULL,		C_bit_string,				C_NULL},						/*�޹���Ϸ�ʽ2������*/
	{0x16,	C_NULL,		C_NULL,		C_array,					C_SettleDay_DataTypeNum},		/*������*/

};
#define GV_Str_OIB_DI2_ParameterTable02Len ( sizeof(GV_Str_OIB_DI2_ParameterTable02) / sizeof(Str_OIB_DI2_ParameterTable01) )

const Str_DI0_DataType_PaTable GV_Str_DI0_DataType_DisplayNum[] =								/*��ʾ����*/
{/*DI0	DataType	*/                                              							
	{C_unsigned,	0x01,	1},																	/*��ǰ�ܶ�����*/
	{C_unsigned,	0x01,	1},																	/*������������*/
};
#define GV_Str_DI0_DataType_DisplayNumLen ( sizeof(GV_Str_DI0_DataType_DisplayNum) / sizeof(Str_DI0_DataType_PaTable) )
const Str_DI0_DataType_PaTable C_DemandTpyeTable[] =
{
	{C_double_long,				4,	4},		{C_date_time_s,	7,	7},
	{C_double_long_unsigned,	4,	4},		{C_date_time_s,	7,	7}
};
#define C_DemandTpyeTable_Len ( sizeof(C_DemandTpyeTable) / sizeof(C_DemandTpyeTable[0]) )


const Str_DI0_DataType_PaTable GV_Str_DI0_DataType_MPPaTable[] =			/*λ����Ϣ*/
{/*	DataType	*/
	//{C_structure,				0x84,	0},
	{C_enum,					0x01,	0},
	{C_unsigned,				0x01,	0},
	{C_unsigned,				0x01,	0},
	{C_unsigned,				0x01,	4},
};
#define GV_Str_DI0_DataType_MPPaTableLen (sizeof(GV_Str_DI0_DataType_MPPaTable)/sizeof(Str_DI0_DataType_PaTable))

const Str_DI0_DataType_PaTable GV_Str_DI0_DataType_MPPaTable01[]=			/*λ����Ϣ*/
{/*	DataType	*/
	//{C_structure,				0x84,	0},
	{C_enum,					0x01,	0},
	{C_unsigned,				0x01,	0},
	{C_unsigned,				0x01,	0},
	{C_unsigned,				0x01,	4},
};
#define GV_Str_DI0_DataType_MPPaTable01Len ( sizeof(GV_Str_DI0_DataType_MPPaTable01) / sizeof(Str_DI0_DataType_PaTable) )


const Str_DI0_DataType_PaTable GV_Str_DI0_DataType_LCDPaTable[] =			/*LCD����*/
{/*DataType	*/                                                          	
	{17,	0x01,	1},														/*�ϵ�ȫ��ʱ��*/
	{18,	0x02,	2},														/*�������ʱ��*/
	{18,	0x02,	2},														/*��ʾ�鿴�������ʱ��*/
	{18,	0x02,	2},														/*�޵簴����Ļפ��ʱ��*/
	{17,	0x01,	1},														/*��ʾ����С��λ��*/
	{17,	0x01,	1},														/*��ʾ����С��λ��*/
	{17,	0x01,	1},														/*Һ���٢���������*/
};
#define GV_Str_DI0_DataType_LCDPaTableLen ( sizeof(GV_Str_DI0_DataType_LCDPaTable) / sizeof(Str_DI0_DataType_PaTable) )

const Str_DI0_DataType_PaTable GV_Str_DI0_DataType_VoltageOKPara[] =		/*��ѹ�ϸ��ʲ���*/
{/*	DataType	*/                                                      	
	{C_long_unsigned,	0x02,	2},											/*��ѹ��������*/
	{C_long_unsigned,	0x02,	2},											/*��ѹ��������*/
	{C_long_unsigned,	0x02,	2},											/*��ѹ�ϸ�����*/
	{C_long_unsigned,	0x02,	2},											/*��ѹ�ϸ�����*/
};
#define GV_Str_DI0_DataType_VoltageOKParaLen ( sizeof(GV_Str_DI0_DataType_VoltageOKPara) / sizeof(Str_DI0_DataType_PaTable) )

const Str_DI0_DataType_PaTable GV_Str_DI0_DataType_ZTPaTable[] =			/*ʱ��ʱ����*/
{/*	DataType	*/                                                      	
	{C_unsigned,	0x01,	1},												/*��ʱ����*/
	{C_unsigned,	0x01,	1},												/*��ʱ�α���*/
	{C_unsigned,	0x01,	1},												/*��ʱ����*/
	{C_unsigned,	0x01,	1},												/*������*/
	{C_unsigned,	0x01,	1},												/*����������*/
};
#define GV_Str_DI0_DataType_ZTPaTableLen ( sizeof(GV_Str_DI0_DataType_ZTPaTable) / sizeof(Str_DI0_DataType_PaTable) )

const Str_DI0_DataType_PaTable GV_Str_DI0_DataType_HPaTable[] =				/*�������գ�DI0�˴�ֻ��01��ת��ʱ���⴦��*/
{/*	DataType	*/                                                      	
	{C_date,		0x05,	5},												/*���������е�����*/
	{C_unsigned,	0x01,	1},												/*���������е���ʱ�α��*/

};
#define GV_Str_DI0_DataType_HPaTableLen ( sizeof(GV_Str_DI0_DataType_HPaTable) / sizeof(Str_DI0_DataType_PaTable) )

const Str_DI0_DataType_PaTable GV_Str_DI0_DataType_ZPaTable[] =				/*ʱ����*/
{/*	DataType		*/                                                  	
	{C_unsigned,	0x01,	1},												/*ʱ�����е���*/
	{C_unsigned,	0x01,	1},												/*ʱ�����е���*/
	{C_unsigned,	0x01,	1},												/*ʱ�����е���ʱ�α��*/
};
#define GV_Str_DI0_DataType_ZPaTableLen ( sizeof(GV_Str_DI0_DataType_ZPaTable) / sizeof(Str_DI0_DataType_PaTable) )

const Str_DI0_DataType_PaTable GV_Str_DI0_DataType_AlarmLimitTable[] =		/*���ʱ�*/
{/*	DataType	*/                                                      	
	{C_double_long_unsigned,	4,	4},										/*���������ֵ1*/
	{C_double_long_unsigned,	4,	4},										/*���������ֵ2*/
};
#define GV_Str_DI0_DataType_AlarmLimitLen ( sizeof(GV_Str_DI0_DataType_AlarmLimitTable) / sizeof(Str_DI0_DataType_PaTable) )
const Str_DI0_DataType_PaTable GV_Str_DI0_DataType_OtherLimitTable[] =		/*���ʱ�*/
{/*	DataType	*/                                                      	
	{C_double_long_unsigned,	4,	4},										/*͸֧�����ֵ*/
	{C_double_long_unsigned,	4,	4},										/*�ڻ������ֵ*/
	{C_double_long_unsigned,	4,	4},										/*��բ��������ֵ*/
};
#define GV_Str_DI0_DataType_OtherLimitLen (sizeof(GV_Str_DI0_DataType_OtherLimitTable)/sizeof(Str_DI0_DataType_PaTable))

const Str_DI0_DataType_PaTable GV_Str_DI0_DataType_LadderTable[] =			/*���ݱ�*/
{/*	DataType	*/                                                      	
	{C_array,	6,	4},														/*����ֵ*/
	{C_array,	7,	4},														/*���ݵ��*/
	{C_array,	4,	3},														/*���ݽ�����*/
};
#define GV_Str_DI0_DataType_LadderLen ( sizeof(GV_Str_DI0_DataType_LadderTable) / sizeof(Str_DI0_DataType_PaTable) )

const Str_DI0_DataType_PaTable GV_Str_DI0_DataType_BroadTimePaTable[] =		/*�㲥Уʱ����*/
{/*	DataType	*/                                                      	
	{C_long_unsigned,	2,	2},												/*�㲥Уʱƫ����Сֵ*/
	{C_long_unsigned,	2,	2},												/*�㲥Уʱƫ�����ֵ*/
};
#define GV_Str_DI0_DataType_BroadTimePaLen ( sizeof(GV_Str_DI0_DataType_BroadTimePaTable) / sizeof(Str_DI0_DataType_PaTable) )


const Str_DI0_DataType_PaTable GV_Str_DI0_DataType_FateTable[] =			/*���ʱ�*/
{/*	DataType	*/                                                      	
	{C_double_long_unsigned,	4,	4},										/*����1*/
	{C_double_long_unsigned,	4,	4},										/*����2*/
	{C_double_long_unsigned,	4,	4},										/*����3*/
	{C_double_long_unsigned,	4,	4},										/*����4*/
	{C_double_long_unsigned,	4,	4},										/*����5*/
	{C_double_long_unsigned,	4,	4},										/*����6*/
	{C_double_long_unsigned,	4,	4},										/*����7*/
	{C_double_long_unsigned,	4,	4},										/*����8*/
	{C_double_long_unsigned,	4,	4},										/*����9*/
	{C_double_long_unsigned,	4,	4},										/*����10*/
	{C_double_long_unsigned,	4,	4},										/*����11*/
	{C_double_long_unsigned,	4,	4},										/*����12*/
};
#define GV_Str_DI0_DataType_FateLen ( sizeof(GV_Str_DI0_DataType_FateTable) / sizeof(Str_DI0_DataType_PaTable) )



const Str_DI0_DataType_PaTable GV_Str_DI0_DataType_TPaTable[] =				/*��ʱ�α�DI0�˴�ֻ��01��ת��ʱ���⴦��*/
{/*	DataType	*/                                                      	
	{C_array,		0x8F,	0},                                         	
	{C_structure,	0x83,	0},                                         	
	{C_unsigned,	0x01,	1},												/*��ʱ�α��е�ʱ*/
	{C_unsigned,	0x01,	1},												/*��ʱ�α��еķ�*/
	{C_unsigned,	0x01,	1},												/*��ʱ�α��еķ��ʺ�*/
};
#define GV_Str_DI0_DataType_TPaTableLen ( sizeof(GV_Str_DI0_DataType_TPaTable) / sizeof(Str_DI0_DataType_PaTable) )

const Str_DI0_DataType_PaTable GV_Str_DI0_DataType_SDPaTable[] =			/*ÿ�½����գ�DI0�˴�ֻ��01��ת��ʱ���⴦��*/
{/*	DataType	*/                                                      	
	{C_unsigned,	0x01,	1},												/*�������е���*/
	{C_unsigned,	0x01,	1},												/*�������е�ʱ*/
};
#define GV_Str_DI0_DataType_SDPaTableLen ( sizeof(GV_Str_DI0_DataType_SDPaTable) / sizeof(Str_DI0_DataType_PaTable) )

const Str_DI0_DataType_PaTable GV_Str_DI0_DataType_CommProTable[] =			/*ͨ�Ź�Լ*/
{
	{C_visible_string,	CLMeter_CommPro1,	CLMeter_CommPro1},				/*ͨ�Ź�Լ�б�1*/	
	{C_visible_string,	CLMeter_CommPro2,	CLMeter_CommPro2},				/*ͨ�Ź�Լ�б�2*/	
};

#define GV_Str_DI0_DataType_CommProTableLen ( sizeof(GV_Str_DI0_DataType_CommProTable) / sizeof(Str_DI0_DataType_PaTable) )

const Str_DI0_DataType_PaTable GV_Str_DI0_DataType_FactoryPaTable[] =		/*������Ϣ*/
{/*DataType	*/                                                          	
	{C_visible_string,	0x04,	4},											/*���ұ��*/
	{C_visible_string,	0x04,	4},											/*����汾��*/
	{C_visible_string,	0x06,	6},											/*�����������*/
	{C_visible_string,	0x04,	4},											/*Ӳ���汾��*/
	{C_visible_string,	0x06,	6},											/*Ӳ����������*/
	{C_visible_string,	0x08,	8},											/*������չ��Ϣ*/
};
#define GV_Str_DI0_DataType_FactoryPaTableLen ( sizeof(GV_Str_DI0_DataType_FactoryPaTable) / sizeof(Str_DI0_DataType_PaTable) )

typedef  struct
{
	uchar8	Temp;															/*����*/
	uchar8	DataType;														/*��������*/
}Str_DataType_PaTable;														/*��������/���Զ�Ӧ*/
const Str_DataType_PaTable GV_Str_DataType_4300PaTable[] =					/**/
{/*Temp		DataType */
	{0x02,		C_visible_string},											/*�豸������*/
	{0x03,		C_structure		},											/*�汾��Ϣ*/
	{0x04,		C_date_time_s	},											/*��������*/
	{0x05,		C_array			},											/*���豸�б�*/
	{0x06,		C_array			},											/*֧�ֹ�Լ�б�*/
	{0x07,		C_bool			},											/*��������ϱ�*/
	{0x08,		C_bool			},											/*���������ϱ�*/
	{0x09,		C_bool			},											/*��������վͨ��*/
	{0x0A,		C_array			},											/*�ϱ�ͨ��*/
};
#define GV_Str_DataType_4300PaTableLen ( sizeof(GV_Str_DataType_4300PaTable) / sizeof(Str_DataType_PaTable) )
typedef  struct
{
	ulong32	P_DataType;														/*��������*/
	uchar8	DataTypeNum;													/*�����������*/
	uchar8	DataNum;														/*�ṹ�����������*/
}Str_Num_DataType_PaTable;													/*�����������/�������͵�ӳ��*/
const Str_Num_DataType_PaTable GV_Str_Num_DataType_PaTable[] =				/**/
{/*DataTypeNum	P_DataType	*/
	{(ulong32)(&GV_Str_DI0_DataType_MPPaTable[0]),				C_MeterPosition_DataTypeNum,		GV_Str_DI0_DataType_MPPaTableLen},
	{(ulong32)(&GV_Str_DI0_DataType_LCDPaTable[0]),				C_LCDParamete_DataTypeNum,			GV_Str_DI0_DataType_LCDPaTableLen},
	{(ulong32)(&GV_Str_DI0_DataType_ZTPaTable[0]),				C_ZoneTime_DataTypeNum,				GV_Str_DI0_DataType_ZTPaTableLen},
	{(ulong32)(&GV_Str_DI0_DataType_HPaTable[0]),				C_Holidy_DataTypeNum,				GV_Str_DI0_DataType_HPaTableLen},
	{(ulong32)(&GV_Str_DI0_DataType_ZPaTable[0]),				C_Zone_DataTypeNum,					GV_Str_DI0_DataType_ZPaTableLen},
	{(ulong32)(&GV_Str_DI0_DataType_TPaTable[0]),				C_Time_DataTypeNum,					GV_Str_DI0_DataType_TPaTableLen},
	{(ulong32)(&GV_Str_DI0_DataType_SDPaTable[0]),				C_SettleDay_DataTypeNum,			GV_Str_DI0_DataType_SDPaTableLen},
	{(ulong32)(&GV_Str_DI0_DataType_VoltageOKPara[0]),			C_VoltageOKPara,					GV_Str_DI0_DataType_VoltageOKParaLen},
	{(ulong32)(&GV_Str_DI0_DataType_DisplayNum[0]),				C_DisplayNum_DataTypeNum,			GV_Str_DI0_DataType_DisplayNumLen},
	//{(ulong32)(&GV_Str_DI0_DataType_Display[0]),				C_Display_DataTypeNum,				GV_Str_DI0_DataType_DisplayLen},
	{(ulong32)(&GV_Str_DI0_DataType_AlarmLimitTable[0]),		C_AlarmLimit_DataTypeNum,			GV_Str_DI0_DataType_AlarmLimitLen},
	{(ulong32)(&GV_Str_DI0_DataType_OtherLimitTable[0]),		C_OtherLimit_DataTypeNum,			GV_Str_DI0_DataType_OtherLimitLen},
	{(ulong32)(&GV_Str_DI0_DataType_FateTable[0]),				C_Fate_DataTypeNum,					GV_Str_DI0_DataType_FateLen},
	{(ulong32)(&GV_Str_DI0_DataType_LadderTable[0]),			C_Ladder_DataTypeNum,				GV_Str_DI0_DataType_LadderLen},
	{(ulong32)(&GV_Str_DI0_DataType_BroadTimePaTable[0]),		C_BroadTime_DataTypeNum,			GV_Str_DI0_DataType_BroadTimePaLen},
	{(ulong32)(&GV_Str_DI0_DataType_CommProTable[0]),			C_Meter_CommProNum,					GV_Str_DI0_DataType_CommProTableLen},

};
#define GV_Str_Num_DataType_PaTableLen ( sizeof(GV_Str_Num_DataType_PaTable) / sizeof(Str_Num_DataType_PaTable) )

/*****************************�¼���¼������������***********************************************/
typedef  struct
{
	uchar8	DataTpye698;													/*698��������*/
	uchar8	Len645;															/*645���ݳ���*/
}Str_EventPara_Type;														/*�¼���¼���ò����ṹ��*/

const	Str_EventPara_Type	LossVol_ParaTable[4] =
{
	{ C_long_unsigned,	2},													/*��ѹ��������*/
	{ C_long_unsigned,	2},													/*��ѹ�ָ�����*/
	{ C_double_long,	4},													/*������������*/
	{ C_unsigned,		1},													/*�ж���ʱʱ��*/
};																			/*���ܱ�ʧѹ�¼�*/

const	Str_EventPara_Type	AllLossVol_ParaTable[1] =
{
	{C_unsigned,		1},													/*�ж���ʱʱ��*/
};																			/*���ܱ�ȫʧѹ�¼�*/
const	Str_EventPara_Type	LowVol_ParaTable[2] =
{
	{C_long_unsigned,	2},													/*��ѹ��������*/
	{C_unsigned,		1},													/*�ж���ʱʱ��*/
};																			/*���ܱ�Ƿѹ�¼�*/

const	Str_EventPara_Type	OverVol_ParaTable[2]=
{
	{C_long_unsigned,	2},													/*��ѹ��������*/
	{C_unsigned,		1},													/*�ж���ʱʱ��*/
};																			/*���ܱ��ѹ�¼�*/

const	Str_EventPara_Type	BreakVol_ParaTable[3] =
{
	{C_long_unsigned,	2},													/*��ѹ��������*/
	{C_double_long,		4},													/*������������*/
	{C_unsigned,		1},													/*�ж���ʱʱ��*/
};																			/*���ܶ����¼�*/
const	Str_EventPara_Type	PowerOff_ParaTable[1] =
{
	{C_unsigned,			1},												/*�ж���ʱʱ��*/
};																			/*�����¼�*/
const	Str_EventPara_Type	ReversedVoltage_ParaTable[1] =
{
	{C_unsigned,			1},												/*�ж���ʱʱ��*/
};																			/*��ѹ�������¼�*/
const	Str_EventPara_Type	ReversedCurrent_ParaTable[1] =
{
	{C_unsigned,			1},												/*�ж���ʱʱ��*/
};																			/*�����������¼�*/
const	Str_EventPara_Type	LossCurr_ParaTable[4] =
{
	{C_long_unsigned,	2},													/*��ѹ��������*/
	{C_double_long,		4},													/*������������*/
	{C_double_long,		4},													/*�����ָ�����*/
	{C_unsigned,		1},													/*�ж���ʱʱ��*/
};																			/*���ܱ�ʧ���¼�*/

const	Str_EventPara_Type	OverCurr_ParaTable[2] =
{
	{C_double_long,	4},														/*������������*/
	{C_unsigned,	1},														/*�ж���ʱʱ��*/
};																			/*���ܱ�����¼�*/

const	Str_EventPara_Type	BreakCurr_ParaTable[3] =
{
	{C_long_unsigned,	2},													/*��ѹ��������*/
	{C_double_long,		4},													/*������������*/
	{C_unsigned,		1},													/*�ж���ʱʱ��*/
};																			/*���ܱ�����¼�*/

const	Str_EventPara_Type	OverLo_ParaTable[2]=
{
	{C_double_long,	4},														/*�й����ʴ�������*/
	{C_unsigned,	1},														/*�ж���ʱʱ��*/
};																			/*���ܱ�����¼�*/

const	Str_EventPara_Type	PosDeOver_ParaTable[2] =
{
	{C_double_long_unsigned,	4},											/*�й����ʴ�������*/
	{C_unsigned,				1},											/*�ж���ʱʱ��*/
};																			/*���ܱ������й����������¼�*/

const	Str_EventPara_Type	ReDeOver_ParaTable[2] =
{
	{C_double_long_unsigned,	4},											/*�޹����ʴ�������*/
	{C_unsigned,				1},											/*�ж���ʱʱ��*/

};

const	Str_EventPara_Type	TrendRev_ParaTable[2] =
{
	{C_double_long,	4},														/*�й����ʴ�������*/
	{C_unsigned,	1},														/*�ж���ʱʱ��*/
};																			/*���ܱ��������¼�*/

const	Str_EventPara_Type	PowerRev_ParaTable[2] =
{
	{C_double_long,	4},														/*�й����ʴ�������*/
	{C_unsigned,	1},														/*�ж���ʱʱ��*/
};																			/*���ܱ��ʷ����¼�*/
const	Str_EventPara_Type	NoBalVol_ParaTable[2] =
{
	{C_long,		2},														/*��ƽ������ֵ*/
	{C_unsigned,	1},														/*�ж���ʱʱ��*/
};																			/*���ܱ��ѹ��ƽ���¼�*/

const	Str_EventPara_Type	NoBalCurr_ParaTable[2] =
{
	{C_long,		2},														/*��ƽ������ֵ*/
	{C_unsigned,	1},														/*�ж���ʱʱ��*/
};																			/*���ܱ������ƽ���¼�*/

const	Str_EventPara_Type	SevNoBalCurr_ParaTable[2] =
{
	{C_long,		2},														/*��ƽ������ֵ*/
	{C_unsigned,	1},														/*�ж���ʱʱ��*/
};																			/*���ܱ�������ز�ƽ���¼�*/

const	Str_EventPara_Type	PFactorTOver_ParaTable[2] =
{
	{C_long,		2},														/*�������������޷�ֵ*/
	{C_unsigned,	1},														/*�ж���ʱʱ��*/
};																			/*���ܱ��������������¼�*/

const	Str_EventPara_Type	NeutralCurrentAbnormal_ParaTable[3] =
{
	{C_double_long,		4},													/*��������������ֵ*/
	{C_long_unsigned,	2},													/*���ߵ�����ƽ����ֵ*/
	{C_unsigned,		1},													/*�ж���ʱʱ��*/
                            												
};																			/*���ܱ����ߵ����쳣�¼�*/

/*****************************�¼���¼�������***********************************************/        

/*class7 ��ǰ��¼��ṹ��*/
const	Str_DI0_DataType_PaTable	Event_Class7_CurrentRecTable[4] =
{	/*	datatype					data698	data645len	*/
	{C_NULL,					0x01,		1},
	{C_structure,				0x02,		0},
	{C_double_long_unsigned,	0x04,		4},
	{C_double_long_unsigned,	0x04,		4}
};
/*class24 ��ǰ��¼��ṹ��*/
const	Str_DI0_DataType_PaTable	Event_Class24_CurrentRecTable[2] =
{	/*di1, 	datatype					data698	data645len	*/
	{C_double_long_unsigned,	0x04,		4},
	{C_double_long_unsigned,	0x04,		4}
};
/*class7 ʱ��״̬��¼��ṹ��*/
const	Str_DI0_DataType_PaTable	Event_Class7_10AttriTable[4]=
{	/*datatype					data698	data645len	*/
	{C_NULL,				0x01,		1},
	{C_structure,			0x02,		0},
	{C_date_time_s,			0x54,		7},									/*�¼�����ʱ��*/
	{C_date_time_s,			0x55,		7}									/*�¼�����ʱ��*/
};
/*class24 ʱ��״̬��¼��ṹ��*/
const	Str_DI0_DataType_PaTable	Event_Class24_14AttriTable[2]=
{	/*di1, 	datatype					data698	data645len	*/
	{C_date_time_s,			0x54,		7},									/*�¼�����ʱ��*/
	{C_date_time_s,			0x55,		7}									/*�¼�����ʱ��*/
};

/******************************�����������**********************************************/        

/*1:˲ʱ���ᡢ�½��㡢ʱ�����л�����ʱ�α��л������ʵ���л��������л�*/
/*PS:1�����Ӷ�����޹���������ѹ���������й����ʡ�����������ʱ��д*/
/*   2���ն����ʣ������������͸֧����*/
#define C_Bit0 0x01
#define C_Bit1 0x02
#define C_Bit2 0x04
#define C_Bit3 0x08
#define C_Bit4 0x10
#define C_Bit5 0x20
#define C_Bit6 0x40
#define C_Bit7 0x80


typedef struct
{
	uchar8	OIB;															/*OIB*/
	uchar8	TypeClass;														/*bit7  bit6��bit7=0��ʾ645��ӦdiΪDI3��1��ʾdi2di1��bit6=1��ʾDi2Di1��������Ч*/
	uchar8	ConfParaNum;													/*���ýṹ�����*/
	uchar8	RelatedOINo;													/*�������������б�*/
	ulong32	ConfParaTableAddr;												/*���ò����ṹ���׵�ַ*/
	ulong32	RecordNum;          											
	ulong32	RelatedOAD;														/*��������OAD*/
	ulong32	RelatedOAD_T;													/*�����������*/
}Str_Event_OIB1;

/*RelatedOINo==0xFF��ʾ,û�й������ԣ���������� EventAttriNO[11]*/
const Str_Event_OIB1	Event_OIBTable[] =
{/*		OIB							TpyeClass					ParaNum	RelatedOINo	ParameterTable						RecordNum   			RelatedOAD					RelatedOAD_T	*/
	{CLoss_Vol_OIB,					C_SplitPhaseEvent_Class,		4,		0,		(ulong32)LossVol_ParaTable,					CLossA_Vol_Degree,				CLoss_Vol_OADTab,				CLoss_Vol_OADTabLen},				/*698-ʧѹ*/
	{CLow_Vol_OIB,					C_SplitPhaseEvent_Class,		2,		0,		(ulong32)LowVol_ParaTable,					CLowA_Vol_Degree,				CLow_Vol_OADTab,				CLow_Vol_OADTabLen},				/*698-Ƿѹ*/
	{COver_Vol_OIB,					C_SplitPhaseEvent_Class,		2,		0,		(ulong32)OverVol_ParaTable,					COverA_Vol_Degree,				COver_Vol_OADTab,				COver_Vol_OADTabLen},				/*698-��ѹ*/
	{CBreak_Vol_OIB,				C_SplitPhaseEvent_Class,		3,		0,		(ulong32)BreakVol_ParaTable,				CBreakA_Vol_Degree,				CBreak_Vol_OADTab,				CBreak_Vol_OADTabLen},				/*698-����*/
	{CLoss_Curr_OIB,				C_SplitPhaseEvent_Class,		4,		1,		(ulong32)LossCurr_ParaTable,				CLossA_Curr_Degree,				CLoss_Curr_OADTab,				CLoss_Curr_OADTabLen},				/*698-ʧ��*/
	{COver_Curr_OIB,				C_SplitPhaseEvent_Class,		2,		1,		(ulong32)OverCurr_ParaTable,				COverA_Curr_Degree,				COver_Curr_OADTab,				COver_Curr_OADTabLen},				/*698-����*/
	{CBreak_Curr_OIB,				C_SplitPhaseEvent_Class,		3,		1,		(ulong32)BreakCurr_ParaTable,				CBreakA_Curr_Degree,			CBreak_Curr_OADTab,				CBreak_Curr_OADTabLen},				/*698-����*/
	{CTrend_Rev_OIB,				C_SplitPhaseEvent_Class,		2,		2,		(ulong32)TrendRev_ParaTable,				CPowerT_Rev_Degree,				CPower_Rev_OADTab,				CPower_Rev_OADTabLen},				/*698-��������*/
	{COver_Lo_OIB,					C_SplitPhaseEvent_Class,		2,		2,		(ulong32)OverLo_ParaTable,					COverA_Lo_Degree,				COver_Lo_OADTab,				COver_Lo_OADTabLen},				/*698-����*/
	{CPos_De_Over_OIB,				C_Event_Class,					2,		20,		(ulong32)PosDeOver_ParaTable,				CPos_Ac_De_Over_Degree,			CPos_Ac_De_Over_OADTab,			CPos_Ac_De_Over_OADTabLen},			/*698-���ܱ������й����������¼�*/
	{CRe_De_Over_OIB,				C_Event_Class,					2,		21,		(ulong32)PosDeOver_ParaTable,				CRev_Ac_De_Over_Degree,			CRev_Ac_De_Over_OADTab,			CRev_Ac_De_Over_OADTabLen},			/*698-���ܱ����й����������¼�*/
	{CRe_ReDe_Over_OIB,				C_SplitPhaseEvent_Class,		2,		22,		(ulong32)ReDeOver_ParaTable,				CQua1_Re_De_Over_Degree,		CQua_Re_De_Over_OADTab,			CQua_Re_De_Over_OADTabLen},			/*698-���ܱ��޹����������¼�*/
	{CPFactorT_Over_OIB,			C_SplitPhaseEvent_Class,		2,		10,		(ulong32)PFactorTOver_ParaTable,			CPFactorT_Over_Degree,			CPFactorT_Over_OADTab,			CPFactorT_Over_OADTabLen},			/*698-���ܱ��������������¼�*/
	{CAll_Loss_Vol_OIB,				C_Event_Class,					1,		19,		0,											CAll_Loss_Vol_Degree,			CAll_Loss_Vol_OADTab,			CAll_Loss_Vol_OADTabLen},			/*698-���ܱ�ȫʧѹ�¼�*/
	{CAux_Pow_Down_OIB,				C_Event_Class,					1,		18,		0,											CAux_Pow_Down_Degree,			CAux_Pow_Down_OADTab,			CAux_Pow_Down_OADTabLen},			/*698-���ܱ�����Դʧ���¼�*/
	{CRevPS_Vol_OIB,				C_Event_Class,					1,		29,		(ulong32)ReversedVoltage_ParaTable,			CRevPS_Vol_Degree,				CRevPS_Vol_OADTab,				CRevPS_Vol_OADTabLen},				/*698-���ܱ��ѹ�������¼�*/
	{CRevPS_Curr_OIB,				C_Event_Class,					1,		29,		(ulong32)ReversedCurrent_ParaTable,			CRevPS_Curr_Degree,				CRevPS_Curr_OADTab,				CRevPS_Curr_OADTabLen},				/*698-���ܱ�����������¼�*/
	{CPow_Down_OIB,					C_Event_Class,					1,		18,		0,											CPow_Down_Degree,				CPow_Down_OADTab,				CPow_Down_OADTabLen},				/*698-���ܱ�����¼�*/
	{CProgram_OIB,					C_Event_Class,					0,		28,		0,											CProgram_Degree,				CProgram_OADTab,				CProgram_OADTabLen},				/*698-���ܱ����¼�*/
	{CTol_Clear_OIB,				C_Event_Class,					0,		8,		0,											CTol_Clear_Degree,				CTol_Clear_OADTab,				CTol_Clear_OADTabLen},				/*698-���ܱ������¼�*/
	{CDe_Clear_OIB,					C_Event_Class,					0,		9,		0,											CDe_Clear_Degree,				CDe_Clear_OADTab,				CDe_Clear_OADTabLen},				/*698-���ܱ����������¼�*/
	{CEven_Clear_OIB,				C_Event_Class,					0,		28,		0,											CEven_Clear_Degree,				CEven_Clear_OADTab,				CEven_Clear_OADTabLen},				/*698-���ܱ��¼������¼�*/
	{CAdjTime_OIB,					C_Event_Class,					0,		11,		0,											CAdjTime_Degree,				CAdjTime_OADTab,				CAdjTime_OADTabLen},				/*698-���ܱ�Уʱ�¼�*/
	{CProgPT_OIB,					C_Event_Class,					0,		12,		0,											CProgPT_Degree,					CProgPT_OADTab,					CProgPT_OADTabLen},					/*698-���ܱ�ʱ�α����¼�*/
	{CProgTZ_OIB,					C_Event_Class,					0,		13,		0,											CProgTZ_Degree,					CProgTZ_OADTab,					CProgTZ_OADTabLen},					/*698-���ܱ�ʱ�������¼�*/
	{CProgWRe_OIB,					C_Event_Class,					0,		14,		0,											CProgWRe_Degree,				CProgWRe_OADTab,				CProgWRe_OADTabLen},				/*698-���ܱ������ձ���¼�*/
	{CProgSettD_OIB,				C_Event_Class,					0,		15,		0,											CProgSettD_Degree,				CProgSettD_OADTab,				CProgSettD_OADTabLen},				/*698-���ܱ�����ձ���¼�*/
	{COpenW_OIB,					C_Event_Class,					0,		4,		0,											COpenW_Degree,					COpenW_OADTab,					COpenW_OADTabLen},					/*698-���ܱ����¼�*/
	{COpenCW_OIB,					C_Event_Class,					0,		4,		0,											COpenCW_Degree,					COpenCW_OADTab,					COpenCW_OADTabLen},					/*698-���ܱ���ť���¼�*/
	{CNoBal_Vol_OIB,				C_Event_Class,					2,		3,		(ulong32)NoBalVol_ParaTable,				CNoBal_Vol_Degree,				CNoBal_Vol_OADTab,				CNoBal_Vol_OADTabLen},				/*698-���ܱ��ѹ��ƽ���¼�*/
	{CNoBal_Curr_OIB,				C_Event_Class,					2,		3,		(ulong32)NoBalCurr_ParaTable,				CNoBal_Curr_Degree,				CNoBal_Curr_OADTab,				CNoBal_Curr_OADTabLen},				/*698-���ܱ������ƽ���¼�*/
	{CRelayOpen_OIB,				C_Event_Class,					0,		5,		0,											CRelayOpen_Degree,				CRelayOpen_OADTab,				CRelayOpen_OADTabLen},				/*698-���ܱ���բ�¼�*/
	{CRelayClose_OIB,				C_Event_Class,					0,		5,		0,											CRelayClose_Degree,				CRelayClose_OADTab,				CRelayClose_OADTabLen},				/*698-���ܱ��բ�¼�*/
	{CProgHol_OIB,					C_Event_Class,					0,		28,		0,											CProgHol_Degree,				CProgHol_OADTab,				CProgHol_OADTabLen},				/*698-���ܱ�ڼ��ձ���¼�*/
	{CProgAcC_OIB,					C_Event_Class,					0,		16,		0,											CProgAcC_Degree,				CProgAcC_OADTab,				CProgAcC_OADTabLen},				/*698-���ܱ��й���Ϸ�ʽ����¼�*/
	{CProgReC_OIB,					C_Event_Class,					0,		17,		0,											CProgReC_Degree,				CProgReC_OADTab,				CProgReC_OADTabLen},				/*698-���ܱ��޹���Ϸ�ʽ����¼�*/
	{CProgTPara_OIB,				C_Event_Class,					0,		28,		0,											CProgTPara_Degree,				CProgTPara_OADTab,				CProgTPara_OADTabLen},				/*698-���ܱ���ʲ��������¼�*/
	{CProgLad_OIB,					C_Event_Class,					0,		28,		0,											CProgLad_Degree,				CProgLad_OADTab,				CProgLad_OADTabLen},				/*698-���ܱ���ݱ����¼�*/
	{CKey_Update_OIB,				C_Event_Class,					0,		27,		0,											CProgKD_Degree,					CProgKD_OADTab,					CProgKD_OADTabLen},					/*698-���ܱ���Կ�����¼�*/
	{CAbnorC_OIB,					C_Event_Class,					0,		28,		0,											CAbnorC_Degree,					CAbnorC_OADTab,					CAbnorC_OADTabLen},					/*698-���ܱ��쳣�忨�¼�*/
	{CBuyCurr_OIB,					C_Event_Class,					0,		28,		0,											CBuyCurr_Degree,				CBuyCurr_OADTab,				CBuyCurr_OADTabLen},				/*698-���ܱ����¼�*/
	{CReturn_M_OIB,					C_Event_Class,					0,		28,		0,											CReturn_M_Degree,				CReturn_M_OADTab,				CReturn_M_OADTabLen},				/*698-���ܱ��˷��¼�*/
	{CConM_OIB,						C_Event_Class,					0,		6,		0,											CConM_Degree,					CConM_OADTab,					CConM_OADTabLen	},					/*698-���ܱ�㶨�ų������¼�*/
	{CRelayFa_OIB,					C_Event_Class,					0,		26,		0,											CRelayFa_Degree,				CRelayFa_OADTab,				CRelayFa_OADTabLen},				/*698-���ܱ��ɿ��������¼�*/
	{CPowerFa_OIB,					C_Event_Class,					0,		7,		0,											CPowerFa_Degree,				CPowerFa_OADTab,				CPowerFa_OADTabLen},				/*698-���ܱ��Դ�쳣�¼�*/
	{CSevNoBal_Curr_OIB,			C_Event_Class,					2,		3,		(ulong32)SevNoBalCurr_ParaTable,			CSevNoBal_Curr_Degree,			CSevNoBal_Curr_OADTab,			CSevNoBal_Curr_OADTabLen},			/*698-���ܱ�������ز�ƽ���¼�*/
	{CClock_FaultState_OIB,			C_Event_Class,					1,		28,		0,											CClockFa_Degree,				CClockFa_OADTab,				CClockFa_OADTabLen},				/*698-���ܱ�ʱ�ӹ����¼�*/
	{CMeteringChipFault_OIB,		C_Event_Class,					1,		28,		(ulong32)ReversedVoltage_ParaTable,			CMeterFa_Degree,				CMeterFa_OADTab,				CMeterFa_OADTabLen},				/*698-���ܱ����оƬ�����¼�*/
	{CBroadcastTime_OIB,			C_Event_Class,					0,		11,		0,											CBroadcastTime_Degree,			CBroadcastTime_OADTab,			CBroadcastTime_OADTabLen},			/*698-���ܱ�㲥Уʱ�¼�*/
	{CNeutralCurrentAbnormal_OIB,	C_Event_Class,					3,		2,		(ulong32)NeutralCurrentAbnormal_ParaTable,	CNeutralCurrentAbnormal_Degree,	CNeutralCurrentAbnormal_OADTab,	CNeutralCurrentAbnormal_OADTabLen},	/*698-���ܱ����ߵ����쳣�¼�*/
};
#define	C_Event_OIBTableLen	( sizeof(Event_OIBTable) / sizeof(Event_OIBTable[0]) )


const	Str_DI0_DataType_PaTable	PosDeOver_SpecificData[] =
{
	{C_double_long_unsigned,	4,	CL_double_long_unsigned},
	{C_date_time_s,				8,	CL_date_time_s},
};
#define	PosDeOver_SpecificDataLen ( sizeof(PosDeOver_SpecificData) / sizeof(PosDeOver_SpecificData[0]) )

const	Str_DI0_DataType_PaTable	Program_SpecificData[]=
{
	{C_array,	0,	0},
	{0x01,		0,	0},
	{C_OAD,		CL_OAD,		CL_OAD},
};
#define	Program_SpecificDataLen ( sizeof(Program_SpecificData) / sizeof(Program_SpecificData[0]) )

const	Str_DI0_DataType_PaTable	Even_Clear_SpecificData[] =
{
	{C_array,	0,	0},
	{0x01,		0,	0},
	{C_OMD,		CL_OMD,	CL_OMD},
};
#define	Even_Clear_SpecificDataLen ( sizeof(Even_Clear_SpecificData) / sizeof(Even_Clear_SpecificData[0]) )

const	Str_DI0_DataType_PaTable	ProgPT_SpecificData[] =
{
	{C_OAD,			CL_OAD,			CL_OAD},
	{C_array,		0,				0},
	{14,			0,				0},
	{C_structure,	0,				0},
	{3,				0,				0},
	{C_unsigned,	CL_unsigned,	CL_unsigned},
	{C_unsigned,	CL_unsigned,	CL_unsigned},
	{C_unsigned,	CL_unsigned,	CL_unsigned},
};
#define	ProgPT_SpecificDataLen ( sizeof(ProgPT_SpecificData) / sizeof(ProgPT_SpecificData[0]) )

const	Str_DI0_DataType_PaTable	ProgHol_SpecificData[] =
{
	{C_OAD,			CL_OAD,			CL_OAD},
	{C_structure,	0,				0},
	{2,				0,				0},
	{C_date,		CL_date,		CL_date},
	{C_unsigned,	CL_unsigned,	CL_unsigned},
};
#define	ProgHol_SpecificDataLen ( sizeof(ProgHol_SpecificData)/sizeof(ProgHol_SpecificData[0]) )

const	Str_DI0_DataType_PaTable	ProgReturnMoney_SpecificData[] =
{
	{C_double_long_unsigned,			CL_double_long_unsigned,	CL_double_long_unsigned},
};
#define	ProgReturnMoney_SpecificDataLen ( sizeof(ProgReturnMoney_SpecificData) / sizeof(ProgReturnMoney_SpecificData[0]) )
const	Str_DI0_DataType_PaTable	ProgErrCard_SpecificData[]=
{
	{C_octet_string,	8,					8},
	{C_unsigned,		CL_unsigned,		CL_unsigned},
	{C_octet_string,	5,					5},
	{C_long_unsigned,	CL_long_unsigned,	CL_long_unsigned},
};
#define	ProgErrCard_SpecificDataLen ( sizeof(ProgErrCard_SpecificData) / sizeof(ProgErrCard_SpecificData[0]) )


const	Str_DI0_DataType_PaTable	ProgLadder_SpecificData[] =
{
	{C_structure,				0,	0},
	{3,							0,	0},
	{C_array,					0,	0},
	{6,							0,	0},
	{C_double_long_unsigned,	CL_double_long_unsigned,	CL_double_long_unsigned},
	{C_double_long_unsigned,	CL_double_long_unsigned,	CL_double_long_unsigned},
	{C_double_long_unsigned,	CL_double_long_unsigned,	CL_double_long_unsigned},
	{C_double_long_unsigned,	CL_double_long_unsigned,	CL_double_long_unsigned},
	{C_double_long_unsigned,	CL_double_long_unsigned,	CL_double_long_unsigned},
	{C_double_long_unsigned,	CL_double_long_unsigned,	CL_double_long_unsigned},
	{C_array,					0,	0},
	{7,							0,	0},
	{C_double_long_unsigned,	CL_double_long_unsigned,	CL_double_long_unsigned},
	{C_double_long_unsigned,	CL_double_long_unsigned,	CL_double_long_unsigned},
	{C_double_long_unsigned,	CL_double_long_unsigned,	CL_double_long_unsigned},
	{C_double_long_unsigned,	CL_double_long_unsigned,	CL_double_long_unsigned},
	{C_double_long_unsigned,	CL_double_long_unsigned,	CL_double_long_unsigned},
	{C_double_long_unsigned,	CL_double_long_unsigned,	CL_double_long_unsigned},
	{C_double_long_unsigned,	CL_double_long_unsigned,	CL_double_long_unsigned},
	{C_array,					0,	0},
	{4,							0,	0},
	{C_structure,				0,	0},
	{3,							0,	0},
	{C_unsigned,				CL_unsigned,	CL_unsigned},
	{C_unsigned,				CL_unsigned,	CL_unsigned},
	{C_unsigned,				CL_unsigned,	CL_unsigned},
	{C_structure,				0,	0},
	{3,							0,	0},
	{C_unsigned,				CL_unsigned,	CL_unsigned},
	{C_unsigned,				CL_unsigned,	CL_unsigned},
	{C_unsigned,				CL_unsigned,	CL_unsigned},
	{C_structure,				0,	0},
	{3,							0,	0},
	{C_unsigned,				CL_unsigned,	CL_unsigned},
	{C_unsigned,				CL_unsigned,	CL_unsigned},
	{C_unsigned,				CL_unsigned,	CL_unsigned},
	{C_structure,				0,	0},
	{3,							0,	0},
	{C_unsigned,				CL_unsigned,	CL_unsigned},
	{C_unsigned,				CL_unsigned,	CL_unsigned},
	{C_unsigned,				CL_unsigned,	CL_unsigned},
};
#define	ProgLadder_SpecificDataLen ( sizeof(ProgLadder_SpecificData) / sizeof(ProgLadder_SpecificData[0]) )

typedef struct
{
	ulong32	SpecificDataTableAddr;								/*�������ݽṹ���׵�ַ*/
	ulong32	SpecificOADTableAddr;								/*��������OAD�׵�ַ*/
	uchar8	OIB;												/*OIB*/
	uchar8	TableLenth;
	uchar8	OADTableLenth;
}Str_Event_SpecificData;
#if 1
typedef struct
{
	ulong32	SpecialOAD;											/*�������ݽṹ���׵�ַ*/
	uchar8	DataLen;											/*���ݳ���*/
	uchar8  LineNo;												/*�ڱ����е��к�*/
}Str_Event_SingleSpecificData;

const Str_Event_SingleSpecificData PosDeOver_SpecificOAD[2] =				/*���������¼���¼��Ԫ*/
{
	C_OverDemandRenew_Demand,			CLCurr_AcDemand,		0,	
	C_OverDemandRenew_HapTime,			CL_date_time_s,			1,
};
const Str_Event_SingleSpecificData Program_SpecificOAD[1] =					/*����¼���¼��Ԫ*/
{
	CProgram_OADList,					CL_OAD * CProgOADNum,	0
};
const Str_Event_SingleSpecificData Even_Clear_SpecificOAD[1] =				/*ʱ�α����¼���¼��Ԫ*/
{
	CEventClear_OADList,				CL_OAD,					0
};
const Str_Event_SingleSpecificData ProgPT_SpecificOAD[2] =					/*ʱ�α����¼���¼��Ԫ*/
{
	CRWTimeTable_OAD,					CL_OAD,					0,
	CRWTimeTable_ForwardData,			CLFirst_TZone_1PT_Data,	1
};
const Str_Event_SingleSpecificData ProgHol_SpecificOAD[2] =					/*�ڼ��ձ���¼���¼��Ԫ*/
{
	C_RWHoliday_OAD,					CL_OAD,					0,
	CRWHoliday_ForwardData,				CLHolidy_PT_Table1,		1
};
const Str_Event_SingleSpecificData ProgReturnMoney_SpecificOAD[1] =			/*�˷��¼���¼��Ԫ*/
{
	CReturnMoney_Charge,				CLAlam1_Money,			0
};
const Str_Event_SingleSpecificData ProgErrCard_SpecificOAD[4] =				/*�쳣�忨�¼���¼��Ԫ*/
{
	CAbnormalCard_CareNo,				CLAbnormalCard_CareNo,				0,
	CAbnormalCard_ErrorStatus,			CLAbnormalCard_ErrorStatus,			1,
	CAbnormalCard_OrderHead,			CLAbnormalCard_OrderHead,			2,
	CAbnormalCard_ErrorRespondStatus,	CLAbnormalCard_ErrorRespondStatus,	3
};
#endif

const Str_Event_SpecificData	Event_SpecificData[] =
{/* ParameterTable				        	 ParameterOAD				        	OIB															*/
	{(ulong32)PosDeOver_SpecificData,		(ulong32)PosDeOver_SpecificOAD,			CPos_De_Over_OIB,	PosDeOver_SpecificDataLen,			0x02},	/*698-���ܱ������й����������¼�*/
	{(ulong32)PosDeOver_SpecificData,		(ulong32)PosDeOver_SpecificOAD,			CRe_De_Over_OIB,	PosDeOver_SpecificDataLen,			0x02},	/*698-���ܱ����й����������¼�*/
	{(ulong32)PosDeOver_SpecificData,		(ulong32)PosDeOver_SpecificOAD,			CRe_ReDe_Over_OIB,	PosDeOver_SpecificDataLen,			0x02},	/*698-���ܱ��޹����������¼�*/
	{(ulong32)Program_SpecificData,			(ulong32)Program_SpecificOAD,			CProgram_OIB,		Program_SpecificDataLen	,			1},		/*698-���ܱ����¼�*/
	{(ulong32)Even_Clear_SpecificData,		(ulong32)Even_Clear_SpecificOAD,		CEven_Clear_OIB,	Even_Clear_SpecificDataLen,			1},		/*698-���ܱ������¼�*/
	{(ulong32)ProgPT_SpecificData,			(ulong32)ProgPT_SpecificOAD,			CProgPT_OIB,		ProgPT_SpecificDataLen	,			2},		/*698-���ܱ�ʱ�α����¼�*/
	{(ulong32)ProgHol_SpecificData,			(ulong32)ProgHol_SpecificOAD,			CProgHol_OIB,		ProgHol_SpecificDataLen	,			2},		/*698-���ܱ�ڼ��ձ���¼�*/
	{(ulong32)ProgReturnMoney_SpecificData,	(ulong32)ProgReturnMoney_SpecificOAD,	CReturn_M_OIB,		ProgReturnMoney_SpecificDataLen	,	1},		/*698-�˷��¼�*/
	{(ulong32)ProgErrCard_SpecificData,		(ulong32)ProgErrCard_SpecificOAD,		CAbnorC_OIB,		ProgErrCard_SpecificDataLen	,		4},		/*698-�쳣�忨�¼�*/

};
#define	C_Event_SpecificDataLen ( sizeof(Event_SpecificData) / sizeof(Event_SpecificData[0]) )

typedef struct
{
	ulong32		RelatedOAD;										/*��������OAD*/
	ulong32		RelatedOAD_T;									/*�������󶳽����ڼ�����*/
	ulong32		RelatedOADAddr;									/*��������OAD��ַ*/
	ushort16	MaxFrozenNum;									/*����¼����*/
	uchar8		RelatedOAD_Num;									/*��������Ĭ�ϸ���*/
	uchar8		OIB;											/*�����¼OAD*/
}Str_Event_OIB2;



typedef struct
{
	ulong32 V_OADFlagL;
	ulong32 V_OADFlagH;
	ushort16 V_CRC;
}Str_RelatedOAD_Type;


/*RelatedOINo==0xFF��ʾ,û��*/
const ulong32 C_RelatedOAD_Immid_Init[] =						/*˲ʱ���ᡢԼ������*/
{
	0x00000001,													/*��������*/
	0x00100200,													/*�����й������ܼ�����*/
	0x00200200,													/*�����й������ܼ�����*/
	0x00300200,													/*����޹�1�����ܼ�����*/
	0x00400200,													/*����޹�2�����ܼ�����*/
	0x00500200,													/*1�����޹������ܼ�����*/
	0x00600200,													/*2�����޹������ܼ�����*/
	0x00700200,													/*3�����޹������ܼ�����*/
	0x00800200,													/*4�����޹������ܼ�����*/
	0x10100200,													/*�����й���������ܼ�����*/
	0x10200200,													/*�����й���������ܼ�����*/
	0x20040200,													/*�й����ʺ��༰����*/
	0x20050200,													/*�޹����ʺ��༰����*/
};
#define	C_RelatedOAD_Immid_InitLen       ( sizeof(C_RelatedOAD_Immid_Init) / sizeof(C_RelatedOAD_Immid_Init[0]) )

const ulong32 C_RelatedOAD_Min_Init[] =							/*���Ӷ���*/
{
	0x0000000F,													/*��������*/
	0x00100201,													/*�����й�������*/
	0x00200201,													/*�����й�������*/
	0x00500201,													/*1�����޹�������*/
	0x00600201,													/*2�����޹�������*/
	0x00700201,													/*3�����޹�������*/
	0x00800201,													/*4�����޹�������*/
	0x20170200,													/*�����й�����*/
	0x20180200,													/*�����й�����*/
	0x20000200,													/*��ѹ����*/
	0x20010200,													/*��������*/
	0x20040200,													/*�й����ʺ��༰����*/
	0x200A0200,													/*�����������༰����*/
};
#define	C_RelatedOAD_Min_InitLen       ( sizeof(C_RelatedOAD_Min_Init) / sizeof(C_RelatedOAD_Min_Init[0]) )

const ulong32 C_RelatedOAD_Hour_Init[] =						/*Сʱ����*/
{
	0x00000001,													/*��������*/
	0x00100201,													/*�����й�������*/
	0x00200201,													/*�����й�������*/
};
#define	C_RelatedOAD_Hour_InitLen       ( sizeof(C_RelatedOAD_Hour_Init) / sizeof(C_RelatedOAD_Hour_Init[0]) )

const ulong32 C_RelatedOAD_Day_Init[]=							/*�ն���*/
{
	0x00000001,													/*��������*/
	0x00100200,													/*�����й������ܼ�����*/
	0x00200200,													/*�����й������ܼ�����*/
	0x00300200,													/*����޹�1�����ܼ�����*/
	0x00400200,													/*����޹�2�����ܼ�����*/
	0x00500200,													/*1�����޹������ܼ�����*/
	0x00600200,													/*2�����޹������ܼ�����*/
	0x00700200,													/*3�����޹������ܼ�����*/
	0x00800200,													/*4�����޹������ܼ�����*/
	0x10100200,													/*�����й���������ܼ�����*/
	0x10200200,													/*�����й���������ܼ�����*/
	0x20040200,													/*�й����ʺ��༰����*/
	0x20050200,													/*�޹����ʺ��༰����*/
	0x202C0200,													/*ʣ����������*/
	0x202D0200,													/*͸֧���*/
               													
	0x21310201,													/*A���յ�ѹ�ϸ���*/
	0x21320201,													/*B���յ�ѹ�ϸ���*/
	0x21330201,													/*C���յ�ѹ�ϸ���*/
};
#define	C_RelatedOAD_Day_InitLen       ( sizeof(C_RelatedOAD_Day_Init) / sizeof(C_RelatedOAD_Day_Init[0]) )

const ulong32 C_RelatedOAD_Settle_Init[]=						/*�����ն���*/
{
	0x00000001,													/*��������*/
	0x00000200,													/*����й������ܼ�����*/
	0x00100200,													/*�����й������ܼ�����*/
	0x00110200,													/*A�������й�����*/
	0x00120200,													/*B�������й�����*/
	0x00130200,													/*C�������й�����*/
	0x00200200,													/*�����й������ܼ�����*/
	0x00200201,													/*A�෴���й�����*/
	0x00200202,													/*B�෴���й�����*/
	0x00200203,													/*C�෴���й�����*/
	0x00300200,													/*����޹�1�����ܼ�����*/
	0x00310200,													/*A������޹�1����*/
	0x00320200,													/*B������޹�1����*/
	0x00330200,													/*C������޹�1����*/
	0x00400200,													/*����޹�2�����ܼ�����*/
	0x00400201,													/*A������޹�2����*/
	0x00400202,													/*B������޹�2����*/
	0x00400203,													/*C������޹�2����*/
	0x00500200,													/*1�����޹������ܼ�����*/
	0x00510200,													/*A��1�����޹�����*/
	0x00520200,													/*B��1�����޹�����*/
	0x00530200,													/*C��1�����޹�����*/
	0x00600200,													/*2�����޹������ܼ�����*/
	0x00610200,													/*A��2�����޹�����*/
	0x00620200,													/*B��2�����޹�����*/
	0x00630200,													/*C��2�����޹�����*/
	0x00700200,													/*3�����޹������ܼ�����*/
	0x00710200,													/*A��3�����޹�����*/
	0x00720200,													/*B��3�����޹�����*/
	0x00730200,													/*C��3�����޹�����*/
	0x00800200,													/*4�����޹������ܼ�����*/
	0x00810200,													/*A��4�����޹�����*/
	0x00820200,													/*B��4�����޹�����*/
	0x00830200,													/*C��4�����޹�����*/
	0x20310200,													/*���������õ���*/
	0x10100200,													/*�����й���������ܼ�����*/
	0x10200200,													/*�����й���������ܼ�����*/
	0x10300200,													/*����޹�1��������ܼ�����*/
	0x10400200,													/*����޹�2��������ܼ�����*/
	0x10500200,													/*1�����޹���������ܼ�����*/
	0x10600200,													/*2�����޹���������ܼ�����*/
	0x10700200,													/*3�����޹���������ܼ�����*/
	0x10800200,													/*4�����޹���������ܼ�����*/

};
#define	C_RelatedOAD_Settle_InitLen       ( sizeof(C_RelatedOAD_Settle_Init) / sizeof(C_RelatedOAD_Settle_Init[0]) )

const ulong32 C_RelatedOAD_Month_Init[] =						/*�¶���*/
{
	0x00000001,													/*��������*/
	0x00000200,													/*����й������ܼ�����*/
	0x00100200,													/*�����й������ܼ�����*/
	0x00110200,													/*A�������й�����*/
	0x00120200,													/*B�������й�����*/
	0x00130200,													/*C�������й�����*/
	0x00200200,													/*�����й������ܼ�����*/
	0x00210200,													/*A�෴���й�����*/
	0x00220200,													/*B�෴���й�����*/
	0x00230200,													/*C�෴���й�����*/
	0x00300201,													/*����޹�1�����ܼ�����*/
	0x00400200,													/*����޹�2�����ܼ�����*/
	0x00500200,													/*1�����޹������ܼ�����*/
	0x00510200,													/*A��1�����޹�����*/
	0x00520200,													/*B��1�����޹�����*/
	0x00530200,													/*C��1�����޹�����*/
	0x00600200,													/*2�����޹������ܼ�����*/
	0x00610200,													/*A��2�����޹�����*/
	0x00620200,													/*B��2�����޹�����*/
	0x00630200,													/*C��2�����޹�����*/
	0x00700200,													/*3�����޹������ܼ�����*/
	0x00710200,													/*A��3�����޹�����*/
	0x00720200,													/*B��3�����޹�����*/
	0x00730200,													/*C��3�����޹�����*/
	0x00800200,													/*4�����޹������ܼ�����*/
	0x00810200,													/*A��4�����޹�����*/
	0x00820200,													/*B��4�����޹�����*/
	0x00830200,													/*C��4�����޹�����*/
	0x00900200,													/*�������ڵ����ܼ�����*/
	0x00910200,													/*A�������й�����*/
	0x00920200,													/*B�������й�����*/
	0x00930200,													/*C�������й�����*/
	0x00A00200,													/*�������ڵ����ܼ�����*/
	0x00A10200,													/*A�෴�����ڵ���*/
	0x00A20200,													/*B�෴�����ڵ���*/
	0x00A30200,													/*C�෴�����ڵ���*/
	0x20310200,													/*�¶��õ���*/
	0x10100200,													/*�����й���������ܼ�����*/
	0x10200200,													/*�����й���������ܼ�����*/

	0x21310202,													/*A���µ�ѹ�ϸ���*/
	0x21320202,													/*B���µ�ѹ�ϸ���*/
	0x21330202,													/*C���µ�ѹ�ϸ���*/
};
#define	C_RelatedOAD_Month_InitLen       ( sizeof(C_RelatedOAD_Month_Init) / sizeof(C_RelatedOAD_Month_Init[0]) )

const ulong32 C_RelatedOAD_Year_Init[] =						/*����ݽ����ն���*/
{
	0x00000001,													/*��������*/
	0x20320200,													/*���������õ���*/
};
#define	C_RelatedOAD_Year_InitLen       ( sizeof(C_RelatedOAD_Year_Init) / sizeof(C_RelatedOAD_Year_Init[0]) )

const ulong32 FreezeChangeTable[][2] =
{
	{C_Fre_PosAcTolEn,				0x05000100},				/*0x00,	����ʱ�������й��ܵ���*/
	{C_Fre_RevAcTolEn,				0x05000200},				/*0x01,	����ʱ�̷����й��ܵ���*/
	{C_Fre_ComRe1TolEn,				0x05000300},				/*0x02,	����ʱ������޹�1�ܵ���*/
	{C_Fre_ComRe2TolEn,				0x05000400},				/*0x03,	����ʱ������޹�2�ܵ���*/
                                                				
	{C_Fre_TQuadrant1En,			0x05000500},				/*0x10,	����ʱ�̵�һ�����޹��ܵ���*/
	{C_Fre_TQuadrant2En,			0x05000600},				/*0x11,	����ʱ�̵ڶ������޹��ܵ���*/
	{C_Fre_TQuadrant3En,			0x05000700},				/*0x12,	����ʱ�̵��������޹��ܵ���*/
	{C_Fre_TQuadrant4En,			0x05000800},				/*0x13,	����ʱ�̵��������޹��ܵ���*/
                                                				
	{C_Fre_PosAc_DeTime,			0x05000900},				/*0x20,	�����й��������������ʱ��*/
	{C_Fre_RevAc_DeTime,			0x05000A00},				/*0x21,	�����й��������������ʱ��*/
                                                				
	{C_Fre_Active_Power,			0x05001000},				/*0x2C,	����ʱ���й�����*/
	{C_Fre_ReActiveT_Power,			0x05001000},				/*0x2D,	����ʱ���޹�����*/

};
#define	C_FreezeChangeTable_Len	  ( sizeof(FreezeChangeTable) / sizeof(FreezeChangeTable[0]) )


const Str_Event_OIB2	Freeze_OIBTable[] =
{  //�����������Ա�ʶ��			OAD����,							Ĭ�Ϲ��������ַ,		�洢���		Ĭ�Ϲ����������			,�����¼OAD
	{CI_Free_OADTab,		CI_Free_OADTabLen_T,		(ulong32)C_RelatedOAD_Immid_Init,	3,		C_RelatedOAD_Immid_InitLen	,0x00},			/*698-˲ʱ����*/
	{CMin_Free_OADTab,		CMin_Free_OADTabLen_T,		(ulong32)C_RelatedOAD_Min_Init,		351,	C_RelatedOAD_Min_InitLen	,0x02},			/*698-���Ӷ���*//*ԭ300��MaxFrozenNumΪ288(28800��),��Ϊ365���Ϊ35040��,�ݸ�Ϊ351,ʵ�ʸ����ݳ���û�õ�*/
	{CH_Free_OADTab,		CH_Free_OADTabLen_T,		(ulong32)C_RelatedOAD_Hour_Init,	254,	C_RelatedOAD_Hour_InitLen	,0x03},			/*698-Сʱ����*/
	{CD_Free_OADTab,		CD_Free_OADTabLen_T,		(ulong32)C_RelatedOAD_Day_Init,		365,	C_RelatedOAD_Day_InitLen	,0x04},			/*698-�ն���*/
	{CSett_Free_OADTab,		CSett_Free_OADTabLen_T,		(ulong32)C_RelatedOAD_Settle_Init,	12,		C_RelatedOAD_Settle_InitLen	,0x05},			/*698-�����ն���*/
	{CM_Free_OADTab,		CM_Free_OADTabLen_T,		(ulong32)C_RelatedOAD_Month_Init,	24,		C_RelatedOAD_Month_InitLen	,0x06},			/*698-�¶���*/
	{CYSettle_Free_OADTab,	CYSettle_Free_OADTabLen_T,	(ulong32)C_RelatedOAD_Year_Init,	4,		C_RelatedOAD_Year_InitLen	,0x11},			/*698-�궳��*/
	{CTZ_Free_OADTab,		CTZ_Free_OADTabLen_T,		(ulong32)C_RelatedOAD_Immid_Init,	2,		C_RelatedOAD_Immid_InitLen	,0x08},			/*698-ʱ�����л�����*/
	{CPT_Free_OADTab,		CPT_Free_OADTabLen_T,		(ulong32)C_RelatedOAD_Immid_Init,	2,		C_RelatedOAD_Immid_InitLen	,0x09},			/*698-��ʱ�α��л�����*/
	{CR_Free_OADTab,		CR_Free_OADTabLen_T,		(ulong32)C_RelatedOAD_Immid_Init,	2,		C_RelatedOAD_Immid_InitLen	,0x0A},			/*698-���ʵ���л�����*/
	{CL_Free_OADTab,		CL_Free_OADTabLen_T,		(ulong32)C_RelatedOAD_Immid_Init,	2,		C_RelatedOAD_Immid_InitLen	,0x0B},			/*698-�����л�����*/
};
#define	C_Freeze_OIBTableLen       ( sizeof(Freeze_OIBTable) / sizeof(Freeze_OIBTable[0]) )

/*************************��ȫģʽ�ֱ��ṹ��*********/
typedef struct
{
	ushort16	DI;											/*��ʶ��*/
	ushort16	Mode;										/*ģʽ��*/
}Str_Safe_Type1;
typedef struct
{
	ushort16	DI;											/*��ʶ��*/
	ushort16	DefaultDI;									/*��ʶ��*/
	ushort16	Mode;										/*ģʽ��*/
}Str_Safe_Type2;

#define	C_Read							0x01				/*��ȡ*/
#define	C_SetUp							0x02				/*����*/
#define	C_Operation						0x04				/*����*/

//#define	C_Read_PlainText				0x8000			/*��ȡ-����*/
#define	C_Read_PlainText				0xF000				/*��ȡ-����*/
#define	C_Read_PlainTextMac				0x4000				/*��ȡ-����+MAC*/
#define	C_Read_CipherText				0x2000				/*��ȡ-����*/
#define	C_Read_CipherTextMac			0x1000				/*��ȡ-����+MAC*/

//#define	C_SetUp_PlainText			    0x0800			/*����-����*/
#define	C_SetUp_PlainText				0x0F00				/*����-����*/
#define	C_SetUp_PlainTextMac			0x0400				/*����-����+MAC*/
#define	C_SetUp_CipherText				0x0200				/*����-����*/
#define	C_SetUp_CipherTextMac			0x0100				/*����-����+MAC*/

//#define	C_Operation_PlainText			0x0080			/*����-����*/
#define	C_Operation_PlainText			0x00F0				/*����-����*/
#define	C_Operation_PlainText_Only		0x0080				/*����-������*/
#define	C_Operation_PlainTextMac		0x0040				/*����-����+MAC*/
#define	C_Operation_CipherText			0x0020				/*����-����*/
#define	C_Operation_CipherTextMac		0x0010				/*����-����+MAC*/
const	Str_Safe_Type1	GV_SafeModeParameters1[]=
{
	{CWalletFile_698,				C_Read_PlainText																			},					/*698-��ǰǮ���ļ�*/
	{CDrive_Report_698,				C_Read_PlainTextMac																			},					/*698-���ܱ������ϱ�*/
#if 0                                                                                                                       	  					
	{CDate_Week_698,				C_Read_PlainText|C_SetUp_CipherTextMac|C_Operation_PlainText								},					/*����ʱ��*/
#endif                                                                                                                              				
	{CDate_Week_698,				C_Read_PlainText|C_SetUp_CipherTextMac|C_Operation_PlainText_Only|C_Operation_CipherTextMac	},					/*����ʱ��*/
	{CComm_Address_698,				C_Read_PlainText|C_SetUp_CipherTextMac														},					/*ͨ�ŵ�ַ*/
	{CMeter_Num_698,				C_Read_PlainText|C_SetUp_PlainTextMac														},					/*���*/
	{CCustomer_Num_698,				C_Read_PlainTextMac|C_SetUp_PlainTextMac													},					/*�ͻ����*/
	{CSoftw_Record_Number_698,		C_Read_PlainText|C_SetUp_CipherTextMac														},					/*���������*/
	{CFrameTransmission_698,		C_Read_PlainText|C_SetUp_CipherTextMac|C_Operation_CipherTextMac							},					/*��֡����*/
	{CBlockTransmission_698,		C_Read_PlainText|C_SetUp_CipherText|C_Operation_CipherText									},					/*�ֿ鴫��*/
	{CExtTransmission_698,			C_Read_PlainText|C_SetUp_PlainText|C_Operation_PlainText									},					/*��չ����*/
	{CESAM_698,						C_Read_PlainText|C_SetUp_PlainTextMac|C_Operation_CipherTextMac								},					/*ESAM*/
	{CSafeModeParameters_698,		C_Read_PlainText|C_SetUp_CipherTextMac|C_Operation_CipherText								},					/*��ȫģʽ����*/
	{0x5000,						C_Read_PlainTextMac|C_SetUp_CipherTextMac|C_Operation_PlainTextMac							},					/*698-˲ʱ����*/
	{CM_Com_Ac_Tol_En_698,			C_Read_PlainText																			},					/*698-�¶��õ���*/
	{CStep_Com_Ac_Tol_En_698,		C_Read_PlainText																			},					/*698-���ݽ����õ���*/
	{CExtern_OIFF86_698,			C_Read_PlainText|C_Operation_PlainText														},					/*698-��������FF86����֧����չ�������ķ���*/
};
#define	GV_SafeModeParameters1Len (sizeof(GV_SafeModeParameters1)/sizeof(Str_Safe_Type1))
const Str_Safe_Type2 GV_SafeModeParameters2[]=
{
	{0x0fff,	0x0fff,		C_Read_PlainText													},													/*698-��ǰ����*/
	{0x1fff,	0x0fff,		C_Read_PlainTextMac													},													/*698-�������*/
	{0x2fff,	0x0fff,		C_Read_PlainTextMac|C_SetUp_CipherTextMac|C_Operation_PlainTextMac|C_Operation_CipherText|C_Operation_CipherTextMac},	/*698-����*/
	{0x3fff,	0x0fff,		C_Read_PlainTextMac|C_SetUp_CipherTextMac|C_Operation_CipherTextMac	},													/*698-�¼�*/
	{0x4fff,	0x0fff,		C_Read_PlainTextMac|C_SetUp_CipherTextMac|C_Operation_CipherTextMac	},													/*698-�α���*/
//	{0x50ff,	0x00ff,		C_Read_PlainTextMac|C_SetUp_CipherTextMac							},													/*698-����*/
	{0x50ff,	0x00ff,		C_Read_PlainTextMac|C_SetUp_CipherTextMac|C_Operation_CipherTextMac	},													/*698-����*/
	{0x60ff,	0x00ff,		C_Read_PlainText|C_SetUp_PlainText|C_Operation_PlainText			},													/*698-�ɼ����*/
	{0x70ff,	0x00ff,		C_Read_PlainText|C_Operation_PlainText								},													/*698-����*/
	{0x80ff,	0x00ff,		C_Read_PlainTextMac|C_SetUp_CipherTextMac|C_Operation_CipherTextMac	},													/*698-����*/
	{0xF2ff,	0x00ff,		C_Read_PlainText|C_SetUp_PlainText|C_Operation_PlainText			},													/*698-��������豸*/
	{0xFFff,	0x00ff,		C_Read_PlainText|C_SetUp_PlainText|C_Operation_PlainText			},													/*698-�Զ���*/
};
#define	GV_SafeModeParameters2Len (sizeof(GV_SafeModeParameters2)/sizeof(Str_Safe_Type2))


//*************************************�ඨ��*********************************************
#define	C_Static			0x00								/*��̬*/
#define	C_Dynamic			0x01								/*��̬*/
typedef struct                                          		
{                                                       		
	uchar8		Conversion;										/*����*/
	uchar8		Unit;											/*��λ*/
}Str_ConandUnit;                                        		
                                                        		
                                                        		
typedef struct                                          		
{                                                       		
	uchar8	Err_645;											/*645������*/
	uchar8	Err_698;											/*698������*/
}Str_698And645_ErrSwich;
const Str_698And645_ErrSwich GV_698And645_ErrSwich[] =
{
	{C_RateNum_OV,			C_RateNum_OV_DAR		},			/*��������*/
	{C_PeriodNum_OV,		C_PeriodNum_OV_DAR		},			/*��ʱ������*/
	{C_SeasonNum_OV,		C_SeasonNum_OV_DAR		},			/*��ʱ������*/
	{C_Baud_NotModified,	C_Baud_NotModified_DAR	},			/*ͨ�����ʲ��ܸ���*/
	{C_Unauthorized,		C_RWForbid_DAR  		},			/*δ��Ȩ/�����*/
	{C_No_Request_data,		C_ObjectNotExist_DAR	},			/*����������  -698���󲻴���*/
	{C_OtherErr,			C_OtherErr_DAR			},			/*��������*/
//	{C_OK,					C_OK_DAR				},			/*�ɹ�*/
	{C_IDError,				C_ObjectNotExist_DAR	},			/*���ݱ�ʶ��   */
	{C_NoAccess,			C_Unauthorized_DAR		},			/*��Ȩ��     */
	{C_SERR_FWAddressErr,	C_FWAddressErr_DAR		},			/* ��ַ�쳣 */
	{C_ObjectTypeErr_DAR,	C_ObjectTypeErr_DAR		},			/* �ӿ������ */
};
#define	GV_698And645_ErrSwichLen ( sizeof(GV_698And645_ErrSwich) / sizeof(Str_698And645_ErrSwich) )

#define	C_ESAMLCError						0x23				/*ESAM��LC����*/

/*����645��ʶ���Ӧ�������ʾ����*/
#define	C_DemandDispScreenNum				3 					/*�������*/
#define	C_TZoneDispScreenNum				14					/*ʱ�α�*/
                                                    								
#define	C_WriteEventRecord					0x68				/*д�¼���¼*/
#define	C_ReadDate							0x86				/*������д���ݲ�*/
#define	C_NeedWriteEventRecord				0xAA				/*д�ܵı�̼�¼*/
#define	C_NotWriteEventRecord				0x55				/*��д�ܵı�̼�¼*/


/*�¼������ʶ���Ӧ*/
typedef struct
{
	uchar8	V_OIB;
	ulong32 V_DI;												/*�¼���¼���ݱ�ʾ**/
}Str_EvenClearTable;
//#define C_EventDI 0x000000FF

const Str_EvenClearTable  Str_EvenClearTable698To645[]=               /*��������������¼���¼������¼������DI1�з����ʶ���¼��������¼�����ʱ�ñ�ʶ��ΪFF���������*/
{//	OIB
	{CLoss_Vol_OIB,						(CLossAVol_FF_1|C_EventDI)},					/*698-ʧѹ*/
	{CLow_Vol_OIB,						(CLowAVol_FF_1|C_EventDI)},						/*698-Ƿѹ*/
	{COver_Vol_OIB,						(COverAVol_FF_1|C_EventDI)},					/*698-��ѹ*/
	{CBreak_Vol_OIB,					(CBreakAVol_FF_1|C_EventDI)},					/*698-����*/
	{CLoss_Curr_OIB,					(CLossACurr_FF_1|C_EventDI)},					/*698-ʧ��*/
	{COver_Curr_OIB,					(COverACurr_FF_1|C_EventDI)},					/*698-����*/
	{CBreak_Curr_OIB,					(CBreakACurr_FF_1|C_EventDI)},					/*698-����*/
//	{CTrend_Rev_OIB,					(CTrend_Rev_Note_1|C_EventDI)},					/*698-��������*/
	{CTrend_Rev_OIB,					(CPowerTRev_FF_1|C_EventDI)},					/*698-���ʷ���*/        
	{COver_Lo_OIB,						(COverALo_FF_1|C_EventDI)},						/*698-����*/
	{CPos_De_Over_OIB,					(CPos_Ac_De_Over_Note_1|C_EventDI)},			/*698-���ܱ������й����������¼�*/
	{CRe_De_Over_OIB,					(CRev_Ac_De_Over_Note_1|C_EventDI)},			/*698-���ܱ����й����������¼�*/
	{CRe_ReDe_Over_OIB,					(CQua1_Re_De_Over_Note_1|C_EventDI)},			/*698-���ܱ��޹����������¼�*/
	{CPFactorT_Over_OIB,				(CPFactorT_FF_1|C_EventDI)},					/*698-���ܱ��������������¼�*/
	{CAll_Loss_Vol_OIB,					(CAll_Loss_Vol|C_EventDI)},						/*698-���ܱ�ȫʧѹ�¼�*/
	{CAux_Pow_Down_OIB,					(CAux_Pow_Down|C_EventDI)},						/*698-���ܱ�����Դʧ���¼�*/
	{CRevPS_Vol_OIB,					(CRevPSVol_FF_1|C_EventDI)},					/*698-���ܱ��ѹ�������¼�*/
	{CRevPS_Curr_OIB,					(CRevPSCurr_FF_1|C_EventDI)},					/*698-���ܱ�����������¼�*/
	{CPow_Down_OIB,						(CPow_Down_Degree|C_EventDI)},					/*698-���ܱ�����¼�*/
	{CProgram_OIB,						(CProgram_Degree|C_EventDI)},					/*698-���ܱ����¼�*/
	{CTol_Clear_OIB,					(CTol_Clear_Degree|C_EventDI)},					/*698-���ܱ������¼�*/
	{CDe_Clear_OIB,						(CDe_Clear_Degree|C_EventDI)},					/*698-���ܱ����������¼�*/
	{CEven_Clear_OIB,					(CEven_Clear_Degree|C_EventDI)},				/*698-���ܱ��¼������¼�*/
	{CAdjTime_OIB,						(CAdjTime_Degree|C_EventDI)},					/*698-���ܱ�Уʱ�¼�*/
	{CProgPT_OIB,						(CProgPT_Degree|C_EventDI)},					/*698-���ܱ�ʱ�α����¼�*/
	{CProgTZ_OIB,						(CProgTZ_Degree|C_EventDI)},					/*698-���ܱ�ʱ�������¼�*/
	{CProgWRe_OIB,						(CProgWRe_Degree|C_EventDI)},					/*698-���ܱ������ձ���¼�*/
	{CProgSettD_OIB,					(CProgSettD_Degree|C_EventDI)},					/*698-���ܱ�����ձ���¼�*/
	{COpenW_OIB,						(COpenW_Degree|C_EventDI)},						/*698-���ܱ����¼�*/
	{COpenCW_OIB,						(COpenCW_Degree|C_EventDI)},					/*698-���ܱ���ť���¼�*/
	{CNoBal_Vol_OIB,					(CNoBalVol_FF_1|C_EventDI)},					/*698-���ܱ��ѹ��ƽ���¼�*/
	{CNoBal_Curr_OIB,					(CNoBalCurr_FF_1|C_EventDI)},					/*698-���ܱ������ƽ���¼�*/
	{CRelayOpen_OIB,					(CRelayOpen_FF_1|C_EventDI)},					/*698-���ܱ���բ�¼�*/
	{CRelayClose_OIB,					(CRelayClose_FF_1|C_EventDI)},					/*698-���ܱ��բ�¼�*/
	{CProgHol_OIB,						(CProgHol_Degree|C_EventDI)},					/*698-���ܱ�ڼ��ձ���¼�*/
	{CProgAcC_OIB,						(CProgAcC_Degree|C_EventDI)},					/*698-���ܱ��й���Ϸ�ʽ����¼�*/
	{CProgReC_OIB,						(CProgReC_Degree|C_EventDI)},					/*698-���ܱ��޹���Ϸ�ʽ����¼�*/
	{CProgTPara_OIB,					(CProgTPara_Degree|C_EventDI)},					/*698-���ܱ���ʲ��������¼�*/
	{CProgLad_OIB,						(CProgLad_Degree|C_EventDI)},					/*698-���ܱ���ݱ����¼�*/
	{CKey_Update_OIB,					(CProgKD_Degree|C_EventDI)},					/*698-���ܱ���Կ�����¼�*/
	{CAbnorC_OIB,						(CAbnorC_Degree|C_EventDI)},					/*698-���ܱ��쳣�忨�¼�*/
	{CBuyCurr_OIB,						(CBuyCurr_FF_Note_1|C_EventDI)},				/*698-���ܱ����¼�*/
	{CReturn_M_OIB,						(CReturn_M_Degree|C_EventDI)},					/*698-���ܱ��˷��¼�*/
	{CConM_OIB,							(CConM_Degree|C_EventDI)},						/*698-���ܱ�㶨�ų������¼�*/
	{CRelayFa_OIB,						(CRelayFa_Degree|C_EventDI)},					/*698-���ܱ��ɿ��������¼�*/
	{CPowerFa_OIB,						(CPowerFa_Degree|C_EventDI)},					/*698-���ܱ��Դ�쳣�¼�*/
	{CSevNoBal_Curr_OIB,				(CSevNoBalCurr_FF_1|C_EventDI)},				/*698-���ܱ�������ز�ƽ���¼�*/
	{CClock_FaultState_OIB,				(CClockFa|C_EventDI)},							/*698-���ܱ�ʱ�ӹ����¼�*/
	{CMeteringChipFault_OIB,			(CMeterFa|C_EventDI)},							/*698-���ܱ����оƬ�����¼�*/
	{CBroadcastTime_OIB,				(CBroadcastTime_Degree|C_EventDI)},				/*698-���ܱ�㲥Уʱ�¼�*/
    {CNeutralCurrentAbnormal_OIB,		(CNeutralCurrentAbnormal_Note_1|C_EventDI)},	/*698-���ܱ����ߵ����쳣�¼�*/
};
#define Str_EvenClearTable698To645_Len  ( sizeof(Str_EvenClearTable698To645) / sizeof(Str_EvenClearTable) )
extern uchar8 SF_DriveReportSet_Change (uchar8 Type, uchar8 *pData, uchar8 DataLenth );



#define	C_CleanOtherEvent				0x68
#define	C_JustAddECleanNo				0x86
#define	C_EventMAXRelatedOAD			60

ulong32	SV_ReadAfterSetTimer;

typedef struct
{
	uchar8	EventNo;											/*�¼���*/
	uchar8	WriteBit;											/*д״̬��λ*/
}Str_OtherEventMapping_Type;

#define	C_EndTimeOffset					(1 + 7)					/*��7 ʱ��״̬��¼������ʱ��ƫ��*/

uchar8	SF_ReadAfterSetForPerDI( uchar8 *P_ucData, ulong32 V_ulDI, uchar8 V_ucDILen );
uchar8	SF_Read_TZone_PTReg( uchar8 *P_ucData, ulong32	LimitDI, ulong32	V_ulDI );
uchar8 Action_Service_PerOI( Str_Comm_698_RW *pV_698RWPara, Str_Comm_645 *pV_645Frame );
void Action_Service_MultiOI( Str_Comm_698_RW *pV_698RWPara, Str_Comm_645 *pV_645Frame );
uchar8 ActionRd_Service_MultiOI( Str_Comm_698_RW *pV_698RWPara, uchar8 *pV_DataBuf, uchar8 V_BufLen, uchar8 *pV_NextFrFlag, Str_Comm_645 *pV_645Frame );
void SF_DemandClear( void );
void	SF_MeterInit( void );
void	SF_MeterClear( Str_Comm_645 *pV_645Frame );
uchar8 SF_EventClear( Str_Comm_645 *pV_645Frame, ulong32 V_ulOAD );
uchar8 SF_FreezingOrder_C16( Str_Comm_645 *pV_645Frame );
uchar8	SF_BroadcastSetClock( Str_Comm_645 *pV_645Frame );
void SF_CombDataTo645Type_W( uchar8 *P_698Data, Str_Comm_645 *pV_645Frame, uchar8 V_Len_645 );
uchar8 SF_SetParm( Str_Comm_645 *pV_645Frame, ulong32 V_ulLastDI, ulong32 V_ulNextDI, uchar8 V_WriteEventFlag, ulong32 V_ulProgOAD, uchar8 OperationFlag );
void		Have_IPEvent_Prog_698( ulong32 V_ulProgOAD, ulong32 V_ulProgTimesOAD, Str_Comm_645 *pV_645Frame );
uchar8 SF_ActionPerOI( Str_Comm_698_RW *pV_698RWPara, Str_Comm_645 *pV_645Frame, uchar8 V_ucOINum );
uchar8 SF_SetPerOI( Str_Comm_698_RW *pV_698RWPara, uchar8 V_ucOINum, Str_Comm_645 *pV_645Frame );
uchar8	SF_ReadAfterSet( Str_Comm_698_RW *pV_698Frame, Str_Comm_645 *pV_645Frame );
uchar8 SF_SetDispPerOI( Str_Comm_698_RW *pV_698RWPara, uchar8 V_ucOINum, Str_Comm_645 *pV_645Frame );
uchar8 SF_GetAPDU_BpsRead( ulong32 V_OAD, uchar8 *P_DataBuf );
uchar8 SF_GetAPDU_ApplianceInOutRead( RdOI_Para_T V_OAD, uchar8 *P_DataBuf, uchar8 V_ucOff, ushort16 *P_DataOff );
ushort16	SF_DataExchangeTo645_BasicData( uchar8 *pV_698data, uchar8 *pV_645data, uchar8 V_ucLen698, uchar8 *V_ucLen645 );

uchar8 SF_FreezeOADRead( RdOI_Para_T V_OAD, uchar8 *P_DataBuf, ushort16 *P_DataOff, uchar8 V_TimeOADFlay, uchar8 *pV_ArrayNum );
uchar8 SF_JugeRelayOAD( Str_Comm_698_RW *pV_698RWPara, uchar8 V_ucOINum );
uchar8 SF_GetAPDU_DISPRead( RdOI_Para_T V_OAD, uchar8 *P_DataBuf, ushort16 V_ucOff, ushort16 *P_DataOff );
void OneByteReverse( uchar8 *pV_Sourcedata );
uchar8 Comm_SoftwareCampare_698( WtOI_Rt_T V_OAD, uchar8 *V_ucBuff, ushort16 *V_Len );
void SF_GetPow_Down_Time( uchar8 *P_DataBuf );
uchar8 SF_SetHolidyPerOI( Str_Comm_698_RW *pV_698RWPara, uchar8 V_ucOINum, Str_Comm_645 *pV_645Frame );
uchar8 SF_GetAPDU_HolidyRead( RdOI_Para_T *V_OAD, uchar8 *P_DataBuf, ushort16 V_ucOff, uchar8 V_DINum, ushort16 *P_DataOff );
uchar8 SF_EventOADRead( RdOI_Para_T V_OAD, uchar8 *P_DataBuf, ushort16 *P_DataOff, uchar8 V_TimeOADFlay, uchar8 *pV_ArrayNum );
uchar8 SF_EventClear_698( ulong32 V_ulOAD, Str_Comm_645 *pV_645Frame, uchar8 V_ProgFlag );
uchar8	JudgeMeterType( ulong32 V_ulOAD );
uchar8	SF_Judge_SetServiceRight( ushort16 V_OI, ushort16 *V_ulMode );
ushort16	SF_DataExchangeTo698_BasicData( uchar8 *pV_698data, uchar8 *pV_645data, uchar8 V_ucLen698, uchar8 V_ucLen645 );
uchar8 SF_Judge_OINature( Str_Comm_698_RW *pV_698RWPara, Str_Type645DI_Class *P_DIFor645, uchar8 *P_645DINum, uchar8 OperationMode );
void CommMSg_StartTxd_698( uchar8 CommNo );
uchar8 SF_LocalAndRemoteMeterDiJudge( ulong32 V_Di );
uchar8 SF_JugeSameOI( ushort16 V_ulOI );
uchar8 InF_Display_JudgeIDActive( ulong32 V_ulCodeID, ulong32 V_ulRelatedCodeID, uchar8 V_ucScreenNum );
uchar8 SF_JudgeSameRealatedOAD( uchar8 *P_RealatedOADTab, uchar8 *P_AddOAD, uchar8 V_ucRealatedOADNum, uchar8 V_ucOIFlag );
uchar8 SF_JudgeSameRealatedOADCycle (uchar8 *P_RealatedOADTab,uchar8 *P_AddOAD,uchar8 V_ucRealatedOADNum,uchar8 V_ucOIFlag);
uchar8 SF_JudgeSameRealatedOADStoreNum( uchar8 *P_RealatedOADTab, uchar8 *P_AddOAD, uchar8 V_ucRealatedOADNum, uchar8 V_ucOIFlag );
uchar8 SF_JudgeAllAA( uchar8 *P_DataBuf, uchar8 P_DataLen );
uchar8 SF_GetChannelVaild( uchar8 V_usChannel );
void SF_Encode_VolRates( Struct_FrozenConvert_Type *pStr_Encode, uchar8 *pDataBuf, uchar8 *pData645Buf, ushort16 *pV_DataOff, ushort16 *pV_DataOff645 );
uchar8 SF_Judge_Para( Str_Comm_698_RW *pV_698RWPara, Str_Type645DI_Class *V_DIFor645, uchar8 V_uc645DINum, uchar8 V_ucOINum );
uchar8 SF_PrograReactivePowerState( ulong32 V_Data_Id_OAD, uchar8 *P_DataBuf, ushort16 *V_Len );
void RELEASE_Service_Deal( uchar8 Client_Addr );
void SF_GetCommChanelCurrentLen( uchar8	V_ucChanelNo );
uchar8 SF_DataLen_AXDR_Encode( uchar8 *pV_DataBuf,ushort16 V_DataLen );
void SF_OverAPDU_DealWith( uchar8 *pV_return, ushort16 *pV_DataOff, ushort16 V_LastDataOff, uchar8 *pV_NextTimeNew, uchar8 *pV_NextTimeOld );
void SF_RenewRelayControlStutas( void );
void SF_DeletReport( uchar8 channel, uchar8 EventNo );
uchar8 InF_RateNumChangeToHex( void );
extern void SF_SetRTCErrState( uchar8 V_ucRTCFlag );
extern uchar8 Inf_ReadEventLast_N( ulong32 * P_Data_Id_OAD, uchar8 * P_FixTime, uchar8 * P_Data, uchar8 * V_NextSign, ushort16 * P_Data_Length, uchar8 V_timeFlash );

/*2020��׼�����ϱ�2005*/
void Inf_DeletReport( uchar8 channel, uchar8 EventNo );


void Inf_DealReportNum( uchar8 *p_EventNo, uchar8 Len );
ushort16 Inf_Comm_REPORTFlag( void );
uchar8 Inf_Comm_REPORTFlagClear( uchar8 ClearMode );

uchar8 Is_ID_Comm_ResponseErr_698( Str_Comm_645 * pV_698Frame, Str_Comm_698_RW *pV_698RWPara );

void SF_Event_Relay_JudgeAll00( ulong32 V_ulOAD, uchar8 *p_VFlag );

///698����645Э�飬��ʶ����ת��
#define C_FreezNumHig							0x01							/*������Ÿ�λƫ��*/
#define C_FreezCycleLow							0x02							/*�������ڵ�λƫ��*/
#define C_FreezCycleHig							0x03							/*�������ڸ�λƫ��*/
///698����645����                                                           	
#define		C_MinFreez							1								/*Freeze_OIBTable����з��Ӷ���λ��*/
#define		C_RelatedOADTabLen					6								/*�����б�洢��ʽ��2�ֽ����+2�ֽڶ�������+2�ֽڴ洢���*/
                                                                            	
#define		C_TolLoss_CurrOffsetA				0								/*698������ȫʧѹA�����ֵ����ƫ��*/
#define		C_TolLoss_CurrOffsetB				3								/*698������ȫʧѹB�����ֵ����ƫ��*/
#define		C_TolLoss_CurrOffsetC				6								/*698������ȫʧѹC�����ֵ����ƫ��*/
#define		C_TolLoss_CurrOffsetASign			(C_TolLoss_CurrOffsetA + 2)		/*698������ȫʧѹA�����ֵ����λƫ��*/
#define		C_TolLoss_CurrOffsetBSign			(C_TolLoss_CurrOffsetB + 2)		/*698������ȫʧѹB�����ֵ����λƫ��*/
#define		C_TolLoss_CurrOffsetCSign			(C_TolLoss_CurrOffsetC + 2)		/*698������ȫʧѹC�����ֵ����λƫ��*/



#define		C_RelayFa_State_Offset				5								/*698�����и��ɿ�������ʱ���ɿ���״̬����ƫ��λ��*/
#define		C_MeterStatus_Relay_Offset			3								/*698ȷ�ϸ����ϱ�״̬�֣�����բ�����ֽ���ͨ���е�ƫ��*/
#define		C_MeterStatus_Offset				2								/*698ȷ�ϸ����ϱ�״̬�֣����ֽ���ͨ���е�ƫ�� */
#define		C_MeterStatus_EventNum				4								/*�����ϱ�״̬���账����¼�������Ŀǰֻ֧����բ����բ+ͣ�����Ƿѹ��ʱ�ӵ��Ƿѹ��	*/
#define		C_BitNum0							0								/*�ֽڼ�����ʼ	*/
#define		C_MeterStatus_RelayWord_Offset		1								/*698������բ�ڸ����ϱ�״̬���е������ֽ�	*/

#define		C_PTNum_Offset						19								/*ʱ�α��̼�¼�У�д���ǵڼ���ʱ�α����ڵ�λ�ã���401702XX��XX��λ��*/
#define		C_PTData_Offset						23								/*ʱ�α��̼�¼�У��������ڵ�λ��*/
#define		C_PTProgEventNum					4								/*ʱ�α��¼���¼��645Э�����ݴ洢ʱ�����ݿ��д洢ʱ�α�ĸ���*/
#define		C_TZData_offset_645					6								/*ʱ�����¼���¼��645Э�飬��������λ��*/


typedef struct
{
	ulong32	RelateOAD_645;														/*���������б��OAD����645��ȡ˳��*/
	uchar8  ReadFlag;															/*�Ƿ���Ҫ���з����ȡ�ı�־*/
	uchar8  DataLen;															/*���ݳ���	*/
}Str_EventChange_Table2;


typedef struct
{
	ulong32	DI;																	/*645DI*/
	uchar8	OIB;																/*OIB,698��ʶ��*/
	uchar8	Nature;																/*Nature,698��ʶ��*/
	ulong32	PStr_EventChange_Table2;											/*�ṹ���׵�ַ*/
	uchar8	TableLen;															/*��Ӧ2������ܸ���*/
}Str_EventChange_Table1;


#define C_ReadDeal_A							0x01							/*��Ҫ��ȡ�������ݣ����ѹ������, A��,(���ʡ�������������ʱ����Ӧ��)  */
#define C_ReadDeal_B							0x02							/*��Ҫ��ȡ�������ݣ����ѹ������, B��,(���ʡ�������������ʱ����ӦA)*/
#define C_ReadDeal_C							0x03							/*��Ҫ��ȡ�������ݣ����ѹ������, C��,(���ʡ�������������ʱ����ӦB)*/
#define C_ReadDeal_D							0x04							/*(���ʡ�������������ʱ����ӦC)*/
#define C_ReadDeal_E							0x05							/*ȫʧѹ����ֵ����*/
#define C_ReadDeal_F							0x06							/*���ɿ�������ʱ״̬����*/
#define C_ReadDeal_G							0x07							/*ʱ���������ݴ���*/
#define C_NormalRead							0x00							/*����Ҫ��ȡ�������ݣ������*/
                                                            					
#define C_EventHappen							0x00002000						/*�¼�����ʱ��*/
#define C_EventHappening						0x00006000						/*�¼������ڼ�*/
#define C_EventEnd								0x00008000						/*�¼�����ʱ��*/
#define C_OADNum								0x03 							/*OAD���� ��1������ȡ��0���¼���OAD��1��������OAD��2:ȫFFFFFFFF*/


/*���˳�������������*/
const Str_EventChange_Table2 EventTable2_RelateOAD0405[] =  /**********����/ʧ�����������б�***************/
{
/*��Ӧ��698���������б�                  �����������ȡ��־��	*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0201	�¼�����ʱ��	645   6�ֽ�*/                                      	
	{C_HP_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00102201	�����й��ܵ���*/        
	{C_HP_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00202201	�����й��ܵ���*/        
	{C_HP_ComRe1TolEn,						C_NormalRead,				CLCom_Re1_Tol_En_0},				/*0x00302201	����޹�1�ܵ���*/   
	{C_HP_ComRe2TolEn,						C_NormalRead,				CLCom_Re2_Tol_En_0},				/*0x00402201	����޹�2�ܵ���*/   
	{C_HP_APosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00112201	A�������й�����*/   
	{C_HP_ARevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00212201	A�෴���й�����*/   
	{C_HP_AComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00312201	A������޹�1�ܵ���*/
	{C_HP_AComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00412201	A������޹�2�ܵ���*/
	{(CPhaseFF_Volage|C_EventHappen),		C_ReadDeal_A,				CLPhaseA_Volage},					/*0x20002200	*/
	{(CPhaseFF_Curr|C_EventHappen),			C_ReadDeal_A,				CLPhaseA_Curr},						/*0x20012200	*/
	{(CInstantFF_AcPow|C_EventHappen),		C_ReadDeal_B,				CLInstantA_AcPow},					/*0x20042200	*/
	{(CInstantFF_RePow|C_EventHappen),		C_ReadDeal_B,				CLInstantA_AcPow},					/*0x20052200	*/
	{(CPhaseFF_PowerFactor|C_EventHappen),	C_ReadDeal_B,				CLPhaseA_PowerFactor},				/*0x200A2200	*/
	{C_HP_BPosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00122200	B�������й�����*/   
	{C_HP_BRevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00222200	B�෴���й�����*/   
	{C_HP_BComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00322200	B������޹�1�ܵ���*/
	{C_HP_BComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00422200	B������޹�2�ܵ���*/
	{(CPhaseFF_Volage|C_EventHappen),		C_ReadDeal_B,				CLPhaseA_Volage},					/*0x20002200	*/
	{(CPhaseFF_Curr|C_EventHappen),			C_ReadDeal_B,				CLPhaseA_Curr},						/*0x20012200	*/
	{(CInstantFF_AcPow|C_EventHappen),		C_ReadDeal_C,				CLInstantA_AcPow},					/*0x20042200                       */
	{(CInstantFF_RePow|C_EventHappen),		C_ReadDeal_C,				CLInstantA_AcPow},					/*0x20052200	*/
	{(CPhaseFF_PowerFactor|C_EventHappen),	C_ReadDeal_C,				CLPhaseA_PowerFactor},				/*0x200A2200	*/
	{C_HP_CPosAcEn ,						C_NormalRead,				CLPosA_Ac_En_0},					/*0x00130200	C�������й�����*/   
	{C_HP_CRevAcEn ,						C_NormalRead,				CLRevA_Ac_En_0},					/*0x00230200	C�෴���й�����*/   
	{C_HP_CComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00330200	C������޹�1�ܵ���*/
	{C_HP_CComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00430200	C������޹�2�ܵ���*/
	{(CPhaseFF_Volage|C_EventHappen),		C_ReadDeal_C,				CLPhaseA_Volage},					/*0x20002200	*/
	{(CPhaseFF_Curr|C_EventHappen),			C_ReadDeal_C,				CLPhaseA_Curr},						/*0x20012200	*/
	{(CInstantFF_AcPow|C_EventHappen),		C_ReadDeal_D,				CLInstantA_AcPow},					/*0x20042200	*/
	{(CInstantFF_RePow|C_EventHappen),		C_ReadDeal_D,				CLInstantA_AcPow},					/*0x20052200	*/
	{(CPhaseFF_PowerFactor|C_EventHappen),	C_ReadDeal_D,				CLPhaseA_PowerFactor},				/*0x200A2200	*/
	{(CEventEndTime),						C_NormalRead,				(CLEventEndTime-1)},				/*0X20200200	�¼�����ʱ��645 6�ֽ�*/
	{C_End_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00100200	�����й��ܵ���*/        
	{C_End_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00200200	�����й��ܵ���*/        
	{C_End_ComRe1TolEn,						C_NormalRead,				CLCom_Re1_Tol_En_0},				/*0x00300200	����޹�1�ܵ���*/   
	{C_End_ComRe2TolEn,						C_NormalRead,				CLCom_Re2_Tol_En_0},				/*0x00400200	����޹�2�ܵ���*/   
	{C_End_APosAcEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00110200	A�������й�����*/   
	{C_End_ARevAcEn,						C_NormalRead,				CLPosA_Ac_En_0	},					/*0x00210200	A�෴���й�����*/   
	{C_End_AComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00310200	A������޹�1�ܵ���*/
	{C_End_AComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00410200	A������޹�2�ܵ���*/
	{C_End_BPosAcEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00122200	B�������й�����*/   
	{C_End_BRevAcEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00222200	B�෴���й�����*/   
	{C_End_BComRe1En,						C_NormalRead,				CLCom_Re1_Tol_En_0},				/*0x00322200	B������޹�1�ܵ���*/
	{C_End_BComRe2En,						C_NormalRead,				CLCom_Re2_Tol_En_0},				/*0x00422200	B������޹�2�ܵ���*/
	{C_End_CPosAcEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00130200	C�������й�����*/   
	{C_End_CRevAcEn,						C_NormalRead,				CLPosA_Ac_En_0},					/*0x00230200	C�෴���й�����*/   
	{C_End_CComRe1En,						C_NormalRead,				CLPosA_Ac_En_0},					/*0x00330200	C������޹�1�ܵ���*/
	{C_End_CComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00430200	C������޹�2�ܵ���*/
};
#define EventTable2_RelateOAD0405_Len  ( sizeof(EventTable2_RelateOAD0405) / sizeof(Str_EventChange_Table2) )
/*���˳�������������*/
const Str_EventChange_Table2 EventTable2_RelateOAD00[] =  /**********ʧѹ/Ƿѹ/��ѹ���������б�***************/
{
/*��Ӧ��698���������б�                  �����������ȡ��־��	*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0201	�¼�����ʱ�� 645   6�ֽ�*/                                      	
	{C_HP_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00102201	�����й��ܵ���*/        
	{C_HP_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00202201	�����й��ܵ���*/        
	{C_HP_ComRe1TolEn,						C_NormalRead,				CLCom_Re1_Tol_En_0},				/*0x00302201	����޹�1�ܵ���*/   
	{C_HP_ComRe2TolEn,						C_NormalRead,				CLCom_Re2_Tol_En_0},				/*0x00402201	����޹�2�ܵ���*/   
	{C_HP_APosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00112201	A�������й�����*/   
	{C_HP_ARevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00212201	A�෴���й�����*/   
	{C_HP_AComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00312201	A������޹�1�ܵ���*/
	{C_HP_AComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00412201	A������޹�2�ܵ���*/
	{(CPhaseFF_Volage|C_EventHappen),		C_ReadDeal_A,				CLPhaseA_Volage},					/*0x20002200	*/
	{(CPhaseFF_Curr|C_EventHappen),			C_ReadDeal_A,				CLPhaseA_Curr},						/*0x20012200	*/
	{(CInstantFF_AcPow|C_EventHappen),		C_ReadDeal_B,				CLInstantA_AcPow},					/*0x20042200	*/
	{(CInstantFF_RePow|C_EventHappen),		C_ReadDeal_B,				CLInstantA_AcPow},					/*0x20052200	*/
	{(CPhaseFF_PowerFactor|C_EventHappen),	C_ReadDeal_B,				CLPhaseA_PowerFactor},				/*0x200A2200	*/
	{C_HP_BPosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00122200	B�������й�����*/   
	{C_HP_BRevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00222200	B�෴���й�����*/   
	{C_HP_BComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00322200	B������޹�1�ܵ���*/
	{C_HP_BComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00422200	B������޹�2�ܵ���*/
	{(CPhaseFF_Volage|C_EventHappen),		C_ReadDeal_B,				CLPhaseA_Volage},					/*0x20002200	*/
	{(CPhaseFF_Curr|C_EventHappen),			C_ReadDeal_B,				CLPhaseA_Curr},						/*0x20012200	*/
	{(CInstantFF_AcPow|C_EventHappen),		C_ReadDeal_C,				CLInstantA_AcPow},					/*0x20042200	*/
	{(CInstantFF_RePow|C_EventHappen),		C_ReadDeal_C,				CLInstantA_AcPow},					/*0x20052200	*/
	{(CPhaseFF_PowerFactor|C_EventHappen),	C_ReadDeal_C,				CLPhaseA_PowerFactor},				/*0x200A2200	*/
	{C_HP_CPosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00130200	C�������й�����*/   
	{C_HP_CRevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00230200	C�෴���й�����*/   
	{C_HP_CComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00330200	C������޹�1�ܵ���*/
	{C_HP_CComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00430200	C������޹�2�ܵ���*/
	{(CPhaseFF_Volage|C_EventHappen),		C_ReadDeal_C,				CLPhaseA_Volage},					/*0x20002200	*/
	{(CPhaseFF_Curr|C_EventHappen),			C_ReadDeal_C,				CLPhaseA_Curr},						/*0x20012200	*/
	{(CInstantFF_AcPow|C_EventHappen),		C_ReadDeal_D,				CLInstantA_AcPow},					/*0x20042200	*/
	{(CInstantFF_RePow|C_EventHappen),		C_ReadDeal_D,				CLInstantA_AcPow},					/*0x20052200	*/
	{(CPhaseFF_PowerFactor|C_EventHappen),	C_ReadDeal_D,				CLPhaseA_PowerFactor},				/*0x200A2200	*/
	{(C_AhNature2|C_EventHappening),		C_ReadDeal_A,				4},									/*0x20292200	*/
	{(C_AhNature2|C_EventHappening),		C_ReadDeal_B,				4},									/*0x20296200	*/
	{(C_AhNature2|C_EventHappening),		C_ReadDeal_C,				4},									/*0x20296200	*/
	{(C_AhNature2|C_EventHappening),		C_ReadDeal_D,				4},									/*0x20296200	*/
	{(CEventEndTime),						C_NormalRead,				(CLEventEndTime-1)},				/*0X20200200	�¼�����ʱ��645 6�ֽ�*/
	{C_End_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00100200	�����й��ܵ���*/        
	{C_End_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00200200	�����й��ܵ���*/        
	{C_End_ComRe1TolEn,						C_NormalRead,				CLCom_Re1_Tol_En_0},				/*0x00300200	����޹�1�ܵ���*/   
	{C_End_ComRe2TolEn,						C_NormalRead,				CLCom_Re2_Tol_En_0},				/*0x00400200	����޹�2�ܵ���*/   
	{C_End_APosAcEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00110200	A�������й�����*/   
	{C_End_ARevAcEn,						C_NormalRead,				CLPosA_Ac_En_0},					/*0x00210200	A�෴���й�����*/   
	{C_End_AComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00310200	A������޹�1�ܵ���*/
	{C_End_AComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00410200	A������޹�2�ܵ���*/
	{C_End_BPosAcEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00122200	B�������й�����*/   
	{C_End_BRevAcEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00222200	B�෴���й�����*/   
	{C_End_BComRe1En,						C_NormalRead,				CLCom_Re1_Tol_En_0},				/*0x00322200	B������޹�1�ܵ���*/
	{C_End_BComRe2En,						C_NormalRead,				CLCom_Re2_Tol_En_0},				/*0x00422200	B������޹�2�ܵ���*/
	{C_End_CPosAcEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00130200	C�������й�����*/   
	{C_End_CRevAcEn,						C_NormalRead,				CLPosA_Ac_En_0},					/*0x00230200	C�෴���й�����*/   
	{C_End_CComRe1En,						C_NormalRead,				CLPosA_Ac_En_0},					/*0x00330200	C������޹�1�ܵ���*/
	{C_End_CComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00430200	C������޹�2�ܵ���*/
};
#define EventTable2_RelateOAD00_Len  ( sizeof(EventTable2_RelateOAD00) /sizeof(Str_EventChange_Table2) )
/*���˳�������������	*/
const Str_EventChange_Table2 EventTable2_RelateOAD1B[] =  /**********����ǹ��������б�***************/
{
/*��Ӧ��698���������б�                  �����������ȡ��־��	*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0200	�¼�����ʱ��*/
	{CEventEndTime,							C_NormalRead,				(CLEventEndTime-1)},				/*0X20200200	�¼�����ʱ��*/
	{C_HP_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00102200	�����й��ܵ���*/        
	{C_HP_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00202200	�����й��ܵ���*/
	{C_Hp_TQuadrant1En,						C_NormalRead,				CLQua1_Re_T1_En_0},					/*0x00502201	�¼�����ʱ�̵�һ�����޹��ܵ���*/
	{C_Hp_TQuadrant2En,						C_NormalRead,				CLQua1_Re_T2_En_0},					/*0x00602201	�¼�����ʱ�̵ڶ������޹��ܵ���*/
	{C_Hp_TQuadrant3En,						C_NormalRead,				CLQua1_Re_T3_En_0},					/*0x00702201	�¼�����ʱ�̵��������޹��ܵ���*/
	{C_Hp_TQuadrant4En,						C_NormalRead,				CLQua1_Re_T4_En_0},					/*0x00802201	�¼�����ʱ�̵��������޹��ܵ���*/
	{C_End_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00108201	�¼�����ʱ�������й��ܵ���*/   
	{C_End_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00208201	�¼�����ʱ�̷����й��ܵ���*/   
	{C_End_TQuadrant1En,					C_NormalRead,				CLQua1_Re_T1_En_0},					/*0x00508201	�¼�����ʱ�̵�һ�����޹��ܵ���*/
	{C_End_TQuadrant2En,					C_NormalRead,				CLQua1_Re_T2_En_0},					/*0x00608201	�¼�����ʱ�̵ڶ������޹��ܵ���*/
	{C_End_TQuadrant3En,					C_NormalRead,				CLQua1_Re_T3_En_0},					/*0x00708201	�¼�����ʱ�̵��������޹��ܵ���*/
	{C_End_TQuadrant4En,					C_NormalRead,				CLQua1_Re_T4_En_0},					/*0x00808201	�¼�����ʱ�̵��������޹��ܵ���*/	
};
#define EventTable2_RelateOAD1B_Len  ( sizeof(EventTable2_RelateOAD1B) / sizeof(Str_EventChange_Table2) )
/*���˳�������������	*/
const Str_EventChange_Table2 EventTable2_RelateOAD2A[] =  /**********�㶨�ų����Ź��������б�***************/
{
/*��Ӧ��698���������б�                  �����������ȡ��־��	*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0201	�¼�����ʱ��*/
	{CEventEndTime,							C_NormalRead,				(CLEventEndTime-1)},				/*0X20200201	�¼�����ʱ��*/
	{C_HP_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00102201	�¼�����ʱ�������й��ܵ���*/        
	{C_HP_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00202201	�¼�����ʱ�̷����й��ܵ���*/
	{C_End_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00108201	�¼�����ʱ�������й��ܵ���*/   
	{C_End_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00208201	�¼�����ʱ�̷����й��ܵ���*/   
};
#define EventTable2_RelateOAD2A_Len  (sizeof(EventTable2_RelateOAD2A)/sizeof(Str_EventChange_Table2))

/*���˳�������������	*/
const Str_EventChange_Table2 EventTable2_RelateOAD11[]=  /**********������������б�***************/
{
/*��Ӧ��698���������б�                  �����������ȡ��־��	*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)	},				/*0x201E0201	�¼�����ʱ��*/
	{CEventEndTime,							C_NormalRead,				(CLEventEndTime-1)	},				/*0X20200201	�¼�����ʱ��*/
};
#define EventTable2_RelateOAD11_Len  ( sizeof(EventTable2_RelateOAD11) / sizeof(Str_EventChange_Table2) )


/*���˳�������������	*/
const Str_EventChange_Table2 EventTable2_RelateOAD2C[] =  /**********��Դ�쳣���������б�***************/
{
/*��Ӧ��698���������б�                �����������ȡ��־��	                             	*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0201	�¼�����ʱ��*/
	{CEventEndTime,							C_NormalRead,				(CLEventEndTime-1)},				/*0X20200201	�¼�����ʱ��*/
	{C_HP_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00102201	�¼�����ʱ�������й��ܵ���*/        
	{C_HP_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00202201	�¼�����ʱ�̷����й��ܵ���*/
};
#define EventTable2_RelateOAD2C_Len  ( sizeof(EventTable2_RelateOAD2C) / sizeof(Str_EventChange_Table2) )

/*���˳�������������	*/
const Str_EventChange_Table2 EventTable2_RelateOAD1F20[] =  /**********��բ���������б�***************/
{
/*��Ӧ��698���������б�            �����������ȡ��־��	*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0201	�¼�����ʱ��*/
	{CRelayOpen_OpeCode_1,					C_NormalRead,				CLRelayOpen_OpeCode_1},				/*0X1D000201	�����ߴ���*/
	{C_HP_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00102201	�¼�����ʱ�������й��ܵ���*/        
	{C_HP_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00202201	�¼�����ʱ�̷����й��ܵ���*/
	{C_Hp_TQuadrant1En,						C_NormalRead,				CLQua1_Re_T1_En_0},					/*0x00502201	�¼�����ʱ�̵�һ�����޹��ܵ���*/
	{C_Hp_TQuadrant2En,						C_NormalRead,				CLQua1_Re_T2_En_0},					/*0x00602201	�¼�����ʱ�̵ڶ������޹��ܵ���*/
	{C_Hp_TQuadrant3En,						C_NormalRead,				CLQua1_Re_T3_En_0},					/*0x00702201	�¼�����ʱ�̵��������޹��ܵ���*/
	{C_Hp_TQuadrant4En,						C_NormalRead,				CLQua1_Re_T4_En_0},					/*0x00802201	�¼�����ʱ�̵��������޹��ܵ���*/
};
#define EventTable2_RelateOAD1F20_Len  ( sizeof(EventTable2_RelateOAD1F20) / sizeof(Str_EventChange_Table2) )

/*���˳�������������	*/
const Str_EventChange_Table2 EventTable2_RelateOAD13[] =  /**********���������������б�***************/
{
/*��Ӧ��698���������б�  �����������ȡ��־��	*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0201	�¼�����ʱ��*/
	{CRelayOpen_OpeCode_1,					C_NormalRead,				CLRelayOpen_OpeCode_1},				/*0X1D000201	�����ߴ���*/
	{C_HP_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00102201	�¼�����ʱ�������й��ܵ���*/        
	{C_HP_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00202201	�¼�����ʱ�̷����й��ܵ���*/
	{C_Hp_TQuadrant1En,						C_NormalRead,				CLQua1_Re_T1_En_0},					/*0x00502201	�¼�����ʱ�̵�һ�����޹��ܵ���*/
	{C_Hp_TQuadrant2En,						C_NormalRead,				CLQua1_Re_T2_En_0},					/*0x00602201	�¼�����ʱ�̵ڶ������޹��ܵ���*/
	{C_Hp_TQuadrant3En,						C_NormalRead,				CLQua1_Re_T3_En_0},					/*0x00702201	�¼�����ʱ�̵��������޹��ܵ���*/
	{C_Hp_TQuadrant4En,						C_NormalRead,				CLQua1_Re_T4_En_0},					/*0x00802201	�¼�����ʱ�̵��������޹��ܵ���*/
	{C_HP_APosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00112201	A�������й�����*/   
	{C_HP_ARevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00212201	A�෴���й�����*/   
	{C_Hp_AQuadrant1En,						C_NormalRead,				CLQua1A_Re_En_0},					/*0x00512201	�¼�����ʱ��A���һ�����޹��ܵ���*/
	{C_Hp_AQuadrant2En,						C_NormalRead,				CLQua2A_Re_En_0},					/*0x00612201	�¼�����ʱ��A��ڶ������޹��ܵ���*/
	{C_Hp_AQuadrant3En,						C_NormalRead,				CLQua3A_Re_En_0},					/*0x00712201	�¼�����ʱ��A����������޹��ܵ���*/
	{C_Hp_AQuadrant4En,						C_NormalRead,				CLQua4A_Re_En_0},					/*0x00812201	�¼�����ʱ��A����������޹��ܵ���*/
	{C_HP_BPosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00122200	B�������й�����*/   
	{C_HP_BRevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00222200	B�෴���й�����*/   
	{C_Hp_BQuadrant1En,						C_NormalRead,				CLQua1B_Re_En_0},					/*0x00522201	�¼�����ʱ��B���һ�����޹��ܵ���*/ 
	{C_Hp_BQuadrant2En,						C_NormalRead,				CLQua2B_Re_En_0},					/*0x00622201	�¼�����ʱ��B��ڶ������޹��ܵ���*/ 
	{C_Hp_BQuadrant3En,						C_NormalRead,				CLQua3B_Re_En_0},					/*0x00722201	�¼�����ʱ��B����������޹��ܵ���*/ 
	{C_Hp_BQuadrant4En,						C_NormalRead,				CLQua4B_Re_En_0},					/*0x00822201	�¼�����ʱ��B����������޹��ܵ���*/ 
	{C_HP_CPosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00130200	C�������й�����*/   
	{C_HP_CRevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00230200	C�෴���й�����*/   
	{C_Hp_CQuadrant1En,						C_NormalRead,				CLQua1C_Re_En_0},					/*0x00532201	�¼�����ʱ��C���һ�����޹��ܵ���*/
	{C_Hp_CQuadrant2En,						C_NormalRead,				CLQua2C_Re_En_0},					/*0x00632201	�¼�����ʱ��C��ڶ������޹��ܵ���*/
	{C_Hp_CQuadrant3En,						C_NormalRead,				CLQua3C_Re_En_0},					/*0x00732201	�¼�����ʱ��C����������޹��ܵ���*/
	{C_Hp_CQuadrant4En,						C_NormalRead,				CLQua4C_Re_En_0},					/*0x00832201	�¼�����ʱ��C����������޹��ܵ���*/
};
#define EventTable2_RelateOAD13_Len  ( sizeof(EventTable2_RelateOAD13) / sizeof(Str_EventChange_Table2) )


/*���˳�������������	*/
const Str_EventChange_Table2 EventTable2_RelateOAD14_E1[] =  /**********����������������б�***************/
{
/*��Ӧ��698���������б�            		�����������ȡ��־��	*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0201	�¼�����ʱ��*/
	{CRelayOpen_OpeCode_1,					C_NormalRead,				CLRelayOpen_OpeCode_1},				/*0X1D000201	�����ߴ���*/
	{C_HP_PosAcTolDe,						C_NormalRead,				CLPos_Ac_Tol_De_0},					/*0x10102201	�¼�����ʱ�������й��������������ʱ��*/  
	{C_HP_RevAcTolDe,						C_NormalRead,				CLRev_Ac_Tol_De_0},					/*0x10202201	�¼�����ʱ�̷����й��������������ʱ��*/ 
	{C_Hp_TQuadrant1De,						C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10502201	�¼�����ʱ�̵�һ�����޹����������������ʱ��*/ 
	{C_Hp_TQuadrant2De,						C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10602201	�¼�����ʱ�̵ڶ������޹����������������ʱ��*/ 
	{C_Hp_TQuadrant3De,						C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10702201	�¼�����ʱ�̵��������޹����������������ʱ��*/
	{C_Hp_TQuadrant4De,						C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10802201	�¼�����ʱ�̵��������޹����������������ʱ��*/
};
#define EventTable2_RelateOAD14_E1_Len  ( sizeof(EventTable2_RelateOAD14_E1) / sizeof(Str_EventChange_Table2) )

/*���˳�������������	*/
const Str_EventChange_Table2 EventTable2_RelateOAD14_F1[] =  /**********����������������б�***************/
{
/*��Ӧ��698���������б�            		�����������ȡ��־��	*/
	{C_HP_APosAcDe,							C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10112201	�¼�����ʱ��A�������й��������������ʱ��*/
	{C_HP_ARevAcDe,							C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10212201	�¼�����ʱ��A�෴���й��������������ʱ��*/
	{C_Hp_AQuadrant1De,						C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10512201	�¼�����ʱ��A���һ�����޹����������������ʱ��*/
	{C_Hp_AQuadrant2De,						C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10612201	�¼�����ʱ��A��ڶ������޹����������������ʱ��*/
	{C_Hp_AQuadrant3De,						C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10712201	�¼�����ʱ��A����������޹����������������ʱ��*/
	{C_Hp_AQuadrant4De,						C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10812201	�¼�����ʱ��A����������޹����������������ʱ��*/
	{C_HP_BPosAcDe,							C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10122201	�¼�����ʱ��B�������й��������������ʱ��*/
	{C_HP_BRevAcDe,							C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10222201	�¼�����ʱ��B�෴���й��������������ʱ��*/
	{C_Hp_BQuadrant1De,						C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10522201	�¼�����ʱ��B���һ�����޹����������������ʱ��*/ 
	{C_Hp_BQuadrant2De,						C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10622201	�¼�����ʱ��B��ڶ������޹����������������ʱ��*/ 
	{C_Hp_BQuadrant3De,						C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10722201	�¼�����ʱ��B����������޹����������������ʱ��*/ 
	{C_Hp_BQuadrant4De,						C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10822201	�¼�����ʱ��B����������޹����������������ʱ��*/ 
	{C_HP_CPosAcDe,							C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10132201	�¼�����ʱ��C�������й��������������ʱ��*/
	{C_HP_CRevAcDe,							C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10232201	�¼�����ʱ��C�෴���й��������������ʱ��*/
	{C_Hp_CQuadrant1De,						C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10532201	�¼�����ʱ��C���һ�����޹����������������ʱ��*/
	{C_Hp_CQuadrant2De,						C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10632201	�¼�����ʱ��C��ڶ������޹����������������ʱ��*/
	{C_Hp_CQuadrant3De,						C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10732201	�¼�����ʱ��C����������޹����������������ʱ��*/
	{C_Hp_CQuadrant4De,						C_NormalRead,				CLQua1_Re_Tol_De_0},				/*0x10832201	�¼�����ʱ��C����������޹����������������ʱ��*/                    
};
#define EventTable2_RelateOAD14_F1_Len  ( sizeof(EventTable2_RelateOAD14_F1) / sizeof(Str_EventChange_Table2) )


/*���˳�������������	*/
const Str_EventChange_Table2 EventTable2_RelateOAD15[] =  /**********�¼�������������б�***************/
{
/*��Ӧ��698���������б�            		�����������ȡ��־��	*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0201	�¼�����ʱ��*/
	{CRelayOpen_OpeCode_1,					C_NormalRead,				CLRelayOpen_OpeCode_1},				/*0X1D000201	�����ߴ���*/
	{0x330C0206,							C_NormalRead,				4},									/*�������ݱ�ʶ      */
};
#define EventTable2_RelateOAD15_Len  ( sizeof(EventTable2_RelateOAD15) / sizeof(Str_EventChange_Table2) )

/*���˳�������������	*/
const Str_EventChange_Table2 EventTable2_RelateOAD2B[] =  /**********���ɿ����������������б�***************/
{
/*��Ӧ��698���������б�            		�����������ȡ��־��	*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0201	�¼�����ʱ��*/  
	{CEventEndTime,							C_NormalRead,				(CLEventEndTime-1)},				/*0X20200201	�¼�����ʱ��*/    
	{0xF2052201,							C_ReadDeal_F,				1},									/*0XF2052201 	���ɿ�������ʱ״̬*/
	{C_HP_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00102201	�¼�����ʱ�������й��ܵ���*/  
	{C_HP_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00202201	�¼�����ʱ�̷����й��ܵ���*/ 
	{C_End_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00108201	�¼�����ʱ�������й��ܵ���*/   
	{C_End_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00208201	�¼�����ʱ�̷����й��ܵ���*/   	
};
#define EventTable2_RelateOAD2B_Len  (sizeof(EventTable2_RelateOAD2B)/sizeof(Str_EventChange_Table2))

/*���˳�������������	*/
const Str_EventChange_Table2 EventTable2_RelateOAD0F[] =  /**********��ѹ��������������б�***************/
{
/*��Ӧ��698���������б�            		�����������ȡ��־��	*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0201	�¼�����ʱ��645   6�ֽ�*/                                      	
	{C_HP_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00102201	�����й��ܵ���*/        
	{C_HP_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00202201	�����й��ܵ���*/        
	{C_HP_ComRe1TolEn,						C_NormalRead,				CLCom_Re1_Tol_En_0},				/*0x00302201	����޹�1�ܵ���*/   
	{C_HP_ComRe2TolEn,						C_NormalRead,				CLCom_Re2_Tol_En_0},				/*0x00402201	����޹�2�ܵ���*/   
	{C_HP_APosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00112201	A�������й�����*/   
	{C_HP_ARevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00212201	A�෴���й�����*/   
	{C_HP_AComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00312201	A������޹�1�ܵ���*/
	{C_HP_AComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00412201	A������޹�2�ܵ���*/
	{C_HP_BPosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00122200	B�������й�����*/   
	{C_HP_BRevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00222200	B�෴���й�����*/   
	{C_HP_BComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00322200	B������޹�1�ܵ���*/
	{C_HP_BComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00422200	B������޹�2�ܵ���*/
	{C_HP_CPosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00130200	C�������й�����*/   
	{C_HP_CRevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00230200	C�෴���й�����*/   
	{C_HP_CComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00330200	C������޹�1�ܵ���*/
	{C_HP_CComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00430200	C������޹�2�ܵ���*/
	{(CEventEndTime),						C_NormalRead,				(CLEventEndTime-1)},				/*0X20200200	�¼�����ʱ��645 6�ֽ�*/
	{C_End_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00100200	�����й��ܵ���*/        
	{C_End_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00200200	�����й��ܵ���*/        
	{C_End_ComRe1TolEn,						C_NormalRead,				CLCom_Re1_Tol_En_0},				/*0x00300200	����޹�1�ܵ���*/   
	{C_End_ComRe2TolEn,						C_NormalRead,				CLCom_Re2_Tol_En_0},				/*0x00400200	����޹�2�ܵ���*/   
	{C_End_APosAcEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00110200	A�������й�����*/   
	{C_End_ARevAcEn,						C_NormalRead,				CLPosA_Ac_En_0},					/*0x00210200	A�෴���й�����*/   
	{C_End_AComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00310200	A������޹�1�ܵ���*/
	{C_End_AComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00410200	A������޹�2�ܵ���*/
	{C_End_BPosAcEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00122200	B�������й�����*/   
	{C_End_BRevAcEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00222200	B�෴���й�����*/   
	{C_End_BComRe1En,						C_NormalRead,				CLCom_Re1_Tol_En_0},				/*0x00322200	B������޹�1�ܵ���*/
	{C_End_BComRe2En,						C_NormalRead,				CLCom_Re2_Tol_En_0},				/*0x00422200	B������޹�2�ܵ���*/
	{C_End_CPosAcEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00130200	C�������й�����*/   
	{C_End_CRevAcEn,						C_NormalRead,				CLPosA_Ac_En_0},					/*0x00230200	C�෴���й�����*/   
	{C_End_CComRe1En,						C_NormalRead,				CLPosA_Ac_En_0},					/*0x00330200	C������޹�1�ܵ���*/
	{C_End_CComRe2En,						C_NormalRead,				CLComA_Re2_En_0},    	//0x00430200	C������޹�2�ܵ���*/
};
#define EventTable2_RelateOAD0F_Len  ( sizeof(EventTable2_RelateOAD0F) / sizeof(Str_EventChange_Table2) )

/*���˳�������������	*/
const Str_EventChange_Table2 EventTable2_RelateOAD1D[] =  /**********��ѹ��ƽ����������б�***************/
{
/*��Ӧ��698���������б�            		�����������ȡ��־��	*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0201	�¼�����ʱ��645   6�ֽ�*/                                      	
	{C_HP_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00102201	�����й��ܵ���*/        
	{C_HP_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00202201	�����й��ܵ���*/        
	{C_HP_ComRe1TolEn,						C_NormalRead,				CLCom_Re1_Tol_En_0},				/*0x00302201	����޹�1�ܵ���*/   
	{C_HP_ComRe2TolEn,						C_NormalRead,				CLCom_Re2_Tol_En_0},				/*0x00402201	����޹�2�ܵ���*/   
	{C_HP_APosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00112201	A�������й�����*/   
	{C_HP_ARevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00212201	A�෴���й�����*/   
	{C_HP_AComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00312201	A������޹�1�ܵ���*/
	{C_HP_AComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00412201	A������޹�2�ܵ���*/
	{C_HP_BPosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00122200	B�������й�����*/   
	{C_HP_BRevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00222200	B�෴���й�����*/   
	{C_HP_BComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00322200	B������޹�1�ܵ���*/
	{C_HP_BComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00422200	B������޹�2�ܵ���*/
	{C_HP_CPosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00130200	C�������й�����*/   
	{C_HP_CRevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00230200	C�෴���й�����*/   
	{C_HP_CComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00330200	C������޹�1�ܵ���*/
	{C_HP_CComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00430200	C������޹�2�ܵ���*/
	{C_VolUnbalanceRate_E,					C_NormalRead,				CLNoBalRate_Vol_End_1},				/*��ѹ��ƽ�����ƽ����*/ 
	{(CEventEndTime),						C_NormalRead,				(CLEventEndTime-1)},				/*0X20200200  �¼�����ʱ��645 6�ֽ�*/
	{C_End_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00100200	�����й��ܵ���*/        
	{C_End_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00200200	�����й��ܵ���*/        
	{C_End_ComRe1TolEn,						C_NormalRead,				CLCom_Re1_Tol_En_0},				/*0x00300200	����޹�1�ܵ���*/   
	{C_End_ComRe2TolEn,						C_NormalRead,				CLCom_Re2_Tol_En_0},				/*0x00400200	����޹�2�ܵ���*/   
	{C_End_APosAcEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00110200	A�������й�����*/   
	{C_End_ARevAcEn,						C_NormalRead,				CLPosA_Ac_En_0},					/*0x00210200	A�෴���й�����*/   
	{C_End_AComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00310200	A������޹�1�ܵ���*/
	{C_End_AComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00410200	A������޹�2�ܵ���*/
	{C_End_BPosAcEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00122200	B�������й�����*/   
	{C_End_BRevAcEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00222200	B�෴���й�����*/   
	{C_End_BComRe1En,						C_NormalRead,				CLCom_Re1_Tol_En_0},				/*0x00322200	B������޹�1�ܵ���*/
	{C_End_BComRe2En,						C_NormalRead,				CLCom_Re2_Tol_En_0},				/*0x00422200	B������޹�2�ܵ���*/
	{C_End_CPosAcEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00130200	C�������й�����*/   
	{C_End_CRevAcEn,						C_NormalRead,				CLPosA_Ac_En_0},					/*0x00230200	C�෴���й�����*/   
	{C_End_CComRe1En,						C_NormalRead,				CLPosA_Ac_En_0},					/*0x00330200	C������޹�1�ܵ���*/
	{C_End_CComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00430200	C������޹�2�ܵ���*/
};
#define EventTable2_RelateOAD1D_Len  ( sizeof(EventTable2_RelateOAD1D) / sizeof(Str_EventChange_Table2) )
/*���˳�������������	*/
const Str_EventChange_Table2 EventTable2_RelateOAD17[] =  /**********������ƽ����������б�***************/
{
/*��Ӧ��698���������б�            		�����������ȡ��־��	*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0201	�¼�����ʱ��645   6�ֽ�*/                                      	
	{C_HP_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00102201	�����й��ܵ���*/        
	{C_HP_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00202201	�����й��ܵ���*/        
	{C_HP_ComRe1TolEn,						C_NormalRead,				CLCom_Re1_Tol_En_0},				/*0x00302201	����޹�1�ܵ���*/   
	{C_HP_ComRe2TolEn,						C_NormalRead,				CLCom_Re2_Tol_En_0},				/*0x00402201	����޹�2�ܵ���*/   
	{C_HP_APosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00112201	A�������й�����*/   
	{C_HP_ARevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00212201	A�෴���й�����*/   
	{C_HP_AComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00312201	A������޹�1�ܵ���*/
	{C_HP_AComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00412201	A������޹�2�ܵ���*/
	{C_HP_BPosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00122200	B�������й�����*/   
	{C_HP_BRevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00222200	B�෴���й�����*/   
	{C_HP_BComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00322200	B������޹�1�ܵ���*/
	{C_HP_BComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00422200	B������޹�2�ܵ���*/
	{C_HP_CPosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00130200	C�������й�����*/   
	{C_HP_CRevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00230200	C�෴���й�����*/   
	{C_HP_CComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00330200	C������޹�1�ܵ���*/
	{C_HP_CComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00430200	C������޹�2�ܵ���*/
	{C_CurUnbalanceRate_E,					C_NormalRead,				CLNoBalRate_Curr_1},				/*������ƽ�����ƽ����*/ 
	{(CEventEndTime),						C_NormalRead,				(CLEventEndTime-1)},				/*0X20200200  �¼�����ʱ��645 6�ֽ�*/
	{C_End_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00100200	�����й��ܵ���*/        
	{C_End_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00200200	�����й��ܵ���*/        
	{C_End_ComRe1TolEn,						C_NormalRead,				CLCom_Re1_Tol_En_0},				/*0x00300200	����޹�1�ܵ���*/   
	{C_End_ComRe2TolEn,						C_NormalRead,				CLCom_Re2_Tol_En_0},				/*0x00400200	����޹�2�ܵ���*/   
	{C_End_APosAcEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00110200	A�������й�����*/   
	{C_End_ARevAcEn,						C_NormalRead,				CLPosA_Ac_En_0},					/*0x00210200	A�෴���й�����*/   
	{C_End_AComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00310200	A������޹�1�ܵ���*/
	{C_End_AComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00410200	A������޹�2�ܵ���*/
	{C_End_BPosAcEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00122200	B�������й�����*/   
	{C_End_BRevAcEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00222200	B�෴���й�����*/   
	{C_End_BComRe1En,						C_NormalRead,				CLCom_Re1_Tol_En_0},				/*0x00322200	B������޹�1�ܵ���*/
	{C_End_BComRe2En,						C_NormalRead,				CLCom_Re2_Tol_En_0},				/*0x00422200	B������޹�2�ܵ���*/
	{C_End_CPosAcEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00130200	C�������й�����*/   
	{C_End_CRevAcEn,						C_NormalRead,				CLPosA_Ac_En_0},					/*0x00230200	C�෴���й�����*/   
	{C_End_CComRe1En,						C_NormalRead,				CLPosA_Ac_En_0},					/*0x00330200	C������޹�1�ܵ���*/
	{C_End_CComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00430200	C������޹�2�ܵ���*/
};
#define EventTable2_RelateOAD17_Len  ( sizeof(EventTable2_RelateOAD17) / sizeof(Str_EventChange_Table2) )


/*���˳�������������	*/
const Str_EventChange_Table2 EventTable2_RelateOAD0D[] =  /**********ȫʧѹ���������б�***************/
{
/*��Ӧ��698���������б�            		�����������ȡ��־��	*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0201	�¼�����ʱ��*/  
	{C_HP_Curr,								C_ReadDeal_E,				3},      							/*0x20012200	�¼�����ʱ�̵���ֵ*/
	{CEventEndTime,							C_NormalRead,				(CLEventEndTime-1)},				/*0X20200201	�¼�����ʱ��*/    
};
#define EventTable2_RelateOAD0D_Len  ( sizeof(EventTable2_RelateOAD0D) / sizeof(Str_EventChange_Table2) )
/*���˳�������������	*/
const Str_EventChange_Table2 EventTable2_RelateOAD16[] =  /**********Уʱ���������б�***************/
{
/*��Ӧ��698���������б�            		�����������ȡ��־��	*/
	{CRelayOpen_OpeCode_1,					C_NormalRead,				CLRelayOpen_OpeCode_1},				/*0X1D000201  	�����ߴ���*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0201	�¼�����ʱ��*/  
	{CEventEndTime,							C_NormalRead,				(CLEventEndTime-1)},				/*0X20200201  �¼�����ʱ��*/    
};
#define EventTable2_RelateOAD16_Len  ( sizeof(EventTable2_RelateOAD16) / sizeof(Str_EventChange_Table2) )


/*���˳�������������	*/
const Str_EventChange_Table2 EventTable2_RelateOAD1A[] =  /**********�����ձ�̹��������б�***************/
{
/*��Ӧ��698���������б�            		�����������ȡ��־��	*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0201	�¼�����ʱ��*/  
	{CRelayOpen_OpeCode_1,					C_NormalRead,   			CLRelayOpen_OpeCode_1},				/*0X1D000201  	�����ߴ���*/
	{C_SettleDatebeforePro,					C_NormalRead,				CLSettleDatebeforePro},				/*0x41162200	���ǰ������*/  
};
#define EventTable2_RelateOAD1A_Len  ( sizeof(EventTable2_RelateOAD1A) / sizeof(Str_EventChange_Table2) )


/*���˳�������������	*/
const Str_EventChange_Table2 EventTable2_RelateOAD18[] =  /**********ʱ�����̹��������б�***************/
{
/*��Ӧ��698���������б�            		�����������ȡ��־��	*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0201	�¼�����ʱ��*/  
	{CRelayOpen_OpeCode_1,					C_NormalRead,				CLRelayOpen_OpeCode_1},				/*0X1D000201  	�����ߴ���*/
	{C_SpareBDayTablePrO,					C_ReadDeal_G,				CLProgTZ_645Comm_Note_OnlyData},	/*0x40152200	ʱ����������*/  
};
#define EventTable2_RelateOAD18_Len  ( sizeof(EventTable2_RelateOAD18) / sizeof(Str_EventChange_Table2) )

#define C_HP_TolPowerCon					0x21FFFFFF
#define CLHP_TolPowerCon					1

/*���˳�������������	*/
const Str_EventChange_Table2 EventTable2_RelateOAD07[] =  /**********��ѹ��������������б�***************/
{
/*��Ӧ��698���������б�            		�����������ȡ��־��	*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0201	�¼�����ʱ��645   6�ֽ�*/                                      	
	{C_HP_TolPowerCon,						C_NormalRead,				CLHP_TolPowerCon},					/*��������������ʱ�ܹ��ʷ���*/
	{C_HP_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00102201	�����й��ܵ���*/        
	{C_HP_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00202201	�����й��ܵ���*/        
	{C_HP_ComRe1TolEn,						C_NormalRead,				CLCom_Re1_Tol_En_0},				/*0x00302201	����޹�1�ܵ���*/   
	{C_HP_ComRe2TolEn,						C_NormalRead,				CLCom_Re2_Tol_En_0},				/*0x00402201	����޹�2�ܵ���*/   
	{C_HP_APosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00112201	A�������й�����*/   
	{C_HP_ARevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00212201	A�෴���й�����*/   
	{C_HP_AComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00312201	A������޹�1�ܵ���*/
	{C_HP_AComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00412201	A������޹�2�ܵ���*/
	{C_HP_BPosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00122200	B�������й�����*/   
	{C_HP_BRevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00222200	B�෴���й�����*/   
	{C_HP_BComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00322200	B������޹�1�ܵ���*/
	{C_HP_BComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00422200	B������޹�2�ܵ���*/
	{C_HP_CPosAcEn,							C_NormalRead,				CLPosA_Ac_En_0},					/*0x00130200	C�������й�����*/   
	{C_HP_CRevAcEn,							C_NormalRead,				CLRevA_Ac_En_0},					/*0x00230200	C�෴���й�����*/   
	{C_HP_CComRe1En,						C_NormalRead,				CLComA_Re1_En_0},					/*0x00330200	C������޹�1�ܵ���*/
	{C_HP_CComRe2En,						C_NormalRead,				CLComA_Re2_En_0},					/*0x00430200	C������޹�2�ܵ���*/
};
#define EventTable2_RelateOAD07_Len  ( sizeof(EventTable2_RelateOAD07) / sizeof(Str_EventChange_Table2) )

/*���˳�������������	*/
const Str_EventChange_Table2 EventTable2_RelateOAD0C[] =  /**********�ܹ������������޹��������б�***************/
{
/*��Ӧ��698���������б�            		�����������ȡ��־��		*/
	{CEventHPTime,							C_NormalRead,				(CLEventHPTime-1)},					/*0x201E0201	�¼�����ʱ��645   6�ֽ�*/                                      	
	{C_HP_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00102201	�����й��ܵ���*/        
	{C_HP_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00202201	�����й��ܵ���*/        
	{C_HP_ComRe1TolEn,						C_NormalRead,				CLCom_Re1_Tol_En_0},				/*0x00302201	����޹�1�ܵ���*/   
	{C_HP_ComRe2TolEn,						C_NormalRead,				CLCom_Re2_Tol_En_0},				/*0x00402201	����޹�2�ܵ���*/   
	{(CEventEndTime),						C_NormalRead,				(CLEventEndTime-1)},				/*0X20200200	�¼�����ʱ��645 6�ֽ�*/
	{C_End_PosAcTolEn,						C_NormalRead,				CLPos_Ac_Tol_En_0},					/*0x00100200	�����й��ܵ���*/        
	{C_End_RevAcTolEn,						C_NormalRead,				CLRev_Ac_Tol_En_0},					/*0x00200200	�����й��ܵ���*/        
	{C_End_ComRe1TolEn,						C_NormalRead,				CLCom_Re1_Tol_En_0},				/*0x00300200	����޹�1�ܵ���*/   
	{C_End_ComRe2TolEn,						C_NormalRead,				CLCom_Re2_Tol_En_0},				/*0x00400200	����޹�2�ܵ���*/   
};
#define EventTable2_RelateOADOC_Len  ( sizeof(EventTable2_RelateOAD0C) / sizeof(Str_EventChange_Table2) )


const Str_EventChange_Table1 EventTable1_OADChange698[] =  
{
/*		DI						OIB         		����     				2������ַ											2��������*/
	{COpenW_Degree,				0x1B,				0x02,			(ulong32)(&EventTable2_RelateOAD1B[0]),				EventTable2_RelateOAD1B_Len},			/*����� */
	{COpenCW_Degree,			0x1C,				0x02,			(ulong32)(&EventTable2_RelateOAD1B[0]),				EventTable2_RelateOAD1B_Len},			/*����ť��  */
	{CConM_Degree,				0x2A,				0x02,			(ulong32)(&EventTable2_RelateOAD2A[0]),				EventTable2_RelateOAD2A_Len},			/*�㶨�ų�*/ 
	{CPow_Down_Degree,			0x11,				0x02,			(ulong32)(&EventTable2_RelateOAD11[0]),				EventTable2_RelateOAD11_Len},			/*����*/
	{CPowerFa_Degree,			0x2C,				0x02,			(ulong32)(&EventTable2_RelateOAD2C[0]),				EventTable2_RelateOAD2C_Len},			/*��Դ�쳣*/
	{CLossA_Vol_Degree,			0x00,				0x07,			(ulong32)(&EventTable2_RelateOAD00[0]),				EventTable2_RelateOAD00_Len},			/*Aʧѹ*/
	{CLossB_Vol_Degree,			0x00,				0x08,			(ulong32)(&EventTable2_RelateOAD00[0]),				EventTable2_RelateOAD00_Len},			/*Bʧѹ*/
	{CLossC_Vol_Degree,			0x00,				0x09,			(ulong32)(&EventTable2_RelateOAD00[0]),				EventTable2_RelateOAD00_Len},			/*Cʧѹ*/
	{CLossA_Curr_Degree,		0x04,				0x07,			(ulong32)(&EventTable2_RelateOAD0405[0]),			EventTable2_RelateOAD0405_Len},			/*Aʧ��*/
	{CLossB_Curr_Degree,		0x04,				0x08,			(ulong32)(&EventTable2_RelateOAD0405[0]),			EventTable2_RelateOAD0405_Len},			/*Bʧ��*/
	{CLossC_Curr_Degree,		0x04,				0x09,			(ulong32)(&EventTable2_RelateOAD0405[0]),			EventTable2_RelateOAD0405_Len},			/*Cʧ��*/
	{COverA_Curr_Degree,		0x05,				0x07,			(ulong32)(&EventTable2_RelateOAD0405[0]),			EventTable2_RelateOAD0405_Len},			/*A����*/
	{COverB_Curr_Degree,		0x05,				0x08,			(ulong32)(&EventTable2_RelateOAD0405[0]),			EventTable2_RelateOAD0405_Len},			/*B����*/
	{COverC_Curr_Degree,		0x05,				0x09,			(ulong32)(&EventTable2_RelateOAD0405[0]),			EventTable2_RelateOAD0405_Len},			/*C����*/
	{CRelayOpen_Degree,			0x1F,				0x02,			(ulong32)(&EventTable2_RelateOAD1F20[0]),			EventTable2_RelateOAD1F20_Len},			/*��բ */  
	{CRelayClose_Degree,		0x20,				0x02,			(ulong32)(&EventTable2_RelateOAD1F20[0]),			EventTable2_RelateOAD1F20_Len},			/*��բ*/
	{CTol_Clear_Degree,			0x13,				0x02,			(ulong32)(&EventTable2_RelateOAD13[0]),				EventTable2_RelateOAD13_Len},			/*������� */
	{CEven_Clear_Degree,		0x15,				0x02,			(ulong32)(&EventTable2_RelateOAD15[0]),				EventTable2_RelateOAD15_Len},			/*�¼����� */ 
	{CRelayFa_Degree,			0x2B,				0x02,			(ulong32)(&EventTable2_RelateOAD2B[0]),				EventTable2_RelateOAD2B_Len},			/*���ɿ�������*/ 
	{CRevPS_Vol_Degree,			0x0F,				0x02,			(ulong32)(&EventTable2_RelateOAD0F[0]),				EventTable2_RelateOAD0F_Len},			/*��ѹ������ */
	{CNoBal_Vol_Degree,			0x1D,				0x02,			(ulong32)(&EventTable2_RelateOAD1D[0]),				EventTable2_RelateOAD1D_Len},			/*��ѹ��ƽ��*/
	{CAdjTime_Degree,			0x16,				0x02,			(ulong32)(&EventTable2_RelateOAD16[0]),				EventTable2_RelateOAD16_Len},			/*Уʱ */
	{CLowA_Vol_Degree,			0x01,				0x07,			(ulong32)(&EventTable2_RelateOAD00[0]),				EventTable2_RelateOAD00_Len},			/*AǷѹ */
	{CLowB_Vol_Degree,			0x01,				0x08,			(ulong32)(&EventTable2_RelateOAD00[0]),				EventTable2_RelateOAD00_Len},			/*BǷѹ */
	{CLowC_Vol_Degree,			0x01,				0x09,			(ulong32)(&EventTable2_RelateOAD00[0]),				EventTable2_RelateOAD00_Len},			/*CǷѹ */
	{COverA_Vol_Degree,			0x02,				0x07,			(ulong32)(&EventTable2_RelateOAD00[0]),				EventTable2_RelateOAD00_Len},			/*A��ѹ */
	{COverB_Vol_Degree,			0x02,				0x08,			(ulong32)(&EventTable2_RelateOAD00[0]),				EventTable2_RelateOAD00_Len},			/*B��ѹ */
	{COverC_Vol_Degree,			0x02,				0x09,			(ulong32)(&EventTable2_RelateOAD00[0]),				EventTable2_RelateOAD00_Len},			/*C��ѹ */
	{0x03050000,				0x0D,				0x02,			(ulong32)(&EventTable2_RelateOAD0D[0]),				EventTable2_RelateOAD0D_Len},			/*ȫʧѹ */
	{CBreakA_Vol_Degree,		0x03,				0x07,			(ulong32)(&EventTable2_RelateOAD00[0]),				EventTable2_RelateOAD00_Len},			/*A���� */
	{CBreakB_Vol_Degree,		0x03,				0x08,			(ulong32)(&EventTable2_RelateOAD00[0]),				EventTable2_RelateOAD00_Len},			/*B���� */
	{CBreakC_Vol_Degree,		0x03,				0x09,			(ulong32)(&EventTable2_RelateOAD00[0]),				EventTable2_RelateOAD00_Len},			/*C���� 	*/
	{CPowerA_Rev_Degree,		0x07,				0x07,			(ulong32)(&EventTable2_RelateOAD0F[0]),				EventTable2_RelateOAD0F_Len},			/*A�й����ʷ��� */
	{CPowerB_Rev_Degree,		0x07,				0x08,			(ulong32)(&EventTable2_RelateOAD0F[0]),				EventTable2_RelateOAD0F_Len},			/*B�й����ʷ���*/
	{CPowerC_Rev_Degree,		0x07,				0x09,			(ulong32)(&EventTable2_RelateOAD0F[0]),				EventTable2_RelateOAD0F_Len},			/*C�й����ʷ���*/
	{CProgSettD_Degree,			0x1A,				0x02,			(ulong32)(&EventTable2_RelateOAD1A[0]),				EventTable2_RelateOAD1A_Len},			/*�����ձ���¼�*/
	{CProgTZ_Degree,			0x18,				0x02,			(ulong32)(&EventTable2_RelateOAD18[0]),				EventTable2_RelateOAD18_Len},			/*ʱ�������¼�*/
	{CPowerT_Rev_Degree,		0x07,				0x06,			(ulong32)(&EventTable2_RelateOAD07[0]),				EventTable2_RelateOAD07_Len},			/*�����������й����ʷ���*/
	{CNoBal_Curr_Degree,		0x1E,				0x02,			(ulong32)(&EventTable2_RelateOAD17[0]),				EventTable2_RelateOAD17_Len},			/*������ƽ��  */
	{CSevNoBal_Curr_Degree,		0x2D,				0x02,			(ulong32)(&EventTable2_RelateOAD17[0]),				EventTable2_RelateOAD17_Len},			/*�������ز�ƽ��*/
	{CRevPS_Curr_Degree,		0x10,				0x02,			(ulong32)(&EventTable2_RelateOAD0F[0]),				EventTable2_RelateOAD0F_Len},			/*����������*/
	{CPFactorT_Over_Degree,		CPFactorT_Over_OIB,	0x06,			(ulong32)(&EventTable2_RelateOAD0C[0]),				EventTable2_RelateOADOC_Len},			/*��������������*/
	{CBreakA_Curr_Degree,		0x06,				0x07,			(ulong32)(&EventTable2_RelateOAD0405[0]),			EventTable2_RelateOAD0405_Len},			/*����A*/
	{CBreakB_Curr_Degree,		0x06,				0x08,			(ulong32)(&EventTable2_RelateOAD0405[0]),			EventTable2_RelateOAD0405_Len},			/*����B*/
	{CBreakC_Curr_Degree,		0x06,				0x09,			(ulong32)(&EventTable2_RelateOAD0405[0]),			EventTable2_RelateOAD0405_Len},			/*����C*/
	{COverA_Lo_Degree,			0x08,				0x07,			(ulong32)(&EventTable2_RelateOAD0F[0]),				EventTable2_RelateOAD0F_Len},			/*����A*/
	{COverB_Lo_Degree,			0x08,				0x08,			(ulong32)(&EventTable2_RelateOAD0F[0]),				EventTable2_RelateOAD0F_Len},			/*����B */
	{COverC_Lo_Degree,			0x08,				0x09,			(ulong32)(&EventTable2_RelateOAD0F[0]),				EventTable2_RelateOAD0F_Len},			/*����C*/
	{CPFactorA_Over_Degree,		CPFactorT_Over_OIB,	0x07,			(ulong32)(&EventTable2_RelateOAD0C[0]),				EventTable2_RelateOADOC_Len},			/*A�๦������������*/
	{CPFactorB_Over_Degree,		CPFactorT_Over_OIB,	0x08,			(ulong32)(&EventTable2_RelateOAD0C[0]),				EventTable2_RelateOADOC_Len},			/*B�๦������������*/
	{CPFactorC_Over_Degree,		CPFactorT_Over_OIB,	0x09,			(ulong32)(&EventTable2_RelateOAD0C[0]),				EventTable2_RelateOADOC_Len},			/*C�๦������������*/
};
#define EventTable1_OADChange698_Len  ( sizeof(EventTable1_OADChange698) / sizeof(Str_EventChange_Table1) )


const Str_ParaChange_OADToDI_Table ParaChange_OADToDI_Table40[] =
{
	{CDate_Time,					CDate_Week_Time_645},				/*ʱ��*/
	{CDay_Table_Num,					CDay_Table_Num_645},    			 
	{CDay_Time_Num,						CDay_Time_Num_645},     			 
	{CRate_Num,							CRate_Num_645},         			 
	{CYear_Zone_Num,					CYear_Zone_Num_645},				/*��ʱ���� */
	{CSettle_Day1,						CSettle_Day1_645},					/*������1*/
	{CSettle_Day2,						CSettle_Day2_645},					/*������1*/
	{CSettle_Day3,						CSettle_Day3_645},					/*������1*/
	{CComm_Address,						CComm_Address_645},					/*ͨ�ŵ�ַ*/
	{CHoliday_Num,						CHoliday_Num_645},
	{CChange_TZ_Time,					CChange_TZ_Time_645},
	{CChange_PT_Time,					CChange_PT_Time_645},
	{CWeek_RestDay,						CWeek_RestDay_645},
	{CWeek_RestDay,						CWeek_RestDay_645},
	{CFirst_TZone_Data,					CFirst_TZone_Data_645},
	{CFirst_TZone_1PT_Data,				CFirst_TZone_1PT_Data_645},
	{CFirst_TZone_2PT_Data,				CFirst_TZone_2PT_Data_645},
	{CFirst_TZone_3PT_Data,				CFirst_TZone_3PT_Data_645},
	{CFirst_TZone_4PT_Data,				CFirst_TZone_4PT_Data_645},
	{CFirst_TZone_5PT_Data,				CFirst_TZone_5PT_Data_645},
	{CFirst_TZone_6PT_Data,				CFirst_TZone_6PT_Data_645},
	{CFirst_TZone_7PT_Data,				CFirst_TZone_7PT_Data_645},
	{CFirst_TZone_8PT_Data,				CFirst_TZone_8PT_Data_645},
	{CSec_TZone_Data,					CSec_TZone_Data_645},
	{CSec_TZone_1PT_Data,				CSec_TZone_1PT_Data_645}, 
	{CSec_TZone_2PT_Data,				CSec_TZone_2PT_Data_645}, 
	{CSec_TZone_3PT_Data,				CSec_TZone_3PT_Data_645},
	{CSec_TZone_4PT_Data,				CSec_TZone_4PT_Data_645}, 
	{CSec_TZone_5PT_Data,				CSec_TZone_5PT_Data_645}, 
	{CSec_TZone_6PT_Data,				CSec_TZone_6PT_Data_645}, 
	{CSec_TZone_7PT_Data,				CSec_TZone_7PT_Data_645}, 
	{CSec_TZone_8PT_Data,				CSec_TZone_8PT_Data_645},                                		
};
#define ParaChange_OADToDI_Table40_Len  ( sizeof(ParaChange_OADToDI_Table40) / sizeof(Str_ParaChange_OADToDI_Table) )

const Str_ParaChange_OADToDI_Table ParaChange_OADToDI_Table41[] =
{
	{CActive_Com_State,					CActive_Com_State_645},
	{CReactive_Com_State1,				CReactive_Com_State1_645},
	{CReactive_Com_State2,				CReactive_Com_State2_645},
	{CSettle_Day1,						CSettle_Day1_645},           
	{CSettle_Day2,						CSettle_Day2_645},
	{CSettle_Day3,						CSettle_Day3_645},
	{CManage_Code,						CManage_Code_645},

};
#define ParaChange_OADToDI_Table41_Len  ( sizeof(ParaChange_OADToDI_Table41) / sizeof(Str_ParaChange_OADToDI_Table) )

const Str_ParaChange_OADToDI_Table ParaChange_OADToDI_Table30[] =
{
	{CLossVolage_Vol_UpLim,				CLossVolage_Vol_UpLim_645},
	{CLossVolage_Vol_LowLim,			CLossVolage_Vol_LowLim_645},
	{CLossVolage_Curr_LowLim,			CLossVolage_Curr_LowLim_645},
	{CLossVolage_Delay_T,				CLossVolage_Delay_T_645},
	{CLowVolage_Vol_UpLim,				CLowVolage_Vol_UpLim_645},
	{CLowVolage_Delay_T,				CLowVolage_Delay_T_645},
	{COverVolage_Vol_LowLim,			COverVolage_Vol_LowLim_645},
	{COverVolage_Delay_T,				COverVolage_Delay_T_645},
	{CBreakVol_Vol_UpLim,				CBreakVol_Vol_UpLim_645},
	{CBreakVol_Curr_UpLim,				CBreakVol_Curr_UpLim_645},
	{CBreakVol_Delay_T,					CBreakVol_Delay_T_645},
	{CNoBal_Vol_Lim,					CNoBal_Vol_Lim_645},
	{CNoBal_Vol_Delay_T,				CNoBal_Vol_Delay_T_645},
	{CNoBal_Curr_Lim,					CNoBal_Curr_Lim_645},
	{CNoBal_Curr_Delay_T,				CNoBal_Curr_Delay_T_645},
	{CSeriNoBal_Curr_Lim,				CSeriNoBal_Curr_Lim_645},
	{CSeriNoBal_Curr_Delay_T,			CSeriNoBal_Curr_Delay_T_645},
	{CLossCurr_Vol_LowLim,				CLossCurr_Vol_LowLim_645},
	{CLossCurr_Curr_UpLim,				CLossCurr_Curr_UpLim_645},
	{CLossCurr_Curr_LowLim,				CLossCurr_Curr_LowLim_645},
	{CLossCurr_Delay_T,					CLossCurr_Delay_T_645},
	{COverCurr_Curr_LowLim,				COverCurr_Curr_LowLim_645},
	{COverCurr_Delay_T,					COverCurr_Delay_T_645},
	{CBreakCurr_Vol_LowLim,				CBreakCurr_Vol_LowLim_645},
	{CBreakCurr_Curr_UpLim,				CBreakCurr_Curr_UpLim_645},
	{CBreakCurr_Delay_T,				CBreakCurr_Delay_T_645},
	{CTrendRev_AcPower_LowLim,			CTrendRev_AcPower_LowLim_645},
	{CTrendRev_Delay_T,					CTrendRev_Delay_T_645},
	{COverLoad_AcPower_LowLim,			COverLoad_AcPower_LowLim_645},
	{COverLoad_Delay_T,					COverLoad_Delay_T_645},
	{CVolage_Check_UpLim,				CVolage_Check_UpLim_645},
	{CVolage_Check_LowLim,				CVolage_Check_LowLim_645},
	{CPosAcDemandOv_De_LowLim,			CAcDemandOv_De_LowLim_645	},
	{CReDemandOv_De_LowLim,				CReDemandOv_De_LowLim_645	},
	{CPosAcDemandOv_Delay_T,			CDemandOv_Delay_T_645	    },
	{CPowerFactor_LowLim,				CPowerFactor_LowLim_645},
	{CPowerFactor_Delay_T,				CPowerFactor_Delay_T_645},
	{CPowerRev_AcPower_LowLim,			CPowerRev_AcPower_LowLim_645},
	{CPowerRev_Delay_T,					CPowerRev_Delay_T_645},
};                          	

#define ParaChange_OADToDI_Table30_Len  ( sizeof(ParaChange_OADToDI_Table30) / sizeof(Str_ParaChange_OADToDI_Table) )

#define C_EventRead_NeedTol_Len 14
const ulong32 C_EventRead_NeedTol[C_EventRead_NeedTol_Len] =   /*645Э���У�û��ÿ�����ݵ�����ȡ   */
{
	0x03300D00,		/*�����*/
	0x03300E00,		/*����ť��*/
	0x03350000,		/*�㶨�ų�����*/
	0x03110000,		/*����*/
	0x03370000,		/*��Դ�쳣*/
	0x03360000,		/*���ɿ�������*/
	0x03300100,		/*�������*/
	0x03300200,		/*��������*/
	0x03300300,		/*�¼�����*/
	0x03300400,		/*Уʱ */
	0x03050000,		/*ȫʧѹ*/
	0x03300C00,		/*�����ձ��*/  
	0x03300600,		/*ʱ������*/
	0x21000000,		/*��������*/
};

uchar8 SF_GetAPDU_FreezeRead( RdOI_Para_T *V_OAD, uchar8 *P_DataBuf, ushort16 *P_DataOff, uchar8 NextFrameFlage );
uchar8 InF_RateNumChangeToHex( void );
uchar8 SF_Judge_CuerrntIDFlag( void );
uchar8 SF_GetEsamIDFlag( void );
uchar8 INF_RELEASE_Service_Deal_Card( void );

void InF_Clear_BroadTimeAbnormalTime( void );
uchar8 SF_Get_Active_OAD( ulong32 V_ulReadOAD, ulong32 *pV_ulSetAndFixedOAD, uchar8 V_ucDataType, uchar8 V_ucHappeningFlag );
#endif

