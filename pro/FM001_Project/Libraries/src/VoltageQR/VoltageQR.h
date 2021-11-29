/********************************************************************************************
Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     VoltageQR.c
Version:       V1
Author:
Date:          2014-3-12
Description:   ��ѹ�ϸ���
---------------------------------------------------------------------------------------------
History1:      ��1���޸�
����1. Date:
       Author:
       Modification:
---------------------------------------------------------------------------------------------
����2. Date:
       Author:
       Modification:
---------------------------------------------------------------------------------------------
History2:      ��2���޸�
����1. Date:
       Author:
       Modification:
---------------------------------------------------------------------------------------------
����2. Date:
       Author:
       Modification:
---------------------------------------------------------------------------------------------
History3:      ��3���޸�
����1. Date:2021.09.22
       Author:zlj
       Modification:
---------------------------------------------------------------------------------------------
����2. Date:
       Author:
       Modification:
********************************************************************************************/
#ifndef __VoltageQR_H
#define __VoltageQR_H

void Msg_VoltageQualifiedRateMetering(void);
void MF_Calculate(uchar8 *pV_Data, ushort16 V_usCurrentvoltage, ushort16 V_usVoltage_UpLim, ushort16 V_usVoltage_LowLim);
void SF_ClearVoltageQualifiedRate_Data(void);

#define	C_Year_hi8					6				/*��ǰ��ݸ�8λ*/
#define	C_Year_lo8					5				/*��ǰ��ݵ�8λ*/
#define	C_Month						4				/*��ǰ�·�*/
#define	C_Day						3				/*��ǰ��*/
#define	C_Hour						2				/*��ǰСʱ*/
#define	C_Minute					1				/*��ǰ����*/

#define	C_offVoltage_UpLim			0	/*��ѹ����ƫ��*/
#define	C_offVoltage_LowLim			1
#define	C_offVoltage_Check_UpLim	2
#define	C_offVoltage_Check_LowLim	3

#define	C_offA_Volt				0	/*A��ѹƫ��*/
#define	C_offB_Volt				1
#define	C_offC_Volt				2

#endif
