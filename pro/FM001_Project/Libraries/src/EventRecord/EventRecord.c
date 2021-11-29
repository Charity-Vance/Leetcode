/*****************************************************************************************
Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     EventRecord.c
Version:       V1
Date:          2014-04-01
Description:   事件记录文件
Function List:
****************************************************************************************
History1:      第1次修改
内容1. Date:2021.09
 	   Author:DB
       Modification:FH001第一版修改
**********************************************
内容2. Date:
   	   Author:
       Modification:
********************************************************************************
History2:      第2次修改
内容1. Date:
  	   Author:
       Modification:
**********************************************
内容2. Date:
   	   Author:
       Modification:
****************************************************************************************/

#include "Public.h"
#include "EventRecord.h"
#include "Communication.h"
#include "SecurityCommunication.h"

/***********************************************/
/*宏定义*/
const	uchar8	C_ucAhEquivalent[4]={0xA0, 0x8C, 0x00, 0x00};/*0.01Ah当量, 每秒累加3位小数电流，3600*10=8CA0(HEX)*/
const	uchar8	C_ucAddAh[4]={01, 00, 00, 00};				/*加0.01Ah的常量*/
const	uchar8	C_ucAddOneMin[4]={01, 00, 00, 00};			/*累计时间加1*/
const	uchar8	C_uc3P3WVotageAngle1[2]={0x2C, 0x01};		/*三相三线逆相序电压角度1，30.0度，hex*/
const	uchar8	C_uc3P3WVotageAngle2[2]={0x7E, 0x04};		/*三相三线逆相序电压角度2，115.0度，hex*/
const	uchar8	C_uc3P3WCurrentAngle1[2]={0x84, 0x03};		/*三相三线逆相序电流角度1，90.0度，hex*/
const	uchar8	C_uc3P3WCurrentAngle2[2]={0xDC, 0x05};		/*三相三线逆相序电流角度2，150.0度，hex*/
		uchar8	GV_ucEvent_Hstate[C_EventNoLength];			/*事件历史状态*/
		uchar8	GV_ucEvent_JudgeTimer[C_EventNoLength]; 	/*事件判断定时器*/
		uchar8 	GV_ucEvent_SymbolHstate[C_EventSymbolLength];/*显示符号历史状态*/
		Str_BeeperAlerm_Type GStr_BackLightAlarm;		    /*背光报警*/
		Str_BeeperAlerm_Type GStr_Alarmoutput; 			    /*报警输出报警*/
		Str_BeeperAlerm_Type GStr_BellAlarm;				/*小铃铛显示报警*/
		uchar8 GV_ucBellAlarm_Hstate[C_AlarmTempLength];    /*小铃铛组合历史状态*/
		uchar8 GV_ucAlarmoutput_Hstate[C_AlarmTempLength];	/*报警输出组合历史状态*/
		uchar8 GV_ucBackLightAlarm_Hstate[C_AlarmTempLength];/*背光报警*/
        uchar8 GV_ucReversecurrentTimes;                     /*潮流反向初始化方向时不报警*/
        uchar8 GV_ucDirectionExchange;                      /*潮流反向正向/反向，方向改变标识*/

/*****************************************************************************************/
/*以下为事件结构体定义*/
/*****************************************************************************************/
Str_LpowerTvoltagelose_Type	GStr_TotalvoltageloseStr;		/*全失压*/
Str_LpowerTvoltagelose_Type	GStr_PowerfailStr;				/*掉电*/
Str_CoverRecord_Type		GStr_OpenMeterCoverStr;			/*开表盖*/
Str_CoverRecord_Type		GStr_OpenTerminalCoverStr;		/*开端钮盖*/
Str_ACPowerFail_Type		GStr_PowerabnormalStr;			/*电源异常*/
Str_ACPowerFail_Type		GStr_ACPowerFailStr;				/*辅助电源失电*/
Str_ActiveDemand_Type 		GStr_OverForwardActiveStr;		/*正向有功需量超限*/
Str_ActiveDemand_Type 		GStr_OverReverseActiveStr;		/*反向有功需量超限*/
Str_ActiveDemand_Type 		GStr_Over1IdleDemandStr;			/*第1象限无功需量超限*/
Str_ActiveDemand_Type 		GStr_Over2IdleDemandStr;			/*第2象限无功需量超限*/
Str_ActiveDemand_Type 		GStr_Over3IdleDemandStr;			/*第3象限无功需量超限*/
Str_ActiveDemand_Type 		GStr_Over4IdleDemandStr;			/*第4象限无功需量超限*/
Str_Unbanlance_Type 		GStr_UnbanlanceVoltageStr;		/*电压不平衡*/
Str_Unbanlance_Type 		GStr_UnbanlanceCurrentStr;		/*电流不平衡*/
Str_Unbanlance_Type 		GStr_SUnbanlanceCurrentStr;		/*电流严重不平衡*/
Str_AhMeter_Type			GStr_AlossvoltageStr;			/*A相失压*/
Str_AhMeter_Type			GStr_BlossvoltageStr;			/*B相失压*/
Str_AhMeter_Type			GStr_ClossvoltageStr;			/*C相失压*/
Str_AhMeter_Type			GStr_ALossphaseStr;				/*A相断相*/
Str_AhMeter_Type			GStr_BLossphaseStr;				/*B相断相*/
Str_AhMeter_Type			GStr_CLossphaseStr;				/*C相断相*/
Str_AhMeter_Type			GStr_ALessvoltageStr;			/*A相欠压*/
Str_AhMeter_Type			GStr_BLessvoltageStr;			/*B相欠压*/
Str_AhMeter_Type			GStr_CLessvoltageStr;			/*C相欠压*/
Str_AhMeter_Type			GStr_AOvervoltageStr;			/*A相过压*/
Str_AhMeter_Type			GStr_BOvervoltageStr;			/*B相过压*/
Str_AhMeter_Type			GStr_COvervoltageStr;			/*C相过压*/
Str_OtherMeter_Type 		GStr_ReversephaseVoltageStr;		/*电压逆相序*/
Str_OtherMeter_Type 		GStr_ReversephaseCurrentStr;		/*电流逆相序*/
Str_OtherMeter_Type			GStr_ALosscurrentStr;			/*A相失流*/
Str_OtherMeter_Type 		GStr_BLosscurrentStr;			/*B相失流*/
Str_OtherMeter_Type 		GStr_CLosscurrentStr;			/*C相失流*/
Str_OtherMeter_Type 		GStr_AFailcurrentStr;			/*A相断流*/
Str_OtherMeter_Type 		GStr_BFailcurrentStr;			/*B相断流*/
Str_OtherMeter_Type 		GStr_CFailcurrentStr;			/*C相断流*/
Str_OtherMeter_Type 		GStr_AOvercurrentStr;			/*A相过流*/
Str_OtherMeter_Type 		GStr_BOvercurrentStr;			/*B相过流*/
Str_OtherMeter_Type 		GStr_COvercurrentStr;			/*C相过流*/
Str_OtherMeter_Type 		GStr_TReversecurrentStr;			/*总功率反向*/
Str_OtherMeter_Type 		GStr_AReversecurrentStr;			/*A相功率反向*/
Str_OtherMeter_Type 		GStr_BReversecurrentStr;			/*B相功率反向*/
Str_OtherMeter_Type 		GStr_CReversecurrentStr;			/*C相功率反向*/
Str_OtherMeter_Type 		GStr_AOverloadStr;				/*A相过载*/
Str_OtherMeter_Type			GStr_BOverloadStr;				/*B相过载*/
Str_OtherMeter_Type 		GStr_COverloadStr;				/*C相过载*/
Str_OtherMeter_Type 		GStr_OverpowerfactStr;			/*总功率因数超下限*/
Str_OtherMeter_Type 		GStr_AOverpowerfactStr;			/*A相功率因数超下限*/
Str_OtherMeter_Type 		GStr_BOverpowerfactStr;			/*B相功率因数超下限*/
Str_OtherMeter_Type 		GStr_COverpowerfactStr;			/*C相功率因数超下限*/
Str_OtherMeter_Type			GStr_ConMStr;					/*恒定磁场干扰*/
Str_OtherMeter_Type			GStr_MeterFaStr;					/*计量芯片故障*/
Str_OtherMeter_Type			GStr_ClockFaStr;					/*时钟故障*/
Str_OtherMeter_Type			GStr_NeutralAbnormalStr;			/*零线电流异常*/
Str_OtherMeter_Type			GStr_BroadcastTimeStr;			/*零线电流异常*/

/*****************************************************************************************/
/*表格的顺序不能随意调整！！*/
/*****************************************************************************************/
const	uchar8	Event_ChooseTableNo[C_EventNoLength][3]=
{/*事件发生时获取数据			事件结束时获取数据*/
	{C_NULL,					C_NULL,					C_3P4W				},/*全失压*/
	{C_NULL,					C_NULL,					C_3P4W				},/*辅助电源失电*/
	{C_NULL,					C_NULL,					C_3P4W				},/*掉电*/
	{C_OpenCoverChooseNo,		C_OpenCoverChooseNo,	C_3P4W				},/*开表盖*/
  	{C_OpenCoverChooseNo,    	C_OpenCoverChooseNo,	C_3P4W				},/*开端钮盖*/
	{C_PowerAbnormalChooseNo,	C_PowerAbnormalChooseNo,C_3P4W				},/*恒定磁场干扰*/
	{C_PowerAbnormalChooseNo,	C_NULL,					C_3P4W				},/*电源异常*/
	{C_NULL,       				C_NULL,					C_3P4W				},/*正向有功需量超限*/
	{C_NULL,       				C_NULL,					C_3P4W				},/*反向有功需量超限*/
	{C_NULL,       				C_NULL,					C_3P4W				},/*1象限无功需量超限*/
	{C_NULL,       				C_NULL,					C_3P4W				},/*2象限无功需量超限*/
	{C_NULL,       				C_NULL,					C_3P4W				},/*3象限无功需量超限*/
	{C_NULL,       				C_NULL,					C_3P4W				},/*4象限无功需量超限*/
	{C_EERAMChooseNo,       	C_EEChooseNo,			C_3P4W				},/*A相失压*/
	{C_EERAMChooseNo,       	C_EEChooseNo,			C_3P3W				},/*B相失压*/
	{C_EERAMChooseNo,       	C_EEChooseNo,			C_3P4W				},/*C相失压*/
	{C_EERAMChooseNo,       	C_EEChooseNo,			C_3P4W				},/*A相欠压*/
	{C_EERAMChooseNo,       	C_EEChooseNo,			C_3P3W				},/*B相欠压*/
	{C_EERAMChooseNo,       	C_EEChooseNo,			C_3P4W				},/*C相欠压*/
	{C_EERAMChooseNo,       	C_EEChooseNo,			C_3P4W				},/*A相过压*/
	{C_EERAMChooseNo,       	C_EEChooseNo,			C_3P3W				},/*B相过压*/
	{C_EERAMChooseNo,       	C_EEChooseNo,			C_3P4W				},/*C相过压*/
	{C_EERAMChooseNo,       	C_EEChooseNo,			C_3P4W				},/*A相断相*/
	{C_EERAMChooseNo,       	C_EEChooseNo,			C_3P3W				},/*B相断相*/
	{C_EERAMChooseNo,       	C_EEChooseNo,			C_3P4W				},/*C相断相*/
	{C_EEChooseNo,       		C_EEChooseNo,			C_3P4W				},/*电压逆相序*/
	{C_EEChooseNo,       		C_EEChooseNo,			C_3P4W				},/*电流逆相序*/
	{C_EEChooseNo,       		C_EEChooseNo,			C_3P4W				},/*电压不平衡*/
	{C_EEChooseNo,       		C_EEChooseNo,			C_3P4W				},/*电流不平衡*/
	{C_EERAMChooseNo,       	C_EEChooseNo,			C_3P4W				},/*A相失流*/
	{C_EERAMChooseNo,       	C_EEChooseNo,			C_3P3W				},/*B相失流*/
	{C_EERAMChooseNo,       	C_EEChooseNo,			C_3P4W				},/*C相失流*/
	{C_EERAMChooseNo,       	C_EEChooseNo,			C_3P4W				},/*A相过流*/
	{C_EERAMChooseNo,      		C_EEChooseNo,			C_3P3W				},/*B相过流*/
	{C_EERAMChooseNo,      		C_EEChooseNo,			C_3P4W				},/*C相过流*/
	{C_EERAMChooseNo,      		C_EEChooseNo,			C_3P4W				},/*A相断流*/
	{C_EERAMChooseNo,      		C_EEChooseNo,			C_3P3W				},/*B相断流*/
	{C_EERAMChooseNo,      		C_EEChooseNo,			C_3P4W				},/*C相断流*/
	{C_EEChooseNo,    			C_EEChooseNo,			C_3P4W				},/*总功率反向*/
	{C_EEChooseNo,    			C_EEChooseNo,			C_3P4W				},/*A相功率反向*/
	{C_EEChooseNo,    			C_EEChooseNo,			C_3P3W				},/*B相功率反向*/
	{C_EEChooseNo,    			C_EEChooseNo,			C_3P4W				},/*C相功率反向*//*三相四线中判断*/
	{C_EEChooseNo,       		C_EEChooseNo,			C_3P4W				},/*A相过载*/
	{C_EEChooseNo,       		C_EEChooseNo,			C_3P3W				},/*B相过载*/
	{C_EEChooseNo,       		C_EEChooseNo,			C_3P4W				},/*C相过载*/
	{C_OverPowerfactChooseNo,	C_OverPowerfactChooseNo,C_3P4W				},/*总功率因数超下限*/
	{C_OverPowerfactChooseNo,	C_OverPowerfactChooseNo,C_3P3W				},/*A相功率因数超下限*/
	{C_OverPowerfactChooseNo,	C_OverPowerfactChooseNo,C_3P3W				},/*B相功率因数超下限*/
	{C_OverPowerfactChooseNo,	C_OverPowerfactChooseNo,C_3P3W				},/*C相功率因数超下限*//*三相四线中判断*/
	{C_EEChooseNo,       		C_EEChooseNo,			C_3P4W				},/*电流严重不平衡*/
#if 0
	{C_EEChooseNo,       		C_NULL,					C_3P4W				},/*总潮流反向*/
#endif
	{C_NULL,			        C_NULL,				    C_3P4W				},/*计量芯片故障*/
	{C_NULL,			        C_NULL,				    C_3P4W				},/*时钟故障*/
	{C_NULL,			        C_NULL,				    C_3P3W				}/*零线电流异常*/
};

/*****************************************************************************************/
/*表格的顺序不能随意调整！！*/
/*****************************************************************************************/
/*事件判断延时时间表格*/
const	ulong32	Event_Delaytime[C_EventNoLength]=
{	/*判断延时时间数据标识*/
	CLossVolage_Delay_T,		/*失压事件判断延时时间*/
	C_NULL,						/*辅助电源掉电*/
	C_NULL,						/*掉电*/
	C_NULL,						/*开表盖*/
	C_NULL,						/*开端钮盖*/
	C_NULL,						/*恒定磁场干扰*/
	C_NULL,						/*电源异常*/
	CPosAcDemandOv_Delay_T,		/*需量超限事件判定延时时间*/
	CRevAcDemandOv_Delay_T,		/*需量超限事件判定延时时间*/
	CReDemandOv_Delay_T,		/*需量超限事件判定延时时间*/
	CReDemandOv_Delay_T,		/*需量超限事件判定延时时间*/
	CReDemandOv_Delay_T,		/*需量超限事件判定延时时间*/
	CReDemandOv_Delay_T,		/*需量超限事件判定延时时间*/
	CLossVolage_Delay_T,		/*失压事件判断延时时间（A相）*/
	CLossVolage_Delay_T,		/*失压事件判断延时时间（B相）*/
	CLossVolage_Delay_T,		/*失压事件判断延时时间（C相）*/
	CLowVolage_Delay_T,			/*欠压事件判断延时时间（A相）*/
	CLowVolage_Delay_T,			/*欠压事件判断延时时间（B相）*/
	CLowVolage_Delay_T,			/*欠压事件判断延时时间（C相）*/
	COverVolage_Delay_T,		/*过压事件判断延时时间（A相）*/
	COverVolage_Delay_T,		/*过压事件判断延时时间（B相）*/
	COverVolage_Delay_T,		/*过压事件判断延时时间（C相）*/
	CBreakVol_Delay_T,			/*断相事件判断延时时间（A相）*/
	CBreakVol_Delay_T,			/*断相事件判断延时时间（B相）*/
	CBreakVol_Delay_T,			/*断相事件判断延时时间（C相）*/
	CReversedVoltage_Delay_T,	/*电压逆相序*/
	CReversedCurrent_Delay_T,	/*电流逆相序*/
	CNoBal_Vol_Delay_T,			/*电压不平衡率判断延时时间*/
	CNoBal_Curr_Delay_T,		/*电流不平衡率判断延时时间*/
	CLossCurr_Delay_T,			/*失流事件判断延时时间（A相）*/
	CLossCurr_Delay_T,			/*失流事件判断延时时间（B相）*/
	CLossCurr_Delay_T,			/*失流事件判断延时时间（C相）*/
	COverCurr_Delay_T,			/*过流事件判断延时时间（A相）*/
	COverCurr_Delay_T,			/*过流事件判断延时时间（B相）*/
	COverCurr_Delay_T,			/*过流事件判断延时时间（C相）*/
	CBreakCurr_Delay_T,			/*断流事件判断延时时间（A相）*/
	CBreakCurr_Delay_T,			/*断流事件判断延时时间（B相）*/
	CBreakCurr_Delay_T,			/*断流事件判断延时时间（C相）*/
	CPowerRev_Delay_T,			/*功率反向事件判断延时时间（总）*/
	CPowerRev_Delay_T,			/*功率反向事件判断延时时间（A相）*/
	CPowerRev_Delay_T,			/*功率反向事件判断延时时间（B相）*/
	CPowerRev_Delay_T,			/*功率反向事件判断延时时间（C相）*/
	COverLoad_Delay_T,			/*过载事件判断延时时间（A相）*/
	COverLoad_Delay_T,			/*过载事件判断延时时间（B相）*/
	COverLoad_Delay_T,			/*过载事件判断延时时间（C相）*/
	CPowerFactor_Delay_T,		/*功率因数超下限判断延时时间*/
	CPowerFactor_Delay_T,		/*功率因数超下限判断延时时间（A相）*/
	CPowerFactor_Delay_T,		/*功率因数超下限判断延时时间（B相）*/
	CPowerFactor_Delay_T,		/*功率因数超下限判断延时时间（C相）*/
	CSeriNoBal_Curr_Delay_T,	/*电流严重不平衡判断延时时间*/
#if 0
	CTrendRev_Delay_T,			/*潮流反向事件判断延时时间*/
#endif
	CMeterFa_Delay_T,			/*在置状态位时延时 计量芯片故障事件判断延时时间*/
#if 0
	CClockFa_Delay_T,			/*在置状态位时延时 时钟故障事件判断延时时间*/
#endif
	C_NULL,			            /*在置状态位时延时 时钟故障事件判断延时时间*/
    CNeutralAbnormal_Delay_T,   /*零线电流异常判定延迟时间*/
};
/*****************************************************************************************/
/*表格的顺序不能随意调整！！*/
/*****************************************************************************************/
/*事件判断延时时间默认表格*/
const uchar8 Event_DDelaytime[C_EventNoLength]=
{/*时间判断阀值默认数据*/
	C_Judge_Event_DefaultTime1,  /*与Event_Delaytime[]表格事件一一对应*/
	C_Judge_Time4,				/*辅助电源、开合盖和恒定磁场去抖由调度做*/
	C_PowerFail_Judge_Time,              /*掉电延时时间默认1s*/
	C_Judge_Time1,
	C_Judge_Time1,
	C_Judge_Time4,
	C_NULL,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Event_DefaultTime1,
	C_Judge_Time0,
    C_Judge_Event_DefaultTime1,
};
/*****************************************************************************************/
/*表格的顺序不能随意调整！！*/
/*****************************************************************************************/
/*事件起始结束时间标识码，用于判断事件发生恢复状态*/
const ulong32 EventHappenEndTime[]=
{/*事件起始时刻数据标识	事件结束时刻数据标识*/
	CAll_Loss_Vol_Note_1,		/*全失压，起始时刻有9个字节*/
	CAux_Pow_Down_Note_1,		/*辅助电源失电*/
	CPow_Down_Note_1,		/*掉电*/
	COpenW_Note_1,			/*开表盖*/
	COpenCW_Note_1,			/*开端钮盖*/
	CConM_Note_1,			/*恒定磁场干扰*/
	CPowerFa_Note_1,		/*电源异常*/
	CPos_Ac_De_Over_Note_1,		/*正向有功需量超限*/
	CRev_Ac_De_Over_Note_1,		/*反向有功需量超限*/
	CQua1_Re_De_Over_Note_1,	/*1象限无功需量超限*/
	CQua2_Re_De_Over_Note_1,	/*2象限无功需量超限*/
	CQua3_Re_De_Over_Note_1,	/*3象限无功需量超限*/
	CQua4_Re_De_Over_Note_1,	/*4象限无功需量超限*/
	CLossAVol_FF_1,			/*A相失压*/
	CLossBVol_FF_1,			/*B相失压*/
	CLossCVol_FF_1,			/*C相失压*/
	CLowAVol_FF_1,			/*A相欠压*/
	CLowBVol_FF_1,			/*B相欠压*/
	CLowCVol_FF_1,			/*C相欠压*/
	COverAVol_FF_1,			/*A相过压*/
	COverBVol_FF_1,			/*B相过压*/
	COverCVol_FF_1,			/*C相过压*/
	CBreakAVol_FF_1,		/*A相断相*/
	CBreakBVol_FF_1,		/*B相断相*/
	CBreakCVol_FF_1,		/*C相断相*/
	CRevPSVol_FF_1,			/*电压逆相序*/
	CRevPSCurr_FF_1,		/*电流逆相序*/
	CNoBalVol_FF_1,			/*电压不平衡*/
	CNoBalCurr_FF_1,		/*电流不平衡*/
	CLossACurr_FF_1,		/*A相失流*/
	CLossBCurr_FF_1,		/*B相失流*/
	CLossCCurr_FF_1,		/*C相失流*/
	COverACurr_FF_1,		/*A相过流*/
	COverBCurr_FF_1,		/*B相过流*/
	COverCCurr_FF_1,		/*C相过流*/
	CBreakACurr_FF_1,		/*A相断流*/
	CBreakBCurr_FF_1,		/*B相断流*/
	CBreakCCurr_FF_1,		/*C相断流*/
	CPowerTRev_FF_1,		/*总功率反向*/
	CPowerARev_FF_1,		/*A相功率反向*/
	CPowerBRev_FF_1,		/*B相功率反向*/
	CPowerCRev_FF_1,		/*C相功率反向*/
	COverALo_FF_1,			/*A相过载*/
	COverBLo_FF_1,			/*B相过载*/
	COverCLo_FF_1,			/*C相过载*/
	CPFactorT_FF_1,			/*总功率因数超下限*/
	CPFactorA_FF_1,		/*A相功率因数超下限*/
	CPFactorB_FF_1,		/*B相功率因数超下限*/
	CPFactorC_FF_1,		/*C相功率因数超下限*/
	CSevNoBalCurr_FF_1,		/*电流严重不平衡*/
#if 0
	C_NULL,
#endif
	CMeterFa_Note_1,		/*计量芯片故障*/
	CClockFa_Note_1,		/*时钟故障*/
    CNeutralCurrentAbnormal_Note_1,   /*零线电流异常*/
	CProgram_Note_1,		/*编程记录*/
	C_NULL,
	C_NULL,
	C_NULL,
	C_NULL,
	C_NULL,
	C_NULL,
	C_NULL,
	C_NULL,
	C_NULL,
	C_NULL,
	C_NULL,
	C_NULL,
	C_NULL,
	C_NULL,
	C_NULL,
	C_NULL,
	C_NULL,
	C_NULL,
	C_NULL,
	CRelayFa_Note_1,		/*负荷开关误动作*/
};
#define EventHappenEndTime_Len  sizeof(EventHappenEndTime)/sizeof(ulong32)

/*****************************************************************************************/
/*表格的顺序不能随意调整！！*/
/*****************************************************************************************/
/*读数据表格*/
const Str_CommunicateReadTable_Type	CommunicateReadTable[C_ReadDataLength]=
{
/*	DataCode,					*DataRAMAddr,					*CRCRAMAddr,						Length,						EventNo*/
/*	数据标识，					数据RAM地址，					结构体首地址，						数据长度，					事件号*/
	{CAll_Loss_Vol_Time,		GStr_TotalvoltageloseStr.AddTime,	&GStr_TotalvoltageloseStr.MeterState,	C_AddTime_Length,			C_TotalVoltageLoseEventNo	},/*0 CAll_Loss_Vol全失压总次数，时间*/
	{CAux_Pow_Down_Time,		GStr_ACPowerFailStr.AddTime,			&GStr_ACPowerFailStr.MeterState,			C_AddTime_Length,			C_ACPowerFailEventNo		},/*1 CAux_Pow_Down辅助电源总次数，时间*/
	{CLossA_Vol_Time,			GStr_AlossvoltageStr.AddTime,		GStr_AlossvoltageStr.Renewal,			C_AddTime_Length,			C_AlossvoltageEventNo		},/*2 A相失压总累计时间*/
	{CLossB_Vol_Time,			GStr_BlossvoltageStr.AddTime,		GStr_BlossvoltageStr.Renewal,			C_AddTime_Length,			C_BlossvoltageEventNo		},/*3 B相失压总累计时间*/
	{CLossC_Vol_Time,			GStr_ClossvoltageStr.AddTime,		GStr_ClossvoltageStr.Renewal,			C_AddTime_Length,			C_ClossvoltageEventNo		},/*4 C相失压总累计时间*/
	{CLowA_Vol_Time,			GStr_ALessvoltageStr.AddTime,		GStr_ALessvoltageStr.Renewal,			C_AddTime_Length,			C_ALessvoltageEventNo		},/*5 A相欠压总累计时间*/
	{CLowB_Vol_Time,			GStr_BLessvoltageStr.AddTime,		GStr_BLessvoltageStr.Renewal,			C_AddTime_Length,			C_BLessvoltageEventNo		},/*6 B相欠压总累计时间*/
	{CLowC_Vol_Time,			GStr_CLessvoltageStr.AddTime,		GStr_CLessvoltageStr.Renewal,			C_AddTime_Length,			C_CLessvoltageEventNo		},/*7 C相欠压总累计时间*/
	{COverA_Vol_Time,			GStr_AOvervoltageStr.AddTime,		GStr_AOvervoltageStr.Renewal,			C_AddTime_Length,			C_AOvervoltageEventNo		},/*8 A相过压总累计时间*/
	{COverB_Vol_Time,			GStr_BOvervoltageStr.AddTime,		GStr_BOvervoltageStr.Renewal,			C_AddTime_Length,			C_BOvervoltageEventNo		},/*9 B相过压总累计时间*/
	{COverC_Vol_Time,			GStr_COvervoltageStr.AddTime,		GStr_COvervoltageStr.Renewal,			C_AddTime_Length,			C_COvervoltageEventNo		},/*10 C相过压总累计时间*/
	{CBreakA_Vol_Time,			GStr_ALossphaseStr.AddTime,			GStr_ALossphaseStr.Renewal,				C_AddTime_Length,			C_ALossphaseEventNo			},/*A相断相总累计时间*/
	{CBreakB_Vol_Time,			GStr_BLossphaseStr.AddTime,			GStr_BLossphaseStr.Renewal,				C_AddTime_Length,			C_BLossphaseEventNo			},/*B相断相总累计时间*/
	{CBreakC_Vol_Time,			GStr_CLossphaseStr.AddTime,			GStr_CLossphaseStr.Renewal,				C_AddTime_Length,			C_CLossphaseEventNo			},/*C相断相总累计时间*/
	{CRevPS_Vol_Time,			GStr_ReversephaseVoltageStr.AddTime,	GStr_ReversephaseVoltageStr.AddTime,  	C_AddTime_Length,			C_ReversephaseVoltageEventNo},/*电压逆相序总累计时间*/
	{CRevPS_Curr_Time,			GStr_ReversephaseCurrentStr.AddTime,	GStr_ReversephaseCurrentStr.AddTime,  	C_AddTime_Length,			C_ReversephaseCurrentEventNo},/*电流逆相序总累计时间*/
	{CNoBal_Vol_Time,			GStr_UnbanlanceVoltageStr.AddTime,	GStr_UnbanlanceVoltageStr.Renewal,		C_AddTime_Length,			C_UnbanlanceVoltageEventNo	},/*电压不平衡总累计时间*/
	{CNoBal_Curr_Time,			GStr_UnbanlanceCurrentStr.AddTime,	GStr_UnbanlanceCurrentStr.Renewal,		C_AddTime_Length,			C_UnbanlanceCurrentEventNo	},/*电流不平衡总累计时间*/
	{CLossA_Curr_Time,			GStr_ALosscurrentStr.AddTime,		GStr_ALosscurrentStr.AddTime,			C_AddTime_Length,			C_ALosscurrentEventNo		},/*A相失流总累计时间*/
	{CLossB_Curr_Time,			GStr_BLosscurrentStr.AddTime,		GStr_BLosscurrentStr.AddTime,			C_AddTime_Length,			C_BLosscurrentEventNo		},/*B相失流总累计时间*/
	{CLossC_Curr_Time,			GStr_CLosscurrentStr.AddTime,		GStr_CLosscurrentStr.AddTime,			C_AddTime_Length,			C_CLosscurrentEventNo		},/*20C相失流总累计时间*/
	{COverA_Curr_Time,			GStr_AOvercurrentStr.AddTime,		GStr_AOvercurrentStr.AddTime,			C_AddTime_Length,			C_AOvercurrentEventNo		},/*A相过流总累计时间*/
	{COverB_Curr_Time,			GStr_BOvercurrentStr.AddTime,		GStr_BOvercurrentStr.AddTime,			C_AddTime_Length,			C_BOvercurrentEventNo		},/*B相过流总累计时间*/
	{COverC_Curr_Time,			GStr_COvercurrentStr.AddTime,		GStr_COvercurrentStr.AddTime,			C_AddTime_Length,			C_COvercurrentEventNo		},/*C相过流总累计时间*/
	{CBreakA_Curr_Time,			GStr_AFailcurrentStr.AddTime,		GStr_AFailcurrentStr.AddTime,			C_AddTime_Length,			C_AFailcurrentEventNo		},/*A相断流总累计时间*/
	{CBreakB_Curr_Time,			GStr_BFailcurrentStr.AddTime,		GStr_BFailcurrentStr.AddTime,			C_AddTime_Length,			C_BFailcurrentEventNo		},/*B相断流总累计时间*/
	{CBreakC_Curr_Time,			GStr_CFailcurrentStr.AddTime,		GStr_CFailcurrentStr.AddTime,			C_AddTime_Length,			C_CFailcurrentEventNo		},/*C相断流总累计时间*/
	{CPowerT_Rev_Time,			GStr_TReversecurrentStr.AddTime,		GStr_TReversecurrentStr.AddTime,			C_AddTime_Length,			C_TReversecurrentEventNo	},/*总功率反向总累计时间*/
	{CPowerA_Rev_Time,			GStr_AReversecurrentStr.AddTime,		GStr_AReversecurrentStr.AddTime,			C_AddTime_Length,			C_AReversecurrentEventNo	},/*A相功率反向总累计时间*/
	{CPowerB_Rev_Time,			GStr_BReversecurrentStr.AddTime,		GStr_BReversecurrentStr.AddTime,			C_AddTime_Length,			C_BReversecurrentEventNo	},/*B相功率反向总累计时间*/
	{CPowerC_Rev_Time,			GStr_CReversecurrentStr.AddTime,		GStr_CReversecurrentStr.AddTime,			C_AddTime_Length,			C_CReversecurrentEventNo	},/*C相功率反向总累计时间*/
	{COverA_Lo_Time,			GStr_AOverloadStr.AddTime,			GStr_AOverloadStr.AddTime,				C_AddTime_Length,			C_AOverloadEventNo			},/*30A相过载*/
	{COverB_Lo_Time,			GStr_BOverloadStr.AddTime,			GStr_BOverloadStr.AddTime,				C_AddTime_Length,			C_BOverloadEventNo			},/*B相过载*/
	{COverC_Lo_Time,			GStr_COverloadStr.AddTime,			GStr_COverloadStr.AddTime,				C_AddTime_Length,			C_COverloadEventNo			},/*C相过载*/
	{CPFactorT_Over_Time,		GStr_OverpowerfactStr.AddTime,		GStr_OverpowerfactStr.AddTime,			C_AddTime_Length,			C_OverpowerfactEventNo		},/*总功率因数超下限*/
	{CPFactorA_Over_Time,		GStr_AOverpowerfactStr.AddTime,		GStr_AOverpowerfactStr.AddTime,			C_AddTime_Length,			C_AOverpowerfactEventNo		},/*A相功率因数超下限*/
	{CPFactorB_Over_Time,		GStr_BOverpowerfactStr.AddTime,		GStr_BOverpowerfactStr.AddTime,			C_AddTime_Length,			C_BOverpowerfactEventNo		},/*B相功率因数超下限*/
	{CPFactorC_Over_Time,		GStr_COverpowerfactStr.AddTime,		GStr_COverpowerfactStr.AddTime,			C_AddTime_Length,			C_COverpowerfactEventNo		},/*36C相功率因数超下限*/
	{CSevNoBal_Curr_Time,		GStr_SUnbanlanceCurrentStr.AddTime,	GStr_SUnbanlanceCurrentStr.Renewal,  	C_AddTime_Length,			C_SUnbanlanceCurrentEventNo	},/*37电流严重不平衡*/
	{CLoss_Vol_Degree,			0,								0,									C_AddNumber_Length,			0							},/*38 失压总次数*/
	{CLoss_Vol_Time,			0,								0,									C_AddTime_Length,			0							},/*39 失压总时间*/
	{CPos_Ac_De_Over_1,	GStr_OverForwardActiveStr.Renewal,	GStr_OverForwardActiveStr.Renewal,		C_OverDemandRenew_Length,	C_OverForwardActiveEventNo	},/*40正向有功需量超下限*/
	{CRev_Ac_De_Over_1,	GStr_OverReverseActiveStr.Renewal,	GStr_OverReverseActiveStr.Renewal,		C_OverDemandRenew_Length,	C_OverReverseActiveEventNo	},/*41反向有功需量超下限*/
	{CQua1_Re_De_Over_1,	GStr_Over1IdleDemandStr.Renewal,		GStr_Over1IdleDemandStr.Renewal,	  		C_OverDemandRenew_Length,	C_1OverIdleDemandEventNo	},/*1象限无功需量超下限*/
	{CQua2_Re_De_Over_1,	GStr_Over2IdleDemandStr.Renewal,		GStr_Over2IdleDemandStr.Renewal,	  		C_OverDemandRenew_Length,	C_2OverIdleDemandEventNo	},/*2象限无功需量超下限*/
	{CQua3_Re_De_Over_1,	GStr_Over3IdleDemandStr.Renewal,		GStr_Over3IdleDemandStr.Renewal,	  		C_OverDemandRenew_Length,	C_3OverIdleDemandEventNo	},/*3象限无功需量超下限*/
	{CQua4_Re_De_Over_1,	GStr_Over4IdleDemandStr.Renewal,		GStr_Over4IdleDemandStr.Renewal,	  		C_OverDemandRenew_Length,	C_4OverIdleDemandEventNo	},/*4象限无功需量超下限*/
	{CLossAVol_TolAh_1,			GStr_AlossvoltageStr.Renewal,		GStr_AlossvoltageStr.Renewal,			C_Ah_Length,				C_AlossvoltageEventNo		},/*上1次A相失压期间总Ah数*/
	{CLossAVol_AAh_1,			GStr_AlossvoltageStr.ARenewal,		GStr_AlossvoltageStr.Renewal,			C_Ah_Length,				C_AlossvoltageEventNo		},/*上1次A相失压期间A相Ah数*/
	{CLossAVol_BAh_1,			GStr_AlossvoltageStr.BRenewal,		GStr_AlossvoltageStr.Renewal,			C_Ah_Length,				C_AlossvoltageEventNo		},/*上1次A相失压期间B相Ah数*/
	{CLossAVol_CAh_1,			GStr_AlossvoltageStr.CRenewal,		GStr_AlossvoltageStr.Renewal,			C_Ah_Length,				C_AlossvoltageEventNo		},/*上1次A相失压期间C相Ah数*/
	{CLossBVol_TolAh_1,			GStr_BlossvoltageStr.Renewal,		GStr_BlossvoltageStr.Renewal,			C_Ah_Length,				C_BlossvoltageEventNo		},/*50上1次B相失压期间总Ah数*/
	{CLossBVol_AAh_1,			GStr_BlossvoltageStr.ARenewal,		GStr_BlossvoltageStr.Renewal,			C_Ah_Length,				C_BlossvoltageEventNo		},/*上1次B相失压期间A相Ah数*/
	{CLossBVol_BAh_1,			GStr_BlossvoltageStr.BRenewal,		GStr_BlossvoltageStr.Renewal,			C_Ah_Length,				C_BlossvoltageEventNo		},/*上1次B相失压期间B相Ah数*/
	{CLossBVol_CAh_1,			GStr_BlossvoltageStr.CRenewal,		GStr_BlossvoltageStr.Renewal,			C_Ah_Length,				C_BlossvoltageEventNo		},/*上1次B相失压期间C相Ah数*/
	{CLossCVol_TolAh_1,			GStr_ClossvoltageStr.Renewal,		GStr_ClossvoltageStr.Renewal,			C_Ah_Length,				C_ClossvoltageEventNo		},/*上1次C相失压期间总Ah数*/
	{CLossCVol_AAh_1,			GStr_ClossvoltageStr.ARenewal,		GStr_ClossvoltageStr.Renewal,			C_Ah_Length,				C_ClossvoltageEventNo		},/*上1次C相失压期间A相Ah数*/
	{CLossCVol_BAh_1,			GStr_ClossvoltageStr.BRenewal,		GStr_ClossvoltageStr.Renewal,			C_Ah_Length,				C_ClossvoltageEventNo		},/*上1次C相失压期间B相Ah数*/
	{CLossCVol_CAh_1,			GStr_ClossvoltageStr.CRenewal,		GStr_ClossvoltageStr.Renewal,			C_Ah_Length,				C_ClossvoltageEventNo		},/*上1次C相失压期间C相Ah数*/
	{CLowAVol_TolAh_1,			GStr_ALessvoltageStr.Renewal,		GStr_ALessvoltageStr.Renewal,			C_Ah_Length,				C_ALessvoltageEventNo		},/*上1次A相欠压期间总Ah数*/
	{CLowAVol_AAh_1,			GStr_ALessvoltageStr.ARenewal,		GStr_ALessvoltageStr.Renewal,			C_Ah_Length,				C_ALessvoltageEventNo		},/**/
	{CLowAVol_BAh_1,			GStr_ALessvoltageStr.BRenewal,		GStr_ALessvoltageStr.Renewal,			C_Ah_Length,				C_ALessvoltageEventNo		},/*60*/
	{CLowAVol_CAh_1,			GStr_ALessvoltageStr.CRenewal,		GStr_ALessvoltageStr.Renewal,			C_Ah_Length,				C_ALessvoltageEventNo		},/**/
	{CLowBVol_TolAh_1,			GStr_BLessvoltageStr.Renewal,		GStr_BLessvoltageStr.Renewal,			C_Ah_Length,				C_BLessvoltageEventNo		},/*上1次B相欠压期间总Ah数*/
	{CLowBVol_AAh_1,			GStr_BLessvoltageStr.ARenewal,		GStr_BLessvoltageStr.Renewal,			C_Ah_Length,				C_BLessvoltageEventNo		},/**/
	{CLowBVol_BAh_1,			GStr_BLessvoltageStr.BRenewal,		GStr_BLessvoltageStr.Renewal,			C_Ah_Length,				C_BLessvoltageEventNo		},/**/
	{CLowBVol_CAh_1,			GStr_BLessvoltageStr.CRenewal,		GStr_BLessvoltageStr.Renewal,			C_Ah_Length,				C_BLessvoltageEventNo		},/**/
	{CLowCVol_TolAh_1,			GStr_CLessvoltageStr.Renewal,		GStr_CLessvoltageStr.Renewal,			C_Ah_Length,				C_CLessvoltageEventNo		},/*上1次C相欠压期间总Ah数*/
	{CLowCVol_AAh_1,			GStr_CLessvoltageStr.ARenewal,		GStr_CLessvoltageStr.Renewal,			C_Ah_Length,				C_CLessvoltageEventNo		},/**/
	{CLowCVol_BAh_1,			GStr_CLessvoltageStr.BRenewal,		GStr_CLessvoltageStr.Renewal,			C_Ah_Length,				C_CLessvoltageEventNo		},/**/
	{CLowCVol_CAh_1,			GStr_CLessvoltageStr.CRenewal,		GStr_CLessvoltageStr.Renewal,			C_Ah_Length,				C_CLessvoltageEventNo		},/**/
	{COverAVol_TolAh_1,			GStr_AOvervoltageStr.Renewal,		GStr_AOvervoltageStr.Renewal,			C_Ah_Length,				C_AOvervoltageEventNo		},/*70上1次A相过压期间总Ah数*/
	{COverAVol_AAh_1,			GStr_AOvervoltageStr.ARenewal,		GStr_AOvervoltageStr.Renewal,			C_Ah_Length,				C_AOvervoltageEventNo		},/**/
	{COverAVol_BAh_1,			GStr_AOvervoltageStr.BRenewal,		GStr_AOvervoltageStr.Renewal,			C_Ah_Length,				C_AOvervoltageEventNo		},/**/
	{COverAVol_CAh_1,			GStr_AOvervoltageStr.CRenewal,		GStr_AOvervoltageStr.Renewal,			C_Ah_Length,				C_AOvervoltageEventNo		},/**/
	{COverBVol_TolAh_1,			GStr_BOvervoltageStr.Renewal,		GStr_BOvervoltageStr.Renewal,			C_Ah_Length,				C_BOvervoltageEventNo		},/*上1次B相过压期间总Ah数*/
	{COverBVol_AAh_1,			GStr_BOvervoltageStr.ARenewal,		GStr_BOvervoltageStr.Renewal,			C_Ah_Length,				C_BOvervoltageEventNo		},/**/
	{COverBVol_BAh_1,			GStr_BOvervoltageStr.BRenewal,		GStr_BOvervoltageStr.Renewal,			C_Ah_Length,				C_BOvervoltageEventNo		},/**/
	{COverBVol_CAh_1,			GStr_BOvervoltageStr.CRenewal,		GStr_BOvervoltageStr.Renewal,			C_Ah_Length,				C_BOvervoltageEventNo		},/**/
	{COverCVol_TolAh_1,			GStr_COvervoltageStr.Renewal,		GStr_COvervoltageStr.Renewal,			C_Ah_Length,				C_COvervoltageEventNo		},/*上1次C相过压期间总Ah数*/
	{COverCVol_AAh_1,			GStr_COvervoltageStr.ARenewal,		GStr_COvervoltageStr.Renewal,			C_Ah_Length,				C_COvervoltageEventNo		},/**/
	{COverCVol_BAh_1,			GStr_COvervoltageStr.BRenewal,		GStr_COvervoltageStr.Renewal,			C_Ah_Length,				C_COvervoltageEventNo		},/*80*/
	{COverCVol_CAh_1,			GStr_COvervoltageStr.CRenewal,		GStr_COvervoltageStr.Renewal,			C_Ah_Length,				C_COvervoltageEventNo		},/**/
	{CBreakAVol_TolAh_1,		GStr_ALossphaseStr.Renewal,			GStr_ALossphaseStr.Renewal,				C_Ah_Length,				C_ALossphaseEventNo			},/*上1次A相断相期间总Ah数*/
	{CBreakAVol_AAh_1,			GStr_ALossphaseStr.ARenewal,			GStr_ALossphaseStr.Renewal,				C_Ah_Length,				C_ALossphaseEventNo			},/**/
	{CBreakAVol_BAh_1,			GStr_ALossphaseStr.BRenewal,			GStr_ALossphaseStr.Renewal,				C_Ah_Length,				C_ALossphaseEventNo			},/**/
	{CBreakAVol_CAh_1,			GStr_ALossphaseStr.CRenewal,			GStr_ALossphaseStr.Renewal,				C_Ah_Length,				C_ALossphaseEventNo			},/**/
	{CBreakBVol_TolAh_1,		GStr_BLossphaseStr.Renewal,			GStr_BLossphaseStr.Renewal,				C_Ah_Length,				C_BLossphaseEventNo			},/*上1次B相断相期间总Ah数*/
	{CBreakBVol_AAh_1,			GStr_BLossphaseStr.ARenewal,			GStr_BLossphaseStr.Renewal,				C_Ah_Length,				C_BLossphaseEventNo			},/**/
	{CBreakBVol_BAh_1,			GStr_BLossphaseStr.BRenewal,			GStr_BLossphaseStr.Renewal,				C_Ah_Length,				C_BLossphaseEventNo			},/**/
	{CBreakBVol_CAh_1,			GStr_BLossphaseStr.CRenewal,			GStr_BLossphaseStr.Renewal,				C_Ah_Length,				C_BLossphaseEventNo			},/**/
	{CBreakCVol_TolAh_1,		GStr_CLossphaseStr.Renewal,			GStr_CLossphaseStr.Renewal,				C_Ah_Length,				C_CLossphaseEventNo			},/*90上1次C相断相期间总Ah数*/
	{CBreakCVol_AAh_1,			GStr_CLossphaseStr.ARenewal,			GStr_CLossphaseStr.Renewal,				C_Ah_Length,				C_CLossphaseEventNo			},/**/
	{CBreakCVol_BAh_1,			GStr_CLossphaseStr.BRenewal,			GStr_CLossphaseStr.Renewal,				C_Ah_Length,				C_CLossphaseEventNo			},/**/
	{CBreakCVol_CAh_1,			GStr_CLossphaseStr.CRenewal,			GStr_CLossphaseStr.Renewal,				C_Ah_Length,				C_CLossphaseEventNo			},/**/
	{CNoBalRate_Vol_End_1,		GStr_UnbanlanceVoltageStr.Renewal,	GStr_UnbanlanceVoltageStr.Renewal,		C_Unbalance_Length,			C_UnbanlanceVoltageEventNo	},/*94上1次电压不平衡事件发生期间最大不平衡率*/
	{CNoBalRate_Curr_1,			GStr_UnbanlanceCurrentStr.Renewal,	GStr_UnbanlanceCurrentStr.Renewal,		C_Unbalance_Length,			C_UnbanlanceCurrentEventNo	},/*上1次电流不平衡事件发生期间最大不平衡率*/
	{CSevNoBalRate_Curr_1,		GStr_SUnbanlanceCurrentStr.Renewal,	GStr_SUnbanlanceCurrentStr.Renewal,		C_Unbalance_Length,			C_SUnbanlanceCurrentEventNo	},/*上1次电流严重不平衡事件发生期间最大不平衡率*/
    {CLoss_Vol_Hp,              0,                              0,	                                C_EventTimeLength,          0                           },/*上1次失压发生时刻*/
    {CLoss_Vol_End,             0,                              0,	                                C_EventTimeLength,          0                           }, /*上1次失压结束时刻*/
	{CPow_Down_Time,			GStr_PowerfailStr.AddTime,			&GStr_PowerfailStr.MeterState,			C_AddTime_Length,			C_PowerfailEventNo			},/*掉电累计时间*/
	{COpenW_Time,				GStr_OpenMeterCoverStr.AddTime,		&GStr_OpenMeterCoverStr.OpenCoverState,		C_AddTime_Length,			C_OpenMeterCoverEventNo			},/*开表盖累计时间*/
	{COpenCW_Time,				GStr_OpenTerminalCoverStr.AddTime,		&GStr_OpenTerminalCoverStr.OpenCoverState,		C_AddTime_Length,		C_OpenTerminalCoverEventNo		},/*开端钮盖计时间*/
	{CConM_Time,				GStr_ConMStr.AddTime,			GStr_ConMStr.AddTime,				C_AddTime_Length,			C_MagneticCheckEventNo			},/*恒定磁场干扰累计时间*/
	{CPowerFa_Time,				GStr_PowerabnormalStr.AddTime,		&GStr_PowerabnormalStr.MeterState,			C_AddTime_Length,			C_PowerAbnormalEventNo			},/*电源异常计时间*/
	{CPos_Ac_De_Over_Time,			GStr_OverForwardActiveStr.AddTime,		&GStr_OverForwardActiveStr.MeterState,		C_AddTime_Length,			C_OverForwardActiveEventNo		},/*正向有功需量超限累计时间*/
	{CRev_Ac_De_Over_Time,			GStr_OverReverseActiveStr.AddTime,		&GStr_OverReverseActiveStr.MeterState,		C_AddTime_Length,			C_OverReverseActiveEventNo		},/*反向有功需量超限累计时间*/
	{CQua1_Re_De_Over_Time,			GStr_Over1IdleDemandStr.AddTime,		&GStr_Over1IdleDemandStr.MeterState,			C_AddTime_Length,			C_1OverIdleDemandEventNo		},/*1象限无功需量超限累计时间*/
	{CQua2_Re_De_Over_Time,			GStr_Over2IdleDemandStr.AddTime,		&GStr_Over2IdleDemandStr.MeterState,			C_AddTime_Length,			C_2OverIdleDemandEventNo		},/*2象限无功需量超限累计时间*/
	{CQua3_Re_De_Over_Time,			GStr_Over3IdleDemandStr.AddTime,		&GStr_Over3IdleDemandStr.MeterState,			C_AddTime_Length,			C_3OverIdleDemandEventNo		},/*3象限无功需量超限累计时间*/
	{CQua4_Re_De_Over_Time,			GStr_Over4IdleDemandStr.AddTime,		&GStr_Over4IdleDemandStr.MeterState,			C_AddTime_Length,			C_4OverIdleDemandEventNo		},/*4象限无功需量超限累计时间*/
	{CMeterFa_Time,				GStr_MeterFaStr.AddTime,			GStr_MeterFaStr.AddTime,				C_AddTime_Length,			C_MeterFaEventNo			},/*计量芯片故障累计时间*/
	{CClockFa_Time,				GStr_ClockFaStr.AddTime,			GStr_ClockFaStr.AddTime,				C_AddTime_Length,			C_ClockFaEventNo			},/*时钟故障累计时间*/
	{CNeutralCurrentAbnormal_Time,GStr_NeutralAbnormalStr.AddTime,GStr_NeutralAbnormalStr.AddTime,C_AddTime_Length,C_NeutralCurrentAbnormalEventNo},/*零线电流异常累计时间*/
#if 0
	{CBroadcastTime_Time,GStr_BroadcastTimeStr.AddTime,GStr_BroadcastTimeStr.AddTime,C_AddTime_Length,C_BroadcastTimeEventNo},/*广播校时累计时间*/
#endif
};
#define C_EventNum_AddTime38    38  /*上表格CommunicateReadTable前38个*/
#define C_EventNum_AddTime100   100  /*上表格CommunicateReadTable第100个*/
#define C_EventNum_AddTime110   110  /*上表格CommunicateReadTable第110个*/
#define C_EventNum_AddTime113   113  /*上表格CommunicateReadTable第113个*/
#define CLoss_Vol_Degree_offset 39   /*失压次数在上表格CommunicateReadTable第39个*/
#define CLoss_Vol_Time_offset   40   /*失压时间在上表格CommunicateReadTable第40个*/

/*****************************************************************************************/
/*表格的顺序不能随意调整！！*/
/*****************************************************************************************/
const Str_AhCountTable_Type Str_RAMAhTable1[12]=	/*Ah数地址*/
{/*总Ah数RAM中地址			A相Ah数RAM地址				B相Ah数RAM地址				C相Ah数RAM地址*/
	{GStr_AlossvoltageStr.Renewal,	GStr_AlossvoltageStr.ARenewal,	GStr_AlossvoltageStr.BRenewal,	GStr_AlossvoltageStr.CRenewal},
	{GStr_BlossvoltageStr.Renewal,	GStr_BlossvoltageStr.ARenewal,	GStr_BlossvoltageStr.BRenewal,	GStr_BlossvoltageStr.CRenewal},
	{GStr_ClossvoltageStr.Renewal,	GStr_ClossvoltageStr.ARenewal,	GStr_ClossvoltageStr.BRenewal,	GStr_ClossvoltageStr.CRenewal},
	{GStr_ALessvoltageStr.Renewal,	GStr_ALessvoltageStr.ARenewal,	GStr_ALessvoltageStr.BRenewal,	GStr_ALessvoltageStr.CRenewal},
	{GStr_BLessvoltageStr.Renewal,	GStr_BLessvoltageStr.ARenewal,	GStr_BLessvoltageStr.BRenewal,	GStr_BLessvoltageStr.CRenewal},
	{GStr_CLessvoltageStr.Renewal,	GStr_CLessvoltageStr.ARenewal,	GStr_CLessvoltageStr.BRenewal,	GStr_CLessvoltageStr.CRenewal},
	{GStr_AOvervoltageStr.Renewal,	GStr_AOvervoltageStr.ARenewal,	GStr_AOvervoltageStr.BRenewal,	GStr_AOvervoltageStr.CRenewal},
	{GStr_BOvervoltageStr.Renewal,	GStr_BOvervoltageStr.ARenewal,	GStr_BOvervoltageStr.BRenewal,	GStr_BOvervoltageStr.CRenewal},
	{GStr_COvervoltageStr.Renewal,	GStr_COvervoltageStr.ARenewal,	GStr_COvervoltageStr.BRenewal,	GStr_COvervoltageStr.CRenewal},
	{GStr_ALossphaseStr.Renewal,		GStr_ALossphaseStr.ARenewal,		GStr_ALossphaseStr.BRenewal,		GStr_ALossphaseStr.CRenewal  },
	{GStr_BLossphaseStr.Renewal,		GStr_BLossphaseStr.ARenewal,		GStr_BLossphaseStr.BRenewal,		GStr_BLossphaseStr.CRenewal	},
	{GStr_CLossphaseStr.Renewal,		GStr_CLossphaseStr.ARenewal,		GStr_CLossphaseStr.BRenewal,		GStr_CLossphaseStr.CRenewal	},
};
/*****************************************************************************************/
/*表格的顺序不能随意调整！！*/
/*****************************************************************************************/
const Str_AhCountTable_Type Str_RAMAhTable2[12]=								/*不足0.01Ah地址*/
{/*总不足0.0Ah数RAM中地址	A相不足0.01Ah数RAM地址	B相不足0.01Ah数RAM地址	C相不足0.01Ah数RAM地址*/
	{GStr_AlossvoltageStr.Ah,	GStr_AlossvoltageStr.AAh,	GStr_AlossvoltageStr.BAh,	GStr_AlossvoltageStr.CAh	},
	{GStr_BlossvoltageStr.Ah,	GStr_BlossvoltageStr.AAh,	GStr_BlossvoltageStr.BAh,	GStr_BlossvoltageStr.CAh	},
	{GStr_ClossvoltageStr.Ah,	GStr_ClossvoltageStr.AAh,	GStr_ClossvoltageStr.BAh,	GStr_ClossvoltageStr.CAh	},
	{GStr_ALessvoltageStr.Ah,	GStr_ALessvoltageStr.AAh,	GStr_ALessvoltageStr.BAh,	GStr_ALessvoltageStr.CAh	},
	{GStr_BLessvoltageStr.Ah,	GStr_BLessvoltageStr.AAh,	GStr_BLessvoltageStr.BAh,	GStr_BLessvoltageStr.CAh	},
	{GStr_CLessvoltageStr.Ah,	GStr_CLessvoltageStr.AAh,	GStr_CLessvoltageStr.BAh,	GStr_CLessvoltageStr.CAh	},
	{GStr_AOvervoltageStr.Ah,	GStr_AOvervoltageStr.AAh,	GStr_AOvervoltageStr.BAh,	GStr_AOvervoltageStr.CAh	},
	{GStr_BOvervoltageStr.Ah,	GStr_BOvervoltageStr.AAh,	GStr_BOvervoltageStr.BAh,	GStr_BOvervoltageStr.CAh	},
	{GStr_COvervoltageStr.Ah,	GStr_COvervoltageStr.AAh,	GStr_COvervoltageStr.BAh,	GStr_COvervoltageStr.CAh	},
	{GStr_ALossphaseStr.Ah,		GStr_ALossphaseStr.AAh,		GStr_ALossphaseStr.BAh,		GStr_ALossphaseStr.CAh	},
	{GStr_BLossphaseStr.Ah,		GStr_BLossphaseStr.AAh,		GStr_BLossphaseStr.BAh,		GStr_BLossphaseStr.CAh	},
	{GStr_CLossphaseStr.Ah,		GStr_CLossphaseStr.AAh,		GStr_CLossphaseStr.BAh,		GStr_CLossphaseStr.CAh 	},
};
/*****************************************************************************************/
/*表格的顺序不能随意调整！！*/
/*****************************************************************************************/
/*清零表格1*/
const Str_CommunicateEventClearTable_Type CommunicateEventClearTable[C_EventNoLength]=
{
	/*RAM地址									CRC地址							长度							   		状态字地址			   偏移量(发生时) 偏移量（结束）小铃铛						报警输出					背光					报警发生时		报警结束时*/
	{&GStr_TotalvoltageloseStr.MeterState,		GStr_TotalvoltageloseStr.V_CRC,		sizeof(Str_LpowerTvoltagelose_Type),	0,						0,				0,			&GStr_BellAlarm.T1_Flag,	&GStr_Alarmoutput.T1_Flag,	&GStr_BackLightAlarm.T1_Flag,	C_Bit4_Start,	C_Bit4_End	},/*全失压*/
	{&GStr_ACPowerFailStr.MeterState,			GStr_ACPowerFailStr.V_CRC,			sizeof(Str_ACPowerFail_Type),			CMeter_Work_State7,		C_Bit4_Start,	C_Bit4_End,	0,						0,							0,								0,				0			},/*辅助电源失电*/
	{&GStr_PowerfailStr.MeterState,				GStr_PowerfailStr.V_CRC,				sizeof(Str_LpowerTvoltagelose_Type),	CMeter_Work_State7,		C_Bit5_Start,	C_Bit5_End,	0,						0,							0,								0,				0			},/*掉电*/
	{&GStr_OpenMeterCoverStr.OpenCoverState,		GStr_OpenMeterCoverStr.V_CRC,		sizeof(Str_CoverRecord_Type),			CMeter_Work_State7,		C_Bit1_Start,	C_Bit1_End,	&GStr_BellAlarm.T1_Flag,	&GStr_Alarmoutput.T1_Flag,	&GStr_BackLightAlarm.T1_Flag,	C_Bit1_Start,	C_Bit1_End	},/*开表盖*/
	{&GStr_OpenTerminalCoverStr.OpenCoverState,	GStr_OpenTerminalCoverStr.V_CRC,  	sizeof(Str_CoverRecord_Type),			CMeter_Work_State7,		C_Bit2_Start,	C_Bit2_End,	&GStr_BellAlarm.T1_Flag,	&GStr_Alarmoutput.T1_Flag,	&GStr_BackLightAlarm.T1_Flag,	C_Bit2_Start,	C_Bit2_End	},/*开端钮盖*/
	{GStr_ConMStr.AddTime,						GStr_ConMStr.V_CRC,					sizeof(Str_OtherMeter_Type),			0,						0,				0,			0,						0,							0,								0,				0			},/*恒定磁场干扰*/
	{&GStr_PowerabnormalStr.MeterState,			GStr_PowerabnormalStr.V_CRC,			sizeof(Str_ACPowerFail_Type),			0,						0,				0,			0,						0,							0,								0,				0			},/*电源异常*/
	{GStr_OverForwardActiveStr.Renewal,			GStr_OverForwardActiveStr.V_CRC,		sizeof(Str_ActiveDemand_Type),			CMeter_Work_State7,		C_Bit6_Start,	C_Bit6_End,	&GStr_BellAlarm.T1_Flag,	&GStr_Alarmoutput.T1_Flag,	&GStr_BackLightAlarm.T1_Flag,	C_Bit0_Start,	C_Bit0_End	},/*正向有功需量超限*/
	{GStr_OverReverseActiveStr.Renewal,			GStr_OverReverseActiveStr.V_CRC,		sizeof(Str_ActiveDemand_Type),			CMeter_Work_State7,		C_Bit6_Start,	C_Bit6_End,	&GStr_BellAlarm.T1_Flag,	&GStr_Alarmoutput.T1_Flag,	&GStr_BackLightAlarm.T1_Flag,	C_Bit0_Start,	C_Bit0_End	},/*反向有功需量超限*/
	{GStr_Over1IdleDemandStr.Renewal,			GStr_Over1IdleDemandStr.V_CRC,		sizeof(Str_ActiveDemand_Type),			CMeter_Work_State7,		C_Bit6_Start,	C_Bit6_End,	0,						0,							0,								0,				0			},/*1象限无功需量超限*/
	{GStr_Over2IdleDemandStr.Renewal,			GStr_Over2IdleDemandStr.V_CRC,		sizeof(Str_ActiveDemand_Type),			CMeter_Work_State7,		C_Bit6_Start,	C_Bit6_End,	0,						0,							0,								0,				0			},/*2象限无功需量超限*/
	{GStr_Over3IdleDemandStr.Renewal,			GStr_Over3IdleDemandStr.V_CRC,		sizeof(Str_ActiveDemand_Type),			CMeter_Work_State7,		C_Bit6_Start,	C_Bit6_End,	0,						0,							0,								0,				0			},/*3象限无功需量超限*/
	{GStr_Over4IdleDemandStr.Renewal,			GStr_Over4IdleDemandStr.V_CRC,		sizeof(Str_ActiveDemand_Type),			CMeter_Work_State7,		C_Bit6_Start,	C_Bit6_End,	0,						0,							0,								0,				0			},/*4象限无功需量超限*/
	{GStr_AlossvoltageStr.Renewal,				GStr_AlossvoltageStr.V_CRC,			sizeof(Str_AhMeter_Type),				CMeter_Work_State4,		C_Bit0_Start,	C_Bit0_End,	&GStr_BellAlarm.A0_Flag,	&GStr_Alarmoutput.A0_Flag,	&GStr_BackLightAlarm.A0_Flag,	C_Bit0_Start,	C_Bit0_End	},/*A相失压*/
	{GStr_BlossvoltageStr.Renewal,				GStr_BlossvoltageStr.V_CRC,			sizeof(Str_AhMeter_Type),				CMeter_Work_State5,		C_Bit0_Start,	C_Bit0_End,	&GStr_BellAlarm.B0_Flag,	&GStr_Alarmoutput.B0_Flag,	&GStr_BackLightAlarm.B0_Flag,	C_Bit0_Start,	C_Bit0_End	},/*B相失压*/
	{GStr_ClossvoltageStr.Renewal,				GStr_ClossvoltageStr.V_CRC,			sizeof(Str_AhMeter_Type),				CMeter_Work_State6,		C_Bit0_Start,	C_Bit0_End,	&GStr_BellAlarm.C0_Flag,	&GStr_Alarmoutput.C0_Flag,	&GStr_BackLightAlarm.C0_Flag,	C_Bit0_Start,	C_Bit0_End	},/*C相失压*/
	{GStr_ALessvoltageStr.Renewal,				GStr_ALessvoltageStr.V_CRC,			sizeof(Str_AhMeter_Type),				CMeter_Work_State4,		C_Bit1_Start,	C_Bit1_End,	&GStr_BellAlarm.A0_Flag,	&GStr_Alarmoutput.A0_Flag,	&GStr_BackLightAlarm.A0_Flag,	C_Bit7_Start,	C_Bit7_End	},/*A相欠压*/
	{GStr_BLessvoltageStr.Renewal,				GStr_BLessvoltageStr.V_CRC,			sizeof(Str_AhMeter_Type),				CMeter_Work_State5,		C_Bit1_Start,	C_Bit1_End,	&GStr_BellAlarm.B0_Flag,	&GStr_Alarmoutput.B0_Flag,	&GStr_BackLightAlarm.B0_Flag,	C_Bit7_Start,	C_Bit7_End	},/*B相欠压*/
	{GStr_CLessvoltageStr.Renewal,				GStr_CLessvoltageStr.V_CRC,			sizeof(Str_AhMeter_Type),				CMeter_Work_State6,		C_Bit1_Start,	C_Bit1_End,	&GStr_BellAlarm.C0_Flag,	&GStr_Alarmoutput.C0_Flag,	&GStr_BackLightAlarm.C0_Flag,	C_Bit7_Start,	C_Bit7_End	},/*C相欠压*/
	{GStr_AOvervoltageStr.Renewal,				GStr_AOvervoltageStr.V_CRC,			sizeof(Str_AhMeter_Type),				CMeter_Work_State4,		C_Bit2_Start,	C_Bit2_End,	&GStr_BellAlarm.A0_Flag,	&GStr_Alarmoutput.A0_Flag,	&GStr_BackLightAlarm.A0_Flag,	C_Bit6_Start,	C_Bit6_End	},/*A相过压*/
	{GStr_BOvervoltageStr.Renewal,				GStr_BOvervoltageStr.V_CRC,			sizeof(Str_AhMeter_Type),				CMeter_Work_State5,		C_Bit2_Start,	C_Bit2_End,	&GStr_BellAlarm.B0_Flag,	&GStr_Alarmoutput.B0_Flag,	&GStr_BackLightAlarm.B0_Flag,	C_Bit6_Start,	C_Bit6_End	},/*B相过压*/
	{GStr_COvervoltageStr.Renewal,				GStr_COvervoltageStr.V_CRC,			sizeof(Str_AhMeter_Type),				CMeter_Work_State6,		C_Bit2_Start,	C_Bit2_End,	&GStr_BellAlarm.C0_Flag,	&GStr_Alarmoutput.C0_Flag,	&GStr_BackLightAlarm.C0_Flag,	C_Bit6_Start,	C_Bit6_End	},/*C相过压*/
	{GStr_ALossphaseStr.Renewal,					GStr_ALossphaseStr.V_CRC,			sizeof(Str_AhMeter_Type),				CMeter_Work_State4,		C_Bit7_Start,	C_Bit7_End,	&GStr_BellAlarm.A0_Flag,	&GStr_Alarmoutput.A0_Flag,	&GStr_BackLightAlarm.A0_Flag,	C_Bit4_Start,	C_Bit4_End	},/*A相断相*/
	{GStr_BLossphaseStr.Renewal,					GStr_BLossphaseStr.V_CRC,			sizeof(Str_AhMeter_Type),				CMeter_Work_State5,		C_Bit7_Start,	C_Bit7_End,	&GStr_BellAlarm.B0_Flag,	&GStr_Alarmoutput.B0_Flag,	&GStr_BackLightAlarm.B0_Flag,	C_Bit4_Start,	C_Bit4_End	},/*B相断相*/
	{GStr_CLossphaseStr.Renewal,					GStr_CLossphaseStr.V_CRC,			sizeof(Str_AhMeter_Type),				CMeter_Work_State6,		C_Bit7_Start,	C_Bit7_End,	&GStr_BellAlarm.C0_Flag,	&GStr_Alarmoutput.C0_Flag,	&GStr_BackLightAlarm.C0_Flag,	C_Bit4_Start,	C_Bit4_End	},/*C相断相*/
	{GStr_ReversephaseVoltageStr.AddTime,		GStr_ReversephaseVoltageStr.V_CRC,	sizeof(Str_OtherMeter_Type),			CMeter_Work_State7,		C_Bit0_Start,	C_Bit0_End,	&GStr_BellAlarm.T0_Flag,	&GStr_Alarmoutput.T0_Flag,	&GStr_BackLightAlarm.T0_Flag,	C_Bit0_Start,	C_Bit0_End	},/*电压逆相序*/
	{GStr_ReversephaseCurrentStr.AddTime,		GStr_ReversephaseCurrentStr.V_CRC,	sizeof(Str_OtherMeter_Type),			CMeter_Work_State7,		C_Bit1_Start,	C_Bit1_End,	&GStr_BellAlarm.T0_Flag,	&GStr_Alarmoutput.T0_Flag,	&GStr_BackLightAlarm.T0_Flag,	C_Bit1_Start,	C_Bit1_End	},/*电流逆相序*/
	{GStr_UnbanlanceVoltageStr.Renewal,			GStr_UnbanlanceVoltageStr.V_CRC,		sizeof(Str_Unbanlance_Type),			CMeter_Work_State7,		C_Bit2_Start,	C_Bit2_End,	&GStr_BellAlarm.T0_Flag,	&GStr_Alarmoutput.T0_Flag,	&GStr_BackLightAlarm.T0_Flag,	C_Bit5_Start,	C_Bit5_End	},/*电压不平衡*/
	{GStr_UnbanlanceCurrentStr.Renewal,			GStr_UnbanlanceCurrentStr.V_CRC,		sizeof(Str_Unbanlance_Type),			CMeter_Work_State7,		C_Bit3_Start,	C_Bit3_End,	&GStr_BellAlarm.T0_Flag,	&GStr_Alarmoutput.T0_Flag,	&GStr_BackLightAlarm.T0_Flag,	C_Bit6_Start,	C_Bit6_End	},/*电流不平衡*/
	{GStr_ALosscurrentStr.AddTime,				GStr_ALosscurrentStr.V_CRC,			sizeof(Str_OtherMeter_Type),			CMeter_Work_State4,		C_Bit3_Start,	C_Bit3_End,	&GStr_BellAlarm.A0_Flag,	&GStr_Alarmoutput.A0_Flag,	&GStr_BackLightAlarm.A0_Flag,	C_Bit3_Start,	C_Bit3_End	},/*A相失流*/
	{GStr_BLosscurrentStr.AddTime,				GStr_BLosscurrentStr.V_CRC,			sizeof(Str_OtherMeter_Type),			CMeter_Work_State5,		C_Bit3_Start,	C_Bit3_End,	&GStr_BellAlarm.B0_Flag,	&GStr_Alarmoutput.B0_Flag,	&GStr_BackLightAlarm.B0_Flag,	C_Bit3_Start,	C_Bit3_End	},/*B相失流*/
	{GStr_CLosscurrentStr.AddTime,				GStr_CLosscurrentStr.V_CRC,			sizeof(Str_OtherMeter_Type),			CMeter_Work_State6,		C_Bit3_Start,	C_Bit3_End,	&GStr_BellAlarm.C0_Flag,	&GStr_Alarmoutput.C0_Flag,	&GStr_BackLightAlarm.C0_Flag,	C_Bit3_Start,	C_Bit3_End	},/*C相失流*/
	{GStr_AOvercurrentStr.AddTime,				GStr_AOvercurrentStr.V_CRC,			sizeof(Str_OtherMeter_Type),			CMeter_Work_State4,		C_Bit4_Start,	C_Bit4_End,	&GStr_BellAlarm.A0_Flag,	&GStr_Alarmoutput.A0_Flag,	&GStr_BackLightAlarm.A0_Flag,	C_Bit5_Start,	C_Bit5_End	},/*A相过流*/
	{GStr_BOvercurrentStr.AddTime,				GStr_BOvercurrentStr.V_CRC,			sizeof(Str_OtherMeter_Type),			CMeter_Work_State5,		C_Bit4_Start,	C_Bit4_End,	&GStr_BellAlarm.B0_Flag,	&GStr_Alarmoutput.B0_Flag,	&GStr_BackLightAlarm.B0_Flag,	C_Bit5_Start,	C_Bit5_End	},/*B相过流*/
	{GStr_COvercurrentStr.AddTime,				GStr_COvercurrentStr.V_CRC,			sizeof(Str_OtherMeter_Type),			CMeter_Work_State6,		C_Bit4_Start,	C_Bit4_End,	&GStr_BellAlarm.C0_Flag,	&GStr_Alarmoutput.C0_Flag,	&GStr_BackLightAlarm.C0_Flag,	C_Bit5_Start,	C_Bit5_End	},/*C相过流*/
	{GStr_AFailcurrentStr.AddTime,				GStr_AFailcurrentStr.V_CRC,			sizeof(Str_OtherMeter_Type),			CMeter_Work_State4,		C_Bit0_Start,	C_Bit0_End,	&GStr_BellAlarm.A1_Flag,	&GStr_Alarmoutput.A1_Flag,	&GStr_BackLightAlarm.A1_Flag,	C_Bit0_Start,	C_Bit0_End	},/*A相断流*/
	{GStr_BFailcurrentStr.AddTime,				GStr_BFailcurrentStr.V_CRC,			sizeof(Str_OtherMeter_Type),			CMeter_Work_State5,		C_Bit0_Start,	C_Bit0_End,	&GStr_BellAlarm.B1_Flag,	&GStr_Alarmoutput.B1_Flag,	&GStr_BackLightAlarm.B1_Flag,	C_Bit0_Start,	C_Bit0_End	},/*B相断流*/
	{GStr_CFailcurrentStr.AddTime,				GStr_CFailcurrentStr.V_CRC,			sizeof(Str_OtherMeter_Type),			CMeter_Work_State6,		C_Bit0_Start,	C_Bit0_End,	&GStr_BellAlarm.C1_Flag,	&GStr_Alarmoutput.C1_Flag,	&GStr_BackLightAlarm.C1_Flag,	C_Bit0_Start,	C_Bit0_End	},/*C相断流*/
	{GStr_TReversecurrentStr.AddTime,			GStr_TReversecurrentStr.V_CRC,		sizeof(Str_OtherMeter_Type),			0,						0,				0,			0,						0,							0,								0,				0			},/*总功率反向*/
	{GStr_AReversecurrentStr.AddTime,			GStr_AReversecurrentStr.V_CRC,		sizeof(Str_OtherMeter_Type),			CMeter_Work_State4,		C_Bit6_Start,	C_Bit6_End,	&GStr_BellAlarm.A0_Flag,	&GStr_Alarmoutput.A0_Flag,	&GStr_BackLightAlarm.A0_Flag,	C_Bit2_Start,	C_Bit2_End	},/*A相功率反向*/
	{GStr_BReversecurrentStr.AddTime,			GStr_BReversecurrentStr.V_CRC,		sizeof(Str_OtherMeter_Type),			CMeter_Work_State5,		C_Bit6_Start,	C_Bit6_End,	&GStr_BellAlarm.B0_Flag,	&GStr_Alarmoutput.B0_Flag,	&GStr_BackLightAlarm.B0_Flag,	C_Bit2_Start,	C_Bit2_End	},/*B相功率反向*/
	{GStr_CReversecurrentStr.AddTime,			GStr_CReversecurrentStr.V_CRC,		sizeof(Str_OtherMeter_Type),			CMeter_Work_State6,		C_Bit6_Start,	C_Bit6_End,	&GStr_BellAlarm.C0_Flag,	&GStr_Alarmoutput.C0_Flag,	&GStr_BackLightAlarm.C0_Flag,	C_Bit2_Start,	C_Bit2_End	},/*C相功率反向*/
	{GStr_AOverloadStr.AddTime,					GStr_AOverloadStr.V_CRC,				sizeof(Str_OtherMeter_Type),			CMeter_Work_State4,		C_Bit5_Start,	C_Bit5_End,	&GStr_BellAlarm.A0_Flag,	&GStr_Alarmoutput.A0_Flag,	&GStr_BackLightAlarm.A0_Flag,	C_Bit1_Start,	C_Bit1_End	},/*A相过载*/
	{GStr_BOverloadStr.AddTime,					GStr_BOverloadStr.V_CRC,				sizeof(Str_OtherMeter_Type),			CMeter_Work_State5,		C_Bit5_Start,	C_Bit5_End,	&GStr_BellAlarm.B0_Flag,	&GStr_Alarmoutput.B0_Flag,	&GStr_BackLightAlarm.B0_Flag,	C_Bit1_Start,	C_Bit1_End	},/*B相过载*/
	{GStr_COverloadStr.AddTime,					GStr_COverloadStr.V_CRC,				sizeof(Str_OtherMeter_Type),			CMeter_Work_State6,		C_Bit5_Start,	C_Bit5_End,	&GStr_BellAlarm.C0_Flag,	&GStr_Alarmoutput.C0_Flag,	&GStr_BackLightAlarm.C0_Flag,	C_Bit1_Start,	C_Bit1_End	},/*C相过载*/
	{GStr_OverpowerfactStr.AddTime,				GStr_OverpowerfactStr.V_CRC,			sizeof(Str_OtherMeter_Type),			CMeter_Work_State7,		C_Bit7_Start,	C_Bit7_End,	&GStr_BellAlarm.T0_Flag,	&GStr_Alarmoutput.T0_Flag,	&GStr_BackLightAlarm.T0_Flag,	C_Bit4_Start,	C_Bit4_End	},/*总功率因数超下限*/
	{GStr_AOverpowerfactStr.AddTime,				GStr_AOverpowerfactStr.V_CRC,		sizeof(Str_OtherMeter_Type),			0,						0,				0,			&GStr_BellAlarm.A1_Flag,	&GStr_Alarmoutput.A1_Flag,	&GStr_BackLightAlarm.A1_Flag,	C_Bit1_Start,	C_Bit1_End	},/*A相功率因数超下限*/
	{GStr_BOverpowerfactStr.AddTime,				GStr_BOverpowerfactStr.V_CRC,		sizeof(Str_OtherMeter_Type),			0,						0,				0,			&GStr_BellAlarm.B1_Flag,	&GStr_Alarmoutput.B1_Flag,	&GStr_BackLightAlarm.B1_Flag,	C_Bit1_Start,	C_Bit1_End	},/*B相功率因数超下限*/
	{GStr_COverpowerfactStr.AddTime,				GStr_COverpowerfactStr.V_CRC,		sizeof(Str_OtherMeter_Type),			0,						0,				0,			&GStr_BellAlarm.C1_Flag,	&GStr_Alarmoutput.C1_Flag,	&GStr_BackLightAlarm.C1_Flag,	C_Bit1_Start,	C_Bit1_End	},/*C相功率因数超下限*/
	{GStr_SUnbanlanceCurrentStr.Renewal,			GStr_SUnbanlanceCurrentStr.V_CRC,	sizeof(Str_Unbanlance_Type),			CMeter_Work_State7,		C_Bit0_Start,	C_Bit0_End,	&GStr_BellAlarm.T0_Flag,	&GStr_Alarmoutput.T0_Flag,	&GStr_BackLightAlarm.T0_Flag,	C_Bit7_Start,	C_Bit7_End	},/*电流严重不平衡*/
#if 0
	{0,										0,								0,										0,						0,				0,			&GStr_BellAlarm.T0_Flag,	&GStr_Alarmoutput.T0_Flag,	&GStr_BackLightAlarm.T0_Flag,	C_Bit3_Start,	C_Bit3_End	},/*总潮流反向*/
#endif
	{GStr_MeterFaStr.AddTime,					GStr_MeterFaStr.V_CRC,				sizeof(Str_OtherMeter_Type),			CMeter_Work_State1,		C_Bit6_Start,	C_Bit6_End,	0,						0,							0,								0,				0			},/*计量芯片故障*/
	{GStr_ClockFaStr.AddTime,					GStr_ClockFaStr.V_CRC,				sizeof(Str_OtherMeter_Type),			0,						0,				0,			0,						0,							0,								0,				0			},/*时钟故障*/
	{GStr_NeutralAbnormalStr.AddTime,			GStr_NeutralAbnormalStr.V_CRC,		sizeof(Str_OtherMeter_Type),			0,						0,				0,			0,						0,							0,								0,				0			},/*零线电流异常*/
};

/*****************************************************************************************/
/*表格的顺序不能随意调整！！*/
/*****************************************************************************************/
const   uchar8  ActiveReportTable[C_EventNoLength]=
{
        C_Times_NoVoltage,
        C_Times_SubPowerOff,
        C_Times_PowerOff,
        C_Times_OpenMeterCover,
        C_Times_OpenTerminalCover,
        C_Times_MagneticCheck,
        C_Times_PowerError,
        C_Times_OverDemadn,
        C_Times_OverDemadn,
        C_NULL,
        C_NULL,
        C_NULL,
        C_NULL,
        C_Times_ALossVoltage,
        C_Times_BLossVoltage,
        C_Times_CLossVoltage,
        C_Times_ALessVoltage,
        C_Times_BLessVoltage,
        C_Times_CLessVoltage,
        C_Times_AOverVoltage,
        C_Times_BOverVoltage,
        C_Times_COverVoltage,
        C_Times_ALossPhase,
        C_Times_BLossPhase,
        C_Times_CLossPhase,
        C_Times_ReversedVoltage,
        C_Times_ReversedCurrent,
        C_Times_UnbalancedVoltage,
        C_Times_UnbalancedCurrent,
        C_Times_ALossCurrent,
        C_Times_BLossCurrent,
        C_Times_CLossCurrent,
        C_Times_AOverCurrent,
        C_Times_BOverCurrent,
        C_Times_COverCurrent,
        C_Times_ALessCurrent,
        C_Times_BLessCurrent,
        C_Times_CLessCurrent,
        C_Times_TActivePowerReversed,
        C_Times_APowerReverse,
        C_Times_BPowerReverse,
        C_Times_CPowerReverse,
        C_Times_AOverLoad,
        C_Times_BOverLoad,
        C_Times_COverLoad,
        C_Times_OverPowerFact,
        C_NULL,
        C_NULL,
        C_NULL,
        C_Times_SeriousUnbalancedCurrent,
        C_NULL,
        C_Times_RTCErr,
};


/*****************************************************************************************/
/*表格的顺序不能随意调整！！*/
/*****************************************************************************************/
/***********事件对应表格**************/
const Str_EventMapping_Type EventMappingTable[]=
{
	{C_AlossvoltageEventNo,		C_SourceNon,	CLossA_Vol_Degree,	CLoss_Vol_OADTab,	CLossAVol_FF_1},
	{C_BlossvoltageEventNo,		C_SourceNon,	CLossB_Vol_Degree,	CLoss_Vol_OADTab,	CLossBVol_FF_1},
	{C_ClossvoltageEventNo,		C_SourceNon,	CLossC_Vol_Degree,	CLoss_Vol_OADTab,	CLossCVol_FF_1},
	{C_ALessvoltageEventNo,		C_SourceNon,	CLowA_Vol_Degree,	CLow_Vol_OADTab,	CLowAVol_FF_1},
	{C_BLessvoltageEventNo,		C_SourceNon,	CLowB_Vol_Degree,	CLow_Vol_OADTab,	CLowBVol_FF_1},
	{C_CLessvoltageEventNo,		C_SourceNon,	CLowC_Vol_Degree,	CLow_Vol_OADTab,	CLowCVol_FF_1},
	{C_AOvervoltageEventNo,		C_SourceNon,	COverA_Vol_Degree,	COver_Vol_OADTab,	COverAVol_FF_1},
	{C_BOvervoltageEventNo,		C_SourceNon,	COverB_Vol_Degree,	COver_Vol_OADTab,	COverBVol_FF_1},
	{C_COvervoltageEventNo,		C_SourceNon,	COverC_Vol_Degree,	COver_Vol_OADTab,	COverCVol_FF_1},
	{C_ALossphaseEventNo,		C_SourceNon,	CBreakA_Vol_Degree,	CBreak_Vol_OADTab,	CBreakAVol_FF_1},
	{C_BLossphaseEventNo,		C_SourceNon,	CBreakB_Vol_Degree,	CBreak_Vol_OADTab,	CBreakBVol_FF_1},
	{C_CLossphaseEventNo,		C_SourceNon,	CBreakC_Vol_Degree,	CBreak_Vol_OADTab,	CBreakCVol_FF_1},
	{C_ALosscurrentEventNo,		C_SourceNon,	CLossA_Curr_Degree,	CLoss_Curr_OADTab,	CLossACurr_FF_1},
	{C_BLosscurrentEventNo,		C_SourceNon,	CLossB_Curr_Degree,	CLoss_Curr_OADTab,	CLossBCurr_FF_1},
	{C_CLosscurrentEventNo,		C_SourceNon,	CLossC_Curr_Degree,	CLoss_Curr_OADTab,	CLossCCurr_FF_1},
	{C_AOvercurrentEventNo,		C_SourceNon,	COverA_Curr_Degree,	COver_Curr_OADTab,	COverACurr_FF_1},
	{C_BOvercurrentEventNo,		C_SourceNon,	COverB_Curr_Degree,	COver_Curr_OADTab,	COverBCurr_FF_1},
	{C_COvercurrentEventNo,		C_SourceNon,	COverC_Curr_Degree,	COver_Curr_OADTab,	COverCCurr_FF_1},
	{C_AFailcurrentEventNo,		C_SourceNon,	CBreakA_Curr_Degree,	CBreak_Curr_OADTab,	CBreakACurr_FF_1},
	{C_BFailcurrentEventNo,		C_SourceNon,	CBreakB_Curr_Degree,	CBreak_Curr_OADTab,	CBreakBCurr_FF_1},
	{C_CFailcurrentEventNo,		C_SourceNon,	CBreakC_Curr_Degree,	CBreak_Curr_OADTab,	CBreakCCurr_FF_1},
	{C_TReversecurrentEventNo,	C_SourceNon,	CPowerT_Rev_Degree,	CPower_Rev_OADTab,	CPowerTRev_FF_1},
	{C_AReversecurrentEventNo,	C_SourceNon,	CPowerA_Rev_Degree,	CPower_Rev_OADTab,	CPowerARev_FF_1},
	{C_BReversecurrentEventNo,	C_SourceNon,	CPowerB_Rev_Degree,	CPower_Rev_OADTab,	CPowerBRev_FF_1},
	{C_CReversecurrentEventNo,	C_SourceNon,	CPowerC_Rev_Degree,	CPower_Rev_OADTab,	CPowerCRev_FF_1},
	{C_AOverloadEventNo,		C_SourceNon,	COverA_Lo_Degree,	COver_Lo_OADTab,	COverALo_FF_1},
	{C_BOverloadEventNo,		C_SourceNon,	COverB_Lo_Degree,	COver_Lo_OADTab,	COverBLo_FF_1},
	{C_COverloadEventNo,		C_SourceNon,	COverC_Lo_Degree,	COver_Lo_OADTab,	COverCLo_FF_1},
	{C_OverForwardActiveEventNo,	C_SourceExist,	CPos_Ac_De_Over_Degree,	CPos_Ac_De_Over_OADTab,	CPos_Ac_De_Over_Note_1},
	{C_OverReverseActiveEventNo,	C_SourceExist,	CRev_Ac_De_Over_Degree,	CRev_Ac_De_Over_OADTab,	CRev_Ac_De_Over_Note_1},
	{C_1OverIdleDemandEventNo,	C_SourceExist,	CQua1_Re_De_Over_Degree,CQua_Re_De_Over_OADTab,	CQua1_Re_De_Over_Note_1},
	{C_2OverIdleDemandEventNo,	C_SourceExist,	CQua2_Re_De_Over_Degree,CQua_Re_De_Over_OADTab,	CQua2_Re_De_Over_Note_1},
	{C_3OverIdleDemandEventNo,	C_SourceExist,	CQua3_Re_De_Over_Degree,CQua_Re_De_Over_OADTab,	CQua3_Re_De_Over_Note_1},
	{C_4OverIdleDemandEventNo,	C_SourceExist,	CQua4_Re_De_Over_Degree,CQua_Re_De_Over_OADTab,	CQua4_Re_De_Over_Note_1},
	{C_OverpowerfactEventNo,	C_SourceNon,	CPFactorT_Over_Degree,	CPFactorT_Over_OADTab,	CPFactorT_FF_1},
	{C_AOverpowerfactEventNo,	C_SourceNon,	CPFactorA_Over_Degree,	CPFactorT_Over_OADTab,	CPFactorA_FF_1},
    {C_BOverpowerfactEventNo,	C_SourceNon,	CPFactorB_Over_Degree,	CPFactorT_Over_OADTab,	CPFactorB_FF_1},
    {C_COverpowerfactEventNo,	C_SourceNon,	CPFactorC_Over_Degree,	CPFactorT_Over_OADTab,	CPFactorC_FF_1},
	{C_TotalVoltageLoseEventNo,	C_SourceExist,	CAll_Loss_Vol_Degree,	CAll_Loss_Vol_OADTab,	CAll_Loss_Vol_Note_1},
	{C_ACPowerFailEventNo,		C_SourceExist,	CAux_Pow_Down_Degree,	CAux_Pow_Down_OADTab,	CAux_Pow_Down_Note_1},
	{C_ReversephaseVoltageEventNo,	C_SourceExist,	CRevPS_Vol_Degree,	CRevPS_Vol_OADTab,	CRevPSVol_FF_1},
	{C_ReversephaseCurrentEventNo,	C_SourceExist,	CRevPS_Curr_Degree,	CRevPS_Curr_OADTab,	CRevPSCurr_FF_1},
	{C_PowerfailEventNo,		C_SourceExist,	CPow_Down_Degree,	CPow_Down_OADTab,	CPow_Down_Note_1},
	{C_OpenMeterCoverEventNo,	C_SourceExist,	COpenW_Degree,		COpenW_OADTab,		COpenW_Note_1},
	{C_OpenTerminalCoverEventNo,	C_SourceExist,	COpenCW_Degree,		COpenCW_OADTab,		COpenCW_Note_1},
	{C_UnbanlanceVoltageEventNo,	C_SourceExist,	CNoBal_Vol_Degree,	CNoBal_Vol_OADTab,	CNoBalVol_FF_1},
	{C_UnbanlanceCurrentEventNo,	C_SourceExist,	CNoBal_Curr_Degree,	CNoBal_Curr_OADTab,	CNoBalCurr_FF_1},
	{C_MagneticCheckEventNo,	C_SourceExist,	CConM_Degree,		CConM_OADTab,		CConM_Note_1},
	{C_PowerAbnormalEventNo,	C_SourceExist,	CPowerFa_Degree,	CPowerFa_OADTab,	CPowerFa_Note_1},
	{C_SUnbanlanceCurrentEventNo,	C_SourceExist,	CSevNoBal_Curr_Degree,	CSevNoBal_Curr_OADTab,	CSevNoBalCurr_FF_1},
#if 0
	{C_ReversecurrentEventNo,	C_SourceNon,	CTrend_Rev_Degree,	CPower_Rev_OADTab,	CTrend_Rev_Note_1},
#endif
	{C_ProgramEventNo,		C_SourceExist,	CProgram_Degree,	CProgram_OADTab,	CProgram_Note_1},
	{C_TolClearEventNo,		C_SourceExist,	CTol_Clear_Degree,	CTol_Clear_OADTab,	CTol_Clear_Note_1},
	{C_DemandClearEventNo,		C_SourceExist,	CDe_Clear_Degree,	CDe_Clear_OADTab,	CDe_Clear_Note_1},
	{C_EventClearEventNo,		C_SourceExist,	CEven_Clear_Degree,	CEven_Clear_OADTab,	CEven_Clear_Note_1},
	{C_AdjTimeEventNo,		C_SourceExist,	CAdjTime_Degree,	CAdjTime_OADTab,	CAdjTime_Note_1},
	{C_ProgPTEventNo,		C_SourceExist,	CProgPT_Degree,		CProgPT_OADTab,		CProgPT_Note_1},
	{C_ProgPZEventNo,		C_SourceExist,	CProgTZ_Degree,		CProgTZ_OADTab,		CProgTZ_Note_1},
	{C_ProgWReEventNo,		C_SourceExist,	CProgWRe_Degree,	CProgWRe_OADTab,	CProgWRe_Note_1},
	{C_ProgSettDEventNo,		C_SourceExist,	CProgSettD_Degree,	CProgSettD_OADTab,	CProgSettD_Note_1},
	{C_RelayOpenEventNo,		C_SourceExist,	CRelayOpen_Degree,	CRelayOpen_OADTab,	CRelayOpen_FF_1},
	{C_RelayCloseEventNo,		C_SourceExist,	CRelayClose_Degree,	CRelayClose_OADTab,	CRelayClose_FF_1},
	{C_ProgHolEventNo,		C_SourceExist,	CProgHol_Degree,	CProgHol_OADTab,	CProgHol_Note_1},
	{C_ProgAcCEventNo,		C_SourceExist,	CProgAcC_Degree,	CProgAcC_OADTab,	CProgAcC_Note_1},
	{C_ProgReCEventNo,		C_SourceExist,	CProgReC_Degree,	CProgReC_OADTab,	CProgReC_Note_1},
	{C_ProgTParaEventNo,		C_SourceExist,	CProgTPara_Degree,	CProgTPara_OADTab,	CProgTPara_Note_1},
	{C_ProgLadEventNo,		C_SourceExist,	CProgLad_Degree,	CProgLad_OADTab,	CProgLad_Note_1},
	{C_Key_UpdateEventNo,		C_SourceExist,	CProgKD_Degree,		CProgKD_OADTab,		CProgKD_Note_1},
	{C_AbnorCEventNo,		C_SourceExist,	CAbnorC_Degree,		CAbnorC_OADTab,		CAbnorC_Note_1},
	{C_BuyCurrEventNo,		C_SourceExist,	CBuyCurr_Degree,	CBuyCurr_OADTab,	CBuyCurr_FF_Note_1},
	{C_ReturnMoneyEventNo,		C_SourceExist,	CReturn_M_Degree,	CReturn_M_OADTab,	CReturn_M_Note_1},
	{C_RelayFaEndEnEventNo,		C_SourceExist,	CRelayFa_Degree,	CRelayFa_OADTab,	CRelayFa_Note_1},
	{C_MeterFaEventNo,		C_SourceExist,	CMeterFa_Degree,	CMeterFa_OADTab,	CMeterFa_Note_1},
	{C_ClockFaEventNo,		C_SourceExist,	CClockFa_Degree,	CClockFa_OADTab,	CClockFa_Note_1},
	{C_BroadcastTimeEventNo,		C_SourceExist,	CBroadcastTime_Degree,	CBroadcastTime_OADTab,	CBroadcastTime_Note_1},
	{C_NeutralCurrentAbnormalEventNo, C_SourceExist,CNeutralCurrentAbnormal_Degree, CNeutralCurrentAbnormal_OADTab, CNeutralCurrentAbnormal_Note_1},
#if 0
	{C_BroadTimeAbnormalEventNo,		C_SourceExist,	CBroadTimeAbnormal_Degree,	CBroadTimeAbnormal_OADTab,	CBroadTimeAbnormal_Note_1},
#endif
};
#define EventMappingTable_Len  sizeof(EventMappingTable)/sizeof(Str_EventMapping_Type)

/*****************************************************************************************/
/*表格的顺序不能随意调整！！*/
/*****************************************************************************************/
/*读实时量表格*/
const Str_SpecialReadTable_Type	SpecialReadTable[]=
{
	{CAll_Loss_Vol_Note_1,		CAll_Loss_Vol_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{CAux_Pow_Down_Note_1,		CAux_Pow_Down_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{CLossAVol_FF_1,		CLossA_Vol_Time,	CLossAVol_TolAh_1,	CLossAVol_AAh_1,	CLossAVol_BAh_1,	CLossAVol_CAh_1		},
	{CLossBVol_FF_1,		CLossB_Vol_Time,	CLossBVol_TolAh_1,	CLossBVol_AAh_1,	CLossBVol_BAh_1,	CLossBVol_CAh_1		},
	{CLossCVol_FF_1,		CLossC_Vol_Time,	CLossCVol_TolAh_1,	CLossCVol_AAh_1,	CLossCVol_BAh_1,	CLossCVol_CAh_1		},
	{CLowAVol_FF_1,			CLowA_Vol_Time,		CLowAVol_TolAh_1,	CLowAVol_AAh_1,		CLowAVol_BAh_1,		CLowAVol_CAh_1		},
	{CLowBVol_FF_1,			CLowB_Vol_Time,		CLowBVol_TolAh_1,	CLowBVol_AAh_1,		CLowBVol_BAh_1,		CLowBVol_CAh_1		},
	{CLowCVol_FF_1,			CLowC_Vol_Time,		CLowCVol_TolAh_1,	CLowCVol_AAh_1,		CLowCVol_BAh_1,		CLowCVol_CAh_1		},
	{COverAVol_FF_1,		COverA_Vol_Time,	COverAVol_TolAh_1,	COverAVol_AAh_1,	COverAVol_BAh_1,	COverAVol_CAh_1		},
	{COverBVol_FF_1,		COverB_Vol_Time,	COverBVol_TolAh_1,	COverBVol_AAh_1,	COverBVol_BAh_1,	COverBVol_CAh_1		},
	{COverCVol_FF_1,		COverC_Vol_Time,	COverCVol_TolAh_1,	COverCVol_AAh_1,	COverCVol_BAh_1,	COverCVol_CAh_1		},
	{CBreakAVol_FF_1,		CBreakA_Vol_Time,	CBreakAVol_TolAh_1,	CBreakAVol_AAh_1,	CBreakAVol_BAh_1,	CBreakAVol_CAh_1	},
	{CBreakBVol_FF_1,		CBreakB_Vol_Time,	CBreakBVol_TolAh_1,	CBreakBVol_AAh_1,	CBreakBVol_BAh_1,	CBreakBVol_CAh_1	},
	{CBreakCVol_FF_1,		CBreakC_Vol_Time,	CBreakCVol_TolAh_1,	CBreakCVol_AAh_1,	CBreakCVol_BAh_1,	CBreakCVol_CAh_1	},
	{CRevPSVol_FF_1,		CRevPS_Vol_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{CRevPSCurr_FF_1,		CRevPS_Curr_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{CNoBalVol_FF_1,		CNoBal_Vol_Time,	CNoBalRate_Vol_End_1,	C_NULL,			C_NULL,			C_NULL			},
	{CNoBalCurr_FF_1,		CNoBal_Curr_Time,	CNoBalRate_Curr_1,	C_NULL,			C_NULL,			C_NULL			},
	{CLossACurr_FF_1,		CLossA_Curr_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{CLossBCurr_FF_1,		CLossB_Curr_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{CLossCCurr_FF_1,		CLossC_Curr_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{COverACurr_FF_1,		COverA_Curr_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{COverBCurr_FF_1,		COverB_Curr_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{COverCCurr_FF_1,		COverC_Curr_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{CBreakACurr_FF_1,		CBreakA_Curr_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{CBreakBCurr_FF_1,		CBreakB_Curr_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{CBreakCCurr_FF_1,		CBreakC_Curr_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{CPowerTRev_FF_1,		CPowerT_Rev_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{CPowerARev_FF_1,		CPowerA_Rev_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{CPowerBRev_FF_1,		CPowerB_Rev_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{CPowerCRev_FF_1,		CPowerC_Rev_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{COverALo_FF_1,			COverA_Lo_Time,		C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{COverBLo_FF_1,			COverB_Lo_Time,		C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{COverCLo_FF_1,			COverC_Lo_Time,		C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{CPFactorT_FF_1,		CPFactorT_Over_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{CPFactorA_FF_1,		CPFactorA_Over_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{CPFactorB_FF_1,		CPFactorB_Over_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{CPFactorC_FF_1,		CPFactorC_Over_Time,	C_NULL,			C_NULL,			C_NULL,			C_NULL			},
	{CSevNoBalCurr_FF_1,		CSevNoBal_Curr_Time,	CSevNoBalRate_Curr_1,	C_NULL,			C_NULL,			C_NULL			},
	{CPos_Ac_De_Over_Note_1,	CPos_Ac_De_Over_Time,	CPos_Ac_De_Over_1,	C_NULL,			C_NULL,			C_NULL			},
	{CRev_Ac_De_Over_Note_1,	CRev_Ac_De_Over_Time,	CRev_Ac_De_Over_1,	C_NULL,			C_NULL,			C_NULL			},
	{CQua1_Re_De_Over_Note_1,	CQua1_Re_De_Over_Time,	CQua1_Re_De_Over_1,	C_NULL,			C_NULL,			C_NULL			},
	{CQua2_Re_De_Over_Note_1,	CQua2_Re_De_Over_Time,	CQua2_Re_De_Over_1,	C_NULL,			C_NULL,			C_NULL			},
	{CQua3_Re_De_Over_Note_1,	CQua3_Re_De_Over_Time,	CQua3_Re_De_Over_1,	C_NULL,			C_NULL,			C_NULL			},
	{CQua4_Re_De_Over_Note_1,	CQua4_Re_De_Over_Time,	CQua4_Re_De_Over_1,	C_NULL,			C_NULL,			C_NULL			},
};
#define SpecialReadTable_Len  sizeof(SpecialReadTable)/sizeof(Str_SpecialReadTable_Type)

const Str_CurrentDataReadTable_Type	CurrentDataReadTable[]=
{
	{CLoss_TollVol_Current,		C_SourceNon,			C_NULL,                          CLoss_TollVol_Attri14_Nature,	CLoss_Vol_Degree,		CLoss_Vol_Time},
	{CLossA_Vol_Current,		C_SourceNon,			C_AlossvoltageEventNo,           CLossA_Vol_Attri14_Nature,		CLossA_Vol_Degree,		CLossA_Vol_Time},
	{CLossB_Vol_Current,		C_SourceNon,			C_BlossvoltageEventNo,           CLossB_Vol_Attri14_Nature,		CLossB_Vol_Degree,		CLossB_Vol_Time},
	{CLossC_Vol_Current,		C_SourceNon,			C_ClossvoltageEventNo,           CLossC_Vol_Attri14_Nature,		CLossC_Vol_Degree,		CLossC_Vol_Time},
	{CLowA_Vol_Current,			C_SourceNon,			C_ALessvoltageEventNo,           CLowA_Vol_Attri14_Nature,		CLowA_Vol_Degree,		CLowA_Vol_Time},
	{CLowB_Vol_Current,			C_SourceNon,			C_BLessvoltageEventNo,           CLowB_Vol_Attri14_Nature,		CLowB_Vol_Degree,		CLowB_Vol_Time},
	{CLowC_Vol_Current,			C_SourceNon,			C_CLessvoltageEventNo,           CLowC_Vol_Attri14_Nature,		CLowC_Vol_Degree,		CLowC_Vol_Time},
	{COverA_Vol_Current,		C_SourceNon,			C_AOvervoltageEventNo,           COverA_Vol_Attri14_Nature,		COverA_Vol_Degree,		COverA_Vol_Time},
	{COverB_Vol_Current,		C_SourceNon,			C_BOvervoltageEventNo,           COverB_Vol_Attri14_Nature,		COverB_Vol_Degree,		COverB_Vol_Time},
	{COverC_Vol_Current,		C_SourceNon,			C_COvervoltageEventNo,           COverC_Vol_Attri14_Nature,		COverC_Vol_Degree,		COverC_Vol_Time},
	{CBreakA_Vol_Current,		C_SourceNon,			C_ALossphaseEventNo,             CBreakA_Vol_Attri14_Nature,		CBreakA_Vol_Degree,		CBreakA_Vol_Time},
	{CBreakB_Vol_Current,		C_SourceNon,			C_BLossphaseEventNo,             CBreakB_Vol_Attri14_Nature,		CBreakB_Vol_Degree,		CBreakB_Vol_Time},
	{CBreakC_Vol_Current,		C_SourceNon,			C_CLossphaseEventNo,             CBreakC_Vol_Attri14_Nature,		CBreakC_Vol_Degree,		CBreakC_Vol_Time},
	{CLossA_Curr_Current,		C_SourceNon,			C_ALosscurrentEventNo,           CLossA_Curr_Attri14_Nature,		CLossA_Curr_Degree,		CLossA_Curr_Time},
	{CLossB_Curr_Current,		C_SourceNon,			C_BLosscurrentEventNo,           CLossB_Curr_Attri14_Nature,		CLossB_Curr_Degree,		CLossB_Curr_Time},
	{CLossC_Curr_Current,		C_SourceNon,			C_CLosscurrentEventNo,           CLossC_Curr_Attri14_Nature,		CLossC_Curr_Degree,		CLossC_Curr_Time},
	{COverA_Curr_Current,		C_SourceNon,			C_AOvercurrentEventNo,           COverA_Curr_Attri14_Nature,		COverA_Curr_Degree,		COverA_Curr_Time},
	{COverB_Curr_Current,		C_SourceNon,			C_BOvercurrentEventNo,           COverB_Curr_Attri14_Nature,		COverB_Curr_Degree,		COverB_Curr_Time},
	{COverC_Curr_Current,		C_SourceNon,			C_COvercurrentEventNo,           COverC_Curr_Attri14_Nature,		COverC_Curr_Degree,		COverC_Curr_Time},
	{CBreakA_Curr_Current,		C_SourceNon,			C_AFailcurrentEventNo,           CBreakA_Curr_Attri14_Nature,	CBreakA_Curr_Degree,	CBreakA_Curr_Time},
	{CBreakB_Curr_Current,		C_SourceNon,			C_BFailcurrentEventNo,           CBreakB_Curr_Attri14_Nature,	CBreakB_Curr_Degree,	CBreakB_Curr_Time},
	{CBreakC_Curr_Current,		C_SourceNon,			C_CFailcurrentEventNo,           CBreakC_Curr_Attri14_Nature,	CBreakC_Curr_Degree,	CBreakC_Curr_Time},
	{CPowerT_Rev_Current,		C_SourceNon,			C_TReversecurrentEventNo,        CPowerT_Rev_Attri14_Nature,		CPowerT_Rev_Degree,		CPowerT_Rev_Time},
	{CPowerA_Rev_Current,		C_SourceNon,			C_AReversecurrentEventNo,        CPowerA_Rev_Attri14_Nature,		CPowerA_Rev_Degree,		CPowerA_Rev_Time},
	{CPowerB_Rev_Current,		C_SourceNon,			C_BReversecurrentEventNo,        CPowerB_Rev_Attri14_Nature,		CPowerB_Rev_Degree,		CPowerB_Rev_Time},
	{CPowerC_Rev_Current,		C_SourceNon,			C_CReversecurrentEventNo,        CPowerC_Rev_Attri14_Nature,		CPowerC_Rev_Degree,		CPowerC_Rev_Time},
	{COverA_Lo_Current,			C_SourceNon,			C_AOverloadEventNo,              COverA_Lo_Attri14_Nature,		COverA_Lo_Degree,		COverA_Lo_Time},
	{COverB_Lo_Current,			C_SourceNon,			C_BOverloadEventNo,              COverB_Lo_Attri14_Nature,		COverB_Lo_Degree,		COverB_Lo_Time},
	{COverC_Lo_Current,			C_SourceNon,			C_COverloadEventNo,              COverC_Lo_Attri14_Nature,		COverC_Lo_Degree,		COverC_Lo_Time},
	{CPos_Ac_De_Over_Current,	C_SourceExist,			C_OverForwardActiveEventNo,      CPos_Ac_De_Over_Attri7_Nature,	CPos_Ac_De_Over_Degree,	CPos_Ac_De_Over_Time},
	{CRev_Ac_De_Over_Current,	C_SourceExist,			C_OverReverseActiveEventNo,      CRev_Ac_De_Over_Attri7_Nature,	CRev_Ac_De_Over_Degree,	CRev_Ac_De_Over_Time},
	{CQua1_Re_De_Over_Current,	C_SourceNon,			C_1OverIdleDemandEventNo,        CQua1_Re_De_Over_Attri14_Nature,CQua1_Re_De_Over_Degree,CQua1_Re_De_Over_Time},
	{CQua2_Re_De_Over_Current,	C_SourceNon,			C_2OverIdleDemandEventNo,        CQua2_Re_De_Over_Attri14_Nature,CQua2_Re_De_Over_Degree,CQua2_Re_De_Over_Time},
	{CQua3_Re_De_Over_Current,	C_SourceNon,			C_3OverIdleDemandEventNo,        CQua3_Re_De_Over_Attri14_Nature,CQua3_Re_De_Over_Degree,CQua3_Re_De_Over_Time},
	{CQua4_Re_De_Over_Current,	C_SourceNon,			C_4OverIdleDemandEventNo,        CQua4_Re_De_Over_Attri14_Nature,CQua4_Re_De_Over_Degree,CQua4_Re_De_Over_Time},
	{CPFactorT_Over_Current,	C_SourceNon,			C_OverpowerfactEventNo,          CPFactorT_Over_Attri14_Nature,	CPFactorT_Over_Degree,	CPFactorT_Over_Time},
	{CPFactorA_Over_Current,	C_SourceNon,			C_AOverpowerfactEventNo,          CPFactorA_Over_Attri14_Nature,	CPFactorA_Over_Degree,	CPFactorA_Over_Time},
	{CPFactorB_Over_Current,	C_SourceNon,			C_BOverpowerfactEventNo,          CPFactorB_Over_Attri14_Nature,	CPFactorB_Over_Degree,	CPFactorB_Over_Time},
	{CPFactorC_Over_Current,	C_SourceNon,			C_COverpowerfactEventNo,          CPFactorC_Over_Attri14_Nature,	CPFactorC_Over_Degree,	CPFactorC_Over_Time},
	{CAll_Loss_Vol_Current,		C_SourceExist,			C_TotalVoltageLoseEventNo,       CAll_Loss_Vol_Attri7_Nature,	CAll_Loss_Vol_Degree,	CAll_Loss_Vol_Time},
	{CAux_Pow_Down_Current,		C_SourceExist,			C_ACPowerFailEventNo,            CAux_Pow_Down_Attri7_Nature,	CAux_Pow_Down_Degree,	CAux_Pow_Down_Time},
	{CRevPS_Vol_Current,		C_SourceExist,			C_ReversephaseVoltageEventNo,    CRevPS_Vol_Attri7_Nature,		CRevPS_Vol_Degree,		CRevPS_Vol_Time},
	{CRevPS_Curr_Current,		C_SourceExist,			C_ReversephaseCurrentEventNo,    CRevPS_Curr_Attri7_Nature,		CRevPS_Curr_Degree,		CRevPS_Curr_Time},
	{CPow_Down_Current,			C_SourceExist,			C_PowerfailEventNo,              CPow_Down_Attri7_Nature,		CPow_Down_Degree,		CPow_Down_Time},
	{CProgram_Current,			C_SourceExist,			C_ProgramEventNo,                CProgram_Attri7_Nature,			CProgram_Degree,		C_NULL},
	{CTol_Clear_Current,		C_SourceExist,			C_TolClearEventNo,               CTol_Clear_Attri7_Nature,		CTol_Clear_Degree,		C_NULL},
	{CDe_Clear_Current,			C_SourceExist,			C_DemandClearEventNo,            CDe_Clear_Attri7_Nature,		CDe_Clear_Degree,		C_NULL},
	{CEven_Clear_Current,		C_SourceExist,			C_EventClearEventNo,             CEven_Clear_Attri7_Nature,		CEven_Clear_Degree,		C_NULL},
	{CAdjTime_Current,			C_SourceExist,			C_AdjTimeEventNo,                CAdjTime_Attri7_Nature	,		CAdjTime_Degree,		C_NULL},
	{CProgPT_Current,			C_SourceExist,			C_ProgPTEventNo,                 CProgPT_Attri7_Nature,			CProgPT_Degree,			C_NULL},
	{CProgTZ_Current,			C_SourceExist,			C_ProgPZEventNo,                 CProgTZ_Attri7_Nature,			CProgTZ_Degree,			C_NULL},
	{CProgWRe_Current,			C_SourceExist,			C_ProgWReEventNo,                CProgWRe_Attri7_Nature,			CProgWRe_Degree,		C_NULL},
	{CProgSettD_Current,		C_SourceExist,			C_ProgSettDEventNo,              CProgSettD_Attri7_Nature,		CProgSettD_Degree,		C_NULL},
	{COpenW_Current,			C_SourceExist,			C_OpenMeterCoverEventNo,         COpenW_Attri7_Nature,			COpenW_Degree,			COpenW_Time},
	{COpenCW_Current,			C_SourceExist,			C_OpenTerminalCoverEventNo,      COpenCW_Attri7_Nature,			COpenCW_Degree,			COpenCW_Time},
	{CNoBal_Vol_Current,		C_SourceExist,			C_UnbanlanceVoltageEventNo,      CNoBal_Vol_Attri7_Nature,		CNoBal_Vol_Degree,		CNoBal_Vol_Time},
	{CNoBal_Curr_Current,		C_SourceExist,			C_UnbanlanceCurrentEventNo,      CNoBal_Curr_Attri7_Nature,		CNoBal_Curr_Degree,		CNoBal_Curr_Time},
	{CRelayOpen_Current,		C_SourceExist,			C_RelayOpenEventNo,              CRelayOpen_Attri7_Nature,		CRelayOpen_Degree,		C_NULL},
	{CRelayClose_Current,		C_SourceExist,			C_RelayCloseEventNo,             CRelayClose_Attri7_Nature,		CRelayClose_Degree,		C_NULL},
	{CProgHol_Current,			C_SourceExist,			C_ProgHolEventNo,                CProgHol_Attri7_Nature,			CProgHol_Degree,		C_NULL},
	{CProgAcC_Current,			C_SourceExist,			C_ProgAcCEventNo,                CProgAcC_Attri7_Nature,			CProgAcC_Degree,		C_NULL},
	{CProgReC_Current,			C_SourceExist,			C_ProgReCEventNo,                CProgReC_Attri7_Nature,			CProgReC_Degree,		C_NULL},
	{CProgTPara_Current,		C_SourceExist,			C_ProgTParaEventNo,              CProgTPara_Attri7_Nature,		CProgTPara_Degree,		C_NULL},
	{CProgLad_Current,			C_SourceExist,			C_ProgLadEventNo,                CProgLad_Attri7_Nature,			CProgLad_Degree,		C_NULL},
	{CProgKD_Current,			C_SourceExist,			C_Key_UpdateEventNo,             CProgKD_Attri7_Nature,			CProgKD_Degree,			C_NULL},
	{CAbnorC_Current,			C_SourceExist,			C_AbnorCEventNo,                 CAbnorC_Attri7_Nature,			CAbnorC_Degree,			C_NULL},
	{CBuyCurr_Current,			C_SourceExist,			C_BuyCurrEventNo,                CBuyCurr_Attri7_Nature,			CBuyCurr_Degree,		C_NULL},
	{CReturn_M_Current,			C_SourceExist,			C_ReturnMoneyEventNo,            CReturn_M_Attri7_Nature,		CReturn_M_Degree,		C_NULL},
	{CConM_Current,				C_SourceExist,			C_MagneticCheckEventNo,          CConM_Attri7_Nature,			CConM_Degree,			CConM_Time},
	{CRelayFa_Current,			C_SourceExist,			C_RelayFaEndEnEventNo,           CRelayFa_Attri7_Nature,			CRelayFa_Degree,		C_NULL},
	{CPowerFa_Current,			C_SourceExist,			C_PowerAbnormalEventNo,          CPowerFa_Attri7_Nature,			CPowerFa_Degree,		CPowerFa_Time},
	{CSevNoBal_Curr_Current,	C_SourceExist,			C_SUnbanlanceCurrentEventNo,     CSevNoBal_Curr_Attri7_Nature,	CSevNoBal_Curr_Degree,	CSevNoBal_Curr_Time},
	{CClockFa_Current,			C_SourceExist,			C_ClockFaEventNo,                CClockFa_Attri7_Nature,			CClockFa_Degree,		CClockFa_Time},
	{CMeterFa_Current,			C_SourceExist,			C_MeterFaEventNo,                CMeterFa_Attri7_Nature,			CMeterFa_Degree,		CMeterFa_Time},
#if 0
	{CTrend_Rev_Current,		C_SourceNon,			C_ReversecurrentEventNo,         CTrend_Rev_Attri7_Nature,		CTrend_Rev_Degree,		C_NULL},
#endif
    {CBroadcastTime_Current,	C_SourceExist,			C_BroadcastTimeEventNo,			CBroadcastTime_Attri7_Nature,		CBroadcastTime_Degree,		C_NULL},
	{CNeutralCurrentAbnormal_Current,	C_SourceExist,	C_NeutralCurrentAbnormalEventNo,		CNeutralCurrentAbnormal_Attri7_Nature,		CNeutralCurrentAbnormal_Degree,		CNeutralCurrentAbnormal_Time},
#if 0
	{CBroadTimeAbnormal_Current,	C_SourceExist,		C_BroadTimeAbnormalEventNo,		CBroadTimeAbnormal_Attri7_Nature,		CBroadTimeAbnormal_Degree,		C_NULL},
#endif
};
#define CurrentDataReadTable_Len  sizeof(CurrentDataReadTable)/sizeof(Str_CurrentDataReadTable_Type)

/***********************************************************************************
函数原型：uchar8 PF_GetAbs(uchar8 *V_ucSrc, uchar8 *V_ucDest, uchar8 V_ucNum)
功能描述：取绝对值
输入参数：*V_ucSrc：原始数据首地址；
            V_ucNum原始数据长度，取值范围1-4
输出参数：*V_ucDest：转换后的数据，输出长度根据V_ucNum而定
返回参数：返回是否为负数，C_Plus、C_Minus、C_Error
功能说明：入参V_ucSrc原始数据必须为hex格式
调用机制：
备    注：
**********************************************************************************/
uchar8 PF_GetAbs(uchar8 *V_ucSrc, uchar8 *V_ucDest, uchar8 V_ucNum)
{
    long32 V_lBuff = 0;
    uchar8 V_uci, V_ucSign;

    if((V_ucNum == 0)
      ||(V_ucNum > 4))
    {
        return C_Error;
    }
    if((V_ucNum < 4) && (V_ucSrc[V_ucNum - 1] & 0x80))/*小于4字节的负数高字节补FF*/
    {
        for(V_uci = 0;V_uci < (4 - V_ucNum);V_uci ++)
        {
            V_lBuff <<= 8;
            V_lBuff |= 0xFF;
        }
    }
    for(V_uci = 0;V_uci < V_ucNum;V_uci ++)/*原始数据转换为long32*/
    {
        V_lBuff <<= 8;
		V_lBuff |= V_ucSrc[V_ucNum - V_uci - 1];
	}
    if(V_lBuff < 0)
    {
        V_lBuff = -V_lBuff;
        V_ucSign = C_Minus;
    }
    else
    {
        V_ucSign = C_Plus;
    }
    for(V_uci = 0;V_uci < V_ucNum;V_uci ++)
	{
		V_ucDest[V_uci] = (uchar8)V_lBuff;
		V_lBuff >>= 8;
	}
    return V_ucSign;
}

/***********************************************************************************
函数原型：uchar8 SF_HEXAddBytes(uchar8 *Add1, uchar8 *Add2, uchar8 *AddResult, uchar8 Len)
功能描述：多字节HEX数据加法
输入参数：Add1为加数1低字节地址
        Add2加数2低字节地址
        AddResult和存放地址
        Len数据长度
输出参数：累加和数据存放AddResult地址开始的Len字节
返回参数：C_CY表示结果又进位，C_NoCY表示没有进位
功能说明：1.原始数据需为hex格式；2.AddResult地址可以与Add1或者Add2相同
调用机制：
备    注：Add1,Add2必须为无符号数
**********************************************************************************/
uchar8 SF_HEXAddBytes(uchar8 *Add1, uchar8 *Add2, uchar8 *AddResult, uchar8 Len)
{
    uchar8 V_ucCY, V_uci;
    ushort16 V_usTemp = 0;

    V_ucCY = C_NoCY;
    for(V_uci = 0;V_uci < Len;V_uci ++)
    {
        V_usTemp = Add1[V_uci] + Add2[V_uci] + V_ucCY;

        if(V_usTemp & 0xFF00)
        {
            V_ucCY = C_CY;
        }
        else
        {
            V_ucCY = C_NoCY;
        }
        AddResult[V_uci] = (uchar8)V_usTemp;
    }
	return V_ucCY;
}

/***********************************************************************************
函数原型：uchar8 SF_HEXDECBytes(uchar8 *Dec1, uchar8 *Dec2, uchar8 *DecResult, uchar8 Len)
功能描述：多字节HEX数据减法
输入参数：Dec1为被减数低字节地址, Dec2为减数低字节地址, DecResult差存放地址, Len数据长度
输出参数：差存放DecResult地址开始的Len字节
返回参数：C_CY表示结果又进位，C_NoCY表示没有进位
功能说明：1.原始数据需为无符号hex格式；2.差DecResult所指向地址可以与Dec1或者Dec2相同
调用机制：
备    注：Add1,Add2必须为无符号数
**********************************************************************************/
uchar8 SF_HEXDECBytes(uchar8 *Dec1, uchar8 *Dec2, uchar8 *DecResult, uchar8 Len)
{
    uchar8 V_ucCY, V_uci, V_ucDecResult;
    ushort16 V_usDec1, V_usDec2;

    V_ucCY = C_NoCY;
    for(V_uci = 0;V_uci < Len;V_uci ++)
    {
        V_usDec1 = Dec1[V_uci];
        V_usDec2 = Dec2[V_uci];

        if(V_usDec1 >= (V_usDec2 + V_ucCY))  /*被减数低半字节小于减数与借位标志之和*/
        {
            V_ucDecResult = V_usDec1 - (V_usDec2 + V_ucCY);
            V_ucCY = C_NoCY;
        }
        else
        {
            V_ucDecResult = (V_usDec1 + 0x0100) - (V_usDec2 + V_ucCY);
            V_ucCY = C_CY;
        }
        DecResult[V_uci] = V_ucDecResult;
    }
	return V_ucCY;
}

/***********************************************************************************
函数原型：SF_ReadLastEvt
功能描述：读上一次事件记录的相关处理
输入参数：pV_ulReadOAD:读取OAD缓存，pV_ucDataBuff：读取数据缓存，pV_usLen：缓存长度, V_ucNum：上N次
输出参数：pV_ucDataBuff：读取数据缓存，pV_usLen：读取数据长度
返回参数：同InF_GetData_Record_DataBase返回参数
功能说明：
调用机制：
备    注：
**********************************************************************************/
uchar8 SF_ReadLastEvt(ulong32 *pV_ulReadOAD, uchar8 *pV_ucDataBuff, ushort16 *pV_usLen, uchar8 V_ucNum)
{
    Str_Read_T Str_Read_TTemp;
    uchar8 V_ucReadBuff[2], V_ucReturn;

    V_ucReadBuff[0] = 9;/*方法9*/
    V_ucReadBuff[1] = V_ucNum;/*上N次*/

    Str_Read_TTemp.pV_ulROAD = pV_ulReadOAD;
    Str_Read_TTemp.pV_ucRST = V_ucReadBuff;
    Str_Read_TTemp.V_usROAD_Num = 1;
    Str_Read_TTemp.V_ucReadMode = C_OtherMode;
    Str_Read_TTemp.V_ucChannelNo = 0xFF;


    V_ucReturn = InF_GetData_Record_DataBase(&Str_Read_TTemp, pV_ucDataBuff, pV_usLen, C_NULL);

    return V_ucReturn;
}

/***********************************************************************************
函数原型： uchar8  InF_EventOADFind(uchar8 V_EventNo)
功能描述*根据数据标示返回事件记录号，供事件记录、通信模块用
输入参数：
    ulong32 V_DI：数据标识
输出参数：无
返回参数：uchar8：EventNum, C_IDError
功能说明：事件记录模块，用于获取Num号；通信模块用于判断标识码是否正确
调用机制：
备    注：未被调用
***********************************************************************************/
ulong32  InF_EventOADFind(uchar8 V_EventNo)
{
	uchar8  V_uci;
	ulong32 V_Data_Id=C_OADError;

	for(V_uci=0;V_uci<EventMappingTable_Len;V_uci++)
	{
	   if(V_EventNo==EventMappingTable[V_uci].EventNo)
	   {
	  	 break;
	   }
	}

	if(V_uci < EventMappingTable_Len)
	{
		V_Data_Id = EventMappingTable[V_uci].WriteOAD;
	}
	return V_Data_Id;
}

/***********************************************************************************
函数原型：uchar8 SF_Judge_EventIntegrity(uchar8 V_ucEventNo)
功能描述：判断事件FLASH中的事件状态
输入参数：EventNo
输出参数：返回事件类型状态
返回参数C_IDError             数据标识码错误
           C_Happen_EventState	事件状态，有发生无恢复
          C_End_EventState	  	事件状态，非有发生无恢复
功能说明：防止事件写FLASH错误；
调用机制：写消息时调用
备    注：
***********************************************************************************/
uchar8 SF_Judge_EventIntegrity(uchar8 V_ucEventNo)
{
	uchar8		V_ucJudgeBuffer[C_Judge_20BufferLength], V_ucNullJudgeBuffer[C_EventTimeLength] = {0};
	ushort16	V_usBufferLength = C_Judge_20BufferLength;
	uchar8		V_ucMode;
	ulong32		V_ulRead_OAD_Hp[3], V_ulRead_OAD_End[3];

	V_ulRead_OAD_Hp[0] = EventHappenEndTime[V_ucEventNo];
	V_ulRead_OAD_Hp[1] = CEventHPTime;
	V_ulRead_OAD_Hp[2] = 0xFFFFFFFF;
	V_ulRead_OAD_End[0] = EventHappenEndTime[V_ucEventNo];
	V_ulRead_OAD_End[1] = CEventEndTime;
	V_ulRead_OAD_End[2] = 0xFFFFFFFF;

    if( (V_ucEventNo < C_TolClearEventNo) || (V_ucEventNo == C_RelayFaEndEnEventNo) )
    {
        V_usBufferLength = C_Judge_20BufferLength;/*V0.2新增长度赋值*/

        V_ucMode = SF_ReadLastEvt(V_ulRead_OAD_Hp, &V_ucJudgeBuffer[C_Judge_StartBuffer0], &V_usBufferLength, (uchar8)V_ulRead_OAD_Hp[0]);/*读FLASH中最近一次事件记录发生时刻*/
        if(V_ucMode == C_OK)
        {
            V_usBufferLength = C_Judge_20BufferLength - 7;/*V0.2新增长度赋值*/
            V_ucMode = SF_ReadLastEvt(V_ulRead_OAD_End, &V_ucJudgeBuffer[C_Judge_TimeEndBuffer], &V_usBufferLength, (uchar8)V_ulRead_OAD_End[0]);/*读FLASH中最近一次事件记录结束时刻*/
            if(V_ucMode == C_OK)
            {
                if( (PF_Campare_Data(&V_ucJudgeBuffer[C_Judge_StartBuffer0], &V_ucNullJudgeBuffer[C_Judge_StartBuffer0], C_EventTimeLength) != C_Equal)
                    &&(PF_Campare_Data(&V_ucJudgeBuffer[C_Judge_TimeEndBuffer], &V_ucNullJudgeBuffer[C_Judge_StartBuffer0], C_EventTimeLength) == C_Equal) )
                {
                    return(C_Happen_EventState);
                }
                else
                {
                    return(C_End_EventState);
                }
            }
            else
            {
                return(C_Error);
            }
        }
        else
        {
            return(C_Error);
        }
    }
    else
    {
        return(C_IDError);
    }
}

/***********************************************************************************
函数原型：uchar8 Get_E_DalayTime(uchar8 EventNo)
功能描述：判断事件判断延时时间
输入参数：EventNo
输出参数：返回事件类型状态
返回参数：CC_IDError             	数据标识码错误
          	C_Happen_EventState		事件状态，有发生无恢复
        	C_End_EventState	  	事件状态，非有发生无恢复
功能说明：防止事件写FLASH错误；
调用机制：写消息时调用
备    注：
**********************************************************************************/
uchar8 SF_Get_Event_DalayTime(uchar8 EventNo)
{
	uchar8	V_ucJudgeBuffer1, V_ucMode;
	ushort16 V_usBufferLength = C_DelayTimeLength, V_usEncode;

	if( (EventNo <= C_NeutralCurrentAbnormalEventNo) && (EventNo != C_PowerAbnormalEventNo) )
	{
		if(Event_Delaytime[EventNo] != C_NULL)
		{
			V_ucMode = InF_GetData_ObjectManage(Event_Delaytime[EventNo], &V_ucJudgeBuffer1, &V_usBufferLength, &V_usEncode);/*读FLASH中最近一次事件记录结束时刻*/
			if( (EventNo == C_TotalVoltageLoseEventNo) || (EventNo == C_PowerfailEventNo) )
			{
				if(GV_ucEvent_Hstate[EventNo] != C_Happen_EventState)
				{
					V_ucMode = C_JudgeTimeError;
				}
			}
			if(V_ucMode == C_OK)
			{
				return(V_ucJudgeBuffer1);
			}
			else
			{
				return(Event_DDelaytime[EventNo]);
			}
		}
		else
		{
			return(Event_DDelaytime[EventNo]);
		}
	}
	return(C_JudgeTimeError);
}



/***********************************************************************************
函数原型：uchar8 SF_Get_TotalVoltageLose_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
功能描述：判断全失压当前状态
输入参数：V_ucEventNo（事件号），Hstate（历史状态）
输出参数：返回事件当前所处状态
返回参数C_Happen_V_ucEventState	事件状态，有发生无恢复
          C_End_EventState	  	事件状态，非有发生无恢复
功能说明：判断事件当前状态；
调用机制：事件判断函数调用
备    注：
**********************************************************************************/
uchar8 SF_Get_TotalVoltageLose_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
	uchar8	V_ucJudgeBuffer1[C_4Volage_Length], V_ucJudgeBuffer2[C_4Curr_Length];/*电流及电压buffer*/
	ushort16 V_usJudgeBufferLength1 = C_4Volage_Length, V_usJudgeBufferLength2 = C_4Curr_Length, V_usEncode;

	if(InF_GetData_ObjectManage(CLoss_Volage_Vol, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)/*读取全失压判断电压*/
	{
		return(V_ucHstate);
	}

    V_usJudgeBufferLength1 = C_4Volage_Length;      /*V0.2新增长度赋值*/
	if(InF_GetData_ObjectManage(CPhaseFF_Volage, &V_ucJudgeBuffer1[C_JudgeVolage_Buffer1], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)/*读当前电压*/
	{
		return(V_ucHstate);
	}

	if(InF_GetData_ObjectManage(CLoss_Volage_Curr, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usJudgeBufferLength2, &V_usEncode) != C_OK)/*读取全失压判断电流*/
	{
		return(V_ucHstate);
	}

    V_usJudgeBufferLength2 = C_4Curr_Length;    /*V0.2新增长度赋值*/
	if(InF_GetData_ObjectManage(CPhaseFF_Curr, &V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], &V_usJudgeBufferLength2, &V_usEncode) != C_OK)/*读当前电流, 三位小数电流*/
	{
		return(V_ucHstate);
	}

	V_ucJudgeBuffer2[C_Judge_StartBuffer2] = C_NULL;/*判断电流高两字节置0*/
    V_ucJudgeBuffer2[C_Judge_StartBuffer3] = C_NULL;

	PF_GetAbs(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], &V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], C_Curr4Bytes_Length);/*A相电流取绝对值*/
	PF_GetAbs(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer2], &V_ucJudgeBuffer2[C_JudgeCurr_Buffer2], C_Curr4Bytes_Length);/*B相电流取绝对值*/
	PF_GetAbs(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer3], &V_ucJudgeBuffer2[C_JudgeCurr_Buffer3], C_Curr4Bytes_Length);/*C相电流取绝对值*/

	if((PF_Campare_Data(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer1], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_LessThan)
		&&(PF_Campare_Data(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer2], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_LessThan)
		&&(PF_Campare_Data(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer3], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_LessThan))
	{
		if( (PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_Curr_Length) == C_GreaterThan)
            || (PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer2], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_Curr_Length) == C_GreaterThan)
            || (PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer3], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_Curr_Length) == C_GreaterThan) )
		{
            return(C_Happen_EventState);
        }
		else
		{
            return(C_End_EventState);
		}
	}
	else
	{
		return(C_End_EventState);
	}
}

/***********************************************************************************
函数原型：uchar8 SF_Get_Powerfail_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
功能描述：判断掉电当前状态
输入参数：V_ucEventNo事件号，Hstate（历史状态）
输出参数：返回事件当前所处状态
返回参数C_Happen_V_ucEventState	事件状态，有发生无恢复
          C_End_EventState	  	事件状态，非有发生无恢复
功能说明：判断事件当前状态；
调用机制：事件判断函数调用
备    注：
**********************************************************************************/
uchar8 SF_Get_Powerfail_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
	uchar8	V_ucJudgeBuffer1[C_4Volage_Length];/*电流及电压buffer*/
	ushort16 V_usJudgeBufferLength1 = C_4Volage_Length, V_usEncode;

	if(InF_GetData_ObjectManage(CLoss_Volage_Vol, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)/*读取全失压判断电压*/
	{
		return(V_ucHstate);
	}

    V_usJudgeBufferLength1 = C_4Volage_Length;      /*V0.2新增长度赋值*/
	if(InF_GetData_ObjectManage(CPhaseFF_Volage, &V_ucJudgeBuffer1[C_JudgeVolage_Buffer1], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)/*读当前电压*/
	{
		return(V_ucHstate);
	}

	if( (PF_Campare_Data(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer1], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_LessThan)
		&&(PF_Campare_Data(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer2], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_LessThan)
		&&(PF_Campare_Data(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer3], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_LessThan) )
	{
        return(C_Happen_EventState);
	}
	else
	{
		return(C_End_EventState);
	}
}

/***********************************************************************************
函数原型：uchar8 SF_Get_PeripheralEvt_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
功能描述：开表盖、开端钮盖、磁场干扰、辅助电源失电事件
输入参数：EventNo(事件号)Hstate（历史状态）
输出参数：返回事件当前所处状态
返回参数C_Happen_V_ucEventState		事件状态，有发生无恢复
          C_End_EventState	  	事件状态，非有发生无恢复
功能说明：判断事件当前状态；
调用机制：事件判断函数调用
备    注：
**********************************************************************************/
uchar8 SF_Get_PeripheralEvt_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
    uchar8 V_ucStatus = C_Error, V_ucType;
	uchar8 V_ucHpStatus, V_ucEndStatus;

    if(V_ucEventNo == C_ACPowerFailEventNo)/*辅助电源失电*/
    {
        V_ucType = C_CheckAuPower;
		V_ucHpStatus = C_Valid;
		V_ucEndStatus = C_Invalid;
    }
    else if(V_ucEventNo == C_OpenMeterCoverEventNo)/*开表盖*/
    {
        V_ucType = C_KeyOpenCover;
		V_ucHpStatus = C_Invalid;
		V_ucEndStatus = C_Valid;
    }
    else if(V_ucEventNo == C_OpenTerminalCoverEventNo)/*开端钮盖*/
    {
        V_ucType = C_KeyOpenTerminal;
		V_ucHpStatus = C_Invalid;
		V_ucEndStatus = C_Valid;
    }
    else if(V_ucEventNo == C_MagneticCheckEventNo)/*恒定磁场干扰*/
    {
        V_ucType = C_Magnetic;
		V_ucHpStatus = C_Valid;
		V_ucEndStatus = C_Invalid;
    }
    else
    {
        return(V_ucHstate);
    }
	V_ucStatus = InF_GetPeripheralStatus(V_ucType);

    if(V_ucStatus == V_ucHpStatus)
	{
		return(C_Happen_EventState);
	}
	else if(V_ucStatus == V_ucEndStatus)
	{
        return(C_End_EventState);
    }
    else
    {
        return(V_ucHstate);
    }
}

/***********************************************************************************
函数原型：uchar8 Get_OverForwardActive_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
功能描述：正向有功需量超限
输入参数：EventNo(事件号) Hstate（历史状态）
输出参数：返回事件当前所处状态
返回参数C_Happen_V_ucEventState		事件状态，有发生无恢复
          C_End_EventState	  	事件状态，非有发生无恢复
          C_Close_EventState		事件状态，关闭
功能说明：判断事件当前状态；
调用机制：事件判断函数调用
备    注：
**********************************************************************************/
uchar8 SF_Get_OverActiveDemand_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
 	uchar8	V_ucJudgeBuffer1[C_Demand_Length], V_ucJudgeBuffer2[C_Demand_Length], V_ucJudgeBuffer3[C_Demand_Length] = {0};
 	ushort16 V_usBufferLength1 = C_Demand_Length, V_usEncode;
    uchar8  V_ucTemp = C_End_EventState, V_ucSign;

    if(V_ucEventNo == C_OverForwardActiveEventNo)
    {
        if(InF_GetData_ObjectManage(CPosAcDemandOv_De_LowLim, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) != C_OK)/*有功需量超限事件需量触发下限, 为0，返回关闭*/
        {
            return(V_ucHstate);
        }
    }
    else if(V_ucEventNo == C_OverReverseActiveEventNo)
    {
        if(InF_GetData_ObjectManage(CRevAcDemandOv_De_LowLim, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) != C_OK)/*有功需量超限事件需量触发下限, 为0，返回关闭*/
        {
            return(V_ucHstate);
        }
    }
    else
    {
        return(V_ucHstate);
    }
  	if(PF_Campare_Data(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_Demand_Length) == C_Equal)
 	{
 		return(C_Close_EventState);
 	}
    V_usBufferLength1 = C_Demand_Length;
 	if(InF_GetData_ObjectManage(CCurr_AcDemand, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) != C_OK)	/*当前有功需量*/
 	{
 		return(V_ucHstate);
 	}
    V_ucSign = PF_GetAbs(V_ucJudgeBuffer2, V_ucJudgeBuffer2, C_Curr4Bytes_Length);/*获取当前有功功率方向, 并取绝对值*/

 	if(PF_Campare_Data(&V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Demand_Length) == C_GreaterThan)
    {
        if(V_ucEventNo == C_OverForwardActiveEventNo)
        {
			if(V_ucSign != C_Minus)/*有功功率方向为正向，且大于阀值*/
            {
                V_ucTemp = C_Happen_EventState;
            }
        }
        else if(V_ucEventNo == C_OverReverseActiveEventNo)
        {
			if(V_ucSign == C_Minus)/*有功功率方向为反向，且大于阀值*/
            {
                V_ucTemp = C_Happen_EventState;
            }
        }
        else
        {
            return(V_ucHstate);
        }
    }
	return V_ucTemp;
}


/***********************************************************************************
函数原型：uchar8 SF_Get_OverIdleDemand_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
功能描述：1-4象限无功需量超限
输入参数：EventNo(事件号) Hstate（历史状态）
输出参数：返回事件当前所处状态
返回参数C_Happen_V_ucEventState		事件状态，有发生无恢复
          C_End_EventState	  	事件状态，非有发生无恢复
          C_Close_EventState		事件状态，关闭
功能说明：判断事件当前状态；
调用机制：事件判断函数调用
备    注：
**********************************************************************************/
uchar8 SF_Get_OverIdleDemand_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
 	uchar8	V_ucJudgeBuffer1[C_Demand_Length], V_ucJudgeBuffer2[C_Demand_Length], V_ucJudgeBuffer3[C_Demand_Length]={0};
 	uchar8	V_ucJudgeBuffer4[C_Demand_Length];				/*当前有功需量*/
 	ushort16 V_usBufferLength1 = C_Demand_Length, V_usEncode;
    uchar8  V_ucTemp = C_End_EventState, V_ucSign[2];

 	if(InF_GetData_ObjectManage(CReDemandOv_De_LowLim, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) != C_OK)/*无功需量超限事件需量触发下限, 为0，返回关闭*/
 	{
 		return(V_ucHstate);
 	}
 	if(PF_Campare_Data(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_Demand_Length)==C_Equal)
 	{
 		return(C_Close_EventState);
 	}
    V_usBufferLength1 = C_Demand_Length; /*V0.2新增长度赋值*/
 	if(InF_GetData_ObjectManage(CCurr_ReDemand, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) != C_OK)	/*无功需量*/
 	{
 		return(V_ucHstate);
 	}
    V_usBufferLength1 = C_Demand_Length;
 	if(InF_GetData_ObjectManage(CCurr_AcDemand, &V_ucJudgeBuffer4[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) != C_OK)	/*当前有功需量*/
 	{
 		return(V_ucHstate);
 	}
    V_ucSign[0] = PF_GetAbs(V_ucJudgeBuffer2, V_ucJudgeBuffer2, C_Curr4Bytes_Length);/*获取当前无功功率方向, 并取绝对值*/
    V_ucSign[1] = PF_GetAbs(V_ucJudgeBuffer4, V_ucJudgeBuffer4, C_Curr4Bytes_Length);/*获取当前有功功率方向, 并取绝对值*/

    if(PF_Campare_Data(&V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Demand_Length) == C_GreaterThan)
    {
        if(V_ucEventNo == C_1OverIdleDemandEventNo)
        {
            if((V_ucSign[0] != C_Minus)/*无功功率方向为正向，且大于阀值*/
                &&(V_ucSign[1] != C_Minus))/*有功功率方向为正向*/
            {
                V_ucTemp = C_Happen_EventState;
            }
        }
        else if(V_ucEventNo == C_2OverIdleDemandEventNo)
        {
            if((V_ucSign[0] != C_Minus)/*无功功率方向为正向，且大于阀值*/
                &&(V_ucSign[1] == C_Minus))/*有功功率方向为反向*/
            {
                V_ucTemp = C_Happen_EventState;
            }
        }
        else if(V_ucEventNo == C_3OverIdleDemandEventNo)
        {
            if((V_ucSign[0] == C_Minus)/*无功功率方向为反向，且大于阀值*/
                &&(V_ucSign[1] == C_Minus))/*有功功率方向为反向*/
            {
                V_ucTemp = C_Happen_EventState;
            }
        }
        else if(V_ucEventNo == C_4OverIdleDemandEventNo)
        {
            if((V_ucSign[0] == C_Minus)/*无功功率方向为反向，且大于阀值*/
                &&(V_ucSign[1] != C_Minus))/*有功功率方向为正向*/
            {
                V_ucTemp = C_Happen_EventState;
            }
        }
        else
        {
            return(V_ucHstate);
        }
    }
    return V_ucTemp;
}

/***********************************************************************************
函数原型：uchar8 SF_Get_lossvoltage_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
功能描述：失压
输入参数：EventNo事件号，Hstate（历史状态）
输出参数：返回事件当前所处状态
返回参数C_Happen_V_ucEventState		事件状态，有发生无恢复
          C_End_EventState	  		事件状态，非有发生无恢复
          C_Close_EventState		事件状态，关闭
功能说明：判断事件当前状态；
调用机制：事件判断函数调用
备    注：
**********************************************************************************/
uchar8 SF_Get_lossvoltage_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
	uchar8	V_ucJudgeBuffer1[C_Volage_Length], V_ucJudgeBuffer2[C_Volage_Length], V_ucJudgeBuffer3[C_Curr_Length];/*三个限值*/
	uchar8	V_ucJudgeBuffer4[C_Volage_Length], V_ucJudgeBuffer5[C_Curr_Length], V_ucJudgeBuffer6[C_Volage_Length] = {0};/*电压、电流、判断条件为零*/
	ushort16 V_usJudgeBufferLength1 = C_Volage_Length, V_usJudgeBufferLength2 = C_Curr_Length, V_usEncode;
	ulong32	V_ulVolage, V_ulCurr;

	if(GV_ucEvent_Hstate[C_TotalVoltageLoseEventNo] == C_Happen_EventState)/*全失压发生，失压结束*/
	{
		return(C_Close_EventState);
	}
	switch(V_ucEventNo)
	{
		case	C_AlossvoltageEventNo:
				V_ulVolage = CPhaseA_Volage;
				V_ulCurr = CPhaseA_Curr_4Dig;
				break;
		case	C_BlossvoltageEventNo:
				V_ulVolage = CPhaseB_Volage;
				V_ulCurr = CPhaseB_Curr_4Dig;
				break;
		case	C_ClossvoltageEventNo:
				V_ulVolage = CPhaseC_Volage;
				V_ulCurr = CPhaseC_Curr_4Dig;
				break;
		default:
				return(V_ucHstate);
	}
	if(InF_GetData_ObjectManage(CLossVolage_Vol_UpLim, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)/*失压事件电压触发上限*/
	{
		return(V_ucHstate);
	}
	if(PF_Campare_Data(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer6[C_Judge_StartBuffer0], C_Volage_Length) == C_Equal)
	{
		return(C_Close_EventState);
	}
    V_usJudgeBufferLength1 = C_Volage_Length;
	if(InF_GetData_ObjectManage(CLossVolage_Vol_LowLim, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)/*失压事件电压恢复下限*/
	{
		return(V_ucHstate);
	}
	if(InF_GetData_ObjectManage(CLossVolage_Curr_LowLim, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_usJudgeBufferLength2, &V_usEncode) != C_OK)/*失压事件电流触发下限*/
	{
		return(V_ucHstate);
	}
    V_usJudgeBufferLength1 = C_Volage_Length;
	if(InF_GetData_ObjectManage(V_ulVolage, &V_ucJudgeBuffer4[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
    V_usJudgeBufferLength2 = C_Curr_Length; /*V0.2新增长度赋值*/
	if(InF_GetData_ObjectManage(V_ulCurr, &V_ucJudgeBuffer5[C_Judge_StartBuffer0], &V_usJudgeBufferLength2, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
    PF_GetAbs(V_ucJudgeBuffer5, V_ucJudgeBuffer5, C_Curr4Bytes_Length);/*取电流绝对值*/

	if( (PF_Campare_Data(&V_ucJudgeBuffer4[C_Judge_StartBuffer0], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_LessThan)
		&&(PF_Campare_Data(&V_ucJudgeBuffer5[C_Judge_StartBuffer0], &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_Curr4Dig_Length) == C_GreaterThan) )
	{
		return(C_Happen_EventState);
	}
	else
	{
		if(PF_Campare_Data(&V_ucJudgeBuffer4[C_Judge_StartBuffer0], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_Volage_Length) == C_GreaterThan)
		{
			return(C_End_EventState);
		}
		else
		{
			return(V_ucHstate);
		}
	}
}

/***********************************************************************************
函数原型：uchar8 SF_Get_Lessvoltage_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
功能描述：欠压
输入参数：EventNo事件号，Hstate（历史状态）
输出参数：返回事件当前所处状态
返回参数C_Happen_V_ucEventState		事件状态，有发生无恢复
          C_End_EventState	  		事件状态，非有发生无恢复
          C_Close_EventState		事件状态，关闭
功能说明：判断事件当前状态；
调用机制：事件判断函数调用
备    注：
**********************************************************************************/
uchar8 SF_Get_Lessvoltage_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
	uchar8	V_ucJudgeBuffer1[C_Volage_Length], V_ucJudgeBuffer2[C_Volage_Length], V_ucJudgeBuffer3[C_Volage_Length] = {0};
	ushort16 V_usJudgeBufferLength = C_Volage_Length, V_usEncode;
	ulong32	V_ulVolage;
	switch(V_ucEventNo)
	{
		case	C_ALessvoltageEventNo:
				V_ulVolage = CPhaseA_Volage;
				break;
		case	C_BLessvoltageEventNo:
				V_ulVolage = CPhaseB_Volage;
				break;
		case	C_CLessvoltageEventNo:
				V_ulVolage = CPhaseC_Volage;
				break;
		default:
				return(V_ucHstate);
	}
	if(InF_GetData_ObjectManage(CLowVolage_Vol_UpLim, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
    V_usJudgeBufferLength = C_Volage_Length;
	if(InF_GetData_ObjectManage(V_ulVolage, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usJudgeBufferLength, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
	if(PF_Campare_Data(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_Volage_Length) == C_Equal)
	{
		return(C_Close_EventState);
	}
	else
	{
		if(PF_Campare_Data(&V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_LessThan)
		{
			return(C_Happen_EventState);
		}
		else
		{
			return(C_End_EventState);
		}
	}
}

/***********************************************************************************
函数原型：uchar8 SF_Get_Overvoltage_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
功能描述: 过压
输入参数：EventNo（事件号）、Hstate（历史状态）
输出参数：返回事件当前所处状态
返回参数C_Happen_V_ucEventState		事件状态，有发生无恢复
          C_End_EventState	  		事件状态，非有发生无恢复
          C_Close_EventState		事件状态，关闭
功能说明：判断事件当前状态；
调用机制：事件判断函数调用
备    注：
**********************************************************************************/
uchar8 SF_Get_Overvoltage_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
	uchar8	V_ucJudgeBuffer1[C_Volage_Length], V_ucJudgeBuffer2[C_Volage_Length], V_ucJudgeBuffer3[C_Volage_Length] = {0};
	ushort16 V_usJudgeBufferLength = C_Volage_Length, V_usEncode;
	ulong32	V_ulVolage;
	switch(V_ucEventNo)
	{
		case	C_AOvervoltageEventNo:
				V_ulVolage = CPhaseA_Volage;
				break;
		case	C_BOvervoltageEventNo:
				V_ulVolage = CPhaseB_Volage;
				break;
		case	C_COvervoltageEventNo:
				V_ulVolage = CPhaseC_Volage;
				break;
		default:
				return(V_ucHstate);
	}
	if(GV_ucEvent_Hstate[C_PowerfailEventNo] == C_Happen_EventState)	/*掉电发生，事件结束*/
	{
		return(C_Close_EventState);
	}
	if(InF_GetData_ObjectManage(COverVolage_Vol_LowLim, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
    V_usJudgeBufferLength = C_Volage_Length;
	if(InF_GetData_ObjectManage(V_ulVolage, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usJudgeBufferLength, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
	if(PF_Campare_Data(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_Volage_Length) == C_Equal)
	{
		return(C_Close_EventState);
	}
	else
	{
		if(PF_Campare_Data(&V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_GreaterThan)
		{
			return(C_Happen_EventState);
		}
		else
		{
			return(C_End_EventState);
		}
	}
}

/***********************************************************************************
函数原型：uchar8 SF_Get_Lossphase_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
功能描述: 断相
输入参数：EventNo（事件号）、Hstate（历史状态）
输出参数：返回事件当前所处状态
返回参数C_Happen_V_ucEventState		事件状态，有发生无恢复
          C_End_EventState	  		事件状态，非有发生无恢复
          C_Close_EventState		事件状态，关闭
功能说明：判断事件当前状态；
调用机制：事件判断函数调用
备    注：
**********************************************************************************/
uchar8 SF_Get_Lossphase_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
 	uchar8	V_ucJudgeBuffer1[C_Volage_Length], V_ucJudgeBuffer2[C_Curr_Length];/*两个限值*/
 	uchar8	V_ucJudgeBuffer3[C_Volage_Length], V_ucJudgeBuffer4[C_Curr_Length], V_ucJudgeBuffer5[C_Volage_Length] = {0};/*电压、电流、判断条件为零*/
 	ushort16 V_usJudgeBufferLength1 = C_Volage_Length, V_usJudgeBufferLength2 = C_Curr_Length, V_usEncode;
 	ulong32	V_ulVolage, V_ulCurr;

	if(GV_ucEvent_Hstate[C_PowerfailEventNo] == C_Happen_EventState)/*掉电发生，事件结束*/
	{
		return(C_Close_EventState);
	}
	switch(V_ucEventNo)
	{
		case	C_ALossphaseEventNo:
				V_ulVolage = CPhaseA_Volage;
				V_ulCurr = CPhaseA_Curr_4Dig;
				break;
		case	C_BLossphaseEventNo:
				V_ulVolage = CPhaseB_Volage;
				V_ulCurr = CPhaseB_Curr_4Dig;
				break;
		case	C_CLossphaseEventNo:
				V_ulVolage = CPhaseC_Volage;
				V_ulCurr = CPhaseC_Curr_4Dig;
				break;
		default:
				return(V_ucHstate);
	}
	if(InF_GetData_ObjectManage(CBreakVol_Vol_UpLim, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)	/*断相事件电压触发上限*/
	{
		return(V_ucHstate);
	}
	if(InF_GetData_ObjectManage(CBreakVol_Curr_UpLim, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usJudgeBufferLength2, &V_usEncode) != C_OK)	/*断相事件电流触发上限*/
	{
		return(V_ucHstate);
	}
    V_usJudgeBufferLength1 = C_Volage_Length;
 	if(InF_GetData_ObjectManage(V_ulVolage, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
    V_usJudgeBufferLength2 = C_Curr_Length; /*V0.2新增长度赋值*/
 	if(InF_GetData_ObjectManage(V_ulCurr, &V_ucJudgeBuffer4[C_Judge_StartBuffer0], &V_usJudgeBufferLength2, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
	PF_GetAbs(V_ucJudgeBuffer4, V_ucJudgeBuffer4, C_Curr4Bytes_Length);/*电流取绝对值*/

 	if(PF_Campare_Data(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer5[C_Judge_StartBuffer0], C_Volage_Length) == C_Equal)
	{
		return(C_Close_EventState);
	}
	else
	{
		if( (PF_Campare_Data(&V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_LessThan)
			&&(PF_Campare_Data(&V_ucJudgeBuffer4[C_Judge_StartBuffer0], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_JudgeCurr_Length) == C_LessThan) )
		{
			return(C_Happen_EventState);
		}
		else
		{
			return(C_End_EventState);
		}
	}
}
/***********************************************************************************
函数原型：uchar8 SF_Get_ReversePhaseFlag(uchar8 *pV_Buffer)
功能描述: 电压逆相序方向
输入参数：pV_Buffer：电表型号，C_3P4W/C_3P3W
输出参数：无
返回参数电压相序状态
功能说明：
调用机制：事件判断函数调用
备    注：
**********************************************************************************/
uchar8 SF_Get_ReversePhaseVoltageFlag(uchar8 *pV_Buffer)
{
	uchar8	V_ucJudgeBuffer1[CLVolFF_Phase];												/*电能表相角*/
	uchar8	V_ucJudgeBuffer2[CLPhaseA_Volage];
	ushort16 V_usJudgeBufferLength1 = CLVolA_Phase, V_usEncode;

	InF_GetData_ObjectManage(CVolA_Phase, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode);		/*分相电压相角*/

    V_usJudgeBufferLength1 = CLVolB_Phase;
	InF_GetData_ObjectManage(CVolB_Phase, &V_ucJudgeBuffer1[C_Judge_StartBuffer2], &V_usJudgeBufferLength1, &V_usEncode);

    V_usJudgeBufferLength1 = CLVolC_Phase;
	InF_GetData_ObjectManage(CVolC_Phase, &V_ucJudgeBuffer1[C_Judge_StartBuffer4], &V_usJudgeBufferLength1, &V_usEncode);

    V_usJudgeBufferLength1 = CLPhaseA_Volage;
	InF_GetData_ObjectManage(CPhaseA_Volage, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode);

	if((V_ucJudgeBuffer2[C_Judge_StartBuffer0]==C_NULL)&&(V_ucJudgeBuffer2[C_Judge_StartBuffer1] == C_NULL))
	{
		return(C_Error);
	}
	if(*pV_Buffer == C_3P4W)
	{
		if(PF_Campare_Data(&V_ucJudgeBuffer1[C_Judge_StartBuffer4], &V_ucJudgeBuffer1[C_Judge_StartBuffer2], C_PhaseAngle) == C_GreaterThan)
		{
			return(C_Positivephase);/*如果C相角>B相角，返回正相序*/
		}
		else
		{
			return(C_Reversephase);
		}
	}
	else
	{
		if(*pV_Buffer == C_3P3W)
		{
			if((PF_Campare_Data(&V_ucJudgeBuffer1[C_Judge_StartBuffer4], (uchar8 *)C_uc3P3WVotageAngle1, C_PhaseAngle) == C_GreaterThan)
			&&(PF_Campare_Data(&V_ucJudgeBuffer1[C_Judge_StartBuffer4], (uchar8 *)C_uc3P3WVotageAngle2, C_PhaseAngle) == C_LessThan))
			{
				return(C_Reversephase);/*如果C相角在30度和115度以内，返回逆相序*/
			}
			else
			{
				return(C_Positivephase);
			}
		}
		else
		{
			return(C_Error);
		}

	}
}
/***********************************************************************************
函数原型：uchar8 SF_Get_ReverseCurrentFlag(uchar8 *pV_Buffer)
功能描述: 电流逆相序方向
输入参数：pV_Buffer：电表型号，C_3P4W/C_3P3W
输出参数：无
返回参数电流相序状态
功能说明：
调用机制：事件判断函数调用
备    注：
**********************************************************************************/
uchar8 SF_Get_ReverseCurrentFlag(uchar8 *pV_Buffer)
{
	uchar8	V_ucJudgeBuffer1[C_Judge_20BufferLength];												/*电能表相角*/
	uchar8	V_ucJudgeBuffer2[C_Judge_20BufferLength];
	ushort16 V_usJudgeBufferLength1 = C_Judge_20BufferLength, V_usEncode;

	InF_GetData_ObjectManage(CCurrA_Phase, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode);		/*分相电流相角*/

    V_usJudgeBufferLength1 = CLCurrB_Phase;
	InF_GetData_ObjectManage(CCurrB_Phase, &V_ucJudgeBuffer1[C_Judge_StartBuffer2], &V_usJudgeBufferLength1, &V_usEncode);

    V_usJudgeBufferLength1 = CLCurrC_Phase;
	InF_GetData_ObjectManage(CCurrC_Phase, &V_ucJudgeBuffer1[C_Judge_StartBuffer4], &V_usJudgeBufferLength1, &V_usEncode);

    V_usJudgeBufferLength1 = C_Judge_20BufferLength;	/*V0.2新增长度赋值*/
	InF_GetData_ObjectManage(CPhaseA_Curr, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode);

	if( (V_ucJudgeBuffer2[C_Judge_StartBuffer0] == C_NULL)
        && (V_ucJudgeBuffer2[C_Judge_StartBuffer1] == C_NULL)
        && (V_ucJudgeBuffer2[C_Judge_StartBuffer2] == C_NULL) )
	{
		return(C_Error);
	}
	if(*pV_Buffer == C_3P4W)
	{		/*（B相电流角-A相电流相角）<（c相电流角-A相电流相角）*/
		SF_HEXDECBytes(&V_ucJudgeBuffer1[C_Judge_StartBuffer2], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer1[C_Judge_StartBuffer2], C_PhaseAngle);/*B相电流相对相角*/
		SF_HEXDECBytes(&V_ucJudgeBuffer1[C_Judge_StartBuffer4], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer1[C_Judge_StartBuffer4], C_PhaseAngle);/*C相电流相对相角*/

        if(PF_Campare_Data(&V_ucJudgeBuffer1[C_Judge_StartBuffer4], &V_ucJudgeBuffer1[C_Judge_StartBuffer2], C_PhaseAngle) == C_GreaterThan)
		{
			return(C_Positivephase);/*如果C相角>B相角，返回正相序*/
		}
		else
		{
			return(C_Reversephase);
		}
	}
	else
	{
		if(*pV_Buffer == C_3P3W)
		{
	 		if( (PF_Campare_Data(&V_ucJudgeBuffer1[C_Judge_StartBuffer4], (uchar8 *)C_uc3P3WCurrentAngle1, C_PhaseAngle) == C_GreaterThan)
                &&(PF_Campare_Data(&V_ucJudgeBuffer1[C_Judge_StartBuffer4], (uchar8 *)C_uc3P3WCurrentAngle2, C_PhaseAngle) == C_LessThan) )
	 		{
	 			return(C_Reversephase);/*如果C相角在90度和150度以内，返回逆相序*/
	 		}
	 		else
	 		{
	 			return(C_Positivephase);
	 		}
		}
		else
		{
			return(C_Error);
		}

	}
}
/***********************************************************************************
函数原型：uchar8 SF_Get_ReversephaseVoltage_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
功能描述: 电压逆相序
输入参数：EventNo（事件号）、Hstate（历史状态）
输出参数：返回事件当前所处状态
返回参数C_Happen_V_ucEventState		事件状态，有发生无恢复
          C_End_EventState	  		事件状态，非有发生无恢复
          C_Close_EventState		事件状态，关闭
功能说明：判断事件当前状态；
调用机制：事件判断函数调用
备    注：
**********************************************************************************/
uchar8 SF_Get_ReversephaseVoltage_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
 	uchar8	V_ucJudgeBuffer1[C_4Volage_Length];											/*全失压判断电压，三相电压*/
	uchar8	V_ucJudgeBuffer2[C_Length_Two];												/*电能表相线类型*/
	ushort16 V_usLineLength = C_Length_One, V_usJudgeBufferLength1 = C_4Volage_Length, V_usEncode;
	uchar8	V_ucReverseFlag;

	if(InF_GetData_ObjectManage(CLoss_Volage_Vol, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)	/*全失压判断电压*/
	{
		return(V_ucHstate);
	}
    V_usJudgeBufferLength1 = C_4Volage_Length;/*V0.2新增长度赋值*/
	if(InF_GetData_ObjectManage(CPhaseFF_Volage, &V_ucJudgeBuffer1[C_JudgeVolage_Buffer1], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)	/*三相电压*/
	{
		return(V_ucHstate);
	}
	if(InF_GetData_ObjectManage(CLine_Type, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usLineLength, &V_usEncode) != C_OK)	/*相线类型*/
	{
		return(V_ucHstate);
	}
	V_ucReverseFlag = SF_Get_ReversePhaseVoltageFlag(&V_ucJudgeBuffer2[C_Judge_StartBuffer0]);/*获取电压逆相序标志*/

    if( (V_ucReverseFlag == C_Reversephase)
        &&( ( (PF_Campare_Data(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer1], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_GreaterThan)
                && (PF_Campare_Data(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer2], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_GreaterThan)
                && (PF_Campare_Data(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer3], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_GreaterThan)
                && (V_ucJudgeBuffer2[C_Judge_StartBuffer0] == C_3P4W) )
            ||( (PF_Campare_Data(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer1], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_GreaterThan)
                && (PF_Campare_Data(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer3], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_GreaterThan)
                && (V_ucJudgeBuffer2[C_Judge_StartBuffer0] == C_3P3W) ) ) )
	{
		return(C_Happen_EventState);
	}
	else
	{
        return(C_End_EventState);
	}
}
/***********************************************************************************
函数原型：uchar8 SF_Get_ReversephaseCurrent_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
功能描述: 电流逆相序
输入参数：EventNo（事件号）、Hstate（历史状态）
输出参数：返回事件当前所处状态
返回参数C_Happen_V_ucEventState		事件状态，有发生无恢复
          C_End_EventState	  		事件状态，非有发生无恢复
          C_Close_EventState		事件状态，关闭
功能说明：判断事件当前状态；
调用机制：事件判断函数调用
备    注：
**********************************************************************************/
uchar8 SF_Get_ReversephaseCurrent_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
 	uchar8	V_ucJudgeBuffer1[C_4Volage_Length];											/*全失压判断电压，三相电压*/
	uchar8	V_ucJudgeBuffer2[C_Length_Two];												/*电能表相线类型*/
 	uchar8	V_ucJudgeBuffer3[C_4Curr4Dig_Length];												/*全失压判断电流，三相电流*/
	ushort16 V_usJudgeBufferLength1 = C_4Volage_Length, V_usVolageLength = C_Volage_Length;
	ushort16 V_usJudgeBufferLength3 = C_4Curr4Dig_Length, V_usEncode;
	uchar8	V_ucReverseFlag;

	if(InF_GetData_ObjectManage(CLoss_Volage_Vol, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)	/*全失压判断电压*/
	{
		return(V_ucHstate);
	}
    V_usJudgeBufferLength1 = C_4Volage_Length;/*V0.2新增长度赋值*/
	if(InF_GetData_ObjectManage(CPhaseFF_Volage, &V_ucJudgeBuffer1[C_JudgeVolage_Buffer1], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)	/*三相电压*/
	{
		return(V_ucHstate);
	}
	if(InF_GetData_ObjectManage(CLine_Type, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usVolageLength, &V_usEncode) != C_OK)	/*相线类型*/
	{
		return(V_ucHstate);
	}
	if(InF_GetData_ObjectManage(CLoss_Volage_Curr, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_usJudgeBufferLength3, &V_usEncode) != C_OK)	/*全失压判断电流*/
	{
		return(V_ucHstate);
	}
    V_usJudgeBufferLength3 = C_4Curr4Dig_Length;/*V0.2新增长度赋值*/
	if(InF_GetData_ObjectManage(CPhaseFF_Curr, &V_ucJudgeBuffer3[C_JudgeCurr_Buffer1], &V_usJudgeBufferLength3, &V_usEncode) != C_OK)	/*三相电流*/
	{
		return(V_ucHstate);
	}
    V_ucJudgeBuffer3[C_Judge_StartBuffer2] = C_NULL;/*判断电流高两字节置0*/
    V_ucJudgeBuffer3[C_Judge_StartBuffer3] = C_NULL;

    PF_GetAbs(&V_ucJudgeBuffer3[C_JudgeCurr_Buffer1], &V_ucJudgeBuffer3[C_JudgeCurr_Buffer1], C_Curr4Bytes_Length);/*A相电流取绝对值*/
	PF_GetAbs(&V_ucJudgeBuffer3[C_JudgeCurr_Buffer2], &V_ucJudgeBuffer3[C_JudgeCurr_Buffer2], C_Curr4Bytes_Length);/*B相电流取绝对值*/
	PF_GetAbs(&V_ucJudgeBuffer3[C_JudgeCurr_Buffer3], &V_ucJudgeBuffer3[C_JudgeCurr_Buffer3], C_Curr4Bytes_Length);/*C相电流取绝对值*/

	V_ucReverseFlag = SF_Get_ReverseCurrentFlag(&V_ucJudgeBuffer2[C_Judge_StartBuffer0]);/*获取电流逆相序标志*/
	if( (V_ucReverseFlag==C_Reversephase)
        && ( ( (PF_Campare_Data(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer1], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length)==C_GreaterThan)
                && (PF_Campare_Data(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer2], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length)==C_GreaterThan)
                && (PF_Campare_Data(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer3], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length)==C_GreaterThan)
                && (V_ucJudgeBuffer2[C_Judge_StartBuffer0]==C_3P4W) )
            || ( (PF_Campare_Data(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer1], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length)==C_GreaterThan)
                && (PF_Campare_Data(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer3], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length)==C_GreaterThan)
                && (V_ucJudgeBuffer2[C_Judge_StartBuffer0]==C_3P3W) ) )
        &&( ( ((PF_Campare_Data(&V_ucJudgeBuffer3[C_JudgeCurr_Buffer1], &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_Curr_Length)==C_GreaterThan)
                && (PF_Campare_Data(&V_ucJudgeBuffer3[C_JudgeCurr_Buffer2], &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_Curr_Length)==C_GreaterThan)
                && (PF_Campare_Data(&V_ucJudgeBuffer3[C_JudgeCurr_Buffer3], &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_Curr_Length)==C_GreaterThan))
                && (V_ucJudgeBuffer2[C_Judge_StartBuffer0]==C_3P4W) )
            || ( ( (PF_Campare_Data(&V_ucJudgeBuffer3[C_JudgeCurr_Buffer1], &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_Curr_Length)==C_GreaterThan)
                && (PF_Campare_Data(&V_ucJudgeBuffer3[C_JudgeCurr_Buffer3], &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_Curr_Length)==C_GreaterThan))
        && (V_ucJudgeBuffer2[C_Judge_StartBuffer0]==C_3P3W) ) ) )
	{
		return(C_Happen_EventState);
	}
	else
	{
        return(C_End_EventState);
	}
}
/*******************************************************************************
函数原型：uchar8 SF_Get_UnbalanceRate_RealTime( uchar8 V_ucEventNo, uchar8 *V_JudgeUnbanlance )
功能描述：获取当前不平衡率
输入参数：EventNo（事件号）、V_JudgeUnbanlance：返回当前不平衡率缓存
输出参数：V_JudgeUnbanlance：返回当前不平衡率
返回参数无
功能说明：判断事件当前状态；
调用机制：事件判断函数调用
备    注：
*******************************************************************************/
void SF_Get_UnbalanceRate_RealTime( uchar8 V_ucEventNo, uchar8 *V_JudgeUnbanlance )
{
 	uchar8  V_ucJudgeBuffer1[C_Judge_20BufferLength], V_ucJudgeBuffer2[3]={0};		/*电压不平衡率判断阀值，电压不平衡率*/
	uchar8	V_ucUmax[C_Curr_Length], V_ucUmin[C_Curr_Length];						/*最大电压、最小电压, 当前不平衡率*/
    ulong32	V_ulDivisor = 0, V_ulDividend = 0, V_ulQuotient = 0;									/*除数、被除数、商*/
	ushort16 V_usJudgeBufferLength1 = C_Judge_20BufferLength, V_usEncode;
	ulong32	V_ulDataCode;
	uchar8	V_ucRealDatabuffer1, V_ucRealDatabuffer2, V_ucRealDatabuffer3, V_ucDatalength;
	
    memset(V_JudgeUnbanlance, 0, C_Unbalance_Length);
	
	switch( V_ucEventNo )
	{
		case C_UnbanlanceVoltageEventNo:
		{
			V_ulDataCode = CPhaseFF_Volage;
			V_ucRealDatabuffer1 = C_JudgeVolage_Buffer1;
			V_ucRealDatabuffer2 = C_JudgeVolage_Buffer2;
			V_ucRealDatabuffer3 = C_JudgeVolage_Buffer3;
			V_ucDatalength = C_Volage_Length;
		}break;
		case C_UnbanlanceCurrentEventNo:
		case C_SUnbanlanceCurrentEventNo:
		{
			V_ulDataCode = CPhaseFF_Curr;
			V_ucRealDatabuffer1 = C_JudgeCurr_Buffer1;
			V_ucRealDatabuffer2 = C_JudgeCurr_Buffer2;
			V_ucRealDatabuffer3 = C_JudgeCurr_Buffer3;
			V_ucDatalength = C_Curr_Length;
		}break;
		default:
			return;
    }

	if( InF_GetData_ObjectManage( V_ulDataCode, &V_ucJudgeBuffer1[V_ucRealDatabuffer1], &V_usJudgeBufferLength1 , &V_usEncode) != C_OK )	/*三相电压/电流*/
	{
		return;
	}
	V_usJudgeBufferLength1 = CLLine_Type;
	if( InF_GetData_ObjectManage( CLine_Type, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength1 , &V_usEncode) != C_OK )		/*相线类型*/
	{
		return;
	}

	if( V_ucEventNo != C_UnbanlanceVoltageEventNo )
	{
        PF_GetAbs(&V_ucJudgeBuffer1[C_JudgeCurr_Buffer1], &V_ucJudgeBuffer1[C_JudgeCurr_Buffer1], C_Curr4Bytes_Length);/*A相电流取绝对值*/
        PF_GetAbs(&V_ucJudgeBuffer1[C_JudgeCurr_Buffer2], &V_ucJudgeBuffer1[C_JudgeCurr_Buffer2], C_Curr4Bytes_Length);/*B相电流取绝对值*/
        PF_GetAbs(&V_ucJudgeBuffer1[C_JudgeCurr_Buffer3], &V_ucJudgeBuffer1[C_JudgeCurr_Buffer3], C_Curr4Bytes_Length);/*C相电流取绝对值*/
	}

	if( PF_Campare_Data( &V_ucJudgeBuffer1[V_ucRealDatabuffer1], &V_ucJudgeBuffer1[V_ucRealDatabuffer3], V_ucDatalength ) == C_GreaterThan )		/*A/C比较，大的放V_Umax，小的放V_Umin*/
	{
		PF_CopyDataBytes(&V_ucJudgeBuffer1[V_ucRealDatabuffer1], &V_ucUmax[C_Judge_StartBuffer0], V_ucDatalength);
		PF_CopyDataBytes(&V_ucJudgeBuffer1[V_ucRealDatabuffer3], &V_ucUmin[C_Judge_StartBuffer0], V_ucDatalength);
	}
    else
    {
        PF_CopyDataBytes(&V_ucJudgeBuffer1[V_ucRealDatabuffer3], &V_ucUmax[C_Judge_StartBuffer0], V_ucDatalength);
        PF_CopyDataBytes(&V_ucJudgeBuffer1[V_ucRealDatabuffer1], &V_ucUmin[C_Judge_StartBuffer0], V_ucDatalength);
    }
    if(V_ucJudgeBuffer1[C_Judge_StartBuffer0]==C_3P4W)																				/*三相四线*/
    {
        if(PF_Campare_Data(&V_ucJudgeBuffer1[V_ucRealDatabuffer2], &V_ucUmax[C_Judge_StartBuffer0], V_ucDatalength) == C_GreaterThan)	/*B比V_Umax大，放V_Umax；比V_Umin小，放V_Umin*/
        {
            PF_CopyDataBytes(&V_ucJudgeBuffer1[V_ucRealDatabuffer2], &V_ucUmax[C_Judge_StartBuffer0], V_ucDatalength);
        }
        else
        {
            if(PF_Campare_Data(&V_ucJudgeBuffer1[V_ucRealDatabuffer2], &V_ucUmin[C_Judge_StartBuffer0], V_ucDatalength) == C_LessThan)
            {
                PF_CopyDataBytes(&V_ucJudgeBuffer1[V_ucRealDatabuffer2], &V_ucUmin[C_Judge_StartBuffer0], V_ucDatalength);
            }
        }
    }

    if(PF_Campare_Data(&V_ucUmax[C_Judge_StartBuffer0], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], V_ucDatalength) == C_Equal)/*被除数等于0*/
    {
        return;
    }
    SF_HEXDECBytes(V_ucUmax, V_ucUmin, (uchar8 *)&V_ulDivisor, V_ucDatalength);/*计算被除数*/
    V_ulDivisor *= C_TenThousand_times;/*差值*100*/

    PF_BufferXToUlong32(V_ucUmax, &V_ulDividend, V_ucDatalength);/*最大电压转成1个32位数据*/

    V_ulQuotient = V_ulDivisor / V_ulDividend;

    PF_Ulong32ToBufferX(V_ucJudgeBuffer1, &V_ulQuotient, 4);
    PF_CopyDataBytes(V_ucJudgeBuffer1, V_JudgeUnbanlance, C_Unbalance_Length);
}
/***********************************************************************************
函数原型：uchar8 SF_Get_UnbanlanceVoltage_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
功能描述: 电压不平衡
输入参数：EventNo（事件号）、Hstate（历史状态）
输出参数：返回事件当前所处状态
返回参数C_Happen_V_ucEventState		事件状态，有发生无恢复
          C_End_EventState	  		事件状态，非有发生无恢复
          C_Close_EventState		事件状态，关闭
功能说明：判断事件当前状态；
调用机制：事件判断函数调用
备    注：
**********************************************************************************/
uchar8 SF_Get_UnbanlanceVoltage_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
 	uchar8	V_ucJudgeBuffer1[C_Unbalance_Length];					/*电压不平衡率判断阀值，电压不平衡率*/
	uchar8	V_ucJudgeBuffer2[C_4Volage_Length];					/*全失压判断电压，三相电压*/
    uchar8  V_ucJudgeUnbanlance[3];
	ushort16 V_usJudgeBufferLength1 = CLNoBal_Vol_Lim, V_usEncode;

	if(InF_GetData_ObjectManage(CNoBal_Vol_Lim, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)		/*电压不平衡判断阀值, 阀值为0，返回关闭*/
	{
		return(V_ucHstate);
	}
	if((V_ucJudgeBuffer1[C_Judge_StartBuffer0] == C_NULL)
       && (V_ucJudgeBuffer1[C_Judge_StartBuffer1] == C_NULL))
	{
		return(C_Close_EventState);
	}
    V_usJudgeBufferLength1 = CLLoss_Volage_Vol;
	if(InF_GetData_ObjectManage(CLoss_Volage_Vol, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)	/*全失压电压*/
	{
		return(V_ucHstate);
	}
    V_usJudgeBufferLength1 = CLPhaseFF_Volage;        /*V0.2新增长度赋值*/
	if(InF_GetData_ObjectManage(CPhaseFF_Volage, &V_ucJudgeBuffer2[C_JudgeVolage_Buffer1], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)	/*三相电压*/
	{
		return(V_ucHstate);
	}
	SF_Get_UnbalanceRate_RealTime(C_UnbanlanceVoltageEventNo, &V_ucJudgeUnbanlance[C_Judge_StartBuffer0]);

	if( ((PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeVolage_Buffer1], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_Volage_Length) == C_GreaterThan)
		|| (PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeVolage_Buffer2], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_Volage_Length) == C_GreaterThan)
		|| (PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeVolage_Buffer3], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_Volage_Length) == C_GreaterThan))/*任一相电压大于临界电压*/
        &&(PF_Campare_Data(&V_ucJudgeUnbanlance[C_Judge_StartBuffer0], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Unbalance_Length) == C_GreaterThan) )	/*电压不平衡率大于判断阀值*/
	{
		return(C_Happen_EventState);
	}
	else
	{
		return(C_End_EventState);
	}
}
/***********************************************************************************
函数原型：uchar8 SF_Get_FFUnbanlanceCurrent_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
功能描述: 电流不平衡、电流严重不平衡
输入参数：EventNo（事件号）、Hstate（历史状态）
输出参数：返回事件当前所处状态
返回参数C_Happen_V_ucEventState		事件状态，有发生无恢复
          C_End_EventState	  		事件状态，非有发生无恢复
          C_Close_EventState		事件状态，关闭
功能说明：判断事件当前状态；
调用机制：事件判断函数调用
备    注：
**********************************************************************************/
uchar8 SF_Get_FFUnbanlanceCurrent_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
 	uchar8	V_ucJudgeBuffer1[C_Unbalance_Length];					/*不平衡率判断阀值，当前电流不平衡率*/
	uchar8	V_ucJudgeBuffer2[C_4Curr_Length];					/*全失压判断电流，三相电流*/
    uchar8  V_ucJudgeUnbanlance[C_Unbalance_Length];
    ulong32	V_JudgeThreshold;
	ushort16 V_usJudgeBufferLength1, V_usEncode;

	switch(V_ucEventNo)
	{
		case	C_UnbanlanceCurrentEventNo:
				V_JudgeThreshold = CNoBal_Curr_Lim;
				break;
		case	C_SUnbanlanceCurrentEventNo:
				V_JudgeThreshold = CSeriNoBal_Curr_Lim;
				break;
		default:
				return(V_ucHstate);
	}
    V_usJudgeBufferLength1 = CLNoBal_Curr_Lim;
	if(InF_GetData_ObjectManage(V_JudgeThreshold, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)		/*不平衡判断阀值, 阀值为0，返回关闭*/
	{
		return(V_ucHstate);
	}
	if( (V_ucJudgeBuffer1[C_Judge_StartBuffer0] == C_NULL)
        &&(V_ucJudgeBuffer1[C_Judge_StartBuffer1] == C_NULL) )
	{
		return(C_Close_EventState);
	}
    V_usJudgeBufferLength1 = CLLoss_Volage_Curr;
	if(InF_GetData_ObjectManage(CLoss_Volage_Curr, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)	/*全失压电流*/
	{
		return(V_ucHstate);
	}
	V_ucJudgeBuffer2[C_Judge_StartBuffer2] = C_NULL;
    V_ucJudgeBuffer2[C_Judge_StartBuffer3] = C_NULL;

    V_usJudgeBufferLength1=CLPhaseFF_Curr; /*V0.2新增长度赋值*/
	if(InF_GetData_ObjectManage(CPhaseFF_Curr, &V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)	/*三相电流*/
	{
		return(V_ucHstate);
	}
    PF_GetAbs(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], &V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], C_Curr4Bytes_Length);/*A相电流取绝对值*/
	PF_GetAbs(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer2], &V_ucJudgeBuffer2[C_JudgeCurr_Buffer2], C_Curr4Bytes_Length);/*B相电流取绝对值*/
	PF_GetAbs(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer3], &V_ucJudgeBuffer2[C_JudgeCurr_Buffer3], C_Curr4Bytes_Length);/*C相电流取绝对值*/

	SF_Get_UnbalanceRate_RealTime(V_ucEventNo, &V_ucJudgeUnbanlance[C_Judge_StartBuffer0]);

	if( ((PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_Curr_Length) == C_GreaterThan)
		|| (PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer2], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_Curr_Length) == C_GreaterThan)
		|| (PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer3], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_Curr_Length) == C_GreaterThan))	/*任一相电压大于临界电压*/
        && (PF_Campare_Data(&V_ucJudgeUnbanlance[C_Judge_StartBuffer0], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Unbalance_Length) == C_GreaterThan) )/*电流不平衡率大于判断阀值*/
	{
		return(C_Happen_EventState);
	}
	else
	{
		return(C_End_EventState);
	}
}

/***********************************************************************************
函数原型：uchar8 SF_Get_Losscurrent_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
功能描述: 失流
输入参数：EventNo（事件号）、Hstate（历史状态）
输出参数：返回事件当前所处状态
返回参数C_Happen_V_ucEventState		事件状态，有发生无恢复
          C_End_EventState	  		事件状态，非有发生无恢复
          C_Close_EventState		事件状态，关闭
功能说明：判断事件当前状态；
调用机制：事件判断函数调用
备    注：
**********************************************************************************/
uchar8 SF_Get_Losscurrent_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
	uchar8	V_ucVolage[C_Volage_Length], V_ucCurr[C_Curr4Dig_Length];
	uchar8	V_ucJudgeBuffer1[C_4Volage_Length];	/*电压判断阀值、三相电压*/
	uchar8	V_ucJudgeBuffer2[C_4Curr_Length];		/*电流判断阀值、三相电流*/
	uchar8	V_ucJudgeBuffer3[C_2Curr_Length];		/*失流事件电流触发下限*/
	uchar8	V_uclineType;
	ushort16 V_usJudgeBufferLength1 = C_4Volage_Length, V_usLineLength=C_Length_One;
	ushort16 V_usJudgeBufferLength2 = C_4Curr_Length, V_usCurrLength = C_Curr_Length, V_usEncode;

	if(InF_GetData_ObjectManage(CLossCurr_Vol_LowLim, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
	if(InF_GetData_ObjectManage(CLossCurr_Curr_UpLim, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usJudgeBufferLength2, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
	if(InF_GetData_ObjectManage(CLine_Type, &V_uclineType, &V_usLineLength, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
	if((V_ucJudgeBuffer2[C_Judge_StartBuffer0] == C_NULL)
        &&(V_ucJudgeBuffer2[C_Judge_StartBuffer1] == C_NULL)
        &&(V_ucJudgeBuffer2[C_Judge_StartBuffer2] == C_NULL)
        &&(V_ucJudgeBuffer2[C_Judge_StartBuffer3] == C_NULL))
	{
		return(C_Close_EventState);
	}
    V_usJudgeBufferLength1 = CLPhaseFF_Volage;      /*V0.2新增长度赋值*/
	if(InF_GetData_ObjectManage(CPhaseFF_Volage, &V_ucJudgeBuffer1[C_JudgeVolage_Buffer1], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
    V_usJudgeBufferLength2 = CLPhaseFF_Curr_4Dig;    /*V0.2新增长度赋值*/
	if(InF_GetData_ObjectManage(CPhaseFF_Curr_4Dig, &V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], &V_usJudgeBufferLength2, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
	if(InF_GetData_ObjectManage(CLossCurr_Curr_LowLim, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_usCurrLength, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
    PF_GetAbs(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], &V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], C_Curr4Bytes_Length);/*A相电流取绝对值*/
	PF_GetAbs(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer2], &V_ucJudgeBuffer2[C_JudgeCurr_Buffer2], C_Curr4Bytes_Length);/*B相电流取绝对值*/
	PF_GetAbs(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer3], &V_ucJudgeBuffer2[C_JudgeCurr_Buffer3], C_Curr4Bytes_Length);/*C相电流取绝对值*/

 	if(PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeCurr4Dig_Buffer1], &V_ucJudgeBuffer2[C_JudgeCurr4Dig_Buffer3], C_Curr4Dig_Length) == C_GreaterThan)
	{
		PF_CopyDataBytes(&V_ucJudgeBuffer2[C_JudgeCurr4Dig_Buffer1], &V_ucJudgeBuffer3[C_JudgeCurr4Dig_Buffer1], C_Curr4Dig_Length);
	}
    else
    {
 	    PF_CopyDataBytes(&V_ucJudgeBuffer2[C_JudgeCurr4Dig_Buffer3], &V_ucJudgeBuffer3[C_JudgeCurr4Dig_Buffer1], C_Curr4Dig_Length);
    }
	if(V_uclineType == C_3P4W)
	{
		if(PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeCurr4Dig_Buffer2], &V_ucJudgeBuffer3[C_JudgeCurr4Dig_Buffer1], C_Curr4Dig_Length) == C_GreaterThan)
		{
			PF_CopyDataBytes(&V_ucJudgeBuffer2[C_JudgeCurr4Dig_Buffer2], &V_ucJudgeBuffer3[C_JudgeCurr4Dig_Buffer1], C_Curr4Dig_Length);
		}
	}
	switch(V_ucEventNo)
	{
		case	C_ALosscurrentEventNo:
				PF_CopyDataBytes(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer1], &V_ucVolage[C_Judge_StartBuffer0], C_Volage_Length);
				PF_CopyDataBytes(&V_ucJudgeBuffer2[C_JudgeCurr4Dig_Buffer1], &V_ucCurr[C_Judge_StartBuffer0], C_Curr4Dig_Length);
				break;
		case	C_BLosscurrentEventNo:
				PF_CopyDataBytes(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer2], &V_ucVolage[C_Judge_StartBuffer0], C_Volage_Length);
				PF_CopyDataBytes(&V_ucJudgeBuffer2[C_JudgeCurr4Dig_Buffer2], &V_ucCurr[C_Judge_StartBuffer0], C_Curr4Dig_Length);
				break;

		default:
				PF_CopyDataBytes(&V_ucJudgeBuffer1[C_JudgeVolage_Buffer3], &V_ucVolage[C_Judge_StartBuffer0], C_Volage_Length);
				PF_CopyDataBytes(&V_ucJudgeBuffer2[C_JudgeCurr4Dig_Buffer3], &V_ucCurr[C_Judge_StartBuffer0], C_Curr4Dig_Length);
				break;
	}
	if( (PF_Campare_Data(&V_ucVolage[C_Judge_StartBuffer0], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_GreaterThan)
		&&(PF_Campare_Data(&V_ucCurr[C_Judge_StartBuffer0], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_Curr4Dig_Length) == C_LessThan)
		&&(PF_Campare_Data(&V_ucJudgeBuffer3[C_JudgeCurr4Dig_Buffer1], &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_Curr4Dig_Length) == C_GreaterThan) )
	{
		return(C_Happen_EventState);
	}
	else
	{
		return(C_End_EventState);
	}
}

/***********************************************************************************
函数原型：uchar8 SF_Get_Overcurrent_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
功能描述: 过流
输入参数：EventNo（事件号）、Hstate（历史状态）
输出参数：返回事件当前所处状态
返回参数C_Happen_V_ucEventState		事件状态，有发生无恢复
          C_End_EventState	  		事件状态，非有发生无恢复
          C_Close_EventState		事件状态，关闭
功能说明：判断事件当前状态；
调用机制：事件判断函数调用
备    注：
**********************************************************************************/
uchar8	SF_Get_Overcurrent_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
	ulong32	V_ulCurr;
	uchar8	V_ucJudgeBuffer1[C_2Curr_Length];			/*电流判断阀值、三相电流*/
	ushort16 V_usCurrLength = C_Curr4Bytes_Length, V_usCurrLength2 = C_Curr4Bytes_Length, V_usEncode;

	if(InF_GetData_ObjectManage(COverCurr_Curr_LowLim, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usCurrLength2, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
	if( (V_ucJudgeBuffer1[C_Judge_StartBuffer0] == C_NULL)
        &&(V_ucJudgeBuffer1[C_Judge_StartBuffer1] == C_NULL)
        &&(V_ucJudgeBuffer1[C_Judge_StartBuffer2] == C_NULL)
        &&(V_ucJudgeBuffer1[C_Judge_StartBuffer3] == C_NULL) )
	{
		return(C_Close_EventState);
	}
	switch(V_ucEventNo)
	{
		case	C_AOvercurrentEventNo:
				V_ulCurr = CPhaseA_Curr_4Dig;
				break;
		case	C_BOvercurrentEventNo:
				V_ulCurr = CPhaseB_Curr_4Dig;
				break;
		case	C_COvercurrentEventNo:
				V_ulCurr = CPhaseC_Curr_4Dig;
				break;
		default:
				return(V_ucHstate);
	}
	if(InF_GetData_ObjectManage(V_ulCurr, &V_ucJudgeBuffer1[C_JudgeCurr4Dig_Buffer1], &V_usCurrLength, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
    PF_GetAbs(&V_ucJudgeBuffer1[C_JudgeCurr4Dig_Buffer1], &V_ucJudgeBuffer1[C_JudgeCurr4Dig_Buffer1], C_Curr4Bytes_Length);/*电流取绝对值*/

	if(PF_Campare_Data(&V_ucJudgeBuffer1[C_JudgeCurr4Dig_Buffer1], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Curr_Length) == C_GreaterThan)
	{
		return(C_Happen_EventState);
	}
	else
	{
		return(C_End_EventState);
	}
}

/***********************************************************************************
函数原型：uchar8	SF_Get_Failcurrent_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
功能描述: 断流
输入参数：EventNo（事件号）、Hstate（历史状态）
输出参数：
返回参数C_Happen_V_ucEventState		事件状态，有发生无恢复
          C_End_EventState	  		事件状态，非有发生无恢复
          C_Close_EventState		事件状态，关闭
功能说明：判断事件当前状态；
调用机制：事件判断函数调用
备    注：
**********************************************************************************/
uchar8	SF_Get_Failcurrent_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
	uchar8	V_ucJudgeBuffer1[C_2Curr4Dig_Length];			/*电流判断阀值、三相电流*/
	uchar8	V_ucJudgeBuffer2[C_2Volage_Length];			/*电流判断阀值、三相电流*/
	ulong32	V_ulVolage, V_ulCurr;
	ushort16 V_usCurrLength1 = C_JudgeCurr_Length, V_usVolageLength = C_Volage_Length, V_usCurrLength = C_Curr4Dig_Length, V_usEncode;

	if(InF_GetData_ObjectManage(CBreakCurr_Curr_UpLim, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usCurrLength1, &V_usEncode)!=C_OK)
	{
		return(V_ucHstate);
	}
	if( (V_ucJudgeBuffer1[C_Judge_StartBuffer0] == C_NULL)
        &&(V_ucJudgeBuffer1[C_Judge_StartBuffer1] == C_NULL)
        &&(V_ucJudgeBuffer1[C_Judge_StartBuffer2] == C_NULL)
        &&(V_ucJudgeBuffer1[C_Judge_StartBuffer3] == C_NULL) )
	{
		return(C_Close_EventState);
	}
	switch(V_ucEventNo)
	{
		case	C_AFailcurrentEventNo:
				V_ulVolage = CPhaseA_Volage;
				V_ulCurr = CPhaseA_Curr_4Dig;
				break;
		case	C_BFailcurrentEventNo:
				V_ulVolage = CPhaseB_Volage;
				V_ulCurr = CPhaseB_Curr_4Dig;
				break;
		case	C_CFailcurrentEventNo:
				V_ulVolage = CPhaseC_Volage;
				V_ulCurr = CPhaseC_Curr_4Dig;
				break;
		default:
				return(V_ucHstate);
	}
	if(InF_GetData_ObjectManage(CBreakCurr_Vol_LowLim, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usVolageLength, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
    V_usVolageLength = C_Volage_Length;
	if(InF_GetData_ObjectManage(V_ulVolage, &V_ucJudgeBuffer2[C_JudgeVolage_Buffer1], &V_usVolageLength, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
	if(InF_GetData_ObjectManage(V_ulCurr, &V_ucJudgeBuffer1[C_JudgeCurr4Dig_Buffer1], &V_usCurrLength, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
    PF_GetAbs(&V_ucJudgeBuffer1[C_JudgeCurr4Dig_Buffer1], &V_ucJudgeBuffer1[C_JudgeCurr4Dig_Buffer1], C_Curr4Bytes_Length);/*电流取绝对值*/

	if( (PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeVolage_Buffer1], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_Volage_Length) == C_GreaterThan)
		&&(PF_Campare_Data(&V_ucJudgeBuffer1[C_JudgeCurr4Dig_Buffer1], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Curr4Dig_Length) == C_LessThan) )
	{
		return(C_Happen_EventState);
	}
	else
	{
		return(C_End_EventState);
	}
}
/***********************************************************************************
函数原型：uchar8	SF_Get_FFReversecurrent_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
功能描述:分相功率反向((三相四线系统中判断) )
输入参数：EventNo（事件号）、Hstate（历史状态）
输出参数：返回事件当前所处状态
返回参数C_Happen_V_ucEventState		事件状态，有发生无恢复
          C_End_EventState	  		事件状态，非有发生无恢复
          C_Close_EventState		事件状态，关闭
功能说明：判断事件当前状态；
调用机制：事件判断函数调用
备    注：(此条开始，长度采用数据层)
**********************************************************************************/
 uchar8	SF_Get_FFReversecurrent_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
 {
 	ulong32		V_ulInstant_AcPow;
 	uchar8		V_ucJudgeBuffer1[C_Length_Eight];		/*8个字节存放判断阀值和分相功率*/
	ushort16    V_usJudgeBufferLength1 = CLInstantA_AcPow, V_usEncode;
    uchar8      V_ucSign;

	switch(V_ucEventNo)
	{
		case	C_TReversecurrentEventNo:
				V_ulInstant_AcPow = CInstant_TolAcPow;	/*总有功功率*/
				break;
		case	C_AReversecurrentEventNo:
				V_ulInstant_AcPow = CInstantA_AcPow;	/*A相有功功率*/
				break;
		case	C_BReversecurrentEventNo:
				V_ulInstant_AcPow = CInstantB_AcPow;
				break;
		case	C_CReversecurrentEventNo:
				V_ulInstant_AcPow = CInstantC_AcPow;
				break;
		default:
				return(V_ucHstate);
	}
   	if(InF_GetData_ObjectManage(CPowerRev_AcPower_LowLim, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK) /*事件判断阀值*/
	{
		return(V_ucHstate);
	}
	if( (V_ucJudgeBuffer1[C_Judge_StartBuffer0] == C_NULL)
        && (V_ucJudgeBuffer1[C_Judge_StartBuffer1] == C_NULL)
        && (V_ucJudgeBuffer1[C_Judge_StartBuffer2] == C_NULL)
        && (V_ucJudgeBuffer1[C_Judge_StartBuffer3] == C_NULL) )/*阀值为0，关闭*/
	{
		return(C_Close_EventState);
	}
    V_usJudgeBufferLength1 = CLInstantA_AcPow;
	if(InF_GetData_ObjectManage(V_ulInstant_AcPow, &V_ucJudgeBuffer1[C_Instant_AcPow_Buffer], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)		/*分相有功功率*/
	{
		return(V_ucHstate);
	}
    V_ucSign = PF_GetAbs(&V_ucJudgeBuffer1[C_Instant_AcPow_Buffer], &V_ucJudgeBuffer1[C_Instant_AcPow_Buffer], C_Curr4Bytes_Length);/*电流取绝对值*/

	if( (V_ucSign == C_GetSignBit)
		&&(PF_Campare_Data(&V_ucJudgeBuffer1[C_Instant_AcPow_Buffer], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], CLInstantA_AcPow) == C_GreaterThan) )
	{
		return(C_Happen_EventState);
	}
	else
	{
		return(C_End_EventState);
	}
 }

/***********************************************************************************
函数原型：uchar8	SF_Get_Overload_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
功能描述: 过载
输入参数：EventNo（事件号）、Hstate（历史状态）
输出参数：返回事件当前所处状态
返回参数C_Happen_V_ucEventState		事件状态，有发生无恢复
          C_End_EventState	  		事件状态，非有发生无恢复
          C_Close_EventState		事件状态，关闭
功能说明：判断事件当前状态；
调用机制：事件判断函数调用
备    注：(此条开始，长度采用数据层)
***********************************************************************************/
 uchar8	SF_Get_Overload_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
 {
 	ulong32		V_ulInstant_AcPow;						/*有功功率*/
 	uchar8		V_ucJudgeBuffer1[C_Length_Eight];		/*8个字节存放判断阀值和分相功率*/
	ushort16    V_usJudgeBufferLength1 = CLInstantA_AcPow, V_usEncode;

	switch(V_ucEventNo)
	{
		case	C_AOverloadEventNo:
				V_ulInstant_AcPow = CInstantA_AcPow;	/*A相有功功率*/
				break;
		case	C_BOverloadEventNo:
				V_ulInstant_AcPow = CInstantB_AcPow;
				break;
		case	C_COverloadEventNo:
				V_ulInstant_AcPow = CInstantC_AcPow;
				break;
		default:
				return(V_ucHstate);
	}
   	if(InF_GetData_ObjectManage(COverLoad_AcPower_LowLim, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK) /*事件判断阀值*/
	{
		return(V_ucHstate);
	}
	if( (V_ucJudgeBuffer1[C_Judge_StartBuffer0] == C_NULL)
        && (V_ucJudgeBuffer1[C_Judge_StartBuffer1] == C_NULL)
        && (V_ucJudgeBuffer1[C_Judge_StartBuffer2] == C_NULL)
        && (V_ucJudgeBuffer1[C_Judge_StartBuffer3] == C_NULL) )/*阀值为0，关闭*/
	{
		return(C_Close_EventState);
	}
    V_usJudgeBufferLength1 = CLInstantA_AcPow;
	if(InF_GetData_ObjectManage(V_ulInstant_AcPow, &V_ucJudgeBuffer1[C_Instant_AcPow_Buffer], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)		/*分相有功功率*/
	{
		return(V_ucHstate);
	}
    PF_GetAbs(&V_ucJudgeBuffer1[C_Instant_AcPow_Buffer], &V_ucJudgeBuffer1[C_Instant_AcPow_Buffer], C_Curr4Bytes_Length);/*电流取绝对值*/

	if(PF_Campare_Data(&V_ucJudgeBuffer1[C_Instant_AcPow_Buffer], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], CLInstantA_AcPow) == C_GreaterThan)
	{
		return(C_Happen_EventState);
	}
	else
	{
		return(C_End_EventState);
	}
 }

/***********************************************************************************
函数原型：uchar8 SF_Get_Overpowerfact_Cstate(uchar8 V_ucHstate)
功能描述：总功率因数超下限
输入参数：EventNo，Hstate（历史状态）
输出参数：返回事件当前所处状态
返回参数C_IDError             数据标识码错误
           C_Happen_EventState	事件状态，有发生无恢复
          C_End_EventState	  	事件状态，非有发生无恢复
          C_Close_EventState	事件状态，关闭状态
功能说明：判断事件当前状态；
调用机制：事件判断函数调用
备    注：
***********************************************************************************/
uchar8 SF_Get_Overpowerfact_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
 	uchar8	V_ucJudgeBuffer1[C_Length_Five];		/*4个字节存放判断阀值和总功率因数, 最后1字节放象限类型*/
	uchar8	V_ucJudgeBuffer2[C_4Curr_Length];
	ushort16 V_usJudgeBufferLength1=C_Length_Five, V_usJudgeBufferLength2 = C_4Curr_Length, V_usEncode;

	if(InF_GetData_ObjectManage(CPowerFactor_LowLim, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)/*判断阀值*/
	{
		return(V_ucHstate);
	}
	if( (V_ucJudgeBuffer1[C_Judge_StartBuffer0] == C_NULL)
       && (V_ucJudgeBuffer1[C_Judge_StartBuffer1] == C_NULL) )
	{
		return(C_Close_EventState);
	}
    V_usJudgeBufferLength1 = CLTol_PowerFactor;
	if(InF_GetData_ObjectManage(CTol_PowerFactor, &V_ucJudgeBuffer1[C_Judge_StartBuffer2], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)	/*总功率因数*/
	{
		return(V_ucHstate);
	}
	if(InF_GetData_ObjectManage(CLoss_Volage_Curr, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usJudgeBufferLength2, &V_usEncode) != C_OK)	/*全失压电流*/
	{
		return(V_ucHstate);
	}
	V_ucJudgeBuffer2[C_Judge_StartBuffer2] = C_NULL;
    V_ucJudgeBuffer2[C_Judge_StartBuffer3] = C_NULL;

    PF_GetAbs(&V_ucJudgeBuffer1[C_Judge_StartBuffer2], &V_ucJudgeBuffer1[C_Judge_StartBuffer2], CLTol_PowerFactor);/*功率因数取绝对值*/

    V_usJudgeBufferLength2 = CLPhaseFF_Curr;    /*V0.2新增长度赋值*/
	if(InF_GetData_ObjectManage(CPhaseFF_Curr, &V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], &V_usJudgeBufferLength2, &V_usEncode) != C_OK)		/*三相电流*/
	{
		return(V_ucHstate);
	}
    PF_GetAbs(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], &V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], C_Curr4Bytes_Length);/*A相电流取绝对值*/
	PF_GetAbs(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer2], &V_ucJudgeBuffer2[C_JudgeCurr_Buffer2], C_Curr4Bytes_Length);/*B相电流取绝对值*/
	PF_GetAbs(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer3], &V_ucJudgeBuffer2[C_JudgeCurr_Buffer3], C_Curr4Bytes_Length);/*C相电流取绝对值*/

	if( (PF_Campare_Data(&V_ucJudgeBuffer1[C_Judge_StartBuffer2], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], CLTol_PowerFactor) == C_LessThan)/*功率阀值判断*/
		&& ((PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_Curr_Length) == C_GreaterThan)/*电流判断*/
            || (PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer2], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_Curr_Length) == C_GreaterThan)
            || (PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer3], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_Curr_Length) == C_GreaterThan)) )
	{
		return(C_Happen_EventState);
	}
	else
	{
		return(C_End_EventState);
	}
}

/***********************************************************************************
函数原型：uchar8 SF_Get_FFOverpowerfact_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
功能描述：分相功率因数超下限
输入参数：EventNo，Hstate（历史状态）
输出参数：返回事件当前所处状态
返回参数C_IDError             数据标识码错误
           C_Happen_EventState	事件状态，有发生无恢复
          C_End_EventState	  	事件状态，非有发生无恢复
          C_Close_EventState	事件状态，关闭状态
功能说明：判断事件当前状态；
调用机制：事件判断函数调用
备    注：
***********************************************************************************/
uchar8 SF_Get_FFOverpowerfact_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
	uchar8	V_ucJudgeBuffer1[C_Length_Four];		/*4个字节存放判断阀值和总功率因数*/
	uchar8	V_ucJudgeBuffer2[C_4Curr_Length];
	ulong32	V_ulOverpowerfact, V_ulCurr;
	ushort16 V_usJudgeBufferLength1 = CLPowerFactor_LowLim, V_usEncode;

	if(InF_GetData_ObjectManage(CPowerFactor_LowLim, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)/*判断阀值*/
	{
		return(V_ucHstate);
	}
	if( (V_ucJudgeBuffer1[C_Judge_StartBuffer0] == C_NULL)
       &&(V_ucJudgeBuffer1[C_Judge_StartBuffer1] == C_NULL) )
	{
		return(C_Close_EventState);
	}
	switch(V_ucEventNo)
	{
		case	C_AOverpowerfactEventNo:
				V_ulOverpowerfact = CPhaseA_PowerFactor;	/*A相功率因数, 电流*/
				V_ulCurr = CPhaseA_Curr;
				break;
		case	C_BOverpowerfactEventNo:
				V_ulOverpowerfact = CPhaseB_PowerFactor;
				V_ulCurr = CPhaseB_Curr;
				break;
		case	C_COverpowerfactEventNo:
				V_ulOverpowerfact = CPhaseC_PowerFactor;
				V_ulCurr = CPhaseC_Curr;
				break;
		default:
				return(V_ucHstate);
	}
    V_usJudgeBufferLength1 = CLPhaseA_PowerFactor;
	if(InF_GetData_ObjectManage(V_ulOverpowerfact, &V_ucJudgeBuffer1[C_Judge_StartBuffer2], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)	/*总功率因数*/
	{
		return(V_ucHstate);
	}
    PF_GetAbs(&V_ucJudgeBuffer1[C_Judge_StartBuffer2], &V_ucJudgeBuffer1[C_Judge_StartBuffer2], CLPhaseA_PowerFactor);/*取功率因数绝对值*/

    V_usJudgeBufferLength1 = CLLoss_Volage_Curr;
	if(InF_GetData_ObjectManage(CLoss_Volage_Curr, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)	/*全失压电流*/
	{
		return(V_ucHstate);
	}
	V_ucJudgeBuffer2[C_Judge_StartBuffer2] = C_NULL;
    V_ucJudgeBuffer2[C_Judge_StartBuffer3] = C_NULL;

    V_usJudgeBufferLength1 = CLPhaseA_Curr;    /*V0.2新增长度赋值*/
	if(InF_GetData_ObjectManage(V_ulCurr, &V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], &V_usJudgeBufferLength1, &V_usEncode) != C_OK)	/*分相电流*/
	{
		return(V_ucHstate);
	}
	PF_GetAbs(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], &V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], CLPhaseA_Curr);/*取电流绝对值*/

	if( (PF_Campare_Data(&V_ucJudgeBuffer1[C_Judge_StartBuffer2], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], CLTol_PowerFactor) == C_LessThan)
		&&(PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer1], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_Curr_Length) == C_GreaterThan) )
	{
		return(C_Happen_EventState);
	}
	else
	{
		return(C_End_EventState);
	}
}
/*******************************************************************************
函数原型：uchar8 SF_Get_MeterAndClockFa_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
功能描述：计量芯片和时钟故障
输入参数：EventNo，Hstate（历史状态）
输出参数：返回事件当前所处状态
返回参数：C_Happen_V_ucEventState 事件状态，有发生无恢复
		 C_End_EventState	 事件状态，非有发生无恢复
调用位置：事件判断函数调用
备    注：
*******************************************************************************/
uchar8 SF_Get_MeterAndClockFa_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
	uchar8	V_ucData;
	uchar8  V_ucData_ChipID[3] = {0};
	ulong32 V_ulData = 0;
    ushort16 V_usEncode, V_usDataLen;

	if(V_ucEventNo == C_MeterFaEventNo)
	{
		SF_ReadOneReg_MeterIC(C_ChipID_Reg, V_ucData_ChipID, C_ReadMeaDataRegFlag);
		PF_BufferXToUlong32(V_ucData_ChipID, &V_ulData, C_RegDataLen);

		if( ( V_ulData == 0x00FFFFFF ) || ( V_ulData == 0 ) )		/*20规范，通信失败判断为计量芯故障, 故障时为0xFFFFFF或全0*/
		{
			return(C_Happen_EventState);
		}
		else
		{
			return(C_End_EventState);
		}
	}
	else if(V_ucEventNo == C_ClockFaEventNo)
	{
		V_usDataLen = CLClock_FaultState;
		if(InF_GetData_ObjectManage(CClock_FaultState, &V_ucData, &V_usDataLen, &V_usEncode) != C_OK)	/*判断状态字*/
		{
			return(V_ucHstate);
		}
		if( (V_ucData & C_RTCERR_MeterWorkState) == C_RTCERR_MeterWorkState )
		{
			return(C_Happen_EventState);
		}
		else
		{
			return(C_End_EventState);
		}
	}
	else
	{
		return(V_ucHstate);
	}
}

/***********************************************************************************
函数原型：uchar8 SF_Get_NeutralCurrentAbnormal_Cstate(uchar8 V_ucHstate)
功能描述: 零线电流异常状态
输入参数：EventNo（事件号）、Hstate（历史状态）
输出参数：返回事件当前所处状态
返回参数C_Happen_V_ucEventState		事件状态，有发生无恢复
          C_End_EventState	  		事件状态，非有发生无恢复
          C_Close_EventState		事件状态，关闭
功能说明：判断事件当前状态；
调用机制：事件判断函数调用
备    注：
***********************************************************************************/
uchar8 SF_Get_NeutralCurrentAbnormal_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
{
 	uchar8	V_ucJudgeBuffer1[C_Judge_10BufferLength] = {0};					/*零线电流和火线电流（三相电能表的火线电流为三相电流矢量和）中任一电流大于电流触发下限*/
	uchar8	V_ucJudgeBuffer2[C_3Curr_Length] = {0};					/*零线电流、火线电流的不平衡率大于不平衡率限值*/
	uchar8	V_ucJudgeBuffer3[C_Curr_Length] = {0};					/*零线电流、火线电流的不平衡率大于不平衡率限值*/
	ushort16 V_usDataLength = 0, V_usEncode;
	uchar8	V_ucMax[4] = {0}, V_ucMin[4] = {0};
    ulong32 V_ulDivisor = 0, V_ulDividend = 0, V_ulQuotient = 0;
    ulong32 V_ulVector_Current, V_ulZero_Current;

    /*不平衡率判断阀值*****************************************************/
    V_usDataLength = CLNeutralUnbalanceRate;
	if(InF_GetData_ObjectManage(CNeutralUnbalanceRate, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usDataLength, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}

    /*不平衡率判断阀值为0，返回关闭*/
	if((V_ucJudgeBuffer1[C_Judge_StartBuffer0] == C_NULL)
       &&(V_ucJudgeBuffer1[C_Judge_StartBuffer1] == C_NULL))
	{
		return(C_Close_EventState);
	}

    /*电流触发下限*********************************************************/
    V_usDataLength = CLNeutralAbnormal_Curr_LowLim;
	if(InF_GetData_ObjectManage(CNeutralAbnormal_Curr_LowLim, &V_ucJudgeBuffer1[C_Judge_StartBuffer3], &V_usDataLength, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}

    /*三相电流矢量和*******************************************************/
    V_usDataLength = CLVector_Current;
	if(InF_GetData_ObjectManage(CVector_Current, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usDataLength, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
    PF_BufferXToUlong32(V_ucJudgeBuffer2, &V_ulVector_Current, CLVector_Current);
    V_ulVector_Current = V_ulVector_Current * 10;
    PF_Ulong32ToBufferX(V_ucJudgeBuffer2, &V_ulVector_Current, CLVector_Current);
    /*零线电流*************************************************************/
    V_usDataLength = CLZero_Current;
	if(InF_GetData_ObjectManage(CZero_Current, &V_ucJudgeBuffer2[C_Judge_StartBuffer4], &V_usDataLength, &V_usEncode) != C_OK)
	{
		return(V_ucHstate);
	}
    PF_BufferXToUlong32(&V_ucJudgeBuffer2[C_Judge_StartBuffer4], &V_ulZero_Current, CLZero_Current);
    V_ulZero_Current = V_ulZero_Current * 10;
    PF_Ulong32ToBufferX(&V_ucJudgeBuffer2[C_Judge_StartBuffer4], &V_ulZero_Current, CLZero_Current);

    /*当前电流不平衡率*****************************************************/
    /*三相电流矢量和与零线电流比较，大的放V_ucMax，小的放V_ucMin*/
	if(PF_Campare_Data(&V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_ucJudgeBuffer2[C_Judge_StartBuffer4], CLVector_Current) == C_GreaterThan)
	{
		PF_CopyDataBytes(&V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_ucMax[C_Judge_StartBuffer0], CLVector_Current);
		PF_CopyDataBytes(&V_ucJudgeBuffer2[C_Judge_StartBuffer4], &V_ucMin[C_Judge_StartBuffer0], CLVector_Current);
	}
    else
    {
		PF_CopyDataBytes(&V_ucJudgeBuffer2[C_Judge_StartBuffer4], &V_ucMax[C_Judge_StartBuffer0], CLVector_Current);
		PF_CopyDataBytes(&V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_ucMin[C_Judge_StartBuffer0], CLVector_Current);
    }

    /*除数等于0*/
    if(PF_Campare_Data(&V_ucMax[C_Judge_StartBuffer0], &V_ucJudgeBuffer3[C_Judge_StartBuffer0], CLVector_Current) == C_Equal)
    {
        return(C_End_EventState);	/*最大值为0表示零线电流、零序电流的绝对值都为0，因此零线电流异常事件结束*/
    }

    /*不平衡率 = （最大值 - 最小值） * 100 / 最大值*/
    SF_HEXDECBytes(V_ucMax, V_ucMin, (uchar8 *)&V_ulDivisor, C_Curr_Length);/*计算被除数*/
    V_ulDivisor *= C_TenThousand_times;/*差值*10000*/

    PF_BufferXToUlong32(V_ucMax, &V_ulDividend, CLVector_Current);/*最大电压转成1个32位数据*/

    V_ulQuotient = V_ulDivisor/V_ulDividend;

    PF_Ulong32ToBufferX(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer2], &V_ulQuotient, CLNeutralUnbalanceRate);
    /*零线电流异常发生或结束************************************************/
	if( ( (PF_Campare_Data(&V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_ucJudgeBuffer1[C_Judge_StartBuffer3], CLVector_Current) == C_GreaterThan)
            || (PF_Campare_Data(&V_ucJudgeBuffer2[C_Judge_StartBuffer4], &V_ucJudgeBuffer1[C_Judge_StartBuffer3], CLVector_Current) == C_GreaterThan) )/*三相电流矢量和或零线电流大于判断阈值*/
        && (PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeCurr_Buffer2], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], CLNeutralUnbalanceRate) == C_GreaterThan) )/*不平衡率大于判断阀值*/
	{
		return(C_Happen_EventState);
	}
	else
	{
		return(C_End_EventState);
	}
}
/*以下事件判断函数根据事件号顺序罗列，顺序不能修改*/
const Str_EvtJudge Tb_EvtJudgeFunc[] =
{
    SF_Get_TotalVoltageLose_Cstate, 			/*全失压*/
    SF_Get_PeripheralEvt_Cstate,               /*辅助电源失电*/
    SF_Get_Powerfail_Cstate,                   /*掉电*/
    SF_Get_PeripheralEvt_Cstate,               /*开表盖*/
    SF_Get_PeripheralEvt_Cstate,               /*开端钮盖*/
    SF_Get_PeripheralEvt_Cstate,               /*恒定磁场干扰*/
    C_NULL,                                 /*电源异常, 有专门接口函数，此处不做*/
    SF_Get_OverActiveDemand_Cstate,            /*正向有功需量超限*/
    SF_Get_OverActiveDemand_Cstate,            /*反向有功需量超限*/
    SF_Get_OverIdleDemand_Cstate,              /*1象限无功需量超限*/
    SF_Get_OverIdleDemand_Cstate,              /*2象限无功需量超限*/
    SF_Get_OverIdleDemand_Cstate,              /*3象限无功需量超限*/
    SF_Get_OverIdleDemand_Cstate,              /*4象限无功需量超限*/
    SF_Get_lossvoltage_Cstate,                 /*A相失压*/
    SF_Get_lossvoltage_Cstate,                 /*B相失压*/
    SF_Get_lossvoltage_Cstate,                 /*C相失压*/
    SF_Get_Lessvoltage_Cstate,                 /*A相欠压*/
    SF_Get_Lessvoltage_Cstate,                 /*B相欠压*/
    SF_Get_Lessvoltage_Cstate,                 /*C相欠压*/
    SF_Get_Overvoltage_Cstate,                 /*A相过压*/
    SF_Get_Overvoltage_Cstate,                 /*B相过压*/
    SF_Get_Overvoltage_Cstate,                 /*C相过压*/
    SF_Get_Lossphase_Cstate,                   /*A相断相*/
    SF_Get_Lossphase_Cstate,                   /*B相断相*/
    SF_Get_Lossphase_Cstate,                   /*C相断相*/
    SF_Get_ReversephaseVoltage_Cstate,         /*电压逆相序*/
    SF_Get_ReversephaseCurrent_Cstate,         /*电流逆相序*/
    SF_Get_UnbanlanceVoltage_Cstate,           /*电压不平衡*/
    SF_Get_FFUnbanlanceCurrent_Cstate,         /*电流不平衡*/
    SF_Get_Losscurrent_Cstate,                 /*A相失流*/
    SF_Get_Losscurrent_Cstate,                 /*B相失流*/
    SF_Get_Losscurrent_Cstate,                 /*C相失流*/
    SF_Get_Overcurrent_Cstate,                 /*A相过流*/
    SF_Get_Overcurrent_Cstate,                 /*B相过流*/
    SF_Get_Overcurrent_Cstate,                 /*C相过流*/
    SF_Get_Failcurrent_Cstate,                 /*A相断流*/
    SF_Get_Failcurrent_Cstate,                 /*B相断流*/
    SF_Get_Failcurrent_Cstate,                 /*C相断流*/
    SF_Get_FFReversecurrent_Cstate,            /*总功率反向*/
    SF_Get_FFReversecurrent_Cstate,            /*A相功率反向*/
    SF_Get_FFReversecurrent_Cstate,            /*B相功率反向*/
    SF_Get_FFReversecurrent_Cstate,            /*C相功率反向*/
    SF_Get_Overload_Cstate,                    /*A相过载*/
    SF_Get_Overload_Cstate,                    /*B相过载*/
    SF_Get_Overload_Cstate,                    /*C相过载*/
    SF_Get_Overpowerfact_Cstate,               /*总功率因数超下限*/
    SF_Get_FFOverpowerfact_Cstate,             /*A相功率因数超下限*/
    SF_Get_FFOverpowerfact_Cstate,             /*B相功率因数超下限*/
    SF_Get_FFOverpowerfact_Cstate,             /*C相功率因数超下限*/
    SF_Get_FFUnbanlanceCurrent_Cstate,         /*电流严重不平衡*/
    SF_Get_MeterAndClockFa_Cstate, 				/*计量芯片故障*/
    SF_Get_MeterAndClockFa_Cstate,             /*时钟故障*/
    SF_Get_NeutralCurrentAbnormal_Cstate,      /*零线电流异常事件号*/
};
/***********************************************************************************
函数原型：uchar8 SF_Get_Event_Cstate(uchar8 V_ucEventNo, uchar8 V_ucHstate)
功能描述：判断事件当前状态
输入参数：EventNo，Hstate（历史状态）
输出参数：返回事件当前所处状态
返回参数C_IDError             数据标识码错误
           C_Happen_EventState	事件状态，有发生无恢复
          C_End_EventState	  	事件状态，非有发生无恢复
          C_Close_EventState	事件状态，关闭状态
功能说明：判断事件当前状态；
调用机制：事件判断函数调用
备    注：
***********************************************************************************/
uchar8 SF_Get_Event_Cstate(uchar8 V_ucEventNo, uchar8 V_ucEvent_Hstate)
{
	uchar8 V_ucMode;

    if((V_ucEventNo > C_NeutralCurrentAbnormalEventNo) || (V_ucEventNo == C_PowerAbnormalEventNo))
    {
        V_ucMode = C_IDError;
    }
    else
    {
        V_ucMode = Tb_EvtJudgeFunc[V_ucEventNo].EvtJudgeFunc(V_ucEventNo, V_ucEvent_Hstate);
    }

	return(V_ucMode);
}

/***********************************************************************************
函数原型：uchar8 SF_Judge_Event_Statechange(uchar8 V_ucEventNo, uchar8 V_ucDelayTime)
功能描述：判断事件是否有发生/恢复消息发出
输入参数：EventNo（事件号），DelayTime（判断延时时间）
输出参数：返回事件当前所处状态
返回参数C_IDError             数据标识码错误
  		C_Happen_EventMsg	0x68	事件发生动作
  		C_End_EventMsg		0x00	事件恢复动作
  		C_NULL_EventMsg	    0x66	事件无动作
功能说明：判断事件当前是否有消息发出；
调用机制：事件判断函数调用
备    注：
***********************************************************************************/
uchar8 SF_Judge_Event_Statechange(uchar8 V_ucEventNo, uchar8 V_ucDelayTime)
{
	uchar8 V_ucCstate;

	if(V_ucEventNo <= C_NeutralCurrentAbnormalEventNo)
	{
		V_ucCstate = SF_Get_Event_Cstate(V_ucEventNo, GV_ucEvent_Hstate[V_ucEventNo]);

		if( (V_ucCstate == GV_ucEvent_Hstate[V_ucEventNo])
           || ((GV_ucEvent_Hstate[V_ucEventNo] == C_Close_EventState) && (V_ucCstate == C_End_EventState)) )
		{
			GV_ucEvent_JudgeTimer[V_ucEventNo] = C_NULL;
			return(C_Null_EventMsg);
		}
		else
		{
			if(V_ucCstate == C_Close_EventState)
			{
				GV_ucEvent_JudgeTimer[V_ucEventNo] = C_NULL;
				if(GV_ucEvent_Hstate[V_ucEventNo] == C_Happen_EventState)
				{
				    GV_ucEvent_Hstate[V_ucEventNo] = V_ucCstate;
					return(C_End_EventMsg);
				}
				else
				{
				    GV_ucEvent_Hstate[V_ucEventNo] = V_ucCstate;
					return(C_Null_EventMsg);
				}
			}
			else
			{
				if(GV_ucEvent_JudgeTimer[V_ucEventNo] >= V_ucDelayTime)
				{

					if(V_ucCstate == C_Happen_EventState)
					{
					    GV_ucEvent_Hstate[V_ucEventNo] = V_ucCstate;
						return(C_Happen_EventMsg);
					}
					else
					{
					    GV_ucEvent_Hstate[V_ucEventNo] = V_ucCstate;
						return(C_End_EventMsg);
					}
				}
				else
				{
					GV_ucEvent_JudgeTimer[V_ucEventNo] ++;
					return(C_Null_EventMsg);
				}

			}
		}
	}
	else
	{
		return(C_IDError);
	}
}

/***********************************************************************************
函数原型：void SF_AppendEventMessage(uchar8 V_ucEventNo, uchar8 EventMsg)
功能描述：事件发生恢复时，发送消息
输入参数：EventNo，EventMsg（事件动作）, V_ucPowFlag电表电源状态
输出参数：无
返回参数：无；
功能说明：发消息中的时间，上电时用进低功耗时间，有电时用当前时间；
调用机制：上电初始化和事件判断函数调用
备    注：
***********************************************************************************/
void SF_AppendEventMessage(uchar8 V_ucEventNo, uchar8 EventMsg, uchar8 V_ucPowFlag)
{
	uchar8	V_ucDataBuffer[C_Event_MsgLength];				/*缓存*/
	ushort16 V_usDataBufferLength = C_Event_MsgLength, V_usEncode;			/*时间长度*/
	Str_Msg_Parameter	Str_SendMsg;
    ulong32 V_ulDI;

	Str_SendMsg.PowerFlag = C_PowerOn;							/*有电*/
	Str_SendMsg.SourceAddr = C_Msg_PowerNetworkMonitoring;	/*事件判断源消息号*/
	Str_SendMsg.DerictAddr = C_Msg_PowerNetworkMonitoring;	/*事件判断目的消息号*/
	Str_SendMsg.Length = C_Event_MsgLength;						/*事件判断发送接收数据长度*/
	V_ucDataBuffer[C_PTEventNo_Msgbuffer] = PT_EventNo;
	V_ucDataBuffer[C_EventNo_Msgbuffer] = V_ucEventNo;

	Str_SendMsg.Parameter = &V_ucDataBuffer[C_PTEventNo_Msgbuffer];

    if(V_ucPowFlag == C_PowerRising)
    {
        V_ulDI = CEnter_LowPower_Time;
    }
    else
    {
        V_ulDI = CDate_Time;
    }
	if(InF_GetData_ObjectManage(V_ulDI, &V_ucDataBuffer[C_Time_Msgbuffer], &V_usDataBufferLength, &V_usEncode) == C_OK)/*读当前时间*/
	{
		if(EventMsg == C_Happen_EventMsg)
		{
			V_ucDataBuffer[C_PTTime_Msgbuffer] = Pt_HappenTime;
			InF_WriteMessege(&Str_SendMsg);
		}
		else
		{
			if(EventMsg == C_End_EventMsg)
			{
				V_ucDataBuffer[C_PTTime_Msgbuffer] = Pt_EndTime;
				InF_WriteMessege(&Str_SendMsg);
			}
			else
			{
				return;
			}
		}
	}
}

/***********************************************************************************
函数原型：void SF_AppendEventMessageLowPower(uchar8 V_ucEventNo, uchar8 EventMsg)
功能描述：事件发生恢复时，发送消息
输入参数：EventNo，EventMsg（事件动作）
输出参数：返回事件当前所处状态
返回参数：无；
功能说明：判断事件当前状态；
调用机制：事件判断函数调用
备    注：
***********************************************************************************/
void SF_AppendEventMessageLowPower(uchar8 V_ucEventNo, uchar8 EventMsg)
{
	uchar8	V_ucDataBuffer[C_Event_MsgLength];				/*缓存*/
	Str_Msg_Parameter	Str_SendMsg;

	Str_SendMsg.PowerFlag = C_PowerOn;							/*有电*/
	Str_SendMsg.SourceAddr = C_Msg_PowerNetworkMonitoring;	/*事件判断源消息号*/
	Str_SendMsg.DerictAddr = C_Msg_PowerNetworkMonitoring;	/*事件判断目的消息号*/
	Str_SendMsg.Length = C_Event_MsgLength;						/*事件判断发送接收数据长度*/
	V_ucDataBuffer[C_PTEventNo_Msgbuffer] = PT_EventNo;
	V_ucDataBuffer[C_EventNo_Msgbuffer] = V_ucEventNo;
	Str_SendMsg.Parameter = &V_ucDataBuffer[C_PTEventNo_Msgbuffer];

	switch(V_ucEventNo)
	{
		case	C_TotalVoltageLoseEventNo:					   /*全失压低功耗下时间*/
				PF_CopyDataBytes(GStr_TotalvoltageloseStr.Time, &V_ucDataBuffer[C_Time_Msgbuffer], C_EventTimeLength);
				break;
 		case	C_ACPowerFailEventNo:						 	/*辅助电源失电低功耗下时间*/
				PF_CopyDataBytes(GStr_ACPowerFailStr.Time, &V_ucDataBuffer[C_Time_Msgbuffer], C_EventTimeLength);
				break;
		case	C_PowerfailEventNo:						 	 /*掉电低功耗下时间*/
				PF_CopyDataBytes(GStr_PowerfailStr.Time, &V_ucDataBuffer[C_Time_Msgbuffer], C_EventTimeLength);
				break;
		case	C_OpenMeterCoverLowPower:							 /*开表盖功耗下时间*/
                V_ucDataBuffer[C_EventNo_Msgbuffer]=C_OpenMeterCoverEventNo;
				PF_CopyDataBytes(GStr_OpenMeterCoverStr.HappenTime, &V_ucDataBuffer[C_Time_Msgbuffer], C_EventTimeLength);
				break;
		case	C_CloseMeterCoverLowPower:							 /*合表盖功耗下时间*/
				V_ucDataBuffer[C_EventNo_Msgbuffer]=C_OpenMeterCoverEventNo;
                PF_CopyDataBytes(GStr_OpenMeterCoverStr.EndTime, &V_ucDataBuffer[C_Time_Msgbuffer], C_EventTimeLength);
				break;
		case	C_OpenTerminalCoverLowPower:							 /*开端钮盖功耗下时间*/
				V_ucDataBuffer[C_EventNo_Msgbuffer]=C_OpenTerminalCoverEventNo;
                PF_CopyDataBytes(GStr_OpenTerminalCoverStr.HappenTime, &V_ucDataBuffer[C_Time_Msgbuffer], C_EventTimeLength);
				break;
		case	C_CloseTerminalCoverLowPower:							 /*合端钮盖功耗下时间*/
				V_ucDataBuffer[C_EventNo_Msgbuffer]=C_OpenTerminalCoverEventNo;
                PF_CopyDataBytes(GStr_OpenTerminalCoverStr.EndTime, &V_ucDataBuffer[C_Time_Msgbuffer], C_EventTimeLength);
				break;
		default:
				break;
	}

	if(EventMsg == C_Happen_EventMsg)
	{
		V_ucDataBuffer[C_PTTime_Msgbuffer] = Pt_HappenTime;
		InF_WriteMessege(&Str_SendMsg);
	}
	else
	{
		if(EventMsg == C_End_EventMsg)
		{
			V_ucDataBuffer[C_PTTime_Msgbuffer] = Pt_EndTime;
			InF_WriteMessege(&Str_SendMsg);
		}
		else
		{
			return;
		}
	}
}
/***********************************************************************************
函数原型：void SF_Judge_Event_Msg(uchar8 V_ucEventNo, uchar8 EventMsg)
功能描述：事件发生恢复时，发送消息
输入参数：EventNo，EventMsg（事件动作）
输出参数：返回事件当前所处状态
返回参数：无；
功能说明：判断事件当前状态；
调用机制：事件判断函数调用
备    注：
***********************************************************************************/
void SF_Judge_Event_Msg(void)
{
	uchar8	V_ucDelayTime, V_ucEventNo, V_ucEventMsg;
	uchar8	V_ucPhase;
	uchar8	V_ucDataTemp = 0;
    ushort16 V_usEncode, V_usDataLen;

    V_usDataLen = CLLine_Type;
	InF_GetData_ObjectManage(CLine_Type, &V_ucPhase, &V_usDataLen, &V_usEncode);					/*读电能表类型，三相三线/三相四线*/

	for(V_ucEventNo = C_TotalVoltageLoseEventNo;V_ucEventNo <= C_NeutralCurrentAbnormalEventNo;V_ucEventNo ++)
	{
		if( ( (V_ucPhase == C_3P3W) && (Event_ChooseTableNo[V_ucEventNo][C_PhaseTypeRowN0] == C_3P3W) )
           || (V_ucEventNo == C_PowerAbnormalEventNo) )/*三相三线时，B相事件及分相功率因数超限不做*/
		{
			continue;
		}
		if(V_ucEventNo == C_ACPowerFailEventNo)
		{
			V_usDataLen = CLAuxi_Power_Sign;
			if(InF_GetData_ObjectManage(CAuxi_Power_Sign, &V_ucDataTemp, &V_usDataLen, &V_usEncode) != C_OK)
			{
				continue;
			}
			if(V_ucDataTemp == C_NoACPowerFail)
			{
				continue;
			}
		}
		if(V_ucEventNo == C_NeutralCurrentAbnormalEventNo)
		{
			V_usDataLen = CLZero_Current_Sign;
			if(InF_GetData_ObjectManage(CZero_Current_Sign, &V_ucDataTemp, &V_usDataLen, &V_usEncode) == C_OK)/*零线电流类型*/
			{
				if(V_ucDataTemp == C_ZeroCurrentOff)/*无零线电流，直接退出*/
				{
					continue;
				}
			}
		}
		V_ucDelayTime = SF_Get_Event_DalayTime(V_ucEventNo);
		if(V_ucDelayTime == C_JudgeTimeError)
		{
			return;
		}
        V_ucEventMsg = SF_Judge_Event_Statechange(V_ucEventNo, V_ucDelayTime);

        SF_AppendEventMessage(V_ucEventNo, V_ucEventMsg, C_PowerOn);
	}
}
/***********************************************************************************
函数原型：void SF_Str_Clear(void)
功能描述：结构体清零
输入参数：
输出参数：
返回参数：
功能说明：清零时调用
调用机制：
备    注：
***********************************************************************************/
void SF_Str_Clear(uchar8 EventNo)
{
	uchar8 V_ucJudgeBuffer1[C_Judge_50BufferLength]={C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL
                , C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL
                , C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL
                , C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL};

	PF_CopyDataBytes_698(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], CommunicateEventClearTable[EventNo].P_Str, CommunicateEventClearTable[EventNo].Length);
}
/***********************************************************************************
函数原型：void SF_Str_CalCRC(uchar8	EventNo)
功能描述：计算结构体CRC
输入参数：
输出参数：
返回参数：
功能说明：清零时调用
调用机制：
备    注：
***********************************************************************************/
void SF_Str_CalCRC(uchar8	EventNo)
{
	ushort16 V_usCRC, V_usLength = (CommunicateEventClearTable[EventNo].Length - C_CRC_Length);/*结构体数据长度*/

	V_usCRC = PF_Cal_CRC(CommunicateEventClearTable[EventNo].P_Str, V_usLength);

	PF_Ushort16ToBuffer2(CommunicateEventClearTable[EventNo].P_CRCAddr, &V_usCRC);
}
/***********************************************************************************
函数原型：uchar8 SF_Str_CheckCRC(uchar8	EventNo)
功能描述：check结构体CRC
输入参数：
输出参数：
返回参数：
功能说明：清零时调用
调用机制：
备    注：
***********************************************************************************/
uchar8 SF_Str_CheckCRC(uchar8	EventNo)
{
	uchar8	V_ucReturnFlag;

	V_ucReturnFlag = PF_Check_CRC(CommunicateEventClearTable[EventNo].P_Str, CommunicateEventClearTable[EventNo].Length);

    if(EventNo == C_MagneticCheckEventNo)
    {
        V_ucReturnFlag = C_OK;
    }
	return V_ucReturnFlag;
}

/***********************************************************************************
函数原型：void SF_SymbolDisplay_Judgemsg(void)
功能描述：显示符号函数
输入参数：
输出参数：
返回参数：
功能说明：判断消息发生时触发
调用机制：判断消息触发
备    注：
***********************************************************************************/
void SF_SymbolDisplay_Judgemsg(void)
{
	uchar8		V_uci, V_ucPhase;
	uchar8		V_ucDisplayBuffer[10];
	uchar8 		V_ucEvent_SymbolCstate[C_EventSymbolLength];
	Str_Msg_Parameter	Str_Event_DisplayMsg;
    ushort16    V_usPhaseLength = 1, V_usEncode;

    if( (GV_ucEvent_Hstate[C_ALossphaseEventNo] == C_Happen_EventState)
       || ((GV_ucEvent_Hstate[C_PowerfailEventNo] == C_Happen_EventState) && (GV_ucEvent_Hstate[C_TotalVoltageLoseEventNo] != C_Happen_EventState)) )//全失压和掉电同时发生，符号看全失压，闪烁
    {
        V_ucEvent_SymbolCstate[C_AVoltage_SymbolNO] = C_NotDisplay;
    }
    else
	{
        if( (GV_ucEvent_Hstate[C_AlossvoltageEventNo] == C_Happen_EventState)
           || (GV_ucEvent_Hstate[C_TotalVoltageLoseEventNo] == C_Happen_EventState) )
        {
            V_ucEvent_SymbolCstate[C_AVoltage_SymbolNO] = C_TwinkleDisplay;
        }
		else
		{
			V_ucEvent_SymbolCstate[C_AVoltage_SymbolNO] = C_AlwaysDisplay;
		}
	}
    InF_GetData_ObjectManage(CLine_Type, &V_ucPhase, &V_usPhaseLength, &V_usEncode);		/*读电能表类型，三相三线/三相四线*/

    if( (V_ucPhase==C_3P3W) || (GV_ucEvent_Hstate[C_BLossphaseEventNo] == C_Happen_EventState)
       || ((GV_ucEvent_Hstate[C_PowerfailEventNo] == C_Happen_EventState) && (GV_ucEvent_Hstate[C_TotalVoltageLoseEventNo] != C_Happen_EventState)) )/*全失压和掉电同时发生，符号看全失压，闪烁*/
    {
        V_ucEvent_SymbolCstate[C_BVoltage_SymbolNO] = C_NotDisplay;
    }
    else
    {
        if((GV_ucEvent_Hstate[C_BlossvoltageEventNo] == C_Happen_EventState) || (GV_ucEvent_Hstate[C_TotalVoltageLoseEventNo] == C_Happen_EventState) )
        {
            V_ucEvent_SymbolCstate[C_BVoltage_SymbolNO] = C_TwinkleDisplay;
        }
        else
        {
            V_ucEvent_SymbolCstate[C_BVoltage_SymbolNO] = C_AlwaysDisplay;
        }
    }


    if( (GV_ucEvent_Hstate[C_CLossphaseEventNo] == C_Happen_EventState)
       || ((GV_ucEvent_Hstate[C_PowerfailEventNo] == C_Happen_EventState) && (GV_ucEvent_Hstate[C_TotalVoltageLoseEventNo] != C_Happen_EventState)) )/*全失压和掉电同时发生，符号看全失压，闪烁*/
    {
        V_ucEvent_SymbolCstate[C_CVoltage_SymbolNO] = C_NotDisplay;
    }
	else
	{

        if((GV_ucEvent_Hstate[C_ClossvoltageEventNo] == C_Happen_EventState) || (GV_ucEvent_Hstate[C_TotalVoltageLoseEventNo] == C_Happen_EventState))
        {
            V_ucEvent_SymbolCstate[C_CVoltage_SymbolNO] = C_TwinkleDisplay;
        }
		else
		{
			V_ucEvent_SymbolCstate[C_CVoltage_SymbolNO] = C_AlwaysDisplay;
		}
	}

    if( (GV_ucEvent_Hstate[C_ALossphaseEventNo] == C_Happen_EventState)
       || ((GV_ucEvent_Hstate[C_PowerfailEventNo] == C_Happen_EventState) && (GV_ucEvent_Hstate[C_TotalVoltageLoseEventNo] != C_Happen_EventState)) )/*全失压和掉电同时发生，符号看全失压，闪烁*/
    {
      	V_ucEvent_SymbolCstate[C_ACurrentminus_SymbolNO] = C_NotDisplay;/*断相或者掉电，符号关闭*/
		V_ucEvent_SymbolCstate[C_ACurrent_SymbolNO] = C_NotDisplay;
    }
    else
    {
        if(GV_ucEvent_Hstate[C_ALosscurrentEventNo] == C_Happen_EventState)
        {
            V_ucEvent_SymbolCstate[C_ACurrentminus_SymbolNO] = C_TwinkleDisplay;
            V_ucEvent_SymbolCstate[C_ACurrent_SymbolNO] = C_TwinkleDisplay;
        }
        else
        {
            if(GV_ucEvent_Hstate[C_AFailcurrentEventNo] == C_Happen_EventState)
            {
                V_ucEvent_SymbolCstate[C_ACurrentminus_SymbolNO] = C_NotDisplay;
                V_ucEvent_SymbolCstate[C_ACurrent_SymbolNO] = C_NotDisplay;
            }
            else
            {
                V_ucEvent_SymbolCstate[C_ACurrentminus_SymbolNO] = C_AlwaysDisplay;
                V_ucEvent_SymbolCstate[C_ACurrent_SymbolNO] = C_AlwaysDisplay;
            }
        }
    }

    if( (V_ucPhase == C_3P3W) || (GV_ucEvent_Hstate[C_BLossphaseEventNo] == C_Happen_EventState)
       || ((GV_ucEvent_Hstate[C_PowerfailEventNo] == C_Happen_EventState) && (GV_ucEvent_Hstate[C_TotalVoltageLoseEventNo] != C_Happen_EventState)) )/*全失压和掉电同时发生，符号看全失压，闪烁*/
    {
      	V_ucEvent_SymbolCstate[C_BCurrentminus_SymbolNO] = C_NotDisplay;/*断相或者掉电，符号关闭*/
		V_ucEvent_SymbolCstate[C_BCurrent_SymbolNO] = C_NotDisplay;
    }
    else
    {
        if(GV_ucEvent_Hstate[C_BLosscurrentEventNo] == C_Happen_EventState)
        {
            V_ucEvent_SymbolCstate[C_BCurrentminus_SymbolNO] = C_TwinkleDisplay;
            V_ucEvent_SymbolCstate[C_BCurrent_SymbolNO] = C_TwinkleDisplay;
        }
        else
        {
            if(GV_ucEvent_Hstate[C_BFailcurrentEventNo] == C_Happen_EventState)
            {
                V_ucEvent_SymbolCstate[C_BCurrentminus_SymbolNO] = C_NotDisplay;
                V_ucEvent_SymbolCstate[C_BCurrent_SymbolNO] = C_NotDisplay;
            }
            else
            {
                V_ucEvent_SymbolCstate[C_BCurrentminus_SymbolNO] = C_AlwaysDisplay;
                V_ucEvent_SymbolCstate[C_BCurrent_SymbolNO] = C_AlwaysDisplay;
            }
        }
    }

    if( (GV_ucEvent_Hstate[C_CLossphaseEventNo] == C_Happen_EventState)
       || ((GV_ucEvent_Hstate[C_PowerfailEventNo] == C_Happen_EventState) && (GV_ucEvent_Hstate[C_TotalVoltageLoseEventNo] != C_Happen_EventState)) )/*全失压和掉电同时发生，符号看全失压，闪烁*/
    {
      	V_ucEvent_SymbolCstate[C_CCurrentminus_SymbolNO] = C_NotDisplay;/*断相或者掉电，符号关闭*/
		V_ucEvent_SymbolCstate[C_CCurrent_SymbolNO] = C_NotDisplay;
    }
    else
    {
        if(GV_ucEvent_Hstate[C_CLosscurrentEventNo] == C_Happen_EventState)
        {
            V_ucEvent_SymbolCstate[C_CCurrentminus_SymbolNO] = C_TwinkleDisplay;
            V_ucEvent_SymbolCstate[C_CCurrent_SymbolNO] = C_TwinkleDisplay;
        }
        else
        {
            if(GV_ucEvent_Hstate[C_CFailcurrentEventNo] == C_Happen_EventState)
            {
                V_ucEvent_SymbolCstate[C_CCurrentminus_SymbolNO] = C_NotDisplay;
                V_ucEvent_SymbolCstate[C_CCurrent_SymbolNO] = C_NotDisplay;
            }
            else
            {
                V_ucEvent_SymbolCstate[C_CCurrentminus_SymbolNO] = C_AlwaysDisplay;
                V_ucEvent_SymbolCstate[C_CCurrent_SymbolNO] = C_AlwaysDisplay;
            }
        }
    }

	if( (GV_ucEvent_Hstate[C_ReversephaseVoltageEventNo] == C_Happen_EventState) || (GV_ucEvent_Hstate[C_ReversephaseCurrentEventNo] == C_Happen_EventState))
	{
		V_ucEvent_SymbolCstate[C_Reversephase_SymbolNO] = C_AlwaysDisplay;
	}
	else
	{
		V_ucEvent_SymbolCstate[C_Reversephase_SymbolNO] = C_NotDisplay;
	}
	for(V_uci = C_AVoltage_SymbolNO;V_uci <= C_Reversephase_SymbolNO;V_uci ++)
	{
		if(V_ucEvent_SymbolCstate[V_uci] != GV_ucEvent_SymbolHstate[V_uci])
		{
			Str_Event_DisplayMsg.PowerFlag = C_PowerOn;
			Str_Event_DisplayMsg.SourceAddr = C_Msg_PowerNetworkMonitoring;
			Str_Event_DisplayMsg.DerictAddr = C_Msg_Display;
			if((V_uci >= C_ACurrentminus_SymbolNO) && (V_uci <= C_CCurrent_SymbolNO))/*电流符号发8个字节数据*/
			{
				Str_Event_DisplayMsg.Length = 8;
			}
			else
			{
				Str_Event_DisplayMsg.Length = 4;														/*电压符号、逆相序发4个字节*/
			}
			V_ucDisplayBuffer[C_DisplayMsgPT1] = Pt_DisplayStatus;
			V_ucDisplayBuffer[C_DisplayMsgTime1H] = 0xFF;			/*闪烁时间，本模块不做处理，由显示处理。按照常显时间FF来设置*/
			V_ucDisplayBuffer[C_DisplayMsgTime1L] = 0xFF;
            V_ucDisplayBuffer[C_DisplayMsgPT2] = Pt_DisplayStatus;
            V_ucDisplayBuffer[C_DisplayMsgTime2H] = 0xFF;			/*闪烁时间，本模块不做处理，由显示处理。按照常显时间FF来设置*/
            V_ucDisplayBuffer[C_DisplayMsgTime2L] = 0xFF;
            if(V_uci == C_AVoltage_SymbolNO)						/*A相电压符号*/
			{
				V_ucDisplayBuffer[C_DisplayMsgType1] = (V_ucEvent_SymbolCstate[V_uci] | C_UaSign);
			}
			if(V_uci == C_BVoltage_SymbolNO)						/*B相电压符号*/
			{
				V_ucDisplayBuffer[C_DisplayMsgType1] = (V_ucEvent_SymbolCstate[V_uci] | C_UbSign);
			}
			if(V_uci==C_CVoltage_SymbolNO)						/*C相电压符号*/
			{
				V_ucDisplayBuffer[C_DisplayMsgType1] = (V_ucEvent_SymbolCstate[V_uci] | C_UcSign);
			}
			if(V_uci == C_ACurrent_SymbolNO)						/*A相电流符号。负号和电流符号默认都同时处理*/
			{
				if(V_ucEvent_SymbolCstate[V_uci] == C_TwinkleDisplay)
				{
					V_ucDisplayBuffer[C_DisplayMsgType1] = (C_TwinkleDisplay | C_IaNegativeSign);
					V_ucDisplayBuffer[C_DisplayMsgType2] = (C_TwinkleDisplay | C_IaSign);
				}
				if(V_ucEvent_SymbolCstate[V_uci] == C_AlwaysDisplay)
				{
					V_ucDisplayBuffer[C_DisplayMsgType1] = (C_AlwaysDisplay | C_IaNegativeSign);
					V_ucDisplayBuffer[C_DisplayMsgType2] = (C_AlwaysDisplay | C_IaSign);
				}
				if(V_ucEvent_SymbolCstate[V_uci] == C_NotDisplay)
				{
					V_ucDisplayBuffer[C_DisplayMsgType1] = (C_NotDisplay | C_IaNegativeSign);
					V_ucDisplayBuffer[C_DisplayMsgType2] = (C_NotDisplay | C_IaSign);
				}
			}
			if(V_uci == C_ACurrentminus_SymbolNO)
			{
				continue;
			}
			if(V_uci == C_BCurrent_SymbolNO)					/*A相电流符号。负号和电流符号默认都同时处理*/
			{
				if(V_ucEvent_SymbolCstate[V_uci] == C_TwinkleDisplay)
				{
					V_ucDisplayBuffer[C_DisplayMsgType1] = (C_TwinkleDisplay | C_IbNegativeSign);
					V_ucDisplayBuffer[C_DisplayMsgType2] = (C_TwinkleDisplay | C_IbSign);
				}
				if(V_ucEvent_SymbolCstate[V_uci] == C_AlwaysDisplay)
				{
					V_ucDisplayBuffer[C_DisplayMsgType1] = (C_AlwaysDisplay | C_IbNegativeSign);
					V_ucDisplayBuffer[C_DisplayMsgType2] = (C_AlwaysDisplay | C_IbSign);
				}
				if(V_ucEvent_SymbolCstate[V_uci] == C_NotDisplay)
				{
					V_ucDisplayBuffer[C_DisplayMsgType1] = (C_NotDisplay | C_IbNegativeSign);
					V_ucDisplayBuffer[C_DisplayMsgType2] = (C_NotDisplay | C_IbSign);
				}
			}
			if(V_uci == C_BCurrentminus_SymbolNO)
			{
				continue;
			}
			if(V_uci == C_CCurrent_SymbolNO)			/*A相电流符号。负号和电流符号默认都同时处理*/
			{
				if(V_ucEvent_SymbolCstate[V_uci] == C_TwinkleDisplay)
				{
					V_ucDisplayBuffer[C_DisplayMsgType1] = (C_TwinkleDisplay | C_IcNegativeSign);
					V_ucDisplayBuffer[C_DisplayMsgType2] = (C_TwinkleDisplay | C_IcSign);
				}
				if(V_ucEvent_SymbolCstate[V_uci] == C_AlwaysDisplay)
				{
					V_ucDisplayBuffer[C_DisplayMsgType1] = (C_AlwaysDisplay | C_IcNegativeSign);
					V_ucDisplayBuffer[C_DisplayMsgType2] = (C_AlwaysDisplay | C_IcSign);
				}
				if(V_ucEvent_SymbolCstate[V_uci] == C_NotDisplay)
				{
					V_ucDisplayBuffer[C_DisplayMsgType1] = (C_NotDisplay | C_IcNegativeSign);
					V_ucDisplayBuffer[C_DisplayMsgType2] = (C_NotDisplay | C_IcSign);
				}
			}
			if(V_uci == C_CCurrentminus_SymbolNO)
			{
				continue;
			}
			if(V_uci == C_Reversephase_SymbolNO)		/*逆相序发生，常显或者关闭*/
			{
				if(V_ucEvent_SymbolCstate[V_uci] == C_AlwaysDisplay)
				{
					V_ucDisplayBuffer[C_DisplayMsgType1] = (C_AlwaysDisplay | C_NegativePhaseSign);
				}
				if(V_ucEvent_SymbolCstate[C_Reversephase_SymbolNO] == C_NotDisplay)
				{
					V_ucDisplayBuffer[C_DisplayMsgType1] = (C_NotDisplay | C_NegativePhaseSign);
				}
			}
			Str_Event_DisplayMsg.Parameter = &V_ucDisplayBuffer[0];
			InF_WriteMessege(&Str_Event_DisplayMsg);/*发消息*/
			GV_ucEvent_SymbolHstate[V_uci] = V_ucEvent_SymbolCstate[V_uci];	/*对显示符号历史状态赋值*/
		}
	}
}
/***********************************************************************************
函数原型：void SF_AlarmDisplay_Judgemsg(void)
功能描述：报警函数
输入参数:
输出参数：
返回参数：
功能说明：判断消息发生时触发
调用机制：判断消息触发
备    注：
***********************************************************************************/
void SF_AlarmDisplay_Judgemsg(void)
 {
	uchar8	V_ucAlarmModeReturnData[C_AlarmModeLength];	/*读报警模式字用*/
	ushort16 V_usBufferLength1 = C_Judge_20BufferLength, V_usEncode;
	uchar8	V_ucBellAlarmTemp[C_AlarmTempLength], V_ucAlarmOuputTemp[C_AlarmTempLength], V_ucBackLightAlarmTemp[C_AlarmTempLength];	/*当前报警和报警模式字的组合*/
	uchar8	V_ucDisplayBuffer[4];
    uchar8  V_ucBufferNull[C_AlarmTempLength] = {0};
    uchar8  V_ucEventNo;
    ulong64 V_ucAlarmCompareTemp, V_ucAlarmHstateCompareTemp;
    uchar8 V_ucBitNo, V_uc1ByteAlarmTemp, V_uc1ByteAlarmHstateTemp, V_ucSendMessageTemp=C_NULL;
	Str_Msg_Parameter	    Str_Event_DisplayMsg;
    uchar8  V_uci, *pV_ucAlarmTemp, *pV_ucHstateTemp, V_ucType, V_ucDisMode;

    PF_CopyDataBytes(&V_ucBufferNull[0], &GStr_BellAlarm.A0_Flag, C_AlarmTempLength);        /*状态字清零*/
    PF_CopyDataBytes(&V_ucBufferNull[0], &GStr_Alarmoutput.A0_Flag, C_AlarmTempLength);
    PF_CopyDataBytes(&V_ucBufferNull[0], &GStr_BackLightAlarm.A0_Flag, C_AlarmTempLength);

	if(InF_GetData_ObjectManage(CAlarm_Status, &V_ucAlarmModeReturnData[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode))/*报警模式字不成功，退出*(从低到高，背光，报警输出，小铃铛)*/
	{
		return;
	}
	for(V_ucEventNo = C_TotalVoltageLoseEventNo;V_ucEventNo <= C_SUnbanlanceCurrentEventNo;V_ucEventNo ++)
    {
        if(GV_ucEvent_Hstate[V_ucEventNo] == C_Happen_EventState)
        {		/*事件发生*/
            *(CommunicateEventClearTable[V_ucEventNo].P_BackLightAlarm) |= CommunicateEventClearTable[V_ucEventNo].V_AlarmStart;	/*背光状态置位*/
            *(CommunicateEventClearTable[V_ucEventNo].P_AlarmOuput) |= CommunicateEventClearTable[V_ucEventNo].V_AlarmStart;		/*报警输出状态置位*/
            *(CommunicateEventClearTable[V_ucEventNo].P_BellAlarm) |= CommunicateEventClearTable[V_ucEventNo].V_AlarmStart;		/*小铃铛当前状态置位*/
        }
        else
        {
            if(V_ucEventNo == C_OverForwardActiveEventNo)
            {
                if(GV_ucEvent_Hstate[C_OverReverseActiveEventNo] == C_Happen_EventState)
                {
                    continue;
                }
            }
            if(V_ucEventNo == C_OverReverseActiveEventNo)
            {
                if(GV_ucEvent_Hstate[C_OverForwardActiveEventNo] == C_Happen_EventState)
                {
                    continue;
                }
            }
            *(CommunicateEventClearTable[V_ucEventNo].P_BackLightAlarm)&=CommunicateEventClearTable[V_ucEventNo].V_AlarmClose;	/*背光状态置位*//*考虑潮流反向*/
            *(CommunicateEventClearTable[V_ucEventNo].P_AlarmOuput)&=CommunicateEventClearTable[V_ucEventNo].V_AlarmClose;		/*报警输出状态置位*/
            *(CommunicateEventClearTable[V_ucEventNo].P_BellAlarm)&=CommunicateEventClearTable[V_ucEventNo].V_AlarmClose;		/*小铃铛当前状态置位*/
        }
    }

    PF_CopyDataBytes(&GStr_BackLightAlarm.A0_Flag, &V_ucBackLightAlarmTemp[C_Judge_StartBuffer0], C_AlarmTempLength);
    PF_CopyDataBytes(&GStr_Alarmoutput.A0_Flag, &V_ucAlarmOuputTemp[C_Judge_StartBuffer0], C_AlarmTempLength);
    PF_CopyDataBytes(&GStr_BellAlarm.A0_Flag, &V_ucBellAlarmTemp[C_Judge_StartBuffer0], C_AlarmTempLength);

    V_ucBackLightAlarmTemp[0] &= V_ucAlarmModeReturnData[C_BacklightAlarm_ABC0ByteNo];
    V_ucBackLightAlarmTemp[1] &= V_ucAlarmModeReturnData[C_BacklightAlarm_ABC1ByteNo];
    V_ucBackLightAlarmTemp[2] &= V_ucAlarmModeReturnData[C_BacklightAlarm_ABC0ByteNo];
    V_ucBackLightAlarmTemp[3] &= V_ucAlarmModeReturnData[C_BacklightAlarm_ABC1ByteNo];
    V_ucBackLightAlarmTemp[4] &= V_ucAlarmModeReturnData[C_BacklightAlarm_ABC0ByteNo];
    V_ucBackLightAlarmTemp[5] &= V_ucAlarmModeReturnData[C_BacklightAlarm_ABC1ByteNo];
    V_ucBackLightAlarmTemp[6] &= V_ucAlarmModeReturnData[C_BacklightAlarm_T0ByteNo];
    V_ucBackLightAlarmTemp[7] &= V_ucAlarmModeReturnData[C_BacklightAlarm_T1ByteNo];

    V_ucAlarmOuputTemp[0] &= V_ucAlarmModeReturnData[C_Alarmoutput_ABC0ByteNo];
    V_ucAlarmOuputTemp[1] &= V_ucAlarmModeReturnData[C_Alarmoutput_ABC1ByteNo];
    V_ucAlarmOuputTemp[2] &= V_ucAlarmModeReturnData[C_Alarmoutput_ABC0ByteNo];
    V_ucAlarmOuputTemp[3] &= V_ucAlarmModeReturnData[C_Alarmoutput_ABC1ByteNo];
    V_ucAlarmOuputTemp[4] &= V_ucAlarmModeReturnData[C_Alarmoutput_ABC0ByteNo];
    V_ucAlarmOuputTemp[5] &= V_ucAlarmModeReturnData[C_Alarmoutput_ABC1ByteNo];
    V_ucAlarmOuputTemp[6] &= V_ucAlarmModeReturnData[C_Alarmoutput_T0ByteNo];
    V_ucAlarmOuputTemp[7] &= V_ucAlarmModeReturnData[C_Alarmoutput_T1ByteNo];

	V_ucBellAlarmTemp[0] &= V_ucAlarmModeReturnData[C_BellAlarm_ABC0ByteNo];
    V_ucBellAlarmTemp[1] &= V_ucAlarmModeReturnData[C_BellAlarm_ABC1ByteNo];
    V_ucBellAlarmTemp[2] &= V_ucAlarmModeReturnData[C_BellAlarm_ABC0ByteNo];
    V_ucBellAlarmTemp[3] &= V_ucAlarmModeReturnData[C_BellAlarm_ABC1ByteNo];
    V_ucBellAlarmTemp[4] &= V_ucAlarmModeReturnData[C_BellAlarm_ABC0ByteNo];
    V_ucBellAlarmTemp[5] &= V_ucAlarmModeReturnData[C_BellAlarm_ABC1ByteNo];
    V_ucBellAlarmTemp[6] &= V_ucAlarmModeReturnData[C_BellAlarm_T0ByteNo];
    V_ucBellAlarmTemp[7] &= V_ucAlarmModeReturnData[C_BellAlarm_T1ByteNo];

    for(V_uci = 0;V_uci < 2;V_uci ++)
    {
        if(V_uci == 0)/*小铃铛符号*/
        {
            pV_ucAlarmTemp = &V_ucBellAlarmTemp[0];
            pV_ucHstateTemp = &GV_ucBellAlarm_Hstate[0];

            V_ucType = C_AlarmSign;
            V_ucDisMode = C_TwinkleDisplay;
        }
        else if(V_uci == 1)/*报警输出*/
        {
            pV_ucAlarmTemp = &V_ucAlarmOuputTemp[0];
            pV_ucHstateTemp = &GV_ucAlarmoutput_Hstate[0];

            V_ucType = C_WarnOutPut;
            V_ucDisMode = C_AlwaysDisplay;
        }
        else/*背光灯*/
        {
            pV_ucAlarmTemp = &V_ucBackLightAlarmTemp[0];
            pV_ucHstateTemp = &GV_ucBackLightAlarm_Hstate[0];

            V_ucType = C_BackLED;
            V_ucDisMode = C_AlwaysDisplay;
        }
        if(PF_Campare_Data(pV_ucAlarmTemp, pV_ucHstateTemp, C_AlarmTempLength)!=C_Equal)
        {
            Str_Event_DisplayMsg.PowerFlag = C_PowerOn;
            Str_Event_DisplayMsg.SourceAddr = C_Msg_PowerNetworkMonitoring;
            Str_Event_DisplayMsg.DerictAddr = C_Msg_Display;
            Str_Event_DisplayMsg.Length = 4;
            V_ucDisplayBuffer[C_DisplayMsgPT1] = Pt_DisplayStatus;
            V_ucDisplayBuffer[C_DisplayMsgTime1H] = 0xFF;			/*闪烁时间，本模块不做处理，由显示处理。按照常显时间FF来设置*/
            V_ucDisplayBuffer[C_DisplayMsgTime1L] = 0xFF;
            if(PF_Campare_Data(pV_ucAlarmTemp, &V_ucBufferNull[0], C_AlarmTempLength) == C_Equal)							/*当前状态为0，取消报警*/
            {
                V_ucDisplayBuffer[C_DisplayMsgType1] = C_NotDisplay|C_AlarmSign;
                Str_Event_DisplayMsg.Parameter=&V_ucDisplayBuffer[C_DisplayMsgPT1];
                InF_WriteMessege(&Str_Event_DisplayMsg);/*发消息*/
            }
            else
            {
                PF_Buffer8ToUlong64(&pV_ucAlarmTemp[0], &V_ucAlarmCompareTemp, C_AlarmTempLength);
                PF_Buffer8ToUlong64(&pV_ucHstateTemp[0], &V_ucAlarmHstateCompareTemp, C_AlarmTempLength);
                for(V_ucBitNo = C_NULL;V_ucBitNo < C_AlarmTempBitLength;V_ucBitNo ++)
                {
                    V_uc1ByteAlarmTemp = (V_ucAlarmCompareTemp>>V_ucBitNo)&C_Bit0_Start;
                    V_uc1ByteAlarmHstateTemp = (V_ucAlarmHstateCompareTemp>>V_ucBitNo)&C_Bit0_Start;
                    if( (V_uc1ByteAlarmTemp == C_CurrentBitAlarmHappen)
                       && (V_uc1ByteAlarmHstateTemp == C_NULL) )
                    {
                        V_ucSendMessageTemp = C_SendAlarmMessage;
                        break;
                    }
                }
                if(V_ucSendMessageTemp == C_SendAlarmMessage)
                {
                    V_ucDisplayBuffer[C_DisplayMsgType1] = V_ucDisMode | V_ucType;
                    Str_Event_DisplayMsg.Parameter = &V_ucDisplayBuffer[C_DisplayMsgPT1];
                    InF_WriteMessege(&Str_Event_DisplayMsg);/*发消息*/
                    V_ucSendMessageTemp = C_NULL;             /*消息标识置0*/
                }
            }
            PF_CopyDataBytes(&pV_ucAlarmTemp[0], &pV_ucHstateTemp[0], C_AlarmTempLength);
        }
        else if(V_uci == 1)/*报警输出需要增加处理*/
        {
            if(V_ucAlarmOuputTemp[6] &= 0x08)
            {
                if(GV_ucDirectionExchange == ReversecurrentHappen)
                {
                    Str_Event_DisplayMsg.PowerFlag = C_PowerOn;
                    Str_Event_DisplayMsg.SourceAddr = C_Msg_PowerNetworkMonitoring;
                    Str_Event_DisplayMsg.DerictAddr = C_Msg_Display;
                    Str_Event_DisplayMsg.Length = 4;
                    V_ucDisplayBuffer[C_DisplayMsgTime1H] = 0xFF;			/*闪烁时间，本模块不做处理，由显示处理。按照常显时间FF来设置*/
                    V_ucDisplayBuffer[C_DisplayMsgTime1L] = 0xFF;
                    V_ucDisplayBuffer[C_DisplayMsgPT1] = Pt_DisplayStatus;
                    V_ucDisplayBuffer[C_DisplayMsgType1] = C_AlwaysDisplay | C_WarnOutPut;
                    Str_Event_DisplayMsg.Parameter = &V_ucDisplayBuffer[C_DisplayMsgPT1];
                    InF_WriteMessege(&Str_Event_DisplayMsg);/*发消息*/
                    GV_ucDirectionExchange = C_NULL;
                }
            }
        }
    }
}
/***********************************************************************************
函数原型：void SF_PowerSupplyType(void)
功能描述：判断当前系统供电类型，置电表运行状态字
输入参数：无
输出参数：无
返回参数：无
功能说明：
调用机制：每秒调用
备    注：
***********************************************************************************/
void SF_PowerSupplyType(void)
{
    uchar8  V_ucJudgeBuffer1[C_Judge_10BufferLength];
    ushort16 V_usBufferLength1 = C_Judge_10BufferLength, V_usEncode;

    if(InF_GetData_ObjectManage(CMeter_Work_State3, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode)==C_OK)/*电表运行状态字3*/
    {
        V_usBufferLength1 = CLAuxi_Power_Sign;
        if(InF_GetData_ObjectManage(CAuxi_Power_Sign, &V_ucJudgeBuffer1[C_Judge_StartBuffer2], &V_usBufferLength1, &V_usEncode)==C_OK)/*辅助电源类型*/
        {
            if(V_ucJudgeBuffer1[C_Judge_StartBuffer2]==C_ACPowerFail)/*具有辅助电源*/
            {
                if(InF_GetPeripheralStatus(C_CheckAuPower)==C_Invalid)/*辅助电源有电*/
                {/*辅助电源供电*/
                    V_ucJudgeBuffer1[C_Judge_StartBuffer0]&=C_Bit2_End;
                    V_ucJudgeBuffer1[C_Judge_StartBuffer0]|=C_Bit1_Start;/*辅助电源供电*/
                }
                else
                {
                    V_ucJudgeBuffer1[C_Judge_StartBuffer0]&=C_Bit_MainPower;/*主电源供电*/
                }
            }
            else
            {
                V_ucJudgeBuffer1[C_Judge_StartBuffer0]&=C_Bit_MainPower;/*主电源供电*/
            }
            InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State3, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag);
        }
    }
}

/***********************************************************************************
函数原型：void SF_WR_Meter_Work_State1(void)
功能描述：时钟故障置电表运行状态字1
输入参数：无
输出参数：无
返回参数： 无
功能说明：每秒判断时钟故障状态，电表运行状态字bit15，若发生置1，未发生置0；
调用机制：每秒调用
备    注：
***********************************************************************************/
void SF_WR_Meter_Work_State1(void)
{
	uchar8 V_ucBuffer[2], V_ucData = C_RTC_OK;
	ushort16 V_uslen, V_usEncode;

	/*从数据层时钟故障状态*/
	V_uslen = CLClock_FaultState;
	if( InF_GetData_ObjectManage(CClock_FaultState, &V_ucData, &V_uslen, &V_usEncode) != C_OK )
	{
		return;
	}
	/*更新数据层时钟故障状态标志：故障或正常；首先从数据层读，刷新后再写*/
	V_uslen = CLMeter_Work_State1;
	if(InF_GetData_ObjectManage(CMeter_Work_State1, V_ucBuffer, &V_uslen, &V_usEncode) == C_OK)
	{
        if(V_ucData == C_RTC_OK)
	    {
		    V_ucBuffer[1] &= ~C_RTCERR_MeterWorkState;
	    }
	    else
	    {
		    V_ucBuffer[1] |= C_RTCERR_MeterWorkState;
	    }
	    InF_Write_Data(C_Msg_Dispatch, CMeter_Work_State1, V_ucBuffer, CLMeter_Work_State1, C_W_SafeFlag);
    }
    else
    {
      return;
    }
}
/*******************************************************************************
函数原型：void SF_MeterStatus_Judgemsg(void)
功能描述：置电表运行状态字
输入参数：无
输出参数：无
返回参数：无
调用位置：每秒调用
备    注：
*******************************************************************************/
void SF_MeterStatus_Judgemsg(void)
{
    uchar8 V_ucMeter_WorkState1Temp[C_MeterWorkState_Length] = {C_NULL, C_NULL};
    uchar8 V_ucMeter_WorkState4Temp[C_MeterWorkState_Length] = {C_NULL, C_NULL};
    uchar8 V_ucMeter_WorkState5Temp[C_MeterWorkState_Length] = {C_NULL, C_NULL};
    uchar8 V_ucMeter_WorkState6Temp[C_MeterWorkState_Length] = {C_NULL, C_NULL};
    uchar8 V_ucMeter_WorkState7Temp[C_MeterWorkState_Length] = {C_NULL, C_NULL};
    uchar8 V_ucEventNo, *pV_ucMeterNo = C_NULL;
	ushort16 V_usLen, V_usEncode;

    SF_PowerSupplyType( );		/*电能表供电类型*/

	for( V_ucEventNo = C_TotalVoltageLoseEventNo; V_ucEventNo <= C_MeterFaEventNo; V_ucEventNo++)
    {
		if(CommunicateEventClearTable[V_ucEventNo].P_State != 0)
		{
			if( ( V_ucEventNo == C_AFailcurrentEventNo )
			 || ( V_ucEventNo == C_BFailcurrentEventNo )
			 || ( V_ucEventNo == C_CFailcurrentEventNo )
			 || ( V_ucEventNo == C_SUnbanlanceCurrentEventNo )
			 || ( V_ucEventNo == C_OpenMeterCoverEventNo )
			 || ( V_ucEventNo == C_OpenTerminalCoverEventNo ) )
			{
				if(CommunicateEventClearTable[V_ucEventNo].P_State == CMeter_Work_State4)
				{
					pV_ucMeterNo = &V_ucMeter_WorkState4Temp[1];
				}

				if(CommunicateEventClearTable[V_ucEventNo].P_State == CMeter_Work_State5)
				{
					pV_ucMeterNo = &V_ucMeter_WorkState5Temp[1];
				}

				if(CommunicateEventClearTable[V_ucEventNo].P_State == CMeter_Work_State6)
				{
					pV_ucMeterNo = &V_ucMeter_WorkState6Temp[1];
				}

				if(CommunicateEventClearTable[V_ucEventNo].P_State == CMeter_Work_State7)
				{
					pV_ucMeterNo = &V_ucMeter_WorkState7Temp[1];
				}
			}
			else if(V_ucEventNo == C_MeterFaEventNo)
			{
				if(CommunicateEventClearTable[V_ucEventNo].P_State == CMeter_Work_State1)
				{
					V_usLen = CLMeter_Work_State1;
					if( InF_GetData_ObjectManage(CMeter_Work_State1, V_ucMeter_WorkState1Temp, &V_usLen, &V_usEncode) == C_OK )
					{
						pV_ucMeterNo = &V_ucMeter_WorkState1Temp[0];
					}	/*else 不赋值为NUll*/
				}
			}
			else
			{
				if(CommunicateEventClearTable[V_ucEventNo].P_State == CMeter_Work_State4)
				{
					pV_ucMeterNo = &V_ucMeter_WorkState4Temp[0];
				}

				if(CommunicateEventClearTable[V_ucEventNo].P_State == CMeter_Work_State5)
				{
					pV_ucMeterNo = &V_ucMeter_WorkState5Temp[0];
				}

				if(CommunicateEventClearTable[V_ucEventNo].P_State == CMeter_Work_State6)
				{
					pV_ucMeterNo = &V_ucMeter_WorkState6Temp[0];
				}

				if(CommunicateEventClearTable[V_ucEventNo].P_State == CMeter_Work_State7)
				{
					pV_ucMeterNo = &V_ucMeter_WorkState7Temp[0];
				}

			}
			if(pV_ucMeterNo == C_NULL)
			{
				return;
			}
			if(GV_ucEvent_Hstate[V_ucEventNo] == C_Happen_EventState)
			{
				*pV_ucMeterNo |= CommunicateEventClearTable[V_ucEventNo].V_Happen;
			}
			else
			{
				if(V_ucEventNo==C_OverReverseActiveEventNo)
				{
					if( ( GV_ucEvent_Hstate[C_OverForwardActiveEventNo] == C_Happen_EventState)
					 || ( GV_ucEvent_Hstate[C_1OverIdleDemandEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_2OverIdleDemandEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_3OverIdleDemandEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_4OverIdleDemandEventNo] == C_Happen_EventState ) )
					{
						continue;
					}
				}
				if(V_ucEventNo == C_OverForwardActiveEventNo)
				{
					if( ( GV_ucEvent_Hstate[C_OverReverseActiveEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_1OverIdleDemandEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_2OverIdleDemandEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_3OverIdleDemandEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_4OverIdleDemandEventNo] == C_Happen_EventState ) )
					{
						continue;
					}
				}
				if(V_ucEventNo == C_1OverIdleDemandEventNo)
				{
					if( ( GV_ucEvent_Hstate[C_OverForwardActiveEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_OverReverseActiveEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_2OverIdleDemandEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_3OverIdleDemandEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_4OverIdleDemandEventNo] == C_Happen_EventState ) )
					{
						continue;
					}
				}
				if(V_ucEventNo == C_2OverIdleDemandEventNo)
				{
					if( ( GV_ucEvent_Hstate[C_OverForwardActiveEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_OverReverseActiveEventNo] == C_Happen_EventState)
					 || ( GV_ucEvent_Hstate[C_1OverIdleDemandEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_3OverIdleDemandEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_4OverIdleDemandEventNo] == C_Happen_EventState ) )
					{
						continue;
					}
				}
				if(V_ucEventNo == C_3OverIdleDemandEventNo)
				{
					if( ( GV_ucEvent_Hstate[C_OverForwardActiveEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_OverReverseActiveEventNo]==C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_1OverIdleDemandEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_2OverIdleDemandEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_4OverIdleDemandEventNo] == C_Happen_EventState ) )
					{
						continue;
					}
				}
				if(V_ucEventNo == C_4OverIdleDemandEventNo)
				{
					if( ( GV_ucEvent_Hstate[C_OverForwardActiveEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_OverReverseActiveEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_1OverIdleDemandEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_2OverIdleDemandEventNo] == C_Happen_EventState )
					 || ( GV_ucEvent_Hstate[C_3OverIdleDemandEventNo] == C_Happen_EventState ) )
					{
						continue;
					}
				}
				*pV_ucMeterNo &= CommunicateEventClearTable[V_ucEventNo].V_End;
			}
		}
    }
    InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State1, &V_ucMeter_WorkState1Temp[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag);   /*电表运行状态字1赋值*/
    InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State4, &V_ucMeter_WorkState4Temp[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag);   /*电表运行状态字4赋值*/
    InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State5, &V_ucMeter_WorkState5Temp[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag);   /*电表运行状态字5赋值*/
    InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State6, &V_ucMeter_WorkState6Temp[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag);   /*电表运行状态字6赋值*/
    InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State7, &V_ucMeter_WorkState7Temp[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag);   /*电表运行状态字7赋值*/
    SF_WR_Meter_Work_State1();
}

/*******************************************************************************
函数原型：void Inf_PowerupEventrestore(void)
功能描述：上电事件记录模块初始化
输入参数：
输出参数：
返回参数：
功能说明：对低功耗下事件状态进行判断，处理上电需要恢复的事件
调用机制：上电初始化时调用
备    注：
*******************************************************************************/
void Inf_PowerupEventrestore(void)
{
	uchar8  V_ucJudgeBuffer1[C_Judge_20BufferLength] = {0};			/*上电时间*/
	uchar8  V_ucJudgeBuffer3[C_Judge_20BufferLength] = {0};			/*中间变量缓存*/
	uchar8  V_ucJudgeBuffer4[C_Judge_20BufferLength] = {0};			/*低功耗时间化整*/
	ushort16  V_usBufferLength1 = C_Judge_20BufferLength, V_usEncode;
	uchar8  V_ucEventNo = 0, V_ucSymbolNo = 0, V_ucAlarmNo = 0;
	ulong32 V_ulAddTimeTemp = 0, V_ulSubSec = 0, V_ulAddTime_H = 0;			/*累计时间计算临时变量*/
	uchar8  V_ucReturnData = C_Error;
	uchar8  V_ucDataBuff[300] = {0};
	ushort16 V_usDataLen = 0, V_usOffset = 0;
	uchar8  V_ucEvent_Flag = 0;
	uchar8  V_ucPowerOnTimeTemp[CLDate_Week_Time] = {0};
	uchar8  V_ucV_ucEventState = 0;
	uchar8  V_uci, V_ucEvtNo, V_ucMsg;
    Str_CoverRecord_Type *pStr_strCoverRecord;

	if(InF_GetData_ObjectManage(CDate_Time, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) == C_OK)		/*读系统当前时间*/
	{
		PF_CopyDataBytes_698( V_ucJudgeBuffer1, V_ucPowerOnTimeTemp, CLDate_Week_Time );

		/*电源异常上电初始化*/
  		if( SF_Str_CheckCRC( C_PowerAbnormalEventNo ) == C_OK )
  		{
			/*电源异常CRC正确或数据为全0，走以下流程*/
			if(GStr_PowerabnormalStr.MeterState == C_Happen_EventMsg)
			{
				V_usBufferLength1 = CLPowerFa_Degree;
				InF_GetData_ObjectManage(CPowerFa_Degree, V_ucDataBuff, &V_usBufferLength1, &V_usEncode);							/*赋事件序号*/
				V_usOffset += 4;

				PF_CopyDataBytes(GStr_PowerabnormalStr.Time, &V_ucDataBuff[V_usOffset], C_EventTimeLength);	/*赋事件发生时间，结束时间为00000000000000*/
				V_usOffset += 7;
				V_usOffset += 7;
				V_usOffset += 1;
                V_usOffset += CLEventReport;/*新增上报状态偏移*/

				V_usDataLen = 300 - V_usOffset;		/*剩余buff长度*/
				V_ucEvent_Flag = 0x01;
				if( Inf_GetRecordData(&V_ucDataBuff[V_usOffset], &V_usDataLen, CPowerFa_OADTab, V_ucEvent_Flag) == C_OK )							/*获取关联OAD数据*/
				{
					V_usOffset += V_usDataLen;		/*数据总长度*/
					if( InF_Write_Data(C_Msg_PowerNetworkMonitoring, CPowerFa_Note_1, V_ucDataBuff, V_usOffset, C_W_SafeFlag) == C_OK )		/*事件发生写数据*/
					{
						Inf_EventReport_HP( C_PowerAbnormalEventNo, C_Happen_EventReport );
                        InF_ActiveReportSetting( ActiveReportTable[C_PowerAbnormalEventNo] );
					}

					V_usOffset = 11;
					PF_CopyDataBytes( &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucDataBuff[V_usOffset], C_EventTimeLength );			/*赋事件结束时间*/
					V_usOffset += 7;
					V_usOffset += 1;
                    V_usOffset += CLEventReport;/*新增上报状态偏移*/
					V_usDataLen = 300 - V_usOffset;		/*剩余buff长度*/
					V_ucEvent_Flag = 0x02;
					if( Inf_GetRecordData( &V_ucDataBuff[V_usOffset], &V_usDataLen, CPowerFa_OADTab, V_ucEvent_Flag ) == C_OK )				/*获取关联OAD数据*/
					{
						V_usOffset += V_usDataLen;		/*数据总长度*/
						if(InF_Write_Data(C_Msg_PowerNetworkMonitoring, CPowerFa_Note_1 + 0x00000001, V_ucDataBuff, V_usOffset, C_W_SafeFlag) == C_OK)	/*事件结束写数据*/
						{
							Inf_EventReport_HP(C_PowerAbnormalEventNo, C_End_EventReport);
						}
					}

					PF_CopyDataBytes( GStr_PowerabnormalStr.Time, &V_ucJudgeBuffer4[C_Judge_StartBuffer0], C_EventTimeLength );
					if( PF_TimeSub_Min_698( &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer4[C_Judge_StartBuffer0], &V_ulAddTimeTemp) != C_LessThan )
					{
						SF_Sub_Sec(V_ucJudgeBuffer1[C_Judge_StartBuffer0], V_ucJudgeBuffer4[C_Judge_StartBuffer0], &V_ulSubSec);
						V_ulAddTimeTemp *= 60;
						V_ulAddTimeTemp += V_ulSubSec;

						V_usBufferLength1 = 20;
						if( InF_GetData_ObjectManage( CPowerFa_Time, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_usBufferLength1 , &V_usEncode) == C_OK )
						{
							PF_BufferXToUlong32( V_ucJudgeBuffer3, &V_ulAddTime_H, C_AddTime_Length );		/*转HEX*/
							V_ulAddTimeTemp += V_ulAddTime_H;
							PF_Ulong32ToBufferX( &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_ulAddTimeTemp, C_AddTime_Length );
							InF_Write_Data( C_Msg_PowerNetworkMonitoring, CPowerFa_Time, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_AddTime_Length, C_W_SafeFlag );		/*事件累计时间写数据*/
						}
					}
				}
				SF_Str_Clear(C_PowerAbnormalEventNo);				/*清零*/
				GStr_PowerabnormalStr.MeterState=C_Null_EventMsg;		/*低功耗状态赋无动作*/
				SF_Str_CalCRC(C_PowerAbnormalEventNo);				/*低功耗结构体算CRC*/
			}
  		}
  		else
		{
			SF_Str_Clear(C_PowerAbnormalEventNo);				/*清零*/
			GStr_PowerabnormalStr.MeterState=C_Null_EventMsg;		/*低功耗状态赋无动作*/
			SF_Str_CalCRC(C_PowerAbnormalEventNo);				/*低功耗结构体算CRC*/
		}

		GV_ucEvent_Hstate[C_PowerAbnormalEventNo] = C_End_EventState;				/*电源异常结束*/
        /*开表盖和开端钮盖初始化合并处理*/
        for(V_uci = 0;V_uci < 2;V_uci ++)
        {
            if(V_uci == 0)/*开表盖初始化*/
            {
                V_ucEvtNo = C_OpenMeterCoverEventNo;
                V_ucMsg = C_OpenMeterCoverLowPower;
                pStr_strCoverRecord = &GStr_OpenMeterCoverStr;
            }
            else/*开端钮盖初始化*/
            {
                V_ucEvtNo = C_OpenTerminalCoverEventNo;
                V_ucMsg = C_OpenTerminalCoverLowPower;
                pStr_strCoverRecord = &GStr_OpenTerminalCoverStr;

                PF_CopyDataBytes_698( V_ucPowerOnTimeTemp, V_ucJudgeBuffer1, CLDate_Week_Time );
            }

            if( SF_Str_CheckCRC( V_ucEvtNo ) == C_OK )
            {
                V_usBufferLength1 = CLEnter_LowPower_Time;
                InF_GetData_ObjectManage( CEnter_LowPower_Time, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_usBufferLength1 , &V_usEncode);		/*进入低功耗时间*/

                uchar8 TempFlag2 = C_OK;
                if( pStr_strCoverRecord->OpenCoverState == C_LowPowerHappen_EventMsg )
                {
                    PF_CopyDataBytes(pStr_strCoverRecord->HappenTime, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_EventTimeLength);
                    SF_AppendEventMessageLowPower(V_ucMsg, C_Happen_EventMsg);						/*发送事件发生写消息*/
                    GV_ucEvent_Hstate[V_ucEvtNo] = C_Happen_EventState;									/*历史状态赋值*/
                    TempFlag2 = C_Error;
                }

                if(pStr_strCoverRecord->CloseCoverState == C_LowPowerEnd_EventMsg)
                {
                    PF_CopyDataBytes(pStr_strCoverRecord->EndTime, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_EventTimeLength);
                    SF_AppendEventMessageLowPower(V_ucMsg, C_End_EventMsg);						/*发送事件结束写消息*/
                    TempFlag2 = C_Error;
                }

                if(TempFlag2 == C_OK)
                {
                    if(SF_Judge_EventIntegrity(V_ucEvtNo) == C_Happen_EventState)
                    {
                        GV_ucEvent_Hstate[V_ucEvtNo] = C_Happen_EventState;							/*历史状态赋值*/
                    }
                    else
                    {
                        GV_ucEvent_Hstate[V_ucEvtNo] = C_End_EventState;								/*历史状态赋值*/
                    }
                }

                if( (TempFlag2 == C_Error) || ( SF_Judge_EventIntegrity(V_ucEvtNo) == C_Happen_EventState ) )
                {
                    if( ( PF_TimeSub_Min_698(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_ulAddTimeTemp) != C_LessThan )
                        && ( InF_GetEnterLowPowerTimerUpdateFlag() == C_OK ) )
                    {
                            SF_Sub_Sec(V_ucJudgeBuffer1[C_Judge_StartBuffer0], V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_ulSubSec);
                            V_ulAddTimeTemp *= 60;
                            V_ulAddTimeTemp += V_ulSubSec;

                            PF_BufferXToUlong32(pStr_strCoverRecord->AddTime, &V_ulAddTime_H, C_AddTime_Length);
                            V_ulAddTime_H += V_ulAddTimeTemp;
                            PF_Ulong32ToBufferX(pStr_strCoverRecord->AddTime, &V_ulAddTime_H, C_AddTime_Length);
                            SF_Str_CalCRC(V_ucEvtNo);				/*低功耗结构体算CRC*/
                    }
                }
            }
            else
            {
                SF_Str_Clear(V_ucEvtNo);						/*清零*/
                pStr_strCoverRecord->OpenCoverState=C_Null_EventMsg;			/*低功耗开盖状态赋无动作*/
                pStr_strCoverRecord->CloseCoverState=C_Null_EventMsg;			/*低功耗状态合盖赋无动作*/
                SF_Str_CalCRC(V_ucEvtNo);						/*低功耗结构体算CRC*/
            }
        }
		/*全失压事件上电初始化*/
		PF_CopyDataBytes_698(V_ucPowerOnTimeTemp, V_ucJudgeBuffer1, CLDate_Week_Time);
		if( SF_Str_CheckCRC(C_TotalVoltageLoseEventNo) == C_OK )
		{
			if(GStr_TotalvoltageloseStr.MeterState == C_Happen_EventMsg)
			{
				PF_CopyDataBytes(GStr_TotalvoltageloseStr.Time, &V_ucJudgeBuffer4[C_Judge_StartBuffer0], C_EventTimeLength);

				if( PF_TimeSub_Min_698(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer4[C_Judge_StartBuffer0], &V_ulAddTimeTemp) != C_LessThan )
				{
					SF_Sub_Sec(V_ucJudgeBuffer1[C_Judge_StartBuffer0], V_ucJudgeBuffer4[C_Judge_StartBuffer0], &V_ulSubSec);
					V_ulAddTimeTemp *= 60;
					V_ulAddTimeTemp += V_ulSubSec;

					PF_Ulong32ToBufferX(GStr_TotalvoltageloseStr.AddTime, &V_ulAddTimeTemp, C_AddTime_Length);
					SF_AppendEventMessageLowPower(C_TotalVoltageLoseEventNo, C_Happen_EventMsg);						/*发送事件发生写消息*/
					SF_Str_CalCRC(C_TotalVoltageLoseEventNo);					/*低功耗结构体算CRC*/
				}

				GV_ucEvent_Hstate[C_TotalVoltageLoseEventNo]=C_Happen_EventState;	/*历史状态赋值*/
			}
			else
			{
				if(GStr_TotalvoltageloseStr.MeterState == C_End_EventMsg)
				{
					PF_BufferXToUlong32(GStr_TotalvoltageloseStr.AddTime, &V_ulAddTimeTemp, C_AddTime_Length);
					V_ulAddTimeTemp += 60;		/*加60*/
					PF_Ulong32ToBufferX(GStr_TotalvoltageloseStr.AddTime, &V_ulAddTimeTemp, C_AddTime_Length);
					SF_Str_CalCRC(C_TotalVoltageLoseEventNo);		/*计算CRC*/
					SF_AppendEventMessageLowPower(C_TotalVoltageLoseEventNo, C_End_EventMsg);		/*发送事件结束写消息*/
					GV_ucEvent_Hstate[C_TotalVoltageLoseEventNo] = C_End_EventState;		/*历史状态赋值*/
				}
				else
				{
					if( SF_Judge_EventIntegrity( C_TotalVoltageLoseEventNo ) == C_Happen_EventState )		/*历史状态为发生，累计时间加上低功耗时间*/
					{
						if( InF_GetEnterLowPowerTimerUpdateFlag() == C_OK )
						{
							V_usBufferLength1 = C_Judge_20BufferLength;		/*V0.2新增长度赋值*/
							InF_GetData_ObjectManage(CEnter_LowPower_Time, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode);	/*低功耗下累计时间*/

							SF_Sub_Sec(V_ucJudgeBuffer1[C_Judge_StartBuffer0], V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_ulSubSec);
							V_ucReturnData = PF_TimeSub_Min_698(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_ulAddTimeTemp);
							V_ulAddTimeTemp *= 60;
							V_ulAddTimeTemp += V_ulSubSec;

							if( (V_ucReturnData == C_GreaterThan) || (V_ucReturnData == C_Equal) )		/*低功耗下累计时间计算*/
							{
								PF_BufferXToUlong32(GStr_TotalvoltageloseStr.AddTime, &V_ulAddTime_H, C_AddTime_Length);
								V_ulAddTime_H += V_ulAddTimeTemp;
								PF_Ulong32ToBufferX(GStr_TotalvoltageloseStr.AddTime, &V_ulAddTime_H, C_AddTime_Length);
								SF_Str_CalCRC(C_TotalVoltageLoseEventNo);		/*低功耗结构体算CRC*/
							}
						}

						GV_ucEvent_Hstate[C_TotalVoltageLoseEventNo] = C_Happen_EventState;		/*历史状态赋值*/
					}
					else
					{
						GV_ucEvent_Hstate[C_TotalVoltageLoseEventNo] = C_End_EventState;		/*历史状态赋值*/
					}
				}
			}
		}
		else
		{
			SF_Str_Clear(C_TotalVoltageLoseEventNo);			/*清零*/
			GStr_TotalvoltageloseStr.MeterState = C_Null_EventMsg;		/*低功耗状态赋无动作*/
			SF_Str_CalCRC(C_TotalVoltageLoseEventNo);			/*低功耗结构体算CRC*/
		}

		/*掉电事件上电初始化*/
		if(SF_Str_CheckCRC(C_PowerfailEventNo) == C_OK)
		{
		    V_ucV_ucEventState = SF_Judge_EventIntegrity(C_PowerfailEventNo);		/*获取Flash中掉电事件的历史状态*/

			if( (V_ucV_ucEventState == C_Happen_EventState)
				&&(GStr_PowerfailStr.MeterState == C_End_EventMsg) )
		    {
                GStr_PowerfailStr.MeterState = C_End_EventMsg;
		    }
		    else if( (V_ucV_ucEventState != C_Happen_EventState)
				&&(GStr_PowerfailStr.MeterState == C_Happen_EventMsg) )
		    {
                GStr_PowerfailStr.MeterState = C_Happen_EventMsg;
		    }
		    else
		    {
		        GStr_PowerfailStr.MeterState = C_Null_EventMsg;
		    }

			SF_Str_CalCRC(C_PowerfailEventNo);		/*低功耗结构体算CRC*/

			if(GStr_PowerfailStr.MeterState == C_Happen_EventMsg)
			{
				PF_CopyDataBytes(GStr_PowerfailStr.Time, &V_ucJudgeBuffer4[C_Judge_StartBuffer0], C_EventTimeLength);
				if( PF_TimeSub_Min_698(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer4[C_Judge_StartBuffer0], &V_ulAddTimeTemp) != C_LessThan )
				{
					SF_Sub_Sec(V_ucJudgeBuffer1[C_Judge_StartBuffer0], V_ucJudgeBuffer4[C_Judge_StartBuffer0], &V_ulSubSec);
					V_ulAddTimeTemp *= 60;
					V_ulAddTimeTemp += (V_ulSubSec + 3);		/*此处加闭锁时间2s加初始化时间1s*/

					PF_Ulong32ToBufferX(GStr_PowerfailStr.AddTime, &V_ulAddTimeTemp, C_AddTime_Length);
					SF_Str_CalCRC(C_PowerfailEventNo);		/*低功耗结构体算CRC*/
				}

				SF_AppendEventMessageLowPower(C_PowerfailEventNo, C_Happen_EventMsg);		/*发送事件发生写消息*/
				GV_ucEvent_Hstate[C_PowerfailEventNo] = C_Happen_EventState;					/*历史状态赋值*/
			}
			else
			{
				if(GStr_PowerfailStr.MeterState == C_End_EventMsg)
				{
        			PF_BufferXToUlong32(GStr_PowerfailStr.AddTime, &V_ulAddTimeTemp, C_AddTime_Length);
					V_ulAddTimeTemp += 3;		/*此处加闭锁时间3s*/
					PF_Ulong32ToBufferX(GStr_PowerfailStr.AddTime, &V_ulAddTimeTemp, C_AddTime_Length);
					SF_AppendEventMessageLowPower(C_PowerfailEventNo, C_End_EventMsg);		/*发送事件结束写消息*/
					SF_Str_CalCRC(C_PowerfailEventNo);									/*低功耗结构体算CRC*/
					GV_ucEvent_Hstate[C_PowerfailEventNo] = C_End_EventState;				/*历史状态赋值*/
				}
				else
				{
					if( V_ucV_ucEventState == C_Happen_EventState )
					{
						if( InF_GetEnterLowPowerTimerUpdateFlag() == C_OK )
						{
							V_usBufferLength1 = C_Judge_20BufferLength;
							InF_GetData_ObjectManage(CEnter_LowPower_Time, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode);	/*进低功耗时间*/

							SF_Sub_Sec(V_ucJudgeBuffer1[C_Judge_StartBuffer0], V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_ulSubSec);
							V_ucReturnData = PF_TimeSub_Min_698(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_ulAddTimeTemp);
							V_ulAddTimeTemp *= 60;
							V_ulAddTimeTemp += (V_ulSubSec + 3);	/*此处加闭锁时间3s*/

							if( (V_ucReturnData == C_GreaterThan) || (V_ucReturnData == C_Equal) )	/*低功耗下累计时间计算*/
							{
								PF_BufferXToUlong32(GStr_PowerfailStr.AddTime, &V_ulAddTime_H, C_AddTime_Length);
								V_ulAddTime_H += V_ulAddTimeTemp;
								PF_Ulong32ToBufferX(GStr_PowerfailStr.AddTime, &V_ulAddTime_H, C_AddTime_Length);
								SF_Str_CalCRC(C_PowerfailEventNo);	/*低功耗结构体算CRC*/
							}
						}

						GV_ucEvent_Hstate[C_PowerfailEventNo] = C_Happen_EventState;		/*历史状态赋值*/
					}
#if 0
					else
					{
						GV_ucEvent_Hstate[C_PowerfailEventNo] = C_End_EventState;		/*历史状态赋值*/
					}
#endif
				}
			}
		}
		else
		{
			SF_Str_Clear(C_PowerfailEventNo);				/*清零*/
			GStr_PowerfailStr.MeterState = C_Null_EventMsg;		/*低功耗状态赋无动作*/
			SF_Str_CalCRC(C_PowerfailEventNo);				/*低功耗结构体算CRC*/
		}

		/*辅助电源失电上电初始化*/
		V_usBufferLength1 = CLAuxi_Power_Sign;
		if(InF_GetData_ObjectManage(CAuxi_Power_Sign, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) == C_OK)	/*读辅助电源类型*/
		{
			if(V_ucJudgeBuffer3[C_Judge_StartBuffer0] == C_ACPowerFail)		/*带辅助电源的表*/
			{
				if(SF_Str_CheckCRC(C_ACPowerFailEventNo) == C_OK)			/*低功耗CRC正确*/
				{
					uchar8 TempFlag = C_OK;

					if(GStr_ACPowerFailStr.MeterState == C_Happen_EventMsg)
					{
						SF_AppendEventMessageLowPower(C_ACPowerFailEventNo, C_Happen_EventMsg);	/*发送事件发生写消息*/
						PF_CopyDataBytes(GStr_ACPowerFailStr.Time, &V_ucJudgeBuffer4[C_Judge_StartBuffer0], C_EventTimeLength);
					}
					else
					{
						if(SF_Judge_EventIntegrity(C_ACPowerFailEventNo) == C_Happen_EventState)	/*历史状态为发生，累计时间加上低功耗时间*/
						{
							V_usBufferLength1 = C_Judge_20BufferLength;		/*V0.2新增长度赋值*/
							InF_GetData_ObjectManage(CEnter_LowPower_Time, &V_ucJudgeBuffer4[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode);	/*进入低功耗时间*/
						}
						else
						{
							GV_ucEvent_Hstate[C_ACPowerFailEventNo] = C_End_EventState;		/*历史状态赋值*/
							TempFlag = C_Error;
						}
					}

					if(TempFlag == C_OK)
					{
						if(InF_GetEnterLowPowerTimerUpdateFlag() == C_OK)
						{
							SF_Sub_Sec(V_ucJudgeBuffer1[C_Judge_StartBuffer0], V_ucJudgeBuffer4[C_Judge_StartBuffer0], &V_ulSubSec);

							uchar8 V_ucReturnData;
							V_ucReturnData = PF_TimeSub_Min_698(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer4[C_Judge_StartBuffer0], &V_ulAddTimeTemp);
							V_ulAddTimeTemp *= 60;
							V_ulAddTimeTemp += V_ulSubSec;

							if( (V_ucReturnData == C_GreaterThan) || (V_ucReturnData == C_Equal) )		/*低功耗下累计时间计算*/
							{
								PF_BufferXToUlong32(GStr_ACPowerFailStr.AddTime, &V_ulAddTime_H, C_AddTime_Length);
								V_ulAddTime_H += (V_ulAddTimeTemp + 3);									/*此处加闭锁时间2s加初始化时间1s*/
								PF_Ulong32ToBufferX(GStr_ACPowerFailStr.AddTime, &V_ulAddTime_H, C_AddTime_Length);
								SF_Str_CalCRC(C_ACPowerFailEventNo);								/*低功耗结构体算CRC*/
							}
						}

						GV_ucEvent_Hstate[C_ACPowerFailEventNo] = C_Happen_EventState;					/*历史状态赋值*/
					}
				}
				else
				{
					SF_Str_Clear(C_ACPowerFailEventNo);				/*清零*/
					GStr_ACPowerFailStr.MeterState = C_Null_EventMsg;	/*低功耗状态赋无动作*/
					SF_Str_CalCRC(C_ACPowerFailEventNo);			/*低功耗结构体算CRC*/
				}
			}
		}
		else
		{
			SF_Str_Clear(C_ACPowerFailEventNo);						/*清零*/
			GStr_ACPowerFailStr.MeterState = C_Null_EventMsg;				/*低功耗状态赋无动作*/
			SF_Str_CalCRC(C_ACPowerFailEventNo);					/*低功耗结构体算CRC*/
		}

		/*时钟故障上电初始化*/
		PF_CopyDataBytes_698(V_ucPowerOnTimeTemp, V_ucJudgeBuffer1, CLDate_Week_Time);
		if(SF_Str_CheckCRC(C_ClockFaEventNo) == C_OK)
		{
			if( SF_Judge_EventIntegrity(C_ClockFaEventNo) == C_Happen_EventState )		/*获取Flash中时钟故障事件的历史状态*/
			{
				GV_ucEvent_Hstate[C_ClockFaEventNo] = C_Happen_EventState;					/*历史状态赋值*/

				V_usBufferLength1 = CLBackTime_OneSec;
				InF_GetData_ObjectManage(CBackTime_OneSec, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode);		/*铁电备份时间*/

				if( PF_TimeSub_Min_698(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_ulAddTimeTemp) != C_LessThan )
				{
					SF_Sub_Sec(V_ucJudgeBuffer1[C_Judge_StartBuffer0], V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_ulSubSec);
					V_ucReturnData = PF_TimeSub_Min_698(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_ulAddTimeTemp);
					V_ulAddTimeTemp *= 60;
					V_ulAddTimeTemp += (V_ulSubSec + 3);										/*此处加闭锁时间*/

					if( (V_ucReturnData == C_GreaterThan) || (V_ucReturnData == C_Equal) )		/*低功耗下累计时间计算*/
					{
						PF_BufferXToUlong32(GStr_ClockFaStr.AddTime, &V_ulAddTime_H, C_AddTime_Length);
						V_ulAddTime_H += V_ulAddTimeTemp;
						PF_Ulong32ToBufferX(GStr_ClockFaStr.AddTime, &V_ulAddTime_H, C_AddTime_Length);
						SF_Str_CalCRC(C_ClockFaEventNo);			                	/*结构体算CRC*/
					}
				}
			}
			else
			{
				GV_ucEvent_Hstate[C_ClockFaEventNo] = C_End_EventState;		/*历史状态赋值*/
			}
		}
		else
		{
			SF_Str_Clear(C_ClockFaEventNo);								/*清零*/
			SF_Str_CalCRC(C_ClockFaEventNo);							/*结构体算CRC*/
		}

		for(V_ucEventNo = C_OverForwardActiveEventNo; V_ucEventNo <= C_NeutralCurrentAbnormalEventNo; V_ucEventNo++)
		{
            if(V_ucEventNo == C_ClockFaEventNo)
			{
				continue;
			}

			GV_ucEvent_JudgeTimer[V_ucEventNo] = C_NULL;	 				/*定时器清零*/
			if( SF_Str_CheckCRC(V_ucEventNo) == C_OK )
			{
				if( SF_Judge_EventIntegrity(V_ucEventNo) == C_Happen_EventState )
				{
					SF_AppendEventMessage(V_ucEventNo, C_End_EventMsg, C_PowerRising);	/*发送事件结束写消息*/
					GV_ucEvent_Hstate[V_ucEventNo] = C_End_EventState;
				}
			}
			else
			{
				SF_Str_Clear(V_ucEventNo);
				SF_Str_CalCRC(V_ucEventNo);		  /*状态位没有置，以后修改，历史状态位不发生，必须为0*/
			}
		}

		GV_ucReversecurrentTimes = C_NULL;               /*上电初始化/清零/事件关闭后第一次有方向，不报警*/
		GV_ucDirectionExchange = C_NULL;

		/******************************低功耗事件定时器清零*************************************************/
		GV_ucEvent_JudgeTimer[C_TotalVoltageLoseEventNo] = C_NULL;
		GV_ucEvent_JudgeTimer[C_ACPowerFailEventNo] = C_NULL;
		GV_ucEvent_JudgeTimer[C_PowerfailEventNo] = C_NULL;
		GV_ucEvent_JudgeTimer[C_OpenMeterCoverEventNo] = C_NULL;
		GV_ucEvent_JudgeTimer[C_OpenTerminalCoverEventNo] = C_NULL;
		GV_ucEvent_JudgeTimer[C_PowerAbnormalEventNo] = C_NULL;

		/******************************恒定磁场事件*************************************************/
		GV_ucEvent_JudgeTimer[C_MagneticCheckEventNo] = C_NULL;	 				/*定时器清零*/
		if(SF_Str_CheckCRC(C_MagneticCheckEventNo) == C_OK)
		{
			if(SF_Judge_EventIntegrity(C_MagneticCheckEventNo) == C_Happen_EventState)
			{
				SF_AppendEventMessage(C_MagneticCheckEventNo, C_End_EventMsg, C_PowerRising);	/*发送事件结束写消息*/
				GV_ucEvent_Hstate[C_MagneticCheckEventNo] = C_End_EventState;
			}
		}
		else
		{
			SF_Str_Clear(C_MagneticCheckEventNo);
			SF_Str_CalCRC(C_MagneticCheckEventNo);		/*状态位没有置，以后修改，历史状态位不发生，必须为0*/
		}
	}
  	else
	{
		for(V_ucEventNo = C_TotalVoltageLoseEventNo; V_ucEventNo <= C_SUnbanlanceCurrentEventNo; V_ucEventNo++)
		{												/*全清*/
			GV_ucEvent_Hstate[V_ucEventNo] = C_End_EventState;	/*关闭*/
			GV_ucEvent_JudgeTimer[V_ucEventNo] = C_NULL;
			SF_Str_Clear(V_ucEventNo);
			SF_Str_CalCRC(V_ucEventNo);
			/*此时报警状态字没有清零，到写消息中去清零*/
		}

		GV_ucReversecurrentTimes = C_NULL;                                             		/*上电初始化/清零/事件关闭后第一次有方向，不报警*/
		GV_ucDirectionExchange = C_NULL;
	}

	for(V_ucSymbolNo = C_AVoltage_SymbolNO; V_ucSymbolNo < C_EventSymbolLength; V_ucSymbolNo++)		/*符号上电初始化*/
	{
		GV_ucEvent_SymbolHstate[V_ucSymbolNo] = 0xff;
	}

	for(V_ucAlarmNo = 0; V_ucAlarmNo < C_AlarmTempLength; V_ucAlarmNo++)                       		/*报警符号上电初始化*/
	{
		GV_ucBackLightAlarm_Hstate[V_ucAlarmNo] = C_NULL;
		GV_ucAlarmoutput_Hstate[V_ucAlarmNo] = C_NULL;
		GV_ucBellAlarm_Hstate[V_ucAlarmNo] = C_NULL;
	}

	SF_SymbolDisplay_Judgemsg();            /*初始化符号*/
	SF_AlarmDisplay_Judgemsg();             /*初始化报警*/
	SF_MeterStatus_Judgemsg();
}

/***********************************************************************************
函数原型：void Inf_LowpowerACPowerFail(void)
功能描述：低功耗下辅助电源失电
输入参数：
输出参数：
返回参数：
功能说明：判断低功耗下辅助电源失电状态
调用机制：进入低功耗时调用
备    注：除了开合盖，其他的进低功耗不判CRC;
***********************************************************************************/
void Inf_LowpowerACPowerFail(void)
{
	uchar8		V_ucEventMsg;
	uchar8		V_ucJudgeBuffer1[C_Judge_20BufferLength];
	uchar8		V_ucJudgeBuffer2[C_Judge_20BufferLength];
	ushort16    V_usBufferLength1 = C_Judge_20BufferLength, V_usEncode;

	if(SF_Str_CheckCRC(C_ACPowerFailEventNo) != C_OK)
	{
		SF_Str_Clear(C_ACPowerFailEventNo);
		GStr_ACPowerFailStr.MeterState = C_Null_EventMsg;		/*低功耗状态赋无动作*/
        SF_Str_CalCRC(C_ACPowerFailEventNo);
	}
	if(InF_GetData_ObjectManage(CAuxi_Power_Sign, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode)!=C_OK)/*辅助电源类型*/
	{
		return;
	}
	if(V_ucJudgeBuffer1[C_Judge_StartBuffer0] != C_ACPowerFail)/*不带辅助电源，直接退出*/
	{
		return;
	}
    if(SF_Judge_EventIntegrity(C_ACPowerFailEventNo) == C_Happen_EventState)
    {
        return;
    }
	else if(GStr_ACPowerFailStr.MeterState == C_Happen_EventMsg)
	{
		return;
	}
    else
    {
        V_ucEventMsg=C_Happen_EventMsg;
    }
	V_usBufferLength1 = C_Judge_20BufferLength;/*V0.2新增长度赋值*/
	if(V_ucEventMsg == C_Happen_EventMsg)
	{
		if(InF_GetData_ObjectManage(CDate_Time, &V_ucJudgeBuffer2[C_Judge_StartBuffer2], &V_usBufferLength1, &V_usEncode) != C_OK)/*读取事件发生时间, 如果出错，什么都不做，退出*/
		{
			return;
		}
        V_usBufferLength1 = CLMeter_Work_State7;
		if(InF_GetData_ObjectManage(CMeter_Work_State7, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) != C_OK)/*电表运行状态字7*/
		{
			return;
		}
		V_ucJudgeBuffer2[C_Judge_StartBuffer0] |= C_Bit4_Start;/*bit4置1, 缓存0的第4位*/
		if(InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State7, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag) != C_OK)/*电表运行状态字7写数据层*/
		{																					/*写电表运行状态字，出错，就不做动作*/
			return;
		}/*读数据成功后，再写数据层，写数据层成功后再操作结构体*/
		GStr_ACPowerFailStr.MeterState = C_Happen_EventMsg;													/*事件状态赋值*/
		PF_CopyDataBytes(&V_ucJudgeBuffer2[C_Judge_StartBuffer2], GStr_ACPowerFailStr.Time, C_EventTimeLength);/*事件发生时刻赋值*/
        SF_Str_CalCRC(C_ACPowerFailEventNo);

		GV_ucEvent_Hstate[C_ACPowerFailEventNo] = C_Happen_EventState;/*历史状态赋值（放到最后写，如果出错，不更新历史状态）*/
	}
}

/***********************************************************************************
函数原型：void Inf_PowerAbnormal(void)
功能描述：低功耗下电源异常
输入参数：
输出参数：
返回参数：
功能说明：判断低功耗是否电源异常
调用机制：进入低功耗1S时调用
备    注：
***********************************************************************************/
void Inf_PowerAbnormal(void)
{
	uchar8		V_ucJudgeBuffer1[C_Judge_20BufferLength];/*判断阀值缓存*/
	uchar8		V_ucJudgeBuffer2[C_Judge_20BufferLength];/*分相电压缓存*/
	ushort16    V_usBufferLength1 = C_Judge_20BufferLength, V_usEncode;
	uchar8		V_ucRelayState;

	if(SF_Str_CheckCRC(C_PowerAbnormalEventNo)!=C_OK)
	{
		SF_Str_Clear(C_PowerAbnormalEventNo);
		GStr_PowerabnormalStr.MeterState=C_Null_EventMsg;	/*低功耗状态赋无动作*/
		SF_Str_CalCRC(C_PowerAbnormalEventNo);
	}
	V_ucRelayState = InF_RelayOpenStatus();	/*继电器状态*/
	if(V_ucRelayState != C_EventOK)/*开关内置且跳闸状态*/
	{
		return;
	}
	if(InF_GetData_ObjectManage(CVolage_Abnor_Vol, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode)!=C_OK)/*电源异常判断电压*/
	{
		return;
	}
    V_usBufferLength1 = C_Judge_20BufferLength;/*V0.2新增长度赋值*/
	if(InF_GetData_ObjectManage(CPhaseFF_Volage, &V_ucJudgeBuffer2[C_JudgeVolage_Buffer1], &V_usBufferLength1, &V_usEncode)!=C_OK)/*读分相电压*/
	{
		return;
	}
	if( ( (PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeVolage_Buffer1], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_GreaterThan)/*低字节是电压下限*/
            && (PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeVolage_Buffer1], &V_ucJudgeBuffer1[C_Judge_StartBuffer2], C_Volage_Length) == C_LessThan) )/*高字节是电压上限*/
		|| ( (PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeVolage_Buffer2], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_GreaterThan)
            &&(PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeVolage_Buffer2], &V_ucJudgeBuffer1[C_Judge_StartBuffer2], C_Volage_Length) == C_LessThan) )
		||( ( (PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeVolage_Buffer3], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Volage_Length) == C_GreaterThan)
            &&(PF_Campare_Data(&V_ucJudgeBuffer2[C_JudgeVolage_Buffer3], &V_ucJudgeBuffer1[C_Judge_StartBuffer2], C_Volage_Length) == C_LessThan)) ) )
	{
    V_usBufferLength1=C_Judge_20BufferLength;     /*V0.2新增长度赋值*/
    if(InF_GetData_ObjectManage(CDate_Time, &V_ucJudgeBuffer1[C_Judge_StartBuffer2], &V_usBufferLength1, &V_usEncode)!=C_OK)/*读取事件发生时间*/
    {
        return;
    }
    GStr_PowerabnormalStr.MeterState = C_Happen_EventMsg;													/*事件发生状态赋值*/
    PF_CopyDataBytes(&V_ucJudgeBuffer1[C_Judge_StartBuffer2], GStr_PowerabnormalStr.Time, C_EventTimeLength);/*事件发生时间赋值*/

    SF_Str_CalCRC(C_PowerAbnormalEventNo);
    GV_ucEvent_Hstate[C_PowerAbnormalEventNo] = C_Happen_EventState;				/*历史状态赋值（放到最后写，如果出错，不更新历史状态）*/
	}
}

/***********************************************************************************
函数原型：void Inf_LowpowerTotalVoltagelose(void)
功能描述：低功耗下全失压
输入参数：
输出参数：
返回参数：
功能说明：低功耗下60s时判断当前电能表状态
调用机制：进入低功耗60S时调用
备    注：
***********************************************************************************/
void Inf_LowpowerTotalVoltagelose(void)
{
	uchar8		V_ucEventMsg;
	uchar8		V_ucJudgeBuffer1[C_Judge_20BufferLength];/*全失压发生时电流缓存*/
	uchar8		V_ucJudgeBuffer2[C_Judge_20BufferLength];/*相线类型*/
	ushort16    V_usBufferLength1 = C_Judge_20BufferLength, V_usEncode;

	if(SF_Str_CheckCRC(C_TotalVoltageLoseEventNo) != C_OK)
	{
		SF_Str_Clear(C_TotalVoltageLoseEventNo);
		GStr_TotalvoltageloseStr.MeterState = C_Null_EventMsg;		/*低功耗状态赋无动作*/
		SF_Str_CalCRC(C_TotalVoltageLoseEventNo);
	}
	V_ucEventMsg = SF_Judge_Event_Statechange(C_TotalVoltageLoseEventNo, C_Judge_Time0);/*判断全失压是否发生*/
	if(V_ucEventMsg == C_Happen_EventMsg)
	{
		V_usBufferLength1 = C_Judge_20BufferLength;
		if(InF_GetData_ObjectManage(CPhaseFF_Curr, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) != C_OK)/*读取事件发生电流*/
        {
            return;
        }
		V_usBufferLength1 = C_Judge_20BufferLength; /*V0.2新增长度赋值*/
		if(InF_GetData_ObjectManage(CDate_Time, &V_ucJudgeBuffer2[C_Judge_StartBuffer2], &V_usBufferLength1, &V_usEncode) != C_OK)/*读取事件发生时间*/
		{
			return;
		}
		PF_CopyDataBytes(&V_ucJudgeBuffer2[C_Judge_StartBuffer2], GStr_TotalvoltageloseStr.Time, C_EventTimeLength);/*给全失压发生时刻赋值*/
		PF_CopyDataBytes(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], GStr_TotalvoltageloseStr.NoVoltageCurrent, C_3Curr_Length);/*给全失压电流赋值*/

        GStr_TotalvoltageloseStr.MeterState = C_Happen_EventMsg;/*全失压低功耗状态置发生*/
		SF_Str_CalCRC(C_TotalVoltageLoseEventNo);			/*低功耗结构体算CRC*/

		GV_ucEvent_Hstate[C_TotalVoltageLoseEventNo] = C_Happen_EventState;/*历史状态赋值*/
	}
 	else
 	{
 		if(V_ucEventMsg == C_End_EventMsg)
 		{
			if(InF_GetData_ObjectManage(CDate_Time, &V_ucJudgeBuffer2[C_Judge_StartBuffer2], &V_usBufferLength1, &V_usEncode) != C_OK)/*读取事件发生时间*/
			{
				return;
			}
			PF_CopyDataBytes(&V_ucJudgeBuffer2[C_Judge_StartBuffer2], GStr_TotalvoltageloseStr.Time, C_EventTimeLength);/*给全失压发生时刻赋值*/
			GStr_TotalvoltageloseStr.MeterState = C_End_EventMsg;/*全失压低功耗结构体状态置结束*/
			SF_Str_CalCRC(C_TotalVoltageLoseEventNo);			/*低功耗结构体算CRC*/

			GV_ucEvent_Hstate[C_TotalVoltageLoseEventNo]=C_End_EventState;/*历史状态赋值*/
 		}
 	}
}
/*******************************************************************************
函数原型： uchar8 Inf_LowpowerPowerFail_No6VBat(void)
功能描述： 低功耗下掉电，没有6V电池
输入参数：
输出参数：
返回参数： C_Happen_V_ucEventState：进入低功耗发生掉电，上报；C_NULL：不是新发生的掉电，不赋初值；
调用位置:
备    注：
*******************************************************************************/
uchar8 Inf_LowpowerPowerFail_No6VBat(void)
{
	uchar8		V_ucJudgeBuffer1[C_Judge_20BufferLength];     /*事件发生时间*/
	uchar8		V_ucJudgeBuffer2[C_Judge_20BufferLength];		/*电表运行状态字7*/
	ushort16    V_usBufferLength1 = C_Judge_20BufferLength, V_usEncode;
    uchar8      V_ucPowerDownHstate = C_NULL, V_ucReturnFlag = C_NULL;

	if(SF_Str_CheckCRC(C_PowerfailEventNo)!=C_OK)
	{
		SF_Str_Clear(C_PowerfailEventNo);
	    GStr_PowerfailStr.MeterState = C_Null_EventMsg;	/*低功耗状态赋无动作*/
		SF_Str_CalCRC(C_PowerfailEventNo);
	}

	V_usBufferLength1 = CLDate_Week_Time;
    if( InF_GetData_ObjectManage( CDate_Time, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) == C_OK)       /*读取事件发生时间*/
    {
		V_usBufferLength1 = CLMeter_Work_State7;
        if(InF_GetData_ObjectManage(CMeter_Work_State7, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) == C_OK)	/*电表运行状态字7*/
		{
            V_ucJudgeBuffer2[C_Judge_StartBuffer0] |= C_Bit5_Start;				/*bit5置1, 缓存0的第5位*/
            if(InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State7, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag) == C_OK)	/*电表运行状态字7写数据层*/
            {/*写电表运行状态字，出错，就不做动作*/
                V_ucPowerDownHstate =  Inf_GetPowerDownEventType(C_PowerfailEventNo);     /*掉电进低功耗时当前状态，是否是已经发生，用于低功耗下主动上报*/
                if(V_ucPowerDownHstate != C_Happen_EventState)                            /*掉电不等于已经发生*/
                {
                    V_ucReturnFlag = C_Happen_EventState;                                 /*表示低功耗下发生掉电，否则不进行新掉电主动上报*/
                }
                PF_CopyDataBytes(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], GStr_PowerfailStr.Time, C_EventTimeLength);        /*时间结构体，赋值*/
                GStr_PowerfailStr.MeterState = C_Happen_EventMsg;                            /*掉电低功耗状态置发生*/
                SF_Str_CalCRC(C_PowerfailEventNo);			                            /*低功耗结构体算CRC*/
                GV_ucEvent_Hstate[C_PowerfailEventNo] = C_Happen_EventState;                 /*历史状态赋值*/
            }/*读数据成功后，再写数据层，写数据层成功后再操作结构体*/
		}
    }

    return V_ucReturnFlag;                                                        /*返回是否需要上报的标志*/
}


/*******************************************************************************
函数原型： uchar8 Inf_LowpowerPowerFail(void)
功能描述： 低功耗下掉电
输入参数：
输出参数：
返回参数： C_Happen_EventState:发生掉电 ；C_End_V_ucEventState：结束掉电；C_NULL读数据出错不做事件
调用位置：
备    注： 低功耗调用
*******************************************************************************/
uchar8 Inf_LowpowerPowerFail(void)
{
	uchar8		V_ucEventState = C_NULL, V_ucReturnFlag = C_NULL;
	uchar8		V_ucJudgeBuffer1[C_Judge_20BufferLength];		/*事件发生时间*/
	uchar8		V_ucJudgeBuffer2[C_Judge_20BufferLength];		/*电表运行状态字7*/
	ushort16    V_usBufferLength1 = C_Judge_20BufferLength, V_usEncode;
    uchar8      V_ucPowerDownHstate = C_NULL;

	if(SF_Str_CheckCRC(C_PowerfailEventNo) != C_OK)
	{
		SF_Str_Clear(C_PowerfailEventNo);
	    GStr_PowerfailStr.MeterState = C_Null_EventMsg;	/*低功耗状态赋无动作*/
		SF_Str_CalCRC(C_PowerfailEventNo);
	}
    V_ucPowerDownHstate =  Inf_GetPowerDownEventType(C_PowerfailEventNo);     /*掉电当前状态，是否是已经发生，用于低功耗下主动上报*/
	V_ucEventState = SF_Get_Powerfail_Cstate(C_PowerfailEventNo, GV_ucEvent_Hstate[C_PowerfailEventNo]);	/*判断掉电是否发生*/
	if(V_ucEventState == C_Happen_EventState)
	{
		if(InF_GetData_ObjectManage(CDate_Time, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) != C_OK)		/*读取事件发生时间*/
		{
			return V_ucReturnFlag;
		}
        V_usBufferLength1 = CLMeter_Work_State7;
		if(InF_GetData_ObjectManage(CMeter_Work_State7, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) != C_OK)	/*电表运行状态字7*/
		{
			return V_ucReturnFlag;
		}
		V_ucJudgeBuffer2[C_Judge_StartBuffer0] |= C_Bit5_Start;				/*bit5置1, 缓存0的第5位*/
		if(InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State7, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag) != C_OK)	/*电表运行状态字7写数据层*/
		{																					/*写电表运行状态字，出错，就不做动作*/
			return V_ucReturnFlag;
		}/*读数据成功后，再写数据层，写数据层成功后再操作结构体*/
		PF_CopyDataBytes(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], GStr_PowerfailStr.Time, C_EventTimeLength);			/*时间结构体，赋值*/
		GStr_PowerfailStr.MeterState = C_Happen_EventMsg;							/*全失压低功耗状态置发生*/
		SF_Str_CalCRC(C_PowerfailEventNo);							/*低功耗结构体算CRC*/
		GV_ucEvent_Hstate[C_PowerfailEventNo] = C_Happen_EventState;		/*历史状态赋值*/
        if(V_ucPowerDownHstate != C_Happen_EventState)
        {
            V_ucReturnFlag = V_ucEventState;
        }
	}
 	else
 	{
 		if(V_ucEventState == C_End_EventState)
 		{
			if(InF_GetData_ObjectManage(CDate_Time, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) != C_OK)		/*读取事件发生时间*/
			{
				return V_ucReturnFlag;
			}
            V_usBufferLength1 = CLMeter_Work_State7;
			if(InF_GetData_ObjectManage(CMeter_Work_State7, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) != C_OK)	/*电表运行状态字7*/
			{
				return V_ucReturnFlag;
			}
			V_ucJudgeBuffer2[C_Judge_StartBuffer0] &= C_Bit5_End;				/*bit5置0, 缓存1的第2位*/
			if(InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State7, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag) != C_OK)	/*电表运行状态字7写数据层*/
			{																		/*写电表运行状态字，出错，就不做动作*/
				return V_ucReturnFlag;
			}/*读数据成功后，再写数据层，写数据层成功后再操作结构体*/
			PF_CopyDataBytes(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], GStr_PowerfailStr.Time, C_EventTimeLength);		/*事件结构体，时间赋值*/
			GStr_PowerfailStr.MeterState = C_End_EventMsg;						/*掉电低功耗结构体状态置结束*/
			SF_Str_CalCRC(C_PowerfailEventNo);								/*低功耗结构体算CRC*/
			GV_ucEvent_Hstate[C_PowerfailEventNo] = C_End_EventState;				/*历史状态赋值*/
            if(V_ucPowerDownHstate == C_Happen_EventState)
            {
                V_ucReturnFlag = V_ucEventState;
            }
 		}
 	}
	return V_ucReturnFlag;
}
#if (_DEBUG_DB)
/***********************************************************************************
函数原型：void Inf_LowpowerOpenMeterCover(void)
功能描述：低功耗下开表盖
输入参数：
输出参数：
返回参数：
功能说明：低功耗下60s时判断电能表开合盖状态，如果低功耗下合盖一次，不再进行判断
调用机制：进入低功耗每秒调用
备    注：
***********************************************************************************/
void Inf_LowpowerOpenMeterCover(void)
{
    uchar8		EventMsg;
	uchar8		V_ucJudgeBuffer1[C_Judge_20BufferLength];
//  uchar8      V_ucJudgeBuffer2[C_Judge_50BufferLength]={C_Null};
	uchar8		V_ucJudgeBuffer3[C_Judge_20BufferLength];
	uchar8		V_ucBufferLength1=C_Judge_20BufferLength;
//	ushort16	V_CRC;
//	if((PF_Check_CRC(&GStr_OpenMeterCoverStr.OpenCoverState, C_Str_CoverRecord_Length)!=C_OK)||(PF_Check_CRC(&GStr_OpenMeterCoverStr.OpenCoverState, C_Str_CoverRecord_Length)!=C_CrcErr_DataZero))
//	{
//		PF_CopyDataBytes(&V_ucJudgeBuffer2[C_Judge_StartBuffer0], &GStr_OpenMeterCoverStr.OpenCoverState, C_Str_CoverRecord_Length);/*CRC错误，清零*/
//	}
	if(SF_Str_CheckCRC(C_OpenMeterCoverEventNo)!=C_OK)
	{
		SF_Str_Clear(C_OpenMeterCoverEventNo);
		GStr_OpenMeterCoverStr.OpenCoverState=C_Null_EventMsg;	/*低功耗状态赋无动作*/
		GStr_OpenMeterCoverStr.CloseCoverState=C_Null_EventMsg;	/*低功耗状态赋无动作*/
		SF_Str_CalCRC(C_OpenMeterCoverEventNo);
	}
    if(GStr_OpenMeterCoverStr.CloseCoverState!=C_NULL)/*发生过结束事件，则退出*/
    {
    	return;
    }
    EventMsg=SF_Judge_Event_Statechange(C_OpenMeterCoverEventNo, C_Judge_Time1);/*判1次*/
    if(EventMsg==C_Happen_EventMsg)
    {
		if(InF_Read_Data(CDate_Time, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucBufferLength1)!=C_OK)/*读取时间不成功，退出*/
		{
			return;
		}
		if(InF_Read_Data(CMeter_Work_State7, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_ucBufferLength1)!=C_OK)/*电表运行状态字7*/
		{
			return;
		}
		V_ucJudgeBuffer3[C_Judge_StartBuffer1]|=C_Bit1_Start;/*bit8置1, 缓存0的1位*/
		if(InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State7, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag)!=C_OK)/*电表运行状态字7写数据层*/
		{																		/*写电表运行状态字，出错，就不做动作*/
// 			PF_CopyDataBytes(&V_ucJudgeBuffer3[C_Judge_StartBuffer0], &GStr_ACPowerFailStr.MeterState, V_ClearLength);/*电表运行状态字7写数据错误，清零*/
			return;
		}/*读数据成功后，再写数据层，写数据层成功后再操作结构体*/
		GStr_OpenMeterCoverStr.OpenCoverState=C_LowPowerHappen_EventMsg;
		PF_CopyDataBytes(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], GStr_OpenMeterCoverStr.HappenTime, C_EventTimeLength);/*事件结构体，时间赋值*/
		SF_Str_CalCRC(C_OpenMeterCoverEventNo);			/*低功耗结构体算CRC*/
//		V_CRC=PF_Cal_CRC(&GStr_OpenMeterCoverStr.OpenCoverState, C_Str_CoverRecord_Length);/*计算CRC*/
//		PF_Ushort16ToBuffer2(GStr_OpenMeterCoverStr.V_CRC, &V_CRC);
		GV_ucEvent_Hstate[C_OpenMeterCoverEventNo]=C_Happen_EventState;/*历史状态赋值*/
	}
	else
	{
		if(EventMsg==C_End_EventMsg)
		{
			if(InF_Read_Data(CDate_Week_Time, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucBufferLength1)!=C_OK)
			{
				return;
			}
			if(InF_Read_Data(CMeter_Work_State7, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_ucBufferLength1)!=C_OK)/*电表运行状态字7*/
			{
				return;
			}
			V_ucJudgeBuffer3[C_Judge_StartBuffer1]&=C_Bit1_End;/*bit8置0, 缓存0的1位*/
			if(InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State7, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag)!=C_OK)/*电表运行状态字7写数据层*/
			{																		/*写电表运行状态字，出错，就不做动作*/
	// 			PF_CopyDataBytes(&V_ucJudgeBuffer3[C_Judge_StartBuffer0], &GStr_ACPowerFailStr.MeterState, V_ClearLength);/*电表运行状态字7写数据错误，清零*/
				return;
			}/*读数据成功后，再写数据层，写数据层成功后再操作结构体*/
			GStr_OpenMeterCoverStr.CloseCoverState=C_LowPowerEnd_EventMsg;
			PF_CopyDataBytes(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], GStr_OpenMeterCoverStr.EndTime, C_EventTimeLength);/*事件结构体，时间赋值*/
			SF_Str_CalCRC(C_OpenMeterCoverEventNo);			/*低功耗结构体算CRC*/
//			V_CRC=PF_Cal_CRC(&GStr_OpenMeterCoverStr.OpenCoverState, C_Str_CoverRecord_Length);/*计算CRC*/
//			PF_Ushort16ToBuffer2(GStr_OpenMeterCoverStr.V_CRC, &V_CRC);
			GV_ucEvent_Hstate[C_OpenMeterCoverEventNo]=C_End_EventState;/*历史状态赋值*/
		}
	}
}
#endif
/***********************************************************************************
函数原型：void Inf_LowpowerOpenCoverState(uchar8 V_ucEvtNo)
功能描述：低功耗下开端钮盖与开表盖处理
输入参数：V_ucEvtNo事件号，只能为C_OpenMeterCoverEventNo或C_OpenTerminalCoverEventNo
输出参数：无
返回参数：无
功能说明：V_ucEvtNo只能为C_OpenMeterCoverEventNo或C_OpenTerminalCoverEventNo
调用机制：
备    注：
**********************************************************************************/
void Inf_LowpowerOpenCoverState(uchar8 V_ucEvtNo)
{
    uchar8 V_ucEventMsg;
	uchar8 V_ucJudgeBuffer1[C_Judge_20BufferLength];
	uchar8 V_ucJudgeBuffer3[C_Judge_20BufferLength];
	ushort16 V_usBufferLength1 = C_Judge_20BufferLength, V_usEncode;
    Str_CoverRecord_Type *pStr_strCoverRecord;
    uchar8 V_ucBit;

    if(V_ucEvtNo == C_OpenMeterCoverEventNo)
    {
        pStr_strCoverRecord = &GStr_OpenMeterCoverStr;
        V_ucBit = C_Bit1_Start;/*bit8*/
    }
    else if(V_ucEvtNo == C_OpenTerminalCoverEventNo)
    {
        pStr_strCoverRecord = &GStr_OpenTerminalCoverStr;
        V_ucBit = C_Bit2_Start;/*bit9*/
    }
    else
    {
        return;
    }
	if(SF_Str_CheckCRC(V_ucEvtNo) != C_OK)
	{
		SF_Str_Clear(V_ucEvtNo);
		pStr_strCoverRecord->OpenCoverState = C_Null_EventMsg;	/*低功耗状态赋无动作*/
		pStr_strCoverRecord->CloseCoverState = C_Null_EventMsg;	/*低功耗状态赋无动作*/
		SF_Str_CalCRC(V_ucEvtNo);
	}
    if(pStr_strCoverRecord->CloseCoverState != C_NULL)/*发生过结束事件，则退出*/
    {
    	return;
    }
    V_ucEventMsg = SF_Judge_Event_Statechange(V_ucEvtNo, C_Judge_Time1);/*判1次*/
    if(V_ucEventMsg == C_Happen_EventMsg)
    {
		if(InF_GetData_ObjectManage(CDate_Time, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) != C_OK)/*读取时间不成功，退出*/
		{
			return;
		}
        V_usBufferLength1 = CLMeter_Work_State7;
		if(InF_GetData_ObjectManage(CMeter_Work_State7, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) != C_OK)/*电表运行状态字7*/
		{
			return;
		}
		V_ucJudgeBuffer3[C_Judge_StartBuffer1] |= V_ucBit;/*bit8置1, 缓存0的1位*/
		if(InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State7, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag) != C_OK)/*电表运行状态字7写数据层*/
		{																		/*写电表运行状态字，出错，就不做动作*/
            return;
		}/*读数据成功后，再写数据层，写数据层成功后再操作结构体*/
		pStr_strCoverRecord->OpenCoverState = C_LowPowerHappen_EventMsg;
		PF_CopyDataBytes(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], pStr_strCoverRecord->HappenTime, C_EventTimeLength);/*事件结构体，时间赋值*/
		SF_Str_CalCRC(V_ucEvtNo);			/*低功耗结构体算CRC*/
		GV_ucEvent_Hstate[V_ucEvtNo] = C_Happen_EventState;/*历史状态赋值*/
	}
	else
	{
		if(V_ucEventMsg == C_End_EventMsg)
		{
			if(InF_GetData_ObjectManage(CDate_Time, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode)!=C_OK)
			{
				return;
			}
            V_usBufferLength1 = CLMeter_Work_State7;
			if(InF_GetData_ObjectManage(CMeter_Work_State7, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode)!=C_OK)/*电表运行状态字7*/
			{
				return;
			}
			V_ucJudgeBuffer3[C_Judge_StartBuffer1] &= (~V_ucBit);
			if(InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State7, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag) != C_OK)/*电表运行状态字7写数据层*/
			{																		/*写电表运行状态字，出错，就不做动作*/
				return;
			}/*读数据成功后，再写数据层，写数据层成功后再操作结构体*/
			pStr_strCoverRecord->CloseCoverState = C_LowPowerEnd_EventMsg;
			PF_CopyDataBytes(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], pStr_strCoverRecord->EndTime, C_EventTimeLength);/*事件结构体，时间赋值*/
			SF_Str_CalCRC(V_ucEvtNo);			/*低功耗结构体算CRC*/
			GV_ucEvent_Hstate[V_ucEvtNo] = C_End_EventState;/*历史状态赋值*/
		}
	}
}
#if (_DEBUG_DB)
/***********************************************************************************
函数原型：void Inf_LowpowerTerminalCoverState(void)
功能描述：低功耗下开端钮盖
输入参数：
输出参数：
返回参数：
功能说明：低功耗下60s时判断电能表开合端钮盖状态，如果低功耗下合端钮盖一次，不再进行判断
调用机制：进入低功耗每秒调用
备    注：
**********************************************************************************/
void Inf_LowpowerTerminalCoverState(void)
{
    uchar8		EventMsg;
	uchar8		V_ucJudgeBuffer1[C_Judge_20BufferLength];
//  uchar8      V_ucJudgeBuffer2[C_Judge_50BufferLength]={C_Null};
	uchar8		V_ucJudgeBuffer3[C_Judge_20BufferLength];
	uchar8		V_ucBufferLength1=C_Judge_20BufferLength;
//	ushort16	V_CRC;
//	if((PF_Check_CRC(&GStr_OpenTerminalCoverStr.OpenCoverState, C_Str_CoverRecord_Length)!=C_OK)||(PF_Check_CRC(&GStr_OpenTerminalCoverStr.OpenCoverState, C_Str_CoverRecord_Length)!=C_CrcErr_DataZero))
//	{
//		PF_CopyDataBytes(&V_ucJudgeBuffer2[C_Judge_StartBuffer0], &GStr_OpenTerminalCoverStr.OpenCoverState, C_Str_CoverRecord_Length);/*CRC错误，清零*/
//	}
	if(SF_Str_CheckCRC(C_OpenTerminalCoverEventNo)!=C_OK)
	{
		SF_Str_Clear(C_OpenTerminalCoverEventNo);
		GStr_OpenTerminalCoverStr.OpenCoverState=C_Null_EventMsg;	/*低功耗状态赋无动作*/
		GStr_OpenTerminalCoverStr.CloseCoverState=C_Null_EventMsg;	/*低功耗状态赋无动作*/
		SF_Str_CalCRC(C_OpenTerminalCoverEventNo);
	}
    if(GStr_OpenTerminalCoverStr.CloseCoverState!=C_NULL)/*发生过结束事件，则退出*/
    {
    	return;
    }
    EventMsg=SF_Judge_Event_Statechange(C_OpenTerminalCoverEventNo, C_Judge_Time1);/*判1次*/
    if(EventMsg==C_Happen_EventMsg)
    {
		if(InF_Read_Data(CDate_Time, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucBufferLength1)!=C_OK)/*读取时间不成功，退出*/
		{
			return;
		}
		if(InF_Read_Data(CMeter_Work_State7, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_ucBufferLength1)!=C_OK)/*电表运行状态字7*/
		{
			return;
		}
		V_ucJudgeBuffer3[C_Judge_StartBuffer1]|=C_Bit2_Start;/*bit9置1, 缓存0的2位*/
		if(InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State7, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag)!=C_OK)/*电表运行状态字7写数据层*/
		{																		/*写电表运行状态字，出错，就不做动作*/
// 			PF_CopyDataBytes(&V_ucJudgeBuffer3[C_Judge_StartBuffer0], &GStr_ACPowerFailStr.MeterState, V_ClearLength);/*电表运行状态字7写数据错误，清零*/
			return;
		}/*读数据成功后，再写数据层，写数据层成功后再操作结构体*/
		GStr_OpenTerminalCoverStr.OpenCoverState=C_LowPowerHappen_EventMsg;
		PF_CopyDataBytes(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], GStr_OpenTerminalCoverStr.HappenTime, C_EventTimeLength);/*事件结构体，时间赋值*/
//		V_CRC=PF_Cal_CRC(&GStr_OpenTerminalCoverStr.OpenCoverState, C_Str_CoverRecord_Length);/*计算CRC*/
//		PF_Ushort16ToBuffer2(GStr_OpenTerminalCoverStr.V_CRC, &V_CRC);
		SF_Str_CalCRC(C_OpenTerminalCoverEventNo);
		GV_ucEvent_Hstate[C_OpenTerminalCoverEventNo]=C_Happen_EventState;/*历史状态赋值*/
	}
	else
	{
		if(EventMsg==C_End_EventMsg)
		{
			if(InF_Read_Data(CDate_Time, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucBufferLength1)!=C_OK)
			{
				return;
			}
			if(InF_Read_Data(CMeter_Work_State7, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], &V_ucBufferLength1)!=C_OK)/*电表运行状态字7*/
			{
				return;
			}
			V_ucJudgeBuffer3[C_Judge_StartBuffer1]&=C_Bit2_End;/*bit10置0, 缓存0的2位*/
			if(InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State7, &V_ucJudgeBuffer3[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag)!=C_OK)/*电表运行状态字7写数据层*/
			{																		/*写电表运行状态字，出错，就不做动作*/
	// 			PF_CopyDataBytes(&V_ucJudgeBuffer3[C_Judge_StartBuffer0], &GStr_ACPowerFailStr.MeterState, V_ClearLength);/*电表运行状态字7写数据错误，清零*/
				return;
			}/*读数据成功后，再写数据层，写数据层成功后再操作结构体*/
			GStr_OpenTerminalCoverStr.CloseCoverState=C_LowPowerEnd_EventMsg;
			PF_CopyDataBytes(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], GStr_OpenTerminalCoverStr.EndTime, C_EventTimeLength);/*事件结构体，时间赋值*/
		    SF_Str_CalCRC(C_OpenTerminalCoverEventNo);
//			V_CRC=PF_Cal_CRC(&GStr_OpenTerminalCoverStr.OpenCoverState, C_Str_CoverRecord_Length);/*计算CRC*/
//			PF_Ushort16ToBuffer2(GStr_OpenTerminalCoverStr.V_CRC, &V_CRC);
			GV_ucEvent_Hstate[C_OpenTerminalCoverEventNo]=C_End_EventState;/*历史状态赋值*/
		}
	}
}
#endif
/**********************************************************************************
函数原型：void Inf_LowPowerMeterStatus(void)
功能描述：低功耗下置电表运行状态字
输入参数：无
输出参数：无
返回参数：无
功能说明：
调用机制：进入低功耗后1s时调用；
备    注：
**********************************************************************************/
void Inf_LowPowerMeterStatus(void)
{
    uchar8 V_ucMeter_WorkState4Temp[C_MeterWorkState_Length] = {C_NULL, C_NULL};
    uchar8 V_ucMeter_WorkState5Temp[C_MeterWorkState_Length] = {C_NULL, C_NULL};
    uchar8 V_ucMeter_WorkState6Temp[C_MeterWorkState_Length] = {C_NULL, C_NULL};
    uchar8 V_ucMeter_WorkState7Temp[C_MeterWorkState_Length] = {C_NULL, C_NULL};
    uchar8 V_ucReturnData;
    ushort16 V_usMeterStateLenth = C_MeterWorkState_Length, V_usEncode;

    InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State4, &V_ucMeter_WorkState4Temp[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag);/*电表运行状态字4赋值*/
    InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State5, &V_ucMeter_WorkState5Temp[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag);/*电表运行状态字5赋值*/
    InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State6, &V_ucMeter_WorkState6Temp[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag);/*电表运行状态字6赋值*/

    V_ucReturnData = InF_GetData_ObjectManage(CMeter_Work_State7, V_ucMeter_WorkState7Temp, &V_usMeterStateLenth, &V_usEncode);
    if(V_ucReturnData == C_OK)
    {
        V_ucMeter_WorkState7Temp[0] &= 0x30;
        V_ucMeter_WorkState7Temp[1] &= C_Bit0_End;

        InF_Write_Data(C_Msg_PowerNetworkMonitoring, CMeter_Work_State7, &V_ucMeter_WorkState7Temp[C_Judge_StartBuffer0], C_MeterWorkState_Length, C_W_SafeFlag);/*电表运行状态字7赋值*/
    }
}

/***********************************************************************************
函数原型：void SF_CalAh_Judgemsg(void)
功能描述：计算Ah数
输入参数：
输出参数：
返回参数：
功能说明：每秒调用一次，计算Ah数
调用机制：
备    注：
***********************************************************************************/
void SF_CalAh_Judgemsg(void)
{
	uchar8 	V_ucEventNo;
	uchar8	V_ucJudgeBuffer1[C_Judge_20BufferLength];
	ushort16 V_usBufferLength1 = C_Judge_20BufferLength, V_usEncode;

	for(V_ucEventNo = C_AlossvoltageEventNo;V_ucEventNo <= C_CLossphaseEventNo;V_ucEventNo ++)
	{
		if(SF_Str_CheckCRC(V_ucEventNo) != C_OK)/*如果结构体CRC错误，清零*/
		{
			SF_Str_Clear(V_ucEventNo);					/*结构体清零*/
			SF_Str_CalCRC(V_ucEventNo);
		}
		else
		{
			if(GV_ucEvent_Hstate[V_ucEventNo] != C_Happen_EventState)
			{
				continue;
			}
			else
			{
				if(InF_GetData_ObjectManage(CPhaseFF_Curr, &V_ucJudgeBuffer1[C_JudgeCurr_Buffer1], &V_usBufferLength1, &V_usEncode) == C_OK)/*获取三相电流*/
				{
                    PF_GetAbs(&V_ucJudgeBuffer1[C_JudgeCurr_Buffer1], &V_ucJudgeBuffer1[C_JudgeCurr_Buffer1], CLPhaseA_Curr);/*电流取绝对值*/
                    PF_GetAbs(&V_ucJudgeBuffer1[C_JudgeCurr_Buffer2], &V_ucJudgeBuffer1[C_JudgeCurr_Buffer2], CLPhaseA_Curr);/*电流取绝对值*/
                    PF_GetAbs(&V_ucJudgeBuffer1[C_JudgeCurr_Buffer3], &V_ucJudgeBuffer1[C_JudgeCurr_Buffer3], CLPhaseA_Curr);/*电流取绝对值*/

                    SF_HEXAddBytes(&V_ucJudgeBuffer1[C_JudgeCurr_Buffer1], &V_ucJudgeBuffer1[C_JudgeCurr_Buffer2], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Curr_Length);/*A+B*/
                    SF_HEXAddBytes(&V_ucJudgeBuffer1[C_JudgeCurr_Buffer3], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], C_Curr_Length);/*A+B+C*/

                    SF_HEXAddBytes(&V_ucJudgeBuffer1[C_JudgeCurr_Buffer1], Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_AAhAddr, Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_AAhAddr, C_Curr_Length);
                    SF_HEXAddBytes(&V_ucJudgeBuffer1[C_JudgeCurr_Buffer2], Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_BAhAddr, Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_BAhAddr, C_Curr_Length);
                    SF_HEXAddBytes(&V_ucJudgeBuffer1[C_JudgeCurr_Buffer3], Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_CAhAddr, Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_CAhAddr, C_Curr_Length);
                    SF_HEXAddBytes(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_TotalAhAddr, Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_TotalAhAddr, C_Curr_Length);

                    while(PF_Campare_Data(Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_AAhAddr, (uchar8 *)C_ucAhEquivalent, C_Curr_Length) != C_LessThan)/*A相Ah写RAM地址*/
					{
						SF_HEXDECBytes(Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_AAhAddr, (uchar8 *)C_ucAhEquivalent, Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_AAhAddr, C_Curr_Length);				/*大于，减去0.01Ah*/
						SF_HEXAddBytes(Str_RAMAhTable1[V_ucEventNo-C_AddAhBaseNo].P_AAhAddr, (uchar8 *)C_ucAddAh, Str_RAMAhTable1[V_ucEventNo-C_AddAhBaseNo].P_AAhAddr, C_Ah_Length);							/*RAM中数据加0.01*/
					}
					while(PF_Campare_Data(Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_BAhAddr, (uchar8 *)C_ucAhEquivalent, C_Curr_Length) != C_LessThan)/*B相Ah写RAM地址*/
					{
						SF_HEXDECBytes(Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_BAhAddr, (uchar8 *)C_ucAhEquivalent, Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_BAhAddr, C_Curr_Length);				/*大于，减去0.01Ah*/
						SF_HEXAddBytes(Str_RAMAhTable1[V_ucEventNo-C_AddAhBaseNo].P_BAhAddr, (uchar8 *)C_ucAddAh, Str_RAMAhTable1[V_ucEventNo-C_AddAhBaseNo].P_BAhAddr, C_Ah_Length);							/*RAM中数据加0.01*/
					}
					while(PF_Campare_Data(Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_CAhAddr, (uchar8 *)C_ucAhEquivalent, C_Curr_Length) != C_LessThan)/*C相Ah写RAM地址*/
					{
						SF_HEXDECBytes(Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_CAhAddr, (uchar8 *)C_ucAhEquivalent, Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_CAhAddr, C_Curr_Length);				/*大于，减去0.01Ah*/
						SF_HEXAddBytes(Str_RAMAhTable1[V_ucEventNo-C_AddAhBaseNo].P_CAhAddr, (uchar8 *)C_ucAddAh, Str_RAMAhTable1[V_ucEventNo-C_AddAhBaseNo].P_CAhAddr, C_Ah_Length);							/*RAM中数据加0.01*/
					}
					while(PF_Campare_Data(Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_TotalAhAddr, (uchar8 *)C_ucAhEquivalent, C_Curr_Length) != C_LessThan)/*总Ah写RAM地址*/
					{
						SF_HEXDECBytes(Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_TotalAhAddr, (uchar8 *)C_ucAhEquivalent, Str_RAMAhTable2[V_ucEventNo-C_AddAhBaseNo].P_TotalAhAddr, C_Curr_Length);				/*大于，减去0.01Ah*/
						SF_HEXAddBytes(Str_RAMAhTable1[V_ucEventNo-C_AddAhBaseNo].P_TotalAhAddr, (uchar8 *)C_ucAddAh, Str_RAMAhTable1[V_ucEventNo-C_AddAhBaseNo].P_TotalAhAddr, C_Ah_Length);							/*RAM中数据加0.01*/
					}
					SF_Str_CalCRC(V_ucEventNo);
				}
			}
		}
	}
}

/***********************************************************************************
函数原型：void SF_RenewalData_Judgemsg(void)
功能描述：更新事件发生过程中数据
输入参数：
输出参数：
返回参数：
功能说明：每秒调用一次，计算Ah数
调用机制：
备    注：
***********************************************************************************/
void SF_RenewalData_Judgemsg(void)
{
	uchar8 	V_ucEventNo, V_ucTableNo, V_UnbalanceNo;
	uchar8	V_ucJudgeBuffer1[C_Judge_20BufferLength];
	uchar8	V_ucJudgeBuffer2[C_Judge_20BufferLength];
	ushort16 V_usBufferLength1 = C_Judge_20BufferLength, V_usEncode;
    uchar8  V_ucSign[2];

	for(V_ucEventNo = C_OverForwardActiveEventNo;V_ucEventNo <= C_4OverIdleDemandEventNo;V_ucEventNo ++)
	{
		if(SF_Str_CheckCRC(V_ucEventNo) != C_OK)/*如果结构体CRC错误，清零*/
		{
            SF_Str_Clear(V_ucEventNo);					/*结构体清零*/
            SF_Str_CalCRC(V_ucEventNo);
		}
		if(GV_ucEvent_Hstate[V_ucEventNo] != C_Happen_EventState)
		{
			continue;
		}
        InF_GetData_ObjectManage(CCurr_AcDemand, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode);/*有功需量*/
        V_ucSign[0] = PF_GetAbs(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ucJudgeBuffer1[C_Judge_StartBuffer0], CLCurr_AcDemand);/*获取绝对值，并置正负标识*/

        V_usBufferLength1 = CLCurr_ReDemand;
        InF_GetData_ObjectManage(CCurr_ReDemand, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode);/*无功需量*/

        V_ucSign[1] = PF_GetAbs(&V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_ucJudgeBuffer2[C_Judge_StartBuffer0], CLCurr_ReDemand);/*获取绝对值，并置正负标识*/

        if( ((V_ucEventNo == C_OverForwardActiveEventNo) && (V_ucSign[0] != C_Minus))
          || ((V_ucEventNo == C_OverReverseActiveEventNo) && (V_ucSign[0] == C_Minus)) )
        {
            if(PF_Campare_Data(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], CommunicateReadTable[V_ucEventNo + C_OverDemandBaseNo].DataRAMAddr, C_Demand_Length) == C_GreaterThan)
            {
                V_usBufferLength1 = CLDate_Week_Time; /*V0.2新增长度赋值*/
                if(InF_GetData_ObjectManage(CDate_Time, &V_ucJudgeBuffer1[C_Judge_StartBuffer4], &V_usBufferLength1, &V_usEncode) == C_OK)
                {
                    PF_CopyDataBytes(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], CommunicateReadTable[V_ucEventNo + C_OverDemandBaseNo].DataRAMAddr, C_DemandTime_Length);
                    SF_Str_CalCRC(V_ucEventNo);
                }
            }
        }
        else if( ((V_ucEventNo==C_1OverIdleDemandEventNo) && (V_ucSign[0] != C_Minus) && (V_ucSign[1] != C_Minus))/*有功正，无功正*/
           || ((V_ucEventNo==C_2OverIdleDemandEventNo) && (V_ucSign[0] == C_Minus) && (V_ucSign[1] != C_Minus))/*有功负，无功正*/
           || ((V_ucEventNo==C_3OverIdleDemandEventNo) && (V_ucSign[0] == C_Minus) && (V_ucSign[1] == C_Minus))/*有功负，无功负*/
           || ((V_ucEventNo==C_4OverIdleDemandEventNo) && (V_ucSign[0] != C_Minus) && (V_ucSign[1] == C_Minus)) )/*有功正，无功负*/
        {
            if(PF_Campare_Data(&V_ucJudgeBuffer2[C_Judge_StartBuffer0], CommunicateReadTable[V_ucEventNo + C_OverDemandBaseNo].DataRAMAddr, C_Demand_Length) == C_GreaterThan)
            {
                V_usBufferLength1 = CLDate_Week_Time; /*V0.2新增长度赋值*/
                if(InF_GetData_ObjectManage(CDate_Time, &V_ucJudgeBuffer2[C_Judge_StartBuffer4], &V_usBufferLength1, &V_usEncode) == C_OK)
                {
                    PF_CopyDataBytes(&V_ucJudgeBuffer2[C_Judge_StartBuffer0], CommunicateReadTable[V_ucEventNo+C_OverDemandBaseNo].DataRAMAddr, C_DemandTime_Length);
                    SF_Str_CalCRC(V_ucEventNo);
                }
            }
        }
    }
	for(V_UnbalanceNo = 0;V_UnbalanceNo <= 2;V_UnbalanceNo ++)
	{
		if(V_UnbalanceNo < 2)
		{
			V_ucEventNo = V_UnbalanceNo + 27;
			V_ucTableNo = V_ucEventNo + C_UnbalanceBaseNo;
		}
		else
		{
			V_ucEventNo = V_UnbalanceNo + 47;
			V_ucTableNo = V_ucEventNo + C_SUnbalanceBaseNo;
		}

		if(SF_Str_CheckCRC(V_ucEventNo) != C_OK)/*如果结构体CRC错误，清零*/
		{
			SF_Str_Clear(V_ucEventNo);					/*结构体清零*/
			SF_Str_CalCRC(V_ucEventNo);
		}
		if(GV_ucEvent_Hstate[V_ucEventNo] != C_Happen_EventState)
		{
			continue;
		}
		SF_Get_UnbalanceRate_RealTime(V_ucEventNo, &V_ucJudgeBuffer1[C_Judge_StartBuffer0]);
        if(PF_Campare_Data(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], CommunicateReadTable[V_ucTableNo].DataRAMAddr, C_Unbalance_Length) == C_GreaterThan)
        {
            PF_CopyDataBytes(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], CommunicateReadTable[V_ucTableNo].DataRAMAddr, C_Unbalance_Length);
            SF_Str_CalCRC(V_ucEventNo);
        }
	}
	SF_CalAh_Judgemsg();
}
/***********************************************************************************
函数原型：void SF_CalAddTime_Judgemsg(void)
功能描述：计算累计时间
输入参数：
输出参数：
返回参数：
功能说明：每分钟调用一次，计算事件累计时间
调用机制：
备    注：
***********************************************************************************/
void SF_CalAddTime_Judgemsg(void)
{
	uchar8  V_uci, EventNo;
	ulong32	V_AddTime;
//    uchar8  *P_AddTemp=(uchar8 *)C_ucAddOneMin;
	for(V_uci=C_TotalVoltageLoseEventNo;V_uci<=C_EventNum_AddTime38;V_uci++)	/*事件抄读表格中的时间序号*/
	{
		if(V_uci<=1)								/*全失压和辅助电源*/
		{
			EventNo=V_uci;
		}
		else
		{
			EventNo=V_uci+C_AddTimeBaseNo;			/*后面的事件总累计时间在表格中的序号与用于判断事件发生恢复表格中序号差11*/
		}
		if(SF_Str_CheckCRC(EventNo)!=C_OK)
		{
			SF_Str_Clear(EventNo);				/*结构体清零*/
			SF_Str_CalCRC(EventNo);
		}
		if(GV_ucEvent_Hstate[EventNo]==C_Happen_EventState)
		{
			PF_BufferXToUlong32(CommunicateReadTable[V_uci].DataRAMAddr, &V_AddTime, C_AddTime_Length);	/*转HEX*/
			V_AddTime++;										/*加1*/
			PF_Ulong32ToBufferX(CommunicateReadTable[V_uci].DataRAMAddr, &V_AddTime, C_AddTime_Length);
			SF_Str_CalCRC(EventNo);		/*计算CRC*/
		}
	}

	for(V_uci=C_EventNum_AddTime100;V_uci<=C_EventNum_AddTime113;V_uci++)	/*新增事件抄读表格中的时间序号*/
	{
		if(V_uci<=C_EventNum_AddTime110)								/*新增事件调整序号*/
		{
			EventNo=V_uci - 98;
		}
		else
		{
			EventNo=V_uci - 61;
		}
		if(SF_Str_CheckCRC(EventNo)!=C_OK)
		{
			SF_Str_Clear(EventNo);				/*结构体清零*/
			SF_Str_CalCRC(EventNo);
		}
		if(GV_ucEvent_Hstate[EventNo]==C_Happen_EventState)
		{
			PF_BufferXToUlong32(CommunicateReadTable[V_uci].DataRAMAddr, &V_AddTime, C_AddTime_Length);	/*转HEX*/
			V_AddTime++;										/*加1*/
			PF_Ulong32ToBufferX(CommunicateReadTable[V_uci].DataRAMAddr, &V_AddTime, C_AddTime_Length);
			SF_Str_CalCRC(EventNo);		/*计算CRC*/
		}
	}

}
/***********************************************************************************
函数原型：void SF_WriteAddTime_Judgemsg(void)
功能描述：计算累计时间
输入参数：事件消息号
输出参数：无
返回参数：无1
功能说明：事件写函数中调用，此处不做清零，不做CRC(此两项放到写函数中去写)
调用机制：
备    注：
***********************************************************************************/
void SF_WriteAddTime_Judgemsg(uchar8 EventNo)
{
	uchar8 V_uci, V_ucj;
	uchar8 V_ucJudgeBuffer1[C_Judge_10BufferLength];
	ushort16 V_usJudgeBufferLength1 = C_Judge_10BufferLength, V_usEncode;
	ulong32 V_ulAddTime1, V_ulAddTime2;

	if(SF_Judge_EventIntegrity(EventNo) == C_Happen_EventState)
	{
		for(V_uci = 0;V_uci < C_AddTimeDataNumbersLength;V_uci ++)
		{
			if(V_uci < 39)
			{
				V_ucj = V_uci;
			}
			else
			{
				V_ucj = V_uci +  61;
			}
			if(EventNo == CommunicateReadTable[V_ucj].EventNo)
			{
				if(InF_GetData_ObjectManage(CommunicateReadTable[V_ucj].DataCode, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usJudgeBufferLength1, &V_usEncode) == C_OK)
				{
					PF_BufferXToUlong32(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ulAddTime1, C_AddTime_Length);	/*转HEX*/

                    PF_BufferXToUlong32(CommunicateReadTable[V_ucj].DataRAMAddr, &V_ulAddTime2, C_AddTime_Length);		/*转HEX*/

                    V_ulAddTime1 += V_ulAddTime2;

                    PF_Ulong32ToBufferX(&V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_ulAddTime1, C_AddTime_Length);

                    InF_Write_Data(C_Msg_PowerNetworkMonitoring, CommunicateReadTable[V_ucj].DataCode, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], CommunicateReadTable[V_ucj].Length, C_W_SafeFlag);/*事件累计时间写数据*/
					return;
				}
			}
		}
	}
}

/*******************************************************************************
函数原型：uchar8 Inf_Get_PowerDownEvent_Data(uchar8 V_ucEventNo, uchar8 *P_DataBuffer , ushort16 *P_DataLen)
功能描述：低功耗下获取掉电数据
输入参数：V_ucEventNo：事件号  P_DataBuffer：缓存  P_DataLen：长度
输出参数：
返回参数： C_Error：错误；C_OK：正确组帧
调用位置：
备    注：
*******************************************************************************/
uchar8 Inf_Get_PowerDownEvent_Data(uchar8 V_ucEventNo, uchar8 *pV_DataBuffer , ushort16 *pV_DataLen)
{
	uchar8		V_ucJudgeBuffer1[C_Judge_300BufferLength] = {0}, V_ucJudgeBuffer2[C_Judge_10BufferLength] = {0};
	uchar8		V_uci, V_ucEvent_Flag, V_ucReturnFlag = C_Error;
	ushort16	V_usOffset = 0, V_usResidualLength, V_usJudgeBufferLength1, V_usBufferLength2 = C_Judge_10BufferLength, V_usEncode;

    for(V_uci = 0; V_uci < EventMappingTable_Len; V_uci++)
	{
		if(EventMappingTable[V_uci].EventNo == V_ucEventNo)
		{
			break;
		}
	}
	if(V_uci < EventMappingTable_Len)
	{
        if(InF_GetData_ObjectManage(CDate_Time, &V_ucJudgeBuffer2[C_Judge_StartBuffer0], &V_usBufferLength2, &V_usEncode) == C_OK)		/*读系统当前时间*/
        {
            V_usJudgeBufferLength1 = 4;
            if(InF_GetData_ObjectManage(EventMappingTable[V_uci].Degree, V_ucJudgeBuffer1, &V_usJudgeBufferLength1, &V_usEncode) == C_OK)		/*赋事件序号*/
            {
                V_usOffset += 4;

                PF_CopyDataBytes(V_ucJudgeBuffer2, &V_ucJudgeBuffer1[V_usOffset], C_EventTimeLength);				/*赋事件发生时间，结束时间为00000000000000*//*获取事件发生时刻*/
                V_usOffset += CLDate_Week_Time;     /*发生时间*/
				memset(V_ucJudgeBuffer1 + V_usOffset, 0xAA, CLDate_Week_Time);
                V_usOffset += CLDate_Week_Time;     /*结束时间*/

                if(EventMappingTable[V_uci].SourceFlag == 0x01)		/*若有发生源赋空*/
                {
                    V_usOffset += 1;
                }
                V_usOffset += CLEventReport;/*新增上报状态偏移*/

                V_usResidualLength = 300 - V_usOffset;				/*剩余buff长度*/

                V_ucEvent_Flag = 0x01;

                if(Inf_GetRecordData(&V_ucJudgeBuffer1[V_usOffset], &V_usResidualLength, EventMappingTable[V_uci].OADTab, V_ucEvent_Flag) == C_OK)	/*获取关联OAD数据*/
                {
                    V_usOffset += V_usResidualLength;			/*数据总长度*/
                    memcpy(pV_DataBuffer, V_ucJudgeBuffer1 , V_usOffset);
                    *pV_DataLen = V_usOffset;
                    V_ucReturnFlag = C_OK;
                }
            }
        }
	}
    return V_ucReturnFlag;
}
/*******************************************************************************
函数原型：void SF_Write_EventCurrentRelate(uchar8 V_ucEventNo, *pV_DataBuffer)
功能描述：事件写消息函数
输入参数：
输出参数：
返回参数：
调用位置：
备    注： 判断消息发生时触发
*******************************************************************************/
void SF_Write_EventCurrentRelate(uchar8 V_ucEventNo, uchar8 *pV_DataBuffer)
{
	uchar8		V_ucJudgeBuffer1[C_Judge_300BufferLength] = {0};
	uchar8		V_uci, V_ucEvent_Flag;
	ushort16	V_usOffset = 0, V_usResidualLength;
	ushort16	V_usJudgeBufferLength1, V_usEncode;

	for(V_uci = 0; V_uci < EventMappingTable_Len; V_uci++)
	{
		if(EventMappingTable[V_uci].EventNo == V_ucEventNo)
		{
			break;
		}
	}

	if(V_uci >= EventMappingTable_Len)
	{
		return;
	}

	if(*(pV_DataBuffer + C_PTTime_Msgbuffer) == Pt_HappenTime)
	{
		if(SF_Judge_EventIntegrity(V_ucEventNo) != C_Happen_EventState)		/*如果历史状态有发生无恢复, 退出*/
		{
			V_usJudgeBufferLength1 = CLAll_Loss_Vol_Degree;
			InF_GetData_ObjectManage(EventMappingTable[V_uci].Degree, V_ucJudgeBuffer1, &V_usJudgeBufferLength1, &V_usEncode);			/*赋事件序号*/
			V_usOffset += CLEventDegree;

			PF_CopyDataBytes(pV_DataBuffer + 3, &V_ucJudgeBuffer1[V_usOffset], C_EventTimeLength);				/*赋事件发生时间，结束时间为00000000000000*//*获取事件发生时刻*/
			V_usOffset += CLDate_Time;
			V_usOffset += CLDate_Time;

			if(EventMappingTable[V_uci].SourceFlag == 0x01)		/*若有发生源赋空*/
			{
				V_usOffset += CLEventSource;
			}
            V_usOffset += CLEventReport;/*新增上报状态偏移*/

			if((V_ucEventNo == C_OverForwardActiveEventNo)||
			   (V_ucEventNo == C_OverReverseActiveEventNo)||
			   (V_ucEventNo == C_1OverIdleDemandEventNo)||
			   (V_ucEventNo == C_2OverIdleDemandEventNo)||
			   (V_ucEventNo == C_3OverIdleDemandEventNo)||
			   (V_ucEventNo == C_4OverIdleDemandEventNo))
			{
				V_usOffset += C_OverDemandRenew_Length;
			}

			V_usResidualLength = 300 - V_usOffset;		/*剩余buff长度*/
			V_ucEvent_Flag = 0x01;
			if(Inf_GetRecordData(&V_ucJudgeBuffer1[V_usOffset], &V_usResidualLength, EventMappingTable[V_uci].OADTab, V_ucEvent_Flag) != C_OK)	/*获取关联OAD数据*/
			{
				return;
			}
			V_usOffset += V_usResidualLength;			/*数据总长度*/
			if(InF_Write_Data(C_Msg_PowerNetworkMonitoring, EventMappingTable[V_uci].WriteOAD, V_ucJudgeBuffer1, V_usOffset, C_W_SafeFlag) == C_OK)		/*事件发生写数据*/
			{
					Inf_EventReport_HP(V_ucEventNo, C_Happen_EventReport);
					InF_ActiveReportSetting(ActiveReportTable[V_ucEventNo]);
			}
		}
        if ( ( V_ucEventNo == C_PowerfailEventNo ) )
        {
            if(Inf_SatisfyPowerOnTime() != C_OK)         /*掉电时不满1小时掉电发生时清零，如果满1小时的不清零等掉电结束后再清零*/
            {
                Inf_Clear_PowerOffShutAcReportTime();
            }
		}
	}
	else
	{
		if(*(pV_DataBuffer + C_PTTime_Msgbuffer) == Pt_EndTime)
		{
			if( ( SF_Str_CheckCRC(V_ucEventNo) ) == C_OK )
			{
				if(SF_Judge_EventIntegrity(V_ucEventNo) == C_Happen_EventState)		/*如果历史状态是有发生无恢复*/
				{
#if 0	/*数据层目前写结束和发生数据为同一标识码写入，所以结束时为不覆盖原有数据，此处不写序号*/
					V_usJudgeBufferLength1 = CLLossA_Vol_Degree;
					InF_GetData_ObjectManage(EventMappingTable[V_uci].Degree, V_ucJudgeBuffer1, &V_usJudgeBufferLength1, &V_usEncode);
#endif
					V_usOffset += CLEventDegree;
#if 0	/*同上面，写恢复时发生时间不用写*/
					V_ulRead_OAD_Hp[0] = EventHappenEndTime[V_ucEventNo];
					V_ulRead_OAD_Hp[1] = CEventHPTime;
					V_ulRead_OAD_Hp[2] = 0xFFFFFFFF;

					V_ucBufferLen = C_EventTimeLength;
                    SF_ReadLastEvt(V_ulRead_OAD_Hp, &V_ucJudgeBuffer1[V_usOffset], &V_ucBufferLen, (uchar8)V_ulRead_OAD_Hp[0]);
#endif
					V_usOffset += CLDate_Time;
					PF_CopyDataBytes(pV_DataBuffer + 3, &V_ucJudgeBuffer1[V_usOffset], C_EventTimeLength);		/*赋事件结束时间，发生时间为00000000000000*/
					V_usOffset += CLDate_Time;

					if(EventMappingTable[V_uci].SourceFlag == 0x01)		/*若有发生源赋空*/
					{
						V_usOffset += CLEventSource;
					}
                    V_usOffset += CLEventReport;/*新增上报状态偏移*/

					switch(V_ucEventNo)
					{
						case	C_OverForwardActiveEventNo:
								PF_CopyDataBytes(GStr_OverForwardActiveStr.Renewal, &V_ucJudgeBuffer1[V_usOffset], C_OverDemandRenew_Length);
								V_usOffset += C_OverDemandRenew_Length;
								break;
						case	C_OverReverseActiveEventNo:
								PF_CopyDataBytes(GStr_OverReverseActiveStr.Renewal, &V_ucJudgeBuffer1[V_usOffset], C_OverDemandRenew_Length);
								V_usOffset += C_OverDemandRenew_Length;
								break;
						case	C_1OverIdleDemandEventNo:
								PF_CopyDataBytes(GStr_Over1IdleDemandStr.Renewal, &V_ucJudgeBuffer1[V_usOffset], C_OverDemandRenew_Length);
								V_usOffset += C_OverDemandRenew_Length;
								break;
						case	C_2OverIdleDemandEventNo:
								PF_CopyDataBytes(GStr_Over2IdleDemandStr.Renewal, &V_ucJudgeBuffer1[V_usOffset], C_OverDemandRenew_Length);
								V_usOffset += C_OverDemandRenew_Length;
								break;
						case	C_3OverIdleDemandEventNo:
								PF_CopyDataBytes(GStr_Over3IdleDemandStr.Renewal, &V_ucJudgeBuffer1[V_usOffset], C_OverDemandRenew_Length);
								V_usOffset += C_OverDemandRenew_Length;
								break;
						case	C_4OverIdleDemandEventNo:
								PF_CopyDataBytes(GStr_Over4IdleDemandStr.Renewal, &V_ucJudgeBuffer1[V_usOffset], C_OverDemandRenew_Length);
								V_usOffset += C_OverDemandRenew_Length;
								break;
						default:
								break;
					}

					V_usResidualLength = 300 - V_usOffset;		/*剩余buff长度*/
					V_ucEvent_Flag = 0x02;

					switch(V_ucEventNo)								/*有发生过程中数据的事件增加区分*/
					{
						case	C_AlossvoltageEventNo:
								V_ucEvent_Flag |= 0x10;
								break;
						case	C_BlossvoltageEventNo:
								V_ucEvent_Flag |= 0x20;
								break;
						case	C_ClossvoltageEventNo:
								V_ucEvent_Flag |= 0x30;
								break;
						case	C_ALessvoltageEventNo:
								V_ucEvent_Flag |= 0x40;
								break;
						case	C_BLessvoltageEventNo:
								V_ucEvent_Flag |= 0x50;
								break;
						case	C_CLessvoltageEventNo:
								V_ucEvent_Flag |= 0x60;
								break;
						case	C_AOvervoltageEventNo:
								V_ucEvent_Flag |= 0x70;
								break;
						case	C_BOvervoltageEventNo:
								V_ucEvent_Flag |= 0x80;
								break;
						case	C_COvervoltageEventNo:
								V_ucEvent_Flag |= 0x90;
								break;
						case	C_ALossphaseEventNo:
								V_ucEvent_Flag |= 0xA0;
								break;
						case	C_BLossphaseEventNo:
								V_ucEvent_Flag |= 0xB0;
								break;
						case	C_CLossphaseEventNo:
								V_ucEvent_Flag |= 0xC0;
								break;
						case	C_UnbanlanceVoltageEventNo:
								V_ucEvent_Flag |= 0xD0;
								break;
						case	C_UnbanlanceCurrentEventNo:
								V_ucEvent_Flag |= 0xE0;
								break;
						case	C_SUnbanlanceCurrentEventNo:
								V_ucEvent_Flag |= 0xF0;
								break;
						default:
								break;
					}
					if(Inf_GetRecordData(&V_ucJudgeBuffer1[V_usOffset], &V_usResidualLength, EventMappingTable[V_uci].OADTab, V_ucEvent_Flag) != C_OK)	/*获取关联OAD数据*/
					{
						return;
					}
					V_usOffset += V_usResidualLength;			/*数据总长度*/
					if(InF_Write_Data(C_Msg_PowerNetworkMonitoring, EventMappingTable[V_uci].WriteOAD + 0x00000001, V_ucJudgeBuffer1, V_usOffset, C_W_SafeFlag) == C_OK)/*事件结束写数据*/
                    {
                        Inf_EventReport_HP(V_ucEventNo, C_End_EventReport);
                    }
				}
			}

            if ( ( V_ucEventNo == C_PowerfailEventNo ) )
            {
                Inf_Clear_PowerOffShutAcReportTime();                       /*上电满1小时时间在写掉电结束时清零，重新开始计时*/
            }
		}
	}
}

/***********************************************************************************
函数原型：uchar8 SF_EventClear_Judgemsg(uchar8 EventNo)
功能描述：清零函数
输入参数：
输出参数：
返回参数：
功能说明：事件清零接口函数
调用机制：通信清零时调用
备    注：
***********************************************************************************/
uchar8 SF_EventClear_Judgemsg(uchar8 EventNo)
{
	uchar8	V_uci;

	if( ( EventNo == C_AllEventNo ) || ( EventNo == C_ClockFaEventNo) )/*如果是时钟故障事件, 不能挪后面要放这里*/
	{
		InF_ExecuteClr_RTC();				/*时钟故障标志*/
		InF_Clear_BroadTimeAbnormalTime();	/*清广播校时异常时间*/
	}

	if(EventNo == C_AllEventNo)
	{
		for(EventNo = C_TotalVoltageLoseEventNo;EventNo <= C_NeutralCurrentAbnormalEventNo;EventNo++)
		{
			GV_ucEvent_Hstate[EventNo] = C_End_EventState;
			GV_ucEvent_JudgeTimer[EventNo] = C_NULL;

			SF_Str_Clear(EventNo);
			SF_Str_CalCRC(EventNo);
		}
	}
	else
	{
		for(V_uci = 0;V_uci < Str_698EventReport_Len;V_uci ++)		/*确定对应事件*/
		{
			if(EventNo == Str_698EventReport[V_uci].EventNo)
			{
				break;
			}
		}

		if(V_uci >= Str_698EventReport_Len)
		{
			return C_IDError;
		}

        Inf_ReportList(C_ReportChannelAll, EventNo, C_DeletReport);///跟随上报
        SF_Clear645_ReportNewAddNum(EventNo, C_EventCLEAR);//698兼容645新增，清645主动上报

		if(EventNo <= C_NeutralCurrentAbnormalEventNo)
		{
			GV_ucEvent_Hstate[EventNo] = C_End_EventState;
			GV_ucEvent_JudgeTimer[EventNo] = C_NULL;

			SF_Str_Clear(EventNo);
			SF_Str_CalCRC(EventNo);
        }
        else
        {
           return(C_IDError);
        }
	}

	SF_MeterStatus_Judgemsg();
	return(C_OK);
}
/***********************************************************************************
函数原型：uchar8 Inf_ReadEventRenew(ulong32 *V_Data_Id, uchar8 *pV_Data, uchar8 pV_Data_Length)
功能描述：通信读取事件发生过程中的数据
输入参数：
           *V_Data_Id     支持单项数据读取，格式1：单OAD V_Data_Id[0]为需读OAD，V_Data_Id[1]=0xFFFFFFFF表示结束
						格式2：双OAD V_Data_Id[0]为所读事件OAD，V_Data_Id[1]为具体数据，V_Data_Id[2]=0xFFFFFFFF表示结束
           *pV_Data                      所读数据指针
           *pV_Data_Length               缓冲区pV_Data最大长度
输出参数： *pV_Data                      读出数据；
           *pV_Data_Length               读数据的实际长度
返回参数：  C_IDError:不支持读取的数据标识，C_DataLenError数据长度错, C_OK:正确执行
            InF_GetData_ObjectManage()所能返回的任何值
功能说明：支持最近1次事件反生过程中Ah数/最大不平衡率/需量超限期间最大需量及时间，最近一次失压起始时间/最近一次失压结束时间
          事件总累计时间及失压总次数（CommunicateReadTable[V_uci].DataCode）
调用机制：通信调用
备    注：*pV_Data_Length必须大于等于所取值长度，不然返回错误；
***********************************************************************************/
uchar8 Inf_ReadEventRenew(ulong32 *V_Data_Id, uchar8 *pV_Data, uchar8 *pV_Data_Length)
{
	uchar8	V_ucJudgeBuffer1[C_Judge_30BufferLength] = {0};			/*失压总次数和分相失压次数, 失压总时间和分相失压时间*/
    uchar8	V_ucJudgeBuffer2[C_Judge_10BufferLength] = {C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL};/*数据全0*/
	ushort16 V_usJudgeBufferLength1 = C_Judge_30BufferLength, V_usEncode;
	uchar8	V_ucReadDataNo;
    uchar8  V_ucMode;
    ulong32	V_ulReadOAD[3], V_ulADD1, V_ulADD2;
    ulong32	V_ulData_Read = 0xFFFFFFFF;
    uchar8	V_uci;
    ushort16 V_usDataLen;

	if(V_Data_Id[1] == 0xFFFFFFFF)
	{
		V_ulData_Read = V_Data_Id[0];
	}
	else if(V_Data_Id[2] == 0xFFFFFFFF)
	{
		for(V_uci = 0;V_uci < SpecialReadTable_Len;V_uci ++)
		{
			if(V_Data_Id[0] == SpecialReadTable[V_uci].EventOAD)
			{
				break;
			}
		}
		if(V_uci >= SpecialReadTable_Len)
		{
			return C_IDError;
		}
		switch(V_Data_Id[1])
		{
			case	C_TolAh_E:
			case	C_VolUnbalanceRate_E:
			case	C_CurUnbalanceRate_E:
			case	CPos_Ac_De_Over_1:
			case	CRev_Ac_De_Over_1:
			case	CQua1_Re_De_Over_1:
			case	CQua2_Re_De_Over_1:
			case	CQua3_Re_De_Over_1:
			case	CQua4_Re_De_Over_1:
				V_ulData_Read = SpecialReadTable[V_uci].TolAh;
				break;
			case	C_AAh_E:
				V_ulData_Read = SpecialReadTable[V_uci].AAh;
				break;
			case	C_BAh_E:
				V_ulData_Read = SpecialReadTable[V_uci].BAh;
				break;
			case	C_CAh_E:
				V_ulData_Read = SpecialReadTable[V_uci].CAh;
				break;
			default:
				return C_IDError;
				break;
		}
	}
	else
	{
		return C_IDError;
	}

	if( (V_ulData_Read==CLoss_Vol_Hp)
       || (V_ulData_Read==CLoss_Vol_End) )
	{
		if(*pV_Data_Length >= CommunicateReadTable[39].Length)/*缓存长度大于提供的buffer长度*/
		{
			V_ulReadOAD[0] = CLossAVol_FF_1;
			V_ulReadOAD[2] = 0xFFFFFFFF;
			if(V_ulData_Read == CLoss_Vol_Hp)
			{
				V_ulReadOAD[1] = CEventHPTime;
			}
			else
			{
				V_ulReadOAD[1] = CEventEndTime;
			}
			V_usDataLen = C_EventTimeLength;
            if( (GV_ucEvent_Hstate[C_AlossvoltageEventNo] == C_Happen_EventState)
               && (V_ulReadOAD[1] == CEventEndTime) )
            {
                V_ulReadOAD[0] += 1;
            }
			V_ucMode = SF_ReadLastEvt(V_ulReadOAD, &V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1], &V_usDataLen, (uchar8)V_ulReadOAD[0]);
			if(V_ucMode == C_NoData)
			{
				V_ucMode = C_OK;
			}

			if(V_ucMode == C_OK)/*最近1次A相失压发生/结束时刻*/
			{
				V_ulReadOAD[0] = CLossBVol_FF_1;
				V_usDataLen=C_EventTimeLength;
                if( (GV_ucEvent_Hstate[C_BlossvoltageEventNo] == C_Happen_EventState)
                   && (V_ulReadOAD[1] == CEventEndTime) )
                {
                    V_ulReadOAD[0] += 1;
                }
				V_ucMode = SF_ReadLastEvt(V_ulReadOAD, &V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1+C_EventTimeLength], &V_usDataLen, (uchar8)V_ulReadOAD[0]);
				if(V_ucMode == C_NoData)
				{
					V_ucMode = C_OK;
				}
				if(V_ucMode == C_OK)/*最近1次B相失压发生/结束时刻*/
				{
					V_ulReadOAD[0] = CLossCVol_FF_1;
					V_usDataLen = C_EventTimeLength;
                    if( (GV_ucEvent_Hstate[C_ClossvoltageEventNo] == C_Happen_EventState)
                       && (V_ulReadOAD[1] == CEventEndTime) )
                    {
                        V_ulReadOAD[0] += 1;
                    }
					V_ucMode = SF_ReadLastEvt(V_ulReadOAD, &V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1 + C_EventTimeLength + C_EventTimeLength], &V_usDataLen, (uchar8)V_ulReadOAD[0]);
					if(V_ucMode == C_NoData)
					{
						V_ucMode = C_OK;
					}
					if(V_ucMode == C_OK)/*最近1次C相失压发生/结束时刻*/
					{
						if(PF_Campare_Data(&V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1], &V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1 + C_EventTimeLength], C_EventTimeLength) == C_GreaterThan)
						{
							PF_CopyDataBytes(&V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1], pV_Data, C_EventTimeLength);
						}
						else
						{
							PF_CopyDataBytes(&V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1 + C_EventTimeLength], pV_Data, C_EventTimeLength);
						}
						if(PF_Campare_Data(&V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1 + C_EventTimeLength + C_EventTimeLength], pV_Data, C_EventTimeLength) == C_GreaterThan)
						{
							PF_CopyDataBytes(&V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1 + C_EventTimeLength + C_EventTimeLength], pV_Data, C_EventTimeLength);
						}
						if(PF_Campare_Data(pV_Data, V_ucJudgeBuffer2, C_EventTimeLength) == C_Equal)	/*时间全零赋AA*/
						{
							for(V_uci = 0;V_uci < C_EventTimeLength;V_uci ++)
							{
								pV_Data[V_uci] = 0xAA;
							}
						}
						*pV_Data_Length = C_EventTimeLength;
					}
				}
			}
			return(V_ucMode);
		}
		else
		{
			return(C_DataLenError);
		}
	}
	if(V_ulData_Read == CLoss_Vol_Degree)			 		/*失压总次数*/
	{
		if(*pV_Data_Length >= CommunicateReadTable[39].Length)/*缓存长度大于提供的buffer长度*/
		{
			V_usJudgeBufferLength1 = C_Judge_30BufferLength;	/*V0.2新增长度赋值*/
			V_ucMode = InF_GetData_ObjectManage(CLossA_Vol_Degree, &V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1], &V_usJudgeBufferLength1, &V_usEncode);
			if(V_ucMode == C_OK)/*A相失压次数*/
			{
                V_usJudgeBufferLength1 = CLLossA_Vol_Degree;
				V_ucMode = InF_GetData_ObjectManage(CLossB_Vol_Degree, &V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1 + CLLossA_Vol_Degree], &V_usJudgeBufferLength1, &V_usEncode);
				if(V_ucMode == C_OK)/*B相失压次数*/
				{
                    V_usJudgeBufferLength1 = CLLossA_Vol_Degree;
					V_ucMode = InF_GetData_ObjectManage(CLossC_Vol_Degree, &V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1 + CLLossA_Vol_Degree * 2], &V_usJudgeBufferLength1, &V_usEncode);
					if(V_ucMode == C_OK)/*C相失压次数*/
					{
						SF_HEXAddBytes(&V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1], &V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1 + CLLossA_Vol_Degree], &V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1], CLLoss_Vol_Degree);
						SF_HEXAddBytes(&V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1], &V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1 + CLLossA_Vol_Degree * 2], &V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1], CLLoss_Vol_Degree);

						PF_CopyDataBytes(&V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1], pV_Data, CLLoss_Vol_Degree);
						*pV_Data_Length = CommunicateReadTable[39].Length;/*返回数据长度*/
					}
				}
			}
			return(V_ucMode);
		}
		else
		{
			return(C_DataLenError);
		}
	}
	else
	{
		if(V_ulData_Read == CLoss_Vol_Time)/*失压总累计时间*/
		{
			if(*pV_Data_Length >= CommunicateReadTable[40].Length)
			{
				if(SF_Str_CheckCRC(C_AlossvoltageEventNo) != C_OK)
				{
					SF_Str_Clear(C_AlossvoltageEventNo);
					SF_Str_CalCRC(C_AlossvoltageEventNo);
				}
				if(SF_Str_CheckCRC(C_BlossvoltageEventNo) != C_OK)
				{
					SF_Str_Clear(C_BlossvoltageEventNo);
					SF_Str_CalCRC(C_BlossvoltageEventNo);
				}
				if(SF_Str_CheckCRC(C_ClossvoltageEventNo) != C_OK)
				{
					SF_Str_Clear(C_ClossvoltageEventNo);
					SF_Str_CalCRC(C_ClossvoltageEventNo);
				}
				V_usJudgeBufferLength1 = C_Judge_30BufferLength;	/*V0.2新增长度赋值*/
				V_ucMode = InF_GetData_ObjectManage(CLossA_Vol_Time, &V_ucJudgeBuffer1[C_FourBytesJudge_Buffer1], &V_usJudgeBufferLength1, &V_usEncode);
				if(V_ucMode == C_OK)/*EE中A相累计时间, buffer3*/
				{
                    V_usJudgeBufferLength1 = CLLossB_Vol_Time;
					V_ucMode = InF_GetData_ObjectManage(CLossB_Vol_Time, &V_ucJudgeBuffer1[C_FourBytesJudge_Buffer2], &V_usJudgeBufferLength1, &V_usEncode);
					if(V_ucMode == C_OK)/*EE中B相累计时间*/
					{
                        V_usJudgeBufferLength1 = CLLossC_Vol_Time;
						V_ucMode = InF_GetData_ObjectManage(CLossC_Vol_Time, &V_ucJudgeBuffer1[C_FourBytesJudge_Buffer3], &V_usJudgeBufferLength1, &V_usEncode);
						if(V_ucMode == C_OK)/*EE中C相累计时间*/
						{
							PF_BufferXToUlong32(GStr_AlossvoltageStr.AddTime, &V_ulADD1, C_AddTime_Length);
							PF_BufferXToUlong32(GStr_BlossvoltageStr.AddTime, &V_ulADD2, C_AddTime_Length);
							V_ulADD1 += V_ulADD2;
							PF_BufferXToUlong32(GStr_ClossvoltageStr.AddTime, &V_ulADD2, C_AddTime_Length);
							V_ulADD1 += V_ulADD2;
							PF_BufferXToUlong32(&V_ucJudgeBuffer1[C_FourBytesJudge_Buffer1], &V_ulADD2, C_AddTime_Length);
							V_ulADD1 += V_ulADD2;
							PF_BufferXToUlong32(&V_ucJudgeBuffer1[C_FourBytesJudge_Buffer2], &V_ulADD2, C_AddTime_Length);
							V_ulADD1 += V_ulADD2;
							PF_BufferXToUlong32(&V_ucJudgeBuffer1[C_FourBytesJudge_Buffer3], &V_ulADD2, C_AddTime_Length);
							V_ulADD1 += V_ulADD2;
							PF_Ulong32ToBufferX(pV_Data, &V_ulADD1, C_AddTime_Length);

							*pV_Data_Length = CommunicateReadTable[40].Length;/*返回数据长度*/
						}
					}
				}
				return(V_ucMode);	/*如果读数据层不成功，返回错误*/
			}
			else
			{
				return(C_DataLenError);
			}
		}
		else
		{
			for(V_ucReadDataNo = 0;V_ucReadDataNo < C_ReadDataLength;V_ucReadDataNo ++)
			{
				if(V_ulData_Read == CommunicateReadTable[V_ucReadDataNo].DataCode)
				{
					if(*pV_Data_Length >= CommunicateReadTable[V_ucReadDataNo].Length)
					{
						if(SF_Str_CheckCRC(CommunicateReadTable[V_ucReadDataNo].EventNo) != C_OK)
						{
							SF_Str_Clear(CommunicateReadTable[V_ucReadDataNo].EventNo);
							SF_Str_CalCRC(CommunicateReadTable[V_ucReadDataNo].EventNo);
						}
						if( (V_ucReadDataNo <= C_EventNum_AddTime38)
                           || ( (V_ucReadDataNo >= C_EventNum_AddTime100) && (V_ucReadDataNo <= C_EventNum_AddTime113) ) )
						{
							PF_CopyDataBytes(CommunicateReadTable[V_ucReadDataNo].DataRAMAddr, pV_Data, CommunicateReadTable[V_ucReadDataNo].Length);
							*pV_Data_Length = CommunicateReadTable[V_ucReadDataNo].Length;
							V_usJudgeBufferLength1 = C_AddTime_Length;
							V_ucMode = InF_GetData_ObjectManage(CommunicateReadTable[V_ucReadDataNo].DataCode, &V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1], &V_usJudgeBufferLength1, &V_usEncode);
							if(V_ucMode == C_OK)
							{
								PF_BufferXToUlong32(&V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1], &V_ulADD1, C_AddTime_Length);
								PF_BufferXToUlong32(pV_Data, &V_ulADD2, C_AddTime_Length);
								V_ulADD1 += V_ulADD2;
								PF_Ulong32ToBufferX(pV_Data, &V_ulADD1, C_AddTime_Length);
							}
							else
							{
								return(V_ucMode);
							}
						}
						else
						{
							V_usDataLen = C_Judge_30BufferLength;
							V_ucMode = SF_ReadLastEvt(V_Data_Id, pV_Data, &V_usDataLen, (uchar8)V_Data_Id[0]);
							if(V_ucMode == C_OK)
							{
								if(SF_Judge_EventIntegrity(CommunicateReadTable[V_ucReadDataNo].EventNo) == C_Happen_EventState)		/*如果历史状态有发生无恢复, 用事件记录本地数据覆盖从数据层中读出的上一次数据*/
								{
									PF_CopyDataBytes(CommunicateReadTable[V_ucReadDataNo].DataRAMAddr, pV_Data, CommunicateReadTable[V_ucReadDataNo].Length);
								}
								*pV_Data_Length = CommunicateReadTable[V_ucReadDataNo].Length;
							}
						}
						return(V_ucMode);
					}
					else
					{
						return(C_DataLenError);
					}
				}
			}
		}
		if((V_ulData_Read == CAll_Loss_Vol)
           || (V_ulData_Read == CAux_Pow_Down))
		{
			V_usJudgeBufferLength1 = C_Judge_30BufferLength;	/*V0.2新增长度赋值*/
			if(V_ulData_Read == CAll_Loss_Vol)
			{		/*V0.2修改*/
				V_ucMode = InF_GetData_ObjectManage(CommunicateReadTable[0].DataCode, &V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1+C_AddNumber_Length], &V_usJudgeBufferLength1, &V_usEncode);
				if(V_ucMode == C_OK)
				{
					V_usJudgeBufferLength1 = C_AddNumber_Length;
					V_ucMode = InF_GetData_ObjectManage(CAll_Loss_Vol_Degree, &V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1], &V_usJudgeBufferLength1, &V_usEncode);
					if(V_ucMode == C_OK)
					{
						PF_BufferXToUlong32(&V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1+C_AddNumber_Length], &V_ulADD1, C_AddTime_Length);
						PF_BufferXToUlong32(CommunicateReadTable[0].DataRAMAddr, &V_ulADD2, C_AddTime_Length);
						V_ulADD1 += V_ulADD2;
						PF_Ulong32ToBufferX(&V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1+C_AddNumber_Length], &V_ulADD1, C_AddTime_Length);
					}
				}
			}
			else
			{
				V_ucMode = InF_GetData_ObjectManage(CommunicateReadTable[1].DataCode, &V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1+C_AddNumber_Length], &V_usJudgeBufferLength1, &V_usEncode);
				if(V_ucMode == C_OK)
				{
					V_usJudgeBufferLength1 = C_AddNumber_Length;
					V_ucMode = InF_GetData_ObjectManage(CAux_Pow_Down_Degree, &V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1], &V_usJudgeBufferLength1, &V_usEncode);
					if(V_ucMode == C_OK)
					{
						PF_BufferXToUlong32(&V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1+C_AddNumber_Length], &V_ulADD1, C_AddTime_Length);
						PF_BufferXToUlong32(CommunicateReadTable[1].DataRAMAddr, &V_ulADD2, C_AddTime_Length);
						V_ulADD1 += V_ulADD2;
						PF_Ulong32ToBufferX(&V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1+C_AddNumber_Length], &V_ulADD1, C_AddTime_Length);
					}
				}
			}
			PF_CopyDataBytes(&V_ucJudgeBuffer1[C_ThreeBytesJudge_Buffer1], pV_Data, C_AddTimeNumbers_Length);
			*pV_Data_Length = C_AddTimeNumbers_Length;/*返回数据长度*/
			return(V_ucMode);
		}
		return(C_IDError);
	}
}

/***********************************************************************************
函数原型：uchar8 Inf_BackLightLimit(void)
功能描述：电压全部低于临界电压，不点亮背光
输入参数：无
输出参数：无
返回参数：C_StatusError:不支持读取的数据标识
          C_OK:正确执行
功能说明：
调用机制：显示调用
备    注：
***********************************************************************************/
uchar8 Inf_BackLightLimit(void)
{
	uchar8 V_ucJudgeBuffer1[C_Judge_10BufferLength];
	ushort16 V_usBufferLength1 = C_Judge_10BufferLength, V_usEncode;

	if(InF_GetData_ObjectManage(CAuxi_Power_Sign, &V_ucJudgeBuffer1[C_Judge_StartBuffer0], &V_usBufferLength1, &V_usEncode) == C_OK)/*辅助电源类型*/
	{
		if(V_ucJudgeBuffer1[C_Judge_StartBuffer0] == C_ACPowerFail)					/*有辅助电源，未失电，值为0x01*/
		{
			if(SF_Get_Event_Cstate(C_ACPowerFailEventNo, GV_ucEvent_Hstate[C_ACPowerFailEventNo]) == C_Happen_EventState)
			{
			    V_ucJudgeBuffer1[C_Judge_StartBuffer0] = C_ACPowerFailState;				/*辅助电源失电，值为0x11*/
			}
		}
		V_ucJudgeBuffer1[C_Judge_StartBuffer1] = SF_Get_Event_Cstate(C_TotalVoltageLoseEventNo, GV_ucEvent_Hstate[C_TotalVoltageLoseEventNo]);
		V_ucJudgeBuffer1[C_Judge_StartBuffer2] = SF_Get_Event_Cstate(C_PowerfailEventNo, GV_ucEvent_Hstate[C_PowerfailEventNo]);

        if( ((V_ucJudgeBuffer1[C_Judge_StartBuffer0] == C_ACPowerFailState) || (V_ucJudgeBuffer1[C_Judge_StartBuffer0] == C_NoACPowerFail))
            && ((V_ucJudgeBuffer1[C_Judge_StartBuffer1] == C_Happen_EventState) || (V_ucJudgeBuffer1[C_Judge_StartBuffer2] == C_Happen_EventState)) )
		{
			return(C_StatusError);
		}
	}
	return(C_OK);
}


/***********************************************************************************
函数原型：void SF_Write_EventMsgFuction(Str_Msg_Parameter pStr_EventMsg)
功能描述：事件写消息函数
输入参数：
输出参数：
返回参数：
功能说明：判断消息发生时触发
调用机制：判断消息触发
备    注：
***********************************************************************************/
void SF_Write_EventMsgFuction(Str_Msg_Parameter *pStr_EventMsg)
{
	uchar8	V_ucEventNo;
	uchar8	V_ucMsg[C_Judge_20BufferLength];
	uchar8	V_ucMsgLength = pStr_EventMsg->Length;

	if(V_ucMsgLength == C_Event_MsgLength)
	{
		PF_CopyDataBytes(pStr_EventMsg->Parameter, &V_ucMsg[C_Judge_StartBuffer0], V_ucMsgLength);/*将系统调度中数据内容拷贝出来*/

        if(V_ucMsg[C_Judge_StartBuffer0] == PT_EventNo)
		{
			V_ucEventNo = V_ucMsg[1];			/*获取EventNo*/
            if(V_ucMsg[C_Judge_StartBuffer2] == Pt_EndTime)	/*电表运行状态字赋值, 累计时间*/
			{
                SF_WriteAddTime_Judgemsg(V_ucEventNo);/*累计时间存数据层*/
                if((V_ucEventNo == C_OpenMeterCoverEventNo)||(V_ucEventNo == C_OpenTerminalCoverEventNo))
                {
                    GV_ucEvent_Hstate[V_ucEventNo] = C_End_EventState;
                }
			}
            if((V_ucEventNo <= C_NeutralCurrentAbnormalEventNo)
               && (V_ucEventNo != C_PowerAbnormalEventNo))
            {
                SF_Write_EventCurrentRelate(V_ucEventNo, &V_ucMsg[C_Judge_StartBuffer0]);
            }
            else
            {
                return;
            }
			GV_ucEvent_JudgeTimer[V_ucEventNo] = C_NULL;	/*定时器清零*/
            if(GV_ucEvent_Hstate[V_ucEventNo] == C_Happen_EventState)
            {
                if(V_ucEventNo == C_TotalVoltageLoseEventNo)
                {
                    GStr_TotalvoltageloseStr.MeterState = C_Null_EventMsg;
                }
                else if(V_ucEventNo == C_ACPowerFailEventNo)
                {
                    GStr_ACPowerFailStr.MeterState = C_Null_EventMsg;
                }
                else if(V_ucEventNo == C_OpenMeterCoverEventNo)
                {
                    GStr_OpenMeterCoverStr.OpenCoverState = C_Null_EventMsg;
                }
                else if(V_ucEventNo == C_OpenTerminalCoverEventNo)
                {
                    GStr_OpenTerminalCoverStr.OpenCoverState = C_Null_EventMsg;
                }
                else if(V_ucEventNo == C_PowerfailEventNo)
                {
                    GStr_PowerfailStr.MeterState = C_Null_EventMsg;
                }
                else
                {
                    return;
                }
                SF_Str_CalCRC(V_ucEventNo);			/*事件低功耗下发生标识清零，计算CRC*/
                return;
            }
			SF_Str_Clear(V_ucEventNo);
			SF_Str_CalCRC(V_ucEventNo);			/*清零，计算CRC*/
		}
	}
}

/***********************************************************************************
函数原型：void InF_Event_Message(Str_Msg_Parameter	pStr_Msg)
功能描述：消息解析函数
输入参数：
输出参数：
返回参数：
功能说明：信息帧解析函数
调用机制：调度调用
备    注：
***********************************************************************************/
void InF_Event_Message(Str_Msg_Parameter *pStr_Msg)
{
	uchar8	V_ucEventNo;
	ulong32	V_ulDataCode;

    if(pStr_Msg->PowerFlag != C_PowerOn)/*如果目的消息不是事件判断消息，退出*/
    {
       return;
    }
    if(pStr_Msg->DerictAddr != C_Msg_PowerNetworkMonitoring)/*如果目的消息不是事件判断消息，判断是否广播总清*/
    {
        if(pStr_Msg->DerictAddr == C_Msg_BroadcastAddress)  /*电表总清，按事件全清处理*/
        {
            if(*pStr_Msg->Parameter == Pt_MeterClear)
            {
                V_ucEventNo = C_AllEventNo;
                SF_EventClear_Judgemsg(V_ucEventNo);		/*清零函数*/
            }
            return;
        }
        return;
    }
    if(pStr_Msg->SourceAddr == C_Msg_Dispatch)/*系统调度*/
    {
        if(*(pStr_Msg->Parameter) == Pt_Dispatch_Timing)			/*时钟变化*/
        {
            if(*((pStr_Msg->Parameter) + 1) == C_SystemSecondChange)	/*系统秒变化*/
            {
                SF_Judge_Event_Msg();				/*事件判断*/

                SF_RenewalData_Judgemsg();		/*事件发生过程中的实时量*/

                SF_AlarmDisplay_Judgemsg();             /*报警函数*/

				SF_SymbolDisplay_Judgemsg();	/*符号显示函数*/

				SF_MeterStatus_Judgemsg();		/*写电表运行状态字*/

				SF_CalAddTime_Judgemsg();/*计算累计时间*/
            }
            else
            {
                return;
            }
        }
        else
        {
            return;
        }
    }
    else
    {
        if(pStr_Msg->SourceAddr == C_Msg_Communication)	/*通信*/
        {
            if(*pStr_Msg->Parameter == Pt_EventClearDI)
            {
                PF_BufferXToUlong32(pStr_Msg->Parameter + 1, &V_ulDataCode, C_DataCode_Length);
                if(V_ulDataCode == 0xFFFFFFFF)
                {
                    V_ucEventNo = C_AllEventNo;
                }
                else
                {
                    V_ucEventNo = InF_EventNumFind(V_ulDataCode);/*获取EventNo*/
                    if(V_ucEventNo > C_NeutralCurrentAbnormalEventNo)
                    {
                        return;
                    }
                }
                SF_EventClear_Judgemsg(V_ucEventNo);		/*清零函数*/
            }
        }
        else
        {
            if(pStr_Msg->SourceAddr == C_Msg_PowerNetworkMonitoring)		/*事件判断消息*/
            {
                SF_Write_EventMsgFuction(pStr_Msg);					/*事件写函数*/
            }
            else
            {
				return;
            }
        }
    }
}
/***********************************************************************************
函数原型：void SF_Sub_Sec(uchar8 V_ucSec1, uchar8 V_ucSec2, ulong32 *V_ulSubMins)
功能描述：计算相差秒数
输入参数：V_ucSec1 第一个秒数
          V_ucSec2 第二个秒数
输出参数：V_ulSubMins 相差秒数(Hex格式)
返回参数：
功能说明：
调用机制：
备    注：
***********************************************************************************/
void SF_Sub_Sec(uchar8 V_ucSec1, uchar8 V_ucSec2, ulong32 *V_ulSubMins)
{
	if(V_ucSec1 >= V_ucSec2)
	{
		*V_ulSubMins = V_ucSec1 - V_ucSec2;
	}
	else
	{
		*V_ulSubMins = V_ucSec1 + 60 - V_ucSec2;
	}
}

/***********************************************************************************
函数原型：ulong32    Inf_GetEventModeDI(uchar8 EventLine, uchar8 OADType)
功能描述：根据行号获取事件跟随上报模式字
输入参数：EventLine  行号
          OADType   获取的标志码是上报模式字还是上报类型，C_ReportMode 获取上报模式字；C_ReportType 获取上报类型


输出参数：ushort16 *V_Data_Length：返回数据长度
返回参数：C_OK、C_Error
功能说明：
调用机制：
备    注：
***********************************************************************************/
ulong32    Inf_GetEventModeDI(uchar8 EventLine, uchar8 OADType)
{
    uchar8 V_Nature;
    ulong32 V_EventModeDI;
    if(C_ReportMode == OADType)/*上报模式字，是否上报*/
    {
      if(((uchar8)(Str_698EventReport[EventLine].OIBANature)) == 0x02)
      {
          V_Nature = 0x08;
      }
      else
      {
          V_Nature = 0x0B;
      }
    }
    else                        /*上报类型，主动上报还是跟随上报*/
    {
      if(((uchar8)(Str_698EventReport[EventLine].OIBANature)) == 0x02)
      {
          V_Nature = 0x0B;
      }
      else
      {
          V_Nature = 0x0F;
      }
    }

    V_EventModeDI = (((((0x00003000)|(((uchar8)(Str_698EventReport[EventLine].OIBANature>>8))))<<8)|V_Nature)<<8);
    return V_EventModeDI;
}
/*******************************************************************************
函数原型：void Inf_EventReport_HP(uchar8 EventNo, uchar8 State)
功能描述：事件发生时写主动上报表格
输入参数：EventNo：事件号 State：C_Happen_EventMsg 事件发生动作；C_End_EventMsg 事件恢复动作
输出参数：
返回参数：
调用位置：
备    注：
*******************************************************************************/
void Inf_EventReport_HP(uchar8 EventNo, uchar8 State)
{
	uchar8	V_ucMode, V_uci, V_ucPowerOffReportType = 0;
	ulong32 V_ulEventOAD;
    uchar8 V_ucMeterReportParameter = C_MeterReportClose, V_ucReturn = C_Error;
    ushort16 V_usDataLen, V_usEncode;

    for(V_uci = 0 ; V_uci < Str_698EventReport_Len ; V_uci++ )		/*确定对应事件*/
    {
        if(EventNo == Str_698EventReport[V_uci].EventNo)
        {
            break;
        }
    }
    if(V_uci >= Str_698EventReport_Len)
    {
        return;
    }

    V_usDataLen = CLLossVolage_Report_Mode;

    V_ulEventOAD = Inf_GetEventModeDI(V_uci, C_ReportMode);
    if( C_OK != InF_GetData_ObjectManage(V_ulEventOAD, &V_ucMode, &V_usDataLen , &V_usEncode) )		/*读模式字*/
    {
        V_ucMode = C_ReportNull;								            /*默认不上报*/
    }

    if( ( ( State == C_Happen_EventReport ) && ( ( V_ucMode == C_ReportHP ) || ( V_ucMode == C_ReportAll ) ) )			/*模式字要上报*/
     || ( ( ( State == C_End_EventReport ) && ( ( EventNo < C_ProgramEventNo ) || ( EventNo == C_RelayFaEndEnEventNo ) ) ) &&( ( V_ucMode == C_ReportEed ) || ( V_ucMode == C_ReportAll ) ) ) )
    {
        if ( ( EventNo == C_PowerfailEventNo ) )   /*如果掉电主动上报是在低功耗下发生的，那么就不写上报，低功耗下已经写过了*/
        {
            V_usDataLen = CLReport_Type;
            V_ucReturn = InF_GetData_ObjectManage( CPowerOff_Report_Type, &V_ucPowerOffReportType, &V_usDataLen, &V_usEncode);
            if( ( V_ucReturn == C_OK ) && ( V_ucPowerOffReportType  == C_ActiveReportType ) )
            {
                if ( GStr_PowerfailStr.MeterState == C_Happen_EventMsg ) /*掉电在低功耗下发生*/
                {
                    return;
                }

                if( ( Inf_SatisfyPowerOnTime() != C_OK ) )          /*如果上电不足1小时或者电能表没有开启上报，不上报*/
                {
                    return;
                }
                if(State == C_Happen_EventReport)
                {
                    V_ucMeterReportParameter = Inf_MeterReportOpen(C_PowerOn, C_FirstNo);
                    if( ( InF_ValtageType() == C_OK) && ( V_ucMeterReportParameter == C_MeterReportOpen ) )      /*电压类型为直接接入式*/
                    {
                        Inf_Event_REPORTONumDeal(C_NewReportFlag);                                  /*掉电发生只写次数*/
                    }
                    return;
                }
            }
        }
        Inf_ReportList(C_ReportChannelAll, EventNo, C_NewReport);
    }
}

#if(_DEBUG_DB)
/***************************************************************************************************************
函数原型：uchar8 Inf_GetEventData(uchar8 *V_Data, ushort16 *V_Data_Length, ulong32 V_OADTab, uchar8 V_ucEvent_Flag)
功能描述：获取事件记录数据
输入参数：uchar8 *V_Data：数据所放缓存
          ushort16 *V_Data_Length：作为输入，缓存最大可用长度
          ulong32 V_OADTab：事件关联OAD序号表
          uchar8 V_Event_Flag：事件发生结束标志，0x01发生，0x02结束
输出参数：ushort16 *V_Data_Length：返回数据长度
返回参数：C_OK、C_Error
功能说明：
调用位置：
备    注：
****************************************************************************************************************/
uchar8 Inf_GetEventData(uchar8 *V_Data, ushort16 *V_Data_Length, ulong32 V_OADTab, uchar8 V_ucEvent_Flag)
{
    uchar8 V_ucTurn, V_uci= 0, V_uc645DINum;
	ushort16 V_usOADTab_Length;
	uchar8 P_Data_Length, DataLen;
	ushort16 V_usOAD[60], V_usOAD_Data, V_usOAD_State;
	ulong32 V_ul698OAD;
	ushort16 V_usOffset = 0;
	uchar8 V_ucType;
	ulong32 V_ulReadBuff[3] = {0};
	ushort16 V_usBuffMaxLen;
	uchar8 V_DataBuff[1024] = {0};
	uchar8 V_Relay_Data[13];
    ulong32 V32_i;
    uchar8	V_Buff_Zero[9] = {0};
    uchar8 V_ucLen_Temp;

	V_usOADTab_Length = 120;
	if(InF_ReadOADTab_Data(V_OADTab, (uchar8 *)&V_usOAD, &V_usOADTab_Length) != C_OK)
	{
		return C_Error;
	}

	V_usBuffMaxLen = *V_Data_Length;

	/*按照OAD的顺序组织数据*/
	for( V_ucTurn = 0; V_ucTurn < (V_usOADTab_Length / 2); V_ucTurn++)
	{
		V_usOAD_Data = V_usOAD[V_ucTurn] & 0x1FFF;
		V_usOAD_State = V_usOAD[V_ucTurn] >> 13;

		if(V_usOAD_Data > Str_FrozenConvert_Table_Len)
		{
			return C_Error;
		}

		V_ul698OAD = Str_FrozenConvert_Table[V_usOAD_Data].V_ulOAD;
		P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data].V_uc645Length;
		V_ucType = Str_FrozenConvert_Table[V_usOAD_Data].V_uc698Type;
		V_uc645DINum = Str_FrozenConvert_Table[V_usOAD_Data].V_uc698NextNum;

		if ( ( ( V_ucEvent_Flag & 0x0C ) == 0x04 )
          && ( ( V_usOAD_State == 0x0003 ) || ( V_usOAD_State == 0x0004 ) ) )
		{
			memset((V_DataBuff + V_usOffset), 0xAA, P_Data_Length);
			V_usOffset += P_Data_Length;
		}
		else if ( ( V_ul698OAD == CKey_State )
               && ( V_usOAD_State == 0x0001 )
			   && ( V_OADTab == CProgKD_OADTab ) )                 /*更新前密钥状态*/
        {
			if((V_ucEvent_Flag & 0x03) == 0x01)
			{
            	PF_CopyDataBytes(GV_KeyHState, (V_DataBuff + V_usOffset), CLKey_State_698);
			}
			V_usOffset += CLKey_State_698;
        }
		else if ( ( ( V_ul698OAD & 0xff000000 ) == 0x00000000 )    /*电能*/
			    || ( V_ul698OAD == 0x202D0200 )                     /*透支金额*/
                || ( ( V_ul698OAD & 0xFFFF0000 ) == 0x20310000 )    /*月度用电量*/
                || ( V_ul698OAD == 0x202C0201 )                     /*剩余金额*/
                || ( ( V_ul698OAD & 0xFFFF0000) == 0x20320000 ) )   /*阶梯结算用电量*/
		{
			if( V_ucType == C_array)    /*需要读多个645标识码*/
			{
				for( V_uci = 1; V_uci <= V_uc645DINum; V_uci++)
				{
					V_ul698OAD = Str_FrozenConvert_Table[V_usOAD_Data + V_uci].V_ulOAD;
					P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data + V_uci].V_uc645Length;
					if ( ( ( ( V_usOAD_State == 0x0001 ) || ( V_usOAD_State == 0x0002 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x01 ) )
                      || ( ( ( V_usOAD_State == 0x0003 ) || ( V_usOAD_State == 0x0004 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x02 ) ) )
					{
						if(InF_ReadEnergy_Protocol(V_ul698OAD, (V_DataBuff + V_usOffset), &P_Data_Length, C_Format_HEX) == C_OK)   /*读取电能*/
						{
							V_usOffset += P_Data_Length;
						}
						else
						{
							P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data + V_uci].V_uc645Length;
							memset((V_DataBuff + V_usOffset), 0xAA, P_Data_Length);
							V_usOffset += P_Data_Length;
						}
					}
					else
					{
						V_usOffset += P_Data_Length;
					}
				}
			}
			else
			{
				if ( ( ( ( V_usOAD_State == 0x0001 ) || ( V_usOAD_State == 0x0002 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x01 ) )
                  || ( ( ( V_usOAD_State == 0x0003 ) || ( V_usOAD_State == 0x0004 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x02 ) ) )
				{
					if(InF_ReadEnergy_Protocol(V_ul698OAD, (V_DataBuff + V_usOffset), &P_Data_Length, C_Format_HEX) == C_OK)     /*读取电能*/
					{
						V_usOffset += P_Data_Length;
					}
					else
					{
						P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data].V_uc645Length;
						memset((V_DataBuff + V_usOffset), 0xAA, P_Data_Length);
						V_usOffset += P_Data_Length;
					}
				}
				else
				{
					V_usOffset += P_Data_Length;
				}
			}
		}
		else if ( V_ul698OAD == 0x202C0200 )       /*钱包文件*/
		{
			if ( ( ( ( V_usOAD_State == 0x0001 ) || ( V_usOAD_State == 0x0002 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x01 ) )
              || ( ( ( V_usOAD_State == 0x0003 ) || ( V_usOAD_State == 0x0004 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x02 ) ) )
			{
				V_ul698OAD = Str_FrozenConvert_Table[V_usOAD_Data + 1].V_ulOAD;
				P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data + 1].V_uc645Length;
				if(InF_ReadEnergy_Protocol(V_ul698OAD, (V_DataBuff + V_usOffset), &P_Data_Length, C_Format_BCD) == C_OK)    /*读取电能*/
				{
					V_usOffset += P_Data_Length;
				}
				else
				{
					P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data + 1].V_uc645Length;
					memset((V_DataBuff + V_usOffset), 0xAA, P_Data_Length);
					V_usOffset += P_Data_Length;
				}
				V_ul698OAD = Str_FrozenConvert_Table[V_usOAD_Data + 2].V_ulOAD;
				P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data + 2].V_uc645Length;

				/*读ESAM中的购电次数*/
				PF_BufferXToUlong32(&V_DataBuff[V_usOffset], &V32_i, 4);

				if( InF_S_GetPPNum( &V32_i ) == C_OK )
				{
					PF_Ulong32ToBufferX(&V_DataBuff[V_usOffset], &V32_i, 4);
					V_usOffset += P_Data_Length;
				}
				else
				{
					memset( (V_DataBuff + V_usOffset), 0xAA, P_Data_Length );
					V_usOffset += P_Data_Length;
				}
			}
			else
			{
				V_usOffset += P_Data_Length;
			}
		}
		else if ( V_ul698OAD == 0x202C0202 )       /*购电次数*/
		{
            /*读ESAM中的购电次数*/
			if ( ( ( ( V_usOAD_State == 0x0001) || ( V_usOAD_State == 0x0002 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x01 ) )
              || ( ( ( V_usOAD_State == 0x0003) || ( V_usOAD_State == 0x0004 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x02 ) ) )
			{
				PF_BufferXToUlong32(&V_DataBuff[V_usOffset], &V32_i, 4);
				if(InF_S_GetPPNum( &V32_i ) == C_OK)
				{
					/*hex格式转换成BCD格式*/
					DataLen = 4;
					PF_HextoBCDBytes(&V32_i, &V_DataBuff[V_usOffset], &DataLen);
					V_usOffset += P_Data_Length;
				}
				else
				{
					memset((V_DataBuff + V_usOffset), 0xAA, P_Data_Length);
					V_usOffset += P_Data_Length;
				}
			}
			else
			{
				V_usOffset += P_Data_Length;
			}
		}
		else if ( ( ( V_ul698OAD & 0xff000000 ) == 0x10000000 )
                || ( ( V_ul698OAD & 0xff000000 ) == 0x11000000 ) )   /*需量*/
		{
			if( V_ucType == C_array)       /*需要读多个645标识码*/
			{
				for( V_uci = 1; V_uci <= V_uc645DINum; V_uci++)
				{
					V_ul698OAD = Str_FrozenConvert_Table[V_usOAD_Data + V_uci].V_ulOAD;
					P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data + V_uci].V_uc645Length;

					if ( ( ( ( V_usOAD_State == 0x0001 ) || ( V_usOAD_State == 0x0002 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x01 ) )
                      || ( ( ( V_usOAD_State == 0x0003 ) || ( V_usOAD_State == 0x0004 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x02 ) ) )
					{
						if ( InF_ReadDemand(V_ul698OAD, (V_DataBuff + V_usOffset), P_Data_Length) == C_OK )   /*读取需量数据*/
						{
							V_usOffset += P_Data_Length;
						}
				 	 	else
						{
							P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data+V_uci].V_uc645Length;
							memset((V_DataBuff + V_usOffset), 0xAA, P_Data_Length);
							V_usOffset += P_Data_Length;
						}
					}
					else
					{
						V_usOffset += P_Data_Length;
					}
				}
			}
			else
			{
				if ( ( ( ( V_usOAD_State == 0x0001 ) || ( V_usOAD_State == 0x0002 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x01 ) )
                  || ( ( ( V_usOAD_State == 0x0003 ) || ( V_usOAD_State == 0x0004 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x02 ) ) )
				{
					if (InF_ReadDemand(V_ul698OAD, (V_DataBuff + V_usOffset), P_Data_Length) == C_OK)     /*读取需量数据*/
					{
						V_usOffset += P_Data_Length;
					}
			 	 	else
					{
						P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data].V_uc645Length;
						memset((V_DataBuff + V_usOffset), 0xAA, P_Data_Length);
						V_usOffset += P_Data_Length;
					}
				}
				else
				{
					V_usOffset += P_Data_Length;
				}
			}
		}
		else if ( ( V_ul698OAD & 0xffff0000 ) == 0x20290000 )       /*安时数*/
		{
			switch(V_ucEvent_Flag & 0xF0)
			{
				case	0x10:
						V_ulReadBuff[0] = CLossAVol_FF_1;
						break;
				case	0x20:
						V_ulReadBuff[0] = CLossBVol_FF_1;
						break;
				case	0x30:
						V_ulReadBuff[0] = CLossCVol_FF_1;
						break;
				case	0x40:
						V_ulReadBuff[0] = CLowAVol_FF_1;
						break;
				case	0x50:
						V_ulReadBuff[0] = CLowBVol_FF_1;
						break;
				case	0x60:
						V_ulReadBuff[0] = CLowCVol_FF_1;
						break;
				case	0x70:
						V_ulReadBuff[0] = COverAVol_FF_1;
						break;
				case	0x80:
						V_ulReadBuff[0] = COverBVol_FF_1;
						break;
				case	0x90:
						V_ulReadBuff[0] = COverCVol_FF_1;
						break;
				case	0xA0:
						V_ulReadBuff[0] = CBreakAVol_FF_1;
						break;
				case	0xB0:
						V_ulReadBuff[0] = CBreakBVol_FF_1;
						break;
				case	0xC0:
						V_ulReadBuff[0] = CBreakCVol_FF_1;
						break;
				default:
						break;
			}
			if(V_ucType == C_array)     /*需要读多个645标识码*/
			{
				for( V_uci = 1; V_uci <= V_uc645DINum; V_uci++)
				{
					V_ul698OAD = Str_FrozenConvert_Table[V_usOAD_Data+V_uci].V_ulOAD;
					P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data+V_uci].V_uc645Length;

					if ( ( ( ( V_usOAD_State == 0x0001 ) || ( V_usOAD_State == 0x0002 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x01 ) )
                      || ( ( ( V_usOAD_State == 0x0003 ) || ( V_usOAD_State == 0x0004 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x02 ) ) )
					{
						V_ulReadBuff[1] = V_ul698OAD;
						V_ulReadBuff[1] |= (ulong32)(V_usOAD_State << 13);
						V_ulReadBuff[2] = 0xFFFFFFFF;

						if( Inf_ReadEventRenew(V_ulReadBuff, (V_DataBuff + V_usOffset), &P_Data_Length) == C_OK )    /*读取数据*/
						{
							V_usOffset += P_Data_Length;
						}
						else
						{
							P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data+V_uci].V_uc645Length;
							memset((V_DataBuff + V_usOffset), 0xAA, P_Data_Length);
							V_usOffset += P_Data_Length;
						}
					}
					else
					{
						V_usOffset += P_Data_Length;
					}
				}
			}
			else
			{
				if ( ( ( ( V_usOAD_State == 0x0001 ) || ( V_usOAD_State == 0x0002 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x01 ) )
                  || ( ( ( V_usOAD_State == 0x0003 ) || ( V_usOAD_State == 0x0004 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x02 ) ) )
				{
					V_ulReadBuff[1] = V_ul698OAD;
					V_ulReadBuff[1] |= (ulong32)(V_usOAD_State << 13);
					V_ulReadBuff[2] = 0xFFFFFFFF;

					if(Inf_ReadEventRenew(V_ulReadBuff, V_DataBuff+V_usOffset, &P_Data_Length) == C_OK)     /*读取数据*/
					{
						V_usOffset += P_Data_Length;
					}
					else
					{
						P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data].V_uc645Length;
						memset((V_DataBuff + V_usOffset), 0xAA, P_Data_Length);
						V_usOffset += P_Data_Length;
					}
				}
				else
				{
					V_usOffset += P_Data_Length;
				}
			}
		}
		else if ( ( V_ul698OAD & 0xffff0000 ) == 0x20260000 )       /*电压不平衡*/
		{
			if((V_ucEvent_Flag & 0xF0) == 0xD0)
			{
				V_ulReadBuff[0] = CNoBalVol_FF_1;
			}
			if ( ( ( ( V_usOAD_State == 0x0001 ) || ( V_usOAD_State == 0x0002 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x01 ) )
              || ( ( ( V_usOAD_State == 0x0003 ) || ( V_usOAD_State == 0x0004 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x02 ) ) )
			{
				V_ulReadBuff[1] = V_ul698OAD;
				V_ulReadBuff[1] |= (ulong32)(V_usOAD_State << 13);
				V_ulReadBuff[2] = 0xFFFFFFFF;

				if(Inf_ReadEventRenew(V_ulReadBuff, (V_DataBuff + V_usOffset), &P_Data_Length) == C_OK)   /*读取数据*/
				{
					V_usOffset += P_Data_Length;
				}
				else
				{
					P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data].V_uc645Length;
					memset((V_DataBuff + V_usOffset), 0xAA, P_Data_Length);
					V_usOffset += P_Data_Length;
				}
			}
			else
			{
				V_usOffset += P_Data_Length;
			}
		}
		else if ( ( V_ul698OAD & 0xffff0000) == 0x20270000 )        /*电流不平衡*/
		{
			if((V_ucEvent_Flag & 0xF0) == 0xE0)
			{
				V_ulReadBuff[0] = CNoBalCurr_FF_1;
			}
			else if((V_ucEvent_Flag & 0xF0) == 0xF0)
			{
				V_ulReadBuff[0] = CSevNoBalCurr_FF_1;
			}
			if ( ( ( ( V_usOAD_State == 0x0001 ) || ( V_usOAD_State == 0x0002 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x01 ) )
              || ( ( ( V_usOAD_State == 0x0003 ) || ( V_usOAD_State == 0x0004 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x02 ) ) )
			{
				V_ulReadBuff[1] = V_ul698OAD;
				V_ulReadBuff[1] |= (ulong32)(V_usOAD_State << 13);
				V_ulReadBuff[2] = 0xFFFFFFFF;

				if(Inf_ReadEventRenew(V_ulReadBuff, V_DataBuff+V_usOffset, &P_Data_Length) == C_OK)     /*读取数据*/
				{
					V_usOffset += P_Data_Length;
				}
				else
				{
					P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data].V_uc645Length;
					memset((V_DataBuff + V_usOffset), 0xAA, P_Data_Length);
					V_usOffset += P_Data_Length;
				}
			}
			else
			{
				V_usOffset += P_Data_Length;
			}
		}
		else if ( ( V_ul698OAD == CFirst_TZone_Data )
                || ( V_ul698OAD == CSec_TZone_Data )
				|| ( V_ul698OAD == CCurrent_Ladder_Table )
                || ( V_ul698OAD == CBackUp_Ladder_Table ) )
		{
			if ( ( ( ( V_usOAD_State == 0x0001 ) || ( V_usOAD_State == 0x0002 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x01 ) )
              || ( ( ( V_usOAD_State == 0x0003 ) || ( V_usOAD_State == 0x0004 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x02 ) ) )
			{
				if(InF_Read_Data(V_ul698OAD, (V_DataBuff + V_usOffset), &P_Data_Length) == C_OK)
				{
					V_usOffset += P_Data_Length;
				}
				else
				{
					P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data].V_uc645Length;
					memset((V_DataBuff + V_usOffset), 0xAA, P_Data_Length);
					V_usOffset += P_Data_Length;
				}
			}
			else
			{
				V_usOffset += P_Data_Length;
			}
		}
		else if ( ( V_ul698OAD == CVolA_Per_Pass_0_Freeze )
                || ( V_ul698OAD == CVolA_Per_Pass_0 )
                || ( V_ul698OAD == CVolB_Per_Pass_0_Freeze )
                || ( V_ul698OAD == CVolB_Per_Pass_0 )		   /*电压合格率和结算日分项特殊处理*/
			    || ( V_ul698OAD == CVolC_Per_Pass_0_Freeze )
                || ( V_ul698OAD == CVolC_Per_Pass_0 )
                || ( V_ul698OAD == CSettle_Day1 )
                || ( V_ul698OAD == CSettle_Day2 )
                || ( V_ul698OAD == CSettle_Day3 ) )
		{
			if ( ( ( ( V_usOAD_State == 0x0001 ) || ( V_usOAD_State == 0x0002 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x01 ) )
              || ( ( ( V_usOAD_State == 0x0003 ) || ( V_usOAD_State == 0x0004 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x02 ) ) )
			{
				if(InF_Read_Data(V_ul698OAD, (V_DataBuff + V_usOffset), &P_Data_Length) == C_OK)
				{
					V_usOffset += P_Data_Length;
				}
				else
				{
					P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data].V_uc645Length;
					memset((V_DataBuff + V_usOffset), 0xAA, P_Data_Length);
					V_usOffset += P_Data_Length;
				}
			}
			else
			{
				V_usOffset += P_Data_Length;
			}
		}
		else if ( V_ul698OAD == C_RelayFa_State )                   /*负荷开关状态*/
		{
			if ( ( ( ( V_usOAD_State == 0x0001 ) || ( V_usOAD_State == 0x0002 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x01 ) )
              || ( ( ( V_usOAD_State == 0x0003 ) || ( V_usOAD_State == 0x0004 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x02 ) ) )
			{
				Inf_Get_ApplianceF205(V_ul698OAD, V_Relay_Data, &P_Data_Length);

                memcpy((V_DataBuff + V_usOffset), &V_Relay_Data[C_RelayDescrip_Offset], CLRelayDescrip);
                V_usOffset += CLRelayDescrip;

				V_DataBuff[V_usOffset] = V_Relay_Data[C_RelayCurrentState_Offset];
				V_usOffset += CLRelayCurrentState;

				V_DataBuff[V_usOffset] = V_Relay_Data[C_RelaySwitchNature_Offset];
				V_usOffset += CLRelaySwitchNature;

				V_DataBuff[V_usOffset] = V_Relay_Data[C_RelayWiringState_Offset];
				V_usOffset += CLRelayWiringState;
			}
			else
			{
				V_usOffset += P_Data_Length;
			}
		}
		else if ( ( V_ul698OAD == CPhaseFF_Curr )
		       && ( V_OADTab == CAll_Loss_Vol_OADTab )
			   && ( V_usOAD_State == 0x0001 )
			   && ( ( V_ucEvent_Flag & 0x03 ) == 0x01 ) )
		{
			if(PF_Campare_Data(GStr_TotalvoltageloseStr.NoVoltageCurrent, V_Buff_Zero, CLPhaseFF_Curr) != C_Equal)
			{
				PF_CopyDataBytes(GStr_TotalvoltageloseStr.NoVoltageCurrent, (V_DataBuff + V_usOffset), CLPhaseFF_Curr);
				V_usOffset += CLPhaseFF_Curr;
			}
			else
			{
				for( V_uci = 1; V_uci <= V_uc645DINum; V_uci++)
				{
					V_ul698OAD = Str_FrozenConvert_Table[V_usOAD_Data + V_uci].V_ulOAD;
					P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data + V_uci].V_uc645Length;
					if( InF_Read_Data(V_ul698OAD, (V_DataBuff + V_usOffset), &P_Data_Length) == C_OK )
					{
						V_usOffset += P_Data_Length;
					}
					else
					{
						P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data + V_uci].V_uc645Length;
						memset((V_DataBuff + V_usOffset), 0xAA, P_Data_Length);
						V_usOffset += P_Data_Length;
					}
				}
			}
		}
		else
		{
			if ( ( V_ucType == C_array ) || ( ( V_ucType == C_structure ) && ( V_uc645DINum != 1 ) ) )    /*需要读多个(电压合格率和结算日分项前面已特殊处理)*/
			{
				for( V_uci = 1; V_uci <= V_uc645DINum; V_uci++)
				{
					V_ul698OAD = Str_FrozenConvert_Table[V_usOAD_Data + V_uci].V_ulOAD;
					P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data + V_uci].V_uc645Length;

					if ( ( ( ( V_usOAD_State == 0x0001 ) || ( V_usOAD_State == 0x0002 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x01 ) )
                      || ( ( ( V_usOAD_State == 0x0003 ) || ( V_usOAD_State == 0x0004 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x02 ) ) )
					{
						if((V_ul698OAD & 0xff000000) == 0x00000000)	  /*电能*/
						{
							if(InF_ReadEnergy_Protocol(V_ul698OAD, (V_DataBuff + V_usOffset), &P_Data_Length, C_Format_HEX) == C_OK)    /*读取电能*/
							{
								V_usOffset += P_Data_Length;
							}
							else
							{
								P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data+V_uci].V_uc645Length;
								memset((V_DataBuff + V_usOffset), 0xAA, P_Data_Length);
								V_usOffset += P_Data_Length;
							}
						}
						else
						{
							if(InF_Read_Data(V_ul698OAD, (V_DataBuff + V_usOffset), &P_Data_Length) == C_OK)
							{
								V_usOffset += P_Data_Length;
							}
							else
							{
								P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data+V_uci].V_uc645Length;
                                if(V_ul698OAD == 0x20010204)
                                {
                                	P_Data_Length = 3;
                                }
								memset((V_DataBuff + V_usOffset), 0xAA, P_Data_Length);
								V_usOffset += P_Data_Length;
							}
						}
					}
					else
					{
						V_usOffset += P_Data_Length;
					}
				}
			}
			else
			{
				if ( ( ( ( V_usOAD_State == 0x0001 ) || ( V_usOAD_State == 0x0002 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x01 ) )
                  || ( ( ( V_usOAD_State == 0x0003 ) || ( V_usOAD_State == 0x0004 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x02 ) ) )
				{
                    if ( ( ( ( V_ul698OAD & 0xFFFFFF00 ) == CSec_TZone_Data ) && ( V_ul698OAD != CSec_TZone_Data ) )
                      || ( ( ( V_ul698OAD & 0xFFFFFF00 ) == CFirst_TZone_Data ) && ( V_ul698OAD != CFirst_TZone_Data ) ) )
                    {
                        V_ucLen_Temp = CLFirst_TZone_Data;
                        P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data].V_uc645Length;

                        if( InF_Read_Data( ( V_ul698OAD & 0xFFFFFF00 ), (V_DataBuff + V_usOffset), &V_ucLen_Temp) == C_OK )
                        {
                            V_DataBuff[V_usOffset] = V_DataBuff[V_usOffset + ( ((uchar8)(V_ul698OAD)) - 1) * 3];
                            V_DataBuff[V_usOffset + 1] = V_DataBuff[V_usOffset+( ((uchar8)(V_ul698OAD)) - 1 ) * 3 + 1];
                            V_DataBuff[V_usOffset + 2] = V_DataBuff[V_usOffset+( ((uchar8)(V_ul698OAD)) - 1 ) * 3 + 2];
                        }
                        else
                        {
							memset((V_DataBuff + V_usOffset), 0xAA, P_Data_Length);
							V_usOffset += P_Data_Length;
                        }
                        V_usOffset += P_Data_Length;
                    }
                    else
                    {
                        if(InF_Read_Data(V_ul698OAD, (V_DataBuff + V_usOffset), &P_Data_Length) == C_OK)
                        {
                            V_usOffset += P_Data_Length;
                        }
                        else
                        {
                            P_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data].V_uc645Length;
    					    memset( (V_DataBuff + V_usOffset), 0xAA, P_Data_Length );
							V_usOffset += P_Data_Length;
                        }
                    }
				}
				else
				{
					V_usOffset += P_Data_Length;
				}
			}
		}
		if( (V_usOffset > V_usBuffMaxLen) || (V_usOffset > (1024 - 40) ) )	/*最大长度不能超过输入Buff长度和自身Buff长度*/
		{
			return	C_DataLenError;
		}
	}

	PF_CopyDataBytes_698(V_DataBuff, V_Data, V_usOffset);
	*V_Data_Length = V_usOffset;

	return C_OK;
}
#endif
/***********************************************************************************
函数原型：uchar8 Inf_ReadEventCurrentData_(ulong32 V_Data_Id, uchar8 *P_Data, uchar8 *P_Data_Length, V_Flag)
功能描述：通信读取事件的的当前值
输入参数：
           V_Data_Id
           *P_Data                      所读数据指针
           *P_Data_Length               缓冲区P_Data最大长度
           V_Flag:V_Dgree:0x01;V_Time:0x02   读次数和时间的判断
输出参数： *P_Data                      读出数据；
           *P_Data_Length               读数据的实际长度
返回参数：  C_IDError:不支持读取的数据标识，C_DataLenError数据长度错, C_OK:正确执行
            InF_GetData_ObjectManage()所能返回的任何值
功能说明：
调用机制：通信调用
备    注：*P_Data_Length必须大于等于所取值长度，不然返回错误；  兼容645增加
***********************************************************************************/
uchar8 Inf_ReadEventCurrentData_JudgeDgreeOrTime(ulong32 V_ulData_Id, uchar8 *pV_ucData, uchar8 *pV_ucData_Length, uchar8 V_ucFlag)
{
	uchar8 V_ucReturn, V_uci;
    ulong32 V_ulData = 0, V_ulOAD[2];
    ushort16 V_usLen, V_usEncode;

    V_usLen = *pV_ucData_Length;

	switch(V_ucFlag)
	{
        case C_Degree:
            for(V_uci = 0;V_uci < CurrentDataReadTable_Len;V_uci ++)
            {
                if(V_ulData_Id == CurrentDataReadTable[V_uci].Degree)
                {
                    V_ucReturn = InF_GetData_ObjectManage(CurrentDataReadTable[V_uci].Degree, pV_ucData, &V_usLen, &V_usEncode);

                    *pV_ucData_Length = V_usLen;

                    if(V_ucReturn == C_OK)
                    {
                        *pV_ucData_Length -= 1;/*645次数为少1字节*/
                    }
                    else
                    {
                        ;
                    }
                    break;
                }
            }
            if(V_uci >= CurrentDataReadTable_Len)
            {
                V_ucReturn = C_IDError;
            }
            break;

        case C_Time:
            for(V_uci=0;V_uci<CurrentDataReadTable_Len;V_uci++)
            {
                if(V_ulData_Id == CurrentDataReadTable[V_uci].AddTime)
                {
                    V_ulOAD[0] = CurrentDataReadTable[V_uci].AddTime;
                    V_ulOAD[1] = 0xFFFFFFFF;

                    V_ucReturn = Inf_ReadEventRenew(V_ulOAD, pV_ucData, pV_ucData_Length);
                    if(V_ucReturn == C_OK)
                    {
                        PF_BufferXToUlong32(pV_ucData, &V_ulData, *pV_ucData_Length);
                        V_ulData = V_ulData/60;/*存储数据为s（hex 4字节）转化为分（BCD，3字节）*/
                        if(V_ulData>0xF423F)
                        {
                            V_ulData = 0xF423F;
                        }
                        PF_HextoBCDBytes(&V_ulData, pV_ucData, pV_ucData_Length);
                        *pV_ucData_Length -= 1;
                    }
                    else
                    {
                        *pV_ucData_Length = 3;
                        memset(pV_ucData, 0x00, 3);
                    }
                    break;
                }
            }
            if(V_uci >= CurrentDataReadTable_Len)
            {
                V_ucReturn = C_IDError;
            }
            break;
        default:
            V_ucReturn = C_IDError;
        break;
	}
	return V_ucReturn;
}
/***********************************************************************************
函数原型：uchar8 Inf_ReadEventCurrentData_Com645(ulong32 V_Data_Id, uchar8 *P_Data, uchar8 *P_Data_Length)
功能描述：通信读取事件的的当前值
输入参数：
           V_Data_Id
           *P_Data                      所读数据指针
           *P_Data_Length               缓冲区P_Data最大长度
           V_Flag                       判断是哪类事件的处理
输出参数： *P_Data                      读出数据；
           *P_Data_Length               读数据的实际长度
返回参数：  C_IDError:不支持读取的数据标识，C_DataLenError数据长度错, C_OK:正确执行
            InF_GetData_ObjectManage()所能返回的任何值
功能说明：
调用机制：通信调用
备    注：*P_Data_Length必须大于等于所取值长度，不然返回错误；  兼容645增加
***********************************************************************************/
const	Str_EventTable_645ChangeTo698	TB_Str_EventTable_645ChangeTo698[] =
{
//  DI                                  OAD                 DILen
  {C_LossVol_Tol_Dgree_645,             CLoss_Vol_Degree,    (CLLoss_Vol_Degree-1)},
  {C_LossVol_Tol_Time_645,              CLoss_Vol_Time,      (CLLoss_Vol_Time-1)},
  {C_LossVol_Recent_HappenTime_645,     CLoss_Vol_Hp,        (CLLoss_Vol_Hp-1)},
  {C_LossVol_Recent_EndTime_645,        CLoss_Vol_End,       (CLLoss_Vol_End-1)},
};
#define TB_Str_EventTable_645ChangeTo698Len  (sizeof(TB_Str_EventTable_645ChangeTo698)/sizeof(Str_EventTable_645ChangeTo698))
uchar8 Inf_ReadEventCurrentData_Com645(ulong32 V_Data_Id, uchar8 *P_Data, uchar8 *P_Data_Length, uchar8 V_Flag)
{
	uchar8	V_ucLen, V_uci;
	uchar8  V_ucReturn, V_ucDataBuffer[CLAll_Loss_Vol_Current];
	ulong32 V_DataTemp[2];
	ulong32	V_Event_Num;
	V_ucLen = CLLoss_Vol_Hp;
    uchar8  V_TempBuff[CLAll_Loss_Vol_Current];

    if(V_Flag == C_Flag03)
    {
      if(V_Data_Id == 0x03050000)
      {
        V_DataTemp[0] = CAll_Loss_Vol_Current;
        V_DataTemp[1] = 0xFFFFFFFF;
        V_ucLen = CLAll_Loss_Vol_Current;
        V_ucReturn = Inf_ReadEventCurrentData(V_DataTemp[0], V_ucDataBuffer, &V_ucLen);
        if(V_ucReturn == C_OK)
		{
            PF_CopyDataBytes(V_ucDataBuffer, V_TempBuff, V_ucLen);
            //全失压次数
            PF_CopyDataBytes(&V_TempBuff[1], &V_ucDataBuffer[0], 3);//全失压次数
            //全失压累计时间
            PF_CopyDataBytes(&V_TempBuff[5], &V_ucDataBuffer[3], 4);//全失压次数
            PF_BufferXToUlong32(&V_ucDataBuffer[3], &V_Event_Num, 4);
            V_Event_Num = V_Event_Num/60;//存储数据为s（hex 4字节）转化为分（BCD，3字节）
            if(V_Event_Num>0xF423F)
            {
              V_Event_Num = 0xF423F;
            }
            V_ucLen = 3;//645累计时间3字节
            PF_HextoBCDBytes(&V_Event_Num, &V_ucDataBuffer[3], &V_ucLen);
            V_ucLen = 3+3;//645累计次数3字节+累计时间3字节
            PF_CopyDataBytes(V_ucDataBuffer, P_Data, V_ucLen);
		}

      }
      else
      {
        V_ucLen = CLLoss_Vol_Hp;
        V_ucReturn = Inf_ReadEventCurrentData_JudgeDgreeOrTime(V_Data_Id, P_Data, &V_ucLen, C_Degree);
      }
    }
    else if(V_Flag == C_Flag10)
    {
      if((V_Data_Id&0x00FF0000) != 0x00000000)  //DI2!=0
      {
        if((V_Data_Id&0x000000FF) == 0x00000001)///分相总次数
        {
          V_ucReturn = Inf_ReadEventCurrentData_JudgeDgreeOrTime(V_Data_Id, P_Data, &V_ucLen, C_Degree);
	    }
	    else if((V_Data_Id&0x000000FF) == 0x00000002)///分相累计时间
        {
         V_ucReturn = Inf_ReadEventCurrentData_JudgeDgreeOrTime(V_Data_Id, P_Data, &V_ucLen, C_Time);
        }
        else
        {
          V_ucReturn = C_IDError;
        }
      }
      else  //DI2=0
      {
        for(V_uci=0;V_uci<TB_Str_EventTable_645ChangeTo698Len;V_uci++)
        {
          if(V_Data_Id == TB_Str_EventTable_645ChangeTo698[V_uci].DI)
          {
            V_Data_Id = TB_Str_EventTable_645ChangeTo698[V_uci].OAD;
            break;
          }
        }
        if(V_uci<TB_Str_EventTable_645ChangeTo698Len)
        {
          V_DataTemp[0]=V_Data_Id;
          V_DataTemp[1]=0xFFFFFFFF;
          V_ucReturn = Inf_ReadEventRenew(V_DataTemp, V_ucDataBuffer, &V_ucLen);
          if(V_ucReturn==C_OK)
          {
            if(SF_JudgeAllAA(V_ucDataBuffer, V_ucLen) != C_OK)
            {
              if(V_Data_Id==CLoss_Vol_Time)
              {
				PF_BufferXToUlong32(V_ucDataBuffer, &V_Event_Num, V_ucLen);
                V_Event_Num = V_Event_Num/60;//存储数据为s（hex 4字节）转化为分（BCD，3字节）
                if(V_Event_Num>0xF423F)
                {
                  V_Event_Num = 0xF423F;
                }
                PF_HextoBCDBytes(&V_Event_Num, V_ucDataBuffer, &V_ucLen);

              }
            }
            else
            {
              memset(V_ucDataBuffer, 0x00, V_ucLen);
            }
            V_ucLen = TB_Str_EventTable_645ChangeTo698[V_uci].DILenth;
          }
          else
          {
              V_ucLen = TB_Str_EventTable_645ChangeTo698[V_uci].DILenth;
              memset(V_ucDataBuffer, 0x00, V_ucLen);
          }
          PF_CopyDataBytes(V_ucDataBuffer, P_Data, V_ucLen);

        }
        else
        {
          V_ucReturn = C_IDError;
        }
      }
  }
    else
    {
      if(((V_Data_Id&0x000000FF) == 0x00000001)||(CTrend_Rev_Degree == V_Data_Id))
      {
        if(CTrend_Rev_Degree == V_Data_Id)
        {
           V_Data_Id = CPowerT_Rev_Degree;
        }
        V_ucReturn = Inf_ReadEventCurrentData_JudgeDgreeOrTime(V_Data_Id, P_Data, &V_ucLen, C_Degree);
	  }
	  else if((V_Data_Id&0x000000FF) == 0x00000002)
      {
        V_ucReturn = Inf_ReadEventCurrentData_JudgeDgreeOrTime(V_Data_Id, P_Data, &V_ucLen, C_Time);
      }
      else
      {
        V_ucReturn = C_IDError;
      }
    }
   *P_Data_Length =  V_ucLen;
  return V_ucReturn;

}
/***********************************************************************************
函数原型：uchar8 Inf_ReadEventCurrentData(ulong32 V_ulData_Id, uchar8 *pV_ucData, uchar8 *pV_ucData_Length)
功能描述：通信读取事件的的当前值
输入参数：
           V_ulData_Id
           *pV_ucData                      所读数据指针
           *pV_ucData_Length               缓冲区P_Data最大长度
输出参数： *pV_ucData                      读出数据；
           *pV_ucData_Length               读数据的实际长度
返回参数：  C_IDError:不支持读取的数据标识，C_DataLenError数据长度错, C_OK:正确执行
            InF_GetData_ObjectManage()所能返回的任何值
功能说明：
调用机制：通信调用
备    注：*P_Data_Length必须大于等于所取值长度，不然返回错误；
***********************************************************************************/
uchar8 Inf_ReadEventCurrentData(ulong32 V_ulData_Id, uchar8 *pV_ucData, uchar8 *pV_ucData_Length)
{
	uchar8	V_uci, V_ucj;
	uchar8	V_ucReturn, V_ucOffset;
	ushort16 V_usDatalength, V_usEncode;
	uchar8	V_ucData[20] = {0};
	uchar8	V_ucDataLen;
	ulong32	V_ulReadOAD[3];
	uchar8  V_ucFlag = 0;
	ulong32 V_ulEventAttri[5] = {0x00000001, 0x00000601, 0x00000701, 0x00000801, 0x00000901};

	for(V_uci = 0;V_uci < CurrentDataReadTable_Len;V_uci ++)
	{
		if(V_ulData_Id == CurrentDataReadTable[V_uci].EventOAD)
		{
            V_ucFlag = C_Type1;
			break;
		}
	}
    if(V_uci >= CurrentDataReadTable_Len)
    {
        for(V_uci = 0;V_uci < CurrentDataReadTable_Len;V_uci ++)
        {
            if( ((ushort16)V_ulData_Id == CurrentDataReadTable[V_uci].EventTimeStatus)
            	&&((V_ulData_Id&0xFFFF0000) == (CurrentDataReadTable[V_uci].EventOAD&0xFFFF0000)) )
            {
                V_ucFlag = C_Type2;
                break;
            }
        }
    }
    if(V_uci >= CurrentDataReadTable_Len)
    {
        return C_IDError;
    }
	V_ucOffset = 0;
	if(V_ucFlag == C_Type1)
	{
		if(CurrentDataReadTable[V_uci].Source != C_SourceNon)
		{
			V_ulReadOAD[0] = (V_ulData_Id & 0xFFFF0000) | 0x00000201;
			V_ulReadOAD[1] = CEventHPSource;
			V_ulReadOAD[2] = 0xFFFFFFFF;
			V_usDatalength = 20;

			V_ucReturn = SF_ReadLastEvt(V_ulReadOAD, V_ucData, &V_usDatalength, (uchar8)V_ulReadOAD[0]);
			if(V_ucReturn==C_OK)
			{
				V_ucOffset += (uchar8)V_usDatalength;
			}
			else if(C_NoData == V_ucReturn)
			{
				V_ucData[0] = 0;
				V_ucOffset += 1;
				V_ucReturn = C_OK;
			}
			else
			{
				return(V_ucReturn);
			}
		}
		V_usDatalength = 20 - V_ucOffset;
		V_ucReturn = InF_GetData_ObjectManage(CurrentDataReadTable[V_uci].Degree, V_ucData + V_ucOffset, &V_usDatalength, &V_usEncode);
		if(V_ucReturn == C_OK)
		{
			V_ucOffset += (uchar8)V_usDatalength;
		}
		else
		{
			return(V_ucReturn);
		}

		if(CurrentDataReadTable[V_uci].AddTime == C_NULL)
		{
			V_ucDataLen = 4;
			for(V_ucj = 0;V_ucj < V_ucDataLen;V_ucj ++)
			{
				*(V_ucData + V_ucOffset + V_ucj) = 0x00;
			}
			V_ucOffset += V_ucDataLen;
		}
		else
		{
			V_ulReadOAD[0] = CurrentDataReadTable[V_uci].AddTime;
			V_ulReadOAD[1] = 0xFFFFFFFF;
			V_ucDataLen = 20 - V_ucOffset;
			V_ucReturn = Inf_ReadEventRenew(V_ulReadOAD, V_ucData + V_ucOffset, &V_ucDataLen);
			if(V_ucReturn == C_OK)
			{
				V_ucOffset += V_ucDataLen;
			}
			else
			{
				return(V_ucReturn);
			}
		}
	}
	else if((V_ucFlag == C_Type2))
	{
		if(CurrentDataReadTable[V_uci].Source != C_SourceNon)
		{
			V_ulReadOAD[0] = (V_ulData_Id & 0xFFFF0000) | 0x00000201;
			V_ulReadOAD[1] = CEventHPSource;
			V_ulReadOAD[2] = 0xFFFFFFFF;
			V_usDatalength = 20;

			V_ucReturn = SF_ReadLastEvt(V_ulReadOAD, V_ucData, &V_usDatalength, (uchar8)V_ulReadOAD[0]);
			if(V_ucReturn == C_NoData)
			{
				V_ucData[0] = 0;
				V_usDatalength = 1;
				V_ucReturn = C_OK;
			}
			if(V_ucReturn == C_OK)
			{
				V_ucOffset += (uchar8)V_usDatalength;
			}
			else
			{
				return(V_ucReturn);
			}
		}
		if(CurrentDataReadTable[V_uci].Source != C_SourceNon)
		{
			V_ulReadOAD[0] = (V_ulData_Id & 0xFFFF0000) | 0x00000201;
		}
		else
		{
			V_ulReadOAD[0] = (V_ulData_Id & 0xFFFF0000) | V_ulEventAttri[(uchar8)V_ulData_Id];
		}
		V_ulReadOAD[1] = CEventHPTime;
		V_ulReadOAD[2] = 0xFFFFFFFF;
		V_usDatalength = 20;

		V_ucReturn = SF_ReadLastEvt(V_ulReadOAD, V_ucData+ V_ucOffset, &V_usDatalength, (uchar8)V_ulReadOAD[0]);

		if(V_ucReturn == C_NoData)
		{
			V_usDatalength = C_EventTimeLength;

			memset(V_ucData + V_ucOffset, 0xAA, C_EventTimeLength);
			V_ucReturn = C_OK;
		}
		if(V_ucReturn==C_OK)
		{
			V_ucOffset += (uchar8)V_usDatalength;
		}
		else
		{
			return(V_ucReturn);
		}
		if(CurrentDataReadTable[V_uci].Source != C_SourceNon)
		{
			V_ulReadOAD[0] = (V_ulData_Id & 0xFFFF0000) | 0x00000201;
		}
		else
		{
			V_ulReadOAD[0] = (V_ulData_Id & 0xFFFF0000) |V_ulEventAttri[(uchar8)V_ulData_Id];
		}
		V_ulReadOAD[1] = CEventEndTime;
		V_ulReadOAD[2] = 0xFFFFFFFF;
		V_usDatalength = 20;

		if(SF_Judge_EventIntegrity(CurrentDataReadTable[V_uci].EventNo)==C_Happen_EventState)		/*如果历史状态是有发生无恢复*/
		{
			V_ulReadOAD[0] += 1;
		}
		V_ucReturn = SF_ReadLastEvt(V_ulReadOAD, V_ucData+ V_ucOffset, &V_usDatalength, (uchar8)V_ulReadOAD[0]);

		if(V_ucReturn==C_NoData)
		{
			V_usDatalength = C_EventTimeLength;

			memset(V_ucData + V_ucOffset, 0xAA, C_EventTimeLength);
			V_ucReturn = C_OK;
		}
		if(V_ucReturn==C_OK)
		{
			V_ucOffset += (uchar8)V_usDatalength;
		}
		else
		{
			return(V_ucReturn);
		}
	}
	if(V_ucOffset > *pV_ucData_Length)
	{
		return	C_DataLenError;
	}

	PF_CopyDataBytes(V_ucData, pV_ucData, V_ucOffset);
	*pV_ucData_Length = V_ucOffset;

	return(V_ucReturn);
}

#if (_DEBUG_DB)
/**********************************************************************************************************
函数原型：uchar8 Inf_ReadEventLast_H(ulong32 V_Data_Id, uchar8 *P_Data, uchar8 *P_Data_Length)
功能描述：通信读取上一次事件
输入参数：  *V_Data_Id需要读取的OAD，V_Data_Id[1]为0xFFFFFFFF整条读取；V_Data_Id[1]不为0xFFFFFFFF为列选读取
           *P_Data 所读数据指针
           *P_Data_Length 缓冲区P_Data最大长度
输出参数： *P_Data 读出数据；
           *P_Data_Length 读数据的实际长度
返回参数：  C_IDError:不支持读取的数据标识，C_DataLenError数据长度错, C_OK:正确执行
          InF_Read_Data()所能返回的任何值
调用位置：通信调用
备    注：*P_Data_Length必须大于等于所取值长度，不然返回错误；
***************************************************************************************************************/
uchar8 Inf_ReadEventLast_H(ulong32 *V_Data_OAD, uchar8 *P_Data, ushort16 *P_Data_Length, uchar8 V_timeFlash, uchar8 *pV_ucHappeningFlag)
{
	uchar8 V_ucTurn, V_uci, V_ucj, V_ucFixTime = 0, V_ucNextSign = 0;
	ushort16 V_usOADTab_Length, V_usDataLength;
	uchar8 V_Data_Length, V_ucReturn, V_ucOADFlag;
	ushort16 V_usOAD[C_EventMAXRelatedOAD], V_usOAD_Data, V_usOAD_State;
	ushort16 V_usOffset = 0;
	uchar8 i;
	ulong32 V_ulReadBuff[3] = {0};
	ushort16 V_usBuffMaxLen;
	uchar8 V_DataBuff[C_EventMAXLen] = {0};
	ushort16 V_usDataoffset = 0;
    uchar8 V_ucSpecicalDataLen = 0;
    uchar8 V_uck;
    uchar8 V_ucRateNum;

    Struct_FrozenConvert_Type Str_Encode;
    Struct_FrozenConvert_Type Str_EncodeNext;

	*pV_ucHappeningFlag = C_End_EventState;			/*默认不发生*/
	for(V_uci = 0; V_uci < EventMappingTable_Len; V_uci++)
	{
		if(EventMappingTable[V_uci].WriteOAD == V_Data_OAD[0])
		{
			break;
		}
	}
	if(V_uci >= EventMappingTable_Len)
	{
		return C_OtherErr;
	}
	V_usDataLength = C_EventMAXLen;
	V_ucReturn = InF_ReadEventData(V_Data_OAD, &V_ucFixTime, V_DataBuff, &V_ucNextSign, &V_usDataLength, V_timeFlash);
	if(V_ucReturn != C_OK)
	{
		return V_ucReturn;
	}

    V_usOADTab_Length = C_EventMAXRelatedOADLen;
	if(InF_ReadOADTab_Data(EventMappingTable[V_uci].OADTab, (uchar8 *)&V_usOAD, &V_usOADTab_Length) != C_OK)
	{
		return C_Error;
	}

    /*这几个事件一般没有关联列表*/
	if ( ( ( V_Data_OAD[0] == CEven_Clear_Note_1 )
        || ( V_Data_OAD[0] == CProgram_Note_1 )
        || ( V_Data_OAD[0] == CProgPT_Note_1 )
        || ( V_Data_OAD[0] == CProgHol_Note_1 )
        || ( V_Data_OAD[0] == CAbnorC_Note_1)
        || ( V_Data_OAD[0] == CReturn_M_Note_1 ) )
       && ( V_usOADTab_Length == 0 ) )
	{
		PF_CopyDataBytes_698(V_DataBuff, P_Data, V_usDataLength);
		*P_Data_Length = V_usDataLength;
		return C_OK;
	}

/************************判定事件记录当前发生状态***************************/
	if( SF_Judge_EventIntegrity(EventMappingTable[V_uci].EventNo) == C_Happen_EventState )
	{
		*pV_ucHappeningFlag = C_Happen_EventState;			/*正在发生*/
	}

	V_usBuffMaxLen = *P_Data_Length;
	if( V_Data_OAD[1] == 0xFFFFFFFF )
	{

        V_usOffset += (CLEventDegree + CLEventHappenTime + CLEventEndTime);		/*事件序号、发生时间、结束时间偏移*/
        V_usDataoffset += (CLEventDegree + CLEventHappenTime + CLEventEndTime);

        if( (*pV_ucHappeningFlag) == C_Happen_EventState )
        {
            memset((V_DataBuff + CLEventDegree + CLEventHappenTime), 0xAA, C_EventTimeLength);
        }

        if(EventMappingTable[V_uci].SourceFlag == C_SourceExist)
        {
            V_usOffset += CLEventSource;	 /*事件发生源偏移*/
            V_usDataoffset += CLEventSource;
        }

        if ( ( V_Data_OAD[0] == CPos_Ac_De_Over_Note_1 )
          || ( V_Data_OAD[0] == CRev_Ac_De_Over_Note_1 )
          || ( V_Data_OAD[0] == CQua1_Re_De_Over_Note_1 )
          || ( V_Data_OAD[0] == CQua2_Re_De_Over_Note_1 )
          || ( V_Data_OAD[0] == CQua3_Re_De_Over_Note_1 )
          || ( V_Data_OAD[0] == CQua4_Re_De_Over_Note_1 ) )
        {
            if( (*pV_ucHappeningFlag) == C_Happen_EventState )		/*如果历史状态是有发生无恢复*/
            {
                switch(EventMappingTable[V_uci].EventNo)
                {
                    case	C_OverForwardActiveEventNo:
                            PF_CopyDataBytes(GStr_OverForwardActiveStr.Renewal, (V_DataBuff + V_usOffset), C_OverDemandRenew_Length);
                            break;
                    case	C_OverReverseActiveEventNo:
                            PF_CopyDataBytes(GStr_OverReverseActiveStr.Renewal, (V_DataBuff + V_usOffset), C_OverDemandRenew_Length);
                            break;
                    case	C_1OverIdleDemandEventNo:
                            PF_CopyDataBytes(GStr_Over1IdleDemandStr.Renewal, (V_DataBuff + V_usOffset), C_OverDemandRenew_Length);
                            break;
                    case	C_2OverIdleDemandEventNo:
                            PF_CopyDataBytes(GStr_Over2IdleDemandStr.Renewal, (V_DataBuff + V_usOffset), C_OverDemandRenew_Length);
                            break;
                    case	C_3OverIdleDemandEventNo:
                            PF_CopyDataBytes(GStr_Over3IdleDemandStr.Renewal, (V_DataBuff + V_usOffset), C_OverDemandRenew_Length);
                            break;
                    case	C_4OverIdleDemandEventNo:
                            PF_CopyDataBytes(GStr_Over4IdleDemandStr.Renewal, (V_DataBuff + V_usOffset), C_OverDemandRenew_Length);
                            break;
                    default:
                            break;
                }
            }
            V_usOffset += C_OverDemandRenew_Length;
            V_usDataoffset += C_OverDemandRenew_Length;
            PF_CopyDataBytes(V_DataBuff, P_Data, V_usDataoffset);
        }
        else
        {
            /*特殊事件记录单元数据长度偏移*/
            SF_Event_SpecificDataLenCal(V_Data_OAD[0], &V_ucSpecicalDataLen);
            V_usOffset += V_ucSpecicalDataLen;
            V_usDataoffset += V_ucSpecicalDataLen;
            PF_CopyDataBytes(V_DataBuff, P_Data, V_usDataoffset);
        }

		/*按照OAD的顺序组织数据*/
		for( V_ucTurn = 0; V_ucTurn < (V_usOADTab_Length / 2); V_ucTurn++)
		{
		    V_usOAD_Data = V_usOAD[V_ucTurn] & 0x1FFF;  /*关联属性列表中的行号*/
			V_usOAD_State = V_usOAD[V_ucTurn] >> 13;    /*事件的属性特征*/

			if(V_usOAD_Data >= Str_FrozenConvert_Table_Len)
			{
				return C_Error;
			}

			V_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data].V_uc645Length;
            Str_Encode = Str_FrozenConvert_Table[V_usOAD_Data];
			SF_FrozenDataFF_NextNum(&Str_Encode, V_usOAD_Data);

            if((SF_FrozenData_JudgeRateNum(V_usOAD_Data, Str_Encode.V_ulOAD)) == C_Error)	    /*费率数超，应答空，数据层返回数据0xBB*/
            {
                P_Data[V_usDataoffset] = C_NotSupportAOD_DataBB;
                V_usDataoffset += CL_NotSupportAOD_DataBB;
                V_usOffset += V_Data_Length;	/*全部块数据长度*/
            }
            else
            {
			    if(V_usOAD_State != 0x0003)       /*0x0003为事件结束前*/
			    {
				    if(V_usOAD_State == 0x0004)   /*0x0004为事件结束后*/
				    {
					    if( (*pV_ucHappeningFlag) == C_Happen_EventState)		/*如果历史状态是有发生无恢复*/
					    {
                            memset(&V_DataBuff[V_usOffset], 0xAA, V_Data_Length);
					    }
				    }
                    PF_CopyDataBytes_698(&V_DataBuff[V_usOffset], &P_Data[V_usDataoffset], Str_Encode.V_uc645Length);
                    V_usDataoffset += Str_Encode.V_uc645Length;       /*根据费率数的长度*/
                    V_usOffset += V_Data_Length;                      /*全部块数据长度*/
			    }
			    else
			    {
				    if(Str_Encode.V_uc698Type == C_array)             /*需要读多个645标识码*/
				    {
					    for(i = 1; i <= Str_Encode.V_uc698NextNum; i++)
					    {
                            Str_EncodeNext = Str_FrozenConvert_Table[V_usOAD_Data + i];
                            V_Data_Length = Str_EncodeNext.V_uc645Length;
			                SF_FrozenDataFF_NextNum(&Str_EncodeNext, (V_usOAD_Data + i));

						    V_ulReadBuff[0] = V_Data_OAD[0];
						    V_ulReadBuff[1] = Str_EncodeNext.V_ulOAD;
						    V_ulReadBuff[1] |= (ulong32)(V_usOAD_State << 13);
						    V_ulReadBuff[2] = 0xFFFFFFFF;
						    if((Inf_ReadEventRenew(V_ulReadBuff, V_DataBuff+V_usOffset, &V_Data_Length)) != C_OK)   /*读取数据*/
						    {
							    V_Data_Length = Str_EncodeNext.V_uc645Length;
                                memset((V_DataBuff + V_usOffset), 0xAA, V_Data_Length);
						    }   /*else 读数据成功，已读出数据*/
		                    PF_CopyDataBytes_698(&V_DataBuff[V_usOffset], &P_Data[V_usDataoffset], Str_EncodeNext.V_uc645Length);
                            V_usDataoffset += Str_EncodeNext.V_uc645Length;     /*根据费率数的长度*/
                            V_usOffset += V_Data_Length;                        /*全部块数据长度*/
					    }
				    }
				   else
				   {
					    V_ulReadBuff[0] = V_Data_OAD[0];
					    V_ulReadBuff[1] = Str_Encode.V_ulOAD;
					    V_ulReadBuff[1] |= (ulong32)(V_usOAD_State << 13);
					    V_ulReadBuff[2] = 0xFFFFFFFF;

					    if((Inf_ReadEventRenew(V_ulReadBuff, (V_DataBuff + V_usOffset), &V_Data_Length)) != C_OK)     /*读取数据*/
					    {
						    V_Data_Length = Str_FrozenConvert_Table[V_usOAD_Data].V_uc645Length;
                            memset((V_DataBuff + V_usOffset), 0xAA, V_Data_Length);
					    }   /*else读取正确，数据已读出*/

                        PF_CopyDataBytes_698(&V_DataBuff[V_usOffset], &P_Data[V_usDataoffset], Str_Encode.V_uc645Length);
                        V_usDataoffset += Str_Encode.V_uc645Length;         /*根据费率数的长度*/
                        V_usOffset += V_Data_Length;                        /*全部块数据长度*/
				   }
			   }
            }

			if((V_usDataoffset > V_usBuffMaxLen) || (V_usDataoffset > (1024 - 40)))	    /*最大长度不能超过输入Buff长度和自身Buff长度*/
			{
				return	C_DataLenError;
			}
		    *P_Data_Length = V_usDataoffset;
		}
    }
	else
	{
        V_ucj = 1;
		while(V_Data_OAD[V_ucj] != 0xFFFFFFFF)
		{
			V_ucOADFlag = 0;
			for(V_ucTurn = 0; V_ucTurn < (V_usOADTab_Length / 2); V_ucTurn++)
            {
				V_usOAD_Data = V_usOAD[V_ucTurn] & 0x1FFF;
				V_usOAD_State = V_usOAD[V_ucTurn] >> 13;
				if(V_usOAD_Data >= Str_FrozenConvert_Table_Len)
                {
					return C_Error;
                }

                Str_Encode = Str_FrozenConvert_Table[V_usOAD_Data];
			    SF_FrozenDataFF_NextNum(&Str_Encode, V_usOAD_Data);

				if(V_Data_OAD[V_ucj] == (Str_Encode.V_ulOAD | (ulong32)(V_usOAD_State << 13)))
				{
					if(V_usOAD_State != 0x0003)           /*0x0003为事件结束前*/
					{
						if(V_usOAD_State == 0x0004)       /*0x0004为事件结束后*/
						{
							if( (*pV_ucHappeningFlag) == C_Happen_EventState)		/*如果历史状态是有发生无恢复*/
							{
                                memset((V_DataBuff + V_usOffset), 0xAA, Str_Encode.V_uc645Length);
							}
						}
						V_usOffset += Str_Encode.V_uc645Length;
					}
					else
					{
						if(Str_Encode.V_uc698Type == C_array)   /*需要读多个标识码*/
						{
							for(i = 1; i <= Str_Encode.V_uc698NextNum; i++)
							{
                                Str_EncodeNext = Str_FrozenConvert_Table[V_usOAD_Data + i];
			                    SF_FrozenDataFF_NextNum(&Str_EncodeNext, (V_usOAD_Data + i));
                                V_Data_Length = Str_EncodeNext.V_uc645Length;

								V_ulReadBuff[0] = V_Data_OAD[0];
								V_ulReadBuff[1] = Str_EncodeNext.V_ulOAD;
								V_ulReadBuff[1] |= (ulong32)(V_usOAD_State << 13);
								V_ulReadBuff[2] = 0xFFFFFFFF;

								if(Inf_ReadEventRenew(V_ulReadBuff, (V_DataBuff + V_usOffset), &V_Data_Length) == C_OK)     /*读取数据*/
								{
									V_usOffset += V_Data_Length;
								}
								else
								{
                                    memset((V_DataBuff + V_usOffset), 0xAA, Str_EncodeNext.V_uc645Length);
								}

							}
						}
						else
						{
							V_ulReadBuff[0] = V_Data_OAD[0];
							V_ulReadBuff[1] = Str_Encode.V_ulOAD;
							V_ulReadBuff[1] |= (ulong32)(V_usOAD_State << 13);
							V_ulReadBuff[2] = 0xFFFFFFFF;

							if(Inf_ReadEventRenew(V_ulReadBuff, (V_DataBuff + V_usOffset), &Str_Encode.V_uc645Length) == C_OK)    /*读取数据*/
							{
								V_usOffset += Str_Encode.V_uc645Length;
							}
							else
							{
                                Str_Encode = Str_FrozenConvert_Table[V_usOAD_Data];
			                    SF_FrozenDataFF_NextNum(&Str_Encode, V_usOAD_Data);

                                memset((V_DataBuff + V_usOffset), 0xAA, Str_Encode.V_uc645Length);
							}
						}
					}
					V_ucOADFlag = 0x68;
					if((V_usOffset > V_usBuffMaxLen) || (V_usOffset > (1024 - 40)))	/*最大长度不能超过输入Buff长度和自身Buff长度*/
					{
						return	C_DataLenError;
					}
					break;
				}
                else
                {
                    if(C_array == Str_Encode.V_uc698Type)
                    {
                        V_ucRateNum = InF_RateNumChangeToHex();
                        for(V_uck = 0; V_uck < (V_ucRateNum + 1); V_uck++)
                        {
                            if ( ( Str_FrozenConvert_Table[V_usOAD_Data + V_uck + 1].V_ulOAD & 0xFFFFFFF0 )
                              == ( Str_FrozenConvert_Table[V_usOAD_Data + V_uck].V_ulOAD & 0xFFFFFFF0 ) )
                            {
                                if( V_Data_OAD[V_ucj] == (Str_FrozenConvert_Table[V_usOAD_Data + V_uck + 1].V_ulOAD | (ulong32)(V_usOAD_State << 13)))
                                {
                                    if(V_usOAD_State != 0x0003)           /*0x0003为事件结束前*/
                                    {
                                        if(V_usOAD_State == 0x0004)       /*0x0004为事件结束后*/
                                        {
                                            if( (*pV_ucHappeningFlag) == C_Happen_EventState)		/*如果历史状态是有发生无恢复*/
                                            {
                                                memset((V_DataBuff + V_usOffset), 0xAA, Str_FrozenConvert_Table[V_usOAD_Data + V_uck + 1].V_uc645Length);
											}
                                        }
                                        V_usOffset += Str_FrozenConvert_Table[V_usOAD_Data + V_uck + 1].V_uc645Length;
                                    }
                                    else
                                    {
                                        V_ulReadBuff[0] = V_Data_OAD[0];
                                        V_ulReadBuff[1] = Str_FrozenConvert_Table[V_usOAD_Data + V_uck + 1].V_ulOAD;
                                        V_ulReadBuff[1] |= (ulong32)(V_usOAD_State << 13);
                                        V_ulReadBuff[2] = 0xFFFFFFFF;

                                        if(Inf_ReadEventRenew(V_ulReadBuff, (V_DataBuff + V_usOffset), &Str_Encode.V_uc645Length) == C_OK)    /*读取数据*/
                                        {
                                            V_usOffset += Str_FrozenConvert_Table[V_usOAD_Data + V_uck + 1].V_uc645Length;
                                        }
                                        else
                                        {
                                            memset((V_DataBuff + V_usOffset), 0xAA, Str_FrozenConvert_Table[V_usOAD_Data + V_uck + 1].V_uc645Length);
                                        }
                                    }
                                    V_ucOADFlag = 0x68;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            if(V_Data_OAD[V_ucj] == CEventNum)
            {
                V_usOffset += CLEventNum;
                V_ucOADFlag = 0x68;
            }
            else if(V_Data_OAD[V_ucj] == CEventHPTime)
            {
                V_usOffset += CLEventHPTime;
                V_ucOADFlag = 0x68;
            }
            else if(V_Data_OAD[V_ucj] == CEventEndTime)
            {
                if( (*pV_ucHappeningFlag)==C_Happen_EventState)
                {
                    memset((V_DataBuff + V_usOffset), 0xAA, C_EventTimeLength);
                }
                V_usOffset += CLEventHPTime;
                V_ucOADFlag = 0x68;
            }
            else if((V_Data_OAD[V_ucj] == CEventHPSource) && (EventMappingTable[V_uci].SourceFlag == C_SourceExist))
            {
                V_ulReadBuff[0] = V_Data_OAD[0];
                V_ulReadBuff[1] = CEventHPSource;
                V_ulReadBuff[2] = 0xFFFFFFFF;
                V_usDataLength = 20;
                V_ucFixTime = 0;
                V_ucNextSign = 0;
                if(InF_ReadEventData(V_ulReadBuff, &V_ucFixTime, (V_DataBuff + V_usOffset), &V_ucNextSign, &V_usDataLength, V_timeFlash) == C_OK)
                {
                    V_usOffset += V_usDataLength;
                }
                else
                {
                    *(V_DataBuff + V_usOffset) = 0xAA;
                    V_usOffset += 1;
                }
                V_ucOADFlag = 0x68;
            }
            else if( V_Data_OAD[V_ucj] == C_OverDemandRenew_Demand )
            {
                if ( ( V_Data_OAD[0] == CPos_Ac_De_Over_Note_1 )
                  || ( V_Data_OAD[0] == CRev_Ac_De_Over_Note_1 )
                  || ( V_Data_OAD[0] == CQua1_Re_De_Over_Note_1 )
                  || ( V_Data_OAD[0] == CQua2_Re_De_Over_Note_1 )
                  || ( V_Data_OAD[0] == CQua3_Re_De_Over_Note_1 )
                  || ( V_Data_OAD[0] == CQua4_Re_De_Over_Note_1 ) )
                {
                    if( (*pV_ucHappeningFlag) == C_Happen_EventState )		/*如果历史状态是有发生无恢复*/
                    {
                        switch(EventMappingTable[V_uci].EventNo)
                        {
                            case	C_OverForwardActiveEventNo:
                                    PF_CopyDataBytes(GStr_OverForwardActiveStr.Renewal, (V_DataBuff + V_usOffset), CLOverDemandRenew_Demand);
                                    break;
                            case	C_OverReverseActiveEventNo:
                                    PF_CopyDataBytes(GStr_OverReverseActiveStr.Renewal, (V_DataBuff + V_usOffset), CLOverDemandRenew_Demand);
                                    break;
                            case	C_1OverIdleDemandEventNo:
                                    PF_CopyDataBytes(GStr_Over1IdleDemandStr.Renewal, (V_DataBuff + V_usOffset), CLOverDemandRenew_Demand);
                                    break;
                            case	C_2OverIdleDemandEventNo:
                                    PF_CopyDataBytes(GStr_Over2IdleDemandStr.Renewal, (V_DataBuff + V_usOffset), CLOverDemandRenew_Demand);
                                    break;
                            case	C_3OverIdleDemandEventNo:
                                    PF_CopyDataBytes(GStr_Over3IdleDemandStr.Renewal, (V_DataBuff + V_usOffset), CLOverDemandRenew_Demand);
                                    break;
                            case	C_4OverIdleDemandEventNo:
                                    PF_CopyDataBytes(GStr_Over4IdleDemandStr.Renewal, (V_DataBuff + V_usOffset), CLOverDemandRenew_Demand);
                                    break;
                            default:
                                    break;
                        }
                    }
                    V_usOffset += CLOverDemandRenew_Demand;
                    V_usDataoffset += CLOverDemandRenew_Demand;
                }
            }
            else if( V_Data_OAD[V_ucj] == C_OverDemandRenew_HapTime )
            {
                if ( ( V_Data_OAD[0] == CPos_Ac_De_Over_Note_1 )
                  || ( V_Data_OAD[0] == CRev_Ac_De_Over_Note_1 )
                  || ( V_Data_OAD[0] == CQua1_Re_De_Over_Note_1 )
                  || ( V_Data_OAD[0] == CQua2_Re_De_Over_Note_1 )
                  || ( V_Data_OAD[0] == CQua3_Re_De_Over_Note_1 )
                  || ( V_Data_OAD[0] == CQua4_Re_De_Over_Note_1 ) )
                {
                    if( (*pV_ucHappeningFlag) == C_Happen_EventState )		/*如果历史状态是有发生无恢复*/
                    {
                        switch(EventMappingTable[V_uci].EventNo)
                        {
                            case	C_OverForwardActiveEventNo:
                                    PF_CopyDataBytes(GStr_OverForwardActiveStr.RenewalTime, (V_DataBuff + V_usOffset), CLOverDemandRenew_HapTime);
                                    break;
                            case	C_OverReverseActiveEventNo:
                                    PF_CopyDataBytes(GStr_OverReverseActiveStr.RenewalTime, (V_DataBuff + V_usOffset), CLOverDemandRenew_HapTime);
                                    break;
                            case	C_1OverIdleDemandEventNo:
                                    PF_CopyDataBytes(GStr_Over1IdleDemandStr.RenewalTime, (V_DataBuff + V_usOffset), CLOverDemandRenew_HapTime);
                                    break;
                            case	C_2OverIdleDemandEventNo:
                                    PF_CopyDataBytes(GStr_Over2IdleDemandStr.RenewalTime, (V_DataBuff + V_usOffset), CLOverDemandRenew_HapTime);
                                    break;
                            case	C_3OverIdleDemandEventNo:
                                    PF_CopyDataBytes(GStr_Over3IdleDemandStr.RenewalTime, (V_DataBuff + V_usOffset), CLOverDemandRenew_HapTime);
                                    break;
                            case	C_4OverIdleDemandEventNo:
                                    PF_CopyDataBytes(GStr_Over4IdleDemandStr.RenewalTime, (V_DataBuff + V_usOffset), CLOverDemandRenew_HapTime);
                                    break;
                            default:
                                    break;
                        }
                    }
                    V_usOffset += CLOverDemandRenew_HapTime;
                    V_usDataoffset += CLOverDemandRenew_HapTime;
                }
            }
            else if(V_Data_OAD[V_ucj] == CProgOADGather)
            {
                V_usOffset += CLProgOADGather;
                V_ucOADFlag = 0x68;
            }

			if(V_ucOADFlag == 0x68)	/*已经查找到，查找下一个*/
			{
				V_ucj++;
				continue;
			}
			else
			{
				*(V_DataBuff + V_usOffset) = C_NotSupportAOD_DataBB;
				V_usOffset += 1;
				V_ucj++;
				if((V_usOffset > V_usBuffMaxLen) || (V_usOffset > (1024 - 40)))	    /*最大长度不能超过输入Buff长度和自身Buff长度*/
				{
                    return	C_DataLenError;
				}
			}
		}
		PF_CopyDataBytes_698(V_DataBuff, P_Data, V_usOffset);
		*P_Data_Length = V_usOffset;
	}
	return C_OK;
}
#endif

const Str_EvtFixRCSD_Type TB_FixRCSD[] = 
{
	{CAbnormalCard_CareNo,				CLAbnormalCard_CareNo},				/*异常插卡卡序列号*/
	{CAbnormalCard_ErrorStatus,			CLAbnormalCard_ErrorStatus},		/*异常插卡错误状态字*/
	{CAbnormalCard_OrderHead,			CLAbnormalCard_OrderHead},			/*异常插卡插卡操作命令头*/
	{CAbnormalCard_ErrorRespondStatus,	CLAbnormalCard_ErrorRespondStatus},	/*异常插卡插卡错误响应状态*/
	{CRWTimeTable_OAD,					CLProgOAD},							/*时段表编程OAD*/
	{CRWTimeTable_ForwardData,			CLFirst_TZone_1PT_Data},			/*时段表编程编程前数据*/
	{C_RWHoliday_OAD,					CLProgOAD},							/*节假日编程OAD*/
	{CRWHoliday_ForwardData,			CLHolidy_PT_Table1},				/*节假日编程前节假日数据*/
	{C_OverDemandRenew_Demand,			CLCurr_AcDemand},					/*需量超限发生期间最大需量*/
	{C_OverDemandRenew_HapTime,			CLDate_Time},						/*需量超限发生期间最大需量发生时间*/
	{CProgram_OADList,					(CLProgOAD + 1) * CProgOADNum},		/*编程事件记录编程列表*/
	{CEventClear_OADList,				CLProgOAD},							/*事件清零记录清零列表*/
	{CReturnMoney_Charge,				CLAlam1_Money},						/*退费事件记录固定列表中退费金额*/
};
#define C_TB_FixRCSD_Len	( sizeof(TB_FixRCSD) / sizeof(Str_EvtFixRCSD_Type) )
/**********************************************************************************************************
函数原型：SF_JudgeFixRCSD
功能描述：判断事件记录固定列表数据的合法性，并给出偏移和标志
输入参数：V_ulOAD:列选OAD；V_ucDataBuff:记录数据缓存；V_usOffset：当前列选OAD对应的偏移；V_ucOADFlag：是否能查到固定列表的标志，输入为0
输出参数：V_usOffset：当前列选OAD对应的偏移；V_ucOADFlag：是否能查到固定列表的标志，0x68能查到
返回参数：无
调用位置：事件模块读事件记录接口调用
备    注：
***************************************************************************************************************/
void SF_JudgeFixRCSD(ulong32 V_ulOAD, uchar8 *V_ucDataBuff, ushort16 *V_usOffset, uchar8 *V_ucOADFlag)
{
	uchar8 V_uci;
	
	if(V_ucDataBuff[*V_usOffset] == C_NotSupportAOD_DataBB)
	{/*数据层数据为BB，表示没有数据，直接返回*/
		return;
	}
	for(V_uci = 0;V_uci < C_TB_FixRCSD_Len;V_uci ++)
	{
		if(V_ulOAD == TB_FixRCSD[V_uci].V_ulOAD)/*查到表格后，赋值偏移和标志*/
		{
			*V_usOffset += TB_FixRCSD[V_uci].V_ucLen;
			
			*V_ucOADFlag = 0x68;

			break;
		}
	}
}

/**********************************************************************************************************
函数原型：uchar8 Inf_ReadEventLast_1(Str_Read_T *pStr_Read, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, Str_SuppInfo *pStr_SuppInfo)
功能描述：读取上一次事件记录数据
输入参数：pStr_Read为读取参数结构体
    pV_ucDataBuf为读取缓存地址
	*pV_usDataLen为读取缓存最大长度
	pV_ucSupplementaryInformation为辅助信息缓存地址
	*pV_usSIDataLen为辅助信息缓存最大长度
输出参数：*pV_ucDataBuf为读取数据
	*pV_usDataLen为读取数据实际长度
	pV_ucSupplementaryInformation为辅助信息数据
	*pV_usSIDataLen为辅助信息数据实际长度
返回参数：C_OK正确，其他返回具体错误
调用位置：事件模块读事件记录接口调用
备    注：*pV_usDataLen必须大于等于所取值长度，不然返回错误；
***************************************************************************************************************/
uchar8 Inf_ReadEventLast_1(Str_Read_T *pStr_Read, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, Str_SuppInfo *pStr_SuppInfo)
{
	uchar8 V_ucTurn, V_uci;
	ushort16 V_usOADTab_Length, V_usDataLength;
	uchar8 V_ucData_Length, V_ucReturn, V_ucOADFlag;
	ushort16 V_usOAD[C_EventMAXRelatedOAD], V_usOAD_Data, V_usOAD_State;
	ushort16 V_usOffset = 0;
	uchar8 i;
	ulong32 V_ulReadBuff[5] = {0};
	ushort16 V_usBuffMaxLen;
	uchar8 V_ucDataBuff[C_EventMAXLen] = {0};
	ushort16 V_usDataoffset = 0, V_usi, V_usNum = pStr_Read->V_usROAD_Num;
    uchar8 V_ucSpecicalDataLen = 0;
    uchar8 V_uck;
    uchar8 V_ucHappeningFlag;
    ulong32 *pV_ulData_OAD;
    Struct_FrozenConvert_Type Str_Encode;
    Struct_FrozenConvert_Type Str_EncodeNext;

    pV_ulData_OAD = pStr_Read->pV_ulROAD;/*获取OAD和关联列表缓存指针*/

	V_ucHappeningFlag = C_End_EventState;			/*默认不发生*/
	for(V_uci = 0; V_uci < EventMappingTable_Len; V_uci++)
	{
		if(EventMappingTable[V_uci].WriteOAD == pV_ulData_OAD[0])
		{
			break;
		}
	}
	if(V_uci >= EventMappingTable_Len)
	{
		return C_OtherErr;
	}
	V_usDataLength = C_EventMAXLen;
	V_ucReturn = InF_GetData_Record_DataBase(pStr_Read, V_ucDataBuff, &V_usDataLength, pStr_SuppInfo);
	if(V_ucReturn != C_OK)
	{
		return V_ucReturn;
	}

    V_usOADTab_Length = C_EventMAXRelatedOADLen;
	if(InF_ReadOADTab_Data(EventMappingTable[V_uci].OADTab, (uchar8 *)&V_usOAD, &V_usOADTab_Length) != C_OK)
	{
		return C_Error;
	}

    /*这几个事件一般没有关联列表*/
	if ( ( ( pV_ulData_OAD[0] == CEven_Clear_Note_1 )
        || ( pV_ulData_OAD[0] == CProgram_Note_1 )
        || ( pV_ulData_OAD[0] == CProgPT_Note_1 )
        || ( pV_ulData_OAD[0] == CProgHol_Note_1 )
        || ( pV_ulData_OAD[0] == CAbnorC_Note_1)
        || ( pV_ulData_OAD[0] == CReturn_M_Note_1 ) )
       && ( V_usOADTab_Length == 0 ) )
	{
		PF_CopyDataBytes_698(V_ucDataBuff, pV_ucDataBuf, V_usDataLength);
		*pV_usDataLen = V_usDataLength;
		return C_OK;
	}

/************************判定事件记录当前发生状态***************************/
	if( SF_Judge_EventIntegrity(EventMappingTable[V_uci].EventNo) == C_Happen_EventState )
	{
		V_ucHappeningFlag = C_Happen_EventState;			/*正在发生*/
		
		pStr_SuppInfo->V_ucLastFlag = C_Active_Happening;	/*如果是正在发生，赋值正在发生标志给通信，用于编码*/
	}

	V_usBuffMaxLen = *pV_usDataLen;
	if( pV_ulData_OAD[1] == 0xFFFFFFFF )
	{

        V_usOffset += (CLEventDegree + CLEventHappenTime + CLEventEndTime);		/*事件序号、发生时间、结束时间偏移*/
        V_usDataoffset += (CLEventDegree + CLEventHappenTime + CLEventEndTime);

        if( (V_ucHappeningFlag == C_Happen_EventState)
		   && (pStr_Read -> V_ucReadMode == C_ComMode) )/*通信读才赋值AA*/
        {
            memset((V_ucDataBuff + CLEventDegree + CLEventHappenTime), 0xAA, C_EventTimeLength);
        }

        if(EventMappingTable[V_uci].SourceFlag == C_SourceExist)
        {
            V_usOffset += CLEventSource;	 /*事件发生源偏移*/
            V_usDataoffset += CLEventSource;
        }
        V_usOffset +=  CLEventReport;/*新增上报状态*/
        V_usDataoffset +=  CLEventReport;

        if ( ( pV_ulData_OAD[0] == CPos_Ac_De_Over_Note_1 )
          || ( pV_ulData_OAD[0] == CRev_Ac_De_Over_Note_1 )
          || ( pV_ulData_OAD[0] == CQua1_Re_De_Over_Note_1 )
          || ( pV_ulData_OAD[0] == CQua2_Re_De_Over_Note_1 )
          || ( pV_ulData_OAD[0] == CQua3_Re_De_Over_Note_1 )
          || ( pV_ulData_OAD[0] == CQua4_Re_De_Over_Note_1 ) )
        {
            if( (V_ucHappeningFlag) == C_Happen_EventState )		/*如果历史状态是有发生无恢复*/
            {
                switch(EventMappingTable[V_uci].EventNo)
                {
                    case	C_OverForwardActiveEventNo:
                            PF_CopyDataBytes(GStr_OverForwardActiveStr.Renewal, (V_ucDataBuff + V_usOffset), C_OverDemandRenew_Length);
                            break;
                    case	C_OverReverseActiveEventNo:
                            PF_CopyDataBytes(GStr_OverReverseActiveStr.Renewal, (V_ucDataBuff + V_usOffset), C_OverDemandRenew_Length);
                            break;
                    case	C_1OverIdleDemandEventNo:
                            PF_CopyDataBytes(GStr_Over1IdleDemandStr.Renewal, (V_ucDataBuff + V_usOffset), C_OverDemandRenew_Length);
                            break;
                    case	C_2OverIdleDemandEventNo:
                            PF_CopyDataBytes(GStr_Over2IdleDemandStr.Renewal, (V_ucDataBuff + V_usOffset), C_OverDemandRenew_Length);
                            break;
                    case	C_3OverIdleDemandEventNo:
                            PF_CopyDataBytes(GStr_Over3IdleDemandStr.Renewal, (V_ucDataBuff + V_usOffset), C_OverDemandRenew_Length);
                            break;
                    case	C_4OverIdleDemandEventNo:
                            PF_CopyDataBytes(GStr_Over4IdleDemandStr.Renewal, (V_ucDataBuff + V_usOffset), C_OverDemandRenew_Length);
                            break;
                    default:
                            break;
                }
            }
            V_usOffset += C_OverDemandRenew_Length;
            V_usDataoffset += C_OverDemandRenew_Length;
            PF_CopyDataBytes(V_ucDataBuff, pV_ucDataBuf, V_usDataoffset);
        }
        else
        {
            /*特殊事件记录单元数据长度偏移*/
            SF_Event_SpecificDataLenCal(pV_ulData_OAD[0], &V_ucSpecicalDataLen);
            V_usOffset += V_ucSpecicalDataLen;
            V_usDataoffset += V_ucSpecicalDataLen;
            PF_CopyDataBytes(V_ucDataBuff, pV_ucDataBuf, V_usDataoffset);
        }

		/*按照OAD的顺序组织数据*/
		for( V_ucTurn = 0; V_ucTurn < (V_usOADTab_Length / 2); V_ucTurn++)
		{
		    V_usOAD_Data = V_usOAD[V_ucTurn] & 0x1FFF;  /*关联属性列表中的行号*/
			V_usOAD_State = V_usOAD[V_ucTurn] >> 13;    /*事件的属性特征*/

			if(V_usOAD_Data >= Str_FrozenConvert_Table_Len)
			{
				return C_Error;
			}

			V_ucData_Length = Str_FrozenConvert_Table[V_usOAD_Data].V_uc645Length;
            Str_Encode = Str_FrozenConvert_Table[V_usOAD_Data];
			SF_FrozenDataFF_NextNum(&Str_Encode, V_usOAD_Data);

            if((SF_FrozenData_JudgeRateNum(V_usOAD_Data, Str_Encode.V_ulOAD)) == C_Error)	    /*费率数超，应答空，数据层返回数据0xBB*/
            {
                pV_ucDataBuf[V_usDataoffset] = C_NotSupportAOD_DataBB;
                V_usDataoffset += CL_NotSupportAOD_DataBB;
                V_usOffset += V_ucData_Length;	/*全部块数据长度*/
            }
            else
            {
			    if(V_usOAD_State != 0x0003)       /*0x0003为事件结束前*/
			    {
				    if(V_usOAD_State == 0x0004)   /*0x0004为事件结束后*/
				    {
					    if( (V_ucHappeningFlag) == C_Happen_EventState)		/*如果历史状态是有发生无恢复*/
					    {
                            memset(&V_ucDataBuff[V_usOffset], 0xAA, V_ucData_Length);
					    }
				    }
                    PF_CopyDataBytes_698(&V_ucDataBuff[V_usOffset], &pV_ucDataBuf[V_usDataoffset], Str_Encode.V_uc645Length);
                    V_usDataoffset += Str_Encode.V_uc645Length;       /*根据费率数的长度*/
                    V_usOffset += V_ucData_Length;                      /*全部块数据长度*/
			    }
			    else
			    {
				    if(Str_Encode.V_uc698Type == C_array)             /*需要读多个645标识码*/
				    {
					    for(i = 1; i <= Str_Encode.V_uc698NextNum; i++)
					    {
                            Str_EncodeNext = Str_FrozenConvert_Table[V_usOAD_Data + i];
                            V_ucData_Length = Str_EncodeNext.V_uc645Length;
			                SF_FrozenDataFF_NextNum(&Str_EncodeNext, (V_usOAD_Data + i));

						    V_ulReadBuff[0] = pV_ulData_OAD[0];
						    V_ulReadBuff[1] = Str_EncodeNext.V_ulOAD;
						    V_ulReadBuff[1] |= (ulong32)(V_usOAD_State << 13);
						    V_ulReadBuff[2] = 0xFFFFFFFF;
						    if((Inf_ReadEventRenew(V_ulReadBuff, V_ucDataBuff+V_usOffset, &V_ucData_Length)) != C_OK)   /*读取数据*/
						    {
							    V_ucData_Length = Str_EncodeNext.V_uc645Length;
                                memset((V_ucDataBuff + V_usOffset), 0xAA, V_ucData_Length);
						    }   /*else 读数据成功，已读出数据*/
		                    PF_CopyDataBytes_698(&V_ucDataBuff[V_usOffset], &pV_ucDataBuf[V_usDataoffset], Str_EncodeNext.V_uc645Length);
                            V_usDataoffset += Str_EncodeNext.V_uc645Length;     /*根据费率数的长度*/
                            V_usOffset += V_ucData_Length;                        /*全部块数据长度*/
					    }
				    }
				   else
				   {
					    V_ulReadBuff[0] = pV_ulData_OAD[0];
					    V_ulReadBuff[1] = Str_Encode.V_ulOAD;
					    V_ulReadBuff[1] |= (ulong32)(V_usOAD_State << 13);
					    V_ulReadBuff[2] = 0xFFFFFFFF;

					    if((Inf_ReadEventRenew(V_ulReadBuff, (V_ucDataBuff + V_usOffset), &V_ucData_Length)) != C_OK)     /*读取数据*/
					    {
						    V_ucData_Length = Str_FrozenConvert_Table[V_usOAD_Data].V_uc645Length;
                            memset((V_ucDataBuff + V_usOffset), 0xAA, V_ucData_Length);
					    }   /*else读取正确，数据已读出*/

                        PF_CopyDataBytes_698(&V_ucDataBuff[V_usOffset], &pV_ucDataBuf[V_usDataoffset], Str_Encode.V_uc645Length);
                        V_usDataoffset += Str_Encode.V_uc645Length;         /*根据费率数的长度*/
                        V_usOffset += V_ucData_Length;                        /*全部块数据长度*/
				   }
			   }
            }

			if((V_usDataoffset > V_usBuffMaxLen) || (V_usDataoffset > (C_EventMAXLen - 40)))	    /*最大长度不能超过输入Buff长度和自身Buff长度*/
			{
				return	C_DataLenError;
			}
		}
		*pV_usDataLen = V_usDataoffset;/*长度赋值放在for循环外面，防止未设置关联列表时返回长度错误*/
    }
	else
	{
		V_usNum += 1;/*关联OAD的存储偏移从第2个开始，此处加1*/
		for(V_usi = 1;V_usi < V_usNum;V_usi ++)
		{
			if(pV_ulData_OAD[V_usi] == 0xFFFFFFFF)
			{
				break;
			}
			V_ucOADFlag = 0;
			for(V_ucTurn = 0; V_ucTurn < (V_usOADTab_Length / 2); V_ucTurn++)
            {
				V_usOAD_Data = V_usOAD[V_ucTurn] & 0x1FFF;
				V_usOAD_State = V_usOAD[V_ucTurn] >> 13;
				if(V_usOAD_Data >= Str_FrozenConvert_Table_Len)
                {
					return C_Error;
                }

                Str_Encode = Str_FrozenConvert_Table[V_usOAD_Data];
			    SF_FrozenDataFF_NextNum(&Str_Encode, V_usOAD_Data);

				if(pV_ulData_OAD[V_usi] == (Str_Encode.V_ulOAD | (ulong32)(V_usOAD_State << 13)))
				{
					if(V_usOAD_State != 0x0003)           /*0x0003为事件结束前*/
					{
						if(V_usOAD_State == 0x0004)       /*0x0004为事件结束后*/
						{
							if( (V_ucHappeningFlag) == C_Happen_EventState)		/*如果历史状态是有发生无恢复*/
							{
                                memset((V_ucDataBuff + V_usOffset), 0xAA, Str_Encode.V_uc645Length);
							}
						}
						V_usOffset += Str_Encode.V_uc645Length;
					}
					else
					{
						if(Str_Encode.V_uc698Type == C_array)   /*需要读多个标识码*/
						{
							for(i = 1; i <= Str_Encode.V_uc698NextNum; i++)
							{
                                Str_EncodeNext = Str_FrozenConvert_Table[V_usOAD_Data + i];
			                    SF_FrozenDataFF_NextNum(&Str_EncodeNext, (V_usOAD_Data + i));
                                V_ucData_Length = Str_EncodeNext.V_uc645Length;

								V_ulReadBuff[0] = pV_ulData_OAD[0];
								V_ulReadBuff[1] = Str_EncodeNext.V_ulOAD;
								V_ulReadBuff[1] |= (ulong32)(V_usOAD_State << 13);
								V_ulReadBuff[2] = 0xFFFFFFFF;

								if(Inf_ReadEventRenew(V_ulReadBuff, (V_ucDataBuff + V_usOffset), &V_ucData_Length) == C_OK)     /*读取数据*/
								{
									V_usOffset += V_ucData_Length;
								}
								else
								{
                                    memset((V_ucDataBuff + V_usOffset), 0xAA, Str_EncodeNext.V_uc645Length);
								}

							}
						}
						else
						{
							V_ulReadBuff[0] = pV_ulData_OAD[0];
							V_ulReadBuff[1] = Str_Encode.V_ulOAD;
							V_ulReadBuff[1] |= (ulong32)(V_usOAD_State << 13);
							V_ulReadBuff[2] = 0xFFFFFFFF;

							if(Inf_ReadEventRenew(V_ulReadBuff, (V_ucDataBuff + V_usOffset), &Str_Encode.V_uc645Length) == C_OK)    /*读取数据*/
							{
								V_usOffset += Str_Encode.V_uc645Length;
							}
							else
							{
                                Str_Encode = Str_FrozenConvert_Table[V_usOAD_Data];
			                    SF_FrozenDataFF_NextNum(&Str_Encode, V_usOAD_Data);

                                memset((V_ucDataBuff + V_usOffset), 0xAA, Str_Encode.V_uc645Length);
							}
						}
					}
					V_ucOADFlag = 0x68;
					if((V_usOffset > V_usBuffMaxLen) || (V_usOffset > (C_EventMAXLen - 40)))	/*最大长度不能超过输入Buff长度和自身Buff长度*/
					{
						return	C_DataLenError;
					}
					break;
				}
                else
                {
                    if(C_array == Str_Encode.V_uc698Type)
                    {
                        for(V_uck = 0; V_uck < 255; V_uck++)/*此处查询个数赋值最大255，实际肯定不会到，后续判断到标识码不匹配就退出*/
                        {
                            if ( ( Str_FrozenConvert_Table[V_usOAD_Data + V_uck + 1].V_ulOAD & 0xFFFFFFF0 )
                              == ( Str_FrozenConvert_Table[V_usOAD_Data + V_uck].V_ulOAD & 0xFFFFFFF0 ) )
                            {
                                if( SF_FrozenData_JudgeRateNum( V_usOAD_Data + V_uck + 1, pV_ulData_OAD[V_usi] ) == C_Error )
                                {/*若费率数超，则退出*/
                                    break;
                                }
                                if( pV_ulData_OAD[V_usi] == (Str_FrozenConvert_Table[V_usOAD_Data + V_uck + 1].V_ulOAD | (ulong32)(V_usOAD_State << 13)))
                                {
                                    if(V_usOAD_State != 0x0003)           /*0x0003为事件结束前*/
                                    {
                                        if(V_usOAD_State == 0x0004)       /*0x0004为事件结束后*/
                                        {
                                            if( (V_ucHappeningFlag) == C_Happen_EventState)		/*如果历史状态是有发生无恢复*/
                                            {
                                                memset((V_ucDataBuff + V_usOffset), 0xAA, Str_FrozenConvert_Table[V_usOAD_Data + V_uck + 1].V_uc645Length);
											}
                                        }
                                        V_usOffset += Str_FrozenConvert_Table[V_usOAD_Data + V_uck + 1].V_uc645Length;
                                    }
                                    else
                                    {
                                        V_ulReadBuff[0] = pV_ulData_OAD[0];
                                        V_ulReadBuff[1] = Str_FrozenConvert_Table[V_usOAD_Data + V_uck + 1].V_ulOAD;
                                        V_ulReadBuff[1] |= (ulong32)(V_usOAD_State << 13);
                                        V_ulReadBuff[2] = 0xFFFFFFFF;

                                        if(Inf_ReadEventRenew(V_ulReadBuff, (V_ucDataBuff + V_usOffset), &Str_Encode.V_uc645Length) == C_OK)    /*读取数据*/
                                        {
                                            V_usOffset += Str_FrozenConvert_Table[V_usOAD_Data + V_uck + 1].V_uc645Length;
                                        }
                                        else
                                        {
                                            memset((V_ucDataBuff + V_usOffset), 0xAA, Str_FrozenConvert_Table[V_usOAD_Data + V_uck + 1].V_uc645Length);
                                        }
                                    }
                                    V_ucOADFlag = 0x68;
                                    break;
                                }
                            }
                            else/*查询到的标识码已不是相同索引，则退出*/
                            {
                                break;
                            }
                        }
                    }
                }
            }
            if(pV_ulData_OAD[V_usi] == CEventNum)
            {
                V_usOffset += CLEventNum;
                V_ucOADFlag = 0x68;
            }
            else if(pV_ulData_OAD[V_usi] == CEventHPTime)
            {
                V_usOffset += CLEventHPTime;
                V_ucOADFlag = 0x68;
            }
            else if(pV_ulData_OAD[V_usi] == CEventEndTime)
            {
                if( (V_ucHappeningFlag == C_Happen_EventState)
				   && (pStr_Read -> V_ucReadMode == C_ComMode) )/*通信读才赋值AA*/
                {
                    memset((V_ucDataBuff + V_usOffset), 0xAA, C_EventTimeLength);
                }
                V_usOffset += CLEventHPTime;
                V_ucOADFlag = 0x68;
            }
            else if((pV_ulData_OAD[V_usi] == CEventHPSource) && (EventMappingTable[V_uci].SourceFlag == C_SourceExist))
            {
                V_ulReadBuff[0] = pV_ulData_OAD[0];
                V_ulReadBuff[1] = CEventHPSource;
                V_ulReadBuff[2] = 0xFFFFFFFF;

                V_usDataLength = 20;
                if(SF_ReadLastEvt(V_ulReadBuff, (V_ucDataBuff + V_usOffset), &V_usDataLength, (uchar8)V_ulReadBuff[0]) == C_OK)
                {
                    V_usOffset += V_usDataLength;
                }
                else
                {
                    *(V_ucDataBuff + V_usOffset) = 0xAA;
                    V_usOffset += 1;
                }
                V_ucOADFlag = 0x68;
            }
            else if( pV_ulData_OAD[V_usi] == C_OverDemandRenew_Demand )
            {
                if ( ( pV_ulData_OAD[0] == CPos_Ac_De_Over_Note_1 )
                  || ( pV_ulData_OAD[0] == CRev_Ac_De_Over_Note_1 )
                  || ( pV_ulData_OAD[0] == CQua1_Re_De_Over_Note_1 )
                  || ( pV_ulData_OAD[0] == CQua2_Re_De_Over_Note_1 )
                  || ( pV_ulData_OAD[0] == CQua3_Re_De_Over_Note_1 )
                  || ( pV_ulData_OAD[0] == CQua4_Re_De_Over_Note_1 ) )
                {
                    if( (V_ucHappeningFlag) == C_Happen_EventState )		/*如果历史状态是有发生无恢复*/
                    {
                        switch(EventMappingTable[V_uci].EventNo)
                        {
                            case	C_OverForwardActiveEventNo:
                                    PF_CopyDataBytes(GStr_OverForwardActiveStr.Renewal, (V_ucDataBuff + V_usOffset), CLOverDemandRenew_Demand);
                                    break;
                            case	C_OverReverseActiveEventNo:
                                    PF_CopyDataBytes(GStr_OverReverseActiveStr.Renewal, (V_ucDataBuff + V_usOffset), CLOverDemandRenew_Demand);
                                    break;
                            case	C_1OverIdleDemandEventNo:
                                    PF_CopyDataBytes(GStr_Over1IdleDemandStr.Renewal, (V_ucDataBuff + V_usOffset), CLOverDemandRenew_Demand);
                                    break;
                            case	C_2OverIdleDemandEventNo:
                                    PF_CopyDataBytes(GStr_Over2IdleDemandStr.Renewal, (V_ucDataBuff + V_usOffset), CLOverDemandRenew_Demand);
                                    break;
                            case	C_3OverIdleDemandEventNo:
                                    PF_CopyDataBytes(GStr_Over3IdleDemandStr.Renewal, (V_ucDataBuff + V_usOffset), CLOverDemandRenew_Demand);
                                    break;
                            case	C_4OverIdleDemandEventNo:
                                    PF_CopyDataBytes(GStr_Over4IdleDemandStr.Renewal, (V_ucDataBuff + V_usOffset), CLOverDemandRenew_Demand);
                                    break;
                            default:
                                    break;
                        }
                    }
                    V_usOffset += CLOverDemandRenew_Demand;
                    V_usDataoffset += CLOverDemandRenew_Demand;
					
					V_ucOADFlag = 0x68;
                }
            }
            else if( pV_ulData_OAD[V_usi] == C_OverDemandRenew_HapTime )
            {
                if ( ( pV_ulData_OAD[0] == CPos_Ac_De_Over_Note_1 )
                  || ( pV_ulData_OAD[0] == CRev_Ac_De_Over_Note_1 )
                  || ( pV_ulData_OAD[0] == CQua1_Re_De_Over_Note_1 )
                  || ( pV_ulData_OAD[0] == CQua2_Re_De_Over_Note_1 )
                  || ( pV_ulData_OAD[0] == CQua3_Re_De_Over_Note_1 )
                  || ( pV_ulData_OAD[0] == CQua4_Re_De_Over_Note_1 ) )
                {
                    if( (V_ucHappeningFlag) == C_Happen_EventState )		/*如果历史状态是有发生无恢复*/
                    {
                        switch(EventMappingTable[V_uci].EventNo)
                        {
                            case	C_OverForwardActiveEventNo:
                                    PF_CopyDataBytes(GStr_OverForwardActiveStr.RenewalTime, (V_ucDataBuff + V_usOffset), CLOverDemandRenew_HapTime);
                                    break;
                            case	C_OverReverseActiveEventNo:
                                    PF_CopyDataBytes(GStr_OverReverseActiveStr.RenewalTime, (V_ucDataBuff + V_usOffset), CLOverDemandRenew_HapTime);
                                    break;
                            case	C_1OverIdleDemandEventNo:
                                    PF_CopyDataBytes(GStr_Over1IdleDemandStr.RenewalTime, (V_ucDataBuff + V_usOffset), CLOverDemandRenew_HapTime);
                                    break;
                            case	C_2OverIdleDemandEventNo:
                                    PF_CopyDataBytes(GStr_Over2IdleDemandStr.RenewalTime, (V_ucDataBuff + V_usOffset), CLOverDemandRenew_HapTime);
                                    break;
                            case	C_3OverIdleDemandEventNo:
                                    PF_CopyDataBytes(GStr_Over3IdleDemandStr.RenewalTime, (V_ucDataBuff + V_usOffset), CLOverDemandRenew_HapTime);
                                    break;
                            case	C_4OverIdleDemandEventNo:
                                    PF_CopyDataBytes(GStr_Over4IdleDemandStr.RenewalTime, (V_ucDataBuff + V_usOffset), CLOverDemandRenew_HapTime);
                                    break;
                            default:
                                    break;
                        }
                    }
                    V_usOffset += CLOverDemandRenew_HapTime;
                    V_usDataoffset += CLOverDemandRenew_HapTime;
					
					V_ucOADFlag = 0x68;
                }
            }
			else
			{
				SF_JudgeFixRCSD(pV_ulData_OAD[V_usi], V_ucDataBuff, &V_usOffset, &V_ucOADFlag);/*固定列表合法性判断*/
			}
			if(V_ucOADFlag != 0x68)	/*没查到，赋值BB*/
			{
				*(V_ucDataBuff + V_usOffset) = C_NotSupportAOD_DataBB;
				V_usOffset += 1;
				
				if((V_usOffset > V_usBuffMaxLen) || (V_usOffset > (C_EventMAXLen - 40)))	    /*最大长度不能超过输入Buff长度和自身Buff长度*/
				{
                    return	C_DataLenError;
				}
			}
		}
		PF_CopyDataBytes_698(V_ucDataBuff, pV_ucDataBuf, V_usOffset);
		*pV_usDataLen = V_usOffset;
	}
	return C_OK;
}
#if (_DEBUG_DB)
/***************************************************************************************************************************************************************
函数原型：uchar8 Inf_ReadEventLast_N(ulong32 * P_Data_Id_OAD, uchar8 * P_FixTime, uchar8 * P_Data, uchar8 * V_ucNextSign, ushort16 * P_Data_Length, uchar8 V_timeFlash)
功能描述：通信读取上n次事件（除上1次，上1次有函数单独处理）
输入参数：*P_Data_Id_OAD：第一个OAD表示读取冻结类型，
                         例如300D0201，表示读取全失压事件，最低1字节00表示表示按时间读取，
														 非00表示读取上XX次记录，此时* P_FixTime、V_BlockNum无效.
				         后续OAD顺序为关联属性对应OAD顺序，当查找OAD为FFFFFFFF则表示，该条记录读取记录OAD结束(包含固定列表)。
         *P_FixTime：给定时间记录块，12个字节。
                     按时间区间抄读，前6个字节表示起始时间，后6个字节表示结束时间，时间格式ssmmhhDDMMYY
    				 按固定时间抄读时，前6个字节与后6个字节相同。当时间区间读需后续帧时，前6个字节为下一块记录时间。
        *V_NextSign：作为输入参数后续帧标识，Bit5--Bit4表示是否为后续帧抄读。当为1时表示为后续帧抄读，非1时表示是首次抄读。
        * V_Length：读数据缓存区最大长度；
	     V_timeFlash:表示根据时间抄读事件记录时，是根据发生时间、还是结束时间。AA表示结束时间，其他数据为发生时间
输出参数：
        *P_FixTime：作为输出参数时，当有后续帧时，返回下一个记录块?锹际奔?前6个字节)。
        *V_Length：所读数据实际长度；
        *P_Data：读数据存放缓存；
        *V_NextSign：作为输出参数后续帧标识，
                     Bit5--Bit4表示是否为后续帧抄读。当为1时表示为后续帧抄读，非1时表示是首次抄读。
    			    Bit0-Bit3表示抄读返回数据包含的事件记录条数(最多10条).
                   Bit7-Bit6:表示按固定时间或区间抄读数据，返回数据是否包含最近1条记录
    						1：表示返回数据包含最近1条记录，0：表示返回数据不包含最近1条记录。部分事件记录最近1次需读事件记录接口函数
    					   (如安时数，发生期间数据层数据为0)。正常固定时间或区间抄读，最近1条记录数据为返回数据的最后1条，时间从前往后查。
返回参数：C_OK、C_IICError、C_SPIError、C_DataLenError、C_IDError、C_NoData、C_Error
功能说明：读取上2-10/1000条的数据处理，用于处理电能类、需量类、费率电价等与费率数相关的电能数据，按费率数应答，以及关联列表中超出费率数的电能应答为空。
调用机制：通信调用
备    注：只有按条数应答的数据需要这里处理，实际按时间区间抄读的数据在InF_ReadEventData函数中处理
******************************************************************************************************************************************************************/
uchar8 Inf_ReadEventLast_N(ulong32 * P_Data_Id_OAD, uchar8 * P_FixTime, uchar8 * P_Data, uchar8 * V_ucNextSign, ushort16 * P_Data_Length, uchar8 V_timeFlash)
{
	uchar8		V_ucTurn, V_uci, V_ucj, V_uck, V_ucData_Length, V_ucReturn;
    uchar8      V_ucNextDataNumTol, V_ucReadEventDegree, V_ucNextDataLenTol;
    uchar8      V_DataBuff[C_EventMAXLen]={0};
	ushort16	V_usOADTab_Length, V_usOAD_Data, V_usDataLength;
	ushort16	V_usOAD[C_EventMAXRelatedOAD];
	ushort16	V_usOffset=0, V_usDataoffset = 0;;
	Struct_FrozenConvert_Type Str_Encode;
    Struct_FrozenConvert_Type Str_EncodeNext;
    ulong32     V_ulOADoffset;
    uchar8 V_ucSpecicalDataLen = 0;

    V_ulOADoffset = P_Data_Id_OAD[0] & 0x000000FF;
	for(V_uci = 0; V_uci<EventMappingTable_Len; V_uci++)
	{
		if(((EventMappingTable[V_uci].WriteOAD &0xFFFFFF00) | V_ulOADoffset) == P_Data_Id_OAD[0])
		{
			break;
	    }
	}
	if(V_uci>=EventMappingTable_Len)
	{
		 return C_OtherErr;
    }

	V_ucReturn = InF_ReadEventData(P_Data_Id_OAD, P_FixTime, V_DataBuff, V_ucNextSign, P_Data_Length, V_timeFlash);
	if(V_ucReturn != C_OK)
	{
		return V_ucReturn;
	}
    V_ucReadEventDegree = (*V_ucNextSign) & 0x0F;//bit0-bit3，表示读取的条数

	V_usOADTab_Length = C_EventMAXRelatedOADLen;
	if(InF_ReadOADTab_Data(EventMappingTable[V_uci].OADTab, (uchar8 *)&V_usOAD, &V_usOADTab_Length)!=C_OK)
	{
		return C_Error;
	}
	if(P_Data_Id_OAD[1] == 0xFFFFFFFF)
	{
        for( V_uck = 0; V_uck < V_ucReadEventDegree; V_uck++)
        {
		    PF_CopyDataBytes_698( &V_DataBuff[V_usOffset], &P_Data[V_usDataoffset], (CLEventDegree + CLEventHappenTime + CLEventEndTime) );
		    V_usOffset += CLEventDegree + CLEventHappenTime + CLEventEndTime;		/*事件序号、发生时间、结束时间偏移*/
            V_usDataoffset += CLEventDegree + CLEventHappenTime + CLEventEndTime;	/*事件序号、发生时间、结束时间偏移*/
            if(EventMappingTable[V_uci].SourceFlag == C_SourceExist)
		    {
                P_Data[V_usDataoffset] = V_DataBuff[V_usOffset];
			    V_usOffset += CLEventSource;	/*事件发生源偏移*/
                V_usDataoffset += CLEventSource;
		    }
            /*特殊事件记录单元数据长度偏移*/
            SF_Event_SpecificDataLenCal(P_Data_Id_OAD[0], &V_ucSpecicalDataLen);
            PF_CopyDataBytes(&V_DataBuff[V_usOffset], &P_Data[V_usDataoffset], V_ucSpecicalDataLen);
            V_usOffset += V_ucSpecicalDataLen;
            V_usDataoffset += V_ucSpecicalDataLen;

			/*按照OAD的顺序组织数据*/
			for( V_ucTurn = 0; V_ucTurn < (V_usOADTab_Length/2); V_ucTurn++ )
			{
			    V_usOAD_Data = V_usOAD[V_ucTurn] & 0x1FFF; //关联属性列表中的行号

				V_ucNextDataNumTol = Str_FrozenConvert_Table[V_usOAD_Data].V_uc698NextNum;
	            V_ucNextDataLenTol = Str_FrozenConvert_Table[V_usOAD_Data].V_uc645Length;

	            Str_Encode = Str_FrozenConvert_Table[V_usOAD_Data];
				SF_FrozenDataFF_NextNum( &Str_Encode, V_usOAD_Data );//按费率数赋值数据长度及数据个数

	            if( ( SF_FrozenData_JudgeRateNum(V_usOAD_Data, Str_Encode.V_ulOAD) ) == C_Error )//费率数超，应答空，数据层返回数据0xBB
	            {
	                P_Data[V_usDataoffset] = C_NotSupportAOD_DataBB;
	                V_usDataoffset += CL_NotSupportAOD_DataBB;
	                V_usOffset += V_ucNextDataLenTol;//全部块数据长度
	            }
	            else
	            {
					 if( Str_Encode.V_uc698Type == C_array ) //需要读多个645标识码
					 {
						 for( V_ucj=1; V_ucj <= Str_Encode.V_uc698NextNum; V_ucj++ )
						 {
	                           Str_EncodeNext = Str_FrozenConvert_Table[ V_usOAD_Data + V_ucj ];
	                           V_ucData_Length = Str_EncodeNext.V_uc645Length;
				               SF_FrozenDataFF_NextNum( &Str_EncodeNext, (V_usOAD_Data + V_ucj) );

			                   PF_CopyDataBytes_698(&V_DataBuff[V_usOffset], &P_Data[V_usDataoffset], Str_EncodeNext.V_uc645Length);
	                           V_usDataoffset += Str_EncodeNext.V_uc645Length;//根据费率数的长度
	                            V_usOffset += V_ucData_Length;
						 }
	                     if( V_ucj < V_ucNextDataNumTol)//数据块全长计算
	                     {
	                          for( ; V_ucj <= V_ucNextDataNumTol; V_ucj++ )
	                          {
	                               Str_EncodeNext = Str_FrozenConvert_Table[ V_usOAD_Data + V_ucj ];
	                               V_ucData_Length = Str_EncodeNext.V_uc645Length;
	                               V_usOffset += V_ucData_Length;
	                          }
	                     }
				     }
					 else
					 {
			             PF_CopyDataBytes_698(&V_DataBuff[V_usOffset], &P_Data[V_usDataoffset], Str_Encode.V_uc645Length);
	                     V_usDataoffset += Str_Encode.V_uc645Length;//根据费率数的长度
	                     V_usOffset += V_ucNextDataLenTol;//全部块数据长度
					 }
	            }
			    *P_Data_Length = V_usDataoffset;
			}
            if(V_ucTurn == 0)
            {
                V_usDataLength = *P_Data_Length;
                PF_CopyDataBytes_698(V_DataBuff, P_Data, V_usDataLength);
            }
		}
    }
    else
    {
        V_usDataLength = *P_Data_Length;
		PF_CopyDataBytes_698(V_DataBuff, P_Data, V_usDataLength);
    }
	return C_OK;
}
#endif

/**********************************************************************************************************
函数原型：uchar8 Inf_ReadEventLast_X(Str_Read_T *pStr_Read, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, Str_SuppInfo *pStr_SuppInfo)
功能描述：读取上N次事件记录数据(包含)
输入参数：pStr_Read为读取参数结构体
    pV_ucDataBuf为读取缓存地址
	*pV_usDataLen为读取缓存最大长度
	pV_ucSupplementaryInformation为辅助信息缓存地址
	*pV_usSIDataLen为辅助信息缓存最大长度
输出参数：*pV_ucDataBuf为读取数据
	*pV_usDataLen为读取数据实际长度
	pV_ucSupplementaryInformation为辅助信息数据
	*pV_usSIDataLen为辅助信息数据实际长度
返回参数：C_OK正确，其他返回具体错误
调用位置：事件模块读事件记录接口调用
备    注：*pV_usDataLen必须大于等于所取值长度，不然返回错误；
***************************************************************************************************************/
uchar8 Inf_ReadEventLast_X(Str_Read_T *pStr_Read, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, Str_SuppInfo *pStr_SuppInfo)
{
	uchar8		V_ucTurn, V_uci, V_ucj, V_uck, V_ucData_Length, V_ucReturn;
    uchar8      V_ucNextDataNumTol, V_ucReadEventDegree, V_ucNextDataLenTol;
    uchar8      V_ucDataBuff[C_EventMAXLen]={0};
	ushort16	V_usOADTab_Length, V_usOAD_Data, V_usDataLength;
	ushort16	V_usOAD[C_EventMAXRelatedOAD];
	ushort16	V_usOffset=0, V_usDataoffset = 0;;
	Struct_FrozenConvert_Type Str_Encode;
    Struct_FrozenConvert_Type Str_EncodeNext;
    ulong32     V_ulOADoffset, *pV_Data_Id_OAD;
    uchar8 V_ucSpecicalDataLen = 0;

    pV_Data_Id_OAD = pStr_Read->pV_ulROAD;

    V_ulOADoffset = pStr_Read->pV_ulROAD[0] & 0x000000FF;
	for(V_uci = 0; V_uci<EventMappingTable_Len; V_uci++)
	{
		if(((EventMappingTable[V_uci].WriteOAD &0xFFFFFF00) | V_ulOADoffset) == pV_Data_Id_OAD[0])
		{
			break;
	    }
	}
	if(V_uci>=EventMappingTable_Len)
	{
		 return C_OtherErr;
    }

	V_ucReturn = InF_GetData_Record_DataBase(pStr_Read, V_ucDataBuff, pV_usDataLen, pStr_SuppInfo);
	if(V_ucReturn != C_OK)
	{
		return V_ucReturn;
	}
    V_ucReadEventDegree = pStr_SuppInfo->V_ucFrameNum;/*bit0-bit3，表示读取的条数*/

	V_usOADTab_Length = C_EventMAXRelatedOADLen;
	if(InF_ReadOADTab_Data(EventMappingTable[V_uci].OADTab, (uchar8 *)&V_usOAD, &V_usOADTab_Length)!=C_OK)
	{
		return C_Error;
	}
	if(pV_Data_Id_OAD[1] == 0xFFFFFFFF)
	{
        for( V_uck = 0; V_uck < V_ucReadEventDegree; V_uck++)
        {
            PF_CopyDataBytes_698( &V_ucDataBuff[V_usOffset], &pV_ucDataBuf[V_usDataoffset], (CLEventDegree + CLEventHappenTime + CLEventEndTime) );
		    V_usOffset += CLEventDegree + CLEventHappenTime + CLEventEndTime;		/*事件序号、发生时间、结束时间偏移*/
            V_usDataoffset += CLEventDegree + CLEventHappenTime + CLEventEndTime;	/*事件序号、发生时间、结束时间偏移*/

            if(EventMappingTable[V_uci].SourceFlag == C_SourceExist)
		    {
                pV_ucDataBuf[V_usDataoffset] = V_ucDataBuff[V_usOffset];
			    V_usOffset += CLEventSource;	/*事件发生源偏移*/
                V_usDataoffset += CLEventSource;
		    }
            pV_ucDataBuf[V_usDataoffset] = V_ucDataBuff[V_usOffset];

            V_usOffset +=  CLEventReport;/*新增上报状态*/
            V_usDataoffset +=  CLEventReport;
            /*特殊事件记录单元数据长度偏移*/
            SF_Event_SpecificDataLenCal(pV_Data_Id_OAD[0], &V_ucSpecicalDataLen);

            PF_CopyDataBytes(&V_ucDataBuff[V_usOffset], &pV_ucDataBuf[V_usDataoffset], V_ucSpecicalDataLen);

            V_usOffset += V_ucSpecicalDataLen;
            V_usDataoffset += V_ucSpecicalDataLen;

			/*按照OAD的顺序组织数据*/
			for( V_ucTurn = 0; V_ucTurn < (V_usOADTab_Length/2); V_ucTurn++ )
			{
			    V_usOAD_Data = V_usOAD[V_ucTurn] & 0x1FFF; /*关联属性列表中的行号*/

				V_ucNextDataNumTol = Str_FrozenConvert_Table[V_usOAD_Data].V_uc698NextNum;
	            V_ucNextDataLenTol = Str_FrozenConvert_Table[V_usOAD_Data].V_uc645Length;

	            Str_Encode = Str_FrozenConvert_Table[V_usOAD_Data];

                SF_FrozenDataFF_NextNum( &Str_Encode, V_usOAD_Data );/*按费率数赋值数据长度及数据个数*/

	            if( ( SF_FrozenData_JudgeRateNum(V_usOAD_Data, Str_Encode.V_ulOAD) ) == C_Error )/*费率数超，应答空，数据层返回数据0xBB*/
	            {
	                pV_ucDataBuf[V_usDataoffset] = C_NotSupportAOD_DataBB;

                    V_usDataoffset += CL_NotSupportAOD_DataBB;
	                V_usOffset += V_ucNextDataLenTol;/*全部块数据长度*/
	            }
                else
	            {
                    if( Str_Encode.V_uc698Type == C_array ) /*需要读多个645标识码*/
                    {
                        for( V_ucj=1; V_ucj <= Str_Encode.V_uc698NextNum; V_ucj++ )
                        {
                            Str_EncodeNext = Str_FrozenConvert_Table[ V_usOAD_Data + V_ucj ];
                            V_ucData_Length = Str_EncodeNext.V_uc645Length;

                            SF_FrozenDataFF_NextNum( &Str_EncodeNext, (V_usOAD_Data + V_ucj) );

                            PF_CopyDataBytes_698(&V_ucDataBuff[V_usOffset], &pV_ucDataBuf[V_usDataoffset], Str_EncodeNext.V_uc645Length);

                            V_usDataoffset += Str_EncodeNext.V_uc645Length;/*根据费率数的长度*/
                            V_usOffset += V_ucData_Length;
                        }
                        if( V_ucj < V_ucNextDataNumTol)/*数据块全长计算*/
                        {
                            for( ; V_ucj <= V_ucNextDataNumTol; V_ucj++ )
                            {
                                Str_EncodeNext = Str_FrozenConvert_Table[ V_usOAD_Data + V_ucj ];

                                V_ucData_Length = Str_EncodeNext.V_uc645Length;
                                V_usOffset += V_ucData_Length;
                            }
                        }
				     }
					 else
					 {
			             PF_CopyDataBytes_698(&V_ucDataBuff[V_usOffset], &pV_ucDataBuf[V_usDataoffset], Str_Encode.V_uc645Length);

                         V_usDataoffset += Str_Encode.V_uc645Length;/*根据费率数的长度*/
	                     V_usOffset += V_ucNextDataLenTol;/*全部块数据长度*/
					 }
	            }
			    *pV_usDataLen = V_usDataoffset;
			}
            if(V_ucTurn == 0)
            {
                V_usDataLength = *pV_usDataLen;
                PF_CopyDataBytes_698(V_ucDataBuff, pV_ucDataBuf, V_usDataLength);
            }
		}
    }
    else
    {
        V_usDataLength = *pV_usDataLen;
		PF_CopyDataBytes_698(V_ucDataBuff, pV_ucDataBuf, V_usDataLength);
    }
	return C_OK;
}

/**********************************************************************************************************
函数原型：uchar8 InF_Get_EventModule(Str_Read_T *pStr_Read, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, uchar8 *pV_ucSupplementaryInformation, ushort16 *pV_usSIDataLen)
功能描述：通信读取事件记录数据
输入参数：pStr_Read为读取参数结构体
    pV_ucDataBuf为读取缓存地址
	*pV_usDataLen为读取缓存最大长度
	pV_ucSupplementaryInformation为辅助信息缓存地址
	*pV_usSIDataLen为辅助信息缓存最大长度
输出参数：*pV_ucDataBuf为读取数据
	*pV_usDataLen为读取数据实际长度
	pV_ucSupplementaryInformation为辅助信息数据
	*pV_usSIDataLen为辅助信息数据实际长度
返回参数：C_OK正确，其他返回具体错误
调用位置：对象管理层调用
备    注：
***************************************************************************************************************/
uchar8 InF_Get_EventModule(Str_Read_T *pStr_Read, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, Str_SuppInfo *pStr_SuppInfo)
{
    uchar8 V_ucReturn = C_OtherErr;
	uchar8 V_ucNum, V_ucReadBuff[2];
	ushort16 V_usOffset, V_usLen;
	Str_Read_T Str_ReadOADTemp;
	Str_SuppInfo Str_SuppInfoTemp;
	
    if((pStr_Read->pV_ulROAD[0] & 0x000000FF) == 0x00000001)/*读上一次记录数据*/
    {
        V_ucReturn = Inf_ReadEventLast_1(pStr_Read, pV_ucDataBuf, pV_usDataLen, pStr_SuppInfo);
    }
    else/*读上2-N记录数据*/
    {
        V_ucReturn = Inf_ReadEventLast_X(pStr_Read, pV_ucDataBuf, pV_usDataLen, pStr_SuppInfo);
		
		if( (V_ucReturn == C_OK)
			&& (pStr_SuppInfo -> V_ucFrameNum != C_InActive)/*读到有数据*/
			&& (pStr_SuppInfo -> V_ucLastFlag == C_Active_LastEvent) )/*读到的数据包含最近一条*/
		{
			V_ucNum = pStr_SuppInfo -> V_ucFrameNum;
			V_usLen = *pV_usDataLen  / V_ucNum;
			V_usOffset = V_usLen * (V_ucNum - 1);
			
			V_ucReadBuff[0] = 9;/*方法9*/
    		V_ucReadBuff[1] = 1;/*上N次*/
			
			Str_ReadOADTemp.pV_ulROAD = pStr_Read -> pV_ulROAD;
			Str_ReadOADTemp.pV_ulROAD[0] = ((Str_ReadOADTemp.pV_ulROAD[0] & 0xFFFFFF00) | 0x01);
			Str_ReadOADTemp.pV_ucRST = V_ucReadBuff;
			Str_ReadOADTemp.V_usROAD_Num = 1;
			Str_ReadOADTemp.V_ucReadMode = C_OtherMode;
			Str_ReadOADTemp.V_ucChannelNo = 0xFF;
			
			Str_SuppInfoTemp.pV_usEncode = pStr_SuppInfo->pV_usEncode;
			
			V_ucReturn = Inf_ReadEventLast_1(pStr_Read, pV_ucDataBuf + V_usOffset, &V_usLen, &Str_SuppInfoTemp);
			
			if(V_ucReturn == C_OK)
			{
				pStr_SuppInfo->V_ucLastFlag = Str_SuppInfoTemp.V_ucLastFlag;
			}
		}
    }
    return V_ucReturn;
}
/*******************************************************************************
函数原型： uchar8 Inf_GetPowerDownEventType(uchar8 EventNo)
功能描述： 获取事件当前状态，发生还是恢复
输入参数：
输出参数：
返回参数：
调用位置：
备    注：
*******************************************************************************/
uchar8 Inf_GetPowerDownEventType(uchar8 EventNo)
{
    uchar8 V_ucReturn = C_End_EventState;

    if(EventNo < C_EventNoLength)
    {
        V_ucReturn = GV_ucEvent_Hstate[EventNo];
    }

    return V_ucReturn;
}

/*******************************************************************************
函数原型：SF_FillEvtRenew
功能描述：将事件实时数据填入缓存中
输入参数：V_usOffset：所读关联OAD数据在public表格中的偏移(行号)；
        V_usOAD_State：关联OAD的属性特征，；
        *V_ucBuff：所有数据缓存的首地址;
        *V_usOffset：当前数据存放在V_ucBuff中的首地址偏移
		V_ucEvent_Flag：事件发生结束标志，低4位0x01发生，0x02结束，高4位为有发生过程中数据事件的区分
输出参数： *V_ucBuff：所有数据缓存的首地址;
        *V_usOffset：当前数据放好后的偏移
返回参数：无
调用位置：Inf_GetRecordData需存放事件当前数据时调用
备    注：
*******************************************************************************/
void SF_FillEvtRenew(ushort16 V_usLineNum, ushort16 V_usOAD_State, uchar8 *pV_ucBuff, ushort16 *pV_usOffset, uchar8 V_ucEvtStatus, uchar8 V_ucEvent_Flag)
{
	ulong32 V_ulReadBuff[3] = {0}, V_ul698OAD;
	uchar8 V_ucData_Length, V_ucLen;
	
	V_ul698OAD = Str_FrozenConvert_Table[V_usLineNum].V_ulOAD;
	V_ucData_Length = Str_FrozenConvert_Table[V_usLineNum].V_uc645Length;
	
	if(V_ucEvtStatus == C_Need)
	{
		switch(V_ucEvent_Flag & 0xF0)
		{
			case	0x10:
				V_ulReadBuff[0] = CLossAVol_FF_1;
				break;
			case	0x20:
				V_ulReadBuff[0] = CLossBVol_FF_1;
				break;
			case	0x30:
				V_ulReadBuff[0] = CLossCVol_FF_1;
				break;
			case	0x40:
				V_ulReadBuff[0] = CLowAVol_FF_1;
				break;
			case	0x50:
				V_ulReadBuff[0] = CLowBVol_FF_1;
				break;
			case	0x60:
				V_ulReadBuff[0] = CLowCVol_FF_1;
				break;
			case	0x70:
				V_ulReadBuff[0] = COverAVol_FF_1;
				break;
			case	0x80:
				V_ulReadBuff[0] = COverBVol_FF_1;
				break;
			case	0x90:
				V_ulReadBuff[0] = COverCVol_FF_1;
				break;
			case	0xA0:
				V_ulReadBuff[0] = CBreakAVol_FF_1;
				break;
			case	0xB0:
				V_ulReadBuff[0] = CBreakBVol_FF_1;
				break;
			case	0xC0:
				V_ulReadBuff[0] = CBreakCVol_FF_1;
				break;
			case	0xD0:
				V_ulReadBuff[0] = CNoBalVol_FF_1;
				break;
			case	0xE0:
				V_ulReadBuff[0] = CNoBalCurr_FF_1;
				break;
			case	0xF0:
				V_ulReadBuff[0] = CSevNoBalCurr_FF_1;
				break;
			default:
				break;
		}
		V_ulReadBuff[1] = V_ul698OAD;
		V_ulReadBuff[1] |= (ulong32)(V_usOAD_State << 13);
		V_ulReadBuff[2] = 0xFFFFFFFF;
		
		V_ucLen = V_ucData_Length;
		if(Inf_ReadEventRenew(V_ulReadBuff, (pV_ucBuff + *pV_usOffset), &V_ucLen) != C_OK)   /*读取数据*/
		{
			memset((pV_ucBuff + *pV_usOffset), 0xAA, V_ucData_Length);
		}
	}
	*pV_usOffset += V_ucData_Length;
}

/*******************************************************************************
函数原型：SF_FillEvtComData
功能描述：将事件普通数据（非实时数据）填入缓存中
输入参数：V_usLineNum：所读关联OAD数据在public表格中的偏移(行号)；
        *pV_ucBuff：所有数据缓存的首地址;
        *pV_usOffset：当前数据存放在V_ucBuff中的首地址偏移
		V_ucEvtStatus：数据是否需要获取的状态
输出参数： *V_ucBuff：所有数据缓存的首地址;
        *V_usOffset：当前数据放好后的偏移
返回参数：无
调用位置：Inf_GetRecordData需存放事件当前数据时调用
备    注：
*******************************************************************************/
void SF_FillEvtComData(ushort16 V_usLineNum, uchar8 *pV_ucBuff, ushort16 *pV_usOffset, uchar8 V_ucEvtStatus)
{
	ulong32 V_ul698OAD;
	ushort16 V_usData_Length, V_usEncode;
	uchar8 V_ucData_Length;
	
	V_ul698OAD = Str_FrozenConvert_Table[V_usLineNum].V_ulOAD;
	V_ucData_Length = Str_FrozenConvert_Table[V_usLineNum].V_uc645Length;
	
	if(V_ucEvtStatus == C_Need)
	{
		V_usData_Length = V_ucData_Length;
		if(InF_GetData_ObjectManage(V_ul698OAD, (pV_ucBuff + *pV_usOffset), &V_usData_Length, &V_usEncode) != C_OK)   /*读取数据*/
		{
			memset((pV_ucBuff + *pV_usOffset), 0xAA, V_ucData_Length);
		}
	}
	*pV_usOffset += V_ucData_Length;
}

/*******************************************************************************
函数原型：uchar8 Inf_GetRecordData(uchar8 *V_ucData, ushort16 *V_ucLength, ulong32 V_OADTab, uchar8 V_ucTypeFlag)
功能描述：获取事件记录和冻结所需数据
输入参数：*V_ucData：数据所放缓存
        *V_ucLength：缓存长度；
        V_OADTab：事件关联OAD序号表，若为冻结调用该OAD为0x50FFFFFF;
        V_ucTypeFlag：为事件时：事件发生结束标志，低4位0x01发生，0x02结束，高4位为有发生过程中数据事件的区分；
                        为冻结时：冻结类型
输出参数：*V_ucData：读取数据的缓存;
        *V_ucLength：读取的数据长度;
返回参数：C_OK、C_Error
调用位置：事件记录、冻结
备    注：
*******************************************************************************/
uchar8 Inf_GetRecordData(uchar8 *V_ucData, ushort16 *V_usLength, ulong32 V_ulOADTab, uchar8 V_ucTypeFlag)
{
    uchar8 V_ucTurn, V_uci= 0, V_uc645DINum;
	ushort16 V_usOADTab_Length;
	uchar8 V_ucData_Length;
	ushort16 V_usOAD[300], V_usOAD_Data, V_usOAD_State;
	ulong32 V_ul698OAD;
	ushort16 V_usOffset = 0;
	uchar8 V_ucType;
	ushort16 V_usBuffMaxLen;
	uchar8 V_ucDataBuff[C_EventMAXLen] = {0};
    uchar8 V_ucBuff_Zero[C_3Curr_Length] = {0};
    uchar8 V_ucCurrentTime[CLDate_Week_Time], V_ucBeginTime[CLDate_Week_Time], V_ucFrozenType, V_ucNum, V_usOADNum, V_ucMulti;
    ushort16 V_usData_Length, V_usEncode;
    ulong32 V_ulNum, V_ulOADNumDI, V_ulOADTable, V_ulSubDays, V_ulSubHours, V_ulSubMins, V_ulIntertime, V_ulFrozenNum, V_ulSubResult;
    uchar8 V_ucIntertimeFlag[96] = {0}, V_ucEvent_Flag, V_ucRecType, V_ucEvtStatus = C_NoNeed;

    V_usBuffMaxLen = *V_usLength;

    if( (V_ulOADTab & 0xFF000000) == C_FrzOAD )
    {
        V_ucRecType = C_Frz;
    }
    else
    {
        V_ucRecType = C_Evt;
    }
    /*冻结做的特殊处理*/
    if(V_ucRecType == C_Frz)
    {
        V_usData_Length = CLDate_Week_Time;
        if( InF_GetData_ObjectManage(CDate_Time, &V_ucCurrentTime[0], &V_usData_Length, &V_usEncode) != C_OK )
        {
            return C_Error;
        }
        if(V_usBuffMaxLen < CLDate_Time)
        {
            return C_DataLenError;
        }
        PF_CopyDataBytes(&V_ucCurrentTime[0], V_ucDataBuff, CLDate_Week_Time);
        V_usOffset += CLDate_Week_Time;

        /*根据冻结类型，赋值读OAD标识码*/
        V_ucFrozenType = V_ucTypeFlag;

        if( ( V_ucFrozenType & 0xf0 ) == C_Minute_Type )    /*分钟冻结*/
        {
            V_ucNum = (V_ucFrozenType & 0x0f);    /*方案号*/
            V_usData_Length = 6 * C_FreezeMAXRelatedOAD;
            if( InF_GetMinFreezeNum_OADTab(V_ucNum, (uchar8 *)&V_usOAD, &V_usData_Length) != C_OK )
            {
                return C_Error;
            }
            V_usOADNum = V_usData_Length / 6;
            if(V_usOADNum > C_FreezeMAXRelatedOAD)
            {
                return C_Error;
            }
            V_ulNum = V_ucNum;
            V_ulNum <<= 21;
            V_ul698OAD = C_RelatedOAD_Min | V_ulNum;
        }
        else
        {
            switch (V_ucFrozenType)
            {
                case C_Immediate_Type:
                {
                    V_ulOADNumDI = CI_Free_OADTabLen_T;
                    V_ulOADTable = CI_Free_OADTab;
                    V_ul698OAD = C_RelatedOAD_Immid;
                }break;
                case C_Hour_Type:
                {
                    V_ulOADNumDI = CH_Free_OADTabLen_T;
                    V_ulOADTable = CH_Free_OADTab;
                    V_ul698OAD = C_RelatedOAD_Hour;
                }break;
                case C_Day_Type:
                case C_Day_Type_Add:
                {
                    V_ulOADNumDI = CD_Free_OADTabLen_T;
                    V_ulOADTable = CD_Free_OADTab;
                    V_ul698OAD = C_RelatedOAD_Day;
                }break;
                case C_Settlement_Type:
                {
                    V_ulOADNumDI = CSett_Free_OADTabLen_T;
                    V_ulOADTable = CSett_Free_OADTab;
                    V_ul698OAD = C_RelatedOAD_Settle;
                }break;
                case C_Month_Type:
                case C_Month_Type_Add:
                {
                    V_ulOADNumDI = CM_Free_OADTabLen_T;
                    V_ulOADTable = CM_Free_OADTab;
                    V_ul698OAD = C_RelatedOAD_Month;
                }break;
                case C_Change_TimeZone_Type:
                {
                    V_ulOADNumDI = CTZ_Free_OADTabLen_T;
                    V_ulOADTable = CTZ_Free_OADTab;
                    V_ul698OAD = C_RelatedOAD_TimeZone;
                }break;
                case C_Change_TimePeriod_Type:
                {
                    V_ulOADNumDI = CPT_Free_OADTabLen_T;
                    V_ulOADTable = CPT_Free_OADTab;
                    V_ul698OAD = C_RelatedOAD_TimeRegion;
                }break;
                case C_Change_Fate_Type:
                {
                    V_ulOADNumDI = CR_Free_OADTabLen_T;
                    V_ulOADTable = CR_Free_OADTab;
                    V_ul698OAD = C_RelatedOAD_RateTalbe;
                }break;
                case C_Change_Ladder_Type:
                {
                    V_ulOADNumDI = CL_Free_OADTabLen_T;
                    V_ulOADTable = CL_Free_OADTab;
                    V_ul698OAD = C_RelatedOAD_StepTable;
                }break;
                case C_YSettle_Type:
                {
                    V_ulOADNumDI = CYSettle_Free_OADTabLen_T;
                    V_ulOADTable = CYSettle_Free_OADTab;
                    V_ul698OAD = C_RelatedOAD_YSettle;
                }break;
                default:
                    return C_Error;
                break;
            }

            /*读OAD及OAD个数*/
            V_usData_Length = CLTZ_Free_OADTabLen_T;
            if( InF_GetData_ObjectManage(V_ulOADNumDI, &V_usOADNum, &V_usData_Length, &V_usEncode) != C_OK )
            {
                return C_Error;
            }

            if(V_usOADNum > C_FreezeMAXRelatedOAD)
            {
                return C_Error;
            }


            V_usData_Length = 6 * V_usOADNum;
            if( InF_ReadOADTab_Data(V_ulOADTable, (uchar8 *)&V_usOAD, &V_usData_Length) != C_OK )
            {
                return C_Error;
            }
        }
        SF_GetFreeze_StartTime(V_ucBeginTime);

        for(V_ucTurn = 0; V_ucTurn < (V_usOADNum * 3); V_ucTurn++)
        {
            V_usOAD[V_ucTurn] &= 0x1FFF;

            if(V_usOAD[V_ucTurn + 1] == 0)
            {
                V_usOAD[V_ucTurn + 1] = 1;
            }

            if((V_ucFrozenType & 0xf0) == C_Minute_Type)    /*分钟冻结*/
            {
                if(PF_TimeSub_Min_698(V_ucCurrentTime, V_ucBeginTime, &V_ulSubMins) == C_GreaterThan)
                {
                    PF_BufferXToUlong32((uchar8 *)&V_usOAD[V_ucTurn + 1], &V_ulIntertime, 2);
                    if(V_ulSubMins % V_ulIntertime)
                    {
                        V_ucIntertimeFlag[V_ucTurn / 3] = 0x68;
                    }
                }
            }
            else
            {
                switch (V_ucFrozenType)
                {
                    case C_Hour_Type:       /*小时冻结*/
                    {
                        if(PF_TimeSub_Hour_698(V_ucCurrentTime, V_ucBeginTime, &V_ulSubHours) == C_GreaterThan)
                        {
                            PF_BufferXToUlong32((uchar8 *)&V_usOAD[V_ucTurn + 1], &V_ulIntertime, 2);
                            if(V_ulSubHours % V_ulIntertime)
                            {
                                V_ucIntertimeFlag[V_ucTurn / 3] = 0x68;
                            }
                        }
                    }break;
                    case C_Day_Type:        /*日冻结*/
                    {
                        if(PF_TimeSub_Day_698(V_ucCurrentTime, V_ucBeginTime, &V_ulSubDays) == C_GreaterThan)
                        {
                            if(V_ulSubDays % V_usOAD[V_ucTurn + 1])
                            {
                                V_ucIntertimeFlag[V_ucTurn / 3] = 0x68;
                            }
                        }
                    }break;
                    case C_Month_Type:      /*月冻结*/
                    {    /*计算2个时间差几个月*/
                        V_ulSubResult = 12 * (V_ucCurrentTime[5] - V_ucBeginTime[5]);

                        V_ulSubResult += V_ucCurrentTime[4];

                        V_ulSubResult -= V_ucBeginTime[4];

                        PF_BufferXToUlong32((uchar8 *)&V_usOAD[V_ucTurn+1], &V_ulIntertime, 2);

                        if(V_ulSubResult%V_ulIntertime)
                        {
                            V_ucIntertimeFlag[V_ucTurn/3] = 0x68;
                        }

                    }break;
                    case C_Change_TimeZone_Type:
                    case C_Immediate_Type:  /*瞬时冻结*/
                    case C_Change_TimePeriod_Type:
                    case C_Change_Fate_Type:
                    case C_Change_Ladder_Type:
                    case C_Settlement_Type: /*结算日冻结*/
                    case C_Day_Type_Add:    /*日冻结补冻*/
                    case C_YSettle_Type:    /*阶梯结算冻结*/
                    case C_Month_Type_Add:  /*月冻结补冻*/
                        break;
                    default:
                        return C_Error;
                    break;
                }
            }
            V_ucTurn += 2;
        }
        /*读上一次冻结序号数据，赋值*/
        V_ucData_Length = 4;
        if(InF_ReadLaterFreezeNum(V_ul698OAD, (uchar8 *)&V_ulFrozenNum, &V_ucData_Length) != C_OK)
        {
            return C_Error;
        }
        if(V_usBuffMaxLen < ( V_usOffset + 4 ) )
        {
            return C_DataLenError;
        }
        PF_CopyDataBytes((uchar8 *)&V_ulFrozenNum, (V_ucDataBuff + V_usOffset), 4);
        V_usOffset += 4;

        for( V_ucTurn = 0; V_ucTurn < (V_usOADNum * 3); V_ucTurn++)
        {
            if(V_ucIntertimeFlag[V_ucTurn / 3] != 0x68)
            {
                break;
            }
            V_ucTurn += 2;
        }

        if( V_ucTurn >= (V_usOADNum * 3) )
        {
            return C_Error;
        }
        V_usOADTab_Length = V_usOADNum;/*冻结关联列表个数赋值*/
    }
    else/*事件处理*/
    {
        V_usOADTab_Length = 120;
        if(InF_ReadOADTab_Data(V_ulOADTab, (uchar8 *)&V_usOAD, &V_usOADTab_Length) != C_OK)
        {
            return C_Error;
        }
        V_usOADTab_Length = (V_usOADTab_Length / 2);
    }

	/*按照OAD的顺序组织数据*/
	for( V_ucTurn = 0; V_ucTurn < V_usOADTab_Length; V_ucTurn++)
	{
        if(V_ucRecType == C_Frz)
        {
            V_ucMulti = 3 * V_ucTurn;/*冻结每项存储6字节（2*3）*/
        }
        else
        {
            V_ucMulti = V_ucTurn;/*事件每项存储2字节（2*1）*/
        }
		V_usOAD_Data = V_usOAD[V_ucMulti] & 0x1FFF;
		V_usOAD_State = V_usOAD[V_ucMulti] >> 13;

		if(V_usOAD_Data > Str_FrozenConvert_Table_Len)
		{
			return C_Error;
		}

		V_ul698OAD = Str_FrozenConvert_Table[V_usOAD_Data].V_ulOAD;
		V_ucData_Length = Str_FrozenConvert_Table[V_usOAD_Data].V_uc645Length;
		V_ucType = Str_FrozenConvert_Table[V_usOAD_Data].V_uc698Type;
		V_uc645DINum = Str_FrozenConvert_Table[V_usOAD_Data].V_uc698NextNum;

        if(V_ucRecType == C_Frz)/*冻结特有处理*/
        {
            if(V_ucIntertimeFlag[V_ucTurn] == 0x68)/*冻结，未到时间，补AA*/
            {
                for( V_uci = 0; V_uci < V_ucData_Length; V_uci++)
                {
                    *(V_ucDataBuff + V_usOffset) = 0xAA;
                    V_usOffset += 1;
                }
                if( V_usOffset > V_usBuffMaxLen )	    /*最大长度不能超过输入Buff长度和自身Buff长度*/
                {
                    return	C_DataLenError;
                }
                else
                {
                    continue;
                }
            }
            V_ucEvent_Flag = 0;/*冻结时将事件标志置0*/

            V_ucEvtStatus = C_Need;/*后续取关联列表相关数据判断是否需要获取，冻结因为不区分发生结束，统一置需要*/
        }
        else/*事件类特有处理*/
        {
            V_ucEvent_Flag = V_ucTypeFlag;

            if ( ( ( ( V_usOAD_State == 0x0001 ) || ( V_usOAD_State == 0x0002 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x01 ) )
                  || ( ( ( V_usOAD_State == 0x0003 ) || ( V_usOAD_State == 0x0004 ) ) && ( ( V_ucEvent_Flag & 0x03 ) == 0x02 ) ) )
            {
                V_ucEvtStatus = C_Need;/*后续取关联列表相关数据判断是否需要获取，这里统一置标志*/
            }
			else
			{
				V_ucEvtStatus = C_NoNeed;
			}
        }

        if ( ( ( V_ucEvent_Flag & 0x0C ) == 0x04 )
          && ( ( V_usOAD_State == 0x0003 ) || ( V_usOAD_State == 0x0004 ) ) )
		{
			memset((V_ucDataBuff + V_usOffset), 0xAA, V_ucData_Length);
			V_usOffset += V_ucData_Length;
		}
		else if ( ( V_ul698OAD == CKey_State )
               && ( V_usOAD_State == 0x0001 )
			   && ( V_ulOADTab == CProgKD_OADTab ) )                 /*更新前密钥状态*/
        {
			if((V_ucEvent_Flag & 0x03) == 0x01)
			{
            	PF_CopyDataBytes(GV_KeyHState, (V_ucDataBuff + V_usOffset), CLKey_State_698);
			}
			V_usOffset += CLKey_State_698;
        }
        else if( (V_ucRecType == C_Evt)
                && (V_ucEvent_Flag & 0xF0)/*事件记录中有实时数据的*/
				&& ( ( (V_ul698OAD & 0xffff0000) == 0x20290000)/*安时数*/
					|| ((V_ul698OAD & 0xffff0000) == 0x20260000)/*电压不平衡*/
					|| ((V_ul698OAD & 0xffff0000) == 0x20270000) ) )/*电流不平衡*/
        {
            if(V_ucType == C_array)     /*需要读多个645标识码*/
			{
				for( V_uci = 1; V_uci <= V_uc645DINum; V_uci++)
				{
                    SF_FillEvtRenew(V_usOAD_Data + V_uci, V_usOAD_State, V_ucDataBuff, &V_usOffset, V_ucEvtStatus, V_ucEvent_Flag);
				}
			}
			else
			{
				SF_FillEvtRenew(V_usOAD_Data, V_usOAD_State, V_ucDataBuff, &V_usOffset, V_ucEvtStatus, V_ucEvent_Flag);
			}
        }
		else if ( ( V_ul698OAD == CPhaseFF_Curr )
		       && ( V_ulOADTab == CAll_Loss_Vol_OADTab )
			   && ( V_usOAD_State == 0x0001 )
			   && ( ( V_ucEvent_Flag & 0x03 ) == 0x01 ) )
		{
			if(PF_Campare_Data(GStr_TotalvoltageloseStr.NoVoltageCurrent, V_ucBuff_Zero, CLPhaseFF_Curr) != C_Equal)
			{
				PF_CopyDataBytes(GStr_TotalvoltageloseStr.NoVoltageCurrent, (V_ucDataBuff + V_usOffset), CLPhaseFF_Curr);
				V_usOffset += CLPhaseFF_Curr;
			}
			else
			{
				for( V_uci = 1; V_uci <= V_uc645DINum; V_uci++)
				{
					SF_FillEvtComData(V_usOAD_Data + V_uci, V_ucDataBuff, &V_usOffset, C_Need);
				}
			}
		}
		else
		{
			if( ( ( V_ucType == C_array ) || ( ( V_ucType == C_structure ) && ( V_uc645DINum > 1 ) ) )    /*需要读多个*/
				&& ( (V_ul698OAD != CFirst_TZone_Data)
					&& (V_ul698OAD != CSec_TZone_Data)
					&& (V_ul698OAD != C_RelayFa_State) ) )/*时区表和继电器输出不需要for循环读*/
			{
				for( V_uci = 1; V_uci <= V_uc645DINum; V_uci++)
				{
					SF_FillEvtComData(V_usOAD_Data + V_uci, V_ucDataBuff, &V_usOffset, V_ucEvtStatus);
				}
			}
			else
			{
				if(V_ucEvtStatus == C_Need)
				{
                    if ( ( ( ( V_ul698OAD & 0xFFFFFF00 ) == CSec_TZone_Data ) && ( V_ul698OAD != CSec_TZone_Data ) )
                      || ( ( ( V_ul698OAD & 0xFFFFFF00 ) == CFirst_TZone_Data ) && ( V_ul698OAD != CFirst_TZone_Data ) ) )
                    {
                        V_usData_Length = CLFirst_TZone_Data;
                        V_ucData_Length = Str_FrozenConvert_Table[V_usOAD_Data].V_uc645Length;

                        if( InF_GetData_ObjectManage( ( V_ul698OAD & 0xFFFFFF00 ), (V_ucDataBuff + V_usOffset), &V_usData_Length, &V_usEncode) == C_OK )
                        {
                            V_ucDataBuff[V_usOffset] = V_ucDataBuff[V_usOffset + ( ((uchar8)(V_ul698OAD)) - 1) * 3];
                            V_ucDataBuff[V_usOffset + 1] = V_ucDataBuff[V_usOffset+( ((uchar8)(V_ul698OAD)) - 1 ) * 3 + 1];
                            V_ucDataBuff[V_usOffset + 2] = V_ucDataBuff[V_usOffset+( ((uchar8)(V_ul698OAD)) - 1 ) * 3 + 2];
                        }
                        else
                        {
							memset((V_ucDataBuff + V_usOffset), 0xAA, V_ucData_Length);
							V_usOffset += V_ucData_Length;
                        }
                        V_usOffset += V_ucData_Length;
                    }
                    else
                    {
						SF_FillEvtComData(V_usOAD_Data, V_ucDataBuff, &V_usOffset, C_Need);
                    }
				}
				else
				{
					V_usOffset += V_ucData_Length;
				}
			}
		}
		if( (V_usOffset > V_usBuffMaxLen) || (V_usOffset > (C_EventMAXLen - 40) ) )	/*最大长度不能超过输入Buff长度和自身Buff长度*/
		{
			return	C_DataLenError;
		}
	}

	PF_CopyDataBytes_698(V_ucDataBuff, V_ucData, V_usOffset);
	*V_usLength = V_usOffset;

	return C_OK;
}


