
///*****************************************************************************************///
///*Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     
///*Version:       V1
///*Date:          2014-3-12
///*Description:   
///*Function List: 
///*****************************************************************************************///
#ifndef	__FlashDrive_H
#define	__FlashDrive_H

#include "Public.h"
#include "IO.h"
#include "Timer.h"

//static ulong32	SV_Flash_SFRBuff;			///*����SFR�Ķ�->�޸�->д*///



#define C_FLASH_CMD_WREN			0x06			///*erite enable *///
#define C_FLASH_CMD_WRDI			0x04			///*write disble *///
#define C_FLASH_CMD_RDID_ANY		0x9F			///*read id      *///
#define C_FLASH_CMD_RDSR			0x05			///* read status register*///
#define C_FLASH_CMD_WRSR			0x01			///* write status register*///
#define C_FLASH_CMD_READ			0x03			///* read any address  *///
#define C_FLASH_CMD_PP				0x02			///*page program��  max 256 byte*///
#define C_FLASH_CMD_SSE				0x20			///*subsector erase 4k bytes erase*///
#define C_FLASH_CMD_DOFR			0x3B			///* dual output fast read  *///

#define C_FLASH_STATUS_WIP			0x01			///*WRITE IN PROGRESS  BIT *///
#define C_FLASH_STATUS_WEL			0x02			///*WRITE ENABLE LATCH BIT *///
//#define C_FLASH_STATUS_REASONABLE	0x40			///*bit6�̶�Ϊ0*///
//#define C_BUSY						8				///*device busy *///
//#define C_DeviceError				9
//#define C_Device_Busy				10

#define C_FLASH_DATA_DUMMY			0x00			///* FastRead��ʱ�򷢵�dummy�ֽ� *///
#define	C_FLASH_WaitTime			2500			///*��ѯflash�Ƿ���е���ʱ*///
#define	C_FLASH_WaitLimited			80				///*�ȴ�Flash�����ʱ�䣺80*2.5ms=200ms*///

#define	C_ReadFlash_MaxLen			1026			///*��Flash��󳤶�����*///
#define	C_FlashAddr_Invalid			0xff800000		///*Flash����Ч��ַ��Flash��Ч��ַ23λ*///
#define	C_FlashPageLen				256				///*Flashҳ��ַ�ĳ��ȣ�256�ֽ�*///
#define C_Flash_Write_Delay			6000			///*дFlash��Ҫ��ʱ6ms=6000us*///

#define	C_FlashAddrFactory			0xffffffff		/* ���������flash���ұ�ţ����������ã������� */
///*******************************************************************///
#define Flash_Set_Sck_Input			{IO_FLASHSCK->MODER &= FLASHSCK_IN_MODE;\
									IO_FLASHSCK->INEN |= FLASHSCK_INOn;\
									IO_FLASHSCK->PUPDR &= FLASHSCK_NOPUPD;}

#define Flash_Set_Sck_Output		{ulong32 SV_Flash_SFRBuff;\
									SV_Flash_SFRBuff = IO_FLASHSCK->MODER;\
									SV_Flash_SFRBuff &= FLASHSCK_IN_MODE;\
									SV_Flash_SFRBuff |= FLASHSCK_OUT_MODE;\
									IO_FLASHSCK->MODER = SV_Flash_SFRBuff;\
									IO_FLASHSCK->OTYPER &= FLASHSCK_OUTPUT_PP;}

#define Flash_Sck_Output_0			{IO_FLASHSCK->BSRR = FLASHSCKRESET;}

#define Flash_Sck_Output_1			{IO_FLASHSCK->BSETH = FLASHSCKSET;}
///*******************************************************************///
#define Flash_Set_Sdo_Input			{IO_FLASHSDO->MODER &= FLASHSDO_IN_MODE;\
									IO_FLASHSDO->INEN |= FLASHSDO_INOn;\
									IO_FLASHSDO->PUPDR &= FLASHSDO_NOPUPD;}

#define Flash_Set_SDO_Output		{ulong32 SV_Flash_SFRBuff;\
									SV_Flash_SFRBuff = IO_FLASHSDO->MODER;\
									SV_Flash_SFRBuff &= FLASHSDO_IN_MODE;\
									SV_Flash_SFRBuff |= FLASHSDO_OUT_MODE;\
									IO_FLASHSDO->MODER = SV_Flash_SFRBuff;\
									IO_FLASHSDO->OTYPER &= FLASHSDO_OUTPUT_PP;}

#define Flash_Sdo_Output_0			{IO_FLASHSDO->BSRR = FLASHSDORESET;}

#define Flash_Sdo_Output_1			{IO_FLASHSDO->BSETH = FLASHSDOSET;}

#define	Flash_Read_Sdo				(IO_FLASHSDO->IDR & FLASHSDO_SELECT)
///*******************************************************************///
#define Flash_Set_Sdi_Input			{IO_FLASHSDI->MODER &= FLASHSDI_IN_MODE;\
									IO_FLASHSDI->INEN |= FLASHSDI_INOn;\
									IO_FLASHSDI->PUPDR &= FLASHSDI_NOPUPD;}


#define	Flash_Read_Sdi				(IO_FLASHSDI->IDR & FLASHSDI_SELECT)

#define Flash_Set_SDI_Output		{ulong32 SV_Flash_SFRBuff;\
									SV_Flash_SFRBuff = IO_FLASHSDI->MODER;\
									SV_Flash_SFRBuff &= FLASHSDI_IN_MODE;\
									SV_Flash_SFRBuff |= FLASHSDI_OUT_MODE;\
									IO_FLASHSDI->MODER = SV_Flash_SFRBuff;\
									IO_FLASHSDI->OTYPER &= FLASHSDI_OUTPUT_PP;}

#define Flash_Sdi_Output_0			{IO_FLASHSDI->BSRR = FLASHSDIRESET;}

#define Flash_Sdi_Output_1			{IO_FLASHSDI->BSETH = FLASHSDISET;}
///*******************************************************************///
#define Flash_Set_CS_Input			{IO_FLASHCS->MODER &= FLASHCS_IN_MODE;\
									IO_FLASHCS->INEN |= FLASHCS_INOn;\
									IO_FLASHCS->PUPDR &= FLASHCS_NOPUPD;}

#define Flash_Set_CS_Output			{ulong32 SV_Flash_SFRBuff;\
									SV_Flash_SFRBuff = IO_FLASHCS->MODER;\
									SV_Flash_SFRBuff &= FLASHCS_IN_MODE;\
									SV_Flash_SFRBuff |= FLASHCS_OUT_MODE;\
									IO_FLASHCS->MODER = SV_Flash_SFRBuff;\
									IO_FLASHCS->OTYPER &= FLASHCS_OUTPUT_PP;}

#define Flash_CS_Output_0			{IO_FLASHCS->BSRR = FLASHCSRESET;}

#define Flash_CS_Output_1			{IO_FLASHCS->BSETH = FLASHCSSET;}
///*******************************************************************///
#define Flash_IO_Init				{IO_FLASHSCK->MODER &= FLASHSCK_IN_MODE;\
									IO_FLASHSCK->INEN |= FLASHSCK_INOn;\
									IO_FLASHSDO->MODER &= FLASHSDO_IN_MODE;\
									IO_FLASHSDO->INEN |= FLASHSDO_INOn;\
									IO_FLASHSDI->MODER &= FLASHSDI_IN_MODE;\
									IO_FLASHSDI->INEN |= FLASHSDI_INOn;}




#endif
