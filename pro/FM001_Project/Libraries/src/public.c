/*******************************************************************************
Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     public.c
Version:       V1
Author:        gyj
Date:          2014-3-12
Description:   此文件是通用文件
---------------------------------------------------------------------------------
History1:第1次修改
内容1. Date:20201015
		Author: fy/fxy
		Modification:优化
		---------------------------------------------------------------------------
History2:第2次修改
内容2. Date:2021/03/01
		Author:G.G
		Modification:Public_CBB部分功能从该文件中移出
----------------------------------------------------------------------------------
History2:第2次修改
内容1.	Date:
		Author:
		Modification:
		---------------------------------------------------------------------------
内容2. Date:
		Author:
		Modification:
******************************************************************************/
#include "Public.h"

/*复旦微RTC*/
/*温度曲线相关参数*/
const uchar8 RTC_Trim_Ctrl@(0x0007FFB4) = 0x55;			/*0x55-补偿步长0.119ppm，其它-补偿补偿0.238ppm(仅404模式下可开启0.119)*/
const uchar8 SleepPtatOffsetCfg@(0x0007FFB6) = 0x55;	/*0x55-启用3V偏置(3V电源ptat偏置控制开关)，其他-关闭 */
const float const_xtl_top@(0x0007FFB8)	= 25.0;			/*计算温度曲线使用的顶点*/
#if 0	/*原来屏蔽*/
const float const_KL@(0x0007FFBC)	= 0.0300;			/*温度补偿系数，9月份电科院送样*/
const float const_KH@(0x0007FFC0)	= 0.0382;
#endif
const float const_KL@(0x0007FFBC)	= 0.0304;			/*温度补偿系数*/
const float const_KH@(0x0007FFC0)	= 0.0399;
const float const_TmpsL @(0x0007FFC4) = 5.0379;		/*温度ADC斜率*/
const float const_TmpsH @(0x0007FFC8) = 5.0379;
const uchar8 constF_Volt@(0x0007FFCC)	= 0;			/*电压补偿量(兼容新硬件电池增加二极管),3表示0.03v/10表示0.1v*/
const ushort16 const_adc_TrimB@(0x0007FFCE) = 0x3ff;
const ushort16 const_adc_TrimT@(0x0007FFD0) = 0x640;
const ushort16 const_KHKL_TrimRange@(0x0007FFD2) = 36;	/*晶体曲线修调功能分界范围，25度±7度内使用常温修调值krh，krl，范围外使用高低温修调值kh，kl*/
const float const_T_OffsetRun@(0x0007FFD4)	= -3.0;		/*芯片发热修正-运行用*/
const float const_T_OffsetSlp@(0x0007FFD8)	= -2.0;		/*芯片发热修正-休眠用*/
const uchar8 const_TopNoTrim@(0x0007FFDC) = 0x55;  		/*顶点±x度附近不补偿 0x55:不补偿， 0x00:正常补偿*/
const uchar8 const_TopNTRange@(0x0007FFDE) = 8;			/*顶点附近关闭自动补偿温度adc范围，±x/5.0379=温度范围*/
const float const_T_CL@(0x0007FFE0) = -23.0;			/*低温查表中心温度*/
const float const_T_CH@(0x0007FFE4) = 57.0;			/*高温查表中心温度*/
const uchar8 const_C_Mode@(0x0007FFE8) = 0x55;			/*0x55:启动高低温高精度查表功能，其他，仅开启常温高精度查表*/

const short16 const_TR_LSTART@(0x0007FFEA)	= -15*10;	/*低温记录启动温度（short16放大10倍）*/
const short16 const_TR_HSTART@(0x0007FFEC)	= 50*10;	/*高温记录启动温度（short16放大10倍）*/
#if 0	/*原来屏蔽*/
const uchar8 const_TR_GAP	= 6;						/*1;//	//记录间隔，单位分钟*/
const uchar8 const_TR_Mode 	= 0x55;						/*0x55:启动温度记录功能，其他，关闭*/
#endif

/* 国网单板复旦微方案，-M表与非模块表(远程、智能表)原理不同，通过如下表型进行预编译区分不同硬件，保持hex一致 */
/* 注意：startup_FM33A0XX.s文件中 HardFault_Handler的调试修改 */

#if 0		/* 20规范-C级智能表-无费控-3059 */
const uchar8 C_Meter_Type@(0x0007FFF0) = C_SmartMeter;
const uchar8 GV_C_Internal_Version[CL_Internal_Version]@(0x0007FFF4) = {0x08,0x21,0x59,0x30,0x03,0x12,0xfc,0xff};

const uchar8 C_Temp_VrefAotu@(0x0007FFB2) = C_Temp_VrefAotu_Dis;		/* 是否开启计量VREF温度补偿，目前电科院送样开启，正常生产关闭 */
const uchar8 C_ESAMPower@(0x0007FFB0) = C_ESAMPower_Close;				/* 是否关闭ESAM，为降低功耗, 目前电科院送样关闭ESAM电源，正常生产关闭 */
const uchar8 C_Odd_Harmonic@(0x0007FFF2) = C_Odd_Harmonic_Dis;			/* 是否开启奇次谐波补偿，目前电科院送样开启奇次谐波补偿，正常生产关闭 */
const uchar8 C_Cap_WhetherUsed@(0x0007FFA0) = C_Cap_WhetherUsed_Dis;	/* 是否使用超级电容，目前只个别地区使用，与硬件配合，注意使用时编译 */
const uchar8 C_Even_Harmonic@(0x0007FFA2) = C_Even_Harmonic_Dis;		/* 是否开启偶次谐波补偿，目前电科院送样开启偶次谐波补偿，正常生产关闭 */
const uchar8 C_Cap_OpenAfter30min@(0x0007FFA4) = C_Cap_OpenAfter30min_En;	/*超级电容充电开启时间，目前电科院送样上电30min后开启，正常生产上电3s后开启*/
																			/*因此此处电科院送样开启，正常生产关闭*/

#endif

#if 1		/* 20规范-B级本地费控表-Local-2966 */
const uchar8 C_Meter_Type@(0x0007FFF0) = C_L_SmartMeter;
const uchar8 GV_C_Internal_Version[CL_Internal_Version]@(0x0007FFF4) = {0x08,0x31,0x66,0x29,0x57,0x12,0xfb,0xff};

const uchar8 C_Temp_VrefAotu@(0x0007FFB2) = C_Temp_VrefAotu_En;			/* 是否开启计量VREF温度补偿，目前电科院送样开启，正常生产关闭 */
const uchar8 C_ESAMPower@(0x0007FFB0) = C_ESAMPower_Close;				/* 是否关闭ESAM，为降低功耗, 目前电科院送样关闭ESAM电源，正常生产关闭 */
const uchar8 C_Odd_Harmonic@(0x0007FFF2) = C_Odd_Harmonic_En;			/* 是否开启奇次谐波补偿，目前电科院送样开启奇次谐波补偿，正常生产关闭 */
const uchar8 C_Cap_WhetherUsed@(0x0007FFA0) = C_Cap_WhetherUsed_Dis;	/* 是否使用超级电容，目前只个别地区使用，与硬件配合，注意使用时编译 */
const uchar8 C_Even_Harmonic@(0x0007FFA2) = C_Even_Harmonic_En;			/* 是否开启偶次谐波补偿，目前电科院送样开启偶次谐波补偿，正常生产关闭 */
const uchar8 C_Cap_OpenAfter30min@(0x0007FFA4) = C_Cap_OpenAfter30min_En;	/*超级电容充电开启时间，目前电科院送样上电30min后开启，正常生产上电3s后开启*/
																			/*因此此处电科院送样开启，正常生产关闭*/

#endif

#if 0		/* 20规范-C级本地费控表-Local-3085 */
const uchar8 C_Meter_Type@(0x0007FFF0) = C_L_SmartMeter;
const uchar8 GV_C_Internal_Version[CL_Internal_Version]@(0x0007FFF4) = {0x08,0x11,0x85,0x30,0x57,0x12,0xfc,0xff};

const uchar8 C_Temp_VrefAotu@(0x0007FFB2) = C_Temp_VrefAotu_Dis;		/* 是否开启计量VREF温度补偿，目前电科院送样开启，正常生产关闭 */
const uchar8 C_ESAMPower@(0x0007FFB0) = C_ESAMPower_Close;				/* 是否关闭ESAM，为降低功耗, 目前电科院送样关闭ESAM电源，正常生产关闭 */
const uchar8 C_Odd_Harmonic@(0x0007FFF2) = C_Odd_Harmonic_Dis;			/* 是否开启奇次谐波补偿，目前电科院送样开启奇次谐波补偿，正常生产关闭 */
const uchar8 C_Cap_WhetherUsed@(0x0007FFA0) = C_Cap_WhetherUsed_Dis;	/* 是否使用超级电容，目前只个别地区使用，与硬件配合，注意使用时编译 */
const uchar8 C_Even_Harmonic@(0x0007FFA2) = C_Even_Harmonic_Dis;		/* 是否开启偶次谐波补偿，目前电科院送样开启偶次谐波补偿，正常生产关闭 */
const uchar8 C_Cap_OpenAfter30min@(0x0007FFA4) = C_Cap_OpenAfter30min_En;	/*超级电容充电开启时间，目前电科院送样上电30min后开启，正常生产上电3s后开启*/
																			/*因此此处电科院送样开启，正常生产关闭*/

#endif

#if	0		/* 20规范-B级远程费控表-Remote-2966 */
const uchar8 C_Meter_Type@(0x0007FFF0) = C_R_SmartMeter;
const uchar8 GV_C_Internal_Version[CL_Internal_Version]@(0x0007FFF4) = {0x08,0x31,0x66,0x29,0x77,0x12,0xfb,0xff};

const uchar8 C_Temp_VrefAotu@(0x0007FFB2) = C_Temp_VrefAotu_En;			/* 是否开启计量VREF温度补偿，目前电科院送样开启，正常生产关闭 */
const uchar8 C_ESAMPower@(0x0007FFB0) = C_ESAMPower_Close;				/* 是否关闭ESAM，为降低功耗, 目前电科院送样关闭ESAM电源，正常生产关闭 */
const uchar8 C_Odd_Harmonic@(0x0007FFF2) = C_Odd_Harmonic_En;			/* 是否开启奇次谐波补偿，目前电科院送样开启奇次谐波补偿，正常生产关闭 */
const uchar8 C_Cap_WhetherUsed@(0x0007FFA0) = C_Cap_WhetherUsed_Dis;	/* 是否使用超级电容，目前只个别地区使用，与硬件配合，注意使用时编译 */
const uchar8 C_Even_Harmonic@(0x0007FFA2) = C_Even_Harmonic_En;			/* 是否开启偶次谐波补偿，目前电科院送样开启偶次谐波补偿，正常生产关闭 */
const uchar8 C_Cap_OpenAfter30min@(0x0007FFA4) = C_Cap_OpenAfter30min_En;	/*超级电容充电开启时间，目前电科院送样上电30min后开启，正常生产上电3s后开启*/
																			/*因此此处电科院送样开启，正常生产关闭*/
#endif

#if	0		/* 20规范-C级远程费控表-Remote-3085 */
const uchar8 C_Meter_Type@(0x0007FFF0) = C_R_SmartMeter;
const uchar8 GV_C_Internal_Version[CL_Internal_Version]@(0x0007FFF4) = {0x08,0x11,0x85,0x30,0x77,0x12,0xfc,0xff};

const uchar8 C_Temp_VrefAotu@(0x0007FFB2) = C_Temp_VrefAotu_Dis;		/* 是否开启计量VREF温度补偿，目前电科院送样开启，正常生产关闭 */
const uchar8 C_ESAMPower@(0x0007FFB0) = C_ESAMPower_Close;				/* 是否关闭ESAM，为降低功耗, 目前电科院送样关闭ESAM电源，正常生产关闭 */
const uchar8 C_Odd_Harmonic@(0x0007FFF2) = C_Odd_Harmonic_Dis;			/* 是否开启奇次谐波补偿，目前电科院送样开启奇次谐波补偿，正常生产关闭 */
const uchar8 C_Cap_WhetherUsed@(0x0007FFA0) = C_Cap_WhetherUsed_Dis;	/* 是否使用超级电容，目前只个别地区使用，与硬件配合，注意使用时编译 */
const uchar8 C_Even_Harmonic@(0x0007FFA2) = C_Even_Harmonic_Dis;		/* 是否开启偶次谐波补偿，目前电科院送样开启偶次谐波补偿，正常生产关闭 */
const uchar8 C_Cap_OpenAfter30min@(0x0007FFA4) = C_Cap_OpenAfter30min_En;	/*超级电容充电开启时间，目前电科院送样上电30min后开启，正常生产上电3s后开启*/
																			/*因此此处电科院送样开启，正常生产关闭*/

#endif
/* 上述5个条件编译，只能选择其中一个 */

/*软件特征码*/
const uchar8 C_Software_Featurcode[C_External_Version_Len]@(C_SafedArea_StardAddr + C_Software_Featurcode_Offset) =
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x18, 0x20, 0x21, 0x02, 0x26, 0xFF, 0xFB, 0x10, 0x9A, 0x29, 0x66, 0x11, 0x00, 0xC9, 0x20,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

#if _DEBUGFY /*不再存RAM，改为使用宏定义,拼接时去掉*/
/*
	从计量芯片读出的脉冲最大阀值,hex格式，目前电能模块用(防飞走)。不同规格类型的表，该预置要计算核对和否合适，不然会影响电能计量
	电压规格	电流规格		脉冲常数    3*1.5Un*2Imax时0.5s脉冲数    10s脉冲数    	取整    	转为16进制数
	3×220/380	3×1.5(6)A		6400		12.16							243.2		244			0xF4
	3×220/380	3×5(60)A		400			13.2							264			264			0x108
	3×220/380	3×10(100)A		300			8.25							132			132			0x84
	3×57.7/100	3×0.3(1.2)A		100000		8.655							173.1		174			0xAE
	3×57.7/100	3×1.5(6)A		20000		8.655							173.1		174			0xAE
	3×57.7/100	3×1(10)A		20000		14.425							288.5		289			0x121
	3×100		3×0.3(1.2)A		100000		10								200			200			0xC8
	3×100		3×1.5(6)A		20000		10								200			200			0xC8
	3×100		3×1(10)A		20000		16.6667							333.333		334			0x14E
*/
const uchar8 GV_C_Pluse_Most__Lim[CLPluse_Most__Lim]@(0x0007FFFC)={0x21,0x01};
#endif

const uchar8 GV_C_SlipCurrent__Flag@(0x0007FFFE)=0;

#if 0
#define C_ParameterTypes   26	///*发送消息类型参数*///
const uchar8 C_ParameterTypesTable[C_ParameterTypes][2]=
{	///*参数号，				对应数据长度*///
	Pt_DisplayStatus,			Pt_DisplayStatus_Len,
	Pt_CodeID,					Pt_CodeID_Len,
	Pt_RelayStateFlag,			Pt_RelayStateFlag_Len,
	Pt_Dispatch_Timing,			Pt_Dispatch_Timing_Len,
	Pt_DemandStatus,			Pt_DemandStatus_Len,
	Pt_MsgFreezeImmediately,	Pt_MsgFreezeImmediately_Len,
	Pt_7DayAdd_FreezeTime,		Pt_7DayAdd_FreezeTime_Len,
	Pt_SettleAdd_Time,			Pt_SettleAdd_Time_Len,
	Pt_StepSwitchFlag,			Pt_StepSwitchFlag_Len,
	PT_Msg_UpdataKey_Review,	PT_Msg_UpdataKey_Review_Len,
	PT_EventNo,					PT_EventNo_Len,
	Pt_HappenTime,				Pt_HappenTime_Len,
	Pt_EndTime,					Pt_EndTime_Len,
	Pt_ParaMetersChange,		Pt_ParaMetersChange_Len,
	Pt_Initialization,			Pt_Initialization_Len,
	Pt_FristCheckDayChange,		Pt_FristCheckDayChange_Len,
	PT_CMsg_UpdataKey_Review,	PT_CMsg_UpdataKey_Review_Len,
	PT_CMsg_UpdKey_Rv_PWOn,		PT_CMsg_UpdKey_Rv_PWOn_Len,
	Pt_Comm_No,					Pt_Comm_No_Len,
	Pt_Dispatch_Key,			Pt_Dispatch_Key_Len,
	Pt_EventClearDI,			Pt_EventClearDI_Len,
	Pt_VoltageQR,				Pt_VoltageQR_Len,
	Pt_DisplayID,				Pt_DisplayID_Len,
	Pt_MeterClear,				Pt_MeterClear_Len,
	Pt_InitialMeterIC,			Pt_InitialMeterIC_Len,
	Pt_YearCheckDayChange,		Pt_YearCheckDayChange_Len
};
#endif


/*需要特殊处理的如下*/
/*电能表运行状态字，bitstring =16,表格中未体现*/
/*A相电压合格率、B相电压合格率、C相电压合格率下级还有一个structure,含有5个元素*/
/*日最大有功率及发生时间、月最大有功率及发生时间，下级包含C_double_long_unsigned和C_date_time_s*/
const Struct_FrozenConvert_Type Str_FrozenConvert_Table[]=
{
	/*V_ulOAD   	            V_uc645Length 		        V_uc698Type  		        V_uc698NextNum  V_uc698NextType             V_uc698RateNumMethod*/
	{CCom_Ac_En_FF_0,	        CLCom_Ac_En_FF_0,	        C_array,			        C_RatesNumTol,	C_double_long,              C_NeedRateNum_FF},  /*组合有功电能*/
	{CCom_Ac_Tol_En_0,	        CLCom_Ac_Tol_En_0,	        C_double_long,		        0,				C_double_long,              C_NeedRateNum 	},  /*组合有功总电能*/
	{CCom_Ac_T1_En_0 ,	        CLCom_Ac_T1_En_0,	        C_double_long,		        0,				C_double_long,              C_NeedRateNum 	},  /*组合有功费率1电能*/
	{CCom_Ac_T2_En_0 ,	        CLCom_Ac_T2_En_0,	        C_double_long,		        0,				C_double_long,              C_NeedRateNum 	},  /*组合有功费率2电能*/
	{CCom_Ac_T3_En_0 ,	        CLCom_Ac_T3_En_0,	        C_double_long,		        0,				C_double_long,              C_NeedRateNum 	},  /*组合有功费率3电能*/
	{CCom_Ac_T4_En_0 ,	        CLCom_Ac_T4_En_0,	        C_double_long,		        0,				C_double_long,              C_NeedRateNum 	},  /*组合有功费率4电能*/
	{CCom_Ac_T5_En_0 ,	        CLCom_Ac_T5_En_0,	        C_double_long,		        0,				C_double_long,              C_NeedRateNum 	},  /*组合有功费率5电能*/
	{CCom_Ac_T6_En_0 ,	        CLCom_Ac_T6_En_0,	        C_double_long,		        0,				C_double_long,              C_NeedRateNum 	},  /*组合有功费率6电能*/
	{CCom_Ac_T7_En_0 ,	        CLCom_Ac_T7_En_0,	        C_double_long,		        0,				C_double_long,              C_NeedRateNum 	},  /*组合有功费率7电能*/
	{CCom_Ac_T8_En_0 ,	        CLCom_Ac_T8_En_0,	        C_double_long,		        0,				C_double_long,              C_NeedRateNum 	},  /*组合有功费率8电能*/
	{CCom_Ac_T9_En_0 ,	        CLCom_Ac_T9_En_0,	        C_double_long,		        0,				C_double_long,              C_NeedRateNum 	},  /*组合有功费率9电能*/
	{CCom_Ac_T10_En_0,	        CLCom_Ac_T10_En_0,	        C_double_long,		        0,				C_double_long,              C_NeedRateNum 	},  /*组合有功费率10电能*/
	{CCom_Ac_T11_En_0,	        CLCom_Ac_T11_En_0,	        C_double_long,		        0,				C_double_long,              C_NeedRateNum	},  /*组合有功费率11电能*/
	{CCom_Ac_T12_En_0,	        CLCom_Ac_T12_En_0,	        C_double_long,		        0,				C_double_long,              C_NeedRateNum 	},  /*组合有功费率12电能*/
	{CPos_Ac_En_FF_0,	        CLPos_Ac_En_FF_0,           C_array,					C_RatesNumTol,	C_double_long_unsigned,     C_NeedRateNum_FF},  /*正向有功电能*/
	{CPos_Ac_Tol_En_0,	        CLPos_Ac_Tol_En_0,	        C_double_long_unsigned,	    0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前正向有功总电能*/
	{CPos_Ac_T1_En_0 ,	        CLPos_Ac_T1_En_0,	        C_double_long_unsigned,	    0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前正向有功费率1电能*/
	{CPos_Ac_T2_En_0 ,	        CLPos_Ac_T2_En_0,	        C_double_long_unsigned,	    0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前正向有功费率2电能*/
	{CPos_Ac_T3_En_0 ,	        CLPos_Ac_T3_En_0,	        C_double_long_unsigned,	    0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前正向有功费率3电能*/
	{CPos_Ac_T4_En_0 ,	        CLPos_Ac_T4_En_0,	        C_double_long_unsigned,	    0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前正向有功费率4电能*/
	{CPos_Ac_T5_En_0 ,	        CLPos_Ac_T5_En_0,	        C_double_long_unsigned,	    0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前正向有功费率5电能*/
	{CPos_Ac_T6_En_0 ,	        CLPos_Ac_T6_En_0,	        C_double_long_unsigned,	    0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前正向有功费率6电能*/
	{CPos_Ac_T7_En_0 ,	        CLPos_Ac_T7_En_0,	        C_double_long_unsigned,	    0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前正向有功费率7电能*/
	{CPos_Ac_T8_En_0 ,	        CLPos_Ac_T8_En_0,	        C_double_long_unsigned,	    0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前正向有功费率8电能*/
	{CPos_Ac_T9_En_0 ,	        CLPos_Ac_T9_En_0,	        C_double_long_unsigned,	    0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前正向有功费率9电能*/
	{CPos_Ac_T10_En_0,	        CLPos_Ac_T10_En_0,	        C_double_long_unsigned,	    0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前正向有功费率10电能*/
	{CPos_Ac_T11_En_0,	        CLPos_Ac_T11_En_0,	        C_double_long_unsigned,	    0,	            C_double_long_unsigned,     C_NeedRateNum	},  /*当前正向有功费率11电能*/
	{CPos_Ac_T12_En_0,	        CLPos_Ac_T12_En_0,	        C_double_long_unsigned,	    0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前正向有功费率12电能*/
	{0x00110200,		        CLPosA_Ac_En_0,	            C_array,					1,	            C_double_long_unsigned,     C_NoRateNum     },  /*A相正向有功电能*/
	{0x00110201,		        CLPosA_Ac_En_0,	            C_double_long_unsigned,	    0,	            C_double_long_unsigned,     C_NoRateNum     },  /*A相正向有功电能*/
	{0x00120200,		        CLPosB_Ac_En_0,	            C_array,					1,	            C_double_long_unsigned,     C_NoRateNum     },  /*B相正向有功电能*/
	{0x00120201,		        CLPosB_Ac_En_0,	            C_double_long_unsigned,	    0,	            C_double_long_unsigned,     C_NoRateNum     },  /*B相正向有功电能*/
	{0x00130200,		        CLPosC_Ac_En_0,	            C_array,					1,	            C_double_long_unsigned,     C_NoRateNum     },  /*C相正向有功电能*/
	{0x00130201,		        CLPosC_Ac_En_0,	            C_double_long_unsigned,	    0,	            C_double_long_unsigned,     C_NoRateNum     },  /*C相正向有功电能*/
	{CRev_Ac_En_FF_0,           CLRev_Ac_En_FF_0,	        C_array,					C_RatesNumTol,	C_double_long_unsigned,     C_NeedRateNum_FF},  /*反向有功电能*/
	{CRev_Ac_Tol_En_0,	        CLRev_Ac_Tol_En_0,	        C_double_long_unsigned,	    0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前反向有功总电能*/
	{CRev_Ac_T1_En_0 ,	        CLRev_Ac_T1_En_0,	        C_double_long_unsigned,	    0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前反向有功费率1电能*/
	{CRev_Ac_T2_En_0 ,	        CLRev_Ac_T2_En_0,	        C_double_long_unsigned,	    0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前反向有功费率2电能*/
	{CRev_Ac_T3_En_0 ,	        CLRev_Ac_T3_En_0,	        C_double_long_unsigned,	    0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前反向有功费率3电能*/
	{CRev_Ac_T4_En_0 ,	        CLRev_Ac_T4_En_0,	        C_double_long_unsigned,	    0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前反向有功费率4电能*/
	{CRev_Ac_T5_En_0 ,	        CLRev_Ac_T5_En_0,	        C_double_long_unsigned,	    0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前反向有功费率5电能*/
	{CRev_Ac_T6_En_0 ,	        CLRev_Ac_T6_En_0,	        C_double_long_unsigned,	    0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前反向有功费率6电能*/
	{CRev_Ac_T7_En_0 ,	        CLRev_Ac_T7_En_0,	        C_double_long_unsigned,	    0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前反向有功费率7电能*/
	{CRev_Ac_T8_En_0 ,	        CLRev_Ac_T8_En_0,	        C_double_long_unsigned,	    0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前反向有功费率8电能*/
	{CRev_Ac_T9_En_0 ,	        CLRev_Ac_T9_En_0,	        C_double_long_unsigned,	    0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前反向有功费率9电能*/
	{CRev_Ac_T10_En_0,	        CLRev_Ac_T10_En_0,	        C_double_long_unsigned,	    0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前反向有功费率10电能*/
	{CRev_Ac_T11_En_0,	        CLRev_Ac_T11_En_0,	        C_double_long_unsigned,	    0,	            C_double_long_unsigned,     C_NeedRateNum	},  /*当前反向有功费率11电能*/
	{CRev_Ac_T12_En_0,	        CLRev_Ac_T12_En_0,	        C_double_long_unsigned,	    0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前反向有功费率12电能*/
  	{0x00210200,	            CLRevA_Ac_En_0,	            C_array,					1,	            C_double_long_unsigned,     C_NoRateNum     },  /*A相反向有功电能*/
	{0x00210201,	            CLRevA_Ac_En_0,	            C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NoRateNum     },  /*A相反向有功电能*/
	{0x00220200,	            CLRevB_Ac_En_0,	            C_array,					1,	            C_double_long_unsigned,     C_NoRateNum     },  /*B相反向有功电能*/
	{0x00220201,	            CLRevB_Ac_En_0,	            C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NoRateNum     },  /*B相反向有功电能*/
	{0x00230200,	            CLRevC_Ac_En_0,	            C_array,					1,	            C_double_long_unsigned,     C_NoRateNum     },  /*C相反向有功电能*/
	{0x00230201,	            CLRevC_Ac_En_0,	            C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NoRateNum     },  /*C相反向有功电能*/
	{CCom_Re1_En_FF_0,	        CLCom_Re1_En_FF_0,	        C_array,					C_RatesNumTol,	C_double_long,              C_NeedRateNum_FF },  /*组合无功 1电能*/
	{CCom_Re1_Tol_En_0,	        CLCom_Re1_Tol_En_0,         C_double_long,				0,	            C_double_long,              C_NeedRateNum 	},  /*当前组合无功1总电能*/
	{CCom_Re1_T1_En_0 ,	        CLCom_Re1_T1_En_0,	        C_double_long,				0,	            C_double_long,              C_NeedRateNum 	},  /*当前组合无功1费率1电能*/
	{CCom_Re1_T2_En_0 ,	        CLCom_Re1_T2_En_0,	        C_double_long,				0,	            C_double_long,              C_NeedRateNum 	},  /*当前组合无功1费率2电能*/
	{CCom_Re1_T3_En_0 ,	        CLCom_Re1_T3_En_0,	        C_double_long,				0,	            C_double_long,              C_NeedRateNum 	},  /*当前组合无功1费率3电能*/
	{CCom_Re1_T4_En_0 ,	        CLCom_Re1_T4_En_0,	        C_double_long,				0,	            C_double_long,              C_NeedRateNum 	},  /*当前组合无功1费率4电能*/
	{CCom_Re1_T5_En_0 ,	        CLCom_Re1_T5_En_0,	        C_double_long,				0,	            C_double_long,              C_NeedRateNum 	},  /*当前组合无功1费率5电能*/
	{CCom_Re1_T6_En_0 ,	        CLCom_Re1_T6_En_0,	        C_double_long,				0,	            C_double_long,              C_NeedRateNum 	},  /*当前组合无功1费率6电能*/
	{CCom_Re1_T7_En_0 ,	        CLCom_Re1_T7_En_0,	        C_double_long,				0,	            C_double_long,              C_NeedRateNum 	},  /*当前组合无功1费率7电能*/
	{CCom_Re1_T8_En_0 ,	        CLCom_Re1_T8_En_0,	        C_double_long,				0,	            C_double_long,              C_NeedRateNum 	},  /*当前组合无功1费率8电能*/
	{CCom_Re1_T9_En_0 ,	        CLCom_Re1_T9_En_0,	        C_double_long,				0,	            C_double_long,              C_NeedRateNum 	},  /*当前组合无功1费率9电能*/
	{CCom_Re1_T10_En_0,	        CLCom_Re1_T10_En_0,         C_double_long,				0,	            C_double_long,              C_NeedRateNum 	},  /*当前组合无功1费率10电能*/
	{CCom_Re1_T11_En_0,	        CLCom_Re1_T11_En_0,         C_double_long,				0,	            C_double_long,              C_NeedRateNum	},  /*当前组合无功1费率11电能*/
	{CCom_Re1_T12_En_0,	        CLCom_Re1_T12_En_0,         C_double_long,				0,	            C_double_long,              C_NeedRateNum 	},  /*当前组合无功1费率12电能*/
	{0x00310200,	            CLComA_Re1_En_0,	        C_array,					1,	            C_double_long,              C_NoRateNum     },  /*A相组合无功1电能*/
	{0x00310201,	            CLComA_Re1_En_0,	        C_double_long,				0,	            C_double_long,              C_NoRateNum     },  /*A相组合无功1电能*/
	{0x00320200,	            CLComB_Re1_En_0,	        C_array,					1,	            C_double_long,              C_NoRateNum     },  /*B相组合无功1电能*/
	{0x00320201,	            CLComB_Re1_En_0,	        C_double_long,				0,	            C_double_long,              C_NoRateNum     },  /*B相组合无功1电能*/
	{0x00330200,	            CLComC_Re1_En_0,	        C_array,					1,	            C_double_long,              C_NoRateNum     },  /*C相组合无功1电能*/
	{0x00330201,	            CLComC_Re1_En_0,	        C_double_long,				0,	            C_double_long,              C_NoRateNum     },  /*C相组合无功1电能*/
	{CCom_Re2_En_FF_0,	        CLCom_Re2_En_FF_0,	        C_array,					C_RatesNumTol,	C_double_long,              C_NeedRateNum_FF},  /*组合无功 2电能*/
	{CCom_Re2_Tol_En_0,	        CLCom_Re2_Tol_En_0,         C_double_long,				0,	            C_double_long,              C_NeedRateNum 	},  /*当前组合无功2总电能*/
    {CCom_Re2_T1_En_0 ,	        CLCom_Re2_T1_En_0 ,         C_double_long,				0,	            C_double_long,              C_NeedRateNum 	},  /*当前组合无功2费率1电能*/
    {CCom_Re2_T2_En_0 ,	        CLCom_Re2_T2_En_0 ,         C_double_long,				0,	            C_double_long,              C_NeedRateNum 	},  /*当前组合无功2费率2电能*/
    {CCom_Re2_T3_En_0 ,	        CLCom_Re2_T3_En_0 ,         C_double_long,				0,	            C_double_long,              C_NeedRateNum 	},  /*当前组合无功2费率3电能*/
    {CCom_Re2_T4_En_0 ,	        CLCom_Re2_T4_En_0 ,         C_double_long,				0,	            C_double_long,              C_NeedRateNum 	},  /*当前组合无功2费率4电能*/
    {CCom_Re2_T5_En_0 ,	        CLCom_Re2_T5_En_0 ,         C_double_long,				0,	            C_double_long,              C_NeedRateNum 	},  /*当前组合无功2费率5电能*/
    {CCom_Re2_T6_En_0 ,	        CLCom_Re2_T6_En_0 ,         C_double_long,				0,	            C_double_long,              C_NeedRateNum 	},  /*当前组合无功2费率6电能*/
    {CCom_Re2_T7_En_0 ,	        CLCom_Re2_T7_En_0 ,         C_double_long,				0,	            C_double_long,              C_NeedRateNum 	},  /*当前组合无功2费率7电能*/
    {CCom_Re2_T8_En_0 ,	        CLCom_Re2_T8_En_0 ,         C_double_long,				0,	            C_double_long,              C_NeedRateNum 	},  /*当前组合无功2费率8电能*/
    {CCom_Re2_T9_En_0 ,	        CLCom_Re2_T9_En_0 ,         C_double_long,				0,	            C_double_long,              C_NeedRateNum 	},  /*当前组合无功2费率9电能*/
    {CCom_Re2_T10_En_0,	        CLCom_Re2_T10_En_0 ,        C_double_long,				0,	            C_double_long,              C_NeedRateNum 	},  /*当前组合无功2费率10电能*/
    {CCom_Re2_T11_En_0,	        CLCom_Re2_T11_En_0 ,        C_double_long,				0,	            C_double_long,              C_NeedRateNum	},  /*当前组合无功2费率11电能*/
    {CCom_Re2_T12_En_0,	        CLCom_Re2_T12_En_0 ,        C_double_long,				0,	            C_double_long,              C_NeedRateNum 	},  /*当前组合无功2费率12电能*/
 	{0x00410200,	            CLComA_Re2_En_0,	        C_array,					1,	            C_double_long,              C_NoRateNum     },  /*A相组合无功2电能*/
	{0x00410201,	            CLComA_Re2_En_0,	        C_double_long,				0,	            C_double_long,              C_NoRateNum     },  /*A相组合无功2电能*/
	{0x00420200,	            CLComB_Re2_En_0,	        C_array,					1,	            C_double_long,              C_NoRateNum     },  /*B相组合无功2电能*/
	{0x00420201,	            CLComB_Re2_En_0,	        C_double_long,				0,	            C_double_long,              C_NoRateNum     },  /*B相组合无功2电能*/
	{0x00430200,	            CLComC_Re2_En_0,	        C_array,					1,	            C_double_long,              C_NoRateNum     },  /*C相组合无功2电能*/
	{0x00430201,	            CLComC_Re2_En_0,	        C_double_long,				0,	            C_double_long,              C_NoRateNum     },  /*C相组合无功2电能*/
	{CQua1_Re_En_FF_0,	        CLQua1_Re_En_FF_0,	        C_array,					C_RatesNumTol,	C_double_long_unsigned,     C_NeedRateNum_FF},  /*第一象限无功电能*/
	{CQua1_Re_Tol_En_0,	        CLQua1_Re_Tol_En_0,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前1象限无功总电能*/
	{CQua1_Re_T1_En_0 ,	        CLQua1_Re_T1_En_0 ,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前1象限无功费率1电能*/
	{CQua1_Re_T2_En_0 ,	        CLQua1_Re_T2_En_0 ,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前1象限无功费率2电能*/
	{CQua1_Re_T3_En_0 ,	        CLQua1_Re_T3_En_0 ,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前1象限无功费率3电能*/
	{CQua1_Re_T4_En_0 ,	        CLQua1_Re_T4_En_0 ,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前1象限无功费率4电能*/
	{CQua1_Re_T5_En_0 ,	        CLQua1_Re_T5_En_0 ,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前1象限无功费率5电能*/
	{CQua1_Re_T6_En_0 ,	        CLQua1_Re_T6_En_0 ,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前1象限无功费率6电能*/
	{CQua1_Re_T7_En_0 ,	        CLQua1_Re_T7_En_0 ,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前1象限无功费率7电能*/
	{CQua1_Re_T8_En_0 ,	        CLQua1_Re_T8_En_0 ,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前1象限无功费率8电能*/
	{CQua1_Re_T9_En_0 ,	        CLQua1_Re_T9_En_0 ,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前1象限无功费率9电能*/
	{CQua1_Re_T10_En_0,	        CLQua1_Re_T10_En_0 ,        C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前1象限无功费率10电能*/
	{CQua1_Re_T11_En_0,	        CLQua1_Re_T11_En_0 ,        C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum	},  /*当前1象限无功费率11电能*/
	{CQua1_Re_T12_En_0,	        CLQua1_Re_T12_En_0 ,        C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前1象限无功费率12电能*/
	{0x00510200,	            CLQua1A_Re_En_0,	        C_array,					1,	            C_double_long_unsigned,     C_NoRateNum     },  /*A相第一象限无功电能*/
	{0x00510201,	            CLQua1A_Re_En_0,	        C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NoRateNum     },  /*A相第一象限无功电能*/
	{0x00520200,	            CLQua1B_Re_En_0,	        C_array,					1,	            C_double_long_unsigned,     C_NoRateNum     },  /*B相第一象限无功电能*/
	{0x00520201,	            CLQua1B_Re_En_0,	        C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NoRateNum     },  /*B相第一象限无功电能*/
	{0x00530200,	            CLQua1C_Re_En_0,	        C_array,					1,	            C_double_long_unsigned,     C_NoRateNum     },  /*C相第一象限无功电能*/
	{0x00530201,	            CLQua1C_Re_En_0,	        C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NoRateNum     },  /*C相第一象限无功电能*/
	{CQua2_Re_En_FF_0,	        CLQua2_Re_En_FF_0,	        C_array,					C_RatesNumTol,	C_double_long_unsigned,     C_NeedRateNum_FF},  /*第二象限无功电能*/
	{CQua2_Re_Tol_En_0,	        CLQua2_Re_Tol_En_0,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前2象限无功总电能*/
	{CQua2_Re_T1_En_0 ,	        CLQua2_Re_T1_En_0 ,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前2象限无功费率1电能*/
	{CQua2_Re_T2_En_0 ,	        CLQua2_Re_T2_En_0 ,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前2象限无功费率2电能*/
	{CQua2_Re_T3_En_0 ,	        CLQua2_Re_T3_En_0 ,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前2象限无功费率3电能*/
	{CQua2_Re_T4_En_0 ,	        CLQua2_Re_T4_En_0 ,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前2象限无功费率4电能*/
	{CQua2_Re_T5_En_0 ,	        CLQua2_Re_T5_En_0 ,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前2象限无功费率5电能*/
	{CQua2_Re_T6_En_0 ,	        CLQua2_Re_T6_En_0 ,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前2象限无功费率6电能*/
	{CQua2_Re_T7_En_0 ,	        CLQua2_Re_T7_En_0 ,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前2象限无功费率7电能*/
	{CQua2_Re_T8_En_0 ,	        CLQua2_Re_T8_En_0 ,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前2象限无功费率8电能*/
	{CQua2_Re_T9_En_0 ,	        CLQua2_Re_T9_En_0 ,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前2象限无功费率9电能*/
	{CQua2_Re_T10_En_0,	        CLQua2_Re_T10_En_0 ,        C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前2象限无功费率10电能*/
	{CQua2_Re_T11_En_0,	        CLQua2_Re_T11_En_0 ,        C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum	},  /*当前2象限无功费率11电能*/
	{CQua2_Re_T12_En_0,	        CLQua2_Re_T12_En_0 ,        C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前2象限无功费率12电能*/
	{0x00610200,	            CLQua2A_Re_En_0,	        C_array,					1,	            C_double_long_unsigned,     C_NoRateNum     },  /*A相第二象限无功电能*/
	{0x00610201,	            CLQua2A_Re_En_0,	        C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NoRateNum     },  /*A相第二象限无功电能*/
	{0x00620200,	            CLQua2B_Re_En_0,	        C_array,					1,	            C_double_long_unsigned,     C_NoRateNum     },  /*B相第二象限无功电能*/
	{0x00620201,	            CLQua2B_Re_En_0,	        C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NoRateNum     },  /*B相第二象限无功电能*/
	{0x00630200,	            CLQua2C_Re_En_0,	        C_array,					1,	            C_double_long_unsigned,     C_NoRateNum     },  /*C相第二象限无功电能*/
	{0x00630201,	            CLQua2C_Re_En_0,	        C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NoRateNum     },  /*C相第二象限无功电能*/
	{CQua3_Re_En_FF_0,	        CLQua3_Re_En_FF_0,	        C_array,					C_RatesNumTol,	C_double_long_unsigned,     C_NeedRateNum_FF},  /*第三象限无功电能*/
	{CQua3_Re_Tol_En_0,	        CLQua3_Re_Tol_En_0,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前3象限无功总电能*/
	{CQua3_Re_T1_En_0 ,	        CLQua3_Re_T1_En_0 ,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前3象限无功费率1电能*/
	{CQua3_Re_T2_En_0 ,	        CLQua3_Re_T2_En_0 ,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前3象限无功费率2电能*/
	{CQua3_Re_T3_En_0 ,	        CLQua3_Re_T3_En_0 ,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前3象限无功费率3电能*/
	{CQua3_Re_T4_En_0 ,	        CLQua3_Re_T4_En_0 ,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前3象限无功费率4电能*/
	{CQua3_Re_T5_En_0 ,	        CLQua3_Re_T5_En_0 ,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前3象限无功费率5电能*/
	{CQua3_Re_T6_En_0 ,	        CLQua3_Re_T6_En_0 ,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前3象限无功费率6电能*/
	{CQua3_Re_T7_En_0 ,	        CLQua3_Re_T7_En_0 ,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前3象限无功费率7电能*/
	{CQua3_Re_T8_En_0 ,	        CLQua3_Re_T8_En_0 ,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前3象限无功费率8电能*/
	{CQua3_Re_T9_En_0 ,	        CLQua3_Re_T9_En_0 ,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前3象限无功费率9电能*/
	{CQua3_Re_T10_En_0,	        CLQua3_Re_T10_En_0 ,        C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前3象限无功费率10电能*/
	{CQua3_Re_T11_En_0,	        CLQua3_Re_T11_En_0 ,        C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum	},  /*当前3象限无功费率11电能*/
	{CQua3_Re_T12_En_0,	        CLQua3_Re_T12_En_0 ,        C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前3象限无功费率12电能*/
	{0x00710200,	            CLQua3A_Re_En_0,	        C_array,					1,	            C_double_long_unsigned,     C_NoRateNum     },  /*A相第三象限无功电能*/
	{0x00710201,	            CLQua3A_Re_En_0,	        C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NoRateNum     },  /*A相第三象限无功电能*/
	{0x00720200,	            CLQua3B_Re_En_0,	        C_array,					1,	            C_double_long_unsigned,     C_NoRateNum     },  /*B相第三象限无功电能*/
	{0x00720201,	            CLQua3B_Re_En_0,	        C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NoRateNum     },  /*B相第三象限无功电能*/
	{0x00730200,	            CLQua3C_Re_En_0,	        C_array,					1,	            C_double_long_unsigned,     C_NoRateNum     },  /*C相第三象限无功电能*/
	{0x00730201,	            CLQua3C_Re_En_0,	        C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NoRateNum     },  /*C相第三象限无功电能*/
	{CQua4_Re_En_FF_0,	        CLQua4_Re_En_FF_0,	        C_array,					C_RatesNumTol,	C_double_long_unsigned,     C_NeedRateNum_FF},  /*第四象限无功电能*/
	{CQua4_Re_Tol_En_0,	        CLQua4_Re_Tol_En_0,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前4象限无功总电能*/
	{CQua4_Re_T1_En_0 ,	        CLQua4_Re_T1_En_0 ,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前4象限无功费率1电能*/
	{CQua4_Re_T2_En_0 ,	        CLQua4_Re_T2_En_0 ,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前4象限无功费率2电能*/
	{CQua4_Re_T3_En_0 ,	        CLQua4_Re_T3_En_0 ,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前4象限无功费率3电能*/
	{CQua4_Re_T4_En_0 ,	        CLQua4_Re_T4_En_0 ,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前4象限无功费率4电能*/
	{CQua4_Re_T5_En_0 ,	        CLQua4_Re_T5_En_0 ,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前4象限无功费率5电能*/
	{CQua4_Re_T6_En_0 ,	        CLQua4_Re_T6_En_0 ,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前4象限无功费率6电能*/
	{CQua4_Re_T7_En_0 ,	        CLQua4_Re_T7_En_0 ,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前4象限无功费率7电能*/
	{CQua4_Re_T8_En_0 ,	        CLQua4_Re_T8_En_0 ,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前4象限无功费率8电能*/
	{CQua4_Re_T9_En_0 ,	        CLQua4_Re_T9_En_0 ,         C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前4象限无功费率9电能*/
	{CQua4_Re_T10_En_0,	        CLQua4_Re_T10_En_0 ,        C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前4象限无功费率10电能*/
	{CQua4_Re_T11_En_0,	        CLQua4_Re_T11_En_0 ,        C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum	},  /*当前4象限无功费率11电能*/
	{CQua4_Re_T12_En_0,	        CLQua4_Re_T12_En_0 ,        C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NeedRateNum 	},  /*当前4象限无功费率12电能*/
	{0x00810200,	            CLQua4A_Re_En_0,	        C_array,					1,	            C_double_long_unsigned,     C_NoRateNum     },  /*A相第四象限无功电能*/
	{0x00810201,	            CLQua4A_Re_En_0,	        C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NoRateNum     },  /*A相第四象限无功电能*/
	{0x00820200,	            CLQua4B_Re_En_0,	        C_array,					1,	            C_double_long_unsigned,     C_NoRateNum     },  /*B相第四象限无功电能*/
	{0x00820201,	            CLQua4B_Re_En_0,	        C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NoRateNum     },  /*B相第四象限无功电能*/
	{0x00830200,	            CLQua4C_Re_En_0,	        C_array,					1,	            C_double_long_unsigned,     C_NoRateNum     },  /*C相第四象限无功电能*/
	{0x00830201,	            CLQua4C_Re_En_0,	        C_double_long_unsigned,		0,	            C_double_long_unsigned,     C_NoRateNum     },  /*C相第四象限无功电能*/

#if 0	/*202011原程序屏蔽，按编程规范修改为条件编译*/
	{0x00900200,	            20,				            C_array,				    5,	            C_double_long_unsigned	},  /*正向视在电能*/
	{0x00900201,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*正向视在总电能*/
	{0x00900202,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*正向视在费率1电能*/
	{0x00900203,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*正向视在费率2电能*/
	{0x00900204,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*正向视在费率3电能*/
	{0x00900205,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*正向视在费率4电能*/
	{0x00910200,	            4,					        C_array,					1,	            C_double_long_unsigned	},  /*A相正向视在电能*/
	{0x00910201,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*A相正向视在电能*/
	{0x00920200,	            4,					        C_array,					1,	            C_double_long_unsigned	},  /*B相正向视在电能*/
	{0x00920201,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*B相正向视在电能*/
	{0x00930200,	            4,					        C_array,					1,	            C_double_long_unsigned	},  /*C相正向视在电能*/
	{0x00930201,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*C相正向视在电能*/
	{0x00A00200,	            20,				  	        C_array,				    5,	            C_double_long_unsigned	},  /*反向视在电能*/
	{0x00A00201,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*反向视在总电能*/
	{0x00A00202,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*反向视在费率1电能*/
	{0x00A00203,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*反向视在费率2电能*/
	{0x00A00204,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*反向视在费率3电能*/
	{0x00A00205,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*反向视在费率4电能*/
	{0x00A10200,	            4,					        C_array,					1,	            C_double_long_unsigned	},  /*A相反向视在电能*/
	{0x00A10201,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*A相反向视在电能*/
	{0x00A20200,	            4,					        C_array,					1,	            C_double_long_unsigned	},  /*B相反向视在电能*/
	{0x00A20201,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*B相反向视在电能*/
	{0x00A30200,	            4,					        C_array,					1,	            C_double_long_unsigned	},  /*C相反向视在电能*/
	{0x00A30201,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*C相反向视在电能*/
	{0x01100200,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*正向有功基波总电能*/
	{0x01110200,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*A 相正向有功基波电能*/
	{0x01120200,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*B 相正向有功基波电能*/
	{0x01130200,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*C 相正向有功基波电能*/
	{0x01200200,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*反向有功基波总电能*/
	{0x01210200,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*A 相反向有功基波电能*/
	{0x01220200,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*B 相反向有功基波电能*/
	{0x01230200,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*C 相反向有功基波电能*/
	{0x02100200,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*正向有功谐波总电能*/
	{0x02110200,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*A 相正向有功谐波电能*/
	{0x02120200,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*B 相正向有功谐波电能*/
	{0x02130200,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*C相正向有功谐波电能*/
	{0x02200200,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*反向有功谐波总电能*/
	{0x02210200,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*A 相反向有功谐波电能*/
	{0x02220200,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*B 相反向有功谐波电能*/
	{0x02230200,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*C 相反向有功谐波电能*/
	{0x03000200,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*铜损有功总电能补偿量*/
	{0x03010200,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*A 相铜损有功电能补偿量*/
	{0x03020200,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*B 相铜损有功电能补偿量*/
	{0x03030200,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*C 相铜损有功电能补偿量*/
	{0x04000200,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*铁损有功总电能补偿量*/
	{0x04010200,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*A 相铁损有功电能补偿量*/
	{0x04020200,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*B 相铁损有功电能补偿量*/
	{0x04030200,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*C 相铁损有功电能补偿*/
	{0x05000200,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*关联总电能*/
	{0x05010200,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*A相关联电能*/
	{0x05020200,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*B相关联电能*/
	{0x05030200,	            4,					        C_double_long_unsigned,		0,	            C_double_long_unsigned	},  /*C相关联电能*/
#endif

	{CPos_Ac_En_PreFF_0,	    CLPos_Ac_En_PreFF_0,        C_array,			        C_RatesNumTol,	C_long64_unsigned,     C_NeedRateNum_FF 	},  /*高精度正向有功电能*/
	{CPos_Ac_Tol_PreEn_0,	    CLPos_Ac_Tol_PreEn_0,       C_long64_unsigned,		    0,	            C_long64_unsigned,     C_NeedRateNum 		},  /*高精度正向有功总电能*/
	{CPos_Ac_T1_PreEn_0 ,	    CLPos_Ac_T1_PreEn_0 ,       C_long64_unsigned,		    0,	            C_long64_unsigned,     C_NeedRateNum 		},  /*高精度正向有功费率1电能*/
	{CPos_Ac_T2_PreEn_0 ,	    CLPos_Ac_T2_PreEn_0 ,       C_long64_unsigned,		    0,	            C_long64_unsigned,     C_NeedRateNum 		},  /*高精度正向有功费率2电能*/
	{CPos_Ac_T3_PreEn_0 ,	    CLPos_Ac_T3_PreEn_0 ,       C_long64_unsigned,		    0,	            C_long64_unsigned,     C_NeedRateNum 		},  /*高精度正向有功费率3电能*/
	{CPos_Ac_T4_PreEn_0 ,	    CLPos_Ac_T4_PreEn_0 ,       C_long64_unsigned,		    0,	            C_long64_unsigned,     C_NeedRateNum 		},  /*高精度正向有功费率4电能*/
	{CPos_Ac_T5_PreEn_0 ,	    CLPos_Ac_T5_PreEn_0 ,       C_long64_unsigned,		    0,	            C_long64_unsigned,     C_NeedRateNum 		},  /*高精度正向有功费率5电能*/
	{CPos_Ac_T6_PreEn_0 ,	    CLPos_Ac_T6_PreEn_0 ,       C_long64_unsigned,		    0,	            C_long64_unsigned,     C_NeedRateNum 		},  /*高精度正向有功费率6电能*/
	{CPos_Ac_T7_PreEn_0 ,	    CLPos_Ac_T7_PreEn_0 ,       C_long64_unsigned,		    0,	            C_long64_unsigned,     C_NeedRateNum 		},  /*高精度正向有功费率7电能*/
	{CPos_Ac_T8_PreEn_0 ,	    CLPos_Ac_T8_PreEn_0 ,       C_long64_unsigned,		    0,	            C_long64_unsigned,     C_NeedRateNum 		},  /*高精度正向有功费率8电能*/
	{CPos_Ac_T9_PreEn_0 ,	    CLPos_Ac_T9_PreEn_0 ,       C_long64_unsigned,		    0,	            C_long64_unsigned,     C_NeedRateNum 		},  /*高精度正向有功费率9电能*/
	{CPos_Ac_T10_PreEn_0,	    CLPos_Ac_T10_PreEn_0,       C_long64_unsigned,		    0,	            C_long64_unsigned,     C_NeedRateNum 		},  /*高精度正向有功费率10电能*/
	{CPos_Ac_T11_PreEn_0,	    CLPos_Ac_T11_PreEn_0,       C_long64_unsigned,		    0,	            C_long64_unsigned,     C_NeedRateNum		},  /*高精度正向有功费率11电能*/
	{CPos_Ac_T12_PreEn_0,	    CLPos_Ac_T12_PreEn_0,       C_long64_unsigned,		    0,	            C_long64_unsigned,     C_NeedRateNum 		},  /*高精度正向有功费率12电能*/

	{CRev_Ac_En_PreFF_0,	    CLRev_Ac_En_PreFF_0,		C_array,			        C_RatesNumTol,	C_long64_unsigned,     C_NeedRateNum_FF 	},  /*高精度反向有功电能*/
	{CRev_Ac_Tol_PreEn_0,	    CLRev_Ac_Tol_PreEn_0,		C_long64_unsigned,		    0,	            C_long64_unsigned,     C_NeedRateNum 		},  /*高精度反向有功总电能*/
	{CRev_Ac_T1_PreEn_0 ,	    CLRev_Ac_T1_PreEn_0 ,		C_long64_unsigned,		    0,	            C_long64_unsigned,     C_NeedRateNum 		},  /*高精度反向有功费率1电能*/
	{CRev_Ac_T2_PreEn_0 ,	    CLRev_Ac_T2_PreEn_0 ,		C_long64_unsigned,		    0,	            C_long64_unsigned,     C_NeedRateNum 		},  /*高精度反向有功费率2电能*/
	{CRev_Ac_T3_PreEn_0 ,	    CLRev_Ac_T3_PreEn_0 ,		C_long64_unsigned,		    0,	            C_long64_unsigned,     C_NeedRateNum 		},  /*高精度反向有功费率3电能*/
	{CRev_Ac_T4_PreEn_0 ,	    CLRev_Ac_T4_PreEn_0 ,		C_long64_unsigned,		    0,	            C_long64_unsigned,     C_NeedRateNum 		},  /*高精度反向有功费率4电能*/
	{CRev_Ac_T5_PreEn_0 ,	    CLRev_Ac_T5_PreEn_0 ,		C_long64_unsigned,		    0,	            C_long64_unsigned,     C_NeedRateNum 		},  /*高精度反向有功费率5电能*/
	{CRev_Ac_T6_PreEn_0 ,	    CLRev_Ac_T6_PreEn_0 ,		C_long64_unsigned,		    0,	            C_long64_unsigned,     C_NeedRateNum 		},  /*高精度反向有功费率6电能*/
	{CRev_Ac_T7_PreEn_0 ,	    CLRev_Ac_T7_PreEn_0 ,		C_long64_unsigned,		    0,	            C_long64_unsigned,     C_NeedRateNum 		},  /*高精度反向有功费率7电能*/
	{CRev_Ac_T8_PreEn_0 ,	    CLRev_Ac_T8_PreEn_0 ,		C_long64_unsigned,		    0,	            C_long64_unsigned,     C_NeedRateNum 		},  /*高精度反向有功费率8电能*/
	{CRev_Ac_T9_PreEn_0 ,	    CLRev_Ac_T9_PreEn_0 ,		C_long64_unsigned,		    0,	            C_long64_unsigned,     C_NeedRateNum 		},  /*高精度反向有功费率9电能*/
	{CRev_Ac_T10_PreEn_0,	    CLRev_Ac_T10_PreEn_0,		C_long64_unsigned,		    0,	            C_long64_unsigned,     C_NeedRateNum 		},  /*高精度反向有功费率10电能*/
	{CRev_Ac_T11_PreEn_0,	    CLRev_Ac_T11_PreEn_0,		C_long64_unsigned,		    0,	            C_long64_unsigned,     C_NeedRateNum		},  /*高精度反向有功费率11电能*/
	{CRev_Ac_T12_PreEn_0,	    CLRev_Ac_T12_PreEn_0,		C_long64_unsigned,		    0,	            C_long64_unsigned,     C_NeedRateNum 		},  /*高精度反向有功费率12电能*/

#if 0	/*202011原程序屏蔽，按编程规范修改为条件编译*/
	{0x00500401,	            5,					        C_long64_unsigned,		    0,	            C_long64_unsigned	},  /*高精度第一象限无功总电能*/
	{0x00600401,	            5,					        C_long64_unsigned,		    0,	            C_long64_unsigned	},  /*高精度第二象限无功总电能*/
	{0x00700401,	            5,					        C_long64_unsigned,		    0,	            C_long64_unsigned	},  /*高精度第三象限无功总电能*/
	{0x00800401,	            5,					        C_long64_unsigned,		    0,	            C_long64_unsigned	},  /*高精度第四象限无功总电能*/
#endif

	{CPos_Ac_De_FF_0,	        CLPos_Ac_De_FF_0,	        C_array,				    C_RatesNumTol,	C_structure,           C_NeedRateNum_FF  		},  /*正向有功最大需量*/
	{CPos_Ac_Tol_De_0,	        CLPos_Ac_Tol_De_0,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前正向有功总最大需量及发生时刻*/
	{CPos_Ac_T1_De_0,	        CLPos_Ac_T1_De_0,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前正向有功费率1最大需量及发生时刻*/
	{CPos_Ac_T2_De_0,	        CLPos_Ac_T2_De_0,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前正向有功费率2最大需量及发生时刻*/
	{CPos_Ac_T3_De_0,	        CLPos_Ac_T3_De_0,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前正向有功费率3最大需量及发生时刻*/
	{CPos_Ac_T4_De_0,	        CLPos_Ac_T4_De_0,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前正向有功费率4最大需量及发生时刻*/
	{CPos_Ac_T5_De_0,	        CLPos_Ac_T4_De_0,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前正向有功费率5最大需量及发生时刻*/
	{CPos_Ac_T6_De_0,	        CLPos_Ac_T4_De_0,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前正向有功费率6最大需量及发生时刻*/
	{CPos_Ac_T7_De_0,	        CLPos_Ac_T4_De_0,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前正向有功费率7最大需量及发生时刻*/
	{CPos_Ac_T8_De_0,	        CLPos_Ac_T4_De_0,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前正向有功费率8最大需量及发生时刻*/
	{CPos_Ac_T9_De_0,	        CLPos_Ac_T4_De_0,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前正向有功费率9最大需量及发生时刻*/
	{CPos_Ac_T10_De_0,	        CLPos_Ac_T4_De_0,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前正向有功费率10最大需量及发生时刻*/
	{CPos_Ac_T11_De_0,	        CLPos_Ac_T4_De_0,	        C_structure,			    1,	            C_structure,           C_NeedRateNum	    	},  /*当前正向有功费率11最大需量及发生时刻*/
	{CPos_Ac_T12_De_0,	        CLPos_Ac_T4_De_0,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前正向有功费率12最大需量及发生时刻*/
	{0x10110200,	            CLPosA_Ac_De_0,		        C_array,				    1,	            C_structure,           C_NoRateNum       		},  /* A相正向有功最大需量*/
	{0x10110201,	            CLPosA_Ac_De_0,		        C_structure,			    1,	            C_structure,           C_NoRateNum       		},  /* A相正向有功最大需量*/
	{0x10120200,	            CLPosB_Ac_De_0,		        C_array,			        1,	            C_structure,           C_NoRateNum       		},  /* B相正向有功最大需量*/
	{0x10120201,	            CLPosB_Ac_De_0,		        C_structure,			    1,	            C_structure,           C_NoRateNum       		},  /* B相正向有功最大需量*/
	{0x10130200,	            CLPosC_Ac_De_0,		        C_array,				    1,	            C_structure,           C_NoRateNum       		},  /* C相正向有功最大需量*/
	{0x10130201,	            CLPosC_Ac_De_0,		        C_structure,			    1,	            C_structure,           C_NoRateNum       		},  /* C相正向有功最大需量*/
	{CRev_Ac_De_FF_0,	        CLRev_Ac_De_FF_0,	        C_array,				    C_RatesNumTol,	C_structure,           C_NeedRateNum_FF  		},  /* 反向有功最大需量*/
	{CRev_Ac_Tol_De_0,	        CLRev_Ac_Tol_De_0,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前反向有功总最大需量及发生时刻*/
	{CRev_Ac_T1_De_0 ,	        CLRev_Ac_T1_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前反向有功费率1最大需量及发生时刻*/
	{CRev_Ac_T2_De_0 ,	        CLRev_Ac_T2_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前反向有功费率2最大需量及发生时刻*/
	{CRev_Ac_T3_De_0 ,	        CLRev_Ac_T3_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前反向有功费率3最大需量及发生时刻*/
	{CRev_Ac_T4_De_0 ,	        CLRev_Ac_T4_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前反向有功费率4最大需量及发生时刻*/
	{CRev_Ac_T5_De_0 ,	        CLRev_Ac_T5_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前反向有功费率4最大需量及发生时刻*/
	{CRev_Ac_T6_De_0 ,	        CLRev_Ac_T6_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前反向有功费率4最大需量及发生时刻*/
	{CRev_Ac_T7_De_0 ,	        CLRev_Ac_T7_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前反向有功费率4最大需量及发生时刻*/
	{CRev_Ac_T8_De_0 ,	        CLRev_Ac_T8_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前反向有功费率4最大需量及发生时刻*/
	{CRev_Ac_T9_De_0 ,	        CLRev_Ac_T9_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前反向有功费率4最大需量及发生时刻*/
	{CRev_Ac_T10_De_0 ,	        CLRev_Ac_T10_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前反向有功费率4最大需量及发生时刻*/
	{CRev_Ac_T11_De_0 ,	        CLRev_Ac_T11_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum	    	},  /*当前反向有功费率4最大需量及发生时刻*/
	{CRev_Ac_T12_De_0 ,	        CLRev_Ac_T12_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前反向有功费率4最大需量及发生时刻*/
	{0x10210200,	            CLRevA_Ac_De_0,		        C_array,				    1,	            C_structure,           C_NoRateNum       		},  /* A相反向有功最大需量*/
	{0x10210201,	            CLRevA_Ac_De_0,		        C_structure,			    1,	            C_structure,           C_NoRateNum       		},  /* A相反向有功最大需量*/
	{0x10220200,	            CLRevB_Ac_De_0,		        C_array,				    1,	            C_structure,           C_NoRateNum       		},  /* B相反向有功最大需量*/
	{0x10220201,	            CLRevB_Ac_De_0,		        C_structure,			    1,	            C_structure,           C_NoRateNum       		},  /* B相反向有功最大需量*/
	{0x10230200,	            CLRevC_Ac_De_0,		        C_array,				    1,	            C_structure,           C_NoRateNum       		},  /* C相反向有功最大需量*/
	{0x10230201,	            CLRevC_Ac_De_0,		        C_structure,			    1,	            C_structure,           C_NoRateNum       		},  /* C相反向有功最大需量*/
	{CCom_Re1_De_FF_0,	        CLCom_Re1_De_FF_0,	        C_array,				    C_RatesNumTol,	C_structure,           C_NeedRateNum_FF  		},  /* 组合无功 1最大需量*/
	{CCom_Re1_Tol_De_0,         CLCom_Re1_Tol_De_0,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前组合无功1总最大需量及发生时刻*/
	{CCom_Re1_T1_De_0 ,         CLCom_Re1_T1_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前组合无功1费率1最大需量及发生时刻*/
	{CCom_Re1_T2_De_0 ,         CLCom_Re1_T2_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前组合无功1费率2最大需量及发生时刻*/
	{CCom_Re1_T3_De_0 ,         CLCom_Re1_T3_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前组合无功1费率3最大需量及发生时刻*/
	{CCom_Re1_T4_De_0 ,         CLCom_Re1_T4_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前组合无功1费率4最大需量及发生时刻*/
	{CCom_Re1_T5_De_0 ,         CLCom_Re1_T5_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前组合无功1费率4最大需量及发生时刻*/
	{CCom_Re1_T6_De_0 ,         CLCom_Re1_T6_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前组合无功1费率4最大需量及发生时刻*/
	{CCom_Re1_T7_De_0 ,         CLCom_Re1_T7_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前组合无功1费率4最大需量及发生时刻*/
	{CCom_Re1_T8_De_0 ,         CLCom_Re1_T8_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前组合无功1费率4最大需量及发生时刻*/
	{CCom_Re1_T9_De_0 ,         CLCom_Re1_T9_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前组合无功1费率4最大需量及发生时刻*/
	{CCom_Re1_T10_De_0 ,        CLCom_Re1_T10_De_0 ,	    C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前组合无功1费率4最大需量及发生时刻*/
	{CCom_Re1_T11_De_0 ,        CLCom_Re1_T11_De_0 ,	    C_structure,			    1,	            C_structure,           C_NeedRateNum	    	},  /*当前组合无功1费率4最大需量及发生时刻*/
	{CCom_Re1_T12_De_0 ,        CLCom_Re1_T12_De_0 ,	    C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前组合无功1费率4最大需量及发生时刻*/
	{0x10310200,	            CLComA_Re1_De_0,	        C_array,				    1,	            C_structure,           C_NoRateNum       		},  /* A相组合无功 1最大需量*/
	{0x10310201,	            CLComA_Re1_De_0,	        C_structure,			    1,	            C_structure,           C_NoRateNum       		},  /* A相组合无功 1最大需量*/
	{0x10320200,	            CLComB_Re1_De_0,	        C_array,				    1,	            C_structure,           C_NoRateNum       		},  /* B相组合无功 1最大需量*/
	{0x10320201,	            CLComB_Re1_De_0,	        C_structure,			    1,	            C_structure,           C_NoRateNum       		},  /* B相组合无功 1最大需量*/
	{0x10330200,	            CLComC_Re1_De_0,	        C_array,				    1,	            C_structure,           C_NoRateNum       		},  /* C相组合无功 1最大需量*/
	{0x10330201,	            CLComC_Re1_De_0,	        C_structure,			    1,	            C_structure,           C_NoRateNum       		},  /* C相组合无功 1最大需量*/
	{CCom_Re2_De_FF_0,	        CLCom_Re2_De_FF_0,	        C_array,				    C_RatesNumTol,	C_structure,           C_NeedRateNum_FF  		},  /* 组合无功2最大需量*/
	{CCom_Re2_Tol_De_0,		    CLCom_Re2_Tol_De_0,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前组合无功2总最大需量及发生时刻*/
	{CCom_Re2_T1_De_0 ,		    CLCom_Re2_T1_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前组合无功2费率1最大需量及发生时刻*/
	{CCom_Re2_T2_De_0 ,		    CLCom_Re2_T2_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前组合无功2费率2最大需量及发生时刻*/
	{CCom_Re2_T3_De_0 ,		    CLCom_Re2_T3_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前组合无功2费率3最大需量及发生时刻*/
	{CCom_Re2_T4_De_0 ,		    CLCom_Re2_T4_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前组合无功2费率4最大需量及发生时刻*/
	{CCom_Re2_T5_De_0 ,		    CLCom_Re2_T5_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前组合无功2费率4最大需量及发生时刻*/
	{CCom_Re2_T6_De_0 ,		    CLCom_Re2_T6_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前组合无功2费率4最大需量及发生时刻*/
	{CCom_Re2_T7_De_0 ,		    CLCom_Re2_T7_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前组合无功2费率4最大需量及发生时刻*/
	{CCom_Re2_T8_De_0 ,		    CLCom_Re2_T8_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前组合无功2费率4最大需量及发生时刻*/
	{CCom_Re2_T9_De_0 ,		    CLCom_Re2_T9_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前组合无功2费率4最大需量及发生时刻*/
	{CCom_Re2_T10_De_0 ,   	    CLCom_Re2_T10_De_0 ,	    C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前组合无功2费率4最大需量及发生时刻*/
	{CCom_Re2_T11_De_0 ,   	    CLCom_Re2_T11_De_0 ,	    C_structure,			    1,	            C_structure,           C_NeedRateNum	    	},  /*当前组合无功2费率4最大需量及发生时刻*/
	{CCom_Re2_T12_De_0 ,   	    CLCom_Re2_T12_De_0 ,	    C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前组合无功2费率4最大需量及发生时刻*/
	{0x10410200,	            CLComA_Re2_De_0,	        C_array,			        1,	            C_structure,           C_NoRateNum       		},  /* A相组合无功2最大需量*/
	{0x10410201,	            CLComA_Re2_De_0,	        C_structure,		        1,	            C_structure,           C_NoRateNum       		},  /* A相组合无功2最大需量*/
	{0x10420200,	            CLComB_Re2_De_0,	        C_array,			        1,	            C_structure,           C_NoRateNum       		},  /* B相组合无功2最大需量*/
	{0x10420201,	            CLComB_Re2_De_0,	        C_structure,		        1,	            C_structure,           C_NoRateNum       		},  /* B相组合无功2最大需量*/
	{0x10430200,	            CLComC_Re2_De_0,	        C_array,			        1,	            C_structure,           C_NoRateNum       		},  /* C相组合无功2最大需量*/
	{0x10430201,	            CLComC_Re2_De_0,	        C_structure,		        1,	            C_structure,           C_NoRateNum       		},  /* C相组合无功2最大需量*/
	{CQua1_Re_De_FF_0,	    	CLQua1_Re_De_FF_0,	        C_array,				    C_RatesNumTol,	C_structure,           C_NeedRateNum_FF  		},  /* 第一象限最大需量*/
	{CQua1_Re_Tol_De_0,		    CLQua1_Re_Tol_De_0,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前1象限无功总最大需量及发生时刻*/
	{CQua1_Re_T1_De_0 ,		    CLQua1_Re_T1_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前1象限无功费率1最大需量及发生时刻*/
	{CQua1_Re_T2_De_0 ,		    CLQua1_Re_T2_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前1象限无功费率2最大需量及发生时刻*/
	{CQua1_Re_T3_De_0 ,		    CLQua1_Re_T3_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前1象限无功费率3最大需量及发生时刻*/
	{CQua1_Re_T4_De_0 ,		    CLQua1_Re_T4_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前1象限无功费率4最大需量及发生时刻*/
	{CQua1_Re_T5_De_0 ,		    CLQua1_Re_T5_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前1象限无功费率4最大需量及发生时刻*/
	{CQua1_Re_T6_De_0 ,		    CLQua1_Re_T6_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前1象限无功费率4最大需量及发生时刻*/
	{CQua1_Re_T7_De_0 ,		    CLQua1_Re_T7_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前1象限无功费率4最大需量及发生时刻*/
	{CQua1_Re_T8_De_0 ,		    CLQua1_Re_T8_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前1象限无功费率4最大需量及发生时刻*/
	{CQua1_Re_T9_De_0 ,		    CLQua1_Re_T9_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前1象限无功费率4最大需量及发生时刻*/
	{CQua1_Re_T10_De_0 ,   	    CLQua1_Re_T10_De_0 ,	    C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前1象限无功费率4最大需量及发生时刻*/
	{CQua1_Re_T11_De_0 ,   	    CLQua1_Re_T11_De_0 ,	    C_structure,			    1,	            C_structure,           C_NeedRateNum	    	},  /*当前1象限无功费率4最大需量及发生时刻*/
	{CQua1_Re_T12_De_0 ,   	    CLQua1_Re_T12_De_0 ,	    C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前1象限无功费率4最大需量及发生时刻*/
	{0x10510200,	            CLQua1A_Re_De_0,	        C_array,				    1,	            C_structure,           C_NoRateNum       		},  /* A相第一象限最大需量*/
	{0x10510201,	            CLQua1A_Re_De_0,	        C_structure,			    1,	            C_structure,           C_NoRateNum       		},  /* A相第一象限最大需量*/
	{0x10520200,	            CLQua1B_Re_De_0,	        C_array,				    1,	            C_structure,           C_NoRateNum       		},  /* B相第一象限最大需量*/
	{0x10520201,	            CLQua1B_Re_De_0,	        C_structure,			    1,	            C_structure,           C_NoRateNum       		},  /* B相第一象限最大需量*/
	{0x10530200,	            CLQua1C_Re_De_0,	        C_array,				    1,	            C_structure,           C_NoRateNum       		},  /* C相第一象限最大需量*/
	{0x10530201,	            CLQua1C_Re_De_0,	        C_structure,			    1,	            C_structure,           C_NoRateNum       		},  /* C相第一象限最大需量*/
	{CQua2_Re_De_FF_0,	    	CLQua2_Re_De_FF_0,	        C_array,				    C_RatesNumTol,	C_structure,           C_NeedRateNum_FF  		},  /* 第二象限最大需量*/
	{CQua2_Re_Tol_De_0,		    CLQua2_Re_Tol_De_0,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前2象限无功总最大需量及发生时刻*/
	{CQua2_Re_T1_De_0 ,		    CLQua2_Re_T1_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前2象限无功费率1最大需量及发生时刻*/
	{CQua2_Re_T2_De_0 ,		    CLQua2_Re_T2_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前2象限无功费率2最大需量及发生时刻*/
	{CQua2_Re_T3_De_0 ,		    CLQua2_Re_T3_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前2象限无功费率3最大需量及发生时刻*/
	{CQua2_Re_T4_De_0 ,		    CLQua2_Re_T4_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前2象限无功费率4最大需量及发生时刻*/
	{CQua2_Re_T5_De_0 ,		    CLQua2_Re_T5_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前2象限无功费率4最大需量及发生时刻*/
	{CQua2_Re_T6_De_0 ,		    CLQua2_Re_T6_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前2象限无功费率4最大需量及发生时刻*/
	{CQua2_Re_T7_De_0 ,		    CLQua2_Re_T7_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前2象限无功费率4最大需量及发生时刻*/
	{CQua2_Re_T8_De_0 ,		    CLQua2_Re_T8_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前2象限无功费率4最大需量及发生时刻*/
	{CQua2_Re_T9_De_0 ,		    CLQua2_Re_T9_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前2象限无功费率4最大需量及发生时刻*/
	{CQua2_Re_T10_De_0 ,   	    CLQua2_Re_T10_De_0 ,	    C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前2象限无功费率4最大需量及发生时刻*/
	{CQua2_Re_T11_De_0 ,   	    CLQua2_Re_T11_De_0 ,	    C_structure,			    1,	            C_structure,           C_NeedRateNum	    	},  /*当前2象限无功费率4最大需量及发生时刻*/
	{CQua2_Re_T12_De_0 ,   	    CLQua2_Re_T12_De_0 ,	    C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前2象限无功费率4最大需量及发生时刻*/
	{0x10610200,	            CLQua2A_Re_De_0,	        C_array,				    1,	            C_structure,           C_NoRateNum       		},  /* A相第二象限最大需量*/
	{0x10610201,	            CLQua2A_Re_De_0,	        C_structure,			    1,	            C_structure,           C_NoRateNum       		},  /* A相第二象限最大需量*/
	{0x10620200,	            CLQua2B_Re_De_0,	        C_array,				    1,	            C_structure,           C_NoRateNum       		},  /* B相第二象限最大需量*/
	{0x10620201,	            CLQua2B_Re_De_0,	        C_structure,			    1,	            C_structure,           C_NoRateNum       		},  /* B相第二象限最大需量*/
	{0x10630200,	            CLQua2C_Re_De_0,	        C_array,				    1,	            C_structure,           C_NoRateNum       		},  /* C相第二象限最大需量*/
	{0x10630201,	            CLQua2C_Re_De_0,	        C_structure,			    1,	            C_structure,           C_NoRateNum       		},  /* C相第二象限最大需量*/
	{CQua3_Re_De_FF_0,	    	CLQua3_Re_De_FF_0,	        C_array,				    C_RatesNumTol,	C_structure,           C_NeedRateNum_FF  		},  /* 第三象限最大需量*/
	{CQua3_Re_Tol_De_0,		    CLQua3_Re_Tol_De_0,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前3象限无功总最大需量及发生时刻*/
	{CQua3_Re_T1_De_0 ,		    CLQua3_Re_T1_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前3象限无功费率1最大需量及发生时刻*/
	{CQua3_Re_T2_De_0 ,		    CLQua3_Re_T2_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前3象限无功费率2最大需量及发生时刻*/
	{CQua3_Re_T3_De_0 ,		    CLQua3_Re_T3_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前3象限无功费率3最大需量及发生时刻*/
	{CQua3_Re_T4_De_0 ,		    CLQua3_Re_T4_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前3象限无功费率4最大需量及发生时刻*/
	{CQua3_Re_T5_De_0 ,		    CLQua3_Re_T5_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前3象限无功费率4最大需量及发生时刻*/
	{CQua3_Re_T6_De_0 ,		    CLQua3_Re_T6_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前3象限无功费率4最大需量及发生时刻*/
	{CQua3_Re_T7_De_0 ,		    CLQua3_Re_T7_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前3象限无功费率4最大需量及发生时刻*/
	{CQua3_Re_T8_De_0 ,		    CLQua3_Re_T8_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前3象限无功费率4最大需量及发生时刻*/
	{CQua3_Re_T9_De_0 ,		    CLQua3_Re_T9_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前3象限无功费率4最大需量及发生时刻*/
	{CQua3_Re_T10_De_0 ,   	    CLQua3_Re_T10_De_0 ,	    C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前3象限无功费率4最大需量及发生时刻*/
	{CQua3_Re_T11_De_0 ,   	    CLQua3_Re_T11_De_0 ,	    C_structure,			    1,	            C_structure,           C_NeedRateNum	    	},  /*当前3象限无功费率4最大需量及发生时刻*/
	{CQua3_Re_T12_De_0 ,   	    CLQua3_Re_T12_De_0 ,	    C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前3象限无功费率4最大需量及发生时刻*/
	{0x10710200,	            CLQua3A_Re_De_0,	        C_array,				    1,	            C_structure,           C_NoRateNum       		},  /* A相第三象限最大需量*/
	{0x10710201,	            CLQua3A_Re_De_0,	        C_structure,			    1,	            C_structure,           C_NoRateNum       		},  /* A相第三象限最大需量*/
	{0x10720200,	            CLQua3B_Re_De_0,	        C_array,				    1,	            C_structure,           C_NoRateNum       		},  /* B相第三象限最大需量*/
	{0x10720201,	            CLQua3B_Re_De_0,	        C_structure,			    1,	            C_structure,           C_NoRateNum       		},  /* B相第三象限最大需量*/
	{0x10730200,	            CLQua3C_Re_De_0,	        C_array,				    1,	            C_structure,           C_NoRateNum       		},  /* C相第三象限最大需量*/
	{0x10730201,	            CLQua3C_Re_De_0,	        C_structure,			    1,	            C_structure,           C_NoRateNum       		},  /* C相第三象限最大需量*/
	{CQua4_Re_De_FF_0,	    	CLQua4_Re_De_FF_0,	        C_array,				    C_RatesNumTol,	C_structure,           C_NeedRateNum_FF  		},  /* 第四象限最大需量*/
	{CQua4_Re_Tol_De_0,		    CLQua4_Re_Tol_De_0,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前4象限无功总最大需量及发生时刻*/
	{CQua4_Re_T1_De_0 ,		    CLQua4_Re_T1_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前4象限无功费率1最大需量及发生时刻*/
	{CQua4_Re_T2_De_0 ,		    CLQua4_Re_T2_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前4象限无功费率2最大需量及发生时刻*/
	{CQua4_Re_T3_De_0 ,		    CLQua4_Re_T3_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前4象限无功费率3最大需量及发生时刻*/
	{CQua4_Re_T4_De_0 ,		    CLQua4_Re_T4_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前4象限无功费率4最大需量及发生时刻*/
	{CQua4_Re_T5_De_0 ,		    CLQua4_Re_T5_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前4象限无功费率4最大需量及发生时刻*/
	{CQua4_Re_T6_De_0 ,		    CLQua4_Re_T6_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前4象限无功费率4最大需量及发生时刻*/
	{CQua4_Re_T7_De_0 ,		    CLQua4_Re_T7_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前4象限无功费率4最大需量及发生时刻*/
	{CQua4_Re_T8_De_0 ,		    CLQua4_Re_T8_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前4象限无功费率4最大需量及发生时刻*/
	{CQua4_Re_T9_De_0 ,		    CLQua4_Re_T9_De_0 ,	        C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前4象限无功费率4最大需量及发生时刻*/
	{CQua4_Re_T10_De_0 ,   	    CLQua4_Re_T10_De_0 ,	    C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前4象限无功费率4最大需量及发生时刻*/
	{CQua4_Re_T11_De_0 ,   	    CLQua4_Re_T11_De_0 ,	    C_structure,			    1,	            C_structure,           C_NeedRateNum	    	},  /*当前4象限无功费率4最大需量及发生时刻*/
	{CQua4_Re_T12_De_0 ,   	    CLQua4_Re_T12_De_0 ,	    C_structure,			    1,	            C_structure,           C_NeedRateNum 			},  /*当前4象限无功费率4最大需量及发生时刻*/
	{0x10810200,	            CLQua4A_Re_De_0,	        C_array,				    1,	            C_structure,           C_NoRateNum       		},  /* A相第四象限最大需量*/
	{0x10810201,	            CLQua4A_Re_De_0,	        C_structure,			    1,	            C_structure,           C_NoRateNum       		},  /* A相第四象限最大需量*/
	{0x10820200,	            CLQua4B_Re_De_0,	        C_array,				    1,	            C_structure,           C_NoRateNum       		},  /* B相第四象限最大需量*/
	{0x10820201,	            CLQua4B_Re_De_0,	        C_structure,			    1,	            C_structure,           C_NoRateNum       		},  /* B相第四象限最大需量*/
	{0x10830200,	            CLQua4C_Re_De_0,	        C_array,				    1,	            C_structure,           C_NoRateNum       		},  /* C相第四象限最大需量*/
	{0x10830201,	            CLQua4C_Re_De_0,	        C_structure,			    1,	            C_structure,           C_NoRateNum       		},  /* C相第四象限最大需量*/

#if 0	/*202011原程序屏蔽，按编程规范修改为条件编译*/
	{0x10900200,	            40,					        C_array,				    5,	            C_structure				},  /* 正向视在最大需量*/
	{0x10900201,	            8,					        C_structure,			    1,	            C_structure				},  /* 正向视在总最大需量*/
	{0x10900202,	            8,					        C_structure,			    1,	            C_structure				},  /* 正向视在费率1最大需量*/
	{0x10900203,	            8,					        C_structure,			    1,	            C_structure				},  /* 正向视在费率2最大需量*/
	{0x10900204,	            8,					        C_structure,			    1,	            C_structure				},  /* 正向视在费率3最大需量*/
	{0x10900205,	            8,					        C_structure,			    1,	            C_structure				},  /* 正向视在费率4最大需量*/
	{0x10910200,	            8,					        C_structure,			    1,	            C_structure				},  /* A相正向视在最大需量*/
	{0x10920200,	            8,					        C_structure,			    1,	            C_structure				},  /* B相正向视在最大需*/
	{0x10930200,	            8,					        C_structure,			    1,	            C_structure				},  /* C相正向视在最大需量*/
	{0x10A00200,	            40,					        C_array,				    5,	            C_structure				},  /* 反向视在最大需量*/
	{0x10A00201,	            8,					        C_structure,			    1,	            C_structure				},  /* 反向视在总最大需量*/
	{0x10A00202,	            8,					        C_structure,			    1,	            C_structure				},  /* 反向视在费率1最大需量*/
	{0x10A00203,	            8,					        C_structure,			    1,	            C_structure				},  /* 反向视在费率2最大需量*/
	{0x10A00204,	            8,					        C_structure,			    1,	            C_structure				},  /* 反向视在费率3最大需量*/
	{0x10A00205,	            8,					        C_structure,			    1,	            C_structure				},  /* 反向视在费率4最大需量*/
	{0x10A10200,	            8,					        C_structure,			    1,	            C_structure				},  /* A 相反向视在最大需量*/
	{0x10A20200,	            8,					        C_structure,			    1,	            C_structure				},  /* B相反向视在最大需量*/
	{0x10A30200,	            8,					        C_structure,			    1,	            C_structure				},  /* C相反向视在最大需量*/
	{0x11100200,	            CLPos_Ac_De_FF_1,	        C_array,				    5,	            C_structure				},  /* 冻结周期内正向有功最大需量*/
	{0x11100201,	            CLPos_Ac_Tol_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内正向有功总最大需量*/
	{0x11100202,	            CLPos_Ac_T1_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内正向有功费率1最大需量*/
	{0x11100203,	            CLPos_Ac_T2_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内正向有功费率2最大需量*/
	{0x11100204,	            CLPos_Ac_T3_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内正向有功费率3最大需量*/
	{0x11100205,	            CLPos_Ac_T4_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内正向有功费率4最大需量*/
	{0x11110200,	            CLPosA_Ac_De_1,		        C_structure,			    1,	            C_structure				},  /* 冻结周期内A相正向有功最大需量*/
	{0x11120200,	            CLPosB_Ac_De_1,		        C_structure,			    1,	            C_structure				},  /* 冻结周期内B相正向有功最大需量*/
	{0x11130200,	            CLPosC_Ac_De_1,		        C_structure,			    1,	            C_structure				},  /* 冻结周期内C相正向有功最大需量*/
	{0x11200200,	            CLRev_Ac_De_FF_1,	        C_array,				    5,	            C_structure				},  /* 冻结周期内反向有功最大需量*/
	{0x11200201,	            CLRev_Ac_Tol_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内反向有功总最大需量*/
	{0x11200202,	            CLRev_Ac_T1_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内反向有功费率1最大需量*/
	{0x11200203,	            CLRev_Ac_T2_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内反向有功费率2最大需量*/
	{0x11200204,	            CLRev_Ac_T3_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内反向有功费率3最大需量*/
	{0x11200205,	            CLRev_Ac_T4_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内反向有功费率4最大需量*/
	{0x11210200,	            CLRevA_Ac_De_1,		        C_structure,			    1,	            C_structure				},  /* 冻结周期内A相反向有功最大需量*/
	{0x11220200,	            CLRevB_Ac_De_1,		        C_structure,			    1,	            C_structure				},  /* 冻结周期内B相反向有功最大需量*/
	{0x11230200,	            CLRevC_Ac_De_1,		        C_structure,			    1,	            C_structure				},  /* 冻结周期内C相反向有功最大需量*/
	{0x11300200,	            CLCom_Re1_De_FF_1,	        C_array,				    5,	            C_structure				},  /* 冻结周期内组合无功*/
	{0x11300201,	            CLCom_Re1_Tol_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内组合无功1总*/
	{0x11300202,	            CLCom_Re1_T1_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内组合无功1费率1*/
	{0x11300203,	            CLCom_Re1_T2_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内组合无功1费率2*/
	{0x11300204,	            CLCom_Re1_T3_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内组合无功1费率3*/
	{0x11300205,	            CLCom_Re1_T4_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内组合无功1费率4*/
	{0x11310200,	            CLComA_Re1_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内A相组合无功1最大需量*/
	{0x11320200,	            CLComB_Re1_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内B相组合无功1最大需量*/
	{0x11330200,	            CLComC_Re1_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内C相组合无功1最大需量*/
	{0x11400200,	            CLCom_Re2_De_FF_1,	        C_array,				    5,	            C_structure				},  /* 冻结周期内组合无功2最大需量*/
	{0x11400201,	            CLCom_Re2_Tol_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内组合无功2总最大需量*/
	{0x11400202,	            CLCom_Re2_T1_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内组合无功2费率1最大需量*/
	{0x11400203,	            CLCom_Re2_T2_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内组合无功2费率2最大需量*/
	{0x11400204,	            CLCom_Re2_T3_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内组合无功2费率3最大需量*/
	{0x11400205,	            CLCom_Re2_T4_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内组合无功2费率4最大需量*/
	{0x11410200,	            CLComA_Re2_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内A相组合无功2最大需量*/
	{0x11420200,	            CLComB_Re2_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内B相组合无功2最大需量*/
	{0x11430200,	            CLComC_Re2_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内C相组合无功2最大需量*/
	{0x11500200,	            CLQua1_Re_De_FF_1,	        C_array,				    5,	            C_structure				},  /* 冻结周期内第一象限最大需量*/
	{0x11500201,	            CLQua1_Re_Tol_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内第一象限总最大需量*/
	{0x11500202,	            CLQua1_Re_T1_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内第一象限费率1最大需量*/
	{0x11500203,	            CLQua1_Re_T2_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内第一象限费率2最大需量*/
	{0x11500204,	            CLQua1_Re_T3_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内第一象限费率3最大需量*/
	{0x11500205,	            CLQua1_Re_T4_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内第一象限费率4最大需量*/
	{0x11510200,	            CLQua1A_Re_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内A相第一象限最大需量*/
	{0x11520200,	            CLQua1B_Re_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内B相第一象限最大需量*/
	{0x11530200,	            CLQua1C_Re_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内C相第一象限最大需量*/
	{0x11600200,	            CLQua2_Re_De_FF_1,	        C_array,				    5,	            C_structure				},  /* 冻结周期内第二象限最大需量*/
	{0x11600201,	            CLQua2_Re_Tol_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内第二象限总最大需量*/
	{0x11600202,	            CLQua2_Re_T1_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内第二象限费率1最大需量*/
	{0x11600203,	            CLQua2_Re_T2_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内第二象限费率2最大需量*/
	{0x11600204,	            CLQua2_Re_T3_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内第二象限费率3最大需量*/
	{0x11600205,	            CLQua2_Re_T4_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内第二象限费率4最大需量*/
	{0x11610200,	            CLQua2A_Re_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内A相第二象限最大需量*/
	{0x11620200,	            CLQua2B_Re_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内B相第二象限最大需量*/
	{0x11630200,	            CLQua2C_Re_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内C相第二象限最大需量*/
	{0x11700200,	            CLQua3_Re_De_FF_1,	        C_array,				    5,	            C_structure				},  /* 冻结周期内第三象限最大需量*/
	{0x11700201,	            CLQua3_Re_Tol_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内第三象限总最大需量*/
	{0x11700202,	            CLQua3_Re_T1_De_1, 	        C_structure,			    1,	            C_structure				},  /* 冻结周期内第三象限费率1最大需量*/
	{0x11700203,	            CLQua3_Re_T2_De_1, 	        C_structure,			    1,	            C_structure				},  /* 冻结周期内第三象限费率2最大需量*/
	{0x11700204,	            CLQua3_Re_T3_De_1, 	        C_structure,			    1,	            C_structure				},  /* 冻结周期内第三象限费率3最大需量*/
	{0x11700205,	            CLQua3_Re_T4_De_1, 	        C_structure,			    1,	            C_structure				},  /* 冻结周期内第三象限费率4最大需量*/
	{0x11710200,	            CLQua3A_Re_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内A相第三象限最大需量*/
	{0x11720200,	            CLQua3B_Re_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内B相第三象限最大需量*/
	{0x11730200,	            CLQua3C_Re_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内C相第三象限最大需量*/
	{0x11800200,	            CLQua4_Re_De_FF_1,	        C_array,				    5,	            C_structure				},  /* 冻结周期内第四象限最大需量*/
	{0x11800201,	            CLQua4_Re_Tol_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内第四象限总最大需量*/
	{0x11800202,	            CLQua4_Re_T1_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内第四象限费率1最大需量*/
	{0x11800203,	            CLQua4_Re_T2_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内第四象限费率2最大需量*/
	{0x11800204,	            CLQua4_Re_T3_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内第四象限费率3最大需量*/
	{0x11800205,	            CLQua4_Re_T4_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内第四象限费率4最大需量*/
	{0x11810200,	            CLQua4A_Re_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内A相第四象限最大需量*/
	{0x11820200,	            CLQua4B_Re_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内B相第四象限最大需量*/
	{0x11830200,	            CLQua4C_Re_De_1,	        C_structure,			    1,	            C_structure				},  /* 冻结周期内C相第四象限最大需量*/
	{0x11900200,	            40,					        C_array,				    5,	            C_structure				},  /* 冻结周期内正向视在最大需量*/
	{0x11900201,	            8,					        C_structure,			    1,	            C_structure				},  /* 冻结周期内正向视在总最大需量*/
	{0x11900202,	            8,					        C_structure,			    1,	            C_structure				},  /* 冻结周期内正向视在费率1最大需量*/
	{0x11900203,	            8,					        C_structure,			    1,	            C_structure				},  /* 冻结周期内正向视在费率2最大需量*/
	{0x11900204,	            8,					        C_structure,			    1,	            C_structure				},  /* 冻结周期内正向视在费率3最大需量*/
	{0x11900205,	            8,					        C_structure,			    1,	            C_structure				},  /* 冻结周期内正向视在费率4最大需量*/
	{0x11910200,	            8,					        C_structure,			    1,	            C_structure				},  /* 冻结周期内A相正向视在最大需量*/
	{0x11920200,	            8,					        C_structure,			    1,	            C_structure				},  /* 冻结周期内B相正向视在最大需量*/
	{0x11930200,	            8,					        C_structure,			    1,	            C_structure				},  /* 冻结周期内C相正向视在最大需量*/
	{0x11A00200,	            40,					        C_array,				    5,	            C_structure				},  /* 冻结周期内反向视在最大需量*/
	{0x11A00201,	            8,					        C_structure,			    1,	            C_structure				},  /* 冻结周期内反向视在总最大需量*/
	{0x11A00202,	            8,					        C_structure,			    1,	            C_structure				},  /* 冻结周期内反向视在费率1最大需量*/
	{0x11A00203,	            8,					        C_structure,			    1,	            C_structure				},  /* 冻结周期内反向视在费率2最大需量*/
	{0x11A00204,	            8,					        C_structure,			    1,	            C_structure				},  /* 冻结周期内反向视在费率3最大需量*/
	{0x11A00205,	            8,					        C_structure,			    1,	            C_structure				},  /* 冻结周期内反向视在费率4最大需量*/
	{0x11A10200,	            8,					        C_structure,			    1,	            C_structure				},  /* 冻结周期内A相反向视在最大需量*/
	{0x11A20200,	            8,					        C_structure,			    1,	            C_structure				},  /* 冻结周期内B相反向视在最大需量*/
	{0x11A30200,	            8,					        C_structure,			    1,	            C_structure				},  /* 冻结周期内C相反向视在最大需量*/
	{0x11100201,	            8,					        C_structure,			    2,	            C_structure				},  /* 冻结周期内正向有功最大需量*/
	{0x11200201,	            8,					        C_structure,			    2,	            C_structure				},  /* 冻结周期内反向有功最大需量*/
#endif

	{0x20000200,	            CLPhaseFF_Volage,	        C_array,				    3,	            C_long_unsigned,       C_NoRateNum              },  /* 电压*/
    {0x20000201,	            CLPhaseA_Volage,	        C_long_unsigned,		    0,	            C_long_unsigned,       C_NoRateNum              },  /*A相电压*/
	{0x20000202,	            CLPhaseB_Volage,	        C_long_unsigned,		    0,	            C_long_unsigned,       C_NoRateNum              },  /*B相电压*/
	{0x20000203,	            CLPhaseC_Volage,	        C_long_unsigned,		    0,	            C_long_unsigned,       C_NoRateNum              },  /*C相电压*/
	{0x20010200,	            CLPhaseFF_Curr,		        C_array,				    3,	            C_double_long,         C_NoRateNum              },  /* 电流*/
	{0x20010201,	            CLPhaseA_Curr,		        C_double_long,			    0,	            C_double_long,         C_NoRateNum              },  /*A相电流*/
	{0x20010202,	            CLPhaseB_Curr,		        C_double_long,			    0,	            C_double_long,         C_NoRateNum              },  /*B相电流*/
	{0x20010203,	            CLPhaseC_Curr,		        C_double_long,			    0,	            C_double_long,         C_NoRateNum              },  /*C相电流*/
	{0x20010400,	            CLZero_Current,		        C_double_long,			    0,	            C_double_long,		   C_NoRateNum              },  /*零线电流*/
	{0x20020200,	            CLPhaseFF_Angle,			C_array,				    3,	            C_long_unsigned,	   C_NoRateNum              },  /* 电压相角*/
	{0x20020201,	            CLPhaseA_Angle,			    C_long_unsigned,		    0,	            C_long_unsigned,	   C_NoRateNum              },  /* A电压相角*/
	{0x20020202,	            CLPhaseB_Angle,			    C_long_unsigned,		    0,	            C_long_unsigned,	   C_NoRateNum              },  /* B电压相角*/
	{0x20020203,	            CLPhaseC_Angle,			    C_long_unsigned,		    0,	            C_long_unsigned,	   C_NoRateNum              },  /* C电压相角*/
	{0x20030200,	            CLPhaseFF_Angle,	        C_array,				    3,	            C_long_unsigned,	   C_NoRateNum              },  /* 电压流相角*/
	{0x20030201,	            CLPhaseA_Angle,		        C_long_unsigned,		    0,	            C_long_unsigned,	   C_NoRateNum              },  /* A电压流相角*/
	{0x20030202,	            CLPhaseB_Angle,		        C_long_unsigned,		    0,	            C_long_unsigned,	   C_NoRateNum              },  /* B电压流相角*/
	{0x20030203,	            CLPhaseC_Angle,		        C_long_unsigned,		    0,	            C_long_unsigned,	   C_NoRateNum              },  /* C电压流相角*/
	{0x20040200,	            CLInstantFF_AcPow,	        C_array,				    4,	            C_double_long,		   C_NoRateNum              },  /* 有功功率*/
	{0x20040201,	            CLInstant_TolAcPow,	        C_double_long,			    0,	            C_double_long,		   C_NoRateNum              },  /*瞬时总有功功率*/
	{0x20040202,	            CLInstantA_AcPow  ,	        C_double_long,			    0,	            C_double_long,		   C_NoRateNum              },  /*A相瞬时有功功率*/
	{0x20040203,	            CLInstantB_AcPow  ,	        C_double_long,			    0,	            C_double_long,		   C_NoRateNum              },  /*B相瞬时有功功率*/
	{0x20040204,	            CLInstantC_AcPow  ,	        C_double_long,			    0,	            C_double_long,		   C_NoRateNum              },  /*C相瞬时有功功率*/
	{0x20050200,	            CLInstantFF_RePow,	        C_array,				    4,	            C_double_long,		   C_NoRateNum              },  /* 无功功率*/
  	{0x20050201,	            CLInstant_TolRePow,	        C_double_long,			    0,	            C_double_long,		   C_NoRateNum              },  /*瞬时总无功功率*/
	{0x20050202,	            CLInstantA_RePow  ,	        C_double_long,			    0,	            C_double_long,		   C_NoRateNum              },  /*A相瞬时无功功率*/
	{0x20050203,	            CLInstantB_RePow  ,	        C_double_long,			    0,	            C_double_long,		   C_NoRateNum              },  /*B相瞬时无功功率*/
	{0x20050204,	            CLInstantC_RePow  ,	        C_double_long,			    0,	            C_double_long,		   C_NoRateNum              },  /*C相瞬时无功功率*/
	{0x20060200,	            CLInstantFF_AppaPow,        C_array,				    4,	            C_double_long,		   C_NoRateNum              },  /* 视在功率*/
	{0x20060201,	            CLInstant_TolAppaPow,       C_double_long,			    0,	            C_double_long,		   C_NoRateNum              },  /*瞬时总视在功率*/
	{0x20060202,	            CLInstantA_AppaPow,	        C_double_long,			    0,	            C_double_long,		   C_NoRateNum              },  /*A相瞬时视在功率*/
	{0x20060203,	            CLInstantB_AppaPow,	        C_double_long,			    0,	            C_double_long,		   C_NoRateNum              },  /*B相瞬时视在功率*/
	{0x20060204,	            CLInstantC_AppaPow,	        C_double_long,			    0,	            C_double_long,		   C_NoRateNum              },  /*C相瞬时视在功率*/
	{0x20070200,	            CLOneMin_AcPower,	        C_double_long,			    0,	            C_double_long,		   C_NoRateNum              },  /* 一分钟平均有功率*/
	{0x20080200,	            CLOneMin_AcPower,	        C_double_long,			    0,	            C_double_long,		   C_NoRateNum              },  /* 一分钟平均无功率*/
	{0x20090200,	            CLOneMin_AcPower,	        C_double_long,			    0,	            C_double_long,		   C_NoRateNum              },  /* 一分钟平均视在功率*/
	{0x200A0200,	            CLPhaseFF_PowerFactor,      C_array,				    4,	            C_long,				   C_NoRateNum              },  /* 功率因数*/
	{0x200A0201,	            CLTol_PowerFactor   ,       C_long,				        0,	            C_long,				   C_NoRateNum              },  /*总功率因数*/
	{0x200A0202,	            CLPhaseA_PowerFactor,       C_long,				        0,	            C_long,				   C_NoRateNum              },  /*A相功率因数*/
	{0x200A0203,	            CLPhaseB_PowerFactor,       C_long,				        0,	            C_long,				   C_NoRateNum              },  /*B相功率因数*/
	{0x200A0204,	            CLPhaseC_PowerFactor,       C_long,				        0,	            C_long,				   C_NoRateNum              },  /*C相功率因数*/

#if 0	/*202011原程序屏蔽，按编程规范修改为条件编译*/
	{0x200B0200,	            6,					        C_array,				    3,	            C_long					},  /* 电压波形失真度*/
	{0x200B0201,	            2,					        C_long,					    0,	            C_long					},  /* A电压波形失真度*/
	{0x200B0202,	            2,					        C_long,					    0,	            C_long					},  /* B电压波形失真度*/
	{0x200B0203,	            2,					        C_long,					    0,	            C_long					},  /* C电压波形失真度*/
	{0x200C0200,	            6,					        C_array,				    3,	            C_long					},  /* 电流波形失真度*/
	{0x200C0201,	            2,					        C_long,					    0,	            C_long					},  /* A电流波形失真度*/
	{0x200C0202,	            2,					        C_long,					    0,	            C_long					},  /* B电流波形失真度*/
	{0x200C0203,	            2,					        C_long,					    0,	            C_long					},  /* C电流波形失真度*/
	{0x200D0200,	            2,					        C_long,					    0,	            C_long					},  /* 电压谐波含有量（总及 2…n次）*/
	{0x200E0200,	            2,					        C_long,					    0,	            C_long					},  /* 电流谐波含有量（总及2…n次）*/
#endif

	{0x200F0200,	            CLElecNet_Freq,		        C_long_unsigned,		    0,	            C_long_unsigned,		C_NoRateNum             },  /* 电网频率*/
	{0x20100200,	            CLMeter_Temp,		        C_long,					    0,	            C_long,					C_NoRateNum             },  /* 表内温度*/
	{0x20110200,	            CLCloc_Batt_Vol,	        C_long_unsigned,		    0,	            C_long_unsigned,		C_NoRateNum             },  /* 时钟电池压*/
	{0x20120200,	            CLReadMeter_Batt_Vol,       C_long_unsigned,		    0,	            C_long_unsigned,		C_NoRateNum             },  /* 停电抄表池压*/
	{0x20130200,	            CLBatt_Work_Time,	        C_double_long_unsigned,	    0,	            C_double_long_unsigned,	C_NoRateNum             },  /* 时钟电池工作间*/
	{0x20140200,	            14,					        C_array,				    7,	            C_bit_string,			C_NoRateNum             },  /* 电能表运行状态字（1-8）*/
	{0x20140201,	            CLMeter_Work_State1,        C_bit_string,			    16,	            C_bit_string,			C_NoRateNum             },  /*电表运行状态字1*/
	{0x20140202,	            CLMeter_Work_State2,        C_bit_string,			    16,	            C_bit_string,			C_NoRateNum             },  /*电表运行状态字2*/
	{0x20140203,	            CLMeter_Work_State3,        C_bit_string,			    16,	            C_bit_string,			C_NoRateNum             },  /*电表运行状态字3*/
	{0x20140204,	            CLMeter_Work_State4,        C_bit_string,			    16,	            C_bit_string,			C_NoRateNum             },  /*电表运行状态字4*/
	{0x20140205,	            CLMeter_Work_State5,        C_bit_string,			    16,	            C_bit_string,			C_NoRateNum             },  /*电表运行状态字5*/
	{0x20140206,	            CLMeter_Work_State6,        C_bit_string,			    16,	            C_bit_string,			C_NoRateNum             },  /*电表运行状态字6*/
	{0x20140207,	            CLMeter_Work_State7,        C_bit_string,			    16,	            C_bit_string,			C_NoRateNum             },  /*电表运行状态字7*/
	{0x20170200,	            CLCurr_AcDemand,	        C_double_long,			    0,	            C_double_long,  		C_NoRateNum             },  /* 当前有功需量*/
	{0x20180200,	            CLCurr_ReDemand,	        C_double_long,			    0,	            C_double_long,  		C_NoRateNum             },  /* 当前无功需量*/
	{0x20190200,	            CLCurr_AppaDemand,	        C_double_long,			    0,	            C_double_long,  		C_NoRateNum             },  /* 当前视在需量*/
	{0x201A0200,	            CLCurr_Price,		        C_double_long_unsigned,	    0,	            C_double_long_unsigned,	C_NoRateNum             },  /* 当前电价*/
	{0x201B0200,	            CLCurr_Rate_Price,	        C_double_long_unsigned,	    0,	            C_double_long_unsigned,	C_NoRateNum             },  /* 当前费率*/
	{0x201C0200,	            CLCurr_Ladder_Price,        C_double_long_unsigned,	    0,	            C_double_long_unsigned,	C_NoRateNum             },  /* 当前阶梯电价*/
	{0x20260200,	            CLNoBal_Vol_Lim,			C_long_unsigned,		    0,	            C_long_unsigned,        C_NoRateNum             },  /* 电压不平衡率*/
	{0x20270200,	            CLNoBal_Curr_Lim,			C_long_unsigned,		    0,	            C_long_unsigned,        C_NoRateNum             },  /* 电流不平衡率*/

#if 0	/*202011原程序屏蔽，按编程规范修改为条件编译*/
	{0x20280200,	            0xFF,				        C_long_unsigned,		    0,	            C_long_unsigned			},  /* 负载率*/
#endif

	{0x20290200,	            16,				            C_array,				    4,	            C_double_long_unsigned, C_NoRateNum             },  /* 安时值*/
	{0x20290201,	            4,				            C_double_long_unsigned,	    0,	            C_double_long_unsigned, C_NoRateNum             },  /* 安时值*/
	{0x20290202,	            4,				            C_double_long_unsigned,	    0,	            C_double_long_unsigned, C_NoRateNum             },  /* 安时值*/
	{0x20290203,	            4,				            C_double_long_unsigned,	    0,	            C_double_long_unsigned, C_NoRateNum             },  /* 安时值*/
	{0x20290204,	            4,				            C_double_long_unsigned,	    0,	            C_double_long_unsigned, C_NoRateNum             },  /* 安时值*/
    {0x202C0200,	            (CLChargeBal_BCD+CLBuyCurr_Degree),	   C_structure,     2,	            C_double_long_unsigned, C_NoRateNum             },  /* （当前）钱包文件*/
	{0x202C0201,	            CLChargeBal_BCD,	        C_double_long_unsigned,	    0,	            C_double_long_unsigned, C_NoRateNum             },  /* 剩余金额*/
	{0x202C0202,	            CLBuyCurr_Degree,	        C_double_long_unsigned,	    0,	            C_double_long_unsigned, C_NoRateNum             },  /* 购电次数*/
	{0x202D0200,	            CLOverDraft_BCD,	        C_double_long_unsigned,	    0,	            C_double_long_unsigned, C_NoRateNum             },  /* （当前）透支金额*/
	{0x202E0200,	            CLBuyCurr_TMoney_1,	        C_double_long_unsigned,	    0,	            C_double_long_unsigned, C_NoRateNum             },  /* 累计购电金额*/
	{0x20310200,	            CLM_Com_Ac_Tol_En_0,        C_double_long_unsigned,	    0,	            C_double_long_unsigned, C_NoRateNum             },  /* 月度用电量*/
	{0x20320200,	            CLY_Com_Ac_Tol_En_0,		C_double_long_unsigned,	    1,	            C_double_long_unsigned, C_NoRateNum             },  /* 阶梯结算用电量*/
	{0x20400200,	            CLControl_ExecuteState,		C_bit_string,			    16,	            C_bit_string,			C_NoRateNum             },  /* 控制命令执行状态字*/
	{0x20410200,	            CLControl_ErrorState,		C_bit_string,			    16,	            C_bit_string,			C_NoRateNum             },  /* 控制命令错误状态字*/
	{0x21310200,	            CLVolA_Per_Pass_FF,			C_structure,			    2,	            C_structure,		    C_NoRateNum             },  /* A相电压合格率*/
	{0x21310201,	            CLVolA_Per_Pass_D,			C_structure,			    0,	            C_double_long_unsigned,	C_NoRateNum             },  /* A相日电压合格率*/
	{0x21310202,	            CLVolA_Per_Pass_M,			C_structure,			    0,	            C_double_long_unsigned,	C_NoRateNum             },  /* A相月电压合格率*/
	{0x21320200,	            CLVolB_Per_Pass_FF,			C_structure,			    2,	            C_structure,		    C_NoRateNum             },  /* B相电压合格率*/
	{0x21320201,	            CLVolB_Per_Pass_D,			C_structure,			    0,	            C_double_long_unsigned,	C_NoRateNum             },  /* B相日电压合格率*/
	{0x21320202,	            CLVolB_Per_Pass_M,			C_structure,			    0,	            C_double_long_unsigned,	C_NoRateNum             },  /* B相月电压合格率*/
	{0x21330200,	            CLVolC_Per_Pass_FF,			C_structure,			    2,	            C_structure,		    C_NoRateNum             },  /* C相电压合格率*/
	{0x21330201,	            CLVolC_Per_Pass_D,			C_structure,			    0,	            C_double_long_unsigned,	C_NoRateNum             },  /* C相日电压合格率*/
	{0x21330202,	            CLVolC_Per_Pass_M,			C_structure,			    0,	            C_double_long_unsigned,	C_NoRateNum             },  /* C相月电压合格率*/

#if 0	/*202011原程序屏蔽，按编程规范修改为条件编译*/
	{0x21400200,	            0xFF,				        C_structure,			    2,	            C_structure,			C_NoRateNum},  /* 日最大有功率及发生时间*/
	{0x21410200,	            0xFF,				        C_structure,			    2,              C_structure,                       },  /* 月最大有功率及发生时间*/
	{0x22030200,	            0xFF,				        C_structure,			    2,	            C_long_unsigned,                   },  /* 供电时间*/
	{0x22040200,	            0xFF,				        C_structure,			    2,	            C_long_unsigned,		           },  /* 复位次数*/
	{0x25040200,	            0xFF,				        C_double_long_unsigned,	    1,	            C_double_long_unsigned,            },  /* 累计工作时间*/
#endif

   	{0x40140200,	            CLFirst_TZone_Data,	        C_array,				    14,	            C_TZone,				C_NoRateNum             },  /* 当前套时区表*/
   	{0x40150200,	            CLSec_TZone_Data,	        C_array,				    14,	            C_TZone,				C_NoRateNum             },  /* 备用套时区表*/
    {0x40140201,	            3,	                        C_TZone,				    3,	            C_TZone,				C_NoRateNum             },  /* 当前套时区表*/
   	{0x40150201,	            3,	                        C_TZone,				    3,	            C_TZone,				C_NoRateNum             },  /* 备用套时区表*/
    {0x40160200,	            CLFirst_TZone_Data,	        C_array,				    8,	            C_TZone,				C_NoRateNum             },  /* 当前套时段表*/
   	{0x40170200,	            CLSec_TZone_Data,	        C_array,				    8,	            C_TZone,				C_NoRateNum             },  /* 备用套时段表*/
   	{0x41160200,	            6,					        C_array,				    3,	            C_SettleDay,			C_NoRateNum             },  /* 结算日*/
    {0x41160201,	            2,					        C_structure,			    1,	            C_SettleDay,			C_NoRateNum             },  /* 结算日*/
   	{0x41160202,	            2,					        C_structure,			    1,	            C_SettleDay,			C_NoRateNum             },  /* 结算日*/
   	{0x41160203,	            2,					        C_structure,			    1,	            C_SettleDay,			C_NoRateNum             },  /* 结算日*/
   	{0x40130200,	            CLWeek_RestDay_DTable,	    C_unsigned,				    1,	            C_unsigned,			    C_NoRateNum             },  /* 周休日采用的日时段表号*/
   	{0x41120200,	            CLActive_Com_State,		    C_bit_string,			    8,	            C_bit_string,			C_NoRateNum             },  /* 有功组合方式特征字*/
   	{0x41130200,	            CLReactive_Com_State1,	    C_bit_string,			    8,	            C_bit_string,			C_NoRateNum             },  /* 无功组合方式特征字1*/
   	{0x41140200,	            CLReactive_Com_State2,	    C_bit_string,			    8,	            C_bit_string,			C_NoRateNum             },  /* 无功组合方式特征字2*/
   	{0x40000200,	            CLDate_Week_Time,	        C_date_time_s,			    7,	            C_date_time_s,			C_NoRateNum             },  /* 时间*/
   	{CCurrent_RateFF_Price,	    CLCurrent_RateFF_Price,	    C_array,				    C_MaxRatesNum,	C_double_long_unsigned,	C_NeedRateNumPrice_FF   },  /* 当前套费率电价*/
    {CCurrent_Rate1_Price,	    CLCurrent_Rate1_Price,	    C_double_long_unsigned,     0,	            C_double_long_unsigned,	C_NeedRateNumPrice 	    },  /* 当前套费率电价*/
   	{CCurrent_Rate2_Price,	    CLCurrent_Rate2_Price,	    C_double_long_unsigned,     0,	            C_double_long_unsigned,	C_NeedRateNumPrice 	    },  /* 当前套费率电价*/
   	{CCurrent_Rate3_Price,	    CLCurrent_Rate3_Price,	    C_double_long_unsigned,     0,	            C_double_long_unsigned,	C_NeedRateNumPrice 	    },  /* 当前套费率电价*/
   	{CCurrent_Rate4_Price,	    CLCurrent_Rate4_Price,	    C_double_long_unsigned,     0,	            C_double_long_unsigned,	C_NeedRateNumPrice 	    },  /* 当前套费率电价*/
   	{CCurrent_Rate5_Price,	    CLCurrent_Rate5_Price,	    C_double_long_unsigned,     0,	            C_double_long_unsigned,	C_NeedRateNumPrice 	    },  /* 当前套费率电价*/
   	{CCurrent_Rate6_Price,	    CLCurrent_Rate6_Price,	    C_double_long_unsigned,     0,	            C_double_long_unsigned,	C_NeedRateNumPrice 	    },  /* 当前套费率电价*/
   	{CCurrent_Rate7_Price,	    CLCurrent_Rate7_Price,	    C_double_long_unsigned,     0,	            C_double_long_unsigned,	C_NeedRateNumPrice 	    },  /* 当前套费率电价*/
   	{CCurrent_Rate8_Price,	    CLCurrent_Rate8_Price,	    C_double_long_unsigned,     0,	            C_double_long_unsigned,	C_NeedRateNumPrice 	    },  /* 当前套费率电价*/
   	{CCurrent_Rate9_Price,	    CLCurrent_Rate9_Price,	    C_double_long_unsigned,     0,	            C_double_long_unsigned,	C_NeedRateNumPrice 	    },  /* 当前套费率电价*/
   	{CCurrent_Rate10_Price,		CLCurrent_Rate10_Price,	    C_double_long_unsigned,     0,	            C_double_long_unsigned,	C_NeedRateNumPrice 	    },  /* 当前套费率电价*/
   	{CCurrent_Rate11_Price,		CLCurrent_Rate11_Price,	    C_double_long_unsigned,     0,	            C_double_long_unsigned,	C_NeedRateNumPrice 	    },  /* 当前套费率电价*/
   	{CCurrent_Rate12_Price,		CLCurrent_Rate12_Price,	    C_double_long_unsigned,     0,	            C_double_long_unsigned,	C_NeedRateNumPrice	    },  /* 当前套费率电价*/
  	{CBackUp_RateFF_Price,		CLBackUp_RateFF_Price,	    C_array,				    C_MaxRatesNum,	C_double_long_unsigned,	C_NeedRateNumPrice_FF   },  /* 备用套费率电价*/
    {CBackUp_Rate1_Price,		CLBackUp_Rate1_Price,	    C_double_long_unsigned,	    0,	            C_double_long_unsigned,	C_NeedRateNumPrice 	    },  /* 备用套费率电价*/
    {CBackUp_Rate2_Price,		CLBackUp_Rate2_Price,	    C_double_long_unsigned,	    0,	            C_double_long_unsigned,	C_NeedRateNumPrice 	    },  /* 备用套费率电价*/
    {CBackUp_Rate3_Price,		CLBackUp_Rate3_Price,	    C_double_long_unsigned,	    0,	            C_double_long_unsigned,	C_NeedRateNumPrice 	    },  /* 备用套费率电价*/
    {CBackUp_Rate4_Price,		CLBackUp_Rate4_Price,	    C_double_long_unsigned,	    0,	            C_double_long_unsigned,	C_NeedRateNumPrice 	    },  /* 备用套费率电价*/
    {CBackUp_Rate5_Price,		CLBackUp_Rate5_Price,	    C_double_long_unsigned,	    0,	            C_double_long_unsigned,	C_NeedRateNumPrice 	    },  /* 备用套费率电价*/
    {CBackUp_Rate6_Price,		CLBackUp_Rate6_Price,	    C_double_long_unsigned,	    0,	            C_double_long_unsigned,	C_NeedRateNumPrice 	    },  /* 备用套费率电价*/
    {CBackUp_Rate7_Price,		CLBackUp_Rate7_Price,	    C_double_long_unsigned,	    0,	            C_double_long_unsigned,	C_NeedRateNumPrice 	    },  /* 备用套费率电价*/
    {CBackUp_Rate8_Price,		CLBackUp_Rate8_Price,	    C_double_long_unsigned,	    0,	            C_double_long_unsigned,	C_NeedRateNumPrice 	    },  /* 备用套费率电价*/
    {CBackUp_Rate9_Price,		CLBackUp_Rate9_Price,	    C_double_long_unsigned,	    0,	            C_double_long_unsigned,	C_NeedRateNumPrice 	    },  /* 备用套费率电价*/
    {CBackUp_Rate10_Price,		CLBackUp_Rate10_Price,	    C_double_long_unsigned,	    0,	            C_double_long_unsigned,	C_NeedRateNumPrice 	    },  /* 备用套费率电价*/
    {CBackUp_Rate11_Price,		CLBackUp_Rate11_Price,	    C_double_long_unsigned,	    0,	            C_double_long_unsigned,	C_NeedRateNumPrice 	    },  /* 备用套费率电价*/
    {CBackUp_Rate12_Price,		CLBackUp_Rate12_Price,	    C_double_long_unsigned,	    0,	            C_double_long_unsigned,	C_NeedRateNumPrice	    },  /* 备用套费率电价*/
   	{0x401A0200,	            CLCurrent_Ladder_Table,	    C_Ladder_Table,				4,	            C_double_long_unsigned,	C_NoRateNum		        },  /* 当前套阶梯电价*/
   	{0x401B0200,	            CLBackUp_Ladder_Table,	    C_Ladder_Table,				4,	            C_double_long_unsigned,	C_NoRateNum		        },  /* 备用套阶梯电价*/
    {C_RelayFa_State,           CLRelayUnit,                C_structure,                4,              C_structure,            C_NoRateNum             },  /*继电器输出*/
    {0xF1000400,                16,                         C_octet_string,             16,             C_octet_string,         C_NoRateNum             },  /*更新前密钥状态字*/
	{CCom_Ac_PreEn_FF_0 ,	    CLCom_Ac_PreEn_FF_0 ,	    C_array,			        C_RatesNumTol,	C_long64,      			C_NeedRateNum_FF        },  /*组合有功精确电能*/
	{CCom_Ac_Tol_PreEn_0,	    CLCom_Ac_Tol_PreEn_0,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum 	        },  /*当前组合有功总精确电能*/
	{CCom_Ac_T1_PreEn_0 ,	    CLCom_Ac_T1_PreEn_0 ,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum 	        },  /*当前组合有功费率1精确电能*/
	{CCom_Ac_T2_PreEn_0 ,	    CLCom_Ac_T2_PreEn_0 ,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum 	        },  /*当前组合有功费率2精确电能*/
	{CCom_Ac_T3_PreEn_0 ,	    CLCom_Ac_T3_PreEn_0 ,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum 	        },  /*当前组合有功费率3精确电能*/
	{CCom_Ac_T4_PreEn_0 ,	    CLCom_Ac_T4_PreEn_0 ,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum 	        },  /*当前组合有功费率4精确电能*/
	{CCom_Ac_T5_PreEn_0 ,	    CLCom_Ac_T5_PreEn_0 ,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum 	        },  /*当前组合有功费率5精确电能*/
	{CCom_Ac_T6_PreEn_0 ,	    CLCom_Ac_T6_PreEn_0 ,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum 	        },  /*当前组合有功费率6精确电能*/
	{CCom_Ac_T7_PreEn_0 ,	    CLCom_Ac_T7_PreEn_0 ,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum 	        },  /*当前组合有功费率7精确电能*/
	{CCom_Ac_T8_PreEn_0 ,	    CLCom_Ac_T8_PreEn_0 ,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum 	        },  /*当前组合有功费率8精确电能*/
	{CCom_Ac_T9_PreEn_0 ,	    CLCom_Ac_T9_PreEn_0 ,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum 	        },  /*当前组合有功费率9精确电能*/
	{CCom_Ac_T10_PreEn_0,	    CLCom_Ac_T10_PreEn_0,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum 	        },  /*当前组合有功费率10精确电能*/
	{CCom_Ac_T11_PreEn_0,	    CLCom_Ac_T11_PreEn_0,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum           },  /*当前组合有功费率11精确电能*/
	{CCom_Ac_T12_PreEn_0,	    CLCom_Ac_T12_PreEn_0,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum           },  /*当前组合有功费率12精确电能*/
	{CCom_Re1_PreEn_FF_0 ,	    CLCom_Re1_PreEn_FF_0 ,	    C_array,			        C_RatesNumTol,	C_long64,      			C_NeedRateNum_FF        },  /*组合无功1精确电能*/
	{CCom_Re1_Tol_PreEn_0,	    CLCom_Re1_Tol_PreEn_0,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum 	        },  /*当前组合无功1总电能*/
	{CCom_Re1_T1_PreEn_0 ,	    CLCom_Re1_T1_PreEn_0 ,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum 	        },  /*当前组合无功1费率1电能*/
	{CCom_Re1_T2_PreEn_0 ,	    CLCom_Re1_T2_PreEn_0 ,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum 	        },  /*当前组合无功1费率2电能*/
	{CCom_Re1_T3_PreEn_0 ,	    CLCom_Re1_T3_PreEn_0 ,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum 	        },  /*当前组合无功1费率3电能*/
	{CCom_Re1_T4_PreEn_0 ,	    CLCom_Re1_T4_PreEn_0 ,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum 	        },  /*当前组合无功1费率4电能*/
	{CCom_Re1_T5_PreEn_0 ,	    CLCom_Re1_T5_PreEn_0 ,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum 	        },  /*当前组合无功1费率5电能*/
	{CCom_Re1_T6_PreEn_0 ,	    CLCom_Re1_T6_PreEn_0 ,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum 	        },  /*当前组合无功1费率6电能*/
	{CCom_Re1_T7_PreEn_0 ,	    CLCom_Re1_T7_PreEn_0 ,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum 	        },  /*当前组合无功1费率7电能*/
	{CCom_Re1_T8_PreEn_0 ,	    CLCom_Re1_T8_PreEn_0 ,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum 	        },  /*当前组合无功1费率8电能*/
	{CCom_Re1_T9_PreEn_0 ,	    CLCom_Re1_T9_PreEn_0 ,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum 	        },  /*当前组合无功1费率9电能*/
	{CCom_Re1_T10_PreEn_0,	    CLCom_Re1_T10_PreEn_0,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum 	        },  /*当前组合无功1费率10电能*/
	{CCom_Re1_T11_PreEn_0,	    CLCom_Re1_T11_PreEn_0,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum           },  /*当前组合无功1费率11电能*/
	{CCom_Re1_T12_PreEn_0,	    CLCom_Re1_T12_PreEn_0,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum           },  /*当前组合无功1费率12电能*/
	{CCom_Re2_PreEn_FF_0 ,	    CLCom_Re2_PreEn_FF_0 ,	    C_array,			        C_RatesNumTol,	C_long64,      			C_NeedRateNum_FF        },  /*组合无功2精确电能*/
	{CCom_Re2_Tol_PreEn_0,	    CLCom_Re2_Tol_PreEn_0,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum 	        },  /*当前组合无功2总精确电能*/
	{CCom_Re2_T1_PreEn_0 ,	    CLCom_Re2_T1_PreEn_0 ,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum 	        },  /*当前组合无功2费率1精确电能*/
	{CCom_Re2_T2_PreEn_0 ,	    CLCom_Re2_T2_PreEn_0 ,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum 	        },  /*当前组合无功2费率2精确电能*/
	{CCom_Re2_T3_PreEn_0 ,	    CLCom_Re2_T3_PreEn_0 ,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum 	        },  /*当前组合无功2费率3精确电能*/
	{CCom_Re2_T4_PreEn_0 ,	    CLCom_Re2_T4_PreEn_0 ,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum 	        },  /*当前组合无功2费率4精确电能*/
	{CCom_Re2_T5_PreEn_0 ,	    CLCom_Re2_T5_PreEn_0 ,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum 	        },  /*当前组合无功2费率5精确电能*/
	{CCom_Re2_T6_PreEn_0 ,	    CLCom_Re2_T6_PreEn_0 ,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum 	        },  /*当前组合无功2费率6精确电能*/
	{CCom_Re2_T7_PreEn_0 ,	    CLCom_Re2_T7_PreEn_0 ,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum 	        },  /*当前组合无功2费率7精确电能*/
	{CCom_Re2_T8_PreEn_0 ,	    CLCom_Re2_T8_PreEn_0 ,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum 	        },  /*当前组合无功2费率8精确电能*/
	{CCom_Re2_T9_PreEn_0 ,	    CLCom_Re2_T9_PreEn_0 ,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum 	        },  /*当前组合无功2费率9精确电能*/
	{CCom_Re2_T10_PreEn_0,	    CLCom_Re2_T10_PreEn_0,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum 	        },  /*当前组合无功2费率10精确电能*/
	{CCom_Re2_T11_PreEn_0,	    CLCom_Re2_T11_PreEn_0,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum           },  /*当前组合无功2费率11精确电能*/
	{CCom_Re2_T12_PreEn_0,	    CLCom_Re2_T12_PreEn_0,	    C_long64,		    		0,				C_long64,      			C_NeedRateNum           },  /*当前组合无功2费率12精确电能*/
	{CQua1_Re_PreEn_FF_0 ,	    CLQua1_Re_PreEn_FF_0 ,	    C_array,		            C_RatesNumTol,	C_long64_unsigned,      C_NeedRateNum_FF        },  /*1象限无功精确电能*/
	{CQua1_Re_Tol_PreEn_0,	    CLQua1_Re_Tol_PreEn_0,	    C_long64_unsigned,			0,	            C_long64_unsigned,      C_NeedRateNum 	        },  /*当前1象限无功总精确电能*/
	{CQua1_Re_T1_PreEn_0 ,	    CLQua1_Re_T1_PreEn_0 ,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前1象限无功费率1精确电能*/
	{CQua1_Re_T2_PreEn_0 ,	    CLQua1_Re_T2_PreEn_0 ,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前1象限无功费率2精确电能*/
	{CQua1_Re_T3_PreEn_0 ,	    CLQua1_Re_T3_PreEn_0 ,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前1象限无功费率3精确电能*/
	{CQua1_Re_T4_PreEn_0 ,	    CLQua1_Re_T4_PreEn_0 ,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前1象限无功费率4精确电能*/
	{CQua1_Re_T5_PreEn_0 ,	    CLQua1_Re_T5_PreEn_0 ,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前1象限无功费率5精确电能*/
	{CQua1_Re_T6_PreEn_0 ,	    CLQua1_Re_T6_PreEn_0 ,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前1象限无功费率6精确电能*/
	{CQua1_Re_T7_PreEn_0 ,	    CLQua1_Re_T7_PreEn_0 ,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前1象限无功费率7精确电能*/
	{CQua1_Re_T8_PreEn_0 ,	    CLQua1_Re_T8_PreEn_0 ,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前1象限无功费率8精确电能*/
	{CQua1_Re_T9_PreEn_0 ,	    CLQua1_Re_T9_PreEn_0 ,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前1象限无功费率9精确电能*/
	{CQua1_Re_T10_PreEn_0,	    CLQua1_Re_T10_PreEn_0,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前1象限无功费率10精确电能*/
	{CQua1_Re_T11_PreEn_0,	    CLQua1_Re_T11_PreEn_0,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum           },  /*当前1象限无功费率11精确电能*/
	{CQua1_Re_T12_PreEn_0,	    CLQua1_Re_T12_PreEn_0,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum           },  /*当前1象限无功费率12精确电能*/
	{CQua2_Re_PreEn_FF_0 ,	    CLQua2_Re_PreEn_FF_0 ,	    C_array,		            C_RatesNumTol,	C_long64_unsigned,      C_NeedRateNum_FF        },  /*2象限无功精确电能*/
	{CQua2_Re_Tol_PreEn_0,	    CLQua2_Re_Tol_PreEn_0,	    C_long64_unsigned,			0,	            C_long64_unsigned,      C_NeedRateNum 	        },  /*当前2象限无功总精确电能*/
	{CQua2_Re_T1_PreEn_0 ,	    CLQua2_Re_T1_PreEn_0 ,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前2象限无功费率1精确电能*/
	{CQua2_Re_T2_PreEn_0 ,	    CLQua2_Re_T2_PreEn_0 ,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前2象限无功费率2精确电能*/
	{CQua2_Re_T3_PreEn_0 ,	    CLQua2_Re_T3_PreEn_0 ,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前2象限无功费率3精确电能*/
	{CQua2_Re_T4_PreEn_0 ,	    CLQua2_Re_T4_PreEn_0 ,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前2象限无功费率4精确电能*/
	{CQua2_Re_T5_PreEn_0 ,	    CLQua2_Re_T5_PreEn_0 ,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前2象限无功费率5精确电能*/
	{CQua2_Re_T6_PreEn_0 ,	    CLQua2_Re_T6_PreEn_0 ,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前2象限无功费率6精确电能*/
	{CQua2_Re_T7_PreEn_0 ,	    CLQua2_Re_T7_PreEn_0 ,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前2象限无功费率7精确电能*/
	{CQua2_Re_T8_PreEn_0 ,	    CLQua2_Re_T8_PreEn_0 ,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前2象限无功费率8精确电能*/
	{CQua2_Re_T9_PreEn_0 ,	    CLQua2_Re_T9_PreEn_0 ,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前2象限无功费率9精确电能*/
	{CQua2_Re_T10_PreEn_0,	    CLQua2_Re_T10_PreEn_0,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前2象限无功费率10精确电能*/
	{CQua2_Re_T11_PreEn_0,	    CLQua2_Re_T11_PreEn_0,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum           },  /*当前2象限无功费率11精确电能*/
	{CQua2_Re_T12_PreEn_0,	    CLQua2_Re_T12_PreEn_0,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum           },  /*当前2象限无功费率12精确电能*/
	{CQua3_Re_PreEn_FF_0 ,	    CLQua3_Re_PreEn_FF_0 ,	    C_array,		            C_RatesNumTol,	C_long64_unsigned,      C_NeedRateNum_FF        },  /*3象限无功精确电能*/
	{CQua3_Re_Tol_PreEn_0,	    CLQua3_Re_Tol_PreEn_0,	    C_long64_unsigned,			0,	            C_long64_unsigned,      C_NeedRateNum 	        },  /*当前3象限无功总精确电能*/
	{CQua3_Re_T1_PreEn_0 ,	    CLQua3_Re_T1_PreEn_0 ,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前3象限无功费率1精确电能*/
	{CQua3_Re_T2_PreEn_0 ,	    CLQua3_Re_T2_PreEn_0 ,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前3象限无功费率2精确电能*/
	{CQua3_Re_T3_PreEn_0 ,	    CLQua3_Re_T3_PreEn_0 ,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前3象限无功费率3精确电能*/
	{CQua3_Re_T4_PreEn_0 ,	    CLQua3_Re_T4_PreEn_0 ,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前3象限无功费率4精确电能*/
	{CQua3_Re_T5_PreEn_0 ,	    CLQua3_Re_T5_PreEn_0 ,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前3象限无功费率5精确电能*/
	{CQua3_Re_T6_PreEn_0 ,	    CLQua3_Re_T6_PreEn_0 ,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前3象限无功费率6精确电能*/
	{CQua3_Re_T7_PreEn_0 ,	    CLQua3_Re_T7_PreEn_0 ,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前3象限无功费率7精确电能*/
	{CQua3_Re_T8_PreEn_0 ,	    CLQua3_Re_T8_PreEn_0 ,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前3象限无功费率8精确电能*/
	{CQua3_Re_T9_PreEn_0 ,	    CLQua3_Re_T9_PreEn_0 ,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前3象限无功费率9精确电能*/
	{CQua3_Re_T10_PreEn_0,	    CLQua3_Re_T10_PreEn_0,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前3象限无功费率10精确电能*/
	{CQua3_Re_T11_PreEn_0,	    CLQua3_Re_T11_PreEn_0,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum           },  /*当前3象限无功费率11精确电能*/
	{CQua3_Re_T12_PreEn_0,	    CLQua3_Re_T12_PreEn_0,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum           },  /*当前3象限无功费率12精确电能*/
	{CQua4_Re_PreEn_FF_0 ,	    CLQua4_Re_PreEn_FF_0 ,	    C_array,		            C_RatesNumTol,	C_long64_unsigned,      C_NeedRateNum_FF        },  /*4象限无功精确电能*/
	{CQua4_Re_Tol_PreEn_0,	    CLQua4_Re_Tol_PreEn_0,	    C_long64_unsigned,			0,	            C_long64_unsigned,      C_NeedRateNum 	        },  /*当前4象限无功总精确电能*/
	{CQua4_Re_T1_PreEn_0 ,	    CLQua4_Re_T1_PreEn_0 ,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前4象限无功费率1精确电能*/
	{CQua4_Re_T2_PreEn_0 ,	    CLQua4_Re_T2_PreEn_0 ,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前4象限无功费率2精确电能*/
	{CQua4_Re_T3_PreEn_0 ,	    CLQua4_Re_T3_PreEn_0 ,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前4象限无功费率3精确电能*/
	{CQua4_Re_T4_PreEn_0 ,	    CLQua4_Re_T4_PreEn_0 ,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前4象限无功费率4精确电能*/
	{CQua4_Re_T5_PreEn_0 ,	    CLQua4_Re_T5_PreEn_0 ,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前4象限无功费率5精确电能*/
	{CQua4_Re_T6_PreEn_0 ,	    CLQua4_Re_T6_PreEn_0 ,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前4象限无功费率6精确电能*/
	{CQua4_Re_T7_PreEn_0 ,	    CLQua4_Re_T7_PreEn_0 ,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前4象限无功费率7精确电能*/
	{CQua4_Re_T8_PreEn_0 ,	    CLQua4_Re_T8_PreEn_0 ,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前4象限无功费率8精确电能*/
	{CQua4_Re_T9_PreEn_0 ,	    CLQua4_Re_T9_PreEn_0 ,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前4象限无功费率9精确电能*/
	{CQua4_Re_T10_PreEn_0,	    CLQua4_Re_T10_PreEn_0,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum 	        },  /*当前4象限无功费率10精确电能*/
	{CQua4_Re_T11_PreEn_0,	    CLQua4_Re_T11_PreEn_0,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum           },  /*当前4象限无功费率11精确电能*/
	{CQua4_Re_T12_PreEn_0,	    CLQua4_Re_T12_PreEn_0,	    C_long64_unsigned,		    0,				C_long64_unsigned,      C_NeedRateNum           },  /*当前4象限无功费率12精确电能*/
	{C_Fre_APosAcPreEn,		    CLPosA_Ac_PreEn_0,	        C_array,					1,	            C_long64_unsigned,      C_NoRateNum             },  /*A相正向有功精确电能*/
	{CPosA_Ac_PreEn_0,		    CLPosA_Ac_PreEn_0,	        C_long64_unsigned,	        0,	            C_long64_unsigned,      C_NoRateNum             },  /*A相正向有功精确电能*/
	{C_Fre_BPosAcPreEn,		    CLPosB_Ac_PreEn_0,	        C_array,					1,	            C_long64_unsigned,      C_NoRateNum             },  /*B相正向有功精确电能*/
	{CPosB_Ac_PreEn_0,		    CLPosB_Ac_PreEn_0,	        C_long64_unsigned,	        0,	            C_long64_unsigned,      C_NoRateNum             },  /*B相正向有功精确电能*/
	{C_Fre_CPosAcPreEn,		    CLPosC_Ac_PreEn_0,	        C_array,					1,	            C_long64_unsigned,      C_NoRateNum             },  /*C相正向有功精确电能*/
	{CPosC_Ac_PreEn_0,		    CLPosC_Ac_PreEn_0,	        C_long64_unsigned,	        0,	            C_long64_unsigned,      C_NoRateNum             },  /*C相正向有功精确电能*/

  	{C_Fre_ARevAcPreEn,	        CLRevA_Ac_PreEn_0,	        C_array,					1,              C_long64_unsigned,      C_NoRateNum             },  /*A相反向有功精确电能*/
	{CRevA_Ac_PreEn_0,	        CLRevA_Ac_PreEn_0,	        C_long64_unsigned,		    0,	            C_long64_unsigned,      C_NoRateNum             },  /*A相反向有功精确电能*/
	{C_Fre_BRevAcPreEn,	        CLRevB_Ac_PreEn_0,	        C_array,					1,              C_long64_unsigned,      C_NoRateNum             },  /*B相反向有功精确电能*/
	{CRevB_Ac_PreEn_0,	        CLRevB_Ac_PreEn_0,	        C_long64_unsigned,		    0,	            C_long64_unsigned,      C_NoRateNum             },  /*B相反向有功精确电能*/
	{C_Fre_CRevAcPreEn,	        CLRevC_Ac_PreEn_0,	        C_array,					1,	            C_long64_unsigned,      C_NoRateNum             },  /*C相反向有功精确电能*/
	{CRevC_Ac_PreEn_0,	        CLRevC_Ac_PreEn_0,	        C_long64_unsigned,		    0,	            C_long64_unsigned,      C_NoRateNum             },  /*C相反向有功精确电能*/

	{C_Fre_AComRe1PreEn,	    CLComA_Re1_PreEn_0,	        C_array,					1,              C_long64,               C_NoRateNum             },  /*A相组合无功1精确电能*/
	{CComA_Re1_PreEn_0,	        CLComA_Re1_PreEn_0,	        C_long64,				    0,	            C_long64,               C_NoRateNum             },  /*A相组合无功1精确电能*/
	{C_Fre_BComRe1PreEn,	    CLComB_Re1_PreEn_0,	        C_array,					1,              C_long64,               C_NoRateNum             },  /*B相组合无功1精确电能*/
	{CComB_Re1_PreEn_0,	        CLComB_Re1_PreEn_0,	        C_long64,				    0,	            C_long64,               C_NoRateNum             },  /*B相组合无功1精确电能*/
	{C_Fre_CComRe1PreEn,	    CLComC_Re1_PreEn_0,	        C_array,					1,              C_long64,               C_NoRateNum             },  /*C相组合无功1精确电能*/
	{CComC_Re1_PreEn_0,	        CLComC_Re1_PreEn_0,	        C_long64,				    0,	            C_long64,               C_NoRateNum             },  /*C相组合无功1精确电能*/

 	{C_Fre_AComRe2PreEn,	    CLComA_Re2_PreEn_0,	        C_array,					1,              C_long64,               C_NoRateNum             },  /*A相组合无功2精确电能*/
	{CComA_Re2_PreEn_0,	        CLComA_Re2_PreEn_0,	        C_long64,				    0,	            C_long64,               C_NoRateNum             },  /*A相组合无功2精确电能*/
	{C_Fre_BComRe2PreEn,	    CLComB_Re2_PreEn_0,	        C_array,					1,              C_long64,               C_NoRateNum             },  /*B相组合无功2精确电能*/
	{CComB_Re2_PreEn_0,	        CLComB_Re2_PreEn_0,	        C_long64,				    0,	            C_long64,               C_NoRateNum             },  /*B相组合无功2精确电能*/
	{C_Fre_CComRe2PreEn,	    CLComC_Re2_PreEn_0,	        C_array,					1,	            C_long64,               C_NoRateNum             },  /*C相组合无功2精确电能*/
	{CComC_Re2_PreEn_0,	        CLComC_Re2_PreEn_0,	        C_long64,				    0,	            C_long64,               C_NoRateNum             },  /*C相组合无功2精确电能*/

	{C_Fre_AQuadrant1PreEn,	    CLQua1A_Re_PreEn_0,	        C_array,					1,             C_long64_unsigned,       C_NoRateNum             },  /*A相第一象限无功精确电能*/
	{CQua1A_Re_PreEn_0,	        CLQua1A_Re_PreEn_0,	        C_long64_unsigned,		    0,	           C_long64_unsigned,       C_NoRateNum             },  /*A相第一象限无功精确电能*/
	{C_Fre_BQuadrant1PreEn,	    CLQua1B_Re_PreEn_0,	        C_array,					1,             C_long64_unsigned,       C_NoRateNum             },  /*B相第一象限无功精确电能*/
	{CQua1B_Re_PreEn_0,	        CLQua1B_Re_PreEn_0,	        C_long64_unsigned,		    0,	           C_long64_unsigned,       C_NoRateNum             },  /*B相第一象限无功精确电能*/
	{C_Fre_CQuadrant1PreEn,	    CLQua1C_Re_PreEn_0,	        C_array,					1,             C_long64_unsigned,       C_NoRateNum             },  /*C相第一象限无功精确电能*/
	{CQua1C_Re_PreEn_0,	        CLQua1C_Re_PreEn_0,	        C_long64_unsigned,		    0,	           C_long64_unsigned,       C_NoRateNum             },  /*C相第一象限无功精确电能*/

	{C_Fre_AQuadrant2PreEn,	    CLQua2A_Re_PreEn_0,	        C_array,					1,             C_long64_unsigned,       C_NoRateNum             },  /*A相第二象限无功精确电能*/
	{CQua2A_Re_PreEn_0,	        CLQua2A_Re_PreEn_0,	        C_long64_unsigned,		    0,	           C_long64_unsigned,       C_NoRateNum             },  /*A相第二象限无功精确电能*/
	{C_Fre_BQuadrant2PreEn,	    CLQua2B_Re_PreEn_0,	        C_array,					1,             C_long64_unsigned,       C_NoRateNum             },  /*B相第二象限无功精确电能*/
	{CQua2B_Re_PreEn_0,	        CLQua2B_Re_PreEn_0,	        C_long64_unsigned,		    0,	           C_long64_unsigned,       C_NoRateNum             },  /*B相第二象限无功精确电能*/
	{C_Fre_CQuadrant2PreEn,	    CLQua2C_Re_PreEn_0,	        C_array,					1,             C_long64_unsigned,       C_NoRateNum             },  /*C相第二象限无功精确电能*/
	{CQua2C_Re_PreEn_0,	        CLQua2C_Re_PreEn_0,	        C_long64_unsigned,		    0,	           C_long64_unsigned,       C_NoRateNum             },  /*C相第二象限无功精确电能*/

	{C_Fre_AQuadrant3PreEn,	    CLQua3A_Re_PreEn_0,	        C_array,					1,             C_long64_unsigned,       C_NoRateNum             },  /*A相第三象限无功精确电能*/
	{CQua3A_Re_PreEn_0,	        CLQua3A_Re_PreEn_0,	        C_long64_unsigned,		    0,	           C_long64_unsigned,       C_NoRateNum             },  /*A相第三象限无功精确电能*/
	{C_Fre_BQuadrant3PreEn,	    CLQua3B_Re_PreEn_0,	        C_array,					1,             C_long64_unsigned,       C_NoRateNum             },  /*B相第三象限无功精确电能*/
	{CQua3B_Re_PreEn_0,	        CLQua3B_Re_PreEn_0,	        C_long64_unsigned,		    0,	           C_long64_unsigned,       C_NoRateNum             },  /*B相第三象限无功精确电能*/
	{C_Fre_CQuadrant3PreEn,	    CLQua3C_Re_PreEn_0,	        C_array,					1,             C_long64_unsigned,       C_NoRateNum             },  /*C相第三象限无功精确电能*/
	{CQua3C_Re_PreEn_0,	        CLQua3C_Re_PreEn_0,	        C_long64_unsigned,		    0,	           C_long64_unsigned,       C_NoRateNum             },  /*C相第三象限无功精确电能*/

	{C_Fre_AQuadrant4PreEn,	    CLQua4A_Re_PreEn_0,	        C_array,					1,             C_long64_unsigned,       C_NoRateNum             },  /*A相第四象限无功精确电能*/
	{CQua4A_Re_PreEn_0,	        CLQua4A_Re_PreEn_0,	        C_long64_unsigned,		    0,	           C_long64_unsigned,       C_NoRateNum             },  /*A相第四象限无功精确电能*/
	{C_Fre_BQuadrant4PreEn,	    CLQua4B_Re_PreEn_0,	        C_array,					1,             C_long64_unsigned,       C_NoRateNum             },  /*B相第四象限无功精确电能*/
	{CQua4B_Re_PreEn_0,	        CLQua4B_Re_PreEn_0,	        C_long64_unsigned,		    0,	           C_long64_unsigned,       C_NoRateNum             },  /*B相第四象限无功精确电能*/
	{C_Fre_CQuadrant4PreEn,	    CLQua4C_Re_PreEn_0,	        C_array,					1,             C_long64_unsigned,       C_NoRateNum             },  /*C相第四象限无功精确电能*/
	{CQua4C_Re_PreEn_0,	        CLQua4C_Re_PreEn_0,	        C_long64_unsigned,		    0,	           C_long64_unsigned,       C_NoRateNum             },  /*C相第四象限无功精确电能*/
	{CVector_Current,	        CLVector_Current,		    C_double_long,			    0,	           C_double_long,		    C_NoRateNum             },  /*零线电流*/

	{CCom_Ac_LastPulse_FF_0,	CLCom_Ac_LastPulse_FF_0,	C_array,			        C_RatesNumTol, C_integer,              C_NeedRateNum_FF         },  /*当前组合有功脉冲尾数数据块*/
	{CCom_Ac_Tol_LastPulse_0,	CLCom_Ac_Tol_LastPulse_0,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合有功总脉冲尾数*/
	{CCom_Ac_T1_LastPulse_0 ,	CLCom_Ac_T1_LastPulse_0 ,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合有功费率1脉冲尾数*/
	{CCom_Ac_T2_LastPulse_0 ,	CLCom_Ac_T2_LastPulse_0 ,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合有功费率2脉冲尾数*/
	{CCom_Ac_T3_LastPulse_0 ,	CLCom_Ac_T3_LastPulse_0 ,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合有功费率3脉冲尾数*/
	{CCom_Ac_T4_LastPulse_0 ,	CLCom_Ac_T4_LastPulse_0 ,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合有功费率4脉冲尾数*/
	{CCom_Ac_T5_LastPulse_0 ,	CLCom_Ac_T5_LastPulse_0 ,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合有功费率5脉冲尾数*/
	{CCom_Ac_T6_LastPulse_0 ,	CLCom_Ac_T6_LastPulse_0 ,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合有功费率6脉冲尾数*/
	{CCom_Ac_T7_LastPulse_0 ,	CLCom_Ac_T7_LastPulse_0 ,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合有功费率7脉冲尾数*/
	{CCom_Ac_T8_LastPulse_0 ,	CLCom_Ac_T8_LastPulse_0 ,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合有功费率8脉冲尾数*/
	{CCom_Ac_T9_LastPulse_0 ,	CLCom_Ac_T9_LastPulse_0 ,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合有功费率9脉冲尾数*/
	{CCom_Ac_T10_LastPulse_0,	CLCom_Ac_T10_LastPulse_0,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合有功费率10脉冲尾数*/
	{CCom_Ac_T11_LastPulse_0,	CLCom_Ac_T11_LastPulse_0,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合有功费率11脉冲尾数*/
	{CCom_Ac_T12_LastPulse_0,	CLCom_Ac_T12_LastPulse_0,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合有功费率12脉冲尾数*/

	{CPos_Ac_LastPulse_FF_0,	CLPos_Ac_LastPulse_FF_0,	C_array,			        C_RatesNumTol, C_unsigned,              C_NeedRateNum_FF        },  /*当前正向有功脉冲尾数数据块*/
	{CPos_Ac_Tol_LastPulse_0,	CLPos_Ac_Tol_LastPulse_0,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前正向有功总脉冲尾数*/
	{CPos_Ac_T1_LastPulse_0 ,	CLPos_Ac_T1_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前正向有功费率1脉冲尾数*/
	{CPos_Ac_T2_LastPulse_0 ,	CLPos_Ac_T2_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前正向有功费率2脉冲尾数*/
	{CPos_Ac_T3_LastPulse_0 ,	CLPos_Ac_T3_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前正向有功费率3脉冲尾数*/
	{CPos_Ac_T4_LastPulse_0 ,	CLPos_Ac_T4_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前正向有功费率4脉冲尾数*/
	{CPos_Ac_T5_LastPulse_0 ,	CLPos_Ac_T5_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前正向有功费率5脉冲尾数*/
	{CPos_Ac_T6_LastPulse_0 ,	CLPos_Ac_T6_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前正向有功费率6脉冲尾数*/
	{CPos_Ac_T7_LastPulse_0 ,	CLPos_Ac_T7_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前正向有功费率7脉冲尾数*/
	{CPos_Ac_T8_LastPulse_0 ,	CLPos_Ac_T8_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前正向有功费率8脉冲尾数*/
	{CPos_Ac_T9_LastPulse_0 ,	CLPos_Ac_T9_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前正向有功费率9脉冲尾数*/
	{CPos_Ac_T10_LastPulse_0,	CLPos_Ac_T10_LastPulse_0,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前正向有功费率10脉冲尾数*/
	{CPos_Ac_T11_LastPulse_0,	CLPos_Ac_T11_LastPulse_0,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前正向有功费率11脉冲尾数*/
	{CPos_Ac_T12_LastPulse_0,	CLPos_Ac_T12_LastPulse_0,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前正向有功费率12脉冲尾数*/

	{CRev_Ac_LastPulse_FF_0,	CLRev_Ac_LastPulse_FF_0,	C_array,			        C_RatesNumTol, C_unsigned,              C_NeedRateNum_FF        },  /*当前反向有功脉冲尾数数据块*/
	{CRev_Ac_Tol_LastPulse_0,	CLRev_Ac_Tol_LastPulse_0,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前反向有功总脉冲尾数*/
	{CRev_Ac_T1_LastPulse_0 ,	CLRev_Ac_T1_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前反向有功费率1脉冲尾数*/
	{CRev_Ac_T2_LastPulse_0 ,	CLRev_Ac_T2_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前反向有功费率2脉冲尾数*/
	{CRev_Ac_T3_LastPulse_0 ,	CLRev_Ac_T3_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前反向有功费率3脉冲尾数*/
	{CRev_Ac_T4_LastPulse_0 ,	CLRev_Ac_T4_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前反向有功费率4脉冲尾数*/
	{CRev_Ac_T5_LastPulse_0 ,	CLRev_Ac_T5_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前反向有功费率5脉冲尾数*/
	{CRev_Ac_T6_LastPulse_0 ,	CLRev_Ac_T6_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前反向有功费率6脉冲尾数*/
	{CRev_Ac_T7_LastPulse_0 ,	CLRev_Ac_T7_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前反向有功费率7脉冲尾数*/
	{CRev_Ac_T8_LastPulse_0 ,	CLRev_Ac_T8_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前反向有功费率8脉冲尾数*/
	{CRev_Ac_T9_LastPulse_0 ,	CLRev_Ac_T9_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前反向有功费率9脉冲尾数*/
	{CRev_Ac_T10_LastPulse_0,	CLRev_Ac_T10_LastPulse_0,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前反向有功费率10脉冲尾数*/
	{CRev_Ac_T11_LastPulse_0,	CLRev_Ac_T11_LastPulse_0,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前反向有功费率11脉冲尾数*/
	{CRev_Ac_T12_LastPulse_0,	CLRev_Ac_T12_LastPulse_0,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前反向有功费率12脉冲尾数*/

	{CCom_Re1_LastPulse_FF_0,	CLCom_Re1_LastPulse_FF_0,	C_array,			        C_RatesNumTol, C_integer,              C_NeedRateNum_FF         },  /*当前组合无功1电能数据块*/
	{CCom_Re1_Tol_LastPulse_0 ,	CLCom_Re1_Tol_LastPulse_0,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合无功1费率12电能*/
	{CCom_Re1_T1_LastPulse_0 ,	CLCom_Re1_T1_LastPulse_0 ,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合无功1总电能*/
	{CCom_Re1_T2_LastPulse_0 ,	CLCom_Re1_T2_LastPulse_0 ,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合无功1费率1电能*/
	{CCom_Re1_T3_LastPulse_0 ,	CLCom_Re1_T3_LastPulse_0 ,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合无功1费率2电能*/
	{CCom_Re1_T4_LastPulse_0 ,	CLCom_Re1_T4_LastPulse_0 ,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合无功1费率3电能*/
	{CCom_Re1_T5_LastPulse_0 ,	CLCom_Re1_T5_LastPulse_0 ,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合无功1费率4电能*/
	{CCom_Re1_T6_LastPulse_0 ,	CLCom_Re1_T6_LastPulse_0 ,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合无功1费率5电能*/
	{CCom_Re1_T7_LastPulse_0 ,	CLCom_Re1_T7_LastPulse_0 ,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合无功1费率6电能*/
	{CCom_Re1_T8_LastPulse_0 ,	CLCom_Re1_T8_LastPulse_0 ,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合无功1费率7电能*/
	{CCom_Re1_T9_LastPulse_0 ,	CLCom_Re1_T9_LastPulse_0 ,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合无功1费率8电能*/
	{CCom_Re1_T10_LastPulse_0,	CLCom_Re1_T10_LastPulse_0,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合无功1费率9电能*/
	{CCom_Re1_T11_LastPulse_0,	CLCom_Re1_T11_LastPulse_0,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合无功1费率10电能*/
	{CCom_Re1_T12_LastPulse_0,	CLCom_Re1_T12_LastPulse_0,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合无功1费率11电能*/

	{CCom_Re2_LastPulse_FF_0,	CLCom_Re2_LastPulse_FF_0,	C_array,			        C_RatesNumTol, C_integer,              C_NeedRateNum_FF         },  /*当前组合无功2电能数据块*/
	{CCom_Re2_Tol_LastPulse_0,	CLCom_Re2_Tol_LastPulse_0,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合无功2总电能*/
	{CCom_Re2_T1_LastPulse_0 ,	CLCom_Re2_T1_LastPulse_0 ,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合无功2费率1电能*/
	{CCom_Re2_T2_LastPulse_0 ,	CLCom_Re2_T2_LastPulse_0 ,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合无功2费率2电能*/
	{CCom_Re2_T3_LastPulse_0 ,	CLCom_Re2_T3_LastPulse_0 ,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合无功2费率3电能*/
	{CCom_Re2_T4_LastPulse_0 ,	CLCom_Re2_T4_LastPulse_0 ,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合无功2费率4电能*/
	{CCom_Re2_T5_LastPulse_0 ,	CLCom_Re2_T5_LastPulse_0 ,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合无功2费率5电能*/
	{CCom_Re2_T6_LastPulse_0 ,	CLCom_Re2_T6_LastPulse_0 ,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合无功2费率6电能*/
	{CCom_Re2_T7_LastPulse_0 ,	CLCom_Re2_T7_LastPulse_0 ,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合无功2费率7电能*/
	{CCom_Re2_T8_LastPulse_0 ,	CLCom_Re2_T8_LastPulse_0 ,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合无功2费率8电能*/
	{CCom_Re2_T9_LastPulse_0 ,	CLCom_Re2_T9_LastPulse_0 ,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合无功2费率9电能*/
	{CCom_Re2_T10_LastPulse_0,	CLCom_Re2_T10_LastPulse_0,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合无功2费率10电能*/
	{CCom_Re2_T11_LastPulse_0,	CLCom_Re2_T11_LastPulse_0,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合无功2费率11电能*/
	{CCom_Re2_T12_LastPulse_0,	CLCom_Re2_T12_LastPulse_0,	C_integer,			        0,             C_integer,              C_NeedRateNum 	        },  /*当前组合无功2费率12电能*/

	{CQua1_Re_LastPulse_FF_0,	CLQua1_Re_LastPulse_FF_0,	C_array,			        C_RatesNumTol, C_unsigned,              C_NeedRateNum_FF        },  /*当前1象限无功脉冲尾数数据块*/
	{CQua1_Re_Tol_LastPulse_0 ,	CLQua1_Re_Tol_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前1象限无功费率12脉冲尾数*/
	{CQua1_Re_T1_LastPulse_0 ,	CLQua1_Re_T1_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前1象限无功总脉冲尾数*/
	{CQua1_Re_T2_LastPulse_0 ,	CLQua1_Re_T2_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前1象限无功费率1脉冲尾数*/
	{CQua1_Re_T3_LastPulse_0 ,	CLQua1_Re_T3_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前1象限无功费率2脉冲尾数*/
	{CQua1_Re_T4_LastPulse_0 ,	CLQua1_Re_T4_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前1象限无功费率3脉冲尾数*/
	{CQua1_Re_T5_LastPulse_0 ,	CLQua1_Re_T5_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前1象限无功费率4脉冲尾数*/
	{CQua1_Re_T6_LastPulse_0 ,	CLQua1_Re_T6_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前1象限无功费率5脉冲尾数*/
	{CQua1_Re_T7_LastPulse_0 ,	CLQua1_Re_T7_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前1象限无功费率6脉冲尾数*/
	{CQua1_Re_T8_LastPulse_0 ,	CLQua1_Re_T8_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前1象限无功费率7脉冲尾数*/
	{CQua1_Re_T9_LastPulse_0 ,	CLQua1_Re_T9_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前1象限无功费率8脉冲尾数*/
	{CQua1_Re_T10_LastPulse_0,	CLQua1_Re_T10_LastPulse_0,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前1象限无功费率9脉冲尾数*/
	{CQua1_Re_T11_LastPulse_0,	CLQua1_Re_T11_LastPulse_0,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前1象限无功费率10脉冲尾数*/
	{CQua1_Re_T12_LastPulse_0,	CLQua1_Re_T12_LastPulse_0,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前1象限无功费率11脉冲尾数*/


	{CQua2_Re_LastPulse_FF_0,	CLQua2_Re_LastPulse_FF_0,	C_array,			        C_RatesNumTol, C_unsigned,              C_NeedRateNum_FF        },  /*当前2象限无功脉冲尾数数据块*/
	{CQua2_Re_Tol_LastPulse_0 ,	CLQua2_Re_Tol_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前2象限无功费率12脉冲尾数*/
	{CQua2_Re_T1_LastPulse_0 ,	CLQua2_Re_T1_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前2象限无功总脉冲尾数*/
	{CQua2_Re_T2_LastPulse_0 ,	CLQua2_Re_T2_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前2象限无功费率1脉冲尾数*/
	{CQua2_Re_T3_LastPulse_0 ,	CLQua2_Re_T3_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前2象限无功费率2脉冲尾数*/
	{CQua2_Re_T4_LastPulse_0 ,	CLQua2_Re_T4_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前2象限无功费率3脉冲尾数*/
	{CQua2_Re_T5_LastPulse_0 ,	CLQua2_Re_T5_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前2象限无功费率4脉冲尾数*/
	{CQua2_Re_T6_LastPulse_0 ,	CLQua2_Re_T6_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前2象限无功费率5脉冲尾数*/
	{CQua2_Re_T7_LastPulse_0 ,	CLQua2_Re_T7_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前2象限无功费率6脉冲尾数*/
	{CQua2_Re_T8_LastPulse_0 ,	CLQua2_Re_T8_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前2象限无功费率7脉冲尾数*/
	{CQua2_Re_T9_LastPulse_0 ,	CLQua2_Re_T9_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前2象限无功费率8脉冲尾数*/
	{CQua2_Re_T10_LastPulse_0,	CLQua2_Re_T10_LastPulse_0,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前2象限无功费率9脉冲尾数*/
	{CQua2_Re_T11_LastPulse_0,	CLQua2_Re_T11_LastPulse_0,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前2象限无功费率10脉冲尾数*/
	{CQua2_Re_T12_LastPulse_0,	CLQua2_Re_T12_LastPulse_0,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前2象限无功费率11脉冲尾数*/

	{CQua3_Re_LastPulse_FF_0,	CLQua3_Re_LastPulse_FF_0,	C_array,			        C_RatesNumTol, C_unsigned,              C_NeedRateNum_FF        },  /*当前3象限无功脉冲尾数数据块*/
	{CQua3_Re_Tol_LastPulse_0 ,	CLQua3_Re_Tol_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前3象限无功费率12脉冲尾数*/
	{CQua3_Re_T1_LastPulse_0 ,	CLQua3_Re_T1_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前3象限无功总脉冲尾数*/
	{CQua3_Re_T2_LastPulse_0 ,	CLQua3_Re_T2_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前3象限无功费率1脉冲尾数*/
	{CQua3_Re_T3_LastPulse_0 ,	CLQua3_Re_T3_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前3象限无功费率2脉冲尾数*/
	{CQua3_Re_T4_LastPulse_0 ,	CLQua3_Re_T4_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前3象限无功费率3脉冲尾数*/
	{CQua3_Re_T5_LastPulse_0 ,	CLQua3_Re_T5_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前3象限无功费率4脉冲尾数*/
	{CQua3_Re_T6_LastPulse_0 ,	CLQua3_Re_T6_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前3象限无功费率5脉冲尾数*/
	{CQua3_Re_T7_LastPulse_0 ,	CLQua3_Re_T7_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前3象限无功费率6脉冲尾数*/
	{CQua3_Re_T8_LastPulse_0 ,	CLQua3_Re_T8_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前3象限无功费率7脉冲尾数*/
	{CQua3_Re_T9_LastPulse_0 ,	CLQua3_Re_T9_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前3象限无功费率8脉冲尾数*/
	{CQua3_Re_T10_LastPulse_0,	CLQua3_Re_T10_LastPulse_0,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前3象限无功费率9脉冲尾数*/
	{CQua3_Re_T11_LastPulse_0,	CLQua3_Re_T11_LastPulse_0,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前3象限无功费率10脉冲尾数*/
	{CQua3_Re_T12_LastPulse_0,	CLQua3_Re_T12_LastPulse_0,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前3象限无功费率11脉冲尾数*/

	{CQua4_Re_LastPulse_FF_0,	CLQua4_Re_LastPulse_FF_0,	C_array,			        C_RatesNumTol, C_unsigned,              C_NeedRateNum_FF        },  /*当前4象限无功脉冲尾数数据块*/
	{CQua4_Re_Tol_LastPulse_0 ,	CLQua4_Re_Tol_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前4象限无功费率12脉冲尾数*/
	{CQua4_Re_T1_LastPulse_0 ,	CLQua4_Re_T1_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前4象限无功总脉冲尾数*/
	{CQua4_Re_T2_LastPulse_0 ,	CLQua4_Re_T2_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前4象限无功费率1脉冲尾数*/
	{CQua4_Re_T3_LastPulse_0 ,	CLQua4_Re_T3_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前4象限无功费率2脉冲尾数*/
	{CQua4_Re_T4_LastPulse_0 ,	CLQua4_Re_T4_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前4象限无功费率3脉冲尾数*/
	{CQua4_Re_T5_LastPulse_0 ,	CLQua4_Re_T5_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前4象限无功费率4脉冲尾数*/
	{CQua4_Re_T6_LastPulse_0 ,	CLQua4_Re_T6_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前4象限无功费率5脉冲尾数*/
	{CQua4_Re_T7_LastPulse_0 ,	CLQua4_Re_T7_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前4象限无功费率6脉冲尾数*/
	{CQua4_Re_T8_LastPulse_0 ,	CLQua4_Re_T8_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前4象限无功费率7脉冲尾数*/
	{CQua4_Re_T9_LastPulse_0 ,	CLQua4_Re_T9_LastPulse_0 ,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前4象限无功费率8脉冲尾数*/
	{CQua4_Re_T10_LastPulse_0,	CLQua4_Re_T10_LastPulse_0,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前4象限无功费率9脉冲尾数*/
	{CQua4_Re_T11_LastPulse_0,	CLQua4_Re_T11_LastPulse_0,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前4象限无功费率10脉冲尾数*/
	{CQua4_Re_T12_LastPulse_0,	CLQua4_Re_T12_LastPulse_0,	C_unsigned,			        0,             C_unsigned,              C_NeedRateNum 	        },  /*当前4象限无功费率11脉冲尾数*/

	{C_Fre_APosAcLastPulse,		CLPosA_Ac_LastPulse_0,	    C_array,					1,	           C_unsigned,     		    C_NoRateNum             },  /*A相正向有功脉冲尾数*/
	{CPosA_Ac_LastPulse_0,		CLPosA_Ac_LastPulse_0,	    C_unsigned,	   			    0,	           C_unsigned,     		    C_NoRateNum             },  /*A相正向有功脉冲尾数*/
	{C_Fre_BPosAcLastPulse,		CLPosB_Ac_LastPulse_0,	    C_array,					1,	           C_unsigned,     		    C_NoRateNum             },  /*B相正向有功脉冲尾数*/
	{CPosB_Ac_LastPulse_0,		CLPosB_Ac_LastPulse_0,	    C_unsigned,	   			    0,	           C_unsigned,     		    C_NoRateNum             },  /*B相正向有功脉冲尾数*/
	{C_Fre_CPosAcLastPulse,		CLPosC_Ac_LastPulse_0,	    C_array,					1,	           C_unsigned,     		    C_NoRateNum             },  /*C相正向有功脉冲尾数*/
	{CPosC_Ac_LastPulse_0,		CLPosC_Ac_LastPulse_0,	    C_unsigned,	   			    0,	           C_unsigned,     		    C_NoRateNum             },  /*C相正向有功脉冲尾数*/

	{C_Fre_ARevAcLastPulse,		CLRevA_Ac_LastPulse_0,	    C_array,					1,	           C_unsigned,     		    C_NoRateNum             },  /*A相反向有功脉冲尾数*/
	{CRevA_Ac_LastPulse_0,		CLRevA_Ac_LastPulse_0,	    C_unsigned,	   			    0,	           C_unsigned,     		    C_NoRateNum             },  /*A相反向有功脉冲尾数*/
	{C_Fre_BRevAcLastPulse,		CLRevB_Ac_LastPulse_0,	    C_array,					1,	           C_unsigned,     		    C_NoRateNum             },  /*B相反向有功脉冲尾数*/
	{CRevB_Ac_LastPulse_0,		CLRevB_Ac_LastPulse_0,	    C_unsigned,	   			    0,	           C_unsigned,     		    C_NoRateNum             },  /*B相反向有功脉冲尾数*/
	{C_Fre_CRevAcLastPulse,		CLRevC_Ac_LastPulse_0,	    C_array,					1,	           C_unsigned,     		    C_NoRateNum             },  /*C相反向有功脉冲尾数*/
	{CRevC_Ac_LastPulse_0,		CLRevC_Ac_LastPulse_0,	    C_unsigned,	   			    0,	           C_unsigned,     		    C_NoRateNum             },  /*C相反向有功脉冲尾数*/

	{C_Fre_AComRe1LastPulse,	CLComA_Re1_LastPulse_0,	    C_array,					1,	           C_integer,     		    C_NoRateNum             },  /*A相组合无功1脉冲尾数*/
	{CComA_Re1_LastPulse_0,		CLComA_Re1_LastPulse_0,	    C_integer,	   			    0,	           C_integer,     		    C_NoRateNum             },  /*A相组合无功1脉冲尾数*/
	{C_Fre_BComRe1LastPulse,	CLComB_Re1_LastPulse_0,	    C_array,					1,	           C_integer,     		    C_NoRateNum             },  /*B相组合无功1脉冲尾数*/
	{CComB_Re1_LastPulse_0,		CLComB_Re1_LastPulse_0,	    C_integer,	   			    0,	           C_integer,     		    C_NoRateNum             },  /*B相组合无功1脉冲尾数*/
	{C_Fre_CComRe1LastPulse,	CLComC_Re1_LastPulse_0,	    C_array,					1,	           C_integer,     		    C_NoRateNum             },  /*C相组合无功1脉冲尾数*/
	{CComC_Re1_LastPulse_0,		CLComC_Re1_LastPulse_0,	    C_integer,	   			    0,	           C_integer,     		    C_NoRateNum             },  /*C相组合无功1脉冲尾数*/

	{C_Fre_AComRe2LastPulse,	CLComA_Re2_LastPulse_0,	    C_array,					1,	           C_integer,     		    C_NoRateNum             },  /*A相组合无功2脉冲尾数*/
	{CComA_Re2_LastPulse_0,		CLComA_Re2_LastPulse_0,	    C_integer,	   			    0,	           C_integer,     		    C_NoRateNum             },  /*A相组合无功2脉冲尾数*/
	{C_Fre_BComRe2LastPulse,	CLComB_Re2_LastPulse_0,	    C_array,					1,	           C_integer,     		    C_NoRateNum             },  /*B相组合无功2脉冲尾数*/
	{CComB_Re2_LastPulse_0,		CLComB_Re2_LastPulse_0,	    C_integer,	   			    0,	           C_integer,     		    C_NoRateNum             },  /*B相组合无功2脉冲尾数*/
	{C_Fre_CComRe2LastPulse,	CLComC_Re2_LastPulse_0,	    C_array,					1,	           C_integer,     		    C_NoRateNum             },  /*C相组合无功2脉冲尾数*/
	{CComC_Re2_LastPulse_0,		CLComC_Re2_LastPulse_0,	    C_integer,	   			    0,	           C_integer,     		    C_NoRateNum             },  /*C相组合无功2脉冲尾数*/

   	{C_Fre_AQuadrant1LastPulse,	CLQua1A_Re_LastPulse_0,	    C_array,					1,	           C_unsigned,     		    C_NoRateNum             },  /*A相1象限无功脉冲尾数*/
	{CQua1A_Re_LastPulse_0,		CLQua1A_Re_LastPulse_0,	    C_unsigned,	   			    0,	           C_unsigned,     		    C_NoRateNum             },  /*A相1象限无功脉冲尾数*/
   	{C_Fre_BQuadrant1LastPulse,	CLQua1B_Re_LastPulse_0,	    C_array,					1,	           C_unsigned,     		    C_NoRateNum             },  /*B相1象限无功脉冲尾数*/
	{CQua1B_Re_LastPulse_0,		CLQua1B_Re_LastPulse_0,	    C_unsigned,	   			    0,	           C_unsigned,     		    C_NoRateNum             },  /*B相1象限无功脉冲尾数*/
   	{C_Fre_CQuadrant1LastPulse,	CLQua1C_Re_LastPulse_0,	    C_array,					1,	           C_unsigned,     		    C_NoRateNum             },  /*C相1象限无功脉冲尾数*/
	{CQua1C_Re_LastPulse_0,		CLQua1C_Re_LastPulse_0,	    C_unsigned,	   			    0,	           C_unsigned,     		    C_NoRateNum             },  /*C相1象限无功脉冲尾数*/

   	{C_Fre_AQuadrant2LastPulse,	CLQua2A_Re_LastPulse_0,	    C_array,					1,	           C_unsigned,     		    C_NoRateNum             },  /*A相2象限无功脉冲尾数*/
	{CQua2A_Re_LastPulse_0,		CLQua2A_Re_LastPulse_0,	    C_unsigned,	   			    0,	           C_unsigned,     		    C_NoRateNum             },  /*A相2象限无功脉冲尾数*/
   	{C_Fre_BQuadrant2LastPulse,	CLQua2B_Re_LastPulse_0,	    C_array,					1,	           C_unsigned,     		    C_NoRateNum             },  /*B相2象限无功脉冲尾数*/
	{CQua2B_Re_LastPulse_0,		CLQua2B_Re_LastPulse_0,	    C_unsigned,	   			    0,	           C_unsigned,     		    C_NoRateNum             },  /*B相2象限无功脉冲尾数*/
   	{C_Fre_CQuadrant2LastPulse,	CLQua2C_Re_LastPulse_0,	    C_array,					1,	           C_unsigned,     		    C_NoRateNum             },  /*C相2象限无功脉冲尾数*/
	{CQua2C_Re_LastPulse_0,		CLQua2C_Re_LastPulse_0,	    C_unsigned,	   			    0,	           C_unsigned,     		    C_NoRateNum             },  /*C相2象限无功脉冲尾数*/

   	{C_Fre_AQuadrant3LastPulse,	CLQua3A_Re_LastPulse_0,	    C_array,					1,	           C_unsigned,     		    C_NoRateNum             },  /*A相3象限无功脉冲尾数*/
	{CQua3A_Re_LastPulse_0,		CLQua3A_Re_LastPulse_0,	    C_unsigned,	   			    0,	           C_unsigned,     		    C_NoRateNum             },  /*A相3象限无功脉冲尾数*/
   	{C_Fre_BQuadrant3LastPulse,	CLQua3B_Re_LastPulse_0,	    C_array,					1,	           C_unsigned,     		    C_NoRateNum             },  /*B相3象限无功脉冲尾数*/
	{CQua3B_Re_LastPulse_0,		CLQua3B_Re_LastPulse_0,	    C_unsigned,	   			    0,	           C_unsigned,     		    C_NoRateNum             },  /*B相3象限无功脉冲尾数*/
   	{C_Fre_CQuadrant3LastPulse,	CLQua3C_Re_LastPulse_0,	    C_array,					1,	           C_unsigned,     		    C_NoRateNum             },  /*C相3象限无功脉冲尾数*/
	{CQua3C_Re_LastPulse_0,		CLQua3C_Re_LastPulse_0,	    C_unsigned,	   			    0,	           C_unsigned,     		    C_NoRateNum             },  /*C相3象限无功脉冲尾数*/

   	{C_Fre_AQuadrant4LastPulse,	CLQua4A_Re_LastPulse_0,	    C_array,					1,	           C_unsigned,     		    C_NoRateNum             },  /*A相4象限无功脉冲尾数*/
	{CQua4A_Re_LastPulse_0,		CLQua4A_Re_LastPulse_0,	    C_unsigned,	   			    0,	           C_unsigned,     		    C_NoRateNum             },  /*A相4象限无功脉冲尾数*/
   	{C_Fre_BQuadrant4LastPulse,	CLQua4B_Re_LastPulse_0,	    C_array,					1,	           C_unsigned,     		    C_NoRateNum             },  /*B相4象限无功脉冲尾数*/
	{CQua4B_Re_LastPulse_0,		CLQua4B_Re_LastPulse_0,	    C_unsigned,	   			    0,	           C_unsigned,     		    C_NoRateNum             },  /*B相4象限无功脉冲尾数*/
   	{C_Fre_CQuadrant4LastPulse,	CLQua4C_Re_LastPulse_0,	    C_array,					1,	           C_unsigned,     		    C_NoRateNum             },  /*C相4象限无功脉冲尾数*/
	{CQua4C_Re_LastPulse_0,		CLQua4C_Re_LastPulse_0,	    C_unsigned,	   			    0,	           C_unsigned,     		    C_NoRateNum             },  /*C相4象限无功脉冲尾数*/
};
#define Str_FrozenConvert_Table_Len_1   ( sizeof(Str_FrozenConvert_Table) / sizeof(Struct_FrozenConvert_Type) )
const ushort16 Str_FrozenConvert_Table_Len = Str_FrozenConvert_Table_Len_1;

const Str_698EventReport_Type Str_698EventReport[]=
{
	{C_AlossvoltageEventNo,				0x01,	0x0007},
	{C_BlossvoltageEventNo,				0x00,	0x0008},
	{C_ClossvoltageEventNo,				0x00,	0x0009},
	{C_ALessvoltageEventNo,				0x01,	0x0107},
	{C_BLessvoltageEventNo,				0x00,	0x0108},
	{C_CLessvoltageEventNo,				0x00,	0x0109},
	{C_AOvervoltageEventNo,				0x01,	0x0207},
	{C_BOvervoltageEventNo,				0x00,	0x0208},
	{C_COvervoltageEventNo,				0x00,	0x0209},
	{C_ALossphaseEventNo,				0x01,	0x0307},
	{C_BLossphaseEventNo,				0x00,	0x0308},
	{C_CLossphaseEventNo,				0x00,	0x0309},
	{C_ALosscurrentEventNo,				0x01,	0x0407},
	{C_BLosscurrentEventNo,				0x00,	0x0408},
	{C_CLosscurrentEventNo,				0x00,	0x0409},
	{C_AOvercurrentEventNo,				0x01,	0x0507},
	{C_BOvercurrentEventNo,				0x00,	0x0508},
	{C_COvercurrentEventNo,				0x00,	0x0509},
	{C_AFailcurrentEventNo,				0x01,	0x0607},
	{C_BFailcurrentEventNo,				0x00,	0x0608},
	{C_CFailcurrentEventNo,				0x00,	0x0609},
	{C_TReversecurrentEventNo,			0x00,	0x0706},	/*山东不需要上报这个*/
	{C_AReversecurrentEventNo,			0x01,	0x0707},
	{C_BReversecurrentEventNo,			0x00,	0x0708},
	{C_CReversecurrentEventNo,			0x00,	0x0709},
	{C_AOverloadEventNo,				0x01,	0x0807},
	{C_BOverloadEventNo,				0x00,	0x0808},
	{C_COverloadEventNo,				0x00,	0x0809},
	{C_OverForwardActiveEventNo,		0x01,	0x0902},
	{C_OverReverseActiveEventNo,		0x01,	0x0A02},
	{C_1OverIdleDemandEventNo,			0x01,	0x0B06},
	{C_2OverIdleDemandEventNo,			0x00,	0x0B07},
	{C_3OverIdleDemandEventNo,			0x00,	0x0B08},
	{C_4OverIdleDemandEventNo,			0x00,	0x0B09},
	{C_OverpowerfactEventNo,        	0x01,	0x3B06},	/*20标准，由7类改成24类*/
	{C_AOverpowerfactEventNo,        	0x00,	0x3B07},
	{C_BOverpowerfactEventNo,        	0x00,	0x3B08},
	{C_COverpowerfactEventNo,        	0x00,	0x3B09},
	{C_TotalVoltageLoseEventNo,			0x01,	0x0D02},
	{C_ACPowerFailEventNo,          	0x01,	0x0E02},
	{C_ReversephaseVoltageEventNo,  	0x01,	0x0F02},
	{C_ReversephaseCurrentEventNo,  	0x01,	0x1002},
	{C_PowerfailEventNo,				0x01,	0x1102},
	{C_OpenMeterCoverEventNo,			0x01,	0x1B02},
	{C_OpenTerminalCoverEventNo,		0x01,	0x1C02},
	{C_UnbanlanceVoltageEventNo,		0x01,	0x1D02},
	{C_UnbanlanceCurrentEventNo,		0x01,	0x1E02},
	{C_MagneticCheckEventNo,			0x01,	0x2A02},
	{C_PowerAbnormalEventNo,			0x01,	0x2C02},
	{C_SUnbanlanceCurrentEventNo,		0x01,	0x2D02},
	{C_ProgramEventNo,					0x01,	0x1202},
	{C_TolClearEventNo,					0x01,	0x1302},
	{C_DemandClearEventNo,				0x01,	0x1402},
	{C_EventClearEventNo,				0x01,	0x1502},
	{C_AdjTimeEventNo,					0x01,	0x1602},
	{C_ProgPTEventNo,					0x01,	0x1702},
	{C_ProgPZEventNo,					0x01,	0x1802},
	{C_ProgWReEventNo,					0x01,	0x1902},
	{C_ProgSettDEventNo,				0x01,	0x1A02},
	{C_RelayOpenEventNo,				0x01,	0x1F02},
	{C_RelayCloseEventNo,				0x01,	0x2002},
	{C_ProgHolEventNo,					0x01,	0x2102},
	{C_ProgAcCEventNo,					0x01,	0x2202},
	{C_ProgReCEventNo,					0x01,	0x2302},
	{C_ProgTParaEventNo,				0x01,	0x2402},//费率表编程
	{C_ProgLadEventNo,					0x01,	0x2502},//阶梯表编程
	{C_Key_UpdateEventNo,				0x01,	0x2602},//密钥更新
	{C_AbnorCEventNo,					0x01,	0x2702},//异常插卡
	{C_BuyCurrEventNo,					0x01,	0x2802},//购电记录
	{C_ReturnMoneyEventNo,				0x01,	0x2902},//退费
	{C_RelayFaEndEnEventNo,				0x01,	0x2B02},
	{C_MeterFaEventNo,					0x01,	0x2F02},
	{C_ClockFaEventNo,					0x01,	0x2E02},
	{C_BroadcastTimeEventNo,			0x01,	0x3C02},
	{C_NeutralCurrentAbnormalEventNo,	0x01,	0x4002},
#if 0	/*原来屏蔽*/
	{C_ReversecurrentEventNo,			0x01,	0x0706},
#endif
};
#define Str_698EventReport_Len_1   ( sizeof(Str_698EventReport) / sizeof(Str_698EventReport_Type) )
const ushort16 Str_698EventReport_Len = Str_698EventReport_Len_1;


#if 0	/*原来屏蔽*/
const Str_698EventReport_Type Str_698EventReport[Str_698EventReport_Len]=
{
	{C_AlossvoltageEventNo,			0,	CLossVolage_Report_Mode,		CALossVolage_Report_Record},
	{C_BlossvoltageEventNo,			1,	CLossVolage_Report_Mode,		CBLossVolage_Report_Record},
	{C_ClossvoltageEventNo,			2,	CLossVolage_Report_Mode,		CCLossVolage_Report_Record},
	{C_ALessvoltageEventNo,			3,	CLowVolage_Report_Mode,			CALowVolage_Report_Record},
	{C_BLessvoltageEventNo,			4,	CLowVolage_Report_Mode,			CBLowVolage_Report_Record},
	{C_CLessvoltageEventNo,			5,	CLowVolage_Report_Mode,			CCLowVolage_Report_Record},
	{C_AOvervoltageEventNo,			6,	COverVolage_Report_Mode,		CAOverVolage_Report_Record},
	{C_BOvervoltageEventNo,			7,	COverVolage_Report_Mode,		CBOverVolage_Report_Record},
	{C_COvervoltageEventNo,			8,	COverVolage_Report_Mode,		CCOverVolage_Report_Record},
	{C_ALossphaseEventNo,			9,	CBreakVol_Report_Mode,			CABreakVol_Report_Record},
	{C_BLossphaseEventNo,			10,	CBreakVol_Report_Mode,			CBBreakVol_Report_Record},
	{C_CLossphaseEventNo,			11,	CBreakVol_Report_Mode,			CCBreakVol_Report_Record},
	{C_ALosscurrentEventNo,			12,	CLossCurr_Report_Mode,			CALossCurr_Report_Record},
	{C_BLosscurrentEventNo,			13,	CLossCurr_Report_Mode,			CBLossCurr_Report_Record},
	{C_CLosscurrentEventNo,			14,	CLossCurr_Report_Mode,			CCLossCurr_Report_Record},
	{C_AOvercurrentEventNo,			15,	COverCurr_Report_Mode,			CAOverCurr_Report_Record},
	{C_BOvercurrentEventNo,			16,	COverCurr_Report_Mode,			CBOverCurr_Report_Record},
	{C_COvercurrentEventNo,			17,	COverCurr_Report_Mode,			CCOverCurr_Report_Record},
	{C_AFailcurrentEventNo,			18,	CBreakCurr_Report_Mode,			CABreakCurr_Report_Record},
	{C_BFailcurrentEventNo,			19,	CBreakCurr_Report_Mode,			CBBreakCurr_Report_Record},
	{C_CFailcurrentEventNo,			20,	CBreakCurr_Report_Mode,			CCBreakCurr_Report_Record},
	{C_AReversecurrentEventNo,		21,	CTrendRev_Report_Mode,			CATrendRev_Report_Record},
	{C_BReversecurrentEventNo,		22,	CTrendRev_Report_Mode,			CBTrendRev_Report_Record},
	{C_CReversecurrentEventNo,		23,	CTrendRev_Report_Mode,			CCTrendRev_Report_Record},
	{C_AOverloadEventNo,			24,	COverLoad_Report_Mode,			CAOverLoad_Report_Record},
	{C_BOverloadEventNo,			25,	COverLoad_Report_Mode,			CBOverLoad_Report_Record},
	{C_COverloadEventNo,			26,	COverLoad_Report_Mode,			CCOverLoad_Report_Record},
	{C_OverForwardActiveEventNo,	27,	CAcDemandOv_Report_Mode,		CAcDemandOv_Report_Record},
	{C_OverReverseActiveEventNo,	28,	CPosDemandOv_Report_Mode,		CPosDemandOv_Report_Record},
	{C_1OverIdleDemandEventNo,		29,	CReDemandOv_Report_Mode,		C1ReDemandOv_Report_Record},
	{C_2OverIdleDemandEventNo,		30,	CReDemandOv_Report_Mode,		C2ReDemandOv_Report_Record},
	{C_3OverIdleDemandEventNo,		31,	CReDemandOv_Report_Mode,		C3ReDemandOv_Report_Record},
	{C_4OverIdleDemandEventNo,		32,	CReDemandOv_Report_Mode,		C4ReDemandOv_Report_Record},
	{C_OverpowerfactEventNo,		33,	CPowerFactor_Report_Mode,		CPowerFactor_Report_Record},
	{C_TotalVoltageLoseEventNo,		34,	CAllLossVolage_Report_Mode,		CAllLossVolage_Report_Record},
	{C_ACPowerFailEventNo,			35,	CAuxPowDown_Report_Mode,		CAuxPowDown_Report_Record},
	{C_ReversephaseVoltageEventNo,	36,	CReversedVoltage_Report_Mode,	CReversedVoltage_Report_Record},
	{C_ReversephaseCurrentEventNo,	37,	CReversedCurrent_Report_Mode,	CReversedCurrent_Report_Record},
	{C_PowerfailEventNo,			38,	CPowerOff_Report_Mode,			CPowerOff_Report_Record},
	{C_OpenMeterCoverEventNo,		48,	COpenW_Report_Mode,				COpenW_Report_Record},
	{C_OpenTerminalCoverEventNo,	49,	COpenCW_Report_Mode,			COpenCW_Report_Record},
	{C_UnbanlanceVoltageEventNo,	50,	CNoBalVol_Report_Mode,			CNoBalVol_Report_Record},
	{C_UnbanlanceCurrentEventNo,	51,	CNoBalCurr_Report_Mode,			CNoBalCurr_Report_Record},
	{C_MagneticCheckEventNo,		63,	CConMEndEn_Report_Mode,			CConMEndEn_Report_Record},
	{C_PowerAbnormalEventNo,		65,	CPowerFa_EndT_Report_Mode,		CPowerFa_EndT_Report_Record},
	{C_SUnbanlanceCurrentEventNo,	66,	CSeriNoBalCurr_Report_Mode,		CSeriNoBalCurr_Report_Record},
	{C_ProgramEventNo,				39,	CProgram_Report_Mode,			CProgram_Report_Record},
	{C_TolClearEventNo,				40,	CTolClear_Report_Mode,			CTolClear_Report_Record},
	{C_DemandClearEventNo,			41,	CDemandClear_Report_Mode,		CDemandClear_Report_Record},
	{C_EventClearEventNo,			42,	CEventClear_Report_Mode,		CEventClear_Report_Record},
	{C_AdjTimeEventNo,				43,	CAdjTime_Report_Mode,			CAdjTime_Report_Record},
	{C_ProgPTEventNo,				44,	CProgPT_Report_Mode,			CProgPT_Report_Record},
	{C_ProgPZEventNo,				45,	CProgPZ_Report_Mode,			CProgPZ_Report_Record},
	{C_ProgWReEventNo,				46,	CProgWRe_Report_Mode,			CProgWRe_Report_Record},
	{C_ProgSettDEventNo,			47,	CProgSettD_Report_Mode,			CProgSettD_Report_Record},
	{C_RelayOpenEventNo,			52,	CRelayOpen_Report_Mode,			CRelayOpen_Report_Record},
	{C_RelayCloseEventNo,			53,	CRelayClose_Report_Mode,		CRelayClose_Report_Record},
	{C_ProgHolEventNo,				54,	CProgHol_Report_Mode,			CProgHol_Report_Record},
	{C_ProgAcCEventNo,				55,	CProgAcC_Report_Mode,			CProgAcC_Report_Record},
	{C_ProgReCEventNo,				56,	CProgReC_Report_Mode,			CProgReC_Report_Record},
	{C_ProgTParaEventNo,			57,	CProgTPara_Report_Mode,			CProgTPara_Report_Record},
	{C_ProgLadEventNo,				58,	CProgLad_Report_Mode,			CProgLad_Report_Record},
	{C_Key_UpdateEventNo,			59,	CKey_Update_Report_Mode,		CKey_Update_Report_Record},
	{C_AbnorCEventNo,				60,	CAbnorC_Report_Mode,			CAbnorC_Report_Record},
	{C_BuyCurrEventNo,				61,	CBuyCurr_Report_Mode,			CBuyCurr_Report_Record},
	{C_ReturnMoneyEventNo,			62,	CReturnMoney_Report_Mode,		CReturnMoney_Report_Record},
	{C_RelayFaEndEnEventNo,			64,	CRelayFaEndEn_Report_Mode,		CRelayFaEndEn_Report_Record},
	{C_MeterFaEventNo,				67,	CMeteringChipFault_Report_Mode,	CMeteringChipFault_Report_Record},
	{C_ClockFaEventNo,				68,	CClockFault_Report_Mode,		CClockFault_Report_Record},
	{C_ReversecurrentEventNo,		69,	CTrendRev_Report_Mode,			CTrendRev_Report_Record},
};
#define Str_698EventReport_Len  sizeof(Str_698EventReport)/sizeof(Str_698EventReport_Type)
#endif

#if 0
/*****************************************************************************************************************
*Function:uchar8 Get_MsgParmLen(uchar8 MsgPT_No,uchar8 *pMsgParmLen)
*Description:	根据输入的信息帧参数或者该信息帧对应的数据长度
*Input:	MsgPT_No信息帧参数名称，pMsgParmLen数据长度存放地址
*Output:  pMsgParmLen数据长度，其中返回0xFF表示该参数长度不定
*Return:	 C_OK表示信息帧参数正确返回，C_Err表示该参数信息帧长度返回错误或者没有查找到该信息帧参数
*Calls:
*Called By:
*Influence:
*Author:	G.G
*Tips:
*Others:
******************************************************************************************************************/
uchar8 PF_Get_MsgParmLen(uchar8 MsgPT_No,uchar8 *pMsgParmLen)
{
	uchar8 V_ucFlay,i;

	V_ucFlay = C_NoData;
	for(i=0;i<C_ParameterTypes;i++)
	{
		if(MsgPT_No == C_ParameterTypesTable[i][0])
		{
			*pMsgParmLen = C_ParameterTypesTable[i][1];
			V_ucFlay = C_OK;
			break;
		}
	}
	return V_ucFlay;
}
#endif

/*******************************************************************************
函数原型： void PF_Long64ToBuffer8(uchar8 *BytesBuffer, ulong64 *DoubleWordBuufer, uchar8 Len)
功能描述： 1个ulong64数转换为Len个uchar8
输入参数： DoubleWordBuufer：64位数据地址；Len：uchar8数个数
输出参数： BytesBuffer：8位数据低地址
返回参数： 无
调用位置:
备    注： 大端模式
*******************************************************************************/
void PF_Ulong64ToBuffer8_698(uchar8 *BytesBuffer, ulong64 *DoubleWordBuufer, uchar8 Len)
{
	ulong64 V_ulTemp;
	uchar8 V_ucTemp;

    V_ulTemp = *DoubleWordBuufer;
	for(V_ucTemp = 0; V_ucTemp < Len; V_ucTemp++)
	{
		BytesBuffer[V_ucTemp] = (uchar8) ( V_ulTemp >> ( 8 * (Len - V_ucTemp - 1 ) ) );
	}
}
/*******************************************************************************
函数原型： void PF_Buffer8ToLong64(uchar8 *BytesBuffer, ulong64 *DoubleWordBuufer, uchar8 Len)
功能描述： 8个uchar8数转换为1个ulong64
输入参数： BytesBuffer：8位数据低地址；Len：uchar8数个数
输出参数： DoubleWordBuufer：64位数据地址
返回参数： 无
调用位置:
备    注： 大端模式
*******************************************************************************/
void PF_Buffer8ToUlong64_698(uchar8 *BytesBuffer, ulong64 *DoubleWordBuufer, uchar8 Len)
{
	ulong64 V_ulTemp = 0;
	uchar8  V_uci;

	for(V_uci = 0; V_uci < Len; V_uci++)
	{
		V_ulTemp <<= 8;
		V_ulTemp |= BytesBuffer[V_uci];
	}

	*DoubleWordBuufer = V_ulTemp;
}

/*zlj新增*/
/*******************************************************************************
函数原型: uchar8 PF_Is_Buf_AllFixedData(uchar8 *P_ucData, uchar8 V_ucFixedData,  ushort16 V_usDataLen)
功能描述: 判断指定起始地址开始的，指定长度的数据是否都等于V_ucFixedData
输入参数: uchar8 *P_ucData：数据起始地址;uchar8 V_ucFixedData：数据值; ushort16 V_usDataLen：数据长度，
输出参数: 无
返回参数: C_OK：全部都等于V_data，C_Error：不全部都等于V_data
调用位置:
备    注:
*******************************************************************************/
uchar8 PF_Is_Buf_AllFixedData(uchar8 *P_ucData, uchar8 V_ucFixedData,  ushort16 V_usDataLen)
{
	uchar8 V_ucReturnTemp = C_OK;
    ushort16 V_usi;

	for (V_usi = 0; V_usi < V_usDataLen; V_usi++)
	{
		if (*(P_ucData + V_usi) != V_ucFixedData)
		{
            V_ucReturnTemp = C_Error;
			break;
		}
	}
	return V_ucReturnTemp;
}

/*******************************************************************************
函数原型: uchar8 PF_HextoBCDOneBytes(uchar8 V_ucData)
功能描述: 1字节Hex转换为1字节BCD
输入参数: uchar8 V_ucData:1字节HEX
输出参数: 无
返回参数: 1字节BCD
调用位置:
备    注:
*******************************************************************************/
uchar8 PF_HextoBCDOneBytes(uchar8 V_ucData)
{
	uchar8 V_DataChagn;
	V_DataChagn = V_ucData / 10;
	V_DataChagn = V_DataChagn << 4;
	V_DataChagn |= V_ucData % 10;
	return V_DataChagn;
}

/*******************************************************************************
函数原型: void PF_Data_Week_Time_BCDtoData_Time_s_HEX(uchar8 *V_ucBCDBuffer, uchar8 *V_ucHexBuffer)
功能描述: 将RTC提供的YYMMDDWWHHMMSS转换为698格式的Data_Time_s
输入参数: uchar8 *V_ucBCDBuffer:RTC提供的YYMMDDWWHHMMSS
输出参数: uchar8 *V_ucHexBuffer:698格式的Data_Time_s
返回参数: 无
调用位置:
备    注:
*******************************************************************************/
void PF_Data_Week_Time_BCDtoData_Time_s_HEX(uchar8 *V_ucBCDBuffer, uchar8 *V_ucHexBuffer)
{
	uchar8 V_ucI = 0, V_ucDataBuffer[CLDate_Time] = {0};
    ulong32 V_ulHexYear;

	V_ucDataBuffer[6] = 0x20;	/*年格式为YYYY，固定为0x20年*/
	for(V_ucI = 0; V_ucI < 6; V_ucI++)	/*RTC格式YYMMDDWWhhmmss去除WW*/
	{
		if(V_ucI < 3)
		{
			V_ucDataBuffer[V_ucI] = V_ucBCDBuffer[V_ucI];
		}
		else
		{
			V_ucDataBuffer[V_ucI] = V_ucBCDBuffer[V_ucI + 1];	/*去除WW*/
		}
	}

	for(V_ucI = 0; V_ucI < 5; V_ucI++)
	{
		V_ucDataBuffer[V_ucI] = PF_BCDtoHexOneByte( V_ucDataBuffer[V_ucI] );
	}

	PF_BCDtoHexBytes(&V_ucDataBuffer[V_ucI], &V_ulHexYear, 0x02);
	PF_Ulong32ToBuffer4(&V_ucDataBuffer[V_ucI], &V_ulHexYear, 0x02);

    PF_CopyDataBytes(V_ucDataBuffer, V_ucHexBuffer, CLDate_Time);
}

/*******************************************************************************
函数原型: void PF_Data_Time_s_HEXtoData_Week_Time_BCD(uchar8 *V_ucHexBuffer, uchar8 *V_ucBCDBuffer)
功能描述: 将698格式的Data_Time_s转换为RTC提供的YYMMDDWWHHMMSS
输入参数: uchar8 *V_ucHexBuffer:698格式的Data_Time_s
输出参数: uchar8 *V_ucBCDBuffer:RTC提供的YYMMDDWWHHMMSS
返回参数: 无
调用位置:
备    注:
*******************************************************************************/
void PF_Data_Time_s_HEXtoData_Week_Time_BCD(uchar8 *V_ucHexBuffer, uchar8 *V_ucBCDBuffer)
{
	uchar8 V_ucI = 0, V_ucDataBuffer[7] = {0}, V_ucDataLength;
    ulong32 V_ulHexYear;

	for(V_ucI = 0; V_ucI < 5; V_ucI++)
	{
		V_ucDataBuffer[V_ucI] = PF_HextoBCDOneBytes(V_ucHexBuffer[V_ucI]);
	}

	V_ucDataLength = 0x02;
	PF_BufferXToUlong32(&V_ucHexBuffer[V_ucI], &V_ulHexYear, V_ucDataLength);
	PF_HextoBCDBytes(&V_ulHexYear, &V_ucDataBuffer[V_ucI], &V_ucDataLength);

	V_ucBCDBuffer[3] = PF_Cal_Week(&V_ucDataBuffer[3]);	/*计算周次,格式为YYMMDDhhmmss*/

	for(V_ucI = 0; V_ucI < 3; V_ucI++)
	{
		V_ucBCDBuffer[V_ucI] = V_ucDataBuffer[V_ucI];
	}

	for(V_ucI = 3; V_ucI < 6; V_ucI++)
	{
		V_ucBCDBuffer[V_ucI+1] = V_ucDataBuffer[V_ucI];
	}
}
