/********************************************************************************************
Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     VoltageQR.c
Version:       V1
Author:
Date:          2014-3-12
Description:   电压合格率
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

#include "public.h"
#include "VoltageQR.h"
#include "DI.h"

/*zlj去掉该变量，目前的做法是模块内部判断是否时间发生跨月修改了，如果是则清月电压合格率数据。但该做法的缺陷是如果时间改成跨月的1日0时0分，则不会清本月电压合格率。
改由通讯发时间变化消息*/
/*static Str_CurrentMonth_Type Str_CurrentMonth;*/

/*******************************************************************************
函数原型: InF_VoltageQRrestore(void)
功能描述: 电压合格率模块上电初始化，若读数据失败，清零全部数据
输入参数: 无
输出参数: 无
返回参数: 无
调用位置:
备    注: 上电初始化时调用
*******************************************************************************/
void InF_VoltageQRrestore(void)
{
	ushort16 V_usData_Length, V_usDataEncode = 0;
	uchar8 V_ucData[CLVolA_Per_Pass_M] = {0x00};

	/*zlj新增是否停上电跨月判断，如果跨月，则清月电压合格率*/
	V_usData_Length = CLEnter_LowPower_Time;
	InF_Read_Data(CEnter_LowPower_Time, V_ucData, &V_usData_Length, &V_usDataEncode);
	V_usData_Length = CLExit_LowPower_Time;
	InF_Read_Data(CExit_LowPower_Time, V_ucData + CLEnter_LowPower_Time, &V_usData_Length, &V_usDataEncode);
	if ( (PF_DataTimeActive_698(V_ucData, C_SecondStart, CLEnter_LowPower_Time) == C_OK) && PF_DataTimeActive_698(V_ucData + CLEnter_LowPower_Time, C_SecondStart, CLExit_LowPower_Time) == C_OK)
	{
		if ( (V_ucData[C_Year_hi8] != V_ucData[C_Year_hi8 + CLEnter_LowPower_Time])
          || (V_ucData[C_Year_lo8] != V_ucData[C_Year_lo8 + CLEnter_LowPower_Time])
          || (V_ucData[C_Month] != V_ucData[C_Month + CLEnter_LowPower_Time]) )
		{
			SF_ClearVoltageQualifiedRate_Data();        /*月电压合格率清零*/
		}
	}

	V_usData_Length = CLVolA_Per_Pass_M;
	if ( (InF_Read_Data(CVolA_Per_Pass_0, V_ucData, &V_usData_Length, &V_usDataEncode) != C_OK)					/*读本月A相统计数据*/
      || (InF_Read_Data(CVolB_Per_Pass_0, V_ucData, &V_usData_Length, &V_usDataEncode) != C_OK)					/*读本月B相统计数据*/
      || (InF_Read_Data(CVolC_Per_Pass_0, V_ucData, &V_usData_Length, &V_usDataEncode) != C_OK) )				/*读本月C相统计数据*/
	{
		SF_ClearVoltageQualifiedRate_Data();            /*月电压合格率清零*/
	}
	V_usData_Length = CLVolA_Per_Pass_D;
	if ( (InF_Read_Data(CVolA_Per_Pass_0_Freeze, V_ucData, &V_usData_Length, &V_usDataEncode) != C_OK)			/*读日A相统计数据*/
      || (InF_Read_Data(CVolB_Per_Pass_0_Freeze, V_ucData, &V_usData_Length, &V_usDataEncode) != C_OK)			/*读日B相统计数据*/
      || (InF_Read_Data(CVolC_Per_Pass_0_Freeze, V_ucData, &V_usData_Length, &V_usDataEncode) != C_OK) )		/*读日C相统计数据*/
	{
		InF_ClearVoltageQR_Data_D();																			/*日电压合格率清零*/
	}

}

/*******************************************************************************
函数原型: InF_VoltageQR_ParseMessage
功能描述: 通信消息处理
输入参数: *pStr_Msg_Parameter:消息结构体
输出参数: 无
返回参数: C_OK/C_Error
调用位置:
备    注: 调度每分钟调用函数
*******************************************************************************/
uchar8 InF_VoltageQR_ParseMessage(Str_Msg_Parameter *pStr_Msg_Parameter)
{
	uchar8 *pV_ucParm;
	if (pStr_Msg_Parameter->PowerFlag == C_PowerFalling)						/*有掉电标志直接退出，返回C_OK*/
	{
		return(C_OK);
	}
	pV_ucParm = pStr_Msg_Parameter->Parameter;
	if (*pV_ucParm == Pt_Dispatch_Timing)										/*判断参数是否正确*/
	{
		if (*(pV_ucParm + 1) == C_SystemMinChange)
		{
			if (pStr_Msg_Parameter->Length == (Pt_Dispatch_Timing_Len + 1) )	/*判断参数长度是否正确*/
			{
				Msg_VoltageQualifiedRateMetering();								/*参数都正确调用电压合格率数据统计函数，返回C_0K*/
				return(C_OK);
			}
		}
		else if (*(pV_ucParm + 1) == C_SystemMonthChange)
		{
			SF_ClearVoltageQualifiedRate_Data();								/*月电压合格率数据清零*/
		}
	}
	if ( (*pV_ucParm == Pt_VRQTimeChange) && (pStr_Msg_Parameter->Length == (Pt_VRQTimeChange_Len + 1) ) )		/*zlj新增通讯修改时间*/
	{
		if ( (*(pV_ucParm + 1 + C_Month)    != (*(pV_ucParm + 1 + CLDate_Week_Time + C_Month) ) )				/*修改前时间和修改后时间的年月不同*/
          || (*(pV_ucParm + 1 + C_Year_lo8) != (*(pV_ucParm + 1 + CLDate_Week_Time + C_Year_lo8) ) )
          || (*(pV_ucParm + 1 + C_Year_hi8) != (*(pV_ucParm + 1 + CLDate_Week_Time + C_Year_hi8) ) ) )

		{
			SF_ClearVoltageQualifiedRate_Data();								/*月电压合格率数据清零*/
		}
	}
	return(C_Error);
}

/*******************************************************************************
函数原型: void SF_ClearVoltageQualifiedRate_Data(void)
功能描述: 月电压合格率数据清零
输入参数: 无
输出参数: 无
返回参数: 无
调用位置: 数据不合法时或者过自然月时清零
备    注:
*******************************************************************************/
void SF_ClearVoltageQualifiedRate_Data(void)
{
	uchar8 V_ucVol_Per_Pass_Data[CLVolA_Per_Pass_M] = {0x00};

	InF_Write_Data(C_Msg_VoltageQualifiedRateMetering, CVolA_Per_Pass_0, V_ucVol_Per_Pass_Data, CLVolA_Per_Pass_M, C_W_SafeFlag);	/*写本月A相统计数据*/
	InF_Write_Data(C_Msg_VoltageQualifiedRateMetering, CVolB_Per_Pass_0, V_ucVol_Per_Pass_Data, CLVolB_Per_Pass_M, C_W_SafeFlag);	/*写本月B相统计数据*/
	InF_Write_Data(C_Msg_VoltageQualifiedRateMetering, CVolC_Per_Pass_0, V_ucVol_Per_Pass_Data, CLVolC_Per_Pass_M, C_W_SafeFlag);	/*写本月C相统计数据*/
}

/*******************************************************************************
函数原型: Msg_VoltageQualifiedRateMetering
功能描述: 电压合格率数据统计
输入参数: 无
输出参数: 无
返回参数: 无
调用位置:
备    注: 通信消息处理函数InF_VoltageQR_ParseMessage在输入参数正确时调用，根据
         参数阈值计算当前电压合格率统计数据并写数据层。
*******************************************************************************/
void Msg_VoltageQualifiedRateMetering(void)
{
	ushort16 V_usVoltPama[4];																								/*存储电压上限、电压下限、电压考核上限、电压考核下限*/
	ulong32 V_ulOADVoltPama[4] = {CVoltage_UpLim, CVoltage_LowLim, CVolage_Check_UpLim, CVolage_Check_LowLim};				/*存储电压上限，电压下限，电压考核上限，电压考核下限的OAD*/

	ushort16 V_usPhaseABC_Volt[3];																							/*存储ABC相电压瞬时量*/
	ulong32 V_ulOADPhaseABC_Volt[3] = {CPhaseA_Volage, CPhaseB_Volage, CPhaseC_Volage};										/*存储ABC相电压瞬时量的OAD*/
    ushort16 V_usDataEncode = 0;

	uchar8 V_ucVol_Per_Pass_Data[3][CLVolA_Per_Pass_M];																		/*存储ABC相月电压合格率数据*/

	ulong32 V_ulOADVolABC_Per_Pass_0[3] = {CVolA_Per_Pass_0, CVolB_Per_Pass_0, CVolC_Per_Pass_0};							/*存储ABC相月电压合格率的OAD*/

	uchar8  V_ucVol_Per_Pass_Data_D[3][CLVolA_Per_Pass_D];															/*存储ABC相日电压合格率数据*/


	ulong32 V_ulOADVol_Per_Pass_0_Freeze[3] = {CVolA_Per_Pass_0_Freeze, CVolB_Per_Pass_0_Freeze,CVolC_Per_Pass_0_Freeze};	/*存储ABC相日电压合格率数据的OAD*/

	ushort16 V_usData_Length;
	uchar8  V_ucLine_Type, V_ucParemeter[CLVoltage_UpLim];
	uchar8 V_uci;

	for (V_uci = 0; V_uci < 4; V_uci++)														/*读电压上限，电压下限，电压考核上限，电压考核下限*/
	{
		V_usData_Length = CLVoltage_UpLim;
		if (InF_Read_Data(V_ulOADVoltPama[V_uci], V_ucParemeter, &V_usData_Length, &V_usDataEncode) != C_OK)
		{
			return;
		}
		PF_Buffer2ToUshort16(V_ucParemeter, &V_usVoltPama[V_uci]);
	}

	if ( (V_usVoltPama[C_offVoltage_UpLim] < V_usVoltPama[C_offVoltage_Check_UpLim])
      && (V_usVoltPama[C_offVoltage_LowLim] > V_usVoltPama[C_offVoltage_Check_LowLim])
      && (V_usVoltPama[C_offVoltage_LowLim] < V_usVoltPama[C_offVoltage_UpLim]) )			/*检验参数合法性*/
	{
		for (V_uci = 0; V_uci < 3; V_uci++)													/*读ABC相电压*/
		{
			V_usData_Length = CLPhaseA_Volage;
			InF_Read_Data(V_ulOADPhaseABC_Volt[V_uci], V_ucParemeter, &V_usData_Length, &V_usDataEncode);
			PF_Buffer2ToUshort16(V_ucParemeter, &V_usPhaseABC_Volt[V_uci]);
		}

		V_usData_Length = CLLine_Type;
		InF_Read_Data(CLine_Type, &V_ucLine_Type, &V_usData_Length, &V_usDataEncode);		/*读相线类型*/
		if (V_ucLine_Type == C_3P3W)														/*三相三线，直接将B相电压赋值为合格电压*/
		{
			V_usPhaseABC_Volt[C_offB_Volt] = V_usVoltPama[C_offVoltage_LowLim] + 1;
		}

		for (V_uci = 0; V_uci < 3; V_uci++)													/*读ABC相月电压合格率统计数据*/
		{
			V_usData_Length = CLVolA_Per_Pass_M;
			if (InF_Read_Data(V_ulOADVolABC_Per_Pass_0[V_uci], &V_ucVol_Per_Pass_Data[V_uci][0], &V_usData_Length, &V_usDataEncode) != C_OK)
			{
				SF_ClearVoltageQualifiedRate_Data();
				return;
			}
		}

		for (V_uci = 0; V_uci < 3; V_uci++)													/*读日ABC相电压合格率统计数据*/
		{
			V_usData_Length = CLVolA_Per_Pass_D;
			if (InF_Read_Data(V_ulOADVol_Per_Pass_0_Freeze[V_uci], &V_ucVol_Per_Pass_Data_D[V_uci][0], &V_usData_Length, &V_usDataEncode) != C_OK)
			{
				memset(&V_ucVol_Per_Pass_Data_D[0][0], 0, CLVolA_Per_Pass_D + CLVolB_Per_Pass_D + CLVolC_Per_Pass_D);											/*CRC错误，清零数据*/
				InF_ClearVoltageQR_Data_D();												/*清日电压合格率数据*/
			}
		}

		for (V_uci = 0; V_uci < 3; V_uci++)													/*统计ABC相月和日电压合格率数据*/
		{
			if ( (V_usPhaseABC_Volt[V_uci] < V_usVoltPama[C_offVoltage_Check_UpLim]) && (V_usPhaseABC_Volt[V_uci] > V_usVoltPama[C_offVoltage_Check_LowLim]) )						/*A/B/C电压是否在考核范围内*/
			{
				MF_Calculate(&V_ucVol_Per_Pass_Data[V_uci][0], V_usPhaseABC_Volt[V_uci], V_usVoltPama[C_offVoltage_UpLim], V_usVoltPama[C_offVoltage_LowLim]);						/*A/B/C相电压在考核范围内，计算A/B/C相电压合格率统计数据*/
				MF_Calculate(&V_ucVol_Per_Pass_Data_D[V_uci][0], V_usPhaseABC_Volt[V_uci], V_usVoltPama[C_offVoltage_UpLim], V_usVoltPama[C_offVoltage_LowLim]);					/*A/B/C相电压在考核范围内，计算日A/B/C相电压合格率统计数据*/
			}
			InF_Write_Data(C_Msg_VoltageQualifiedRateMetering, V_ulOADVolABC_Per_Pass_0[V_uci], &V_ucVol_Per_Pass_Data[V_uci][0], CLVolA_Per_Pass_M, C_W_SafeFlag);					/*写本月A/B/C相统计数据*/
			InF_Write_Data(C_Msg_VoltageQualifiedRateMetering, V_ulOADVol_Per_Pass_0_Freeze[V_uci], &V_ucVol_Per_Pass_Data_D[V_uci][0], CLVolA_Per_Pass_D, C_W_SafeFlag);			/*写日A/B/C相统计数据*/
		}
	}
}

/*******************************************************************************
函数原型: void MF_Calculate
功能描述: 分相电压合格率数据计算
输入参数: *pV_Data 各相电压合格率统计数据指针；V_usCurrentVoltage 各相当前电压；V_usVoltage_UpLim 电压上限；
          V_usVoltage_LowLim 电压下限；
输出参数: *pV_Data 各相电压合格率统计数据；
返回参数: 无
调用位置:
备    注: 电压合格率数据统计函数Msg_VoltageQualifiedRateMetering计算A、B、C相
         电压合格率数据时分别调用。
*******************************************************************************/
void MF_Calculate(uchar8 *pV_Data, ushort16 V_usCurrentVoltage, ushort16 V_usVoltage_UpLim, ushort16 V_usVoltage_LowLim)
{
	ulong32 V_ulMonitorTime, V_ulOverUpTime, V_ulOverLowTime;
	ushort16 V_usPassRate, V_usOverRate;
	ulong64 V_ulTemp;

	PF_BufferXToUlong32(pV_Data, &V_ulMonitorTime, CLPer_Pass_MonitorTime);
	V_ulMonitorTime++;						/*电压监测时间+1*/
	PF_Ulong32ToBufferX(pV_Data, &V_ulMonitorTime, CLPer_Pass_MonitorTime);

	PF_BufferXToUlong32( (pV_Data + CLPer_Pass_MonitorTime + CLPer_Pass_PassRate + CLPer_Pass_OverRate), &V_ulOverUpTime, CLPer_Pass_OverUpTime);						/*电压超上限时间*/
	PF_BufferXToUlong32( (pV_Data + CLPer_Pass_MonitorTime + CLPer_Pass_PassRate + CLPer_Pass_OverRate + CLPer_Pass_OverUpTime), &V_ulOverLowTime, CLPer_Pass_OverLowTime);		/*电压超下限时间*/
	if (V_usCurrentVoltage > V_usVoltage_UpLim)
	{
		V_ulOverUpTime++;					/*电压超上限时间+1*/
		PF_Ulong32ToBufferX( (pV_Data + CLPer_Pass_MonitorTime + CLPer_Pass_PassRate + CLPer_Pass_OverRate), &V_ulOverUpTime, CLPer_Pass_OverUpTime);
	}
	else if (V_usCurrentVoltage < V_usVoltage_LowLim)
	{
		V_ulOverLowTime++;					/*电压超下限时间+1*/
		PF_Ulong32ToBufferX( (pV_Data + CLPer_Pass_MonitorTime + CLPer_Pass_PassRate + CLPer_Pass_OverRate + CLPer_Pass_OverUpTime), &V_ulOverLowTime, CLPer_Pass_OverLowTime);
	}

	V_ulTemp = V_ulOverUpTime + V_ulOverLowTime;
	V_usOverRate = (ushort16)( (V_ulTemp * 100000 / V_ulMonitorTime + 5) / 10 );														/*计算电压超限率保留两位小数*/
	PF_Ushort16ToBuffer2( (pV_Data + CLPer_Pass_MonitorTime + CLPer_Pass_PassRate), &V_usOverRate);

	V_usPassRate = 10000 - V_usOverRate;	/*计算电压合格率*/
	PF_Ushort16ToBuffer2( (pV_Data + CLPer_Pass_MonitorTime), &V_usPassRate);

}

/*******************************************************************************
函数原型: void InF_ClearVoltageQR_Data_D(void)
功能描述: 日冻结电压合格率数据清零
输入参数: 无
输出参数: 无
返回参数: 无
调用位置:
备    注:
*******************************************************************************/
void InF_ClearVoltageQR_Data_D(void)
{
	uchar8	V_ucData_Buff[CLVol_Per_Pass_D] = {0};

	InF_Write_Data(C_Msg_VoltageQualifiedRateMetering, CVolA_Per_Pass_0_Freeze, V_ucData_Buff, CLVolA_Per_Pass_D, C_W_SafeFlag);	/*写日A相统计数据*/
	InF_Write_Data(C_Msg_VoltageQualifiedRateMetering, CVolB_Per_Pass_0_Freeze, V_ucData_Buff, CLVolB_Per_Pass_D, C_W_SafeFlag);	/*写日B相统计数据*/
	InF_Write_Data(C_Msg_VoltageQualifiedRateMetering, CVolC_Per_Pass_0_Freeze, V_ucData_Buff, CLVolC_Per_Pass_D, C_W_SafeFlag);	/*写日C相统计数据*/
}
