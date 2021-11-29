/*******************************************************************************
Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     Freeze.h
Version:       V1
Author:        
Date:          2014-3-12
Description:   
---------------------------------------------------------------------------------
History1:      ��1���޸�
����1. Date:   
   	   Author: 
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

#ifndef	__Freeze_H
#define	__Freeze_H

#include "SecurityCommunication.h"

#define	C_DemandBegin_Freeze 165

#define	C_DemandLen     8
#define	C_AddTimeLen    6

#define	C_YYMMLen		3	/*���³��ȣ�698��ʽ*/
#define	C_DDhhmmssLen	4	/*��ʱ���볤�ȣ�698��ʽ*/

#define C_IntertimeOn			    0x00	/*���ʱ�䵽*/
#define C_IntertimeOff		        0x68	/*���ʱ��δ��*/

#define C_NeedAddSettleFreezeFlag   0x68    /*��Ҫ�����������*/
#define C_NoAddSettleFreezeFlag     0x00    /*����Ҫ�����������*/


extern void InF_FreezeDayAfterPowerUp(void);
extern void InF_FreezeSwitch(ulong32 V_ulDataCode,uchar8 Swich_Time[6]);
void SF_GetNextDay(uchar8 *P_ucDay,uchar8 V_ucMode);
extern	uchar8  InF_ReadOADTab_Data(ulong32 V_Data_Id, uchar8 *P_Data, ushort16 * P_Data_Length);
extern	uchar8  InF_ReadLaterFreezeNum(ulong32 V_Data_Id,uchar8 * P_Data,uchar8 * V_Length);
void SF_AddMonthFreeze(uchar8 *P_ucCurrentTime, uchar8 *P_ucPowerOffTime);
extern void SF_ClearVoltageQualifiedRate_Data(void);
#endif
