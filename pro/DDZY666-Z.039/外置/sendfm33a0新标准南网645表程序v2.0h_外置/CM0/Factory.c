#include "ex_var.h"
#include "ex_func.h"
#include <string.h>


#pragma push
#pragma O0
#pragma arm section rodata = "Protected"

//主频选择
#define	MAINCLOCK	8	//系统主频,单位M

//8MHz
#if( MAINCLOCK == 8 )
const uint08 ecode clkmode  = 0x01;
const uint32 ecode rchfcfgreg = RCC_RCHFCON_FSEL_8M;//RCHF中心频率8MHz
#else//16MHz
const uint08 ecode clkmode  = 0x02;
const uint32 ecode rchfcfgreg = RCC_RCHFCON_FSEL_16M;//RCHF中心频率16MHz
#endif

//寄存器配置
const uint32 ecode runwdtcon = IWDT_IWDTOVP_2s;//iwdt周期2s
const uint08 ecode rtcosccfg = RCC_XTLFIPW_450NA;//xtlf振荡器电流配置，默认450nA
const uint32 ecode SleepBorCfg = 0x00000001;//关闭BOR	
const uint32 ecode SleepPdrCfg = 0x00000007;//打开PDR 1.4V	
const uint32 ecode RunBorCfg = 0x00000002;//打开BOR 1.6V
const uint32 ecode RunPdrCfg = 0x00000007;//打开PDR 1.4V	
const uint08 ecode Compile_LvdLvCfg = ANAC_SVDCFG_SVDLVL_4_157v;//ANAC_SVDCFG_SVDLVL_4_371v;
const uint32 ecode Runet1Outcnt = 0x00000a3e;//80ms脉冲宽度输出配置寄存器(暂不支持)
const uint08 ecode Runrtctmls = RTC_FSEL_FSEL_PLL_1S;	//使能秒时标输出,负脉冲切换信号
const uint32 ecode IRDutyCycleCfg = BIT14|BIT13;//Mclk=8M时38k调制 占空比Y(73.9%) = (TZBRG[10:4]*TH)/(TZBRG+1)=(13*12)/（210+1）,经过三极管反相后变为26.1% 

//功能编译
#define RELAYTYPE 	0x55 	//0x55:外置继电器，其它:内置继电器
#if( RELAYTYPE == 0x55 )
const uint08 ecode Relay_Mode = 0x55;		//0x55-外置继电器表(最大电流修改成80A),其他-内置继电器表(最大电流修改成60A)
#else
const uint08 ecode Relay_Mode = 0x00;		//0x55-外置继电器表(最大电流修改成80A),其他-内置继电器表(最大电流修改成60A)
#endif

#if(1 == CHINT_Mode)
///*通信协议的字符含义修改，按照表的型号来。*///
//				01		//远程 内置继电器 内置电池

//				02		//本地 内置继电器 内置电池

//				03		//远程 内置继电器 外置电池

//				04		//本地 内置继电器 外置电池

//				05		//远程 外置继电器 内置电池
 
//				06		//本地 外置继电器 内置电池

//				07		//远程 外置继电器 外置电池

//				08		//本地 外置继电器 外置电池
const unsigned char ecode C_ucSoftVerForFactory[] = {
			0x11,		
			0x20,		///*程序版本号3个字符*///	
			0x99,												
			0x31,		///*线路板号5个字符*///	
			0x3F, 		///*通信方式2个字符，3F：载波、485、红外、微功率、GPRS*///										
			0x07, 		///*通信规约1个字符，02：支持DL/T645-2007*///											
			0xF0, 													
			0xFF		///*市场属性4个字符*///													
};
#endif

//其他编译
const uint08 ecode Correction_Mode = 0x55;	//0x55-开启电压补偿功能,其他-关闭(目前rn8209c和ht7017支持)
const uint08 ecode Rn8209c_Mode = 0x55;		//0x55-RN8209C开启硬件自热补偿功能,其他-关闭
const uint08 ecode Compile_Polar_485 = 0x00;	//0x55-兼容无极性485,其他-只支持有极性485
const uint08 ecode Memoryerr_Ctrl = 0x00;	//0x55-允许存储器上报,其他-禁止存储器上报(建议关闭)
const uint08 ecode FlashPowerOff_Ctrl = 0x55;	//0x55-空闲时flash电源关闭,其他-空闲时flash电源打开
const uint08 ecode EsamPowerOff_Ctrl = 0x55;	//0x55-空闲时esam电源关闭,其他-空闲时esam电源打开
const uint08 ecode Wwdt_Lcd_Ctrl = 0x00;	//0x55-HardFault_Flag引起wwdt复位特殊处理,其他-标准设计
const uint08 ecode RTC_Trim_Ctrl = 0x55;	//0x55-补偿步长0.119ppm，其它-补偿步长0.238ppm(仅404模式下可开启0.119)
const uint08 ecode SleepPtatOffsetCfg = 0x55;	//0x55-启用3V偏置(3V电源ptat偏置控制开关)，其他-关闭 
const uint08 ecode Extbattery = 0x55;		//0x55-电池外置，其他-电池内置
const uint08 ecode ExtVoltage = 0x55;		//0x55-外部掉电检测(电池外置或带dataflash表)，其他-内部掉电检测

//版本和规格
const unsigned char ecode Verdate[24] =  "NWXXXX-M02021-211009-H20";   //厂家,版本号及版本日期 
const unsigned char ecode RatedVolt[6] = "220.0V";	//额定电压
const unsigned char ecode RatedCurr[6] = "5.0A";		//额定电流/基本电流
#if( RELAYTYPE == 0x55 )
const unsigned char ecode MaxCurr[6] = "80.0A";	//最大电流
#else
const unsigned char ecode MaxCurr[6] = "60.0A";	//最大电流
#endif
const unsigned char ecode MinCurr[6]  = "0.25A";   //最小电流
const unsigned char ecode TrtCurr[6]  = "0.5A";    //转折电流
const unsigned char ecode ActiveClass[4] = "A";	//有功准确度等级
const unsigned char ecode ReActiveClass[4] = "2.0";//无功准确度等级
const unsigned char ecode MaterType[32] = "";	//电表型号
const unsigned char ecode ProtocolVer[16] = "DL/T645-2007-21";//协议版本号
const unsigned char ecode SoftwareVer1[32] = "00000000000000000000000000000000";	//厂家软件版本号
const unsigned char ecode HardwareVer1[32] = "00000000000000000000000000000000";	//厂家硬件版本号
const unsigned char ecode FactoryNum[32] = "00000000000000000000000000000000"; //厂家编号
const unsigned char ecode Softbk[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};	//软件备案号
const unsigned char ecode Facdate[10] = "";	//生产日期
#if( RELAYTYPE == 0x55 )
const unsigned long ecode Def_Meterconst_Bcd = 0x2000;	//脉冲常数默认2000
const unsigned char ecode Def_Meterconst_Hex = 20;	//脉冲常数默认2000
#else
const unsigned long ecode Def_Meterconst_Bcd = 0x2000;	//脉冲常数默认2000
const unsigned char ecode Def_Meterconst_Hex = 20;	//脉冲常数默认2000
#endif
const unsigned char ecode Def_Plusevalidtimer = 20;	//80ms脉冲宽度(同步通讯)
const unsigned char ecode resetworking_timer_delay=60;	//240ms复位载波芯片时间
const unsigned char ecode Bps_9600 = 0x20;		//默认载波通讯波特率9600
const unsigned short ecode Zb_Comm_Timer_delay = 2160;	//36h载波通讯波特率恢复定时器 
const unsigned short ecode Mod_Comm_Timer_delay1= 2160;	//36h通信模块超时定时器 
const unsigned char ecode Mod_Comm_Timer_delay2 = 5;	//5min通信模块异常延时定时器
const unsigned char ecode Def_Erase_Times = 5; 		//扇区允许重复擦除的次数

//温度曲线相关参数
const float ecode const_xtl_top	= 25.0;		//计算温度曲线使用的顶点
#if((CHINT_TemperatureMode == 1))
const float ecode const_KL	= 0.02919;		//生产温度补偿系数
const float ecode const_KH	= 0.03525;
#else
const float ecode const_KL	= 0.0300;		//电科院温度补偿系数
const float ecode const_KH	= 0.0382;
#endif
const float ecode const_TmpsL	= 5.0379;	//温度ADC斜率
const float ecode const_TmpsH	= 5.0379;
const uint08 ecode constF_Volt	= 0;		//电压补偿量(兼容新硬件电池增加二极管),3表示0.03v/10表示0.1v
const uint16 ecode const_adc_TrimB = 0x3ff;
const uint16 ecode const_adc_TrimT = 0x640;
const uint16 ecode const_KHKL_TrimRange = 36;//晶体曲线修调功能分界范围，25度±7度内使用常温修调值krh，krl，范围外使用高低温修调值kh，kl
const float ecode const_T_OffsetRun	= -3.0;	//芯片发热修正-运行用
const float ecode const_T_OffsetSlp	= -2.0;	//芯片发热修正-休眠用
const uint08 ecode const_TopNoTrim = 0x55;  //顶点±x度附近不补偿 0x55:不补偿， 0x00:正常补偿
const uint08 ecode const_TopNTRange = 8;	//顶点附近关闭自动补偿温度adc范围，±x/5.0379=温度范围
#if( NEWCLOCKADJ == 0 ) //旧标准时钟调校	
const float ecode const_T_CL	= -23.0;	//低温查表中心温度
const float ecode const_T_CH	= 62.0;		//高温查表中心温度(国网57.0)
const uint08 ecode const_C_Mode = 0x55;		//0x55:启动高低温高精度查表功能，其他，仅开启常温高精度查表
#else
const uint16 ecode const_adc_Min  = 900; 	//温度adc最小有效值
#endif

//继电器相关
const uint08 ecode Relaytimer_Delay_N = 30;	//120ms内置继电器电平延时
const uint08 ecode Relaytimer_Delay_W = 98;	//400ms外置置继电器电平延时
const uint08 ecode Defaultspacetimer = 5;	//默认预跳闸间隔时间(5min)
const uint08 ecode Defrelayerrorcnt_s = 0;	//继电器检测显示去抖开始次数
const uint08 ecode Defrelayerrorcount = 3;	//继电器检测显示去抖次数(每次0.5s)
const uint08 ecode Defrelayerrorcount_r = 10;	//继电器检测故障记录去抖次数(每次0.5s)

//energy
const uint08 ecode Def_Dl_Difference = 100;	//总脉冲数-各费率脉冲值的允许最大差值,默认100个脉冲
const uint08 ecode Def_Plusefiltertimer = 6;	//20ms脉冲软件滤波(为0表示仅支持硬件滤波)
const uint08 ecode Def_Plusefiltertimer2 = 6;	//20ms脉冲软件滤波(为0表示仅支持硬件滤波)(无功)
const uint08 ecode Adjclk_timer_delay_s = 90;	//无计量通讯90s后启动8M时钟调校功能,如果为0则关闭定时8M时钟调校功能
const uint08 ecode Adjclk_timer_delay =  6;	//无通讯6h后启动8M时钟调校功能,如果为0则关闭定时8M时钟调校功能
const uint16 ecode Defendenergyvoltage = 0;	//如果为0x1250表示125v关闭计量,如果为0则禁止关闭计量(建议设置成0)
const uint08 ecode Def_Shielding_I1 = 0x15;	//允许火线清零最大值15mA
const uint08 ecode Def_Shielding_I2 = 0x20;	//允许零线清零最大值20mA
const uint08 ecode Def_Shielding_Cos = 0x50;	//允许功率因数置位最小值0.05
const uint08 ecode Defcurrovercount = 3;	//拉闸电流判断超过限制去抖时间
const uint16 ecode Defaultpdvoltage = 0x1320;	//默认掉电电压值(60%Un)
const uint08 ecode Defaultpddelay = 3;		//掉电去抖时间，默认3s
const uint08 ecode Deflowvoltagecount_s = 1;	//默认掉电记录上电去抖时间
const uint08 ecode Deflowvoltagecount = 3;	//默认掉电记录上电去抖时间(或者高于60%去抖时间)
const int16  ecode Uoffset = 0;			//默认电压系数偏移量
const uint08 ecode Def_Powerdetcnt2 = 11;	//低于170v在8s以内才进行电源异常检测,上电默认低于170v约11s
const uint08 ecode ht7017_mclk = 2;		//ht7017主频:1表示1M,2表示2M (2M时上位机下发的hfconst也需要*2)
const uint32 ecode Def_SelfHeat_I = 0x59000; 	//自热补偿电流默认值：59A
const uint08 ecode Def_SelfHeat_Cancel = 60; 	//电流低于自热补偿电流最多60s后，才退出补偿
const uint32 ecode Def_Device_Id = 0x7f820900;	//目前仅支持rn8208c芯片的定义用于故障判断

//interrupt
const uint08 ecode Fulllcdbias = 0x06;		//全屏显示偏置电压
const uint08 ecode Runlcdbias = 0x04;		//运行液晶显示偏置电压
const uint08 ecode RunlLCDSET 	= B0001_0001;//1/3bias， A波形， 6com
const uint08 ecode RunlLCDDRV 	= B0000_0001;//电流最大，片内电阻驱动
const uint08 ecode Sleeplcdfreq = 54;		//25Hz@6com;	
const uint08 ecode SleepLCDSET = B0001_0101;//1/3bias， B波形， 6com
const uint08 ecode SleepLCDDRV = B0000_0011;//电流次大，片内电阻驱动
const uint16 ecode Sleepvthreshold[6] = {0x540,0x600,0x680,0x760,0x840,0x920};//停电液晶显示电压台阶,定义0x600表示3.00v
const uint08 ecode Sleeplcdbias[6] = {0x0f,0x0e,0x0d,0x0b,0x08,0x05};//停电液晶显示偏置电压(按照3v液晶配置)
const uint08 ecode def_powerdown_timer = 2+1; //停电上报默认运行总时间(表在检测到掉电后每秒发一次,发送3次),单位秒
const uint08 ecode def_meterrun_timer = 60;//电表上电运行时间,单位分钟(如果不足1小时停止停电和上电上报)
const uint08 ecode def_coverdelaytimer = 3;//默认开盖去抖时间

//其他
const uint16 ecode Defaultauthtimer = 0x30;	//默认身份认证时效(30min)
const uint08 ecode Defaultstartup = 0x00;	//默认启动时间全0x00或者全0x99
const uint08 ecode MAX_PSW_NUM = 32;		//最大密钥数默认32条
const uint08 ecode Defpassworderrcnt = 5;	//密码错误5次闭锁
const uint16 ecode Def_Vthreshold = 0x300;	//电池欠压阀值,定义0x300表示3.00v
const uint16 ecode Def_Vthreshold_H = 0x340;	//电池欠压恢复阀值,定义0x340表示3.40v
const uint16 ecode Def_Relay_ActL = 0x1500;	//继电器动作电压阈值L
const uint16 ecode Def_Relay_ActH = 0x2750;	//继电器动作电压阈值H
const uint16 ecode Def_Relay_Det = 0x1500;	//继电器检测电压阈值

//lcd
const unsigned long ecode disp_table[disp_num]=
{
	//0x200/0x800＋1~169：	当前及上12月组合电量
	//0x200/0x800＋170：	当前及上12月正向电量
	//0x200/0x800＋339：	当前及上12月反向电量
	//0x200/0x800＋508：	当前及上12月组合无功1电量
	//0x200/0x800＋677：	当前及上12月组合无功2电量
	//0x200/0x800＋846：	当前及上12月第一象限无功电量
	//0x200/0x800＋1015：	当前及上12月第二象限无功电量
	//0x200/0x800＋1184：	当前及上12月第三象限无功电量
	//0x200/0x800＋1353：	当前及上12月第四象限无功电量
	0xffffffff,		//全显200
	0x00000c00,		//本月用电量201
	0x01000c00,		//上月用电量202
	0x03070004,		//485通信波特率
	0x00010102,		//电压(A相)204
	0x00010202,		//电流(A相)205
	0x00000302,		//功率(总)206
	0x00010302,		//功率(A相)207
	0x00000602,		//功率因数(总)208	
	0x00010602,		//功率因数(A相)209
	0x01008002,		//零线电流210
	0x09040004,		//常数211
	0x010b0004,		//第1结算日212
	0x020b0004,		//第2结算日213
	0x030b0004,		//第3结算日214
	0x0e040004,		//户号低215
	0x0e040004,		//户号高216
	0x02040004,		//表号低217
	0x02040004,		//表号高218
	0x01040004,		//通讯地址低219
	0x01040004,		//通讯地址高220
	0x01010004,		//日期221
	0x02010004,		//时间222
	0x01003003,		//最近一次编程日期223
	0x01003003,		//最近一次编程时间224
	0x01013003,		//最近一次清零日期225
	0x01013003,		//最近一次清零时间226
	0x00000d00,		//当前年用电量227
	0x01000d00,		//上次年用电量228
	0xcccccccc,		//预留229
	0x02008002,		//频率230
	0x00000402,		//无功功率(总)231
	0x00010402,		//无功功率(A相)232
	0x00007000,		//当前组合电量(高精度)233
	0x00007100,		//当前正向电量(高精度)234
	0x00007200,		//当前反向电量(高精度)235
	0x00007300,		//当前组合无功1电量(高精度)236
	0x00007400,		//当前组合无功2电量(高精度)237
	0x00007500,		//当前组合第一象限无功电量(高精度)238
	0x00007600,		//当前组合第二象限无功电量(高精度)239
	0x00007700,		//当前组合第三象限无功电量(高精度)240
	0x00007800,		//当前组合第四象限无功电量(高精度)241
};


//factory
const unsigned char ecode  Def_Limitmenory_table[]=
{
	0x00,0x00,0x10,0x00,		//透支金额限值xxxxxx.xx
	0x00,0x20,0x00,0x00,		//囤积金额限值xxxxxx.xx
	0x00,0x00,0x02,0x00,		//合闸允许金额限值xxxxxx.xx
};

const unsigned char ecode Def_DisplayPara_table[ee_displaypara_lenth]=
{
	7,			//自动循环显示屏数
	5, 			//每屏显示时间    
	2, 			//显示电能小数位数
	4, 			//显示功率小数位数
	25,			//按键循环显示屏数
	0,			//预留
	0,			//预留
	5,			//上电全显5s   
	0x13,0x01,0x01,0x00,0x00,//负荷记录起始时间(年月日时分)
	0x00,0x15,		//第1~5类负荷记录间隔时间	
	0x00,0x15,
	0x00,0x15,
	0x00,0x15, 
	0x00,0x15, 
	0x00,0x15,		//组合有功费率电能负荷记录间隔时间  
	0x00,0x15, 
	0x00,0x15,    
};

const unsigned char ecode Def_SleepDisplayPara_table[8]=	//停电显示参数
{
	4,	//自动循环显示屏数
	5, 	//每屏显示时间    
	2, 	//显示电能小数位数
	4, 	//显示功率小数位数
	4,	//按键循环显示屏数
	0,	//预留
	0,	//预留
	5,	//上电全显5s   
};

const unsigned short ecode Def_Sleepdisp_table[16]=	//停电显示项
{    
	0x2AA,	 // 正向有功总电量
	0x353,	 // 反向有功总电量
	215,	 // 户号低8位
	216,	 // 户号高4位
	1,	 // 预留5
	1,	 // 预留6      
	1,	 // 预留7      
	1,	 // 预留8      
	1,	 // 预留9
	1,	 // 预留10      
	1,	 // 预留11      
	1,	 // 预留12      
	1,	 // 预留13      
	1,	 // 预留14      
	1,	 // 预留15      
	1,	 // 预留16     
};


const unsigned char ecode Def_featureword_table[]=
{
	0x20,		//通信口1 波特率特征字	04000703	20H（9600bps）        
	0x05,		//有功组合方式特征字	04000601	05H（正向有功+反向有功)
	0,0,0,0, 	//预留4字节
	0x03,		//停电事件判断延时(bcd码) 默认3s
	0x60,		//主动上报上报时限(bcd码) 默认60min
	0x08,		//电表运行特征字1,04为启用后续帧,08为启用主动上报
	0xbb,		//上报模式字1/除内卡初始化错误	
	0x04,		//上报模式字2/开盖
	0x00,		//上报模式字3/null
	0x00,		//上报模式字4/null
	0x20,		//上报模式字5/掉电
	0x00,		//上报模式字6/null
	0x00,		//上报模式字7/null
	0x00,		//上报模式字8/null
	0x03,0x00,0x00,	//继电器拉闸控制电流门限值(XXX.XXX)
	0x00,0x00,  	//跳闸延时时间(bcd码)
	0x14,0x40,	//大电流拉闸延时(bcd码)
	0x30,		//红外认证(bcd码)
	0x30,		//上报复位延时(bcd码)
	0x00,		//内置继电器0x55表示自动合闸,外置继电器0x55表示手动合闸
	0x80,		//扩展模式字,bit7=1允许复位载波(主要针对瑞斯康载波),bit2=1红外遥控器点亮背光,bit1=1欠压点亮背光,bit0=1反向点亮背光
	0x41,		//无功组合方式特征字1	04000602	1+4
	0x14,		//无功组合方式特征字2	04000603	2+3
	0x20,		//通信口3 波特率特征字	04000705	20H（9600bps） (载波) 
	0x00,		//预留
};


const unsigned char ecode Def_weekloadpara_table[]=
{
	0x7F,				//周休日特征字7F（周六、周日无休息）
	0x01,				//周休日采用的日时段表号1（第一套第1日时段表）
	0x01,0x1f,			//负荷模式字
	0x00,0x83,			//定时冻结数据模式字（定时冻结正向有功电能、反向有功电能、组合无功1、组合无功2、四象限无功、变量）
	0x00,0x83,			//瞬时冻结数据模式字（瞬时冻结正向有功电能、反向有功电能、组合无功1、组合无功2、四象限无功、变量）
	0x00,0x83,			//约定冻结数据模式字（约定冻结正向有功电能、反向有功电能、组合无功1、组合无功2、四象限无功、变量）
	0x00,0x03,			//整点冻结数据模式字（整点冻结正向有功总电能、反向有功总电能） 
	0x00,0x83,			//日冻结数据模式字（日冻结正向有功电能、反向有功电能、组合无功1、组合无功2、四象限无功、变量）
	0x00,0x83,			//月冻结数据模式字（月冻结正向有功电能、反向有功电能、组合无功1、组合无功2、四象限无功、变量）
	0x00,				//预留1字节
#if(RELAYTYPE == 0x55)
	0x09,0x60,   			//过流触发下限1.2Imax,96.0A
#else
	0x07,0x20,   			//过流触发下限1.2Imax,72.0A
#endif
	0x60,				//过流延时时间,60s   
	0x00,0x01,0x00,0x00,		//电流触发下限,1.0A NNNN.NNNN(698协议)(20%Ib)
	0x50, 0x00, 			//零线电流不平衡限值, 50.00%
	0x60,         			//零线电流延时, 60s       
};


//电压合格率参数
const unsigned char ecode Def_vollmtpara_table[]=
{
	0x23, 0x54,			//电压上限值   107%Un = 235.4V
	0x19, 0x80,			//电压下限值    90%Un = 198.0V
	0x26, 0x40,			//电压考核上限 120%Un = 264.0V
	0x15, 0x40,			//电压考核下限  70%Un = 154.0V
	
	0x17, 0x16,			//失压事件电压触发上限   78%Un = 171.6V
	0x18, 0x70,			//失压事件电压恢复下限    85%Un = 187.0V
	0x00,0x00,0x02,0x50,		//失压事件电流触发下限,25mA NNNN.NNNN(698协议)(0.5%Ib)
	0x60,         			//失压事件延时判定时间, 60s 
	
	0x19, 0x80,			//低电压事件电压触发上限    90%Un = 198.0V
	0x06, 0x00,			//低电压事件延时判定时间, 10h = 600min
	0x23, 0x54,			//高电压事件事件延时判定时间   107%Un = 235.4V
	0x12, 0x00,			//高电压事件延时判定时间, 20h = 1200min
	
	0x60,				//计量故障判定延时,默认60s
};

//循环显示默认支持31项初始化,如果超过不能修改表格实现,只能通讯设置实现
const unsigned short ecode Def_Autodisp_table[31]=
{    
	221, 	// 日期
	222, 	// 时间
	0x201,	// 组合总电量
	0x54E,	// 当前第一象限无功总电量
	0x5F7,	// 当前第二象限无功总电量
	0x6A0,	// 当前第三象限无功总电量
	0x749,	// 当前第四象限无功总电量
	0x201,	// 预留8
	0x201,	// 预留9
	0x201,	// 预留10      
	0x201,	// 预留11      
	0x201,	// 预留12      
	0x201,	// 预留13      
	0x201,	// 预留14      
	0x201,	// 预留15      
	0x201,	// 预留16 
	0x201,	// 预留17
	0x201,	// 预留18
	0x201,	// 预留19
	0x201,	// 预留20
	0x201,	// 预留21
	0x201,	// 预留22
	0x201,	// 预留23
	0x201,	// 预留24
	0x201,	// 预留25
	0x201,	// 预留26
	0x201,	// 预留27
	0x201,	// 预留28
	0x201,	// 预留29
	0x201,	// 预留30
	0x201,	// 预留31     
};

//按键显示默认支持62项初始化,如果超过不能修改表格实现,只能通讯设置实现
const unsigned short ecode Def_Keydisp_table[62]=
{
	219, 	// 通讯地址低8位    
	220, 	// 通讯地址高4位
	221, 	// 日期             
	222, 	// 时间 
	204, 	// 电压
	205, 	// 电流
	207, 	// 功率A相
	232, 	// 无率A相
	209, 	// 功率因数A相  
	215, 	// 户号低8位
	216, 	// 户号高4位
	0x201,	// 显示组合总电量
	0x202,	// 显示组合尖电量
	0x203,	// 显示组合峰电量
	0x204,	// 显示组合平电量
	0x205,	// 显示组合谷电量
	0x54E,	// 当前第一象限无功总电量
	0x5F7,	// 当前第二象限无功总电量
	0x6A0,	// 当前第三象限无功总电量
	0x749,	// 当前第四象限无功总电量
	0x20E,	// 显示组合总电量  上1月
	0x20F,	// 显示组合尖电量  上1月
	0x210,	// 显示组合峰电量  上1月
	0x211,	// 显示组合平电量  上1月
	0x212,	// 显示组合谷电量  上1月
	0x201,	// 预留26
	0x201,	// 预留27
	0x201,	// 预留28
	0x201,	// 预留29
	0x201,	// 预留30
	0x201,	// 预留31
	0x201,	// 预留32
	0x201,	// 预留33
	0x201,	// 预留34
	0x201,	// 预留35
	0x201,	// 预留36
	0x201,	// 预留37
	0x201,	// 预留38
	0x201,	// 预留39
	0x201,	// 预留40
	0x201,	// 预留41
	0x201,	// 预留42
	0x201,	// 预留43
	0x201,	// 预留44
	0x201,	// 预留45
	0x201,	// 预留46
	0x201,	// 预留47
	0x201,	// 预留48
	0x201,	// 预留49
	0x201,	// 预留50
	0x201,	// 预留51
	0x201,	// 预留52
	0x201,	// 预留53
	0x201,	// 预留54
	0x201,	// 预留55
	0x201,	// 预留56
	0x201,	// 预留57
	0x201,	// 预留58
	0x201,	// 预留59
	0x201,	// 预留60
	0x201,	// 预留61
	0x201,	// 预留62  
};

const unsigned char ecode Def_freezeparameter_table[]=
{
	0x10,0x01,0x01,0x00,0x00,	//整点冻结起始时间	10年01月01日00时00分
	0x60,				//整点冻结时间间隔	60分钟
	0x00,0x00,			//日冻结时间		00时00分
	0x99,0x99,0x12,0x00,		//定时冻结时间		12时00分
};

const unsigned char ecode Def_feik_table[]=
{
	0x02,  //年时区数	2                                               
	0x02,  //日时段表数	2                                               
	0x08,  //日时段数 	8                                               
	0x04,  //费率数	4                                               
	0x00,  //公共假日数	0（不启用，启用时至少可设置1～14日公共假日参数）
	0x00,  //谐波分析次数	0                                               
	0x02,  //阶梯数	2        
	0x11,	//密钥允许设置的条数                                
};

//冻结日
const unsigned char ecode Def_histroyparameter_table[]=
{
	0x00,0x01,	//01日00点
	0x99,0x99,
	0x99,0x99,
};

//密码
const unsigned char ecode Def_Password3_table[]=
{
	0x03,0x00,0x00,0x33,
};

const unsigned char ecode Def_Password4_table[]=
{
	0x04,0x11,0x11,0x11,
};

//时区表1
const unsigned char ecode Def_sqb_table1[]=
{
	0x01,0x22,0x06,	   //时段表号、日、月
	0x02,0x28,0x12,	   //时段表号、日、月
	0x02,0x28,0x12,	   //时段表号、日、月
	0x02,0x28,0x12,	   //时段表号、日、月
	0x02,0x28,0x12,	   //时段表号、日、月
	0x02,0x28,0x12,	   //时段表号、日、月
	0x02,0x28,0x12,	   //时段表号、日、月
	0x02,0x28,0x12,	   //时段表号、日、月
	0x02,0x28,0x12,	   //时段表号、日、月
	0x02,0x28,0x12,	   //时段表号、日、月
	0x02,0x28,0x12,	   //时段表号、日、月
	0x02,0x28,0x12,	   //时段表号、日、月
	0x02,0x28,0x12,	   //时段表号、日、月
	0x02,0x28,0x12,	   //时段表号、日、月
};

//时区表2
const unsigned char ecode Def_sqb_table2[]=
{
	0x01,0x22,0x06,	   //时段表号、日、月
	0x02,0x28,0x12,	   //时段表号、日、月
	0x02,0x28,0x12,	   //时段表号、日、月
	0x02,0x28,0x12,	   //时段表号、日、月
	0x02,0x28,0x12,	   //时段表号、日、月
	0x02,0x28,0x12,	   //时段表号、日、月
	0x02,0x28,0x12,	   //时段表号、日、月
	0x02,0x28,0x12,	   //时段表号、日、月
	0x02,0x28,0x12,	   //时段表号、日、月
	0x02,0x28,0x12,	   //时段表号、日、月
	0x02,0x28,0x12,	   //时段表号、日、月
	0x02,0x28,0x12,	   //时段表号、日、月
	0x02,0x28,0x12,	   //时段表号、日、月
	0x02,0x28,0x12,	   //时段表号、日、月
};


//时段表1
const unsigned char ecode Def_sdb_table1[]=
{										//费率号,分,时,最多14个
	0x01,0x00,0x00,        
	0x02,0x00,0x08,
	0x03,0x00,0x16,
	0x03,0x00,0x16,
	0x03,0x00,0x16,
	0x03,0x00,0x16,
	0x03,0x00,0x16,
	0x03,0x00,0x16,
	0x03,0x00,0x16,
	0x03,0x00,0x16,
	0x03,0x00,0x16,
	0x03,0x00,0x16,
	0x03,0x00,0x16,
	0x03,0x00,0x16,
};

//时段表2
const unsigned char ecode Def_sdb_table2[]=
{										//费率号,分,时,最多14个
	0x01,0x00,0x00,        
	0x02,0x00,0x06,
	0x03,0x00,0x12,
	0x04,0x00,0x18,
	0x04,0x00,0x18,
	0x04,0x00,0x18,
	0x04,0x00,0x18,
	0x04,0x00,0x18,
	0x04,0x00,0x18,
	0x04,0x00,0x18,
	0x04,0x00,0x18,
	0x04,0x00,0x18,
	0x04,0x00,0x18,
	0x04,0x00,0x18,
};

//当前阶梯时区表
const unsigned char ecode Def_jtshiqu_table[]=
{										//阶梯表张号+日+月
	0x01,0x01,0x01,        
	0x02,0x01,0x05,
	0x01,0x01,0x11,
	0x01,0x01,0x11,
};

//备用阶梯时区表
const unsigned char ecode Def_jtshiqu_table2[]=
{										//阶梯表张号+日+月
	0x01,0x01,0x01,        
	0x02,0x01,0x05,
	0x01,0x01,0x11,
	0x01,0x01,0x11,
};
#pragma arm section 
#pragma pop


