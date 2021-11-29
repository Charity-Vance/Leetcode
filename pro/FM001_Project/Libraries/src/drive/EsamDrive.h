
///*****************************************************************************************///
///*Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
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

#define C_Len_SerialNumber	    8			///*序列号长度*///
#define	C_Len_APDU_5		    5			///*情况2：发送5字节给ESAM*///
#define	C_Len_APDU_2		    2			///*接收2字节SW*///
#define	C_Esam_2ETU			    93			///*延时2ETU，186us，以2us为单位计时*///
#define	C_Esam_16ETU		    800			///*数据手册要求最少16ETU：1488us，程序实际1600us，以2us为单位计时*///
#define	C_Esam_20ETU		    1000		///*数据手册要求最少20ETU：1860us，程序实际2000us，以2us为单位计时*///

//#define	C_Esam_3S		    1500000		///*接收超时：3s,2us基准*///
#define	C_Esam_1S		        50000		///*接收超时：1s,2us基准*///
#define	C_Len_APDU_4		    4			///*最小数据长度，按CLA INS P1 P2*///
//#define	C_Esam_Tcsl60us	30				///*数据手册要求最少50us，最大100us，此处设置为60us，以2us为单位计时*///
//#define	C_Esam_Tcsh30us	15				///*数据手册要求最少10us，最大50us，此处设置为30us，以2us为单位计时*///
#define	C_Esam_Tq20us	        10			///*数据手册要求最少15us，最大——，此处设置为20us，以2us为单位计时*///
#define	C_Esam_Tcsd6us	        3			///*数据手册要求最少3us，最大10us，此处设置为6us，以2us为单位计时*///
#define	C_Esam_RetryTime	    3			///*ESAM数据操作重复次数，最多3次*///
#define	C_Esam_TxRxSign55	    0x55		///*ESAM数据发送、接收标志*///
#define	C_Esam_DataOff4_Len1	4			///*应用层数据，Len1偏移*///
#define	C_Esam_DataOff5_Len2	5			///*应用层数据，Len2偏移*///
#define	C_Len_Esam_Max		    2048		///*接收ESAM最大数据长度，防止接收数据异常，一直处于接收中*///


#define C_FirstByte_ATR		0x3b		///*复位应答的第1字节*///
#define C_SecondByte_ATR	0x69		///*复位应答的第2字节*///
#define C_ThirdByte_ATR		0x00		///*复位应答的第3字节*///
#define C_FourthByte_ATR	0x00		///*复位应答的第4字节*///
#define C_FifthByte_ATR41	0x41		///*复位应答的第5字节*///
#define C_FifthByte_ATR43	0x43		///*复位应答的第5字节*///



//#define C_Security_Err							0xff00+C_Error				///*Esam/Card操作异常*///
//#define C_Security_MaxLenErr					0xff00+C_MaxResponseLen_ERR	///*Esam/Card操作缓冲区最大长度错误*///
//
//#define C_Security_ProcessOk					0x6100		///*正常处理：61XX*///
//#define C_Security_CommandOk					0x9000		///*命令执行成功*///
//
//#define C_Security_InvalidFile					0x6283		///*选择的文件无效*///
//#define C_Security_AuthenFailed					0x6300		///*认证失败*///
//#define C_Security_VerifyFailed					0x63c0		///*验证失败：63cX*///
//#define C_Security_ExecutingError 				0x6400		///*执行出错*///
//#define C_Security_E2Damage						0x6581		///*E2损坏*///
//#define C_Security_LcLengthError				0x6700		///*Lc长度错误*///
//#define C_Security_CLAError						0x6900		///*CLA不符合文件属性要求*///
//#define C_Security_CmdNotReceiving				0x6901		///*命令不接收*///
//#define C_Security_CmdNotCompatible				0x6981		///*命令与文件结构不相容*///
//#define C_Security_NotMeetSafety				0x6982		///*不满足安全状态*///
//#define C_Security_AuthMethodLocking			0x6983		///*认证方法锁定*///
//#define C_Security_ReferenceDataInvalid			0x6984		///*引用数据无效*///
//#define C_Security_ConditionNotSatisfied		0x6985		///*使用条件不满足*///
//#define C_Security_CurrentFileNotSelected		0x6986		///*没有选择当前文件*///
//#define C_Security_SafetyDataIncorrect			0x6988		///*安全报文数据项不正确*///
//#define C_Security_DomainParaIncorrect			0x6a80		///*数据域参数不正确*///
//#define C_Security_FunctionNotSupported			0x6a81		///*功能不支持*///
//#define C_Security_FileNotFound					0x6a82		///*未找到文件*///
//#define C_Security_RecordNotFound				0x6a83		///*未找到记录*///
//#define C_Security_RecordSpaceFull				0x6a84		///*记录空间已满*///
//#define C_Security_LcAndTLVNotMatch				0x6a85		///*Lc与TLV结构不匹配*///
//#define C_Security_ParaP1AndP2NotCorrect		0x6a86		///*参数P1/P2不正确*///
//#define C_Security_ReferenceDataNotFound		0x6a88		///*未找到引用数据*///
//#define C_Security_ParameterError				0x6b00		///*参数错误*///
//#define C_Security_LeLengthError				0x6c00		///*Le长度错误*///
//#define C_Security_CmdNotExist					0x6d00		///*命令不存在*///
//#define C_Security_CLACmdTypeFault				0x6e00		///*命令类型错，CLA错*///
//#define C_Security_DataInvalid					0x6f00		///*数据无效*///
//#define C_Security_MACInvalid					0x9302		///*MAC无效*///
//#define C_Security_AppLocked					0x9303		///*应用被永久锁定*///
//#define C_Security_AmountLess					0x9401		///*金额不足*///

#define	C_Esam_StatusWorkL					0x86	///*Esam处于工作状态*///
#define	C_Esam_StatusWorkH					0x68	///*Esam处于工作状态*///
#define	C_Esam_StatusDeactivationL			0xa6	///*Esam处于停活状态*///
#define	C_Esam_StatusDeactivationH			0x5a	///*Esam处于停活状态*///

#define	C_Esam_Len_Status					2		///*Esam状态标志的长度*///
#define	C_Esam_Len_ResetAck					13		///*Esam复位后的应答长度*///


#define	C_Esam_ERR							0x86	///*Esam故障；ESAM故障上报过*///
#define	C_Esam_OK							0x00	///*Esam正常；ESAM故障未上报过*///
#define	C_ESAMERR_MeterWorkState			0x02	///*电表运行特征字1中的Esam故障位*///


typedef struct
{
	uchar8	Report;				///*是否上报标志*///
	uchar8	HStatus;			///*历史状态*///
}Str_ESAM_Type;

static Str_ESAM_Type Str_ESAM_Status;		///*ESAM故障状态*///




///*开关ESAM标志：带CRC*///
//typedef struct
//{
//	uchar8 Hstatus[2];		///*历史状态*///
//	uchar8 ESAMCRC[2];		///*CRC*///
//}Str_EsamState_Type;
//static Str_EsamState_Type Str_EsamStatus;


///*usart Souceclock enable/disable*///
#define EsamClock_Output_EN()	{SFR_ESAMCOM->CR2 |= 0x00000800;}
#define EsamClock_Output_DIS()	{SFR_ESAMCOM->CR2 &= 0xFFFFF7FF;}
///*****************************************************************************************///
///*ESAM电源控制:口线推挽输出*///
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
//#define Esam_SouceClock_EN()	{Esam_SouceClock_SFR |= EsamSouceClock_EN;}///*ESAM时钟有效后最少2ms@4MHz后才能正式通信*///
//#define Esam_SouceClock_DIS()	{Esam_SouceClock_SFR &= EsamSouceClock_DIS;}
///*****************************************************************************************///
///*ESAM复位控制:口线推挽输出*///
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

