/********************************************************************************
Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     Relay.h
Version:       V1
Date:          2014-3-12
Description:   ���ɿ��ش���
Function List: 
---------------------------------------------------------------------------------
History1:      ��1���޸�
����1. Date:    2021-11-18
       Author:  wxy
       Modification:
       --------------------------------------------------------------------------
����2. Date:
       Author:
       Modification:
---------------------------------------------------------------------------------
History2:      ��2���޸�
����1. Date:
       Author:
       Modification:
       --------------------------------------------------------------------------
����2. Date:
       Author:
       Modification:
********************************************************************************/

#ifndef	__Relay_H
#define	__Relay_H

/* ������̬���� */
ulong32	SV_OpenRealyDelay_Time;					/* ���ڼ�¼��բ��ʱʱ�䣬ÿs��1���ж���բ��ʱ�Ƿ� */
uchar8	SV_L_CloseRealyDelay_Time;				/* ���ر���һ����բ�������բ��ʱʱ�䣨������բ��ʱʱ�䣩 */
ulong32	SV_Comm_CloseRealyDelay_Time;			/* ͨ����բ�Զ��ָ�����ʱ�� */
uchar8	SV_Error_Time;							/* ���ڼ�¼�̵����쳣ʱ�䣬ÿs��1���ж��쳣ʱ���Ƿ�5s�������̵����쳣�¼���¼ */
uchar8	SV_RelayDisplayStatus;					/* Bit0bit1ָʾ��ǰ����բ���ַ���ʾ״̬��00��ʾ����ʾ��01��ʾ���ԡ�10��ʾ��˸�� */
												/* Bit2bit3ָʾ��ǰLED��ʾ״̬��00��ʾ����ʾ��01��ʾ���ԡ�10��ʾ��˸�� */
												/* Bit4bit5ָʾ��ǰ������ʾ״̬��00��ʾ����ʾ��01��ʾ��ǰ���ԣ� */
ulong32	SV_24HourDelayTimer;					/* ���ڵ����������޵�����ʱ */
uchar8	SV_RelayCheckStatus;					/* �̵�����·���״̬�֣�����ʵ�̵ּ���ʵ��״̬���λ������ */
uchar8	SV_ucRelayOperatorCode[4];				/* ��Ų����ߴ��� */
ushort16	SV_RelayRework_Timer;				/* �ظ�������ʱ��ʱ�� */
uchar8	SV_AlarmAfterPowerUp;					/* �ϵ�ʱ�б�������ʱ��Ҫ���½��б��������ϵ���0x68���ù������� */
uchar8	SV_RelayOpenAfterPowerUp;				/* �ϵ�ʱ������բ״̬Ҫ����բ���ϵ���0x68���ù������� */
uchar8	SV_EventOut_Err_Relay[3];				/* �����ϱ���ʶ��Ϊ0x68��ʾ��Ҫ�����ϱ����ɿ����������ϱ������� */
uchar8	SV_EventOut_Open_Relay[3];				/* �����ϱ���ʶ��Ϊ0x68��ʾ��Ҫ�����ϱ����ɿ����������ϱ������� */
uchar8	SV_EventOut_Close_Relay[3];				/* �����ϱ���ʶ��Ϊ0x68��ʾ��Ҫ�����ϱ����ɿ����������ϱ������� */
uchar8	SV_Relay_L_OpenFlag[3];					/* ����������բ��ʶ��Ϊ0x68��ʾ���������������բ״̬��Ϊ0x86ΪԤ��բ��ʶ���յ����غ�բ��Ϣ������ */
uchar8	SV_LocalOrderNum;						/* ����������� */
uchar8	SV_ComOrderNum;							/* Զ��������� */
uchar8	SV_ClearFlag;							/* ��������ʶ,�յ�������Ϣ�����ΪԶ�����ñ���Ϊ68����բ�������㣬�ϵ��ʼ��ʱ���㡢�յ����������������� */
#if 0
uchar8  SV_ucExternalRelayStatusTime;				/* ���ü̵��������źż��5s��ʱ������500ms */
#endif
/* ��������ṹ��Զ�̡����ؿ�������״̬�ͼ̵���״̬��־��Ҫ��EE */
 
typedef struct
{
uchar8	PreWarning;								/* Զ��Ԥ��բ����Ϊ0x68��Ԥ��բ�������Ϊ0x00 */
uchar8	Protect_Current;						/* ����Ϊ0x68���Ǳ���Ϊ0x00 */
uchar8	RelayOrderStatus;						/* �̵�������״̬��1A��բΪ0x68��1D��բ�Զ��ָ�Ϊ0x55��1E��բ�Զ��ָ�Ϊ0xAA����բ����Ϊ0x86����բΪ0x00 */
}Str_ComOrder_Relay;
Str_ComOrder_Relay	Com_RelayOrder;

/* ���ؿ������� */
typedef struct
{
uchar8	PreWarning;								/* ����Ԥ��բ����Ϊ0x68��Ԥ��բ�������Ϊ0x00 */
uchar8	RelayOrderStatus;						/* ��բΪ0x00��Ԥ��բΪ0x86��������բΪ0x68 */
}Str_LocalOrder_Relay;
Str_LocalOrder_Relay Local_RelayOrder;

/* ��Ͽ������� */
typedef struct
{
uchar8	PreWarning;								/* ����Ϊ0x68���������Ϊ0x00 */
uchar8	RelayOrderStatus;						/* ��բΪ0x00��������բ����������忨��բ��Ϊ0x86����բΪ0x68 */
}Str_CombineOrder_Relay;
Str_CombineOrder_Relay  Combine_RelayOrder;

/* �̵���״̬ */
typedef struct
{
uchar8	RelaytheoreticWarningStatus;			/* �̵������۱���״̬������Ϊ0x68���������Ϊ0x00 */
uchar8	RelaytheoreticStatus;					/* �̵�������״̬���Ͽ�Ϊ0x68����ͨΪ0x00 */
uchar8	RelayRealStatus;						/* �̵���ʵ��״̬���Ͽ�Ϊ0x68����ͨΪ0x00 */
}Str_RelayStutas_Relay;
Str_RelayStutas_Relay   Relay_Stutas;

/* ��������ṹ�����ú궨�� */
#define	C_Close_Direct					0x00			/* ֱ�Ӻ�բ */
#define	C_Close_Allow					0x86			/* �����բ */
#define	C_Pre_Open						0x55			/* Ԥ��բ */
#define	C_Close_conditonal				0x86			/* ������բ */
#define	C_Open							0x68			/* ֱ����բ */
#define	C_Open_Allow					0xAA			/* ��բ�Զ��ָ�����ʱʱ�䵽��բ���� */
#define	C_Open_Direct					0x55			/* ��բ�Զ��ָ�����ʱʱ�䵽ֱ�Ӻ�բ�� */
#define	C_Protect_Current				0x68			/* ���� */
#define	C_Protect_Current_Release		0x00			/* ������ */
#define	C_OrderNull						0x99			/* �̵����������Ϊ�� */

#define	C_PreWarning					0x68			/* ���� */
#define	C_PreWarning_Release			0x00			/* ������� */

#define	C_RelayOff						0x68			/* �̵����Ͽ� */
#define	C_RelayOn						0x00			/* �̵�����ͨ */


/* �¼���غ궨�� */
#define	C_EventOnlyStart				0x68			/* �з����޽��� */
#define	C_EventNotOnlyStart				0x86			/* ���з����޽��� */
#define	C_EventOut_Relay				0x68			/* ��ʾ��Ҫ�ϱ��¼� */
#define	C_EventOutNot_Relay				0x00			/* ��ʾ����Ҫ�ϱ��¼� */
#define	C_EventOutOpenErr_Relay			0x68			/* ��ʾ��Ҫ�ϱ��¼� */
#define	C_EventOutCloseErr_Relay		0x86			/* ��ʾ��Ҫ�ϱ��¼� */

/* ״̬����غ궨�� */
#define	C_ControlLoopError				0x01			/* ���ƻ�·�� */
#define	C_ControlLoopNoError			0xFE			/* �޿��ƻ�·�� */
#if 0
#define	C_RelayStatusOn_External		0xDF			/* ���ü̵��������źŵ�ͨ(0:��ͨ1:�Ͽ�) */
#define	C_RelayStatusOff_External		0x20			/* ���ü̵��������źŶϿ�(0:��ͨ1:�Ͽ�) */
#endif
#define	C_RelayStatusOn					0xEF			/* �̵�����ͨ */
#define	C_RelayStatusOff				0x10			/* �̵����Ͽ� */

#define	C_RelayOrderStatusOn			0xBF			/* �̵������ͨ */
#define	C_RelayOrderStatusOff			0x40			/* �̵�������Ͽ� */

#define	C_RelayPreWarning_Release		0x7F			/* ��Ԥ��բ���� */
#define	C_RelayPreWarning				0x80			/* Ԥ��բ���� */

#define	C_RelayProtect_Current_Release	0xEF			/* �Ǳ��� */
#define	C_RelayProtect_Current			0x10			/* ���� */

/* ���� */
#define	C_CurrentOk						0x01			/* ��ʾ��ǰ����ֵ��С�����޵�����������բ */
#define	C_CurrentOver					0x02			/* ��ʾ��ǰ����������г������޵���ֵ�ģ���������բ */

#define C_RealayOpenSignOn				0x01			/* ��բ���� */
#define C_RealayOpenSignTwinkle			0x02			/* ��բ��˸ */
#define C_RealayOpenSignOff				0xFC			/* ��բϨ�� */

#define C_RelayStatusLEDOn				0x04			/* ��բָʾ�Ƴ��� */
#define C_RelayStatusLEDTwinkle			0x08			/* ��բָʾ����˸ */
#define C_RelayStatusLEDOff				0xF3			/* ��բָʾ��Ϩ�� */

#define C_BackLEDOn						0x10			/* ���ⳣ�� */
#define C_BackLEDOff						0xCF			/* ����Ϩ�� */

#define C_DisplayOn						0x01			/* ���� */
#define C_DisplayTwinkle					0x02			/* ��˸ */
#define C_DisplayOff						0xFC			/* Ϩ�� */

#define	C_RelayRealOff					0x01			/* �̵����Ͽ� */
#define	C_RelayRealOn					0xFE			/* �̵�����ͨ */

#define	C_Relay_Type					0x0F			/* ���ɿ�������ȡ��4λ */
#define	C_RelayBuiltIn_Type				0xF0			/* ���ɿ������ͣ��Ƿ�������� */
#define	C_RelayFbackLine_Type			0x10			/* ���ɿ��ط���+���ʷ��� */

#define	C_Nosign						0x7F			/* ���ɿ�������ȡ��4λ */

#define	C_EventClearSingle				0x302B00FF		/* ���ɿ�������ȡ��4λ */
#define	C_EventClearAll					0xFFFFFFFF		/* ���ɿ�������ȡ��4λ */

#define	C_RelayRework_Timer				(5 * 60 * 2)	/* �ظ�������ʱʱ�� */
#define	C_RelayReworkPowerUp_Timer		(5 * 2)			/* �ϵ��ʼ���ظ�������ʱʱ�� */
#define C_L_CloseRealyDelay_Time			3				/* ���ر���һ����բ�������բ��ʱʱ�䣨������բ��ʱʱ�䣩 */
#define	C_Error_Time					5				/* ���ɿ��������ж�ʱ�� */

#define	C_Allowed						0x68			/* �����·���բ�Զ��ָ����� */
#define	C_UnAllowed						0x86			/* �������·���բ�Զ��ָ����� */
#define	C_BackLEDstatusOn				0x68			/* ���⵱ǰ���� */
#if 0
#define C_ExternalRelayStatusTime		10				/* ���ü̵��������źż��5s��ʱ������500ms */
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
