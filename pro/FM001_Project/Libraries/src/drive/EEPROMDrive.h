
///*****************************************************************************************///
///*Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
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

//static ulong32	SV_EE_SFRBuff;			///*用于SFR的读->修改->写*///

#define	C_EE_SlaveAddr_Write		0xA0		///*写EE的从地址*///
#define	C_EE_SlaveAddr_Read			0xA1		///*读EE的从地址*///
#define	C_EE_MostSignificantBit		0x80		///*最高有效位*///
#define C_E2_Max_StopTimes			20			///*发stop时最多次数*///
#define	C_E2_BitLen					8			///*I2C传输数据的数据长度：1字节*///
#define	C_WriteZero					0			///*专门用于E2清零*///
#define C_E2_Max_Len				128			///*一次写E2最大长度*///
#define	C_E2_InternalPageAddr		0x007f		///*页内最高地址：每页128字节*///
#define C_E2_Write_Delay			10500		///*写E2最多需要延时10.5ms=10500us*///
#define	C_E2_MaxLen					1024		///*操作EE的最大长度*///
#define C_E2_Busy					0x68		/* 表示E2处于忙状态 */
#define C_E2_Idle					0x00		/* 表示E2处于空闲状态 */
///*io 口线操作的宏定义*///
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
