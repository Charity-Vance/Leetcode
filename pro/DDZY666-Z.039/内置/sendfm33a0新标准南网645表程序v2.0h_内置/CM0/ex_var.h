//定义全局函数及其变量主要标注为extern

#ifndef __EX_VAR_H__
#define __EX_VAR_H__
#include "define4.h"

#if(1 == CHINT_Mode)
extern const unsigned char ecode C_ucSoftVerForFactory[];   //内部版本号
#endif

extern const float ecode const_KL;
extern const float ecode const_KH;
extern const float ecode const_xtl_top;
extern const float ecode const_TmpsL;
extern const float ecode const_TmpsH;
extern const uint08 ecode constF_Volt;
extern const uint16 ecode const_adc_TrimB;
extern const uint16 ecode const_adc_TrimT;
extern const uint16 ecode const_KHKL_TrimRange;
extern const float ecode const_T_OffsetRun;
extern const float ecode const_T_OffsetSlp;
extern const uint08 ecode const_TopNoTrim;
extern const uint08 ecode const_TopNTRange;
extern const float ecode const_T_CL;
extern const float ecode const_T_CH;
extern const uint08 ecode const_C_Mode;
extern const int16 ecode const_TR_LSTART;
extern const int16 ecode const_TR_HSTART;
extern const uint08 ecode const_TR_GAP;
extern const uint08 ecode const_TR_Mode;
extern const uint08 ecode RTC_Trim_Ctrl;

extern const uint16 ecode BPS_SPBRGL1[];
extern const struct HisEvent_STR ecode EventTable[];

extern const uint08 ecode clkmode;
extern const uint32 ecode rchfcfgreg;
extern const uint32 ecode runwdtcon;
extern const uint08 ecode rtcosccfg;
extern const uint32 ecode SleepBorCfg;
extern const uint32 ecode SleepPdrCfg;
extern const uint32 ecode RunBorCfg;
extern const uint32 ecode RunPdrCfg;
extern const uint08 ecode Compile_LvdLvCfg;
extern const uint32 ecode Runet1Outcnt;
extern const uint08 ecode Runrtctmls;

extern const uint08 ecode Relay_Mode;
extern const uint08 ecode Correction_Mode;
extern const uint08 ecode Compile_Polar_485;
extern const uint08 ecode FlashPowerOff_Ctrl;
extern const uint08 ecode EsamPowerOff_Ctrl;
extern const uint08 ecode Memoryerr_Ctrl;	
extern const uint08 ecode Wwdt_Lcd_Ctrl;
extern const uint32 ecode IRDutyCycleCfg;
extern const uint08 ecode SleepPtatOffsetCfg;
extern const uint08 ecode Extbattery;
extern const uint08 ecode ExtVoltage;
extern const uint16 code MaxRecNum[];
extern const uint08 ecode Def_Erase_Times;
extern const uint08 code LoadOffset[max_casecount];
extern const uint08 code LoadLen[max_casecount];

extern const unsigned char ecode Verdate[24];
extern const unsigned char ecode RatedVolt[6];
extern const unsigned char ecode RatedCurr[6];
extern const unsigned char ecode MaxCurr[6];
extern const unsigned char ecode MinCurr[6];
extern const unsigned char ecode TrtCurr[6];
extern const unsigned char ecode ActiveClass[4];
extern const unsigned char ecode ReActiveClass[4];
extern const unsigned char ecode MaterType[32];
extern const unsigned char ecode Facdate[10];
extern const unsigned char ecode ProtocolVer[16];
extern const unsigned char ecode SoftwareVer1[32];
extern const unsigned char ecode HardwareVer1[32];
extern const unsigned char ecode FactoryNum[32];
extern const unsigned char ecode Softbk[8];
extern const unsigned char ecode DispVer[3];
extern const unsigned long ecode Def_Meterconst_Bcd;
extern const unsigned char ecode Def_Meterconst_Hex;
extern const unsigned char ecode Def_Plusevalidtimer;

extern const unsigned char ecode resetworking_timer_delay;
extern const unsigned short ecode Zb_Comm_Timer_delay;
extern const unsigned char ecode Bps_9600;
extern const unsigned short ecode Mod_Comm_Timer_delay1;
extern const unsigned char ecode Mod_Comm_Timer_delay2;

extern const uint08 ecode Relaytimer_Delay_N;
extern const uint08 ecode Relaytimer_Delay_W;
extern const uint08 ecode Defaultspacetimer;
extern const uint08 ecode Defrelayerrorcnt_s;
extern const uint08 ecode Defrelayerrorcount;
extern const uint08 ecode Defrelayerrorcount_r;

extern const uint08 ecode Def_Dl_Difference;
extern const uint08 ecode Def_Plusefiltertimer;
extern const uint08 ecode Def_Plusefiltertimer2;
extern const uint08 ecode Adjclk_timer_delay_s;
extern const uint08 ecode Adjclk_timer_delay;
extern const uint16 ecode Defendenergyvoltage;
extern const uint08 ecode Def_Shielding_I1;
extern const uint08 ecode Def_Shielding_I2;
extern const uint08 ecode Def_Shielding_Cos;
extern const uint08 ecode Defcurrovercount;
extern const uint16 ecode Defaultpdvoltage;
extern const uint08 ecode Defaultpddelay;
extern const uint08 ecode Deflowvoltagecount_s;
extern const uint08 ecode Deflowvoltagecount;
extern const int16 ecode Uoffset;
extern const uint08 ecode Def_Powerdetcnt2;
extern const uint08 ecode ht7017_mclk;
extern const uint32 ecode Def_SelfHeat_I;
extern const uint08 ecode Def_SelfHeat_Cancel;
extern const uint32 ecode Def_Device_Id;

extern const uint08 ecode Fulllcdbias;
extern const uint08 ecode Runlcdbias;
extern const uint08 ecode RunlLCDSET;
extern const uint08 ecode RunlLCDDRV;
extern const uint08 ecode Sleeplcdfreq;
extern const uint08 ecode SleepLCDSET;
extern const uint08 ecode SleepLCDDRV;
extern const uint16 ecode Sleepvthreshold[];
extern const uint08 ecode Sleeplcdbias[];
extern const uint08 ecode def_powerdown_timer;
extern const uint08 ecode def_meterrun_timer;
extern const uint08 ecode def_coverdelaytimer;

extern const uint16 ecode Defaultauthtimer;
extern const uint08 ecode Defaultstartup;
extern const uint16 ecode Defaultpdcurrent;
extern const uint08 ecode MAX_PSW_NUM;
extern const uint08 ecode Defpassworderrcnt;
extern const uint16 ecode Def_Vthreshold;
extern const uint16 ecode Def_Vthreshold_H;
extern const uint16 ecode Def_Relay_ActL;
extern const uint16 ecode Def_Relay_ActH;
extern const uint16 ecode Def_Relay_Det;

extern const unsigned long ecode disp_table[];
extern const unsigned char ecode Def_Limitmenory_table[];
extern const unsigned char ecode Def_DisplayPara_table[];
extern const unsigned char ecode Def_SleepDisplayPara_table[8];
extern const unsigned short ecode Def_Sleepdisp_table[16];
extern const unsigned char ecode Def_featureword_table[];
extern const unsigned char ecode Def_weekloadpara_table[];
extern const unsigned char ecode Def_vollmtpara_table[];
extern const unsigned char ecode Def_feik_table[];
extern const unsigned short ecode Def_Autodisp_table[31];
extern const unsigned short ecode Def_Keydisp_table[62];

extern const unsigned char ecode Def_Password3_table[];
extern const unsigned char ecode Def_Password4_table[];
extern const unsigned char ecode Def_histroyparameter_table[];
extern const unsigned char ecode Def_freezeparameter_table[];
extern const unsigned char ecode Def_sqb_table1[];
extern const unsigned char ecode Def_sqb_table2[];
extern const unsigned char ecode Def_sdb_table1[];
extern const unsigned char ecode Def_sdb_table2[];
extern const unsigned char ecode Def_sdb_table2[];
extern const unsigned char ecode Def_jtshiqu_table[];
extern const unsigned char ecode Def_jtshiqu_table2[];

//---------------------- bit variable ------------------------------------------------------------------------
extern 	B08_Bit bdata			Meter_Status_S;			//(改变需要保存)
#define	Meter_Status			Meter_Status_S.B08
#define	commmodule_open_flag  		Meter_Status_S.Bit.bit0		//通信模块拔出状态标志
#define	commmodule_failed_flag		Meter_Status_S.Bit.bit1		//通信模块通讯失败标志
#define	lower_v_event_flag		Meter_Status_S.Bit.bit2		//低电压事件标志
#define	high_v_event_flag		Meter_Status_S.Bit.bit3		//高电压事件标志
#define	low_voltage_flag		Meter_Status_S.Bit.bit4		//电池低压标志
#define	change_batt_flag		Meter_Status_S.Bit.bit5		//允许电池更换标志
#define	relay_success2_flag		Meter_Status_S.Bit.bit6		//继电器操作成功标志
#define	relay_commu_close2_flag		Meter_Status_S.Bit.bit7		//保电解除标志(南网新增)

extern 	B08_Bit bdata			Meter_Status1_S;		//(改变需要保存)
#define	Meter_Status1			Meter_Status1_S.B08
#define	relay_status_flag		Meter_Status1_S.Bit.bit0	//继电器状态(0表示闭合1表示断开)
#define	relay_commu_alarm_flag		Meter_Status1_S.Bit.bit4	//通讯报警继电器
#define	relay_commu_open_flag		Meter_Status1_S.Bit.bit5	//通讯断开继电器
#define relay_commu_disable_close_flag	Meter_Status1_S.Bit.bit6	//不允许闭合继电器标志
#define	relay_commu_close_flag		Meter_Status1_S.Bit.bit7	//通讯闭合继电器

extern 	B08_Bit bdata			Meter_Status2_S;		//(改变需要保存)
#define	Meter_Status2			Meter_Status2_S.B08
#define	relay_success_flag		Meter_Status2_S.Bit.bit0	//继电器操作成功标志
#define	relay_failed_flag		Meter_Status2_S.Bit.bit1	//继电器错误标志(上报)
#define	relay_commu_open_1a_flag	Meter_Status2_S.Bit.bit2	//通讯跳闸命令标志
#define	relay_commu_open_1d_flag	Meter_Status2_S.Bit.bit3	//通讯预跳闸命令标志
#define	relay_commu_open_1e_flag	Meter_Status2_S.Bit.bit4	//通讯预跳闸命令标志
#define	relay_cleardl_flag		Meter_Status2_S.Bit.bit5	//外置表清零标志
#define	commmodule_start_flag		Meter_Status2_S.Bit.bit7	//通信模块更换首次启动标志

extern 	B08_Bit bdata			System_Status_S;		//(停电不清)
#define	System_Status			System_Status_S.B08
#define	real_relaystatus_flag		System_Status_S.Bit.bit0	//继电器实际状态标志
#define	clock_error			System_Status_S.Bit.bit2	//时钟错误标志
#define	esam_error			System_Status_S.Bit.bit4	//esam错误标志
#define	eeprom_error_flag		System_Status_S.Bit.bit5	//存储器故障标志
#define	hangup_comm_flag		System_Status_S.Bit.bit6	//挂起通讯标志
#define	already_setclock_flag		System_Status_S.Bit.bit7	//已经校时标志

extern 	B08_Bit bdata			System_Status1_S;		//
#define	System_Status1			System_Status1_S.B08
#define	identity_prog_flag		System_Status1_S.Bit.bit0	//认证编程标志
#define identity_ir_flag		System_Status1_S.Bit.bit1	//红外请求标志
#define	display_zaibo_flag		System_Status1_S.Bit.bit2	//显示载波标志
#define	display_ble_flag		System_Status1_S.Bit.bit3	//显示蓝牙标志
#define	first_prog_flag			System_Status1_S.Bit.bit4	//首次编程标志
#define	progenable			System_Status1_S.Bit.bit5	//编程使能
#define	comm_relaystatus_flag		System_Status1_S.Bit.bit6	//继电器实际状态标志(通讯专用)
#define	relay_error			System_Status1_S.Bit.bit7	//继电器错误标志

extern 	B08_Bit bdata			System_Status2_S;		//
#define	System_Status2			System_Status2_S.B08
#define	esam_biaohao_flag		System_Status2_S.Bit.bit0	//已采用esam表号标志
#define	display_rtc_flag		System_Status2_S.Bit.bit1	//显示时间标志
#define	disp_0_flag			System_Status2_S.Bit.bit2	//需要灭零处理标志
#define	freeze_display_flag		System_Status2_S.Bit.bit3	//结算日电量显示标志
#define	below_60u_flag			System_Status2_S.Bit.bit4	//低于60%电压标志
#define	below_70u_flag			System_Status2_S.Bit.bit5	//低于70%电压标志
#define	relay_direct_flag		System_Status2_S.Bit.bit6	//继电器直接动作标志
#define	relay_delay_flag		System_Status2_S.Bit.bit7	//大电流延时跳闸标志

extern 	B08_Bit bdata			System_Status3_S;
#define	System_Status3			System_Status3_S.B08
#define	run_freeze_flag			System_Status3_S.Bit.bit3	//冻结和结算标志
#define	run_loadchk_flag		System_Status3_S.Bit.bit4	//负荷记录标志
#define	run_timezone_flag		System_Status3_S.Bit.bit5	//时区时段表标志
#define	run_price_flag			System_Status3_S.Bit.bit6	//电价更新标志
#define	run_alarm_flag			System_Status3_S.Bit.bit7	//报警状态标志

extern 	B08_Bit bdata			System_Status4_S;
#define	System_Status4			System_Status4_S.B08
#define	fwdl_veri_flag			System_Status4_S.Bit.bit0	//正向电量校验标志
#define	bkdl_veri_flag			System_Status4_S.Bit.bit1	//反向电量校验标志
#define	rpdl_veri_flag			System_Status4_S.Bit.bit2	//无功电量校验标志
#define	mode_veri_flag			System_Status4_S.Bit.bit3	//特征模式字校验标志
#define	addr_veri_flag			System_Status4_S.Bit.bit4	//通信地址校验标志
#define	disppm_veri_flag		System_Status4_S.Bit.bit5	//显示参数校验标志
#define	dispitem_veri_flag		System_Status4_S.Bit.bit6	//显示项目校验标志
#define	temperpara_veri_flag		System_Status4_S.Bit.bit7	//温度系数校验标志

extern 	B08_Bit bdata			System_Status5_S;
#define System_Status5			System_Status5_S.B08
#define	month_change_flag		System_Status5_S.Bit.bit0	//月改变标志
#define	year_change_flag		System_Status5_S.Bit.bit1	//年改变标志
#define	year_change_flag2		System_Status5_S.Bit.bit2	//年改变标志(仅用于高低压事件)

extern	B08_Bit	bdata			AT7051_Flag_S;
#define AT7051_Flag			AT7051_Flag_S.B08
#define read_back_flag			AT7051_Flag_S.Bit.bit0		//读反向电量标志
#define	init_7051_flag1			AT7051_Flag_S.Bit.bit1		//初始化AT7051标志1
#define	read_uip_flag1			AT7051_Flag_S.Bit.bit2		//读AT7051瞬时值标志1
#define	check_7051_flag1		AT7051_Flag_S.Bit.bit3		//校验AT7051调教值标志1
#define	load_over_flag			AT7051_Flag_S.Bit.bit4		//过流标志
#define	over_xxx_flag			AT7051_Flag_S.Bit.bit5		//拉闸电流超标志
#define	power_zero_flag			AT7051_Flag_S.Bit.bit6		//功率等于0标志
#define	ble_inter_flag			AT7051_Flag_S.Bit.bit7		//蓝牙内部命令标志

extern B08_Bit bdata			AT7051_Flag2_S;	
#define AT7017_Flag			AT7051_Flag2_S.B08
#define	dln_back_flag		        AT7051_Flag2_S.Bit.bit0		//零线电流反向标志
#define	nline_err_flag		        AT7051_Flag2_S.Bit.bit1		//零线电流异常标志
#define	dl_back_flag			AT7051_Flag2_S.Bit.bit2		//电量反向
#define	dl_back_flag2			AT7051_Flag2_S.Bit.bit3		//电流反向标志2(标志1和标志2结合确定四象限无功)
#define	lost_v_flag			AT7051_Flag2_S.Bit.bit4		//失压标志
#define	lower_v_flag			AT7051_Flag2_S.Bit.bit5		//低电压标志
#define	high_v_flag			AT7051_Flag2_S.Bit.bit6		//高电压标志
#define	cal_err_flag		        AT7051_Flag2_S.Bit.bit7		//计量故障标志

//;=============================< IDATA 存储定义 >================================
extern 	uint08			idata	run_readrtc_flag;		//读取实时时钟标志
extern 	uint08			idata	run_display_flag;		//刷新LCD显示标志
extern 	uint08			idata	run_relaychk_flag;		//继电器检测标志
extern 	uint08			idata	reg_veri_flag;			//寄存器校验标志
extern 	uint08			bdata	DisKeySamp;			//显示按键去抖寄存器
extern 	uint08			bdata	Uart1KeySamp;			//485极性检测去抖寄存器
extern 	uint08			idata	VectorTimer;			//毫秒定时器
extern 	struct 	SYS_CLOCK_FRM	idata	Sclock;				//时钟数据
extern 	uint08			idata	Key_Status;			//密钥状态,00表示全部公钥,01表示全部私钥,FF表有公有私

//;=============================< XDATA 存储定义 >================================
extern NoInit_t 			NoInit;
#define	Progkey				NoInit.Progkey			//240min编程(停电运行)
#define	Cover				NoInit.Cover			//开盖参数(停电保存) 
#define Mac_Err_Times			NoInit.Mac_Err_Times		//MAC校验失败次数
#define	G_Clockerr_Times		NoInit.G_Clockerr_Times		//明文广播校时记录故障次数
#define System_St_Bk			NoInit.System_St_Bk		//系统状态字备份(停电运行)
#define Report_Data			NoInit.Report_Data		//有效上报状态字
#define Report_Data2			NoInit.Report_Data2		//有效上报状态字备份
#define Report_Num			NoInit.Report_Num		//事件上报新增次数
#define RReport_Status			NoInit.RReport_Status		//之前已读上报状态允许复位上报状态
#define	Meter_Run_Timer4		NoInit.Meter_Run_Timer4		//
#define Reset_Rep_Timer			NoInit.Reset_Rep_Timer		//复位上报状态字定时器
#define	Password_Err			NoInit.Password_Err		//密码错误次数
#define	Load				NoInit.Load			//负荷指针共22字节
#define	Meter_Run_Timer1		NoInit.Meter_Run_Timer1		//
#define	Meter_Run_Timer2		NoInit.Meter_Run_Timer2		//	
#define	Wr_Ext_Number			NoInit.Wr_Ext_Number		//内部扩展命令写ee允许次数
#define	Fwdl		  		NoInit.Fwdl			//正向脉冲数					
#define	Bkdl		  		NoInit.Bkdl			//反向脉冲数
#define	Rpdl				NoInit.Rpdl			//四象限无功脉冲数
#define	RAMREG0				NoInit.RAMREG0			//定义特殊寄存器
#define	RAMREG1				NoInit.RAMREG1			//
#define	RAMREG2				NoInit.RAMREG2			//
#define	RAMREG3				NoInit.RAMREG3			//
#define	RAMREG4				NoInit.RAMREG4			//
#define	RAMREG5				NoInit.RAMREG5			//
#define	RAMREG6				NoInit.RAMREG6			//
#define	RAMREG7				NoInit.RAMREG7			//
#define	RAMREG8				NoInit.RAMREG8			//
#define	RAMREG9				NoInit.RAMREG9			//
#define	RAMREG10			NoInit.RAMREG10			//
#define	RAMREG11			NoInit.RAMREG11			//
#define	RAMREG12			NoInit.RAMREG12			//
#define	RAMREG13			NoInit.RAMREG13			//
#define	RAMREG14			NoInit.RAMREG14			//
#define	RAMREG15			NoInit.RAMREG15			//
#define	RAMBUF				NoInit.RAMBUF			//

extern 	uint08			near	Outputtype;	//0-秒脉冲,1-需量,2-时段投切信号,0x50-FOUT输出
extern 	struct  TIMER_FRM	near	Successled,Shiduanctrl,Relayctrl;
extern 	struct  TMR_STS_FRM	near	Adcctrl;
extern 	uint16			near	Lcdled;//背光定时器
extern 	uint32			near	Identitytimer;	//安全认证定时器
extern 	uint32			near	IR_EnTimer;	//红外认证定时器
extern 	uint32			near	Opendelaytimer;	//跳闸延时定时器
extern 	uint32			near	CurrentTimer;	//超拉闸电流定时器
extern 	uint08			near	Relayerror_Count,Relayerror_Count1,Relayerror_Count2;//继电器错误计数器
extern 	uint08			near	Relay_Space_Timer;//上电延时控制继电器定时器
extern 	uint08			near	Keyclose_timer;//按键闭合继电器定时器
extern 	uint08			near	Display_Space_Timer;//红外控制显示间隔定时器
extern 	uint16		  	near	Stop_Disptimer;//停电显示时间定时
extern 	signed char		near	Temperature_Hex;//备份温度(hex码)
extern	uint16		 	near	Temperature_Adc;//当前温度ADC值(hex码)
extern	float			near	Rtcadj_Offset;//温度补偿调校值
extern	float			near	Rtcadj_Offset2;//温度补偿调校值
extern	uint08			near	RtcStopProcFlag;//停止温补标志
extern 	unsigned int		near	Hw_Lcdled_Timer;//红外点亮背光时间
extern 	uint16			near	Ext_Disp_Cnt;//扩展LCD查询命令
extern 	uint08			near	Init_Led_Timer;//点亮指示灯定时器
extern 	uint08			near	Cover_Space_Timer;//开盖延时定时器
extern 	uint08			near	RdLoadPara[CHNum][34]; //数据标识(4)+剩余记录块数(1)+后续帧序号(1)+起始地址(4)+剩余有效记录数(2)+给定时间(5)+上一次电量(16)
extern  uint08			near	PowerDetCnt0,PowerDetCnt1,PowerDetCnt2,PowerDetCnt3;//电源检测计数器
extern	uint08			near	Resetworking_Timer;//载波复位时间定时器
extern	uint08			near	Current_Over_Count;//超拉闸电流限值时间计数器
extern	uint08			near	Current_Over_Count2,Current_Over_Count3;//过流/失压持续时间计数器
extern	uint08			near	Current_Over_Count4,Current_Over_Count5;//低电压/高电压持续时间计数器(仅用于去抖)
extern	uint16			near	Current_Over_Count41,Current_Over_Count51;//低电压/高电压持续时间计数器
extern	uint08			near	Voltage_Low_Count;//低压持续时间计数器
extern	union	B32_B08		near	Loadtime;	//总过载累计时间(低3字节有效)
extern	uint08			near	Adj_Clk_Timer_S;//定时8M时钟调校定时器(计量uart专用)
extern	uint08			near	Adj_Clk_Timer;	//定时8M时钟调校定时器

extern	uint08			near	ReportList[2];	//上报对象次数和上报对象：Bit[1:0]=停电, Bit[3:2]=上电, Bit[5:4]=状态
extern	uint08			near	BkupReport[2];	//上报标志
extern	uint08			near	Meter_Run_Timer3;//上报状态字延时
extern	uint32			near	Lost_Aver_I,Lost_V_Timer;//失压期间平均电流和此次失压累计时间
extern 	uint08			near	Commmodule_Space_Timer;//通讯模块更换定时器
extern	uint16			near	Zb_Comm_Timer;	//载波通讯波特率恢复定时器
extern	uint08			near	Zbbps;		//载波通讯波特率
extern	uint16			near	Mod_Comm_Timer1;//通信模块超时定时器
extern	uint08			near	Mod_Comm_Timer2;//通信模块异常延时定时器
extern  uint08  		near	Bat_Delay_Timer;//电池欠压延时60s
extern  uint08  		near	Bat_Change_Timer;//电池更换延时定时器
extern  uint32			near 	HardFault_Flag;//HardFault标志
extern	uint08			near	Nline_Err_Count;//零线电流异常时间计数器
extern	uint08			near	Plusefiltertimer;//脉冲毫秒去抖定时器
extern	uint08			near	Plusefiltertimer2;//无功脉冲毫秒去抖定时器
extern	uint08			near	UpdateBps;	//更新波特率
extern	uint08 			near	EmuErrCnt;	//计量芯片通信错误计数器
extern  uint08			near 	FlashTimer;	//falsh电源有效延时秒定时器
extern  uint08 			near	FreezeBuf[8];	//显示结算日电量缓冲区
extern  uint32			near 	Powerd_Flag;	//掉电标志
extern  uint32 			near	DispBuf[10];	//显示缓冲区
extern	uint08			near	LoadBuf[ee_ploadrec_lenth]; //负荷记录缓冲区
extern  uint08			near	Plusevalidtimer;//无功脉冲定时器
extern  uint32			near	SleepDisp_Timer;//停电显示定时器

extern  uint16			near	Ble_CF;			//蓝牙帧序号
extern  uint08			near	Ble_Step;		//蓝牙初始化过程
extern  uint08			near  Ble_Buf[8];	//蓝牙透传命令头
extern  uint16			near	Ble_RstTimer;//蓝牙复位定时器
extern  uint08			near  Ble_Reset;	//蓝牙复位标志

extern 	struct	PARA_ESAM_FRM		near	Esam_Para;	//变比(6)＋表号(6)+客户编号(6)+身份认证时效(2)+Crc(2)
extern 	struct	PARA_DISPLAY_FRM	near	Display_Para;	//循显屏数(1)＋每屏显示时间(1)＋显示电能小数位数(1) ＋波特率(1)+ 跳闸延时时间（2）＋crc（2）
extern 	struct 	COMM_ADDRESS_FRM	near	Comm_Addr;	//通信地址(6) ＋crc（2）
extern 	struct 	STARTTIME_FRM		near	Starttime;	//两套时区表切换时间（5）＋两套日时段表切换时间（5）＋两套费率电价切换时间（5）＋两套阶梯切换时间（5）＋crc（2）
extern 	struct 	EMU_FRM			near	Emu_Para;	//增益1(2)＋相位1(1)＋增益2(2)＋相位2(1)+电流2增益(2)+速率(2)＋电压系数(4)＋电流系数(4)＋电流系数(4)＋Crc(2)
extern 	struct	PRICE_FRM		near	Price;		//当前阶梯电量（16）＋crc（2）＋当前阶梯电价（20）＋crc（2）＋当前费率电价表（16）＋crc（2）
extern 	struct 	TARIFF_FRM		near	Tariff;		//当前费率时段表（3*14）＋crc（2）
extern 	struct 	ITEM_FRM		near	Item[2];	//循环/按键显示项目（1*99）＋crc（2）
extern 	struct	UIP_FRM			near	Emu_Data;	//电压（3）+电流1（3）电流2（3）+功率1（3）+功率2（3）+功率因数（2）
extern 	struct  FUNCTION_FRM		near	Fun_Para;	//性能参数
extern 	struct	DECIMAL_FRM		near	Decimal;	//脉冲尾数数据
extern 	struct 	DISPALY_FRM		near	Display;
extern 	struct 	EEPROM_FRM		near	Eeprom;
extern 	struct 	COMMUNICATION_FRM	near	Uart[CHNum];
extern 	struct	WEEK_FRM		near	Week_Holiday;
extern 	struct	TEMPERATURE_FRM		near	Tpara;
extern 	struct 	METERCONST_FRM		near	Meter;
extern 	struct 	PARA_FEATUREWORD_FRM	near	Mode;
extern	struct	ADCDATA_FRM		near	ADCResultArr;
extern	struct	RTC_TRIM_FRM		near	RTC_RT;
extern 	struct	FEIK_FRM		near	Feik;
extern  struct  TIMER2_FRM		near  	Keeptime;	//零线电流不平衡持续时间，过流持续时间，电池欠压累计时间，掉电累计时间，电池工作时间
extern struct	VOLLMT_FRM		near	VolLimit;	//电压合格率等相关参数
extern struct	VOLPASS_FRM		near	VolStatus[2];	//电压合格率运行情况
extern struct	BLEDEVICE_FRM		near	Ble_Connect[5];	//蓝牙连接状态：A2+A3+sta+MAC[6]

//uart-u7816
extern 	unsigned char 	near	Ic_Comm_RxBuf[u7816_buf_size]	;	//7816接收缓冲区
extern 	unsigned char 	near	Ic_Comm_RxPtr			;	//7816接收指针
extern 	unsigned char 	near	Ic_Comm_TxBuf[u7816_buf_size]	;	//7816发送缓冲区
extern 	unsigned char 	near	Ic_Comm_TxPtr			;	//7816接收指针

extern  unsigned char 	near	Err_Sw12[2]			;	//暂存错误命令返回的SW1和SW2
extern 	unsigned char	near	PcRst8B[8]			;	//PC远程下发的 分散因子 8字节
extern 	unsigned char	near	PcRand[8]			;	//PC远程下发的 随机数1  8字节
extern 	unsigned char	near	EsamRst8B[8]			;	//ESAM复位信息中后8字节
extern 	unsigned char	near	EsamRand[8]			;	//ESAM 8字节随机数
extern 	unsigned char	near	Esam_Timer			;	//ESAM上电延时复位定时器

extern	RtRecord near   SynFlash; //时间回退指针
extern  MoveRec  near   MvFlash;  //记录搬移参数
extern  SynRec   near	SynEe; //同步EE记录

#if(1 == CHINT_Mode)
///*我们自己扩展的功能变量都定义到这里*///
extern 	struct	Ijtimer_FRM		near	Ijtimer_Para;
//extern  uint08 near Relay_Mode;	///*继电器模式 0x55-外置继电器表,其他-内置继电器表*///
#endif

#endif


