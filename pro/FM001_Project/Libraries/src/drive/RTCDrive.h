
///*****************************************************************************************///
///*Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     
///*Version:       V1
///*Date:          2014-3-12
///*Description:   
///*Function List: 
///*****************************************************************************************///
#ifndef	__RTCDrive_H
#define	__RTCDrive_H

#include "Public.h"
#include "IO.h"
#include "Timer.h"


//static ulong32	SV_RTC_SFRBuff;			///*用于SFR的读->修改->写*///


//#define	C_RTC_ERR							0x86	///*RTC故障；RTC故障上报过*///
//#define	C_RTC_OK							0x00	///*RTC正常；RTC故障未上报过*///
//#define	C_RTCERR_MeterWorkState				0x80	///*电表运行特征字1中的RTC故障位*///
#define C_RTC_Times							3		///*连续3次错误认为时钟故障发生*///
#define C_Day1000				    1000	///*1000天，时钟故障判断*///

#define C_Const_MCON01					0x2000
#define C_Const_MCON23					0x0588
#define C_Const_MCON45					0x4488
#define C_ReadRTC_Time1ms			500	

typedef struct
{
	uchar8	Timer;				///*计数器*///
	uchar8	HStatus;			///*历史状态*///
}Str_RTC_Type;

static Str_RTC_Type Str_RTC_Status;		///*RTC故障状态*///

#define	TAB_MeterSty_samp	3		///*3点校正
#define	EnWr_WPREG()		RTC->RTCWE = 0xACACACAC							//则关闭写保护功能，用户可以写操作被保护的寄存器
#define	DisWr_WPREG()		RTC->RTCWE = 0x00000000	

#define	C_RTC_SlaveAddr_Write		0x64		///*写RTC的从地址*///
#define	C_RTC_SlaveAddr_Read		0x65		///*读RTC的从地址*///
#define	C_RTC_StartAddr				0x00		///*读/写RTC的起始寄存器*///
#define	C_RTC_SFRAddr				0x0D		///*RTC的SFR地址：从0x0D开始的3个寄存器*///
#define	C_RTC_MostSignificantBit	0x80		///*最高有效位*///
#define C_RTC_Max_StopTimes			20			///*发stop时最多次数*///
#define	C_RTC_BitLen				8			///*I2C传输数据的数据长度：1字节*///

#define	C_RTC_SFR_D_DATA			0x00		///*D 寄存器的值*///
#define	C_RTC_SFR_E_DATA			0x00		///*E 寄存器的值*///
#define	C_RTC_SFR_E_VLF				0x02		///*E 寄存器的bit1必须为0*///
#define	C_RTC_SFR_F_DATA			0x60		///*F 寄存器的值*///

#define C_WeekAddr					3			///*week所在地址偏移*///

///*io 口线操作的宏定义*///
///*******************************************************************///
#define RTC_Set_Scl_Input		{IO_RTCSCL->IOCFG&=RTCSCL_SELECT;\
								IO_RTCSCL->MODER &= RTCSCL_IN_MODE;\
								IO_RTCSCL->PUPDR |= RTCSCL_NOPUPD;}

#define RTC_Set_Scl_Output		{IO_RTCSCL->IOCFG&=RTCSCL_SELECT;\
								IO_RTCSCL->MODER |= RTCSCL_OUT_MODE;\
								IO_RTCSCL->OTYPER |= RTCSCL_OUTPUT_PP;}
 
#define RTC_Scl_Output_0		{IO_RTCSCL->PTCLR = RTCSCLRESET;}

#define RTC_Scl_Output_1		{IO_RTCSCL->PTSET = RTCSCLSET;}
///*******************************************************************///
#define RTC_IO_Init				{IO_RTCSCL->IOCFG&=RTCSCL_SELECT;\
								IO_RTCSCL->MODER &= RTCSCL_IN_MODE;\
								IO_RTCSCL->PUPDR |= RTCSCL_NOPUPD;\
								IO_RTCSDA->IOCFG &= RTCSDA_SELECT;\
								IO_RTCSDA->MODER &= RTCSDA_IN_MODE;\
								IO_RTCSDA->PUPDR |= RTCSDA_NOPUPD;}

#define RTC_Set_Sda_Input		{IO_RTCSDA->IOCFG &= RTCSDA_SELECT;\
								IO_RTCSDA->MODER &= RTCSDA_IN_MODE;\
								IO_RTCSDA->PUPDR |= RTCSDA_NOPUPD;}

#define RTC_Set_Sda_Output		{IO_RTCSDA->IOCFG&=RTCSDA_SELECT;\
								IO_RTCSDA->MODER |= RTCSDA_OUT_MODE;\
								IO_RTCSDA->OTYPER &= RTCSDA_OUTPUT_OD;}

#define RTC_Sda_Output_0		{IO_RTCSDA->PTCLR = RTCSDARESET;}

#define RTC_Sda_Output_1		{IO_RTCSDA->PTSET = RTCSDASET;}

#define	RTC_Read_Sda			(IO_RTCSDA->IDR & RTCSDASET)
///*******************************************************************///
///*复旦微RTC
extern ushort16		Temperature_Adc;///当前温度ADC值(hex码)
extern float		Rtcadj_Offset;///温度补偿调校值
extern float		Rtcadj_Offset2;///温度补偿调校值
extern uchar8		RtcStopProcFlag;///停止温补标志
extern char8  	Temperature_Hex;///备份温度(hex码)
extern uchar8		temperpara_veri_flag;///温度系数校验标志

#define const_mark404		HXVAR( ushort16, 0x1FFFFC0E )	//404标记


//温度曲线相关参数
//extern const uchar8 RTC_Trim_Ctrl;	//0x55-补偿步长0.119ppm，其它-补偿补偿0.238ppm(仅404模式下可开启0.119)
//extern const uchar8 SleepPtatOffsetCfg;	//0x55-启用3V偏置(3V电源ptat偏置控制开关)，其他-关闭 
//extern const float const_xtl_top;		//计算温度曲线使用的顶点
//extern const float const_KL;	//温度补偿系数
//extern const float const_KH;
//extern const float const_TmpsL;	//温度ADC斜率
//extern const float const_TmpsH;
//extern const uchar8 constF_Volt;		//电压补偿量(兼容新硬件电池增加二极管),3表示0.03v/10表示0.1v
//extern const ushort16 const_adc_TrimB;
//extern const ushort16 const_adc_TrimT;
//extern const ushort16 const_KHKL_TrimRange;//晶体曲线修调功能分界范围，25度±7度内使用常温修调值krh，krl，范围外使用高低温修调值kh，kl
//extern const float const_T_OffsetRun;	//芯片发热修正-运行用
//extern const float const_T_OffsetSlp;	//芯片发热修正-休眠用
//extern const uchar8 const_TopNoTrim;  //顶点±x度附近不补偿 0x55:不补偿， 0x00:正常补偿
//extern const uchar8 const_TopNTRange;	//顶点附近关闭自动补偿温度adc范围，±x/5.0379=温度范围
//extern const float const_T_CL;	//低温查表中心温度
//extern const float const_T_CH;		//高温查表中心温度
//extern const uchar8 const_C_Mode;		//0x55:启动高低温高精度查表功能，其他，仅开启常温高精度查表
//
//extern const short16 const_TR_LSTART;	//低温记录启动温度（short16放大10倍）
//extern const short16 const_TR_HSTART;	//高温记录启动温度（short16放大10倍）
/////extern const uchar8 const_TR_GAP;//1;//	//记录间隔，单位分钟
/////extern const uchar8 const_TR_Mode;		//0x55:启动温度记录功能，其他，关闭

#endif
