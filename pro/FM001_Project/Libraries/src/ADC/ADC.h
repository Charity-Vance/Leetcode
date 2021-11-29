
///*****************************************************************************************///
///*Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     ADC.h
///*Version:       V1
///*Date:          2014-3-12
///*Description:   
///*Function List: 
///*****************************************************************************************///
#ifndef	__ADC_H
#define __ADC_H

#include "IO.h"

static	ulong32	SV_ulTemp_ADC;
extern uchar8 GV_ucTime;

#define C_Tem8s   8
#define C_Tem10s  10
///*****************************************************************************************///
///*****************************************************************************************///
#define	C_RTCBATT				0x01				///*����3.6Vʱ�ӵ�ص�A/Dת��*///
#define	C_WAKEUPBATT			0x02				///*����6Vͣ�绽�ѵ�ص�A/Dת��*///

#define	ADCChannel13			(ulong32)13			///*3.6V��ص�1ת������*///
#define	ADCChannel20			(ulong32)20<<5		///*6V��ص�2ת������*///
#define	ADCChannel9				(ulong32)9<<5		///*6V��ص�2ת������*///


typedef struct
{
	uchar8	Timer;		///*��ʱ������1sΪ��λ*///
	uchar8	HStatus;	///*��ʷ״̬*///
}Str_ADC_Type1;
static Str_ADC_Type1 Str_RTCBATT;			///*ʱ�ӵ��*///
static Str_ADC_Type1 Str_WAKEUPBATT;		///*���ѵ��*///

#define	C_BATTErr_Times			0x03		///*����3�ε�ص�ѹ�ͣ���Ϊ����*///
#define	C_RTCBATT_Value			0x0200		///*ʱ�ӵ�ص�ѹ����02.00V��Ϊ����*///
#define	C_WAKEUPBATT_Value		0x0450		///*���ѵ�ص�ѹ����04.50V��Ϊ����*///
#define C_ADC_Delay				8000			///*ADCת����ʱ����2usΪ��λ*///
#define	C_WakeUpBatt_LowerLimit	350			///*���ѵ�ص��ڴ�ֵ��ת��ֵ����*///
#define	C_RTCBatt_LowerLimit	100			///*ʱ�ӵ�ص��ڴ�ֵ��ת��ֵ����*///
#define	C_WakeUpBatt_UpperLimit	675			///*���ѵ�ظ��ڴ�ֵ��ת��ֵ�̶�*///
#define	C_RTCBatt_UpperLimit	370			///*ʱ�ӵ�ظ��ڴ�ֵ��ת��ֵ�̶�*///

#define	C_Cap_LowerLimit	150			///*�������ݵ��ڴ�ֵ1.5V��ת��ֵ���㣬�����������ݣ���ѹ��Ϊ0����*///
#define	C_CapReport_LowerLimit	0x0300		/*�������ݵ��ڴ�ֵ3V�������ʱҲû��ͣ�糭���أ������ϱ��͵����¼���¼*/

#define	C_RTCBatt_WarnLimit		250			///*ʱ�ӵ�ص��ڴ�ֵ������*///
#define	C_WakeUpBatt_WarnLimit	500			///*���ѵ�ص��ڴ�ֵ������*///

#define	C_BATT_ERR							0x86	///*RTC���ϣ�RTC�����ϱ���*///
#define	C_BATT_OK							0x00	///*RTC������RTC����δ�ϱ���*///
#define	C_RTCBattERR_MeterWorkState			0x04	///*�������������1�е�ʱ�ӵ�ع���λ*///
#define	C_WakeUpBattERR_MeterWorkState		0x08	///*�������������1�еĳ����ع���λ*///

#define C_BattChange						0x86	///*���״̬�б仯*///
#define	C_RTCBattChange_Err					0x06	///*ʱ�ӵ�ر�ΪǷѹ*///
#define	C_RTCBattChange_Ok					0x08	///*ʱ�ӵ�ر�Ϊ����*///
#define	C_WakeupBattChange_Err				0x80	///*���ѵ�ر�ΪǷѹ*///
#define	C_WakeupBattChange_Ok				0x60	///*���ѵ�ر�Ϊ����*///




#define	C_ADC_SMPR0		(ADC_SMPR3_SMP31_2|ADC_SMPR3_SMP30_2)
#define	C_ADC_SMPR1		(ADC_SMPR1_SMP29_2|ADC_SMPR1_SMP28_2|ADC_SMPR1_SMP27_2|ADC_SMPR1_SMP26_2|ADC_SMPR1_SMP25_2|ADC_SMPR1_SMP24_2|ADC_SMPR1_SMP23_2|ADC_SMPR1_SMP22_2|ADC_SMPR1_SMP21_2|ADC_SMPR1_SMP20_2)
#define	C_ADC_SMPR2		(ADC_SMPR2_SMP19_2|ADC_SMPR2_SMP18_2|ADC_SMPR2_SMP17_2|ADC_SMPR2_SMP16_2|ADC_SMPR2_SMP15_2|ADC_SMPR2_SMP14_2|ADC_SMPR2_SMP13_2|ADC_SMPR2_SMP12_2|ADC_SMPR2_SMP11_2|ADC_SMPR2_SMP10_2)
#define	C_ADC_SMPR3		(ADC_SMPR3_SMP9_2|ADC_SMPR3_SMP8_2|ADC_SMPR3_SMP7_2|ADC_SMPR3_SMP6_2|ADC_SMPR3_SMP5_2|ADC_SMPR3_SMP4_2|ADC_SMPR3_SMP3_2|ADC_SMPR3_SMP2_2|ADC_SMPR3_SMP1_2|ADC_SMPR3_SMP0_2)
///*****************************************************************************************///
#define	C_HSE_STARTUP_TIMEOUT		0x500
///*****************************************************************************************///

void SF_ADC_Set(uchar8 V_ucFlag);


#define	Set_IO_RTCBatt_Analong()	{ulong32 SV_ulTemp_ADC;\
									IO_RTCBATT->PUPDR &= RTCBATT_NOPUPD;\
									SV_ulTemp_ADC	 = IO_RTCBATT->MODER;\
									SV_ulTemp_ADC &= RTCBATT_IN_MODE;\
									SV_ulTemp_ADC |= RTCBATT_ANALOG_MODE;\
									IO_RTCBATT->MODER = SV_ulTemp_ADC;\
									IO_RTCBATT->PUPDR &= RTCBATT_NOPUPD;}

#define	Set_IO_WakeBatt_Analong()	{ulong32 SV_ulTemp_ADC1;\
									IO_WAKEBATT->PUPDR &= WAKEBATT_NOPUPD;\
									SV_ulTemp_ADC1 = IO_WAKEBATT->MODER;\
									SV_ulTemp_ADC1 &= WAKEBATT_IN_MODE;\
									SV_ulTemp_ADC1 |= WAKEBATT_ANALOG_MODE;\
									IO_WAKEBATT->MODER = SV_ulTemp_ADC1;\
									IO_WAKEBATT->PUPDR &= WAKEBATT_NOPUPD;}
#define	Set_IO_Cap_Analong()	{ulong32 SV_ulTemp_ADC2;\
									IO_CAP->PUPDR &= CAP_NOPUPD;\
									SV_ulTemp_ADC2 = IO_CAP->MODER;\
									SV_ulTemp_ADC2 &= CAP_IN_MODE;\
									SV_ulTemp_ADC2 |= CAP_ANALOG_MODE;\
									IO_CAP->MODER = SV_ulTemp_ADC2;\
									IO_CAP->PUPDR &= CAP_NOPUPD;}

#endif
