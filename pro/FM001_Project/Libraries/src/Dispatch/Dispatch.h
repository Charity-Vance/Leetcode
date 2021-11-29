/*****************************************************************************************
Copyright:ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:Dispatch.h
Version:V1
Date:2014-3-12
Description:
Function List:
*****************************************************************************************/
#ifndef __Dispatch_H
#define __Dispatch_H

#include "Public.h"

#define C_First_Squeue				0x01	/*��һ��Ϣ����*/
#define C_Second_Squeue				0x02	/*�ڶ���Ϣ����*/

/*Data_Time_s��Bufferƫ��*/
#define C_Sec_698					C_DT_Start_ss
#define C_Min_698					C_DT_Start_mm
#define C_Hour_698					C_DT_Start_hh
#define C_Day_698					C_DT_Start_DD
#define C_Month_698					C_DT_Start_MM
#define C_Year_698					C_DT_Start_NN

extern void Dispatch_SendMessage(uchar8 MsgDerictAddr,uchar8 *P_Parameter,uchar8 ParameterLen);
extern void InF_DispatchClr_Message(Str_Msg_Parameter *P_Msg_Parameter);
extern uchar8 SF_RTCErrJudgeAndDeal(uchar8 *pData);

#endif

