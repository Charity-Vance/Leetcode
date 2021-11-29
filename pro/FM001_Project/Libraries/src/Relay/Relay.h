/********************************************************************************
Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     Relay.h
Version:       V1
Date:          2014-3-12
Description:   负荷开关处理
Function List: 
---------------------------------------------------------------------------------
History1:      第1次修改
内容1. Date:    2021-11-18
       Author:  wxy
       Modification:
       --------------------------------------------------------------------------
内容2. Date:
       Author:
       Modification:
---------------------------------------------------------------------------------
History2:      第2次修改
内容1. Date:
       Author:
       Modification:
       --------------------------------------------------------------------------
内容2. Date:
       Author:
       Modification:
********************************************************************************/

#ifndef	__Relay_H
#define	__Relay_H

/* 其他静态变量 */
ulong32	SV_OpenRealyDelay_Time;					/* 用于记录跳闸延时时间，每s减1，判断跳闸延时是否到 */
uchar8	SV_L_CloseRealyDelay_Time;				/* 本地表本地一次跳闸后允许合闸延时时间（条件合闸延时时间） */
ulong32	SV_Comm_CloseRealyDelay_Time;			/* 通信跳闸自动恢复持续时间 */
uchar8	SV_Error_Time;							/* 用于记录继电器异常时间，每s加1，判断异常时间是否＞5s，触发继电器异常事件记录 */
uchar8	SV_RelayDisplayStatus;					/* Bit0bit1指示当前“拉闸”字符显示状态：00表示不显示、01表示常显、10表示闪烁； */
												/* Bit2bit3指示当前LED显示状态：00表示不显示、01表示常显、10表示闪烁； */
												/* Bit4bit5指示当前背光显示状态：00表示不显示、01表示当前常显； */
ulong32	SV_24HourDelayTimer;					/* 用于电流超过门限电流计时 */
uchar8	SV_RelayCheckStatus;					/* 继电器回路检测状态字，用来实现继电器实际状态三次滑差计数 */
uchar8	SV_ucRelayOperatorCode[4];				/* 存放操作者代码 */
ushort16	SV_RelayRework_Timer;				/* 重复动作延时定时器 */
uchar8	SV_AlarmAfterPowerUp;					/* 上电时有报警命令时需要重新进行报警处理，上电置0x68，用过后清零 */
uchar8	SV_RelayOpenAfterPowerUp;				/* 上电时条件合闸状态要先跳闸，上电置0x68，用过后清零 */
uchar8	SV_EventOut_Err_Relay[3];				/* 主动上报标识，为0x68表示需要主动上报负荷开关误动作，上报后清零 */
uchar8	SV_EventOut_Open_Relay[3];				/* 主动上报标识，为0x68表示需要主动上报负荷开关误动作，上报后清零 */
uchar8	SV_EventOut_Close_Relay[3];				/* 主动上报标识，为0x68表示需要主动上报负荷开关误动作，上报后清零 */
uchar8	SV_Relay_L_OpenFlag[3];					/* 本地立即跳闸标识，为0x68表示本地命令处于立即跳闸状态，为0x86为预跳闸标识，收到本地合闸消息后清零 */
uchar8	SV_LocalOrderNum;						/* 本地命令序号 */
uchar8	SV_ComOrderNum;							/* 远程命令序号 */
uchar8	SV_ClearFlag;							/* 电表清零标识,收到总清消息后如果为远程外置表置为68，合闸后则清零，上电初始化时清零、收到其他控制命令清零 */
#if 0
uchar8  SV_ucExternalRelayStatusTime;				/* 外置继电器反馈信号检测5s定时，基于500ms */
#endif
/* 控制命令结构体远程、本地控制命令状态和继电器状态标志需要存EE */
 
typedef struct
{
uchar8	PreWarning;								/* 远程预跳闸报警为0x68；预跳闸报警解除为0x00 */
uchar8	Protect_Current;						/* 保电为0x68；非保电为0x00 */
uchar8	RelayOrderStatus;						/* 继电器命令状态：1A跳闸为0x68；1D跳闸自动恢复为0x55；1E跳闸自动恢复为0xAA；合闸允许为0x86；合闸为0x00 */
}Str_ComOrder_Relay;
Str_ComOrder_Relay	Com_RelayOrder;

/* 本地控制命令 */
typedef struct
{
uchar8	PreWarning;								/* 本地预跳闸报警为0x68；预跳闸报警解除为0x00 */
uchar8	RelayOrderStatus;						/* 合闸为0x00；预跳闸为0x86；立即跳闸为0x68 */
}Str_LocalOrder_Relay;
Str_LocalOrder_Relay Local_RelayOrder;

/* 组合控制命令 */
typedef struct
{
uchar8	PreWarning;								/* 报警为0x68；报警解除为0x00 */
uchar8	RelayOrderStatus;						/* 合闸为0x00；条件合闸（允许按键或插卡合闸）为0x86；跳闸为0x68 */
}Str_CombineOrder_Relay;
Str_CombineOrder_Relay  Combine_RelayOrder;

/* 继电器状态 */
typedef struct
{
uchar8	RelaytheoreticWarningStatus;			/* 继电器理论报警状态：报警为0x68；报警解除为0x00 */
uchar8	RelaytheoreticStatus;					/* 继电器理论状态：断开为0x68；导通为0x00 */
uchar8	RelayRealStatus;						/* 继电器实际状态：断开为0x68；导通为0x00 */
}Str_RelayStutas_Relay;
Str_RelayStutas_Relay   Relay_Stutas;

/* 控制命令结构体所用宏定义 */
#define	C_Close_Direct					0x00			/* 直接合闸 */
#define	C_Close_Allow					0x86			/* 允许合闸 */
#define	C_Pre_Open						0x55			/* 预跳闸 */
#define	C_Close_conditonal				0x86			/* 条件合闸 */
#define	C_Open							0x68			/* 直接跳闸 */
#define	C_Open_Allow					0xAA			/* 跳闸自动恢复（延时时间到合闸允许） */
#define	C_Open_Direct					0x55			/* 跳闸自动恢复（延时时间到直接合闸） */
#define	C_Protect_Current				0x68			/* 保电 */
#define	C_Protect_Current_Release		0x00			/* 保电解除 */
#define	C_OrderNull						0x99			/* 继电器组合命令为空 */

#define	C_PreWarning					0x68			/* 报警 */
#define	C_PreWarning_Release			0x00			/* 报警解除 */

#define	C_RelayOff						0x68			/* 继电器断开 */
#define	C_RelayOn						0x00			/* 继电器导通 */


/* 事件相关宏定义 */
#define	C_EventOnlyStart				0x68			/* 有发生无结束 */
#define	C_EventNotOnlyStart				0x86			/* 非有发生无结束 */
#define	C_EventOut_Relay				0x68			/* 表示需要上报事件 */
#define	C_EventOutNot_Relay				0x00			/* 表示不需要上报事件 */
#define	C_EventOutOpenErr_Relay			0x68			/* 表示需要上报事件 */
#define	C_EventOutCloseErr_Relay		0x86			/* 表示需要上报事件 */

/* 状态字相关宏定义 */
#define	C_ControlLoopError				0x01			/* 控制回路错 */
#define	C_ControlLoopNoError			0xFE			/* 无控制回路错 */
#if 0
#define	C_RelayStatusOn_External		0xDF			/* 外置继电器反馈信号导通(0:导通1:断开) */
#define	C_RelayStatusOff_External		0x20			/* 外置继电器反馈信号断开(0:导通1:断开) */
#endif
#define	C_RelayStatusOn					0xEF			/* 继电器导通 */
#define	C_RelayStatusOff				0x10			/* 继电器断开 */

#define	C_RelayOrderStatusOn			0xBF			/* 继电器命令导通 */
#define	C_RelayOrderStatusOff			0x40			/* 继电器命令断开 */

#define	C_RelayPreWarning_Release		0x7F			/* 无预跳闸报警 */
#define	C_RelayPreWarning				0x80			/* 预跳闸报警 */

#define	C_RelayProtect_Current_Release	0xEF			/* 非保电 */
#define	C_RelayProtect_Current			0x10			/* 保电 */

/* 其他 */
#define	C_CurrentOk						0x01			/* 表示当前电流值均小于门限电流，允许跳闸 */
#define	C_CurrentOver					0x02			/* 表示当前三相电流中有超过门限电流值的，不允许跳闸 */

#define C_RealayOpenSignOn				0x01			/* 拉闸常显 */
#define C_RealayOpenSignTwinkle			0x02			/* 拉闸闪烁 */
#define C_RealayOpenSignOff				0xFC			/* 拉闸熄灭 */

#define C_RelayStatusLEDOn				0x04			/* 跳闸指示灯常显 */
#define C_RelayStatusLEDTwinkle			0x08			/* 跳闸指示灯闪烁 */
#define C_RelayStatusLEDOff				0xF3			/* 跳闸指示灯熄灭 */

#define C_BackLEDOn						0x10			/* 背光常显 */
#define C_BackLEDOff						0xCF			/* 背光熄灭 */

#define C_DisplayOn						0x01			/* 常显 */
#define C_DisplayTwinkle					0x02			/* 闪烁 */
#define C_DisplayOff						0xFC			/* 熄灭 */

#define	C_RelayRealOff					0x01			/* 继电器断开 */
#define	C_RelayRealOn					0xFE			/* 继电器导通 */

#define	C_Relay_Type					0x0F			/* 负荷开关类型取低4位 */
#define	C_RelayBuiltIn_Type				0xF0			/* 负荷开关类型，是否带反馈线 */
#define	C_RelayFbackLine_Type			0x10			/* 负荷开关反馈+功率反馈 */

#define	C_Nosign						0x7F			/* 负荷开关类型取低4位 */

#define	C_EventClearSingle				0x302B00FF		/* 负荷开关类型取低4位 */
#define	C_EventClearAll					0xFFFFFFFF		/* 负荷开关类型取低4位 */

#define	C_RelayRework_Timer				(5 * 60 * 2)	/* 重复动作延时时间 */
#define	C_RelayReworkPowerUp_Timer		(5 * 2)			/* 上电初始化重复动作延时时间 */
#define C_L_CloseRealyDelay_Time			3				/* 本地表本地一次跳闸后允许合闸延时时间（条件合闸延时时间） */
#define	C_Error_Time					5				/* 负荷开关误动作判断时间 */

#define	C_Allowed						0x68			/* 允许下发跳闸自动恢复命令 */
#define	C_UnAllowed						0x86			/* 不允许下发跳闸自动恢复命令 */
#define	C_BackLEDstatusOn				0x68			/* 背光当前点亮 */
#if 0
#define C_ExternalRelayStatusTime		10				/* 外置继电器反馈信号检测5s定时，基于500ms */
#endif

#define SF_ABS(X) ( (X) >= 0 ? (X) : -(X) )

uchar8 SF_JudgeCurrent_Relay(void);
void SF_Event_CloseRelay_Relay(void);
void SF_Event_OpenRelay_Relay(void);
void SF_Event_RelayCheck_Relay(void);
void SF_RelayStatusCheck_Relay(void);
void SF_DealWithSV_Relay(void);
void SF_MsgSend_Relay(uchar8 *V_ucParm, uchar8 V_ucParmLen, uchar8 V_ucDerictAddr);
void SF_LocalControl_Relay(uchar8 V_RelayOrder);
void SF_Cardor3sCloseRelayTask_Relay(void);
void SF_TimeTask_Relay(void);
void SF_Combine_R_L_Order_Relay(void);
void SF_CombineOrderExecute_Relay(void);
void SF_RealayOpenSignMsgSend_Relay(uchar8 V_ucDisplayType);
void SF_RelayStatusLEDMsgSend_Relay(uchar8 V_ucDisplayType);
void SF_BackLEDMsgSend_Relay(uchar8 V_ucDisplayType);
uchar8 InF_JudgeVolage_Relay(void);
uchar8 SF_GetNewOrderNum(void);
uchar8 SF_JudgeOrderStatus(void);
void SF_Judge1D1EOrderStatus(void);
void SF_Op_OpenRelay_Relay(void);
uchar8 SF_Get_ApplianceF205(ulong32 V_OAD, uchar8 *P_DataBuf, ushort16 *V_Len);

#endif
