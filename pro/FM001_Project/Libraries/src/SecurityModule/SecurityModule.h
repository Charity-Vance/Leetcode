/*******************************************************************************
Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     SecurityModule.h
Version:       V1
Author:        jiangzs
Date:          2014-3-31
Description:   安全文件
---------------------------------------------------------------------------------
History1:      第1次修改
内容1. Date:   20211021
   	   Author: lx
       Modification:
	   ---------------------------------------------------------------------------
内容2. Date:
   	   Author:
       Modification:
----------------------------------------------------------------------------------
History2:      第2次修改
内容1. Date:
   	   Author:
       Modification:
	   ---------------------------------------------------------------------------
内容2. Date:
   	   Author:
       Modification:
******************************************************************************/ 

#ifndef	__SecurityModule_H
#define	__SecurityModule_H

#include    "Public.h"
#include    "SecurityCommunication.h"

extern ulong32 GV_EsamTime;				/*Esam同步时间*/

extern ConectRequest_Type	Com_Conect;	/*通信应用连接结构体*/

/*******************************数据验证信息******************************************/

/*加密方法宏定义*/
#define	PlainData_MAC_698 	0x11
#define	CodedData_698 		0xA6
#define	CodedData_MAC_698 	0xA7


/*数据长度宏定义*/
#define	AuthMaxLength_698 	52
#define	MaxLength_698    	2048

#define	AuthSessionData1Len_698   		0x20
#define	AuthSessionData2Len_698   		0x30
#define	AuthSessionData2Len_698_termal  0x40 	/*终端服务器随机数*/
#define	IRidRequestData1Len_698   		0x08	/*图片0X10*/
#define	IRidRequestData2Len_698   		0x08

#define	C_DataID_Length_698	4		/*标识长度*/
#define	C_MAC_Length_698	4		/*MAC长度*/
#define	C_len_698			1		/*长度占1字节*/

/******************** 钱包初始化 *********************************************/
#define	C_PreSetMoney_len_698		4	/*预置金额*/

/******************** 钱包充值和退费 *********************************************/
#define	C_BuyMoney_len_698   		4	/*购电金额*/
#define	C_BuyMoneyNum_len_698		4	/*购电次数*/
#define	C_ClientNum_len_698			6	/*客户编号*/

/********************  ESAM方法宏定义  *********************************************/
#define	C_EsamAction_Reset			1	/*复位*/
#define	C_EsamAction_Action			2	/*执行*/
#define	C_EsamAction_ReadData		3	/*数据读取*/
#define	C_EsamAction_DataUpdate		4	/*数据更新*/
#define	C_EsamAction_Unvalid			5	/*协商失效*/
#define	C_EsamAction_MoneyAction	6	/*钱包操作*/
#define	C_EsamAction_KetUpdate		7	/*密钥更新*/
//#define	C_EsamAction_Reset   		8	/*证书更新*/
#define	C_EsamAction_Auth_Time		9	/*协商时效设置*/
#define	C_EsamAction_MoneyInit		10	/*钱包初始化*/
#define	C_EsamAction_IRRequest		11	/*红外认证请求*/
#define	C_EsamAction_IRID			12	/*红外认证*/

/********************  钱包操作宏定义  *********************************************/
#define	C_OpenAccount		0		/*开户*/
#define	C_MoneyAdd			1		/*钱包充值*/
#define	C_MoneyReturn		2		/*钱包退费*/


/********************  ESAM7816 命令表格  *********************************************/
#define	CLen_LC_Len_698				2					/*Lc长度，2个字节*/
#define	CLen_TB_ESAM_4_698			4					/*ESAM命令表格不含第5字节（第5字节肯定为Lc或Le或为空(空为情况1))*/
#define	CLen_TB_ESAM_Lc_698			5					/*ESAM命令表格含Lc(情况3或4)*/
#define CLen_TB_ESAM_6_698			6

const	uchar8	TB_ReadEsamInfoAll_698[CLen_TB_ESAM_4_698] = {0x80,0x36,0x00,0xff}; 				/*读esam全部信息*/
const	uchar8	TB_ReadEsamInfoAll_698_termal[CLen_TB_ESAM_4_698] = {0x80,0x36,0x00,0xfe};			/*读终端esam全部信息*/
const	uchar8	TB_ReadEsamInfo_698[CLen_TB_ESAM_4_698] = {0x80,0x36,0x00,0x00}; 					/*读esam全部信息*/
const	uchar8	TB_Authentication_698[CLen_TB_ESAM_Lc_698] = {0x81,0x02,0x00,0x00,0x00};			/*身份认证命令头包含数据长度*/
const	uchar8	TB_Authentication_698_termal[CLen_TB_ESAM_Lc_698] = {0x82,0x02,0x00,0x00,0x00};		/*主战身份认证命令头包含数据长度*/
const	uchar8	TB_Encrypt_RN_PlainData_MAC_698[CLen_TB_ESAM_4_698] = {0x80,0x0E,0x40,0x02};		/*读数据加密 明文+MAC(带RN)*/
const	uchar8	TB_Encrypt_RN_EncodedData_698[CLen_TB_ESAM_4_698] = {0x80,0x0A,0x40,0x02};			/*读数据加密 密文(带RN)*/
const	uchar8	TB_Encrypt_RN_EncodedData_MAC_698[CLen_TB_ESAM_4_698] = {0x80,0x10,0x40,0x02};		/*读数据加密 密文+MAC(带RN)*/
const	uchar8	TB_Encrypt_EncodedData_MAC_698[CLen_TB_ESAM_4_698] = {0x81,0x1c,0x00,0x00};			/*读数据加密 密文+MAC(带RN)*/

/*增加终端加密数据命令头*/
const	uchar8	TB_Encrypt_EncodedData_Plain_MAC_698_terminal[CLen_TB_ESAM_4_698] = {0x82,0x24,0x00,0x11}; 			/*终端读数据加密 密文+MAC(带RN)*/
const	uchar8	TB_Encrypt_EncodedData_Plain_MAC_698_terminal_back[CLen_TB_ESAM_4_698] = {0x80,0x24,0x11,0x00}; 	/*终端读数据加密 密文+MAC(带RN)*/
const	uchar8	TB_Encrypt_EncodedData_698_terminal[CLen_TB_ESAM_4_698] = {0x82,0x24,0x00,0x12}; 					/*终端读数据加密 密文+MAC(带RN)*/
const	uchar8	TB_Encrypt_EncodedData_MAC_698_terminal[CLen_TB_ESAM_4_698] = {0x82,0x24,0x00,0x13}; 				/*终端读数据加密 密文+MAC(带RN)*/
const	uchar8	TB_Encrypt_EncodedData_MAC_698_terminal_back[CLen_TB_ESAM_4_698] = {0x80,0x24,0x13,0x00};			/*终端读数据加密 密文+MAC(带RN)*/

/*2020标准主动上报2005*/
const	uchar8	TB_Encrypt_Report_RN_MAC_698[CLen_TB_ESAM_4_698] = {0x80,0x14,0x01,0x03}; 	    		/*主动上报加密 明文+MAC(带RN)*/
const	uchar8	TB_Encrypt_Report_MAC_698[CLen_TB_ESAM_4_698] = {0x80,0x0E,0x40,0x81}; 	        		/*主动上报响应解密 明文+MAC*/

const	uchar8	TB_IR_ID_Request_698[CLen_TB_ESAM_6_698] = {0x80,0x08,0x08,0x03,0x00,0x10}; 			/*红外认证请求*/
const	uchar8	TB_IR_ID_Request_698_Termal[CLen_TB_ESAM_6_698] = {0x80,0x08,0x00,0x04,0x00,0x08}; 		/*终端身份认证请求*/


const	uchar8	TB_IR_ID_Request2_698[CLen_TB_ESAM_6_698] = {0x80,0x04,0x00,0x08,0x00,0x00}; 			/*红外认证请求*/
const	uchar8	TB_IR_ID_698[CLen_TB_ESAM_6_698] = {0x80,0x06,0x00,0x01,0x00,0x08}; 					/*红外认证请求*/

/*******************************和响应相关******************************************/
#define		C_Resp_61XXType		0xFF00
#define		C_Resp_63CXType		0xFFF0

#define		CL_Send_InIC		60					/*插卡过程中用到发送临时缓冲区长度*/
#define		CL_Response_InIC	60					/*插卡过程中用到接收临时缓冲区长度*/

/*******************************和颠倒相关的宏************************************/
#define	C_OneDataRev			0x00000001			/*一个数据项颠倒*/
#define	CDI_Auth_R				0x00000002			/*身份认证返回需颠倒的方法*/
#define	CDI_TZone_Data			0x00000004
#define	CDI_TZone_PT_Data		0x00000005


#define	C_RItem_Len_Auth		3					/*身份认证需要颠倒的数据项*/
#define	C_RItem_Len_AuthR		3					/*身份认证返回需颠倒的数据项*/
#define	C_RITem_Len_CPTime		2					/*身份认证时长颠倒的数据项*/
/*******************************ESAM命令相关宏************************************/
#define	CLen_TB_ESAM_4				4				/*ESAM命令表格不含第5字节（第5字节肯定为Lc或Le或为空(空为情况1))*/
#define	CLen_TB_ESAM_Lc				5				/*ESAM命令表格含Lc(情况3或4)*/
#define	CLen_TB_ESAM_Le				5				/*ESAM命令表格含Le(情况2)*/
#define	CLen_TB_ESAM_Le_698_Esam	6				/*ESAM命令表格含Le(新6982个字节数据长度)*/
#define	CLen_TB_ESAM_Lc_698_Esam	6				/*ESAM命令表格含Lc(情况3或4)*/
#define	CLen_TB_ESAM_Lc_698_SoftwareCampare	3		/*ESAM命令表格软件比对*/

/**698**/
#define	C_AuthPTime_LByte		0x30				/*身份认证有效时长默认参数低字节*/
#define	C_AuthPTime_HByte		0x00

/**698兼容645协议**/
#define	CLen_Respond_Auth				0		/*身份认证应答数据起始位置偏移K2/Rand4/ESAM序列号*/
#define	CLen_Respond_Auth_Only90		0		/*红外认证应答数据起始位置偏移ESAM序列号/K1/Rand2*/

/*698兼容645协议,二类参数更新，数据偏移,1字节长度+4字节标识码+数据*/
#define	CLen_DataLEN		5             /*数据偏移*/
#define	CLen_DataDILEN		4             /*数据中标识码长度*/

/*******************************变量及类型定义************************************/
static	uchar8	SV_Rand1_4[4];						/*身份认证时主站下发的随机数。*/
static	uchar8	SV_SafeByte;

static	uchar8	SV_UpdateMInEsamTimer;				/*要求状态查询时刷新ESAM有15min闭锁。*/
													/*带开关减定时器基于5s*/
#define	C_SV_UpdateMInEsamTimer		180				/*180*5=900s=15min*/
/******************************* 表格**************************************************/

/********************  数据颠倒分项长度表  *************************************/
const	uchar8	TB_RItem_Len_Auth[C_RItem_Len_Auth] = 
				{CL_Auth_CiphertextK1,CL_Auth_Rand1,CL_Auth_Dis_factor};
				/*{0x08,0x08,0x08}*/
const	uchar8	TB_RItem_Len_AuthR[C_RItem_Len_AuthR] = 
				{CLen_Rand2,CLen_ESAMNo,CLen_AuthPTime};
				/*{0x04,0x08,0x02}*/
const	uchar8	TB_RITem_Len_CPTime[C_RITem_Len_CPTime] = 
				{CLen_AuthPTime,C_MacLen};
				/*{0x02,0x04}*/

#define	C_RItem_Len_RateBak		33				/*费率表32个费率电价+1个Mac*/
const	uchar8	TB_RITem_Len_RateBak[C_RItem_Len_RateBak] = 
				{
					4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
					4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
					4
				};			/*最后1个为Mac*/
#define	C_RITem_Len_LadderBak	18				/*阶梯表6个阶梯值+7个阶梯电价+4个年阶梯+1个Mac*/
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
				/*{4,4,4,4};*/		/*购置(剩余)金额，Mac，购电次数,Mac*/




/********************  ESAM7816 命令表格  *********************************************/
/**698**/
const	uchar8	TB_AuthDistributedkey_698[CLen_TB_ESAM_Lc_698_Esam] = {0x80,0x08,0x08,0x02,0x00,0x10}; 		/*身份认证中采用表号分散密钥包含Lc*/
const	uchar8	TB_AuthDistributedkey_L_698[CLen_TB_ESAM_Le_698_Esam] = {0x80,0x08,0x08,0x01,0x00,0x10}; 	/*身份认证中采用卡号分散密钥包含Lc*/
const	uchar8	TB_GetChallenge_698_Esam[CLen_TB_ESAM_Lc_698_Esam] = {0x80,0x04,0x00,0x00,0x00,0x00};		/*获取随机数命令头，不含Le*/
const	uchar8	TB_CardEncryptingRand1[CLen_TB_ESAM_Lc] = {0x00,0x88,0x00,0x01,0x08};						/*卡片加密随机数1(内部认证)	*/				
const	uchar8	TB_Increase_698[CLen_TB_ESAM_Lc_698_Esam] = {0x80,0x42,0x00,0x00,0x00,0x0C};				/*存款*/
const	uchar8	TB_WriteRecord_698[CLen_TB_ESAM_Lc_698_Esam] = {0x83,0x3e,0x00,0x00,0x00,0x08};				/*写记录文件，P1为记录号需要替换。*/
const	uchar8	TB_Decrease_698[CLen_TB_ESAM_Lc_698_Esam] = {0x80,0x46,0x00,0x00,0x00,0x04};				/*扣款，不带Mac扣款*/
/**698**/


/**698兼容645,645命令**/
const	uchar8	TB_AuthDistributedkey_645[CLen_TB_ESAM_Lc_698_Esam] = {0x80,0x08,0x08,0x03,0x00,0x10}; 		/*身份认证中采用表号分散密钥包含Lc*/
const	uchar8	TB_GetChallenge_645_Esam[CLen_TB_ESAM_Lc_698_Esam] = {0x80,0x04,0x00,0x04,0x00,0x00};		/*获取随机数命令头，不含Le*/
const	uchar8	TB_RdESAMNo_645[CLen_TB_ESAM_Lc_698_Esam] = {0x80,0x36,0x00,0x02,0x00,0x00};				/*读ESAM序列号命令头		*/		
/**698兼容645,645命令**/


const	uchar8	TB_RdESAMNo[CLen_TB_ESAM_Le] = {0x00,0xB0,0x99,0x01,0x08};				/*读ESAM序列号包含Le*/
const	uchar8	TB_AuthDistributedkey[CLen_TB_ESAM_Lc] = {0x80,0xFA,0x00,0x03,0x08}; 	/*身份认证中采用表号分散密钥包含Lc*/
const	uchar8	TB_AuthDistributedkey_L[CLen_TB_ESAM_Lc] = {0x80,0xFA,0x00,0x01,0x08};	/*身份认证中采用卡号分散密钥包含Lc*/
const	uchar8	TB_EncryptingRand1[CLen_TB_ESAM_Lc] = {0x80,0xfa,0x00,0x00,0x08};		/*身份认证中加密随机数1 包含Lc*/
const	uchar8	TB_GetResponse[CLen_TB_ESAM_4] = {0x00,0xC0,0x00,0x00};					/*获取响应的命令头，不含Le*/
const	uchar8	TB_GetChallenge[CLen_TB_ESAM_4] = {0x00,0x84,0x00,0x00};				/*获取随机数命令头，不含Le*/
const	uchar8	TB_Decrease[CLen_TB_ESAM_Lc] = {0x80,0x30,0x01,0x0C,0x05};				/*扣款，不带Mac扣款*/
const	uchar8	TB_IRExtAuth[CLen_TB_ESAM_Lc] = {0x00,0x82,0x00,0x02,0x08};				/*外部认证命令头*/
const	uchar8	TB_UpdateKey[CLen_TB_ESAM_Lc] = {0x84,0xD4,0x01,0xFF,0x20};				/*密钥更新到ESAM的命令*/
const	uchar8	TB_Increase[CLen_TB_ESAM_Lc] = {0x84,0x32,0x01,0x0C,0x0C};				/*存款*/
const	uchar8	TB_WriteRecord[CLen_TB_ESAM_Lc] = {0x04,0xDC,0xFF,0x0c,0x08};			/*写记录文件，P1为记录号需要替换。*/
const	uchar8	TB_SelectFile[CLen_TB_ESAM_Lc] = {0x00,0xA4,0x00,0x00,0x02};			/*选择文件*/
const	uchar8	TB_SoftwareCampare[CLen_TB_ESAM_Lc] = {0x80,0xFA,0x01,0x00,0x40};		/*加密软件比对数据*/

/*读记录文件*/
#define	CLen_TB_ReadRecord		9

#define	C_O_LC				4						/*LC的偏移。*/
#define	C_O_MeterNum		CLen_TB_ReadRecord		/*表号*/

const	uchar8	TB_ReadRecord[CLen_TB_ReadRecord] = 
{
	0x80,0x48,0x00,0x00,0x00,
	0x0d,0x48,0x00,0x00
};			/*读钱包文件*/


#define	CLen_TB_ReadRecord_698		7
const	uchar8	TB_ReadRecord_698[CLen_TB_ReadRecord_698] = {0x80,0x48,0x00,0x00,0x00,0x01,0x00};


												
/*带Mac读二进制文件(ESAM)*/
#define	CLen_TB_ReadBinFileMac		27
#define	C_O_P2						3
#define	C_O_P1						2				/*P1的偏移。*/
#define	C_O_P2_04D6					12
#define	C_O_Lc2						25
#define	C_O_Rand4					13				/* 4  字节随机数偏移*/
#define	C_O_MeterNumBinFile			7				/* 表号偏移*/
#define	C_O_P2BinFile				17				/* P2偏移*/
#define	C_O_lenBinFile				19				/* len偏移*/

const	uchar8	TB_ReadBinFile_Mac[CLen_TB_ReadBinFileMac] = 	/*带Mac读二进制文件*/
{
	0x83,0x2C,0xFF,0xFF,0x15,0x00,0x48,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,
	0xFF,0xFF,
	0x04,0xD6,0x85,0x00,
	0xFF,0xFF
};							

/********************  文件及文件中参数偏移  *********************************************/
/*带Mac写二进制文件。*/
#define	C_F_Pam_Max		CLen_S_BufMaxLen						/*参数最大字节长度*/

/*文件目录*/
/*#define	C_F_MainDir			0xDF01*/

/*********************清零、控制命令中的偏移*************************************************/
#define	CF_O_CMDEndTime		2						/*命令执行的截止时间*/
#define	CL_CMDEndTime		6
#define	CF_O_EventClearDI	(CF_O_CMDEndTime + CL_CMDEndTime)
#define	CL_DI				4
/*********************参数更新文件中的偏移*************************************************/
#define	CF_O_PU_StartA		0						/*参数更新文件中起始地址偏移*/
#define	CF_O_PU_LC			0						/*首字节是长度*/
#define	CF_O_PU_DI			1						/* 1-4 DI*/
#define	CF_O_PU_Data		5						/*数据开始*/
#define	CL_PU_LC			1						/*LC长度*/
#define	CL_DataCode			4						/*DataCode长度*/
/*********************参数信息文件C_F_ParmInf 中的偏移*********************************/
#define	CF_O_ChgRate		10						/*参数信息文件中两套费率切换时间*/
#define	CF_O_Alarm1			16						/*参数信息文件中报警金额1*/
#define	CF_O_Alarm2			20						/*参数信息文件总报警金额2*/
#define	CF_O_RatioCTInParm	24						/*参数信息文件中电流互感器变比*/
#define	CF_O_RatioVTInParm	27						/*参数信息文件中电压互感器变比	*/
#define	CF_O_MNumInParm		30						/*参数信息文件中表号*/
#define	CF_O_CNumInParm		36						/*参数信息文件中客户编号的偏移*/
#define	CF_O_AuthPTime		43						/*参数信息文件中身份认证有效时长偏移*/

/*********************当前套电价C_F_ElePriceBak文件中偏移*********************************************/
#define	CF_O_Ladder			137						/*当前套电价文件中阶梯数据块起始地址。*/


/*********************备用套电价C_F_ElePriceBak文件中偏移*********************************************/
#define	CF_O_Rate1Bak		4						/*备用套电价文件中费率1电价起始地址*/
#define	CF_O_LadderBak		132						/*备用套电价文件中阶梯数据块起始地址。*/

#define	CF_O_ChgLadder		196						/*备用套电价文件中两套阶梯切换时间*/

/*********************密钥状态C_F_LKeyState文件中偏移***************************************/
#define	CF_O_KeyState		0						/*本地密钥状态文件中密钥状态偏移*/

/*********************运行信息C_F_OpParm文件中偏移************************************/
#define	CF_O_RatioCTInOP	5						/*运行信息文件中电流互感器变比*/
#define	CF_O_RatioVTInOP	8						/*运行信息文件中电压互感器变比*/

#define	CF_O_MNumInOP		11						/*运行信息文件中表号*/
#define	CF_O_CNumInOP		17						/*运行信息文件中客户编号*/

#define	CF_O_OPI_ChBal_H_C	23						/*剩余金额在运行信息文件中偏移*/
#define	CF_O_OPI_PEN		27						/*购电次数在运行信息文件中偏移*/
#define	CF_O_OPI_OD_B		31						/*透支金额在运行信息文件中偏移*/

#define	CF_O_OPI_Start		0						/*运行文件起始字节偏移*/
#define	CF_O_OPI_CMD		1						/*运行文件命令码偏移*/
#define	CF_O_OPI_Len		2						/*运行文件长度偏移*/
#define	CF_O_OPI_LawLessIC	39						/*运行文件中非法插卡次数*/
#define	CF_O_OPI_RWRClock	42						/*运行文件中返写日期*/
#define	CF_O_OPI_CS		47							/*运行文件中CS*/
#define	CF_O_OPI_End		48
#define	CL_OPI				49						/*运行文件数据总长度*/
/*************************记录C_F_Purse文件**********************************************************/
/*698用*/
#define	C_ChargeBal_Mac			0x01					/*剩余金额*/
#define	C_PurchasingE_Num_Mac	0x03					/*购电次数*/
#define	C_Custormer_Num			0x05					/*客户编号*/
/*698用*/

/*698兼容645使用*/
#define	C_AuthPTimeP2			0x03					/*获取ESAM信息偏移P2=05，表格C_EsamNatureToAction中位置，会话失效门限+会话时效剩余时间*/
#define C_AuthPTimeRemain  		0x08        			/*会话时效剩余时间数据偏移*/


#define C_Max_EsamLen			200

/**************** 通信设置1类参数表格********************************************/
typedef	struct
{
	ulong32	DI;						/*标识码*/
	uchar8	Len;					/*数据长度，不含Mac*/
	uchar8	FileNo;					/*写到ESAM去的文件号*/
	uchar8	Offset;					/*在FileNo中对应的偏移*/
	uchar8	OffsetInOP;				/*如果写运行文件，对应运行文件中的偏移.否则为oxFF*/
}Str_ParmPlainText;

#define	C_Invalid_Offset			0xFF
#define	C_ParmPlainText_MaxNum		11
const	Str_ParmPlainText	TB_ParmPlainText[C_ParmPlainText_MaxNum] = 
{
	{CChange_Rate,CLChange_Rate,C_F_ParmInf,CF_O_ChgRate,C_Invalid_Offset},						/*两套费率切换时间	*/
	{CChange_Ladder,CLChange_Ladder,C_F_ElePriceBak,CF_O_ChgLadder,C_Invalid_Offset},			/*两套阶梯电价切换时间*/
	{CRatio_Curr_Tran,CLRatio_Curr_Tran_Esam,C_F_ParmInf,CF_O_RatioCTInParm,CF_O_RatioCTInOP},	/*电流互感器变比*/
	{CRatio_Vol_Tran,CLRatio_Vol_Tran_Esam,C_F_ParmInf,CF_O_RatioVTInParm,CF_O_RatioVTInOP},	/*电压互感器变比*/
	{CMeter_Num,CLMeter_Num,C_F_ParmInf,CF_O_MNumInParm,CF_O_MNumInOP},							/*表号*/
	{CCustomer_Num,CLCustomer_Num,C_F_ParmInf,CF_O_CNumInParm,CF_O_CNumInOP},					/*客户编号*/
	{CAlam1_Money,CLAlam1_Money,C_F_ParmInf,CF_O_Alarm1,C_Invalid_Offset},						/*报警金额1*/
	{CAlam2_Money,CLAlam2_Money,C_F_ParmInf,CF_O_Alarm2,C_Invalid_Offset},						/*报警金额2*/
	{0x401E0200,8,C_F_ParmInf,CF_O_Alarm2,C_Invalid_Offset},									/*报警金额2*/
	{CBackUp_RateFF_Price,CLBackUp_RateFF_Price,C_F_ElePriceBak,CF_O_Rate1Bak,C_Invalid_Offset},/*费率电价1*/
	{CBackUp_Ladder_Table,CLBackUp_Ladder_Table,C_F_ElePriceBak,CF_O_LadderBak,C_Invalid_Offset}/*阶梯参数*/
};

/**************** 通信设置1类参数表格********************************************/
typedef	struct
{
	ushort16	V_usDI1DI0;		/*标识码*/
	uchar8		V_ucP2;			/*数据长度，不含Mac*/
	uchar8		V_ucOffset;		/*偏移*/
	uchar8		V_ucLen;		/*数据长度*/
}Str_EsamTable;




/**************** 函数声明********************************************/
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
void 		SF_ColdReset_7816_Esam_No(void);	/*测试ESAM不读取序列号输出*/
extern void InF_Clear698ConectTimer();
#endif

