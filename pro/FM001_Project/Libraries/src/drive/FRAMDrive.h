
///*****************************************************************************************///
///*Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     
///*Version:       V1
///*Date:          2014-3-12
///*Description:   
///*Function List: 
///*****************************************************************************************///
#ifndef	__FRAMPROMDrive_H
#define	__FRAMPROMDrive_H

#include "Public.h"
#include "IO.h"
#include "Timer.h"


#define	C_FRAM_SlaveAddr_Write			0xA0		///*дFRAM�Ĵӵ�ַ*///
#define	C_FRAM_SlaveAddr_Read				0xA1		///*��FRAM�Ĵӵ�ַ*///
#define	C_FRAM_MostSignificantBit		0x80		///*�����Чλ*///
#define C_FRAM_Max_StopTimes				20			///*��stopʱ������*///
#define	C_FRAM_BitLen								8			///*I2C�������ݵ����ݳ��ȣ�1�ֽ�*///
#define	C_WriteZero									0			///*ר������E2����*///
#define C_FRAM_Max_Len							128			///*һ��дE2��󳤶�*///
#define	C_FRAM_MaxBit								0xF800		///*2k��11λ��ַ*///
#define	C_FRAM_MaxAddr							0x07FF		///*2k����ַ*///
#define	C_FRAM_GetHighAddr					0x0700		///*��ȡ��λ��ַ����3λ*///
#define C_FRAM_Write_Delay					10500		///*дE2��Ҫ��ʱ6.5ms=6500us*///
#define	C_FRAM_MaxLen								1024			///*����FRAM����󳤶�*///
///*io ���߲����ĺ궨��*///
///*******************************************************************///
#define FRAM_IO_Init				{IO_FRAMSCL->MODER &= FRAMSCL_IN_MODE;\
								IO_FRAMSCL->INEN |= FRAMSCL_INOn;\
								IO_FRAMSDA->MODER &= FRAMSDA_IN_MODE;\
								IO_FRAMSDA->INEN |= FRAMSDA_INOn;}

#define FRAM_Set_Scl_Input		{IO_FRAMSCL->MODER &= FRAMSCL_IN_MODE;\
								IO_FRAMSCL->INEN |= FRAMSCL_INOn;\
								IO_FRAMSCL->PUPDR &= FRAMSCL_NOPUPD;}

#define FRAM_Set_Scl_Output		{ulong32 SV_FRAM_SFRBuff;\
								SV_FRAM_SFRBuff = IO_FRAMSCL->MODER;\
								SV_FRAM_SFRBuff &= FRAMSCL_IN_MODE;\
								SV_FRAM_SFRBuff |= FRAMSCL_OUT_MODE;\
								IO_FRAMSCL->MODER = SV_FRAM_SFRBuff;\
								IO_FRAMSCL->OTYPER &= FRAMSCL_OUTPUT_PP;}

#define FRAM_Scl_Output_0			{IO_FRAMSCL->BSRR = FRAMSCLRESET;}

#define FRAM_Scl_Output_1			{IO_FRAMSCL->BSETH = FRAMSCLSET;}
///*******************************************************************///

#define FRAM_Set_Sda_Input		{IO_FRAMSDA->MODER &= FRAMSDA_IN_MODE;\
								IO_FRAMSDA->INEN |= FRAMSDA_INOn;\
								IO_FRAMSDA->PUPDR &= FRAMSDA_NOPUPD;}

#define FRAM_Set_Sda_Output		{ulong32 SV_FRAM_SFRBuff;\
								SV_FRAM_SFRBuff = IO_FRAMSDA->MODER;\
								SV_FRAM_SFRBuff &= FRAMSDA_IN_MODE;\
								SV_FRAM_SFRBuff |= FRAMSDA_OUT_MODE;\
								IO_FRAMSDA->MODER = SV_FRAM_SFRBuff;\
								IO_FRAMSDA->OTYPER |= FRAMSDA_OUTPUT_OD;}
//#define FRAM_Set_Sda_Output		{IO_FRAMSDA->MODER |= FRAMSDA_OUT_MODE;\
//								IO_FRAMSDA->OTYPER |= FRAMSDA_OUTPUT_OD;\
//								IO_FRAMSDA->OSPEEDR &= FRAMSDA_SPEED_INIT;\
//								IO_FRAMSDA->OSPEEDR |= FRAMSDA_SPEED_2MHZ;}

#define FRAM_Sda_Output_0			{IO_FRAMSDA->BSRR = FRAMSDARESET;}

#define FRAM_Sda_Output_1			{IO_FRAMSDA->BSETH = FRAMSDASET;}

#define	FRAM_Read_Sda				(IO_FRAMSDA->IDR & FRAMSDA_SELECT)
///*******************************************************************///
#define FRAM_Set_WP_Input			{IO_FRAMWP->MODER &= FRAMWP_IN_MODE;\
									IO_FRAMWP->INEN |= FRAMWP_INOn;\
								IO_FRAMWP->PUPDR &= FRAMWP_NOPUPD;}

#define FRAM_Set_WP_Output		{ulong32 SV_FRAM_SFRBuff;\
								SV_FRAM_SFRBuff = IO_FRAMWP->MODER;\
								SV_FRAM_SFRBuff &= FRAMWP_IN_MODE;\
								SV_FRAM_SFRBuff |= FRAMWP_OUT_MODE;\
								IO_FRAMWP->MODER = SV_FRAM_SFRBuff;\
								IO_FRAMWP->OTYPER &= FRAMWP_OUTPUT_PP;}

#define FRAM_WP_Output_0			{IO_FRAMWP->BSRR = FRAMWPRESET;}

#define FRAM_WP_Output_1			{IO_FRAMWP->BSETH = FRAMWPSET;}
///*******************************************************************///
#endif
