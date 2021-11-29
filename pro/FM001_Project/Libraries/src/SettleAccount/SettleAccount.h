/*******************************************************************************
Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     SettleAccount.c
Version:       V1
Author:        
Date:          2014-3-12
Description:   结算
---------------------------------------------------------------------------------
History1:      第1次修改
内容1. Date:   20219016
   	   Author: fy
       Modification:
	   ---------------------------------------------------------------------------
内容2. Date:
   	   Author:
       Modification:
----------------------------------------------------------------------------------
History2:      第2次修改
内容1. Date:
   	   Author:
       Modification:
	   ---------------------------------------------------------------------------
内容2. Date:
   	   Author:
       Modification:
******************************************************************************/
#ifndef	__SettleAccount_H
#define	__SettleAccount_H

#include "Freeze.h"

#define	C_DemandClearFlag	0x68

uchar8 SV_FristCheckDayChange[4];				/* 用于掉电保存消息参数，[0]为消息号，[1]为消息类型，[2][3]为CRC；*/
uchar8 SV_StepSwitch[10];						/* 用于掉电保存消息参数，[0]为消息号,[1]为消息类型,[2]-[7]为切换时间，[8]-[9]为CRC；*/

void InF_SettleAccountsAfterPowerUp(void);
void SF_DealwithMin_SettleAccounts(uchar8 Settle_Time[6]);
void SF_SettleAdd_SettleAccounts(uchar8 *StartTime,uchar8 *EndTime);
void SF_DealwithYear_SettleAccounts(uchar8 *pV_ucSettle_Time);
void SF_DealwithYearAdd_SettleAccounts(uchar8 *StartTime,uchar8 *EndTime);
void SF_GetRevEnergy_Pul_SettleAccounts(uchar8 *V_ucResultData);
void SF_GetPosEnergy_Pul_SettleAccounts(uchar8 *V_ucResultData);
void SF_MsgSend_SettleAccounts(void);
void SF_MsgSend_SettleAccounts_ReSettle_Day1(void);
void SF_FreezeYSettle(uchar8 *Swich_Time,uchar8 Len);

uchar8 SF_JudgeAndOrder_SettleAccounts(uchar8 *P_ucData,uchar8 V_ucLen,uchar8 V_ucNum);


#endif
