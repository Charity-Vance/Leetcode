/********************************************************************************************
Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     Rate.c
Version:       V1
Author:        
Date:          2014-3-12
Description:   费率、时段等的处理
---------------------------------------------------------------------------------------------
History1:      第1次修改
内容1. Date:
       Author:
       Modification:
---------------------------------------------------------------------------------------------
内容2. Date:
       Author:
       Modification:
---------------------------------------------------------------------------------------------
History2:      第2次修改
内容1. Date:
       Author:
       Modification:
---------------------------------------------------------------------------------------------
内容2. Date:
       Author:
       Modification:
---------------------------------------------------------------------------------------------
History3:      第3次修改
内容1. Date:2021.09.22
       Author:zlj
       Modification:
---------------------------------------------------------------------------------------------
内容2. Date:
       Author:
       Modification:
********************************************************************************************/

#ifndef __Rate_H
#define __Rate_H

/*时段状态*/
uchar8 SV_ucTimeIntervalStatus;			/*时段状态寄存器,用于时段投切判断*/
uchar8 SV_ucTimeIntSetStatus;			/*时段表状态寄存器*/
#define C_TimeChange			0xAA	/*时段发生投切*/
#define C_TimeNoChange			0xBB	/*时段没投切*/


#define C_HolidyIntID			0x0403FA00	/*用于读公共假日标识码初始赋值*/
#define C_HoliBlockNum			46			/*读公共假日数据的块数1*/
/*四种切换类型处理*/
#define C_DisStutas_Char1		0x02	/*特征字1中取bit1,用于判断①②含义*/
#define C_DisplayRate			1		/*液晶①②符号的表示费率电价*/
#define C_DisplayTimeInterval	0		/*液晶①②符号的表示时段表*/

#define C_TimeZone_Status3		0x20	/*状态字3中时区表对应位*/
#define C_FirstTimeZone			0xDF	/*第一套时区表*/
#define C_SecondTimeZone		0x20	/*第二套时区表*/
#define C_TimeZoneOffset		5		/*状态字3中时区位的偏移量*/

#define C_TimeInterval_Status3	0x01	/*状态字3中时段表对应位*/
#define C_FirstTimeInterval		0xFE	/*第一套时段表*/
#define C_SecondTimeInterval	0x01	/*第二套时段表*/

#define C_LowByte				0x00	/*状态字3中的低字节*/
#define C_HighByte				0x01	/*状态字3中的高字节*/

#define C_First					0x00	/*自扩寄存器第一套数据*/
#define C_Second				0x86	/*自扩寄存器第二套数据*/

#define C_RateOADChange_Flag	0x00000001		/*费率电价数据标识改变标志*/


/*自扩寄存器*/
#define C_TIntervalSet_EX		0		/*时段表套数对应字节地址*/
#define C_TZoneSet_EX			1		/*时区表套数对应字节地址*/

/*年/月阶梯判断*/
#define C_SettlementLength_One	3		/*每个年结算日数据长度*/
#define C_SettlementNum			(CLCurrent_Ladder_Table_LadSett/C_SettlementLength_One)		/*每套阶梯包含年结算日个数*/

/*切换时间判断*/
#define C_SwitchValid			0	/*切换有效*/
#define C_SwitchInvalid			1	/*切换无效*/
#define C_SwitchTimeErr			2	/*切换时间错误*/

/*日期,含星期0x04000101*/
#define C_Week_Data				0	/*周*/
#define C_Day_Data				1	/*日*/
#define C_Month_Datak			2	/*月*/
#define C_Year_Data				3	/*年*/

/*时间和日期,不含星期0x040001FD*/
#define C_Sec					0	/*秒*/
#define C_Minute				1	/*分*/
#define C_Hour					2	/*时*/
#define C_Day					3	/*日*/
#define C_Month					4	/*月*/
#define C_Year					5	/*年*/

/*时间和日期,含星期0x0400010C*/
#define C_Second_Week			0	/*秒*/
#define C_Minute_Week			1	/*分*/
#define C_Hour_Week				2	/*时*/
#define C_Week_Week				3	/*周*/
#define C_Day_Week				4	/*日*/
#define C_Month_Week			5	/*月*/
#define C_Year_Week				6	/*年*/

/*电表状态指示标志*/
uchar8 SV_ucPowerStatus;			/*电表状态指示标志，判断冻结与结算时为当前时间还是参数时间*/
#define C_PowerUpEdge			0xAA	/*上电沿状态,为参数时间*/
#define C_PowerOnPeriod			0xBB	/*电表正常有电状态,为当前时间*/
/*时段表*/
#define CL_OneTimeIntervalNum	3		/*一个时段表的长度*/


typedef struct
{
	uchar8 StepSwitchType;	/*结算类型*/
	uchar8 Time[5];			/*日期时间*/
}Str_StepSwitch;

/*zlj新增，代替原来的常量数组C_usLimitJudge[5]*/
#define C_MaxYearTZNum		14	/*年时区数限值*/
#define C_MaxDayPTTabNum	8	/*日时段表数限值*/
#define C_MaxDayPTNum		14	/*日时段数限值*/
/*费率数限值采用现有的C_MaxRatesNum宏定义*/
#define C_MaxHolidayNum		20	/*公共假日数限值(评审会上说改为20)*/


/**************** 函数声明********************************************/
void InF_MultiRates_ParseMessage(Str_Msg_Parameter *pStr_Msg);
void InF_Deal_MultiRates(void);
uchar8 SF_JudgeSwitchTime_MultiRates(ulong32 V_ulSwitchTimeID, uchar8 *pV_ucCurrentTime, uchar8 *pV_ucSwitchTimeTemp);
void SF_StepTypeProcess(uchar8 *pV_ucOldDate, uchar8 *pV_ucNewDate, uchar8 *pV_ucSettlementTime);
void SF_JudgeStepSwitch_MultiRates(uchar8 *pV_ucCurrentTime, uchar8 *pV_ucCurrentStepData, uchar8 V_ucStepStatus);
void SF_JudgeTimeIntervalSwitch_MultiRates(uchar8 V_ucDisplayType, uchar8 *pV_ucCurrentTime, uchar8 *pV_ucChangeFlag);
void SF_JudgeTimeZoneSwitch_MultiRates(uchar8 *pV_ucCurrentTime, uchar8 *pV_ucChangeFlag);
void SF_JudgeRateSwitch_MultiRates(uchar8 V_ucDisplayType, uchar8 *pV_ucCurrentTime);
uchar8 SF_ParseMessage_MultiRates(Str_Msg_Parameter *pStr_Msg_Parameter);
void SF_MsgProcess(uchar8 *pV_ucParm, uchar8 V_ucParmLen, uchar8 V_ucDerictMod);
void SF_ParaChangeProcess_MultiRates(uchar8 V_ucStepStatus, uchar8 V_ucRatesNum);
void SF_SendMsgToDisplay(uchar8 V_ucMsg1, uchar8 V_ucMsg2, uchar8 V_ucMsg1_Mode, uchar8 V_ucMsg2_Mode, uchar8 V_ucMsgNum);
void SF_TimeZoneSequence( uchar8 *pV_ucBuf, uchar8 V_ucNum);
void SF_Deal12dig(ulong32 V_ulOAD, uchar8 *pV_ucdata);
#endif
