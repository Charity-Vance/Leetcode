/*******************************************************************************
Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     SecurityModule.h
Version:       V1
Author:        jiangzs
Date:          2014-3-31
Description:   ��ȫ�ļ�
---------------------------------------------------------------------------------
History1:      ��1���޸�
����1. Date:   20211021
   	   Author: lx
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

#ifndef	__SecurityModule_H
#define	__SecurityModule_H

#include    "Public.h"
#include    "SecurityCommunication.h"

extern ulong32 GV_EsamTime;				/*Esamͬ��ʱ��*/

extern ConectRequest_Type	Com_Conect;	/*ͨ��Ӧ�����ӽṹ��*/

/*******************************������֤��Ϣ******************************************/

/*���ܷ����궨��*/
#define	PlainData_MAC_698 	0x11
#define	CodedData_698 		0xA6
#define	CodedData_MAC_698 	0xA7


/*���ݳ��Ⱥ궨��*/
#define	AuthMaxLength_698 	52
#define	MaxLength_698    	2048

#define	AuthSessionData1Len_698   		0x20
#define	AuthSessionData2Len_698   		0x30
#define	AuthSessionData2Len_698_termal  0x40 	/*�ն˷����������*/
#define	IRidRequestData1Len_698   		0x08	/*ͼƬ0X10*/
#define	IRidRequestData2Len_698   		0x08

#define	C_DataID_Length_698	4		/*��ʶ����*/
#define	C_MAC_Length_698	4		/*MAC����*/
#define	C_len_698			1		/*����ռ1�ֽ�*/

/******************** Ǯ����ʼ�� *********************************************/
#define	C_PreSetMoney_len_698		4	/*Ԥ�ý��*/

/******************** Ǯ����ֵ���˷� *********************************************/
#define	C_BuyMoney_len_698   		4	/*������*/
#define	C_BuyMoneyNum_len_698		4	/*�������*/
#define	C_ClientNum_len_698			6	/*�ͻ����*/

/********************  ESAM�����궨��  *********************************************/
#define	C_EsamAction_Reset			1	/*��λ*/
#define	C_EsamAction_Action			2	/*ִ��*/
#define	C_EsamAction_ReadData		3	/*���ݶ�ȡ*/
#define	C_EsamAction_DataUpdate		4	/*���ݸ���*/
#define	C_EsamAction_Unvalid			5	/*Э��ʧЧ*/
#define	C_EsamAction_MoneyAction	6	/*Ǯ������*/
#define	C_EsamAction_KetUpdate		7	/*��Կ����*/
//#define	C_EsamAction_Reset   		8	/*֤�����*/
#define	C_EsamAction_Auth_Time		9	/*Э��ʱЧ����*/
#define	C_EsamAction_MoneyInit		10	/*Ǯ����ʼ��*/
#define	C_EsamAction_IRRequest		11	/*������֤����*/
#define	C_EsamAction_IRID			12	/*������֤*/

/********************  Ǯ�������궨��  *********************************************/
#define	C_OpenAccount		0		/*����*/
#define	C_MoneyAdd			1		/*Ǯ����ֵ*/
#define	C_MoneyReturn		2		/*Ǯ���˷�*/


/********************  ESAM7816 ������  *********************************************/
#define	CLen_LC_Len_698				2					/*Lc���ȣ�2���ֽ�*/
#define	CLen_TB_ESAM_4_698			4					/*ESAM�����񲻺���5�ֽڣ���5�ֽڿ϶�ΪLc��Le��Ϊ��(��Ϊ���1))*/
#define	CLen_TB_ESAM_Lc_698			5					/*ESAM������Lc(���3��4)*/
#define CLen_TB_ESAM_6_698			6

const	uchar8	TB_ReadEsamInfoAll_698[CLen_TB_ESAM_4_698] = {0x80,0x36,0x00,0xff}; 				/*��esamȫ����Ϣ*/
const	uchar8	TB_ReadEsamInfoAll_698_termal[CLen_TB_ESAM_4_698] = {0x80,0x36,0x00,0xfe};			/*���ն�esamȫ����Ϣ*/
const	uchar8	TB_ReadEsamInfo_698[CLen_TB_ESAM_4_698] = {0x80,0x36,0x00,0x00}; 					/*��esamȫ����Ϣ*/
const	uchar8	TB_Authentication_698[CLen_TB_ESAM_Lc_698] = {0x81,0x02,0x00,0x00,0x00};			/*�����֤����ͷ�������ݳ���*/
const	uchar8	TB_Authentication_698_termal[CLen_TB_ESAM_Lc_698] = {0x82,0x02,0x00,0x00,0x00};		/*��ս�����֤����ͷ�������ݳ���*/
const	uchar8	TB_Encrypt_RN_PlainData_MAC_698[CLen_TB_ESAM_4_698] = {0x80,0x0E,0x40,0x02};		/*�����ݼ��� ����+MAC(��RN)*/
const	uchar8	TB_Encrypt_RN_EncodedData_698[CLen_TB_ESAM_4_698] = {0x80,0x0A,0x40,0x02};			/*�����ݼ��� ����(��RN)*/
const	uchar8	TB_Encrypt_RN_EncodedData_MAC_698[CLen_TB_ESAM_4_698] = {0x80,0x10,0x40,0x02};		/*�����ݼ��� ����+MAC(��RN)*/
const	uchar8	TB_Encrypt_EncodedData_MAC_698[CLen_TB_ESAM_4_698] = {0x81,0x1c,0x00,0x00};			/*�����ݼ��� ����+MAC(��RN)*/

/*�����ն˼�����������ͷ*/
const	uchar8	TB_Encrypt_EncodedData_Plain_MAC_698_terminal[CLen_TB_ESAM_4_698] = {0x82,0x24,0x00,0x11}; 			/*�ն˶����ݼ��� ����+MAC(��RN)*/
const	uchar8	TB_Encrypt_EncodedData_Plain_MAC_698_terminal_back[CLen_TB_ESAM_4_698] = {0x80,0x24,0x11,0x00}; 	/*�ն˶����ݼ��� ����+MAC(��RN)*/
const	uchar8	TB_Encrypt_EncodedData_698_terminal[CLen_TB_ESAM_4_698] = {0x82,0x24,0x00,0x12}; 					/*�ն˶����ݼ��� ����+MAC(��RN)*/
const	uchar8	TB_Encrypt_EncodedData_MAC_698_terminal[CLen_TB_ESAM_4_698] = {0x82,0x24,0x00,0x13}; 				/*�ն˶����ݼ��� ����+MAC(��RN)*/
const	uchar8	TB_Encrypt_EncodedData_MAC_698_terminal_back[CLen_TB_ESAM_4_698] = {0x80,0x24,0x13,0x00};			/*�ն˶����ݼ��� ����+MAC(��RN)*/

/*2020��׼�����ϱ�2005*/
const	uchar8	TB_Encrypt_Report_RN_MAC_698[CLen_TB_ESAM_4_698] = {0x80,0x14,0x01,0x03}; 	    		/*�����ϱ����� ����+MAC(��RN)*/
const	uchar8	TB_Encrypt_Report_MAC_698[CLen_TB_ESAM_4_698] = {0x80,0x0E,0x40,0x81}; 	        		/*�����ϱ���Ӧ���� ����+MAC*/

const	uchar8	TB_IR_ID_Request_698[CLen_TB_ESAM_6_698] = {0x80,0x08,0x08,0x03,0x00,0x10}; 			/*������֤����*/
const	uchar8	TB_IR_ID_Request_698_Termal[CLen_TB_ESAM_6_698] = {0x80,0x08,0x00,0x04,0x00,0x08}; 		/*�ն������֤����*/


const	uchar8	TB_IR_ID_Request2_698[CLen_TB_ESAM_6_698] = {0x80,0x04,0x00,0x08,0x00,0x00}; 			/*������֤����*/
const	uchar8	TB_IR_ID_698[CLen_TB_ESAM_6_698] = {0x80,0x06,0x00,0x01,0x00,0x08}; 					/*������֤����*/

/*******************************����Ӧ���******************************************/
#define		C_Resp_61XXType		0xFF00
#define		C_Resp_63CXType		0xFFF0

#define		CL_Send_InIC		60					/*�忨�������õ�������ʱ����������*/
#define		CL_Response_InIC	60					/*�忨�������õ�������ʱ����������*/

/*******************************�͵ߵ���صĺ�************************************/
#define	C_OneDataRev			0x00000001			/*һ��������ߵ�*/
#define	CDI_Auth_R				0x00000002			/*�����֤������ߵ��ķ���*/
#define	CDI_TZone_Data			0x00000004
#define	CDI_TZone_PT_Data		0x00000005


#define	C_RItem_Len_Auth		3					/*�����֤��Ҫ�ߵ���������*/
#define	C_RItem_Len_AuthR		3					/*�����֤������ߵ���������*/
#define	C_RITem_Len_CPTime		2					/*�����֤ʱ���ߵ���������*/
/*******************************ESAM������غ�************************************/
#define	CLen_TB_ESAM_4				4				/*ESAM�����񲻺���5�ֽڣ���5�ֽڿ϶�ΪLc��Le��Ϊ��(��Ϊ���1))*/
#define	CLen_TB_ESAM_Lc				5				/*ESAM������Lc(���3��4)*/
#define	CLen_TB_ESAM_Le				5				/*ESAM������Le(���2)*/
#define	CLen_TB_ESAM_Le_698_Esam	6				/*ESAM������Le(��6982���ֽ����ݳ���)*/
#define	CLen_TB_ESAM_Lc_698_Esam	6				/*ESAM������Lc(���3��4)*/
#define	CLen_TB_ESAM_Lc_698_SoftwareCampare	3		/*ESAM����������ȶ�*/

/**698**/
#define	C_AuthPTime_LByte		0x30				/*�����֤��Чʱ��Ĭ�ϲ������ֽ�*/
#define	C_AuthPTime_HByte		0x00

/**698����645Э��**/
#define	CLen_Respond_Auth				0		/*�����֤Ӧ��������ʼλ��ƫ��K2/Rand4/ESAM���к�*/
#define	CLen_Respond_Auth_Only90		0		/*������֤Ӧ��������ʼλ��ƫ��ESAM���к�/K1/Rand2*/

/*698����645Э��,����������£�����ƫ��,1�ֽڳ���+4�ֽڱ�ʶ��+����*/
#define	CLen_DataLEN		5             /*����ƫ��*/
#define	CLen_DataDILEN		4             /*�����б�ʶ�볤��*/

/*******************************���������Ͷ���************************************/
static	uchar8	SV_Rand1_4[4];						/*�����֤ʱ��վ�·����������*/
static	uchar8	SV_SafeByte;

static	uchar8	SV_UpdateMInEsamTimer;				/*Ҫ��״̬��ѯʱˢ��ESAM��15min������*/
													/*�����ؼ���ʱ������5s*/
#define	C_SV_UpdateMInEsamTimer		180				/*180*5=900s=15min*/
/******************************* ���**************************************************/

/********************  ���ݵߵ�����ȱ�  *************************************/
const	uchar8	TB_RItem_Len_Auth[C_RItem_Len_Auth] = 
				{CL_Auth_CiphertextK1,CL_Auth_Rand1,CL_Auth_Dis_factor};
				/*{0x08,0x08,0x08}*/
const	uchar8	TB_RItem_Len_AuthR[C_RItem_Len_AuthR] = 
				{CLen_Rand2,CLen_ESAMNo,CLen_AuthPTime};
				/*{0x04,0x08,0x02}*/
const	uchar8	TB_RITem_Len_CPTime[C_RITem_Len_CPTime] = 
				{CLen_AuthPTime,C_MacLen};
				/*{0x02,0x04}*/

#define	C_RItem_Len_RateBak		33				/*���ʱ�32�����ʵ��+1��Mac*/
const	uchar8	TB_RITem_Len_RateBak[C_RItem_Len_RateBak] = 
				{
					4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
					4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
					4
				};			/*���1��ΪMac*/
#define	C_RITem_Len_LadderBak	18				/*���ݱ�6������ֵ+7�����ݵ��+4�������+1��Mac*/
const	uchar8	TB_RITem_Len_LadderBak[C_RITem_Len_LadderBak] = 
				{
					4,4,4,4,4,4,
				  	4,4,4,4,4,4,4,
				  	3,3,3,3,
				  	4
				  };
#define	C_RITem_Len_MeterPosition	3
const	uchar8	TB_RITem_Len_MeterPosition[C_RITem_Len_MeterPosition] = 
				{4,4,3};
	
#define	C_RITem_Len_TZone_Data		14
#define	C_Len_TZone_Data			42
const	uchar8	TB_RITem_Len_TZone_Data[C_RITem_Len_TZone_Data] = 
				{3,3,3,3,3,3,3,3,3,3,3,3,3,3};
#define	C_RITem_Len_TZone_PT_Data	14
#define	C_Len_TZone_PT_Data			42
const	uchar8	TB_RITem_Len_TZone_PT_Data[C_RITem_Len_TZone_PT_Data] = 
				{3,3,3,3,3,3,3,3,3,3,3,3,3,3};
#define	C_RITem_Len_InitMoney		4

const	uchar8	TB_RITem_Len_InitMoney[C_RITem_Len_InitMoney] = 
				{CLChargeBal_Hex_Cent,C_MacLen,CL_PurchasingE_Num,C_MacLen};
				/*{4,4,4,4};*/		/*����(ʣ��)��Mac���������,Mac*/




/********************  ESAM7816 ������  *********************************************/
/**698**/
const	uchar8	TB_AuthDistributedkey_698[CLen_TB_ESAM_Lc_698_Esam] = {0x80,0x08,0x08,0x02,0x00,0x10}; 		/*�����֤�в��ñ�ŷ�ɢ��Կ����Lc*/
const	uchar8	TB_AuthDistributedkey_L_698[CLen_TB_ESAM_Le_698_Esam] = {0x80,0x08,0x08,0x01,0x00,0x10}; 	/*�����֤�в��ÿ��ŷ�ɢ��Կ����Lc*/
const	uchar8	TB_GetChallenge_698_Esam[CLen_TB_ESAM_Lc_698_Esam] = {0x80,0x04,0x00,0x00,0x00,0x00};		/*��ȡ���������ͷ������Le*/
const	uchar8	TB_CardEncryptingRand1[CLen_TB_ESAM_Lc] = {0x00,0x88,0x00,0x01,0x08};						/*��Ƭ���������1(�ڲ���֤)	*/				
const	uchar8	TB_Increase_698[CLen_TB_ESAM_Lc_698_Esam] = {0x80,0x42,0x00,0x00,0x00,0x0C};				/*���*/
const	uchar8	TB_WriteRecord_698[CLen_TB_ESAM_Lc_698_Esam] = {0x83,0x3e,0x00,0x00,0x00,0x08};				/*д��¼�ļ���P1Ϊ��¼����Ҫ�滻��*/
const	uchar8	TB_Decrease_698[CLen_TB_ESAM_Lc_698_Esam] = {0x80,0x46,0x00,0x00,0x00,0x04};				/*�ۿ����Mac�ۿ�*/
/**698**/


/**698����645,645����**/
const	uchar8	TB_AuthDistributedkey_645[CLen_TB_ESAM_Lc_698_Esam] = {0x80,0x08,0x08,0x03,0x00,0x10}; 		/*�����֤�в��ñ�ŷ�ɢ��Կ����Lc*/
const	uchar8	TB_GetChallenge_645_Esam[CLen_TB_ESAM_Lc_698_Esam] = {0x80,0x04,0x00,0x04,0x00,0x00};		/*��ȡ���������ͷ������Le*/
const	uchar8	TB_RdESAMNo_645[CLen_TB_ESAM_Lc_698_Esam] = {0x80,0x36,0x00,0x02,0x00,0x00};				/*��ESAM���к�����ͷ		*/		
/**698����645,645����**/


const	uchar8	TB_RdESAMNo[CLen_TB_ESAM_Le] = {0x00,0xB0,0x99,0x01,0x08};				/*��ESAM���кŰ���Le*/
const	uchar8	TB_AuthDistributedkey[CLen_TB_ESAM_Lc] = {0x80,0xFA,0x00,0x03,0x08}; 	/*�����֤�в��ñ�ŷ�ɢ��Կ����Lc*/
const	uchar8	TB_AuthDistributedkey_L[CLen_TB_ESAM_Lc] = {0x80,0xFA,0x00,0x01,0x08};	/*�����֤�в��ÿ��ŷ�ɢ��Կ����Lc*/
const	uchar8	TB_EncryptingRand1[CLen_TB_ESAM_Lc] = {0x80,0xfa,0x00,0x00,0x08};		/*�����֤�м��������1 ����Lc*/
const	uchar8	TB_GetResponse[CLen_TB_ESAM_4] = {0x00,0xC0,0x00,0x00};					/*��ȡ��Ӧ������ͷ������Le*/
const	uchar8	TB_GetChallenge[CLen_TB_ESAM_4] = {0x00,0x84,0x00,0x00};				/*��ȡ���������ͷ������Le*/
const	uchar8	TB_Decrease[CLen_TB_ESAM_Lc] = {0x80,0x30,0x01,0x0C,0x05};				/*�ۿ����Mac�ۿ�*/
const	uchar8	TB_IRExtAuth[CLen_TB_ESAM_Lc] = {0x00,0x82,0x00,0x02,0x08};				/*�ⲿ��֤����ͷ*/
const	uchar8	TB_UpdateKey[CLen_TB_ESAM_Lc] = {0x84,0xD4,0x01,0xFF,0x20};				/*��Կ���µ�ESAM������*/
const	uchar8	TB_Increase[CLen_TB_ESAM_Lc] = {0x84,0x32,0x01,0x0C,0x0C};				/*���*/
const	uchar8	TB_WriteRecord[CLen_TB_ESAM_Lc] = {0x04,0xDC,0xFF,0x0c,0x08};			/*д��¼�ļ���P1Ϊ��¼����Ҫ�滻��*/
const	uchar8	TB_SelectFile[CLen_TB_ESAM_Lc] = {0x00,0xA4,0x00,0x00,0x02};			/*ѡ���ļ�*/
const	uchar8	TB_SoftwareCampare[CLen_TB_ESAM_Lc] = {0x80,0xFA,0x01,0x00,0x40};		/*��������ȶ�����*/

/*����¼�ļ�*/
#define	CLen_TB_ReadRecord		9

#define	C_O_LC				4						/*LC��ƫ�ơ�*/
#define	C_O_MeterNum		CLen_TB_ReadRecord		/*���*/

const	uchar8	TB_ReadRecord[CLen_TB_ReadRecord] = 
{
	0x80,0x48,0x00,0x00,0x00,
	0x0d,0x48,0x00,0x00
};			/*��Ǯ���ļ�*/


#define	CLen_TB_ReadRecord_698		7
const	uchar8	TB_ReadRecord_698[CLen_TB_ReadRecord_698] = {0x80,0x48,0x00,0x00,0x00,0x01,0x00};


												
/*��Mac���������ļ�(ESAM)*/
#define	CLen_TB_ReadBinFileMac		27
#define	C_O_P2						3
#define	C_O_P1						2				/*P1��ƫ�ơ�*/
#define	C_O_P2_04D6					12
#define	C_O_Lc2						25
#define	C_O_Rand4					13				/* 4  �ֽ������ƫ��*/
#define	C_O_MeterNumBinFile			7				/* ���ƫ��*/
#define	C_O_P2BinFile				17				/* P2ƫ��*/
#define	C_O_lenBinFile				19				/* lenƫ��*/

const	uchar8	TB_ReadBinFile_Mac[CLen_TB_ReadBinFileMac] = 	/*��Mac���������ļ�*/
{
	0x83,0x2C,0xFF,0xFF,0x15,0x00,0x48,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,
	0xFF,0xFF,
	0x04,0xD6,0x85,0x00,
	0xFF,0xFF
};							

/********************  �ļ����ļ��в���ƫ��  *********************************************/
/*��Macд�������ļ���*/
#define	C_F_Pam_Max		CLen_S_BufMaxLen						/*��������ֽڳ���*/

/*�ļ�Ŀ¼*/
/*#define	C_F_MainDir			0xDF01*/

/*********************���㡢���������е�ƫ��*************************************************/
#define	CF_O_CMDEndTime		2						/*����ִ�еĽ�ֹʱ��*/
#define	CL_CMDEndTime		6
#define	CF_O_EventClearDI	(CF_O_CMDEndTime + CL_CMDEndTime)
#define	CL_DI				4
/*********************���������ļ��е�ƫ��*************************************************/
#define	CF_O_PU_StartA		0						/*���������ļ�����ʼ��ַƫ��*/
#define	CF_O_PU_LC			0						/*���ֽ��ǳ���*/
#define	CF_O_PU_DI			1						/* 1-4 DI*/
#define	CF_O_PU_Data		5						/*���ݿ�ʼ*/
#define	CL_PU_LC			1						/*LC����*/
#define	CL_DataCode			4						/*DataCode����*/
/*********************������Ϣ�ļ�C_F_ParmInf �е�ƫ��*********************************/
#define	CF_O_ChgRate		10						/*������Ϣ�ļ������׷����л�ʱ��*/
#define	CF_O_Alarm1			16						/*������Ϣ�ļ��б������1*/
#define	CF_O_Alarm2			20						/*������Ϣ�ļ��ܱ������2*/
#define	CF_O_RatioCTInParm	24						/*������Ϣ�ļ��е������������*/
#define	CF_O_RatioVTInParm	27						/*������Ϣ�ļ��е�ѹ���������	*/
#define	CF_O_MNumInParm		30						/*������Ϣ�ļ��б��*/
#define	CF_O_CNumInParm		36						/*������Ϣ�ļ��пͻ���ŵ�ƫ��*/
#define	CF_O_AuthPTime		43						/*������Ϣ�ļ��������֤��Чʱ��ƫ��*/

/*********************��ǰ�׵��C_F_ElePriceBak�ļ���ƫ��*********************************************/
#define	CF_O_Ladder			137						/*��ǰ�׵���ļ��н������ݿ���ʼ��ַ��*/


/*********************�����׵��C_F_ElePriceBak�ļ���ƫ��*********************************************/
#define	CF_O_Rate1Bak		4						/*�����׵���ļ��з���1�����ʼ��ַ*/
#define	CF_O_LadderBak		132						/*�����׵���ļ��н������ݿ���ʼ��ַ��*/

#define	CF_O_ChgLadder		196						/*�����׵���ļ������׽����л�ʱ��*/

/*********************��Կ״̬C_F_LKeyState�ļ���ƫ��***************************************/
#define	CF_O_KeyState		0						/*������Կ״̬�ļ�����Կ״̬ƫ��*/

/*********************������ϢC_F_OpParm�ļ���ƫ��************************************/
#define	CF_O_RatioCTInOP	5						/*������Ϣ�ļ��е������������*/
#define	CF_O_RatioVTInOP	8						/*������Ϣ�ļ��е�ѹ���������*/

#define	CF_O_MNumInOP		11						/*������Ϣ�ļ��б��*/
#define	CF_O_CNumInOP		17						/*������Ϣ�ļ��пͻ����*/

#define	CF_O_OPI_ChBal_H_C	23						/*ʣ������������Ϣ�ļ���ƫ��*/
#define	CF_O_OPI_PEN		27						/*���������������Ϣ�ļ���ƫ��*/
#define	CF_O_OPI_OD_B		31						/*͸֧�����������Ϣ�ļ���ƫ��*/

#define	CF_O_OPI_Start		0						/*�����ļ���ʼ�ֽ�ƫ��*/
#define	CF_O_OPI_CMD		1						/*�����ļ�������ƫ��*/
#define	CF_O_OPI_Len		2						/*�����ļ�����ƫ��*/
#define	CF_O_OPI_LawLessIC	39						/*�����ļ��зǷ��忨����*/
#define	CF_O_OPI_RWRClock	42						/*�����ļ��з�д����*/
#define	CF_O_OPI_CS		47							/*�����ļ���CS*/
#define	CF_O_OPI_End		48
#define	CL_OPI				49						/*�����ļ������ܳ���*/
/*************************��¼C_F_Purse�ļ�**********************************************************/
/*698��*/
#define	C_ChargeBal_Mac			0x01					/*ʣ����*/
#define	C_PurchasingE_Num_Mac	0x03					/*�������*/
#define	C_Custormer_Num			0x05					/*�ͻ����*/
/*698��*/

/*698����645ʹ��*/
#define	C_AuthPTimeP2			0x03					/*��ȡESAM��Ϣƫ��P2=05�����C_EsamNatureToAction��λ�ã��ỰʧЧ����+�ỰʱЧʣ��ʱ��*/
#define C_AuthPTimeRemain  		0x08        			/*�ỰʱЧʣ��ʱ������ƫ��*/


#define C_Max_EsamLen			200

/**************** ͨ������1��������********************************************/
typedef	struct
{
	ulong32	DI;						/*��ʶ��*/
	uchar8	Len;					/*���ݳ��ȣ�����Mac*/
	uchar8	FileNo;					/*д��ESAMȥ���ļ���*/
	uchar8	Offset;					/*��FileNo�ж�Ӧ��ƫ��*/
	uchar8	OffsetInOP;				/*���д�����ļ�����Ӧ�����ļ��е�ƫ��.����ΪoxFF*/
}Str_ParmPlainText;

#define	C_Invalid_Offset			0xFF
#define	C_ParmPlainText_MaxNum		11
const	Str_ParmPlainText	TB_ParmPlainText[C_ParmPlainText_MaxNum] = 
{
	{CChange_Rate,CLChange_Rate,C_F_ParmInf,CF_O_ChgRate,C_Invalid_Offset},						/*���׷����л�ʱ��	*/
	{CChange_Ladder,CLChange_Ladder,C_F_ElePriceBak,CF_O_ChgLadder,C_Invalid_Offset},			/*���׽��ݵ���л�ʱ��*/
	{CRatio_Curr_Tran,CLRatio_Curr_Tran_Esam,C_F_ParmInf,CF_O_RatioCTInParm,CF_O_RatioCTInOP},	/*�������������*/
	{CRatio_Vol_Tran,CLRatio_Vol_Tran_Esam,C_F_ParmInf,CF_O_RatioVTInParm,CF_O_RatioVTInOP},	/*��ѹ���������*/
	{CMeter_Num,CLMeter_Num,C_F_ParmInf,CF_O_MNumInParm,CF_O_MNumInOP},							/*���*/
	{CCustomer_Num,CLCustomer_Num,C_F_ParmInf,CF_O_CNumInParm,CF_O_CNumInOP},					/*�ͻ����*/
	{CAlam1_Money,CLAlam1_Money,C_F_ParmInf,CF_O_Alarm1,C_Invalid_Offset},						/*�������1*/
	{CAlam2_Money,CLAlam2_Money,C_F_ParmInf,CF_O_Alarm2,C_Invalid_Offset},						/*�������2*/
	{0x401E0200,8,C_F_ParmInf,CF_O_Alarm2,C_Invalid_Offset},									/*�������2*/
	{CBackUp_RateFF_Price,CLBackUp_RateFF_Price,C_F_ElePriceBak,CF_O_Rate1Bak,C_Invalid_Offset},/*���ʵ��1*/
	{CBackUp_Ladder_Table,CLBackUp_Ladder_Table,C_F_ElePriceBak,CF_O_LadderBak,C_Invalid_Offset}/*���ݲ���*/
};

/**************** ͨ������1��������********************************************/
typedef	struct
{
	ushort16	V_usDI1DI0;		/*��ʶ��*/
	uchar8		V_ucP2;			/*���ݳ��ȣ�����Mac*/
	uchar8		V_ucOffset;		/*ƫ��*/
	uchar8		V_ucLen;		/*���ݳ���*/
}Str_EsamTable;




/**************** ��������********************************************/
void		DataReversed(ulong32 V_ulReversedMethod, uchar8 *pV_ucData, uchar8 V_ucR_ItemNum);
uchar8		ReadRecordFile(uchar8 * pV_ucData, uchar8 * pV_ucLen, uchar8 V_ucRecordNo);
ushort16	WriteRecordFile(uchar8 * pV_ucData, uchar8 V_ucLen);
uchar8		ReadBinFileMac(uchar8 *pV_ucData, uchar8 *pV_ucFileNo, uchar8 *pV_ucParmOffset, uchar8 *pV_ucParmLen);
uchar8		WriteBinFileMac(uchar8 V_ucCH, uchar8 * pV_ucData, uchar8 V_ucFileNo, uchar8 V_ucParmOffset, ushort16 V_usParmLen);
uchar8		WriteBinFileMac_1(uchar8 V_ucCH, uchar8 *pV_ucData, uchar8 V_ucFileNo, uchar8 V_ucParmLen);
uchar8		WriteBinFile(uchar8 V_ucCH, uchar8 *pV_ucData, uchar8 V_ucFileNo, uchar8 V_ucParmOffset, uchar8 V_ucParmLen);
uchar8		WriteBinFileMac_2(uchar8 V_ucCH, uchar8 * pV_ucData, uchar8 V_ucParmOffsetL, uchar8 V_ucParmOffsetH, uchar8 V_ucParmLen);
uchar8		LookForStr_ParmPlainText(ulong32	V_ulDI,	uchar8 	*pV_ucParmPlainText_O);
uchar8		GetParmUpdataFileNo(ulong32	V_ucDI);
uchar8		SelectFile(uchar8	V_ucFileNo);
void		UpdataChargeBalInESAMWithSwitch(void);
uchar8		SC_ReadBinFileMac(uchar8 V_ucCH, uchar8 V_ucFileNo, uchar8 V_ucParmOffset, uchar8 *pV_ucData,
				uchar8 V_ucNxtCLA, uchar8 V_ucNxtINS, uchar8 V_ucNxtP1, uchar8 V_ucNxtP2, uchar8 V_ucLC1,uchar8	 *pV_ucIC_CardNo);
void		Init_GV_7816CMD(void);
uchar8		S_ReadEsam_698(uchar8 *pV_ucData,ushort16 *pV_usLen,ushort16 V_usItem);
void 		SF_ColdReset_7816_Esam_No(void);	/*����ESAM����ȡ���к����*/
extern void InF_Clear698ConectTimer();
#endif

