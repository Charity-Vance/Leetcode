
///*******************************************************************************************************///
///* Copyright：  (c)Copyright 2016,浙江正泰仪器仪表有限责任公司,智能电表研发一部                        *///
///*                            All rights reserved.                                                     *///
///* FileName:   LibEepromLayout.h                                                                       *///
///* Brief:       E2数据结构分布				                                                         */// 
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
///*******************************************************************************************************///

#ifndef   _LIBEEPROMLAYOUT_H
#define   _LIBEEPROMLAYOUT_H

///*------------------------------- H文件使用说明 -------------------------------------------------------*///
///*                                                                                                     *///
///* 该文件宏定义的前缀为:LIB_E2P_                                                                         *///
///*                                                                                                     *///
///*                                                                                                     *///

///* 注释格式均采用三斜杠加星号的方式，注释与注释符之间用空格隔开 *///
///* 代码控制均采用tab制表符（设置成占4个空格）或者直接敲4个空格  *///
///*-------------------------------- 宏定义区 -----------------------------------------------------------*///
#define LIB_E2P_ENRGY_Addr	    0x0000u
#define LIB_E2P_ENRGY_BAK_Addr	0x0100u
	#define LIB_E2P_ENRGY_Len	10    ///正向电量（4）+反向电量（4）+CRC（2）

#define LIB_E2P_Money_Addr		(LIB_E2P_ENRGY_Addr+LIB_E2P_ENRGY_Len)
#define LIB_E2P_Money_BAK_Addr	(LIB_E2P_ENRGY_BAK_Addr+LIB_E2P_ENRGY_Len)
	#define LIB_E2P_Money_Len	14   ///剩余金额（6）+透支金额（6）+CRC(2)

#define LIB_E2P_Price_Addr		(LIB_E2P_Money_Addr+LIB_E2P_Money_Len)
#define LIB_E2P_Price_BAK_Addr	(LIB_E2P_Money_BAK_Addr+LIB_E2P_Money_Len)
	#define LIB_E2P_Price_Len	14   ///电价（4）+总购电金额（4）+实际购电次数（4）+CRC(2)

#define LIB_E2P_EMU_CALPARA_Addr		(LIB_E2P_Price_Addr+LIB_E2P_Price_Len)
#define LIB_E2P_EMU_CALPARA_BAK_Addr	(LIB_E2P_Price_BAK_Addr+LIB_E2P_Price_Len)
	#define LIB_E2P_EMU_CALPARA_Len	22   ///脉冲频率（4）+有功功率增益（4）+相位调校(4)+小信号调校（4）+潜动阀值（4）+CRC（2）

#define LIB_E2P_EMU_UIPKms_Addr            (LIB_E2P_EMU_CALPARA_Addr+LIB_E2P_EMU_CALPARA_Len)
#define LIB_E2P_EMU_UIPKms_BAK_Addr         (LIB_E2P_EMU_CALPARA_BAK_Addr+LIB_E2P_EMU_CALPARA_Len)
    #define  LIB_E2P_EMU_UIPKms_Len         14   ///电压系数（4）+电流系数（4）+功率系数（4）+CRC（2）

#define LIB_E2P_FUN_CONFIG_Addr              (LIB_E2P_EMU_UIPKms_Addr+LIB_E2P_EMU_UIPKms_Len)
#define LIB_E2P_FUN_CONFIG_BAK_Addr              (LIB_E2P_EMU_UIPKms_BAK_Addr+LIB_E2P_EMU_UIPKms_Len)
    #define  LIB_E2P_FUN_CONFIG_Len  16  ///基本电流（1）+常数（1） +12字节预留+CRC（2）   

#define LIB_E2P_ENERGY_DECPULSE_FW_Addr     (LIB_E2P_FUN_CONFIG_Addr+LIB_E2P_FUN_CONFIG_Len)
   #define LIB_E2P_ENERGY_DECPULSE_FW_Len    13    ///正向电量小数
 
#define LIB_E2P_ENERGY_DECPULSE_BK_Addr     (LIB_E2P_ENERGY_DECPULSE_FW_Addr+LIB_E2P_ENERGY_DECPULSE_FW_Len)
   #define LIB_E2P_ENERGY_DECPULSE_BK_Len    13   ///反向电量小数

#define LIB_E2P_ENERGY_DECPULSE_WS_Addr      (LIB_E2P_ENERGY_DECPULSE_BK_Addr+LIB_E2P_ENERGY_DECPULSE_BK_Len)
   #define LIB_E2P_ENERGY_DECPULSE_WS_Len    4    ///尾数 正向+效验+反向+效验 

#define   LIB_E2P_RUN_STATE_Addr              (LIB_E2P_ENERGY_DECPULSE_WS_Addr+LIB_E2P_ENERGY_DECPULSE_WS_Len)
  #define   LIB_E2P_RUN_STATE_Len        3   ///运行状态字（1）+CRC（2）
 
#define  LIB_E2P_METER_INFO_Addr              (LIB_E2P_RUN_STATE_Addr+LIB_E2P_RUN_STATE_Len)
  #define  LIB_E2P_METER_INFO_Len      27   ///通信地址（6）+表号（6）+客户编号（6）+电压互感器变比（3）+电流互感器变比（3）+波特率特征字（1）+CRC（2）

#define  LIB_E2P_Money_Para_Addr              (LIB_E2P_METER_INFO_Addr+LIB_E2P_METER_INFO_Len)
  #define  LIB_E2P_Money_Para_Len      25///  一级报警金额（4）+二级报警金额（4）+囤积金额限值（4）+透支金额限值（4）囤积金额（4）+过载功率（3）+CRC（2）*///

#define LIB_E2P_Password_Addr    (LIB_E2P_Money_Para_Addr+LIB_E2P_Money_Para_Len)
  #define LIB_E2P_Password_Len        11    //////* 00 01 02密码3字节+CrC(2)*///

#define LIB_E2P_SecretKey_Addr   (LIB_E2P_Password_Addr+LIB_E2P_Password_Len)
  #define LIB_E2P_SecretKey_Len     16  ///密钥16字节

#define LIB_E2P_SOFTI_J_Addr   (LIB_E2P_SecretKey_Addr+LIB_E2P_SecretKey_Len)
  #define LIB_E2P_SOFTI_J_Len     6  ///软IJ时间（4）+CRC（2）
 
#define  LIB_E2P_AvailTimer_Addr   (LIB_E2P_SOFTI_J_Addr+LIB_E2P_SOFTI_J_Len)
  #define LIB_E2P_AvailTimer_Len    5  ///身份认证有效时长(2)+退费标志（1）+CRC（2）
  
#define  LIB_E2P_EventNumPiont_Addr    LIB_E2P_AvailTimer_Addr+LIB_E2P_AvailTimer_Len
    #define LIB_E2P_EventNumPiont_Len   8   ///* 事件有效指针  6+CRC（2）
	
#define  LIB_E2P_EventValidPiont_Addr    LIB_E2P_EventNumPiont_Addr+LIB_E2P_EventNumPiont_Len
    #define LIB_E2P_EventValidPiont_Len   8    ///* 事件循环指针  6+CRC（2）

#define  LIB_E2P_EventNum_Addr    LIB_E2P_EventValidPiont_Addr+LIB_E2P_EventValidPiont_Len
    #define LIB_E2P_EventNum_Addr_Len   26    ///* 事件次数 6*4+CRC（2）
	
	
	
	
#define  LIB_E2P_HoldFirstMoney_Addr   	LIB_E2P_FUN_CONFIG_BAK_Addr+LIB_E2P_FUN_CONFIG_Len
    #define LIB_E2P_HoldFirstMoney_Len     14           ///每分钟定时保存剩余金额和透支金额  存4处，地址紧接着其他数据的备份区
////6字节数据+两字节CRC

#define   LIB_E2P_BluePara_Addr    LIB_E2P_HoldFirstMoney_Addr+LIB_E2P_HoldFirstMoney_Len*4
     #define LIB_E2P_BluePara_Len     26 ///MAC（6）+蓝牙名称（12）+配对码（3）+广播间隔（2）+配对等级（1）+CRC（2）  
  
#define  LIB_E2P_Display_Para_Addr   LIB_E2P_BluePara_Addr+LIB_E2P_BluePara_Len
  #define  LIB_E2P_Display_Para_Len   6///* 上电全显时间（1）+每屏显示时间（1）+按键显示屏数（1）+循环显示屏数（1）+CRC（2） *///  
 
#define LIB_E2P_Display_Table_Addr (LIB_E2P_Display_Para_Addr+LIB_E2P_Display_Para_Len)
  #define LIB_E2P_Display_Table_len   62///* 循显项（30）+键显项（30）+CRC（2）*///


typedef struct{
	ushort16	ucE2pAddressIndex;	///* 地址索引 	*///
	ushort16	usE2pAddress;		///* 具体地址 	*///
	uchar8		ucE2pSize;			///* 占E2空间	*///
	uchar8		ucE2pLen;			///* 数据长度（一次读写的长度） 	*///
	uchar8		ucIsCRC;			///* 是否带CRC	*///
	uchar8		ucIsBak;			///* 是否带备份 	*///
}GStr_EEPROM_MAP;

///* 增加或删除对应E2数据时，请修改枚举和,文件中的表格 EEPROM_MAP_TAB *///
typedef enum {
	LIB_E2P_ENRGY = 0,				///* 电能存储E2地址,正向总电能（3）+反向总电能（3）+crc */// 
	LIB_E2P_ENRGY_BAK,				///* 电能存储E2地址备份,正向总电能（3）+反向总电能（3）+crc */// 
	LIB_E2P_Money,                  ///* 金额存储E2地址,剩余金额（6）+透支金额（6）+crc */// 
	LIB_E2P_Money_BAK,              ///* 金额存储E2地址备份,剩余金额（6）+透支金额（6）+电价（4）+总购电金额（6）+crc *///   
	LIB_E2P_Price,                  ///* 电价（4）+总购电金额（4）+总购电次数（4）+CRC（2）
	LIB_E2P_Price_BAK,              ///*备份
	LIB_E2P_EMU_CALPARA,			///* 校表参数,数据+crc *///
	LIB_E2P_EMU_CALPARA_BAK,		///* 校表参数备份,数据+crc *///
	LIB_E2P_EMU_UIPKms,             ///* 瞬时量系数
	LIB_E2P_EMU_UIPKms_BAK,         ///* 瞬时量系数备份
	LIB_E2P_FUN_CONFIG,             ///* 功能配置，暂时预留14字节+2CRC *//
	LIB_E2P_FUN_CONFIG_BAK,         ///* 功能配置备份，暂时预留14字节+2CRC *//
	LIB_E2P_ENERGY_DECPULSE_FW,		///* 小数电量(正向） 13字节，一次写一字节 *///
	LIB_E2P_ENERGY_DECPULSE_BK,		///* 小数电量(反向） 13字节，一次写一字节 *///
	LIB_E2P_ENERGY_DECPULSE_WS,		///* 脉冲尾数，掉电保存，正向+反向，共4字节 *///
	LIB_E2P_RUN_STATE,              ///* 运行状态  1字节+CRC
	LIB_E2P_METER_INFO,				///* 电表信息：通信地址，表号，客户编号，电压互感器变比，电流互感器变比，+crc *///
	LIB_E2P_Money_Para,             ///* 常用信息： 一级报警金额（4）+二级报警金额（4）+囤积金额限值（4）+透支金额限值（4）囤积金额+过载功率（3）+CRC（2）*///
	LIB_E2P_Password,               ///* 00级密码（3）+01级密码（3）+02级密码（3）+CRC（2）*///
	LIB_E2P_SecretKey,              ///* 密钥16字节
	LIB_E2P_SOFTI_J,				///* 软件I_J时间存储4字节+2字节crc *///	
	LIB_E2P_AvailTimer,             ///* 身份认证有效时长
	LIB_E2P_EventNumPiont,          ///* 事件有效指针  6+CRC（2）
	LIB_E2P_EventValidPiont,         ///* 事件循环指针  6+CRC（2）
	LIB_E2P_EventNum,                ///*事件次数6*4+2crc
	LIB_E2P_Display_Para,           ///* 显示参数
	LIB_E2P_Display_Table,          ///* 循显键显项 
	LIB_E2P_BLE_PARA,				///* 蓝牙参数 *///
	
	LIB_E2P_INDEX_MAX,				///* 最大索引 *///
}LIB_E2P_INDEX;

extern const  GStr_EEPROM_MAP EEPROM_MAP_TAB[ ];


///*-------------------------------- 函数声明区 ---------------------------------------------------------*///
///* 主要是申明对应.c文件里的函数 *///
//extern void LibEep_ReadE2Map(void);


#endif
