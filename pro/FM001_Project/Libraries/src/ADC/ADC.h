
///*****************************************************************************************///
///*Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
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
#define	C_RTCBATT				0x01				///*进行3.6V时钟电池的A/D转换*///
#define	C_WAKEUPBATT			0x02				///*进行6V停电唤醒电池的A/D转换*///

#define	ADCChannel13			(ulong32)13			///*3.6V电池第1转换序列*///
#define	ADCChannel20			(ulong32)20<<5		///*6V电池第2转换序列*///
#define	ADCChannel9				(ulong32)9<<5		///*6V电池第2转换序列*///


typedef struct
{
	uchar8	Timer;		///*计时器：以1s为单位*///
	uchar8	HStatus;	///*历史状态*///
}Str_ADC_Type1;
static Str_ADC_Type1 Str_RTCBATT;			///*时钟电池*///
static Str_ADC_Type1 Str_WAKEUPBATT;		///*唤醒电池*///

#define	C_BATTErr_Times			0x03		///*连续3次电池电压低，认为故障*///
#define	C_RTCBATT_Value			0x0200		///*时钟电池电压低于02.00V认为故障*///
#define	C_WAKEUPBATT_Value		0x0450		///*唤醒电池电压低于04.50V认为故障*///
#define C_ADC_Delay				8000			///*ADC转换延时：以2us为单位*///
#define	C_WakeUpBatt_LowerLimit	350			///*唤醒电池低于此值，转换值清零*///
#define	C_RTCBatt_LowerLimit	100			///*时钟电池低于此值，转换值清零*///
#define	C_WakeUpBatt_UpperLimit	675			///*唤醒电池高于此值，转换值固定*///
#define	C_RTCBatt_UpperLimit	370			///*时钟电池高于此值，转换值固定*///

#define	C_Cap_LowerLimit	150			///*超级电容低于此值1.5V，转换值清零，不焊超级电容，电压不为0问题*///
#define	C_CapReport_LowerLimit	0x0300		/*超级电容低于此值3V，如果此时也没有停电抄表电池，不做上报和掉电事件记录*/

#define	C_RTCBatt_WarnLimit		250			///*时钟电池低于此值，故障*///
#define	C_WakeUpBatt_WarnLimit	500			///*唤醒电池低于此值，故障*///

#define	C_BATT_ERR							0x86	///*RTC故障；RTC故障上报过*///
#define	C_BATT_OK							0x00	///*RTC正常；RTC故障未上报过*///
#define	C_RTCBattERR_MeterWorkState			0x04	///*电表运行特征字1中的时钟电池故障位*///
#define	C_WakeUpBattERR_MeterWorkState		0x08	///*电表运行特征字1中的抄表电池故障位*///

#define C_BattChange						0x86	///*电池状态有变化*///
#define	C_RTCBattChange_Err					0x06	///*时钟电池变为欠压*///
#define	C_RTCBattChange_Ok					0x08	///*时钟电池变为正常*///
#define	C_WakeupBattChange_Err				0x80	///*唤醒电池变为欠压*///
#define	C_WakeupBattChange_Ok				0x60	///*唤醒电池变为正常*///




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
