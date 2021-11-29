/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    RamDefine.h                                                                        
**** Brief:       系统变量定义头文件                                                                    
**** Author:      peter.he@chint.com                                                                 
**** Version:     V1.0                                                                               
**** Date:        2019年3月14日                                                                         
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

#ifndef   RAMDEFINE_H
#define   RAMDEFINE_H

/*-------------------------------- H文件使用说明 -------------------------------------------------------*/
/*
 *  该文件宏定义的前缀为:
 *
 */

 
/*----------------< 包含文件 >----------------------------------*/


/*----------------< 宏定义区 >----------------------------------*/
#define C_OK	                 0		
#define C_ERR                  1			
/*----------------< 变量声明 >----------------------------------*/
/* g_Flag：主要是表的各种状态*/
// GStr_Flag.System  
#define F_PWON                  _BIT0			///* 上电标志，没有则为掉电 *///
#define F_PWOFF_NOW				_BIT1			///* 正在掉电，中断里置起，检测LVDIN1的电压 *///
#define	F_PWRUN					_BIT2			///* 已经上电运行过 *///

// GStr_Flag.ucMeterMode  
#define	F_FACTORY_MODE			_BIT0			///* 工厂模式（非工厂模式就是用户模式） */// 
// #define	F_FACTORY_MODE_HDIJ		_BIT1			///* 表示硬件I_J已经短接 *///

// GStr_Flag.PwOnState  

// GStr_Flag.ucMeasure
#define F_CE_UPDATA				_BIT0			///* 每s更新计量数据，如瞬时量 *///

// GStr_Flag.ucTOU
#define	F_SEC_UPDATA			_BIT0			///* 秒变化标志   *///
#define	F_MIN_UPDATA			_BIT1			///* 分钟变化标志 *///
#define	F_HOUR_UPDATA			_BIT2			///* 小时变化标志 *///
#define	F_DAY_UPDATA			_BIT3			///* 天变化标志   *///
#define	F_DATE_TIME_UPDATA		_BIT4			///* 时钟更新标志 *///

// GStr_Flag.ucDisp
#define	F_DISP_UPDATA			_BIT0			///* 显示刷新标志 *///
#define	F_DISP_DISPALL			_BIT1			///* 上电全显标志 *///
#define	F_DISP_AUTODISP			_BIT2			///* 自动循环显示 *///
#define	F_DISP_KEYDISP			_BIT3			///* 按键循环显示 *///
#define	F_DISP_DISPVER			_BIT4			///* 厂内显示版本号 *///
#define	F_DISP_COM_DIASP		_BIT5			///* 通信查看 *///

// GStr_Flag.ucDispKey
#define	F_KEY_ACKTION_DOWN		_BIT0			///* 按键按下动作 *///
#define	F_KEY_STATUS_TRUE		_BIT1			///* 按键状态为完整状态 *///
#define	F_KEY_STATUS_IDLE		_BIT2			///* 按键状态为空闲状态 *///

// GStr_Flag.ucRunState    改变需存EE
#define	F_RUN_KEEP_ELEC		    		_BIT0			///* 保电*///
#define	F_RUN_COMM_RELAYOFF				_BIT1			///* 通信跳闸 *///
#define	F_RUN_CLOSE_L2      			_BIT2			///* 二级报警合闸*///  需存EE
#define	F_RUN_CLOSE_ZERO     			_BIT3			///* 过零合闸*///  需存EE
#define F_RUN_DISABLE_CLOSE	 			_BIT4          ///* 不允许合闸标志   过透支金额限值
#define	F_RUN_OVER_DRAFTRELAY    	    _BIT5			///* 透支超透支门限*///
#define	F_RUN_RELAY_STATE_EE    	    _BIT6			///* 继电器状态*///  需存EE  1为跳闸

// GStr_Flag.ucRunState2    
#define F_RUN_OpenAccoutFlag            _BIT0           ///* 开户状态		1为开户
#define F_RUN_EsamKeyFlag               _BIT1           ///* 密钥状态状态  1为私钥
#define	F_RUN_INTAUTH_MACNumErrFlag     _BIT2	        ///身份认证挂起
#define	F_RUN_INTAUTHAvailabilityFlag   _BIT3	        ///身份认证有效标志
#define F_RUN_FirstProgFlag             _BIT4           ///首次编程标志
#define	F_RUN_RELAY_STATE     			_BIT5			///* 继电器状态*///  需存EE  1为跳闸
#define	F_RUN_Current_State    			_BIT6			///* 走字状态，配合跳闸状态判断跳闸是否成功
#define F_RUN_PROG_10MIN_FLAG           _BIT7           ///一次编程记录10min计时标志



// GStr_Flag.ucRunState1  
#define	F_RUN_L1_ALRAM	     	        _BIT0			///* 一级报警*///
#define	F_RUN_L2_ALRAM	     	        _BIT1			///* 二级报警*///
#define	F_RUN_REMAIND_ZERO              _BIT2			///* 剩余电量为0*///
#define	F_RUN_OVER_DRAFT    	        _BIT3			///* 透支*///
//#define	F_RUN_OVER_DRAFTRELAY    	    _BIT4			///* 透支超透支门限*///
#define	F_RUN_OVER_DEMAND     	        _BIT5			///* 过载*///  
#define	F_RUN_POWER_REVERSE             _BIT6			///* 功率反向*///
#define	F_RUN_OVER_DEMAND_CLOSE   		_BIT7			///* 过载跳闸后，需自动合闸标志

// GStr_Flag.ucRunState3
#define	F_RUN_LowVoltage	     	    _BIT0			///* 低于75%Un标志*///
#define	F_RUN_READ_RANDOM2     	    	_BIT1			///* 读取随机数标志*///

#if(METER_TYPE==METER_TYPE_DTSY666)	
#define	F_RUN_Relayact_Voltage	     	_BIT2			///* 高于%Un标志,用于判断三相表只加一相电压时是否动作的标志*///
#endif

#define F_SYS_MONEY_Money2E2	_BIT0		///* 金额存E2标志 *///
#define F_SYS_MONEY_MoneyDEC	_BIT1		///* 金额扣减标志 *///
typedef  struct                
{
    //系统运行标志
	volatile uchar8 ucSystem;				///* 系统状态标志                                  *///
    volatile uchar8 ucMeterMode;			///* 工厂模式或者用户模式（厂内模式或厂外模式）    *///
    volatile uchar8 ucPwOnState;			///* 电表上电状态（刚上电、正在上电、上电完全）    *///
	volatile uchar8 ucRunState;			    ///* 电表运行状态需存EE    *///
	volatile ushort16 usCRC16;
	volatile uchar8 ucRunState2;			    ///* 电表运行状态    *///
	volatile uchar8 ucRunState1;			    ///* 电表运行状态   *///
	volatile uchar8 ucRunState3;			    ///* 电表运行状态   *///
    //芯片硬件
//     volatile uchar8 ucRTC;					///* RTC相关                                     */// 
//     volatile uchar8 ucMeasure;				///* 计量相关标志                                  *///
    //应用程序用
//     volatile uchar8 ucTOU;					///* 定时任务相关标志 *///
    volatile uchar8 ucDisp;  				///* 显示相关标识 *///
    volatile uchar8 ucFactoryKey;           ///* 按键相关（短接点) */// 
    volatile uchar8 ucDispKey;          	 ///* 按键相关 */// 
    volatile uchar8 ucMoney;				///* 金额相关      *///
	volatile uchar8 ucPowerOnFlag;				///* 上电不初始化计量标志     *///
	volatile uchar8 ucWrE2promSafeByte;      ///*写EE安全字
//	volatile uchar8 ucRelayOnFlag;				///* 上电合闸标志     *///
	volatile uchar8 ucBLESTATFlag;      	///*蓝牙连接状态标志*///
	//volatile uchar8 ucBLERSTFlag;      		///*蓝牙模块复位标志，电表设置地址后，需返回参数后再进行设置蓝牙参数*///

}GStr_FLAG_Type;
#define	GStr_FLAG_Type_LEN		(sizeof(GStr_FLAG_Type))

///* 系统监控相关 *///
#define	FACTORY_MAX_TIME		0x0000A8C0	///* 厂内最长时间 43200min *///
#define	UIP_UPDATE_INTERVAL		1000u		///* 瞬时量更新时间，1000ms更新一次 *///
typedef   struct{
	volatile ulong32 ulTimer_ms;			///* 每毫秒中断累加,中断中使用 *///
	volatile ulong32 ulTimer_ms_old;		///* 每毫秒中断累加,中断中使用 *///
	volatile ulong32 ulTimerClrWDT;			///* 看门狗互锁定时 *///
	volatile ulong32 ulTimerMin;			///* 分钟定时 *///
	volatile ulong32 ulTimer5ms;            ///* 5ms定时
	volatile uchar8	 ucPowerOnTimer;		///* 上电定时，以1s为基准
	volatile ulong32 ulTimers;              ///* 1s定时
	volatile ulong32 ulUpDateUIPTime;		///* 瞬时量更新计时 ms为单位 *///
	volatile ulong32 ulSoftI_JTime;			///* 软件I_J时间，存E2 *///
	volatile ushort16 usSoftI_JTimeCRC16;	///* 软I_J的crc
	volatile ushort16 usPasswordErrTime[4];  /// 密码错24小时自动解锁，上电清零，1min为单位usPasswordErrTime[3]为身份认证挂起时间
	volatile uchar8	 ucCommSymbolTime;		///* 通信符号闪烁时间 以500ms为单位 *///
	volatile uchar8	 ucPowerLimitNum;       ///* 过载计数
	volatile ulong32 ulOverDemandCloseTime;	///* 过载跳闸后恢复合闸时间计数
	volatile ulong32 ulProgEventDelayTime;	///* 编程时间记录10min定时计数
	volatile ulong32 ulReadRandom2DelayTime;///* 读随机数2有效时间5min定时
	volatile uchar8	 ucBleAdvCnt;			///* 蓝牙广播分钟校验计数，用于定时起动广播，重新广播或有通信就清零
	volatile uchar8	 ucBleConnectCnt;		///* 蓝牙连接定时校验计数，用于防止误连接，收到心跳包就清零
	#if ( METER_TYPE == METER_TYPE_DTSY666 )
	volatile ulong32 ulPulsewidth;///*脉冲宽度80ms计数
	#endif	
}GStr_MONITOR_Tpye;
#define	GStr_MONITOR_Tpye_LEN	(sizeof(GStr_MONITOR_Tpye))

///* 电量相关 *///
#define F_PULSESTATU_1KWH		_BIT0		///* 整度进位 *///
#define F_PULSESTATU_Add1		_BIT1		///* 小数电量进位标志 */// 
#define F_PULSESTATU_BUSY		_BIT2		///* 脉冲电量处理中 *///

typedef  struct{
	uchar8	ucPulseAdd;						///* 脉冲增量,根据正反向标志来判断是否计入正向还是反向 *///
	uchar8	ucPulseAddBusy;					///* 处理脉冲增量时为了不清掉正在产生的脉冲，将脉冲存在这里 *///
	uchar8	ucPulseStatu;					///* 脉冲处理标志 *///

	uchar8	ucPulseDecimal;					///* 小数,按16进制存储 *///
	uchar8	ucPulseDecSavePtr;				///* 脉冲电量保存指针 *///
	uchar8	ucPulseDecSaveNoFF;				///* 脉冲电量非全FF数据 *///
	uchar8	ucaPulseRemain[2];				///* 脉冲尾数，掉电保存，带字节校验(按位取反），校验错补一半脉冲 */// 
}GStr_ENERGY_PULSE_Type;

#define	GStr_ENERGY_PULSE_Type_LEN	(sizeof(GStr_ENERGY_PULSE_Type))
 
typedef  struct{ 
	uchar8 ucaFw_Energy[4];			///* 正向电量 *///
	uchar8 ucaBk_Energy[4];			///* 反向电量 *///
	ushort16 usCRC16;
}GStr_ENERGY_Type; 
#define	GStr_ENERGY_Type_LEN	(sizeof(GStr_ENERGY_Type))

typedef  struct{ 
	uchar8 ucaFw_EnergyDec[13];		///* 正向电量小数 *///
	uchar8 ucaBk_EnergyDec[13];		///* 反向电量小数 *///
//	ushort16 usCRC16;
}GStr_ENERGYDEC_Type; 
#define	GStr_ENERGYDEC_Type_LEN	(sizeof(GStr_ENERGYDEC_Type))

///* 电能表信息 *///
typedef  struct{
	uchar8	ucaCommAddr[6];				///* 通信地址 A5A4A3A2A1A0 *///
	uchar8	ucaMeterID[6];				///* 表号 *///  
    uchar8	ucaUserID[6];				///* 客户编号 *///  	
	uchar8  ucVoltageTrans[3];///*电压互感器变比
	uchar8  ucCurrentTrans[3];///*电流互感器变比
	uchar8	ucBpsVal;					///* 波特率特征字 *///
//	uchar8	ucClrTimes[4];				///* 清零次数 *///
//	uchar8 	ucPurchaseTimes[4];		    ///* 购电次数 *///
//	uchar8 	ucProgramTimes[4];		    ///* 编程次数 *///
//	uchar8 	ucRejectMoneyTimes[4];		///* 退费次数 *///
	ushort16 usCRC16;

}GStr_METER_IFO_Type;
#define	GStr_METER_IFO_Type_LEN	(sizeof(GStr_METER_IFO_Type))

///* 显示相关参数 *///
#define	LCD_UPTATA_TIME			500		///* 显示刷新时间500ms *///
#define	LCD_DISP_DUR_TIME		5	    ///* 每屏显示时间5s *///
#define	LCD_DISP_FULL_TIME		5   	///* 全显时间5s *///
#define	LCD_DISP_COMM_TIME		60000	///* 液晶查看时间60000ms *///
#define	LCD_DISP_Key_TIME		15000	///* 按键无操作显示时间30000ms *///



typedef struct{
	uchar8		ucFullDisp_Time;			///* 全显时间 *///  5~30s可设
	uchar8		ucDispDurTime;				///* 每屏显示时间 *///5~30s可设
	uchar8      ucAutoDispNum;              ///* 循环显示屏数
	uchar8      ucKeyDispNum;	 			///* 循环显示屏数
	ushort16    usDisp_ParaCRC16;	        ///* 显示参数的CRC
	uchar8      ucAutoDisptable[30];        ///* 循环显示项
	uchar8      ucKeyDisptable[30];         ///* 按键显示项
	ushort16    usDisp_tableCRC16;	        ///* 显示参数的CRC
	
	uchar8      ucBackLightTime;            ///* 背光显示时间
	uchar8      ucRelayLEDTime;             ///* 跳闸灯显示时间
	ulong32		ulDispUpdataTime;			///* 显示刷新时间 *///
	ushort16 	usDispCnt;					///* 显示计数，可用来控制闪烁 *///
	ulong32     ulDisptimer;                ///* 液晶显示时间 500ms为计数单位
	uchar8      ucKeydelaytimer;            ///* 按键去抖时间
	uchar8      ucFirstKeyDisp;			 	///* 第一次按键循环显示标志
	uchar8      ucDisp_0_flag;				///* 灭零标志
	uchar8      ucDisp_tongxin_Flag;		///* 通信符号显示标志
	ulong32      ucDisp_tongxin_Time;		///* 通信符号显示时间5s
	uchar8      ucDispNum;	                ///* 显示序号
	uchar8      ucLCDDrvDispBuf[40];		///* 显示缓冲区 *///
}GStr_DISPLAY_PARA_Type;
#define	GStr_DISPLAY_PARA_Type_LEN	(sizeof(GStr_DISPLAY_PARA_Type))

// 通信定义
///* 通信地址类型 *///
#define	F_COMMADDRTYPE_NULL		NO_BITS
#define	F_COMMADDRTYPE_AA		_BIT0		///* 全AA *///
#define	F_COMMADDRTYPE_99		_BIT1		///* 全99 *///
#define	F_COMMADDRTYPE_ID		_BIT2		///* 全匹配 *///
#define	F_COMMADDRTYPE_SW		_BIT3		///* 缩位 *///
typedef struct{
	uchar8	ucCommChStatus;					///* 通道状态，空闲，发送，接收等状态 *///
	uchar8	ucCommRevStep;					///* 通信步骤 *///
	uchar8	ucCommRevLen;					///* 接收数据长度，主要用来接收计数 *///
	uchar8	ucCommSndLen;					///* 发送计数长度。主要用来发送计数 *///
	uchar8	ucCommSndCnt;					///* 数据发送指针 *///
	uchar8	ucCommAddrType;					///* 通信地址类型 *///
	uchar8	ucCommError;					///* 错误信息字，如果是安全认证的话，可以在扩一个字节 *///
	ulong32	ulCommTimeInit;					///* 定时初始化计时，以ms为单位 *///
	ulong32	ulCommRcvByteOverTime;			///* 字节超时，以ms为单位 *///
	ulong32	ulCommSndByteOverTime;			///* 字节超时，以ms为单位 *///
	ulong32	ulCommRspOverTime;				///* 响应超时，以ms为单位 *///
	uchar8	ucaCommRXBuff[200];				///* 通信接收缓存 *///
	uchar8	ucaCommTXBuff[200];				///* 通信发送缓存 *///
}GStr_UART_COMM_Type; 
#define GStr_UART_COMM_TypeLEN		( sizeof(GStr_UART_COMM_Type) )

typedef struct                 
{
	volatile ushort16 ucFactoryMode_Cnt;       ///* 工厂模式检测计数器 *///
	volatile ushort16 ucKeyRelayOn_Cnt;       ///* 报警按键合闸 *///
	volatile uchar8   ucRelayDelay_Cnt;       ///* 跳闸口线置位计数器 *///
	volatile uchar8   ucHoldMoney_Cnt;       ///* 定时保存剩余透支金额计数器 *///
	volatile uchar8   ucPasswordErr_Cnt[3];			///* 密码错误次数
	
	#if(METER_TYPE==METER_TYPE_DTSY666)	
	volatile uchar8   ucRelayon_Cnt;       	 ///* 合闸口线计数器，用于表认为合闸而实际未合闸情况 *///
	#endif
}GStr_COUNTER_Type;
#define GStr_COUNTER_Type_LEN    (sizeof(GStr_COUNTER_Type))

typedef struct{
	uchar8	ucaRemainMoney[6];		// 剩余金额
	uchar8	ucaTickMoney[6];		// 透支金额
	ushort16 usCRC16;				// CRC
}GStr_MONEY_Type;
#define GStr_MONEY_Type_LEN    (sizeof(GStr_MONEY_Type))

typedef struct{
	uchar8	ucaPrice[4];		// 电价
	uchar8	ucaPurchaseMoneyAll[4];		// 总购电金额
	uchar8 	ucPurchaseTimes[4];		    ///* 购电次数 *///
	ushort16 usCRC16;				// CRC
}GStr_PRICE_Type;
#define GStr_PRICE_Type_LEN    (sizeof(GStr_PRICE_Type))


typedef struct{
	uchar8	ucaAlarmMoneyL1[4];		// 1级报警金额
	uchar8	ucaAlarmMoneyL2[4];		// 2级报警金额
	uchar8	ucaMaxMoneyLimit[4];	// 囤积金额限值
	uchar8	ucaTickMoneyLimit[4];	// 透支金额限值
	uchar8	ucaAllowcloseMoney[4];	// 合闸允许金额
	uchar8	ucaOverLoadVal[3];		// 过载功率值
	ushort16 usCRC16;				// CRC
}GStr_MONEY_PARA_Type;
#define GStr_MONEY_PARA_Type_LEN    (sizeof(GStr_MONEY_PARA_Type))
 
///* 功能配置 *///
typedef struct{
	uchar8	ucFunCurrentVal;	///* 基本电流 目前暂时不用 *///
	uchar8	ucFunMeterConst;	///* 常数百分之一 *///
	uchar8	ucRes[12];			///* 预留，以免后面增加功能不兼容 *///
	ushort16 usCRC16;
}GStr_FUN_CONFIG_Type;
#define GStr_FUN_CONFIG_TypeLEN		( sizeof(GStr_FUN_CONFIG_Type) )


typedef struct{
	ushort16	us_IDAvailTimer;       //// 身份认证有效时长
	uchar8		ucBackMonFlag;          ///bit0=1 退费允许标志 =0不允许     bit1=1  已开户    =0  未开户									 ///bit2=1  正式密钥   =0 测试密钥   其他位保留
	ushort16 	usCRC16;
	
	ulong32   ulAutRemainingTime;		    ///* 身份认证有效时长剩余时间,xxxx    上电清零///
	uchar8    ucRechangeMoney[4];			          //操作金额	
	uchar8    ucBuybeforeMoney[4];			          //操作前金额	
	uchar8    ucbeforeFwEnergy[4];			          //操作前正向电量
	uchar8    ucbeforeBkEnergy[4];			          //操作前反向电量
    uchar8    ucE2Key[16]; 	                         
}GStr_AVAIL_Type;
#define GStr_AVAIL_TypeLEN		( sizeof(GStr_AVAIL_Type) )

typedef struct{
	uchar8	ucVoltage[4];       ///* 合相电压
	uchar8	ucVoltageA[4];		///* 电压 ABC,单相都一样 *///
	uchar8	ucVoltageB[4];		///* 电压 ABC,单相都一样 *///
	uchar8	ucVoltageC[4];		///* 电压 ABC,单相都一样 */// 显示使用的值 因显示需要显示2为小数

	///1位小数的小数点液晶上没有
	
	uchar8	ucCOMMVoltage[4];       ///* 合相电压	
	uchar8	ucCOMMVoltageA[4];		///* 电压 ABC,单相都一样 *///
	uchar8	ucCOMMVoltageB[4];		///* 电压 ABC,单相都一样 *///
	uchar8	ucCOMMVoltageC[4];		///* 电压 ABC,单相都一样 *///通信使用的值

	
	uchar8	ucCurrent[4];      	///* 合相电流
	uchar8	ucCurrentA[4];		///* 电流 ABC,单相都一样  *///
	uchar8	ucCurrentB[4];		///* 电流 ABC,单相都一样  *///
	uchar8	ucCurrentC[4];		///* 电流 ABC,单相都一样  *///
	
	uchar8	ucCOMMCurrent[4];      	///* 合相电流
	uchar8	ucCOMMCurrentA[4];		///* 电流 ABC,单相都一样  *///
	uchar8	ucCOMMCurrentB[4];		///* 电流 ABC,单相都一样  *///
	uchar8	ucCOMMCurrentC[4];		///* 电流 ABC,单相都一样  *///通信使用的值
	
	
	uchar8	ucPower[4];			///* 总功率 总ABC,单相都一样  *///
	uchar8	ucPowerA[4];			///* 功率 总ABC,单相都一样  *///
	uchar8	ucPowerB[4];			///* 功率 总ABC,单相都一样  *///
	uchar8	ucPowerC[4];			///* 功率 总ABC,单相都一样  *///
	
	uchar8	ucCOMMPower[4];      	///* 合相功率
	uchar8	ucCOMMPowerA[4];		///* 功率 ABC,单相都一样  *///
	uchar8	ucCOMMPowerB[4];		///* 功率 ABC,单相都一样  *///
	uchar8	ucCOMMPowerC[4];		///* 功率 ABC,单相都一样  *///通信使用的值
	
	uchar8	ucFactory[4];		///* 总功率因数 总ABC,单相都一样  */// 
	uchar8	ucFactoryA[4];		///* 功率因数 总ABC,单相都一样  */// 
	uchar8	ucFactoryB[4];		///* 功率因数 总ABC,单相都一样  */// 
	uchar8	ucFactoryC[4];		///* 功率因数 总ABC,单相都一样  */// 
	
	uchar8	ucCOMMFactory[4];      	///* 合相功率因数
	uchar8	ucCOMMFactoryA[4];		///* 功率因数 ABC,单相都一样  *///
	uchar8	ucCOMMFactoryB[4];		///* 功率因数 ABC,单相都一样  *///
	uchar8	ucCOMMFactoryC[4];		///* 功率因数 ABC,单相都一样  *///通信使用的值
	
	uchar8	ucFrequency[4];		///* 电网频率 *///
	
	uchar8	ucMeterConst[3];		///* 有功常数 *///
}GStr_UIP_DISPLAY_Type;  ///不存EE

// 瞬时量结构体（不存E2） 注意，前三个要和调校系数顺序一致
typedef struct{
	ulong32	ulVoltage[4];		///* 电压 ABC,单相都一样 *///
	ulong32	ulCurrent[4];		///* 电流 ABC,单相都一样  *///
	ulong32	ulPower[4];			///* 功率 总ABC,单相都一样  *///
	
	ulong32	ulFactory[4];		///* 功率因数 总ABC,单相都一样  */// 
	ulong32	ulFrequency;		///* 电网频率 *///
}GStr_UIP_GROUP_Type;
#define GStr_UIP_GROUP_Type_LEN		( sizeof(GStr_UIP_GROUP_Type) )
	
// 蓝牙相关参数
typedef struct{
	
	uchar8 ucBleMAC[6];			// 蓝牙Mac地址，6字节
	uchar8 ucBleName[12];		// 蓝牙名称，12字节
	uchar8 ucBleKey[3];			// 蓝牙配对码，3字节
	ushort16 usAdvTime;			// 蓝牙广播间隔,2字节
	uchar8 ucBleTPL;			// 蓝牙发射功率
//	uchar8 ucSMPLevel;			// 蓝牙配对等级
	ushort16 usCRC16;
	
}GStr_BLE_GROUP_Type;
#define GStr_BLE_GROUP_TypeLEN		( sizeof(GStr_BLE_GROUP_Type) )

//extern uchar8 ucBletargetMAC[6];			// 目标设备地址蓝牙Mac地址，6字节wxy调试设置的变量

typedef struct    	                	            	///*事件记录次数有效指针 *///
{
 uchar8     	uc_Num[6];//只支持编程、清零、购电、退费、拉闸、合闸		  
 ushort16   	usCRC16;
}GStr_EventNumPiont_Type;
#define GStr_EventNumPiont_TypeLEN		( sizeof(GStr_EventNumPiont_Type) )


typedef struct     										///* 事件记录循环指针 *///
{
 uchar8			uc_Point[6]; 		   
 ushort16		usCRC16;
}GStr_EventValidPiont_Type;

#define GStr_EventValidPiont_TypeLEN		( sizeof(GStr_EventValidPiont_Type) )

typedef struct    							        ///*事件记录总次数  *///
{
	uchar8  ucEventTimes[6][4];  ///顺序为  清零 购电 编程 退费、拉闸、合闸
	ushort16		usCRC16;
}GStr_EventRecordNum_Type;
#define GStr_EventRecordNum_TypeLEN		( sizeof(GStr_EventRecordNum_Type) )


/*----------------< 外部变量声明区 >----------------------------------*/
extern GStr_FLAG_Type				GStr_Flag;
extern GStr_ENERGY_PULSE_Type 		GStr_EnergyPulseFw,GStr_EnergyPulseBk;
extern GStr_ENERGY_Type 			GStr_Energy; 
extern GStr_MONITOR_Tpye			GStr_Monitor;
extern GStr_DISPLAY_PARA_Type		GStr_DisplayPara;
extern GStr_COUNTER_Type			GStr_Counter;
extern GStr_UART_COMM_Type			Gstr_UartComm[];
extern GStr_METER_IFO_Type			GStr_MeterIFO;
extern GStr_FUN_CONFIG_Type			GStr_FunConfigPara;
extern GStr_MONEY_PARA_Type         GStr_MoneyPara;
extern  GStr_PRICE_Type             GStr_PRICE;
extern GStr_MONEY_Type              GStr_Money;
extern GStr_ENERGYDEC_Type          GStr_ENERGYDEC;
extern GStr_AVAIL_Type              GStr_AVAIL;
///GStr_MeasurePara;
extern GStr_UIP_GROUP_Type     		GStr_UIPGroup;
extern GStr_BLE_GROUP_Type     		GStr_BLEGroup;
extern GStr_UIP_DISPLAY_Type        GStr_UIPDisplay;
extern GStr_EventNumPiont_Type      GStr_EventNumPiont;
extern GStr_EventValidPiont_Type    GStr_EventValidPiont;
extern GStr_EventRecordNum_Type     GStr_EventRecordNum;
/*----------------< 函数声明 >----------------------------------*/






#endif
