 
///*******************************************************************************************************///
///* Copyright：  (c)Copyright 2016,浙江正泰仪器仪表有限责任公司,智能电表研发一部                        *///
///*                            All rights reserved.                                                     *///
///* FileName:    LibEepromLayout.c                                                                      *///
///* Brief:       E2分布定义						                                                     */// 
///* Author:      作者                                                                                   *///
///* Version:     版本                                                                                   *///
///* Date:        日期                                                                                   *///
///*                                                                                                     *///
///* note:修改历史记录列表，每条修改记录应包括修改日期、修改者及修                                       *///
///* 1.  Author:                                                                                         *///
///*     Version:                                                                                        *///
///*     Date :                                                                                          *///
///* 2.  Author:                                                                                         *///
///*     Version:                                                                                        *///
///*     Date:                                                                                           *///
///*                                                                                                     *///
///*  addtogroup:Template                                                                                *///
///*******************************************************************************************************///

///*-------------------------------- 文件功能说明 -------------------------------------------------------*///
///*                                                                                                     *///
///*  该文件所有函数的前缀为Temp_                                                                        *///
///*  文件主函数和对外函数需放在文件的首部，并且主函数需要放在第一个位置;                                *///
///*  函数注释采用标准模板，函数内部注释采用//;                                                          *///
///*  对于注释较多的部分，可以增加一个注释符，然后详细说明放在文件的尾部;                                *///
///*                                                                                                     *///
///*-----------------------------------------------------------------------------------------------------*///


///* 注释格式均采用三斜杠加星号的方式，注释与注释符之间用空格隔开 *///
///* 代码控制均采用tab制表符（设置成占4个空格）或者直接敲4个空格  *///
///*--------------------------------- 头文件包含区 ------------------------------------------------------*///
#include "Include.h"

///*--------------------------------- 变量声明区 --------------------------------------------------------*///

const  GStr_EEPROM_MAP EEPROM_MAP_TAB[ ]={
	///* 地址索引        			具体地址                      占E2空间 		         数据长度   	       是否带CRC	  是否备份 	*///
	///* 第1页开始 0x0000地址暂时不用*///
	{ LIB_E2P_ENRGY, 				LIB_E2P_ENRGY_Addr, 	        LIB_E2P_ENRGY_Len , 		LIB_E2P_ENRGY_Len,			_TRUE, 		_TRUE,  },		///* 电能存储E2地址,正向总电能（4）+反向总电能（4）+crc */// 
	{ LIB_E2P_ENRGY_BAK, 			LIB_E2P_ENRGY_BAK_Addr, 	    LIB_E2P_ENRGY_Len, 		    LIB_E2P_ENRGY_Len,			_TRUE, 		_FALSE, },		///* 电能存储E2地址备份,正向总电能（4）+反向总电能（4）+crc */// 
	{ LIB_E2P_Money, 			    LIB_E2P_Money_Addr, 		    LIB_E2P_Money_Len, 			LIB_E2P_Money_Len,			_TRUE, 		_TRUE,  },		///* 金额存储E2地址,剩余金额（6）+透支金额（6）+crc */// 
   	{ LIB_E2P_Money_BAK, 			LIB_E2P_Money_BAK_Addr, 	    LIB_E2P_Money_Len, 			LIB_E2P_Money_Len,			_TRUE, 		_FALSE, },		///* 金额存储E2地址备份,剩余金额（6）+透支金额（6）+crc *///   
    { LIB_E2P_Price, 			    LIB_E2P_Price_Addr, 		    LIB_E2P_Price_Len, 			LIB_E2P_Price_Len,			_TRUE, 		_TRUE,  },		///* 电价存储E2地址,电价（4）+总购电金额（4）+crc */// 
   	{ LIB_E2P_Price_BAK, 			LIB_E2P_Price_BAK_Addr, 	    LIB_E2P_Price_Len, 			LIB_E2P_Price_Len,			_TRUE, 		_FALSE, },		///* 电价存储E2地址备份
	{ LIB_E2P_EMU_CALPARA, 			LIB_E2P_EMU_CALPARA_Addr, 	    LIB_E2P_EMU_CALPARA_Len, 	LIB_E2P_EMU_CALPARA_Len,	_TRUE, 		_TRUE,  },		///* 校表参数,数据+crc *///脉冲频率（4）+有功功率增益（4）+相位调校(4)+小信号调校（4）+潜动阀值（4）+CRC（2）
	{ LIB_E2P_EMU_CALPARA_BAK, 	    LIB_E2P_EMU_CALPARA_BAK_Addr, 	LIB_E2P_EMU_CALPARA_Len, 	LIB_E2P_EMU_CALPARA_Len,	_TRUE, 		_FALSE, },		///* 校表参数备份,数据+crc *///
	#if(METER_TYPE!=METER_TYPE_DTSY666)
	{ LIB_E2P_EMU_UIPKms 	,		LIB_E2P_EMU_UIPKms_Addr , 	    LIB_E2P_EMU_UIPKms_Len, 	LIB_E2P_EMU_UIPKms_Len,		_TRUE, 		_TRUE,  },		///* 瞬时量系数,数据+crc *///电压系数（4）+电流系数（4）+功率系数（4）+CRC（2）
	{ LIB_E2P_EMU_UIPKms_BAK, 	    LIB_E2P_EMU_UIPKms_BAK_Addr, 	LIB_E2P_EMU_UIPKms_Len, 	LIB_E2P_EMU_UIPKms_Len,		_TRUE, 		_FALSE, },		///* 瞬时量系数,数据+crc *///电压系数（4）+电流系数（4）+功率系数（4）+CRC（2）
	#else
	{ LIB_E2P_EMU_UIPKms 	,		LIB_E2P_EMU_UIPKms_Addr , 	    6, 							LIB_E2P_EMU_UIPKms_Len,		_TRUE, 		_TRUE,  },		///* 瞬时量系数,数据+crc *///三相表只有电流系数（4）+CRC（2）
	{ LIB_E2P_EMU_UIPKms_BAK, 	    LIB_E2P_EMU_UIPKms_BAK_Addr, 	6, 							LIB_E2P_EMU_UIPKms_Len,		_TRUE, 		_FALSE, },		///* 瞬时量系数,数据+crc *///三相表只有电流系数（4）+CRC（2）
	#endif
	{ LIB_E2P_FUN_CONFIG,			LIB_E2P_FUN_CONFIG_Addr,		LIB_E2P_FUN_CONFIG_Len,		LIB_E2P_FUN_CONFIG_Len,		_TRUE, 		_TRUE,  },		///* 功能配置：基本电流（1），常数（1）+12字节预留+CRC（2） *///
    { LIB_E2P_FUN_CONFIG_BAK,		LIB_E2P_FUN_CONFIG_BAK_Addr,	LIB_E2P_FUN_CONFIG_Len,		LIB_E2P_FUN_CONFIG_Len,		_TRUE, 		_FALSE, },		///* 功能配置备份：基本电流（1），常数（1）+12字节预留+CRC（2） */// 
	{ LIB_E2P_ENERGY_DECPULSE_FW, 	LIB_E2P_ENERGY_DECPULSE_FW_Addr, LIB_E2P_ENERGY_DECPULSE_FW_Len, 		1,			    _FALSE, 	_FALSE, },		///* 小数电量（正向），存13字节*/// 
	{ LIB_E2P_ENERGY_DECPULSE_BK, 	LIB_E2P_ENERGY_DECPULSE_BK_Addr, LIB_E2P_ENERGY_DECPULSE_BK_Len, 		1,			    _FALSE, 	_FALSE, },		///* 小数电量（正向），存13字节*/// 
    { LIB_E2P_ENERGY_DECPULSE_WS, 	LIB_E2P_ENERGY_DECPULSE_WS_Addr, LIB_E2P_ENERGY_DECPULSE_WS_Len,LIB_E2P_ENERGY_DECPULSE_WS_Len,	_FALSE, 	_FALSE, },		///* 脉冲尾数，掉电保存，正向+反向，共4字节 *///
    { LIB_E2P_RUN_STATE        , 	LIB_E2P_RUN_STATE_Addr, 	     LIB_E2P_RUN_STATE_Len, 	LIB_E2P_RUN_STATE_Len,		_TRUE, 	    _FALSE, },		///* 运行状态  1字节+CRC(2)
	{ LIB_E2P_METER_INFO, 			LIB_E2P_METER_INFO_Addr, 		 LIB_E2P_METER_INFO_Len, 	LIB_E2P_METER_INFO_Len,		_TRUE, 		_FALSE, },		///* 电表信息：通信地址(6)，表号(6)，客户编号（6），波特率特征字(1)，清零次数（4）购电次数（4）+crc(2) *///
    { LIB_E2P_Money_Para, 	        LIB_E2P_Money_Para_Addr, 		 LIB_E2P_Money_Para_Len, 	LIB_E2P_Money_Para_Len,		_TRUE, 	    _FALSE, },		///* 常用信息： 一级报警金额（4）+二级报警金额（4）+囤积金额限值（4）+透支金额限值（4）囤积金额（4）+过载功率（3）+CRC（2）*///
    { LIB_E2P_Password, 	        LIB_E2P_Password_Addr,           LIB_E2P_Password_Len, 		LIB_E2P_Password_Len,		_TRUE,      _FALSE, },		///* 00 01 02密码3字节*///
    { LIB_E2P_SecretKey, 	        LIB_E2P_SecretKey_Addr, 		 LIB_E2P_SecretKey_Len, 	LIB_E2P_SecretKey_Len,		_FALSE,     _FALSE, },		///* 密钥16字节*///
	{ LIB_E2P_SOFTI_J,				LIB_E2P_SOFTI_J_Addr,		     LIB_E2P_SOFTI_J_Len,		LIB_E2P_SOFTI_J_Len,		_TRUE, 		_FALSE, },		///* 软I_J存储地址4个数据+2CRC *///
    { LIB_E2P_AvailTimer,           LIB_E2P_AvailTimer_Addr,         LIB_E2P_AvailTimer_Len,    LIB_E2P_AvailTimer_Len,     _FALSE,     _FALSE, },      ///* 身份认证有效时长
    { LIB_E2P_EventNumPiont,        LIB_E2P_EventNumPiont_Addr,      LIB_E2P_EventNumPiont_Len, LIB_E2P_EventNumPiont_Len,  _TRUE,      _FALSE, },      ///* 事件有效指针  4+CRC（2）
	{ LIB_E2P_EventValidPiont,      LIB_E2P_EventValidPiont_Addr,    LIB_E2P_EventValidPiont_Len,LIB_E2P_EventValidPiont_Len,_TRUE,      _FALSE, },    ///* 事件循环指针  4+CRC（2）
	{ LIB_E2P_EventNum,             LIB_E2P_EventNum_Addr,           LIB_E2P_EventNum_Addr_Len, LIB_E2P_EventNum_Addr_Len ,  _TRUE,      _FALSE, },    ///* 事件次数  4*4+CRC（2）
    { LIB_E2P_Display_Para,			LIB_E2P_Display_Para_Addr,		 LIB_E2P_Display_Para_Len,	LIB_E2P_Display_Para_Len,	_TRUE, 		_FALSE, },		///* 上电全显时间（1）+每屏显示时间（1）+按键显示屏数（1）+循环显示屏数（1）+CRC（2） *///  
    { LIB_E2P_Display_Table,		LIB_E2P_Display_Table_Addr,		 LIB_E2P_Display_Table_len,	LIB_E2P_Display_Table_len,	_TRUE, 		_FALSE, },		///* 循显项（30）+键显项（30）+CRC（2）*///  
	{ LIB_E2P_BLE_PARA,				LIB_E2P_BluePara_Addr,			LIB_E2P_BluePara_Len,		LIB_E2P_BluePara_Len,		_TRUE,		_FALSE,	},    ///*?蓝牙参数（23)+crc(2)
};
///*--------------------------------- 函数声明区 --------------------------------------------------------*///


///*--------------------------------- 函数区 ------------------------------------------------------------*///

///* 有形参的函数格式:*///
///**********************************************************************///
///* Brief:  函数功能简要描述                                           *///
///* Param:  入口参数说明，一个参数占一行                               *///
///* Return: 函数返回值的说明                                           *///
///* Note:   修改及其他说明                                             *///
///**********************************************************************///


///* 无形参的函数格式: *///
///**********************************************************************///
///* Brief:  函数功能简要描述                                           *///
///* Return: 函数返回值的说明                                           *///
///* Note:   修改及其他说明                                             *///
///**********************************************************************///
//void LibEep_ReadE2Map(void)
//{
//	GStr_E2Map++;
//}




///*--------------------------------- 注释详解区 ---------------------------------------------------------*///

///* 注释1: 一些复杂的功能可以在这里注释，主要是注释上面函数的功能，如有需要可以每一个函数配一个注释详解区*///

///* 注释2: *///

///*------------------------------------------------------------------------------------------------------*///

