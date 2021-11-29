
///*****************************************************************************************///
///*Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     
///*Version:       V1
///*Date:          2014-3-12
///*Description:   
///*Function List: 
///*****************************************************************************************///
#ifndef	__EEPROMDrive_H
#define	__EEPROMDrive_H

#include "Public.h"
#include "IO.h"
#include "Timer.h"

//static ulong32	SV_EE_SFRBuff;			///*����SFR�Ķ�->�޸�->д*///

#define	C_EE_SlaveAddr_Write		0xA0		///*дEE�Ĵӵ�ַ*///
#define	C_EE_SlaveAddr_Read			0xA1		///*��EE�Ĵӵ�ַ*///
#define	C_EE_MostSignificantBit		0x80		///*�����Чλ*///
#define C_E2_Max_StopTimes			20			///*��stopʱ������*///
#define	C_E2_BitLen					8			///*I2C�������ݵ����ݳ��ȣ�1�ֽ�*///
#define	C_WriteZero					0			///*ר������E2����*///
#define C_E2_Max_Len				128			///*һ��дE2��󳤶�*///
#define	C_E2_InternalPageAddr		0x007f		///*ҳ����ߵ�ַ��ÿҳ128�ֽ�*///
#define C_E2_Write_Delay			10500		///*дE2�����Ҫ��ʱ10.5ms=10500us*///
#define	C_E2_MaxLen					1024		///*����EE����󳤶�*///
#define C_E2_Busy					0x68		/* ��ʾE2����æ״̬ */
#define C_E2_Idle					0x00		/* ��ʾE2���ڿ���״̬ */
///*io ���߲����ĺ궨��*///
///*******************************************************************///
#define EE_IO_Init				{IO_EESCL->MODER &= EESCL_IN_MODE;\
									IO_EESCL->INEN |= EESCL_INOn;\
														IO_EESDA->MODER &= EESDA_IN_MODE;\
														IO_EESDA->INEN |= EESDA_INOn;}

#define EE_Set_Scl_Input		{IO_EESCL->MODER &= EESCL_IN_MODE;\
								IO_EESCL->INEN |= EESCL_INOn;\
														 IO_EESCL->PUPDR &= EESCL_NOPUPD;}

#define EE_Set_Scl_Output		{ulong32 SV_EE_SFRBuff;\
								SV_EE_SFRBuff = IO_EESCL->MODER;\
								SV_EE_SFRBuff &= EESCL_IN_MODE;\
								SV_EE_SFRBuff |= EESCL_OUT_MODE;\
								IO_EESCL->MODER = SV_EE_SFRBuff;\
								IO_EESCL->OTYPER &= EESCL_OUTPUT_PP;}

#define EE_Scl_Output_0			{IO_EESCL->BSRR = EESCLRESET;}

#define EE_Scl_Output_1			{IO_EESCL->BSETH = EESCLSET;}
///*******************************************************************///

#define EE_Set_Sda_Input		{IO_EESDA->MODER &= EESDA_IN_MODE;\
								IO_EESDA->INEN |= EESDA_INOn;\
								IO_EESDA->PUPDR &= EESDA_NOPUPD;}

#define EE_Set_Sda_Output		{IO_EESDA->MODER |= EESDA_OUT_MODE;\
								IO_EESDA->OTYPER |= EESDA_OUTPUT_OD;}

#define EE_Sda_Output_0			{IO_EESDA->BSRR = EESDARESET;}

#define EE_Sda_Output_1			{IO_EESDA->BSETH = EESDASET;}

#define	EE_Read_Sda				(IO_EESDA->IDR & EESDA_SELECT)
///*******************************************************************///
#define EE_Set_WP_Input			{IO_EEWP->MODER &= EEWP_IN_MODE;\
									IO_EEWP->INEN |= EEWP_INOn;\
								IO_EEWP->PUPDR &= EEWP_NOPUPD;}

#define EE_Set_WP_Output		{ulong32 SV_EE_SFRBuff;\
								SV_EE_SFRBuff = IO_EEWP->MODER;\
								SV_EE_SFRBuff &= EEWP_IN_MODE;\
								SV_EE_SFRBuff |= EEWP_OUT_MODE;\
								IO_EEWP->MODER = SV_EE_SFRBuff;\
								IO_EEWP->OTYPER &= EEWP_OUTPUT_PP;}

#define EE_WP_Output_0			{IO_EEWP->BSRR = EEWPRESET;}

#define EE_WP_Output_1			{IO_EEWP->BSETH = EEWPSET;}
///*******************************************************************///
#endif
