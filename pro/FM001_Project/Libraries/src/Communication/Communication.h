
/****************************************************************************************
Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     communication.h
Author		jiangzs
Version:       V1
Date:          2014-3-12
Description:   通信处理、解析文件
Function List:
---------------------------------------------------------------------------------
History1:      第1次修改
内容1. Date:
   	   Author:
       Modification:
---------------------------------------------------------------------------------
内容2. Date:
   	   Author:
       Modification:
	---------------------------------------------------------------------------------
History2:      第2次修改
内容1. Date:
   	   Author:
       Modification:
---------------------------------------------------------------------------------
内容2. Date:
   	   Author:
       Modification:
***************************************************************************************/
#ifndef	__communication_H
#define	__communication_H

#include	"Public.h"
#include   "SecurityCommunication.h"

extern		uchar8	SV_SetBPS_Flag;								/*C_OK设置BPS，C_Error其他通信命令*/
extern		uchar8 SV_Comm_Address[CLComm_Address + 2];			/*通信地址*/
extern      ulong32 SV_ModuleResetTimer24h;   					/*24h模块通道复位*/

#define		C_ModuleResetTimer24h ( 24 * 60 * 60 * 1000 / 500 )	/*24h模块通道复位*/

/******************** 宏定义************************************************************/
/*时间和日期*/
#define	C_Sec						0			/*秒*/
#define	C_Minute					1			/*分*/
#define	C_Hour						2			/*时*/
#define	C_Day						3			/*日*/
#define	C_Month						4			/*月*/
#define	C_Year						5			/*年*/

#define	C_LoadTimeLen				5			/*负荷记录时间的长度*/
#define C_ReCal						0x78		/*当截止时间比当前时间大，块数需重算*/
#define C_LoadTLength				5      		/*负荷记录时间长度*/
#define	C_EnergyLenForComm			4			/*通信电能一般长度*/
#define	C_DemandLenForComm	    	8			/*通信需量一般长度3+5*/

#define C_CAddr_OFS_ForRx_698	    0x04		/*地址起始偏移*/
#define C_CLenL_OFS_ForRx_698	    0x01		/*长度低字节偏移*/
#define C_CLenH_OFS_ForRx_698	    0x02		/*长度高字节偏移*/
#define C_CControl_OFS_ForRx_698	0x03		/*控制字偏移*/

/*645错误应答Err标志*/
#define	C_RateNum_OV				0x40		/*费率数超*/
#define	C_PeriodNum_OV				0x41		/*日时段数超*/
#define	C_SeasonNum_OV				0x42		/*年时区数超*/
#define	C_Baud_NotModified			0x43		/*通信速率不能更改*/
#define	C_Unauthorized				0x44		/*未授权/密码错*/
#define	C_No_Request_data			0x45		/*无请求数据*/
#define	C_OtherErr					0x46		/*其他错误*/
/**************************************************/
/*******************698兼容645增加*****************/
#define	C_PeriodNum_OV_645			0x20		/*日时段数超*/
#define	C_SeasonNum_OV_645			0x10		/*年时区数超*/
#define	C_Baud_NotModified_645		0x08		/*通信速率不能更改*/
#define	C_Unauthorized_645			0x04		/*未授权/密码错*/
#define	C_No_Request_data_645		0x02		/*无请求数据*/
#define	C_OtherErr_645				0x01		/*其他错误*/

#define	C_1200						2
#define	C_2400						3
#define	C_4800						4
#define	C_9600						6

#define	C_JudgeDI0FF  				0x000000FF
#define CL_EventFF_AALen   			1           /*上10次事件数据块，补AA，AA长度1字节*/

/****************************************************/

#define	C_Cal_LenErr				0xA0		/*校表长度错误*/
#define	C_Cal_PWCanNotRD			0xA1		/*校表时，电能表校表密码读不出*/
#define	C_Cal_IDErr					0xA2		/*校表时，标识码错误*/
#define	C_Cal_SPIErr				0xA3		/*校表时，SPI错误*/
#define	C_Cal_NOStartErr			0xA4		/*校表时，未启动校表错误*/
#define	C_Cal_PWOkButSetCPW			0xA5		/*已设置过校表密码，重复设置校表密码*/
#define	C_Cal_WrMICOtherErr			0xA6		/*校表时写计量芯片其他错误*/
#define	C_Cal_WrDataErr				0xA7		/*校表时写数据层校表寄存器错误*/
#define	C_Cal_PW_Err				0xA8		/*校表时密码错*/
#define	C_Cal_NoErr					0xA9		/*校表时序号错误*/
#define	C_Cal_SafeFlagErr			0xAA		/*校表时安全字节错误*/
#define	C_YSettle_All99				0x68		/*年结算日设置成全99*/
/*交互通信缓冲区偏移*/
#define	C_68_1_OFS_ForRx			0x00		/*通讯交互变量缓冲区数据接收时第1个68偏移*/
#define	C_CAddr_OFS_ForRx			0x01		/*通讯交互变量缓冲区数据接收时通信地址偏移*/
#define	C_68_2_OFS_ForRx			0x07		/*通讯交互变量缓冲区数据接收时第2个68偏移	*/
#define	C_C_OFS_ForRx				0x08		/*通讯交互变量缓冲区数据接收时C偏移	*/
#define	C_L_OFS_ForRx				0x09		/*通讯交互变量缓冲区数据接收时L偏移	*/
#define	C_Data_OFS_ForRx			0x0A		/*通讯交互变量缓冲区数据接收时数据偏移*/

#define	C_FE_OFS_ForTx				0x00		/*通讯交互变量缓冲区数据发送时FE偏移	*/
#define	C_68_1_OFS_ForTx			0x04		/*通讯交互变量缓冲区数据发送时第1个68偏移*/
#define	C_CAddr_OFS_ForTx			0x05		/*通信交互变量缓冲区数据发送时通信地址偏移*/
#define	C_68_2_OFS_ForTx			0x0B		/*通讯交互变量缓冲区数据发送时第2个68偏移	*/
#define	C_C_OFS_ForTx				0x0C		/*通讯交互变量缓冲区数据发送时C偏移	*/
#define	C_L_OFS_ForTx				0x0D		/*通讯交互变量缓冲区数据发送时L偏移	*/
#define	C_Data_OFS_ForTx			0x0E		/*通讯交互变量缓冲区数据发送时数据偏移*/

/******************698交互数据偏移**************************/
#define	C_First68_OFFSet_698		0x00		/*698帧第一个68*/
#define	C_LH_OFFSet_698		    	0x02		/*698帧长度高字节*/
#define	C_LL_OFFSet_698		    	0x01		/*698帧长度高字节*/
#define	C_C_OFFSet_698				0x03		/*698帧控制字节*/
#define	C_AF_OFFSet_698		    	0x04		/*698帧中地址起始字节:低半字节为服务器地址*/
#define	C_AddressFirst_698			0x05		/*698帧中地址第一个字节*/


/*V_645Frame.Data中数据偏移地址*/
#define	C_DI_OFS					0x00
#define	C_PW_OFS_14					0x04
#define	C_OPCode_OFS_14				0x08
#define	C_Data_OFS_14				0x0C
/*表号相关标志*/
#define	C_MeterAddress				0x68
#define	C_Broadcast					0x99
#define	C_Condense_AA_All			0xAA
#define	C_Condense_AA				0x0A
#define	C_AdrressError				0xFF
/*密钥相关*/
#define	CLen_Key					32			/*密钥长度*/
#define	C_TestKey					0x68		/*密钥状态为测试密钥*/
#define	C_OfficialKey				0x86		/*密钥状态为正式密钥*/
#define	C_InitUpdataKeyState		0x00		/*密钥状态为未更新过状态,上述3个密钥既可表示所有密钥状态，又可表示单个密钥状态*/
#define	C_UpdataKeyProcess			0xFF		/*密钥更新过程中,只能表示所有密钥的一个状态*/
/*电表挂起*/
#define	C_SPT_Num_Over				0xE1		/*指示安全次数超*/
#define	C_KeyErr_Num_Over			0xE2		/*指示密码错误次数超*/
/*消息标志(请注意通讯中的消息标志，采用按位或方式，因此取值按位取值)*/
#define	C_MessageMaxNum				15			/*消息总数	*/
#define	CMsg_Txd					0x00000001	/*发送消息	*/
#define	CMsg_InitComm				0x00000002	/*初始化通信口消息	*/
#define	CMsg_MeterClear				0x00000004	/*电表总清消息	收到1A命令时触发*/
#define	CMsg_DemandClear			0x00000008	/*需量清零消息	收到19命令时触发*/
#define	CMsg_EventClear				0x00000010	/*事件清零消息	收到1B命令时触发*/
#define	CMsg_ProgTimePeriod			0x00000020	/*时段表编程消息	"收到14：第1套时段表编程04010001-04010008，*/
												/*第2套时段表编程04020001-04020008"*/
#define	CMsg_ProgSeason				0x00000040	/*时区表编程消息	"收到14：第1套时区表编程04010000*/
												/*第2套时区表编程04020000"*/
#define	CMsg_ProgWeekRest			0x00000080	/*周休日编程消息	收到14：周休日编程04000802*/
#define	CMsg_ProgHoliday			0x00000100	/*公共假日编程消息	收到14：公共假日编程04030001-040300FE*/
#define	CMsg_ProgCombPState			0x00000200	/*组合状态字编程消息	收到14：组合状态字（有功、无功1、2）编程04000601-04000603*/
#define	CMsg_ProgCombQ1State		0x00000400
#define	CMsg_ProgCombQ2State		0x00000800
#define	CMsg_ProgSetADate			0x00001000	/*结算日编程消息	收到14：第1-3结算日编程04000B01-04000B03*/
#define	CMsg_ProgRate				0x00002000	/*费率表编程消息	收到14：备用套费率电价编程040501FF*/
#define	CMsg_ProgStepTariff			0x00004000	/*阶梯表编程消息	收到14：备用套阶梯电价编程040605FF*/
#define	CMsg_ProgDateTime			0x00008000	/*校时记录消息*/
#define	CMsg_PurchaseToDL			0x00010000	/*数据层充值消息处理，收到远程开户命令和充值命令时触发*/
#define	CMsg_ReturnMoney			0x00020000	/*退费消息处理，收到退费命令时触发*/
#define	CMsg_BroadcastTime			0x00040000	/*广播校时记录消息*/
/*通信交互变量相关宏*/
#define	C_First68_Ok				0x01
#define	C_Second68_Ok				0x04
#define	C_Len_Ok					0x10
#define	C_CS_Ok				    	0x20
#define	C_16_Ok						0x40
#define	C_CommRecFlagForInt_Ok		(C_First68_Ok | C_Second68_Ok | C_Len_Ok | C_CS_Ok | C_16_Ok)
#define	C_Comm_Buf_MaxLen			220
#define	C_Comm_Data_MaxLen			200			/*处理数据长度最长为200*/
#define	C_Comm_FixedRxLen			12			/* 2个68+6个表号+C+L+CS+16 = 12*/
#define	C_Comm_FixedTxLen			16			/*多了4个FE*/
#define	C_Comm_RNData_MaxLen		35			/*随机数长度*/
#define	C_CLenCS16_645	        	2		    /*cs,0x16长度*/

#define	C_Comm_Buf_MaxLen_698		2020
#define	C_Comm_Data_MaxLen_698		2000		/*处理数据长度最长为200*/
/*事件记录中数据偏移*/
#define	C_O_ProgClock				0
#define	C_O_OperateCode				6
#define	C_O_EventData				10

/*电表运行状态字相关的宏*/
#define	CB_RemoteOAccount			0x80		/*远程开户在bit15*/
#define	CO_RemoteOAccount			1			/*远程开户在电表运行状态字3的高字节*/
#define	CB_LocalOAccount			0x40		/*本地开户在bit14*/
#define	CO_LocalOAccount			1			/*在电表运行状态字3的高字节*/
#define	CB_IDAuth					0x20		/*身份认证状态在bit13*/
#define	CO_IDAuth					1			/*在电表运行状态字3的高字节*/
#define	CB_IRAuth					0x08		/*红外认证在bit3*/
#define	CO_IRAuth					0			/*在电表运行状态字3的低字节*/
#define	CB_IRAuth_T					0x04		/*终端身份认证在bit10*/
#define	CO_IRAuth_T					1			/*在电表运行状态字3的高字节*/
#define	CB_IDAuth_T					0x08		/*终端安全认证状态在bit11*/
#define	CO_IDAuth_T					1			/*在电表运行状态字3的高字节*/
/*其他宏  */
#define	C_Duration_Alway			0xFFFF
#define	C_Duration_3s_L				0x03
#define	C_Duration_3s_H				0x00
#define	C_NoNxtFrame				0x00
#define	C_HaveNxtFrame				0x68

#define	C_SupperPW_OK				0x68

/*带星期时间格式*/
#define	CDate_WW_Time_WW_O			3
#define	CDate_WW_Time_DD_O			4
#define	CDate_WW_Time_MM_O			5
#define	CDate_WW_Time_YY_O			6

#define C_FramePartValueLen			512		/*链路层分帧有效数据长度*/
#define C_FramePartMaxLen			530		/*链路层分帧发送缓存*/
#define	C_FrameMaxLen				2048	/*一帧数据最大长度*/
#define	C_APDUMaxLen				2000	/*APDU最大长度*/
#define	C_FrameMaxLen_698			2000	/*一帧数据最大长度*/
/*********************以下为全局静态变量的定义*****************************************/
/*中断区分645协议和698协议判断使用*/
typedef struct
{
	ushort16    Len;						/*通讯帧总长度。接收时在收到645长度时置，发送时在启动发送时置*/
	uchar8      RecFlag;					/*通讯接收中断合法标志，有效时或上：C_First68_Ok、*/
                                    		/*C_Second68_Ok、C_Len_Ok、C_cs_Ok、C_16_Ok。全部合法，本字节*/
                                    		/*为C_CommRecFlagForInt_Ok */
	uchar8	    ProtocolType;	    		/*规约类型*/
}Str_Comm_Judge;
/*****通道通信缓冲区******/
typedef struct
{
	ushort16	Offset;						/*通讯接收、发送时的偏移量。注意设计时不管发送还是接*/
											/*收都是先使用再调整指针*/
	ushort16	FrameNum;					/*帧序号，已经接收的帧序号*/
	ushort16	APDULen;					/*APDU长度*/
	ushort16	APDUOffset;					/*APDU偏移*/
	uchar8	Buff[C_FramePartMaxLen];		/*接收时，不包含FE，发送时包含4个FE*/
	uchar8	Buff_APDU[C_FrameMaxLen];		/*接收时，不包含FE，发送时包含4个FE*/
	uchar8	OTimer;							/*通讯超时定时器加定时器*/
	uchar8	AddrLen;						/*通讯地址长度*/
	uchar8	CommDeriction;					/*分帧发起者标志*/
    Str_Comm_Judge Comm_Judge645; 			/*/645协议判断结构体*/
    Str_Comm_Judge Comm_Judge698; 			/*/698协议判断结构体*/
}Str_Comm_Parm;
#define	C_Comm_OTime				5		/*超时定时器值*/
static	Str_Comm_Parm				SV_RS485_1_Comm_Parm @".DataProcessADDR";
static	Str_Comm_Parm				SV_RS485_2_Comm_Parm @".DataProcessADDR";
static	Str_Comm_Parm				SV_IR_Comm_Parm @".DataProcessADDR";
static	Str_Comm_Parm				SV_Module_Parm @".DataProcessADDR";

/*2020标准主动上报2005*/
#define CLMeterStatusNum (CLDrive_Report_Mode * 8)  /*模块通道的电表运行状态字的事件的上报次数*/
extern  uchar8 SV_REPORTCommBuff[C_ModuleMaxLen];
typedef struct
{
    ushort16    ReportLen;              	/*主动上报数据帧长度*/
    ushort16    ReportFlag;             	/*当前是否处于主动上报发送状态*/
    ushort16    Last_ReportLen;         	/*上次发送的长度*/
    uchar8      ReportOffset;           	/*主动上报已发送帧长度*/
    uchar8      ReportOTimer;           	/*100ms定时器中去处理*/
    uchar8      PowerDown_ReportOTimer; 	/*掉电上报后等待再次上报时间*/
    uchar8      ReportClearNum;         	/*如果正常通信时发现2.5S还没有主动上报成功，就清零*/
    uchar8      V_CRC[2];
}Str_Report_Parm;
extern  Str_Report_Parm SV_ReportSend;
extern  uchar8  SV_PowerfailReportONum[3];
#define CL_SV_ReportParm      		sizeof(Str_Report_Parm)
#define C_ReportToTempVariable      0x68	/*report结构体拷贝到变量*/
#define C_TempVariableToReport      0x86	/*变量拷贝到report结构体*/

/*简写*/
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
/*宏定义*/
#define	C_ProtocolType_698			0x98	/*698协议*/
#define	C_ProtocolType_NOT698		0x89	/*不是698协议*/
#define	C_ProtocolType_645			0x45	/*645协议*/
#define	C_ProtocolType_NOT645		0x54	/*不是645协议*/
#define	C_ProtocolType_Init  		0x00	/*未判断645协议，也未判断698协议，初始化值*/

/******后续帧****************/
#define	LClockLen					5		/*负荷记录点时标为年月日时分5字节*/
#define	CLen_CREnergy				16		/*连续读电能集合为正、反有功总，组合无功1、2共16字节*/
typedef struct
{
	ulong32	DataCode;						/*数据项标识码。注意这里是总的数据项标识码*/
	uchar8	FrameNo;						/*帧序号，表示下一帧期望主站下发的帧序号。*/
											/*11-1中有后续帧置1*/
	uchar8	HaveReport;						/*已主动上报标志C_Error表示未主动上报，C_OK表示已主动上报20140707增加*/
	uchar8	FrameFinished;					/*C_OK表示后续帧数据已结束，C_Error表示后续帧数据未读完*/
	ulong32	Nxt_DataCode;					/*下一帧分项数据标识码*/
	uchar8	LNxt_Fix_Time[LClockLen];		/*下一帧负荷记录有效数据块的记录时间*/
	uchar8	LNxt_BlockNum;					/*下一帧负荷记录需要读的数据块个数*/
	uchar8	LNxt_CREnergy[CLen_CREnergy];	/*下一帧连续读电能集合*/
	uchar8	Sub_DataCode;					/*本次分项数据标识码*/
	uchar8	LSub_Fix_Time[LClockLen];		/*本次负荷记录有效数据块的记录时间*/
	uchar8	LSub_BlockNum;					/*本次负荷记录需要读的数据块个数*/
	uchar8	LSub_CREnergy[CLen_CREnergy];	/*本次连续读电能集合*/
    uchar8  TotalBlockNum;					/*总读的数据块个数*/
    uchar8  ReadedBlockNum;					/*已经读走的个数*/
}Str_Comm_NxtFrame;
											/*注1：DataCode和FrameNo为总的后续帧使用的变量。*/
											/*注2：带Nxt的，下一帧使用到的分项变量。在11-1中真正初始化。*/
											/*注3：带Sub的，本次使用到的分项变量。在12命令中初始化。为的是能够重读本后续帧。*/
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
/* 20140629讨论，不采用分项标识码后带长度的做法，太浪费空间了。*/
/*而是充分利用数据层读数据不管长度够不够，都会返回实际长度的特点。*/
typedef struct							/*总的数据项标识码表*/
{
	ulong32  DataCode;					/*总的数据项标识码，屏蔽DI0（次数），次数有效性在11命令中判断*/
	ulong32	*pTB_SubDI;					/*分项数据标识码汇总表格地址。*/
	uchar8	SubDINum;					/*分项标识码总数，用于判断是否到表格尾部*/
	uchar8	Method;						/*使用2级表的方法，共2个方法*/
}Str_TBNxtFrame;
#define	C_Freeze_Method			01
#define	C_Prog_SubDI_LBit4		02		/*分项标识码使用低4位作为次数。次数深度固定为0x0A*/
#define	C_CarryingSubDI			03		/*分项标识码DI0不代表次数。*/
#define	C_Event_Method			04  	/*事件方法*/

/*冻结的分项标识码汇总定义（8类冻结，使用一张表格，程序中将冻结类型DI2及次数替代上去。）*/
#define	C_FreezeSubDILen		12
extern const	ulong32 		TB_FreezeSubDI[C_FreezeSubDILen];				/*上1次定时冻结变量数据*/

/*整点冻结*/
#define	C_HFreezeSubDILen		3
extern const	ulong32 		TB_HFreezeSubDI[C_HFreezeSubDILen];				/*上1次整点冻结变量数据*/

/*需清事件记录*/
#define	C_DCLREvent_SubDILen	2
extern const	ulong32	TB_DCLREvent_SubDI[C_DCLREvent_SubDILen];
/*时段编程事件记录*/
#define	C_ProgPT_SubDILen		4
extern const	ulong32	TB_ProgPT_SubDI[C_ProgPT_SubDILen];
/*节假日编程事件*/
#define	C_ProgHol_SubDILen	6
extern const	ulong32	TB_ProgHol_SubDI[C_ProgHol_SubDILen];
/*校表编程记录*/
/*备注，这里需要注意，表格定义最长长度254行，*/
/*但实际在第1张表中，采用实际有效分项标识码数目C_MeterICDataNum_T*/
#define	C_CalMReg_SubDILen	255
extern const	ulong32	TB_CalMReg_SubDI[C_CalMReg_SubDILen];
/*失流事件记录*/
#define	C_LossA_Curr_SubDILen		10
extern const	ulong32	TB_LossA_Curr_SubDI[C_LossA_Curr_SubDILen];

#define	C_LossB_Curr_SubDILen		10
extern const	ulong32	TB_LossB_Curr_SubDI[C_LossB_Curr_SubDILen];

#define	C_LossC_Curr_SubDILen		10
extern const	ulong32	TB_LossC_Curr_SubDI[C_LossC_Curr_SubDILen];

/*过流事件记录*/
#define	C_OverA_Curr_SubDILen		10
extern const	ulong32	TB_OverA_Curr_SubDI[C_OverA_Curr_SubDILen];

#define	C_OverB_Curr_SubDILen		10
extern const	ulong32	TB_OverB_Curr_SubDI[C_OverB_Curr_SubDILen];

#define	C_OverC_Curr_SubDILen		10
extern const	ulong32	TB_OverC_Curr_SubDI[C_OverC_Curr_SubDILen];

/* 1级表*/
#define	C_TBNxtFrameNum				11
extern const	Str_TBNxtFrame		TB_NxtFrame[C_TBNxtFrameNum];
/********************带分项标识码读取的二级表格定义*********************************/
typedef struct					/*总的数据项标识码表1级表*/
{
	ulong32	DataCode;			/*总的数据项标识码，这里是不带次数的。*/
	ulong32	*pTB_SubDI;			/*分项数据标识码汇总表格地址。*/
	uchar8	SubDINum;			/*分项标识码总数，用于判断是否到表格尾部*/
}Str_TBCarryingSubDI_1;

/*带分项标识码读的2级表*/
/*费率电价FF读取分项标识码*/
#define			CLen_TB_RateFF_Price		12
extern const	ulong32	TB_Current_RateFF_Price[CLen_TB_RateFF_Price];
extern const	ulong32	TB_BackUp_RateFF_Price[CLen_TB_RateFF_Price];
/*电表运行状态字*/
#define			CLen_TB_MeterStatus			8
extern const	ulong32	TB_MeterStatus[CLen_TB_MeterStatus];
/*正、反有功、1-4无功需量超限总次数*/
#define			CLen_TB_De_Over_Degree		6
extern const	ulong32	TB_De_Over_Degree[CLen_TB_De_Over_Degree];

/*带分项标识码读的1级表*/
#define			CLen_TBCarryingSubDI_1		4
extern	const	Str_TBCarryingSubDI_1		TBCarryingSubDI_1[CLen_TBCarryingSubDI_1];

#define			Pstr_ParaChange_Event_Len	27
extern const 	Str_ParaChange_OADToDI_Table Pstr_ParaChange_Event[Pstr_ParaChange_Event_Len];

/******通信解析全局变量***/
typedef struct
{
	uchar8	SafeControlFlag;				/*安全控制标志*/
	uchar8	MeterClearFlag;					/*电表总清标志*/
	ulong32	MessageFlag;					/*消息标志，1位表示1个消息。见注1*/
	uchar8	RecFlag;						/*通道接收标志置换过来的。*/
	uchar8	ClientAddrFlag;					/*通道接收标志置换过来的。*/
}Str_Comm_Parse_Local;
extern	Str_Comm_Parse_Local SV_Comm_Parse_Local;
/*注1：使用Comm_AppendMsg，Comm_FetchMsg插入和获取一个消息标志。*/

/*200次挂起结构体*/
typedef struct
{
	uchar8	Key0204_ErrNum;					/*02/04级密码错误次数*/
	uchar8	Key04_ErrNum;					/*04级密码错误次数*/
	uchar8	Num;							/*SafePendingThreshold，200次挂起次数*/
	uchar8	RecentClock[7];					/*最近一次SPT或密码错误发生时间，用于判断跨零点清除标志*/
	ushort16	Crc;
}Str_SPT;

#define	CLen_Str_SPT				12			/*包括CRC，10个字节长*/
#define	C_SPTNum_Threshold			200			/*挂起阀值*/
#define	C_Key0204_ErrThreshold		3			/*02/04级密码错误次数阀值。*/

#define	C_KeyErrNumAdd				0x04		/*密码错误次数++*/
#define	C_JudgeKeyErr				0x05		/*判断密码错误次数是否到?*/
#define	C_ClrKeyErrNum				0x06		/*因为是连续3次密码错误，因此有清零的方法*/
#define	C_Key02Flag					0x80		/*02级密码处理标志*/
#define	C_Key04Flag					0x40		/*04级密码处理标志*/
#define	C_SPTFlag					0x00		/*SPT级密码处理标志*/

/*超过10min中的定时器。基准为500ms.*/
typedef struct
{
	uchar8		BaseTimer;						/* 基本定时器。为16进制数	*/
	ulong32		Timer;							/*基于1minTimer。为10进制数。*/
	ushort16	Crc;
}Str_TimerExceed10min;
#define	C_StrTimerExceed10minLen	7
#define	C_TimerExceed10minLen		4
#define	C_Timer_Base_10minLen		5
#define	C_TimerDisable				0x00
#define	C_TimerEnable				0x68
#define	C_BaseTimer					120			/*基本定时器初值。如500ms调用一次扣减，则为1min*/
												/* 如果是2.5s调用一次扣减，则为5min。*/
#define	C_ProgKeyTime_L				0x40
#define	C_ProgKeyTime_H 			0x02		/*编程开关初值240分钟，4小时*/
/*控制模块复位结构体*/
#define	C_Flag_Ok					0x68		/*标志正确*/
#define	C_Flag_Err					0x00		/*标志错误*/
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
	uchar8						Timer_1min;					/*通用定时器，1min*/
   	Str_SPT 					SPTVariable;				/*SafePendingThreshold，200次挂起次数*/
	Str_TimerExceed10min		ID_Authentication_Timer; 	/*身份认证剩余时间定时器，初值由安全模块身份认证  接口函数出口参数带出*/
	Str_TimerExceed10min		IR_Authentication_Timer;	/*红外认证有效定时器，初值固定为30min*/
	uchar8						SI_JBaseTimer;
	Str_TimerExceed10min		SI_JTimer;
	Str_TimerExceed10min		ProgramKey_Timer;			/*编程开关*/
	Str_TimerExceed10min		ID_Authentication_T_Timer;	/*终端身份认证有效定时器，初值固定为30min*/
	Str_RstModule				RstModuleParm;				/*复位模块相关参数*/
	uchar8						BDSC_RecentClock[7];		/*broadcastSetClck，最近一次广播校时时间 YYMMDDhhmmss*/
	Str_ProgRecord				ProgRecord;					/*通讯模块兜的编程记录需要全局变量，卡处理模块中 可以设计成内部变量*/
    Str_ProgRecord_645			ProgRecord_645;  			/*645编程记录增加*/
	ushort16					Init_GPRS_DisplayTimer;		/*GPRS信号强度,20min不写信号强度则将信号强度清零,不再显示*/
	Str_TimerExceed10min		IR_Authentication_Timer_645;
}Str_Comm_Parse;

#define	C_SI_JBTimer_2500		5
extern Str_Comm_Parse			SV_Comm_Parse;

/*简写*/
#define	KEY02ErrNum				SV_Comm_Parse.SPTVariable.Key0204_ErrNum
#define	KEY04ErrNum				SV_Comm_Parse.SPTVariable.Key04_ErrNum
#define	SPTNum					SV_Comm_Parse.SPTVariable.Num
#define	SPTRecentClock			SV_Comm_Parse.SPTVariable.RecentClock
#define	SPTCrc					SV_Comm_Parse.SPTVariable.Crc

/*简写身份认证、红外、编程开关都是基于500ms基本节拍。*/
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

/*698兼容645协议，红外定时器*/
#define	IR_AuthT_645			SV_Comm_Parse.IR_Authentication_Timer_645
#define	IR_AuthT_BaseTimer_645	SV_Comm_Parse.IR_Authentication_Timer_645.BaseTimer
#define	IR_AuthT_Timer_645		SV_Comm_Parse.IR_Authentication_Timer_645.Timer
#define	IR_AuthT_Crc_645		SV_Comm_Parse.IR_Authentication_Timer_645.Crc


/*简写，软IJ定时器基于2500ms*/
#define	SI_JTimer_BSOn2500		SV_Comm_Parse.SI_JTimer
#define	SI_JT_BaseTimer			SV_Comm_Parse.SI_JTimer.BaseTimer
#define	SI_JT_Timer				SV_Comm_Parse.SI_JTimer.Timer
#define	SI_JT_Crc				SV_Comm_Parse.SI_JTimer.Crc
#define	SI_JBaseTimer_2500		SV_Comm_Parse.SI_JBaseTimer			/*软IJ基本节拍，2.5s*/

#define	C_SI_JTimerHaveCRC_Len		7								/*SI_JTimer结构体长度BaseTimer+Timer+Crc*/
#define	C_SI_JTimer_Len				5								/*SI_JTimer结构体长度BaseTimer+Timer*/

#define	C_Init_GPRS_DisplayTimer	2400							/*定时是基于500ms的,因此这里定时2400,20分钟*/
/********* 645数据暂存结构体************/
typedef struct
{
	ulong32		DI;									/*698的数据对象标识OI*/
	uchar8		*SecurityAddr;						/*安全传输起始地址,Frame中HCS后所有数据起始地址*/
	uchar8		*P_APDUStart;						/*APDU起始地址*/
	ushort16	DataLen_698;						/*解密后，数据区数据长度*/
	ushort16	APDULen;							/*APDU总长度*/
	ushort16	FrameBlockFlag;						/*分帧标志*/
	uchar8		Opcode[4];
	uchar8		AddrLen;							/*SA地址长度*/
	uchar8		C;
	uchar8		StandardFlay;						/*规约标志*/
	uchar8		SECURITYFlay[3];					/*是否安全传输标志*/
	uchar8		SICMAC_Type;						/*安全验证结果*/
	uchar8		DataLen;							/*解密后，数据区数据长度*/
    uchar8		Data[C_Comm_Data_MaxLen_698];		/*本缓冲区数据是原始数据域数据，包含DI等数据*/
	uchar8		RN_Data[C_Comm_RNData_MaxLen];		/*本缓冲区数据是原始数据域数据，包含DI等数据*/
	uchar8		AddressFlag;						/* 取值C_MeterAddress,C_Broadcast,C_CondenseAll，C_Condense */
	uchar8		ChannelNo;							/*通道号暂存*/
	uchar8		PowerFlag;							/*调度过来的电源状态暂存*/
	uchar8		MAC_Verify;							/*安全验证结果*/
	uchar8		ClientAddr;							/*客户机地址*/
	uchar8		RNSICBit;							/*权限所占bit位*/
    ushort16  	TimeTageByte;     					/*时间标签所在的字节*/
}Str_Comm_645;

#define	CLen_DI						C_DataCodeLen
#define	CLen_OpCode					4
#define	CLen_CommPW					4
/*Data[C_Comm_Data_MaxLen]中的偏移*/
#define	CDI_O_V_645					C_DI_OFS			/*V_645Frame中DI偏移*/
#define	CPW_SpecialO_V_645			0					/*特殊命令密码偏移*/
#define	CBoardCastData_O_V_645		0					/*广播校时时数据偏移*/
#define	CFreezeParm_O_V_645			0					/*冻结命令数据偏移*/
#define	C17SetBpsData_O_V_645		0					/*17命令设置bps时数据起始偏移*/
#define	C1DData_O_V_645				0					/* 1D命令设置多功能输出时数据起始偏移*/

#define	COpCode_OtherO_V_645		4					/*03等其他命令中OPcode*/
#define	CData_OtherO_V_645			8					/*03等其他命令中data开始的偏移*/
#define	CMaxRMNLen_OtherV_645		(C_Comm_Data_MaxLen - 8)

#define	CPW_14OV_645				C_PW_OFS_14			/*14命令中密码*/
#define	COpcode_14O_V_645			C_OPCode_OFS_14		/*14命令中OpCode*/
#define	CData_14O_V_645				C_Data_OFS_14		/*14命令中数据开始偏移*/
#define	CMaxRMNLen_14V_645			(C_Comm_Data_MaxLen - 12)

#define	C_O_EventClear_DI			8

#define	C_11_SData					4
#define	C_O_FrameNo					4

#define	C_O_SF_Data					4					/*厂内模式设置时，数据开始偏移地址*/

#define	C_O_PW_Cal					2					/*校表时，密码开始偏移*/
#define	C_O_Data_Cal				6					/*校表时，实际校表数据开始偏移*/
#define	C_DILen_Cal					2					/*校表读数据开始偏移*/
/*特殊命令从去除密码、操作码后的有效数据开始偏移定义*/
#define	C_R1_O						0
#define	C_R2_O						1
#define	C_R3_O						2
#define	C_R9_O						8
/*帧格式3的偏移*/
#define	C_F3_O_BlockNum				4
#define	C_F3_O_GivenClock			5
/*负荷记录相关定义*/
#define C_DataAANum					6

/************有独立编程事件的编程项结构体*********/
typedef struct
{
	ulong32	ProgramDI;          	/*事件记录写的标识码*/
	ulong32	GetDataDI_First;		/*获取数据的第 1个标识码*/
	ulong32	GetDataDI_End;			/*获取数据的最后一个标识码*/
}Str_ProgTable;

/***********参数编程项目合法性判断结构体*********/
typedef struct
{
	ulong32	ParmDI;					/*参数标识码*/
	ulong32	Method;					/*方法，见注1*/
}Str_WrParmTable;
/*注1: 见详细设计文档<参数有效性及后续处理>*/
/*Method方法中Bit31-Bit28*/
#define		C_HaveIPEventType				0xF0000000		/*取值如下*/
/*因为本字段只有16种取值范围，因此6月12日决定将编程类事件合并一个方法，*/
/*在该方法中判断标识码，然后进行不同消息触发。*/
#define		C_HaveIPEvent_Invalid			0x00000000
#define		C_HaveIPEvent_ProgParm			0x10000000		/*有独立编程事件*/
#define		C_HaveIPEvent_ReturnMoney		0x20000000		/*退费事件记录*/
#define		C_HaveIPEvent_RstReportState	0x30000000		/*复位主动上报状态字,*/
															/*不是说复位主动上报状态字有编程事件，而是需要特殊处理，不是写数据层*/
#define		C_HaveIPEvent_GPRSSignal		0x40000000
/*Method方法中Bit28-Bit24*/
#define		C_ExtMsgType					0x0F000000		/*取值如下*/
#define		C_ExtMsgType_Invalid			0x00000000		/*无对消息发布*/
#define		C_ExtMsg_ReWorkTime				0x01000000		/*时钟更改消息发布,需单独编写程序*/
#define		C_ExtMsg_ReSettle_Day1			0x02000000		/*第1结算日更改，需要判断修改前后结算日是否相同，相同则不发消息，不同发消息给结算模块*/
#define		C_ExtMsg_SetKeyNum				0x03000000		/*设置密钥总条数消息，触发密钥检查*/

#define		C_ExtMsg_ReLocalWarningPara 	0x0D000000		/*设置本地报警相关参数*/
#define		C_ExtMsg_ReMultiRatesParm		0x0E000000		/*时段费率类参数更改，Other函数统一处理*/
#define		C_ExtMsg_ReDemand_Cycle			0x0F000000		/*需量周期更改,Other函数统一处理*/
/*Method方法中Bit23-Bit16  */
#define		C_ExtMsgDA_StartBit				0x00010000		/*开始位*/
#define		C_ExtMsgDA_MaxNum				8				/*最多有8个消息地址可以发布*/
#define		C_ExtMsgDestAddress				0x00FF0000		/*取值如下*/
#define		C_ExtMsgDA_Demand				0x00010000		/*Bit16:需量消息*/
#define		C_ExtMsgDA_MultiRates			0x00020000		/*Bit17:费率时段判断消息*/
#define		C_ExtMsgDA_Settle				0x00040000		/*Bit18:结算模块*/
#define		C_ExtMsgDA_EnergyMetering		0x00080000		/*Bit19:电能模块*/
/*Method方法中Bit15-Bit13*/
#define		C_DataValidMethodType			0x0000E000		/*取值如下*/
#define		C_DataValid_NoLimit				0x00002000		/*通用方法1，不作限制。Bit12-Bit8值无效*/
#define		C_DataValidBCD_Range			0x00004000		/*通用方法2，BCD，范围AA-BB，Bit12-Bit8，BCD范围方法1-32种*/
#define		C_DataValidOnlyBCD				0x00006000		/*通用方法3，BCD，不作范围限制。Bit12-Bit8值无效*/
#define		C_DataValidHex_Range			0x00008000		/*通用方法4，HEX，范围AA-BB，Bit12-Bit8，HEX范围方法1-32种*/
#define		C_DataValidSpecialMethod		0x0000E000		/*特殊方法，需要调用专用函数进行判断，Bit12-Bit8，特殊方法序号*/
/*Method方法中Bit12-Bit8*/
#define		C_DataValidMethod				0x00001F00		/*取值如下*/
/*针对特殊方法 C_DataValidSpecialMethod*/
#define		C_DV_Date_Time					0x00000100		/*特殊方法之日期时间判断*/
#define		C_DV_Demand_Cycle				0x00000200		/*特殊方法之需量周期*/
#define		C_DV_Sliding_Time				0x00000300		/*特殊方法之滑差周期*/
#define		C_DV_SwitchingTime				0x00000400		/*特殊方法之切换时间(年月日时分)判断*/
#define		C_DV_Comm_Address				0x00000500		/*特殊方法之表地址(BCD,不能全0x99)*/
#define		C_DV_Bps						0x00000600		/*特殊方法之波特率的设置*/
#define		C_DV_Hour_Freeze				0x00000700		/*特殊方法之整点冻结模式字的判断*/
#define		C_DV_HF_InteTime				0x00000800		/*特殊方法之整点冻结间隔时间判断*/
#define		C_DV_Settle_Day					0x00000900		/*特殊方法之结算日有效性*/
#define		C_DV_Return_Money				0x00000A00		/*特殊方法之退费金额，这里需要判断够不够退，不够返回错误*/
#define		C_DV_DayFreezeClock				0x00000B00		/*特殊方法之日冻结时间判断*/
#define		C_DV_Season						0x00000C00		/*特殊方法之时区判断方法*/
#define		C_DV_TimePeriod					0x00000D00		/*特殊方法之时段判断方法*/
#define		C_DV_Ladder						0x00000E00		/*特殊方法之阶梯表判断方法*/
#define		C_DV_DiplayItemSet				0x00000F00		/*特殊方法之显示项目设置(轮显、键显)*/
#define		C_DV_HolidaySet					0x00001000		/*特殊方法之公共假日设置*/
#define		C_DV_RstReport_State			0x00001100		/*特殊方法之主动上报状体字的复位*/
#define		C_DV_Eventpara					0x00001200		/*特殊方法之事件判断参数*/
#define		C_DV_Position					0x00001300		/*特殊方法之电能表位置信息*/
#define		C_DV_Date_Time_645				0x00001400		/*特殊方法之日期时间,645中0x04000101/0x04000102判断*/
#define		C_DV_ReportChannel				0x00001500		/*特殊方法之上报通道判断*/
/*针对通用方法4  C_DataValidHex_Range*/
#define		C_DV_HexRange_1_14				0x00000100		/*Hex范围:1-14*/
#define		C_DV_HexRange_1_8				0x00000200		/*Hex范围:1-8*/
#define		C_DV_HexRange_Rates				0x00000300		/*Hex范围:1-12 费率数判断方法*/
#define		C_DV_HexRange_0_20				0x00000400		/*Hex范围:0-20*/
#define		C_DV_HexRange_0_6				0x00000500		/*Hex范围:0-6*/
#define		C_DV_HexRange_1_99				0x00000600		/*Hex范围:1-99*/
#define		C_DV_HexRange_5_20				0x00000700		/*Hex范围:5-20*/
#define		C_DV_HexRange_0_4				0x00000800		/*Hex范围:0-4*/
#define		C_DV_HexRange_5_30				0x00000900		/*Hex范围:5-30*/
#define		C_DV_HexRange_0_60				0x00000A00		/*Hex范围:0-60*/
#define		C_DV_HexRange_0_1				0x00000B00		/*Hex范围:0-1*/
#define		C_DV_HexRange_0_3				0x00000C00		/*Hex范围:0-3*/
#define		C_DV_HexRange_1_32				0x00000D00		/*Hex范围:1-32*/

/*Method方法中Bit7-Bit0*/
#define		C_IsAddFixedDataLen				0x00000080		/*取值如下*/
#define		C_AddFixedDataLen				0x00000080		/*october、visiblestring、bitstring格式数据补齐固定长度0x00*/
#define		C_UnAddFixedDataLen				0x00000000		/*不用按固定长度补齐0x00*/

#define		C_DataLenFixedFlag				0x00000040		/*取值如下*/
#define		C_DataLenFixed_OK				0x00000040		/*数据长度固定，固定时长度必须小于63，否则认为不固定*/
#define		C_DataLenUnsized				0x00000000		/*数据长度不固定*/

#define		C_DataLenFixed					0x0000003F		/*取值如下*/
#define		C_UnsizedLen_Method				0x0000003F		/*取值如下*/
#define		C_UnsizedLen_LSTime				0x00000001		/*不定长判断方法-负荷记录起始时间*/
#define		C_UnsizedLen_PW			    	0x00000002		/*密码，需要将长度改成03长度*/
#define		C_UnsizedLen_S_PT				0x00000003		/*时区表时段表长度判断方法*/
#define		C_UnsizedLen_Date				0x00000004		/*日期设置，判断长度是否正确且需调整数据为0400010C格式*/
#define		C_UnsizedLen_Time				0x00000005		/*时间设置，判断长度是否正确且需调整数据为0400010C格式*/
#define		C_UnsizedLen_BackUpLadder		0x00000006		/*设置备用套阶梯表参数，长度大于63字节，需要特殊处理*/
#define		C_UnsizedLen_BackUpRateFFPrice	0x00000007		/*设置备用套费率电价数据块参数，长度应该小于132字节，且能被4整除*/
#define		C_UnsizedLen_ReportChannel		0x00000008	    /*上报通道长度，不足13字节高位补0*/
/*698兼容645增加*/
#define 	C_NeedChangeTo698 				0x55
#define 	C_Normal645 					0x00
#define 	C_ASCII_A   					0x41   			/*A对应的ASCII码0x41*/
#define 	C_ASCII_0   					0x30   			/*0对应的ASCII码0x30*/
#define 	C_ASCII_9   					0x39   			/*9对应的ASCII码0x39*/

#define 	C_2015CLEAR 					0x01 			/*/2015确认上报*/
#define 	C_EventCLEAR 					0x02 			/*/2015确认上报*/

#define 	C_ProgramEventClearDI  			0x033000FF

#define 	C_BCDMax_OneBit  				0x63   			/*1字节BCD最大99，用于判断Hex转BCD后，是否会大于1字节*/
#define 	C_BCDMax         				0x99   			/*1字节BCD最大0x99*/
#define 	C_BCDMax_TwoBit  				0x270F 			/*2字节BCD最大9999，用于判断Hex转BCD后，是否会大于2字节*/

typedef struct
{
	uchar8	DI2;        		/*645DI2*/
	uchar8  OIB;				/*698OIB */
}Str_DI2ToOIB;


typedef struct
{
	uchar8	BitN0;        		/*bit位*/
	uchar8  EventN0;			/*事件号*/
}Str_ReportEventNo;

/*698主动上报状态字*/
#define C_Report_Bit0	 		0        	/*负荷开关误动作*/
#define C_Report_Bit3    		3		  	/*时钟电池电压低*/
#define C_Report_Bit7    		7		  	/*时钟故障*/
#define C_Report_Bit8    		8		  	/*停电抄表电池欠压*/
#define C_Report_Bit10   		10			/*开盖*/
#define C_Report_Bit11   		11		  	/*开端钮盖*/
#define C_Report_Bit12   		12         	/*恒定磁场干扰 */
#define C_Report_Bit13   		13         	/*电源异常 */
#define C_Report_Bit14   		14         	/*跳闸  */
#define C_Report_Bit15   		15         	/*合闸  */
#define C_Report_Bit16   		16         	/*A相失压 */
#define C_Report_Bit17   		17       	/*A相欠压*/
#define C_Report_Bit18   		18       	/*A相过压 */
#define C_Report_Bit19   		19         	/*A相失流 */
#define C_Report_Bit20   		20         	/*A相过流 */
#define C_Report_Bit21   		22       	/*A相功率反向*/
#define C_Report_Bit22   		23       	/*A相断相*/
#define C_Report_Bit32   		32         	/*B相失压 */
#define C_Report_Bit33   		33       	/*B相欠压*/
#define C_Report_Bit34   		34       	/*B相过压 */
#define C_Report_Bit35   		35         	/*B相失流 */
#define C_Report_Bit36   		36         	/*B相过流*/
#define C_Report_Bit38   		38       	/*B相功率反向*/
#define C_Report_Bit39   		39       	/*B相断相 */
#define C_Report_Bit48   		48         	/*C相失压*/
#define C_Report_Bit49   		49         	/*C相欠压*/
#define C_Report_Bit50   		50         	/*C相过压 */
#define C_Report_Bit51   		51         	/*C相失流 */
#define C_Report_Bit52   		52         	/*C相过流 */
#define C_Report_Bit54   		54         	/*C相功率反向 */
#define C_Report_Bit55   		55         	/*C相断相*/
#define C_Report_Bit64   		64         	/*电压逆相序*/
#define C_Report_Bit66   		66         	/*电压不平衡*/
#define C_Report_Bit69   		69         	/*掉电 */
#define C_Report_Bit73   		73         	/*双协议中的总有功功率反向*/
#define C_Report_Bit74   		74         	/*全失压*/
#define C_Report_Bit80   		80         	/*编程 */
#define C_Report_Bit81   		81         	/*电表清零*/
#define C_Report_Bit82   		82         	/*需量清零*/
#define C_Report_Bit83   		83         	/*事件清零 */
#define C_Report_Bit84   		84          /*校时 */

#define C_MeterStatus_Bit0   	0
#define C_MeterStatus_Bit1   	1

#define C_WordLen   			8
#define C_ReportStateJudge   	1  							/*用于主动上报状态字移位判断用*/
extern const Str_ReportEventNo 	TB_ReportEventNo[CReport_645_Judge_Num];

/*********************主动上报相关变量和宏定义***************************************/
#define	C_ReportStateNum		96
#define	C_ReportStateByteNum	12
static	uchar8	SV_ReportNewAddNum[C_ReportStateNum + 2];	/*96字节新增上报次数*/
typedef struct
{
	uchar8		State[C_ReportStateByteNum];				/*12字节已上报字节数。已上报为1*/
	ushort16	Timer;										/*主动上报状态字自动复位延时时间  基于500ms  这个时间，如果掉电，则不包括掉电时间*/
	ushort16 	CRC16;
}Str_HaveReport;
static	Str_HaveReport	SV_HaveReportState;

typedef struct
{
    uchar8 		ReportMode645_Bit;							/*645主动上报模式字bit*/
    uchar8 		OIB;										/*698中事件的OIB*/
    uchar8 		Nature;										/*698中上报标识对应的属性*/
    uchar8 		Report698_2015_Bit;							/*698中2015中的bit(不在2015中为NULL)*/
}Str_DriveReport_Change;
extern const Str_DriveReport_Change Pstr_DriveReport_Change[];

/*645主动上报模式字*/
#define		C_ReportMode645_Bit0        0					/*负荷开关误动误动作   */
#define		C_ReportMode645_Bit1        1           		/*ESAM错误         */
#define		C_ReportMode645_Bit2        2           		/*内卡初始化错误  */
#define		C_ReportMode645_Bit3        3           		/*时钟电池电压低*/
#define		C_ReportMode645_Bit4        4           		/*内部程序错误   */
#define		C_ReportMode645_Bit5        5           		/*存储器故障或损坏 */
#define		C_ReportMode645_Bit6        6           		/*保留    */
#define		C_ReportMode645_Bit7        7           		/*时钟故障 */
#define		C_ReportMode645_Bit8        8           		/*停电抄表电池欠压 */
#define		C_ReportMode645_Bit9        9           		/*透支状态  */
#define		C_ReportMode645_Bit10		10          		/*开表盖 */
#define		C_ReportMode645_Bit11       11          		/*开端钮盖 */
#define		C_ReportMode645_Bit12       12          		/*恒定磁场干扰  */
#define		C_ReportMode645_Bit13       13          		/*电源异常 */
#define		C_ReportMode645_Bit14       14          		/*跳闸成功*/
#define		C_ReportMode645_Bit15       15          		/*合闸成功*/
#define		C_ReportMode645_Bit16       16          		/*失压   */
#define		C_ReportMode645_Bit17       17          		/*欠压   */
#define		C_ReportMode645_Bit18       18          		/*过压   */
#define		C_ReportMode645_Bit19       19          		/*失流   */
#define		C_ReportMode645_Bit20       20          		/*过流   */
#define		C_ReportMode645_Bit21       21          		/*过载   */
#define		C_ReportMode645_Bit22       22          		/*功率反向*/
#define		C_ReportMode645_Bit23       23          		/*断相*/
#define		C_ReportMode645_Bit24       24          		/*断流 */
#define		C_ReportMode645_Bit25       25          		/*保留 */
#define		C_ReportMode645_Bit26       26          		/*保留*/
#define		C_ReportMode645_Bit27       27          		/*保留 */
#define		C_ReportMode645_Bit28       28          		/*保留 */
#define		C_ReportMode645_Bit29       29          		/*保留 */
#define		C_ReportMode645_Bit30       30          		/*保留 */
#define		C_ReportMode645_Bit31       31          		/*电压逆相序*/
#define		C_ReportMode645_Bit32       32          		/*电流逆相序*/
#define		C_ReportMode645_Bit33       33          		/*电压不平衡*/
#define		C_ReportMode645_Bit34       34          		/*电流不平衡*/
#define		C_ReportMode645_Bit35       35          		/*辅助电源失电*/
#define		C_ReportMode645_Bit36       36          		/*掉电 */
#define		C_ReportMode645_Bit37       37          		/*需量超限  698分为正向3009、反向300A、无功30 */
#define		C_ReportMode645_Bit38       38          		/*总功率因数超下限 */
#define		C_ReportMode645_Bit39       39          		/*电流严重不平衡 */
#define		C_ReportMode645_Bit40       40          		/*潮流反向 698潮流反向做在功率反向里  */
#define		C_ReportMode645_Bit41       41          		/*全失压*/
#define		C_ReportMode645_Bit42       42          		/*保留*/
#define		C_ReportMode645_Bit43       43          		/*保留 */
#define		C_ReportMode645_Bit44       44          		/*保留 */
#define		C_ReportMode645_Bit45       45          		/*保留  */
#define		C_ReportMode645_Bit46       46          		/*保留 */
#define		C_ReportMode645_Bit47       47          		/*保留 */
#define		C_ReportMode645_Bit48       48          		/*编程 */
#define		C_ReportMode645_Bit49       49          		/*电表清零*/
#define		C_ReportMode645_Bit50       50          		/*需量清零*/
#define		C_ReportMode645_Bit51       51          		/*事件清零*/
#define		C_ReportMode645_Bit52       52          		/*校时  */
#define		C_ReportMode645_Bit53       53          		/*时段表编程 */
#define		C_ReportMode645_Bit54       54          		/*时区表编程*/
#define		C_ReportMode645_Bit55       55          		/*周休日编程*/
#define		C_ReportMode645_Bit56       56          		/*节假日编程 */
#define		C_ReportMode645_Bit57       57          		/*有功组合方式编程 */
#define		C_ReportMode645_Bit58       58          		/*无功组合方式1编程 698只有无功组合方式编程*/
#define		C_ReportMode645_Bit59       59          		/*无功组合方式2编程*/
#define		C_ReportMode645_Bit60       60          		/*结算日编程 */
#define		C_ReportMode645_Bit61       61          		/*费率参数表编程*/
#define		C_ReportMode645_Bit62       62          		/*阶梯表编程  */
#define		C_ReportMode645_Bit63       63          		/*密钥更新  */

/*698跟随上报模式字2015 */
#define		C_Report698_2015_Bit1      	1   				/*ESAM错误*/
#define		C_Report698_2015_Bit3      	3 					/*时钟电池电压低*/
#define		C_Report698_2015_Bit5      	5 					/*存储器故障或损坏*/
#define		C_Report698_2015_Bit8      	8 					/*停电抄表电池欠压*/
#define		C_Report698_2015_Bit9      	9 					/*透支状态*/
#define		C_Report698_2015_Bit14     	14					/*跳闸成功*/
#define		C_Report698_2015_Bit15     	15					/*合闸成功*/
#define		C_Report698_2015_Bit30     	30					/*外置继电器反馈信号 断*/
#define		C_Report698_2015_Bit31     	31					/*外置继电器反馈信号 通*/

#define 	CL_OI2Len 					0x01  				/*OI2长度*/

#define 	C_SeverseToClient			0x89
#define 	C_ClientToSeverse			0x98

typedef  struct
{
	ulong32 ChannelOAD;
}Str_ChannelOAD;

/********************* 以下为内部函数原型 ************************************************/
/*通信内部加取消息标志*/
void		Comm_AppendMsg(ulong32	MsgNum);
ulong32		Comm_FetchMsg(void);
/*通信交互缓冲区相关*/
Str_Comm_Parm	* Get_Str_Comm_Parm_Pointer(uchar8 CommNo);
void		Comm_WR_TxData_ToCtrbyte(Str_Comm_Parm *pStr_Comm_Parm_Address, uchar8 Rx_CtrByte);
void		Comm_Response_Set_ReadErr(uchar8  Err, Str_Comm_645 *pV_645Frame);
void		Comm_Response_03_Err(ushort16  SERR, Str_Comm_645 *pV_645Frame);
void		Comm_11_03Response_Normal(Str_Comm_645 *pV_645Frame, uchar8	*pData,uchar8 DataLen);
void		Comm_Response_FromP_Normal(Str_Comm_645 * pV_645Frame, uchar8	*pData,uchar8 DataLen);
void		Comm_IfHaveNxtFrame_Set_C(Str_Comm_645 * pV_645Frame);
void		Comm_SetFrameNo(uchar8	CommNo, uchar8	FrameNo);
void		CommMSg_StartTxd(uchar8 	CommNo);

/*几个超过10min定时器*/
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

/*后续帧*/
void		Init_SV_CommNxtFrame (uchar8	CommNo);
void		Set_SV_CommNxtFrame (uchar8 CommNo,Str_Comm_NxtFrame *pNxtFrame);
uchar8		Get_SV_CommNxtFrame (uchar8 CommNo, Str_Comm_NxtFrame *pNxtFrame);

/*和调度打交道的发送消息*/
void		Comm_SendMsg(uchar8 *pParm,uchar8 ParmLen,uchar8 DestMsg);
void		Comm_SendMsgToDisp(uchar8 DispSign,uchar8	DispMode,ushort16 Duration);
void		LightenCommSign(uchar8	CommNo,uchar8	PowerFlag);
void		Comm_A_MsgToDispatchQueue_UpKeyR(uchar8 PT_Type);
void		Comm_SendMsgForUpdataParm(uchar8	ParmType,uchar8	DestMsg);

/*密钥更新*/
uchar8		Get_AllTemporaryKeyState(void);
void		Init_AllTemporaryKeyState(void);
void		Comm_UpdataKey_Review(uchar8	PT_Type);
/*编程*/
void		Have_IPEvent_Prog(Str_ProgTable *pProgTable,uchar8 TabLineNum,Str_Comm_645 *pV_645Frame);
void		Have_IPEvent_MeterClear(Str_Comm_645 *pV_645Frame );
void		Have_IPEvent_DemandClear(Str_Comm_645 *pV_645Frame);
void		Have_IPEvent_EventClear(Str_Comm_645 *pV_645Frame,ulong32 V_ulOAD);
void		Have_IPEvent_ProgDateTime(Str_Comm_645 *pV_645Frame);
void		Have_IPEvent_ProgRate(Str_Comm_645 *pV_645Frame);
/*主动上报相关函数*/
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
/*解析*/
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

/*特殊命令解析*/
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

/*14命令解析*/
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
/*11 12解析命令*/
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
/*03命令解析*/
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
/*定时消息处理*/
void		Comm_500ms_Execute(uchar8		PowerFlag);
/*其他*/
ushort16	GetAutoDispCycleTime(void);
void		DealWith_RstModule(uchar8	IsPowerOnFlag);

extern void  OneDataReversed(uchar8 *pSBuf, uchar8 *pDBuf,uchar8 Len);
extern void OneByteReverse(uchar8 *pV_Sourcedata);

/*总的编程记录相关*/
void		INF_Init_Str_ProgRecord (Str_ProgRecord		*pProgRecord);
uchar8	Get_ProgRecord1InRam(uchar8	*pProgRecordInRam,Str_ProgRecord *pProgRecord);

uchar8 SF_GetAPDU_EventRead_645(Str_Comm_645 *pV_645Frame,uchar8 *P_DataBuf,ushort16 *P_DataLength);

void	SF_Clear645_ReportNewAddNum(uchar8 V_ucEventNo,uchar8 V_ucFlag);

/***********698兼容645增加*****************************************************/
#define C_DataOffset_Time 			4   			/*698事件清零事件记录中事件发生时间偏移*/
#define C_DataOffset_OAD  			19  			/*698事件清零事件记录中事件数据标识偏移*/
#define C_EventClr_Len  			( 6 + 4 + 4 ) 	/*645事件清零记录长度（6发生时间 4操作者代码 4数据标识）*/
#define C_EventClr_Offset  			10  			/*645主动上报状态字中的电表清零bit81所在偏移*/
#define C_NoChangeEvent 			0xFF   			/*645和698表格不能转换的标志Pstr_DriveReport_Change*/

#define	C_O_CPUNum					0				/*CPU编号偏移*/
#define	C_O_EncryptKeyNum			1				/*密钥索引偏移*/
#define	C_O_FactorAddress			2				/*分散因子地址偏移*/
#define	C_O_DataAddress				6				/*加密数据偏移*/
#define	C_CPUNum					0				/*CPU编号*/
#define	C_SafeSpace_StartAddr		0				/*保护区起始地址*/
#define	C_SafeSpace_EndAddr			0				/*保护区结束地址*/
#define	C_MinCodeSpace				0x00000000		/*最小代码地址*/
#define	C_MaxCodeSpace				0x0007ffff		/*最大代码地址*/
#define	C_L_FactorLen				0x10			/*分散因子长度*/
#define	C_L_FactorData				0x8				/*分散因子分段偏移*/
#define	C_L_PlainDataLen			0x100			/*待加密数据长度*/
#define	C_L_CipherData				0x40			/*密文数据长度*/
#define	C_L_PlainDataLen_698		0x400			/*待加密数据长度*/

#define	C_L_RandLen				    0x40			/*随机数长度*/
#define	C_L_RandData				0x10			/*随机数异或数据长度*/

#define C_Buf_MaxLen 				2000

void Comm_SoftwareCampare(Str_Comm_645	*pV_645Frame);
void Comm_Parse_698(uchar8 CommNo, uchar8	PowerFlag);
uchar8 InF_ConectTimer_Deal(void);
uchar8 InF_Judge_EventOAD_OP(ulong32 V_OAD, uchar8 *pEventLineNO);

#define	C_TB_ProgTimePeriod_Len 	0x04
extern	const	Str_ProgTable		TB_ProgTimePeriod[C_TB_ProgTimePeriod_Len];

#define	C_TB_ProgSeason_Len			0x01
extern	const	Str_ProgTable 		TB_ProgSeason[C_TB_ProgSeason_Len];
/*周休日*/
#define	C_TB_ProgWeekRest_Len		0x01
extern	const	Str_ProgTable		TB_ProgWeekRest[C_TB_ProgWeekRest_Len];
/*结算日1-3采用同一个表格*/
#define	C_TB_ProgSetADate_Len		0x01
extern	const	Str_ProgTable		TB_ProgSetADate[C_TB_ProgSetADate_Len];

/*有功组合状态字*/
#define	C_TB_ProgCombState_P_Len	0x01
extern	const	Str_ProgTable		TB_ProgCombState_P[C_TB_ProgCombState_P_Len];
/*无功组合状态字1*/
#define	C_TB_ProgCombState_Q1_Len	0x01
extern	const	Str_ProgTable		TB_ProgCombState_Q1[C_TB_ProgCombState_Q1_Len];
/*无功组合状态字2*/
#define	C_TB_ProgCombState_Q2_Len	0x01
extern	const	Str_ProgTable		TB_ProgCombState_Q2[C_TB_ProgCombState_Q2_Len];
/*无功组合状态字698*/
#define	C_TB_ProgCombState_Q698_Len	0x01
extern const	Str_ProgTable		TB_ProgCombState_Q698[C_TB_ProgCombState_Q698_Len];
/*阶梯表编程记录*/
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

#define C_ResetDealConectTime		0x86	/*清零应用连接时间*/
#define C_ReworkDealConectTime		0x68	/*同步应用连接时间*/
#define C_PowerUpDealConectTime		0x45	/*上电处理应用连接时间*/
#define C_SynDealConectTime			0x0		/*定时刷新应用连接时间*/
/*复旦微时钟调校*/
union B16_B08
{
	unsigned char B08[2];
};
union B16_B08_2						/*小端存储(51为大端)*/
{
	unsigned short	B16;
	unsigned char	B08[2];
};

struct TEMPERATURE_FRM
{
	uchar8		Offset[8];				/*温度调整系数8字节*/
	uchar8		RtcTMode;				/*RTC补偿工作模式，0x55:测试模式，0xAA常温查表插值模式，其他：普通模式*/
	uchar8		krh;					/*晶体系数常温修调值*/
	uchar8		krl;
	union B16_B08 	Crc16;				/*CRC校验码*/
};
extern struct	TEMPERATURE_FRM		Tpara;


struct RTC_TRIMA_FRM
{
	ushort16	PTAT_Value[21];			/*温度ADC*/
	union B16_B08 	Crc16;				/*CRC校验码*/
};
struct RTC_TRIMV_FRM
{
	short16	Trim_Value[21];				/*补偿值*/
	union B16_B08 	Crc16;				/*CRC校验码*/
};

struct RTC_TRIM_FRM
{
	struct RTC_TRIMA_FRM	TAdc;
	struct RTC_TRIMV_FRM	TVal;
	short16					TestTrim;
	uchar8					TempFlag;	/*查表表格温度标志 0=常温，1=低温，2=高温*/
	float					CFixTrim;	/*查表中心误差*/
};

extern struct	RTC_TRIM_FRM	RTC_RT;
/*2020标准主动上报2005*/
#define C_ReportInit        0xFF
#define C_ReportInitTime    ( ( C_ShutRealTimeData / 200 + C_PowerFail_Judge_Time ) + 4 )   /*1s处理一次,闭锁时间为电能表功能闭锁时间+掉电判断时间+4，上电闭锁10s*/
void Comm_SendMsgToComm(void);
void CommMSg_StartTxd_698(uchar8 CommNo);
extern void Card_DispDynamicSign(void);
extern ConectRequest_Type	Com_Conect;			/*通信应用连接结构体*/

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

