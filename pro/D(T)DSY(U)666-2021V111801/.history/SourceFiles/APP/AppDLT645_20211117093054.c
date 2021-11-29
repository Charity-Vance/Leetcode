/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    AppDLT645.c                                                                          
**** Brief:       645协议通信函数                                                                     
**** Author:      peter.he@chint.com                                                                 
**** Version:     V1.0                                                                               
**** Date:        2016-7-14                                                                          
****                                                                                                 
**** note:修改历史记录列表，每条修改记录应包括修改日期、修改者                                          
**** 1.  Author:                                                                                     
****     Version:                                                                                    
****     Date :                                                                                      
**** 2.  Author:                                                                                     
****     Version:                                                                                       
****     Date:
****                                                                                        
****  addtogroup:Library                                                             
**********************************************************************************************************/

/*--------------------------------- 文件功能说明 -------------------------------------------------------*/
/*
 *  该文件所有函数的前缀为xxxx_
 *  文件主函数和对外函数需放在文件的首部，并且主函数需要放在第一个位置;
 *  函数注释采用标准模板，函数内部注释采用//;
 *  对于注释较多的部分，可以增加一个注释符，然后详细说明放在文件的尾部;
 *--------------------------------- 文件功能说明 -------------------------------------------------------*/
 
/**有形参的函数格式:*/
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    xx任务处理函数
 *
 *  @param    xx :
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
/**无形参的函数格式:*/
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    上电所有口线配置成初始状态，后面可根据需要开启和配置
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
 
 
/*----------------< 包含文件 >----------------------------------*/

#include "..\SourceFiles\PUB\Include.h"
/*----------------< 常量定义 >----------------------------------*/                                     
#if ( METER_TYPE == METER_TYPE_DDSY666)
const uchar8 code GT_ucaFactoryVerNo[]=
{ 
	0xFF,0xF0,		///* 地区 *///
	0x02,			///* 07协议 *///
	0x00,			///* 蓝牙，无红外485 *///
	0x27,0x06,		///* 硬件版本号 *///
	0x20,0x13,		///* 迭代号 *///
};
const uchar8 code GT_ucaMaterType[10] = {'D','D','S','Y','6','6','6',' ',' ',' '};	///*电表型号 *///
#elif ( METER_TYPE == METER_TYPE_DTSY666)
const uchar8 code GT_ucaFactoryVerNo[]=
{ 
	0xFF,0xF0,		///* 地区 *///
	0x02,			///* 07协议 *///
	0x00,			///* 蓝牙，无红外485 *///
	0x27,0x07,		///* 硬件版本号 *///
	0x40,0x11,		///* 迭代号 *///
};
const uchar8 code GT_ucaMaterType[10] = {'D','T','S','Y','6','6','6',' ',' ',' '};	///*电表型号 *///
#else
const uchar8 code GT_ucaFactoryVerNo[]=
{ ///导轨表后续内部版本号需要升级
	0xFF,0xF0,		///* 地区 *///
	0x02,			///* 07协议 *///
	0x00,			///* 蓝牙，无红外485 *///
	0x27,0x35,		///* 硬件版本号 *///
	0x40,0x10,		///* 迭代号 *///
};
const uchar8 code GT_ucaMaterType[10] = {'D','D','S','Y','/','U','6','6','6',' '};	///*电表型号 *///
#endif
#define	GT_ucaFactoryVerNo_Len	sizeof(GT_ucaFactoryVerNo)

const uchar8 code GT_ucaProtocolVer[16] = {'D','L','/','T',0,'6','4','5','-','2','0','0','7','-','1','4'};	///*协议版本号 *///

uchar8 code C_cBleComm_Head[] = { 0xFE,0xFE,0xFE,0xFE,0x68,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x68,0x00 };	/*和蓝牙模块通信的数据前缀*/
	#define C_cBleComm_Head_Len	sizeof(C_cBleComm_Head)

/*----------------< 宏定义区 >----------------------------------*/
static const  GStr_Comm_MAP code Comm_MAP_TAB[ ]={ 
	///数据标识       RAM地址                            是否可写       E2索引              E2偏移         长度        是否BCD    EE存储是否为HEX
	///ucaDataId     ucaRamAdd                          IsWrite      ucaE2pIndex     	ucaE2offset  ucaDataLen     IsBCD         EEISHEX
	{ 0x00000000 , GStr_Energy.ucaFw_Energy         ,     _FALSE , NO_BITS             ,   NO_BITS ,     4 ,       _TRUE  ,      _FALSE     , }	,   //* 当前总电量    *///0/
	{ 0x00010000 , GStr_Energy.ucaFw_Energy         ,     _FALSE , NO_BITS             ,   NO_BITS ,     4 ,       _TRUE  ,      _FALSE     , }	,   //* 正向电量      *///1/
	{ 0x00020000 , GStr_Energy.ucaBk_Energy         ,     _FALSE , NO_BITS             ,   NO_BITS ,     4 ,       _TRUE  ,      _FALSE     , }	,   //* 反向电量      *///2/
	{ 0x00900201 , GStr_Money. ucaTickMoney         ,     _FALSE , NO_BITS             ,   NO_BITS ,     4 ,       _TRUE  ,      _FALSE     , }	,   //* 透支金额      *///3/
	{ 0x00900200 , GStr_Money. ucaRemainMoney       ,     _FALSE , NO_BITS             ,   NO_BITS ,     4 ,       _TRUE  ,      _FALSE     , }	,   //* 剩余金额      *///4/
//	{ 0x00900200 , GStr_Money. ucaRemainMoney       ,     _FALSE , NO_BITS             ,   NO_BITS ,     4 ,       _TRUE  ,      _FALSE     , }	,   //* 剩余金额      *///5/
	{ 0x03300601 , GStr_PRICE .ucaPurchaseMoneyAll  ,     _FALSE , NO_BITS             ,   NO_BITS ,     4 ,       _TRUE  ,      _FALSE     , }	,   //* 总购电金额      *///6/
	{ 0x02800020 , GStr_PRICE. ucaPrice             ,     _TRUE  , LIB_E2P_Price       ,   0       ,     4 ,       _TRUE  ,      _FALSE     , }	,   //* 电价(修改)          *///7/
//	{ 0x02800020 , GStr_PRICE. ucaPrice             ,     _FALSE  , LIB_E2P_Money       ,   12      ,     4 ,       _TRUE  ,      _FALSE     , }	,   //* 电价          *///7/
	{ 0x04000401 , GStr_MeterIFO. ucaCommAddr       ,     _TRUE  , LIB_E2P_METER_INFO  ,   0       ,     6 ,       _TRUE  ,      _FALSE     , }	,   //* 通信地址      *///8/
	{ 0x04000402 , GStr_MeterIFO. ucaMeterID        ,     _TRUE  , LIB_E2P_METER_INFO  ,   6       ,     6 ,       _TRUE  ,      _FALSE     , }	,   //* 表号          *///9/
	{ 0x0400040E , GStr_MeterIFO. ucaUserID         ,     _TRUE  , LIB_E2P_METER_INFO  ,   12      ,     6 ,       _TRUE  ,      _FALSE     , }	,   ///* 客户编号      *//10/	
//	{ 0x04000703 , &GStr_MeterIFO. ucBpsVal         ,     _TRUE  , LIB_E2P_METER_INFO  ,   18      ,     1 ,       _FALSE ,      _TRUE      , }	,   ///* 波特率特征字  *//11/	
	{ 0x03300100 , &GStr_EventRecordNum.ucEventTimes[0][0] ,   _FALSE , NO_BITS        ,   NO_BITS ,     4 ,       _FALSE ,      _FALSE     , }	,   ///*清零次数 *///	  12
	{ 0x03330201 , &GStr_EventRecordNum.ucEventTimes[1][0] ,   _FALSE , NO_BITS        ,   NO_BITS ,     4 ,       _FALSE ,      _FALSE     , }	,   ///*购电事件次数 *///     13
	{ 0x04001001 , GStr_MoneyPara. ucaAlarmMoneyL1  ,     _TRUE  , LIB_E2P_Money_Para  ,   0       ,     4 ,       _TRUE  ,      _FALSE     , }	,   ///*一级报警 *///     14
	{ 0x04001002 , GStr_MoneyPara. ucaAlarmMoneyL2  ,     _TRUE  , LIB_E2P_Money_Para  ,   4       ,     4 ,       _TRUE  ,      _FALSE     , }	,   ///*二级报警 *///     15
	{ 0x04001004 , GStr_MoneyPara. ucaMaxMoneyLimit ,     _TRUE  , LIB_E2P_Money_Para  ,   8       ,     4 ,       _TRUE  ,      _FALSE     , }	,   ///*囤积金额 *///     16
	{ 0x04001003 , GStr_MoneyPara.ucaTickMoneyLimit ,     _TRUE  , LIB_E2P_Money_Para  ,   12      ,     4 ,       _TRUE  ,      _FALSE     , }	,   ///*透支金额 *///     17
	{ 0x04001005 , GStr_MoneyPara.ucaAllowcloseMoney,     _TRUE  , LIB_E2P_Money_Para  ,   16      ,     4 ,       _TRUE  ,      _FALSE     , }	,   ///*合闸允许金额 */// 18
	{ 0x04090B01 , GStr_MoneyPara.ucaOverLoadVal    ,     _TRUE  , LIB_E2P_Money_Para  ,   20      ,     3 ,       _TRUE  ,      _FALSE     , }	,   ///*过载功率 *///     19
    { 0x04800010 , GT_ucaFactoryVerNo               ,     _FALSE , NO_BITS             ,   NO_BITS ,     8 ,       _FALSE ,      _TRUE      , }	,   ///*内部版本号 *///   20
    { 0x0400040D , GT_ucaProtocolVer                ,     _FALSE , NO_BITS             ,   NO_BITS ,     16,       _FALSE ,      _TRUE      , }	,   ///*协议版本号 */// 	21
    { 0x0400040B , GT_ucaMaterType                  ,     _FALSE , NO_BITS             ,   NO_BITS ,     10,       _FALSE ,      _TRUE      , }	,   ///*电表型号 */// 		22
    { 0x04000C01 , NO_BITS                          ,     _TRUE  , LIB_E2P_Password    ,   0       ,     4 ,       _FALSE ,      _TRUE      , }	,   ///*00密码 *///       23
    { 0x04000C02 , NO_BITS                          ,     _TRUE  , LIB_E2P_Password    ,   3       ,     4 ,      _FALSE ,      _TRUE      , }	,   ///*01密码 *///	      24
    { 0x04000C03 , NO_BITS                          ,     _TRUE  , LIB_E2P_Password    ,   6       ,     4 ,      _FALSE ,      _TRUE      , }	,   ///*02密码 *///	      25
	{ 0x04000308 , &GStr_DisplayPara.ucFullDisp_Time,     _TRUE  , LIB_E2P_Display_Para,   0       ,     1 ,      _TRUE  ,      _TRUE      , }	,   ///*上电全显时间 */// 26	
	{ 0x04000302 , &GStr_DisplayPara.ucDispDurTime  ,     _TRUE  , LIB_E2P_Display_Para,   1       ,     1 ,      _TRUE  ,      _TRUE      , }	,   ///*每屏显示时间 */// 27
	{ 0x04000301 , &GStr_DisplayPara.ucAutoDispNum  ,     _TRUE  , LIB_E2P_Display_Para,   2       ,     1 ,      _TRUE  ,      _TRUE      , }	,   ///*循环显示屏数 */// 28	
	{ 0x04000305 , &GStr_DisplayPara.ucKeyDispNum   ,     _TRUE  , LIB_E2P_Display_Para,   3       ,     1 ,      _TRUE  ,      _TRUE      , }	,   ///*按键显示屏数 */// 29	
	{ 0x04040101 , GStr_DisplayPara.ucAutoDisptable ,     _TRUE  , LIB_E2P_Display_Table,  0      ,     1 ,       _FALSE ,      _TRUE       , }	,   ///*循环显示项第一屏 *30///	  2~30屏   数据标识+1,E2偏移+1	
	{ 0x04040201 , GStr_DisplayPara.ucKeyDisptable  ,     _TRUE  , LIB_E2P_Display_Table,  30     ,     1 ,       _FALSE ,      _TRUE       , }	,   ///*按键显示项第一屏 *31///	  2~30屏   数据标识+1,E2偏移+1	
	{ 0x04000306 , GStr_MeterIFO. ucCurrentTrans, 		  _TRUE  , LIB_E2P_METER_INFO,     21     ,     3 ,       _TRUE  ,      _FALSE      , } ,    ///电流互感器变比
	{ 0x04000307 , GStr_MeterIFO. ucVoltageTrans, 		  _TRUE  , LIB_E2P_METER_INFO,     18     ,     3 ,       _TRUE  ,      _FALSE      , } ,    ///电压互感器变比
	{ 0x02010100,   &GStr_UIPDisplay.ucCOMMVoltageA[2],       _FALSE,  NO_BITS,				   NO_BITS,		2,		  _TRUE	 ,		_FALSE	    , } ,   ///* 15A相电压
	{ 0x02020100,   &GStr_UIPDisplay.ucCOMMCurrentA[1],       _FALSE,  NO_BITS,				   NO_BITS,		3,		  _TRUE	 ,		_FALSE	    , } ,   ///* 16A相电流
	{ 0x02030000,   &GStr_UIPDisplay.ucCOMMPower[1],          _FALSE,  NO_BITS,			  	   NO_BITS,		3,		  _TRUE	 ,		_FALSE	    , } ,   ///* 17总有功功率
	{ 0x02030100,   &GStr_UIPDisplay.ucCOMMPowerA[1],         _FALSE,  NO_BITS,				   NO_BITS, 	3,		  _TRUE	 ,		_FALSE	    , } ,   ///* 18A相有功功率,	
	{ 0x02060000,   &GStr_UIPDisplay.ucCOMMFactory[2],        _FALSE,  NO_BITS,				   NO_BITS,		2,		  _TRUE	 ,		_FALSE	    , } ,   ///* 19总功率因数
	{ 0x02060100,   &GStr_UIPDisplay.ucCOMMFactoryA[2],       _FALSE,  NO_BITS,				   NO_BITS,		2,		  _TRUE	 ,		_FALSE	    , } ,   ///* 20A相功率因数,	
	{ 0x02800002,   &GStr_UIPDisplay.ucFrequency[2],      _FALSE,  NO_BITS,				   NO_BITS,		2,		  _TRUE	 ,		_FALSE	    , } ,   ///* 21A电网频率,	
	#if(METER_TYPE==METER_TYPE_DTSY666)
	{0x02010200,    &GStr_UIPDisplay.ucCOMMVoltageB[2],    _FALSE,  NO_BITS,				   NO_BITS,		2,   	  _TRUE  ,      _FALSE      , } ,  ///* 22B相电压,	
	{0x02010300,    &GStr_UIPDisplay.ucCOMMVoltageC[2],    _FALSE,  NO_BITS,				   NO_BITS,		2,   	  _TRUE	 ,		_FALSE	    , } ,  ///* 23C相电压,		
	{0x02020200,    &GStr_UIPDisplay.ucCOMMCurrentB[1],       _FALSE,  NO_BITS,			  	   NO_BITS,		3,   	  _TRUE	 ,		_FALSE	    , } ,  ///* 24B相电流,	
	{0x02020300,	&GStr_UIPDisplay.ucCOMMCurrentC[1],       _FALSE,  NO_BITS,				   NO_BITS,		3,   	  _TRUE	 ,		_FALSE	    , } ,  ///* 25C相电流,			
	{0x02030200,	&GStr_UIPDisplay.ucCOMMPowerB[1]  ,       _FALSE,  NO_BITS,				   NO_BITS,		3,   	  _TRUE	 ,		_FALSE	    , } ,  ///* 26B相有功功率
	{0x02030300,	&GStr_UIPDisplay.ucCOMMPowerC[1]  ,       _FALSE,  NO_BITS,				   NO_BITS,		3,   	  _TRUE	 ,		_FALSE	    , } ,  ///* 27C相有功功率,	
	{0x02060200,	&GStr_UIPDisplay.ucCOMMFactoryB[2],       _FALSE,  NO_BITS,				   NO_BITS,		2,   	  _TRUE	 ,		_FALSE	    , } ,  ///* 28B功率因数
	{0x02060300,	&GStr_UIPDisplay.ucCOMMFactoryC[2],       _FALSE,  NO_BITS,				   NO_BITS,		2,   	  _TRUE	 ,		_FALSE	    , } ,  ///* 29C相功率因数,
	#endif
};                                                                                                                                        
#define	MAX_Comm_MAP_TAB	sizeof(Comm_MAP_TAB)/sizeof(GStr_Comm_MAP)


const 	ulong32	code C_ulaSafeCertification_Code[]={
	0x070000FF,   ///*0  485身份认证32*///
	0x070001FF,   ///*1  身份认证时效14*///
	0x070101FF,   ///*2  开户30*///
	0x070102FF,   ///*3  个人充值30*///
	0x070103FF,   ///*4  钱包初始化24*///
										//		0x070104FF,   ///*5  补助金额充值30*///
	0x070301FF,   ///*5  秘钥更新48*///
										//	0x078003FF,   ///*7  红外认证请求16*///
										//	0x070003FF,	  ///*8  红外认证命令16*///
	0x070002FF,   ///*6 身份认证失效设置 *///
	// 0x070000EE,   ///*7  485身份认证32(自扩数据标识，系统身份认证返回信息)*///
	// 0x070102EE,   ///*8  个人充值30(自扩数据标识，系统充值返回信息)*///
//	0x078001FF,	  ///*7 数据回抄 16 *///
//	0x078102ff	  ///*8 状态查询 08 *///
};
#define C_SafeCertifiificationCodeNum (sizeof(C_ulaSafeCertification_Code)/4)
const 	uchar8	code C_ulaSafeCertification_Len[C_SafeCertifiificationCodeNum]       = {
	32,
	14,
	30,
	30,
	24,
//	30,
	48,
//	16,
//	16,
	8,
	// 32,
//	16,
//	8
};
const 	uchar8	code C_ulaSafeCertification_ReturnLen[C_SafeCertifiificationCodeNum] = {
	16,
	4 ,
	4 ,
	4 ,
	4 ,
//	4 ,
	4 ,
//	34 ,
//	4,
	22,
	// 16,
//	28,
//	30
};
const 	uchar8	code C_ulaSafeCertification_ReturnType[C_SafeCertifiificationCodeNum]= 
{
0x11,
0x00,
0x00,
0x00,
0x00,
//0x00,
0x11,
//0x11,
//0x00,
0x11,
//0x11,
//0x11
};
const 	uchar8	code GT_ucVirtualEsam[26][4]= {
    0x00,0xB0,0x99,0x01,				 ///* 0  获取ESAM序列号                                        *///
	0x84,0xD4,0x01,0xFF,				 ///* 1  更新密钥,密钥存E2                                     *///
	0x84,0x30,0x02,0x0C,				 ///* 2  ESAM钱包退费                                          *///
	0x80,0xFA,0x00,0x03,				 ///* 3  密钥分散命令                  	                       *///
	0x80,0xFA,0x00,0x00,				 ///* 4  加密随机数                                            *///
	0x00,0x84,0x00,0x00,				 ///* 5  获取随机数                                            *///
	0x84,0xD6,0x96,0x00,				 ///* 6  计算密钥更新MAC  数据长度0x20，        			   *///
	0x04,0xD6,0x82,0x24,				 ///* 7  开户计算客户编号MAC 数据长度0x06，数据块长度0x0B      *///
	0x04,0xDC,0x01,0x0C,				 ///* 8  计算预置金额MAC                                       *///
	0x04,0xdc,0x03,0x0C,				 ///* 9  计算购电次数MAC                                       *///
	0x84,0x32,0x01,0x0C,				 ///* 10 计算钱包充值（钱+次数）MAC                            *///
	0x04,0xD6,0x82,0x00,				 ///* 11 计算一类参数更新MAC///*数据长度-8                     *///
	0x04,0xD6,0x83,0x00,				 ///* 12 计算当前套电价更新MAC                                 *///
	0x04,0xD6,0x84,0x00,				 ///* 13 计算备用套电价更新MAC                                 *///
	0x00,0x82,0x00,0x08,				 ///* 14 红外验证                                              *///
	0x04,0xD6,0x8C,0x00,				 ///* 15 退费                                                  *///
	0x04,0xD6,0x00,0x00,				 ///* 16 二类参数解密                                          *///
	0x04,0xD6,0x88,0x00,				 ///* 17 远程控制                                               *///
	0x04,0xD6,0x94,0x00,				 ///* 18 电量清零                                              *///
	0x04,0xD6,0x97,0x00,				 ///* 19 事件清零                                              *///
	0x00,0xC0,0x00,0x00,				 ///* 20 返回上一次操作数                                      *///
	0x00,0xB0,0x88,0x00,				 ///* 21 远程控制数据+9000                                     *///
	0x00,0xB0,0x8C,0x00,				 ///* 22 退费数据+MAC                                          *///
	0x00,0xB0,0x94,0x00,				 ///* 23 电量清零数据                                          *///
	0x00,0xB0,0x97,0x00,				 ///* 24 事件清零数据                                          *///
	0x04,0xB2,0x01,0x0c,				 ///* 25 剩余金额                                          *///
};

// const ulong32 code C_ulaMultiDataWrite_DI[7]={	///*多数据项设置(充值)，数据标识*///
// 	0x070102FF,			///*充值金额+购电次数*///
// 	0x040501FF,			///*电价参数*///
// 	0x04001001,			///*报警金额1*///
// 	0x04001002,			///*报警金额2*///
// 	0x04000306,			///*CT*///
// 	0x04000307,			///*PT*///
// 	0x04001003,			///*透支金额限值*///
// };
/*----------------< 变量定义 >----------------------------------*/
GU_BoolWordVariable	 		GU_SecurityErr;						///* 安全认证错误字//
//uchar8  xdata  GV_ClearFlag;

/*----------------< 函数声明 >----------------------------------*/
void ApiDLT645_UARTReceiveDataJudge0( uchar8 v_ucChID, uchar8 v_ucData );
void ApiDLT645_UARTReceiveDataJudge1( uchar8 v_ucChID, uchar8 v_ucData );
void ApiDLT645_FrameAnalysis( uchar8 v_ucChID);
uchar8 PrepaymentModule_Comm_INTAUTH(uchar8 *P_ucDataPtr);
uchar8 PrepaymentModule_Comm_TimeAvailableIn(uchar8 *P_DataPtr);
uchar8 PrepaymentModule_Comm_INTAUTH_Invalidation(uchar8 *P_DataPtr);
uchar8 PrepaymentModule_Comm_ModifyKey(uchar8 *P_DataPtr);
uchar8 PrepaymentModule_Comm_OpenAccout(uchar8 *P_DataPtr);
uchar8 PrepaymentModule_CommWriteESAMBinaryMAC(uchar8 *P_ucData, uchar8 V_ucLen, uchar8 V_ucHeadNum, uchar8 V_ucType);
uchar8 PrepaymentModule_Comm_HandBackMoney(uchar8 *P_DataPtr);

static uchar8 ApiDLT645_AddrTypeCheck( uchar8 v_ucChID );
static uchar8 ApiDLT645_ReadMeterAddress( uchar8 v_ucChID );
static uchar8 ApiDLT645_WriteMeterAddress( uchar8 v_ucChID );
static uchar8 ApiDLT645_ReadEmuReg( uchar8 v_ucChID );
static uchar8 ApiDLT645_WriteEmuReg( uchar8 v_ucChID );
static uchar8 ApiDLT645_FactoryCommand( uchar8 v_ucChID );
static uchar8 ApiDLT645_ReadData07( uchar8 v_ucChID );
//static uchar8 ApiDLT645_ReadData97( uchar8 v_ucChID );
//static uchar8 ApiDLT645_SetBaudRate( uchar8 v_ucChID);
static uchar8 ApiDLT645_WriteData( uchar8 v_ucChID);
static uchar8 ApiDLT645_MeterClear( uchar8 v_ucChID);
//static uchar8 ApiDLT645_ModifyPsw( uchar8 v_ucChID );
static uchar8 ApiDLT645_RelayControl(uchar8 v_ucChID);
static uchar8 ApiDLT645_SafeCertification( uchar8 v_ucChID );
static uchar8 ApiDLT645_ModifyPsw(uchar8  v_ucChID );
static uchar8 ApiDLT645_AccountTx(uchar8  v_ucChID );
static ushort16 ApiDLT645_GetStatusFlag3(void);
//static uchar8 MultiDataRead_Deal( uchar8 v_ucChID );	//多数据项组合抄读
static uchar8 MultiDataWrite_Deal( uchar8 v_ucChID );	//多数据项组合设置

/*----------------< 函数定义 >----------------------------------*/



///**********************************************************************///
///* Brief:  645接收数据帧判断                                           *///
///*                                                                    *///
///* Param:  v_ucChID：通道                                               *///
///* Param:  v_ucData：接收到的数据                                      *///
///*                                                                    *///
///* Return: 无                                                         *///
///*                                                                    *///
///* Note:   UART0中调用                                              *///
///* FE FE FE FE 68 A0 A1 A2 A3 A4 A5 68 C  L  D  CS 16 *///
///**********************************************************************///
void ApiDLT645_UARTReceiveDataJudge0( uchar8 v_ucChID, uchar8 v_ucData )
{
	
		Gstr_UartComm[v_ucChID].ucCommChStatus = API_COMM_STATUS_RECV;	///* 串口处于接收状态 *///
		Gstr_UartComm[v_ucChID].ulCommRcvByteOverTime = LibPub_GetTimerBeatInt0() ;///* 接收字节超时 *///
	
		switch ( Gstr_UartComm[v_ucChID].ucCommRevStep )
		{
			///* 是否接收到第一个68H *///
			case API_COMM_STEP0:
			{
				if ( v_ucData == 0x68 )
				{
					Gstr_UartComm[v_ucChID].ucCommRevLen = 4;
					Gstr_UartComm[v_ucChID].ucCommRevStep = API_COMM_STEP1 ;
				}
				// else
				// {
				// 	Gstr_UartComm[v_ucChID].ucCommChStatus = API_COMM_STATUS_ERROR;
				// }
				
			}break;
			
			///* 接收通信地址 *///
			case API_COMM_STEP1:
			{
				if ( Gstr_UartComm[v_ucChID].ucCommRevLen >= 10 )
				{
					Gstr_UartComm[v_ucChID].ucCommRevStep = API_COMM_STEP2 ;
				}
			}break;
			
			///* 判断第2个68H *///
			case API_COMM_STEP2:
			{
				if (  0x68 == v_ucData )
				{
					Gstr_UartComm[v_ucChID].ucCommRevStep = API_COMM_STEP3 ;
				}
				else
				{
					Gstr_UartComm[v_ucChID].ucCommChStatus = API_COMM_STATUS_ERROR;
				}
			}break;
			
			///* 接收控制字 *///
			case API_COMM_STEP3:
			{
				Gstr_UartComm[v_ucChID].ucCommRevStep = API_COMM_STEP4 ;
			}break;
			
			///* 接收数据长度 *///
			case API_COMM_STEP4:
			{
				if ( 0x00 == v_ucData )
				{
					Gstr_UartComm[v_ucChID].ucCommRevStep = API_COMM_STEP6 ;	///* 长度是0，直接接收CS *///
				}
				else
				{
					if ( API_COMM_BUF_MAX_LEN-12 < v_ucData )	///* 数据长度超出缓存大小 *///
					{
						Gstr_UartComm[v_ucChID].ucCommChStatus = API_COMM_STATUS_ERROR;
					}
					else
					{ 
						Gstr_UartComm[v_ucChID].ucCommRevStep = API_COMM_STEP5 ;
					}
				}
			}break;
			
			///* 接收数据 *///
			case API_COMM_STEP5:
			{
				if ( Gstr_UartComm[v_ucChID].ucCommRevLen == Gstr_UartComm[v_ucChID].ucaCommRXBuff[API_DLT645_LEN] + 9 + 4 ) 
				{
					Gstr_UartComm[v_ucChID].ucCommRevStep = API_COMM_STEP6 ;
				}
			}break;
			
			///* 接收CS *///
			case API_COMM_STEP6:
			{
				Gstr_UartComm[v_ucChID].ucCommRevStep = API_COMM_STEP7;
			}break;
			
			///* 接收16 *///
			case API_COMM_STEP7:
			{
				if ( 0x16 != v_ucData )
				{
					Gstr_UartComm[v_ucChID].ucCommChStatus = API_COMM_STATUS_ERROR;
				}
				else
				{
					Gstr_UartComm[v_ucChID].ucCommChStatus = API_COMM_STATUS_RECV_OK;		///* 数据接收完成 *///
					Gstr_UartComm[v_ucChID].ulCommRspOverTime = LibPub_GetTimerBeatInt0() ;		///* 启动响应超时 *///
					GStr_DisplayPara.ucDisp_tongxin_Time=LibPub_GetTimerBeatInt0() ;
					GStr_DisplayPara.ucDisp_tongxin_Flag=0x55;///接收完成闪烁显示通信符号
					
				}
			}break;
			
			default:
			{
				Gstr_UartComm[v_ucChID].ucCommChStatus = API_COMM_STATUS_ERROR;
			}break;
		}
				
		
		if ( API_COMM_STATUS_ERROR != Gstr_UartComm[v_ucChID].ucCommChStatus )
		{
			Gstr_UartComm[v_ucChID].ucaCommRXBuff[Gstr_UartComm[v_ucChID].ucCommRevLen] = v_ucData;
			Gstr_UartComm[v_ucChID].ucCommRevLen++ ; 
		}
}
///**********************************************************************///
///* Brief:  645接收数据帧判断                                           *///
///*                                                                    *///
///* Param:  v_ucChID：通道                                               *///
///* Param:  v_ucData：接收到的数据                                      *///
///*                                                                    *///
///* Return: 无                                                         *///
///*                                                                    *///
///* Note:   UART1中调用,为了消除编译器报警，                           *///
///*蓝牙数据帧结构FE FE FE FE 68H L1 L2 M5-M0 STA1 RES2 68H C D0-Dn CS 16H*///
///**********************************************************************///
void ApiDLT645_UARTReceiveDataJudge1( uchar8 v_ucChID, uchar8 v_ucData )
{
	
		Gstr_UartComm[v_ucChID].ucCommChStatus = API_COMM_STATUS_RECV;	///* 串口处于接收状态 *///
		Gstr_UartComm[v_ucChID].ulCommRcvByteOverTime = LibPub_GetTimerBeatInt1() ;///* 接收字节超时 *///
	
		switch ( Gstr_UartComm[v_ucChID].ucCommRevStep )
		{
			///* 是否接收到第一个68H *///
			case API_COMM_STEP0:
			{
				if ( v_ucData == 0x68 )
				{
					Gstr_UartComm[v_ucChID].ucCommRevLen = 4;
					Gstr_UartComm[v_ucChID].ucCommRevStep = API_COMM_STEP1 ;
				}
				
			}break;
			
			///* 接收长度低8位（长度有两个字节，由于缓存限值高8位为0） *///
			case API_COMM_STEP1:
			{
				if ( API_COMM_BUF_MAX_LEN-19 < v_ucData )	///* 数据长度超出缓存大小,长度不可能为0 *///
				{
					Gstr_UartComm[v_ucChID].ucCommChStatus = API_COMM_STATUS_ERROR;
				}
				Gstr_UartComm[v_ucChID].ucCommRevStep = API_COMM_STEP2 ;
			}break;

			///* 接收长度高8位、MAC地址、链路状态、预留、判断第2个68H *///
			case API_COMM_STEP2:
			{
				if (( Gstr_UartComm[v_ucChID].ucCommRevLen >= 15 )&&(  0x68 == v_ucData ))
				{
					Gstr_UartComm[v_ucChID].ucCommRevStep = API_COMM_STEP3 ;
				}
			}break;
			
			///* 接收蓝牙协议控制字，因为是透传只能是0x00和0xFF *///
			case API_COMM_STEP3:
			{
					Gstr_UartComm[v_ucChID].ucCommRevStep = API_COMM_STEP4 ;
			}break;
						
			///* 接收数据 *///
			case API_COMM_STEP4:
			{
				if ( Gstr_UartComm[v_ucChID].ucCommRevLen == Gstr_UartComm[v_ucChID].ucaCommRXBuff[API_DLT645_BLELENLSB] + 16 ) 
				{
					Gstr_UartComm[v_ucChID].ucCommRevStep = API_COMM_STEP5 ;
				}
			}break;
			
			///* 接收CS *///
			case API_COMM_STEP5:
			{
				Gstr_UartComm[v_ucChID].ucCommRevStep = API_COMM_STEP6;
			}break;
			
			///* 接收16 *///
			case API_COMM_STEP6:
			{
				if ( 0x16 != v_ucData )
				{
					Gstr_UartComm[v_ucChID].ucCommChStatus = API_COMM_STATUS_ERROR;
				}
				else
				{
					Gstr_UartComm[v_ucChID].ucCommChStatus = API_COMM_STATUS_RECV_OK;		///* 数据接收完成 *///
					Gstr_UartComm[v_ucChID].ulCommRspOverTime = LibPub_GetTimerBeatInt1() ;		///* 启动响应超时 *///
					GStr_DisplayPara.ucDisp_tongxin_Time=LibPub_GetTimerBeatInt1() ;
					GStr_DisplayPara.ucDisp_tongxin_Flag=0x55;///接收完成闪烁显示通信符号
					///判断是否为模块主动上报连接信息；控制码为0x82，目标设备地址为全F
					if( (Gstr_UartComm[v_ucChID].ucaCommRXBuff[16] == 0x82)&&!(LibPub_0xFFCheckInt(&Gstr_UartComm[v_ucChID].ucaCommRXBuff[API_DLT645_MACADDRLSB], 6)) )
					{
						if( Gstr_UartComm[v_ucChID].ucaCommRXBuff[API_DLT645_BLELENLSB] == 0x0A)
						{
							GStr_Flag.ucBLESTATFlag = BLE_STAT_CONNECTED;	///*已连接状态*///
						}
						else if(( Gstr_UartComm[v_ucChID].ucaCommRXBuff[API_DLT645_BLELENLSB] == 0x05)||( Gstr_UartComm[v_ucChID].ucaCommRXBuff[API_DLT645_BLELENLSB] == 0x04))
						{
							GStr_Flag.ucBLESTATFlag = BLE_STAT_IDLE;		///*空闲状态*///
						}
						else
						{
							GStr_Flag.ucBLESTATFlag = BLE_STAT_IDLE;		///*空闲状态*///
						}
					}
				}
			}break;
			
			default:
			{
				Gstr_UartComm[v_ucChID].ucCommChStatus = API_COMM_STATUS_ERROR;
			}break;
		}
				
		
		if ( API_COMM_STATUS_ERROR != Gstr_UartComm[v_ucChID].ucCommChStatus )
		{
			Gstr_UartComm[v_ucChID].ucaCommRXBuff[Gstr_UartComm[v_ucChID].ucCommRevLen] = v_ucData;
			Gstr_UartComm[v_ucChID].ucCommRevLen++ ; 
		}
}

///**********************************************************************///
///* Brief:  645帧解析                                                  *///
///*                                                                    *///
///* Param:  v_ucChID：通道                                             */// 
///*                                                                    *///
///* Return: 无                                                         *///
///*                                                                    *///
///* Note:   修改及其他说明                                              *///
///**********************************************************************///
void ApiDLT645_FrameAnalysis( uchar8 v_ucChID)
{
	uchar8	V_ucTemp;		/*1字节临时变量，即用即消*/
	uchar8	V_ucCnt_i;		/*用于计算存放CS*/
	uchar8	BLE_head_Frame[20]="";

	/*接收缓存拷贝到发送缓存中*/
	if ( CH_UART_UART0 == v_ucChID)	// 目前是485
	{
		LibPub_MemCopyBytes( &Gstr_UartComm[v_ucChID].ucaCommRXBuff[0], &Gstr_UartComm[v_ucChID].ucaCommTXBuff[0], Gstr_UartComm[v_ucChID].ucaCommRXBuff[API_DLT645_LEN]+16 );
	}
	
	if ( CH_UART_UART1 == v_ucChID)	// 目前是蓝牙
	{
		LibPub_MemCopyBytes( &Gstr_UartComm[v_ucChID].ucaCommRXBuff[17], &Gstr_UartComm[v_ucChID].ucaCommTXBuff[0], Gstr_UartComm[v_ucChID].ucaCommRXBuff[5] );	/*ucaCommTXBuff[5]为645数据帧的长度	*/				
	}
	
	///* 先判断一下通信地址 *///	
	Gstr_UartComm[v_ucChID].ucCommAddrType = ApiDLT645_AddrTypeCheck(v_ucChID);
	if ( F_COMMADDRTYPE_NULL == Gstr_UartComm[v_ucChID].ucCommAddrType )
	{
		Gstr_UartComm[v_ucChID].ucCommChStatus = API_COMM_STATUS_ERROR;
		return;
	}	
	
	///* 算一下CS和-33处理 *///
	V_ucTemp = LibPub_CalSum( &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1ST68H], Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] + 10) ;
	for( V_ucCnt_i = 0; V_ucCnt_i < Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN]; V_ucCnt_i++ )
	{
		Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+V_ucCnt_i] -= 0x33;
	}	 
	if ( V_ucTemp != Gstr_UartComm[v_ucChID].ucaCommTXBuff[V_ucCnt_i+API_DLT645_1STDATA])///* 判断一下CS *///
	{
		Gstr_UartComm[v_ucChID].ucCommChStatus = API_COMM_STATUS_ERROR;
		return;
	}
	
	///* 以下数据正常，可以正常解析了 *///
	///*先保存下操作者代码和数据标识用于编程记录
	if(Gstr_UartComm[v_ucChID].ucaCommTXBuff[ API_DLT645_CMD ]!=API_DLT645_CMD_Safe_Certification)
	{
		LibPub_MemCopyBytes(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[ API_DLT645_C0 ], &GA_ucOperCode[0], 4);
		LibPub_MemCopyBytes(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[ API_DLT645_DI0 ], &GA_ucDICode[0], 4);
	}
	else////03命令没有密码，所以操作这代码为18位开始
	{
		LibPub_MemCopyBytes(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[ API_DLT645_PA0 ], &GA_ucOperCode[0], 4);
		LibPub_MemCopyBytes(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[ API_DLT645_DI0 ], &GA_ucDICode[0], 4);
	}
	
	switch ( Gstr_UartComm[v_ucChID].ucaCommTXBuff[ API_DLT645_CMD ] )
	{
		case    API_DLT645_CMD_Safe_Certification:      ///*身份认证   *////
		{
				V_ucTemp = ApiDLT645_SafeCertification( v_ucChID );
		}break;
			
		case	API_DLT645_CMD_RD_METER_ADDR:			///* 全A读通信地址 *///
		{
				V_ucTemp = ApiDLT645_ReadMeterAddress( v_ucChID );
		}break;
		
		
		case	API_DLT645_CMD_WR_METER_ADDR:			///* 全A写通信地址 *///
		{
				V_ucTemp = ApiDLT645_WriteMeterAddress( v_ucChID );
		}break;
		
		case	API_DLT645_CMD_RD_EMU_REG:				///* 读emu寄存器地址 *///
		{
				V_ucTemp =  ApiDLT645_ReadEmuReg( v_ucChID );
		}break;
		
		case	API_DLT645_CMD_WR_EMU_REG:				///* 写emu寄存器地址 *///
		{
				V_ucTemp =  ApiDLT645_WriteEmuReg( v_ucChID );
		}break;
		
		case  API_DLT645_CMD_RELAY_CTRL:               ///* 费控命令
		{
			LibPub_MemCopyBytes(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_R],GA_ucRelayOperCode,4);
			V_ucTemp =  ApiDLT645_RelayControl( v_ucChID );
		}break;
		
		case	API_DLT645_CMD_FACTORY_1E:				///* 厂内自扩命令 *///
		case	API_DLT645_CMD_FACTORY_1F:	
		{
				V_ucTemp =  ApiDLT645_FactoryCommand( v_ucChID );
		}break;
			
		case	API_DLT645_CMD_RD_DATA07:				///* 07读数据 *///
		{
				V_ucTemp =  ApiDLT645_ReadData07( v_ucChID );
		}break;
		
		case	API_DLT645_CMD_WR_DATA07:				///* 07写数据 *///
		{
				V_ucTemp =  ApiDLT645_WriteData( v_ucChID );
		}break;
		
		case	API_DLT645_CMD_METER_CLR:				///* 07电表清零 *///
		{
				V_ucTemp =  ApiDLT645_MeterClear( v_ucChID );
		}break;
		
		case	API_DLT645_CMD_WR_SET_PSW:				///* 修改密码 *///
		{
				V_ucTemp =  ApiDLT645_ModifyPsw( v_ucChID );			
		}break;
		
		case	API_DLT645_CMD_Account_Transaction:		///* 系统自扩命令 *///
		{
				V_ucTemp =  ApiDLT645_AccountTx( v_ucChID );
		}break;
		
		default:break;
	}
	
	///* 根据处理结果组织需要返回的数据 */// 
	switch( V_ucTemp )
	{
		case API_DLT645_COMM_ERR_OK:	///* 正常应答 *///
		{
			if((Gstr_UartComm[v_ucChID].ucaCommTXBuff[ API_DLT645_CMD ] ==API_DLT645_CMD_WR_DATA07)||(Gstr_UartComm[v_ucChID].ucaCommTXBuff[ API_DLT645_CMD ] ==API_DLT645_CMD_Safe_Certification))
			{
				if(!(GStr_Flag.ucRunState2 &F_RUN_PROG_10MIN_FLAG))
				{
					GStr_Monitor.ulProgEventDelayTime=LibPub_GetTimerBeat();///10min定时
					GStr_Flag.ucRunState2|=F_RUN_PROG_10MIN_FLAG;///置10min定时标志
					GStr_Flag.ucRunState2|=F_RUN_FirstProgFlag;///置首次编程标志
					ApiEvent_WriteRecord(C_Program);///做首次编程记录
				}
				else
				{
					GStr_Monitor.ulProgEventDelayTime=LibPub_GetTimerBeat();///10min定时
					GStr_Flag.ucRunState2|=F_RUN_PROG_10MIN_FLAG;///置10min定时标志
					ApiEvent_WriteRecord(C_Program);///做编程记录	
				}
			}
			
			 Gstr_UartComm[v_ucChID].ucaCommTXBuff[ API_DLT645_CMD ] |= 0x80;
		}break;
		
		case API_DLT645_COMM_RD_OK:
		{
			Gstr_UartComm[v_ucChID].ucaCommTXBuff[ API_DLT645_CMD ] |= 0x80;
		}break;
		case API_DLT645_COMM_WR_OK:	///*修改密码正确*///
		{
			Gstr_UartComm[v_ucChID].ucaCommTXBuff[12] |= 0x80;								//控制码
			Gstr_UartComm[v_ucChID].ucaCommTXBuff[13]  = 0x04;								//数据长度
		}break;
		///* 有错误 *///
		case API_DLT645_COMM_ERR_OTHER:
		case API_DLT645_COMM_ERR_NODATA:
		case API_DLT645_COMM_ERR_NOAUTH:
		case API_DLT645_COMM_ERR_BPSERR:
		{
			Gstr_UartComm[v_ucChID].ucaCommTXBuff[ API_DLT645_CMD ] |= 0xC0;
			Gstr_UartComm[v_ucChID].ucaCommTXBuff[ API_DLT645_LEN ]  = 0x01;
			Gstr_UartComm[v_ucChID].ucaCommTXBuff[ API_DLT645_1STDATA ]  = V_ucTemp;
			
		}break;
		
		///* 不应答 *///
		case API_DLT645_COMM_ERR_NOACK:
		{
			Gstr_UartComm[v_ucChID].ucCommChStatus = API_COMM_STATUS_ERROR; 
		}break;
		///身份认证失败
		case API_DLT645_SAFE_CERT_ERR:
		{
			Gstr_UartComm[v_ucChID].ucaCommTXBuff[ API_DLT645_CMD ] |= 0xC0;
			Gstr_UartComm[v_ucChID].ucaCommTXBuff[ API_DLT645_LEN ]  = 0x02;
			// Gstr_UartComm[v_ucChID].ucaCommTXBuff[ API_DLT645_1STDATA ]  = GU_SecurityErr.BYTE[0];
			// Gstr_UartComm[v_ucChID].ucaCommTXBuff[ API_DLT645_1STDATA+1 ]  = GU_SecurityErr.BYTE[1];
		}break;
		
		
		default:
		{
			Gstr_UartComm[v_ucChID].ucCommChStatus = API_COMM_STATUS_ERROR;
		}break;
	}
	
	if ( Gstr_UartComm[v_ucChID].ucCommChStatus != API_COMM_STATUS_ERROR )
	{
		///* 组织要返回的数据 *///
		Gstr_UartComm[v_ucChID].ucCommSndCnt = 0;
		
		LibPub_MemSetBytes( &Gstr_UartComm[v_ucChID].ucaCommTXBuff[ API_DLT645_1STFE ], 0xFE, 4 );	///* 组织4个FE *///
		LibPub_MemExchangeBytes( &GStr_MeterIFO.ucaCommAddr[0], &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_ADDRLSB], 6);	///* 通信地址 *///
		
		for( V_ucCnt_i = 0; V_ucCnt_i < Gstr_UartComm[v_ucChID].ucaCommTXBuff[ API_DLT645_LEN ]; V_ucCnt_i++ )
		{
			Gstr_UartComm[v_ucChID].ucaCommTXBuff[ API_DLT645_1STDATA + V_ucCnt_i ] += 0x33;
		}
		V_ucTemp = LibPub_CalSum( &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1ST68H], Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] + 10) ;
		Gstr_UartComm[v_ucChID].ucaCommTXBuff[ Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] + API_DLT645_1STDATA] = V_ucTemp;
		Gstr_UartComm[v_ucChID].ucaCommTXBuff[ Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] + API_DLT645_1STDATA + 1] = 0x16;
		
		Gstr_UartComm[v_ucChID].ucCommSndLen = Gstr_UartComm[v_ucChID].ucaCommTXBuff[ API_DLT645_LEN ] + 16;	///* 485要发送的数据长度 *///
		/*以下是组织蓝牙结构的数据帧长度、控制码、CS、16*/
		if ( CH_UART_UART1 == v_ucChID)	// 目前是蓝牙
		{
			for( V_ucCnt_i = Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN]+API_DLT645_BLE1STDATA; V_ucCnt_i > 0; V_ucCnt_i-- )	/*将645数据帧往后移，空出蓝牙数据的帧头,API_DLT645_BLE1STDATA位数据*/
			{
				Gstr_UartComm[v_ucChID].ucaCommTXBuff[ V_ucCnt_i + API_DLT645_BLE1STDATA - 1 ] = Gstr_UartComm[v_ucChID].ucaCommTXBuff[ V_ucCnt_i-1 ];
			}

			/*蓝牙数据帧前缀*/
			LibPub_MemCopyBytes( &C_cBleComm_Head[ API_DLT645_BLE1STFE ], &Gstr_UartComm[v_ucChID].ucaCommTXBuff[ API_DLT645_BLE1STFE ], 7 );	
			Gstr_UartComm[v_ucChID].ucaCommTXBuff[ 5 ] = Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] + API_DLT645_BLE1STDATA - 1;	/*蓝牙帧结构的数据长度低位*/
			LibPub_MemCopyBytes( &Gstr_UartComm[v_ucChID].ucaCommRXBuff[ 7 ], &Gstr_UartComm[v_ucChID].ucaCommTXBuff[ 7 ], 6 );	/*目标蓝牙Mac地址*/
			LibPub_MemCopyBytes( &C_cBleComm_Head[ API_DLT645_BLELinkSTA ], &Gstr_UartComm[v_ucChID].ucaCommTXBuff[ API_DLT645_BLELinkSTA ], 4 );	

			V_ucTemp = LibPub_CalSum( &Gstr_UartComm[v_ucChID].ucaCommTXBuff[ 4 ], Gstr_UartComm[v_ucChID].ucaCommTXBuff[ 5 ] + 13) ;
			Gstr_UartComm[v_ucChID].ucaCommTXBuff[ Gstr_UartComm[v_ucChID].ucaCommTXBuff[ 5 ] + API_DLT645_BLE1STDATA ] = V_ucTemp;
			Gstr_UartComm[v_ucChID].ucaCommTXBuff[ Gstr_UartComm[v_ucChID].ucaCommTXBuff[ 5 ] + API_DLT645_BLE1STDATA +1 ] = 0x16;

			Gstr_UartComm[v_ucChID].ucCommSndLen = Gstr_UartComm[v_ucChID].ucaCommTXBuff[ 5 ] + 19;	///* 蓝牙要发送的数据长度 *///
			GStr_Monitor.ucBleRestCnt = 0;	//蓝牙定时校验计数清零，有蓝牙通信就清零
		}
		
		///* 数据准备好了就可以发送了 *///
		Gstr_UartComm[v_ucChID].ucCommChStatus = API_COMM_STATUS_FRAME_OK;
	} 
	
}
///**********************************************************************///
///* Brief:  读通信地址                                                  *///
///*                                                                    *///
///* Param:  v_ucChID：通道                                             */// 
///*                                                                    *///
///* Return: 返回处理结果                    					        *///
///*                                                                    *///
///* Note:   修改及其他说明                                              *///
///**********************************************************************///
static uchar8 ApiDLT645_ReadMeterAddress( uchar8 v_ucChID )
{
	uchar8	V_ucErrorType = API_DLT645_COMM_ERR_NOACK; 	

	if ( Gstr_UartComm[v_ucChID].ucCommAddrType == F_COMMADDRTYPE_AA )
	{

		LibPub_MemExchangeBytes( &GStr_MeterIFO.ucaCommAddr[0], &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA], 6);
		Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = 6;
		V_ucErrorType = API_DLT645_COMM_ERR_OK;
	}
	
	return ( V_ucErrorType ) ;
}
///**********************************************************************///
///* Brief:  写通信地址                                                  *///
///*                                                                    *///
///* Param:  v_ucChID：通道                                             */// 
///*                                                                    *///
///* Return: 返回处理结果                    					        *///
///*                                                                    *///
///* Note:   修改及其他说明                                              *///
///**********************************************************************///
static uchar8 ApiDLT645_WriteMeterAddress( uchar8 v_ucChID )
{
	uchar8	V_ucErrorType = API_DLT645_COMM_ERR_NOACK; 	
// 	uchar8  V_ucTempBuff[30];
	if ( Gstr_UartComm[v_ucChID].ucCommAddrType == F_COMMADDRTYPE_AA )
	{
		if(_FAILED==LibPub_IsBCD(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA],6))
		{
			V_ucErrorType=API_DLT645_COMM_ERR_OTHER;
		}
		else
		{
			if( _SUCCESS == LibPub_ReadDataFromE2prom(LIB_E2P_METER_INFO, 0, &GStr_MeterIFO.ucaCommAddr[0]))
			{

 				//先读取通信地址所在EE的整条数据，用于后续算CRC
				LibPub_MemExchangeBytes(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA],&GStr_MeterIFO.ucaCommAddr[0],6);
				//更新RAM
				if( _SUCCESS == LibPub_WriteDataToE2prom(LIB_E2P_METER_INFO, 0, &GStr_MeterIFO.ucaCommAddr[0]) ) 
				{
					V_ucErrorType = API_DLT645_COMM_ERR_OK;
					GStr_Flag.ucBLESTATFlag = BLE_STAT_MAC_MOD;		//需要设置蓝牙模块mac标志
					/*写完通信地址后需要重新设置蓝牙模块参数，并重新广播*/
					//BleDrv_BleReset();
					//BleDrv_InitBleRunPara();
					//BleDrv_SetBleStat();	 
				}
				else
				{
					V_ucErrorType=API_DLT645_COMM_ERR_OTHER;
				}
			}
			else
			{
				V_ucErrorType=API_DLT645_COMM_ERR_OTHER;
			}
		}		
	}
	
	return ( V_ucErrorType ) ;
}


///**********************************************************************///
///* Brief:  通信地址类型解析                                             *///
///*                                                                    *///
///* Param:  v_ucChID：通道                                             */// 
///*                                                                    *///
///* Return: 通信地址类型（全9、全A、缩位、匹配)                          *///
///*                                                                    *///
///* Note:   修改及其他说明                                              *///
///**********************************************************************///
uchar8 ApiDLT645_AddrTypeCheck( uchar8 v_ucChID )
{
	uchar8 i,j,V_ucAddrType = F_COMMADDRTYPE_NULL;
	
	for ( i = 0; i < 6; i++ )
	{
		if ( 0x99 != Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_ADDRLSB+i] )
		{
			break;
		}
	}
	
	if ( 6 == i )
	{
		V_ucAddrType = F_COMMADDRTYPE_99;	///* 全9广播地址 *///
	}
	else
	{
		for ( i = 0; i < 6; i++ )
		{
			if ( 0xAA != Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_ADDRMSB-i] )
			{
				for ( j = i; j < 6; j++ )
				{
					if ( Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_ADDRMSB - j] != GStr_MeterIFO.ucaCommAddr[j] )
					{
						break;
					}
				}
				if ( 6 == j )	///* 说明是全等地址或者是缩位 *///
				{
					if ( 0 == i )
					{
						V_ucAddrType = F_COMMADDRTYPE_ID;
					}
					else
					{
						V_ucAddrType = F_COMMADDRTYPE_SW;
					}
				}
				break;
			}
		}
		
		if ( 6 == i )
		{
			V_ucAddrType = F_COMMADDRTYPE_AA;
		}
	}
	
	return ( V_ucAddrType ); 
}
///**********************************************************************///
///* Brief:  通信写emu寄存器地址（校表）                                 *///
///*                                                                    *///
///* Param:  v_ucChID：通道                                             */// 
///*                                                                    *///
///* Return: 返回处理结果                                                *///
///*                                                                    *///
///* Note:   修改及其他说明                                              *///
///**********************************************************************///
///* fe fe fe fe 68	A0 … A5 68 2F 0C DI0-DI3 PA P0-P2 C0-C3 N1-Nn CS	16  *///
///* 0  1     3  4  5     10          14      18       22                   *///
static uchar8 ApiDLT645_WriteEmuReg( uchar8 v_ucChID )
{
	uchar8	V_ucErrorType = API_DLT645_COMM_ERR_NOAUTH;
	
	do{
		// Brief: 数据长度错了，回复未授权错误
// 		if ( Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] != 0x10 )	// 数据长度16字节
// 		{
// 			break;
// 		}
// 		
// 		// Brief: DI3错误，回复未授权错误
// 		if ( Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+3] != 0x80 )
// 		{
// 			break;
// 		}
		
// 		// Brief: 不在厂内，回复未授权错误
 		if ( (GStr_Flag.ucMeterMode&F_FACTORY_MODE) != F_FACTORY_MODE )  
 		{
 			break;
 		}
		
// 		// Brief: 密码不是00级，回复未授权错误
// 		if ( 0x00 != Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_PA0] )
// 		{
// 			break;
// 		}
		// Brief: 密码不对，回复未授权错误
// 		if ( _TRUE != LibPub_CheckPassword( &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_PA0]) )	
// 		{
// 			break;			
// 		}
		
		// Brief: 以上都对，则开始操作
		if( _SUCCESS == ApiMS_CalibrationMeterComm(v_ucChID) )
		{
			V_ucErrorType = API_DLT645_COMM_ERR_OK;
			Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = 0;
		} 
		
	}while(0); 

	
	return  V_ucErrorType;
}
///*--------------------------------- 注释详解区 ---------------------------------------------------------*///

///* 注释1: [33 33 33 B3] 括号内从左到右一次为寄存器低地址、寄存器高地址、数据长度(固定00)、功能码（80:读校表寄存器EC,81：读计量参数寄存器EP）*///

///* 注释2: 该命令不判断通信地址类型，为厂内调试命令，不做要求 *///

///*------------------------------------------------------------------------------------------------------*///
///**********************************************************************///
///* Brief:  通信读emu寄存器地址                                         *///
///*                                                                    *///
///* Param:  v_ucChID：通道                                             */// 
///*                                                                    *///
///* Return: 返回处理结果                                                *///
///*                                                                    *///
///* Note:   修改及其他说明                                              *///
///**********************************************************************///
///* FE FE FE FE 68 00 00 00 00 00 00 68 2E 04 [33 33 39 B3] cs 16   8006xxxx*///
///* FE FE FE FE 68 00 00 00 00 00 00 68 2E 04 [33 36 34 B3] cs 16   80010300 功率原始值*///

static uchar8 ApiDLT645_ReadEmuReg( uchar8 v_ucChID )
{
	uchar8	V_ucErrorType = API_DLT645_COMM_ERR_NODATA; 

	do{
		
		// Brief: 数据长度错了就回复其他错误
		if ( Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] != 4 )
		{
			V_ucErrorType = API_DLT645_COMM_ERR_OTHER ; 
			break;
		}
		
		// Brief:  DI3必须为80H
		if ( Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+3] != 0x80 )
		{
			V_ucErrorType = API_DLT645_COMM_ERR_OTHER ; 
			break;
		}
		
		// Brief: 判断一下DI2是否为读计量芯片寄存器
		if( ( 0x03 != Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+2] ) &&
			( 0x04 != Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+2] )&&
			( 0x01 != Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+2] )
		  )
		{ 
			V_ucErrorType = API_DLT645_COMM_ERR_OTHER ; 
			break;
		}
		
		if( _SUCCESS == ApiMS_CalibrationMeterComm( v_ucChID ) )
		{
			V_ucErrorType = API_DLT645_COMM_ERR_OK; 
			if( (0x01 != Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+2])||
				((0x01 == Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+2])&&(0xFF != Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0]))
			  )
			{
				Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = 8;
			}		
			else if( (0x03==Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+1])||
				(0x05==Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+1])||
				(0x07==Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+1])
				)
			{
				
				Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = 20;  ///数据标识+ABC合相数据
				
			}
			else
			{
				Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = 16;  ///校表参数没有合相数据
			}
		} 
	}while(0);
	
	return V_ucErrorType;
}
///**********************************************************************///
///* Brief:  07规约读数据                                                *///
///*                                                                    *///
///* Param:  v_ucChID：通道                                             */// 
///*                                                                    *///
///* Return: 返回处理结果                     					        *///
///*                                                                    *///
///* Note:   修改及其他说明                                              *///
///**********************************************************************///
static uchar8 ApiDLT645_ReadData07( uchar8 v_ucChID )
{
	uchar8		*P_ucTemp,V_ucErrorType;
	uchar8      V_ucTable[5];
	ulong32		V_ulDI3DI2DI1DI0;
	uchar8    V_Temp,i,V_Temp1,V_LcdNum;
	uchar8    V_ucPassword[11];
	uchar8    V_ucTempData[60];
	ushort16  V_usStateFlag3;
	
	V_ulDI3DI2DI1DI0  = (ulong32) Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0];
	V_ulDI3DI2DI1DI0 |= (ulong32) Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+1]<<8;
	V_ulDI3DI2DI1DI0 |= (ulong32) Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+2]<<16;
	V_ulDI3DI2DI1DI0 |= (ulong32) Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+3]<<24;

	if( 0x04040300 == V_ulDI3DI2DI1DI0 )	///* 液晶查看 *///
	{
		if(	0x09 == Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] )
		{
			V_ulDI3DI2DI1DI0  = (ulong32) Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_R];
			V_ulDI3DI2DI1DI0 |= (ulong32) Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_R+1]<<8;
			V_ulDI3DI2DI1DI0 |= (ulong32) Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_R+2]<<16;
			V_ulDI3DI2DI1DI0 |= (ulong32) Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_R+3]<<24;
			
			// 查看表号、通信地址和客户编号时，要判断一下屏数是否超出允许值【0，1】
			//-----------------------------------------------------------------------------------------------
			if((0x04000401==V_ulDI3DI2DI1DI0)||(0x04000402==V_ulDI3DI2DI1DI0)||(0x0400040E==V_ulDI3DI2DI1DI0))
			{
				if(1<Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_R+4])
				{
				 return(API_DLT645_COMM_ERR_NODATA);
				}
			}
			else if( 0xFFFFFFFF==V_ulDI3DI2DI1DI0)///*全显屏数要为0xFF
			{
				if(0xFF!=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_R+4])
				{
					 return(API_DLT645_COMM_ERR_NODATA);
				}
			}
			else
			{
				if(0x00!=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_R+4])
				{
					 return(API_DLT645_COMM_ERR_NODATA);
				}
			}
			V_Temp=ApiGet_Lcd_Num(V_ulDI3DI2DI1DI0,Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_R+4]);
			if(0x00!=V_Temp)
			{
				V_Temp-=1;
				GStr_DisplayPara.ucDispNum=V_Temp;  ///获取的屏数从第1屏开始的，实际是从第0屏开始，需减1
			    GStr_Flag.ucDisp &= F_DISP_COM_DIASP;//清其他显示标志
				GStr_Flag.ucDisp |= F_DISP_COM_DIASP;
			}	
			else
			{
			    return(API_DLT645_COMM_ERR_NODATA);
			}
			GStr_DisplayPara.ulDisptimer = LCD_DISP_COMM_TIME/LCD_UPTATA_TIME;    //液晶查看时间赋值//500ms减1
			GStr_DisplayPara.ucBackLightTime=LCD_DISP_COMM_TIME/LCD_UPTATA_TIME/2;//背光1S减1，所以时间要为显示的一半
			Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN]=9;
			return(API_DLT645_COMM_RD_OK);
		}
		else
		{
			return(API_DLT645_COMM_ERR_OTHER);
		}
	}
	
	if ( Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] != 0x04 )	///* 数据长度不对 *///
	{
			return(API_DLT645_COMM_ERR_OTHER);
	}
	if(0x04000409==V_ulDI3DI2DI1DI0)////电表有功常数
	{
		
		Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_R+1]=LibPub_1Hex_2_1BCD(GStr_FunConfigPara.ucFunMeterConst);
		Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_R]=0;
		Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_R+2]=0;
		Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = 7;
		return (API_DLT645_COMM_ERR_OK);
		
	}
	if(0x040501FF==V_ulDI3DI2DI1DI0)///费率电价4*4
	{
		  for(i=0;i<4;i++)
		  {
					LibPub_MemExchangeBytes(GStr_PRICE.ucaPrice,&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_R+4*i],4);
			}///四个费率电价全返回当前电价
			Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = 20;
			return (API_DLT645_COMM_ERR_OK);
	}
	if(0x04000503==V_ulDI3DI2DI1DI0)  ///读状态字3
	{
			V_usStateFlag3=ApiDLT645_GetStatusFlag3();
		  Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_R]=(uchar8)V_usStateFlag3;
		  Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_R+1]=(uchar8)(V_usStateFlag3>>8);
		  Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN]=6;
		  return(API_DLT645_COMM_ERR_OK);
	}
	
	if(0x080100FF== V_ulDI3DI2DI1DI0)	/*自扩数据标识 080100FF  读取上一次购电信息、表内剩余金额、客户编号、表号、当前总电量、随机数2、状态字3、表内透支金额、合闸允许金额、囤积金额限值*/
	{															/*0~17					18~21		22~27	28~33   34~37      38~41     42        44~47         48~51        52~55*/
		/*上一次购电记录*/
		V_Temp = GStr_EventValidPiont.uc_Point[C_BuyMoney];		/*上一次购电记录的指针*/
		V_Temp1 = CAddr_SelfMoney_Lenth;		/*上一次购电记录的长度*/
		Hal_ReadEEPROM( V_ucTempData,CAddr_SelfMoney_Note+V_Temp*V_Temp1,V_Temp1 );		/*读取购电记录*/
		LibPub_Inverse( &V_ucTempData[0], 2 );		/*上一次购电后购电总次数*/
		LibPub_Inverse( &V_ucTempData[2], 4 );		/*上一次购电金额*/
		LibPub_Inverse( &V_ucTempData[6], 4 );		/*上一次购电前剩余金额*/
		LibPub_Inverse( &V_ucTempData[10], 4 );		/*上一次购电后剩余金额*/
		LibPub_Inverse( &V_ucTempData[14], 4 );		/*上一次购电后总购电金额*/
		  
		/*表内剩余金额*/
		LibPub_MemExchangeBytes( &GStr_Money.ucaRemainMoney[0], &V_ucTempData[18], 0x04 );	
		
		/*表内透支金额*/
		LibPub_MemExchangeBytes( GStr_Money.ucaTickMoney, &V_ucTempData[22], 0x04 );	
			
		/*合闸允许金额*/
		LibPub_MemExchangeBytes( GStr_MoneyPara.ucaAllowcloseMoney, &V_ucTempData[26], 0x04 );	
			
		/*囤积金额限值*/
		LibPub_MemExchangeBytes( GStr_MoneyPara.ucaMaxMoneyLimit, &V_ucTempData[30], 0x04 );	
			
		/*当前总电量*/
		LibPub_MemExchangeBytes( &GStr_Energy.ucaFw_Energy[0], &V_ucTempData[34], 0x04 );
			
		/*客户编号*/
		LibPub_MemExchangeBytes( &GStr_MeterIFO.ucaUserID[0], &V_ucTempData[38], 0x06 );	
		
		/*表号*/
		LibPub_MemExchangeBytes( &GStr_MeterIFO.ucaMeterID[0], &V_ucTempData[44], 0x06 );
		
		/*随机数2*/
		if( 0==(GStr_Flag.ucRunState2 & F_RUN_INTAUTHAvailabilityFlag) )		/*身份认证失效重新获取随机数*/
		{
			PrepaymentModule_GetChallenge(&GStr_VirtualEsamPara.ucRs485RandNum2[0], 0x04) ;		/*获取随机数2*/
			LibPub_MemSetBytes(&GStr_VirtualEsamPara.ucRs485RandNum2[4], 0x00, 4);
		}		/*身份认证有效直接把当前的随机数2返回*/			
		LibPub_MemExchangeBytes(&GStr_VirtualEsamPara.ucRs485RandNum2[0], &V_ucTempData[50], 0x04 );		/*数据倒向以便数据返回*/		
		  
		/*状态字3*/
		V_usStateFlag3 = ApiDLT645_GetStatusFlag3();
		V_ucTempData[54] = (uchar8)V_usStateFlag3;
		V_ucTempData[55] = (uchar8)(V_usStateFlag3>>8);
		// if(GStr_Flag.ucRunState2&F_RUN_OpenAccoutFlag)///开户状态
		// {
		// 		V_ucTempData[42]=0x00;
		// }
		// else
		// {
		// 		V_ucTempData[42]=0x01;
		// }GStr_Money. ucaTickMoney
		GStr_Flag.ucRunState3|=F_RUN_READ_RANDOM2;		/*置读取随机数标志*/
		GStr_Monitor.ulReadRandom2DelayTime=LibPub_GetTimerBeat();		/*读随机数2后取系统时间*/
		/*置五分钟*/ 
		LibPub_MemCopyBytes( V_ucTempData, &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_R], 56);	
		Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN]=60;
		return (API_DLT645_COMM_ERR_OK);			
	}
	
	if((0x03==Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+3])
	||(0x1D==Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+3])
	||(0x1E==Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+3]))///事件记录
	{
		V_ucErrorType = ReadEventRecordData(V_ulDI3DI2DI1DI0,&(Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_R]), &(Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN]));
        Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN]+=4;///长度加4字节数据标识
		return 	V_ucErrorType;
	}
	
	if(0x04000C00==(V_ulDI3DI2DI1DI0&0xFFFFFFF0)) ///密码直接从EE读
    {
		if((GStr_Flag.ucMeterMode&F_FACTORY_MODE)!=F_FACTORY_MODE)///*厂外密码不可读
		{return (API_DLT645_COMM_ERR_NOACK);}
		else
		{
			LibPub_ReadDataFromE2prom(LIB_E2P_Password, 0, V_ucPassword);
			LibPub_MemCopyBytes(&V_ucPassword[(Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0]-1)*3],&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_R+1],3);
			Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_R]=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0]-1;
			Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN]=8;
			return (API_DLT645_COMM_ERR_OK);	
		}
		
	}
	
	if((0x04040100==(V_ulDI3DI2DI1DI0&0xFFFFFF00))||(0x04040200==(V_ulDI3DI2DI1DI0&0xFFFFFF00)))///*循显项和键显项
	{
			V_Temp=V_ulDI3DI2DI1DI0&0x000000FF;
			if(30<V_Temp)///最大为30屏
			{
				return (API_DLT645_COMM_ERR_NODATA) ;
			}
			if(	0x04040100==(V_ulDI3DI2DI1DI0&0xFFFFFF00))//循显
			{
					for(i=0;i<MAX_Comm_MAP_TAB;i++)
					{
							if(0x04040101==Comm_MAP_TAB[i].ucaDataId)
							{
									V_Temp1=i;
									break;
							}
					}
			}
			else                   //键显
			{
					for(i=0;i<MAX_Comm_MAP_TAB;i++)
					{
							if(0x04040201==Comm_MAP_TAB[i].ucaDataId)
							{
								V_Temp1=i;
								break;
							}
					}
			}
			V_LcdNum = Comm_MAP_TAB[V_Temp1].ucaRamAdd[V_Temp-1];
			V_ulDI3DI2DI1DI0=ApiGet_Lcd_ID(V_LcdNum);
			V_ucTable[1]=(uchar8)((V_ulDI3DI2DI1DI0>>24)&0x000000FF);
			V_ucTable[2]=(uchar8)((V_ulDI3DI2DI1DI0>>16)&0x000000FF);
			V_ucTable[3]=(uchar8)((V_ulDI3DI2DI1DI0>>8)&0x000000FF);
			V_ucTable[4]=(uchar8)((V_ulDI3DI2DI1DI0)&0x000000FF);
			if((4==V_LcdNum)||(6==V_LcdNum)||(8==V_LcdNum))///表号通信地址客户编号
			{
				V_ucTable[0]=0x01;
			}
			else
			{
				V_ucTable[0]=0x00;
			}
			
			LibPub_MemExchangeBytes( V_ucTable, &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_R],5);	///*返回数据为数据标识加屏号 5字节
			Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = 5+4;  ///返回数据长度为数据长度加上4
			return (API_DLT645_COMM_ERR_OK);
	}
    for(i=0;i<MAX_Comm_MAP_TAB;i++)
	{
		if(V_ulDI3DI2DI1DI0==Comm_MAP_TAB[i].ucaDataId)
		{
			
			P_ucTemp = Comm_MAP_TAB[i].ucaRamAdd;
			LibPub_MemExchangeBytes( P_ucTemp, &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_R], Comm_MAP_TAB[i]. ucaDataLen);	
			if((_TRUE==Comm_MAP_TAB[i].IsBCD)&&(_TRUE==Comm_MAP_TAB[i].EEIsHEX))///目前只有显示参数需要转换格式
			{
				Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_R]=LibPub_1Hex_2_1BCD(Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_R]);
			}
			Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = Comm_MAP_TAB[i]. ucaDataLen+4;  ///返回数据长度为数据长度加上4
			return (API_DLT645_COMM_ERR_OK);
		}	
	}
	return (API_DLT645_COMM_ERR_NODATA) ;
}

///**********************************************************************///
///* Brief: 写数据                                                      *///
///*                                                                    *///
///* Param:  v_ucChID：通道                                             */// 
///*                                                                    *///
///* Return: 返回处理结果                     					        *///
///*                                                                    *///
///* Note:   修改及其他说明                                              *///
///**********************************************************************///
///* FE FE FE FE 68 A0 A1 A2 A3 A4 A5 68 C  L  DI0DI1DI2DI3 PAP0P1P2 C0C1C2C3 D0D1...Dn CS 16 *///
static uchar8 ApiDLT645_WriteData( uchar8 v_ucChID)
{
	uchar8		V_ucErrorType = API_DLT645_COMM_ERR_NOAUTH; 	///* 密码错未授权 *///
	uchar8		P_ucTemp[64];
	uchar8      V_Temp,V_Temp1,V_ScreenNum,V_LcdNum,i;
	ulong32		V_ulDI3DI2DI1DI0;
	//uchar8	V_ucBleStatus;

	V_ulDI3DI2DI1DI0  = (ulong32) Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0];
	V_ulDI3DI2DI1DI0 |= (ulong32) Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+1]<<8;
	V_ulDI3DI2DI1DI0 |= (ulong32) Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+2]<<16;
	V_ulDI3DI2DI1DI0 |= (ulong32) Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+3]<<24;
	
	if((V_ulDI3DI2DI1DI0 & 0xFFFFFF00) == 0xEEEEEE00)
	{
		//V_ucBleStatus = BleDrv_GetBleStat();
		if( BLE_STAT_CONNECTED != GStr_Flag.ucBLESTATFlag)		///*空闲状态*///
		{
			V_Temp = API_DLT645_COMM_ERR_NOACK;	///*空闲状态不应答*///
			return(V_Temp);
		}
		else
		{
			V_Temp = MultiDataWrite_Deal(v_ucChID);
			return (V_Temp);	
		}
	}

	switch(Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_PA0] )
	{
		case 0x98:
		case 0x99:
		{
			if((0==(GStr_Flag.ucRunState2&F_RUN_INTAUTHAvailabilityFlag))||(GStr_Flag.ucRunState2&F_RUN_INTAUTH_MACNumErrFlag))
			{
				return(API_DLT645_COMM_ERR_NOAUTH);
			}///98\99级密码身份认证失效和身份认证挂起， 回密码错
			V_Temp1=0;
			switch(V_ulDI3DI2DI1DI0)
			{
					case 0x04000402:	//表号
					case 0x0400040E:	//客户编号
					case 0x04001001:	//报警金额1
					case 0x04001002:	//报警金额2
					#if(METER_TYPE==METER_TYPE_DTSY666)  ///单相表不可写电压电流互感器变比，默认为1
					case 0x04000306:  //电压互感器变比
					case 0x04000307:  //电流互感器变比
					#endif
					{
						V_Temp1 = 11;
					}break;
					
					case 0x040501FF:	///* 当前套费率电价4*4 *///
					{
						V_Temp1 = 12;
					}break;
					default:break;
			}
			if(V_Temp1!=0)
			{
				V_Temp=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN]-16;
				if( (0x99==Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_PA0]) && (_SUCCESS==LibPub_IsBCD(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W], V_Temp )))
				{
					if(V_Temp1==12)
					{
								for( i = 0; i < 4; i++ )
								{
									LibPub_Inverse(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+i*4],  4);	///*数据倒向 *///
									
								}
					}
					else
					{
							LibPub_Inverse(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W],  V_Temp);	///*数据倒序 *///
					}
					LibPub_Inverse(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+V_Temp], 4); ///* MAC倒序*///
					if( C_ERR == PrepaymentModule_CommWriteESAMBinaryMAC(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W], V_Temp, V_Temp1, 0x01) )
					{ return(API_DLT645_COMM_ERR_NOAUTH); }
					if(V_Temp1==12)
					{
								for( i = 0; i < 4; i++ )
								{
										LibPub_Inverse(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+i*4],  4);	///* 数据倒序*///
								}
					}
					else
					{
							LibPub_Inverse(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W],  V_Temp);	///* 数据倒序 *///
					}
					
					Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN]-=4;

				}
				else
				{
					return(API_DLT645_COMM_ERR_NOAUTH);
				}
			}
			else if(0x98==Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_PA0])
			{
			    if( Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN]>16)
				{
						if( ((V_ulDI3DI2DI1DI0==0x04001006) || (V_ulDI3DI2DI1DI0==0x040010FF)) && (Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN]== 24) )
						{
							V_Temp1 = 15;  ///退费
						}
						else
						{
							V_Temp1 = 16;  //二类参数设置
						}
						V_Temp=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN]-16;
						LibPub_Inverse(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W],  V_Temp);	///*数据倒序 *///
						LibPub_Inverse(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+V_Temp], 4); ///* MAC倒序*///
						///*数据解密  带MAC *///
						if( C_ERR == PrepaymentModule_DataDecription(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W], V_Temp1, &V_Temp) )
						{ return(API_DLT645_COMM_ERR_NOAUTH);}
						
						LibPub_Inverse(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W], V_Temp );
						if( V_Temp1 == 15 )///* 退费0x04001006 *///
						{
							if(( BLE_STAT_CONNECTED != GStr_Flag.ucBLESTATFlag)&&(V_ulDI3DI2DI1DI0 == 0x040010FF))		///*空闲状态*///
							{
								return(API_DLT645_COMM_ERR_NOACK);		///*空闲状态不应答*///								
							}

							P_ucTemp[0] = PrepaymentModule_Comm_HandBackMoney(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W]);
							if( V_ulDI3DI2DI1DI0 == 0x040010FF )	///*自扩退费命令，带返回参数，与原先退费命令兼容*///
							{
								///当前总电量4字节
								LibPub_MemExchangeBytes(&GStr_Energy.ucaFw_Energy[0], &P_ucTemp[1], 0x04 );

								///表内剩余金额4字节
								LibPub_MemExchangeBytes(&GStr_Money.ucaRemainMoney[0], &P_ucTemp[5], 0x04 );

								///购电次数4字节
								LibPub_MemExchangeBytes(&GStr_PRICE.ucPurchaseTimes[0], &P_ucTemp[9], 0x04 );

								///表内透支金额4字节
								LibPub_MemExchangeBytes(GStr_Money.ucaTickMoney, &P_ucTemp[13], 0x04 );

								///状态字3 2字节
								//V_usStateFlag3=ApiDLT645_GetStatusFlag3();
								P_ucTemp[17]=(uchar8)ApiDLT645_GetStatusFlag3();
								P_ucTemp[18]=(uchar8)(ApiDLT645_GetStatusFlag3()>>8);

								LibPub_MemCopyBytes( P_ucTemp, &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_R], 19);	

								Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = 23;///*返回数据的长度，包含了4个字节的标识码*///							
							}
							return( P_ucTemp[0] );
						}
						Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = 12+V_Temp;
				}
				else
				{
					return(API_DLT645_COMM_ERR_NOAUTH);
				}
			}
			else
			{
				return(API_DLT645_COMM_ERR_NOAUTH);
			}	
		}break;
		case 0x00:    ///00级密码只能修改01级、02级密码
		{
			if((V_ulDI3DI2DI1DI0!=0x04000C01)&&(V_ulDI3DI2DI1DI0!=0x04000C02)&&(V_ulDI3DI2DI1DI0!=0x04000C03))
			{
				return(API_DLT645_COMM_ERR_NOAUTH);
			}
			if((_FAILED==LibPub_CheckPassword(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_PA0]))&&(!(GStr_Flag.ucMeterMode&F_FACTORY_MODE)))
			{////密码错误 并且厂外模式   厂内模式不判断密码，只判密级
				return(API_DLT645_COMM_ERR_NOAUTH);
			}
		}break;
		case 0x01:  ///01级密码不能修改00级密码  
		{
			if(V_ulDI3DI2DI1DI0==0x04000C01)
			{
				return(API_DLT645_COMM_ERR_NOAUTH);
			}
			if(!(GStr_Flag.ucMeterMode&F_FACTORY_MODE))///厂外模式
			{
					if((V_ulDI3DI2DI1DI0==0x040501FF)||(V_ulDI3DI2DI1DI0==0x04000402)||(V_ulDI3DI2DI1DI0==0x0400040E)||(V_ulDI3DI2DI1DI0==0x04001001)
					||(V_ulDI3DI2DI1DI0==0x04001002)||(V_ulDI3DI2DI1DI0==0x04000306)||(V_ulDI3DI2DI1DI0==0x04000307)
					||(_FAILED==LibPub_CheckPassword(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_PA0])))
					{///密码错或电价表号等一类参数回密码错未授权
							return(API_DLT645_COMM_ERR_NOAUTH);
					}
					
			}
			else
			{
					#if(METER_TYPE!=METER_TYPE_DTSY666)  ///单相表不可写电压电流互感器变比，默认为1
					if((V_ulDI3DI2DI1DI0==0x04000306)||(V_ulDI3DI2DI1DI0==0x04000307))  //变比
					{
								return(API_DLT645_COMM_ERR_NOAUTH);
					}
					#endif
			}
		}break;
		case 0x02: ///02级密码只能跳和闸，该函数中只能修改02级密码
		{
			if(V_ulDI3DI2DI1DI0!=0x04000C03)
			{
				return(API_DLT645_COMM_ERR_NOAUTH);
			}
			if((_FAILED==LibPub_CheckPassword(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_PA0]))&&(!(GStr_Flag.ucMeterMode&F_FACTORY_MODE)))
			{////密码错误 并且厂外模式   厂内模式不判断密码，只判密级
				return(API_DLT645_COMM_ERR_NOAUTH);
			}
		}break;
		default:
		return(API_DLT645_COMM_ERR_NOAUTH);
		
	}
  if(V_ulDI3DI2DI1DI0==0x040501FF)///费率电价4*4
	{
				if(28!=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN])
				          	//4字节数据标识+4字节密码+4字节操作者代码+16数据
				{
					return ( API_DLT645_COMM_ERR_OTHER );
				}
				if(_FAILED==LibPub_IsBCD(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W], 16 ))
				{
						return ( API_DLT645_COMM_ERR_OTHER );
				}
				LibPub_MemExchangeBytes( &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W],GStr_PRICE.ucaPrice , 4);
					///更新RAM
				LibPub_ReadDataFromE2prom(LIB_E2P_Price,0,P_ucTemp);//将EE内数据读出算CRC
				LibPub_MemExchangeBytes( &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W],&P_ucTemp[0] , 4);
				LibPub_WriteDataToE2prom(LIB_E2P_Price,0,P_ucTemp );//写入EE
				Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = 0;
				return (API_DLT645_COMM_ERR_OK);
	}
	
	if((0x04040100==(V_ulDI3DI2DI1DI0&0xFFFFFF00))||(0x04040200==(V_ulDI3DI2DI1DI0&0xFFFFFF00)))///*循显项和键显项
	{
		V_Temp=V_ulDI3DI2DI1DI0&0x000000FF;
		if(17 != Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN]) ///长度为4字节数据标识+4字节密码+4字节操作者代码+5字节数据
		{
			return ( API_DLT645_COMM_ERR_OTHER );
		}	
		if(30<V_Temp)///最大为30屏
		{
			return ( API_DLT645_COMM_ERR_NODATA );
		}
		if(	0x04040100==(V_ulDI3DI2DI1DI0&0xFFFFFF00))//循显
		{
				for(i=0;i<MAX_Comm_MAP_TAB;i++)
				{
						if(0x04040101==Comm_MAP_TAB[i].ucaDataId)
						{
								V_Temp1=i;
								break;
						}
				}
		}
		else                   //键显
		{
				for(i=0;i<MAX_Comm_MAP_TAB;i++)
				{
						if(0x04040201==Comm_MAP_TAB[i].ucaDataId)
						{
								V_Temp1=i;
								break;
						}
				}
		}
		V_ulDI3DI2DI1DI0  = (ulong32) Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W];
		V_ulDI3DI2DI1DI0 |= (ulong32) Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+1]<<8;
		V_ulDI3DI2DI1DI0 |= (ulong32) Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+2]<<16;
		V_ulDI3DI2DI1DI0 |= (ulong32) Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+3]<<24;
		V_ScreenNum=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+4];//屏号
		
		V_LcdNum=ApiGet_Lcd_Num(V_ulDI3DI2DI1DI0,V_ScreenNum);
		if(0x00!=V_LcdNum)
		{
			V_LcdNum-=1;///获取的屏数从第1屏开始的，实际是从第0屏开始，需减1
			///V_LcdNum为要写入的显示屏号
			Comm_MAP_TAB[V_Temp1].ucaRamAdd[V_Temp-1]=V_LcdNum;///更新RAM
			LibPub_ReadDataFromE2prom(Comm_MAP_TAB[V_Temp1].ucaE2pIndex,0,P_ucTemp);//将EE内数据读出算CRC
			LibPub_MemExchangeBytes( &Comm_MAP_TAB[V_Temp1].ucaRamAdd[V_Temp-1],&P_ucTemp[Comm_MAP_TAB[V_Temp1].ucaE2offset+V_Temp-1]  ,  1);
			//更新需要更改的数据
			LibPub_WriteDataToE2prom( Comm_MAP_TAB[V_Temp1].ucaE2pIndex, 0, P_ucTemp) ;//将更新好的数据带CRC写入EE
			
			Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = 0;
			return (API_DLT645_COMM_ERR_OK);
		}
		return ( API_DLT645_COMM_ERR_OTHER );
	}
	else
	{
		if(0x04000300==(V_ulDI3DI2DI1DI0&0xFFFFFF00))
		{
			switch((uchar8)(V_ulDI3DI2DI1DI0&0x000000FF))
			{
				case 0x01:   ///循环显示屏数
				case 0x05:   ///按键显示屏数
				{		
					if((Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W]>0x30)||(Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W]==0))
					{
						return ( API_DLT645_COMM_ERR_OTHER );
					}
				}break;
				case 0x02:   ///每屏显示时间
				case 0x08:   ///上电全显时间
				{
					if((Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W]>0x30)||(Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W]<0x05))
					{
						return ( API_DLT645_COMM_ERR_OTHER );
					}
				}break;
				default:
				break;
			}
		}
		for(i=0;i<MAX_Comm_MAP_TAB;i++)
		{
			if(V_ulDI3DI2DI1DI0==Comm_MAP_TAB[i].ucaDataId)
			{

				if((4+4+4+Comm_MAP_TAB[i].ucaDataLen)!=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN])
					//4字节数据标识+4字节密码+4字节操作者代码+数据
				{
					return ( API_DLT645_COMM_ERR_OTHER );
				}
				if(_TRUE!=Comm_MAP_TAB[i].IsWrite)   ///不支持写的数据回错
				{
					return ( API_DLT645_COMM_ERR_OTHER );
				}
				if(_TRUE==Comm_MAP_TAB[i].IsBCD)    ///BCD数据先判断数据是否为BCD
				{
					if(_FAILED==LibPub_IsBCD(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W], Comm_MAP_TAB[i].ucaDataLen ))
					{
						return ( API_DLT645_COMM_ERR_OTHER );
					}
					if(_TRUE==Comm_MAP_TAB[i].EEIsHEX)
					{                                    ///*目前只有显示相关参数需要更换格式，均为1字节
						Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W]=LibPub_1BCD_2_1HEX(Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W]);
					}
					
				}
				if(0x04001001==V_ulDI3DI2DI1DI0)///1级报警
				{
					LibPub_MemExchangeBytes(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W],P_ucTemp,4);
					if(C_GreaterThan!=LibPub_CompareData(P_ucTemp, GStr_MoneyPara.ucaAlarmMoneyL2, 4, CMP_MODE_HIGHT))
					{
						return ( API_DLT645_COMM_ERR_OTHER );
					}
				}
				if(0x04001002==V_ulDI3DI2DI1DI0)///2级报警
				{
					LibPub_MemExchangeBytes(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W],P_ucTemp,4);
					if(C_LessThan!=LibPub_CompareData(P_ucTemp, GStr_MoneyPara.ucaAlarmMoneyL1, 4, CMP_MODE_HIGHT))
					{
						return ( API_DLT645_COMM_ERR_OTHER );
					}
				}///写1级报警和2级报警时判断下2个值的大小   2级报警要比1级报警小
				if(0x02800020==V_ulDI3DI2DI1DI0)	//电价不能通过查表方式写
				{
					return ( API_DLT645_COMM_ERR_OTHER );
				}
				
				if(0x04000C00!=(V_ulDI3DI2DI1DI0&0xFFFFFFF0))///密码不存RAM
		    {
				  if((GStr_Flag.ucRunState2&F_RUN_EsamKeyFlag)&&(0x04000402==V_ulDI3DI2DI1DI0))///新增，私钥状态下不允许改表号
		      {
							return ( API_DLT645_COMM_ERR_OTHER );
		      }
					LibPub_MemExchangeBytes( &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W],Comm_MAP_TAB[i].ucaRamAdd , Comm_MAP_TAB[i].ucaDataLen);
					///更新RAM
				  ///RAM的CRC暂时不算，效验错之后直接从EE更新
					LibPub_ReadDataFromE2prom(Comm_MAP_TAB[i].ucaE2pIndex,0,P_ucTemp);//将EE内数据读出算CRC
					LibPub_MemExchangeBytes( &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W],&P_ucTemp[Comm_MAP_TAB[i].ucaE2offset] , Comm_MAP_TAB[i].ucaDataLen);
					LibPub_WriteDataToE2prom( Comm_MAP_TAB[i].ucaE2pIndex,0,P_ucTemp );//写入EE
				}
				else///密码
				{
					if((Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0]-1)!=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W])
					{
						return ( API_DLT645_COMM_ERR_OTHER );
					}
					LibPub_ReadDataFromE2prom(Comm_MAP_TAB[i].ucaE2pIndex,0,P_ucTemp);
					LibPub_MemCopyBytes( &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+1],&P_ucTemp[Comm_MAP_TAB[i].ucaE2offset] ,3);
					LibPub_WriteDataToE2prom( Comm_MAP_TAB[i].ucaE2pIndex,0,P_ucTemp );//写入EE
					///密码倒序存储
					
				}

			    if(0x04001000==(V_ulDI3DI2DI1DI0&0xFFFFFF00))///写报警参数时，需重新判断是否需要动作继电器
				{
					V_Temp=(uchar8)(V_ulDI3DI2DI1DI0);
					if(0x02==V_Temp)///写二级报警金额后要重新判断是否二级报警
					{
						GStr_Flag.ucRunState1 &=~F_RUN_L2_ALRAM;  //清二级报警标志，重新判断
					}
					ApiRelay_SubtractMoneyRelayJudge();
					ApiRelay_ControlProcess();
				}
				
				if( 0x04000401 == V_ulDI3DI2DI1DI0)		//修改地址，需要重新广播蓝牙模块
				{
					GStr_Flag.ucBLESTATFlag = BLE_STAT_MAC_MOD;		//需要设置蓝牙模块mac标志
					/*写完通信地址后需要重新设置蓝牙模块参数，并重新广播*/
					//BleDrv_BleReset();
					//BleDrv_InitBleRunPara();
					//BleDrv_SetBleStat();					
				}	 

				Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = 0;
				return (API_DLT645_COMM_ERR_OK);
			}
		}
		return (API_DLT645_COMM_ERR_OTHER);
	}
	

	return (API_DLT645_COMM_ERR_OTHER);	
}	

///**********************************************************************///
///* Brief: 多数据项组合设置充值命令                                                     *///
///*                                                                    *///
///* Param:  v_ucChID：通道                                             */// 
///*                                                                    *///
///* Return: 返回处理结果                     					        *///
///*                                                                    *///
///* Note:充值金额+购电次数、电价参数、报警金额1、报警金额2、CT、PT、透支金额限值 *///
///*14 L  DI0-DI3 PA P0-P3 C0-C3 K0-K5 MAC DI1DATA BB DI2DATA BB DI3DATA BB DI4DATA BB DI5DATA BB DI6DATA BB DI7DATA*///
///*12 13 14      18 19    22    26    32  36         53         78         91         104        116        128    *///
///*新蓝牙协议*///
///*14 L  DI0-DI3   PA     P0-P3  C0-C3       DI1           DI1DATA*///
///*23 24 25数据标识 20密级 30密码 33操作者代码 37第一个设置项  41数据 *///
///**********************************************************************///
static uchar8 MultiDataWrite_Deal( uchar8 v_ucChID )	//多数据项组合设置
{
	uchar8		V_ucErrorType = API_DLT645_COMM_ERR_NOAUTH; 	/*密码错未授权*/
	uchar8		P_ucTemp[35];				/*用于存放临时数据，充值数据及写e2数据*/
	uchar8		V_ucTempData[70];			/*用于存储返回的数据*/
	uchar8		V_DATALen,V_DATALen1,i,j,NN;/*V_DATALen为各数据的长度；V_DATALen1为BUff中各数据的偏移量；i,j为临时变量；NN为要设置的数据项项数*/
	uchar8		V_ucMoneyflag = 0;			/*用与记录是否有充值业务*/
	uchar8		V_ucDATANum = 0;			/*用与判定数据项项数是否一致*/
	ulong32		V_ulDI3DI2DI1DI0[10];		/*多项数据设置的6个数据标识，一次最多设置6个数据*/
	uchar8		V_ucDATAOffset[11];			/*多项设置前6个数据项的偏移量:*/
	uchar8		V_ucDATALen[10];			/*多项设置6个数据项的长度*/
	ushort16	V_usStateFlag3;				/*运行状态字3*/
	uchar8		AlarmMoneyL1_Set,AlarmMoneyL2_Set;/*报警金额1、2设置标志*/

	NN  = Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0];		/*要设置的数据项项数*/

	if((0==(GStr_Flag.ucRunState2&F_RUN_INTAUTHAvailabilityFlag))||(GStr_Flag.ucRunState2&F_RUN_INTAUTH_MACNumErrFlag))
	{
		return(API_DLT645_COMM_ERR_OTHER);
	}	/*98\99级密码身份认证失效和身份认证挂起， 回密码错*/
	if( 0x99 != Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_PA0] )
	{
		return(API_DLT645_COMM_ERR_NOAUTH);
	}	/*电价参数需99级密级设置*/
	
	/*判断第一个数据标识是不是充值*/
	V_ulDI3DI2DI1DI0[0]  = (ulong32) Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W];		/*API_DLT645_D0_W，第一个DI数据充值金额+购电次数*/	
	V_ulDI3DI2DI1DI0[0] |= (ulong32) Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+1]<<8;		
	V_ulDI3DI2DI1DI0[0] |= (ulong32) Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+2]<<16;
	V_ulDI3DI2DI1DI0[0] |= (ulong32) Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+3]<<24;

	if( 0x070102FF == V_ulDI3DI2DI1DI0[0])		/*存在充值业务*/
	{
		V_ucMoneyflag = 1;			/*第一个数据项为充值，下个数据放在第2个buff中*/
		V_ucDATANum = 1;
		V_ucDATAOffset[0] = 0x00;
		V_ucDATAOffset[1] = 0x1A;		/*充值26个字节：070102FF+充值金额+购电次数+MAC+客户编号+MAC*/
		V_ucDATALen[0] = 0x12;
	}
	else
	{
		V_ucDATAOffset[0] = 0x00;
		V_ucMoneyflag = 0;			/*第一个数据项不为充值，第一个个数据放在第1个buff中*/
		V_ucDATANum = 0;
	}

	for(i=V_ucMoneyflag; i<NN; i++)	/*判断设置的数据项是否在Comm_MAP_TAB表格中*/
	{
		V_ulDI3DI2DI1DI0[i]  = (ulong32) Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+V_ucDATAOffset[i]];		/*API_DLT645_D0_W，第一个DI数据充值金额+购电次数*/	
		V_ulDI3DI2DI1DI0[i] |= (ulong32) Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+V_ucDATAOffset[i]+1]<<8;
		V_ulDI3DI2DI1DI0[i] |= (ulong32) Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+V_ucDATAOffset[i]+2]<<16;
		V_ulDI3DI2DI1DI0[i] |= (ulong32) Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+V_ucDATAOffset[i]+3]<<24;

		for(j=0; j<MAX_Comm_MAP_TAB; j++)
		{
			if(V_ulDI3DI2DI1DI0[i] == Comm_MAP_TAB[j].ucaDataId)
			{
				V_ucDATALen[i] = Comm_MAP_TAB[j].ucaDataLen;
				V_ucDATAOffset[i+1] = V_ucDATAOffset[i] + V_ucDATALen[i]+4+4;	/*数据长度+标识码+MAC*/
				V_ucDATANum++;
			}
		}
		if(_FAILED==LibPub_IsBCD(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+4+V_ucDATAOffset[i]], V_ucDATALen[i]) )
		{
			return ( API_DLT645_COMM_ERR_OTHER );		/*数据不是BCD码，返回其他错误*/
		}			
	}
	if( V_ucDATANum != NN)
	{
		return ( API_DLT645_COMM_ERR_OTHER );			/*数据项数对不上，返回其他错误*/		
	}

	/*格式正确，组织返回数据帧的数据标识，数据标识+错误特征字（5字节）*/
	for(i=0; i<NN; i++)
	{
		V_ucTempData[i*5+0]	= (V_ulDI3DI2DI1DI0[i])     & 0xFF;
		V_ucTempData[i*5+1]	= (V_ulDI3DI2DI1DI0[i]>>8)  & 0xFF;	
		V_ucTempData[i*5+2]	= (V_ulDI3DI2DI1DI0[i]>>16) & 0xFF;	
		V_ucTempData[i*5+3]	= (V_ulDI3DI2DI1DI0[i]>>24) & 0xFF;
		V_ucTempData[i*5+4]	= 0x00;		/*默认设置成功*/
		#if (METER_TYPE != METER_TYPE_DTSY666)		/*导轨表和单相表不能设置电流电压互感器变比*/
		{		
			if((V_ulDI3DI2DI1DI0[i] == 0x04000306)||(V_ulDI3DI2DI1DI0[i] == 0x04000307))
			V_ucTempData[i*5+4] = 0x01;		/*电流、电压互感器变比设置失败*/
		}
		#endif
		if(V_ulDI3DI2DI1DI0[i] == 0x04001001)			/*有设置1级2级报警金额*/
		{
			AlarmMoneyL1_Set = ((i<<4)|0x01)&0xFF;		/*前四位表示在哪个数据标识，后四位非0表示有这个标志*/
		}
		else if(V_ulDI3DI2DI1DI0[i] == 0x04001002)
		{
			AlarmMoneyL2_Set = ((i<<4)|0x01)&0xFF;		/*前四位表示在哪个数据标识，后四位非0表示有这个标志*/
		}
	}

	/*需设置报警金额，2级报警要比1级报警小*/
	if( (AlarmMoneyL1_Set & 0x01)&(AlarmMoneyL2_Set & 0x01) )
	{
		LibPub_MemExchangeBytes(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+4+V_ucDATAOffset[AlarmMoneyL1_Set>>0x04]],P_ucTemp,4);		/*1级报警金额*/
		LibPub_MemExchangeBytes(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+4+V_ucDATAOffset[AlarmMoneyL2_Set>>0x04]],P_ucTemp+4,4);		/*2级报警金额*/
		if(C_GreaterThan!=LibPub_CompareData(P_ucTemp, P_ucTemp+4, 4, CMP_MODE_HIGHT))
		{
			V_ucTempData[4+5*(AlarmMoneyL1_Set>>0x04)] = 0x01;		/*1级报警金额设置失败*/
			V_ucTempData[4+5*(AlarmMoneyL2_Set>>0x04)] = 0x01;		/*2级报警金额设置失败*/
		}
	}
	/*只设报警金额1，不设报警金额2*/
	else if( AlarmMoneyL1_Set & 0x01 )
	{
		LibPub_MemExchangeBytes(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+4+V_ucDATAOffset[AlarmMoneyL1_Set>>0x04]],P_ucTemp,4);		/*1级报警金额*/
		if(C_GreaterThan!=LibPub_CompareData(P_ucTemp, GStr_MoneyPara.ucaAlarmMoneyL2, 4, CMP_MODE_HIGHT))
		{
			V_ucTempData[4+5*(AlarmMoneyL1_Set>>0x04)] = 0x01;		/*1级报警金额设置失败*/
		}
	}
	/*只设报警金额2，不设报警金额1*/
	else if( AlarmMoneyL2_Set & 0x01 )
	{
		LibPub_MemExchangeBytes(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+4+V_ucDATAOffset[AlarmMoneyL2_Set>>0x04]],P_ucTemp,4);		/*1级报警金额*/
		if(C_GreaterThan!=LibPub_CompareData(GStr_MoneyPara.ucaAlarmMoneyL1, P_ucTemp, 4, CMP_MODE_HIGHT))
		{
			V_ucTempData[4+5*(AlarmMoneyL2_Set>>0x04)] = 0x01;		/*1级报警金额设置失败*/
		}
	}

	/*有充值先进行充值设置 0x070102FF+充值金额+购电次数+MAC+客户编号+MAC*/	
	if( 0x070102FF == V_ulDI3DI2DI1DI0[0] )		
	{
		/*数据标识DI，4字节*/
		LibPub_MemCopyBytes(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W], &P_ucTemp[0], 0x04 );		/*老蓝牙协议第26个数据*/	
		/*LibPub_Inverse( &P_ucTemp[0], 4 );数据标识DI数据倒向*/
		
		/*操作者代码，4字节*/
		LibPub_MemCopyBytes(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W-4], &P_ucTemp[4], 0x04 );	/*老蓝牙协议第22个数据*/	

		/*充值金额+购电次数+MAC，12字节*/
		LibPub_MemCopyBytes(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+4], &P_ucTemp[8], 0x0C );	/*老蓝牙协议第30个数据*/

		/*客户编号+MAC，10字节*/
		LibPub_MemCopyBytes(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+16], &P_ucTemp[20], 0x0A );	/*老蓝牙协议第42个数据*/

		/*充值操作，返回充值是否成功*/
		V_ucTempData[4] = PrepaymentModule_Comm_OpenAccout(&P_ucTemp[0]);
	}

	/*0x04001001:报警金额1+MAC  0x04001002:报警金额2+MAC  0x04000306:CT+MAC  0x04000307:PT+MAC  0x04001003:透支金额限值+MAC*/
	for( i=V_ucMoneyflag; i<NN; i++ )		/*i=1,有充值；i=0，无充值*/
	{
		for( j=0; j<MAX_Comm_MAP_TAB; j++ )
		{
			if( V_ulDI3DI2DI1DI0[i] == Comm_MAP_TAB[j].ucaDataId )
			{
				if( _TRUE != Comm_MAP_TAB[j].IsWrite )   
				{
					V_ucTempData[i*5+4] = 0x02;		/*不支持写的数据回02*/
				}

				V_DATALen1 = V_ucDATAOffset[i];				/*BUff中各数据的偏移量*/
				V_DATALen = Comm_MAP_TAB[j].ucaDataLen;		/*各数据的长度*/
				LibPub_Inverse( &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+4+V_DATALen1], V_DATALen );/*数据倒序*/
				LibPub_Inverse( &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+4+V_DATALen1+V_DATALen], 4 ); /* MAC倒序*/
				if( C_ERR == PrepaymentModule_CommWriteESAMBinaryMAC( &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+4+V_DATALen1], V_DATALen, 11, 0x01) )
				{ 
					V_ucTempData[i*5+4] = 0x04;		/*MAC校验失败*/
				}
				if(V_ucTempData[i*5+4] == 0x00)		/*都正确则写参数*/
				{
					LibPub_MemCopyBytes( &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+4+V_DATALen1], Comm_MAP_TAB[j].ucaRamAdd, V_DATALen);
					LibPub_Inverse( &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+4+V_DATALen1], V_DATALen );	/*数据倒序*/
					/*更新RAM和EE,RAM的CRC暂时不算，效验错之后直接从EE更新*/
					LibPub_ReadDataFromE2prom(Comm_MAP_TAB[j].ucaE2pIndex,0,P_ucTemp);		/*将EE内数据读出算CRC*/
					LibPub_MemExchangeBytes( &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+4+V_DATALen1],&P_ucTemp[Comm_MAP_TAB[j].ucaE2offset] , Comm_MAP_TAB[j].ucaDataLen);
					LibPub_WriteDataToE2prom( Comm_MAP_TAB[j].ucaE2pIndex,0,P_ucTemp );		/*写入EE*/
				}
			}
		}
	}

	/*当前总电量4字节 5*NN*/
	LibPub_MemExchangeBytes(&GStr_Energy.ucaFw_Energy[0], &V_ucTempData[5*NN], 0x04 );

	/*总购电金额4字节*/
	LibPub_MemExchangeBytes(&GStr_PRICE.ucaPurchaseMoneyAll[0], &V_ucTempData[5*NN+4], 0x04 );

	/*购电次数4字节*/
	LibPub_MemExchangeBytes(&GStr_PRICE.ucPurchaseTimes[0], &V_ucTempData[5*NN+8], 0x04 );

	/*表内剩余金额4字节*/
	LibPub_MemExchangeBytes(&GStr_Money.ucaRemainMoney[0], &V_ucTempData[5*NN+12], 0x04 );

	/*表内透支金额4字节*/
	LibPub_MemExchangeBytes(GStr_Money.ucaTickMoney, &V_ucTempData[5*NN+16], 0x04 );

	/*状态字3 2字节*/
	V_usStateFlag3=ApiDLT645_GetStatusFlag3();
	V_ucTempData[5*NN+20]=(uchar8)V_usStateFlag3;
	V_ucTempData[5*NN+21]=(uchar8)(V_usStateFlag3>>8);

	LibPub_MemCopyBytes( V_ucTempData, &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_R], 5*NN+22);	

	Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = 5*NN+26;/*返回数据的长度，包含了4个字节的标识码*/
	
	return(API_DLT645_COMM_ERR_OK);
}

///**********************************************************************///
///* Brief: 费控命令                                                     *///
///*                                                                    *///
///* Param:  v_ucChID：通道                                             */// 
///*                                                                    *///
///* Return: 返回处理结果                     					        *///
///*                                                                    *///
///* Note:   修改及其他说明                                              *///
///**********************************************************************///
uchar8 ApiDLT645_RelayControl(uchar8 v_ucChID)
{
///FE FE FE FE 68 03 00 00 00 00 00 68 1C 10 36 33 33 33 45 33 33 33 4D 33 33 33 33 34 34 CC F9 16 
	uchar8      V_ucTemp;
	uchar8		V_ucErrorType = API_DLT645_COMM_ERR_NODATA; 	///* 无请求数据 *///
	
	if  (Gstr_UartComm[v_ucChID].ucCommAddrType != F_COMMADDRTYPE_ID)	/* 全地址相等才可以操作 */
	{
		return V_ucErrorType;
	}

	if(0x98 == Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA])
	{
		if((!(GStr_Flag.ucRunState2&F_RUN_INTAUTHAvailabilityFlag))||(GStr_Flag.ucRunState2&F_RUN_INTAUTH_MACNumErrFlag))///*身份认证有效标志失效||身份认证挂起*///
		{
			return API_DLT645_COMM_ERR_NOAUTH;
		}
		V_ucTemp = Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN]-12;
		LibPub_Inverse(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_C0], V_ucTemp);	
		LibPub_Inverse(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_C0+V_ucTemp], 4);	
		if(C_ERR==PrepaymentModule_DataDecription(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_C0], 17, &V_ucTemp))
		{
			V_ucErrorType=API_DLT645_COMM_ERR_NOAUTH;
			return V_ucErrorType;
		}
		LibPub_Inverse(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_C0], V_ucTemp);	
	}
	else if(0x02 == Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA])
	{
		if(!(GStr_Flag.ucMeterMode&F_FACTORY_MODE))
		{
			if(_FAILED==LibPub_CheckPassword(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA]))
			{
				return API_DLT645_COMM_ERR_NOAUTH;
			}
		}
	}
	else
	{
		return API_DLT645_COMM_ERR_NOAUTH;
	}
		
	
	
	switch(Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_C0])   ///第22位为命令码
	{
		case 0x1A:                  ///* 跳闸
		{
			if(F_RUN_KEEP_ELEC==(GStr_Flag.ucRunState&F_RUN_KEEP_ELEC))  ///保电
			{
				return (API_DLT645_COMM_ERR_NOAUTH);
			}		
			GStr_Flag.ucRunState |= F_RUN_COMM_RELAYOFF;
			ApiRelay_ControlProcess();
			LibPub_WriteDataToE2prom(LIB_E2P_RUN_STATE,0,&GStr_Flag.ucRunState);
			V_ucErrorType=API_DLT645_COMM_ERR_OK;
			Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = 0;
		}break;
		
        case 0x1C:                ///*合闸
		{
			if(F_RUN_DISABLE_CLOSE==(GStr_Flag.ucRunState&F_RUN_DISABLE_CLOSE))
			{
				return (API_DLT645_COMM_ERR_NOAUTH);
			}
			
			if(GStr_Flag.ucRunState1&F_RUN_L2_ALRAM)	/*与小程序匹配，二级报警和过零只要有通信合闸命令就合闸*/
			{
				GStr_Flag.ucRunState|=F_RUN_CLOSE_L2;
			}
			if(GStr_Flag.ucRunState1&F_RUN_REMAIND_ZERO)
			{
				GStr_Flag.ucRunState|=F_RUN_CLOSE_ZERO;
			}

			GStr_Flag.ucRunState &=~F_RUN_COMM_RELAYOFF;		
			GStr_Flag.ucRunState1 &=~F_RUN_OVER_DEMAND_CLOSE;    ///合闸，清除过载恢复合闸标志
			ApiRelay_ControlProcess();
			LibPub_WriteDataToE2prom(LIB_E2P_RUN_STATE,0,&GStr_Flag.ucRunState);
			V_ucErrorType=API_DLT645_COMM_ERR_OK;
			Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = 0;
		}break;
		
		case 0x3A:              ///*保电
		{
			GStr_Flag.ucRunState  |=F_RUN_KEEP_ELEC;		
			GStr_Flag.ucRunState1 &=~F_RUN_OVER_DEMAND_CLOSE;    ///保电自动合闸，清除过载恢复合闸标志
			ApiRelay_ControlProcess();
			LibPub_WriteDataToE2prom(LIB_E2P_RUN_STATE,0,&GStr_Flag.ucRunState);
			V_ucErrorType=API_DLT645_COMM_ERR_OK;
			Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = 0;
		}break;
		
		case 0x3B:              ///*保电解除
		{
			GStr_Flag.ucRunState &=~F_RUN_KEEP_ELEC;		
			ApiRelay_ControlProcess();
			LibPub_WriteDataToE2prom(LIB_E2P_RUN_STATE,0,&GStr_Flag.ucRunState);
			V_ucErrorType=API_DLT645_COMM_ERR_OK;
			Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = 0;
		}break;
		default :
		return API_DLT645_COMM_ERR_NODATA;
	}
	
    return  V_ucErrorType;

}



///**********************************************************************///
///* Brief:  厂内自扩命令                                                *///
///*                                                                    *///
///* Param:  v_ucChID：通道                                             */// 
///*                                                                    *///
///* Return: 返回处理结果                     					        *///
///*                                                                    *///
///* Note:   修改及其他说明                                              *///
///**********************************************************************///
static uchar8 ApiDLT645_FactoryCommand( uchar8 v_ucChID )
{
	uchar8		V_ucErrorType = API_DLT645_COMM_ERR_NODATA; 	///* 无请求数据 *///
	uchar8		V_ucTempdata;
	ushort16	V_usAddress; 
//	uchar8    V_ucTempData08[3];
	ulong32		V_ulDI3DI2DI1DI0,V_ulTempData32;

	
	V_ulDI3DI2DI1DI0  = (ulong32) Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0];
	V_ulDI3DI2DI1DI0 |= (ulong32) Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+1]<<8;
	V_ulDI3DI2DI1DI0 |= (ulong32) Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+2]<<16;
	V_ulDI3DI2DI1DI0 |= (ulong32) Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+3]<<24;
	
	if ( Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_CMD] == API_DLT645_CMD_FACTORY_1E )
	{
		if (  V_ulDI3DI2DI1DI0 == 0xFFFFFFFF ) 
		{
 			switch( Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+4] )
 			{
 				///* 读E2:	FE FE FE FE 68 00 00 00 00 00 00 68 1E 0A 32 32 32 32 33 67 45 33 33 43 48 16 *///
 				///* 读RAM:	FE FE FE FE 68 00 00 00 00 00 00 68 1E 0A 32 32 32 32 34 67 45 33 33 43 49 16 *///

				case 0x00:	///* 读RAM *///
 				case 0x01:	///* 读E2  *///  数据不倒序
 				{
 					if ( Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] == 0x0A )
 					{
 						if ( Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+9] <= 32 )	///* 一次只能抄读32字节
 						{
 							V_usAddress  = ((ushort16)Gstr_UartComm[v_ucChID].ucaCommTXBuff[20]<<8) & 0xff00;					
 							V_usAddress |= ((ushort16)Gstr_UartComm[v_ucChID].ucaCommTXBuff[19]) & 0x00ff;
 							V_ucTempdata = Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+9];
 							
 							if ( Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+4] == 0 )	///* 读RAM *///
 							{
 								if( (V_usAddress+V_ucTempdata) > 0x1f00)	// 地址+长度超过最大地址，则直接退出
 								{
 									break;
 								}
 								LibPub_MemCopyBytes( (uchar8 xdata*)(V_usAddress), &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_R], V_ucTempdata);
 							}
 							else	///* 读E2 *///
 							{
 								DrvE2p_ReadData( V_usAddress, &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_R], V_ucTempdata);							
								
 								///* 如果读取的e2地址包含密码地址，则返回数据用FF填充，厂外适用 *///
 								if ( F_FACTORY_MODE != (GStr_Flag.ucMeterMode & F_FACTORY_MODE ) )
 								{
 									///* 地址小于密码地址，地址+长度大于等于密码地址 *///
 									if( V_usAddress <= EEPROM_MAP_TAB[LIB_E2P_Password].usE2pAddress )
 									{
 										if( (V_usAddress+V_ucTempdata) >= EEPROM_MAP_TAB[LIB_E2P_Password].usE2pAddress ) 
 										{
 											LibPub_MemSetBytes( &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_R], 0xff, V_ucTempdata );
 										}
 									}///* 地址大于密码地址，但小于密码地址+长度 *///
 									else if(  ( V_usAddress <= EEPROM_MAP_TAB[LIB_E2P_Password].usE2pAddress + EEPROM_MAP_TAB[LIB_E2P_Password].ucE2pLen ) )
 									{
 										LibPub_MemSetBytes( &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_R], 0xff, V_ucTempdata );
 									}
 								}
 							}
 							
 							Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = 4+V_ucTempdata;				
 							
 							V_ucErrorType = API_DLT645_COMM_ERR_OK;
 						}
 					}
 				}break;
			///* 读类EE：FE FE FE FE 68 00 00 00 00 00 00 68 1E 0A 32 32 32 32 35 67 45 33 33 43 49 16 *///
				case 0x02:  ///* 读类EE*///
				{
						if ( Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] == 0x0A )
						{
								if ( Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+9] <= 128 )	///* 一次最多抄读128字节
								{
											V_usAddress  = ((ushort16)Gstr_UartComm[v_ucChID].ucaCommTXBuff[20]<<8) & 0xff00;					
											V_usAddress |= ((ushort16)Gstr_UartComm[v_ucChID].ucaCommTXBuff[19]) & 0x00ff;
											V_ucTempdata = Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+9];
									    
											if(0xFF==Hal_ReadEEPROM( &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_R], V_usAddress, V_ucTempdata))
											{
													break;
											}
											Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = 4+V_ucTempdata;				
											V_ucErrorType = API_DLT645_COMM_ERR_OK;
								}
						}
				
				}break;
 				///* 设置软I_J FE FE FE FE 68 AA AA AA AA AA AA 68 1E 09 32 32 32 32 4D F3 DB 33 33 3C 16  *///
 				case 0x1A:
 				{
 					V_ucErrorType = API_DLT645_COMM_ERR_NOAUTH;
 					///* 数据长度不为9，则退出 *///
 					if ( Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] == 0x09 )
 					{
 						///* 准备一下数据 */// 
 						LibPub_MemExchangeBytes( &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+5] ,( uchar8*)&V_ulTempData32, 4 );
 						
						if ( F_KEY_ACKTION_DOWN != (GStr_Flag.ucFactoryKey & F_KEY_ACKTION_DOWN) )
 						{
 							if( V_ulTempData32!= 0 ) break;
 						}
 						
 						if( V_ulTempData32 > FACTORY_MAX_TIME) break;
 						
 						GStr_Monitor.ulSoftI_JTime = V_ulTempData32;
 						
 						if( GStr_Monitor.ulSoftI_JTime == 0 )
 						{
 							GStr_Flag.ucMeterMode &= ~F_FACTORY_MODE;
 						}
 						else
 						{
 							GStr_Flag.ucMeterMode |= F_FACTORY_MODE;
 						}
 						LibPub_WriteDataToE2prom( LIB_E2P_SOFTI_J, 0, (uchar8 *)&GStr_Monitor.ulSoftI_JTime);						
 						
 						Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = 0;					
 						V_ucErrorType = API_DLT645_COMM_ERR_OK;
 					}
 					
 				}break;
 				
 				///* 读软I_J FE FE FE FE 68 AA AA AA AA AA AA 68 1E 09 32 32 32 32 4E 33 33 33 33 D5 16   *///
 				case 0x1B:
 				{
					LibPub_ReadDataFromE2prom( LIB_E2P_SOFTI_J, 0, (uchar8 *)&GStr_Monitor.ulSoftI_JTime );
					LibPub_MemExchangeBytes( (uchar8 *)&GStr_Monitor.ulSoftI_JTime, &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+5] , 4 );
 					
 					Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = 9;					
 					V_ucErrorType = API_DLT645_COMM_ERR_OK;
 				}break;
 				
				case 0x2A:////*写蓝牙参数  FE FE FE FE 68 A0 A1 A2 A3 A4 A5 68 1E 1D 32 32 32 32 5D MAC5 4 3 2 1 0 NAME11 10 9 8 7 6 5 4 3 2 1 0 KEY2 1 0 ucAdvTime1  0  ucBleTPL  cs 16
				{
					if( 0x1D != Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] )
					{
						break;
					}
					
					/*------------------------------------------------------------------------------------------------------*/
					/* 更新参数  */
					LibPub_MemExchangeBytes(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+5], &GStr_BLEGroup.ucBleMAC[0], 6);
					LibPub_MemExchangeBytes(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+11], &GStr_BLEGroup.ucBleName[0], 12);
					LibPub_MemExchangeBytes(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+23], &GStr_BLEGroup.ucBleKey[0], 3);
					LibPub_MemExchangeBytes(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+26], (uchar8*)&GStr_BLEGroup.usAdvTime, 2);
					GStr_BLEGroup.ucBleTPL=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+28];
					
					/*------------------------------------------------------------------------------------------------------*/
					/* 计算一下crc，将参数写入E2  */
					GStr_BLEGroup.usCRC16 = LibPub_CRC16_CCITT(&GStr_BLEGroup.ucBleMAC[0], GStr_BLE_GROUP_TypeLEN-2); 
					LibPub_WriteDataToE2prom( LIB_E2P_BLE_PARA, 0, &GStr_BLEGroup.ucBleMAC[0])	;	
					
					
					/*------------------------------------------------------------------------------------------------------*/
					GStr_Flag.ucBLESTATFlag = BLE_STAT_MAC_MOD;		//需要设置蓝牙模块mac标志
					/* 如果RAM参数有变化，重新设置一下蓝牙参数，设置成广播态，这里会有延迟，所以这帧数据的回复会延时较长 */
					//BleDrv_BleReset();
					//BleDrv_SetBleRunPara();
					//BleDrv_SetBleStat();
					
					Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = 0;
					V_ucErrorType = API_DLT645_COMM_ERR_OK;
						
				}break;
					
				case 0x2B:	/*读蓝牙参数  FE FE FE FE 68 A0 A1 A2 A3 A4 A5 68 1E 09 32 32 32 32 5E 33 33 33 33 cs 16 */
							/*            9E  17  MAC5..0  name11...0 key3..0  time1 0 */
				{
					if(0x09!=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN])
					{
						break;
					}	
					
					BleDrv_GetBleMac(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+5]);
					LibPub_Inverse(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+5], 6);	/*MAC*/
					LibPub_MemExchangeBytes(&GStr_BLEGroup.ucBleName[0],&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+11], 12);		/*名称*/
					LibPub_MemExchangeBytes(&GStr_BLEGroup.ucBleKey[0],&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+23],  3);		/*配对码*/
					LibPub_MemExchangeBytes((uchar8*)&GStr_BLEGroup.usAdvTime,&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+26],  2);	/*广播时间*/
					
					Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+28]=GStr_BLEGroup.ucBleTPL;	/*发射功率*/
					Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN]=0x1D;
					V_ucErrorType = API_DLT645_COMM_ERR_OK;
				}break;
				case 0x20:///读蓝牙MAC  FE FE FE FE 68 A0 A1 A2 A3 A4 A5 68 1E 09 32 32 32 32 53 33 33 33 33 cs 16
				{
					if( 0x09 != Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] )
					{
						break;
					}		
					
					if( _SUCCESS == BleDrv_GetBleMac(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA]) )
					{
						Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN]=0x06;
						V_ucErrorType = API_DLT645_COMM_ERR_OK;
					}
					
				}break;
				
				case 0x21:///读蓝牙名称  FE FE FE FE 68 A0 A1 A2 A3 A4 A5 68 1E 09 32 32 32 32 54 33 33 33 33 cs 16
				{
					if( 0x09 != Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] )
					{
						break;
					}	
					
					if( _SUCCESS == BleDrv_GetBleName(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA]) )
					{
						Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = 0x0C;
						V_ucErrorType = API_DLT645_COMM_ERR_OK;
					}
					
				}break;

				case 0x25:///读蓝牙发射功率  FE FE FE FE 68 A0 A1 A2 A3 A4 A5 68 1E 09 32 32 32 32 58 33 33 33 33 cs 16
				{
					if( 0x09 != Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN])
					{
						break;
					}		
					
					if(_SUCCESS==BleDrv_GetBleTPL(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA]))
					{
						Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN]=0x01;
						V_ucErrorType = API_DLT645_COMM_ERR_OK;
					}
					
				}break;		
				
				case 0x28:	/* 设置蓝牙发射功率   FE FE FE FE 68 A0 A1 A2 A3 A4 A5 68 1E 06 32 32 32 32 5B 33 cs 16 */
				{			/* 1字节 */	
					if( 0x06 != Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] )
					{
						break;
					}		
					if( _SUCCESS == BleDrv_SetBleTPL(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+5]))
					{
						Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = 0x00;
						V_ucErrorType = API_DLT645_COMM_ERR_OK;
						/* 计算一下crc，将参数写入E2  */
						GStr_BLEGroup.ucBleTPL = Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+5];
						GStr_BLEGroup.usCRC16 = LibPub_CRC16_CCITT(&GStr_BLEGroup.ucBleMAC[0], GStr_BLE_GROUP_TypeLEN-2); 
						LibPub_WriteDataToE2prom( LIB_E2P_BLE_PARA, 0, &GStr_BLEGroup.ucBleMAC[0]);			
					}	
				}break;	
				
				case 0x29:	/*设置蓝牙工作模式 01：从（仅做从）FE FE FE FE 68 A0 A1 A2 A3 A4 A5 68 1E 06 32 32 32 32 5C data cs 16*/
				{			/* 1字节 */	
					if( 0x06 != Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] )
					{
						break;
					}					 		
					if( _SUCCESS == BleDrv_CommSetBlePara( COMM_BLE_MOD, BLE_TTP_Len, &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+5] ))
					{
						Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = 0x00;
						V_ucErrorType = API_DLT645_COMM_ERR_OK;
					}	
				}break;	

				case 0x30:	/*读蓝牙工作模式 01：从（仅做从）FE FE FE FE 68 A0 A1 A2 A3 A4 A5 68 1E 09 32 32 32 32 63 33 33 33 33 cs 16*/
				{			/* 1字节 */	
					if( 0x09 != Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] )
					{
						break;
					}					 		
					if( _SUCCESS == BleDrv_CommGetBlePara( COMM_BLE_MOD, BLE_TTP_Len, &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA] ))
					{
						Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = 0x01;
						V_ucErrorType = API_DLT645_COMM_ERR_OK;
					}	
				}break;	

				case 0x31:	/*设置透传协议 01：645协议（默认）02：698协议FE FE FE FE 68 A0 A1 A2 A3 A4 A5 68 1E 06 32 32 32 32 64 data cs 16*/
				{			/* 1字节 */	
					if( 0x06 != Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] )
					{
						break;
					}					 		
					if( _SUCCESS == BleDrv_CommSetBlePara( COMM_BLE_TTP, BLE_TTP_Len, &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+5] ))
					{
						Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = 0x00;
						V_ucErrorType = API_DLT645_COMM_ERR_OK;
					}	
				}break;	

				case 0x32:	/*读透传协议 01：645协议（默认）02：698协议FE FE FE FE 68 A0 A1 A2 A3 A4 A5 68 1E 09 32 32 32 32 65 33 33 33 33 cs 16*/
				{			/* 1字节 */	
					if( 0x09 != Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] )
					{
						break;
					}					 		
					if( _SUCCESS == BleDrv_CommGetBlePara( COMM_BLE_TTP, BLE_TTP_Len, &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA] ))
					{
						Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = 0x01;
						V_ucErrorType = API_DLT645_COMM_ERR_OK;
					}	
				}break;	
				
				case 0x33:	/*读取当前连接的设备MAC （如果没有连接，返回全FF）FE FE FE FE 68 A0 A1 A2 A3 A4 A5 68 1E 09 32 32 32 32 66 33 33 33 33 cs 16*/
				{			/* 6字节 */	
					if( 0x09 != Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] )
					{
						break;
					}					 		
					if( _SUCCESS == BleDrv_CommGetBlePara( COMM_BLE_STAT, BLE_STAT_Len, &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA] ))
					{
						Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = 0x06;
						V_ucErrorType = API_DLT645_COMM_ERR_OK;
					}	
				}break;	
				
				case 0x34:	/*模块固件版本号ASCII（需对照版本格式）FE FE FE FE 68 A0 A1 A2 A3 A4 A5 68 1E 09 32 32 32 32 67 33 33 33 33 cs 16*/
				{			/* 32字节 */	
					if( 0x09 != Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] )
					{
						break;
					}					 		
					if( _SUCCESS == BleDrv_CommGetBlePara( COMM_BLE_MFV, BLE_MFV_Len, &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA] ))
					{
						Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = 0x20;
						V_ucErrorType = API_DLT645_COMM_ERR_OK;
					}	
				}break;	
				
//				case 0x22:///读蓝牙key  FE FE FE FE 68 A0 A1 A2 A3 A4 A5 A6 68 1E 09 32 32 32 32 55 33 33 33 33 cs 16
//				{
//							if(0x09!=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN])
//							{
//									break;
//							}		
//							if(_SUCCESS==BleDrv_GetBleKey(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA]))
//							{
//									Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN]=0x06;
//									V_ucErrorType = API_DLT645_COMM_ERR_OK;
//							}
//							else
//							{
//									break;
//							}
//				}break;
				
//				case 0x23:///读蓝牙配对等级  FE FE FE FE 68 A0 A1 A2 A3 A4 A5 A6 68 1E 09 32 32 32 32 56 33 33 33 33 cs 16
//				{
//							if(0x09!=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN])
//							{
//									break;
//							}		
//							if(_SUCCESS==BleDrv_GetBleSMPLv(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA]))
//							{
//									Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN]=0x01;
//									V_ucErrorType = API_DLT645_COMM_ERR_OK;
//							}
//							else
//							{
//									break;
//							}
//				}break;
				
//				case 0x24:///读蓝牙广播周期  FE FE FE FE 68 A0 A1 A2 A3 A4 A5 A6 68 1E 09 32 32 32 32 57 33 33 33 33 cs 16
//				{
//							if(0x09!=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN])
//							{
//									break;
//							}		
//							if(_SUCCESS==BleDrv_GetBleADVP(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA]))
//							{
//									Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN]=0x05;
//									V_ucErrorType = API_DLT645_COMM_ERR_OK;
//							}
//							else
//							{
//									break;
//							}
//				}break;			
				
//				case 0x26:///读蓝牙配对密码  FE FE FE FE 68 A0 A1 A2 A3 A4 A5 A6 68 1E 09 32 32 32 32 59 33 33 33 33 cs 16
//				{
//							if(0x09!=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN])
//							{
//									break;
//							}		
//							if(_SUCCESS==BleDrv_GetBlePSK(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA]))
//							{
//									Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN]=0x06;
//									V_ucErrorType = API_DLT645_COMM_ERR_OK;
//							}
//							else
//							{
//									break;
//							}
//				}break;		

//				case 0x27:///设置蓝牙配对密码  FE FE FE FE 68 A0 A1 A2 A3 A4 A5 A6 68 1E 0B 32 32 32 32 59 33 33 33 33 33 33 cs 16
//				{
//							if(0x0B!=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN])
//							{
//									break;
//							}		
//							LibPub_Inverse( &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+5], 6 );
//							if(_SUCCESS==BleDrv_SetBlePSK(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+5]))
//							{
//									Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN]=0x00;
//									V_ucErrorType = API_DLT645_COMM_ERR_OK;
//							}
//							else
//							{
//									break;
//							}
//				}break;	

				///* FE FE FE FE  68 AA AA AA AA AA AA 68 1E Len 32 32 32 32 B4 Type data1 data2 data3 CS 16 *///
				///* Type:0x80：读   0x00: 写 *///
				case 0x81:
				{
					if(  Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+5] == 0x00 )		///* 写 *///
					{
						V_ucErrorType = API_DLT645_COMM_ERR_NOAUTH;
						if ( GStr_Flag.ucMeterMode & F_FACTORY_MODE )///* 厂内可写 *///
						{
							if ( Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] == 0x14 )
							{
								if ( _SUCCESS == LibPub_WriteDataToE2prom( LIB_E2P_FUN_CONFIG, 0, &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+6]) )
								{
									LibPub_MemCopyBytes( &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+6], &GStr_FunConfigPara.ucFunCurrentVal, GStr_FUN_CONFIG_TypeLEN );
									Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = 0;					
									V_ucErrorType = API_DLT645_COMM_ERR_OK;
								}
							}
						}
					}
					else if(  Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+5] == 0x80 )	///* 读 *///
					{
						if( _SUCCESS == LibPub_ReadDataFromE2prom( LIB_E2P_FUN_CONFIG, 0, &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_R] ) )
						{
							LibPub_MemCopyBytes( &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_R], &GStr_FunConfigPara.ucFunCurrentVal, GStr_FUN_CONFIG_TypeLEN );
							
							Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = 4+14;
							V_ucErrorType = API_DLT645_COMM_ERR_OK;
						}
					}
					else
					{
						break;
					}
				}break;

 				default:break;
 			}
		}
	}
	else	///* 控制码为1F *///
	{ 
			switch ( Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA] )
			{
					case 0x13:///* 电表初始化：FE FE FE 68 AA AA AA AA AA AA 68 1F 04 46 47 87 B3 B6 16 *///
					{
							V_ucErrorType = API_DLT645_COMM_ERR_NOAUTH;
							if ( GStr_Flag.ucMeterMode & F_FACTORY_MODE )///* 厂内可写 *///
							{
									if( V_ulDI3DI2DI1DI0 == 0x80541413 )
									{
											ApiPwOn_MeterInitInFactory();
											Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = 0;
											V_ucErrorType = API_DLT645_COMM_ERR_OK;
									}
							}
						
					}break;
					
					default:break;
				
			}
	}
		
	return V_ucErrorType;
}


///**********************************************************************///
///* Brief: 身份认证                                                  *///
///*                                                                    *///
///* Param:  v_ucChID：通道                                             */// 
///*                                                                    *///
///* Return: 返回处理结果                     					        *///
///*                                                                    *///
///* Note:   修改及其他说明                                              *///
///**********************************************************************///
uchar8 ApiDLT645_SafeCertification(uchar8 v_ucChID)
{
	uchar8	i,j;
	uchar8	V_ucDI[4];
	uchar8	V_ucErrorType;
	ulong32 V_ulDI0DI1DI2DI3;
	// uchar8	V_Temp,V_Temp1;
	// ushort16	V_usStateFlag3;
	// uchar8	V_ucTempData[60];

	V_ucErrorType = API_DLT645_COMM_ERR_NOACK;
	GU_SecurityErr.BYTE[0] = 0x00;
	GU_SecurityErr.BYTE[1] = 0x00;
	V_ulDI0DI1DI2DI3 = 0;

    LibPub_MemCopyBytes(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0],&GA_ucDICode[0],4);///数据标识
	LibPub_MemCopyBytes(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_PA0],&GA_ucOperCode[0],4);///操作者代码
	if  (Gstr_UartComm[v_ucChID].ucCommAddrType == F_COMMADDRTYPE_ID)	/* 全地址相等才可以操作 */
	{  
		if (GStr_Flag.ucRunState2&F_RUN_INTAUTH_MACNumErrFlag )		///*安全认证标识挂起就不允许执行了*///
		{
			*((ushort16 *)(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA]) )= 0x0001;///*安全认证错误*///
			V_ucErrorType = API_DLT645_SAFE_CERT_ERR;
		}
		else
		{
			for ( i = 0; i < 4; i++ )
			{
				V_ucDI[i] = Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+i];
				V_ulDI0DI1DI2DI3 |= (((ulong32)V_ucDI[i])<<(8*i));
			}
			
			for ( j = 0; j < C_SafeCertifiificationCodeNum; j++ )
			{
				if ( V_ulDI0DI1DI2DI3 == C_ulaSafeCertification_Code[j] )///* 查表找相应的数据标识 *///
				{
					if((Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN])!=C_ulaSafeCertification_Len[j])
					{
						*((ushort16 *)(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA])) = 0x0100;
						V_ucErrorType = API_DLT645_SAFE_CERT_ERR;
						break;
					}
					else
					{
						///* 定义的函数参数和传递的参数不匹配，修改后值传递从DI0开始的数据 *///
						switch ( j )
						{
							case 0:		///身份认证
							{ 
								V_ucErrorType = PrepaymentModule_Comm_INTAUTH(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0]); 
							}break;
							
							case 1:		///身份认证时效设置
							{
								V_ucErrorType = PrepaymentModule_Comm_TimeAvailableIn(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0]); 
							}break;
							
							case 2:		///* 开户 *///
							case 3:		///* 充值 *///
							case 4:		///* 钱包初始化 */// 
							// case 5:		///* 补助金额充值 *///
							{
								V_ucErrorType = PrepaymentModule_Comm_OpenAccout(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0]);  
							}break;
							
						    case 5:		///* 密钥更新 *///
							{
								V_ucErrorType = PrepaymentModule_Comm_ModifyKey(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0]); 
							}break;	
							
							
							case 6:		///* 身份认证失效 *///
							{
								V_ucErrorType = PrepaymentModule_Comm_INTAUTH_Invalidation(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0]);
							}break;
							
							default:  break;		   
						}
 						if( C_ERR == V_ucErrorType)
 						{
 							V_ucErrorType = API_DLT645_SAFE_CERT_ERR;
							Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA]= GU_SecurityErr.BYTE[0];
							Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+1]= GU_SecurityErr.BYTE[1];			   ///*错误返回错误信息字*///
 							break;
 						}
						else
						{
							Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = C_ulaSafeCertification_ReturnLen[j];								
							V_ucErrorType = C_ulaSafeCertification_ReturnType[j];
						}
						break;
					}
				}
			}
			if(j >=C_SafeCertifiificationCodeNum)
			{
 				*((ushort16 *)(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA])) = 0x0100;
				V_ucErrorType = API_DLT645_SAFE_CERT_ERR;
			}
		}
	}
	else
	{
		V_ucErrorType = 0x80;
	}

	return(V_ucErrorType);
	
}
///**********************************************************************///
///* Brief: 电表清零                                                    *///
///*                                                                    *///
///* Param:  v_ucChID：通道                                             */// 
///*                                                                    *///
///* Return: 返回处理结果                     					        *///
///*                                                                    *///
///* Note:   修改及其他说明                                              *///
///**********************************************************************///
uchar8 ApiDLT645_MeterClear( uchar8 v_ucChID )////该命令只在厂内有效，需验证00级密码，密码000000
{
	
	if  (Gstr_UartComm[v_ucChID].ucCommAddrType != F_COMMADDRTYPE_ID)	/* 全地址相等才可以操作 */
	{
			return API_DLT645_COMM_ERR_NODATA;    //0x02	///* 无请求数据 *///
	}
	if  (Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] != 0x08)	/* 长度需为8 */
	{
			return API_DLT645_COMM_ERR_OTHER;     //0x01	///* 其他错误 *///
	}
	if(GStr_Flag.ucMeterMode&F_FACTORY_MODE)
	{
		if(0x00==Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA])
		{
			if(_FAILED==LibPub_CheckPassword(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA]))
			{
				return API_DLT645_COMM_ERR_NOAUTH;
			}	
		}
		else
		{
			return API_DLT645_COMM_ERR_NOAUTH;
		}
	}
	else
	{
			return API_DLT645_COMM_ERR_NOAUTH;	
	}
	Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN]=0;
	ApiPwOn_MeterClear();	
	ApiRelay_SubtractMoneyRelayJudge();///总清完处理一下继电器
	ApiRelay_ControlProcess();
	// GV_ClearFlag=CommClear;
	return API_DLT645_COMM_ERR_OK;
}

///**********************************************************************///
///* Brief: 系统自扩命令（充值、身份认证）                            *///
///*                                                                    *///
///* Param:  v_ucChID：通道                                             */// 
///*                                                                    *///
///* Return: 返回处理结果                     					        *///
///*                                                                    *///
///* Note:   修改及其他说明                                              *///
///**********************************************************************///
uchar8 ApiDLT645_AccountTx(uchar8  v_ucChID )
{
	uchar8	i;
	uchar8	V_ucDI[4];
	uchar8	V_ucErrorType;
	ulong32 V_ulDI0DI1DI2DI3;
	uchar8	V_Temp,V_Temp1;
	ushort16	V_usStateFlag3;
	uchar8	V_ucTempData[35];

	V_ucErrorType = API_DLT645_COMM_ERR_NOACK;
	GU_SecurityErr.BYTE[0] = 0x00;
	GU_SecurityErr.BYTE[1] = 0x00;
	V_ulDI0DI1DI2DI3 = 0;

	if( BLE_STAT_CONNECTED != GStr_Flag.ucBLESTATFlag)		///*空闲状态*///
	{
		return(API_DLT645_COMM_ERR_NOACK);		///*空闲状态不应答*///
	}

    LibPub_MemCopyBytes(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0],&GA_ucDICode[0],4);///数据标识
	LibPub_MemCopyBytes(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_PA0],&GA_ucOperCode[0],4);///操作者代码
	if  (Gstr_UartComm[v_ucChID].ucCommAddrType == F_COMMADDRTYPE_ID)	/* 全地址相等才可以操作 */
	{  
		if (GStr_Flag.ucRunState2&F_RUN_INTAUTH_MACNumErrFlag )		///*安全认证标识挂起就不允许执行了*///
		{
			*((ushort16 *)(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA]) )= 0x0001;///*安全认证错误*///
			V_ucErrorType = API_DLT645_SAFE_CERT_ERR;
		}
		else
		{
			for ( i = 0; i < 4; i++ )
			{
				V_ucDI[i] = Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+i];
				V_ulDI0DI1DI2DI3 |= (((ulong32)V_ucDI[i])<<(8*i));
			}
			if( 0x070000EE == V_ulDI0DI1DI2DI3)	///身份认证(自扩数据标识，蓝牙身份认证返回信息)
			{
				if((Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN]) != 32)
				{
					*((ushort16 *)(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA])) = 0x0100;
					V_ucErrorType = API_DLT645_SAFE_CERT_ERR;
				}
				else
				{
					V_ucErrorType = PrepaymentModule_Comm_INTAUTH(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0]); 
					if( V_ucErrorType == C_OK)	///*身份认证成功*///
					{
						///上一次购电记录
						V_Temp=GStr_EventValidPiont.uc_Point[C_BuyMoney];///上一次购电记录的指针
						V_Temp1=CAddr_SelfMoney_Lenth;///上一次购电记录的长度
						Hal_ReadEEPROM(V_ucTempData,CAddr_SelfMoney_Note+V_Temp*V_Temp1,V_Temp1);////读取购电记录
						LibPub_Inverse( &V_ucTempData[0], 2 );///上一次购电后购电总次数
						LibPub_Inverse( &V_ucTempData[2], 4 );///上一次购电金额
						LibPub_Inverse( &V_ucTempData[6], 4 );///上一次购电前剩余金额
						LibPub_Inverse( &V_ucTempData[10], 4 );///上一次购电后剩余金额
						LibPub_Inverse( &V_ucTempData[14], 4 );///上一次购电后总购电金额		  

						///表内剩余金额
						LibPub_MemExchangeBytes(&GStr_Money.ucaRemainMoney[0], &V_ucTempData[18], 0x04 );	
		
						///表内透支金额
						LibPub_MemExchangeBytes(GStr_Money.ucaTickMoney, &V_ucTempData[22], 0x04 );	

						///合闸允许金额
						LibPub_MemExchangeBytes(GStr_MoneyPara.ucaAllowcloseMoney, &V_ucTempData[26], 0x04 );

						///囤积金额限值
						LibPub_MemExchangeBytes(GStr_MoneyPara.ucaMaxMoneyLimit, &V_ucTempData[30], 0x04 );	
						
						///当前总电量
						LibPub_MemExchangeBytes(&GStr_Energy.ucaFw_Energy[0], &V_ucTempData[34], 0x04 );			

						///状态字3
						V_usStateFlag3=ApiDLT645_GetStatusFlag3();
						V_ucTempData[38] = (uchar8)V_usStateFlag3;
						V_ucTempData[39] = (uchar8)(V_usStateFlag3>>8);
						GStr_Flag.ucRunState3|=F_RUN_READ_RANDOM2;///置读取随机数标志.
						GStr_Monitor.ulReadRandom2DelayTime = LibPub_GetTimerBeat();///读随机数2后取系统时间
						///置五分钟 
						LibPub_MemCopyBytes( V_ucTempData, &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+16], 40);	
						Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = 40+16;
						V_ucErrorType = 0x11;
					}
					else
					{
 						V_ucErrorType = API_DLT645_SAFE_CERT_ERR;
						Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA]= GU_SecurityErr.BYTE[0];
						Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+1]= GU_SecurityErr.BYTE[1];	///*错误返回错误信息字*///
					}
				}
			}
			else if( 0x070102EE == V_ulDI0DI1DI2DI3)	///充值(自扩数据标识，蓝牙充值返回信息)
			{
				if((Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN]) != 30)
				{
					*((ushort16 *)(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_R])) = 0x0100;
					V_ucErrorType = API_DLT645_SAFE_CERT_ERR;
					Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = 6;///*返回数据的长度，包含了4个字节的标识码*///							
				}
				else
				{
					V_ucErrorType = PrepaymentModule_Comm_OpenAccout(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0]);  
					V_ucTempData[0] = V_ucErrorType;
					V_ucTempData[1] = 0x00;
					///当前总电量4字节 
					LibPub_MemExchangeBytes(&GStr_Energy.ucaFw_Energy[0], &V_ucTempData[2], 0x04 );

					///总购电金额4字节
					LibPub_MemExchangeBytes(&GStr_PRICE.ucaPurchaseMoneyAll[0], &V_ucTempData[6], 0x04 );

					///购电次数4字节
					LibPub_MemExchangeBytes(&GStr_PRICE.ucPurchaseTimes[0], &V_ucTempData[10], 0x04 );

					///表内剩余金额4字节
					LibPub_MemExchangeBytes(&GStr_Money.ucaRemainMoney[0], &V_ucTempData[14], 0x04 );

					///表内透支金额4字节
					LibPub_MemExchangeBytes(GStr_Money.ucaTickMoney, &V_ucTempData[18], 0x04 );

					///状态字3 2字节
					//V_usStateFlag3=ApiDLT645_GetStatusFlag3();
					V_ucTempData[22]=(uchar8)ApiDLT645_GetStatusFlag3();
					V_ucTempData[23]=(uchar8)(ApiDLT645_GetStatusFlag3()>>8);

					LibPub_MemCopyBytes( V_ucTempData, &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_R], 24);	

					Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN] = 28;///*返回数据的长度，包含了4个字节的标识码*///							
				}			
			}
		}
	}
	else
	{
		V_ucErrorType = 0x80;
	}
	return(V_ucErrorType);
}


///**********************************************************************///
///* Brief: 修改密码                                              *///
///*                                                                    *///
///* Param:  v_ucChID：通道                                             */// 
///*                                                                    *///
///* Return: 返回处理结果                     					        *///
///*                                                                    *///
///* Note:   修改及其他说明                                              *///
///**********************************************************************///
uchar8 ApiDLT645_ModifyPsw(uchar8  v_ucChID )
{
	uchar8	V_ucErrorType;
	uchar8	i,V_ucTempBuff[11];
  	uchar8	V_ucaPasswordDI0[3]={0x01,0x02,0x03};	///*只支持修改00、01、02*///
	V_ucErrorType = API_DLT645_COMM_ERR_NOAUTH;

	if  (Gstr_UartComm[v_ucChID].ucCommAddrType == F_COMMADDRTYPE_ID)	/* 全地址相等才可以操作 */
	{
			if( (Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_LEN]== 12)&&(LibPub_CheckPassword(&(Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_PA0]))==_SUCCESS) ) 
			{
					if((Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+3]==0x04)&&(Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+2]==0x00)&&(Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+1]==0x0c))
					{
							for(i=0;i<3;i++)
							{
									if(Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0]==V_ucaPasswordDI0[i])
									{
											if( (Gstr_UartComm[v_ucChID].ucaCommTXBuff[22]==(V_ucaPasswordDI0[i])-1) && (Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_PA0]<=(V_ucaPasswordDI0[i])-1) )
											{
													if(_SUCCESS==LibPub_ReadDataFromE2prom(LIB_E2P_Password, 0, V_ucTempBuff))
													{
															LibPub_MemCopyBytes(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[23], &V_ucTempBuff[i*3], 3);
														
															if(_SUCCESS==LibPub_WriteDataToE2prom(LIB_E2P_Password,0,  V_ucTempBuff))
															{
																	LibPub_MemCopyBytes(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[22],&Gstr_UartComm[v_ucChID].ucaCommTXBuff[14],4);
																	V_ucErrorType=API_DLT645_COMM_WR_OK;
															}
												} 
										}
										break;
								}
							}
					}
			}
	}
	else
	{
			V_ucErrorType = API_DLT645_COMM_ERR_NOACK;
	}

	return(V_ucErrorType);
}


///**********************************************************************///
///* Brief: 获取状态字3	  只支持BIT15开户状态、 BIt13身份认证有效、BIT12保电                                           *///
///*                            BIT9BIT8电表类型、bit6继电器命令状态、                                        *///
///* Param:                                        */// 
///*                                                                    *///
///* Return:                   					        *///
///*                                                                    *///
///* Note:                                               *///
///**********************************************************************///
ushort16 ApiDLT645_GetStatusFlag3(void)
{
	ushort16 V_usResult=0;
	/*未开户*/
	if(!(GStr_Flag.ucRunState2&F_RUN_OpenAccoutFlag))
	{
		V_usResult|=_BIT15;  ///未开户状态置1
	}
	/*身份认证有效*/
	if(GStr_Flag.ucRunState2&F_RUN_INTAUTHAvailabilityFlag)
	{
		V_usResult|=_BIT13;  ///身份认证有效置1
	}
	/*保电*/
	if(GStr_Flag.ucRunState&F_RUN_KEEP_ELEC)
	{
		V_usResult|=_BIT12;  ///保电置1
	}
	/*一级报警*/
	if(GStr_Flag.ucRunState1&F_RUN_L1_ALRAM)	
	{
		V_usResult|=_BIT11;		/*一级报警置1*/
	}
	/*二级报警*/
	if(GStr_Flag.ucRunState1&F_RUN_L2_ALRAM)
	{
		V_usResult|=_BIT10;		/*二级报警置1*/
	}
	
	V_usResult|=_BIT9;  ///BIT9、BIt8为10  电费型预付费表
	
	/*继电器状态为跳闸状态*/
	if(GStr_Flag.ucRunState2&F_RUN_RELAY_STATE)
	{
		V_usResult|=_BIT4;  ///跳闸置1
	}
	/*密钥状态为私钥*/
	if(GStr_Flag.ucRunState2&F_RUN_EsamKeyFlag)
	{
		V_usResult|=_BIT3;  ///私钥置1
	}
	/*透支超透支门限*/
	if(GStr_Flag.ucRunState&F_RUN_OVER_DRAFTRELAY)
	{
		V_usResult|=_BIT2;  ///透支超透支门限置1
	}
	/*通信跳闸*/
	if(GStr_Flag.ucRunState&F_RUN_COMM_RELAYOFF)
	{
		V_usResult|=_BIT1;  ///跳闸置1
	}
	
	  return V_usResult;
}
