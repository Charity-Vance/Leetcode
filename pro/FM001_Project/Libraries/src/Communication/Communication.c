
/****************************************************************************************
Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     communication.c
Author		jiangzs
Version:       V1
Date:          2014-3-12
Description:   通信处理、解析文件
Function List:
---------------------------------------------------------------------------------
History1:      第1次修改
内容1. Date:
   	   Author:
       Modification:
---------------------------------------------------------------------------------
内容2. Date:
   	   Author:
       Modification:
	---------------------------------------------------------------------------------
History2:      第2次修改
内容1. Date:
   	   Author:
       Modification:
---------------------------------------------------------------------------------
内容2. Date:
   	   Author:
       Modification:
****************************************************************************************/

#include "Communication.h"
#include "RTCDrive.h"
#include "ADC.h"

/*2020标准主动上报2005*/
uchar8  SV_REPORTCommBuff[C_ModuleMaxLen];
uchar8  SV_PowerfailReportONum[3];
uchar8  SV_ReportShutTime;
Str_Report_Parm SV_ReportSend;
Str_Comm_Parse_Local SV_Comm_Parse_Local;
Str_Comm_Parse		SV_Comm_Parse;
uchar8	SV_SetBPS_Flag;							/*C_OK设置BPS，C_Error其他通信命令*/
uchar8  SV_Comm_Address[CLComm_Address+2];
/*复旦微时钟调校*/
struct	TEMPERATURE_FRM		Tpara;
struct	RTC_TRIM_FRM	RTC_RT;
/*编程事件写表格*/
/*时段表*/
const	Str_ProgTable	TB_ProgTimePeriod[C_TB_ProgTimePeriod_Len] =
{
	{CProgPT_NoteC_1,		CFirst_TZone_1PT_Data,		CFirst_TZone_4PT_Data},
	{CProgPT_NoteD_1,		CFirst_TZone_5PT_Data,		CFirst_TZone_8PT_Data},
	{CProgPT_NoteE_1,		CSec_TZone_1PT_Data,		CSec_TZone_4PT_Data},
	{CProgPT_NoteF_1,		CSec_TZone_5PT_Data,		CSec_TZone_8PT_Data}
};
/*时区表*/
const	Str_ProgTable TB_ProgSeason[C_TB_ProgSeason_Len] =
{
	{CProgTZ_Note_1,	CFirst_TZone_Data,	CSec_TZone_Data}
};
/*周休日*/
const	Str_ProgTable	TB_ProgWeekRest[C_TB_ProgWeekRest_Len] =
{
	{CProgWRe_Note_1,	CWeek_RestDay_DTable,	CWeek_RestDay_DTable}
};
/*结算日1-3采用同一个表格*/
const	Str_ProgTable	TB_ProgSetADate[C_TB_ProgSetADate_Len] =
{
	{CProgSettD_Note_1,	CSettle_Day1,	CSettle_Day3}
};

/*有功组合状态字*/
const	Str_ProgTable	TB_ProgCombState_P[C_TB_ProgCombState_P_Len] =
{
	{CProgAcC_Note_1,	CActive_Com_State,	CActive_Com_State}
};

/*无功组合状态字698*/
const	Str_ProgTable	TB_ProgCombState_Q698[C_TB_ProgCombState_Q698_Len] =
{
	{CProgReC698_Note_1,CReactive_Com_State1,CReactive_Com_State2}
};
/*电能清零、需清事件记录写的表格。含义和上面不一样。仅仅是事件数据来源的数据标识码*/
/*清零事件记录表格*/
#define	C_TB_MeterClearEvent_Len		24
const	ulong32	TB_MeterClearEvent[C_TB_MeterClearEvent_Len] =
{
	CPos_Ac_Tol_En_0,		/*正向有功*/
	CRev_Ac_Tol_En_0,		/*反向有功*/
	CQua1_Re_Tol_En_0,		/* 1象限无功*/
	CQua2_Re_Tol_En_0,		/* 2象限无功*/
	CQua3_Re_Tol_En_0,		/* 3象限无功*/
	CQua4_Re_Tol_En_0,		/* 4象限无功*/
	CPosA_Ac_En_0,			/*A正向有功*/
	CRevA_Ac_En_0,			/*A反向有功*/
	CQua1A_Re_En_0,			/*A-1象限无功*/
	CQua2A_Re_En_0,			/*A-2象限无功*/
	CQua3A_Re_En_0,			/*A-3象限无功*/
	CQua4A_Re_En_0,			/*A-4象限无功*/
	CPosB_Ac_En_0,			/*B正向有功*/
	CRevB_Ac_En_0,			/*B反向有功*/
	CQua1B_Re_En_0,			/*B-1象限无功*/
	CQua2B_Re_En_0,			/*B-2象限无功*/
	CQua3B_Re_En_0,			/*B-3象限无功*/
	CQua4B_Re_En_0,			/*B-4象限无功*/
	CPosC_Ac_En_0,			/*C正向有功*/
	CRevC_Ac_En_0,			/*C反向有功*/
	CQua1C_Re_En_0,			/*C-1象限无功*/
	CQua2C_Re_En_0,			/*C-2象限无功*/
	CQua3C_Re_En_0,			/*C-3象限无功*/
	CQua4C_Re_En_0,			/*C-4象限无功*/
};

/*阶梯表编程记录*/
const	Str_ProgTable	TB_StepTariffEvent[C_TB_StepTariffEvent_Len] =
{
	{CProgLad_Note_1,	CCurrent_Ladder_Table,	CBackUp_Ladder_Table}
};


/*费率电价编程记录*/
#define	C_TB_ProgRateEvent_Len		24
const	ulong32	TB_ProgRateEvent[C_TB_ProgRateEvent_Len] =
{
	CCurrent_Rate1_Price,
	CCurrent_Rate2_Price,
	CCurrent_Rate3_Price,
	CCurrent_Rate4_Price,
	CCurrent_Rate5_Price,
	CCurrent_Rate6_Price,
	CCurrent_Rate7_Price,
	CCurrent_Rate8_Price,
	CCurrent_Rate9_Price,
	CCurrent_Rate10_Price,
	CCurrent_Rate11_Price,
	CCurrent_Rate12_Price,
	CBackUp_Rate1_Price,
	CBackUp_Rate2_Price,
	CBackUp_Rate3_Price,
	CBackUp_Rate4_Price,
	CBackUp_Rate5_Price,
	CBackUp_Rate6_Price,
	CBackUp_Rate7_Price,
	CBackUp_Rate8_Price,
	CBackUp_Rate9_Price,
	CBackUp_Rate10_Price,
	CBackUp_Rate11_Price,
	CBackUp_Rate12_Price
};
/****************************************************************************/
/*698兼容645增加*/
/*事件中参数延时，用于判断是延时标识，需要转换数据为十进制*/
#define	C_TB_EventDelayTime_Len 15
const	ulong32	TB_EventDelayTime[C_TB_EventDelayTime_Len] =
{
	CLossVolage_Delay_T,
	CLowVolage_Delay_T,
	COverVolage_Delay_T,
	CBreakVol_Delay_T,
	CNoBal_Vol_Delay_T,
	CNoBal_Curr_Delay_T,
	CSeriNoBal_Curr_Delay_T,
	CLossCurr_Delay_T,
	COverCurr_Delay_T,
	CTrendRev_Delay_T,
	COverLoad_Delay_T,
	CPosAcDemandOv_Delay_T,
	CPowerFactor_Delay_T,
	CPowerRev_Delay_T,
	CBreakCurr_Delay_T
};
#define	C_TB_EventParaSpecial_Len	10
const	ulong32	 TB_EventParaSpecial[C_TB_EventParaSpecial_Len] =
{
	CLossVolage_Curr_LowLim,
	CBreakVol_Curr_UpLim,
	CLossCurr_Curr_UpLim,
	CLossCurr_Curr_LowLim,
	CBreakCurr_Curr_UpLim,
	CTrendRev_AcPower_LowLim,
	COverLoad_AcPower_LowLim,
	CPosAcDemandOv_De_LowLim,
	CRevAcDemandOv_De_LowLim,
	CReDemandOv_De_LowLim,
};
/****************************************************************************/
/*698兼容645增加*/
const Str_ParaChange_OADToDI_Table Pstr_ParaChange[]=
{
/*		OAD						DI		*/
	{0x40000200,					0x0400010C					},
	{0x40080200,					0x04000106					},
	{0x40090200,					0x04000107					},
	{0x41160201,					0x04000B01					},
	{0x41160202,					0x04000B02					},
	{0x41160203,					0x04000B03					},
	{CYear_Zone_Num,				0x04000201					},
	{CDay_Table_Num,				0x04000202					},
	{CDay_Time_Num,					0x04000203					},
	{CRate_Num,						0x04000204					},
	{0x40140200,					0x04010000					},
	{0x40150200,					0x04020000					},
	{0x40160201,					0x04010001					},
	{0x40160202,					0x04010002					},
	{0x40160203,					0x04010003					},
	{0x40160204,					0x04010004					},
	{0x40160205,					0x04010005					},
	{0x40160206,					0x04010006					},
	{0x40160207,					0x04010007					},
	{0x40160208,					0x04010008					},
	{0x40170201,					0x04020001					},
	{0x40170202,					0x04020002					},
	{0x40170203,					0x04020003					},
	{0x40170204,					0x04020004					},
	{0x40170205,					0x04020005					},
	{0x40170206,					0x04020006					},
	{0x40170207,					0x04020007					},
	{0x40170208,					0x04020008					},
	{CMeter_Num,					0x04000402					},
	{CMeter_Work_State1,			0x04000501					}, 		/*电表运行状态字1*/
	{CMeter_Work_State2,			0x04000502					}, 		/*电表运行状态字2*/
	{CMeter_Work_State3,			0x04000503					}, 		/*电表运行状态字3*/
	{CMeter_Work_State4,			0x04000504					}, 		/*电表运行状态字4*/
	{CMeter_Work_State5,			0x04000505					}, 		/*电表运行状态字5*/
	{CMeter_Work_State6,			0x04000506					}, 		/*电表运行状态字6*/
	{CMeter_Work_State7,			0x04000507					}, 		/*电表运行状态字7*/
	{CComm_Address,					CComm_Address_645			},		/*通信地址*/
	{CSoftw_Record_Number,			CSoftw_Record_Number_645	},		/*软件备案号*/
	{COne485_Baud,					COne485_Baud_645			},		/*通信口1通信速率特征字*/
	{CTwo485_Baud,					CTwo485_Baud_645			},		/*通信口2通信速率特征字*/
	{CActive_Com_State,				CActive_Com_State_645		},
	{CReactive_Com_State1,			CReactive_Com_State1_645	},
	{CReactive_Com_State2,			CReactive_Com_State2_645	},
	{CRated_Vol,					CRated_Vol645         		},
	{CRated_Curr,					CRated_Curr645        		},
	{CMax_Curr,						CMax_Curr645          		},
	{CActive_Accur_Deg,				CActive_Accur_Deg645  		},
	{CReactive_Accur_Deg,			CReactive_Accur_Deg645		},
	{CMeter_Ac_Const,				CMeter_Ac_Const645    		},
	{CMeter_Re_Const,				CMeter_Re_Const645    		},
	{CMeter_Model,					CMeter_Model645       		},
	{CProd_Date,					CProd_Date645         		},
	{CManage_Code,					CManage_Code_645      		},
	{CLossVolage_Vol_UpLim		,	CLossVolage_Vol_UpLim_645	},
	{CLossVolage_Vol_LowLim		,   CLossVolage_Vol_LowLim_645	},
	{CLossVolage_Curr_LowLim	,	CLossVolage_Curr_LowLim_645	},
	{CLossVolage_Delay_T	    ,	CLossVolage_Delay_T_645	    },
	{CLowVolage_Vol_UpLim		,   CLowVolage_Vol_UpLim_645	},
	{CLowVolage_Delay_T	    	,   CLowVolage_Delay_T_645	    },
	{COverVolage_Vol_LowLim		,   COverVolage_Vol_LowLim_645	},
	{COverVolage_Delay_T	    ,	COverVolage_Delay_T_645	    },
	{CBreakVol_Vol_UpLim	    ,	CBreakVol_Vol_UpLim_645	    },
	{CBreakVol_Curr_UpLim		,   CBreakVol_Curr_UpLim_645	},
	{CBreakVol_Delay_T	    	,   CBreakVol_Delay_T_645	    },
	{CNoBal_Vol_Lim	        	,   CNoBal_Vol_Lim_645	        },
	{CNoBal_Vol_Delay_T	    	,   CNoBal_Vol_Delay_T_645	    },
	{CNoBal_Curr_Lim	        ,	CNoBal_Curr_Lim_645	        },
	{CNoBal_Curr_Delay_T	    ,	CNoBal_Curr_Delay_T_645	    },
	{CSeriNoBal_Curr_Lim	    ,	CSeriNoBal_Curr_Lim_645	    },
	{CSeriNoBal_Curr_Delay_T	,	CSeriNoBal_Curr_Delay_T_645	},
	{CLossCurr_Vol_LowLim		,   CLossCurr_Vol_LowLim_645	},
	{CLossCurr_Curr_UpLim		,   CLossCurr_Curr_UpLim_645	},
	{CLossCurr_Curr_LowLim		,   CLossCurr_Curr_LowLim_645	},
	{CLossCurr_Delay_T	    	,   CLossCurr_Delay_T_645	    },
	{COverCurr_Curr_LowLim		,   COverCurr_Curr_LowLim_645	},
	{COverCurr_Delay_T	    	,   COverCurr_Delay_T_645	    },
	{CBreakCurr_Vol_LowLim		,   CBreakCurr_Vol_LowLim_645	},
	{CBreakCurr_Curr_UpLim		,   CBreakCurr_Curr_UpLim_645	},
	{CBreakCurr_Delay_T	    	,   CBreakCurr_Delay_T_645	    },
	{CTrendRev_AcPower_LowLim	,   CTrendRev_AcPower_LowLim_645},
	{CTrendRev_Delay_T	    	,   CTrendRev_Delay_T_645	    },
	{COverLoad_AcPower_LowLim	,   COverLoad_AcPower_LowLim_645},
	{COverLoad_Delay_T	    	,   COverLoad_Delay_T_645	    },
	{CVolage_Check_UpLim	    ,	CVolage_Check_UpLim_645	    },
	{CVolage_Check_LowLim		,   CVolage_Check_LowLim_645	},
	{CPosAcDemandOv_De_LowLim	,   CAcDemandOv_De_LowLim_645	},
	{CReDemandOv_De_LowLim		,   CReDemandOv_De_LowLim_645	},
	{CPosAcDemandOv_Delay_T	    ,   CDemandOv_Delay_T_645	    },
	{CPowerFactor_LowLim	    ,	CPowerFactor_LowLim_645	    },
	{CPowerFactor_Delay_T		,  	CPowerFactor_Delay_T_645	},
	{CPowerRev_AcPower_LowLim	,  	CPowerRev_AcPower_LowLim_645},
	{CPowerRev_Delay_T       	,  	CPowerRev_Delay_T_645       },
	{0x40120200					,	0x04000801					},		/*周休日特征字*/
	{0x40130200					,	0x04000802					},		/*周休日采用日时段表号*/
	{0x41020200					,	0x04000105					},		/*校表脉冲宽度*/
	{0x400C0205					,	0x04000205					},		/*公共节假日数*/
	{0xF3000300					,	0x04000302					},		/*循显每屏显示时间*/
	{0x40070205					,	0x04000303					},		/*显示电能小数位数*/
	{0x40070206					,	0x04000304					},		/*显示功率小数位数*/
	{CMod_InFr_Baud				,	CMod_InFr_Baud_645			},		/*通信速率特征字调制红外*/
	{0x41120200					,	0x04000601					},		/*有功组合特征字*/
	{0x41130200					,	0x04000602					},		/*无功组合方式1特征字*/
	{0x41140200					,	0x04000603					},		/*无功组合方式2特征字*/
	{0xF3000401					,	0x04000301					},		/*循显当前总对象数*/
	{0xF3010401					,	0x04000305					},		/*键显当前总对象数*/
	{CDemand_Cycle				, 	CDemand_Cycle645			},
	{CSliding_Time				, 	CSliding_Time645			},
};
#define Pstr_ParaChange_Len  (sizeof(Pstr_ParaChange) / sizeof(Str_ParaChange_OADToDI_Table))

const Str_ParaChange_OADToDI_Table Pstr_ParaChange_TZone[]=
{
/*/  OAD         		DI        */
	{0x40140200,	0x04010000},
	{0x40150200,	0x04020000},
	{0x40160201,	0x04010001},
	{0x40160202,	0x04010002},
	{0x40160203,	0x04010003},
	{0x40160204,	0x04010004},
	{0x40160205,	0x04010005},
	{0x40160206,	0x04010006},
	{0x40160207,	0x04010007},
	{0x40160208,	0x04010008},
	{0x40170201,	0x04020001},
	{0x40170202,	0x04020002},
	{0x40170203,	0x04020003},
	{0x40170204,	0x04020004},
	{0x40170205,	0x04020005},
	{0x40170206,	0x04020006},
	{0x40170207,	0x04020007},
	{0x40170208,	0x04020008},
};
#define Pstr_ParaChange_TZone_Len  (sizeof(Pstr_ParaChange_TZone) / sizeof(Str_ParaChange_OADToDI_Table))


const Str_ParaChange_OADToDI_Table Pstr_ParaChange02[]=
{
	 /*  OAD         DI*/
	{CPhaseA_Volage,		0x02010100},/*A相电压*/
	{CPhaseB_Volage,		0x02010200},/*B相电压*/
	{CPhaseC_Volage,		0x02010300},/*C相电压*/
	{CPhaseA_Curr,			0x02020100},/*A相电流*/
	{CPhaseB_Curr,			0x02020200},/*B相电流*/
	{CPhaseC_Curr,			0x02020300},/*C相电流*/
	{CInstant_TolAcPow,		0x02030000},/*瞬时总有功功率*/
	{CInstantA_AcPow  ,		0x02030100},/*A相瞬时有功功率*/
	{CInstantB_AcPow  ,		0x02030200},/*B相瞬时有功功率*/
	{CInstantC_AcPow  ,		0x02030300},/*C相瞬时有功功率*/
	{CInstant_TolRePow, 	0x02040000},/*瞬时总无功功率*/
	{CInstantA_RePow  , 	0x02040100},/*A相瞬时无功功率*/
	{CInstantB_RePow  , 	0x02040200},/*B相瞬时无功功率*/
	{CInstantC_RePow  , 	0x02040300},/*C相瞬时无功功率*/
	{CInstant_TolAppaPow, 	0x02050000},/*瞬时总视在功率*/
	{CInstantA_AppaPow,   	0x02050100},/*瞬时A视在功率*/
	{CInstantB_AppaPow,   	0x02050200},/*瞬时B视在功率*/
	{CInstantC_AppaPow,   	0x02050300},/*瞬时C视在功率*/
	{CTol_PowerFactor, 		0x02060000},/*总功率因数*/
	{CPhaseA_PowerFactor, 	0x02060100},/*A功率因数*/
	{CPhaseB_PowerFactor, 	0x02060200},/*B功率因数*/
	{CPhaseC_PowerFactor, 	0x02060300},/*C功率因数*/
	{CZero_Current, 		0x02800001},/*零线电流*/
	{CElecNet_Freq, 		0x02800002},/*电网频率*/
	{CCurr_AcDemand, 		0x02800004},/*当前有功需量*/
	{CCurr_ReDemand, 		0x02800005},/*当前无功需量*/
	{CCloc_Batt_Vol, 		0x02800008},/*时钟电池电压*/
	{CReadMeter_Batt_Vol, 	0x02800009},/*抄表电池电压*/
	{CBatt_Work_Time, 		0x0280000A},/*内部电池工作时间*/
	{CPhaseA_Angle, 		0x02070100},/*A相相角*/
	{CPhaseB_Angle,       	0x02070200},/*B相相角*/
	{CPhaseC_Angle, 	    0x02070300},/*C相相角*/
};
#define Pstr_ParaChange02_Len  (sizeof(Pstr_ParaChange02) / sizeof(Str_ParaChange_OADToDI_Table))

const Str_ParaChange_OADToDI_Table Pstr_ParaChange_Event[Pstr_ParaChange_Event_Len]=
{
  {0x300D0100,			0x030500FF},  /*698-电能表全失压事件*/
  {0x300F0100,		    0x1400FFFF},  /*698-电能表电压逆相序事件*/
  {0x30110100,			0x031100FF},  /*698-电能表掉电事件*/
  {0x30120100,			0x033000FF},  /*698-电能表编程事件*/
  {0x43000500,			0xFFFFFFFF},  /*698-电能表清零事件*/
  {0x30140100,			0x033002FF},  /*698-电能表需量清零事件*/
  {0x30150100,	    	0x033003FF},  /*698-电能表事件清零事件*/
  {0x30160100,			0x033004FF},  /*698-电能表校时事件*/
  {0x301B0100,			0x03300DFF},  /*698-电能表开盖事件*/
  {0x301C0100,		    0x03300EFF},  /*698-电能表开端钮盖事件*/
  {0x301D0100,		    0x1600FFFF},  /*698-电能表电压不平衡事件*/
  {0x301F0100,			0x1D00FFFF},  /*698-电能表跳闸事件*/
  {0x30200100,			0x1E00FFFF},  /*698-电能表合闸事件*/
  {0x302A0100,			0x033500FF},  /*698-电能表恒定磁场干扰事件*/
  {0x302B0100,			0x033600FF},  /*698-电能表负荷开关误动作事件*/
  {0x302C0100,			0x033700FF},  /*698-电能表电源异常事件*/
  {0x30050100,          0x19FFFFFF},  /*698-过流*/
  {0x30000100,          0x10FFFFFF},  /*698-失压*/
  {0x30040100,          0x18FFFFFF},  /*698-失流*/
  {0x30010100,          0x11FFFFFF},  /*698-欠压*/
  {0x30020100,          0x12FFFFFF},  /*698-过压*/
  {0x30030100,          0x13FFFFFF},  /*698-断相*/
  {0x30070100,          0x1BFFFFFF},  /*698-潮流反向*/
  {0x30130100,          0x033001FF},  /*698-电表清零事件*/
  {0x30170100,          0x033005FF},  /*时段表编程事件*/
  {0x30180100,          0x033006FF},  /*时区表编程事件*/
  {0x301A0100,          0x03300CFF},  /*结算日编程*/
};
#define Pstr_ParaChange_Event_Len 27

const Str_DriveReport_Change Pstr_DriveReport_Change[]=
{
	/*645主动上报模式字bit，	 698中事件的OIB， 	698中上报标识对应的属性，	698中2015中的bit(不在2015中为NULL)*/
	{C_ReportMode645_Bit0,		 0x2B,				0x08,						C_NoChangeEvent},			/*负荷开关误动误动作*/
	{C_ReportMode645_Bit1,		 C_NoChangeEvent,	C_NoChangeEvent,		    C_Report698_2015_Bit1},		/*ESAM错误*/
	{C_ReportMode645_Bit2,		 C_NoChangeEvent,	C_NoChangeEvent,		    C_NoChangeEvent},			/*内卡初始化错误*/
	{C_ReportMode645_Bit3,		 C_NoChangeEvent,	C_NoChangeEvent,			C_Report698_2015_Bit3},		/*时钟电池电压低*/
	{C_ReportMode645_Bit4,		 C_NoChangeEvent,	C_NoChangeEvent,			C_NoChangeEvent},			/*内部程序错误*/
	{C_ReportMode645_Bit5,		 C_NoChangeEvent,	C_NoChangeEvent,			C_Report698_2015_Bit5},		/*存储器故障或损坏*/
	{C_ReportMode645_Bit6,		 C_NoChangeEvent,	C_NoChangeEvent,			C_NoChangeEvent},			/*保留*/
	{C_ReportMode645_Bit7,		 0x2E,				0x08,						C_NoChangeEvent},			/*时钟故障*/
	{C_ReportMode645_Bit8,		 C_NoChangeEvent,	C_NoChangeEvent,			C_Report698_2015_Bit8},		/*停电抄表电池欠压*/
	{C_ReportMode645_Bit9,		 C_NoChangeEvent,	C_NoChangeEvent,			C_Report698_2015_Bit9},		/*透支状态*/
	{C_ReportMode645_Bit10,		 0x1B,				0x08,						C_NoChangeEvent},			/*开表盖*/
	{C_ReportMode645_Bit11,		 0x1C,				0x08,						C_NoChangeEvent},			/*开端钮盖*/
	{C_ReportMode645_Bit12,		 0x2A,				0x08,						C_NoChangeEvent},			/*恒定磁场干扰*/
	{C_ReportMode645_Bit13,		 0x2C,				0x08,						C_NoChangeEvent},			/*电源异常*/
	{C_ReportMode645_Bit14,		 C_NoChangeEvent,	C_NoChangeEvent,			C_Report698_2015_Bit14},	/*跳闸成功*/
	{C_ReportMode645_Bit15,		 C_NoChangeEvent,	C_NoChangeEvent,			C_Report698_2015_Bit15},	/*合闸成功*/
	{C_ReportMode645_Bit16,		 0x00,				0x0B,						C_NoChangeEvent},			/*失压*/
	{C_ReportMode645_Bit17,		 0x01,				0x0B,						C_NoChangeEvent},			/*欠压*/
	{C_ReportMode645_Bit18,		 0x02,				0x0B,						C_NoChangeEvent},			/*过压*/
	{C_ReportMode645_Bit19,		 0x04,				0x0B,						C_NoChangeEvent},			/*失流*/
	{C_ReportMode645_Bit20,		 0x05,				0x0B,						C_NoChangeEvent},			/*过流*/
	{C_ReportMode645_Bit21,		 0x08,				0x0B,						C_NoChangeEvent},			/*过载*/
	{C_ReportMode645_Bit22,		 0x07,				0x0B,						C_NoChangeEvent},			/*功率反向*/
	{C_ReportMode645_Bit23,		 0x03,				0x0B,						C_NoChangeEvent},			/*断相*/
	{C_ReportMode645_Bit24,		 0x06,				0x0B,						C_NoChangeEvent},			/*断流*/
	{C_ReportMode645_Bit25,		 C_NoChangeEvent,	C_NoChangeEvent,			C_NoChangeEvent},			/*保留*/
	{C_ReportMode645_Bit26,		 C_NoChangeEvent,	C_NoChangeEvent,			C_NoChangeEvent},			/*保留*/
	{C_ReportMode645_Bit27,		 C_NoChangeEvent,	C_NoChangeEvent,			C_NoChangeEvent},			/*保留*/
	{C_ReportMode645_Bit28,		 C_NoChangeEvent,	C_NoChangeEvent,			C_NoChangeEvent},			/*保留*/
	{C_ReportMode645_Bit29,		 C_NoChangeEvent,	C_NoChangeEvent,			C_NoChangeEvent},			/*保留*/
	{C_ReportMode645_Bit30,		 C_NoChangeEvent,	C_NoChangeEvent,			C_NoChangeEvent},			/*保留*/
	{C_ReportMode645_Bit31,		 C_NoChangeEvent,	C_NoChangeEvent,			C_NoChangeEvent},			/*保留*/
	{C_ReportMode645_Bit32,		 0x0F,				0x08,						C_NoChangeEvent},			/*电压逆相序*/
	{C_ReportMode645_Bit33,		 0x10,				0x08,						C_NoChangeEvent},			/*电流逆相序  */
	{C_ReportMode645_Bit34,		 0x1D,				0x08,						C_NoChangeEvent},			/*电压不平衡 */
	{C_ReportMode645_Bit35,		 0x1E,				0x08,						C_NoChangeEvent},			/*电流不平衡 */
	{C_ReportMode645_Bit36,		 0x0E,				0x08,						C_NoChangeEvent},			/*辅助电源失电*/
	{C_ReportMode645_Bit37,		 0x11,				0x08,						C_NoChangeEvent},			/*掉电*/
	{C_ReportMode645_Bit38,		 C_NoChangeEvent,	C_NoChangeEvent,			C_NoChangeEvent},			/*需量超限  698分为正向3009、反向300A、无功300B */
	{C_ReportMode645_Bit39,		 0x0C,				0x08,						C_NoChangeEvent},			/*总功率因数超下限 */
	{C_ReportMode645_Bit40,		 0x2D,				0x08,						C_NoChangeEvent},			/*电流严重不平衡 */
	{C_ReportMode645_Bit41,		 C_NoChangeEvent,	C_NoChangeEvent,			C_NoChangeEvent},			/*潮流反向 698潮流反向做在功率反向里*/
	{C_ReportMode645_Bit42,		 0x0D,				0x08,						C_NoChangeEvent},			/*全失压*/
	{C_ReportMode645_Bit43,		 C_NoChangeEvent,	C_NoChangeEvent,			C_NoChangeEvent},			/*保留*/
	{C_ReportMode645_Bit44,		 C_NoChangeEvent,	C_NoChangeEvent,			C_NoChangeEvent},			/*保留*/
	{C_ReportMode645_Bit45,		 C_NoChangeEvent,	C_NoChangeEvent,			C_NoChangeEvent},			/*保留*/
	{C_ReportMode645_Bit46,		 C_NoChangeEvent,	C_NoChangeEvent,			C_NoChangeEvent},			/*保留 */
	{C_ReportMode645_Bit47,		 C_NoChangeEvent,	C_NoChangeEvent,			C_NoChangeEvent},			/*保留*/
	{C_ReportMode645_Bit48,		 0x12,				0x08,						C_NoChangeEvent},			/*编程  */
	{C_ReportMode645_Bit49,		 0x13,				0x08,						C_NoChangeEvent},			/*电表清零*/
	{C_ReportMode645_Bit50,		 0x14,				0x08,						C_NoChangeEvent},			/*需量清零*/
	{C_ReportMode645_Bit51,		 0x15,				0x08,						C_NoChangeEvent},			/*事件清零*/
	{C_ReportMode645_Bit52,		 0x16,				0x08,						C_NoChangeEvent},			/*校时*/
	{C_ReportMode645_Bit53,		 0x17,				0x08,						C_NoChangeEvent},			/*时段表编程*/
	{C_ReportMode645_Bit54,		 0x18,				0x08,						C_NoChangeEvent},			/*时区表编程*/
	{C_ReportMode645_Bit55,		 0x19,				0x08,						C_NoChangeEvent},			/*周休日编程*/
	{C_ReportMode645_Bit56,		 0x21,				0x08,						C_NoChangeEvent},			/*节假日编程*/
	{C_ReportMode645_Bit57,		 0x22,				0x08,						C_NoChangeEvent},			/*有功组合方式编程*/
	{C_ReportMode645_Bit58,		 C_NoChangeEvent,	C_NoChangeEvent,			C_NoChangeEvent},			/*无功组合方式1编程 698只有无功组合方式编程*/
	{C_ReportMode645_Bit59,		 C_NoChangeEvent,	C_NoChangeEvent,			C_NoChangeEvent},			/*无功组合方式2编程*/
	{C_ReportMode645_Bit60,		 0x1A,				0x08,						C_NoChangeEvent},			/*结算日编程*/
	{C_ReportMode645_Bit61,		 0x24,				0x08,						C_NoChangeEvent},			/*费率参数表编程*/
	{C_ReportMode645_Bit62,		 0x25,				0x08,						C_NoChangeEvent},			/*阶梯表编程*/
	{C_ReportMode645_Bit63,		 0x26,				0x08,						C_NoChangeEvent},			/*密钥更新*/
};

#define Pstr_DriveReport_ChangeLen  (sizeof(Pstr_DriveReport_Change) / sizeof(Str_DriveReport_Change))

const ulong32 TB_ChannelOAD[]=		/*上报通道*/
{
	{COne485_Baud},
	{CTwo485_Baud},
	{C485_Baud_Gather},
	{CModular_Baud},
	{CModular_Baud_Gather},
};
#define TB_ChannelOADLen ( sizeof(TB_ChannelOAD) / sizeof(ulong32) )

/***************************************************************************
函数原型 	INF_Comm_ForPowerOn
函数功能	通信模块上电初始化接口函数
输入参数	无

输出参数 	无
返回参数	无
全局变量 	SV_Comm_Parse/SV_Comm_Parse_Local
函数备注
***************************************************************************/
void INF_Comm_ForPowerOn(void)
{
	uchar8	buf[C_TimerExceed10minLen];
	uchar8	PowerOffClock[CLEnter_LowPower_Time];
	uchar8	PowerOnClock[CLEnter_LowPower_Time];
	ulong32	PowerOffDUR_Min;						/*电源掉电持续时间，单位为min*/
	ulong32	PowerOffDUR_5Min;
	ushort16	DataLen, V_usDataEncode;
	uchar8	V_ReturnData;
	uchar8	V_ReturnData1;
    uchar8 V_ucBuffer[7];

/*初始化各串口及对应的通道交互变量*/
	InF_InitComm(C_RS485_1);
	InF_InitComm(C_RS485_2);
	InF_InitComm(C_Module);
	InF_InitComm(C_IR);

/*初始化后续帧变量*/
	Init_SV_CommNxtFrame(C_RS485_1);
	Init_SV_CommNxtFrame(C_RS485_2);
	Init_SV_CommNxtFrame(C_Module);
	Init_SV_CommNxtFrame(C_IR);

/*触发密钥检查消息*/
	Comm_A_MsgToDispatchQueue_UpKeyR(PT_CMsg_UpdKey_Rv_PWOn);

/*初始化静态全局变量SV_Comm_Parse_Local*/
	Comm_ParseInit();

/*初始化静态全局变量SV_Comm_Parse*/
/*初始化SPTVariable*/
	Comm_DealwithSPTVariable(C_InitSPTVariable);
/*初始化安全认证、红外认证有效定时器*/
	memset( buf,0, C_TimerExceed10minLen );
	DealWith_ID_Auth_Timer(C_Set_TimerExceed10min, &buf[0]);
	DealWith_IR_Auth_Timer(C_Set_TimerExceed10min, &buf[0]);
	DealWith_ID_Auth_T_Timer(C_Set_TimerExceed10min, &buf[0]);
	DealWith_IR_Auth_Timer_645(C_Set_TimerExceed10min, &buf[0]);
/*计算停电持续时间*/
	DataLen = CLEnter_LowPower_Time;
	V_ReturnData = InF_Read_Data(CEnter_LowPower_Time,PowerOffClock, &DataLen, &V_usDataEncode);
	V_ReturnData1 = InF_Read_Data(CExit_LowPower_Time,PowerOnClock, &DataLen, &V_usDataEncode);
	if( ( V_ReturnData == C_OK )&&( V_ReturnData1 == C_OK ) )
	{
		V_ReturnData = PF_TimeSub_Min_698(PowerOffClock, PowerOnClock, &PowerOffDUR_Min);
		if( V_ReturnData == C_LessThan )
		{
			PowerOffDUR_5Min = PowerOffDUR_Min/5;	/* 1min定时,转成5min基本节拍*/
		}
		else
		{
			PowerOffDUR_5Min = 0;
			PowerOffDUR_Min = 0;
		}
	}
	else
	{												/*进出低功耗时间有一个读不出，则扣减0.*/
		PowerOffDUR_5Min = 0;
		PowerOffDUR_Min = 0;
	}
/*初始化软IJ有效时间定时器，处理函数中会判断定时器有效才扣减*/
/*软IJ剩余时间初始化*/
	V_ucBuffer[0] = SI_JT_BaseTimer;
	PF_Ulong32ToBuffer4(&V_ucBuffer[1], &SI_JT_Timer, C_TimerExceed10minLen);
	PF_Ushort16ToBuffer2(&V_ucBuffer[C_Timer_Base_10minLen], &SI_JT_Crc);
	if( PF_Check_CRC(V_ucBuffer,C_SI_JTimerHaveCRC_Len) != C_OK )
	{
		DataLen = CLSoftI_J_RemainTime;
		if( InF_Read_Data(CSoftI_J_RemainTime, &V_ucBuffer[1], &DataLen, &V_usDataEncode) != C_OK )
		{
			memset(&V_ucBuffer[1], 0x00, C_TimerExceed10minLen);
		}
		PF_Buffer4ToUlong32(&V_ucBuffer[1], &SI_JT_Timer,C_TimerExceed10minLen);
		SI_JT_BaseTimer = 0;
		V_ucBuffer[0]=SI_JT_BaseTimer;
		SI_JT_Crc = PF_Cal_CRC(V_ucBuffer,C_SI_JTimer_Len);
	}
    DataLen = 4;
	PF_HextoBCDBytes(&PowerOffDUR_5Min, buf, (uchar8 *)&DataLen);
	DealWith_SI_J_Timer(C_Sub_TimerExceed10min,buf);

/*判断已上报定时器停电消耗了多少?暂时不管。*/

	SV_Comm_Parse.Timer_1min = 0;										/*重新定时*/
	InF_UpdateAccountStateInMeterStatus3();

/*RstModuleParm初始化*/
	DealWith_RstModule(C_Flag_Ok);

/*上电初始化插卡状态字为未知*/
	InF_WriteCardStatus(C_CardStatusUnknow);
/*上电初始化主动上报未确认1s定时器    */
	InF_JudgeESAMConTimer(C_PowerUpDealConectTime, Termal_Address);      /*上电清零*/
	InF_JudgeESAMConTimer(C_PowerUpDealConectTime, Master_Address);      /*上电清零*/

	Inf_Comm_ClearModuleCommuniFlag(0);         						/*通信标识清零*/
	Inf_Comm_REPORTFlagClear(0);                						/*主动上报清零*/
	Inf_DealEventReportShut(C_ReportInit);      						/*其他事件的主动上报延时定时器，上电后闭锁*/

	Inf_Event_REPORTONumDeal(0);                						/*上电初始化，清掉电次数*/
}

/***************************************************************************
函数原型 	void INF_Comm_RecForInt
函数功能	中断接收服务程序(将接收到的数据放置到通信缓存，并判断是否一帧接收完毕)
输入参数	CommNo		串口号
				RecData		接收到正确的数据
输出参数
返回参数	C_ContinueReceive:		继续接收

				C_CorrectFrame:		接收到正确的帧。需调度触发通信解析消息(参数为通道号)
									同时调度需要关闭接收。
全局变量 	Str_Comm_Parm型变量
函数备注	1、见返回参数注释
				2、调度调用时，如果是中断一次能接收到多字节，请循环调用本函数；
***************************************************************************/
#define C_ContralWord_645_Len	18
const	uchar8 C_ContralWord_645[C_ContralWord_645_Len] =
{
	0x11, 0x14, 0x03, 0x12, 0x13, 0x15, 0x16, 0x18, 0x08, 0x19, 0x1A, 0x1B, 0x1C, 0x21, 0x20, 0x1E, 0x1F, 0x17
};
uchar8	INF_Comm_RecForInt(uchar8 CommNo, uchar8 RecData)
{
	Str_Comm_Parm	*pStr_Comm_Parm_Address;
	ushort16	V_LenTemp;
	uchar8 i;
    uchar8 V_ucReturn = C_AbortReceive;

/*如果通道错了怎么办?现在直接退出*/
	pStr_Comm_Parm_Address = Get_Str_Comm_Parm_Pointer(CommNo);
	if(pStr_Comm_Parm_Address == C_NULL)
	{
		return(C_ContinueReceive);
	}
/*只要通道正确，我们就将超时关闭。通过协议准确接收*/
	CommOTimer = 0;
	if(CommOffset >= C_FramePartMaxLen)
	{
		return(C_AbortReceive);									/*直接不再接收*/
	}
/*判断是否处于准备接收第1个68*/
	if(CommOffset == C_68_1_OFS_ForRx)
	{
		if(RecData ==0x68)
		{
			CommBuff[CommOffset] = RecData;
			CommOffset++;
			CommRecFlag = CommRecFlag | C_First68_Ok; 			/*698协议，第一个0x68*/
			CommProtocolType = 0;
			CommRecFlag645 = CommRecFlag645 | C_First68_Ok;		/*645协议，第一个0x68*/
			CommProtocolType645 = 0;
		}
		return(C_ContinueReceive);
	}
	if(CommOffset < C_FramePartValueLen)						/*长度小于512字节的时候直接接收*/
	{
		CommBuff[CommOffset] = RecData;
		CommOffset++;
		if((CommOffset >= 11))
		{
/*********************645帧判断**********************/
				if(CommBuff[C_68_2_OFS_ForRx] == 0x68)
				{
					/******************************************/
					CommRecFlag645 = CommRecFlag645 | C_Second68_Ok;
					V_LenTemp = CommBuff[C_L_OFS_ForRx];
					V_LenTemp += C_Comm_FixedRxLen;
					if(V_LenTemp <= 220)						/*645长度不大于220字节*/
					{
						if(V_LenTemp == CommOffset)				/*长度等于offset*/
						{
							if(RecData == 0x16)
							{
								if( ( CommBuff[C_C_OFS_ForRx] & 0xC0 ) == 0 )
								{
									for( i = 0; i < C_ContralWord_645_Len; i++ )
									{
										if( ( C_ContralWord_645[i] ) == CommBuff[C_C_OFS_ForRx] )
										{
											break;
										}
									}
									if( i >= C_ContralWord_645_Len )
									{
										CommProtocolType645 = C_ProtocolType_NOT645;
									}
									else
									{
								/****************判断通信地址**************/
										for( i = 0; i < CLComm_Address; i++ )
										{
											if( CommBuff[C_CAddr_OFS_ForRx + i] != SV_Comm_Address[i] )
											{
												break;
											}
										}
										for( ; i < CLComm_Address; i++ )
										{
											if( CommBuff[C_CAddr_OFS_ForRx + i] != 0xAA )		/*不是统配*/
											{
												break;
											}
										}
										if(i < CLComm_Address)
										{
											for( i = 0; i < CLComm_Address; i++ )
											{
												if(CommBuff[C_CAddr_OFS_ForRx + i] != 0x99)		/*不是广播*/
												{
													break;
												}
											}
										}
										if(i < CLComm_Address)
										{
											CommProtocolType645 = C_ProtocolType_NOT645;
										}
										else
										{
											CommRecFlag645 = CommRecFlag645 | C_Len_Ok | C_16_Ok;
											if( Cal_645CS_CommRec( &CommBuff[C_68_1_OFS_ForRx],(C_Comm_FixedRxLen - C_CLenCS16_645 + CommBuff[C_L_OFS_ForRx]) )
											   != CommBuff[C_Data_OFS_ForRx + CommBuff[C_L_OFS_ForRx]] )
											{
												CommProtocolType645 = C_ProtocolType_NOT645;
											}
											else
											{
												CommRecFlag645 |= C_CS_Ok;
												CommProtocolType645 = C_ProtocolType_645;
												CommLen645 = V_LenTemp;
											}
										}
									}
								}
								else
								{
									CommProtocolType645 = C_ProtocolType_NOT645;
								}
							}
							else
							{
								CommProtocolType645 = C_ProtocolType_NOT645;
							}
						}
						else if(V_LenTemp < CommOffset)
						{
							CommProtocolType645 = C_ProtocolType_NOT645;
						}
						else
						{
							for( i = 0; i < C_ContralWord_645_Len; i++ )
							{
								if( ( C_ContralWord_645[i] ) == CommBuff[C_C_OFS_ForRx] )
								{
									break;
								}
							}
							if( i >= C_ContralWord_645_Len )
							{
								CommProtocolType645 = C_ProtocolType_NOT645;
							}
							else
							{
                                ;/*未判断明确，继续接收*/
							}
						}
					}
					else
					{
						CommProtocolType645 = C_ProtocolType_NOT645;
					}
				}
				else
				{
					CommProtocolType645 = C_ProtocolType_NOT645;
				}

/*************************如果到这里，判断是否完整的698*************************************************************/
			if( ( CommRecFlag & ( C_First68_Ok | C_Second68_Ok ) ) != ( C_First68_Ok | C_Second68_Ok ) )	/*地址没有判断过*/
			{
				CommAddrLen = ( CommBuff[C_AF_OFFSet_698] & 0x0F ) + 1;										/*ADDR地址长度*/
				if( CommOffset < ( CommAddrLen + 8 ) )
				{
					V_LenTemp =  CommBuff[C_LH_OFFSet_698];
					V_LenTemp <<= 8;
					V_LenTemp |= (ushort16)CommBuff[C_LL_OFFSet_698];										/*帧长度*/
					if( ( V_LenTemp > C_FramePartMaxLen )													/*长度不对*/
					 || ( ( CommBuff[ C_C_OFFSet_698] & 0x07 ) != 0x03 ) )									/*控制字不对*/
					{
                        CommProtocolType = C_ProtocolType_NOT698;
					}
					else
					{
                        ;
					}
				}
				else
				{
					if(PF_Check_CRC_698_CommRec( &CommBuff[C_LL_OFFSet_698], ( CommAddrLen + 7 ) ) == C_OK )
					{
						/****************判断通信地址**************/
						if( ( CommBuff[C_AF_OFFSet_698] & 0xC0 ) == 0xC0 )			/*广播地址*/
						{
							for( i = 0; i < CommAddrLen; i++ )
							{
								if( CommBuff[C_AddressFirst_698 + i] != 0xAA )
								{
									break;
								}
							}
						}
						else
						{
							for( i = 0 ; i < CommAddrLen; i++ )
							{
								if( ( ( ( CommBuff[C_AddressFirst_698 + i] & 0xF0 ) != (SV_Comm_Address[i] & 0xF0 ) )
								   && ( ( CommBuff[C_AddressFirst_698 + i] & 0xF0 ) != 0xA0 ) )
								 || ( ( ( CommBuff[C_AddressFirst_698 + i] & 0x0F ) != ( SV_Comm_Address[i] & 0x0F ) )
								   && ( ( CommBuff[C_AddressFirst_698 + i] & 0x0F ) != 0x0A ) ) )
								{
									break;
								}
							}
						}
						if( i == CommAddrLen )
						{
							CommRecFlag = CommRecFlag | C_Second68_Ok;				/*第二个68或者帧头校验码正确*/

							V_LenTemp =  CommBuff[C_LH_OFFSet_698];
							V_LenTemp <<= 8;
							V_LenTemp |= (ushort16)CommBuff[C_LL_OFFSet_698];		/*帧长度*/
							if( V_LenTemp <= ( C_FramePartValueLen - 2 ) )
							{
								CommLen = V_LenTemp + 2;							/*帧头68+帧尾16*/
								CommRecFlag = CommRecFlag | C_Len_Ok;
							}
						}
                        else
                        {
                            CommProtocolType = C_ProtocolType_NOT698;
                        }
					}
					else
					{
                        CommProtocolType = C_ProtocolType_NOT698;
					}
				}
			}
			else/*地址已经判断过 */
			{
                if(CommOffset == CommLen)
                {
					CommRecFlag = CommRecFlag | C_CS_Ok;
					if(RecData == 0x16)
					{
						CommRecFlag = CommRecFlag | C_16_Ok;
						CommProtocolType = C_ProtocolType_698;				/*确定是698*/
					}
					else
					{
						CommProtocolType = C_ProtocolType_NOT698;			/*确定不是698*/
					}

                }
				else  if( ( CommOffset - C_First68_OFFSet_698 ) > CommLen )
				{
					CommProtocolType = C_ProtocolType_NOT698;				/*确定不是698*/
				}
                else
                {
                    ;/*未判断，继续接收*/
                }
			}
            if( ( CommProtocolType == C_ProtocolType_NOT698 ) && ( CommProtocolType645 == C_ProtocolType_NOT645 ) )		/*不是698也不是645*/
            {
                for( i = 1; i < CommOffset; i++)
				{
					if(CommBuff[i] == 0x68)
					{
						break;
					}
				}
				if(i < CommOffset)					/*有帧头干扰，找下一个0x68，并移位*/
				{
                    memmove(&CommBuff[C_First68_OFFSet_698], &CommBuff[i], CommOffset);
                    CommOffset -= i;
                    CommProtocolType = C_ProtocolType_Init;
                    CommProtocolType645 = C_ProtocolType_Init;
                    V_ucReturn = C_ContinueReceive;							/*继续接收*/
				}
                else								/*后面没有0x68*/
                {
                    CommProtocolType = C_ProtocolType_NOT698;
                    CommProtocolType645 = C_ProtocolType_NOT645;
                    V_ucReturn = C_AbortReceive;	/*不是645也不是698，不再接收*/
                }
            }
            else if( ( CommProtocolType == C_ProtocolType_698 ) || ( CommProtocolType645 == C_ProtocolType_645 ) )		/*确定是698或者是645*/
            {
                V_ucReturn = C_CorrectFrame;		/*在正确帧*/
            }
            else
            {
                V_ucReturn = C_ContinueReceive;		/*未判断，继续接收*/
            }

		}
		else
		{
            V_ucReturn = C_ContinueReceive;			/*未判断，继续接收*/
		}
	}
    return V_ucReturn;
}

/***************************************************************************
函数原型 	INF_Comm_TxdForInt
函数功能	串口发送中断服务程序
输入参数	CommNum:		串口号取值：第1路485；第2路485；红外；模块
				p_TxdData:		待发送数据的指针
输出参数 	*p_TxdData		待发送的数据
返回参数	C_ContinueTransmit: 	继续发送
				C_AbortTransmit:		退出发送
全局变量
函数备注	注意这里最后1个字节0x16发送时应继续返回C_ContinueTransmit
				发送完16，再次进入中断，才返回C_AbortTransmit，要求调度初始化串口
***************************************************************************/
uchar8 INF_Comm_TxdForInt(uchar8 CommNum, uchar8	*p_TxdData)
{
	uchar8	V_ReturnData = C_AbortTransmit;
	Str_Comm_Parm	*pStr_Comm_Parm_Address;

	if(SV_SetBPS_Flag == C_OK)
	{
		V_ReturnData = C_AbortTransmit_SetBPS;
	}
/*如果通道错了怎么办?现在直接退出*/
	pStr_Comm_Parm_Address = Get_Str_Comm_Parm_Pointer(CommNum);
	if(pStr_Comm_Parm_Address == C_NULL)
	{
		return(C_AbortTransmit);					/*这种情况应该是不可能出现的。*/
	}
/*只要通道正确，我们就将超时关闭。通过协议准确接收*/
	CommOTimer = 0;

/*判断缓冲区的长度是否合理*/
    if(CommProtocolType == C_ProtocolType_698)
    {
        if(CommLen >= C_FramePartMaxLen)
		{
			CommLen = 0;
			CommOffset = 0;
			CommRecFlag = 0;
			CommOTimer = 0;
            CommProtocolType = C_ProtocolType_Init;
			return(V_ReturnData);					/*长度不合理，退出发送。应该是不可能发生的。*/
		}
/*判断有没有发送完成。最后16也发送了，则退出发送。*/
        if(CommOffset >= CommLen)
		{
			CommLen = 0;
			CommOffset = 0;
			CommRecFlag = 0;
			CommOTimer = 0;
            CommProtocolType = C_ProtocolType_Init;
			return(V_ReturnData);					/*发送完成*/
		}
    }
    if(CommProtocolType645 == C_ProtocolType_645)
    {
        if(CommLen645 >= C_FramePartMaxLen)
        {
			CommLen645 = 0;
			CommOffset = 0;
			CommRecFlag645 = 0;
			CommOTimer = 0;
            CommProtocolType645 = C_ProtocolType_Init;
			return(V_ReturnData);					/*长度不合理，退出发送。应该是不可能发生的。*/
        }
        if(CommOffset >= CommLen645)
        {
			CommLen645 = 0;
			CommOffset = 0;
			CommRecFlag645 = 0;
			CommOTimer = 0;
            CommProtocolType645 = C_ProtocolType_Init;
			return(V_ReturnData);					/*发送完成*/
        }
    }
/*发送数据*/
	*p_TxdData = CommBuff[CommOffset];
	(CommOffset)++;
	return(C_ContinueTransmit);

}
/*******************************************************************************
函数原型： void Inf_CalReportCRC(void)
功能描述： 上报结构体算CRC
输入参数：
输出参数：
返回参数：
调用位置：
备    注：
*******************************************************************************/
void Inf_CalReportCRC(void)
{
    SF_Deal_ReportCRC(C_CountCRC);
}
/*******************************************************************************
函数原型： uchar8 INF_Comm_TxdForInt_698Report(uchar8 CommNum,uchar8	*p_TxdData)
功能描述： 串口发送中断服务程序(上报）
输入参数：CommNum:		串口号取值：第1路485；第2路485；红外；模块
	      p_TxdData:		待发送数据的指针
输出参数：*p_TxdData		待发送的数据
返回参数： C_ContinueTransmit: 	继续发送
		  C_AbortTransmit:		退出发送
调用位置：
备    注： 注意这里最后1个字节0x16发送时应继续返回C_ContinueTransmit
				发送完16，再次进入中断，才返回C_AbortTransmit，要求调度初始化串口
*******************************************************************************/
uchar8 INF_Comm_TxdForInt_698Report(uchar8 CommNum,uchar8	*p_TxdData)
{
	uchar8	V_ReturnData = C_AbortTransmit;

    SV_SetBPS_Flag = C_Error;				/*默认不是设置BPS*/

/*判断缓冲区的长度是否合理*/
	if( SV_ReportSend.ReportLen > ( C_FramePartMaxLen + C_Comm_FixedTxLen ) )
	{
		SV_ReportSend.ReportLen = 0;
		SV_ReportSend.ReportOffset = 0;
		Inf_CalReportCRC();
		return(V_ReturnData);				/*长度不合理，退出发送。应该是不可能发生的*/
	}

/*判断有没有发送完成。最后16也发送了，则退出发送。	*/
	if(SV_ReportSend.ReportOffset >= SV_ReportSend.ReportLen)
	{
		SV_ReportSend.ReportLen = 0;
		SV_ReportSend.ReportOffset = 0;
		Inf_CalReportCRC();
		return(V_ReturnData);				/*发送完成*/
	}

/*发送数据*/
	*p_TxdData = SV_REPORTCommBuff[SV_ReportSend.ReportOffset];
	(SV_ReportSend.ReportOffset)++;
	Inf_CalReportCRC();
	return(C_ContinueTransmit);
}
/***************************************************************************
函数原型 	INF_WrClearAllRecord
函数功能	完成总清事件记录并进行数据层总清，总清主动上报。
输入参数	*pOpCode				:操作者代码(固定为4字节)
				SafeFlag				:安全字节，一路带到数据层
输出参数 	无
返回参数	C_OK/C_Error
全局变量
函数备注	注意，这里总清分厂内模式厂外模式。
				厂内，不进行总清记录，且数据层清零和厂外有微小区别
***************************************************************************/
uchar8 INF_WrClearAllRecord (uchar8 *pOpCode, uchar8	SafeFlag)
{
	uchar8	FactoryType = C_FactoryOutType;
	Str_Comm_645	V_645Frame = {0};

/*安全流程字节判断*/
	if( SafeFlag != C_ClearMeterSafeFlag )
	{
		return(C_Error);
	}
/*厂内模式，不管是什么密级清零，都不进总清事件记录。因为厂内模式是*/
	if( JudgeTimerExceed10min(&SI_JTimer_BSOn2500) != C_TimerEnable )
	{
		Have_IPEvent_Prog_698(CTol_Clear_Note_1, CTol_Clear_Degree, &V_645Frame);
	}
	else
	{
		FactoryType = C_FactoryInType;
	}
/*调用数据层的总清函数*/
	InF_Total_Clear(C_Msg_Communication, FactoryType,SafeFlag);
/*将RAM中编程记录清零*/
	INF_Init_Str_ProgRecord(&SV_Comm_Parse.ProgRecord);
	INF_Init_Str_ProgRecord_645(&SV_Comm_Parse.ProgRecord_645);
	Init_SV_ReportNewAddNum();							/*电表清零主动上报处理*/
	Init_SV_HaveReportState();							/*电表清零首先全部复位主动上报，重新判断有故障再次上报*/
	if(FactoryType == C_FactoryOutType)					/*厂外才上报*/
    {
      InF_ActiveReportSetting(C_Times_MeterClear);		/*电表清零主动上报。函数会判私钥才上报*/
    }
    else
    {
      ;/*厂内公钥和私钥都不用上报*/
    }

	Inf_ReportList(C_ReportChannelAll,C_TolClearEventNo,C_NewReport);	/*跟随上报*/
    Inf_EventReport_HP(C_TolClearEventNo,C_NewReport);
    Inf_CleanAllMeterStatus8();
	return C_OK;
}
/***************************************************************************
函数原型 	INF_Init_Str_ProgRecord
函数功能	初始化编程记录全局静态变量
输入参数	pProgRecord		:需初始化的编程变量指针

输出参数 	*pProgRecord		:初始化后的数据
返回参数	无
全局变量 	SV_Comm_Parse.ProgRecord
函数备注	pProgRecord	此指针就是全局静态变量指针。
功能说明
				1、	SV_Comm_Parse. ProgRecord.Opclock为全0
				2、	SV_Comm_Parse. ProgRecord.OpCode为全FF
				3、	SV_Comm_Parse. ProgRecord.DI为全FF
				4、	计算CRC
***************************************************************************/
void INF_Init_Str_ProgRecord (Str_ProgRecord		*pProgRecord)
{
	uchar8	i;
	uchar8	j;
	uchar8	Progbuf[70];		/*6+4+40+2=52*/
	uchar8	*pProgbufDI;

	for( i = 0; i < 19; i++ )
	{/*编程时间清零*/
		Progbuf[ProgOpClock_O + i] = 0x00;
		ProgOpClock[i] = Progbuf[ProgOpClock_O + i] ;
	}

	pProgbufDI = &Progbuf[ProgDI_O];
	for( i = 0; i < 10; i++ )
	{/*DI 全FF*/
		for( j = 0; j < CLProgTypeOADGather; j++ )
		{
			*pProgbufDI = 0xFF;
			ProgDI[i][j] = *pProgbufDI;
			pProgbufDI++;
		}
	}
	ProgCrc = PF_Cal_CRC(Progbuf, ProgCrc_O);
}

/***************************************************************************
函数原型 	INF_Init_Str_ProgRecord
函数功能	初始化编程记录全局静态变量
输入参数	pProgRecord		:需初始化的编程变量指针

输出参数 	*pProgRecord		:初始化后的数据
返回参数	无
全局变量 	SV_Comm_Parse.ProgRecord
函数备注	pProgRecord	此指针就是全局静态变量指针。
功能说明
				1、	SV_Comm_Parse. ProgRecord.Opclock为全0
				2、	SV_Comm_Parse. ProgRecord.OpCode为全FF
				3、	SV_Comm_Parse. ProgRecord.DI为全FF
				4、	计算CRC
***************************************************************************/
#define	ProgOpClock_O_645	0
#define	ProgOpCode_O_645	7
#define	ProgDI_O_645		11
#define	ProgCrc_O_645		51
void INF_Init_Str_ProgRecord_645 (Str_ProgRecord_645	*pProgRecord_645)
{
	uchar8	i, j;
	uchar8	Progbuf[53];		/*6+4+40+2=52*/
	uchar8	*pProgbufDI;

    /*编程时间清零*/
    memset(&Progbuf[ProgOpClock_O_645], 0, 7);
    PF_CopyDataBytes(&Progbuf[ProgOpClock_O_645], ProgOpClock_645, 7);

    /*操作者代码全FF*/
    memset(&Progbuf[ProgOpCode_O_645], 0xFF, 4);
    memset(ProgOpCode_645, 0xFF, 4);

	pProgbufDI = &Progbuf[ProgDI_O_645];
	for( i = 0; i < 10; i++ )
	{/*DI 全FF*/
		for( j = 0; j < 4; j++ )
		{
			*pProgbufDI = 0xFF;
			ProgDI_645[i][j] = *pProgbufDI;
			pProgbufDI++;
		}
	}
	ProgCrc_645 = PF_Cal_CRC(Progbuf, 51);
}
/***************************************************************************
函数原型 	INF_Append_ProgRecordDI
函数功能	向Str_ProgRecord变量中增加一次编程记录
输入参数	*pOpCode		本次编程的操作者代码,固定为4字节
			  	*pProgDI		本次编程的数据标识码,固定为4字节
				pProgRecord	编程记录保存全局变量指针
输出参数 	*pProgRecord	保存好的编程记录
返回参数	无
全局变量 	pProgRecord	此指针就是全局静态变量指针。
调用时机	14命令设置1、2类参数。其他命令都不进行编程记录。
				注意3类参数不写，身份认证有效时长设置也不写
***************************************************************************/
void INF_Append_ProgRecordDI (uchar8 *pOpCode, uchar8 *pProgDI, Str_ProgRecord *pProgRecord, uchar8 V_ProgType)
{
	uchar8	i, j;
	uchar8	Progbuf[500];		/*6+4+40+2=52*/
	uchar8	*pProgbufDI;
	uchar8	V_ReturnData;
	ushort16	DataLen, LenFor_Data = 400;

	/* 在应用连接取消的情况下，如果不是插卡过来，则退出，不做编程记录 */
	/* 一开始在应用连接取消的情况下不做编程记录，是为了模块波特率协商、写信号强度不做编程记录 */
	/* 但是对于卡表来讲，插卡后会取消所有的应用连接信息，此时卡写参数反而不做编程记录了，因此做了特殊判断 */
	/* 2021年1月28日修改 mym+fy+gyj */
	if( InF_ConectTimer_DealNoTimer() == C_TimerDisable )
	{
		if( ( pProgDI[2] != 0x98 )
		 || ( pProgDI[3] != 0x99 ) )
		{
			return;
		}
	}

	V_ReturnData = Get_ProgRecord1InRam(Progbuf, pProgRecord);

/*先计算已保存的编程事件记录是否CRC正确,不正确，清0*/
	if( ( V_ReturnData != C_OK ) && ( V_ReturnData != C_CrcErr_DataZero ) )
	{
		memset(Progbuf, 0x00, ProgCrc_O);
	}
	/*判断当前编程记录中的时间是否为全0，*/
	if( ( V_ReturnData != C_OK ) || ( Is_Buf_AllZero( &Progbuf[ProgOpClock_O], 7 ) == C_OK ) )
	{/*取内存编程记录时存在CRC错或时钟为0的错误，不管是什么错误，都初始化*/
		/*DI全部为FF*/
		pProgbufDI = &Progbuf[ProgDI_O];
		memset(pProgbufDI, 0xFF, ProgOADLen);

		Inf_EventReport_HP(C_ProgramEventNo, C_NewReport);
        InF_ActiveReportSetting(C_Times_Program);

		DataLen = SF_GetProgFixedData_698(CProgram_Degree, Progbuf);

		PF_CopyDataBytes(&Progbuf[0], &ProgOpClock[0], CLProgFixedData);

		memset(&Progbuf[ProgDI_O], 0x00, ProgOADLen);
		DataLen += ProgOADLen;
		if( Inf_GetRecordData( &Progbuf[ProgCrc_O], &LenFor_Data, CProgram_OADTab, 0x01 ) == C_OK )	/*取发生数据*/
		{
			DataLen += 	LenFor_Data;
		}
		InF_Write_Data(C_Msg_Communication, CProgram_Note_1, Progbuf, DataLen, C_W_SafeFlag);
	}
/*将编程事件记录中DI进行移位DI[i] <- DI[i-1],新的加入到DI[0]*/
	for( i = 9; i > 0; i-- )
	{
		for( j = 0; j < CLProgTypeOADGather; j++ )
		{
			ProgDI[i][j] = ProgDI[i - 1][j];
		}
	}
	if(C_ACTION_Request == V_ProgType)
	{
		ProgDI[0][0] = C_OMD;
	}
	else
	{
		ProgDI[0][0] = C_OAD;
	}
	PF_CopyDataBytes(&pProgDI[0], &ProgDI[0][1], 4);

	ProgCrc = PF_Cal_CRC(pProgRecord->FixedData, ProgCrc_O);
	return;
}

/***************************************************************************
函数原型 	INF_Append_ProgRecordDI
函数功能	向Str_ProgRecord变量中增加一次编程记录
输入参数	*pOpCode		本次编程的操作者代码,固定为4字节
			  	*pProgDI		本次编程的数据标识码,固定为4字节
				pProgRecord	编程记录保存全局变量指针
输出参数 	*pProgRecord	保存好的编程记录
返回参数	无
全局变量 	pProgRecord	此指针就是全局静态变量指针。
调用时机	14命令设置1、2类参数。其他命令都不进行编程记录。
				注意3类参数不写，身份认证有效时长设置也不写
***************************************************************************/
void	INF_Append_ProgRecordDI_645 (uchar8 *pOpCode, uchar8 *pProgDI, Str_ProgRecord_645 *pProgRecord_645)
{
	uchar8	i, j;
	uchar8	Progbuf[53];		/*6+4+40+2=52*/
	uchar8	*pProgbufDI;
	uchar8	V_ReturnData;
	ushort16	DataLen, V_usDataEncode;


	V_ReturnData = Get_ProgRecord1InRam_645(Progbuf, pProgRecord_645);
	if(V_ReturnData != C_OK)
	{/*取内存编程记录时存在CRC错或时钟为0的错误，不管是什么错误，都初始化*/
	  /*Progbuf，从头开始。*/
		/*取时钟*/
		DataLen = CLDate_Time;
		InF_Read_Data(CDate_Time, &Progbuf[ProgOpClock_O_645], &DataLen, &V_usDataEncode);
		/*取操作者代码 */
		PF_CopyDataBytes(&pOpCode[0], &Progbuf[ProgOpCode_O_645] ,4);
		/*DI全部为FF*/
		pProgbufDI = &Progbuf[ProgDI_O_645];
		memset(pProgbufDI, 0xFF, 40);
		Inf_EventReport_HP(C_ProgramEventNo, C_NewReport);
		InF_ActiveReportSetting(C_Times_Program);		/*编程主动上报*/
	}
/*将编程事件记录中DI进行移位DI[i] <- DI[i-1],新的加入到DI[0]*/
	pProgbufDI = &Progbuf[ProgDI_O_645];
	for( i = 9; i > 0; i-- )
	{
		for( j = 0; j < 4; j++ )
		{
			pProgbufDI[i * 4 + j] = pProgbufDI[( i - 1 ) * 4 + j];

		}
	}
/*将新的DI，加入到DI缓冲区*/
    if( ( pProgDI[1] == 0x02 ) && ( pProgDI[2] == 0x01 ) && ( pProgDI[3] == 0xF2 ) )	/*F2010201设置通信口1速率特征字*/
    {
        pProgbufDI[0] = pProgDI[0] + 2;        					/*645的标识码比698的DI0多2*/
        pProgbufDI[1] = (uchar8)(COne485_Baud_645 >> 8);		/*如果是698标识码通信口1速率特征字改成645标识码*/
        pProgbufDI[2] = (uchar8)(COne485_Baud_645 >> 16);
        pProgbufDI[3] = (uchar8)(COne485_Baud_645 >> 24);
    }
    else
    {
        PF_CopyDataBytes(&pProgDI[0], &pProgbufDI[0] ,4);
    }

/*赋值，并计算CRC*/
   PF_CopyDataBytes(&Progbuf[ProgOpClock_O_645], &ProgOpClock_645[0] ,7);
   PF_CopyDataBytes(&Progbuf[ProgOpCode_O_645], &ProgOpCode_645[0] ,4);

	pProgbufDI = &Progbuf[ProgDI_O_645];
	for( i = 0; i < 10; i++ )
	{
		for( j = 0; j < 4; j++ )
		{
			ProgDI_645[i][j] = *pProgbufDI;
			pProgbufDI++;
		}
	}

	ProgCrc_645 = PF_Cal_CRC(Progbuf, 51);
	return;
}

/***************************************************************************
函数原型 	INF_StopProgState
函数功能	供结束远程编程状态(身份认证取消)和将Str_ProgRecord所指内容
				写入最近一次编程记录
输入参数	*pProgRecord		最近一次编程数据

输出参数 	*pProgRecord		该变量全部清零
返回参数	C_Ok、C_Error和数据层返回值
全局变量 	SV_Comm_Parse.ID_Authentication_Timer
函数备注	只卡处理模块调用写卡的编程记录。
***************************************************************************/
uchar8 INF_StopProgState(Str_ProgRecord *pProgRecord)
{
	uchar8	 Progbuf[500];		/*6+4+40+2=52*/
	uchar8	 V_ReturnData;
	uchar8	 W_Safe_Flag = C_W_SafeFlag_1;
	ushort16 LenFor_Data = 400, V_Len = ProgCrc_O, V_usDataEncode;

/*写最近一次编程事件记录*/
/*先取数据*/
	V_ReturnData = Get_ProgRecord1InRam(Progbuf, pProgRecord);

	InF_Read_Data(CDate_Time, &Progbuf[ProgEndTime], &V_Len, &V_usDataEncode);/*发生时间*/
/*将Str_ProgRecord初始化掉*/
	INF_Init_Str_ProgRecord(pProgRecord);

/*判断CRC是否正确，正确才写，不正确直接退出*/
	W_Safe_Flag = W_Safe_Flag | C_W_SafeFlag_2;

	if(V_ReturnData != C_OK)
	{/*取出来的数据不管是CRC不正确还是编程时钟为全0，都认为是错误，不进行实际写事件记录*/
		return(C_Error);
	}
	W_Safe_Flag = W_Safe_Flag | C_W_SafeFlag_3;
	V_Len = ProgCrc_O;
	if( Inf_GetRecordData( &Progbuf[ProgCrc_O], &LenFor_Data, CProgram_OADTab, 0x02 ) == C_OK )/*取结束数据*/
	{
		V_Len += LenFor_Data;
	}

/*写最近一次编程记录*/
	V_ReturnData = InF_Write_Data(C_Msg_Communication, CProgram_Note_1 + 1, Progbuf, V_Len, W_Safe_Flag);
	return(V_ReturnData);
}

/***************************************************************************
函数原型 	INF_StopProgState
函数功能	供结束远程编程状态(身份认证取消)和将Str_ProgRecord所指内容
				写入最近一次编程记录
输入参数	*pProgRecord		最近一次编程数据

输出参数 	*pProgRecord		该变量全部清零
返回参数	C_Ok、C_Error和数据层返回值
全局变量 	SV_Comm_Parse.ID_Authentication_Timer
函数备注	只卡处理模块调用写卡的编程记录。
***************************************************************************/
uchar8 INF_StopProgState_645(Str_ProgRecord_645 *pProgRecord_645)
{
	uchar8	Progbuf[53];		/*6+4+40+2=52*/
	uchar8	V_ReturnData;
	uchar8	W_Safe_Flag = C_W_SafeFlag_1;

	V_ReturnData = Get_ProgRecord1InRam_645(Progbuf, pProgRecord_645);
/*将Str_ProgRecord初始化掉*/
	INF_Init_Str_ProgRecord_645(pProgRecord_645);

/*判断CRC是否正确，正确才写，不正确直接退出*/
	W_Safe_Flag = W_Safe_Flag | C_W_SafeFlag_2;

	if(V_ReturnData != C_OK)
	{/*取出来的数据不管是CRC不正确还是编程时钟为全0，都认为是错误，不进行实际写事件记录*/
		return(C_Error);
	}
	W_Safe_Flag = W_Safe_Flag | C_W_SafeFlag_3;
/*写最近一次编程记录*/
	V_ReturnData = InF_Write_Data(C_Msg_Communication, CProgram_Note_1_645, Progbuf, CLProgram_Note_1_645, W_Safe_Flag);
	return(V_ReturnData);
}
/***************************************************************************
函数原型 	INF_StopCommProgState
函数功能	退出通信编程状态
输入参数	无

输出参数 	无
返回参数	SV
全局变量 	SV_Comm_Parse.ProgRecord
函数备注	卡处理模块认证通过，即可首先调用本函数
				远程编程状态且写编程记录。
				通信模块结束编程记录时也可调用本函数。
***************************************************************************/
void		INF_StopCommProgState(void)
{
	INF_StopProgState(&SV_Comm_Parse.ProgRecord);
	INF_StopProgState_645(&SV_Comm_Parse.ProgRecord_645);	/*这两个函数顺序不要颠倒，上面一个有关闭编程状态*/
}

/***************************************************************************
函数原型: uchar8 Get_ProgRecord1InRam(uchar8 *pProgRecordInRam, Str_ProgRecord *pProgRecord)
功能描述: 获取内存上1次编程记录的数据(包括2字节CRC)
输入参数: pProgRecordInRam:输出参数指针
          *pProgRecord:最近一次编程数据
输出参数: *pProgRecordInRam:固定为52字节，所以调用时缓冲区长度要确保
返回参数: C_OK:表示正处于编程状态; C_Error:表示不处于编程状态或CRC错误
调用位置:
备    注: *pProgRecord不会改变，其他见上述注释。
***************************************************************************/
uchar8 Get_ProgRecord1InRam(uchar8 *pProgRecordInRam, Str_ProgRecord *pProgRecord)
{
	uchar8	*pProgbufDI;
	uchar8	V_ReturnData;
	uchar8	i;

	/*取内存编程记录*/
	PF_CopyDataBytes(&ProgOpClock[0], &pProgRecordInRam[0], CLProgFixedData);

	pProgbufDI = &pProgRecordInRam[ProgDI_O];
	for( i = 0; i < CProgOADNum; i++ )
    {
        PF_CopyDataBytes(&ProgDI[i][0], &pProgbufDI[i * CLProgTypeOADGather], CLProgTypeOADGather);
    }
	PF_Ushort16ToBuffer2(&pProgRecordInRam[ProgCrc_O], &ProgCrc);
    /*判断是否处于编程状态，判断条件有2:
    1、CRC是否正确
    2、编程时间是否为全0
    是否处于身份认证期间，先不管。防止以后扩展采用密码编程*/
	V_ReturnData = PF_Check_CRC( pProgRecordInRam, ( ProgCrc_O + 2 ) );
	if( V_ReturnData != C_OK )
    {
        /*CRC不正确*/
        return(C_Error);
    }

	V_ReturnData = Is_Buf_AllZero(&pProgRecordInRam[ProgOpClock_O], 7);
	if( V_ReturnData == C_OK )
    {
        /*时间全0，也返回错误*/
        return(C_Error);
    }
	return(C_OK);
}
/**********************************************************************************
Function：判断上电后实时量闭锁时间是否到*
该函数判断上电后寄存器是否为0,不为0返回C_Error,为0返回C_OK,为非法值清零定时器并返回C_OK
**********************************************************************************/
uchar8 Inf_DealEventReportShut(uchar8 Type)
{
    uchar8      V_Return = C_Error;

    if(C_ReportInit == Type)						/*上电初始化*/
    {
        SV_ReportShutTime = C_ReportInitTime;		/*上电初始化时间为功能模块闭锁时间+掉电事件结束时间*/
    }
    else
    {
		if( SV_ReportShutTime > C_ReportInitTime )
		{/*不合理的值,认为时间到,并将寄存器清零*/
			SV_ReportShutTime = 0;
		}
		if( SV_ReportShutTime > 0 )
		{
			SV_ReportShutTime--;
		}
		if( SV_ReportShutTime == 0 )
		{
			V_Return = C_OK;
		}
    }
    return V_Return;
}

/***************************************************************************
函数原型 	Get_ProgRecord1InRam
函数功能	获取内存上1次编程记录的数据(包括2字节CRC)
输入参数	pProgRecordInRam				:输出参数指针
				*pProgRecord					:最近一次编程数据
输出参数 	*pProgRecordInRam				:固定为52字节，所以调用时缓冲区长度要确保
返回参数	C_OK						:表示正处于编程状态
				C_Error						:表示不处于编程状态或CRC错误
全局变量
函数备注	*pProgRecord不会改变，其他见上述注释。
***************************************************************************/
uchar8	Get_ProgRecord1InRam_645(uchar8	*pProgRecordInRam, Str_ProgRecord_645 *pProgRecord_645)
{
	uchar8	*pProgbufDI;
	uchar8	V_ReturnData;
	uchar8	i;

	/*取内存编程记录*/
	PF_CopyDataBytes(&ProgOpClock_645[0], &pProgRecordInRam[ProgOpClock_O_645], 7);
    PF_CopyDataBytes(&ProgOpCode_645[0], &pProgRecordInRam[ProgOpCode_O_645], 4);
	pProgbufDI = &pProgRecordInRam[ProgDI_O_645];

	for( i = 0; i < 10; i++ )
	{
		PF_CopyDataBytes( &ProgDI_645[i][0], &pProgbufDI[i * 4], 4 );
	}
	PF_Ushort16ToBuffer2( &pProgRecordInRam[ProgCrc_O_645], &ProgCrc_645 );
/*判断是否处于编程状态，判断条件有2:*/
/* 1、CRC是否正确*/
/* 2、编程时间是否为全0*/
/*是否处于身份认证期间，先不管。防止以后扩展采用密码编程*/
	V_ReturnData = PF_Check_CRC( pProgRecordInRam, ( CLProgram_Note_1_645 + 2 ) );
	if(V_ReturnData != C_OK)
	{
		/*CRC不正确*/
		return(C_Error);
	}
	V_ReturnData = Is_Buf_AllZero(&pProgRecordInRam[ProgOpClock_O_645], 7);
	if(V_ReturnData ==C_OK)
	{
		/*时间全0，也返回错误*/
		return(C_Error);
	}
	return(C_OK);
}
/*******************************************************************************
函数原型： uchar8 Comm_ParseMessage(Str_Msg_Parameter * P_Msg_Parameter)
功能描述：完成通信模块消息处理解析(第一层)
输入参数：*P_Msg_Parameter:			消息结构体
输出参数：无
返回参数： Ok/C_Error
调用位置：
备    注：情况1：	SourceAddr= 调度。接收中断发送通讯解析消息。
				DerictAddr = C_Msg_Communication
				Len = 2
				数据域：Pt_Comm_No,取值，C_RS485_1、C_RS485_2、C_IR、C_Module
				中的一个
	情况2：	SourceAddr= 调度。调度每500ms发送通讯解析消息
				DerictAddr = C_Msg_Communication
				Len = 2
				数据域：Pt_Dispatch_Timing，取值C_HalfSecond
	情况3：	SourceAddr：C_Msg_Communication。上电或接收到密钥更新命令后触发
				DerictAddr = C_Msg_Communication
				Len = 1
				数据域：PT_CMsg_UpdataKey_Review,取值为空
	情况4：	SourceAddr：C_Msg_Dispatch。接收到编程开关后触发
				DerictAddr = C_Msg_Communication
				Len = 2
				数据域为Pt_Dispatch_Key，取值为C_KeyPrg
*******************************************************************************/
uchar8 Comm_ParseMessage(Str_Msg_Parameter * P_Msg_Parameter)
{
	uchar8	*pParm;
	uchar8  V_ReportState = 0;
	Str_Comm_Parm 	*pStr_Comm_Parm_Address;

/*如果调度发过来是停电，那么直接退出，返回C_OK*/
	if(P_Msg_Parameter->PowerFlag == C_PowerFalling)
	{/*注意，通信有低功耗下运行的要求，因此这里只能判断C_PowerFalling*/
		return(C_OK);
	}

/*区分三种情况,根据情况调用分项解析函数*/
	pParm = P_Msg_Parameter->Parameter;
	if(*pParm == Pt_Comm_No)
	{
		if(P_Msg_Parameter->Length ==(Pt_Comm_No_Len + 1))
		{
			/*情况1.这里不判断串口号是否正确。应在Comm_Parse中已判断*/
			pParm++;
			pStr_Comm_Parm_Address = Get_Str_Comm_Parm_Pointer(*pParm);
			if(CommProtocolType645 == C_ProtocolType_645)
			{
				Comm_Parse(*pParm, P_Msg_Parameter->PowerFlag);
			}
			else if(CommProtocolType == C_ProtocolType_698)
			{
				Comm_Parse_698(*pParm, P_Msg_Parameter->PowerFlag);
			}
			else
			{
				;/*都不是，不解析*/
			}
			return(C_OK);
		}
	}
	else if(*pParm == Pt_Dispatch_Timing)
	{
		if( P_Msg_Parameter ->Length == (Pt_Dispatch_Timing_Len + 1) )
		{
			pParm++;
			if(*pParm == C_HalfSecond)
			{
					/*情况2，定时消息*/
					Comm_500ms_Execute(P_Msg_Parameter->PowerFlag);
				  return(C_OK);
			}
			else if(*pParm == C_SystemSecondChange)
			{
				/*2020标准主动上报2005*/
				if(Inf_Comm_GetModuleCommuniFlag() == 0x0F)
				{
					Inf_Comm_ClearModuleCommuniFlag(0x0F);
				}
				else
				{
					Inf_Comm_ClearModuleCommuniFlag(0xFF);
				}
				if(Inf_Comm_REPORTFlagClear(C_ReportMaxNum_Remin) == 0)
				{
					V_ReportState = Inf_EventTypeCommReport(P_Msg_Parameter->PowerFlag, C_FirstNo);
					if( ( V_ReportState == 0 ) && ( Inf_DealEventReportShut(C_ReportInit - 1) == C_OK ) && ( Inf_Event_REPORTONumGet() == 0 ) )
					{
						Inf_CommReport(P_Msg_Parameter->PowerFlag);
					}
					if(Inf_Comm_GetModuleCommuniFlag() == (C_CommuniSafeWorld1 | C_CommuniSafeWorld2))
					{
						CommMSg_StartTxd_698(C_Module);
					}
				}
				return(C_OK);
			}
		}
	}
	return(C_Error);
}

/***************************************************************************
函数原型 	Have_IPEvent_MeterClear
函数功能	拥有独立编程事件项目电表总清编程（完成对应事件记录及数据层电表总清）
输入参数	*pV_645Frame				:接收到的645帧	,仅使用到其中的操作者代码
输出参数 	无
返回参数	无
全局变量 	无
函数备注	安全考虑3个，通信RecFlag，清零安全字节，编程安全字节
***************************************************************************/
void		Have_IPEvent_MeterClear(Str_Comm_645 *pV_645Frame )
{
	uchar8	Flag;
/*安全流程字节判断*/
	if(SV_Comm_Parse_Local.RecFlag!=C_CommRecFlagForInt_Ok)
	{
		return;
	}
	if( ( SV_Comm_Parse_Local.MeterClearFlag == C_ClearMeterSafeFlag )
	 && ( SV_Comm_Parse_Local.SafeControlFlag==C_W_SafeFlag ) )
	{/*安全字节正确，调用写总清记录并进行数据层总清，总清主动上报处理*/
		INF_WrClearAllRecord(pV_645Frame->Opcode, SV_Comm_Parse_Local.MeterClearFlag);
	}
/*如果是本地表，则写数据层剩余金额为钱包初始化命令中的预置金额*/
	if(C_Meter_Type == C_L_SmartMeter)
	{/*是本地费控表，且在厂外模式，肯定是钱包初始化命令才能到这里。*/
	/*写数据层剩余金额-充值*/
        Flag = C_Money_Init;
		if( JudgeTimerExceed10min(&SI_JTimer_BSOn2500) != C_TimerEnable )
		{
		/*写最近一次购电记录*/
		/*初始化钱包写购电记录，其中购电前剩余金额写成0*/
		/*购电金额为本次预置金额。购电总金额，由于总清，*/
		/*上1次购电金额读出来为0，*/
		/*所以可以采用上1次记录中购电总金额+本次购电金额*/
			InF_WRPre1PowerPurchaseRecord(MoneyClient_Table.V_ulMoney, SV_Comm_Parse_Local.MeterClearFlag, Flag);
		}
		else
		{
			InF_MoneyToPurchase(MoneyClient_Table.V_ulMoney, Flag, SV_Comm_Parse_Local.MeterClearFlag);
		}
	}
}
/***************************************************************************
函数原型 	Have_IPEvent_DemandClear
函数功能	拥有独立编程事件项目电表需清编程（完成对应事件记录及数据层需量清零）
输入参数	*pV_645Frame				:接收到的645帧	,仅使用到其中的操作者代码
输出参数 	无
返回参数	无
全局变量 	无
函数备注	安全考虑2个，通信RecFlag，编程安全字节
***************************************************************************/
void Have_IPEvent_DemandClear(Str_Comm_645 *pV_645Frame)
{
/*安全流程字节判断*/
	if( SV_Comm_Parse_Local.RecFlag != C_CommRecFlagForInt_Ok )
	{
		return;
	}
	if( SV_Comm_Parse_Local.SafeControlFlag != C_W_SafeFlag )
	{
		return;
	}

/*根据CDe_Clear_Note_1要求，读取数据层对应的需量*/
	Have_IPEvent_Prog_698(CDe_Clear_Note_1, CDe_Clear_Degree, pV_645Frame);
/*调用数据层清零动作	*/
	InF_Demand_Clear(C_Msg_Communication, SV_Comm_Parse_Local.SafeControlFlag);
}

/***************************************************************************
函数原型 	Have_IPEvent_EventClear
函数功能	拥有独立编程事件项目电表事件记录清零操作
				（完成对应事件记录及数据层事件记录相关内容清零)
输入参数	*pV_645Frame				:接收到的645帧	,仅使用到其中的操作者代码
输出参数 	无
返回参数	无
全局变量 	无
函数备注	安全考虑2个，通信RecFlag，编程安全字节
***************************************************************************/
void Have_IPEvent_EventClear(Str_Comm_645 *pV_645Frame, ulong32 V_ulOAD)
{
	uchar8	buf[C_Buf_MaxLen], i, k = 0;
	ulong32	MCE_Data_DI;							/*事件记录数据来源的标识码*/
	ushort16	buf_O_CanWrite = 0, V_ucRelateoff;	/*缓冲区可写数据的偏移*/
	ushort16	LenFor_Data = C_Buf_MaxLen;			/*缓冲区可被写的总的长度*/

/*安全流程字节判断*/
	if( SV_Comm_Parse_Local.RecFlag != C_CommRecFlagForInt_Ok )
	{
		return;
	}
	if( SV_Comm_Parse_Local.SafeControlFlag != C_W_SafeFlag )
	{
		return;
	}
	buf_O_CanWrite = SF_GetProgFixedData_698(CEven_Clear_Degree, buf);
	PF_Ulong32ToBuffer4(&buf[buf_O_CanWrite], &V_ulOAD, CLen_DI);
	buf_O_CanWrite += CLen_DI;

	V_ucRelateoff = buf_O_CanWrite;
	LenFor_Data = C_Buf_MaxLen - V_ucRelateoff;
	if(Inf_GetRecordData( &buf[V_ucRelateoff], &LenFor_Data, CEven_Clear_OADTab, 0x01 ) == C_OK )	/*取发生数据*/
	{
		buf_O_CanWrite += LenFor_Data;
	}
	InF_Write_Data(C_Msg_Communication, CEven_Clear_Note_1, buf, buf_O_CanWrite,(SV_Comm_Parse_Local.SafeControlFlag));

	LenFor_Data = C_Buf_MaxLen - V_ucRelateoff;
    buf_O_CanWrite = V_ucRelateoff;
	if(Inf_GetRecordData( &buf[V_ucRelateoff], &LenFor_Data, CEven_Clear_OADTab, 0x02 ) == C_OK )	/*取结束数据*/
	{
		buf_O_CanWrite += LenFor_Data;
	}
	InF_Write_Data(C_Msg_Communication, CEven_Clear_Note_1 + 1, buf, buf_O_CanWrite, (SV_Comm_Parse_Local.SafeControlFlag));

/*调用数据层函数，进行事件记录清零*/
	PF_Buffer4ToUlong32(&pV_645Frame->Data[C_O_EventClear_DI], &MCE_Data_DI, CLen_DI);

    for( i = 0; i < Str_698EventReport_Len; i++ )
    {
        if( ( ( (uchar8)( V_ulOAD >> 24 ) ) == 0x30 ) && ( ( (uchar8)( V_ulOAD >> 16 ) ) == ((uchar8)( ( Str_698EventReport[i].OIBANature ) >> 8 ) ) ) )
        {
            Inf_ReportList(C_ReportChannelAll, Str_698EventReport[i].EventNo, C_DeletReport);
            SF_Clear645_ReportNewAddNum(Str_698EventReport[i].EventNo, C_EventCLEAR);
            k++;
            if( ( ( (uchar8)( V_ulOAD >> 16 ) ) == CTrend_Rev_OIB )||( ( (uchar8)( V_ulOAD >> 16 ) ) == CRe_ReDe_Over_OIB ) )
            {
                if(k >= 4)
                {
                    break;
                }
            }
            else if( ( ( (uchar8)( V_ulOAD >> 16 ) ) < CTrend_Rev_OIB ) || ( ( (uchar8)( V_ulOAD >> 16 ) ) == COver_Lo_OIB ) )
            {
                if(k >= 3)
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }
    }

}

/***************************************************************************
函数原型 	Comm_AppendMsg
函数功能	通信插入一个消息标志
输入参数	MsgNum:			消息名称

输出参数 	无
返回参数	无
全局变量 	SV_Comm_Parse_Local
函数备注
***************************************************************************/
void		Comm_AppendMsg(ulong32	MsgNum)
{
	uchar8	i;
	uchar8	OneNum = 0;
	ulong32	MsgNumBak = MsgNum;

/*判断MsgNum是否合法*/
	for(i = 0; i < 32; i++ )
	{
		if( ( MsgNumBak & 0x00000001 ) != 0 )
		{
			OneNum++;
		}
		MsgNumBak = MsgNumBak >> 1;
	}
	if( OneNum != 1 )
	{
		return;
	}
	SV_Comm_Parse_Local.MessageFlag = SV_Comm_Parse_Local.MessageFlag | MsgNum;
	return;

}

/***************************************************************************
函数原型 	Comm_FetchMsg
函数功能	通信解析消息取出一个消息
输入参数	无

输出参数 	无
返回参数	消息号。无消息返回CMsg_Null
全局变量 	SV_Comm_Parse_Local
函数备注
***************************************************************************/
ulong32	Comm_FetchMsg(void)
{
	ulong32	MsgNum = 0x00000001;
	uchar8	i;

	for( i = 0; i < 32; i++ )
	{
		if( ( SV_Comm_Parse_Local.MessageFlag & MsgNum ) != 0 )
		{
			SV_Comm_Parse_Local.MessageFlag = SV_Comm_Parse_Local.MessageFlag & (~MsgNum);
			return(MsgNum);
		}
		else
		{
			MsgNum = MsgNum << 1;
		}
	}
	return(CMsg_Null);
}

/***************************************************************************
函数原型 	TimerExceed10min_Dec_IR
函数功能	Str_TimerExceed10min型变量进行定时器扣减
输入参数	*pTimerExceed10min：		待处理的定时器值

输出参数 	无
返回参数	C_TimerEnable/C_TimerDisable
全局变量 	Str_TimerExceed10min型变量
函数备注
***************************************************************************/
#define	C_BaseTimer_O		0
#define	C_Timer_O			1
#define	C_TimerCrc_O		5
uchar8	TimerExceed10min_Dec_IR( Str_TimerExceed10min *pTimerExceed10min )
{
	uchar8	V_ReturnData;
	uchar8	TimerExceed10min[C_StrTimerExceed10minLen];				/*定时器值暂存*/
	ushort16	Crc;

/*数据合法性的判断,不合法定时器清零并且返回C_TimerDisable*/
	TimerExceed10min[C_BaseTimer_O] = pTimerExceed10min->BaseTimer;
	PF_Ulong32ToBuffer4(&TimerExceed10min[C_Timer_O], &(pTimerExceed10min->Timer), C_TimerExceed10minLen);
	PF_Ushort16ToBuffer2(&TimerExceed10min[C_TimerCrc_O], &(pTimerExceed10min->Crc));
	V_ReturnData = PF_Check_CRC(TimerExceed10min, C_StrTimerExceed10minLen);
	if( ( V_ReturnData != C_OK ) && ( V_ReturnData != C_CrcErr_DataZero ) )
	{
		pTimerExceed10min->BaseTimer = 0;
		pTimerExceed10min->Timer = 0;
		pTimerExceed10min->Crc = 0;
		return(C_TimerDisable);
	}
/*判断定时器是否为0，为0，直接返回C_TimerDisable*/
	if( pTimerExceed10min->Timer == 0 )
	{
		return(C_TimerDisable);
	}
/*定时器进行减一扣减;采用TimerExceed10min数组中的数据，最后保存到pTimerExceed10min*/
	if( TimerExceed10min[C_BaseTimer_O] != 0 )
	{
		TimerExceed10min[C_BaseTimer_O]--;
	}
	if( TimerExceed10min[C_BaseTimer_O] == 0 )
	{
		if( pTimerExceed10min->Timer != 0 )
		{
			/*Timer未到0，则继续进行*/
			pTimerExceed10min->Timer = (pTimerExceed10min->Timer -1);		/*HEX格式*/
			PF_Ulong32ToBuffer4(&TimerExceed10min[C_Timer_O], &(pTimerExceed10min->Timer), C_TimerExceed10minLen);
			if( pTimerExceed10min->Timer == 0 )
			{
				/*定时器到了!*/
				Crc = PF_Cal_CRC(TimerExceed10min, 5);
				pTimerExceed10min->BaseTimer = 0;
				pTimerExceed10min->Timer = 0;
				pTimerExceed10min->Crc = Crc;
				return(C_TimerDisable);
			}
			else
			{
				TimerExceed10min[C_BaseTimer_O] = C_BaseTimer;
			}

		}
	}
	Crc = PF_Cal_CRC(TimerExceed10min, 5);
	pTimerExceed10min->BaseTimer = TimerExceed10min[C_BaseTimer_O];
	pTimerExceed10min->Crc = Crc;
	return(C_TimerEnable);
}
/***************************************************************************
函数原型 	TimerExceed10min_Dec
函数功能	Str_TimerExceed10min型变量进行定时器扣减
输入参数	*pTimerExceed10min：		待处理的定时器值

输出参数 	无
返回参数	C_TimerEnable/C_TimerDisable
全局变量 	Str_TimerExceed10min型变量
函数备注
***************************************************************************/
#define	C_BaseTimer_O		0
#define	C_Timer_O			1
#define	C_TimerCrc_O		5
uchar8	TimerExceed10min_Dec( Str_TimerExceed10min *pTimerExceed10min )
{
	uchar8	V_ReturnData;
	uchar8	TimerExceed10min[C_StrTimerExceed10minLen];				/*定时器值暂存*/
	ushort16	Crc;
	uchar8	Dec2[C_TimerExceed10minLen];
	uchar8	Result[C_TimerExceed10minLen];

/*数据合法性的判断,不合法定时器清零并且返回C_TimerDisable*/
	TimerExceed10min[C_BaseTimer_O] = pTimerExceed10min->BaseTimer;
	PF_Ulong32ToBuffer4(&TimerExceed10min[C_Timer_O], &(pTimerExceed10min->Timer), C_TimerExceed10minLen);
	PF_Ushort16ToBuffer2(&TimerExceed10min[C_TimerCrc_O], &(pTimerExceed10min->Crc));
	V_ReturnData = PF_Check_CRC(TimerExceed10min, C_StrTimerExceed10minLen);
	if( ( V_ReturnData != C_OK ) && ( V_ReturnData !=C_CrcErr_DataZero ) )
	{
		pTimerExceed10min->BaseTimer = 0;
		pTimerExceed10min->Timer = 0;
		pTimerExceed10min->Crc = 0;
		return(C_TimerDisable);
	}
/*判断定时器是否为0，为0，直接返回C_TimerDisable*/
	if( pTimerExceed10min->Timer == 0 )
	{
		return(C_TimerDisable);
	}

/*定时器进行减一扣减;采用TimerExceed10min数组中的数据，最后保存到pTimerExceed10min*/
	if(TimerExceed10min[C_BaseTimer_O] != 0)
	{
		TimerExceed10min[C_BaseTimer_O]--;
	}
	if(TimerExceed10min[C_BaseTimer_O] == 0)
	{
		if( pTimerExceed10min->Timer != 0 )
		{
			/*Timer未到0，则继续进行*/
			memset(Dec2, 0, C_TimerExceed10minLen);
			Dec2[0] = 0x01;
			PF_BCDDECBytes(&TimerExceed10min[C_Timer_O], Dec2, Result, C_TimerExceed10minLen);
			PF_CopyDataBytes(Result, &TimerExceed10min[C_Timer_O], C_TimerExceed10minLen);
			PF_Buffer4ToUlong32(&TimerExceed10min[C_Timer_O], &(pTimerExceed10min->Timer), C_TimerExceed10minLen);
			if( pTimerExceed10min->Timer == 0)
			{
				/*定时器到了!*/
				Crc = PF_Cal_CRC(TimerExceed10min, C_Timer_Base_10minLen);
				pTimerExceed10min->BaseTimer = 0;
				pTimerExceed10min->Timer = 0;
				pTimerExceed10min->Crc = Crc;
				return(C_TimerDisable);
			}
			else
			{
				TimerExceed10min[C_BaseTimer_O] = C_BaseTimer;
			}
		}
	}

	Crc = PF_Cal_CRC(TimerExceed10min, C_Timer_Base_10minLen);
	pTimerExceed10min->BaseTimer = TimerExceed10min[C_BaseTimer_O];
	pTimerExceed10min->Crc = Crc;

	return(C_TimerEnable);
}

/***************************************************************************
函数原型 	JudgeTimerExceed10min
函数功能	判断Str_TimerExceed10min型定时器是否有效
输入参数	*pTimerExceed10min：待处理的定时器值

输出参数 	无
返回参数	C_TimerEnable/C_TimerDisable
全局变量 	Str_TimerExceed10min型变量
函数备注
***************************************************************************/
uchar8	JudgeTimerExceed10min( Str_TimerExceed10min *pTimerExceed10min )
{
	uchar8	V_ReturnData;
	uchar8	TimerExceed10min[C_StrTimerExceed10minLen];				/*定时器值暂存*/

/*数据合法性的判断,不合法定时器清零并且返回C_TimerDisable*/
	TimerExceed10min[C_BaseTimer_O] = pTimerExceed10min->BaseTimer;
	PF_Ulong32ToBuffer4(&TimerExceed10min[C_Timer_O], &(pTimerExceed10min->Timer),C_TimerExceed10minLen);
	PF_Ushort16ToBuffer2(&TimerExceed10min[C_TimerCrc_O], &(pTimerExceed10min->Crc));
	V_ReturnData = PF_Check_CRC(TimerExceed10min, C_StrTimerExceed10minLen);
	if( ( V_ReturnData != C_OK ) && ( V_ReturnData !=C_CrcErr_DataZero ) )
	{
		pTimerExceed10min->BaseTimer = 0;
		pTimerExceed10min->Timer = 0;
		pTimerExceed10min->Crc = 0;
		return(C_TimerDisable);
	}
/*判断定时器是否为全0，为全0，则返回C_TimerDisable*/
	if( pTimerExceed10min->Timer == 0 )
	{
		return(C_TimerDisable);
	}
	else
	{
		return(C_TimerEnable);
	}
}
/***************************************************************************
函数原型 	SetTimerExceed10min
函数功能	完成Str_TimerExceed10min型定时器置初值
输入参数	pTimerExceed10min:	需要写的定时器地址，
				*pMinTimer:			输入的时间，基于1min或5min(软IJ)
									pMinTimer开始连续2字节数据，符合小端模式
输出参数 	*pTimerExceed10min
返回参数	C_TimerEnable/C_TimerDisable
全局变量 	Str_TimerExceed10min型变量
函数备注	20140504补充:对于软IJ，这个时间不是基于分钟，而是基于5分钟。
***************************************************************************/
uchar8	SetTimerExceed10min( Str_TimerExceed10min *pTimerExceed10min, uchar8 *pVMinTimer )
{
	uchar8	ReturnDataCode;
	uchar8	TimerExceed10min[C_StrTimerExceed10minLen];				/*定时器值暂存*/
	ushort16	Crc;

	PF_CopyDataBytes(pVMinTimer, &TimerExceed10min[C_Timer_O], C_TimerExceed10minLen);
	PF_Buffer4ToUlong32(&TimerExceed10min[C_Timer_O], &(pTimerExceed10min->Timer), C_TimerExceed10minLen);
	if( pTimerExceed10min->Timer == 0)
	{
		/*意味定时清0*/
		ReturnDataCode = C_TimerDisable;
		TimerExceed10min[C_BaseTimer_O] = 0;
	}
	else
	{
		ReturnDataCode = C_TimerEnable;
		TimerExceed10min[C_BaseTimer_O] = C_BaseTimer;
	}

	Crc = PF_Cal_CRC(TimerExceed10min, C_Timer_Base_10minLen);
	pTimerExceed10min->BaseTimer = TimerExceed10min[C_BaseTimer_O];
	pTimerExceed10min->Crc = Crc;

	return(ReturnDataCode);
}

/***************************************************************************
函数原型 	DealWith_ID_Auth_Timer
函数功能	完成身份认证定时器设置和扣减，数据层剩余时间的返写
				及
输入参数	Method			:处理方法。
								:取值C_Set_TimerExceed10min/ C_Dec_TimerExceed10min
				*pVTimer			:基于基本定时器的时间2字节（小端）。（C_Set_TimerExceed10min时有效）
输出参数 	无
返回参数	无
全局变量 	SV_Comm_Parse.ID_Authentication_Timer
函数备注	扣减时，基于基本节拍500ms扣减一次
				设置0就是对身份认证定时器清0初始化
***************************************************************************/
void	DealWith_ID_Auth_Timer( uchar8 Method, uchar8 *pVTimer )
{
	uchar8	buf[5];
	uchar8	MeterRunState3[CLMeter_Work_State3 + 3];
	ushort16	DataLen, V_usDataEncode;
	ulong32 IDTimer;

	switch( Method )
	{
		case C_Set_TimerExceed10min:
			SetTimerExceed10min(&ID_AuthT, pVTimer);
			break;

		case C_Dec_TimerExceed10min:
		{
			IDTimer = ID_AuthT_Timer;
			TimerExceed10min_Dec_IR(&ID_AuthT);
			if( ID_AuthT_Timer == 0 )
			{
				if( IDTimer != 0 )
				{
                    buf[0] = Pt_ResetEsam;			/*发送复位消息给ESAM模块*/
                    Dispatch_SendMessage(C_Msg_Esam, buf, Pt_ResetEsam_Len + 1);
				}
			}
		}break;

		default:
			break;
	}
/*电表运行字3*/
	DataLen = CLMeter_Work_State3;
	InF_Read_Data(CMeter_Work_State3, MeterRunState3, &DataLen, &V_usDataEncode);	/*读不出不管*/
	MeterRunState3[CO_IDAuth] = MeterRunState3[CO_IDAuth] & (~CB_IDAuth);
	if( ( Com_Conect.ConectOverTime != 0 ) || ( ID_AuthT_Timer != 0 ) )
	{
		MeterRunState3[CO_IDAuth] = MeterRunState3[CO_IDAuth] | CB_IDAuth;
	}
	InF_Write_Data(C_Msg_Communication, CMeter_Work_State3, MeterRunState3, CLMeter_Work_State3, C_W_SafeFlag);

/*返写身份认证剩余时间,645长度为2字节，直接取低字节*/
	PF_Ulong32ToBuffer4(buf,&ID_AuthT_Timer,4);
	InF_Write_Data(C_Msg_Communication, CID_Auth_Remain_Time_645, buf, CLID_Auth_Remain_Time_645, C_W_SafeFlag);
	return;
}

/***************************************************************************
函数原型 	DealWith_ID_AuthT_T_Timer
函数功能	完成红外安全认证时长定时器的设置和扣减
				完成数据层返写，电表运行状态字3的写，显示符号的处理
输入参数	Method			:处理方法。
								:取值C_Set_TimerExceed10min/ C_Dec_TimerExceed10min
				*pVTimer			:基于基本定时器的时间2字节（小端）。（C_Set_TimerExceed10min时有效）
输出参数 	无
返回参数	无
全局变量 	SV_Comm_Parse.IR_Authentication_Timer.Timer
函数备注	设置成0，就是初始化清0
				扣减时，基于基本节拍500ms扣减一次
				这里存在一个缺陷，即如果显示模块中符号误点亮，我这里
				是不会清除发灭消息。这里是在设置和扣减到0的沿上发消息。
				已在2014.05.05和小牛、小郭谈过这个缺陷。结论:显示模块自己搞定。
***************************************************************************/
void	DealWith_ID_Auth_T_Timer( uchar8 Method, uchar8 *pVTimer )
{
	uchar8	buf[5];
	uchar8	V_ReturnData;
	uchar8	MeterRunState3[CLMeter_Work_State3 + 3];
	ushort16	DataLen, V_usDataEncode;

	switch( Method )
	{
		case	C_Set_TimerExceed10min:
			/*设置定时器，不管设置结果，肯定会处理显示符号*/
			SetTimerExceed10min(&ID_AuthT_T, pVTimer);
			break;

		case	C_Dec_TimerExceed10min:
		{
			/*进行数据扣减，扣减到0才进行显示符号处理*/
			V_ReturnData = JudgeTimerExceed10min(&ID_AuthT_T);/*存储hex格式，扣减不能BCD扣减*/
			if( V_ReturnData == C_TimerEnable )
			{
				V_ReturnData = TimerExceed10min_Dec_IR(&ID_AuthT_T);
			}
		}break;

		default:
			break;
	}
/*先取电表运行状态字3，将红外认证位屏蔽*/
	DataLen = CLMeter_Work_State3;
	InF_Read_Data(CMeter_Work_State3, MeterRunState3, &DataLen, &V_usDataEncode);	/*读不出不管*/
	MeterRunState3[CO_IRAuth_T] = MeterRunState3[CO_IRAuth_T] & (~CB_IRAuth_T);
	if( ( ID_AuthT_T_Timer != 0 ) )
	{
		MeterRunState3[CO_IRAuth_T] = MeterRunState3[CO_IRAuth_T] | CB_IRAuth_T;
	}
	InF_Write_Data(C_Msg_Communication, CMeter_Work_State3, MeterRunState3, CLMeter_Work_State3, C_W_SafeFlag);
/*刷新数据层对应红外认证剩余时间 */
	PF_Ulong32ToBuffer4(buf, &ID_AuthT_T_Timer, 4);
	InF_Write_Data(C_Msg_Communication, CID_Auth_T_Remain_Time, buf, CLInfra_Auth_Remain_Time, C_W_SafeFlag);
	return;
}
/***************************************************************************
函数原型 	DealWith_IR_Auth_Timer
函数功能	完成红外安全认证时长定时器的设置和扣减
				完成数据层返写，电表运行状态字3的写，显示符号的处理
输入参数	Method			:处理方法。
								:取值C_Set_TimerExceed10min/ C_Dec_TimerExceed10min
				*pVTimer			:基于基本定时器的时间2字节（小端）。（C_Set_TimerExceed10min时有效）
输出参数 	无
返回参数	无
全局变量 	SV_Comm_Parse.IR_Authentication_Timer.Timer
函数备注	设置成0，就是初始化清0
				扣减时，基于基本节拍500ms扣减一次
				这里存在一个缺陷，即如果显示模块中符号误点亮，我这里
				是不会清除发灭消息。这里是在设置和扣减到0的沿上发消息。
				已在2014.05.05和小牛、小郭谈过这个缺陷。结论:显示模块自己搞定。
***************************************************************************/
void	DealWith_IR_Auth_Timer( uchar8 Method, uchar8 *pVTimer )
{
	uchar8	buf[5];
	uchar8	V_ReturnData;
	uchar8	MeterRunState3[CLMeter_Work_State3 + 3];
	ushort16	DataLen, V_usDataEncode;

	switch( Method )
	{
		case	C_Set_TimerExceed10min:
		{
/*设置定时器，不管设置结果，肯定会处理显示符号*/
			SetTimerExceed10min(&IR_AuthT, pVTimer);
			if( ( IR_AuthT_Timer == 0 )
			 && ( IR_AuthT_Timer_645 == 0 )
		 	 && ( JudgeTimerExceed10min(&ProgKey_Timer) == C_TimerDisable ) )			/*设置的值为0*/
			{
				/*发灭红外认证显示符号消息*/
				Comm_SendMsgToDisp(C_ProgramEnableSign, C_NotDisplay, C_Duration_Alway);
			}
			else
			{
				/*发点红外认证显示符号消息*/
				Comm_SendMsgToDisp(C_ProgramEnableSign, C_AlwaysDisplay, C_Duration_Alway);
			}
		}break;

		case	C_Dec_TimerExceed10min:
		{
			/*进行数据扣减，扣减到0才进行显示符号处理*/
			V_ReturnData = JudgeTimerExceed10min(&IR_AuthT);/*存储hex格式，扣减不能BCD扣减*/
			if( V_ReturnData == C_TimerEnable )
			{
				V_ReturnData = TimerExceed10min_Dec_IR(&IR_AuthT);
				if( ( V_ReturnData == C_TimerDisable )
				 && ( IR_AuthT_Timer_645 == 0 )
				 && ( JudgeTimerExceed10min(&ProgKey_Timer) == C_TimerDisable ) )
				{
					/*发灭红外认证显示符号消息*/
					Comm_SendMsgToDisp(C_ProgramEnableSign, C_NotDisplay,C_Duration_Alway);
				}
			}
		}break;

		default:
			break;
	}
/*先取电表运行状态字3，将红外认证位屏蔽*/
	DataLen = CLMeter_Work_State3;
	InF_Read_Data(CMeter_Work_State3, MeterRunState3, &DataLen, &V_usDataEncode);	/*读不出不管*/
	MeterRunState3[CO_IRAuth] = MeterRunState3[CO_IRAuth] & (~CB_IRAuth);
	if( ( IR_AuthT_Timer_645 != 0 ) || ( IR_AuthT_Timer != 0 )
	  ||( JudgeTimerExceed10min(&ProgKey_Timer) == C_TimerEnable ) )
	{
		MeterRunState3[CO_IRAuth] = MeterRunState3[CO_IRAuth] | CB_IRAuth;
	}
	InF_Write_Data(C_Msg_Communication, CMeter_Work_State3, MeterRunState3, CLMeter_Work_State3, C_W_SafeFlag);
/*刷新数据层对应红外认证剩余时间*/
	PF_Ulong32ToBuffer4(buf,&IR_AuthT_Timer,4);
	InF_Write_Data(C_Msg_Communication, CInfra_Auth_Remain_Time, buf, CLInfra_Auth_Remain_Time, C_W_SafeFlag);
	return;
}
/***************************************************************************
函数原型 	DealWith_IR_Auth_Timer_645
函数功能	完成红外安全认证时长定时器的设置和扣减
				完成数据层返写，电表运行状态字3的写，显示符号的处理
输入参数	Method			:处理方法。
								:取值C_Set_TimerExceed10min/ C_Dec_TimerExceed10min
				*pVTimer			:基于基本定时器的时间2字节（小端）。（C_Set_TimerExceed10min时有效）
输出参数 	无
返回参数	无
全局变量 	SV_Comm_Parse.IR_Authentication_Timer.Timer
函数备注	设置成0，就是初始化清0
				扣减时，基于基本节拍500ms扣减一次
				这里存在一个缺陷，即如果显示模块中符号误点亮，我这里
				是不会清除发灭消息。这里是在设置和扣减到0的沿上发消息。
				已在2014.05.05和小牛、小郭谈过这个缺陷。结论:显示模块自己搞定。
***************************************************************************/
void	DealWith_IR_Auth_Timer_645( uchar8 Method, uchar8 *pVTimer )
{
	uchar8	buf[5];
	uchar8	V_ReturnData;
	uchar8	MeterRunState3[CLMeter_Work_State3 + 3];
	ushort16	DataLen, V_usDataEncode;

	switch(Method)
	{
		case	C_Set_TimerExceed10min:
		{
			/*设置定时器，不管设置结果，肯定会处理显示符号*/
			SetTimerExceed10min(&IR_AuthT_645, pVTimer);
			if( ( IR_AuthT_Timer_645 == 0 )
			 && ( IR_AuthT_Timer == 0 )
			 && ( JudgeTimerExceed10min(&ProgKey_Timer) == C_TimerDisable ) )			/*设置的值为0*/
			{
				/*发灭红外认证显示符号消息*/
				Comm_SendMsgToDisp(C_ProgramEnableSign, C_NotDisplay, C_Duration_Alway);
			}
			else
			{
				/*发点红外认证显示符号消息*/
				Comm_SendMsgToDisp(C_ProgramEnableSign, C_AlwaysDisplay, C_Duration_Alway);
			}
		}break;

		case	C_Dec_TimerExceed10min:
		{
			/*进行数据扣减，扣减到0才进行显示符号处理*/
			V_ReturnData = JudgeTimerExceed10min(&IR_AuthT_645);/*存储hex格式，扣减不能BCD扣减*/
			if( V_ReturnData == C_TimerEnable )
			{
				V_ReturnData = TimerExceed10min_Dec_IR(&IR_AuthT_645);
				if( ( V_ReturnData == C_TimerDisable )
				 && ( IR_AuthT_Timer == 0 )
				 && ( JudgeTimerExceed10min(&ProgKey_Timer) == C_TimerDisable ) )
				{
					/*发灭红外认证显示符号消息*/
					Comm_SendMsgToDisp(C_ProgramEnableSign, C_NotDisplay, C_Duration_Alway);
				}
			}
		}break;

		default:
			break;
	}
/*先取电表运行状态字3，将红外认证位屏蔽*/
	DataLen = CLMeter_Work_State3;
	InF_Read_Data(CMeter_Work_State3, MeterRunState3, &DataLen, &V_usDataEncode);	/*读不出不管*/
	MeterRunState3[CO_IRAuth] = MeterRunState3[CO_IRAuth] & (~CB_IRAuth);
	if( ( IR_AuthT_Timer_645 != 0 )
	 || ( IR_AuthT_Timer != 0 )
     || ( JudgeTimerExceed10min(&ProgKey_Timer) == C_TimerEnable ) )
	{
		MeterRunState3[CO_IRAuth] = MeterRunState3[CO_IRAuth] |CB_IRAuth;
	}
	InF_Write_Data(C_Msg_Communication, CMeter_Work_State3, MeterRunState3, CLMeter_Work_State3, C_W_SafeFlag);
/*刷新数据层对应红外认证剩余时间*/
	PF_Ulong32ToBuffer4(buf, &IR_AuthT_Timer_645, 4);
	InF_Write_Data(C_Msg_Communication,CInfra_Auth_Remain_Time_645, buf, CLInfra_Auth_Remain_Time_645, C_W_SafeFlag);
	return;
}
/***************************************************************************
函数原型 	DealWith_SI_J_Timer
函数功能	完成软件IJ的设置、扣减数据层返写及对应符号显示
输入参数	Method			:处理方法。
								:取值
								C_Set_TimerExceed10min	:设置
								C_Dec_TimerExceed10min	:定时器-1
								C_Sub_TimerExceed10min	:定时器减固定值
				*pVTimer			:基于基本定时器的时间,2字节（小端）。
								:方法为C_Set_TimerExceed10min/C_Sub_TimerExceed10min时有效
								:单位为5min，10进制数
输出参数 	无
返回参数	无
全局变量 	SV_Comm_Parse.SI_JTimer_BSOn2_5s.Timer
函数备注	扣减时，基于基本节拍2500ms扣减一次
				这里存在一个缺陷，即如果显示模块中符号误点亮，我这里
				是不会清除发灭消息。这里是在设置和扣减到0的沿上发消息。
				已在2014.05.05和小牛、小郭谈过这个缺陷。结论:显示模块自己搞定。
***************************************************************************/
void	DealWith_SI_J_Timer( uchar8  Method, uchar8  *pVTimer )
{
	uchar8	 buf[5];
	uchar8	 V_ReturnData;
	uchar8	 V_ucDatabuf[4];
	ushort16 V_ucDataLen, V_usDataEncode;
	ulong32  V_usData=0;

	switch( Method )
	{
		case	C_Sub_TimerExceed10min:
		{
			SI_JBaseTimer_2500 = 0;
			memset(buf, 0, C_TimerExceed10minLen);
			if(JudgeTimerExceed10min(&SI_JTimer_BSOn2500) == C_TimerEnable)
			{
				PF_Ulong32ToBuffer4(buf, &SI_JT_Timer, C_TimerExceed10minLen);
				if( PF_BCDDECBytes(buf, pVTimer, buf, C_TimerExceed10minLen) == C_CY )
				{
					memset(buf, 0, C_TimerExceed10minLen);
				}
			}
			SetTimerExceed10min(&SI_JTimer_BSOn2500, buf);
			if(SI_JT_Timer == 0)			/*设置的值为0*/
			{/*发显示坐标轴消息*/
				Comm_SendMsgToDisp(C_AxisSign, C_AlwaysDisplay, C_Duration_Alway);
			}
			else
			{/*发坐标轴闪烁消息*/
				Comm_SendMsgToDisp(C_AxisSign, C_TwinkleDisplay, C_Duration_Alway);
			}
		}break;
		case	C_Set_TimerExceed10min:
		{
			/*设置的话，先将基本节拍清零*/
			SI_JBaseTimer_2500 = 0;
			/*设置定时器，不管设置结果，肯定会处理显示符号*/
			SetTimerExceed10min(&SI_JTimer_BSOn2500, pVTimer);
			if(SI_JT_Timer == 0)			/*设置的值为0*/
			{
				/*发显示坐标轴消息*/
				Comm_SendMsgToDisp(C_AxisSign, C_AlwaysDisplay, C_Duration_Alway);
			}
			else
			{
				/*发坐标轴闪烁消息*/
				Comm_SendMsgToDisp(C_AxisSign, C_TwinkleDisplay, C_Duration_Alway);
			}
		}break;
		case		C_Dec_TimerExceed10min:
		{
			/*进行数据扣减，扣减到0才进行显示符号处理*/
			V_ReturnData = JudgeTimerExceed10min(&SI_JTimer_BSOn2500);
			if(V_ReturnData == C_TimerEnable)
			{
				V_ReturnData = TimerExceed10min_Dec(&SI_JTimer_BSOn2500);
				if(V_ReturnData == C_TimerDisable)
				{
					/*发显示坐标轴消息*/
					Comm_SendMsgToDisp(C_AxisSign, C_AlwaysDisplay, C_Duration_Alway);
				}
			}
		}break;

		default:
			break;
	}
	V_ucDataLen = CLSoftI_J_RemainTime;
	InF_Read_Data(CSoftI_J_RemainTime, &V_ucDatabuf[0], &V_ucDataLen, &V_usDataEncode);
	PF_Buffer4ToUlong32(&V_ucDatabuf[0], &V_usData, C_TimerExceed10minLen);

	PF_Ulong32ToBuffer4(buf, &SI_JT_Timer, C_TimerExceed10minLen);
	if( ( SI_JT_Timer == 0 ) && ( V_usData == 0 ) )
	{
		return;
	}
	InF_Write_Data(C_Msg_Communication, CSoftI_J_RemainTime, buf, CLSoftI_J_RemainTime, C_W_SafeFlag);
	return;
}
/***************************************************************************
函数原型 	InF_IsInFactoryState
函数功能	供非通信模块调用，判断是否在厂内状态
输入参数	无
输出参数 	无
返回参数	C_OK			:在厂内状态
				C_Error			:不在厂内状态
全局变量 	无
函数备注	无
***************************************************************************/
uchar8	InF_IsInFactoryState(void)
{
	if( JudgeTimerExceed10min(&SI_JTimer_BSOn2500) == C_TimerEnable )
	{
		return(C_OK);
	}
	else
	{
		return(C_Error);
	}
}
/***************************************************************************
函数原型 	Comm_DealwithSPTVariable
函数功能	处理电能表挂起全局静态变量SV_Comm_Parse.SPT Variable
				及处理现实锁符号
输入参数	method高半字节:密级,=C_Key02Flag,表示为02级
								=C_Key04Flag,表示为04级
								=C_SPTFlag,表示为mac错挂起
			method低半字节:处理方法
							=C_SPTNumAdd，将挂起次数加的方法
							=C_JudgeSPTVariable，判断200次是否到方法
							=C_InitSPTVariable，初始化方法.注意这里初始化不是为
											将所有次数清0，还是根据CRC和时钟综合判断
											和Judge方法不同的是，肯定会动作锁点亮或灭
							=C_KeyErrNumAdd，密码错误次数+
							=C_JudgeKeyErr，密码错误次数判断
							=C_ClrKeyErrNum	密码错误次数清零，因为密码连续错误所以有这个方法
输入参数说明：因为一开始02、04级密码闭锁是合为一个闭锁内容。加，判断和初始化方法分为3*2.现在0204分开：
			method高半字节:密级,=C_Key02Flag,C_Key04Flag，使用C_KeyErrNumAdd，C_JudgeKeyErr，C_ClrKeyErrNum
							    =C_SPTFlag，使用C_SPTNumAdd，C_JudgeSPTVariable，C_InitSPTVariable
输出参数 	SV_Comm_Parse. SPT Variable
返回参数	Ok，C_SPT_Num_Over（安全次数超）C_KeyErr_Num_Over(密码错误次数超)
全局变量
函数备注	这里时钟读不出，认为是时钟非法，本处没有进行时钟合法性判断。
***************************************************************************/
#define	Key02_ErrNum_O		0
#define	Key04_ErrNum_O		1
#define	SPTNum_O			2
#define	SPTRecentClock_O	3		/*时分秒*/
#define	SPTRecentDate_O		3		/*（SPTRecentClock_O+SPTRecentDate_O）为年月日起始偏移，所以这里3固定不变。*/
#define	SPTCrc_O			( SPTRecentClock_O + CLDate_Time )
uchar8	Comm_DealwithSPTVariable(uchar8 method)
{
	uchar8	buf[CLen_Str_SPT];
	uchar8	V_ReturnData;
	uchar8	ReturnCode = C_OK;
	uchar8	Clock[CLDate_Time];
	uchar8	i;
	uchar8	Key0204_ErrNum_O;
	ushort16	DataLen, V_usDataEncode;

/*****************根据高办字节判断密级************************/
	if( ( method & 0xF0 ) == C_Key02Flag )	/*02级密码偏移*/
	{
		Key0204_ErrNum_O = Key02_ErrNum_O;
	}
	else
	{/*其他去04级密码偏移,如果为mac错挂起处理的话这个偏移为04级密码的也没有问题,有mode方式控制不会处理04级密码相关*/
		Key0204_ErrNum_O = Key04_ErrNum_O;
	}
	method &= 0x0F;
/*判断SPT CRC是否正确。不正确初始化，并返回C_OK*/
	buf[Key02_ErrNum_O] = KEY02ErrNum;
	buf[Key04_ErrNum_O] = KEY04ErrNum;
	buf[SPTNum_O] = SPTNum;
	PF_CopyDataBytes(SPTRecentClock, &buf[SPTRecentClock_O], CLDate_Time);
	PF_Ushort16ToBuffer2(&buf[SPTCrc_O], &SPTCrc);
	V_ReturnData = PF_Check_CRC(buf, CLen_Str_SPT);
	if( ( V_ReturnData != C_OK ) && ( V_ReturnData != C_CrcErr_DataZero ) )
	{
		method = C_InitSPTVariable;			/*CRC error and data is not zero*/
		for( i = 0; i < ( CLen_Str_SPT - 2 ); i++ )
		{
			buf[i] = 0;
		}
	}
/*按照method，进行相关处理*/
	switch(method)
		{
			case		C_KeyErrNumAdd:
			{
				if(buf[Key0204_ErrNum_O]>=C_Key0204_ErrThreshold)
				{/*次数已满*/
					ReturnCode = C_KeyErr_Num_Over;
				}
				else
				{
					buf[Key0204_ErrNum_O]++;
					DataLen = CLDate_Time;
					V_ReturnData = InF_Read_Data(CDate_Time, &buf[SPTRecentClock_O], &DataLen, &V_usDataEncode);
					if( buf[Key0204_ErrNum_O] >= C_Key0204_ErrThreshold )
					{/*加1后，满3次点锁。沿!*/
						ReturnCode = C_KeyErr_Num_Over;	/*点锁，是不需要判断SPT的*/
						Comm_SendMsgToDisp(C_HoldUpSign, C_AlwaysDisplay, C_Duration_Alway);
					}
				}
				break;
			}
			case		C_SPTNumAdd:
			{/*次数++*/
				if(buf[SPTNum_O] >= C_SPTNum_Threshold)
				{/*次数已满*/
					ReturnCode = C_SPT_Num_Over;
				}
				else
				{
					buf[SPTNum_O]++;
					DataLen = CLDate_Time;
					V_ReturnData = InF_Read_Data(CDate_Time, &buf[SPTRecentClock_O], &DataLen, &V_usDataEncode);
					if( buf[SPTNum_O] >= C_SPTNum_Threshold )
					{/*加1后，满200次点锁。沿!*/
						ReturnCode = C_SPT_Num_Over;
						Comm_SendMsgToDisp(C_HoldUpSign, C_AlwaysDisplay, C_Duration_Alway);
					}
				}
				break;
			}
			case		C_JudgeSPTVariable:
			case		C_JudgeKeyErr:
			{/*判断SPT有没有溢出。*/
				if( Is_Buf_AllZero(buf, ( CLen_Str_SPT - 2 ) ) == C_OK )
				{	/*次数和时间都为0，不需要发灭锁消息，直接退出。*/
					break;
				}
				DataLen = CLDate_Time;
				V_ReturnData = InF_Read_Data(CDate_Time, Clock, &DataLen, &V_usDataEncode);
				if( ( Clock[SPTRecentDate_O] != buf[SPTRecentClock_O + SPTRecentDate_O] )
				 || ( Clock[SPTRecentDate_O + 1] != buf[SPTRecentClock_O + SPTRecentDate_O + 1] )
				 ||	( Clock[SPTRecentDate_O + 2] != buf[SPTRecentClock_O + SPTRecentDate_O + 2] ) )
				{	/*日期不等，即可进行清0动作。并将数据全部清零*/
					buf[SPTNum_O] = 0;
					buf[Key02_ErrNum_O] = 0;
					buf[Key04_ErrNum_O] = 0;
					for(i = 0; i < CLDate_Time; i++ )
					{
						buf[SPTRecentClock_O + i] = 0;
					}
					Comm_SendMsgToDisp(C_HoldUpSign, C_NotDisplay, C_Duration_Alway);
					break;
				}
				else
				{
					if(method == C_JudgeSPTVariable)
					{
						if(buf[SPTNum_O] >= C_SPTNum_Threshold)
						{
							ReturnCode = C_SPT_Num_Over;
						}
					}
					else
					{
						if(buf[Key0204_ErrNum_O] >= C_Key0204_ErrThreshold)
						{
							ReturnCode = C_KeyErr_Num_Over;
						}
					}
					return(ReturnCode);
				}
			}
			case		C_InitSPTVariable:
			{	/*本处和Judge方法不同的是，不管怎么说都会发锁的消息*/
				if( Is_Buf_AllZero(buf,( CLen_Str_SPT - 2 ) ) == C_OK )
				{	/*次数和时间都为0，发灭锁消息，直接退出。*/
					Comm_SendMsgToDisp(C_HoldUpSign, C_NotDisplay, C_Duration_Alway);
					break;
				}
				DataLen = CLDate_Time;
				V_ReturnData = InF_Read_Data(CDate_Time, Clock, &DataLen, &V_usDataEncode);
				if(V_ReturnData != C_OK)
				{	/*读不出时钟,次数灭0?*/
					buf[SPTNum_O] = 0;
					buf[Key02_ErrNum_O] = 0;
					buf[Key04_ErrNum_O] = 0;
					Comm_SendMsgToDisp(C_HoldUpSign, C_NotDisplay, C_Duration_Alway);
					break;
				}
				if( ( Clock[SPTRecentDate_O] != buf[SPTRecentClock_O + SPTRecentDate_O] )
				 || ( Clock[SPTRecentDate_O + 1] != buf[SPTRecentClock_O + SPTRecentDate_O + 1] )
				 || ( Clock[SPTRecentDate_O + 2] != buf[SPTRecentClock_O + SPTRecentDate_O + 2] ) )
				{	/*日期不等，即可进行清0动作。*/
					buf[SPTNum_O] = 0;
					buf[Key02_ErrNum_O] = 0;
					buf[Key04_ErrNum_O] = 0;
					for( i = 0; i < CLDate_Time; i++ )
					{
						buf[SPTRecentClock_O + i] = 0;
					}
					Comm_SendMsgToDisp(C_HoldUpSign, C_NotDisplay, C_Duration_Alway);
					break;
				}
				else
				{
					if( ( buf[SPTNum_O] >= C_SPTNum_Threshold ) || ( buf[Key02_ErrNum_O] >= C_Key0204_ErrThreshold ) || ( buf[Key04_ErrNum_O] >= C_Key0204_ErrThreshold ) )
					{
						ReturnCode = C_SPT_Num_Over;
						Comm_SendMsgToDisp(C_HoldUpSign, C_AlwaysDisplay, C_Duration_Alway);
					}
					else
					{
						Comm_SendMsgToDisp(C_HoldUpSign, C_NotDisplay, C_Duration_Alway);
					}
					return(ReturnCode);
				}
			}
			case		C_ClrKeyErrNum:
			{/*密码次数清零方法.清零前，如果密码错次数满,SPT次数不满，*/
			/*则本次清零，需发灭锁消息。否则不管灭锁消息*/
				if( ( buf[SPTNum_O] < C_SPTNum_Threshold ) && ( buf[Key0204_ErrNum_O] >= C_Key0204_ErrThreshold ) )
				{
					Comm_SendMsgToDisp(C_HoldUpSign, C_NotDisplay, C_Duration_Alway);
				}
				DataLen = CLDate_Time;
				V_ReturnData = InF_Read_Data(CDate_Time, &buf[SPTRecentClock_O], &DataLen, &V_usDataEncode);
				buf[Key0204_ErrNum_O] = 0;
				break;
			}
			default:			/*入口参数错，啥也不干直接返回OK*/
				return(ReturnCode);
		}
/*返写全局SPT，并计算CRC*/
	KEY02ErrNum = buf[Key02_ErrNum_O];
	KEY04ErrNum = buf[Key04_ErrNum_O];
	SPTNum = buf[SPTNum_O];
	PF_CopyDataBytes(&buf[SPTRecentClock_O], SPTRecentClock, CLDate_Time);
	SPTCrc = PF_Cal_CRC(buf,(CLen_Str_SPT - 2));
	return(ReturnCode);
}
/***************************************************************************
函数原型 	Is_Buf_AllZero
函数功能	判断缓冲区数据是否为全0
输入参数	pData		缓冲区首地址
				DataLen		数据长度
输出参数 	无
返回参数	C_OK		数据全等于0
				C_Error		数据有不全等于0或入口参数错误
全局变量 	无
函数备注
***************************************************************************/
uchar8		Is_Buf_AllZero(uchar8	*pData, uchar8	DataLen)
{
	uchar8	i;

	if(DataLen != 0)
	{
		for(i = 0; i < DataLen; i++ )
		{
			if( pData[i] != 0 )
			{
				break;
			}
		}
		if(i == DataLen)
		{
			return(C_OK);
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
/***************************************************************************
函数原型 	Comm_SendMsg
函数功能	通信发送消息给其他模块
输入参数	*pParm			:消息中的参数域
				ParmLen			:参数域长度,注意这个长度包含PT
输出参数 	无
返回参数	无
全局变量 	调度的消息队列
函数备注
***************************************************************************/
void	Comm_SendMsg(uchar8 *pParm, uchar8 ParmLen, uchar8 DestMsg)
{
	Str_Msg_Parameter	MsgParm;

	MsgParm.DerictAddr = DestMsg;
	MsgParm.SourceAddr = C_Msg_Communication;
	MsgParm.Parameter = pParm;
	MsgParm.Length = ParmLen;
	InF_WriteMessege(&MsgParm);
}

/***************************************************************************
函数原型 	Comm_SendMsgForUpdataParm
函数功能	发送参数更新消息
输入参数	ParmType			:更新的参数类型。
					取值		:  C_ReWorkTime			时间更改
							        : C_ReDemand_Cycle		需量周期更改
							        : C_ReMultiRatesParm		时段费率等参数修改
							        : C_ReSettle_Day1			第1结算日修改
输出参数 	无
返回参数	无
全局变量 	调度的消息队列
函数备注
***************************************************************************/
void		Comm_SendMsgForUpdataParm(uchar8	ParmType, uchar8	DestMsg)
{
	Str_Msg_Parameter	MsgParm;
	uchar8	buf[2];

	MsgParm.DerictAddr = DestMsg;
	MsgParm.SourceAddr = C_Msg_Communication;
	MsgParm.Parameter = buf;
	MsgParm.Length = Pt_ParaMetersChange_Len + 1;
	buf[0] = Pt_ParaMetersChange;
	buf[1] = ParmType;
	InF_WriteMessege(&MsgParm);
}

/***************************************************************************
函数原型 	Comm_SendMsgToDisp
函数功能	完成发消息给显示模块处理一个字符。
输入参数	DispSign				:处理字符名称
				DispMode				:处理方式C_TwinkleDisplay/C_AlwaysDisplay/C_NotDisplay
				Duration				:持续时间C_Duration_Alway表示一直这样。
输出参数 	无
返回参数	无
全局变量 	无
函数备注
***************************************************************************/
void	Comm_SendMsgToDisp(uchar8 DispSign, uchar8	DispMode, ushort16 Duration)
{
	Str_Msg_Parameter	MsgParm;
	uchar8	buf[4];

	MsgParm.DerictAddr = C_Msg_Display;
	MsgParm.SourceAddr = C_Msg_Communication;
	buf[0] = Pt_DisplayStatus;
	buf[1] = DispSign | DispMode;
	PF_Ushort16ToBuffer2(&buf[2], &Duration);
	MsgParm.Parameter = buf;
	MsgParm.Length = Pt_DisplayStatus_Len + 1;
    InF_WriteMessege(&MsgParm);
}

/***************************************************************************
函数原型 	Init_SV_CommNxtFrame
函数功能	初始化全局静态变量SV_CommNxtFrame_XX。实际就是封装了通道的判断。
输入参数	CommNo					:通道号

输出参数 	无
返回参数	无
全局变量 	SV_CommNxtFrame_XX
函数备注
***************************************************************************/
void		Init_SV_CommNxtFrame (uchar8	CommNo)
{
	Str_Comm_NxtFrame	*pStr_Comm_NxtFrame;
	uchar8	i;

	switch(CommNo)
	{
		case		C_RS485_1:
			pStr_Comm_NxtFrame = &SV_CommNxtFrame_RS485_1;
			break;
		case		C_RS485_2:
			pStr_Comm_NxtFrame = &SV_CommNxtFrame_RS485_2;
			break;
		case		C_IR:
			pStr_Comm_NxtFrame = &SV_CommNxtFrame_IR;
			break;
		case		C_Module:
			pStr_Comm_NxtFrame = &SV_CommNxtFrame_Module;
			break;
		default:
			return;
	}

	NxtF_DataCode = 0xFFFFFFFF;

	NxtF_HaveReport = C_Error;
	NxtF_FrameFinished = C_Error;

	NxtF_FrameNo = 1;

	NxtF_Nxt_DataCode = 0;
	NxtF_Sub_DataCode = 0;

	for( i = 0; i < LClockLen; i++ )
	{
		NxtF_LNxt_Fix_Time[i] = 0;
		NxtF_LSub_Fix_Time[i] = 0;
	}
	NxtF_LNxt_BlockNum = 0;
	NxtF_LSub_BlockNum = 0;

	for( i = 0; i < CLen_CREnergy; i++ )
	{
		NxtF_LNxt_CREnergy[i] = 0;
		NxtF_LSub_CREnergy[i] = 0;
	}

	return;
}

/***************************************************************************
函数原型 	Set_SV_CommNxtFrame
函数功能	设置后续帧通道变量
输入参数	CommNo				:通道号
				*pStr_Comm_NxtFrame	:准备写的值
输出参数 	无
返回参数	无
全局变量 	SV_CommNxtFrame_XX
函数备注
***************************************************************************/
void		Set_SV_CommNxtFrame (uchar8 CommNo, Str_Comm_NxtFrame *pNxtFrame)
{
	Str_Comm_NxtFrame	*pStr_Comm_NxtFrame;
	uchar8	i;

	switch(CommNo)
	{
		case		C_RS485_1:
			pStr_Comm_NxtFrame = &SV_CommNxtFrame_RS485_1;
			break;
		case		C_RS485_2:
			pStr_Comm_NxtFrame = &SV_CommNxtFrame_RS485_2;
			break;
		case		C_IR:
			pStr_Comm_NxtFrame = &SV_CommNxtFrame_IR;
			break;
		case		C_Module:
			pStr_Comm_NxtFrame = &SV_CommNxtFrame_Module;
			break;
		default:
			return;
	}
	NxtF_DataCode = pNxtFrame->DataCode;
	NxtF_FrameNo = pNxtFrame->FrameNo;

	NxtF_HaveReport= pNxtFrame->HaveReport;

	NxtF_FrameFinished =  pNxtFrame->FrameFinished;

	NxtF_Nxt_DataCode = pNxtFrame->Nxt_DataCode;
	NxtF_Sub_DataCode = pNxtFrame->Sub_DataCode;

	for( i = 0; i < LClockLen; i++ )
	{
		NxtF_LNxt_Fix_Time[i] = pNxtFrame->LNxt_Fix_Time[i];
		NxtF_LSub_Fix_Time[i] = pNxtFrame->LSub_Fix_Time[i];
	}
	for( i = 0; i < CLen_CREnergy; i++ )
	{
		NxtF_LNxt_CREnergy[i] =  pNxtFrame->LNxt_CREnergy[i];
		NxtF_LSub_CREnergy[i] = pNxtFrame->LSub_CREnergy[i];
	}

	NxtF_LNxt_BlockNum = pNxtFrame->LNxt_BlockNum;
	NxtF_LSub_BlockNum = pNxtFrame->LSub_BlockNum;
    NxtF_LNxt_TotalBlockNum = pNxtFrame->TotalBlockNum;
    NxtF_LNxt_ReadedBlockNum = pNxtFrame->ReadedBlockNum;

	return;
}
/***************************************************************************
函数原型 	Get_SV_CommNxtFrame
函数功能	获取通道SV_CommNxtFrame值。实际就是封装了通道的判断。
输入参数	CommNo				:通道号
				pNxtFrame			:待写的Str_Comm_NxtFrame指针
输出参数 	*pNxtFrame			:值
返回参数	C_OK/C_Error
全局变量 	无
函数备注
***************************************************************************/
uchar8		Get_SV_CommNxtFrame (uchar8 CommNo, Str_Comm_NxtFrame *pNxtFrame)
{
	Str_Comm_NxtFrame	*pStr_Comm_NxtFrame;
	uchar8	i;

	switch(CommNo)
	{
		case		C_RS485_1:
			pStr_Comm_NxtFrame = &SV_CommNxtFrame_RS485_1;
			break;
		case		C_RS485_2:
			pStr_Comm_NxtFrame = &SV_CommNxtFrame_RS485_2;
			break;
		case		C_IR:
			pStr_Comm_NxtFrame = &SV_CommNxtFrame_IR;
			break;
		case		C_Module:
			pStr_Comm_NxtFrame = &SV_CommNxtFrame_Module;
			break;
		default:
			return(C_Error);
	}
	pNxtFrame->DataCode = NxtF_DataCode;
	pNxtFrame->FrameNo = NxtF_FrameNo;

	pNxtFrame->Nxt_DataCode = NxtF_Nxt_DataCode;
	pNxtFrame->Sub_DataCode = NxtF_Sub_DataCode;

	pNxtFrame->HaveReport = NxtF_HaveReport;

	pNxtFrame->FrameFinished = NxtF_FrameFinished;

	for( i = 0; i < LClockLen; i++ )
	{
		pNxtFrame->LNxt_Fix_Time[i] = NxtF_LNxt_Fix_Time[i];
		pNxtFrame->LSub_Fix_Time[i] = NxtF_LSub_Fix_Time[i];
	}
	for( i = 0; i < CLen_CREnergy; i++ )
	{
		pNxtFrame->LNxt_CREnergy[i] = NxtF_LNxt_CREnergy[i];
		pNxtFrame->LSub_CREnergy[i] = NxtF_LSub_CREnergy[i];
	}

	pNxtFrame->LNxt_BlockNum = NxtF_LNxt_BlockNum;
	pNxtFrame->LSub_BlockNum = NxtF_LSub_BlockNum;

    pNxtFrame->TotalBlockNum = NxtF_LNxt_TotalBlockNum;
    pNxtFrame->ReadedBlockNum = NxtF_LNxt_ReadedBlockNum;
	return(C_OK);
}
/***************************************************************************
函数原型 	Comm_A_MsgToDispatchQueue_UpKeyR
函数功能	触发密钥更新检查消息到调度队列
输入参数	PT_Type				:PT_CMsg_UpdataKey_Review/PT_CMsg_UpdKey_Rv_PWOn

输出参数 	无
返回参数	无
全局变量 	调度队列
函数备注
***************************************************************************/
void		Comm_A_MsgToDispatchQueue_UpKeyR(uchar8 PT_Type)
{
	uchar8	pParm[2];

	pParm[0] = PT_Type;
	Comm_SendMsg(pParm, (PT_CMsg_UpdataKey_Review_Len + 1), C_Msg_Communication);
}
/***************************************************************************
函数原型 	Get_Str_Comm_Parm_Pointer
函数功能	根据通道号，返回Str_Comm_Parm型指针值
输入参数	CommNo：				通道号


输出参数
返回参数	存放Str_Comm_Parm指针值，如果通道号错，返回C_NULL
全局变量
函数备注
***************************************************************************/
Str_Comm_Parm	* Get_Str_Comm_Parm_Pointer(uchar8 CommNo)
{
	Str_Comm_Parm	*pStr_Comm_Parm_Address;

	switch(CommNo)
	{
		case		C_RS485_2:
			pStr_Comm_Parm_Address = &SV_RS485_2_Comm_Parm;
			break;
		case		C_IR:
			pStr_Comm_Parm_Address = &SV_IR_Comm_Parm;
			break;
		case		C_Module:
			pStr_Comm_Parm_Address = &SV_Module_Parm;
			break;
		default:
			pStr_Comm_Parm_Address = &SV_RS485_1_Comm_Parm;
			break;
	}
	return(pStr_Comm_Parm_Address);
}

/***************************************************************************
函数原型 	Init_Str_Comm_Parm
函数功能	完成Str_Comm_Parm型变量的初始化
输入参数	CommNo:		通道号

输出参数 	无
返回参数	无
全局变量 	Str_Comm_Parm型变量
函数备注
***************************************************************************/
void	Init_Str_Comm_Parm(uchar8	CommNo)
{
	Str_Comm_Parm	*pStr_Comm_Parm_Address;

	pStr_Comm_Parm_Address = Get_Str_Comm_Parm_Pointer(CommNo);
	if(pStr_Comm_Parm_Address == C_NULL)
	{
		return;
	}
	CommLen = 0;
	CommLen645 = 0;
	CommOffset = 0;
	CommRecFlag = 0;
	CommRecFlag645 = 0;
	CommOTimer = 0;
    CommProtocolType = C_ProtocolType_Init;
    CommProtocolType645 = C_ProtocolType_Init;
}
/***************************************************************************
函数原型 	Comm_ParseInit
函数功能	完成Comm_Parse模块初始化
输入参数	无

输出参数 	无
返回参数	无
全局变量 	SV_Comm_Parse_Local
函数备注
调用时机	1、Comm_Parse函数，一进去首先初始化。
				2、定时消息中，每次都调用初始化
				3、上电初始化函数中。Comm_ForPowerOn
				4、请注意调度是不调用本函数。
				5、SV_Comm_Parse变量原本在这里初始化，现在
					由于CRC采取下级CRC，使用时判断，所以这里
					不初始化了。在上电初始化函数中初始化。
***************************************************************************/
void Comm_ParseInit(void)
{
	SV_Comm_Parse_Local.MessageFlag = 0;
	SV_Comm_Parse_Local.MeterClearFlag = 0;
	SV_Comm_Parse_Local.SafeControlFlag = 0;
	SV_Comm_Parse_Local.ClientAddrFlag = 0;/*增加终端与主战客户机地址的区分*/
}

/***************************************************************************
函数原型 	uchar8 SF_BPS698transfor645(uchar8 bps698)
函数功能	波特率转换
输入参数	698波特率特征字

输出参数 	645的波特率特征字
返回参数	无
全局变量 	Str_Comm_Parm型全局变量
函数备注
***************************************************************************/
uchar8 SF_BPS698transfor645(uchar8 bps698)
{
    uchar8 bps;

	switch(bps698)
	{
		case		C_bps_300_698:
			bps = C_bps_300;
			break;
		case		C_bps_600_698:
			bps = C_bps_600;
			break;
		case		C_bps_1200_698:
			bps = C_bps_1200;
			break;
		case		C_bps_2400_698:
			bps = C_bps_2400;
			break;
		case		C_bps_4800_698:
			bps = C_bps_4800;
			break;
		case		C_bps_9600_698:
			bps = C_bps_9600;
			break;
		case		C_bps_19200_698:
			bps = C_bps_19200;
			break;
		case		C_bps_38400_698:
			bps = C_bps_38400;
			break;
		default:
			bps = C_bps_9600;
			break;;
	}
    return bps;
}

/***************************************************************************
函数原型 	uchar8 SF_BPS698transfor645(uchar8 bps698)
函数功能	波特率转换
输入参数	698波特率特征字

输出参数 	645的波特率特征字
返回参数	无
全局变量 	Str_Comm_Parm型全局变量
函数备注
***************************************************************************/
uchar8 SF_BPS645transfor698(uchar8 bps645)
{
    uchar8 bps;

	switch(bps645)
	{
		case		C_bps_300:
			bps = C_bps_300_698;
			break;
		case		C_bps_600:
			bps = C_bps_600_698;
			break;
		case		C_bps_1200:
			bps = C_bps_1200_698;
			break;
		case		C_bps_2400:
			bps = C_bps_2400_698;
			break;
		case		C_bps_4800:
			bps = C_bps_4800_698;
			break;
		case		C_bps_9600:
			bps = C_bps_9600_698;
			break;
		case		C_bps_19200:
			bps = C_bps_19200_698;
			break;
		case		C_bps_38400:
			bps = C_bps_38400_698;
			break;
		default:
			bps = C_bps_Error;
			break;;
	}
    return bps;
}

/***************************************************************************
函数原型 	InF_InitComm
函数功能	初始化硬件串口及该串口对应的通道全局变量
输入参数	CommNum:	串口编号

输出参数 	无
返回参数	无
全局变量 	Str_Comm_Parm型全局变量
函数备注
***************************************************************************/
void InF_InitComm(uchar8 CommNo)
{
	ulong32	bpsDataCode;
	uchar8	V_ReturnData;
	uchar8	bps;
	uchar8	bpsDefault;
    uchar8  CommDataLen, StpLen, parityChk, bpsData[5];
	ushort16  DataLen, V_usDataEncode;

/*初始化硬件串口*/
/*取串口波特率*/
	switch(CommNo)
	{
		case		C_RS485_1:
		{
			bpsDataCode = COne485_Baud;
			bpsDefault = C_bps_9600;
		}break;
		case		C_RS485_2:
		{
			bpsDataCode = CTwo485_Baud;
			bpsDefault = C_bps_9600;
		}break;
		case		C_IR:
		{
			bpsDataCode = CMod_InFr_Baud;
			bpsDefault = C_bps_1200;
		}break;
		case		C_Module:
		{
			bpsDataCode = CModular_Baud;
			bpsDefault = C_bps_9600;
		}break;
		default:
			return;
	}
	DataLen = CLOne485_Baud;
	V_ReturnData = InF_Read_Data(bpsDataCode, bpsData, &DataLen, &V_usDataEncode);

    bps = SF_BPS698transfor645(bpsData[0]);

	parityChk = bpsData[1];
	CommDataLen = bpsData[2];
	StpLen = bpsData[3];

	if( ( V_ReturnData != C_OK ) || ( Is_CommBPS_OK( CommNo, bpsData[0] ) != C_OK ) )
	{
		bps = bpsDefault;
		parityChk = C_parity_Even;
		CommDataLen = C_CommDataLen8;
		StpLen = C_SerStp_2;
	}
	if( ( InF_JudgeIJTimer() == C_OK ) && ( ( CommNo == C_RS485_1 ) || ( CommNo == C_RS485_2 ) ) )
	{
		bps = C_bps_9600;
	}


	InF_InitCommUartForDispatch(CommNo, bps, CommDataLen, StpLen, parityChk);

/*初始化通道交互变量*/
	Init_Str_Comm_Parm(CommNo);
}

/***************************************************************************
函数原型 	Comm_WR_TxData_ToCtrbyte
函数功能	完成写通讯缓冲区4个FE到控制字。
输入参数	pStr_Comm_Parm_Address		:待处理的通信缓冲区
输出参数 	Rx_CtrByte					:接收到的控制字
返回参数	无
全局变量 	Str_Comm_Parm型变量
函数备注	复旦微RTC调校非645格式，特殊处理
***************************************************************************/
void		Comm_WR_TxData_ToCtrbyte1(Str_Comm_Parm *pStr_Comm_Parm_Address, uchar8 Rx_CtrByte)
{
	ushort16	i, V_usDataEncode;

	CommLen645 = 0;
/*赋值4个FE*/
	CommBuff[C_FE_OFS_ForTx] = 0xFE;
	CommLen645 ++;
	CommBuff[C_FE_OFS_ForTx + 1] = 0xFE;
	CommLen645 ++;
	CommBuff[C_FE_OFS_ForTx + 2] = 0xFE;
	CommLen645 ++;
	CommBuff[C_FE_OFS_ForTx + 3] = 0xFE;
	CommLen645 ++;

/*赋值第1个0x68*/
	CommBuff[C_68_1_OFS_ForTx] = 0x68;
	CommLen645 ++;
/*取通信地址*/
	for( i = 0; i < CLComm_Address; i++ )
	{
		CommBuff[C_CAddr_OFS_ForTx + i] = 0;
	}

	InF_Read_Data(CComm_Address, &CommBuff[C_CAddr_OFS_ForTx], &i, &V_usDataEncode);
	CommLen645 = CommLen645 + i;
/*赋值第2个0x68*/
	CommBuff[C_68_2_OFS_ForTx] = 0x68;
	CommLen645 ++;
/*赋值C*/
	CommBuff[C_C_OFS_ForTx] = Rx_CtrByte;
	CommLen645 ++;
	return;
}
/***************************************************************************
函数原型 	Comm_WR_TxData_ToCtrbyte
函数功能	完成写通讯缓冲区4个FE到控制字。
输入参数	pStr_Comm_Parm_Address		:待处理的通信缓冲区
输出参数 	Rx_CtrByte					:接收到的控制字
返回参数	无
全局变量 	Str_Comm_Parm型变量
函数备注	1、这里控制只是置原值或上0x80.应答。
				2、总的Len同步赋值
				2级置发送函数，被一级置发送函数调用
***************************************************************************/
void		Comm_WR_TxData_ToCtrbyte(Str_Comm_Parm *pStr_Comm_Parm_Address, uchar8 Rx_CtrByte)
{
	ushort16	i, V_usDataEncode;

	CommLen645 = 0;
/*赋值4个FE*/
	CommBuff[C_FE_OFS_ForTx] = 0xFE;
	CommLen645 ++;
	CommBuff[C_FE_OFS_ForTx + 1] = 0xFE;
	CommLen645 ++;
	CommBuff[C_FE_OFS_ForTx + 2] = 0xFE;
	CommLen645 ++;
	CommBuff[C_FE_OFS_ForTx + 3] = 0xFE;
	CommLen645 ++;

/*赋值第1个0x68*/
	CommBuff[C_68_1_OFS_ForTx] = 0x68;
	CommLen645 ++;
/*取通信地址*/
	for(i = 0; i < CLComm_Address; i++ )
	{
		CommBuff[C_CAddr_OFS_ForTx + i] = 0;
	}
	InF_Read_Data(CComm_Address, &CommBuff[C_CAddr_OFS_ForTx], &i, &V_usDataEncode);
	CommLen645 = CommLen645 + i;
/*赋值第2个0x68*/
	CommBuff[C_68_2_OFS_ForTx] = 0x68;
	CommLen645 ++;
/*赋值C*/
	CommBuff[C_C_OFS_ForTx] = Rx_CtrByte | 0x80;
	CommLen645 ++;
	return;
}

/***************************************************************************
函数原型 	Comm_Response_Set_ReadErr
函数功能	完成Set(write(14)、（Action）特殊命令)的应答及读取的错误应答。
				直接置Str_Comm_Parm型全局变量。
输入参数	Err				:通讯错误类型；=C_Ok表示正确应答
				*pV_645Frame		:接收到已解析的645帧
输出参数 	无
返回参数	无
全局变量	Str_Comm_Parm型变量
函数备注	到这里为止，所有应答帧中的数据，除CS，16外都已经置好。包括645Len
				1级置发送函数除CS、16以外(这2项在发送消息处理时置)，包括发送消息标志都已置。
***************************************************************************/
void		Comm_Response_Set_ReadErr(uchar8  Err, Str_Comm_645 *pV_645Frame)
{
	Str_Comm_Parm *pStr_Comm_Parm_Address;

	pStr_Comm_Parm_Address = Get_Str_Comm_Parm_Pointer(pV_645Frame->ChannelNo);
	if(pStr_Comm_Parm_Address == C_NULL)
	{
		return;		/*通道错，这实际不可能。发生了，也不发送，直接退出。*/
	}

	Comm_WR_TxData_ToCtrbyte(pStr_Comm_Parm_Address, (pV_645Frame->C));

	if(Err == C_OK)
	{
		/*设置正确FE FE FE FE 68 A0-A5 68 (C|0x80) 00 */
		CommBuff[C_L_OFS_ForTx] = 0;		/*长度为0	*/
		CommLen645 ++;
	}
	else
	{
		CommBuff[C_C_OFS_ForTx] = CommBuff[C_C_OFS_ForTx] | 0x40;
		CommBuff[C_L_OFS_ForTx] = 1;		/*长度为1*/
		CommLen645 ++;
		CommBuff[C_Data_OFS_ForTx] =  Err;
		CommLen645 ++;
	}

	Comm_AppendMsg(CMsg_Txd);
	return;
}

/***************************************************************************
函数原型 	Comm_Response_03_Err
函数功能	完成03 特殊命令的错误应答。
				直接置Str_Comm_Parm型全局变量。
输入参数	Err				:通讯错误类型；
				*pV_645Frame		:接收到已解析的645帧
输出参数 	无
返回参数	无
全局变量	Str_Comm_Parm型变量
函数备注	到这里为止，所有应答帧中的数据，除CS，16外都已经置好。包括645Len
				1级置发送函数除CS、16以外(这2项在发送消息处理时置)，包括发送消息标志都已置。
***************************************************************************/
void		Comm_Response_03_Err(ushort16  SERR, Str_Comm_645 *pV_645Frame)
{
	Str_Comm_Parm *pStr_Comm_Parm_Address;

	pStr_Comm_Parm_Address = Get_Str_Comm_Parm_Pointer(pV_645Frame->ChannelNo);
	if(pStr_Comm_Parm_Address == C_NULL)
	{
		return;		/*通道错，这实际不可能。发生了，也不发送，直接退出。*/
	}

	Comm_WR_TxData_ToCtrbyte(pStr_Comm_Parm_Address, (pV_645Frame->C));

	CommBuff[C_C_OFS_ForTx] = CommBuff[C_C_OFS_ForTx] | 0x40;	/*控制字或上错误标志*/

	CommBuff[C_L_OFS_ForTx] = 2;		/*长度为2*/
	CommLen645 ++;
	PF_Ushort16ToBuffer2(&CommBuff[C_Data_OFS_ForTx] , &SERR);
	CommLen645 ++;
	CommLen645 ++;
	Comm_AppendMsg(CMsg_Txd);
	return;
}
/***************************************************************************
函数原型 	Comm_RTC1E_Response_Normal(Str_Comm_645 *pV_645Frame,uchar8	*pData,uchar8 DataLen)
函数功能	复旦微RTC 1E读数据命令，非645格式应答帧。(除CS、16外所有数据)
输入参数	*pV_645Frame		:接收到已解析的645帧
				pData:			:正常应答DI后的数据 首地址
				DataLen			:pData数据长度
输出参数 	无
返回参数	无
全局变量	Str_Comm_Parm型变量
函数备注	到这里为止，所有应答帧中的数据，除CS，16外都已经置好。包括645Len
				1级置发送函数除CS、16以外(这2项在发送消息处理时置)，包括发送消息标志都已置。
***************************************************************************/
void		Comm_RTC1E_Response_Normal(Str_Comm_645 *pV_645Frame, uchar8	*pData, uchar8 DataLen)
{
	uchar8	i;
	Str_Comm_Parm *pStr_Comm_Parm_Address;

	pStr_Comm_Parm_Address = Get_Str_Comm_Parm_Pointer(pV_645Frame->ChannelNo);
	if(pStr_Comm_Parm_Address ==C_NULL)
	{
		return;		/*通道错，这实际不可能。发生了，也不发送，直接退出。*/
	}
/*FE->C*/
	Comm_WR_TxData_ToCtrbyte1(pStr_Comm_Parm_Address, (pV_645Frame->C));
/*L*/
	CommBuff[C_L_OFS_ForTx] = 4 + DataLen;		/*正常应答至少为4字节，DI*/
	CommLen645 ++;
/*DI  数据域-0x33，复旦微非645格式*/
	CommBuff[C_Data_OFS_ForTx] = pV_645Frame->Data[CDI_O_V_645] - 0x33;
	CommBuff[C_Data_OFS_ForTx + 1] = pV_645Frame->Data[CDI_O_V_645 + 1] - 0x33;
	CommBuff[C_Data_OFS_ForTx + 2] = pV_645Frame->Data[CDI_O_V_645 + 2] - 0x33;
	CommBuff[C_Data_OFS_ForTx + 3] = pV_645Frame->Data[CDI_O_V_645 + 3] - 0x33;
	CommLen645 = CommLen645 + 4;
/*data*/
	if( ( DataLen != 0 ) && ( DataLen < C_Comm_Data_MaxLen ) )
	{
		for( i = 0; i < DataLen; i++ )
		{
			CommBuff[C_Data_OFS_ForTx + 4 + i] = pData[i] - 0x33;
			CommLen645++;
		}
	}

	Comm_AppendMsg(CMsg_Txd);
	return;
}

/***************************************************************************
函数原型 	Comm_11_03Response_Normal
函数功能	复旦微RTC 1F时钟调校命令，非645格式应答帧。(除CS、16外所有数据)
输入参数	*pV_645Frame		:接收到已解析的645帧
				pData:			:正常应答DI后的数据 首地址
				DataLen			:pData数据长度
输出参数 	无
返回参数	无
全局变量	Str_Comm_Parm型变量
函数备注	到这里为止，所有应答帧中的数据，除CS，16外都已经置好。包括645Len
				1级置发送函数除CS、16以外(这2项在发送消息处理时置)，包括发送消息标志都已置。
***************************************************************************/
void		Comm_RTC1F_Response_Normal(Str_Comm_645 *pV_645Frame, uchar8	*pData, uchar8 DataLen)
{
	uchar8	i;
	Str_Comm_Parm *pStr_Comm_Parm_Address;

	pStr_Comm_Parm_Address = Get_Str_Comm_Parm_Pointer(pV_645Frame->ChannelNo);
	if(pStr_Comm_Parm_Address ==C_NULL)
	{
		return;		/*通道错，这实际不可能。发生了，也不发送，直接退出。*/
	}
/*FE->C*/
	Comm_WR_TxData_ToCtrbyte(pStr_Comm_Parm_Address, (pV_645Frame->C));
/*L*/
	CommBuff[C_L_OFS_ForTx] = DataLen;		/*数据长度已包含DI*/
	CommLen645 ++;

/*data*/
	if( ( DataLen != 0 ) && ( DataLen < C_Comm_Data_MaxLen ) )
	{
		for( i = 0; i < DataLen; i++ )
		{
			CommBuff[C_Data_OFS_ForTx + i] = pData[i];
			CommLen645++;
		}
	}

	Comm_AppendMsg(CMsg_Txd);
	return;
}
/***************************************************************************
函数原型 	Comm_11_03Response_Normal
函数功能	完成03/11命令正常应答帧组帧。(除CS、16外所有数据)
输入参数	*pV_645Frame		:接收到已解析的645帧
				pData:			:正常应答DI后的数据 首地址
				DataLen			:pData数据长度
输出参数 	无
返回参数	无
全局变量	Str_Comm_Parm型变量
函数备注	到这里为止，所有应答帧中的数据，除CS，16外都已经置好。包括645Len
				1级置发送函数除CS、16以外(这2项在发送消息处理时置)，包括发送消息标志都已置。
***************************************************************************/
void		Comm_11_03Response_Normal(Str_Comm_645 *pV_645Frame, uchar8	*pData, uchar8 DataLen)
{
	uchar8	i;
	Str_Comm_Parm *pStr_Comm_Parm_Address;

	pStr_Comm_Parm_Address = Get_Str_Comm_Parm_Pointer(pV_645Frame->ChannelNo);
	if(pStr_Comm_Parm_Address ==C_NULL)
	{
		return;		/*通道错，这实际不可能。发生了，也不发送，直接退出。*/
	}
/*FE->C*/
	Comm_WR_TxData_ToCtrbyte(pStr_Comm_Parm_Address, (pV_645Frame->C));
/*L*/
	CommBuff[C_L_OFS_ForTx] = 4 + DataLen;		/*正常应答至少为4字节，DI*/
	CommLen645 ++;
/*DI*/
	CommBuff[C_Data_OFS_ForTx] = pV_645Frame->Data[CDI_O_V_645];
	CommBuff[C_Data_OFS_ForTx + 1] = pV_645Frame->Data[CDI_O_V_645 + 1];
	CommBuff[C_Data_OFS_ForTx + 2] = pV_645Frame->Data[CDI_O_V_645 + 2];
	CommBuff[C_Data_OFS_ForTx + 3] = pV_645Frame->Data[CDI_O_V_645 + 3];
	CommLen645 = CommLen645 + 4;
/*data*/
	if( ( DataLen != 0 ) && ( DataLen < C_Comm_Data_MaxLen ) )
	{
		for( i = 0; i < DataLen; i++ )
		{
			CommBuff[C_Data_OFS_ForTx + 4 + i] = pData[i];
			CommLen645++;
		}
	}

	Comm_AppendMsg(CMsg_Txd);
	return;
}
/***************************************************************************
函数原型 	Comm_Response_FromP_Normal
函数功能	完成从指定指针开始数据的应答(除CS、16外所有数据)
				和Comm_11_03Response_Normal比，少了个DI赋值
输入参数	*pV_645Frame		:接收到已解析的645帧
				pData:			:L后一个字节数据首地址
				DataLen			:pData数据长度
输出参数 	无
返回参数	无
全局变量	Str_Comm_Parm型变量
函数备注	到这里为止，所有应答帧中的数据，除CS，16外都已经置好。包括645Len
				1级置发送函数除CS、16以外(这2项在发送消息处理时置)，包括发送消息标志都已置。
***************************************************************************/
void		Comm_Response_FromP_Normal(Str_Comm_645 * pV_645Frame, uchar8	*pData, uchar8 DataLen)
{
	uchar8	i;
	Str_Comm_Parm *pStr_Comm_Parm_Address;

	pStr_Comm_Parm_Address = Get_Str_Comm_Parm_Pointer(pV_645Frame->ChannelNo);
	if(pStr_Comm_Parm_Address == C_NULL)
	{
		return;		/*通道错，这实际不可能。发生了，也不发送，直接退出。*/
	}
/*FE->C*/
	Comm_WR_TxData_ToCtrbyte(pStr_Comm_Parm_Address, (pV_645Frame->C));
/*L*/
	CommBuff[C_L_OFS_ForTx] = DataLen;
	CommLen645 ++;

/*data*/
	if( ( DataLen != 0 ) && ( DataLen < C_Comm_Data_MaxLen ) )
	{
		for( i = 0; i < DataLen; i++ )
		{
			CommBuff[C_Data_OFS_ForTx + i] = pData[i];
			CommLen645++;
		}
	}

	Comm_AppendMsg(CMsg_Txd);
	return;
}
/***************************************************************************
函数原型 	Comm_IfHaveNxtFrame_Set_C
函数功能	判断有后续帧时，调用，置通信发送缓冲区中C有后续帧
输入参数	pV_645Frame					:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	对应的通信发送缓冲区中C
函数备注	1、有无后续帧在外面判断
				2、通信缓冲区中从至少FE-C已经置好。
***************************************************************************/
void		Comm_IfHaveNxtFrame_Set_C(Str_Comm_645 *pV_645Frame)
{
	Str_Comm_Parm *pStr_Comm_Parm_Address;

	pStr_Comm_Parm_Address = Get_Str_Comm_Parm_Pointer(pV_645Frame->ChannelNo);
	if(pStr_Comm_Parm_Address ==C_NULL)
	{
		return;														/*通道错，这实际不可能。发生了，也不发送，直接退出。*/
	}
	if( ( CommBuff[C_C_OFS_ForTx] & 0x40 ) == 0x00 )				/*正确应答的情况下才将读后续标志值1*/
	{
		CommBuff[C_C_OFS_ForTx] = CommBuff[C_C_OFS_ForTx] | 0x20;	/*bit5是有后续帧标志*/
	}
}

/***************************************************************************
函数原型 	Comm_SetFrameNo
函数功能	在帧尾添加帧序号
输入参数	CommNo						:通道缓冲区
				FrameNo						:帧序号
输出参数 	无
返回参数	无
全局变量 	对应的通信发送缓冲区
函数备注
***************************************************************************/
void	Comm_SetFrameNo(uchar8	CommNo,uchar8	FrameNo)
{
	Str_Comm_Parm *pStr_Comm_Parm_Address;

	pStr_Comm_Parm_Address = Get_Str_Comm_Parm_Pointer(CommNo);
	if(pStr_Comm_Parm_Address ==C_NULL)
	{
		return;								/*通道错，这实际不可能。发生了，也不发送，直接退出。*/
	}
	if( CommLen645 > ( C_Comm_Buf_MaxLen - 3 ) )
	{
		return;								/*缓冲区溢出*/
	}
	CommBuff[CommLen645] = FrameNo;
	CommLen645++;							/*总长度调整*/
	CommBuff[C_L_OFS_ForTx]++;				/*数据域长度调整*/
}

/***************************************************************************
函数原型 	GetCommMeterAddressType
函数功能	获取表地址类型
输入参数	*pCommMAdrress			:通信带过来的表地址
输出参数 	无
返回参数	C_MeterAddress/C_Broadcast/C_Condense_AA_All/C_Condense_AA/C_AdrressError
全局变量 	无
函数备注	如果数据层表地址读不出，能支持全99或全AA，或全0(全0认为全表号)，
***************************************************************************/
uchar8	GetCommMeterAddressType(uchar8	*pCommMAdrress)
{
	ushort16	i, V_usDataEncode;
	uchar8	V_ReturnData;
	uchar8	MeterAddress[CLComm_Address];
	uchar8	V_AANum;
	uchar8	V_MeterAddrNum;

/*判断表地址是否为全99*/
	for( i = 0; i < CLComm_Address; i++ )
	{
		if(pCommMAdrress[i] != 0x99)
		{
			break;
		}
	}
	if(i == CLComm_Address)
	{
		return(C_Broadcast);		/*广播*/
	}

/*取表通信地址，如果读不出，默认为全0*/
	i = CLComm_Address;
	V_ReturnData = InF_Read_Data(CComm_Address, MeterAddress, &i, &V_usDataEncode);
	if(V_ReturnData != C_OK)
	{
		for( i = 0; i < CLComm_Address; i++ )
		{
			MeterAddress[i] = 0;
		}
	}
/*比对表地址是否为缩位或全地址*/
	V_AANum = 0;
	V_MeterAddrNum = 0;
	for( i = 0; i < CLComm_Address; i++ )
	{
		if(V_AANum ==0)
		{/*没有判断过AA，进行全表号判断*/
			if(pCommMAdrress[i] == MeterAddress[i])
				{
					V_MeterAddrNum++;
				}
			else if(pCommMAdrress[i] == 0xAA)
				{
					V_AANum++;
				}
			else
				{
					return(C_AdrressError);
				}
		}
		else
		{/*有过0xAA，则后面必须全部是0xAA，所以这里就不判表号了*/
			if(pCommMAdrress[i] == 0xAA)
			{
				V_AANum++;
			}
			else
			{
				return(C_AdrressError);
			}
		}
	}
	if(V_MeterAddrNum == CLComm_Address)
	{/*全表号*/
		return(C_MeterAddress);
	}
	if(V_AANum == CLComm_Address)
	{/*全AA*/
		return(C_Condense_AA_All);
	}
	if( ( V_AANum + V_MeterAddrNum ) == CLComm_Address )
	{/*部分缩位*/
		return(C_Condense_AA);
	}
	else
	{
		return(C_AdrressError);
	}
}

/***************************************************************************
函数原型 	Cal_645CS
函数功能	计算CS
输入参数	pStartByte			:计算的首地址
				BygteLen				:待计算长度
输出参数 	无
返回参数	累积和256的模
全局变量 	无
函数备注	调用本函数必须确保长度正确，这里不判断长度合法
***************************************************************************/
uchar8		Cal_645CS(uchar8	*pStartByte, uchar8 BygteLen)
{
	uchar8	i;
	uchar8	sum = 0;

	for( i = 0; i < BygteLen; i++ )
	{
		sum = sum + pStartByte[i];
	}
	return(sum);
}
/***************************************************************************
函数原型 	Cal_645CS
函数功能	计算CS
输入参数	pStartByte			:计算的首地址
				BygteLen				:待计算长度
输出参数 	无
返回参数	累积和256的模
全局变量 	无
函数备注	调用本函数必须确保长度正确，这里不判断长度合法;
          此函数仅通信中断调用
***************************************************************************/
uchar8		Cal_645CS_CommRec(uchar8	*pStartByte, uchar8 BygteLen)
{
	uchar8	i;
	uchar8	sum = 0;

	for( i = 0; i < BygteLen; i++ )
	{
		sum = sum + pStartByte[i];
	}
	return(sum);
}

/***************************************************************************
函数原型 	If_Frame_Ok
函数功能	进行完整帧格式的判断，合法将数据置V_645Frame变量
输入参数	pV_645Frame				:待处理的接收帧
				*pStr_Comm_Parm_Address	:通信交互变量
输出参数 	 *pV_645Frame			:合法，接收下数据.
返回参数	C_OK/C_Error
全局变量 	SV_Comm_Parse_Local.RecFlag
函数备注	pV_645Frame->ChannelNo在外面置.其他本程序全部置好

***************************************************************************/
uchar8	IfFrameOkSetV_645Frame(Str_Comm_645 *pV_645Frame, Str_Comm_Parm 	*pStr_Comm_Parm_Address)
{
	uchar8	 i;
	ushort16 V_DataOffSet;

/*判断通道交互变量无2个68及16标志*/
	if(CommRecFlag645 != C_CommRecFlagForInt_Ok)
	{
		return(C_Error);
	}
	else
	{
		SV_Comm_Parse_Local.RecFlag = CommRecFlag645;
	}

/*注这里只判断表号和CS，68，16都在通信中断中判断过了*/
/*判断通信地址*/
	pV_645Frame->AddressFlag = GetCommMeterAddressType(&CommBuff[C_CAddr_OFS_ForRx]);

	if( ( pV_645Frame->AddressFlag != C_MeterAddress )
	   && ( pV_645Frame->AddressFlag != C_Broadcast )
	   && ( pV_645Frame->AddressFlag != C_Condense_AA_All )
	   && ( pV_645Frame->AddressFlag != C_Condense_AA ) )
	{
		return(C_Error);
	}
/*计算Cs是否正确.注C_Comm_FixedRxLen包含CS 16的固定长度*/
	if( Cal_645CS(&CommBuff[C_68_1_OFS_ForRx], ( C_Comm_FixedRxLen - 2 + CommBuff[C_L_OFS_ForRx] ) )
	   != CommBuff[C_Data_OFS_ForRx + CommBuff[C_L_OFS_ForRx]] )
	{
		return(C_Error);
	}

/*置V_645Frame其他值*/
/*C，不需要-0x33*/
	pV_645Frame->C = CommBuff[C_C_OFS_ForRx];

/*数据长度包括68等*/
/*数据域长度及数据域copy。注意这里长度不需要-0x33，数据需要-0x33*/
	pV_645Frame->DataLen = CommBuff[C_L_OFS_ForRx];

	for(i = 0; i < CommBuff[C_L_OFS_ForRx]; i++ )
	{
		pV_645Frame->Data[i] = CommBuff[C_Data_OFS_ForRx + i] - 0x33;
	}
/*冻结测试跑脚本程序，设置时间04000102转换成698格式设置*/
	PF_Buffer4ToUlong32(&pV_645Frame->Data[CDI_O_V_645], &( pV_645Frame->DI), 4);

	/*置pV_645Frame中操作者代码*/
	if(pV_645Frame->C != 0x14)
	{
		V_DataOffSet = COpCode_OtherO_V_645;
	}
	else
	{
		V_DataOffSet = COpcode_14O_V_645;
	}
	PF_CopyDataBytes(&pV_645Frame->Data[V_DataOffSet], &pV_645Frame->Opcode[0], 4);

	return(C_OK);
}

/***************************************************************************
函数原型 	DealWith_RstModule
函数功能	处理复位模块电源消息。并设置SV_CommParse.RstModuleParm变量
输入参数	IsPowerOn：是否有上电标志？= C_Flag_Ok有上电标志，其他值没有
输出参数 	无
返回参数	无
全局变量 	SV_CommParse.RstModuleParm
函数备注	1、上电初始化程序中调用
				2、定时解析函数中调用（500ms调用一次）
				3	上电必须对模块进行复位一次
				4、时钟跨过12:25:25时进行判断，（不跨过则不进行复位）
					a、	如果是载波模块，则进行模块复位
					b、	如果是GPRS模块，不进行模块复位
					区分是否为GPRS模块，以当天是否设置过GPRS信号区别
***************************************************************************/
ulong32 SV_ModuleResetTimer24h;   /*24h模块通道复位*/
void DealWith_RstModule( uchar8 IsPowerOnFlag )
{
	ulong32 bpsDataCode = CModular_Baud;
	uchar8 bpsData[5] = {0x06, 0x02, 0x08, 0x01, 0x00};/*9600,偶校验，8位数据，1位停止，无控制流*/
	ushort16 bpsDataLen = CLModular_Baud;
	uchar8 buf[2];
/*如果是上电，则直接复位模块一次*/
	if( ( IsPowerOnFlag == C_Flag_Ok ) || ( SV_ModuleResetTimer24h == 0 ) )
	{
		SV_ModuleResetTimer24h = C_ModuleResetTimer24h;
		InF_InitCommUartForDispatch(C_Module, C_bps_9600, C_CommDataLen8, C_SerStp_1, C_parity_Even);/*复位模块波特率*/
		InF_Write_Data(C_Msg_Communication, bpsDataCode, bpsData, bpsDataLen, C_W_SafeFlag);
		InF_SwithPeripherals(C_ModuleReset, C_On);

		buf[0] = 0;
		buf[1] = 0;
		SetGPRSSignal(&buf[0]);		/*698协议*/

		SV_Comm_Parse.RstModuleParm.IsRstModuleFlag = C_Flag_Ok;
		SV_Comm_Parse.RstModuleParm.IsSet_GPRS_Signal = C_Flag_Err;
		return;
	}
}

/***************************************************************************
函数原型 	GetAutoDispCycleTime
函数功能	获取自动轮显周期时间
输入参数	无
输出参数 	无
返回参数	自动轮显周期(HEX)
全局变量 	无
函数备注
***************************************************************************/
ushort16	GetAutoDispCycleTime(void)
{
	ushort16	Len, V_usDataEncode;
	uchar8	DispNumHex;
	uchar8	DispTimeHex;
	uchar8	V_ReturnData;
	ushort16	AutoDispCycleTime;

	Len = 1;
	V_ReturnData = InF_Read_Data(CAuto_Dis_Screen_Num, &DispNumHex, &Len, &V_usDataEncode);
	if(V_ReturnData != C_OK)
	{
		DispNumHex = 0x12;				/*读不出，默认是12屏*/
	}

	Len = 1;	/*用了宏可能会导致读的开缓冲区超出而查不出来*/
	V_ReturnData = InF_Read_Data(CPer_Dis_Screen_Time, &DispTimeHex, &Len, &V_usDataEncode);
	if(V_ReturnData != C_OK)
	{
		DispTimeHex = 5;
	}
	/*去掉BCD转HEX的操作*/


	AutoDispCycleTime =(ushort16) (DispNumHex * DispTimeHex);

	return(AutoDispCycleTime);


}
/***************************************************************************
函数原型 	LightenCommSign
函数功能	点通信符号
输入参数	CommNo				:通道号
输出参数 	无
返回参数	无
全局变量 	调度队列
函数备注	无
***************************************************************************/
void		LightenCommSign(uchar8	CommNo,uchar8	PowerFlag)
{
	ushort16	AutoDispCycleTime;

	switch(CommNo)
	{
		case		C_RS485_1:
		{
			/*电话筒及电话筒上1*/
			Comm_SendMsgToDisp(C_ComSign,C_AlwaysDisplay,C_Duration_3s_L);
			Comm_SendMsgToDisp(C_ComChannel1Sign,C_AlwaysDisplay,C_Duration_3s_L);
		}break;
		case		C_RS485_2:
		{
			/*电话筒及电话筒上2*/
			Comm_SendMsgToDisp(C_ComSign,C_AlwaysDisplay,C_Duration_3s_L);
			Comm_SendMsgToDisp(C_ComChannel2Sign,C_AlwaysDisplay,C_Duration_3s_L);
		}break;
		case		C_Module:
		{
			/*载波符号*/
			Comm_SendMsgToDisp(C_ModuleComSign,C_AlwaysDisplay,C_Duration_3s_L);
		}break;
		case		C_IR:
		{
			/*电话筒*/
			Comm_SendMsgToDisp(C_ComSign,C_AlwaysDisplay,C_Duration_3s_L);
			if(PowerFlag != C_PowerOff)			/*停电通信不点背光*/
			{/*背光*/
				AutoDispCycleTime = GetAutoDispCycleTime();
				Comm_SendMsgToDisp(C_BackLED,C_AlwaysDisplay,(AutoDispCycleTime*2));
			}
		}break;
		default:
			return;
	}
}
/***************************************************************************
函数原型 	InF_ActiveReportSetting
函数功能	完成主动上报状态的登记
输入参数	V_ucBitNum		:要修改的主动上报事件在主动上报状态字中位数
输出参数 	无
返回参数	无
全局变量
函数备注	如果模式字对应位允许设置，则对应新增次数++
				当然如果是清零，则特殊处理
***************************************************************************/
void		InF_ActiveReportSetting(uchar8	V_ucBitNum)
{
	ushort16	Crc16;
/*判断入口参数是否合法，且模式字是否允许上报 */
	if(Is_EnableReport(V_ucBitNum)!=C_OK)
	{
		return;
	}
/*判断新增次数是否数据正确，如果不正确则清零*/
	J_ReportNAN_Null_IfErrSetZero();

	if(V_ucBitNum == C_Times_MeterClear)
	{
		if(InF_JudgeKeyStatus()==CInfo_TestKey)
		{/*为测试密钥(公钥)不进行上报，私钥才进行上报*/
			return;
		}
	}
/*无发生次数数据标识的事件传FF*/
	switch(V_ucBitNum)
	{
		case		C_Times_ESAMErr:
		case		C_Times_RTCBatteryErr:
		case		C_Times_InternalProgramErr:
		case		C_Times_MemoryErr:
		case		C_Times_RTCErr:
		case		C_Times_PowerBatteryErr:
		case		C_Times_OverDraft:
			SV_ReportNewAddNum[V_ucBitNum] = 0xFF;
			break;
		default:
			break;
	}
/*新增次数++，重新算CRC*/
	if(SV_ReportNewAddNum[V_ucBitNum] != 0xFF)
	{
		SV_ReportNewAddNum[V_ucBitNum]++;
	}
	Crc16 = PF_Cal_CRC(SV_ReportNewAddNum, C_ReportStateNum);
	PF_Ushort16ToBuffer2(&SV_ReportNewAddNum[C_ReportStateNum], &Crc16);
	Write_SV_ReportNewAddNum(SV_ReportNewAddNum);
}

/***************************************************************************
函数原型 	J_ReportNAN_Null_IfErrSetZero
函数功能	1、如果主动上报新增次数不正确则清零
				2、判断主动上报状态字是否全空。全空，返回C_OK
输入参数	无
输出参数 	无
返回参数	C_OK			:全空，没有任何故障信息需要上报
				C_Error			:有故障需要上报
全局变量 	SV_ReportNewAddNum
函数备注
***************************************************************************/
uchar8	J_ReportNAN_Null_IfErrSetZero(void)
{
	uchar8	 V_ReturnData;
	ushort16 Crc16, V_Len, V_usDataEncode;

/*判断SV_ReportNewAddNum是否CRC正确，如果不正确，则全部清零*/
	V_ReturnData = PF_Check_CRC( SV_ReportNewAddNum, ( C_ReportStateNum + 2 ) );
	if( ( V_ReturnData != C_OK ) && ( V_ReturnData != C_CrcErr_DataZero ) )
	{
		V_Len = C_ReportStateNum;
		if(InF_Read_Data(CReportNewAddNum, SV_ReportNewAddNum, &V_Len, &V_usDataEncode) != C_OK)
		{
			Init_SV_ReportNewAddNum();
			Init_SV_HaveReportState();
		}
		else
		{
			Crc16 = PF_Cal_CRC(SV_ReportNewAddNum, C_ReportStateNum);
			PF_Ushort16ToBuffer2(&SV_ReportNewAddNum[C_ReportStateNum], &Crc16);
		}
	}
	V_ReturnData = PF_Check_CRC(SV_HaveReportState.State, ( C_ReportStateByteNum + 2 + 2 ) );
	if( ( V_ReturnData != C_OK ) && ( V_ReturnData != C_CrcErr_DataZero ) )
	{
		V_Len = C_ReportStateByteNum + 2;
		if(InF_Read_Data( CHaveReportState, SV_HaveReportState.State, &V_Len, &V_usDataEncode ) != C_OK )
		{
			Init_SV_HaveReportState();
		}
		else
		{
			SV_HaveReportState.CRC16 = PF_Cal_CRC( SV_HaveReportState.State, C_ReportStateByteNum + 2 );
		}
	}
/*判断新增次数是否全部为0?*/
	if( Is_Buf_AllZero( SV_ReportNewAddNum, C_ReportStateNum ) == C_OK )
	{/*数据全部等于0，*/
		return(C_OK);
	}
	else
	{/*有故障*/
		return(C_Error);
	}
}

/***************************************************************************
函数原型 	Judge_ReportWithNxtFrame
函数功能	判断是否采用后续帧进行主动上报
输入参数	无
输出参数 	无
返回参数	C_OK			: 是，用后续帧进行主动上报
				C_Error			:否，无主动上报。
全局变量
函数备注
***************************************************************************/
#define		C_Work_Char_RWNxtFrame	0x04
uchar8	Judge_ReportWithNxtFrame(void)
{
	uchar8	Meter_Work_Char, V_ReturnData;
	ushort16	DataLen, V_usDataEncode;

/*首先读取电表运行特征字中主动上报模式*/
	DataLen = CLMeter_Work_Char1_645;
	V_ReturnData = InF_Read_Data(CMeter_Work_Char1_645, &Meter_Work_Char, &DataLen, &V_usDataEncode);
	if(V_ReturnData != C_OK)
	{
		return(C_Error);		/*特征字读不出，认为不允许后续帧上报*/
	}
/*判断特征字是否允许主动上报*/
	if((Meter_Work_Char & C_Work_Char_RWNxtFrame) == 0)
	{
		return(C_Error);		/*特征字不允许后续帧上报*/
	}
/*判断是否有主动上报*/
/*暂时不管有没有上报过，如果读后，不是立刻复位，任何命令都会*/
/*提示有后续帧。如果以后要求:已上报后未发生过新的主动上报，不允许提示再次上报，*/
/*则到时再处理*/
/*判断是否为全空。*/
	if(J_ReportNAN_Null_IfErrSetZero() == C_OK)
	{/*全空*/
		return(C_Error);
	}
	else
	{
		return(C_OK);
	}
}

/***************************************************************************
函数原型 	Is_EnableReport
函数功能	确认是否允许上报
输入参数	V_ucBitNum		:上报事件在主动上报状态字中位数0-95
输出参数 	无
返回参数 	C_OK			:允许上报
				C_Error			:不允许上报
全局变量
函数备注	如果模式字对应位允许设置，则答复C_OK
				当前根据模式字位和主动上报位之间的相互关系
				列算法。后面如果关系不明确，可列对应表。
			698兼容645增加，只部分项目允许上报，其他不管模式字是否设置为开启上报，均不上报
			允许上报项（电源异常、恒定磁场、开表盖、跳合闸、过流、失压、失流、掉电）
***************************************************************************/
uchar8		Is_EnableReport(uchar8	V_ucBitNum)
{
	uchar8	Drive_Report_Mode_645[CLDrive_Report_Mode_645];
	uchar8	V_ReturnData;
	uchar8	ByteIndex;					/*模式字数组下标*/
	uchar8	BitIndex;					/*该模式字节中对应的位数*/
	uchar8	Mode;
	ushort16	i, V_usDataEncode;
	ulong64 V_uldrive_Report_Mode_645 = 0;
/*下标超出最大值，则返回错误*/

	if(V_ucBitNum >= C_ReportStateNum)
	{
		return(C_Error);
	}
/*读模式字，如果读不出，则返回错误*/
	i = CLDrive_Report_Mode_645;
	V_ReturnData = InF_Read_Data(CDrive_Report_Mode_645, Drive_Report_Mode_645, &i, &V_usDataEncode);

	if(V_ReturnData != C_OK)
	{
		return(C_Error);
	}
	i = CLDrive_Report_Mode_645;
	PF_Buffer8ToUlong64(Drive_Report_Mode_645, &V_uldrive_Report_Mode_645, i);
	V_uldrive_Report_Mode_645 &= CDrive_Report_Mode_645_Judge;
	PF_Ulong64ToBuffer8(Drive_Report_Mode_645, &V_uldrive_Report_Mode_645, i);

/*主动上报状态字在0-31位，和模式字位一一对应*/
	if(V_ucBitNum < 32)
	{
		i = V_ucBitNum;
	}
/*主动上报状态字在32-47位，和模式字16-31位对应*/
	else if(V_ucBitNum < 48)
	{
		i = V_ucBitNum - 16;
	}
/*主动上报状态字在48-63位，和模式字16-31位对应*/
/*主动上报状态字在64-95位，和模式字32-63位对应*/
	else
	{
		i = V_ucBitNum - 32;
	}
	if( i == 41 )  /*双协议总功率反向 645上报模式字采用bit22功率反向，原bit41潮流反向变为保留位*/
	{
		i = 22;
	}
	ByteIndex = i / 8;
	BitIndex = i % 8;
	Mode = 0x01;
	for( i = 0; i < BitIndex; i++ )
	{
		Mode = Mode << 1;
	}
	if((Drive_Report_Mode_645[ByteIndex] & Mode) != 0x00)
	{
		return(C_OK);
	}
	else
	{
		return(C_Error);
	}
}

/***************************************************************************
函数原型 	Init_SV_ReportNewAddNum
函数功能	初始化主动上报状态字
输入参数	无
输出参数 	无
返回参数	无
全局变量 	SV_ReportNewAddNum
调用时机	1、总清时，先调用本函数，然后再调用总清主动上报置位
				2、判断函数J_ReportNAN_Null_IfErrSetZero中发现CRC错误
***************************************************************************/
void		Init_SV_ReportNewAddNum(void)
{
	uchar8	i;
	ushort16	Crc16;

	for(i = 0 ; i < ( C_ReportStateNum + 2 ); i++ )
	{
		SV_ReportNewAddNum[i] = 0;
	}
	Crc16 = PF_Cal_CRC(SV_ReportNewAddNum, C_ReportStateNum);
	PF_Ushort16ToBuffer2(&SV_ReportNewAddNum[C_ReportStateNum], &Crc16);
	Write_SV_ReportNewAddNum(SV_ReportNewAddNum);
}

/***************************************************************************
函数原型 	SF_Clear645_ReportNewAddNum
函数功能	清645主动上报新增事件表（复位状态）
输入参数
输出参数 	无
返回参数	无
全局变量
调用时机

***************************************************************************/
void	SF_Clear645_ReportNewAddNum(uchar8 V_ucEventNo, uchar8 V_Flag)
{
	uchar8 i;
    uchar8 V_ucHaveReportState[C_ReportStateByteNum] = {0};
    uchar8 V_ucWord;
    uchar8 V_ucBit;

    if( ( V_ucEventNo == C_EventClearEventNo ) && ( V_Flag != C_ReadRecord ) )
    {
		memset(V_ucHaveReportState, 0xFF, C_ReportStateByteNum);
		V_ucHaveReportState[C_EventClr_Offset] = 0xFD;  /*去除电表清零、事件清零*/
		Rst_SV_ReportNewAddNum(V_ucHaveReportState);
    }
    else
    {
		for(i = 0; i < CReport_645_Judge_Num; i++ )
		{
			if(V_ucEventNo == TB_ReportEventNo[i].EventN0) /*表格外不用清除上报*/
			{
				if( ( ( V_ucEventNo != C_RelayOpenEventNo ) && ( V_ucEventNo != C_RelayCloseEventNo ) ) || ( V_Flag == C_2015CLEAR ) )
				{
					V_ucWord = TB_ReportEventNo[i].BitN0 / C_WordLen;
					V_ucBit  = TB_ReportEventNo[i].BitN0 % C_WordLen;
					V_ucHaveReportState[V_ucWord] = C_ReportStateJudge << V_ucBit;
					Rst_SV_ReportNewAddNum(V_ucHaveReportState);
				}
			}
		}
    }
    return;
}
/***************************************************************************
函数原型 	SF_Clear645_ReportNewAddNum
函数功能	清645主动上报新增事件表（复位状态）
输入参数
输出参数 	无
返回参数	无
全局变量
调用时机

***************************************************************************/
void	SF_Clear645_ReportNewAddNum_EventClear()
{
	Init_SV_ReportNewAddNum();					/*主动上报处理*/
	Init_SV_HaveReportState();					/*首先全部复位主动上报，重新判断有故障再次上报*/
    return;
}
/***************************************************************************
函数原型 	SF_RstHaveReportState_645To698
函数功能	根据645已上报的状态字，复位对应位698中的事件
输入参数	*pRstState				:待复位的主动上报状态字。固定为12字节
输出参数 	无
返回参数	无
全局变量 	SV_HaveReportState
调用时机	1、主动上报状态字自动复位延时时间 到
			2、收到复位命令
698兼容645新增	   根据645中的上报位，对应698中的事件号，进行复位，
                   此函数需要在645复位命令之前，645复位后，已主动上报位会复位
645默认允许上报项（电源异常、恒定磁场、开表盖、跳合闸、过流、失压、失流、掉电,电表清零）
***************************************************************************/
const Str_ReportEventNo TB_ReportEventNo[CReport_645_Judge_Num]=
{
  /*645中bit位    			698中事件号*/
  {C_Report_Bit10,     C_OpenMeterCoverEventNo},	/*开盖*/
  {C_Report_Bit12,     C_MagneticCheckEventNo}, 	/*恒定磁场干扰*/
  {C_Report_Bit13,     C_PowerAbnormalEventNo}, 	/*电源异常*/
  {C_Report_Bit14,     C_RelayOpenEventNo},     	/*跳闸*/
  {C_Report_Bit15,     C_RelayCloseEventNo},    	/*合闸*/
  {C_Report_Bit16,     C_AlossvoltageEventNo},  	/*A相失压*/
  {C_Report_Bit19,     C_ALosscurrentEventNo},  	/*A相失流*/
  {C_Report_Bit20,     C_AOvercurrentEventNo},  	/*A相过流*/
  {C_Report_Bit32,     C_BlossvoltageEventNo},  	/*B相失压*/
  {C_Report_Bit35,     C_BLosscurrentEventNo},  	/*B相失流*/
  {C_Report_Bit36,     C_BOvercurrentEventNo},  	/*B相过流*/
  {C_Report_Bit48,     C_ClossvoltageEventNo},  	/*C相失压*/
  {C_Report_Bit51,     C_CLosscurrentEventNo},  	/*C相失流*/
  {C_Report_Bit52,     C_COvercurrentEventNo},  	/*C相过流*/
  {C_Report_Bit69,     C_PowerfailEventNo},     	/*掉电*/
  {C_Report_Bit81,     C_TolClearEventNo},      	/*电表清零*/

  {C_Report_Bit0,		C_RelayFaEndEnEventNo},		/*负荷开关误动作 */
  {C_Report_Bit3,		C_RTCBatLowVolEventNo},		/*时钟电池电压低 */
  {C_Report_Bit8,		C_PowerBatLowVolEventNo},	/*停电抄表电池欠压*/
  {C_Report_Bit11,		C_OpenTerminalCoverEventNo},/*开端钮盖*/
  {C_Report_Bit17,		C_ALessvoltageEventNo},		/*A相欠压*/
  {C_Report_Bit18,		C_AOvervoltageEventNo},		/*A相过压*/
  {C_Report_Bit21,		C_AReversecurrentEventNo},	/*A相功率反向*/
  {C_Report_Bit22,		C_ALossphaseEventNo},		/*A相断相  */
  {C_Report_Bit33,		C_BLessvoltageEventNo},		/*B相欠压*/
  {C_Report_Bit34,		C_BOvervoltageEventNo},		/*B相过压*/
  {C_Report_Bit38,		C_BReversecurrentEventNo},	/*B相功率反向*/
  {C_Report_Bit39,		C_BLossphaseEventNo},		/*B相断相  */
  {C_Report_Bit49,  	C_CLessvoltageEventNo},		/*C相欠压 */
  {C_Report_Bit50,  	C_COvervoltageEventNo},		/*C相过压  */
  {C_Report_Bit54,  	C_CReversecurrentEventNo},	/*C相功率反向*/
  {C_Report_Bit55,  	C_CLossphaseEventNo},		/*C相断相 */
  {C_Report_Bit64,  	C_ReversephaseVoltageEventNo},/*电压逆相序 */
  {C_Report_Bit66,  	C_UnbanlanceVoltageEventNo},/*电压不平衡 */
  {C_Report_Bit74,  	C_TotalVoltageLoseEventNo},	/*全失压 */
  {C_Report_Bit80,  	C_ProgramEventNo},			/*编程  */
  {C_Report_Bit82,  	C_DemandClearEventNo},		/*需量清零 */
  {C_Report_Bit83,  	C_EventClearEventNo},		/*事件清零 */
  {C_Report_Bit84,  	C_AdjTimeEventNo},			/*校时 */
  {C_Report_Bit7,       C_ClockFaEventNo},         /*时钟故障*/
  {C_Report_Bit73,		C_TReversecurrentEventNo}, /*总有功功率反向*/
};
void SF_RstHaveReportState_645To698(uchar8	*pRstState)
{
	uchar8	V_ucBitNum = 0;
	uchar8	i;
	uchar8	j;
	uchar8	HaveReportState;
    uchar8  V_ucEventNo[CReport_645_Judge_Num], V_ucFindEventNo, V_ucRstEventNum = 0;


    /*根据已经上报状态字中的位数，找对应位698事件号。*/
	for( j = 0; j < C_ReportStateByteNum; j++ )
	{
		HaveReportState = 0x01;
		for(i = 0; i < 8; i++ )				/* 1字节有8位*/
		{
			if( ( pRstState[j] & HaveReportState ) != 0 )
			{/*对应位需要复位，查找对应698事件号*/
				for( V_ucFindEventNo = 0; V_ucFindEventNo < CReport_645_Judge_Num; V_ucFindEventNo++ )
				{
					if(V_ucBitNum == TB_ReportEventNo[V_ucFindEventNo].BitN0)
					{
						V_ucEventNo[V_ucRstEventNum] = TB_ReportEventNo[V_ucFindEventNo].EventN0;
						V_ucRstEventNum++;
						break;/*表格中找到了，就不用再找，每个bit只代表1个事件*/
					}
					else/*表格以外事件不处理*/
					{
						;
					}
				}
			}
			V_ucBitNum++;
			HaveReportState = HaveReportState << 1;
		}
	}
     /*根据698事件号及事件个数，清对应上报。*/
    for( i = 0; i < V_ucRstEventNum; i++ )
    {
		/*跳合闸跟随上报状态字需特殊处理+时钟欠压和抄表欠压*/
		if( ( V_ucEventNo[i] == C_RelayOpenEventNo ) || ( V_ucEventNo[i] == C_RelayCloseEventNo )
		 || ( V_ucEventNo[i] == C_RTCBatLowVolEventNo ) || ( V_ucEventNo[i] == C_PowerBatLowVolEventNo ) )
		{
			Inf_CleanMeterStatus8_Relay(V_ucEventNo[i]);
		}
		else
		{
			Inf_ReportList(C_ReportChannelAll, V_ucEventNo[i], C_DeletReport);
		}
    }
}
/***************************************************************************
函数原型 	Rst_SV_ReportNewAddNum
函数功能	根据已上报的状态字，复位对应位新增次数,清已上报变量
输入参数	*pRstState				:待复位的主动上报状态字。固定为12字节
输出参数 	无
返回参数	无
全局变量 	SV_ReportNewAddNum、SV_HaveReportState
调用时机	1、主动上报状态字自动复位延时时间 到
				2、收到复位命令
***************************************************************************/
void		Rst_SV_ReportNewAddNum(uchar8	*pRstState)
{
	uchar8	V_ucBitNum = 0;
	uchar8	i;
	uchar8	j;
	uchar8	HaveReportState;
	ushort16	Crc16;

/*判断主动上报新增次数数组是否正确，不正确则直接全部清零*/
	J_ReportNAN_Null_IfErrSetZero();
/*根据已经上报状态字中的位数，对对应位进行清零。*/
	for( j = 0; j < C_ReportStateByteNum; j++ )
	{
		HaveReportState = 0x01;
		for( i = 0; i < 8; i++ )				/* 1字节有8位*/
		{
			if((pRstState[j] & HaveReportState) != 0)
			{/*对应位已上报*/
				SV_ReportNewAddNum[V_ucBitNum] = 0;
			}
			V_ucBitNum++;
			HaveReportState = HaveReportState << 1;
		}
	}
/*重新计算CRC*/
	Crc16 = PF_Cal_CRC(SV_ReportNewAddNum, C_ReportStateNum);
	PF_Ushort16ToBuffer2(&SV_ReportNewAddNum[C_ReportStateNum], &Crc16);
	Write_SV_ReportNewAddNum(SV_ReportNewAddNum);
/*复位已上报变量*/
	for( i = 0; i < C_ReportStateByteNum; i++ )
	{
		SV_HaveReportState.State[i] = SV_HaveReportState.State[i] & (~pRstState[i]);
	}
	SV_HaveReportState.Timer = 0;
	SV_HaveReportState.CRC16 = PF_Cal_CRC(SV_HaveReportState.State, C_ReportStateByteNum + 2);
	Write_SV_HaveReportState(SV_HaveReportState.State);
}
/***************************************************************************
函数原型 	Init_SV_HaveReportState
函数功能	复位SV_HaveReportState
输入参数	无
输出参数 	无
返回参数	无
全局变量 	SV_HaveReportState
调用时机	通信定时调度解析函数中，判断定时器为0

***************************************************************************/
void		Init_SV_HaveReportState(void)
{
	uchar8	i;

	SV_HaveReportState.Timer = 0;
	for( i = 0; i < C_ReportStateByteNum; i++ )
	{
		SV_HaveReportState.State[i] = 0;
	}

	SV_HaveReportState.CRC16 = PF_Cal_CRC(SV_HaveReportState.State, C_ReportStateByteNum + 2);
	Write_SV_HaveReportState(SV_HaveReportState.State);
}
/***************************************************************************
函数原型 	Set_SV_HaveReportState
函数功能	赋值SV_HaveReportState
输入参数	*pHaveReportState				:已主动上报状态字，固定12字节
输出参数 	无
返回参数	无
全局变量 	SV_HaveReportState
函数备注	主动上报时(函数Set_ReportStateFrame)中调用
***************************************************************************/
void		Set_SV_HaveReportState(uchar8	*pHaveReportState)
{
	ushort16	i, V_usDataEncode;
	uchar8	V_ReturnData;
	uchar8	V_RstReportStateTimerBCD;
	ulong32	V_RstReportStateTimerHex;

/*主动上报自动复位时间*/
	i = 1;
	V_ReturnData = InF_Read_Data(CRst_ReportState_Timer, &V_RstReportStateTimerBCD, &i, &V_usDataEncode);
	if(V_ReturnData != C_OK)
	{
		V_RstReportStateTimerBCD = 0x30;								/*读不出来，默认30分钟*/
	}
	PF_BCDtoHexBytes(&V_RstReportStateTimerBCD, &V_RstReportStateTimerHex, CLRst_ReportState_Timer);
	V_RstReportStateTimerHex = V_RstReportStateTimerHex * 120;			/*基于500ms定时器*/

/*赋值SV_HaveReportState*/
	SV_HaveReportState.Timer = (ushort16)V_RstReportStateTimerHex;
	for(i = 0; i < C_ReportStateByteNum; i++ )
	{
		SV_HaveReportState.State[i] = pHaveReportState[i];
	}
	SV_HaveReportState.CRC16 = PF_Cal_CRC(SV_HaveReportState.State, C_ReportStateByteNum + 2);
	Write_SV_HaveReportState(SV_HaveReportState.State);
	if(SV_HaveReportState.Timer == 0)
	{/*定时器直接就是0*/
		SF_RstHaveReportState_645To698(&SV_HaveReportState.State[0]);	/*清698主动上报，698兼容645增加*/
		Rst_SV_ReportNewAddNum(&SV_HaveReportState.State[0]);
		return;
	}
}
/***************************************************************************
函数原型 	Set_ReportStateFrame
函数功能	组织主动上报帧，并赋值SV_HaveReportState，启动自动清定时器
输入参数	pReportStateFrame				:上报帧的首地址
				pReportLen					:数据帧长度指针
输出参数 	*pReportStateFrame			:主动上报数据帧
				*pReportLen					:数据帧长度
返回参数	无
全局变量 	SV_HaveReportState
函数备注	注意pReportStateFrame开始缓冲区一定满足
				4字节DI长度+12(主动上报状态字)+96(新增次数)+2(AA)最大长度要求
***************************************************************************/
void		Set_ReportStateFrame(uchar8	*pReportStateFrame, uchar8	*pReportLen)
{
	uchar8	i;
	uchar8	j;
	uchar8	V_ucBitNum = 0;
	uchar8	HaveReportState;
	ulong32	ReportStateDI;

/*判断新增次数CRC是否正确，不正确则全部清0*/
	J_ReportNAN_Null_IfErrSetZero();

/*先置DI*/
	ReportStateDI = CDrive_Report_State_645;
	PF_Ulong32ToBuffer4(pReportStateFrame, &ReportStateDI, CLen_DI);

/*置长度为4字节DI+12字节主动上报状态字+1字节AA*/
	*pReportLen = C_ReportStateByteNum + CLen_DI;
	pReportStateFrame[*pReportLen] = 0xAA;		/*置位第1个AA*/
	(*pReportLen)++;
/*根据新增次数，置位上报帧中主动上报状态字和新增次数*/
	for( j = 0; j < C_ReportStateByteNum; j++ )
	{
		HaveReportState = 0x01;
		pReportStateFrame[CLen_DI + j] = 0;		/*首先将帧缓冲区中主动上报状态字清0*/

		for( i = 0; i < 8; i++ )				/* 1字节有8位*/
		{
			if(SV_ReportNewAddNum[V_ucBitNum] != 0)
			{/*新增次数不为0*/
				pReportStateFrame[CLen_DI + j] = pReportStateFrame[CLen_DI + j] | HaveReportState;
				pReportStateFrame[*pReportLen] = SV_ReportNewAddNum[V_ucBitNum];
				(*pReportLen)++;
			}
			V_ucBitNum++;				/*实际就是i*j+j*/
			HaveReportState = HaveReportState << 1;
		}
	}
/*增加最后一个块分隔符AA*/
	pReportStateFrame[*pReportLen] = 0xAA;
	(*pReportLen)++;
}
/***************************************************************************
函数原型 	Write_SV_HaveReportState
函数功能	将已主动上报标志写数据层
输入参数	*pHaveReportState	:已主动上报状态字，固定12字节
输出参数 	无
返回参数	无
全局变量 	SV_HaveReportState
函数备注	主动上报时(函数Set_ReportStateFrame)中调用
***************************************************************************/
void Write_SV_HaveReportState(uchar8 *HaveReportState)
{
	uchar8 Status_Old[20];
	ushort16 DataLen = 20, V_usDataEncode;

	InF_Read_Data(CHaveReportState, Status_Old, &DataLen, &V_usDataEncode);
	if(PF_Campare_Data(HaveReportState, Status_Old, DataLen - 2) != C_Equal)
	{
		InF_Write_Data(C_Msg_Communication, CHaveReportState, HaveReportState, DataLen, C_W_SafeFlag);
	}
}
/***************************************************************************
函数原型 	Write_SV_ReportNewAddNum
函数功能	将主动上报次数写数据层
输入参数	*ReportNewAddNum	:主动上报次数，固定96字节
输出参数 	无
返回参数	无
全局变量 	SV_ReportNewAddNum
函数备注	主动上报时(函数Set_ReportStateFrame)中调用
***************************************************************************/
void Write_SV_ReportNewAddNum(uchar8 *ReportNewAddNum)
{
	uchar8   ReportNewAddNum_Old[C_ReportStateNum];
	ushort16 DataLen = C_ReportStateNum, V_usDataEncode;

	InF_Read_Data(CReportNewAddNum, ReportNewAddNum_Old, &DataLen, &V_usDataEncode);
	if(PF_Campare_Data(ReportNewAddNum, ReportNewAddNum_Old, DataLen) != C_Equal)
	{
		InF_Write_Data(C_Msg_Communication, CReportNewAddNum, ReportNewAddNum, DataLen, C_W_SafeFlag);
	}
}
/***************************************************************************
函数原型 	DealWithEventReportIO
函数功能	处理主动上报口线
输入参数	无
输出参数 	无
返回参数	无
全局变量 	无
调用时机	1、通信500ms定时处理中调用
				2、上电初始化程序中调用
***************************************************************************/
void		DealWithEventReportIO(void)
{
	uchar8 V_Buf[C_ModuleMaxLen];
	ushort16 V_Len = C_ModuleMaxLen;
	uchar8 V_ucFlag_Report_645;

	memset(V_Buf, 0x00, C_ModuleMaxLen);
	V_ucFlag_Report_645 = J_ReportNAN_Null_IfErrSetZero();
	Inf_GetReportData(&V_Buf[0], &V_Len, C_Module, C_NoActiveReportFlag);
	if( ( V_Len == 1 ) && ( V_ucFlag_Report_645 == C_OK ) )
	{
		InF_SwithPeripherals(C_EventOut, C_Off);
	}
	else
	{
		InF_SwithPeripherals(C_EventOut, C_On);
	}
}

/***************************************************************************
函数原型 	Comm_Parse
函数功能	完成通信解析、数据应答、编程事件等任务
输入参数	CommNo:			串口通道号
				PowerFlag:		电源标志C_PowerOn表示有电状态，
								C_PowerFalling表示发生掉电的沿变过程，
								C_PowerOff表示处于掉电状态，C_PowerRising表示发生来电的沿变过程
输出参数 	无
返回参数	无
全局变量 	SV_Comm_Parse/SV_Com_Parse_Local/
				通道相关Str_Comm_Parm/Str_Comm_NxtFrame
函数备注
***************************************************************************/
void	Comm_Parse( uchar8 CommNo, uchar8	PowerFlag )
{
	Str_Comm_645	V_645Frame;
	Str_Comm_Parm 	*pStr_Comm_Parm_Address;
	uchar8	i;
	uchar8	CanParse = C_OK;
	ulong32	V_CommMsgNo;
	uchar8	V_Buf2[C_TimerExceed10minLen];
	uchar8	V_HaveMsgTx = C_Error;

/*解析函数的全局变量初始化*/
	Comm_ParseInit();
	SV_SetBPS_Flag = C_Error;			/*默认不是设置BPS*/
/*是有电到停电的沿，不应答，直接退出。*/
	if( PowerFlag == C_PowerFalling )
	{
		return;
	}
	if( CommNo == C_Module )
	{
	  	SV_ModuleResetTimer24h = C_ModuleResetTimer24h;
	}
/*获取通道交互变量指针*/
	SV_Comm_Parse_Local.SafeControlFlag = SV_Comm_Parse_Local.SafeControlFlag | C_W_SafeFlag_1;

	pStr_Comm_Parm_Address = Get_Str_Comm_Parm_Pointer(CommNo);
	if(pStr_Comm_Parm_Address == C_NULL)
	{
		Comm_ParseInit();
		return;		/*通道错，这实际不可能。发生了，也不发送，直接退出。*/
	}
	else
	{
		V_645Frame.ChannelNo = CommNo;
	}
/*进行完整帧分析如果合法，置V_645Frame*/
	if( IfFrameOkSetV_645Frame( &V_645Frame, pStr_Comm_Parm_Address ) != C_OK )
	{
		InF_InitComm(CommNo);
		Comm_ParseInit();
		return;
	}
	V_645Frame.PowerFlag = PowerFlag;

/*判断如果不是有电期间过来，则复位红外认证有效，同时判断通道不是红外就退出。*/
	memset( V_Buf2, 0, C_TimerExceed10minLen );/*清零备用*/
	if( PowerFlag == C_PowerOff )
	{/*掉电期间,如果红外认证有效，则清零*/
		if( JudgeTimerExceed10min(&IR_AuthT_645) == C_TimerEnable )
		{/*停电期间，如果原先红外认证有效，则取消红外认证。此时会发灭红外认证符号消息*/
			DealWith_IR_Auth_Timer_645(C_Set_TimerExceed10min, V_Buf2);
		}
		if( JudgeTimerExceed10min(&ID_AuthT_T) == C_TimerEnable )
		{/*停电期间，如果原先身份认证有效，则取消身份认证。此时会发灭红身份证符号消息*/
			DealWith_ID_Auth_T_Timer(C_Set_TimerExceed10min, V_Buf2);
		}
/*判断通道是否为红外，不是直接退出*/
		if( CommNo != C_IR )
		{
			return;
		}
	}
/*进行地址、红外权限、权限的判断.注意3个判断函数中有应答，因此*/
/*应该避免多次应答错误情况*/
	if( If_AddressFlagOK_ResponseErr(&V_645Frame) == C_Error )
	{
		CanParse = C_Error;
	}
	else if( Is_IR_Comm_ResponseErr_645(&V_645Frame) == C_Error )
	{
		CanParse = C_Error;
	}
	else if( Is_ID_Auth_Ok_ResponseErr(&V_645Frame) == C_Error )
	{
		CanParse = C_Error;
	}
	else if( Is_SPT_NotOver_ResponseErr(&V_645Frame) == C_Error )
	{
		CanParse = C_Error;
	}
	else
	{
		CanParse = C_OK;
	}

/*根据C调用不同的解析函数		*/
	if( CanParse == C_OK )
	{
		SV_Comm_Parse_Local.SafeControlFlag = SV_Comm_Parse_Local.SafeControlFlag | C_W_SafeFlag_2;
		switch( V_645Frame.C )
		{
			case		0x15:		/*设置通信地址*/
				Comm_SetCommAddress(&V_645Frame);
				break;
			case		0x13:		/*缩位读表号	*/
				Comm_CondenseAAReadMAddress(&V_645Frame);
				break;
			case		0x21:		/*写校表参数*/
				Comm_MeterCalibration(&V_645Frame);
				break;
			case		0x20:		/*读校表参数*/
				Comm_Cal_Read(&V_645Frame);
				break;
			case		0x03:		/*安全认证命令*/
				Comm_SecurityParse(&V_645Frame);
				break;
			case		0x1A:		/*电表总清命令*/
				Comm_MeterClear(&V_645Frame);
				break;
			case		0x19:		/*需量总清*/
				Comm_DemandClear(&V_645Frame);
				break;
			case		0x1B:		/*事件记录清零*/
				Comm_EventClear(&V_645Frame);
				break;
			case		0x18:		/*修改密码*/
				Comm_SetPassword(&V_645Frame);
				break;
			case		0x08:		/*广播校时*/
				Comm_BroadcastSetClock(&V_645Frame);
				break;
			case		0x17:		/*修改波特率*/
				Comm_Set_BPSr_C17(&V_645Frame);
				break;
			case		0x1C:		/*负荷开关控制*/
				Comm_LoadSwitch_Control(&V_645Frame);
				break;
			case		0x14:		/*参变量设置*/
				Comm_14SetParm(&V_645Frame);
				break;
			case		0x11:		/*读*/
				Comm_11_Read(&V_645Frame);
				break;
			case		0x12:		/*后续帧读*/
				Comm_ReadNxtFrameParse(&V_645Frame);
				break;
			case		0x1E:		/*厂内设置命令*/
				Comm_SetInFactoryState(&V_645Frame);
				break;
			case		0x1F:		/*自扩命令，数据恢复操作，具体描述见寄存器汇总*/
				Comm_RecoverRamData(&V_645Frame);
				break;
			default:			/*控制字C错误,应答其他错误*/
				InF_InitComm(CommNo);
				Comm_ParseInit();
				break;
		}
	}


/*根据通道号触发对应的显示*/
	LightenCommSign(CommNo,PowerFlag);

/*根据内部消息标志，进行对应的消息处理*/
	for( i = 0; i < C_MessageMaxNum; i++ )
	{
		V_CommMsgNo = Comm_FetchMsg();
		if(V_CommMsgNo == CMsg_Null)
		{
			break;
		}
		switch(V_CommMsgNo)
		{
			case	CMsg_Txd:				/*启动发送*/
			{
				if(V_645Frame.AddressFlag != C_Broadcast)
				{
					V_HaveMsgTx = C_OK;
					CommMSg_StartTxd(CommNo);
				}
				else
				{
					InF_InitComm(CommNo);
				}
			}break;
			case	CMsg_InitComm:			/*初始化串口消息*/
			{
				InF_InitComm(CommNo);
			}break;
			case	CMsg_MeterClear:			/*电表总清消息处理*/
				Have_IPEvent_MeterClear(&V_645Frame);
				break;
			case		CMsg_DemandClear:		/*电表需清消息处理*/
				Have_IPEvent_DemandClear(&V_645Frame);
				break;
			default:
				break;
		}
	}
/*调用Comm_ParseInit退出函数*/
	if(V_HaveMsgTx == C_Error)
	{/*程序中有的地方是直接退出的，没有触发发送消息，所以这里打个补丁，没有发送消息，就初始化串口*/
	 	InF_InitComm(CommNo);
	}
	Comm_ParseInit();
	return;
}

/***************************************************************************
函数原型 	Comm_LoadSwitch_Control
函数功能	负荷开关控制命令解析及应答
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	无
函数备注	1、是否已红外认证，身份认证是否有效，在这里判断。
					但请注意:02/04命令无须红外认证和身份认证，
				2、如果是98级密码，则200次挂起在这里判断。
					02/04级密码，密码判断函数中已判断3次密码闭锁
				3、表型是否支持本命令需要在这里判断。但外置内置不管
***************************************************************************/
void		Comm_LoadSwitch_Control(Str_Comm_645 *pV_645Frame)
{
	uchar8	ReponseDataNum = 1;			/*响应的字节个数*/
	ushort16	V_usOrderExcuteStatus = C_PasswordError_failure, ValidDataLen, V_usDataEncode;		/*默认密码错未授权。*/
	uchar8	Clock[CLDate_Time];
	uchar8	*pValidData;
	uchar8	V_ReturnData;

/*取响应字节长度*/
	if( ( pV_645Frame->Data[CPW_SpecialO_V_645 + 3] == 0x01 )
	 && ( pV_645Frame->Data[CPW_SpecialO_V_645] != 0x02 )
	 && ( ( pV_645Frame->Data[CPW_SpecialO_V_645] != 0x04 ) ) )
	{/*如果密级不等于2、4且p2=1，响应为2字节。*/
		ReponseDataNum = 2;
	}
/*判断表型是否支持*/
	if(C_Meter_Type == C_SmartMeter)
	{/*智能表不支持本命令*/
		Comm_LoadS_Ctr_Reponse(C_Error, C_PasswordError_failure, ReponseDataNum, pV_645Frame);
		return;
	}
/*进行权限判断。但不判断执行时间*/
	if(pV_645Frame->Data[CPW_SpecialO_V_645] == 0x98)
	{/*98级*/
		V_usOrderExcuteStatus = Comm_98LoadSwitch_Control(pV_645Frame);
	}
	else if( ( pV_645Frame->Data[CPW_SpecialO_V_645] == 0x02 ) || ( pV_645Frame->Data[CPW_SpecialO_V_645] == 0x04 ) )
	{/*02或04级密码*/
		V_usOrderExcuteStatus = Comm_02LoadSwitch_Control(pV_645Frame);
	}
	else
	{/*其他应答未授权退出*/
		Comm_LoadS_Ctr_Reponse(C_Error,C_PasswordError_failure, ReponseDataNum, pV_645Frame);
		return;
	}
	if(V_usOrderExcuteStatus != C_OK)
	{
		Comm_LoadS_Ctr_Reponse(C_Error, V_usOrderExcuteStatus, ReponseDataNum, pV_645Frame);
		return;
	}
/*判断长度及判断命令截止时间是否在系统时间之后。命令截止时间在系统时间之后*/
	if( pV_645Frame->DataLen != ( 4 + 4 + 8 ) )	/* 4字节密码4字节操作者代码8字节R1-R8*/
	{
		Comm_LoadS_Ctr_Reponse(C_Error, C_PasswordError_failure, ReponseDataNum, pV_645Frame);
	}

	pValidData = &pV_645Frame->Data[CData_OtherO_V_645];
	ValidDataLen = CLDate_Time;

/*判断截止时间是否有效，无效应答执行时间无效*/
	if( PF_DataTimeActive( &pValidData[C_R3_O], C_DT_Start_ss, CLDate_Time ) != C_OK )
	{
		Comm_LoadS_Ctr_Reponse( C_Error, C_ActTimeUnvalid_failure, ReponseDataNum, pV_645Frame );
		return;
	}
	if( InF_Read_Data( CDate_Time, Clock, &ValidDataLen, &V_usDataEncode ) == C_OK )
	{/*时间读得出*/
		if( PF_Campare_Data( &pValidData[C_R3_O], Clock, CLDate_Time ) == C_LessThan )
		{
			Comm_LoadS_Ctr_Reponse( C_Error, C_ActTimeUnvalid_failure, ReponseDataNum, pV_645Frame );
			return;
		}
	}
//698兼容645，进行跳闸延时645转写698
#if 0
        ValidDataLen = CLRelay_Delay_Time_645;
        if(InF_Read_Data(CRelay_Delay_Time_645, V_ucBuffer, &ValidDataLen, &V_usDataEncode) != C_OK)
        {
          V_ucBuffer[0] = 0;
          V_ucBuffer[1] = 0;
        }
        InF_Write_Data(C_Msg_Communication, CRelay_Delay_Time,V_ucBuffer, CLRelay_Delay_Time, C_W_SafeFlag);
#endif
//到这里，所有通信该判断的都已经判断了，调用继电器模块的接口函数。
//根据他的返回值进行应答.
	ulong32 V_ulDelay;
	V_ulDelay = pValidData[C_R2_O];
	V_ulDelay = V_ulDelay * 5;
	V_ReturnData = InF_DealwithComRelayOrder( pValidData[C_R1_O], pV_645Frame->Opcode, V_ulDelay, &V_usOrderExcuteStatus, C_UsedBy645);
	Comm_LoadS_Ctr_Reponse(V_ReturnData, V_usOrderExcuteStatus, ReponseDataNum, pV_645Frame);
}

/***************************************************************************
函数原型 	Comm_98LoadSwitch_Control
函数功能	完成98级负荷控制相关验证。并将数据改写成02级相关格式
输入参数	 *pV_645Frame			:接收到的数据帧
输出参数 	 *pV_645Frame			:整理成02级的格式
返回参数	C_OK/C_Meter_Safeguardfailure/C_MACError_failure/C_AuthOverTime_failure/C_PasswordError_failure
全局变量
函数备注	和其他特殊命令不同，长度不判断，R3-R8不判断,
				但需要管理200次电表挂起.管理身份认证是否有效，
				管理红外认证是否有效
***************************************************************************/
ushort16		Comm_98LoadSwitch_Control(Str_Comm_645 *pV_645Frame)
{
	uchar8	*pValidData;
	uchar8	ValidDataLen;
	ushort16	Serr16;

/*初步判断长度*/
	if(pV_645Frame->DataLen <= ( CLen_OpCode + CLen_CommPW ) )
	{
		return(C_PasswordError_failure);
	}
/*98级，必须有身份认证*/
	if(JudgeTimerExceed10min(&ID_AuthT) != C_TimerEnable)
	{
		return(C_AuthOverTime_failure);					/*身份认证超时*/
	}
/*有没有200次挂起*/
	if( Comm_DealwithSPTVariable(C_JudgeSPTVariable) == C_SPT_Num_Over )
	{
		return(C_Meter_Safeguardfailure);				/*200次挂起*/
	}
/*如果是红外输入口，则必须处于红外认证期间*/
	if(pV_645Frame->ChannelNo == C_IR)
	{
		if(JudgeTimerExceed10min(&IR_AuthT_645) != C_TimerEnable)
		{
			return(C_PasswordError_failure);
		}
	}
/*调用安全模块接口函数进行解密*/
	pValidData = &pV_645Frame->Data[CData_OtherO_V_645];
	ValidDataLen = pV_645Frame->DataLen - CLen_CommPW - CLen_OpCode;

	Serr16 = InF_S_ControlCommand(pValidData, &ValidDataLen);
	if(Serr16 == C_SERR_ESAM_VF)
	{
		Comm_DealwithSPTVariable(C_SPTNumAdd);
		return(C_MACError_failure);
	}
	else if(Serr16 != C_OK)
	{/*其他错误*/
		return(C_PasswordError_failure);
	}
	else
	{
		pV_645Frame->DataLen = CLen_OpCode + CLen_CommPW + ValidDataLen;
		return(C_OK);
	}
}

/***************************************************************************
函数原型 	Comm_02LoadSwitch_Control
函数功能	完成02级负荷控制相关验证。
输入参数	 *pV_645Frame			:接收到的数据帧
输出参数 	 *pV_645Frame			:整理成02级的格式
返回参数	C_OK/C_AuthOverTime_failure/
全局变量
函数备注	和其他特殊命令不同，长度不判断，R1-R8不判断,
				1、判断密码是否正确，
				2、判断是否为合闸和合闸允许命令。这一点对原先综合市场考虑差别了
					最早考虑02、04级密码负荷控制就是针对综合市场。
					其他综合市场命令有编程开关!但负荷控制重来不需要编程开关!
				3、如是判断红外通道无须判断红外认证
***************************************************************************/
ushort16		Comm_02LoadSwitch_Control(Str_Comm_645 *pV_645Frame)
{
	uchar8	*pValidData;

	pValidData = &pV_645Frame->Data[CData_OtherO_V_645];
/*判断是否为密码错误	*/
	if( Is_PW_OK( &pV_645Frame->Data[CPW_SpecialO_V_645] ) != C_OK )
	{
		return(C_PasswordError_failure);
	}
/*判断是否厂内，厂内所有控制命令都执行*/
	if( JudgeTimerExceed10min(&SI_JTimer_BSOn2500) == C_TimerEnable )
	{
		return (C_OK);
	}
/*判断是否为合闸或合闸允许。不是则应答C_PasswordError_failure*/
	if( ( pValidData[C_R1_O] == 0x1B ) || ( pValidData[C_R1_O] == 0x1C ) )
	{
		return(C_OK);
	}
	else
	{
		return(C_PasswordError_failure);
	}
}
/***************************************************************************
函数原型 	Comm_LoadS_Ctr_Reponse
函数功能	负荷控制的应答帧组织
输入参数	ReposneType				:=C_OK:正确应答 = C_Error:错误应答
				V_usOrderExcuteStatus		:ReposneType = C_OK，为控制命令执行状态字
										:ReposneType = C_Error，为错误状态字
				ReposneLen				:响应长度 =1 ,则ReposneType =C_OK，长度为0
														ReposneType =C_Error,长度为1
										:响应长度 =2,不管ReposneType，长度均为2
				*pV_645Frame				:接收到的数据帧
输出参数
返回参数
全局变量 	调用通道交互相关函数置发送缓冲
函数备注
***************************************************************************/
void	Comm_LoadS_Ctr_Reponse(uchar8 ReposneType, ushort16 V_usOrderExcuteStatus, uchar8 ReposneLen, Str_Comm_645 *pV_645Frame)
{
	uchar8	ResponseData[2];

	PF_Ushort16ToBuffer2(ResponseData, &V_usOrderExcuteStatus);
/*长度等于1，的应答*/
	if(ReposneLen == 1)
	{
		if(ReposneType == C_OK)
		{
			Comm_Response_Set_ReadErr(C_OK, pV_645Frame);
		}
		else
		{
			Comm_Response_Set_ReadErr(C_Unauthorized_645, pV_645Frame);
		}
		return;
	}
/*长度等于2*/
	if(ReposneType != C_OK)
	{
		Comm_Response_03_Err(V_usOrderExcuteStatus, pV_645Frame);
	}
	else
	{/*正确应答2字节的执行状态字*/
		Comm_Response_FromP_Normal(pV_645Frame, ResponseData, 2);
	}
}
/****************************************************************************
*厂内模式下参数设置
****************************************************************************/
typedef struct
{
	ulong32	ParmDI;
	ulong32	ParmDI_645;
	uchar8	ParmLen;
	uchar8	Offset;				/*通信帧中的偏移。不包括DI*/
	uchar8	ChangeFlag;
}Str_SetParmInFactoryState;
#define		CL_TB_SetParmInFactoryState	19
#define C_NormalExchangeOAD		1
#define C_AbnormalVoltageOAD	2
const	Str_SetParmInFactoryState	TB_SetParmInFactoryState[CL_TB_SetParmInFactoryState] =
{
	{CVolage_Type			,CVolage_Type_645			,CLVolage_Type			,	0	,	0},
	{CCurrent_Type			,CCurrent_Type_645			,CLCurrent_Type			,	1	,	0},
	{CLine_Type				,CLine_Type_645				,CLLine_Type			,	2	,	0},
	{CAuxi_Power_Sign		,CAuxi_Power_Sign_645		,CLAuxi_Power_Sign		,	3	,	0},
	{CRelay_Type			,CRelay_Type_645			,CLRelay_Type			,	4	,	0},
	{CComm_Way				,CComm_Way_645				,CLComm_Way				,	5	,	0},
	{CZero_Current_Sign		,CZero_Current_Sign_645		,CLZero_Current_Sign	,	6	,	0},
	{CStart_Up_Current		,CStart_Up_Current_645		,CLStart_Up_Current		,	11	,	C_NormalExchangeOAD},
	{CVolage_Abnor_Vol		,CVolage_Abnor_Vol_645		,CLVolage_Abnor_Vol		,	16	,	C_AbnormalVoltageOAD},
	{CPulse_Constant		,CPulse_Constant_645		,CLPulse_Constant		,	20	,	0},
	{CLoss_Volage_Curr		,CLoss_Volage_Curr_645		,CLLoss_Volage_Curr		,	32	,	C_NormalExchangeOAD},
	{CLoss_Volage_Vol		,CLoss_Volage_Vol_645		,CLLoss_Volage_Vol		,	34	,	C_NormalExchangeOAD},
	{CRev_Phase_Vol			,CRev_Phase_Vol_645			,CLRev_Phase_Vol		,	36	,	0},
	{CRelayOpen_Vol__LowLim	,CRelayOpen_Vol__LowLim_645	,CLRelayOpen_Vol__LowLim,	40	,	C_NormalExchangeOAD},
	{CRelayOpen_Vol__UpLim	,CRelayOpen_Vol__UpLim_645	,CLRelayOpen_Vol__UpLim	,	42	,	C_NormalExchangeOAD},
	{CStart_Up_Power		,CStart_Up_Power_645		,CLStart_Up_Power		,	44	,	0},
	{CProgram_Valid			,CProgram_Valid_645			,CLProgram_Valid		,	52	,	0},
	{CMeterRunStatic		,CMeterRunStatic_645		,CLMeterRunStatic		,	63	,	0},
	{CPluse_Most__Lim		,CPluse_Most__Lim_645		,CLPluse_Most__Lim		,	65	,	0},
};
/***************************************************************************
函数原型 	SF_InFactoryState
函数功能	判断输入的是哪个标志码，如果是全失压电压/电流/起动功率/起动电流,回C_NormalExchangeOAD
									如果是电压异常电压阀值，回C_AbnormalVoltageOAD
输入参数	UlOAD:645标志码
输出参数
返回参数	标志码类型：0：不需要数据转换；1：需要进行BCD和HEX转换；2 ：拆成2个，分别转换；
全局变量
函数备注
***************************************************************************/

uchar8	SF_InFactoryState(ulong32 UlOAD)
{
	uchar8 V_ucReturn = 0;

	if( ( UlOAD == CLoss_Volage_Vol_645 ) || ( UlOAD == CLoss_Volage_Curr_645 ) || ( UlOAD == CStart_Up_Current_645 ) || ( UlOAD == CStart_Up_Power_645 ) )
	{
		V_ucReturn = C_NormalExchangeOAD;			/*BCD转HEX*/
	}
	else if( UlOAD == CVolage_Abnor_Vol_645 )
	{
		V_ucReturn = C_AbnormalVoltageOAD;			/*要分成2个数据分别转*/
	}
	return V_ucReturn;
}
/***************************************************************************
函数原型 	SF_InFactoryExchangeBCD
函数功能	对有需要的三相配置参数数据进行数据转换
			如果是全失压电压/电流/起动功率/起动电流,回HEX转BCD;
			如果是电压异常电压阀值，分成两个分别进行HEX转BCD;
输入参数	UlOAD:645标志码
输出参数
返回参数
全局变量
函数备注
***************************************************************************/
void SF_InFactoryExchangeBCD(uchar8 LineNo, uchar8 *pV_ucData)
{
	uchar8	V_ucOADType, V_ucLen, V_ucVoltage, V_ucBuffer[10] = {0};
	ulong32 V_ulDoubleWordBuufer = 0;

	V_ucLen = TB_SetParmInFactoryState[LineNo].ParmLen;
	V_ucOADType = TB_SetParmInFactoryState[LineNo].ChangeFlag;
	if( V_ucOADType == C_NormalExchangeOAD)										/*需要进行HEX和BCD的转化OAD*/
	{
		PF_Buffer4ToUlong32(pV_ucData, &V_ulDoubleWordBuufer, V_ucLen);
		PF_HextoBCDBytes(&V_ulDoubleWordBuufer, pV_ucData, (uchar8 *)&V_ucLen);
	}
	else if( V_ucOADType == C_AbnormalVoltageOAD )
	{
		V_ucVoltage = CLVolage_Abnor_Vol_Single;								/*电源异常电压触发上限*/
		PF_Buffer4ToUlong32(pV_ucData, &V_ulDoubleWordBuufer, V_ucVoltage);
		PF_HextoBCDBytes(&V_ulDoubleWordBuufer, pV_ucData, &V_ucVoltage);
		V_ucVoltage = CLVolage_Abnor_Vol_Single;								/*电源异常电压触发下限*/
		PF_Buffer4ToUlong32(pV_ucData + V_ucVoltage, &V_ulDoubleWordBuufer, V_ucVoltage);
		PF_HextoBCDBytes(&V_ulDoubleWordBuufer, pV_ucData  + V_ucVoltage, &V_ucVoltage);
	}
	else
	{
		;
	}
}
/***************************************************************************
函数原型 	Comm_SetInFactoryState
函数功能	厂内设置命令
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	无
函数备注	见寄存器汇总.后增加复旦微自扩读命令
***************************************************************************/
void		Comm_SetInFactoryState(Str_Comm_645 *pV_645Frame)
{
	uchar8   V_ucBuffer[72], i, Is_WriteDataOk = C_OK, V_ucVoltage = 0, V_ucOADType = 0;
	ushort16 V_ucLen, V_usDataEncode;
	Str_WrParmTable	WrParmTable;
	union B16_B08_2 Temp16;
	struct COMMUNICATION_FRM
	{
		uchar8 Buf[100];										/*接收缓冲/发送缓冲*/
	}Uart[1];
	ulong32  V_ulDoubleWordBuufer = 0;

	if( ( pV_645Frame->DataLen == 0x04 ) && ( pV_645Frame->Data[0] == 0x05 ) )		/*RTC时钟调校，复旦微自扩读EE数据命令,自扩命令注意*/
	{
		if( JudgeTimerExceed10min(&SI_JTimer_BSOn2500) != C_TimerEnable )
		{
			Comm_Response_Set_ReadErr(C_Unauthorized, pV_645Frame);
			return;
		}
		Uart[0].Buf[9] = pV_645Frame->DataLen;
		memcpy(Uart[0].Buf + 10, &(pV_645Frame->Data[0]), pV_645Frame->DataLen);	/*兼容复旦微程序，10：数据域*/

		{
			Temp16.B08[0] = Uart[0].Buf[ 11 ];					/*Di1*/
			Temp16.B08[1] = Uart[0].Buf[ 12 ];					/*Di2*/

			if( Temp16.B16 == 0xeeee )							/*需要保留这条命令，否则复旦的校表软件无法下发RTC日计时校准命令*/
			{
				memset( Uart[0].Buf+14, 0x00, 64 );

				Uart[0].Buf[14 + 32] = *(uchar8*)0x1FFFFC0E;	/*0x04 代表404*/
				Uart[0].Buf[14 + 38] = 0xaa;
			}
			else if( Temp16.B16 == 0xfefe )
			{
				memset( Uart[0].Buf + 14, 0x00, 64 );
				memcpy( Uart[0].Buf + 14, (uchar8*)0x1FFFFC10, 9 );

			}
			else if( Temp16.B16 < 0x400 )						/*需要保留扩展读ee的命令，否则复旦的校表软件无法读取ee中的数据*/
			{
				InF_ReadE2ThreeRTC(ee_temperature_page, ee_temperature_inpage, (Uart[0].Buf + 14 + ee_temperature_inpage), ee_temperature_lenth); /*获取11字节温度补偿系数*/

				if(Temp16.B16 == 0x002a)
				{
					memcpy(Uart[0].Buf + 14, (uchar8*)(&RTC_RT.TAdc), ee_ptatvalue_lenth);
				}
				if(Temp16.B16 == 0x002b)
				{
					memcpy(Uart[0].Buf + 14, (uchar8*)(&RTC_RT.TVal), ee_ptatvalue_lenth);
				}
			}
			Comm_RTC1E_Response_Normal(pV_645Frame,Uart[0].Buf + 14, 64);
			return;
		}
	}
	else
	{
		if( Is_ParmType_3( pV_645Frame->DI, &WrParmTable, pV_645Frame->ChannelNo ) == C_OK )	/*三类参数中，能用1E命令写的参数只有GPRS相关参数*/
		{/*本段代码，是为了解决III类参数中，自扩GPRS模块相关参数能通过1E命令进行读和写。*/
	       /*************三类参数中包括GPRS信号强度和复位主动上报，只能用14命令设置**************/
			if( ( pV_645Frame->DI == CGPS_Signal ) || ( pV_645Frame->DI == CRst_Report_State_645 ) )
			{
				return;
			}
			V_ucLen = pV_645Frame->DataLen - CLen_DI - CLen_CommPW;
			if( pV_645Frame->DataLen > ( CLen_DI + CLen_CommPW ) )								/*长度大于标识码加密码长度，表示为写数据*/
			{/*写数据前不对合法性进行判断，数据层长度不对写不进去的*/
				Is_WriteDataOk = InF_Write_Data(C_Msg_Communication, pV_645Frame->DI, &pV_645Frame->Data[CData_OtherO_V_645], (ushort16)V_ucLen, C_W_SafeFlag);

				Comm_Response_Set_ReadErr(Is_WriteDataOk, pV_645Frame);
			}
			else
			{
				V_ucLen = C_Comm_Data_MaxLen - CLen_DI;
				Is_WriteDataOk = InF_Read_Data(pV_645Frame->DI, &pV_645Frame->Data[C_11_SData], &V_ucLen, &V_usDataEncode);
				if(Is_WriteDataOk == C_OK)
				{
					Comm_11_03Response_Normal(pV_645Frame, &pV_645Frame->Data[C_11_SData], V_ucLen);
				}
				else
				{
					Comm_Response_Set_ReadErr(C_OtherErr, pV_645Frame);
				}
			}
			return;
		}
	/*判断标识码*/
		if(pV_645Frame->DI != 0xFFFFFFFF)
		{
			if((pV_645Frame->DI == 0x3EEEEE05))
			{
				Comm_11_03Response_Normal(pV_645Frame, V_ucBuffer, 64);
				return;
			}
			else
			{
				return;						/*如果是标识码不对，不进行应答*/
			}
		}
	/*判断是否为进入或退出厂内模式*/
		if( ( pV_645Frame->DataLen == 0x09 ) && ( pV_645Frame->Data[C_O_SF_Data] == 0x1A ) )
		{/*厂内自扩命令1A为进出厂内模式的标志。*/
			In_Out_FactoryState(pV_645Frame);
			return;
		}

	/*其他所有命令都必须是在厂内模式下设置。*/
		if( JudgeTimerExceed10min(&SI_JTimer_BSOn2500) != C_TimerEnable )
		{
			Comm_Response_Set_ReadErr(C_Unauthorized, pV_645Frame);
			return;
		}
	/*根据长度，进行不同设置命令的解析。*/
		if(pV_645Frame->DataLen == 0x09)
		{
			Act_InFactoryState(pV_645Frame);
		}
		else if(pV_645Frame->DataLen == 0x48)
		{
			Set_InFactoryState(pV_645Frame);
		}
		else if(pV_645Frame->DataLen == 0x0A)
		{
			if(pV_645Frame->Data[C_O_SF_Data] == C_ReadParaFlay)	/*读取厂内配置参数*/
			{
				for( i = 0; i < 72; i++)
				{
					V_ucBuffer[i] = 0;
				}
				for( i = 0; i < CL_TB_SetParmInFactoryState; i++)
				{
					V_ucLen = TB_SetParmInFactoryState[i].ParmLen;
					InF_Read_Data(TB_SetParmInFactoryState[i].ParmDI, &V_ucBuffer[TB_SetParmInFactoryState[i].Offset], &V_ucLen, &V_usDataEncode);

					SF_InFactoryExchangeBCD( i,  &V_ucBuffer[TB_SetParmInFactoryState[i].Offset] );
				}
				Comm_11_03Response_Normal(pV_645Frame, V_ucBuffer, 0x44);
			}
		}
	}
}
/***************************************************************************
函数原型 	Comm_RecoverRamData
函数功能	恢复数据层RAM数据，具体见寄存器汇总《RAM数据恢复命令》
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	无
函数备注	后增复旦微RTC调校命令，RTC调校操作必须在厂内
***************************************************************************/
void		Comm_RecoverRamData(Str_Comm_645 *pV_645Frame)
{
	uchar8   V_ReturnFlag;
	uchar8   i, Temp08 = 0;
	ushort16 V_Len, V_usDataEncode;;
	ulong32  V_ulAddr;
	union    B16_B08_2 Temp16;
	struct COMMUNICATION_FRM
	{
		uchar8 Buf[220];			/*接收缓冲/发送缓冲*/
	}Uart[1];
	uchar8 k, OutBuf[256], Buf[64];/*返回数据长度*/

	/*判断标识码,公司内部自扩命令判断*/
	if( ( pV_645Frame->DI == 0xFFFFFFFF ) && ( ( pV_645Frame->DataLen == 0x0A ) || ( pV_645Frame->DataLen == 0x09 ) ) )/*初步判断读E2、RAM、Flash数据或者数据恢复操作*/
	{
		if(pV_645Frame->DataLen == 0x0A)/*抄读数据*/
		{
			if( ( pV_645Frame->Data[C_O_SF_Data] == C_ReadFlashFlay )		/*读取flash数据*/
			 || ( pV_645Frame->Data[C_O_SF_Data] == C_ReadRamFlay ) 		/*读取Ram数据*/
		     || ( pV_645Frame->Data[C_O_SF_Data] == C_ReadE2Flay)			/*读取E2数据*/
			 || ( pV_645Frame->Data[C_O_SF_Data] == C_ReadFRAMFlay ) )		/*读取铁电数据*/
			{
				PF_Buffer4ToUlong32(&pV_645Frame->Data[C_O_SF_Data + 1],&V_ulAddr,4);

				pV_645Frame->DataLen = pV_645Frame->Data[C_O_SF_Data + 5];
				if(pV_645Frame->DataLen > (C_Comm_Data_MaxLen - C_DILen_Cal))
				{
					return;
				}
				InF_ReadE2_Flash_Data(&pV_645Frame->Data[C_O_SF_Data ], pV_645Frame->Data[C_O_SF_Data + 5], pV_645Frame->Data[C_O_SF_Data], V_ulAddr);
				Comm_11_03Response_Normal(pV_645Frame, &pV_645Frame->Data[C_O_SF_Data], pV_645Frame->DataLen);
				return;
			}
		}
		else												/* 数据恢复 */
		{
			if(pV_645Frame->Data[C_O_SF_Data] == 0x02)		/* E2恢复RAM数据 */
			{
				InF_RAMDataRecoverFromE2();					/* 调用数据层，E2恢复RAM数据 */
				Comm_Response_Set_ReadErr(C_OK, pV_645Frame);
				return;
			}
		}
	}
	/*复旦微RTC时钟调校处理，判断是否厂内*/
	k = 0;
	OutBuf[0] = 0x00;
	if(C_OK != InF_JudgeIJTimer())
	{
		Comm_Response_Set_ReadErr(C_OtherErr, pV_645Frame);
		return;
	}
	Uart[0].Buf[9] = pV_645Frame->DataLen;
	memcpy( &(Uart[0].Buf[10]), &(pV_645Frame->Data[0]), pV_645Frame->DataLen);		/*兼容复旦微程序，10：数据域*/

	switch(pV_645Frame->Data[0])								/*数据域数据*/
	{
		case 0x03:
		{
			/*设置温度曲线的参数说明：*/
			/*0 高温温度斜率微调 */
			/*1 低温温度斜率微调*/
			/*2 高温晶体曲线微调（高温修调二次函数系数）x*0.0001*/
			/*3 低温晶体曲线微调（低温修调二次函数系数）x*0.0001*/
			/*4 常温顶点调校值修正值*/
			/*9 常温25+晶体曲线微调（常温25+修调二次函数系数）x*0.0004 krh*/
			/*10常温25-晶体曲线微调（常温25-修调二次函数系数）x*0.0004 krl*/
			if(pV_645Frame->DataLen != 0x0A)
			{
				break;
			}

			Temperpara_Verify();								/*温度系数校验*/
			memcpy( Buf, Tpara.Offset, ee_temperature_lenth );	/*复制温度系数*/

			if( Uart[0].Buf[19] == 0x00 )						/*全部更新*/
			{
				memcpy( Buf + 2, Uart[0].Buf + 16, 3 );
			}
			else if( Uart[0].Buf[19] == 0x55 )					/*更新高温温度系数*/
			{
				Buf[2] = Uart[0].Buf[16];
			}
			else if( Uart[0].Buf[19] == 0x5a )					/*更新低温温度系数*/
			{
				Buf[3] = Uart[0].Buf[17];
			}
			else if( Uart[0].Buf[19] == 0xaa )					/*更新调校值*/
			{
				Buf[4] = Uart[0].Buf[18];
			}
			else if( Uart[0].Buf[19] == 0x05 )					/*更新高温温度系数krh*/
			{
				Buf[9] = Uart[0].Buf[18];
			}
			else if( Uart[0].Buf[19] == 0x50 )					/*更新低温温度系数krl*/
			{
				Buf[10] = Uart[0].Buf[18];
			}
			else
			{
				break;
			}
			V_ReturnFlag = InF_WriteE2ThreeRTC( ee_temperature_page, ee_temperature_inpage, Buf, ee_temperature_lenth );
			if( C_OK != V_ReturnFlag )
			{
				break;
			}
			memcpy( Tpara.Offset, Buf, ee_temperature_lenth );		/*更新ram温度系数*/
			Crc_16Bits_Add2(Tpara.Offset, ee_temperature_lenth );	/*CRC计算*/
			RTC_RT.TempFlag = 0xff;									/*更新查表数据*/
			GV_ucTime = 6;											/*立刻启动温度adc,4S后*/
			k = 1;
		}
		break;
		case 0x04:													/*读温度ADC等数据*/
		{
			ushort16 Vus_RTCADJUST;
			k = 9;
			if( const_tx_flag == 0x3cc3 )
			{
				OutBuf[1] = 0xc3;									/*0xc3表示温度调校过*/
			}
			else
			{
				OutBuf[1] = (uchar8)(const_tx_flag & 0xff);
			}
			OutBuf[2] = Tpara.RtcTMode;								/*读RTC补偿工作模式，0x55:测试模式，0xAA常温查表插值模式，其他：普通模式*/

			Vus_RTCADJUST = InF_GetRTC_Adjust();
			if( RTC->ADSIGN & 0x00000001 )							/*调校值小于0*/
			{
				Temp16.B16 = (ushort16)((short16)Vus_RTCADJUST * -1);
			}
			else
			{
				Temp16.B16 = Vus_RTCADJUST;
			}
			OutBuf[3] = Temp16.B16;
			OutBuf[4] = Temp16.B16 >> 8;							/*实际补偿值*/
			OutBuf[5] = Temperature_Adc;							/*读温度ADC数据*/
			OutBuf[6] = Temperature_Adc >> 8;

			V_Len = CLMeter_Temp;
			InF_Read_Data(CMeter_Temp, &OutBuf[7], &V_Len, &V_usDataEncode);
		}
		break;
		case 0x07:	/*设置RTC补偿工作模式，0x55:测试模式，0xAA常温查表插值模式，其他：普通模式*/
			RTC_RT.TestTrim = 0;
		case 0xa9:	/*关闭温度补偿（通信调时钟误差，准备测量时钟误差）*/
		case 0xaa:	/*写常温顶点调校值（通信调时钟误差）(下发2字节日计时误差,-10.0秒~10.0秒,补码)*/
		case 0x0b:	/*常温温度ADC微调*/
		{
			/*5 常温温度ADC微调*/
			/*6 常温顶点调校值L（通信调时钟误差）*/
			/*7 常温顶点调校值H（通信调时钟误差）*/
			/*8 RTC补偿工作模式，0x55:测试模式，0xAA常温查表插值模式，其他：普通模式*/
			Temperpara_Verify();	/*温度系数校验*/
			memcpy( Buf, Tpara.Offset, ee_temperature_lenth );		/*复制温度系数*/
			if( Uart[0].Buf[ 10 ] == 0x07 )
			{
				if( ( Uart[0].Buf[9] != 0x02 ) ) 					/*数据长度错误,编程禁止*/
				{
					break;
				}
				Buf[8] = Uart[0].Buf[11];
				RtcStopProcFlag = 0x00;								/*打开RTC温度补偿功能*/
			}
			else if( Uart[0].Buf[ 10 ] == 0xa9 )/*关闭温度补偿（通信调时钟误差，准备测量时钟误差）*/
			{
				if( ( Uart[0].Buf[9] != 0x01 ) || ( const_tx_flag == 0x3cc3 ) )
				{
					break;		/*刚编程调校过*/
				}
				if( ( Tpara.RtcTMode == 0x55 ) || ( Tpara.RtcTMode == 0xAA ) )
				{
					break;		/*禁止关闭rtc补偿*/
				}
				RtcStopProcFlag = 0x55;								/*关闭RTC温度补偿功能*/
				GV_ucTime = 6;										/*立刻启动温度adc   复旦微同上*/
				k = 1;
				break;
			}
			else if( Uart[0].Buf[ 10 ] == 0xaa )					/*(下发2字节日计时误差,补码)*/
			{
				if( (Uart[0].Buf[9] != 0x03)||(const_tx_flag == 0x3cc3)||(RtcStopProcFlag!=0x55)) break;	/*刚编程调校过*/

				Temp16.B08[0] = Uart[0].Buf[ 11 ];
				Temp16.B08[1] = Uart[0].Buf[ 12 ];
				if( ( (short16)Temp16.B16 > 10000 ) || ( (short16)Temp16.B16 < -10000 ) )
				{
					break;											/*限制±10.000秒*/
				}
				Temp16.B16 = Get_RTCTop_Proc( Temp16.B16 );			/*折算顶点调校值*/
				Buf[6] = Temp16.B08[0];
				Buf[7] = Temp16.B08[1];
				RtcStopProcFlag = 0x00;								/*打开RTC温度补偿功能*/
				Buf[4] = 0;											/*清微调值*/
				if( Buf[1] == 0 )
				{
					Buf[1] = 0x80;
				}
			}
			else	/*5 常温温度ADC微调*/
			{
				if( ( Uart[0].Buf[9] != 0x02 )||( ( Uart[0].Buf[11] & 0x7F ) > 50 ) )
				{
					break;											/*超出允许调整范围*/
				}
				Buf[5] = Uart[0].Buf[11];
			}
			V_ReturnFlag = InF_WriteE2ThreeRTC( ee_temperature_page, ee_temperature_inpage, Buf, ee_temperature_lenth );
			if( C_OK != V_ReturnFlag )
			{
				break;
			}

			if( ( Uart[0].Buf[10] & 0x0f ) == 0x0a )				/*写常温顶点调校值时时间记录*/
			{
				InF_ReadE2ThreeRTC( ee_rtcadj_time_page, ee_rtcadjtime_inpage, Buf, ee_rtcadjtime_lenth );
				Buf[0]++;											/*写常温顶点调校值次数加1*/

				V_Len = CLMeter_Temp;
				InF_Read_Data(CMeter_Temp, &Buf[8], &V_Len, &V_usDataEncode);
				Buf[7] = Uart[0].Buf[ 10 ];							/*通讯标识*/
				InF_WriteE2ThreeRTC( ee_rtcadj_time_page, ee_rtcadjtime_inpage, Buf, ee_rtcadjtime_lenth );
			}

			Tpara.Crc16.B08[0] += 1;
			temperpara_veri_flag = 1;
			RTC_RT.TempFlag = 0xff;									/*更新查表数据*/
			GV_ucTime = 6;											/*立刻启动温度adc*/
			k = 1;
		}
		break;
		case 0x06:							/*修改顶点调校值的偏移量	NNNN	2*/
		{
			if(Uart[0].Buf[9] != 0x03)
			{
				break;						/*数据长度错误,编程禁止*/
			}
			if( Tpara.RtcTMode != 0x55 )
			{
				break;						/*仅在测试模式下有效*/
			}

			Temp16.B08[0] = Uart[0].Buf[11];
			Temp16.B08[1] = Uart[0].Buf[12];
			if( ( ( (short16)Temp16.B16 ) < -200 ) || ( ( (short16)Temp16.B16 ) ) > 200 )
			{
				break;						/*顶点调校值的偏移量，单位为补偿最小步长，0.238或0.119*/
			}
			RTC_RT.TestTrim = (short16)Temp16.B16;
			RTC_RT.TempFlag = 0xff;			/*更新查表数据*/
			GV_ucTime = 6;					/*立刻启动温度adc*/
			k = 1;
		}
		break;
		case 0x08:/*设置查表插值数据*/
		{
			if( Uart[0].Buf[9] != 85 )
			{
				break;/*数据长度错误,编程禁止*/
			}
			if( ( Tpara.RtcTMode != 0x55 ) && ( Tpara.RtcTMode != 0xAA ) )
			{
				break;/*仅在测试模式下有效*/
			}

			/*根据温度自动判断写入数据的地址*/
			if( RTC_RT.TempFlag == 0 )/*常温查表*/
			{
				Temp16.B16 = ee_ptatvalue_page;
				i = ee_ptatvalue_inpage;
				Temp08 = ee_ptatvalue_lenth;
			}
			else if( RTC_RT.TempFlag == 1 )/*低温查表*/
			{
				Temp16.B16 = ee_ptatvalue_lt_page;
				i = ee_ptatvalue_lt_inpage;
				Temp08 = ee_ptatvalue_lt_lenth;

				Crc_16Bits_Add2(Uart[0].Buf + 11, Temp08);
				Crc_16Bits_Add2(Uart[0].Buf + 11 + 42, Temp08);
				Temp08 = Temp08 + 2;/*加上CRC的2字节*/
			}
			else if( RTC_RT.TempFlag == 2 )/*高温查表*/
			{
				Temp16.B16 = ee_ptatvalue_ht_page;
				i = ee_ptatvalue_ht_inpage;
				Temp08 = ee_ptatvalue_ht_lenth;

				Crc_16Bits_Add2(Uart[0].Buf + 11, Temp08);
				Crc_16Bits_Add2(Uart[0].Buf + 11 + 42, Temp08);
				Temp08 = Temp08+2;
			}
			else
			{
				break;
			}
			V_ReturnFlag = InF_WriteE2ThreeRTC( Temp16.B16, i, Uart[0].Buf + 11, Temp08 );
			V_ReturnFlag = InF_WriteE2ThreeRTC( Temp16.B16 + 1, i, Uart[0].Buf + 11 + 42, Temp08 );

			if( C_OK != V_ReturnFlag )
			{
				break;
			}
			Fill_RTC_RT_TAdc();
			Fill_RTC_RT_TVal();

			Temperpara_Verify();									/*温度系数校验*/
			memcpy( Buf, Tpara.Offset, ee_temperature_lenth );		/*复制温度系数*/
			Buf[8] = 0xAA;											/*下发数据后自动进入查表模式*/
			V_ReturnFlag = InF_WriteE2ThreeRTC( ee_temperature_page, ee_temperature_inpage, Buf, ee_temperature_lenth );
			if( C_OK != V_ReturnFlag )
			{
				break;
			}
			Tpara.Crc16.B08[0] += 1;
			temperpara_veri_flag = 1;
			RTC_RT.TempFlag = 0xff;									/*更新查表数据*/
			GV_ucTime = 6;											/*立刻启动温度adc*/
			k = 1;
		}
		break;
		case 0x09:													/*读常温顶点调校值（通信调时钟误差）*/
		{
			k = 5;
			if( const_tx_flag == 0x3cc3 )
			{
				OutBuf[1] = 0xc3;									/*0xc3表示温度调校过*/
			}
			else
			{
				OutBuf[1] = (uchar8)(const_tx_flag & 0xff);
			}
			OutBuf[2] = Tpara.Offset[5];							/*常温温度ADC微调*/
			OutBuf[3] = Tpara.Offset[6];							/*常温顶点调校值L*/
			OutBuf[4] = Tpara.Offset[7];							/*常温顶点调校值H*/
		}
		break;
		default:
				break;
	}
	if( k == 0x00 )													/*不发送应答帧*/
	{
		Comm_Response_Set_ReadErr(C_OtherErr,pV_645Frame);
		return;
	}
	else
	{
		if(OutBuf[0] == 0x00)	 /*确认帧*/
		{
			if( ( Uart[0].Buf[8] == 0x03 ) || ( Uart[0].Buf[8] == 0x11 ) || ( Uart[0].Buf[8] == 0x12 ) )
			{
				Temp08 += 4;
			}

		}
		else
		{
			Comm_Response_Set_ReadErr(C_OtherErr, pV_645Frame);
			return;
		}
	}

	Uart[0].Buf[9] = ( k - 1 + Temp08 );
	pV_645Frame->DataLen = Uart[0].Buf[9];
	memcpy( Uart[0].Buf + 10 + Temp08, OutBuf + 1, k );							/*搬移数据*/
	memcpy( &pV_645Frame->Data[0], Uart[0].Buf + 10, pV_645Frame->DataLen);		/*搬移数据，所有数据域数据	*/
	Comm_RTC1F_Response_Normal(pV_645Frame, &pV_645Frame->Data[0], pV_645Frame->DataLen);
}
/***************************************************************************
函数原型 	Set_InFactoryState
函数功能	厂内模式下的 设置
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	无
函数备注	无
***************************************************************************/
void		Set_InFactoryState(Str_Comm_645 *pV_645Frame)
{
	uchar8	V_ReturnData;
	uchar8	i, V_ucOADType, V_ucLen;
	ulong32 V_ulDoubleWordBuufer = 0;
	Str_SetParmInFactoryState	*pSPIFS;

	pSPIFS = (Str_SetParmInFactoryState *) &TB_SetParmInFactoryState[0];

	SV_Comm_Parse_Local.SafeControlFlag = SV_Comm_Parse_Local.SafeControlFlag | C_W_SafeFlag_3;

	for( i = 0; i < CL_TB_SetParmInFactoryState; i++ )
	{
		V_ReturnData = C_Error;
		if(JudgeTimerExceed10min(&SI_JTimer_BSOn2500) == C_TimerEnable)
		{				/*改成698标志码*/
			V_ucOADType = TB_SetParmInFactoryState[i].ChangeFlag;
			if( V_ucOADType == C_NormalExchangeOAD)										/*需要进行HEX和BCD的转化OAD*/
			{
				V_ucLen = pSPIFS[i].ParmLen;
				PF_BCDtoHexBytes(&pV_645Frame->Data[C_O_SF_Data + pSPIFS[i].Offset], &V_ulDoubleWordBuufer, V_ucLen);
				PF_Ulong32ToBuffer4(&pV_645Frame->Data[C_O_SF_Data + pSPIFS[i].Offset], &V_ulDoubleWordBuufer, V_ucLen);
			}
			else if( V_ucOADType == C_AbnormalVoltageOAD )								/*电源异常电压触发上限和下限*/
			{
				V_ucLen = CLVolage_Abnor_Vol_Single;
				PF_BCDtoHexBytes(&pV_645Frame->Data[C_O_SF_Data + pSPIFS[i].Offset], &V_ulDoubleWordBuufer, V_ucLen);
				PF_Ulong32ToBuffer4(&pV_645Frame->Data[C_O_SF_Data + pSPIFS[i].Offset], &V_ulDoubleWordBuufer, V_ucLen);
				PF_BCDtoHexBytes(&pV_645Frame->Data[C_O_SF_Data + pSPIFS[i].Offset + V_ucLen], &V_ulDoubleWordBuufer, V_ucLen);
				PF_Ulong32ToBuffer4(&pV_645Frame->Data[C_O_SF_Data + pSPIFS[i].Offset + V_ucLen], &V_ulDoubleWordBuufer, V_ucLen);
			}
			else
			{
				;
			}
			V_ReturnData = InF_Write_Data(C_Msg_Communication,pSPIFS[i].ParmDI, &(pV_645Frame->Data[C_O_SF_Data+pSPIFS[i].Offset]),
											pSPIFS[i].ParmLen,SV_Comm_Parse_Local.SafeControlFlag);
		}
		if(V_ReturnData == C_OK)
		{
			continue;
		}
		else
		{
			Comm_Response_Set_ReadErr(C_Unauthorized, pV_645Frame);
			return;
		}
	}
	Comm_Response_Set_ReadErr(C_OK, pV_645Frame);
}
/***************************************************************************
函数原型 	Act_InFactoryState
函数功能	厂内模式下的动作
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	无
函数备注	这些命令用于厂内模式下进行硬件检测
***************************************************************************/
#define C_InFactoryState_DisplayTime_On 0x0A
void		Act_InFactoryState(Str_Comm_645 *pV_645Frame)
{
	uchar8	V_ResponseOk = C_OK;
/*根据CC进行动作分类*/
	switch(pV_645Frame->Data[C_O_SF_Data])
	{
		case		0x03:										/*多功能输出秒脉冲*/
			InF_ModifyFunctionWord(C_SecondPulseOutput);		/*秒脉冲只需要控制*/
			break;
		case		0x04:										/*需量周期脉冲输出*/
			InF_ModifyFunctionWord(C_DemandPulseOutput);
			InF_MultiFunctionOutput(C_DemandPulse);
			break;
		case		0x05:										/*时段投切信号输出*/
			InF_ModifyFunctionWord(C_RatePulseOutput);
			InF_MultiFunctionOutput(C_RatePulse);
			break;
		case		0x06:										/*报警继电器输出通*/
			Comm_SendMsgToDisp(C_WarnOutPut, C_AlwaysDisplay, C_InFactoryState_DisplayTime_On);
			break;
		case		0x07:										/*报警继电器输出关*/
			Comm_SendMsgToDisp(C_WarnOutPut, C_NotDisplay, C_Duration_Alway);
			break;
		case		0x09:										/*复位载波模块*/
			InF_SwithPeripherals(C_ModuleReset, C_On);
			break;
		case		0x0A:										/*点亮报警灯*/
			V_ResponseOk = C_Error;
			break;
		case		0x0B:										/*关闭报警灯*/
			V_ResponseOk = C_Error;
			break;
		case		0x0C:										/*点亮报警灯并拉闸*/
			InF_RelayAct(C_Off);
			Comm_SendMsgToDisp(C_RelayStatusLED, C_AlwaysDisplay, C_InFactoryState_DisplayTime_On);
			break;
		case		0x0D:										/*关闭报警灯并合闸*/
			InF_RelayAct(C_On);
			Comm_SendMsgToDisp(C_RelayStatusLED, C_NotDisplay, C_Duration_Alway);
			break;
		case		0x0E:										/*点亮背光灯*/
			Comm_SendMsgToDisp(C_BackLED, C_AlwaysDisplay, C_InFactoryState_DisplayTime_On);
			break;
		case		0x0F:										/*光闭背光灯*/
			Comm_SendMsgToDisp(C_BackLED, C_NotDisplay, C_Duration_Alway);
			break;
		case		0x18:										/*开蜂鸣器*/
		case		0x19:										/*关闭蜂鸣器*/
			V_ResponseOk = C_Error;
			break;
		case		0x1C:										/*写外置继电器脉冲宽度*/
			SV_Comm_Parse_Local.SafeControlFlag = SV_Comm_Parse_Local.SafeControlFlag | C_W_SafeFlag_3;
			V_ResponseOk = InF_Write_Data(C_Msg_Communication, CExtern_Relay_PulW,
				&pV_645Frame->Data[C_O_SF_Data+1], CLExtern_Relay_PulW, SV_Comm_Parse_Local.SafeControlFlag);
			break;
		default:
			V_ResponseOk = C_Error;
			break;
	}
	if(V_ResponseOk == C_OK)
	{
		Comm_Response_Set_ReadErr(C_OK,pV_645Frame);
	}
	else
	{
		Comm_Response_Set_ReadErr(C_Unauthorized, pV_645Frame);
	}
}

/***************************************************************************
函数原型 	In_Out_FactoryState
函数功能	进出厂内模式的解析及应答及事件记录
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	无
函数备注	实际设置软IJ时间，设置为0退出。设置为非0，进入
***************************************************************************/
#define		C_TimeDurationInFactory		0xAE60
void	In_Out_FactoryState( Str_Comm_645 *pV_645Frame )
{
	ulong32	Soft_I_J_Time;
	uchar8	Buf[16];					/*格式前7个字节是日期时间，后2字节是基于5min的软IJ时间，BCD*/
	ushort16	DataLen = CLDate_Time, V_usDataEncode;

/*读系统时钟，作为编程记录的起始时间如果时钟读不出，默认2000年1月1日*/
	if( InF_Read_Data(CDate_Time, Buf, &DataLen, &V_usDataEncode) != C_OK )
	{
		Buf[CDate_Time_DD_O] = 0x01;
		Buf[CDate_Time_MM_O] = 0x01;
		Buf[CDate_Time_YYL_O] = 0xD0;
		Buf[CDate_Time_YYH_O] = 0x07;
	}

/*判断设置还是退出*/
	PF_Buffer4ToUlong32(&pV_645Frame->Data[C_O_SF_Data + 1], &Soft_I_J_Time, 4);
	SV_Comm_Parse_Local.SafeControlFlag = SV_Comm_Parse_Local.SafeControlFlag | C_W_SafeFlag_3;
	if( Soft_I_J_Time == 0 )
	{/*退出*/
		if( JudgeTimerExceed10min(&SI_JTimer_BSOn2500) == C_TimerEnable )
		{
			memset( &Buf[CDate_Time_YYH_O+1], 0, 4 );
			DealWith_SI_J_Timer(C_Set_TimerExceed10min,&Buf[CDate_Time_YYH_O+1]);
			/*写进入厂内模式事件记录*/
			InF_Write_Data(C_Msg_Communication, CSoft_I_J_Prog_2, Buf, CLSoft_I_J_Prog_2, SV_Comm_Parse_Local.SafeControlFlag);
		}
		Comm_Response_Set_ReadErr(C_OK, pV_645Frame);
		return;
	}
	else if( Soft_I_J_Time <= C_TimeDurationInFactory )
	{/*时间非0，且小于31天，认为进入厂内模式*/
		if( InF_GetPeripheralStatus(C_KeyOpenCover) == C_Invalid )
		{/*开盖的情况下才能进入厂内模式。开盖去抖是在驱动层做的。*/
		/*现在软IJ的根据2.5s扣减1次Str_TimerExceed10min。基本大定时器基于5min，需处于5*/
			Soft_I_J_Time = Soft_I_J_Time / 5;
			DataLen = 4;
			PF_HextoBCDBytes(&Soft_I_J_Time, &Buf[CDate_Time_YYH_O+1], (uchar8 *)&DataLen);
			if(SV_Comm_Parse_Local.SafeControlFlag == C_W_SafeFlag)
			{
				DealWith_SI_J_Timer(C_Set_TimerExceed10min,&Buf[CDate_Time_YYH_O+1]);	//进入厂内模式
				//写进入厂内模式事件记录
				InF_Write_Data(C_Msg_Communication,CSoft_I_J_Prog_1,Buf,CLSoft_I_J_Prog_1,SV_Comm_Parse_Local.SafeControlFlag);
				Comm_Response_Set_ReadErr(C_OK,pV_645Frame);
			}
		}
		return;
	}
	else
	{
		return;			/*其他不应答*/
	}
}
/***************************************************************************
函数原型 	Comm_Cal_Read
函数功能	通信校表相关读命令的解析及应答
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	通信通道缓冲区变量
函数备注	校表读命令格式:68 A0-A5 68 20 02 DI0 DI1 CS 16.
				异常应答68 A0 -A5 E0 01 ERR CS 16
				正常应答68 A0 -A5 A0 L DI0 DI1 Data CS 16
	1、特殊命令-读校表序列号。DI1DI0 = 0x87A0
	2、读校表参数，计量芯片。DI1DI0 = 0x86XX
	3、读数据层校表参数。DI1DI0 = 0x85XX
	4、读计量芯片实时参数原始值。DI1DI0 = 0x83XX
***************************************************************************/
void		Comm_Cal_Read(Str_Comm_645 *pV_645Frame)
{
	uchar8	V_ReturnData;
	uchar8	buf_O_CanWrite = C_DILen_Cal;					/*缓冲区可写数据的偏移*/
	ushort16	Cal_RdDI, LenFor_Data, V_usDataEncode;		/*缓冲区可被写的总的长度*/
	uchar8	*pData;

	PF_Buffer2ToUshort16(&pV_645Frame->Data[C_O_DI0], &Cal_RdDI);
/*指针从DI0开始*/
	pData = &pV_645Frame->Data[C_O_DI0];
	LenFor_Data = C_Comm_Data_MaxLen - C_DILen_Cal;

	if(Cal_RdDI == 0x87A0)
	{/*读校表序列号*/
		V_ReturnData = InF_Read_Data(CRec_MeterSequence, &pData[buf_O_CanWrite], &LenFor_Data, &V_usDataEncode);
	}
	else	if(pV_645Frame->Data[C_O_DI1] == 0x85)
	{/*读数据层校表参数*/
		V_ReturnData = InF_Read_RecMeterData(pV_645Frame->Data[C_O_DI0], &pData[buf_O_CanWrite], (uchar8 *)&LenFor_Data);
	}
	else
	{/*其他都是读计量芯片中的校表寄存器或实时参数原始值*/
		V_ReturnData = InF_ReadReg_MeterIC(Cal_RdDI, &pData[buf_O_CanWrite], (uchar8 *)&LenFor_Data);
	}
/*组织应答帧*/
	if(V_ReturnData == C_OK)
	{
		buf_O_CanWrite = buf_O_CanWrite + LenFor_Data;
		Comm_Response_FromP_Normal(pV_645Frame, pData, buf_O_CanWrite);
	}
	else
	{/*读不出来，等同于错误类型为校表时密码读不出*/
		Comm_Response_Set_ReadErr(V_ReturnData, pV_645Frame);
	}
	return;
}
/***************************************************************************
函数原型 	Comm_MeterCalibration
函数功能	通信校表命令解析(完成写计量芯片，校表事件记录)
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	通信通道缓冲区变量
				因为校表非常重要，应用2个安全标志
SV_Comm_Parse_Local.SafeControlFlag = SV_Comm_Parse_Local.SafeControlFlag|C_W_SafeFlag_1;
SV_Comm_Parse_Local.MeterClearFlag = SV_Comm_Parse_Local.MeterClearFlag |C_W_SafeFlag(校表总清用)
函数备注
	1、特殊命令有3个:
		a。校表加密命令:
			格式:L(0x13) +DI0 DI1 (A0 87) +PAP0P1P2C0C1C2C3  +5字节序列号+4字节密码
			电表判断数据层密码是否能正确读出，不能才允许写。否则不允许写
		b。启动校表命令
			格式:L(0x09)+DI0DI1(68 87)+PAP0P1P2 +3字节无效数据
			处理:调用计量模块接口函数，如果返回值为启动校表，
					不写数据层校表参数,写校表编程记录的时间
		c。结束校表命令
			格式:L(0x09)+DI0DI1(69 87)+PAP0P1P2 +3字节无效数据
			处理:调用计量模块接口函数，如果返回值为结束校表
					不作任何处理，直接应答正确，退出。
		d。写校表总清命令
			格式:L(0x09)+DI0DI1(6A 87)+PAP0P1P2 +3字节无效数据
			处理:调用计量模块接口函数，如果返回值为结束校表
					循环读数据层校表参数，写校表记录1-最大值，同时清数据层校表参数
	2、其他单个校表命令
			格式:L + DI0 DI1 (XX 86) + PAP0P1P2+3字节校表参数
			处理:调用计量模块的接口函数，如果返回值为C_OK，输出序号个数为1
					读数据层校表参数，写校表记录，再写数据层校表参数
	3、块校表命令
			格式:L+DI0 DI1 (XX 82) + PAP0P1P2+9字节校表参数
			处理:调用计量模块的接口函数，如果返回值为C_OK，输出个数为3
					循环3次写读数据层序号对应校表参数，写校表记录，再写数据层校表参数
***************************************************************************/
#define		C_DI0ForBlockMaxLen		30
void		Comm_MeterCalibration(Str_Comm_645 *pV_645Frame)
{
	ushort16		Cal_DI1_DI0, DataLen, V_usDataEncode;
	uchar8	V_ReturnData;
	uchar8	Cal_DI0Buf_ForBlock[C_DI0ForBlockMaxLen];		/*块写时，返回分项序号的名称*/
	uchar8	Cal_DI0_Num;									/*分项序号的个数*/
	uchar8	Cal_PW[CLRec_MeterPassWord];
	uchar8	i;

	PF_Buffer2ToUshort16(&pV_645Frame->Data[C_O_DI0], &Cal_DI1_DI0);
	SV_Comm_Parse_Local.MeterClearFlag = SV_Comm_Parse_Local.MeterClearFlag | C_W_SafeFlag_1;
/*判断是否为 校表加密命令*/
	if( ( Cal_DI1_DI0 == 0x87A0 ) && ( pV_645Frame->DataLen == 15 ) )
	{
		Cal_SetPassword(pV_645Frame);
		return;
	}
/*这里判断一下长度及DI1-DI0 是否正确*/
	switch(Cal_DI1_DI0)
	{
		case		0x8768:					/*特殊命令-启动校表*/
		case		0x8769:					/*特殊命令-结束校表*/
			DataLen = 9;					/* 2字节DI，+4字节密码+3字节数据*/
			break;
		case		0x876A:					/*特殊命令-校表清零*/
			DataLen = 9;					/* 2字节DI，+4字节密码+3字节数据*/
			SV_Comm_Parse_Local.MeterClearFlag = SV_Comm_Parse_Local.MeterClearFlag | C_W_SafeFlag_2;
			break;
		default:
			if((Cal_DI1_DI0 & 0xFF00)==0x8600)
			{/*一般校表命令*/
				if(pV_645Frame->Data[C_O_DI0] >= C_MeterICDataNum_T)
				{/*DI0超出范围*/
					Comm_Response_Set_ReadErr(C_Cal_IDErr, pV_645Frame);
					return;
				}
				else
				{
					DataLen = 9;
					break;
				}
			}
			if( ( Cal_DI1_DI0 & 0xFF00 ) == 0x8200 )
			{/*块写标识码。DI0由计量模块判断，我这里不判断*/
				DataLen = 15;
				break;
			}
			/*其他*/
			Comm_Response_Set_ReadErr(C_Cal_IDErr,pV_645Frame);
			return;
	}
	if(DataLen != pV_645Frame->DataLen)
		{/*长度错误*/
			Comm_Response_Set_ReadErr(C_Cal_LenErr, pV_645Frame);
			return;
		}
/*校表仅允许厂内模式，在外面判过了，这里仅判断密码是否正确*/
	DataLen = CLRec_MeterPassWord;
	V_ReturnData = InF_Read_Data(CRec_MeterPassWord, Cal_PW, &DataLen, &V_usDataEncode);
	if(V_ReturnData != C_OK)
		{/*应该属于未设置过校表密码的情况*/
			Comm_Response_Set_ReadErr(C_Cal_PWCanNotRD, pV_645Frame);
			return;
		}
	if((pV_645Frame->Data[C_O_PW_Cal]!=Cal_PW[0])||
		(pV_645Frame->Data[C_O_PW_Cal+1]!=Cal_PW[1])||
		(pV_645Frame->Data[C_O_PW_Cal+2]!=Cal_PW[2])||
		(pV_645Frame->Data[C_O_PW_Cal+3]!=Cal_PW[3]))
		{/*校表密码错!*/
			Comm_Response_Set_ReadErr(C_Cal_PW_Err, pV_645Frame);
			return;
		}
	SV_Comm_Parse_Local.SafeControlFlag = SV_Comm_Parse_Local.SafeControlFlag|C_W_SafeFlag_3;
/*调用计量芯片的接口函数，写计量芯片校表寄存器,长度为接收到缓冲区长度扣减6(2字节标识码和4字节密码)*/
	Cal_DI0_Num = C_DI0ForBlockMaxLen;
	V_ReturnData = InF_WriteCalReg_MeterIC(Cal_DI1_DI0, &pV_645Frame->Data[C_O_Data_Cal],
                                           (pV_645Frame->DataLen - 6), Cal_DI0Buf_ForBlock, &Cal_DI0_Num);
/*根据返回值进行不同的处理:*/
	switch(V_ReturnData)
	{
		case		C_StartCalibrationOK:		/*启动校表*/
			Cal_WriteCalStartClock(pV_645Frame);
			return;
		case		C_CalibrationOK:			/*结束校表*/
			Comm_Response_Set_ReadErr(C_OK, pV_645Frame);
			return;
		case		C_ClearCalRegOK:			/*总清校表成功*/
			SV_Comm_Parse_Local.MeterClearFlag = SV_Comm_Parse_Local.MeterClearFlag |C_W_SafeFlag_3;
			Cal_ClearAllCalReg(pV_645Frame);
			return;
		case		C_NOStartCalibration:		/*校表状态错误，即未启动校表*/
			Comm_Response_Set_ReadErr(C_Cal_NOStartErr, pV_645Frame);
			return;
		case		C_SPIError:
			Comm_Response_Set_ReadErr(C_Cal_SPIErr, pV_645Frame);
			return;
		case		C_IDError:
			Comm_Response_Set_ReadErr(C_Cal_IDErr, pV_645Frame);
			return;

		default:
		{
			if(V_ReturnData == C_OK)/*校表正确,需区分块写还是单个写*/
			{
				if(Cal_DI0_Num == 0x01)
				{/*单个写*/
					V_ReturnData = Write_OneCalRegToData(pV_645Frame->Data[C_O_DI0], &pV_645Frame->Data[C_O_Data_Cal]);
					Comm_Response_Set_ReadErr(V_ReturnData, pV_645Frame);
				}
				else if(Cal_DI0_Num == 0x03)
				{/*块写*/
					for( i = 0; i < Cal_DI0_Num; i++ )
					{																	/*校表参数长度为为3*/
						V_ReturnData = Write_OneCalRegToData(Cal_DI0Buf_ForBlock[i], &pV_645Frame->Data[C_O_Data_Cal + 3 * i]);
						if(V_ReturnData != C_OK)
						{
							Comm_Response_Set_ReadErr(V_ReturnData, pV_645Frame);
							return;
						}
					}
					/*块写结束*/
					Comm_Response_Set_ReadErr(V_ReturnData, pV_645Frame);
					return;
				}
				else
				{
					Comm_Response_Set_ReadErr(C_Cal_WrMICOtherErr, pV_645Frame);
				}
				return;
			}
			else
			{
				Comm_Response_Set_ReadErr(C_Cal_WrMICOtherErr, pV_645Frame);
			}
		}
		return;
	}
}

/***************************************************************************
函数原型 	Cal_ClearAllCalReg
函数功能	总清校表寄存器
输入参数	*pV_645Frame				:接收到的数据帧
				SV_Comm_Parse_Local.SafeControlFlag
				SV_Comm_Parse_Local.MeterClearFlag
输出参数 	无
返回参数	无
全局变量 	无
函数备注	无
***************************************************************************/
void		Cal_ClearAllCalReg(Str_Comm_645 *pV_645Frame)
{
	uchar8	CalRegData[3] = {0, 0, 0};
	uchar8	i;
	uchar8	V_ReturnData;

/*循环总清*/
	for( i = 0; i < C_MeterICDataNum_T; i++ )
	{
		if(SV_Comm_Parse_Local.MeterClearFlag == C_W_SafeFlag)
		{/*总清标志正确，安全控制标志，在单个写参数中判断中用了*/
			V_ReturnData = Write_OneCalRegToData(i, CalRegData);
			if(V_ReturnData != C_OK)
			{
				Comm_Response_Set_ReadErr(V_ReturnData, pV_645Frame);
				return;
			}
		}
	}
	Comm_Response_Set_ReadErr(C_OK, pV_645Frame);
}

/***************************************************************************
函数原型 	Write_OneCalRegToData并作事件记录
函数功能	写一个校表寄存器到数据层，并作事件记录
输入参数	CalRegInData_No			:数据层的校表寄存器序号
				pCalReg					:新的校表数据，长度固定为3字节
				SV_Comm_Parse_Local.SafeControlFlag
输出参数 	无
返回参数	C_OK/C_Cal_NoErr/C_Cal_SafeFlagErr/C_Cal_WrDataErr
全局变量 	见输入参数
函数备注	无
***************************************************************************/
#define		C_PreCalReg_O			1
#define		C_HaveWrCalEventFlag_O	0
#define		C_IsNotWrCalEvent		0x00
#define		C_HaveNotWrCalEvent		0x68
uchar8	Write_OneCalRegToData(uchar8 CalRegInData_No, uchar8	*pCalReg)
{
	ulong32	 CalEventDI;
	uchar8	 CalEventData[CLRec_Meter_Bef1_Data_1 + 2];
	uchar8	 V_ReturnData;
	ushort16 DataLen, V_usDataEncode;

/*首先判断序号是否错误*/
	if(CalRegInData_No >= C_MeterICDataNum_T)
	{
		return(C_Cal_NoErr);
	}
/*读对应的校表事件记录，判断该寄存器有没有写过校表记录*/
	CalEventDI = (ulong32) (CalRegInData_No + 1);		/*校表记录中校表参数从1开始，数据层从0开始*/
	CalEventDI = (CalEventDI << 8) & 0x0000FF00;
	CalEventDI = CalEventDI | (CRec_Meter_Bef1_Data_1 & 0xFFFF00FF);
	DataLen = CLRec_Meter_Bef1_Data_1;
	V_ReturnData = InF_Read_Data(CalEventDI, CalEventData, &DataLen, &V_usDataEncode);
	if( ( V_ReturnData == C_OK ) && ( CalEventData[C_HaveWrCalEventFlag_O] ==  C_IsNotWrCalEvent ) )
	{/*对应事件记录能读出，且未写过*/
		DataLen = 3;			/*校表参数固定成3字节*/
		V_ReturnData = InF_Read_RecMeterData(CalRegInData_No, &CalEventData[C_PreCalReg_O], (uchar8 *)&DataLen);
		if(V_ReturnData != C_OK)
		{/*读不出认为上1次为0*/
			CalEventData[C_PreCalReg_O] = 0;
			CalEventData[C_PreCalReg_O+1] = 0;
			CalEventData[C_PreCalReg_O+2] = 0;
		}
		CalEventData[C_HaveWrCalEventFlag_O] = C_HaveNotWrCalEvent;
		InF_Write_Data(C_Msg_Communication, CalEventDI,CalEventData, CLRec_Meter_Bef1_Data_1, SV_Comm_Parse_Local.SafeControlFlag);
	}/*事件记录写错了不管，不能因为写错了直接退出，这样无Flash都不可以校表了*/
/*写数据层校表参数*/
	V_ReturnData = InF_Write_RecMeterData(C_Msg_Communication,pCalReg, 3, SV_Comm_Parse_Local.SafeControlFlag, CalRegInData_No);
	if(V_ReturnData == C_SafeFlagError)
	{
		return(C_Cal_SafeFlagErr);
	}
	else if(V_ReturnData != C_OK)
	{
		return(C_Cal_WrDataErr);
	}
	else
	{
		return(C_OK);
	}
}
/***************************************************************************
函数原型 	Cal_WriteCalStartClock
函数功能	写启动校表
输入参数	SV_Comm_Parse_Local.SafeControlFlag
				*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	SV_Comm_Parse_Local.SafeControlFlag
函数备注	无
***************************************************************************/
void			Cal_WriteCalStartClock(Str_Comm_645 *pV_645Frame)
{
	ushort16	DataLen = CLDate_Time, V_usDataEncode;
	uchar8	SystemClock[CLDate_Time];
	uchar8	V_ReturnData;

	if(InF_Read_Data(CDate_Time, SystemClock, &DataLen, &V_usDataEncode) != C_OK)
	{/*如果时钟读不出，则默认为2000年1月1日，时间不管*/
		SystemClock[CDate_Time_YYH_O] = 0x07;
		SystemClock[CDate_Time_YYL_O] = 0xD0;
		SystemClock[CDate_Time_MM_O] = 0x01;
		SystemClock[CDate_Time_DD_O] = 0x01;
	}
	V_ReturnData = InF_Write_Data(C_Msg_Communication, CRec_Meter_Hp_T_1, SystemClock, CLRec_Meter_Hp_T_1, SV_Comm_Parse_Local.SafeControlFlag);
	if(V_ReturnData != C_OK)
	{
		Comm_Response_Set_ReadErr(C_Cal_WrDataErr, pV_645Frame);
	}
	else
	{
		Comm_Response_Set_ReadErr(C_OK, pV_645Frame);
	}
}

/***************************************************************************
函数原型 	Cal_SetPassword
函数功能	校表过程中设置序列号和校表密码解析并应答
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	无
函数备注	判断校表密码是否正确，不正确才允许写。正确不允许写。
				上位机通过读取序列号，查找自己的数据库才能校表。
				如果查不到，只能更换E2后，才能写。
***************************************************************************/
#define		C_O_CalNo		6
#define		C_O_CalPW		11
void		Cal_SetPassword(Str_Comm_645 *pV_645Frame)
{
	uchar8	V_ReturnData;
	ushort16	DataLen, V_usDataEncode;
	uchar8	buf[CLRec_MeterPassWord];

/*读取数据层校表密码，如果能读出，才允许写。*/
	DataLen = CLRec_MeterPassWord;
	V_ReturnData = InF_Read_Data(CRec_MeterPassWord, buf, &DataLen, &V_usDataEncode);
	if(V_ReturnData == C_OK)
	{/*读出应答非授权*/
		Comm_Response_Set_ReadErr(C_Cal_PWOkButSetCPW, pV_645Frame);
		return;
	}
/*读不出，表示允许写。*/
	SV_Comm_Parse_Local.SafeControlFlag = SV_Comm_Parse_Local.SafeControlFlag | C_W_SafeFlag_3;
	V_ReturnData = InF_Write_Data(C_Msg_Communication, CRec_MeterSequence, &pV_645Frame->Data[C_O_CalNo], CLRec_MeterSequence, SV_Comm_Parse_Local.SafeControlFlag);
	if(V_ReturnData != C_OK)
	{
		Comm_Response_Set_ReadErr(C_Cal_WrDataErr, pV_645Frame);
		return;
	}
	V_ReturnData = InF_Write_Data(C_Msg_Communication, CRec_MeterPassWord, &pV_645Frame->Data[C_O_CalPW], CLRec_MeterPassWord, SV_Comm_Parse_Local.SafeControlFlag);
	if(V_ReturnData == C_OK)
	{
		Comm_Response_Set_ReadErr(C_OK, pV_645Frame);
	}
	else
	{
		Comm_Response_Set_ReadErr(C_Cal_WrDataErr, pV_645Frame);
	}
}

/***************************************************************************
函数原型 	Comm_ReadNxtFrameParse
函数功能	完成后续帧解析
输入参数	*pV_645Frame					:信息帧
输出参数 	无
返回参数	无
全局变量 	通道变量
函数备注	无
***************************************************************************/
void		Comm_ReadNxtFrameParse(Str_Comm_645 *pV_645Frame)
{
	Str_Comm_NxtFrame	Comm_NxtFrame;
	Str_Comm_NxtFrame	*pStr_Comm_NxtFrame;
	uchar8	DataLen;
	uchar8	i;

	pStr_Comm_NxtFrame = &Comm_NxtFrame;

/*判断长度*/
	if(pV_645Frame->DataLen != 0x05)
	{
		return;			/*长度不对，什么都不处理退出。*/
	}
/*获取通道后续帧变量*/
	if( Get_SV_CommNxtFrame( pV_645Frame->ChannelNo, pStr_Comm_NxtFrame ) != C_OK )
	{
		return;			/*出错，什么都不处理。*/
	}

/*首先判断总的标识码是否正确，不正确应答其他错误,NxtF_DataCode=0xFFFFFFFF表示已经没有后续，此时读后续为主动上报*/
	if( ( NxtF_DataCode != pV_645Frame->DI ) && ( NxtF_DataCode != 0xFFFFFFFF ) )
	{
		Comm_Response_Set_ReadErr(C_OtherErr, pV_645Frame);
		return;
	}
	if(NxtF_DataCode == 0xFFFFFFFF)
	{
		NxtF_FrameFinished = C_OK;
	}
/*判断帧序号是否正确*/
	if( ( NxtF_FrameNo == ( pV_645Frame->Data[C_O_FrameNo] + 1 ) )
	 && ( pV_645Frame->Data[C_O_FrameNo] != 0 ) )
	{/* 帧序号是上1帧，重读。此时再判断有没有故障信息主动上报*/
		if(NxtF_HaveReport == C_OK)
		{/*有表示故障信息状态字重读*/
			if( Judge_ReportWithNxtFrame() == C_OK )
			{/*有主动上报从pV_645Frame->Data[C_O_FrameNo+1]开始*/
				Set_ReportStateFrame(&pV_645Frame->Data[C_O_FrameNo + 1], &DataLen);
				/*帧序号直接取发过来的。*/
				pV_645Frame->Data[C_O_FrameNo + 1 + DataLen] = pV_645Frame->Data[C_O_FrameNo];
				DataLen++;
				/*置发送数据*/
				Comm_Response_FromP_Normal(pV_645Frame,&pV_645Frame->Data[C_O_FrameNo + 1], DataLen);
				/*启动已发送定时器及置位已发送状态字节*/
				Set_SV_HaveReportState(&pV_645Frame->Data[C_O_FrameNo + 1 + CLen_DI]);
				NxtF_HaveReport = C_OK;
				Set_SV_CommNxtFrame(pV_645Frame->ChannelNo, pStr_Comm_NxtFrame);
			}
			else
			{/*无主动上报,应答无请求数据*/
				Init_SV_CommNxtFrame(pV_645Frame->ChannelNo);
				Comm_Response_Set_ReadErr(C_OtherErr_645, pV_645Frame);
			}
			return;
		}
		else
		{/*没有表示正常后续帧数据重读*/
			NxtF_FrameNo = pV_645Frame->Data[C_O_FrameNo];
			NxtF_Nxt_DataCode = NxtF_Sub_DataCode;
			for(i = 0; i < LClockLen; i++)
			{
				NxtF_LNxt_Fix_Time[i] = NxtF_LSub_Fix_Time[i];
			}
			NxtF_LNxt_BlockNum = NxtF_LSub_BlockNum;
			for(i = 0; i < CLen_CREnergy; i++)
			{
				NxtF_LNxt_CREnergy[i] = NxtF_LSub_CREnergy[i];
			}
			Comm_ReadNxtFrame(pV_645Frame, pStr_Comm_NxtFrame);
		}
	}
	else if(NxtF_FrameNo != (pV_645Frame->Data[C_O_FrameNo]))
	{/*帧序号错误*/
		Comm_Response_Set_ReadErr(C_OtherErr_645, pV_645Frame);
	}
	else
	{/*下一帧,判断后续帧是否完成，完成则判断故障信息是否需要上报*/
		if(NxtF_FrameFinished == C_OK)
		{/* 完成，判断有无主动上报*/
			if(Judge_ReportWithNxtFrame()==C_OK)
			{/*有主动上报从pV_645Frame->Data[C_O_FrameNo+1]开始*/
				Set_ReportStateFrame(&pV_645Frame->Data[C_O_FrameNo + 1], &DataLen);
				/*帧序号直接取发过来的。*/
				pV_645Frame->Data[C_O_FrameNo + 1 + DataLen] = pV_645Frame->Data[C_O_FrameNo];
				DataLen++;
				/*置发送数据*/
				Comm_Response_FromP_Normal(pV_645Frame, &pV_645Frame->Data[C_O_FrameNo + 1], DataLen);
				/*启动已发送定时器及置位已发送状态字节*/
				Set_SV_HaveReportState(&pV_645Frame->Data[C_O_FrameNo + 1 + CLen_DI]);
				NxtF_HaveReport = C_OK;
				Set_SV_CommNxtFrame(pV_645Frame->ChannelNo, pStr_Comm_NxtFrame);
			}
			else
			{/*无主动上报,应答无请求数据*/
				Init_SV_CommNxtFrame(pV_645Frame->ChannelNo);
				Comm_Response_Set_ReadErr(C_OtherErr_645, pV_645Frame);
			}
			return;
		}
		else
		{/*读下一帧数据	*/
			Comm_ReadNxtFrame(pV_645Frame, pStr_Comm_NxtFrame);
		}
	}

/*程序到这里，如果是主动上报已退出，所以只能是正常后续帧，下一步*/
/*判断是否需要后续帧报故障信息主动上报?*/
	if(Judge_ReportWithNxtFrame()==C_OK)
	{
		Comm_IfHaveNxtFrame_Set_C(pV_645Frame);	/*bit5是有后续帧标志*/
	}
}

/*******************************************************************************
函数原型 Comm_ReadNxtFrame
函数功能 真正的后续帧处理及应答
输入参数 *pV_645Frame:收到的命令帧
		 *pStr_Comm_NxtFrame:后续帧相关结构体
输出参数 无
返回参数 无
全局变量 和通道相关的全局变量(通道缓冲区和后续帧变量)
函数备注 包括帧序号在内，发送缓冲区已置好。
*******************************************************************************/
void Comm_ReadNxtFrame(Str_Comm_645 *pV_645Frame, Str_Comm_NxtFrame *pStr_Comm_NxtFrame)
{
	uchar8	V_ReturnData;
	ulong32	ReadDI;
	uchar8	TB_NxtFrame_LineNo;					/* 1级表行号*/
	uchar8	i;

/*将Nxt->sub，准备重读*/
	NxtF_Sub_DataCode = NxtF_Nxt_DataCode;
	for(i = 0; i < LClockLen; i++ )
	{
		NxtF_LSub_Fix_Time[i] = NxtF_LNxt_Fix_Time[i];
	}
	NxtF_LSub_BlockNum = NxtF_LNxt_BlockNum;
	for(i = 0; i < CLen_CREnergy; i++ )
	{
		NxtF_LSub_CREnergy[i] = NxtF_LNxt_CREnergy[i];
	}

	if(Is_NormalReadingLoadCurve(NxtF_DataCode) == C_OK)
	{	/*13规范负荷记录读取*/
		V_ReturnData = NormalReadingLoadCurve(pV_645Frame, pStr_Comm_NxtFrame);
	}
	else if(Is_SeqReadingLoadCurve(NxtF_DataCode) == C_OK)
	{	/*补遗4负荷曲线读取*/
		V_ReturnData = SeqReadingLoadCurve(pV_645Frame, pStr_Comm_NxtFrame);
	}
	else
	{	/*不是上面2种情况，就是固定分帧。首先查阅1级表，查一级表,得到行号*/
		if((pV_645Frame->DI & C_JudgeDI0FF) == C_JudgeDI0FF)
		{
			ReadDI = pV_645Frame->DI;  /* 1级表中失流、过流事件DI0FF*/
		}
		else
		{
			ReadDI = (pV_645Frame->DI & 0xFFFFFF00) | 0x00000001;			/* 1级表中屏蔽了次数*/
		}

		for( TB_NxtFrame_LineNo = 0; TB_NxtFrame_LineNo < C_TBNxtFrameNum; TB_NxtFrame_LineNo++ )
		{
			if(ReadDI == TB_NxtFrame[TB_NxtFrame_LineNo].DataCode)
			{
				break;
			}
		}

		if(TB_NxtFrame_LineNo >= C_TBNxtFrameNum)
		{/* 1级表中查阅失败，应答无请求数据退出。*/
			Init_SV_CommNxtFrame(pV_645Frame->ChannelNo);
			Comm_Response_Set_ReadErr(C_No_Request_data, pV_645Frame);
			return;
		}

		/*根据1级表中的方法调用不同的函数C_Freeze_Method/C_Prog_SubDI_LBit4/C_CarryingSubDI*/
		if(TB_NxtFrame[TB_NxtFrame_LineNo].Method == C_Freeze_Method)
		{/*冻结的方法*/
			V_ReturnData = ReadFreezeReg_NxtFrame(pStr_Comm_NxtFrame, pV_645Frame,TB_NxtFrame_LineNo);
		}
		else if(TB_NxtFrame[TB_NxtFrame_LineNo].Method == C_Prog_SubDI_LBit4)
		{/*分项标识码DI0最低4位是次数的方法，次数固定为0A*/
			V_ReturnData = ReadProgRecordReg_NxtFrame(pStr_Comm_NxtFrame, pV_645Frame, TB_NxtFrame_LineNo);
		}
		else if(TB_NxtFrame[TB_NxtFrame_LineNo].Method == C_Event_Method)
		{/*失流、过流*/
			V_ReturnData = ReadCurrFFRecordReg_NxtFrame(pStr_Comm_NxtFrame, pV_645Frame, TB_NxtFrame_LineNo);
		}
		else
		{/*C_CarryingSubDI方法，目前没有，应答其他错误退出,不可能到这里*/
			Init_SV_CommNxtFrame(pV_645Frame->ChannelNo);
			Comm_Response_Set_ReadErr(C_OtherErr, pV_645Frame);
			return;
		}
	}

	/*置通信缓冲区帧序号*/
	Comm_SetFrameNo(pV_645Frame->ChannelNo, NxtF_FrameNo);
	NxtF_FrameNo++;
	if(V_ReturnData == C_HaveNxtFrame)
	{
		Comm_IfHaveNxtFrame_Set_C(pV_645Frame);					/*置通信缓冲区有后续帧*/
		NxtF_FrameFinished = C_Error;							/*表示有后续帧*/
		NxtF_HaveReport = C_Error;								/*表示未主动上报过*/
	}
	else
	{
		NxtF_FrameFinished = C_OK;								/*表示没有后续帧*/
		NxtF_HaveReport = C_Error;								/*表示未主动上报过*/
	}
	Set_SV_CommNxtFrame(pV_645Frame->ChannelNo, pStr_Comm_NxtFrame);
}

/*******************************************************************************
函数原型 Is_NormalReadingLoadCurve
函数功能 判断是否为正常读负荷曲线标识码
输入参数 DataCode:读取的标识码
输出参数 无
返回参数 C_OK/C_Error
全局变量 无
函数备注 无
*******************************************************************************/
uchar8 Is_NormalReadingLoadCurve(ulong32 DataCode)
{
/*DI3为06*/
	if( (DataCode & 0xFF000000) != 0x06000000 )
	{
		return(C_Error);
	}
/*DI2在0-6之间*/
	if( (DataCode & 0x00FF0000) > 0x00060000 )
	{
		return(C_Error);
	}
/*DI1/DI0在0000-0002之间*/
	if( (DataCode & 0x0000FFFF) > 0x00000002 )
	{
		return(C_Error);
	}
	return(C_OK);
}

/***************************************************************************
函数原型 	Is_SeqReadingLoadCurve
函数功能	判断是否为连续读负荷曲线标识码
输入参数	DataCode					:读取的标识码
输出参数 	无
返回参数	C_OK/C_Error
全局变量 	无
函数备注	无
***************************************************************************/
uchar8		Is_SeqReadingLoadCurve(ulong32	DataCode)
{
	ulong32	DI1Bak;
	ulong32	DI0Bak;

/*DI1为1-8 ，DI0根据DI1不同而不同。*/
	DI1Bak = DataCode & 0xFFFFFF00;
	DI0Bak = DataCode & 0x000000FF;
	switch(DI1Bak)
	{
		case		0x06100100:			/*电压*/
		case		0x06100200:			/*电流*/
			if( ( DI0Bak == 0 ) || ( ( DI0Bak > 0x00000003 ) && ( DI0Bak != 0xFF ) ) )
			{
				return(C_Error);
			}
			return(C_OK);
		case		0x06100300:			/*有功功率*/
		case		0x06100400:			/*无功功率*/
		case		0x06100500:			/*功率因数*/
			if( ( DI0Bak > 0x00000003 ) && ( DI0Bak != 0xFF ) )
			{
				return(C_Error);
			}
			return(C_OK);
		case		0x06100600:			/*有功无功曲线*/
		case		0x06100700:			/* 四象限无功曲线*/
			if( ( DI0Bak == 0 ) || ( ( DI0Bak > 0x00000004 ) && ( DI0Bak != 0xFF ) ) )
			{
				return(C_Error);
			}
			return(C_OK);
		case		0x06100800:			/*需量*/
			if( ( DI0Bak == 0 ) || ( ( DI0Bak > 0x00000002 ) && ( DI0Bak != 0xFF ) ) )
			{
				return(C_Error);
			}
			return(C_OK);
		default:
			return(C_Error);
	}
}

/***********************负荷记录645数据标识对应698表格**************************/
const Str_LoadRecord645DITo698OAD Str_LoadRecord645To698[] =
{
	/*电压类*/
	CPhaseA_Volage,			CEarlietRec1_Load,	CLVoltageA_Load,		0x00,
	CPhaseB_Volage,			CEarlietRec1_Load,	CLVoltageB_Load,		0x02,
	CPhaseC_Volage,			CEarlietRec1_Load,	CLVoltageC_Load,		0x04,
	/*电流类*/
	CPhaseA_Curr,			CEarlietRec1_Load,	CLCurrentA_Load,		0x06,
	CPhaseB_Curr,			CEarlietRec1_Load,	CLCurrentB_Load,		0x09,
	CPhaseC_Curr,			CEarlietRec1_Load,	CLCurrentC_Load,		0x0C,
	/*频率类*/
	CElecNet_Freq,			CEarlietRec1_Load,	CLElecNet_Freq,			0x0F,
	/*有功功率类*/
	CInstant_TolAcPow,		CEarlietRec2_Load,	CLActPowerT_Load,		0x00,
	CInstantA_AcPow,		CEarlietRec2_Load,	CLActPowerA_Load,		0x03,
	CInstantB_AcPow,		CEarlietRec2_Load,	CLActPowerB_Load,		0x06,
	CInstantC_AcPow,		CEarlietRec2_Load,	CLActPowerC_Load,		0x09,
	/*无功功率类*/
	CInstant_TolRePow,		CEarlietRec2_Load,	CLReActPowerT_Load,		0x0C,
	CInstantA_RePow,		CEarlietRec2_Load,	CLReActPowerA_Load,		0x0F,
	CInstantB_RePow,		CEarlietRec2_Load,	CLReActPowerB_Load,		0x12,
	CInstantC_RePow,		CEarlietRec2_Load,	CLReActPowerC_Load,		0x15,
	/*功率因素类*/
	CTol_PowerFactor,		CEarlietRec3_Load,	CLPowFactorT_Load,		0x00,
	CPhaseA_PowerFactor,	CEarlietRec3_Load,	CLPowFactorA_Load,		0x02,
	CPhaseB_PowerFactor,	CEarlietRec3_Load,	CLPowFactorB_Load,		0x04,
	CPhaseC_PowerFactor,	CEarlietRec3_Load,	CLPowFactorC_Load,		0x06,
	/*有无功总电能类*/
	CPos_Ac_Tol_En_0,		CEarlietRec4_Load,	CLPosActEnergyT_Load,	0x00,
	CRev_Ac_Tol_En_0,		CEarlietRec4_Load,	CLRevActEnergyT_Load,	0x04,
	CCom_Re1_Tol_En_0,		CEarlietRec4_Load,	CLComReAct1T_Load,		0x08,
	CCom_Re2_Tol_En_0,		CEarlietRec4_Load,	CLComReAct2T_Load,		0x0C,
	/*四象限无功电能类*/
	CQua1_Re_Tol_En_0,		CEarlietRec5_Load,	CLReActQuad1_Load,		0x00,
	CQua2_Re_Tol_En_0,		CEarlietRec5_Load,	CLReActQuad2_Load,		0x04,
	CQua3_Re_Tol_En_0,		CEarlietRec5_Load,	CLReActQuad3_Load,		0x08,
	CQua4_Re_Tol_En_0,		CEarlietRec5_Load,	CLReActQuad4_Load,		0x0C,
	/*当前需量类*/
	CCurr_AcDemand,			CEarlietRec6_Load,	CLActDemand_Load,		0x00,
	CCurr_ReDemand,			CEarlietRec6_Load,	CLReActDemand_Load,		0x03,
};
#define Str_LoadRecord645To698_Len	sizeof(Str_LoadRecord645To698) / sizeof(Str_LoadRecord645DITo698OAD)

/***********************************负荷曲线645数据标识对应698表格*****************************************/
const Str_698To645LoadReadStatus Str_645To698LoadStatus[]=
{
	/*电压类*/
	CPhaseA_Volage,     	1,  0xFF,  	CVoltageA_Load,			CLVoltageA_Load,
	CPhaseB_Volage,     	1,  0xFF,  	CVoltageB_Load,			CLVoltageB_Load,
	CPhaseC_Volage,     	1,  0xFF,  	CVoltageC_Load,			CLVoltageC_Load,
	CPhaseFF_Volage,    	1,  0xFF,  	CVoltageBlock_Load,		CLVoltageBlock_Load,
	/*电流类*/
	CPhaseA_Curr,       	1,	0xFF,  	CCurrentA_Load,			CLCurrentA_Load,
	CPhaseB_Curr,       	1,	0xFF,  	CCurrentB_Load,			CLCurrentB_Load,
	CPhaseC_Curr,       	1,	0xFF,  	CCurrentC_Load,			CLCurrentC_Load,
	CPhaseFF_Curr,      	1,	0xFF,  	CCurrentBlock_Load,		CLCurrentBlock_Load,
	/*有功功率类*/
	CInstant_TolAcPow,  	1,	0xFF,  	CActPowerT_Load,		CLActPowerT_Load,
	CInstantA_AcPow,    	1,	0xFF,  	CActPowerA_Load,		CLActPowerA_Load,
	CInstantB_AcPow,    	1,	0xFF,  	CActPowerB_Load,		CLActPowerB_Load,
	CInstantC_AcPow,    	1,	0xFF,  	CActPowerC_Load,		CLActPowerC_Load,
	CInstantFF_AcPow,   	1,	0xFF,  	CActPowerBlock_Load,	CLActPowerBlock_Load,
	/*无功功率类*/
	CInstant_TolRePow,  	1,  0xFF,  	CReActPowerT_Load,		CLReActPowerT_Load,
	CInstantA_RePow,    	1,  0xFF,  	CReActPowerA_Load,		CLReActPowerA_Load,
	CInstantB_RePow,    	1,  0xFF,  	CReActPowerB_Load,		CLReActPowerB_Load,
	CInstantC_RePow,    	1,  0xFF,  	CReActPowerC_Load,		CLReActPowerC_Load,
	CInstantFF_RePow,   	1,  0xFF,  	CReActPowerBlock_Load,	CLReActPowerBlock_Load,
	/*功率因素类*/
	CTol_PowerFactor,   	1,  0xFF,  	CPowFactorT_Load,		CLPowFactorT_Load,
	CPhaseA_PowerFactor,	1,  0xFF,  	CPowFactorA_Load,		CLPowFactorA_Load,
	CPhaseB_PowerFactor,	1,  0xFF,  	CPowFactorB_Load,		CLPowFactorB_Load,
	CPhaseC_PowerFactor,	1,  0xFF,  	CPowFactorC_Load,		CLPowFactorC_Load,
	CPhaseFF_PowerFactor,	1,  0xFF,  	CPowFactorBlock_Load,	CLPowFactorBlock_Load,
	/*有无功总电能类*/
	CPos_Ac_Tol_En_0,   	1,  0,      CPosActEnergyT_Load,	CLPosActEnergyT_Load,
	CRev_Ac_Tol_En_0,   	1,  0,      CRevActEnergyT_Load,	CLRevActEnergyT_Load,
	CCom_Re1_Tol_En_0,  	1,  0,      CComReAct1T_Load,		CLComReAct1T_Load,
	CCom_Re2_Tol_En_0,  	1,  0,      CComReAct2T_Load,		CLComReAct2T_Load,
	CTotEnergyBlock_698,	4,  0,      CTotEnergyBlock_Load,	CLTotEnergyBlock_Load,
	/*四象限无功电能类*/
	CQua1_Re_Tol_En_0,	    1,  0,      CReActQuad1_Load,		CLReActQuad1_Load,
	CQua2_Re_Tol_En_0,	    1,  0,      CReActQuad2_Load,		CLReActQuad2_Load,
	CQua3_Re_Tol_En_0,	    1,  0,      CReActQuad3_Load,		CLReActQuad3_Load,
	CQua4_Re_Tol_En_0,	    1,  0,      CReActQuad4_Load,		CLReActQuad4_Load,
	CTotQua_Re_Block_698,	4,  0,      CReActQuadTBlock_Load,	CLReActQuadTBlock_Load,
	/*当前需量类*/
	CCurr_AcDemand,     	1,	0xFF,	CActDemand_Load,		CLActDemand_Load,
	CCurr_ReDemand,     	1,	0xFF,	CReActDemand_Load,		CLReActDemand_Load,
	CCurr_Demand_Block, 	2,	0xFF,	CDemandBlock_Load,		CLDemandBlock_Load
};
#define Str_645To698LoadStatus_Len  sizeof(Str_645To698LoadStatus) / sizeof(Str_698To645LoadReadStatus)
/***********************************负荷记录的对应698表格*****************************************/
const Str_698To645DFreezReadStatus Str_698To645DFreezRead[]=
{
	CFreeTime,     	        1,  CD_Free_Time_1,			CLD_Free_Time_1,
	CPos_Ac_En_FF_0,     	5,  CD_Free_Pos_Ac_En_1,    CLD_Free_Pos_Ac_En_1,
	CRev_Ac_En_FF_0,     	5,  CD_Free_Rev_Ac_En_1,    CLD_Free_Rev_Ac_En_1,
	CCom_Re1_En_FF_0,    	5,  CD_Free_Com_Re1_En_1,   CLD_Free_Com_Re1_En_1,
	CCom_Re2_En_FF_0,       5,	CD_Free_Com_Re2_En_1,   CLD_Free_Com_Re2_En_1,
	CQua1_Re_En_FF_0,       5,	CD_Free_Qua1_Re_En_1,   CLD_Free_Qua1_Re_En_1,
	CQua2_Re_En_FF_0,       5,	CD_Free_Qua2_Re_En_1,   CLD_Free_Qua2_Re_En_1,
	CQua3_Re_En_FF_0,      	5,	CD_Free_Qua3_Re_En_1,   CLD_Free_Qua3_Re_En_1,
	CQua4_Re_En_FF_0,  	    5,	CD_Free_Qua4_Re_En_1,   CLD_Free_Qua4_Re_En_1,
	CPos_Ac_De_FF_0,    	5,	CD_Free_Pos_Ac_De_1,    CLD_Free_Pos_Ac_De_1,
	CRev_Ac_De_FF_0,    	5,	CD_Free_Rev_Ac_De_1,    CLD_Free_Rev_Ac_De_1,
	CInstantFF_AcPow,    	8,	CD_Free_Variable_1,		CLD_Free_Variable_1,
};
#define Str_698To645DFreezRead_Len  sizeof(Str_698To645DFreezRead) / sizeof(Str_698To645DFreezReadStatus)

/***********************************整点冻结的对应698表格*****************************************/
const Str_698To645DFreezReadStatus Str_698To645HFreezRead[]=
{
	CFreeTime,     	        1,  CH_Free_Time_1,				CLH_Free_Time_1,
	CPos_Ac_Tol_En_0,     	1,  CH_Free_Pos_Ac_TolEn_1,    	CLH_Free_Pos_Ac_TolEn_1,
	CRev_Ac_Tol_En_0,     	1,  CH_Free_Rev_Ac_En_1,    	CLH_Free_Rev_Ac_En_1,
};
#define Str_698To645HFreezRead_Len  sizeof(Str_698To645DFreezRead)/sizeof(Str_698To645DFreezReadStatus)

/***************************************************************************
函数原型 	SeqReadingLoadCurve_11
函数功能	11命令连续读取负荷曲线
输入参数	*pV_645Frame			:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	通信通道缓冲区
函数备注	进入本命令，标识码肯定正确
***************************************************************************/
ulong32	SF_RecordingCodeConversion(ulong32 DataCode, uchar8 *p_Line, uchar8 *p_Num, uchar8 *p_Len, uchar8 *p_SuppleData)
{
	ulong32	V_ReturnCode = 0xFFFFFFFF;
    uchar8  i;

    for(i = 0;i< Str_645To698LoadStatus_Len; i++ )
    {
        if(DataCode == Str_645To698LoadStatus[i].V_ulDataId645)
        {
            V_ReturnCode = Str_645To698LoadStatus[i].V_ulDataId698;
            *p_Line = i;
            *p_Num = Str_645To698LoadStatus[i].V_Num;
            *p_SuppleData = Str_645To698LoadStatus[i].V_SuppleData;
            *p_Len = Str_645To698LoadStatus[i].V_ucDataLen;
            break;
        }
    }
    return  V_ReturnCode;
}
/*******************************************************************************
函数原型 SF_LoadRecord645DITo698OAD
函数功能	 负荷记录645数据标识转换为698数据标识
输入参数
输出参数
返回参数
全局变量
函数备注 进入本命令，标识码肯定正确
*******************************************************************************/
void SF_LoadRecord645DITo698OAD(ulong32 V_ul645DataCode, ulong32 *P_ul698DataCode, uchar8 *P_uc698DataCodeLen, uchar8 *P_uc698DataCodeOffset)
{
	uchar8 V_ucI = 0, V_ucJ = 0;

	for(V_ucI = 0; V_ucI < Str_LoadRecord645To698_Len; V_ucI ++)
	{
		if( ( ( V_ul645DataCode & 0xFFFFFF00 ) == Str_LoadRecord645To698[V_ucI].V_ulDataDI645 )
		 || ( ( V_ul645DataCode & 0x00FF0000 ) == 0x00000000 ) )
		{
			*(P_ul698DataCode + V_ucJ) = Str_LoadRecord645To698[V_ucI].V_ulDataOAD698;
			*(P_uc698DataCodeLen + V_ucJ) = Str_LoadRecord645To698[V_ucI].V_ucDataLen;
			*(P_uc698DataCodeOffset + V_ucJ) = Str_LoadRecord645To698[V_ucI].V_ucDataOffset;
			V_ucJ ++;
		}
	}
}
/*******************************************************************************
函数原型 SF_LoadRecordingCodeConversion
函数功能	 645负荷曲线数据标识转换为698关联列表
输入参数
输出参数
返回参数
全局变量
函数备注 进入本命令，标识码肯定正确
*******************************************************************************/
uchar8	SF_LoadRecordingCodeConversion(ulong32 DataCode, ulong32 *p_datacode, uchar8 *p_Len, uchar8 *p_SuppleData)
{
    ulong32 V_CodeTemp;
    uchar8  j, V_Line = 0, V_Num = 0, V_ReturnFlag = 0xFF;

    V_CodeTemp = SF_RecordingCodeConversion(DataCode, &V_Line, &V_Num, p_Len, p_SuppleData);
    if(V_CodeTemp != 0xFFFFFFFF)
    {
        if(V_Num != 1)
        {
            for(j = 0; j < V_Num; j++ )
            {
                *(p_datacode + ( V_Num - 1 - j ) ) = Str_645To698LoadStatus[V_Line - j - 1].V_ulDataId698;
            }
            V_ReturnFlag = V_Num;
        }
        else
        {
            *p_datacode = V_CodeTemp;
            V_ReturnFlag = 1;
        }
    }

    return V_ReturnFlag;
}

/***************************************************************************
函数原型 	SeqReadingLoadCurve_11
函数功能	11命令连续读取负荷曲线
输入参数	*pV_645Frame			:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	通信通道缓冲区
函数备注	进入本命令，标识码肯定正确
***************************************************************************/
void SF_TimeSequencing(ushort16 V_BlockNum, uchar8 *p_SaveFreezeTime, uchar8 *p_SequencingFreezeTime)
{
    uchar8 i;
    for( i = 0; i < V_BlockNum; i++ )
    {
        memcpy(p_SequencingFreezeTime + ( V_BlockNum - i - 1 ) * 6 , p_SaveFreezeTime + i * 6, 6);
    }
}
/**************************************************************************************
Function:uchar8 SF_FirstTime_LoadProfile
Description:根据起始时间和数据层的实际负荷记录点,取出归一时间
Input:	V_ulDataId-数据标识
		*P_ucInteTime-间隔时间
		* P_ucReadStartTime -读取负荷记录的起始时间，5字节（YYMMDDhhmm）
		*P_ucStartTime-最早负荷记录事件,6字节
		*P_ucParaTime-负荷起始时间
		* P_SendTime –用于输出,返回时间首地址,5字节
Output: * P_SendTime –实际返回数据中第一个负荷记录的记录时间
Return:	V_ucflag,为0表示不用重新计算块数，C_ReCal表示需重新计算
Calls:
Called By:SF_SepRead_LoadProfile
Influence:
Author:
Tips:
Others:
*****************************************************************************************/
uchar8 SF_FirstTime_LoadProfile(uchar8 *P_ucInteTime, uchar8 *P_ucReadStartTime, uchar8 *P_ucStartTime, uchar8 *P_ucParaTime, uchar8 *P_ucSendTime)
{
	uchar8 V_ucTimeBuff[CLLoad_Rec_Time_Year + 1];				/*归一时间中间变量缓存*/
	uchar8 V_ucflag = 0, V_ucIntTime = *P_ucInteTime;			/*间隔时间*/
	ulong32 V_ulSubMins = 0;

	V_ucTimeBuff[C_Sec] = 0;									/*将抄读时间扩为6字节*/
	PF_CopyDataBytes(P_ucReadStartTime, &V_ucTimeBuff[C_Minute], CLLoad_Rec_Time_Year);               		/*抄读时间*/

	if( PF_Campare_Data( &V_ucTimeBuff[C_Minute], &P_ucStartTime[C_Minute], C_LoadTimeLen ) == C_LessThan )	/*抄读时间比最早负荷记录时间*/
	{
		PF_CopyDataBytes(&P_ucStartTime[C_Minute], &V_ucTimeBuff[C_Minute], CLLoad_Rec_Time_Year);

		V_ucflag = C_ReCal;
	}
	PF_TimeSub_Min(V_ucTimeBuff, P_ucParaTime, &V_ulSubMins);	/*取抄读时间与负荷起始时间差值*/

	if( ( ( V_ulSubMins % V_ucIntTime ) != 0 ) && ( V_ucIntTime != 0 ) )		/*差值不能整除间隔时间,则往后取最近一个整除点*/
	{
		V_ulSubMins = V_ucIntTime - ( V_ulSubMins % V_ucIntTime );

		SF_MinsAdd_LoadProfile(&V_ucTimeBuff[C_Minute], V_ulSubMins, &V_ucTimeBuff[C_Minute]);

		V_ucflag = C_ReCal;
	}
	PF_CopyDataBytes(&V_ucTimeBuff[C_Minute], P_ucSendTime, CLLoad_Rec_Time_Year);

	return V_ucflag;
}

/***************************************************************************
函数原型 	SeqReadingLoadCurve_11
函数功能	11命令连续读取负荷曲线
输入参数	*pV_645Frame			:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	通信通道缓冲区
函数备注	进入本命令，标识码肯定正确
***************************************************************************/
uchar8 SF_TimeZone_LoadProfile(uchar8 V_ucIntTime, uchar8 *P_ucBlockNum, uchar8 *P_ucTime, uchar8 *P_ucLoadEarTime, uchar8 *P_ucLoadStartTime, uchar8 *P_ucLoadEndTime)
{
	uchar8  V_ucCurrentTime[CLDate_Time];										/*最早负荷记录时间和当前时间*/
	uchar8  V_ucFirstTime[C_LoadTLength + 1], V_ucEndTime[C_LoadTLength + 1];	/*连续抄读第一块和截止块时间*/
	ulong32 V_ulSubMins = 0;
	uchar8  V_ucReturnTemp, V_ucFlag = 0, i;
	ushort16 V_ucLength, V_usDataEncode;
	uchar8  V_ucParaTime[CLLoad_Rec_Time_Year + 1] = {0x00, 0x00, 0x00, 0x01, 0x01, 0x19};
    uchar8  V_ucTime[6];

	V_ucFirstTime[C_Sec] = 0;													/*秒位补0,时间求差时使用*/
	V_ucEndTime[C_Sec] = 0;

	V_ucParaTime[C_Sec] = 0;

	V_ucLength = CLDate_Time;/*此处读出时间为hex格式的7字节时间，本函数后期会重新调整，使用的时候再核对，lzy 20211023*/
	InF_Read_Data(CDate_Time, V_ucCurrentTime, &V_ucLength, &V_usDataEncode);	/*读取当前时间*/
	V_ucFlag = SF_FirstTime_LoadProfile(&V_ucIntTime, P_ucTime, &P_ucLoadEarTime[C_Sec], &V_ucParaTime[C_Sec], &V_ucFirstTime[C_Minute]);	/*获取归一时间*/

	V_ucTime[0] = 0;
	memcpy(V_ucTime + 1, P_ucTime, 5);
	PF_TimeSub_Min(V_ucTime, V_ucParaTime, &V_ulSubMins);						/*取抄读时间与负荷起始时间差值*/
	if( ( ( V_ulSubMins % V_ucIntTime ) != 0 ) && ( V_ucIntTime != 0 ) )		/*差值不能整除间隔时间,则往后取最近一个整除点*/
	{
		V_ulSubMins = V_ucIntTime - ( V_ulSubMins % V_ucIntTime );
		SF_MinsAdd_LoadProfile(P_ucTime, V_ulSubMins, &V_ucTime[C_Minute]);		/*读起始时间归一*/
	}

	SF_MinsAdd_LoadProfile(V_ucTime + 1, (*P_ucBlockNum - 1) * V_ucIntTime, &V_ucEndTime[C_Minute]);	/*计算出截止时间*/

	if(PF_Campare_Data(&V_ucEndTime[C_Minute], &V_ucCurrentTime[C_Minute], C_LoadTimeLen) == C_GreaterThan)
	{
		PF_CopyDataBytes(&V_ucCurrentTime[C_Minute], &V_ucEndTime[C_Minute], C_LoadTimeLen);

		V_ucFlag = C_ReCal;
	}
	V_ucReturnTemp = PF_Campare_Data(&V_ucFirstTime[C_Minute], &V_ucEndTime[C_Minute], C_LoadTimeLen);

	if(V_ucReturnTemp == C_GreaterThan)
	{/*第一个数据时间大于截止时间，返回无数据*/
		*P_ucBlockNum = 0;
		return C_NoData;
	}
	else if(V_ucReturnTemp == C_Equal)
	{
		*P_ucBlockNum = 1;
	}
	else if(V_ucFlag == C_ReCal)
	{
		PF_TimeSub_Min(V_ucEndTime, V_ucFirstTime, &V_ulSubMins);/*计算归一时间和截止时间的时间差*/

		*P_ucBlockNum = V_ulSubMins / V_ucIntTime + 1;/*算出归一时间后更新总抄读块数*/
	}
	for( i = 0; i < 6; i++ )
	{
		*(P_ucLoadStartTime + i) = V_ucFirstTime[i];
		*(P_ucLoadEndTime + i) = V_ucEndTime[i];
	}
	return V_ucReturnTemp;
}

/*******************************************************************************
函数原型 SeqReadingLoadCurve_11
函数功能 11命令连续读取负荷曲线
输入参数 *pV_645Frame:接收到的数据帧
输出参数 无
返回参数 无
全局变量 通信通道缓冲区
函数备注 进入本命令，标识码肯定正确
*******************************************************************************/
uchar8 SeqReadingLoadCurve(Str_Comm_645 *pV_645Frame, Str_Comm_NxtFrame *pStr_Comm_NxtFrame)
{
	uchar8 j = 0;
	uchar8 V_ucRetrun = C_OK;
	ushort16 V_usDataLen = 0, V_usReadRecordNum = 0;
	uchar8 V_DataTemp[C_645FreezeMAXRelatedOAD * C_698To645EnergyBlockLength + 5 + 10] = {0};
	uchar8 V_DataTempBuffer[C_645FreezeMAXRelatedOAD * C_698To645EnergyBlockLength + 5 + 10] = {0};
	uchar8 V_ucDataTempOffset = 0,V_ucDataBufferOffset = 0;
	uchar8 V_EndTime[6] = {0, 0, 0, 0, 0, 0};
	uchar8 V_IntervalTime8[4] = {0, 0, 0, 0};
	ulong32 V_IntervalTime32 = 0;	/*用于计算结束时间*/
	ulong32 p_datacode[6] = {0x50020000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
	uchar8 V_TimeZone[12] = {0};
	uchar8 V_ReadOADLen = 0;
	uchar8 V_LastNumber = 0;
	uchar8 V_SuppleDataCycle = 0, V_SuppleDataType = 0;
	ushort16 V_usReadRecordNumOriginal = 0;
	uchar8 V_ucTotalNum = 0;
	uchar8 V_ucLoadStartTime[6] = {0, 0, 0, 0, 0, 0}, V_ucLoadEndTime[6] = {0, 0, 0, 0, 0, 0};
	uchar8 *V_DataSuppleTemp;
	uchar8 LenFor_Data = 0;			/*缓冲区可被写的总的长度*/
	uchar8 V_LAheadTime[6] = {0}, V_LAheadTimeDataBuf[20] = {0};
	uchar8 V_TotalFrameLen = 0;
	uchar8 V_ucIntTime = 0, V_ucPlanNum = 0;
    uchar8 V_ucDataBuf[4] = {0}, i = 0, V_Flag = 0;
    ushort16 V_ulIntTime16 = 0;
	ushort16 V_usEnergyLen = 0;
	uchar8 V_SequencingFreezeTime[C_645FreezeTimeBufLen] = {0}, V_SaveFreezeTimeBuf[C_645FreezeTimeBufLen] = {0};
	ushort16 V_usOADTabBufferLen = 0, V_usDataEncode;
	uchar8 V_ucOADTabBuffer[C_MAXRelatedOAD * 6] = {0};
	ushort16 V_usOADNO = 0;
	ulong32 V_ulNature = 0;
	ulong32 V_ulReadOADBuf_All[C_MAXRelatedOAD] = {0};
	uchar8 V_ucOADOffset = 0, V_ucOADTabNum = 0, V_ucTabNum = 0;
	ushort16 V_usNum = 0, V_usNumData = 0;
	uchar8 V_ucOADDatalen = 0, V_ucOADDataNum = 0, V_ucOADNum = 0, V_ucFillData;
	uchar8 V_ucDatacodeBufLen = 0;

	V_DataSuppleTemp = &pV_645Frame->Data[C_11_SData];

	if(NxtF_FrameNo == 0)
	{
		LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - 5 - 1;		/*扣去1的目的，最后可能要帧序号*/
	}
	else
	{
		LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - 1;			/*扣去1的目的，最后可能要帧序号*/
	}
	/*调用读命令，根据返回值置位C*/
	/*V_ReturnData = SeqReadingLoadCurve(pV_645Frame,pStr_Comm_NxtFrame);*/

	/*******************645格式负荷记录格式调整为698分钟冻结格式*****************/
	SF_LoadRecordingCodeConversion(NxtF_DataCode, (p_datacode + 1), &V_ReadOADLen, &V_SuppleDataType);	/*645转698标识码*/

	/***获取对应的分钟冻结周期,不同方案会有不同***/
	V_ucDatacodeBufLen = 0x05;				/*去掉第一个OAD 0x50020200*/
	V_Flag = SF_GetMinFreezeCycle(p_datacode, V_ucDatacodeBufLen, &V_ucPlanNum, &V_ulIntTime16);

	if(V_Flag != C_OK)
	{
		V_usDataLen = 0;
		Comm_11_03Response_Normal(pV_645Frame, V_DataTemp, V_usDataLen);
		V_ucRetrun = C_NoNxtFrame;
		return V_ucRetrun;
	}

	if(V_ulIntTime16 > 0xFF)
	{
		V_ulIntTime16 = 0xFF;
	}

	PF_Ushort16ToBuffer2(V_ucDataBuf, &V_ulIntTime16);
	V_ucIntTime = V_ucDataBuf[0];

	for(i = 0; i < 5; i++ )
	{
		if(p_datacode[i + 1] != 0xFFFFFFFF)
		{
			PF_Ulong32ToBuffer4(V_ucDataBuf, &p_datacode[i + 1], 4);
			V_ucDataBuf[1] |= V_ucPlanNum;
			PF_Buffer4ToUlong32(V_ucDataBuf, &p_datacode[i + 1], 4);
		}
		else
		{
			break;
		}
	}
	/*************************由读起始时间确定结束时间**************************/
	V_IntervalTime32 = ( NxtF_LNxt_BlockNum ) * V_ucIntTime;
	PF_Ulong32ToBuffer4( V_IntervalTime8, &V_IntervalTime32, 4 );
	PF_Buffer4ToUlong32( V_IntervalTime8, &V_IntervalTime32, 4 );
	SF_MinsAdd_LoadProfile( NxtF_LNxt_Fix_Time, V_IntervalTime32, (V_EndTime + 1) );

	/*************************调用接口函数读取冻结记录**************************/
	/***************用645的方法获取负荷连续抄读的起始、结束时间和块数************/
	memset(V_SaveFreezeTimeBuf, 0x00, C_645FreezeTimeBufLen);				/*数据去过后将缓存中的数据清理*/
	memset(V_SequencingFreezeTime, 0x00, C_645FreezeTimeBufLen);
	V_SaveFreezeTimeBuf[0] = 0x68;
	memset(V_TimeZone, 0x00, 12);
	memcpy(V_TimeZone + 1, NxtF_LNxt_Fix_Time, 5);
	memcpy(V_TimeZone + 7, V_EndTime + 1, 5);
	V_usReadRecordNum = 0;
	V_usDataLen = C_645FreezeMAXRelatedOAD * C_698To645EnergyBlockLength + 5;
	V_ucRetrun = InF_ReadFreezeData(p_datacode, V_TimeZone, V_DataTemp, &V_usReadRecordNum, &V_usDataLen, V_ucIntTime, V_SaveFreezeTimeBuf, C_698EarLoadMode);
	if(V_ucRetrun != C_698EarLoadMode)
	{
		V_ucTotalNum = 0;
	}
	else
	{
		V_ucTotalNum = NxtF_LNxt_BlockNum;
		SF_TimeZone_LoadProfile(V_ucIntTime, &V_ucTotalNum, NxtF_LNxt_Fix_Time, V_TimeZone, V_ucLoadStartTime, V_ucLoadEndTime);
	}

    if(NxtF_FrameNo == 0)
    {
        NxtF_LNxt_BlockNum = V_ucTotalNum;
        NxtF_LNxt_TotalBlockNum = V_ucTotalNum;
        NxtF_LNxt_ReadedBlockNum = 0;
        V_TotalFrameLen = 5;
    }

	if(V_ReadOADLen != 0)
	{
		V_LastNumber = LenFor_Data / V_ReadOADLen;
		if(NxtF_LNxt_BlockNum > V_LastNumber)
		{
			NxtF_LNxt_BlockNum -= V_LastNumber;
		}
		else
		{
			V_LastNumber = NxtF_LNxt_BlockNum;
			NxtF_LNxt_BlockNum = 0;
		}
		SF_MinsAdd_LoadProfile( ( V_ucLoadStartTime + 1 ), ( ( V_LastNumber - 1 ) * V_ucIntTime ), ( V_ucLoadEndTime + 1 ) );	/**区间2算法是前闭后开*/
		SF_MinsAdd_LoadProfile( ( V_ucLoadStartTime + 1 ), ( V_LastNumber * V_ucIntTime ), NxtF_LNxt_Fix_Time );				/**区间2算法是前闭后开*/
	}
	else
	{
		V_LastNumber = 0;	/*读取数据长度为0，说明读取对象645的负荷曲线不支持,读取条数直接清零*/
	}

	if(V_LastNumber != 0)
	{
		memcpy(V_TimeZone + 1, V_ucLoadStartTime + 1, 5);
		SF_MinsAdd_LoadProfile(V_ucLoadEndTime + 1, 1, V_TimeZone + 7);					/*区间2算法是前闭后开*/

		/******************用698方法2的方法获取区间内的分钟冻结数据*************/
		V_usDataLen = C_645FreezeMAXRelatedOAD * C_698To645EnergyBlockLength + 5;
		V_ucRetrun = InF_ReadFreezeData(p_datacode, V_TimeZone, V_DataTemp, &V_usReadRecordNum, &V_usDataLen, V_ucIntTime, V_SaveFreezeTimeBuf, C_645Mode);

		/*************************判断数据是否存在0xBB*************************/
		if( ( ( NxtF_DataCode & 0x0000FF00 ) == 0x00000100 )
		 || ( ( NxtF_DataCode & 0x0000FF00 ) == 0x00000500 ) )
		{
			V_ucOADDatalen = 0x02;
			V_ucFillData = 0xFF;
		}
		else if( ( ( NxtF_DataCode & 0x0000FF00 ) == 0x00000200 )
			   || ( ( NxtF_DataCode & 0x0000FF00 ) == 0x00000300 )
			   || ( ( NxtF_DataCode & 0x0000FF00 ) == 0x00000400 )
			   || ( ( NxtF_DataCode & 0x0000FF00 ) == 0x00000800 ) )
		{
			V_ucOADDatalen = 0x03;
			V_ucFillData = 0xFF;
		}
		else if( ( (NxtF_DataCode & 0x0000FF00 ) == 0x00000600 )
			   || ( ( NxtF_DataCode & 0x0000FF00 ) == 0x00000700 ) )
		{
			V_ucOADDatalen = 0x04;
			V_ucFillData = 0x00;
		}
		else
		{
			V_ucOADDatalen = 0x00;
			V_ucFillData = 0x00;
		}

		for(V_usNum = 0; V_usNum < 6; V_usNum ++)
		{
			if(p_datacode[V_ucOADDataNum] != 0xFFFFFFFF)
			{
				V_ucOADDataNum ++;
			}
			else
			{
				break;
			}
		}

		/********************获取冻结关联列表****************************/
		V_usOADTabBufferLen = CLLoss_Vol_OADTabLen;
		InF_Read_Data(CMin_Free_OADTabLen_T, &V_ucOADTabNum, &V_usOADTabBufferLen, &V_usDataEncode);

		V_usOADTabBufferLen = C_FreezeMAXRelatedOAD * 6;
		InF_ReadOADTab_Data(CMin_Free_OADTab, V_ucOADTabBuffer, &V_usOADTabBufferLen);

		for(V_ucTabNum = 0; V_ucTabNum < V_ucOADTabNum; V_ucTabNum++)
		{
			V_usOADNO = V_ucOADTabBuffer[V_ucTabNum * 6 + 1];
			V_usOADNO &= 0x1F;
			V_usOADNO <<= 8;
			V_usOADNO |= V_ucOADTabBuffer[V_ucTabNum * 6];

			V_ulNature = V_ucOADTabBuffer[V_ucTabNum * 6 + 1];
			V_ulNature &= 0xE0;
			V_ulNature <<=8;

			V_ulReadOADBuf_All[V_ucOADOffset] = Str_FrozenConvert_Table[V_usOADNO].V_ulOAD;
			V_ulReadOADBuf_All[V_ucOADOffset] |= V_ulNature;
			V_ucOADOffset++;
		}
		/*********************************************************************/
		PF_CopyDataBytes(&V_DataTemp[V_ucDataTempOffset], &V_DataTempBuffer[V_ucDataBufferOffset], 0x05);
		V_ucDataBufferOffset += 0x05;
		V_ucDataTempOffset += 0x05;

		for(V_usNum = 0; V_usNum < (V_usReadRecordNum >> 2); V_usNum ++)
		{
			for(V_ucOADNum = 1; V_ucOADNum < V_ucOADDataNum; V_ucOADNum ++)
			{
				/**********************0xBB为无效数据**************************/
				if( ( V_DataTemp[V_ucDataTempOffset] == C_NotSupportAOD_DataBB )
				 && ( SF_Get_Active_OAD(p_datacode[V_ucOADNum] | V_ucPlanNum, &V_ulReadOADBuf_All[0], C_structure, C_End_EventState) == C_AAorBBIsDisactive) )
				{
					memset(&V_DataTempBuffer[V_ucDataBufferOffset], V_ucFillData, V_ucOADDatalen);
					V_ucDataBufferOffset += V_ucOADDatalen;
					V_ucDataTempOffset ++;
				}
				else		/******************0xBB为有效数据******************/
				{
					PF_CopyDataBytes(&V_DataTemp[V_ucDataTempOffset],&V_DataTempBuffer[V_ucDataBufferOffset],V_ucOADDatalen);
					V_ucDataBufferOffset += V_ucOADDatalen;
					V_ucDataTempOffset += V_ucOADDatalen;
				}
			}
		}
		PF_CopyDataBytes(V_DataTempBuffer,V_DataTemp,V_ucDataBufferOffset);
		/**********************************************************************/
		V_usReadRecordNumOriginal = V_usReadRecordNum >> 2;												/*方法2读出来的记录条数*/
		SF_TimeSequencing(V_usReadRecordNumOriginal, V_SaveFreezeTimeBuf + 1, V_SequencingFreezeTime);	/*区间2获取的时间按照从小到大顺序排列*/
		memcpy(pV_645Frame->Data + 4, V_ucLoadStartTime + 1, 5);

		/*************************补区间2起始时间前面的数据*********************/
		if(V_usReadRecordNumOriginal == 0)
		{
			V_usReadRecordNumOriginal = V_LastNumber;
			if(V_ucRetrun == C_NoData)
			{
				V_ucRetrun = 0;			/*如果区间2方法查出来没有数据，把返回改成OK*/
			}
			else
			{
				V_ucTotalNum = 0;		/*如果没有合法的数据，直接回0*/
			}
		}

		V_SuppleDataCycle = 0;
		j = 0;
		for( ; j < V_LastNumber; j ++)
		{
			for( ; V_SuppleDataCycle < V_usReadRecordNumOriginal; V_SuppleDataCycle ++ )		/*一共需要读出来的块数*/
			{
				SF_MinsAdd_LoadProfile(V_ucLoadStartTime + 1, j * V_ucIntTime, V_EndTime + 1);
				if( PF_Campare_Data( V_EndTime, V_SequencingFreezeTime + V_SuppleDataCycle * 6, C_LoadTimeLen + 1 ) != C_Equal )
				{
					if(j == 0)
					{
						memset(V_LAheadTimeDataBuf, 0, V_ReadOADLen);
						V_usDataLen = C_645FreezeMAXRelatedOAD * C_698To645EnergyBlockLength + 5;
						V_ucRetrun = InF_ReadFreezeData(p_datacode, V_TimeZone, V_LAheadTimeDataBuf, &V_usReadRecordNum, &V_usDataLen, 15, V_LAheadTime, C_698AheadTimeMode);
						if(V_ucRetrun == C_698AheadTimeMode)
						{
							V_ucRetrun = 0;
							if(V_SuppleDataType == 0xFF)
							{
								memset( ( (pV_645Frame->Data) + 4 + 5 ), 0xFF, V_ReadOADLen);
							}
							else
							{
								V_ucDataTempOffset = 0;
								V_ucDataBufferOffset = 0;

								if((V_usReadRecordNum >> 2) == 0x00)
								{
									V_usNumData = 0x01;
								}
								else
								{
									V_usNumData = (V_usReadRecordNum >> 2);
								}

								for(V_usNum = 0; V_usNum < V_usNumData; V_usNum ++)
								{
									for(V_ucOADNum = 1; V_ucOADNum < V_ucOADDataNum; V_ucOADNum ++)
									{
										/**********************0xBB为无效数据**************************/
										if( ( V_LAheadTimeDataBuf[V_ucDataTempOffset] == C_NotSupportAOD_DataBB )
										 && ( SF_Get_Active_OAD(p_datacode[V_ucOADNum] | V_ucPlanNum, &V_ulReadOADBuf_All[0], C_structure, C_End_EventState ) == C_AAorBBIsDisactive ) )
										{
											memset(&V_DataTempBuffer[V_ucDataBufferOffset], V_ucFillData, V_ucOADDatalen);
											V_ucDataBufferOffset += V_ucOADDatalen;
											V_ucDataTempOffset ++;
										}
										else
										{

											PF_CopyDataBytes(&V_LAheadTimeDataBuf[V_ucDataTempOffset], &V_DataTempBuffer[V_ucDataBufferOffset], V_ucOADDatalen);
											V_ucDataBufferOffset += V_ucOADDatalen;
											V_ucDataTempOffset += V_ucOADDatalen;
										}
									}
								}

								PF_CopyDataBytes(V_DataTempBuffer, V_LAheadTimeDataBuf, V_ucDataBufferOffset);

								V_usEnergyLen = V_ReadOADLen;
								SF_EnergyT0_645(V_LAheadTimeDataBuf, (pV_645Frame->Data) + 4 + 5, &V_usEnergyLen, 4, (uchar8)( p_datacode[1] >> 16 ) );
							}
						}
					}
					else
					{
						if(V_SuppleDataType == 0xFF)
						{
							memset( ( (pV_645Frame->Data) + 4 + 5 + (j * V_ReadOADLen) ), 0xFF, V_ReadOADLen );
						}
						else
						{
							memcpy( ( (pV_645Frame->Data) + 4 + 5 + (j * V_ReadOADLen) ), ( V_DataSuppleTemp + 5 + ( (j - 1) * V_ReadOADLen ) ), V_ReadOADLen );
						}
					}
				}
				else
				{
                	if( ( p_datacode[1] & 0xFF000000 ) == 0x00000000 )
                	{
						V_usEnergyLen = V_ReadOADLen;
                    	SF_EnergyT0_645(V_DataTemp + 5 + V_SuppleDataCycle * V_ReadOADLen, V_DataSuppleTemp + 5 + j * V_ReadOADLen, &V_usEnergyLen, 4, (uchar8)( p_datacode[1] >> 16 ) );
					}
                    else
                    {
						memcpy(V_DataSuppleTemp + 5 + j * V_ReadOADLen, V_DataTemp + 5 + V_SuppleDataCycle * V_ReadOADLen, V_ReadOADLen);
                    }
					V_SuppleDataCycle++;
				}

				break;
			}

			if( ( V_SuppleDataCycle >= V_usReadRecordNumOriginal ) && ( ( j != V_LastNumber ) ) )
			{
				j++;
				for( ; j < V_LastNumber; j++ )
				{
					if(V_SuppleDataType == 0xFF)
					{
						memset( ( ( pV_645Frame->Data ) + 4 + 5 + ( j * V_ReadOADLen ) ), 0xFF, V_ReadOADLen );
					}
					else
					{
						memcpy( ( (pV_645Frame->Data) + 4 + 5 + (j * V_ReadOADLen) ), ( V_DataSuppleTemp + 5 + ( (j - 1) * V_ReadOADLen ) ), V_ReadOADLen );
					}
				}
			}
		}
	}

	V_usDataLen = V_LastNumber * V_ReadOADLen + V_TotalFrameLen;
	/*组织应答帧*/
	if(V_ucRetrun != C_OK)
	{/*错了。*/
		V_usDataLen = 0;
		Comm_11_03Response_Normal(pV_645Frame, V_DataTemp, V_usDataLen);
		V_ucRetrun = C_NoNxtFrame;
	}
	else
	{
		NxtF_LNxt_ReadedBlockNum += V_LastNumber;
		if(NxtF_FrameNo == 0)/*首帧*/
		{
			Comm_11_03Response_Normal(pV_645Frame, (pV_645Frame->Data) + 4, V_usDataLen);
		}
		else
		{
			Comm_11_03Response_Normal(pV_645Frame, (pV_645Frame->Data) + 4 + 5, V_usDataLen);
		}
	}

	if(NxtF_LNxt_BlockNum == 0)
    {
        V_ucRetrun = C_NoNxtFrame;
    }
	else
    {
        V_ucRetrun = C_HaveNxtFrame;
    }

	return V_ucRetrun;
}

/*******************************************************************************
函数原型 ulong32 * P_Data_Id_OAD,uchar8 * P_FixTime,uchar8 * P_Data,ushort16 * V_BlockNum,ushort16 * V_Length,ushort16 V_IntervalTime,uchar8 *pV_FreezeTimeBuf,uchar8 V_Mode
函数功能 获取645负荷记录数据
输入参数
输出参数
返回参数 有无后续帧(C_HaveNxtFrame/C_NoNxtFrame)
全局变量
函数备注	 645负荷记录数据由698分钟冻结转换而来
*******************************************************************************/
uchar8 SF_Get645LoadRecordData(ulong32 V_ulDataCode645, uchar8 *P_ucFixTime, uchar8 *V_ucBlockNum, uchar8 *P_ucData, uchar8 *V_ucDataLen ,uchar8 V_ucFrameNo)
{
	uchar8 V_ucRetrunData = C_OK;
	ushort16 V_ucTimeLength, V_usDataEncode;
	ulong32 V_ulDataCode645Temp = 0;
	uchar8 V_ucDataCodeType = 0;

    ulong32 V_ulDataCode698Buffer[Str_LoadRecord645To698_Len + 7] =
	{	0x50020000,0x20210200,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,
		0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,
		0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,
		0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,
		0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,
		0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,
	};
	uchar8 V_ucDataCode698LenBuffer[Str_LoadRecord645To698_Len] = {0};
	uchar8 V_ucDataCode698OffsetBuffer[Str_LoadRecord645To698_Len] = {0};

	uchar8 V_ucPlanNum = 0, V_ucNum = 0;
	ushort16 V_usFreezeCycle = 0, V_usDataLength = 0;
	uchar8 V_ucSaveFreezeTimeBuf[C_645FreezeTimeBufLen] = {0};

	uchar8 V_ucDataCodeNum = 0,V_ucDataCodeLen = 0,V_ucDataAANum = 0;
	uchar8 V_usI_Block = 0, V_ucI = 0;

	uchar8 V_ucDataBuffer[1024] = {0};
	uchar8 V_ucDataTemp[1024] = {0};
	uchar8 V_ucDataTempOffset = 0;
	uchar8 V_ucDataCodeOffset = 0;
	ushort16 V_usBlockNumber,V_usDataBufferOffset = 0;

	ulong32 V_ulAddMins;
	uchar8 V_ucActualDataLen = 0;
	uchar8 V_usSendBlock = 0;
	uchar8 V_ucDataFormat = 0;
	ushort16 V_usEnergyLen = 0;

	ushort16 V_usOADTabBufferLen = 0;
	uchar8 V_ucOADTabBuffer[C_MAXRelatedOAD * 6] = {0};
	ushort16 V_usOADNO = 0;
	ulong32 V_ulNature = 0;
	ulong32 V_ulReadOADBuf_All[C_MAXRelatedOAD] = {0};
	uchar8 V_ucOADOffset = 0, V_ucOADTabNum = 0, V_ucTabNum = 0;

	uchar8 V_ucDatacodeBufLen = 0;

	/*****************645负荷记录格式调整为698分钟冻结格式**********************/
	SF_LoadRecord645DITo698OAD(V_ulDataCode645, &V_ulDataCode698Buffer[2], V_ucDataCode698LenBuffer, V_ucDataCode698OffsetBuffer);

	/*****************获取对应的分钟冻结周期,不同方案会有不同********************/
	V_ucDatacodeBufLen = Str_LoadRecord645To698_Len + 1;	/*最多六类抄读时OAD共Str_LoadRecord645To698_Len个，最后一个为0xFFFFFFFF*/
	V_ucRetrunData = SF_GetMinFreezeCycle(&V_ulDataCode698Buffer[1], V_ucDatacodeBufLen, &V_ucPlanNum, &V_usFreezeCycle);
	if(V_ucRetrunData != C_OK)	/*方案号不同直接返回*/
	{
		return V_ucRetrunData;
	}

	if(V_usFreezeCycle > 0xFF)
	{
		V_usFreezeCycle = 0xFF;
	}

	for(V_ucNum = 0; V_ucNum < Str_LoadRecord645To698_Len; V_ucNum ++)
	{
		if(V_ulDataCode698Buffer[V_ucNum + 2] != 0xFFFFFFFF)
		{
			PF_Ulong32ToBuffer4(V_ucDataBuffer, &V_ulDataCode698Buffer[V_ucNum + 2], 4);
			V_ucDataBuffer[1] |= V_ucPlanNum;
			PF_Buffer4ToUlong32(V_ucDataBuffer, &V_ulDataCode698Buffer[V_ucNum + 2], 4);
		}
		else
		{
			break;
		}
	}

	if( ( (V_ulDataCode645 & 0x000000FF) == 0x00000000 )
		&& (V_ucFrameNo == 0x00) )	/*最早记录块首帧读取赋值起始时间*/
	{
		/*****************获取负荷记录最早记录时间************************************/
		V_usDataLength = 1024;
		V_ucRetrunData = InF_ReadFreezeData(V_ulDataCode698Buffer, P_ucFixTime, V_ucDataBuffer, &V_usBlockNumber, &V_usDataLength, V_usFreezeCycle, V_ucSaveFreezeTimeBuf, C_698EarLoadMode);
		if(V_ucRetrunData != C_698EarLoadMode)
		{
			return V_ucRetrunData;
		}
	}

	if(( (V_ulDataCode645 & 0x000000FF) == 0x00000000 )			/*最早记录块读取*/
		|| ( (V_ulDataCode645 & 0x000000FF) == 0x00000001 ) )		/*给定时间记录块*/
	{
		/*****************获取对应的分钟冻结数据************************************/
		V_ucTimeLength = CLDate_Time;/*此处读出时间为hex格式的7字节时间，本函数后期会重新调整，使用的时候再核对，lzy 20211023*/
		V_ucRetrunData = InF_Read_Data(CDate_Time, &P_ucFixTime[6], &V_ucTimeLength, &V_usDataEncode);		/*读取当前时间*/
		P_ucFixTime[6] = 0x00;	/*秒清零*/
		if(V_ucRetrunData != C_OK)
		{
			V_ulAddMins = V_usFreezeCycle * (*V_ucBlockNum);
			SF_MinsAdd_LoadProfile(&P_ucFixTime[1], V_ulAddMins, &P_ucFixTime[7]);
		}
		V_usDataLength = 1024;
		V_ucRetrunData = InF_ReadFreezeData(V_ulDataCode698Buffer, P_ucFixTime, V_ucDataBuffer, &V_usBlockNumber, &V_usDataLength, V_usFreezeCycle, V_ucSaveFreezeTimeBuf, C_698Mode);
		if(V_ucRetrunData != C_OK)
		{
			return V_ucRetrunData;
		}
	}
	else if( (V_ulDataCode645 & 0x000000FF) == 0x00000002 )		/*最近一个记录块*/
	{
		/*****************获取对应的分钟冻结数据************************************/
		V_ulDataCode698Buffer[0] = V_ulDataCode698Buffer[0] | 0x00000001;
		V_usDataLength = 1024;
		V_ucRetrunData = InF_ReadFreezeData(V_ulDataCode698Buffer, P_ucFixTime, V_ucDataBuffer, &V_usBlockNumber, &V_usDataLength, V_usFreezeCycle, V_ucSaveFreezeTimeBuf, C_698EarLoadMode);
		if(V_ucRetrunData != C_OK)
		{
			return V_ucRetrunData;
		}
	}
	else
	{
		return C_Error;
	}

	/********************获取冻结关联列表****************************/
	V_usOADTabBufferLen = CLLoss_Vol_OADTabLen;
	InF_Read_Data(CMin_Free_OADTabLen_T, &V_ucOADTabNum, &V_usOADTabBufferLen, &V_usDataEncode);

	V_usOADTabBufferLen = C_FreezeMAXRelatedOAD * 6;
	InF_ReadOADTab_Data(CMin_Free_OADTab, V_ucOADTabBuffer, &V_usOADTabBufferLen);

	for(V_ucTabNum = 0; V_ucTabNum < V_ucOADTabNum; V_ucTabNum++)
	{
		V_usOADNO = V_ucOADTabBuffer[V_ucTabNum * 6 + 1];
		V_usOADNO &= 0x1F;
		V_usOADNO <<= 8;
		V_usOADNO |= V_ucOADTabBuffer[V_ucTabNum * 6];

		V_ulNature = V_ucOADTabBuffer[V_ucTabNum * 6 + 1];
		V_ulNature &= 0xE0;
		V_ulNature <<=8;

		V_ulReadOADBuf_All[V_ucOADOffset] = Str_FrozenConvert_Table[V_usOADNO].V_ulOAD;
		V_ulReadOADBuf_All[V_ucOADOffset] |= V_ulNature;
		V_ucOADOffset++;
	}

	if( (V_ulDataCode645 & 0x00FF0000) == 0x00000000 )
	{
		V_ulDataCode645 |= 0x00010000;
		V_ucDataCodeType = 6;
	}
	else
	{
		V_ucDataCodeType = 1;
	}

	if((V_usBlockNumber >> 2) >= *V_ucBlockNum)
	{
		V_usSendBlock = *V_ucBlockNum;
	}
	else
	{
		V_usSendBlock = (V_usBlockNumber >> 2);
	}

	V_usDataBufferOffset = 0;

	for(V_usI_Block = 0; V_usI_Block < V_usSendBlock; V_usI_Block ++ )
	{
		V_ucDataCodeOffset = 0;

		memset(&V_ucDataTemp[0],0xA0,0x02);		/*负荷记录起始码A0H，A0H*/
		V_ucDataTemp[2] = 0x00;					/*负荷记录字节数清零，本次数据块编码结束后根据实际长度赋值*/
		V_ucDataTempOffset = 0x03;

		/*负荷记录存储时间为年月日时分5字节，数据层获取的时间为年月日时分秒6字节*/
		PF_CopyDataBytes(&V_ucDataBuffer[(V_usDataBufferOffset + 1)], &V_ucDataTemp[V_ucDataTempOffset], 0x05 );
		V_usDataBufferOffset += 0x06;
		V_ucDataTempOffset = 0x08;

		for(V_ucI = 0; V_ucI < V_ucDataCodeType; V_ucI++)
		{
			V_ulDataCode645Temp = V_ulDataCode645 + (0x00010000 * V_ucI);

			if( (V_ulDataCode645Temp & 0x00FF0000) == 0x00010000 )
			{
				V_ucDataCodeNum = 7;
				V_ucDataCodeLen = 17;
				V_ucDataAANum = 0;
				V_ucDataFormat = C_Format_BCD;
			}
			else if( (V_ulDataCode645Temp & 0x00FF0000) == 0x00020000 )
			{
				V_ucDataCodeNum = 8;
				V_ucDataCodeLen = 24;
				V_ucDataAANum = 1;
				V_ucDataFormat = C_Format_BCD;
			}
			else if( (V_ulDataCode645Temp & 0x00FF0000) == 0x00030000 )
			{
				V_ucDataCodeNum = 4;
				V_ucDataCodeLen = 8;
				V_ucDataAANum = 2;
				V_ucDataFormat = C_Format_BCD;
			}
			else if( (V_ulDataCode645Temp & 0x00FF0000) == 0x00040000 )
			{
				V_ucDataCodeNum = 4;
				V_ucDataCodeLen = 16;
				V_ucDataAANum = 3;
				V_ucDataFormat = C_Format_HEX;
			}
			else if( (V_ulDataCode645Temp & 0x00FF0000) == 0x00050000 )
			{
				V_ucDataCodeNum = 4;
				V_ucDataCodeLen = 16;
				V_ucDataAANum = 4;
				V_ucDataFormat = C_Format_HEX;
			}
			else if( (V_ulDataCode645Temp & 0x00FF0000) == 0x00060000 )
			{
				V_ucDataCodeNum = 2;
				V_ucDataCodeLen = 6;
				V_ucDataAANum = 5;
				V_ucDataFormat = C_Format_BCD;
			}
			else
			{
				V_ucDataCodeNum = 0;
				V_ucDataCodeLen = 0;
				V_ucDataAANum = 0;
				V_ucDataFormat = C_Format_BCD;
			}

			/********************判断0xBB是否为有效数据************************/
			if(V_ucDataFormat == C_Format_BCD)
			{
				for(V_ucNum = 0; V_ucNum < V_ucDataCodeNum; V_ucNum ++)
				{
					if(V_ucDataBuffer[V_usDataBufferOffset] == 0xBB)
					{
						V_ucDataCodeLen = 0;
						V_usDataBufferOffset ++;
						V_ucDataCodeOffset ++;
					}
					else
					{
						V_usDataBufferOffset += V_ucDataCode698LenBuffer[V_ucDataCodeOffset];
						V_ucDataCodeOffset ++;
					}
				}
			}
			else
			{
				for(V_ucNum = 0; V_ucNum < V_ucDataCodeNum; V_ucNum ++)
				{
					/*0xBB为无效数据*/
					if( (V_ucDataBuffer[V_usDataBufferOffset] == C_NotSupportAOD_DataBB)
						&& (SF_Get_Active_OAD(V_ulDataCode698Buffer[2 + V_ucDataCodeOffset] | V_ucPlanNum, &V_ulReadOADBuf_All[0], C_structure, C_End_EventState) == C_AAorBBIsDisactive) )	/*无效*/
					{
						V_ucDataCodeLen = 0;
						V_usDataBufferOffset ++;
						V_ucDataCodeOffset ++;
					}
					else	/*0xBB为有效数据*/
					{
						V_usEnergyLen = CLPosActEnergyT_Load;
						SF_EnergyT0_645(&V_ucDataBuffer[V_usDataBufferOffset], &V_ucDataBuffer[V_usDataBufferOffset], &V_usEnergyLen, 4, (uchar8)(V_ulDataCode698Buffer[2 + V_ucDataCodeOffset] >> 16) );
						V_usDataBufferOffset += CLPosActEnergyT_Load;
						V_ucDataCodeOffset ++;
					}
				}
			}

			/*负荷记录数据编码*/
			if(V_ucDataCodeType == 6)
			{
				PF_CopyDataBytes( &V_ucDataBuffer[(V_usDataBufferOffset - V_ucDataCodeLen)], &V_ucDataTemp[V_ucDataTempOffset], V_ucDataCodeLen );
				V_ucDataTempOffset = V_ucDataTempOffset + V_ucDataCodeLen;
				V_ucDataTemp[V_ucDataTempOffset] = 0xAA;
				V_ucDataTempOffset ++;
			}
			else
			{
				memset(&V_ucDataTemp[V_ucDataTempOffset], 0xAA, V_ucDataAANum);
				V_ucDataTempOffset = V_ucDataTempOffset + V_ucDataAANum;
				PF_CopyDataBytes( &V_ucDataBuffer[(V_usDataBufferOffset - V_ucDataCodeLen)], &V_ucDataTemp[V_ucDataTempOffset], V_ucDataCodeLen);
				V_ucDataTempOffset = V_ucDataTempOffset + V_ucDataCodeLen;
				memset(&V_ucDataTemp[V_ucDataTempOffset], 0xAA,(C_DataAANum - V_ucDataAANum));
				V_ucDataTempOffset = V_ucDataTempOffset + (C_DataAANum - V_ucDataAANum);
			}
		}

		if(V_ucDataTempOffset <= 0x0E)
		{
			V_ucDataTempOffset = 0;
		}
		else
		{
			/*负荷记录字节数*/
			V_ucDataTemp[2] = V_ucDataTempOffset - 3;

			/*负荷记录累加校验码*/
			V_ucDataTemp[V_ucDataTempOffset] = 0x00;
			for(V_ucI = 0; V_ucI < V_ucDataTempOffset; V_ucI++)
			{
				V_ucDataTemp[V_ucDataTempOffset] += V_ucDataTemp[V_ucI];
			}
			V_ucDataTempOffset ++;

			/*负荷记录结束码*/
			V_ucDataTemp[V_ucDataTempOffset] = 0xE5;
			V_ucDataTempOffset ++;
		}

		PF_CopyDataBytes(&V_ucDataTemp[0], &P_ucData[V_ucActualDataLen], V_ucDataTempOffset);
		V_ucActualDataLen += V_ucDataTempOffset;

		if( (*V_ucDataLen - V_ucActualDataLen) < V_ucDataTempOffset)
		{
			V_usI_Block ++;
			break;
		}
	}

	if(V_ucActualDataLen != 0)
	{
		if( V_usI_Block == V_usSendBlock )
		{
			if( (V_usBlockNumber & 0x0003) != 0x0000 )	/*数据层有后续帧，但本次编码已完成*/
			{
				*V_ucBlockNum = *V_ucBlockNum - V_usI_Block;
				/*数据层有后续帧时，数据层会返回下一帧起始时间到P_ucFixTime*/
			}
			else	/*数据层无后续帧,且编码已完成*/
			{
				*V_ucBlockNum = 0;
			}
		}
		else	/*本次编码未完成*/
		{
			*V_ucBlockNum = *V_ucBlockNum - V_usI_Block;
			/*后续帧负荷记录起始时间，数据层获取的时间为年月日时分秒6字节*/
			PF_CopyDataBytes(&V_ucDataBuffer[(V_usDataBufferOffset + 1)], &P_ucFixTime[1], 0x05 );
		}
	}
	else
	{
		*V_ucBlockNum = 0;
	}

	*V_ucDataLen = V_ucActualDataLen;

	return V_ucRetrunData;
}
/*******************************************************************************
函数原型 NormalReadingLoadCurve
函数功能 正常读负荷记录
输入参数 *pV_645Frame:收到的命令帧
		 *pStr_Comm_NxtFrame:后续帧相关结构体
输出参数 pStr_Comm_NxtFrame.Nxt:如果有后续帧，则后续帧起始时间等相关变量
返回参数 C_HaveNxtFrame/C_NoNxtFrame
全局变量
函数备注
*******************************************************************************/
uchar8 NormalReadingLoadCurve(Str_Comm_645 *pV_645Frame, Str_Comm_NxtFrame *pStr_Comm_NxtFrame)
{
	uchar8 V_ucRetrunData;

	ulong32 V_ulDataCode645;
	uchar8 V_ucFixTime[14] = {0};
	uchar8 V_ucDataBuffer[C_Comm_Data_MaxLen - CLen_DI - 1] = {0};
	uchar8 V_ucDataLen;

	V_ulDataCode645 = NxtF_DataCode;
	PF_CopyDataBytes( NxtF_LNxt_Fix_Time, &V_ucFixTime[1], LClockLen );
	V_ucDataLen = C_Comm_Data_MaxLen - CLen_DI - 1;		/*扣去1的目的，最后可能要帧序号*/

	V_ucRetrunData = SF_Get645LoadRecordData(V_ulDataCode645, V_ucFixTime, &NxtF_LNxt_BlockNum, V_ucDataBuffer, &V_ucDataLen, NxtF_FrameNo);

    if(V_ucRetrunData != C_OK)
    {
        V_ucDataLen = 0;
        Comm_11_03Response_Normal(pV_645Frame, pV_645Frame->Data, V_ucDataLen);
        return C_NoNxtFrame;
    }
    else
    {
		PF_CopyDataBytes( V_ucDataBuffer, (pV_645Frame->Data) + 4, V_ucDataLen);
		Comm_11_03Response_Normal(pV_645Frame, (pV_645Frame->Data) + 4,V_ucDataLen);

		if(NxtF_LNxt_BlockNum == 0)
		{
			return C_NoNxtFrame;
		}
		else
		{
			PF_CopyDataBytes( &V_ucFixTime[1], NxtF_LNxt_Fix_Time, LClockLen);
			return C_HaveNxtFrame;
		}
	}
}

/***************************************************************************
函数原型 	SeqReadingLoadCurve_11
函数功能	11命令连续读取负荷曲线
输入参数	*pV_645Frame			:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	通信通道缓冲区
函数备注	进入本命令，标识码肯定正确
***************************************************************************/
void		SeqReadingLoadCurve_11(Str_Comm_645 *pV_645Frame)
{
	Str_Comm_NxtFrame	Comm_NxtFrame;
	Str_Comm_NxtFrame	*pStr_Comm_NxtFrame;
	uchar8	V_ReturnData;
	uchar8	i;

	pStr_Comm_NxtFrame = &Comm_NxtFrame;
	if(Get_SV_CommNxtFrame(pV_645Frame->ChannelNo, pStr_Comm_NxtFrame) != C_OK)
	{
		return;			/*出错，什么都不处理。*/
	}
/*11命令置后续帧 变量*/
	NxtF_DataCode = pV_645Frame->DI;
	NxtF_FrameNo = 0x00;
	for( i = 0; i < LClockLen; i++ )
	{
		NxtF_LNxt_Fix_Time[i] = pV_645Frame->Data[C_F3_O_GivenClock + i];
	}
	NxtF_LNxt_BlockNum = (pV_645Frame->Data[C_F3_O_BlockNum] & 0x0F) + (pV_645Frame->Data[C_F3_O_BlockNum] >> 4) * 10;

/*调用读命令，根据返回值置位C*/
	V_ReturnData = SeqReadingLoadCurve(pV_645Frame,pStr_Comm_NxtFrame);

	if(V_ReturnData  == C_HaveNxtFrame)
	{
		Comm_IfHaveNxtFrame_Set_C(pV_645Frame);
		NxtF_FrameFinished = C_Error;										/*表示有后续帧*/
		NxtF_HaveReport = C_Error;											/*表示未主动上报过*/
		NxtF_FrameNo = 0x01;
		Set_SV_CommNxtFrame(pV_645Frame->ChannelNo, pStr_Comm_NxtFrame);	/*11命令是不用加帧序号的。*/
	}
}
/*******************************************************************************
函数原型 Comm_11_Read
函数功能 完成11命令的解析及应答
输入参数 *pV_645Frame:收到的命令帧
输出参数 无
返回参数 无
全局变量 和通道相关的全局变量
函数备注 本函数进行读帧格式和下级读函数的判断。
*******************************************************************************/
void Comm_11_Read(Str_Comm_645 *pV_645Frame)
{
	ushort16 V_ucDataLen, V_usDataEncode, V_RTCLen;

/*进入11命令首先初始化本通道后续帧变量*/
	Init_SV_CommNxtFrame(pV_645Frame->ChannelNo);

/*判断是否读取软I_J剩余时间*/
	if(pV_645Frame->DI == 0x02FFFE01)
	{
		pV_645Frame->Data[C_11_SData] = SV_Comm_Parse.SI_JTimer.BaseTimer;
		PF_Ulong32ToBuffer4(&pV_645Frame->Data[C_11_SData + 1], &SV_Comm_Parse.SI_JTimer.Timer, 2);
		Comm_11_03Response_Normal(pV_645Frame, &pV_645Frame->Data[C_11_SData], 3);
		return;
	}

/*判断是否读取通信地址*/
	if(pV_645Frame->DI == 0x04000401)
	{
		V_ucDataLen = CLComm_Address;
		InF_Read_Data(CComm_Address, &(pV_645Frame->Data[C_11_SData]), &V_ucDataLen, &V_usDataEncode);
		Comm_11_03Response_Normal(pV_645Frame, &pV_645Frame->Data[C_11_SData], CLComm_Address);
		return;
	}

/*需要保留这条命令，否则复旦的校表软件无法下发RTC日计时校准命令*/
	if(pV_645Frame->DI == 0x02800007)
	{
		V_RTCLen = CLMeter_Temp;
		InF_Read_Data(CMeter_Temp, &(pV_645Frame->Data[C_11_SData]), &V_RTCLen, &V_usDataEncode);
		Comm_11_03Response_Normal(pV_645Frame, &pV_645Frame->Data[C_11_SData], CLMeter_Temp);
		return;
	}

/*判断是否本表型支持*/
	if(IsMeterTypeSupport(pV_645Frame) != C_OK)
	{
		Comm_Response_Set_ReadErr(C_No_Request_data_645, pV_645Frame);
		return;		/*这里不判断主动上报了。*/
	}

/*进行读帧格式的判断*/
	if(pV_645Frame->DataLen == 0x04)
	{/*帧格式1*/
		switch(pV_645Frame->Data[C_O_DI3])
		{
			case		0x00:				/*读电能类*/
				Comm_ReadEnergyReg(pV_645Frame);
				break;
			case		0x01:				/*读需量类*/
				Comm_ReadDemandReg(pV_645Frame);
				break;
			case		0x04:				/*参变量类*/
			case		0x02:
				Comm_Read_P_V_Reg(pV_645Frame);
				break;
			case		0x05:				/*读冻结类*/
				Comm_ReadFreezeReg_11(pV_645Frame);
				break;
			case		0x10:				/*失压*/
			case		0x11:				/*欠压*/
			case		0x12:				/*过压*/
			case		0x13:				/*断相*/
			case		0x14:				/*电压逆相序*/
			case		0x15:				/*电流逆相序*/
			case		0x16:				/*电压不平衡*/
			case		0x17:				/*电流不平衡*/
			case		0x20:				/*电流严重不平衡*/
			case		0x18:				/*失流*/
			case		0x19:				/*过流*/
			case		0x1A:				/*断流*/
			case		0x1B:				/*功率反向*/
			case		0x1C:				/*过载*/
			case		0x21:				/*潮流反向*/
			case		0x1F:				/*功率因数超下限*/
			case		0x03:				/*其他编程、开盖等事件类*/
			case		0x1D:				/*跳闸记录*/
			case		0x1E:				/*合闸记录*/
				Comm_Read_EventReg(pV_645Frame);
				break;
			default:
				Comm_Response_Set_ReadErr(C_OtherErr_645, pV_645Frame);
				break;
		}
	}
	else if(pV_645Frame->DataLen == 0x05)
	{/*帧格式2*/
		if(Is_NormalReadingLoadCurve(pV_645Frame->DI) == C_OK)
		{/*正常读负荷曲线*/
			NormalReadingLoadCurve_11(pV_645Frame);
		}
		else
		{
			Comm_Response_Set_ReadErr(C_No_Request_data_645, pV_645Frame);
		}
	}
	else if(pV_645Frame->DataLen == 0x0A)
	{/*帧格式3*/
		if(Is_NormalReadingLoadCurve(pV_645Frame->DI) == C_OK)
		{/*正常读负荷曲线*/
			NormalReadingLoadCurve_11(pV_645Frame);
		}
		else if(Is_SeqReadingLoadCurve(pV_645Frame->DI) == C_OK)
		{
			SeqReadingLoadCurve_11(pV_645Frame);
		}
		else
		{
			Comm_Response_Set_ReadErr(C_No_Request_data_645, pV_645Frame);
		}
	}
	else
	{
		Comm_Response_Set_ReadErr(C_OtherErr_645, pV_645Frame);
	}

/*判断是否需要后续帧报故障信息主动上报?*/
	if( ( Judge_ReportWithNxtFrame() == C_OK ) && ( pV_645Frame->DI != CDrive_Report_State_645 ) )
	{/*有上报且本次命令不是主动上报功能*/
		Comm_IfHaveNxtFrame_Set_C(pV_645Frame);	/*bit5是有后续帧标志*/
	}
}
/***************************************************************************
函数原型 	Comm_LCD_View
函数功能	液晶查看命令解析及应答
输入参数	*pV_645Frame			:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	通信通道缓冲区
函数备注	进入本命令，长度标识码肯定正确
***************************************************************************/
void		Comm_LCD_View(Str_Comm_645 *pV_645Frame)
{
	ulong32	V_ulCodeID;
	uchar8  V_ucDisplayMsg[20];

/*调用显示接口函数，判断是否支持该标识码显示*/
	PF_Buffer4ToUlong32(&pV_645Frame->Data[C_11_SData], &V_ulCodeID, CLen_DI);
/*发消息给显示模块，并正确应答	*/
	Comm_11_03Response_Normal(pV_645Frame, &pV_645Frame->Data[C_11_SData], Pt_DisplayID_Len);
	PF_CopyDataBytes(&pV_645Frame->Data[C_11_SData], &V_ucDisplayMsg[1], Pt_DisplayID_Len);
	V_ucDisplayMsg[0] = Pt_DisplayID;
	V_ucDisplayMsg[6] = 10;
	V_ucDisplayMsg[7] = 0;
	Comm_SendMsg(&V_ucDisplayMsg[0], (Pt_DisplayID_Len + 1), C_Msg_Display);
}

/*******************************************************************************
函数原型 NormalReadingLoadCurve_11
函数功能 11命令正常读负荷记录及应答
输入参数 *pV_645Frame:接收到的数据帧
输出参数 无
返回参数 无
全局变量 通信通道缓冲区
函数备注 进入本命令，标识码肯定正确
*******************************************************************************/
void NormalReadingLoadCurve_11(Str_Comm_645 *pV_645Frame)
{
	Str_Comm_NxtFrame Comm_NxtFrame;
	Str_Comm_NxtFrame *pStr_Comm_NxtFrame;
	uchar8 V_ReturnData;
	uchar8 i;

	pStr_Comm_NxtFrame = &Comm_NxtFrame;
	if(Get_SV_CommNxtFrame(pV_645Frame->ChannelNo, pStr_Comm_NxtFrame) != C_OK)
	{
		return;		/*出错，什么都不处理*/
	}

	/*11命令置后续帧变量*/
	NxtF_DataCode = pV_645Frame->DI;
	NxtF_FrameNo = 0x00;
	if(pV_645Frame->Data[C_O_DI0] == 0x01)
	{
		/*最早数据块、最近数据块第1次读，时间值只能为全0。只有给定时间读才能置时间*/
		for( i = 0; i < LClockLen; i++)
		{
			NxtF_LNxt_Fix_Time[i] = pV_645Frame->Data[C_F3_O_GivenClock + i];
		}
	}
	NxtF_LNxt_BlockNum = ( pV_645Frame->Data[C_F3_O_BlockNum] & 0x0F )
						+ ( ( pV_645Frame->Data[C_F3_O_BlockNum] >> 4 ) * 10 );

	V_ReturnData = NormalReadingLoadCurve(pV_645Frame,pStr_Comm_NxtFrame);

	if( V_ReturnData == C_HaveNxtFrame )
	{
		Comm_IfHaveNxtFrame_Set_C(pV_645Frame);
		NxtF_FrameFinished = C_Error;										/*表示有后续帧*/
		NxtF_HaveReport = C_Error;											/*表示未主动上报过*/
		NxtF_FrameNo = 0x01;
		Set_SV_CommNxtFrame(pV_645Frame->ChannelNo, pStr_Comm_NxtFrame);	/*11命令是不用加帧序号的*/
	}
}

/***************************************************************************
函数原型 	Is_EventReg_DI0FFOK
函数功能	判断是否允许DI0=0xFF读取事件记录数据块
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	C_OK允许读取，C_No_Request_data表示不支持该标识码读取
全局变量 	无
函数备注	这里总失压事件记录需要进行特殊处理，该标识码不支持DI0=0xFF读取事件记录
	支持这类标识码的事件记录有失压、欠压、过压、断相、电压/电流逆相序、电压/电流不平衡
	失流、断流、过流、过载、功率因数超限、有功功率反向、拉合闸记录
	判断的时候只需要判断此类标识码的DI3DI2即可
***************************************************************************/
/*支持DI0=0xFF的事件记录的标识码*/
#define	C_TB_DI0FFEventDI3DI2_Len		38
#define  C_KeepDI3DI2	0xFFFF0000
const	ulong32 TB_DI0FFEventDI3DI2[C_TB_DI0FFEventDI3DI2_Len] =
{
	(CLossA_Vol_Hp_1 & C_KeepDI3DI2),		/*失压*/
	(CLossB_Vol_Hp_1 & C_KeepDI3DI2),
	(CLossC_Vol_Hp_1 & C_KeepDI3DI2),
	(CLowA_Vol_Hp_1 & C_KeepDI3DI2),		/*欠压*/
	(CLowB_Vol_Hp_1 & C_KeepDI3DI2),
	(CLowC_Vol_Hp_1 & C_KeepDI3DI2),
	(COverA_Vol_Hp_1 & C_KeepDI3DI2),		/*过压*/
	(COverB_Vol_Hp_1 & C_KeepDI3DI2),
	(COverC_Vol_Hp_1 & C_KeepDI3DI2),
	(CBreakA_Vol_Hp_1 & C_KeepDI3DI2),		/*断相*/
	(CBreakB_Vol_Hp_1 & C_KeepDI3DI2),
	(CBreakC_Vol_Hp_1 & C_KeepDI3DI2),
	(CRevPS_Vol_Hp_1 & C_KeepDI3DI2),		/*电压逆相序*/
	(CRevPS_Curr_Hp_1 & C_KeepDI3DI2),		/*电流逆相序*/
	(CNoBal_Vol_Hp_1 & C_KeepDI3DI2),		/*电压不平衡*/
	(CNoBal_Curr_Hp_1 & C_KeepDI3DI2),		/*电流不平衡*/
	(CSevNoBal_Curr_Hp_1 & C_KeepDI3DI2),	/*电流严重不平衡*/
	(CLossA_Curr_Hp_1 & C_KeepDI3DI2),		/*失流*/
	(CLossB_Curr_Hp_1 & C_KeepDI3DI2),
	(CLossC_Curr_Hp_1 & C_KeepDI3DI2),
	(COverA_Curr_Hp_1 & C_KeepDI3DI2),		/*过流*/
	(COverB_Curr_Hp_1 & C_KeepDI3DI2),
	(COverC_Curr_Hp_1 & C_KeepDI3DI2),
	(CBreakA_Curr_Hp_1 & C_KeepDI3DI2),		/*断流*/
	(CBreakB_Curr_Hp_1 & C_KeepDI3DI2),
	(CBreakC_Curr_Hp_1 & C_KeepDI3DI2),
	(CPowerA_Rev_Hp_1 & C_KeepDI3DI2),		/*有功功率反向*/
	(CPowerB_Rev_Hp_1 & C_KeepDI3DI2),
	(CPowerC_Rev_Hp_1 & C_KeepDI3DI2),
	(COverA_Lo_Hp_1 & C_KeepDI3DI2),		/*过载*/
	(COverB_Lo_Hp_1 & C_KeepDI3DI2),
	(COverC_Lo_Hp_1 & C_KeepDI3DI2),
	(CRelayOpen_Hp_T_1 & C_KeepDI3DI2),		/*跳闸*/
	(CRelayClose_Hp_T_1 & C_KeepDI3DI2),	/*合闸*/
	(CPFactorT_Over_Hp_1 & C_KeepDI3DI2),	/*功率因数超下限*/
	(CPFactorA_Over_Hp_1 & C_KeepDI3DI2),
	(CPFactorB_Over_Hp_1 & C_KeepDI3DI2),
	(CPFactorC_Over_Hp_1 & C_KeepDI3DI2)
};
uchar8 Is_EventReg_DI0FFOK(Str_Comm_645 *pV_645Frame)
{
	ulong32 V_uLDI;
	uchar8 i;

	V_uLDI = pV_645Frame->DI;
	V_uLDI &= C_KeepDI3DI2;
	for( i = 0; i < C_TB_DI0FFEventDI3DI2_Len; i++ )
	{
		if(V_uLDI == TB_DI0FFEventDI3DI2[i])
		{
			return C_OK;
		}
	}
	return C_No_Request_data;
}
/***************************************************************************
函数原型 	Is_EventReg_DI0FFOK_Part
函数功能	   判断是否允许DI0=0xFF读取事件记录数据块
输入参数	   *pV_645Frame				:接收到的数据帧
输出参数    无
返回参数	   C_OK允许读取，C_No_Request_data表示不支持该标识码读取
全局变量   无
函数备注	  仅支持这类标识码的事件记录有失流、过流
	      判断的时候只需要判断此类标识码的DI3DI2即可
***************************************************************************/
/*支持DI0=0xFF的事件记录的标识码*/
#define	C_TB_DI0FFEventDI3DI2_Part_Len		6
const	ulong32 TB_DI0FFEventDI3DI2_Part[C_TB_DI0FFEventDI3DI2_Part_Len] =
{
	CLossA_Curr_FF_FF,	/*失流*/
	CLossB_Curr_FF_FF,
	CLossC_Curr_FF_FF,
	COverA_Curr_FF_FF,	/*过流*/
	COverB_Curr_FF_FF,
	COverC_Curr_FF_FF,
};

uchar8 Is_EventReg_DI0FFOK_Part(Str_Comm_645 *pV_645Frame)
{
	uchar8 i;

	for( i = 0; i < C_TB_DI0FFEventDI3DI2_Part_Len; i++ )
	{
		if( pV_645Frame->DI == TB_DI0FFEventDI3DI2_Part[i] )
		{
			return C_OK;
		}
	}
	return C_No_Request_data;
}

/***************************************************************************
函数原型 	Comm_Read_EventReg
函数功能	读事件记录寄存器
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	通信通道缓冲区
函数备注	将特殊处理的首先挑选出来 。剩下，先调用
				事件记录模块的读接口函数，返回无标识码，再调用数据层
***************************************************************************/
uchar8 SF_EventClrRead_645(Str_Comm_645 *pV_645Frame, uchar8 *P_DataBuf, uchar8 *P_DataLength)
{/*645协议处理，后续修改 lzy 20211102*/
#if 0
    ulong32 V_ulReadOADBuf[2];
    uchar8  V_timeFlash = 0x68, V_ucDataBuff = 0, V_ucRetrun, V_ucJudgeAll00;
    ushort16 V_usDataLen = 1024;
    uchar8  V_ucData[1024];
    ulong32 V_EventOAD = 0xFFFFFFFF;
    uchar8  i, V_ucHappening_Flag = C_End_EventState;

    V_ulReadOADBuf[0] = CEven_Clear_Degree_698 | (pV_645Frame->DI & 0x000000FF);
    V_ulReadOADBuf[1] = 0xFFFFFFFF;

    if( ( V_ulReadOADBuf[0] & 0x000000FF ) == 0x00000001 ) 					/*上1次事件记录读取*/
	{
		V_ucRetrun = Inf_ReadEventLast_H(V_ulReadOADBuf, V_ucData, &V_usDataLen, V_timeFlash, &V_ucHappening_Flag);
	}
    else
	{
		V_ucRetrun = InF_ReadEventData(V_ulReadOADBuf, &V_ucDataBuff, V_ucData, &V_ucDataBuff, &V_usDataLen, V_timeFlash);
	}
	if(V_ucRetrun == C_OK)
	{
        /*发生时间*/
        PF_CopyDataBytes(&V_ucData[C_DataOffset_Time], &P_DataBuf[0], ( CLEventHPTime - 1 ) );
        /*操作者代码*/
        SF_Event_Relay_JudgeAll00(V_ulReadOADBuf[0], &V_ucJudgeAll00);
        if( ( V_ucJudgeAll00 == C_ALL00_Flag )|| ( ( SF_JudgeAllAA( V_ucData, ( CLEventHPTime - 1 ) ) == C_OK ) ) )
        {
            V_usDataLen = C_EventClr_Len - ( CLEventHPTime - 1 );
            memset( &P_DataBuf[CLEventHPTime - 1], 0x00, V_usDataLen );
        }
        else
        {
            V_usDataLen = CLRelayOpen_OpeCode_1;
            memset(&P_DataBuf[CLEventHPTime - 1], 0xFF, V_usDataLen);
            /*数据标识*/
            V_usDataLen = 4;
            PF_Buffer4ToUlong32(&V_ucData[C_DataOffset_OAD], &V_EventOAD, V_usDataLen);
            for( i = 0; i < Pstr_ParaChange_Event_Len; i++ )
            {
				if(V_EventOAD == Pstr_ParaChange_Event[i].OAD)
				{
					V_EventOAD = Pstr_ParaChange_Event[i].DI;
					V_usDataLen = 4;
					PF_Ulong32ToBuffer4(&P_DataBuf[(CLEventHPTime - 1) + CLRelayOpen_OpeCode_1], &V_EventOAD, V_usDataLen);
					break;
				}
            }
            if(i >= Pstr_ParaChange_Event_Len)
            {
              memset(&P_DataBuf[(CLEventHPTime - 1) + CLRelayOpen_OpeCode_1], 0xFF, 4);
            }
        }

	}
    else
    {
		memset(P_DataBuf, 0x00, C_EventClr_Len);
    }

	 *P_DataLength = C_EventClr_Len;
#endif
	 return C_OK;
}

/***************************************************************************
函数原型 	Comm_Read_EventReg
函数功能	读事件记录寄存器
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	通信通道缓冲区
函数备注	将特殊处理的首先挑选出来 。剩下，先调用
				事件记录模块的读接口函数，返回无标识码，再调用数据层
***************************************************************************/
void Comm_Read_EventReg(Str_Comm_645 *pV_645Frame)
{
	ushort16 LenFor_Data;
	uchar8   V_ReturnData, V_ucDataLen, V_ucBuffer[2];
	uchar8	 buf_O_CanWrite = 0;					/*缓冲区可写数据的偏移*/
	uchar8   *pData;

	pData = &pV_645Frame->Data[C_11_SData];
	LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - buf_O_CanWrite ;
	/*集合读校表命令,带后续帧*/
	if( ( (pV_645Frame->DI & 0xFFFFFF00) == 0x03FBFF00)
		|| ( ( ( (pV_645Frame->DI & 0xFFFFFF00) == CDe_Clear_Degree) || ( (pV_645Frame->DI & 0xFFFFFF00) == CProgPT_Degree) )
		&& (pV_645Frame->Data[C_O_DI0] <= 0x0A) && (pV_645Frame->Data[C_O_DI0] != 0x00) )
		|| ( Is_EventReg_DI0FFOK_Part(pV_645Frame) == C_OK ) )
	{
		Read_EventRegWithNxtFrame(pV_645Frame);
		return;
	}

	if(pV_645Frame->Data[C_O_DI0]<=0x0A)
	{
		if((pV_645Frame->DI & 0xFFFFFF00) == (CProgram_Note_1_645 & 0xFFFFFF00)) /*/上1-上10次编程记录单独处理*/
		{
            RD_ProgRecordReg_645(pV_645Frame);
			return;
		}
        else if( ( ( pV_645Frame->DI & 0xFFFFFF00 )== CEven_Clear_Degree ) && ( pV_645Frame->Data[C_O_DI0] != 0 ) )
        {
            V_ReturnData = SF_EventClrRead_645(pV_645Frame, pData, &V_ucDataLen);
        }
		else
		{
			if( ( pV_645Frame->Data[C_O_DI3] == 0x03 ) && ( pV_645Frame->Data[C_O_DI0] == 0x00 ) ) 						/*累计次数及时间处理*/
			{
     		  	V_ReturnData = Inf_ReadEventCurrentData_Com645(pV_645Frame->DI, pData, &V_ucDataLen, C_Flag03);
			}
			else if( ( ( ( (pV_645Frame->Data[C_O_DI3] >= 0x11 )&& ( pV_645Frame->Data[C_O_DI3] <= 0x20 ) )		/*累计次数及时间处理*/
				    || ( pV_645Frame->Data[C_O_DI3] == 0x1B) || (pV_645Frame->Data[C_O_DI3] == 0x1D) || (pV_645Frame->Data[C_O_DI3] == 0x1E) )
				    || ( (pV_645Frame->Data[C_O_DI3] == 0x21) &&( (pV_645Frame->Data[C_O_DI0] == 0x00 ) ) ) )
			      && ( pV_645Frame->Data[C_O_DI1] == 0x00) )
			{
       			V_ReturnData = Inf_ReadEventCurrentData_Com645(pV_645Frame->DI, pData, &V_ucDataLen, C_Flagelse);
			}
			else if( ( pV_645Frame->Data[C_O_DI3] == 0x10 )		/*失压总次数、总累计时间*/
				   && ( ( pV_645Frame->Data[C_O_DI2] == 0x00 ) || ( pV_645Frame->Data[C_O_DI1] == 0x00 ) ) )
			{
       			V_ReturnData = Inf_ReadEventCurrentData_Com645(pV_645Frame->DI, pData, &V_ucDataLen, C_Flag10);
			}
			else
			{
				V_ReturnData = SF_GetAPDU_EventRead_645(pV_645Frame, pData, &LenFor_Data);
				PF_Ushort16ToBuffer2(V_ucBuffer, &LenFor_Data);
        	    V_ucDataLen = V_ucBuffer[0];
			}
		}
	}
	else
	{
        V_ReturnData = C_IDError;
	}
	if(V_ReturnData == C_OK)
	{/*返回正确，表示事件记录模块支持该寄存器读取。*/
		Comm_11_03Response_Normal(pV_645Frame, pData, V_ucDataLen);

	}
	else if(V_ReturnData == C_IDError)
	{/*标识码错误*/
		Comm_Response_Set_ReadErr(C_No_Request_data_645, pV_645Frame);
	}
	else
	{
		Comm_Response_Set_ReadErr(C_OtherErr_645, pV_645Frame);
	}
	return;
}
/***************************************************************************
函数原型 	RD_ProgRecordReg
函数功能	读总编程记录相关寄存器应答
输入参数	*pV_645Frame					:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	通道相关的变量
函数备注	总编程记录中编程总次数，上1-上10次编程记录都在这里解析
***************************************************************************/
void RD_ProgRecordReg(Str_Comm_645 *pV_645Frame)
{
	uchar8	buf[3];
	uchar8	buf_O_CanWrite = 0;					/*缓冲区可写数据的偏移*/
	ushort16	LenFor_Data, V_usDataEncode;	/*缓冲区可被写的总的长度*/
	uchar8	*pData;
	uchar8	V_ReturnData;
/*取指针*/
	pData = &pV_645Frame->Data[C_11_SData];
	LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - buf_O_CanWrite ;
/*判断是否为编程过程中，顺便取出数据*/
	V_ReturnData = Get_ProgRecord1InRam(pData, &SV_Comm_Parse.ProgRecord);
	if(V_ReturnData == C_OK)
	{/*正处于编程过程中*/
		if(pV_645Frame->DI == CProgram_Note_1)
		{/*为上1次编程记录*/
			LenFor_Data = CLProgram_Note_1;
		}
		else if(pV_645Frame->DI == CProgram_Degree)
		{/*为编程总次数，需加1*/
			V_ReturnData = InF_Read_Data(pV_645Frame->DI, pData, &LenFor_Data, &V_usDataEncode);
			buf[0] = 0x01;
			buf[1] = 0;
			buf[2] = 0;
			PF_BCDAddBytes(pData, buf, pData, LenFor_Data);
		}
		else
		{/*其他肯定为上2-上10次将DI0减1读数据层*/
			V_ReturnData = InF_Read_Data((pV_645Frame->DI -0x00000001), pData, &LenFor_Data, &V_usDataEncode);
		}
	}
	else
	{/*不在编程过程中,直接读数据层*/
		V_ReturnData = InF_Read_Data(pV_645Frame->DI, pData, &LenFor_Data, &V_usDataEncode);
	}
/*根据返回值，应答*/
	if(V_ReturnData == C_OK)
	{
		Comm_11_03Response_Normal(pV_645Frame, pData, LenFor_Data);
	}
	else
	{
		Comm_Response_Set_ReadErr(C_OtherErr, pV_645Frame);
	}
}

/***************************************************************************
函数原型 	RD_ProgRecordReg
函数功能	读总编程记录相关寄存器应答
输入参数	*pV_645Frame					:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	通道相关的变量
函数备注	总编程记录中编程总次数，上1-上10次编程记录都在这里解析
***************************************************************************/
void RD_ProgRecordReg_645(Str_Comm_645 *pV_645Frame)
{
	uchar8	buf[3];
	uchar8	buf_O_CanWrite = 0;					/*缓冲区可写数据的偏移*/
	ushort16	LenFor_Data, V_usDataEncode;							/*缓冲区可被写的总的长度*/
	uchar8	*pData;
	uchar8	V_ReturnData;
/*取指针*/
	pData = &pV_645Frame->Data[C_11_SData];
	LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - buf_O_CanWrite ;
/*判断是否为编程过程中，顺便取出数据*/
	V_ReturnData = Get_ProgRecord1InRam_645(pData, &SV_Comm_Parse.ProgRecord_645);
	if(V_ReturnData == C_OK)
	{/*正处于编程过程中*/
		if(pV_645Frame->DI == CProgram_Note_1_645)
		{/*为上1次编程记录*/
			LenFor_Data = CLProgram_Note_1_645;
		}
		else if(pV_645Frame->DI == CProgram_Degree)
		{/*为编程总次数，需加1*/
			V_ReturnData = InF_Read_Data(CProgram_Degree_645, pData, &LenFor_Data, &V_usDataEncode);
			buf[0] = 0x01;
			buf[1] = 0;
			buf[2] = 0;
			PF_BCDAddBytes(pData, buf, pData, LenFor_Data);
		}
		else
		{/*其他肯定为上2-上10次将DI0减1读数据层*/
			V_ReturnData = InF_Read_Data((pV_645Frame->DI - 0x00000001), pData, &LenFor_Data, &V_usDataEncode);
		}
	}
	else
	{/*不在编程过程中,直接读数据层*/
		if(pV_645Frame->DI == CProgram_Degree)
		{
			V_ReturnData = InF_Read_Data(CProgram_Degree_645, pData, &LenFor_Data, &V_usDataEncode);
		}
		else
		{
			V_ReturnData = InF_Read_Data(pV_645Frame->DI, pData, &LenFor_Data, &V_usDataEncode);
		}
	}
/*根据返回值，应答*/
	if(V_ReturnData == C_OK)
	{
		Comm_11_03Response_Normal(pV_645Frame, pData, LenFor_Data);
	}
	else
	{
		Comm_Response_Set_ReadErr(C_OtherErr, pV_645Frame);
	}
}


/***************************************************************************
函数原型：void InF_RD_ProgRecordReg(ulong32 V_ulDI, uchar8 *P_Buffer)
功能描述：读总编程记录相关寄存器,
输入参数：V_ulDI编程记录标识码，	P_Buffer读取数据存放地址
输出参数： *P_Buffer为读取编程记录数据
返回参数	： C_OK表示读取数据正确，C_IDError数据标识码错，C_Error其他错误
调用位置： 通道相关的变量
备    注： 总编程记录中编程总次数，上1-上10次编程记录都通过该函数读取
***************************************************************************/
uchar8 InF_RD_ProgRecordReg(ulong32 V_ulDI, uchar8 *P_Buffer)
{
	uchar8 V_DataTemp[ProgCrc_O + 2];
    uchar8 V_ucReturn = C_Error;

	if(V_ulDI != CProgram_Note_1)
	{
		return V_ucReturn;
	}

    V_ucReturn = Get_ProgRecord1InRam(V_DataTemp, &SV_Comm_Parse.ProgRecord);
	if( V_ucReturn == C_OK)
	{
		PF_CopyDataBytes(V_DataTemp, P_Buffer, CLProgram_Note_1);
		memset(&P_Buffer[ProgEndTime], 0xAA, CLEventEndTime);
	}

    return V_ucReturn;
}
/***************************************************************************
函数原型 	RD_Pre1_FF_NoBalEvent
函数功能	读上1次不平衡率集合
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	通道通信缓冲区
函数备注	不平衡事件指:电压、电流、电流严重不平衡
				不平衡率由事件记录模块中不平衡率替代
***************************************************************************/
#define		C_O_NoBal		70
void		RD_Pre1_FF_NoBalEvent(Str_Comm_645 *pV_645Frame)
{
	uchar8	buf_O_CanWrite = 0;					/*缓冲区可写数据的偏移*/
	ushort16	LenFor_Data, V_usDataEncode;							/*缓冲区可被写的总的长度*/
	uchar8	*pData;
	uchar8	V_ReturnData;

/*注意pData不包含DI数据*/
	pData = &pV_645Frame->Data[C_11_SData];
	LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - buf_O_CanWrite ;
/*读数据层上1次的集合*/
	V_ReturnData = InF_Read_Data(pV_645Frame->DI, pData, &LenFor_Data, &V_usDataEncode);
	if(V_ReturnData !=C_OK)
	{/*不可能到这里*/
		Comm_Response_Set_ReadErr(C_OtherErr,pV_645Frame);
		return;
	}
/*读事件记录模块的不平衡率替代*/
	if(V_ReturnData != C_OK)
	{/*不可能到这里*/
		Comm_Response_Set_ReadErr(C_OtherErr,pV_645Frame);
		return;
	}
	Comm_11_03Response_Normal(pV_645Frame, pData,LenFor_Data);
}

/***************************************************************************
函数原型 	RD_Pre1_FF_VoltageEvent
函数功能	读上1次电压类事件集合
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	通道通信缓冲区
函数备注	电压类事件指:失压、欠压、过压、断相,上1次AH由事件记录模块替代
***************************************************************************/
#define		C_O_Total_Ah		109			/*总的A*/
void		RD_Pre1_FF_VoltageEvent(Str_Comm_645 *pV_645Frame)
{
	uchar8	buf_O_CanWrite = 0;					/*缓冲区可写数据的偏移*/
	ushort16	LenFor_Data, V_usDataEncode;							/*缓冲区可被写的总的长度*/
	uchar8	*pData;
	uchar8	i;
	uchar8	V_ReturnData;
	ulong32	Ah_DI1;

/*注意pData不包含DI数据*/
	pData = &pV_645Frame->Data[C_11_SData];
	LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - buf_O_CanWrite ;
/*读数据层上1次的集合*/
	V_ReturnData = InF_Read_Data(pV_645Frame->DI, pData, &LenFor_Data, &V_usDataEncode);
	if(V_ReturnData !=C_OK)
	{/*不可能到这里*/
		Comm_Response_Set_ReadErr(C_OtherErr, pV_645Frame);
		return;
	}
/*当前Ah数由事件记录接口函数替代*/
	Ah_DI1 = 0x00002100;				/*21 22 23 24*/
	buf_O_CanWrite = C_O_Total_Ah;
	for( i = 0; i < 4; i++ )			/*总、ABC所以循环次数为4*/
	{
		Ah_DI1 = Ah_DI1 + 0x0100;
		if(V_ReturnData != C_OK)
		{/*不可能到这里*/
			Comm_Response_Set_ReadErr(C_OtherErr, pV_645Frame);
			return;
		}
		buf_O_CanWrite = buf_O_CanWrite + CLLossAVol_TolAh_1;
	}
	Comm_11_03Response_Normal(pV_645Frame, pData, LenFor_Data);
}

/***************************************************************************
函数原型 	Is_Pre1_RFF_VoltageEvent
函数功能	判断是否属于上1次电压类事件集合读
输入参数	DataCode					:需读的标识码
输出参数
返回参数	C_OK/C_Error
全局变量
函数备注	电压类事件指:失压、欠压、过压、断相
***************************************************************************/
uchar8	Is_Pre1_RFF_VoltageEvent(ulong32	DataCode)
{
	switch(DataCode)
	{
		case		CLossAVol_FF_1:			/*失压类*/
		case		CLossBVol_FF_1:
		case		CLossCVol_FF_1:

		case		CLowAVol_FF_1:			/*欠压类*/
		case		CLowBVol_FF_1:
		case		CLowCVol_FF_1:

		case		COverAVol_FF_1:			/*过压类*/
		case		COverBVol_FF_1:
		case		COverCVol_FF_1:

		case		CBreakAVol_FF_1:		/*断相类*/
		case		CBreakBVol_FF_1:
		case		CBreakCVol_FF_1:
			return(C_OK);
		default:
			return(C_Error);
	}
}

/***************************************************************************
函数原型 	Read_EventRegWithNxtFrame
函数功能	带后续帧读取事件记录
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	通信通道缓冲区
函数备注	调用本函数前，保证DI已经判断完全正确，且为有后续帧
***************************************************************************/
void Read_EventRegWithNxtFrame(Str_Comm_645 *pV_645Frame)
{
	Str_Comm_NxtFrame	Comm_NxtFrame;
	Str_Comm_NxtFrame	*pStr_Comm_NxtFrame;
	uchar8	TB_NxtFrame_LineNo;						/* 1级表行号*/
	ulong32	*pTB_SubDI;								/*分帧标识码数据*/
	uchar8	V_ReturnData;

	pStr_Comm_NxtFrame = &Comm_NxtFrame;
/*获取通道后续帧变量*/
	if(Get_SV_CommNxtFrame(pV_645Frame->ChannelNo, pStr_Comm_NxtFrame) != C_OK)
	{
		return;										/*出错，什么都不处理。*/
	}
	NxtF_DataCode = pV_645Frame->DI;

/*查阅1级表*/
	for( TB_NxtFrame_LineNo = 0; TB_NxtFrame_LineNo < C_TBNxtFrameNum; TB_NxtFrame_LineNo++ )
	{
		if( ( ( pV_645Frame->DI & 0xFFFFFF00 ) | 0x00000001 ) == TB_NxtFrame[TB_NxtFrame_LineNo].DataCode )
		{
			break;
		}
		else if( ( pV_645Frame->DI == TB_NxtFrame[TB_NxtFrame_LineNo].DataCode )
			   && ( ( pV_645Frame->DI & 0x000000FF ) == 0x000000FF ) )
		{
			break;
		}/*else继续查找*/
	}
	if(TB_NxtFrame_LineNo >= C_TBNxtFrameNum)
	{
		Comm_Response_Set_ReadErr(C_No_Request_data, pV_645Frame);
		return;
	}
	pTB_SubDI = TB_NxtFrame[TB_NxtFrame_LineNo].pTB_SubDI;
	if(TB_NxtFrame[TB_NxtFrame_LineNo].Method == C_Event_Method)
	{
		NxtF_Nxt_DataCode = pTB_SubDI[0];
		/*带固定分帧方式读取寄存器。*/
		/*注意:1、数据已经置发送缓冲区，pStr_Comm_NxtFrame只需要置Nxt_DataCode*/
		V_ReturnData = ReadCurrFFRecordReg_NxtFrame(pStr_Comm_NxtFrame, pV_645Frame, TB_NxtFrame_LineNo);
	}
	else
	{
		NxtF_Nxt_DataCode = pTB_SubDI[0] | ( pV_645Frame->DI & 0x0000000F );
		/*带固定分帧方式读取寄存器。*/
		/*注意:1、数据已经置发送缓冲区，pStr_Comm_NxtFrame只需要置Nxt_DataCode*/
		V_ReturnData = ReadProgRecordReg_NxtFrame(pStr_Comm_NxtFrame, pV_645Frame, TB_NxtFrame_LineNo);
	}
	if(V_ReturnData  == C_HaveNxtFrame)
	{
		Comm_IfHaveNxtFrame_Set_C(pV_645Frame);
		NxtF_Sub_DataCode = NxtF_Nxt_DataCode;
		NxtF_FrameFinished = C_Error;										/*表示有后续帧*/
		NxtF_HaveReport = C_Error;											/*表示未主动上报过*/
		NxtF_FrameNo = 0x01;
		Set_SV_CommNxtFrame(pV_645Frame->ChannelNo, pStr_Comm_NxtFrame);	/*11命令是不用加帧序号的。*/
	}
}

/***************************************************************************
函数原型 	R_CarryingSubDIReg
函数功能	该标识码数据层不支持，采用分项标识码读取方法
输入参数	*pV_645Frame				:接收到的数据帧
				*pCarryingSubDI			:带分项标识码一级表中的数据
输出参数 	无
返回参数	无
全局变量 	通道相关通信缓冲区
函数备注	1、本函数虽然分帧，但是无后续帧的。
				2、本函数分项标识码是不含次数等信息的。
***************************************************************************/
void	R_CarryingSubDIReg(Str_Comm_645 *pV_645Frame, Str_TBCarryingSubDI_1 *pCarryingSubDI)
{
	uchar8	buf_O_CanWrite = 0;					/*缓冲区可写数据的偏移*/
	ushort16	LenFor_Data, V_usDataEncode;	/*缓冲区可被写的总的长度*/
	uchar8	*pData;
	uchar8	i;
	uchar8	V_ReturnData;
	ulong32	*pTBSubDI;							/* 2级表的首地址*/
	uchar8	TBSubDILen;							/* 2级表长度(行)*/

	pTBSubDI = pCarryingSubDI->pTB_SubDI;
	TBSubDILen = pCarryingSubDI->SubDINum;

/*注意pData不包含DI数据*/
	pData = &pV_645Frame->Data[C_11_SData];
	LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - buf_O_CanWrite ;
/*循环读数据*/
	for( i = 0; i < TBSubDILen; i++ )
	{
		V_ReturnData = InF_Read_Data(pTBSubDI[i], &pData[buf_O_CanWrite], &LenFor_Data, &V_usDataEncode);
		if(V_ReturnData != C_OK)
		{/*不管长度错误，无标识码，CRC不对，都是不应该出现的，应答其他错误*/
			Comm_Response_Set_ReadErr(C_OtherErr, pV_645Frame);
			return;
		}
		/*调整指针和剩余空间*/
		buf_O_CanWrite = buf_O_CanWrite + LenFor_Data;				/*这里LenFor_Data被数据层改写成所读数据项实际长度了。*/

		if( buf_O_CanWrite > ( C_Comm_Data_MaxLen - CLen_DI ) )
		{/*不可能到这里。*/
			Comm_Response_Set_ReadErr(C_OtherErr, pV_645Frame);
			return;
		}

		LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - buf_O_CanWrite ;
	}
	Comm_11_03Response_Normal(pV_645Frame, pData,buf_O_CanWrite);
}
/***************************************************************************
函数原型 	IsIn_TBCarryingSubDI_1
函数功能	查阅带分项标识码的1级表，确认总标识码是否在1级表中，
				是返回正确，并将1级表数据返回
输入参数	DataCode					:读的标识码
				pTBCarryingSubDI_1_Line	:一级表行号指针
输出参数 	*pTBCarryingSubDI_1_Line	:一级表中的行号
返回参数	C_OK					:在一级表中搜素到
				C_Error					:在一级表中未搜素到
全局变量 	无
函数备注	目前本函数和固定分帧表格，方法不混用。
***************************************************************************/
uchar8		IsIn_TBCarryingSubDI_1(ulong32 DataCode, uchar8 *pTBCarryingSubDI_1_Line)
{
	Str_TBCarryingSubDI_1	*pTBCarryingSubDI_1;
	uchar8	i;

	pTBCarryingSubDI_1 = (Str_TBCarryingSubDI_1 *)&TBCarryingSubDI_1[0];
	for( i = 0; i < CLen_TBCarryingSubDI_1; i++ )
	{
		if(pTBCarryingSubDI_1[i].DataCode == DataCode)
		{
			break;
		}
	}
	if(i >= CLen_TBCarryingSubDI_1)
	{
		return(C_Error);
	}
	else
	{
		*pTBCarryingSubDI_1_Line = i;
		return(C_OK);
	}
}
/***************************************************************************
函数原型 SF_ASCIItoChar(uchar8 *pData,uchar8 *pDataLen)
函数功能	 软件备案号输入数据为ASCII码转换为字符
输入参数	 pData输入ASCII码数据地址 *pDataLen待转换数据长度
输出参数 pData转换后数据	*pDataLen转换后数据长度
返回参数	 是否转换成功 C_OK 成功  C_Error失败
全局变量 无
函数备注	 ASCII码只转换全AA和0-9，其余按转换失败。转换长度固定为16字节ASCII码
***************************************************************************/
uchar8 SF_ASCIItoChar(uchar8 *pData, uchar8 *pDataLen)
{
  uchar8 V_ucDataLen, V_ucReturn, V_ucBuf[CLSoftw_Record_Number], i, j;
  uchar8 V_ucAANum = 0, V_ucIllegalData_Num = 0;

  V_ucDataLen = *pDataLen;
  V_ucReturn = C_Error;

	if(V_ucDataLen == CLSoftw_Record_Number)
	{
		for( i = 0; i < CLSoftw_Record_Number; i++ )
		{
			if(*(pData+i) == C_ASCII_A)												/*全AA*/
			{
				V_ucAANum++;
			}
			else if( (*(pData + i) < C_ASCII_0 ) || ( *(pData + i) > C_ASCII_9 ) )  /*只转换0-9*/
			{
				V_ucIllegalData_Num++;
			}
		}
		if( V_ucAANum == CLSoftw_Record_Number )
		{
			memset(pData, 0xAA, CLSoftw_Record_Number_645);
			*pDataLen = CLSoftw_Record_Number_645;
			V_ucReturn = C_OK;
		}
		else if(V_ucIllegalData_Num != 0)											/*含有非0-9数据*/
		{
			return V_ucReturn;
		}
		else
		{
			j = 0;
			for( i = 0; i < CLSoftw_Record_Number_645; i++ )
			{
				V_ucBuf[i] = *(pData + 1 + j);
				V_ucBuf[i] <<= 4;
				V_ucBuf[i] |=  (*(pData + j)) & 0x0F;
				j += 2;
			}
			PF_CopyDataBytes(V_ucBuf, pData, CLSoftw_Record_Number_645);
			*pDataLen = CLSoftw_Record_Number_645;
			V_ucReturn = C_OK;
		}
	}
	return V_ucReturn;
}
/***************************************************************************
函数原型 SF_ChartoASCII(uchar8 *pData,uchar8 *pDataLen)
函数功能	 输入数据为Char转换为ASCII
输入参数	 pData输入Char数据地址 *pDataLen待转换数据长度
输出参数 pData转换后数据	*pDataLen转换后数据长度
返回参数	 是否转换成功 C_OK 成功  C_Error失败
全局变量 无
函数备注	 转换长度固定为7字节Char,转换5字节生产时间
***************************************************************************/
uchar8 SF_ChartoASCII(uchar8 *pData, uchar8 *pDataLen)
{
    uchar8 i, j, V_ucLength = *pDataLen, V_ucBuf[CLProd_Date645] = {0};
    uchar8 V_ucReturn = C_Error;

    j = 0;
    if(*pDataLen > CLProd_Date_YMDHM)
    {
      V_ucReturn = C_Error;
    }
    else
    {
        for(i = 0; i < V_ucLength; i++)
        {
            V_ucBuf[j+ 1] = (*(pData + i) >> 4) | 0x30;
            V_ucBuf[j] = (*(pData + i) & 0x0F) | 0x30;
            j += 2;
        }
      PF_CopyDataBytes(V_ucBuf, pData, CLProd_Date645);
      *pDataLen = CLProd_Date645;
      V_ucReturn = C_OK;
    }
    return V_ucReturn;
}
/***************************************************************************
函数原型 uchar8	SF_Read_AuthTime(ulong32 OAD,uchar8 *p_Data,ushort8 *Len)
函数功能	读取红外认证时效和身份认证时效
输入参数	 OAD要读取的数据标识
输出参数 读取的数据地址p_Data；读取的数据长度Len
返回参数	C_OK/C_Error
全局变量
函数备注
***************************************************************************/
uchar8	SF_Read_AuthTime(ulong32 OAD,uchar8 *p_Data,uchar8 *Len)
{
    uchar8   V_Return = C_Error;
    uchar8   V_ucData[4] = {0};
	ushort16 V_DataLen, V_usDataEncode;
    ulong32  V_ulData;
    ulong32  V_ulOAD;

    if( ( OAD == C_IRAuth_Timer645 ) || ( OAD == CInfra_Auth_Remain_Time_645 ) )
    {
        if(OAD == C_IRAuth_Timer645)
        {
			V_ulOAD = C_IRAuth_Timer;
			V_DataLen = CL_IRAuth_Timer;
        }
        else
        {
			V_ulOAD = CInfra_Auth_Remain_Time_645;
			V_DataLen = CLInfra_Auth_Remain_Time_645;
        }
        V_Return = InF_Read_Data(V_ulOAD, V_ucData, &V_DataLen, &V_usDataEncode);
        if(V_Return == C_OK)
        {
            PF_Buffer4ToUlong32(V_ucData, &V_ulData, 4);
            V_DataLen = 4;
            PF_HextoBCDBytes(&V_ulData, V_ucData, (uchar8 *)&V_DataLen);
            if(V_ulData > C_BCDMax_OneBit)			/*1字节BCD最大99*/
            {
                V_ucData[0] = C_BCDMax;
            }
            PF_CopyDataBytes(V_ucData, p_Data, CL_IRAuth_Timer);
            *Len = CL_IRAuth_Timer;
        }
        else
        {
          return V_Return;
        }
    }
    else if(OAD == CID_Auth_Remain_Time_645)
    {
        V_ulOAD = CID_Auth_Remain_Time_645;
        V_DataLen = CLID_Auth_Remain_Time_645;
        V_Return = InF_Read_Data(V_ulOAD, V_ucData, &V_DataLen, &V_usDataEncode);
        if(V_Return == C_OK)
        {
            PF_Buffer4ToUlong32(V_ucData, &V_ulData, 4);
            V_DataLen = 4;
            PF_HextoBCDBytes(&V_ulData, V_ucData, (uchar8 *) &V_DataLen);
            if(V_ulData > C_BCDMax_TwoBit)					/*2字节BCD最大9999*/
            {
                V_ucData[1] = C_BCDMax;
                V_ucData[0] = C_BCDMax;
            }
            PF_CopyDataBytes(V_ucData, p_Data, CLID_Auth_Remain_Time_645);
            *Len = CLID_Auth_Remain_Time_645;
        }
        else
        {
          return V_Return;
        }
    }/*else返回错误*/

    return V_Return;
}
/*******************************************************************************
函数原型：void		Comm_Read_P_V_Reg(Str_Comm_645 *pV_645Frame)
功能描述：读数据
输入参数：pV_645Frame 读数据的信息
输出参数：pV_645Frame 返回读的内容和错误信息状态
返回参数：
调用位置：
备    注：
*******************************************************************************/
void		Comm_Read_P_V_Reg(Str_Comm_645 *pV_645Frame)
{
	uchar8	buf_O_CanWrite = 0;						/*缓冲区可写数据的偏移*/
	ushort16	LenFor_Data, V_usDataEncode;							/*缓冲区可被写的总的长度*/
	uchar8	*pData;
	uchar8	V_ReturnData = C_OK;					/*默认数据是正确的*/
	uchar8	i, V_ucDataoff = 0;
    uchar8  j;
    ulong32 V_ulData = 0;
	ulong32	LimitDI;
	uchar8  V_ucTemp[2], V_ucLength, V_uck;
	ulong32 V_ulTemp;

/*注意pData不包含DI数据*/
	pData = &pV_645Frame->Data[C_11_SData];
	LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - buf_O_CanWrite ;

/*判断是否为密码的读取*/
	if( ( pV_645Frame->DI & 0xFFFFFF00 ) == 0x04000C00 )
	{
		Comm_Response_Set_ReadErr(C_Unauthorized_645, pV_645Frame);
		return;
	}
	if( pV_645Frame->DI == CRec_MeterPassWord )
	{
		Comm_Response_Set_ReadErr(C_Unauthorized_645, pV_645Frame);
		return;
	}
/*判断是否为故障信息主动上报标识码*/
	if( pV_645Frame->DI == CDrive_Report_State_645 )
	{
		/*取故障信息主动上报数据帧。包含DI、状态字、新增次数。*/
		Set_ReportStateFrame(pData, (uchar8 *)&LenFor_Data);
		/*置发送数据*/
		Comm_Response_FromP_Normal(pV_645Frame, pData, LenFor_Data);
		/*启动已发送定时器及置位已发送状态字节*/
		Set_SV_HaveReportState(&pData[CLen_DI]);
		return;
	}

/*判断标识码是否为校表脉冲，是固定80ms*/
	if( pV_645Frame->DI == 0x04000105 )
	{
		pData[0] = 0x80;
		pData[1] = 0;
		LenFor_Data = 0x02;
		Comm_11_03Response_Normal(pV_645Frame, pData, LenFor_Data);
		return;
	}
/*判断标识码是否为调制型红外光口波特率特征字，固定0x04*/
	if( pV_645Frame->DI == CMod_InFr_Baud_645 )
	{
		pData[0] = C_bps_1200;
		LenFor_Data = 0x01;
		Comm_11_03Response_Normal(pV_645Frame, pData, LenFor_Data);
		return;
	}
/*判断是否读取内部版本号*/
	if( pV_645Frame->DI == 0x04800010 )
	{
		PF_CopyDataBytes((uchar8 * )GV_C_Internal_Version, pData, CL_Internal_Version);
		LenFor_Data = CL_Internal_Version;
		Comm_11_03Response_Normal(pV_645Frame, pData, LenFor_Data);
		return;
	}
/*时区表，时段表根据时区表数目，时段表数目进行应答*/
	if( ( pV_645Frame->DI == CFirst_TZone_Data_645 ) || ( pV_645Frame->DI == CSec_TZone_Data_645 ) )
	{
		LimitDI = CYear_Zone_Num;
		Comm_Read_TZone_PTReg(pV_645Frame, LimitDI);
		return;
	}
	else if( ( ( pV_645Frame->DI >= CFirst_TZone_1PT_Data_645 ) && ( pV_645Frame->DI <= CFirst_TZone_8PT_Data_645 ) )
		   || ( ( pV_645Frame->DI >= CSec_TZone_1PT_Data_645 ) && ( pV_645Frame->DI <= CSec_TZone_8PT_Data_645 ) ) )
	{
		LimitDI = CDay_Time_Num;
		Comm_Read_TZone_PTReg(pV_645Frame, LimitDI);
		return;
	}
/*判断是否读取软IJ有效时间*/
	if( pV_645Frame->DI == 0x04FE0304 )
	{
		PF_Ulong32ToBuffer4(V_ucTemp, &SV_Comm_Parse.SI_JTimer.Timer, 2);
		PF_BCDtoHexBytes(V_ucTemp, &V_ulTemp, 2);
		V_ulTemp *= 5;
		V_ucLength = 4;
		PF_HextoBCDBytes(&V_ulTemp, pData, &V_ucLength);
		LenFor_Data = 4;
		Comm_11_03Response_Normal(pV_645Frame, pData, LenFor_Data);
		return;
	}
/*其他读数据层，根据数据层返回值对应应答*/
	if( pV_645Frame->Data[C_O_DI3] == 0x02 )
	{
		if( pV_645Frame->Data[C_O_DI1] == 0xFF )
		{
			for( i = 0; i < Pstr_ParaChange02_Len; i++ )
			{
				if( ( pV_645Frame->DI & 0xFFFF00FF ) == (Pstr_ParaChange02[i].DI & 0xFFFF00FF ) )
				{
					V_ReturnData = InF_Read_Data(Pstr_ParaChange02[i].OAD, pData + V_ucDataoff, &LenFor_Data, &V_usDataEncode);
					V_ucDataoff += LenFor_Data;
				}
			}
			if( V_ucDataoff != 0 )
			{
				LenFor_Data = V_ucDataoff;
				if(V_ReturnData == C_OK)
				{
					Comm_11_03Response_Normal(pV_645Frame, pData, LenFor_Data);
					return;
				}
			}

		}
		else
		{
			for( i = 0; i < Pstr_ParaChange02_Len; i++ )
			{
				if( pV_645Frame->DI == Pstr_ParaChange02[i].DI )
				{
					V_ReturnData = InF_Read_Data(Pstr_ParaChange02[i].OAD, pData, &LenFor_Data, &V_usDataEncode);
					if(V_ReturnData == C_OK)
					{
					  Comm_11_03Response_Normal(pV_645Frame, pData, LenFor_Data);
					  return;
					}
					break;
				}
			}
		}
	}
	if( pV_645Frame->Data[C_O_DI3] == 0x04 )
	{
		if( pV_645Frame->DI == 0x040005FF )
		{
			for( i = 0; i < Pstr_ParaChange_Len; i++ )
			{
				if( ( pV_645Frame->DI & 0xFFFFFF00 ) == (Pstr_ParaChange[i].DI & 0xFFFFFF00 ) )
				{
					V_ReturnData = InF_Read_Data(Pstr_ParaChange[i].OAD, pData + V_ucDataoff, &LenFor_Data, &V_usDataEncode);
					V_ucDataoff += LenFor_Data;
					if( Pstr_ParaChange[i].OAD == CMeter_Work_State7 )
					{
						memset(pData+V_ucDataoff, 0x00, 4);				/*密钥状态字补0,4字节*/
						V_ucDataoff += 4;
					}
				}
			}
			if( V_ucDataoff != 0 )
			{
				LenFor_Data = V_ucDataoff;
				if(V_ReturnData == C_OK)
				{
					Comm_11_03Response_Normal(pV_645Frame, pData, LenFor_Data);
					return;
				}
			}
		}
		else if( pV_645Frame->DI == C_IRAuth_Timer645 )
		{
			V_ReturnData = SF_Read_AuthTime(pV_645Frame->DI, pData, (uchar8 *)&LenFor_Data);
			if(V_ReturnData == C_OK)
			{
				Comm_11_03Response_Normal(pV_645Frame, pData, LenFor_Data);
			}
			else
			{
				Comm_Response_Set_ReadErr(C_OtherErr_645, pV_645Frame);
			}
			return;
		}
		else
		{
			for( i = 0; i < Pstr_ParaChange_Len; i++ )
			{
				if( ( pV_645Frame->DI == Pstr_ParaChange[i].DI ) && ( pV_645Frame->DI != 0x0400010C ) )
				{
					V_ReturnData = InF_Read_Data(Pstr_ParaChange[i].OAD, pData, &LenFor_Data, &V_usDataEncode);
					if( pV_645Frame->DI == 0x04000402)
					{
					  LenFor_Data = 6;
					}
					else if( ( pV_645Frame->DI == 0x04000106 ) || ( pV_645Frame->DI == 0x04000107 ) )
					{
						PF_CopyDataBytes(pData + 1, pData, LenFor_Data);
						LenFor_Data = 5;										/*YYMMDDHHmm*/
					}
					else if(pV_645Frame->DI == CSoftw_Record_Number_645)		/*协议数据格式不同，698ASCII码*/
					{
						V_ReturnData = SF_ASCIItoChar(pData, (uchar8 *)&LenFor_Data);
						if(V_ReturnData != C_OK)
						{
						   Comm_Response_Set_ReadErr(C_OtherErr_645, pV_645Frame);
						}
					}
					else if( ( pV_645Frame->DI == COne485_Baud_645 )        /*通信口1*/
						   || ( pV_645Frame->DI == CTwo485_Baud_645 ) )     /*通信口2*/
					{
						uchar8 bps;
						LenFor_Data = CLOne485_Baud_645;            /*645通信口特征字长度*/
						bps = SF_BPS698transfor645(pData[0]);             /*存储的是698格式改成645*/
						pData[0] = bps;
					}
					else if( ( pV_645Frame->DI == CMeter_Ac_Const645 ) || ( pV_645Frame->DI == CMeter_Re_Const645 ) )
					{
						LenFor_Data = CLMeter_Ac_Const645;
					}
					else if(pV_645Frame->DI == CMeter_Model645)
					{
						LenFor_Data = CLMeter_Model645;
						PF_CopyDataBytes( ( pData + ( CLMeter_Model - CLMeter_Model645 ) ), pData, LenFor_Data );
					}
					else if(pV_645Frame->DI == CProd_Date645)
					{
						LenFor_Data = CLProd_Date_YMDHM;
						V_ReturnData = SF_ChartoASCII( ( pData + 1 ), (uchar8 *)&LenFor_Data );	/*去掉年20和秒*/
						PF_CopyDataBytes( ( pData + 1 ), pData, LenFor_Data );
						if(V_ReturnData != C_OK)
						{
						   Comm_Response_Set_ReadErr(C_OtherErr_645, pV_645Frame);
						}
					}
					else if(pV_645Frame->DI == COverCurr_Curr_LowLim_645)
					{
						LenFor_Data = CLOverCurr_Curr_LowLim645;
						PF_Buffer4ToUlong32(pData, &V_ulData, CLOverCurr_Curr_LowLim);
						V_ulData = V_ulData >> 12;												/*698为4位小数，645为1位小数*/
						PF_Ulong32ToBuffer4(pData, &V_ulData, CLOverCurr_Curr_LowLim);
					}
					else
					{
						for(j = 0; j < C_TB_EventDelayTime_Len; j++)							/*事件延时参数*/
						{
							if(Pstr_ParaChange[i].OAD == TB_EventDelayTime[j])
							{
								PF_Buffer4ToUlong32(pData, &V_ulData, CLLossVolage_Delay_T);
								LenFor_Data = CLLossVolage_Delay_T;
								PF_HextoBCDBytes(&V_ulData, pData, (uchar8 *)&LenFor_Data);
								break;
							}
						}
					}
					if(V_ReturnData == C_OK)
					{
						Comm_11_03Response_Normal(pV_645Frame, pData, LenFor_Data);
						return;
					}
					break;
				}
			}
		}
	}
	if(pV_645Frame->DI == 0x0400010C)
	{
		V_ReturnData = InF_Read_Data(CTime, pData, &LenFor_Data, &V_usDataEncode);
		V_ucDataoff += LenFor_Data;
		LenFor_Data = CLDate_Week;
		V_ReturnData = InF_Read_Data(CDate_Week, pData + V_ucDataoff, &LenFor_Data, &V_usDataEncode);
		V_ucDataoff += LenFor_Data;
		LenFor_Data = V_ucDataoff;
	}
    else
    {
		if( ( ( pV_645Frame->DI & 0xFFFFFF00 ) == 0x04000A00 )						/*负荷记录起始或间隔时间*/
		 || ( ( pV_645Frame->DI & 0xFFFFFF00 ) == 0x04001200 ) )
		{
			V_ReturnData = C_IDError;
		}
		else
		{
			if( ( pV_645Frame->DI == CID_Auth_Remain_Time_645 ) || ( pV_645Frame->DI == CInfra_Auth_Remain_Time_645 ) )
			{
				V_ReturnData = SF_Read_AuthTime(pV_645Frame->DI, pData, (uchar8 *)&LenFor_Data);
			}
			else
			{
				for(V_uck = 0; V_uck < CL_TB_SetParmInFactoryState; V_uck++)
				{
					if(pV_645Frame->DI == TB_SetParmInFactoryState[V_uck].ParmDI_645)
					{
						pV_645Frame->DI = TB_SetParmInFactoryState[V_uck].ParmDI;		/*把三相配置参数转成698标志码*/
						LenFor_Data = TB_SetParmInFactoryState[V_uck].ParmLen;

						V_ReturnData = InF_Read_Data(pV_645Frame->DI, pData, &LenFor_Data, &V_usDataEncode);
						SF_InFactoryExchangeBCD( V_uck, pData );						/*有5个数据做BCD和HEX的转换*/
						break;
					}
				}
			}
		}
    }
	if(V_ReturnData == C_IDError)
	{/*无此标识码*/
		Comm_Response_Set_ReadErr(C_No_Request_data_645, pV_645Frame);
	}
	else if(V_ReturnData != C_OK)
	{/*其他类型错误，一律应答其他错误*/
		Comm_Response_Set_ReadErr(C_OtherErr_645, pV_645Frame);
	}
	else
	{
		Comm_11_03Response_Normal(pV_645Frame, pData, LenFor_Data);
		if(pV_645Frame->DI == CInset_Card_State)
		{
			InF_WriteCardStatus(C_CardStatusUnknow);
		}
	}
}

/***************************************************************************
函数原型 	Comm_ReadFreezeReg_11
函数功能	11命令读取时区表，时段表数据
输入参数	*pV_645Frame				:收到的命令帧
			LimitDI						:限制DI，即年时区数(04000201)或日时段数(04000203)
输出参数 	无
返回参数	无
全局变量 	和通道相关的全局变量
函数备注	进入本函数，DI3肯定等于05
***************************************************************************/
void	Comm_Read_TZone_PTReg(Str_Comm_645 *pV_645Frame, ulong32	LimitDI)
{
	uchar8	buf_O_CanWrite = 0;								/*缓冲区可写数据的偏移	*/
	uchar8	*pData;
	uchar8	V_ReturnData;
	uchar8	LimintData;
	ushort16	LenFor_Data, DataLen = 1, V_usDataEncode;	/*缓冲区可被写的总的长度*/
    uchar8 i;
    ulong32 V_ulDI;

/*645标识码转换为698标识码（数据层存储为698标识码）*/
	for(i = 0; i < Pstr_ParaChange_TZone_Len; i++ )
	{
		if(pV_645Frame->DI == Pstr_ParaChange_TZone[i].DI)
		{
			V_ulDI = Pstr_ParaChange_TZone[i].OAD;
			break;
		}
	}
   if(i == Pstr_ParaChange_TZone_Len)/*不可能*/
   {
     return;
   }

/*读取年时区数或日时段数。1字节。错误默认14个*/
	V_ReturnData = InF_Read_Data(LimitDI, &LimintData, &DataLen, &V_usDataEncode);
	if(V_ReturnData != C_OK)
	{
		LimintData = 14;
	}
	else
	{
		LimintData = PF_BCDtoHexOneByte(LimintData);
		if(LimintData > 14)
		{
			LimintData = 14;
		}
	}

	/*注意pData不包含DI数据*/
	pData = &pV_645Frame->Data[C_11_SData];
	LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - buf_O_CanWrite ;

	V_ReturnData = InF_Read_Data(V_ulDI, pData, &LenFor_Data, &V_usDataEncode);
	if(V_ReturnData == C_IDError)
	{/*无此标识码*/
		Comm_Response_Set_ReadErr(C_No_Request_data, pV_645Frame);
	}
	else if(V_ReturnData != C_OK)
	{/*其他类型错误，一律应答其他错误*/
		Comm_Response_Set_ReadErr(C_OtherErr, pV_645Frame);
	}
	else
	{
		Comm_11_03Response_Normal(pV_645Frame, pData,( LimintData * 3 ) );
	}
}
/*******************************************************************************
函数原型：uchar8 SF_ReadDFreeze(ulong32 V_Data_Id, uchar8 * P_Data, uchar8 *P_Data_Length)
功能描述：
输入参数：
输出参数：
返回参数：
调用位置：
备    注：
*******************************************************************************/
uchar8 SF_ReadDFreeze(ulong32 V_Data_Id, uchar8 * P_Data, uchar8 *P_Data_Length)
{
    ulong32  p_datacode[4] = {0x50040200, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
    uchar8   V_TimeZone[2], V_SaveFreezeTimeBuf[6];
    ushort16 V_usReadRecordNum = 0, LenFor_Data = CLD_Free_Pos_Ac_De_1, V_645Len = 0;
    uchar8   TB_SubDI_LineNo, V_ReturnData = C_OtherErr_645;
	uchar8   V_ucData_Temp[(C_MaxRatesNum + 1) * CLPos_Ac_Tol_De_0] = {0};

/*这里增加缓存定义，因为在698中最大费率数可以设置为12，*/
/*如果按照645总及费率电能集合的长度定义缓存底层读取数据会出现缓存不够的情况*/
    if( ( V_Data_Id & 0x0000FF00 ) != 0x0000FF00 )			/*外面已经判过块了，只有分相会到这里*/
    {
        for(TB_SubDI_LineNo = 0; TB_SubDI_LineNo < Str_698To645DFreezRead_Len; TB_SubDI_LineNo++ )
        {
            if( ( V_Data_Id & 0xFFFFFF00 ) == (Str_698To645DFreezRead[TB_SubDI_LineNo].V_ulDataId645 & 0xFFFFFF00 ) )
            {
                p_datacode[1] = Str_698To645DFreezRead[TB_SubDI_LineNo].V_ulDataId698;
                if(Str_698To645DFreezRead[TB_SubDI_LineNo].V_ulDataId698 == CInstantFF_AcPow)
                {
                    p_datacode[2] = Str_698To645DFreezRead[TB_SubDI_LineNo].V_ulDataId698 + 0x00010000;
                }
                V_645Len = Str_698To645DFreezRead[TB_SubDI_LineNo].V_ucDataLen;
                break;
            }
        }
        if(TB_SubDI_LineNo == Str_698To645DFreezRead_Len)
        {
            V_ReturnData = C_IDError;
        }
        else
        {
            p_datacode[0] |= ((V_Data_Id)&0x000000FF);
			LenFor_Data = sizeof(V_ucData_Temp);
            V_ReturnData = InF_ReadFreezeData(p_datacode,V_TimeZone, V_ucData_Temp, &V_usReadRecordNum, &LenFor_Data, 15, V_SaveFreezeTimeBuf, C_698EarLoadMode);
            if(V_ReturnData == C_OK)
            {
				if(p_datacode[1] == CFreeTime)
            	{
					memcpy(P_Data, V_ucData_Temp + 1, CLFreeTime_645);
              		LenFor_Data = CLFreeTime_645;
				}
				else if( (p_datacode[1] & 0xFF000000) == 0x00000000)
				{
					if( (p_datacode[1] & 0x000000FF) == 0x00000000)
					{
						if(LenFor_Data < CLPos_Ac_En_FF_1 )		/*预防费率数<4情况*/
						{
							memset(&V_ucData_Temp[LenFor_Data], 0x00, (CLPos_Ac_En_FF_1 - LenFor_Data));
						}
				 		LenFor_Data = CLPos_Ac_En_FF_1;			/*对于电能集合，645读取只取总及前4个费率电能*/
				 	}
					SF_EnergyT0_645(V_ucData_Temp, P_Data, &LenFor_Data, 4, (uchar8)(p_datacode[1]>>16) );
				}
				else if( ( ( p_datacode[1] & 0xFF000000 ) == 0x10000000 ) )
				{
					if( ( p_datacode[1] & 0x000000FF ) == 0x00000000 )
					{
						if( LenFor_Data < CLPos_Ac_De_FF_0_4Rate )		/*预防费率数<4情况*/
						{
							memset(&V_ucData_Temp[LenFor_Data], 0x00, ( CLPos_Ac_De_FF_0_4Rate - LenFor_Data ) );
						}
				 		LenFor_Data = CLPos_Ac_De_FF_0_4Rate;			/*对于需量集合，645读取只取总及前4个费率电能*/
				 	}
				  	memcpy(P_Data, V_ucData_Temp, LenFor_Data);
				}
				else
				{
				  	memcpy(P_Data, V_ucData_Temp, LenFor_Data);
				}
            }
            if(V_ReturnData != C_OK)									/*无此项数据时，关联列表没有设置，导致查找不到*/
            {
              LenFor_Data = V_645Len;
              memset(P_Data, 0x00, V_645Len);
              V_ReturnData = C_OK;
            }
            PF_Ushort16ToBuffer2(P_Data_Length, &LenFor_Data);
        }
    }
    return V_ReturnData;
}
/*******************************************************************************
函数原型：uchar8 SF_ReadHFreeze(ulong32 V_Data_Id, uchar8 * P_Data, uchar8 *P_Data_Length)
功能描述：小时冻结事件记录
输入参数：
输出参数：
返回参数：
调用位置：
备    注：
*******************************************************************************/
uchar8 SF_ReadHFreeze(ulong32 V_Data_Id, uchar8 * P_Data, uchar8 *P_Data_Length)
{
    ulong32  p_datacode[4] = {0x50030200, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
    uchar8   V_TimeZone[2], V_SaveFreezeTimeBuf[6];
    ushort16 V_usReadRecordNum = 0, LenFor_Data = CLFreeTime, V_645Len = 0;
    uchar8   TB_SubDI_LineNo, V_ReturnData = C_OtherErr_645;

    if( ( V_Data_Id & 0x0000FF00) != 0x0000FF00)			/*外面已经判过块了，只有分相会到这里*/
    {
        for(TB_SubDI_LineNo = 0; TB_SubDI_LineNo < Str_698To645HFreezRead_Len; TB_SubDI_LineNo++)
        {
            if( ( V_Data_Id & 0xFFFFFF00 ) == ( Str_698To645HFreezRead[TB_SubDI_LineNo].V_ulDataId645 & 0xFFFFFF00 ) )
            {
                p_datacode[1] = Str_698To645HFreezRead[TB_SubDI_LineNo].V_ulDataId698;
                V_645Len = Str_698To645HFreezRead[TB_SubDI_LineNo].V_ucDataLen;
                break;
            }
        }
        if(TB_SubDI_LineNo == Str_698To645HFreezRead_Len)
        {
            V_ReturnData = C_IDError;
        }
        else
        {
            p_datacode[0] |= ( (V_Data_Id) & 0x000000FF );
            V_ReturnData = InF_ReadFreezeData(p_datacode,V_TimeZone, P_Data, &V_usReadRecordNum, &LenFor_Data, 15,V_SaveFreezeTimeBuf, C_698EarLoadMode);
            if( ( V_ReturnData == C_OK ) && ( p_datacode[1] == CFreeTime ) )
            {
                memcpy(P_Data, P_Data + 1, CLFreeTime_645);
                LenFor_Data = CLFreeTime_645;
            }
			else
			{
				SF_EnergyT0_645(P_Data, P_Data, &LenFor_Data, 4, (uchar8)(p_datacode[1] >> 16) );
			}
            if(V_ReturnData != C_OK)
            {
                LenFor_Data = V_645Len;
                memset(P_Data, 0x00, V_645Len);
                V_ReturnData = C_OK;
            }
            PF_Ushort16ToBuffer2(P_Data_Length, &LenFor_Data);
        }
    }
    return V_ReturnData;
}
/****************************************************************************
*函数原型 	Comm_ReadFreezeReg_11
*函数功能	11命令读取冻结类寄存器
*输入参数	*pV_645Frame				:收到的命令帧
*输出参数 	无
*返回参数	无
*全局变量 	和通道相关的全局变量
*函数备注	进入本函数，DI3肯定等于05
****************************************************************************/
void		Comm_ReadFreezeReg_11(Str_Comm_645 *pV_645Frame)
{
	uchar8	buf_O_CanWrite = 0;					/*缓冲区可写数据的偏移*/
	ushort16	LenFor_Data, V_usDataEncode;						/*缓冲区可被写的总的长度*/
	uchar8	*pData;
	uchar8	V_ReturnData;
	ulong32	ReadDI;
	Str_Comm_NxtFrame NxtFrame;
	Str_Comm_NxtFrame *pNxtFrame;				/*后续帧保留数据*/
	uchar8	TB_NxtFrame_LineNo;					/* 1级表行号*/
	ulong32	*pTB_SubDI;							/*分帧标识码数据*/

	/*获取通道后续帧变量*/
	pNxtFrame = &NxtFrame;
	if( Get_SV_CommNxtFrame(pV_645Frame->ChannelNo, pNxtFrame) != C_OK )
	{
		return;			/*出错，什么都不处理。*/
	}
	/*注意pData不包含DI数据*/
	pData = &pV_645Frame->Data[C_11_SData];
	LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - buf_O_CanWrite ;

	/*判断DI=0，读次数，直接读*/
	if(pV_645Frame->Data[C_O_DI0] == 0)
	{
		V_ReturnData = InF_Read_Data(pV_645Frame->DI, &pData[buf_O_CanWrite], &LenFor_Data, &V_usDataEncode);
		if(V_ReturnData == C_OK)
		{
			Comm_11_03Response_Normal(pV_645Frame, pData, LenFor_Data);
		}
		else if(V_ReturnData == C_IDError)
		{
			Comm_Response_Set_ReadErr(C_No_Request_data_645, pV_645Frame);
		}
		else
		{
			Comm_Response_Set_ReadErr(C_OtherErr_645, pV_645Frame);
		}
		return;
	}
/*判断DI1 != 0xFF，表示分项冻结数据读，不存在分帧问题*/
	if(pV_645Frame->Data[C_O_DI1] != 0xFF)
	{
		if(IsFreezeDataEnableRead(pV_645Frame->DI) != C_OK)
		{
			Comm_Response_Set_ReadErr(C_No_Request_data_645, pV_645Frame);
			return;
		}
        if( ( ( pV_645Frame->DI ) & 0xFFFF0000 ) == CD_Free_Degree )
        {
            V_ReturnData = SF_ReadDFreeze(pV_645Frame->DI, &pData[buf_O_CanWrite], (uchar8 *)&LenFor_Data);
        }
        else if( ( ( pV_645Frame->DI ) & 0xFFFF0000 ) == CH_Free_Degree )
        {
            V_ReturnData = SF_ReadHFreeze(pV_645Frame->DI, &pData[buf_O_CanWrite], (uchar8 *)&LenFor_Data);
        }
        else
        {
			V_ReturnData = InF_Read_Data(pV_645Frame->DI, &pData[buf_O_CanWrite], &LenFor_Data, &V_usDataEncode);
        }
		if(V_ReturnData == C_OK)
		{
			Comm_11_03Response_Normal(pV_645Frame, pData, LenFor_Data);
		}
		else if(V_ReturnData == C_IDError)
		{
			Comm_Response_Set_ReadErr(C_No_Request_data_645, pV_645Frame);
		}
		else
		{
			Comm_Response_Set_ReadErr(C_OtherErr_645, pV_645Frame);
		}
		return;
	}

/*DI1 == 0xFF，集合*/
/*目前仅定时、约定、整点、日冻结会有集合，所以DI2不可呢 大于等于8*/
	if(pV_645Frame->Data[C_O_DI2] >= 0x08)
	{
		Comm_Response_Set_ReadErr(C_No_Request_data_645, pV_645Frame);
		return;
	}
/*判断集合的次数是否合理，本处采用该集合中冻结时间*/
/*调用IsFreezeDataEnableRead，判断模式字是否为全空和DI0次数是否正确*/
	if(IsFreezeDataEnableRead(pV_645Frame->DI & 0xFFFF00FF) != C_OK)
	{
		Comm_Response_Set_ReadErr(C_No_Request_data_645, pV_645Frame);
		return;
	}
/*到这里，DI3-0都是正确的。而且DI1=FF，读集合*/
/*首先查一级表,得到行号*/
	for( TB_NxtFrame_LineNo = 0; TB_NxtFrame_LineNo < C_TBNxtFrameNum; TB_NxtFrame_LineNo++ )
	{
		if( ( ( pV_645Frame->DI & 0xFFFFFF00 ) | 0x00000001 ) == TB_NxtFrame[TB_NxtFrame_LineNo].DataCode )
		{
			break;
		}
	}
	if(TB_NxtFrame_LineNo >= C_TBNxtFrameNum)
	{
		Comm_Response_Set_ReadErr(C_No_Request_data_645, pV_645Frame);
		return;
	}

	/*Set_SV_CommNxtFrame，置通道后续帧全局变量*/
	pTB_SubDI = TB_NxtFrame[TB_NxtFrame_LineNo].pTB_SubDI;

	pNxtFrame->DataCode = pV_645Frame->DI;
	pNxtFrame->FrameNo = 0;

	ReadDI = pTB_SubDI[0] & 0xFF00FF00;		/*DI2 和DI0采用总的。因为冻结分项表格不包含次数和类别*/
	pNxtFrame->Nxt_DataCode = (pV_645Frame->DI & 0x00FF00FF) | ReadDI;

	V_ReturnData = ReadFreezeReg_NxtFrame(pNxtFrame, pV_645Frame, TB_NxtFrame_LineNo);
	if(V_ReturnData == C_HaveNxtFrame)
	{
		Comm_IfHaveNxtFrame_Set_C(pV_645Frame);
		pNxtFrame->Sub_DataCode = pNxtFrame->Nxt_DataCode;
		pNxtFrame->FrameFinished = C_Error;						/*表示有后续帧*/
		pNxtFrame->HaveReport = C_Error;						/*表示未主动上报过*/
		pNxtFrame->FrameNo = 1;
		Set_SV_CommNxtFrame(pV_645Frame->ChannelNo, pNxtFrame);	/*11命令是不用加帧序号的。*/
	}
	else
	{
		Init_SV_CommNxtFrame(pV_645Frame->ChannelNo);
	}
}

/****************************************************************************
*函数原型 	ReadFreezeReg_NxtFrame
*函数功能	带后续帧变量读取冻结寄存器。注意：后续帧帧序号在外面置。这里只是置应答数据。
*输入参数	*pSV_CommNxtFrame		:后续帧变量
*				*pV_645Frame				:接收到的数据帧
*				TB_NxtFrame_LineNo		:1级表中的行号
*输出参数 	*pSV_CommNxtFrame.Nxt	:下一个数据分项标识码
*返回参数	C_NoNxtFrame/C_HaveNxtFrame
*全局变量
*函数备注	1）调用本函数之前，缓冲区其他位置没有赋值。
*				2）通道后续帧变量中，Nxt在本函数已置，但Sub及帧序号在外面置。
*				3）本函数对于次数DI0，及冻结类型DI2不进行合法性判断。
*					因为在11命令调用本函数前已经判断过，那么后续帧变量中的总的DI是正确的，12命令调用也无须再次判断。
****************************************************************************/
uchar8	ReadFreezeReg_NxtFrame (Str_Comm_NxtFrame *pSV_CommNxtFrame,Str_Comm_645 *pV_645Frame,uchar8 TB_NxtFrame_LineNo)
{
	uchar8	buf_O_CanWrite;						/*缓冲区可写数据的偏移  */
	ushort16	LenFor_Data;					/*缓冲区可被写的总的长度*/
	uchar8	*pData;
	uchar8	V_ReturnData;
	ulong32	*pTB_SubDI;							/* 2级表指针   */
	uchar8	TB_SubDI_LineNo;					/* 2级表行号   */
	uchar8	TB_SubDI_MaxLineNo;					/* 2级表中     */
	ulong32	ReadDI;
    ulong32 p_datacode[14];
	uchar8   V_TimeZone[12], V_645Len = 0;
	ushort16 V_usReadRecordNum;
	uchar8 V_SaveFreezeTimeBuf[C_SaveFreezeTimeBufLen];
/*查询一级表，获取2级表相关参数*/
	pTB_SubDI = TB_NxtFrame[TB_NxtFrame_LineNo].pTB_SubDI;
	TB_SubDI_MaxLineNo = TB_NxtFrame[TB_NxtFrame_LineNo].SubDINum;

    memset(p_datacode, 0xFF, 14 * 4);
/*循环查询2级表，确认2级表中首个分项标识码对应的2级表行号*/
	ReadDI = pSV_CommNxtFrame->Nxt_DataCode;
	for(TB_SubDI_LineNo = 0; TB_SubDI_LineNo < TB_SubDI_MaxLineNo; TB_SubDI_LineNo++ )
	{/*屏蔽DI2/DI0比较,因为冻结分项标识码表格不包括类别和次数*/
		if( ( ReadDI & 0xFF00FF00 ) == ( pTB_SubDI[TB_SubDI_LineNo] & 0xFF00FF00 ) )
		{
			break;
		}
	}
	if(TB_SubDI_LineNo >= TB_SubDI_MaxLineNo)
	{/*分项表格中找不到*/
		Comm_Response_Set_ReadErr(C_No_Request_data, pV_645Frame);
		return(C_NoNxtFrame);
	}
/*循环查询2级表的分项标识码，读数据层数据*/
	/*注意pData不包含DI数据*/
	buf_O_CanWrite = 0;
	pData = &pV_645Frame->Data[C_11_SData];
	LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - buf_O_CanWrite - 2;			/*扣去2的目的，最后可能要加上AA和帧序号*/

	for( ; TB_SubDI_LineNo < TB_SubDI_MaxLineNo; TB_SubDI_LineNo++ )
	{
	/*首先取分项标识码,DI2/DI0取总的标识码中的DI2/DI0*/
		ReadDI = pTB_SubDI[TB_SubDI_LineNo] & 0xFF00FF00;
		ReadDI = (pV_645Frame->DI & 0x00FF00FF) | ReadDI;
	/*判断剩余字节是否够写最后的帧序号*/
		if(LenFor_Data < 1)
		{
			break;																/*TB_SubDI_LineNo本行还没有判断*/
		}
	/*判断该分项标识码，模式字是否支持读	*/
		if(IsFreezeDataEnableRead(ReadDI) != C_OK)
		{/*该分项标识码不让读,冻结时间是肯定让读的。*/
			pData[buf_O_CanWrite] = 0xAA;
			buf_O_CanWrite++;
			if( buf_O_CanWrite >= ( C_Comm_Data_MaxLen - CLen_DI - 2 ) )
			{
				break;
			}
			LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - buf_O_CanWrite - 2;
			continue;
		}
	/*读数据层*/
	    /****************************************************/
	    if(((pV_645Frame->DI)&0xFFFF0000) == CD_Free_Degree)
	    {
            p_datacode[0] = 0x50040200|((pV_645Frame->DI)&0x000000FF);
            p_datacode[1] = Str_698To645DFreezRead[TB_SubDI_LineNo].V_ulDataId698;
            V_645Len = Str_698To645DFreezRead[TB_SubDI_LineNo].V_ucDataLen;
            if(Str_698To645DFreezRead[TB_SubDI_LineNo].V_ulDataId698 == CInstantFF_AcPow)
            {
                p_datacode[2] = Str_698To645DFreezRead[TB_SubDI_LineNo].V_ulDataId698 + 0x00010000;
            }
            if( LenFor_Data > V_645Len)
			{
				V_ReturnData = InF_ReadFreezeData(p_datacode,V_TimeZone, &pData[buf_O_CanWrite], &V_usReadRecordNum,&LenFor_Data, 15,V_SaveFreezeTimeBuf,C_698EarLoadMode);    /*************************用645的方法获取负荷连续抄读的起始、结束时间和块数***************************/
				if(V_ReturnData == C_OK)	/*只有读取数据正确才进行数据格式转换*/
				{
					if(Str_698To645DFreezRead[TB_SubDI_LineNo].V_ulDataId698 == CFreeTime)
					{
						LenFor_Data = CLFreeTime_645;
						memcpy(&pData[buf_O_CanWrite],&pData[buf_O_CanWrite]+1,LenFor_Data);
					}
					else if( (Str_698To645DFreezRead[TB_SubDI_LineNo].V_ulDataId698 & 0xFF000000) == 0x00000000)
					{
						if( (p_datacode[1]&0x000000FF) == 0x00000000)
						{
							if(LenFor_Data < CLPos_Ac_En_FF_1 )		/*预防费率数<4情况*/
							{
								memset(&pData[buf_O_CanWrite + LenFor_Data], 0x00, (CLPos_Ac_En_FF_1 - LenFor_Data));
							}

							LenFor_Data = CLPos_Ac_En_FF_1;			/*对于电能集合，645读取只取总及前4个费率电能*/
						}
						SF_EnergyT0_645(&pData[buf_O_CanWrite], &pData[buf_O_CanWrite], &LenFor_Data, 4, (uchar8)(Str_698To645DFreezRead[TB_SubDI_LineNo].V_ulDataId698>>16));
					}
					else if(( (p_datacode[1] & 0xFF000000) == 0x10000000) )
					{
						if( (p_datacode[1]&0x000000FF) == 0x00000000)
						{
							if(LenFor_Data < CLPos_Ac_De_FF_0_4Rate )	/*预防费率数<4情况*/
							{
								memset(&pData[buf_O_CanWrite + LenFor_Data], 0x00, (CLPos_Ac_De_FF_0_4Rate - LenFor_Data));
							}

							LenFor_Data = CLPos_Ac_De_FF_0_4Rate;				/*对于需量集合，645读取只取总及前4个费率电能*/
						}
					}
				}
			}
			else
			{
				V_ReturnData = C_DataLenError;
			}
	    }
	    else if(((pV_645Frame->DI)&0xFFFF0000) == CH_Free_Degree)
	    {
            p_datacode[0] = 0x50030200|((pV_645Frame->DI)&0x000000FF);
            p_datacode[1] = Str_698To645HFreezRead[TB_SubDI_LineNo].V_ulDataId698;
            V_645Len = Str_698To645HFreezRead[TB_SubDI_LineNo].V_ucDataLen;

            V_ReturnData = InF_ReadFreezeData(p_datacode,V_TimeZone, &pData[buf_O_CanWrite], &V_usReadRecordNum,&LenFor_Data, 15,V_SaveFreezeTimeBuf,C_698EarLoadMode);    /*************************用645的方法获取负荷连续抄读的起始、结束时间和块数***************************/
            if(Str_698To645HFreezRead[TB_SubDI_LineNo].V_ulDataId698 == CFreeTime)
            {
                LenFor_Data = CLFreeTime_645;
                memcpy(&pData[buf_O_CanWrite],&pData[buf_O_CanWrite]+1,LenFor_Data);
            }
			else if( (Str_698To645DFreezRead[TB_SubDI_LineNo].V_ulDataId698 & 0xFF000000) == 0x00000000)
			{
				SF_EnergyT0_645(&pData[buf_O_CanWrite], &pData[buf_O_CanWrite], &LenFor_Data, 4, (uchar8)(Str_698To645DFreezRead[TB_SubDI_LineNo].V_ulDataId698>>16));
			}
	    }
	    else
	    {
	    	V_ReturnData = C_IDError;
	    }
        if(V_ReturnData == C_NoData)
        {
            if(LenFor_Data >= V_645Len)
            {
                LenFor_Data = V_645Len;
                memset(&pData[buf_O_CanWrite], 0x00, V_645Len);
                V_ReturnData = C_OK;
            }
            else
            {
                V_ReturnData = C_DataLenError;
            }
        }
		if(V_ReturnData == C_IDError)
		{/*无此标识码，应答无请求数据退出.不可能到这里的!*/
			Comm_Response_Set_ReadErr(C_No_Request_data, pV_645Frame);
			return(C_NoNxtFrame);
		}
		/*长度不够，退出循环*/
		if(V_ReturnData == C_DataLenError)
		{
			break;
		}
		/*其他不是OK，是不可能的，因此应答其他错误退出*/
		if(V_ReturnData != C_OK)
		{
			Comm_Response_Set_ReadErr(C_OtherErr, pV_645Frame);
			return(C_NoNxtFrame);
		}
		/*OK，读出的数据认可*/
		buf_O_CanWrite = buf_O_CanWrite + LenFor_Data;
		pData[buf_O_CanWrite] = 0xAA;
		buf_O_CanWrite++;

		if(buf_O_CanWrite >= (C_Comm_Data_MaxLen - CLen_DI - 2))
		{/*不可能到这里。*/
			break;
		}
		LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - buf_O_CanWrite - 2;
	}
/*组织应答帧*/
	Comm_11_03Response_Normal(pV_645Frame, pData, buf_O_CanWrite);
/*是否有后续帧的判断*/
	if(TB_SubDI_LineNo >= TB_SubDI_MaxLineNo)
	{/*到分项标识码表格最后，表明后面无数据了*/
		return(C_NoNxtFrame);
	}

	for( ; TB_SubDI_LineNo < TB_SubDI_MaxLineNo; TB_SubDI_LineNo++ )
	{
		ReadDI = pTB_SubDI[TB_SubDI_LineNo] & 0xFF00FF00;
		ReadDI = (pV_645Frame->DI &0x00FF00FF) | ReadDI;
		pSV_CommNxtFrame->Nxt_DataCode = ReadDI;
		if(IsFreezeDataEnableRead(ReadDI) == C_OK)
		{
			return(C_HaveNxtFrame);	/*后面只要有1个分项标识码允许读，就有后续帧*/
		}
	}
	return(C_NoNxtFrame);
}

/***************************************************************************
函数原型 	ReadProgRecordReg_NxtFrame
函数功能	带后续帧变量读取编程事件记录。注意：后续帧帧序号在外面置。这里只是置应答数据。
输入参数	*pSV_CommNxtFrame		:后续帧变量
				*pV_645Frame				:接收到的数据帧
				TB_NxtFrame_LineNo		:1级表中的行号
输出参数 	*pSV_CommNxtFrame.Nxt	:下一个数据分项标识码
返回参数	C_NoNxtFrame/C_HaveNxtFrame
全局变量
函数备注	1）调用本函数之前，缓冲区其他位置没有赋值。
				2）通道后续帧变量中，Nxt在本函数已置，但Sub及帧序号在外面置。
				3）本函数对于次数DI0，及冻结类型DI2不进行合法性判断。
					因为在11命令调用本函数前已经判断过，那么后续帧变量中的总的DI是正确的，12命令调用也无须再次判断。
				4)	此处次数是DI0的低4位，肯定小于0x0A
***************************************************************************/
uchar8 ReadProgRecordReg_NxtFrame (Str_Comm_NxtFrame *pSV_CommNxtFrame, Str_Comm_645 *pV_645Frame, uchar8 TB_NxtFrame_LineNo)
{
	uchar8	buf_O_CanWrite;						/*缓冲区可写数据的偏移*/
	ushort16	LenFor_Data, V_usDataEncode;							/*缓冲区可被写的总的长度*/
	uchar8	*pData;
	uchar8	V_ReturnData;

	ulong32	*pTB_SubDI;						/* 2级表指针*/
	uchar8	TB_SubDI_LineNo;					/* 2级表行号*/
	uchar8	TB_SubDI_MaxLineNo;					/* 2级表中*/

	ulong32	ReadDI;

/*查询一级表，获取2级表相关参数*/
	pTB_SubDI = TB_NxtFrame[TB_NxtFrame_LineNo].pTB_SubDI;
	TB_SubDI_MaxLineNo = TB_NxtFrame[TB_NxtFrame_LineNo].SubDINum;

/*循环查询2级表，确认2级表中首个分项标识码对应的2级表行号*/
	ReadDI = pSV_CommNxtFrame->Nxt_DataCode;
	for( TB_SubDI_LineNo = 0; TB_SubDI_LineNo < TB_SubDI_MaxLineNo; TB_SubDI_LineNo++ )
	{/*屏蔽DI0低4位比较,因为分项标识码表格不包括次数*/
		if( ( ReadDI & 0xFFFFFFF0 ) == ( pTB_SubDI[TB_SubDI_LineNo] & 0xFFFFFFF0 ) )
		{
			break;
		}
	}
	if(TB_SubDI_LineNo >= TB_SubDI_MaxLineNo)
	{/*分项表格中找不到*/
		Comm_Response_Set_ReadErr(C_No_Request_data, pV_645Frame);
		return(C_NoNxtFrame);
	}
/*循环查询2级表的分项标识码，读数据层数据*/
	/*注意pData不包含DI数据*/
	buf_O_CanWrite = 0;
	pData = &pV_645Frame->Data[C_11_SData];
	LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - buf_O_CanWrite - 1;	/*扣去1的目的，最后可能要帧序号*/

	for( ;TB_SubDI_LineNo < TB_SubDI_MaxLineNo; TB_SubDI_LineNo++ )
	{
	/*首先取分项标识码,DI2/DI0取总的标识码中的DI2/DI0*/
		ReadDI = pTB_SubDI[TB_SubDI_LineNo] & 0xFFFFFFF0;
		ReadDI = (pV_645Frame->DI &0x0000000F) | ReadDI;
		pSV_CommNxtFrame->Nxt_DataCode = ReadDI;				/*留待下一帧读*/
	/*判断剩余字节是否够写最后的帧序号*/
		if(LenFor_Data < 1)
		{
			break;						/*TB_SubDI_LineNo本行还没有判断*/
		}
	/*读数据层*/
		if( ( ReadDI & 0xFFFFFF00 ) == CDe_Clear_Degree )
		{
			V_ReturnData = SF_Read_DemandEvent(ReadDI, pV_645Frame->Data[C_O_DI0], &pData[buf_O_CanWrite], (uchar8 *)&LenFor_Data);
		}
		else
		{
			V_ReturnData = InF_Read_Data(ReadDI, &pData[buf_O_CanWrite], &LenFor_Data, &V_usDataEncode);
		}
		if(V_ReturnData == C_IDError)
		{/*无此标识码，应答无请求数据退出.不可能到这里的!*/
			Comm_Response_Set_ReadErr(C_No_Request_data, pV_645Frame);
			return(C_NoNxtFrame);
		}
	/*长度不够，退出循环*/
		if(V_ReturnData == C_DataLenError)
		{
			break;
		}
	/*其他不是OK，是不可能的，因此应答其他错误退出*/
		if(V_ReturnData != C_OK)
		{
			Comm_Response_Set_ReadErr(C_OtherErr, pV_645Frame);
			return(C_NoNxtFrame);
		}
	/*OK，读出的数据认可*/
		buf_O_CanWrite = buf_O_CanWrite + LenFor_Data;

		if( buf_O_CanWrite >= ( C_Comm_Data_MaxLen - CLen_DI - 1 ) )
		{/*不可能到这里。*/
			break;
		}
		LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - buf_O_CanWrite - 1;
	}

/*组织应答帧*/
	Comm_11_03Response_Normal(pV_645Frame, pData, buf_O_CanWrite);

	/*是否有后续帧的判断*/
	if(TB_SubDI_LineNo >= TB_SubDI_MaxLineNo)
	{/*到分项标识码表格最后，表明后面无数据了*/
		return(C_NoNxtFrame);
	}
	else
	{
		return(C_HaveNxtFrame);
	}
}

/***************************************************************************
函数原型  uchar8 ReadCurrFFRecordReg_NxtFrame (Str_Comm_NxtFrame *pSV_CommNxtFrame,Str_Comm_645 *pV_645Frame,uchar8 TB_NxtFrame_LineNo)
函数功能	  带后续帧变量读取编程事件记录。注意：后续帧帧序号在外面置。这里只是置应答数据。
输入参数   *pSV_CommNxtFrame:后续帧变量
		  *pV_645Frame:接收到的数据帧
		  TB_NxtFrame_LineNo:1级表中的行号
输出参数   *pSV_CommNxtFrame.Nxt:下一个数据分项标识码
返回参数   C_NoNxtFrame/C_HaveNxtFrame
全局变量
函数备注	1）调用本函数之前，缓冲区其他位置没有赋值。
		2）通道后续帧变量中，Nxt在本函数已置，但Sub及帧序号在外面置。
		3）本函数对于DI0及DI2不进行合法性判断。
		因为在11命令调用本函数前已经判断过，那么后续帧变量中的总的DI是正确的，12命令调用也无须再次判断。
            只支持过流、失流事件。
***************************************************************************/
uchar8 ReadCurrFFRecordReg_NxtFrame (Str_Comm_NxtFrame *pSV_CommNxtFrame, Str_Comm_645 *pV_645Frame, uchar8 TB_NxtFrame_LineNo)
{
	uchar8	buf_O_CanWrite;		/*缓冲区可写数据的偏移*/
	uchar8	LenFor_Data;		/*缓冲区可被写的总的长度*/
	uchar8	*pData;
	uchar8	V_ReturnData;
	ulong32	*pTB_SubDI;			/* 2级表指针*/
	uchar8	TB_SubDI_LineNo;	/* 2级表行号*/
	uchar8	TB_SubDI_MaxLineNo;	/* 2级表中*/
	ulong32	ReadDI;

/*查询一级表，获取2级表相关参数*/
	pTB_SubDI = TB_NxtFrame[TB_NxtFrame_LineNo].pTB_SubDI;
	TB_SubDI_MaxLineNo = TB_NxtFrame[TB_NxtFrame_LineNo].SubDINum;

/*循环查询2级表，确认2级表中首个分项标识码对应的2级表行号*/
	ReadDI = pSV_CommNxtFrame->Nxt_DataCode;
	for(TB_SubDI_LineNo = 0; TB_SubDI_LineNo < TB_SubDI_MaxLineNo; TB_SubDI_LineNo++ )
	{
		if( ReadDI == (pTB_SubDI[TB_SubDI_LineNo]))
		{
			break;
		}
	}
	if(TB_SubDI_LineNo >= TB_SubDI_MaxLineNo)
	{/*分项表格中找不到*/
		Comm_Response_Set_ReadErr(C_No_Request_data, pV_645Frame);
		return(C_NoNxtFrame);
	}
/*循环查询2级表的分项标识码，读数据层数据*/
	/*注意pData不包含DI数据*/
	buf_O_CanWrite = 0;
	pData = &pV_645Frame->Data[C_11_SData];
	LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - buf_O_CanWrite - 1;	/*扣去1的目的，最后可能要帧序号*/

	for( ; TB_SubDI_LineNo < TB_SubDI_MaxLineNo; TB_SubDI_LineNo++ )
	{
		/*首先取分项标识码,DI2/DI0取总的标识码中的DI2/DI0*/
			ReadDI = pTB_SubDI[TB_SubDI_LineNo] ;
			pSV_CommNxtFrame->Nxt_DataCode = ReadDI;					/*留待下一帧读*/
		/*判断剩余字节是否够写最后的帧序号*/
			if(LenFor_Data < 1)
			{
				break;					        						/*TB_SubDI_LineNo本行还没有判断*/
			}
		/*读数据层*/
             V_ReturnData = SF_ReadCurrEventFF_645(ReadDI, &pData[buf_O_CanWrite], &LenFor_Data);
             if(V_ReturnData == C_OK)
             {
                 pData[buf_O_CanWrite + LenFor_Data] = 0xAA;    		/*数据集补AA*/
                 LenFor_Data += CL_EventFF_AALen;
             }
			if(V_ReturnData == C_IDError)
			{/*无此标识码，应答无请求数据退出.不可能到这里的!*/
				Comm_Response_Set_ReadErr(C_No_Request_data, pV_645Frame);
				return(C_NoNxtFrame);
			}
		/*长度不够，退出循环*/
			if(V_ReturnData == C_DataLenError)
			{
				break;
			}
		/*其他不是OK，是不可能的，因此应答其他错误退出*/
			if(V_ReturnData != C_OK)
			{
				Comm_Response_Set_ReadErr(C_OtherErr, pV_645Frame);
				return(C_NoNxtFrame);
			}
		/*OK，读出的数据认可*/
			buf_O_CanWrite = buf_O_CanWrite + LenFor_Data;

			if(buf_O_CanWrite >= (C_Comm_Data_MaxLen - CLen_DI - 1))
			{/*不可能到这里。*/
				break;
			}
			LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - buf_O_CanWrite - 1;
		}

/*组织应答帧*/
	Comm_11_03Response_Normal(pV_645Frame, pData, buf_O_CanWrite);

/*是否有后续帧的判断*/
	if(TB_SubDI_LineNo >= TB_SubDI_MaxLineNo)
	{/*到分项标识码表格最后，表明后面无数据了*/
		return(C_NoNxtFrame);
	}
	else
	{
		return(C_HaveNxtFrame);
	}
}
/***************************************************************************
函数原型 	IsFreezeDataEnableRead
函数功能	确定该标识码（非集合数据项）是否允许读。
输入参数	DataCode			:数据项标识码
输出参数 	无
返回参数	C_OK/C_Error
全局变量
函数备注	1）仅支持分项标识码，不支持集合。
				2）剩余金额日冻结直接返回允许读。
				3）如果模式字为0，则读冻结时间也不允许。
				4)	同时判断分项标识码次数是否合理。
				5)	除DI1外其他都判断了。DI1就不进行判断了，因为数据层会返回C_IDError，就不单独判断了。
***************************************************************************/
uchar8		IsFreezeDataEnableRead (ulong32 DataCode)
{
	uchar8	DefaultFreezeMode;
	uchar8	FreezeMode;
	uchar8	DI0Range;

/*判断输入参数是否为DI1=0xFF集合，是则应答错误*/
	if((DataCode & 0x0000FF00) == 0x0000FF00)
	{
		return(C_Error);
	}
/*根据输入参数确定该类冻结模式字的DI*/
	switch(DataCode & 0xFFFF0000)
	{
		case		0x05000000:			/*定时冻结*/
			DefaultFreezeMode = 0xFF;	/*默认全允许读*/
			DI0Range = 0x3C;			/*定时冻结只允许读上1-上60*/
			break;
		case		0x05010000:			/*瞬时冻结*/
			DefaultFreezeMode = 0xFF;	/*默认全允许读*/
			DI0Range = 0x03;			/*瞬时冻结只允许读上1-上3*/
			break;
		case		0x05020000:			/*约定冻结*/
		case		0x05030000:
		case		0x05050000:
		case		0x05070000:
			DefaultFreezeMode = 0xFF;	/*默认全允许读*/
			DI0Range = 0x02;			/*约定冻结是2次*/
			break;
		case		0x05040000:			/*整点冻结*/
			DefaultFreezeMode = 0x03;	/*默认全允许读*/
			DI0Range = 0xFE;			/*整点冻结只允许读上1-上254*/
			break;
		case		0x05060000:			/*日冻结*/
			DefaultFreezeMode = 0xFF;	/*默认全允许读*/
			DI0Range = 0x3E;			/*日冻结只允许读上1-上62次*/
			break;
		case		0x05080000:			/* 剩余金额没有模式字的控制，应答OK*/
			if( ( DataCode & 0x000000FF ) > 0x3E )
			{
				return(C_Error);	/*剩余金额日冻结也只允许读上1-上62次*/
			}
			return(C_OK);
		default:
			return(C_Error);
	}
	FreezeMode = DefaultFreezeMode;

/*判断DI0次数是否在合理范围，不是则返回错误。DI1数据层会进行判断的。*/
	if( ( ( DataCode & 0x000000FF ) > (ulong32)DI0Range ) || ( ( DataCode & 0x000000FF ) == 0 ) )
	{/*DI0=0表示读次数这里也返回失败。*/
		return(C_Error);
	}

/*根据模式字判断分项标识码是否支持读*/
/*如果读取冻结时间，只要模式字不为0，就直接可读。*/
	if( ( DataCode & 0x0000FF00 ) == 0 )
	{/*冻结时间*/
		if(FreezeMode != 0)
		{
			return(C_OK);
		}
		else
		{
			return(C_Error);
		}
	}
/*其他判断DI1*/
	switch(DataCode & 0x0000FF00)
	{
		case		0x00000100:			/*正向有功*/
			DefaultFreezeMode = 0x01;	/*仅需要第0位*/
			break;
		case		0x00000200:			/*反向有功*/
			DefaultFreezeMode = 0x02;	/*仅需要第1位*/
			break;
		case		0x00000300:			/*组无1*/
			DefaultFreezeMode = 0x04;	/*仅需要第2位*/
			break;
		case		0x00000400:			/*组无2*/
			DefaultFreezeMode = 0x08;	/*仅需要第3位*/
			break;
		case		0x00000500:			/* 1-4象限无功*/
		case		0x00000600:
		case		0x00000700:
		case		0x00000800:
			DefaultFreezeMode = 0x10;	/*仅需要第4位*/
			break;
		case		0x00000900:			/*正有需*/
			DefaultFreezeMode = 0x20;	/*仅需要第5位*/
			break;
		case		0x00000A00:			/*反有需*/
			DefaultFreezeMode = 0x40;	/*仅需要第6位*/
			break;
		case		0x00001000:			/*变量*/
			DefaultFreezeMode = 0x80;	/*仅需要第7位*/
			break;
		default:
			return(C_Error);
	}

	if( ( FreezeMode & DefaultFreezeMode ) == 0 )
	{/*对应位设置成0了。*/
		return(C_Error);
	}
	else
	{
		return(C_OK);
	}
}

/**************************************/
/**********698兼容645增加***********/
/*需量*/
const Str_ParaChange_OADToDI_Table  Str_DemandChange[]=
{
     /*  OAD         	        DI */
    {CPos_Ac_Tol_De_0,	        0x01010000},/*当前正向有功总最大需量及发生时刻*/
    {CPos_Ac_T1_De_0 ,	        0x01010100},/*当前正向有功费率1最大需量及发生时刻*/
    {CPos_Ac_T2_De_0 ,	        0x01010200},/*当前正向有功费率2最大需量及发生时刻*/
    {CPos_Ac_T3_De_0 ,	        0x01010300},/*当前正向有功费率3最大需量及发生时刻*/
    {CPos_Ac_T4_De_0 ,	        0x01010400},/*当前正向有功费率4最大需量及发生时刻*/
    {CRev_Ac_Tol_De_0,	        0x01020000},/*当前反向有功总最大需量及发生时刻*/
    {CRev_Ac_T1_De_0 ,	        0x01020100},/*当前反向有功费率1最大需量及发生时刻*/
    {CRev_Ac_T2_De_0 ,	        0x01020200},/*当前反向有功费率2最大需量及发生时刻*/
    {CRev_Ac_T3_De_0 ,	        0x01020300},/*当前反向有功费率3最大需量及发生时刻*/
    {CRev_Ac_T4_De_0 ,	        0x01020400},/*当前反向有功费率4最大需量及发生时刻*/
    {CCom_Re1_Tol_De_0,	        0x01030000},/*当前组合无功1总最大需量及发生时刻*/
    {CCom_Re1_T1_De_0 ,	        0x01030100},/*当前组合无功1费率1最大需量及发生时刻*/
    {CCom_Re1_T2_De_0 ,	        0x01030200},/*当前组合无功1费率2最大需量及发生时刻*/
    {CCom_Re1_T3_De_0 ,	        0x01030300},/*当前组合无功1费率3最大需量及发生时刻*/
    {CCom_Re1_T4_De_0 ,	        0x01030400},/*当前组合无功1费率4最大需量及发生时刻*/
    {CCom_Re2_Tol_De_0,	        0x01040000},/*当前组合无功2总最大需量及发生时刻*/
    {CCom_Re2_T1_De_0 ,	        0x01040100},/*当前组合无功2费率1最大需量及发生时刻*/
    {CCom_Re2_T2_De_0 ,	        0x01040200},/*当前组合无功2费率2最大需量及发生时刻*/
    {CCom_Re2_T3_De_0 ,	        0x01040300},/*当前组合无功2费率3最大需量及发生时刻*/
    {CCom_Re2_T4_De_0 ,	        0x01040400},/*当前组合无功2费率4最大需量及发生时刻*/
    {CQua1_Re_Tol_De_0,	        0x01050000},/*当前1象限无功总最大需量及发生时刻*/
    {CQua1_Re_T1_De_0 ,	        0x01050100},/*当前1象限无功费率1最大需量及发生时刻*/
    {CQua1_Re_T2_De_0 ,	        0x01050200},/*当前1象限无功费率2最大需量及发生时刻*/
    {CQua1_Re_T3_De_0 ,	        0x01050300},/*当前1象限无功费率3最大需量及发生时刻*/
    {CQua1_Re_T4_De_0 ,	        0x01050400},/*当前1象限无功费率4最大需量及发生时刻*/
    {CQua2_Re_Tol_De_0,	        0x01060000},/*当前2象限无功总最大需量及发生时刻*/
    {CQua2_Re_T1_De_0 ,	        0x01060100},/*当前2象限无功费率1最大需量及发生时刻*/
    {CQua2_Re_T2_De_0 ,	        0x01060200},/*当前2象限无功费率2最大需量及发生时刻*/
    {CQua2_Re_T3_De_0 ,	        0x01060300},/*当前2象限无功费率3最大需量及发生时刻*/
    {CQua2_Re_T4_De_0 ,	        0x01060400},/*当前2象限无功费率4最大需量及发生时刻*/
    {CQua3_Re_Tol_De_0,	        0x01070000},/*当前3象限无功总最大需量及发生时刻*/
    {CQua3_Re_T1_De_0 ,	        0x01070100},/*当前3象限无功费率1最大需量及发生时刻*/
    {CQua3_Re_T2_De_0 ,	        0x01070200},/*当前3象限无功费率2最大需量及发生时刻*/
    {CQua3_Re_T3_De_0 ,	        0x01070300},/*当前3象限无功费率3最大需量及发生时刻*/
    {CQua3_Re_T4_De_0 ,	        0x01070400},/*当前3象限无功费率4最大需量及发生时刻*/
    {CQua4_Re_Tol_De_0 ,        0x01080000}, /*当前4象限无功总最大需量及发生时刻*/
    {CQua4_Re_T1_De_0 ,	        0x01080100}, /*当前4象限无功费率1最大需量及发生时刻*/
    {CQua4_Re_T2_De_0 ,	        0x01080200}, /*当前4象限无功费率2最大需量及发生时刻*/
    {CQua4_Re_T3_De_0 ,	        0x01080300}, /*当前4象限无功费率3最大需量及发生时刻*/
    {CQua4_Re_T4_De_0 ,	        0x01080400}, /*当前4象限无功费率4最大需量及发生时刻*/

    {CPosA_Ac_De_0,             0x01150000},  /*当前A相正向有功最大需量及发生时刻*/
    {CRevA_Ac_De_0,             0x01160000},  /*当前A相反向有功最大需量及发生时刻*/
    {CComA_Re1_De_0,            0x01170000},  /*当前A相组合无功1最大需量及发生时刻*/
    {CComA_Re2_De_0,            0x01180000},  /*当前A相组合无功2最大需量及发生时刻*/
    {CQua1A_Re_De_0,            0x01190000},  /*当前A相1象限无功最大需量及发生时刻*/
    {CQua2A_Re_De_0,            0x011A0000},  /*当前A相2象限无功最大需量及发生时刻*/
    {CQua3A_Re_De_0,            0x011B0000},  /*当前A相3象限无功最大需量及发生时刻*/
    {CQua4A_Re_De_0,            0x011C0000},  /*当前A相4象限无功最大需量及发生时刻*/
    {CPosB_Ac_De_0,             0x01290000},  /*当前B相正向有功最大需量及发生时刻*/
    {CRevB_Ac_De_0,             0x012A0000},  /*当前B相反向有功最大需量及发生时刻*/
    {CComB_Re1_De_0,            0x012B0000},  /*当前B相组合无功1最大需量及发生时刻*/
    {CComB_Re2_De_0,            0x012C0000},  /*当前B相组合无功2最大需量及发生时刻*/
    {CQua1B_Re_De_0,            0x012D0000},  /*当前B相1象限无功最大需量及发生时刻*/
    {CQua2B_Re_De_0,            0x012E0000},  /*当前B相2象限无功最大需量及发生时刻*/
    {CQua3B_Re_De_0,            0x012F0000},  /*当前B相3象限无功最大需量及发生时刻*/
    {CQua4B_Re_De_0,            0x01300000},  /*当前B相4象限无功最大需量及发生时刻*/
    {CPosC_Ac_De_0,             0x013D0000},  /*当前C相正向有功最大需量及发生时刻*/
    {CRevC_Ac_De_0,             0x013E0000},  /*当前C相反向有功最大需量及发生时刻*/
    {CComC_Re1_De_0,            0x013F0000},  /*当前C相组合无功1最大需量及发生时刻*/
    {CComC_Re2_De_0,            0x01400000},  /*当前C相组合无功2最大需量及发生时刻*/
    {CQua1C_Re_De_0,            0x01410000},  /*当前C相1象限无功最大需量及发生时刻*/
    {CQua2C_Re_De_0,            0x01420000},  /*当前C相2象限无功最大需量及发生时刻*/
    {CQua3C_Re_De_0,            0x01430000},  /*当前C相3象限无功最大需量及发生时刻*/
    {CQua4C_Re_De_0,            0x01440000},  /*当前C相4象限无功最大需量及发生时刻*/

};
#define Str_DemandChange_Len  (sizeof(Str_DemandChange) / sizeof(Str_ParaChange_OADToDI_Table))

/***************************************************************************
函数原型 	Comm_ReadDemandReg
函数功能	完成读需量命令的解析并应答
输入参数	*pV_645Frame				:收到的命令帧
输出参数 	无
返回参数	无
全局变量 	和通道相关的全局变量
函数备注	进入本函数，DI3肯定等于01
***************************************************************************/
void 		Comm_ReadDemandReg(Str_Comm_645 * pV_645Frame)
{
	uchar8	buf_O_CanWrite = 0;						/*缓冲区可写数据的偏移*/
	uchar8	LenFor_Data[2];							/*缓冲区可被写的总的长度*/
	uchar8	*pData;
	uchar8	V_ReturnData = C_IDError;
    ushort16 V_usLen;
	uchar8	i;

/*注意pData不包含DI数据*/
	pData = &pV_645Frame->Data[C_11_SData];
/*读当前需量*/
	if(pV_645Frame->Data[C_O_DI0] == 0x00)
	{
       if(pV_645Frame->Data[C_O_DI1] == 0xFF)
       {
       		for( i = 0; i < Str_DemandChange_Len; i++ )
       		{
       			if( ( pV_645Frame->DI & 0xFFFF00FF )== ( Str_DemandChange[i].DI & 0xFFFF00FF ) )
       			{
					/*V_ReturnData = InF_ReadDemand(Str_DemandChange[i].OAD, &pData[buf_O_CanWrite], CLRev_Ac_Tol_De_0);
                    645协议处理，后续修改 lzy 20211101*/
                    buf_O_CanWrite += CLRev_Ac_Tol_De_0;
       			}
       		}
       }
       else
       {
       		for( i = 0; i < Str_DemandChange_Len; i++ )
       		{
       			if(pV_645Frame->DI == Str_DemandChange[i].DI)
       			{
					/*V_ReturnData = InF_ReadDemand(Str_DemandChange[i].OAD, &pData[buf_O_CanWrite], CLRev_Ac_Tol_De_0);
                    645协议处理，后续修改 lzy 20211101*/
                    break;
                }
       		}
            buf_O_CanWrite = CLRev_Ac_Tol_De_0;
       }
       LenFor_Data[0] = buf_O_CanWrite;


	}
    else
    {
/*读结算需量*/
		if( ( pV_645Frame->Data[C_O_DI0] >= 0x01 ) && ( pV_645Frame->Data[C_O_DI0] <= 0x0C ) )
		{
			if( pV_645Frame->Data[C_O_DI2] < 0x09 ) /*DI2 0x00-0x08*/
			{
				V_usLen = CLRev_Ac_Tol_De_0;
				V_ReturnData = SF_GetFrozenData_SettleFreeze_645(pV_645Frame, &pData[buf_O_CanWrite], &V_usLen);
			}
		}
        PF_Ushort16ToBuffer2(LenFor_Data, &V_usLen);
    }

	if(V_ReturnData == C_IDError)
	{/*无此标识码，应答无请求数据退出*/
		Comm_Response_Set_ReadErr(C_No_Request_data_645, pV_645Frame);
		return;
	}

	if(V_ReturnData != C_OK)
	{/*其他问题读不出，则应答其他错误。所以如果没有总清，也是其他错误。*/
		Comm_Response_Set_ReadErr(C_OtherErr_645, pV_645Frame);
		return;
	}

	Comm_11_03Response_Normal(pV_645Frame, pData, LenFor_Data[0]);
}

/*****************************************************************************************
Function：	void SF_GetFrozenData_SettleFreeze(uchar8 *V_ucResultData,uchar8 V_ucFrozenType)
Description：645获取结算冻结数据
Input： pV_645Frame接收的数据帧
Output：V_ucResultData获取的数据；V_ucResultDataLength数据长度
Calls：
Called By：
Author:
*****************************************************************************************/
#define TB_DI2ToOIB_Len 6
const Str_DI2ToOIB TB_DI2ToOIB[TB_DI2ToOIB_Len]=
{
  /*DI2   OIB*/
  {0x15,  0x11},
  {0x16,  0x21},
  {0x29,  0x12},
  {0x2A,  0x22},
  {0x3D,  0x13},
  {0x3E,  0x23},
};

uchar8 SF_GetFrozenData_SettleFreeze_645(Str_Comm_645 *pV_645Frame, uchar8 *V_ucResultData, ushort16 *V_ucResultDataLength)
{
	ulong32 V_ulOAD[3];
	uchar8 V_ucBuffer[4],V_Return;
	uchar8 V_ucData_Temp[(C_MaxRatesNum + 1) * CLPos_Ac_Tol_De_0] = {0};

/*这里增加缓存定义，因为在698中最大费率数可以设置为12，*/
/*如果按照645总及费率电能集合的长度定义缓存底层读取数据会出现缓存不够的情况*/
	ushort16 V_usLen = 0;
    uchar8 i;
	V_ulOAD[0] = (C_RelatedOAD_Settle&0xFFFF00FF) | (pV_645Frame->Data[C_O_DI0] & 0x000000FF);	/*0x500500xx*/
	V_ulOAD[2] = 0xFFFFFFFF;

    if(pV_645Frame->Data[C_O_DI3] == 0x00)
    {
		if(pV_645Frame->Data[C_O_DI1] <= 0x04)
		{
			V_ucBuffer[C_O_DI0] = pV_645Frame->Data[C_O_DI1] + 1;
			V_ucBuffer[C_O_DI1] = 0x02; 															/*电能类读取均为属性2*/
			/**V_ucBuffer[C_O_DI2]***************/
			if(pV_645Frame->Data[C_O_DI2] < 0x09)
			{
				V_ucBuffer[C_O_DI2] = pV_645Frame->Data[C_O_DI2] << 4;
			}
			else
			{
				for( i = 0; i < TB_DI2ToOIB_Len; i++ )
				{
					if(TB_DI2ToOIB[i].DI2 == pV_645Frame->Data[C_O_DI2])
					{
						V_ucBuffer[C_O_DI2] = TB_DI2ToOIB[i].OIB;
						break;
					}
				}
				if(i == TB_DI2ToOIB_Len)
				{
					V_Return = C_NoData;
					return 	V_Return;
				}
			}
        /**************************************/
			V_ucBuffer[C_O_DI3] = pV_645Frame->Data[C_O_DI3];										/*电能类读取均为OIA均为0x00	 */
			PF_Buffer4ToUlong32(V_ucBuffer, &V_ulOAD[1], 4);
			V_usLen = CLPrePos_Ac_Tol_En_1;
			V_Return = Inf_Read_FrozenData_OneOAD(V_ulOAD, V_ucResultData, &V_usLen);
			if(V_Return == C_NoData)
			{
				V_usLen = CLPos_Ac_Tol_En_1;
				memset(V_ucResultData, 0x00, V_usLen);
				V_Return = C_OK;
			}
		}
		else if( pV_645Frame->Data[C_O_DI1] == 0xFF)
		{
			V_ucBuffer[C_O_DI0] = 0x00; /*电能类读取索引00获取集合*/
			V_ucBuffer[C_O_DI1] = 0x02; /*电能类读取均为属性2*/

			/**V_ucBuffer[C_O_DI2]***************/
			if(pV_645Frame->Data[C_O_DI2] < 0x09)
			{
				V_ucBuffer[C_O_DI2] = pV_645Frame->Data[C_O_DI2] << 4;
			}
			else
			{
				for( i = 0; i < TB_DI2ToOIB_Len; i++ )
				{
					if(TB_DI2ToOIB[i].DI2 == pV_645Frame->Data[C_O_DI2])
					{
						V_ucBuffer[C_O_DI2] = TB_DI2ToOIB[i].OIB;
						break;
					}
				}
				if(i == TB_DI2ToOIB_Len)
				{
					V_Return = C_NoData;
					return 	V_Return;
				}
			}

			V_ucBuffer[C_O_DI3] = pV_645Frame->Data[C_O_DI3];					/*电能类读取均为OIA均为0x00	 */
			PF_Buffer4ToUlong32(V_ucBuffer, &V_ulOAD[1], 4);

			V_usLen = sizeof(V_ucData_Temp);
			V_Return = Inf_Read_FrozenData_OneOAD(V_ulOAD, V_ucData_Temp, &V_usLen);
			memcpy(V_ucResultData, V_ucData_Temp, CLPos_Ac_En_FF_1);			/*截取总及前4费率电能*/
			if(V_Return == C_NoData)
			{
				V_usLen = CLPos_Ac_En_FF_1;
				memset(V_ucResultData, 0x00, V_usLen);
				V_Return = C_OK;
			}

			if(V_usLen < CLPos_Ac_En_FF_1)										/*预防费率数<4情况*/
			{
				memset(&V_ucResultData[V_usLen], 0x00, (CLPos_Ac_En_FF_1 - V_usLen) );
			}

			V_usLen = CLPos_Ac_En_FF_1;
		}
		else
		{
			V_Return = C_NoData;
		}
	}
    if(pV_645Frame->Data[C_O_DI3] == 0x01)
    {
		if(pV_645Frame->Data[C_O_DI1] <= 0x04)
		{
			V_ucBuffer[C_O_DI0] = pV_645Frame->Data[C_O_DI1]+1;
			V_ucBuffer[C_O_DI1] = 0x02; /*需量类读取均为属性2*/
			V_ucBuffer[C_O_DI2] = pV_645Frame->Data[C_O_DI2]<<4;

			V_ucBuffer[C_O_DI3] = pV_645Frame->Data[C_O_DI3]<<4;	/*需量类读取均为OIA均为0x10	*/
			PF_Buffer4ToUlong32(V_ucBuffer,&V_ulOAD[1],4);
			V_usLen=CLPos_Ac_Tol_De_0;
			V_Return = Inf_Read_FrozenData_OneOAD(V_ulOAD,V_ucResultData,&V_usLen);
			if(V_Return == C_NoData)
			{
				V_usLen=CLPos_Ac_Tol_De_0;
				memset(V_ucResultData,0x00,V_usLen);
				V_Return = C_OK;
			}
		}
		else if(pV_645Frame->Data[C_O_DI1] == 0xFF)
		{
			V_ucBuffer[C_O_DI0] = 0x00; /*需量类读取索引00获取集合*/
			V_ucBuffer[C_O_DI1] = 0x02; /*需量类读取均为属性2*/
			V_ucBuffer[C_O_DI2] = pV_645Frame->Data[C_O_DI2] << 4;

			V_ucBuffer[C_O_DI3] = pV_645Frame->Data[C_O_DI3] << 4;	/*需量类读取均为OIA均为0x00	 */
			PF_Buffer4ToUlong32(V_ucBuffer, &V_ulOAD[1], 4);
			V_usLen = CLPos_Ac_De_FF_0;
			V_Return = Inf_Read_FrozenData_OneOAD(V_ulOAD, V_ucData_Temp, &V_usLen);
			memcpy(V_ucResultData, V_ucData_Temp, CLPos_Ac_De_FF_0_4Rate);		/*截取总及前4费率需量*/

			if(V_Return == C_NoData)
			{
				V_usLen = CLPos_Ac_De_FF_0_4Rate;
				memset(V_ucResultData, 0x00, V_usLen);
				V_Return = C_OK;
			}

			if(V_usLen < CLPos_Ac_De_FF_0_4Rate)
			{
				memset(&V_ucResultData[V_usLen],0x00,(CLPos_Ac_De_FF_0_4Rate - V_usLen));
			}

			V_usLen = CLPos_Ac_De_FF_0_4Rate;
		}
		else
		{
			V_Return = C_NoData;
		}
    }
	*V_ucResultDataLength = V_usLen;
	return V_Return;
}
/*********************************/
/*698兼容645增加*/
/*电能*/
const Str_ParaChange_OADToDI_Table  Str_EnergyChange[]=
{
/*/  OAD         			DI */
  {CCom_Ac_Tol_En_0,	0x00000000	},/*当前组合有功总电能*/
  {CCom_Ac_T1_En_0 ,	0x00000100	},/*当前组合有功费率1电能*/
  {CCom_Ac_T2_En_0 ,	0x00000200	},/*当前组合有功费率2电能*/
  {CCom_Ac_T3_En_0 ,	0x00000300	},/*当前组合有功费率3电能*/
  {CCom_Ac_T4_En_0 ,	0x00000400	},/*当前组合有功费率4电能*/
  {CPos_Ac_Tol_En_0 ,	0x00010000 	},/*当前正向有功总电能*/
  {CPos_Ac_T1_En_0 , 	0x00010100	},/*当前正向有功费率1电能*/
  {CPos_Ac_T2_En_0 , 	0x00010200	},/*当前正向有功费率2电能*/
  {CPos_Ac_T3_En_0 , 	0x00010300	},/*当前正向有功费率3电能*/
  {CPos_Ac_T4_En_0 , 	0x00010400	},/*当前正向有功费率4电能*/
  {CRev_Ac_Tol_En_0, 	0x00020000 	},/*当前反向有功总电能*/
  {CRev_Ac_T1_En_0 , 	0x00020100	},/*当前反向有功费率1电能*/
  {CRev_Ac_T2_En_0 , 	0x00020200	},/*当前反向有功费率2电能*/
  {CRev_Ac_T3_En_0 , 	0x00020300	},/*当前反向有功费率3电能*/
  {CRev_Ac_T4_En_0 , 	0x00020400	},/*当前反向有功费率4电能*/
  {CCom_Re1_Tol_En_0,	0x00030000	},/*当前组合无功1总电能*/
  {CCom_Re1_T1_En_0 ,	0x00030100	},/*当前组合无功1费率1电能*/
  {CCom_Re1_T2_En_0 ,	0x00030200	},/*当前组合无功1费率2电能*/
  {CCom_Re1_T3_En_0 ,	0x00030300	},/*当前组合无功1费率3电能*/
  {CCom_Re1_T4_En_0 ,	0x00030400	},/*当前组合无功1费率4电能*/
  {CCom_Re2_Tol_En_0,	0x00040000	},/*当前组合无功2总电能*/
  {CCom_Re2_T1_En_0 ,	0x00040100	},/*当前组合无功2费率1电能*/
  {CCom_Re2_T2_En_0 ,	0x00040200	},/*当前组合无功2费率2电能*/
  {CCom_Re2_T3_En_0 ,	0x00040300	},/*当前组合无功2费率3电能*/
  {CCom_Re2_T4_En_0 ,	0x00040400	},/*当前组合无功2费率4电能*/
  {CQua1_Re_Tol_En_0,	0x00050000	},/*当前1象限无功总电能*/
  {CQua1_Re_T1_En_0 ,	0x00050100	},/*当前1象限无功费率1电能*/
  {CQua1_Re_T2_En_0 ,	0x00050200	},/*当前1象限无功费率2电能*/
  {CQua1_Re_T3_En_0 ,	0x00050300	},/*当前1象限无功费率3电能*/
  {CQua1_Re_T4_En_0 ,	0x00050400	},/*当前1象限无功费率4电能*/
  {CQua2_Re_Tol_En_0 , 	0x00060000 	},/*当前2象限无功总电能*/
  {CQua2_Re_T1_En_0  , 	0x00060100	},/*当前2象限无功费率1电能*/
  {CQua2_Re_T2_En_0  , 	0x00060200	},/*当前2象限无功费率2电能*/
  {CQua2_Re_T3_En_0  , 	0x00060300	},/*当前2象限无功费率3电能*/
  {CQua2_Re_T4_En_0  , 	0x00060400	},/*当前2象限无功费率4电能*/
  {CQua3_Re_Tol_En_0 , 	0x00070000	},/*当前3象限无功总电能*/
  {CQua3_Re_T1_En_0  , 	0x00070100	},/*当前3象限无功费率1电能*/
  {CQua3_Re_T2_En_0  , 	0x00070200	},/*当前3象限无功费率2电能*/
  {CQua3_Re_T3_En_0  , 	0x00070300	},/*当前3象限无功费率3电能*/
  {CQua3_Re_T4_En_0  , 	0x00070400	},/*当前3象限无功费率4电能*/
  {CQua4_Re_Tol_En_0 , 	0x00080000	},/*当前4象限无功总电能*/
  {CQua4_Re_T1_En_0  , 	0x00080100	},/*当前4象限无功费率1电能*/
  {CQua4_Re_T2_En_0  , 	0x00080200	},/*当前4象限无功费率2电能*/
  {CQua4_Re_T3_En_0  , 	0x00080300	},/*当前4象限无功费率3电能*/
  {CQua4_Re_T4_En_0  , 	0x00080400	},/*当前4象限无功费率4电能*/
  {CPosA_Ac_En_0,		0x00150000	},/*当前A相正向有功电能*/
  {CPosB_Ac_En_0,		0x00290000	},/*当前B相正向有功电能*/
  {CPosC_Ac_En_0,		0x003D0000	},/*当前C相正向有功电能*/
  {CRevA_Ac_En_0,		0x00160000	},/*当前A相反向有功电能*/
  {CRevB_Ac_En_0,		0x002A0000	},/*当前B相反向有功电能*/
  {CRevC_Ac_En_0,		0x003E0000	},/*当前C相反向有功电能*/
  {CQua1A_Re_En_0,		0x00190000  },/*当前A相1象限无功电能*/
  {CQua2A_Re_En_0,		0x001A0000  },/*当前A相2象限无功电能*/
  {CQua3A_Re_En_0,		0x001B0000  },/*当前A相3象限无功电能*/
  {CQua4A_Re_En_0,		0x001C0000	},/*当前A相4象限无功电能*/
  {CQua1B_Re_En_0,		0X002D0000  },/*当前B相1象限无功电能*/
  {CQua2B_Re_En_0,		0X002E0000  },/*当前B相2象限无功电能*/
  {CQua3B_Re_En_0,		0X002F0000  },/*当前B相3象限无功电能*/
  {CQua4B_Re_En_0,		0X00300000  },/*当前B相4象限无功电能*/
  {CQua1C_Re_En_0,      0x00410000	},/*当前C相1象限无功电能*/
  {CQua2C_Re_En_0,      0x00420000	},/*当前C相2象限无功电能*/
  {CQua3C_Re_En_0,      0x00430000	},/*当前C相3象限无功电能*/
  {CQua4C_Re_En_0,      0x00440000	},/*当前C相4象限无功电能*/
  {CComA_Re1_En_0,      0x00170000  },/*当前A相组合无功1电能*/
  {CComA_Re2_En_0,      0x00180000  },/*当前A相组合无功2电能*/
  {CComB_Re1_En_0,      0x002B0000  },/*当前B相组合无功1电能*/
  {CComB_Re2_En_0,      0x002C0000  },/*当前B相组合无功2电能*/
  {CComC_Re1_En_0,      0x003F0000  },/*当前C相组合无功1电能*/
  {CComC_Re2_En_0,      0x00400000  },/*当前C相组合无功2电能*/
};
#define Str_EnergyChange_Len  (sizeof(Str_EnergyChange) / sizeof(Str_ParaChange_OADToDI_Table))

/*精确电能*/
const Str_ParaChange_OADToDI_Table  Str_EnergyChange_Pre[]=
{
/*/  OAD         				DI  */
  {CPos_Ac_Tol_PreEn_0 ,	0x00600000 	},/*当前正向有功总精确电能*/
  {CPos_Ac_T1_PreEn_0 , 	0x00600100	},/*当前正向有功费率1精确电能*/
  {CPos_Ac_T2_PreEn_0 , 	0x00600200	},/*当前正向有功费率2精确电能*/
  {CPos_Ac_T3_PreEn_0 , 	0x00600300	},/*当前正向有功费率3精确电能*/
  {CPos_Ac_T4_PreEn_0 , 	0x00600400	},/*当前正向有功费率4精确电能*/
  {CRev_Ac_Tol_PreEn_0, 	0x00610000 	},/*当前反向有功总精确电能*/
  {CRev_Ac_T1_PreEn_0 , 	0x00610100	},/*当前反向有功费率1精确电能*/
  {CRev_Ac_T2_PreEn_0 , 	0x00610200	},/*当前反向有功费率2精确电能*/
  {CRev_Ac_T3_PreEn_0 , 	0x00610300	},/*当前反向有功费率3精确电能*/
  {CRev_Ac_T4_PreEn_0 , 	0x00610400	},/*当前反向有功费率4精确电能*/
};
#define Str_EnergyChange_Pre_Len  (sizeof(Str_EnergyChange) / sizeof(Str_ParaChange_OADToDI_Table))

/***************************************************************************
函数原型： SF_EnergyT0_645
函数功能： 将电能数据转换为645格式
输入参数：
			pV_ucBuf为转换前数据：属性2，每个电能4（数据块20）字节hex，大端模式
								属性4，每个电能5（数据块25）字节hex，大端模式
			*pV_usLen为原始数据长度
			V_ucOIB_698: 698标识码的IOB，用于判定是否为组合电能，组合电能翻零799999.99
						其他电能翻零999999.99
输出参数：*pV_ucBuf_Exchanged为转换后数据：属性2，每个电能4字节BCD，小端模式
								属性4，每个电能5字节BCD，小端模式
			*pV_usLen为转换后数据长度
返回参数：无
调用位置：和通道相关的全局变量
备    注：转换后数据超过对应长度则直接截取对应长度，属性2为4字节，属性4为5字节
***************************************************************************/
void SF_EnergyT0_645(uchar8 *pV_ucBuf, uchar8 *pV_ucBuf_Exchanged, ushort16 *pV_usLen, uchar8 V_ucPerLen, uchar8 V_ucOIB_698)
{
	uchar8  V_ucOneLen, i, j, V_ucEnergy_Num = 1, V_ucSign = 0;
	ulong64 V_ulData;
	ulong32 V_ulClearMax = 100000000;

	if( ( ( V_ucOIB_698 & 0xF0) == 0x00 )
		|| ( (V_ucOIB_698 & 0xF0) == 0x30 )
		|| ( (V_ucOIB_698 & 0xF0) == 0x40 ) )		/*组合电能*/
	{
		V_ulClearMax = 80000000;
	}
	V_ucOneLen = V_ucPerLen;
	V_ucEnergy_Num = (*pV_usLen) / V_ucPerLen;


	*pV_usLen = 0;
	for(j = 0; j < V_ucEnergy_Num; j++)
	{
		V_ulData = 0;
		if( (pV_ucBuf[0 + j*V_ucOneLen] & 0x80) == 0x80)
		{
			for(i = V_ucOneLen; i < 8; i++)
			{
				V_ulData <<= 8;
				V_ulData |= 0xFF;
			}
			for(i = 0; i < V_ucOneLen; i++)
			{
				V_ulData <<= 8;
				V_ulData |= pV_ucBuf[i + j*V_ucOneLen];
			}
			V_ulData = (~V_ulData) + 1;
			V_ucSign = 0x80;										/*保存符号位*/
		}
		else
		{
			for(i = 0; i < V_ucOneLen; i++)
			{
				V_ulData <<= 8;
				V_ulData |= pV_ucBuf[i + j*V_ucOneLen];
			}
		}
		V_ulData %= V_ulClearMax;									/*转换后数据对响应的进制求余*/
		for(i = 0; i < V_ucOneLen; i++)
		{
			pV_ucBuf_Exchanged[i + j * V_ucOneLen] = V_ulData%10;
			V_ulData /= 10;
			pV_ucBuf_Exchanged[i + j * V_ucOneLen] |= ( ( (uchar8)(V_ulData%10) ) << 4);
			V_ulData /= 10;
		}
		pV_ucBuf_Exchanged[i + j * V_ucOneLen - 1] |= V_ucSign;		/*最高位或上符号位*/
		*pV_usLen += V_ucOneLen;
	}
}

/***************************************************************************
函数原型：Comm_ReadEnergyReg
函数功能	：完成读电能命令的解析及应答
输入参数	：*pV_645Frame:收到的命令帧
输出参数：无
返回参数：无
调用位置：和通道相关的全局变量
备    注：进入本函数，DI3肯定等于00
***************************************************************************/
void Comm_ReadEnergyReg(Str_Comm_645 *pV_645Frame)
{/*645协议处理  后续修改 lzy 20211104*/
#if 0
	uchar8 LenFor_Data[2] = {0};    						/*缓冲区可被写的总的长度*/
	uchar8 V_ucBuffer[CLSettle_Time_1 * 12 + 10] = {0};
	uchar8 V_ReturnData = C_IDError;
	ushort16 V_usLen=CLPos_Ac_En_FF_1;
	uchar8 i, V_ucDataOff = 0;
    RdOI_Para_T V_OAD;
    ushort16 P_DataOff = 0;
    uchar8 V_Temp[CLSettle_Time_1 * 12 + 10] = {0};  		/*数据层可能存的是精确电能，长度按精确电能25,48长度能满足*/
    uchar8 V_ucLen645 = 0;
    ushort16 V_usLenTemp = 0;
    uchar8 V_LastNo = 0;
	uchar8 V_ucBufferTemp[CLSettle_Time_1 * 12] = {0};
	uchar8 V_ucDataLen;

    /*读当前电能*/
	if(pV_645Frame->Data[C_O_DI0] == 0x00)
	{
		if(pV_645Frame->Data[C_O_DI1] == 0xFF)
		{
			if( (pV_645Frame->Data[C_O_DI2] != 0x60) && (pV_645Frame->Data[C_O_DI2] != 0x61) )	/*不是精确电能*/
			{
				for(i=0;i<Str_EnergyChange_Len;i++)
				{
					if( (pV_645Frame->DI & 0xFFFF00FF) == (Str_EnergyChange[i].DI & 0xFFFF00FF) )
					{
						V_ucDataLen = CLPos_Ac_Tol_En_0;
						V_ReturnData = InF_ReadEnergy_Protocol(Str_EnergyChange[i].OAD, &V_ucBuffer[V_ucDataOff], &V_ucDataLen, C_Format_BCD);
						V_ucDataOff += CLPos_Ac_Tol_En_0;
					}
				}
			}
			else  /*读精确电能*/
			{
				for(i = 0; i < Str_EnergyChange_Pre_Len; i++)
				{
					if( (pV_645Frame->DI & 0xFFFF00FF) == (Str_EnergyChange_Pre[i].DI & 0xFFFF00FF) )
					{
						V_ucDataLen = C_EnergyNature4BCDLen;
						V_ReturnData = InF_ReadEnergy_Protocol(Str_EnergyChange_Pre[i].OAD, &V_ucBuffer[V_ucDataOff], &V_ucDataLen, C_Format_BCD);
						V_ucDataOff += CL04Pos_Ac_Tol_En_0_645;
					}
				}
			}
		}
		else
		{
			if( (pV_645Frame->Data[C_O_DI2] != 0x60) && (pV_645Frame->Data[C_O_DI2] != 0x61) )
			{
				for(i = 0; i < Str_EnergyChange_Len; i++)
				{
					if(pV_645Frame->DI == Str_EnergyChange[i].DI)
					{
						V_ucDataLen = CLPos_Ac_Tol_En_0;
						V_ReturnData = InF_ReadEnergy_Protocol(Str_EnergyChange[i].OAD, V_ucBuffer, &V_ucDataLen, C_Format_BCD);
						break;
					}
				}
				V_ucDataOff = CLPos_Ac_Tol_En_0;
			}
			else      /*读精确电能*/
			{
				for(i = 0; i < Str_EnergyChange_Pre_Len; i++)
				{
					if(pV_645Frame->DI == Str_EnergyChange_Pre[i].DI)
					{
						V_ucDataLen = C_EnergyNature4BCDLen;
						V_ReturnData = InF_ReadEnergy_Protocol(Str_EnergyChange_Pre[i].OAD, V_ucBuffer, &V_ucDataLen, C_Format_BCD);
						break;
					}
				}
				V_ucDataOff = CL04Pos_Ac_Tol_En_0_645;
			}
		}
		LenFor_Data[0] = V_ucDataOff;
	}
    else
    {
		/*读结算电能*/
		if ( ( pV_645Frame->Data[C_O_DI0] >= 0x01 ) && ( pV_645Frame->Data[C_O_DI0] <= 0x0C ) )				/*读结算电能*/
		{
			P_DataOff = CLPos_Ac_En_FF_1;
			V_ucLen645 = CLPos_Ac_En_FF_1;
			if( ( ( pV_645Frame->Data[C_O_DI2]) == 0xFE ) && ( ( pV_645Frame->Data[C_O_DI1] ) == 0x00 ) )	/*上1次结算时间00FE0001*/
			{
				V_OAD.RdOI.OAD = C_RelatedOAD_Settle | (pV_645Frame->Data[C_O_DI0]);
				V_OAD.Rd_RecordRelatedOI[0] = CFreeTime;
				V_OAD.Rd_RecordSelect[0] = C_RSDSelector9;
				V_OAD.Rd_RecordSelect[1] = pV_645Frame->Data[C_O_DI0];
				V_OAD.Rd_RecordRelatedOINum = 1;
				memset(V_Temp, 0x00, CLPos_Ac_En_FF_1);
				V_ReturnData = SF_GetAPDU_FreezeRead(&V_OAD, V_ucBuffer, &P_DataOff, C_GETNormal_Request);
				if( ( V_ReturnData == C_OK ) && ( P_DataOff != 1 ) ) 										/*无数据情况*/
				{
					V_usLen = SF_DataExchangeTo645_BasicData((V_ucBuffer + 2), V_Temp, V_usLen, &V_ucLen645);	/*时间格式与之前数据一致，不需要修改*/
					V_usLen = CLSettle_Time_1;
					memcpy(V_ucBuffer, (V_Temp + 2), V_usLen);
				}
				else
				{
				   V_usLen = CLSettle_Time_1;
				   memset(V_ucBuffer, 0x00, V_usLen);
				}
			}
			else if ( ( ( pV_645Frame->Data[C_O_DI2]) < 0x09 )    /*DI2 0x00-0x08*/
					|| ( ( pV_645Frame->Data[C_O_DI2] >= 0x15 ) && ( pV_645Frame->Data[C_O_DI2] <= 0x16 ) )
					|| ( ( pV_645Frame->Data[C_O_DI2] >= 0x29 ) && ( pV_645Frame->Data[C_O_DI2] <= 0x2A ) )
					|| ( ( pV_645Frame->Data[C_O_DI2] >= 0x3D ) && ( pV_645Frame->Data[C_O_DI2] <= 0x3E ) ) )
			{
				V_ReturnData = SF_GetFrozenData_SettleFreeze_645(pV_645Frame, V_Temp, &V_usLen);
				SF_EnergyT0_645(V_Temp, V_ucBuffer, &V_usLen, 4, (pV_645Frame->Data[C_O_DI2] << 4) );
			}
		}
		else if(pV_645Frame->Data[C_O_DI0] == 0xFF)			/*读当前及上1-12数据块：仅支持时间数据块读取，电能不支持，因此不需要修改*/
		{
			P_DataOff = CLPos_Ac_En_FF_1;
			V_ucLen645 = CLPos_Ac_En_FF_1;
			V_usLen = 0;
			if ( ( ( pV_645Frame->Data[C_O_DI2]) == 0xFE ) && ( ( pV_645Frame->Data[C_O_DI1] ) == 0x00 ) )
			{
				for(V_LastNo = 1; V_LastNo < 0x0D; V_LastNo++)
				{
					V_OAD.RdOI.OAD = C_RelatedOAD_Settle|V_LastNo;
					V_OAD.Rd_RecordRelatedOI[0] = CFreeTime;
					V_OAD.Rd_RecordSelect[0] = C_RSDSelector9;
					V_OAD.Rd_RecordSelect[1] = V_LastNo;
					V_OAD.Rd_RecordRelatedOINum = 1;
                	memset(V_Temp, 0x00, CLPos_Ac_En_FF_1);
                	P_DataOff = CLPos_Ac_En_FF_1;
					V_ReturnData = SF_GetAPDU_FreezeRead(&V_OAD, V_ucBufferTemp, &P_DataOff, C_GETNormal_Request);
					if( ( V_ReturnData == C_OK ) && ( P_DataOff != 1 ) )	/*有数据情况*/
					{
						V_usLenTemp = CLSettle_Time_1;
						V_usLenTemp = SF_DataExchangeTo645_BasicData((V_ucBufferTemp + 2), V_Temp, V_usLenTemp, &V_ucLen645);
						V_usLenTemp = CLSettle_Time_1;
						memcpy( (V_ucBuffer + (V_LastNo - 1) * CLSettle_Time_1), (V_Temp + 2), V_usLenTemp);
					}
					else	/*无数据情况*/
					{
						V_usLenTemp = CLSettle_Time_1;
						memset( (V_ucBuffer + (V_LastNo - 1) * CLSettle_Time_1), 0x00, V_usLenTemp);
					}
					V_usLen = V_usLen + V_usLenTemp;
				}
			}
		}
		PF_Ushort16ToBuffer2(LenFor_Data, &V_usLen);
    }

	if(V_ReturnData == C_OK)
    {   /*成功读出*/
        Comm_11_03Response_Normal(pV_645Frame, V_ucBuffer,LenFor_Data[0]);
        return;
    }
	else if(V_ReturnData == C_IDError)
    {   /*不成功，且为ID错误*/
        Comm_Response_Set_ReadErr(C_No_Request_data_645, pV_645Frame);
        return;
    }
	else
    {   /*其他错误*/
        Comm_Response_Set_ReadErr(C_OtherErr_645, pV_645Frame);
        return;
    }
#endif
}

/***************************************************************************
函数原型 	SF_DIChangetoOAD
函数功能	645DI标识查表转换成698OAD
输入参数	645DI
输出参数 	无
返回参数	698OAD
全局变量 	无
函数备注
***************************************************************************/
ulong32	SF_DIChangetoOAD(ulong32 V_ulDI)
{
	uchar8 i;
	ulong32 V_ulReturn = 0;

	for( i = 0; i < Pstr_ParaChange_Len; i++ )
	{
		if(V_ulDI == Pstr_ParaChange[i].DI)
		{
			V_ulReturn = Pstr_ParaChange[i].OAD;
			break;
		}
	}
	return V_ulReturn;
}
/***************************************************************************
函数原型 	SF_Error_ChangeTo645
函数功能	    698兼容645错误类型转换为645要求类型
输入参数	    V_ErrorFlag	：返回的错误类型
输出参数 	无
返回参数	    返回645错误类型
全局变量 	无
函数备注
***************************************************************************/
uchar8      SF_Error_ChangeTo645(uchar8 V_ErrorFlag)
{
     uchar8 V_ReturnData;

     switch(V_ErrorFlag)
    {
        case C_PeriodNum_OV:
          V_ReturnData = C_PeriodNum_OV_645;
            break;
        case C_SeasonNum_OV:
          V_ReturnData = C_SeasonNum_OV_645;
            break;
        case C_Unauthorized:
          V_ReturnData = C_Unauthorized_645;
            break;
        case C_No_Request_data:
          V_ReturnData = C_No_Request_data_645;
            break;
        case C_RateNum_OV:
          V_ReturnData = C_RateNum_OV;
            break;
        case C_Baud_NotModified:
          V_ReturnData = C_Baud_NotModified_645;
            break;
        default:
          V_ReturnData = C_OtherErr_645;
            break;

    }
    return V_ReturnData;
}
/**********************************************************************************
函数原型：uchar8 SF_DriveReportSet_Change(uchar8 Type, uchar8 *pData, uchar8 DataLenth)
功能描述：645在设置上报模式字，698在设置事件上报标识和跟随上报模式字（2015）时，相对应转换
          设置645时，对应698进行设置；设置698时，对应645也进行设置
输入参数：Type：C_ProtocolType_698/C_ProtocolType_645,进行操作的是645协议，还是698协议；
          *pData:输入的需要设置的数据；DataLenth：
          数据长度；645设置主动上报模式字时是8字节/
                    698设置事件属性上报标识时是共2字节(1字节数据标识OI2+1字节上报标识)/
                    698设置2015时是4字节
输出参数：
返回参数: 设置是否成功 C_OK C_Error
功能说明：
调用机制：
备    注：
**********************************************************************************/
#define C_OneBit 0x08  /*一个字节8位*/
uchar8 SF_DriveReportSet_Change(uchar8 Type, uchar8 *pData, uchar8 DataLenth)
{
	uchar8   V_ucReturn, i, j, k, V_ucTableNum;
	ushort16 V_ucLength, V_usDataEncode;
	uchar8   V_ucDataBuf[CLDrive_Report_Mode_645], V_ucReportMode698[CLDrive_Report_Mode] = {0};
	ulong64  V_ulData_Old = 0, V_ulData_New = 0;
	ulong32  V_ul32Data_Old, V_ul32Data_New,V_ulOAD = 0;

	V_ucLength = CLDrive_Report_Mode_645;
	V_ucReturn = InF_Read_Data(CDrive_Report_Mode_645, V_ucDataBuf, &V_ucLength, &V_usDataEncode);
	if(V_ucReturn != C_OK)
	{
        memset(V_ucDataBuf, 0x00, CLDrive_Report_Mode_645);
    }
    PF_Buffer8ToUlong64(V_ucDataBuf, &V_ulData_Old, CLDrive_Report_Mode_645);

    V_ucLength = CLDrive_Report_Mode;
    V_ucReturn = InF_Read_Data(CDrive_Report_Mode,V_ucReportMode698, &V_ucLength, &V_usDataEncode);
    if(V_ucReturn != C_OK)
    {
        memset(V_ucReportMode698, 0x00, CLDrive_Report_Mode);
    }

    switch(Type)
    {
        case C_ProtocolType_645:
        {
            if(DataLenth == CLDrive_Report_Mode_645)
            {
                PF_Buffer8ToUlong64(pData, &V_ulData_New, CLDrive_Report_Mode_645);
                V_ulData_Old ^= V_ulData_New;

                for( i = 0; i < CLDrive_Report_Mode_645 * C_OneBit; i++ )
                {
                    if(V_ulData_Old & 0x0000000000000001)
                    {
                    	/*写事件上报标识属性*/
                        /*得到对应的OAD*/
                        V_ucDataBuf[0] = 0x00;
                        if(Pstr_DriveReport_Change[i].Nature != C_NoChangeEvent)
                        {
							V_ucDataBuf[1] = Pstr_DriveReport_Change[i].Nature;
							V_ucDataBuf[2] = Pstr_DriveReport_Change[i].OIB;
							V_ucDataBuf[3] = 0x30;
							PF_Buffer4ToUlong32(V_ucDataBuf, &V_ulOAD, 4);
							/*得到应该写入的值*/
							if(V_ulData_New & 0x0000000000000001)
							{
								V_ucDataBuf[0] = 0x01;
							}
							else
							{
								V_ucDataBuf[0] = 0x00;
							}
							InF_Write_Data(C_Msg_Communication, V_ulOAD, V_ucDataBuf, CLOpenW_Report_Mode, C_W_SafeFlag);
                        }
                        /*写2015*/
                        if(Pstr_DriveReport_Change[i].Report698_2015_Bit != C_NoChangeEvent)
                        {
                            j = Pstr_DriveReport_Change[i].Report698_2015_Bit / C_OneBit;
                            k = Pstr_DriveReport_Change[i].Report698_2015_Bit % C_OneBit;
                            if(V_ulData_New & 0x0000000000000001)
                            {
                                V_ucReportMode698[j] |= 0x01 << k;
                            }
                            else /*0x01*/
                            {
                                V_ucReportMode698[j] &= ~(0x01 << k);
                            }
                        }
                    }
                    V_ulData_Old >>= 1;
                    V_ulData_New >>= 1;
                }
                InF_Write_Data(C_Msg_Communication, CDrive_Report_Mode, V_ucReportMode698, CLDrive_Report_Mode, C_W_SafeFlag);
            }
            else
            {
                V_ucReturn = C_Error;
            }
        }
        break;
        case C_ProtocolType_698:
        {
            if(DataLenth == CLOpenW_Report_Mode + CL_OI2Len) /*698写上报标识属性，置645主动上报模式字*/
            {
                for(i = 0; i < Pstr_DriveReport_ChangeLen; i++ )
                {
                    if(Pstr_DriveReport_Change[i].OIB == (*pData))
                    {
                        j = Pstr_DriveReport_Change[i].ReportMode645_Bit / C_OneBit; /*在第几字节*/
                        k = Pstr_DriveReport_Change[i].ReportMode645_Bit % C_OneBit; /*在字节中第几位*/
                        if( (*(pData + 1) ) == 0 )			/*不上报*/
                        {
                            V_ucDataBuf[j] &= ~(0x01 << k);
                        }
                        else/*其他均认为上报*/
                        {
                            V_ucDataBuf[j] |= 0x01 << k;
                        }
                        break;
                    }
                }
                if(i == Pstr_DriveReport_ChangeLen)
                {
                    V_ucReturn = C_Error;
                    break;
                }
                else
                {
                    InF_Write_Data(C_Msg_Communication, CDrive_Report_Mode_645, V_ucDataBuf, CLDrive_Report_Mode_645, C_W_SafeFlag);
                }
            }
            else if(DataLenth == CLDrive_Report_Mode)			/*698写2015，置645主动上报模式字*/
            {
                PF_Buffer4ToUlong32(V_ucReportMode698, &V_ul32Data_Old, CLDrive_Report_Mode);
                PF_Buffer4ToUlong32(pData, &V_ul32Data_New, CLDrive_Report_Mode);
                V_ul32Data_Old ^= V_ul32Data_New;
                for(i = 0; i < ( CLDrive_Report_Mode * C_OneBit ); i++ )
                {
                    if(V_ul32Data_Old & 0x00000001)
                    {
                        for( V_ucTableNum = 0; V_ucTableNum < Pstr_DriveReport_ChangeLen; V_ucTableNum++ )
                        {
                            if(i == Pstr_DriveReport_Change[i].Report698_2015_Bit)
                            {
                                j = Pstr_DriveReport_Change[i].ReportMode645_Bit / C_OneBit; 	/*在第几字节*/
                                k = Pstr_DriveReport_Change[i].ReportMode645_Bit % C_OneBit; 	/*在字节中第几位*/
                                if( ( ( V_ul32Data_New >> i ) & 0x00000001 ) == 0 ) 			/*不上报*/
                                {
                                    V_ucDataBuf[j] &= ~(0x01 << k);
                                }
                                else		/*其他均认为上报*/
                                {
                                    V_ucDataBuf[j] |= 0x01 << k;
                                }
                                break;
                            }

                        }
                        if(i == Pstr_DriveReport_ChangeLen)
                        {
                            V_ucReturn = C_Error;
                            break;
                        }
                        else				/*暂不写，都判断完再写*/
                        {
                            ;
                        }
                    }
                    V_ul32Data_Old >>= 1;

                }
                InF_Write_Data(C_Msg_Communication, CDrive_Report_Mode_645, V_ucDataBuf, CLDrive_Report_Mode_645, C_W_SafeFlag);
            }
            else
            {
                V_ucReturn = C_Error;
            }
        }
        break;
        default:
            V_ucReturn = C_Error;
        break;
    }
    return V_ucReturn;
}

/***************************************************************************
函数原型 	Comm_14SetParm
函数功能	通信14命令的解析及处理(编程记录、独立编程事件触发等)
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	无
函数备注
***************************************************************************/
void		Comm_14SetParm(Str_Comm_645 *pV_645Frame)
{
	uchar8	V_ReturnData = C_OtherErr_645;
	ulong32	ExtMsgType;
	uchar8	Is_WriteDataOk = C_OK;
	uchar8	*pData;
	uchar8	DataLen;
	Str_WrParmTable	WrParmTable;
    ulong32 V_ulData;
    uchar8 V_ucFlag = C_Normal645;

/*首先根据表的类型，进行命令是否支持的判断.在数据有效性判断函数中做*/
/**********************************645设置时间用***********************************/
	if( ( pV_645Frame->DI & 0xFFFF0000 ) != 0x04FE0000 )
	{
		;
	}
/*判断如果不是3类参数，则进行Mac/解密/密码判断*/
	if( Is_ParmType_3( pV_645Frame->DI, &WrParmTable, pV_645Frame->ChannelNo ) != C_OK )
	{
		V_ulData = SF_DIChangetoOAD(pV_645Frame->DI);
		if( ( V_ulData != 0 ) && ( ( pV_645Frame->DI & 0xFFFF0000 ) != 0x04010000 ) )
		{
			pV_645Frame->DI = V_ulData;
			V_ucFlag = C_NeedChangeTo698;
		}
		if( ( pV_645Frame->DI == CDate_Week ) || ( pV_645Frame->DI == CTime ) ) /*原本就为645数据标识，存储也为645标识*/
		{
			V_ucFlag = C_NeedChangeTo698;
		}
		/*查表*/
		V_ReturnData = LookFor_WrParmTable(pV_645Frame, &WrParmTable);
		if(V_ReturnData != C_OK)
		{/*标识码不对，应答其他错误*/
			if(pV_645Frame->DI == CModular_Baud_645)
			{
				Comm_Response_Set_ReadErr(C_Baud_NotModified_645, pV_645Frame);

			}
			else
			{
				Comm_Response_Set_ReadErr(C_Unauthorized_645, pV_645Frame);
			}
			return;
		}

		if(pV_645Frame->Data[CPW_14OV_645] == 0x98)
		{
			/*II类参数，解密及数据有效性判断*/
			V_ReturnData = Comm_14_98SetParm(pV_645Frame, &WrParmTable, V_ucFlag);
		}
		else
		{
			/*其他去判断04、02级密码，解密及数据有效性判断*/
			V_ReturnData = Comm_14_04SetParm(pV_645Frame, &WrParmTable, V_ucFlag);
		}

		if(V_ReturnData != C_OK)
		{
			V_ReturnData = SF_Error_ChangeTo645(V_ReturnData);
			Comm_Response_Set_ReadErr(V_ReturnData, pV_645Frame);
			return;
		}

		if(V_ReturnData == C_OK)
		{
			INF_Append_ProgRecordDI_645(&pV_645Frame->Data[COpcode_14O_V_645], &pV_645Frame->Data[CDI_O_V_645], &SV_Comm_Parse.ProgRecord_645);

			if(pV_645Frame->DI == CDrive_Report_Mode_645)
			{
				pData = &pV_645Frame->Data[CData_14O_V_645];
				SF_DriveReportSet_Change(C_ProtocolType_645, pData, CLDrive_Report_Mode_645);
			}
		}
		if( ( V_ReturnData == C_OK ) && ( V_ucFlag == C_NeedChangeTo698 ) )
		{
			Comm_Response_Set_ReadErr(C_OK, pV_645Frame);
			return;
		}
	}
	else
	{
		/*III类参数,不需要查表，直接根据pWrParmTable执行数据有效性判断*/
		/*实际上就判了个长度,不判密码*/
		V_ReturnData = Is_SetParmData_Ok(pV_645Frame, &WrParmTable);
		if(V_ReturnData !=C_OK)
		{
		  V_ReturnData = SF_Error_ChangeTo645(V_ReturnData);
			Comm_Response_Set_ReadErr(V_ReturnData, pV_645Frame);
			return;
		}
	}
/*判断是否是具有独立编程事件的编程项目或其他有特殊动作的项目*/
/*是，则调用对应的处理函数*/
/*否则直接写数据层*/
	SV_Comm_Parse_Local.SafeControlFlag = SV_Comm_Parse_Local.SafeControlFlag | C_W_SafeFlag_3;
	pData = &pV_645Frame->Data[CData_14O_V_645];
	DataLen = pV_645Frame->DataLen - (CLen_DI + CLen_OpCode + CLen_CommPW);

	switch(WrParmTable.Method & C_HaveIPEventType)
	{
		case		C_HaveIPEvent_RstReportState:		/*复位主动上报状体字*/
			SF_RstHaveReportState_645To698(&pV_645Frame->Data[C_Data_OFS_14]);	/*清698主动上报，698兼容645增加*/
			Rst_SV_ReportNewAddNum(&pV_645Frame->Data[C_Data_OFS_14]);
			break;
		case		C_HaveIPEvent_Invalid:				/*无特殊处理，直接写数据层*/
			if( ( pV_645Frame->DI == 0x04000C03 ) || ( pV_645Frame->DI == 0x04000C05 ) )
			{
				PF_CopyDataBytes(pData + 1, pData, 3);
			   DataLen = 4 - 1;							/*秘级不需要写*/
			}
			Is_WriteDataOk = InF_Write_Data(C_Msg_Communication, pV_645Frame->DI, pData, (ushort16)DataLen, SV_Comm_Parse_Local.SafeControlFlag);
			break;
		default:
			Comm_Response_Set_ReadErr(C_Unauthorized_645, pV_645Frame);			/*不可能到这里*/
			return;
	}
/*后续有无消息触发?    有，则触发对应的消息*/
	ExtMsgType = WrParmTable.Method & C_ExtMsgType;
	switch(ExtMsgType)
	{/*触发外部消息*/
		case		C_ExtMsgType_Invalid:		/*无外部消息需要触发*/
			break;

		default:
			break;								/*不可能跑到这里.*/
	}
/*组织正确应答帧*/
	if(Is_WriteDataOk == C_OK)
	{
		Comm_Response_Set_ReadErr(C_OK, pV_645Frame);
	}
	else
	{
		Comm_Response_Set_ReadErr(C_OtherErr_645, pV_645Frame);
	}
}

/***************************************************************************
函数原型：void ReturnMoney_698()
函数功能：通信退费
输入参数：无
输出参数：无
返回参数：无
调用位置：无
备    注：在进入本函数之前，已判断200次挂起，身份认证有效权限
***************************************************************************/
void ReturnMoney_698()
{
    uchar8 V_ucbuf[CLReturn_M_Note_1];
	ushort16 V_usDataLen, V_usDataEncode[30] = {0x00};
	uchar8 V_ucDataBuff[300] = {0};
	ushort16 V_usOffset = 0, V_ResidualLength, V_ucRelateoff;

	V_usOffset = SF_GetProgFixedData_698(CReturn_M_Degree, V_ucDataBuff);  /*取固定列数据*/

    /*退费标准记录单元,事件记录存BCD格式，退费金额*/
	PF_Ulong32ToBuffer4(&V_ucDataBuff[V_usOffset],&(MoneyClient_Table.V_ulMoney),CLReturn_M_Sum3);
	V_usOffset += CLReturn_M_Sum3;

	V_ResidualLength = 300 - V_usOffset;		/*剩余buff长度*/
	V_ucRelateoff = V_usOffset;
	if(Inf_GetRecordData(&V_ucDataBuff[V_usOffset], &V_ResidualLength, CReturn_M_OADTab, C_ReadRecord_Hap) == C_OK)	/*获取关联OAD数据*/
	{
		V_usOffset += V_ResidualLength;			/*数据总长度*/
	}

	InF_Write_Data(C_Msg_Communication, CReturn_M_Note_1, V_ucDataBuff, V_usOffset, C_W_SafeFlag);

     /*同步ESAM*/
    V_usDataLen = CLChargeBal_Hex_Cent;
	if( InF_GetData_ObjectManage( CChargeBal_Hex_Cent, V_ucbuf, &V_usDataLen, V_usDataEncode ) == C_OK )
    {
        InF_S_UpdataChargeBalInESAM( V_ucbuf );
    }

    /*写发生后*/
	V_ResidualLength = 300 - V_ucRelateoff;
	if(Inf_GetRecordData(&V_ucDataBuff[V_ucRelateoff], &V_ResidualLength, CReturn_M_OADTab, C_ReadRecord_End) == C_OK)   /*取结束数据*/
	{
		V_ucRelateoff += V_ResidualLength;
	}

	InF_Write_Data(C_Msg_Communication, (CReturn_M_Note_1 + 1), V_ucDataBuff, V_ucRelateoff, C_W_SafeFlag);

	Inf_EventReport_HP(C_ReturnMoneyEventNo,C_Happen_EventReport);

	return;
}
/***************************************************************************
函数原型 	HaveIPEvent
函数功能	触发独立的编程事件消息
输入参数	*pV_645Frame			:接收到645帧
输出参数 	无
返回参数	无
全局变量 	内部全局消息标志
函数备注
***************************************************************************/
void	HaveIPEvent( Str_Comm_645 *pV_645Frame )
{
	ulong32 V_ulDITemp;

	if( ( pV_645Frame->DI & 0xFFFFFF00 ) == CSec_TZone_Data )
	{
		V_ulDITemp = ( pV_645Frame->DI & 0xFFFFFF00 );
	}
	else
	{
		V_ulDITemp = pV_645Frame->DI;
	}

	switch(V_ulDITemp)
	{
		case	CDate_Time:			/*校时记录。CDate_Week、CTime、CDate_Week_Time*/

			Comm_AppendMsg(CMsg_ProgDateTime);		/*校时主动上报在校时独立编程事件中执行。*/
			return;
        case	CBroadcastTimeM:                	/*广播校时记录。已在时钟长度特殊方法中全部调整成CDate_Time*/
			Comm_AppendMsg(CMsg_BroadcastTime);		/*广播校时主动上报在校时独立编程事件中执行。*/
			return;
		case	CActive_Com_State:					/*有功组合状态字*/
			Comm_AppendMsg(CMsg_ProgCombPState);
            Inf_EventReport_HP(C_ProgAcCEventNo, C_Happen_EventReport);
			return;
		case	CReactive_Com_State1:				/*无功组合状态字1*/
			Comm_AppendMsg(CMsg_ProgCombQ1State);
            Inf_EventReport_HP(C_ProgReCEventNo, C_Happen_EventReport);
			return;
		case	CReactive_Com_State2:				/*无功组合状态字2*/
			Comm_AppendMsg(CMsg_ProgCombQ2State);
            Inf_EventReport_HP(C_ProgReCEventNo, C_Happen_EventReport);
			return;
		case	CWeek_RestDay_DTable:				/*周休日采取的日时段表号*/
			Comm_AppendMsg(CMsg_ProgWeekRest);
            Inf_EventReport_HP(C_ProgWReEventNo, C_Happen_EventReport);
			return;
		case	CSettle_Day1:						/*每月第1结算日*/
		case	CSettle_Day2:
		case	CSettle_Day3:
			Comm_AppendMsg(CMsg_ProgSetADate);
            Inf_EventReport_HP(C_ProgSettDEventNo, C_Happen_EventReport);
			return;
		case	CFirst_TZone_Data:					/* 第1套时区表*/
		case	CSec_TZone_Data:
			Comm_AppendMsg(CMsg_ProgSeason);
            Inf_EventReport_HP(C_ProgPZEventNo, C_Happen_EventReport);

			return;
		case	CBackUp_RateFF_Price:				/*备用套费率电价数据块*/
			Comm_AppendMsg(CMsg_ProgRate);
			Inf_EventReport_HP(C_ProgTParaEventNo, C_Happen_EventReport);

			return;
		case	CBackUp_Ladder_Table:				/*备用套阶梯表*/
			Comm_AppendMsg(CMsg_ProgStepTariff);
            Inf_EventReport_HP(C_ProgLadEventNo, C_Happen_EventReport);

			return;
		case	CFirst_TZone_1PT_Data:				/*第1套时段表编程*/
		case	CFirst_TZone_2PT_Data:
		case	CFirst_TZone_3PT_Data:
		case	CFirst_TZone_4PT_Data:
		case	CFirst_TZone_5PT_Data:
		case	CFirst_TZone_6PT_Data:
		case	CFirst_TZone_7PT_Data:
		case	CFirst_TZone_8PT_Data:

		case	CSec_TZone_1PT_Data:				/*第2套时段表编程*/
		case	CSec_TZone_2PT_Data:
		case	CSec_TZone_3PT_Data:
		case	CSec_TZone_4PT_Data:
		case	CSec_TZone_5PT_Data:
		case	CSec_TZone_6PT_Data:
		case	CSec_TZone_7PT_Data:
		case	CSec_TZone_8PT_Data:
			Comm_AppendMsg(CMsg_ProgTimePeriod);
            Inf_EventReport_HP(C_ProgPTEventNo, C_Happen_EventReport);
			return;
		default:
			if((pV_645Frame->DI & 0xFFFFFF00) == 0x40110200)	/*设置公共假日*/
			{
				Comm_AppendMsg(CMsg_ProgHoliday);
				Inf_EventReport_HP(C_ProgHolEventNo, C_Happen_EventReport);
				return;
			}
			return;
	}
}
/*******************************************************************************
函数原型:SetGPRSSignal
函数功能:设置GPRS信号，数据写入数据层同时发送信号符号显示
输入参数:V_GPRSSignal:接收到的GPRS信号
输出参数:
返回参数:
全局变量:
函数备注:698协议信号强度数据类型为long，单位为dBm。
*******************************************************************************/
void SetGPRSSignal( uchar8 *V_GPRSSignal )
{
	ulong32 V_ulGPRSSignal;
	float V_fSignal;

	GPRS_DisplayTimer = C_Init_GPRS_DisplayTimer;
	/*BCD格式rssi(dbm)写数据层,威思顿4G模块每15分钟写一次*/
	InF_Write_Data( C_Msg_Communication, CGPS_Signal, V_GPRSSignal, CLGPS_Signal, C_W_SafeFlag );

	if( (V_GPRSSignal[1] & 0x80) != 0x80 )					/*rssi(dbm)为0或正数*/
	{
		Comm_SendMsgToDisp( C_GPRSSign, C_NotDisplay, C_Duration_Alway );
		Comm_SendMsgToDisp( C_GPRSSignalSign4, C_NotDisplay, C_Duration_Alway );
	}
	else													/*rssi(dbm)为负数*/
	{
		/*将BCD格式rssi(dbm)转换为正数*/
		V_GPRSSignal[1] = V_GPRSSignal[1] & 0x7F;
		PF_BCDtoHexBytes( V_GPRSSignal, &V_ulGPRSSignal, CLGPS_Signal );

		if( V_ulGPRSSignal >= 113 )
		{
			V_fSignal = 0;
		}
		else if(  V_ulGPRSSignal < 51 )
		{
			V_fSignal = 31;
		}
		else
		{
			/*根据rssi(dbm)计算signal(csq)*/
			V_fSignal = ( 113 - (float)V_ulGPRSSignal ) / 2;
		}

		V_fSignal = V_fSignal / 8;							/*信号强度分为4份*/

		if( V_fSignal <= 0 )								/*不在线灭符号*/
		{
			Comm_SendMsgToDisp( C_GPRSSign, C_NotDisplay, C_Duration_Alway );
			Comm_SendMsgToDisp( C_GPRSSignalSign4, C_NotDisplay, C_Duration_Alway );
		}
		else if( ( V_fSignal > 0 ) && ( V_fSignal <= 1 ) )
		{
			Comm_SendMsgToDisp( C_GPRSSign, C_AlwaysDisplay, C_Duration_Alway );			/*在线显示天线符号*/
			Comm_SendMsgToDisp( C_GPRSSignalSign1, C_AlwaysDisplay, C_Duration_Alway );		/*显示1个格*/
		}
		else if( ( V_fSignal > 1 ) && ( V_fSignal <= 2 ) )
		{
			Comm_SendMsgToDisp( C_GPRSSign, C_AlwaysDisplay, C_Duration_Alway );			/*在线显示天线符号*/
			Comm_SendMsgToDisp( C_GPRSSignalSign2, C_AlwaysDisplay, C_Duration_Alway );		/*显示2个格*/
		}
		else if( ( V_fSignal > 2 ) && ( V_fSignal <= 3 ) )
		{
			Comm_SendMsgToDisp( C_GPRSSign, C_AlwaysDisplay, C_Duration_Alway );			/*在线显示天线符号*/
			Comm_SendMsgToDisp( C_GPRSSignalSign3, C_AlwaysDisplay, C_Duration_Alway );		/*显示3个格*/
		}
		else
		{
			Comm_SendMsgToDisp( C_GPRSSign, C_AlwaysDisplay, C_Duration_Alway );			/*在线显示天线符号*/
			Comm_SendMsgToDisp( C_GPRSSignalSign4, C_AlwaysDisplay, C_Duration_Alway );		/*显示4个格*/
		}
	}
}

/***************************************************************************
函数原型 	SetRTC_AppendMsg
函数功能	设置时钟触发消息
输入参数	DestMsgAddressType	:通用时钟更改后发布消息的目的地址类型。
									:采用C_ExtMsgDestAddress格式
				pV_645Frame			:接收到645帧
输出参数 	无
返回参数	无
全局变量
函数备注	时钟往前更改需要负荷记录清零，但时间太长，放置到校时记录中执行。
***************************************************************************/
void	SetRTC_AppendMsg( ulong32 DestMsgAddressType, Str_Comm_645 *pV_645Frame )
{
	uchar8	Buf[CLDate_Time * 2 + 1];		/*时间存放从位置1开始，*/
	ushort16	DataLen, V_usDataEncode;

/*先将时钟更改消息发布给表格中定义的模块号*/
	SetParm_14_AppendMsg(C_ReworkTime, DestMsgAddressType);
/*时钟更改特殊消息发布*/
	DataLen = CLDate_Time;
	if( InF_Read_Data( CDate_Time, &Buf[1], &DataLen, &V_usDataEncode ) != C_OK )
	{
		/*如果时钟读不出来，则只能进行时钟设置，无法广播校时*/
		return;
	}

/*将修改前时钟(7字节，CDate_Time格式)，发布消息给结算模块*/
	Buf[0] = Pt_SettleAdd_Time;
	Comm_SendMsg(Buf, (CLDate_Time+1),C_Msg_Freeze);

/*将修改前时钟(7字节，CDate_Time格式)，发布消息给冻结模块*/
	Buf[0] = Pt_7DayAdd_FreezeTime;
	Comm_SendMsg(&Buf[0], (Pt_7DayAdd_FreezeTime_Len+1),C_Msg_Freeze);

#if 0	/*修改时间跨月清零电压合格率 费控流程月冻结不合格*/
/*将修改前后时钟(7字节，CDate_Time格式)，发布消息给电压合格率模块 此部分理论上不能放到这个位置 要时间设置成功了再发消息 需要调整 lzy 20211014*/
	PF_CopyDataBytes(&pV_645Frame->Data[CData_14O_V_645],&Buf[CLDate_Time+1],CLDate_Time);
	Buf[0] = Pt_VRQTimeChange;
	Comm_SendMsg(Buf, (CLDate_Time*2+1),C_Msg_VoltageQualifiedRateMetering);
#endif

}

/***************************************************************************
函数原型 	ReSettle_Day1_AppendMsg
函数功能	设置第一结算日触发消息
输入参数	DestMsgAddressType	:修改第一结算日后发布消息的目的地址类型。
									:采用C_ExtMsgDestAddress格式
				pV_645Frame			:接收到645帧
输出参数 	无
返回参数	无
全局变量
函数备注
***************************************************************************/
void	ReSettle_Day1_AppendMsg( ulong32 DestMsgAddressType, Str_Comm_645 *pV_645Frame )
{
	uchar8	Buf[CLSettle_Day1];	/*第一结算日存放从位置0开始，*/
	ushort16	DataLen, V_usDataEncode;

	DataLen = CLSettle_Day1;
	if( InF_Read_Data(CSettle_Day1, Buf, &DataLen, &V_usDataEncode) == C_OK )
	{
		if( PF_Campare_Data(Buf, &pV_645Frame->Data[CData_14O_V_645], CLSettle_Day1) != C_Equal )
		{
			SetParm_14_AppendMsg(C_ReSettle_Day1, DestMsgAddressType);
		}
	}
	else
	{
		SetParm_14_AppendMsg(C_ReSettle_Day1, DestMsgAddressType);
	}
}
/***************************************************************************
函数原型 	SetParm_14_AppendMsg
函数功能	14命令触发外部消息(通用型)
输入参数	ParmType				:更改的参数类型，取值:
									C_ReMultiRatesParm,C_ReDemand_Cycle,C_ReSettle_Day1,C_ReWorkTime等
				DestMsgAddressType	:目的地址类型采用C_ExtMsgDestAddress格式
输出参数 	无
返回参数	无
全局变量
函数备注
***************************************************************************/
void	SetParm_14_AppendMsg( uchar8 ParmType, ulong32 DestMsgAddressType )
{
	uchar8	i;
	ulong32	ExtMsgDestAddress = C_ExtMsgDA_StartBit;
	ulong32	TempDAType;

	for(i = 0; i < C_ExtMsgDA_MaxNum; i++ )
	{
		TempDAType = DestMsgAddressType & ExtMsgDestAddress;
		switch(TempDAType)
		{
			case		C_ExtMsgDA_Demand:		/*发消息给需量模块*/
				Comm_SendMsgForUpdataParm(ParmType, C_Msg_DemandMetering);
				break;
			case		C_ExtMsgDA_MultiRates:		/*时段费率模块*/
				Comm_SendMsgForUpdataParm(ParmType, C_Msg_Deal_MultiRates);
				break;
			case		C_ExtMsgDA_Settle:		/*结算日模块*/
				Comm_SendMsgForUpdataParm(ParmType, C_Msg_SettleAccounts);
				break;
			case		C_ExtMsgDA_EnergyMetering:	/*电能模块*/
				Comm_SendMsgForUpdataParm(ParmType, C_Msg_EnergyMetering);
				break;
			default:
				break;
		}
		ExtMsgDestAddress = ExtMsgDestAddress << 1;
	}
}
/*******************************************************************************
函数原型：void SF_645Meter_Work_Char1_Deal698(Str_Comm_645 *pV_645Frame)
功能描述：写645电表运行特征字1，同步698中LCD参数和开关属性
输入参数：*pV_645Frame:接收到的数据帧
输出参数：无
返回参数：无
调用位置：通信14写
备    注：
*******************************************************************************/
void SF_645Meter_Work_Char1_Deal698(Str_Comm_645 *pV_645Frame)
{
    uchar8   V_ucData, V_ucMeter_Work_Type = 0;
	ushort16 V_ucMeter_Work_Len = CLMeter_Work_Char1, V_usDataEncode;

    V_ucData = (pV_645Frame->Data[CData_14O_V_645] >> 1) & 0x01;    /*取特征字1中的液晶显示①②数据*/
    InF_Write_Data(C_Msg_Communication, C1And2Display, &V_ucData, CL1And2Display, C_W_SafeFlag);

    V_ucData = pV_645Frame->Data[CData_14O_V_645] & 0x01;           /*取特征字1中的外置控制方式*/
    InF_Read_Data(CMeter_Work_Char1, &V_ucMeter_Work_Type, &V_ucMeter_Work_Len, &V_usDataEncode);	/*读特征字*/
    V_ucMeter_Work_Type &= 0xFE;
    V_ucMeter_Work_Type |= (~V_ucData);
    InF_Write_Data(C_Msg_Communication, CMeter_Work_Char1, &V_ucMeter_Work_Type, CLMeter_Work_Char1, C_W_SafeFlag);
}
/***************************************************************************
函数原型 	Comm_14_04SetParm
函数功能	见备注
输入参数	*pV_645Frame				:接收到的数据帧
				pWrParmTable				:返回参数表格中数据地址
输出参数 	*pTBParmLineNo			:返回参数表格中数据
返回参数	C_OK/C_Unauthorized/C_OtherErr/
				/C_Baud_NotModified/C_SeasonNum_OV/C_PeriodNum_OV/C_RateNum_OV
全局变量 	无
函数备注	1、进行密级判断。
				2、进行密级判断。
				3、长度、数据合法性判断
***************************************************************************/
uchar8 Comm_14_04SetParm( Str_Comm_645 *pV_645Frame, Str_WrParmTable *pWrParmTable, uchar8 V_Flag)
{
	uchar8	Err;
	/*判断密级是否正确*/
	if( (pV_645Frame->Data[CPW_14OV_645] != 0x02)
		&&(pV_645Frame->Data[CPW_14OV_645] != 0x04) )
	{
		return(C_Unauthorized);
	}
	/*判断是否厂内，不在厂内用02、04级设置参数应答无权限*/
	if( ( pV_645Frame->DI != C_EvenHar_AddData_A0 )
	 && ( pV_645Frame->DI != C_EvenHar_AddData_A1 )
	 && ( pV_645Frame->DI != C_EvenHar_AddData_B0 )
	 && ( pV_645Frame->DI != C_EvenHar_AddData_B1 )
	 && ( pV_645Frame->DI != C_EvenHar_AddData_C0 )
	 && ( pV_645Frame->DI != C_EvenHar_AddData_C1 )
	 && ( pV_645Frame->DI != C_EvenHar_Time ) )
	{
		if(JudgeTimerExceed10min(&SI_JTimer_BSOn2500) != C_TimerEnable)
		{
			return(C_Unauthorized);
		}
	}
	/*判断密码是否正确*/
	if( ( pV_645Frame->DI != C_OddHar_AddData1 ) && ( pV_645Frame->DI != C_OddHar_AddData2 ) ) /*奇次谐波补偿不判密码*/
	{
		Err = Is_PW_OK(&pV_645Frame->Data[CPW_14OV_645]);
		if(Err != C_OK)
		{
			return(C_Unauthorized);
		}
	}
/*长度、数据合法性判断*/
/*数据合法性的判断*/
    if(V_Flag == C_NeedChangeTo698)
    {
		Err = SF_Deal_Comm_98SetParm(pV_645Frame);
		return(Err);
    }
    else
    {
       Err = Is_SetParmData_Ok(pV_645Frame, pWrParmTable);
       if ( ( pV_645Frame->DI == CMeter_Work_Char1_645 ) && ( Err == C_OK ) )
       {
           SF_645Meter_Work_Char1_Deal698( pV_645Frame );
       }
       return(Err);
    }
}
/***************************************************************************
函数原型 	SF_EventDelayTimeBCDtoHex
函数功能	:   事件延时数据BCD 转换成 Hex
输入参数	:   *pV_645Frame   :接收到的数据帧
输出参数: 	无
返回参数	：  无
全局变量：	无
函数备注：
***************************************************************************/
void SF_EventDelayTimeBCDtoHex(Str_Comm_645 *pV_645Frame)
{
    uchar8 j, V_ucData[4] = {0};
    ulong32 V_ulData = 0;

    for(j = 0; j < C_TB_EventDelayTime_Len; j++)		/*事件延时参数*/
    {
        if(pV_645Frame->DI == TB_EventDelayTime[j])
        {
            PF_BCDtoHexBytes(&pV_645Frame->Data[CData_14O_V_645], &V_ulData, CLLossVolage_Delay_T);
            PF_Ulong32ToBuffer4(V_ucData, &V_ulData, 4);
            pV_645Frame->Data[CData_14O_V_645] = V_ucData[0];
            break;
        }
    }
}
/***************************************************************************
函数原型 	SF_EventParaSpecial
函数功能	:   补1字节0x00，TB_WrParm中部分事件C_DataValidSpecialMethod转换了4字节数据，将多以1字节置0x00
输入参数	:   *pV_645Frame   :接收到的数据帧
输出参数: 	*pV_645Frame   :接收到的数据帧
返回参数	：  无
全局变量：	无
函数备注：  具体涉及事件详见表格TB_EventParaSpecial
***************************************************************************/
void SF_EventParaSpecial(Str_Comm_645 *pV_645Frame)
{
    uchar8 j;

    for(j = 0; j < C_TB_EventParaSpecial_Len; j++)/*事件延时参数*/
    {
        if(pV_645Frame->DI == TB_EventParaSpecial[j])
        {
            memset(&pV_645Frame->Data[CData_14O_V_645 + CLLossVolage_Curr_LowLim], 0x00, 1);/*由于C_DataValidSpecialMethod中转换为4字节，所以补1字节0x00*/
            break;
        }
    }
}
/***************************************************************************
函数原型 	SF_Deal_Comm_98SetParm
函数功能	:   参数写入处理
输入参数	:   *pV_645Frame   :接收到的数据帧
输出参数: 	无
返回参数	：C_OK/C_Unauthorized/C_OtherErr/
				/C_Baud_NotModified/C_SeasonNum_OV/C_PeriodNum_OV/C_RateNum_OV
全局变量：	无
函数备注：
***************************************************************************/
uchar8	SF_Deal_Comm_98SetParm(Str_Comm_645 *pV_645Frame)
{
    ulong32 V_ulLastDI = 0xFFFFFFFF;
    ulong32 V_ulNextDI = 0xFFFFFFFF;
    uchar8 V_ucFlag = C_NeedWrite645EventRecord, ReturnFlag, V_ucReturn1, V_ucReturn2;
    uchar8 V_ucBuffer[CLDate_Time], i;
    ulong32 V_ulData = 0;
	ushort16 V_ucDataLen = CLOne485_Baud, V_usDataEncode;

    if(pV_645Frame->DI == CDate_Time)
    {
		PF_CopyDataBytes(&pV_645Frame->Data[CData_14O_V_645], V_ucBuffer, CLDate_Time);
		for( i = 3; i < CLDate_Time - 1; i++ )
		{
			V_ucBuffer[i] = pV_645Frame->Data[CData_14O_V_645 + i + 1];
		}
		V_ucBuffer[6] = 0x20;
		PF_CopyDataBytes(V_ucBuffer, &pV_645Frame->Data[CData_14O_V_645], CLDate_Time);
    }
    else if( ( pV_645Frame->DI == CChange_TZ_Time ) || ( pV_645Frame->DI == CChange_PT_Time ) )
    {
		pV_645Frame->DataLen += 2;
		PF_CopyDataBytes(&pV_645Frame->Data[CData_14O_V_645], &V_ucBuffer[1], 5);
		V_ucReturn1 = Is_Buf_AllZero(&V_ucBuffer[1], 5);
		if(V_ucReturn1 == C_OK )
		{
			V_ucBuffer[0] = 0x00;
			V_ucBuffer[6] = 0x00;
		}
		V_ucReturn2 = SF_JugeDemadFF(&V_ucBuffer[1], 5);
		if(V_ucReturn2 == C_OK )
		{
			V_ucBuffer[0] = 0xFF;
			V_ucBuffer[6] = 0xFF;
		}
		if( ( V_ucReturn1 != C_OK ) && ( V_ucReturn2 != C_OK ) )
		{
			V_ucBuffer[0] = 0xFF;
			V_ucBuffer[6] = 0x20;
		}
		PF_CopyDataBytes(V_ucBuffer, &pV_645Frame->Data[CData_14O_V_645], CLChange_PT_Time);
    }
    else if( ( pV_645Frame->DI == COne485_Baud ) || ( pV_645Frame->DI == CTwo485_Baud ) )
    {

        V_ucBuffer[0] = C_bps_9600_698;
        V_ucBuffer[1] = C_parity_Even;
        V_ucBuffer[2] = C_CommDataLen8;
        V_ucBuffer[3] = C_parity_Odd;
        V_ucBuffer[4] = 0;
        InF_Read_Data(pV_645Frame->DI, V_ucBuffer, &V_ucDataLen, &V_usDataEncode);
        V_ucBuffer[0] = SF_BPS645transfor698( *( (pV_645Frame->Data) + 12 ) );

        /*判断数据的合理性*/
        if( Is_CommBPS_OK(C_RS485_1, V_ucBuffer[0]) != C_OK )
        {
            return C_Baud_NotModified;
        }
        else
        {
            PF_Ulong32ToBuffer4(pV_645Frame->Data, &(pV_645Frame->DI), CLen_DI);    /*OAD*/
            memset(pV_645Frame->Data + CLen_DI, 0x00, CLen_OpCode);                 /*操作者代码*/

            memcpy(pV_645Frame->Data + 12, V_ucBuffer, V_ucDataLen);
            pV_645Frame->DataLen = CLen_DI+CLen_OpCode + CLen_CommPW + CLOne485_Baud;
        }
    }
    else if(pV_645Frame->DI == COverCurr_Curr_LowLim)
    {
        pV_645Frame->DataLen = CLOverCurr_Curr_LowLim + CData_14O_V_645;
        PF_Buffer4ToUlong32(&pV_645Frame->Data[CData_14O_V_645], &V_ulData, CLOverCurr_Curr_LowLim645);
        V_ulData = V_ulData << 12;/*698为4位小数，645为1位小数*/
        PF_Ulong32ToBuffer4(&pV_645Frame->Data[CData_14O_V_645], &V_ulData, CLOverCurr_Curr_LowLim);
    }
    else
    {
        SF_EventDelayTimeBCDtoHex(pV_645Frame);
        SF_EventParaSpecial(pV_645Frame);
    }
    ReturnFlag = SF_SetParm(pV_645Frame, V_ulLastDI, V_ulNextDI, V_ucFlag, pV_645Frame->DI, C_SetUp);
    return ReturnFlag;
}
/***************************************************************************
函数原型 	Comm_14_98SetParm
函数功能	见备注
输入参数	*pV_645Frame				:接收到的数据帧
				pWrParmTable				:返回参数表格中数据地址
输出参数 	*pWrParmTable			:返回参数表格中数据
			 	pV_645Frame->DataLen						:数据长度，包括DI,PW,OPCode,及数据长度
				pV_645Frame->Data[CData_14O_V_645]		:解密后的数据
返回参数	C_OK/C_Unauthorized/C_OtherErr/
				/C_Baud_NotModified/C_SeasonNum_OV/C_PeriodNum_OV/C_RateNum_OV
全局变量 	无
函数备注	1、完成II类参数的解密及将数据返写pV_645Frame->Data[CData_14O_V_645]
				2、完成解密后长度返写pV_645Frame->DataLen
				2、完成解密后数据合法性、长度判断
***************************************************************************/
uchar8	Comm_14_98SetParm(Str_Comm_645 *pV_645Frame, Str_WrParmTable *pWrParmTable, uchar8 V_Flag)
{
	ushort16	Serror;
	uchar8	ValidDataLen;
	uchar8	Err;
    uchar8  V_ucBlock;
    ulong32 V_ulMethod;
/*是否为1类参数的判断,98级不能设置1类参数*/
	if( InF_S_Is_ParmPlainTextMAC( pV_645Frame->DI, &ValidDataLen ) == C_OK )
	{
		return(C_Unauthorized);
	}
/*长度的初步判断*/
	if( pV_645Frame->DataLen > ( CLen_DI + CLen_OpCode + CLen_CommPW ) )
	{
		ValidDataLen = pV_645Frame->DataLen -  (CLen_DI + CLen_OpCode + CLen_CommPW );
	}
	else
	{
		return(C_OtherErr);
	}
/*解密*/
	if(pV_645Frame->DI != CReturn_Money)
	{
		Serror = InF_S_WritePara_CipherTextMAC(pV_645Frame->DI, &pV_645Frame->Data[CData_14O_V_645],&ValidDataLen);
		if(Serror == C_SERR_ESAM_VF)
		{
			Comm_DealwithSPTVariable(C_SPTNumAdd);	/*ESAM验证失败。*/
			return(C_Unauthorized);
		}
		else if(Serror != C_OK)
		{
			return(C_OtherErr);
		}
		else
		{
			/*正确解密，赋值pV_645Frame->DataLen*/
			pV_645Frame->DataLen = ValidDataLen + CLen_DI + CLen_OpCode + CLen_CommPW;
		}

		/*数据合法性的判断*/
		if(V_Flag == C_NeedChangeTo698)
		{
			if( ( pV_645Frame->DI == CSec_TZone_Data ) || ( ( pV_645Frame->DI & 0xFFFFFF00 ) == 0x40170200 ) )
			{
				V_ucBlock = ValidDataLen / 3;
				V_ulMethod = 0x00000004;
				DataReversed(V_ulMethod, &pV_645Frame->Data[CData_14O_V_645], V_ucBlock);
				PF_OneDataReversed(&pV_645Frame->Data[CData_14O_V_645], &pV_645Frame->Data[CData_14O_V_645], ValidDataLen);
			}
			Err = SF_Deal_Comm_98SetParm(pV_645Frame);
			return(Err);
		}
		else
		{
			Err = Is_SetParmData_Ok(pV_645Frame,pWrParmTable);
			if ( ( pV_645Frame->DI == CMeter_Work_Char1_645 ) && ( Err == C_OK ) )
			{
				SF_645Meter_Work_Char1_Deal698( pV_645Frame );
			}
			return(Err);
		}
	}
	else
		{/*0514-70中对退费有明文规定，进行特殊流程处理*/
			Serror = InF_S_WR_ReturnFile( &pV_645Frame->Data[CData_14O_V_645], ValidDataLen);
			if(Serror == C_SERR_ESAM_VF)
			{
				Comm_DealwithSPTVariable(C_SPTNumAdd);	/*ESAM验证失败。*/
				return(C_Unauthorized);
			}
			else if(Serror != C_OK)
			{
				return(C_OtherErr);
			}
			else
			{
				/*正确解密，赋值pV_645Frame->DataLen*/
				pV_645Frame->DataLen = (CLReturn_Money + C_MacLen) + CLen_DI + CLen_OpCode + CLen_CommPW;
			}
			/*钱包文件同步,且判断剩余金额是否够退	*/
			if(DV_Return_Money(pV_645Frame) !=C_OK)
			{
				return(C_OtherErr);
			}
			/*进行ESAM退费验证*/
			Serror = InF_S_OPMoneyFile_Return(&pV_645Frame->Data[CData_14O_V_645]);
			if(Serror == C_SERR_ESAM_VF)
			{
				Comm_DealwithSPTVariable(C_SPTNumAdd);	/*ESAM验证失败。*/
				return(C_Unauthorized);
			}
			else if(Serror != C_OK)
			{
				return(C_OtherErr);
			}
			else
			{
				return(C_OK);
			}
		}
}
/***************************************************************************
函数原型 	Comm_14_99SetParm
函数功能	见备注
输入参数	*pV_645Frame				:接收到的数据帧
				pWrParmTable				:返回参数表格中数据地址
输出参数 	*pWrParmTable			:返回参数表格中数据
				pV_645Frame->DataLen						:数据长度，包括DI,PW,OPCode，不包括Mac
				pV_645Frame->Data[CData_14O_V_645]		:解密后的数据
返回参数	C_OK/C_Unauthorized/C_OtherErr/

全局变量 	无
函数备注	1、完成是否合法的判断(是否为1类参数，数据本身是否合法)
				2、完成是否需要测试密钥才能设置的判断
				3、完成I类参数的Mac计算
				4、写ESAM，
				5、数据返写pV_645Frame->DataLen
***************************************************************************/
uchar8	Comm_14_99SetParm(Str_Comm_645 *pV_645Frame, Str_WrParmTable *pWrParmTable)
{
	ushort16	Serror;
	uchar8	Err;
	uchar8	ValidDataLen;

/*是否为1类参数的判断*/
	if( InF_S_Is_ParmPlainTextMAC(pV_645Frame->DI, &ValidDataLen) != C_OK )
	{
		return(C_Unauthorized);
	}
/*判断是否满足必须在公钥下测试，且确实在公钥下。*/
	if(InF_JudgeKeyStatus() == C_StateOfOfficialKey)
	{
		/*为正式密钥*/
		if( ( pV_645Frame->DI == CCustomer_Num ) || ( pV_645Frame->DI == CMeter_Num ) )
		{/*正式密钥下，不能设置客户编号和表号*/
			return(C_Unauthorized);
		}
	}

/*数据合法性的判断*/
	pV_645Frame->DataLen = pV_645Frame->DataLen - C_MacLen;	/*去掉MAC长度，待判断数据合法性*/
	Err = Is_SetParmData_Ok(pV_645Frame, pWrParmTable);
	if( Err != C_OK )
	{
		return(Err);
	}
/*计算Mac*/
	ValidDataLen = pV_645Frame->DataLen - ( CLen_DI + CLen_OpCode + CLen_CommPW );
	ValidDataLen = ValidDataLen + C_MacLen;					/*因为pV_645Frame->DataLen前面减去Mac长度了	*/
	Serror = InF_S_WritePara_PlainTextMAC(pV_645Frame->DI, &pV_645Frame->Data[CData_14O_V_645], ValidDataLen);
	if(Serror == C_SERR_ESAM_VF)
	{
		Comm_DealwithSPTVariable(C_SPTNumAdd);				/*ESAM验证失败。*/
		return(C_Unauthorized);
	}
	else if(Serror != C_OK)
	{
		return(C_OtherErr);
	}
	else
	{
		return(C_OK);
	}
}
/**************************************************************************************/
/*表格含义可参见设计文档"通信模块"章节之<参数有效性及后续处理>   */
const	Str_WrParmTable	TB_WrParm[] = {
/* 0x04000101	  日期周次	*/
	{CDate_Week,
/*		表型         |      长度固定 |    长度  |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenUnsized|C_UnsizedLen_Date|C_DataValidSpecialMethod|C_DV_Date_Time_645|
/*      独立编程事件	  |触发后续消息|目的地址	*/
	C_HaveIPEvent_ProgParm |C_ExtMsg_ReWorkTime|C_ExtMsgDA_Demand|C_ExtMsgDA_MultiRates)},

/* 0x04000102	  时间	*/
	{CTime,
/*		表型         |      长度固定 |    长度  |   数据有效性判断方法 	*/
	(C_UnAddFixedDataLen|C_DataLenUnsized|C_UnsizedLen_Time|C_DataValidSpecialMethod|C_DV_Date_Time_645|
/*      独立编程事件	  |触发后续消息|目的地址	*/
	C_HaveIPEvent_ProgParm |C_ExtMsg_ReWorkTime|C_ExtMsgDA_Demand|C_ExtMsgDA_MultiRates)},

/* 0x40000200	  日期周次及时间	*/
	{CDate_Time,
/*		表型         |      长度固定 |    长度             |   数据有效性判断方法		*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLDate_Time|C_DataValidSpecialMethod|C_DV_Date_Time|
/*      独立编程事件	  |触发后续消息|目的地址	*/
	C_HaveIPEvent_ProgParm |C_ExtMsg_ReWorkTime|C_ExtMsgDA_Demand|C_ExtMsgDA_MultiRates)},

/*0x41000200	 需量周期	*/
	{CDemand_Cycle,
/*		表型         |      长度固定 |    长度         |   数据有效性判断方法	*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLDemand_Cycle|C_DataValidSpecialMethod|C_DV_Demand_Cycle|
/*      独立编程事件	  |触发后续消息|目的地址	*/
	C_HaveIPEvent_Invalid |C_ExtMsg_ReDemand_Cycle|C_ExtMsgDA_Demand)},

/*0x41010200 滑差周期	*/
	{CSliding_Time,
/*		表型         |      长度固定 |    长度       |   数据有效性判断方法	*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLSliding_Time|C_DataValidSpecialMethod|C_DV_Sliding_Time|
/*      独立编程事件	  |触发后续消息|目的地址	*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x40080200 两套时区表切换时间*/
	{CChange_TZ_Time,
/*		表型         |      长度固定 |    长度             |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLChange_TZ_Time|C_DataValidSpecialMethod|C_DV_SwitchingTime|
/*      独立编程事件	  |触发后续消息|目的地址	*/
	C_HaveIPEvent_Invalid |C_ExtMsg_ReMultiRatesParm|C_ExtMsgDA_MultiRates)},

/*0x40090200 两套时段表切换时间*/
	{CChange_PT_Time,
/*		表型         |      长度固定 |    长度             |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLChange_PT_Time|C_DataValidSpecialMethod|C_DV_SwitchingTime|
/*      独立编程事件	  |触发后续消息|目的地址	*/
	C_HaveIPEvent_Invalid |C_ExtMsg_ReMultiRatesParm|C_ExtMsgDA_MultiRates)},

/*0x400A0200 两套费率电价切换时间*/
	{CChange_Rate,
/*		表型                |      长度固定 |    长度             |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLChange_Rate|C_DataValidSpecialMethod|C_DV_SwitchingTime|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsg_ReMultiRatesParm|C_ExtMsgDA_MultiRates)},

/*0x400B0200 两套阶梯电价切换时间*/
	{CChange_Ladder,
/*		表型                |      长度固定 |    长度             |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLChange_Ladder|C_DataValidSpecialMethod|C_DV_SwitchingTime|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsg_ReMultiRatesParm|C_ExtMsgDA_MultiRates)},

/*0x400C0201 年时区数*/
	{CYear_Zone_Num,
/*		表型         |      长度固定 |    长度             |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLYear_Zone_Num|C_DataValidHex_Range|C_DV_HexRange_1_14|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsg_ReMultiRatesParm|C_ExtMsgDA_MultiRates)},

/*0x400C0202 日时段表数*/
	{CDay_Table_Num,
/*		表型         |      长度固定 |    长度             |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLDay_Table_Num|C_DataValidHex_Range|C_DV_HexRange_1_8|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsg_ReMultiRatesParm|C_ExtMsgDA_MultiRates)},

/*0x400C0203 日时段数*/
	{CDay_Time_Num,
/*		表型         |      长度固定 |    长度             |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLDay_Time_Num|C_DataValidHex_Range|C_DV_HexRange_1_14|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsg_ReMultiRatesParm|C_ExtMsgDA_MultiRates)},

/*0x400C0204 费率数*/
	{CRate_Num,
/*		表型         |      长度固定 |    长度             |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLRate_Num|C_DataValidHex_Range|C_DV_HexRange_Rates|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsg_ReMultiRatesParm|C_ExtMsgDA_MultiRates)},

/*0x400C0205 公共假日数*/
	{CHoliday_Num,
/*		表型         |      长度固定 |    长度             |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLHoliday_Num|C_DataValidHex_Range|C_DV_HexRange_0_20|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsg_ReMultiRatesParm|C_ExtMsgDA_MultiRates)},

/*0x400D0200 阶梯数*/
	{CStep_Num,
/*		表型         	     |      长度固定 |    长度             |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLStep_Num|C_DataValidHex_Range|C_DV_HexRange_0_6|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsg_ReMultiRatesParm|C_ExtMsgDA_MultiRates)},

/*0x400F0200 密钥总条数*/
	{CKey_Tol_Num,
/*		表型         |      长度固定 |    长度             |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLKey_Tol_Num|C_DataValidHex_Range|C_DV_HexRange_1_32|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsg_SetKeyNum)},		/*触发密钥更新检查消息，无须带目的地址*/

/*0xF3000401 自动循显屏数*/
	{CAuto_Dis_Screen_Num,
/*		表型         |      长度固定 |    长度                      |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLAuto_Dis_Screen_Num|C_DataValidHex_Range|C_DV_HexRange_1_99|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0xF3000300 每屏显示时间*/
	{CPer_Dis_Screen_Time,
/*		表型         |      长度固定 |    长度                      |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLPer_Dis_Screen_Time|C_DataValidHex_Range|C_DV_HexRange_5_20|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x40070205 电能小数位数*/
	{CEnergy_Decimal_Num,
/*		表型         |      长度固定 |    长度                      |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLEnergy_Decimal_Num|C_DataValidHex_Range|C_DV_HexRange_0_4|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x40070206 显示功率（最大需量）小数位数*/
	{CPower_Decimal_Num,
/*		表型         |      长度固定 |    长度                      |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLPower_Decimal_Num|C_DataValidHex_Range|C_DV_HexRange_0_6|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0xF3010401 按键循环显示屏数*/
	{CKey_CycDis_Screen_Num,
/*		表型         |      长度固定 |    长度                      |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLKey_CycDis_Screen_Num|C_DataValidHex_Range|C_DV_HexRange_1_99|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x40070201 上电全显时间*/
	{CPowerOn_Dis_All_Time,
/*		表型         |      长度固定 |    长度                      |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLPowerOn_Dis_All_Time|C_DataValidHex_Range|C_DV_HexRange_5_30|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x40070207		液晶①②字样意义*/
	{C1And2Display,
/*		表型         |      长度固定 |    长度                      |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CL1And2Display|C_DataValidHex_Range|C_DV_HexRange_0_1|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgDA_MultiRates|C_ExtMsg_ReMultiRatesParm|C_ExtMsgType_Invalid)},

/*0x40010200 通讯地址(应答时通信地址填充什么?全99?)*/
	{CComm_Address,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLComm_Address|C_DataValidSpecialMethod|C_DV_Comm_Address|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x40020200 表号*/
	{CMeter_Num,
/*		表型         |      长度固定 |    长度      |   数据有效性判断方法*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLMeter_Num|C_DataValidOnlyBCD|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x41030200 资产管理编码*/
	{CManage_Code,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLManage_Code|C_DataValid_NoLimit|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x41040200 额定电压*/
	{CRated_Vol,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLRated_Vol|C_DataValid_NoLimit|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x41050200 额定电流*/
	{CRated_Curr,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLRated_Curr|C_DataValid_NoLimit|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x41060200 最大电流*/
	{CMax_Curr,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLMax_Curr|C_DataValid_NoLimit|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x41060300 最小电流*/
	{CMin_Curr,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLMin_Curr|C_DataValid_NoLimit|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x41060400 转折电流*/
	{CTurn_Curr,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLTurn_Curr|C_DataValid_NoLimit|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x41070200 有功准确度等级*/
	{CActive_Accur_Deg,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLActive_Accur_Deg|C_DataValid_NoLimit|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x41080200 无功准确度等级*/
	{CReactive_Accur_Deg,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLReactive_Accur_Deg|C_DataValid_NoLimit|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x410B0200 电表型号*/
	{CMeter_Model,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLMeter_Model|C_DataValid_NoLimit|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x43000400 生产日期*/
	{CProd_Date,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLProd_Date|C_DataValidSpecialMethod|C_DV_Date_Time|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x40030200 客户编号*/
	{CCustomer_Num,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLCustomer_Num|C_DataValidOnlyBCD|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

//0x0400040F 电能表位置信息
	{CMeter_Position,
//		表型         |      长度固定 |    长度           |   数据有效性判断方法
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLMeter_Position|C_DataValidSpecialMethod|C_DV_Position|
//      独立编程事件	  |触发后续消息|目的地址
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x41120200 有功组合状态字*/
	{CActive_Com_State,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLActive_Com_State|C_DataValid_NoLimit|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_ProgParm |C_ExtMsgType_Invalid)},

/*0x41130200 无功组合状态字1*/
	{CReactive_Com_State1,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLReactive_Com_State1|C_DataValid_NoLimit|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_ProgParm |C_ExtMsgType_Invalid)},

/*0x41140200 无功组合状态字2*/
	{CReactive_Com_State2,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLReactive_Com_State2|C_DataValid_NoLimit|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_ProgParm |C_ExtMsgType_Invalid)},

/*0xF2020201 调制型红外光口波特率特征字*/
	{CMod_InFr_Baud,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLMod_InFr_Baud|C_DataValidSpecialMethod|C_DV_Bps|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0xF2010201 1路485波特率特征字*/
	{COne485_Baud,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLOne485_Baud|C_DataValidSpecialMethod|C_DV_Bps|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0xF2010202 2路485波特率特征字*/
	{CTwo485_Baud,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLTwo485_Baud|C_DataValidSpecialMethod|C_DV_Bps|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0xF2090201 模块通道波特率特征字*/
	{CModular_Baud,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLModular_Baud|C_DataValidSpecialMethod|C_DV_Bps|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0xF20902FD 模块通道协商波特率特征字*/
	{CModular_BaudConsult,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLModular_BaudConsult|C_DataValidSpecialMethod|C_DV_Bps|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x40130200 周休日采取的日时段表号*/
	{CWeek_RestDay_DTable,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLWeek_RestDay_DTable|C_DataValidHex_Range|C_DV_HexRange_1_8|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_ProgParm |C_ExtMsg_ReMultiRatesParm|C_ExtMsgDA_MultiRates)},

/*0x41160201 每月第1结算日*/
	{CSettle_Day1,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLSettle_Day1|C_DataValidSpecialMethod|C_DV_Settle_Day|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_ProgParm |C_ExtMsg_ReSettle_Day1|C_ExtMsgDA_Settle)},

/*0x41160202 每月第2结算日*/
	{CSettle_Day2,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLSettle_Day2|C_DataValidSpecialMethod|C_DV_Settle_Day|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_ProgParm |C_ExtMsgType_Invalid)},

/*0x41160203 每月第3结算日*/
	{CSettle_Day3,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLSettle_Day3|C_DataValidSpecialMethod|C_DV_Settle_Day|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_ProgParm |C_ExtMsgType_Invalid)},

/*0x04000C03 2级密码*/
	{CKey_2_Class,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenUnsized|C_UnsizedLen_PW|C_DataValidOnlyBCD|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

	/*0x44010200 698密码*/
	{C698Key,
/*		表型         |      长度固定 |    长度      |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CL698Key|C_DataValid_NoLimit|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x04000C05 4级密码*/
	{CKey_4_Class,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenUnsized|C_UnsizedLen_PW|C_DataValidOnlyBCD|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x401E0201 报警金额1限值*/
	{CAlam1_Money,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLAlam1_Money|C_DataValid_NoLimit|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsg_ReLocalWarningPara|C_ExtMsgDA_EnergyMetering)},

/*0x401E0202 报警金额2限值*/
	{CAlam2_Money,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLAlam2_Money|C_DataValid_NoLimit|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsg_ReLocalWarningPara|C_ExtMsgDA_EnergyMetering)},

/*0x401F0201 透支金额限值*/
	{COverDraft_Money,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLOverDraft_Money|C_DataValid_NoLimit|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsg_ReLocalWarningPara|C_ExtMsgDA_EnergyMetering)},

/*0x04001006 退费金额 核对是否不需要此行 lzy 20211003*/
	{CReturn_Money,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLReturn_Money|C_DataValidSpecialMethod|C_DV_Return_Money|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_ReturnMoney |C_ExtMsgType_Invalid)},

/*0x41100200 电表运行特征字1*/
	{CMeter_Work_Char1,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLMeter_Work_Char1|C_DataValid_NoLimit|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsg_ReMultiRatesParm|C_ExtMsgDA_MultiRates)},

/*0x20150400 主动上报模式字*/
	{CDrive_Report_Mode,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLDrive_Report_Mode|C_DataValid_NoLimit|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x20150500 主动上报状态字*/
	{CDrive_Report_Type,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLReport_Type|C_DataValidHex_Range|C_DV_HexRange_0_1|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x04001405 主动上报自动复位延时时间*/
	{CRst_ReportState_Timer,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLRst_ReportState_Timer|C_DataValidOnlyBCD|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x40190200 备用套费率电价数据块*/
	{CBackUp_RateFF_Price,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenUnsized|C_UnsizedLen_BackUpRateFFPrice|C_DataValid_NoLimit|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_ProgParm |C_ExtMsgType_Invalid)},

/*0x401B0200 备用套阶梯表*/
	{CBackUp_Ladder_Table,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenUnsized|C_UnsizedLen_BackUpLadder|C_DataValidSpecialMethod|C_DV_Ladder|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_ProgParm |C_ExtMsgType_Invalid)},

/*0x43000302 厂家软件版本号*/
	{CFactory_Softw_Version,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLFactory_Softw_Version|C_DataValid_NoLimit|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x43000304 厂家硬件版本号*/
	{CFactory_Hardw_Version,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLFactory_Hardw_Version|C_DataValid_NoLimit|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x43000301 厂家编号*/
	{CFactory_Number,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLFactory_Number|C_DataValid_NoLimit|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x43000601 支持通信规约1*/
	{CMeter_CommPro1,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLMeter_CommPro1|C_DataValid_NoLimit|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x43000602 支持通信规约2*/
	{CMeter_CommPro2,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLMeter_CommPro2|C_DataValid_NoLimit|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x41110200 软件备案号*/
	{CSoftw_Record_Number,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLSoftw_Record_Number|C_DataValid_NoLimit|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/* 0x44000305		协议一致性块*/
	{CAppProConsistency,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLAppProConsistency|C_DataValid_NoLimit|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*	0x44000306		功能一致性块*/
	{CAppFunConsistency,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLAppFunConsistency|C_DataValid_NoLimit|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*CConAutheMechanism			0x44000500		连接认证机制*/
	{CConAutheMechanism,
/*		表型         |      长度固定 |    长 度                |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLConAutheMechanism|C_DataValidHex_Range|C_DV_HexRange_0_3|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0xF1010200	安全模式是否开启*/
	{CSafeModePara,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLSafeModePara|C_DataValidHex_Range|C_DV_HexRange_0_1|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x43000800		主动上报允许标志*/
	{CAllowAccordUpTell,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLAllowAccordUpTell|C_DataValidHex_Range|C_DV_HexRange_0_1|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x43000700		跟随上报允许标志*/
	{CAllowFollowUpTell,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLAllowFollowUpTell|C_DataValidHex_Range|C_DV_HexRange_0_1|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x43000900		对话允许标志*/
	{CAllowMasterCall,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLAllowMasterCall|C_DataValidHex_Range|C_DV_HexRange_0_1|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x43000200		设备描述符*/
	{CEquipmentDis,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLEquipmentDis|C_DataValid_NoLimit|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},
/*0x43000A00		上报通道*/
	{CUpTellChannel,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenUnsized|C_UnsizedLen_ReportChannel|C_DataValidSpecialMethod|C_DV_ReportChannel|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x04001104 645主动上报模式字 698兼容645增加*/
	{CDrive_Report_Mode_645 ,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLDrive_Report_Mode_645 |C_DataValid_NoLimit|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x04001101 645电表运行特征字1 698兼容645增加*/
	{CMeter_Work_Char1_645,
/*		表型         |      长度固定 |    长度           |   数据有效性判断方法*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLMeter_Work_Char1_645|C_DataValid_NoLimit|
/*      独立编程事件	  |触发后续消息|目的地址*/
	C_HaveIPEvent_Invalid |C_ExtMsg_ReMultiRatesParm|C_ExtMsgDA_MultiRates)},
};
#define	CLen_TB_WrParm		(sizeof(TB_WrParm) / sizeof(Str_WrParmTable))
/***************************************************************************
函数原型 	Is_SetParmData_Ok
函数功能	判断设置参数长度及数据合法性
输入参数	*pV_645Frame				:接收到的数据帧
				*pWrParmTable			:参数表格中数据
输出参数
				pV_645Frame->DataLen						:数据长度，不定长会进行调整
				pV_645Frame->Data[CData_14O_V_645]		:不定长数据会补齐数据
返回参数	C_OK/C_Unauthorized/C_OtherErr/
				/C_Baud_NotModified/C_SeasonNum_OV/C_PeriodNum_OV/C_RateNum_OV
全局变量
函数备注	pV_645Frame不管98还是99，调用本函数时，
				pV_645Frame->DataLen和Data[]区格式，都符合04密级要求
***************************************************************************/
uchar8	Is_SetParmData_Ok( Str_Comm_645 *pV_645Frame, Str_WrParmTable *pWrParmTable )
{
	uchar8	Err;
/*表型是否支持该命令在其他地方已经做了判断*/
/*判断长度是否正确，如果是不定长，补齐数据，修改DataLen*/
	Err = Is_14_DataLenOk(pV_645Frame, pWrParmTable);
	if( Err != C_OK )
	{
		return(Err);
	}
/*判断数据有效性.*/
	Err = Is_14_DataValid(pV_645Frame, pWrParmTable);
	return(Err);
}
/***************************************************************************
函数原型 	Is_14_DataValid
函数功能	判断14命令数据合法性
输入参数	*pV_645Frame				:接收到的数据帧
				*pWrParmTable			:参数设置表格中数据内容
输出参数
返回参数	C_OK/C_OtherErr/
全局变量 	无
函数备注	无
***************************************************************************/
uchar8	Is_14_DataValid(Str_Comm_645 *pV_645Frame,Str_WrParmTable *pWrParmTable)
{
	ulong32	MethodType;
	ulong32	Method;
	uchar8	Range_Min;
	uchar8	Range_Max;
	uchar8	V_ReturnData;
	uchar8	ValidLen;

	MethodType = pWrParmTable->Method & C_DataValidMethodType;
	Method = pWrParmTable->Method & C_DataValidMethod;
	ValidLen = pV_645Frame->DataLen - (CLen_DI + CLen_OpCode + CLen_CommPW);	/*本函数调用前长度合法了*/

/*根据14命令表格中数据有效性判断类型及不同方法进行判断*/
	switch( MethodType )
	{
		case C_DataValid_NoLimit:			/*没有任何限制*/
		{
			return(C_OK);
		}break;

		case C_DataValidHex_Range:			/*通用方法4，Hex，范围AA-BB，Bit13-9，BCD范围方法1-32种*/
		{
			/*绝大多数范围都是单字节数据判断，统一方法判断。其他如2字节单独方法判断*/
			switch( Method )
			{
				case C_DV_HexRange_1_14:
					Range_Min = 1;
					Range_Max = 14;
					break;

				case C_DV_HexRange_1_8:
					Range_Min = 1;
					Range_Max = 8;
					break;

				case C_DV_HexRange_Rates:
					Range_Min = 0;
					Range_Max = C_MaxRatesNum;
					break;

				case C_DV_HexRange_0_20:
					Range_Min = 0;
					Range_Max = 20;
					break;

				case C_DV_HexRange_0_6:
					Range_Min = 0;
					Range_Max = 6;
					break;

				case C_DV_HexRange_1_99:
					Range_Min = 1;
					Range_Max = 99;
					break;

				case C_DV_HexRange_5_20:
					Range_Min = 5;
					Range_Max = 20;
					break;

				case C_DV_HexRange_0_4:
					Range_Min = 0;
					Range_Max = 4;
					break;

				case C_DV_HexRange_5_30:
					Range_Min = 5;
					Range_Max = 30;
					break;

				case C_DV_HexRange_0_60:
					Range_Min = 0;
					Range_Max = 60;
					break;

				case C_DV_HexRange_0_1:
					Range_Min = 0;
					Range_Max = 1;
					break;

				case C_DV_HexRange_0_3:
					Range_Min = 0;
					Range_Max = 3;
					break;

				default:
					return(C_OtherErr);
			}

			V_ReturnData = DV_HexRange( pV_645Frame, Range_Min, Range_Max );
			return(V_ReturnData);
		}break;

		case C_DataValidOnlyBCD:				/*通用方法3，BCD，不作范围限制。Bit12-Bit8值无效*/
		{
			V_ReturnData = PF_Judge_BCD( ValidLen, &(pV_645Frame->Data[CData_14O_V_645]) );
			if(V_ReturnData != C_OK)
			{
				return(C_OtherErr);
			}
			else
			{
				return(C_OK);
			}
		}break;

		case C_DataValidBCD_Range:				/*用方法2，BCD，范围AA-BB 暂时未用到*/
		{
			return(C_OK);
		}break;

		case C_DataValidSpecialMethod:			/*特殊方法*/
		{
			switch( Method )
			{
				case C_DV_Date_Time_645:		/*特殊方法之日期时间判断,645中时间0x04000101、0x04000102*/
					V_ReturnData = DV_Date_Time_645( pV_645Frame );
					return(V_ReturnData);
				case C_DV_Date_Time:			/*特殊方法之日期时间判断*/
					V_ReturnData = DV_Date_Time( pV_645Frame );
					return(V_ReturnData);

				case C_DV_Demand_Cycle:			/*特殊方法之需量周期*/
					V_ReturnData = DV_Demand_Cycle( pV_645Frame );
					return(V_ReturnData);

				case C_DV_Sliding_Time:			/*特殊方法之滑差周期*/
					V_ReturnData = DV_Sliding_Time( pV_645Frame );
					return(V_ReturnData);

				case C_DV_SwitchingTime:		/*特殊方法之切换时间(年月日时分)判断*/
					V_ReturnData = DV_SwitchingTime( pV_645Frame );
					return(V_ReturnData);

				case C_DV_Comm_Address:			/*特殊方法之表地址(BCD,不能全0x99)*/
					V_ReturnData = DV_Comm_Address( &pV_645Frame->Data[CData_14O_V_645] );
					return(V_ReturnData);

				case C_DV_Bps:					/*特殊方法之波特率的设置*/
					V_ReturnData = DV_Bps( pV_645Frame );
					return(V_ReturnData);

				case C_DV_Settle_Day:			/*特殊方法之结算日有效性*/
					V_ReturnData = DV_Settle_Day( pV_645Frame );
					return(V_ReturnData);

				case C_DV_Return_Money:			/*特殊方法之退费金额，这里需要判断够不够退，不够返回错误*/
					V_ReturnData = DV_Return_Money( pV_645Frame );
					return(V_ReturnData);

				case C_DV_Season:				/*特殊方法之时区判断方法*/
					V_ReturnData = DV_Season( pV_645Frame );
					return(V_ReturnData);

				case C_DV_TimePeriod:			/*特殊方法之时段判断方法*/
					V_ReturnData = DV_TimePeriod( pV_645Frame );
					return(V_ReturnData);

				case C_DV_HolidaySet:			/*特殊方法之公共假日的判断方法*/
					V_ReturnData = DV_HolidaySet( pV_645Frame );
					return(V_ReturnData);

				case C_DV_Ladder:				/*特殊方法之阶梯表判断方法*/
					V_ReturnData = DV_Ladder( pV_645Frame );
					return(V_ReturnData);

				case C_DV_RstReport_State:		/*特殊方法之复位主动上报状体字*/
					V_ReturnData = DV_RstReport_State( pV_645Frame );
					return(V_ReturnData);		/*复位主动上报状态字不进行数据合法性判断*/

				case C_DV_ReportChannel:		/*特殊方法之上报通道*/
					V_ReturnData = DV_ReportChannel( pV_645Frame );
					return(V_ReturnData);
				case C_DV_Position:				/*特殊方法之电能表位置信息*/
					V_ReturnData = DV_Position(pV_645Frame);
					return(V_ReturnData);
				default:
					return(C_OtherErr);			/*不可能出现*/
			}
		}break;

		default:								/*不可能*/
			return(C_OtherErr);
	}
}
/***************************************************************************
函数原型 	DV_ReportChannel
函数功能	特殊方法之上报通道
输入参数	*pV_645Frame				:接收到的数据帧
输出参数
返回参数	C_OK/C_OtherErr
全局变量
函数备注	允许设置通道个数为0，最大支持3个，可设置通道485和模块
***************************************************************************/
uchar8	DV_ReportChannel( Str_Comm_645 *pV_645Frame )
{
	uchar8  V_ucNum;
	uchar8  V_ucI, V_ucJ;
	ulong32 V_ulChannelOAD;

	V_ucNum = pV_645Frame->Data[CData_14O_V_645];				/*通道个数*/
	if( V_ucNum > 3 )
	{
		return(C_OtherErr);
	}
	for( V_ucI = 0; V_ucI < V_ucNum; V_ucI++ )
	{
		PF_Buffer4ToUlong32(&pV_645Frame->Data[CData_14O_V_645 + 1 + V_ucI * 4], &V_ulChannelOAD, 4);
		for( V_ucJ = 0; V_ucJ < TB_ChannelOADLen; V_ucJ++ )
		{
			if( V_ulChannelOAD == TB_ChannelOAD[V_ucJ] )
			{
				break;
			}
		}
		if( V_ucJ >= TB_ChannelOADLen )
		{
			return(C_OtherErr);
		}
	}
	return(C_OK);
}
/***************************************************************************
函数原型 	DV_RstReport_State
函数功能	特殊方法之复位主动上报状体字合法性，并将置位可以复位的状态字
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	pV_645Frame->Data[CData_14O_V_645 0-12]	: 需复位的位。注意为1需复位。
返回参数	C_OK/C_OtherErr
全局变量
函数备注	1、复位命令中的位为0需要复位，和已上报中相反
				2、只要复位命令中对应位在已上报状态字中存在，
				则应答正确，否则应答失败
***************************************************************************/
uchar8		DV_RstReport_State(Str_Comm_645 *pV_645Frame)
{
	uchar8	i, j;
	uchar8  RSTData, HaveReportedData;

	if(SV_HaveReportState.Timer == 0)
	{/*要求收到复位命令后，如果再次收到复位命令，应答错误*/
		return(C_Unauthorized);
	}
/*增加判断，复位的位中有没有事件发生但是没有上报过的位，如果有则异常应答*/
	for( j = 0; j < C_ReportStateByteNum; j++ )
	{
		RSTData = pV_645Frame->Data[CData_14O_V_645 + j];
		HaveReportedData = SV_HaveReportState.State[j];
		for( i = 0; i < 8; i++ )							/* 1字节有8位*/
		{
			if( ( ( RSTData & 0x01 ) == 0 )					/*上位机下发的复位数据*/
			 && ( ( HaveReportedData & 0x01 ) == 0 )		/*已经上报过的标志*/
			 && ( SV_ReportNewAddNum[j * 8 + i] != 0 ) )	/*需要上报的数据*/
			{/*对应位已上报*/
				return(C_Unauthorized);
			}
			RSTData >>= 1;
			HaveReportedData >>= 1;
		}
	}
/*将收到复位命令取反和已上报状态位相与，不等于0，表示有位可以复位。*/
/*全部等于0，表示没有位可以复位。*/
	for( i = 0; i < C_ReportStateByteNum; i++ )
	{
		pV_645Frame->Data[CData_14O_V_645 + i] =
			(~pV_645Frame->Data[CData_14O_V_645 + i]) & SV_HaveReportState.State[i];
	}
	return(C_OK);
}

/***************************************************************************
函数原型 	DV_Position
函数功能	地理位置参数合法性判断
输入参数	*pV_645Frame				:接收到的数据帧
输出参数
返回参数	C_OK/C_OtherErr
全局变量
函数备注	、


***************************************************************************/
uchar8	DV_Position( Str_Comm_645 *pV_645Frame )
{
	if( ( ( pV_645Frame->Data[C_Data_OFS_14] != 0 ) && ( pV_645Frame->Data[C_Data_OFS_14] != 1 ) )
	  ||( ( pV_645Frame->Data[C_Data_OFS_14+4] != 0 ) && ( pV_645Frame->Data[C_Data_OFS_14+4] != 1 ) ) )
	{
		return 	C_OtherErr;
	}
	else
	{
		return(C_OK);
	}
}
/***************************************************************************
函数原型 	DV_Date_Time
函数功能	特殊方法之日期时间判断,同时判断修改时间前后是否日期相同,不同则将广播校时时间清零
输入参数	*pV_645Frame				:接收到的数据帧
输出参数
返回参数	C_OK/C_OtherErr
全局变量 	广播校时时间在日期不同时会被清零
函数备注
***************************************************************************/
uchar8	DV_Date_Time( Str_Comm_645 *pV_645Frame )
{
	uchar8	 V_ReturnData;
	uchar8	 V_ucBuffer[CLDate_Time];

	PF_CopyDataBytes(&pV_645Frame->Data[CData_14O_V_645], V_ucBuffer, 7);

	V_ReturnData = PF_DataTimeActive_698( &pV_645Frame->Data[CData_14O_V_645], C_DT_Start_ss, CLDate_Time );
	if(V_ReturnData != C_OK)
	{
		return(C_OtherErr);
	}
    return(C_OK);
}
/***************************************************************************
函数原型 	DV_Date_Time
函数功能	特殊方法之日期时间判断,同时判断修改时间前后是否日期相同,不同则将广播校时时间清零
输入参数	*pV_645Frame				:接收到的数据帧
输出参数
返回参数	C_OK/C_OtherErr
全局变量 	广播校时时间在日期不同时会被清零
函数备注	645协议处理数据格式需要再核对 本次修改时间格式只保证数据不溢出 lzy 20211023
***************************************************************************/
uchar8		DV_Date_Time_645(Str_Comm_645 *pV_645Frame)
{
	uchar8	V_ReturnData;
	uchar8	V_ucBuffer[CLDate_Time];
	ulong32 V_ulDI645=0;

	PF_Buffer4ToUlong32(&pV_645Frame->Data[C_O_DI0], &V_ulDI645, 4);

	if( ( V_ulDI645 == CDate_Week_Time_645 ) || ( V_ulDI645 == CTime ) )
	{
		PF_CopyDataBytes( &pV_645Frame->Data[CData_14O_V_645], V_ucBuffer, 7 );
	}
	else
	{
		PF_CopyDataBytes( &pV_645Frame->Data[CData_14O_V_645], V_ucBuffer, CLTime );
		PF_CopyDataBytes( &pV_645Frame->Data[CData_14O_V_645 + CDate_WW_Time_DD_O], &V_ucBuffer[CDate_Time_DD_O], CLTime );
		PF_CopyDataBytes( &V_ucBuffer[CDate_Time_DD_O], &pV_645Frame->Data[CData_14O_V_645 + CDate_WW_Time_WW_O],  CLTime );
		pV_645Frame->Data[CData_14O_V_645 + CDate_WW_Time_YY_O] = 0x20;
	}

	V_ReturnData = PF_DataTimeActive( V_ucBuffer, C_DT_Start_ss, CLDate_Time );
	if( V_ReturnData != C_OK )
	{
		return(C_OtherErr);
	}
    return(C_OK);
}

/***************************************************************************
函数原型 	DV_Demand_Cycle
函数功能	特殊方法之需量周期
输入参数	*pV_645Frame				:接收到的数据帧
输出参数
返回参数	C_OK/C_OtherErr
全局变量
函数备注	固定为5、10、15、30、60
***************************************************************************/
uchar8	DV_Demand_Cycle( Str_Comm_645 *pV_645Frame )
{
	switch( pV_645Frame->Data[CData_14O_V_645] )
	{
		case	5:
		case	10:
		case	15:
		case	30:
		case	60:
			return(C_OK);
		default:
			return(C_OtherErr);
	}
}
/***************************************************************************
函数原型 	DV_Sliding_Time
函数功能	特殊方法之滑差周期
输入参数	*pV_645Frame				:接收到的数据帧
输出参数
返回参数	C_OK/C_OtherErr
全局变量
函数备注	1、2、3、5
***************************************************************************/
uchar8	DV_Sliding_Time( Str_Comm_645 *pV_645Frame )
{
	switch( pV_645Frame->Data[CData_14O_V_645] )
	{
		case	1:
		case	2:
		case	3:
		case	5:
		case	10:
			return(C_OK);
		default:
			return(C_OtherErr);
	}
}

/***************************************************************************
函数原型 	DV_SwitchingTime
函数功能	特殊方法之切换时间(年月日时分)判断
输入参数	*pV_645Frame				:接收到的数据帧
输出参数
返回参数	C_OK/C_OtherErr
全局变量
函数备注
***************************************************************************/
uchar8	DV_SwitchingTime( Str_Comm_645 *pV_645Frame )
{
	uchar8	V_ReturnData;

	V_ReturnData = PF_DataTimeActive_698(&pV_645Frame->Data[CData_14O_V_645 + 1], C_DT_Start_mm, 5);

	if( ( pV_645Frame->Data[CData_14O_V_645] != 0xFF )
   	 && ( pV_645Frame->Data[CData_14O_V_645] >=0x60 ) )
	{
		return(C_OtherErr);
	}
	if( ( pV_645Frame->Data[CData_14O_V_645+5] == 0xFF )
	 && ( pV_645Frame->Data[CData_14O_V_645+6] == 0xFF ) )		/*年为全FF*/
	{
		V_ReturnData = C_OtherErr;
	}
	if(V_ReturnData != C_OK)
	{
		if( PF_Is_Buf_AllFixedData( &pV_645Frame->Data[CData_14O_V_645 + 1], 0x00, 5 ) == C_OK ) /*切换时间可设置0x00*/
		{
			return(C_OK);
		}
		if( PF_Is_Buf_AllFixedData( &pV_645Frame->Data[CData_14O_V_645 + 1], 0x63, 5 ) == C_OK )	/*切换时间可设置0x99*/
		{
			return(C_OK);
		}
		if( PF_Is_Buf_AllFixedData( &pV_645Frame->Data[CData_14O_V_645 + 1], 0xFF, 5 ) == C_OK ) /*切换时间可设置0xFF*/
		{
			return(C_OK);
		}
		return(C_OtherErr);
	}
	else
	{
		return(C_OK);
	}

}

/***************************************************************************
函数原型 	DV_Comm_Address
函数功能	特殊方法之表地址(BCD,不能全0x99)
输入参数	*pComm_Address				:设置的通信地址开始位置
输出参数
返回参数	C_OK/C_OtherErr
全局变量
函数备注
***************************************************************************/
uchar8 DV_Comm_Address( uchar8 *pComm_Address )
{
	uchar8 V_ReturnData;
	uchar8 i;

/*判断是否为BCD*/
	V_ReturnData = PF_Judge_BCD( CLComm_Address, pComm_Address );
	if( V_ReturnData != C_OK )
	{
		return(C_OtherErr);
	}
/*判断是否为全99*/
	for(i = 0; i < CLComm_Address; i ++)
	{
		if(pComm_Address[i] != 0x99)
		{
			return(C_OK);
		}
	}
	return(C_OtherErr);
}

/***************************************************************************
函数原型 	DV_Bps
函数功能	特殊方法之波特率的设置
输入参数	*pV_645Frame				:接收到的数据帧
输出参数
返回参数	C_OK/C_Baud_NotModified
全局变量
函数备注	波特率设置只要不是需要波特率都应答C_Baud_NotModified
***************************************************************************/
uchar8	DV_Bps( Str_Comm_645 *pV_645Frame )
{
	uchar8	CommNo;
	switch( pV_645Frame->DI )
	{
		case		CMod_InFr_Baud:
			CommNo = C_IR;
			break;
		case		COne485_Baud:
			CommNo = C_RS485_1;
			break;
		case		CTwo485_Baud:
			CommNo = C_RS485_2;
			break;
		case		CModular_Baud:
		case		CModular_BaudConsult:
			CommNo = C_Module;
			break;
		default:
			return(C_OtherErr);
	}

	if( Is_CommBPS_OK( CommNo, pV_645Frame->Data[CData_14O_V_645] ) == C_OK )
	{
		SV_SetBPS_Flag = C_OK;				/*通知调度，设置BPS啦*/
		return(C_OK);
	}
	else
	{
		return(C_Baud_NotModified);
	}
}

/***************************************************************************
函数原型 	DV_Settle_Day
函数功能	特殊方法之结算日有效性
输入参数	*pV_645Frame				:接收到的数据帧
输出参数
返回参数	C_OK/C_OtherErr
全局变量
函数备注	第1结算日，1-28日，0-23；第2、3结算日增加可设为全0，全FF，全99
***************************************************************************/
uchar8	DV_Settle_Day( Str_Comm_645 *pV_645Frame )
{
/*第2结算日或第3结算日，可设全0，全FF，全99*/
	if( ( pV_645Frame->DI == CSettle_Day2 )
	 || ( pV_645Frame->DI == CSettle_Day3 ) )
	{
		if( ( pV_645Frame->Data[CData_14O_V_645] == 0 )
		 && ( pV_645Frame->Data[CData_14O_V_645 + 1] == 0 ) )
		{
			return(C_OK);
		}
		if( ( pV_645Frame->Data[CData_14O_V_645] == 0x63 )
		 && ( pV_645Frame->Data[CData_14O_V_645 + 1] == 0x63 ) )
		{
			return(C_OK);
		}
		if( ( pV_645Frame->Data[CData_14O_V_645] == 0xFF )
		 && ( pV_645Frame->Data[CData_14O_V_645 + 1] == 0xFF ) )
		{
			return(C_OK);
		}
	}
/*小时必须是小于24*/
	if( pV_645Frame->Data[CData_14O_V_645 + 1] > 23 )
	{
		return(C_OtherErr);
	}
/*天必须小于29且不为零*/
	if( ( pV_645Frame->Data[CData_14O_V_645] > 28 )
	 || ( pV_645Frame->Data[CData_14O_V_645] == 0 ) )
	{
		return(C_OtherErr);
	}
	return(C_OK);
}

/***************************************************************************
函数原型 	DV_Return_Money
函数功能	退费金额有效性判断
输入参数	*pV_645Frame				:接收到的数据帧
输出参数
返回参数	C_OK/C_OtherErr
全局变量
函数备注	hex，并且必须小于钱包金额
***************************************************************************/
uchar8	DV_Return_Money( Str_Comm_645 *pV_645Frame )
{
	uchar8	V_ReturnData;
	uchar8	ChargeBal_Hex_Cent[CLChargeBal_Hex_Cent];
    ushort16 V_usDataLen, V_usDataEncode[30] = {0x00};

/*读电能模块接口函数，剩余金额	*/
	V_usDataLen = CLChargeBal_Hex_Cent;
	V_ReturnData = InF_GetData_ObjectManage(CChargeBal_Hex_Cent, ChargeBal_Hex_Cent, &V_usDataLen, V_usDataEncode);

	if(V_ReturnData != C_OK)
	{/*读不出*/
		return(C_OtherErr);
	}
/*钱包同步*/
	InF_S_UpdataChargeBalInESAM(ChargeBal_Hex_Cent);
/*同步后，再读数据层剩余金额。因为同步中，可能会以ESAM为准，扣减数据层*/
	V_usDataLen = CLChargeBal_Hex_Cent;
	InF_GetData_ObjectManage(CChargeBal_Hex_Cent, ChargeBal_Hex_Cent, &V_usDataLen, V_usDataEncode);
/*比较*/
	V_ReturnData = PF_Campare_Data(&pV_645Frame->Data[CData_14O_V_645], ChargeBal_Hex_Cent, CLChargeBal_Hex_Cent);
	if( ( V_ReturnData == C_GreaterThan )
	 || ( PF_Is_Buf_AllFixedData(ChargeBal_Hex_Cent, 0x00, CLChargeBal_Hex_Cent ) == C_OK ) )
	{/*C_GreaterThan表示数组1大于数组2*/
		return(C_OtherErr);
	}
	else
	{
		return(C_OK);
	}
}

/***************************************************************************
函数原型 	DV_Season
函数功能	特殊方法之时区判断方法
输入参数	*pV_645Frame				:接收到的数据帧
输出参数
返回参数	C_OK/C_OtherErr
全局变量
函数备注	hex；MM：1-12；DD：1-28；
				NN：1-8；数据，
				调用本函数时，数据长度合法，且已数据补齐
***************************************************************************/
uchar8	DV_Season( Str_Comm_645 *pV_645Frame )
{
	uchar8	i;
	uchar8	TZone_Num;
	uchar8	*pPreData;
	uchar8	*pCurData;

/*判断数据有效性，判断方法见函数备注*/
/*首先判第一个有效性*/
	if( Is_TZone_Data_OK( &pV_645Frame->Data[CData_14O_V_645] ) != C_OK )
	{
		return(C_OtherErr);
	}
	TZone_Num = CLFirst_TZone_Data / 3;
	pPreData = &pV_645Frame->Data[CData_14O_V_645 - 3];
	pCurData = &pV_645Frame->Data[CData_14O_V_645];
	for( i = 1; i < TZone_Num; i++ )
	{
		/*调整指针*/
		pPreData = pPreData + 3;
		pCurData = pCurData + 3;

		if( Is_TZone_Data_OK(pCurData) != C_OK )
		{
			return(C_OtherErr);
		}
		else
		{
			continue;
		}
	}
	return(C_OK);
}
/***************************************************************************
函数原型 	Is_TZone_Data_OK
函数功能	判断3字节的时区数据是否合法
输入参数	*pTZone_Data				:连续3字节的时区数据
										:数据顺序调整为3字节按照NNDDMM排列
输出参数
返回参数	C_OK/C_OtherErr
全局变量
函数备注	MM：1-12；DD：1-28；NN：1-8。
***************************************************************************/
uchar8	Is_TZone_Data_OK( uchar8	*pTZone_Data )
{
	uchar8	V_ucData[3];

	PF_OneDataReversed(pTZone_Data, V_ucData,3);							/*数据顺序调整*/

	if( ( V_ucData[0] < 0x01 )||( V_ucData[0] > 0x08 ) )					/*NN：1-8*/
	{
		return(C_OtherErr);
	}

	if( PF_DataTimeActive_698( &V_ucData[1], C_DT_Start_DD, 2 ) != C_OK )	/*DDMM合法性判断*/
	{
			return(C_OtherErr);
	}
	return(C_OK);
}

/***************************************************************************
函数原型 	DV_TimePeriod
函数功能	特殊方法之时段判断方法
输入参数	*pV_645Frame				:接收到的数据帧
输出参数
返回参数	C_OK/C_OtherErr/C_RateNum_OV
全局变量
函数备注	hex；hh：00-23；mm：0-59；
				NN：1-4；数据，hhmm应该后一个大于等于前一个；
				大于时，一定大于等于15min .注意最后可以以00 00 00×N补充
***************************************************************************/
uchar8	DV_TimePeriod( Str_Comm_645 *pV_645Frame )
{
	uchar8	V_ReturnData;
	uchar8	i;
	uchar8	TimePeriod_Num;
	uchar8	ZeroFlag = 0;
	uchar8	*pPreData;
	uchar8	*pCurData;
	ushort16	CurMin;
	ushort16	PreMin;
	ulong32	HexTemp;
	uchar8	V_ucData[CLFirst_TZone_1PT_Data + 3 + 3];			/*第一个+3是为了做地址减3处理，第2个+3是为了保存第15个时段*/

	TimePeriod_Num = CLFirst_TZone_1PT_Data / 3;
	for( i = 0; i < TimePeriod_Num; i++ )
	{
		PF_OneDataReversed(&pV_645Frame->Data[CData_14O_V_645 + i * 3], V_ucData +3 + i * 3, 3);	/*数据顺序调整*/
	}

/*第1个时段表+24小时，用于计算最后一个时段和第一个时段时间的间隔*/
	V_ucData[CLFirst_TZone_1PT_Data + 3] = V_ucData[3];
	V_ucData[CLFirst_TZone_1PT_Data + 3 + 1] = V_ucData[4];
	V_ucData[CLFirst_TZone_1PT_Data + 3 + 2] = V_ucData[5] + 24;

/*判断数据有效性，判断方法见函数备注*/
/*首先判第一个有效性*/
	V_ReturnData = Is_TimePeriod_Data_OK( V_ucData + 3 );
	if( V_ReturnData != C_OK )
	{
		return(V_ReturnData);
	}

	pPreData = V_ucData;
	pCurData = V_ucData + 3;				/*第一个时段表首地址*/

	/*取第一个时段表的hhmm作为上一个分钟。用于计算15min*/
	HexTemp = pCurData[2];					/*上1个小时*/
	PreMin = (ushort16)(HexTemp * 60 );
	HexTemp = pCurData[1];					/*上1个分钟*/
	PreMin = PreMin + (ushort16)HexTemp;

	for( i = 1; i< (TimePeriod_Num + 1); i++)
	{
		/*调整指针*/
		pPreData = pPreData + 3;
		pCurData = pCurData + 3;
		if( ZeroFlag )
		{
			/*数据已经是0了，则后面必须全部是0.(因为循环从第2个时区开始)*/
			if( ( pCurData[0] != 0 ) || ( pCurData[1] != 0 ) || ( pCurData[2] != 0 ) )
			{
				return(C_OtherErr);
			}
			continue;
		}
		else
		{
			/*下一个必须比前一个大于等于。如果小于必须全0，置0标志*/
			V_ReturnData = PF_Campare_Data( &pPreData[1], &pCurData[1], 2 );		/*比2字节hhmm大小*/
			if( V_ReturnData == C_Equal )
			{
				if( ( pCurData[1] == 0 ) && ( pCurData[2] == 0 ) )
				{
					if( pCurData[0] == 0 )
					{
						ZeroFlag = 1;
						continue;			/*只有第一个日时段参数有效，且第一个日时段时间为00:00*/
					}
				}
				/*hhmm相等，则NN也必须相等*/
				if( pPreData[0] != pCurData[0] )
				{
					return(C_OtherErr);
				}
				continue;					/*没有要求等于之后，后面必须全部等于*/
			}
			else if( V_ReturnData == C_GreaterThan )
			{
				/*前一个比后一个大，只有后一个是全0 的可能。*/
				if( ( pCurData[0] != 0 ) || ( pCurData[1] != 0 ) || ( pCurData[2] != 0 ) )
				{
					return(C_OtherErr);
				}
				ZeroFlag = 1;
				continue;
			}
			else if( V_ReturnData == C_LessThan )
			{
				/*前一个比后一个小，去判断后一个数据合法性*/
				if( TimePeriod_Num == i )/*第15个时段由第1个时段加24小时计算所得，不判断合法性，*/
				{
					V_ReturnData = C_OK;
				}
				else
				{
					V_ReturnData = Is_TimePeriod_Data_OK(pCurData);
				}
				if( V_ReturnData != C_OK )
				{
					return(V_ReturnData);
				}
				else
				{
					/*合法，去判断后一个比前一个大于15min*/
					HexTemp = pCurData[2];					/*当前小时*/
					CurMin = (ushort16)( HexTemp * 60 );
					HexTemp = pCurData[1];					/*当前分钟*/
					CurMin = CurMin + (ushort16)HexTemp;
					if( ( CurMin - PreMin ) < 15 )
					{
						return(C_OtherErr);
					}
					PreMin = CurMin;
					continue;
				}
			}
			else
			{
				/*不可能到这里*/
				return(C_OtherErr);
			}
		}
	}
    return(C_OK);
}

/***************************************************************************
函数原型 	Is_TimePeriod_Data_OK
函数功能	单个时段表数据是否正确
输入参数	*pTimePeriod_Data				:连续3字节的时段数据
											:3字节按照NN mm hh排列
输出参数
返回参数	C_OK/C_OtherErr/C_RateNum_OV
全局变量
函数备注	hh：00-23；mm：0-59；NN：1-12，已判过BCD了。
***************************************************************************/
uchar8		Is_TimePeriod_Data_OK(uchar8	*pTimePeriod_Data)
{
/*NN：1-4*/
	if( ( *pTimePeriod_Data < 0x01 )
	 || ( *pTimePeriod_Data > C_MaxRatesNum ) )
	{
		return(C_RateNum_OV);
	}

/*mm：0-59*/
	if( *( pTimePeriod_Data + 1 ) > 59)
	{
		return(C_OtherErr);
	}

/*hh：0-23*/
	if( *( pTimePeriod_Data + 2 ) > 23 )
	{
		return(C_OtherErr);
	}
	return(C_OK);
}

/***************************************************************************
函数原型 	DV_HolidaySet
函数功能	特殊方法之公共假日的判断方法
输入参数	*pV_645Frame				:接收到的数据帧
输出参数
返回参数	C_OK/C_OtherErr
全局变量
函数备注	仅判断如果年月日0时，时段表号也为0，其他不作要求
            增加周，年月日为0，周也为0，时段表号也为0 20190411
***************************************************************************/
uchar8	DV_HolidaySet( Str_Comm_645 *pV_645Frame )
{
	uchar8 V_i;
	uchar8 V_ucLen;

	if( ( PF_Is_Buf_AllFixedData(&pV_645Frame->Data[CData_14O_V_645], 0x00,  6) == C_OK )		/*允许设置全0*/
	|| ( PF_Is_Buf_AllFixedData(&pV_645Frame->Data[CData_14O_V_645], 0xFF,  6) == C_OK ) )		/*允许设置全F*/
	{
		return(C_OK);
	}
	for( V_i = 0; V_i < 5; V_i++ )		/*年在高字节*/
	{
		if( pV_645Frame->Data[CData_14O_V_645 + 5 - 1 - V_i] != 0xFF )
		{
			break;
		}
	}
	if( V_i == 0 )						/*数据全部有效*/
	{
		V_ucLen = 4;
		if( PF_Cal_Week_698(&pV_645Frame->Data[CData_14O_V_645 + 1]) != pV_645Frame->Data[CData_14O_V_645] )	/*判断周合法性*/
		{
			return(C_OtherErr);
		}
	}
	else if( V_i == 2 )					/*年无效*/
	{
		V_ucLen = 2;
	}
	else if( V_i == 3 )					/*年、月无效*/
	{
		V_ucLen = 1;
	}
	else
	{
		return(C_OtherErr);
	}
	if( pV_645Frame->Data[CData_14O_V_645] > 6 )		/*周不能大于6*/
	{
		return(C_OtherErr);
	}
	if( ( pV_645Frame->Data[CData_14O_V_645 + 5] > 8 )
	||( pV_645Frame->Data[CData_14O_V_645 + 5] < 1 ) )/*时段表号*/
	{
		return(C_OtherErr);
	}
	if( PF_DataTimeActive_698( &pV_645Frame->Data[CData_14O_V_645 + 1], C_DT_Start_DD, V_ucLen ) != C_OK )		/*日期合法性判断*/
	{
		return(C_OtherErr);
	}
	return(C_OK);
}

/**************************************************************************
函数原型 	DV_Ladder
函数功能	特殊方法之阶梯表判断方法
输入参数	*pV_645Frame				:接收到的数据帧
输出参数
返回参数	C_OK/C_OtherErr
全局变量
函数备注
***************************************************************************/
uchar8	DV_Ladder( Str_Comm_645 *pV_645Frame )
{
	if( InF_DV_Ladder( &pV_645Frame->Data[CData_14O_V_645] ) != C_OK )
	{
		return(C_OtherErr);
	}
	return(C_OK);
}

/***************************************************************************
函数原型 	InF_DV_Ladder
函数功能	特殊方法之阶梯表判断方法
输入参数	*pLadderData				:阶梯表数据
输出参数 							:数据格式固定为4*6阶梯值
										4*7阶梯电价，3*4年阶梯结算日
返回参数	C_OK/C_OtherErr
全局变量
函数备注	三类数据均要求为BCD码。阶梯值要求后一个比前一个大或等于。
				阶梯电价相互间没有关系
				年结算日：MM：1-12；DD：1-28；hh：0-23。且后一个比前一个大。或者为999999
				这里判断一旦等于，后面全等。一旦为999999，后面全部为999999
***************************************************************************/
#define	YSettle_O		52
#define	DataEqual     	1
#define	DataAllZero     2
uchar8	InF_DV_Ladder( uchar8	*pLadderData )
{
	uchar8	V_ReturnData;
	uchar8	i;
	uchar8	EqualFlag;
	uchar8	*pPreData;
	uchar8	*pCurData;
	uchar8	All00Flag = 0;

/*判断阶梯值数据的合理性。*/
	pPreData = pLadderData - 4;										/*一进循环立刻先调整指针。*/
	pCurData = pLadderData;
	EqualFlag = 0;
	if( PF_Is_Buf_AllFixedData(pCurData, 0x00, 4) == C_OK )			/*全0*/
	{
		All00Flag = 0x68;
	}
	for( i = 1; i < 6; i++ )										/*从第2个阶梯值开始，要求后面一个必须大于等于前一个*/
	{
		pPreData = pPreData + 4;
		pCurData = pCurData + 4;
		V_ReturnData = PF_Campare_Data( pPreData, pCurData, 4 );	/*比较前后值*/
		if( EqualFlag == DataEqual )
		{	/*前面有相等了，那么后面必须全等*/
			if( V_ReturnData != C_Equal )
			{
				if( PF_Is_Buf_AllFixedData( pCurData, 0x00,  4) == C_OK )
				{
					EqualFlag = DataAllZero;
					continue;
				}
				return(C_OtherErr);
			}
			continue;
		}
		else if( EqualFlag == DataAllZero )
		{	/*前面有相等了，那么后面必须全等*/
			if( V_ReturnData != C_Equal )
			{
				return(C_OtherErr);
			}
			continue;
		}
		else
		{
			if( V_ReturnData == C_Equal )
			{	/*值相等*/
				EqualFlag = DataEqual;
				continue;
			}
			else if( V_ReturnData == C_GreaterThan )
			{	/*前一个比后一个大*/
				if( PF_Is_Buf_AllFixedData( pCurData, 0x00,  4) == C_OK )
				{
					EqualFlag = DataAllZero;
					continue;
				}
				return(C_OtherErr);
			}
			else
			{
				continue;
			}
		}
	}
/*阶梯电价仅作BCD判断，不做其他判断了。*/

/*年结算日*/
	pPreData = &pLadderData[YSettle_O - 3];					/*一进循环立刻先调整指针。*/
	pCurData = &pLadderData[YSettle_O];
	EqualFlag = 0;

	/*判断第1个年结算日*/
	V_ReturnData = Is_YSettle_OK(pCurData);
	if( V_ReturnData == C_YSettle_All99 )
	{
		EqualFlag = 1;										/*第1个为全99，则认为相邻数据相等了，要求后面数据必须等于前一个数据。*/
	}														/*即要求后面数据也为全99了。*/
	else if( V_ReturnData != C_OK )
	{
		return(V_ReturnData);
	}

	for( i = 1; i < 4; i++ )								/*4个年结算日*/
	{
		pPreData = pPreData + 3;
		pCurData = pCurData + 3;

		V_ReturnData = Is_YSettle_OK(pCurData);
		if( ( V_ReturnData != C_OK ) && ( V_ReturnData != C_YSettle_All99 ) )
		{/*本次数据异常*/
			return(V_ReturnData);
		}
		if( V_ReturnData == C_YSettle_All99 )
		{
			EqualFlag++;									/*第1个为全99，则认为相邻数据相等了，要求后面数据必须等于前一个数据。*/
		}													/*即要求后面数据也为全99了。*/
	}
	if( ( EqualFlag == 4 ) && ( All00Flag != 0x68 ) )		/*4个结算日均无效，但是阶梯表数据有效，应答其他错误*/
	{
		return(C_OtherErr);
	}
	return(C_OK);
}

/***************************************************************************
函数原型 	Is_YSettle_OK
函数功能	判断年结算日数据是否正确
输入参数	*pYSettle				:连续3字节年结算日首地址

输出参数
返回参数	C_OK 				:数据正常
				C_YSettle_All99		:数据正确，但为全99
				C_OtherErr			:数据错误
全局变量 	无
函数备注	MM：1-12；DD：1-28；hh：0-23
				年结算日BCD已在程序外作判断。
***************************************************************************/
uchar8	Is_YSettle_OK( uchar8 *pYSettle )
{
/*判断是否为全99*/
	if( ( PF_Is_Buf_AllFixedData(pYSettle, 0x00,  3) == C_OK )		/*允许设置全0*/
	 || ( PF_Is_Buf_AllFixedData(pYSettle, 0x63,  3) == C_OK )		/*允许设置全9*/
	 || ( PF_Is_Buf_AllFixedData(pYSettle, 0xFF,  3) == C_OK ) )	/*允许设置全F*/
	{
		return(C_YSettle_All99);
	}
/*hh 0-23*/
	if(pYSettle[2] > 23)
    {
        return(C_OtherErr);
    }
/*DD 1-28*/

    if ( ( pYSettle[0] != 0x63 ) && ( pYSettle[0] != 0xFF ) )   /*如果 月是无效（0x99或0xFF）*/
    {
        if( ( pYSettle[1] < 1 ) || ( pYSettle[1] > 28 ) ) 		/*日合法性判断 1-28 */
        {
            return(C_OtherErr);
        }
    }
    else   /*月有效，日可以是1-28，或0x99或0xFF*/
    {
        if ( ( ( pYSettle[1] < 1 ) || ( pYSettle[1] > 28 ) )   && ( pYSettle[1] != 0x63 ) && ( pYSettle[1] != 0xFF ) )    /*费控流程会测999902情况*/
        {
            return(C_OtherErr);
        }
    }

/*MM 1-12*/
	if( ( ( pYSettle[0] < 1 ) || ( pYSettle[0] > 12 ) ) && ( pYSettle[0] != 0x63 ) && ( pYSettle[0] != 0xFF ) )
    {
        return(C_OtherErr);
    }

	return(C_OK);
}
/***************************************************************************
函数原型 	DV_HexRange
函数功能	数据为BCD，且范围在BCDMin<=   数据<= BCDMax之间
输入参数	*pV_645Frame				:接收到的数据帧
				HexMin/HexMax			:最小值/最大值
输出参数
返回参数	C_OK/C_OtherErr
全局变量 	无
函数备注	*pV_645Frame	中有效数据长度为1
***************************************************************************/
uchar8		DV_HexRange(Str_Comm_645 *pV_645Frame,uchar8	HexMin,uchar8 HexMax)
{

	if( ( pV_645Frame->Data[CData_14O_V_645] < HexMin )
	 || ( pV_645Frame->Data[CData_14O_V_645] > HexMax ) )
	{
		if( pV_645Frame->DI == CYear_Zone_Num )			/*年时区数*/
		{
			return(C_SeasonNum_OV);
		}
		else if( pV_645Frame->DI == CDay_Time_Num )		/*日时段数*/
		{
			return(C_PeriodNum_OV);
		}
		else if( pV_645Frame->DI == CRate_Num )			/*费率数*/
		{
			return(C_RateNum_OV);
		}
		else
		{
			return(C_OtherErr);
		}
	}
	else
	{
		return(C_OK);
	}
}

/*******************************************************************************
函数原型 Is_14_DataLenOk
函数功能	 判断14命令长度的合法性，如果不定长，则补齐数据并修改接收帧长度
输入参数	 *pV_645Frame				:接收到的数据帧
		 *pWrParmTable				:参数设置表格中数据内容
输出参数 pV_645Frame->DataLen/Data[]	:补齐数据时修改
返回参数	 C_OK/C_OtherErr/C_Unauthorized
全局变量 无
函数备注	 对于14命令修改密码，这里还判断权限合理性。
*******************************************************************************/
uchar8	Is_14_DataLenOk( Str_Comm_645 *pV_645Frame, Str_WrParmTable *pWrParmTable )
{
	uchar8	ValidLen;
	uchar8	V_ReturnData;
	ulong32	UnsizedLen_Method;
	uchar8	V_ucFixedLen;
	uchar8	V_ucI;
    uchar8  V_ucTemp[100];

/*长度必须是合理*/
	if( pV_645Frame->DataLen > ( CLen_DI + CLen_OpCode + CLen_CommPW ) )
	{
		ValidLen = pV_645Frame->DataLen - ( CLen_DI + CLen_OpCode + CLen_CommPW );
	}
	else
	{
		return(C_OtherErr);
	}

/*取长度判断方法	*/
	if( ( pWrParmTable->Method & C_DataLenFixedFlag ) == C_DataLenFixed_OK )
	{
		/*定长*/
		if( ( (uchar8)(pWrParmTable->Method & C_DataLenFixed) ) == ValidLen )
		{
			return(C_OK);
		}
		else if( ( (uchar8)(pWrParmTable->Method & C_DataLenFixed) ) < ValidLen )
		{
			return(C_OverStep_DAR);
		}
		else
		{
			return(C_OtherErr);
		}
	}
	else
	{/*不定长*/
		if( ( pWrParmTable->Method & C_IsAddFixedDataLen ) == C_AddFixedDataLen )	/*不定长高位统一补0*/
		{
			V_ucFixedLen = (uchar8)(pWrParmTable->Method & C_DataLenFixed);
			if( ValidLen <= V_ucFixedLen )
			{
                PF_CopyDataBytes(&pV_645Frame->Data[CData_14O_V_645],V_ucTemp,ValidLen);
                PF_CopyDataBytes(V_ucTemp,&(pV_645Frame->Data[C_Data_OFS_14+V_ucFixedLen-ValidLen]),ValidLen);
				for( V_ucI = 0; V_ucI < (V_ucFixedLen - ValidLen); V_ucI++ )
				{
					pV_645Frame->Data[CData_14O_V_645 + V_ucI] = 0;
				}
				pV_645Frame->DataLen = V_ucFixedLen + (CLen_DI + CLen_OpCode + CLen_CommPW);
			}
			else
			{
				return(C_OtherErr);
			}
		}
		else
		{/*不定长根据特殊要求补数据*/
			UnsizedLen_Method = pWrParmTable->Method & C_UnsizedLen_Method;
			switch(UnsizedLen_Method)
			{
				case C_UnsizedLen_PW:					/*密码，需要判断长度及密码设置权限合理性，并去除密码PA，目前程序中未做处理，后续调整645协议时，注意核对 lzy 20211012*/
					V_ReturnData = IsPW_Len_Auth(pV_645Frame);
					return(V_ReturnData);
				case C_UnsizedLen_S_PT:					/*时段、时区表的判断，不满14*3，补足*/
					V_ReturnData = Adjust_UnsizedLen_S_PT(pV_645Frame);
					return(V_ReturnData);
				case C_UnsizedLen_Date:					/*日期设置，判断长度是否正确且需调整数据为040001FD格式. 后续调整645协议时，注意核对 lzy 20211012*/
					V_ReturnData = Adjust_DateLen(pV_645Frame);
					return(V_ReturnData);
				case C_UnsizedLen_Time:					/*时间设置，判断长度是否正确且需调整数据为040001FD格式. 后续调整645协议时，注意核对 lzy 20211012*/
					V_ReturnData = Adjust_TimeLen(pV_645Frame);
					return(V_ReturnData);
				case C_UnsizedLen_BackUpLadder:			/*备用套阶梯表参数设置，长度大于63字节，需要特殊处理*/
					V_ReturnData = Adjust_BackUpLadderLen(pV_645Frame);
					return(V_ReturnData);
				case C_UnsizedLen_BackUpRateFFPrice:	/*设置备用套费率电价参数*/
					V_ReturnData = Adjust_BackUpRateFFPriceLen(pV_645Frame);
					return(V_ReturnData);
				case C_UnsizedLen_ReportChannel:		/*上报通道长度不足13字节，补齐*/
					V_ReturnData = Adjust_ReportChannel(pV_645Frame);
					return(V_ReturnData);
				default:								/*其他值是不可能的。*/
					return(C_OtherErr);
			}
		}
	}
	return(C_OK);
}

/***************************************************************************
函数原型 	Adjust_DateLen
函数功能	判断长度是否正确且需调整数据为0400010C格式
输入参数	*pV_645Frame			:接收到645帧
输出参数 	pV_645Frame->DataLen/Data[]	:补齐数据时修改
返回参数	C_OK/C_OtherErr/
全局变量
函数备注
***************************************************************************/
uchar8		Adjust_DateLen(Str_Comm_645 *pV_645Frame)
{
	uchar8		Date_Time[CLDate_Time];		/*最早是调整成Date_Time，后经讨论调整成CDate_Week_Time格式，但变量名不修改*/
	ushort16	DataLen, V_usDataEncode;

/*判断长度*/
	if(pV_645Frame->DataLen != (CLDate_Week + CLen_DI + CLen_OpCode + CLen_CommPW))
	{
		return(C_OtherErr);
	}
/*数据调整,长度,标识码(用于数据层的写)*/
	DataLen = CLDate_Time;
	InF_Read_Data(CDate_Time, Date_Time, &DataLen, &V_usDataEncode);

	PF_CopyDataBytes(&pV_645Frame->Data[CData_14O_V_645], &Date_Time[CDate_WW_Time_WW_O], CLDate_Week);

	if(PF_DataTimeActive(&Date_Time[C_ss_O], C_DT_Start_ss, CLTime) != C_OK)	/*时间非法，默认00:00:00*/
	{
		Date_Time[C_ss_O] = 0x00;
		Date_Time[C_mm_O] = 0x00;
		Date_Time[C_hh_O] = 0x00;
	}

	PF_CopyDataBytes(Date_Time, &pV_645Frame->Data[CData_14O_V_645], CLDate_Time);

	pV_645Frame->DataLen = CLDate_Time + CLen_DI + CLen_OpCode + CLen_CommPW;

	pV_645Frame->DI = CDate_Time;
	return(C_OK);
}

/***************************************************************************
函数原型 	Adjust_TimeLen
函数功能	判断长度是否正确且需调整数据为0400010C格式
输入参数	*pV_645Frame			:接收到645帧
输出参数 	pV_645Frame->DataLen/Data[]	:补齐数据时修改
返回参数	C_OK/C_OtherErr/
全局变量
函数备注
***************************************************************************/
uchar8		Adjust_TimeLen(Str_Comm_645 *pV_645Frame)
{
	uchar8		Date_Time[CLDate_Time];		/*最早是调整成Date_Time，后经讨论调整成CDate_Week_Time格式，但变量名不修改*/
	ushort16	DataLen, V_usDataEncode;

/*判断长度*/
	if(pV_645Frame->DataLen != (CLTime + CLen_DI + CLen_OpCode + CLen_CommPW))
		{
			return(C_OtherErr);
		}
/*数据调整,长度,标识码(用于数据层的写)*/
	DataLen = CLDate_Time;
	InF_Read_Data(CDate_Time, Date_Time, &DataLen, &V_usDataEncode);  /*698中读出已为ssmmHHDDMMYY*/

	PF_CopyDataBytes(&Date_Time[CDate_WW_Time_WW_O], &pV_645Frame->Data[CData_14O_V_645 + CLTime], CLDate_Week - 1);

	if(PF_DataTimeActive(&Date_Time[CDate_WW_Time_WW_O], C_DT_Start_DD, CLDate_Week - 1) != C_OK)	/*日期非法，默认00-01-01*/
    {
      	pV_645Frame->Data[CData_14O_V_645 + CDate_WW_Time_WW_O] = 0x01;
		pV_645Frame->Data[CData_14O_V_645 + CDate_WW_Time_DD_O] = 0x01;
		pV_645Frame->Data[CData_14O_V_645 + CDate_WW_Time_MM_O] = 0x00;
	}
    pV_645Frame->Data[CData_14O_V_645 + CDate_WW_Time_YY_O] = 0x20;   /*年为20年*/
	pV_645Frame->DataLen = CLDate_Time + CLen_DI + CLen_OpCode + CLen_CommPW;

	pV_645Frame->DI = CDate_Time;
	return(C_OK);
}

/***************************************************************************
函数原型 	Adjust_UnsizedLen_S_PT
函数功能	判断时段、时区表数据长度是否正确。且长度统一调整成3*14
输入参数	*pV_645Frame			:接收到645帧
输出参数 	pV_645Frame->DataLen/Data[]	:补齐数据时修改
返回参数	C_OK/C_OtherErr/C_PeriodNum_OV或C_SeasonNum_OV
全局变量
函数备注
***************************************************************************/
uchar8	Adjust_UnsizedLen_S_PT(Str_Comm_645 *pV_645Frame)
{
	uchar8	ValidLen;
	uchar8	V_uci;
	uchar8	SourceLen;
	uchar8 V_TZone_Temp[CLSec_TZone_Data];
	ushort16 V_TZone_LenTemp, V_usDataEncode;

/*取有效长度，应上级函数中已判断645数据域长度肯定大于12，这里就不判断了*/
	ValidLen = pV_645Frame->DataLen - ( CLen_DI + CLen_OpCode + CLen_CommPW );
/*长度必须大于等于3，小于等于42*/
	if( ValidLen > CLFirst_TZone_Data )
	{
		if( ( pV_645Frame->DI == CFirst_TZone_Data ) || ( pV_645Frame->DI == CSec_TZone_Data ) )
		{
			return(C_SeasonNum_OV);
		}
		else
		{
			return(C_PeriodNum_OV);
		}
	}
	if( ValidLen < 3 )
	{
		return(C_OtherErr);
	}
/*长度必须能被3整除*/
	if( ( ValidLen % 3 ) != 0 )
	{
		return(C_OtherErr);
	}
/*补足3*14个数据*/
	if( ( pV_645Frame->DI != CSec_TZone_Data ) && ( ( pV_645Frame->DI & 0xFFFFFF00 ) == CSec_TZone_Data ) )
	{/*索引非0设置补数据，目前未使用 暂时先保留 lzy 20211012*/
		V_TZone_LenTemp = CLSec_TZone_Data;
		if( InF_Read_Data(CSec_TZone_Data, V_TZone_Temp, &V_TZone_LenTemp, &V_usDataEncode) != C_OK )
		{
			for( V_uci = 0; V_uci < CLSec_TZone_Data; V_uci++ )
			{
				V_TZone_Temp[V_uci] = 0x00;
			}
		}
		V_TZone_LenTemp = ((uchar8)(pV_645Frame->DI&0xFF) - 1);
		V_TZone_LenTemp *= 3;
		V_TZone_Temp[V_TZone_LenTemp] = pV_645Frame->Data[CData_14O_V_645];
		V_TZone_Temp[V_TZone_LenTemp + 1] = pV_645Frame->Data[CData_14O_V_645 + 1];
		V_TZone_Temp[V_TZone_LenTemp + 2] = pV_645Frame->Data[CData_14O_V_645 + 2];
        PF_CopyDataBytes(V_TZone_Temp, &pV_645Frame->Data[CData_14O_V_645], CLSec_TZone_Data);
	}
	else
	{
		SourceLen = ValidLen - 3;
		while( ValidLen < CLFirst_TZone_Data )
		{
			for( V_uci = 0; V_uci < 3 ; V_uci++ )
			{
				pV_645Frame->Data[CData_14O_V_645 + ValidLen] = pV_645Frame->Data[CData_14O_V_645 + SourceLen];
				ValidLen++;
				SourceLen++;
			}
		}
	}
	pV_645Frame->DataLen = CLFirst_TZone_Data + (CLen_DI + CLen_OpCode + CLen_CommPW);
	return(C_OK);
}
/***************************************************************************
函数原型 	Adjust_BackUpLadderLen
函数功能	判断备用套阶梯表参数数据长度是否正确，备用套数据长度固定64字节
输入参数	*pV_645Frame			:接收到645帧
输出参数 	pV_645Frame->DataLen为数据长度，固定64字节
返回参数	C_OK/C_OtherErr
全局变量
函数备注
***************************************************************************/
uchar8	Adjust_BackUpLadderLen( Str_Comm_645 *pV_645Frame )
{
	if( pV_645Frame->DataLen == ( CLBackUp_Ladder_Table + ( CLen_DI + CLen_OpCode + CLen_CommPW ) ) )
	{
		return C_OK;
	}
	else
	{
		return(C_OtherErr);
	}
}
/***************************************************************************
函数原型 	Adjust_ReportChannel
函数功能	上报通道长度判断，小于13字节时高位补0
输入参数	*pV_645Frame			:接收到645帧
输出参数 	pV_645Frame->DataLen为数据长度，固定13字节
返回参数	C_OK/C_OtherErr
全局变量
函数备注
***************************************************************************/
uchar8	Adjust_ReportChannel( Str_Comm_645 *pV_645Frame )
{
	uchar8 V_ucTemp;

	V_ucTemp = pV_645Frame->DataLen - ( CLen_DI + CLen_OpCode + CLen_CommPW );
	if( V_ucTemp > CLUpTellChannel )
	{
		return(C_OtherErr);
	}
	else
	{
		memset( &pV_645Frame->Data[CData_14O_V_645 + V_ucTemp], 0, (CLUpTellChannel - V_ucTemp));
		pV_645Frame->DataLen = CLUpTellChannel + (CLen_DI + CLen_OpCode + CLen_CommPW);
		return C_OK;
	}
}
/***************************************************************************
函数原型 	Adjust_BackUpRateFFPriceLen
函数功能	判断备用套费率表参数数据长度是否正确，长度要小于32*4且能被4整除
输入参数	*pV_645Frame			:接收到645帧
输出参数 	pV_645Frame->DataLen为数据长度，长度应该小于32*4+4字节MAC的长度
返回参数	C_OK/C_OtherErr
全局变量
函数备注	阶梯表长度64字节，超过了通用判断方法中最大长度63字节，因此特殊判断
***************************************************************************/
uchar8	Adjust_BackUpRateFFPriceLen(Str_Comm_645 *pV_645Frame)
{
	uchar8 V_ucTemp;
	if( ( pV_645Frame->DataLen <= ( 32 * 4 + ( CLen_DI + CLen_OpCode + CLen_CommPW ) ) )
	 && ( pV_645Frame->DataLen > ( ( CLen_DI + CLen_OpCode + CLen_CommPW ) ) ) )
	{
		V_ucTemp = pV_645Frame->DataLen - ( CLen_DI + CLen_OpCode + CLen_CommPW );
		if( ( V_ucTemp % 4 ) == 0 )
		{
			if(V_ucTemp < CLBackUp_RateFF_Price)
			{
				memset( &pV_645Frame->Data[CData_14O_V_645 + V_ucTemp], 0, (CLBackUp_RateFF_Price - V_ucTemp));
				pV_645Frame->DataLen = CLBackUp_RateFF_Price + (CLen_DI + CLen_OpCode + CLen_CommPW);
			}
			return C_OK;
		}
		else
		{
			return(C_OtherErr);
		}
	}
	else
	{
		return(C_OtherErr);
	}
}

/***************************************************************************
函数原型 	IsLoad_Rec_Time_LenOK
函数功能	判断密码长度、权限合理性及去除PA
输入参数	*pV_645Frame			:接收到645帧
输出参数 	pV_645Frame->DataLen/Data[]	:补齐数据时修改
返回参数	C_OK/C_OtherErr/C_Unauthorized
全局变量
函数备注	2014规范要求采用98级进行密钥修改!
***************************************************************************/
uchar8	IsPW_Len_Auth( Str_Comm_645 *pV_645Frame )
{
	if( ( pV_645Frame->DataLen - ( CLKey_2_Class + 1 + CLen_DI + CLen_OpCode + CLen_CommPW ) ) < 32 )
	{
		return C_OK;
	}
	else
	{
		return(C_OtherErr);
	}
}

/***************************************************************************
函数原型 	LookFor_WrParmTable
函数功能	搜索参数设置表格WrParmTable，实际也是判断DI在不在设置范围
输入参数	*pV_645Frame			:接收到的数据帧
				pWrParmTable			:参数设置表格中数据的地址
输出参数 	*pWrParmTable		:参数设置表格中数据内容
返回参数	C_OK/C_OtherErr
全局变量 	无
函数备注	无
***************************************************************************/
#define C_Event07ReportMode		0x08									/*07类事件上报类型11属性*/
#define C_Event24ReportMode		0x0B									/*24类事件上报类型15属性*/
#define C_First_TZone_PT_Data	(CFirst_TZone_1PT_Data & 0xFFFFFF00)	/*当前套时段表*/
#define C_Sec_TZone_PT_Data		(CSec_TZone_1PT_Data & 0xFFFFFF00)		/*备用套时段表*/

uchar8	LookFor_WrParmTable( Str_Comm_645 *pV_645Frame, Str_WrParmTable *pWrParmTable )
{
	uchar8	i;
	uchar8 DI_Temp[4];

/*首先确认DI是否为特殊*/
	PF_Ulong32ToBuffer4(DI_Temp, &(pV_645Frame->DI), 4);        /*获取OIA,OIB*/
	if( ( ( pV_645Frame->DI & 0xFFFFFF00 ) == 0xF3000200 )
	 || ( (pV_645Frame->DI & 0xFFFFFF00 ) == 0xF3010200 ) )
	{/*循显项、键显项*/
	 /*设置自动轮显或按键显示*/
		if( (pV_645Frame->DI & 0x000000FF) < 0x64 )
		{
			pWrParmTable->ParmDI = pV_645Frame->DI ;
			pWrParmTable->Method = C_UnAddFixedDataLen | C_DataLenFixed_OK | CLAuto_Dis_1ScreenCode | C_DataValid_NoLimit/*显示方法不做特殊限制，2017/12/29 10:47:36*/
				 					| C_HaveIPEvent_Invalid | C_ExtMsgType_Invalid;
			return(C_OK);
		}
		else
		{
			return(C_Error);
		}
	}
	else if( (pV_645Frame->DI & 0xFFFFFF00) == 0x40110200 )
	{/*设置公共假日*/
		if( ( ( pV_645Frame->DI & 0x000000FF ) != 0 ) && ( ( pV_645Frame->DI & 0x000000FF ) <= 20 ) )
		{
			pWrParmTable->ParmDI = pV_645Frame->DI ;
			pWrParmTable->Method = C_UnAddFixedDataLen | C_DataLenFixed_OK | CLHolidy_PT_Table1 | C_DataValidSpecialMethod | C_DV_HolidaySet
									| C_HaveIPEvent_ProgParm|C_ExtMsg_ReMultiRatesParm|C_ExtMsgDA_MultiRates;
			return(C_OK);
		}
		else
		{
			return(C_Error);
		}

	}
	else if( pV_645Frame->DI == CGPS_Signal )
	{
		pWrParmTable->Method = C_UnAddFixedDataLen | C_DataLenFixed_OK | CLGPS_Signal | C_DataValid_NoLimit
										| C_HaveIPEvent_GPRSSignal | C_ExtMsgType_Invalid;
		return(C_OK);
	}
	else if( ( C_EventOIA == DI_Temp[3] )
		   && ( ( ( ( DI_Temp[2] <= 0x08 ) || ( DI_Temp[2] == 0x0B ) || ( DI_Temp[2] == 0x3B ) )
			   && ( C_Event24ReportType == DI_Temp[1] ) )			/*24类的事件，OIB,2020标准修改了功率因数超限事件302B 属性15*/
			 ||( ( ( DI_Temp[2] == 0x09 )||( DI_Temp[2] == 0x0A )||( DI_Temp[2] >= 0x0C ) )&&( DI_Temp[2] != 0x3B )
			   && ( C_Event07ReportType == DI_Temp[1] ) ) ) )		/*7类的事件，OIB 属性11*/
	{
		pWrParmTable->Method = C_UnAddFixedDataLen | C_DataLenFixed_OK | CLReport_Type | C_DataValidHex_Range | C_DV_HexRange_0_1
								| C_HaveIPEvent_Invalid | C_ExtMsgType_Invalid;
		return(C_OK);
	}
	else if( ( C_EventOIA == DI_Temp[3] )
		   && ( ( ( ( DI_Temp[2] <= 0x08 ) || ( DI_Temp[2] == 0x0B ) || ( DI_Temp[2] == 0x3B ) )
			   && ( C_Event24ReportMode == DI_Temp[1] ) )			/*24类的事件，OIB,2020标准修改了功率因数超限事件302B 属性11*/
			  ||( ( ( DI_Temp[2] == 0x09 ) || ( DI_Temp[2] == 0x0A ) || ( DI_Temp[2] >= 0x0C ) ) && ( DI_Temp[2] != 0x3B )
			   && ( C_Event07ReportMode == DI_Temp[1] ) ) ) )		/*7类的事件，OIB 属性8*/
	{
		pWrParmTable->Method = C_UnAddFixedDataLen | C_DataLenFixed_OK | CLReport_Type | C_DataValidHex_Range | C_DV_HexRange_0_3
								| C_HaveIPEvent_Invalid | C_ExtMsgType_Invalid;
		return(C_OK);
	}
	else if( ( ( pV_645Frame->DI & 0xFFFFFF00 ) == CSec_TZone_Data ) || ( ( pV_645Frame->DI & 0xFFFFFF00 ) == CFirst_TZone_Data ) )
	{
		pWrParmTable->Method = C_UnAddFixedDataLen | C_DataLenUnsized | C_UnsizedLen_S_PT | C_DataValidSpecialMethod | C_DV_Season
								| C_HaveIPEvent_ProgParm | C_ExtMsg_ReMultiRatesParm | C_ExtMsgDA_MultiRates;
		return(C_OK);
	}
	else if( ( ( pV_645Frame->DI & 0xFFFFFF00 ) == C_Sec_TZone_PT_Data ) || ( ( pV_645Frame->DI & 0xFFFFFF00 ) == C_First_TZone_PT_Data ) )
	{
		pWrParmTable->Method = C_UnAddFixedDataLen | C_DataLenUnsized | C_UnsizedLen_S_PT | C_DataValidSpecialMethod | C_DV_TimePeriod
								| C_HaveIPEvent_ProgParm | C_ExtMsg_ReMultiRatesParm | C_ExtMsgDA_MultiRates;
		return(C_OK);
	}
	else
	{
		for( i = 0; i < CLen_TB_WrParm; i++ )
		{
			if(pV_645Frame->DI == TB_WrParm[i].ParmDI)
			{
				pWrParmTable->Method = TB_WrParm[i].Method;
				break;
			}
		}
		if( i >= CLen_TB_WrParm )
		{
			pWrParmTable->Method = C_UnAddFixedDataLen | C_DataLenFixed_OK | (pV_645Frame->DataLen - 12)
									| C_DataValid_NoLimit | C_HaveIPEvent_Invalid | C_ExtMsgType_Invalid;
		}
	}
	pWrParmTable->ParmDI = pV_645Frame->DI;
	return(C_OK);
}

/***************************************************************************
函数原型 	Is_ParmType_3
函数功能	判断是否为3类参数设置(如果设置GPRS信号，则必须是模块通道，否则认为不是III类参数。)
输入参数	DI				:接收到的待设置的DI
				pWrParmTable		:参数表格中数据地址
				V_ucCommNum			:通道号,主要用于GPRS信号强度设置只能是模块通道的判断限制
输出参数 	*pWrParmTable	:参数表格中的数据
返回参数	C_OK/C_Error
全局变量 	无
函数备注
***************************************************************************/
uchar8 Is_ParmType_3(ulong32 DI, Str_WrParmTable *pWrParmTable, uchar8 V_ucCommNum)
{
	/*复位模块状态字、GPRS信号设置*/
	switch(DI)
	{
		case		CGPS_Signal:				/*设置GPRS信号*/
		{
			pWrParmTable->ParmDI = DI;
			pWrParmTable->Method = C_UnAddFixedDataLen | C_DataLenFixed_OK | CLGPS_Signal | C_DataValid_NoLimit
									| C_HaveIPEvent_GPRSSignal | C_ExtMsgType_Invalid;
			if(V_ucCommNum != C_Module)			/*通道号不是模块通道*/
			{
				return(C_Error);
			}
		}return(C_OK);
		case		CRst_Report_State_645:		/*复位主动上报状态字*/
		{
			pWrParmTable->ParmDI = DI;
			pWrParmTable->Method = C_UnAddFixedDataLen | C_DataLenFixed_OK | CLRst_Report_State_645 | C_DataValidSpecialMethod | C_DV_RstReport_State
									| C_HaveIPEvent_RstReportState | C_ExtMsgType_Invalid;
		}return(C_OK);
		case		CF1_TerUpCommParam:			/*外扩自己模块GPRS模块设置IP等参数*/
			pWrParmTable->ParmDI = DI;
			pWrParmTable->Method = C_UnAddFixedDataLen | C_DataLenFixed_OK | CLF1_TerUpCommParam | C_DataValid_NoLimit
									| C_HaveIPEvent_Invalid | C_ExtMsgType_Invalid;
			return(C_OK);
		case		CF3_MainStaCommParam:		/*外扩自己模块GPRS模块设置IP等参数*/
			pWrParmTable->ParmDI = DI;
			pWrParmTable->Method = C_UnAddFixedDataLen | C_DataLenFixed_OK | CLF3_MainStaCommParam | C_DataValid_NoLimit
									| C_HaveIPEvent_Invalid | C_ExtMsgType_Invalid;
			return(C_OK);
		case		CF4_SMSCommParam:			/*外扩自己模块GPRS模块设置IP等参数*/
			pWrParmTable->ParmDI = DI;
			pWrParmTable->Method = C_UnAddFixedDataLen | C_DataLenFixed_OK | CLF4_SMSCommParam | C_DataValid_NoLimit
									| C_HaveIPEvent_Invalid | C_ExtMsgType_Invalid;
			return(C_OK);
		case		CF7_TerminalIPAddr:			/*外扩自己模块GPRS模块设置IP等参数*/
			pWrParmTable->ParmDI = DI;
			pWrParmTable->Method = C_UnAddFixedDataLen | C_DataLenFixed_OK | CLF7_TerminalIPAddr | C_DataValid_NoLimit
									| C_HaveIPEvent_Invalid | C_ExtMsgType_Invalid;
			return(C_OK);
		case		CF8_ConnectParam:			/*外扩自己模块GPRS模块设置IP等参数*/
			pWrParmTable->ParmDI = DI;
			pWrParmTable->Method = C_UnAddFixedDataLen | C_DataLenFixed_OK | CLF8_ConnectParam | C_DataValid_NoLimit
									| C_HaveIPEvent_Invalid | C_ExtMsgType_Invalid;
			return(C_OK);
		case		CF16_MoveAPNPassWord:		/*外扩自己模块GPRS模块设置IP等参数*/
			pWrParmTable->ParmDI = DI;
			pWrParmTable->Method = C_UnAddFixedDataLen | C_DataLenFixed_OK | CLF16_MoveAPNPassWord | C_DataValid_NoLimit
									| C_HaveIPEvent_Invalid | C_ExtMsgType_Invalid;
			return(C_OK);
		case		CF89_TerminalAddr:			/*外扩自己模块GPRS模块设置IP等参数*/
			pWrParmTable->ParmDI = DI;
			pWrParmTable->Method = C_UnAddFixedDataLen | C_DataLenFixed_OK | CLF89_TerminalAddr | C_DataValid_NoLimit
									| C_HaveIPEvent_Invalid | C_ExtMsgType_Invalid;
			return(C_OK);
		case		CFactoryInMeterNum:			/*自扩厂内表号*/
			pWrParmTable->ParmDI = DI;
			pWrParmTable->Method = C_UnAddFixedDataLen | C_DataLenFixed_OK | CLFactoryInMeterNum | C_DataValid_NoLimit
									| C_HaveIPEvent_Invalid | C_ExtMsgType_Invalid;
			return(C_OK);
		default:
			return(C_Error);
	}
}

/***************************************************************************
函数原型 	Comm_MultFOut
函数功能	完成多功能功能输出命令解析与处理
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	无
函数备注
***************************************************************************/
void		Comm_MultFOut(Str_Comm_645 *pV_645Frame)
{
	uchar8	Err = C_OK;

/*判断长度*/
	if(pV_645Frame->DataLen !=0x01)
	{
		Err = C_OtherErr;
	}
/*调用多功能输出接口函数，将设置的参数传递给该模块，根据返回值确定取值是否合理 */
	if(InF_ModifyFunctionWord(pV_645Frame->Data[C1DData_O_V_645]) != C_OK)
	{
		Err = C_OtherErr;
	}
/*应答*/
	if(pV_645Frame->AddressFlag == C_Broadcast)
	{/*广播地址不应答*/
		return;
	}
	if(Err == C_OK)
	{
		Comm_Response_FromP_Normal(pV_645Frame, &pV_645Frame->Data[C1DData_O_V_645], 1);
	}
	else
	{
		Comm_Response_Set_ReadErr(Err, pV_645Frame);
	}
}

/*******************************************************************************
函数原型: Comm_Set_BPSr_C17
函数功能: 完成波特率修改命令解析与处理
输入参数: *pV_645Frame:接收到的数据帧
输出参数: 无
返回参数: 无
全局变量: 无
函数备注
*******************************************************************************/
void Comm_Set_BPSr_C17(Str_Comm_645 *pV_645Frame)
{
	ulong32	bpsDI;
    uchar8	bps;
    ushort16	V_ucDataLen, V_usDataEncode;
    uchar8	V_ucBuffer[CLOne485_Baud];

	/*判断长度合法性*/
	if( pV_645Frame->DataLen != CLOne485_Baud_645 )
	{
		Comm_Response_Set_ReadErr(C_OtherErr_645, pV_645Frame);
		return;
	}

	/*判断数据合理性*/
    bps = SF_BPS645transfor698(pV_645Frame->Data[C17SetBpsData_O_V_645]);
	if( Is_CommBPS_OK(pV_645Frame->ChannelNo, bps) != C_OK )
	{
		Comm_Response_Set_ReadErr(C_Baud_NotModified_645, pV_645Frame);
		return;
	}

	/*模块通道波特率只能设置为9600*/
	if( (pV_645Frame->ChannelNo == C_Module) && (bps != C_9600) )
	{
		Comm_Response_Set_ReadErr(C_Baud_NotModified_645, pV_645Frame);
		return;
	}

	/*写数据层*/
	bpsDI = Get_CommBpsDataCode(pV_645Frame->ChannelNo);
    V_ucDataLen = CLOne485_Baud;
    if( InF_Read_Data(bpsDI, V_ucBuffer, &V_ucDataLen, &V_usDataEncode) != C_OK )
	{
		V_ucBuffer[0] = C_bps_9600_698;
		V_ucBuffer[1] = C_parity_Even;
		V_ucBuffer[2] = C_CommDataLen8;
		V_ucBuffer[3] = C_parity_Odd;
		V_ucBuffer[4] = 0;
	}

    V_ucBuffer[0] = bps;
	SV_Comm_Parse_Local.SafeControlFlag = SV_Comm_Parse_Local.SafeControlFlag | C_W_SafeFlag_3;
	InF_Write_Data(C_Msg_Communication, bpsDI, V_ucBuffer, CLOne485_Baud, SV_Comm_Parse_Local.SafeControlFlag);

	Comm_Response_FromP_Normal(pV_645Frame, &pV_645Frame->Data[C17SetBpsData_O_V_645], CLOne485_Baud_645);

	SV_SetBPS_Flag = C_OK;
}

/***************************************************************************
函数原型 	Get_CommBpsDataCode
函数功能	获取通道波特率的DI
输入参数	CommNo			:通道号
输出参数 	无
返回参数	通道波特率的DI
全局变量 	无
函数备注	注意这里必须保证通道号是正确的，否则会导致
				不可预知的错误
***************************************************************************/
ulong32		Get_CommBpsDataCode(uchar8	CommNo)
{
	switch(CommNo)
	{
		case		C_RS485_1:
			return COne485_Baud;
		case		C_RS485_2:
			return CTwo485_Baud;
		case		C_IR:
			return CMod_InFr_Baud;
		case		C_Module:
			return CModular_Baud;
		default:
			return CModular_Baud;
	}
}

/***************************************************************************
函数原型 	Is_CommBPS_OK
函数功能	判断通道的bps是否合理
输入参数	CommNo			:通道号
				bps				:波特率特征字
输出参数 	无
返回参数	C_OK/C_Error
全局变量 	无
函数备注
***************************************************************************/
#define	C_Len_TB_Bps	5
#define	C_1200			2
#define	C_2400			3
#define	C_4800			4
#define	C_9600			6
#define	C_19200			7
const	uchar8	TB_RS485BPS_Parm[C_Len_TB_Bps] = {C_1200, C_2400, C_4800, C_9600, C_9600};
const	uchar8	TB_IRBPS_Parm[C_Len_TB_Bps] = {C_1200, C_1200, C_1200, C_1200, C_1200};
const	uchar8	TB_ModuleBSP_Parm[C_Len_TB_Bps] = {C_1200, C_2400, C_4800, C_9600, C_19200};
uchar8	Is_CommBPS_OK( uchar8 CommNo, uchar8 bps )
{
	uchar8	*pCommBPS;
	uchar8	i;
	switch( CommNo )
	{
		case	C_RS485_1:
		case	C_RS485_2:
			pCommBPS = (uchar8 *)TB_RS485BPS_Parm;
			break;
		case	C_IR:
			pCommBPS = (uchar8 *)TB_IRBPS_Parm;
			break;
		case	C_Module:
			pCommBPS = (uchar8 *)TB_ModuleBSP_Parm;
			break;
		default:
			return(C_Error);
	}
	for( i = 0; i < C_Len_TB_Bps; i++ )
	{
		if( bps == pCommBPS[i] )
		{
			break;
		}
	}
	if( i == C_Len_TB_Bps )
	{
		return(C_Error);
	}
	else
	{
		return(C_OK);
	}

}
/***************************************************************************
函数原型 	Comm_FreezingOrder_C16
函数功能	完成冻结命令
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	无
函数备注
***************************************************************************/
/*																mm   hh    DD    MM */
const	uchar8	FreezeOrder_C16_PLimit[CLTiming_Freeze_Time] = {0x60, 0x24, 0x29, 0x13};
void		Comm_FreezingOrder_C16(Str_Comm_645 *pV_645Frame)
{
	uchar8	Err = C_OK;
	uchar8	i;
	uchar8	MsgParm;
	uchar8	j;
/*判断长度*/
	if(pV_645Frame->DataLen != CLTiming_Freeze_Time)
	{
		Err = C_OtherErr;
	}
/*判断数据是否为BCD*/
	if( PF_Judge_BCD( CLTiming_Freeze_Time, &pV_645Frame->Data[CFreezeParm_O_V_645] ) != C_OK )
	{
		Err = C_OtherErr;
	}
/*判断全99的个数。4个全99，表示瞬时冻结。99只能从后到前顺序拥有*/
/*数据格式为mm hh DD MM*/
	for( i = 4; i > 0; i-- )
	{
		if( pV_645Frame->Data[CFreezeParm_O_V_645 + i - 1] != 0x99 )
		{
			break;
		}
	}
	/*i=0表示4个全99，瞬时冻结。i等于几，表示判断几个时间是否合法。*/
	if(i == 0)
	{
		/*瞬时冻结发布消息*/
		MsgParm = Pt_MsgFreezeImmediately;
		Comm_SendMsg(&MsgParm, (Pt_MsgFreezeImmediately_Len + 1), C_Msg_Freeze);
	}
	else
	{
		/*判断数据是否合法*/
		for( j = 0; j < i; j++ )
		{
			if( pV_645Frame->Data[CFreezeParm_O_V_645 + j] >= FreezeOrder_C16_PLimit[j] )
			{
				Err = C_OtherErr;
				break;
			}
		}
		if( ( pV_645Frame->Data[CFreezeParm_O_V_645 + 2] == 0 ) || ( pV_645Frame->Data[CFreezeParm_O_V_645 + 3] == 0 ) )
		{/*日、月等于0*/
			Err = C_OtherErr;
		}
		/*判断如果数据没有出现过错误，则更新数据层*/
		if(Err == C_OK)
		{
			SV_Comm_Parse_Local.SafeControlFlag = SV_Comm_Parse_Local.SafeControlFlag | C_W_SafeFlag_3;
			InF_Write_Data(C_Msg_Communication, CTiming_Freeze_Time, &pV_645Frame->Data[CFreezeParm_O_V_645], CLTiming_Freeze_Time, SV_Comm_Parse_Local.SafeControlFlag);
		}
	}

	if(pV_645Frame->AddressFlag != C_Broadcast)
	{
		/*不是广播就应答*/
		Comm_Response_Set_ReadErr(Err,pV_645Frame);
	}
}

/***************************************************************************
函数原型 	Comm_BroadcastSetClock_PointResponed
函数功能	点对点广播校时应答
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	无
函数备注
***************************************************************************/
void		Comm_BroadcastSetClock_PointResponed(Str_Comm_645 *pV_645Frame,uchar8 V_ErrFlag)
{
    if(pV_645Frame->AddressFlag != C_Broadcast)
    {
      Comm_Response_Set_ReadErr(V_ErrFlag, pV_645Frame);
    }
}
/***************************************************************************
函数原型 	Comm_BroadcastSetClock
函数功能	完成广播校时
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	无
函数备注	645协议处理数据格式需要再核对 本次修改时间格式只保证数据不溢出 lzy 20211023
***************************************************************************/
void		Comm_BroadcastSetClock(Str_Comm_645 *pV_645Frame)
{
	uchar8	V_SystemDate_Time[CLDate_Time];
	uchar8	V_CMPDate_Time[CLDate_Time];
	ulong32	V_MinDIFValue;
	ushort16	DataLen, V_usDataEncode;
	uchar8	V_ReturnData;
	uchar8	V_DIF;
	uchar8	V_ucMsg[CLDate_Time*2 + 1];

/*判断长度*/
	if(pV_645Frame->DataLen != 0x06)
	{
		return;
	}
/*读系统时钟*/
	DataLen = CLDate_Time;
	if( InF_Read_Data( CDate_Time, V_SystemDate_Time, &DataLen, &V_usDataEncode ) != C_OK )
	{
		/*如果时钟读不出来，则只能进行时钟设置，无法广播校时*/
		Comm_BroadcastSetClock_PointResponed(pV_645Frame, C_OtherErr_645);
		return;
	}
/*判断广播校时时间是否合法*/
	if(PF_DataTimeActive_698(&pV_645Frame->Data[CBoardCastData_O_V_645 + C_ss_O], C_DT_Start_ss, CLDate_Time) != C_OK)
	{
		Comm_BroadcastSetClock_PointResponed(pV_645Frame, C_OtherErr_645);
		return;
	}

/*判断当天有没有广播校时过*/
	if( ( SV_Comm_Parse.BDSC_RecentClock[CDate_Time_DD_O] ==  V_SystemDate_Time[CDate_Time_DD_O] )
	 && ( SV_Comm_Parse.BDSC_RecentClock[CDate_Time_MM_O] == V_SystemDate_Time[CDate_Time_MM_O] )
	 && ( SV_Comm_Parse.BDSC_RecentClock[CDate_Time_YYL_O] == V_SystemDate_Time[CDate_Time_YYL_O] ) )
	{
		Comm_BroadcastSetClock_PointResponed(pV_645Frame, C_OtherErr_645);
		return;
	}
/*判断系统时间是否在00:00附件5min，是则不允许广播校时*/
    memset(&V_CMPDate_Time[C_ss_O], 0, 3);
	V_CMPDate_Time[CDate_Time_DD_O] = V_SystemDate_Time[CDate_Time_DD_O];
	V_CMPDate_Time[CDate_Time_MM_O] = V_SystemDate_Time[CDate_Time_MM_O];
	V_CMPDate_Time[CDate_Time_YYL_O] = V_SystemDate_Time[CDate_Time_YYL_O];
	PF_TimeSub_Min(V_CMPDate_Time, V_SystemDate_Time, &V_MinDIFValue);
	if( ( V_MinDIFValue < 5 ) || ( V_MinDIFValue >= 1435 ) )
	{
/*零点附近5min*/
		Comm_BroadcastSetClock_PointResponed(pV_645Frame, C_OtherErr_645);
		return;
	}
/*判断是否在结算日附近*/
	DataLen = CLSettle_Day1;
	if( InF_Read_Data( CSettle_Day1, &V_CMPDate_Time[C_hh_O], &DataLen, &V_usDataEncode ) == C_OK )
	{
		PF_TimeSub_Min(V_CMPDate_Time, V_SystemDate_Time, &V_MinDIFValue);
		if(V_MinDIFValue < 5)
		{
/*结算日附近5min*/
			Comm_BroadcastSetClock_PointResponed(pV_645Frame, C_OtherErr_645);
			return;
		}
	}
	if( InF_Read_Data( CSettle_Day2, &V_CMPDate_Time[C_hh_O], &DataLen, &V_usDataEncode ) == C_OK )
	{
		PF_TimeSub_Min(V_CMPDate_Time, V_SystemDate_Time, &V_MinDIFValue);
		if(V_MinDIFValue < 5)
		{
/*结算日附近5min*/
			Comm_BroadcastSetClock_PointResponed(pV_645Frame, C_OtherErr_645);
			return;
		}
	}
	if( InF_Read_Data( CSettle_Day3, &V_CMPDate_Time[C_hh_O], &DataLen, &V_usDataEncode ) == C_OK )
	{
		PF_TimeSub_Min(V_CMPDate_Time, V_SystemDate_Time, &V_MinDIFValue);
		if(V_MinDIFValue < 5)
		{
/*结算日附近5min*/
			Comm_BroadcastSetClock_PointResponed(pV_645Frame, C_OtherErr_645);
			return;
		}
	}
/*广播校时时间应该和系统时间差值小于等于5min*/
	V_DIF = PF_TimeSub_Min(&pV_645Frame->Data[CBoardCastData_O_V_645+C_ss_O], V_SystemDate_Time, &V_MinDIFValue);
	if(V_MinDIFValue >= 5)
	{
		/*大于5min*/
		Comm_BroadcastSetClock_PointResponed(pV_645Frame, C_OtherErr_645);
		return;
	}
/*可以写时钟*/
/*首先刷新最近一次广播校时时间*/
	PF_CopyDataBytes(&pV_645Frame->Data[CBoardCastData_O_V_645 + C_ss_O], &SV_Comm_Parse.BDSC_RecentClock[C_ss_O], CLDate_Time);

	SV_Comm_Parse_Local.SafeControlFlag = SV_Comm_Parse_Local.SafeControlFlag | C_W_SafeFlag_3;

	V_ReturnData = InF_Write_Data(C_Msg_Communication, CDate_Time, &pV_645Frame->Data[CBoardCastData_O_V_645 + C_ss_O], CLDate_Time, SV_Comm_Parse_Local.SafeControlFlag);
	if(V_ReturnData != C_OK)
	{
		Comm_BroadcastSetClock_PointResponed(pV_645Frame, C_OtherErr_645);
		return;
	}
    Comm_BroadcastSetClock_PointResponed(pV_645Frame, C_OK);
/*修改时钟需要发布的消息*/
/*往前修改时钟，需要覆盖负荷记录*/
	if(V_DIF == C_LessThan)
	{
		InF_ChangeTime_LoadProfileCover();
	}
/*发布消息给需量模块*/
	Comm_SendMsgForUpdataParm(C_ReworkTime, C_Msg_DemandMetering);

	Comm_SendMsgForUpdataParm(C_ReworkTime, C_Msg_Deal_MultiRates);

/*将修改前时钟(7字节，CDate_Time格式)，发布消息给冻结模块*/
	PF_CopyDataBytes(V_SystemDate_Time,&V_ucMsg[1],CLDate_Time);
	V_ucMsg[0] = Pt_7DayAdd_FreezeTime;
	Comm_SendMsg(&V_ucMsg[0], (Pt_7DayAdd_FreezeTime_Len+1),C_Msg_Freeze);

#if 0	/*修改时间跨月清零电压合格率 费控流程月冻结不合格*/
/*将修改前后时钟(7字节，CDate_Time格式)，发布消息给电压合格率模块*/
	PF_CopyDataBytes(&pV_645Frame->Data[CBoardCastData_O_V_645+C_ss_O],&V_ucMsg[CLDate_Time+1],CLDate_Time);
	V_ucMsg[0] = Pt_VRQTimeChange;
	Comm_SendMsg(V_ucMsg, (CLDate_Time*2+1),C_Msg_VoltageQualifiedRateMetering);
#endif
	
}

/***************************************************************************
函数原型 	Comm_CondenseAAReadMAddress
函数功能	完成缩位读表地址功能
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	无
函数备注
***************************************************************************/
void		Comm_CondenseAAReadMAddress(Str_Comm_645 *pV_645Frame)
{
	uchar8	MeterAddress[CLComm_Address];
	uchar8	V_ReturnData;
	ushort16	DataLen, V_usDataEncode;
/*判断长度*/
	if(pV_645Frame->DataLen != 0x00)
	{
		Comm_Response_Set_ReadErr(C_OtherErr, pV_645Frame);
		return;
	}
/*读表地址*/
	DataLen = CLComm_Address;
	V_ReturnData = InF_Read_Data(CComm_Address, MeterAddress, &DataLen, &V_usDataEncode);
	if(V_ReturnData != C_OK)
	{
		Comm_Response_Set_ReadErr(C_OtherErr, pV_645Frame);
	}
	else
	{
		Comm_Response_FromP_Normal(pV_645Frame, MeterAddress, CLComm_Address);
	}
}
/***************************************************************************
函数原型 	Comm_SetCommAddress
函数功能	完成设置通信地址功能
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	无
函数备注
***************************************************************************/
#define		C_O_CommAddress	0
void		Comm_SetCommAddress(Str_Comm_645 *pV_645Frame)
{
	uchar8	V_ReturnData;

/*因为Is_ID_Auth_Ok_ResponseErr函数中身份认证情况下就算通过安全认证*/
/*所以这里需要重新判断编程开关或厂内状态，确保只有编程开关允许密码编程*/
	if( ( JudgeTimerExceed10min(&SI_JTimer_BSOn2500) != C_TimerEnable )
	 && ( JudgeTimerExceed10min(&ProgKey_Timer) != C_TimerEnable ) )
	{
		return;
	}
/*判断长度*/
	if(pV_645Frame->DataLen != CLComm_Address)
	{
		return;
	}
/*判断通信地址是否有效*/
	V_ReturnData = DV_Comm_Address(&pV_645Frame->Data[C_O_CommAddress]);
	if(V_ReturnData != C_OK)
	{
		return;
	}
/*设置表通信地址*/
	SV_Comm_Parse_Local.SafeControlFlag = SV_Comm_Parse_Local.SafeControlFlag | C_W_SafeFlag_3;

	InF_Write_Data(C_Msg_Communication, CComm_Address, &pV_645Frame->Data[C_O_CommAddress], CLComm_Address, SV_Comm_Parse_Local.SafeControlFlag);
	InF_Get_Comm_Address(SV_Comm_Address, 0x00);		/*更新通信中的通信地址*/
/*组织正常应答帧*/
	Comm_Response_Set_ReadErr(C_OK, pV_645Frame);
}
/***************************************************************************
函数原型 	Comm_SetPassword
函数功能	完成密码编程解析及处理
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	无
函数备注
***************************************************************************/
#define		CPAO_Offset		4
#define		CPAN_Offset		8
void		Comm_SetPassword(Str_Comm_645 *pV_645Frame)
{
	uchar8	PA_N;
	uchar8	V_ReturnData;

/*因为Is_ID_Auth_Ok_ResponseErr函数中身份认证情况下就算通过安全认证*/
/*所以这里需要重新判断编程开关或厂内状态，确保只有编程开关允许密码编程*/
	if( ( JudgeTimerExceed10min(&SI_JTimer_BSOn2500) != C_TimerEnable )
	 && ( JudgeTimerExceed10min(&ProgKey_Timer) != C_TimerEnable ) )
	{
		Comm_Response_Set_ReadErr(C_Unauthorized_645, pV_645Frame);
		return;
	}
/*判断长度,密码修改，数据域为DI0-DI3 PAO P1O-P3O PAN P1N-P3N*/
	if(pV_645Frame->DataLen!=0x0C)
	{
		Comm_Response_Set_ReadErr(C_OtherErr_645, pV_645Frame);
		return;
	}
/*判断拟修改的密码DI和PN是否合理*/
	switch(pV_645Frame->DI)
	{
		case		CKey_0_Class:
			PA_N = 0;
			break;
		case		CKey_1_Class:
			PA_N = 1;
			break;
		case		CKey_2_Class:
			PA_N = 2;
			break;
		case		CKey_3_Class:
			PA_N = 3;
			break;
		case		CKey_4_Class:
			PA_N = 4;
			break;
		case		CKey_5_Class:
			PA_N = 5;
			break;
		case		CKey_6_Class:
			PA_N = 6;
			break;
		case		CKey_7_Class:
			PA_N = 7;
			break;
		case		CKey_8_Class:
			PA_N = 8;
			break;
		case		CKey_9_Class:
			PA_N = 9;
			break;
		default:	/*标识码错误*/
			Comm_Response_Set_ReadErr(C_OtherErr_645, pV_645Frame);
			return;
	}
	if(PA_N != pV_645Frame->Data[CPAN_Offset])
	{
		Comm_Response_Set_ReadErr(C_OtherErr_645, pV_645Frame);
	}
/*判断旧密级是否符合权限，密码是否正确*/
	if( pV_645Frame->Data[CPAO_Offset]>PA_N)
	{
		/*低优先级密码更改高优先级密码*/
		Comm_Response_Set_ReadErr(C_Unauthorized_645, pV_645Frame);
		return;
	}
	V_ReturnData = Is_PW_OK(&pV_645Frame->Data[CPAO_Offset]);
	if(V_ReturnData != C_OK)
	{
		if( ( V_ReturnData == C_SupperPW_OK ) && ( JudgeTimerExceed10min(&SI_JTimer_BSOn2500) == C_TimerEnable ) )
		{/*校表记录指针数据清零*/
			SV_Comm_Parse_Local.SafeControlFlag = SV_Comm_Parse_Local.SafeControlFlag|C_W_SafeFlag_3;
			InF_RecMeterNote_Clear(C_Msg_Communication, SV_Comm_Parse_Local.SafeControlFlag);
		}
		else
		{/*不是超级密码，且不在厂内模式下，不能更改密码*/
			Comm_Response_Set_ReadErr(C_Unauthorized_645,pV_645Frame);
			return;
		}
	}
/*判断新密码是否为BCD*/
	if(PF_Judge_BCD(CLKey_0_Class, &pV_645Frame->Data[CPAN_Offset+1]))
	{
		Comm_Response_Set_ReadErr(C_OtherErr_645,pV_645Frame);
		return;
	}
/*写密码*/
	SV_Comm_Parse_Local.SafeControlFlag = SV_Comm_Parse_Local.SafeControlFlag|C_W_SafeFlag_3;

	InF_Write_Data(C_Msg_Communication, pV_645Frame->DI, &pV_645Frame->Data[CPAN_Offset + 1], CLKey_0_Class, SV_Comm_Parse_Local.SafeControlFlag);

/*组织正常应答帧*/
	Comm_Response_FromP_Normal(pV_645Frame, &pV_645Frame->Data[CPAN_Offset], (CLKey_0_Class+1));

}
/***************************************************************************
函数原型 	Comm_EventClear
函数功能	完成事件清零命令解析及应答
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	通道交互变量
函数备注
***************************************************************************/
void		Comm_EventClear(Str_Comm_645 *pV_645Frame)
{
	uchar8	Err;
	ulong32	EventDI;
    ulong32 V_ulOAD;

/*根据对应的密级进行相应的逻辑判断	*/
	if(pV_645Frame->Data[CPW_SpecialO_V_645] == 0x98)
	{
		Err = Comm_98EventClear(pV_645Frame);
	}
	else if(pV_645Frame->Data[CPW_SpecialO_V_645] == 0x02)
	{
		Err = Comm_02EventClear(pV_645Frame);
	}
	else
	{
		/*密级不对*/
		Err = C_Unauthorized_645;
	}
/*逻辑判断后，进行相应事件触发和应答*/
	if(Err == C_OK)
	{
		PF_Buffer4ToUlong32(&pV_645Frame->Data[C_O_EventClear_DI], &EventDI, CLen_DI);

		/*山东双协议新增*/
		if((EventDI == 0xFFFFFFFF))
		{
			V_ulOAD = 0x43000500;
			Err = SF_EventClear(pV_645Frame, V_ulOAD);
			INF_Init_Str_ProgRecord_645(&SV_Comm_Parse.ProgRecord_645);
		}
		else
		{
			PF_Buffer4ToUlong32(&pV_645Frame->Data[C_O_EventClear_DI], &V_ulOAD, 4);
			if( ( V_ulOAD == ( CTol_Clear_Degree | 0x000000FF ) ) || ( V_ulOAD == ( CEven_Clear_Degree | 0x000000FF ) ) )
			{
				Err = C_Unauthorized_645;
			}
			else
			{
				Err = SF_EventClear_698_Dou645(pV_645Frame,C_Program);
				if( ( EventDI == C_ProgramEventClearDI ) && ( Err == C_OK ) )
				{
				 	INF_Init_Str_ProgRecord_645(&SV_Comm_Parse.ProgRecord_645);
				}
			}
		}
	}
	if(Err !=C_OK)
	{
		SV_Comm_Parse_Local.SafeControlFlag = 0;
		if(Err == C_OtherErr)
		{
		   Err = C_OtherErr_645;
		}
	}
	Comm_Response_Set_ReadErr(Err, pV_645Frame);
}

/***************************************************************************
函数原型 	Comm_02EventClear
函数功能	事件记录清零02级逻辑判断
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	C_OK/C_OtherErr/C_Unauthorized
全局变量 	无
函数备注
***************************************************************************/
uchar8	Comm_02EventClear(Str_Comm_645 *pV_645Frame)
{
/*判断是否厂内，不在厂内用02、04级清零应答无权限*/
	if( JudgeTimerExceed10min(&SI_JTimer_BSOn2500) != C_TimerEnable )
	{
		return(C_Unauthorized);
	}
/*判断长度*/
	if(pV_645Frame->DataLen != ( CLen_OpCode + CLen_CommPW + CLen_DI ) )
	{
		return(C_OtherErr);
	}

/*判断密码是否正确*/
	if( Is_PW_OK( &(pV_645Frame->Data[CPW_SpecialO_V_645]) ) != C_OK )
	{
		return(C_Unauthorized);
	}

	return(C_OK);
}

/***************************************************************************
函数原型 	Comm_98EventClear
函数功能	事件记录清零98级逻辑判断
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	pV_645Frame->Data[C_O_EventClear_DI]	:将解密后的事件DIcopy到和02级一致位置
返回参数	C_OK/C_OtherErr/C_Unauthorized
全局变量 	无
函数备注	645协议处理数据格式需要再核对 本次修改时间格式只保证数据不溢出 lzy 20211023
***************************************************************************/
uchar8	Comm_98EventClear(Str_Comm_645 *pV_645Frame)
{
	ushort16	SError, ValidDataLen, V_usDataEncode;
	uchar8	*pValidData;
	uchar8	Clock[CLDate_Time];

/*判断长度*/
	if( pV_645Frame->DataLen <= ( CLen_OpCode + CLen_CommPW + CLen_DI ) )
	{
		return(C_OtherErr);
	}

/*调用安全模块接口函数*/
	pValidData = &pV_645Frame->Data[CData_OtherO_V_645];
	ValidDataLen = pV_645Frame->DataLen - CLen_CommPW - CLen_OpCode;
	/*解密后数据在pValidData，长度为12.按照R1-R12排列*/
	SError = InF_S_EventClear(pValidData, (uchar8 *)&ValidDataLen);
	if(SError != C_OK)
	{
		if(SError == C_SERR_ESAM_VF)
		{/*ESAM验证失败，200次++*/
			Comm_DealwithSPTVariable(C_SPTNumAdd);
		}
		return(C_Unauthorized_645);
	}
/*判断R1不等于*/
	if(pValidData[C_R1_O] != 0x1B)
	{
		return(C_Unauthorized_645);
	}
/*判断截止时间是否有效，无效应答其他错误*/
	if(PF_DataTimeActive(&pValidData[C_R3_O], C_DT_Start_ss, CLDate_Time) != C_OK)
	{
		return(C_OtherErr_645);
	}
/*判断系统时间在命令截止时间之前*/
	ValidDataLen = CLDate_Time;
	if(InF_Read_Data(CDate_Time, Clock, &ValidDataLen, &V_usDataEncode) == C_OK)
	{/*时间有效*/
		if( PF_Campare_Data( &pValidData[C_R3_O], Clock, CLDate_Time) == C_LessThan )
		{
			return(C_Unauthorized_645);
		}
	}
/*将需清零事件标识码放置到02级密码事件清零对应事件标识码位置.*/
	pV_645Frame->Data[C_O_EventClear_DI] = pValidData[C_R9_O];
	pV_645Frame->Data[C_O_EventClear_DI + 1] = pValidData[C_R9_O + 1];
	pV_645Frame->Data[C_O_EventClear_DI + 2] = pValidData[C_R9_O + 2];
	pV_645Frame->Data[C_O_EventClear_DI + 3] = pValidData[C_R9_O + 3];

	return(C_OK);
}
/***************************************************************************
函数原型 	Comm_DemandClear
函数功能	完成需清命令解析及应答
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	通道交互变量
函数备注
***************************************************************************/
void		Comm_DemandClear(Str_Comm_645 *pV_645Frame)
{
	uchar8	Err;

/*根据对应的密级进行相应的逻辑判断	*/
	if(pV_645Frame->Data[CPW_SpecialO_V_645] == 0x98)
	{
		Err = Comm_98DemandClear(pV_645Frame);
	}
	else if( ( pV_645Frame->Data[CPW_SpecialO_V_645] == 0x02 )
		   || ( pV_645Frame->Data[CPW_SpecialO_V_645] == 0x04 ) )
	{
		Err = Comm_04DemandClear(pV_645Frame);
	}
	else
	{
		/*密级不对*/
		Err = C_Unauthorized;
	}
/*逻辑判断后，进行相应事件触发和应答*/
	if(Err == C_OK)
	{
/*需清命令成功,触发需清消息，同时将需清命令成功发布给相应模块*/
		SF_DemandClear();
	}
	else
	{
		SV_Comm_Parse_Local.SafeControlFlag = 0;
		Err = SF_Error_ChangeTo645(Err);
	}
	Comm_Response_Set_ReadErr(Err, pV_645Frame);
}
/***************************************************************************
函数原型 	Comm_98DemandClear
函数功能	完成98级密码需清命令的相关验证
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	C_OK/C_Unauthorized/C_OtherErr
全局变量 	无
函数备注	645协议处理数据格式需要再核对 本次修改时间格式只保证数据不溢出 lzy 20211023
***************************************************************************/
uchar8	Comm_98DemandClear(Str_Comm_645 *pV_645Frame)
{
	ushort16	SError, ValidDataLen, V_usDataEncode;
	uchar8	*pValidData;
	uchar8	Clock[CLDate_Time];

/*判断长度*/
	if( pV_645Frame->DataLen <= ( CLen_OpCode + CLen_CommPW ) )
	{
		return(C_OtherErr);
	}

/*调用安全模块接口函数*/
	pValidData = &pV_645Frame->Data[CData_OtherO_V_645];
	ValidDataLen = pV_645Frame->DataLen - CLen_CommPW - CLen_OpCode;
	/*解密后数据在pValidData，长度为8.按照R1-R8排列*/
	SError = InF_S_DemandClear(pValidData, (uchar8 *)&ValidDataLen);
	if(SError != C_OK)
	{
		if(SError == C_SERR_ESAM_VF)
		{/*ESAM验证失败，200次++*/
			Comm_DealwithSPTVariable(C_SPTNumAdd);
		}
		return(C_Unauthorized);
	}
/*判断R1不等于*/
	if(pValidData[C_R1_O] != 0x19)
	{
		return(C_Unauthorized);
	}
/*判断截止时间是否有效，无效应答其他错误*/
	if(PF_DataTimeActive(&pValidData[C_R3_O], C_DT_Start_ss, CLDate_Time) != C_OK)
	{
		return(C_OtherErr);
	}
/*判断系统时间在命令截止时间之前*/
	ValidDataLen = CLDate_Time;
	if(InF_Read_Data(CDate_Time, Clock, &ValidDataLen, &V_usDataEncode) == C_OK)
	{/*时间有效*/
		if(PF_Campare_Data(&pValidData[C_R3_O], Clock, CLDate_Time) == C_LessThan)
		{
			return(C_Unauthorized);
		}
	}
	return(C_OK);

}
/***************************************************************************
函数原型 	Comm_04DemandClear
函数功能	通信需清04(02)级密码判断
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	C_OK/C_OtherErr/C_Unauthorized
全局变量 	无
函数备注
***************************************************************************/
uchar8	Comm_04DemandClear(Str_Comm_645 *pV_645Frame)
{
/*判断是否厂内，不在厂内用02、04级清零应答无权限*/
	if( JudgeTimerExceed10min(&SI_JTimer_BSOn2500) != C_TimerEnable )
	{
		return(C_Unauthorized);
	}
/*判断长度*/
	if( pV_645Frame->DataLen != (CLen_OpCode + CLen_CommPW) )
	{
		return(C_OtherErr);
	}

/*判断密码是否正确*/
	if( Is_PW_OK( &( pV_645Frame->Data[CPW_SpecialO_V_645] ) ) != C_OK )
	{
		return(C_Unauthorized);
	}

	return(C_OK);

}
/***************************************************************************
函数原型 	Comm_MeterClear
函数功能	通信总清命令解析及应答
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	通道交互变量
函数备注	MeterClearFlag标志在本函数中置2个，在2个权限判断函数中置一个。
***************************************************************************/
void		Comm_MeterClear(Str_Comm_645 *pV_645Frame)
{
	uchar8	Err;

	SV_Comm_Parse_Local.MeterClearFlag = SV_Comm_Parse_Local.MeterClearFlag | C_ClearMeterSafeFlag_1;
/*判断表型是否支持该命令*/
	if(IsMeterTypeSupport(pV_645Frame) != C_OK)
	{
		Comm_Response_Set_ReadErr(C_Unauthorized, pV_645Frame);
		SV_Comm_Parse_Local.MeterClearFlag = 0;
		SV_Comm_Parse_Local.SafeControlFlag = 0;
		return;
	}

/*根据密级进行对应判断	*/
	if(pV_645Frame->Data[CPW_SpecialO_V_645] == 0x98)
	{
		/*98级密码，适用于厂外清零*/
		Err = Comm_98MeterClear(pV_645Frame);
	}
	else if(pV_645Frame->Data[CPW_SpecialO_V_645] == 0x02)
	{
		/*02级密码，适用于厂内清零,或配合综合市场配合编程开关清零*/
		Err = Comm_02MeterClear(pV_645Frame);
	}
	else
	{
		/*密级不对*/
		Err = C_Unauthorized;
	}

	if(Err == C_OK)
	{
		/*698兼容645修改*/
		if( ( InF_JudgeKeyStatus() == C_StateOfOfficialKey )    /*正式密钥不允许清零，安全规范*/
		 && ( JudgeTimerExceed10min(&SI_JTimer_BSOn2500 ) == C_TimerDisable ) )
		{
			Err = C_Unauthorized;	/*密码错或未授权*/
		}
		else
		{
			SF_MeterClear(pV_645Frame);
		}
	}
	else
	{
		SV_Comm_Parse_Local.MeterClearFlag = 0;
		SV_Comm_Parse_Local.SafeControlFlag = 0;
		Err = SF_Error_ChangeTo645(Err);
	}
	Comm_Response_Set_ReadErr(Err, pV_645Frame);
}
/***************************************************************************
函数原型 	Comm_02MeterClear
函数功能	完成02级清零相关验证
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	C_OK/C_OtherErr/C_Unauthorized
全局变量 	无
函数备注
***************************************************************************/
uchar8	Comm_02MeterClear(Str_Comm_645 *pV_645Frame)
{
	SV_Comm_Parse_Local.MeterClearFlag = SV_Comm_Parse_Local.MeterClearFlag | C_ClearMeterSafeFlag_2;
/*判断是否厂内，不在厂内用02、04级清零应答无权限*/
	if( JudgeTimerExceed10min(&SI_JTimer_BSOn2500) != C_TimerEnable )
	{
		return(C_Unauthorized);
	}
/*判断长度*/
	if( pV_645Frame->DataLen != (CLen_OpCode + CLen_CommPW) )
	{
		return(C_OtherErr);
	}

/*判断密码是否正确*/
	if( Is_PW_OK(&(pV_645Frame->Data[CPW_SpecialO_V_645])) != C_OK )
	{
		return(C_Unauthorized);
	}

	return(C_OK);
}
/***************************************************************************
函数原型 	IsMeterTypeSupport
函数功能	判断表的类型是否支持该命令
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	C_OK支持/C_Error不支持
全局变量
函数备注	注意，这里对非法标识码不进行判断。非法标识码
				天生在通信模块解析函数中会进行判断的。

***************************************************************************/
#define	CLen_TB_OnlyLocalSupport		7
const	ulong32	TB_OnlyLocalSupport[CLen_TB_OnlyLocalSupport] =
{
	CCurr_Ladder_Price,
	CCurr_Price,
	CCurr_Rate_Price,
	CChange_Rate,
	CChange_Ladder,
	CStep_Num,
	CInset_Card_State
};

uchar8	IsMeterTypeSupport(Str_Comm_645 *pV_645Frame)
{
	uchar8	i;

/*总清命令，本地表不支持98级总清*/
	if(pV_645Frame->C == 0x1A)
	{
		if(pV_645Frame->Data[CPW_SpecialO_V_645] == 0x98)
		{
			if(C_Meter_Type == C_L_SmartMeter)
			{	/*本地表不支持1A命令清零*/
				return(C_Error);
			}
		}
		return(C_OK);
	}
/*安全规范命令*/
	if(pV_645Frame->C == 0x03)
	{
		if(C_Meter_Type == C_L_SmartMeter)
		{/*本地表都支持*/
			return(C_OK);
		}
		else
		{/*远程和智能表*/
			switch(pV_645Frame->DI)
			{
				case		CDI_Init_Money:		/*远程钱包初始化命令*/
				case		CDI_ROpenAnAccount:
				case		CDI_RChgBL:
					return(C_Error);
				default:						/*其他命令都支持*/
					return(C_OK);
			}
		}

	}
/*设置*/
	if(pV_645Frame->C == 0x14)
	{
		/*14设置命令表型相关判断在14命令解析判断数据有效性函数Is_SetParmData_Ok中判断*/
		/*根据表型进行判断*/
		return(C_OK);
	}

/*读命令*/
	if(pV_645Frame->C == 0x11)
	{/*读本地表所有命令都支持，个别命令智能表、费控表支持*/
		if(C_Meter_Type == C_L_SmartMeter)
		{
			return(C_OK);
		}
		/*费控表和智能表*/
		if(pV_645Frame->Data[C_O_DI3] == 0x00)
		{/*电能类*/
			if(pV_645Frame->Data[C_O_DI2] == 0x0D)
			{/*年结算仅本地表支持*/
				return(C_Error);
			}
			if(pV_645Frame->Data[C_O_DI2] == 0x90)
			{/*剩余金额、透支金额仅本地表支持*/
				return(C_Error);
			}
			return(C_OK);
		}
		if( ( pV_645Frame->DI & 0xFFFF0000 ) == 0x05080000 )
		{/*剩余金额日冻结仅本地表支持*/
			return(C_Error);
		}
		if( ( pV_645Frame->DI & 0xFFFF0000 ) == 0x05050000 )
		{/*费率电价切换冻结只有本地表才支持*/
			return(C_Error);
		}
		if( ( pV_645Frame->DI & 0xFFFF0000 ) == 0x05070000 )
		{/*阶梯表切换冻结只有本地表才支持*/
			return(C_Error);
		}
		if( ( pV_645Frame->DI & 0xFFFFFF00 ) == 0x04001000 )
		{/*报警金额限制等仅本地表支持*/
			return(C_Error);
		}
		if( ( pV_645Frame->DI & 0xFFFF0000 ) == 0x04050000 )
		{/*费率电价类，仅本地表支持*/
			return(C_Error);
		}
		if( ( pV_645Frame->DI & 0xFFFF0000 ) == 0x04060000 )
		{/*阶梯电价类*/
			return(C_Error);
		}
		if( ( pV_645Frame->DI & 0xFFFFFF00 ) == 0x03300F00 )
		{/*费率表编程记录*/
			return(C_Error);
		}
		if( ( pV_645Frame->DI & 0xFFFFFF00 ) == 0x03301000 )
		{/*阶梯表编程记录*/
			return(C_Error);
		}
		if( ( pV_645Frame->DI & 0xFFFFFF00 ) == 0x03301300 )
		{/*异常插卡记录记录*/
			return(C_Error);
		}
		if( pV_645Frame->DI == 0x03301400 )
		{/*非法插卡次数*/
			return(C_Error);
		}
		if( ( pV_645Frame->DI & 0xFFFF0000 ) == 0x03330000 )
		{/*购电记录*/
			return(C_Error);
		}
		if( ( pV_645Frame->DI & 0xFFFF0000 ) == 0x03340000 )
		{/*退费记录*/
			return(C_Error);
		}
		for( i = 0; i < CLen_TB_OnlyLocalSupport; i++ )
		{/*剩余查表确认是否仅为本地表支持*/
			if(pV_645Frame->DI == TB_OnlyLocalSupport[i])
			{
				return(C_Error);
			}
		}
		return(C_OK);
	}
/*其他命令，都支持*/
	return(C_OK);
}
/***************************************************************************
函数原型 	Is_PW_OK
函数功能	判断密码是否正确
输入参数	pCommPW		:通信密码地址，固定4字节
输出参数 	无
返回参数	C_OK/C_Error/C_SupperPW_OK
全局变量 	无
函数备注	对于密码闭锁，只要要0204密码，都要管密码闭锁
20140715修改:
				增加超级密码:
				1、仅在密码读不出。即CRC错误时判断是否为超级密码
				2、仅在进入厂内模式命令或在厂内模式下
				        采用0c命令设置密码使用。
***************************************************************************/
#define	PA_O_Comm		0
#define	PW_O_Comm		1
uchar8	Is_PW_OK(uchar8	*pCommPW)
{
	uchar8		PW[CLKey_0_Class];
	ulong32		PW_DI;
	ushort16	PW_Len = CLKey_0_Class, V_usDataEncode;
	uchar8		KeyClassFlag = 0xF0;

	switch(pCommPW[PA_O_Comm])
	{
		case		0x00:
			PW_DI = CKey_0_Class;
			break;
		case		0x01:
			PW_DI = CKey_1_Class;
			break;
		case		0x02:
			PW_DI = CKey_2_Class;
			KeyClassFlag = C_Key02Flag;
			break;
		case		0x03:
			PW_DI = CKey_3_Class;
			break;
		case		0x04:
			PW_DI = CKey_4_Class;
			KeyClassFlag = C_Key04Flag;
			break;
		case		0x05:
			PW_DI = CKey_5_Class;
			break;
		case		0x06:
			PW_DI = CKey_6_Class;
			break;
		case		0x07:
			PW_DI = CKey_7_Class;
			break;
		case		0x08:
			PW_DI = CKey_8_Class;
			break;
		case		0x09:
			PW_DI = CKey_9_Class;
			break;
		default:
			return(C_Error);
	}

/*首先判断密码是否闭锁，是闭锁直接返回密码错误*/
	if( Comm_DealwithSPTVariable(C_JudgeKeyErr | KeyClassFlag) == C_KeyErr_Num_Over )
	{
		return(C_Error);
	}

/*判断传递进来密码是否正确*/
	if( InF_Read_Data(PW_DI, &PW[0], &PW_Len, &V_usDataEncode ) == C_OK )
	{/*密码读出来才去判断密码正确还是错误，*/
		if( PF_Campare_Data(&PW[0], &pCommPW[PW_O_Comm], PW_Len ) == C_Equal )
		{
			Comm_DealwithSPTVariable(C_ClrKeyErrNum | KeyClassFlag);
			return(C_OK);
		}
		else
		{
			if(InF_JudgeIJTimer() != C_OK)							/*厂内密码错不闭锁*/
			{
				Comm_DealwithSPTVariable(C_KeyErrNumAdd | KeyClassFlag);
			}
			return(C_Error);
		}
	}
	else
	{/*如果读不出来，判断是否为超级密码。是返回超级密码正确*/
		if( ( pCommPW[PA_O_Comm] == 0x02 ) && ( pCommPW[PW_O_Comm] == 0x22 )
		 && ( pCommPW[PW_O_Comm + 1] == 0x12 ) && ( pCommPW[PW_O_Comm + 2] == 0x11 ) )
		{/*密级02，密码是111222属于超级密码*/
			return(C_SupperPW_OK);
		}
		return(C_Error);
	}
}
/***************************************************************************
函数原型 	Comm_98MeterClear
函数功能	完成98级清零相关验证
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	C_OK/C_OtherErr/C_Unauthorized
全局变量 	无
函数备注	645协议处理数据格式需要再核对 本次修改时间格式只保证数据不溢出 lzy 20211023
***************************************************************************/
uchar8	Comm_98MeterClear(Str_Comm_645 *pV_645Frame)
{
	ushort16	SError, ValidDataLen, V_usDataEncode;
	uchar8		*pValidData;
	uchar8		Clock[CLDate_Time];

	SV_Comm_Parse_Local.MeterClearFlag = SV_Comm_Parse_Local.MeterClearFlag | C_ClearMeterSafeFlag_2;

/*判断长度*/
	if( pV_645Frame->DataLen <= ( CLen_OpCode + CLen_CommPW ) )
	{
		return(C_OtherErr);
	}

/*调用安全模块接口函数*/
	pValidData = &pV_645Frame->Data[CData_OtherO_V_645];
	ValidDataLen = pV_645Frame->DataLen - CLen_CommPW - CLen_OpCode;
	/*解密后数据在pValidData，长度为8.按照R1-R8排列*/
	SError = InF_S_MeterClear(pValidData, (uchar8 *)&ValidDataLen);
	if(SError != C_OK)
	{
		if(SError == C_SERR_ESAM_VF)
		{/*ESAM验证失败，200次++*/
			Comm_DealwithSPTVariable(C_SPTNumAdd);
		}
		return(C_Unauthorized);
	}
/*判断R1不等于*/
	if(pValidData[C_R1_O] != 0x1A)
	{
		return(C_Unauthorized);
	}
/*判断截止时间是否有效，无效应答其他错误*/
	if( PF_DataTimeActive( &pValidData[C_R3_O], C_DT_Start_ss, CLDate_Time ) != C_OK )
	{
		return(C_OtherErr);
	}
/*判断系统时间在命令截止时间之前*/
	ValidDataLen = CLDate_Time;
	if(InF_Read_Data( CDate_Time, Clock, &ValidDataLen, &V_usDataEncode ) == C_OK )
	{/*时间有效*/
		if( PF_Campare_Data( &pValidData[C_R3_O], Clock, CLDate_Time ) == C_LessThan )
		{
			return(C_Unauthorized);
		}
	}
	return(C_OK);
}
/***************************************************************************
函数原型 	Comm_SecurityParse
函数功能	通信03命令解析及应答
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	通道交互变量
函数备注
***************************************************************************/
void		Comm_SecurityParse(Str_Comm_645 *pV_645Frame)
{
/*判断是否处于低功耗下通信*/
	if(pV_645Frame->PowerFlag != C_PowerOn)
	{
		Comm_Response_03_Err(C_SERR_OtherErr, pV_645Frame);
		return;
	}
/*表型是否支持*/
	if(IsMeterTypeSupport(pV_645Frame) != C_OK)
	{
		Comm_Response_03_Err(C_SERR_OtherErr, pV_645Frame);
		return;
	}
/*判断安全认证命令*/
	switch(pV_645Frame->DI)
	{
		case		CDI_Auth:		/*身份认证*/
			Comm_Authentication(pV_645Frame);
			break;
		case		CDI_IRCReq_645:		/*红外认证请求命令*/
			Comm_IRCertification_Request(pV_645Frame);
			break;
		case		CDI_IR_ExtAuth_645:	/*红外认证*/
			Comm_IRCertification_Instruction(pV_645Frame);
			break;
		default:
			Comm_Response_03_Err(C_SERR_OtherErr, pV_645Frame);
			break;
	}

	return;
}

/***************************************************************************
函数原型 	InF_PurchaseDL
函数功能	将充值金额充值到数据层，并写购电记录，同步ESAM钱包文件
输入参数	PPMoney					:本次购电金额，Hex单位为分
				V_SafeFlag				:安全标志，=C_W_SafeFlag有效
输出参数 	无
返回参数	无
函数备注	在调用本函数前，已确认能充值
				经过了囤积、购电次数，ESAM验证等步骤。
***************************************************************************/
void		InF_PurchaseDL(ulong32	PPMoney,uchar8	V_SafeFlag)
{
	uchar8	V_ucbuf[CLChargeBal_Hex_Cent], Flag;
	ulong32	PreRemainMoney;
    ushort16 V_usDataLen, V_usDataEncode[30] = {0x00};

/*首先读取数据层的剩余金额，因为调用本函数前已读过该变量，如果
读不出是不让充值的。*/
    V_usDataLen = CLChargeBal_Hex_Cent;
	InF_GetData_ObjectManage(CChargeBal_Hex_Cent, V_ucbuf, &V_usDataLen, V_usDataEncode);
	PF_Buffer4ToUlong32(V_ucbuf, &PreRemainMoney, CLChargeBal_Hex_Cent);

/*进行购电事件记录并进行充值*/
	Flag = C_Money_Purchase;
	InF_WRPre1PowerPurchaseRecord(PPMoney, V_SafeFlag, Flag);
/*/同步ESAM*/
	V_usDataLen = CLChargeBal_Hex_Cent;
	if(InF_GetData_ObjectManage(CChargeBal_Hex_Cent, V_ucbuf, &V_usDataLen, V_usDataEncode) == C_OK)
	{
		InF_S_UpdataChargeBalInESAM(V_ucbuf);
	}
}
/***************************************************************************
函数原型 	InF_Compare_CustomerNum
函数功能	比对客户编号
输入参数	*pCustomerNum			:输入的客户编号，固定为6字节，
										:符合645小端模式
输出参数 	无
返回参数	C_OK					:和数据层客户编号一致。
				C_Error					:和数据层客户编号不一样
全局变量 	无
函数备注	无
***************************************************************************/
uchar8	InF_Compare_CustomerNum(uchar8	 *pCustomerNum)
{
	uchar8	 buf[CLCustomer_Num];
	ushort16 DataLen = CLCustomer_Num, V_usDataEncode;

	if(InF_Read_Data( CCustomer_Num, buf, &DataLen, &V_usDataEncode ) != C_OK )
	{
		return(C_Error);
	}
	if(PF_Campare_Data( buf, pCustomerNum, CLCustomer_Num ) == C_Equal )
	{
		return(C_OK);
	}
	else
	{
		return(C_Error);
	}
}
/***************************************************************************
函数原型 	InF_V_CustomerNumWithEsam
函数功能	验证客户编码是否为BCD,Mac是否正确，全部正确刷新ESAM
输入参数	*pCustomerNum			:输入的客户编号，固定为6字节+4字节Mac，
										:符合645小端模式
输出参数 	无
返回参数	C_OK/C_SERR_OtherErr/C_SERR_ESAM_VF
全局变量 	无
函数备注	无
***************************************************************************/
ushort16	InF_V_CustomerNumWithEsam(uchar8	*pCustomerNum)
{
	ushort16		Serr16;

/*首先判断是否为BCD*/
	if( PF_Judge_BCD( CLCustomer_Num, pCustomerNum ) != C_OK )
	{
		return(C_SERR_OtherErr);
	}
/*进行ESAM的Mac验证，没有问题，则刷新ESAM参数和运行文件*/
	Serr16 = InF_S_WritePara_PlainTextMAC(CCustomer_Num, pCustomerNum, ( CLCustomer_Num + C_MacLen ) );

	return(Serr16);
}

/***************************************************************************
函数原型 	InF_Judge_ChgBal_PC_Num
函数功能	判断购电次数和充值金额
输入参数	V_ChgBal				:待充值金额，Hex，单位为分
				V_PC_Num			:待判断的购电次数，Hex
输出参数 	无
返回参数	C_PC_Num_Equal		:	购电次数相等
				C_SERR_RechargeNumErr:	表示大于表内购电次数2及2以上
				C_SERR_RechargeHoarding:	购电次数差1，但超囤积或溢出
				C_MeterPC_Num_Large	:	表内购电次数大。
				C_SERR_OtherErr		:	其他错误
				C_Can_EPurchase		:	购电次数差1，金额没有超囤积可以充值
全局变量
函数备注	本函数先判断了购电次数，购电次数满足条件充值条件后，
				再进行充值金额超囤积的判断
***************************************************************************/
ushort16		InF_Judge_ChgBal_PC_Num(ulong32	V_ChgBal,ulong32 V_PC_Num)
{
	ulong32		Meter_PC_Num;
	ulong32		Meter_OverDraft;
	ulong32		Meter_ChargeBal;
	ulong32		Hoarding_Money_Hex_Cent;
	uchar8		V_ucbuf[CLChargeBal_Hex_Cent];
    ushort16    V_usDataLen, V_usDataEncode[30] = {0x00};

/*读数据层剩余金额到Meter_ChargeBal 单位是分，Hex格式*/
    V_usDataLen = CLChargeBal_Hex_Cent;
	if( InF_GetData_ObjectManage( CChargeBal_Hex_Cent, V_ucbuf, &V_usDataLen, V_usDataEncode ) != C_OK )
	{/*数据层剩余金额读不出，不让充值*/
		return(C_SERR_OtherErr);
	}
	PF_Buffer4ToUlong32(V_ucbuf, &Meter_ChargeBal, CLChargeBal_Hex_Cent);

/*读数据层的透支金额*/
    V_usDataLen = CLOverDraft_Hex_Cent;
	if( InF_GetData_ObjectManage( COverDraft_Hex_Cent, V_ucbuf, &V_usDataLen, V_usDataEncode ) != C_OK )
	{/*数据层透支金额读不出，不让充值*/
		return(C_SERR_OtherErr);
	}
	PF_Buffer4ToUlong32(V_ucbuf, &Meter_OverDraft, CLOverDraft_Hex_Cent);

/*读ESAM中的购电次数*/
    V_usDataLen = CLOverDraft_Hex_Cent;
    if( InF_GetData_ObjectManage( CPurchasePowTime, V_ucbuf, &V_usDataLen, V_usDataEncode ) != C_OK )
	{/*读不出购电次数*/
		return(C_SERR_OtherErr);
	}
    PF_Buffer4ToUlong32(V_ucbuf, &Meter_PC_Num, CLOverDraft_Hex_Cent);

/*判断购电次数*/
	if(V_PC_Num < Meter_PC_Num)
	{
		return(C_MeterPC_Num_Large);
	}
	else if(V_PC_Num == Meter_PC_Num)
	{
		return(C_PC_Num_Equal);
	}
/*以下待判断的购电次数大于表内购电次数*/
	if( ( V_PC_Num - Meter_PC_Num ) != 1 )
	{
		return(C_SERR_RechargeNumErr);
	}
/*仅大于1，判断超囤积*/
/*读参变量超囤积*/
	if( InF_Read_Data( CHoarding_Money, V_ucbuf, &V_usDataLen, V_usDataEncode ) == C_OK )
	{
		PF_BCDtoHexBytes( V_ucbuf, &Hoarding_Money_Hex_Cent, CLHoarding_Money );
		if(Hoarding_Money_Hex_Cent == 0)
		{/*限值设置为0，等效于999999.99元，安全规范7.5*/
			Hoarding_Money_Hex_Cent = 99999999;
		}
	}
	else
	{/*如果限值读不出，默认为999999.99元*/
		Hoarding_Money_Hex_Cent = 99999999;
	}
/*判断有没有超囤积限值*/
	if(V_ChgBal > 99999999)
	{/*太大，直接退出。*/
		return(C_SERR_RechargeHoarding);
	}
	V_ChgBal = V_ChgBal + Meter_ChargeBal;		/*充值金额+剩余金额*/
	if(V_ChgBal <= Meter_OverDraft)
	{/*剩余金额小于等于透支金额,肯定允许充值*/
		return(C_Can_EPurchase);
	}
	else if( ( V_ChgBal - Meter_OverDraft ) > Hoarding_Money_Hex_Cent )
	{/*超囤积*/
		return(C_SERR_RechargeHoarding);
	}
	else
	{
		return(C_Can_EPurchase);
	}
}

/***************************************************************************
函数原型 	 uchar8 InF_DealWith_L_R_OAAFlag(uchar8	Method,uchar8	Value)
函数功能	处理远程开户状态
输入参数
Value:		C_HaveOpenAnAccount 0x68为处于开户状态
	   		C_HaveNoOpenAnAccount 0x00为处于未开户状态
Method:		C_Judge_Method_R 0x01为判断远程开户状态
			C_Set_Method_R 0x02为处理远程开户状态
			C_Judge_Method_L 0x10为判断本地开户状态
			C_Set_Method_L 0x11为处理本地开户状态
输出参数 	无
返回参数	C_HaveOpenAnAccount/C_HaveNoOpenAnAccount
全局变量 	无
函数备注	1、设置时会调用刷新电表运行状态字3函数
				2、设置时如果设置不成功，会返回C_HaveNoOpenAnAccount
***************************************************************************/
#define	C_Method_R	0x00
#define	C_Method_L	0x10
uchar8	InF_DealWith_L_R_OAAFlag(uchar8	Method,uchar8	Value)
{
	uchar8		AccountState[CLRemote_Local_State + 5], V_ucStatusOff, V_ucSource;
	ushort16	DataLen = CLRemote_Local_State, V_usDataEncode;

/*首先读数据层远程本地开户状态。读不出，默认为未开户*/
	if(InF_Read_Data(CRemote_Local_State, AccountState, &DataLen, &V_usDataEncode) != C_OK)
	{
		AccountState[C_O_ROpenAnAccount] = C_HaveNoOpenAnAccount;
		AccountState[C_O_LOpenAnAccount] = C_HaveNoOpenAnAccount;
	}
/*判断是否为设置方法，是则刷新数据层对应开户标志为Value值，同时刷新状态字3*/
	V_ucSource = (Method & 0xF0);
	if( V_ucSource == C_Method_R )
	{
		V_ucStatusOff = C_O_ROpenAnAccount;
	}
	else if( V_ucSource == C_Method_L )
	{
		V_ucStatusOff = C_O_LOpenAnAccount;
	}
	if( ( Method == C_Set_Method_R )|| ( Method == C_Set_Method_L ) )
	{
		AccountState[V_ucStatusOff] = Value;
		InF_Write_Data(C_Msg_Communication, CRemote_Local_State, AccountState, CLRemote_Local_State, C_W_SafeFlag);
		InF_UpdateAccountStateInMeterStatus3();
	}
	return(AccountState[V_ucStatusOff]);
}

/***************************************************************************
函数原型 	InF_UpdateAccountStateInMeterStatus3
函数功能	更新电表运行状态字3中远程本地开户状态
输入参数	无
输出参数 	无
返回参数	无
全局变量 	无
函数备注	1、根据数据层02FE0501刷新电表运行状态字3中远程本地开户状态
				2、本函数在远程钱包初始化命令、远程开户命令时调用
				3、本函数在本地插入参数预制卡，本地开户是调用
				4、通信1min调用一次
			注意本函数在InF_DealWith_L_OAAFlag中set方法中调用了，
			所以这里不要再调用InF_DealWith_L_OAAFlag的Judge方法，会形成互调!
***************************************************************************/
void		InF_UpdateAccountStateInMeterStatus3(void)
{
	uchar8		AccountState[CLRemote_Local_State];
	ushort16	DataLen, V_usDataEncode;
	uchar8		Meter_Work_State3[CLMeter_Work_State3 + 3];

/*读取状态字3*/
	DataLen = CLMeter_Work_State3;
	InF_Read_Data(CMeter_Work_State3, Meter_Work_State3, &DataLen, &V_usDataEncode);
	if(C_Meter_Type == C_L_SmartMeter)
	{
/*读取数据层专门保存的开户状态	*/
		DataLen = CLRemote_Local_State;
		InF_Read_Data(CRemote_Local_State, AccountState, &DataLen, &V_usDataEncode);
/*根据02FE0501写电表运行状态3中开户状态。*/
/*bit14为本地开户 bit15为远程开户。*/
/*=0表示开户，=1表示未开户*/
		if(AccountState[C_O_ROpenAnAccount] == C_HaveOpenAnAccount)
		{/*远程已开户，Bit15 = 0*/
			Meter_Work_State3[CO_RemoteOAccount] = Meter_Work_State3[CO_RemoteOAccount] & (~CB_RemoteOAccount);
		}
		else
		{/*远程未开户，Bit15 = 1*/
			Meter_Work_State3[CO_RemoteOAccount] = Meter_Work_State3[CO_RemoteOAccount] | CB_RemoteOAccount;
		}
		if(AccountState[C_O_LOpenAnAccount] == C_HaveOpenAnAccount)
		{/*本地已开户，Bit14 = 0*/
			Meter_Work_State3[CO_LocalOAccount] = Meter_Work_State3[CO_LocalOAccount] & (~CB_LocalOAccount);
		}
		else
		{/*本地未开户，Bit14 = 1*/
			Meter_Work_State3[CO_LocalOAccount] = Meter_Work_State3[CO_LocalOAccount] | CB_LocalOAccount;
		}
	}
	else
	{/*远程已开户，Bit15 = 0*/
		Meter_Work_State3[CO_RemoteOAccount] = Meter_Work_State3[CO_RemoteOAccount] & (~CB_RemoteOAccount);
	/*本地已开户，Bit14 = 0*/
		Meter_Work_State3[CO_LocalOAccount] = Meter_Work_State3[CO_LocalOAccount] & (~CB_LocalOAccount);
	}
	InF_Write_Data(C_Msg_Communication, CMeter_Work_State3, Meter_Work_State3, CLMeter_Work_State3, C_W_SafeFlag);
}
/***************************************************************************
函数原型 	InF_WRPre1PowerPurchaseRecord
函数功能	写最近一次购电记录
输入参数	V_ulBuyMoney				:购电金额，格式:
			C_SafeFlag					安全标志
			Flag						命令标志
输出参数 	无
返回参数	无
全局变量 	无
函数备注
***************************************************************************/
void		InF_WRPre1PowerPurchaseRecord(ulong32 V_ulBuyMoney,uchar8 C_SafeFlag,uchar8 Flag)
{
	uchar8	 V_ucDataBuff[300] = {0};
	ushort16 V_usOffset = 0, V_ResidualLength, V_ucRelateoff;
	uchar8	 V_Event_Flag;

	V_usOffset = SF_GetProgFixedData_698(CBuyCurr_Degree, V_ucDataBuff);	/*取固定列数据*/

	V_ResidualLength = 300 - V_usOffset;									/*剩余buff长度*/
	V_Event_Flag = 0x01;
	V_ucRelateoff = V_usOffset;												/*保存上一次的事件头偏移地址，便于写恢复用*/
	if(Inf_GetRecordData(&V_ucDataBuff[V_usOffset], &V_ResidualLength, CBuyCurr_OADTab, V_Event_Flag) == C_OK)	/*获取关联OAD数据*/
	{
		V_usOffset += V_ResidualLength;										/*数据总长度*/
	}
	InF_Write_Data(C_Msg_Communication, CBuyCurr_FF_Note_1, V_ucDataBuff, V_usOffset, C_W_SafeFlag);			/*写购电记录*/

/*钱包操作*/
	InF_MoneyToPurchase(V_ulBuyMoney, Flag, C_SafeFlag );
/*写恢复*/
	V_ResidualLength = 300 - V_ucRelateoff;
	if(Inf_GetRecordData(&V_ucDataBuff[V_ucRelateoff], &V_ResidualLength, CBuyCurr_OADTab, 0x02)	== C_OK)		/*取结束数据*/
	{
		V_ucRelateoff += V_ResidualLength;
	}
	InF_Write_Data(C_Msg_Communication, (CBuyCurr_FF_Note_1 + 1), V_ucDataBuff, V_ucRelateoff, C_W_SafeFlag);

	Inf_EventReport_HP(C_BuyCurrEventNo, C_Happen_EventReport);

	return;
}

/***************************************************************************
函数原型 	Comm_IRCertification_Instruction
函数功能	03-红外认证
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	通道交互变量
函数备注
***************************************************************************/
void	Comm_IRCertification_Instruction( Str_Comm_645	*pV_645Frame )
{
	uchar8	buf[C_TimerExceed10minLen];
	ushort16	SError;
	uchar8	*pValidData;
	ushort16 V_usDatalen,V_usDataEncode;

	memset( buf, 0, C_TimerExceed10minLen );/*清零备用*/
/*判断长度是否合理*/
	if( pV_645Frame->DataLen != (CLen_DI + CLen_OpCode + CL_Auth_CiphertextK2 ) )
	{
		Comm_Response_03_Err(C_SERR_OtherErr, pV_645Frame);
		return;
	}
/*调用安全模块接口函数，进行红外认证*/
	pValidData = &(pV_645Frame->Data[CData_OtherO_V_645]);
	SError = InF_S_IRCertification_Instruction(pValidData);
	if( SError != C_OK )
	{
		if( SError == C_SERR_ESAM_VF )
		{/*ESAM验证失败，200次++*/
			Comm_DealwithSPTVariable(C_SPTNumAdd);
		}
		Comm_Response_03_Err(SError, pV_645Frame);
	/*红外认证失败结束红外认证有效*/
		DealWith_IR_Auth_Timer_645(C_Set_TimerExceed10min, &buf[0]);
	}
	else
	{/*正确，应答并赋值红外认证定时器	*/
		Comm_11_03Response_Normal(pV_645Frame, pValidData, 0);

		buf[1] = 0;
		V_usDatalen = 4;
		SError = InF_GetData_ObjectManage(C_IRAuth_Timer, buf, &V_usDatalen, &V_usDataEncode);
		PF_OneDataReversed(buf, buf, V_usDatalen);

		if(SError != C_OK)
		{
			buf[0] = C_IRAuthTime_L;		/*数据层读不出数据，则默认为30分钟*/
			buf[1] = C_IRAuthTime_H;
		}
		if(buf[0] == 0)						/*认证时间为0或者非BCD码,默认*/
		{
			buf[0] = C_IRAuthTime_L;		/*数据非法,默认为30分钟*/
			buf[1] = C_IRAuthTime_H;
		}
		DealWith_IR_Auth_Timer_645(C_Set_TimerExceed10min, &buf[0]);
	}
	return;
}
/***************************************************************************
函数原型 	Comm_IRCertification_Request
函数功能	03-红外认证请求
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	通道交互变量
函数备注
***************************************************************************/
void	Comm_IRCertification_Request( Str_Comm_645	*pV_645Frame )
{
	uchar8	buf[C_TimerExceed10minLen];
	ushort16	SError;
	uchar8	ValidDataLen;
	uchar8	*pValidData;

/*首先设置红外认证时效为无效*/
	memset( buf, 0, C_TimerExceed10minLen );
	DealWith_IR_Auth_Timer_645(C_Set_TimerExceed10min, &buf[0]);

/*红外认证和身份认证有何关系?红外认证时取消身份认证，由小郭找出处*/
	DealWith_ID_Auth_Timer(C_Set_TimerExceed10min, &buf[0]);

/*判断长度是否合理*/
	if( pV_645Frame->DataLen != (CL_Auth_Rand1 + CLen_DI + CLen_OpCode ) )
	{
		Comm_Response_03_Err(C_SERR_OtherErr, pV_645Frame);
		return;
	}
	else
	{
		ValidDataLen = CL_Auth_Rand1;
	}

/*调用安全模块的接口函数*/
	pValidData = &(pV_645Frame->Data[CData_OtherO_V_645]);
	SError = InF_S_IRCertification_Request(pValidData, &ValidDataLen, CMaxRMNLen_OtherV_645);
	if( SError == C_OK )
	{
		Comm_11_03Response_Normal(pV_645Frame, pValidData, ValidDataLen);
	}
	else
	{
		Comm_Response_03_Err(SError, pV_645Frame);
		if(SError == C_SERR_ESAM_VF)
		{/*ESAM验证失败，200次++*/
			Comm_DealwithSPTVariable(C_SPTNumAdd);
		}
	}
	return;
}

/***************************************************************************
函数原型 	Comm_Authentication
函数功能	03-身份认证命令解析及对应处理
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	无
全局变量 	通道交互变量，身份认证时效
函数备注
***************************************************************************/
void	Comm_Authentication( Str_Comm_645 *pV_645Frame )
{
	uchar8	buf[C_TimerExceed10minLen];
	ushort16	SError;
	uchar8	ValidDataLen;
	uchar8	*pValidData;

	/*首先设置当前身份认证无效,结束上一次编程记录*/
	memset( buf, 0, C_TimerExceed10minLen );
	DealWith_ID_Auth_Timer(C_Set_TimerExceed10min, &buf[0]);
	INF_StopCommProgState();		/*到定时处理消息中处理*/

	/*判断长度是否合理*/
	if( pV_645Frame->DataLen != ( C_Authentication_Len + CLen_DI + CLen_OpCode ) )
	{
		Comm_Response_03_Err(C_SERR_OtherErr, pV_645Frame);
		return;
	}
	else
	{
		ValidDataLen = C_Authentication_Len;
	}

/*调用安全模块接口函数*/
	pValidData = &(pV_645Frame->Data[CData_OtherO_V_645]);
	SError = InF_S_Authentication(pValidData, &ValidDataLen);
	if( SError != C_OK )
	{
		Comm_Response_03_Err(SError, pV_645Frame);
		if( SError == C_SERR_ESAM_VF )
		{/*ESAM验证失败，200次++*/
			Comm_DealwithSPTVariable(C_SPTNumAdd);
		}
		return;
	}
/*置身份认证有效时间*/
	memset( buf, 0, C_TimerExceed10minLen );
	PF_CopyDataBytes(&pValidData[C_R_Auth_O_AuthPTime], buf, 2);
	DealWith_ID_Auth_Timer(C_Set_TimerExceed10min, buf);

	ValidDataLen = ValidDataLen - CLen_AuthPTime;
/*置正常应答帧*/
	Comm_11_03Response_Normal(pV_645Frame, pValidData, ValidDataLen);
	return;
}

/***************************************************************************
函数原型 	Is_ID_Auth_Ok_ResponseErr
函数功能	判断本命令是否有权限。包括该命令是否需要身份认证、
				编程开关、厂内状态权限判断，需要是否OK?Err，则组织应答帧
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	C_OK/C_Error
全局变量 	无
函数备注	本函数在各控制码解析函数中调用。调用后如果
				C_Error，则需要根据情况应答
				除安全命令外，其他命令在厂内模式下都是不需要身份认证的。
***************************************************************************/
uchar8 Is_ID_Auth_Ok_ResponseErr( Str_Comm_645 *pV_645Frame )
{
	Str_WrParmTable WrParmTable;

	/*03命令无厂内状态和编程开关的说法*/
	if(pV_645Frame->C ==0x03)
	{
		switch(pV_645Frame->DI)
		{	/*以下命令可不需要身份认证*/
			case		CDI_Auth:				/*身份认证*/
			{	/*判断如果是红外通道，但红外认证没有，不允许身份认证*/
				if( (pV_645Frame->ChannelNo == C_IR)
					&&(JudgeTimerExceed10min(&IR_AuthT_645) != C_TimerEnable) )
				{
					Comm_Response_03_Err(C_SERR_OtherErr, pV_645Frame);
					return(C_Error);
				}
				else
				{
					return(C_OK);
				}
			}break;
			case CDI_IRCReq_645:				/*红外认证请求*/
			case CDI_IR_ExtAuth_645:			/*红外认证*/
			{
				/*红外认证及红外认证请求，必须是红外通道。*/
				if(pV_645Frame->ChannelNo == C_IR)
				{
					return(C_OK);
				}
				else
				{
					Comm_Response_03_Err(C_SERR_OtherErr, pV_645Frame);
					return(C_Error);
				}
			}break;
			default:
			{
				if(JudgeTimerExceed10min(&ID_AuthT) == C_TimerEnable)
				{
					return(C_OK);
				}
				else
				{
					Comm_Response_03_Err(C_SERR_AF, pV_645Frame);
					return(C_Error);
				}
			}break;
		}
	}

	/*自扩命令，数据恢复操作，具体描述见寄存器汇总,没有特殊限制*/
	if(pV_645Frame->C ==0x1F)
	{
		return(C_OK);
	}

	/*其他判断是否为厂内模式，如果是可以不管身份认证*/
	if(JudgeTimerExceed10min(&SI_JTimer_BSOn2500)==C_TimerEnable)
	{
		return(C_OK);		/*退出去判断密码。如果在厂内模式采用98、99，由于*/
							/*没有判断是否处于身份认证有效，可能会导致200次挂起。*/
	}
	else
	{
		/*不在厂内模式，下面命令不允许设置*/
		if(pV_645Frame->C == 0x14)	/*645命令在厂外不允许设置2017/12/28 17:27:52*/
		{
			switch(pV_645Frame->DI)
			{
				case CRated_Vol645:				/*额定电压*/
				case CRated_Curr645:			/*额定电流*/
				case CMax_Curr645:				/*最大电流*/
				case CActive_Accur_Deg645:		/*有功准确度等级*/
				case CReactive_Accur_Deg645:	/*无功准确度等级*/
				case CMeter_Ac_Const645:		/*电表有功常数*/
				case CMeter_Re_Const645:		/*电表有无功常数*/
				case CMeter_Model645:			/*电表型号*/
				case CProd_Date645:				/*生产日期*/
				case CProt_Version_Num:			/*协议版本号*/
				case CFactory_Softw_Version:	/*厂家软件版本号*/
				case CFactory_Hardw_Version:	/*厂家硬件版本号*/
				case CFactory_Number:			/*厂家编号*/
				case CSoftw_Record_Number:		/*软件备案号*/
				case 0x43000500:				/*子设备列表*/
				case CMeter_CommPro:			/*支持规约列表*/
				{
					Comm_Response_Set_ReadErr(C_Unauthorized_645, pV_645Frame);
					return(C_Error);
				}break;
				default:
					break;						/*注意这里是break，到下一步判断*/
			}
		}

		if(pV_645Frame->C == 0x21)
		{
			return(C_Error);					/*校表命令不允许在厂外模式设置*/
		}
	}

	/*其他判断是否编程开关有效，有效也不管身份认证。因为新国网*/
	/*是没有编程开关，所以此动作是没有问题的。*/
	/*换句话，身份认证过了，有编程开关，也允许04级设置*/
	if(JudgeTimerExceed10min(&ProgKey_Timer) == C_TimerEnable)
	{
		return(C_OK);
	}

	/*身份认证有效期间，剩余所有命令都开放	2017/12/28 17:28:50    645命令不判断身份认证有效*/
	if(JudgeTimerExceed10min(&ID_AuthT) == C_TimerEnable)
	{
		return(C_OK);
	}

	/*到这里既不是厂内、也无编程开关和身份认证*/
	/*需要判断命令类型*/
	switch(pV_645Frame->C)
	{
		/*以下命令都不需要身份认证*/
		case 0x1E:			/*厂内自扩命令，应答OK，在解析函数中处理安全。*/
		case 0x11:			/*读*/
		case 0x12:			/*读后续帧*/
		case 0x18:			/*设置密码*/
		case 0x13:			/*读通信地址*/
		case 0x08:			/*广播校时*/
		case 0x17:			/*更改通信速率*/
		case 0x20:			/*校表命令读*/
		case 0x1C:			/*控制命令在命令解析中判断，因为应答2字节/1字节未定*/
		{
			return(C_OK);
		}break;
		/*写命令，个别不需要身份认证。*/
		case 0x14:			/*写*/
		{
			if(Is_ParmType_3(pV_645Frame->DI,&WrParmTable,pV_645Frame->ChannelNo) == C_OK)
			{
				return(C_OK);	/*III类数据，无线通讯在线级信号强弱指示;或自定义IP字段等标识码*/
			}
			else if( ( pV_645Frame->DI == C_EvenHar_AddData_A0 )
				   || ( pV_645Frame->DI == C_EvenHar_AddData_A1 )
				   || ( pV_645Frame->DI == C_EvenHar_AddData_B0 )
				   || ( pV_645Frame->DI == C_EvenHar_AddData_B1 )
				   || ( pV_645Frame->DI == C_EvenHar_AddData_C0 )
				   || ( pV_645Frame->DI == C_EvenHar_AddData_C1 )
				   || ( pV_645Frame->DI == C_EvenHar_Time ) )
			{
				return(C_OK);
			}
			else
			{
				Comm_Response_Set_ReadErr(C_Unauthorized_645, pV_645Frame);
				return(C_Error);
			}
		}break;
		default:
		{
			Comm_Response_Set_ReadErr(C_Unauthorized_645, pV_645Frame);
			return(C_Error);	/*其他命令，如电表清零等都需要身份认证*/
		}break;
	}
}

/***************************************************************************
函数原型 	Is_SPT_NotOver_ResponseErr
函数功能	判断命令是否需要判200次超出?如需要则判断，
				超出则进行命令应答
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	C_OK/C_Error
全局变量 	无
函数备注	201407，国网发布14规范，其中要求合闸(合闸允许)
				可以采用02/04密码，不用管编程开关。02/04密码采用密码闭锁功能
				1、程序中密码闭锁。密码闭锁在密码判断函数中执行
				2、1C控制命令，在该命令中判断200次挂起。
***************************************************************************/
uchar8	Is_SPT_NotOver_ResponseErr(Str_Comm_645	*pV_645Frame)
{
	Str_WrParmTable	WrParmTable;
/*03命令无厂内状态的说法*/
	if(pV_645Frame->C ==0x03)
	{
		switch(pV_645Frame->DI)
		{/*以下命令不需要判断电能表挂起状态*/
			case		CDI_Auth:			/*身份认证*/
			case		CDI_IRCReq:			/*红外认证请求*/
			case		CDI_IR_ExtAuth:		/*红外认证*/
				return(C_OK);
			default:
				if(Comm_DealwithSPTVariable(C_JudgeSPTVariable) == C_SPT_Num_Over)
				{
					Comm_Response_03_Err(C_SERR_Meter_Safeguard, pV_645Frame);
					return(C_Error);
				}
				else
				{
					return(C_OK);
				}
		}
	}
	/*自扩命令，数据恢复操作，具体描述见寄存器汇总,没有特殊限制*/
	if(pV_645Frame->C == 0x1F)
	{
		return(C_OK);
	}

/*其他判断是否为厂内模式，如果是可以不管200次，运用02等密级了*/
	if( JudgeTimerExceed10min(&SI_JTimer_BSOn2500) == C_TimerEnable )
	{
		return(C_OK);			/*退出去判断密码。如果在厂内模式采用98、99，由于*/
								/*没有判断是否处于200次挂起，会导致该功能无效200次挂起。*/
	}
/*其他判断是否编程开关有效，有效也不管200次。*/
	if(JudgeTimerExceed10min(&ProgKey_Timer) == C_TimerEnable)
	{/*编程开关有效，意味判断密码，此时到密码判断函数中判断密码闭锁。*/
	/*如果编程开关有效，又采用98.99级，又在200次挂起，此时由于这里*/
	/*直接返回OK，会有问题。但因为新国网是没有编程开关，所以没关系*/
		return(C_OK);
	}
/*200次没有到，除了特殊命令修改密码其他所有命令都开放*/
	if(Comm_DealwithSPTVariable(C_JudgeSPTVariable) != C_SPT_Num_Over)
	{
		return(C_OK);
	}

/*到了这里，200次到了，则需要判断命令类型是否需要判断200次挂起*/
	switch(pV_645Frame->C)
	{
	/*以下命令都不需要身份认证*/
		case		0x11:			/*读*/
		case		0x12:			/*读后续帧*/
		case		0x15:			/*写通讯地址*/
		case		0x18:			/*设置密码*/
		case		0x13:			/*读通信地址*/
		case		0x08:			/*广播校时*/
		case		0x1C:			/*负荷开关控制命令。负荷开关控制命令在该命令中判断*/
									/*200次挂起是否有效。此处直接退出。*/
		case		0x1E:			/*厂内不需要判断挂起*/
			return(C_OK);
	/*写命令，个别不需要身份认证。*/
		case		0x14:			/*写*/
		{
			if(Is_ParmType_3(pV_645Frame->DI, &WrParmTable, pV_645Frame->ChannelNo) == C_OK)
			{/*III类数据，无线通讯在线级信号强弱指示;或自定义标识码*/
				return(C_OK);
			}
			else
			{
				Comm_Response_Set_ReadErr(C_Unauthorized_645, pV_645Frame);
				return(C_Error);
			}
		}
		default:
			Comm_Response_Set_ReadErr(C_Unauthorized_645, pV_645Frame);
			return(C_Error);		/*其他命令，如电表清零等都需要判断200次挂起*/
	}

}
/***************************************************************************
函数原型 	If_AddressFlagErr_Response
函数功能	判断通信地址标志是否合适，不合适则应答错误
输入参数	pV_645Frame	->C					:645控制字
				pV_645Frame->AddressFlag			:通信地址标志
							C_MeterAddress/C_Broadcast/C_Condense_AA_All/C_Condense_AA
输出参数 	无
返回参数	C_OK/C_Error
全局变量 	通道交互变量
函数备注	如果判断标志不合适，组织好通信应答帧，置发送消息标志
***************************************************************************/
uchar8	If_AddressFlagOK_ResponseErr(Str_Comm_645 *pV_645Frame)
{
	Str_WrParmTable WrParmTable;
/*和广播地址相关的2条命令:广播校时或广播冻结及多功能输出*/
/*浙江广播校时要求点对点*/
	if(pV_645Frame->C == 0x08)
	{
		return(C_OK);
	}
	else if(pV_645Frame->C ==0x16)
	{
		if( ( pV_645Frame->AddressFlag == C_Broadcast ) || ( pV_645Frame->AddressFlag == C_MeterAddress ) )
		{/*冻结支持广播和全表号*/
			return(C_OK);
		}
		else
		{
			Comm_Response_Set_ReadErr(C_Unauthorized, pV_645Frame);
			return(C_Error);
		}
	}
	else if(pV_645Frame->C ==0x1D)			/*控制多功能输出*/
	{
		return(C_OK);						/*多功能输出只要表号正确就可以，对表号格式无要求*/
	}
	else if( ( pV_645Frame->C ==0x11 ) && ( pV_645Frame->DataLen == 0x09 )
		   && ( pV_645Frame->DI == CLCD_View ) )
	{
		return(C_OK);
	}
	else
	{
		if(pV_645Frame->AddressFlag == C_Broadcast)
		{/*其他命令不允许有广播地址*/
			return(C_Error);
		}
	}
/*根据控制字去判断地址是否合法。*/
	switch(pV_645Frame->C)
	{
	/*以下命令是支持除广播命令之外所有表地址格式*/
		case		0x11:			/*读命令*/
		case		0x12:			/*读后续帧*/
		case		0x1E:			/*厂内命令*/
		case		0x20:			/*读校表参数*/
		case		0x21:			/*写校表命令*/
			return(C_OK);
	/*以下命令必须全表号*/
		case		0x14:			/*写*/
		case		0x1A:			/*电表总清*/
		case		0x1B:			/*事件记录清零*/
		case		0x19:			/*需量清零*/
		case		0x17:			/*修改波特率*/
		case		0x18:			/*修改密码*/
		case		0x1C:			/*控制命令*/
		case		0x1F:			/*自扩命令，数据恢复操作，具体描述见寄存器汇总	*/
		{
			if(pV_645Frame->AddressFlag != C_MeterAddress)
			{/*20141023,因为无线模块设置可能采用全AA，所以三类参数允许全AA设置*/
				if( ( pV_645Frame->C == 0x14 )
					&& ( Is_ParmType_3(pV_645Frame->DI, &WrParmTable, pV_645Frame->ChannelNo ) == C_OK ) )
				{
					return(C_OK);
				}
				else
				{
					Comm_Response_Set_ReadErr(C_Unauthorized_645, pV_645Frame);
					return(C_Error);
				}
			}
			else
			{
				return(C_OK);
			}
		}
	/*以下命令必须全AA,其他不应答*/
		case		0x13:			/*读表通信地址*/
		case		0x15:			/*设表通信地址*/
			if( pV_645Frame->AddressFlag == C_Condense_AA_All )
			{
				return(C_OK);
			}
			else
			{						/*读设地址不用全AA也不应答*/
				return(C_Error);
			}
									/*03控制比较特殊，其中一些读命令支持缩位*/
		case		0x03:			/*安全命令中读命令支持缩位，其他命令只支持全表号*/
			switch(pV_645Frame->DI)
				{
					case		CDI_GetData:			/*数据回抄*/
					case		CDI_GetData01:
					case		CDI_GetStatus:			/*状态查询*/
					case		CDI_GetStatus01:
					case		CDI_CMPSoft:			/*软件比对*/
						return(C_OK);
					default:
					{
						if(pV_645Frame->AddressFlag != C_MeterAddress)
						{
							Comm_Response_03_Err(C_SERR_OtherErr, pV_645Frame);
							return(C_Error);
						}
						else
						{
							return(C_OK);
						}
					}
				}

		default:					/*控制码错，不应答，直接退出.*/
			return(C_Error);
	}
}
/***************************************************************************
函数原型 	Is_IR_Comm_ResponseErr
函数功能	判断红外通信是否允许,不允许则组织应答
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	C_OK/C_Error
全局变量 	无
函数备注	判断如果是红外通信口过来的通信，则需要红外认证，
				否则只允许仅支持读表号、通信地址、备案号、
				当前日期、当前时间、当前电能、当前剩余金额、
				红外认证查询命令，其它信息不允许读出，
				所有信息均不允许设置；
***************************************************************************/
uchar8		Is_IR_Comm_ResponseErr(Str_Comm_645	*pV_645Frame)
{
	if(pV_645Frame->ChannelNo != C_IR)
	{
		return(C_OK);							/*不是红外口进来，不管红外认证*/
	}
	if(JudgeTimerExceed10min(&IR_AuthT) == C_TimerEnable)
	{
		return(C_OK);							/*红外认证有效*/
	}

/*红外认证无效，判断是否是允许通信的内容*/
	/*增加几个特殊命令*/
	if(pV_645Frame->C == 0x11)					/*11读取命令*/
	{
		if( ( ( ( pV_645Frame->DI&0xFF000000 ) == 0 ) && ( ( pV_645Frame->DI & 0x000000FF ) == 0 ) )
		 || ( pV_645Frame->DI == COverDraft_Hex_Cent ) )
		{/*当前电能类包括剩余金额、透支金额*/
			return(C_OK);
		}
		switch(pV_645Frame->DI)
		{
			case		CMeter_Num:				/*表号*/
			case		CComm_Address:			/*通信地址*/
			case		CSoftw_Record_Number:	/*备案号*/
			case		CDate_Week:				/*日期及星期*/
			case		CTime:					/*时间*/
			case		CDate_Time:				/*日期星期-时间*/
				return(C_OK);
			default:
				Comm_Response_Set_ReadErr(C_Unauthorized, pV_645Frame);
				return(C_Error);				/*其他命令不支持读*/
		}
	}
	else if(pV_645Frame->C == 0x03)				/*安全命令*/
	{
		switch(pV_645Frame->DI)
		{
			case		CDI_IRCReq:				/*红外认证请求命令*/
			case		CDI_IR_ExtAuth:			/*红外认证命令*/
				return(C_OK);
			default:
				Comm_Response_03_Err(C_SERR_OtherErr, pV_645Frame);
				return(C_Error);				/*其他命令不支持读*/
		}
	}
	else if(pV_645Frame->C == 0x13)				/*广播读通信地址也是被允许的*/
	{
		return(C_OK);
	}
	else if( ( pV_645Frame->C == 0x1C ) && ( pV_645Frame->PowerFlag == C_PowerOn ) )
	{/*02、04合闸命令不考虑红外认证*/
		return(C_OK);							/*红外认证退出到控制命令解析中判断，因为应答2字节1字节未定*/
	}
	else if( ( pV_645Frame->C == 0x1F ) && ( pV_645Frame->PowerFlag == C_PowerOn ) )
	{/*自扩命令，数据恢复操作，具体描述见寄存器汇总	*/
		return(C_OK);
	}
	else
	{
		if(pV_645Frame->PowerFlag == C_PowerOn)
		{/*有电，无红外认证，不支持命令应答其他情况不应答*/
			Comm_Response_Set_ReadErr(C_Unauthorized, pV_645Frame);
		}
		return(C_Error);
	}
}

/***************************************************************************
函数原型 	Is_IR_Comm_ResponseErr_645
函数功能	判断红外通信是否允许,不允许则组织应答
输入参数	*pV_645Frame				:接收到的数据帧
输出参数 	无
返回参数	C_OK/C_Error
全局变量 	无
函数备注	判断如果是红外通信口过来的通信，则需要红外认证，
				否则只允许仅支持读表号、通信地址、备案号、
				当前日期、当前时间、当前电能、当前剩余金额、
				红外认证查询命令，其它信息不允许读出，
				所有信息均不允许设置；
***************************************************************************/
uchar8		Is_IR_Comm_ResponseErr_645(Str_Comm_645	*pV_645Frame)
{
	if(pV_645Frame->ChannelNo != C_IR)
	{
		return(C_OK);								/*不是红外口进来，不管红外认证*/
	}
	if(JudgeTimerExceed10min(&IR_AuthT_645) == C_TimerEnable)
	{
		return(C_OK);								/*红外认证有效*/
	}

/*红外认证无效，判断是否是允许通信的内容*/
	/*增加几个特殊命令*/
	if(pV_645Frame->C == 0x11)						/*11读取命令*/
	{
		if( ( ( ( pV_645Frame->DI&0xFF000000 ) == 0 ) && ( ( pV_645Frame->DI & 0x000000FF ) == 0 ) )
		 || ( pV_645Frame->DI == COverDraft_Hex_Cent ) )
		{/*当前电能类包括剩余金额、透支金额*/
			return(C_OK);
		}
		switch(pV_645Frame->DI)
		{
			case		CMeter_Num_645:				/*表号*/
			case		CComm_Address_645:			/*通信地址*/
			case		CSoftw_Record_Number_645:	/*备案号*/
			case		CDate_Week:					/*日期及星期*/
			case		CTime:						/*时间*/
			case		CDate_Week_Time_645:		/*日期星期-时间*/
				return(C_OK);
			default:
				Comm_Response_Set_ReadErr(C_Unauthorized_645, pV_645Frame);
				return(C_Error);					/*其他命令不支持读*/
		}
	}
	else if(pV_645Frame->C == 0x03)					/*安全命令*/
	{
		switch(pV_645Frame->DI)
		{
			case		CDI_IRCReq_645:				/*红外认证请求命令*/
			case		CDI_IR_ExtAuth_645:			/*红外认证命令*/
				return(C_OK);
			default:
				Comm_Response_03_Err(C_SERR_OtherErr, pV_645Frame);
				return(C_Error);					/*其他命令不支持读*/
		}
	}
	else if(pV_645Frame->C == 0x13)					/*广播读通信地址也是被允许的。*/
	{
		return(C_OK);
	}
	else if( ( pV_645Frame->C == 0x1C ) && ( pV_645Frame->PowerFlag == C_PowerOn ) )
	{/*02、04合闸命令不考虑红外认证*/
		return(C_OK);								/*红外认证退出到控制命令解析中判断，因为应答2字节1字节未定*/
	}
	else if( ( pV_645Frame->C == 0x1F ) && ( pV_645Frame->PowerFlag == C_PowerOn ) )
	{/*自扩命令，数据恢复操作，具体描述见寄存器汇总	*/
		return(C_OK);
	}
	else
	{
		if(pV_645Frame->PowerFlag == C_PowerOn)
		{/*有电，无红外认证，不支持命令应答其他情况不应答*/
			Comm_Response_Set_ReadErr(C_Unauthorized_645, pV_645Frame);
		}
		return(C_Error);
	}
}

/***************************************************************************
函数原型 	CommMSg_StartTxd
函数功能	计算CS，置16，清对应定时器，启动发送
输入参数	CommNo				:通道号
输出参数 	无
返回参数	无
全局变量 	通道交互变量
函数备注	在调用这个函数之前，通道变量中已确保
				除CS、16之外所有数据都已置好
***************************************************************************/
void		CommMSg_StartTxd(uchar8 	CommNo)
{
	uchar8	CS;
	uchar8	i;
	Str_Comm_Parm 	*pStr_Comm_Parm_Address;

	pStr_Comm_Parm_Address = Get_Str_Comm_Parm_Pointer(CommNo);
	if(pStr_Comm_Parm_Address == C_NULL)
	{
		return;		/*通道错，这实际不可能。发生了，也不发送，直接退出。*/
	}

	CommOffset = 0;
	CommRecFlag645 = 0;
	CommOTimer = 0;

	if( ( CommLen645 < ( C_Comm_FixedTxLen - 2 ) ) || ( CommLen645 > ( C_Comm_Buf_MaxLen - 2 ) ) )
	{	/*实际上是不可能的。*/
		InF_InitComm(CommNo);
		Comm_ParseInit();
		return;
	}

/*数据域+0x33处理*/
	for( i = 0; i < CommBuff[C_L_OFS_ForTx]; i++ )
	{
		CommBuff[C_Data_OFS_ForTx + i] = CommBuff[C_Data_OFS_ForTx + i] + 0x33;
	}

/*计算CS，置CS、16并启动发送*/
	CS = 0;
	for( i = 0; i < ( CommLen645 - 4 ); i++ )		/*CommLen包含了4个FE的长度，应该扣除*/
	{
		CS = CS + CommBuff[C_68_1_OFS_ForTx + i];
	}
	CommBuff[C_68_1_OFS_ForTx + i] = CS;
	CommLen645++;
	i++;
	CommBuff[C_68_1_OFS_ForTx + i] = 0x16;
	CommLen645++;
/*启动发送*/
 	if((Inf_Comm_REPORTFlag() != C_ReportNULL))
 	{
		return;
 	}
	InF_CommUart_TxdDataForDispatch(CommNo, CommBuff[CommOffset], C_NoActiveReportFlag);
	CommOffset++;
}

/***************************************************************************
函数原型 	Comm_500ms_Execute
函数功能	完成通信定时消息的处理
输入参数	PowerFlag			:调度输入的电源标志
								C_PowerOn表示有电状态，
								C_PowerFalling表示发生掉电的沿变过程，
								C_PowerOff表示处于掉电状态，C_PowerRising表示发生来电的沿变过程
输出参数 	无
返回参数	无
全局变量 	SV_Comm_Parse/SV_Com_Parse_Local/
				通道相关Str_Comm_Parm/Str_Comm_NxtFrame
函数备注
***************************************************************************/
void	Comm_500ms_Execute(uchar8		PowerFlag)
{
	uchar8	buf[C_TimerExceed10minLen];
	Str_Comm_Parm 	*pStr_Comm_Parm_Address;

	if (PowerFlag == C_PowerOn )
	{
		/*首先处理最大定时超过10min定时器*/
		DealWith_IR_Auth_Timer(C_Dec_TimerExceed10min, buf);
		DealWith_ID_Auth_T_Timer(C_Dec_TimerExceed10min, buf);
		DealWith_IR_Auth_Timer_645(C_Dec_TimerExceed10min, buf);
		if( Com_Conect.ConectOverTime == 0 )
		{
			DealWith_ID_Auth_Timer(C_Dec_TimerExceed10min, buf);
		}

		/*软IJ定时器处理*/
		SI_JBaseTimer_2500++;
		if( SI_JBaseTimer_2500 >= C_SI_JBTimer_2500 )
		{
			SI_JBaseTimer_2500 = 0;
			DealWith_SI_J_Timer(C_Dec_TimerExceed10min, buf);
		}
		/*是否进行编程事件记录的判断*/
		if( ( JudgeTimerExceed10min(&ID_AuthT) == C_TimerDisable )
		 && ( InF_ConectTimer_DealNoTimer() == C_TimerDisable ) )
		{
		/*2个定时器都无效，进行编程总记录写。在写函数中会判断是否*/
		/*实际有数据写。没有是不会写的，因此这里没有问题*/
			INF_StopCommProgState();
		}
		/*处理通用定时器*/
		SV_Comm_Parse.Timer_1min++;
		if( SV_Comm_Parse.Timer_1min >= C_Timer_1min )
		{/*1min到*/
			SV_Comm_Parse.Timer_1min = 0;				/*重新定时*/
			InF_UpdateAccountStateInMeterStatus3();
		}

		/*通道的定时器处理*/
		/*RS485_1通道*/
		pStr_Comm_Parm_Address = &SV_RS485_1_Comm_Parm;
		CommOTimer++;
		if( CommOTimer >= C_Comm_OTime )
		{
			CommOTimer = 0;
		}
		/*RS485_2通道*/
		pStr_Comm_Parm_Address = &SV_RS485_2_Comm_Parm;
		CommOTimer++;
		if( CommOTimer >= C_Comm_OTime )
		{
			CommOTimer = 0;
		}
		/*红外通道*/
		pStr_Comm_Parm_Address = &SV_IR_Comm_Parm;
		CommOTimer++;
		if( CommOTimer >= C_Comm_OTime )
		{
			CommOTimer = 0;
		}
		/*模块通道*/
		pStr_Comm_Parm_Address = &SV_Module_Parm;
		CommOTimer++;
		if( CommOTimer >= C_Comm_OTime )
		{
			CommOTimer = 0;
            Inf_Comm_ClearModuleCommuniFlag(0);
		}
		if( SV_ModuleResetTimer24h != 0 )
        {
          	SV_ModuleResetTimer24h--;
        }
		/*模块电源*/
		DealWith_RstModule(C_Flag_Err);				/*不是有电情况下，调用模块复位处理*/

		/*已主动上报延时:*/
		if( SV_HaveReportState.Timer != 0 )
		{
			SV_HaveReportState.Timer--;
			if( SV_HaveReportState.Timer == 0 )
			{
                SF_RstHaveReportState_645To698(&SV_HaveReportState.State[0]);	/*清698主动上报，698兼容645增加*/
				Rst_SV_ReportNewAddNum(&SV_HaveReportState.State[0]);
			}
			SV_HaveReportState.CRC16 = PF_Cal_CRC(SV_HaveReportState.State, C_ReportStateByteNum + 2);
		}
		else
		{
			Init_SV_HaveReportState();
		}
		DealWithEventReportIO();


		if( ID_AuthT_Timer == 0 )
		{
			InF_ConectTimer_Deal();					/*应用连接时间*/
		}
	}
	InF_Check_Comm_Address();						/*定时500mscheck通信地址RAM中的数据，不对从EE读取*/
	InF_Get_Comm_Address(SV_Comm_Address, 0x00);	/*获取通信地址到通信自定义缓存*/

	/*645协议，模块80s不写信号强度，信号强度不再显示.
	698协议，威思顿4G模块每15分钟写一次信号强度*/
	SF_Comm_GPRSDisplay();


/*以下动作，不管有电没有电，都要搞一下*/
	Comm_DealwithSPTVariable(C_JudgeSPTVariable);	/*判断有没有过零点。*/
	Comm_ParseInit();
}
/***************************************************************************
函数原型 	InF_LowPower_IR_Inti
函数功能	完成低功耗下通信中红外认证和身份认证相关标志\定时器等的清零
输入参数	无
输出参数 	无
返回参数	无
全局变量 	红外认证有效定时器清零\电表运行状态中3中的红外认证有效标志返写0
			数据层中身份认证有效时间\电表允许状态字3中身份认证有效标志清零
函数备注	调度检测到掉电,进入低功耗前调用该函数
***************************************************************************/
void InF_LowPower_IR_Inti(void)
{
	uchar8 V_Buf2[C_TimerExceed10minLen];

	memset(V_Buf2, 0, C_TimerExceed10minLen);
	DealWith_IR_Auth_Timer(C_Set_TimerExceed10min, V_Buf2);			/*红外认证无效*/
	DealWith_ID_Auth_Timer(C_Set_TimerExceed10min, V_Buf2);			/*身份认证无效*/
	DealWith_ID_Auth_T_Timer(C_Set_TimerExceed10min, V_Buf2);		/*终端身份认证无效*/
	DealWith_IR_Auth_Timer_645(C_Set_TimerExceed10min, V_Buf2);		/*红外认证无效*/
}
/*********************************************************************************
函数原型	SF_Comm_GPRSDisplay
函数功能	完成GPRS信号强度定时80s没有设置过则不现实的功能
输入参数	无
输出参数 	无
返回参数	无
全局变量 	698协议，GPRS信号强度设置间隔定时器
函数备注	500ms调用
			由于威思顿4G模块每15分钟写一次信号强度，且模块24小时无通信会复位模块。
			因此698协议此函数不再使用。
*********************************************************************************/
void SF_Comm_GPRSDisplay(void)
{
	uchar8	V_ucBuffer[2];

	if(GPRS_DisplayTimer != 0)
	{
		GPRS_DisplayTimer--;
		if(GPRS_DisplayTimer == 0)
		{
			V_ucBuffer[0] = 0;
			V_ucBuffer[1] = 0;
			SetGPRSSignal(&V_ucBuffer[0]);	/*不显示GPRS信号强度*/
		}
	}
}

/***************************************************************************
函数原型 	Clear_BDSC_RecentClock
函数功能	清零广播校时时间
输入参数	无
输出参数 	无
返回参数	无
全局变量 	SV_Comm_Parse.BDSC_RecentClock
函数备注	修改日期\电表清零调用
***************************************************************************/
void Clear_BDSC_RecentClock(void)
{
	memset(&SV_Comm_Parse.BDSC_RecentClock[0], 0, 7);
}

/***************************************************************************
函数原型 	InF_JudgeJTTimer
函数功能	判断当前软IJ是否有效
输入参数	无
输出参数 	无
返回参数	C_OK有效,C_Error无效
全局变量
函数备注	本函数专门用于厂内状态下，未校表时检测插卡功能
***************************************************************************/
uchar8	InF_JudgeIJTimer( void )
{
	if( (JudgeTimerExceed10min(&SI_JTimer_BSOn2500) == C_TimerEnable) )
	{
		return C_OK;
	}
	else
	{
		return C_Error;
	}
}

const	Str_TBCarryingSubDI_1		TBCarryingSubDI_1[CLen_TBCarryingSubDI_1] =
{
	{CCurrent_RateFF_Price	,	(ulong32 *)&TB_Current_RateFF_Price	,	CLen_TB_RateFF_Price	},
	{CBackUp_RateFF_Price	,	(ulong32 *)&TB_BackUp_RateFF_Price	,	CLen_TB_RateFF_Price	},
	{CMeter_Work_StateFF	,	(ulong32 *)&TB_MeterStatus			,	CLen_TB_MeterStatus		},
	{CDe_Over_Degree		,	(ulong32 *)TB_De_Over_Degree		,	CLen_TB_De_Over_Degree	}
};
const	ulong32	TB_Current_RateFF_Price[CLen_TB_RateFF_Price] =
{
	CCurrent_Rate1_Price,
	CCurrent_Rate2_Price,
	CCurrent_Rate3_Price,
	CCurrent_Rate4_Price,
	CCurrent_Rate5_Price,
	CCurrent_Rate6_Price,
	CCurrent_Rate7_Price,
	CCurrent_Rate8_Price,
	CCurrent_Rate9_Price,
	CCurrent_Rate10_Price,
	CCurrent_Rate11_Price,
	CCurrent_Rate12_Price
};
const	ulong32	TB_BackUp_RateFF_Price[CLen_TB_RateFF_Price] =
{	CBackUp_Rate1_Price,
	CBackUp_Rate2_Price,
	CBackUp_Rate3_Price,
	CBackUp_Rate4_Price,
	CBackUp_Rate5_Price,
	CBackUp_Rate6_Price,
	CBackUp_Rate7_Price,
	CBackUp_Rate8_Price,
	CBackUp_Rate9_Price,
	CBackUp_Rate10_Price,
	CBackUp_Rate11_Price,
	CBackUp_Rate12_Price
};
const	ulong32	TB_CalMReg_SubDI[C_CalMReg_SubDILen] =
{
	CRec_Meter_Hp_T_1,		    /*上1次校表时间*/
	CRec_Meter_Bef1_Data_1,	    /*上1次1号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_2,	    /*上1次2号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_3,	    /*上1次3号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_4,	    /*上1次4号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_5,	    /*上1次5号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_6,	    /*上1次6号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_7,	    /*上1次7号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_8,	    /*上1次8号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_9,	    /*上1次9号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_10, 	/*上1次10号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_11, 	/*上1次11号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_12, 	/*上1次12号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_13, 	/*上1次13号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_14, 	/*上1次14号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_15, 	/*上1次15号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_16, 	/*上1次16号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_17, 	/*上1次17号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_18, 	/*上1次18号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_19, 	/*上1次19号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_20, 	/*上1次20号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_21, 	/*上1次21号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_22, 	/*上1次22号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_23, 	/*上1次23号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_24, 	/*上1次24号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_25, 	/*上1次25号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_26, 	/*上1次26号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_27, 	/*上1次27号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_28, 	/*上1次28号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_29, 	/*上1次29号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_30, 	/*上1次30号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_31, 	/*上1次31号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_32, 	/*上1次32号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_33, 	/*上1次33号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_34, 	/*上1次34号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_35, 	/*上1次35号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_36, 	/*上1次36号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_37, 	/*上1次37号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_38, 	/*上1次38号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_39, 	/*上1次39号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_40, 	/*上1次40号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_41, 	/*上1次41号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_42, 	/*上1次42号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_43, 	/*上1次43号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_44, 	/*上1次44号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_45, 	/*上1次45号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_46, 	/*上1次46号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_47, 	/*上1次47号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_48, 	/*上1次48号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_49, 	/*上1次49号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_50, 	/*上1次50号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_51, 	/*上1次51号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_52, 	/*上1次52号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_53, 	/*上1次53号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_54, 	/*上1次54号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_55, 	/*上1次55号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_56, 	/*上1次56号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_57, 	/*上1次57号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_58, 	/*上1次58号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_59, 	/*上1次59号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_60, 	/*上1次60号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_61, 	/*上1次61号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_62, 	/*上1次62号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_63, 	/*上1次63号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_64, 	/*上1次64号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_65, 	/*上1次65号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_66, 	/*上1次66号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_67, 	/*上1次67号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_68, 	/*上1次68号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_69, 	/*上1次69号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_70, 	/*上1次70号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_71, 	/*上1次71号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_72, 	/*上1次72号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_73, 	/*上1次73号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_74, 	/*上1次74号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_75, 	/*上1次75号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_76, 	/*上1次76号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_77, 	/*上1次77号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_78, 	/*上1次78号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_79, 	/*上1次79号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_80, 	/*上1次80号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_81, 	/*上1次81号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_82, 	/*上1次82号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_83, 	/*上1次83号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_84, 	/*上1次84号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_85, 	/*上1次85号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_86, 	/*上1次86号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_87, 	/*上1次87号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_88, 	/*上1次88号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_89, 	/*上1次89号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_90, 	/*上1次90号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_91, 	/*上1次91号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_92, 	/*上1次92号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_93, 	/*上1次93号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_94, 	/*上1次94号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_95, 	/*上1次95号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_96, 	/*上1次96号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_97, 	/*上1次97号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_98, 	/*上1次98号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_99, 	/*上1次99号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_100,   /*上1次100号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_101,   /*上1次101号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_102,   /*上1次102号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_103,   /*上1次103号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_104,   /*上1次104号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_105,   /*上1次105号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_106,   /*上1次106号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_107,   /*上1次107号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_108,   /*上1次108号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_109,   /*上1次109号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_110,   /*上1次110号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_111,   /*上1次111号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_112,   /*上1次112号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_113,   /*上1次113号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_114,   /*上1次114号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_115,   /*上1次115号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_116,   /*上1次116号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_117,   /*上1次117号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_118,   /*上1次118号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_119,   /*上1次119号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_120,   /*上1次120号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_121,   /*上1次121号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_122,   /*上1次122号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_123,   /*上1次123号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_124,   /*上1次124号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_125,   /*上1次125号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_126,   /*上1次126号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_127,   /*上1次127号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_128,   /*上1次128号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_129,   /*上1次129号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_130,   /*上1次130号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_131,   /*上1次131号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_132,   /*上1次132号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_133,   /*上1次133号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_134,   /*上1次134号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_135,   /*上1次135号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_136,   /*上1次136号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_137,   /*上1次137号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_138,   /*上1次138号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_139,   /*上1次139号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_140,   /*上1次140号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_141,   /*上1次141号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_142,   /*上1次142号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_143,   /*上1次143号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_144,   /*上1次144号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_145,   /*上1次145号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_146,   /*上1次146号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_147,   /*上1次147号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_148,   /*上1次148号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_149,   /*上1次149号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_150,   /*上1次150号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_151,   /*上1次151号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_152,   /*上1次152号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_153,   /*上1次153号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_154,   /*上1次154号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_155,   /*上1次155号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_156,   /*上1次156号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_157,   /*上1次157号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_158,   /*上1次158号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_159,   /*上1次159号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_160,   /*上1次160号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_161,   /*上1次161号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_162,   /*上1次162号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_163,   /*上1次163号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_164,   /*上1次164号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_165,   /*上1次165号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_166,   /*上1次166号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_167,   /*上1次167号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_168,   /*上1次168号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_169,   /*上1次169号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_170,   /*上1次170号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_171,   /*上1次171号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_172,   /*上1次172号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_173,   /*上1次173号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_174,   /*上1次174号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_175,   /*上1次175号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_176,   /*上1次176号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_177,   /*上1次177号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_178,   /*上1次178号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_179,   /*上1次179号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_180,   /*上1次180号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_181,   /*上1次181号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_182,   /*上1次182号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_183,   /*上1次183号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_184,   /*上1次184号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_185,   /*上1次185号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_186,   /*上1次186号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_187,   /*上1次187号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_188,   /*上1次188号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_189,   /*上1次189号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_190,   /*上1次190号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_191,   /*上1次191号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_192,   /*上1次192号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_193,   /*上1次193号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_194,   /*上1次194号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_195,   /*上1次195号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_196,   /*上1次196号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_197,   /*上1次197号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_198,   /*上1次198号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_199,   /*上1次199号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_200,   /*上1次200号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_201,   /*上1次201号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_202,   /*上1次202号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_203,   /*上1次203号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_204,   /*上1次204号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_205,   /*上1次205号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_206,   /*上1次206号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_207,   /*上1次207号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_208,   /*上1次208号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_209,   /*上1次209号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_210,   /*上1次210号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_211,   /*上1次211号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_212,   /*上1次212号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_213,   /*上1次213号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_214,   /*上1次214号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_215,   /*上1次215号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_216,   /*上1次216号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_217,   /*上1次217号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_218,   /*上1次218号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_219,   /*上1次219号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_220,   /*上1次220号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_221,   /*上1次221号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_222,   /*上1次222号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_223,   /*上1次223号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_224,   /*上1次224号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_225,   /*上1次225号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_226,   /*上1次226号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_227,   /*上1次227号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_228,   /*上1次228号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_229,   /*上1次229号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_230,   /*上1次230号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_231,   /*上1次231号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_232,   /*上1次232号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_233,   /*上1次233号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_234,   /*上1次234号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_235,   /*上1次235号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_236,   /*上1次236号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_237,   /*上1次237号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_238,   /*上1次238号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_239,   /*上1次239号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_240,   /*上1次240号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_241,   /*上1次241号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_242,   /*上1次242号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_243,   /*上1次243号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_244,   /*上1次244号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_245,   /*上1次245号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_246,   /*上1次246号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_247,   /*上1次247号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_248,   /*上1次248号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_249,   /*上1次249号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_250,   /*上1次250号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_251,   /*上1次251号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_252,   /*上1次252号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_253,   /*上1次253号校表参数校表前数据*/
	CRec_Meter_Bef1_Data_254	/*上1次254号校表参数校表前数据*/
};
const	ulong32	TB_LossA_Curr_SubDI[C_LossA_Curr_SubDILen] =
{
    CLossA_Curr_FF_1,
    CLossA_Curr_FF_2,
    CLossA_Curr_FF_3,
    CLossA_Curr_FF_4,
    CLossA_Curr_FF_5,
    CLossA_Curr_FF_6,
    CLossA_Curr_FF_7,
    CLossA_Curr_FF_8,
    CLossA_Curr_FF_9,
    CLossA_Curr_FF_10,
};
const	ulong32	TB_LossB_Curr_SubDI[C_LossB_Curr_SubDILen] =
{
    CLossB_Curr_FF_1,
    CLossB_Curr_FF_2,
    CLossB_Curr_FF_3,
    CLossB_Curr_FF_4,
    CLossB_Curr_FF_5,
    CLossB_Curr_FF_6,
    CLossB_Curr_FF_7,
    CLossB_Curr_FF_8,
    CLossB_Curr_FF_9,
    CLossB_Curr_FF_10,
};
const	ulong32	TB_LossC_Curr_SubDI[C_LossC_Curr_SubDILen] =
{
    CLossC_Curr_FF_1,
    CLossC_Curr_FF_2,
    CLossC_Curr_FF_3,
    CLossC_Curr_FF_4,
    CLossC_Curr_FF_5,
    CLossC_Curr_FF_6,
    CLossC_Curr_FF_7,
    CLossC_Curr_FF_8,
    CLossC_Curr_FF_9,
    CLossC_Curr_FF_10,
};
const	ulong32	TB_OverA_Curr_SubDI[C_OverA_Curr_SubDILen] =
{
    COverA_Curr_FF_1,
    COverA_Curr_FF_2,
    COverA_Curr_FF_3,
    COverA_Curr_FF_4,
    COverA_Curr_FF_5,
    COverA_Curr_FF_6,
    COverA_Curr_FF_7,
    COverA_Curr_FF_8,
    COverA_Curr_FF_9,
    COverA_Curr_FF_10,
};
const	ulong32	TB_OverB_Curr_SubDI[C_OverB_Curr_SubDILen] =
{
    COverB_Curr_FF_1,
    COverB_Curr_FF_2,
    COverB_Curr_FF_3,
    COverB_Curr_FF_4,
    COverB_Curr_FF_5,
    COverB_Curr_FF_6,
    COverB_Curr_FF_7,
    COverB_Curr_FF_8,
    COverB_Curr_FF_9,
    COverB_Curr_FF_10,
};
const	ulong32	TB_OverC_Curr_SubDI[C_OverC_Curr_SubDILen] =
{
    COverC_Curr_FF_1,
    COverC_Curr_FF_2,
    COverC_Curr_FF_3,
    COverC_Curr_FF_4,
    COverC_Curr_FF_5,
    COverC_Curr_FF_6,
    COverC_Curr_FF_7,
    COverC_Curr_FF_8,
    COverC_Curr_FF_9,
    COverC_Curr_FF_10,
};

const	ulong32	TB_DCLREvent_SubDI[C_DCLREvent_SubDILen] =
{
	CDe_Clear_NoteE_1,
	CDe_Clear_NoteF_1
};
const	ulong32	TB_De_Over_Degree[CLen_TB_De_Over_Degree] =
{
	CPos_Ac_De_Over_Degree,
	CRev_Ac_De_Over_Degree,
	CQua1_Re_De_Over_Degree,
	CQua2_Re_De_Over_Degree,
	CQua3_Re_De_Over_Degree,
	CQua4_Re_De_Over_Degree
};
const	ulong32 	TB_FreezeSubDI[C_FreezeSubDILen] =
{
	CT_Free_Time_1, 					/*上1次定时冻结时间*/
	CT_Free_Pos_Ac_En_1,				/*上1次定时冻结正向有功电能数据*/
	CT_Free_Rev_Ac_En_1,				/*上1次定时冻结反向有功电能数据*/
	CT_Free_Com_Re1_En_1,				/*上1次定时冻结组合无功1数据*/
	CT_Free_Com_Re2_En_1,
	CT_Free_Qua1_Re_En_1,				/*上1次定时冻结四象限电能数据*/
	CT_Free_Qua2_Re_En_1,
	CT_Free_Qua3_Re_En_1,
	CT_Free_Qua4_Re_En_1,
	CT_Free_Pos_Ac_De_1,				/*上1次定时冻结正向需量数据*/
	CT_Free_Rev_Ac_De_1,
	CT_Free_Variable_1					/*上1次定时冻结变量数据*/
};

const	ulong32 	TB_HFreezeSubDI[C_HFreezeSubDILen] =
{
	CT_Free_Time_1, 					/*上1次定时冻结时间*/
	CT_Free_Pos_Ac_En_1,				/*上1次定时冻结正向有功电能数据*/
	CT_Free_Rev_Ac_En_1					/*上1次定时冻结反向有功电能数据*/
};


const	ulong32	TB_MeterStatus[CLen_TB_MeterStatus] =
{CMeter_Work_State1,CMeter_Work_State2,CMeter_Work_State3,CMeter_Work_State4,
CMeter_Work_State5,CMeter_Work_State6,CMeter_Work_State7,CKey_State};
const	Str_TBNxtFrame	TB_NxtFrame[C_TBNxtFrameNum]=
{
{CH_Free_FF_1				,(ulong32*)TB_HFreezeSubDI		,C_HFreezeSubDILen			,	C_Freeze_Method 	},	/*整点冻结*/
{CD_Free_FF_1				,(ulong32*)TB_FreezeSubDI		,C_FreezeSubDILen			,	C_Freeze_Method 	},	/*日冻结*/
{CDe_Clear_Note_1_645		,(ulong32*)TB_DCLREvent_SubDI	,C_DCLREvent_SubDILen		,	C_Prog_SubDI_LBit4	},	/*需清,698兼容645修改为645标识*/
{CProgPT_CurrentPart_Note_1	,(ulong32*)TB_ProgPT_SubDI		,C_ProgPT_SubDILen			,	C_Prog_SubDI_LBit4	},	/*时段表*/
{CRec_Meter_FF_Data_1		,(ulong32*)TB_CalMReg_SubDI		,(C_MeterICDataNum_T + 1)	,	C_Prog_SubDI_LBit4	},	/*校表集合读*/
{CLossA_Curr_FF_FF			,(ulong32*)TB_LossA_Curr_SubDI	,C_LossA_Curr_SubDILen		,	C_Event_Method		},	/*A相失流*/
{CLossB_Curr_FF_FF			,(ulong32*)TB_LossB_Curr_SubDI	,C_LossB_Curr_SubDILen		,	C_Event_Method		},	/*B相失流*/
{CLossC_Curr_FF_FF			,(ulong32*)TB_LossC_Curr_SubDI	,C_LossC_Curr_SubDILen		,	C_Event_Method		},	/*C相失流*/
{COverA_Curr_FF_FF			,(ulong32*)TB_OverA_Curr_SubDI	,C_OverA_Curr_SubDILen		,	C_Event_Method		},	/*A相过流*/
{COverB_Curr_FF_FF			,(ulong32*)TB_OverB_Curr_SubDI	,C_OverB_Curr_SubDILen		,	C_Event_Method		},	/*B相过流*/
{COverC_Curr_FF_FF			,(ulong32*)TB_OverC_Curr_SubDI	,C_OverC_Curr_SubDILen		,	C_Event_Method		},	/*C相过流*/
};
const	ulong32	TB_ProgHol_SubDI[C_ProgHol_SubDILen] =
{
	CProgHol_Note9_1,
	CProgHol_NoteA_1,
	CProgHol_NoteB_1,
	CProgHol_NoteC_1,
	CProgHol_NoteD_1,
	CProgHol_NoteE_1
};
const	ulong32	TB_ProgPT_SubDI[C_ProgPT_SubDILen] =
{
	CProgPT_NoteC_1,
	CProgPT_NoteD_1,
	CProgPT_NoteE_1,
	CProgPT_NoteF_1
};



