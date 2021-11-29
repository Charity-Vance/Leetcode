/*******************************************************************************
Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     Card.h
Version:       V1
Author:        jiangzs
Date:          2014-3-31
Description:   �������ļ�
---------------------------------------------------------------------------------
History1:      ��1���޸�
����1. Date:   20211021
   	   Author: lx
       Modification:
	   ---------------------------------------------------------------------------
����2. Date:
   	   Author:
       Modification:
----------------------------------------------------------------------------------
History2:      ��2���޸�
����1. Date:
   	   Author:
       Modification:
	   ---------------------------------------------------------------------------
����2. Date:
   	   Author:
       Modification:
******************************************************************************/

#ifndef	__Card_H
#define	__Card_H

#include    "Public.h"
#include    "SecurityCommunication.h"
#include    "Communication.h"

static	uchar8	SV_IC_SafeFlag;
		

#define	C_Length_4		0x04					/*���������*/
#define	C_Length_8		0x08					/*���������*/
#define	C_Length_10		0x0A					/*���������*/
extern Str_Comm_Parse		SV_Comm_Parse;		
/*********�����б�*****************************************************************/
void		MF_Card_Message(void);
uchar8	MF_Card_Esam_Proc(StrCardParse	*pStr_CardParse);
uchar8	IsVolage_Ok(void);
uchar8	MF_IsOverDraft_Zero(void);
uchar8	MF_PreSetCard_Esam_Proc(StrCardParse	*pStr_CardParse);
uchar8	MF_UserCard_Esam_Proc(StrCardParse	*pStr_CardParse);
uchar8	MF_OPS_Card_Esam_Proc(StrCardParse	*pStr_CardParse,uchar8 *pV_ucIC_ErrStatus);
uchar8	MF_Judge_OpenStutusAndCustNumCardNo(StrCardParse	*pStr_CardParse);
void	MF_Finish_L_Open(StrCardParse	*pStr_CardParse);
/*�����������*/
uchar8	MF_IC_UpdateParm(StrCardParse	*pStr_CardParse);

/*�쳣�忨�¼���¼���*/
void	MF_Init_IC_ErrEvent(StrCardParse	*pStr_CardParse);
void	MF_Write_IC_ErrEvent(StrCardParse	*pStr_CardParse);
/*��ʾ����Ϣ����*/
void	MF_Card_SendMsgToDisp(uchar8 V_ucDispSign,uchar8	V_ucDispMode,ushort16 V_ucDuration);
void	MF_Card_LCDView(uchar8	 V_ucType,StrCardParse	*pStr_CardParse);
void	MF_Card_SendICMsg(void);
void	MF_Card_SendMsg(uchar8	*pStr_MsgParmData,uchar8 V_ucLen,uchar8 V_ucDestAddress);
void	MF_Card_SendMsgForUpdataParm(uchar8	V_ucParmType,uchar8	V_ucDestMsg);
void	MF_MF_Card_SendMsgToSettlement(void);
extern 	uchar8 InF_CountDynamicDispNum(void);
extern 	void SF_ReadDispBuff(uchar8 *p_databuff);
extern 	void InF_WriteLCD(uchar8 *p_databuff,uchar8 Len,uchar8 KillZero);
extern 	uchar8  SF_DispAllScreenMode(void);
extern 	uchar8 INF_RELEASE_Service_Deal_Card(void);
extern 	void InF_Card_DispDynamicSign(void);
extern  uchar8 InF_JudgeVolage_Relay(void);

#endif
