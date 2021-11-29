#include "FM32L0XX.h"  
#include "define4.h"
#include "stdarg.h"

const uint16 ecode BPS_SPBRGL1[9] = { 13332, 6666, 3332, 1666, 832, 417, 208, 139, 69 };		//波特率配置16M从0开始，8M从1开始
//1200,2400,4800,9600,19200,38400,57600,115200

//---------------------- bit variable --------------------
B08_Bit			bdata				Meter_Status_S;			//(改变需要保存)
B08_Bit			bdata				Meter_Status1_S;		//(改变需要保存)
B08_Bit			bdata				Meter_Status2_S;		//(改变需要保存)
B08_Bit			bdata				System_Status_S;		//(停电不清)
B08_Bit			bdata				System_Status1_S;		//(停电清零)
B08_Bit			bdata				System_Status2_S;
B08_Bit			bdata				System_Status3_S;
B08_Bit			bdata				System_Status4_S;
B08_Bit			bdata				System_Status5_S;
B08_Bit			bdata				AT7051_Flag_S;
B08_Bit			bdata				AT7051_Flag2_S;

//;=============================< IDATA 存储定义 >================================
uint08			idata	run_readrtc_flag;	//读取实时时钟标志
uint08			idata	run_display_flag;	//刷新LCD显示标志
uint08			idata	run_relaychk_flag;	//继电器检测标志
uint08			idata	reg_veri_flag;		//寄存器校验标志
uint08			bdata	DisKeySamp;		//显示按键去抖寄存器
uint08			bdata	Uart1KeySamp;		//485极性检测去抖寄存器
uint08			idata	VectorTimer;		//毫秒定时器
struct 	SYS_CLOCK_FRM	idata	Sclock;			//时钟数据
uint08			idata	Key_Status;		//密钥状态,00表示全部公钥,01表示全部私钥,FF表有公有私


#define NOINIT(x) __attribute__ ((at(x)))
#pragma push

#pragma O0
//#pragma arm section rwdata = "NotInit", zidata = "NotInit"


NoInit_t NoInit NOINIT(0x20000000);

//#pragma arm section 

#pragma pop


uint08			near 	Outputtype;	//0-秒脉冲,1-需量,2-时段投切信号,0x50-FOUT输出
struct  TIMER_FRM	near	Successled,Shiduanctrl,Relayctrl;
struct  TMR_STS_FRM	near	Adcctrl;	//adc转换时间间隔定时器
uint16			near	Lcdled;		//背光定时器
uint32			near	Identitytimer;	//安全认证定时器
uint32			near 	IR_EnTimer;	//红外认证定时器
uint32			near	Opendelaytimer;//跳闸延时定时器
uint32			near	CurrentTimer;	//超拉闸电流定时器
uint08			near	Relayerror_Count,Relayerror_Count1,Relayerror_Count2;//继电器错误计数器
uint08			near	Relay_Space_Timer;//上电延时控制继电器定时器
uint08			near	Keyclose_timer;//按键闭合继电器定时器
uint08			near	Display_Space_Timer;//红外控制显示间隔定时器
uint16			near	Stop_Disptimer;//停电显示时间定时
signed char		near	Temperature_Hex;//备份温度(hex码)
uint16	 		near	Temperature_Adc;//当前温度ADC值(hex码)
float			near	Rtcadj_Offset;//温度补偿调校值
float			near	Rtcadj_Offset2;//温度补偿调校值
uint08			near	RtcStopProcFlag;//停止温补标志
unsigned int		near	Hw_Lcdled_Timer;//红外点亮背光时间
uint16			near	Ext_Disp_Cnt;	//扩展LCD查询命令
uint08			near	Init_Led_Timer;//点亮指示灯定时器
uint08			near	Cover_Space_Timer;//开盖延时定时器
uint08			near	RdLoadPara[CHNum][34]; //数据标识(4)+剩余记录块数(1)+后续帧序号(1)+起始地址(4)+剩余有效记录数(2)+给定时间(5)+上一次电量(16)
uint08			near	PowerDetCnt0,PowerDetCnt1,PowerDetCnt2,PowerDetCnt3;	//电源检测计数器
uint08			near	Resetworking_Timer;//载波复位时间定时器
uint08			near	Current_Over_Count;//超拉闸电流限值时间计数器
uint08			near	Current_Over_Count2,Current_Over_Count3;//过流/失压持续时间计数器
uint08			near	Current_Over_Count4,Current_Over_Count5;//低电压/高电压持续时间计数器(仅用于去抖)
uint16			near	Current_Over_Count41,Current_Over_Count51;//低电压/高电压持续时间计数器
uint08			near	Voltage_Low_Count;//低压持续时间计数器
union   B32_B08		near	Loadtime;	//总过载累计时间(低3字节有效)
uint08			near	Adj_Clk_Timer_S;//定时8M时钟调校定时器(计量uart专用)
uint08			near	Adj_Clk_Timer;	//定时8M时钟调校定时器

uint08			near	ReportList[2];	//上报对象次数和上报对象：Bit[1:0]=停电, Bit[3:2]=上电, Bit[5:4]=状态
uint08			near	BkupReport[2];	//上报标志
uint08			near	Meter_Run_Timer3;//上报状态字延时
uint32			near	Lost_Aver_I,Lost_V_Timer;//失压期间平均电流和此次失压累计时间
uint08			near	Commmodule_Space_Timer;//通讯模块更换定时器
uint16			near	Zb_Comm_Timer;	//载波通讯波特率恢复定时器
uint08			near	Zbbps;		//载波通讯波特率
uint16			near	Mod_Comm_Timer1;//通信模块超时定时器
uint08			near	Mod_Comm_Timer2;//通信模块异常延时定时器
uint08  		near	Bat_Delay_Timer;//电池欠压延时60s
uint08  		near	Bat_Change_Timer;//电池更换延时定时器
uint32			near 	HardFault_Flag;//HardFault标志
uint08			near	Nline_Err_Count;//零线电流异常时间计数器
uint08			near	Plusefiltertimer;//脉冲毫秒去抖定时器
uint08			near	Plusefiltertimer2;//无功脉冲毫秒去抖定时器
uint08			near	UpdateBps;	//更新波特率
uint08 			near	EmuErrCnt;	//计量芯片通信错误计数器
uint08			near 	FlashTimer;	//falsh电源有效延时秒定时器
uint08 			near	FreezeBuf[8];	//显示结算日电量缓冲区
uint32			near 	Powerd_Flag;	//掉电标志
uint32 			near	DispBuf[10];	//显示缓冲区
uint08			near	LoadBuf[ee_ploadrec_lenth]; //负荷记录缓冲区
uint08			near	Plusevalidtimer;//无功脉冲定时器
uint32			near	SleepDisp_Timer;//停电显示定时器

uint16			near	Ble_CF;			//蓝牙帧序号
uint08			near	Ble_Step;		//蓝牙初始化过程
uint08			near  Ble_Buf[8];	//蓝牙透传命令头
uint16			near	Ble_RstTimer;//蓝牙复位定时器
uint08			near  Ble_Reset;	//蓝牙复位标志

struct	PARA_ESAM_FRM		near	Esam_Para;	//变比(6)＋表号(6)+客户编号(6)+身份认证时效(2)+Crc(2)
struct	PARA_DISPLAY_FRM	near	Display_Para;	//循显屏数(1)＋每屏显示时间(1)＋显示电能小数位数(1) ＋波特率(1)+ 跳闸延时时间（2）＋crc（2）
struct 	COMM_ADDRESS_FRM	near	Comm_Addr;	//通信地址(6) ＋crc（2）
struct 	STARTTIME_FRM		near	Starttime;	//两套时区表切换时间（5）＋两套日时段表切换时间（5）＋两套费率电价切换时间（5）＋两套阶梯切换时间（5）＋crc（2）
struct 	EMU_FRM			near	Emu_Para;	//增益1(2)＋相位1(1)＋增益2(2)＋相位2(1)+电流2增益(2)+速率(2)＋电压系数(4)＋电流系数(4)＋电流系数(4)＋Crc(2)
struct	PRICE_FRM		near	Price;		//当前阶梯电量（16）＋crc（2）＋当前阶梯电价（20）＋crc（2）＋当前费率电价表（16）＋crc（2）
struct 	TARIFF_FRM		near	Tariff;		//当前费率时段表（3*14）＋crc（2）
struct 	ITEM_FRM		near	Item[2];	//循环/按键显示项目（1*99）＋crc（2）
struct	UIP_FRM			near	Emu_Data;	//电压（3）+电流1（3）电流2（3）+功率1（3）+功率2（3）+功率因数（2）
struct  FUNCTION_FRM		near	Fun_Para;	//性能参数
struct	DECIMAL_FRM		near	Decimal;	//脉冲尾数数据
struct 	DISPALY_FRM		near	Display;
struct 	EEPROM_FRM		near	Eeprom;
struct 	COMMUNICATION_FRM	near	Uart[CHNum];
struct	WEEK_FRM		near	Week_Holiday;
struct	TEMPERATURE_FRM		near	Tpara;
struct 	METERCONST_FRM		near	Meter;
struct 	PARA_FEATUREWORD_FRM	near	Mode;
struct	ADCDATA_FRM		near	ADCResultArr;
struct	RTC_TRIM_FRM		near	RTC_RT;
struct	FEIK_FRM		near	Feik;		//年时区数+日时段表数+日时段数+费率数+公共假日数+谐波次数+阶梯数+密钥总条数+CRC(2)
struct  TIMER2_FRM		near	Keeptime;	//零线电流不平衡持续时间，过流持续时间，电池欠压累计时间，掉电累计时间，电池工作时间
struct	VOLLMT_FRM		near	VolLimit;	//电压合格率等相关参数
struct	VOLPASS_FRM		near	VolStatus[2];	//电压合格率运行情况
struct	BLEDEVICE_FRM		near	Ble_Connect[5];	//蓝牙连接状态：A2+A3+sta+MAC[6]

//uart-u7816
unsigned char 	near	Ic_Comm_RxBuf[u7816_buf_size]	;	//7816接收缓冲区
unsigned char 	near	Ic_Comm_RxPtr			;	//7816接收指针
unsigned char 	near	Ic_Comm_TxBuf[u7816_buf_size]	;	//7816发送缓冲区
unsigned char 	near	Ic_Comm_TxPtr			;	//7816接收指针

unsigned char 	near	Err_Sw12[2]			;	//暂存错误命令返回的SW1和SW2
unsigned char	near	PcRst8B[8]			;	//PC远程下发的 分散因子 8字节
unsigned char	near	PcRand[8]			;	//PC远程下发的 随机数1  8字节
unsigned char	near	EsamRst8B[8]			;	//ESAM复位信息中后8字节
unsigned char	near	EsamRand[8]			;	//ESAM 8字节随机数
unsigned char	near	Esam_Timer			;	//ESAM上电延时复位定时器

RtRecord near SynFlash; //时间回退指针
MoveRec  near MvFlash; //记录搬移参数
SynRec   near SynEe; //同步EE记录

#if(1 == CHINT_Mode)
///*我们自己扩展的功能变量都定义到这里*///
struct	Ijtimer_FRM		near	Ijtimer_Para;
//uint08 near Relay_Mode;				///*继电器模式 0x55-外置继电器表,其他-内置继电器表*///
#endif
