
///*****************************************************************************************///
///*Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     
///*Version:       V1
///*Date:          2014-3-12
///*Description:   
///*Function List: 
///*****************************************************************************************///
#ifndef	__EsamDrive_H
#define	__EsamDrive_H

#include "Public.h"
#include "IO.h"
#include "Timer.h"

//static	ulong32	SV_ulTemp_ESAM;

#define C_Len_SerialNumber	    8			///*���кų���*///
#define	C_Len_APDU_5		    5			///*���2������5�ֽڸ�ESAM*///
#define	C_Len_APDU_2		    2			///*����2�ֽ�SW*///
#define	C_Esam_2ETU			    93			///*��ʱ2ETU��186us����2usΪ��λ��ʱ*///
#define	C_Esam_16ETU		    800			///*�����ֲ�Ҫ������16ETU��1488us������ʵ��1600us����2usΪ��λ��ʱ*///
#define	C_Esam_20ETU		    1000		///*�����ֲ�Ҫ������20ETU��1860us������ʵ��2000us����2usΪ��λ��ʱ*///

//#define	C_Esam_3S		    1500000		///*���ճ�ʱ��3s,2us��׼*///
#define	C_Esam_1S		        50000		///*���ճ�ʱ��1s,2us��׼*///
#define	C_Len_APDU_4		    4			///*��С���ݳ��ȣ���CLA INS P1 P2*///
//#define	C_Esam_Tcsl60us	30				///*�����ֲ�Ҫ������50us�����100us���˴�����Ϊ60us����2usΪ��λ��ʱ*///
//#define	C_Esam_Tcsh30us	15				///*�����ֲ�Ҫ������10us�����50us���˴�����Ϊ30us����2usΪ��λ��ʱ*///
#define	C_Esam_Tq20us	        10			///*�����ֲ�Ҫ������15us����󡪡����˴�����Ϊ20us����2usΪ��λ��ʱ*///
#define	C_Esam_Tcsd6us	        3			///*�����ֲ�Ҫ������3us�����10us���˴�����Ϊ6us����2usΪ��λ��ʱ*///
#define	C_Esam_RetryTime	    3			///*ESAM���ݲ����ظ����������3��*///
#define	C_Esam_TxRxSign55	    0x55		///*ESAM���ݷ��͡����ձ�־*///
#define	C_Esam_DataOff4_Len1	4			///*Ӧ�ò����ݣ�Len1ƫ��*///
#define	C_Esam_DataOff5_Len2	5			///*Ӧ�ò����ݣ�Len2ƫ��*///
#define	C_Len_Esam_Max		    2048		///*����ESAM������ݳ��ȣ���ֹ���������쳣��һֱ���ڽ�����*///


#define C_FirstByte_ATR		0x3b		///*��λӦ��ĵ�1�ֽ�*///
#define C_SecondByte_ATR	0x69		///*��λӦ��ĵ�2�ֽ�*///
#define C_ThirdByte_ATR		0x00		///*��λӦ��ĵ�3�ֽ�*///
#define C_FourthByte_ATR	0x00		///*��λӦ��ĵ�4�ֽ�*///
#define C_FifthByte_ATR41	0x41		///*��λӦ��ĵ�5�ֽ�*///
#define C_FifthByte_ATR43	0x43		///*��λӦ��ĵ�5�ֽ�*///



//#define C_Security_Err							0xff00+C_Error				///*Esam/Card�����쳣*///
//#define C_Security_MaxLenErr					0xff00+C_MaxResponseLen_ERR	///*Esam/Card������������󳤶ȴ���*///
//
//#define C_Security_ProcessOk					0x6100		///*��������61XX*///
//#define C_Security_CommandOk					0x9000		///*����ִ�гɹ�*///
//
//#define C_Security_InvalidFile					0x6283		///*ѡ����ļ���Ч*///
//#define C_Security_AuthenFailed					0x6300		///*��֤ʧ��*///
//#define C_Security_VerifyFailed					0x63c0		///*��֤ʧ�ܣ�63cX*///
//#define C_Security_ExecutingError 				0x6400		///*ִ�г���*///
//#define C_Security_E2Damage						0x6581		///*E2��*///
//#define C_Security_LcLengthError				0x6700		///*Lc���ȴ���*///
//#define C_Security_CLAError						0x6900		///*CLA�������ļ�����Ҫ��*///
//#define C_Security_CmdNotReceiving				0x6901		///*�������*///
//#define C_Security_CmdNotCompatible				0x6981		///*�������ļ��ṹ������*///
//#define C_Security_NotMeetSafety				0x6982		///*�����㰲ȫ״̬*///
//#define C_Security_AuthMethodLocking			0x6983		///*��֤��������*///
//#define C_Security_ReferenceDataInvalid			0x6984		///*����������Ч*///
//#define C_Security_ConditionNotSatisfied		0x6985		///*ʹ������������*///
//#define C_Security_CurrentFileNotSelected		0x6986		///*û��ѡ��ǰ�ļ�*///
//#define C_Security_SafetyDataIncorrect			0x6988		///*��ȫ�����������ȷ*///
//#define C_Security_DomainParaIncorrect			0x6a80		///*�������������ȷ*///
//#define C_Security_FunctionNotSupported			0x6a81		///*���ܲ�֧��*///
//#define C_Security_FileNotFound					0x6a82		///*δ�ҵ��ļ�*///
//#define C_Security_RecordNotFound				0x6a83		///*δ�ҵ���¼*///
//#define C_Security_RecordSpaceFull				0x6a84		///*��¼�ռ�����*///
//#define C_Security_LcAndTLVNotMatch				0x6a85		///*Lc��TLV�ṹ��ƥ��*///
//#define C_Security_ParaP1AndP2NotCorrect		0x6a86		///*����P1/P2����ȷ*///
//#define C_Security_ReferenceDataNotFound		0x6a88		///*δ�ҵ���������*///
//#define C_Security_ParameterError				0x6b00		///*��������*///
//#define C_Security_LeLengthError				0x6c00		///*Le���ȴ���*///
//#define C_Security_CmdNotExist					0x6d00		///*�������*///
//#define C_Security_CLACmdTypeFault				0x6e00		///*�������ʹ�CLA��*///
//#define C_Security_DataInvalid					0x6f00		///*������Ч*///
//#define C_Security_MACInvalid					0x9302		///*MAC��Ч*///
//#define C_Security_AppLocked					0x9303		///*Ӧ�ñ���������*///
//#define C_Security_AmountLess					0x9401		///*����*///

#define	C_Esam_StatusWorkL					0x86	///*Esam���ڹ���״̬*///
#define	C_Esam_StatusWorkH					0x68	///*Esam���ڹ���״̬*///
#define	C_Esam_StatusDeactivationL			0xa6	///*Esam����ͣ��״̬*///
#define	C_Esam_StatusDeactivationH			0x5a	///*Esam����ͣ��״̬*///

#define	C_Esam_Len_Status					2		///*Esam״̬��־�ĳ���*///
#define	C_Esam_Len_ResetAck					13		///*Esam��λ���Ӧ�𳤶�*///


#define	C_Esam_ERR							0x86	///*Esam���ϣ�ESAM�����ϱ���*///
#define	C_Esam_OK							0x00	///*Esam������ESAM����δ�ϱ���*///
#define	C_ESAMERR_MeterWorkState			0x02	///*�������������1�е�Esam����λ*///


typedef struct
{
	uchar8	Report;				///*�Ƿ��ϱ���־*///
	uchar8	HStatus;			///*��ʷ״̬*///
}Str_ESAM_Type;

static Str_ESAM_Type Str_ESAM_Status;		///*ESAM����״̬*///




///*����ESAM��־����CRC*///
//typedef struct
//{
//	uchar8 Hstatus[2];		///*��ʷ״̬*///
//	uchar8 ESAMCRC[2];		///*CRC*///
//}Str_EsamState_Type;
//static Str_EsamState_Type Str_EsamStatus;


///*usart Souceclock enable/disable*///
#define EsamClock_Output_EN()	{SFR_ESAMCOM->CR2 |= 0x00000800;}
#define EsamClock_Output_DIS()	{SFR_ESAMCOM->CR2 &= 0xFFFFF7FF;}
///*****************************************************************************************///
///*ESAM��Դ����:�����������*///
#define	SwitchOn_EsamPower()	{ulong32 SV_ulTemp_ESAM;\
								IO_ESAMPOWER->OTYPER &= ESAMPOWER_OUTPUT_PP;\
								IO_ESAMPOWER->BSRR = ESAMPOWERRESET;\
								SV_ulTemp_ESAM = IO_ESAMPOWER->MODER;\
								SV_ulTemp_ESAM &= ESAMPOWER_IN_MODE;\
								SV_ulTemp_ESAM |= ESAMPOWER_OUT_MODE;\
								IO_ESAMPOWER->MODER = SV_ulTemp_ESAM;\
								IO_ESAMPOWER->BSRR = ESAMPOWERRESET;}
								
#define	SwitchOff_EsamPower()	{ulong32 SV_ulTemp_ESAM;\
								IO_ESAMPOWER->OTYPER &= ESAMPOWER_OUTPUT_PP;\
								IO_ESAMPOWER->BSETH = ESAMPOWERSET;\
								SV_ulTemp_ESAM = IO_ESAMPOWER->MODER;\
								SV_ulTemp_ESAM &= ESAMPOWER_IN_MODE;\
								SV_ulTemp_ESAM |= ESAMPOWER_OUT_MODE;\
								IO_ESAMPOWER->MODER = SV_ulTemp_ESAM;\
								IO_ESAMPOWER->BSETH = ESAMPOWERSET;}
///*****************************************************************************************///
///*usart Souceclock enable/disable*///
//#define Esam_SouceClock_EN()	{Esam_SouceClock_SFR |= EsamSouceClock_EN;}///*ESAMʱ����Ч������2ms@4MHz�������ʽͨ��*///
//#define Esam_SouceClock_DIS()	{Esam_SouceClock_SFR &= EsamSouceClock_DIS;}
///*****************************************************************************************///
///*ESAM��λ����:�����������*///
#define	Esam_EN()				{ulong32 SV_ulTemp_ESAM;\
								SV_ulTemp_ESAM = IO_ESAMRESET->OSPEEDR;\
								SV_ulTemp_ESAM &= ESAMRESET_SPEED_INIT;\
								SV_ulTemp_ESAM |= ESAMRESET_SPEED_2MHZ;\
								IO_ESAMRESET->OSPEEDR = SV_ulTemp_ESAM;\
								IO_ESAMRESET->OTYPER &= ESAMRESET_OUTPUT_PP;\
								IO_ESAMRESET->BSRR = ESAMRESETSET;\
								SV_ulTemp_ESAM = IO_ESAMRESET->MODER;\
								SV_ulTemp_ESAM &= ESAMRESET_IN_MODE;\
								SV_ulTemp_ESAM |= ESAMRESET_OUT_MODE;\
								IO_ESAMRESET->MODER = SV_ulTemp_ESAM;\
								IO_ESAMRESET->PUPDR &= ESAMRESET_NOPUPD;\
								IO_ESAMRESET->BSRR = ESAMRESETSET;}

#define	Esam_Reset()			{ulong32 SV_ulTemp_ESAM;\
								SV_ulTemp_ESAM = IO_ESAMRESET->OSPEEDR;\
								SV_ulTemp_ESAM &= ESAMRESET_SPEED_INIT;\
								SV_ulTemp_ESAM |= ESAMRESET_SPEED_2MHZ;\
								IO_ESAMRESET->OSPEEDR = SV_ulTemp_ESAM;\
								IO_ESAMRESET->OTYPER &= ESAMRESET_OUTPUT_PP;\
								IO_ESAMRESET->BSRR = ESAMRESETRESET;\
								SV_ulTemp_ESAM = IO_ESAMRESET->MODER;\
								SV_ulTemp_ESAM &= ESAMRESET_IN_MODE;\
								SV_ulTemp_ESAM |= ESAMRESET_OUT_MODE;\
								IO_ESAMRESET->MODER = SV_ulTemp_ESAM;\
								IO_ESAMRESET->PUPDR &= ESAMRESET_NOPUPD;\
								IO_ESAMRESET->BSRR = ESAMRESETRESET;}

#define	EsamCLK_Init()			{ulong32 SV_ulTemp_ESAM;\
								IO_ESAMCLK->OSPEEDR |= ESAMCLK_SPEED_50MHZ;\
								IO_ESAMCLK->PUPDR &= ESAMCLK_NOPUPD;\
								IO_ESAMCLK->BSRR = ESAMCLKRESET;\
								SV_ulTemp_ESAM = IO_ESAMCLK->MODER;\
								SV_ulTemp_ESAM &= ESAMCLK_IN_MODE;\
								SV_ulTemp_ESAM |= ESAMCLK_OUT_MODE;\
								IO_ESAMCLK->MODER = SV_ulTemp_ESAM;\
								IO_ESAMCLK->OTYPER &= ESAMCLK_OUTPUT_PP;}
								
#define	EsamIO_Init()			{ulong32 SV_ulTemp_ESAM;\
								SV_ulTemp_ESAM = IO_ESAMDATA->OSPEEDR;\
								SV_ulTemp_ESAM &= ESAMDATA_SPEED_INIT;\
								SV_ulTemp_ESAM |= ESAMDATA_SPEED_50MHZ;\
								IO_ESAMDATA->OSPEEDR = SV_ulTemp_ESAM;\
								IO_ESAMDATA->PUPDR &= ESAMDATA_NOPUPD;\
								IO_ESAMDATA->OTYPER |= ESAMDATA_OUTPUT_OD;\
								IO_ESAMDATA->BSRR = ESAMDATARESET;\
								SV_ulTemp_ESAM = IO_ESAMDATA->MODER;\
								SV_ulTemp_ESAM &= ESAMDATA_IN_MODE;\
								SV_ulTemp_ESAM |= ESAMDATA_OUT_MODE;\
								IO_ESAMDATA->MODER = SV_ulTemp_ESAM;\
								IO_ESAMDATA->BSRR = ESAMDATARESET;}


#endif

