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
#ifndef __VoltageQR_H
#define __VoltageQR_H

void Msg_VoltageQualifiedRateMetering(void);
void MF_Calculate(uchar8 *pV_Data, ushort16 V_usCurrentvoltage, ushort16 V_usVoltage_UpLim, ushort16 V_usVoltage_LowLim);
void SF_ClearVoltageQualifiedRate_Data(void);

#define	C_Year_hi8					6				/*当前年份高8位*/
#define	C_Year_lo8					5				/*当前年份低8位*/
#define	C_Month						4				/*当前月份*/
#define	C_Day						3				/*当前日*/
#define	C_Hour						2				/*当前小时*/
#define	C_Minute					1				/*当前分钟*/

#define	C_offVoltage_UpLim			0	/*电压上限偏移*/
#define	C_offVoltage_LowLim			1
#define	C_offVoltage_Check_UpLim	2
#define	C_offVoltage_Check_LowLim	3

#define	C_offA_Volt				0	/*A电压偏移*/
#define	C_offB_Volt				1
#define	C_offC_Volt				2

#endif
