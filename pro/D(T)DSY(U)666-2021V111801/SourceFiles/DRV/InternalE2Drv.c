/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    InternalE2Drv.c                                                                          
**** Brief:       类E2驱动文件                                                                    
**** Author:      peter.he@chint.com                                                                 
**** Version:     V1.0                                                                               
**** Date:        2016-7-14                                                                          
****                                                                                                 
**** note:修改历史记录列表，每条修改记录应包括修改日期、修改者                                          
**** 1.  Author:                                                                                     
****     Version:                                                                                    
****     Date :                                                                                      
**** 2.  Author:                                                                                     
****     Version:                                                                                       
****     Date:
****                                                                                        
****  addtogroup:Library                                                             
**********************************************************************************************************/

/*--------------------------------- 文件功能说明 -------------------------------------------------------*/
/*
 *  该文件所有函数的前缀为xxxx_
 *  文件主函数和对外函数需放在文件的首部，并且主函数需要放在第一个位置;
 *  函数注释采用标准模板，函数内部注释采用//;
 *  对于注释较多的部分，可以增加一个注释符，然后详细说明放在文件的尾部;
 *--------------------------------- 文件功能说明 -------------------------------------------------------*/
 
 // 79f7021A 类E2地址：0000-0FFF 每512字节为一个扇区，总共8个扇区,其寿命标称为10W次，但是实际测试（海外张龙）在全温度范围内
 // 只能按3W次计算
 /*
 --------------------------XPAGE 说明 -----------------------------------
 F7H    第7位     第6位   第5位    第4位    第3位  第2位   第1位   第0位
XPAGE  XPAGE.7  XPAGE.6  XPAGE.5 XPAGE.4 XPAGE.3 XPAGE.2 XPAGE.1 XPAGE.0

位编号 位符号       说明
7-4   XPAGE[7:4]   在擦除/编程块区时无意义
3-1   XPAGE[3:1]   被擦除/编程的块区号， 0000代表块0， 依此类推。
0     XPAGE0       被擦除/编程的存储单元高位地址

@brief --类EEPROM块区对应XPAGE[3:0]为0000-0111的块。 类EEPROM块区的访问可通过指令“MOVC A， @A+DPTR”或“MOVC A，
@A+PC”实现， 注意： 需要将FAC位（FLASHCON.0） 置1。
---------------------------IB_OFFSET 说明 ----------------------------------
EEH         第7位       第6位       第5位       第4位       第3位        第2位        第1位       第0位
IB_OFFSET  IBS_EOTF.7F IBS_EOTF.6F IBS_EOTF.5F IBS_EOTF.4F IBS_EOTF.3F IBS_EOTF.2F IBS_EOTF.1F IBS_EOTF.0

位编号 位符号           说明
7-0    IB_OFFSET[7:0]  被擦除/编程的块单元地址

@brief -- IB_OFFSET[7:0]共8位， 可以表示1个块区内全部256个字节的偏移量。
 */
/**有形参的函数格式:*/
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    xx任务处理函数
 *
 *  @param    xx :
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
/**无形参的函数格式:*/
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    上电所有口线配置成初始状态，后面可根据需要开启和配置
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
 
 
/*----------------< 包含文件 >----------------------------------*/

#include "..\SourceFiles\PUB\Include.h"

/*----------------< 宏定义区 >----------------------------------*/


/*----------------< 常量定义 >----------------------------------*/


/*----------------< 变量定义 >----------------------------------*/


/*----------------< 函数声明 >----------------------------------*/
INT8U Hal_EraseEEPROM(INT16U Dst);
void Hal_EraseFlashSector(INT16U adr, INT8U dat, INT8U sta);
INT8U Hal_ReadEEPROM(INT8U  *Dst, INT16U Src, INT16U Len);
INT8U Hal_ReadFlash_byte(INT16U adr, INT8U sta);
INT8U Hal_WriteEEPROM(INT16U Dst, INT8U  *Src, INT16U Len);
void Hal_WriteFlash_byte(INT16U adr, INT8U dat, INT8U sta);

/*----------------< 函数定义 >----------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    类EEPROM写1个字节
 *
 *  @param    xx :
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/

#pragma SAVE
#pragma OT(0)
void Hal_WriteFlash_byte(INT16U adr, INT8U dat, INT8U sta)
{
//	_push_(IEN0);
	EA = 0;
	
	IB_DATA = dat;
	IB_OFFSET = (INT8U)(adr&0xFF);
	XPAGE = (INT8U)(adr>>8);
	FLASHCON = 1;
	

		IB_CON1 = 0x6E;
		IB_CON2 = 0x05;
		IB_CON3 = 0x0A;
		IB_CON4 = 0x09;
	if(sta == FLASH_RW_ENABLE)
	{	
		IB_CON5 = 0x06;
		_nop_();
		_nop_();
		_nop_();
		_nop_();
	}
	
	FLASHCON = 0;
	XPAGE = 0;
	EA = 1;
//	_pop_(IEN0);
}
#pragma RESTORE

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    类EEPROM写指定长度数据
 *
 *  @param    xx :
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/

INT8U Hal_WriteEEPROM(INT16U Dst, INT8U  *Src, INT16U Len)
{
    INT8U xdata Dat;
		/* 需要增加掉电判断 */
	PASLO_POWER_SWITCH_ON();
//	#if(METER_TYPE==METER_TYPE_DDSYU666)   //导轨表低电压检测为3.00V
		LPDCON2 = ( LPDCON2_LPD2EN  | LPDCON2_LPDS_300 );	// 允许低电压检测，开LPD2,禁止LPD3检测，电压3.00V 约90%
//	#else
//		LPDCON2 = ( LPDCON2_LPD2EN  | LPDCON2_LPDS_315 );	// 允许低电压检测，开LPD2,禁止LPD3检测，电压3.15V 约95%
//	#endif
	NOP();
	NOP();
	if ( (LPDCON2 & LPDCON2_LPD2F) == LPDCON2_LPD2F )	///* 掉电了就直接退出 *///
	{
		return 0xFF;;
	}  ////xww
	
	if(C_SafeByte!=GStr_Flag.ucWrE2promSafeByte)//安全流程字判断//	
	{
		return 0xFF;
	}

    if ((Dst + Len) > 4096)
    {
        return (0xFF);
    }
    while (Len>0)
    {
        Dat = *Src;
        Hal_WriteFlash_byte(Dst, Dat, FLASH_RW_ENABLE);
        Dst++;
        Src++;
        Len--;
    }
	
    return(0x00);
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    类EEPROM读取1个字节
 *
 *  @param    adr : 要读取的数据地址 2字节
 *  @param    sta : 状态控制字节
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/

INT8U Hal_ReadFlash_byte(INT16U adr, INT8U sta)
{
    INT8U  t_tmp = 0;
	
    if (sta == FLASH_RW_ENABLE)
    {
        //_push_(IEN0);
        EA = 0;
        FLASHCON = 1;
        t_tmp = *((INT8U code*)adr);
        FLASHCON = 0x00;
		EA = 1;
        //_pop_(IEN0);
   }
   
   return t_tmp;
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    读取指定长度类E2数据内容
 *
 *  @param    Dst : 数据存放缓存指针
 *  @param    Src : 要读取数据的地址
 *  @param    Len : 要读取的数据长度
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/

INT8U Hal_ReadEEPROM(INT8U  *Dst, INT16U Src, INT16U Len)
{
	/* 需要增加掉电判断 */
	PASLO_POWER_SWITCH_ON();
//	#if(METER_TYPE==METER_TYPE_DDSYU666)   //导轨表低电压检测为3.00V
		LPDCON2 = ( LPDCON2_LPD2EN  | LPDCON2_LPDS_300 );	// 允许低电压检测，开LPD2,禁止LPD3检测，电压3.00V 约90%
//	#else
//		LPDCON2 = ( LPDCON2_LPD2EN  | LPDCON2_LPDS_315 );	// 允许低电压检测，开LPD2,禁止LPD3检测，电压3.15V 约95%
//	#endif
	NOP();
	NOP();
	if ( (LPDCON2 & LPDCON2_LPD2F) == LPDCON2_LPD2F )	///* 掉电了就直接退出 *///
	{
		return 0xFF;;
	}  ////xww

    if ((Src + Len) > 4096)
    {
        return 0xFF;
    }

    while (Len > 0)
    {
        *Dst = Hal_ReadFlash_byte(Src, FLASH_RW_ENABLE);
        Dst++;
        Src++;
        Len--;
    }
	
    return 0x00;
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    擦除类E2指定页
 *
 *  @param    adr : 地址
 *  @param    dat : 数据（通常为0x00?)
 *  @param    sta : 状态控制字节
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/

#pragma SAVE
#pragma OT(0)
void Hal_EraseFlashSector(INT16U adr, INT8U dat, INT8U sta)
{
		/* 需要增加掉电判断 */
	/* 需要增加掉电判断 */
	PASLO_POWER_SWITCH_ON();
//	#if(METER_TYPE==METER_TYPE_DDSYU666)   //导轨表低电压检测为3.00V
		LPDCON2 = ( LPDCON2_LPD2EN  | LPDCON2_LPDS_300 );	// 允许低电压检测，开LPD2,禁止LPD3检测，电压3.00V 约90%
//	#else
//		LPDCON2 = ( LPDCON2_LPD2EN  | LPDCON2_LPDS_315 );	// 允许低电压检测，开LPD2,禁止LPD3检测，电压3.15V 约95%
//	#endif
	NOP();
	NOP();
	if ( (LPDCON2 & LPDCON2_LPD2F) == LPDCON2_LPD2F )	///* 掉电了就直接退出 *///
	{
		return ;
	}  ////xww
	if(C_SafeByte!=GStr_Flag.ucWrE2promSafeByte)//安全流程字判断//	
	{
		return ;
	}
	
//	_push_(IEN0);
	EA = 0;
	IB_DATA = dat;
	IB_OFFSET = (INT8U)(adr&0xFF);
	XPAGE = (INT8U)(adr>>8);
	FLASHCON = 1;
	

		IB_CON1 = 0xE6;
		IB_CON2 = 0x05;
		IB_CON3 = 0x0A;
		IB_CON4 = 0x09;
		
	if (sta == FLASH_RW_ENABLE)
	{		
		IB_CON5 = 0x06;
		_nop_();
		_nop_();
		_nop_();
		_nop_();
	}
	
	FLASHCON = 0;
	XPAGE = 0;
	EA = 1;
//	_pop_(IEN0);
}
#pragma RESTORE

///*------------------------------------------------------------------------------------------------------*/
///**
// *  @brief    类EEPROM读取1个字节
// *
// *  @param    Dst : 地址
// *
// *  @return   xx
// *
// *  @note     xx
// *
// */
///*------------------------------------------------------------------------------------------------------*/

//INT8U Hal_EraseEEPROM(INT16U Dst)
//{
//    if (Dst >= 4096)
//    {
//        return (0xFF);
//    }
//    Hal_EraseFlashSector(Dst, 0x00, FLASH_RW_ENABLE);

//    return (0x00);
//}
