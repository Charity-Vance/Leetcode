
/****************************************************************************************
Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     communication.c
Author		jiangzs
Version:       V1
Date:          2014-3-12
Description:   ͨ�Ŵ��������ļ�
Function List:
---------------------------------------------------------------------------------
History1:      ��1���޸�
����1. Date:
   	   Author:
       Modification:
---------------------------------------------------------------------------------
����2. Date:
   	   Author:
       Modification:
	---------------------------------------------------------------------------------
History2:      ��2���޸�
����1. Date:
   	   Author:
       Modification:
---------------------------------------------------------------------------------
����2. Date:
   	   Author:
       Modification:
****************************************************************************************/

#include "Communication.h"
#include "RTCDrive.h"
#include "ADC.h"

/*2020��׼�����ϱ�2005*/
uchar8  SV_REPORTCommBuff[C_ModuleMaxLen];
uchar8  SV_PowerfailReportONum[3];
uchar8  SV_ReportShutTime;
Str_Report_Parm SV_ReportSend;
Str_Comm_Parse_Local SV_Comm_Parse_Local;
Str_Comm_Parse		SV_Comm_Parse;
uchar8	SV_SetBPS_Flag;							/*C_OK����BPS��C_Error����ͨ������*/
uchar8  SV_Comm_Address[CLComm_Address+2];
/*����΢ʱ�ӵ�У*/
struct	TEMPERATURE_FRM		Tpara;
struct	RTC_TRIM_FRM	RTC_RT;
/*����¼�д���*/
/*ʱ�α�*/
const	Str_ProgTable	TB_ProgTimePeriod[C_TB_ProgTimePeriod_Len] =
{
	{CProgPT_NoteC_1,		CFirst_TZone_1PT_Data,		CFirst_TZone_4PT_Data},
	{CProgPT_NoteD_1,		CFirst_TZone_5PT_Data,		CFirst_TZone_8PT_Data},
	{CProgPT_NoteE_1,		CSec_TZone_1PT_Data,		CSec_TZone_4PT_Data},
	{CProgPT_NoteF_1,		CSec_TZone_5PT_Data,		CSec_TZone_8PT_Data}
};
/*ʱ����*/
const	Str_ProgTable TB_ProgSeason[C_TB_ProgSeason_Len] =
{
	{CProgTZ_Note_1,	CFirst_TZone_Data,	CSec_TZone_Data}
};
/*������*/
const	Str_ProgTable	TB_ProgWeekRest[C_TB_ProgWeekRest_Len] =
{
	{CProgWRe_Note_1,	CWeek_RestDay_DTable,	CWeek_RestDay_DTable}
};
/*������1-3����ͬһ�����*/
const	Str_ProgTable	TB_ProgSetADate[C_TB_ProgSetADate_Len] =
{
	{CProgSettD_Note_1,	CSettle_Day1,	CSettle_Day3}
};

/*�й����״̬��*/
const	Str_ProgTable	TB_ProgCombState_P[C_TB_ProgCombState_P_Len] =
{
	{CProgAcC_Note_1,	CActive_Com_State,	CActive_Com_State}
};

/*�޹����״̬��698*/
const	Str_ProgTable	TB_ProgCombState_Q698[C_TB_ProgCombState_Q698_Len] =
{
	{CProgReC698_Note_1,CReactive_Com_State1,CReactive_Com_State2}
};
/*�������㡢�����¼���¼д�ı�񡣺�������治һ�����������¼�������Դ�����ݱ�ʶ��*/
/*�����¼���¼���*/
#define	C_TB_MeterClearEvent_Len		24
const	ulong32	TB_MeterClearEvent[C_TB_MeterClearEvent_Len] =
{
	CPos_Ac_Tol_En_0,		/*�����й�*/
	CRev_Ac_Tol_En_0,		/*�����й�*/
	CQua1_Re_Tol_En_0,		/* 1�����޹�*/
	CQua2_Re_Tol_En_0,		/* 2�����޹�*/
	CQua3_Re_Tol_En_0,		/* 3�����޹�*/
	CQua4_Re_Tol_En_0,		/* 4�����޹�*/
	CPosA_Ac_En_0,			/*A�����й�*/
	CRevA_Ac_En_0,			/*A�����й�*/
	CQua1A_Re_En_0,			/*A-1�����޹�*/
	CQua2A_Re_En_0,			/*A-2�����޹�*/
	CQua3A_Re_En_0,			/*A-3�����޹�*/
	CQua4A_Re_En_0,			/*A-4�����޹�*/
	CPosB_Ac_En_0,			/*B�����й�*/
	CRevB_Ac_En_0,			/*B�����й�*/
	CQua1B_Re_En_0,			/*B-1�����޹�*/
	CQua2B_Re_En_0,			/*B-2�����޹�*/
	CQua3B_Re_En_0,			/*B-3�����޹�*/
	CQua4B_Re_En_0,			/*B-4�����޹�*/
	CPosC_Ac_En_0,			/*C�����й�*/
	CRevC_Ac_En_0,			/*C�����й�*/
	CQua1C_Re_En_0,			/*C-1�����޹�*/
	CQua2C_Re_En_0,			/*C-2�����޹�*/
	CQua3C_Re_En_0,			/*C-3�����޹�*/
	CQua4C_Re_En_0,			/*C-4�����޹�*/
};

/*���ݱ��̼�¼*/
const	Str_ProgTable	TB_StepTariffEvent[C_TB_StepTariffEvent_Len] =
{
	{CProgLad_Note_1,	CCurrent_Ladder_Table,	CBackUp_Ladder_Table}
};


/*���ʵ�۱�̼�¼*/
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
/*698����645����*/
/*�¼��в�����ʱ�������ж�����ʱ��ʶ����Ҫת������Ϊʮ����*/
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
/*698����645����*/
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
	{CMeter_Work_State1,			0x04000501					}, 		/*�������״̬��1*/
	{CMeter_Work_State2,			0x04000502					}, 		/*�������״̬��2*/
	{CMeter_Work_State3,			0x04000503					}, 		/*�������״̬��3*/
	{CMeter_Work_State4,			0x04000504					}, 		/*�������״̬��4*/
	{CMeter_Work_State5,			0x04000505					}, 		/*�������״̬��5*/
	{CMeter_Work_State6,			0x04000506					}, 		/*�������״̬��6*/
	{CMeter_Work_State7,			0x04000507					}, 		/*�������״̬��7*/
	{CComm_Address,					CComm_Address_645			},		/*ͨ�ŵ�ַ*/
	{CSoftw_Record_Number,			CSoftw_Record_Number_645	},		/*���������*/
	{COne485_Baud,					COne485_Baud_645			},		/*ͨ�ſ�1ͨ������������*/
	{CTwo485_Baud,					CTwo485_Baud_645			},		/*ͨ�ſ�2ͨ������������*/
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
	{0x40120200					,	0x04000801					},		/*������������*/
	{0x40130200					,	0x04000802					},		/*�����ղ�����ʱ�α��*/
	{0x41020200					,	0x04000105					},		/*У��������*/
	{0x400C0205					,	0x04000205					},		/*�����ڼ�����*/
	{0xF3000300					,	0x04000302					},		/*ѭ��ÿ����ʾʱ��*/
	{0x40070205					,	0x04000303					},		/*��ʾ����С��λ��*/
	{0x40070206					,	0x04000304					},		/*��ʾ����С��λ��*/
	{CMod_InFr_Baud				,	CMod_InFr_Baud_645			},		/*ͨ�����������ֵ��ƺ���*/
	{0x41120200					,	0x04000601					},		/*�й����������*/
	{0x41130200					,	0x04000602					},		/*�޹���Ϸ�ʽ1������*/
	{0x41140200					,	0x04000603					},		/*�޹���Ϸ�ʽ2������*/
	{0xF3000401					,	0x04000301					},		/*ѭ�Ե�ǰ�ܶ�����*/
	{0xF3010401					,	0x04000305					},		/*���Ե�ǰ�ܶ�����*/
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
	{CPhaseA_Volage,		0x02010100},/*A���ѹ*/
	{CPhaseB_Volage,		0x02010200},/*B���ѹ*/
	{CPhaseC_Volage,		0x02010300},/*C���ѹ*/
	{CPhaseA_Curr,			0x02020100},/*A�����*/
	{CPhaseB_Curr,			0x02020200},/*B�����*/
	{CPhaseC_Curr,			0x02020300},/*C�����*/
	{CInstant_TolAcPow,		0x02030000},/*˲ʱ���й�����*/
	{CInstantA_AcPow  ,		0x02030100},/*A��˲ʱ�й�����*/
	{CInstantB_AcPow  ,		0x02030200},/*B��˲ʱ�й�����*/
	{CInstantC_AcPow  ,		0x02030300},/*C��˲ʱ�й�����*/
	{CInstant_TolRePow, 	0x02040000},/*˲ʱ���޹�����*/
	{CInstantA_RePow  , 	0x02040100},/*A��˲ʱ�޹�����*/
	{CInstantB_RePow  , 	0x02040200},/*B��˲ʱ�޹�����*/
	{CInstantC_RePow  , 	0x02040300},/*C��˲ʱ�޹�����*/
	{CInstant_TolAppaPow, 	0x02050000},/*˲ʱ�����ڹ���*/
	{CInstantA_AppaPow,   	0x02050100},/*˲ʱA���ڹ���*/
	{CInstantB_AppaPow,   	0x02050200},/*˲ʱB���ڹ���*/
	{CInstantC_AppaPow,   	0x02050300},/*˲ʱC���ڹ���*/
	{CTol_PowerFactor, 		0x02060000},/*�ܹ�������*/
	{CPhaseA_PowerFactor, 	0x02060100},/*A��������*/
	{CPhaseB_PowerFactor, 	0x02060200},/*B��������*/
	{CPhaseC_PowerFactor, 	0x02060300},/*C��������*/
	{CZero_Current, 		0x02800001},/*���ߵ���*/
	{CElecNet_Freq, 		0x02800002},/*����Ƶ��*/
	{CCurr_AcDemand, 		0x02800004},/*��ǰ�й�����*/
	{CCurr_ReDemand, 		0x02800005},/*��ǰ�޹�����*/
	{CCloc_Batt_Vol, 		0x02800008},/*ʱ�ӵ�ص�ѹ*/
	{CReadMeter_Batt_Vol, 	0x02800009},/*�����ص�ѹ*/
	{CBatt_Work_Time, 		0x0280000A},/*�ڲ���ع���ʱ��*/
	{CPhaseA_Angle, 		0x02070100},/*A�����*/
	{CPhaseB_Angle,       	0x02070200},/*B�����*/
	{CPhaseC_Angle, 	    0x02070300},/*C�����*/
};
#define Pstr_ParaChange02_Len  (sizeof(Pstr_ParaChange02) / sizeof(Str_ParaChange_OADToDI_Table))

const Str_ParaChange_OADToDI_Table Pstr_ParaChange_Event[Pstr_ParaChange_Event_Len]=
{
  {0x300D0100,			0x030500FF},  /*698-���ܱ�ȫʧѹ�¼�*/
  {0x300F0100,		    0x1400FFFF},  /*698-���ܱ��ѹ�������¼�*/
  {0x30110100,			0x031100FF},  /*698-���ܱ�����¼�*/
  {0x30120100,			0x033000FF},  /*698-���ܱ����¼�*/
  {0x43000500,			0xFFFFFFFF},  /*698-���ܱ������¼�*/
  {0x30140100,			0x033002FF},  /*698-���ܱ����������¼�*/
  {0x30150100,	    	0x033003FF},  /*698-���ܱ��¼������¼�*/
  {0x30160100,			0x033004FF},  /*698-���ܱ�Уʱ�¼�*/
  {0x301B0100,			0x03300DFF},  /*698-���ܱ����¼�*/
  {0x301C0100,		    0x03300EFF},  /*698-���ܱ���ť���¼�*/
  {0x301D0100,		    0x1600FFFF},  /*698-���ܱ��ѹ��ƽ���¼�*/
  {0x301F0100,			0x1D00FFFF},  /*698-���ܱ���բ�¼�*/
  {0x30200100,			0x1E00FFFF},  /*698-���ܱ��բ�¼�*/
  {0x302A0100,			0x033500FF},  /*698-���ܱ�㶨�ų������¼�*/
  {0x302B0100,			0x033600FF},  /*698-���ܱ��ɿ��������¼�*/
  {0x302C0100,			0x033700FF},  /*698-���ܱ��Դ�쳣�¼�*/
  {0x30050100,          0x19FFFFFF},  /*698-����*/
  {0x30000100,          0x10FFFFFF},  /*698-ʧѹ*/
  {0x30040100,          0x18FFFFFF},  /*698-ʧ��*/
  {0x30010100,          0x11FFFFFF},  /*698-Ƿѹ*/
  {0x30020100,          0x12FFFFFF},  /*698-��ѹ*/
  {0x30030100,          0x13FFFFFF},  /*698-����*/
  {0x30070100,          0x1BFFFFFF},  /*698-��������*/
  {0x30130100,          0x033001FF},  /*698-��������¼�*/
  {0x30170100,          0x033005FF},  /*ʱ�α����¼�*/
  {0x30180100,          0x033006FF},  /*ʱ�������¼�*/
  {0x301A0100,          0x03300CFF},  /*�����ձ��*/
};
#define Pstr_ParaChange_Event_Len 27

const Str_DriveReport_Change Pstr_DriveReport_Change[]=
{
	/*645�����ϱ�ģʽ��bit��	 698���¼���OIB�� 	698���ϱ���ʶ��Ӧ�����ԣ�	698��2015�е�bit(����2015��ΪNULL)*/
	{C_ReportMode645_Bit0,		 0x2B,				0x08,						C_NoChangeEvent},			/*���ɿ���������*/
	{C_ReportMode645_Bit1,		 C_NoChangeEvent,	C_NoChangeEvent,		    C_Report698_2015_Bit1},		/*ESAM����*/
	{C_ReportMode645_Bit2,		 C_NoChangeEvent,	C_NoChangeEvent,		    C_NoChangeEvent},			/*�ڿ���ʼ������*/
	{C_ReportMode645_Bit3,		 C_NoChangeEvent,	C_NoChangeEvent,			C_Report698_2015_Bit3},		/*ʱ�ӵ�ص�ѹ��*/
	{C_ReportMode645_Bit4,		 C_NoChangeEvent,	C_NoChangeEvent,			C_NoChangeEvent},			/*�ڲ��������*/
	{C_ReportMode645_Bit5,		 C_NoChangeEvent,	C_NoChangeEvent,			C_Report698_2015_Bit5},		/*�洢�����ϻ���*/
	{C_ReportMode645_Bit6,		 C_NoChangeEvent,	C_NoChangeEvent,			C_NoChangeEvent},			/*����*/
	{C_ReportMode645_Bit7,		 0x2E,				0x08,						C_NoChangeEvent},			/*ʱ�ӹ���*/
	{C_ReportMode645_Bit8,		 C_NoChangeEvent,	C_NoChangeEvent,			C_Report698_2015_Bit8},		/*ͣ�糭����Ƿѹ*/
	{C_ReportMode645_Bit9,		 C_NoChangeEvent,	C_NoChangeEvent,			C_Report698_2015_Bit9},		/*͸֧״̬*/
	{C_ReportMode645_Bit10,		 0x1B,				0x08,						C_NoChangeEvent},			/*�����*/
	{C_ReportMode645_Bit11,		 0x1C,				0x08,						C_NoChangeEvent},			/*����ť��*/
	{C_ReportMode645_Bit12,		 0x2A,				0x08,						C_NoChangeEvent},			/*�㶨�ų�����*/
	{C_ReportMode645_Bit13,		 0x2C,				0x08,						C_NoChangeEvent},			/*��Դ�쳣*/
	{C_ReportMode645_Bit14,		 C_NoChangeEvent,	C_NoChangeEvent,			C_Report698_2015_Bit14},	/*��բ�ɹ�*/
	{C_ReportMode645_Bit15,		 C_NoChangeEvent,	C_NoChangeEvent,			C_Report698_2015_Bit15},	/*��բ�ɹ�*/
	{C_ReportMode645_Bit16,		 0x00,				0x0B,						C_NoChangeEvent},			/*ʧѹ*/
	{C_ReportMode645_Bit17,		 0x01,				0x0B,						C_NoChangeEvent},			/*Ƿѹ*/
	{C_ReportMode645_Bit18,		 0x02,				0x0B,						C_NoChangeEvent},			/*��ѹ*/
	{C_ReportMode645_Bit19,		 0x04,				0x0B,						C_NoChangeEvent},			/*ʧ��*/
	{C_ReportMode645_Bit20,		 0x05,				0x0B,						C_NoChangeEvent},			/*����*/
	{C_ReportMode645_Bit21,		 0x08,				0x0B,						C_NoChangeEvent},			/*����*/
	{C_ReportMode645_Bit22,		 0x07,				0x0B,						C_NoChangeEvent},			/*���ʷ���*/
	{C_ReportMode645_Bit23,		 0x03,				0x0B,						C_NoChangeEvent},			/*����*/
	{C_ReportMode645_Bit24,		 0x06,				0x0B,						C_NoChangeEvent},			/*����*/
	{C_ReportMode645_Bit25,		 C_NoChangeEvent,	C_NoChangeEvent,			C_NoChangeEvent},			/*����*/
	{C_ReportMode645_Bit26,		 C_NoChangeEvent,	C_NoChangeEvent,			C_NoChangeEvent},			/*����*/
	{C_ReportMode645_Bit27,		 C_NoChangeEvent,	C_NoChangeEvent,			C_NoChangeEvent},			/*����*/
	{C_ReportMode645_Bit28,		 C_NoChangeEvent,	C_NoChangeEvent,			C_NoChangeEvent},			/*����*/
	{C_ReportMode645_Bit29,		 C_NoChangeEvent,	C_NoChangeEvent,			C_NoChangeEvent},			/*����*/
	{C_ReportMode645_Bit30,		 C_NoChangeEvent,	C_NoChangeEvent,			C_NoChangeEvent},			/*����*/
	{C_ReportMode645_Bit31,		 C_NoChangeEvent,	C_NoChangeEvent,			C_NoChangeEvent},			/*����*/
	{C_ReportMode645_Bit32,		 0x0F,				0x08,						C_NoChangeEvent},			/*��ѹ������*/
	{C_ReportMode645_Bit33,		 0x10,				0x08,						C_NoChangeEvent},			/*����������  */
	{C_ReportMode645_Bit34,		 0x1D,				0x08,						C_NoChangeEvent},			/*��ѹ��ƽ�� */
	{C_ReportMode645_Bit35,		 0x1E,				0x08,						C_NoChangeEvent},			/*������ƽ�� */
	{C_ReportMode645_Bit36,		 0x0E,				0x08,						C_NoChangeEvent},			/*������Դʧ��*/
	{C_ReportMode645_Bit37,		 0x11,				0x08,						C_NoChangeEvent},			/*����*/
	{C_ReportMode645_Bit38,		 C_NoChangeEvent,	C_NoChangeEvent,			C_NoChangeEvent},			/*��������  698��Ϊ����3009������300A���޹�300B */
	{C_ReportMode645_Bit39,		 0x0C,				0x08,						C_NoChangeEvent},			/*�ܹ������������� */
	{C_ReportMode645_Bit40,		 0x2D,				0x08,						C_NoChangeEvent},			/*�������ز�ƽ�� */
	{C_ReportMode645_Bit41,		 C_NoChangeEvent,	C_NoChangeEvent,			C_NoChangeEvent},			/*�������� 698�����������ڹ��ʷ�����*/
	{C_ReportMode645_Bit42,		 0x0D,				0x08,						C_NoChangeEvent},			/*ȫʧѹ*/
	{C_ReportMode645_Bit43,		 C_NoChangeEvent,	C_NoChangeEvent,			C_NoChangeEvent},			/*����*/
	{C_ReportMode645_Bit44,		 C_NoChangeEvent,	C_NoChangeEvent,			C_NoChangeEvent},			/*����*/
	{C_ReportMode645_Bit45,		 C_NoChangeEvent,	C_NoChangeEvent,			C_NoChangeEvent},			/*����*/
	{C_ReportMode645_Bit46,		 C_NoChangeEvent,	C_NoChangeEvent,			C_NoChangeEvent},			/*���� */
	{C_ReportMode645_Bit47,		 C_NoChangeEvent,	C_NoChangeEvent,			C_NoChangeEvent},			/*����*/
	{C_ReportMode645_Bit48,		 0x12,				0x08,						C_NoChangeEvent},			/*���  */
	{C_ReportMode645_Bit49,		 0x13,				0x08,						C_NoChangeEvent},			/*�������*/
	{C_ReportMode645_Bit50,		 0x14,				0x08,						C_NoChangeEvent},			/*��������*/
	{C_ReportMode645_Bit51,		 0x15,				0x08,						C_NoChangeEvent},			/*�¼�����*/
	{C_ReportMode645_Bit52,		 0x16,				0x08,						C_NoChangeEvent},			/*Уʱ*/
	{C_ReportMode645_Bit53,		 0x17,				0x08,						C_NoChangeEvent},			/*ʱ�α���*/
	{C_ReportMode645_Bit54,		 0x18,				0x08,						C_NoChangeEvent},			/*ʱ������*/
	{C_ReportMode645_Bit55,		 0x19,				0x08,						C_NoChangeEvent},			/*�����ձ��*/
	{C_ReportMode645_Bit56,		 0x21,				0x08,						C_NoChangeEvent},			/*�ڼ��ձ��*/
	{C_ReportMode645_Bit57,		 0x22,				0x08,						C_NoChangeEvent},			/*�й���Ϸ�ʽ���*/
	{C_ReportMode645_Bit58,		 C_NoChangeEvent,	C_NoChangeEvent,			C_NoChangeEvent},			/*�޹���Ϸ�ʽ1��� 698ֻ���޹���Ϸ�ʽ���*/
	{C_ReportMode645_Bit59,		 C_NoChangeEvent,	C_NoChangeEvent,			C_NoChangeEvent},			/*�޹���Ϸ�ʽ2���*/
	{C_ReportMode645_Bit60,		 0x1A,				0x08,						C_NoChangeEvent},			/*�����ձ��*/
	{C_ReportMode645_Bit61,		 0x24,				0x08,						C_NoChangeEvent},			/*���ʲ�������*/
	{C_ReportMode645_Bit62,		 0x25,				0x08,						C_NoChangeEvent},			/*���ݱ���*/
	{C_ReportMode645_Bit63,		 0x26,				0x08,						C_NoChangeEvent},			/*��Կ����*/
};

#define Pstr_DriveReport_ChangeLen  (sizeof(Pstr_DriveReport_Change) / sizeof(Str_DriveReport_Change))

const ulong32 TB_ChannelOAD[]=		/*�ϱ�ͨ��*/
{
	{COne485_Baud},
	{CTwo485_Baud},
	{C485_Baud_Gather},
	{CModular_Baud},
	{CModular_Baud_Gather},
};
#define TB_ChannelOADLen ( sizeof(TB_ChannelOAD) / sizeof(ulong32) )

/***************************************************************************
����ԭ�� 	INF_Comm_ForPowerOn
��������	ͨ��ģ���ϵ��ʼ���ӿں���
�������	��

������� 	��
���ز���	��
ȫ�ֱ��� 	SV_Comm_Parse/SV_Comm_Parse_Local
������ע
***************************************************************************/
void INF_Comm_ForPowerOn(void)
{
	uchar8	buf[C_TimerExceed10minLen];
	uchar8	PowerOffClock[CLEnter_LowPower_Time];
	uchar8	PowerOnClock[CLEnter_LowPower_Time];
	ulong32	PowerOffDUR_Min;						/*��Դ�������ʱ�䣬��λΪmin*/
	ulong32	PowerOffDUR_5Min;
	ushort16	DataLen, V_usDataEncode;
	uchar8	V_ReturnData;
	uchar8	V_ReturnData1;
    uchar8 V_ucBuffer[7];

/*��ʼ�������ڼ���Ӧ��ͨ����������*/
	InF_InitComm(C_RS485_1);
	InF_InitComm(C_RS485_2);
	InF_InitComm(C_Module);
	InF_InitComm(C_IR);

/*��ʼ������֡����*/
	Init_SV_CommNxtFrame(C_RS485_1);
	Init_SV_CommNxtFrame(C_RS485_2);
	Init_SV_CommNxtFrame(C_Module);
	Init_SV_CommNxtFrame(C_IR);

/*������Կ�����Ϣ*/
	Comm_A_MsgToDispatchQueue_UpKeyR(PT_CMsg_UpdKey_Rv_PWOn);

/*��ʼ����̬ȫ�ֱ���SV_Comm_Parse_Local*/
	Comm_ParseInit();

/*��ʼ����̬ȫ�ֱ���SV_Comm_Parse*/
/*��ʼ��SPTVariable*/
	Comm_DealwithSPTVariable(C_InitSPTVariable);
/*��ʼ����ȫ��֤��������֤��Ч��ʱ��*/
	memset( buf,0, C_TimerExceed10minLen );
	DealWith_ID_Auth_Timer(C_Set_TimerExceed10min, &buf[0]);
	DealWith_IR_Auth_Timer(C_Set_TimerExceed10min, &buf[0]);
	DealWith_ID_Auth_T_Timer(C_Set_TimerExceed10min, &buf[0]);
	DealWith_IR_Auth_Timer_645(C_Set_TimerExceed10min, &buf[0]);
/*����ͣ�����ʱ��*/
	DataLen = CLEnter_LowPower_Time;
	V_ReturnData = InF_Read_Data(CEnter_LowPower_Time,PowerOffClock, &DataLen, &V_usDataEncode);
	V_ReturnData1 = InF_Read_Data(CExit_LowPower_Time,PowerOnClock, &DataLen, &V_usDataEncode);
	if( ( V_ReturnData == C_OK )&&( V_ReturnData1 == C_OK ) )
	{
		V_ReturnData = PF_TimeSub_Min_698(PowerOffClock, PowerOnClock, &PowerOffDUR_Min);
		if( V_ReturnData == C_LessThan )
		{
			PowerOffDUR_5Min = PowerOffDUR_Min/5;	/* 1min��ʱ,ת��5min��������*/
		}
		else
		{
			PowerOffDUR_5Min = 0;
			PowerOffDUR_Min = 0;
		}
	}
	else
	{												/*�����͹���ʱ����һ������������ۼ�0.*/
		PowerOffDUR_5Min = 0;
		PowerOffDUR_Min = 0;
	}
/*��ʼ����IJ��Чʱ�䶨ʱ�����������л��ж϶�ʱ����Ч�ſۼ�*/
/*��IJʣ��ʱ���ʼ��*/
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

/*�ж����ϱ���ʱ��ͣ�������˶���?��ʱ���ܡ�*/

	SV_Comm_Parse.Timer_1min = 0;										/*���¶�ʱ*/
	InF_UpdateAccountStateInMeterStatus3();

/*RstModuleParm��ʼ��*/
	DealWith_RstModule(C_Flag_Ok);

/*�ϵ��ʼ���忨״̬��Ϊδ֪*/
	InF_WriteCardStatus(C_CardStatusUnknow);
/*�ϵ��ʼ�������ϱ�δȷ��1s��ʱ��    */
	InF_JudgeESAMConTimer(C_PowerUpDealConectTime, Termal_Address);      /*�ϵ�����*/
	InF_JudgeESAMConTimer(C_PowerUpDealConectTime, Master_Address);      /*�ϵ�����*/

	Inf_Comm_ClearModuleCommuniFlag(0);         						/*ͨ�ű�ʶ����*/
	Inf_Comm_REPORTFlagClear(0);                						/*�����ϱ�����*/
	Inf_DealEventReportShut(C_ReportInit);      						/*�����¼��������ϱ���ʱ��ʱ�����ϵ�����*/

	Inf_Event_REPORTONumDeal(0);                						/*�ϵ��ʼ������������*/
}

/***************************************************************************
����ԭ�� 	void INF_Comm_RecForInt
��������	�жϽ��շ������(�����յ������ݷ��õ�ͨ�Ż��棬���ж��Ƿ�һ֡�������)
�������	CommNo		���ں�
				RecData		���յ���ȷ������
�������
���ز���	C_ContinueReceive:		��������

				C_CorrectFrame:		���յ���ȷ��֡������ȴ���ͨ�Ž�����Ϣ(����Ϊͨ����)
									ͬʱ������Ҫ�رս��ա�
ȫ�ֱ��� 	Str_Comm_Parm�ͱ���
������ע	1�������ز���ע��
				2�����ȵ���ʱ��������ж�һ���ܽ��յ����ֽڣ���ѭ�����ñ�������
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

/*���ͨ��������ô��?����ֱ���˳�*/
	pStr_Comm_Parm_Address = Get_Str_Comm_Parm_Pointer(CommNo);
	if(pStr_Comm_Parm_Address == C_NULL)
	{
		return(C_ContinueReceive);
	}
/*ֻҪͨ����ȷ�����Ǿͽ���ʱ�رա�ͨ��Э��׼ȷ����*/
	CommOTimer = 0;
	if(CommOffset >= C_FramePartMaxLen)
	{
		return(C_AbortReceive);									/*ֱ�Ӳ��ٽ���*/
	}
/*�ж��Ƿ���׼�����յ�1��68*/
	if(CommOffset == C_68_1_OFS_ForRx)
	{
		if(RecData ==0x68)
		{
			CommBuff[CommOffset] = RecData;
			CommOffset++;
			CommRecFlag = CommRecFlag | C_First68_Ok; 			/*698Э�飬��һ��0x68*/
			CommProtocolType = 0;
			CommRecFlag645 = CommRecFlag645 | C_First68_Ok;		/*645Э�飬��һ��0x68*/
			CommProtocolType645 = 0;
		}
		return(C_ContinueReceive);
	}
	if(CommOffset < C_FramePartValueLen)						/*����С��512�ֽڵ�ʱ��ֱ�ӽ���*/
	{
		CommBuff[CommOffset] = RecData;
		CommOffset++;
		if((CommOffset >= 11))
		{
/*********************645֡�ж�**********************/
				if(CommBuff[C_68_2_OFS_ForRx] == 0x68)
				{
					/******************************************/
					CommRecFlag645 = CommRecFlag645 | C_Second68_Ok;
					V_LenTemp = CommBuff[C_L_OFS_ForRx];
					V_LenTemp += C_Comm_FixedRxLen;
					if(V_LenTemp <= 220)						/*645���Ȳ�����220�ֽ�*/
					{
						if(V_LenTemp == CommOffset)				/*���ȵ���offset*/
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
								/****************�ж�ͨ�ŵ�ַ**************/
										for( i = 0; i < CLComm_Address; i++ )
										{
											if( CommBuff[C_CAddr_OFS_ForRx + i] != SV_Comm_Address[i] )
											{
												break;
											}
										}
										for( ; i < CLComm_Address; i++ )
										{
											if( CommBuff[C_CAddr_OFS_ForRx + i] != 0xAA )		/*����ͳ��*/
											{
												break;
											}
										}
										if(i < CLComm_Address)
										{
											for( i = 0; i < CLComm_Address; i++ )
											{
												if(CommBuff[C_CAddr_OFS_ForRx + i] != 0x99)		/*���ǹ㲥*/
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
                                ;/*δ�ж���ȷ����������*/
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

/*************************���������ж��Ƿ�������698*************************************************************/
			if( ( CommRecFlag & ( C_First68_Ok | C_Second68_Ok ) ) != ( C_First68_Ok | C_Second68_Ok ) )	/*��ַû���жϹ�*/
			{
				CommAddrLen = ( CommBuff[C_AF_OFFSet_698] & 0x0F ) + 1;										/*ADDR��ַ����*/
				if( CommOffset < ( CommAddrLen + 8 ) )
				{
					V_LenTemp =  CommBuff[C_LH_OFFSet_698];
					V_LenTemp <<= 8;
					V_LenTemp |= (ushort16)CommBuff[C_LL_OFFSet_698];										/*֡����*/
					if( ( V_LenTemp > C_FramePartMaxLen )													/*���Ȳ���*/
					 || ( ( CommBuff[ C_C_OFFSet_698] & 0x07 ) != 0x03 ) )									/*�����ֲ���*/
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
						/****************�ж�ͨ�ŵ�ַ**************/
						if( ( CommBuff[C_AF_OFFSet_698] & 0xC0 ) == 0xC0 )			/*�㲥��ַ*/
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
							CommRecFlag = CommRecFlag | C_Second68_Ok;				/*�ڶ���68����֡ͷУ������ȷ*/

							V_LenTemp =  CommBuff[C_LH_OFFSet_698];
							V_LenTemp <<= 8;
							V_LenTemp |= (ushort16)CommBuff[C_LL_OFFSet_698];		/*֡����*/
							if( V_LenTemp <= ( C_FramePartValueLen - 2 ) )
							{
								CommLen = V_LenTemp + 2;							/*֡ͷ68+֡β16*/
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
			else/*��ַ�Ѿ��жϹ� */
			{
                if(CommOffset == CommLen)
                {
					CommRecFlag = CommRecFlag | C_CS_Ok;
					if(RecData == 0x16)
					{
						CommRecFlag = CommRecFlag | C_16_Ok;
						CommProtocolType = C_ProtocolType_698;				/*ȷ����698*/
					}
					else
					{
						CommProtocolType = C_ProtocolType_NOT698;			/*ȷ������698*/
					}

                }
				else  if( ( CommOffset - C_First68_OFFSet_698 ) > CommLen )
				{
					CommProtocolType = C_ProtocolType_NOT698;				/*ȷ������698*/
				}
                else
                {
                    ;/*δ�жϣ���������*/
                }
			}
            if( ( CommProtocolType == C_ProtocolType_NOT698 ) && ( CommProtocolType645 == C_ProtocolType_NOT645 ) )		/*����698Ҳ����645*/
            {
                for( i = 1; i < CommOffset; i++)
				{
					if(CommBuff[i] == 0x68)
					{
						break;
					}
				}
				if(i < CommOffset)					/*��֡ͷ���ţ�����һ��0x68������λ*/
				{
                    memmove(&CommBuff[C_First68_OFFSet_698], &CommBuff[i], CommOffset);
                    CommOffset -= i;
                    CommProtocolType = C_ProtocolType_Init;
                    CommProtocolType645 = C_ProtocolType_Init;
                    V_ucReturn = C_ContinueReceive;							/*��������*/
				}
                else								/*����û��0x68*/
                {
                    CommProtocolType = C_ProtocolType_NOT698;
                    CommProtocolType645 = C_ProtocolType_NOT645;
                    V_ucReturn = C_AbortReceive;	/*����645Ҳ����698�����ٽ���*/
                }
            }
            else if( ( CommProtocolType == C_ProtocolType_698 ) || ( CommProtocolType645 == C_ProtocolType_645 ) )		/*ȷ����698������645*/
            {
                V_ucReturn = C_CorrectFrame;		/*����ȷ֡*/
            }
            else
            {
                V_ucReturn = C_ContinueReceive;		/*δ�жϣ���������*/
            }

		}
		else
		{
            V_ucReturn = C_ContinueReceive;			/*δ�жϣ���������*/
		}
	}
    return V_ucReturn;
}

/***************************************************************************
����ԭ�� 	INF_Comm_TxdForInt
��������	���ڷ����жϷ������
�������	CommNum:		���ں�ȡֵ����1·485����2·485�����⣻ģ��
				p_TxdData:		���������ݵ�ָ��
������� 	*p_TxdData		�����͵�����
���ز���	C_ContinueTransmit: 	��������
				C_AbortTransmit:		�˳�����
ȫ�ֱ���
������ע	ע���������1���ֽ�0x16����ʱӦ��������C_ContinueTransmit
				������16���ٴν����жϣ��ŷ���C_AbortTransmit��Ҫ����ȳ�ʼ������
***************************************************************************/
uchar8 INF_Comm_TxdForInt(uchar8 CommNum, uchar8	*p_TxdData)
{
	uchar8	V_ReturnData = C_AbortTransmit;
	Str_Comm_Parm	*pStr_Comm_Parm_Address;

	if(SV_SetBPS_Flag == C_OK)
	{
		V_ReturnData = C_AbortTransmit_SetBPS;
	}
/*���ͨ��������ô��?����ֱ���˳�*/
	pStr_Comm_Parm_Address = Get_Str_Comm_Parm_Pointer(CommNum);
	if(pStr_Comm_Parm_Address == C_NULL)
	{
		return(C_AbortTransmit);					/*�������Ӧ���ǲ����ܳ��ֵġ�*/
	}
/*ֻҪͨ����ȷ�����Ǿͽ���ʱ�رա�ͨ��Э��׼ȷ����*/
	CommOTimer = 0;

/*�жϻ������ĳ����Ƿ����*/
    if(CommProtocolType == C_ProtocolType_698)
    {
        if(CommLen >= C_FramePartMaxLen)
		{
			CommLen = 0;
			CommOffset = 0;
			CommRecFlag = 0;
			CommOTimer = 0;
            CommProtocolType = C_ProtocolType_Init;
			return(V_ReturnData);					/*���Ȳ������˳����͡�Ӧ���ǲ����ܷ����ġ�*/
		}
/*�ж���û�з�����ɡ����16Ҳ�����ˣ����˳����͡�*/
        if(CommOffset >= CommLen)
		{
			CommLen = 0;
			CommOffset = 0;
			CommRecFlag = 0;
			CommOTimer = 0;
            CommProtocolType = C_ProtocolType_Init;
			return(V_ReturnData);					/*�������*/
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
			return(V_ReturnData);					/*���Ȳ������˳����͡�Ӧ���ǲ����ܷ����ġ�*/
        }
        if(CommOffset >= CommLen645)
        {
			CommLen645 = 0;
			CommOffset = 0;
			CommRecFlag645 = 0;
			CommOTimer = 0;
            CommProtocolType645 = C_ProtocolType_Init;
			return(V_ReturnData);					/*�������*/
        }
    }
/*��������*/
	*p_TxdData = CommBuff[CommOffset];
	(CommOffset)++;
	return(C_ContinueTransmit);

}
/*******************************************************************************
����ԭ�ͣ� void Inf_CalReportCRC(void)
���������� �ϱ��ṹ����CRC
���������
���������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
void Inf_CalReportCRC(void)
{
    SF_Deal_ReportCRC(C_CountCRC);
}
/*******************************************************************************
����ԭ�ͣ� uchar8 INF_Comm_TxdForInt_698Report(uchar8 CommNum,uchar8	*p_TxdData)
���������� ���ڷ����жϷ������(�ϱ���
���������CommNum:		���ں�ȡֵ����1·485����2·485�����⣻ģ��
	      p_TxdData:		���������ݵ�ָ��
���������*p_TxdData		�����͵�����
���ز����� C_ContinueTransmit: 	��������
		  C_AbortTransmit:		�˳�����
����λ�ã�
��    ע�� ע���������1���ֽ�0x16����ʱӦ��������C_ContinueTransmit
				������16���ٴν����жϣ��ŷ���C_AbortTransmit��Ҫ����ȳ�ʼ������
*******************************************************************************/
uchar8 INF_Comm_TxdForInt_698Report(uchar8 CommNum,uchar8	*p_TxdData)
{
	uchar8	V_ReturnData = C_AbortTransmit;

    SV_SetBPS_Flag = C_Error;				/*Ĭ�ϲ�������BPS*/

/*�жϻ������ĳ����Ƿ����*/
	if( SV_ReportSend.ReportLen > ( C_FramePartMaxLen + C_Comm_FixedTxLen ) )
	{
		SV_ReportSend.ReportLen = 0;
		SV_ReportSend.ReportOffset = 0;
		Inf_CalReportCRC();
		return(V_ReturnData);				/*���Ȳ������˳����͡�Ӧ���ǲ����ܷ�����*/
	}

/*�ж���û�з�����ɡ����16Ҳ�����ˣ����˳����͡�	*/
	if(SV_ReportSend.ReportOffset >= SV_ReportSend.ReportLen)
	{
		SV_ReportSend.ReportLen = 0;
		SV_ReportSend.ReportOffset = 0;
		Inf_CalReportCRC();
		return(V_ReturnData);				/*�������*/
	}

/*��������*/
	*p_TxdData = SV_REPORTCommBuff[SV_ReportSend.ReportOffset];
	(SV_ReportSend.ReportOffset)++;
	Inf_CalReportCRC();
	return(C_ContinueTransmit);
}
/***************************************************************************
����ԭ�� 	INF_WrClearAllRecord
��������	��������¼���¼���������ݲ����壬���������ϱ���
�������	*pOpCode				:�����ߴ���(�̶�Ϊ4�ֽ�)
				SafeFlag				:��ȫ�ֽڣ�һ·�������ݲ�
������� 	��
���ز���	C_OK/C_Error
ȫ�ֱ���
������ע	ע�⣬��������ֳ���ģʽ����ģʽ��
				���ڣ������������¼�������ݲ�����ͳ�����΢С����
***************************************************************************/
uchar8 INF_WrClearAllRecord (uchar8 *pOpCode, uchar8	SafeFlag)
{
	uchar8	FactoryType = C_FactoryOutType;
	Str_Comm_645	V_645Frame = {0};

/*��ȫ�����ֽ��ж�*/
	if( SafeFlag != C_ClearMeterSafeFlag )
	{
		return(C_Error);
	}
/*����ģʽ��������ʲô�ܼ����㣬�����������¼���¼����Ϊ����ģʽ��*/
	if( JudgeTimerExceed10min(&SI_JTimer_BSOn2500) != C_TimerEnable )
	{
		Have_IPEvent_Prog_698(CTol_Clear_Note_1, CTol_Clear_Degree, &V_645Frame);
	}
	else
	{
		FactoryType = C_FactoryInType;
	}
/*�������ݲ�����庯��*/
	InF_Total_Clear(C_Msg_Communication, FactoryType,SafeFlag);
/*��RAM�б�̼�¼����*/
	INF_Init_Str_ProgRecord(&SV_Comm_Parse.ProgRecord);
	INF_Init_Str_ProgRecord_645(&SV_Comm_Parse.ProgRecord_645);
	Init_SV_ReportNewAddNum();							/*������������ϱ�����*/
	Init_SV_HaveReportState();							/*�����������ȫ����λ�����ϱ��������ж��й����ٴ��ϱ�*/
	if(FactoryType == C_FactoryOutType)					/*������ϱ�*/
    {
      InF_ActiveReportSetting(C_Times_MeterClear);		/*������������ϱ�����������˽Կ���ϱ�*/
    }
    else
    {
      ;/*���ڹ�Կ��˽Կ�������ϱ�*/
    }

	Inf_ReportList(C_ReportChannelAll,C_TolClearEventNo,C_NewReport);	/*�����ϱ�*/
    Inf_EventReport_HP(C_TolClearEventNo,C_NewReport);
    Inf_CleanAllMeterStatus8();
	return C_OK;
}
/***************************************************************************
����ԭ�� 	INF_Init_Str_ProgRecord
��������	��ʼ����̼�¼ȫ�־�̬����
�������	pProgRecord		:���ʼ���ı�̱���ָ��

������� 	*pProgRecord		:��ʼ���������
���ز���	��
ȫ�ֱ��� 	SV_Comm_Parse.ProgRecord
������ע	pProgRecord	��ָ�����ȫ�־�̬����ָ�롣
����˵��
				1��	SV_Comm_Parse. ProgRecord.OpclockΪȫ0
				2��	SV_Comm_Parse. ProgRecord.OpCodeΪȫFF
				3��	SV_Comm_Parse. ProgRecord.DIΪȫFF
				4��	����CRC
***************************************************************************/
void INF_Init_Str_ProgRecord (Str_ProgRecord		*pProgRecord)
{
	uchar8	i;
	uchar8	j;
	uchar8	Progbuf[70];		/*6+4+40+2=52*/
	uchar8	*pProgbufDI;

	for( i = 0; i < 19; i++ )
	{/*���ʱ������*/
		Progbuf[ProgOpClock_O + i] = 0x00;
		ProgOpClock[i] = Progbuf[ProgOpClock_O + i] ;
	}

	pProgbufDI = &Progbuf[ProgDI_O];
	for( i = 0; i < 10; i++ )
	{/*DI ȫFF*/
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
����ԭ�� 	INF_Init_Str_ProgRecord
��������	��ʼ����̼�¼ȫ�־�̬����
�������	pProgRecord		:���ʼ���ı�̱���ָ��

������� 	*pProgRecord		:��ʼ���������
���ز���	��
ȫ�ֱ��� 	SV_Comm_Parse.ProgRecord
������ע	pProgRecord	��ָ�����ȫ�־�̬����ָ�롣
����˵��
				1��	SV_Comm_Parse. ProgRecord.OpclockΪȫ0
				2��	SV_Comm_Parse. ProgRecord.OpCodeΪȫFF
				3��	SV_Comm_Parse. ProgRecord.DIΪȫFF
				4��	����CRC
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

    /*���ʱ������*/
    memset(&Progbuf[ProgOpClock_O_645], 0, 7);
    PF_CopyDataBytes(&Progbuf[ProgOpClock_O_645], ProgOpClock_645, 7);

    /*�����ߴ���ȫFF*/
    memset(&Progbuf[ProgOpCode_O_645], 0xFF, 4);
    memset(ProgOpCode_645, 0xFF, 4);

	pProgbufDI = &Progbuf[ProgDI_O_645];
	for( i = 0; i < 10; i++ )
	{/*DI ȫFF*/
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
����ԭ�� 	INF_Append_ProgRecordDI
��������	��Str_ProgRecord����������һ�α�̼�¼
�������	*pOpCode		���α�̵Ĳ����ߴ���,�̶�Ϊ4�ֽ�
			  	*pProgDI		���α�̵����ݱ�ʶ��,�̶�Ϊ4�ֽ�
				pProgRecord	��̼�¼����ȫ�ֱ���ָ��
������� 	*pProgRecord	����õı�̼�¼
���ز���	��
ȫ�ֱ��� 	pProgRecord	��ָ�����ȫ�־�̬����ָ�롣
����ʱ��	14��������1��2�������������������б�̼�¼��
				ע��3�������д�������֤��Чʱ������Ҳ��д
***************************************************************************/
void INF_Append_ProgRecordDI (uchar8 *pOpCode, uchar8 *pProgDI, Str_ProgRecord *pProgRecord, uchar8 V_ProgType)
{
	uchar8	i, j;
	uchar8	Progbuf[500];		/*6+4+40+2=52*/
	uchar8	*pProgbufDI;
	uchar8	V_ReturnData;
	ushort16	DataLen, LenFor_Data = 400;

	/* ��Ӧ������ȡ��������£�������ǲ忨���������˳���������̼�¼ */
	/* һ��ʼ��Ӧ������ȡ��������²�����̼�¼����Ϊ��ģ�鲨����Э�̡�д�ź�ǿ�Ȳ�����̼�¼ */
	/* ���Ƕ��ڿ����������忨���ȡ�����е�Ӧ��������Ϣ����ʱ��д��������������̼�¼�ˣ�������������ж� */
	/* 2021��1��28���޸� mym+fy+gyj */
	if( InF_ConectTimer_DealNoTimer() == C_TimerDisable )
	{
		if( ( pProgDI[2] != 0x98 )
		 || ( pProgDI[3] != 0x99 ) )
		{
			return;
		}
	}

	V_ReturnData = Get_ProgRecord1InRam(Progbuf, pProgRecord);

/*�ȼ����ѱ���ı���¼���¼�Ƿ�CRC��ȷ,����ȷ����0*/
	if( ( V_ReturnData != C_OK ) && ( V_ReturnData != C_CrcErr_DataZero ) )
	{
		memset(Progbuf, 0x00, ProgCrc_O);
	}
	/*�жϵ�ǰ��̼�¼�е�ʱ���Ƿ�Ϊȫ0��*/
	if( ( V_ReturnData != C_OK ) || ( Is_Buf_AllZero( &Progbuf[ProgOpClock_O], 7 ) == C_OK ) )
	{/*ȡ�ڴ��̼�¼ʱ����CRC���ʱ��Ϊ0�Ĵ��󣬲�����ʲô���󣬶���ʼ��*/
		/*DIȫ��ΪFF*/
		pProgbufDI = &Progbuf[ProgDI_O];
		memset(pProgbufDI, 0xFF, ProgOADLen);

		Inf_EventReport_HP(C_ProgramEventNo, C_NewReport);
        InF_ActiveReportSetting(C_Times_Program);

		DataLen = SF_GetProgFixedData_698(CProgram_Degree, Progbuf);

		PF_CopyDataBytes(&Progbuf[0], &ProgOpClock[0], CLProgFixedData);

		memset(&Progbuf[ProgDI_O], 0x00, ProgOADLen);
		DataLen += ProgOADLen;
		if( Inf_GetRecordData( &Progbuf[ProgCrc_O], &LenFor_Data, CProgram_OADTab, 0x01 ) == C_OK )	/*ȡ��������*/
		{
			DataLen += 	LenFor_Data;
		}
		InF_Write_Data(C_Msg_Communication, CProgram_Note_1, Progbuf, DataLen, C_W_SafeFlag);
	}
/*������¼���¼��DI������λDI[i] <- DI[i-1],�µļ��뵽DI[0]*/
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
����ԭ�� 	INF_Append_ProgRecordDI
��������	��Str_ProgRecord����������һ�α�̼�¼
�������	*pOpCode		���α�̵Ĳ����ߴ���,�̶�Ϊ4�ֽ�
			  	*pProgDI		���α�̵����ݱ�ʶ��,�̶�Ϊ4�ֽ�
				pProgRecord	��̼�¼����ȫ�ֱ���ָ��
������� 	*pProgRecord	����õı�̼�¼
���ز���	��
ȫ�ֱ��� 	pProgRecord	��ָ�����ȫ�־�̬����ָ�롣
����ʱ��	14��������1��2�������������������б�̼�¼��
				ע��3�������д�������֤��Чʱ������Ҳ��д
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
	{/*ȡ�ڴ��̼�¼ʱ����CRC���ʱ��Ϊ0�Ĵ��󣬲�����ʲô���󣬶���ʼ��*/
	  /*Progbuf����ͷ��ʼ��*/
		/*ȡʱ��*/
		DataLen = CLDate_Time;
		InF_Read_Data(CDate_Time, &Progbuf[ProgOpClock_O_645], &DataLen, &V_usDataEncode);
		/*ȡ�����ߴ��� */
		PF_CopyDataBytes(&pOpCode[0], &Progbuf[ProgOpCode_O_645] ,4);
		/*DIȫ��ΪFF*/
		pProgbufDI = &Progbuf[ProgDI_O_645];
		memset(pProgbufDI, 0xFF, 40);
		Inf_EventReport_HP(C_ProgramEventNo, C_NewReport);
		InF_ActiveReportSetting(C_Times_Program);		/*��������ϱ�*/
	}
/*������¼���¼��DI������λDI[i] <- DI[i-1],�µļ��뵽DI[0]*/
	pProgbufDI = &Progbuf[ProgDI_O_645];
	for( i = 9; i > 0; i-- )
	{
		for( j = 0; j < 4; j++ )
		{
			pProgbufDI[i * 4 + j] = pProgbufDI[( i - 1 ) * 4 + j];

		}
	}
/*���µ�DI�����뵽DI������*/
    if( ( pProgDI[1] == 0x02 ) && ( pProgDI[2] == 0x01 ) && ( pProgDI[3] == 0xF2 ) )	/*F2010201����ͨ�ſ�1����������*/
    {
        pProgbufDI[0] = pProgDI[0] + 2;        					/*645�ı�ʶ���698��DI0��2*/
        pProgbufDI[1] = (uchar8)(COne485_Baud_645 >> 8);		/*�����698��ʶ��ͨ�ſ�1���������ָĳ�645��ʶ��*/
        pProgbufDI[2] = (uchar8)(COne485_Baud_645 >> 16);
        pProgbufDI[3] = (uchar8)(COne485_Baud_645 >> 24);
    }
    else
    {
        PF_CopyDataBytes(&pProgDI[0], &pProgbufDI[0] ,4);
    }

/*��ֵ��������CRC*/
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
����ԭ�� 	INF_StopProgState
��������	������Զ�̱��״̬(�����֤ȡ��)�ͽ�Str_ProgRecord��ָ����
				д�����һ�α�̼�¼
�������	*pProgRecord		���һ�α������

������� 	*pProgRecord		�ñ���ȫ������
���ز���	C_Ok��C_Error�����ݲ㷵��ֵ
ȫ�ֱ��� 	SV_Comm_Parse.ID_Authentication_Timer
������ע	ֻ������ģ�����д���ı�̼�¼��
***************************************************************************/
uchar8 INF_StopProgState(Str_ProgRecord *pProgRecord)
{
	uchar8	 Progbuf[500];		/*6+4+40+2=52*/
	uchar8	 V_ReturnData;
	uchar8	 W_Safe_Flag = C_W_SafeFlag_1;
	ushort16 LenFor_Data = 400, V_Len = ProgCrc_O, V_usDataEncode;

/*д���һ�α���¼���¼*/
/*��ȡ����*/
	V_ReturnData = Get_ProgRecord1InRam(Progbuf, pProgRecord);

	InF_Read_Data(CDate_Time, &Progbuf[ProgEndTime], &V_Len, &V_usDataEncode);/*����ʱ��*/
/*��Str_ProgRecord��ʼ����*/
	INF_Init_Str_ProgRecord(pProgRecord);

/*�ж�CRC�Ƿ���ȷ����ȷ��д������ȷֱ���˳�*/
	W_Safe_Flag = W_Safe_Flag | C_W_SafeFlag_2;

	if(V_ReturnData != C_OK)
	{/*ȡ���������ݲ�����CRC����ȷ���Ǳ��ʱ��Ϊȫ0������Ϊ�Ǵ��󣬲�����ʵ��д�¼���¼*/
		return(C_Error);
	}
	W_Safe_Flag = W_Safe_Flag | C_W_SafeFlag_3;
	V_Len = ProgCrc_O;
	if( Inf_GetRecordData( &Progbuf[ProgCrc_O], &LenFor_Data, CProgram_OADTab, 0x02 ) == C_OK )/*ȡ��������*/
	{
		V_Len += LenFor_Data;
	}

/*д���һ�α�̼�¼*/
	V_ReturnData = InF_Write_Data(C_Msg_Communication, CProgram_Note_1 + 1, Progbuf, V_Len, W_Safe_Flag);
	return(V_ReturnData);
}

/***************************************************************************
����ԭ�� 	INF_StopProgState
��������	������Զ�̱��״̬(�����֤ȡ��)�ͽ�Str_ProgRecord��ָ����
				д�����һ�α�̼�¼
�������	*pProgRecord		���һ�α������

������� 	*pProgRecord		�ñ���ȫ������
���ز���	C_Ok��C_Error�����ݲ㷵��ֵ
ȫ�ֱ��� 	SV_Comm_Parse.ID_Authentication_Timer
������ע	ֻ������ģ�����д���ı�̼�¼��
***************************************************************************/
uchar8 INF_StopProgState_645(Str_ProgRecord_645 *pProgRecord_645)
{
	uchar8	Progbuf[53];		/*6+4+40+2=52*/
	uchar8	V_ReturnData;
	uchar8	W_Safe_Flag = C_W_SafeFlag_1;

	V_ReturnData = Get_ProgRecord1InRam_645(Progbuf, pProgRecord_645);
/*��Str_ProgRecord��ʼ����*/
	INF_Init_Str_ProgRecord_645(pProgRecord_645);

/*�ж�CRC�Ƿ���ȷ����ȷ��д������ȷֱ���˳�*/
	W_Safe_Flag = W_Safe_Flag | C_W_SafeFlag_2;

	if(V_ReturnData != C_OK)
	{/*ȡ���������ݲ�����CRC����ȷ���Ǳ��ʱ��Ϊȫ0������Ϊ�Ǵ��󣬲�����ʵ��д�¼���¼*/
		return(C_Error);
	}
	W_Safe_Flag = W_Safe_Flag | C_W_SafeFlag_3;
/*д���һ�α�̼�¼*/
	V_ReturnData = InF_Write_Data(C_Msg_Communication, CProgram_Note_1_645, Progbuf, CLProgram_Note_1_645, W_Safe_Flag);
	return(V_ReturnData);
}
/***************************************************************************
����ԭ�� 	INF_StopCommProgState
��������	�˳�ͨ�ű��״̬
�������	��

������� 	��
���ز���	SV
ȫ�ֱ��� 	SV_Comm_Parse.ProgRecord
������ע	������ģ����֤ͨ�����������ȵ��ñ�����
				Զ�̱��״̬��д��̼�¼��
				ͨ��ģ�������̼�¼ʱҲ�ɵ��ñ�������
***************************************************************************/
void		INF_StopCommProgState(void)
{
	INF_StopProgState(&SV_Comm_Parse.ProgRecord);
	INF_StopProgState_645(&SV_Comm_Parse.ProgRecord_645);	/*����������˳��Ҫ�ߵ�������һ���йرձ��״̬*/
}

/***************************************************************************
����ԭ��: uchar8 Get_ProgRecord1InRam(uchar8 *pProgRecordInRam, Str_ProgRecord *pProgRecord)
��������: ��ȡ�ڴ���1�α�̼�¼������(����2�ֽ�CRC)
�������: pProgRecordInRam:�������ָ��
          *pProgRecord:���һ�α������
�������: *pProgRecordInRam:�̶�Ϊ52�ֽڣ����Ե���ʱ����������Ҫȷ��
���ز���: C_OK:��ʾ�����ڱ��״̬; C_Error:��ʾ�����ڱ��״̬��CRC����
����λ��:
��    ע: *pProgRecord����ı䣬����������ע�͡�
***************************************************************************/
uchar8 Get_ProgRecord1InRam(uchar8 *pProgRecordInRam, Str_ProgRecord *pProgRecord)
{
	uchar8	*pProgbufDI;
	uchar8	V_ReturnData;
	uchar8	i;

	/*ȡ�ڴ��̼�¼*/
	PF_CopyDataBytes(&ProgOpClock[0], &pProgRecordInRam[0], CLProgFixedData);

	pProgbufDI = &pProgRecordInRam[ProgDI_O];
	for( i = 0; i < CProgOADNum; i++ )
    {
        PF_CopyDataBytes(&ProgDI[i][0], &pProgbufDI[i * CLProgTypeOADGather], CLProgTypeOADGather);
    }
	PF_Ushort16ToBuffer2(&pProgRecordInRam[ProgCrc_O], &ProgCrc);
    /*�ж��Ƿ��ڱ��״̬���ж�������2:
    1��CRC�Ƿ���ȷ
    2�����ʱ���Ƿ�Ϊȫ0
    �Ƿ��������֤�ڼ䣬�Ȳ��ܡ���ֹ�Ժ���չ����������*/
	V_ReturnData = PF_Check_CRC( pProgRecordInRam, ( ProgCrc_O + 2 ) );
	if( V_ReturnData != C_OK )
    {
        /*CRC����ȷ*/
        return(C_Error);
    }

	V_ReturnData = Is_Buf_AllZero(&pProgRecordInRam[ProgOpClock_O], 7);
	if( V_ReturnData == C_OK )
    {
        /*ʱ��ȫ0��Ҳ���ش���*/
        return(C_Error);
    }
	return(C_OK);
}
/**********************************************************************************
Function���ж��ϵ��ʵʱ������ʱ���Ƿ�*
�ú����ж��ϵ��Ĵ����Ƿ�Ϊ0,��Ϊ0����C_Error,Ϊ0����C_OK,Ϊ�Ƿ�ֵ���㶨ʱ��������C_OK
**********************************************************************************/
uchar8 Inf_DealEventReportShut(uchar8 Type)
{
    uchar8      V_Return = C_Error;

    if(C_ReportInit == Type)						/*�ϵ��ʼ��*/
    {
        SV_ReportShutTime = C_ReportInitTime;		/*�ϵ��ʼ��ʱ��Ϊ����ģ�����ʱ��+�����¼�����ʱ��*/
    }
    else
    {
		if( SV_ReportShutTime > C_ReportInitTime )
		{/*�������ֵ,��Ϊʱ�䵽,�����Ĵ�������*/
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
����ԭ�� 	Get_ProgRecord1InRam
��������	��ȡ�ڴ���1�α�̼�¼������(����2�ֽ�CRC)
�������	pProgRecordInRam				:�������ָ��
				*pProgRecord					:���һ�α������
������� 	*pProgRecordInRam				:�̶�Ϊ52�ֽڣ����Ե���ʱ����������Ҫȷ��
���ز���	C_OK						:��ʾ�����ڱ��״̬
				C_Error						:��ʾ�����ڱ��״̬��CRC����
ȫ�ֱ���
������ע	*pProgRecord����ı䣬����������ע�͡�
***************************************************************************/
uchar8	Get_ProgRecord1InRam_645(uchar8	*pProgRecordInRam, Str_ProgRecord_645 *pProgRecord_645)
{
	uchar8	*pProgbufDI;
	uchar8	V_ReturnData;
	uchar8	i;

	/*ȡ�ڴ��̼�¼*/
	PF_CopyDataBytes(&ProgOpClock_645[0], &pProgRecordInRam[ProgOpClock_O_645], 7);
    PF_CopyDataBytes(&ProgOpCode_645[0], &pProgRecordInRam[ProgOpCode_O_645], 4);
	pProgbufDI = &pProgRecordInRam[ProgDI_O_645];

	for( i = 0; i < 10; i++ )
	{
		PF_CopyDataBytes( &ProgDI_645[i][0], &pProgbufDI[i * 4], 4 );
	}
	PF_Ushort16ToBuffer2( &pProgRecordInRam[ProgCrc_O_645], &ProgCrc_645 );
/*�ж��Ƿ��ڱ��״̬���ж�������2:*/
/* 1��CRC�Ƿ���ȷ*/
/* 2�����ʱ���Ƿ�Ϊȫ0*/
/*�Ƿ��������֤�ڼ䣬�Ȳ��ܡ���ֹ�Ժ���չ����������*/
	V_ReturnData = PF_Check_CRC( pProgRecordInRam, ( CLProgram_Note_1_645 + 2 ) );
	if(V_ReturnData != C_OK)
	{
		/*CRC����ȷ*/
		return(C_Error);
	}
	V_ReturnData = Is_Buf_AllZero(&pProgRecordInRam[ProgOpClock_O_645], 7);
	if(V_ReturnData ==C_OK)
	{
		/*ʱ��ȫ0��Ҳ���ش���*/
		return(C_Error);
	}
	return(C_OK);
}
/*******************************************************************************
����ԭ�ͣ� uchar8 Comm_ParseMessage(Str_Msg_Parameter * P_Msg_Parameter)
�������������ͨ��ģ����Ϣ�������(��һ��)
���������*P_Msg_Parameter:			��Ϣ�ṹ��
�����������
���ز����� Ok/C_Error
����λ�ã�
��    ע�����1��	SourceAddr= ���ȡ������жϷ���ͨѶ������Ϣ��
				DerictAddr = C_Msg_Communication
				Len = 2
				������Pt_Comm_No,ȡֵ��C_RS485_1��C_RS485_2��C_IR��C_Module
				�е�һ��
	���2��	SourceAddr= ���ȡ�����ÿ500ms����ͨѶ������Ϣ
				DerictAddr = C_Msg_Communication
				Len = 2
				������Pt_Dispatch_Timing��ȡֵC_HalfSecond
	���3��	SourceAddr��C_Msg_Communication���ϵ����յ���Կ��������󴥷�
				DerictAddr = C_Msg_Communication
				Len = 1
				������PT_CMsg_UpdataKey_Review,ȡֵΪ��
	���4��	SourceAddr��C_Msg_Dispatch�����յ���̿��غ󴥷�
				DerictAddr = C_Msg_Communication
				Len = 2
				������ΪPt_Dispatch_Key��ȡֵΪC_KeyPrg
*******************************************************************************/
uchar8 Comm_ParseMessage(Str_Msg_Parameter * P_Msg_Parameter)
{
	uchar8	*pParm;
	uchar8  V_ReportState = 0;
	Str_Comm_Parm 	*pStr_Comm_Parm_Address;

/*������ȷ�������ͣ�磬��ôֱ���˳�������C_OK*/
	if(P_Msg_Parameter->PowerFlag == C_PowerFalling)
	{/*ע�⣬ͨ���е͹��������е�Ҫ���������ֻ���ж�C_PowerFalling*/
		return(C_OK);
	}

/*�����������,����������÷����������*/
	pParm = P_Msg_Parameter->Parameter;
	if(*pParm == Pt_Comm_No)
	{
		if(P_Msg_Parameter->Length ==(Pt_Comm_No_Len + 1))
		{
			/*���1.���ﲻ�жϴ��ں��Ƿ���ȷ��Ӧ��Comm_Parse�����ж�*/
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
				;/*�����ǣ�������*/
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
					/*���2����ʱ��Ϣ*/
					Comm_500ms_Execute(P_Msg_Parameter->PowerFlag);
				  return(C_OK);
			}
			else if(*pParm == C_SystemSecondChange)
			{
				/*2020��׼�����ϱ�2005*/
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
����ԭ�� 	Have_IPEvent_MeterClear
��������	ӵ�ж�������¼���Ŀ��������̣���ɶ�Ӧ�¼���¼�����ݲ������壩
�������	*pV_645Frame				:���յ���645֡	,��ʹ�õ����еĲ����ߴ���
������� 	��
���ز���	��
ȫ�ֱ��� 	��
������ע	��ȫ����3����ͨ��RecFlag�����㰲ȫ�ֽڣ���̰�ȫ�ֽ�
***************************************************************************/
void		Have_IPEvent_MeterClear(Str_Comm_645 *pV_645Frame )
{
	uchar8	Flag;
/*��ȫ�����ֽ��ж�*/
	if(SV_Comm_Parse_Local.RecFlag!=C_CommRecFlagForInt_Ok)
	{
		return;
	}
	if( ( SV_Comm_Parse_Local.MeterClearFlag == C_ClearMeterSafeFlag )
	 && ( SV_Comm_Parse_Local.SafeControlFlag==C_W_SafeFlag ) )
	{/*��ȫ�ֽ���ȷ������д�����¼���������ݲ����壬���������ϱ�����*/
		INF_WrClearAllRecord(pV_645Frame->Opcode, SV_Comm_Parse_Local.MeterClearFlag);
	}
/*����Ǳ��ر���д���ݲ�ʣ����ΪǮ����ʼ�������е�Ԥ�ý��*/
	if(C_Meter_Type == C_L_SmartMeter)
	{/*�Ǳ��طѿر����ڳ���ģʽ���϶���Ǯ����ʼ��������ܵ����*/
	/*д���ݲ�ʣ����-��ֵ*/
        Flag = C_Money_Init;
		if( JudgeTimerExceed10min(&SI_JTimer_BSOn2500) != C_TimerEnable )
		{
		/*д���һ�ι����¼*/
		/*��ʼ��Ǯ��д�����¼�����й���ǰʣ����д��0*/
		/*������Ϊ����Ԥ�ý������ܽ��������壬*/
		/*��1�ι����������Ϊ0��*/
		/*���Կ��Բ�����1�μ�¼�й����ܽ��+���ι�����*/
			InF_WRPre1PowerPurchaseRecord(MoneyClient_Table.V_ulMoney, SV_Comm_Parse_Local.MeterClearFlag, Flag);
		}
		else
		{
			InF_MoneyToPurchase(MoneyClient_Table.V_ulMoney, Flag, SV_Comm_Parse_Local.MeterClearFlag);
		}
	}
}
/***************************************************************************
����ԭ�� 	Have_IPEvent_DemandClear
��������	ӵ�ж�������¼���Ŀ��������̣���ɶ�Ӧ�¼���¼�����ݲ��������㣩
�������	*pV_645Frame				:���յ���645֡	,��ʹ�õ����еĲ����ߴ���
������� 	��
���ز���	��
ȫ�ֱ��� 	��
������ע	��ȫ����2����ͨ��RecFlag����̰�ȫ�ֽ�
***************************************************************************/
void Have_IPEvent_DemandClear(Str_Comm_645 *pV_645Frame)
{
/*��ȫ�����ֽ��ж�*/
	if( SV_Comm_Parse_Local.RecFlag != C_CommRecFlagForInt_Ok )
	{
		return;
	}
	if( SV_Comm_Parse_Local.SafeControlFlag != C_W_SafeFlag )
	{
		return;
	}

/*����CDe_Clear_Note_1Ҫ�󣬶�ȡ���ݲ��Ӧ������*/
	Have_IPEvent_Prog_698(CDe_Clear_Note_1, CDe_Clear_Degree, pV_645Frame);
/*�������ݲ����㶯��	*/
	InF_Demand_Clear(C_Msg_Communication, SV_Comm_Parse_Local.SafeControlFlag);
}

/***************************************************************************
����ԭ�� 	Have_IPEvent_EventClear
��������	ӵ�ж�������¼���Ŀ����¼���¼�������
				����ɶ�Ӧ�¼���¼�����ݲ��¼���¼�����������)
�������	*pV_645Frame				:���յ���645֡	,��ʹ�õ����еĲ����ߴ���
������� 	��
���ز���	��
ȫ�ֱ��� 	��
������ע	��ȫ����2����ͨ��RecFlag����̰�ȫ�ֽ�
***************************************************************************/
void Have_IPEvent_EventClear(Str_Comm_645 *pV_645Frame, ulong32 V_ulOAD)
{
	uchar8	buf[C_Buf_MaxLen], i, k = 0;
	ulong32	MCE_Data_DI;							/*�¼���¼������Դ�ı�ʶ��*/
	ushort16	buf_O_CanWrite = 0, V_ucRelateoff;	/*��������д���ݵ�ƫ��*/
	ushort16	LenFor_Data = C_Buf_MaxLen;			/*�������ɱ�д���ܵĳ���*/

/*��ȫ�����ֽ��ж�*/
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
	if(Inf_GetRecordData( &buf[V_ucRelateoff], &LenFor_Data, CEven_Clear_OADTab, 0x01 ) == C_OK )	/*ȡ��������*/
	{
		buf_O_CanWrite += LenFor_Data;
	}
	InF_Write_Data(C_Msg_Communication, CEven_Clear_Note_1, buf, buf_O_CanWrite,(SV_Comm_Parse_Local.SafeControlFlag));

	LenFor_Data = C_Buf_MaxLen - V_ucRelateoff;
    buf_O_CanWrite = V_ucRelateoff;
	if(Inf_GetRecordData( &buf[V_ucRelateoff], &LenFor_Data, CEven_Clear_OADTab, 0x02 ) == C_OK )	/*ȡ��������*/
	{
		buf_O_CanWrite += LenFor_Data;
	}
	InF_Write_Data(C_Msg_Communication, CEven_Clear_Note_1 + 1, buf, buf_O_CanWrite, (SV_Comm_Parse_Local.SafeControlFlag));

/*�������ݲ㺯���������¼���¼����*/
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
����ԭ�� 	Comm_AppendMsg
��������	ͨ�Ų���һ����Ϣ��־
�������	MsgNum:			��Ϣ����

������� 	��
���ز���	��
ȫ�ֱ��� 	SV_Comm_Parse_Local
������ע
***************************************************************************/
void		Comm_AppendMsg(ulong32	MsgNum)
{
	uchar8	i;
	uchar8	OneNum = 0;
	ulong32	MsgNumBak = MsgNum;

/*�ж�MsgNum�Ƿ�Ϸ�*/
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
����ԭ�� 	Comm_FetchMsg
��������	ͨ�Ž�����Ϣȡ��һ����Ϣ
�������	��

������� 	��
���ز���	��Ϣ�š�����Ϣ����CMsg_Null
ȫ�ֱ��� 	SV_Comm_Parse_Local
������ע
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
����ԭ�� 	TimerExceed10min_Dec_IR
��������	Str_TimerExceed10min�ͱ������ж�ʱ���ۼ�
�������	*pTimerExceed10min��		������Ķ�ʱ��ֵ

������� 	��
���ز���	C_TimerEnable/C_TimerDisable
ȫ�ֱ��� 	Str_TimerExceed10min�ͱ���
������ע
***************************************************************************/
#define	C_BaseTimer_O		0
#define	C_Timer_O			1
#define	C_TimerCrc_O		5
uchar8	TimerExceed10min_Dec_IR( Str_TimerExceed10min *pTimerExceed10min )
{
	uchar8	V_ReturnData;
	uchar8	TimerExceed10min[C_StrTimerExceed10minLen];				/*��ʱ��ֵ�ݴ�*/
	ushort16	Crc;

/*���ݺϷ��Ե��ж�,���Ϸ���ʱ�����㲢�ҷ���C_TimerDisable*/
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
/*�ж϶�ʱ���Ƿ�Ϊ0��Ϊ0��ֱ�ӷ���C_TimerDisable*/
	if( pTimerExceed10min->Timer == 0 )
	{
		return(C_TimerDisable);
	}
/*��ʱ�����м�һ�ۼ�;����TimerExceed10min�����е����ݣ���󱣴浽pTimerExceed10min*/
	if( TimerExceed10min[C_BaseTimer_O] != 0 )
	{
		TimerExceed10min[C_BaseTimer_O]--;
	}
	if( TimerExceed10min[C_BaseTimer_O] == 0 )
	{
		if( pTimerExceed10min->Timer != 0 )
		{
			/*Timerδ��0�����������*/
			pTimerExceed10min->Timer = (pTimerExceed10min->Timer -1);		/*HEX��ʽ*/
			PF_Ulong32ToBuffer4(&TimerExceed10min[C_Timer_O], &(pTimerExceed10min->Timer), C_TimerExceed10minLen);
			if( pTimerExceed10min->Timer == 0 )
			{
				/*��ʱ������!*/
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
����ԭ�� 	TimerExceed10min_Dec
��������	Str_TimerExceed10min�ͱ������ж�ʱ���ۼ�
�������	*pTimerExceed10min��		������Ķ�ʱ��ֵ

������� 	��
���ز���	C_TimerEnable/C_TimerDisable
ȫ�ֱ��� 	Str_TimerExceed10min�ͱ���
������ע
***************************************************************************/
#define	C_BaseTimer_O		0
#define	C_Timer_O			1
#define	C_TimerCrc_O		5
uchar8	TimerExceed10min_Dec( Str_TimerExceed10min *pTimerExceed10min )
{
	uchar8	V_ReturnData;
	uchar8	TimerExceed10min[C_StrTimerExceed10minLen];				/*��ʱ��ֵ�ݴ�*/
	ushort16	Crc;
	uchar8	Dec2[C_TimerExceed10minLen];
	uchar8	Result[C_TimerExceed10minLen];

/*���ݺϷ��Ե��ж�,���Ϸ���ʱ�����㲢�ҷ���C_TimerDisable*/
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
/*�ж϶�ʱ���Ƿ�Ϊ0��Ϊ0��ֱ�ӷ���C_TimerDisable*/
	if( pTimerExceed10min->Timer == 0 )
	{
		return(C_TimerDisable);
	}

/*��ʱ�����м�һ�ۼ�;����TimerExceed10min�����е����ݣ���󱣴浽pTimerExceed10min*/
	if(TimerExceed10min[C_BaseTimer_O] != 0)
	{
		TimerExceed10min[C_BaseTimer_O]--;
	}
	if(TimerExceed10min[C_BaseTimer_O] == 0)
	{
		if( pTimerExceed10min->Timer != 0 )
		{
			/*Timerδ��0�����������*/
			memset(Dec2, 0, C_TimerExceed10minLen);
			Dec2[0] = 0x01;
			PF_BCDDECBytes(&TimerExceed10min[C_Timer_O], Dec2, Result, C_TimerExceed10minLen);
			PF_CopyDataBytes(Result, &TimerExceed10min[C_Timer_O], C_TimerExceed10minLen);
			PF_Buffer4ToUlong32(&TimerExceed10min[C_Timer_O], &(pTimerExceed10min->Timer), C_TimerExceed10minLen);
			if( pTimerExceed10min->Timer == 0)
			{
				/*��ʱ������!*/
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
����ԭ�� 	JudgeTimerExceed10min
��������	�ж�Str_TimerExceed10min�Ͷ�ʱ���Ƿ���Ч
�������	*pTimerExceed10min��������Ķ�ʱ��ֵ

������� 	��
���ز���	C_TimerEnable/C_TimerDisable
ȫ�ֱ��� 	Str_TimerExceed10min�ͱ���
������ע
***************************************************************************/
uchar8	JudgeTimerExceed10min( Str_TimerExceed10min *pTimerExceed10min )
{
	uchar8	V_ReturnData;
	uchar8	TimerExceed10min[C_StrTimerExceed10minLen];				/*��ʱ��ֵ�ݴ�*/

/*���ݺϷ��Ե��ж�,���Ϸ���ʱ�����㲢�ҷ���C_TimerDisable*/
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
/*�ж϶�ʱ���Ƿ�Ϊȫ0��Ϊȫ0���򷵻�C_TimerDisable*/
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
����ԭ�� 	SetTimerExceed10min
��������	���Str_TimerExceed10min�Ͷ�ʱ���ó�ֵ
�������	pTimerExceed10min:	��Ҫд�Ķ�ʱ����ַ��
				*pMinTimer:			�����ʱ�䣬����1min��5min(��IJ)
									pMinTimer��ʼ����2�ֽ����ݣ�����С��ģʽ
������� 	*pTimerExceed10min
���ز���	C_TimerEnable/C_TimerDisable
ȫ�ֱ��� 	Str_TimerExceed10min�ͱ���
������ע	20140504����:������IJ�����ʱ�䲻�ǻ��ڷ��ӣ����ǻ���5���ӡ�
***************************************************************************/
uchar8	SetTimerExceed10min( Str_TimerExceed10min *pTimerExceed10min, uchar8 *pVMinTimer )
{
	uchar8	ReturnDataCode;
	uchar8	TimerExceed10min[C_StrTimerExceed10minLen];				/*��ʱ��ֵ�ݴ�*/
	ushort16	Crc;

	PF_CopyDataBytes(pVMinTimer, &TimerExceed10min[C_Timer_O], C_TimerExceed10minLen);
	PF_Buffer4ToUlong32(&TimerExceed10min[C_Timer_O], &(pTimerExceed10min->Timer), C_TimerExceed10minLen);
	if( pTimerExceed10min->Timer == 0)
	{
		/*��ζ��ʱ��0*/
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
����ԭ�� 	DealWith_ID_Auth_Timer
��������	��������֤��ʱ�����úͿۼ������ݲ�ʣ��ʱ��ķ�д
				��
�������	Method			:��������
								:ȡֵC_Set_TimerExceed10min/ C_Dec_TimerExceed10min
				*pVTimer			:���ڻ�����ʱ����ʱ��2�ֽڣ�С�ˣ�����C_Set_TimerExceed10minʱ��Ч��
������� 	��
���ز���	��
ȫ�ֱ��� 	SV_Comm_Parse.ID_Authentication_Timer
������ע	�ۼ�ʱ�����ڻ�������500ms�ۼ�һ��
				����0���Ƕ������֤��ʱ����0��ʼ��
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
                    buf[0] = Pt_ResetEsam;			/*���͸�λ��Ϣ��ESAMģ��*/
                    Dispatch_SendMessage(C_Msg_Esam, buf, Pt_ResetEsam_Len + 1);
				}
			}
		}break;

		default:
			break;
	}
/*���������3*/
	DataLen = CLMeter_Work_State3;
	InF_Read_Data(CMeter_Work_State3, MeterRunState3, &DataLen, &V_usDataEncode);	/*����������*/
	MeterRunState3[CO_IDAuth] = MeterRunState3[CO_IDAuth] & (~CB_IDAuth);
	if( ( Com_Conect.ConectOverTime != 0 ) || ( ID_AuthT_Timer != 0 ) )
	{
		MeterRunState3[CO_IDAuth] = MeterRunState3[CO_IDAuth] | CB_IDAuth;
	}
	InF_Write_Data(C_Msg_Communication, CMeter_Work_State3, MeterRunState3, CLMeter_Work_State3, C_W_SafeFlag);

/*��д�����֤ʣ��ʱ��,645����Ϊ2�ֽڣ�ֱ��ȡ���ֽ�*/
	PF_Ulong32ToBuffer4(buf,&ID_AuthT_Timer,4);
	InF_Write_Data(C_Msg_Communication, CID_Auth_Remain_Time_645, buf, CLID_Auth_Remain_Time_645, C_W_SafeFlag);
	return;
}

/***************************************************************************
����ԭ�� 	DealWith_ID_AuthT_T_Timer
��������	��ɺ��ⰲȫ��֤ʱ����ʱ�������úͿۼ�
				������ݲ㷵д���������״̬��3��д����ʾ���ŵĴ���
�������	Method			:��������
								:ȡֵC_Set_TimerExceed10min/ C_Dec_TimerExceed10min
				*pVTimer			:���ڻ�����ʱ����ʱ��2�ֽڣ�С�ˣ�����C_Set_TimerExceed10minʱ��Ч��
������� 	��
���ز���	��
ȫ�ֱ��� 	SV_Comm_Parse.IR_Authentication_Timer.Timer
������ע	���ó�0�����ǳ�ʼ����0
				�ۼ�ʱ�����ڻ�������500ms�ۼ�һ��
				�������һ��ȱ�ݣ��������ʾģ���з����������������
				�ǲ������������Ϣ�������������úͿۼ���0�����Ϸ���Ϣ��
				����2014.05.05��Сţ��С��̸�����ȱ�ݡ�����:��ʾģ���Լ��㶨��
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
			/*���ö�ʱ�����������ý�����϶��ᴦ����ʾ����*/
			SetTimerExceed10min(&ID_AuthT_T, pVTimer);
			break;

		case	C_Dec_TimerExceed10min:
		{
			/*�������ݿۼ����ۼ���0�Ž�����ʾ���Ŵ���*/
			V_ReturnData = JudgeTimerExceed10min(&ID_AuthT_T);/*�洢hex��ʽ���ۼ�����BCD�ۼ�*/
			if( V_ReturnData == C_TimerEnable )
			{
				V_ReturnData = TimerExceed10min_Dec_IR(&ID_AuthT_T);
			}
		}break;

		default:
			break;
	}
/*��ȡ�������״̬��3����������֤λ����*/
	DataLen = CLMeter_Work_State3;
	InF_Read_Data(CMeter_Work_State3, MeterRunState3, &DataLen, &V_usDataEncode);	/*����������*/
	MeterRunState3[CO_IRAuth_T] = MeterRunState3[CO_IRAuth_T] & (~CB_IRAuth_T);
	if( ( ID_AuthT_T_Timer != 0 ) )
	{
		MeterRunState3[CO_IRAuth_T] = MeterRunState3[CO_IRAuth_T] | CB_IRAuth_T;
	}
	InF_Write_Data(C_Msg_Communication, CMeter_Work_State3, MeterRunState3, CLMeter_Work_State3, C_W_SafeFlag);
/*ˢ�����ݲ��Ӧ������֤ʣ��ʱ�� */
	PF_Ulong32ToBuffer4(buf, &ID_AuthT_T_Timer, 4);
	InF_Write_Data(C_Msg_Communication, CID_Auth_T_Remain_Time, buf, CLInfra_Auth_Remain_Time, C_W_SafeFlag);
	return;
}
/***************************************************************************
����ԭ�� 	DealWith_IR_Auth_Timer
��������	��ɺ��ⰲȫ��֤ʱ����ʱ�������úͿۼ�
				������ݲ㷵д���������״̬��3��д����ʾ���ŵĴ���
�������	Method			:��������
								:ȡֵC_Set_TimerExceed10min/ C_Dec_TimerExceed10min
				*pVTimer			:���ڻ�����ʱ����ʱ��2�ֽڣ�С�ˣ�����C_Set_TimerExceed10minʱ��Ч��
������� 	��
���ز���	��
ȫ�ֱ��� 	SV_Comm_Parse.IR_Authentication_Timer.Timer
������ע	���ó�0�����ǳ�ʼ����0
				�ۼ�ʱ�����ڻ�������500ms�ۼ�һ��
				�������һ��ȱ�ݣ��������ʾģ���з����������������
				�ǲ������������Ϣ�������������úͿۼ���0�����Ϸ���Ϣ��
				����2014.05.05��Сţ��С��̸�����ȱ�ݡ�����:��ʾģ���Լ��㶨��
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
/*���ö�ʱ�����������ý�����϶��ᴦ����ʾ����*/
			SetTimerExceed10min(&IR_AuthT, pVTimer);
			if( ( IR_AuthT_Timer == 0 )
			 && ( IR_AuthT_Timer_645 == 0 )
		 	 && ( JudgeTimerExceed10min(&ProgKey_Timer) == C_TimerDisable ) )			/*���õ�ֵΪ0*/
			{
				/*���������֤��ʾ������Ϣ*/
				Comm_SendMsgToDisp(C_ProgramEnableSign, C_NotDisplay, C_Duration_Alway);
			}
			else
			{
				/*���������֤��ʾ������Ϣ*/
				Comm_SendMsgToDisp(C_ProgramEnableSign, C_AlwaysDisplay, C_Duration_Alway);
			}
		}break;

		case	C_Dec_TimerExceed10min:
		{
			/*�������ݿۼ����ۼ���0�Ž�����ʾ���Ŵ���*/
			V_ReturnData = JudgeTimerExceed10min(&IR_AuthT);/*�洢hex��ʽ���ۼ�����BCD�ۼ�*/
			if( V_ReturnData == C_TimerEnable )
			{
				V_ReturnData = TimerExceed10min_Dec_IR(&IR_AuthT);
				if( ( V_ReturnData == C_TimerDisable )
				 && ( IR_AuthT_Timer_645 == 0 )
				 && ( JudgeTimerExceed10min(&ProgKey_Timer) == C_TimerDisable ) )
				{
					/*���������֤��ʾ������Ϣ*/
					Comm_SendMsgToDisp(C_ProgramEnableSign, C_NotDisplay,C_Duration_Alway);
				}
			}
		}break;

		default:
			break;
	}
/*��ȡ�������״̬��3����������֤λ����*/
	DataLen = CLMeter_Work_State3;
	InF_Read_Data(CMeter_Work_State3, MeterRunState3, &DataLen, &V_usDataEncode);	/*����������*/
	MeterRunState3[CO_IRAuth] = MeterRunState3[CO_IRAuth] & (~CB_IRAuth);
	if( ( IR_AuthT_Timer_645 != 0 ) || ( IR_AuthT_Timer != 0 )
	  ||( JudgeTimerExceed10min(&ProgKey_Timer) == C_TimerEnable ) )
	{
		MeterRunState3[CO_IRAuth] = MeterRunState3[CO_IRAuth] | CB_IRAuth;
	}
	InF_Write_Data(C_Msg_Communication, CMeter_Work_State3, MeterRunState3, CLMeter_Work_State3, C_W_SafeFlag);
/*ˢ�����ݲ��Ӧ������֤ʣ��ʱ��*/
	PF_Ulong32ToBuffer4(buf,&IR_AuthT_Timer,4);
	InF_Write_Data(C_Msg_Communication, CInfra_Auth_Remain_Time, buf, CLInfra_Auth_Remain_Time, C_W_SafeFlag);
	return;
}
/***************************************************************************
����ԭ�� 	DealWith_IR_Auth_Timer_645
��������	��ɺ��ⰲȫ��֤ʱ����ʱ�������úͿۼ�
				������ݲ㷵д���������״̬��3��д����ʾ���ŵĴ���
�������	Method			:��������
								:ȡֵC_Set_TimerExceed10min/ C_Dec_TimerExceed10min
				*pVTimer			:���ڻ�����ʱ����ʱ��2�ֽڣ�С�ˣ�����C_Set_TimerExceed10minʱ��Ч��
������� 	��
���ز���	��
ȫ�ֱ��� 	SV_Comm_Parse.IR_Authentication_Timer.Timer
������ע	���ó�0�����ǳ�ʼ����0
				�ۼ�ʱ�����ڻ�������500ms�ۼ�һ��
				�������һ��ȱ�ݣ��������ʾģ���з����������������
				�ǲ������������Ϣ�������������úͿۼ���0�����Ϸ���Ϣ��
				����2014.05.05��Сţ��С��̸�����ȱ�ݡ�����:��ʾģ���Լ��㶨��
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
			/*���ö�ʱ�����������ý�����϶��ᴦ����ʾ����*/
			SetTimerExceed10min(&IR_AuthT_645, pVTimer);
			if( ( IR_AuthT_Timer_645 == 0 )
			 && ( IR_AuthT_Timer == 0 )
			 && ( JudgeTimerExceed10min(&ProgKey_Timer) == C_TimerDisable ) )			/*���õ�ֵΪ0*/
			{
				/*���������֤��ʾ������Ϣ*/
				Comm_SendMsgToDisp(C_ProgramEnableSign, C_NotDisplay, C_Duration_Alway);
			}
			else
			{
				/*���������֤��ʾ������Ϣ*/
				Comm_SendMsgToDisp(C_ProgramEnableSign, C_AlwaysDisplay, C_Duration_Alway);
			}
		}break;

		case	C_Dec_TimerExceed10min:
		{
			/*�������ݿۼ����ۼ���0�Ž�����ʾ���Ŵ���*/
			V_ReturnData = JudgeTimerExceed10min(&IR_AuthT_645);/*�洢hex��ʽ���ۼ�����BCD�ۼ�*/
			if( V_ReturnData == C_TimerEnable )
			{
				V_ReturnData = TimerExceed10min_Dec_IR(&IR_AuthT_645);
				if( ( V_ReturnData == C_TimerDisable )
				 && ( IR_AuthT_Timer == 0 )
				 && ( JudgeTimerExceed10min(&ProgKey_Timer) == C_TimerDisable ) )
				{
					/*���������֤��ʾ������Ϣ*/
					Comm_SendMsgToDisp(C_ProgramEnableSign, C_NotDisplay, C_Duration_Alway);
				}
			}
		}break;

		default:
			break;
	}
/*��ȡ�������״̬��3����������֤λ����*/
	DataLen = CLMeter_Work_State3;
	InF_Read_Data(CMeter_Work_State3, MeterRunState3, &DataLen, &V_usDataEncode);	/*����������*/
	MeterRunState3[CO_IRAuth] = MeterRunState3[CO_IRAuth] & (~CB_IRAuth);
	if( ( IR_AuthT_Timer_645 != 0 )
	 || ( IR_AuthT_Timer != 0 )
     || ( JudgeTimerExceed10min(&ProgKey_Timer) == C_TimerEnable ) )
	{
		MeterRunState3[CO_IRAuth] = MeterRunState3[CO_IRAuth] |CB_IRAuth;
	}
	InF_Write_Data(C_Msg_Communication, CMeter_Work_State3, MeterRunState3, CLMeter_Work_State3, C_W_SafeFlag);
/*ˢ�����ݲ��Ӧ������֤ʣ��ʱ��*/
	PF_Ulong32ToBuffer4(buf, &IR_AuthT_Timer_645, 4);
	InF_Write_Data(C_Msg_Communication,CInfra_Auth_Remain_Time_645, buf, CLInfra_Auth_Remain_Time_645, C_W_SafeFlag);
	return;
}
/***************************************************************************
����ԭ�� 	DealWith_SI_J_Timer
��������	������IJ�����á��ۼ����ݲ㷵д����Ӧ������ʾ
�������	Method			:��������
								:ȡֵ
								C_Set_TimerExceed10min	:����
								C_Dec_TimerExceed10min	:��ʱ��-1
								C_Sub_TimerExceed10min	:��ʱ�����̶�ֵ
				*pVTimer			:���ڻ�����ʱ����ʱ��,2�ֽڣ�С�ˣ���
								:����ΪC_Set_TimerExceed10min/C_Sub_TimerExceed10minʱ��Ч
								:��λΪ5min��10������
������� 	��
���ز���	��
ȫ�ֱ��� 	SV_Comm_Parse.SI_JTimer_BSOn2_5s.Timer
������ע	�ۼ�ʱ�����ڻ�������2500ms�ۼ�һ��
				�������һ��ȱ�ݣ��������ʾģ���з����������������
				�ǲ������������Ϣ�������������úͿۼ���0�����Ϸ���Ϣ��
				����2014.05.05��Сţ��С��̸�����ȱ�ݡ�����:��ʾģ���Լ��㶨��
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
			if(SI_JT_Timer == 0)			/*���õ�ֵΪ0*/
			{/*����ʾ��������Ϣ*/
				Comm_SendMsgToDisp(C_AxisSign, C_AlwaysDisplay, C_Duration_Alway);
			}
			else
			{/*����������˸��Ϣ*/
				Comm_SendMsgToDisp(C_AxisSign, C_TwinkleDisplay, C_Duration_Alway);
			}
		}break;
		case	C_Set_TimerExceed10min:
		{
			/*���õĻ����Ƚ�������������*/
			SI_JBaseTimer_2500 = 0;
			/*���ö�ʱ�����������ý�����϶��ᴦ����ʾ����*/
			SetTimerExceed10min(&SI_JTimer_BSOn2500, pVTimer);
			if(SI_JT_Timer == 0)			/*���õ�ֵΪ0*/
			{
				/*����ʾ��������Ϣ*/
				Comm_SendMsgToDisp(C_AxisSign, C_AlwaysDisplay, C_Duration_Alway);
			}
			else
			{
				/*����������˸��Ϣ*/
				Comm_SendMsgToDisp(C_AxisSign, C_TwinkleDisplay, C_Duration_Alway);
			}
		}break;
		case		C_Dec_TimerExceed10min:
		{
			/*�������ݿۼ����ۼ���0�Ž�����ʾ���Ŵ���*/
			V_ReturnData = JudgeTimerExceed10min(&SI_JTimer_BSOn2500);
			if(V_ReturnData == C_TimerEnable)
			{
				V_ReturnData = TimerExceed10min_Dec(&SI_JTimer_BSOn2500);
				if(V_ReturnData == C_TimerDisable)
				{
					/*����ʾ��������Ϣ*/
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
����ԭ�� 	InF_IsInFactoryState
��������	����ͨ��ģ����ã��ж��Ƿ��ڳ���״̬
�������	��
������� 	��
���ز���	C_OK			:�ڳ���״̬
				C_Error			:���ڳ���״̬
ȫ�ֱ��� 	��
������ע	��
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
����ԭ�� 	Comm_DealwithSPTVariable
��������	������ܱ����ȫ�־�̬����SV_Comm_Parse.SPT Variable
				��������ʵ������
�������	method�߰��ֽ�:�ܼ�,=C_Key02Flag,��ʾΪ02��
								=C_Key04Flag,��ʾΪ04��
								=C_SPTFlag,��ʾΪmac�����
			method�Ͱ��ֽ�:������
							=C_SPTNumAdd������������ӵķ���
							=C_JudgeSPTVariable���ж�200���Ƿ񵽷���
							=C_InitSPTVariable����ʼ������.ע�������ʼ������Ϊ
											�����д�����0�����Ǹ���CRC��ʱ���ۺ��ж�
											��Judge������ͬ���ǣ��϶��ᶯ������������
							=C_KeyErrNumAdd������������+
							=C_JudgeKeyErr�������������ж�
							=C_ClrKeyErrNum	�������������㣬��Ϊ�������������������������
�������˵������Ϊһ��ʼ02��04����������Ǻ�Ϊһ���������ݡ��ӣ��жϺͳ�ʼ��������Ϊ3*2.����0204�ֿ���
			method�߰��ֽ�:�ܼ�,=C_Key02Flag,C_Key04Flag��ʹ��C_KeyErrNumAdd��C_JudgeKeyErr��C_ClrKeyErrNum
							    =C_SPTFlag��ʹ��C_SPTNumAdd��C_JudgeSPTVariable��C_InitSPTVariable
������� 	SV_Comm_Parse. SPT Variable
���ز���	Ok��C_SPT_Num_Over����ȫ��������C_KeyErr_Num_Over(������������)
ȫ�ֱ���
������ע	����ʱ�Ӷ���������Ϊ��ʱ�ӷǷ�������û�н���ʱ�ӺϷ����жϡ�
***************************************************************************/
#define	Key02_ErrNum_O		0
#define	Key04_ErrNum_O		1
#define	SPTNum_O			2
#define	SPTRecentClock_O	3		/*ʱ����*/
#define	SPTRecentDate_O		3		/*��SPTRecentClock_O+SPTRecentDate_O��Ϊ��������ʼƫ�ƣ���������3�̶����䡣*/
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

/*****************���ݸ߰��ֽ��ж��ܼ�************************/
	if( ( method & 0xF0 ) == C_Key02Flag )	/*02������ƫ��*/
	{
		Key0204_ErrNum_O = Key02_ErrNum_O;
	}
	else
	{/*����ȥ04������ƫ��,���Ϊmac�������Ļ����ƫ��Ϊ04�������Ҳû������,��mode��ʽ���Ʋ��ᴦ��04���������*/
		Key0204_ErrNum_O = Key04_ErrNum_O;
	}
	method &= 0x0F;
/*�ж�SPT CRC�Ƿ���ȷ������ȷ��ʼ����������C_OK*/
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
/*����method��������ش���*/
	switch(method)
		{
			case		C_KeyErrNumAdd:
			{
				if(buf[Key0204_ErrNum_O]>=C_Key0204_ErrThreshold)
				{/*��������*/
					ReturnCode = C_KeyErr_Num_Over;
				}
				else
				{
					buf[Key0204_ErrNum_O]++;
					DataLen = CLDate_Time;
					V_ReturnData = InF_Read_Data(CDate_Time, &buf[SPTRecentClock_O], &DataLen, &V_usDataEncode);
					if( buf[Key0204_ErrNum_O] >= C_Key0204_ErrThreshold )
					{/*��1����3�ε�������!*/
						ReturnCode = C_KeyErr_Num_Over;	/*�������ǲ���Ҫ�ж�SPT��*/
						Comm_SendMsgToDisp(C_HoldUpSign, C_AlwaysDisplay, C_Duration_Alway);
					}
				}
				break;
			}
			case		C_SPTNumAdd:
			{/*����++*/
				if(buf[SPTNum_O] >= C_SPTNum_Threshold)
				{/*��������*/
					ReturnCode = C_SPT_Num_Over;
				}
				else
				{
					buf[SPTNum_O]++;
					DataLen = CLDate_Time;
					V_ReturnData = InF_Read_Data(CDate_Time, &buf[SPTRecentClock_O], &DataLen, &V_usDataEncode);
					if( buf[SPTNum_O] >= C_SPTNum_Threshold )
					{/*��1����200�ε�������!*/
						ReturnCode = C_SPT_Num_Over;
						Comm_SendMsgToDisp(C_HoldUpSign, C_AlwaysDisplay, C_Duration_Alway);
					}
				}
				break;
			}
			case		C_JudgeSPTVariable:
			case		C_JudgeKeyErr:
			{/*�ж�SPT��û�������*/
				if( Is_Buf_AllZero(buf, ( CLen_Str_SPT - 2 ) ) == C_OK )
				{	/*������ʱ�䶼Ϊ0������Ҫ��������Ϣ��ֱ���˳���*/
					break;
				}
				DataLen = CLDate_Time;
				V_ReturnData = InF_Read_Data(CDate_Time, Clock, &DataLen, &V_usDataEncode);
				if( ( Clock[SPTRecentDate_O] != buf[SPTRecentClock_O + SPTRecentDate_O] )
				 || ( Clock[SPTRecentDate_O + 1] != buf[SPTRecentClock_O + SPTRecentDate_O + 1] )
				 ||	( Clock[SPTRecentDate_O + 2] != buf[SPTRecentClock_O + SPTRecentDate_O + 2] ) )
				{	/*���ڲ��ȣ����ɽ�����0��������������ȫ������*/
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
			{	/*������Judge������ͬ���ǣ�������ô˵���ᷢ������Ϣ*/
				if( Is_Buf_AllZero(buf,( CLen_Str_SPT - 2 ) ) == C_OK )
				{	/*������ʱ�䶼Ϊ0����������Ϣ��ֱ���˳���*/
					Comm_SendMsgToDisp(C_HoldUpSign, C_NotDisplay, C_Duration_Alway);
					break;
				}
				DataLen = CLDate_Time;
				V_ReturnData = InF_Read_Data(CDate_Time, Clock, &DataLen, &V_usDataEncode);
				if(V_ReturnData != C_OK)
				{	/*������ʱ��,������0?*/
					buf[SPTNum_O] = 0;
					buf[Key02_ErrNum_O] = 0;
					buf[Key04_ErrNum_O] = 0;
					Comm_SendMsgToDisp(C_HoldUpSign, C_NotDisplay, C_Duration_Alway);
					break;
				}
				if( ( Clock[SPTRecentDate_O] != buf[SPTRecentClock_O + SPTRecentDate_O] )
				 || ( Clock[SPTRecentDate_O + 1] != buf[SPTRecentClock_O + SPTRecentDate_O + 1] )
				 || ( Clock[SPTRecentDate_O + 2] != buf[SPTRecentClock_O + SPTRecentDate_O + 2] ) )
				{	/*���ڲ��ȣ����ɽ�����0������*/
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
			{/*����������㷽��.����ǰ���������������,SPT����������*/
			/*�򱾴����㣬�跢������Ϣ�����򲻹�������Ϣ*/
				if( ( buf[SPTNum_O] < C_SPTNum_Threshold ) && ( buf[Key0204_ErrNum_O] >= C_Key0204_ErrThreshold ) )
				{
					Comm_SendMsgToDisp(C_HoldUpSign, C_NotDisplay, C_Duration_Alway);
				}
				DataLen = CLDate_Time;
				V_ReturnData = InF_Read_Data(CDate_Time, &buf[SPTRecentClock_O], &DataLen, &V_usDataEncode);
				buf[Key0204_ErrNum_O] = 0;
				break;
			}
			default:			/*��ڲ�����ɶҲ����ֱ�ӷ���OK*/
				return(ReturnCode);
		}
/*��дȫ��SPT��������CRC*/
	KEY02ErrNum = buf[Key02_ErrNum_O];
	KEY04ErrNum = buf[Key04_ErrNum_O];
	SPTNum = buf[SPTNum_O];
	PF_CopyDataBytes(&buf[SPTRecentClock_O], SPTRecentClock, CLDate_Time);
	SPTCrc = PF_Cal_CRC(buf,(CLen_Str_SPT - 2));
	return(ReturnCode);
}
/***************************************************************************
����ԭ�� 	Is_Buf_AllZero
��������	�жϻ����������Ƿ�Ϊȫ0
�������	pData		�������׵�ַ
				DataLen		���ݳ���
������� 	��
���ز���	C_OK		����ȫ����0
				C_Error		�����в�ȫ����0����ڲ�������
ȫ�ֱ��� 	��
������ע
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
����ԭ�� 	Comm_SendMsg
��������	ͨ�ŷ�����Ϣ������ģ��
�������	*pParm			:��Ϣ�еĲ�����
				ParmLen			:�����򳤶�,ע��������Ȱ���PT
������� 	��
���ز���	��
ȫ�ֱ��� 	���ȵ���Ϣ����
������ע
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
����ԭ�� 	Comm_SendMsgForUpdataParm
��������	���Ͳ���������Ϣ
�������	ParmType			:���µĲ������͡�
					ȡֵ		:  C_ReWorkTime			ʱ�����
							        : C_ReDemand_Cycle		�������ڸ���
							        : C_ReMultiRatesParm		ʱ�η��ʵȲ����޸�
							        : C_ReSettle_Day1			��1�������޸�
������� 	��
���ز���	��
ȫ�ֱ��� 	���ȵ���Ϣ����
������ע
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
����ԭ�� 	Comm_SendMsgToDisp
��������	��ɷ���Ϣ����ʾģ�鴦��һ���ַ���
�������	DispSign				:�����ַ�����
				DispMode				:����ʽC_TwinkleDisplay/C_AlwaysDisplay/C_NotDisplay
				Duration				:����ʱ��C_Duration_Alway��ʾһֱ������
������� 	��
���ز���	��
ȫ�ֱ��� 	��
������ע
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
����ԭ�� 	Init_SV_CommNxtFrame
��������	��ʼ��ȫ�־�̬����SV_CommNxtFrame_XX��ʵ�ʾ��Ƿ�װ��ͨ�����жϡ�
�������	CommNo					:ͨ����

������� 	��
���ز���	��
ȫ�ֱ��� 	SV_CommNxtFrame_XX
������ע
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
����ԭ�� 	Set_SV_CommNxtFrame
��������	���ú���֡ͨ������
�������	CommNo				:ͨ����
				*pStr_Comm_NxtFrame	:׼��д��ֵ
������� 	��
���ز���	��
ȫ�ֱ��� 	SV_CommNxtFrame_XX
������ע
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
����ԭ�� 	Get_SV_CommNxtFrame
��������	��ȡͨ��SV_CommNxtFrameֵ��ʵ�ʾ��Ƿ�װ��ͨ�����жϡ�
�������	CommNo				:ͨ����
				pNxtFrame			:��д��Str_Comm_NxtFrameָ��
������� 	*pNxtFrame			:ֵ
���ز���	C_OK/C_Error
ȫ�ֱ��� 	��
������ע
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
����ԭ�� 	Comm_A_MsgToDispatchQueue_UpKeyR
��������	������Կ���¼����Ϣ�����ȶ���
�������	PT_Type				:PT_CMsg_UpdataKey_Review/PT_CMsg_UpdKey_Rv_PWOn

������� 	��
���ز���	��
ȫ�ֱ��� 	���ȶ���
������ע
***************************************************************************/
void		Comm_A_MsgToDispatchQueue_UpKeyR(uchar8 PT_Type)
{
	uchar8	pParm[2];

	pParm[0] = PT_Type;
	Comm_SendMsg(pParm, (PT_CMsg_UpdataKey_Review_Len + 1), C_Msg_Communication);
}
/***************************************************************************
����ԭ�� 	Get_Str_Comm_Parm_Pointer
��������	����ͨ���ţ�����Str_Comm_Parm��ָ��ֵ
�������	CommNo��				ͨ����


�������
���ز���	���Str_Comm_Parmָ��ֵ�����ͨ���Ŵ�����C_NULL
ȫ�ֱ���
������ע
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
����ԭ�� 	Init_Str_Comm_Parm
��������	���Str_Comm_Parm�ͱ����ĳ�ʼ��
�������	CommNo:		ͨ����

������� 	��
���ز���	��
ȫ�ֱ��� 	Str_Comm_Parm�ͱ���
������ע
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
����ԭ�� 	Comm_ParseInit
��������	���Comm_Parseģ���ʼ��
�������	��

������� 	��
���ز���	��
ȫ�ֱ��� 	SV_Comm_Parse_Local
������ע
����ʱ��	1��Comm_Parse������һ��ȥ���ȳ�ʼ����
				2����ʱ��Ϣ�У�ÿ�ζ����ó�ʼ��
				3���ϵ��ʼ�������С�Comm_ForPowerOn
				4����ע������ǲ����ñ�������
				5��SV_Comm_Parse����ԭ���������ʼ��������
					����CRC��ȡ�¼�CRC��ʹ��ʱ�жϣ���������
					����ʼ���ˡ����ϵ��ʼ�������г�ʼ����
***************************************************************************/
void Comm_ParseInit(void)
{
	SV_Comm_Parse_Local.MessageFlag = 0;
	SV_Comm_Parse_Local.MeterClearFlag = 0;
	SV_Comm_Parse_Local.SafeControlFlag = 0;
	SV_Comm_Parse_Local.ClientAddrFlag = 0;/*�����ն�����ս�ͻ�����ַ������*/
}

/***************************************************************************
����ԭ�� 	uchar8 SF_BPS698transfor645(uchar8 bps698)
��������	������ת��
�������	698������������

������� 	645�Ĳ�����������
���ز���	��
ȫ�ֱ��� 	Str_Comm_Parm��ȫ�ֱ���
������ע
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
����ԭ�� 	uchar8 SF_BPS698transfor645(uchar8 bps698)
��������	������ת��
�������	698������������

������� 	645�Ĳ�����������
���ز���	��
ȫ�ֱ��� 	Str_Comm_Parm��ȫ�ֱ���
������ע
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
����ԭ�� 	InF_InitComm
��������	��ʼ��Ӳ�����ڼ��ô��ڶ�Ӧ��ͨ��ȫ�ֱ���
�������	CommNum:	���ڱ��

������� 	��
���ز���	��
ȫ�ֱ��� 	Str_Comm_Parm��ȫ�ֱ���
������ע
***************************************************************************/
void InF_InitComm(uchar8 CommNo)
{
	ulong32	bpsDataCode;
	uchar8	V_ReturnData;
	uchar8	bps;
	uchar8	bpsDefault;
    uchar8  CommDataLen, StpLen, parityChk, bpsData[5];
	ushort16  DataLen, V_usDataEncode;

/*��ʼ��Ӳ������*/
/*ȡ���ڲ�����*/
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

/*��ʼ��ͨ����������*/
	Init_Str_Comm_Parm(CommNo);
}

/***************************************************************************
����ԭ�� 	Comm_WR_TxData_ToCtrbyte
��������	���дͨѶ������4��FE�������֡�
�������	pStr_Comm_Parm_Address		:�������ͨ�Ż�����
������� 	Rx_CtrByte					:���յ��Ŀ�����
���ز���	��
ȫ�ֱ��� 	Str_Comm_Parm�ͱ���
������ע	����΢RTC��У��645��ʽ�����⴦��
***************************************************************************/
void		Comm_WR_TxData_ToCtrbyte1(Str_Comm_Parm *pStr_Comm_Parm_Address, uchar8 Rx_CtrByte)
{
	ushort16	i, V_usDataEncode;

	CommLen645 = 0;
/*��ֵ4��FE*/
	CommBuff[C_FE_OFS_ForTx] = 0xFE;
	CommLen645 ++;
	CommBuff[C_FE_OFS_ForTx + 1] = 0xFE;
	CommLen645 ++;
	CommBuff[C_FE_OFS_ForTx + 2] = 0xFE;
	CommLen645 ++;
	CommBuff[C_FE_OFS_ForTx + 3] = 0xFE;
	CommLen645 ++;

/*��ֵ��1��0x68*/
	CommBuff[C_68_1_OFS_ForTx] = 0x68;
	CommLen645 ++;
/*ȡͨ�ŵ�ַ*/
	for( i = 0; i < CLComm_Address; i++ )
	{
		CommBuff[C_CAddr_OFS_ForTx + i] = 0;
	}

	InF_Read_Data(CComm_Address, &CommBuff[C_CAddr_OFS_ForTx], &i, &V_usDataEncode);
	CommLen645 = CommLen645 + i;
/*��ֵ��2��0x68*/
	CommBuff[C_68_2_OFS_ForTx] = 0x68;
	CommLen645 ++;
/*��ֵC*/
	CommBuff[C_C_OFS_ForTx] = Rx_CtrByte;
	CommLen645 ++;
	return;
}
/***************************************************************************
����ԭ�� 	Comm_WR_TxData_ToCtrbyte
��������	���дͨѶ������4��FE�������֡�
�������	pStr_Comm_Parm_Address		:�������ͨ�Ż�����
������� 	Rx_CtrByte					:���յ��Ŀ�����
���ز���	��
ȫ�ֱ��� 	Str_Comm_Parm�ͱ���
������ע	1���������ֻ����ԭֵ����0x80.Ӧ��
				2���ܵ�Lenͬ����ֵ
				2���÷��ͺ�������һ���÷��ͺ�������
***************************************************************************/
void		Comm_WR_TxData_ToCtrbyte(Str_Comm_Parm *pStr_Comm_Parm_Address, uchar8 Rx_CtrByte)
{
	ushort16	i, V_usDataEncode;

	CommLen645 = 0;
/*��ֵ4��FE*/
	CommBuff[C_FE_OFS_ForTx] = 0xFE;
	CommLen645 ++;
	CommBuff[C_FE_OFS_ForTx + 1] = 0xFE;
	CommLen645 ++;
	CommBuff[C_FE_OFS_ForTx + 2] = 0xFE;
	CommLen645 ++;
	CommBuff[C_FE_OFS_ForTx + 3] = 0xFE;
	CommLen645 ++;

/*��ֵ��1��0x68*/
	CommBuff[C_68_1_OFS_ForTx] = 0x68;
	CommLen645 ++;
/*ȡͨ�ŵ�ַ*/
	for(i = 0; i < CLComm_Address; i++ )
	{
		CommBuff[C_CAddr_OFS_ForTx + i] = 0;
	}
	InF_Read_Data(CComm_Address, &CommBuff[C_CAddr_OFS_ForTx], &i, &V_usDataEncode);
	CommLen645 = CommLen645 + i;
/*��ֵ��2��0x68*/
	CommBuff[C_68_2_OFS_ForTx] = 0x68;
	CommLen645 ++;
/*��ֵC*/
	CommBuff[C_C_OFS_ForTx] = Rx_CtrByte | 0x80;
	CommLen645 ++;
	return;
}

/***************************************************************************
����ԭ�� 	Comm_Response_Set_ReadErr
��������	���Set(write(14)����Action����������)��Ӧ�𼰶�ȡ�Ĵ���Ӧ��
				ֱ����Str_Comm_Parm��ȫ�ֱ�����
�������	Err				:ͨѶ�������ͣ�=C_Ok��ʾ��ȷӦ��
				*pV_645Frame		:���յ��ѽ�����645֡
������� 	��
���ز���	��
ȫ�ֱ���	Str_Comm_Parm�ͱ���
������ע	������Ϊֹ������Ӧ��֡�е����ݣ���CS��16�ⶼ�Ѿ��úá�����645Len
				1���÷��ͺ�����CS��16����(��2���ڷ�����Ϣ����ʱ��)������������Ϣ��־�����á�
***************************************************************************/
void		Comm_Response_Set_ReadErr(uchar8  Err, Str_Comm_645 *pV_645Frame)
{
	Str_Comm_Parm *pStr_Comm_Parm_Address;

	pStr_Comm_Parm_Address = Get_Str_Comm_Parm_Pointer(pV_645Frame->ChannelNo);
	if(pStr_Comm_Parm_Address == C_NULL)
	{
		return;		/*ͨ������ʵ�ʲ����ܡ������ˣ�Ҳ�����ͣ�ֱ���˳���*/
	}

	Comm_WR_TxData_ToCtrbyte(pStr_Comm_Parm_Address, (pV_645Frame->C));

	if(Err == C_OK)
	{
		/*������ȷFE FE FE FE 68 A0-A5 68 (C|0x80) 00 */
		CommBuff[C_L_OFS_ForTx] = 0;		/*����Ϊ0	*/
		CommLen645 ++;
	}
	else
	{
		CommBuff[C_C_OFS_ForTx] = CommBuff[C_C_OFS_ForTx] | 0x40;
		CommBuff[C_L_OFS_ForTx] = 1;		/*����Ϊ1*/
		CommLen645 ++;
		CommBuff[C_Data_OFS_ForTx] =  Err;
		CommLen645 ++;
	}

	Comm_AppendMsg(CMsg_Txd);
	return;
}

/***************************************************************************
����ԭ�� 	Comm_Response_03_Err
��������	���03 ��������Ĵ���Ӧ��
				ֱ����Str_Comm_Parm��ȫ�ֱ�����
�������	Err				:ͨѶ�������ͣ�
				*pV_645Frame		:���յ��ѽ�����645֡
������� 	��
���ز���	��
ȫ�ֱ���	Str_Comm_Parm�ͱ���
������ע	������Ϊֹ������Ӧ��֡�е����ݣ���CS��16�ⶼ�Ѿ��úá�����645Len
				1���÷��ͺ�����CS��16����(��2���ڷ�����Ϣ����ʱ��)������������Ϣ��־�����á�
***************************************************************************/
void		Comm_Response_03_Err(ushort16  SERR, Str_Comm_645 *pV_645Frame)
{
	Str_Comm_Parm *pStr_Comm_Parm_Address;

	pStr_Comm_Parm_Address = Get_Str_Comm_Parm_Pointer(pV_645Frame->ChannelNo);
	if(pStr_Comm_Parm_Address == C_NULL)
	{
		return;		/*ͨ������ʵ�ʲ����ܡ������ˣ�Ҳ�����ͣ�ֱ���˳���*/
	}

	Comm_WR_TxData_ToCtrbyte(pStr_Comm_Parm_Address, (pV_645Frame->C));

	CommBuff[C_C_OFS_ForTx] = CommBuff[C_C_OFS_ForTx] | 0x40;	/*�����ֻ��ϴ����־*/

	CommBuff[C_L_OFS_ForTx] = 2;		/*����Ϊ2*/
	CommLen645 ++;
	PF_Ushort16ToBuffer2(&CommBuff[C_Data_OFS_ForTx] , &SERR);
	CommLen645 ++;
	CommLen645 ++;
	Comm_AppendMsg(CMsg_Txd);
	return;
}
/***************************************************************************
����ԭ�� 	Comm_RTC1E_Response_Normal(Str_Comm_645 *pV_645Frame,uchar8	*pData,uchar8 DataLen)
��������	����΢RTC 1E�����������645��ʽӦ��֡��(��CS��16����������)
�������	*pV_645Frame		:���յ��ѽ�����645֡
				pData:			:����Ӧ��DI������� �׵�ַ
				DataLen			:pData���ݳ���
������� 	��
���ز���	��
ȫ�ֱ���	Str_Comm_Parm�ͱ���
������ע	������Ϊֹ������Ӧ��֡�е����ݣ���CS��16�ⶼ�Ѿ��úá�����645Len
				1���÷��ͺ�����CS��16����(��2���ڷ�����Ϣ����ʱ��)������������Ϣ��־�����á�
***************************************************************************/
void		Comm_RTC1E_Response_Normal(Str_Comm_645 *pV_645Frame, uchar8	*pData, uchar8 DataLen)
{
	uchar8	i;
	Str_Comm_Parm *pStr_Comm_Parm_Address;

	pStr_Comm_Parm_Address = Get_Str_Comm_Parm_Pointer(pV_645Frame->ChannelNo);
	if(pStr_Comm_Parm_Address ==C_NULL)
	{
		return;		/*ͨ������ʵ�ʲ����ܡ������ˣ�Ҳ�����ͣ�ֱ���˳���*/
	}
/*FE->C*/
	Comm_WR_TxData_ToCtrbyte1(pStr_Comm_Parm_Address, (pV_645Frame->C));
/*L*/
	CommBuff[C_L_OFS_ForTx] = 4 + DataLen;		/*����Ӧ������Ϊ4�ֽڣ�DI*/
	CommLen645 ++;
/*DI  ������-0x33������΢��645��ʽ*/
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
����ԭ�� 	Comm_11_03Response_Normal
��������	����΢RTC 1Fʱ�ӵ�У�����645��ʽӦ��֡��(��CS��16����������)
�������	*pV_645Frame		:���յ��ѽ�����645֡
				pData:			:����Ӧ��DI������� �׵�ַ
				DataLen			:pData���ݳ���
������� 	��
���ز���	��
ȫ�ֱ���	Str_Comm_Parm�ͱ���
������ע	������Ϊֹ������Ӧ��֡�е����ݣ���CS��16�ⶼ�Ѿ��úá�����645Len
				1���÷��ͺ�����CS��16����(��2���ڷ�����Ϣ����ʱ��)������������Ϣ��־�����á�
***************************************************************************/
void		Comm_RTC1F_Response_Normal(Str_Comm_645 *pV_645Frame, uchar8	*pData, uchar8 DataLen)
{
	uchar8	i;
	Str_Comm_Parm *pStr_Comm_Parm_Address;

	pStr_Comm_Parm_Address = Get_Str_Comm_Parm_Pointer(pV_645Frame->ChannelNo);
	if(pStr_Comm_Parm_Address ==C_NULL)
	{
		return;		/*ͨ������ʵ�ʲ����ܡ������ˣ�Ҳ�����ͣ�ֱ���˳���*/
	}
/*FE->C*/
	Comm_WR_TxData_ToCtrbyte(pStr_Comm_Parm_Address, (pV_645Frame->C));
/*L*/
	CommBuff[C_L_OFS_ForTx] = DataLen;		/*���ݳ����Ѱ���DI*/
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
����ԭ�� 	Comm_11_03Response_Normal
��������	���03/11��������Ӧ��֡��֡��(��CS��16����������)
�������	*pV_645Frame		:���յ��ѽ�����645֡
				pData:			:����Ӧ��DI������� �׵�ַ
				DataLen			:pData���ݳ���
������� 	��
���ز���	��
ȫ�ֱ���	Str_Comm_Parm�ͱ���
������ע	������Ϊֹ������Ӧ��֡�е����ݣ���CS��16�ⶼ�Ѿ��úá�����645Len
				1���÷��ͺ�����CS��16����(��2���ڷ�����Ϣ����ʱ��)������������Ϣ��־�����á�
***************************************************************************/
void		Comm_11_03Response_Normal(Str_Comm_645 *pV_645Frame, uchar8	*pData, uchar8 DataLen)
{
	uchar8	i;
	Str_Comm_Parm *pStr_Comm_Parm_Address;

	pStr_Comm_Parm_Address = Get_Str_Comm_Parm_Pointer(pV_645Frame->ChannelNo);
	if(pStr_Comm_Parm_Address ==C_NULL)
	{
		return;		/*ͨ������ʵ�ʲ����ܡ������ˣ�Ҳ�����ͣ�ֱ���˳���*/
	}
/*FE->C*/
	Comm_WR_TxData_ToCtrbyte(pStr_Comm_Parm_Address, (pV_645Frame->C));
/*L*/
	CommBuff[C_L_OFS_ForTx] = 4 + DataLen;		/*����Ӧ������Ϊ4�ֽڣ�DI*/
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
����ԭ�� 	Comm_Response_FromP_Normal
��������	��ɴ�ָ��ָ�뿪ʼ���ݵ�Ӧ��(��CS��16����������)
				��Comm_11_03Response_Normal�ȣ����˸�DI��ֵ
�������	*pV_645Frame		:���յ��ѽ�����645֡
				pData:			:L��һ���ֽ������׵�ַ
				DataLen			:pData���ݳ���
������� 	��
���ز���	��
ȫ�ֱ���	Str_Comm_Parm�ͱ���
������ע	������Ϊֹ������Ӧ��֡�е����ݣ���CS��16�ⶼ�Ѿ��úá�����645Len
				1���÷��ͺ�����CS��16����(��2���ڷ�����Ϣ����ʱ��)������������Ϣ��־�����á�
***************************************************************************/
void		Comm_Response_FromP_Normal(Str_Comm_645 * pV_645Frame, uchar8	*pData, uchar8 DataLen)
{
	uchar8	i;
	Str_Comm_Parm *pStr_Comm_Parm_Address;

	pStr_Comm_Parm_Address = Get_Str_Comm_Parm_Pointer(pV_645Frame->ChannelNo);
	if(pStr_Comm_Parm_Address == C_NULL)
	{
		return;		/*ͨ������ʵ�ʲ����ܡ������ˣ�Ҳ�����ͣ�ֱ���˳���*/
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
����ԭ�� 	Comm_IfHaveNxtFrame_Set_C
��������	�ж��к���֡ʱ�����ã���ͨ�ŷ��ͻ�������C�к���֡
�������	pV_645Frame					:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	��Ӧ��ͨ�ŷ��ͻ�������C
������ע	1�����޺���֡�������ж�
				2��ͨ�Ż������д�����FE-C�Ѿ��úá�
***************************************************************************/
void		Comm_IfHaveNxtFrame_Set_C(Str_Comm_645 *pV_645Frame)
{
	Str_Comm_Parm *pStr_Comm_Parm_Address;

	pStr_Comm_Parm_Address = Get_Str_Comm_Parm_Pointer(pV_645Frame->ChannelNo);
	if(pStr_Comm_Parm_Address ==C_NULL)
	{
		return;														/*ͨ������ʵ�ʲ����ܡ������ˣ�Ҳ�����ͣ�ֱ���˳���*/
	}
	if( ( CommBuff[C_C_OFS_ForTx] & 0x40 ) == 0x00 )				/*��ȷӦ�������²Ž���������־ֵ1*/
	{
		CommBuff[C_C_OFS_ForTx] = CommBuff[C_C_OFS_ForTx] | 0x20;	/*bit5���к���֡��־*/
	}
}

/***************************************************************************
����ԭ�� 	Comm_SetFrameNo
��������	��֡β���֡���
�������	CommNo						:ͨ��������
				FrameNo						:֡���
������� 	��
���ز���	��
ȫ�ֱ��� 	��Ӧ��ͨ�ŷ��ͻ�����
������ע
***************************************************************************/
void	Comm_SetFrameNo(uchar8	CommNo,uchar8	FrameNo)
{
	Str_Comm_Parm *pStr_Comm_Parm_Address;

	pStr_Comm_Parm_Address = Get_Str_Comm_Parm_Pointer(CommNo);
	if(pStr_Comm_Parm_Address ==C_NULL)
	{
		return;								/*ͨ������ʵ�ʲ����ܡ������ˣ�Ҳ�����ͣ�ֱ���˳���*/
	}
	if( CommLen645 > ( C_Comm_Buf_MaxLen - 3 ) )
	{
		return;								/*���������*/
	}
	CommBuff[CommLen645] = FrameNo;
	CommLen645++;							/*�ܳ��ȵ���*/
	CommBuff[C_L_OFS_ForTx]++;				/*�����򳤶ȵ���*/
}

/***************************************************************************
����ԭ�� 	GetCommMeterAddressType
��������	��ȡ���ַ����
�������	*pCommMAdrress			:ͨ�Ŵ������ı��ַ
������� 	��
���ز���	C_MeterAddress/C_Broadcast/C_Condense_AA_All/C_Condense_AA/C_AdrressError
ȫ�ֱ��� 	��
������ע	������ݲ���ַ����������֧��ȫ99��ȫAA����ȫ0(ȫ0��Ϊȫ���)��
***************************************************************************/
uchar8	GetCommMeterAddressType(uchar8	*pCommMAdrress)
{
	ushort16	i, V_usDataEncode;
	uchar8	V_ReturnData;
	uchar8	MeterAddress[CLComm_Address];
	uchar8	V_AANum;
	uchar8	V_MeterAddrNum;

/*�жϱ��ַ�Ƿ�Ϊȫ99*/
	for( i = 0; i < CLComm_Address; i++ )
	{
		if(pCommMAdrress[i] != 0x99)
		{
			break;
		}
	}
	if(i == CLComm_Address)
	{
		return(C_Broadcast);		/*�㲥*/
	}

/*ȡ��ͨ�ŵ�ַ�������������Ĭ��Ϊȫ0*/
	i = CLComm_Address;
	V_ReturnData = InF_Read_Data(CComm_Address, MeterAddress, &i, &V_usDataEncode);
	if(V_ReturnData != C_OK)
	{
		for( i = 0; i < CLComm_Address; i++ )
		{
			MeterAddress[i] = 0;
		}
	}
/*�ȶԱ��ַ�Ƿ�Ϊ��λ��ȫ��ַ*/
	V_AANum = 0;
	V_MeterAddrNum = 0;
	for( i = 0; i < CLComm_Address; i++ )
	{
		if(V_AANum ==0)
		{/*û���жϹ�AA������ȫ����ж�*/
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
		{/*�й�0xAA����������ȫ����0xAA����������Ͳ��б����*/
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
	{/*ȫ���*/
		return(C_MeterAddress);
	}
	if(V_AANum == CLComm_Address)
	{/*ȫAA*/
		return(C_Condense_AA_All);
	}
	if( ( V_AANum + V_MeterAddrNum ) == CLComm_Address )
	{/*������λ*/
		return(C_Condense_AA);
	}
	else
	{
		return(C_AdrressError);
	}
}

/***************************************************************************
����ԭ�� 	Cal_645CS
��������	����CS
�������	pStartByte			:������׵�ַ
				BygteLen				:�����㳤��
������� 	��
���ز���	�ۻ���256��ģ
ȫ�ֱ��� 	��
������ע	���ñ���������ȷ��������ȷ�����ﲻ�жϳ��ȺϷ�
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
����ԭ�� 	Cal_645CS
��������	����CS
�������	pStartByte			:������׵�ַ
				BygteLen				:�����㳤��
������� 	��
���ز���	�ۻ���256��ģ
ȫ�ֱ��� 	��
������ע	���ñ���������ȷ��������ȷ�����ﲻ�жϳ��ȺϷ�;
          �˺�����ͨ���жϵ���
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
����ԭ�� 	If_Frame_Ok
��������	��������֡��ʽ���жϣ��Ϸ���������V_645Frame����
�������	pV_645Frame				:������Ľ���֡
				*pStr_Comm_Parm_Address	:ͨ�Ž�������
������� 	 *pV_645Frame			:�Ϸ�������������.
���ز���	C_OK/C_Error
ȫ�ֱ��� 	SV_Comm_Parse_Local.RecFlag
������ע	pV_645Frame->ChannelNo��������.����������ȫ���ú�

***************************************************************************/
uchar8	IfFrameOkSetV_645Frame(Str_Comm_645 *pV_645Frame, Str_Comm_Parm 	*pStr_Comm_Parm_Address)
{
	uchar8	 i;
	ushort16 V_DataOffSet;

/*�ж�ͨ������������2��68��16��־*/
	if(CommRecFlag645 != C_CommRecFlagForInt_Ok)
	{
		return(C_Error);
	}
	else
	{
		SV_Comm_Parse_Local.RecFlag = CommRecFlag645;
	}

/*ע����ֻ�жϱ�ź�CS��68��16����ͨ���ж����жϹ���*/
/*�ж�ͨ�ŵ�ַ*/
	pV_645Frame->AddressFlag = GetCommMeterAddressType(&CommBuff[C_CAddr_OFS_ForRx]);

	if( ( pV_645Frame->AddressFlag != C_MeterAddress )
	   && ( pV_645Frame->AddressFlag != C_Broadcast )
	   && ( pV_645Frame->AddressFlag != C_Condense_AA_All )
	   && ( pV_645Frame->AddressFlag != C_Condense_AA ) )
	{
		return(C_Error);
	}
/*����Cs�Ƿ���ȷ.עC_Comm_FixedRxLen����CS 16�Ĺ̶�����*/
	if( Cal_645CS(&CommBuff[C_68_1_OFS_ForRx], ( C_Comm_FixedRxLen - 2 + CommBuff[C_L_OFS_ForRx] ) )
	   != CommBuff[C_Data_OFS_ForRx + CommBuff[C_L_OFS_ForRx]] )
	{
		return(C_Error);
	}

/*��V_645Frame����ֵ*/
/*C������Ҫ-0x33*/
	pV_645Frame->C = CommBuff[C_C_OFS_ForRx];

/*���ݳ��Ȱ���68��*/
/*�����򳤶ȼ�������copy��ע�����ﳤ�Ȳ���Ҫ-0x33��������Ҫ-0x33*/
	pV_645Frame->DataLen = CommBuff[C_L_OFS_ForRx];

	for(i = 0; i < CommBuff[C_L_OFS_ForRx]; i++ )
	{
		pV_645Frame->Data[i] = CommBuff[C_Data_OFS_ForRx + i] - 0x33;
	}
/*��������ܽű���������ʱ��04000102ת����698��ʽ����*/
	PF_Buffer4ToUlong32(&pV_645Frame->Data[CDI_O_V_645], &( pV_645Frame->DI), 4);

	/*��pV_645Frame�в����ߴ���*/
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
����ԭ�� 	DealWith_RstModule
��������	����λģ���Դ��Ϣ��������SV_CommParse.RstModuleParm����
�������	IsPowerOn���Ƿ����ϵ��־��= C_Flag_Ok���ϵ��־������ֵû��
������� 	��
���ز���	��
ȫ�ֱ��� 	SV_CommParse.RstModuleParm
������ע	1���ϵ��ʼ�������е���
				2����ʱ���������е��ã�500ms����һ�Σ�
				3	�ϵ�����ģ����и�λһ��
				4��ʱ�ӿ��12:25:25ʱ�����жϣ���������򲻽��и�λ��
					a��	������ز�ģ�飬�����ģ�鸴λ
					b��	�����GPRSģ�飬������ģ�鸴λ
					�����Ƿ�ΪGPRSģ�飬�Ե����Ƿ����ù�GPRS�ź�����
***************************************************************************/
ulong32 SV_ModuleResetTimer24h;   /*24hģ��ͨ����λ*/
void DealWith_RstModule( uchar8 IsPowerOnFlag )
{
	ulong32 bpsDataCode = CModular_Baud;
	uchar8 bpsData[5] = {0x06, 0x02, 0x08, 0x01, 0x00};/*9600,żУ�飬8λ���ݣ�1λֹͣ���޿�����*/
	ushort16 bpsDataLen = CLModular_Baud;
	uchar8 buf[2];
/*������ϵ磬��ֱ�Ӹ�λģ��һ��*/
	if( ( IsPowerOnFlag == C_Flag_Ok ) || ( SV_ModuleResetTimer24h == 0 ) )
	{
		SV_ModuleResetTimer24h = C_ModuleResetTimer24h;
		InF_InitCommUartForDispatch(C_Module, C_bps_9600, C_CommDataLen8, C_SerStp_1, C_parity_Even);/*��λģ�鲨����*/
		InF_Write_Data(C_Msg_Communication, bpsDataCode, bpsData, bpsDataLen, C_W_SafeFlag);
		InF_SwithPeripherals(C_ModuleReset, C_On);

		buf[0] = 0;
		buf[1] = 0;
		SetGPRSSignal(&buf[0]);		/*698Э��*/

		SV_Comm_Parse.RstModuleParm.IsRstModuleFlag = C_Flag_Ok;
		SV_Comm_Parse.RstModuleParm.IsSet_GPRS_Signal = C_Flag_Err;
		return;
	}
}

/***************************************************************************
����ԭ�� 	GetAutoDispCycleTime
��������	��ȡ�Զ���������ʱ��
�������	��
������� 	��
���ز���	�Զ���������(HEX)
ȫ�ֱ��� 	��
������ע
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
		DispNumHex = 0x12;				/*��������Ĭ����12��*/
	}

	Len = 1;	/*���˺���ܻᵼ�¶��Ŀ��������������鲻����*/
	V_ReturnData = InF_Read_Data(CPer_Dis_Screen_Time, &DispTimeHex, &Len, &V_usDataEncode);
	if(V_ReturnData != C_OK)
	{
		DispTimeHex = 5;
	}
	/*ȥ��BCDתHEX�Ĳ���*/


	AutoDispCycleTime =(ushort16) (DispNumHex * DispTimeHex);

	return(AutoDispCycleTime);


}
/***************************************************************************
����ԭ�� 	LightenCommSign
��������	��ͨ�ŷ���
�������	CommNo				:ͨ����
������� 	��
���ز���	��
ȫ�ֱ��� 	���ȶ���
������ע	��
***************************************************************************/
void		LightenCommSign(uchar8	CommNo,uchar8	PowerFlag)
{
	ushort16	AutoDispCycleTime;

	switch(CommNo)
	{
		case		C_RS485_1:
		{
			/*�绰Ͳ���绰Ͳ��1*/
			Comm_SendMsgToDisp(C_ComSign,C_AlwaysDisplay,C_Duration_3s_L);
			Comm_SendMsgToDisp(C_ComChannel1Sign,C_AlwaysDisplay,C_Duration_3s_L);
		}break;
		case		C_RS485_2:
		{
			/*�绰Ͳ���绰Ͳ��2*/
			Comm_SendMsgToDisp(C_ComSign,C_AlwaysDisplay,C_Duration_3s_L);
			Comm_SendMsgToDisp(C_ComChannel2Sign,C_AlwaysDisplay,C_Duration_3s_L);
		}break;
		case		C_Module:
		{
			/*�ز�����*/
			Comm_SendMsgToDisp(C_ModuleComSign,C_AlwaysDisplay,C_Duration_3s_L);
		}break;
		case		C_IR:
		{
			/*�绰Ͳ*/
			Comm_SendMsgToDisp(C_ComSign,C_AlwaysDisplay,C_Duration_3s_L);
			if(PowerFlag != C_PowerOff)			/*ͣ��ͨ�Ų��㱳��*/
			{/*����*/
				AutoDispCycleTime = GetAutoDispCycleTime();
				Comm_SendMsgToDisp(C_BackLED,C_AlwaysDisplay,(AutoDispCycleTime*2));
			}
		}break;
		default:
			return;
	}
}
/***************************************************************************
����ԭ�� 	InF_ActiveReportSetting
��������	��������ϱ�״̬�ĵǼ�
�������	V_ucBitNum		:Ҫ�޸ĵ������ϱ��¼��������ϱ�״̬����λ��
������� 	��
���ز���	��
ȫ�ֱ���
������ע	���ģʽ�ֶ�Ӧλ�������ã����Ӧ��������++
				��Ȼ��������㣬�����⴦��
***************************************************************************/
void		InF_ActiveReportSetting(uchar8	V_ucBitNum)
{
	ushort16	Crc16;
/*�ж���ڲ����Ƿ�Ϸ�����ģʽ���Ƿ������ϱ� */
	if(Is_EnableReport(V_ucBitNum)!=C_OK)
	{
		return;
	}
/*�ж����������Ƿ�������ȷ���������ȷ������*/
	J_ReportNAN_Null_IfErrSetZero();

	if(V_ucBitNum == C_Times_MeterClear)
	{
		if(InF_JudgeKeyStatus()==CInfo_TestKey)
		{/*Ϊ������Կ(��Կ)�������ϱ���˽Կ�Ž����ϱ�*/
			return;
		}
	}
/*�޷����������ݱ�ʶ���¼���FF*/
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
/*��������++��������CRC*/
	if(SV_ReportNewAddNum[V_ucBitNum] != 0xFF)
	{
		SV_ReportNewAddNum[V_ucBitNum]++;
	}
	Crc16 = PF_Cal_CRC(SV_ReportNewAddNum, C_ReportStateNum);
	PF_Ushort16ToBuffer2(&SV_ReportNewAddNum[C_ReportStateNum], &Crc16);
	Write_SV_ReportNewAddNum(SV_ReportNewAddNum);
}

/***************************************************************************
����ԭ�� 	J_ReportNAN_Null_IfErrSetZero
��������	1����������ϱ�������������ȷ������
				2���ж������ϱ�״̬���Ƿ�ȫ�ա�ȫ�գ�����C_OK
�������	��
������� 	��
���ز���	C_OK			:ȫ�գ�û���κι�����Ϣ��Ҫ�ϱ�
				C_Error			:�й�����Ҫ�ϱ�
ȫ�ֱ��� 	SV_ReportNewAddNum
������ע
***************************************************************************/
uchar8	J_ReportNAN_Null_IfErrSetZero(void)
{
	uchar8	 V_ReturnData;
	ushort16 Crc16, V_Len, V_usDataEncode;

/*�ж�SV_ReportNewAddNum�Ƿ�CRC��ȷ���������ȷ����ȫ������*/
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
/*�ж����������Ƿ�ȫ��Ϊ0?*/
	if( Is_Buf_AllZero( SV_ReportNewAddNum, C_ReportStateNum ) == C_OK )
	{/*����ȫ������0��*/
		return(C_OK);
	}
	else
	{/*�й���*/
		return(C_Error);
	}
}

/***************************************************************************
����ԭ�� 	Judge_ReportWithNxtFrame
��������	�ж��Ƿ���ú���֡���������ϱ�
�������	��
������� 	��
���ز���	C_OK			: �ǣ��ú���֡���������ϱ�
				C_Error			:���������ϱ���
ȫ�ֱ���
������ע
***************************************************************************/
#define		C_Work_Char_RWNxtFrame	0x04
uchar8	Judge_ReportWithNxtFrame(void)
{
	uchar8	Meter_Work_Char, V_ReturnData;
	ushort16	DataLen, V_usDataEncode;

/*���ȶ�ȡ��������������������ϱ�ģʽ*/
	DataLen = CLMeter_Work_Char1_645;
	V_ReturnData = InF_Read_Data(CMeter_Work_Char1_645, &Meter_Work_Char, &DataLen, &V_usDataEncode);
	if(V_ReturnData != C_OK)
	{
		return(C_Error);		/*�����ֶ���������Ϊ���������֡�ϱ�*/
	}
/*�ж��������Ƿ����������ϱ�*/
	if((Meter_Work_Char & C_Work_Char_RWNxtFrame) == 0)
	{
		return(C_Error);		/*�����ֲ��������֡�ϱ�*/
	}
/*�ж��Ƿ��������ϱ�*/
/*��ʱ������û���ϱ�����������󣬲������̸�λ���κ������*/
/*��ʾ�к���֡������Ժ�Ҫ��:���ϱ���δ�������µ������ϱ�����������ʾ�ٴ��ϱ���*/
/*��ʱ�ٴ���*/
/*�ж��Ƿ�Ϊȫ�ա�*/
	if(J_ReportNAN_Null_IfErrSetZero() == C_OK)
	{/*ȫ��*/
		return(C_Error);
	}
	else
	{
		return(C_OK);
	}
}

/***************************************************************************
����ԭ�� 	Is_EnableReport
��������	ȷ���Ƿ������ϱ�
�������	V_ucBitNum		:�ϱ��¼��������ϱ�״̬����λ��0-95
������� 	��
���ز��� 	C_OK			:�����ϱ�
				C_Error			:�������ϱ�
ȫ�ֱ���
������ע	���ģʽ�ֶ�Ӧλ�������ã����C_OK
				��ǰ����ģʽ��λ�������ϱ�λ֮����໥��ϵ
				���㷨�����������ϵ����ȷ�����ж�Ӧ��
			698����645���ӣ�ֻ������Ŀ�����ϱ�����������ģʽ���Ƿ�����Ϊ�����ϱ��������ϱ�
			�����ϱ����Դ�쳣���㶨�ų�������ǡ�����բ��������ʧѹ��ʧ�������磩
***************************************************************************/
uchar8		Is_EnableReport(uchar8	V_ucBitNum)
{
	uchar8	Drive_Report_Mode_645[CLDrive_Report_Mode_645];
	uchar8	V_ReturnData;
	uchar8	ByteIndex;					/*ģʽ�������±�*/
	uchar8	BitIndex;					/*��ģʽ�ֽ��ж�Ӧ��λ��*/
	uchar8	Mode;
	ushort16	i, V_usDataEncode;
	ulong64 V_uldrive_Report_Mode_645 = 0;
/*�±곬�����ֵ���򷵻ش���*/

	if(V_ucBitNum >= C_ReportStateNum)
	{
		return(C_Error);
	}
/*��ģʽ�֣�������������򷵻ش���*/
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

/*�����ϱ�״̬����0-31λ����ģʽ��λһһ��Ӧ*/
	if(V_ucBitNum < 32)
	{
		i = V_ucBitNum;
	}
/*�����ϱ�״̬����32-47λ����ģʽ��16-31λ��Ӧ*/
	else if(V_ucBitNum < 48)
	{
		i = V_ucBitNum - 16;
	}
/*�����ϱ�״̬����48-63λ����ģʽ��16-31λ��Ӧ*/
/*�����ϱ�״̬����64-95λ����ģʽ��32-63λ��Ӧ*/
	else
	{
		i = V_ucBitNum - 32;
	}
	if( i == 41 )  /*˫Э���ܹ��ʷ��� 645�ϱ�ģʽ�ֲ���bit22���ʷ���ԭbit41���������Ϊ����λ*/
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
����ԭ�� 	Init_SV_ReportNewAddNum
��������	��ʼ�������ϱ�״̬��
�������	��
������� 	��
���ز���	��
ȫ�ֱ��� 	SV_ReportNewAddNum
����ʱ��	1������ʱ���ȵ��ñ�������Ȼ���ٵ������������ϱ���λ
				2���жϺ���J_ReportNAN_Null_IfErrSetZero�з���CRC����
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
����ԭ�� 	SF_Clear645_ReportNewAddNum
��������	��645�����ϱ������¼�����λ״̬��
�������
������� 	��
���ز���	��
ȫ�ֱ���
����ʱ��

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
		V_ucHaveReportState[C_EventClr_Offset] = 0xFD;  /*ȥ��������㡢�¼�����*/
		Rst_SV_ReportNewAddNum(V_ucHaveReportState);
    }
    else
    {
		for(i = 0; i < CReport_645_Judge_Num; i++ )
		{
			if(V_ucEventNo == TB_ReportEventNo[i].EventN0) /*����ⲻ������ϱ�*/
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
����ԭ�� 	SF_Clear645_ReportNewAddNum
��������	��645�����ϱ������¼�����λ״̬��
�������
������� 	��
���ز���	��
ȫ�ֱ���
����ʱ��

***************************************************************************/
void	SF_Clear645_ReportNewAddNum_EventClear()
{
	Init_SV_ReportNewAddNum();					/*�����ϱ�����*/
	Init_SV_HaveReportState();					/*����ȫ����λ�����ϱ��������ж��й����ٴ��ϱ�*/
    return;
}
/***************************************************************************
����ԭ�� 	SF_RstHaveReportState_645To698
��������	����645���ϱ���״̬�֣���λ��Ӧλ698�е��¼�
�������	*pRstState				:����λ�������ϱ�״̬�֡��̶�Ϊ12�ֽ�
������� 	��
���ز���	��
ȫ�ֱ��� 	SV_HaveReportState
����ʱ��	1�������ϱ�״̬���Զ���λ��ʱʱ�� ��
			2���յ���λ����
698����645����	   ����645�е��ϱ�λ����Ӧ698�е��¼��ţ����и�λ��
                   �˺�����Ҫ��645��λ����֮ǰ��645��λ���������ϱ�λ�Ḵλ
645Ĭ�������ϱ����Դ�쳣���㶨�ų�������ǡ�����բ��������ʧѹ��ʧ��������,������㣩
***************************************************************************/
const Str_ReportEventNo TB_ReportEventNo[CReport_645_Judge_Num]=
{
  /*645��bitλ    			698���¼���*/
  {C_Report_Bit10,     C_OpenMeterCoverEventNo},	/*����*/
  {C_Report_Bit12,     C_MagneticCheckEventNo}, 	/*�㶨�ų�����*/
  {C_Report_Bit13,     C_PowerAbnormalEventNo}, 	/*��Դ�쳣*/
  {C_Report_Bit14,     C_RelayOpenEventNo},     	/*��բ*/
  {C_Report_Bit15,     C_RelayCloseEventNo},    	/*��բ*/
  {C_Report_Bit16,     C_AlossvoltageEventNo},  	/*A��ʧѹ*/
  {C_Report_Bit19,     C_ALosscurrentEventNo},  	/*A��ʧ��*/
  {C_Report_Bit20,     C_AOvercurrentEventNo},  	/*A�����*/
  {C_Report_Bit32,     C_BlossvoltageEventNo},  	/*B��ʧѹ*/
  {C_Report_Bit35,     C_BLosscurrentEventNo},  	/*B��ʧ��*/
  {C_Report_Bit36,     C_BOvercurrentEventNo},  	/*B�����*/
  {C_Report_Bit48,     C_ClossvoltageEventNo},  	/*C��ʧѹ*/
  {C_Report_Bit51,     C_CLosscurrentEventNo},  	/*C��ʧ��*/
  {C_Report_Bit52,     C_COvercurrentEventNo},  	/*C�����*/
  {C_Report_Bit69,     C_PowerfailEventNo},     	/*����*/
  {C_Report_Bit81,     C_TolClearEventNo},      	/*�������*/

  {C_Report_Bit0,		C_RelayFaEndEnEventNo},		/*���ɿ������� */
  {C_Report_Bit3,		C_RTCBatLowVolEventNo},		/*ʱ�ӵ�ص�ѹ�� */
  {C_Report_Bit8,		C_PowerBatLowVolEventNo},	/*ͣ�糭����Ƿѹ*/
  {C_Report_Bit11,		C_OpenTerminalCoverEventNo},/*����ť��*/
  {C_Report_Bit17,		C_ALessvoltageEventNo},		/*A��Ƿѹ*/
  {C_Report_Bit18,		C_AOvervoltageEventNo},		/*A���ѹ*/
  {C_Report_Bit21,		C_AReversecurrentEventNo},	/*A�๦�ʷ���*/
  {C_Report_Bit22,		C_ALossphaseEventNo},		/*A�����  */
  {C_Report_Bit33,		C_BLessvoltageEventNo},		/*B��Ƿѹ*/
  {C_Report_Bit34,		C_BOvervoltageEventNo},		/*B���ѹ*/
  {C_Report_Bit38,		C_BReversecurrentEventNo},	/*B�๦�ʷ���*/
  {C_Report_Bit39,		C_BLossphaseEventNo},		/*B�����  */
  {C_Report_Bit49,  	C_CLessvoltageEventNo},		/*C��Ƿѹ */
  {C_Report_Bit50,  	C_COvervoltageEventNo},		/*C���ѹ  */
  {C_Report_Bit54,  	C_CReversecurrentEventNo},	/*C�๦�ʷ���*/
  {C_Report_Bit55,  	C_CLossphaseEventNo},		/*C����� */
  {C_Report_Bit64,  	C_ReversephaseVoltageEventNo},/*��ѹ������ */
  {C_Report_Bit66,  	C_UnbanlanceVoltageEventNo},/*��ѹ��ƽ�� */
  {C_Report_Bit74,  	C_TotalVoltageLoseEventNo},	/*ȫʧѹ */
  {C_Report_Bit80,  	C_ProgramEventNo},			/*���  */
  {C_Report_Bit82,  	C_DemandClearEventNo},		/*�������� */
  {C_Report_Bit83,  	C_EventClearEventNo},		/*�¼����� */
  {C_Report_Bit84,  	C_AdjTimeEventNo},			/*Уʱ */
  {C_Report_Bit7,       C_ClockFaEventNo},         /*ʱ�ӹ���*/
  {C_Report_Bit73,		C_TReversecurrentEventNo}, /*���й����ʷ���*/
};
void SF_RstHaveReportState_645To698(uchar8	*pRstState)
{
	uchar8	V_ucBitNum = 0;
	uchar8	i;
	uchar8	j;
	uchar8	HaveReportState;
    uchar8  V_ucEventNo[CReport_645_Judge_Num], V_ucFindEventNo, V_ucRstEventNum = 0;


    /*�����Ѿ��ϱ�״̬���е�λ�����Ҷ�Ӧλ698�¼��š�*/
	for( j = 0; j < C_ReportStateByteNum; j++ )
	{
		HaveReportState = 0x01;
		for(i = 0; i < 8; i++ )				/* 1�ֽ���8λ*/
		{
			if( ( pRstState[j] & HaveReportState ) != 0 )
			{/*��Ӧλ��Ҫ��λ�����Ҷ�Ӧ698�¼���*/
				for( V_ucFindEventNo = 0; V_ucFindEventNo < CReport_645_Judge_Num; V_ucFindEventNo++ )
				{
					if(V_ucBitNum == TB_ReportEventNo[V_ucFindEventNo].BitN0)
					{
						V_ucEventNo[V_ucRstEventNum] = TB_ReportEventNo[V_ucFindEventNo].EventN0;
						V_ucRstEventNum++;
						break;/*������ҵ��ˣ��Ͳ������ң�ÿ��bitֻ����1���¼�*/
					}
					else/*��������¼�������*/
					{
						;
					}
				}
			}
			V_ucBitNum++;
			HaveReportState = HaveReportState << 1;
		}
	}
     /*����698�¼��ż��¼����������Ӧ�ϱ���*/
    for( i = 0; i < V_ucRstEventNum; i++ )
    {
		/*����բ�����ϱ�״̬�������⴦��+ʱ��Ƿѹ�ͳ���Ƿѹ*/
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
����ԭ�� 	Rst_SV_ReportNewAddNum
��������	�������ϱ���״̬�֣���λ��Ӧλ��������,�����ϱ�����
�������	*pRstState				:����λ�������ϱ�״̬�֡��̶�Ϊ12�ֽ�
������� 	��
���ز���	��
ȫ�ֱ��� 	SV_ReportNewAddNum��SV_HaveReportState
����ʱ��	1�������ϱ�״̬���Զ���λ��ʱʱ�� ��
				2���յ���λ����
***************************************************************************/
void		Rst_SV_ReportNewAddNum(uchar8	*pRstState)
{
	uchar8	V_ucBitNum = 0;
	uchar8	i;
	uchar8	j;
	uchar8	HaveReportState;
	ushort16	Crc16;

/*�ж������ϱ��������������Ƿ���ȷ������ȷ��ֱ��ȫ������*/
	J_ReportNAN_Null_IfErrSetZero();
/*�����Ѿ��ϱ�״̬���е�λ�����Զ�Ӧλ�������㡣*/
	for( j = 0; j < C_ReportStateByteNum; j++ )
	{
		HaveReportState = 0x01;
		for( i = 0; i < 8; i++ )				/* 1�ֽ���8λ*/
		{
			if((pRstState[j] & HaveReportState) != 0)
			{/*��Ӧλ���ϱ�*/
				SV_ReportNewAddNum[V_ucBitNum] = 0;
			}
			V_ucBitNum++;
			HaveReportState = HaveReportState << 1;
		}
	}
/*���¼���CRC*/
	Crc16 = PF_Cal_CRC(SV_ReportNewAddNum, C_ReportStateNum);
	PF_Ushort16ToBuffer2(&SV_ReportNewAddNum[C_ReportStateNum], &Crc16);
	Write_SV_ReportNewAddNum(SV_ReportNewAddNum);
/*��λ���ϱ�����*/
	for( i = 0; i < C_ReportStateByteNum; i++ )
	{
		SV_HaveReportState.State[i] = SV_HaveReportState.State[i] & (~pRstState[i]);
	}
	SV_HaveReportState.Timer = 0;
	SV_HaveReportState.CRC16 = PF_Cal_CRC(SV_HaveReportState.State, C_ReportStateByteNum + 2);
	Write_SV_HaveReportState(SV_HaveReportState.State);
}
/***************************************************************************
����ԭ�� 	Init_SV_HaveReportState
��������	��λSV_HaveReportState
�������	��
������� 	��
���ز���	��
ȫ�ֱ��� 	SV_HaveReportState
����ʱ��	ͨ�Ŷ�ʱ���Ƚ��������У��ж϶�ʱ��Ϊ0

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
����ԭ�� 	Set_SV_HaveReportState
��������	��ֵSV_HaveReportState
�������	*pHaveReportState				:�������ϱ�״̬�֣��̶�12�ֽ�
������� 	��
���ز���	��
ȫ�ֱ��� 	SV_HaveReportState
������ע	�����ϱ�ʱ(����Set_ReportStateFrame)�е���
***************************************************************************/
void		Set_SV_HaveReportState(uchar8	*pHaveReportState)
{
	ushort16	i, V_usDataEncode;
	uchar8	V_ReturnData;
	uchar8	V_RstReportStateTimerBCD;
	ulong32	V_RstReportStateTimerHex;

/*�����ϱ��Զ���λʱ��*/
	i = 1;
	V_ReturnData = InF_Read_Data(CRst_ReportState_Timer, &V_RstReportStateTimerBCD, &i, &V_usDataEncode);
	if(V_ReturnData != C_OK)
	{
		V_RstReportStateTimerBCD = 0x30;								/*����������Ĭ��30����*/
	}
	PF_BCDtoHexBytes(&V_RstReportStateTimerBCD, &V_RstReportStateTimerHex, CLRst_ReportState_Timer);
	V_RstReportStateTimerHex = V_RstReportStateTimerHex * 120;			/*����500ms��ʱ��*/

/*��ֵSV_HaveReportState*/
	SV_HaveReportState.Timer = (ushort16)V_RstReportStateTimerHex;
	for(i = 0; i < C_ReportStateByteNum; i++ )
	{
		SV_HaveReportState.State[i] = pHaveReportState[i];
	}
	SV_HaveReportState.CRC16 = PF_Cal_CRC(SV_HaveReportState.State, C_ReportStateByteNum + 2);
	Write_SV_HaveReportState(SV_HaveReportState.State);
	if(SV_HaveReportState.Timer == 0)
	{/*��ʱ��ֱ�Ӿ���0*/
		SF_RstHaveReportState_645To698(&SV_HaveReportState.State[0]);	/*��698�����ϱ���698����645����*/
		Rst_SV_ReportNewAddNum(&SV_HaveReportState.State[0]);
		return;
	}
}
/***************************************************************************
����ԭ�� 	Set_ReportStateFrame
��������	��֯�����ϱ�֡������ֵSV_HaveReportState�������Զ��嶨ʱ��
�������	pReportStateFrame				:�ϱ�֡���׵�ַ
				pReportLen					:����֡����ָ��
������� 	*pReportStateFrame			:�����ϱ�����֡
				*pReportLen					:����֡����
���ز���	��
ȫ�ֱ��� 	SV_HaveReportState
������ע	ע��pReportStateFrame��ʼ������һ������
				4�ֽ�DI����+12(�����ϱ�״̬��)+96(��������)+2(AA)��󳤶�Ҫ��
***************************************************************************/
void		Set_ReportStateFrame(uchar8	*pReportStateFrame, uchar8	*pReportLen)
{
	uchar8	i;
	uchar8	j;
	uchar8	V_ucBitNum = 0;
	uchar8	HaveReportState;
	ulong32	ReportStateDI;

/*�ж���������CRC�Ƿ���ȷ������ȷ��ȫ����0*/
	J_ReportNAN_Null_IfErrSetZero();

/*����DI*/
	ReportStateDI = CDrive_Report_State_645;
	PF_Ulong32ToBuffer4(pReportStateFrame, &ReportStateDI, CLen_DI);

/*�ó���Ϊ4�ֽ�DI+12�ֽ������ϱ�״̬��+1�ֽ�AA*/
	*pReportLen = C_ReportStateByteNum + CLen_DI;
	pReportStateFrame[*pReportLen] = 0xAA;		/*��λ��1��AA*/
	(*pReportLen)++;
/*����������������λ�ϱ�֡�������ϱ�״̬�ֺ���������*/
	for( j = 0; j < C_ReportStateByteNum; j++ )
	{
		HaveReportState = 0x01;
		pReportStateFrame[CLen_DI + j] = 0;		/*���Ƚ�֡�������������ϱ�״̬����0*/

		for( i = 0; i < 8; i++ )				/* 1�ֽ���8λ*/
		{
			if(SV_ReportNewAddNum[V_ucBitNum] != 0)
			{/*����������Ϊ0*/
				pReportStateFrame[CLen_DI + j] = pReportStateFrame[CLen_DI + j] | HaveReportState;
				pReportStateFrame[*pReportLen] = SV_ReportNewAddNum[V_ucBitNum];
				(*pReportLen)++;
			}
			V_ucBitNum++;				/*ʵ�ʾ���i*j+j*/
			HaveReportState = HaveReportState << 1;
		}
	}
/*�������һ����ָ���AA*/
	pReportStateFrame[*pReportLen] = 0xAA;
	(*pReportLen)++;
}
/***************************************************************************
����ԭ�� 	Write_SV_HaveReportState
��������	���������ϱ���־д���ݲ�
�������	*pHaveReportState	:�������ϱ�״̬�֣��̶�12�ֽ�
������� 	��
���ز���	��
ȫ�ֱ��� 	SV_HaveReportState
������ע	�����ϱ�ʱ(����Set_ReportStateFrame)�е���
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
����ԭ�� 	Write_SV_ReportNewAddNum
��������	�������ϱ�����д���ݲ�
�������	*ReportNewAddNum	:�����ϱ��������̶�96�ֽ�
������� 	��
���ز���	��
ȫ�ֱ��� 	SV_ReportNewAddNum
������ע	�����ϱ�ʱ(����Set_ReportStateFrame)�е���
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
����ԭ�� 	DealWithEventReportIO
��������	���������ϱ�����
�������	��
������� 	��
���ز���	��
ȫ�ֱ��� 	��
����ʱ��	1��ͨ��500ms��ʱ�����е���
				2���ϵ��ʼ�������е���
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
����ԭ�� 	Comm_Parse
��������	���ͨ�Ž���������Ӧ�𡢱���¼�������
�������	CommNo:			����ͨ����
				PowerFlag:		��Դ��־C_PowerOn��ʾ�е�״̬��
								C_PowerFalling��ʾ����������ر���̣�
								C_PowerOff��ʾ���ڵ���״̬��C_PowerRising��ʾ����������ر����
������� 	��
���ز���	��
ȫ�ֱ��� 	SV_Comm_Parse/SV_Com_Parse_Local/
				ͨ�����Str_Comm_Parm/Str_Comm_NxtFrame
������ע
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

/*����������ȫ�ֱ�����ʼ��*/
	Comm_ParseInit();
	SV_SetBPS_Flag = C_Error;			/*Ĭ�ϲ�������BPS*/
/*���е絽ͣ����أ���Ӧ��ֱ���˳���*/
	if( PowerFlag == C_PowerFalling )
	{
		return;
	}
	if( CommNo == C_Module )
	{
	  	SV_ModuleResetTimer24h = C_ModuleResetTimer24h;
	}
/*��ȡͨ����������ָ��*/
	SV_Comm_Parse_Local.SafeControlFlag = SV_Comm_Parse_Local.SafeControlFlag | C_W_SafeFlag_1;

	pStr_Comm_Parm_Address = Get_Str_Comm_Parm_Pointer(CommNo);
	if(pStr_Comm_Parm_Address == C_NULL)
	{
		Comm_ParseInit();
		return;		/*ͨ������ʵ�ʲ����ܡ������ˣ�Ҳ�����ͣ�ֱ���˳���*/
	}
	else
	{
		V_645Frame.ChannelNo = CommNo;
	}
/*��������֡��������Ϸ�����V_645Frame*/
	if( IfFrameOkSetV_645Frame( &V_645Frame, pStr_Comm_Parm_Address ) != C_OK )
	{
		InF_InitComm(CommNo);
		Comm_ParseInit();
		return;
	}
	V_645Frame.PowerFlag = PowerFlag;

/*�ж���������е��ڼ��������λ������֤��Ч��ͬʱ�ж�ͨ�����Ǻ�����˳���*/
	memset( V_Buf2, 0, C_TimerExceed10minLen );/*���㱸��*/
	if( PowerFlag == C_PowerOff )
	{/*�����ڼ�,���������֤��Ч��������*/
		if( JudgeTimerExceed10min(&IR_AuthT_645) == C_TimerEnable )
		{/*ͣ���ڼ䣬���ԭ�Ⱥ�����֤��Ч����ȡ��������֤����ʱ�ᷢ�������֤������Ϣ*/
			DealWith_IR_Auth_Timer_645(C_Set_TimerExceed10min, V_Buf2);
		}
		if( JudgeTimerExceed10min(&ID_AuthT_T) == C_TimerEnable )
		{/*ͣ���ڼ䣬���ԭ�������֤��Ч����ȡ�������֤����ʱ�ᷢ������֤������Ϣ*/
			DealWith_ID_Auth_T_Timer(C_Set_TimerExceed10min, V_Buf2);
		}
/*�ж�ͨ���Ƿ�Ϊ���⣬����ֱ���˳�*/
		if( CommNo != C_IR )
		{
			return;
		}
	}
/*���е�ַ������Ȩ�ޡ�Ȩ�޵��ж�.ע��3���жϺ�������Ӧ�����*/
/*Ӧ�ñ�����Ӧ��������*/
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

/*����C���ò�ͬ�Ľ�������		*/
	if( CanParse == C_OK )
	{
		SV_Comm_Parse_Local.SafeControlFlag = SV_Comm_Parse_Local.SafeControlFlag | C_W_SafeFlag_2;
		switch( V_645Frame.C )
		{
			case		0x15:		/*����ͨ�ŵ�ַ*/
				Comm_SetCommAddress(&V_645Frame);
				break;
			case		0x13:		/*��λ�����	*/
				Comm_CondenseAAReadMAddress(&V_645Frame);
				break;
			case		0x21:		/*дУ�����*/
				Comm_MeterCalibration(&V_645Frame);
				break;
			case		0x20:		/*��У�����*/
				Comm_Cal_Read(&V_645Frame);
				break;
			case		0x03:		/*��ȫ��֤����*/
				Comm_SecurityParse(&V_645Frame);
				break;
			case		0x1A:		/*�����������*/
				Comm_MeterClear(&V_645Frame);
				break;
			case		0x19:		/*��������*/
				Comm_DemandClear(&V_645Frame);
				break;
			case		0x1B:		/*�¼���¼����*/
				Comm_EventClear(&V_645Frame);
				break;
			case		0x18:		/*�޸�����*/
				Comm_SetPassword(&V_645Frame);
				break;
			case		0x08:		/*�㲥Уʱ*/
				Comm_BroadcastSetClock(&V_645Frame);
				break;
			case		0x17:		/*�޸Ĳ�����*/
				Comm_Set_BPSr_C17(&V_645Frame);
				break;
			case		0x1C:		/*���ɿ��ؿ���*/
				Comm_LoadSwitch_Control(&V_645Frame);
				break;
			case		0x14:		/*�α�������*/
				Comm_14SetParm(&V_645Frame);
				break;
			case		0x11:		/*��*/
				Comm_11_Read(&V_645Frame);
				break;
			case		0x12:		/*����֡��*/
				Comm_ReadNxtFrameParse(&V_645Frame);
				break;
			case		0x1E:		/*������������*/
				Comm_SetInFactoryState(&V_645Frame);
				break;
			case		0x1F:		/*����������ݻָ������������������Ĵ�������*/
				Comm_RecoverRamData(&V_645Frame);
				break;
			default:			/*������C����,Ӧ����������*/
				InF_InitComm(CommNo);
				Comm_ParseInit();
				break;
		}
	}


/*����ͨ���Ŵ�����Ӧ����ʾ*/
	LightenCommSign(CommNo,PowerFlag);

/*�����ڲ���Ϣ��־�����ж�Ӧ����Ϣ����*/
	for( i = 0; i < C_MessageMaxNum; i++ )
	{
		V_CommMsgNo = Comm_FetchMsg();
		if(V_CommMsgNo == CMsg_Null)
		{
			break;
		}
		switch(V_CommMsgNo)
		{
			case	CMsg_Txd:				/*��������*/
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
			case	CMsg_InitComm:			/*��ʼ��������Ϣ*/
			{
				InF_InitComm(CommNo);
			}break;
			case	CMsg_MeterClear:			/*���������Ϣ����*/
				Have_IPEvent_MeterClear(&V_645Frame);
				break;
			case		CMsg_DemandClear:		/*���������Ϣ����*/
				Have_IPEvent_DemandClear(&V_645Frame);
				break;
			default:
				break;
		}
	}
/*����Comm_ParseInit�˳�����*/
	if(V_HaveMsgTx == C_Error)
	{/*�������еĵط���ֱ���˳��ģ�û�д���������Ϣ������������������û�з�����Ϣ���ͳ�ʼ������*/
	 	InF_InitComm(CommNo);
	}
	Comm_ParseInit();
	return;
}

/***************************************************************************
����ԭ�� 	Comm_LoadSwitch_Control
��������	���ɿ��ؿ������������Ӧ��
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	��
������ע	1���Ƿ��Ѻ�����֤�������֤�Ƿ���Ч���������жϡ�
					����ע��:02/04�������������֤�������֤��
				2�������98�����룬��200�ι����������жϡ�
					02/04�����룬�����жϺ��������ж�3���������
				3�������Ƿ�֧�ֱ�������Ҫ�������жϡ����������ò���
***************************************************************************/
void		Comm_LoadSwitch_Control(Str_Comm_645 *pV_645Frame)
{
	uchar8	ReponseDataNum = 1;			/*��Ӧ���ֽڸ���*/
	ushort16	V_usOrderExcuteStatus = C_PasswordError_failure, ValidDataLen, V_usDataEncode;		/*Ĭ�������δ��Ȩ��*/
	uchar8	Clock[CLDate_Time];
	uchar8	*pValidData;
	uchar8	V_ReturnData;

/*ȡ��Ӧ�ֽڳ���*/
	if( ( pV_645Frame->Data[CPW_SpecialO_V_645 + 3] == 0x01 )
	 && ( pV_645Frame->Data[CPW_SpecialO_V_645] != 0x02 )
	 && ( ( pV_645Frame->Data[CPW_SpecialO_V_645] != 0x04 ) ) )
	{/*����ܼ�������2��4��p2=1����ӦΪ2�ֽڡ�*/
		ReponseDataNum = 2;
	}
/*�жϱ����Ƿ�֧��*/
	if(C_Meter_Type == C_SmartMeter)
	{/*���ܱ�֧�ֱ�����*/
		Comm_LoadS_Ctr_Reponse(C_Error, C_PasswordError_failure, ReponseDataNum, pV_645Frame);
		return;
	}
/*����Ȩ���жϡ������ж�ִ��ʱ��*/
	if(pV_645Frame->Data[CPW_SpecialO_V_645] == 0x98)
	{/*98��*/
		V_usOrderExcuteStatus = Comm_98LoadSwitch_Control(pV_645Frame);
	}
	else if( ( pV_645Frame->Data[CPW_SpecialO_V_645] == 0x02 ) || ( pV_645Frame->Data[CPW_SpecialO_V_645] == 0x04 ) )
	{/*02��04������*/
		V_usOrderExcuteStatus = Comm_02LoadSwitch_Control(pV_645Frame);
	}
	else
	{/*����Ӧ��δ��Ȩ�˳�*/
		Comm_LoadS_Ctr_Reponse(C_Error,C_PasswordError_failure, ReponseDataNum, pV_645Frame);
		return;
	}
	if(V_usOrderExcuteStatus != C_OK)
	{
		Comm_LoadS_Ctr_Reponse(C_Error, V_usOrderExcuteStatus, ReponseDataNum, pV_645Frame);
		return;
	}
/*�жϳ��ȼ��ж������ֹʱ���Ƿ���ϵͳʱ��֮�������ֹʱ����ϵͳʱ��֮��*/
	if( pV_645Frame->DataLen != ( 4 + 4 + 8 ) )	/* 4�ֽ�����4�ֽڲ����ߴ���8�ֽ�R1-R8*/
	{
		Comm_LoadS_Ctr_Reponse(C_Error, C_PasswordError_failure, ReponseDataNum, pV_645Frame);
	}

	pValidData = &pV_645Frame->Data[CData_OtherO_V_645];
	ValidDataLen = CLDate_Time;

/*�жϽ�ֹʱ���Ƿ���Ч����ЧӦ��ִ��ʱ����Ч*/
	if( PF_DataTimeActive( &pValidData[C_R3_O], C_DT_Start_ss, CLDate_Time ) != C_OK )
	{
		Comm_LoadS_Ctr_Reponse( C_Error, C_ActTimeUnvalid_failure, ReponseDataNum, pV_645Frame );
		return;
	}
	if( InF_Read_Data( CDate_Time, Clock, &ValidDataLen, &V_usDataEncode ) == C_OK )
	{/*ʱ����ó�*/
		if( PF_Campare_Data( &pValidData[C_R3_O], Clock, CLDate_Time ) == C_LessThan )
		{
			Comm_LoadS_Ctr_Reponse( C_Error, C_ActTimeUnvalid_failure, ReponseDataNum, pV_645Frame );
			return;
		}
	}
//698����645��������բ��ʱ645תд698
#if 0
        ValidDataLen = CLRelay_Delay_Time_645;
        if(InF_Read_Data(CRelay_Delay_Time_645, V_ucBuffer, &ValidDataLen, &V_usDataEncode) != C_OK)
        {
          V_ucBuffer[0] = 0;
          V_ucBuffer[1] = 0;
        }
        InF_Write_Data(C_Msg_Communication, CRelay_Delay_Time,V_ucBuffer, CLRelay_Delay_Time, C_W_SafeFlag);
#endif
//���������ͨ�Ÿ��жϵĶ��Ѿ��ж��ˣ����ü̵���ģ��Ľӿں�����
//�������ķ���ֵ����Ӧ��.
	ulong32 V_ulDelay;
	V_ulDelay = pValidData[C_R2_O];
	V_ulDelay = V_ulDelay * 5;
	V_ReturnData = InF_DealwithComRelayOrder( pValidData[C_R1_O], pV_645Frame->Opcode, V_ulDelay, &V_usOrderExcuteStatus, C_UsedBy645);
	Comm_LoadS_Ctr_Reponse(V_ReturnData, V_usOrderExcuteStatus, ReponseDataNum, pV_645Frame);
}

/***************************************************************************
����ԭ�� 	Comm_98LoadSwitch_Control
��������	���98�����ɿ��������֤���������ݸ�д��02����ظ�ʽ
�������	 *pV_645Frame			:���յ�������֡
������� 	 *pV_645Frame			:�����02���ĸ�ʽ
���ز���	C_OK/C_Meter_Safeguardfailure/C_MACError_failure/C_AuthOverTime_failure/C_PasswordError_failure
ȫ�ֱ���
������ע	�������������ͬ�����Ȳ��жϣ�R3-R8���ж�,
				����Ҫ����200�ε�����.���������֤�Ƿ���Ч��
				���������֤�Ƿ���Ч
***************************************************************************/
ushort16		Comm_98LoadSwitch_Control(Str_Comm_645 *pV_645Frame)
{
	uchar8	*pValidData;
	uchar8	ValidDataLen;
	ushort16	Serr16;

/*�����жϳ���*/
	if(pV_645Frame->DataLen <= ( CLen_OpCode + CLen_CommPW ) )
	{
		return(C_PasswordError_failure);
	}
/*98���������������֤*/
	if(JudgeTimerExceed10min(&ID_AuthT) != C_TimerEnable)
	{
		return(C_AuthOverTime_failure);					/*�����֤��ʱ*/
	}
/*��û��200�ι���*/
	if( Comm_DealwithSPTVariable(C_JudgeSPTVariable) == C_SPT_Num_Over )
	{
		return(C_Meter_Safeguardfailure);				/*200�ι���*/
	}
/*����Ǻ�������ڣ�����봦�ں�����֤�ڼ�*/
	if(pV_645Frame->ChannelNo == C_IR)
	{
		if(JudgeTimerExceed10min(&IR_AuthT_645) != C_TimerEnable)
		{
			return(C_PasswordError_failure);
		}
	}
/*���ð�ȫģ��ӿں������н���*/
	pValidData = &pV_645Frame->Data[CData_OtherO_V_645];
	ValidDataLen = pV_645Frame->DataLen - CLen_CommPW - CLen_OpCode;

	Serr16 = InF_S_ControlCommand(pValidData, &ValidDataLen);
	if(Serr16 == C_SERR_ESAM_VF)
	{
		Comm_DealwithSPTVariable(C_SPTNumAdd);
		return(C_MACError_failure);
	}
	else if(Serr16 != C_OK)
	{/*��������*/
		return(C_PasswordError_failure);
	}
	else
	{
		pV_645Frame->DataLen = CLen_OpCode + CLen_CommPW + ValidDataLen;
		return(C_OK);
	}
}

/***************************************************************************
����ԭ�� 	Comm_02LoadSwitch_Control
��������	���02�����ɿ��������֤��
�������	 *pV_645Frame			:���յ�������֡
������� 	 *pV_645Frame			:�����02���ĸ�ʽ
���ز���	C_OK/C_AuthOverTime_failure/
ȫ�ֱ���
������ע	�������������ͬ�����Ȳ��жϣ�R1-R8���ж�,
				1���ж������Ƿ���ȷ��
				2���ж��Ƿ�Ϊ��բ�ͺ�բ���������һ���ԭ���ۺ��г����ǲ����
					���翼��02��04�����븺�ɿ��ƾ�������ۺ��г���
					�����ۺ��г������б�̿���!�����ɿ�����������Ҫ��̿���!
				3�������жϺ���ͨ�������жϺ�����֤
***************************************************************************/
ushort16		Comm_02LoadSwitch_Control(Str_Comm_645 *pV_645Frame)
{
	uchar8	*pValidData;

	pValidData = &pV_645Frame->Data[CData_OtherO_V_645];
/*�ж��Ƿ�Ϊ�������	*/
	if( Is_PW_OK( &pV_645Frame->Data[CPW_SpecialO_V_645] ) != C_OK )
	{
		return(C_PasswordError_failure);
	}
/*�ж��Ƿ��ڣ��������п������ִ��*/
	if( JudgeTimerExceed10min(&SI_JTimer_BSOn2500) == C_TimerEnable )
	{
		return (C_OK);
	}
/*�ж��Ƿ�Ϊ��բ���բ����������Ӧ��C_PasswordError_failure*/
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
����ԭ�� 	Comm_LoadS_Ctr_Reponse
��������	���ɿ��Ƶ�Ӧ��֡��֯
�������	ReposneType				:=C_OK:��ȷӦ�� = C_Error:����Ӧ��
				V_usOrderExcuteStatus		:ReposneType = C_OK��Ϊ��������ִ��״̬��
										:ReposneType = C_Error��Ϊ����״̬��
				ReposneLen				:��Ӧ���� =1 ,��ReposneType =C_OK������Ϊ0
														ReposneType =C_Error,����Ϊ1
										:��Ӧ���� =2,����ReposneType�����Ⱦ�Ϊ2
				*pV_645Frame				:���յ�������֡
�������
���ز���
ȫ�ֱ��� 	����ͨ��������غ����÷��ͻ���
������ע
***************************************************************************/
void	Comm_LoadS_Ctr_Reponse(uchar8 ReposneType, ushort16 V_usOrderExcuteStatus, uchar8 ReposneLen, Str_Comm_645 *pV_645Frame)
{
	uchar8	ResponseData[2];

	PF_Ushort16ToBuffer2(ResponseData, &V_usOrderExcuteStatus);
/*���ȵ���1����Ӧ��*/
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
/*���ȵ���2*/
	if(ReposneType != C_OK)
	{
		Comm_Response_03_Err(V_usOrderExcuteStatus, pV_645Frame);
	}
	else
	{/*��ȷӦ��2�ֽڵ�ִ��״̬��*/
		Comm_Response_FromP_Normal(pV_645Frame, ResponseData, 2);
	}
}
/****************************************************************************
*����ģʽ�²�������
****************************************************************************/
typedef struct
{
	ulong32	ParmDI;
	ulong32	ParmDI_645;
	uchar8	ParmLen;
	uchar8	Offset;				/*ͨ��֡�е�ƫ�ơ�������DI*/
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
����ԭ�� 	SF_InFactoryState
��������	�ж���������ĸ���־�룬�����ȫʧѹ��ѹ/����/�𶯹���/�𶯵���,��C_NormalExchangeOAD
									����ǵ�ѹ�쳣��ѹ��ֵ����C_AbnormalVoltageOAD
�������	UlOAD:645��־��
�������
���ز���	��־�����ͣ�0������Ҫ����ת����1����Ҫ����BCD��HEXת����2 �����2�����ֱ�ת����
ȫ�ֱ���
������ע
***************************************************************************/

uchar8	SF_InFactoryState(ulong32 UlOAD)
{
	uchar8 V_ucReturn = 0;

	if( ( UlOAD == CLoss_Volage_Vol_645 ) || ( UlOAD == CLoss_Volage_Curr_645 ) || ( UlOAD == CStart_Up_Current_645 ) || ( UlOAD == CStart_Up_Power_645 ) )
	{
		V_ucReturn = C_NormalExchangeOAD;			/*BCDתHEX*/
	}
	else if( UlOAD == CVolage_Abnor_Vol_645 )
	{
		V_ucReturn = C_AbnormalVoltageOAD;			/*Ҫ�ֳ�2�����ݷֱ�ת*/
	}
	return V_ucReturn;
}
/***************************************************************************
����ԭ�� 	SF_InFactoryExchangeBCD
��������	������Ҫ���������ò������ݽ�������ת��
			�����ȫʧѹ��ѹ/����/�𶯹���/�𶯵���,��HEXתBCD;
			����ǵ�ѹ�쳣��ѹ��ֵ���ֳ������ֱ����HEXתBCD;
�������	UlOAD:645��־��
�������
���ز���
ȫ�ֱ���
������ע
***************************************************************************/
void SF_InFactoryExchangeBCD(uchar8 LineNo, uchar8 *pV_ucData)
{
	uchar8	V_ucOADType, V_ucLen, V_ucVoltage, V_ucBuffer[10] = {0};
	ulong32 V_ulDoubleWordBuufer = 0;

	V_ucLen = TB_SetParmInFactoryState[LineNo].ParmLen;
	V_ucOADType = TB_SetParmInFactoryState[LineNo].ChangeFlag;
	if( V_ucOADType == C_NormalExchangeOAD)										/*��Ҫ����HEX��BCD��ת��OAD*/
	{
		PF_Buffer4ToUlong32(pV_ucData, &V_ulDoubleWordBuufer, V_ucLen);
		PF_HextoBCDBytes(&V_ulDoubleWordBuufer, pV_ucData, (uchar8 *)&V_ucLen);
	}
	else if( V_ucOADType == C_AbnormalVoltageOAD )
	{
		V_ucVoltage = CLVolage_Abnor_Vol_Single;								/*��Դ�쳣��ѹ��������*/
		PF_Buffer4ToUlong32(pV_ucData, &V_ulDoubleWordBuufer, V_ucVoltage);
		PF_HextoBCDBytes(&V_ulDoubleWordBuufer, pV_ucData, &V_ucVoltage);
		V_ucVoltage = CLVolage_Abnor_Vol_Single;								/*��Դ�쳣��ѹ��������*/
		PF_Buffer4ToUlong32(pV_ucData + V_ucVoltage, &V_ulDoubleWordBuufer, V_ucVoltage);
		PF_HextoBCDBytes(&V_ulDoubleWordBuufer, pV_ucData  + V_ucVoltage, &V_ucVoltage);
	}
	else
	{
		;
	}
}
/***************************************************************************
����ԭ�� 	Comm_SetInFactoryState
��������	������������
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	��
������ע	���Ĵ�������.�����Ӹ���΢����������
***************************************************************************/
void		Comm_SetInFactoryState(Str_Comm_645 *pV_645Frame)
{
	uchar8   V_ucBuffer[72], i, Is_WriteDataOk = C_OK, V_ucVoltage = 0, V_ucOADType = 0;
	ushort16 V_ucLen, V_usDataEncode;
	Str_WrParmTable	WrParmTable;
	union B16_B08_2 Temp16;
	struct COMMUNICATION_FRM
	{
		uchar8 Buf[100];										/*���ջ���/���ͻ���*/
	}Uart[1];
	ulong32  V_ulDoubleWordBuufer = 0;

	if( ( pV_645Frame->DataLen == 0x04 ) && ( pV_645Frame->Data[0] == 0x05 ) )		/*RTCʱ�ӵ�У������΢������EE��������,��������ע��*/
	{
		if( JudgeTimerExceed10min(&SI_JTimer_BSOn2500) != C_TimerEnable )
		{
			Comm_Response_Set_ReadErr(C_Unauthorized, pV_645Frame);
			return;
		}
		Uart[0].Buf[9] = pV_645Frame->DataLen;
		memcpy(Uart[0].Buf + 10, &(pV_645Frame->Data[0]), pV_645Frame->DataLen);	/*���ݸ���΢����10��������*/

		{
			Temp16.B08[0] = Uart[0].Buf[ 11 ];					/*Di1*/
			Temp16.B08[1] = Uart[0].Buf[ 12 ];					/*Di2*/

			if( Temp16.B16 == 0xeeee )							/*��Ҫ��������������򸴵���У������޷��·�RTC�ռ�ʱУ׼����*/
			{
				memset( Uart[0].Buf+14, 0x00, 64 );

				Uart[0].Buf[14 + 32] = *(uchar8*)0x1FFFFC0E;	/*0x04 ����404*/
				Uart[0].Buf[14 + 38] = 0xaa;
			}
			else if( Temp16.B16 == 0xfefe )
			{
				memset( Uart[0].Buf + 14, 0x00, 64 );
				memcpy( Uart[0].Buf + 14, (uchar8*)0x1FFFFC10, 9 );

			}
			else if( Temp16.B16 < 0x400 )						/*��Ҫ������չ��ee��������򸴵���У������޷���ȡee�е�����*/
			{
				InF_ReadE2ThreeRTC(ee_temperature_page, ee_temperature_inpage, (Uart[0].Buf + 14 + ee_temperature_inpage), ee_temperature_lenth); /*��ȡ11�ֽ��¶Ȳ���ϵ��*/

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
		if( Is_ParmType_3( pV_645Frame->DI, &WrParmTable, pV_645Frame->ChannelNo ) == C_OK )	/*��������У�����1E����д�Ĳ���ֻ��GPRS��ز���*/
		{/*���δ��룬��Ϊ�˽��III������У�����GPRSģ����ز�����ͨ��1E������ж���д��*/
	       /*************��������а���GPRS�ź�ǿ�Ⱥ͸�λ�����ϱ���ֻ����14��������**************/
			if( ( pV_645Frame->DI == CGPS_Signal ) || ( pV_645Frame->DI == CRst_Report_State_645 ) )
			{
				return;
			}
			V_ucLen = pV_645Frame->DataLen - CLen_DI - CLen_CommPW;
			if( pV_645Frame->DataLen > ( CLen_DI + CLen_CommPW ) )								/*���ȴ��ڱ�ʶ������볤�ȣ���ʾΪд����*/
			{/*д����ǰ���ԺϷ��Խ����жϣ����ݲ㳤�Ȳ���д����ȥ��*/
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
	/*�жϱ�ʶ��*/
		if(pV_645Frame->DI != 0xFFFFFFFF)
		{
			if((pV_645Frame->DI == 0x3EEEEE05))
			{
				Comm_11_03Response_Normal(pV_645Frame, V_ucBuffer, 64);
				return;
			}
			else
			{
				return;						/*����Ǳ�ʶ�벻�ԣ�������Ӧ��*/
			}
		}
	/*�ж��Ƿ�Ϊ������˳�����ģʽ*/
		if( ( pV_645Frame->DataLen == 0x09 ) && ( pV_645Frame->Data[C_O_SF_Data] == 0x1A ) )
		{/*������������1AΪ��������ģʽ�ı�־��*/
			In_Out_FactoryState(pV_645Frame);
			return;
		}

	/*������������������ڳ���ģʽ�����á�*/
		if( JudgeTimerExceed10min(&SI_JTimer_BSOn2500) != C_TimerEnable )
		{
			Comm_Response_Set_ReadErr(C_Unauthorized, pV_645Frame);
			return;
		}
	/*���ݳ��ȣ����в�ͬ��������Ľ�����*/
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
			if(pV_645Frame->Data[C_O_SF_Data] == C_ReadParaFlay)	/*��ȡ�������ò���*/
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
����ԭ�� 	Comm_RecoverRamData
��������	�ָ����ݲ�RAM���ݣ�������Ĵ������ܡ�RAM���ݻָ����
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	��
������ע	��������΢RTC��У���RTC��У���������ڳ���
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
		uchar8 Buf[220];			/*���ջ���/���ͻ���*/
	}Uart[1];
	uchar8 k, OutBuf[256], Buf[64];/*�������ݳ���*/

	/*�жϱ�ʶ��,��˾�ڲ����������ж�*/
	if( ( pV_645Frame->DI == 0xFFFFFFFF ) && ( ( pV_645Frame->DataLen == 0x0A ) || ( pV_645Frame->DataLen == 0x09 ) ) )/*�����ж϶�E2��RAM��Flash���ݻ������ݻָ�����*/
	{
		if(pV_645Frame->DataLen == 0x0A)/*��������*/
		{
			if( ( pV_645Frame->Data[C_O_SF_Data] == C_ReadFlashFlay )		/*��ȡflash����*/
			 || ( pV_645Frame->Data[C_O_SF_Data] == C_ReadRamFlay ) 		/*��ȡRam����*/
		     || ( pV_645Frame->Data[C_O_SF_Data] == C_ReadE2Flay)			/*��ȡE2����*/
			 || ( pV_645Frame->Data[C_O_SF_Data] == C_ReadFRAMFlay ) )		/*��ȡ��������*/
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
		else												/* ���ݻָ� */
		{
			if(pV_645Frame->Data[C_O_SF_Data] == 0x02)		/* E2�ָ�RAM���� */
			{
				InF_RAMDataRecoverFromE2();					/* �������ݲ㣬E2�ָ�RAM���� */
				Comm_Response_Set_ReadErr(C_OK, pV_645Frame);
				return;
			}
		}
	}
	/*����΢RTCʱ�ӵ�У�����ж��Ƿ���*/
	k = 0;
	OutBuf[0] = 0x00;
	if(C_OK != InF_JudgeIJTimer())
	{
		Comm_Response_Set_ReadErr(C_OtherErr, pV_645Frame);
		return;
	}
	Uart[0].Buf[9] = pV_645Frame->DataLen;
	memcpy( &(Uart[0].Buf[10]), &(pV_645Frame->Data[0]), pV_645Frame->DataLen);		/*���ݸ���΢����10��������*/

	switch(pV_645Frame->Data[0])								/*����������*/
	{
		case 0x03:
		{
			/*�����¶����ߵĲ���˵����*/
			/*0 �����¶�б��΢�� */
			/*1 �����¶�б��΢��*/
			/*2 ���¾�������΢���������޵����κ���ϵ����x*0.0001*/
			/*3 ���¾�������΢���������޵����κ���ϵ����x*0.0001*/
			/*4 ���¶����Уֵ����ֵ*/
			/*9 ����25+��������΢��������25+�޵����κ���ϵ����x*0.0004 krh*/
			/*10����25-��������΢��������25-�޵����κ���ϵ����x*0.0004 krl*/
			if(pV_645Frame->DataLen != 0x0A)
			{
				break;
			}

			Temperpara_Verify();								/*�¶�ϵ��У��*/
			memcpy( Buf, Tpara.Offset, ee_temperature_lenth );	/*�����¶�ϵ��*/

			if( Uart[0].Buf[19] == 0x00 )						/*ȫ������*/
			{
				memcpy( Buf + 2, Uart[0].Buf + 16, 3 );
			}
			else if( Uart[0].Buf[19] == 0x55 )					/*���¸����¶�ϵ��*/
			{
				Buf[2] = Uart[0].Buf[16];
			}
			else if( Uart[0].Buf[19] == 0x5a )					/*���µ����¶�ϵ��*/
			{
				Buf[3] = Uart[0].Buf[17];
			}
			else if( Uart[0].Buf[19] == 0xaa )					/*���µ�Уֵ*/
			{
				Buf[4] = Uart[0].Buf[18];
			}
			else if( Uart[0].Buf[19] == 0x05 )					/*���¸����¶�ϵ��krh*/
			{
				Buf[9] = Uart[0].Buf[18];
			}
			else if( Uart[0].Buf[19] == 0x50 )					/*���µ����¶�ϵ��krl*/
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
			memcpy( Tpara.Offset, Buf, ee_temperature_lenth );		/*����ram�¶�ϵ��*/
			Crc_16Bits_Add2(Tpara.Offset, ee_temperature_lenth );	/*CRC����*/
			RTC_RT.TempFlag = 0xff;									/*���²������*/
			GV_ucTime = 6;											/*���������¶�adc,4S��*/
			k = 1;
		}
		break;
		case 0x04:													/*���¶�ADC������*/
		{
			ushort16 Vus_RTCADJUST;
			k = 9;
			if( const_tx_flag == 0x3cc3 )
			{
				OutBuf[1] = 0xc3;									/*0xc3��ʾ�¶ȵ�У��*/
			}
			else
			{
				OutBuf[1] = (uchar8)(const_tx_flag & 0xff);
			}
			OutBuf[2] = Tpara.RtcTMode;								/*��RTC��������ģʽ��0x55:����ģʽ��0xAA���²���ֵģʽ����������ͨģʽ*/

			Vus_RTCADJUST = InF_GetRTC_Adjust();
			if( RTC->ADSIGN & 0x00000001 )							/*��УֵС��0*/
			{
				Temp16.B16 = (ushort16)((short16)Vus_RTCADJUST * -1);
			}
			else
			{
				Temp16.B16 = Vus_RTCADJUST;
			}
			OutBuf[3] = Temp16.B16;
			OutBuf[4] = Temp16.B16 >> 8;							/*ʵ�ʲ���ֵ*/
			OutBuf[5] = Temperature_Adc;							/*���¶�ADC����*/
			OutBuf[6] = Temperature_Adc >> 8;

			V_Len = CLMeter_Temp;
			InF_Read_Data(CMeter_Temp, &OutBuf[7], &V_Len, &V_usDataEncode);
		}
		break;
		case 0x07:	/*����RTC��������ģʽ��0x55:����ģʽ��0xAA���²���ֵģʽ����������ͨģʽ*/
			RTC_RT.TestTrim = 0;
		case 0xa9:	/*�ر��¶Ȳ�����ͨ�ŵ�ʱ����׼������ʱ����*/
		case 0xaa:	/*д���¶����Уֵ��ͨ�ŵ�ʱ����(�·�2�ֽ��ռ�ʱ���,-10.0��~10.0��,����)*/
		case 0x0b:	/*�����¶�ADC΢��*/
		{
			/*5 �����¶�ADC΢��*/
			/*6 ���¶����УֵL��ͨ�ŵ�ʱ����*/
			/*7 ���¶����УֵH��ͨ�ŵ�ʱ����*/
			/*8 RTC��������ģʽ��0x55:����ģʽ��0xAA���²���ֵģʽ����������ͨģʽ*/
			Temperpara_Verify();	/*�¶�ϵ��У��*/
			memcpy( Buf, Tpara.Offset, ee_temperature_lenth );		/*�����¶�ϵ��*/
			if( Uart[0].Buf[ 10 ] == 0x07 )
			{
				if( ( Uart[0].Buf[9] != 0x02 ) ) 					/*���ݳ��ȴ���,��̽�ֹ*/
				{
					break;
				}
				Buf[8] = Uart[0].Buf[11];
				RtcStopProcFlag = 0x00;								/*��RTC�¶Ȳ�������*/
			}
			else if( Uart[0].Buf[ 10 ] == 0xa9 )/*�ر��¶Ȳ�����ͨ�ŵ�ʱ����׼������ʱ����*/
			{
				if( ( Uart[0].Buf[9] != 0x01 ) || ( const_tx_flag == 0x3cc3 ) )
				{
					break;		/*�ձ�̵�У��*/
				}
				if( ( Tpara.RtcTMode == 0x55 ) || ( Tpara.RtcTMode == 0xAA ) )
				{
					break;		/*��ֹ�ر�rtc����*/
				}
				RtcStopProcFlag = 0x55;								/*�ر�RTC�¶Ȳ�������*/
				GV_ucTime = 6;										/*���������¶�adc   ����΢ͬ��*/
				k = 1;
				break;
			}
			else if( Uart[0].Buf[ 10 ] == 0xaa )					/*(�·�2�ֽ��ռ�ʱ���,����)*/
			{
				if( (Uart[0].Buf[9] != 0x03)||(const_tx_flag == 0x3cc3)||(RtcStopProcFlag!=0x55)) break;	/*�ձ�̵�У��*/

				Temp16.B08[0] = Uart[0].Buf[ 11 ];
				Temp16.B08[1] = Uart[0].Buf[ 12 ];
				if( ( (short16)Temp16.B16 > 10000 ) || ( (short16)Temp16.B16 < -10000 ) )
				{
					break;											/*���ơ�10.000��*/
				}
				Temp16.B16 = Get_RTCTop_Proc( Temp16.B16 );			/*���㶥���Уֵ*/
				Buf[6] = Temp16.B08[0];
				Buf[7] = Temp16.B08[1];
				RtcStopProcFlag = 0x00;								/*��RTC�¶Ȳ�������*/
				Buf[4] = 0;											/*��΢��ֵ*/
				if( Buf[1] == 0 )
				{
					Buf[1] = 0x80;
				}
			}
			else	/*5 �����¶�ADC΢��*/
			{
				if( ( Uart[0].Buf[9] != 0x02 )||( ( Uart[0].Buf[11] & 0x7F ) > 50 ) )
				{
					break;											/*�������������Χ*/
				}
				Buf[5] = Uart[0].Buf[11];
			}
			V_ReturnFlag = InF_WriteE2ThreeRTC( ee_temperature_page, ee_temperature_inpage, Buf, ee_temperature_lenth );
			if( C_OK != V_ReturnFlag )
			{
				break;
			}

			if( ( Uart[0].Buf[10] & 0x0f ) == 0x0a )				/*д���¶����Уֵʱʱ���¼*/
			{
				InF_ReadE2ThreeRTC( ee_rtcadj_time_page, ee_rtcadjtime_inpage, Buf, ee_rtcadjtime_lenth );
				Buf[0]++;											/*д���¶����Уֵ������1*/

				V_Len = CLMeter_Temp;
				InF_Read_Data(CMeter_Temp, &Buf[8], &V_Len, &V_usDataEncode);
				Buf[7] = Uart[0].Buf[ 10 ];							/*ͨѶ��ʶ*/
				InF_WriteE2ThreeRTC( ee_rtcadj_time_page, ee_rtcadjtime_inpage, Buf, ee_rtcadjtime_lenth );
			}

			Tpara.Crc16.B08[0] += 1;
			temperpara_veri_flag = 1;
			RTC_RT.TempFlag = 0xff;									/*���²������*/
			GV_ucTime = 6;											/*���������¶�adc*/
			k = 1;
		}
		break;
		case 0x06:							/*�޸Ķ����Уֵ��ƫ����	NNNN	2*/
		{
			if(Uart[0].Buf[9] != 0x03)
			{
				break;						/*���ݳ��ȴ���,��̽�ֹ*/
			}
			if( Tpara.RtcTMode != 0x55 )
			{
				break;						/*���ڲ���ģʽ����Ч*/
			}

			Temp16.B08[0] = Uart[0].Buf[11];
			Temp16.B08[1] = Uart[0].Buf[12];
			if( ( ( (short16)Temp16.B16 ) < -200 ) || ( ( (short16)Temp16.B16 ) ) > 200 )
			{
				break;						/*�����Уֵ��ƫ��������λΪ������С������0.238��0.119*/
			}
			RTC_RT.TestTrim = (short16)Temp16.B16;
			RTC_RT.TempFlag = 0xff;			/*���²������*/
			GV_ucTime = 6;					/*���������¶�adc*/
			k = 1;
		}
		break;
		case 0x08:/*���ò���ֵ����*/
		{
			if( Uart[0].Buf[9] != 85 )
			{
				break;/*���ݳ��ȴ���,��̽�ֹ*/
			}
			if( ( Tpara.RtcTMode != 0x55 ) && ( Tpara.RtcTMode != 0xAA ) )
			{
				break;/*���ڲ���ģʽ����Ч*/
			}

			/*�����¶��Զ��ж�д�����ݵĵ�ַ*/
			if( RTC_RT.TempFlag == 0 )/*���²��*/
			{
				Temp16.B16 = ee_ptatvalue_page;
				i = ee_ptatvalue_inpage;
				Temp08 = ee_ptatvalue_lenth;
			}
			else if( RTC_RT.TempFlag == 1 )/*���²��*/
			{
				Temp16.B16 = ee_ptatvalue_lt_page;
				i = ee_ptatvalue_lt_inpage;
				Temp08 = ee_ptatvalue_lt_lenth;

				Crc_16Bits_Add2(Uart[0].Buf + 11, Temp08);
				Crc_16Bits_Add2(Uart[0].Buf + 11 + 42, Temp08);
				Temp08 = Temp08 + 2;/*����CRC��2�ֽ�*/
			}
			else if( RTC_RT.TempFlag == 2 )/*���²��*/
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

			Temperpara_Verify();									/*�¶�ϵ��У��*/
			memcpy( Buf, Tpara.Offset, ee_temperature_lenth );		/*�����¶�ϵ��*/
			Buf[8] = 0xAA;											/*�·����ݺ��Զ�������ģʽ*/
			V_ReturnFlag = InF_WriteE2ThreeRTC( ee_temperature_page, ee_temperature_inpage, Buf, ee_temperature_lenth );
			if( C_OK != V_ReturnFlag )
			{
				break;
			}
			Tpara.Crc16.B08[0] += 1;
			temperpara_veri_flag = 1;
			RTC_RT.TempFlag = 0xff;									/*���²������*/
			GV_ucTime = 6;											/*���������¶�adc*/
			k = 1;
		}
		break;
		case 0x09:													/*�����¶����Уֵ��ͨ�ŵ�ʱ����*/
		{
			k = 5;
			if( const_tx_flag == 0x3cc3 )
			{
				OutBuf[1] = 0xc3;									/*0xc3��ʾ�¶ȵ�У��*/
			}
			else
			{
				OutBuf[1] = (uchar8)(const_tx_flag & 0xff);
			}
			OutBuf[2] = Tpara.Offset[5];							/*�����¶�ADC΢��*/
			OutBuf[3] = Tpara.Offset[6];							/*���¶����УֵL*/
			OutBuf[4] = Tpara.Offset[7];							/*���¶����УֵH*/
		}
		break;
		default:
				break;
	}
	if( k == 0x00 )													/*������Ӧ��֡*/
	{
		Comm_Response_Set_ReadErr(C_OtherErr,pV_645Frame);
		return;
	}
	else
	{
		if(OutBuf[0] == 0x00)	 /*ȷ��֡*/
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
	memcpy( Uart[0].Buf + 10 + Temp08, OutBuf + 1, k );							/*��������*/
	memcpy( &pV_645Frame->Data[0], Uart[0].Buf + 10, pV_645Frame->DataLen);		/*�������ݣ���������������	*/
	Comm_RTC1F_Response_Normal(pV_645Frame, &pV_645Frame->Data[0], pV_645Frame->DataLen);
}
/***************************************************************************
����ԭ�� 	Set_InFactoryState
��������	����ģʽ�µ� ����
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	��
������ע	��
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
		{				/*�ĳ�698��־��*/
			V_ucOADType = TB_SetParmInFactoryState[i].ChangeFlag;
			if( V_ucOADType == C_NormalExchangeOAD)										/*��Ҫ����HEX��BCD��ת��OAD*/
			{
				V_ucLen = pSPIFS[i].ParmLen;
				PF_BCDtoHexBytes(&pV_645Frame->Data[C_O_SF_Data + pSPIFS[i].Offset], &V_ulDoubleWordBuufer, V_ucLen);
				PF_Ulong32ToBuffer4(&pV_645Frame->Data[C_O_SF_Data + pSPIFS[i].Offset], &V_ulDoubleWordBuufer, V_ucLen);
			}
			else if( V_ucOADType == C_AbnormalVoltageOAD )								/*��Դ�쳣��ѹ�������޺�����*/
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
����ԭ�� 	Act_InFactoryState
��������	����ģʽ�µĶ���
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	��
������ע	��Щ�������ڳ���ģʽ�½���Ӳ�����
***************************************************************************/
#define C_InFactoryState_DisplayTime_On 0x0A
void		Act_InFactoryState(Str_Comm_645 *pV_645Frame)
{
	uchar8	V_ResponseOk = C_OK;
/*����CC���ж�������*/
	switch(pV_645Frame->Data[C_O_SF_Data])
	{
		case		0x03:										/*�๦�����������*/
			InF_ModifyFunctionWord(C_SecondPulseOutput);		/*������ֻ��Ҫ����*/
			break;
		case		0x04:										/*���������������*/
			InF_ModifyFunctionWord(C_DemandPulseOutput);
			InF_MultiFunctionOutput(C_DemandPulse);
			break;
		case		0x05:										/*ʱ��Ͷ���ź����*/
			InF_ModifyFunctionWord(C_RatePulseOutput);
			InF_MultiFunctionOutput(C_RatePulse);
			break;
		case		0x06:										/*�����̵������ͨ*/
			Comm_SendMsgToDisp(C_WarnOutPut, C_AlwaysDisplay, C_InFactoryState_DisplayTime_On);
			break;
		case		0x07:										/*�����̵��������*/
			Comm_SendMsgToDisp(C_WarnOutPut, C_NotDisplay, C_Duration_Alway);
			break;
		case		0x09:										/*��λ�ز�ģ��*/
			InF_SwithPeripherals(C_ModuleReset, C_On);
			break;
		case		0x0A:										/*����������*/
			V_ResponseOk = C_Error;
			break;
		case		0x0B:										/*�رձ�����*/
			V_ResponseOk = C_Error;
			break;
		case		0x0C:										/*���������Ʋ���բ*/
			InF_RelayAct(C_Off);
			Comm_SendMsgToDisp(C_RelayStatusLED, C_AlwaysDisplay, C_InFactoryState_DisplayTime_On);
			break;
		case		0x0D:										/*�رձ����Ʋ���բ*/
			InF_RelayAct(C_On);
			Comm_SendMsgToDisp(C_RelayStatusLED, C_NotDisplay, C_Duration_Alway);
			break;
		case		0x0E:										/*���������*/
			Comm_SendMsgToDisp(C_BackLED, C_AlwaysDisplay, C_InFactoryState_DisplayTime_On);
			break;
		case		0x0F:										/*��ձ����*/
			Comm_SendMsgToDisp(C_BackLED, C_NotDisplay, C_Duration_Alway);
			break;
		case		0x18:										/*��������*/
		case		0x19:										/*�رշ�����*/
			V_ResponseOk = C_Error;
			break;
		case		0x1C:										/*д���ü̵���������*/
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
����ԭ�� 	In_Out_FactoryState
��������	��������ģʽ�Ľ�����Ӧ���¼���¼
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	��
������ע	ʵ��������IJʱ�䣬����Ϊ0�˳�������Ϊ��0������
***************************************************************************/
#define		C_TimeDurationInFactory		0xAE60
void	In_Out_FactoryState( Str_Comm_645 *pV_645Frame )
{
	ulong32	Soft_I_J_Time;
	uchar8	Buf[16];					/*��ʽǰ7���ֽ�������ʱ�䣬��2�ֽ��ǻ���5min����IJʱ�䣬BCD*/
	ushort16	DataLen = CLDate_Time, V_usDataEncode;

/*��ϵͳʱ�ӣ���Ϊ��̼�¼����ʼʱ�����ʱ�Ӷ�������Ĭ��2000��1��1��*/
	if( InF_Read_Data(CDate_Time, Buf, &DataLen, &V_usDataEncode) != C_OK )
	{
		Buf[CDate_Time_DD_O] = 0x01;
		Buf[CDate_Time_MM_O] = 0x01;
		Buf[CDate_Time_YYL_O] = 0xD0;
		Buf[CDate_Time_YYH_O] = 0x07;
	}

/*�ж����û����˳�*/
	PF_Buffer4ToUlong32(&pV_645Frame->Data[C_O_SF_Data + 1], &Soft_I_J_Time, 4);
	SV_Comm_Parse_Local.SafeControlFlag = SV_Comm_Parse_Local.SafeControlFlag | C_W_SafeFlag_3;
	if( Soft_I_J_Time == 0 )
	{/*�˳�*/
		if( JudgeTimerExceed10min(&SI_JTimer_BSOn2500) == C_TimerEnable )
		{
			memset( &Buf[CDate_Time_YYH_O+1], 0, 4 );
			DealWith_SI_J_Timer(C_Set_TimerExceed10min,&Buf[CDate_Time_YYH_O+1]);
			/*д���볧��ģʽ�¼���¼*/
			InF_Write_Data(C_Msg_Communication, CSoft_I_J_Prog_2, Buf, CLSoft_I_J_Prog_2, SV_Comm_Parse_Local.SafeControlFlag);
		}
		Comm_Response_Set_ReadErr(C_OK, pV_645Frame);
		return;
	}
	else if( Soft_I_J_Time <= C_TimeDurationInFactory )
	{/*ʱ���0����С��31�죬��Ϊ���볧��ģʽ*/
		if( InF_GetPeripheralStatus(C_KeyOpenCover) == C_Invalid )
		{/*���ǵ�����²��ܽ��볧��ģʽ������ȥ���������������ġ�*/
		/*������IJ�ĸ���2.5s�ۼ�1��Str_TimerExceed10min��������ʱ������5min���账��5*/
			Soft_I_J_Time = Soft_I_J_Time / 5;
			DataLen = 4;
			PF_HextoBCDBytes(&Soft_I_J_Time, &Buf[CDate_Time_YYH_O+1], (uchar8 *)&DataLen);
			if(SV_Comm_Parse_Local.SafeControlFlag == C_W_SafeFlag)
			{
				DealWith_SI_J_Timer(C_Set_TimerExceed10min,&Buf[CDate_Time_YYH_O+1]);	//���볧��ģʽ
				//д���볧��ģʽ�¼���¼
				InF_Write_Data(C_Msg_Communication,CSoft_I_J_Prog_1,Buf,CLSoft_I_J_Prog_1,SV_Comm_Parse_Local.SafeControlFlag);
				Comm_Response_Set_ReadErr(C_OK,pV_645Frame);
			}
		}
		return;
	}
	else
	{
		return;			/*������Ӧ��*/
	}
}
/***************************************************************************
����ԭ�� 	Comm_Cal_Read
��������	ͨ��У����ض�����Ľ�����Ӧ��
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	ͨ��ͨ������������
������ע	У��������ʽ:68 A0-A5 68 20 02 DI0 DI1 CS 16.
				�쳣Ӧ��68 A0 -A5 E0 01 ERR CS 16
				����Ӧ��68 A0 -A5 A0 L DI0 DI1 Data CS 16
	1����������-��У�����кš�DI1DI0 = 0x87A0
	2����У�����������оƬ��DI1DI0 = 0x86XX
	3�������ݲ�У�������DI1DI0 = 0x85XX
	4��������оƬʵʱ����ԭʼֵ��DI1DI0 = 0x83XX
***************************************************************************/
void		Comm_Cal_Read(Str_Comm_645 *pV_645Frame)
{
	uchar8	V_ReturnData;
	uchar8	buf_O_CanWrite = C_DILen_Cal;					/*��������д���ݵ�ƫ��*/
	ushort16	Cal_RdDI, LenFor_Data, V_usDataEncode;		/*�������ɱ�д���ܵĳ���*/
	uchar8	*pData;

	PF_Buffer2ToUshort16(&pV_645Frame->Data[C_O_DI0], &Cal_RdDI);
/*ָ���DI0��ʼ*/
	pData = &pV_645Frame->Data[C_O_DI0];
	LenFor_Data = C_Comm_Data_MaxLen - C_DILen_Cal;

	if(Cal_RdDI == 0x87A0)
	{/*��У�����к�*/
		V_ReturnData = InF_Read_Data(CRec_MeterSequence, &pData[buf_O_CanWrite], &LenFor_Data, &V_usDataEncode);
	}
	else	if(pV_645Frame->Data[C_O_DI1] == 0x85)
	{/*�����ݲ�У�����*/
		V_ReturnData = InF_Read_RecMeterData(pV_645Frame->Data[C_O_DI0], &pData[buf_O_CanWrite], (uchar8 *)&LenFor_Data);
	}
	else
	{/*�������Ƕ�����оƬ�е�У��Ĵ�����ʵʱ����ԭʼֵ*/
		V_ReturnData = InF_ReadReg_MeterIC(Cal_RdDI, &pData[buf_O_CanWrite], (uchar8 *)&LenFor_Data);
	}
/*��֯Ӧ��֡*/
	if(V_ReturnData == C_OK)
	{
		buf_O_CanWrite = buf_O_CanWrite + LenFor_Data;
		Comm_Response_FromP_Normal(pV_645Frame, pData, buf_O_CanWrite);
	}
	else
	{/*������������ͬ�ڴ�������ΪУ��ʱ���������*/
		Comm_Response_Set_ReadErr(V_ReturnData, pV_645Frame);
	}
	return;
}
/***************************************************************************
����ԭ�� 	Comm_MeterCalibration
��������	ͨ��У���������(���д����оƬ��У���¼���¼)
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	ͨ��ͨ������������
				��ΪУ��ǳ���Ҫ��Ӧ��2����ȫ��־
SV_Comm_Parse_Local.SafeControlFlag = SV_Comm_Parse_Local.SafeControlFlag|C_W_SafeFlag_1;
SV_Comm_Parse_Local.MeterClearFlag = SV_Comm_Parse_Local.MeterClearFlag |C_W_SafeFlag(У��������)
������ע
	1������������3��:
		a��У���������:
			��ʽ:L(0x13) +DI0 DI1 (A0 87) +PAP0P1P2C0C1C2C3  +5�ֽ����к�+4�ֽ�����
			����ж����ݲ������Ƿ�����ȷ���������ܲ�����д����������д
		b������У������
			��ʽ:L(0x09)+DI0DI1(68 87)+PAP0P1P2 +3�ֽ���Ч����
			����:���ü���ģ��ӿں������������ֵΪ����У��
					��д���ݲ�У�����,дУ���̼�¼��ʱ��
		c������У������
			��ʽ:L(0x09)+DI0DI1(69 87)+PAP0P1P2 +3�ֽ���Ч����
			����:���ü���ģ��ӿں������������ֵΪ����У��
					�����κδ���ֱ��Ӧ����ȷ���˳���
		d��дУ����������
			��ʽ:L(0x09)+DI0DI1(6A 87)+PAP0P1P2 +3�ֽ���Ч����
			����:���ü���ģ��ӿں������������ֵΪ����У��
					ѭ�������ݲ�У�������дУ���¼1-���ֵ��ͬʱ�����ݲ�У�����
	2����������У������
			��ʽ:L + DI0 DI1 (XX 86) + PAP0P1P2+3�ֽ�У�����
			����:���ü���ģ��Ľӿں������������ֵΪC_OK�������Ÿ���Ϊ1
					�����ݲ�У�������дУ���¼����д���ݲ�У�����
	3����У������
			��ʽ:L+DI0 DI1 (XX 82) + PAP0P1P2+9�ֽ�У�����
			����:���ü���ģ��Ľӿں������������ֵΪC_OK���������Ϊ3
					ѭ��3��д�����ݲ���Ŷ�ӦУ�������дУ���¼����д���ݲ�У�����
***************************************************************************/
#define		C_DI0ForBlockMaxLen		30
void		Comm_MeterCalibration(Str_Comm_645 *pV_645Frame)
{
	ushort16		Cal_DI1_DI0, DataLen, V_usDataEncode;
	uchar8	V_ReturnData;
	uchar8	Cal_DI0Buf_ForBlock[C_DI0ForBlockMaxLen];		/*��дʱ�����ط�����ŵ�����*/
	uchar8	Cal_DI0_Num;									/*������ŵĸ���*/
	uchar8	Cal_PW[CLRec_MeterPassWord];
	uchar8	i;

	PF_Buffer2ToUshort16(&pV_645Frame->Data[C_O_DI0], &Cal_DI1_DI0);
	SV_Comm_Parse_Local.MeterClearFlag = SV_Comm_Parse_Local.MeterClearFlag | C_W_SafeFlag_1;
/*�ж��Ƿ�Ϊ У���������*/
	if( ( Cal_DI1_DI0 == 0x87A0 ) && ( pV_645Frame->DataLen == 15 ) )
	{
		Cal_SetPassword(pV_645Frame);
		return;
	}
/*�����ж�һ�³��ȼ�DI1-DI0 �Ƿ���ȷ*/
	switch(Cal_DI1_DI0)
	{
		case		0x8768:					/*��������-����У��*/
		case		0x8769:					/*��������-����У��*/
			DataLen = 9;					/* 2�ֽ�DI��+4�ֽ�����+3�ֽ�����*/
			break;
		case		0x876A:					/*��������-У������*/
			DataLen = 9;					/* 2�ֽ�DI��+4�ֽ�����+3�ֽ�����*/
			SV_Comm_Parse_Local.MeterClearFlag = SV_Comm_Parse_Local.MeterClearFlag | C_W_SafeFlag_2;
			break;
		default:
			if((Cal_DI1_DI0 & 0xFF00)==0x8600)
			{/*һ��У������*/
				if(pV_645Frame->Data[C_O_DI0] >= C_MeterICDataNum_T)
				{/*DI0������Χ*/
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
			{/*��д��ʶ�롣DI0�ɼ���ģ���жϣ������ﲻ�ж�*/
				DataLen = 15;
				break;
			}
			/*����*/
			Comm_Response_Set_ReadErr(C_Cal_IDErr,pV_645Frame);
			return;
	}
	if(DataLen != pV_645Frame->DataLen)
		{/*���ȴ���*/
			Comm_Response_Set_ReadErr(C_Cal_LenErr, pV_645Frame);
			return;
		}
/*У���������ģʽ���������й��ˣ�������ж������Ƿ���ȷ*/
	DataLen = CLRec_MeterPassWord;
	V_ReturnData = InF_Read_Data(CRec_MeterPassWord, Cal_PW, &DataLen, &V_usDataEncode);
	if(V_ReturnData != C_OK)
		{/*Ӧ������δ���ù�У����������*/
			Comm_Response_Set_ReadErr(C_Cal_PWCanNotRD, pV_645Frame);
			return;
		}
	if((pV_645Frame->Data[C_O_PW_Cal]!=Cal_PW[0])||
		(pV_645Frame->Data[C_O_PW_Cal+1]!=Cal_PW[1])||
		(pV_645Frame->Data[C_O_PW_Cal+2]!=Cal_PW[2])||
		(pV_645Frame->Data[C_O_PW_Cal+3]!=Cal_PW[3]))
		{/*У�������!*/
			Comm_Response_Set_ReadErr(C_Cal_PW_Err, pV_645Frame);
			return;
		}
	SV_Comm_Parse_Local.SafeControlFlag = SV_Comm_Parse_Local.SafeControlFlag|C_W_SafeFlag_3;
/*���ü���оƬ�Ľӿں�����д����оƬУ��Ĵ���,����Ϊ���յ����������ȿۼ�6(2�ֽڱ�ʶ���4�ֽ�����)*/
	Cal_DI0_Num = C_DI0ForBlockMaxLen;
	V_ReturnData = InF_WriteCalReg_MeterIC(Cal_DI1_DI0, &pV_645Frame->Data[C_O_Data_Cal],
                                           (pV_645Frame->DataLen - 6), Cal_DI0Buf_ForBlock, &Cal_DI0_Num);
/*���ݷ���ֵ���в�ͬ�Ĵ���:*/
	switch(V_ReturnData)
	{
		case		C_StartCalibrationOK:		/*����У��*/
			Cal_WriteCalStartClock(pV_645Frame);
			return;
		case		C_CalibrationOK:			/*����У��*/
			Comm_Response_Set_ReadErr(C_OK, pV_645Frame);
			return;
		case		C_ClearCalRegOK:			/*����У��ɹ�*/
			SV_Comm_Parse_Local.MeterClearFlag = SV_Comm_Parse_Local.MeterClearFlag |C_W_SafeFlag_3;
			Cal_ClearAllCalReg(pV_645Frame);
			return;
		case		C_NOStartCalibration:		/*У��״̬���󣬼�δ����У��*/
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
			if(V_ReturnData == C_OK)/*У����ȷ,�����ֿ�д���ǵ���д*/
			{
				if(Cal_DI0_Num == 0x01)
				{/*����д*/
					V_ReturnData = Write_OneCalRegToData(pV_645Frame->Data[C_O_DI0], &pV_645Frame->Data[C_O_Data_Cal]);
					Comm_Response_Set_ReadErr(V_ReturnData, pV_645Frame);
				}
				else if(Cal_DI0_Num == 0x03)
				{/*��д*/
					for( i = 0; i < Cal_DI0_Num; i++ )
					{																	/*У���������ΪΪ3*/
						V_ReturnData = Write_OneCalRegToData(Cal_DI0Buf_ForBlock[i], &pV_645Frame->Data[C_O_Data_Cal + 3 * i]);
						if(V_ReturnData != C_OK)
						{
							Comm_Response_Set_ReadErr(V_ReturnData, pV_645Frame);
							return;
						}
					}
					/*��д����*/
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
����ԭ�� 	Cal_ClearAllCalReg
��������	����У��Ĵ���
�������	*pV_645Frame				:���յ�������֡
				SV_Comm_Parse_Local.SafeControlFlag
				SV_Comm_Parse_Local.MeterClearFlag
������� 	��
���ز���	��
ȫ�ֱ��� 	��
������ע	��
***************************************************************************/
void		Cal_ClearAllCalReg(Str_Comm_645 *pV_645Frame)
{
	uchar8	CalRegData[3] = {0, 0, 0};
	uchar8	i;
	uchar8	V_ReturnData;

/*ѭ������*/
	for( i = 0; i < C_MeterICDataNum_T; i++ )
	{
		if(SV_Comm_Parse_Local.MeterClearFlag == C_W_SafeFlag)
		{/*�����־��ȷ����ȫ���Ʊ�־���ڵ���д�������ж�������*/
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
����ԭ�� 	Write_OneCalRegToData�����¼���¼
��������	дһ��У��Ĵ��������ݲ㣬�����¼���¼
�������	CalRegInData_No			:���ݲ��У��Ĵ������
				pCalReg					:�µ�У�����ݣ����ȹ̶�Ϊ3�ֽ�
				SV_Comm_Parse_Local.SafeControlFlag
������� 	��
���ز���	C_OK/C_Cal_NoErr/C_Cal_SafeFlagErr/C_Cal_WrDataErr
ȫ�ֱ��� 	���������
������ע	��
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

/*�����ж�����Ƿ����*/
	if(CalRegInData_No >= C_MeterICDataNum_T)
	{
		return(C_Cal_NoErr);
	}
/*����Ӧ��У���¼���¼���жϸüĴ�����û��д��У���¼*/
	CalEventDI = (ulong32) (CalRegInData_No + 1);		/*У���¼��У�������1��ʼ�����ݲ��0��ʼ*/
	CalEventDI = (CalEventDI << 8) & 0x0000FF00;
	CalEventDI = CalEventDI | (CRec_Meter_Bef1_Data_1 & 0xFFFF00FF);
	DataLen = CLRec_Meter_Bef1_Data_1;
	V_ReturnData = InF_Read_Data(CalEventDI, CalEventData, &DataLen, &V_usDataEncode);
	if( ( V_ReturnData == C_OK ) && ( CalEventData[C_HaveWrCalEventFlag_O] ==  C_IsNotWrCalEvent ) )
	{/*��Ӧ�¼���¼�ܶ�������δд��*/
		DataLen = 3;			/*У������̶���3�ֽ�*/
		V_ReturnData = InF_Read_RecMeterData(CalRegInData_No, &CalEventData[C_PreCalReg_O], (uchar8 *)&DataLen);
		if(V_ReturnData != C_OK)
		{/*��������Ϊ��1��Ϊ0*/
			CalEventData[C_PreCalReg_O] = 0;
			CalEventData[C_PreCalReg_O+1] = 0;
			CalEventData[C_PreCalReg_O+2] = 0;
		}
		CalEventData[C_HaveWrCalEventFlag_O] = C_HaveNotWrCalEvent;
		InF_Write_Data(C_Msg_Communication, CalEventDI,CalEventData, CLRec_Meter_Bef1_Data_1, SV_Comm_Parse_Local.SafeControlFlag);
	}/*�¼���¼д���˲��ܣ�������Ϊд����ֱ���˳���������Flash��������У����*/
/*д���ݲ�У�����*/
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
����ԭ�� 	Cal_WriteCalStartClock
��������	д����У��
�������	SV_Comm_Parse_Local.SafeControlFlag
				*pV_645Frame				:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	SV_Comm_Parse_Local.SafeControlFlag
������ע	��
***************************************************************************/
void			Cal_WriteCalStartClock(Str_Comm_645 *pV_645Frame)
{
	ushort16	DataLen = CLDate_Time, V_usDataEncode;
	uchar8	SystemClock[CLDate_Time];
	uchar8	V_ReturnData;

	if(InF_Read_Data(CDate_Time, SystemClock, &DataLen, &V_usDataEncode) != C_OK)
	{/*���ʱ�Ӷ���������Ĭ��Ϊ2000��1��1�գ�ʱ�䲻��*/
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
����ԭ�� 	Cal_SetPassword
��������	У��������������кź�У�����������Ӧ��
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	��
������ע	�ж�У�������Ƿ���ȷ������ȷ������д����ȷ������д��
				��λ��ͨ����ȡ���кţ������Լ������ݿ����У��
				����鲻����ֻ�ܸ���E2�󣬲���д��
***************************************************************************/
#define		C_O_CalNo		6
#define		C_O_CalPW		11
void		Cal_SetPassword(Str_Comm_645 *pV_645Frame)
{
	uchar8	V_ReturnData;
	ushort16	DataLen, V_usDataEncode;
	uchar8	buf[CLRec_MeterPassWord];

/*��ȡ���ݲ�У�����룬����ܶ�����������д��*/
	DataLen = CLRec_MeterPassWord;
	V_ReturnData = InF_Read_Data(CRec_MeterPassWord, buf, &DataLen, &V_usDataEncode);
	if(V_ReturnData == C_OK)
	{/*����Ӧ�����Ȩ*/
		Comm_Response_Set_ReadErr(C_Cal_PWOkButSetCPW, pV_645Frame);
		return;
	}
/*����������ʾ����д��*/
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
����ԭ�� 	Comm_ReadNxtFrameParse
��������	��ɺ���֡����
�������	*pV_645Frame					:��Ϣ֡
������� 	��
���ز���	��
ȫ�ֱ��� 	ͨ������
������ע	��
***************************************************************************/
void		Comm_ReadNxtFrameParse(Str_Comm_645 *pV_645Frame)
{
	Str_Comm_NxtFrame	Comm_NxtFrame;
	Str_Comm_NxtFrame	*pStr_Comm_NxtFrame;
	uchar8	DataLen;
	uchar8	i;

	pStr_Comm_NxtFrame = &Comm_NxtFrame;

/*�жϳ���*/
	if(pV_645Frame->DataLen != 0x05)
	{
		return;			/*���Ȳ��ԣ�ʲô���������˳���*/
	}
/*��ȡͨ������֡����*/
	if( Get_SV_CommNxtFrame( pV_645Frame->ChannelNo, pStr_Comm_NxtFrame ) != C_OK )
	{
		return;			/*����ʲô��������*/
	}

/*�����ж��ܵı�ʶ���Ƿ���ȷ������ȷӦ����������,NxtF_DataCode=0xFFFFFFFF��ʾ�Ѿ�û�к�������ʱ������Ϊ�����ϱ�*/
	if( ( NxtF_DataCode != pV_645Frame->DI ) && ( NxtF_DataCode != 0xFFFFFFFF ) )
	{
		Comm_Response_Set_ReadErr(C_OtherErr, pV_645Frame);
		return;
	}
	if(NxtF_DataCode == 0xFFFFFFFF)
	{
		NxtF_FrameFinished = C_OK;
	}
/*�ж�֡����Ƿ���ȷ*/
	if( ( NxtF_FrameNo == ( pV_645Frame->Data[C_O_FrameNo] + 1 ) )
	 && ( pV_645Frame->Data[C_O_FrameNo] != 0 ) )
	{/* ֡�������1֡���ض�����ʱ���ж���û�й�����Ϣ�����ϱ�*/
		if(NxtF_HaveReport == C_OK)
		{/*�б�ʾ������Ϣ״̬���ض�*/
			if( Judge_ReportWithNxtFrame() == C_OK )
			{/*�������ϱ���pV_645Frame->Data[C_O_FrameNo+1]��ʼ*/
				Set_ReportStateFrame(&pV_645Frame->Data[C_O_FrameNo + 1], &DataLen);
				/*֡���ֱ��ȡ�������ġ�*/
				pV_645Frame->Data[C_O_FrameNo + 1 + DataLen] = pV_645Frame->Data[C_O_FrameNo];
				DataLen++;
				/*�÷�������*/
				Comm_Response_FromP_Normal(pV_645Frame,&pV_645Frame->Data[C_O_FrameNo + 1], DataLen);
				/*�����ѷ��Ͷ�ʱ������λ�ѷ���״̬�ֽ�*/
				Set_SV_HaveReportState(&pV_645Frame->Data[C_O_FrameNo + 1 + CLen_DI]);
				NxtF_HaveReport = C_OK;
				Set_SV_CommNxtFrame(pV_645Frame->ChannelNo, pStr_Comm_NxtFrame);
			}
			else
			{/*�������ϱ�,Ӧ������������*/
				Init_SV_CommNxtFrame(pV_645Frame->ChannelNo);
				Comm_Response_Set_ReadErr(C_OtherErr_645, pV_645Frame);
			}
			return;
		}
		else
		{/*û�б�ʾ��������֡�����ض�*/
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
	{/*֡��Ŵ���*/
		Comm_Response_Set_ReadErr(C_OtherErr_645, pV_645Frame);
	}
	else
	{/*��һ֡,�жϺ���֡�Ƿ���ɣ�������жϹ�����Ϣ�Ƿ���Ҫ�ϱ�*/
		if(NxtF_FrameFinished == C_OK)
		{/* ��ɣ��ж����������ϱ�*/
			if(Judge_ReportWithNxtFrame()==C_OK)
			{/*�������ϱ���pV_645Frame->Data[C_O_FrameNo+1]��ʼ*/
				Set_ReportStateFrame(&pV_645Frame->Data[C_O_FrameNo + 1], &DataLen);
				/*֡���ֱ��ȡ�������ġ�*/
				pV_645Frame->Data[C_O_FrameNo + 1 + DataLen] = pV_645Frame->Data[C_O_FrameNo];
				DataLen++;
				/*�÷�������*/
				Comm_Response_FromP_Normal(pV_645Frame, &pV_645Frame->Data[C_O_FrameNo + 1], DataLen);
				/*�����ѷ��Ͷ�ʱ������λ�ѷ���״̬�ֽ�*/
				Set_SV_HaveReportState(&pV_645Frame->Data[C_O_FrameNo + 1 + CLen_DI]);
				NxtF_HaveReport = C_OK;
				Set_SV_CommNxtFrame(pV_645Frame->ChannelNo, pStr_Comm_NxtFrame);
			}
			else
			{/*�������ϱ�,Ӧ������������*/
				Init_SV_CommNxtFrame(pV_645Frame->ChannelNo);
				Comm_Response_Set_ReadErr(C_OtherErr_645, pV_645Frame);
			}
			return;
		}
		else
		{/*����һ֡����	*/
			Comm_ReadNxtFrame(pV_645Frame, pStr_Comm_NxtFrame);
		}
	}

/*�����������������ϱ����˳�������ֻ������������֡����һ��*/
/*�ж��Ƿ���Ҫ����֡��������Ϣ�����ϱ�?*/
	if(Judge_ReportWithNxtFrame()==C_OK)
	{
		Comm_IfHaveNxtFrame_Set_C(pV_645Frame);	/*bit5���к���֡��־*/
	}
}

/*******************************************************************************
����ԭ�� Comm_ReadNxtFrame
�������� �����ĺ���֡����Ӧ��
������� *pV_645Frame:�յ�������֡
		 *pStr_Comm_NxtFrame:����֡��ؽṹ��
������� ��
���ز��� ��
ȫ�ֱ��� ��ͨ����ص�ȫ�ֱ���(ͨ���������ͺ���֡����)
������ע ����֡������ڣ����ͻ��������úá�
*******************************************************************************/
void Comm_ReadNxtFrame(Str_Comm_645 *pV_645Frame, Str_Comm_NxtFrame *pStr_Comm_NxtFrame)
{
	uchar8	V_ReturnData;
	ulong32	ReadDI;
	uchar8	TB_NxtFrame_LineNo;					/* 1�����к�*/
	uchar8	i;

/*��Nxt->sub��׼���ض�*/
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
	{	/*13�淶���ɼ�¼��ȡ*/
		V_ReturnData = NormalReadingLoadCurve(pV_645Frame, pStr_Comm_NxtFrame);
	}
	else if(Is_SeqReadingLoadCurve(NxtF_DataCode) == C_OK)
	{	/*����4�������߶�ȡ*/
		V_ReturnData = SeqReadingLoadCurve(pV_645Frame, pStr_Comm_NxtFrame);
	}
	else
	{	/*��������2����������ǹ̶���֡�����Ȳ���1������һ����,�õ��к�*/
		if((pV_645Frame->DI & C_JudgeDI0FF) == C_JudgeDI0FF)
		{
			ReadDI = pV_645Frame->DI;  /* 1������ʧ���������¼�DI0FF*/
		}
		else
		{
			ReadDI = (pV_645Frame->DI & 0xFFFFFF00) | 0x00000001;			/* 1�����������˴���*/
		}

		for( TB_NxtFrame_LineNo = 0; TB_NxtFrame_LineNo < C_TBNxtFrameNum; TB_NxtFrame_LineNo++ )
		{
			if(ReadDI == TB_NxtFrame[TB_NxtFrame_LineNo].DataCode)
			{
				break;
			}
		}

		if(TB_NxtFrame_LineNo >= C_TBNxtFrameNum)
		{/* 1�����в���ʧ�ܣ�Ӧ�������������˳���*/
			Init_SV_CommNxtFrame(pV_645Frame->ChannelNo);
			Comm_Response_Set_ReadErr(C_No_Request_data, pV_645Frame);
			return;
		}

		/*����1�����еķ������ò�ͬ�ĺ���C_Freeze_Method/C_Prog_SubDI_LBit4/C_CarryingSubDI*/
		if(TB_NxtFrame[TB_NxtFrame_LineNo].Method == C_Freeze_Method)
		{/*����ķ���*/
			V_ReturnData = ReadFreezeReg_NxtFrame(pStr_Comm_NxtFrame, pV_645Frame,TB_NxtFrame_LineNo);
		}
		else if(TB_NxtFrame[TB_NxtFrame_LineNo].Method == C_Prog_SubDI_LBit4)
		{/*�����ʶ��DI0���4λ�Ǵ����ķ����������̶�Ϊ0A*/
			V_ReturnData = ReadProgRecordReg_NxtFrame(pStr_Comm_NxtFrame, pV_645Frame, TB_NxtFrame_LineNo);
		}
		else if(TB_NxtFrame[TB_NxtFrame_LineNo].Method == C_Event_Method)
		{/*ʧ��������*/
			V_ReturnData = ReadCurrFFRecordReg_NxtFrame(pStr_Comm_NxtFrame, pV_645Frame, TB_NxtFrame_LineNo);
		}
		else
		{/*C_CarryingSubDI������Ŀǰû�У�Ӧ�����������˳�,�����ܵ�����*/
			Init_SV_CommNxtFrame(pV_645Frame->ChannelNo);
			Comm_Response_Set_ReadErr(C_OtherErr, pV_645Frame);
			return;
		}
	}

	/*��ͨ�Ż�����֡���*/
	Comm_SetFrameNo(pV_645Frame->ChannelNo, NxtF_FrameNo);
	NxtF_FrameNo++;
	if(V_ReturnData == C_HaveNxtFrame)
	{
		Comm_IfHaveNxtFrame_Set_C(pV_645Frame);					/*��ͨ�Ż������к���֡*/
		NxtF_FrameFinished = C_Error;							/*��ʾ�к���֡*/
		NxtF_HaveReport = C_Error;								/*��ʾδ�����ϱ���*/
	}
	else
	{
		NxtF_FrameFinished = C_OK;								/*��ʾû�к���֡*/
		NxtF_HaveReport = C_Error;								/*��ʾδ�����ϱ���*/
	}
	Set_SV_CommNxtFrame(pV_645Frame->ChannelNo, pStr_Comm_NxtFrame);
}

/*******************************************************************************
����ԭ�� Is_NormalReadingLoadCurve
�������� �ж��Ƿ�Ϊ�������������߱�ʶ��
������� DataCode:��ȡ�ı�ʶ��
������� ��
���ز��� C_OK/C_Error
ȫ�ֱ��� ��
������ע ��
*******************************************************************************/
uchar8 Is_NormalReadingLoadCurve(ulong32 DataCode)
{
/*DI3Ϊ06*/
	if( (DataCode & 0xFF000000) != 0x06000000 )
	{
		return(C_Error);
	}
/*DI2��0-6֮��*/
	if( (DataCode & 0x00FF0000) > 0x00060000 )
	{
		return(C_Error);
	}
/*DI1/DI0��0000-0002֮��*/
	if( (DataCode & 0x0000FFFF) > 0x00000002 )
	{
		return(C_Error);
	}
	return(C_OK);
}

/***************************************************************************
����ԭ�� 	Is_SeqReadingLoadCurve
��������	�ж��Ƿ�Ϊ�������������߱�ʶ��
�������	DataCode					:��ȡ�ı�ʶ��
������� 	��
���ز���	C_OK/C_Error
ȫ�ֱ��� 	��
������ע	��
***************************************************************************/
uchar8		Is_SeqReadingLoadCurve(ulong32	DataCode)
{
	ulong32	DI1Bak;
	ulong32	DI0Bak;

/*DI1Ϊ1-8 ��DI0����DI1��ͬ����ͬ��*/
	DI1Bak = DataCode & 0xFFFFFF00;
	DI0Bak = DataCode & 0x000000FF;
	switch(DI1Bak)
	{
		case		0x06100100:			/*��ѹ*/
		case		0x06100200:			/*����*/
			if( ( DI0Bak == 0 ) || ( ( DI0Bak > 0x00000003 ) && ( DI0Bak != 0xFF ) ) )
			{
				return(C_Error);
			}
			return(C_OK);
		case		0x06100300:			/*�й�����*/
		case		0x06100400:			/*�޹�����*/
		case		0x06100500:			/*��������*/
			if( ( DI0Bak > 0x00000003 ) && ( DI0Bak != 0xFF ) )
			{
				return(C_Error);
			}
			return(C_OK);
		case		0x06100600:			/*�й��޹�����*/
		case		0x06100700:			/* �������޹�����*/
			if( ( DI0Bak == 0 ) || ( ( DI0Bak > 0x00000004 ) && ( DI0Bak != 0xFF ) ) )
			{
				return(C_Error);
			}
			return(C_OK);
		case		0x06100800:			/*����*/
			if( ( DI0Bak == 0 ) || ( ( DI0Bak > 0x00000002 ) && ( DI0Bak != 0xFF ) ) )
			{
				return(C_Error);
			}
			return(C_OK);
		default:
			return(C_Error);
	}
}

/***********************���ɼ�¼645���ݱ�ʶ��Ӧ698���**************************/
const Str_LoadRecord645DITo698OAD Str_LoadRecord645To698[] =
{
	/*��ѹ��*/
	CPhaseA_Volage,			CEarlietRec1_Load,	CLVoltageA_Load,		0x00,
	CPhaseB_Volage,			CEarlietRec1_Load,	CLVoltageB_Load,		0x02,
	CPhaseC_Volage,			CEarlietRec1_Load,	CLVoltageC_Load,		0x04,
	/*������*/
	CPhaseA_Curr,			CEarlietRec1_Load,	CLCurrentA_Load,		0x06,
	CPhaseB_Curr,			CEarlietRec1_Load,	CLCurrentB_Load,		0x09,
	CPhaseC_Curr,			CEarlietRec1_Load,	CLCurrentC_Load,		0x0C,
	/*Ƶ����*/
	CElecNet_Freq,			CEarlietRec1_Load,	CLElecNet_Freq,			0x0F,
	/*�й�������*/
	CInstant_TolAcPow,		CEarlietRec2_Load,	CLActPowerT_Load,		0x00,
	CInstantA_AcPow,		CEarlietRec2_Load,	CLActPowerA_Load,		0x03,
	CInstantB_AcPow,		CEarlietRec2_Load,	CLActPowerB_Load,		0x06,
	CInstantC_AcPow,		CEarlietRec2_Load,	CLActPowerC_Load,		0x09,
	/*�޹�������*/
	CInstant_TolRePow,		CEarlietRec2_Load,	CLReActPowerT_Load,		0x0C,
	CInstantA_RePow,		CEarlietRec2_Load,	CLReActPowerA_Load,		0x0F,
	CInstantB_RePow,		CEarlietRec2_Load,	CLReActPowerB_Load,		0x12,
	CInstantC_RePow,		CEarlietRec2_Load,	CLReActPowerC_Load,		0x15,
	/*����������*/
	CTol_PowerFactor,		CEarlietRec3_Load,	CLPowFactorT_Load,		0x00,
	CPhaseA_PowerFactor,	CEarlietRec3_Load,	CLPowFactorA_Load,		0x02,
	CPhaseB_PowerFactor,	CEarlietRec3_Load,	CLPowFactorB_Load,		0x04,
	CPhaseC_PowerFactor,	CEarlietRec3_Load,	CLPowFactorC_Load,		0x06,
	/*���޹��ܵ�����*/
	CPos_Ac_Tol_En_0,		CEarlietRec4_Load,	CLPosActEnergyT_Load,	0x00,
	CRev_Ac_Tol_En_0,		CEarlietRec4_Load,	CLRevActEnergyT_Load,	0x04,
	CCom_Re1_Tol_En_0,		CEarlietRec4_Load,	CLComReAct1T_Load,		0x08,
	CCom_Re2_Tol_En_0,		CEarlietRec4_Load,	CLComReAct2T_Load,		0x0C,
	/*�������޹�������*/
	CQua1_Re_Tol_En_0,		CEarlietRec5_Load,	CLReActQuad1_Load,		0x00,
	CQua2_Re_Tol_En_0,		CEarlietRec5_Load,	CLReActQuad2_Load,		0x04,
	CQua3_Re_Tol_En_0,		CEarlietRec5_Load,	CLReActQuad3_Load,		0x08,
	CQua4_Re_Tol_En_0,		CEarlietRec5_Load,	CLReActQuad4_Load,		0x0C,
	/*��ǰ������*/
	CCurr_AcDemand,			CEarlietRec6_Load,	CLActDemand_Load,		0x00,
	CCurr_ReDemand,			CEarlietRec6_Load,	CLReActDemand_Load,		0x03,
};
#define Str_LoadRecord645To698_Len	sizeof(Str_LoadRecord645To698) / sizeof(Str_LoadRecord645DITo698OAD)

/***********************************��������645���ݱ�ʶ��Ӧ698���*****************************************/
const Str_698To645LoadReadStatus Str_645To698LoadStatus[]=
{
	/*��ѹ��*/
	CPhaseA_Volage,     	1,  0xFF,  	CVoltageA_Load,			CLVoltageA_Load,
	CPhaseB_Volage,     	1,  0xFF,  	CVoltageB_Load,			CLVoltageB_Load,
	CPhaseC_Volage,     	1,  0xFF,  	CVoltageC_Load,			CLVoltageC_Load,
	CPhaseFF_Volage,    	1,  0xFF,  	CVoltageBlock_Load,		CLVoltageBlock_Load,
	/*������*/
	CPhaseA_Curr,       	1,	0xFF,  	CCurrentA_Load,			CLCurrentA_Load,
	CPhaseB_Curr,       	1,	0xFF,  	CCurrentB_Load,			CLCurrentB_Load,
	CPhaseC_Curr,       	1,	0xFF,  	CCurrentC_Load,			CLCurrentC_Load,
	CPhaseFF_Curr,      	1,	0xFF,  	CCurrentBlock_Load,		CLCurrentBlock_Load,
	/*�й�������*/
	CInstant_TolAcPow,  	1,	0xFF,  	CActPowerT_Load,		CLActPowerT_Load,
	CInstantA_AcPow,    	1,	0xFF,  	CActPowerA_Load,		CLActPowerA_Load,
	CInstantB_AcPow,    	1,	0xFF,  	CActPowerB_Load,		CLActPowerB_Load,
	CInstantC_AcPow,    	1,	0xFF,  	CActPowerC_Load,		CLActPowerC_Load,
	CInstantFF_AcPow,   	1,	0xFF,  	CActPowerBlock_Load,	CLActPowerBlock_Load,
	/*�޹�������*/
	CInstant_TolRePow,  	1,  0xFF,  	CReActPowerT_Load,		CLReActPowerT_Load,
	CInstantA_RePow,    	1,  0xFF,  	CReActPowerA_Load,		CLReActPowerA_Load,
	CInstantB_RePow,    	1,  0xFF,  	CReActPowerB_Load,		CLReActPowerB_Load,
	CInstantC_RePow,    	1,  0xFF,  	CReActPowerC_Load,		CLReActPowerC_Load,
	CInstantFF_RePow,   	1,  0xFF,  	CReActPowerBlock_Load,	CLReActPowerBlock_Load,
	/*����������*/
	CTol_PowerFactor,   	1,  0xFF,  	CPowFactorT_Load,		CLPowFactorT_Load,
	CPhaseA_PowerFactor,	1,  0xFF,  	CPowFactorA_Load,		CLPowFactorA_Load,
	CPhaseB_PowerFactor,	1,  0xFF,  	CPowFactorB_Load,		CLPowFactorB_Load,
	CPhaseC_PowerFactor,	1,  0xFF,  	CPowFactorC_Load,		CLPowFactorC_Load,
	CPhaseFF_PowerFactor,	1,  0xFF,  	CPowFactorBlock_Load,	CLPowFactorBlock_Load,
	/*���޹��ܵ�����*/
	CPos_Ac_Tol_En_0,   	1,  0,      CPosActEnergyT_Load,	CLPosActEnergyT_Load,
	CRev_Ac_Tol_En_0,   	1,  0,      CRevActEnergyT_Load,	CLRevActEnergyT_Load,
	CCom_Re1_Tol_En_0,  	1,  0,      CComReAct1T_Load,		CLComReAct1T_Load,
	CCom_Re2_Tol_En_0,  	1,  0,      CComReAct2T_Load,		CLComReAct2T_Load,
	CTotEnergyBlock_698,	4,  0,      CTotEnergyBlock_Load,	CLTotEnergyBlock_Load,
	/*�������޹�������*/
	CQua1_Re_Tol_En_0,	    1,  0,      CReActQuad1_Load,		CLReActQuad1_Load,
	CQua2_Re_Tol_En_0,	    1,  0,      CReActQuad2_Load,		CLReActQuad2_Load,
	CQua3_Re_Tol_En_0,	    1,  0,      CReActQuad3_Load,		CLReActQuad3_Load,
	CQua4_Re_Tol_En_0,	    1,  0,      CReActQuad4_Load,		CLReActQuad4_Load,
	CTotQua_Re_Block_698,	4,  0,      CReActQuadTBlock_Load,	CLReActQuadTBlock_Load,
	/*��ǰ������*/
	CCurr_AcDemand,     	1,	0xFF,	CActDemand_Load,		CLActDemand_Load,
	CCurr_ReDemand,     	1,	0xFF,	CReActDemand_Load,		CLReActDemand_Load,
	CCurr_Demand_Block, 	2,	0xFF,	CDemandBlock_Load,		CLDemandBlock_Load
};
#define Str_645To698LoadStatus_Len  sizeof(Str_645To698LoadStatus) / sizeof(Str_698To645LoadReadStatus)
/***********************************���ɼ�¼�Ķ�Ӧ698���*****************************************/
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

/***********************************���㶳��Ķ�Ӧ698���*****************************************/
const Str_698To645DFreezReadStatus Str_698To645HFreezRead[]=
{
	CFreeTime,     	        1,  CH_Free_Time_1,				CLH_Free_Time_1,
	CPos_Ac_Tol_En_0,     	1,  CH_Free_Pos_Ac_TolEn_1,    	CLH_Free_Pos_Ac_TolEn_1,
	CRev_Ac_Tol_En_0,     	1,  CH_Free_Rev_Ac_En_1,    	CLH_Free_Rev_Ac_En_1,
};
#define Str_698To645HFreezRead_Len  sizeof(Str_698To645DFreezRead)/sizeof(Str_698To645DFreezReadStatus)

/***************************************************************************
����ԭ�� 	SeqReadingLoadCurve_11
��������	11����������ȡ��������
�������	*pV_645Frame			:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	ͨ��ͨ��������
������ע	���뱾�����ʶ��϶���ȷ
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
����ԭ�� SF_LoadRecord645DITo698OAD
��������	 ���ɼ�¼645���ݱ�ʶת��Ϊ698���ݱ�ʶ
�������
�������
���ز���
ȫ�ֱ���
������ע ���뱾�����ʶ��϶���ȷ
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
����ԭ�� SF_LoadRecordingCodeConversion
��������	 645�����������ݱ�ʶת��Ϊ698�����б�
�������
�������
���ز���
ȫ�ֱ���
������ע ���뱾�����ʶ��϶���ȷ
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
����ԭ�� 	SeqReadingLoadCurve_11
��������	11����������ȡ��������
�������	*pV_645Frame			:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	ͨ��ͨ��������
������ע	���뱾�����ʶ��϶���ȷ
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
Description:������ʼʱ������ݲ��ʵ�ʸ��ɼ�¼��,ȡ����һʱ��
Input:	V_ulDataId-���ݱ�ʶ
		*P_ucInteTime-���ʱ��
		* P_ucReadStartTime -��ȡ���ɼ�¼����ʼʱ�䣬5�ֽڣ�YYMMDDhhmm��
		*P_ucStartTime-���縺�ɼ�¼�¼�,6�ֽ�
		*P_ucParaTime-������ʼʱ��
		* P_SendTime �C�������,����ʱ���׵�ַ,5�ֽ�
Output: * P_SendTime �Cʵ�ʷ��������е�һ�����ɼ�¼�ļ�¼ʱ��
Return:	V_ucflag,Ϊ0��ʾ�������¼��������C_ReCal��ʾ�����¼���
Calls:
Called By:SF_SepRead_LoadProfile
Influence:
Author:
Tips:
Others:
*****************************************************************************************/
uchar8 SF_FirstTime_LoadProfile(uchar8 *P_ucInteTime, uchar8 *P_ucReadStartTime, uchar8 *P_ucStartTime, uchar8 *P_ucParaTime, uchar8 *P_ucSendTime)
{
	uchar8 V_ucTimeBuff[CLLoad_Rec_Time_Year + 1];				/*��һʱ���м��������*/
	uchar8 V_ucflag = 0, V_ucIntTime = *P_ucInteTime;			/*���ʱ��*/
	ulong32 V_ulSubMins = 0;

	V_ucTimeBuff[C_Sec] = 0;									/*������ʱ����Ϊ6�ֽ�*/
	PF_CopyDataBytes(P_ucReadStartTime, &V_ucTimeBuff[C_Minute], CLLoad_Rec_Time_Year);               		/*����ʱ��*/

	if( PF_Campare_Data( &V_ucTimeBuff[C_Minute], &P_ucStartTime[C_Minute], C_LoadTimeLen ) == C_LessThan )	/*����ʱ������縺�ɼ�¼ʱ��*/
	{
		PF_CopyDataBytes(&P_ucStartTime[C_Minute], &V_ucTimeBuff[C_Minute], CLLoad_Rec_Time_Year);

		V_ucflag = C_ReCal;
	}
	PF_TimeSub_Min(V_ucTimeBuff, P_ucParaTime, &V_ulSubMins);	/*ȡ����ʱ���븺����ʼʱ���ֵ*/

	if( ( ( V_ulSubMins % V_ucIntTime ) != 0 ) && ( V_ucIntTime != 0 ) )		/*��ֵ�����������ʱ��,������ȡ���һ��������*/
	{
		V_ulSubMins = V_ucIntTime - ( V_ulSubMins % V_ucIntTime );

		SF_MinsAdd_LoadProfile(&V_ucTimeBuff[C_Minute], V_ulSubMins, &V_ucTimeBuff[C_Minute]);

		V_ucflag = C_ReCal;
	}
	PF_CopyDataBytes(&V_ucTimeBuff[C_Minute], P_ucSendTime, CLLoad_Rec_Time_Year);

	return V_ucflag;
}

/***************************************************************************
����ԭ�� 	SeqReadingLoadCurve_11
��������	11����������ȡ��������
�������	*pV_645Frame			:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	ͨ��ͨ��������
������ע	���뱾�����ʶ��϶���ȷ
***************************************************************************/
uchar8 SF_TimeZone_LoadProfile(uchar8 V_ucIntTime, uchar8 *P_ucBlockNum, uchar8 *P_ucTime, uchar8 *P_ucLoadEarTime, uchar8 *P_ucLoadStartTime, uchar8 *P_ucLoadEndTime)
{
	uchar8  V_ucCurrentTime[CLDate_Time];										/*���縺�ɼ�¼ʱ��͵�ǰʱ��*/
	uchar8  V_ucFirstTime[C_LoadTLength + 1], V_ucEndTime[C_LoadTLength + 1];	/*����������һ��ͽ�ֹ��ʱ��*/
	ulong32 V_ulSubMins = 0;
	uchar8  V_ucReturnTemp, V_ucFlag = 0, i;
	ushort16 V_ucLength, V_usDataEncode;
	uchar8  V_ucParaTime[CLLoad_Rec_Time_Year + 1] = {0x00, 0x00, 0x00, 0x01, 0x01, 0x19};
    uchar8  V_ucTime[6];

	V_ucFirstTime[C_Sec] = 0;													/*��λ��0,ʱ�����ʱʹ��*/
	V_ucEndTime[C_Sec] = 0;

	V_ucParaTime[C_Sec] = 0;

	V_ucLength = CLDate_Time;/*�˴�����ʱ��Ϊhex��ʽ��7�ֽ�ʱ�䣬���������ڻ����µ�����ʹ�õ�ʱ���ٺ˶ԣ�lzy 20211023*/
	InF_Read_Data(CDate_Time, V_ucCurrentTime, &V_ucLength, &V_usDataEncode);	/*��ȡ��ǰʱ��*/
	V_ucFlag = SF_FirstTime_LoadProfile(&V_ucIntTime, P_ucTime, &P_ucLoadEarTime[C_Sec], &V_ucParaTime[C_Sec], &V_ucFirstTime[C_Minute]);	/*��ȡ��һʱ��*/

	V_ucTime[0] = 0;
	memcpy(V_ucTime + 1, P_ucTime, 5);
	PF_TimeSub_Min(V_ucTime, V_ucParaTime, &V_ulSubMins);						/*ȡ����ʱ���븺����ʼʱ���ֵ*/
	if( ( ( V_ulSubMins % V_ucIntTime ) != 0 ) && ( V_ucIntTime != 0 ) )		/*��ֵ�����������ʱ��,������ȡ���һ��������*/
	{
		V_ulSubMins = V_ucIntTime - ( V_ulSubMins % V_ucIntTime );
		SF_MinsAdd_LoadProfile(P_ucTime, V_ulSubMins, &V_ucTime[C_Minute]);		/*����ʼʱ���һ*/
	}

	SF_MinsAdd_LoadProfile(V_ucTime + 1, (*P_ucBlockNum - 1) * V_ucIntTime, &V_ucEndTime[C_Minute]);	/*�������ֹʱ��*/

	if(PF_Campare_Data(&V_ucEndTime[C_Minute], &V_ucCurrentTime[C_Minute], C_LoadTimeLen) == C_GreaterThan)
	{
		PF_CopyDataBytes(&V_ucCurrentTime[C_Minute], &V_ucEndTime[C_Minute], C_LoadTimeLen);

		V_ucFlag = C_ReCal;
	}
	V_ucReturnTemp = PF_Campare_Data(&V_ucFirstTime[C_Minute], &V_ucEndTime[C_Minute], C_LoadTimeLen);

	if(V_ucReturnTemp == C_GreaterThan)
	{/*��һ������ʱ����ڽ�ֹʱ�䣬����������*/
		*P_ucBlockNum = 0;
		return C_NoData;
	}
	else if(V_ucReturnTemp == C_Equal)
	{
		*P_ucBlockNum = 1;
	}
	else if(V_ucFlag == C_ReCal)
	{
		PF_TimeSub_Min(V_ucEndTime, V_ucFirstTime, &V_ulSubMins);/*�����һʱ��ͽ�ֹʱ���ʱ���*/

		*P_ucBlockNum = V_ulSubMins / V_ucIntTime + 1;/*�����һʱ�������ܳ�������*/
	}
	for( i = 0; i < 6; i++ )
	{
		*(P_ucLoadStartTime + i) = V_ucFirstTime[i];
		*(P_ucLoadEndTime + i) = V_ucEndTime[i];
	}
	return V_ucReturnTemp;
}

/*******************************************************************************
����ԭ�� SeqReadingLoadCurve_11
�������� 11����������ȡ��������
������� *pV_645Frame:���յ�������֡
������� ��
���ز��� ��
ȫ�ֱ��� ͨ��ͨ��������
������ע ���뱾�����ʶ��϶���ȷ
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
	ulong32 V_IntervalTime32 = 0;	/*���ڼ������ʱ��*/
	ulong32 p_datacode[6] = {0x50020000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
	uchar8 V_TimeZone[12] = {0};
	uchar8 V_ReadOADLen = 0;
	uchar8 V_LastNumber = 0;
	uchar8 V_SuppleDataCycle = 0, V_SuppleDataType = 0;
	ushort16 V_usReadRecordNumOriginal = 0;
	uchar8 V_ucTotalNum = 0;
	uchar8 V_ucLoadStartTime[6] = {0, 0, 0, 0, 0, 0}, V_ucLoadEndTime[6] = {0, 0, 0, 0, 0, 0};
	uchar8 *V_DataSuppleTemp;
	uchar8 LenFor_Data = 0;			/*�������ɱ�д���ܵĳ���*/
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
		LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - 5 - 1;		/*��ȥ1��Ŀ�ģ�������Ҫ֡���*/
	}
	else
	{
		LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - 1;			/*��ȥ1��Ŀ�ģ�������Ҫ֡���*/
	}
	/*���ö�������ݷ���ֵ��λC*/
	/*V_ReturnData = SeqReadingLoadCurve(pV_645Frame,pStr_Comm_NxtFrame);*/

	/*******************645��ʽ���ɼ�¼��ʽ����Ϊ698���Ӷ����ʽ*****************/
	SF_LoadRecordingCodeConversion(NxtF_DataCode, (p_datacode + 1), &V_ReadOADLen, &V_SuppleDataType);	/*645ת698��ʶ��*/

	/***��ȡ��Ӧ�ķ��Ӷ�������,��ͬ�������в�ͬ***/
	V_ucDatacodeBufLen = 0x05;				/*ȥ����һ��OAD 0x50020200*/
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
	/*************************�ɶ���ʼʱ��ȷ������ʱ��**************************/
	V_IntervalTime32 = ( NxtF_LNxt_BlockNum ) * V_ucIntTime;
	PF_Ulong32ToBuffer4( V_IntervalTime8, &V_IntervalTime32, 4 );
	PF_Buffer4ToUlong32( V_IntervalTime8, &V_IntervalTime32, 4 );
	SF_MinsAdd_LoadProfile( NxtF_LNxt_Fix_Time, V_IntervalTime32, (V_EndTime + 1) );

	/*************************���ýӿں�����ȡ�����¼**************************/
	/***************��645�ķ�����ȡ����������������ʼ������ʱ��Ϳ���************/
	memset(V_SaveFreezeTimeBuf, 0x00, C_645FreezeTimeBufLen);				/*����ȥ���󽫻����е���������*/
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
		SF_MinsAdd_LoadProfile( ( V_ucLoadStartTime + 1 ), ( ( V_LastNumber - 1 ) * V_ucIntTime ), ( V_ucLoadEndTime + 1 ) );	/**����2�㷨��ǰ�պ�*/
		SF_MinsAdd_LoadProfile( ( V_ucLoadStartTime + 1 ), ( V_LastNumber * V_ucIntTime ), NxtF_LNxt_Fix_Time );				/**����2�㷨��ǰ�պ�*/
	}
	else
	{
		V_LastNumber = 0;	/*��ȡ���ݳ���Ϊ0��˵����ȡ����645�ĸ������߲�֧��,��ȡ����ֱ������*/
	}

	if(V_LastNumber != 0)
	{
		memcpy(V_TimeZone + 1, V_ucLoadStartTime + 1, 5);
		SF_MinsAdd_LoadProfile(V_ucLoadEndTime + 1, 1, V_TimeZone + 7);					/*����2�㷨��ǰ�պ�*/

		/******************��698����2�ķ�����ȡ�����ڵķ��Ӷ�������*************/
		V_usDataLen = C_645FreezeMAXRelatedOAD * C_698To645EnergyBlockLength + 5;
		V_ucRetrun = InF_ReadFreezeData(p_datacode, V_TimeZone, V_DataTemp, &V_usReadRecordNum, &V_usDataLen, V_ucIntTime, V_SaveFreezeTimeBuf, C_645Mode);

		/*************************�ж������Ƿ����0xBB*************************/
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

		/********************��ȡ��������б�****************************/
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
				/**********************0xBBΪ��Ч����**************************/
				if( ( V_DataTemp[V_ucDataTempOffset] == C_NotSupportAOD_DataBB )
				 && ( SF_Get_Active_OAD(p_datacode[V_ucOADNum] | V_ucPlanNum, &V_ulReadOADBuf_All[0], C_structure, C_End_EventState) == C_AAorBBIsDisactive) )
				{
					memset(&V_DataTempBuffer[V_ucDataBufferOffset], V_ucFillData, V_ucOADDatalen);
					V_ucDataBufferOffset += V_ucOADDatalen;
					V_ucDataTempOffset ++;
				}
				else		/******************0xBBΪ��Ч����******************/
				{
					PF_CopyDataBytes(&V_DataTemp[V_ucDataTempOffset],&V_DataTempBuffer[V_ucDataBufferOffset],V_ucOADDatalen);
					V_ucDataBufferOffset += V_ucOADDatalen;
					V_ucDataTempOffset += V_ucOADDatalen;
				}
			}
		}
		PF_CopyDataBytes(V_DataTempBuffer,V_DataTemp,V_ucDataBufferOffset);
		/**********************************************************************/
		V_usReadRecordNumOriginal = V_usReadRecordNum >> 2;												/*����2�������ļ�¼����*/
		SF_TimeSequencing(V_usReadRecordNumOriginal, V_SaveFreezeTimeBuf + 1, V_SequencingFreezeTime);	/*����2��ȡ��ʱ�䰴�մ�С����˳������*/
		memcpy(pV_645Frame->Data + 4, V_ucLoadStartTime + 1, 5);

		/*************************������2��ʼʱ��ǰ�������*********************/
		if(V_usReadRecordNumOriginal == 0)
		{
			V_usReadRecordNumOriginal = V_LastNumber;
			if(V_ucRetrun == C_NoData)
			{
				V_ucRetrun = 0;			/*�������2���������û�����ݣ��ѷ��ظĳ�OK*/
			}
			else
			{
				V_ucTotalNum = 0;		/*���û�кϷ������ݣ�ֱ�ӻ�0*/
			}
		}

		V_SuppleDataCycle = 0;
		j = 0;
		for( ; j < V_LastNumber; j ++)
		{
			for( ; V_SuppleDataCycle < V_usReadRecordNumOriginal; V_SuppleDataCycle ++ )		/*һ����Ҫ�������Ŀ���*/
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
										/**********************0xBBΪ��Ч����**************************/
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
	/*��֯Ӧ��֡*/
	if(V_ucRetrun != C_OK)
	{/*���ˡ�*/
		V_usDataLen = 0;
		Comm_11_03Response_Normal(pV_645Frame, V_DataTemp, V_usDataLen);
		V_ucRetrun = C_NoNxtFrame;
	}
	else
	{
		NxtF_LNxt_ReadedBlockNum += V_LastNumber;
		if(NxtF_FrameNo == 0)/*��֡*/
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
����ԭ�� ulong32 * P_Data_Id_OAD,uchar8 * P_FixTime,uchar8 * P_Data,ushort16 * V_BlockNum,ushort16 * V_Length,ushort16 V_IntervalTime,uchar8 *pV_FreezeTimeBuf,uchar8 V_Mode
�������� ��ȡ645���ɼ�¼����
�������
�������
���ز��� ���޺���֡(C_HaveNxtFrame/C_NoNxtFrame)
ȫ�ֱ���
������ע	 645���ɼ�¼������698���Ӷ���ת������
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

	/*****************645���ɼ�¼��ʽ����Ϊ698���Ӷ����ʽ**********************/
	SF_LoadRecord645DITo698OAD(V_ulDataCode645, &V_ulDataCode698Buffer[2], V_ucDataCode698LenBuffer, V_ucDataCode698OffsetBuffer);

	/*****************��ȡ��Ӧ�ķ��Ӷ�������,��ͬ�������в�ͬ********************/
	V_ucDatacodeBufLen = Str_LoadRecord645To698_Len + 1;	/*������೭��ʱOAD��Str_LoadRecord645To698_Len�������һ��Ϊ0xFFFFFFFF*/
	V_ucRetrunData = SF_GetMinFreezeCycle(&V_ulDataCode698Buffer[1], V_ucDatacodeBufLen, &V_ucPlanNum, &V_usFreezeCycle);
	if(V_ucRetrunData != C_OK)	/*�����Ų�ֱͬ�ӷ���*/
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
		&& (V_ucFrameNo == 0x00) )	/*�����¼����֡��ȡ��ֵ��ʼʱ��*/
	{
		/*****************��ȡ���ɼ�¼�����¼ʱ��************************************/
		V_usDataLength = 1024;
		V_ucRetrunData = InF_ReadFreezeData(V_ulDataCode698Buffer, P_ucFixTime, V_ucDataBuffer, &V_usBlockNumber, &V_usDataLength, V_usFreezeCycle, V_ucSaveFreezeTimeBuf, C_698EarLoadMode);
		if(V_ucRetrunData != C_698EarLoadMode)
		{
			return V_ucRetrunData;
		}
	}

	if(( (V_ulDataCode645 & 0x000000FF) == 0x00000000 )			/*�����¼���ȡ*/
		|| ( (V_ulDataCode645 & 0x000000FF) == 0x00000001 ) )		/*����ʱ���¼��*/
	{
		/*****************��ȡ��Ӧ�ķ��Ӷ�������************************************/
		V_ucTimeLength = CLDate_Time;/*�˴�����ʱ��Ϊhex��ʽ��7�ֽ�ʱ�䣬���������ڻ����µ�����ʹ�õ�ʱ���ٺ˶ԣ�lzy 20211023*/
		V_ucRetrunData = InF_Read_Data(CDate_Time, &P_ucFixTime[6], &V_ucTimeLength, &V_usDataEncode);		/*��ȡ��ǰʱ��*/
		P_ucFixTime[6] = 0x00;	/*������*/
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
	else if( (V_ulDataCode645 & 0x000000FF) == 0x00000002 )		/*���һ����¼��*/
	{
		/*****************��ȡ��Ӧ�ķ��Ӷ�������************************************/
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

	/********************��ȡ��������б�****************************/
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

		memset(&V_ucDataTemp[0],0xA0,0x02);		/*���ɼ�¼��ʼ��A0H��A0H*/
		V_ucDataTemp[2] = 0x00;					/*���ɼ�¼�ֽ������㣬�������ݿ������������ʵ�ʳ��ȸ�ֵ*/
		V_ucDataTempOffset = 0x03;

		/*���ɼ�¼�洢ʱ��Ϊ������ʱ��5�ֽڣ����ݲ��ȡ��ʱ��Ϊ������ʱ����6�ֽ�*/
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

			/********************�ж�0xBB�Ƿ�Ϊ��Ч����************************/
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
					/*0xBBΪ��Ч����*/
					if( (V_ucDataBuffer[V_usDataBufferOffset] == C_NotSupportAOD_DataBB)
						&& (SF_Get_Active_OAD(V_ulDataCode698Buffer[2 + V_ucDataCodeOffset] | V_ucPlanNum, &V_ulReadOADBuf_All[0], C_structure, C_End_EventState) == C_AAorBBIsDisactive) )	/*��Ч*/
					{
						V_ucDataCodeLen = 0;
						V_usDataBufferOffset ++;
						V_ucDataCodeOffset ++;
					}
					else	/*0xBBΪ��Ч����*/
					{
						V_usEnergyLen = CLPosActEnergyT_Load;
						SF_EnergyT0_645(&V_ucDataBuffer[V_usDataBufferOffset], &V_ucDataBuffer[V_usDataBufferOffset], &V_usEnergyLen, 4, (uchar8)(V_ulDataCode698Buffer[2 + V_ucDataCodeOffset] >> 16) );
						V_usDataBufferOffset += CLPosActEnergyT_Load;
						V_ucDataCodeOffset ++;
					}
				}
			}

			/*���ɼ�¼���ݱ���*/
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
			/*���ɼ�¼�ֽ���*/
			V_ucDataTemp[2] = V_ucDataTempOffset - 3;

			/*���ɼ�¼�ۼ�У����*/
			V_ucDataTemp[V_ucDataTempOffset] = 0x00;
			for(V_ucI = 0; V_ucI < V_ucDataTempOffset; V_ucI++)
			{
				V_ucDataTemp[V_ucDataTempOffset] += V_ucDataTemp[V_ucI];
			}
			V_ucDataTempOffset ++;

			/*���ɼ�¼������*/
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
			if( (V_usBlockNumber & 0x0003) != 0x0000 )	/*���ݲ��к���֡�������α��������*/
			{
				*V_ucBlockNum = *V_ucBlockNum - V_usI_Block;
				/*���ݲ��к���֡ʱ�����ݲ�᷵����һ֡��ʼʱ�䵽P_ucFixTime*/
			}
			else	/*���ݲ��޺���֡,�ұ��������*/
			{
				*V_ucBlockNum = 0;
			}
		}
		else	/*���α���δ���*/
		{
			*V_ucBlockNum = *V_ucBlockNum - V_usI_Block;
			/*����֡���ɼ�¼��ʼʱ�䣬���ݲ��ȡ��ʱ��Ϊ������ʱ����6�ֽ�*/
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
����ԭ�� NormalReadingLoadCurve
�������� ���������ɼ�¼
������� *pV_645Frame:�յ�������֡
		 *pStr_Comm_NxtFrame:����֡��ؽṹ��
������� pStr_Comm_NxtFrame.Nxt:����к���֡�������֡��ʼʱ�����ر���
���ز��� C_HaveNxtFrame/C_NoNxtFrame
ȫ�ֱ���
������ע
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
	V_ucDataLen = C_Comm_Data_MaxLen - CLen_DI - 1;		/*��ȥ1��Ŀ�ģ�������Ҫ֡���*/

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
����ԭ�� 	SeqReadingLoadCurve_11
��������	11����������ȡ��������
�������	*pV_645Frame			:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	ͨ��ͨ��������
������ע	���뱾�����ʶ��϶���ȷ
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
		return;			/*����ʲô��������*/
	}
/*11�����ú���֡ ����*/
	NxtF_DataCode = pV_645Frame->DI;
	NxtF_FrameNo = 0x00;
	for( i = 0; i < LClockLen; i++ )
	{
		NxtF_LNxt_Fix_Time[i] = pV_645Frame->Data[C_F3_O_GivenClock + i];
	}
	NxtF_LNxt_BlockNum = (pV_645Frame->Data[C_F3_O_BlockNum] & 0x0F) + (pV_645Frame->Data[C_F3_O_BlockNum] >> 4) * 10;

/*���ö�������ݷ���ֵ��λC*/
	V_ReturnData = SeqReadingLoadCurve(pV_645Frame,pStr_Comm_NxtFrame);

	if(V_ReturnData  == C_HaveNxtFrame)
	{
		Comm_IfHaveNxtFrame_Set_C(pV_645Frame);
		NxtF_FrameFinished = C_Error;										/*��ʾ�к���֡*/
		NxtF_HaveReport = C_Error;											/*��ʾδ�����ϱ���*/
		NxtF_FrameNo = 0x01;
		Set_SV_CommNxtFrame(pV_645Frame->ChannelNo, pStr_Comm_NxtFrame);	/*11�����ǲ��ü�֡��ŵġ�*/
	}
}
/*******************************************************************************
����ԭ�� Comm_11_Read
�������� ���11����Ľ�����Ӧ��
������� *pV_645Frame:�յ�������֡
������� ��
���ز��� ��
ȫ�ֱ��� ��ͨ����ص�ȫ�ֱ���
������ע ���������ж�֡��ʽ���¼����������жϡ�
*******************************************************************************/
void Comm_11_Read(Str_Comm_645 *pV_645Frame)
{
	ushort16 V_ucDataLen, V_usDataEncode, V_RTCLen;

/*����11�������ȳ�ʼ����ͨ������֡����*/
	Init_SV_CommNxtFrame(pV_645Frame->ChannelNo);

/*�ж��Ƿ��ȡ��I_Jʣ��ʱ��*/
	if(pV_645Frame->DI == 0x02FFFE01)
	{
		pV_645Frame->Data[C_11_SData] = SV_Comm_Parse.SI_JTimer.BaseTimer;
		PF_Ulong32ToBuffer4(&pV_645Frame->Data[C_11_SData + 1], &SV_Comm_Parse.SI_JTimer.Timer, 2);
		Comm_11_03Response_Normal(pV_645Frame, &pV_645Frame->Data[C_11_SData], 3);
		return;
	}

/*�ж��Ƿ��ȡͨ�ŵ�ַ*/
	if(pV_645Frame->DI == 0x04000401)
	{
		V_ucDataLen = CLComm_Address;
		InF_Read_Data(CComm_Address, &(pV_645Frame->Data[C_11_SData]), &V_ucDataLen, &V_usDataEncode);
		Comm_11_03Response_Normal(pV_645Frame, &pV_645Frame->Data[C_11_SData], CLComm_Address);
		return;
	}

/*��Ҫ��������������򸴵���У������޷��·�RTC�ռ�ʱУ׼����*/
	if(pV_645Frame->DI == 0x02800007)
	{
		V_RTCLen = CLMeter_Temp;
		InF_Read_Data(CMeter_Temp, &(pV_645Frame->Data[C_11_SData]), &V_RTCLen, &V_usDataEncode);
		Comm_11_03Response_Normal(pV_645Frame, &pV_645Frame->Data[C_11_SData], CLMeter_Temp);
		return;
	}

/*�ж��Ƿ񱾱���֧��*/
	if(IsMeterTypeSupport(pV_645Frame) != C_OK)
	{
		Comm_Response_Set_ReadErr(C_No_Request_data_645, pV_645Frame);
		return;		/*���ﲻ�ж������ϱ��ˡ�*/
	}

/*���ж�֡��ʽ���ж�*/
	if(pV_645Frame->DataLen == 0x04)
	{/*֡��ʽ1*/
		switch(pV_645Frame->Data[C_O_DI3])
		{
			case		0x00:				/*��������*/
				Comm_ReadEnergyReg(pV_645Frame);
				break;
			case		0x01:				/*��������*/
				Comm_ReadDemandReg(pV_645Frame);
				break;
			case		0x04:				/*�α�����*/
			case		0x02:
				Comm_Read_P_V_Reg(pV_645Frame);
				break;
			case		0x05:				/*��������*/
				Comm_ReadFreezeReg_11(pV_645Frame);
				break;
			case		0x10:				/*ʧѹ*/
			case		0x11:				/*Ƿѹ*/
			case		0x12:				/*��ѹ*/
			case		0x13:				/*����*/
			case		0x14:				/*��ѹ������*/
			case		0x15:				/*����������*/
			case		0x16:				/*��ѹ��ƽ��*/
			case		0x17:				/*������ƽ��*/
			case		0x20:				/*�������ز�ƽ��*/
			case		0x18:				/*ʧ��*/
			case		0x19:				/*����*/
			case		0x1A:				/*����*/
			case		0x1B:				/*���ʷ���*/
			case		0x1C:				/*����*/
			case		0x21:				/*��������*/
			case		0x1F:				/*��������������*/
			case		0x03:				/*������̡����ǵ��¼���*/
			case		0x1D:				/*��բ��¼*/
			case		0x1E:				/*��բ��¼*/
				Comm_Read_EventReg(pV_645Frame);
				break;
			default:
				Comm_Response_Set_ReadErr(C_OtherErr_645, pV_645Frame);
				break;
		}
	}
	else if(pV_645Frame->DataLen == 0x05)
	{/*֡��ʽ2*/
		if(Is_NormalReadingLoadCurve(pV_645Frame->DI) == C_OK)
		{/*��������������*/
			NormalReadingLoadCurve_11(pV_645Frame);
		}
		else
		{
			Comm_Response_Set_ReadErr(C_No_Request_data_645, pV_645Frame);
		}
	}
	else if(pV_645Frame->DataLen == 0x0A)
	{/*֡��ʽ3*/
		if(Is_NormalReadingLoadCurve(pV_645Frame->DI) == C_OK)
		{/*��������������*/
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

/*�ж��Ƿ���Ҫ����֡��������Ϣ�����ϱ�?*/
	if( ( Judge_ReportWithNxtFrame() == C_OK ) && ( pV_645Frame->DI != CDrive_Report_State_645 ) )
	{/*���ϱ��ұ�������������ϱ�����*/
		Comm_IfHaveNxtFrame_Set_C(pV_645Frame);	/*bit5���к���֡��־*/
	}
}
/***************************************************************************
����ԭ�� 	Comm_LCD_View
��������	Һ���鿴���������Ӧ��
�������	*pV_645Frame			:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	ͨ��ͨ��������
������ע	���뱾������ȱ�ʶ��϶���ȷ
***************************************************************************/
void		Comm_LCD_View(Str_Comm_645 *pV_645Frame)
{
	ulong32	V_ulCodeID;
	uchar8  V_ucDisplayMsg[20];

/*������ʾ�ӿں������ж��Ƿ�֧�ָñ�ʶ����ʾ*/
	PF_Buffer4ToUlong32(&pV_645Frame->Data[C_11_SData], &V_ulCodeID, CLen_DI);
/*����Ϣ����ʾģ�飬����ȷӦ��	*/
	Comm_11_03Response_Normal(pV_645Frame, &pV_645Frame->Data[C_11_SData], Pt_DisplayID_Len);
	PF_CopyDataBytes(&pV_645Frame->Data[C_11_SData], &V_ucDisplayMsg[1], Pt_DisplayID_Len);
	V_ucDisplayMsg[0] = Pt_DisplayID;
	V_ucDisplayMsg[6] = 10;
	V_ucDisplayMsg[7] = 0;
	Comm_SendMsg(&V_ucDisplayMsg[0], (Pt_DisplayID_Len + 1), C_Msg_Display);
}

/*******************************************************************************
����ԭ�� NormalReadingLoadCurve_11
�������� 11�������������ɼ�¼��Ӧ��
������� *pV_645Frame:���յ�������֡
������� ��
���ز��� ��
ȫ�ֱ��� ͨ��ͨ��������
������ע ���뱾�����ʶ��϶���ȷ
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
		return;		/*����ʲô��������*/
	}

	/*11�����ú���֡����*/
	NxtF_DataCode = pV_645Frame->DI;
	NxtF_FrameNo = 0x00;
	if(pV_645Frame->Data[C_O_DI0] == 0x01)
	{
		/*�������ݿ顢������ݿ��1�ζ���ʱ��ֵֻ��Ϊȫ0��ֻ�и���ʱ���������ʱ��*/
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
		NxtF_FrameFinished = C_Error;										/*��ʾ�к���֡*/
		NxtF_HaveReport = C_Error;											/*��ʾδ�����ϱ���*/
		NxtF_FrameNo = 0x01;
		Set_SV_CommNxtFrame(pV_645Frame->ChannelNo, pStr_Comm_NxtFrame);	/*11�����ǲ��ü�֡��ŵ�*/
	}
}

/***************************************************************************
����ԭ�� 	Is_EventReg_DI0FFOK
��������	�ж��Ƿ�����DI0=0xFF��ȡ�¼���¼���ݿ�
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	C_OK�����ȡ��C_No_Request_data��ʾ��֧�ָñ�ʶ���ȡ
ȫ�ֱ��� 	��
������ע	������ʧѹ�¼���¼��Ҫ�������⴦���ñ�ʶ�벻֧��DI0=0xFF��ȡ�¼���¼
	֧�������ʶ����¼���¼��ʧѹ��Ƿѹ����ѹ�����ࡢ��ѹ/���������򡢵�ѹ/������ƽ��
	ʧ�������������������ء������������ޡ��й����ʷ�������բ��¼
	�жϵ�ʱ��ֻ��Ҫ�жϴ����ʶ���DI3DI2����
***************************************************************************/
/*֧��DI0=0xFF���¼���¼�ı�ʶ��*/
#define	C_TB_DI0FFEventDI3DI2_Len		38
#define  C_KeepDI3DI2	0xFFFF0000
const	ulong32 TB_DI0FFEventDI3DI2[C_TB_DI0FFEventDI3DI2_Len] =
{
	(CLossA_Vol_Hp_1 & C_KeepDI3DI2),		/*ʧѹ*/
	(CLossB_Vol_Hp_1 & C_KeepDI3DI2),
	(CLossC_Vol_Hp_1 & C_KeepDI3DI2),
	(CLowA_Vol_Hp_1 & C_KeepDI3DI2),		/*Ƿѹ*/
	(CLowB_Vol_Hp_1 & C_KeepDI3DI2),
	(CLowC_Vol_Hp_1 & C_KeepDI3DI2),
	(COverA_Vol_Hp_1 & C_KeepDI3DI2),		/*��ѹ*/
	(COverB_Vol_Hp_1 & C_KeepDI3DI2),
	(COverC_Vol_Hp_1 & C_KeepDI3DI2),
	(CBreakA_Vol_Hp_1 & C_KeepDI3DI2),		/*����*/
	(CBreakB_Vol_Hp_1 & C_KeepDI3DI2),
	(CBreakC_Vol_Hp_1 & C_KeepDI3DI2),
	(CRevPS_Vol_Hp_1 & C_KeepDI3DI2),		/*��ѹ������*/
	(CRevPS_Curr_Hp_1 & C_KeepDI3DI2),		/*����������*/
	(CNoBal_Vol_Hp_1 & C_KeepDI3DI2),		/*��ѹ��ƽ��*/
	(CNoBal_Curr_Hp_1 & C_KeepDI3DI2),		/*������ƽ��*/
	(CSevNoBal_Curr_Hp_1 & C_KeepDI3DI2),	/*�������ز�ƽ��*/
	(CLossA_Curr_Hp_1 & C_KeepDI3DI2),		/*ʧ��*/
	(CLossB_Curr_Hp_1 & C_KeepDI3DI2),
	(CLossC_Curr_Hp_1 & C_KeepDI3DI2),
	(COverA_Curr_Hp_1 & C_KeepDI3DI2),		/*����*/
	(COverB_Curr_Hp_1 & C_KeepDI3DI2),
	(COverC_Curr_Hp_1 & C_KeepDI3DI2),
	(CBreakA_Curr_Hp_1 & C_KeepDI3DI2),		/*����*/
	(CBreakB_Curr_Hp_1 & C_KeepDI3DI2),
	(CBreakC_Curr_Hp_1 & C_KeepDI3DI2),
	(CPowerA_Rev_Hp_1 & C_KeepDI3DI2),		/*�й����ʷ���*/
	(CPowerB_Rev_Hp_1 & C_KeepDI3DI2),
	(CPowerC_Rev_Hp_1 & C_KeepDI3DI2),
	(COverA_Lo_Hp_1 & C_KeepDI3DI2),		/*����*/
	(COverB_Lo_Hp_1 & C_KeepDI3DI2),
	(COverC_Lo_Hp_1 & C_KeepDI3DI2),
	(CRelayOpen_Hp_T_1 & C_KeepDI3DI2),		/*��բ*/
	(CRelayClose_Hp_T_1 & C_KeepDI3DI2),	/*��բ*/
	(CPFactorT_Over_Hp_1 & C_KeepDI3DI2),	/*��������������*/
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
����ԭ�� 	Is_EventReg_DI0FFOK_Part
��������	   �ж��Ƿ�����DI0=0xFF��ȡ�¼���¼���ݿ�
�������	   *pV_645Frame				:���յ�������֡
�������    ��
���ز���	   C_OK�����ȡ��C_No_Request_data��ʾ��֧�ָñ�ʶ���ȡ
ȫ�ֱ���   ��
������ע	  ��֧�������ʶ����¼���¼��ʧ��������
	      �жϵ�ʱ��ֻ��Ҫ�жϴ����ʶ���DI3DI2����
***************************************************************************/
/*֧��DI0=0xFF���¼���¼�ı�ʶ��*/
#define	C_TB_DI0FFEventDI3DI2_Part_Len		6
const	ulong32 TB_DI0FFEventDI3DI2_Part[C_TB_DI0FFEventDI3DI2_Part_Len] =
{
	CLossA_Curr_FF_FF,	/*ʧ��*/
	CLossB_Curr_FF_FF,
	CLossC_Curr_FF_FF,
	COverA_Curr_FF_FF,	/*����*/
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
����ԭ�� 	Comm_Read_EventReg
��������	���¼���¼�Ĵ���
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	ͨ��ͨ��������
������ע	�����⴦���������ѡ���� ��ʣ�£��ȵ���
				�¼���¼ģ��Ķ��ӿں����������ޱ�ʶ�룬�ٵ������ݲ�
***************************************************************************/
uchar8 SF_EventClrRead_645(Str_Comm_645 *pV_645Frame, uchar8 *P_DataBuf, uchar8 *P_DataLength)
{/*645Э�鴦�������޸� lzy 20211102*/
#if 0
    ulong32 V_ulReadOADBuf[2];
    uchar8  V_timeFlash = 0x68, V_ucDataBuff = 0, V_ucRetrun, V_ucJudgeAll00;
    ushort16 V_usDataLen = 1024;
    uchar8  V_ucData[1024];
    ulong32 V_EventOAD = 0xFFFFFFFF;
    uchar8  i, V_ucHappening_Flag = C_End_EventState;

    V_ulReadOADBuf[0] = CEven_Clear_Degree_698 | (pV_645Frame->DI & 0x000000FF);
    V_ulReadOADBuf[1] = 0xFFFFFFFF;

    if( ( V_ulReadOADBuf[0] & 0x000000FF ) == 0x00000001 ) 					/*��1���¼���¼��ȡ*/
	{
		V_ucRetrun = Inf_ReadEventLast_H(V_ulReadOADBuf, V_ucData, &V_usDataLen, V_timeFlash, &V_ucHappening_Flag);
	}
    else
	{
		V_ucRetrun = InF_ReadEventData(V_ulReadOADBuf, &V_ucDataBuff, V_ucData, &V_ucDataBuff, &V_usDataLen, V_timeFlash);
	}
	if(V_ucRetrun == C_OK)
	{
        /*����ʱ��*/
        PF_CopyDataBytes(&V_ucData[C_DataOffset_Time], &P_DataBuf[0], ( CLEventHPTime - 1 ) );
        /*�����ߴ���*/
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
            /*���ݱ�ʶ*/
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
����ԭ�� 	Comm_Read_EventReg
��������	���¼���¼�Ĵ���
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	ͨ��ͨ��������
������ע	�����⴦���������ѡ���� ��ʣ�£��ȵ���
				�¼���¼ģ��Ķ��ӿں����������ޱ�ʶ�룬�ٵ������ݲ�
***************************************************************************/
void Comm_Read_EventReg(Str_Comm_645 *pV_645Frame)
{
	ushort16 LenFor_Data;
	uchar8   V_ReturnData, V_ucDataLen, V_ucBuffer[2];
	uchar8	 buf_O_CanWrite = 0;					/*��������д���ݵ�ƫ��*/
	uchar8   *pData;

	pData = &pV_645Frame->Data[C_11_SData];
	LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - buf_O_CanWrite ;
	/*���϶�У������,������֡*/
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
		if((pV_645Frame->DI & 0xFFFFFF00) == (CProgram_Note_1_645 & 0xFFFFFF00)) /*/��1-��10�α�̼�¼��������*/
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
			if( ( pV_645Frame->Data[C_O_DI3] == 0x03 ) && ( pV_645Frame->Data[C_O_DI0] == 0x00 ) ) 						/*�ۼƴ�����ʱ�䴦��*/
			{
     		  	V_ReturnData = Inf_ReadEventCurrentData_Com645(pV_645Frame->DI, pData, &V_ucDataLen, C_Flag03);
			}
			else if( ( ( ( (pV_645Frame->Data[C_O_DI3] >= 0x11 )&& ( pV_645Frame->Data[C_O_DI3] <= 0x20 ) )		/*�ۼƴ�����ʱ�䴦��*/
				    || ( pV_645Frame->Data[C_O_DI3] == 0x1B) || (pV_645Frame->Data[C_O_DI3] == 0x1D) || (pV_645Frame->Data[C_O_DI3] == 0x1E) )
				    || ( (pV_645Frame->Data[C_O_DI3] == 0x21) &&( (pV_645Frame->Data[C_O_DI0] == 0x00 ) ) ) )
			      && ( pV_645Frame->Data[C_O_DI1] == 0x00) )
			{
       			V_ReturnData = Inf_ReadEventCurrentData_Com645(pV_645Frame->DI, pData, &V_ucDataLen, C_Flagelse);
			}
			else if( ( pV_645Frame->Data[C_O_DI3] == 0x10 )		/*ʧѹ�ܴ��������ۼ�ʱ��*/
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
	{/*������ȷ����ʾ�¼���¼ģ��֧�ָüĴ�����ȡ��*/
		Comm_11_03Response_Normal(pV_645Frame, pData, V_ucDataLen);

	}
	else if(V_ReturnData == C_IDError)
	{/*��ʶ�����*/
		Comm_Response_Set_ReadErr(C_No_Request_data_645, pV_645Frame);
	}
	else
	{
		Comm_Response_Set_ReadErr(C_OtherErr_645, pV_645Frame);
	}
	return;
}
/***************************************************************************
����ԭ�� 	RD_ProgRecordReg
��������	���ܱ�̼�¼��ؼĴ���Ӧ��
�������	*pV_645Frame					:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	ͨ����صı���
������ע	�ܱ�̼�¼�б���ܴ�������1-��10�α�̼�¼�����������
***************************************************************************/
void RD_ProgRecordReg(Str_Comm_645 *pV_645Frame)
{
	uchar8	buf[3];
	uchar8	buf_O_CanWrite = 0;					/*��������д���ݵ�ƫ��*/
	ushort16	LenFor_Data, V_usDataEncode;	/*�������ɱ�д���ܵĳ���*/
	uchar8	*pData;
	uchar8	V_ReturnData;
/*ȡָ��*/
	pData = &pV_645Frame->Data[C_11_SData];
	LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - buf_O_CanWrite ;
/*�ж��Ƿ�Ϊ��̹����У�˳��ȡ������*/
	V_ReturnData = Get_ProgRecord1InRam(pData, &SV_Comm_Parse.ProgRecord);
	if(V_ReturnData == C_OK)
	{/*�����ڱ�̹�����*/
		if(pV_645Frame->DI == CProgram_Note_1)
		{/*Ϊ��1�α�̼�¼*/
			LenFor_Data = CLProgram_Note_1;
		}
		else if(pV_645Frame->DI == CProgram_Degree)
		{/*Ϊ����ܴ��������1*/
			V_ReturnData = InF_Read_Data(pV_645Frame->DI, pData, &LenFor_Data, &V_usDataEncode);
			buf[0] = 0x01;
			buf[1] = 0;
			buf[2] = 0;
			PF_BCDAddBytes(pData, buf, pData, LenFor_Data);
		}
		else
		{/*�����϶�Ϊ��2-��10�ν�DI0��1�����ݲ�*/
			V_ReturnData = InF_Read_Data((pV_645Frame->DI -0x00000001), pData, &LenFor_Data, &V_usDataEncode);
		}
	}
	else
	{/*���ڱ�̹�����,ֱ�Ӷ����ݲ�*/
		V_ReturnData = InF_Read_Data(pV_645Frame->DI, pData, &LenFor_Data, &V_usDataEncode);
	}
/*���ݷ���ֵ��Ӧ��*/
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
����ԭ�� 	RD_ProgRecordReg
��������	���ܱ�̼�¼��ؼĴ���Ӧ��
�������	*pV_645Frame					:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	ͨ����صı���
������ע	�ܱ�̼�¼�б���ܴ�������1-��10�α�̼�¼�����������
***************************************************************************/
void RD_ProgRecordReg_645(Str_Comm_645 *pV_645Frame)
{
	uchar8	buf[3];
	uchar8	buf_O_CanWrite = 0;					/*��������д���ݵ�ƫ��*/
	ushort16	LenFor_Data, V_usDataEncode;							/*�������ɱ�д���ܵĳ���*/
	uchar8	*pData;
	uchar8	V_ReturnData;
/*ȡָ��*/
	pData = &pV_645Frame->Data[C_11_SData];
	LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - buf_O_CanWrite ;
/*�ж��Ƿ�Ϊ��̹����У�˳��ȡ������*/
	V_ReturnData = Get_ProgRecord1InRam_645(pData, &SV_Comm_Parse.ProgRecord_645);
	if(V_ReturnData == C_OK)
	{/*�����ڱ�̹�����*/
		if(pV_645Frame->DI == CProgram_Note_1_645)
		{/*Ϊ��1�α�̼�¼*/
			LenFor_Data = CLProgram_Note_1_645;
		}
		else if(pV_645Frame->DI == CProgram_Degree)
		{/*Ϊ����ܴ��������1*/
			V_ReturnData = InF_Read_Data(CProgram_Degree_645, pData, &LenFor_Data, &V_usDataEncode);
			buf[0] = 0x01;
			buf[1] = 0;
			buf[2] = 0;
			PF_BCDAddBytes(pData, buf, pData, LenFor_Data);
		}
		else
		{/*�����϶�Ϊ��2-��10�ν�DI0��1�����ݲ�*/
			V_ReturnData = InF_Read_Data((pV_645Frame->DI - 0x00000001), pData, &LenFor_Data, &V_usDataEncode);
		}
	}
	else
	{/*���ڱ�̹�����,ֱ�Ӷ����ݲ�*/
		if(pV_645Frame->DI == CProgram_Degree)
		{
			V_ReturnData = InF_Read_Data(CProgram_Degree_645, pData, &LenFor_Data, &V_usDataEncode);
		}
		else
		{
			V_ReturnData = InF_Read_Data(pV_645Frame->DI, pData, &LenFor_Data, &V_usDataEncode);
		}
	}
/*���ݷ���ֵ��Ӧ��*/
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
����ԭ�ͣ�void InF_RD_ProgRecordReg(ulong32 V_ulDI, uchar8 *P_Buffer)
�������������ܱ�̼�¼��ؼĴ���,
���������V_ulDI��̼�¼��ʶ�룬	P_Buffer��ȡ���ݴ�ŵ�ַ
��������� *P_BufferΪ��ȡ��̼�¼����
���ز���	�� C_OK��ʾ��ȡ������ȷ��C_IDError���ݱ�ʶ���C_Error��������
����λ�ã� ͨ����صı���
��    ע�� �ܱ�̼�¼�б���ܴ�������1-��10�α�̼�¼��ͨ���ú�����ȡ
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
����ԭ�� 	RD_Pre1_FF_NoBalEvent
��������	����1�β�ƽ���ʼ���
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	ͨ��ͨ�Ż�����
������ע	��ƽ���¼�ָ:��ѹ���������������ز�ƽ��
				��ƽ�������¼���¼ģ���в�ƽ�������
***************************************************************************/
#define		C_O_NoBal		70
void		RD_Pre1_FF_NoBalEvent(Str_Comm_645 *pV_645Frame)
{
	uchar8	buf_O_CanWrite = 0;					/*��������д���ݵ�ƫ��*/
	ushort16	LenFor_Data, V_usDataEncode;							/*�������ɱ�д���ܵĳ���*/
	uchar8	*pData;
	uchar8	V_ReturnData;

/*ע��pData������DI����*/
	pData = &pV_645Frame->Data[C_11_SData];
	LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - buf_O_CanWrite ;
/*�����ݲ���1�εļ���*/
	V_ReturnData = InF_Read_Data(pV_645Frame->DI, pData, &LenFor_Data, &V_usDataEncode);
	if(V_ReturnData !=C_OK)
	{/*�����ܵ�����*/
		Comm_Response_Set_ReadErr(C_OtherErr,pV_645Frame);
		return;
	}
/*���¼���¼ģ��Ĳ�ƽ�������*/
	if(V_ReturnData != C_OK)
	{/*�����ܵ�����*/
		Comm_Response_Set_ReadErr(C_OtherErr,pV_645Frame);
		return;
	}
	Comm_11_03Response_Normal(pV_645Frame, pData,LenFor_Data);
}

/***************************************************************************
����ԭ�� 	RD_Pre1_FF_VoltageEvent
��������	����1�ε�ѹ���¼�����
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	ͨ��ͨ�Ż�����
������ע	��ѹ���¼�ָ:ʧѹ��Ƿѹ����ѹ������,��1��AH���¼���¼ģ�����
***************************************************************************/
#define		C_O_Total_Ah		109			/*�ܵ�A*/
void		RD_Pre1_FF_VoltageEvent(Str_Comm_645 *pV_645Frame)
{
	uchar8	buf_O_CanWrite = 0;					/*��������д���ݵ�ƫ��*/
	ushort16	LenFor_Data, V_usDataEncode;							/*�������ɱ�д���ܵĳ���*/
	uchar8	*pData;
	uchar8	i;
	uchar8	V_ReturnData;
	ulong32	Ah_DI1;

/*ע��pData������DI����*/
	pData = &pV_645Frame->Data[C_11_SData];
	LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - buf_O_CanWrite ;
/*�����ݲ���1�εļ���*/
	V_ReturnData = InF_Read_Data(pV_645Frame->DI, pData, &LenFor_Data, &V_usDataEncode);
	if(V_ReturnData !=C_OK)
	{/*�����ܵ�����*/
		Comm_Response_Set_ReadErr(C_OtherErr, pV_645Frame);
		return;
	}
/*��ǰAh�����¼���¼�ӿں������*/
	Ah_DI1 = 0x00002100;				/*21 22 23 24*/
	buf_O_CanWrite = C_O_Total_Ah;
	for( i = 0; i < 4; i++ )			/*�ܡ�ABC����ѭ������Ϊ4*/
	{
		Ah_DI1 = Ah_DI1 + 0x0100;
		if(V_ReturnData != C_OK)
		{/*�����ܵ�����*/
			Comm_Response_Set_ReadErr(C_OtherErr, pV_645Frame);
			return;
		}
		buf_O_CanWrite = buf_O_CanWrite + CLLossAVol_TolAh_1;
	}
	Comm_11_03Response_Normal(pV_645Frame, pData, LenFor_Data);
}

/***************************************************************************
����ԭ�� 	Is_Pre1_RFF_VoltageEvent
��������	�ж��Ƿ�������1�ε�ѹ���¼����϶�
�������	DataCode					:����ı�ʶ��
�������
���ز���	C_OK/C_Error
ȫ�ֱ���
������ע	��ѹ���¼�ָ:ʧѹ��Ƿѹ����ѹ������
***************************************************************************/
uchar8	Is_Pre1_RFF_VoltageEvent(ulong32	DataCode)
{
	switch(DataCode)
	{
		case		CLossAVol_FF_1:			/*ʧѹ��*/
		case		CLossBVol_FF_1:
		case		CLossCVol_FF_1:

		case		CLowAVol_FF_1:			/*Ƿѹ��*/
		case		CLowBVol_FF_1:
		case		CLowCVol_FF_1:

		case		COverAVol_FF_1:			/*��ѹ��*/
		case		COverBVol_FF_1:
		case		COverCVol_FF_1:

		case		CBreakAVol_FF_1:		/*������*/
		case		CBreakBVol_FF_1:
		case		CBreakCVol_FF_1:
			return(C_OK);
		default:
			return(C_Error);
	}
}

/***************************************************************************
����ԭ�� 	Read_EventRegWithNxtFrame
��������	������֡��ȡ�¼���¼
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	ͨ��ͨ��������
������ע	���ñ�����ǰ����֤DI�Ѿ��ж���ȫ��ȷ����Ϊ�к���֡
***************************************************************************/
void Read_EventRegWithNxtFrame(Str_Comm_645 *pV_645Frame)
{
	Str_Comm_NxtFrame	Comm_NxtFrame;
	Str_Comm_NxtFrame	*pStr_Comm_NxtFrame;
	uchar8	TB_NxtFrame_LineNo;						/* 1�����к�*/
	ulong32	*pTB_SubDI;								/*��֡��ʶ������*/
	uchar8	V_ReturnData;

	pStr_Comm_NxtFrame = &Comm_NxtFrame;
/*��ȡͨ������֡����*/
	if(Get_SV_CommNxtFrame(pV_645Frame->ChannelNo, pStr_Comm_NxtFrame) != C_OK)
	{
		return;										/*����ʲô��������*/
	}
	NxtF_DataCode = pV_645Frame->DI;

/*����1����*/
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
		}/*else��������*/
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
		/*���̶���֡��ʽ��ȡ�Ĵ�����*/
		/*ע��:1�������Ѿ��÷��ͻ�������pStr_Comm_NxtFrameֻ��Ҫ��Nxt_DataCode*/
		V_ReturnData = ReadCurrFFRecordReg_NxtFrame(pStr_Comm_NxtFrame, pV_645Frame, TB_NxtFrame_LineNo);
	}
	else
	{
		NxtF_Nxt_DataCode = pTB_SubDI[0] | ( pV_645Frame->DI & 0x0000000F );
		/*���̶���֡��ʽ��ȡ�Ĵ�����*/
		/*ע��:1�������Ѿ��÷��ͻ�������pStr_Comm_NxtFrameֻ��Ҫ��Nxt_DataCode*/
		V_ReturnData = ReadProgRecordReg_NxtFrame(pStr_Comm_NxtFrame, pV_645Frame, TB_NxtFrame_LineNo);
	}
	if(V_ReturnData  == C_HaveNxtFrame)
	{
		Comm_IfHaveNxtFrame_Set_C(pV_645Frame);
		NxtF_Sub_DataCode = NxtF_Nxt_DataCode;
		NxtF_FrameFinished = C_Error;										/*��ʾ�к���֡*/
		NxtF_HaveReport = C_Error;											/*��ʾδ�����ϱ���*/
		NxtF_FrameNo = 0x01;
		Set_SV_CommNxtFrame(pV_645Frame->ChannelNo, pStr_Comm_NxtFrame);	/*11�����ǲ��ü�֡��ŵġ�*/
	}
}

/***************************************************************************
����ԭ�� 	R_CarryingSubDIReg
��������	�ñ�ʶ�����ݲ㲻֧�֣����÷����ʶ���ȡ����
�������	*pV_645Frame				:���յ�������֡
				*pCarryingSubDI			:�������ʶ��һ�����е�����
������� 	��
���ز���	��
ȫ�ֱ��� 	ͨ�����ͨ�Ż�����
������ע	1����������Ȼ��֡�������޺���֡�ġ�
				2�������������ʶ���ǲ�����������Ϣ�ġ�
***************************************************************************/
void	R_CarryingSubDIReg(Str_Comm_645 *pV_645Frame, Str_TBCarryingSubDI_1 *pCarryingSubDI)
{
	uchar8	buf_O_CanWrite = 0;					/*��������д���ݵ�ƫ��*/
	ushort16	LenFor_Data, V_usDataEncode;	/*�������ɱ�д���ܵĳ���*/
	uchar8	*pData;
	uchar8	i;
	uchar8	V_ReturnData;
	ulong32	*pTBSubDI;							/* 2������׵�ַ*/
	uchar8	TBSubDILen;							/* 2������(��)*/

	pTBSubDI = pCarryingSubDI->pTB_SubDI;
	TBSubDILen = pCarryingSubDI->SubDINum;

/*ע��pData������DI����*/
	pData = &pV_645Frame->Data[C_11_SData];
	LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - buf_O_CanWrite ;
/*ѭ��������*/
	for( i = 0; i < TBSubDILen; i++ )
	{
		V_ReturnData = InF_Read_Data(pTBSubDI[i], &pData[buf_O_CanWrite], &LenFor_Data, &V_usDataEncode);
		if(V_ReturnData != C_OK)
		{/*���ܳ��ȴ����ޱ�ʶ�룬CRC���ԣ����ǲ�Ӧ�ó��ֵģ�Ӧ����������*/
			Comm_Response_Set_ReadErr(C_OtherErr, pV_645Frame);
			return;
		}
		/*����ָ���ʣ��ռ�*/
		buf_O_CanWrite = buf_O_CanWrite + LenFor_Data;				/*����LenFor_Data�����ݲ��д������������ʵ�ʳ����ˡ�*/

		if( buf_O_CanWrite > ( C_Comm_Data_MaxLen - CLen_DI ) )
		{/*�����ܵ����*/
			Comm_Response_Set_ReadErr(C_OtherErr, pV_645Frame);
			return;
		}

		LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - buf_O_CanWrite ;
	}
	Comm_11_03Response_Normal(pV_645Frame, pData,buf_O_CanWrite);
}
/***************************************************************************
����ԭ�� 	IsIn_TBCarryingSubDI_1
��������	���Ĵ������ʶ���1����ȷ���ܱ�ʶ���Ƿ���1�����У�
				�Ƿ�����ȷ������1�������ݷ���
�������	DataCode					:���ı�ʶ��
				pTBCarryingSubDI_1_Line	:һ�����к�ָ��
������� 	*pTBCarryingSubDI_1_Line	:һ�����е��к�
���ز���	C_OK					:��һ���������ص�
				C_Error					:��һ������δ���ص�
ȫ�ֱ��� 	��
������ע	Ŀǰ�������͹̶���֡��񣬷��������á�
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
����ԭ�� SF_ASCIItoChar(uchar8 *pData,uchar8 *pDataLen)
��������	 �����������������ΪASCII��ת��Ϊ�ַ�
�������	 pData����ASCII�����ݵ�ַ *pDataLen��ת�����ݳ���
������� pDataת��������	*pDataLenת�������ݳ���
���ز���	 �Ƿ�ת���ɹ� C_OK �ɹ�  C_Errorʧ��
ȫ�ֱ��� ��
������ע	 ASCII��ֻת��ȫAA��0-9�����ఴת��ʧ�ܡ�ת�����ȹ̶�Ϊ16�ֽ�ASCII��
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
			if(*(pData+i) == C_ASCII_A)												/*ȫAA*/
			{
				V_ucAANum++;
			}
			else if( (*(pData + i) < C_ASCII_0 ) || ( *(pData + i) > C_ASCII_9 ) )  /*ֻת��0-9*/
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
		else if(V_ucIllegalData_Num != 0)											/*���з�0-9����*/
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
����ԭ�� SF_ChartoASCII(uchar8 *pData,uchar8 *pDataLen)
��������	 ��������ΪCharת��ΪASCII
�������	 pData����Char���ݵ�ַ *pDataLen��ת�����ݳ���
������� pDataת��������	*pDataLenת�������ݳ���
���ز���	 �Ƿ�ת���ɹ� C_OK �ɹ�  C_Errorʧ��
ȫ�ֱ��� ��
������ע	 ת�����ȹ̶�Ϊ7�ֽ�Char,ת��5�ֽ�����ʱ��
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
����ԭ�� uchar8	SF_Read_AuthTime(ulong32 OAD,uchar8 *p_Data,ushort8 *Len)
��������	��ȡ������֤ʱЧ�������֤ʱЧ
�������	 OADҪ��ȡ�����ݱ�ʶ
������� ��ȡ�����ݵ�ַp_Data����ȡ�����ݳ���Len
���ز���	C_OK/C_Error
ȫ�ֱ���
������ע
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
            if(V_ulData > C_BCDMax_OneBit)			/*1�ֽ�BCD���99*/
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
            if(V_ulData > C_BCDMax_TwoBit)					/*2�ֽ�BCD���9999*/
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
    }/*else���ش���*/

    return V_Return;
}
/*******************************************************************************
����ԭ�ͣ�void		Comm_Read_P_V_Reg(Str_Comm_645 *pV_645Frame)
����������������
���������pV_645Frame �����ݵ���Ϣ
���������pV_645Frame ���ض������ݺʹ�����Ϣ״̬
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
void		Comm_Read_P_V_Reg(Str_Comm_645 *pV_645Frame)
{
	uchar8	buf_O_CanWrite = 0;						/*��������д���ݵ�ƫ��*/
	ushort16	LenFor_Data, V_usDataEncode;							/*�������ɱ�д���ܵĳ���*/
	uchar8	*pData;
	uchar8	V_ReturnData = C_OK;					/*Ĭ����������ȷ��*/
	uchar8	i, V_ucDataoff = 0;
    uchar8  j;
    ulong32 V_ulData = 0;
	ulong32	LimitDI;
	uchar8  V_ucTemp[2], V_ucLength, V_uck;
	ulong32 V_ulTemp;

/*ע��pData������DI����*/
	pData = &pV_645Frame->Data[C_11_SData];
	LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - buf_O_CanWrite ;

/*�ж��Ƿ�Ϊ����Ķ�ȡ*/
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
/*�ж��Ƿ�Ϊ������Ϣ�����ϱ���ʶ��*/
	if( pV_645Frame->DI == CDrive_Report_State_645 )
	{
		/*ȡ������Ϣ�����ϱ�����֡������DI��״̬�֡�����������*/
		Set_ReportStateFrame(pData, (uchar8 *)&LenFor_Data);
		/*�÷�������*/
		Comm_Response_FromP_Normal(pV_645Frame, pData, LenFor_Data);
		/*�����ѷ��Ͷ�ʱ������λ�ѷ���״̬�ֽ�*/
		Set_SV_HaveReportState(&pData[CLen_DI]);
		return;
	}

/*�жϱ�ʶ���Ƿ�ΪУ�����壬�ǹ̶�80ms*/
	if( pV_645Frame->DI == 0x04000105 )
	{
		pData[0] = 0x80;
		pData[1] = 0;
		LenFor_Data = 0x02;
		Comm_11_03Response_Normal(pV_645Frame, pData, LenFor_Data);
		return;
	}
/*�жϱ�ʶ���Ƿ�Ϊ�����ͺ����ڲ����������֣��̶�0x04*/
	if( pV_645Frame->DI == CMod_InFr_Baud_645 )
	{
		pData[0] = C_bps_1200;
		LenFor_Data = 0x01;
		Comm_11_03Response_Normal(pV_645Frame, pData, LenFor_Data);
		return;
	}
/*�ж��Ƿ��ȡ�ڲ��汾��*/
	if( pV_645Frame->DI == 0x04800010 )
	{
		PF_CopyDataBytes((uchar8 * )GV_C_Internal_Version, pData, CL_Internal_Version);
		LenFor_Data = CL_Internal_Version;
		Comm_11_03Response_Normal(pV_645Frame, pData, LenFor_Data);
		return;
	}
/*ʱ����ʱ�α����ʱ������Ŀ��ʱ�α���Ŀ����Ӧ��*/
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
/*�ж��Ƿ��ȡ��IJ��Чʱ��*/
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
/*���������ݲ㣬�������ݲ㷵��ֵ��ӦӦ��*/
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
						memset(pData+V_ucDataoff, 0x00, 4);				/*��Կ״̬�ֲ�0,4�ֽ�*/
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
					else if(pV_645Frame->DI == CSoftw_Record_Number_645)		/*Э�����ݸ�ʽ��ͬ��698ASCII��*/
					{
						V_ReturnData = SF_ASCIItoChar(pData, (uchar8 *)&LenFor_Data);
						if(V_ReturnData != C_OK)
						{
						   Comm_Response_Set_ReadErr(C_OtherErr_645, pV_645Frame);
						}
					}
					else if( ( pV_645Frame->DI == COne485_Baud_645 )        /*ͨ�ſ�1*/
						   || ( pV_645Frame->DI == CTwo485_Baud_645 ) )     /*ͨ�ſ�2*/
					{
						uchar8 bps;
						LenFor_Data = CLOne485_Baud_645;            /*645ͨ�ſ������ֳ���*/
						bps = SF_BPS698transfor645(pData[0]);             /*�洢����698��ʽ�ĳ�645*/
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
						V_ReturnData = SF_ChartoASCII( ( pData + 1 ), (uchar8 *)&LenFor_Data );	/*ȥ����20����*/
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
						V_ulData = V_ulData >> 12;												/*698Ϊ4λС����645Ϊ1λС��*/
						PF_Ulong32ToBuffer4(pData, &V_ulData, CLOverCurr_Curr_LowLim);
					}
					else
					{
						for(j = 0; j < C_TB_EventDelayTime_Len; j++)							/*�¼���ʱ����*/
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
		if( ( ( pV_645Frame->DI & 0xFFFFFF00 ) == 0x04000A00 )						/*���ɼ�¼��ʼ����ʱ��*/
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
						pV_645Frame->DI = TB_SetParmInFactoryState[V_uck].ParmDI;		/*���������ò���ת��698��־��*/
						LenFor_Data = TB_SetParmInFactoryState[V_uck].ParmLen;

						V_ReturnData = InF_Read_Data(pV_645Frame->DI, pData, &LenFor_Data, &V_usDataEncode);
						SF_InFactoryExchangeBCD( V_uck, pData );						/*��5��������BCD��HEX��ת��*/
						break;
					}
				}
			}
		}
    }
	if(V_ReturnData == C_IDError)
	{/*�޴˱�ʶ��*/
		Comm_Response_Set_ReadErr(C_No_Request_data_645, pV_645Frame);
	}
	else if(V_ReturnData != C_OK)
	{/*�������ʹ���һ��Ӧ����������*/
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
����ԭ�� 	Comm_ReadFreezeReg_11
��������	11�����ȡʱ����ʱ�α�����
�������	*pV_645Frame				:�յ�������֡
			LimitDI						:����DI������ʱ����(04000201)����ʱ����(04000203)
������� 	��
���ز���	��
ȫ�ֱ��� 	��ͨ����ص�ȫ�ֱ���
������ע	���뱾������DI3�϶�����05
***************************************************************************/
void	Comm_Read_TZone_PTReg(Str_Comm_645 *pV_645Frame, ulong32	LimitDI)
{
	uchar8	buf_O_CanWrite = 0;								/*��������д���ݵ�ƫ��	*/
	uchar8	*pData;
	uchar8	V_ReturnData;
	uchar8	LimintData;
	ushort16	LenFor_Data, DataLen = 1, V_usDataEncode;	/*�������ɱ�д���ܵĳ���*/
    uchar8 i;
    ulong32 V_ulDI;

/*645��ʶ��ת��Ϊ698��ʶ�루���ݲ�洢Ϊ698��ʶ�룩*/
	for(i = 0; i < Pstr_ParaChange_TZone_Len; i++ )
	{
		if(pV_645Frame->DI == Pstr_ParaChange_TZone[i].DI)
		{
			V_ulDI = Pstr_ParaChange_TZone[i].OAD;
			break;
		}
	}
   if(i == Pstr_ParaChange_TZone_Len)/*������*/
   {
     return;
   }

/*��ȡ��ʱ��������ʱ������1�ֽڡ�����Ĭ��14��*/
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

	/*ע��pData������DI����*/
	pData = &pV_645Frame->Data[C_11_SData];
	LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - buf_O_CanWrite ;

	V_ReturnData = InF_Read_Data(V_ulDI, pData, &LenFor_Data, &V_usDataEncode);
	if(V_ReturnData == C_IDError)
	{/*�޴˱�ʶ��*/
		Comm_Response_Set_ReadErr(C_No_Request_data, pV_645Frame);
	}
	else if(V_ReturnData != C_OK)
	{/*�������ʹ���һ��Ӧ����������*/
		Comm_Response_Set_ReadErr(C_OtherErr, pV_645Frame);
	}
	else
	{
		Comm_11_03Response_Normal(pV_645Frame, pData,( LimintData * 3 ) );
	}
}
/*******************************************************************************
����ԭ�ͣ�uchar8 SF_ReadDFreeze(ulong32 V_Data_Id, uchar8 * P_Data, uchar8 *P_Data_Length)
����������
���������
���������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_ReadDFreeze(ulong32 V_Data_Id, uchar8 * P_Data, uchar8 *P_Data_Length)
{
    ulong32  p_datacode[4] = {0x50040200, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
    uchar8   V_TimeZone[2], V_SaveFreezeTimeBuf[6];
    ushort16 V_usReadRecordNum = 0, LenFor_Data = CLD_Free_Pos_Ac_De_1, V_645Len = 0;
    uchar8   TB_SubDI_LineNo, V_ReturnData = C_OtherErr_645;
	uchar8   V_ucData_Temp[(C_MaxRatesNum + 1) * CLPos_Ac_Tol_De_0] = {0};

/*�������ӻ��涨�壬��Ϊ��698������������������Ϊ12��*/
/*�������645�ܼ����ʵ��ܼ��ϵĳ��ȶ��建��ײ��ȡ���ݻ���ֻ��治�������*/
    if( ( V_Data_Id & 0x0000FF00 ) != 0x0000FF00 )			/*�����Ѿ��й����ˣ�ֻ�з���ᵽ����*/
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
						if(LenFor_Data < CLPos_Ac_En_FF_1 )		/*Ԥ��������<4���*/
						{
							memset(&V_ucData_Temp[LenFor_Data], 0x00, (CLPos_Ac_En_FF_1 - LenFor_Data));
						}
				 		LenFor_Data = CLPos_Ac_En_FF_1;			/*���ڵ��ܼ��ϣ�645��ȡֻȡ�ܼ�ǰ4�����ʵ���*/
				 	}
					SF_EnergyT0_645(V_ucData_Temp, P_Data, &LenFor_Data, 4, (uchar8)(p_datacode[1]>>16) );
				}
				else if( ( ( p_datacode[1] & 0xFF000000 ) == 0x10000000 ) )
				{
					if( ( p_datacode[1] & 0x000000FF ) == 0x00000000 )
					{
						if( LenFor_Data < CLPos_Ac_De_FF_0_4Rate )		/*Ԥ��������<4���*/
						{
							memset(&V_ucData_Temp[LenFor_Data], 0x00, ( CLPos_Ac_De_FF_0_4Rate - LenFor_Data ) );
						}
				 		LenFor_Data = CLPos_Ac_De_FF_0_4Rate;			/*�����������ϣ�645��ȡֻȡ�ܼ�ǰ4�����ʵ���*/
				 	}
				  	memcpy(P_Data, V_ucData_Temp, LenFor_Data);
				}
				else
				{
				  	memcpy(P_Data, V_ucData_Temp, LenFor_Data);
				}
            }
            if(V_ReturnData != C_OK)									/*�޴�������ʱ�������б�û�����ã����²��Ҳ���*/
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
����ԭ�ͣ�uchar8 SF_ReadHFreeze(ulong32 V_Data_Id, uchar8 * P_Data, uchar8 *P_Data_Length)
����������Сʱ�����¼���¼
���������
���������
���ز�����
����λ�ã�
��    ע��
*******************************************************************************/
uchar8 SF_ReadHFreeze(ulong32 V_Data_Id, uchar8 * P_Data, uchar8 *P_Data_Length)
{
    ulong32  p_datacode[4] = {0x50030200, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
    uchar8   V_TimeZone[2], V_SaveFreezeTimeBuf[6];
    ushort16 V_usReadRecordNum = 0, LenFor_Data = CLFreeTime, V_645Len = 0;
    uchar8   TB_SubDI_LineNo, V_ReturnData = C_OtherErr_645;

    if( ( V_Data_Id & 0x0000FF00) != 0x0000FF00)			/*�����Ѿ��й����ˣ�ֻ�з���ᵽ����*/
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
*����ԭ�� 	Comm_ReadFreezeReg_11
*��������	11�����ȡ������Ĵ���
*�������	*pV_645Frame				:�յ�������֡
*������� 	��
*���ز���	��
*ȫ�ֱ��� 	��ͨ����ص�ȫ�ֱ���
*������ע	���뱾������DI3�϶�����05
****************************************************************************/
void		Comm_ReadFreezeReg_11(Str_Comm_645 *pV_645Frame)
{
	uchar8	buf_O_CanWrite = 0;					/*��������д���ݵ�ƫ��*/
	ushort16	LenFor_Data, V_usDataEncode;						/*�������ɱ�д���ܵĳ���*/
	uchar8	*pData;
	uchar8	V_ReturnData;
	ulong32	ReadDI;
	Str_Comm_NxtFrame NxtFrame;
	Str_Comm_NxtFrame *pNxtFrame;				/*����֡��������*/
	uchar8	TB_NxtFrame_LineNo;					/* 1�����к�*/
	ulong32	*pTB_SubDI;							/*��֡��ʶ������*/

	/*��ȡͨ������֡����*/
	pNxtFrame = &NxtFrame;
	if( Get_SV_CommNxtFrame(pV_645Frame->ChannelNo, pNxtFrame) != C_OK )
	{
		return;			/*����ʲô��������*/
	}
	/*ע��pData������DI����*/
	pData = &pV_645Frame->Data[C_11_SData];
	LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - buf_O_CanWrite ;

	/*�ж�DI=0����������ֱ�Ӷ�*/
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
/*�ж�DI1 != 0xFF����ʾ��������ݶ��������ڷ�֡����*/
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

/*DI1 == 0xFF������*/
/*Ŀǰ����ʱ��Լ�������㡢�ն�����м��ϣ�����DI2������ ���ڵ���8*/
	if(pV_645Frame->Data[C_O_DI2] >= 0x08)
	{
		Comm_Response_Set_ReadErr(C_No_Request_data_645, pV_645Frame);
		return;
	}
/*�жϼ��ϵĴ����Ƿ�����������øü����ж���ʱ��*/
/*����IsFreezeDataEnableRead���ж�ģʽ���Ƿ�Ϊȫ�պ�DI0�����Ƿ���ȷ*/
	if(IsFreezeDataEnableRead(pV_645Frame->DI & 0xFFFF00FF) != C_OK)
	{
		Comm_Response_Set_ReadErr(C_No_Request_data_645, pV_645Frame);
		return;
	}
/*�����DI3-0������ȷ�ġ�����DI1=FF��������*/
/*���Ȳ�һ����,�õ��к�*/
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

	/*Set_SV_CommNxtFrame����ͨ������֡ȫ�ֱ���*/
	pTB_SubDI = TB_NxtFrame[TB_NxtFrame_LineNo].pTB_SubDI;

	pNxtFrame->DataCode = pV_645Frame->DI;
	pNxtFrame->FrameNo = 0;

	ReadDI = pTB_SubDI[0] & 0xFF00FF00;		/*DI2 ��DI0�����ܵġ���Ϊ��������񲻰������������*/
	pNxtFrame->Nxt_DataCode = (pV_645Frame->DI & 0x00FF00FF) | ReadDI;

	V_ReturnData = ReadFreezeReg_NxtFrame(pNxtFrame, pV_645Frame, TB_NxtFrame_LineNo);
	if(V_ReturnData == C_HaveNxtFrame)
	{
		Comm_IfHaveNxtFrame_Set_C(pV_645Frame);
		pNxtFrame->Sub_DataCode = pNxtFrame->Nxt_DataCode;
		pNxtFrame->FrameFinished = C_Error;						/*��ʾ�к���֡*/
		pNxtFrame->HaveReport = C_Error;						/*��ʾδ�����ϱ���*/
		pNxtFrame->FrameNo = 1;
		Set_SV_CommNxtFrame(pV_645Frame->ChannelNo, pNxtFrame);	/*11�����ǲ��ü�֡��ŵġ�*/
	}
	else
	{
		Init_SV_CommNxtFrame(pV_645Frame->ChannelNo);
	}
}

/****************************************************************************
*����ԭ�� 	ReadFreezeReg_NxtFrame
*��������	������֡������ȡ����Ĵ�����ע�⣺����֡֡����������á�����ֻ����Ӧ�����ݡ�
*�������	*pSV_CommNxtFrame		:����֡����
*				*pV_645Frame				:���յ�������֡
*				TB_NxtFrame_LineNo		:1�����е��к�
*������� 	*pSV_CommNxtFrame.Nxt	:��һ�����ݷ����ʶ��
*���ز���	C_NoNxtFrame/C_HaveNxtFrame
*ȫ�ֱ���
*������ע	1�����ñ�����֮ǰ������������λ��û�и�ֵ��
*				2��ͨ������֡�����У�Nxt�ڱ��������ã���Sub��֡����������á�
*				3�����������ڴ���DI0������������DI2�����кϷ����жϡ�
*					��Ϊ��11������ñ�����ǰ�Ѿ��жϹ�����ô����֡�����е��ܵ�DI����ȷ�ģ�12�������Ҳ�����ٴ��жϡ�
****************************************************************************/
uchar8	ReadFreezeReg_NxtFrame (Str_Comm_NxtFrame *pSV_CommNxtFrame,Str_Comm_645 *pV_645Frame,uchar8 TB_NxtFrame_LineNo)
{
	uchar8	buf_O_CanWrite;						/*��������д���ݵ�ƫ��  */
	ushort16	LenFor_Data;					/*�������ɱ�д���ܵĳ���*/
	uchar8	*pData;
	uchar8	V_ReturnData;
	ulong32	*pTB_SubDI;							/* 2����ָ��   */
	uchar8	TB_SubDI_LineNo;					/* 2�����к�   */
	uchar8	TB_SubDI_MaxLineNo;					/* 2������     */
	ulong32	ReadDI;
    ulong32 p_datacode[14];
	uchar8   V_TimeZone[12], V_645Len = 0;
	ushort16 V_usReadRecordNum;
	uchar8 V_SaveFreezeTimeBuf[C_SaveFreezeTimeBufLen];
/*��ѯһ������ȡ2������ز���*/
	pTB_SubDI = TB_NxtFrame[TB_NxtFrame_LineNo].pTB_SubDI;
	TB_SubDI_MaxLineNo = TB_NxtFrame[TB_NxtFrame_LineNo].SubDINum;

    memset(p_datacode, 0xFF, 14 * 4);
/*ѭ����ѯ2����ȷ��2�������׸������ʶ���Ӧ��2�����к�*/
	ReadDI = pSV_CommNxtFrame->Nxt_DataCode;
	for(TB_SubDI_LineNo = 0; TB_SubDI_LineNo < TB_SubDI_MaxLineNo; TB_SubDI_LineNo++ )
	{/*����DI2/DI0�Ƚ�,��Ϊ��������ʶ���񲻰������ʹ���*/
		if( ( ReadDI & 0xFF00FF00 ) == ( pTB_SubDI[TB_SubDI_LineNo] & 0xFF00FF00 ) )
		{
			break;
		}
	}
	if(TB_SubDI_LineNo >= TB_SubDI_MaxLineNo)
	{/*���������Ҳ���*/
		Comm_Response_Set_ReadErr(C_No_Request_data, pV_645Frame);
		return(C_NoNxtFrame);
	}
/*ѭ����ѯ2����ķ����ʶ�룬�����ݲ�����*/
	/*ע��pData������DI����*/
	buf_O_CanWrite = 0;
	pData = &pV_645Frame->Data[C_11_SData];
	LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - buf_O_CanWrite - 2;			/*��ȥ2��Ŀ�ģ�������Ҫ����AA��֡���*/

	for( ; TB_SubDI_LineNo < TB_SubDI_MaxLineNo; TB_SubDI_LineNo++ )
	{
	/*����ȡ�����ʶ��,DI2/DI0ȡ�ܵı�ʶ���е�DI2/DI0*/
		ReadDI = pTB_SubDI[TB_SubDI_LineNo] & 0xFF00FF00;
		ReadDI = (pV_645Frame->DI & 0x00FF00FF) | ReadDI;
	/*�ж�ʣ���ֽ��Ƿ�д����֡���*/
		if(LenFor_Data < 1)
		{
			break;																/*TB_SubDI_LineNo���л�û���ж�*/
		}
	/*�жϸ÷����ʶ�룬ģʽ���Ƿ�֧�ֶ�	*/
		if(IsFreezeDataEnableRead(ReadDI) != C_OK)
		{/*�÷����ʶ�벻�ö�,����ʱ���ǿ϶��ö��ġ�*/
			pData[buf_O_CanWrite] = 0xAA;
			buf_O_CanWrite++;
			if( buf_O_CanWrite >= ( C_Comm_Data_MaxLen - CLen_DI - 2 ) )
			{
				break;
			}
			LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - buf_O_CanWrite - 2;
			continue;
		}
	/*�����ݲ�*/
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
				V_ReturnData = InF_ReadFreezeData(p_datacode,V_TimeZone, &pData[buf_O_CanWrite], &V_usReadRecordNum,&LenFor_Data, 15,V_SaveFreezeTimeBuf,C_698EarLoadMode);    /*************************��645�ķ�����ȡ����������������ʼ������ʱ��Ϳ���***************************/
				if(V_ReturnData == C_OK)	/*ֻ�ж�ȡ������ȷ�Ž������ݸ�ʽת��*/
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
							if(LenFor_Data < CLPos_Ac_En_FF_1 )		/*Ԥ��������<4���*/
							{
								memset(&pData[buf_O_CanWrite + LenFor_Data], 0x00, (CLPos_Ac_En_FF_1 - LenFor_Data));
							}

							LenFor_Data = CLPos_Ac_En_FF_1;			/*���ڵ��ܼ��ϣ�645��ȡֻȡ�ܼ�ǰ4�����ʵ���*/
						}
						SF_EnergyT0_645(&pData[buf_O_CanWrite], &pData[buf_O_CanWrite], &LenFor_Data, 4, (uchar8)(Str_698To645DFreezRead[TB_SubDI_LineNo].V_ulDataId698>>16));
					}
					else if(( (p_datacode[1] & 0xFF000000) == 0x10000000) )
					{
						if( (p_datacode[1]&0x000000FF) == 0x00000000)
						{
							if(LenFor_Data < CLPos_Ac_De_FF_0_4Rate )	/*Ԥ��������<4���*/
							{
								memset(&pData[buf_O_CanWrite + LenFor_Data], 0x00, (CLPos_Ac_De_FF_0_4Rate - LenFor_Data));
							}

							LenFor_Data = CLPos_Ac_De_FF_0_4Rate;				/*�����������ϣ�645��ȡֻȡ�ܼ�ǰ4�����ʵ���*/
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

            V_ReturnData = InF_ReadFreezeData(p_datacode,V_TimeZone, &pData[buf_O_CanWrite], &V_usReadRecordNum,&LenFor_Data, 15,V_SaveFreezeTimeBuf,C_698EarLoadMode);    /*************************��645�ķ�����ȡ����������������ʼ������ʱ��Ϳ���***************************/
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
		{/*�޴˱�ʶ�룬Ӧ�������������˳�.�����ܵ������!*/
			Comm_Response_Set_ReadErr(C_No_Request_data, pV_645Frame);
			return(C_NoNxtFrame);
		}
		/*���Ȳ������˳�ѭ��*/
		if(V_ReturnData == C_DataLenError)
		{
			break;
		}
		/*��������OK���ǲ����ܵģ����Ӧ�����������˳�*/
		if(V_ReturnData != C_OK)
		{
			Comm_Response_Set_ReadErr(C_OtherErr, pV_645Frame);
			return(C_NoNxtFrame);
		}
		/*OK�������������Ͽ�*/
		buf_O_CanWrite = buf_O_CanWrite + LenFor_Data;
		pData[buf_O_CanWrite] = 0xAA;
		buf_O_CanWrite++;

		if(buf_O_CanWrite >= (C_Comm_Data_MaxLen - CLen_DI - 2))
		{/*�����ܵ����*/
			break;
		}
		LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - buf_O_CanWrite - 2;
	}
/*��֯Ӧ��֡*/
	Comm_11_03Response_Normal(pV_645Frame, pData, buf_O_CanWrite);
/*�Ƿ��к���֡���ж�*/
	if(TB_SubDI_LineNo >= TB_SubDI_MaxLineNo)
	{/*�������ʶ������󣬱���������������*/
		return(C_NoNxtFrame);
	}

	for( ; TB_SubDI_LineNo < TB_SubDI_MaxLineNo; TB_SubDI_LineNo++ )
	{
		ReadDI = pTB_SubDI[TB_SubDI_LineNo] & 0xFF00FF00;
		ReadDI = (pV_645Frame->DI &0x00FF00FF) | ReadDI;
		pSV_CommNxtFrame->Nxt_DataCode = ReadDI;
		if(IsFreezeDataEnableRead(ReadDI) == C_OK)
		{
			return(C_HaveNxtFrame);	/*����ֻҪ��1�������ʶ������������к���֡*/
		}
	}
	return(C_NoNxtFrame);
}

/***************************************************************************
����ԭ�� 	ReadProgRecordReg_NxtFrame
��������	������֡������ȡ����¼���¼��ע�⣺����֡֡����������á�����ֻ����Ӧ�����ݡ�
�������	*pSV_CommNxtFrame		:����֡����
				*pV_645Frame				:���յ�������֡
				TB_NxtFrame_LineNo		:1�����е��к�
������� 	*pSV_CommNxtFrame.Nxt	:��һ�����ݷ����ʶ��
���ز���	C_NoNxtFrame/C_HaveNxtFrame
ȫ�ֱ���
������ע	1�����ñ�����֮ǰ������������λ��û�и�ֵ��
				2��ͨ������֡�����У�Nxt�ڱ��������ã���Sub��֡����������á�
				3�����������ڴ���DI0������������DI2�����кϷ����жϡ�
					��Ϊ��11������ñ�����ǰ�Ѿ��жϹ�����ô����֡�����е��ܵ�DI����ȷ�ģ�12�������Ҳ�����ٴ��жϡ�
				4)	�˴�������DI0�ĵ�4λ���϶�С��0x0A
***************************************************************************/
uchar8 ReadProgRecordReg_NxtFrame (Str_Comm_NxtFrame *pSV_CommNxtFrame, Str_Comm_645 *pV_645Frame, uchar8 TB_NxtFrame_LineNo)
{
	uchar8	buf_O_CanWrite;						/*��������д���ݵ�ƫ��*/
	ushort16	LenFor_Data, V_usDataEncode;							/*�������ɱ�д���ܵĳ���*/
	uchar8	*pData;
	uchar8	V_ReturnData;

	ulong32	*pTB_SubDI;						/* 2����ָ��*/
	uchar8	TB_SubDI_LineNo;					/* 2�����к�*/
	uchar8	TB_SubDI_MaxLineNo;					/* 2������*/

	ulong32	ReadDI;

/*��ѯһ������ȡ2������ز���*/
	pTB_SubDI = TB_NxtFrame[TB_NxtFrame_LineNo].pTB_SubDI;
	TB_SubDI_MaxLineNo = TB_NxtFrame[TB_NxtFrame_LineNo].SubDINum;

/*ѭ����ѯ2����ȷ��2�������׸������ʶ���Ӧ��2�����к�*/
	ReadDI = pSV_CommNxtFrame->Nxt_DataCode;
	for( TB_SubDI_LineNo = 0; TB_SubDI_LineNo < TB_SubDI_MaxLineNo; TB_SubDI_LineNo++ )
	{/*����DI0��4λ�Ƚ�,��Ϊ�����ʶ���񲻰�������*/
		if( ( ReadDI & 0xFFFFFFF0 ) == ( pTB_SubDI[TB_SubDI_LineNo] & 0xFFFFFFF0 ) )
		{
			break;
		}
	}
	if(TB_SubDI_LineNo >= TB_SubDI_MaxLineNo)
	{/*���������Ҳ���*/
		Comm_Response_Set_ReadErr(C_No_Request_data, pV_645Frame);
		return(C_NoNxtFrame);
	}
/*ѭ����ѯ2����ķ����ʶ�룬�����ݲ�����*/
	/*ע��pData������DI����*/
	buf_O_CanWrite = 0;
	pData = &pV_645Frame->Data[C_11_SData];
	LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - buf_O_CanWrite - 1;	/*��ȥ1��Ŀ�ģ�������Ҫ֡���*/

	for( ;TB_SubDI_LineNo < TB_SubDI_MaxLineNo; TB_SubDI_LineNo++ )
	{
	/*����ȡ�����ʶ��,DI2/DI0ȡ�ܵı�ʶ���е�DI2/DI0*/
		ReadDI = pTB_SubDI[TB_SubDI_LineNo] & 0xFFFFFFF0;
		ReadDI = (pV_645Frame->DI &0x0000000F) | ReadDI;
		pSV_CommNxtFrame->Nxt_DataCode = ReadDI;				/*������һ֡��*/
	/*�ж�ʣ���ֽ��Ƿ�д����֡���*/
		if(LenFor_Data < 1)
		{
			break;						/*TB_SubDI_LineNo���л�û���ж�*/
		}
	/*�����ݲ�*/
		if( ( ReadDI & 0xFFFFFF00 ) == CDe_Clear_Degree )
		{
			V_ReturnData = SF_Read_DemandEvent(ReadDI, pV_645Frame->Data[C_O_DI0], &pData[buf_O_CanWrite], (uchar8 *)&LenFor_Data);
		}
		else
		{
			V_ReturnData = InF_Read_Data(ReadDI, &pData[buf_O_CanWrite], &LenFor_Data, &V_usDataEncode);
		}
		if(V_ReturnData == C_IDError)
		{/*�޴˱�ʶ�룬Ӧ�������������˳�.�����ܵ������!*/
			Comm_Response_Set_ReadErr(C_No_Request_data, pV_645Frame);
			return(C_NoNxtFrame);
		}
	/*���Ȳ������˳�ѭ��*/
		if(V_ReturnData == C_DataLenError)
		{
			break;
		}
	/*��������OK���ǲ����ܵģ����Ӧ�����������˳�*/
		if(V_ReturnData != C_OK)
		{
			Comm_Response_Set_ReadErr(C_OtherErr, pV_645Frame);
			return(C_NoNxtFrame);
		}
	/*OK�������������Ͽ�*/
		buf_O_CanWrite = buf_O_CanWrite + LenFor_Data;

		if( buf_O_CanWrite >= ( C_Comm_Data_MaxLen - CLen_DI - 1 ) )
		{/*�����ܵ����*/
			break;
		}
		LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - buf_O_CanWrite - 1;
	}

/*��֯Ӧ��֡*/
	Comm_11_03Response_Normal(pV_645Frame, pData, buf_O_CanWrite);

	/*�Ƿ��к���֡���ж�*/
	if(TB_SubDI_LineNo >= TB_SubDI_MaxLineNo)
	{/*�������ʶ������󣬱���������������*/
		return(C_NoNxtFrame);
	}
	else
	{
		return(C_HaveNxtFrame);
	}
}

/***************************************************************************
����ԭ��  uchar8 ReadCurrFFRecordReg_NxtFrame (Str_Comm_NxtFrame *pSV_CommNxtFrame,Str_Comm_645 *pV_645Frame,uchar8 TB_NxtFrame_LineNo)
��������	  ������֡������ȡ����¼���¼��ע�⣺����֡֡����������á�����ֻ����Ӧ�����ݡ�
�������   *pSV_CommNxtFrame:����֡����
		  *pV_645Frame:���յ�������֡
		  TB_NxtFrame_LineNo:1�����е��к�
�������   *pSV_CommNxtFrame.Nxt:��һ�����ݷ����ʶ��
���ز���   C_NoNxtFrame/C_HaveNxtFrame
ȫ�ֱ���
������ע	1�����ñ�����֮ǰ������������λ��û�и�ֵ��
		2��ͨ������֡�����У�Nxt�ڱ��������ã���Sub��֡����������á�
		3������������DI0��DI2�����кϷ����жϡ�
		��Ϊ��11������ñ�����ǰ�Ѿ��жϹ�����ô����֡�����е��ܵ�DI����ȷ�ģ�12�������Ҳ�����ٴ��жϡ�
            ֻ֧�ֹ�����ʧ���¼���
***************************************************************************/
uchar8 ReadCurrFFRecordReg_NxtFrame (Str_Comm_NxtFrame *pSV_CommNxtFrame, Str_Comm_645 *pV_645Frame, uchar8 TB_NxtFrame_LineNo)
{
	uchar8	buf_O_CanWrite;		/*��������д���ݵ�ƫ��*/
	uchar8	LenFor_Data;		/*�������ɱ�д���ܵĳ���*/
	uchar8	*pData;
	uchar8	V_ReturnData;
	ulong32	*pTB_SubDI;			/* 2����ָ��*/
	uchar8	TB_SubDI_LineNo;	/* 2�����к�*/
	uchar8	TB_SubDI_MaxLineNo;	/* 2������*/
	ulong32	ReadDI;

/*��ѯһ������ȡ2������ز���*/
	pTB_SubDI = TB_NxtFrame[TB_NxtFrame_LineNo].pTB_SubDI;
	TB_SubDI_MaxLineNo = TB_NxtFrame[TB_NxtFrame_LineNo].SubDINum;

/*ѭ����ѯ2����ȷ��2�������׸������ʶ���Ӧ��2�����к�*/
	ReadDI = pSV_CommNxtFrame->Nxt_DataCode;
	for(TB_SubDI_LineNo = 0; TB_SubDI_LineNo < TB_SubDI_MaxLineNo; TB_SubDI_LineNo++ )
	{
		if( ReadDI == (pTB_SubDI[TB_SubDI_LineNo]))
		{
			break;
		}
	}
	if(TB_SubDI_LineNo >= TB_SubDI_MaxLineNo)
	{/*���������Ҳ���*/
		Comm_Response_Set_ReadErr(C_No_Request_data, pV_645Frame);
		return(C_NoNxtFrame);
	}
/*ѭ����ѯ2����ķ����ʶ�룬�����ݲ�����*/
	/*ע��pData������DI����*/
	buf_O_CanWrite = 0;
	pData = &pV_645Frame->Data[C_11_SData];
	LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - buf_O_CanWrite - 1;	/*��ȥ1��Ŀ�ģ�������Ҫ֡���*/

	for( ; TB_SubDI_LineNo < TB_SubDI_MaxLineNo; TB_SubDI_LineNo++ )
	{
		/*����ȡ�����ʶ��,DI2/DI0ȡ�ܵı�ʶ���е�DI2/DI0*/
			ReadDI = pTB_SubDI[TB_SubDI_LineNo] ;
			pSV_CommNxtFrame->Nxt_DataCode = ReadDI;					/*������һ֡��*/
		/*�ж�ʣ���ֽ��Ƿ�д����֡���*/
			if(LenFor_Data < 1)
			{
				break;					        						/*TB_SubDI_LineNo���л�û���ж�*/
			}
		/*�����ݲ�*/
             V_ReturnData = SF_ReadCurrEventFF_645(ReadDI, &pData[buf_O_CanWrite], &LenFor_Data);
             if(V_ReturnData == C_OK)
             {
                 pData[buf_O_CanWrite + LenFor_Data] = 0xAA;    		/*���ݼ���AA*/
                 LenFor_Data += CL_EventFF_AALen;
             }
			if(V_ReturnData == C_IDError)
			{/*�޴˱�ʶ�룬Ӧ�������������˳�.�����ܵ������!*/
				Comm_Response_Set_ReadErr(C_No_Request_data, pV_645Frame);
				return(C_NoNxtFrame);
			}
		/*���Ȳ������˳�ѭ��*/
			if(V_ReturnData == C_DataLenError)
			{
				break;
			}
		/*��������OK���ǲ����ܵģ����Ӧ�����������˳�*/
			if(V_ReturnData != C_OK)
			{
				Comm_Response_Set_ReadErr(C_OtherErr, pV_645Frame);
				return(C_NoNxtFrame);
			}
		/*OK�������������Ͽ�*/
			buf_O_CanWrite = buf_O_CanWrite + LenFor_Data;

			if(buf_O_CanWrite >= (C_Comm_Data_MaxLen - CLen_DI - 1))
			{/*�����ܵ����*/
				break;
			}
			LenFor_Data = C_Comm_Data_MaxLen - CLen_DI - buf_O_CanWrite - 1;
		}

/*��֯Ӧ��֡*/
	Comm_11_03Response_Normal(pV_645Frame, pData, buf_O_CanWrite);

/*�Ƿ��к���֡���ж�*/
	if(TB_SubDI_LineNo >= TB_SubDI_MaxLineNo)
	{/*�������ʶ������󣬱���������������*/
		return(C_NoNxtFrame);
	}
	else
	{
		return(C_HaveNxtFrame);
	}
}
/***************************************************************************
����ԭ�� 	IsFreezeDataEnableRead
��������	ȷ���ñ�ʶ�루�Ǽ���������Ƿ��������
�������	DataCode			:�������ʶ��
������� 	��
���ز���	C_OK/C_Error
ȫ�ֱ���
������ע	1����֧�ַ����ʶ�룬��֧�ּ��ϡ�
				2��ʣ�����ն���ֱ�ӷ����������
				3�����ģʽ��Ϊ0���������ʱ��Ҳ������
				4)	ͬʱ�жϷ����ʶ������Ƿ����
				5)	��DI1���������ж��ˡ�DI1�Ͳ������ж��ˣ���Ϊ���ݲ�᷵��C_IDError���Ͳ������ж��ˡ�
***************************************************************************/
uchar8		IsFreezeDataEnableRead (ulong32 DataCode)
{
	uchar8	DefaultFreezeMode;
	uchar8	FreezeMode;
	uchar8	DI0Range;

/*�ж���������Ƿ�ΪDI1=0xFF���ϣ�����Ӧ�����*/
	if((DataCode & 0x0000FF00) == 0x0000FF00)
	{
		return(C_Error);
	}
/*�����������ȷ�����ඳ��ģʽ�ֵ�DI*/
	switch(DataCode & 0xFFFF0000)
	{
		case		0x05000000:			/*��ʱ����*/
			DefaultFreezeMode = 0xFF;	/*Ĭ��ȫ�����*/
			DI0Range = 0x3C;			/*��ʱ����ֻ�������1-��60*/
			break;
		case		0x05010000:			/*˲ʱ����*/
			DefaultFreezeMode = 0xFF;	/*Ĭ��ȫ�����*/
			DI0Range = 0x03;			/*˲ʱ����ֻ�������1-��3*/
			break;
		case		0x05020000:			/*Լ������*/
		case		0x05030000:
		case		0x05050000:
		case		0x05070000:
			DefaultFreezeMode = 0xFF;	/*Ĭ��ȫ�����*/
			DI0Range = 0x02;			/*Լ��������2��*/
			break;
		case		0x05040000:			/*���㶳��*/
			DefaultFreezeMode = 0x03;	/*Ĭ��ȫ�����*/
			DI0Range = 0xFE;			/*���㶳��ֻ�������1-��254*/
			break;
		case		0x05060000:			/*�ն���*/
			DefaultFreezeMode = 0xFF;	/*Ĭ��ȫ�����*/
			DI0Range = 0x3E;			/*�ն���ֻ�������1-��62��*/
			break;
		case		0x05080000:			/* ʣ����û��ģʽ�ֵĿ��ƣ�Ӧ��OK*/
			if( ( DataCode & 0x000000FF ) > 0x3E )
			{
				return(C_Error);	/*ʣ�����ն���Ҳֻ�������1-��62��*/
			}
			return(C_OK);
		default:
			return(C_Error);
	}
	FreezeMode = DefaultFreezeMode;

/*�ж�DI0�����Ƿ��ں���Χ�������򷵻ش���DI1���ݲ������жϵġ�*/
	if( ( ( DataCode & 0x000000FF ) > (ulong32)DI0Range ) || ( ( DataCode & 0x000000FF ) == 0 ) )
	{/*DI0=0��ʾ����������Ҳ����ʧ�ܡ�*/
		return(C_Error);
	}

/*����ģʽ���жϷ����ʶ���Ƿ�֧�ֶ�*/
/*�����ȡ����ʱ�䣬ֻҪģʽ�ֲ�Ϊ0����ֱ�ӿɶ���*/
	if( ( DataCode & 0x0000FF00 ) == 0 )
	{/*����ʱ��*/
		if(FreezeMode != 0)
		{
			return(C_OK);
		}
		else
		{
			return(C_Error);
		}
	}
/*�����ж�DI1*/
	switch(DataCode & 0x0000FF00)
	{
		case		0x00000100:			/*�����й�*/
			DefaultFreezeMode = 0x01;	/*����Ҫ��0λ*/
			break;
		case		0x00000200:			/*�����й�*/
			DefaultFreezeMode = 0x02;	/*����Ҫ��1λ*/
			break;
		case		0x00000300:			/*����1*/
			DefaultFreezeMode = 0x04;	/*����Ҫ��2λ*/
			break;
		case		0x00000400:			/*����2*/
			DefaultFreezeMode = 0x08;	/*����Ҫ��3λ*/
			break;
		case		0x00000500:			/* 1-4�����޹�*/
		case		0x00000600:
		case		0x00000700:
		case		0x00000800:
			DefaultFreezeMode = 0x10;	/*����Ҫ��4λ*/
			break;
		case		0x00000900:			/*������*/
			DefaultFreezeMode = 0x20;	/*����Ҫ��5λ*/
			break;
		case		0x00000A00:			/*������*/
			DefaultFreezeMode = 0x40;	/*����Ҫ��6λ*/
			break;
		case		0x00001000:			/*����*/
			DefaultFreezeMode = 0x80;	/*����Ҫ��7λ*/
			break;
		default:
			return(C_Error);
	}

	if( ( FreezeMode & DefaultFreezeMode ) == 0 )
	{/*��Ӧλ���ó�0�ˡ�*/
		return(C_Error);
	}
	else
	{
		return(C_OK);
	}
}

/**************************************/
/**********698����645����***********/
/*����*/
const Str_ParaChange_OADToDI_Table  Str_DemandChange[]=
{
     /*  OAD         	        DI */
    {CPos_Ac_Tol_De_0,	        0x01010000},/*��ǰ�����й����������������ʱ��*/
    {CPos_Ac_T1_De_0 ,	        0x01010100},/*��ǰ�����й�����1�������������ʱ��*/
    {CPos_Ac_T2_De_0 ,	        0x01010200},/*��ǰ�����й�����2�������������ʱ��*/
    {CPos_Ac_T3_De_0 ,	        0x01010300},/*��ǰ�����й�����3�������������ʱ��*/
    {CPos_Ac_T4_De_0 ,	        0x01010400},/*��ǰ�����й�����4�������������ʱ��*/
    {CRev_Ac_Tol_De_0,	        0x01020000},/*��ǰ�����й����������������ʱ��*/
    {CRev_Ac_T1_De_0 ,	        0x01020100},/*��ǰ�����й�����1�������������ʱ��*/
    {CRev_Ac_T2_De_0 ,	        0x01020200},/*��ǰ�����й�����2�������������ʱ��*/
    {CRev_Ac_T3_De_0 ,	        0x01020300},/*��ǰ�����й�����3�������������ʱ��*/
    {CRev_Ac_T4_De_0 ,	        0x01020400},/*��ǰ�����й�����4�������������ʱ��*/
    {CCom_Re1_Tol_De_0,	        0x01030000},/*��ǰ����޹�1���������������ʱ��*/
    {CCom_Re1_T1_De_0 ,	        0x01030100},/*��ǰ����޹�1����1�������������ʱ��*/
    {CCom_Re1_T2_De_0 ,	        0x01030200},/*��ǰ����޹�1����2�������������ʱ��*/
    {CCom_Re1_T3_De_0 ,	        0x01030300},/*��ǰ����޹�1����3�������������ʱ��*/
    {CCom_Re1_T4_De_0 ,	        0x01030400},/*��ǰ����޹�1����4�������������ʱ��*/
    {CCom_Re2_Tol_De_0,	        0x01040000},/*��ǰ����޹�2���������������ʱ��*/
    {CCom_Re2_T1_De_0 ,	        0x01040100},/*��ǰ����޹�2����1�������������ʱ��*/
    {CCom_Re2_T2_De_0 ,	        0x01040200},/*��ǰ����޹�2����2�������������ʱ��*/
    {CCom_Re2_T3_De_0 ,	        0x01040300},/*��ǰ����޹�2����3�������������ʱ��*/
    {CCom_Re2_T4_De_0 ,	        0x01040400},/*��ǰ����޹�2����4�������������ʱ��*/
    {CQua1_Re_Tol_De_0,	        0x01050000},/*��ǰ1�����޹����������������ʱ��*/
    {CQua1_Re_T1_De_0 ,	        0x01050100},/*��ǰ1�����޹�����1�������������ʱ��*/
    {CQua1_Re_T2_De_0 ,	        0x01050200},/*��ǰ1�����޹�����2�������������ʱ��*/
    {CQua1_Re_T3_De_0 ,	        0x01050300},/*��ǰ1�����޹�����3�������������ʱ��*/
    {CQua1_Re_T4_De_0 ,	        0x01050400},/*��ǰ1�����޹�����4�������������ʱ��*/
    {CQua2_Re_Tol_De_0,	        0x01060000},/*��ǰ2�����޹����������������ʱ��*/
    {CQua2_Re_T1_De_0 ,	        0x01060100},/*��ǰ2�����޹�����1�������������ʱ��*/
    {CQua2_Re_T2_De_0 ,	        0x01060200},/*��ǰ2�����޹�����2�������������ʱ��*/
    {CQua2_Re_T3_De_0 ,	        0x01060300},/*��ǰ2�����޹�����3�������������ʱ��*/
    {CQua2_Re_T4_De_0 ,	        0x01060400},/*��ǰ2�����޹�����4�������������ʱ��*/
    {CQua3_Re_Tol_De_0,	        0x01070000},/*��ǰ3�����޹����������������ʱ��*/
    {CQua3_Re_T1_De_0 ,	        0x01070100},/*��ǰ3�����޹�����1�������������ʱ��*/
    {CQua3_Re_T2_De_0 ,	        0x01070200},/*��ǰ3�����޹�����2�������������ʱ��*/
    {CQua3_Re_T3_De_0 ,	        0x01070300},/*��ǰ3�����޹�����3�������������ʱ��*/
    {CQua3_Re_T4_De_0 ,	        0x01070400},/*��ǰ3�����޹�����4�������������ʱ��*/
    {CQua4_Re_Tol_De_0 ,        0x01080000}, /*��ǰ4�����޹����������������ʱ��*/
    {CQua4_Re_T1_De_0 ,	        0x01080100}, /*��ǰ4�����޹�����1�������������ʱ��*/
    {CQua4_Re_T2_De_0 ,	        0x01080200}, /*��ǰ4�����޹�����2�������������ʱ��*/
    {CQua4_Re_T3_De_0 ,	        0x01080300}, /*��ǰ4�����޹�����3�������������ʱ��*/
    {CQua4_Re_T4_De_0 ,	        0x01080400}, /*��ǰ4�����޹�����4�������������ʱ��*/

    {CPosA_Ac_De_0,             0x01150000},  /*��ǰA�������й��������������ʱ��*/
    {CRevA_Ac_De_0,             0x01160000},  /*��ǰA�෴���й��������������ʱ��*/
    {CComA_Re1_De_0,            0x01170000},  /*��ǰA������޹�1�������������ʱ��*/
    {CComA_Re2_De_0,            0x01180000},  /*��ǰA������޹�2�������������ʱ��*/
    {CQua1A_Re_De_0,            0x01190000},  /*��ǰA��1�����޹��������������ʱ��*/
    {CQua2A_Re_De_0,            0x011A0000},  /*��ǰA��2�����޹��������������ʱ��*/
    {CQua3A_Re_De_0,            0x011B0000},  /*��ǰA��3�����޹��������������ʱ��*/
    {CQua4A_Re_De_0,            0x011C0000},  /*��ǰA��4�����޹��������������ʱ��*/
    {CPosB_Ac_De_0,             0x01290000},  /*��ǰB�������й��������������ʱ��*/
    {CRevB_Ac_De_0,             0x012A0000},  /*��ǰB�෴���й��������������ʱ��*/
    {CComB_Re1_De_0,            0x012B0000},  /*��ǰB������޹�1�������������ʱ��*/
    {CComB_Re2_De_0,            0x012C0000},  /*��ǰB������޹�2�������������ʱ��*/
    {CQua1B_Re_De_0,            0x012D0000},  /*��ǰB��1�����޹��������������ʱ��*/
    {CQua2B_Re_De_0,            0x012E0000},  /*��ǰB��2�����޹��������������ʱ��*/
    {CQua3B_Re_De_0,            0x012F0000},  /*��ǰB��3�����޹��������������ʱ��*/
    {CQua4B_Re_De_0,            0x01300000},  /*��ǰB��4�����޹��������������ʱ��*/
    {CPosC_Ac_De_0,             0x013D0000},  /*��ǰC�������й��������������ʱ��*/
    {CRevC_Ac_De_0,             0x013E0000},  /*��ǰC�෴���й��������������ʱ��*/
    {CComC_Re1_De_0,            0x013F0000},  /*��ǰC������޹�1�������������ʱ��*/
    {CComC_Re2_De_0,            0x01400000},  /*��ǰC������޹�2�������������ʱ��*/
    {CQua1C_Re_De_0,            0x01410000},  /*��ǰC��1�����޹��������������ʱ��*/
    {CQua2C_Re_De_0,            0x01420000},  /*��ǰC��2�����޹��������������ʱ��*/
    {CQua3C_Re_De_0,            0x01430000},  /*��ǰC��3�����޹��������������ʱ��*/
    {CQua4C_Re_De_0,            0x01440000},  /*��ǰC��4�����޹��������������ʱ��*/

};
#define Str_DemandChange_Len  (sizeof(Str_DemandChange) / sizeof(Str_ParaChange_OADToDI_Table))

/***************************************************************************
����ԭ�� 	Comm_ReadDemandReg
��������	��ɶ���������Ľ�����Ӧ��
�������	*pV_645Frame				:�յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	��ͨ����ص�ȫ�ֱ���
������ע	���뱾������DI3�϶�����01
***************************************************************************/
void 		Comm_ReadDemandReg(Str_Comm_645 * pV_645Frame)
{
	uchar8	buf_O_CanWrite = 0;						/*��������д���ݵ�ƫ��*/
	uchar8	LenFor_Data[2];							/*�������ɱ�д���ܵĳ���*/
	uchar8	*pData;
	uchar8	V_ReturnData = C_IDError;
    ushort16 V_usLen;
	uchar8	i;

/*ע��pData������DI����*/
	pData = &pV_645Frame->Data[C_11_SData];
/*����ǰ����*/
	if(pV_645Frame->Data[C_O_DI0] == 0x00)
	{
       if(pV_645Frame->Data[C_O_DI1] == 0xFF)
       {
       		for( i = 0; i < Str_DemandChange_Len; i++ )
       		{
       			if( ( pV_645Frame->DI & 0xFFFF00FF )== ( Str_DemandChange[i].DI & 0xFFFF00FF ) )
       			{
					/*V_ReturnData = InF_ReadDemand(Str_DemandChange[i].OAD, &pData[buf_O_CanWrite], CLRev_Ac_Tol_De_0);
                    645Э�鴦�������޸� lzy 20211101*/
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
                    645Э�鴦�������޸� lzy 20211101*/
                    break;
                }
       		}
            buf_O_CanWrite = CLRev_Ac_Tol_De_0;
       }
       LenFor_Data[0] = buf_O_CanWrite;


	}
    else
    {
/*����������*/
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
	{/*�޴˱�ʶ�룬Ӧ�������������˳�*/
		Comm_Response_Set_ReadErr(C_No_Request_data_645, pV_645Frame);
		return;
	}

	if(V_ReturnData != C_OK)
	{/*�����������������Ӧ�����������������û�����壬Ҳ����������*/
		Comm_Response_Set_ReadErr(C_OtherErr_645, pV_645Frame);
		return;
	}

	Comm_11_03Response_Normal(pV_645Frame, pData, LenFor_Data[0]);
}

/*****************************************************************************************
Function��	void SF_GetFrozenData_SettleFreeze(uchar8 *V_ucResultData,uchar8 V_ucFrozenType)
Description��645��ȡ���㶳������
Input�� pV_645Frame���յ�����֡
Output��V_ucResultData��ȡ�����ݣ�V_ucResultDataLength���ݳ���
Calls��
Called By��
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

/*�������ӻ��涨�壬��Ϊ��698������������������Ϊ12��*/
/*�������645�ܼ����ʵ��ܼ��ϵĳ��ȶ��建��ײ��ȡ���ݻ���ֻ��治�������*/
	ushort16 V_usLen = 0;
    uchar8 i;
	V_ulOAD[0] = (C_RelatedOAD_Settle&0xFFFF00FF) | (pV_645Frame->Data[C_O_DI0] & 0x000000FF);	/*0x500500xx*/
	V_ulOAD[2] = 0xFFFFFFFF;

    if(pV_645Frame->Data[C_O_DI3] == 0x00)
    {
		if(pV_645Frame->Data[C_O_DI1] <= 0x04)
		{
			V_ucBuffer[C_O_DI0] = pV_645Frame->Data[C_O_DI1] + 1;
			V_ucBuffer[C_O_DI1] = 0x02; 															/*�������ȡ��Ϊ����2*/
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
			V_ucBuffer[C_O_DI3] = pV_645Frame->Data[C_O_DI3];										/*�������ȡ��ΪOIA��Ϊ0x00	 */
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
			V_ucBuffer[C_O_DI0] = 0x00; /*�������ȡ����00��ȡ����*/
			V_ucBuffer[C_O_DI1] = 0x02; /*�������ȡ��Ϊ����2*/

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

			V_ucBuffer[C_O_DI3] = pV_645Frame->Data[C_O_DI3];					/*�������ȡ��ΪOIA��Ϊ0x00	 */
			PF_Buffer4ToUlong32(V_ucBuffer, &V_ulOAD[1], 4);

			V_usLen = sizeof(V_ucData_Temp);
			V_Return = Inf_Read_FrozenData_OneOAD(V_ulOAD, V_ucData_Temp, &V_usLen);
			memcpy(V_ucResultData, V_ucData_Temp, CLPos_Ac_En_FF_1);			/*��ȡ�ܼ�ǰ4���ʵ���*/
			if(V_Return == C_NoData)
			{
				V_usLen = CLPos_Ac_En_FF_1;
				memset(V_ucResultData, 0x00, V_usLen);
				V_Return = C_OK;
			}

			if(V_usLen < CLPos_Ac_En_FF_1)										/*Ԥ��������<4���*/
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
			V_ucBuffer[C_O_DI1] = 0x02; /*�������ȡ��Ϊ����2*/
			V_ucBuffer[C_O_DI2] = pV_645Frame->Data[C_O_DI2]<<4;

			V_ucBuffer[C_O_DI3] = pV_645Frame->Data[C_O_DI3]<<4;	/*�������ȡ��ΪOIA��Ϊ0x10	*/
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
			V_ucBuffer[C_O_DI0] = 0x00; /*�������ȡ����00��ȡ����*/
			V_ucBuffer[C_O_DI1] = 0x02; /*�������ȡ��Ϊ����2*/
			V_ucBuffer[C_O_DI2] = pV_645Frame->Data[C_O_DI2] << 4;

			V_ucBuffer[C_O_DI3] = pV_645Frame->Data[C_O_DI3] << 4;	/*�������ȡ��ΪOIA��Ϊ0x00	 */
			PF_Buffer4ToUlong32(V_ucBuffer, &V_ulOAD[1], 4);
			V_usLen = CLPos_Ac_De_FF_0;
			V_Return = Inf_Read_FrozenData_OneOAD(V_ulOAD, V_ucData_Temp, &V_usLen);
			memcpy(V_ucResultData, V_ucData_Temp, CLPos_Ac_De_FF_0_4Rate);		/*��ȡ�ܼ�ǰ4��������*/

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
/*698����645����*/
/*����*/
const Str_ParaChange_OADToDI_Table  Str_EnergyChange[]=
{
/*/  OAD         			DI */
  {CCom_Ac_Tol_En_0,	0x00000000	},/*��ǰ����й��ܵ���*/
  {CCom_Ac_T1_En_0 ,	0x00000100	},/*��ǰ����й�����1����*/
  {CCom_Ac_T2_En_0 ,	0x00000200	},/*��ǰ����й�����2����*/
  {CCom_Ac_T3_En_0 ,	0x00000300	},/*��ǰ����й�����3����*/
  {CCom_Ac_T4_En_0 ,	0x00000400	},/*��ǰ����й�����4����*/
  {CPos_Ac_Tol_En_0 ,	0x00010000 	},/*��ǰ�����й��ܵ���*/
  {CPos_Ac_T1_En_0 , 	0x00010100	},/*��ǰ�����й�����1����*/
  {CPos_Ac_T2_En_0 , 	0x00010200	},/*��ǰ�����й�����2����*/
  {CPos_Ac_T3_En_0 , 	0x00010300	},/*��ǰ�����й�����3����*/
  {CPos_Ac_T4_En_0 , 	0x00010400	},/*��ǰ�����й�����4����*/
  {CRev_Ac_Tol_En_0, 	0x00020000 	},/*��ǰ�����й��ܵ���*/
  {CRev_Ac_T1_En_0 , 	0x00020100	},/*��ǰ�����й�����1����*/
  {CRev_Ac_T2_En_0 , 	0x00020200	},/*��ǰ�����й�����2����*/
  {CRev_Ac_T3_En_0 , 	0x00020300	},/*��ǰ�����й�����3����*/
  {CRev_Ac_T4_En_0 , 	0x00020400	},/*��ǰ�����й�����4����*/
  {CCom_Re1_Tol_En_0,	0x00030000	},/*��ǰ����޹�1�ܵ���*/
  {CCom_Re1_T1_En_0 ,	0x00030100	},/*��ǰ����޹�1����1����*/
  {CCom_Re1_T2_En_0 ,	0x00030200	},/*��ǰ����޹�1����2����*/
  {CCom_Re1_T3_En_0 ,	0x00030300	},/*��ǰ����޹�1����3����*/
  {CCom_Re1_T4_En_0 ,	0x00030400	},/*��ǰ����޹�1����4����*/
  {CCom_Re2_Tol_En_0,	0x00040000	},/*��ǰ����޹�2�ܵ���*/
  {CCom_Re2_T1_En_0 ,	0x00040100	},/*��ǰ����޹�2����1����*/
  {CCom_Re2_T2_En_0 ,	0x00040200	},/*��ǰ����޹�2����2����*/
  {CCom_Re2_T3_En_0 ,	0x00040300	},/*��ǰ����޹�2����3����*/
  {CCom_Re2_T4_En_0 ,	0x00040400	},/*��ǰ����޹�2����4����*/
  {CQua1_Re_Tol_En_0,	0x00050000	},/*��ǰ1�����޹��ܵ���*/
  {CQua1_Re_T1_En_0 ,	0x00050100	},/*��ǰ1�����޹�����1����*/
  {CQua1_Re_T2_En_0 ,	0x00050200	},/*��ǰ1�����޹�����2����*/
  {CQua1_Re_T3_En_0 ,	0x00050300	},/*��ǰ1�����޹�����3����*/
  {CQua1_Re_T4_En_0 ,	0x00050400	},/*��ǰ1�����޹�����4����*/
  {CQua2_Re_Tol_En_0 , 	0x00060000 	},/*��ǰ2�����޹��ܵ���*/
  {CQua2_Re_T1_En_0  , 	0x00060100	},/*��ǰ2�����޹�����1����*/
  {CQua2_Re_T2_En_0  , 	0x00060200	},/*��ǰ2�����޹�����2����*/
  {CQua2_Re_T3_En_0  , 	0x00060300	},/*��ǰ2�����޹�����3����*/
  {CQua2_Re_T4_En_0  , 	0x00060400	},/*��ǰ2�����޹�����4����*/
  {CQua3_Re_Tol_En_0 , 	0x00070000	},/*��ǰ3�����޹��ܵ���*/
  {CQua3_Re_T1_En_0  , 	0x00070100	},/*��ǰ3�����޹�����1����*/
  {CQua3_Re_T2_En_0  , 	0x00070200	},/*��ǰ3�����޹�����2����*/
  {CQua3_Re_T3_En_0  , 	0x00070300	},/*��ǰ3�����޹�����3����*/
  {CQua3_Re_T4_En_0  , 	0x00070400	},/*��ǰ3�����޹�����4����*/
  {CQua4_Re_Tol_En_0 , 	0x00080000	},/*��ǰ4�����޹��ܵ���*/
  {CQua4_Re_T1_En_0  , 	0x00080100	},/*��ǰ4�����޹�����1����*/
  {CQua4_Re_T2_En_0  , 	0x00080200	},/*��ǰ4�����޹�����2����*/
  {CQua4_Re_T3_En_0  , 	0x00080300	},/*��ǰ4�����޹�����3����*/
  {CQua4_Re_T4_En_0  , 	0x00080400	},/*��ǰ4�����޹�����4����*/
  {CPosA_Ac_En_0,		0x00150000	},/*��ǰA�������й�����*/
  {CPosB_Ac_En_0,		0x00290000	},/*��ǰB�������й�����*/
  {CPosC_Ac_En_0,		0x003D0000	},/*��ǰC�������й�����*/
  {CRevA_Ac_En_0,		0x00160000	},/*��ǰA�෴���й�����*/
  {CRevB_Ac_En_0,		0x002A0000	},/*��ǰB�෴���й�����*/
  {CRevC_Ac_En_0,		0x003E0000	},/*��ǰC�෴���й�����*/
  {CQua1A_Re_En_0,		0x00190000  },/*��ǰA��1�����޹�����*/
  {CQua2A_Re_En_0,		0x001A0000  },/*��ǰA��2�����޹�����*/
  {CQua3A_Re_En_0,		0x001B0000  },/*��ǰA��3�����޹�����*/
  {CQua4A_Re_En_0,		0x001C0000	},/*��ǰA��4�����޹�����*/
  {CQua1B_Re_En_0,		0X002D0000  },/*��ǰB��1�����޹�����*/
  {CQua2B_Re_En_0,		0X002E0000  },/*��ǰB��2�����޹�����*/
  {CQua3B_Re_En_0,		0X002F0000  },/*��ǰB��3�����޹�����*/
  {CQua4B_Re_En_0,		0X00300000  },/*��ǰB��4�����޹�����*/
  {CQua1C_Re_En_0,      0x00410000	},/*��ǰC��1�����޹�����*/
  {CQua2C_Re_En_0,      0x00420000	},/*��ǰC��2�����޹�����*/
  {CQua3C_Re_En_0,      0x00430000	},/*��ǰC��3�����޹�����*/
  {CQua4C_Re_En_0,      0x00440000	},/*��ǰC��4�����޹�����*/
  {CComA_Re1_En_0,      0x00170000  },/*��ǰA������޹�1����*/
  {CComA_Re2_En_0,      0x00180000  },/*��ǰA������޹�2����*/
  {CComB_Re1_En_0,      0x002B0000  },/*��ǰB������޹�1����*/
  {CComB_Re2_En_0,      0x002C0000  },/*��ǰB������޹�2����*/
  {CComC_Re1_En_0,      0x003F0000  },/*��ǰC������޹�1����*/
  {CComC_Re2_En_0,      0x00400000  },/*��ǰC������޹�2����*/
};
#define Str_EnergyChange_Len  (sizeof(Str_EnergyChange) / sizeof(Str_ParaChange_OADToDI_Table))

/*��ȷ����*/
const Str_ParaChange_OADToDI_Table  Str_EnergyChange_Pre[]=
{
/*/  OAD         				DI  */
  {CPos_Ac_Tol_PreEn_0 ,	0x00600000 	},/*��ǰ�����й��ܾ�ȷ����*/
  {CPos_Ac_T1_PreEn_0 , 	0x00600100	},/*��ǰ�����й�����1��ȷ����*/
  {CPos_Ac_T2_PreEn_0 , 	0x00600200	},/*��ǰ�����й�����2��ȷ����*/
  {CPos_Ac_T3_PreEn_0 , 	0x00600300	},/*��ǰ�����й�����3��ȷ����*/
  {CPos_Ac_T4_PreEn_0 , 	0x00600400	},/*��ǰ�����й�����4��ȷ����*/
  {CRev_Ac_Tol_PreEn_0, 	0x00610000 	},/*��ǰ�����й��ܾ�ȷ����*/
  {CRev_Ac_T1_PreEn_0 , 	0x00610100	},/*��ǰ�����й�����1��ȷ����*/
  {CRev_Ac_T2_PreEn_0 , 	0x00610200	},/*��ǰ�����й�����2��ȷ����*/
  {CRev_Ac_T3_PreEn_0 , 	0x00610300	},/*��ǰ�����й�����3��ȷ����*/
  {CRev_Ac_T4_PreEn_0 , 	0x00610400	},/*��ǰ�����й�����4��ȷ����*/
};
#define Str_EnergyChange_Pre_Len  (sizeof(Str_EnergyChange) / sizeof(Str_ParaChange_OADToDI_Table))

/***************************************************************************
����ԭ�ͣ� SF_EnergyT0_645
�������ܣ� ����������ת��Ϊ645��ʽ
���������
			pV_ucBufΪת��ǰ���ݣ�����2��ÿ������4�����ݿ�20���ֽ�hex�����ģʽ
								����4��ÿ������5�����ݿ�25���ֽ�hex�����ģʽ
			*pV_usLenΪԭʼ���ݳ���
			V_ucOIB_698: 698��ʶ���IOB�������ж��Ƿ�Ϊ��ϵ��ܣ���ϵ��ܷ���799999.99
						�������ܷ���999999.99
���������*pV_ucBuf_ExchangedΪת�������ݣ�����2��ÿ������4�ֽ�BCD��С��ģʽ
								����4��ÿ������5�ֽ�BCD��С��ģʽ
			*pV_usLenΪת�������ݳ���
���ز�������
����λ�ã���ͨ����ص�ȫ�ֱ���
��    ע��ת�������ݳ�����Ӧ������ֱ�ӽ�ȡ��Ӧ���ȣ�����2Ϊ4�ֽڣ�����4Ϊ5�ֽ�
***************************************************************************/
void SF_EnergyT0_645(uchar8 *pV_ucBuf, uchar8 *pV_ucBuf_Exchanged, ushort16 *pV_usLen, uchar8 V_ucPerLen, uchar8 V_ucOIB_698)
{
	uchar8  V_ucOneLen, i, j, V_ucEnergy_Num = 1, V_ucSign = 0;
	ulong64 V_ulData;
	ulong32 V_ulClearMax = 100000000;

	if( ( ( V_ucOIB_698 & 0xF0) == 0x00 )
		|| ( (V_ucOIB_698 & 0xF0) == 0x30 )
		|| ( (V_ucOIB_698 & 0xF0) == 0x40 ) )		/*��ϵ���*/
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
			V_ucSign = 0x80;										/*�������λ*/
		}
		else
		{
			for(i = 0; i < V_ucOneLen; i++)
			{
				V_ulData <<= 8;
				V_ulData |= pV_ucBuf[i + j*V_ucOneLen];
			}
		}
		V_ulData %= V_ulClearMax;									/*ת�������ݶ���Ӧ�Ľ�������*/
		for(i = 0; i < V_ucOneLen; i++)
		{
			pV_ucBuf_Exchanged[i + j * V_ucOneLen] = V_ulData%10;
			V_ulData /= 10;
			pV_ucBuf_Exchanged[i + j * V_ucOneLen] |= ( ( (uchar8)(V_ulData%10) ) << 4);
			V_ulData /= 10;
		}
		pV_ucBuf_Exchanged[i + j * V_ucOneLen - 1] |= V_ucSign;		/*���λ���Ϸ���λ*/
		*pV_usLen += V_ucOneLen;
	}
}

/***************************************************************************
����ԭ�ͣ�Comm_ReadEnergyReg
��������	����ɶ���������Ľ�����Ӧ��
�������	��*pV_645Frame:�յ�������֡
�����������
���ز�������
����λ�ã���ͨ����ص�ȫ�ֱ���
��    ע�����뱾������DI3�϶�����00
***************************************************************************/
void Comm_ReadEnergyReg(Str_Comm_645 *pV_645Frame)
{/*645Э�鴦��  �����޸� lzy 20211104*/
#if 0
	uchar8 LenFor_Data[2] = {0};    						/*�������ɱ�д���ܵĳ���*/
	uchar8 V_ucBuffer[CLSettle_Time_1 * 12 + 10] = {0};
	uchar8 V_ReturnData = C_IDError;
	ushort16 V_usLen=CLPos_Ac_En_FF_1;
	uchar8 i, V_ucDataOff = 0;
    RdOI_Para_T V_OAD;
    ushort16 P_DataOff = 0;
    uchar8 V_Temp[CLSettle_Time_1 * 12 + 10] = {0};  		/*���ݲ���ܴ���Ǿ�ȷ���ܣ����Ȱ���ȷ����25,48����������*/
    uchar8 V_ucLen645 = 0;
    ushort16 V_usLenTemp = 0;
    uchar8 V_LastNo = 0;
	uchar8 V_ucBufferTemp[CLSettle_Time_1 * 12] = {0};
	uchar8 V_ucDataLen;

    /*����ǰ����*/
	if(pV_645Frame->Data[C_O_DI0] == 0x00)
	{
		if(pV_645Frame->Data[C_O_DI1] == 0xFF)
		{
			if( (pV_645Frame->Data[C_O_DI2] != 0x60) && (pV_645Frame->Data[C_O_DI2] != 0x61) )	/*���Ǿ�ȷ����*/
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
			else  /*����ȷ����*/
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
			else      /*����ȷ����*/
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
		/*���������*/
		if ( ( pV_645Frame->Data[C_O_DI0] >= 0x01 ) && ( pV_645Frame->Data[C_O_DI0] <= 0x0C ) )				/*���������*/
		{
			P_DataOff = CLPos_Ac_En_FF_1;
			V_ucLen645 = CLPos_Ac_En_FF_1;
			if( ( ( pV_645Frame->Data[C_O_DI2]) == 0xFE ) && ( ( pV_645Frame->Data[C_O_DI1] ) == 0x00 ) )	/*��1�ν���ʱ��00FE0001*/
			{
				V_OAD.RdOI.OAD = C_RelatedOAD_Settle | (pV_645Frame->Data[C_O_DI0]);
				V_OAD.Rd_RecordRelatedOI[0] = CFreeTime;
				V_OAD.Rd_RecordSelect[0] = C_RSDSelector9;
				V_OAD.Rd_RecordSelect[1] = pV_645Frame->Data[C_O_DI0];
				V_OAD.Rd_RecordRelatedOINum = 1;
				memset(V_Temp, 0x00, CLPos_Ac_En_FF_1);
				V_ReturnData = SF_GetAPDU_FreezeRead(&V_OAD, V_ucBuffer, &P_DataOff, C_GETNormal_Request);
				if( ( V_ReturnData == C_OK ) && ( P_DataOff != 1 ) ) 										/*���������*/
				{
					V_usLen = SF_DataExchangeTo645_BasicData((V_ucBuffer + 2), V_Temp, V_usLen, &V_ucLen645);	/*ʱ���ʽ��֮ǰ����һ�£�����Ҫ�޸�*/
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
		else if(pV_645Frame->Data[C_O_DI0] == 0xFF)			/*����ǰ����1-12���ݿ飺��֧��ʱ�����ݿ��ȡ�����ܲ�֧�֣���˲���Ҫ�޸�*/
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
					if( ( V_ReturnData == C_OK ) && ( P_DataOff != 1 ) )	/*���������*/
					{
						V_usLenTemp = CLSettle_Time_1;
						V_usLenTemp = SF_DataExchangeTo645_BasicData((V_ucBufferTemp + 2), V_Temp, V_usLenTemp, &V_ucLen645);
						V_usLenTemp = CLSettle_Time_1;
						memcpy( (V_ucBuffer + (V_LastNo - 1) * CLSettle_Time_1), (V_Temp + 2), V_usLenTemp);
					}
					else	/*���������*/
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
    {   /*�ɹ�����*/
        Comm_11_03Response_Normal(pV_645Frame, V_ucBuffer,LenFor_Data[0]);
        return;
    }
	else if(V_ReturnData == C_IDError)
    {   /*���ɹ�����ΪID����*/
        Comm_Response_Set_ReadErr(C_No_Request_data_645, pV_645Frame);
        return;
    }
	else
    {   /*��������*/
        Comm_Response_Set_ReadErr(C_OtherErr_645, pV_645Frame);
        return;
    }
#endif
}

/***************************************************************************
����ԭ�� 	SF_DIChangetoOAD
��������	645DI��ʶ���ת����698OAD
�������	645DI
������� 	��
���ز���	698OAD
ȫ�ֱ��� 	��
������ע
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
����ԭ�� 	SF_Error_ChangeTo645
��������	    698����645��������ת��Ϊ645Ҫ������
�������	    V_ErrorFlag	�����صĴ�������
������� 	��
���ز���	    ����645��������
ȫ�ֱ��� 	��
������ע
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
����ԭ�ͣ�uchar8 SF_DriveReportSet_Change(uchar8 Type, uchar8 *pData, uchar8 DataLenth)
����������645�������ϱ�ģʽ�֣�698�������¼��ϱ���ʶ�͸����ϱ�ģʽ�֣�2015��ʱ�����Ӧת��
          ����645ʱ����Ӧ698�������ã�����698ʱ����Ӧ645Ҳ��������
���������Type��C_ProtocolType_698/C_ProtocolType_645,���в�������645Э�飬����698Э�飻
          *pData:�������Ҫ���õ����ݣ�DataLenth��
          ���ݳ��ȣ�645���������ϱ�ģʽ��ʱ��8�ֽ�/
                    698�����¼������ϱ���ʶʱ�ǹ�2�ֽ�(1�ֽ����ݱ�ʶOI2+1�ֽ��ϱ���ʶ)/
                    698����2015ʱ��4�ֽ�
���������
���ز���: �����Ƿ�ɹ� C_OK C_Error
����˵����
���û��ƣ�
��    ע��
**********************************************************************************/
#define C_OneBit 0x08  /*һ���ֽ�8λ*/
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
                    	/*д�¼��ϱ���ʶ����*/
                        /*�õ���Ӧ��OAD*/
                        V_ucDataBuf[0] = 0x00;
                        if(Pstr_DriveReport_Change[i].Nature != C_NoChangeEvent)
                        {
							V_ucDataBuf[1] = Pstr_DriveReport_Change[i].Nature;
							V_ucDataBuf[2] = Pstr_DriveReport_Change[i].OIB;
							V_ucDataBuf[3] = 0x30;
							PF_Buffer4ToUlong32(V_ucDataBuf, &V_ulOAD, 4);
							/*�õ�Ӧ��д���ֵ*/
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
                        /*д2015*/
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
            if(DataLenth == CLOpenW_Report_Mode + CL_OI2Len) /*698д�ϱ���ʶ���ԣ���645�����ϱ�ģʽ��*/
            {
                for(i = 0; i < Pstr_DriveReport_ChangeLen; i++ )
                {
                    if(Pstr_DriveReport_Change[i].OIB == (*pData))
                    {
                        j = Pstr_DriveReport_Change[i].ReportMode645_Bit / C_OneBit; /*�ڵڼ��ֽ�*/
                        k = Pstr_DriveReport_Change[i].ReportMode645_Bit % C_OneBit; /*���ֽ��еڼ�λ*/
                        if( (*(pData + 1) ) == 0 )			/*���ϱ�*/
                        {
                            V_ucDataBuf[j] &= ~(0x01 << k);
                        }
                        else/*��������Ϊ�ϱ�*/
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
            else if(DataLenth == CLDrive_Report_Mode)			/*698д2015����645�����ϱ�ģʽ��*/
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
                                j = Pstr_DriveReport_Change[i].ReportMode645_Bit / C_OneBit; 	/*�ڵڼ��ֽ�*/
                                k = Pstr_DriveReport_Change[i].ReportMode645_Bit % C_OneBit; 	/*���ֽ��еڼ�λ*/
                                if( ( ( V_ul32Data_New >> i ) & 0x00000001 ) == 0 ) 			/*���ϱ�*/
                                {
                                    V_ucDataBuf[j] &= ~(0x01 << k);
                                }
                                else		/*��������Ϊ�ϱ�*/
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
                        else				/*�ݲ�д�����ж�����д*/
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
����ԭ�� 	Comm_14SetParm
��������	ͨ��14����Ľ���������(��̼�¼����������¼�������)
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	��
������ע
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

/*���ȸ��ݱ�����ͣ����������Ƿ�֧�ֵ��ж�.��������Ч���жϺ�������*/
/**********************************645����ʱ����***********************************/
	if( ( pV_645Frame->DI & 0xFFFF0000 ) != 0x04FE0000 )
	{
		;
	}
/*�ж��������3������������Mac/����/�����ж�*/
	if( Is_ParmType_3( pV_645Frame->DI, &WrParmTable, pV_645Frame->ChannelNo ) != C_OK )
	{
		V_ulData = SF_DIChangetoOAD(pV_645Frame->DI);
		if( ( V_ulData != 0 ) && ( ( pV_645Frame->DI & 0xFFFF0000 ) != 0x04010000 ) )
		{
			pV_645Frame->DI = V_ulData;
			V_ucFlag = C_NeedChangeTo698;
		}
		if( ( pV_645Frame->DI == CDate_Week ) || ( pV_645Frame->DI == CTime ) ) /*ԭ����Ϊ645���ݱ�ʶ���洢ҲΪ645��ʶ*/
		{
			V_ucFlag = C_NeedChangeTo698;
		}
		/*���*/
		V_ReturnData = LookFor_WrParmTable(pV_645Frame, &WrParmTable);
		if(V_ReturnData != C_OK)
		{/*��ʶ�벻�ԣ�Ӧ����������*/
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
			/*II����������ܼ�������Ч���ж�*/
			V_ReturnData = Comm_14_98SetParm(pV_645Frame, &WrParmTable, V_ucFlag);
		}
		else
		{
			/*����ȥ�ж�04��02�����룬���ܼ�������Ч���ж�*/
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
		/*III�����,����Ҫ���ֱ�Ӹ���pWrParmTableִ��������Ч���ж�*/
		/*ʵ���Ͼ����˸�����,��������*/
		V_ReturnData = Is_SetParmData_Ok(pV_645Frame, &WrParmTable);
		if(V_ReturnData !=C_OK)
		{
		  V_ReturnData = SF_Error_ChangeTo645(V_ReturnData);
			Comm_Response_Set_ReadErr(V_ReturnData, pV_645Frame);
			return;
		}
	}
/*�ж��Ƿ��Ǿ��ж�������¼��ı����Ŀ�����������⶯������Ŀ*/
/*�ǣ�����ö�Ӧ�Ĵ�����*/
/*����ֱ��д���ݲ�*/
	SV_Comm_Parse_Local.SafeControlFlag = SV_Comm_Parse_Local.SafeControlFlag | C_W_SafeFlag_3;
	pData = &pV_645Frame->Data[CData_14O_V_645];
	DataLen = pV_645Frame->DataLen - (CLen_DI + CLen_OpCode + CLen_CommPW);

	switch(WrParmTable.Method & C_HaveIPEventType)
	{
		case		C_HaveIPEvent_RstReportState:		/*��λ�����ϱ�״����*/
			SF_RstHaveReportState_645To698(&pV_645Frame->Data[C_Data_OFS_14]);	/*��698�����ϱ���698����645����*/
			Rst_SV_ReportNewAddNum(&pV_645Frame->Data[C_Data_OFS_14]);
			break;
		case		C_HaveIPEvent_Invalid:				/*�����⴦��ֱ��д���ݲ�*/
			if( ( pV_645Frame->DI == 0x04000C03 ) || ( pV_645Frame->DI == 0x04000C05 ) )
			{
				PF_CopyDataBytes(pData + 1, pData, 3);
			   DataLen = 4 - 1;							/*�ؼ�����Ҫд*/
			}
			Is_WriteDataOk = InF_Write_Data(C_Msg_Communication, pV_645Frame->DI, pData, (ushort16)DataLen, SV_Comm_Parse_Local.SafeControlFlag);
			break;
		default:
			Comm_Response_Set_ReadErr(C_Unauthorized_645, pV_645Frame);			/*�����ܵ�����*/
			return;
	}
/*����������Ϣ����?    �У��򴥷���Ӧ����Ϣ*/
	ExtMsgType = WrParmTable.Method & C_ExtMsgType;
	switch(ExtMsgType)
	{/*�����ⲿ��Ϣ*/
		case		C_ExtMsgType_Invalid:		/*���ⲿ��Ϣ��Ҫ����*/
			break;

		default:
			break;								/*�������ܵ�����.*/
	}
/*��֯��ȷӦ��֡*/
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
����ԭ�ͣ�void ReturnMoney_698()
�������ܣ�ͨ���˷�
�����������
�����������
���ز�������
����λ�ã���
��    ע���ڽ��뱾����֮ǰ�����ж�200�ι��������֤��ЧȨ��
***************************************************************************/
void ReturnMoney_698()
{
    uchar8 V_ucbuf[CLReturn_M_Note_1];
	ushort16 V_usDataLen, V_usDataEncode[30] = {0x00};
	uchar8 V_ucDataBuff[300] = {0};
	ushort16 V_usOffset = 0, V_ResidualLength, V_ucRelateoff;

	V_usOffset = SF_GetProgFixedData_698(CReturn_M_Degree, V_ucDataBuff);  /*ȡ�̶�������*/

    /*�˷ѱ�׼��¼��Ԫ,�¼���¼��BCD��ʽ���˷ѽ��*/
	PF_Ulong32ToBuffer4(&V_ucDataBuff[V_usOffset],&(MoneyClient_Table.V_ulMoney),CLReturn_M_Sum3);
	V_usOffset += CLReturn_M_Sum3;

	V_ResidualLength = 300 - V_usOffset;		/*ʣ��buff����*/
	V_ucRelateoff = V_usOffset;
	if(Inf_GetRecordData(&V_ucDataBuff[V_usOffset], &V_ResidualLength, CReturn_M_OADTab, C_ReadRecord_Hap) == C_OK)	/*��ȡ����OAD����*/
	{
		V_usOffset += V_ResidualLength;			/*�����ܳ���*/
	}

	InF_Write_Data(C_Msg_Communication, CReturn_M_Note_1, V_ucDataBuff, V_usOffset, C_W_SafeFlag);

     /*ͬ��ESAM*/
    V_usDataLen = CLChargeBal_Hex_Cent;
	if( InF_GetData_ObjectManage( CChargeBal_Hex_Cent, V_ucbuf, &V_usDataLen, V_usDataEncode ) == C_OK )
    {
        InF_S_UpdataChargeBalInESAM( V_ucbuf );
    }

    /*д������*/
	V_ResidualLength = 300 - V_ucRelateoff;
	if(Inf_GetRecordData(&V_ucDataBuff[V_ucRelateoff], &V_ResidualLength, CReturn_M_OADTab, C_ReadRecord_End) == C_OK)   /*ȡ��������*/
	{
		V_ucRelateoff += V_ResidualLength;
	}

	InF_Write_Data(C_Msg_Communication, (CReturn_M_Note_1 + 1), V_ucDataBuff, V_ucRelateoff, C_W_SafeFlag);

	Inf_EventReport_HP(C_ReturnMoneyEventNo,C_Happen_EventReport);

	return;
}
/***************************************************************************
����ԭ�� 	HaveIPEvent
��������	���������ı���¼���Ϣ
�������	*pV_645Frame			:���յ�645֡
������� 	��
���ز���	��
ȫ�ֱ��� 	�ڲ�ȫ����Ϣ��־
������ע
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
		case	CDate_Time:			/*Уʱ��¼��CDate_Week��CTime��CDate_Week_Time*/

			Comm_AppendMsg(CMsg_ProgDateTime);		/*Уʱ�����ϱ���Уʱ��������¼���ִ�С�*/
			return;
        case	CBroadcastTimeM:                	/*�㲥Уʱ��¼������ʱ�ӳ������ⷽ����ȫ��������CDate_Time*/
			Comm_AppendMsg(CMsg_BroadcastTime);		/*�㲥Уʱ�����ϱ���Уʱ��������¼���ִ�С�*/
			return;
		case	CActive_Com_State:					/*�й����״̬��*/
			Comm_AppendMsg(CMsg_ProgCombPState);
            Inf_EventReport_HP(C_ProgAcCEventNo, C_Happen_EventReport);
			return;
		case	CReactive_Com_State1:				/*�޹����״̬��1*/
			Comm_AppendMsg(CMsg_ProgCombQ1State);
            Inf_EventReport_HP(C_ProgReCEventNo, C_Happen_EventReport);
			return;
		case	CReactive_Com_State2:				/*�޹����״̬��2*/
			Comm_AppendMsg(CMsg_ProgCombQ2State);
            Inf_EventReport_HP(C_ProgReCEventNo, C_Happen_EventReport);
			return;
		case	CWeek_RestDay_DTable:				/*�����ղ�ȡ����ʱ�α��*/
			Comm_AppendMsg(CMsg_ProgWeekRest);
            Inf_EventReport_HP(C_ProgWReEventNo, C_Happen_EventReport);
			return;
		case	CSettle_Day1:						/*ÿ�µ�1������*/
		case	CSettle_Day2:
		case	CSettle_Day3:
			Comm_AppendMsg(CMsg_ProgSetADate);
            Inf_EventReport_HP(C_ProgSettDEventNo, C_Happen_EventReport);
			return;
		case	CFirst_TZone_Data:					/* ��1��ʱ����*/
		case	CSec_TZone_Data:
			Comm_AppendMsg(CMsg_ProgSeason);
            Inf_EventReport_HP(C_ProgPZEventNo, C_Happen_EventReport);

			return;
		case	CBackUp_RateFF_Price:				/*�����׷��ʵ�����ݿ�*/
			Comm_AppendMsg(CMsg_ProgRate);
			Inf_EventReport_HP(C_ProgTParaEventNo, C_Happen_EventReport);

			return;
		case	CBackUp_Ladder_Table:				/*�����׽��ݱ�*/
			Comm_AppendMsg(CMsg_ProgStepTariff);
            Inf_EventReport_HP(C_ProgLadEventNo, C_Happen_EventReport);

			return;
		case	CFirst_TZone_1PT_Data:				/*��1��ʱ�α���*/
		case	CFirst_TZone_2PT_Data:
		case	CFirst_TZone_3PT_Data:
		case	CFirst_TZone_4PT_Data:
		case	CFirst_TZone_5PT_Data:
		case	CFirst_TZone_6PT_Data:
		case	CFirst_TZone_7PT_Data:
		case	CFirst_TZone_8PT_Data:

		case	CSec_TZone_1PT_Data:				/*��2��ʱ�α���*/
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
			if((pV_645Frame->DI & 0xFFFFFF00) == 0x40110200)	/*���ù�������*/
			{
				Comm_AppendMsg(CMsg_ProgHoliday);
				Inf_EventReport_HP(C_ProgHolEventNo, C_Happen_EventReport);
				return;
			}
			return;
	}
}
/*******************************************************************************
����ԭ��:SetGPRSSignal
��������:����GPRS�źţ�����д�����ݲ�ͬʱ�����źŷ�����ʾ
�������:V_GPRSSignal:���յ���GPRS�ź�
�������:
���ز���:
ȫ�ֱ���:
������ע:698Э���ź�ǿ����������Ϊlong����λΪdBm��
*******************************************************************************/
void SetGPRSSignal( uchar8 *V_GPRSSignal )
{
	ulong32 V_ulGPRSSignal;
	float V_fSignal;

	GPRS_DisplayTimer = C_Init_GPRS_DisplayTimer;
	/*BCD��ʽrssi(dbm)д���ݲ�,��˼��4Gģ��ÿ15����дһ��*/
	InF_Write_Data( C_Msg_Communication, CGPS_Signal, V_GPRSSignal, CLGPS_Signal, C_W_SafeFlag );

	if( (V_GPRSSignal[1] & 0x80) != 0x80 )					/*rssi(dbm)Ϊ0������*/
	{
		Comm_SendMsgToDisp( C_GPRSSign, C_NotDisplay, C_Duration_Alway );
		Comm_SendMsgToDisp( C_GPRSSignalSign4, C_NotDisplay, C_Duration_Alway );
	}
	else													/*rssi(dbm)Ϊ����*/
	{
		/*��BCD��ʽrssi(dbm)ת��Ϊ����*/
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
			/*����rssi(dbm)����signal(csq)*/
			V_fSignal = ( 113 - (float)V_ulGPRSSignal ) / 2;
		}

		V_fSignal = V_fSignal / 8;							/*�ź�ǿ�ȷ�Ϊ4��*/

		if( V_fSignal <= 0 )								/*�����������*/
		{
			Comm_SendMsgToDisp( C_GPRSSign, C_NotDisplay, C_Duration_Alway );
			Comm_SendMsgToDisp( C_GPRSSignalSign4, C_NotDisplay, C_Duration_Alway );
		}
		else if( ( V_fSignal > 0 ) && ( V_fSignal <= 1 ) )
		{
			Comm_SendMsgToDisp( C_GPRSSign, C_AlwaysDisplay, C_Duration_Alway );			/*������ʾ���߷���*/
			Comm_SendMsgToDisp( C_GPRSSignalSign1, C_AlwaysDisplay, C_Duration_Alway );		/*��ʾ1����*/
		}
		else if( ( V_fSignal > 1 ) && ( V_fSignal <= 2 ) )
		{
			Comm_SendMsgToDisp( C_GPRSSign, C_AlwaysDisplay, C_Duration_Alway );			/*������ʾ���߷���*/
			Comm_SendMsgToDisp( C_GPRSSignalSign2, C_AlwaysDisplay, C_Duration_Alway );		/*��ʾ2����*/
		}
		else if( ( V_fSignal > 2 ) && ( V_fSignal <= 3 ) )
		{
			Comm_SendMsgToDisp( C_GPRSSign, C_AlwaysDisplay, C_Duration_Alway );			/*������ʾ���߷���*/
			Comm_SendMsgToDisp( C_GPRSSignalSign3, C_AlwaysDisplay, C_Duration_Alway );		/*��ʾ3����*/
		}
		else
		{
			Comm_SendMsgToDisp( C_GPRSSign, C_AlwaysDisplay, C_Duration_Alway );			/*������ʾ���߷���*/
			Comm_SendMsgToDisp( C_GPRSSignalSign4, C_AlwaysDisplay, C_Duration_Alway );		/*��ʾ4����*/
		}
	}
}

/***************************************************************************
����ԭ�� 	SetRTC_AppendMsg
��������	����ʱ�Ӵ�����Ϣ
�������	DestMsgAddressType	:ͨ��ʱ�Ӹ��ĺ󷢲���Ϣ��Ŀ�ĵ�ַ���͡�
									:����C_ExtMsgDestAddress��ʽ
				pV_645Frame			:���յ�645֡
������� 	��
���ز���	��
ȫ�ֱ���
������ע	ʱ����ǰ������Ҫ���ɼ�¼���㣬��ʱ��̫�������õ�Уʱ��¼��ִ�С�
***************************************************************************/
void	SetRTC_AppendMsg( ulong32 DestMsgAddressType, Str_Comm_645 *pV_645Frame )
{
	uchar8	Buf[CLDate_Time * 2 + 1];		/*ʱ���Ŵ�λ��1��ʼ��*/
	ushort16	DataLen, V_usDataEncode;

/*�Ƚ�ʱ�Ӹ�����Ϣ����������ж����ģ���*/
	SetParm_14_AppendMsg(C_ReworkTime, DestMsgAddressType);
/*ʱ�Ӹ���������Ϣ����*/
	DataLen = CLDate_Time;
	if( InF_Read_Data( CDate_Time, &Buf[1], &DataLen, &V_usDataEncode ) != C_OK )
	{
		/*���ʱ�Ӷ�����������ֻ�ܽ���ʱ�����ã��޷��㲥Уʱ*/
		return;
	}

/*���޸�ǰʱ��(7�ֽڣ�CDate_Time��ʽ)��������Ϣ������ģ��*/
	Buf[0] = Pt_SettleAdd_Time;
	Comm_SendMsg(Buf, (CLDate_Time+1),C_Msg_Freeze);

/*���޸�ǰʱ��(7�ֽڣ�CDate_Time��ʽ)��������Ϣ������ģ��*/
	Buf[0] = Pt_7DayAdd_FreezeTime;
	Comm_SendMsg(&Buf[0], (Pt_7DayAdd_FreezeTime_Len+1),C_Msg_Freeze);

#if 0	/*�޸�ʱ����������ѹ�ϸ��� �ѿ������¶��᲻�ϸ�*/
/*���޸�ǰ��ʱ��(7�ֽڣ�CDate_Time��ʽ)��������Ϣ����ѹ�ϸ���ģ�� �˲��������ϲ��ܷŵ����λ�� Ҫʱ�����óɹ����ٷ���Ϣ ��Ҫ���� lzy 20211014*/
	PF_CopyDataBytes(&pV_645Frame->Data[CData_14O_V_645],&Buf[CLDate_Time+1],CLDate_Time);
	Buf[0] = Pt_VRQTimeChange;
	Comm_SendMsg(Buf, (CLDate_Time*2+1),C_Msg_VoltageQualifiedRateMetering);
#endif

}

/***************************************************************************
����ԭ�� 	ReSettle_Day1_AppendMsg
��������	���õ�һ�����մ�����Ϣ
�������	DestMsgAddressType	:�޸ĵ�һ�����պ󷢲���Ϣ��Ŀ�ĵ�ַ���͡�
									:����C_ExtMsgDestAddress��ʽ
				pV_645Frame			:���յ�645֡
������� 	��
���ز���	��
ȫ�ֱ���
������ע
***************************************************************************/
void	ReSettle_Day1_AppendMsg( ulong32 DestMsgAddressType, Str_Comm_645 *pV_645Frame )
{
	uchar8	Buf[CLSettle_Day1];	/*��һ�����մ�Ŵ�λ��0��ʼ��*/
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
����ԭ�� 	SetParm_14_AppendMsg
��������	14������ⲿ��Ϣ(ͨ����)
�������	ParmType				:���ĵĲ������ͣ�ȡֵ:
									C_ReMultiRatesParm,C_ReDemand_Cycle,C_ReSettle_Day1,C_ReWorkTime��
				DestMsgAddressType	:Ŀ�ĵ�ַ���Ͳ���C_ExtMsgDestAddress��ʽ
������� 	��
���ز���	��
ȫ�ֱ���
������ע
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
			case		C_ExtMsgDA_Demand:		/*����Ϣ������ģ��*/
				Comm_SendMsgForUpdataParm(ParmType, C_Msg_DemandMetering);
				break;
			case		C_ExtMsgDA_MultiRates:		/*ʱ�η���ģ��*/
				Comm_SendMsgForUpdataParm(ParmType, C_Msg_Deal_MultiRates);
				break;
			case		C_ExtMsgDA_Settle:		/*������ģ��*/
				Comm_SendMsgForUpdataParm(ParmType, C_Msg_SettleAccounts);
				break;
			case		C_ExtMsgDA_EnergyMetering:	/*����ģ��*/
				Comm_SendMsgForUpdataParm(ParmType, C_Msg_EnergyMetering);
				break;
			default:
				break;
		}
		ExtMsgDestAddress = ExtMsgDestAddress << 1;
	}
}
/*******************************************************************************
����ԭ�ͣ�void SF_645Meter_Work_Char1_Deal698(Str_Comm_645 *pV_645Frame)
����������д645�������������1��ͬ��698��LCD�����Ϳ�������
���������*pV_645Frame:���յ�������֡
�����������
���ز�������
����λ�ã�ͨ��14д
��    ע��
*******************************************************************************/
void SF_645Meter_Work_Char1_Deal698(Str_Comm_645 *pV_645Frame)
{
    uchar8   V_ucData, V_ucMeter_Work_Type = 0;
	ushort16 V_ucMeter_Work_Len = CLMeter_Work_Char1, V_usDataEncode;

    V_ucData = (pV_645Frame->Data[CData_14O_V_645] >> 1) & 0x01;    /*ȡ������1�е�Һ����ʾ�٢�����*/
    InF_Write_Data(C_Msg_Communication, C1And2Display, &V_ucData, CL1And2Display, C_W_SafeFlag);

    V_ucData = pV_645Frame->Data[CData_14O_V_645] & 0x01;           /*ȡ������1�е����ÿ��Ʒ�ʽ*/
    InF_Read_Data(CMeter_Work_Char1, &V_ucMeter_Work_Type, &V_ucMeter_Work_Len, &V_usDataEncode);	/*��������*/
    V_ucMeter_Work_Type &= 0xFE;
    V_ucMeter_Work_Type |= (~V_ucData);
    InF_Write_Data(C_Msg_Communication, CMeter_Work_Char1, &V_ucMeter_Work_Type, CLMeter_Work_Char1, C_W_SafeFlag);
}
/***************************************************************************
����ԭ�� 	Comm_14_04SetParm
��������	����ע
�������	*pV_645Frame				:���յ�������֡
				pWrParmTable				:���ز�����������ݵ�ַ
������� 	*pTBParmLineNo			:���ز������������
���ز���	C_OK/C_Unauthorized/C_OtherErr/
				/C_Baud_NotModified/C_SeasonNum_OV/C_PeriodNum_OV/C_RateNum_OV
ȫ�ֱ��� 	��
������ע	1�������ܼ��жϡ�
				2�������ܼ��жϡ�
				3�����ȡ����ݺϷ����ж�
***************************************************************************/
uchar8 Comm_14_04SetParm( Str_Comm_645 *pV_645Frame, Str_WrParmTable *pWrParmTable, uchar8 V_Flag)
{
	uchar8	Err;
	/*�ж��ܼ��Ƿ���ȷ*/
	if( (pV_645Frame->Data[CPW_14OV_645] != 0x02)
		&&(pV_645Frame->Data[CPW_14OV_645] != 0x04) )
	{
		return(C_Unauthorized);
	}
	/*�ж��Ƿ��ڣ����ڳ�����02��04�����ò���Ӧ����Ȩ��*/
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
	/*�ж������Ƿ���ȷ*/
	if( ( pV_645Frame->DI != C_OddHar_AddData1 ) && ( pV_645Frame->DI != C_OddHar_AddData2 ) ) /*���г��������������*/
	{
		Err = Is_PW_OK(&pV_645Frame->Data[CPW_14OV_645]);
		if(Err != C_OK)
		{
			return(C_Unauthorized);
		}
	}
/*���ȡ����ݺϷ����ж�*/
/*���ݺϷ��Ե��ж�*/
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
����ԭ�� 	SF_EventDelayTimeBCDtoHex
��������	:   �¼���ʱ����BCD ת���� Hex
�������	:   *pV_645Frame   :���յ�������֡
�������: 	��
���ز���	��  ��
ȫ�ֱ�����	��
������ע��
***************************************************************************/
void SF_EventDelayTimeBCDtoHex(Str_Comm_645 *pV_645Frame)
{
    uchar8 j, V_ucData[4] = {0};
    ulong32 V_ulData = 0;

    for(j = 0; j < C_TB_EventDelayTime_Len; j++)		/*�¼���ʱ����*/
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
����ԭ�� 	SF_EventParaSpecial
��������	:   ��1�ֽ�0x00��TB_WrParm�в����¼�C_DataValidSpecialMethodת����4�ֽ����ݣ�������1�ֽ���0x00
�������	:   *pV_645Frame   :���յ�������֡
�������: 	*pV_645Frame   :���յ�������֡
���ز���	��  ��
ȫ�ֱ�����	��
������ע��  �����漰�¼�������TB_EventParaSpecial
***************************************************************************/
void SF_EventParaSpecial(Str_Comm_645 *pV_645Frame)
{
    uchar8 j;

    for(j = 0; j < C_TB_EventParaSpecial_Len; j++)/*�¼���ʱ����*/
    {
        if(pV_645Frame->DI == TB_EventParaSpecial[j])
        {
            memset(&pV_645Frame->Data[CData_14O_V_645 + CLLossVolage_Curr_LowLim], 0x00, 1);/*����C_DataValidSpecialMethod��ת��Ϊ4�ֽڣ����Բ�1�ֽ�0x00*/
            break;
        }
    }
}
/***************************************************************************
����ԭ�� 	SF_Deal_Comm_98SetParm
��������	:   ����д�봦��
�������	:   *pV_645Frame   :���յ�������֡
�������: 	��
���ز���	��C_OK/C_Unauthorized/C_OtherErr/
				/C_Baud_NotModified/C_SeasonNum_OV/C_PeriodNum_OV/C_RateNum_OV
ȫ�ֱ�����	��
������ע��
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

        /*�ж����ݵĺ�����*/
        if( Is_CommBPS_OK(C_RS485_1, V_ucBuffer[0]) != C_OK )
        {
            return C_Baud_NotModified;
        }
        else
        {
            PF_Ulong32ToBuffer4(pV_645Frame->Data, &(pV_645Frame->DI), CLen_DI);    /*OAD*/
            memset(pV_645Frame->Data + CLen_DI, 0x00, CLen_OpCode);                 /*�����ߴ���*/

            memcpy(pV_645Frame->Data + 12, V_ucBuffer, V_ucDataLen);
            pV_645Frame->DataLen = CLen_DI+CLen_OpCode + CLen_CommPW + CLOne485_Baud;
        }
    }
    else if(pV_645Frame->DI == COverCurr_Curr_LowLim)
    {
        pV_645Frame->DataLen = CLOverCurr_Curr_LowLim + CData_14O_V_645;
        PF_Buffer4ToUlong32(&pV_645Frame->Data[CData_14O_V_645], &V_ulData, CLOverCurr_Curr_LowLim645);
        V_ulData = V_ulData << 12;/*698Ϊ4λС����645Ϊ1λС��*/
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
����ԭ�� 	Comm_14_98SetParm
��������	����ע
�������	*pV_645Frame				:���յ�������֡
				pWrParmTable				:���ز�����������ݵ�ַ
������� 	*pWrParmTable			:���ز������������
			 	pV_645Frame->DataLen						:���ݳ��ȣ�����DI,PW,OPCode,�����ݳ���
				pV_645Frame->Data[CData_14O_V_645]		:���ܺ������
���ز���	C_OK/C_Unauthorized/C_OtherErr/
				/C_Baud_NotModified/C_SeasonNum_OV/C_PeriodNum_OV/C_RateNum_OV
ȫ�ֱ��� 	��
������ע	1�����II������Ľ��ܼ������ݷ�дpV_645Frame->Data[CData_14O_V_645]
				2����ɽ��ܺ󳤶ȷ�дpV_645Frame->DataLen
				2����ɽ��ܺ����ݺϷ��ԡ������ж�
***************************************************************************/
uchar8	Comm_14_98SetParm(Str_Comm_645 *pV_645Frame, Str_WrParmTable *pWrParmTable, uchar8 V_Flag)
{
	ushort16	Serror;
	uchar8	ValidDataLen;
	uchar8	Err;
    uchar8  V_ucBlock;
    ulong32 V_ulMethod;
/*�Ƿ�Ϊ1��������ж�,98����������1�����*/
	if( InF_S_Is_ParmPlainTextMAC( pV_645Frame->DI, &ValidDataLen ) == C_OK )
	{
		return(C_Unauthorized);
	}
/*���ȵĳ����ж�*/
	if( pV_645Frame->DataLen > ( CLen_DI + CLen_OpCode + CLen_CommPW ) )
	{
		ValidDataLen = pV_645Frame->DataLen -  (CLen_DI + CLen_OpCode + CLen_CommPW );
	}
	else
	{
		return(C_OtherErr);
	}
/*����*/
	if(pV_645Frame->DI != CReturn_Money)
	{
		Serror = InF_S_WritePara_CipherTextMAC(pV_645Frame->DI, &pV_645Frame->Data[CData_14O_V_645],&ValidDataLen);
		if(Serror == C_SERR_ESAM_VF)
		{
			Comm_DealwithSPTVariable(C_SPTNumAdd);	/*ESAM��֤ʧ�ܡ�*/
			return(C_Unauthorized);
		}
		else if(Serror != C_OK)
		{
			return(C_OtherErr);
		}
		else
		{
			/*��ȷ���ܣ���ֵpV_645Frame->DataLen*/
			pV_645Frame->DataLen = ValidDataLen + CLen_DI + CLen_OpCode + CLen_CommPW;
		}

		/*���ݺϷ��Ե��ж�*/
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
		{/*0514-70�ж��˷������Ĺ涨�������������̴���*/
			Serror = InF_S_WR_ReturnFile( &pV_645Frame->Data[CData_14O_V_645], ValidDataLen);
			if(Serror == C_SERR_ESAM_VF)
			{
				Comm_DealwithSPTVariable(C_SPTNumAdd);	/*ESAM��֤ʧ�ܡ�*/
				return(C_Unauthorized);
			}
			else if(Serror != C_OK)
			{
				return(C_OtherErr);
			}
			else
			{
				/*��ȷ���ܣ���ֵpV_645Frame->DataLen*/
				pV_645Frame->DataLen = (CLReturn_Money + C_MacLen) + CLen_DI + CLen_OpCode + CLen_CommPW;
			}
			/*Ǯ���ļ�ͬ��,���ж�ʣ�����Ƿ���	*/
			if(DV_Return_Money(pV_645Frame) !=C_OK)
			{
				return(C_OtherErr);
			}
			/*����ESAM�˷���֤*/
			Serror = InF_S_OPMoneyFile_Return(&pV_645Frame->Data[CData_14O_V_645]);
			if(Serror == C_SERR_ESAM_VF)
			{
				Comm_DealwithSPTVariable(C_SPTNumAdd);	/*ESAM��֤ʧ�ܡ�*/
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
����ԭ�� 	Comm_14_99SetParm
��������	����ע
�������	*pV_645Frame				:���յ�������֡
				pWrParmTable				:���ز�����������ݵ�ַ
������� 	*pWrParmTable			:���ز������������
				pV_645Frame->DataLen						:���ݳ��ȣ�����DI,PW,OPCode��������Mac
				pV_645Frame->Data[CData_14O_V_645]		:���ܺ������
���ز���	C_OK/C_Unauthorized/C_OtherErr/

ȫ�ֱ��� 	��
������ע	1������Ƿ�Ϸ����ж�(�Ƿ�Ϊ1����������ݱ����Ƿ�Ϸ�)
				2������Ƿ���Ҫ������Կ�������õ��ж�
				3�����I�������Mac����
				4��дESAM��
				5�����ݷ�дpV_645Frame->DataLen
***************************************************************************/
uchar8	Comm_14_99SetParm(Str_Comm_645 *pV_645Frame, Str_WrParmTable *pWrParmTable)
{
	ushort16	Serror;
	uchar8	Err;
	uchar8	ValidDataLen;

/*�Ƿ�Ϊ1��������ж�*/
	if( InF_S_Is_ParmPlainTextMAC(pV_645Frame->DI, &ValidDataLen) != C_OK )
	{
		return(C_Unauthorized);
	}
/*�ж��Ƿ���������ڹ�Կ�²��ԣ���ȷʵ�ڹ�Կ�¡�*/
	if(InF_JudgeKeyStatus() == C_StateOfOfficialKey)
	{
		/*Ϊ��ʽ��Կ*/
		if( ( pV_645Frame->DI == CCustomer_Num ) || ( pV_645Frame->DI == CMeter_Num ) )
		{/*��ʽ��Կ�£��������ÿͻ���źͱ��*/
			return(C_Unauthorized);
		}
	}

/*���ݺϷ��Ե��ж�*/
	pV_645Frame->DataLen = pV_645Frame->DataLen - C_MacLen;	/*ȥ��MAC���ȣ����ж����ݺϷ���*/
	Err = Is_SetParmData_Ok(pV_645Frame, pWrParmTable);
	if( Err != C_OK )
	{
		return(Err);
	}
/*����Mac*/
	ValidDataLen = pV_645Frame->DataLen - ( CLen_DI + CLen_OpCode + CLen_CommPW );
	ValidDataLen = ValidDataLen + C_MacLen;					/*��ΪpV_645Frame->DataLenǰ���ȥMac������	*/
	Serror = InF_S_WritePara_PlainTextMAC(pV_645Frame->DI, &pV_645Frame->Data[CData_14O_V_645], ValidDataLen);
	if(Serror == C_SERR_ESAM_VF)
	{
		Comm_DealwithSPTVariable(C_SPTNumAdd);				/*ESAM��֤ʧ�ܡ�*/
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
/*�����ɲμ�����ĵ�"ͨ��ģ��"�½�֮<������Ч�Լ���������>   */
const	Str_WrParmTable	TB_WrParm[] = {
/* 0x04000101	  �����ܴ�	*/
	{CDate_Week,
/*		����         |      ���ȹ̶� |    ����  |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenUnsized|C_UnsizedLen_Date|C_DataValidSpecialMethod|C_DV_Date_Time_645|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ	*/
	C_HaveIPEvent_ProgParm |C_ExtMsg_ReWorkTime|C_ExtMsgDA_Demand|C_ExtMsgDA_MultiRates)},

/* 0x04000102	  ʱ��	*/
	{CTime,
/*		����         |      ���ȹ̶� |    ����  |   ������Ч���жϷ��� 	*/
	(C_UnAddFixedDataLen|C_DataLenUnsized|C_UnsizedLen_Time|C_DataValidSpecialMethod|C_DV_Date_Time_645|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ	*/
	C_HaveIPEvent_ProgParm |C_ExtMsg_ReWorkTime|C_ExtMsgDA_Demand|C_ExtMsgDA_MultiRates)},

/* 0x40000200	  �����ܴμ�ʱ��	*/
	{CDate_Time,
/*		����         |      ���ȹ̶� |    ����             |   ������Ч���жϷ���		*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLDate_Time|C_DataValidSpecialMethod|C_DV_Date_Time|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ	*/
	C_HaveIPEvent_ProgParm |C_ExtMsg_ReWorkTime|C_ExtMsgDA_Demand|C_ExtMsgDA_MultiRates)},

/*0x41000200	 ��������	*/
	{CDemand_Cycle,
/*		����         |      ���ȹ̶� |    ����         |   ������Ч���жϷ���	*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLDemand_Cycle|C_DataValidSpecialMethod|C_DV_Demand_Cycle|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ	*/
	C_HaveIPEvent_Invalid |C_ExtMsg_ReDemand_Cycle|C_ExtMsgDA_Demand)},

/*0x41010200 ��������	*/
	{CSliding_Time,
/*		����         |      ���ȹ̶� |    ����       |   ������Ч���жϷ���	*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLSliding_Time|C_DataValidSpecialMethod|C_DV_Sliding_Time|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ	*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x40080200 ����ʱ�����л�ʱ��*/
	{CChange_TZ_Time,
/*		����         |      ���ȹ̶� |    ����             |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLChange_TZ_Time|C_DataValidSpecialMethod|C_DV_SwitchingTime|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ	*/
	C_HaveIPEvent_Invalid |C_ExtMsg_ReMultiRatesParm|C_ExtMsgDA_MultiRates)},

/*0x40090200 ����ʱ�α��л�ʱ��*/
	{CChange_PT_Time,
/*		����         |      ���ȹ̶� |    ����             |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLChange_PT_Time|C_DataValidSpecialMethod|C_DV_SwitchingTime|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ	*/
	C_HaveIPEvent_Invalid |C_ExtMsg_ReMultiRatesParm|C_ExtMsgDA_MultiRates)},

/*0x400A0200 ���׷��ʵ���л�ʱ��*/
	{CChange_Rate,
/*		����                |      ���ȹ̶� |    ����             |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLChange_Rate|C_DataValidSpecialMethod|C_DV_SwitchingTime|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsg_ReMultiRatesParm|C_ExtMsgDA_MultiRates)},

/*0x400B0200 ���׽��ݵ���л�ʱ��*/
	{CChange_Ladder,
/*		����                |      ���ȹ̶� |    ����             |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLChange_Ladder|C_DataValidSpecialMethod|C_DV_SwitchingTime|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsg_ReMultiRatesParm|C_ExtMsgDA_MultiRates)},

/*0x400C0201 ��ʱ����*/
	{CYear_Zone_Num,
/*		����         |      ���ȹ̶� |    ����             |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLYear_Zone_Num|C_DataValidHex_Range|C_DV_HexRange_1_14|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsg_ReMultiRatesParm|C_ExtMsgDA_MultiRates)},

/*0x400C0202 ��ʱ�α���*/
	{CDay_Table_Num,
/*		����         |      ���ȹ̶� |    ����             |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLDay_Table_Num|C_DataValidHex_Range|C_DV_HexRange_1_8|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsg_ReMultiRatesParm|C_ExtMsgDA_MultiRates)},

/*0x400C0203 ��ʱ����*/
	{CDay_Time_Num,
/*		����         |      ���ȹ̶� |    ����             |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLDay_Time_Num|C_DataValidHex_Range|C_DV_HexRange_1_14|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsg_ReMultiRatesParm|C_ExtMsgDA_MultiRates)},

/*0x400C0204 ������*/
	{CRate_Num,
/*		����         |      ���ȹ̶� |    ����             |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLRate_Num|C_DataValidHex_Range|C_DV_HexRange_Rates|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsg_ReMultiRatesParm|C_ExtMsgDA_MultiRates)},

/*0x400C0205 ����������*/
	{CHoliday_Num,
/*		����         |      ���ȹ̶� |    ����             |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLHoliday_Num|C_DataValidHex_Range|C_DV_HexRange_0_20|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsg_ReMultiRatesParm|C_ExtMsgDA_MultiRates)},

/*0x400D0200 ������*/
	{CStep_Num,
/*		����         	     |      ���ȹ̶� |    ����             |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLStep_Num|C_DataValidHex_Range|C_DV_HexRange_0_6|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsg_ReMultiRatesParm|C_ExtMsgDA_MultiRates)},

/*0x400F0200 ��Կ������*/
	{CKey_Tol_Num,
/*		����         |      ���ȹ̶� |    ����             |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLKey_Tol_Num|C_DataValidHex_Range|C_DV_HexRange_1_32|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsg_SetKeyNum)},		/*������Կ���¼����Ϣ�������Ŀ�ĵ�ַ*/

/*0xF3000401 �Զ�ѭ������*/
	{CAuto_Dis_Screen_Num,
/*		����         |      ���ȹ̶� |    ����                      |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLAuto_Dis_Screen_Num|C_DataValidHex_Range|C_DV_HexRange_1_99|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0xF3000300 ÿ����ʾʱ��*/
	{CPer_Dis_Screen_Time,
/*		����         |      ���ȹ̶� |    ����                      |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLPer_Dis_Screen_Time|C_DataValidHex_Range|C_DV_HexRange_5_20|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x40070205 ����С��λ��*/
	{CEnergy_Decimal_Num,
/*		����         |      ���ȹ̶� |    ����                      |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLEnergy_Decimal_Num|C_DataValidHex_Range|C_DV_HexRange_0_4|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x40070206 ��ʾ���ʣ����������С��λ��*/
	{CPower_Decimal_Num,
/*		����         |      ���ȹ̶� |    ����                      |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLPower_Decimal_Num|C_DataValidHex_Range|C_DV_HexRange_0_6|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0xF3010401 ����ѭ����ʾ����*/
	{CKey_CycDis_Screen_Num,
/*		����         |      ���ȹ̶� |    ����                      |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLKey_CycDis_Screen_Num|C_DataValidHex_Range|C_DV_HexRange_1_99|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x40070201 �ϵ�ȫ��ʱ��*/
	{CPowerOn_Dis_All_Time,
/*		����         |      ���ȹ̶� |    ����                      |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLPowerOn_Dis_All_Time|C_DataValidHex_Range|C_DV_HexRange_5_30|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x40070207		Һ���٢���������*/
	{C1And2Display,
/*		����         |      ���ȹ̶� |    ����                      |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CL1And2Display|C_DataValidHex_Range|C_DV_HexRange_0_1|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgDA_MultiRates|C_ExtMsg_ReMultiRatesParm|C_ExtMsgType_Invalid)},

/*0x40010200 ͨѶ��ַ(Ӧ��ʱͨ�ŵ�ַ���ʲô?ȫ99?)*/
	{CComm_Address,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLComm_Address|C_DataValidSpecialMethod|C_DV_Comm_Address|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x40020200 ���*/
	{CMeter_Num,
/*		����         |      ���ȹ̶� |    ����      |   ������Ч���жϷ���*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLMeter_Num|C_DataValidOnlyBCD|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x41030200 �ʲ��������*/
	{CManage_Code,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLManage_Code|C_DataValid_NoLimit|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x41040200 ���ѹ*/
	{CRated_Vol,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLRated_Vol|C_DataValid_NoLimit|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x41050200 �����*/
	{CRated_Curr,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLRated_Curr|C_DataValid_NoLimit|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x41060200 ������*/
	{CMax_Curr,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLMax_Curr|C_DataValid_NoLimit|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x41060300 ��С����*/
	{CMin_Curr,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLMin_Curr|C_DataValid_NoLimit|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x41060400 ת�۵���*/
	{CTurn_Curr,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLTurn_Curr|C_DataValid_NoLimit|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x41070200 �й�׼ȷ�ȵȼ�*/
	{CActive_Accur_Deg,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLActive_Accur_Deg|C_DataValid_NoLimit|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x41080200 �޹�׼ȷ�ȵȼ�*/
	{CReactive_Accur_Deg,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLReactive_Accur_Deg|C_DataValid_NoLimit|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x410B0200 ����ͺ�*/
	{CMeter_Model,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLMeter_Model|C_DataValid_NoLimit|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x43000400 ��������*/
	{CProd_Date,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLProd_Date|C_DataValidSpecialMethod|C_DV_Date_Time|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x40030200 �ͻ����*/
	{CCustomer_Num,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLCustomer_Num|C_DataValidOnlyBCD|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

//0x0400040F ���ܱ�λ����Ϣ
	{CMeter_Position,
//		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLMeter_Position|C_DataValidSpecialMethod|C_DV_Position|
//      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x41120200 �й����״̬��*/
	{CActive_Com_State,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLActive_Com_State|C_DataValid_NoLimit|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_ProgParm |C_ExtMsgType_Invalid)},

/*0x41130200 �޹����״̬��1*/
	{CReactive_Com_State1,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLReactive_Com_State1|C_DataValid_NoLimit|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_ProgParm |C_ExtMsgType_Invalid)},

/*0x41140200 �޹����״̬��2*/
	{CReactive_Com_State2,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLReactive_Com_State2|C_DataValid_NoLimit|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_ProgParm |C_ExtMsgType_Invalid)},

/*0xF2020201 �����ͺ����ڲ�����������*/
	{CMod_InFr_Baud,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLMod_InFr_Baud|C_DataValidSpecialMethod|C_DV_Bps|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0xF2010201 1·485������������*/
	{COne485_Baud,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLOne485_Baud|C_DataValidSpecialMethod|C_DV_Bps|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0xF2010202 2·485������������*/
	{CTwo485_Baud,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLTwo485_Baud|C_DataValidSpecialMethod|C_DV_Bps|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0xF2090201 ģ��ͨ��������������*/
	{CModular_Baud,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLModular_Baud|C_DataValidSpecialMethod|C_DV_Bps|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0xF20902FD ģ��ͨ��Э�̲�����������*/
	{CModular_BaudConsult,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLModular_BaudConsult|C_DataValidSpecialMethod|C_DV_Bps|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x40130200 �����ղ�ȡ����ʱ�α��*/
	{CWeek_RestDay_DTable,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLWeek_RestDay_DTable|C_DataValidHex_Range|C_DV_HexRange_1_8|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_ProgParm |C_ExtMsg_ReMultiRatesParm|C_ExtMsgDA_MultiRates)},

/*0x41160201 ÿ�µ�1������*/
	{CSettle_Day1,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLSettle_Day1|C_DataValidSpecialMethod|C_DV_Settle_Day|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_ProgParm |C_ExtMsg_ReSettle_Day1|C_ExtMsgDA_Settle)},

/*0x41160202 ÿ�µ�2������*/
	{CSettle_Day2,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLSettle_Day2|C_DataValidSpecialMethod|C_DV_Settle_Day|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_ProgParm |C_ExtMsgType_Invalid)},

/*0x41160203 ÿ�µ�3������*/
	{CSettle_Day3,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLSettle_Day3|C_DataValidSpecialMethod|C_DV_Settle_Day|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_ProgParm |C_ExtMsgType_Invalid)},

/*0x04000C03 2������*/
	{CKey_2_Class,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenUnsized|C_UnsizedLen_PW|C_DataValidOnlyBCD|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

	/*0x44010200 698����*/
	{C698Key,
/*		����         |      ���ȹ̶� |    ����      |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CL698Key|C_DataValid_NoLimit|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x04000C05 4������*/
	{CKey_4_Class,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenUnsized|C_UnsizedLen_PW|C_DataValidOnlyBCD|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x401E0201 �������1��ֵ*/
	{CAlam1_Money,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLAlam1_Money|C_DataValid_NoLimit|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsg_ReLocalWarningPara|C_ExtMsgDA_EnergyMetering)},

/*0x401E0202 �������2��ֵ*/
	{CAlam2_Money,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLAlam2_Money|C_DataValid_NoLimit|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsg_ReLocalWarningPara|C_ExtMsgDA_EnergyMetering)},

/*0x401F0201 ͸֧�����ֵ*/
	{COverDraft_Money,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLOverDraft_Money|C_DataValid_NoLimit|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsg_ReLocalWarningPara|C_ExtMsgDA_EnergyMetering)},

/*0x04001006 �˷ѽ�� �˶��Ƿ���Ҫ���� lzy 20211003*/
	{CReturn_Money,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLReturn_Money|C_DataValidSpecialMethod|C_DV_Return_Money|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_ReturnMoney |C_ExtMsgType_Invalid)},

/*0x41100200 �������������1*/
	{CMeter_Work_Char1,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLMeter_Work_Char1|C_DataValid_NoLimit|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsg_ReMultiRatesParm|C_ExtMsgDA_MultiRates)},

/*0x20150400 �����ϱ�ģʽ��*/
	{CDrive_Report_Mode,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLDrive_Report_Mode|C_DataValid_NoLimit|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x20150500 �����ϱ�״̬��*/
	{CDrive_Report_Type,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLReport_Type|C_DataValidHex_Range|C_DV_HexRange_0_1|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x04001405 �����ϱ��Զ���λ��ʱʱ��*/
	{CRst_ReportState_Timer,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLRst_ReportState_Timer|C_DataValidOnlyBCD|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x40190200 �����׷��ʵ�����ݿ�*/
	{CBackUp_RateFF_Price,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenUnsized|C_UnsizedLen_BackUpRateFFPrice|C_DataValid_NoLimit|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_ProgParm |C_ExtMsgType_Invalid)},

/*0x401B0200 �����׽��ݱ�*/
	{CBackUp_Ladder_Table,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenUnsized|C_UnsizedLen_BackUpLadder|C_DataValidSpecialMethod|C_DV_Ladder|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_ProgParm |C_ExtMsgType_Invalid)},

/*0x43000302 ��������汾��*/
	{CFactory_Softw_Version,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLFactory_Softw_Version|C_DataValid_NoLimit|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x43000304 ����Ӳ���汾��*/
	{CFactory_Hardw_Version,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLFactory_Hardw_Version|C_DataValid_NoLimit|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x43000301 ���ұ��*/
	{CFactory_Number,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLFactory_Number|C_DataValid_NoLimit|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x43000601 ֧��ͨ�Ź�Լ1*/
	{CMeter_CommPro1,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLMeter_CommPro1|C_DataValid_NoLimit|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x43000602 ֧��ͨ�Ź�Լ2*/
	{CMeter_CommPro2,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLMeter_CommPro2|C_DataValid_NoLimit|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x41110200 ���������*/
	{CSoftw_Record_Number,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLSoftw_Record_Number|C_DataValid_NoLimit|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/* 0x44000305		Э��һ���Կ�*/
	{CAppProConsistency,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLAppProConsistency|C_DataValid_NoLimit|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*	0x44000306		����һ���Կ�*/
	{CAppFunConsistency,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLAppFunConsistency|C_DataValid_NoLimit|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*CConAutheMechanism			0x44000500		������֤����*/
	{CConAutheMechanism,
/*		����         |      ���ȹ̶� |    �� ��                |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLConAutheMechanism|C_DataValidHex_Range|C_DV_HexRange_0_3|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0xF1010200	��ȫģʽ�Ƿ���*/
	{CSafeModePara,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLSafeModePara|C_DataValidHex_Range|C_DV_HexRange_0_1|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x43000800		�����ϱ������־*/
	{CAllowAccordUpTell,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLAllowAccordUpTell|C_DataValidHex_Range|C_DV_HexRange_0_1|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x43000700		�����ϱ������־*/
	{CAllowFollowUpTell,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLAllowFollowUpTell|C_DataValidHex_Range|C_DV_HexRange_0_1|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x43000900		�Ի������־*/
	{CAllowMasterCall,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLAllowMasterCall|C_DataValidHex_Range|C_DV_HexRange_0_1|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x43000200		�豸������*/
	{CEquipmentDis,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_AddFixedDataLen|C_DataLenUnsized|CLEquipmentDis|C_DataValid_NoLimit|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},
/*0x43000A00		�ϱ�ͨ��*/
	{CUpTellChannel,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenUnsized|C_UnsizedLen_ReportChannel|C_DataValidSpecialMethod|C_DV_ReportChannel|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x04001104 645�����ϱ�ģʽ�� 698����645����*/
	{CDrive_Report_Mode_645 ,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLDrive_Report_Mode_645 |C_DataValid_NoLimit|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsgType_Invalid)},

/*0x04001101 645�������������1 698����645����*/
	{CMeter_Work_Char1_645,
/*		����         |      ���ȹ̶� |    ����           |   ������Ч���жϷ���*/
	(C_UnAddFixedDataLen|C_DataLenFixed_OK|CLMeter_Work_Char1_645|C_DataValid_NoLimit|
/*      ��������¼�	  |����������Ϣ|Ŀ�ĵ�ַ*/
	C_HaveIPEvent_Invalid |C_ExtMsg_ReMultiRatesParm|C_ExtMsgDA_MultiRates)},
};
#define	CLen_TB_WrParm		(sizeof(TB_WrParm) / sizeof(Str_WrParmTable))
/***************************************************************************
����ԭ�� 	Is_SetParmData_Ok
��������	�ж����ò������ȼ����ݺϷ���
�������	*pV_645Frame				:���յ�������֡
				*pWrParmTable			:�������������
�������
				pV_645Frame->DataLen						:���ݳ��ȣ�����������е���
				pV_645Frame->Data[CData_14O_V_645]		:���������ݻᲹ������
���ز���	C_OK/C_Unauthorized/C_OtherErr/
				/C_Baud_NotModified/C_SeasonNum_OV/C_PeriodNum_OV/C_RateNum_OV
ȫ�ֱ���
������ע	pV_645Frame����98����99�����ñ�����ʱ��
				pV_645Frame->DataLen��Data[]����ʽ��������04�ܼ�Ҫ��
***************************************************************************/
uchar8	Is_SetParmData_Ok( Str_Comm_645 *pV_645Frame, Str_WrParmTable *pWrParmTable )
{
	uchar8	Err;
/*�����Ƿ�֧�ָ������������ط��Ѿ������ж�*/
/*�жϳ����Ƿ���ȷ������ǲ��������������ݣ��޸�DataLen*/
	Err = Is_14_DataLenOk(pV_645Frame, pWrParmTable);
	if( Err != C_OK )
	{
		return(Err);
	}
/*�ж�������Ч��.*/
	Err = Is_14_DataValid(pV_645Frame, pWrParmTable);
	return(Err);
}
/***************************************************************************
����ԭ�� 	Is_14_DataValid
��������	�ж�14�������ݺϷ���
�������	*pV_645Frame				:���յ�������֡
				*pWrParmTable			:�������ñ������������
�������
���ز���	C_OK/C_OtherErr/
ȫ�ֱ��� 	��
������ע	��
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
	ValidLen = pV_645Frame->DataLen - (CLen_DI + CLen_OpCode + CLen_CommPW);	/*����������ǰ���ȺϷ���*/

/*����14��������������Ч���ж����ͼ���ͬ���������ж�*/
	switch( MethodType )
	{
		case C_DataValid_NoLimit:			/*û���κ�����*/
		{
			return(C_OK);
		}break;

		case C_DataValidHex_Range:			/*ͨ�÷���4��Hex����ΧAA-BB��Bit13-9��BCD��Χ����1-32��*/
		{
			/*���������Χ���ǵ��ֽ������жϣ�ͳһ�����жϡ�������2�ֽڵ��������ж�*/
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

		case C_DataValidOnlyBCD:				/*ͨ�÷���3��BCD��������Χ���ơ�Bit12-Bit8ֵ��Ч*/
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

		case C_DataValidBCD_Range:				/*�÷���2��BCD����ΧAA-BB ��ʱδ�õ�*/
		{
			return(C_OK);
		}break;

		case C_DataValidSpecialMethod:			/*���ⷽ��*/
		{
			switch( Method )
			{
				case C_DV_Date_Time_645:		/*���ⷽ��֮����ʱ���ж�,645��ʱ��0x04000101��0x04000102*/
					V_ReturnData = DV_Date_Time_645( pV_645Frame );
					return(V_ReturnData);
				case C_DV_Date_Time:			/*���ⷽ��֮����ʱ���ж�*/
					V_ReturnData = DV_Date_Time( pV_645Frame );
					return(V_ReturnData);

				case C_DV_Demand_Cycle:			/*���ⷽ��֮��������*/
					V_ReturnData = DV_Demand_Cycle( pV_645Frame );
					return(V_ReturnData);

				case C_DV_Sliding_Time:			/*���ⷽ��֮��������*/
					V_ReturnData = DV_Sliding_Time( pV_645Frame );
					return(V_ReturnData);

				case C_DV_SwitchingTime:		/*���ⷽ��֮�л�ʱ��(������ʱ��)�ж�*/
					V_ReturnData = DV_SwitchingTime( pV_645Frame );
					return(V_ReturnData);

				case C_DV_Comm_Address:			/*���ⷽ��֮���ַ(BCD,����ȫ0x99)*/
					V_ReturnData = DV_Comm_Address( &pV_645Frame->Data[CData_14O_V_645] );
					return(V_ReturnData);

				case C_DV_Bps:					/*���ⷽ��֮�����ʵ�����*/
					V_ReturnData = DV_Bps( pV_645Frame );
					return(V_ReturnData);

				case C_DV_Settle_Day:			/*���ⷽ��֮��������Ч��*/
					V_ReturnData = DV_Settle_Day( pV_645Frame );
					return(V_ReturnData);

				case C_DV_Return_Money:			/*���ⷽ��֮�˷ѽ�������Ҫ�жϹ������ˣ��������ش���*/
					V_ReturnData = DV_Return_Money( pV_645Frame );
					return(V_ReturnData);

				case C_DV_Season:				/*���ⷽ��֮ʱ���жϷ���*/
					V_ReturnData = DV_Season( pV_645Frame );
					return(V_ReturnData);

				case C_DV_TimePeriod:			/*���ⷽ��֮ʱ���жϷ���*/
					V_ReturnData = DV_TimePeriod( pV_645Frame );
					return(V_ReturnData);

				case C_DV_HolidaySet:			/*���ⷽ��֮�������յ��жϷ���*/
					V_ReturnData = DV_HolidaySet( pV_645Frame );
					return(V_ReturnData);

				case C_DV_Ladder:				/*���ⷽ��֮���ݱ��жϷ���*/
					V_ReturnData = DV_Ladder( pV_645Frame );
					return(V_ReturnData);

				case C_DV_RstReport_State:		/*���ⷽ��֮��λ�����ϱ�״����*/
					V_ReturnData = DV_RstReport_State( pV_645Frame );
					return(V_ReturnData);		/*��λ�����ϱ�״̬�ֲ��������ݺϷ����ж�*/

				case C_DV_ReportChannel:		/*���ⷽ��֮�ϱ�ͨ��*/
					V_ReturnData = DV_ReportChannel( pV_645Frame );
					return(V_ReturnData);
				case C_DV_Position:				/*���ⷽ��֮���ܱ�λ����Ϣ*/
					V_ReturnData = DV_Position(pV_645Frame);
					return(V_ReturnData);
				default:
					return(C_OtherErr);			/*�����ܳ���*/
			}
		}break;

		default:								/*������*/
			return(C_OtherErr);
	}
}
/***************************************************************************
����ԭ�� 	DV_ReportChannel
��������	���ⷽ��֮�ϱ�ͨ��
�������	*pV_645Frame				:���յ�������֡
�������
���ز���	C_OK/C_OtherErr
ȫ�ֱ���
������ע	��������ͨ������Ϊ0�����֧��3����������ͨ��485��ģ��
***************************************************************************/
uchar8	DV_ReportChannel( Str_Comm_645 *pV_645Frame )
{
	uchar8  V_ucNum;
	uchar8  V_ucI, V_ucJ;
	ulong32 V_ulChannelOAD;

	V_ucNum = pV_645Frame->Data[CData_14O_V_645];				/*ͨ������*/
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
����ԭ�� 	DV_RstReport_State
��������	���ⷽ��֮��λ�����ϱ�״���ֺϷ��ԣ�������λ���Ը�λ��״̬��
�������	*pV_645Frame				:���յ�������֡
������� 	pV_645Frame->Data[CData_14O_V_645 0-12]	: �踴λ��λ��ע��Ϊ1�踴λ��
���ز���	C_OK/C_OtherErr
ȫ�ֱ���
������ע	1����λ�����е�λΪ0��Ҫ��λ�������ϱ����෴
				2��ֻҪ��λ�����ж�Ӧλ�����ϱ�״̬���д��ڣ�
				��Ӧ����ȷ������Ӧ��ʧ��
***************************************************************************/
uchar8		DV_RstReport_State(Str_Comm_645 *pV_645Frame)
{
	uchar8	i, j;
	uchar8  RSTData, HaveReportedData;

	if(SV_HaveReportState.Timer == 0)
	{/*Ҫ���յ���λ���������ٴ��յ���λ���Ӧ�����*/
		return(C_Unauthorized);
	}
/*�����жϣ���λ��λ����û���¼���������û���ϱ�����λ����������쳣Ӧ��*/
	for( j = 0; j < C_ReportStateByteNum; j++ )
	{
		RSTData = pV_645Frame->Data[CData_14O_V_645 + j];
		HaveReportedData = SV_HaveReportState.State[j];
		for( i = 0; i < 8; i++ )							/* 1�ֽ���8λ*/
		{
			if( ( ( RSTData & 0x01 ) == 0 )					/*��λ���·��ĸ�λ����*/
			 && ( ( HaveReportedData & 0x01 ) == 0 )		/*�Ѿ��ϱ����ı�־*/
			 && ( SV_ReportNewAddNum[j * 8 + i] != 0 ) )	/*��Ҫ�ϱ�������*/
			{/*��Ӧλ���ϱ�*/
				return(C_Unauthorized);
			}
			RSTData >>= 1;
			HaveReportedData >>= 1;
		}
	}
/*���յ���λ����ȡ�������ϱ�״̬λ���룬������0����ʾ��λ���Ը�λ��*/
/*ȫ������0����ʾû��λ���Ը�λ��*/
	for( i = 0; i < C_ReportStateByteNum; i++ )
	{
		pV_645Frame->Data[CData_14O_V_645 + i] =
			(~pV_645Frame->Data[CData_14O_V_645 + i]) & SV_HaveReportState.State[i];
	}
	return(C_OK);
}

/***************************************************************************
����ԭ�� 	DV_Position
��������	����λ�ò����Ϸ����ж�
�������	*pV_645Frame				:���յ�������֡
�������
���ز���	C_OK/C_OtherErr
ȫ�ֱ���
������ע	��


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
����ԭ�� 	DV_Date_Time
��������	���ⷽ��֮����ʱ���ж�,ͬʱ�ж��޸�ʱ��ǰ���Ƿ�������ͬ,��ͬ�򽫹㲥Уʱʱ������
�������	*pV_645Frame				:���յ�������֡
�������
���ز���	C_OK/C_OtherErr
ȫ�ֱ��� 	�㲥Уʱʱ�������ڲ�ͬʱ�ᱻ����
������ע
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
����ԭ�� 	DV_Date_Time
��������	���ⷽ��֮����ʱ���ж�,ͬʱ�ж��޸�ʱ��ǰ���Ƿ�������ͬ,��ͬ�򽫹㲥Уʱʱ������
�������	*pV_645Frame				:���յ�������֡
�������
���ز���	C_OK/C_OtherErr
ȫ�ֱ��� 	�㲥Уʱʱ�������ڲ�ͬʱ�ᱻ����
������ע	645Э�鴦�����ݸ�ʽ��Ҫ�ٺ˶� �����޸�ʱ���ʽֻ��֤���ݲ���� lzy 20211023
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
����ԭ�� 	DV_Demand_Cycle
��������	���ⷽ��֮��������
�������	*pV_645Frame				:���յ�������֡
�������
���ز���	C_OK/C_OtherErr
ȫ�ֱ���
������ע	�̶�Ϊ5��10��15��30��60
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
����ԭ�� 	DV_Sliding_Time
��������	���ⷽ��֮��������
�������	*pV_645Frame				:���յ�������֡
�������
���ز���	C_OK/C_OtherErr
ȫ�ֱ���
������ע	1��2��3��5
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
����ԭ�� 	DV_SwitchingTime
��������	���ⷽ��֮�л�ʱ��(������ʱ��)�ж�
�������	*pV_645Frame				:���յ�������֡
�������
���ز���	C_OK/C_OtherErr
ȫ�ֱ���
������ע
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
	 && ( pV_645Frame->Data[CData_14O_V_645+6] == 0xFF ) )		/*��ΪȫFF*/
	{
		V_ReturnData = C_OtherErr;
	}
	if(V_ReturnData != C_OK)
	{
		if( PF_Is_Buf_AllFixedData( &pV_645Frame->Data[CData_14O_V_645 + 1], 0x00, 5 ) == C_OK ) /*�л�ʱ�������0x00*/
		{
			return(C_OK);
		}
		if( PF_Is_Buf_AllFixedData( &pV_645Frame->Data[CData_14O_V_645 + 1], 0x63, 5 ) == C_OK )	/*�л�ʱ�������0x99*/
		{
			return(C_OK);
		}
		if( PF_Is_Buf_AllFixedData( &pV_645Frame->Data[CData_14O_V_645 + 1], 0xFF, 5 ) == C_OK ) /*�л�ʱ�������0xFF*/
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
����ԭ�� 	DV_Comm_Address
��������	���ⷽ��֮���ַ(BCD,����ȫ0x99)
�������	*pComm_Address				:���õ�ͨ�ŵ�ַ��ʼλ��
�������
���ز���	C_OK/C_OtherErr
ȫ�ֱ���
������ע
***************************************************************************/
uchar8 DV_Comm_Address( uchar8 *pComm_Address )
{
	uchar8 V_ReturnData;
	uchar8 i;

/*�ж��Ƿ�ΪBCD*/
	V_ReturnData = PF_Judge_BCD( CLComm_Address, pComm_Address );
	if( V_ReturnData != C_OK )
	{
		return(C_OtherErr);
	}
/*�ж��Ƿ�Ϊȫ99*/
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
����ԭ�� 	DV_Bps
��������	���ⷽ��֮�����ʵ�����
�������	*pV_645Frame				:���յ�������֡
�������
���ز���	C_OK/C_Baud_NotModified
ȫ�ֱ���
������ע	����������ֻҪ������Ҫ�����ʶ�Ӧ��C_Baud_NotModified
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
		SV_SetBPS_Flag = C_OK;				/*֪ͨ���ȣ�����BPS��*/
		return(C_OK);
	}
	else
	{
		return(C_Baud_NotModified);
	}
}

/***************************************************************************
����ԭ�� 	DV_Settle_Day
��������	���ⷽ��֮��������Ч��
�������	*pV_645Frame				:���յ�������֡
�������
���ز���	C_OK/C_OtherErr
ȫ�ֱ���
������ע	��1�����գ�1-28�գ�0-23����2��3���������ӿ���Ϊȫ0��ȫFF��ȫ99
***************************************************************************/
uchar8	DV_Settle_Day( Str_Comm_645 *pV_645Frame )
{
/*��2�����ջ��3�����գ�����ȫ0��ȫFF��ȫ99*/
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
/*Сʱ������С��24*/
	if( pV_645Frame->Data[CData_14O_V_645 + 1] > 23 )
	{
		return(C_OtherErr);
	}
/*�����С��29�Ҳ�Ϊ��*/
	if( ( pV_645Frame->Data[CData_14O_V_645] > 28 )
	 || ( pV_645Frame->Data[CData_14O_V_645] == 0 ) )
	{
		return(C_OtherErr);
	}
	return(C_OK);
}

/***************************************************************************
����ԭ�� 	DV_Return_Money
��������	�˷ѽ����Ч���ж�
�������	*pV_645Frame				:���յ�������֡
�������
���ز���	C_OK/C_OtherErr
ȫ�ֱ���
������ע	hex�����ұ���С��Ǯ�����
***************************************************************************/
uchar8	DV_Return_Money( Str_Comm_645 *pV_645Frame )
{
	uchar8	V_ReturnData;
	uchar8	ChargeBal_Hex_Cent[CLChargeBal_Hex_Cent];
    ushort16 V_usDataLen, V_usDataEncode[30] = {0x00};

/*������ģ��ӿں�����ʣ����	*/
	V_usDataLen = CLChargeBal_Hex_Cent;
	V_ReturnData = InF_GetData_ObjectManage(CChargeBal_Hex_Cent, ChargeBal_Hex_Cent, &V_usDataLen, V_usDataEncode);

	if(V_ReturnData != C_OK)
	{/*������*/
		return(C_OtherErr);
	}
/*Ǯ��ͬ��*/
	InF_S_UpdataChargeBalInESAM(ChargeBal_Hex_Cent);
/*ͬ�����ٶ����ݲ�ʣ�����Ϊͬ���У����ܻ���ESAMΪ׼���ۼ����ݲ�*/
	V_usDataLen = CLChargeBal_Hex_Cent;
	InF_GetData_ObjectManage(CChargeBal_Hex_Cent, ChargeBal_Hex_Cent, &V_usDataLen, V_usDataEncode);
/*�Ƚ�*/
	V_ReturnData = PF_Campare_Data(&pV_645Frame->Data[CData_14O_V_645], ChargeBal_Hex_Cent, CLChargeBal_Hex_Cent);
	if( ( V_ReturnData == C_GreaterThan )
	 || ( PF_Is_Buf_AllFixedData(ChargeBal_Hex_Cent, 0x00, CLChargeBal_Hex_Cent ) == C_OK ) )
	{/*C_GreaterThan��ʾ����1��������2*/
		return(C_OtherErr);
	}
	else
	{
		return(C_OK);
	}
}

/***************************************************************************
����ԭ�� 	DV_Season
��������	���ⷽ��֮ʱ���жϷ���
�������	*pV_645Frame				:���յ�������֡
�������
���ز���	C_OK/C_OtherErr
ȫ�ֱ���
������ע	hex��MM��1-12��DD��1-28��
				NN��1-8�����ݣ�
				���ñ�����ʱ�����ݳ��ȺϷ����������ݲ���
***************************************************************************/
uchar8	DV_Season( Str_Comm_645 *pV_645Frame )
{
	uchar8	i;
	uchar8	TZone_Num;
	uchar8	*pPreData;
	uchar8	*pCurData;

/*�ж�������Ч�ԣ��жϷ�����������ע*/
/*�����е�һ����Ч��*/
	if( Is_TZone_Data_OK( &pV_645Frame->Data[CData_14O_V_645] ) != C_OK )
	{
		return(C_OtherErr);
	}
	TZone_Num = CLFirst_TZone_Data / 3;
	pPreData = &pV_645Frame->Data[CData_14O_V_645 - 3];
	pCurData = &pV_645Frame->Data[CData_14O_V_645];
	for( i = 1; i < TZone_Num; i++ )
	{
		/*����ָ��*/
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
����ԭ�� 	Is_TZone_Data_OK
��������	�ж�3�ֽڵ�ʱ�������Ƿ�Ϸ�
�������	*pTZone_Data				:����3�ֽڵ�ʱ������
										:����˳�����Ϊ3�ֽڰ���NNDDMM����
�������
���ز���	C_OK/C_OtherErr
ȫ�ֱ���
������ע	MM��1-12��DD��1-28��NN��1-8��
***************************************************************************/
uchar8	Is_TZone_Data_OK( uchar8	*pTZone_Data )
{
	uchar8	V_ucData[3];

	PF_OneDataReversed(pTZone_Data, V_ucData,3);							/*����˳�����*/

	if( ( V_ucData[0] < 0x01 )||( V_ucData[0] > 0x08 ) )					/*NN��1-8*/
	{
		return(C_OtherErr);
	}

	if( PF_DataTimeActive_698( &V_ucData[1], C_DT_Start_DD, 2 ) != C_OK )	/*DDMM�Ϸ����ж�*/
	{
			return(C_OtherErr);
	}
	return(C_OK);
}

/***************************************************************************
����ԭ�� 	DV_TimePeriod
��������	���ⷽ��֮ʱ���жϷ���
�������	*pV_645Frame				:���յ�������֡
�������
���ز���	C_OK/C_OtherErr/C_RateNum_OV
ȫ�ֱ���
������ע	hex��hh��00-23��mm��0-59��
				NN��1-4�����ݣ�hhmmӦ�ú�һ�����ڵ���ǰһ����
				����ʱ��һ�����ڵ���15min .ע����������00 00 00��N����
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
	uchar8	V_ucData[CLFirst_TZone_1PT_Data + 3 + 3];			/*��һ��+3��Ϊ������ַ��3������2��+3��Ϊ�˱����15��ʱ��*/

	TimePeriod_Num = CLFirst_TZone_1PT_Data / 3;
	for( i = 0; i < TimePeriod_Num; i++ )
	{
		PF_OneDataReversed(&pV_645Frame->Data[CData_14O_V_645 + i * 3], V_ucData +3 + i * 3, 3);	/*����˳�����*/
	}

/*��1��ʱ�α�+24Сʱ�����ڼ������һ��ʱ�κ͵�һ��ʱ��ʱ��ļ��*/
	V_ucData[CLFirst_TZone_1PT_Data + 3] = V_ucData[3];
	V_ucData[CLFirst_TZone_1PT_Data + 3 + 1] = V_ucData[4];
	V_ucData[CLFirst_TZone_1PT_Data + 3 + 2] = V_ucData[5] + 24;

/*�ж�������Ч�ԣ��жϷ�����������ע*/
/*�����е�һ����Ч��*/
	V_ReturnData = Is_TimePeriod_Data_OK( V_ucData + 3 );
	if( V_ReturnData != C_OK )
	{
		return(V_ReturnData);
	}

	pPreData = V_ucData;
	pCurData = V_ucData + 3;				/*��һ��ʱ�α��׵�ַ*/

	/*ȡ��һ��ʱ�α��hhmm��Ϊ��һ�����ӡ����ڼ���15min*/
	HexTemp = pCurData[2];					/*��1��Сʱ*/
	PreMin = (ushort16)(HexTemp * 60 );
	HexTemp = pCurData[1];					/*��1������*/
	PreMin = PreMin + (ushort16)HexTemp;

	for( i = 1; i< (TimePeriod_Num + 1); i++)
	{
		/*����ָ��*/
		pPreData = pPreData + 3;
		pCurData = pCurData + 3;
		if( ZeroFlag )
		{
			/*�����Ѿ���0�ˣ���������ȫ����0.(��Ϊѭ���ӵ�2��ʱ����ʼ)*/
			if( ( pCurData[0] != 0 ) || ( pCurData[1] != 0 ) || ( pCurData[2] != 0 ) )
			{
				return(C_OtherErr);
			}
			continue;
		}
		else
		{
			/*��һ�������ǰһ�����ڵ��ڡ����С�ڱ���ȫ0����0��־*/
			V_ReturnData = PF_Campare_Data( &pPreData[1], &pCurData[1], 2 );		/*��2�ֽ�hhmm��С*/
			if( V_ReturnData == C_Equal )
			{
				if( ( pCurData[1] == 0 ) && ( pCurData[2] == 0 ) )
				{
					if( pCurData[0] == 0 )
					{
						ZeroFlag = 1;
						continue;			/*ֻ�е�һ����ʱ�β�����Ч���ҵ�һ����ʱ��ʱ��Ϊ00:00*/
					}
				}
				/*hhmm��ȣ���NNҲ�������*/
				if( pPreData[0] != pCurData[0] )
				{
					return(C_OtherErr);
				}
				continue;					/*û��Ҫ�����֮�󣬺������ȫ������*/
			}
			else if( V_ReturnData == C_GreaterThan )
			{
				/*ǰһ���Ⱥ�һ����ֻ�к�һ����ȫ0 �Ŀ��ܡ�*/
				if( ( pCurData[0] != 0 ) || ( pCurData[1] != 0 ) || ( pCurData[2] != 0 ) )
				{
					return(C_OtherErr);
				}
				ZeroFlag = 1;
				continue;
			}
			else if( V_ReturnData == C_LessThan )
			{
				/*ǰһ���Ⱥ�һ��С��ȥ�жϺ�һ�����ݺϷ���*/
				if( TimePeriod_Num == i )/*��15��ʱ���ɵ�1��ʱ�μ�24Сʱ�������ã����жϺϷ��ԣ�*/
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
					/*�Ϸ���ȥ�жϺ�һ����ǰһ������15min*/
					HexTemp = pCurData[2];					/*��ǰСʱ*/
					CurMin = (ushort16)( HexTemp * 60 );
					HexTemp = pCurData[1];					/*��ǰ����*/
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
				/*�����ܵ�����*/
				return(C_OtherErr);
			}
		}
	}
    return(C_OK);
}

/***************************************************************************
����ԭ�� 	Is_TimePeriod_Data_OK
��������	����ʱ�α������Ƿ���ȷ
�������	*pTimePeriod_Data				:����3�ֽڵ�ʱ������
											:3�ֽڰ���NN mm hh����
�������
���ز���	C_OK/C_OtherErr/C_RateNum_OV
ȫ�ֱ���
������ע	hh��00-23��mm��0-59��NN��1-12�����й�BCD�ˡ�
***************************************************************************/
uchar8		Is_TimePeriod_Data_OK(uchar8	*pTimePeriod_Data)
{
/*NN��1-4*/
	if( ( *pTimePeriod_Data < 0x01 )
	 || ( *pTimePeriod_Data > C_MaxRatesNum ) )
	{
		return(C_RateNum_OV);
	}

/*mm��0-59*/
	if( *( pTimePeriod_Data + 1 ) > 59)
	{
		return(C_OtherErr);
	}

/*hh��0-23*/
	if( *( pTimePeriod_Data + 2 ) > 23 )
	{
		return(C_OtherErr);
	}
	return(C_OK);
}

/***************************************************************************
����ԭ�� 	DV_HolidaySet
��������	���ⷽ��֮�������յ��жϷ���
�������	*pV_645Frame				:���յ�������֡
�������
���ز���	C_OK/C_OtherErr
ȫ�ֱ���
������ע	���ж����������0ʱ��ʱ�α��ҲΪ0����������Ҫ��
            �����ܣ�������Ϊ0����ҲΪ0��ʱ�α��ҲΪ0 20190411
***************************************************************************/
uchar8	DV_HolidaySet( Str_Comm_645 *pV_645Frame )
{
	uchar8 V_i;
	uchar8 V_ucLen;

	if( ( PF_Is_Buf_AllFixedData(&pV_645Frame->Data[CData_14O_V_645], 0x00,  6) == C_OK )		/*��������ȫ0*/
	|| ( PF_Is_Buf_AllFixedData(&pV_645Frame->Data[CData_14O_V_645], 0xFF,  6) == C_OK ) )		/*��������ȫF*/
	{
		return(C_OK);
	}
	for( V_i = 0; V_i < 5; V_i++ )		/*���ڸ��ֽ�*/
	{
		if( pV_645Frame->Data[CData_14O_V_645 + 5 - 1 - V_i] != 0xFF )
		{
			break;
		}
	}
	if( V_i == 0 )						/*����ȫ����Ч*/
	{
		V_ucLen = 4;
		if( PF_Cal_Week_698(&pV_645Frame->Data[CData_14O_V_645 + 1]) != pV_645Frame->Data[CData_14O_V_645] )	/*�ж��ܺϷ���*/
		{
			return(C_OtherErr);
		}
	}
	else if( V_i == 2 )					/*����Ч*/
	{
		V_ucLen = 2;
	}
	else if( V_i == 3 )					/*�ꡢ����Ч*/
	{
		V_ucLen = 1;
	}
	else
	{
		return(C_OtherErr);
	}
	if( pV_645Frame->Data[CData_14O_V_645] > 6 )		/*�ܲ��ܴ���6*/
	{
		return(C_OtherErr);
	}
	if( ( pV_645Frame->Data[CData_14O_V_645 + 5] > 8 )
	||( pV_645Frame->Data[CData_14O_V_645 + 5] < 1 ) )/*ʱ�α��*/
	{
		return(C_OtherErr);
	}
	if( PF_DataTimeActive_698( &pV_645Frame->Data[CData_14O_V_645 + 1], C_DT_Start_DD, V_ucLen ) != C_OK )		/*���ںϷ����ж�*/
	{
		return(C_OtherErr);
	}
	return(C_OK);
}

/**************************************************************************
����ԭ�� 	DV_Ladder
��������	���ⷽ��֮���ݱ��жϷ���
�������	*pV_645Frame				:���յ�������֡
�������
���ز���	C_OK/C_OtherErr
ȫ�ֱ���
������ע
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
����ԭ�� 	InF_DV_Ladder
��������	���ⷽ��֮���ݱ��жϷ���
�������	*pLadderData				:���ݱ�����
������� 							:���ݸ�ʽ�̶�Ϊ4*6����ֵ
										4*7���ݵ�ۣ�3*4����ݽ�����
���ز���	C_OK/C_OtherErr
ȫ�ֱ���
������ע	�������ݾ�Ҫ��ΪBCD�롣����ֵҪ���һ����ǰһ�������ڡ�
				���ݵ���໥��û�й�ϵ
				������գ�MM��1-12��DD��1-28��hh��0-23���Һ�һ����ǰһ���󡣻���Ϊ999999
				�����ж�һ�����ڣ�����ȫ�ȡ�һ��Ϊ999999������ȫ��Ϊ999999
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

/*�жϽ���ֵ���ݵĺ����ԡ�*/
	pPreData = pLadderData - 4;										/*һ��ѭ�������ȵ���ָ�롣*/
	pCurData = pLadderData;
	EqualFlag = 0;
	if( PF_Is_Buf_AllFixedData(pCurData, 0x00, 4) == C_OK )			/*ȫ0*/
	{
		All00Flag = 0x68;
	}
	for( i = 1; i < 6; i++ )										/*�ӵ�2������ֵ��ʼ��Ҫ�����һ��������ڵ���ǰһ��*/
	{
		pPreData = pPreData + 4;
		pCurData = pCurData + 4;
		V_ReturnData = PF_Campare_Data( pPreData, pCurData, 4 );	/*�Ƚ�ǰ��ֵ*/
		if( EqualFlag == DataEqual )
		{	/*ǰ��������ˣ���ô�������ȫ��*/
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
		{	/*ǰ��������ˣ���ô�������ȫ��*/
			if( V_ReturnData != C_Equal )
			{
				return(C_OtherErr);
			}
			continue;
		}
		else
		{
			if( V_ReturnData == C_Equal )
			{	/*ֵ���*/
				EqualFlag = DataEqual;
				continue;
			}
			else if( V_ReturnData == C_GreaterThan )
			{	/*ǰһ���Ⱥ�һ����*/
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
/*���ݵ�۽���BCD�жϣ����������ж��ˡ�*/

/*�������*/
	pPreData = &pLadderData[YSettle_O - 3];					/*һ��ѭ�������ȵ���ָ�롣*/
	pCurData = &pLadderData[YSettle_O];
	EqualFlag = 0;

	/*�жϵ�1���������*/
	V_ReturnData = Is_YSettle_OK(pCurData);
	if( V_ReturnData == C_YSettle_All99 )
	{
		EqualFlag = 1;										/*��1��Ϊȫ99������Ϊ������������ˣ�Ҫ��������ݱ������ǰһ�����ݡ�*/
	}														/*��Ҫ���������ҲΪȫ99�ˡ�*/
	else if( V_ReturnData != C_OK )
	{
		return(V_ReturnData);
	}

	for( i = 1; i < 4; i++ )								/*4���������*/
	{
		pPreData = pPreData + 3;
		pCurData = pCurData + 3;

		V_ReturnData = Is_YSettle_OK(pCurData);
		if( ( V_ReturnData != C_OK ) && ( V_ReturnData != C_YSettle_All99 ) )
		{/*���������쳣*/
			return(V_ReturnData);
		}
		if( V_ReturnData == C_YSettle_All99 )
		{
			EqualFlag++;									/*��1��Ϊȫ99������Ϊ������������ˣ�Ҫ��������ݱ������ǰһ�����ݡ�*/
		}													/*��Ҫ���������ҲΪȫ99�ˡ�*/
	}
	if( ( EqualFlag == 4 ) && ( All00Flag != 0x68 ) )		/*4�������վ���Ч�����ǽ��ݱ�������Ч��Ӧ����������*/
	{
		return(C_OtherErr);
	}
	return(C_OK);
}

/***************************************************************************
����ԭ�� 	Is_YSettle_OK
��������	�ж�������������Ƿ���ȷ
�������	*pYSettle				:����3�ֽ���������׵�ַ

�������
���ز���	C_OK 				:��������
				C_YSettle_All99		:������ȷ����Ϊȫ99
				C_OtherErr			:���ݴ���
ȫ�ֱ��� 	��
������ע	MM��1-12��DD��1-28��hh��0-23
				�������BCD���ڳ��������жϡ�
***************************************************************************/
uchar8	Is_YSettle_OK( uchar8 *pYSettle )
{
/*�ж��Ƿ�Ϊȫ99*/
	if( ( PF_Is_Buf_AllFixedData(pYSettle, 0x00,  3) == C_OK )		/*��������ȫ0*/
	 || ( PF_Is_Buf_AllFixedData(pYSettle, 0x63,  3) == C_OK )		/*��������ȫ9*/
	 || ( PF_Is_Buf_AllFixedData(pYSettle, 0xFF,  3) == C_OK ) )	/*��������ȫF*/
	{
		return(C_YSettle_All99);
	}
/*hh 0-23*/
	if(pYSettle[2] > 23)
    {
        return(C_OtherErr);
    }
/*DD 1-28*/

    if ( ( pYSettle[0] != 0x63 ) && ( pYSettle[0] != 0xFF ) )   /*��� ������Ч��0x99��0xFF��*/
    {
        if( ( pYSettle[1] < 1 ) || ( pYSettle[1] > 28 ) ) 		/*�պϷ����ж� 1-28 */
        {
            return(C_OtherErr);
        }
    }
    else   /*����Ч���տ�����1-28����0x99��0xFF*/
    {
        if ( ( ( pYSettle[1] < 1 ) || ( pYSettle[1] > 28 ) )   && ( pYSettle[1] != 0x63 ) && ( pYSettle[1] != 0xFF ) )    /*�ѿ����̻��999902���*/
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
����ԭ�� 	DV_HexRange
��������	����ΪBCD���ҷ�Χ��BCDMin<=   ����<= BCDMax֮��
�������	*pV_645Frame				:���յ�������֡
				HexMin/HexMax			:��Сֵ/���ֵ
�������
���ز���	C_OK/C_OtherErr
ȫ�ֱ��� 	��
������ע	*pV_645Frame	����Ч���ݳ���Ϊ1
***************************************************************************/
uchar8		DV_HexRange(Str_Comm_645 *pV_645Frame,uchar8	HexMin,uchar8 HexMax)
{

	if( ( pV_645Frame->Data[CData_14O_V_645] < HexMin )
	 || ( pV_645Frame->Data[CData_14O_V_645] > HexMax ) )
	{
		if( pV_645Frame->DI == CYear_Zone_Num )			/*��ʱ����*/
		{
			return(C_SeasonNum_OV);
		}
		else if( pV_645Frame->DI == CDay_Time_Num )		/*��ʱ����*/
		{
			return(C_PeriodNum_OV);
		}
		else if( pV_645Frame->DI == CRate_Num )			/*������*/
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
����ԭ�� Is_14_DataLenOk
��������	 �ж�14����ȵĺϷ��ԣ�������������������ݲ��޸Ľ���֡����
�������	 *pV_645Frame				:���յ�������֡
		 *pWrParmTable				:�������ñ������������
������� pV_645Frame->DataLen/Data[]	:��������ʱ�޸�
���ز���	 C_OK/C_OtherErr/C_Unauthorized
ȫ�ֱ��� ��
������ע	 ����14�����޸����룬���ﻹ�ж�Ȩ�޺����ԡ�
*******************************************************************************/
uchar8	Is_14_DataLenOk( Str_Comm_645 *pV_645Frame, Str_WrParmTable *pWrParmTable )
{
	uchar8	ValidLen;
	uchar8	V_ReturnData;
	ulong32	UnsizedLen_Method;
	uchar8	V_ucFixedLen;
	uchar8	V_ucI;
    uchar8  V_ucTemp[100];

/*���ȱ����Ǻ���*/
	if( pV_645Frame->DataLen > ( CLen_DI + CLen_OpCode + CLen_CommPW ) )
	{
		ValidLen = pV_645Frame->DataLen - ( CLen_DI + CLen_OpCode + CLen_CommPW );
	}
	else
	{
		return(C_OtherErr);
	}

/*ȡ�����жϷ���	*/
	if( ( pWrParmTable->Method & C_DataLenFixedFlag ) == C_DataLenFixed_OK )
	{
		/*����*/
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
	{/*������*/
		if( ( pWrParmTable->Method & C_IsAddFixedDataLen ) == C_AddFixedDataLen )	/*��������λͳһ��0*/
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
		{/*��������������Ҫ������*/
			UnsizedLen_Method = pWrParmTable->Method & C_UnsizedLen_Method;
			switch(UnsizedLen_Method)
			{
				case C_UnsizedLen_PW:					/*���룬��Ҫ�жϳ��ȼ���������Ȩ�޺����ԣ���ȥ������PA��Ŀǰ������δ��������������645Э��ʱ��ע��˶� lzy 20211012*/
					V_ReturnData = IsPW_Len_Auth(pV_645Frame);
					return(V_ReturnData);
				case C_UnsizedLen_S_PT:					/*ʱ�Ρ�ʱ������жϣ�����14*3������*/
					V_ReturnData = Adjust_UnsizedLen_S_PT(pV_645Frame);
					return(V_ReturnData);
				case C_UnsizedLen_Date:					/*�������ã��жϳ����Ƿ���ȷ�����������Ϊ040001FD��ʽ. ��������645Э��ʱ��ע��˶� lzy 20211012*/
					V_ReturnData = Adjust_DateLen(pV_645Frame);
					return(V_ReturnData);
				case C_UnsizedLen_Time:					/*ʱ�����ã��жϳ����Ƿ���ȷ�����������Ϊ040001FD��ʽ. ��������645Э��ʱ��ע��˶� lzy 20211012*/
					V_ReturnData = Adjust_TimeLen(pV_645Frame);
					return(V_ReturnData);
				case C_UnsizedLen_BackUpLadder:			/*�����׽��ݱ�������ã����ȴ���63�ֽڣ���Ҫ���⴦��*/
					V_ReturnData = Adjust_BackUpLadderLen(pV_645Frame);
					return(V_ReturnData);
				case C_UnsizedLen_BackUpRateFFPrice:	/*���ñ����׷��ʵ�۲���*/
					V_ReturnData = Adjust_BackUpRateFFPriceLen(pV_645Frame);
					return(V_ReturnData);
				case C_UnsizedLen_ReportChannel:		/*�ϱ�ͨ�����Ȳ���13�ֽڣ�����*/
					V_ReturnData = Adjust_ReportChannel(pV_645Frame);
					return(V_ReturnData);
				default:								/*����ֵ�ǲ����ܵġ�*/
					return(C_OtherErr);
			}
		}
	}
	return(C_OK);
}

/***************************************************************************
����ԭ�� 	Adjust_DateLen
��������	�жϳ����Ƿ���ȷ�����������Ϊ0400010C��ʽ
�������	*pV_645Frame			:���յ�645֡
������� 	pV_645Frame->DataLen/Data[]	:��������ʱ�޸�
���ز���	C_OK/C_OtherErr/
ȫ�ֱ���
������ע
***************************************************************************/
uchar8		Adjust_DateLen(Str_Comm_645 *pV_645Frame)
{
	uchar8		Date_Time[CLDate_Time];		/*�����ǵ�����Date_Time�������۵�����CDate_Week_Time��ʽ�������������޸�*/
	ushort16	DataLen, V_usDataEncode;

/*�жϳ���*/
	if(pV_645Frame->DataLen != (CLDate_Week + CLen_DI + CLen_OpCode + CLen_CommPW))
	{
		return(C_OtherErr);
	}
/*���ݵ���,����,��ʶ��(�������ݲ��д)*/
	DataLen = CLDate_Time;
	InF_Read_Data(CDate_Time, Date_Time, &DataLen, &V_usDataEncode);

	PF_CopyDataBytes(&pV_645Frame->Data[CData_14O_V_645], &Date_Time[CDate_WW_Time_WW_O], CLDate_Week);

	if(PF_DataTimeActive(&Date_Time[C_ss_O], C_DT_Start_ss, CLTime) != C_OK)	/*ʱ��Ƿ���Ĭ��00:00:00*/
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
����ԭ�� 	Adjust_TimeLen
��������	�жϳ����Ƿ���ȷ�����������Ϊ0400010C��ʽ
�������	*pV_645Frame			:���յ�645֡
������� 	pV_645Frame->DataLen/Data[]	:��������ʱ�޸�
���ز���	C_OK/C_OtherErr/
ȫ�ֱ���
������ע
***************************************************************************/
uchar8		Adjust_TimeLen(Str_Comm_645 *pV_645Frame)
{
	uchar8		Date_Time[CLDate_Time];		/*�����ǵ�����Date_Time�������۵�����CDate_Week_Time��ʽ�������������޸�*/
	ushort16	DataLen, V_usDataEncode;

/*�жϳ���*/
	if(pV_645Frame->DataLen != (CLTime + CLen_DI + CLen_OpCode + CLen_CommPW))
		{
			return(C_OtherErr);
		}
/*���ݵ���,����,��ʶ��(�������ݲ��д)*/
	DataLen = CLDate_Time;
	InF_Read_Data(CDate_Time, Date_Time, &DataLen, &V_usDataEncode);  /*698�ж�����ΪssmmHHDDMMYY*/

	PF_CopyDataBytes(&Date_Time[CDate_WW_Time_WW_O], &pV_645Frame->Data[CData_14O_V_645 + CLTime], CLDate_Week - 1);

	if(PF_DataTimeActive(&Date_Time[CDate_WW_Time_WW_O], C_DT_Start_DD, CLDate_Week - 1) != C_OK)	/*���ڷǷ���Ĭ��00-01-01*/
    {
      	pV_645Frame->Data[CData_14O_V_645 + CDate_WW_Time_WW_O] = 0x01;
		pV_645Frame->Data[CData_14O_V_645 + CDate_WW_Time_DD_O] = 0x01;
		pV_645Frame->Data[CData_14O_V_645 + CDate_WW_Time_MM_O] = 0x00;
	}
    pV_645Frame->Data[CData_14O_V_645 + CDate_WW_Time_YY_O] = 0x20;   /*��Ϊ20��*/
	pV_645Frame->DataLen = CLDate_Time + CLen_DI + CLen_OpCode + CLen_CommPW;

	pV_645Frame->DI = CDate_Time;
	return(C_OK);
}

/***************************************************************************
����ԭ�� 	Adjust_UnsizedLen_S_PT
��������	�ж�ʱ�Ρ�ʱ�������ݳ����Ƿ���ȷ���ҳ���ͳһ������3*14
�������	*pV_645Frame			:���յ�645֡
������� 	pV_645Frame->DataLen/Data[]	:��������ʱ�޸�
���ز���	C_OK/C_OtherErr/C_PeriodNum_OV��C_SeasonNum_OV
ȫ�ֱ���
������ע
***************************************************************************/
uchar8	Adjust_UnsizedLen_S_PT(Str_Comm_645 *pV_645Frame)
{
	uchar8	ValidLen;
	uchar8	V_uci;
	uchar8	SourceLen;
	uchar8 V_TZone_Temp[CLSec_TZone_Data];
	ushort16 V_TZone_LenTemp, V_usDataEncode;

/*ȡ��Ч���ȣ�Ӧ�ϼ����������ж�645�����򳤶ȿ϶�����12������Ͳ��ж���*/
	ValidLen = pV_645Frame->DataLen - ( CLen_DI + CLen_OpCode + CLen_CommPW );
/*���ȱ�����ڵ���3��С�ڵ���42*/
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
/*���ȱ����ܱ�3����*/
	if( ( ValidLen % 3 ) != 0 )
	{
		return(C_OtherErr);
	}
/*����3*14������*/
	if( ( pV_645Frame->DI != CSec_TZone_Data ) && ( ( pV_645Frame->DI & 0xFFFFFF00 ) == CSec_TZone_Data ) )
	{/*������0���ò����ݣ�Ŀǰδʹ�� ��ʱ�ȱ��� lzy 20211012*/
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
����ԭ�� 	Adjust_BackUpLadderLen
��������	�жϱ����׽��ݱ�������ݳ����Ƿ���ȷ�����������ݳ��ȹ̶�64�ֽ�
�������	*pV_645Frame			:���յ�645֡
������� 	pV_645Frame->DataLenΪ���ݳ��ȣ��̶�64�ֽ�
���ز���	C_OK/C_OtherErr
ȫ�ֱ���
������ע
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
����ԭ�� 	Adjust_ReportChannel
��������	�ϱ�ͨ�������жϣ�С��13�ֽ�ʱ��λ��0
�������	*pV_645Frame			:���յ�645֡
������� 	pV_645Frame->DataLenΪ���ݳ��ȣ��̶�13�ֽ�
���ز���	C_OK/C_OtherErr
ȫ�ֱ���
������ע
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
����ԭ�� 	Adjust_BackUpRateFFPriceLen
��������	�жϱ����׷��ʱ�������ݳ����Ƿ���ȷ������ҪС��32*4���ܱ�4����
�������	*pV_645Frame			:���յ�645֡
������� 	pV_645Frame->DataLenΪ���ݳ��ȣ�����Ӧ��С��32*4+4�ֽ�MAC�ĳ���
���ز���	C_OK/C_OtherErr
ȫ�ֱ���
������ע	���ݱ���64�ֽڣ�������ͨ���жϷ�������󳤶�63�ֽڣ���������ж�
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
����ԭ�� 	IsLoad_Rec_Time_LenOK
��������	�ж����볤�ȡ�Ȩ�޺����Լ�ȥ��PA
�������	*pV_645Frame			:���յ�645֡
������� 	pV_645Frame->DataLen/Data[]	:��������ʱ�޸�
���ز���	C_OK/C_OtherErr/C_Unauthorized
ȫ�ֱ���
������ע	2014�淶Ҫ�����98��������Կ�޸�!
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
����ԭ�� 	LookFor_WrParmTable
��������	�����������ñ��WrParmTable��ʵ��Ҳ���ж�DI�ڲ������÷�Χ
�������	*pV_645Frame			:���յ�������֡
				pWrParmTable			:�������ñ�������ݵĵ�ַ
������� 	*pWrParmTable		:�������ñ������������
���ز���	C_OK/C_OtherErr
ȫ�ֱ��� 	��
������ע	��
***************************************************************************/
#define C_Event07ReportMode		0x08									/*07���¼��ϱ�����11����*/
#define C_Event24ReportMode		0x0B									/*24���¼��ϱ�����15����*/
#define C_First_TZone_PT_Data	(CFirst_TZone_1PT_Data & 0xFFFFFF00)	/*��ǰ��ʱ�α�*/
#define C_Sec_TZone_PT_Data		(CSec_TZone_1PT_Data & 0xFFFFFF00)		/*������ʱ�α�*/

uchar8	LookFor_WrParmTable( Str_Comm_645 *pV_645Frame, Str_WrParmTable *pWrParmTable )
{
	uchar8	i;
	uchar8 DI_Temp[4];

/*����ȷ��DI�Ƿ�Ϊ����*/
	PF_Ulong32ToBuffer4(DI_Temp, &(pV_645Frame->DI), 4);        /*��ȡOIA,OIB*/
	if( ( ( pV_645Frame->DI & 0xFFFFFF00 ) == 0xF3000200 )
	 || ( (pV_645Frame->DI & 0xFFFFFF00 ) == 0xF3010200 ) )
	{/*ѭ���������*/
	 /*�����Զ����Ի򰴼���ʾ*/
		if( (pV_645Frame->DI & 0x000000FF) < 0x64 )
		{
			pWrParmTable->ParmDI = pV_645Frame->DI ;
			pWrParmTable->Method = C_UnAddFixedDataLen | C_DataLenFixed_OK | CLAuto_Dis_1ScreenCode | C_DataValid_NoLimit/*��ʾ���������������ƣ�2017/12/29 10:47:36*/
				 					| C_HaveIPEvent_Invalid | C_ExtMsgType_Invalid;
			return(C_OK);
		}
		else
		{
			return(C_Error);
		}
	}
	else if( (pV_645Frame->DI & 0xFFFFFF00) == 0x40110200 )
	{/*���ù�������*/
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
			   && ( C_Event24ReportType == DI_Temp[1] ) )			/*24����¼���OIB,2020��׼�޸��˹������������¼�302B ����15*/
			 ||( ( ( DI_Temp[2] == 0x09 )||( DI_Temp[2] == 0x0A )||( DI_Temp[2] >= 0x0C ) )&&( DI_Temp[2] != 0x3B )
			   && ( C_Event07ReportType == DI_Temp[1] ) ) ) )		/*7����¼���OIB ����11*/
	{
		pWrParmTable->Method = C_UnAddFixedDataLen | C_DataLenFixed_OK | CLReport_Type | C_DataValidHex_Range | C_DV_HexRange_0_1
								| C_HaveIPEvent_Invalid | C_ExtMsgType_Invalid;
		return(C_OK);
	}
	else if( ( C_EventOIA == DI_Temp[3] )
		   && ( ( ( ( DI_Temp[2] <= 0x08 ) || ( DI_Temp[2] == 0x0B ) || ( DI_Temp[2] == 0x3B ) )
			   && ( C_Event24ReportMode == DI_Temp[1] ) )			/*24����¼���OIB,2020��׼�޸��˹������������¼�302B ����11*/
			  ||( ( ( DI_Temp[2] == 0x09 ) || ( DI_Temp[2] == 0x0A ) || ( DI_Temp[2] >= 0x0C ) ) && ( DI_Temp[2] != 0x3B )
			   && ( C_Event07ReportMode == DI_Temp[1] ) ) ) )		/*7����¼���OIB ����8*/
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
����ԭ�� 	Is_ParmType_3
��������	�ж��Ƿ�Ϊ3���������(�������GPRS�źţ��������ģ��ͨ����������Ϊ����III�������)
�������	DI				:���յ��Ĵ����õ�DI
				pWrParmTable		:������������ݵ�ַ
				V_ucCommNum			:ͨ����,��Ҫ����GPRS�ź�ǿ������ֻ����ģ��ͨ�����ж�����
������� 	*pWrParmTable	:��������е�����
���ز���	C_OK/C_Error
ȫ�ֱ��� 	��
������ע
***************************************************************************/
uchar8 Is_ParmType_3(ulong32 DI, Str_WrParmTable *pWrParmTable, uchar8 V_ucCommNum)
{
	/*��λģ��״̬�֡�GPRS�ź�����*/
	switch(DI)
	{
		case		CGPS_Signal:				/*����GPRS�ź�*/
		{
			pWrParmTable->ParmDI = DI;
			pWrParmTable->Method = C_UnAddFixedDataLen | C_DataLenFixed_OK | CLGPS_Signal | C_DataValid_NoLimit
									| C_HaveIPEvent_GPRSSignal | C_ExtMsgType_Invalid;
			if(V_ucCommNum != C_Module)			/*ͨ���Ų���ģ��ͨ��*/
			{
				return(C_Error);
			}
		}return(C_OK);
		case		CRst_Report_State_645:		/*��λ�����ϱ�״̬��*/
		{
			pWrParmTable->ParmDI = DI;
			pWrParmTable->Method = C_UnAddFixedDataLen | C_DataLenFixed_OK | CLRst_Report_State_645 | C_DataValidSpecialMethod | C_DV_RstReport_State
									| C_HaveIPEvent_RstReportState | C_ExtMsgType_Invalid;
		}return(C_OK);
		case		CF1_TerUpCommParam:			/*�����Լ�ģ��GPRSģ������IP�Ȳ���*/
			pWrParmTable->ParmDI = DI;
			pWrParmTable->Method = C_UnAddFixedDataLen | C_DataLenFixed_OK | CLF1_TerUpCommParam | C_DataValid_NoLimit
									| C_HaveIPEvent_Invalid | C_ExtMsgType_Invalid;
			return(C_OK);
		case		CF3_MainStaCommParam:		/*�����Լ�ģ��GPRSģ������IP�Ȳ���*/
			pWrParmTable->ParmDI = DI;
			pWrParmTable->Method = C_UnAddFixedDataLen | C_DataLenFixed_OK | CLF3_MainStaCommParam | C_DataValid_NoLimit
									| C_HaveIPEvent_Invalid | C_ExtMsgType_Invalid;
			return(C_OK);
		case		CF4_SMSCommParam:			/*�����Լ�ģ��GPRSģ������IP�Ȳ���*/
			pWrParmTable->ParmDI = DI;
			pWrParmTable->Method = C_UnAddFixedDataLen | C_DataLenFixed_OK | CLF4_SMSCommParam | C_DataValid_NoLimit
									| C_HaveIPEvent_Invalid | C_ExtMsgType_Invalid;
			return(C_OK);
		case		CF7_TerminalIPAddr:			/*�����Լ�ģ��GPRSģ������IP�Ȳ���*/
			pWrParmTable->ParmDI = DI;
			pWrParmTable->Method = C_UnAddFixedDataLen | C_DataLenFixed_OK | CLF7_TerminalIPAddr | C_DataValid_NoLimit
									| C_HaveIPEvent_Invalid | C_ExtMsgType_Invalid;
			return(C_OK);
		case		CF8_ConnectParam:			/*�����Լ�ģ��GPRSģ������IP�Ȳ���*/
			pWrParmTable->ParmDI = DI;
			pWrParmTable->Method = C_UnAddFixedDataLen | C_DataLenFixed_OK | CLF8_ConnectParam | C_DataValid_NoLimit
									| C_HaveIPEvent_Invalid | C_ExtMsgType_Invalid;
			return(C_OK);
		case		CF16_MoveAPNPassWord:		/*�����Լ�ģ��GPRSģ������IP�Ȳ���*/
			pWrParmTable->ParmDI = DI;
			pWrParmTable->Method = C_UnAddFixedDataLen | C_DataLenFixed_OK | CLF16_MoveAPNPassWord | C_DataValid_NoLimit
									| C_HaveIPEvent_Invalid | C_ExtMsgType_Invalid;
			return(C_OK);
		case		CF89_TerminalAddr:			/*�����Լ�ģ��GPRSģ������IP�Ȳ���*/
			pWrParmTable->ParmDI = DI;
			pWrParmTable->Method = C_UnAddFixedDataLen | C_DataLenFixed_OK | CLF89_TerminalAddr | C_DataValid_NoLimit
									| C_HaveIPEvent_Invalid | C_ExtMsgType_Invalid;
			return(C_OK);
		case		CFactoryInMeterNum:			/*�������ڱ��*/
			pWrParmTable->ParmDI = DI;
			pWrParmTable->Method = C_UnAddFixedDataLen | C_DataLenFixed_OK | CLFactoryInMeterNum | C_DataValid_NoLimit
									| C_HaveIPEvent_Invalid | C_ExtMsgType_Invalid;
			return(C_OK);
		default:
			return(C_Error);
	}
}

/***************************************************************************
����ԭ�� 	Comm_MultFOut
��������	��ɶ๦�ܹ��������������봦��
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	��
������ע
***************************************************************************/
void		Comm_MultFOut(Str_Comm_645 *pV_645Frame)
{
	uchar8	Err = C_OK;

/*�жϳ���*/
	if(pV_645Frame->DataLen !=0x01)
	{
		Err = C_OtherErr;
	}
/*���ö๦������ӿں����������õĲ������ݸ���ģ�飬���ݷ���ֵȷ��ȡֵ�Ƿ���� */
	if(InF_ModifyFunctionWord(pV_645Frame->Data[C1DData_O_V_645]) != C_OK)
	{
		Err = C_OtherErr;
	}
/*Ӧ��*/
	if(pV_645Frame->AddressFlag == C_Broadcast)
	{/*�㲥��ַ��Ӧ��*/
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
����ԭ��: Comm_Set_BPSr_C17
��������: ��ɲ������޸���������봦��
�������: *pV_645Frame:���յ�������֡
�������: ��
���ز���: ��
ȫ�ֱ���: ��
������ע
*******************************************************************************/
void Comm_Set_BPSr_C17(Str_Comm_645 *pV_645Frame)
{
	ulong32	bpsDI;
    uchar8	bps;
    ushort16	V_ucDataLen, V_usDataEncode;
    uchar8	V_ucBuffer[CLOne485_Baud];

	/*�жϳ��ȺϷ���*/
	if( pV_645Frame->DataLen != CLOne485_Baud_645 )
	{
		Comm_Response_Set_ReadErr(C_OtherErr_645, pV_645Frame);
		return;
	}

	/*�ж����ݺ�����*/
    bps = SF_BPS645transfor698(pV_645Frame->Data[C17SetBpsData_O_V_645]);
	if( Is_CommBPS_OK(pV_645Frame->ChannelNo, bps) != C_OK )
	{
		Comm_Response_Set_ReadErr(C_Baud_NotModified_645, pV_645Frame);
		return;
	}

	/*ģ��ͨ��������ֻ������Ϊ9600*/
	if( (pV_645Frame->ChannelNo == C_Module) && (bps != C_9600) )
	{
		Comm_Response_Set_ReadErr(C_Baud_NotModified_645, pV_645Frame);
		return;
	}

	/*д���ݲ�*/
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
����ԭ�� 	Get_CommBpsDataCode
��������	��ȡͨ�������ʵ�DI
�������	CommNo			:ͨ����
������� 	��
���ز���	ͨ�������ʵ�DI
ȫ�ֱ��� 	��
������ע	ע��������뱣֤ͨ��������ȷ�ģ�����ᵼ��
				����Ԥ֪�Ĵ���
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
����ԭ�� 	Is_CommBPS_OK
��������	�ж�ͨ����bps�Ƿ����
�������	CommNo			:ͨ����
				bps				:������������
������� 	��
���ز���	C_OK/C_Error
ȫ�ֱ��� 	��
������ע
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
����ԭ�� 	Comm_FreezingOrder_C16
��������	��ɶ�������
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	��
������ע
***************************************************************************/
/*																mm   hh    DD    MM */
const	uchar8	FreezeOrder_C16_PLimit[CLTiming_Freeze_Time] = {0x60, 0x24, 0x29, 0x13};
void		Comm_FreezingOrder_C16(Str_Comm_645 *pV_645Frame)
{
	uchar8	Err = C_OK;
	uchar8	i;
	uchar8	MsgParm;
	uchar8	j;
/*�жϳ���*/
	if(pV_645Frame->DataLen != CLTiming_Freeze_Time)
	{
		Err = C_OtherErr;
	}
/*�ж������Ƿ�ΪBCD*/
	if( PF_Judge_BCD( CLTiming_Freeze_Time, &pV_645Frame->Data[CFreezeParm_O_V_645] ) != C_OK )
	{
		Err = C_OtherErr;
	}
/*�ж�ȫ99�ĸ�����4��ȫ99����ʾ˲ʱ���ᡣ99ֻ�ܴӺ�ǰ˳��ӵ��*/
/*���ݸ�ʽΪmm hh DD MM*/
	for( i = 4; i > 0; i-- )
	{
		if( pV_645Frame->Data[CFreezeParm_O_V_645 + i - 1] != 0x99 )
		{
			break;
		}
	}
	/*i=0��ʾ4��ȫ99��˲ʱ���ᡣi���ڼ�����ʾ�жϼ���ʱ���Ƿ�Ϸ���*/
	if(i == 0)
	{
		/*˲ʱ���ᷢ����Ϣ*/
		MsgParm = Pt_MsgFreezeImmediately;
		Comm_SendMsg(&MsgParm, (Pt_MsgFreezeImmediately_Len + 1), C_Msg_Freeze);
	}
	else
	{
		/*�ж������Ƿ�Ϸ�*/
		for( j = 0; j < i; j++ )
		{
			if( pV_645Frame->Data[CFreezeParm_O_V_645 + j] >= FreezeOrder_C16_PLimit[j] )
			{
				Err = C_OtherErr;
				break;
			}
		}
		if( ( pV_645Frame->Data[CFreezeParm_O_V_645 + 2] == 0 ) || ( pV_645Frame->Data[CFreezeParm_O_V_645 + 3] == 0 ) )
		{/*�ա��µ���0*/
			Err = C_OtherErr;
		}
		/*�ж��������û�г��ֹ�������������ݲ�*/
		if(Err == C_OK)
		{
			SV_Comm_Parse_Local.SafeControlFlag = SV_Comm_Parse_Local.SafeControlFlag | C_W_SafeFlag_3;
			InF_Write_Data(C_Msg_Communication, CTiming_Freeze_Time, &pV_645Frame->Data[CFreezeParm_O_V_645], CLTiming_Freeze_Time, SV_Comm_Parse_Local.SafeControlFlag);
		}
	}

	if(pV_645Frame->AddressFlag != C_Broadcast)
	{
		/*���ǹ㲥��Ӧ��*/
		Comm_Response_Set_ReadErr(Err,pV_645Frame);
	}
}

/***************************************************************************
����ԭ�� 	Comm_BroadcastSetClock_PointResponed
��������	��Ե�㲥УʱӦ��
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	��
������ע
***************************************************************************/
void		Comm_BroadcastSetClock_PointResponed(Str_Comm_645 *pV_645Frame,uchar8 V_ErrFlag)
{
    if(pV_645Frame->AddressFlag != C_Broadcast)
    {
      Comm_Response_Set_ReadErr(V_ErrFlag, pV_645Frame);
    }
}
/***************************************************************************
����ԭ�� 	Comm_BroadcastSetClock
��������	��ɹ㲥Уʱ
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	��
������ע	645Э�鴦�����ݸ�ʽ��Ҫ�ٺ˶� �����޸�ʱ���ʽֻ��֤���ݲ���� lzy 20211023
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

/*�жϳ���*/
	if(pV_645Frame->DataLen != 0x06)
	{
		return;
	}
/*��ϵͳʱ��*/
	DataLen = CLDate_Time;
	if( InF_Read_Data( CDate_Time, V_SystemDate_Time, &DataLen, &V_usDataEncode ) != C_OK )
	{
		/*���ʱ�Ӷ�����������ֻ�ܽ���ʱ�����ã��޷��㲥Уʱ*/
		Comm_BroadcastSetClock_PointResponed(pV_645Frame, C_OtherErr_645);
		return;
	}
/*�жϹ㲥Уʱʱ���Ƿ�Ϸ�*/
	if(PF_DataTimeActive_698(&pV_645Frame->Data[CBoardCastData_O_V_645 + C_ss_O], C_DT_Start_ss, CLDate_Time) != C_OK)
	{
		Comm_BroadcastSetClock_PointResponed(pV_645Frame, C_OtherErr_645);
		return;
	}

/*�жϵ�����û�й㲥Уʱ��*/
	if( ( SV_Comm_Parse.BDSC_RecentClock[CDate_Time_DD_O] ==  V_SystemDate_Time[CDate_Time_DD_O] )
	 && ( SV_Comm_Parse.BDSC_RecentClock[CDate_Time_MM_O] == V_SystemDate_Time[CDate_Time_MM_O] )
	 && ( SV_Comm_Parse.BDSC_RecentClock[CDate_Time_YYL_O] == V_SystemDate_Time[CDate_Time_YYL_O] ) )
	{
		Comm_BroadcastSetClock_PointResponed(pV_645Frame, C_OtherErr_645);
		return;
	}
/*�ж�ϵͳʱ���Ƿ���00:00����5min����������㲥Уʱ*/
    memset(&V_CMPDate_Time[C_ss_O], 0, 3);
	V_CMPDate_Time[CDate_Time_DD_O] = V_SystemDate_Time[CDate_Time_DD_O];
	V_CMPDate_Time[CDate_Time_MM_O] = V_SystemDate_Time[CDate_Time_MM_O];
	V_CMPDate_Time[CDate_Time_YYL_O] = V_SystemDate_Time[CDate_Time_YYL_O];
	PF_TimeSub_Min(V_CMPDate_Time, V_SystemDate_Time, &V_MinDIFValue);
	if( ( V_MinDIFValue < 5 ) || ( V_MinDIFValue >= 1435 ) )
	{
/*��㸽��5min*/
		Comm_BroadcastSetClock_PointResponed(pV_645Frame, C_OtherErr_645);
		return;
	}
/*�ж��Ƿ��ڽ����ո���*/
	DataLen = CLSettle_Day1;
	if( InF_Read_Data( CSettle_Day1, &V_CMPDate_Time[C_hh_O], &DataLen, &V_usDataEncode ) == C_OK )
	{
		PF_TimeSub_Min(V_CMPDate_Time, V_SystemDate_Time, &V_MinDIFValue);
		if(V_MinDIFValue < 5)
		{
/*�����ո���5min*/
			Comm_BroadcastSetClock_PointResponed(pV_645Frame, C_OtherErr_645);
			return;
		}
	}
	if( InF_Read_Data( CSettle_Day2, &V_CMPDate_Time[C_hh_O], &DataLen, &V_usDataEncode ) == C_OK )
	{
		PF_TimeSub_Min(V_CMPDate_Time, V_SystemDate_Time, &V_MinDIFValue);
		if(V_MinDIFValue < 5)
		{
/*�����ո���5min*/
			Comm_BroadcastSetClock_PointResponed(pV_645Frame, C_OtherErr_645);
			return;
		}
	}
	if( InF_Read_Data( CSettle_Day3, &V_CMPDate_Time[C_hh_O], &DataLen, &V_usDataEncode ) == C_OK )
	{
		PF_TimeSub_Min(V_CMPDate_Time, V_SystemDate_Time, &V_MinDIFValue);
		if(V_MinDIFValue < 5)
		{
/*�����ո���5min*/
			Comm_BroadcastSetClock_PointResponed(pV_645Frame, C_OtherErr_645);
			return;
		}
	}
/*�㲥Уʱʱ��Ӧ�ú�ϵͳʱ���ֵС�ڵ���5min*/
	V_DIF = PF_TimeSub_Min(&pV_645Frame->Data[CBoardCastData_O_V_645+C_ss_O], V_SystemDate_Time, &V_MinDIFValue);
	if(V_MinDIFValue >= 5)
	{
		/*����5min*/
		Comm_BroadcastSetClock_PointResponed(pV_645Frame, C_OtherErr_645);
		return;
	}
/*����дʱ��*/
/*����ˢ�����һ�ι㲥Уʱʱ��*/
	PF_CopyDataBytes(&pV_645Frame->Data[CBoardCastData_O_V_645 + C_ss_O], &SV_Comm_Parse.BDSC_RecentClock[C_ss_O], CLDate_Time);

	SV_Comm_Parse_Local.SafeControlFlag = SV_Comm_Parse_Local.SafeControlFlag | C_W_SafeFlag_3;

	V_ReturnData = InF_Write_Data(C_Msg_Communication, CDate_Time, &pV_645Frame->Data[CBoardCastData_O_V_645 + C_ss_O], CLDate_Time, SV_Comm_Parse_Local.SafeControlFlag);
	if(V_ReturnData != C_OK)
	{
		Comm_BroadcastSetClock_PointResponed(pV_645Frame, C_OtherErr_645);
		return;
	}
    Comm_BroadcastSetClock_PointResponed(pV_645Frame, C_OK);
/*�޸�ʱ����Ҫ��������Ϣ*/
/*��ǰ�޸�ʱ�ӣ���Ҫ���Ǹ��ɼ�¼*/
	if(V_DIF == C_LessThan)
	{
		InF_ChangeTime_LoadProfileCover();
	}
/*������Ϣ������ģ��*/
	Comm_SendMsgForUpdataParm(C_ReworkTime, C_Msg_DemandMetering);

	Comm_SendMsgForUpdataParm(C_ReworkTime, C_Msg_Deal_MultiRates);

/*���޸�ǰʱ��(7�ֽڣ�CDate_Time��ʽ)��������Ϣ������ģ��*/
	PF_CopyDataBytes(V_SystemDate_Time,&V_ucMsg[1],CLDate_Time);
	V_ucMsg[0] = Pt_7DayAdd_FreezeTime;
	Comm_SendMsg(&V_ucMsg[0], (Pt_7DayAdd_FreezeTime_Len+1),C_Msg_Freeze);

#if 0	/*�޸�ʱ����������ѹ�ϸ��� �ѿ������¶��᲻�ϸ�*/
/*���޸�ǰ��ʱ��(7�ֽڣ�CDate_Time��ʽ)��������Ϣ����ѹ�ϸ���ģ��*/
	PF_CopyDataBytes(&pV_645Frame->Data[CBoardCastData_O_V_645+C_ss_O],&V_ucMsg[CLDate_Time+1],CLDate_Time);
	V_ucMsg[0] = Pt_VRQTimeChange;
	Comm_SendMsg(V_ucMsg, (CLDate_Time*2+1),C_Msg_VoltageQualifiedRateMetering);
#endif
	
}

/***************************************************************************
����ԭ�� 	Comm_CondenseAAReadMAddress
��������	�����λ�����ַ����
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	��
������ע
***************************************************************************/
void		Comm_CondenseAAReadMAddress(Str_Comm_645 *pV_645Frame)
{
	uchar8	MeterAddress[CLComm_Address];
	uchar8	V_ReturnData;
	ushort16	DataLen, V_usDataEncode;
/*�жϳ���*/
	if(pV_645Frame->DataLen != 0x00)
	{
		Comm_Response_Set_ReadErr(C_OtherErr, pV_645Frame);
		return;
	}
/*�����ַ*/
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
����ԭ�� 	Comm_SetCommAddress
��������	�������ͨ�ŵ�ַ����
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	��
������ע
***************************************************************************/
#define		C_O_CommAddress	0
void		Comm_SetCommAddress(Str_Comm_645 *pV_645Frame)
{
	uchar8	V_ReturnData;

/*��ΪIs_ID_Auth_Ok_ResponseErr�����������֤����¾���ͨ����ȫ��֤*/
/*����������Ҫ�����жϱ�̿��ػ���״̬��ȷ��ֻ�б�̿�������������*/
	if( ( JudgeTimerExceed10min(&SI_JTimer_BSOn2500) != C_TimerEnable )
	 && ( JudgeTimerExceed10min(&ProgKey_Timer) != C_TimerEnable ) )
	{
		return;
	}
/*�жϳ���*/
	if(pV_645Frame->DataLen != CLComm_Address)
	{
		return;
	}
/*�ж�ͨ�ŵ�ַ�Ƿ���Ч*/
	V_ReturnData = DV_Comm_Address(&pV_645Frame->Data[C_O_CommAddress]);
	if(V_ReturnData != C_OK)
	{
		return;
	}
/*���ñ�ͨ�ŵ�ַ*/
	SV_Comm_Parse_Local.SafeControlFlag = SV_Comm_Parse_Local.SafeControlFlag | C_W_SafeFlag_3;

	InF_Write_Data(C_Msg_Communication, CComm_Address, &pV_645Frame->Data[C_O_CommAddress], CLComm_Address, SV_Comm_Parse_Local.SafeControlFlag);
	InF_Get_Comm_Address(SV_Comm_Address, 0x00);		/*����ͨ���е�ͨ�ŵ�ַ*/
/*��֯����Ӧ��֡*/
	Comm_Response_Set_ReadErr(C_OK, pV_645Frame);
}
/***************************************************************************
����ԭ�� 	Comm_SetPassword
��������	��������̽���������
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	��
������ע
***************************************************************************/
#define		CPAO_Offset		4
#define		CPAN_Offset		8
void		Comm_SetPassword(Str_Comm_645 *pV_645Frame)
{
	uchar8	PA_N;
	uchar8	V_ReturnData;

/*��ΪIs_ID_Auth_Ok_ResponseErr�����������֤����¾���ͨ����ȫ��֤*/
/*����������Ҫ�����жϱ�̿��ػ���״̬��ȷ��ֻ�б�̿�������������*/
	if( ( JudgeTimerExceed10min(&SI_JTimer_BSOn2500) != C_TimerEnable )
	 && ( JudgeTimerExceed10min(&ProgKey_Timer) != C_TimerEnable ) )
	{
		Comm_Response_Set_ReadErr(C_Unauthorized_645, pV_645Frame);
		return;
	}
/*�жϳ���,�����޸ģ�������ΪDI0-DI3 PAO P1O-P3O PAN P1N-P3N*/
	if(pV_645Frame->DataLen!=0x0C)
	{
		Comm_Response_Set_ReadErr(C_OtherErr_645, pV_645Frame);
		return;
	}
/*�ж����޸ĵ�����DI��PN�Ƿ����*/
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
		default:	/*��ʶ�����*/
			Comm_Response_Set_ReadErr(C_OtherErr_645, pV_645Frame);
			return;
	}
	if(PA_N != pV_645Frame->Data[CPAN_Offset])
	{
		Comm_Response_Set_ReadErr(C_OtherErr_645, pV_645Frame);
	}
/*�жϾ��ܼ��Ƿ����Ȩ�ޣ������Ƿ���ȷ*/
	if( pV_645Frame->Data[CPAO_Offset]>PA_N)
	{
		/*�����ȼ�������ĸ����ȼ�����*/
		Comm_Response_Set_ReadErr(C_Unauthorized_645, pV_645Frame);
		return;
	}
	V_ReturnData = Is_PW_OK(&pV_645Frame->Data[CPAO_Offset]);
	if(V_ReturnData != C_OK)
	{
		if( ( V_ReturnData == C_SupperPW_OK ) && ( JudgeTimerExceed10min(&SI_JTimer_BSOn2500) == C_TimerEnable ) )
		{/*У���¼ָ����������*/
			SV_Comm_Parse_Local.SafeControlFlag = SV_Comm_Parse_Local.SafeControlFlag|C_W_SafeFlag_3;
			InF_RecMeterNote_Clear(C_Msg_Communication, SV_Comm_Parse_Local.SafeControlFlag);
		}
		else
		{/*���ǳ������룬�Ҳ��ڳ���ģʽ�£����ܸ�������*/
			Comm_Response_Set_ReadErr(C_Unauthorized_645,pV_645Frame);
			return;
		}
	}
/*�ж��������Ƿ�ΪBCD*/
	if(PF_Judge_BCD(CLKey_0_Class, &pV_645Frame->Data[CPAN_Offset+1]))
	{
		Comm_Response_Set_ReadErr(C_OtherErr_645,pV_645Frame);
		return;
	}
/*д����*/
	SV_Comm_Parse_Local.SafeControlFlag = SV_Comm_Parse_Local.SafeControlFlag|C_W_SafeFlag_3;

	InF_Write_Data(C_Msg_Communication, pV_645Frame->DI, &pV_645Frame->Data[CPAN_Offset + 1], CLKey_0_Class, SV_Comm_Parse_Local.SafeControlFlag);

/*��֯����Ӧ��֡*/
	Comm_Response_FromP_Normal(pV_645Frame, &pV_645Frame->Data[CPAN_Offset], (CLKey_0_Class+1));

}
/***************************************************************************
����ԭ�� 	Comm_EventClear
��������	����¼��������������Ӧ��
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	ͨ����������
������ע
***************************************************************************/
void		Comm_EventClear(Str_Comm_645 *pV_645Frame)
{
	uchar8	Err;
	ulong32	EventDI;
    ulong32 V_ulOAD;

/*���ݶ�Ӧ���ܼ�������Ӧ���߼��ж�	*/
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
		/*�ܼ�����*/
		Err = C_Unauthorized_645;
	}
/*�߼��жϺ󣬽�����Ӧ�¼�������Ӧ��*/
	if(Err == C_OK)
	{
		PF_Buffer4ToUlong32(&pV_645Frame->Data[C_O_EventClear_DI], &EventDI, CLen_DI);

		/*ɽ��˫Э������*/
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
����ԭ�� 	Comm_02EventClear
��������	�¼���¼����02���߼��ж�
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	C_OK/C_OtherErr/C_Unauthorized
ȫ�ֱ��� 	��
������ע
***************************************************************************/
uchar8	Comm_02EventClear(Str_Comm_645 *pV_645Frame)
{
/*�ж��Ƿ��ڣ����ڳ�����02��04������Ӧ����Ȩ��*/
	if( JudgeTimerExceed10min(&SI_JTimer_BSOn2500) != C_TimerEnable )
	{
		return(C_Unauthorized);
	}
/*�жϳ���*/
	if(pV_645Frame->DataLen != ( CLen_OpCode + CLen_CommPW + CLen_DI ) )
	{
		return(C_OtherErr);
	}

/*�ж������Ƿ���ȷ*/
	if( Is_PW_OK( &(pV_645Frame->Data[CPW_SpecialO_V_645]) ) != C_OK )
	{
		return(C_Unauthorized);
	}

	return(C_OK);
}

/***************************************************************************
����ԭ�� 	Comm_98EventClear
��������	�¼���¼����98���߼��ж�
�������	*pV_645Frame				:���յ�������֡
������� 	pV_645Frame->Data[C_O_EventClear_DI]	:�����ܺ���¼�DIcopy����02��һ��λ��
���ز���	C_OK/C_OtherErr/C_Unauthorized
ȫ�ֱ��� 	��
������ע	645Э�鴦�����ݸ�ʽ��Ҫ�ٺ˶� �����޸�ʱ���ʽֻ��֤���ݲ���� lzy 20211023
***************************************************************************/
uchar8	Comm_98EventClear(Str_Comm_645 *pV_645Frame)
{
	ushort16	SError, ValidDataLen, V_usDataEncode;
	uchar8	*pValidData;
	uchar8	Clock[CLDate_Time];

/*�жϳ���*/
	if( pV_645Frame->DataLen <= ( CLen_OpCode + CLen_CommPW + CLen_DI ) )
	{
		return(C_OtherErr);
	}

/*���ð�ȫģ��ӿں���*/
	pValidData = &pV_645Frame->Data[CData_OtherO_V_645];
	ValidDataLen = pV_645Frame->DataLen - CLen_CommPW - CLen_OpCode;
	/*���ܺ�������pValidData������Ϊ12.����R1-R12����*/
	SError = InF_S_EventClear(pValidData, (uchar8 *)&ValidDataLen);
	if(SError != C_OK)
	{
		if(SError == C_SERR_ESAM_VF)
		{/*ESAM��֤ʧ�ܣ�200��++*/
			Comm_DealwithSPTVariable(C_SPTNumAdd);
		}
		return(C_Unauthorized_645);
	}
/*�ж�R1������*/
	if(pValidData[C_R1_O] != 0x1B)
	{
		return(C_Unauthorized_645);
	}
/*�жϽ�ֹʱ���Ƿ���Ч����ЧӦ����������*/
	if(PF_DataTimeActive(&pValidData[C_R3_O], C_DT_Start_ss, CLDate_Time) != C_OK)
	{
		return(C_OtherErr_645);
	}
/*�ж�ϵͳʱ���������ֹʱ��֮ǰ*/
	ValidDataLen = CLDate_Time;
	if(InF_Read_Data(CDate_Time, Clock, &ValidDataLen, &V_usDataEncode) == C_OK)
	{/*ʱ����Ч*/
		if( PF_Campare_Data( &pValidData[C_R3_O], Clock, CLDate_Time) == C_LessThan )
		{
			return(C_Unauthorized_645);
		}
	}
/*���������¼���ʶ����õ�02�������¼������Ӧ�¼���ʶ��λ��.*/
	pV_645Frame->Data[C_O_EventClear_DI] = pValidData[C_R9_O];
	pV_645Frame->Data[C_O_EventClear_DI + 1] = pValidData[C_R9_O + 1];
	pV_645Frame->Data[C_O_EventClear_DI + 2] = pValidData[C_R9_O + 2];
	pV_645Frame->Data[C_O_EventClear_DI + 3] = pValidData[C_R9_O + 3];

	return(C_OK);
}
/***************************************************************************
����ԭ�� 	Comm_DemandClear
��������	����������������Ӧ��
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	ͨ����������
������ע
***************************************************************************/
void		Comm_DemandClear(Str_Comm_645 *pV_645Frame)
{
	uchar8	Err;

/*���ݶ�Ӧ���ܼ�������Ӧ���߼��ж�	*/
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
		/*�ܼ�����*/
		Err = C_Unauthorized;
	}
/*�߼��жϺ󣬽�����Ӧ�¼�������Ӧ��*/
	if(Err == C_OK)
	{
/*��������ɹ�,����������Ϣ��ͬʱ����������ɹ���������Ӧģ��*/
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
����ԭ�� 	Comm_98DemandClear
��������	���98��������������������֤
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	C_OK/C_Unauthorized/C_OtherErr
ȫ�ֱ��� 	��
������ע	645Э�鴦�����ݸ�ʽ��Ҫ�ٺ˶� �����޸�ʱ���ʽֻ��֤���ݲ���� lzy 20211023
***************************************************************************/
uchar8	Comm_98DemandClear(Str_Comm_645 *pV_645Frame)
{
	ushort16	SError, ValidDataLen, V_usDataEncode;
	uchar8	*pValidData;
	uchar8	Clock[CLDate_Time];

/*�жϳ���*/
	if( pV_645Frame->DataLen <= ( CLen_OpCode + CLen_CommPW ) )
	{
		return(C_OtherErr);
	}

/*���ð�ȫģ��ӿں���*/
	pValidData = &pV_645Frame->Data[CData_OtherO_V_645];
	ValidDataLen = pV_645Frame->DataLen - CLen_CommPW - CLen_OpCode;
	/*���ܺ�������pValidData������Ϊ8.����R1-R8����*/
	SError = InF_S_DemandClear(pValidData, (uchar8 *)&ValidDataLen);
	if(SError != C_OK)
	{
		if(SError == C_SERR_ESAM_VF)
		{/*ESAM��֤ʧ�ܣ�200��++*/
			Comm_DealwithSPTVariable(C_SPTNumAdd);
		}
		return(C_Unauthorized);
	}
/*�ж�R1������*/
	if(pValidData[C_R1_O] != 0x19)
	{
		return(C_Unauthorized);
	}
/*�жϽ�ֹʱ���Ƿ���Ч����ЧӦ����������*/
	if(PF_DataTimeActive(&pValidData[C_R3_O], C_DT_Start_ss, CLDate_Time) != C_OK)
	{
		return(C_OtherErr);
	}
/*�ж�ϵͳʱ���������ֹʱ��֮ǰ*/
	ValidDataLen = CLDate_Time;
	if(InF_Read_Data(CDate_Time, Clock, &ValidDataLen, &V_usDataEncode) == C_OK)
	{/*ʱ����Ч*/
		if(PF_Campare_Data(&pValidData[C_R3_O], Clock, CLDate_Time) == C_LessThan)
		{
			return(C_Unauthorized);
		}
	}
	return(C_OK);

}
/***************************************************************************
����ԭ�� 	Comm_04DemandClear
��������	ͨ������04(02)�������ж�
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	C_OK/C_OtherErr/C_Unauthorized
ȫ�ֱ��� 	��
������ע
***************************************************************************/
uchar8	Comm_04DemandClear(Str_Comm_645 *pV_645Frame)
{
/*�ж��Ƿ��ڣ����ڳ�����02��04������Ӧ����Ȩ��*/
	if( JudgeTimerExceed10min(&SI_JTimer_BSOn2500) != C_TimerEnable )
	{
		return(C_Unauthorized);
	}
/*�жϳ���*/
	if( pV_645Frame->DataLen != (CLen_OpCode + CLen_CommPW) )
	{
		return(C_OtherErr);
	}

/*�ж������Ƿ���ȷ*/
	if( Is_PW_OK( &( pV_645Frame->Data[CPW_SpecialO_V_645] ) ) != C_OK )
	{
		return(C_Unauthorized);
	}

	return(C_OK);

}
/***************************************************************************
����ԭ�� 	Comm_MeterClear
��������	ͨ���������������Ӧ��
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	ͨ����������
������ע	MeterClearFlag��־�ڱ���������2������2��Ȩ���жϺ�������һ����
***************************************************************************/
void		Comm_MeterClear(Str_Comm_645 *pV_645Frame)
{
	uchar8	Err;

	SV_Comm_Parse_Local.MeterClearFlag = SV_Comm_Parse_Local.MeterClearFlag | C_ClearMeterSafeFlag_1;
/*�жϱ����Ƿ�֧�ָ�����*/
	if(IsMeterTypeSupport(pV_645Frame) != C_OK)
	{
		Comm_Response_Set_ReadErr(C_Unauthorized, pV_645Frame);
		SV_Comm_Parse_Local.MeterClearFlag = 0;
		SV_Comm_Parse_Local.SafeControlFlag = 0;
		return;
	}

/*�����ܼ����ж�Ӧ�ж�	*/
	if(pV_645Frame->Data[CPW_SpecialO_V_645] == 0x98)
	{
		/*98�����룬�����ڳ�������*/
		Err = Comm_98MeterClear(pV_645Frame);
	}
	else if(pV_645Frame->Data[CPW_SpecialO_V_645] == 0x02)
	{
		/*02�����룬�����ڳ�������,������ۺ��г���ϱ�̿�������*/
		Err = Comm_02MeterClear(pV_645Frame);
	}
	else
	{
		/*�ܼ�����*/
		Err = C_Unauthorized;
	}

	if(Err == C_OK)
	{
		/*698����645�޸�*/
		if( ( InF_JudgeKeyStatus() == C_StateOfOfficialKey )    /*��ʽ��Կ���������㣬��ȫ�淶*/
		 && ( JudgeTimerExceed10min(&SI_JTimer_BSOn2500 ) == C_TimerDisable ) )
		{
			Err = C_Unauthorized;	/*������δ��Ȩ*/
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
����ԭ�� 	Comm_02MeterClear
��������	���02�����������֤
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	C_OK/C_OtherErr/C_Unauthorized
ȫ�ֱ��� 	��
������ע
***************************************************************************/
uchar8	Comm_02MeterClear(Str_Comm_645 *pV_645Frame)
{
	SV_Comm_Parse_Local.MeterClearFlag = SV_Comm_Parse_Local.MeterClearFlag | C_ClearMeterSafeFlag_2;
/*�ж��Ƿ��ڣ����ڳ�����02��04������Ӧ����Ȩ��*/
	if( JudgeTimerExceed10min(&SI_JTimer_BSOn2500) != C_TimerEnable )
	{
		return(C_Unauthorized);
	}
/*�жϳ���*/
	if( pV_645Frame->DataLen != (CLen_OpCode + CLen_CommPW) )
	{
		return(C_OtherErr);
	}

/*�ж������Ƿ���ȷ*/
	if( Is_PW_OK(&(pV_645Frame->Data[CPW_SpecialO_V_645])) != C_OK )
	{
		return(C_Unauthorized);
	}

	return(C_OK);
}
/***************************************************************************
����ԭ�� 	IsMeterTypeSupport
��������	�жϱ�������Ƿ�֧�ָ�����
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	C_OK֧��/C_Error��֧��
ȫ�ֱ���
������ע	ע�⣬����ԷǷ���ʶ�벻�����жϡ��Ƿ���ʶ��
				������ͨ��ģ����������л�����жϵġ�

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

/*����������ر�֧��98������*/
	if(pV_645Frame->C == 0x1A)
	{
		if(pV_645Frame->Data[CPW_SpecialO_V_645] == 0x98)
		{
			if(C_Meter_Type == C_L_SmartMeter)
			{	/*���ر�֧��1A��������*/
				return(C_Error);
			}
		}
		return(C_OK);
	}
/*��ȫ�淶����*/
	if(pV_645Frame->C == 0x03)
	{
		if(C_Meter_Type == C_L_SmartMeter)
		{/*���ر�֧��*/
			return(C_OK);
		}
		else
		{/*Զ�̺����ܱ�*/
			switch(pV_645Frame->DI)
			{
				case		CDI_Init_Money:		/*Զ��Ǯ����ʼ������*/
				case		CDI_ROpenAnAccount:
				case		CDI_RChgBL:
					return(C_Error);
				default:						/*�������֧��*/
					return(C_OK);
			}
		}

	}
/*����*/
	if(pV_645Frame->C == 0x14)
	{
		/*14���������������ж���14��������ж�������Ч�Ժ���Is_SetParmData_Ok���ж�*/
		/*���ݱ��ͽ����ж�*/
		return(C_OK);
	}

/*������*/
	if(pV_645Frame->C == 0x11)
	{/*�����ر��������֧�֣������������ܱ��ѿر�֧��*/
		if(C_Meter_Type == C_L_SmartMeter)
		{
			return(C_OK);
		}
		/*�ѿر�����ܱ�*/
		if(pV_645Frame->Data[C_O_DI3] == 0x00)
		{/*������*/
			if(pV_645Frame->Data[C_O_DI2] == 0x0D)
			{/*���������ر�֧��*/
				return(C_Error);
			}
			if(pV_645Frame->Data[C_O_DI2] == 0x90)
			{/*ʣ���͸֧�������ر�֧��*/
				return(C_Error);
			}
			return(C_OK);
		}
		if( ( pV_645Frame->DI & 0xFFFF0000 ) == 0x05080000 )
		{/*ʣ�����ն�������ر�֧��*/
			return(C_Error);
		}
		if( ( pV_645Frame->DI & 0xFFFF0000 ) == 0x05050000 )
		{/*���ʵ���л�����ֻ�б��ر��֧��*/
			return(C_Error);
		}
		if( ( pV_645Frame->DI & 0xFFFF0000 ) == 0x05070000 )
		{/*���ݱ��л�����ֻ�б��ر��֧��*/
			return(C_Error);
		}
		if( ( pV_645Frame->DI & 0xFFFFFF00 ) == 0x04001000 )
		{/*����������ƵȽ����ر�֧��*/
			return(C_Error);
		}
		if( ( pV_645Frame->DI & 0xFFFF0000 ) == 0x04050000 )
		{/*���ʵ���࣬�����ر�֧��*/
			return(C_Error);
		}
		if( ( pV_645Frame->DI & 0xFFFF0000 ) == 0x04060000 )
		{/*���ݵ����*/
			return(C_Error);
		}
		if( ( pV_645Frame->DI & 0xFFFFFF00 ) == 0x03300F00 )
		{/*���ʱ��̼�¼*/
			return(C_Error);
		}
		if( ( pV_645Frame->DI & 0xFFFFFF00 ) == 0x03301000 )
		{/*���ݱ��̼�¼*/
			return(C_Error);
		}
		if( ( pV_645Frame->DI & 0xFFFFFF00 ) == 0x03301300 )
		{/*�쳣�忨��¼��¼*/
			return(C_Error);
		}
		if( pV_645Frame->DI == 0x03301400 )
		{/*�Ƿ��忨����*/
			return(C_Error);
		}
		if( ( pV_645Frame->DI & 0xFFFF0000 ) == 0x03330000 )
		{/*�����¼*/
			return(C_Error);
		}
		if( ( pV_645Frame->DI & 0xFFFF0000 ) == 0x03340000 )
		{/*�˷Ѽ�¼*/
			return(C_Error);
		}
		for( i = 0; i < CLen_TB_OnlyLocalSupport; i++ )
		{/*ʣ����ȷ���Ƿ��Ϊ���ر�֧��*/
			if(pV_645Frame->DI == TB_OnlyLocalSupport[i])
			{
				return(C_Error);
			}
		}
		return(C_OK);
	}
/*���������֧��*/
	return(C_OK);
}
/***************************************************************************
����ԭ�� 	Is_PW_OK
��������	�ж������Ƿ���ȷ
�������	pCommPW		:ͨ�������ַ���̶�4�ֽ�
������� 	��
���ز���	C_OK/C_Error/C_SupperPW_OK
ȫ�ֱ��� 	��
������ע	�������������ֻҪҪ0204���룬��Ҫ���������
20140715�޸�:
				���ӳ�������:
				1�������������������CRC����ʱ�ж��Ƿ�Ϊ��������
				2�����ڽ��볧��ģʽ������ڳ���ģʽ��
				        ����0c������������ʹ�á�
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

/*�����ж������Ƿ�������Ǳ���ֱ�ӷ����������*/
	if( Comm_DealwithSPTVariable(C_JudgeKeyErr | KeyClassFlag) == C_KeyErr_Num_Over )
	{
		return(C_Error);
	}

/*�жϴ��ݽ��������Ƿ���ȷ*/
	if( InF_Read_Data(PW_DI, &PW[0], &PW_Len, &V_usDataEncode ) == C_OK )
	{/*�����������ȥ�ж�������ȷ���Ǵ���*/
		if( PF_Campare_Data(&PW[0], &pCommPW[PW_O_Comm], PW_Len ) == C_Equal )
		{
			Comm_DealwithSPTVariable(C_ClrKeyErrNum | KeyClassFlag);
			return(C_OK);
		}
		else
		{
			if(InF_JudgeIJTimer() != C_OK)							/*�������������*/
			{
				Comm_DealwithSPTVariable(C_KeyErrNumAdd | KeyClassFlag);
			}
			return(C_Error);
		}
	}
	else
	{/*��������������ж��Ƿ�Ϊ�������롣�Ƿ��س���������ȷ*/
		if( ( pCommPW[PA_O_Comm] == 0x02 ) && ( pCommPW[PW_O_Comm] == 0x22 )
		 && ( pCommPW[PW_O_Comm + 1] == 0x12 ) && ( pCommPW[PW_O_Comm + 2] == 0x11 ) )
		{/*�ܼ�02��������111222���ڳ�������*/
			return(C_SupperPW_OK);
		}
		return(C_Error);
	}
}
/***************************************************************************
����ԭ�� 	Comm_98MeterClear
��������	���98�����������֤
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	C_OK/C_OtherErr/C_Unauthorized
ȫ�ֱ��� 	��
������ע	645Э�鴦�����ݸ�ʽ��Ҫ�ٺ˶� �����޸�ʱ���ʽֻ��֤���ݲ���� lzy 20211023
***************************************************************************/
uchar8	Comm_98MeterClear(Str_Comm_645 *pV_645Frame)
{
	ushort16	SError, ValidDataLen, V_usDataEncode;
	uchar8		*pValidData;
	uchar8		Clock[CLDate_Time];

	SV_Comm_Parse_Local.MeterClearFlag = SV_Comm_Parse_Local.MeterClearFlag | C_ClearMeterSafeFlag_2;

/*�жϳ���*/
	if( pV_645Frame->DataLen <= ( CLen_OpCode + CLen_CommPW ) )
	{
		return(C_OtherErr);
	}

/*���ð�ȫģ��ӿں���*/
	pValidData = &pV_645Frame->Data[CData_OtherO_V_645];
	ValidDataLen = pV_645Frame->DataLen - CLen_CommPW - CLen_OpCode;
	/*���ܺ�������pValidData������Ϊ8.����R1-R8����*/
	SError = InF_S_MeterClear(pValidData, (uchar8 *)&ValidDataLen);
	if(SError != C_OK)
	{
		if(SError == C_SERR_ESAM_VF)
		{/*ESAM��֤ʧ�ܣ�200��++*/
			Comm_DealwithSPTVariable(C_SPTNumAdd);
		}
		return(C_Unauthorized);
	}
/*�ж�R1������*/
	if(pValidData[C_R1_O] != 0x1A)
	{
		return(C_Unauthorized);
	}
/*�жϽ�ֹʱ���Ƿ���Ч����ЧӦ����������*/
	if( PF_DataTimeActive( &pValidData[C_R3_O], C_DT_Start_ss, CLDate_Time ) != C_OK )
	{
		return(C_OtherErr);
	}
/*�ж�ϵͳʱ���������ֹʱ��֮ǰ*/
	ValidDataLen = CLDate_Time;
	if(InF_Read_Data( CDate_Time, Clock, &ValidDataLen, &V_usDataEncode ) == C_OK )
	{/*ʱ����Ч*/
		if( PF_Campare_Data( &pValidData[C_R3_O], Clock, CLDate_Time ) == C_LessThan )
		{
			return(C_Unauthorized);
		}
	}
	return(C_OK);
}
/***************************************************************************
����ԭ�� 	Comm_SecurityParse
��������	ͨ��03���������Ӧ��
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	ͨ����������
������ע
***************************************************************************/
void		Comm_SecurityParse(Str_Comm_645 *pV_645Frame)
{
/*�ж��Ƿ��ڵ͹�����ͨ��*/
	if(pV_645Frame->PowerFlag != C_PowerOn)
	{
		Comm_Response_03_Err(C_SERR_OtherErr, pV_645Frame);
		return;
	}
/*�����Ƿ�֧��*/
	if(IsMeterTypeSupport(pV_645Frame) != C_OK)
	{
		Comm_Response_03_Err(C_SERR_OtherErr, pV_645Frame);
		return;
	}
/*�жϰ�ȫ��֤����*/
	switch(pV_645Frame->DI)
	{
		case		CDI_Auth:		/*�����֤*/
			Comm_Authentication(pV_645Frame);
			break;
		case		CDI_IRCReq_645:		/*������֤��������*/
			Comm_IRCertification_Request(pV_645Frame);
			break;
		case		CDI_IR_ExtAuth_645:	/*������֤*/
			Comm_IRCertification_Instruction(pV_645Frame);
			break;
		default:
			Comm_Response_03_Err(C_SERR_OtherErr, pV_645Frame);
			break;
	}

	return;
}

/***************************************************************************
����ԭ�� 	InF_PurchaseDL
��������	����ֵ����ֵ�����ݲ㣬��д�����¼��ͬ��ESAMǮ���ļ�
�������	PPMoney					:���ι����Hex��λΪ��
				V_SafeFlag				:��ȫ��־��=C_W_SafeFlag��Ч
������� 	��
���ز���	��
������ע	�ڵ��ñ�����ǰ����ȷ���ܳ�ֵ
				�����˶ڻ������������ESAM��֤�Ȳ��衣
***************************************************************************/
void		InF_PurchaseDL(ulong32	PPMoney,uchar8	V_SafeFlag)
{
	uchar8	V_ucbuf[CLChargeBal_Hex_Cent], Flag;
	ulong32	PreRemainMoney;
    ushort16 V_usDataLen, V_usDataEncode[30] = {0x00};

/*���ȶ�ȡ���ݲ��ʣ�����Ϊ���ñ�����ǰ�Ѷ����ñ��������
�������ǲ��ó�ֵ�ġ�*/
    V_usDataLen = CLChargeBal_Hex_Cent;
	InF_GetData_ObjectManage(CChargeBal_Hex_Cent, V_ucbuf, &V_usDataLen, V_usDataEncode);
	PF_Buffer4ToUlong32(V_ucbuf, &PreRemainMoney, CLChargeBal_Hex_Cent);

/*���й����¼���¼�����г�ֵ*/
	Flag = C_Money_Purchase;
	InF_WRPre1PowerPurchaseRecord(PPMoney, V_SafeFlag, Flag);
/*/ͬ��ESAM*/
	V_usDataLen = CLChargeBal_Hex_Cent;
	if(InF_GetData_ObjectManage(CChargeBal_Hex_Cent, V_ucbuf, &V_usDataLen, V_usDataEncode) == C_OK)
	{
		InF_S_UpdataChargeBalInESAM(V_ucbuf);
	}
}
/***************************************************************************
����ԭ�� 	InF_Compare_CustomerNum
��������	�ȶԿͻ����
�������	*pCustomerNum			:����Ŀͻ���ţ��̶�Ϊ6�ֽڣ�
										:����645С��ģʽ
������� 	��
���ز���	C_OK					:�����ݲ�ͻ����һ�¡�
				C_Error					:�����ݲ�ͻ���Ų�һ��
ȫ�ֱ��� 	��
������ע	��
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
����ԭ�� 	InF_V_CustomerNumWithEsam
��������	��֤�ͻ������Ƿ�ΪBCD,Mac�Ƿ���ȷ��ȫ����ȷˢ��ESAM
�������	*pCustomerNum			:����Ŀͻ���ţ��̶�Ϊ6�ֽ�+4�ֽ�Mac��
										:����645С��ģʽ
������� 	��
���ز���	C_OK/C_SERR_OtherErr/C_SERR_ESAM_VF
ȫ�ֱ��� 	��
������ע	��
***************************************************************************/
ushort16	InF_V_CustomerNumWithEsam(uchar8	*pCustomerNum)
{
	ushort16		Serr16;

/*�����ж��Ƿ�ΪBCD*/
	if( PF_Judge_BCD( CLCustomer_Num, pCustomerNum ) != C_OK )
	{
		return(C_SERR_OtherErr);
	}
/*����ESAM��Mac��֤��û�����⣬��ˢ��ESAM�����������ļ�*/
	Serr16 = InF_S_WritePara_PlainTextMAC(CCustomer_Num, pCustomerNum, ( CLCustomer_Num + C_MacLen ) );

	return(Serr16);
}

/***************************************************************************
����ԭ�� 	InF_Judge_ChgBal_PC_Num
��������	�жϹ�������ͳ�ֵ���
�������	V_ChgBal				:����ֵ��Hex����λΪ��
				V_PC_Num			:���жϵĹ��������Hex
������� 	��
���ز���	C_PC_Num_Equal		:	����������
				C_SERR_RechargeNumErr:	��ʾ���ڱ��ڹ������2��2����
				C_SERR_RechargeHoarding:	���������1�������ڻ������
				C_MeterPC_Num_Large	:	���ڹ��������
				C_SERR_OtherErr		:	��������
				C_Can_EPurchase		:	���������1�����û�г��ڻ����Գ�ֵ
ȫ�ֱ���
������ע	���������ж��˹�������������������������ֵ������
				�ٽ��г�ֵ���ڻ����ж�
***************************************************************************/
ushort16		InF_Judge_ChgBal_PC_Num(ulong32	V_ChgBal,ulong32 V_PC_Num)
{
	ulong32		Meter_PC_Num;
	ulong32		Meter_OverDraft;
	ulong32		Meter_ChargeBal;
	ulong32		Hoarding_Money_Hex_Cent;
	uchar8		V_ucbuf[CLChargeBal_Hex_Cent];
    ushort16    V_usDataLen, V_usDataEncode[30] = {0x00};

/*�����ݲ�ʣ���Meter_ChargeBal ��λ�Ƿ֣�Hex��ʽ*/
    V_usDataLen = CLChargeBal_Hex_Cent;
	if( InF_GetData_ObjectManage( CChargeBal_Hex_Cent, V_ucbuf, &V_usDataLen, V_usDataEncode ) != C_OK )
	{/*���ݲ�ʣ��������������ó�ֵ*/
		return(C_SERR_OtherErr);
	}
	PF_Buffer4ToUlong32(V_ucbuf, &Meter_ChargeBal, CLChargeBal_Hex_Cent);

/*�����ݲ��͸֧���*/
    V_usDataLen = CLOverDraft_Hex_Cent;
	if( InF_GetData_ObjectManage( COverDraft_Hex_Cent, V_ucbuf, &V_usDataLen, V_usDataEncode ) != C_OK )
	{/*���ݲ�͸֧�������������ó�ֵ*/
		return(C_SERR_OtherErr);
	}
	PF_Buffer4ToUlong32(V_ucbuf, &Meter_OverDraft, CLOverDraft_Hex_Cent);

/*��ESAM�еĹ������*/
    V_usDataLen = CLOverDraft_Hex_Cent;
    if( InF_GetData_ObjectManage( CPurchasePowTime, V_ucbuf, &V_usDataLen, V_usDataEncode ) != C_OK )
	{/*�������������*/
		return(C_SERR_OtherErr);
	}
    PF_Buffer4ToUlong32(V_ucbuf, &Meter_PC_Num, CLOverDraft_Hex_Cent);

/*�жϹ������*/
	if(V_PC_Num < Meter_PC_Num)
	{
		return(C_MeterPC_Num_Large);
	}
	else if(V_PC_Num == Meter_PC_Num)
	{
		return(C_PC_Num_Equal);
	}
/*���´��жϵĹ���������ڱ��ڹ������*/
	if( ( V_PC_Num - Meter_PC_Num ) != 1 )
	{
		return(C_SERR_RechargeNumErr);
	}
/*������1���жϳ��ڻ�*/
/*���α������ڻ�*/
	if( InF_Read_Data( CHoarding_Money, V_ucbuf, &V_usDataLen, V_usDataEncode ) == C_OK )
	{
		PF_BCDtoHexBytes( V_ucbuf, &Hoarding_Money_Hex_Cent, CLHoarding_Money );
		if(Hoarding_Money_Hex_Cent == 0)
		{/*��ֵ����Ϊ0����Ч��999999.99Ԫ����ȫ�淶7.5*/
			Hoarding_Money_Hex_Cent = 99999999;
		}
	}
	else
	{/*�����ֵ��������Ĭ��Ϊ999999.99Ԫ*/
		Hoarding_Money_Hex_Cent = 99999999;
	}
/*�ж���û�г��ڻ���ֵ*/
	if(V_ChgBal > 99999999)
	{/*̫��ֱ���˳���*/
		return(C_SERR_RechargeHoarding);
	}
	V_ChgBal = V_ChgBal + Meter_ChargeBal;		/*��ֵ���+ʣ����*/
	if(V_ChgBal <= Meter_OverDraft)
	{/*ʣ����С�ڵ���͸֧���,�϶������ֵ*/
		return(C_Can_EPurchase);
	}
	else if( ( V_ChgBal - Meter_OverDraft ) > Hoarding_Money_Hex_Cent )
	{/*���ڻ�*/
		return(C_SERR_RechargeHoarding);
	}
	else
	{
		return(C_Can_EPurchase);
	}
}

/***************************************************************************
����ԭ�� 	 uchar8 InF_DealWith_L_R_OAAFlag(uchar8	Method,uchar8	Value)
��������	����Զ�̿���״̬
�������
Value:		C_HaveOpenAnAccount 0x68Ϊ���ڿ���״̬
	   		C_HaveNoOpenAnAccount 0x00Ϊ����δ����״̬
Method:		C_Judge_Method_R 0x01Ϊ�ж�Զ�̿���״̬
			C_Set_Method_R 0x02Ϊ����Զ�̿���״̬
			C_Judge_Method_L 0x10Ϊ�жϱ��ؿ���״̬
			C_Set_Method_L 0x11Ϊ�����ؿ���״̬
������� 	��
���ز���	C_HaveOpenAnAccount/C_HaveNoOpenAnAccount
ȫ�ֱ��� 	��
������ע	1������ʱ�����ˢ�µ������״̬��3����
				2������ʱ������ò��ɹ����᷵��C_HaveNoOpenAnAccount
***************************************************************************/
#define	C_Method_R	0x00
#define	C_Method_L	0x10
uchar8	InF_DealWith_L_R_OAAFlag(uchar8	Method,uchar8	Value)
{
	uchar8		AccountState[CLRemote_Local_State + 5], V_ucStatusOff, V_ucSource;
	ushort16	DataLen = CLRemote_Local_State, V_usDataEncode;

/*���ȶ����ݲ�Զ�̱��ؿ���״̬����������Ĭ��Ϊδ����*/
	if(InF_Read_Data(CRemote_Local_State, AccountState, &DataLen, &V_usDataEncode) != C_OK)
	{
		AccountState[C_O_ROpenAnAccount] = C_HaveNoOpenAnAccount;
		AccountState[C_O_LOpenAnAccount] = C_HaveNoOpenAnAccount;
	}
/*�ж��Ƿ�Ϊ���÷���������ˢ�����ݲ��Ӧ������־ΪValueֵ��ͬʱˢ��״̬��3*/
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
����ԭ�� 	InF_UpdateAccountStateInMeterStatus3
��������	���µ������״̬��3��Զ�̱��ؿ���״̬
�������	��
������� 	��
���ز���	��
ȫ�ֱ��� 	��
������ע	1���������ݲ�02FE0501ˢ�µ������״̬��3��Զ�̱��ؿ���״̬
				2����������Զ��Ǯ����ʼ�����Զ�̿�������ʱ����
				3���������ڱ��ز������Ԥ�ƿ������ؿ����ǵ���
				4��ͨ��1min����һ��
			ע�Ȿ������InF_DealWith_L_OAAFlag��set�����е����ˣ�
			�������ﲻҪ�ٵ���InF_DealWith_L_OAAFlag��Judge���������γɻ���!
***************************************************************************/
void		InF_UpdateAccountStateInMeterStatus3(void)
{
	uchar8		AccountState[CLRemote_Local_State];
	ushort16	DataLen, V_usDataEncode;
	uchar8		Meter_Work_State3[CLMeter_Work_State3 + 3];

/*��ȡ״̬��3*/
	DataLen = CLMeter_Work_State3;
	InF_Read_Data(CMeter_Work_State3, Meter_Work_State3, &DataLen, &V_usDataEncode);
	if(C_Meter_Type == C_L_SmartMeter)
	{
/*��ȡ���ݲ�ר�ű���Ŀ���״̬	*/
		DataLen = CLRemote_Local_State;
		InF_Read_Data(CRemote_Local_State, AccountState, &DataLen, &V_usDataEncode);
/*����02FE0501д�������״̬3�п���״̬��*/
/*bit14Ϊ���ؿ��� bit15ΪԶ�̿�����*/
/*=0��ʾ������=1��ʾδ����*/
		if(AccountState[C_O_ROpenAnAccount] == C_HaveOpenAnAccount)
		{/*Զ���ѿ�����Bit15 = 0*/
			Meter_Work_State3[CO_RemoteOAccount] = Meter_Work_State3[CO_RemoteOAccount] & (~CB_RemoteOAccount);
		}
		else
		{/*Զ��δ������Bit15 = 1*/
			Meter_Work_State3[CO_RemoteOAccount] = Meter_Work_State3[CO_RemoteOAccount] | CB_RemoteOAccount;
		}
		if(AccountState[C_O_LOpenAnAccount] == C_HaveOpenAnAccount)
		{/*�����ѿ�����Bit14 = 0*/
			Meter_Work_State3[CO_LocalOAccount] = Meter_Work_State3[CO_LocalOAccount] & (~CB_LocalOAccount);
		}
		else
		{/*����δ������Bit14 = 1*/
			Meter_Work_State3[CO_LocalOAccount] = Meter_Work_State3[CO_LocalOAccount] | CB_LocalOAccount;
		}
	}
	else
	{/*Զ���ѿ�����Bit15 = 0*/
		Meter_Work_State3[CO_RemoteOAccount] = Meter_Work_State3[CO_RemoteOAccount] & (~CB_RemoteOAccount);
	/*�����ѿ�����Bit14 = 0*/
		Meter_Work_State3[CO_LocalOAccount] = Meter_Work_State3[CO_LocalOAccount] & (~CB_LocalOAccount);
	}
	InF_Write_Data(C_Msg_Communication, CMeter_Work_State3, Meter_Work_State3, CLMeter_Work_State3, C_W_SafeFlag);
}
/***************************************************************************
����ԭ�� 	InF_WRPre1PowerPurchaseRecord
��������	д���һ�ι����¼
�������	V_ulBuyMoney				:�������ʽ:
			C_SafeFlag					��ȫ��־
			Flag						�����־
������� 	��
���ز���	��
ȫ�ֱ��� 	��
������ע
***************************************************************************/
void		InF_WRPre1PowerPurchaseRecord(ulong32 V_ulBuyMoney,uchar8 C_SafeFlag,uchar8 Flag)
{
	uchar8	 V_ucDataBuff[300] = {0};
	ushort16 V_usOffset = 0, V_ResidualLength, V_ucRelateoff;
	uchar8	 V_Event_Flag;

	V_usOffset = SF_GetProgFixedData_698(CBuyCurr_Degree, V_ucDataBuff);	/*ȡ�̶�������*/

	V_ResidualLength = 300 - V_usOffset;									/*ʣ��buff����*/
	V_Event_Flag = 0x01;
	V_ucRelateoff = V_usOffset;												/*������һ�ε��¼�ͷƫ�Ƶ�ַ������д�ָ���*/
	if(Inf_GetRecordData(&V_ucDataBuff[V_usOffset], &V_ResidualLength, CBuyCurr_OADTab, V_Event_Flag) == C_OK)	/*��ȡ����OAD����*/
	{
		V_usOffset += V_ResidualLength;										/*�����ܳ���*/
	}
	InF_Write_Data(C_Msg_Communication, CBuyCurr_FF_Note_1, V_ucDataBuff, V_usOffset, C_W_SafeFlag);			/*д�����¼*/

/*Ǯ������*/
	InF_MoneyToPurchase(V_ulBuyMoney, Flag, C_SafeFlag );
/*д�ָ�*/
	V_ResidualLength = 300 - V_ucRelateoff;
	if(Inf_GetRecordData(&V_ucDataBuff[V_ucRelateoff], &V_ResidualLength, CBuyCurr_OADTab, 0x02)	== C_OK)		/*ȡ��������*/
	{
		V_ucRelateoff += V_ResidualLength;
	}
	InF_Write_Data(C_Msg_Communication, (CBuyCurr_FF_Note_1 + 1), V_ucDataBuff, V_ucRelateoff, C_W_SafeFlag);

	Inf_EventReport_HP(C_BuyCurrEventNo, C_Happen_EventReport);

	return;
}

/***************************************************************************
����ԭ�� 	Comm_IRCertification_Instruction
��������	03-������֤
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	ͨ����������
������ע
***************************************************************************/
void	Comm_IRCertification_Instruction( Str_Comm_645	*pV_645Frame )
{
	uchar8	buf[C_TimerExceed10minLen];
	ushort16	SError;
	uchar8	*pValidData;
	ushort16 V_usDatalen,V_usDataEncode;

	memset( buf, 0, C_TimerExceed10minLen );/*���㱸��*/
/*�жϳ����Ƿ����*/
	if( pV_645Frame->DataLen != (CLen_DI + CLen_OpCode + CL_Auth_CiphertextK2 ) )
	{
		Comm_Response_03_Err(C_SERR_OtherErr, pV_645Frame);
		return;
	}
/*���ð�ȫģ��ӿں��������к�����֤*/
	pValidData = &(pV_645Frame->Data[CData_OtherO_V_645]);
	SError = InF_S_IRCertification_Instruction(pValidData);
	if( SError != C_OK )
	{
		if( SError == C_SERR_ESAM_VF )
		{/*ESAM��֤ʧ�ܣ�200��++*/
			Comm_DealwithSPTVariable(C_SPTNumAdd);
		}
		Comm_Response_03_Err(SError, pV_645Frame);
	/*������֤ʧ�ܽ���������֤��Ч*/
		DealWith_IR_Auth_Timer_645(C_Set_TimerExceed10min, &buf[0]);
	}
	else
	{/*��ȷ��Ӧ�𲢸�ֵ������֤��ʱ��	*/
		Comm_11_03Response_Normal(pV_645Frame, pValidData, 0);

		buf[1] = 0;
		V_usDatalen = 4;
		SError = InF_GetData_ObjectManage(C_IRAuth_Timer, buf, &V_usDatalen, &V_usDataEncode);
		PF_OneDataReversed(buf, buf, V_usDatalen);

		if(SError != C_OK)
		{
			buf[0] = C_IRAuthTime_L;		/*���ݲ���������ݣ���Ĭ��Ϊ30����*/
			buf[1] = C_IRAuthTime_H;
		}
		if(buf[0] == 0)						/*��֤ʱ��Ϊ0���߷�BCD��,Ĭ��*/
		{
			buf[0] = C_IRAuthTime_L;		/*���ݷǷ�,Ĭ��Ϊ30����*/
			buf[1] = C_IRAuthTime_H;
		}
		DealWith_IR_Auth_Timer_645(C_Set_TimerExceed10min, &buf[0]);
	}
	return;
}
/***************************************************************************
����ԭ�� 	Comm_IRCertification_Request
��������	03-������֤����
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	ͨ����������
������ע
***************************************************************************/
void	Comm_IRCertification_Request( Str_Comm_645	*pV_645Frame )
{
	uchar8	buf[C_TimerExceed10minLen];
	ushort16	SError;
	uchar8	ValidDataLen;
	uchar8	*pValidData;

/*�������ú�����֤ʱЧΪ��Ч*/
	memset( buf, 0, C_TimerExceed10minLen );
	DealWith_IR_Auth_Timer_645(C_Set_TimerExceed10min, &buf[0]);

/*������֤�������֤�кι�ϵ?������֤ʱȡ�������֤����С���ҳ���*/
	DealWith_ID_Auth_Timer(C_Set_TimerExceed10min, &buf[0]);

/*�жϳ����Ƿ����*/
	if( pV_645Frame->DataLen != (CL_Auth_Rand1 + CLen_DI + CLen_OpCode ) )
	{
		Comm_Response_03_Err(C_SERR_OtherErr, pV_645Frame);
		return;
	}
	else
	{
		ValidDataLen = CL_Auth_Rand1;
	}

/*���ð�ȫģ��Ľӿں���*/
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
		{/*ESAM��֤ʧ�ܣ�200��++*/
			Comm_DealwithSPTVariable(C_SPTNumAdd);
		}
	}
	return;
}

/***************************************************************************
����ԭ�� 	Comm_Authentication
��������	03-�����֤�����������Ӧ����
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	��
ȫ�ֱ��� 	ͨ�����������������֤ʱЧ
������ע
***************************************************************************/
void	Comm_Authentication( Str_Comm_645 *pV_645Frame )
{
	uchar8	buf[C_TimerExceed10minLen];
	ushort16	SError;
	uchar8	ValidDataLen;
	uchar8	*pValidData;

	/*�������õ�ǰ�����֤��Ч,������һ�α�̼�¼*/
	memset( buf, 0, C_TimerExceed10minLen );
	DealWith_ID_Auth_Timer(C_Set_TimerExceed10min, &buf[0]);
	INF_StopCommProgState();		/*����ʱ������Ϣ�д���*/

	/*�жϳ����Ƿ����*/
	if( pV_645Frame->DataLen != ( C_Authentication_Len + CLen_DI + CLen_OpCode ) )
	{
		Comm_Response_03_Err(C_SERR_OtherErr, pV_645Frame);
		return;
	}
	else
	{
		ValidDataLen = C_Authentication_Len;
	}

/*���ð�ȫģ��ӿں���*/
	pValidData = &(pV_645Frame->Data[CData_OtherO_V_645]);
	SError = InF_S_Authentication(pValidData, &ValidDataLen);
	if( SError != C_OK )
	{
		Comm_Response_03_Err(SError, pV_645Frame);
		if( SError == C_SERR_ESAM_VF )
		{/*ESAM��֤ʧ�ܣ�200��++*/
			Comm_DealwithSPTVariable(C_SPTNumAdd);
		}
		return;
	}
/*�������֤��Чʱ��*/
	memset( buf, 0, C_TimerExceed10minLen );
	PF_CopyDataBytes(&pValidData[C_R_Auth_O_AuthPTime], buf, 2);
	DealWith_ID_Auth_Timer(C_Set_TimerExceed10min, buf);

	ValidDataLen = ValidDataLen - CLen_AuthPTime;
/*������Ӧ��֡*/
	Comm_11_03Response_Normal(pV_645Frame, pValidData, ValidDataLen);
	return;
}

/***************************************************************************
����ԭ�� 	Is_ID_Auth_Ok_ResponseErr
��������	�жϱ������Ƿ���Ȩ�ޡ������������Ƿ���Ҫ�����֤��
				��̿��ء�����״̬Ȩ���жϣ���Ҫ�Ƿ�OK?Err������֯Ӧ��֡
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	C_OK/C_Error
ȫ�ֱ��� 	��
������ע	�������ڸ���������������е��á����ú����
				C_Error������Ҫ�������Ӧ��
				����ȫ�����⣬���������ڳ���ģʽ�¶��ǲ���Ҫ�����֤�ġ�
***************************************************************************/
uchar8 Is_ID_Auth_Ok_ResponseErr( Str_Comm_645 *pV_645Frame )
{
	Str_WrParmTable WrParmTable;

	/*03�����޳���״̬�ͱ�̿��ص�˵��*/
	if(pV_645Frame->C ==0x03)
	{
		switch(pV_645Frame->DI)
		{	/*��������ɲ���Ҫ�����֤*/
			case		CDI_Auth:				/*�����֤*/
			{	/*�ж�����Ǻ���ͨ������������֤û�У������������֤*/
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
			case CDI_IRCReq_645:				/*������֤����*/
			case CDI_IR_ExtAuth_645:			/*������֤*/
			{
				/*������֤��������֤���󣬱����Ǻ���ͨ����*/
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

	/*����������ݻָ������������������Ĵ�������,û����������*/
	if(pV_645Frame->C ==0x1F)
	{
		return(C_OK);
	}

	/*�����ж��Ƿ�Ϊ����ģʽ������ǿ��Բ��������֤*/
	if(JudgeTimerExceed10min(&SI_JTimer_BSOn2500)==C_TimerEnable)
	{
		return(C_OK);		/*�˳�ȥ�ж����롣����ڳ���ģʽ����98��99������*/
							/*û���ж��Ƿ��������֤��Ч�����ܻᵼ��200�ι���*/
	}
	else
	{
		/*���ڳ���ģʽ�����������������*/
		if(pV_645Frame->C == 0x14)	/*645�����ڳ��ⲻ��������2017/12/28 17:27:52*/
		{
			switch(pV_645Frame->DI)
			{
				case CRated_Vol645:				/*���ѹ*/
				case CRated_Curr645:			/*�����*/
				case CMax_Curr645:				/*������*/
				case CActive_Accur_Deg645:		/*�й�׼ȷ�ȵȼ�*/
				case CReactive_Accur_Deg645:	/*�޹�׼ȷ�ȵȼ�*/
				case CMeter_Ac_Const645:		/*����й�����*/
				case CMeter_Re_Const645:		/*������޹�����*/
				case CMeter_Model645:			/*����ͺ�*/
				case CProd_Date645:				/*��������*/
				case CProt_Version_Num:			/*Э��汾��*/
				case CFactory_Softw_Version:	/*��������汾��*/
				case CFactory_Hardw_Version:	/*����Ӳ���汾��*/
				case CFactory_Number:			/*���ұ��*/
				case CSoftw_Record_Number:		/*���������*/
				case 0x43000500:				/*���豸�б�*/
				case CMeter_CommPro:			/*֧�ֹ�Լ�б�*/
				{
					Comm_Response_Set_ReadErr(C_Unauthorized_645, pV_645Frame);
					return(C_Error);
				}break;
				default:
					break;						/*ע��������break������һ���ж�*/
			}
		}

		if(pV_645Frame->C == 0x21)
		{
			return(C_Error);					/*У����������ڳ���ģʽ����*/
		}
	}

	/*�����ж��Ƿ��̿�����Ч����ЧҲ���������֤����Ϊ�¹���*/
	/*��û�б�̿��أ����Դ˶�����û������ġ�*/
	/*���仰�������֤���ˣ��б�̿��أ�Ҳ����04������*/
	if(JudgeTimerExceed10min(&ProgKey_Timer) == C_TimerEnable)
	{
		return(C_OK);
	}

	/*�����֤��Ч�ڼ䣬ʣ�������������	2017/12/28 17:28:50    645����ж������֤��Ч*/
	if(JudgeTimerExceed10min(&ID_AuthT) == C_TimerEnable)
	{
		return(C_OK);
	}

	/*������Ȳ��ǳ��ڡ�Ҳ�ޱ�̿��غ������֤*/
	/*��Ҫ�ж���������*/
	switch(pV_645Frame->C)
	{
		/*�����������Ҫ�����֤*/
		case 0x1E:			/*�����������Ӧ��OK���ڽ��������д���ȫ��*/
		case 0x11:			/*��*/
		case 0x12:			/*������֡*/
		case 0x18:			/*��������*/
		case 0x13:			/*��ͨ�ŵ�ַ*/
		case 0x08:			/*�㲥Уʱ*/
		case 0x17:			/*����ͨ������*/
		case 0x20:			/*У�������*/
		case 0x1C:			/*��������������������жϣ���ΪӦ��2�ֽ�/1�ֽ�δ��*/
		{
			return(C_OK);
		}break;
		/*д���������Ҫ�����֤��*/
		case 0x14:			/*д*/
		{
			if(Is_ParmType_3(pV_645Frame->DI,&WrParmTable,pV_645Frame->ChannelNo) == C_OK)
			{
				return(C_OK);	/*III�����ݣ�����ͨѶ���߼��ź�ǿ��ָʾ;���Զ���IP�ֶεȱ�ʶ��*/
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
			return(C_Error);	/*���������������ȶ���Ҫ�����֤*/
		}break;
	}
}

/***************************************************************************
����ԭ�� 	Is_SPT_NotOver_ResponseErr
��������	�ж������Ƿ���Ҫ��200�γ���?����Ҫ���жϣ�
				�������������Ӧ��
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	C_OK/C_Error
ȫ�ֱ��� 	��
������ע	201407����������14�淶������Ҫ���բ(��բ����)
				���Բ���02/04���룬���ùܱ�̿��ء�02/04������������������
				1�������������������������������жϺ�����ִ��
				2��1C��������ڸ��������ж�200�ι���
***************************************************************************/
uchar8	Is_SPT_NotOver_ResponseErr(Str_Comm_645	*pV_645Frame)
{
	Str_WrParmTable	WrParmTable;
/*03�����޳���״̬��˵��*/
	if(pV_645Frame->C ==0x03)
	{
		switch(pV_645Frame->DI)
		{/*���������Ҫ�жϵ��ܱ����״̬*/
			case		CDI_Auth:			/*�����֤*/
			case		CDI_IRCReq:			/*������֤����*/
			case		CDI_IR_ExtAuth:		/*������֤*/
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
	/*����������ݻָ������������������Ĵ�������,û����������*/
	if(pV_645Frame->C == 0x1F)
	{
		return(C_OK);
	}

/*�����ж��Ƿ�Ϊ����ģʽ������ǿ��Բ���200�Σ�����02���ܼ���*/
	if( JudgeTimerExceed10min(&SI_JTimer_BSOn2500) == C_TimerEnable )
	{
		return(C_OK);			/*�˳�ȥ�ж����롣����ڳ���ģʽ����98��99������*/
								/*û���ж��Ƿ���200�ι��𣬻ᵼ�¸ù�����Ч200�ι���*/
	}
/*�����ж��Ƿ��̿�����Ч����ЧҲ����200�Ρ�*/
	if(JudgeTimerExceed10min(&ProgKey_Timer) == C_TimerEnable)
	{/*��̿�����Ч����ζ�ж����룬��ʱ�������жϺ������ж����������*/
	/*�����̿�����Ч���ֲ���98.99��������200�ι��𣬴�ʱ��������*/
	/*ֱ�ӷ���OK���������⡣����Ϊ�¹�����û�б�̿��أ�����û��ϵ*/
		return(C_OK);
	}
/*200��û�е����������������޸��������������������*/
	if(Comm_DealwithSPTVariable(C_JudgeSPTVariable) != C_SPT_Num_Over)
	{
		return(C_OK);
	}

/*�������200�ε��ˣ�����Ҫ�ж����������Ƿ���Ҫ�ж�200�ι���*/
	switch(pV_645Frame->C)
	{
	/*�����������Ҫ�����֤*/
		case		0x11:			/*��*/
		case		0x12:			/*������֡*/
		case		0x15:			/*дͨѶ��ַ*/
		case		0x18:			/*��������*/
		case		0x13:			/*��ͨ�ŵ�ַ*/
		case		0x08:			/*�㲥Уʱ*/
		case		0x1C:			/*���ɿ��ؿ���������ɿ��ؿ��������ڸ��������ж�*/
									/*200�ι����Ƿ���Ч���˴�ֱ���˳���*/
		case		0x1E:			/*���ڲ���Ҫ�жϹ���*/
			return(C_OK);
	/*д���������Ҫ�����֤��*/
		case		0x14:			/*д*/
		{
			if(Is_ParmType_3(pV_645Frame->DI, &WrParmTable, pV_645Frame->ChannelNo) == C_OK)
			{/*III�����ݣ�����ͨѶ���߼��ź�ǿ��ָʾ;���Զ����ʶ��*/
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
			return(C_Error);		/*���������������ȶ���Ҫ�ж�200�ι���*/
	}

}
/***************************************************************************
����ԭ�� 	If_AddressFlagErr_Response
��������	�ж�ͨ�ŵ�ַ��־�Ƿ���ʣ���������Ӧ�����
�������	pV_645Frame	->C					:645������
				pV_645Frame->AddressFlag			:ͨ�ŵ�ַ��־
							C_MeterAddress/C_Broadcast/C_Condense_AA_All/C_Condense_AA
������� 	��
���ز���	C_OK/C_Error
ȫ�ֱ��� 	ͨ����������
������ע	����жϱ�־�����ʣ���֯��ͨ��Ӧ��֡���÷�����Ϣ��־
***************************************************************************/
uchar8	If_AddressFlagOK_ResponseErr(Str_Comm_645 *pV_645Frame)
{
	Str_WrParmTable WrParmTable;
/*�͹㲥��ַ��ص�2������:�㲥Уʱ��㲥���ἰ�๦�����*/
/*�㽭�㲥УʱҪ���Ե�*/
	if(pV_645Frame->C == 0x08)
	{
		return(C_OK);
	}
	else if(pV_645Frame->C ==0x16)
	{
		if( ( pV_645Frame->AddressFlag == C_Broadcast ) || ( pV_645Frame->AddressFlag == C_MeterAddress ) )
		{/*����֧�ֹ㲥��ȫ���*/
			return(C_OK);
		}
		else
		{
			Comm_Response_Set_ReadErr(C_Unauthorized, pV_645Frame);
			return(C_Error);
		}
	}
	else if(pV_645Frame->C ==0x1D)			/*���ƶ๦�����*/
	{
		return(C_OK);						/*�๦�����ֻҪ�����ȷ�Ϳ��ԣ��Ա�Ÿ�ʽ��Ҫ��*/
	}
	else if( ( pV_645Frame->C ==0x11 ) && ( pV_645Frame->DataLen == 0x09 )
		   && ( pV_645Frame->DI == CLCD_View ) )
	{
		return(C_OK);
	}
	else
	{
		if(pV_645Frame->AddressFlag == C_Broadcast)
		{/*������������й㲥��ַ*/
			return(C_Error);
		}
	}
/*���ݿ�����ȥ�жϵ�ַ�Ƿ�Ϸ���*/
	switch(pV_645Frame->C)
	{
	/*����������֧�ֳ��㲥����֮�����б��ַ��ʽ*/
		case		0x11:			/*������*/
		case		0x12:			/*������֡*/
		case		0x1E:			/*��������*/
		case		0x20:			/*��У�����*/
		case		0x21:			/*дУ������*/
			return(C_OK);
	/*�����������ȫ���*/
		case		0x14:			/*д*/
		case		0x1A:			/*�������*/
		case		0x1B:			/*�¼���¼����*/
		case		0x19:			/*��������*/
		case		0x17:			/*�޸Ĳ�����*/
		case		0x18:			/*�޸�����*/
		case		0x1C:			/*��������*/
		case		0x1F:			/*����������ݻָ������������������Ĵ�������	*/
		{
			if(pV_645Frame->AddressFlag != C_MeterAddress)
			{/*20141023,��Ϊ����ģ�����ÿ��ܲ���ȫAA�����������������ȫAA����*/
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
	/*�����������ȫAA,������Ӧ��*/
		case		0x13:			/*����ͨ�ŵ�ַ*/
		case		0x15:			/*���ͨ�ŵ�ַ*/
			if( pV_645Frame->AddressFlag == C_Condense_AA_All )
			{
				return(C_OK);
			}
			else
			{						/*�����ַ����ȫAAҲ��Ӧ��*/
				return(C_Error);
			}
									/*03���ƱȽ����⣬����һЩ������֧����λ*/
		case		0x03:			/*��ȫ�����ж�����֧����λ����������ֻ֧��ȫ���*/
			switch(pV_645Frame->DI)
				{
					case		CDI_GetData:			/*���ݻس�*/
					case		CDI_GetData01:
					case		CDI_GetStatus:			/*״̬��ѯ*/
					case		CDI_GetStatus01:
					case		CDI_CMPSoft:			/*����ȶ�*/
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

		default:					/*���������Ӧ��ֱ���˳�.*/
			return(C_Error);
	}
}
/***************************************************************************
����ԭ�� 	Is_IR_Comm_ResponseErr
��������	�жϺ���ͨ���Ƿ�����,����������֯Ӧ��
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	C_OK/C_Error
ȫ�ֱ��� 	��
������ע	�ж�����Ǻ���ͨ�ſڹ�����ͨ�ţ�����Ҫ������֤��
				����ֻ�����֧�ֶ���š�ͨ�ŵ�ַ�������š�
				��ǰ���ڡ���ǰʱ�䡢��ǰ���ܡ���ǰʣ���
				������֤��ѯ���������Ϣ�����������
				������Ϣ�����������ã�
***************************************************************************/
uchar8		Is_IR_Comm_ResponseErr(Str_Comm_645	*pV_645Frame)
{
	if(pV_645Frame->ChannelNo != C_IR)
	{
		return(C_OK);							/*���Ǻ���ڽ��������ܺ�����֤*/
	}
	if(JudgeTimerExceed10min(&IR_AuthT) == C_TimerEnable)
	{
		return(C_OK);							/*������֤��Ч*/
	}

/*������֤��Ч���ж��Ƿ�������ͨ�ŵ�����*/
	/*���Ӽ�����������*/
	if(pV_645Frame->C == 0x11)					/*11��ȡ����*/
	{
		if( ( ( ( pV_645Frame->DI&0xFF000000 ) == 0 ) && ( ( pV_645Frame->DI & 0x000000FF ) == 0 ) )
		 || ( pV_645Frame->DI == COverDraft_Hex_Cent ) )
		{/*��ǰ���������ʣ���͸֧���*/
			return(C_OK);
		}
		switch(pV_645Frame->DI)
		{
			case		CMeter_Num:				/*���*/
			case		CComm_Address:			/*ͨ�ŵ�ַ*/
			case		CSoftw_Record_Number:	/*������*/
			case		CDate_Week:				/*���ڼ�����*/
			case		CTime:					/*ʱ��*/
			case		CDate_Time:				/*��������-ʱ��*/
				return(C_OK);
			default:
				Comm_Response_Set_ReadErr(C_Unauthorized, pV_645Frame);
				return(C_Error);				/*�������֧�ֶ�*/
		}
	}
	else if(pV_645Frame->C == 0x03)				/*��ȫ����*/
	{
		switch(pV_645Frame->DI)
		{
			case		CDI_IRCReq:				/*������֤��������*/
			case		CDI_IR_ExtAuth:			/*������֤����*/
				return(C_OK);
			default:
				Comm_Response_03_Err(C_SERR_OtherErr, pV_645Frame);
				return(C_Error);				/*�������֧�ֶ�*/
		}
	}
	else if(pV_645Frame->C == 0x13)				/*�㲥��ͨ�ŵ�ַҲ�Ǳ������*/
	{
		return(C_OK);
	}
	else if( ( pV_645Frame->C == 0x1C ) && ( pV_645Frame->PowerFlag == C_PowerOn ) )
	{/*02��04��բ������Ǻ�����֤*/
		return(C_OK);							/*������֤�˳�����������������жϣ���ΪӦ��2�ֽ�1�ֽ�δ��*/
	}
	else if( ( pV_645Frame->C == 0x1F ) && ( pV_645Frame->PowerFlag == C_PowerOn ) )
	{/*����������ݻָ������������������Ĵ�������	*/
		return(C_OK);
	}
	else
	{
		if(pV_645Frame->PowerFlag == C_PowerOn)
		{/*�е磬�޺�����֤����֧������Ӧ�����������Ӧ��*/
			Comm_Response_Set_ReadErr(C_Unauthorized, pV_645Frame);
		}
		return(C_Error);
	}
}

/***************************************************************************
����ԭ�� 	Is_IR_Comm_ResponseErr_645
��������	�жϺ���ͨ���Ƿ�����,����������֯Ӧ��
�������	*pV_645Frame				:���յ�������֡
������� 	��
���ز���	C_OK/C_Error
ȫ�ֱ��� 	��
������ע	�ж�����Ǻ���ͨ�ſڹ�����ͨ�ţ�����Ҫ������֤��
				����ֻ�����֧�ֶ���š�ͨ�ŵ�ַ�������š�
				��ǰ���ڡ���ǰʱ�䡢��ǰ���ܡ���ǰʣ���
				������֤��ѯ���������Ϣ�����������
				������Ϣ�����������ã�
***************************************************************************/
uchar8		Is_IR_Comm_ResponseErr_645(Str_Comm_645	*pV_645Frame)
{
	if(pV_645Frame->ChannelNo != C_IR)
	{
		return(C_OK);								/*���Ǻ���ڽ��������ܺ�����֤*/
	}
	if(JudgeTimerExceed10min(&IR_AuthT_645) == C_TimerEnable)
	{
		return(C_OK);								/*������֤��Ч*/
	}

/*������֤��Ч���ж��Ƿ�������ͨ�ŵ�����*/
	/*���Ӽ�����������*/
	if(pV_645Frame->C == 0x11)						/*11��ȡ����*/
	{
		if( ( ( ( pV_645Frame->DI&0xFF000000 ) == 0 ) && ( ( pV_645Frame->DI & 0x000000FF ) == 0 ) )
		 || ( pV_645Frame->DI == COverDraft_Hex_Cent ) )
		{/*��ǰ���������ʣ���͸֧���*/
			return(C_OK);
		}
		switch(pV_645Frame->DI)
		{
			case		CMeter_Num_645:				/*���*/
			case		CComm_Address_645:			/*ͨ�ŵ�ַ*/
			case		CSoftw_Record_Number_645:	/*������*/
			case		CDate_Week:					/*���ڼ�����*/
			case		CTime:						/*ʱ��*/
			case		CDate_Week_Time_645:		/*��������-ʱ��*/
				return(C_OK);
			default:
				Comm_Response_Set_ReadErr(C_Unauthorized_645, pV_645Frame);
				return(C_Error);					/*�������֧�ֶ�*/
		}
	}
	else if(pV_645Frame->C == 0x03)					/*��ȫ����*/
	{
		switch(pV_645Frame->DI)
		{
			case		CDI_IRCReq_645:				/*������֤��������*/
			case		CDI_IR_ExtAuth_645:			/*������֤����*/
				return(C_OK);
			default:
				Comm_Response_03_Err(C_SERR_OtherErr, pV_645Frame);
				return(C_Error);					/*�������֧�ֶ�*/
		}
	}
	else if(pV_645Frame->C == 0x13)					/*�㲥��ͨ�ŵ�ַҲ�Ǳ�����ġ�*/
	{
		return(C_OK);
	}
	else if( ( pV_645Frame->C == 0x1C ) && ( pV_645Frame->PowerFlag == C_PowerOn ) )
	{/*02��04��բ������Ǻ�����֤*/
		return(C_OK);								/*������֤�˳�����������������жϣ���ΪӦ��2�ֽ�1�ֽ�δ��*/
	}
	else if( ( pV_645Frame->C == 0x1F ) && ( pV_645Frame->PowerFlag == C_PowerOn ) )
	{/*����������ݻָ������������������Ĵ�������	*/
		return(C_OK);
	}
	else
	{
		if(pV_645Frame->PowerFlag == C_PowerOn)
		{/*�е磬�޺�����֤����֧������Ӧ�����������Ӧ��*/
			Comm_Response_Set_ReadErr(C_Unauthorized_645, pV_645Frame);
		}
		return(C_Error);
	}
}

/***************************************************************************
����ԭ�� 	CommMSg_StartTxd
��������	����CS����16�����Ӧ��ʱ������������
�������	CommNo				:ͨ����
������� 	��
���ز���	��
ȫ�ֱ��� 	ͨ����������
������ע	�ڵ����������֮ǰ��ͨ����������ȷ��
				��CS��16֮���������ݶ����ú�
***************************************************************************/
void		CommMSg_StartTxd(uchar8 	CommNo)
{
	uchar8	CS;
	uchar8	i;
	Str_Comm_Parm 	*pStr_Comm_Parm_Address;

	pStr_Comm_Parm_Address = Get_Str_Comm_Parm_Pointer(CommNo);
	if(pStr_Comm_Parm_Address == C_NULL)
	{
		return;		/*ͨ������ʵ�ʲ����ܡ������ˣ�Ҳ�����ͣ�ֱ���˳���*/
	}

	CommOffset = 0;
	CommRecFlag645 = 0;
	CommOTimer = 0;

	if( ( CommLen645 < ( C_Comm_FixedTxLen - 2 ) ) || ( CommLen645 > ( C_Comm_Buf_MaxLen - 2 ) ) )
	{	/*ʵ�����ǲ����ܵġ�*/
		InF_InitComm(CommNo);
		Comm_ParseInit();
		return;
	}

/*������+0x33����*/
	for( i = 0; i < CommBuff[C_L_OFS_ForTx]; i++ )
	{
		CommBuff[C_Data_OFS_ForTx + i] = CommBuff[C_Data_OFS_ForTx + i] + 0x33;
	}

/*����CS����CS��16����������*/
	CS = 0;
	for( i = 0; i < ( CommLen645 - 4 ); i++ )		/*CommLen������4��FE�ĳ��ȣ�Ӧ�ÿ۳�*/
	{
		CS = CS + CommBuff[C_68_1_OFS_ForTx + i];
	}
	CommBuff[C_68_1_OFS_ForTx + i] = CS;
	CommLen645++;
	i++;
	CommBuff[C_68_1_OFS_ForTx + i] = 0x16;
	CommLen645++;
/*��������*/
 	if((Inf_Comm_REPORTFlag() != C_ReportNULL))
 	{
		return;
 	}
	InF_CommUart_TxdDataForDispatch(CommNo, CommBuff[CommOffset], C_NoActiveReportFlag);
	CommOffset++;
}

/***************************************************************************
����ԭ�� 	Comm_500ms_Execute
��������	���ͨ�Ŷ�ʱ��Ϣ�Ĵ���
�������	PowerFlag			:��������ĵ�Դ��־
								C_PowerOn��ʾ�е�״̬��
								C_PowerFalling��ʾ����������ر���̣�
								C_PowerOff��ʾ���ڵ���״̬��C_PowerRising��ʾ����������ر����
������� 	��
���ز���	��
ȫ�ֱ��� 	SV_Comm_Parse/SV_Com_Parse_Local/
				ͨ�����Str_Comm_Parm/Str_Comm_NxtFrame
������ע
***************************************************************************/
void	Comm_500ms_Execute(uchar8		PowerFlag)
{
	uchar8	buf[C_TimerExceed10minLen];
	Str_Comm_Parm 	*pStr_Comm_Parm_Address;

	if (PowerFlag == C_PowerOn )
	{
		/*���ȴ������ʱ����10min��ʱ��*/
		DealWith_IR_Auth_Timer(C_Dec_TimerExceed10min, buf);
		DealWith_ID_Auth_T_Timer(C_Dec_TimerExceed10min, buf);
		DealWith_IR_Auth_Timer_645(C_Dec_TimerExceed10min, buf);
		if( Com_Conect.ConectOverTime == 0 )
		{
			DealWith_ID_Auth_Timer(C_Dec_TimerExceed10min, buf);
		}

		/*��IJ��ʱ������*/
		SI_JBaseTimer_2500++;
		if( SI_JBaseTimer_2500 >= C_SI_JBTimer_2500 )
		{
			SI_JBaseTimer_2500 = 0;
			DealWith_SI_J_Timer(C_Dec_TimerExceed10min, buf);
		}
		/*�Ƿ���б���¼���¼���ж�*/
		if( ( JudgeTimerExceed10min(&ID_AuthT) == C_TimerDisable )
		 && ( InF_ConectTimer_DealNoTimer() == C_TimerDisable ) )
		{
		/*2����ʱ������Ч�����б���ܼ�¼д����д�����л��ж��Ƿ�*/
		/*ʵ��������д��û���ǲ���д�ģ��������û������*/
			INF_StopCommProgState();
		}
		/*����ͨ�ö�ʱ��*/
		SV_Comm_Parse.Timer_1min++;
		if( SV_Comm_Parse.Timer_1min >= C_Timer_1min )
		{/*1min��*/
			SV_Comm_Parse.Timer_1min = 0;				/*���¶�ʱ*/
			InF_UpdateAccountStateInMeterStatus3();
		}

		/*ͨ���Ķ�ʱ������*/
		/*RS485_1ͨ��*/
		pStr_Comm_Parm_Address = &SV_RS485_1_Comm_Parm;
		CommOTimer++;
		if( CommOTimer >= C_Comm_OTime )
		{
			CommOTimer = 0;
		}
		/*RS485_2ͨ��*/
		pStr_Comm_Parm_Address = &SV_RS485_2_Comm_Parm;
		CommOTimer++;
		if( CommOTimer >= C_Comm_OTime )
		{
			CommOTimer = 0;
		}
		/*����ͨ��*/
		pStr_Comm_Parm_Address = &SV_IR_Comm_Parm;
		CommOTimer++;
		if( CommOTimer >= C_Comm_OTime )
		{
			CommOTimer = 0;
		}
		/*ģ��ͨ��*/
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
		/*ģ���Դ*/
		DealWith_RstModule(C_Flag_Err);				/*�����е�����£�����ģ�鸴λ����*/

		/*�������ϱ���ʱ:*/
		if( SV_HaveReportState.Timer != 0 )
		{
			SV_HaveReportState.Timer--;
			if( SV_HaveReportState.Timer == 0 )
			{
                SF_RstHaveReportState_645To698(&SV_HaveReportState.State[0]);	/*��698�����ϱ���698����645����*/
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
			InF_ConectTimer_Deal();					/*Ӧ������ʱ��*/
		}
	}
	InF_Check_Comm_Address();						/*��ʱ500mscheckͨ�ŵ�ַRAM�е����ݣ����Դ�EE��ȡ*/
	InF_Get_Comm_Address(SV_Comm_Address, 0x00);	/*��ȡͨ�ŵ�ַ��ͨ���Զ��建��*/

	/*645Э�飬ģ��80s��д�ź�ǿ�ȣ��ź�ǿ�Ȳ�����ʾ.
	698Э�飬��˼��4Gģ��ÿ15����дһ���ź�ǿ��*/
	SF_Comm_GPRSDisplay();


/*���¶����������е�û�е磬��Ҫ��һ��*/
	Comm_DealwithSPTVariable(C_JudgeSPTVariable);	/*�ж���û�й���㡣*/
	Comm_ParseInit();
}
/***************************************************************************
����ԭ�� 	InF_LowPower_IR_Inti
��������	��ɵ͹�����ͨ���к�����֤�������֤��ر�־\��ʱ���ȵ�����
�������	��
������� 	��
���ز���	��
ȫ�ֱ��� 	������֤��Ч��ʱ������\�������״̬��3�еĺ�����֤��Ч��־��д0
			���ݲ��������֤��Чʱ��\�������״̬��3�������֤��Ч��־����
������ע	���ȼ�⵽����,����͹���ǰ���øú���
***************************************************************************/
void InF_LowPower_IR_Inti(void)
{
	uchar8 V_Buf2[C_TimerExceed10minLen];

	memset(V_Buf2, 0, C_TimerExceed10minLen);
	DealWith_IR_Auth_Timer(C_Set_TimerExceed10min, V_Buf2);			/*������֤��Ч*/
	DealWith_ID_Auth_Timer(C_Set_TimerExceed10min, V_Buf2);			/*�����֤��Ч*/
	DealWith_ID_Auth_T_Timer(C_Set_TimerExceed10min, V_Buf2);		/*�ն������֤��Ч*/
	DealWith_IR_Auth_Timer_645(C_Set_TimerExceed10min, V_Buf2);		/*������֤��Ч*/
}
/*********************************************************************************
����ԭ��	SF_Comm_GPRSDisplay
��������	���GPRS�ź�ǿ�ȶ�ʱ80sû�����ù�����ʵ�Ĺ���
�������	��
������� 	��
���ز���	��
ȫ�ֱ��� 	698Э�飬GPRS�ź�ǿ�����ü����ʱ��
������ע	500ms����
			������˼��4Gģ��ÿ15����дһ���ź�ǿ�ȣ���ģ��24Сʱ��ͨ�ŻḴλģ�顣
			���698Э��˺�������ʹ�á�
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
			SetGPRSSignal(&V_ucBuffer[0]);	/*����ʾGPRS�ź�ǿ��*/
		}
	}
}

/***************************************************************************
����ԭ�� 	Clear_BDSC_RecentClock
��������	����㲥Уʱʱ��
�������	��
������� 	��
���ز���	��
ȫ�ֱ��� 	SV_Comm_Parse.BDSC_RecentClock
������ע	�޸�����\����������
***************************************************************************/
void Clear_BDSC_RecentClock(void)
{
	memset(&SV_Comm_Parse.BDSC_RecentClock[0], 0, 7);
}

/***************************************************************************
����ԭ�� 	InF_JudgeJTTimer
��������	�жϵ�ǰ��IJ�Ƿ���Ч
�������	��
������� 	��
���ز���	C_OK��Ч,C_Error��Ч
ȫ�ֱ���
������ע	������ר�����ڳ���״̬�£�δУ��ʱ���忨����
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
	CRec_Meter_Hp_T_1,		    /*��1��У��ʱ��*/
	CRec_Meter_Bef1_Data_1,	    /*��1��1��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_2,	    /*��1��2��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_3,	    /*��1��3��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_4,	    /*��1��4��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_5,	    /*��1��5��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_6,	    /*��1��6��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_7,	    /*��1��7��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_8,	    /*��1��8��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_9,	    /*��1��9��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_10, 	/*��1��10��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_11, 	/*��1��11��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_12, 	/*��1��12��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_13, 	/*��1��13��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_14, 	/*��1��14��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_15, 	/*��1��15��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_16, 	/*��1��16��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_17, 	/*��1��17��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_18, 	/*��1��18��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_19, 	/*��1��19��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_20, 	/*��1��20��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_21, 	/*��1��21��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_22, 	/*��1��22��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_23, 	/*��1��23��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_24, 	/*��1��24��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_25, 	/*��1��25��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_26, 	/*��1��26��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_27, 	/*��1��27��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_28, 	/*��1��28��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_29, 	/*��1��29��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_30, 	/*��1��30��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_31, 	/*��1��31��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_32, 	/*��1��32��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_33, 	/*��1��33��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_34, 	/*��1��34��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_35, 	/*��1��35��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_36, 	/*��1��36��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_37, 	/*��1��37��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_38, 	/*��1��38��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_39, 	/*��1��39��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_40, 	/*��1��40��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_41, 	/*��1��41��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_42, 	/*��1��42��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_43, 	/*��1��43��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_44, 	/*��1��44��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_45, 	/*��1��45��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_46, 	/*��1��46��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_47, 	/*��1��47��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_48, 	/*��1��48��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_49, 	/*��1��49��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_50, 	/*��1��50��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_51, 	/*��1��51��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_52, 	/*��1��52��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_53, 	/*��1��53��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_54, 	/*��1��54��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_55, 	/*��1��55��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_56, 	/*��1��56��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_57, 	/*��1��57��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_58, 	/*��1��58��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_59, 	/*��1��59��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_60, 	/*��1��60��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_61, 	/*��1��61��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_62, 	/*��1��62��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_63, 	/*��1��63��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_64, 	/*��1��64��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_65, 	/*��1��65��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_66, 	/*��1��66��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_67, 	/*��1��67��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_68, 	/*��1��68��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_69, 	/*��1��69��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_70, 	/*��1��70��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_71, 	/*��1��71��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_72, 	/*��1��72��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_73, 	/*��1��73��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_74, 	/*��1��74��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_75, 	/*��1��75��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_76, 	/*��1��76��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_77, 	/*��1��77��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_78, 	/*��1��78��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_79, 	/*��1��79��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_80, 	/*��1��80��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_81, 	/*��1��81��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_82, 	/*��1��82��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_83, 	/*��1��83��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_84, 	/*��1��84��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_85, 	/*��1��85��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_86, 	/*��1��86��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_87, 	/*��1��87��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_88, 	/*��1��88��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_89, 	/*��1��89��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_90, 	/*��1��90��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_91, 	/*��1��91��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_92, 	/*��1��92��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_93, 	/*��1��93��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_94, 	/*��1��94��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_95, 	/*��1��95��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_96, 	/*��1��96��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_97, 	/*��1��97��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_98, 	/*��1��98��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_99, 	/*��1��99��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_100,   /*��1��100��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_101,   /*��1��101��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_102,   /*��1��102��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_103,   /*��1��103��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_104,   /*��1��104��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_105,   /*��1��105��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_106,   /*��1��106��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_107,   /*��1��107��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_108,   /*��1��108��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_109,   /*��1��109��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_110,   /*��1��110��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_111,   /*��1��111��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_112,   /*��1��112��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_113,   /*��1��113��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_114,   /*��1��114��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_115,   /*��1��115��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_116,   /*��1��116��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_117,   /*��1��117��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_118,   /*��1��118��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_119,   /*��1��119��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_120,   /*��1��120��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_121,   /*��1��121��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_122,   /*��1��122��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_123,   /*��1��123��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_124,   /*��1��124��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_125,   /*��1��125��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_126,   /*��1��126��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_127,   /*��1��127��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_128,   /*��1��128��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_129,   /*��1��129��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_130,   /*��1��130��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_131,   /*��1��131��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_132,   /*��1��132��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_133,   /*��1��133��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_134,   /*��1��134��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_135,   /*��1��135��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_136,   /*��1��136��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_137,   /*��1��137��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_138,   /*��1��138��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_139,   /*��1��139��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_140,   /*��1��140��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_141,   /*��1��141��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_142,   /*��1��142��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_143,   /*��1��143��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_144,   /*��1��144��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_145,   /*��1��145��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_146,   /*��1��146��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_147,   /*��1��147��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_148,   /*��1��148��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_149,   /*��1��149��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_150,   /*��1��150��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_151,   /*��1��151��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_152,   /*��1��152��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_153,   /*��1��153��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_154,   /*��1��154��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_155,   /*��1��155��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_156,   /*��1��156��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_157,   /*��1��157��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_158,   /*��1��158��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_159,   /*��1��159��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_160,   /*��1��160��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_161,   /*��1��161��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_162,   /*��1��162��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_163,   /*��1��163��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_164,   /*��1��164��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_165,   /*��1��165��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_166,   /*��1��166��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_167,   /*��1��167��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_168,   /*��1��168��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_169,   /*��1��169��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_170,   /*��1��170��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_171,   /*��1��171��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_172,   /*��1��172��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_173,   /*��1��173��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_174,   /*��1��174��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_175,   /*��1��175��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_176,   /*��1��176��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_177,   /*��1��177��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_178,   /*��1��178��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_179,   /*��1��179��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_180,   /*��1��180��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_181,   /*��1��181��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_182,   /*��1��182��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_183,   /*��1��183��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_184,   /*��1��184��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_185,   /*��1��185��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_186,   /*��1��186��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_187,   /*��1��187��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_188,   /*��1��188��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_189,   /*��1��189��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_190,   /*��1��190��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_191,   /*��1��191��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_192,   /*��1��192��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_193,   /*��1��193��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_194,   /*��1��194��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_195,   /*��1��195��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_196,   /*��1��196��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_197,   /*��1��197��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_198,   /*��1��198��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_199,   /*��1��199��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_200,   /*��1��200��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_201,   /*��1��201��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_202,   /*��1��202��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_203,   /*��1��203��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_204,   /*��1��204��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_205,   /*��1��205��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_206,   /*��1��206��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_207,   /*��1��207��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_208,   /*��1��208��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_209,   /*��1��209��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_210,   /*��1��210��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_211,   /*��1��211��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_212,   /*��1��212��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_213,   /*��1��213��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_214,   /*��1��214��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_215,   /*��1��215��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_216,   /*��1��216��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_217,   /*��1��217��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_218,   /*��1��218��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_219,   /*��1��219��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_220,   /*��1��220��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_221,   /*��1��221��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_222,   /*��1��222��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_223,   /*��1��223��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_224,   /*��1��224��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_225,   /*��1��225��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_226,   /*��1��226��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_227,   /*��1��227��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_228,   /*��1��228��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_229,   /*��1��229��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_230,   /*��1��230��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_231,   /*��1��231��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_232,   /*��1��232��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_233,   /*��1��233��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_234,   /*��1��234��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_235,   /*��1��235��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_236,   /*��1��236��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_237,   /*��1��237��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_238,   /*��1��238��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_239,   /*��1��239��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_240,   /*��1��240��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_241,   /*��1��241��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_242,   /*��1��242��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_243,   /*��1��243��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_244,   /*��1��244��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_245,   /*��1��245��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_246,   /*��1��246��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_247,   /*��1��247��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_248,   /*��1��248��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_249,   /*��1��249��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_250,   /*��1��250��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_251,   /*��1��251��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_252,   /*��1��252��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_253,   /*��1��253��У�����У��ǰ����*/
	CRec_Meter_Bef1_Data_254	/*��1��254��У�����У��ǰ����*/
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
	CT_Free_Time_1, 					/*��1�ζ�ʱ����ʱ��*/
	CT_Free_Pos_Ac_En_1,				/*��1�ζ�ʱ���������й���������*/
	CT_Free_Rev_Ac_En_1,				/*��1�ζ�ʱ���ᷴ���й���������*/
	CT_Free_Com_Re1_En_1,				/*��1�ζ�ʱ��������޹�1����*/
	CT_Free_Com_Re2_En_1,
	CT_Free_Qua1_Re_En_1,				/*��1�ζ�ʱ���������޵�������*/
	CT_Free_Qua2_Re_En_1,
	CT_Free_Qua3_Re_En_1,
	CT_Free_Qua4_Re_En_1,
	CT_Free_Pos_Ac_De_1,				/*��1�ζ�ʱ����������������*/
	CT_Free_Rev_Ac_De_1,
	CT_Free_Variable_1					/*��1�ζ�ʱ�����������*/
};

const	ulong32 	TB_HFreezeSubDI[C_HFreezeSubDILen] =
{
	CT_Free_Time_1, 					/*��1�ζ�ʱ����ʱ��*/
	CT_Free_Pos_Ac_En_1,				/*��1�ζ�ʱ���������й���������*/
	CT_Free_Rev_Ac_En_1					/*��1�ζ�ʱ���ᷴ���й���������*/
};


const	ulong32	TB_MeterStatus[CLen_TB_MeterStatus] =
{CMeter_Work_State1,CMeter_Work_State2,CMeter_Work_State3,CMeter_Work_State4,
CMeter_Work_State5,CMeter_Work_State6,CMeter_Work_State7,CKey_State};
const	Str_TBNxtFrame	TB_NxtFrame[C_TBNxtFrameNum]=
{
{CH_Free_FF_1				,(ulong32*)TB_HFreezeSubDI		,C_HFreezeSubDILen			,	C_Freeze_Method 	},	/*���㶳��*/
{CD_Free_FF_1				,(ulong32*)TB_FreezeSubDI		,C_FreezeSubDILen			,	C_Freeze_Method 	},	/*�ն���*/
{CDe_Clear_Note_1_645		,(ulong32*)TB_DCLREvent_SubDI	,C_DCLREvent_SubDILen		,	C_Prog_SubDI_LBit4	},	/*����,698����645�޸�Ϊ645��ʶ*/
{CProgPT_CurrentPart_Note_1	,(ulong32*)TB_ProgPT_SubDI		,C_ProgPT_SubDILen			,	C_Prog_SubDI_LBit4	},	/*ʱ�α�*/
{CRec_Meter_FF_Data_1		,(ulong32*)TB_CalMReg_SubDI		,(C_MeterICDataNum_T + 1)	,	C_Prog_SubDI_LBit4	},	/*У���϶�*/
{CLossA_Curr_FF_FF			,(ulong32*)TB_LossA_Curr_SubDI	,C_LossA_Curr_SubDILen		,	C_Event_Method		},	/*A��ʧ��*/
{CLossB_Curr_FF_FF			,(ulong32*)TB_LossB_Curr_SubDI	,C_LossB_Curr_SubDILen		,	C_Event_Method		},	/*B��ʧ��*/
{CLossC_Curr_FF_FF			,(ulong32*)TB_LossC_Curr_SubDI	,C_LossC_Curr_SubDILen		,	C_Event_Method		},	/*C��ʧ��*/
{COverA_Curr_FF_FF			,(ulong32*)TB_OverA_Curr_SubDI	,C_OverA_Curr_SubDILen		,	C_Event_Method		},	/*A�����*/
{COverB_Curr_FF_FF			,(ulong32*)TB_OverB_Curr_SubDI	,C_OverB_Curr_SubDILen		,	C_Event_Method		},	/*B�����*/
{COverC_Curr_FF_FF			,(ulong32*)TB_OverC_Curr_SubDI	,C_OverC_Curr_SubDILen		,	C_Event_Method		},	/*C�����*/
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



