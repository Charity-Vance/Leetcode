/****************************************************************************************
Copyright:	ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:	DataProcess.h
Version:	V1
Date:		2014-3-12
Description:
Function List:该部分主要是定义E2、Flash数据结构及DI标识表格
				为了便于使用E2地址检查工具，请勿在括号内增加空格或Tab
****************************************************************************************/
#ifndef __DataProcess_H
#define __DataProcess_H

#include "Public.h"

#pragma pack(1)    /*1字节对齐*/

#define C_CRCLen2                        2                                                                     /*CRC长度*/
#define C_CurrDataLen5                   5                                                                     /*Hex格式5字节长度*/

/**************************铁电大小为2kByte***********************************/
/*****铁电 三处定义，每处669，共2007，剩余1处41，备份数据采用固定备份偏移*****/
#define FRAM_BackUp2_Space               0x029D                                                      /*备份第1处备份起始地址*/
#define FRAM_BackUp3_Space               0x053A                                                      /*备份第2处备份起始地址*/
#define FRAM_Remaind_Space               0x07D7                                                      /*剩余铁电起始地址*/
#define FRAM_Max_Addr                    0x07FF                                                      /*铁电最大地址*/

/*电能相关,5字节hex数据，每个数据项单独带2字节CRC，共7个字节。透支、剩余金额列当前电量类数据最后，结合程序一起。上电处理计算地址与程序有关。*/
/*698表电能部分修改放铁电，为兼容原来E2地址，该部分与需量接口E2地址采用宏定义方式。同时电能宏定义还是采用E2Addr格式，实际放铁电*/
#define E2Addr_CurrEnergy_St             0x0000                                                      /*当前电能计量FRAM起始地址*/
#define E2Addr_Pos_Ac_T1_En_Pul_0        (E2Addr_CurrEnergy_St)                                      /*当前正向有功费率1电能脉冲数*/
#define E2Addr_Pos_Ac_T2_En_Pul_0        (E2Addr_Pos_Ac_T1_En_Pul_0+C_CurrDataLen5+C_CRCLen2)        /*当前正向有功费率2电能脉冲数*/
#define E2Addr_Pos_Ac_T3_En_Pul_0        (E2Addr_Pos_Ac_T2_En_Pul_0+C_CurrDataLen5+C_CRCLen2)        /*当前正向有功费率3电能脉冲数*/
#define E2Addr_Pos_Ac_T4_En_Pul_0        (E2Addr_Pos_Ac_T3_En_Pul_0+C_CurrDataLen5+C_CRCLen2)        /*当前正向有功费率4电能脉冲数*/
#define E2Addr_Pos_Ac_T5_En_Pul_0        (E2Addr_Pos_Ac_T4_En_Pul_0+C_CurrDataLen5+C_CRCLen2)        /*当前正向有功费率5电能脉冲数*/
#define E2Addr_Pos_Ac_T6_En_Pul_0        (E2Addr_Pos_Ac_T5_En_Pul_0+C_CurrDataLen5+C_CRCLen2)        /*当前正向有功费率6电能脉冲数*/
#define E2Addr_Pos_Ac_T7_En_Pul_0        (E2Addr_Pos_Ac_T6_En_Pul_0+C_CurrDataLen5+C_CRCLen2)        /*当前正向有功费率7电能脉冲数*/
#define E2Addr_Pos_Ac_T8_En_Pul_0        (E2Addr_Pos_Ac_T7_En_Pul_0+C_CurrDataLen5+C_CRCLen2)        /*当前正向有功费率8电能脉冲数*/
#define E2Addr_Pos_Ac_T9_En_Pul_0        (E2Addr_Pos_Ac_T8_En_Pul_0+C_CurrDataLen5+C_CRCLen2)        /*当前正向有功费率9电能脉冲数*/
#define E2Addr_Pos_Ac_T10_En_Pul_0       (E2Addr_Pos_Ac_T9_En_Pul_0+C_CurrDataLen5+C_CRCLen2)        /*当前正向有功费率10电能脉冲数*/
#define E2Addr_Pos_Ac_T11_En_Pul_0       (E2Addr_Pos_Ac_T10_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前正向有功费率11电能脉冲数*/
#define E2Addr_Pos_Ac_T12_En_Pul_0       (E2Addr_Pos_Ac_T11_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前正向有功费率12电能脉冲数*/

#define E2Addr_Rev_Ac_T1_En_Pul_0        (E2Addr_Pos_Ac_T12_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前反向有功费率1电能脉冲数*/
#define E2Addr_Rev_Ac_T2_En_Pul_0        (E2Addr_Rev_Ac_T1_En_Pul_0+C_CurrDataLen5+C_CRCLen2)        /*当前反向有功费率2电能脉冲数*/
#define E2Addr_Rev_Ac_T3_En_Pul_0        (E2Addr_Rev_Ac_T2_En_Pul_0+C_CurrDataLen5+C_CRCLen2)        /*当前反向有功费率3电能脉冲数*/
#define E2Addr_Rev_Ac_T4_En_Pul_0        (E2Addr_Rev_Ac_T3_En_Pul_0+C_CurrDataLen5+C_CRCLen2)        /*当前反向有功费率4电能脉冲数*/
#define E2Addr_Rev_Ac_T5_En_Pul_0        (E2Addr_Rev_Ac_T4_En_Pul_0+C_CurrDataLen5+C_CRCLen2)        /*当前反向有功费率5电能脉冲数*/
#define E2Addr_Rev_Ac_T6_En_Pul_0        (E2Addr_Rev_Ac_T5_En_Pul_0+C_CurrDataLen5+C_CRCLen2)        /*当前反向有功费率6电能脉冲数*/
#define E2Addr_Rev_Ac_T7_En_Pul_0        (E2Addr_Rev_Ac_T6_En_Pul_0+C_CurrDataLen5+C_CRCLen2)        /*当前反向有功费率7电能脉冲数*/
#define E2Addr_Rev_Ac_T8_En_Pul_0        (E2Addr_Rev_Ac_T7_En_Pul_0+C_CurrDataLen5+C_CRCLen2)        /*当前反向有功费率8电能脉冲数*/
#define E2Addr_Rev_Ac_T9_En_Pul_0        (E2Addr_Rev_Ac_T8_En_Pul_0+C_CurrDataLen5+C_CRCLen2)        /*当前反向有功费率9电能脉冲数*/
#define E2Addr_Rev_Ac_T10_En_Pul_0       (E2Addr_Rev_Ac_T9_En_Pul_0+C_CurrDataLen5+C_CRCLen2)        /*当前反向有功费率10电能脉冲数*/
#define E2Addr_Rev_Ac_T11_En_Pul_0       (E2Addr_Rev_Ac_T10_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前反向有功费率11电能脉冲数*/
#define E2Addr_Rev_Ac_T12_En_Pul_0       (E2Addr_Rev_Ac_T11_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前反向有功费率12电能脉冲数*/

#define E2Addr_Qua1_Re_T1_En_Pul_0       (E2Addr_Rev_Ac_T12_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前1象限无功费率1电能脉冲数*/
#define E2Addr_Qua1_Re_T2_En_Pul_0       (E2Addr_Qua1_Re_T1_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前1象限无功费率2电能脉冲数*/
#define E2Addr_Qua1_Re_T3_En_Pul_0       (E2Addr_Qua1_Re_T2_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前1象限无功费率3电能脉冲数*/
#define E2Addr_Qua1_Re_T4_En_Pul_0       (E2Addr_Qua1_Re_T3_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前1象限无功费率4电能脉冲数*/
#define E2Addr_Qua1_Re_T5_En_Pul_0       (E2Addr_Qua1_Re_T4_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前1象限无功费率5电能脉冲数*/
#define E2Addr_Qua1_Re_T6_En_Pul_0       (E2Addr_Qua1_Re_T5_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前1象限无功费率6电能脉冲数*/
#define E2Addr_Qua1_Re_T7_En_Pul_0       (E2Addr_Qua1_Re_T6_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前1象限无功费率7电能脉冲数*/
#define E2Addr_Qua1_Re_T8_En_Pul_0       (E2Addr_Qua1_Re_T7_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前1象限无功费率8电能脉冲数*/
#define E2Addr_Qua1_Re_T9_En_Pul_0       (E2Addr_Qua1_Re_T8_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前1象限无功费率9电能脉冲数*/
#define E2Addr_Qua1_Re_T10_En_Pul_0      (E2Addr_Qua1_Re_T9_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前1象限无功费率10电能脉冲数*/
#define E2Addr_Qua1_Re_T11_En_Pul_0      (E2Addr_Qua1_Re_T10_En_Pul_0+C_CurrDataLen5+C_CRCLen2)      /*当前1象限无功费率11电能脉冲数*/
#define E2Addr_Qua1_Re_T12_En_Pul_0      (E2Addr_Qua1_Re_T11_En_Pul_0+C_CurrDataLen5+C_CRCLen2)      /*当前1象限无功费率12电能脉冲数*/

#define E2Addr_Qua2_Re_T1_En_Pul_0       (E2Addr_Qua1_Re_T12_En_Pul_0+C_CurrDataLen5+C_CRCLen2)      /*当前2象限无功费率1电能脉冲数*/
#define E2Addr_Qua2_Re_T2_En_Pul_0       (E2Addr_Qua2_Re_T1_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前2象限无功费率2电能脉冲数*/
#define E2Addr_Qua2_Re_T3_En_Pul_0       (E2Addr_Qua2_Re_T2_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前2象限无功费率3电能脉冲数*/
#define E2Addr_Qua2_Re_T4_En_Pul_0       (E2Addr_Qua2_Re_T3_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前2象限无功费率4电能脉冲数*/
#define E2Addr_Qua2_Re_T5_En_Pul_0       (E2Addr_Qua2_Re_T4_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前2象限无功费率5电能脉冲数*/
#define E2Addr_Qua2_Re_T6_En_Pul_0       (E2Addr_Qua2_Re_T5_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前2象限无功费率6电能脉冲数*/
#define E2Addr_Qua2_Re_T7_En_Pul_0       (E2Addr_Qua2_Re_T6_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前2象限无功费率7电能脉冲数*/
#define E2Addr_Qua2_Re_T8_En_Pul_0       (E2Addr_Qua2_Re_T7_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前2象限无功费率8电能脉冲数*/
#define E2Addr_Qua2_Re_T9_En_Pul_0       (E2Addr_Qua2_Re_T8_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前2象限无功费率9电能脉冲数*/
#define E2Addr_Qua2_Re_T10_En_Pul_0      (E2Addr_Qua2_Re_T9_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前2象限无功费率10电能脉冲数*/
#define E2Addr_Qua2_Re_T11_En_Pul_0      (E2Addr_Qua2_Re_T10_En_Pul_0+C_CurrDataLen5+C_CRCLen2)      /*当前2象限无功费率11电能脉冲数*/
#define E2Addr_Qua2_Re_T12_En_Pul_0      (E2Addr_Qua2_Re_T11_En_Pul_0+C_CurrDataLen5+C_CRCLen2)      /*当前2象限无功费率12电能脉冲数*/

#define E2Addr_Qua3_Re_T1_En_Pul_0       (E2Addr_Qua2_Re_T12_En_Pul_0+C_CurrDataLen5+C_CRCLen2)      /*当前3象限无功费率1电能脉冲数*/
#define E2Addr_Qua3_Re_T2_En_Pul_0       (E2Addr_Qua3_Re_T1_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前3象限无功费率2电能脉冲数*/
#define E2Addr_Qua3_Re_T3_En_Pul_0       (E2Addr_Qua3_Re_T2_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前3象限无功费率3电能脉冲数*/
#define E2Addr_Qua3_Re_T4_En_Pul_0       (E2Addr_Qua3_Re_T3_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前3象限无功费率4电能脉冲数*/
#define E2Addr_Qua3_Re_T5_En_Pul_0       (E2Addr_Qua3_Re_T4_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前3象限无功费率5电能脉冲数*/
#define E2Addr_Qua3_Re_T6_En_Pul_0       (E2Addr_Qua3_Re_T5_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前3象限无功费率6电能脉冲数*/
#define E2Addr_Qua3_Re_T7_En_Pul_0       (E2Addr_Qua3_Re_T6_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前3象限无功费率7电能脉冲数*/
#define E2Addr_Qua3_Re_T8_En_Pul_0       (E2Addr_Qua3_Re_T7_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前3象限无功费率8电能脉冲数*/
#define E2Addr_Qua3_Re_T9_En_Pul_0       (E2Addr_Qua3_Re_T8_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前3象限无功费率9电能脉冲数*/
#define E2Addr_Qua3_Re_T10_En_Pul_0      (E2Addr_Qua3_Re_T9_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前3象限无功费率10电能脉冲数*/
#define E2Addr_Qua3_Re_T11_En_Pul_0      (E2Addr_Qua3_Re_T10_En_Pul_0+C_CurrDataLen5+C_CRCLen2)      /*当前3象限无功费率11电能脉冲数*/
#define E2Addr_Qua3_Re_T12_En_Pul_0      (E2Addr_Qua3_Re_T11_En_Pul_0+C_CurrDataLen5+C_CRCLen2)      /*当前3象限无功费率12电能脉冲数*/

#define E2Addr_Qua4_Re_T1_En_Pul_0       (E2Addr_Qua3_Re_T12_En_Pul_0+C_CurrDataLen5+C_CRCLen2)      /*当前4象限无功费率1电能脉冲数*/
#define E2Addr_Qua4_Re_T2_En_Pul_0       (E2Addr_Qua4_Re_T1_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前4象限无功费率2电能脉冲数*/
#define E2Addr_Qua4_Re_T3_En_Pul_0       (E2Addr_Qua4_Re_T2_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前4象限无功费率3电能脉冲数*/
#define E2Addr_Qua4_Re_T4_En_Pul_0       (E2Addr_Qua4_Re_T3_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前4象限无功费率4电能脉冲数*/
#define E2Addr_Qua4_Re_T5_En_Pul_0       (E2Addr_Qua4_Re_T4_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前4象限无功费率5电能脉冲数*/
#define E2Addr_Qua4_Re_T6_En_Pul_0       (E2Addr_Qua4_Re_T5_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前4象限无功费率6电能脉冲数*/
#define E2Addr_Qua4_Re_T7_En_Pul_0       (E2Addr_Qua4_Re_T6_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前4象限无功费率7电能脉冲数*/
#define E2Addr_Qua4_Re_T8_En_Pul_0       (E2Addr_Qua4_Re_T7_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前4象限无功费率8电能脉冲数*/
#define E2Addr_Qua4_Re_T9_En_Pul_0       (E2Addr_Qua4_Re_T8_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前4象限无功费率9电能脉冲数*/
#define E2Addr_Qua4_Re_T10_En_Pul_0      (E2Addr_Qua4_Re_T9_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*当前4象限无功费率10电能脉冲数*/
#define E2Addr_Qua4_Re_T11_En_Pul_0      (E2Addr_Qua4_Re_T10_En_Pul_0+C_CurrDataLen5+C_CRCLen2)      /*当前4象限无功费率11电能脉冲数*/
#define E2Addr_Qua4_Re_T12_En_Pul_0      (E2Addr_Qua4_Re_T11_En_Pul_0+C_CurrDataLen5+C_CRCLen2)      /*当前4象限无功费率12电能脉冲数*/

#define E2Addr_PosA_Ac_En_Pul_0          (E2Addr_Qua4_Re_T12_En_Pul_0+C_CurrDataLen5+C_CRCLen2)      /*当前A相正向有功电能脉冲数*/
#define E2Addr_RevA_Ac_En_Pul_0          (E2Addr_PosA_Ac_En_Pul_0+C_CurrDataLen5+C_CRCLen2)          /*当前A相反向有功电能脉冲数*/
#define E2Addr_Qua1A_Re_En_Pul_0         (E2Addr_RevA_Ac_En_Pul_0+C_CurrDataLen5+C_CRCLen2)          /*当前A相1象限无功电能脉冲数*/
#define E2Addr_Qua2A_Re_En_Pul_0         (E2Addr_Qua1A_Re_En_Pul_0+C_CurrDataLen5+C_CRCLen2)         /*当前A相2象限无功电能脉冲数*/
#define E2Addr_Qua3A_Re_En_Pul_0         (E2Addr_Qua2A_Re_En_Pul_0+C_CurrDataLen5+C_CRCLen2)         /*当前A相3象限无功电能脉冲数*/
#define E2Addr_Qua4A_Re_En_Pul_0         (E2Addr_Qua3A_Re_En_Pul_0+C_CurrDataLen5+C_CRCLen2)         /*当前A相4象限无功电能脉冲数*/

#define E2Addr_PosB_Ac_En_Pul_0          (E2Addr_Qua4A_Re_En_Pul_0+C_CurrDataLen5+C_CRCLen2)         /*当前B相正向有功电能脉冲数*/
#define E2Addr_RevB_Ac_En_Pul_0          (E2Addr_PosB_Ac_En_Pul_0+C_CurrDataLen5+C_CRCLen2)          /*当前B相反向有功电能脉冲数*/
#define E2Addr_Qua1B_Re_En_Pul_0         (E2Addr_RevB_Ac_En_Pul_0+C_CurrDataLen5+C_CRCLen2)          /*当前B相1象限无功电能脉冲数*/
#define E2Addr_Qua2B_Re_En_Pul_0         (E2Addr_Qua1B_Re_En_Pul_0+C_CurrDataLen5+C_CRCLen2)         /*当前B相2象限无功电能脉冲数*/
#define E2Addr_Qua3B_Re_En_Pul_0         (E2Addr_Qua2B_Re_En_Pul_0+C_CurrDataLen5+C_CRCLen2)         /*当前B相3象限无功电能脉冲数*/
#define E2Addr_Qua4B_Re_En_Pul_0         (E2Addr_Qua3B_Re_En_Pul_0+C_CurrDataLen5+C_CRCLen2)         /*当前B相4象限无功电能脉冲数*/

#define E2Addr_PosC_Ac_En_Pul_0          (E2Addr_Qua4B_Re_En_Pul_0+C_CurrDataLen5+C_CRCLen2)         /*当前C相正向有功电能脉冲数*/
#define E2Addr_RevC_Ac_En_Pul_0          (E2Addr_PosC_Ac_En_Pul_0+C_CurrDataLen5+C_CRCLen2)          /*当前C相反向有功电能脉冲数*/
#define E2Addr_Qua1C_Re_En_Pul_0         (E2Addr_RevC_Ac_En_Pul_0+C_CurrDataLen5+C_CRCLen2)          /*当前C相1象限无功电能脉冲数*/
#define E2Addr_Qua2C_Re_En_Pul_0         (E2Addr_Qua1C_Re_En_Pul_0+C_CurrDataLen5+C_CRCLen2)         /*当前C相2象限无功电能脉冲数*/
#define E2Addr_Qua3C_Re_En_Pul_0         (E2Addr_Qua2C_Re_En_Pul_0+C_CurrDataLen5+C_CRCLen2)         /*当前C相3象限无功电能脉冲数*/
#define E2Addr_Qua4C_Re_En_Pul_0         (E2Addr_Qua3C_Re_En_Pul_0+C_CurrDataLen5+C_CRCLen2)         /*当前C相4象限无功电能脉冲数*/

#define E2Addr_SC_Com_Ac_Tol_En_Pul_0    (E2Addr_Qua4C_Re_En_Pul_0+C_CurrDataLen5+C_CRCLen2)         /*当前结算周期内组合有功总累计用电量-脉冲数格式*/
#define E2Addr_M_Com_Ac_Tol_En_Pul_0     (E2Addr_SC_Com_Ac_Tol_En_Pul_0+C_CurrDataLen5+C_CRCLen2)    /*当前月度组合有功总累计用电量-脉冲数格式*/
#define E2Addr_Y_Com_Ac_Tol_En_Pul_0     (E2Addr_M_Com_Ac_Tol_En_Pul_0+C_CurrDataLen5+C_CRCLen2)     /*当前年结算周期组合有功总累计用电量-脉冲数格式*/
#define E2Addr_ChargeBal_Hex_Deal        (E2Addr_Y_Com_Ac_Tol_En_Pul_0+C_CurrDataLen5+C_CRCLen2)     /*当前剩余金额,电能处理模块*/
#define E2Addr_OverDraft_Hex_Deal        (E2Addr_ChargeBal_Hex_Deal+C_CurrDataLen5+C_CRCLen2)        /*当前透支金额,电能处理模块*/
#define E2Addr_CurrEnergyRam_End         (E2Addr_OverDraft_Hex_Deal+C_CurrDataLen5+C_CRCLen2)        /*当前电能计量存RAM E2结束地址*/
/***********以上铁电3处数据空间，剩余约40Byte*******************/

/***********铁电 1处定义，共40Byte，从0x07D7开始****************/
#define FRAMAddr_Enter_LowPower_Time     FRAM_Remaind_Space                                                /*进入低功耗时间 带2 CRC*/
#define FRAMAddr_Exit_LowPower_Time      (FRAMAddr_Enter_LowPower_Time+CLEnter_LowPower_Time+C_CRCLen2)    /*退出低功耗时间 带2 CRC*/
#define FRAMAddr_SoftI_J_RemainTime      (FRAMAddr_Exit_LowPower_Time+CLExit_LowPower_Time+C_CRCLen2)      /*软IJ剩余时间  2字节+2CRC*/
#define FRAMAddr_BackTime_OneSec         (FRAMAddr_SoftI_J_RemainTime+CLSoftI_J_RemainTime+C_CRCLen2)      /*备份时间，每秒写铁电，年月日时分秒  6字节+2CRC*/
/***********以上铁电1处数据空间，剩余约20Byte*******************/



/***********E2大小为512kBit，64kByte，每页64Byte，共1024页,E2最大地址0x10000*************/
/***********E2 三处定义，每处18k，共54k，剩余为E2 一处定义10k****************************/
/**************************备份数据采用固定备份偏移288页*********************************/
#define E2_BackUp2_Space                 0x4B00                                                                /*备份第1处备份起始地址*/
#define E2_BackUp3_Space                 0x9600                                                                /*备份第2处备份起始地址*/
#define E2_Remaind_Space                 0xE100                                                                /*剩余E2起始地址*/
#define E2_Max_Addr                      0xFFFE                                                                /*E2最大地址,为兼容原来数据定义两字节，本次最大限值为*/

#define E2Addr_SC_Com_Ac_Tol_En_1        0x0000                                                                /*上1结算周期内组合有功总累计用电量,总清电能注意*/
#define E2Addr_SC_Pos_Ac_Tol_En_Pul_1    (E2Addr_SC_Com_Ac_Tol_En_1+CLSC_Com_Ac_Tol_En_1+C_CRCLen2)            /*上1结算周期内正向有功总电量-脉冲数格式，*/
#define E2Addr_SC_Rev_Ac_Tol_En_Pul_1    (E2Addr_SC_Pos_Ac_Tol_En_Pul_1+CLSC_Pos_Ac_Tol_En_Pul_1+C_CRCLen2)    /*上1结算周期内反向有功总电量-脉冲数格式*/
#define E2Addr_M_Com_Ac_Tol_En_1         (E2Addr_SC_Rev_Ac_Tol_En_Pul_1+CLSC_Rev_Ac_Tol_En_Pul_1+C_CRCLen2)    /*上1月度组合有功总累计用电量*/
#define E2Addr_M_Pos_Ac_Tol_En_Pul_1     (E2Addr_M_Com_Ac_Tol_En_1+CLM_Com_Ac_Tol_En_1+C_CRCLen2)              /*上1月度正向有功累计电量-脉冲数格式*/
#define E2Addr_M_Rev_Ac_Tol_En_Pul_1     (E2Addr_M_Pos_Ac_Tol_En_Pul_1+CLM_Pos_Ac_Tol_En_Pul_1+C_CRCLen2)      /*上1月度反向有功累计电量-脉冲数格式*/

/******************需量,每个数据项4字节需量+7字节时间+2字节CRC,共13字节*******************/
#define E2Addr_Pos_Ac_Tol_De_0           (E2Addr_M_Rev_Ac_Tol_En_Pul_1+CLM_Rev_Ac_Tol_En_Pul_1+C_CRCLen2)      /*当前正向有功总最大需量及发生时刻*/
#define E2Addr_Pos_Ac_T1_De_0            (E2Addr_Pos_Ac_Tol_De_0+CLPos_Ac_Tol_De_0+C_CRCLen2)                  /*当前正向有功费率1最大需量及发生时刻*/
#define E2Addr_Pos_Ac_T2_De_0            (E2Addr_Pos_Ac_T1_De_0+CLPos_Ac_T1_De_0+C_CRCLen2)                    /*当前正向有功费率2最大需量及发生时刻*/
#define E2Addr_Pos_Ac_T3_De_0            (E2Addr_Pos_Ac_T2_De_0+CLPos_Ac_T2_De_0+C_CRCLen2)                    /*当前正向有功费率3最大需量及发生时刻*/
#define E2Addr_Pos_Ac_T4_De_0            (E2Addr_Pos_Ac_T3_De_0+CLPos_Ac_T3_De_0+C_CRCLen2)                    /*当前正向有功费率4最大需量及发生时刻*/
#define E2Addr_Pos_Ac_T5_De_0            (E2Addr_Pos_Ac_T4_De_0+CLPos_Ac_T4_De_0+C_CRCLen2)                    /*当前正向有功费率5最大需量及发生时刻*/
#define E2Addr_Pos_Ac_T6_De_0            (E2Addr_Pos_Ac_T5_De_0+CLPos_Ac_T5_De_0+C_CRCLen2)                    /*当前正向有功费率6最大需量及发生时刻*/
#define E2Addr_Pos_Ac_T7_De_0            (E2Addr_Pos_Ac_T6_De_0+CLPos_Ac_T6_De_0+C_CRCLen2)                    /*当前正向有功费率7最大需量及发生时刻*/
#define E2Addr_Pos_Ac_T8_De_0            (E2Addr_Pos_Ac_T7_De_0+CLPos_Ac_T7_De_0+C_CRCLen2)                    /*当前正向有功费率8最大需量及发生时刻*/
#define E2Addr_Pos_Ac_T9_De_0            (E2Addr_Pos_Ac_T8_De_0+CLPos_Ac_T8_De_0+C_CRCLen2)                    /*当前正向有功费率9最大需量及发生时刻*/
#define E2Addr_Pos_Ac_T10_De_0           (E2Addr_Pos_Ac_T9_De_0+CLPos_Ac_T9_De_0+C_CRCLen2)                    /*当前正向有功费率10最大需量及发生时刻*/
#define E2Addr_Pos_Ac_T11_De_0           (E2Addr_Pos_Ac_T10_De_0+CLPos_Ac_T10_De_0+C_CRCLen2)                  /*当前正向有功费率11最大需量及发生时刻*/
#define E2Addr_Pos_Ac_T12_De_0           (E2Addr_Pos_Ac_T11_De_0+CLPos_Ac_T11_De_0+C_CRCLen2)                  /*当前正向有功费率12最大需量及发生时刻*/

#define E2Addr_Rev_Ac_Tol_De_0           (E2Addr_Pos_Ac_T12_De_0+CLPos_Ac_T12_De_0+C_CRCLen2)                  /*当前反向有功总最大需量及发生时刻*/
#define E2Addr_Rev_Ac_T1_De_0            (E2Addr_Rev_Ac_Tol_De_0+CLRev_Ac_Tol_De_0+C_CRCLen2)                  /*当前反向有功费率1最大需量及发生时刻*/
#define E2Addr_Rev_Ac_T2_De_0            (E2Addr_Rev_Ac_T1_De_0+CLRev_Ac_T1_De_0+C_CRCLen2)                    /*当前反向有功费率2最大需量及发生时刻*/
#define E2Addr_Rev_Ac_T3_De_0            (E2Addr_Rev_Ac_T2_De_0+CLRev_Ac_T2_De_0+C_CRCLen2)                    /*当前反向有功费率3最大需量及发生时刻*/
#define E2Addr_Rev_Ac_T4_De_0            (E2Addr_Rev_Ac_T3_De_0+CLRev_Ac_T3_De_0+C_CRCLen2)                    /*当前反向有功费率4最大需量及发生时刻*/
#define E2Addr_Rev_Ac_T5_De_0            (E2Addr_Rev_Ac_T4_De_0+CLRev_Ac_T4_De_0+C_CRCLen2)                    /*当前反向有功费率5最大需量及发生时刻*/
#define E2Addr_Rev_Ac_T6_De_0            (E2Addr_Rev_Ac_T5_De_0+CLRev_Ac_T5_De_0+C_CRCLen2)                    /*当前反向有功费率6最大需量及发生时刻*/
#define E2Addr_Rev_Ac_T7_De_0            (E2Addr_Rev_Ac_T6_De_0+CLRev_Ac_T6_De_0+C_CRCLen2)                    /*当前反向有功费率7最大需量及发生时刻*/
#define E2Addr_Rev_Ac_T8_De_0            (E2Addr_Rev_Ac_T7_De_0+CLRev_Ac_T7_De_0+C_CRCLen2)                    /*当前反向有功费率8最大需量及发生时刻*/
#define E2Addr_Rev_Ac_T9_De_0            (E2Addr_Rev_Ac_T8_De_0+CLRev_Ac_T8_De_0+C_CRCLen2)                    /*当前反向有功费率9最大需量及发生时刻*/
#define E2Addr_Rev_Ac_T10_De_0           (E2Addr_Rev_Ac_T9_De_0+CLRev_Ac_T9_De_0+C_CRCLen2)                    /*当前反向有功费率10最大需量及发生时刻*/
#define E2Addr_Rev_Ac_T11_De_0           (E2Addr_Rev_Ac_T10_De_0+CLRev_Ac_T10_De_0+C_CRCLen2)                  /*当前反向有功费率11最大需量及发生时刻*/
#define E2Addr_Rev_Ac_T12_De_0           (E2Addr_Rev_Ac_T11_De_0+CLRev_Ac_T11_De_0+C_CRCLen2)                  /*当前反向有功费率12最大需量及发生时刻*/

#define E2Addr_Qua1_Re_Tol_De_0          (E2Addr_Rev_Ac_T12_De_0+CLRev_Ac_T12_De_0+C_CRCLen2)                  /*当前1象限无功总最大需量及发生时刻*/
#define E2Addr_Qua1_Re_T1_De_0           (E2Addr_Qua1_Re_Tol_De_0+CLQua1_Re_Tol_De_0+C_CRCLen2)                /*当前1象限无功费率1最大需量及发生时刻*/
#define E2Addr_Qua1_Re_T2_De_0           (E2Addr_Qua1_Re_T1_De_0+CLQua1_Re_T1_De_0+C_CRCLen2)                  /*当前1象限无功费率2最大需量及发生时刻*/
#define E2Addr_Qua1_Re_T3_De_0           (E2Addr_Qua1_Re_T2_De_0+CLQua1_Re_T2_De_0+C_CRCLen2)                  /*当前1象限无功费率3最大需量及发生时刻*/
#define E2Addr_Qua1_Re_T4_De_0           (E2Addr_Qua1_Re_T3_De_0+CLQua1_Re_T3_De_0+C_CRCLen2)                  /*当前1象限无功费率4最大需量及发生时刻*/
#define E2Addr_Qua1_Re_T5_De_0           (E2Addr_Qua1_Re_T4_De_0+CLQua1_Re_T4_De_0+C_CRCLen2)                  /*当前1象限无功费率5最大需量及发生时刻*/
#define E2Addr_Qua1_Re_T6_De_0           (E2Addr_Qua1_Re_T5_De_0+CLQua1_Re_T5_De_0+C_CRCLen2)                  /*当前1象限无功费率6最大需量及发生时刻*/
#define E2Addr_Qua1_Re_T7_De_0           (E2Addr_Qua1_Re_T6_De_0+CLQua1_Re_T6_De_0+C_CRCLen2)                  /*当前1象限无功费率7最大需量及发生时刻*/
#define E2Addr_Qua1_Re_T8_De_0           (E2Addr_Qua1_Re_T7_De_0+CLQua1_Re_T7_De_0+C_CRCLen2)                  /*当前1象限无功费率8最大需量及发生时刻*/
#define E2Addr_Qua1_Re_T9_De_0           (E2Addr_Qua1_Re_T8_De_0+CLQua1_Re_T8_De_0+C_CRCLen2)                  /*当前1象限无功费率9最大需量及发生时刻*/
#define E2Addr_Qua1_Re_T10_De_0          (E2Addr_Qua1_Re_T9_De_0+CLQua1_Re_T9_De_0+C_CRCLen2)                  /*当前1象限无功费率10最大需量及发生时刻*/
#define E2Addr_Qua1_Re_T11_De_0          (E2Addr_Qua1_Re_T10_De_0+CLQua1_Re_T10_De_0+C_CRCLen2)                /*当前1象限无功费率11最大需量及发生时刻*/
#define E2Addr_Qua1_Re_T12_De_0          (E2Addr_Qua1_Re_T11_De_0+CLQua1_Re_T11_De_0+C_CRCLen2)                /*当前1象限无功费率12最大需量及发生时刻*/

#define E2Addr_Qua2_Re_Tol_De_0          (E2Addr_Qua1_Re_T12_De_0+CLQua1_Re_T12_De_0+C_CRCLen2)                /*当前2象限无功总最大需量及发生时刻*/
#define E2Addr_Qua2_Re_T1_De_0           (E2Addr_Qua2_Re_Tol_De_0+CLQua2_Re_Tol_De_0+C_CRCLen2)                /*当前2象限无功费率1最大需量及发生时刻*/
#define E2Addr_Qua2_Re_T2_De_0           (E2Addr_Qua2_Re_T1_De_0+CLQua2_Re_T1_De_0+C_CRCLen2)                  /*当前2象限无功费率2最大需量及发生时刻*/
#define E2Addr_Qua2_Re_T3_De_0           (E2Addr_Qua2_Re_T2_De_0+CLQua2_Re_T2_De_0+C_CRCLen2)                  /*当前2象限无功费率3最大需量及发生时刻*/
#define E2Addr_Qua2_Re_T4_De_0           (E2Addr_Qua2_Re_T3_De_0+CLQua2_Re_T3_De_0+C_CRCLen2)                  /*当前2象限无功费率4最大需量及发生时刻*/
#define E2Addr_Qua2_Re_T5_De_0           (E2Addr_Qua2_Re_T4_De_0+CLQua2_Re_T4_De_0+C_CRCLen2)                  /*当前2象限无功费率5最大需量及发生时刻*/
#define E2Addr_Qua2_Re_T6_De_0           (E2Addr_Qua2_Re_T5_De_0+CLQua2_Re_T5_De_0+C_CRCLen2)                  /*当前2象限无功费率6最大需量及发生时刻*/
#define E2Addr_Qua2_Re_T7_De_0           (E2Addr_Qua2_Re_T6_De_0+CLQua2_Re_T6_De_0+C_CRCLen2)                  /*当前2象限无功费率7最大需量及发生时刻*/
#define E2Addr_Qua2_Re_T8_De_0           (E2Addr_Qua2_Re_T7_De_0+CLQua2_Re_T7_De_0+C_CRCLen2)                  /*当前2象限无功费率8最大需量及发生时刻*/
#define E2Addr_Qua2_Re_T9_De_0           (E2Addr_Qua2_Re_T8_De_0+CLQua2_Re_T8_De_0+C_CRCLen2)                  /*当前2象限无功费率9最大需量及发生时刻*/
#define E2Addr_Qua2_Re_T10_De_0          (E2Addr_Qua2_Re_T9_De_0+CLQua2_Re_T9_De_0+C_CRCLen2)                  /*当前2象限无功费率10最大需量及发生时刻*/
#define E2Addr_Qua2_Re_T11_De_0          (E2Addr_Qua2_Re_T10_De_0+CLQua2_Re_T10_De_0+C_CRCLen2)                /*当前2象限无功费率11最大需量及发生时刻*/
#define E2Addr_Qua2_Re_T12_De_0          (E2Addr_Qua2_Re_T11_De_0+CLQua2_Re_T11_De_0+C_CRCLen2)                /*当前2象限无功费率12最大需量及发生时刻*/

#define E2Addr_Qua3_Re_Tol_De_0          (E2Addr_Qua2_Re_T12_De_0+CLQua2_Re_T12_De_0+C_CRCLen2)                /*当前3象限无功总最大需量及发生时刻*/
#define E2Addr_Qua3_Re_T1_De_0           (E2Addr_Qua3_Re_Tol_De_0+CLQua3_Re_Tol_De_0+C_CRCLen2)                /*当前3象限无功费率1最大需量及发生时刻*/
#define E2Addr_Qua3_Re_T2_De_0           (E2Addr_Qua3_Re_T1_De_0+CLQua3_Re_T1_De_0+C_CRCLen2)                  /*当前3象限无功费率2最大需量及发生时刻*/
#define E2Addr_Qua3_Re_T3_De_0           (E2Addr_Qua3_Re_T2_De_0+CLQua3_Re_T2_De_0+C_CRCLen2)                  /*当前3象限无功费率3最大需量及发生时刻*/
#define E2Addr_Qua3_Re_T4_De_0           (E2Addr_Qua3_Re_T3_De_0+CLQua3_Re_T3_De_0+C_CRCLen2)                  /*当前3象限无功费率4最大需量及发生时刻*/
#define E2Addr_Qua3_Re_T5_De_0           (E2Addr_Qua3_Re_T4_De_0+CLQua3_Re_T4_De_0+C_CRCLen2)                  /*当前3象限无功费率5最大需量及发生时刻*/
#define E2Addr_Qua3_Re_T6_De_0           (E2Addr_Qua3_Re_T5_De_0+CLQua3_Re_T5_De_0+C_CRCLen2)                  /*当前3象限无功费率6最大需量及发生时刻*/
#define E2Addr_Qua3_Re_T7_De_0           (E2Addr_Qua3_Re_T6_De_0+CLQua3_Re_T6_De_0+C_CRCLen2)                  /*当前3象限无功费率7最大需量及发生时刻*/
#define E2Addr_Qua3_Re_T8_De_0           (E2Addr_Qua3_Re_T7_De_0+CLQua3_Re_T7_De_0+C_CRCLen2)                  /*当前3象限无功费率8最大需量及发生时刻*/
#define E2Addr_Qua3_Re_T9_De_0           (E2Addr_Qua3_Re_T8_De_0+CLQua3_Re_T8_De_0+C_CRCLen2)                  /*当前3象限无功费率9最大需量及发生时刻*/
#define E2Addr_Qua3_Re_T10_De_0          (E2Addr_Qua3_Re_T9_De_0+CLQua3_Re_T9_De_0+C_CRCLen2)                  /*当前3象限无功费率10最大需量及发生时刻*/
#define E2Addr_Qua3_Re_T11_De_0          (E2Addr_Qua3_Re_T10_De_0+CLQua3_Re_T10_De_0+C_CRCLen2)                /*当前3象限无功费率11最大需量及发生时刻*/
#define E2Addr_Qua3_Re_T12_De_0          (E2Addr_Qua3_Re_T11_De_0+CLQua3_Re_T11_De_0+C_CRCLen2)                /*当前3象限无功费率12最大需量及发生时刻*/

#define E2Addr_Qua4_Re_Tol_De_0          (E2Addr_Qua3_Re_T12_De_0+CLQua3_Re_T12_De_0+C_CRCLen2)                /*当前4象限无功总最大需量及发生时刻*/
#define E2Addr_Qua4_Re_T1_De_0           (E2Addr_Qua4_Re_Tol_De_0+CLQua4_Re_Tol_De_0+C_CRCLen2)                /*当前4象限无功费率1最大需量及发生时刻*/
#define E2Addr_Qua4_Re_T2_De_0           (E2Addr_Qua4_Re_T1_De_0+CLQua4_Re_T1_De_0+C_CRCLen2)                  /*当前4象限无功费率2最大需量及发生时刻*/
#define E2Addr_Qua4_Re_T3_De_0           (E2Addr_Qua4_Re_T2_De_0+CLQua4_Re_T2_De_0+C_CRCLen2)                  /*当前4象限无功费率3最大需量及发生时刻*/
#define E2Addr_Qua4_Re_T4_De_0           (E2Addr_Qua4_Re_T3_De_0+CLQua4_Re_T3_De_0+C_CRCLen2)                  /*当前4象限无功费率4最大需量及发生时刻*/
#define E2Addr_Qua4_Re_T5_De_0           (E2Addr_Qua4_Re_T4_De_0+CLQua4_Re_T4_De_0+C_CRCLen2)                  /*当前4象限无功费率5最大需量及发生时刻*/
#define E2Addr_Qua4_Re_T6_De_0           (E2Addr_Qua4_Re_T5_De_0+CLQua4_Re_T5_De_0+C_CRCLen2)                  /*当前4象限无功费率6最大需量及发生时刻*/
#define E2Addr_Qua4_Re_T7_De_0           (E2Addr_Qua4_Re_T6_De_0+CLQua4_Re_T6_De_0+C_CRCLen2)                  /*当前4象限无功费率7最大需量及发生时刻*/
#define E2Addr_Qua4_Re_T8_De_0           (E2Addr_Qua4_Re_T7_De_0+CLQua4_Re_T7_De_0+C_CRCLen2)                  /*当前4象限无功费率8最大需量及发生时刻*/
#define E2Addr_Qua4_Re_T9_De_0           (E2Addr_Qua4_Re_T8_De_0+CLQua4_Re_T8_De_0+C_CRCLen2)                  /*当前4象限无功费率9最大需量及发生时刻*/
#define E2Addr_Qua4_Re_T10_De_0          (E2Addr_Qua4_Re_T9_De_0+CLQua4_Re_T9_De_0+C_CRCLen2)                  /*当前4象限无功费率10最大需量及发生时刻*/
#define E2Addr_Qua4_Re_T11_De_0          (E2Addr_Qua4_Re_T10_De_0+CLQua4_Re_T10_De_0+C_CRCLen2)                /*当前4象限无功费率11最大需量及发生时刻*/
#define E2Addr_Qua4_Re_T12_De_0          (E2Addr_Qua4_Re_T11_De_0+CLQua4_Re_T11_De_0+C_CRCLen2)                /*当前4象限无功费率12最大需量及发生时刻*/

#define E2Addr_PosA_Ac_De_0              (E2Addr_Qua4_Re_T12_De_0+CLQua4_Re_T12_De_0+C_CRCLen2)                /*当前A相正向有功最大需量及发生时刻*/
#define E2Addr_RevA_Ac_De_0              (E2Addr_PosA_Ac_De_0+CLPosA_Ac_De_0+C_CRCLen2)                        /*当前A相反向有功最大需量及发生时刻*/
#define E2Addr_ComA_Re1_De_0             (E2Addr_RevA_Ac_De_0+CLRevA_Ac_De_0+C_CRCLen2)                        /*当前A相组合无功1最大需量及发生时刻*/
#define E2Addr_ComA_Re2_De_0             (E2Addr_ComA_Re1_De_0+CLComA_Re1_De_0+C_CRCLen2)                      /*当前A相组合无功2最大需量及发生时刻*/
#define E2Addr_Qua1A_Re_De_0             (E2Addr_ComA_Re2_De_0+CLComA_Re2_De_0+C_CRCLen2)                      /*当前A相1象限无功最大需量及发生时刻*/
#define E2Addr_Qua2A_Re_De_0             (E2Addr_Qua1A_Re_De_0+CLQua1A_Re_De_0+C_CRCLen2)                      /*当前A相2象限无功最大需量及发生时刻*/
#define E2Addr_Qua3A_Re_De_0             (E2Addr_Qua2A_Re_De_0+CLQua2A_Re_De_0+C_CRCLen2)                      /*当前A相3象限无功最大需量及发生时刻*/
#define E2Addr_Qua4A_Re_De_0             (E2Addr_Qua3A_Re_De_0+CLQua3A_Re_De_0+C_CRCLen2)                      /*当前A相4象限无功最大需量及发生时刻*/

#define E2Addr_PosB_Ac_De_0              (E2Addr_Qua4A_Re_De_0+CLQua4A_Re_De_0+C_CRCLen2)                      /*当前B相正向有功最大需量及发生时刻*/
#define E2Addr_RevB_Ac_De_0              (E2Addr_PosB_Ac_De_0+CLPosB_Ac_De_0+C_CRCLen2)                        /*当前B相反向有功最大需量及发生时刻*/
#define E2Addr_ComB_Re1_De_0             (E2Addr_RevB_Ac_De_0+CLRevB_Ac_De_0+C_CRCLen2)                        /*当前B相组合无功1最大需量及发生时刻*/
#define E2Addr_ComB_Re2_De_0             (E2Addr_ComB_Re1_De_0+CLComB_Re1_De_0+C_CRCLen2)                      /*当前B相组合无功2最大需量及发生时刻*/
#define E2Addr_Qua1B_Re_De_0             (E2Addr_ComB_Re2_De_0+CLComB_Re2_De_0+C_CRCLen2)                      /*当前B相1象限无功最大需量及发生时刻*/
#define E2Addr_Qua2B_Re_De_0             (E2Addr_Qua1B_Re_De_0+CLQua1B_Re_De_0+C_CRCLen2)                      /*当前B相2象限无功最大需量及发生时刻*/
#define E2Addr_Qua3B_Re_De_0             (E2Addr_Qua2B_Re_De_0+CLQua2B_Re_De_0+C_CRCLen2)                      /*当前B相3象限无功最大需量及发生时刻*/
#define E2Addr_Qua4B_Re_De_0             (E2Addr_Qua3B_Re_De_0+CLQua3B_Re_De_0+C_CRCLen2)                      /*当前B相4象限无功最大需量及发生时刻*/

#define E2Addr_PosC_Ac_De_0              (E2Addr_Qua4B_Re_De_0+CLQua4B_Re_De_0+C_CRCLen2)                      /*当前C相正向有功最大需量及发生时刻*/
#define E2Addr_RevC_Ac_De_0              (E2Addr_PosC_Ac_De_0+CLPosC_Ac_De_0+C_CRCLen2)                        /*当前C相反向有功最大需量及发生时刻*/
#define E2Addr_ComC_Re1_De_0             (E2Addr_RevC_Ac_De_0+CLRevC_Ac_De_0+C_CRCLen2)                        /*当前C相组合无功1最大需量及发生时刻*/
#define E2Addr_ComC_Re2_De_0             (E2Addr_ComC_Re1_De_0+CLComC_Re1_De_0+C_CRCLen2)                      /*当前C相组合无功2最大需量及发生时刻*/
#define E2Addr_Qua1C_Re_De_0             (E2Addr_ComC_Re2_De_0+CLComC_Re2_De_0+C_CRCLen2)                      /*当前C相1象限无功最大需量及发生时刻*/
#define E2Addr_Qua2C_Re_De_0             (E2Addr_Qua1C_Re_De_0+CLQua1C_Re_De_0+C_CRCLen2)                      /*当前C相2象限无功最大需量及发生时刻*/
#define E2Addr_Qua3C_Re_De_0             (E2Addr_Qua2C_Re_De_0+CLQua2C_Re_De_0+C_CRCLen2)                      /*当前C相3象限无功最大需量及发生时刻*/
#define E2Addr_Qua4C_Re_De_0             (E2Addr_Qua3C_Re_De_0+CLQua3C_Re_De_0+C_CRCLen2)                      /*当前C相4象限无功最大需量及发生时刻*/
#define E2Addr_De_End                    (E2Addr_Qua4C_Re_De_0+CLQua4C_Re_De_0+C_CRCLen2)                      /*需量记录E2结束地址*/

/*******************电网类事件****************************************************/
#define E2Addr_EventNote_StPage1         E2Addr_De_End                                                         /*事件记录E2存储起始地址*/

#define E2Addr_All_Loss_Vol_Degree       E2Addr_EventNote_StPage1                                              /*全失压总次数*/
#define E2Addr_All_Loss_Vol_Time         (E2Addr_All_Loss_Vol_Degree+CLAll_Loss_Vol_Degree+C_CRCLen2)          /*全失压累计时间*/

#define E2Addr_Aux_Pow_Down_Degree       (E2Addr_All_Loss_Vol_Time+CLAll_Loss_Vol_Time+C_CRCLen2)              /*辅助电源掉电总次数*/
#define E2Addr_Aux_Pow_Down_Time         (E2Addr_Aux_Pow_Down_Degree+CLAux_Pow_Down_Degree+C_CRCLen2)          /*辅助电源掉电总累计时间*/

#define E2Addr_Pow_Down_Degree           (E2Addr_Aux_Pow_Down_Time+CLAux_Pow_Down_Time+C_CRCLen2)              /*掉电总次数*/
#define	E2Addr_Pow_Down_Time             (E2Addr_Pow_Down_Degree+CLPow_Down_Degree+C_CRCLen2)                  /*掉电累计时间*/

#define E2Addr_Pos_Ac_De_Over_Degree     (E2Addr_Pow_Down_Time+CLPow_Down_Time+C_CRCLen2)                      /*正向有功需量超限总次数*/
#define E2Addr_Pos_Ac_De_Over_Time       (E2Addr_Pos_Ac_De_Over_Degree+CLPos_Ac_De_Over_Degree+C_CRCLen2)      /*正向有功需量超限总累计时间*/

#define E2Addr_Rev_Ac_De_Over_Degree     (E2Addr_Pos_Ac_De_Over_Time+CLPos_Ac_De_Over_Time+C_CRCLen2)          /*反向有功需量超限总次数*/
#define E2Addr_Rev_Ac_De_Over_Time       (E2Addr_Rev_Ac_De_Over_Degree+CLRev_Ac_De_Over_Degree+C_CRCLen2)      /*反向有功需量超限总累计时间*/

#define E2Addr_Qua1_Re_De_Over_Degree    (E2Addr_Rev_Ac_De_Over_Time+CLRev_Ac_De_Over_Time+C_CRCLen2)          /*1象限无功需量超限总次数*/
#define E2Addr_Qua1_Re_De_Over_Time      (E2Addr_Qua1_Re_De_Over_Degree+CLQua1_Re_De_Over_Degree+C_CRCLen2)    /*1象限无功需量超限总累计时间*/
#define E2Addr_Qua2_Re_De_Over_Degree    (E2Addr_Qua1_Re_De_Over_Time+CLQua1_Re_De_Over_Time+C_CRCLen2)        /*2象限无功需量超限总次数*/
#define E2Addr_Qua2_Re_De_Over_Time      (E2Addr_Qua2_Re_De_Over_Degree+CLQua2_Re_De_Over_Degree+C_CRCLen2)    /*2象限无功需量超限总累计时间*/
#define E2Addr_Qua3_Re_De_Over_Degree    (E2Addr_Qua2_Re_De_Over_Time+CLQua2_Re_De_Over_Time+C_CRCLen2)        /*3象限无功需量超限总次数*/
#define E2Addr_Qua3_Re_De_Over_Time      (E2Addr_Qua3_Re_De_Over_Degree+CLQua3_Re_De_Over_Degree+C_CRCLen2)    /*3象限无功需量超限总累计时间*/
#define E2Addr_Qua4_Re_De_Over_Degree    (E2Addr_Qua3_Re_De_Over_Time+CLQua3_Re_De_Over_Time+C_CRCLen2)        /*4象限无功需量超限总次数*/
#define E2Addr_Qua4_Re_De_Over_Time      (E2Addr_Qua4_Re_De_Over_Degree+CLQua4_Re_De_Over_Degree+C_CRCLen2)    /*4象限无功需量超限总累计时间*/

#define E2Addr_LossA_Vol_Degree          (E2Addr_Qua4_Re_De_Over_Time+CLQua4_Re_De_Over_Time+C_CRCLen2)        /*A相失压总次数*/
#define E2Addr_LossA_Vol_Time            (E2Addr_LossA_Vol_Degree+CLLossA_Vol_Degree+C_CRCLen2)                /*A相失压总累计时间*/
#define E2Addr_LossB_Vol_Degree          (E2Addr_LossA_Vol_Time+CLLossA_Vol_Time+C_CRCLen2)                    /*B相失压总次数*/
#define E2Addr_LossB_Vol_Time            (E2Addr_LossB_Vol_Degree+CLLossB_Vol_Degree+C_CRCLen2)                /*B相失压总累计时间*/
#define E2Addr_LossC_Vol_Degree          (E2Addr_LossB_Vol_Time+CLLossB_Vol_Time+C_CRCLen2)                    /*C相失压总次数*/
#define E2Addr_LossC_Vol_Time            (E2Addr_LossC_Vol_Degree+CLLossC_Vol_Degree+C_CRCLen2)                /*C相失压总累计时间*/

#define E2Addr_LowA_Vol_Degree           (E2Addr_LossC_Vol_Time+CLLossC_Vol_Time+C_CRCLen2)                    /*A相欠压总次数*/
#define E2Addr_LowA_Vol_Time             (E2Addr_LowA_Vol_Degree+CLLowA_Vol_Degree+C_CRCLen2)                  /*A相欠压总累计时间*/
#define E2Addr_LowB_Vol_Degree           (E2Addr_LowA_Vol_Time+CLLowA_Vol_Time+C_CRCLen2)                      /*B相欠压总次数*/
#define E2Addr_LowB_Vol_Time             (E2Addr_LowB_Vol_Degree+CLLowB_Vol_Degree+C_CRCLen2)                  /*B相欠压总累计时间*/
#define E2Addr_LowC_Vol_Degree           (E2Addr_LowB_Vol_Time+CLLowB_Vol_Time+C_CRCLen2)                      /*C相欠压总次数*/
#define E2Addr_LowC_Vol_Time             (E2Addr_LowC_Vol_Degree+CLLowC_Vol_Degree+C_CRCLen2)                  /*C相欠压总累计时间*/

#define E2Addr_OverA_Vol_Degree          (E2Addr_LowC_Vol_Time+CLLowC_Vol_Time+C_CRCLen2)                      /*A相过压总次数*/
#define E2Addr_OverA_Vol_Time            (E2Addr_OverA_Vol_Degree+CLOverA_Vol_Degree+C_CRCLen2)                /*A相过压总累计时间*/
#define E2Addr_OverB_Vol_Degree          (E2Addr_OverA_Vol_Time+CLOverA_Vol_Time+C_CRCLen2)                    /*B相过压总次数*/
#define E2Addr_OverB_Vol_Time            (E2Addr_OverB_Vol_Degree+CLOverB_Vol_Degree+C_CRCLen2)                /*B相过压总累计时间*/
#define E2Addr_OverC_Vol_Degree          (E2Addr_OverB_Vol_Time+CLOverB_Vol_Time+C_CRCLen2)                    /*C相过压总次数*/
#define E2Addr_OverC_Vol_Time            (E2Addr_OverC_Vol_Degree+CLOverC_Vol_Degree+C_CRCLen2)                /*C相过压总累计时间*/

#define E2Addr_BreakA_Vol_Degree         (E2Addr_OverC_Vol_Time+CLOverC_Vol_Time+C_CRCLen2)                    /*A相相断总次数*/
#define E2Addr_BreakA_Vol_Time           (E2Addr_BreakA_Vol_Degree+CLBreakA_Vol_Degree+C_CRCLen2)              /*A相相断总累计时间*/
#define E2Addr_BreakB_Vol_Degree         (E2Addr_BreakA_Vol_Time+CLBreakA_Vol_Time+C_CRCLen2)                  /*B相相断总次数*/
#define E2Addr_BreakB_Vol_Time           (E2Addr_BreakB_Vol_Degree+CLBreakB_Vol_Degree+C_CRCLen2)              /*B相相断总累计时间*/
#define E2Addr_BreakC_Vol_Degree         (E2Addr_BreakB_Vol_Time+CLBreakB_Vol_Time+C_CRCLen2)                  /*C相相断总次数*/
#define E2Addr_BreakC_Vol_Time           (E2Addr_BreakC_Vol_Degree+CLBreakC_Vol_Degree+C_CRCLen2)              /*C相相断总累计时间*/

#define E2Addr_RevPS_Vol_Degree          (E2Addr_BreakC_Vol_Time+CLBreakC_Vol_Time+C_CRCLen2)                  /*电压逆相序总次数*/
#define E2Addr_RevPS_Vol_Time            (E2Addr_RevPS_Vol_Degree+CLRevPS_Vol_Degree+C_CRCLen2)                /*电压逆相序总累计时间*/

#define E2Addr_RevPS_Curr_Degree         (E2Addr_RevPS_Vol_Time+CLRevPS_Vol_Time+C_CRCLen2)                    /*电流逆相序总次数*/
#define E2Addr_RevPS_Curr_Time           (E2Addr_RevPS_Curr_Degree+CLRevPS_Curr_Degree+C_CRCLen2)              /*电流逆相序总累计时间*/

#define E2Addr_NoBal_Vol_Degree          (E2Addr_RevPS_Curr_Time+CLRevPS_Curr_Time+C_CRCLen2)                  /*电压不平衡总次数*/
#define E2Addr_NoBal_Vol_Time            (E2Addr_NoBal_Vol_Degree+CLNoBal_Vol_Degree+C_CRCLen2)                /*电压不平衡总累计时间*/

#define E2Addr_NoBal_Curr_Degree         (E2Addr_NoBal_Vol_Time+CLNoBal_Vol_Time+C_CRCLen2)                    /*电流不平衡总次数*/
#define E2Addr_NoBal_Curr_Time           (E2Addr_NoBal_Curr_Degree+CLNoBal_Curr_Degree+C_CRCLen2)              /*电流不平衡总累计时间*/

#define E2Addr_SevNoBal_Curr_Degree      (E2Addr_NoBal_Curr_Time+CLNoBal_Curr_Time+C_CRCLen2)                  /*电流严重不平衡总次数*/
#define E2Addr_SevNoBal_Curr_Time        (E2Addr_SevNoBal_Curr_Degree+CLSevNoBal_Curr_Degree+C_CRCLen2)        /*电流严重不平衡总累计时间*/

#define E2Addr_LossA_Curr_Degree         (E2Addr_SevNoBal_Curr_Time+CLSevNoBal_Curr_Time+C_CRCLen2)            /*A相失流总次数*/
#define E2Addr_LossA_Curr_Time           (E2Addr_LossA_Curr_Degree+CLLossA_Curr_Degree+C_CRCLen2)              /*A相失流总累计时间*/
#define E2Addr_LossB_Curr_Degree         (E2Addr_LossA_Curr_Time+CLLossA_Curr_Time+C_CRCLen2)                  /*B相失流总次数*/
#define E2Addr_LossB_Curr_Time           (E2Addr_LossB_Curr_Degree+CLLossB_Curr_Degree+C_CRCLen2)              /*B相失流总累计时间*/
#define E2Addr_LossC_Curr_Degree         (E2Addr_LossB_Curr_Time+CLLossB_Curr_Time+C_CRCLen2)                  /*C相失流总次数*/
#define E2Addr_LossC_Curr_Time           (E2Addr_LossC_Curr_Degree+CLLossC_Curr_Degree+C_CRCLen2)              /*C相失流总累计时间*/

#define E2Addr_OverA_Curr_Degree         (E2Addr_LossC_Curr_Time+CLLossC_Curr_Time+C_CRCLen2)                  /*A相过流总次数*/
#define E2Addr_OverA_Curr_Time           (E2Addr_OverA_Curr_Degree+CLOverA_Curr_Degree+C_CRCLen2)              /*A相过流总累计时间*/
#define E2Addr_OverB_Curr_Degree         (E2Addr_OverA_Curr_Time+CLOverA_Curr_Time+C_CRCLen2)                  /*B相过流总次数*/
#define E2Addr_OverB_Curr_Time           (E2Addr_OverB_Curr_Degree+CLOverB_Curr_Degree+C_CRCLen2)              /*B相过流总累计时间*/
#define E2Addr_OverC_Curr_Degree         (E2Addr_OverB_Curr_Time+CLOverB_Curr_Time+C_CRCLen2)                  /*C相过流总次数*/
#define E2Addr_OverC_Curr_Time           (E2Addr_OverC_Curr_Degree+CLOverC_Curr_Degree+C_CRCLen2)              /*C相过流总累计时间*/

#define E2Addr_BreakA_Curr_Degree        (E2Addr_OverC_Curr_Time+CLOverC_Curr_Time+C_CRCLen2)                  /*A相断流总次数*/
#define E2Addr_BreakA_Curr_Time          (E2Addr_BreakA_Curr_Degree+CLBreakA_Curr_Degree+C_CRCLen2)            /*A相断流总累计时间*/
#define E2Addr_BreakB_Curr_Degree        (E2Addr_BreakA_Curr_Time+CLBreakA_Curr_Time+C_CRCLen2)                /*B相断流总次数*/
#define E2Addr_BreakB_Curr_Time          (E2Addr_BreakB_Curr_Degree+CLBreakB_Curr_Degree+C_CRCLen2)            /*B相断流总累计时间*/
#define E2Addr_BreakC_Curr_Degree        (E2Addr_BreakB_Curr_Time+CLBreakB_Curr_Time+C_CRCLen2)                /*C相断流总次数*/
#define E2Addr_BreakC_Curr_Time          (E2Addr_BreakC_Curr_Degree+CLBreakC_Curr_Degree+C_CRCLen2)            /*C相断流总累计时间*/

#define E2Addr_PowerT_Rev_Degree         (E2Addr_BreakC_Curr_Time+CLBreakC_Curr_Time+C_CRCLen2)                /*总功率反向总次数*/
#define E2Addr_PowerT_Rev_Time           (E2Addr_PowerT_Rev_Degree+CLPowerT_Rev_Degree+C_CRCLen2)              /*总功率反向总累计时间*/
#define E2Addr_PowerA_Rev_Degree         (E2Addr_PowerT_Rev_Time+CLPowerT_Rev_Time+C_CRCLen2)                  /*A相功率反向总次数*/
#define E2Addr_PowerA_Rev_Time           (E2Addr_PowerA_Rev_Degree+CLPowerA_Rev_Degree+C_CRCLen2)              /*A相功率反向总累计时间*/
#define E2Addr_PowerB_Rev_Degree         (E2Addr_PowerA_Rev_Time+CLPowerA_Rev_Time+C_CRCLen2)                  /*B相功率反向总次数*/
#define E2Addr_PowerB_Rev_Time           (E2Addr_PowerB_Rev_Degree+CLPowerB_Rev_Degree+C_CRCLen2)              /*B相功率反向总累计时间*/
#define E2Addr_PowerC_Rev_Degree         (E2Addr_PowerB_Rev_Time+CLPowerB_Rev_Time+C_CRCLen2)                  /*C相功率反向总次数*/
#define E2Addr_PowerC_Rev_Time           (E2Addr_PowerC_Rev_Degree+CLPowerC_Rev_Degree+C_CRCLen2)              /*C相功率反向总累计时间*/

#define E2Addr_OverA_Lo_Degree           (E2Addr_PowerC_Rev_Time+CLPowerC_Rev_Time+C_CRCLen2)                  /*A相过载总次数*/
#define E2Addr_OverA_Lo_Time             (E2Addr_OverA_Lo_Degree+CLOverA_Lo_Degree+C_CRCLen2)                  /*A相过载总累计时间*/
#define E2Addr_OverB_Lo_Degree           (E2Addr_OverA_Lo_Time+CLOverA_Lo_Time+C_CRCLen2)                      /*B相过载总次数*/
#define E2Addr_OverB_Lo_Time             (E2Addr_OverB_Lo_Degree+CLOverB_Lo_Degree+C_CRCLen2)                  /*B相过载总累计时间*/
#define E2Addr_OverC_Lo_Degree           (E2Addr_OverB_Lo_Time+CLOverB_Lo_Time+C_CRCLen2)                      /*C相过载总次数*/
#define E2Addr_OverC_Lo_Time             (E2Addr_OverC_Lo_Degree+CLOverC_Lo_Degree+C_CRCLen2)                  /*C相过载总累计时间*/

#define E2Addr_PFactorT_Over_Degree      (E2Addr_OverC_Lo_Time+CLOverC_Lo_Time+C_CRCLen2)                      /*总功率因数超下限总次数*/
#define E2Addr_PFactorT_Over_Time        (E2Addr_PFactorT_Over_Degree+CLPFactorT_Over_Degree+C_CRCLen2)        /*总功率因数超下限总累计时间*/
#define E2Addr_PFactorA_Over_Degree      (E2Addr_PFactorT_Over_Time+CLPFactorT_Over_Time+C_CRCLen2)            /*A功率因数超下限总次数*/
#define E2Addr_PFactorA_Over_Time        (E2Addr_PFactorA_Over_Degree+CLPFactorA_Over_Degree+C_CRCLen2)        /*A功率因数超下限总累计时间*/
#define E2Addr_PFactorB_Over_Degree      (E2Addr_PFactorA_Over_Time+CLPFactorA_Over_Time+C_CRCLen2)            /*B功率因数超下限总次数*/
#define E2Addr_PFactorB_Over_Time        (E2Addr_PFactorB_Over_Degree+CLPFactorB_Over_Degree+C_CRCLen2)        /*B功率因数超下限总累计时间*/
#define E2Addr_PFactorC_Over_Degree      (E2Addr_PFactorB_Over_Time+CLPFactorB_Over_Time+C_CRCLen2)            /*C功率因数超下限总次数*/
#define E2Addr_PFactorC_Over_Time        (E2Addr_PFactorC_Over_Degree+CLPFactorC_Over_Degree+C_CRCLen2)        /*C功率因数超下限总累计时间*/

#define E2Addr_NeutralCurrentAbnormal_Degree    (E2Addr_PFactorC_Over_Time+CLPFactorC_Over_Time+C_CRCLen2)     /*零线电流异常总次数*/
#define E2Addr_NeutralCurrentAbnormal_Time      (E2Addr_NeutralCurrentAbnormal_Degree+CLNeutralCurrentAbnormal_Degree+C_CRCLen2)    /*零线电流异常总累计时间*/

/**************编程类*******************/
#define E2Addr_De_Clear_Degree           (E2Addr_NeutralCurrentAbnormal_Time+CLNeutralCurrentAbnormal_Time+C_CRCLen2)    /*需量清零总次数*/
#define E2Addr_RelayClose_Degree         (E2Addr_De_Clear_Degree+CLDe_Clear_Degree+C_CRCLen2)                 /*合闸记录总次数*/
#define E2Addr_Program_Degree            (E2Addr_RelayClose_Degree+CLRelayClose_Degree+C_CRCLen2)             /*编程记录总次数*/
#define E2Addr_AdjTime_Degree            (E2Addr_Program_Degree+CLProgram_Degree+C_CRCLen2)                   /*校时记录总次数*/
#define E2Addr_BroadcastTime_Degree      (E2Addr_AdjTime_Degree+CLAdjTime_Degree+C_CRCLen2)                   /*广播校时记录总次数*/
#define E2Addr_ProgPT_Degree             (E2Addr_BroadcastTime_Degree+CLBroadcastTime_Degree+C_CRCLen2)       /*时段表编程记录总次数*/
#define E2Addr_ProgTZ_Degree             (E2Addr_ProgPT_Degree+CLProgPT_Degree+C_CRCLen2)                     /*时区表编程记录总次数*/
#define E2Addr_ProgWRe_Degree            (E2Addr_ProgTZ_Degree+CLProgTZ_Degree+C_CRCLen2)                     /*周休日编程记录总次数*/
#define E2Addr_ProgHol_Degree            (E2Addr_ProgWRe_Degree+CLProgWRe_Degree+C_CRCLen2)                   /*节假日编程记录总次数*/
#define E2Addr_ProgAcC_Degree            (E2Addr_ProgHol_Degree+CLProgHol_Degree+C_CRCLen2)                   /*有功组合方式编程记录总次数*/
#define E2Addr_ProgReC1_Degree           (E2Addr_ProgAcC_Degree+CLProgAcC_Degree+C_CRCLen2)                   /*无功组合方式1编程记录总次数*/
#define E2Addr_ProgSettD_Degree          (E2Addr_ProgReC1_Degree+CLProgReC_Degree+C_CRCLen2)                  /*结算日编程记录总次数*/
#define E2Addr_ProgTPara_Degree          (E2Addr_ProgSettD_Degree+CLProgSettD_Degree+C_CRCLen2)               /*费率参数表编程记录总次数*/
#define E2Addr_ProgLad_Degree            (E2Addr_ProgTPara_Degree+CLProgTPara_Degree+C_CRCLen2)               /*阶梯表编程记录总次数*/
#define E2Addr_ProgKD_Degree             (E2Addr_ProgLad_Degree+CLProgLad_Degree+C_CRCLen2)                   /*密钥编程记录总次数*/
#define E2Addr_AbnorC_Degree             (E2Addr_ProgKD_Degree+CLProgKD_Degree+C_CRCLen2)                     /*异常插卡记录总次数*/

#define E2Addr_OpenW_Degree              (E2Addr_AbnorC_Degree+CLAbnorC_Degree+C_CRCLen2)                     /*开表盖记录总次数*/
#define E2Addr_OpenW_Time	             (E2Addr_OpenW_Degree+CLOpenW_Degree+C_CRCLen2)                       /*开表盖记录累计时间*/

#define E2Addr_OpenCW_Degree             (E2Addr_OpenW_Time+CLOpenW_Time+C_CRCLen2)                           /*开端钮盖记录总次数*/
#define E2Addr_OpenCW_Time               (E2Addr_OpenCW_Degree+CLOpenCW_Degree+C_CRCLen2)                     /*开端钮盖累计时间*/

#define E2Addr_BuyCurr_Degree            (E2Addr_OpenCW_Time+CLOpenCW_Time+C_CRCLen2)                         /*购电记录总次数*/
#define E2Addr_Return_M_Degree           (E2Addr_BuyCurr_Degree+CLBuyCurr_Degree+C_CRCLen2)                   /*退费记录总次数*/
#define E2Addr_LawlessC_Degree           (E2Addr_Return_M_Degree+CLReturn_M_Degree+C_CRCLen2)                 /*非法插卡总次数,无事件记录*/

#define E2Addr_ConM_Degree               (E2Addr_LawlessC_Degree+CLLawlessC_Degree+C_CRCLen2)                 /*恒定磁场干扰记录总次数*/
#define E2Addr_ConM_Time                 (E2Addr_ConM_Degree+CLConM_Degree+C_CRCLen2)                         /*恒定磁场干扰记录累计时间*/

#define E2Addr_RelayFa_Degree            (E2Addr_ConM_Time+CLConM_Time+C_CRCLen2)                             /*负荷开关误动作记录总次数*/
#define E2Addr_RelayFa_Time              (E2Addr_RelayFa_Degree+CLRelayFa_Degree+C_CRCLen2)                   /*负荷开关误动作记录累计时间*/

#define E2Addr_PowerFa_Degree            (E2Addr_RelayFa_Time+CLRelayFa_Time+C_CRCLen2)                       /*电源异常记录总次数*/
#define E2Addr_PowerFa_Time              (E2Addr_PowerFa_Degree+CLPowerFa_Degree+C_CRCLen2)                   /*电源异常记录总累计时间*/

#define E2Addr_MeterFa_Degree            (E2Addr_PowerFa_Time+CLPowerFa_Time+C_CRCLen2)                       /*计量芯片异常记录总次数*/
#define E2Addr_MeterFa_Time              (E2Addr_MeterFa_Degree+CLMeterFa_Degree+C_CRCLen2)                   /*计量芯片异常记录总累计时间*/

#define E2Addr_ClockFa_Degree            (E2Addr_MeterFa_Time+CLMeterFa_Time+C_CRCLen2)                       /*时钟故障异常记录总次数*/
#define E2Addr_ClockFa_Time              (E2Addr_ClockFa_Degree+CLClockFa_Degree+C_CRCLen2)                   /*时钟故障异常记录总累计时间*/

#define E2Addr_RelayOpen_Degree          (E2Addr_ClockFa_Time+CLClockFa_Time+C_CRCLen2)                       /*跳闸记录总次数*/

#define E2Addr_Soft_I_J_Prog_Degree      (E2Addr_RelayOpen_Degree+CLRelayOpen_Degree+C_CRCLen2)               /*软IJ有效时间编程总次数,次数为3字节，读、写记录特殊处理*/

#define E2Addr_Even_Clear_Degree         (E2Addr_Soft_I_J_Prog_Degree+CLSoft_I_J_Prog_Degree+C_CRCLen2)       /*事件清零总次数,放事件记录E2存储空间最后，方便事件记录总清*/

#define E2Addr_EventNote_End_OutTol      E2Addr_Even_Clear_Degree                                             /*事件记录E2存储结束地址,不包含事件清零总次数*/

#define E2Addr_Rec_Meter_Degree          (E2Addr_Even_Clear_Degree+CLEven_Clear_Degree+C_CRCLen2)             /*校表总次数，次数为3字节，读、写记录特殊处理*/

#define E2Addr_EventNote_End             E2Addr_Rec_Meter_Degree                                              /*事件记录E2存储结束地址,不包括校表记录清零*/

#define E2Addr_Tol_Clear_Out_End         (E2Addr_Rec_Meter_Degree+CLRec_Meter_Degree+C_CRCLen2)               /*总清厂外模式结束地址*/
#define E2Addr_Tol_Clear_Degree          (E2Addr_Rec_Meter_Degree+CLRec_Meter_Degree+C_CRCLen2)               /*电表清零总次数,放E2清零最后，方便总清厂内、厂外区分*/
#define E2Addr_Tol_Clear_In_End          (E2Addr_Tol_Clear_Degree+CLTol_Clear_Degree+C_CRCLen2)               /*总清厂内模式结束地址*/

/**************************************参变量******************************************/
#define E2Addr_Demand_Cycle              (E2Addr_Tol_Clear_Degree+CLTol_Clear_Degree+C_CRCLen2)                    /*最大需量周期*/
#define E2Addr_Sliding_Time              (E2Addr_Demand_Cycle+CLDemand_Cycle+C_CRCLen2)                            /*滑差时间*/

#define E2Addr_BroadcastTimeOffset_Min   (E2Addr_Sliding_Time+CLSliding_Time+C_CRCLen2)                            /*广播校时偏差最小值*/
#define E2Addr_BroadcastTimeOffset_Max   (E2Addr_BroadcastTimeOffset_Min+CLBroadcastTimeOffset_Min+C_CRCLen2)      /*广播校时偏差最大值*/

#define E2Addr_Change_TZ_Time            (E2Addr_BroadcastTimeOffset_Max+CLBroadcastTimeOffset_Max+C_CRCLen2)      /*两套时区表切换时间*/
#define E2Addr_Change_PT_Time            (E2Addr_Change_TZ_Time+CLChange_TZ_Time+C_CRCLen2)                        /*两套日时段表切换时间*/
#define E2Addr_Change_Rate               (E2Addr_Change_PT_Time+CLChange_PT_Time+C_CRCLen2)                        /*两套费率电价切换时间*/
#define E2Addr_Change_Ladder             (E2Addr_Change_Rate+CLChange_Rate+C_CRCLen2)                              /*两套阶梯电价切换时间*/

#define E2Addr_Year_Zone_Num             (E2Addr_Change_Ladder+CLChange_Ladder+C_CRCLen2)                          /*年时区数*/
#define E2Addr_Day_Table_Num             (E2Addr_Year_Zone_Num+CLYear_Zone_Num+C_CRCLen2)                          /*日时段表数*/
#define E2Addr_Day_Time_Num              (E2Addr_Day_Table_Num+CLDay_Table_Num+C_CRCLen2)                          /*日时段数*/
#define E2Addr_Rate_Num                  (E2Addr_Day_Time_Num+CLDay_Time_Num+C_CRCLen2)                            /*费率数*/
#define E2Addr_Holiday_Num               (E2Addr_Rate_Num+CLRate_Num+C_CRCLen2)                                    /*公共假日数*/

#define E2Addr_Step_Num                  (E2Addr_Holiday_Num+CLHoliday_Num+C_CRCLen2)                              /*阶梯数*/

#define E2Addr_Per_Dis_Screen_Time       (E2Addr_Step_Num+CLStep_Num+C_CRCLen2)                                    /*循显每屏显示时间*/
#define E2Addr_Auto_Dis_Screen_Num       (E2Addr_Per_Dis_Screen_Time+CLPer_Dis_Screen_Time+C_CRCLen2)              /*循显屏数*/
#define E2Addr_Auto_Dis_Screen_MaxNum    (E2Addr_Auto_Dis_Screen_Num+CLAuto_Dis_Screen_Num+C_CRCLen2)              /*循显最大屏数*/

#define E2Addr_Perkey_Dis_Screen_Time    (E2Addr_Auto_Dis_Screen_MaxNum+CLAuto_Dis_Screen_MaxNum+C_CRCLen2)        /*键显每屏显示时间*/
#define E2Addr_Key_CycDis_Screen_Num     (E2Addr_Perkey_Dis_Screen_Time+CLPerkey_Dis_Screen_Time+C_CRCLen2)        /*键显屏数*/
#define E2Addr_Key_CycDis_Screen_MaxNum  (E2Addr_Key_CycDis_Screen_Num+CLKey_CycDis_Screen_Num+C_CRCLen2)          /*键显最大屏数*/

#define E2Addr_PowerOn_Dis_All_Time      (E2Addr_Key_CycDis_Screen_MaxNum+CLKey_CycDis_Screen_MaxNum+C_CRCLen2)    /*上电全显时间*/
#define E2Addr_BacklightTime             (E2Addr_PowerOn_Dis_All_Time+CLPowerOn_Dis_All_Time+C_CRCLen2)            /*背光点亮时间*/
#define E2Addr_SViewBacklightTime        (E2Addr_BacklightTime+CLBacklightTime+C_CRCLen2)                          /*显示查看背光点亮时间*/
#define E2Addr_NEScreenDisplay           (E2Addr_SViewBacklightTime+CLSViewBacklightTime+C_CRCLen2)                /*无电按键屏幕驻留最大时间*/
#define E2Addr_Energy_Decimal_Num        (E2Addr_NEScreenDisplay+CLNEScreenDisplay+C_CRCLen2)                      /*电能小数位数*/
#define E2Addr_Power_Decimal_Num         (E2Addr_Energy_Decimal_Num+CLEnergy_Decimal_Num+C_CRCLen2)                /*显示功率（最大需量）小数位数*/
#define E2Addr_1And2Display              (E2Addr_Power_Decimal_Num+CLPower_Decimal_Num+C_CRCLen2)                  /*液晶①②字样意义*/

#define E2Addr_Ratio_Curr_Tran           (E2Addr_1And2Display+CL1And2Display+C_CRCLen2)                      /*电流互感器变比*/
#define E2Addr_Ratio_Vol_Tran            (E2Addr_Ratio_Curr_Tran+CLRatio_Curr_Tran+C_CRCLen2)                /*电压互感器变比*/
#define E2Addr_Comm_Address              (E2Addr_Ratio_Vol_Tran+CLRatio_Vol_Tran+C_CRCLen2)                  /*通讯地址*/
#define E2Addr_Meter_Num                 (E2Addr_Comm_Address+CLComm_Address+C_CRCLen2)                      /*表号*/
#define E2Addr_Manage_Code               (E2Addr_Meter_Num+CLMeter_Num+C_CRCLen2)                            /*资产管理编码*/
#define E2Addr_Rated_Vol                 (E2Addr_Manage_Code+CLManage_Code+C_CRCLen2)                        /*额定电压*/
#define E2Addr_Rated_Curr                (E2Addr_Rated_Vol+CLRated_Vol+C_CRCLen2)                            /*额定电流/基本电流*/
#define E2Addr_Max_Curr                  (E2Addr_Rated_Curr+CLRated_Curr+C_CRCLen2)                          /*最大电流*/
#define E2Addr_Min_Curr                  (E2Addr_Max_Curr+CLMax_Curr+C_CRCLen2)                              /*最小电流*/
#define E2Addr_Turn_Curr                 (E2Addr_Min_Curr+CLMin_Curr+C_CRCLen2)                              /*转折电流*/
#define E2Addr_Active_Accur_Deg          (E2Addr_Turn_Curr+CLTurn_Curr+C_CRCLen2)                            /*有功准确度等级*/
#define E2Addr_Reactive_Accur_Deg        (E2Addr_Active_Accur_Deg+CLActive_Accur_Deg+C_CRCLen2)              /*无功准确度等级*/
#define E2Addr_Meter_Ac_Const            (E2Addr_Reactive_Accur_Deg+CLReactive_Accur_Deg+C_CRCLen2)          /*电表有功常数*/
#define E2Addr_Meter_Re_Const            (E2Addr_Meter_Ac_Const+CLMeter_Ac_Const+C_CRCLen2)                  /*电表有无功常数*/
#define E2Addr_Meter_Model               (E2Addr_Meter_Re_Const+CLMeter_Re_Const+C_CRCLen2)                  /*电表型号*/

/*考虑放置在E2一处*/
#define E2Addr_Prod_Date                 (E2Addr_Meter_Model+CLMeter_Model+C_CRCLen2)                        /*生产日期*/
#define E2Addr_Prot_Version_Num          (E2Addr_Prod_Date+CLProd_Date+C_CRCLen2)                            /*协议版本号*/

#define E2Addr_Customer_Num              (E2Addr_Prot_Version_Num+CLProt_Version_Num+C_CRCLen2)              /*客户编号*/
#define E2Addr_Meter_Position            (E2Addr_Customer_Num+CLCustomer_Num+C_CRCLen2)                      /*电能表位置信息:经度、纬度、高度*/

#define E2Addr_Active_Com_State          (E2Addr_Meter_Position+CLMeter_Position+C_CRCLen2)                  /*有功组合状态字*/
#define E2Addr_Reactive_Com_State1       (E2Addr_Active_Com_State+CLActive_Com_State+C_CRCLen2)              /*无功组合状态字1*/
#define E2Addr_Reactive_Com_State2       (E2Addr_Reactive_Com_State1+CLReactive_Com_State1+C_CRCLen2)        /*无功组合状态字2*/

#define E2Addr_Mod_InFr_Baud             (E2Addr_Reactive_Com_State2+CLReactive_Com_State2+C_CRCLen2)        /*调制型红外光口波特率特征字*/
#define E2Addr_One485_Baud               (E2Addr_Mod_InFr_Baud+CLMod_InFr_Baud+C_CRCLen2)                    /*1路485波特率特征字*/
#define E2Addr_Two485_Baud               (E2Addr_One485_Baud+CLOne485_Baud+C_CRCLen2)                        /*2路485波特率特征字*/
#define E2Addr_Modular_Baud              (E2Addr_Two485_Baud+CLTwo485_Baud+C_CRCLen2)                        /*模块通道波特率特征字*/

#define E2Addr_Week_RestDay              (E2Addr_Modular_Baud+CLModular_Baud+C_CRCLen2)                      /*周休日特征字*/
#define E2Addr_Week_RestDay_DTable       (E2Addr_Week_RestDay+CLWeek_RestDay+C_CRCLen2)                      /*周休日采取的日时段表号*/

#define E2Addr_Settle_Day1               (E2Addr_Week_RestDay_DTable+CLWeek_RestDay_DTable+C_CRCLen2)        /*每月第1结算日*/
#define E2Addr_Settle_Day2               (E2Addr_Settle_Day1+CLSettle_Day1+C_CRCLen2)                        /*每月第2结算日*/
#define E2Addr_Settle_Day3               (E2Addr_Settle_Day2+CLSettle_Day2+C_CRCLen2)                        /*每月第3结算日*/

#define E2Addr_Key_0_Class               (E2Addr_Settle_Day3+CLSettle_Day3+C_CRCLen2)                        /*0级密码*/
#define E2Addr_Key_1_Class               (E2Addr_Key_0_Class+CLKey_0_Class+C_CRCLen2)                        /*1级密码*/
#define E2Addr_Key_2_Class               (E2Addr_Key_1_Class+CLKey_1_Class+C_CRCLen2)                        /*2级密码*/
#define E2Addr_Key_3_Class               (E2Addr_Key_2_Class+CLKey_2_Class+C_CRCLen2)                        /*3级密码*/
#define E2Addr_Key_4_Class               (E2Addr_Key_3_Class+CLKey_3_Class+C_CRCLen2)                        /*4级密码*/

#if 0		/*645密码仅保留0-4密级对应密码*/
#define E2Addr_Key_5_Class               (E2Addr_Key_4_Class+CLKey_4_Class+C_CRCLen2)                        /*5级密码*/
#define E2Addr_Key_6_Class               (E2Addr_Key_5_Class+CLKey_5_Class+C_CRCLen2)                        /*6级密码*/
#define E2Addr_Key_7_Class               (E2Addr_Key_6_Class+CLKey_6_Class+C_CRCLen2)                        /*7级密码*/
#define E2Addr_Key_8_Class               (E2Addr_Key_7_Class+CLKey_7_Class+C_CRCLen2)                        /*8级密码*/
#define E2Addr_Key_9_Class               (E2Addr_Key_8_Class+CLKey_8_Class+C_CRCLen2)                        /*9级密码*/

#define E2Addr_Alam1_Money               (E2Addr_Key_9_Class+CLKey_9_Class+C_CRCLen2)                        /*报警金额1限值*/
#endif

#define E2Addr_Alam1_Money               (E2Addr_Key_4_Class+CLKey_4_Class+C_CRCLen2)                        /*报警金额1限值*/
#define E2Addr_Alam2_Money               (E2Addr_Alam1_Money+CLAlam1_Money+C_CRCLen2)                        /*报警金额2限值*/

#define E2Addr_OverDraft_Money           (E2Addr_Alam2_Money+CLAlam2_Money+C_CRCLen2)                        /*透支金额限值*/
#define E2Addr_Hoarding_Money            (E2Addr_OverDraft_Money+CLOverDraft_Money+C_CRCLen2)                /*囤积金额限值*/
#define E2Addr_Close_Relay_Money         (E2Addr_Hoarding_Money+CLHoarding_Money+C_CRCLen2)                  /*合闸允许金额限值*/

#define E2Addr_Return_Money              (E2Addr_Close_Relay_Money+CLClose_Relay_Money+C_CRCLen2)            /*退费金额*/

#define E2Addr_Drive_Report_Mode         (E2Addr_Return_Money+CLReturn_Money+C_CRCLen2)                      /*主动上报模式字*/

//#define E2Addr_Relay_Delay_Time          (E2Addr_Drive_Report_Mode+CLDrive_Report_Mode+C_CRCLen2)          /*跳闸延时时间*/
#define E2Addr_Relay_Open_CurrTreshold   (E2Addr_Drive_Report_Mode+CLDrive_Report_Mode+C_CRCLen2)            /*继电器拉闸控制电流门限值*/

#define E2Addr_First_TZone_Data          (E2Addr_Relay_Open_CurrTreshold+CLRelay_Open_CurrTreshold+C_CRCLen2)    /*第一套时区表数据*/
#define E2Addr_First_TZone_1PT_Data      (E2Addr_First_TZone_Data+CLFirst_TZone_Data+C_CRCLen2)              /*第一套第1日时段表数据*/
#define E2Addr_First_TZone_2PT_Data      (E2Addr_First_TZone_1PT_Data+CLFirst_TZone_1PT_Data+C_CRCLen2)      /*第一套第2日时段表数据*/
#define E2Addr_First_TZone_3PT_Data      (E2Addr_First_TZone_2PT_Data+CLFirst_TZone_2PT_Data+C_CRCLen2)      /*第一套第3日时段表数据*/
#define E2Addr_First_TZone_4PT_Data      (E2Addr_First_TZone_3PT_Data+CLFirst_TZone_3PT_Data+C_CRCLen2)      /*第一套第4日时段表数据*/
#define E2Addr_First_TZone_5PT_Data      (E2Addr_First_TZone_4PT_Data+CLFirst_TZone_4PT_Data+C_CRCLen2)      /*第一套第5日时段表数据*/
#define E2Addr_First_TZone_6PT_Data      (E2Addr_First_TZone_5PT_Data+CLFirst_TZone_5PT_Data+C_CRCLen2)      /*第一套第6日时段表数据*/
#define E2Addr_First_TZone_7PT_Data      (E2Addr_First_TZone_6PT_Data+CLFirst_TZone_6PT_Data+C_CRCLen2)      /*第一套第7日时段表数据*/
#define E2Addr_First_TZone_8PT_Data      (E2Addr_First_TZone_7PT_Data+CLFirst_TZone_7PT_Data+C_CRCLen2)      /*第一套第8日时段表数据*/

#define E2Addr_Sec_TZone_Data            (E2Addr_First_TZone_8PT_Data+CLFirst_TZone_8PT_Data+C_CRCLen2)      /*第二套时区表数据*/
#define E2Addr_Sec_TZone_1PT_Data        (E2Addr_Sec_TZone_Data+CLSec_TZone_Data+C_CRCLen2)                  /*第二套第1日时段表数据*/
#define E2Addr_Sec_TZone_2PT_Data        (E2Addr_Sec_TZone_1PT_Data+CLSec_TZone_1PT_Data+C_CRCLen2)          /*第二套第2日时段表数据*/
#define E2Addr_Sec_TZone_3PT_Data        (E2Addr_Sec_TZone_2PT_Data+CLSec_TZone_2PT_Data+C_CRCLen2)          /*第二套第3日时段表数据*/
#define E2Addr_Sec_TZone_4PT_Data        (E2Addr_Sec_TZone_3PT_Data+CLSec_TZone_3PT_Data+C_CRCLen2)          /*第二套第4日时段表数据*/
#define E2Addr_Sec_TZone_5PT_Data        (E2Addr_Sec_TZone_4PT_Data+CLSec_TZone_4PT_Data+C_CRCLen2)          /*第二套第5日时段表数据*/
#define E2Addr_Sec_TZone_6PT_Data        (E2Addr_Sec_TZone_5PT_Data+CLSec_TZone_5PT_Data+C_CRCLen2)          /*第二套第6日时段表数据*/
#define E2Addr_Sec_TZone_7PT_Data        (E2Addr_Sec_TZone_6PT_Data+CLSec_TZone_6PT_Data+C_CRCLen2)          /*第二套第7日时段表数据*/
#define E2Addr_Sec_TZone_8PT_Data        (E2Addr_Sec_TZone_7PT_Data+CLSec_TZone_7PT_Data+C_CRCLen2)          /*第二套第8日时段表数据*/

#define E2Addr_Current_Rate1_Price       (E2Addr_Sec_TZone_8PT_Data+CLSec_TZone_8PT_Data+C_CRCLen2)          /*当前费率1-12电价*/
#define E2Addr_Current_Rate2_Price       (E2Addr_Current_Rate1_Price+CLCurrent_Rate1_Price+C_CRCLen2)        /**/
#define E2Addr_Current_Rate3_Price       (E2Addr_Current_Rate2_Price+CLCurrent_Rate2_Price+C_CRCLen2)        /**/
#define E2Addr_Current_Rate4_Price       (E2Addr_Current_Rate3_Price+CLCurrent_Rate3_Price+C_CRCLen2)        /**/
#define E2Addr_Current_Rate5_Price       (E2Addr_Current_Rate4_Price+CLCurrent_Rate4_Price+C_CRCLen2)        /**/
#define E2Addr_Current_Rate6_Price       (E2Addr_Current_Rate5_Price+CLCurrent_Rate5_Price+C_CRCLen2)        /**/
#define E2Addr_Current_Rate7_Price       (E2Addr_Current_Rate6_Price+CLCurrent_Rate6_Price+C_CRCLen2)        /**/
#define E2Addr_Current_Rate8_Price       (E2Addr_Current_Rate7_Price+CLCurrent_Rate7_Price+C_CRCLen2)        /**/
#define E2Addr_Current_Rate9_Price       (E2Addr_Current_Rate8_Price+CLCurrent_Rate8_Price+C_CRCLen2)        /**/
#define E2Addr_Current_Rate10_Price      (E2Addr_Current_Rate9_Price+CLCurrent_Rate9_Price+C_CRCLen2)        /**/
#define E2Addr_Current_Rate11_Price      (E2Addr_Current_Rate10_Price+CLCurrent_Rate10_Price+C_CRCLen2)      /**/
#define E2Addr_Current_Rate12_Price      (E2Addr_Current_Rate11_Price+CLCurrent_Rate11_Price+C_CRCLen2)      /**/

#define E2Addr_BackUp_Rate1_Price        (E2Addr_Current_Rate12_Price+CLCurrent_Rate12_Price+C_CRCLen2)      /*备用套费率1-12电价*/
#define E2Addr_BackUp_Rate2_Price        (E2Addr_BackUp_Rate1_Price+CLBackUp_Rate1_Price+C_CRCLen2)          /**/
#define E2Addr_BackUp_Rate3_Price        (E2Addr_BackUp_Rate2_Price+CLBackUp_Rate2_Price+C_CRCLen2)          /**/
#define E2Addr_BackUp_Rate4_Price        (E2Addr_BackUp_Rate3_Price+CLBackUp_Rate3_Price+C_CRCLen2)          /**/
#define E2Addr_BackUp_Rate5_Price        (E2Addr_BackUp_Rate4_Price+CLBackUp_Rate4_Price+C_CRCLen2)          /**/
#define E2Addr_BackUp_Rate6_Price        (E2Addr_BackUp_Rate5_Price+CLBackUp_Rate5_Price+C_CRCLen2)          /**/
#define E2Addr_BackUp_Rate7_Price        (E2Addr_BackUp_Rate6_Price+CLBackUp_Rate6_Price+C_CRCLen2)          /**/
#define E2Addr_BackUp_Rate8_Price        (E2Addr_BackUp_Rate7_Price+CLBackUp_Rate7_Price+C_CRCLen2)          /**/
#define E2Addr_BackUp_Rate9_Price        (E2Addr_BackUp_Rate8_Price+CLBackUp_Rate8_Price+C_CRCLen2)          /**/
#define E2Addr_BackUp_Rate10_Price       (E2Addr_BackUp_Rate9_Price+CLBackUp_Rate9_Price+C_CRCLen2)          /**/
#define E2Addr_BackUp_Rate11_Price       (E2Addr_BackUp_Rate10_Price+CLBackUp_Rate10_Price+C_CRCLen2)        /**/
#define E2Addr_BackUp_Rate12_Price       (E2Addr_BackUp_Rate11_Price+CLBackUp_Rate11_Price+C_CRCLen2)        /**/

#define E2Addr_Current_Ladder_Table      (E2Addr_BackUp_Rate12_Price+CLBackUp_Rate12_Price+C_CRCLen2)        /*当前套阶梯表*/
#define E2Addr_BackUp_Ladder_Table       (E2Addr_Current_Ladder_Table+CLCurrent_Ladder_Table+C_CRCLen2)      /*备用套阶梯表*/

#define E2Addr_LossVolage_Vol_UpLim      (E2Addr_BackUp_Ladder_Table+CLBackUp_Ladder_Table+C_CRCLen2)        /*失压事件电压触发上限*/
#define E2Addr_LossVolage_Vol_LowLim     (E2Addr_LossVolage_Vol_UpLim+CLLossVolage_Vol_UpLim+C_CRCLen2)      /*失压事件电压恢复下限*/
#define E2Addr_LossVolage_Curr_LowLim    (E2Addr_LossVolage_Vol_LowLim+CLLossVolage_Vol_LowLim+C_CRCLen2)    /*失压事件电流触发上限*/
#define E2Addr_LossVolage_Delay_T        (E2Addr_LossVolage_Curr_LowLim+CLLossVolage_Curr_LowLim+C_CRCLen2)  /*失压事件判断延时时间*/

#define E2Addr_LowVolage_Vol_UpLim       (E2Addr_LossVolage_Delay_T+CLLossVolage_Delay_T+C_CRCLen2)          /*欠压事件电压触发上限*/
#define E2Addr_LowVolage_Delay_T         (E2Addr_LowVolage_Vol_UpLim+CLLowVolage_Vol_UpLim+C_CRCLen2)        /*欠压事件判断延时时间*/

#define E2Addr_OverVolage_Vol_LowLim     (E2Addr_LowVolage_Delay_T+CLLowVolage_Delay_T+C_CRCLen2)            /*过压事件电压触发下限*/
#define E2Addr_OverVolage_Delay_T        (E2Addr_OverVolage_Vol_LowLim+CLOverVolage_Vol_LowLim+C_CRCLen2)    /*过压时间判断延时时间*/

#define E2Addr_BreakVol_Vol_UpLim        (E2Addr_OverVolage_Delay_T+CLOverVolage_Delay_T+C_CRCLen2)          /*断相事件电压触发上限*/
#define E2Addr_BreakVol_Curr_UpLim       (E2Addr_BreakVol_Vol_UpLim+CLBreakVol_Vol_UpLim+C_CRCLen2)          /*断相事件电流触发上线*/
#define E2Addr_BreakVol_Delay_T          (E2Addr_BreakVol_Curr_UpLim+CLBreakVol_Curr_UpLim+C_CRCLen2)        /*断相事件判定延时时间*/

#define E2Addr_NoBal_Vol_Lim             (E2Addr_BreakVol_Delay_T+CLBreakVol_Delay_T+C_CRCLen2)              /*电压不平衡率限值*/
#define E2Addr_NoBal_Vol_Delay_T         (E2Addr_NoBal_Vol_Lim+CLNoBal_Vol_Lim+C_CRCLen2)                    /*电压不平衡率判定延时时间*/

#define E2Addr_NoBal_Curr_Lim            (E2Addr_NoBal_Vol_Delay_T+CLNoBal_Vol_Delay_T+C_CRCLen2)            /*电流不平衡率限值*/
#define E2Addr_NoBal_Curr_Delay_T        (E2Addr_NoBal_Curr_Lim+CLNoBal_Curr_Lim+C_CRCLen2)                  /*电流不平衡率判定延时时间*/

#define E2Addr_SeriNoBal_Curr_Lim        (E2Addr_NoBal_Curr_Delay_T+CLNoBal_Curr_Delay_T+C_CRCLen2)          /*电流严重不平衡率限值*/
#define E2Addr_SeriNoBal_Curr_Delay_T    (E2Addr_SeriNoBal_Curr_Lim+CLSeriNoBal_Curr_Lim+C_CRCLen2)          /*电流严重不平衡率判定延时时间*/

#define E2Addr_LossCurr_Vol_LowLim       (E2Addr_SeriNoBal_Curr_Delay_T+CLSeriNoBal_Curr_Delay_T+C_CRCLen2)  /*失流事件电压触发下限*/
#define E2Addr_LossCurr_Curr_UpLim       (E2Addr_LossCurr_Vol_LowLim+CLLossCurr_Vol_LowLim+C_CRCLen2)        /*失流事件电流触发上限*/
#define E2Addr_LossCurr_Curr_LowLim      (E2Addr_LossCurr_Curr_UpLim+CLLossCurr_Curr_UpLim+C_CRCLen2)        /*失流事件电流触发下限*/
#define E2Addr_LossCurr_Delay_T          (E2Addr_LossCurr_Curr_LowLim+CLLossCurr_Curr_LowLim+C_CRCLen2)      /*失流事件判断延时时间*/

#define E2Addr_OverCurr_Curr_LowLim      (E2Addr_LossCurr_Delay_T+CLLossCurr_Delay_T+C_CRCLen2)              /*过流事件电流触发下限*/
#define E2Addr_OverCurr_Delay_T          (E2Addr_OverCurr_Curr_LowLim+CLOverCurr_Curr_LowLim+C_CRCLen2)      /*过流事件判断延时时间*/

#define E2Addr_BreakCurr_Vol_LowLim      (E2Addr_OverCurr_Delay_T+CLOverCurr_Delay_T+C_CRCLen2)              /*断流事件电压触发下限*/
#define E2Addr_BreakCurr_Curr_UpLim      (E2Addr_BreakCurr_Vol_LowLim+CLBreakCurr_Vol_LowLim+C_CRCLen2)      /*断流事件电流触发上限*/
#define E2Addr_BreakCurr_Delay_T         (E2Addr_BreakCurr_Curr_UpLim+CLBreakCurr_Curr_UpLim+C_CRCLen2)      /*断流事件判定延时时间*/

#define E2Addr_OverLoad_AcPower_LowLim   (E2Addr_BreakCurr_Delay_T+CLBreakCurr_Delay_T+C_CRCLen2)                /*过载事件有功功率触发下限*/
#define E2Addr_OverLoad_Delay_T          (E2Addr_OverLoad_AcPower_LowLim+CLOverLoad_AcPower_LowLim+C_CRCLen2)    /*过载事件判定延时时间*/

#define E2Addr_PosAcDemandOv_De_LowLim   (E2Addr_OverLoad_Delay_T+CLOverLoad_Delay_T+C_CRCLen2)                  /*正向有功需量超限事件需量触发下限*/
#define E2Addr_PosAcDemandOv_Delay_T     (E2Addr_PosAcDemandOv_De_LowLim+CLPosAcDemandOv_De_LowLim+C_CRCLen2)    /*正向有功需量超限事件判定延时时间*/

#define E2Addr_RevAcDemandOv_De_LowLim   (E2Addr_PosAcDemandOv_Delay_T+CLPosAcDemandOv_Delay_T+C_CRCLen2)        /*反向有功需量超限事件需量触发下限，698新增*/
#define E2Addr_RevAcDemandOv_Delay_T     (E2Addr_RevAcDemandOv_De_LowLim+CLRevAcDemandOv_De_LowLim+C_CRCLen2)    /*反向有功需量超限事件判定延时时间，698新增*/

#define E2Addr_ReDemandOv_De_LowLim      (E2Addr_RevAcDemandOv_Delay_T+CLRevAcDemandOv_Delay_T+C_CRCLen2)        /*无功需量超限事件需量触发下限*/
#define E2Addr_ReDemandOv_Delay_T        (E2Addr_ReDemandOv_De_LowLim+CLReDemandOv_De_LowLim+C_CRCLen2)          /*无功需量超限事件判定延时时间，698新增*/

#define E2Addr_PowerFactor_LowLim        (E2Addr_ReDemandOv_Delay_T+CLReDemandOv_Delay_T+C_CRCLen2)              /*功率因数超下限阀值*/
#define E2Addr_PowerFactor_Delay_T       (E2Addr_PowerFactor_LowLim+CLPowerFactor_LowLim+C_CRCLen2)              /*功率因素超下限判定延时时间*/

#define E2Addr_PowerRev_AcPower_LowLim   (E2Addr_PowerFactor_Delay_T+CLPowerFactor_Delay_T+C_CRCLen2)            /*功率反向事件有功功率触发下限*/
#define E2Addr_PowerRev_Delay_T          (E2Addr_PowerRev_AcPower_LowLim+CLPowerRev_AcPower_LowLim+C_CRCLen2)    /*功率反向事件判定延时时间*/

#define E2Addr_NeutralUnbalanceRate           (E2Addr_PowerRev_Delay_T+CLPowerRev_Delay_T+C_CRCLen2)                          /*零线电流异常不平衡率限值*/
#define E2Addr_NeutralAbnormal_Curr_LowLim    (E2Addr_NeutralUnbalanceRate+CLNeutralUnbalanceRate+C_CRCLen2)                  /*零线电流异常电流触发下限*/
#define E2Addr_NeutralAbnormal_Delay_T        (E2Addr_NeutralAbnormal_Curr_LowLim+CLNeutralAbnormal_Curr_LowLim+C_CRCLen2)    /*零线电流异常判定延迟时间*/

#define E2Addr_ReversedVoltage_Delay_T        (E2Addr_NeutralAbnormal_Delay_T+CLNeutralAbnormal_Delay_T+C_CRCLen2)            /*电压逆相序事件判定延时时间*/
#define E2Addr_ReversedCurrent_Delay_T        (E2Addr_ReversedVoltage_Delay_T+CLReversedVoltage_Delay_T+C_CRCLen2)            /*电流逆相序事件判定延时时间*/
#define E2Addr_PowerOff_Delay_T               (E2Addr_ReversedCurrent_Delay_T+CLReversedVoltage_Delay_T+C_CRCLen2)            /*掉电事件判定延时时间*/
#define E2Addr_Aux_Pow_Down_Delay_T           (E2Addr_PowerOff_Delay_T+CLPowerOff_Delay_T+C_CRCLen2)                          /*辅助电源掉电判定延时时间*/
#define E2Addr_MeterFa_Delay_T                (E2Addr_Aux_Pow_Down_Delay_T+CLAux_Pow_Down_Delay_T+C_CRCLen2)                  /*计量芯片故障判定延时时间*/
#define E2Addr_ClockFa_Delay_T                (E2Addr_MeterFa_Delay_T+CLMeterFa_Delay_T+C_CRCLen2)                            /*时钟故障判定延时时间*/

#define E2Addr_Volage_Check_UpLim             (E2Addr_ClockFa_Delay_T+CLClockFa_Delay_T+C_CRCLen2)                            /*电压考核上限*/
#define E2Addr_Volage_Check_LowLim            (E2Addr_Volage_Check_UpLim+CLVolage_Check_UpLim+C_CRCLen2)                      /*电压考核下限*/
#define E2Addr_Voltage_UpLim                  (E2Addr_Volage_Check_LowLim+CLVolage_Check_LowLim+C_CRCLen2)                    /*电压合格上限*/
#define E2Addr_Voltage_LowLim                 (E2Addr_Voltage_UpLim+CLVoltage_UpLim+C_CRCLen2)                                /*电压合格下限*/

/*********************************************************************************************************************************/
#define E2Addr_Volage_Type               (E2Addr_Voltage_LowLim+CLVoltage_LowLim+C_CRCLen2)                  /*电压类型等设置参数 24*/
#define E2Addr_Start_Up_Current          (E2Addr_Volage_Type+(CLVolage_Type+C_CRCLen2)*8)                    /*电流瞬时量阀值*/
#define E2Addr_Start_Up_Power            (E2Addr_Start_Up_Current+CLStart_Up_Current+C_CRCLen2)              /*功率瞬时量阀值*/
#define E2Addr_Volage_Abnor_Vol          (E2Addr_Start_Up_Power+CLStart_Up_Power+C_CRCLen2)                  /*电压异常判断电压*/
#define E2Addr_Loss_Volage_Curr          (E2Addr_Volage_Abnor_Vol+CLVolage_Abnor_Vol+C_CRCLen2)              /*全失压电流等参数*/
#define E2Addr_Pluse_Most__Lim           (E2Addr_Loss_Volage_Curr+(CLLoss_Volage_Curr+C_CRCLen2)*5)          /*从计量芯片读出的脉冲最大阀值。20141129数据长度由1字节改为2字节*/
#define E2Addr_Curr_Ratio_30A            (E2Addr_Pluse_Most__Lim+CLPluse_Most__Lim+C_CRCLen2)                /*校表30A对应的相应电流规格系数*/
#define E2Addr_Pulse_Constant            (E2Addr_Curr_Ratio_30A+CLCurr_Ratio_30A+C_CRCLen2)                  /*脉冲常数*/
#define E2Addr_SoftIJ_Valid_Time         (E2Addr_Pulse_Constant+CLPulse_Constant+C_CRCLen2)                  /*软IJ有效时间*/
#define E2Addr_Extern_Relay_PulW         (E2Addr_SoftIJ_Valid_Time+CLSoftIJ_Valid_Time+C_CRCLen2)            /*外置继电器脉冲宽度 4*/
#define E2Addr_Key_Update_ID             (E2Addr_Extern_Relay_PulW+CLExtern_Relay_PulW+C_CRCLen2)            /*密钥更新第1个标识码是操作者代码6*/
#define E2Addr_MeterRunStatic            (E2Addr_Key_Update_ID+CLKey_Update_ID+C_CRCLen2)                    /*当前运行在第几套时区表、时段表。时区表在前(低地址)*/

#define E2Addr_F1_TerUpCommParam         (E2Addr_MeterRunStatic+CLMeterRunStatic+C_CRCLen2)                  /*F1终端上行通信参数*/
#define E2Addr_F3_MainStaCommParam       (E2Addr_F1_TerUpCommParam+CLF1_TerUpCommParam+C_CRCLen2)            /*F3主站通信参数,28*/
#define E2Addr_F4_SMSCommParam           (E2Addr_F3_MainStaCommParam+CLF3_MainStaCommParam+C_CRCLen2)        /*F4短信通信参数*/
#define E2Addr_F7_TerminalIPAddr         (E2Addr_F4_SMSCommParam+CLF4_SMSCommParam+C_CRCLen2)                /*F7终端IP地址，64*/
#define E2Addr_F8_ConnectParam           (E2Addr_F7_TerminalIPAddr+CLF7_TerminalIPAddr+C_CRCLen2)            /*F8 连接参数*/
#define E2Addr_F16_MoveAPNPassWord       (E2Addr_F8_ConnectParam+CLF8_ConnectParam+C_CRCLen2)                /*F16 移动APN密码，64*/
#define E2Addr_F89_TerminalAddr          (E2Addr_F16_MoveAPNPassWord+CLF16_MoveAPNPassWord+C_CRCLen2)        /*F89 终端地址 10*/

#define E2Addr_Alarm_Status              (E2Addr_F89_TerminalAddr+CLF89_TerminalAddr+C_CRCLen2)              /*报警模式字 14*/
#define E2Addr_Rst_ReportState_Timer     (E2Addr_Alarm_Status+CLAlarm_Status+C_CRCLen2)                      /*主动上报自动复位时间3*/
#define E2Addr_Relay_Open_CurrTimer      (E2Addr_Rst_ReportState_Timer+CLRst_ReportState_Timer+C_CRCLen2)    /*拉闸控制电流门限保护延时时间 4*/

#define E2Addr_Relay_RemoteOrder         (E2Addr_Relay_Open_CurrTimer+CLRelay_Open_CurrTimer+C_CRCLen2)       /*远程控制命令 5*/
#define E2Addr_Relay_State               (E2Addr_Relay_RemoteOrder+CLRelay_RemoteOrder+C_CRCLen2)             /*继电器状态 5*/
#define E2Addr_Relay_LocalOrder          (E2Addr_Relay_State+CLRelay_State+C_CRCLen2)                         /*本地控制命令 4*/
#define E2Addr_Soft_I_J_Prog_1           (E2Addr_Relay_LocalOrder+CLRelay_LocalOrder+C_CRCLen2)               /*进入厂内模式编程记录 11*/
#define E2Addr_Soft_I_J_Prog_2           (E2Addr_Soft_I_J_Prog_1+CLSoft_I_J_Prog_1+C_CRCLen2)                 /*出厂内模式编程记录 11*/
#define E2Addr_Rec_MeterSequence         (E2Addr_Soft_I_J_Prog_2+CLSoft_I_J_Prog_2+C_CRCLen2)                 /*校表序列号 7*/
#define E2Addr_Rec_MeterPassWord         (E2Addr_Rec_MeterSequence+CLRec_MeterSequence+C_CRCLen2)             /*校表密码 6*/
#define E2Addr_Remote_Local_State        (E2Addr_Rec_MeterPassWord+CLRec_MeterPassWord+C_CRCLen2)             /*远程、本地开户状态 4*/
#define E2Addr_UserCardNo                (E2Addr_Remote_Local_State+CLRemote_Local_State+C_CRCLen2)           /*卡序列号 10*/
#define E2Addr_Cloc_Batt_LowState        (E2Addr_UserCardNo+CL_UserCardNo+C_CRCLen2)                          /*时钟电池欠压状态 3*/
#define E2Addr_ReadMeter_Batt_LowState   (E2Addr_Cloc_Batt_LowState+CLCloc_Batt_LowState+C_CRCLen2)           /*唤醒电池欠压状态 3*/
#define E2Addr_ESAM_FaultState           (E2Addr_ReadMeter_Batt_LowState+CLReadMeter_Batt_LowState+C_CRCLen2) /*ESAM故障状态 3*/
#define E2Addr_Clock_FaultState          (E2Addr_ESAM_FaultState+CLESAM_FaultState+C_CRCLen2)                 /*时钟故障状态 3*/
#define E2Addr_FactoryInMeterNum         (E2Addr_Clock_FaultState+CLClock_FaultState+C_CRCLen2)               /*电表内部序号 4*/

#define E2Addr_ReportNewAddNum           (E2Addr_FactoryInMeterNum+CLFactoryInMeterNum+C_CRCLen2)             /*主动上报次数98，小郭修改*/
#define E2Addr_HaveReportState           (E2Addr_ReportNewAddNum+CLReportNewAddNum+C_CRCLen2)                 /*已主动上报标志*/

#define E2Addr_AppProInformation         (E2Addr_HaveReportState+CLHaveReportState+C_CRCLen2)                 /*协议版本信息*/
#define E2Addr_AppMaxReAPDU              (E2Addr_AppProInformation+CLAppProInformation+C_CRCLen2)             /*最大接收APDU尺寸*/
#define E2Addr_AppMaxSeAPDU              (E2Addr_AppMaxReAPDU+CLAppMaxReAPDU+C_CRCLen2)                       /*最大发送APDU尺寸*/
#define E2Addr_AppMaxHandleAPDU          (E2Addr_AppMaxSeAPDU+CLAppMaxSeAPDU+C_CRCLen2)                       /*最大可处理APDU尺寸*/
#define E2Addr_AppProConsistency         (E2Addr_AppMaxHandleAPDU+CLAppMaxHandleAPDU+C_CRCLen2)               /*协议一致性块*/
#define E2Addr_AppFunConsistency         (E2Addr_AppProConsistency+CLAppProConsistency+C_CRCLen2)             /*功能一致性块*/
#define E2Addr_AppStaticTimeout          (E2Addr_AppFunConsistency+CLAppFunConsistency+C_CRCLen2)             /*静态超时时间*/

#define E2Addr_AppStaticTimeout_termal   (E2Addr_AppStaticTimeout+CLAppStaticTimeout+C_CRCLen2)               /*终端静态超时时间*/
#define E2Addr_ConAutheMechanism         (E2Addr_AppStaticTimeout_termal+CLAppStaticTimeout+C_CRCLen2)        /*连接认证机制*/
#define E2Addr_SafeModePara              (E2Addr_ConAutheMechanism+CLConAutheMechanism+C_CRCLen2)             /*安全模式参数*/

#define E2Addr_I_Free_OADTabLen_T        (E2Addr_SafeModePara+CLSafeModePara+C_CRCLen2)                      /*瞬时冻结OAD序号表实际长度及周期，4*/
#define E2Addr_Min_Free_OADTabLen_T      (E2Addr_I_Free_OADTabLen_T+CLI_Free_OADTabLen_T+C_CRCLen2)          /*分钟冻结OAD序号表实际长度及周期，4*/
#define E2Addr_H_Free_OADTabLen_T        (E2Addr_Min_Free_OADTabLen_T+CLMin_Free_OADTabLen_T+C_CRCLen2)      /*小时冻结OAD序号表实际长度及周期，4*/
#define E2Addr_D_Free_OADTabLen_T        (E2Addr_H_Free_OADTabLen_T+CLH_Free_OADTabLen_T+C_CRCLen2)          /*日冻结OAD序号表实际长度及周期，4*/
#define E2Addr_Sett_Free_OADTabLen_T     (E2Addr_D_Free_OADTabLen_T+CLD_Free_OADTabLen_T+C_CRCLen2)          /*结算日冻结OAD序号表实际长度及周期，4*/
#define E2Addr_M_Free_OADTabLen_T        (E2Addr_Sett_Free_OADTabLen_T+CLSett_Free_OADTabLen_T+C_CRCLen2)    /*月冻结OAD序号表实际长度及周期，4*/
#define E2Addr_Y_Free_OADTabLen_T        (E2Addr_M_Free_OADTabLen_T+CLM_Free_OADTabLen_T+C_CRCLen2)          /*年冻结OAD序号表实际长度及周期，4*/
#define E2Addr_TZ_Free_OADTabLen_T       (E2Addr_Y_Free_OADTabLen_T+CLYSettle_Free_OADTabLen_T+C_CRCLen2)    /*时区表切换冻结OAD序号表实际长度及周期，4*/
#define E2Addr_PT_Free_OADTabLen_T       (E2Addr_TZ_Free_OADTabLen_T+CLTZ_Free_OADTabLen_T+C_CRCLen2)        /*日时段表切换冻结OAD序号表实际长度及周期，4*/
#define E2Addr_R_Free_OADTabLen_T        (E2Addr_PT_Free_OADTabLen_T+CLPT_Free_OADTabLen_T+C_CRCLen2)        /*费率电价切换冻结OAD序号表实际长度及周期，4*/
#define E2Addr_L_Free_OADTabLen_T        (E2Addr_R_Free_OADTabLen_T+CLR_Free_OADTabLen_T+C_CRCLen2)          /*阶梯电价切换冻结OAD序号表实际长度及周期，4*/

#define E2Addr_I_Free_OADTab             (E2Addr_L_Free_OADTabLen_T+CLL_Free_OADTabLen_T+C_CRCLen2)          /*瞬时冻结OAD序号表，C_698Free_OADTabLen*/
#define E2Addr_Min_Free_OADTab           (E2Addr_I_Free_OADTab+C_698Free_OADTabLen+C_CRCLen2)                /*分钟冻结OAD序号表，C_698Free_OADTabLen*/
#define E2Addr_H_Free_OADTab             (E2Addr_Min_Free_OADTab+C_698Free_OADTabLen+C_CRCLen2)              /*小时冻结OAD序号表，C_698Free_OADTabLen*/
#define E2Addr_D_Free_OADTab             (E2Addr_H_Free_OADTab+C_698Free_OADTabLen+C_CRCLen2)                /*日冻结OAD序号表，C_698Free_OADTabLen*/
#define E2Addr_Sett_Free_OADTab          (E2Addr_D_Free_OADTab+C_698Free_OADTabLen+C_CRCLen2)                /*结算日冻结OAD序号表，C_698Free_OADTabLen*/
#define E2Addr_M_Free_OADTab             (E2Addr_Sett_Free_OADTab+C_698Free_OADTabLen+C_CRCLen2)             /*月冻结OAD序号表，C_698Free_OADTabLen,地址0x503-0x282=641,剩余63*/
#define E2Addr_Y_Free_OADTab             (E2Addr_M_Free_OADTab+C_698Free_OADTabLen+C_CRCLen2)                /*年冻结OAD序号表，C_698Free_OADTabLen,实际为阶梯结算冻结*/
#define E2Addr_TZ_Free_OADTab            (E2Addr_Y_Free_OADTab+C_698Free_OADTabLen+C_CRCLen2)                /*时区表切换冻结OAD序号表，C_698Free_OADTabLen*/
#define E2Addr_PT_Free_OADTab            (E2Addr_TZ_Free_OADTab+C_698Free_OADTabLen+C_CRCLen2)               /*日时段表切换冻结OAD序号表，C_698Free_OADTabLen*/
#define E2Addr_R_Free_OADTab             (E2Addr_PT_Free_OADTab+C_698Free_OADTabLen+C_CRCLen2)               /*费率电价切换冻结OAD序号表，C_698Free_OADTabLen*/
#define E2Addr_L_Free_OADTab             (E2Addr_R_Free_OADTab+C_698Free_OADTabLen+C_CRCLen2)                /*阶梯电价切换冻结OAD序号表，C_698Free_OADTabLen*/

#define E2Addr_D_Free_StartTime          (E2Addr_L_Free_OADTab+C_698Free_OADTabLen+C_CRCLen2)                /*日冻结起始日期时间，5*/
#define E2Addr_M_Free_StartTime          (E2Addr_D_Free_StartTime+CLD_Free_StartTime+C_CRCLen2)              /*月冻结起始日期时间，5*/
#define E2Addr_Y_Free_StartTime          (E2Addr_M_Free_StartTime+CLM_Free_StartTime+C_CRCLen2)              /*年冻结起始日期时间，5*/

#define	E2Addr_LossVolage_Report_Mode           (E2Addr_Y_Free_StartTime+CLY_Free_StartTime+C_CRCLen2)            /*失压上报模式字*/
#define	E2Addr_LowVolage_Report_Mode            (E2Addr_LossVolage_Report_Mode+CLReport_Mode+C_CRCLen2)           /*欠压上报模式字*/
#define	E2Addr_OverVolage_Report_Mode           (E2Addr_LowVolage_Report_Mode+CLReport_Mode+C_CRCLen2)            /*过压上报模式字*/
#define	E2Addr_BreakVol_Report_Mode             (E2Addr_OverVolage_Report_Mode+CLReport_Mode+C_CRCLen2)           /*断相上报模式字*/
#define	E2Addr_LossCurr_Report_Mode             (E2Addr_BreakVol_Report_Mode+CLReport_Mode+C_CRCLen2)             /*失流上报模式字*/
#define	E2Addr_OverCurr_Report_Mode             (E2Addr_LossCurr_Report_Mode+CLReport_Mode+C_CRCLen2)             /*过流上报模式字*/
#define	E2Addr_BreakCurr_Report_Mode            (E2Addr_OverCurr_Report_Mode+CLReport_Mode+C_CRCLen2)             /*断流上报模式字*/
#define	E2Addr_PowerRev_Report_Mode             (E2Addr_BreakCurr_Report_Mode+CLReport_Mode+C_CRCLen2)            /*功率反向上报模式字*/
#define	E2Addr_OverLoad_Report_Mode             (E2Addr_PowerRev_Report_Mode+CLReport_Mode+C_CRCLen2)             /*过载上报模式字*/
#define	E2Addr_PosAcDemandOv_Report_Mode        (E2Addr_OverLoad_Report_Mode+CLReport_Mode+C_CRCLen2)             /*正向有功需量超限事件上报模式字*/
#define	E2Addr_RevAcDemandOv_Report_Mode        (E2Addr_PosAcDemandOv_Report_Mode+CLReport_Mode+C_CRCLen2)        /*反向有功需量超限事件上报模式字*/
#define	E2Addr_ReDemandOv_Report_Mode           (E2Addr_RevAcDemandOv_Report_Mode+CLReport_Mode+C_CRCLen2)        /*无功需量超限事件上报模式字*/
#define	E2Addr_PowerFactor_Report_Mode          (E2Addr_ReDemandOv_Report_Mode+CLReport_Mode+C_CRCLen2)           /*功率因数超下限事件上报模式字*/
#define	E2Addr_AllLossVolage_Report_Mode        (E2Addr_PowerFactor_Report_Mode+CLReport_Mode+C_CRCLen2)          /*全失压上报模式字*/
#define	E2Addr_AuxPowDown_Report_Mode           (E2Addr_AllLossVolage_Report_Mode+CLReport_Mode+C_CRCLen2)        /*辅助电源失电上报模式字*/
#define	E2Addr_ReversedVoltage_Report_Mode      (E2Addr_AuxPowDown_Report_Mode+CLReport_Mode+C_CRCLen2)           /*电压逆相序上报模式字*/
#define	E2Addr_ReversedCurrent_Report_Mode      (E2Addr_ReversedVoltage_Report_Mode+CLReport_Mode+C_CRCLen2)      /*电流逆相序上报模式字*/
#define	E2Addr_PowerOff_Report_Mode             (E2Addr_ReversedCurrent_Report_Mode+CLReport_Mode+C_CRCLen2)      /*掉电上报模式字*/
#define	E2Addr_Program_Report_Mode              (E2Addr_PowerOff_Report_Mode+CLReport_Mode+C_CRCLen2)             /*编程上报模式字*/
#define	E2Addr_TolClear_Report_Mode             (E2Addr_Program_Report_Mode+CLReport_Mode+C_CRCLen2)              /*电表清零上报模式字*/
#define	E2Addr_DemandClear_Report_Mode          (E2Addr_TolClear_Report_Mode+CLReport_Mode+C_CRCLen2)             /*需量清零上报模式字*/
#define	E2Addr_EventClear_Report_Mode           (E2Addr_DemandClear_Report_Mode+CLReport_Mode+C_CRCLen2)          /*事件清零上报模式字*/
#define	E2Addr_AdjTime_Report_Mode              (E2Addr_EventClear_Report_Mode+CLReport_Mode+C_CRCLen2)           /*校时上报模式字*/
#define	E2Addr_BroadcastTime_Report_Mode        (E2Addr_AdjTime_Report_Mode+CLReport_Mode+C_CRCLen2)              /*广播校时上报模式字*/
#define	E2Addr_ProgPT_Report_Mode               (E2Addr_BroadcastTime_Report_Mode+CLReport_Mode+C_CRCLen2)        /*时段表编程上报模式字*/
#define	E2Addr_ProgPZ_Report_Mode               (E2Addr_ProgPT_Report_Mode+CLReport_Mode+C_CRCLen2)               /*时区表编程上报模式字*/
#define	E2Addr_ProgWRe_Report_Mode              (E2Addr_ProgPZ_Report_Mode+CLReport_Mode+C_CRCLen2)               /*周休日编程上报模式字*/
#define	E2Addr_ProgSettD_Report_Mode            (E2Addr_ProgWRe_Report_Mode+CLReport_Mode+C_CRCLen2)              /*结算日编程上报模式字*/
#define	E2Addr_OpenW_Report_Mode                (E2Addr_ProgSettD_Report_Mode+CLReport_Mode+C_CRCLen2)            /*开表盖上报模式字*/
#define	E2Addr_OpenCW_Report_Mode               (E2Addr_OpenW_Report_Mode+CLReport_Mode+C_CRCLen2)                /*开端钮盖上报模式字*/
#define	E2Addr_NoBalVol_Report_Mode             (E2Addr_OpenCW_Report_Mode+CLReport_Mode+C_CRCLen2)               /*电压不平衡上报模式字*/
#define	E2Addr_NoBalCurr_Report_Mode            (E2Addr_NoBalVol_Report_Mode+CLReport_Mode+C_CRCLen2)             /*电流不平衡上报模式字*/
#define	E2Addr_RelayOpen_Report_Mode            (E2Addr_NoBalCurr_Report_Mode+CLReport_Mode+C_CRCLen2)            /*跳闸上报模式字*/
#define	E2Addr_RelayClose_Report_Mode           (E2Addr_RelayOpen_Report_Mode+CLReport_Mode+C_CRCLen2)            /*合闸上报模式字*/
#define	E2Addr_ProgHol_Report_Mode              (E2Addr_RelayClose_Report_Mode+CLReport_Mode+C_CRCLen2)           /*节假日编程上报模式字*/
#define	E2Addr_ProgAcC_Report_Mode              (E2Addr_ProgHol_Report_Mode+CLReport_Mode+C_CRCLen2)              /*有功组合方式编程上报模式字*/
#define	E2Addr_ProgReC_Report_Mode              (E2Addr_ProgAcC_Report_Mode+CLReport_Mode+C_CRCLen2)              /*无功组合方式编程上报模式字*/
#define	E2Addr_ProgTPara_Report_Mode            (E2Addr_ProgReC_Report_Mode+CLReport_Mode+C_CRCLen2)              /*费率参数表编程上报模式字*/
#define	E2Addr_ProgLad_Report_Mode              (E2Addr_ProgTPara_Report_Mode+CLReport_Mode+C_CRCLen2)            /*阶梯表编程上报模式字*/
#define	E2Addr_Key_Update_Report_Mode           (E2Addr_ProgLad_Report_Mode+CLReport_Mode+C_CRCLen2)              /*密钥更新上报模式字*/
#define	E2Addr_AbnorC_Report_Mode               (E2Addr_Key_Update_Report_Mode+CLReport_Mode+C_CRCLen2)           /*异常插卡上报模式字*/
#define	E2Addr_BuyCurr_Report_Mode              (E2Addr_AbnorC_Report_Mode+CLReport_Mode+C_CRCLen2)               /*购电上报模式字*/
#define	E2Addr_ReturnMoney_Report_Mode          (E2Addr_BuyCurr_Report_Mode+CLReport_Mode+C_CRCLen2)              /*退费上报模式字*/
#define	E2Addr_ConMEndEn_Report_Mode            (E2Addr_ReturnMoney_Report_Mode+CLReport_Mode+C_CRCLen2)          /*恒定磁场干扰上报模式字*/
#define	E2Addr_RelayFaEndEn_Report_Mode         (E2Addr_ConMEndEn_Report_Mode+CLReport_Mode+C_CRCLen2)            /*负荷开关误动作上报模式字*/
#define	E2Addr_PowerFa_EndT_Report_Mode         (E2Addr_RelayFaEndEn_Report_Mode+CLReport_Mode+C_CRCLen2)         /*电源异常上报模式字*/
#define	E2Addr_SeriNoBalCurr_Report_Mode        (E2Addr_PowerFa_EndT_Report_Mode+CLReport_Mode+C_CRCLen2)         /*电流严重不平衡上报模式字*/
#define	E2Addr_ClockFault_Report_Mode           (E2Addr_SeriNoBalCurr_Report_Mode+CLReport_Mode+C_CRCLen2)        /*时钟故障上报模式字*/
#define	E2Addr_MeteringChipFault_Report_Mode    (E2Addr_ClockFault_Report_Mode+CLReport_Mode+C_CRCLen2)           /*计量芯片故障上报模式字*/

#define	E2Addr_LossVolage_Report_Type           (E2Addr_MeteringChipFault_Report_Mode+CLReport_Mode+C_CRCLen2)    /*失压上报方式*/
#define	E2Addr_LowVolage_Report_Type            (E2Addr_LossVolage_Report_Type+CLReport_Type+C_CRCLen2)           /*欠压上报方式*/
#define	E2Addr_OverVolage_Report_Type           (E2Addr_LowVolage_Report_Type+CLReport_Type+C_CRCLen2)            /*过压上报方式*/
#define	E2Addr_BreakVol_Report_Type             (E2Addr_OverVolage_Report_Type+CLReport_Type+C_CRCLen2)           /*断相上报方式*/
#define	E2Addr_LossCurr_Report_Type             (E2Addr_BreakVol_Report_Type+CLReport_Type+C_CRCLen2)             /*失流上报方式*/
#define	E2Addr_OverCurr_Report_Type             (E2Addr_LossCurr_Report_Type+CLReport_Type+C_CRCLen2)             /*过流上报方式*/
#define	E2Addr_BreakCurr_Report_Type            (E2Addr_OverCurr_Report_Type+CLReport_Type+C_CRCLen2)             /*断流上报方式*/
#define	E2Addr_PowerRev_Report_Type             (E2Addr_BreakCurr_Report_Type+CLReport_Type+C_CRCLen2)            /*功率反向上报方式*/
#define	E2Addr_OverLoad_Report_Type             (E2Addr_PowerRev_Report_Type+CLReport_Type+C_CRCLen2)             /*过载上报方式*/
#define	E2Addr_PosAcDemandOv_Report_Type        (E2Addr_OverLoad_Report_Type+CLReport_Type+C_CRCLen2)             /*正向有功需量超限事件上报方式*/
#define	E2Addr_RevAcDemandOv_Report_Type        (E2Addr_PosAcDemandOv_Report_Type+CLReport_Type+C_CRCLen2)        /*反向有功需量超限事件上报方式*/
#define	E2Addr_ReDemandOv_Report_Type           (E2Addr_RevAcDemandOv_Report_Type+CLReport_Type+C_CRCLen2)        /*无功需量超限事件上报方式*/
#define	E2Addr_PowerFactor_Report_Type          (E2Addr_ReDemandOv_Report_Type+CLReport_Type+C_CRCLen2)           /*功率因数超下限事件上报方式*/
#define	E2Addr_AllLossVolage_Report_Type        (E2Addr_PowerFactor_Report_Type+CLReport_Type+C_CRCLen2)          /*全失压上报方式*/
#define	E2Addr_AuxPowDown_Report_Type           (E2Addr_AllLossVolage_Report_Type+CLReport_Type+C_CRCLen2)        /*辅助电源失电上报方式*/
#define	E2Addr_ReversedVoltage_Report_Type      (E2Addr_AuxPowDown_Report_Type+CLReport_Type+C_CRCLen2)           /*电压逆相序上报方式*/
#define	E2Addr_ReversedCurrent_Report_Type      (E2Addr_ReversedVoltage_Report_Type+CLReport_Type+C_CRCLen2)      /*电流逆相序上报方式*/
#define	E2Addr_PowerOff_Report_Type             (E2Addr_ReversedCurrent_Report_Type+CLReport_Type+C_CRCLen2)      /*掉电上报方式*/
#define	E2Addr_Program_Report_Type              (E2Addr_PowerOff_Report_Type+CLReport_Type+C_CRCLen2)             /*编程上报方式*/
#define	E2Addr_TolClear_Report_Type             (E2Addr_Program_Report_Type+CLReport_Type+C_CRCLen2)              /*电表清零上报方式*/
#define	E2Addr_DemandClear_Report_Type          (E2Addr_TolClear_Report_Type+CLReport_Type+C_CRCLen2)             /*需量清零上报方式*/
#define	E2Addr_EventClear_Report_Type           (E2Addr_DemandClear_Report_Type+CLReport_Type+C_CRCLen2)          /*事件清零上报方式*/
#define	E2Addr_AdjTime_Report_Type              (E2Addr_EventClear_Report_Type+CLReport_Type+C_CRCLen2)           /*校时上报方式*/
#define	E2Addr_BroadcastTime_Report_Type        (E2Addr_AdjTime_Report_Type+CLReport_Type+C_CRCLen2)              /*广播校时上报方式*/
#define	E2Addr_ProgPT_Report_Type               (E2Addr_BroadcastTime_Report_Type+CLReport_Type+C_CRCLen2)        /*时段表编程上报方式*/
#define	E2Addr_ProgPZ_Report_Type               (E2Addr_ProgPT_Report_Type+CLReport_Type+C_CRCLen2)               /*时区表编程上报方式*/
#define	E2Addr_ProgWRe_Report_Type              (E2Addr_ProgPZ_Report_Type+CLReport_Type+C_CRCLen2)               /*周休日编程上报方式*/
#define	E2Addr_ProgSettD_Report_Type            (E2Addr_ProgWRe_Report_Type+CLReport_Type+C_CRCLen2)              /*结算日编程上报方式*/
#define	E2Addr_OpenW_Report_Type                (E2Addr_ProgSettD_Report_Type+CLReport_Type+C_CRCLen2)            /*开表盖上报方式*/
#define	E2Addr_OpenCW_Report_Type               (E2Addr_OpenW_Report_Type+CLReport_Type+C_CRCLen2)                /*开端钮盖上报方式*/
#define	E2Addr_NoBalVol_Report_Type             (E2Addr_OpenCW_Report_Type+CLReport_Type+C_CRCLen2)               /*电压不平衡上报方式*/
#define	E2Addr_NoBalCurr_Report_Type            (E2Addr_NoBalVol_Report_Type+CLReport_Type+C_CRCLen2)             /*电流不平衡上报方式*/
#define	E2Addr_RelayOpen_Report_Type            (E2Addr_NoBalCurr_Report_Type+CLReport_Type+C_CRCLen2)            /*跳闸上报方式*/
#define	E2Addr_RelayClose_Report_Type           (E2Addr_RelayOpen_Report_Type+CLReport_Type+C_CRCLen2)            /*合闸上报方式*/
#define	E2Addr_ProgHol_Report_Type              (E2Addr_RelayClose_Report_Type+CLReport_Type+C_CRCLen2)           /*节假日编程上报方式*/
#define	E2Addr_ProgAcC_Report_Type              (E2Addr_ProgHol_Report_Type+CLReport_Type+C_CRCLen2)              /*有功组合方式编程上报方式*/
#define	E2Addr_ProgReC_Report_Type              (E2Addr_ProgAcC_Report_Type+CLReport_Type+C_CRCLen2)              /*无功组合方式编程上报方式*/
#define	E2Addr_ProgTPara_Report_Type            (E2Addr_ProgReC_Report_Type+CLReport_Type+C_CRCLen2)              /*费率参数表编程上报方式*/
#define	E2Addr_ProgLad_Report_Type              (E2Addr_ProgTPara_Report_Type+CLReport_Type+C_CRCLen2)            /*阶梯表编程上报方式*/
#define	E2Addr_Key_Update_Report_Type           (E2Addr_ProgLad_Report_Type+CLReport_Type+C_CRCLen2)              /*密钥更新上报方式*/
#define	E2Addr_AbnorC_Report_Type               (E2Addr_Key_Update_Report_Type+CLReport_Type+C_CRCLen2)           /*异常插卡上报方式*/
#define	E2Addr_BuyCurr_Report_Type              (E2Addr_AbnorC_Report_Type+CLReport_Type+C_CRCLen2)               /*购电上报方式*/
#define	E2Addr_ReturnMoney_Report_Type          (E2Addr_BuyCurr_Report_Type+CLReport_Type+C_CRCLen2)              /*退费上报方式*/
#define	E2Addr_ConMEndEn_Report_Type            (E2Addr_ReturnMoney_Report_Type+CLReport_Type+C_CRCLen2)          /*恒定磁场干扰上报方式*/
#define	E2Addr_RelayFaEndEn_Report_Type         (E2Addr_ConMEndEn_Report_Type+CLReport_Type+C_CRCLen2)            /*负荷开关误动作上报方式*/
#define	E2Addr_PowerFa_EndT_Report_Type         (E2Addr_RelayFaEndEn_Report_Type+CLReport_Type+C_CRCLen2)         /*电源异常上报方式*/
#define	E2Addr_SeriNoBalCurr_Report_Type        (E2Addr_PowerFa_EndT_Report_Type+CLReport_Type+C_CRCLen2)         /*电流严重不平衡上报方式*/
#define	E2Addr_ClockFault_Report_Type           (E2Addr_SeriNoBalCurr_Report_Type+CLReport_Type+C_CRCLen2)        /*时钟故障上报方式*/
#define	E2Addr_MeteringChipFault_Report_Type    (E2Addr_ClockFault_Report_Type+CLReport_Type+C_CRCLen2)           /*计量芯片故障上报方式*/
#define	E2Addr_Drive_Report_Type                (E2Addr_MeteringChipFault_Report_Type+CLReport_Type+C_CRCLen2)    /*2015跟随上报方式*/
#define	E2Addr_ABnor_ZeroCurrent_Report_Mode    (E2Addr_Drive_Report_Type+CLReport_Type+C_CRCLen2)                /*2015跟随上报方式*/
#define	E2Addr_ABnor_ZeroCurrent_Report_Type    (E2Addr_ABnor_ZeroCurrent_Report_Mode+CLReport_Type+C_CRCLen2)    /*零线电流异常上报模式字*/
#if 0
#define	E2Addr_BroadTimeAbnormal_Report_Mode    (E2Addr_ABnor_ZeroCurrent_Report_Type+CLReport_Type+C_CRCLen2)    /*广播校时异常上报模式字*/
#define	E2Addr_BroadTimeAbnormal_Report_Type    (E2Addr_BroadTimeAbnormal_Report_Mode+CLReport_Type+C_CRCLen2)    /*广播校时异常上报方式*/
#endif
#define	E2Addr_ADD_End                          (E2Addr_ABnor_ZeroCurrent_Report_Type+CLReport_Type+C_CRCLen2)

#define E2Addr_All_Loss_Vol_OADTab              (E2Addr_ABnor_ZeroCurrent_Report_Type+CLReport_Type+C_CRCLen2)    /*全失压关联列表*/
#define E2Addr_Aux_Pow_Down_OADTab              (E2Addr_All_Loss_Vol_OADTab+C_698Event_OADTabLen+C_CRCLen2)       /*辅助电源掉电*/
#define E2Addr_Pow_Down_OADTab                  (E2Addr_Aux_Pow_Down_OADTab+C_698Event_OADTabLen+C_CRCLen2)       /*掉电*/
#define E2Addr_Pos_Ac_De_Over_OADTab            (E2Addr_Pow_Down_OADTab+C_698Event_OADTabLen+C_CRCLen2)           /*正向有功需量超限事件*/
#define E2Addr_Rev_Ac_De_Over_OADTab            (E2Addr_Pos_Ac_De_Over_OADTab+C_698Event_OADTabLen+C_CRCLen2)     /*反向有功需量超限事件*/
#define E2Addr_Qua_Re_De_Over_OADTab            (E2Addr_Rev_Ac_De_Over_OADTab+C_698Event_OADTabLen+C_CRCLen2)     /*无功有功需量超限事件*/
#define E2Addr_Loss_Vol_OADTab                  (E2Addr_Qua_Re_De_Over_OADTab+C_698Event_OADTabLen+C_CRCLen2)     /*失压关联列表*/
#define E2Addr_Low_Vol_OADTab                   (E2Addr_Loss_Vol_OADTab+C_698Event_OADTabLen+C_CRCLen2)           /*欠压关联列表*/
#define E2Addr_Over_Vol_OADTab                  (E2Addr_Low_Vol_OADTab+C_698Event_OADTabLen+C_CRCLen2)            /*过压关联列表*/
#define E2Addr_Break_Vol_OADTab                 (E2Addr_Over_Vol_OADTab+C_698Event_OADTabLen+C_CRCLen2)           /*断相关联列表*/
#define E2Addr_RevPS_Vol_OADTab                 (E2Addr_Break_Vol_OADTab+C_698Event_OADTabLen+C_CRCLen2)          /*电压逆相序关联列表*/
#define E2Addr_RevPS_Curr_OADTab                (E2Addr_RevPS_Vol_OADTab+C_698Event_OADTabLen+C_CRCLen2)          /*电流逆相序关联列表*/
#define E2Addr_NoBal_Vol_OADTab                 (E2Addr_RevPS_Curr_OADTab+C_698Event_OADTabLen+C_CRCLen2)         /*电压不平衡关联列表*/
#define E2Addr_NoBal_Curr_OADTab                (E2Addr_NoBal_Vol_OADTab+C_698Event_OADTabLen+C_CRCLen2)          /*电流不平衡关联列表*/
#define E2Addr_SevNoBal_Curr_OADTab             (E2Addr_NoBal_Curr_OADTab+C_698Event_OADTabLen+C_CRCLen2)         /*电流严重不平衡关联列表*/
#define E2Addr_Loss_Curr_OADTab                 (E2Addr_SevNoBal_Curr_OADTab+C_698Event_OADTabLen+C_CRCLen2)      /*失流关联列表*/
#define E2Addr_Over_Curr_OADTab                 (E2Addr_Loss_Curr_OADTab+C_698Event_OADTabLen+C_CRCLen2)          /*过流关联列表*/
#define E2Addr_Break_Curr_OADTab                (E2Addr_Over_Curr_OADTab+C_698Event_OADTabLen+C_CRCLen2)          /*断流关联列表*/
#define E2Addr_Power_Rev_OADTab                 (E2Addr_Break_Curr_OADTab+C_698Event_OADTabLen+C_CRCLen2)         /*功率反向关联列表*/
#define E2Addr_Over_Lo_OADTab                   (E2Addr_Power_Rev_OADTab+C_698Event_OADTabLen+C_CRCLen2)          /*过载关联列表*/
#define E2Addr_Tol_Clear_OADTab                 (E2Addr_Over_Lo_OADTab+C_698Event_OADTabLen+C_CRCLen2)            /*总清关联列表*/
#define E2Addr_De_Clear_OADTab                  (E2Addr_Tol_Clear_OADTab+C_698Event_OADTabLen+C_CRCLen2)          /*需清关联列表*/
#define E2Addr_Even_Clear_OADTab                (E2Addr_De_Clear_OADTab+C_698Event_OADTabLen+C_CRCLen2)           /*事件清零关联列表*/
#define E2Addr_Program_OADTab                   (E2Addr_Even_Clear_OADTab+C_698Event_OADTabLen+C_CRCLen2)         /*编程记录关联列表*/
#define E2Addr_AbnorC_OADTab                    (E2Addr_Program_OADTab+C_698Event_OADTabLen+C_CRCLen2)            /*异常插卡记录关联列表*/
#define E2Addr_OpenW_OADTab                     (E2Addr_AbnorC_OADTab+C_698Event_OADTabLen+C_CRCLen2)             /*开表盖记录关联列表*/
#define E2Addr_OpenCW_OADTab                    (E2Addr_OpenW_OADTab+C_698Event_OADTabLen+C_CRCLen2)              /*开端钮盖记录关联列表*/
#define E2Addr_BuyCurr_OADTab                   (E2Addr_OpenCW_OADTab+C_698Event_OADTabLen+C_CRCLen2)             /*购电记录关联列表*/
#define E2Addr_Return_M_OADTab                  (E2Addr_BuyCurr_OADTab+C_698Event_OADTabLen+C_CRCLen2)            /*退费记录关联列表*/
#define E2Addr_ConM_OADTab                      (E2Addr_Return_M_OADTab+C_698Event_OADTabLen+C_CRCLen2)           /*恒定磁场干扰关联列表*/
#define E2Addr_RelayFa_OADTab                   (E2Addr_ConM_OADTab+C_698Event_OADTabLen+C_CRCLen2)               /*负荷开关误动作关联列表*/
#define E2Addr_PowerFa_OADTab                   (E2Addr_RelayFa_OADTab+C_698Event_OADTabLen+C_CRCLen2)            /*电源异常关联列表*/
#define E2Addr_RelayOpen_OADTab                 (E2Addr_PowerFa_OADTab+C_698Event_OADTabLen+C_CRCLen2)            /*跳闸记录关联列表*/
#define E2Addr_RelayClose_OADTab                (E2Addr_RelayOpen_OADTab+C_698Event_OADTabLen+C_CRCLen2)          /*和闸记录关联列表*/
#define E2Addr_PFactorT_Over_OADTab             (E2Addr_RelayClose_OADTab+C_698Event_OADTabLen+C_CRCLen2)         /*总功率超限关联列表*/
#define E2Addr_AdjTime_OADTab                   (E2Addr_PFactorT_Over_OADTab+C_698Event_OADTabLen+C_CRCLen2)      /*校时关联列表*/
#define E2Addr_BroadcastTime_OADTab             (E2Addr_AdjTime_OADTab+C_698Event_OADTabLen+C_CRCLen2)            /*广播校时关联列表*/
#define E2Addr_ProgPT_OADTab                    (E2Addr_BroadcastTime_OADTab+C_698Event_OADTabLen+C_CRCLen2)      /*时段表编程关联列表*/
#define E2Addr_ProgTZ_OADTab                    (E2Addr_ProgPT_OADTab+C_698Event_OADTabLen+C_CRCLen2)             /*时区表编程关联列表*/
#define E2Addr_ProgWRe_OADTab                   (E2Addr_ProgTZ_OADTab+C_698Event_OADTabLen+C_CRCLen2)             /*周休日编程关联列表*/
#define E2Addr_ProgHol_OADTab                   (E2Addr_ProgWRe_OADTab+C_698Event_OADTabLen+C_CRCLen2)            /*节假日编程关联列表*/
#define E2Addr_ProgAcC_OADTab                   (E2Addr_ProgHol_OADTab+C_698Event_OADTabLen+C_CRCLen2)            /*有功组合方式编程关联列表*/
#define E2Addr_ProgReC_OADTab                   (E2Addr_ProgAcC_OADTab+C_698Event_OADTabLen+C_CRCLen2)            /*无功组合方式编程关联列表*/
#define E2Addr_ProgSettD_OADTab                 (E2Addr_ProgReC_OADTab+C_698Event_OADTabLen+C_CRCLen2)            /*结算日编程关联列表*/
#define E2Addr_ProgTPara_OADTab                 (E2Addr_ProgSettD_OADTab+C_698Event_OADTabLen+C_CRCLen2)          /*费率表编程关联列表*/
#define E2Addr_ProgLad_OADTab                   (E2Addr_ProgTPara_OADTab+C_698Event_OADTabLen+C_CRCLen2)          /*阶梯表编程关联列表*/
#define E2Addr_ProgKD_OADTab                    (E2Addr_ProgLad_OADTab+C_698Event_OADTabLen+C_CRCLen2)            /*密钥更新列表*/
#define E2Addr_MeterFa_OADTab                   (E2Addr_ProgKD_OADTab+C_698Event_OADTabLen+C_CRCLen2)             /*计量芯片故障列表*/
#define E2Addr_ClockFa_OADTab                   (E2Addr_MeterFa_OADTab+C_698Event_OADTabLen+C_CRCLen2)            /*时钟故障列表*/
#define E2Addr_NeutralCurrentAbnormal_OADTab    (E2Addr_ClockFa_OADTab+C_698Event_OADTabLen+C_CRCLen2)            /*零线电流异常*/

/*顺序不要随意调整，与程序和数据标识关联，InF_Write_Data()、【CAll_Loss_Vol_OADTabLen(0x04FE1201) - CClockFa_OADTabLen(0x04FE1230)*/
#define E2Addr_All_Loss_Vol_OADTabLen           (E2Addr_NeutralCurrentAbnormal_OADTab+C_698Event_OADTabLen+C_CRCLen2)     /*全失压关联列表长度，1*/
#define E2Addr_Aux_Pow_Down_OADTabLen           (E2Addr_All_Loss_Vol_OADTabLen+CLAll_Loss_Vol_OADTabLen+C_CRCLen2)        /*辅助电源掉电关联列表长度，1*/
#define E2Addr_Pow_Down_OADTabLen               (E2Addr_Aux_Pow_Down_OADTabLen+CLAux_Pow_Down_OADTabLen+C_CRCLen2)        /*掉电关联列表长度，1*/
#define E2Addr_Pos_Ac_De_Over_OADTabLen         (E2Addr_Pow_Down_OADTabLen+CLPow_Down_OADTabLen+C_CRCLen2)                /*正向有功需量超限事件，1*/
#define E2Addr_Rev_Ac_De_Over_OADTabLen         (E2Addr_Pos_Ac_De_Over_OADTabLen+CLPos_Ac_De_Over_OADTabLen+C_CRCLen2)    /*反向有功需量超限事件，1*/
#define E2Addr_Qua_Re_De_Over_OADTabLen         (E2Addr_Rev_Ac_De_Over_OADTabLen+CLRev_Ac_De_Over_OADTabLen+C_CRCLen2)    /*无功需量超限事件，1*/
#define E2Addr_Loss_Vol_OADTabLen               (E2Addr_Qua_Re_De_Over_OADTabLen+CLQua_Re_De_Over_OADTabLen+C_CRCLen2)    /*失压，1*/
#define E2Addr_Low_Vol_OADTabLen                (E2Addr_Loss_Vol_OADTabLen+CLLoss_Vol_OADTabLen+C_CRCLen2)                /*欠压，1*/
#define E2Addr_Over_Vol_OADTabLen               (E2Addr_Low_Vol_OADTabLen+CLLow_Vol_OADTabLen+C_CRCLen2)                  /*过压，1*/
#define E2Addr_Break_Vol_OADTabLen              (E2Addr_Over_Vol_OADTabLen+CLOver_Vol_OADTabLen+C_CRCLen2)                /*断相，1*/
#define E2Addr_RevPS_Vol_OADTabLen              (E2Addr_Break_Vol_OADTabLen+CLBreak_Vol_OADTabLen+C_CRCLen2)              /*电压逆相序，1*/
#define E2Addr_RevPS_Curr_OADTabLen             (E2Addr_RevPS_Vol_OADTabLen+CLRevPS_Vol_OADTabLen+C_CRCLen2)              /*电流逆相序，1*/
#define E2Addr_NoBal_Vol_OADTabLen              (E2Addr_RevPS_Curr_OADTabLen+CLRevPS_Curr_OADTabLen+C_CRCLen2)            /*电压不平衡，1*/
#define E2Addr_NoBal_Curr_OADTabLen             (E2Addr_NoBal_Vol_OADTabLen+CLNoBal_Vol_OADTabLen+C_CRCLen2)              /*电流不平衡，1*/
#define E2Addr_SevNoBal_Curr_OADTabLen          (E2Addr_NoBal_Curr_OADTabLen+CLNoBal_Curr_OADTabLen+C_CRCLen2)            /*电流严重不平衡，1*/
#define E2Addr_Loss_Curr_OADTabLen              (E2Addr_SevNoBal_Curr_OADTabLen+CLSevNoBal_Curr_OADTabLen+C_CRCLen2)      /*失流，1*/
#define E2Addr_Over_Curr_OADTabLen              (E2Addr_Loss_Curr_OADTabLen+CLLoss_Curr_OADTabLen+C_CRCLen2)              /*过流，1*/
#define E2Addr_Break_Curr_OADTabLen             (E2Addr_Over_Curr_OADTabLen+CLOver_Curr_OADTabLen+C_CRCLen2)              /*断流，1*/
#define E2Addr_Power_Rev_OADTabLen              (E2Addr_Break_Curr_OADTabLen+CLBreak_Curr_OADTabLen+C_CRCLen2)            /*功率反向，1*/
#define E2Addr_Over_Lo_OADTabLen                (E2Addr_Power_Rev_OADTabLen+CLPower_Rev_OADTabLen+C_CRCLen2)              /*过载反向，1*/
#define E2Addr_Tol_Clear_OADTabLen              (E2Addr_Over_Lo_OADTabLen+CLOver_Lo_OADTabLen+C_CRCLen2)                  /*总清，1*/
#define E2Addr_De_Clear_OADTabLen               (E2Addr_Tol_Clear_OADTabLen+CLTol_Clear_OADTabLen+C_CRCLen2)              /*需清，1*/
#define E2Addr_Even_Clear_OADTabLen             (E2Addr_De_Clear_OADTabLen+CLDe_Clear_OADTabLen+C_CRCLen2)                /*事件清零，1*/
#define E2Addr_Program_OADTabLen                (E2Addr_Even_Clear_OADTabLen+CLEven_Clear_OADTabLen+C_CRCLen2)            /*编程记录，1*/
#define E2Addr_AbnorC_OADTabLen                 (E2Addr_Program_OADTabLen+CLProgram_OADTabLen+C_CRCLen2)                  /*异常插卡记录，1*/
#define E2Addr_OpenW_OADTabLen                  (E2Addr_AbnorC_OADTabLen+CLAbnorC_OADTabLen+C_CRCLen2)                    /*开表盖记录，1*/
#define E2Addr_OpenCW_OADTabLen                 (E2Addr_OpenW_OADTabLen+CLOpenW_OADTabLen+C_CRCLen2)                      /*开表盖记录，1*/
#define E2Addr_BuyCurr_OADTabLen                (E2Addr_OpenCW_OADTabLen+CLOpenCW_OADTabLen+C_CRCLen2)                    /*购电记录，1*/
#define E2Addr_Return_M_OADTabLen               (E2Addr_BuyCurr_OADTabLen+CLBuyCurr_OADTabLen+C_CRCLen2)                  /*退费记录，1*/
#define E2Addr_ConM_OADTabLen                   (E2Addr_Return_M_OADTabLen+CLReturn_M_OADTabLen+C_CRCLen2)                /*恒定磁场干扰记录，1*/
#define E2Addr_RelayFa_OADTabLen                (E2Addr_ConM_OADTabLen+CLConM_OADTabLen+C_CRCLen2)                        /*负荷开关误动作记录，1*/
#define E2Addr_PowerFa_OADTabLen                (E2Addr_RelayFa_OADTabLen+CLRelayFa_OADTabLen+C_CRCLen2)                  /*电源异常记录，1*/
#define E2Addr_RelayOpen_OADTabLen              (E2Addr_PowerFa_OADTabLen+CLPowerFa_OADTabLen+C_CRCLen2)                  /*跳闸记录，1*/
#define E2Addr_RelayClose_OADTabLen             (E2Addr_RelayOpen_OADTabLen+CLRelayOpen_OADTabLen+C_CRCLen2)              /*合闸记录，1*/
#define E2Addr_PFactorT_Over_OADTabLen          (E2Addr_RelayClose_OADTabLen+CLRelayClose_OADTabLen+C_CRCLen2)            /*总功率超限，1*/
#define E2Addr_AdjTime_OADTabLen                (E2Addr_PFactorT_Over_OADTabLen+CLPFactorT_Over_OADTabLen+C_CRCLen2)      /*校时，1*/
#define E2Addr_ProgPT_OADTabLen                 (E2Addr_AdjTime_OADTabLen+CLAdjTime_OADTabLen+C_CRCLen2)                  /*时段表，1*/
#define E2Addr_ProgTZ_OADTabLen                 (E2Addr_ProgPT_OADTabLen+CLProgPT_OADTabLen+C_CRCLen2)                    /*时区表，1*/
#define E2Addr_ProgWRe_OADTabLen                (E2Addr_ProgTZ_OADTabLen+CLProgTZ_OADTabLen+C_CRCLen2)                    /*周休日，1*/
#define E2Addr_ProgHol_OADTabLen                (E2Addr_ProgWRe_OADTabLen+CLProgWRe_OADTabLen+C_CRCLen2)                  /*节假日，1*/
#define E2Addr_ProgAcC_OADTabLen                (E2Addr_ProgHol_OADTabLen+CLProgHol_OADTabLen+C_CRCLen2)                  /*有功组合方式，1*/
#define E2Addr_ProgReC_OADTabLen                (E2Addr_ProgAcC_OADTabLen+CLProgAcC_OADTabLen+C_CRCLen2)                  /*无功组合方式，1*/
#define E2Addr_ProgSettD_OADTabLen              (E2Addr_ProgReC_OADTabLen+CLProgReC_OADTabLen+C_CRCLen2)                  /*结算日编程记录，1*/
#define E2Addr_ProgTPara_OADTabLen              (E2Addr_ProgSettD_OADTabLen+CLProgSettD_OADTabLen+C_CRCLen2)              /*费率表编程记录，1*/
#define E2Addr_ProgLad_OADTabLen                (E2Addr_ProgTPara_OADTabLen+CLProgTPara_OADTabLen+C_CRCLen2)              /*阶梯表编程记录，1*/
#define E2Addr_ProgKD_OADTabLen                 (E2Addr_ProgLad_OADTabLen+CLProgLad_OADTabLen+C_CRCLen2)                  /*密钥更新编程记录，1*/
#define E2Addr_MeterFa_OADTabLen                (E2Addr_ProgKD_OADTabLen+CLProgKD_OADTabLen+C_CRCLen2)                    /*计量芯片故障记录，1*/
#define E2Addr_ClockFa_OADTabLen                (E2Addr_MeterFa_OADTabLen+CLMeterFa_OADTabLen+C_CRCLen2)                  /*时钟故障记录，1*/
#define E2Addr_BroadcastTime_OADTabLen          (E2Addr_ClockFa_OADTabLen+CLClockFa_OADTabLen+C_CRCLen2)                  /*广播校时，1*/
#define E2Addr_NeutralCurrentAbnormal_OADTabLen (E2Addr_BroadcastTime_OADTabLen+CLBroadcastTime_OADTabLen+C_CRCLen2)      /*零线电流异常，1*/
#define C_EventOADTabLenNum                     (((E2Addr_NeutralCurrentAbnormal_OADTabLen+CLNeutralCurrentAbnormal_OADTabLen+C_CRCLen2)-E2Addr_All_Loss_Vol_OADTabLen)/(CLRelayClose_OADTabLen+C_CRCLen2))    /*事件关联列表总个数*/
/**********顺序不要随意调整******************************************************************************************/

#define E2Addr_698Key                           (E2Addr_NeutralCurrentAbnormal_OADTabLen+CLNeutralCurrentAbnormal_OADTabLen+C_CRCLen2)    /*698,认证密码*/
#define E2Addr_AllowFollowUpTell                (E2Addr_698Key+CL698Key+C_CRCLen2)                                              /*是否允许跟随上报1*/
#define E2Addr_AllowAccordUpTell                (E2Addr_AllowFollowUpTell+CLAllowFollowUpTell+C_CRCLen2)                        /*是否允许主动上报1*/
#define E2Addr_AllowMasterCall                  (E2Addr_AllowAccordUpTell+CLAllowAccordUpTell+C_CRCLen2)                        /*是否允许与主站通话1*/
#define E2Addr_UpTellChannel                    (E2Addr_AllowMasterCall+CLAllowMasterCall+C_CRCLen2)                            /*上报通道12*/
#define E2Addr_BuyCurr_TMoney                   (E2Addr_UpTellChannel+CLUpTellChannel+C_CRCLen2)                                /*累计购电金额4+2,清零要清除*/
#define E2Addr__IRAuth_Timer                    (E2Addr_BuyCurr_TMoney+CLBuyCurr_TMoney+C_CRCLen2)                              /*红外认证时效4+2*/
#define E2Addr_ProgReC1                         (E2Addr__IRAuth_Timer+CL_IRAuth_Timer+C_CRCLen2)                                /*组合无功1编程次数4+2*/
#define E2Addr_ProgReC2                         (E2Addr_ProgReC1+CLProgReC1_Degree+C_CRCLen2)                                   /*组合无功2编程次数4+2*/
#define E2Addr_RTC_AdjustTemp                   (E2Addr_ProgReC2+CLProgReC2_Degree+C_CRCLen2)                                   /*RTC校准温度值8+2，矩泉方案*/
#define E2Addr_RTC_AdjustTemp_End               (E2Addr_RTC_AdjustTemp+CLRTC_AdjustTemp+C_CRCLen2)                              /*RTC校准温度值8+2，矩泉方案,结束地址*/
#define E2Addr_Batt_Work_Time                   (E2Addr_RTC_AdjustTemp_End)                                                     /*电池工作时间，4+2CRC*/

#define E2Addr_LoadProfile_St                   (E2Addr_Batt_Work_Time+CLBatt_Work_Time+C_CRCLen2)
#define E2Addr_LoadP_Flash_Ear                  (E2Addr_LoadProfile_St)                                     /*最早一条记录Flash页地址，放E2地址三处带CRC*/
#define E2Addr_LoadP_Flash_Late                 (E2Addr_LoadP_Flash_Ear+CLFlashAddress+C_CRCLen2)           /*最近一条记录Flash页地址，放E2地址三处带CRC*/
#define E2Addr_Min_Free_Flash_Ear               (E2Addr_LoadP_Flash_Late+CLFlashAddress+C_CRCLen2)          /*最早一条记录Flash绝对地址,1字节日期调整标识+记录，放E2地址三处带CRC*/
#define E2Addr_Min_Free_Flash_Late              (E2Addr_Min_Free_Flash_Ear+CLFlashAddress+C_CRCLen2)        /*最近一条记录Flash页地址，放E2地址三处带CRC*/
#define E2Addr_I_Free_Flash_Ear                 (E2Addr_Min_Free_Flash_Late+CLFlashAddress+C_CRCLen2)       /*最早一条记录Flash绝对地址,1字节日期调整标识+记录，放E2地址三处带CRC*/
#define E2Addr_I_Free_Flash_Late                (E2Addr_I_Free_Flash_Ear+CLFlashAddress+C_CRCLen2)          /*最近一条记录Flash页地址，放E2地址三处带CRC*/
#define E2Addr_H_Free_Flash_Ear                 (E2Addr_I_Free_Flash_Late+CLFlashAddress+C_CRCLen2)         /*最早一条记录Flash绝对地址,1字节日期调整标识+记录，放E2地址三处带CRC*/
#define E2Addr_H_Free_Flash_Late                (E2Addr_H_Free_Flash_Ear+CLFlashAddress+C_CRCLen2)          /*最近一条记录Flash页地址，放E2地址三处带CRC*/
#define E2Addr_D_Free_Flash_Ear                 (E2Addr_H_Free_Flash_Late+CLFlashAddress+C_CRCLen2)         /*最早一条记录Flash绝对地址,1字节日期调整标识+记录，放E2地址三处带CRC*/
#define E2Addr_D_Free_Flash_Late                (E2Addr_D_Free_Flash_Ear+CLFlashAddress+C_CRCLen2)          /*最近一条记录Flash页地址，放E2地址三处带CRC*/
#define E2Addr_M_Free_Flash_Ear                 (E2Addr_D_Free_Flash_Late+CLFlashAddress+C_CRCLen2)         /*最早一条记录Flash绝对地址,1字节日期调整标识+记录，放E2地址三处带CRC*/
#define E2Addr_M_Free_Flash_Late                (E2Addr_M_Free_Flash_Ear+CLFlashAddress+C_CRCLen2)          /*最近一条记录Flash页地址，放E2地址三处带CRC*/
#define E2Addr_TZ_Free_Flash_Ear                (E2Addr_M_Free_Flash_Late+CLFlashAddress+C_CRCLen2)         /*最早一条记录Flash绝对地址,1字节日期调整标识+记录，放E2地址三处带CRC*/
#define E2Addr_TZ_Free_Flash_Late               (E2Addr_TZ_Free_Flash_Ear+CLFlashAddress+C_CRCLen2)         /*最近一条记录Flash页地址，放E2地址三处带CRC*/
#define E2Addr_PT_Free_Flash_Ear                (E2Addr_TZ_Free_Flash_Late+CLFlashAddress+C_CRCLen2)        /*最早一条记录Flash绝对地址,1字节日期调整标识+记录，放E2地址三处带CRC*/
#define E2Addr_PT_Free_Flash_Late               (E2Addr_PT_Free_Flash_Ear+CLFlashAddress+C_CRCLen2)         /*最近一条记录Flash页地址，放E2地址三处带CRC*/
#define E2Addr_R_Free_Flash_Ear                 (E2Addr_PT_Free_Flash_Late+CLFlashAddress+C_CRCLen2)        /*最早一条记录Flash绝对地址,1字节日期调整标识+记录，放E2地址三处带CRC*/
#define E2Addr_R_Free_Flash_Late                (E2Addr_R_Free_Flash_Ear+CLFlashAddress+C_CRCLen2)          /*最近一条记录Flash页地址，放E2地址三处带CRC*/
#define E2Addr_L_Free_Flash_Ear                 (E2Addr_R_Free_Flash_Late+CLFlashAddress+C_CRCLen2)         /*最早一条记录Flash绝对地址,1字节日期调整标识+记录，放E2地址三处带CRC*/
#define E2Addr_L_Free_Flash_Late                (E2Addr_L_Free_Flash_Ear+CLFlashAddress+C_CRCLen2)          /*最近一条记录Flash页地址，放E2地址三处带CRC*/
#define E2Addr_Sett_Free_Flash_Ear              (E2Addr_L_Free_Flash_Late+CLFlashAddress+C_CRCLen2)         /*最早一条记录Flash绝对地址,1字节日期调整标识+记录，放E2地址三处带CRC*/
#define E2Addr_Sett_Free_Flash_Late             (E2Addr_Sett_Free_Flash_Ear+CLFlashAddress+C_CRCLen2)       /*最近一条记录Flash页地址，放E2地址三处带CRC*/
#define E2Addr_Y_Free_Flash_Ear                 (E2Addr_Sett_Free_Flash_Late+CLFlashAddress+C_CRCLen2)      /*最早一条记录Flash绝对地址,1字节日期调整标识+记录，放E2地址三处带CRC*/
#define E2Addr_Y_Free_Flash_Late                (E2Addr_Y_Free_Flash_Ear+CLFlashAddress+C_CRCLen2)          /*最近一条记录Flash页地址，放E2地址三处带CRC,4+2数据长度*/
#define E2Addr_Sett_Freeze_Flash_Ear            (E2Addr_Y_Free_Flash_Late+CLFlashAddress+C_CRCLen2)         /*最近一条记录Flash页地址，放E2地址三处带CRC,4+2数据长度*/
#define E2Addr_Sett_Freeze_Flash_Late           (E2Addr_Sett_Freeze_Flash_Ear+CLFlashAddress+C_CRCLen2)     /*最近一条记录Flash页地址，放E2地址三处带CRC,4+2数据长度*/

#define E2Addr_SafeModeParaNat3_Num             (E2Addr_Sett_Freeze_Flash_Late+CLFlashAddress+C_CRCLen2)    /*安全模式参数,属性3,元素个数三处带CRC,1+2数据长度*/

#define E2Addr_Min_Free_Flash_Ear1              (E2Addr_SafeModeParaNat3_Num+CLSafeModeParaNat3_Num+C_CRCLen2)                        /*分钟冻结8种方案，Flash记录存储最近、最早记录Flash地址，8*(4+2+4+2),96,最早、最近单独带 CRC*/
#define E2Addr_Min_Free_FlashAddr_Allo          (E2Addr_Min_Free_Flash_Ear1+8*(CLFlashAddress+C_CRCLen2+CLFlashAddress+C_CRCLen2))    /*分钟冻结8种方案，Flash记录存储地址分配起始、结束地址存E2，8*(4+4),64+2 CRC*/

/*698兼容645时增加*/
#define E2Addr_Relay_Delay_Time_645             (E2Addr_Min_Free_FlashAddr_Allo+8*(CLFlashAddress+CLFlashAddress)+C_CRCLen2)          /*用于存储645跳闸延时时间2字节+2字节CRC*/
#define E2Addr_Drive_Report_Mode_645            (E2Addr_Relay_Delay_Time_645+CLRelay_Delay_Time_645+C_CRCLen2)                        /*用于存储645主动上报模式字8字节+2字节CRC*/
#define E2Addr_Meter_Work_Char1_645             (E2Addr_Drive_Report_Mode_645+CLDrive_Report_Mode_645+C_CRCLen2)                      /*用于存储645电表运行特征字1 1字节+2字节CRC*/
#define E2Addr_ProgPT_CurrentPart_Degree        (E2Addr_Meter_Work_Char1_645+CLMeter_Work_Char1_645+C_CRCLen2)                        /*用于存储645时段表次数 4字节+2字节CRC*/
#define E2Addr_ProgTZ_CurrentPart_Degree        (E2Addr_ProgPT_CurrentPart_Degree+CLProgPT_CurrentPart_Degree+C_CRCLen2)              /*用于存储645时区表次数 4字节+2字节CRC*/
#define E2Addr_Program_Degree_645               (E2Addr_ProgTZ_CurrentPart_Degree+CLProgTZ_CurrentPart_Degree+C_CRCLen2)              /*用于存储645编程记录次数 3字节+2字节CRC*/
#define E2Addr_Meter_Work_Char1                 (E2Addr_Program_Degree_645+CLProgram_Degree_645+C_CRCLen2)                            /*用于存储698电表运行特征字1 1字节+2字节CRC*/

#define E2Addr_ParaEnd                 			(E2Addr_Meter_Work_Char1+CLMeter_Work_Char1+C_CRCLen2)                           	  /*结束*/

/***********以上E2三处数据空间，还剩将近42byte**************/
#if ((E2Addr_ParaEnd > 0x4600)?1:0) /*编译器报错*/
	#error "EEPROM Capacity Exhausted!"
#endif

/****************************************计量校表数据,E2三处带CRC,预留2kbyte*******************************************/
#define E2Addr_MeterIC_St                       0x4600                                                                  /*校表数据存E2起始地址*/
#define E2Addr_MeterIC_End                      (E2Addr_MeterIC_St+C_MeterICDataNum_T*(C_MeterICE2ResLen+C_CRCLen2))    /*校表数据存E2结束地址*/

/*复旦微RTC调校新增*/
#define E2Addr_temperatureAddr                  (E2Addr_MeterIC_End)                                                    /*温度补偿系数存E2,11+2 CRC*/
#define E2Addr_ptatvalueAddr                    (E2Addr_temperatureAddr+ee_temperature_lenth+C_CRCLen2)                 /*常温查表温度ADC页地址E2,42+2CRC*/
#define E2Addr_ptatvalue_ltAddr                 (E2Addr_ptatvalueAddr+ee_ptatvalue_lenth+C_CRCLen2)                     /*低温查表温度ADC页地址E2,30+2+2CRC*/
#define E2Addr_ptatvalue_htAddr                 (E2Addr_ptatvalue_ltAddr+ee_ptatvalue_lt_lenth+2+C_CRCLen2)             /*高温查表温度ADC页地址E2,30+2+2CRC*/
#define E2Addr_trimvalueAddr                    (E2Addr_ptatvalue_htAddr+ee_ptatvalue_ht_lenth+2+C_CRCLen2)             /*常温查表温度补偿值页地址E2,42+2CRC*/
#define E2Addr_trimvalue_ltAddr                 (E2Addr_trimvalueAddr+ee_trimvalue_lenth+C_CRCLen2)                     /*低温查表温度补偿值页地址E2,30+2+2CRC*/
#define E2Addr_trimvalue_htAddr                 (E2Addr_trimvalue_ltAddr+ee_trimvalue_lt_lenth+2+C_CRCLen2)             /*高温查表温度补偿值页地址E2,30+2+2CRC*/
#define E2Addr_rtcadj_timeAddr                  (E2Addr_trimvalue_htAddr+ee_trimvalue_ht_lenth+2+C_CRCLen2)             /*写常温顶点调校值时时间记录页地址(始终不清),10+2CRC*/

#define E2Addr_Odd_Harmonic_AddData1            (E2Addr_rtcadj_timeAddr+ee_rtcadjtime_lenth+C_CRCLen2)                  /*奇次谐波补偿值1,(电流:2.8A~4A条件),3+2CRC*/
#define E2Addr_Odd_Harmonic_AddData2            (E2Addr_Odd_Harmonic_AddData1+CL_OddHar_AddData1+C_CRCLen2)             /*奇次谐波补偿值2,(电流:1.4A~2A条件),3+2CRC*/

#define E2Addr_Even_Harmonic_AddData_A0         (E2Addr_Odd_Harmonic_AddData2+CL_OddHar_AddData2+C_CRCLen2)             /*偶次谐波补偿值1,(0.5L条件),3+2CRC*/
#define E2Addr_Even_Harmonic_AddData_A1         (E2Addr_Even_Harmonic_AddData_A0+CL_EvenHar_AddData_A0+C_CRCLen2)       /*偶次谐波补偿值2,(0.5L条件),3+2CRC*/
#define E2Addr_Even_Harmonic_AddData_B0         (E2Addr_Even_Harmonic_AddData_A1+CL_EvenHar_AddData_A1+C_CRCLen2)       /*偶次谐波补偿值2,(0.5L条件),3+2CRC*/
#define E2Addr_Even_Harmonic_AddData_B1         (E2Addr_Even_Harmonic_AddData_B0+CL_EvenHar_AddData_B0+C_CRCLen2)       /*偶次谐波补偿值1,(0.5L条件),3+2CRC*/
#define E2Addr_Even_Harmonic_AddData_C0         (E2Addr_Even_Harmonic_AddData_B1+CL_EvenHar_AddData_B1+C_CRCLen2)       /*偶次谐波补偿值2,(0.5L条件),3+2CRC*/
#define E2Addr_Even_Harmonic_AddData_C1         (E2Addr_Even_Harmonic_AddData_C0+CL_EvenHar_AddData_C0+C_CRCLen2)       /*偶次谐波补偿值2,(0.5L条件),3+2CRC*/
/******************************以上E2三处校表等试验数据空间，还剩数据量119byte*******************************/

/****************************************E2 1处定义,0xD800-FFFE**********************************************/
#define E2Addr_Y_Com_Ac_Tol_En_St               E2_Remaind_Space                                                        /*年结算电量起始地址*/
#define E2Addr_Y_Com_Ac_Tol_En_1                E2Addr_Y_Com_Ac_Tol_En_St                                               /*上1次年结算日结算时间及上1年结算周期组合有功总累计用电量*/
#define E2Addr_Y_Com_Ac_Tol_En_2                (E2Addr_Y_Com_Ac_Tol_En_1+CLY_Com_Ac_Tol_En_1)                          /*上2次年结算日结算时间及上2年结算周期组合有功总累计用电量*/
#define E2Addr_Y_Com_Ac_Tol_En_3                (E2Addr_Y_Com_Ac_Tol_En_2+CLY_Com_Ac_Tol_En_2)                          /*上3次年结算日结算时间及上3年结算周期组合有功总累计用电量*/
#define E2Addr_Y_Com_Ac_Tol_En_4                (E2Addr_Y_Com_Ac_Tol_En_3+CLY_Com_Ac_Tol_En_3)                          /*上4次年结算日结算时间及上4年结算周期组合有功总累计用电量*/
#define E2Addr_Load_Rec_Time_Year               (E2Addr_Y_Com_Ac_Tol_En_4+CLY_Com_Ac_Tol_En_4)                          /*负荷记录起始时间,YYMMDDhhmm*/
#define E2Addr_Y_Com_Ac_Tol_En_End              E2Addr_Load_Rec_Time_Year                                               /*年结算电量结束地址*/

#define E2Addr_Auto_Dis_1ScreenCode             (E2Addr_Load_Rec_Time_Year+CLLoad_Rec_Time_Year)                        /*自动循显显示第1-99屏显示代码，99*(9+2)=693*/
#define E2Addr_Key_Dis_1ScreenCode              (E2Addr_Auto_Dis_1ScreenCode+99*(CLAuto_Dis_1ScreenCode+C_CRCLen2))     /*按键循显显示第1-99屏显示代码，99*(9+2)=693*/

/*公共假日后续需修改为20个*/
#define E2Addr_Holidy_PT_Table1                 (E2Addr_Key_Dis_1ScreenCode+99*(CLKey_Dis_1ScreenCode+C_CRCLen2))       /*第1-20公共假日日期及日时段表号*/
#if 0
#define E2Addr_Holidy_PT_Table_Fa01             (E2Addr_Holidy_PT_Table1)                                               /*第1-20公共假日日期及日时段表号*/
#define E2Addr_Holidy_PT_Table_Fa02             (E2Addr_Holidy_PT_Table_Fa01+CLHolidy_PT_Table_Fa01)                    /*第64-126公共假日日期及日时段表号*/
#define E2Addr_Holidy_PT_Table_Fa03             (E2Addr_Holidy_PT_Table_Fa02+CLHolidy_PT_Table_Fa02)                    /*第127-189公共假日日期及日时段表号*/
#define E2Addr_Holidy_PT_Table_Fa04             (E2Addr_Holidy_PT_Table_Fa03+CLHolidy_PT_Table_Fa03)                    /*第190-252公共假日日期及日时段表号*/
#define E2Addr_Holidy_PT_Table_Fa05             (E2Addr_Holidy_PT_Table_Fa04+CLHolidy_PT_Table_Fa04)                    /*第253-254公共假日日期及日时段表号*/
#endif

#define E2Addr_EquipmentDis                     (E2Addr_Holidy_PT_Table1+CLHolidy_PT_Table1*20)                   /*设备描述符32*/

#define E2Addr_Factory_Number                   (E2Addr_EquipmentDis+CLEquipmentDis)                              /*厂家编号*/
#define E2Addr_Factory_Softw_Version            (E2Addr_Factory_Number+CLFactory_Number)                          /*厂家软件版本号*/
#define E2Addr_Factory_Softw_VersionDate        (E2Addr_Factory_Softw_Version+CLFactory_Softw_Version)            /*厂家软件版本日期，6*/
#define E2Addr_Factory_Hardw_Version            (E2Addr_Factory_Softw_VersionDate+CLFactory_Softw_VersionDate)    /*硬件版本号*/
#define E2Addr_Factory_Hardw_VersionDate        (E2Addr_Factory_Hardw_Version+CLFactory_Hardw_Version)            /*厂家硬件版本日期,6*/
#define E2Addr_Factory_ExternSign               (E2Addr_Factory_Hardw_VersionDate+CLFactory_Hardw_VersionDate)    /*厂家扩展信息,8*/

#if 0	/*后续使用*/
#define E2Addr_FactoryInfomation         (E2Addr_SafeModePara+CLSafeModePara+C_CRCLen2)                           /*厂家信息*/
#endif

#define E2Addr_Meter_CommPro1                   (E2Addr_Factory_ExternSign+CLFactory_ExternSign)                  /*电表支持通信协议1*/
#define E2Addr_Meter_CommPro2                   (E2Addr_Meter_CommPro1+CLMeter_CommPro1)                          /*电表支持通信协议2*/

#define E2Addr_Softw_Record_Number              (E2Addr_Meter_CommPro2+CLMeter_CommPro2)                          /*软件备案号*/

#define E2Addr_Control_ExecuteState             (E2Addr_Softw_Record_Number+CLSoftw_Record_Number)                /*控制命令执行状态字，2字节*/
#define E2Addr_Control_ErrorState               (E2Addr_Control_ExecuteState+CLControl_ExecuteState)              /*控制命令错误状态字，2字节*/

#define E2Addr_SafeModeParaNat3                 (E2Addr_Control_ErrorState+CLControl_ErrorState)                  /*安全模式参数,属性3带CRC，1+50*4*/

#define E2Addr_ClientAddr                       (E2Addr_SafeModeParaNat3+CLSafeModeParaNat3+C_CRCLen2)            /*当前连接的客户机地址 1*/

#define E2NewReportList                         (E2Addr_ClientAddr+CLClientAddr)                                  /*新增上报列表70*2+1+2CRC*/
#define E2Drive_Report_State_New                (E2NewReportList+CLNewReportList+C_CRCLen2)                       /*跟随上报状态字4+32+2CRC*/

#define E2Addr_Clock_FaultTime                  (E2Drive_Report_State_New+CLDrive_Report_State_New+C_CRCLen2)     /*广播校时异常时钟故障时间*/
#define E2Addr_Even_Harmonic_Time               (E2Addr_Clock_FaultTime+CLClock_FaultTime)                        /*偶次谐波补偿计时，默认24h*60min*/
#define E2Addr_CDoubleAgreementFlag             (E2Addr_Even_Harmonic_Time+CL_EvenHar_Time)                       /*是否双协议的标志，主要是用于协议版本号一个还是两个*/
/***********以上E2 1处数据空间，还剩将近1996byte**************/

/*******************Flash大小为64MBit，4MByte，每页4kByte，共2048页***********************/
/****************************************存Flash数据**************************************/
#define C_OneFlashPage                   0x00001000                                      /*每页Flash大小*/
#define C_TenFlashPage                   0x0000A000
#define C_Flash_Max_Addr                 0x007FFFFF                                      /*Flash最大地址*/

/**********结算电能共345个字节，每页Flash 4092/345=11次，12次采用多页存储，0~0x3000共4页**********/
#define SettEn_Data_Len                  345                                             /*结算电能数据长度*/
#define FlashStAddr_SettEn               0x00000000                                      /*结算电能Flash首页地址*/
#define FlashEndAddr_SettEn              (FlashStAddr_SettEn+C_OneFlashPage*3)           /*结算电能Flash尾页地址*/

/*********************结算日结算时间后加,共4个字节，每页Flash 4092/4=1023，12次采用奇偶页存储****6**4~5*******/
#define SettTime_Data_Len                4                                               /*结算日结算时间数据长度*/
#define FlashStAddr_SettTime             (FlashEndAddr_SettEn+C_OneFlashPage)            /*结算日结算时间Flash首页地址*/
#define FlashEndAddr_SettTime            (FlashStAddr_SettTime+C_OneFlashPage)           /*结算日结算时间Flash尾页地址*/

/*********************698结算冻结，采用原来的结算电能及结算需量，上面的结算电能、需量、结算日没有用****10********/
#define FlashStAddr_Sett_Free            0x00000000                                       /*结算电能Flash首页地址*/
#define FlashEndAddr_Sett_Free           (FlashStAddr_Sett_Free+C_OneFlashPage*9)         /*结算电能Flash尾页地址*/

/*********************电网类事件***698事件记录，默认关联列表，基本都是原645记录数据项*****************************/
/*********************全失压共15个字节，每页Flash 4092/15=272，698后22，10次采用奇偶页存储********12****10~11*****/
#define All_Loss_Vol_Data_Len            15                                               /*全失压数据长度*/
#define FlashStAddr_All_Loss_Vol         (FlashEndAddr_Sett_Free+C_OneFlashPage)          /*全失压Flash首页地址*/
#define FlashEndAddr_All_Loss_Vol        (FlashStAddr_All_Loss_Vol+C_OneFlashPage)        /*全失压Flash尾页地址*/

/*********************辅助电源掉电共12个字节，每页Flash 4092/12=341，301110次采用奇偶页存储****14******12~13*******/
#define Aux_Pow_Down_Data_Len            12                                               /*辅助电源掉电数据长度*/
#define FlashStAddr_Aux_Pow_Down         (FlashEndAddr_All_Loss_Vol+C_OneFlashPage)       /*辅助电源掉电Flash首页地址*/
#define FlashEndAddr_Aux_Pow_Down        (FlashStAddr_Aux_Pow_Down+C_OneFlashPage)        /*辅助电源掉电Flash尾页地址*/

/*********************电源掉电共12个字节，每页Flash 4092/12=341，698后19，10次采用奇偶页存储*********16****14~15****/
#define Pow_Down_Data_Len                12                                               /*电源掉电数据长度*/
#define FlashStAddr_Pow_Down             (FlashEndAddr_Aux_Pow_Down+C_OneFlashPage)       /*电源掉电Flash首页地址*/
#define FlashEndAddr_Pow_Down            (FlashStAddr_Pow_Down+C_OneFlashPage*2)          /*电源掉电Flash尾页地址*/

/*********************需量超限共20个字节，每页Flash 4092/20=204，698后27，10次采用奇偶页存储*********28********/
#define De_Over_Data_Len                 20                                               /*需量超限数据长度*/
#define FlashStAddr_Pos_Ac_De_Over       (FlashEndAddr_Pow_Down+C_OneFlashPage)           /*正向有功需量超限Flash首页地址*/
#define FlashEndAddr_Pos_Ac_De_Over      (FlashStAddr_Pos_Ac_De_Over+C_OneFlashPage)      /*正向有功需量超限Flash尾页地址*/
#define FlashStAddr_Rev_Ac_De_Over       (FlashEndAddr_Pos_Ac_De_Over+C_OneFlashPage)     /*反向有功需量超限Flash首页地址*/
#define FlashEndAddr_Rev_Ac_De_Over      (FlashStAddr_Rev_Ac_De_Over+C_OneFlashPage)      /*反向有功需量超限Flash尾页地址*/
#define FlashStAddr_Qua1_Re_De_Over      (FlashEndAddr_Rev_Ac_De_Over+C_OneFlashPage)     /*1象限无功需量超限Flash首页地址*/
#define FlashEndAddr_Qua1_Re_De_Over     (FlashStAddr_Qua1_Re_De_Over+C_OneFlashPage)     /*1象限无功需量超限Flash尾页地址*/
#define FlashStAddr_Qua2_Re_De_Over      (FlashEndAddr_Qua1_Re_De_Over+C_OneFlashPage)    /*2象限无功需量超限Flash首页地址*/
#define FlashEndAddr_Qua2_Re_De_Over     (FlashStAddr_Qua2_Re_De_Over+C_OneFlashPage)     /*2象限无功需量超限Flash尾页地址*/
#define FlashStAddr_Qua3_Re_De_Over      (FlashEndAddr_Qua2_Re_De_Over+C_OneFlashPage)    /*3象限无功需量超限Flash首页地址*/
#define FlashEndAddr_Qua3_Re_De_Over     (FlashStAddr_Qua3_Re_De_Over+C_OneFlashPage)     /*3象限无功需量超限Flash尾页地址*/
#define FlashStAddr_Qua4_Re_De_Over      (FlashEndAddr_Qua3_Re_De_Over+C_OneFlashPage)    /*4象限无功需量超限Flash首页地址*/
#define FlashEndAddr_Qua4_Re_De_Over     (FlashStAddr_Qua4_Re_De_Over+C_OneFlashPage)     /*4象限无功需量超限Flash尾页地址*/

/*********************失压记录共195个字节，每页Flash 4092/195=20，698后230，4092/230=17，10次采用奇偶页存储********34*********/
#define Loss_Vol_Data_Len                195                                              /*失压数据长度*/
#define FlashStAddr_LossA_Vol            (FlashEndAddr_Qua4_Re_De_Over+C_OneFlashPage)    /*A相失压Flash首页地址*/
#define FlashEndAddr_LossA_Vol           (FlashStAddr_LossA_Vol+C_OneFlashPage)           /*A相失压Flash尾页地址*/
#define FlashStAddr_LossB_Vol            (FlashEndAddr_LossA_Vol+C_OneFlashPage)          /*B相失压Flash首页地址*/
#define FlashEndAddr_LossB_Vol           (FlashStAddr_LossB_Vol+C_OneFlashPage)           /*B相失压Flash尾页地址*/
#define FlashStAddr_LossC_Vol            (FlashEndAddr_LossB_Vol+C_OneFlashPage)          /*C相失压Flash首页地址*/
#define FlashEndAddr_LossC_Vol           (FlashStAddr_LossC_Vol+C_OneFlashPage)           /*C相失压Flash尾页地址*/

/*********************欠压记录共195个字节，每页Flash 4092/195=20，698后230，4092/230=17，10次采用奇偶页存储*********40********/
#define Low_Vol_Data_Len                 195                                              /*欠压数据长度*/
#define FlashStAddr_LowA_Vol             (FlashEndAddr_LossC_Vol+C_OneFlashPage)          /*A相欠压Flash首页地址*/
#define FlashEndAddr_LowA_Vol            (FlashStAddr_LowA_Vol+C_OneFlashPage)            /*A相欠压Flash尾页地址*/
#define FlashStAddr_LowB_Vol             (FlashEndAddr_LowA_Vol+C_OneFlashPage)           /*B相欠压Flash首页地址*/
#define FlashEndAddr_LowB_Vol            (FlashStAddr_LowB_Vol+C_OneFlashPage)            /*B相欠压Flash尾页地址*/
#define FlashStAddr_LowC_Vol             (FlashEndAddr_LowB_Vol+C_OneFlashPage)           /*C相欠压Flash首页地址*/
#define FlashEndAddr_LowC_Vol            (FlashStAddr_LowC_Vol+C_OneFlashPage)            /*C相欠压Flash尾页地址*/

/*********************过压记录共195个字节，每页Flash 4092/195=20，698后230，4092/230=17，10次采用奇偶页存储********46*********/
#define Over_Vol_Data_Len                195                                              /*过压数据长度*/
#define FlashStAddr_OverA_Vol            (FlashEndAddr_LowC_Vol+C_OneFlashPage)           /*A相过压Flash首页地址*/
#define FlashEndAddr_OverA_Vol           (FlashStAddr_OverA_Vol+C_OneFlashPage)           /*A相过压Flash尾页地址*/
#define FlashStAddr_OverB_Vol            (FlashEndAddr_OverA_Vol+C_OneFlashPage)          /*B相过压Flash首页地址*/
#define FlashEndAddr_OverB_Vol           (FlashStAddr_OverB_Vol+C_OneFlashPage)           /*B相过压Flash尾页地址*/
#define FlashStAddr_OverC_Vol            (FlashEndAddr_OverB_Vol+C_OneFlashPage)          /*C相过压Flash首页地址*/
#define FlashEndAddr_OverC_Vol           (FlashStAddr_OverC_Vol+C_OneFlashPage)           /*C相过压Flash尾页地址*/

/*********************断相记录共195个字节，每页Flash 4092/195=20，698后230，4092/230=17，10次采用奇偶页存储*******52**********/
#define Break_Vol_Data_Len               195                                              /*断相数据长度*/
#define FlashStAddr_BreakA_Vol           (FlashEndAddr_OverC_Vol+C_OneFlashPage)          /*A相断相Flash首页地址*/
#define FlashEndAddr_BreakA_Vol          (FlashStAddr_BreakA_Vol+C_OneFlashPage)          /*A断相压Flash尾页地址*/
#define FlashStAddr_BreakB_Vol           (FlashEndAddr_BreakA_Vol+C_OneFlashPage)         /*B相断相Flash首页地址*/
#define FlashEndAddr_BreakB_Vol          (FlashStAddr_BreakB_Vol+C_OneFlashPage)          /*B相断相Flash尾页地址*/
#define FlashStAddr_BreakC_Vol           (FlashEndAddr_BreakB_Vol+C_OneFlashPage)         /*C相断相Flash首页地址*/
#define FlashEndAddr_BreakC_Vol          (FlashStAddr_BreakC_Vol+C_OneFlashPage)          /*C相断相Flash尾页地址*/

/*********************电压逆相序共140个字节，每页Flash 4092/140=29，698后147，10次采用奇偶页存储*********54********/
#define RevPS_Vol_Data_Len               140                                              /*电压逆相序数据长度*/
#define FlashStAddr_RevPS_Vol            (FlashEndAddr_BreakC_Vol+C_OneFlashPage)         /*电压逆相序Flash首页地址*/
#define FlashEndAddr_RevPS_Vol           (FlashStAddr_RevPS_Vol+C_OneFlashPage)           /*电压逆相序Flash尾页地址*/

/*********************电流逆相序共140个字节，每页Flash 4092/140=29，10次采用奇偶页存储********56*********/
#define RevPS_Curr_Data_Len              140                                              /*电流逆相序数据长度*/
#define FlashStAddr_RevPS_Curr           (FlashEndAddr_RevPS_Vol+C_OneFlashPage)          /*电流逆相序Flash首页地址*/
#define FlashEndAddr_RevPS_Curr          (FlashStAddr_RevPS_Curr+C_OneFlashPage)          /*电流逆相序Flash尾页地址*/

/*********************电压不平衡共143个字节，每页Flash 4092/143=28，698后150，10次采用奇偶页存储*********58********/
#define NoBal_Vol_Data_Len               143                                              /*电压不平衡数据长度*/
#define FlashStAddr_NoBal_Vol            (FlashEndAddr_RevPS_Curr+C_OneFlashPage)         /*电压不平衡Flash首页地址*/
#define FlashEndAddr_NoBal_Vol           (FlashStAddr_NoBal_Vol+C_OneFlashPage)           /*电压不平衡Flash尾页地址*/

/*********************电流不平衡共143个字节，每页Flash 4092/143=28，698后150，10次采用奇偶页存储********60*********/
#define NoBal_Curr_Data_Len              143                                              /*电流不平衡数据长度*/
#define FlashStAddr_NoBal_Curr           (FlashEndAddr_NoBal_Vol+C_OneFlashPage)          /*电流不平衡Flash首页地址*/
#define FlashEndAddr_NoBal_Curr          (FlashStAddr_NoBal_Curr+C_OneFlashPage)          /*电流不平衡Flash尾页地址*/

/*********************电流严重不平衡共143个字节，每页Flash 4092/143=28，698后150，10次采用奇偶页存储*****62************/
#define SevNoBal_Curr_Data_Len           143                                              /*电流严重不平衡数据长度*/
#define FlashStAddr_SevNoBal_Curr        (FlashEndAddr_NoBal_Curr+C_OneFlashPage)         /*电流严重不平衡Flash首页地址*/
#define FlashEndAddr_SevNoBal_Curr       (FlashStAddr_SevNoBal_Curr+C_OneFlashPage)       /*电流严重不平衡Flash尾页地址*/

/*********************失流共179个字节，每页Flash 4092/179=22，698后214，4092/214=19，10次采用奇偶页存储**********68*******/
#define Loss_Curr_Data_Len               179                                              /*失流数据长度*/
#define FlashStAddr_LossA_Curr           (FlashEndAddr_SevNoBal_Curr+C_OneFlashPage)      /*A相失流Flash首页地址*/
#define FlashEndAddr_LossA_Curr          (FlashStAddr_LossA_Curr+C_OneFlashPage)          /*A相失流Flash尾页地址*/
#define FlashStAddr_LossB_Curr           (FlashEndAddr_LossA_Curr+C_OneFlashPage)         /*B相失流Flash首页地址*/
#define FlashEndAddr_LossB_Curr          (FlashStAddr_LossB_Curr+C_OneFlashPage)          /*B相失流Flash尾页地址*/
#define FlashStAddr_LossC_Curr           (FlashEndAddr_LossB_Curr+C_OneFlashPage)         /*C相失流Flash首页地址*/
#define FlashEndAddr_LossC_Curr          (FlashStAddr_LossC_Curr+C_OneFlashPage)          /*C相失流Flash尾页地址*/

/*********************过流共179个字节，每页Flash 4092/179=22，698后214，4092/214=19，10次采用奇偶页存储**********74*******/
#define Over_Curr_Data_Len               179                                              /*过流数据长度*/
#define FlashStAddr_OverA_Curr           (FlashEndAddr_LossC_Curr+C_OneFlashPage)         /*A相过流Flash首页地址*/
#define FlashEndAddr_OverA_Curr          (FlashStAddr_OverA_Curr+C_OneFlashPage)          /*A相过流Flash尾页地址*/
#define FlashStAddr_OverB_Curr           (FlashEndAddr_OverA_Curr+C_OneFlashPage)         /*B相过流Flash首页地址*/
#define FlashEndAddr_OverB_Curr          (FlashStAddr_OverB_Curr+C_OneFlashPage)          /*B相过流Flash尾页地址*/
#define FlashStAddr_OverC_Curr           (FlashEndAddr_OverB_Curr+C_OneFlashPage)         /*C相过流Flash首页地址*/
#define FlashEndAddr_OverC_Curr          (FlashStAddr_OverC_Curr+C_OneFlashPage)          /*C相过流Flash尾页地址*/

/*********************断流共179个字节，每页Flash 4092/179=22，698后214，4092/214=19，10次采用奇偶页存储*********80********/
#define Break_Curr_Data_Len              179                                              /*断流数据长度*/
#define FlashStAddr_BreakA_Curr          (FlashEndAddr_OverC_Curr+C_OneFlashPage)         /*A相断流Flash首页地址*/
#define FlashEndAddr_BreakA_Curr         (FlashStAddr_BreakA_Curr+C_OneFlashPage)         /*A相断流Flash尾页地址*/
#define FlashStAddr_BreakB_Curr          (FlashEndAddr_BreakA_Curr+C_OneFlashPage)        /*B相断流Flash首页地址*/
#define FlashEndAddr_BreakB_Curr         (FlashStAddr_BreakB_Curr+C_OneFlashPage)         /*B相断流Flash尾页地址*/
#define FlashStAddr_BreakC_Curr          (FlashEndAddr_BreakB_Curr+C_OneFlashPage)        /*C相断流Flash首页地址*/
#define FlashEndAddr_BreakC_Curr         (FlashStAddr_BreakC_Curr+C_OneFlashPage)         /*C相断流Flash尾页地址*/

/*********************功率反向共140个字节，每页Flash 4092/140=29，698后147，4092/147=27，10次采用奇偶页存储*********86********/
#define Power_Rev_Data_Len               140                                              /*功率反向数据长度*/
#define FlashStAddr_PowerT_Rev           (FlashEndAddr_BreakC_Curr+C_OneFlashPage)        /*总功率反向Flash首页地址*/
#define FlashEndAddr_PowerT_Rev          (FlashStAddr_PowerT_Rev+C_OneFlashPage)          /*总功率反向Flash尾页地址*/
#define FlashStAddr_PowerA_Rev           (FlashEndAddr_PowerT_Rev+C_OneFlashPage)         /*A相功率反向Flash首页地址*/
#define FlashEndAddr_PowerA_Rev          (FlashStAddr_PowerA_Rev+C_OneFlashPage)          /*A相功率反向Flash尾页地址*/
#define FlashStAddr_PowerB_Rev           (FlashEndAddr_PowerA_Rev+C_OneFlashPage)         /*B相功率反向Flash首页地址*/
#define FlashEndAddr_PowerB_Rev          (FlashStAddr_PowerB_Rev+C_OneFlashPage)          /*B相功率反向Flash尾页地址*/
#define FlashStAddr_PowerC_Rev           (FlashEndAddr_PowerB_Rev+C_OneFlashPage)         /*C相功率反向Flash首页地址*/
#define FlashEndAddr_PowerC_Rev          (FlashStAddr_PowerC_Rev+C_OneFlashPage)          /*C相功率反向Flash尾页地址*/

/*********************过载共140个字节，每页Flash 4092/140=29，698后147，4092/147=27，10次采用奇偶页存储**********92*******/
#define Over_Lo_Data_Len                 140                                              /*过载数据长度*/
#define FlashStAddr_OverA_Lo             (FlashEndAddr_PowerC_Rev+C_OneFlashPage)         /*A相过载Flash首页地址*/
#define FlashEndAddr_OverA_Lo            (FlashStAddr_OverA_Lo+C_OneFlashPage)            /*A相过载Flash尾页地址*/
#define FlashStAddr_OverB_Lo             (FlashEndAddr_OverA_Lo+C_OneFlashPage)           /*B相过载Flash首页地址*/
#define FlashEndAddr_OverB_Lo            (FlashStAddr_OverB_Lo+C_OneFlashPage)            /*B相过载Flash尾页地址*/
#define FlashStAddr_OverC_Lo             (FlashEndAddr_OverB_Lo+C_OneFlashPage)           /*C相过载Flash首页地址*/
#define FlashEndAddr_OverC_Lo            (FlashStAddr_OverC_Lo+C_OneFlashPage)            /*C相过载Flash尾页地址*/

/*********************功率因数超下限共44个字节，每页Flash 4092/44=93，10次采用奇偶页存储*******102**********/
#define PFactor_Over_Data_Len            44                                               /*总功率因数超下限数据长度*/
#define FlashStAddr_PFactorT_Over        (FlashEndAddr_OverC_Lo+C_OneFlashPage)           /*总功率因数超下限Flash首页地址*/
#define FlashEndAddr_PFactorT_Over       (FlashStAddr_PFactorT_Over+C_OneFlashPage)       /*总功率因数超下限Flash尾页地址*/
#define FlashStAddr_PFactorA_Over        (FlashEndAddr_PFactorT_Over+C_OneFlashPage)      /*A相功率因数超下限Flash首页地址*/
#define FlashEndAddr_PFactorA_Over       (FlashStAddr_PFactorA_Over+C_OneFlashPage)       /*A相功率因数超下限Flash尾页地址*/
#define FlashStAddr_PFactorB_Over        (FlashEndAddr_PFactorA_Over+C_OneFlashPage)      /*B相功率因数超下限Flash首页地址*/
#define FlashEndAddr_PFactorB_Over       (FlashStAddr_PFactorB_Over+C_OneFlashPage)       /*B相功率因数超下限Flash尾页地址*/
#define FlashStAddr_PFactorC_Over        (FlashEndAddr_PFactorB_Over+C_OneFlashPage)      /*C相功率因数超下限Flash首页地址*/
#define FlashEndAddr_PFactorC_Over       (FlashStAddr_PFactorC_Over+C_OneFlashPage)       /*C相功率因数超下限Flash尾页地址*/

/*********************电压合格率共108个字节，每页Flash 4092/108=37，12次采用奇偶页存储********104*********/
#define Vol_Per_Pass_Data_Len            108                                              /*电压合格率数据长度*/
#define FlashStAddr_Vol_Per_Pass         (FlashEndAddr_PFactorC_Over+C_OneFlashPage)      /*电压合格率Flash首页地址*/
#define FlashEndAddr_Vol_Per_Pass        (FlashStAddr_Vol_Per_Pass+C_OneFlashPage)        /*电压合格率Flash尾页地址*/

/*********************需量清零记录共202个字节，每页Flash 4092/202=20，10次采用奇偶页存储********106*********/
#define De_Clear_Data_Len                202                                              /*需量清零记录数据长度*/
#define FlashStAddr_De_Clear             (FlashEndAddr_Vol_Per_Pass+C_OneFlashPage)       /*需量清零记录Flash首页地址*/
#define FlashEndAddr_De_Clear            (FlashStAddr_De_Clear+C_OneFlashPage)            /*需量清零记录Flash尾页地址*/

/*********************合闸记录共34个字节，每页Flash 4092/34=120，10次采用奇偶页存储********108*********/
#define RelayClose_Data_Len              34                                               /*合闸记录数据长度*/
#define FlashStAddr_RelayClose           (FlashEndAddr_De_Clear+C_OneFlashPage)           /*合闸记录Flash首页地址*/
#define FlashEndAddr_RelayClose          (FlashStAddr_RelayClose+C_OneFlashPage)          /*合闸记录Flash尾页地址*/

/*********************编程记录共50个字节，每页Flash 4092/50=91，10次采用奇偶页存储**********110*******/
#define Program_Data_Len                 50                                               /*编程记录数据长度*/
#define FlashStAddr_Program              (FlashEndAddr_RelayClose+C_OneFlashPage)         /*编程记录Flash首页地址*/
#define FlashEndAddr_Program             (FlashStAddr_Program+C_OneFlashPage)             /*编程记录Flash尾页地址*/

/*********************校时记录共16个字节，每页Flash 4092/16=255，10次采用奇偶页存储**********112*******/
#define AdjTime_Data_Len                 CLAdjTime_Note_1                                 /*校时记录数据长度*/
#define FlashStAddr_AdjTime              (FlashEndAddr_Program+C_OneFlashPage)            /*校时记录Flash首页地址*/
#define FlashEndAddr_AdjTime             (FlashStAddr_AdjTime+C_OneFlashPage)             /*校时记录Flash尾页地址*/

/*********************广播校时记录共16个字节，每页Flash 4092/16=255，100次采用多页存储，防止超过12条清掉**********112*******/
#define BroadcastTime_Data_Len           CLBroadcastTime_Note_1                            /*广播校时记录数据长度*/
#define FlashStAddr_BroadcastTime        (FlashEndAddr_AdjTime+C_OneFlashPage)             /*广播校时记录Flash首页地址*/
#define FlashEndAddr_BroadcastTime       (FlashStAddr_BroadcastTime+C_OneFlashPage*2)      /*广播校时记录Flash尾页地址*/

/*********************时段表编程记录共65个字节，每页Flash 4092/65=62，10次采用多页,2页存储****116***************/
#define ProgPT_Data_Len                  CLProgPT_Note_1                                  /*时段表编程记录数据长度*/
#define FlashStAddr_ProgPT               (FlashEndAddr_BroadcastTime+C_OneFlashPage)      /*时段表编程记录Flash首页地址*/
#define FlashEndAddr_ProgPT              (FlashStAddr_ProgPT+C_OneFlashPage)              /*时段表编程记录Flash尾页地址*/

/*********************时区表编程记录共94个字节，每页Flash 4092/94=43，10次采用奇偶页存储*******118**********/
#define ProgTZ_Data_Len                  CLProgTZ_Note_1                                  /*时区表编程记录数据长度*/
#define FlashStAddr_ProgTZ               (FlashEndAddr_ProgPT+C_OneFlashPage)             /*时区表编程记录Flash首页地址*/
#define FlashEndAddr_ProgTZ              (FlashStAddr_ProgTZ+C_OneFlashPage)              /*时区表编程记录Flash尾页地址*/

/*********************周休日编程记录共11个字节，每页Flash 4092/11=372，10次采用奇偶页存储*******120**********/
#define ProgWRe_Data_Len                 CLProgWRe_Note_1                                 /*周休日编程记录数据长度*/
#define FlashStAddr_ProgWRe              (FlashEndAddr_ProgTZ+C_OneFlashPage)             /*周休日编程记录Flash首页地址*/
#define FlashEndAddr_ProgWRe             (FlashStAddr_ProgWRe+C_OneFlashPage)             /*周休日编程记录Flash尾页地址*/

/*********************节假日编程记录共1026个字节，每页Flash 4092/1026=3，10次采用多页,6页存储*****126**********/
#define ProgHol_Data_Len                 CLProgHol_Note_1                                 /*节假日编程记录数据长度*/
#define FlashStAddr_ProgHol              (FlashEndAddr_ProgWRe+C_OneFlashPage)            /*节假日编程记录Flash首页地址*/
#define FlashEndAddr_ProgHol             (FlashStAddr_ProgHol+C_OneFlashPage*5)           /*节假日编程记录Flash尾页地址*/

/*********************组合方式编程记录共11个字节，每页Flash 4092/11=372，10次采用奇偶页存储*******130**********/
#define ProgCom_Data_Len                 CLProgAcC_Note_1                                 /*组合方式编程记录数据长度*/
#define FlashStAddr_ProgAcC              (FlashEndAddr_ProgHol+C_OneFlashPage)            /*有功组合方式编程记录Flash首页地址*/
#define FlashEndAddr_ProgAcC             (FlashStAddr_ProgAcC+C_OneFlashPage)             /*有功组合方式编程记录Flash尾页地址*/

#define FlashStAddr_ProgReC1             (FlashEndAddr_ProgAcC+C_OneFlashPage)            /*无功组合方式1编程记录Flash首页地址*/
#define FlashEndAddr_ProgReC1            (FlashStAddr_ProgReC1+C_OneFlashPage)            /*无功组合方式1编程记录Flash尾页地址*/

/*********************结算日编程记录共16个字节，每页Flash 4092/16=255，10次采用奇偶页存储********132*********/
#define ProgSettD_Data_Len               CLProgSettD_Note_1                               /*结算日编程记录数据长度*/
#define FlashStAddr_ProgSettD            (FlashEndAddr_ProgReC1+C_OneFlashPage)           /*结算日编程记录Flash首页地址*/
#define FlashEndAddr_ProgSettD           (FlashStAddr_ProgSettD+C_OneFlashPage)           /*结算日编程记录Flash尾页地址*/

/*********************费率参数编程记录共42个字节，每页Flash 4092/42=97，10次采用奇偶页存储*******134**********/
#define ProgTPara_Data_Len               CLProgTPara_Note_1                               /*费率参数编程记录数据长度*/
#define FlashStAddr_ProgTPara            (FlashEndAddr_ProgSettD+C_OneFlashPage)          /*费率参数编程记录Flash首页地址*/
#define FlashEndAddr_ProgTPara           (FlashStAddr_ProgTPara+C_OneFlashPage)           /*费率参数编程记录Flash尾页地址*/

/*********************阶梯表编程记录共138个字节，每页Flash 4092/138=29，10次采用奇偶页存储*******136**********/
#define ProgLad_Data_Len                 CLProgLad_Note_1                                 /*阶梯表编程记录数据长度*/
#define FlashStAddr_ProgLad              (FlashEndAddr_ProgTPara+C_OneFlashPage)          /*阶梯表编程记录Flash首页地址*/
#define FlashEndAddr_ProgLad             (FlashStAddr_ProgLad+C_OneFlashPage)             /*阶梯表编程记录Flash尾页地址*/

/*********************密钥更新记录共15个字节，每页Flash 4092/15=272，10次采用奇偶页存储**********138*******/
#define ProgKD_Data_Len                  CLProgKD_Note_1                                  /*密钥更新数据长度*/
#define FlashStAddr_ProgKD               (FlashEndAddr_ProgLad+C_OneFlashPage)            /*密钥更新记录Flash首页地址*/
#define FlashEndAddr_ProgKD              (FlashStAddr_ProgKD+C_OneFlashPage)              /*密钥更新记录Flash尾页地址*/

/*********************异常插卡记录共36个字节，每页Flash 4092/36=113，10次采用奇偶页存储**********140*******/
#define AbnorC_Data_Len                  36                                               /*异常插卡记录数据长度*/
#define FlashStAddr_AbnorC               (FlashEndAddr_ProgKD+C_OneFlashPage)             /*异常插卡记录Flash首页地址*/
#define FlashEndAddr_AbnorC              (FlashStAddr_AbnorC+C_OneFlashPage)              /*异常插卡记录Flash尾页地址*/

/*********************开表盖记录共60个字节，每页Flash 4092/60=68，10次采用奇偶页存储***********142******/
#define OpenW_Data_Len                   60                                               /*开表盖记录数据长度*/
#define FlashStAddr_OpenW                (FlashEndAddr_AbnorC+C_OneFlashPage)             /*开表盖记录Flash首页地址*/
#define FlashEndAddr_OpenW               (FlashStAddr_OpenW+C_OneFlashPage)               /*开表盖记录Flash尾页地址*/

/*********************开端钮盖记录共60个字节，每页Flash 4092/60=68，10次采用奇偶页存储*********144********/
#define OpenCW_Data_Len                  60                                                 /*开端钮盖记录数据长度*/
#define FlashStAddr_OpenCW               (FlashEndAddr_OpenW+C_OneFlashPage)                /*开端钮盖记录Flash首页地址*/
#define FlashEndAddr_OpenCW              (FlashStAddr_OpenCW+C_OneFlashPage)                /*开端钮盖记录Flash尾页地址*/

/*********************购电记录共23个字节，每页Flash 4092/23=177，10次采用奇偶页存储************146*****/
#define BuyCurr_Data_Len                 23                                                 /*购电记录数据长度*/
#define FlashStAddr_BuyCurr              (FlashEndAddr_OpenCW+C_OneFlashPage)               /*购电记录Flash首页地址*/
#define FlashEndAddr_BuyCurr             (FlashStAddr_BuyCurr+C_OneFlashPage)               /*购电记录Flash尾页地址*/

/*********************退费记录共19个字节，每页Flash 4092/19=215，10次采用奇偶页存储**********148*******/
#define Return_M_Data_Len                19                                                 /*退费记录数据长度*/
#define FlashStAddr_Return_M             (FlashEndAddr_BuyCurr+C_OneFlashPage)              /*退费记录Flash首页地址*/
#define FlashEndAddr_Return_M            (FlashStAddr_Return_M+C_OneFlashPage)              /*退费记录Flash尾页地址*/

/*********************恒定磁场干扰记录共28个字节，每页Flash 4092/28=146，10次采用奇偶页存储*******150**********/
#define ConM_Data_Len                    28                                                 /*恒定磁场干扰记录数据长度*/
#define FlashStAddr_ConM                 (FlashEndAddr_Return_M+C_OneFlashPage)             /*恒定磁场干扰记录Flash首页地址*/
#define FlashEndAddr_ConM                (FlashStAddr_ConM+C_OneFlashPage)                  /*恒定磁场干扰记录Flash尾页地址*/

/*********************负荷开关误动作记录共29个字节，每页Flash 4092/29=141，10次采用奇偶页存储******152***********/
#define RelayFa_Data_Len                 29                                                 /*负荷开关误动作记录数据长度*/
#define FlashStAddr_RelayFa              (FlashEndAddr_ConM+C_OneFlashPage)                 /*负荷开关误动作记录Flash首页地址*/
#define FlashEndAddr_RelayFa             (FlashStAddr_RelayFa+C_OneFlashPage)                   /*负荷开关误动作记录Flash尾页地址*/

/*********************电源异常记录共20个字节，每页Flash 4092/20=204，10次采用奇偶页存储*********154********/
#define PowerFa_Data_Len                 20                                                 /*电源异常记录数据长度*/
#define FlashStAddr_PowerFa              (FlashEndAddr_RelayFa+C_OneFlashPage)              /*电源异常记录Flash首页地址*/
#define FlashEndAddr_PowerFa             (FlashStAddr_PowerFa+C_OneFlashPage)               /*电源异常记录Flash尾页地址*/

/*********************跳闸记录共34个字节，每页Flash 4092/34=120，目前698跳合闸记录默认数据同开盖记录，10次采用奇偶页存储*******156**********/
#define RelayOpen_Data_Len               34                                                 /*跳闸记录数据长度*/
#define FlashStAddr_RelayOpen            (FlashEndAddr_PowerFa+C_OneFlashPage)              /*跳闸记录Flash首页地址*/
#define FlashEndAddr_RelayOpen           (FlashStAddr_RelayOpen+C_OneFlashPage)             /*跳闸记录Flash尾页地址*/

/*********************校表编程共1022个字节，每页Flash 4092/1022=4，10次采用多页存储，5页********161*********/
#define Rec_Meter_Data_Len               1022                                               /*校表编程记录数据长度*/
#define FlashStAddr_Rec_Meter            (FlashEndAddr_RelayOpen+C_OneFlashPage)            /*校表编程记录Flash首页地址*/
#define FlashEndAddr_Rec_Meter           (FlashStAddr_Rec_Meter+C_OneFlashPage*4)           /*校表编程记录Flash尾页地址*/

/*********************事件清零记录共14个字节，每页Flash 4092/14=292，10次采用奇偶页存储*********163********/
#define Even_Clear_Data_Len              14                                                 /*事件清零记录数据长度*/
#define FlashStAddr_Even_Clear           (FlashEndAddr_Rec_Meter+C_OneFlashPage)            /*事件清零记录Flash首页地址*/
#define FlashEndAddr_Even_Clear          (FlashStAddr_Even_Clear+C_OneFlashPage)            /*事件清零记录Flash尾页地址*/

/**********************总清记录共106个字节，每页Flash 4092/106=38，10次采用奇偶页存储*********165******/
#define Tol_Clear_Data_Len               106                                                /*总清记录数据长度*/
#define FlashStAddr_Tol_Clear            (FlashEndAddr_Even_Clear+C_OneFlashPage)           /*总清记录Flash首页地址*/
#define FlashEndAddr_Tol_Clear           (FlashStAddr_Tol_Clear+C_OneFlashPage)             /*总清记录Flash尾页地址*/

/**********************计量芯片故障记录共106个字节，每页Flash 4092/106=38，10次采用奇偶页存储*********167******/
#define MeterFa_Data_Len                 106                                                /*计量芯片故障数据长度*/
#define FlashStAddr_MeterFa              (FlashEndAddr_Tol_Clear+C_OneFlashPage)            /*计量芯片故障记录Flash首页地址*/
#define FlashEndAddr_MeterFa             (FlashStAddr_MeterFa+C_OneFlashPage)               /*计量芯片故障记录Flash尾页地址*/

/**********************时钟故障记录共106个字节，每页Flash 4092/106=38，10次采用奇偶页存储*********169******/
#define ClockFa_Data_Len                 106                                                /*时钟故障数据长度*/
#define FlashStAddr_ClockFa              (FlashEndAddr_MeterFa+C_OneFlashPage)              /*时钟故障记录Flash首页地址*/
#define FlashEndAddr_ClockFa             (FlashStAddr_ClockFa+C_OneFlashPage)               /*时钟故障记录Flash尾页地址*/

/**********************零线电流异常记录共106个字节，每页Flash 4092/106=38，10次采用奇偶页存储*********169******/
#define CNeutralCurrentAbnormal_Data_Len       106                                                    /*零线电流异常数据长度*/
#define FlashStAddr_NeutralCurrentAbnormal     (FlashEndAddr_ClockFa+C_OneFlashPage)                  /*零线电流异常记录Flash首页地址*/
#define FlashEndAddr_NeutralCurrentAbnormal    (FlashStAddr_NeutralCurrentAbnormal+C_OneFlashPage)    /*零线电流异常记录Flash尾页地址*/

/*********************************冻结类，1.7修改为类似负荷记录存储方式，根据下发OAD存储(存储预留空间根据林洋建议表预留)**********************************/
/*********************定时冻结，对应698 分钟冻结，共109个字节，每页Flash 4092/109=37，96*365=35040次采用多页存储，947页***实际用947*1.3+2=1234页********/
#define T_Free_Data_Len                    269                                                     /*定时冻结记录数据长度*/
#define FlashStAddr_T_Free                 (FlashEndAddr_NeutralCurrentAbnormal+C_OneFlashPage)    /*定时冻结记录Flash首页地址*/
#define FlashEndAddr_T_Free                (FlashStAddr_T_Free+C_OneFlashPage*1233)                /*定时冻结记录Flash尾页地址*/
#define MinFreezeFlashTol                  1234
#define C_MinFreezeNeedNum                 96*365                                                  /*35040条,分钟冻结需要记录条数*/

/*********************瞬时冻结共390个字节，698记录默认表格同原645数据项，每页Flash 4092/390=10，3次为方便巡航程序12次统一，采用多页存储，3页*********702********/
#define I_Free_Data_Len                    269                                                /*瞬时冻结记录数据长度*/
#define FlashStAddr_I_Free                 (FlashEndAddr_T_Free+C_OneFlashPage)               /*瞬时冻结记录Flash首页地址*/
#define FlashEndAddr_I_Free                (FlashStAddr_I_Free+C_OneFlashPage*2)              /*瞬时冻结记录Flash尾页地址*/

/*********************整点冻结 对应698小时冻结，共13个字节，698记录17，每页Flash 4092/13=314，254次为方便巡航程序12次统一，采用多页存储，6页***708********/
#define H_Free_Data_Len                    13                                                 /*瞬时冻结记录数据长度*/
#define FlashStAddr_H_Free                 (FlashEndAddr_I_Free+C_OneFlashPage)               /*瞬时冻结记录Flash首页地址*/
#define FlashEndAddr_H_Free                (FlashStAddr_H_Free+C_OneFlashPage*5)              /*瞬时冻结记录Flash尾页地址*/

/*********************日冻结共873个字节，每页Flash 4092/873=4，365次采用多页存储，365*1.3/4=119+2页*****728*****/
#define D_Free_Data_Len                    377                                                /*日冻结记录数据长度*/
#define FlashStAddr_D_Free                 (FlashEndAddr_H_Free+C_OneFlashPage)               /*日冻结记录Flash首页地址*/
#define FlashEndAddr_D_Free                (FlashStAddr_D_Free+C_OneFlashPage*120)            /*日冻结记录Flash尾页地址*/

/*********************月冻结共914个字节，每页Flash 4092/914=4，24次采用多页存储，24*1.3/4=8+2页***************6*****734*****/
#define D_Free_Data_Len                    377                                                /*月冻结记录数据长度*/
#define FlashStAddr_M_Free                 (FlashEndAddr_D_Free+C_OneFlashPage)               /*月冻结记录Flash首页地址*/
#define FlashEndAddr_M_Free                (FlashStAddr_M_Free+C_OneFlashPage*9)              /*月冻结记录Flash尾页地址*/

/*********************2套时区表切换约定共269个字节，每页Flash 4092/269=15，2次采用奇偶页存储******4***738********/
#define TZ_Free_Data_Len                   269                                                /*2套时区表切换约定冻结记录数据长度*/
#define FlashStAddr_TZ_Free                (FlashEndAddr_M_Free+C_OneFlashPage)               /*2套时区表切换约定冻结记录Flash首页地址*/
#define FlashEndAddr_TZ_Free               (FlashStAddr_TZ_Free+C_OneFlashPage*3)             /*2套时区表切换约定冻结记录Flash尾页地址*/

/*********************2套日时段表切换约定冻结共269个字节，每页Flash 4092/269=15，2次采用奇偶页存储*******4**742********/
#define PT_Free_Data_Len                   269                                                /*2套日时段表切换约定冻结记录数据长度*/
#define FlashStAddr_PT_Free                (FlashEndAddr_TZ_Free+C_OneFlashPage)              /*2套日时段表切换约定冻结记录Flash首页地址*/
#define FlashEndAddr_PT_Free               (FlashStAddr_PT_Free+C_OneFlashPage*3)             /*2套日时段表切换约定冻结记录Flash尾页地址*/

/*********************2套费率电价切换约定冻结共269个字节，每页Flash 4092/269=15，2次采用奇偶页存储******4***746********/
#define R_Free_Data_Len                    269                                                /*2套费率电价切换约定冻结记录数据长度*/
#define FlashStAddr_R_Free                 (FlashEndAddr_PT_Free+C_OneFlashPage)              /*2套费率电价切换约定冻结记录Flash首页地址*/
#define FlashEndAddr_R_Free                (FlashStAddr_R_Free+C_OneFlashPage*3)              /*2套费率电价切换约定冻结记录Flash尾页地址*/

/**********************2套阶梯切换约定冻结共269个字节，每页Flash 4092/269=15，2次采用奇偶页存储*******4**750********/
#define L_Free_Data_Len                    269                                                /*2套阶梯切换约定冻结记录数据长度*/
#define FlashStAddr_L_Free                 (FlashEndAddr_R_Free+C_OneFlashPage)               /*2套阶梯切换约定冻结记录Flash首页地址*/
#define FlashEndAddr_L_Free                (FlashStAddr_L_Free+C_OneFlashPage*3)              /*2套阶梯切换约定冻结记录Flash尾页地址*/

/**********************年结算冻结698*******10**760*****后更改为阶梯结算冻结***/
#define FlashStAddr_Y_Free                 (FlashEndAddr_L_Free+C_OneFlashPage)               /*年结算冻结记录Flash首页地址*/
#define FlashEndAddr_Y_Free                (FlashStAddr_Y_Free+C_OneFlashPage*9)              /*年结算冻结记录Flash尾页地址*/

//*********************山东双协议新增,用于645协议中时段表、时区表编程记录**********************************************/
/*********************时段表编程记录共682个字节，每页Flash 4092/682=6，10次采用多页存储,4页*******************/
#define ProgPT_Data_CurrentPart_Len        CLProgPT_CurrentPart_Note_1                        /*时段表编程记录数据长度*/
#define FlashStAddr_CurrentPart_ProgPT     FlashEndAddr_Y_Free+C_OneFlashPage                 /*时段表编程记录Flash首页地址*/
#define FlashEndAddr_CurrentPart_ProgPT    FlashStAddr_CurrentPart_ProgPT+C_OneFlashPage*3    /*时段表编程记录Flash尾页地址*/

/*********************时区表编程记录共42个字节，每页Flash 4092/48=85，10次采用奇偶页存储*******118**********/
#define ProgTZ_Data_CurrentPart_Len        CLProgTZ_CurrentPart_Note_1                        /*时区表编程记录数据长度*/
#define FlashStAddr_CurrentPart_ProgTZ     FlashEndAddr_CurrentPart_ProgPT+C_OneFlashPage     /*时区表编程记录Flash首页地址*/
#define FlashEndAddr_CurrentPart_ProgTZ    FlashStAddr_CurrentPart_ProgTZ+C_OneFlashPage      /*时区表编程记录Flash尾页地址*/

/*********************645编程记录共50个字节，每页Flash 4092/50=91，10次采用奇偶页存储**********110*******/
#define Program_Data_Len_645               CLProgram_Note_1_645                               /*编程记录数据长度*/
#define FlashStAddr_Program_645            FlashEndAddr_CurrentPart_ProgTZ+C_OneFlashPage     /*编程记录Flash首页地址*/
#define FlashEndAddr_Program_645           FlashStAddr_Program_645+C_OneFlashPage             /*编程记录Flash尾页地址*/

/***********************内部变量定义*****************************/
#define C_CurrEnergy_Len           ((E2Addr_CurrEnergyRam_End-E2Addr_CurrEnergy_St)/(C_CRCLen2+C_CurrDataLen5))     /*当前电量类数据，长度*/
#define C_CurrEnergy_ByteLen       (C_CRCLen2+C_CurrDataLen5)
#define C_ChargeBal_offset_InGV    ((E2Addr_ChargeBal_Hex_Deal-E2Addr_CurrEnergy_St)/(C_CRCLen2+C_CurrDataLen5))    /*剩余金额在RAM中位置*/

#define C_698Free_Num                 11     /*目前698冻结，类别*/
#define C_698FreeData_SequenceLen4    4      /*冻结数据序号长度*/
#define C_698FreeData_DateLen6        7      /*冻结数据日期长度YMDhms*/

#define C_698Event_OADTabMaxNum       60     /*事件698关联序号表最大支持个数*/
#define C_698Event_OADTabDataType     2      /*事件698关联序号表数据格式，2个字节表示1个关联OAD*/

#define C_698Event_OADTabLen          (C_698Event_OADTabMaxNum*C_698Event_OADTabDataType)    /*事件698关联序号表*/
#define C_698Event_FixOADTabLen       10     /*事件698固定关联序号表，最大支持10个*/

/*数据层重要数据，放RAM绝对地址，具体空间分配在stm32l151xD.icf文件中定义，注意在工程配置中，option-linker-config中选定更改后.icf文件*/
uchar8 GV_CurrEnergyData[C_CurrEnergy_Len][C_CRCLen2+C_CurrDataLen5];    /*RAM 带CRC 当前电量类数据,与E2存储对应*/
uchar8 GV_CurrMVolPerPass[4][C_CRCLen2+CLVol_Per_Pass_M];                /*RAM 带CRC 当前电压合格率，总、ABC*/
uchar8 GV_Voltage_PassTime[C_CRCLen2+CLVol_PassTime_M];                /*RAM 带CRC 当前电压合格率电压合格时间*/

/************参变量*************/
uchar8 GV_Date_Time[CLDate_Week_Time];                                       /*ssmmhhwwDDMMYY*/
uchar8 GV_BroadcastTimeOffset_Min[CLBroadcastTimeOffset_Min+C_CRCLen2];      /*广播校时偏差最小值*/
uchar8 GV_BroadcastTimeOffset_Max[CLBroadcastTimeOffset_Max+C_CRCLen2];      /*广播校时偏差最大值*/

uchar8 GV_Demand_Cycle[CLDemand_Cycle+C_CRCLen2];                            /*最大需量周期带2 CRC*/
uchar8 GV_Sliding_Time[CLSliding_Time+C_CRCLen2];                            /*滑差时间带2 CRC*/

uchar8 GV_Change_TZ_Time[CLChange_TZ_Time+C_CRCLen2];                        /*两套时区表切换时间带2 CRC*/
uchar8 GV_Change_PT_Time[CLChange_PT_Time+C_CRCLen2];                        /*两套日时段表切换时间带2 CRC*/
uchar8 GV_Change_Rate[CLChange_Rate+C_CRCLen2];                              /*两套费率电价切换时间带2 CRC*/
uchar8 GV_Change_Ladder[CLChange_Ladder+C_CRCLen2];                          /*两套阶梯电价切换时间带2 CRC*/

uchar8 GV_Year_Zone_Num[CLYear_Zone_Num+C_CRCLen2];                          /*年时区数 带2 CRC*/
uchar8 GV_Day_Table_Num[CLDay_Table_Num+C_CRCLen2];                          /*日时段表数 带2 CRC*/
uchar8 GV_Day_Time_Num[CLDay_Time_Num+C_CRCLen2];                            /*日时段数 带2 CRC*/
uchar8 GV_Rate_Num[CLRate_Num+C_CRCLen2];                                    /*费率数 带2 CRC*/
uchar8 GV_Holiday_Num[CLHoliday_Num+C_CRCLen2];                              /*公共假日数 带2 CRC*/

uchar8 GV_Step_Num[CLStep_Num+C_CRCLen2];                                    /*阶梯数 带2 CRC*/
#if 0
uchar8 GV_Key_Tol_Num[CLKey_Tol_Num+C_CRCLen2];                              /*密钥总条数 带2 CRC*/
#endif

uchar8 GV_Per_Dis_Screen_Time[CLPer_Dis_Screen_Time+C_CRCLen2];              /*循显每屏显示时间*/
uchar8 GV_Auto_Dis_Screen_Num[CLAuto_Dis_Screen_Num+C_CRCLen2];              /*循显屏数*/
uchar8 GV_Auto_Dis_Screen_MaxNum[C_CRCLen2+CLAuto_Dis_Screen_MaxNum];        /*循显最大显示屏数*/

uchar8 GV_Perkey_Dis_Screen_Time[C_CRCLen2+CLPerkey_Dis_Screen_Time];        /*键显每屏显示时间*/
uchar8 GV_Key_CycDis_Screen_Num[CLKey_CycDis_Screen_Num+C_CRCLen2];          /*键显屏数*/
uchar8 GV_Key_CycDis_Screen_MaxNum[C_CRCLen2+CLKey_CycDis_Screen_MaxNum];    /*键显最大显示屏数*/

uchar8 GV_PowerOn_Dis_All_Time[CLPowerOn_Dis_All_Time+C_CRCLen2];    /*上电全显时间 带2 CRC*/
uchar8 GV_BacklightTime[CLBacklightTime+C_CRCLen2];                  /*背光点亮时间 带2 CRC*/
uchar8 GV_SViewBacklightTime[CLSViewBacklightTime+C_CRCLen2];        /*显示查看背光点亮时间 带2 CRC*/
uchar8 GV_NEScreenDisplay[CLNEScreenDisplay+C_CRCLen2];              /*无电按键屏幕驻留最大时间 带2 CRC*/
uchar8 GV_Energy_Decimal_Num[CLEnergy_Decimal_Num+C_CRCLen2];        /*电能小数位数 带2 CRC*/
uchar8 GV_Power_Decimal_Num[CLPower_Decimal_Num+C_CRCLen2];          /*显示功率（最大需量）小数位数 带2 CRC*/
uchar8 GV_1And2Display[CL1And2Display+C_CRCLen2];                    /*液晶①②字样意义,带2 CRC*/

uchar8 GV_Ratio_Curr_Tran[CLRatio_Curr_Tran+C_CRCLen2];              /*电流互感器变比 带2 CRC*/
uchar8 GV_Ratio_Vol_Tran[CLRatio_Vol_Tran+C_CRCLen2];                /*电压互感器变比 带2 CRC*/

uchar8 GV_Meter_Work_State[7][CLMeter_Work_State1];                  /*电表运行状态字1-7*/
uchar8 GV_Key_State[CLKey_State+C_CRCLen2];                          /*电表运行状态字8，密钥状态 带2 CRC*/
uchar8 GV_Active_Com_State[3][CLReactive_Com_State2+C_CRCLen2];      /*组合状态字,带2 CRC*/

uchar8 GV_Mod_InFr_Baud[CLMod_InFr_Baud+C_CRCLen2];                  /*调制式红外,带2 CRC*/
uchar8 GV_One485_Baud[CLOne485_Baud+C_CRCLen2];                      /*第1路485,带2 CRC*/
uchar8 GV_Two485_Baud[CLTwo485_Baud+C_CRCLen2];                      /*第2路485,带2 CRC*/
uchar8 GV_Modular_Baud[CLModular_Baud+C_CRCLen2];                    /*模块通道,带2 CRC*/

uchar8 GV_Week_RestDay[2][CLWeek_RestDay+C_CRCLen2];                 /*周休日特征字,带2 CRC*/

uchar8 GV_Alam1_Money[5][CLClose_Relay_Money+C_CRCLen2];             /*报警金额类限值,带2 CRC*/

uchar8 GV_Meter_Work_Char1[CLMeter_Work_Char1+C_CRCLen2];            /*电表运行特征字1,带2 CRC*/

uchar8 GV_Comm_Address[CLComm_Address+C_CRCLen2];                    /*通信地址CRC,带2 CRC*/

uchar8 GV_GPS_Signal[CLGPS_Signal];                                        /*无线通讯在线级信号强弱指示*/
//uchar8 GV_Relay_Delay_Time[CLRelay_Delay_Time+C_CRCLen2];                /*跳闸延时时间,带2 CRC*/
uchar8 GV_Relay_Open_CurrTreshold[CLRelay_Open_CurrTreshold+C_CRCLen2];    /*继电器拉闸控制电流门限值,带2 CRC*/
uchar8 GV_Inset_Card_State[CLInset_Card_State];                            /*插卡状态字*/

uchar8 GV_Current_Rate_Price[C_MaxRatesNum][CLCurrent_Rate12_Price+C_CRCLen2];    /*当前费率1-12电价,带2 CRC*/
uchar8 GV_BackUp_Rate_Price[C_MaxRatesNum][CLBackUp_Rate12_Price+C_CRCLen2];      /*备用套费率1-12电价,带2 CRC*/
uchar8 GV_Current_Ladder_Table[CLCurrent_Ladder_Table+C_CRCLen2];                 /*当前套阶梯表,带2 CRC*/
uchar8 GV_BackUp_Ladder_Table[CLBackUp_Ladder_Table+C_CRCLen2];                   /*备用套阶梯表,带2 CRC*/

uchar8 GV_LossVolage_Vol_UpLim[CLLossVolage_Vol_UpLim+C_CRCLen2];          /*失压事件电压触发上限,带2 CRC*/
uchar8 GV_LossVolage_Vol_LowLim[CLLossVolage_Vol_LowLim+C_CRCLen2];        /*失压事件电压恢复下限,带2 CRC*/
uchar8 GV_LossVolage_Curr_LowLim[CLLossVolage_Curr_LowLim+C_CRCLen2];      /*失压事件电流触发上限,带2 CRC*/
uchar8 GV_LossVolage_Delay_T[CLLossVolage_Delay_T+C_CRCLen2];              /*失压事件判断延时时间,带2 CRC*/

uchar8 GV_LowVolage_Vol_UpLim[CLLowVolage_Vol_UpLim+C_CRCLen2];            /*欠压事件电压触发上限,带2 CRC*/
uchar8 GV_LowVolage_Delay_T[CLLowVolage_Delay_T+C_CRCLen2];                /*欠压事件判断延时时间,带2 CRC*/

uchar8 GV_OverVolage_Vol_LowLim[CLOverVolage_Vol_LowLim+C_CRCLen2];        /*过压事件电压触发下限,带2 CRC*/
uchar8 GV_OverVolage_Delay_T[CLOverVolage_Delay_T+C_CRCLen2];              /*过压时间判断延时时间,带2 CRC*/

uchar8 GV_BreakVol_Vol_UpLim[CLBreakVol_Vol_UpLim+C_CRCLen2];              /*断相事件电压触发上限,带2 CRC*/
uchar8 GV_BreakVol_Curr_UpLim[CLBreakVol_Curr_UpLim+C_CRCLen2];            /*断相事件电流触发上线,带2 CRC*/
uchar8 GV_BreakVol_Delay_T[CLBreakVol_Delay_T+C_CRCLen2];                  /*断相事件判定延时时间,带2 CRC*/

uchar8 GV_NoBal_Vol_Lim[CLNoBal_Vol_Lim+C_CRCLen2];                        /*电压不平衡率限值,带2 CRC*/
uchar8 GV_NoBal_Vol_Delay_T[CLNoBal_Vol_Delay_T+C_CRCLen2];                /*电压不平衡率判定延时时间,带2 CRC*/

uchar8 GV_NoBal_Curr_Lim[CLNoBal_Curr_Lim+C_CRCLen2];                      /*电流不平衡率限值,带2 CRC*/
uchar8 GV_NoBal_Curr_Delay_T[CLNoBal_Curr_Delay_T+C_CRCLen2];              /*电流不平衡率判定延时时间,带2 CRC*/

uchar8 GV_SeriNoBal_Curr_Lim[CLSeriNoBal_Curr_Lim+C_CRCLen2];              /*电流严重不平衡率限值,带2 CRC*/
uchar8 GV_SeriNoBal_Curr_Delay_T[CLSeriNoBal_Curr_Delay_T+C_CRCLen2];      /*电流严重不平衡率判定延时时间,带2 CRC*/

uchar8 GV_LossCurr_Vol_LowLim[CLLossCurr_Vol_LowLim+C_CRCLen2];            /*失流事件电压触发下限,带2 CRC*/
uchar8 GV_LossCurr_Curr_UpLim[CLLossCurr_Curr_UpLim+C_CRCLen2];            /*失流事件电流触发上限,带2 CRC*/
uchar8 GV_LossCurr_Curr_LowLim[CLLossCurr_Curr_LowLim+C_CRCLen2];          /*失流事件电流触发下限,带2 CRC*/
uchar8 GV_LossCurr_Delay_T[CLLossCurr_Delay_T+C_CRCLen2];                  /*失流事件判定延时时间,带2 CRC*/

uchar8 GV_OverCurr_Curr_LowLim[CLOverCurr_Curr_LowLim+C_CRCLen2];          /*过流事件电流触发下限 ,带2 CRC*/
uchar8 GV_OverCurr_Delay_T[CLOverCurr_Delay_T+C_CRCLen2];                  /*过流事件判断延时时间 ,带2 CRC*/

uchar8 GV_BreakCurr_Vol_LowLim[CLBreakCurr_Vol_LowLim+C_CRCLen2];          /*断流事件电压触发下限 ,带2 CRC*/
uchar8 GV_BreakCurr_Curr_UpLim[CLBreakCurr_Curr_UpLim+C_CRCLen2];          /*断流事件电流触发上限 ,带2 CRC*/
uchar8 GV_BreakCurr_Delay_T[CLBreakCurr_Delay_T+C_CRCLen2];                /*断流事件判定延时时间 ,带2 CRC*/

uchar8 GV_OverLoad_AcPower_LowLim[CLOverLoad_AcPower_LowLim+C_CRCLen2];    /*过载事件有功功率触发下限 ,带2 CRC*/
uchar8 GV_OverLoad_Delay_T[CLOverLoad_Delay_T+C_CRCLen2];                  /*过载事件判定延时时间,带2 CRC*/

uchar8 GV_PosAcDemandOv_De_LowLim[CLPosAcDemandOv_De_LowLim+C_CRCLen2];    /*正向有功需量超限事件需量触发下限,带2 CRC*/
uchar8 GV_PosAcDemandOv_Delay_T[CLPosAcDemandOv_Delay_T+C_CRCLen2];        /*正向有功需量超限事件判定延时时间,带2 CRC*/

uchar8 GV_RevAcDemandOv_De_LowLim[CLRevAcDemandOv_De_LowLim+C_CRCLen2];    /*反向有功需量超限事件需量触发下限,带2 CRC*/
uchar8 GV_RevAcDemandOv_Delay_T[CLRevAcDemandOv_Delay_T+C_CRCLen2];        /*反向有需量超限事件判定延时时间,带2 CRC*/

uchar8 GV_ReDemandOv_De_LowLim[CLReDemandOv_De_LowLim+C_CRCLen2];          /*无功需量超限事件需量触发下限,带2 CRC*/
uchar8 GV_ReDemandOv_Delay_T[CLReDemandOv_Delay_T+C_CRCLen2];              /*无功需量超限事件判定延时时间,带2 CRC*/

uchar8 GV_PowerFactor_LowLim[CLPowerFactor_LowLim+C_CRCLen2];              /*功率因数超下限阀值,带2 CRC*/
uchar8 GV_PowerFactor_Delay_T[CLPowerFactor_Delay_T+C_CRCLen2];            /*功率因素超下限判定延时时间,带2 CRC*/

uchar8 GV_PowerRev_AcPower_LowLim[CLPowerRev_AcPower_LowLim+C_CRCLen2];    /*功率反向事件有功功率触发下限,带2 CRC*/
uchar8 GV_PowerRev_Delay_T[CLPowerRev_Delay_T+C_CRCLen2];                  /*功率反向事件判定延时时间,带2 CRC*/

uchar8 GV_NeutralUnbalanceRate[CLNeutralUnbalanceRate+C_CRCLen2];                  /*零线电流异常不平衡率限值*/
uchar8 GV_NeutralAbnormal_Curr_LowLim[CLNeutralAbnormal_Curr_LowLim+C_CRCLen2];    /*零线电流异常电流触发下限*/
uchar8 GV_NeutralAbnormal_Delay_T[CLNeutralAbnormal_Delay_T+C_CRCLen2];            /*零线电流异常判定延迟时间*/

uchar8 GV_ReversedVoltage_Delay_T[CLReversedVoltage_Delay_T+C_CRCLen2];            /*电压逆相序事件判定延时时间*/
uchar8 GV_ReversedCurrent_Delay_T[CLReversedCurrent_Delay_T+C_CRCLen2];            /*电流逆相序事件判定延时时间*/
uchar8 GV_PowerOff_Delay_T[CLPowerOff_Delay_T+C_CRCLen2];                          /*掉电事件判定延时时间*/
uchar8 GV_Aux_Pow_Down_Delay_T[CLAux_Pow_Down_Delay_T+C_CRCLen2];                  /*辅助电源掉电判定延时时间*/
uchar8 GV_ClockFa_Delay_T[CLClockFa_Delay_T+C_CRCLen2];                            /*时钟故障判定延时时间*/
uchar8 GV_MeterFa_Delay_T[CLMeterFa_Delay_T+C_CRCLen2];                            /*计量芯片故障判定延时时间*/

uchar8 GV_Voltage_UpLim[CLVoltage_UpLim+C_CRCLen2];                  /*电压上限值,带2 CRC*/
uchar8 GV_Voltage_LowLim[CLVoltage_LowLim+C_CRCLen2];                /*电压下限值,带2 CRC*/
uchar8 GV_Volage_Check_UpLim[2][CLVolage_Check_LowLim+C_CRCLen2];    /*电压考核,带2 CRC*/

uchar8 GV_Volage_Type[8][CLVolage_Type+C_CRCLen2];                   /*电压类型等设置参数,带2 CRC*/
uchar8 GV_Start_Up_Current[CLStart_Up_Current+C_CRCLen2];            /*电流瞬时量阀值,带2 CRC*/
uchar8 GV_Start_Up_Power[CLStart_Up_Power+C_CRCLen2];                /*功率瞬时量阀值,带2 CRC*/
uchar8 GV_Volage_Abnor_Vol[CLVolage_Abnor_Vol+C_CRCLen2];            /*电压异常判断电压,带2 CRC*/
uchar8 GV_Loss_Volage_Curr[5][CLLoss_Volage_Curr+C_CRCLen2];         /*全失压电流等相关参数,带2 CRC*/
uchar8 GV_Pluse_Most__Lim[CLPluse_Most__Lim+C_CRCLen2];              /*从计量芯片读出的脉冲最大阀值,带2 CRC*/
uchar8 GV_Curr_Ratio_30A[CLCurr_Ratio_30A+C_CRCLen2];                /*校表30A对应的相应电流规格系数,带2 CRC*/
uchar8 GV_Pulse_Constant[CLPulse_Constant+C_CRCLen2];                /*脉冲常数,带2 CRC*/
uchar8 GV_SoftIJ_Valid_Time[CLSoftIJ_Valid_Time+C_CRCLen2];          /*软IJ有效时间,带2 CRC*/
uchar8 GV_Extern_Relay_PulW[CLExtern_Relay_PulW+C_CRCLen2];          /*外置继电器脉冲宽度,带2 CRC*/
uchar8 GV_MeterRunStatic[CLMeterRunStatic+C_CRCLen2];                /*当前运行在第几套时区表、时段表。时区表在前（低地址）,带2 CRC*/
uchar8 GV_HardError_State[CLHardError_State];                        /*硬件故障运行状态字*/
uchar8 GV_Alarm_Status[CLAlarm_Status+C_CRCLen2];                    /*报警模式字,带2 CRC*/
uchar8 GV_RTC_AdjustTemp[CLRTC_AdjustTemp+C_CRCLen2];                /*RTC校准温度值8+2*/
uchar8 GV_Cap_Vol[CLCap_Vol+C_CRCLen2];                              /*超级电容电压,带2 CRC*/

uchar8 GV_PhaseA_Volage[3][CLPhaseC_Volage];                         /*电压数据*/
uchar8 GV_PhaseA_Curr[3][CLPhaseC_Curr];                             /*电流数据*/
uchar8 GV_Instant_TolAcPow[4][CLInstantC_AcPow];                     /*瞬时有功功率数据*/
uchar8 GV_Instant_TolRePow[4][CLInstantC_RePow];                     /*瞬时无功功率数据*/
uchar8 GV_Instant_TolAppaPow[4][CLInstantC_AppaPow];                 /*瞬时视在功率数据*/
uchar8 GV_Tol_PowerFactor[4][CLPhaseC_PowerFactor];                  /*功率因数数据*/
uchar8 GV_PhaseA_Angle[3][CLPhaseC_Angle];                           /*相角数据*/
uchar8 GV_Vector_Current[CLVector_Current];                          /*三相电流矢量和*/
uchar8 GV_Zero_Current[CLZero_Current];                              /*零线电流*/
uchar8 GV_ElecNet_Freq[CLElecNet_Freq];                              /*电网频率*/
uchar8 GV_OneMin_AcPower[4][CLOneMin_AcPower];                       /*1分钟有功平均功率，总ABC*/
uchar8 GV_OneMin_RePower[4][CLOneMin_RePower];                       /*1分钟无功平均功率，总ABC*/
uchar8 GV_Curr_AcDemand[CLCurr_AcDemand];                            /*当前有功需量*/
uchar8 GV_Curr_ReDemand[CLCurr_ReDemand];                            /*当前无功需量*/
//uchar8 GV_Curr_AppaDemand[CLCurr_AppaDemand];                      /*当前视在需量*/
uchar8 GV_Meter_Temp[CLMeter_Temp];                                  /*表内温度*/
uchar8 GV_Cloc_Batt_Vol[CLCloc_Batt_Vol];                            /*时钟电池电压*/
uchar8 GV_ReadMeter_Batt_Vol[CLReadMeter_Batt_Vol];                  /*抄表电池电压*/
uchar8 GV_Batt_Work_Time[CLBatt_Work_Time+C_CRCLen2];                /*内部电池工作时间  ,带2 CRC*/
uchar8 GV_Curr_Ladder_Price[CLCurr_Ladder_Price];                    /*当前阶梯电价*/
uchar8 GV_Curr_Price[CLCurr_Price];                                  /*当前电价*/
uchar8 GV_Curr_Rate_Price[CLCurr_Rate_Price+C_CRCLen2];              /*当前费率电价,带2 CRC*/
uchar8 GV_ID_Auth_Remain_Time[CLID_Auth_Remain_Time];                /*身份认证时效剩余时间*/
uchar8 GV_ID_Auth_T_Remain_Time[CLInfra_Auth_Remain_Time];           /*终端身份认证时效剩余时间*/
uchar8 GV_ID_Auth_Remain_Time_645[CLID_Auth_Remain_Time_645];        /*645身份认证时效剩余时间(698兼容645)*/
uchar8 GV_Infra_Auth_Remain_Time[CLInfra_Auth_Remain_Time];          /*红外认证时效剩余时间*/
uchar8 GV_Infra_Auth_Remain_Time_645[CLInfra_Auth_Remain_Time_645];  /*645红外认证时效剩余时间(698兼容645)*/

uchar8 GV_SoftI_J_RemainTime[CLSoftI_J_RemainTime];                  /*软IJ有效剩余时间*/
uchar8 GV_CurrMon_Vol_Pass_Time[CLCurrMon_Vol_Pass_Time];            /*本月总电压合格时间*/
uchar8 GV_Curr_Rate_No[CLCurr_Rate_No];                              /*当前费率号*/
uchar8 GV_Curr_Step_No[CLCurr_Step_No];                              /*当前阶梯号*/
uchar8 GV_CurrA_Phase[3][CLCurrC_Phase];                             /*电流相角*/
uchar8 GV_VolA_Phase[3][CLVolC_Phase];                               /*电压相角*/
uchar8 GV_PhaseA_Curr_4Dig[3][CLPhaseC_Curr_4Dig];                   /*电流,4位小数*/
uchar8 GV_Rst_ReportState_Timer[CLRst_ReportState_Timer+C_CRCLen2];  /*主动上报自动复位时间 带2 CRC*/
uchar8 GV_Relay_Open_CurrTimer[CLRelay_Open_CurrTimer+C_CRCLen2];    /*拉闸控制电流门限保护延时时间  带2 CRC*/
uchar8 GV__IRAuth_Timer[CL_IRAuth_Timer+C_CRCLen2];                  /*红外认证时效  带2 CRC*/
uchar8 GV_Relay_RemoteOrder[CLRelay_RemoteOrder+C_CRCLen2];          /*远程控制命令  带2 CRC*/
uchar8 GV_Relay_State[CLRelay_State+C_CRCLen2];                      /*继电器状态  带2 CRC*/
uchar8 GV_Relay_LocalOrder[CLRelay_LocalOrder+C_CRCLen2];            /*本地控制命令 带2 CRC*/
uchar8 GV_Remote_Local_State[CLRemote_Local_State+C_CRCLen2];        /*远程、本地开户状态 带2 CRC*/
uchar8 GV_Drive_Report_Mode[CLDrive_Report_Mode+C_CRCLen2];          /*主动上报模式字 带2 CRC*/

uchar8 GV_AppProInformation[CLAppProInformation+C_CRCLen2];          /*协议版本信息 带2 CRC*/
uchar8 GV_AppMaxReAPDU[CLAppMaxReAPDU+C_CRCLen2];                    /*最大接收APDU尺寸 带2 CRC*/
uchar8 GV_AppMaxSeAPDU[CLAppMaxSeAPDU+C_CRCLen2];                    /*最大发送APDU尺寸 带2 CRC*/
uchar8 GV_AppMaxHandleAPDU[CLAppMaxHandleAPDU+C_CRCLen2];            /*最大可处理APDU尺寸 带2 CRC*/
uchar8 GV_AppProConsistency[CLAppProConsistency+C_CRCLen2];          /*协议一致性块 带2 CRC*/
uchar8 GV_AppFunConsistency[CLAppFunConsistency+C_CRCLen2];          /*功能一致性块 带2 CRC*/
uchar8 GV_AppStaticTimeout[CLAppStaticTimeout+C_CRCLen2];            /*静态超时时间 带2 CRC*/

uchar8 GV_AppStaticTimeout_terminal[CLAppStaticTimeout+C_CRCLen2];   /*终端静态超时时间 带2 CRC*/

uchar8 GV_ConAutheMechanism[CLConAutheMechanism+C_CRCLen2];          /*连接认证机制 带2 CRC*/
uchar8 GV_SafeModePara[CLSafeModePara+C_CRCLen2];                    /*安全模式参数 带2 CRC*/

uchar8 GV_LoadWriteNum[CLLoadWriteNum+C_CRCLen2];                             /*负荷记录次数*/
uchar8 GV_Free_OADTab[C_698Free_Num][C_698Free_OADTabLen+C_CRCLen2];          /*698 OAD序号表*/
uchar8 GV_Free_OADTabLen_T[C_698Free_Num][CLI_Free_OADTabLen_T+C_CRCLen2];    /*698 OAD序号表长度及周期*/
uchar8 GV_Free_StartTime[3][CLD_Free_StartTime+C_CRCLen2];                    /*698 冻结起始日期时间*/

uchar8 GV_CurrDVolPerPass[4][C_CRCLen2+CLVol_Per_Pass_D];				/*RAM 带CRC 当前日电压合格率，总ABC*/

#if 0
uchar8 GV_Voltage_PassTime_D[C_CRCLen2+CLVol_PassTime_D];				/*RAM 带CRC 当前日电压合格率电压合格时间*/
#endif

uchar8 GV_LossVolage_Report_Mode[C_CRCLen2+CLReport_Mode];				/*失压上报模式字*/
uchar8 GV_LowVolage_Report_Mode[C_CRCLen2+CLReport_Mode];				/*欠压上报模式字*/
uchar8 GV_OverVolage_Report_Mode[C_CRCLen2+CLReport_Mode];				/*过压上报模式字*/
uchar8 GV_BreakVol_Report_Mode[C_CRCLen2+CLReport_Mode];				/*断相上报模式字*/
uchar8 GV_LossCurr_Report_Mode[C_CRCLen2+CLReport_Mode];				/*失流上报模式字*/
uchar8 GV_OverCurr_Report_Mode[C_CRCLen2+CLReport_Mode];				/*过流上报模式字*/
uchar8 GV_BreakCurr_Report_Mode[C_CRCLen2+CLReport_Mode];				/*断流上报模式字*/
uchar8 GV_PowerRev_Report_Mode[C_CRCLen2+CLReport_Mode];				/*功率反向上报模式字*/
uchar8 GV_OverLoad_Report_Mode[C_CRCLen2+CLReport_Mode];				/*过载上报模式字*/
uchar8 GV_PosAcDemandOv_Report_Mode[C_CRCLen2+CLReport_Mode];			/*正向有功需量超限事件上报模式字*/
uchar8 GV_RevAcDemandOv_Report_Mode[C_CRCLen2+CLReport_Mode];			/*反向有功需量超限事件上报模式字*/
uchar8 GV_ReDemandOv_Report_Mode[C_CRCLen2+CLReport_Mode];				/*无功需量超限事件上报模式字*/
uchar8 GV_PowerFactor_Report_Mode[C_CRCLen2+CLReport_Mode];				/*功率因数超下限事件上报模式字*/
uchar8 GV_AllLossVolage_Report_Mode[C_CRCLen2+CLReport_Mode];			/*全失压上报模式字*/
uchar8 GV_AuxPowDown_Report_Mode[C_CRCLen2+CLReport_Mode];				/*辅助电源失电上报模式字*/
uchar8 GV_ReversedVoltage_Report_Mode[C_CRCLen2+CLReport_Mode];			/*电压逆相序上报模式字*/
uchar8 GV_ReversedCurrent_Report_Mode[C_CRCLen2+CLReport_Mode];			/*电流逆相序上报模式字*/
uchar8 GV_PowerOff_Report_Mode[C_CRCLen2+CLReport_Mode];				/*掉电上报模式字*/
uchar8 GV_Program_Report_Mode[C_CRCLen2+CLReport_Mode];					/*编程上报模式字*/
uchar8 GV_TolClear_Report_Mode[C_CRCLen2+CLReport_Mode];				/*电表清零上报模式字*/
uchar8 GV_DemandClear_Report_Mode[C_CRCLen2+CLReport_Mode];				/*需量清零上报模式字*/
uchar8 GV_EventClear_Report_Mode[C_CRCLen2+CLReport_Mode];				/*事件清零上报模式字*/
uchar8 GV_AdjTime_Report_Mode [C_CRCLen2+CLReport_Mode];				/*校时上报模式字*/
uchar8 GV_BroadcastTime_Report_Mode [C_CRCLen2+CLReport_Mode];			/*广播校时上报模式字*/
uchar8 GV_ProgPT_Report_Mode[C_CRCLen2+CLReport_Mode];					/*时段表编程上报模式字*/
uchar8 GV_ProgPZ_Report_Mode[C_CRCLen2+CLReport_Mode];					/*时区表编程上报模式字*/
uchar8 GV_ProgWRe_Report_Mode[C_CRCLen2+CLReport_Mode];					/*周休日编程上报模式字*/
uchar8 GV_ProgSettD_Report_Mode[C_CRCLen2+CLReport_Mode];				/*结算日编程上报模式字*/
uchar8 GV_OpenW_Report_Mode[C_CRCLen2+CLReport_Mode];					/*开表盖上报模式字*/
uchar8 GV_OpenCW_Report_Mode[C_CRCLen2+CLReport_Mode];					/*开端钮盖上报模式字*/
uchar8 GV_NoBalVol_Report_Mode[C_CRCLen2+CLReport_Mode];				/*电压不平衡上报模式字*/
uchar8 GV_NoBalCurr_Report_Mode[C_CRCLen2+CLReport_Mode];				/*电流不平衡上报模式字*/
uchar8 GV_RelayOpen_Report_Mode[C_CRCLen2+CLReport_Mode];				/*跳闸上报模式字*/
uchar8 GV_RelayClose_Report_Mode[C_CRCLen2+CLReport_Mode];				/*合闸上报模式字*/
uchar8 GV_ProgHol_Report_Mode[C_CRCLen2+CLReport_Mode];					/*节假日编程上报模式字*/
uchar8 GV_ProgAcC_Report_Mode[C_CRCLen2+CLReport_Mode];					/*有功组合方式编程上报模式字*/
uchar8 GV_ProgReC_Report_Mode[C_CRCLen2+CLReport_Mode];					/*无功组合方式编程上报模式字*/
uchar8 GV_ProgTPara_Report_Mode[C_CRCLen2+CLReport_Mode];				/*费率参数表编程上报模式字*/
uchar8 GV_ProgLad_Report_Mode[C_CRCLen2+CLReport_Mode];					/*阶梯表编程上报模式字*/
uchar8 GV_Key_Update_Report_Mode[C_CRCLen2+CLReport_Mode];				/*密钥更新上报模式字*/
uchar8 GV_AbnorC_Report_Mode[C_CRCLen2+CLReport_Mode];					/*异常插卡上报模式字*/
uchar8 GV_BuyCurr_Report_Mode[C_CRCLen2+CLReport_Mode];					/*购电上报模式字*/
uchar8 GV_ReturnMoney_Report_Mode[C_CRCLen2+CLReport_Mode];				/*退费上报模式字*/
uchar8 GV_ConMEndEn_Report_Mode[C_CRCLen2+CLReport_Mode];				/*恒定磁场干扰上报模式字*/
uchar8 GV_RelayFaEndEn_Report_Mode[C_CRCLen2+CLReport_Mode];			/*负荷开关误动作上报模式字*/
uchar8 GV_PowerFa_EndT_Report_Mode[C_CRCLen2+CLReport_Mode];			/*电源异常上报模式字*/
uchar8 GV_SeriNoBalCurr_Report_Mode[C_CRCLen2+CLReport_Mode];			/*电流严重不平衡上报模式字*/
uchar8 GV_ClockFault_Report_Mode[C_CRCLen2+CLReport_Mode];				/*时钟故障上报模式字*/
uchar8 GV_MeteringChipFault_Report_Mode[C_CRCLen2+CLReport_Mode];		/*计量芯片故障上报模式字*/
uchar8 GV_ABnor_ZeroCurrent_Report_Mode[C_CRCLen2+CLABnor_ZeroCurrent_Report_Mode];		/*零线电流异常上报模式字*/

uchar8 GV_LossVolage_Report_Type[C_CRCLen2+CLReport_Type];					/*失压上报方式*/
uchar8 GV_LowVolage_Report_Type[C_CRCLen2+CLReport_Type];					/*欠压上报方式*/
uchar8 GV_OverVolage_Report_Type[C_CRCLen2+CLReport_Type];					/*过压上报方式*/
uchar8 GV_BreakVol_Report_Type[C_CRCLen2+CLReport_Type];					/*断相上报方式*/
uchar8 GV_LossCurr_Report_Type[C_CRCLen2+CLReport_Type];					/*失流上报方式*/
uchar8 GV_OverCurr_Report_Type[C_CRCLen2+CLReport_Type];					/*过流上报方式*/
uchar8 GV_BreakCurr_Report_Type[C_CRCLen2+CLReport_Type];					/*断流上报方式*/
uchar8 GV_PowerRev_Report_Type[C_CRCLen2+CLReport_Type];					/*功率反向上报方式*/
uchar8 GV_OverLoad_Report_Type[C_CRCLen2+CLReport_Type];					/*过载上报方式*/
uchar8 GV_PosAcDemandOv_Report_Type[C_CRCLen2+CLReport_Type];				/*正向有功需量超限事件上报方式*/  //
uchar8 GV_RevAcDemandOv_Report_Type[C_CRCLen2+CLReport_Type];				/*反向有功需量超限事件上报方式*/  //
uchar8 GV_ReDemandOv_Report_Type[C_CRCLen2+CLReport_Type];					/*无功需量超限事件上报方式*/
uchar8 GV_PowerFactor_Report_Type[C_CRCLen2+CLReport_Type];					/*功率因数超下限事件上报方式*/
uchar8 GV_AllLossVolage_Report_Type[C_CRCLen2+CLReport_Type];				/*全失压上报方式*/
uchar8 GV_AuxPowDown_Report_Type[C_CRCLen2+CLReport_Type];					/*辅助电源失电上报方式*/
uchar8 GV_ReversedVoltage_Report_Type[C_CRCLen2+CLReport_Type];				/*电压逆相序上报方式*/
uchar8 GV_ReversedCurrent_Report_Type[C_CRCLen2+CLReport_Type];				/*电流逆相序上报方式*/
uchar8 GV_PowerOff_Report_Type[C_CRCLen2+CLReport_Type];					/*掉电上报方式*/
uchar8 GV_Program_Report_Type[C_CRCLen2+CLReport_Type];						/*编程上报方式*/
uchar8 GV_TolClear_Report_Type[C_CRCLen2+CLReport_Type];					/*电表清零上报方式*/
uchar8 GV_DemandClear_Report_Type[C_CRCLen2+CLReport_Type];					/*需量清零上报方式*/
uchar8 GV_EventClear_Report_Type[C_CRCLen2+CLReport_Type];					/*事件清零上报方式*/
uchar8 GV_AdjTime_Report_Type [C_CRCLen2+CLReport_Type];					/*校时上报方式*/
uchar8 GV_BroadcastTime_Report_Type [C_CRCLen2+CLReport_Type];				/*广播校时上报方式*/
uchar8 GV_ProgPT_Report_Type[C_CRCLen2+CLReport_Type];						/*时段表编程上报方式*/
uchar8 GV_ProgPZ_Report_Type[C_CRCLen2+CLReport_Type];						/*时区表编程上报方式*/
uchar8 GV_ProgWRe_Report_Type[C_CRCLen2+CLReport_Type];						/*周休日编程上报方式*/
uchar8 GV_ProgSettD_Report_Type[C_CRCLen2+CLReport_Type];					/*结算日编程上报方式*/
uchar8 GV_OpenW_Report_Type[C_CRCLen2+CLReport_Type];						/*开表盖上报方式*/
uchar8 GV_OpenCW_Report_Type[C_CRCLen2+CLReport_Type];						/*开端钮盖上报方式*/
uchar8 GV_NoBalVol_Report_Type[C_CRCLen2+CLReport_Type];					/*电压不平衡上报方式*/
uchar8 GV_NoBalCurr_Report_Type[C_CRCLen2+CLReport_Type];					/*电流不平衡上报方式*/
uchar8 GV_RelayOpen_Report_Type[C_CRCLen2+CLReport_Type];					/*跳闸上报方式*/
uchar8 GV_RelayClose_Report_Type[C_CRCLen2+CLReport_Type];					/*合闸上报方式*/
uchar8 GV_ProgHol_Report_Type[C_CRCLen2+CLReport_Type];						/*节假日编程上报方式*/
uchar8 GV_ProgAcC_Report_Type[C_CRCLen2+CLReport_Type];						/*有功组合方式编程上报方式*/
uchar8 GV_ProgReC_Report_Type[C_CRCLen2+CLReport_Type];						/*无功组合方式编程上报方式*/
uchar8 GV_ProgTPara_Report_Type[C_CRCLen2+CLReport_Type];					/*费率参数表编程上报方式*/
uchar8 GV_ProgLad_Report_Type[C_CRCLen2+CLReport_Type];						/*阶梯表编程上报方式*/
uchar8 GV_Key_Update_Report_Type[C_CRCLen2+CLReport_Type];					/*密钥更新上报方式*/
uchar8 GV_AbnorC_Report_Type[C_CRCLen2+CLReport_Type];						/*异常插卡上报方式*/
uchar8 GV_BuyCurr_Report_Type[C_CRCLen2+CLReport_Type];						/*购电上报方式*/
uchar8 GV_ReturnMoney_Report_Type[C_CRCLen2+CLReport_Type];					/*退费上报方式*/
uchar8 GV_ConMEndEn_Report_Type[C_CRCLen2+CLReport_Type];					/*恒定磁场干扰上报方式*/
uchar8 GV_RelayFaEndEn_Report_Type[C_CRCLen2+CLReport_Type];				/*负荷开关误动作上报方式*/
uchar8 GV_PowerFa_EndT_Report_Type[C_CRCLen2+CLReport_Type];				/*电源异常上报方式*/
uchar8 GV_SeriNoBalCurr_Report_Type[C_CRCLen2+CLReport_Type];				/*电流严重不平衡上报方式*/
uchar8 GV_ClockFault_Report_Type[C_CRCLen2+CLReport_Type];					/*时钟故障上报方式*/
uchar8 GV_MeteringChipFault_Report_Type[C_CRCLen2+CLReport_Type];			/*计量芯片故障上报方式*/
uchar8 GV_ABnor_ZeroCurrent_Report_Type[C_CRCLen2+CLReport_Type];			/*零线电流异常上报方式*/
uchar8 GV_Drive_Report_Type[C_CRCLen2+CLReport_Type];						/*主动上报方式*/

uchar8 GV_Relay_Delay_Time_645[CLRelay_Delay_Time_645+C_CRCLen2];					/*跳闸延时时间,带2 CRC*/
uchar8 GV_Drive_Report_Mode_645[CLDrive_Report_Mode_645+C_CRCLen2];					/*主动上报模式字,带2 CRC*/
uchar8 GV_Meter_Work_Char1_645[CLMeter_Work_Char1_645+C_CRCLen2];					/*电表运行特征字1,带2 CRC*/
uchar8 GV_DisplayBorrowPoint[CLDisplayBorrowPoint+C_CRCLen2];						/*显示借位位数,带2 CRC*/
uchar8 GV_DisplayBorrowPoint_RecFlag[CLDisplayBorrowPoint_RecFlag+C_CRCLen2];		/*显示借位位数矫正标志,带2 CRC*/

/************************数据层用内部静态变量********************************/
uchar8  GV_D_SafeFlag;                                  /*数据层内部用安全标志，在巡航程序中清零*/
uchar8  GV_20min_Num;                                   /*20min累加计数器*/
uchar8  GV_CruiseCheck_FlashNum;                        /*巡检Flash次数*/
uchar8  GV_CruiseCheck_RAMNum;                          /*巡检RAM CRC次数,当前巡检数据只为当前电能*/
ulong32 GV_ReadLoadFlashAddr32;                         /*该全局变量，用于14规范负荷记录模块抄读用，当初始化或第1次抄读时为全FF，第1次抄读完成后存放下1条负荷记录Flash地址*/
ulong32 GV_ReadLoadFlashAddr32Ear;                      /*用于14规范负荷记录模块抄读用，初始化为全FF*/
ulong32 GV_ReadLoadFlashAddr32Late;                     /*用于14规范负荷记录模块抄读用，初始化为全FF*/
uchar8  GV_SecLoadModeNum;                              /*用于14规范负荷记录模块抄读用，用于记录下1条记录模式字序号，初始化为FF*/
uchar8  GV_ReadRecordNum;                               /*用于记录冻结记录已应答个数*/
uchar8  GV_D_ClearSafeFlag;                             /*数据层内部用总清安全标志，在巡航程序中清零*/

/*************************数据结构定义***************************************/
#define NeedClearDataSign    0x80               /*需总清数据标志*/
/************数据存储格式读写方法宏定义*******645标识码块读仅支持645格式，数据长度，如电量类数据*********/
#define DT_Ref_E23_RAMCRC             1     /*①E2三处CRC备份及RAM带CRC(写该类数据时，先写RAM，接着更新E2数据,包括充值，电能透支剩余金额及结算时当前结算电能)*/
#define DT_Ti_E23_RAMCRC              (NeedClearDataSign|2)    /*②E2三处CRC备份及RAM带CRC(写该类数据时，只写RAM，定时写E2，主要是当前电量该类数据)。注意：目前698软件可靠性用于写铁电及RAM三处。只是当前电能的处理，写数据时判断写入数据的合理性。同时表示可清零数据特征*/
#define DT_E23                        3     /*③E2三处CRC备份*/
#define DT_Flash_DI04                 4     /*④Flash，带次数数据，DI0低4位表示次数，高4位表示不同标识码(查询4级表用)*/
#define DT_E21                        5     /*⑤E2一处*/
#define DT_RAM                        6     /*⑥RAM不带CRC*/
#define DT_RAMCRC                     7     /*⑦RAM带CRC*/
#define DT_E23_Hex                    8     /*⑧E2三处CRC备份，数据存储格式为hex格式(主要是累计次数，在通讯读该数据时，转换为BCD格式)*/
#define DT_Flash_Tol_DI0_DI1          9     /*⑨Flash，带次数数据，整个DI0表示次数，DI1表示分项标识码(查询4级表用)*/
#define DT_RAM_Time_Data              10    /*⑩RAM不带CRC，读数据时先判断掉电标志。*/
#if 0
#define DT_Flash_Tol_DI0_DI2          11    /*11： Flash，带次数数据，整个DI0表示次数，DI2表示分项标识码(查询4级表用，如需量的ABC三相数据读)*/
#define DT_Flash_Tol_DI0_SettEn       12    /*12：Flash，带次数数据，整个DI0表示次数，利用DI2、DI1计算分项偏移地址(代替查询4级表，主要是结算电量读，除ABC三相数据外)。*/
                                            /*同时数据长度及所读数据，根据是否是6+4(类似显示),或6+2(类似通信)，进行特殊处理*/
#define DT_Flash_Tol_DI0_SettDe       13    /*13：Flash，带次数数据，整个DI0表示次数，利用DI2、DI1计算分项偏移地址(代替查询4级表，主要是结算需量读，除ABC三相数据外)。*/
#define DT_Flash_Tol_DI0_W_Sett_En    14    /*14：Flash，带次数数据，整个DI0表示次数。结算模块写数据时一起写数据层，数据层内部，结算电量及结算日时间分开存储*/
#endif
#define DT_Flash_Tol_DI0              15    /*15： Flash，带次数数据，整个DI0表示次数。没有分项标识码。*/
#if 0
#define DT_E23_En                     16    /*16：电量类数据，满足6+2与6+4数据长度时，该数据需单独处理，数据长度(读、写)及所读数据，根据是否是6+4(类似显示),或6+2(类似通信)，进行特殊处理*/
                                            /*(列表645数据长度为6+2，当采用6+4读数据时，返回数据长度调整，取E2地址调整，如上1结算周期内组合有功累计用电量),写数据时，数据长度判断调整；*/
#define DT_E21_En                     17    /*17：电量类数据，满足6+2与6+4数据长度时，该数据需单独处理，数据长度(读、写)及所读数据，根据是否是6+4(类似显示),或6+2(类似通信)，进行特殊处理,主要针对存E2 1处数据*/
                                            /*(列表645数据长度为6+2，当采用6+4读数据时，返回数据长度调整，取E2地址调整，如上1--4次年结算日结算时间及结算周期组合有功总累计用电量*/
#endif
#define DT_RAM_DI0                    18    /*18：数据存RAM不带CRC，且数据长度、类型一样(同一DI3-DI1)，列表格时只列DI0最大值(,同一类型，不包括DI0=0，DI0=0要单列)，程序内部处理，*/
                                            /*数据地址及DI判断是否正确，如类似电表运行状态字1-7，列表格时，对应数据存储地址，为最低DI0对应数据存储地址，注意*/
#define DT_Ref_E23_RAMCRC_DI0         19    /*19：E2三处RAM带CRC，数据长度类型一样(同一DI3-DI1)，列表格时只列DI0最大值(不包括DI0=0，DI0=0要单列)，程序内部处理，*/
                                            /*数据地址及DI判断是否正确，如类似组合状态字，列表格时，对应数据存储地址，为最低DI0对应数据存储地址，注意*/
#define DT_E23_DI0                    20    /*20：E2三处，E2地址顺序列，数据长度类型一样(同一DI3-DI1)，列表格时只列DI0最大值(不包括DI0=0，DI0=0要单列)，程序内部处理，*/
                                            /*数据地址及DI判断是否正确，如类似结算日、密码，列表格时，对应数据存储地址，为最低DI0对应数据存储地址，注意*/
#define DT_E21CRC_DI0                 21    /*21：E2一处带CRC，数据长度类型一样(同一DI3-DI1)，列表格时只列DI0最大值(不包括DI0=0，DI0=0要单列)，程序内部处理，*/
                                            /*数据地址及DI判断是否正确，如类似自动循显显示第1-99屏显示代码，列表格时，对应数据存储地址，为最低DI0对应数据存储地址，注意*/
#define DT_E21_DI0                    22    /*22：E2一处，数据长度类型一样(同一DI3-DI1)，列表格时只列DI0最大值(不包括DI0=0，DI0=0要单列)，程序内部处理，*/
                                            /*数据地址及DI判断是否正确，如类似第1-254公共假日日期及日时段表号，列表格时，对应数据存储地址，为最低DI0对应数据存储地址，注意*/
#if 0
#define DT_RAM_DI1_0                  23    /*23：数据存RAM不带CRC，且数据长度、类型一样(同一DI3-DI2、DI0)，列表格时只列DI1最大值(,同一类型,包括DI1=0，计算数据偏移地址时，要考虑)，*/
                                            /*程序内部处理，数据地址及DI判断是否正确，如类似参数瞬时功率，列表格时，对应数据存储地址，为最低DI1对应数据存储地址，注意*/
#define DT_RAM_DI1                    24    /*24：数据存RAM不带CRC，且数据长度、类型一样(同一DI3-DI2、DI0)，列表格时只列DI1最大值(,同一类型，不包括DI1=0)，程序内部处理，*/
                                            /*数据地址及DI判断是否正确，如类似电压数据，列表格时，对应数据存储地址，为最低DI1对应数据存储地址，注意*/
#define DT_R_Flash_Tol_DI0_DI2_En     25    /*25： Flash，带次数数据，整个DI0表示次数，DI2表示分项标识码(查询4级表用，电量的ABC三相数据读)，*/
                                            /*同时数据长度及所读数据，根据是否是6+4(类似显示),或6+2(类似通信)，进行特殊处理*/
#endif
#define DT_W_Ref_E23_RAMCRC_Te        26    /*26:写E2 RAM数据，写入时模块一起写入，数据层内部单独处理，分开写，如当前套费率电价数据块*/
#define DT_Flash_Tol_DI0_DI1Max       27    /*27： Flash，带次数数据，整个DI0表示次数，列表2级表时只列上1次DI1最大值(不采用查找4级表的方式)，在查找数据DI及DI数据存放偏移地址时，*/
                                            /*OffsetAddr程序采用计算方式处理,目前只有校表记录采用该方式,除发生时刻DI1=0外*/
#define DT_Ref_E23_RAMCRC_DI0_2       28    /*28：E2三处RAM带CRC，数据长度类型一样(同一DI3-DI1)，列表格时只列DI0最大值(不包括DI0=0，1,DI0=0,1要单列)，程序内部处理，*/
                                            /*数据地址及DI判断是否正确，如类似全失压电流该类参数设置，列表格时，对应数据存储地址(电压异常判断电压地址)，为最低DI0对应数据存储地址，注意*/
#define DT_Flash_698EventTab          37    /*带OAD关联列表事件记录，存Flash*/
#define DT_E23_OADTab                 38    /*存E2三处，读数据时判断数据长度，需读取该关联列表OAD个数，写数据时只判断最大长度*/
#define DT_R_Ref_E23_RAMCRC_Lad       39    /*39:写E2 RAM数据，阶梯表写入时支持集合写，读数据时支持分开读，数据层内部单独处理*/
#define DT_E21CRC_MaxLen              40    /*40：E2一处带CRC，写入时判断不超过最大数据长度*/
#if 0
#define DT_E21_DI0_ReadDegree         41    /*41：E2一处，数据长度类型一样(同一DI3-DI1)，列表格时只列DI0最大值(不包括DI0=0，DI0=0要单列)，程序内部处理，*/
                                            /*数据地址及DI判断是否正确，读数据时需判断响应条件，如事件上报表格，读数据时，徐判断对应事件记录次数。列表格时，对应数据存储地址，为最低DI0对应数据存储地址，注意*/
#endif
#define DT_FRAM1CRC                   42    /*42：铁电一处带CRC*/
#if 0
#define DT_E23_En_Clear               (DT_E23_En|NeedClearDataSign)    /*16：电量类数据，满足6+2与6+4数据长度时，该数据需单独处理，数据长度(读、写)及所读数据，根据是否是6+4(类似显示),或6+2(类似通信)，进行特殊处理*/
                                            /*(列表645数据长度为6+2，当采用6+4读数据时，返回数据长度调整，取E2地址调整，如上1结算周期内组合有功累计用电量),写数据时，数据长度判断调整；*/
#endif
#define DT_E23_Clear                  (DT_E23|NeedClearDataSign)    /*③E2三处CRC备份*/

#define C_RAM_Max                     240    /*写E2数据内部最大缓存,长度包含2字节CRC*/
#define C_Clear_SafeFlag              0
#define C_Flash_EmptyNum              4      /*每页预留空标志字节数*/
#define C_OneFlash_PageNum            (4096-C_Flash_EmptyNum)    /*每页Flash可记录数据量*/
#define C_Flash_Empty                 0x00   /*读Flash是否为空判断，Flash底层反*/
#define C_Flash_NoEmpty               0xFF   /*写Flash不为空*/
#define C_Flash_Empty68               0x68   /*写Flash为空，每次擦除后，写4个68表示该页Flash为空，非68则不为空*/
#define C_LoadProfile_RevMode         1      /*698冻结修改时间标志，数据长度*/
#if 0
#define C_Wr_LoadProfile_MaxLen       105    /*写负荷记录最大数据长度，全记录103个字节*/
#define C_LoadP_CurrVol_Len_Bit0      17     /*第1类负荷记录电压、电流、频率数据长度*/
#define C_LoadP_Power_Len_Bit1        24     /*第2类负荷记录功率数据长度*/
#define C_LoadP_PowActor_Len_Bit2     8      /*第3类负荷记录功率因数数据长度*/
#define C_LoadP_TolEn_Len_Bit3        16     /*第4类负荷记录有、无功总电能数据长度*/
#define C_LoadP_QuarEn_Len_Bit4       16     /*第5类负荷记录四象限无功总电能数据长度*/
#define C_LoadP_CurrDe_Len_Bit5       6      /*第6类负荷记录当前需量数据长度*/
#endif
#define C_GV_20min_Num                240    /*5s累加定时器，20min*/
#define C_GV_19min_50s_Num            238    /*5s累加定时器，20min*/
#define C_FlashEvenOEEPageNum         12     /*Flash记录奇偶页擦除，查询次数12，当本页记录＞=12次时，则查询擦除下页，否则不满足擦除条件*/
#define C_MeterICE2ResLen             3      /*校表寄存器数据长度*/
#define C_RAMRefE2En_MaxPluse         80000  /*20minRAM电量更新E2限值,电能增量-见数据层数据梳理：最大脉冲值 计算*/
#define C_Meter_Work_State1           0xC33C /*电表运行状态字1:  Bit1：需量积算方式*/
#define C_Meter_Work_State2           0x0077 /*电表运行状态字2*/
//#define C_Meter_Work_State3         0x0077 /*电表运行状态字3，程序内部处理*/
#define C_Meter_Work_State4           0x01FF /*电表运行状态字4*/
#define C_Meter_Work_State5           0x01FF /*电表运行状态字5*/
#define C_Meter_Work_State6           0x01FF /*电表运行状态字6*/
#define C_Meter_Work_State7           0x07FF /*电表运行状态字7*/
#define C_HardError                   0x01   /*硬件故障运行状态字*/
#if 0
#define C_WriteAllLoadMode            0x3F   /*所有负荷记录模式字全记3F*/
#define C_RealTimeParaLoadMode        0x01   /*实时参数负荷记录模式字*/
#define C_PowerLoadMode               0x02   /*功率负荷记录模式字*/
#define C_PowerFactorLoadMode         0x04   /*功率因数负荷记录模式字*/
#define C_ReAcEnergy                  0x08   /*有、无功总电能负荷记录模式字*/
#define C_FourQuarterEnLoadMode       0x10   /*4象限电能负荷记录模式字*/
#define C_DemandLoadMode              0x20   /*需量负荷记录模式字*/
#define C_AllLoadModeDataLen          103    /*负荷记录全纪录数据长度*/
#define C_LoadEndSign                 0xE5   /*负荷记录结束标志*/
#endif
#define C_LoadStartSign               0xA0   /*负荷记录开始标志*/
#if 0
#define C_LoadBlockSign               0xAA   /*负荷记录块分割标志*/
#define C_OneLoadFixedLength          16     /*1条负荷记录固定数据长度，2A0+1字节数+5时间+6AA+1CS+1E5*/
#define C_OneLoadByteLength           5      /*负荷记录中字节数表示的数据长度，用记录总长度-该数据长度5(2A0+1字节数+1CS+1E5)*/
#define C_OneLoadFlashMemoryLength    1      /*1条负荷记录保存Flash时，总长度去掉的数据长度，用记录总长度-该数据长度1(目前去掉 1字节数)*/
#endif
#define C_LoadStartSignLength         0      /*负荷记录起始码长度，2A0，后为YMDhms 698冻结记录起始为YMDhms */
#define C_LoadDichotomyFindBefore     0x55   /*表示2分法，时间往前查找，主要用于时间往前调整*/
#define C_LoadDichotomyFindAfter      0xAA   /*表示2分法，时间往后查找，主要用于抄读负荷记录给定时间*/

#define C_NiuDebugReadData            0x01   /*读底层E2、Flash数据接口函数，调试用，0x00，不起作用*/
#if 0
#define C_NotNeedRenew                0xFFFF /*不需要更新*/
#endif
#define C_NextSign                    0x10   /*后续帧标志，Bit4-5:1有后续帧，0没有后续帧*/
#define C_NoNextSign                  0x00   /*后续帧标志，Bit4-5:1有后续帧，0没有后续帧*/

#define C_NextSign_Judge              0x30   /*后续帧标志，Bit4-5:1有后续帧，0没有后续帧*/

#define C_NextSign_Last               0x40   /*Bit7-6:1：表示返回数据包含最近1条记录，0：表示返回数据不包含最近1条记录*/

#define C_698Event_MaxNum100          100    /*广播校时和掉电最大次数，100次*/
#define C_698Event_MaxNum             10     /*事件最大次数，目前是10次*/
#define C_698Key_UpdateEvent_MaxNum   2      /*事件最大次数，密钥更新是2次，根据次数抄读判断用*/

//***********************************冻结后续帧***************/
#define C_FreezeNextSign              0x02   /*后续帧标志，Bit0-1:2有后续帧，非2无后续帧*/
#define C_FreezeNextSignFlag          0x03   /*后续帧判断位Bit0-1*/


/*读取冻结中关联电能判断标志*/
#define C_ReadRelated02Energy         0x01   /*读取的是02属性电能*/
#define C_SaveRelated04Energy         0x02   /*存储的是04属性电能*/
#define C_EnergyPlanSame              0x04   /*电能方案是相同的*/

//***********************************流程安全标志***************/
#define	C_DataClearMeterSafeFlag      0x36   /*电表总清安全字节值*/
#define	C_DataClearMeterSafeFlag_1    0x06   /**/
#define	C_DataClearMeterSafeFlag_2    0x10   /**/
#define	C_DataClearMeterSafeFlag_3    0x20   /**/

typedef struct
{
	ulong32 V_DI;               /*DI:DI3~DI0数据标识*/
	ulong32 PStr_3TableAddr;    /*对应3级表格结构体数组地址，当3级表不是结构体时，直接为数据存放E2或RAM绝对地址*/
	ushort16 V_LineNum;         /*行号：当三级表为结构体数组时，表示数据表格数据对应的三级表数组具体的行号，*/
	                            /*非结构体时，该数据为0*/
	ushort16 V_DataLen;         /*DI3~DI0数据标识对应的具体数据长度*/
	uchar8 V_WR_MesAuth;        /*WR:最高字节表示Bit7:表示对应标识码，是否支持读；*/
	                            /*1：支持；0：不支持        */
	                            /*Bit0~Bit6：表示写数据消息号，当支持多个消息写时，采用组合方式，全零表示不支持写；*/
	uchar8 V_DT_Type;           /*上文中汇总①~13种数据存储特征*/
}Str_2Table;

typedef struct
{
	Str_2Table *PV_Str_2Table;  /*用于事件记录后续帧抄读用，方便后续帧查找.满足要求的事件2级表绝对地址**/
	uchar8 V_NextSign;          /*后续帧标志，安全性判断*/
	uchar8 V_LastNum;           /*用于事件记录抄读记录上次读取到多少次，方便后续帧从下次继续抄读*/
	ushort16 V_CRC16;
}Str_NextEvent;

Str_NextEvent GV_Str_NextEvent;

#define C_NextLoadTime_MaxNum      12    /*结算日冻结最大12次*/
#define C_FreezeImmid_MaxNum       3     /*瞬时冻结最大3次*/
#define C_FreezeTimeZone_MaxNum    2     /*切换冻结最大2次*/
#define C_YSettleFreeze_MaxNum     4     /*阶梯切换冻结最大4次*/

uchar8 GV_FreezeLastNum[3];              /*用于冻结记录抄读记录上次读取到多少次，方便后续帧从下次继续抄读*/
/*******************************************************变量表格结构体定义***********************************************************/
typedef struct
{
	ushort16 V_OffAddr;    /*对于1记录块内有分类标识码(如结算电量)*/
	                       /*用于存放记录该标识码对应的数据偏移地址，所有值包括自扩标识码*/
	uchar8 V_DI;           /*用于区分偏移地址的1个数据标示*/
}Str_4Table;

typedef struct
{
	ulong32 V_StaFlashAddr;          /*起始页地址：记录块Flash首页地址*/
	ulong32 V_EndFlashAddr;          /*结束页地址：记录块Flash尾页地址*/
	ulong32 PStr_4TableAddr;         /*4级表格结构体数组地址*/
	ushort16 V_Num_E2BakeUp1Addr;    /*次数存E2第1处备份地址*/
	ushort16 V_DataToalLen;          /*1个记录块数据总长度*/
	uchar8  V_Str_4TableLen;         /*4级表格结构体数组数据长度,当不存在4级表时，数据为全零*/
}Str_3cTable;

typedef struct
{
	ushort16 V_E2BakeUp1Addr;        /*数据存放E2三处备份,第一块地址，第2、3块采用固定间隔地址*/
	uchar8 *V_RamAddr;               /*数据存放RAM地址*/
	ushort16 V_DataLen;              /*每个数据项长度，后增项目，用于E2数据恢复RAM,不包括CRC长度*/
	uchar8 V_DataNum;                /*每类数据项个数，后增项目，用于E2数据恢复RAM，如04FE00项目列表格DI时，没有全列，此时的该项目为8:01-08*/
}Str_3aTable;

typedef struct
{
	ushort16 V_E2BakeUp1Addr_OADTab;       /*数据存放E2三处备份,第一块地址，第2、3块采用固定间隔地址,关联OAD序号表*/
	ushort16 V_E2BakeUp1Addr_OADTabLen;    /*数据存放E2三处备份,第一块地址，第2、3块采用固定间隔地址,关联序号表OAD个数*/
//	uchar8 V_DI2;                          /*不同事件记录DI2*/
}Str_3eTable;

typedef struct
{
	ulong32 PStr_2TableAddr;     /*2级表格结构体数组地址**/
	ushort16 V_Str_2TableLen;    /*对应2级表结构体数据长度*/
	uchar8 V_DI3;                /*数据标识*/
}Str_1Table;

typedef struct
{
	ulong32 V_DI;            /*事件记录数据标示*/
	ushort16 V_E2AddrSt;     /*数据标识对应E2起始地址*/
	ushort16 V_E2AddrEnd;    /*数据标识对应E2结束地址*/
	uchar8 V_EventNum;       /*数据标示对应EventNum号，学云宏定义*/
}Str_EvenTable;

typedef struct
{
	ulong32 V_StaFlashAddr;     /*起始页地址：记录块Flash首页地址*/
	ulong32 V_EndFlashAddr;     /*结束页地址：记录块Flash尾页地址*/
	ushort16 V_LineNumLen_T;    /*行号：表示数据表格数据对应的三级表数组具体的行号，冻结OAD长度、周期表*/
	ushort16 V_LineNumTab;      /*行号：表示数据表格数据对应的三级表数组具体的行号，冻结序号表*/
	ushort16 V_E2AddrEar;       /*数据标识对应E2起始地址*/
	ushort16 V_E2AddrLate;      /*数据标识对应E2结束地址*/
	uchar8 V_DI2;               /*冻结DI2*/
}Str_698FreezeAddrTable;

/************************************4级分表************************************/
#define En_Data_Len           4          /*电能字节数，电能2位小数*/
#if 0
#define En_Data_Len_FF        20         /*每块电能字节数*/
#define De_Data_Len           9          /*需量字节数(包括时间)，需量6位小数*/
#define De_Data_Len_FF        45         /*每块需量字节数*/
#define En_SettEn_BlockLen    276        /*69个电能数据，6+2，4字节*/

#define PosA_Ac_En_Off        (5*4*9)    /*结算A相正向有功电能偏移地址*/
#define PosA_Ac_De_Off        (5*9*8)    /*结算A相正向有功最大需量及发生时刻偏移地址,2+6+YMDhm*/
#define TFree_Off_Len         20         /**每个定时冻结数据块长度*/
#endif
#define Get_DI0    0x000000FF))          /*4级表用*/
#define Get_DI1    0x0000FF00)>>8)
#define Get_DI2    0x00FF0000)>>16)
#define Get_DI3    0xFF000000)>>24)
#define Get_OI     0xFFFF0000)>>16)

/*****************事件记录表格***********************/
/**********当前值记录表，不带累计时间，数据层内部统一处理操作********/
typedef struct
{
	ulong32 V_OAD;                   /*事件记录，当前值记录表OAD*/
	ushort16 V_Num_E2BakeUp1Addr;    /*当前值记录表中对应事件发生次数E2地址*/
}Str_EventCurrentTab;

const Str_EventCurrentTab GCStr_EventCurrentTab[]=  /************当前记录表*************/
{
/*事件记录，当前值记录表OAD                 当前值记录表中对应事件发生次数E2地址*/
	{CTol_Clear_Current,            E2Addr_Tol_Clear_Degree},		/*总清当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
	{CDe_Clear_Current,             E2Addr_De_Clear_Degree},		/*需清当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
	{CEven_Clear_Current,           E2Addr_Even_Clear_Degree},		/*事件清零当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
	{CProgram_Current,              E2Addr_Program_Degree},			/*编程记录当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
	{CAdjTime_Current,              E2Addr_AdjTime_Degree},			/*校时记录当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
	{CProgPT_Current,               E2Addr_ProgPT_Degree},			/*时段表记录当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
	{CProgTZ_Current,               E2Addr_ProgTZ_Degree},			/*时区表记录当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
	{CProgWRe_Current,              E2Addr_ProgWRe_Degree},			/*周休日编程记录当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
	{CProgHol_Current,              E2Addr_ProgHol_Degree},			/*节假日编程记录当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
	{CProgAcC_Current,              E2Addr_ProgAcC_Degree},			/*有功组合方式编程记录当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
	{CProgSettD_Current,            E2Addr_ProgSettD_Degree},		/*结算日编程记录当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
	{CProgTPara_Current,            E2Addr_ProgTPara_Degree},		/*费率参数表编程记录当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
	{CProgLad_Current,              E2Addr_ProgLad_Degree},			/*阶梯表编程记录当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
	{CProgKD_Current,               E2Addr_ProgKD_Degree},			/*密钥编程记录当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
	{CAbnorC_Current,               E2Addr_AbnorC_Degree},			/*异常插卡记录当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
	{CBuyCurr_Current,              E2Addr_BuyCurr_Degree},			/*购电记录当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
	{CReturn_M_Current,             E2Addr_Return_M_Degree},		/*退费记录当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
	{CRelayOpen_Current,            E2Addr_RelayOpen_Degree},		/*跳闸当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
	{CRelayClose_Current,           E2Addr_RelayClose_Degree},		/*合闸当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
	{CBroadcastTime_Current,        E2Addr_BroadcastTime_Degree},	/*广播校时记录当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
//	{CBroadTimeAbnormal_Current,    E2Addr_BroadTimeAbnormal_Degree},
};
#define GCStr_EventCurrentTab_Len (sizeof(GCStr_EventCurrentTab)/sizeof(Str_EventCurrentTab))

/**********电网类事件固定关联列表对应数据层存数数据偏移********/
#define C_EventHPSign          0x80    /*最高位为1，表示发生数据*/
#define C_EventOutSign         0x7F    /*去除最高位*/
#if 0
#define C_TolTabDataLenSign    1       /*固定、关联OAD列表，对应数据总长度*/
#define C_FixTabDataLenSign    2       /*固定OAD列表，对应数据总长度*/
#define C_TabDataLenSign       3       /*可变OAD列表，对应数据总长度*/
#endif
typedef struct
{
	ulong32 V_OAD;       /*对应固定列表OAD*/
	uchar8 V_DataLen;    /*数据长度最大127,最高位为1表示发生*/
}Str_4aTable;

const Str_4aTable Str_4aTable_AllLossVol[]=  /************全失压***CLASS 7*************/
{
	/************全失压****************/
/*对应固定列表OAD           数据长度最大127,最高位为1表示发生*/
	{CEventNum,								(C_EventHPSign|CLEventNum)},
	{CEventHPTime,							(C_EventHPSign|CLEventHPTime)},
	{CEventEndTime,							(CLEventEndTime)},
	{CEventHPSource,						(C_EventHPSign|0x01)},
	{CUpdata_Status,						(C_EventHPSign|0x01)},			/*事件上报状态*/
};
#define Str_4aTable_AllLossVol_Len (sizeof(Str_4aTable_AllLossVol)/sizeof(Str_4aTable))


const Str_4aTable Str_4aTable_De_Over[]=  /************需量超限事件单元***CLASS 7*************/
{
/*对应固定列表OAD     					数据长度最大127,最高位为1表示发生*/
	{CEventNum,                   			(C_EventHPSign|CLEventNum)	},
	{CEventHPTime,                			(C_EventHPSign|CLEventHPTime)},
	{CEventEndTime,               			(CLEventEndTime)},
	{CEventHPSource,              			(C_EventHPSign|0x01)},
	{CUpdata_Status,						(C_EventHPSign|0x01)},			/*事件上报状态*/
	{C_OverDemandRenew_Demand,            	(CLCurr_AcDemand)},				/*需量超限期间最大需量*/
	{C_OverDemandRenew_HapTime,            	(CLDate_Time)},					/*需量超限期间最大需量发生时间*/
};
#define Str_4aTable_De_Over_Len  (sizeof(Str_4aTable_De_Over)/sizeof(Str_4aTable))

const Str_4aTable Str_4aTable_Qua_De_Over[]=  /************无功需量超限事件单元***CLASS 24，暂定*************/
{
/*对应固定列表OAD               数据长度最大127,最高位为1表示发生*/
	{CEventNum,                   			(C_EventHPSign|CLEventNum)	},
	{CEventHPTime,                			(C_EventHPSign|CLEventHPTime)},
	{CEventEndTime,               			(CLEventEndTime)},
	{CEventHPSource,              			(C_EventHPSign|0x01)},
	{CUpdata_Status,						(C_EventHPSign|0x01)},			/*事件上报状态*/
	{C_OverDemandRenew_Demand,            	(CLCurr_ReDemand)},				/*需量超限期间最大需量*/
	{C_OverDemandRenew_HapTime,            	(CLDate_Time)},					/*需量超限期间最大需量发生时间*/
};
#define Str_4aTable_Qua_De_Over_Len  (sizeof(Str_4aTable_Qua_De_Over)/sizeof(Str_4aTable))

const Str_4aTable Str_4aTable_Even_Clear[]=  /************事件清零记录单元***CLASS 7*************/
{
/*对应固定列表OAD                 数据长度最大127,最高位为1表示发生*/
	{CEventNum,                   			(C_EventHPSign|CLEventNum)	},
	{CEventHPTime,                			(C_EventHPSign|CLEventHPTime)},
	{CEventEndTime,               			(CLEventEndTime)},
	{CEventHPSource,              			(C_EventHPSign|0x01)},
	{CUpdata_Status,						(C_EventHPSign|0x01)},			/*事件上报状态*/
	{CEventClear_OADList,					(C_EventHPSign|CLProgOAD)},		/*编程记录OAD列表*/
};
#define Str_4aTable_Even_Clear_Len  (sizeof(Str_4aTable_Even_Clear)/sizeof(Str_4aTable))

const Str_4aTable Str_4aTable_Prog[]=  /************编程记录单元***CLASS 7*************/
{
/*对应固定列表OAD     					数据长度最大127,最高位为1表示发生*/
	{CEventNum,                   			(C_EventHPSign|CLEventNum)	},
	{CEventHPTime,                			(C_EventHPSign|CLEventHPTime)},
	{CEventEndTime,               			(CLEventEndTime)},
	{CEventHPSource,              			(C_EventHPSign|0x01)},
	{CUpdata_Status,						(C_EventHPSign|0x01)},			/*事件上报状态*/
	{CProgOADGather,              			(CLProgOADGather)},				/*编程记录OAD列表*/
};
#define Str_4aTable_Prog_Len  (sizeof(Str_4aTable_Prog)/sizeof(Str_4aTable))

const Str_4aTable Str_4aTable_AbnorC[]=  /************异常插卡记录***CLASS 7*************/
{
/*对应固定列表OAD     					数据长度最大127,最高位为1表示发生*/
	{CEventNum,                   			(C_EventHPSign|CLEventNum)	},
	{CEventHPTime,                			(C_EventHPSign|CLEventHPTime)},
	{CEventEndTime,               			(CLEventEndTime)},
	{CEventHPSource,              			(C_EventHPSign|0x01)},
	{CUpdata_Status,						(C_EventHPSign|0x01)},								/*事件上报状态*/
	{CAbnormalCard_CareNo,					(C_EventHPSign|CLAbnormalCard_CareNo)},				/*异常插卡卡序列号*/
	{CAbnormalCard_ErrorStatus,				(C_EventHPSign|CLAbnormalCard_ErrorStatus)},		/*异常插卡错误状态字*/
	{CAbnormalCard_OrderHead,				(C_EventHPSign|CLAbnormalCard_OrderHead)},			/*异常插卡插卡操作命令头*/
	{CAbnormalCard_ErrorRespondStatus,		(C_EventHPSign|CLAbnormalCard_ErrorRespondStatus)},	/*异常插卡插卡错误响应状态*/
};
#define Str_4aTable_AbnorC_Len  (sizeof(Str_4aTable_AbnorC)/sizeof(Str_4aTable))


const Str_4aTable Str_4aTable_Return_M[]=  /************退费记录***CLASS 7*************/
{
/*对应固定列表OAD     					数据长度最大127,最高位为1表示发生*/
	{CEventNum,                   			(C_EventHPSign|CLEventNum)	},
	{CEventHPTime,                			(C_EventHPSign|CLEventHPTime)},
	{CEventEndTime,               			(CLEventEndTime)},
	{CEventHPSource,              			(C_EventHPSign|0x01)},
	{CUpdata_Status,						(C_EventHPSign|0x01)},			/*事件上报状态*/
	{CReturnMoney_Charge,					(C_EventHPSign|CLReturn_M_Sum3)},
};
#define Str_4aTable_Return_M_Len  (sizeof(Str_4aTable_Return_M)/sizeof(Str_4aTable))

const Str_4aTable Str_4aTable_ProgPT[]=  /************时段表编程记录***CLASS 7*************/
{
	/************时段表编程记录****************/
/*对应固定列表OAD     					数据长度最大127,最高位为1表示发生*/
	{CEventNum,                   			(C_EventHPSign|CLEventNum)	},
	{CEventHPTime,                			(C_EventHPSign|CLEventHPTime)},
	{CEventEndTime,               			(CLEventEndTime)},
	{CEventHPSource,              			(C_EventHPSign|0x01)},
	{CUpdata_Status,						(C_EventHPSign|0x01)},						/*事件上报状态*/
	{CRWTimeTable_OAD,              		(C_EventHPSign|CLProgOAD)},					/*时段表编程OAD*/
	{CRWTimeTable_ForwardData,				(C_EventHPSign|CLFirst_TZone_1PT_Data)},	/*时段表编程编程前数据*/
};
#define Str_4aTable_ProgPT_Len  (sizeof(Str_4aTable_ProgPT)/sizeof(Str_4aTable))

const Str_4aTable Str_4aTable_ProgHol[]=  /************公共假日编程记录***CLASS 7*************/
{
	/************公共假日编程记录****************/
/*对应固定列表OAD     					数据长度最大127,最高位为1表示发生*/
	{CEventNum,                   			(C_EventHPSign|CLEventNum)	},
	{CEventHPTime,                			(C_EventHPSign|CLEventHPTime)},
	{CEventEndTime,               			(CLEventEndTime)},
	{CEventHPSource,              			(C_EventHPSign|0x01)},
	{CUpdata_Status,						(C_EventHPSign|0x01)},					/*事件上报状态*/
	{C_RWHoliday_OAD,              			(C_EventHPSign|CLProgOAD)},				/*节假日编程OAD*/
	{CRWHoliday_ForwardData,				(C_EventHPSign|CLHolidy_PT_Table1)},	/*节假日编程前节假日数据*/
};
#define Str_4aTable_ProgHol_Len  (sizeof(Str_4aTable_ProgHol)/sizeof(Str_4aTable))

const Str_4aTable Str_4aTable_QuaReDeOver[]=  /************无功需量超限，CLASS 24*************/
{
	/************无功需量超限****************/
/*对应固定列表OAD     					数据长度最大127,最高位为1表示发生*/
	{CEventNum,                   			(C_EventHPSign|CLEventNum)},
	{CEventHPTime,                			(C_EventHPSign|CLEventHPTime)},
	{CEventEndTime,               			(CLEventEndTime)},
	{CUpdata_Status,						(C_EventHPSign|0x01)},			/*事件上报状态*/
};
#define Str_4aTable_QuaReDeOver_Len  (sizeof(Str_4aTable_QuaReDeOver)/sizeof(Str_4aTable))

typedef struct
{
	ulong32 V_StaFlashAddr;            /*起始页地址：记录块Flash首页地址*/
	ulong32 V_EndFlashAddr;            /*结束页地址：记录块Flash尾页地址*/
	ulong32 PStr_4aTableAddr;          /*4a级表格结构体数组地址，事件固定关联列表*/
	ushort16 V_TB_E2BakeUp1Addr;       /*关联列表存E2第1处备份地址*/
	ushort16 V_TBLen_E2BakeUp1Addr;    /*关联列个数存E2第1处备份地址*/
	ushort16 V_Num_E2BakeUp1Addr;      /*次数存E2第1处备份地址*/
	uchar8 V_Str_4aTableLen;           /*4级表格结构体数组数据长度,当不存在4级表时，数据为全零*/
}Str_3dEventTable;

const Str_3dEventTable Str_3d698EventTable_Flash[]=
{/*行号 Flash首地址                             Flash尾页地址                           4a级表格结构体数组地址                             事件关联列表     存E2第1处备份地址                    关联列个数存E2第1处备份地址                             次数存E2第1处备份地址                             4级表格结构体数组数据长度,当不存在4级表时，数据为全零*/
/*000*/{FlashStAddr_All_Loss_Vol,          FlashEndAddr_All_Loss_Vol,          (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_All_Loss_Vol_OADTab,              E2Addr_All_Loss_Vol_OADTabLen,              E2Addr_All_Loss_Vol_Degree,              Str_4aTable_AllLossVol_Len},
/*001*/{FlashStAddr_Aux_Pow_Down,          FlashEndAddr_Aux_Pow_Down,          (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_Aux_Pow_Down_OADTab,              E2Addr_Aux_Pow_Down_OADTabLen,              E2Addr_Aux_Pow_Down_Degree,              Str_4aTable_AllLossVol_Len},
/*002*/{FlashStAddr_Pow_Down,              FlashEndAddr_Pow_Down,              (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_Pow_Down_OADTab,                  E2Addr_Pow_Down_OADTabLen,                  E2Addr_Pow_Down_Degree,                  Str_4aTable_AllLossVol_Len},
/*003*/{FlashStAddr_Pos_Ac_De_Over,        FlashEndAddr_Pos_Ac_De_Over,        (ulong32)&Str_4aTable_De_Over[0],        E2Addr_Pos_Ac_De_Over_OADTab,            E2Addr_Pos_Ac_De_Over_OADTabLen,            E2Addr_Pos_Ac_De_Over_Degree,            Str_4aTable_De_Over_Len},
/*004*/{FlashStAddr_Rev_Ac_De_Over,        FlashEndAddr_Rev_Ac_De_Over,        (ulong32)&Str_4aTable_De_Over[0],        E2Addr_Rev_Ac_De_Over_OADTab,            E2Addr_Rev_Ac_De_Over_OADTabLen,            E2Addr_Rev_Ac_De_Over_Degree,            Str_4aTable_De_Over_Len},
/*005*/{FlashStAddr_Qua1_Re_De_Over,       FlashEndAddr_Qua1_Re_De_Over,       (ulong32)&Str_4aTable_Qua_De_Over[0],    E2Addr_Qua_Re_De_Over_OADTab,            E2Addr_Qua_Re_De_Over_OADTabLen,            E2Addr_Qua1_Re_De_Over_Degree,           Str_4aTable_Qua_De_Over_Len},
/*006*/{FlashStAddr_Qua2_Re_De_Over,       FlashEndAddr_Qua2_Re_De_Over,       (ulong32)&Str_4aTable_Qua_De_Over[0],    E2Addr_Qua_Re_De_Over_OADTab,            E2Addr_Qua_Re_De_Over_OADTabLen,            E2Addr_Qua2_Re_De_Over_Degree,           Str_4aTable_Qua_De_Over_Len},
/*007*/{FlashStAddr_Qua3_Re_De_Over,       FlashEndAddr_Qua3_Re_De_Over,       (ulong32)&Str_4aTable_Qua_De_Over[0],    E2Addr_Qua_Re_De_Over_OADTab,            E2Addr_Qua_Re_De_Over_OADTabLen,            E2Addr_Qua3_Re_De_Over_Degree,           Str_4aTable_Qua_De_Over_Len},
/*008*/{FlashStAddr_Qua4_Re_De_Over,       FlashEndAddr_Qua4_Re_De_Over,       (ulong32)&Str_4aTable_Qua_De_Over[0],    E2Addr_Qua_Re_De_Over_OADTab,            E2Addr_Qua_Re_De_Over_OADTabLen,            E2Addr_Qua4_Re_De_Over_Degree,           Str_4aTable_Qua_De_Over_Len},
/*009*/{FlashStAddr_LossA_Vol,             FlashEndAddr_LossA_Vol,             (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Loss_Vol_OADTab,                  E2Addr_Loss_Vol_OADTabLen,                  E2Addr_LossA_Vol_Degree,                 Str_4aTable_QuaReDeOver_Len},
/*010*/{FlashStAddr_LossB_Vol,             FlashEndAddr_LossB_Vol,             (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Loss_Vol_OADTab,                  E2Addr_Loss_Vol_OADTabLen,                  E2Addr_LossB_Vol_Degree,                 Str_4aTable_QuaReDeOver_Len},
/*011*/{FlashStAddr_LossC_Vol,             FlashEndAddr_LossC_Vol,             (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Loss_Vol_OADTab,                  E2Addr_Loss_Vol_OADTabLen,                  E2Addr_LossC_Vol_Degree,                 Str_4aTable_QuaReDeOver_Len},
/*012*/{FlashStAddr_LowA_Vol,              FlashEndAddr_LowA_Vol,              (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Low_Vol_OADTab,                   E2Addr_Low_Vol_OADTabLen,                   E2Addr_LowA_Vol_Degree,                  Str_4aTable_QuaReDeOver_Len},
/*013*/{FlashStAddr_LowB_Vol,              FlashEndAddr_LowB_Vol,              (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Low_Vol_OADTab,                   E2Addr_Low_Vol_OADTabLen,                   E2Addr_LowB_Vol_Degree,                  Str_4aTable_QuaReDeOver_Len},
/*014*/{FlashStAddr_LowC_Vol,              FlashEndAddr_LowC_Vol,              (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Low_Vol_OADTab,                   E2Addr_Low_Vol_OADTabLen,                   E2Addr_LowC_Vol_Degree,                  Str_4aTable_QuaReDeOver_Len},
/*015*/{FlashStAddr_OverA_Vol,             FlashEndAddr_OverA_Vol,             (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Over_Vol_OADTab,                  E2Addr_Over_Vol_OADTabLen,                  E2Addr_OverA_Vol_Degree,                 Str_4aTable_QuaReDeOver_Len},
/*016*/{FlashStAddr_OverB_Vol,             FlashEndAddr_OverB_Vol,             (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Over_Vol_OADTab,                  E2Addr_Over_Vol_OADTabLen,                  E2Addr_OverB_Vol_Degree,                 Str_4aTable_QuaReDeOver_Len},
/*017*/{FlashStAddr_OverC_Vol,             FlashEndAddr_OverC_Vol,             (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Over_Vol_OADTab,                  E2Addr_Over_Vol_OADTabLen,                  E2Addr_OverC_Vol_Degree,                 Str_4aTable_QuaReDeOver_Len},
/*018*/{FlashStAddr_BreakA_Vol,            FlashEndAddr_BreakA_Vol,            (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Break_Vol_OADTab,                 E2Addr_Break_Vol_OADTabLen,                 E2Addr_BreakA_Vol_Degree,                Str_4aTable_QuaReDeOver_Len},
/*019*/{FlashStAddr_BreakB_Vol,            FlashEndAddr_BreakB_Vol,            (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Break_Vol_OADTab,                 E2Addr_Break_Vol_OADTabLen,                 E2Addr_BreakB_Vol_Degree,                Str_4aTable_QuaReDeOver_Len},
/*020*/{FlashStAddr_BreakC_Vol,            FlashEndAddr_BreakC_Vol,            (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Break_Vol_OADTab,                 E2Addr_Break_Vol_OADTabLen,                 E2Addr_BreakC_Vol_Degree,                Str_4aTable_QuaReDeOver_Len},
/*021*/{FlashStAddr_RevPS_Vol,             FlashEndAddr_RevPS_Vol,             (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_RevPS_Vol_OADTab,                 E2Addr_RevPS_Vol_OADTabLen,                 E2Addr_RevPS_Vol_Degree,                 Str_4aTable_AllLossVol_Len},
/*022*/{FlashStAddr_RevPS_Curr,            FlashEndAddr_RevPS_Curr,            (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_RevPS_Curr_OADTab,                E2Addr_RevPS_Curr_OADTabLen,                E2Addr_RevPS_Curr_Degree,                Str_4aTable_AllLossVol_Len},
/*023*/{FlashStAddr_NoBal_Vol,             FlashEndAddr_NoBal_Vol,             (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_NoBal_Vol_OADTab,                 E2Addr_NoBal_Vol_OADTabLen,                 E2Addr_NoBal_Vol_Degree,                 Str_4aTable_AllLossVol_Len},
/*024*/{FlashStAddr_NoBal_Curr,            FlashEndAddr_NoBal_Curr,            (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_NoBal_Curr_OADTab,                E2Addr_NoBal_Curr_OADTabLen,                E2Addr_NoBal_Curr_Degree,                Str_4aTable_AllLossVol_Len},
/*025*/{FlashStAddr_SevNoBal_Curr,         FlashEndAddr_SevNoBal_Curr,         (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_SevNoBal_Curr_OADTab,             E2Addr_SevNoBal_Curr_OADTabLen,             E2Addr_SevNoBal_Curr_Degree,             Str_4aTable_AllLossVol_Len},
/*026*/{FlashStAddr_LossA_Curr,            FlashEndAddr_LossA_Curr,            (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Loss_Curr_OADTab,                 E2Addr_Loss_Curr_OADTabLen,                 E2Addr_LossA_Curr_Degree,                Str_4aTable_QuaReDeOver_Len},
/*027*/{FlashStAddr_LossB_Curr,            FlashEndAddr_LossB_Curr,            (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Loss_Curr_OADTab,                 E2Addr_Loss_Curr_OADTabLen,                 E2Addr_LossB_Curr_Degree,                Str_4aTable_QuaReDeOver_Len},
/*028*/{FlashStAddr_LossC_Curr,            FlashEndAddr_LossC_Curr,            (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Loss_Curr_OADTab,                 E2Addr_Loss_Curr_OADTabLen,                 E2Addr_LossC_Curr_Degree,                Str_4aTable_QuaReDeOver_Len},
/*029*/{FlashStAddr_OverA_Curr,            FlashEndAddr_OverA_Curr,            (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Over_Curr_OADTab,                 E2Addr_Over_Curr_OADTabLen,                 E2Addr_OverA_Curr_Degree,                Str_4aTable_QuaReDeOver_Len},
/*030*/{FlashStAddr_OverB_Curr,            FlashEndAddr_OverB_Curr,            (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Over_Curr_OADTab,                 E2Addr_Over_Curr_OADTabLen,                 E2Addr_OverB_Curr_Degree,                Str_4aTable_QuaReDeOver_Len},
/*031*/{FlashStAddr_OverC_Curr,            FlashEndAddr_OverC_Curr,            (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Over_Curr_OADTab,                 E2Addr_Over_Curr_OADTabLen,                 E2Addr_OverC_Curr_Degree,                Str_4aTable_QuaReDeOver_Len},
/*032*/{FlashStAddr_BreakA_Curr,           FlashEndAddr_BreakA_Curr,           (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Break_Curr_OADTab,                E2Addr_Break_Curr_OADTabLen,                E2Addr_BreakA_Curr_Degree,               Str_4aTable_QuaReDeOver_Len},
/*033*/{FlashStAddr_BreakB_Curr,           FlashEndAddr_BreakB_Curr,           (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Break_Curr_OADTab,                E2Addr_Break_Curr_OADTabLen,                E2Addr_BreakB_Curr_Degree,               Str_4aTable_QuaReDeOver_Len},
/*034*/{FlashStAddr_BreakC_Curr,           FlashEndAddr_BreakC_Curr,           (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Break_Curr_OADTab,                E2Addr_Break_Curr_OADTabLen,                E2Addr_BreakC_Curr_Degree,               Str_4aTable_QuaReDeOver_Len},
/*035*/{FlashStAddr_PowerA_Rev,            FlashEndAddr_PowerA_Rev,            (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Power_Rev_OADTab,                 E2Addr_Power_Rev_OADTabLen,                 E2Addr_PowerA_Rev_Degree,                Str_4aTable_QuaReDeOver_Len},
/*036*/{FlashStAddr_PowerB_Rev,            FlashEndAddr_PowerB_Rev,            (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Power_Rev_OADTab,                 E2Addr_Power_Rev_OADTabLen,                 E2Addr_PowerB_Rev_Degree,                Str_4aTable_QuaReDeOver_Len},
/*037*/{FlashStAddr_PowerC_Rev,            FlashEndAddr_PowerC_Rev,            (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Power_Rev_OADTab,                 E2Addr_Power_Rev_OADTabLen,                 E2Addr_PowerC_Rev_Degree,                Str_4aTable_QuaReDeOver_Len},
/*038*/{FlashStAddr_OverA_Lo,              FlashEndAddr_OverA_Lo,              (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Over_Lo_OADTab,                   E2Addr_Over_Lo_OADTabLen,                   E2Addr_OverA_Lo_Degree,                  Str_4aTable_QuaReDeOver_Len},
/*039*/{FlashStAddr_OverB_Lo,              FlashEndAddr_OverB_Lo,              (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Over_Lo_OADTab,                   E2Addr_Over_Lo_OADTabLen,                   E2Addr_OverB_Lo_Degree,                  Str_4aTable_QuaReDeOver_Len},
/*040*/{FlashStAddr_OverC_Lo,              FlashEndAddr_OverC_Lo,              (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Over_Lo_OADTab,                   E2Addr_Over_Lo_OADTabLen,                   E2Addr_OverC_Lo_Degree,                  Str_4aTable_QuaReDeOver_Len},
/*041*/{FlashStAddr_Tol_Clear,             FlashEndAddr_Tol_Clear,             (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_Tol_Clear_OADTab,                 E2Addr_Tol_Clear_OADTabLen,                 E2Addr_Tol_Clear_Degree,                 Str_4aTable_AllLossVol_Len},
/*042*/{FlashStAddr_De_Clear,              FlashEndAddr_De_Clear,              (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_De_Clear_OADTab,                  E2Addr_De_Clear_OADTabLen,                  E2Addr_De_Clear_Degree,                  Str_4aTable_AllLossVol_Len},
/*043*/{FlashStAddr_Even_Clear,            FlashEndAddr_Even_Clear,            (ulong32)&Str_4aTable_Even_Clear[0],     E2Addr_Even_Clear_OADTab,                E2Addr_Even_Clear_OADTabLen,                E2Addr_Even_Clear_Degree,                Str_4aTable_Even_Clear_Len},
/*044*/{FlashStAddr_Program,               FlashEndAddr_Program,               (ulong32)&Str_4aTable_Prog[0],           E2Addr_Program_OADTab,                   E2Addr_Program_OADTabLen,                   E2Addr_Program_Degree,                   Str_4aTable_Prog_Len},
/*045*/{FlashStAddr_AbnorC,                FlashEndAddr_AbnorC,                (ulong32)&Str_4aTable_AbnorC[0],         E2Addr_AbnorC_OADTab,                    E2Addr_AbnorC_OADTabLen,                    E2Addr_AbnorC_Degree,                    Str_4aTable_AbnorC_Len},
/*046*/{FlashStAddr_OpenW,                 FlashEndAddr_OpenW,                 (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_OpenW_OADTab,                     E2Addr_OpenW_OADTabLen,                     E2Addr_OpenW_Degree,                     Str_4aTable_AllLossVol_Len},
/*047*/{FlashStAddr_OpenCW,                FlashEndAddr_OpenCW,                (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_OpenCW_OADTab,                    E2Addr_OpenCW_OADTabLen,                    E2Addr_OpenCW_Degree,                    Str_4aTable_AllLossVol_Len},
/*048*/{FlashStAddr_BuyCurr,               FlashEndAddr_BuyCurr,               (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_BuyCurr_OADTab,                   E2Addr_BuyCurr_OADTabLen,                   E2Addr_BuyCurr_Degree,                   Str_4aTable_AllLossVol_Len},
/*049*/{FlashStAddr_Return_M,              FlashEndAddr_Return_M,              (ulong32)&Str_4aTable_Return_M[0],       E2Addr_Return_M_OADTab,                  E2Addr_Return_M_OADTabLen,                  E2Addr_Return_M_Degree,                  Str_4aTable_Return_M_Len},
/*050*/{FlashStAddr_ConM,                  FlashEndAddr_ConM,                  (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_ConM_OADTab,                      E2Addr_ConM_OADTabLen,                      E2Addr_ConM_Degree,                      Str_4aTable_AllLossVol_Len},
/*051*/{FlashStAddr_RelayFa,               FlashEndAddr_RelayFa,               (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_RelayFa_OADTab,                   E2Addr_RelayFa_OADTabLen,                   E2Addr_RelayFa_Degree,                   Str_4aTable_AllLossVol_Len},
/*052*/{FlashStAddr_PowerFa,               FlashEndAddr_PowerFa,               (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_PowerFa_OADTab,                   E2Addr_PowerFa_OADTabLen,                   E2Addr_PowerFa_Degree,                   Str_4aTable_AllLossVol_Len},
/*053*/{FlashStAddr_RelayOpen,             FlashEndAddr_RelayOpen,             (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_RelayOpen_OADTab,                 E2Addr_RelayOpen_OADTabLen,                 E2Addr_RelayOpen_Degree,                 Str_4aTable_AllLossVol_Len},
/*054*/{FlashStAddr_RelayClose,            FlashEndAddr_RelayClose,            (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_RelayClose_OADTab,                E2Addr_RelayClose_OADTabLen,                E2Addr_RelayClose_Degree,                Str_4aTable_AllLossVol_Len},
#if 0
/*000*/{FlashStAddr_Trend_Rev,             FlashEndAddr_Trend_Rev,             (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Power_Rev_OADTab,                 E2Addr_Power_Rev_OADTabLen,                 E2Addr_Trend_Rev_Degree,                 Str_4aTable_QuaReDeOver_Len},
#endif
/*055*/{FlashStAddr_PFactorT_Over,         FlashEndAddr_PFactorT_Over,         (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_PFactorT_Over_OADTab,             E2Addr_PFactorT_Over_OADTabLen,             E2Addr_PFactorT_Over_Degree,             Str_4aTable_QuaReDeOver_Len},
/*056*/{FlashStAddr_AdjTime,               FlashEndAddr_AdjTime,               (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_AdjTime_OADTab,                   E2Addr_AdjTime_OADTabLen,                   E2Addr_AdjTime_Degree,                   Str_4aTable_AllLossVol_Len},
/*057*/{FlashStAddr_ProgPT,                FlashEndAddr_ProgPT,                (ulong32)&Str_4aTable_ProgPT[0],         E2Addr_ProgPT_OADTab,                    E2Addr_ProgPT_OADTabLen,                    E2Addr_ProgPT_Degree,                    Str_4aTable_ProgPT_Len},
/*058*/{FlashStAddr_ProgTZ,                FlashEndAddr_ProgTZ,                (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_ProgTZ_OADTab,                    E2Addr_ProgTZ_OADTabLen,                    E2Addr_ProgTZ_Degree,                    Str_4aTable_AllLossVol_Len},
/*059*/{FlashStAddr_ProgWRe,               FlashEndAddr_ProgWRe,               (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_ProgWRe_OADTab,                   E2Addr_ProgWRe_OADTabLen,                   E2Addr_ProgWRe_Degree,                   Str_4aTable_AllLossVol_Len},
/*060*/{FlashStAddr_ProgHol,               FlashEndAddr_ProgHol,               (ulong32)&Str_4aTable_ProgHol[0],        E2Addr_ProgHol_OADTab,                   E2Addr_ProgHol_OADTabLen,                   E2Addr_ProgHol_Degree,                   Str_4aTable_ProgHol_Len},
/*061*/{FlashStAddr_ProgAcC,               FlashEndAddr_ProgAcC,               (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_ProgAcC_OADTab,                   E2Addr_ProgAcC_OADTabLen,                   E2Addr_ProgAcC_Degree,                   Str_4aTable_AllLossVol_Len},
/*062*/{FlashStAddr_ProgReC1,              FlashEndAddr_ProgReC1,              (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_ProgReC_OADTab,                   E2Addr_ProgReC_OADTabLen,                   E2Addr_ProgReC1_Degree,                  Str_4aTable_AllLossVol_Len},
/*063*/{FlashStAddr_ProgSettD,             FlashEndAddr_ProgSettD,             (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_ProgSettD_OADTab,                 E2Addr_ProgSettD_OADTabLen,                 E2Addr_ProgSettD_Degree,                 Str_4aTable_AllLossVol_Len},
/*064*/{FlashStAddr_ProgTPara,             FlashEndAddr_ProgTPara,             (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_ProgTPara_OADTab,                 E2Addr_ProgTPara_OADTabLen,                 E2Addr_ProgTPara_Degree,                 Str_4aTable_AllLossVol_Len},
/*065*/{FlashStAddr_ProgLad,               FlashEndAddr_ProgLad,               (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_ProgLad_OADTab,                   E2Addr_ProgLad_OADTabLen,                   E2Addr_ProgLad_Degree,                   Str_4aTable_AllLossVol_Len},
/*066*/{FlashStAddr_ProgKD,                FlashEndAddr_ProgKD,                (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_ProgKD_OADTab,                    E2Addr_ProgKD_OADTabLen,                    E2Addr_ProgKD_Degree,                    Str_4aTable_AllLossVol_Len},
/*067*/{FlashStAddr_MeterFa,               FlashEndAddr_MeterFa,               (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_MeterFa_OADTab,                   E2Addr_MeterFa_OADTabLen,                   E2Addr_MeterFa_Degree,                   Str_4aTable_AllLossVol_Len},
/*068*/{FlashStAddr_ClockFa,               FlashEndAddr_ClockFa,               (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_ClockFa_OADTab,                   E2Addr_ClockFa_OADTabLen,                   E2Addr_ClockFa_Degree,                   Str_4aTable_AllLossVol_Len},
/*069*/{FlashStAddr_BroadcastTime,         FlashEndAddr_BroadcastTime,         (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_BroadcastTime_OADTab,             E2Addr_BroadcastTime_OADTabLen,             E2Addr_BroadcastTime_Degree,             Str_4aTable_AllLossVol_Len},
/*070*/{FlashStAddr_PowerT_Rev,            FlashEndAddr_PowerT_Rev,            (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Power_Rev_OADTab,                 E2Addr_Power_Rev_OADTabLen,                 E2Addr_PowerT_Rev_Degree,                Str_4aTable_QuaReDeOver_Len},
/*071*/{FlashStAddr_NeutralCurrentAbnormal,FlashEndAddr_NeutralCurrentAbnormal,(ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_NeutralCurrentAbnormal_OADTab,    E2Addr_NeutralCurrentAbnormal_OADTabLen,    E2Addr_NeutralCurrentAbnormal_Degree,    Str_4aTable_AllLossVol_Len},
/*072*/{FlashStAddr_PFactorA_Over,         FlashEndAddr_PFactorA_Over,         (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_PFactorT_Over_OADTab,             E2Addr_PFactorT_Over_OADTabLen,             E2Addr_PFactorA_Over_Degree,             Str_4aTable_QuaReDeOver_Len},
/*073*/{FlashStAddr_PFactorB_Over,         FlashEndAddr_PFactorB_Over,         (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_PFactorT_Over_OADTab,             E2Addr_PFactorT_Over_OADTabLen,             E2Addr_PFactorB_Over_Degree,             Str_4aTable_QuaReDeOver_Len},
/*074*/{FlashStAddr_PFactorC_Over,         FlashEndAddr_PFactorC_Over,         (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_PFactorT_Over_OADTab,             E2Addr_PFactorT_Over_OADTabLen,             E2Addr_PFactorC_Over_Degree,             Str_4aTable_QuaReDeOver_Len},
};
#define Str_3dTable_Flash_Len  (sizeof(Str_3d698EventTable_Flash)/sizeof(Str_3dEventTable))

#define C_698FixTimeFreeze 4        /*只有年（后改为阶梯结算冻结）、月、日、时、分覆盖，注意下表顺序，与数据层覆盖程序对应*/
const Str_698FreezeAddrTable Str_698FreezeDataTable[]=
{
	/************冻结数据****************/
	/*	Flash首地址					Flash尾地址	冻结OAD长度(周期)表行号	冻结序号表行号	E2起始地址						E2结束地址								冻结DI2*/
	{FlashStAddr_T_Free,		FlashEndAddr_T_Free,		222,	234,	E2Addr_Min_Free_Flash_Ear,		E2Addr_Min_Free_Flash_Late,		(uchar8)((C_RelatedOAD_Min&Get_DI2},
	{FlashStAddr_H_Free,		FlashEndAddr_H_Free,		223,	235,	E2Addr_H_Free_Flash_Ear,		E2Addr_H_Free_Flash_Late,		(uchar8)((C_RelatedOAD_Hour&Get_DI2},
	{FlashStAddr_D_Free,		FlashEndAddr_D_Free,		224,	236,	E2Addr_D_Free_Flash_Ear,		E2Addr_D_Free_Flash_Late,		(uchar8)((C_RelatedOAD_Day&Get_DI2},
	{FlashStAddr_M_Free,		FlashEndAddr_M_Free,		226,	238,	E2Addr_M_Free_Flash_Ear,		E2Addr_M_Free_Flash_Late,		(uchar8)((C_RelatedOAD_Month&Get_DI2},
	{FlashStAddr_Y_Free,		FlashEndAddr_Y_Free,		227,	239,	E2Addr_Y_Free_Flash_Ear,		E2Addr_Y_Free_Flash_Late,		(uchar8)((C_RelatedOAD_YSettle&Get_DI2},/*更改为阶梯结算冻结*/
	{FlashStAddr_I_Free,		FlashEndAddr_I_Free,		221,	233,	E2Addr_I_Free_Flash_Ear,		E2Addr_I_Free_Flash_Late,		(uchar8)((C_RelatedOAD_Immid&Get_DI2},
	{FlashStAddr_TZ_Free,		FlashEndAddr_TZ_Free,		228,	240,	E2Addr_TZ_Free_Flash_Ear,		E2Addr_TZ_Free_Flash_Late,		(uchar8)((C_RelatedOAD_TimeZone&Get_DI2},
	{FlashStAddr_PT_Free,		FlashEndAddr_PT_Free,		229,	241,	E2Addr_PT_Free_Flash_Ear,		E2Addr_PT_Free_Flash_Late,		(uchar8)((C_RelatedOAD_TimeRegion&Get_DI2},
	{FlashStAddr_R_Free,		FlashEndAddr_R_Free,		230,	242,	E2Addr_R_Free_Flash_Ear,		E2Addr_R_Free_Flash_Late,		(uchar8)((C_RelatedOAD_RateTalbe&Get_DI2},
	{FlashStAddr_L_Free,		FlashEndAddr_L_Free,		231,	243,	E2Addr_L_Free_Flash_Ear,		E2Addr_L_Free_Flash_Late,		(uchar8)((C_RelatedOAD_StepTable&Get_DI2},
	{FlashStAddr_Sett_Free,		FlashEndAddr_Sett_Free,		225,	237,	E2Addr_Sett_Freeze_Flash_Ear,	E2Addr_Sett_Freeze_Flash_Late,	(uchar8)((C_RelatedOAD_Settle&Get_DI2},
};
#define Str_698FreezeDataTable_Len  (sizeof(Str_698FreezeDataTable)/sizeof(Str_698FreezeAddrTable))

const Str_4Table Str_4Table_ProgPT[]=          /************时段表编程事件记录********/
{
	/************时段表编程事件记录********帧长度可能要更改*******/
/*ushort16该标识码对应的数据偏移地址                         uchar8用于区分偏移地址的1个数据标示*/
	{(0),                                                     (uchar8)((CProgPT_NoteC_1    &Get_DI0},
	{(CLProgPT_NoteC_1),                                      (uchar8)((CProgPT_NoteD_1    &Get_DI0},
	{(CLProgPT_NoteC_1+CLProgPT_NoteD_1),                     (uchar8)((CProgPT_NoteE_1    &Get_DI0},
	{(CLProgPT_NoteC_1+CLProgPT_NoteD_1+CLProgPT_NoteE_1),    (uchar8)((CProgPT_NoteF_1    &Get_DI0},

};
#define Str_4Table_ProgPT_Len  (sizeof(Str_4Table_ProgPT)/sizeof(Str_4Table))

const Str_4Table Str_4Table_Rec_Meter[]=          /**********校表记录********/
{
	/************校表事件记录********/
/*ushort16该标识码对应的数据偏移地址         uchar8用于区分偏移地址的1个数据标示*/
	{(0),    (uchar8)((CRec_Meter_Hp_T_1           &Get_DI1},
	{(6),    (uchar8)((CRec_Meter_Bef1_Data_254    &Get_DI1},
};
#define Str_4Table_Rec_Meter_Len  (sizeof(Str_4Table_Rec_Meter)/sizeof(Str_4Table))

const Str_3aTable Str_3aTable_E23RAM[]=
{/*行号      数据存放E2第1处地址                          数据存放RAM地址*/
/*000*/{E2Addr_Pos_Ac_T1_En_Pul_0,           &GV_CurrEnergyData[0][0],             C_CurrDataLen5,           1},
/*001*/{E2Addr_Pos_Ac_T2_En_Pul_0,           &GV_CurrEnergyData[1][0],             C_CurrDataLen5,           1},
/*002*/{E2Addr_Pos_Ac_T3_En_Pul_0,           &GV_CurrEnergyData[2][0],             C_CurrDataLen5,           1},
/*003*/{E2Addr_Pos_Ac_T4_En_Pul_0,           &GV_CurrEnergyData[3][0],             C_CurrDataLen5,           1},
/*004*/{E2Addr_Pos_Ac_T5_En_Pul_0,           &GV_CurrEnergyData[4][0],             C_CurrDataLen5,           1},
/*005*/{E2Addr_Pos_Ac_T6_En_Pul_0,           &GV_CurrEnergyData[5][0],             C_CurrDataLen5,           1},
/*006*/{E2Addr_Pos_Ac_T7_En_Pul_0,           &GV_CurrEnergyData[6][0],             C_CurrDataLen5,           1},
/*007*/{E2Addr_Pos_Ac_T8_En_Pul_0,           &GV_CurrEnergyData[7][0],             C_CurrDataLen5,           1},
/*008*/{E2Addr_Pos_Ac_T9_En_Pul_0,           &GV_CurrEnergyData[8][0],             C_CurrDataLen5,           1},
/*009*/{E2Addr_Pos_Ac_T10_En_Pul_0,          &GV_CurrEnergyData[9][0],             C_CurrDataLen5,           1},
/*010*/{E2Addr_Pos_Ac_T11_En_Pul_0,          &GV_CurrEnergyData[10][0],            C_CurrDataLen5,           1},
/*011*/{E2Addr_Pos_Ac_T12_En_Pul_0,          &GV_CurrEnergyData[11][0],            C_CurrDataLen5,           1},

/*012*/{E2Addr_Rev_Ac_T1_En_Pul_0,           &GV_CurrEnergyData[12][0],            C_CurrDataLen5,           1},
/*013*/{E2Addr_Rev_Ac_T2_En_Pul_0,           &GV_CurrEnergyData[13][0],            C_CurrDataLen5,           1},
/*014*/{E2Addr_Rev_Ac_T3_En_Pul_0,           &GV_CurrEnergyData[14][0],            C_CurrDataLen5,           1},
/*015*/{E2Addr_Rev_Ac_T4_En_Pul_0,           &GV_CurrEnergyData[15][0],            C_CurrDataLen5,           1},
/*016*/{E2Addr_Rev_Ac_T5_En_Pul_0,           &GV_CurrEnergyData[16][0],            C_CurrDataLen5,           1},
/*017*/{E2Addr_Rev_Ac_T6_En_Pul_0,           &GV_CurrEnergyData[17][0],            C_CurrDataLen5,           1},
/*018*/{E2Addr_Rev_Ac_T7_En_Pul_0,           &GV_CurrEnergyData[18][0],            C_CurrDataLen5,           1},
/*019*/{E2Addr_Rev_Ac_T8_En_Pul_0,           &GV_CurrEnergyData[19][0],            C_CurrDataLen5,           1},
/*020*/{E2Addr_Rev_Ac_T9_En_Pul_0,           &GV_CurrEnergyData[20][0],            C_CurrDataLen5,           1},
/*021*/{E2Addr_Rev_Ac_T10_En_Pul_0,          &GV_CurrEnergyData[21][0],            C_CurrDataLen5,           1},
/*022*/{E2Addr_Rev_Ac_T11_En_Pul_0,          &GV_CurrEnergyData[22][0],            C_CurrDataLen5,           1},
/*023*/{E2Addr_Rev_Ac_T12_En_Pul_0,          &GV_CurrEnergyData[23][0],            C_CurrDataLen5,           1},

/*024*/{E2Addr_Qua1_Re_T1_En_Pul_0,          &GV_CurrEnergyData[24][0],            C_CurrDataLen5,           1},
/*025*/{E2Addr_Qua1_Re_T2_En_Pul_0,          &GV_CurrEnergyData[25][0],            C_CurrDataLen5,           1},
/*026*/{E2Addr_Qua1_Re_T3_En_Pul_0,          &GV_CurrEnergyData[26][0],            C_CurrDataLen5,           1},
/*027*/{E2Addr_Qua1_Re_T4_En_Pul_0,          &GV_CurrEnergyData[27][0],            C_CurrDataLen5,           1},
/*028*/{E2Addr_Qua1_Re_T5_En_Pul_0,          &GV_CurrEnergyData[28][0],            C_CurrDataLen5,           1},
/*029*/{E2Addr_Qua1_Re_T6_En_Pul_0,          &GV_CurrEnergyData[29][0],            C_CurrDataLen5,           1},
/*030*/{E2Addr_Qua1_Re_T7_En_Pul_0,          &GV_CurrEnergyData[30][0],            C_CurrDataLen5,           1},
/*031*/{E2Addr_Qua1_Re_T8_En_Pul_0,          &GV_CurrEnergyData[31][0],            C_CurrDataLen5,           1},
/*032*/{E2Addr_Qua1_Re_T9_En_Pul_0,          &GV_CurrEnergyData[32][0],            C_CurrDataLen5,           1},
/*033*/{E2Addr_Qua1_Re_T10_En_Pul_0,         &GV_CurrEnergyData[33][0],            C_CurrDataLen5,           1},
/*034*/{E2Addr_Qua1_Re_T11_En_Pul_0,         &GV_CurrEnergyData[34][0],            C_CurrDataLen5,           1},
/*035*/{E2Addr_Qua1_Re_T12_En_Pul_0,         &GV_CurrEnergyData[35][0],            C_CurrDataLen5,           1},

/*036*/{E2Addr_Qua2_Re_T1_En_Pul_0,          &GV_CurrEnergyData[36][0],            C_CurrDataLen5,           1},
/*037*/{E2Addr_Qua2_Re_T2_En_Pul_0,          &GV_CurrEnergyData[37][0],            C_CurrDataLen5,           1},
/*038*/{E2Addr_Qua2_Re_T3_En_Pul_0,          &GV_CurrEnergyData[38][0],            C_CurrDataLen5,           1},
/*039*/{E2Addr_Qua2_Re_T4_En_Pul_0,          &GV_CurrEnergyData[39][0],            C_CurrDataLen5,           1},
/*040*/{E2Addr_Qua2_Re_T5_En_Pul_0,          &GV_CurrEnergyData[40][0],            C_CurrDataLen5,           1},
/*041*/{E2Addr_Qua2_Re_T6_En_Pul_0,          &GV_CurrEnergyData[41][0],            C_CurrDataLen5,           1},
/*042*/{E2Addr_Qua2_Re_T7_En_Pul_0,          &GV_CurrEnergyData[42][0],            C_CurrDataLen5,           1},
/*043*/{E2Addr_Qua2_Re_T8_En_Pul_0,          &GV_CurrEnergyData[43][0],            C_CurrDataLen5,           1},
/*044*/{E2Addr_Qua2_Re_T9_En_Pul_0,          &GV_CurrEnergyData[44][0],            C_CurrDataLen5,           1},
/*045*/{E2Addr_Qua2_Re_T10_En_Pul_0,         &GV_CurrEnergyData[45][0],            C_CurrDataLen5,           1},
/*046*/{E2Addr_Qua2_Re_T11_En_Pul_0,         &GV_CurrEnergyData[46][0],            C_CurrDataLen5,           1},
/*047*/{E2Addr_Qua2_Re_T12_En_Pul_0,         &GV_CurrEnergyData[47][0],            C_CurrDataLen5,           1},

/*048*/{E2Addr_Qua3_Re_T1_En_Pul_0,          &GV_CurrEnergyData[48][0],            C_CurrDataLen5,           1},
/*049*/{E2Addr_Qua3_Re_T2_En_Pul_0,          &GV_CurrEnergyData[49][0],            C_CurrDataLen5,           1},
/*050*/{E2Addr_Qua3_Re_T3_En_Pul_0,          &GV_CurrEnergyData[50][0],            C_CurrDataLen5,           1},
/*051*/{E2Addr_Qua3_Re_T4_En_Pul_0,          &GV_CurrEnergyData[51][0],            C_CurrDataLen5,           1},
/*052*/{E2Addr_Qua3_Re_T5_En_Pul_0,          &GV_CurrEnergyData[52][0],            C_CurrDataLen5,           1},
/*053*/{E2Addr_Qua3_Re_T6_En_Pul_0,          &GV_CurrEnergyData[53][0],            C_CurrDataLen5,           1},
/*054*/{E2Addr_Qua3_Re_T7_En_Pul_0,          &GV_CurrEnergyData[54][0],            C_CurrDataLen5,           1},
/*055*/{E2Addr_Qua3_Re_T8_En_Pul_0,          &GV_CurrEnergyData[55][0],            C_CurrDataLen5,           1},
/*056*/{E2Addr_Qua3_Re_T9_En_Pul_0,          &GV_CurrEnergyData[56][0],            C_CurrDataLen5,           1},
/*057*/{E2Addr_Qua3_Re_T10_En_Pul_0,         &GV_CurrEnergyData[57][0],            C_CurrDataLen5,           1},
/*058*/{E2Addr_Qua3_Re_T11_En_Pul_0,         &GV_CurrEnergyData[58][0],            C_CurrDataLen5,           1},
/*059*/{E2Addr_Qua3_Re_T12_En_Pul_0,         &GV_CurrEnergyData[59][0],            C_CurrDataLen5,           1},

/*060*/{E2Addr_Qua4_Re_T1_En_Pul_0,          &GV_CurrEnergyData[60][0],            C_CurrDataLen5,           1},
/*061*/{E2Addr_Qua4_Re_T2_En_Pul_0,          &GV_CurrEnergyData[61][0],            C_CurrDataLen5,           1},
/*062*/{E2Addr_Qua4_Re_T3_En_Pul_0,          &GV_CurrEnergyData[62][0],            C_CurrDataLen5,           1},
/*063*/{E2Addr_Qua4_Re_T4_En_Pul_0,          &GV_CurrEnergyData[63][0],            C_CurrDataLen5,           1},
/*064*/{E2Addr_Qua4_Re_T5_En_Pul_0,          &GV_CurrEnergyData[64][0],            C_CurrDataLen5,           1},
/*065*/{E2Addr_Qua4_Re_T6_En_Pul_0,          &GV_CurrEnergyData[65][0],            C_CurrDataLen5,           1},
/*066*/{E2Addr_Qua4_Re_T7_En_Pul_0,          &GV_CurrEnergyData[66][0],            C_CurrDataLen5,           1},
/*067*/{E2Addr_Qua4_Re_T8_En_Pul_0,          &GV_CurrEnergyData[67][0],            C_CurrDataLen5,           1},
/*068*/{E2Addr_Qua4_Re_T9_En_Pul_0,          &GV_CurrEnergyData[68][0],            C_CurrDataLen5,           1},
/*069*/{E2Addr_Qua4_Re_T10_En_Pul_0,         &GV_CurrEnergyData[69][0],            C_CurrDataLen5,           1},
/*070*/{E2Addr_Qua4_Re_T11_En_Pul_0,         &GV_CurrEnergyData[70][0],            C_CurrDataLen5,           1},
/*071*/{E2Addr_Qua4_Re_T12_En_Pul_0,         &GV_CurrEnergyData[71][0],            C_CurrDataLen5,           1},

/*072*/{E2Addr_PosA_Ac_En_Pul_0,             &GV_CurrEnergyData[72][0],            C_CurrDataLen5,           1},
/*073*/{E2Addr_RevA_Ac_En_Pul_0,             &GV_CurrEnergyData[73][0],            C_CurrDataLen5,           1},
/*074*/{E2Addr_Qua1A_Re_En_Pul_0,            &GV_CurrEnergyData[74][0],            C_CurrDataLen5,           1},
/*075*/{E2Addr_Qua2A_Re_En_Pul_0,            &GV_CurrEnergyData[75][0],            C_CurrDataLen5,           1},
/*076*/{E2Addr_Qua3A_Re_En_Pul_0,            &GV_CurrEnergyData[76][0],            C_CurrDataLen5,           1},
/*077*/{E2Addr_Qua4A_Re_En_Pul_0,            &GV_CurrEnergyData[77][0],            C_CurrDataLen5,           1},

/*078*/{E2Addr_PosB_Ac_En_Pul_0,             &GV_CurrEnergyData[78][0],            C_CurrDataLen5,           1},
/*079*/{E2Addr_RevB_Ac_En_Pul_0,             &GV_CurrEnergyData[79][0],            C_CurrDataLen5,           1},
/*080*/{E2Addr_Qua1B_Re_En_Pul_0,            &GV_CurrEnergyData[80][0],            C_CurrDataLen5,           1},
/*081*/{E2Addr_Qua2B_Re_En_Pul_0,            &GV_CurrEnergyData[81][0],            C_CurrDataLen5,           1},
/*082*/{E2Addr_Qua3B_Re_En_Pul_0,            &GV_CurrEnergyData[82][0],            C_CurrDataLen5,           1},
/*083*/{E2Addr_Qua4B_Re_En_Pul_0,            &GV_CurrEnergyData[83][0],            C_CurrDataLen5,           1},

/*084*/{E2Addr_PosC_Ac_En_Pul_0,             &GV_CurrEnergyData[84][0],            C_CurrDataLen5,           1},
/*085*/{E2Addr_RevC_Ac_En_Pul_0,             &GV_CurrEnergyData[85][0],            C_CurrDataLen5,           1},
/*086*/{E2Addr_Qua1C_Re_En_Pul_0,            &GV_CurrEnergyData[86][0],            C_CurrDataLen5,           1},
/*087*/{E2Addr_Qua2C_Re_En_Pul_0,            &GV_CurrEnergyData[87][0],            C_CurrDataLen5,           1},
/*088*/{E2Addr_Qua3C_Re_En_Pul_0,            &GV_CurrEnergyData[88][0],            C_CurrDataLen5,           1},
/*089*/{E2Addr_Qua4C_Re_En_Pul_0,            &GV_CurrEnergyData[89][0],            C_CurrDataLen5,           1},

/*090*/{E2Addr_SC_Com_Ac_Tol_En_Pul_0,       &GV_CurrEnergyData[90][0],            C_CurrDataLen5,           1},
/*091*/{E2Addr_M_Com_Ac_Tol_En_Pul_0,        &GV_CurrEnergyData[91][0],            C_CurrDataLen5,           1},
/*092*/{E2Addr_Y_Com_Ac_Tol_En_Pul_0,        &GV_CurrEnergyData[92][0],            C_CurrDataLen5,           1},
/*093*/{E2Addr_ChargeBal_Hex_Deal,           &GV_CurrEnergyData[93][0],            C_CurrDataLen5,           1},
/*094*/{E2Addr_OverDraft_Hex_Deal,           &GV_CurrEnergyData[94][0],            C_CurrDataLen5,           1},

/*095*/{E2Addr_BroadcastTimeOffset_Min,      &GV_BroadcastTimeOffset_Min[0],       CLBroadcastTimeOffset_Min,      1},
/*096*/{E2Addr_BroadcastTimeOffset_Max,      &GV_BroadcastTimeOffset_Max[0],       CLBroadcastTimeOffset_Max,      1},

/*097*/{E2Addr_Demand_Cycle,                 &GV_Demand_Cycle[0],                  CLDemand_Cycle,                 1},
/*098*/{E2Addr_Sliding_Time,                 &GV_Sliding_Time[0],                  CLSliding_Time,                 1},

/*099*/{E2Addr_Change_TZ_Time,               &GV_Change_TZ_Time[0],                CLChange_TZ_Time,               1},
/*100*/{E2Addr_Change_PT_Time,               &GV_Change_PT_Time[0],                CLChange_PT_Time,               1},
/*101*/{E2Addr_Change_Rate,                  &GV_Change_Rate[0],                   CLChange_Rate,                  1},
/*102*/{E2Addr_Change_Ladder,                &GV_Change_Ladder[0],                 CLChange_Ladder,                1},

/*103*/{E2Addr_Year_Zone_Num,                &GV_Year_Zone_Num[0],                 CLYear_Zone_Num,                1},
/*104*/{E2Addr_Day_Table_Num,                &GV_Day_Table_Num[0],                 CLDay_Table_Num,                1},
/*105*/{E2Addr_Day_Time_Num,                 &GV_Day_Time_Num[0],                  CLDay_Time_Num,                 1},
/*106*/{E2Addr_Rate_Num,                     &GV_Rate_Num[0],                      CLRate_Num,                     1},
/*107*/{E2Addr_Holiday_Num,                  &GV_Holiday_Num[0],                   CLHoliday_Num,                  1},
/*108*/{E2Addr_Step_Num,                     &GV_Step_Num[0],                      CLStep_Num,                     1},

/*109*/{E2Addr_Per_Dis_Screen_Time,          &GV_Per_Dis_Screen_Time[0],           CLPer_Dis_Screen_Time,          1},
/*110*/{E2Addr_Auto_Dis_Screen_Num,          &GV_Auto_Dis_Screen_Num[0],           CLAuto_Dis_Screen_Num,          1},
/*111*/{E2Addr_Auto_Dis_Screen_MaxNum,       &GV_Auto_Dis_Screen_MaxNum[0],        CLAuto_Dis_Screen_MaxNum,       1},

/*112*/{E2Addr_Perkey_Dis_Screen_Time,       &GV_Perkey_Dis_Screen_Time[0],        CLPerkey_Dis_Screen_Time,       1},
/*113*/{E2Addr_Key_CycDis_Screen_Num,        &GV_Key_CycDis_Screen_Num[0],         CLKey_CycDis_Screen_Num,        1},
/*114*/{E2Addr_Key_CycDis_Screen_MaxNum,     &GV_Key_CycDis_Screen_MaxNum[0],      CLKey_CycDis_Screen_MaxNum,     1},

/*115*/{E2Addr_PowerOn_Dis_All_Time,         &GV_PowerOn_Dis_All_Time[0],          CLPowerOn_Dis_All_Time,         1},
/*116*/{E2Addr_BacklightTime,                &GV_BacklightTime[0],                 CLBacklightTime,                1},
/*117*/{E2Addr_SViewBacklightTime,           &GV_SViewBacklightTime[0],            CLSViewBacklightTime,           1},
/*118*/{E2Addr_NEScreenDisplay,              &GV_NEScreenDisplay[0],               CLNEScreenDisplay,              1},
/*119*/{E2Addr_Energy_Decimal_Num,           &GV_Energy_Decimal_Num[0],            CLEnergy_Decimal_Num,           1},
/*120*/{E2Addr_Power_Decimal_Num,            &GV_Power_Decimal_Num[0],             CLPower_Decimal_Num,            1},
/*121*/{E2Addr_1And2Display,                 &GV_1And2Display[0],                  CL1And2Display,                 1},

/*122*/{E2Addr_Ratio_Curr_Tran,              &GV_Ratio_Curr_Tran[0],               CLRatio_Curr_Tran,              1},
/*123*/{E2Addr_Ratio_Vol_Tran,               &GV_Ratio_Vol_Tran[0],                CLRatio_Vol_Tran,               1},

/*124*/{E2Addr_Active_Com_State,             &GV_Active_Com_State[0][0],           CLActive_Com_State,             1},
/*125*/{E2Addr_Reactive_Com_State1,          &GV_Active_Com_State[1][0],           CLReactive_Com_State1,          1},
/*126*/{E2Addr_Reactive_Com_State2,          &GV_Active_Com_State[2][0],           CLReactive_Com_State2,          1},

/*127*/{E2Addr_Mod_InFr_Baud,                &GV_Mod_InFr_Baud[0],                 CLMod_InFr_Baud,                1},
/*128*/{E2Addr_One485_Baud  ,                &GV_One485_Baud[0],                   CLOne485_Baud,                  1},
/*129*/{E2Addr_Two485_Baud  ,                &GV_Two485_Baud[0],                   CLTwo485_Baud,                  1},
/*130*/{E2Addr_Modular_Baud ,                &GV_Modular_Baud[0],                  CLModular_Baud,                 1},

/*131*/{E2Addr_Week_RestDay ,                &GV_Week_RestDay[0][0],               CLWeek_RestDay,                 1},
/*132*/{E2Addr_Week_RestDay_DTable,          &GV_Week_RestDay[1][0],               CLWeek_RestDay_DTable,          1},

/*133*/{E2Addr_Alam1_Money,                  &GV_Alam1_Money[0][0],                CLAlam1_Money,                  2},
/*134*/{E2Addr_OverDraft_Money,              &GV_Alam1_Money[2][0],                CLOverDraft_Money,              3},

/*135*/{E2Addr_Comm_Address,                 &GV_Comm_Address[0],                  CLComm_Address,                 1},

/*136*/{E2Addr_Relay_Open_CurrTreshold,      &GV_Relay_Open_CurrTreshold[0],       CLRelay_Open_CurrTreshold,      1},

/*137*/{E2Addr_Current_Rate1_Price,          &GV_Current_Rate_Price[0][0],         CLCurrent_Rate1_Price,          C_MaxRatesNum},
/*138*/{E2Addr_BackUp_Rate1_Price,           &GV_BackUp_Rate_Price[0][0],          CLBackUp_Rate1_Price,           C_MaxRatesNum},
/*139*/{E2Addr_Current_Ladder_Table,         &GV_Current_Ladder_Table[0],          CLCurrent_Ladder_Table,         1},
/*140*/{E2Addr_BackUp_Ladder_Table,          &GV_BackUp_Ladder_Table[0],           CLBackUp_Ladder_Table,          1},

/*141*/{E2Addr_LossVolage_Vol_UpLim,         &GV_LossVolage_Vol_UpLim[0],          CLLossVolage_Vol_UpLim,         1},
/*142*/{E2Addr_LossVolage_Vol_LowLim,        &GV_LossVolage_Vol_LowLim[0],         CLLossVolage_Vol_LowLim,        1},
/*143*/{E2Addr_LossVolage_Curr_LowLim,       &GV_LossVolage_Curr_LowLim[0],        CLLossVolage_Curr_LowLim,       1},
/*144*/{E2Addr_LossVolage_Delay_T,           &GV_LossVolage_Delay_T[0],            CLLossVolage_Delay_T,           1},

/*145*/{E2Addr_LowVolage_Vol_UpLim,          &GV_LowVolage_Vol_UpLim[0],           CLLowVolage_Vol_UpLim,          1},
/*146*/{E2Addr_LowVolage_Delay_T,            &GV_LowVolage_Delay_T[0],             CLLowVolage_Delay_T,            1},

/*147*/{E2Addr_OverVolage_Vol_LowLim,        &GV_OverVolage_Vol_LowLim[0],         CLOverVolage_Vol_LowLim,        1},
/*148*/{E2Addr_OverVolage_Delay_T,           &GV_OverVolage_Delay_T[0],            CLOverVolage_Delay_T,           1},

/*149*/{E2Addr_BreakVol_Vol_UpLim,           &GV_BreakVol_Vol_UpLim[0],            CLBreakVol_Vol_UpLim,           1},
/*150*/{E2Addr_BreakVol_Curr_UpLim,          &GV_BreakVol_Curr_UpLim[0],           CLBreakVol_Curr_UpLim,          1},
/*151*/{E2Addr_BreakVol_Delay_T,             &GV_BreakVol_Delay_T[0],              CLBreakVol_Delay_T,             1},

/*152*/{E2Addr_NoBal_Vol_Lim,                &GV_NoBal_Vol_Lim[0],                 CLNoBal_Vol_Lim,                1},
/*153*/{E2Addr_NoBal_Vol_Delay_T,            &GV_NoBal_Vol_Delay_T[0],             CLNoBal_Vol_Delay_T,            1},

/*154*/{E2Addr_NoBal_Curr_Lim,               &GV_NoBal_Curr_Lim[0],                CLNoBal_Curr_Lim,               1},
/*155*/{E2Addr_NoBal_Curr_Delay_T,           &GV_NoBal_Curr_Delay_T[0],            CLNoBal_Curr_Delay_T,           1},

/*156*/{E2Addr_SeriNoBal_Curr_Lim,           &GV_SeriNoBal_Curr_Lim[0],            CLSeriNoBal_Curr_Lim,           1},
/*157*/{E2Addr_SeriNoBal_Curr_Delay_T,       &GV_SeriNoBal_Curr_Delay_T[0],        CLSeriNoBal_Curr_Delay_T,       1},

/*158*/{E2Addr_LossCurr_Vol_LowLim,          &GV_LossCurr_Vol_LowLim[0],           CLLossCurr_Vol_LowLim,          1},
/*159*/{E2Addr_LossCurr_Curr_UpLim,          &GV_LossCurr_Curr_UpLim[0],           CLLossCurr_Curr_UpLim,          1},
/*160*/{E2Addr_LossCurr_Curr_LowLim,         &GV_LossCurr_Curr_LowLim[0],          CLLossCurr_Curr_LowLim,         1},
/*161*/{E2Addr_LossCurr_Delay_T,             &GV_LossCurr_Delay_T[0],              CLLossCurr_Delay_T,             1},

/*162*/{E2Addr_OverCurr_Curr_LowLim,         &GV_OverCurr_Curr_LowLim[0],          CLOverCurr_Curr_LowLim,         1},
/*163*/{E2Addr_OverCurr_Delay_T,             &GV_OverCurr_Delay_T[0],              CLOverCurr_Delay_T,             1},

/*164*/{E2Addr_BreakCurr_Vol_LowLim,         &GV_BreakCurr_Vol_LowLim[0],          CLBreakCurr_Vol_LowLim,         1},
/*165*/{E2Addr_BreakCurr_Curr_UpLim,         &GV_BreakCurr_Curr_UpLim[0],          CLBreakCurr_Curr_UpLim,         1},
/*166*/{E2Addr_BreakCurr_Delay_T,            &GV_BreakCurr_Delay_T[0],             CLBreakCurr_Delay_T,            1},

/*167*/{E2Addr_OverLoad_AcPower_LowLim,      &GV_OverLoad_AcPower_LowLim[0],       CLOverLoad_AcPower_LowLim,      1},
/*168*/{E2Addr_OverLoad_Delay_T,             &GV_OverLoad_Delay_T[0],              CLOverLoad_Delay_T,             1},

/*169*/{E2Addr_PosAcDemandOv_De_LowLim,      &GV_PosAcDemandOv_De_LowLim[0],       CLPosAcDemandOv_De_LowLim,      1},
/*170*/{E2Addr_PosAcDemandOv_Delay_T,        &GV_PosAcDemandOv_Delay_T[0],         CLPosAcDemandOv_Delay_T,        1},
/*171*/{E2Addr_RevAcDemandOv_De_LowLim,      &GV_RevAcDemandOv_De_LowLim[0],       CLRevAcDemandOv_De_LowLim,      1},
/*172*/{E2Addr_RevAcDemandOv_Delay_T,        &GV_RevAcDemandOv_Delay_T[0],         CLRevAcDemandOv_Delay_T,        1},
/*173*/{E2Addr_ReDemandOv_De_LowLim,         &GV_ReDemandOv_De_LowLim[0],          CLReDemandOv_De_LowLim,         1},
/*174*/{E2Addr_ReDemandOv_Delay_T,           &GV_ReDemandOv_Delay_T[0],            CLReDemandOv_Delay_T,           1},

/*175*/{E2Addr_PowerFactor_LowLim,           &GV_PowerFactor_LowLim[0],            CLPowerFactor_LowLim,           1},
/*176*/{E2Addr_PowerFactor_Delay_T,          &GV_PowerFactor_Delay_T[0],           CLPowerFactor_Delay_T,          1},

/*177*/{E2Addr_PowerRev_AcPower_LowLim,      &GV_PowerRev_AcPower_LowLim[0],       CLPowerRev_AcPower_LowLim,      1},
/*178*/{E2Addr_PowerRev_Delay_T,             &GV_PowerRev_Delay_T[0],              CLPowerRev_Delay_T,             1},

/*179*/{E2Addr_NeutralAbnormal_Curr_LowLim,  &GV_NeutralAbnormal_Curr_LowLim[0],   CLNeutralAbnormal_Curr_LowLim,  1},
/*180*/{E2Addr_NeutralUnbalanceRate,         &GV_NeutralUnbalanceRate[0],          CLNeutralUnbalanceRate,         1},
/*181*/{E2Addr_NeutralAbnormal_Delay_T,      &GV_NeutralAbnormal_Delay_T[0],       CLNeutralAbnormal_Delay_T,      1},

/*182*/{E2Addr_ReversedVoltage_Delay_T,      &GV_ReversedVoltage_Delay_T[0],       CLReversedVoltage_Delay_T,      1},
/*183*/{E2Addr_ReversedCurrent_Delay_T,      &GV_ReversedCurrent_Delay_T[0],       CLReversedCurrent_Delay_T,      1},
/*184*/{E2Addr_PowerOff_Delay_T,             &GV_PowerOff_Delay_T[0],              CLPowerOff_Delay_T,             1},
/*185*/{E2Addr_Aux_Pow_Down_Delay_T,         &GV_Aux_Pow_Down_Delay_T[0],          CLAux_Pow_Down_Delay_T,         1},
/*186*/{E2Addr_ClockFa_Delay_T,              &GV_ClockFa_Delay_T[0],               CLClockFa_Delay_T,              1},
/*187*/{E2Addr_MeterFa_Delay_T,              &GV_MeterFa_Delay_T[0],               CLMeterFa_Delay_T,              1},

/*188*/{E2Addr_Voltage_UpLim,                &GV_Voltage_UpLim[0],                 CLVoltage_UpLim,                1},
/*189*/{E2Addr_Voltage_LowLim,               &GV_Voltage_LowLim[0],                CLVoltage_LowLim,               1},
/*190*/{E2Addr_Volage_Check_UpLim,           &GV_Volage_Check_UpLim[0][0],         CLVolage_Check_UpLim,           2},

/*191*/{E2Addr_Volage_Type,                  &GV_Volage_Type[0][0],                CLVolage_Type,                  8},
/*192*/{E2Addr_Start_Up_Current,             &GV_Start_Up_Current[0],              CLStart_Up_Current,             1},
/*193*/{E2Addr_Start_Up_Power,               &GV_Start_Up_Power[0],                CLStart_Up_Power,               1},
/*194*/{E2Addr_Volage_Abnor_Vol,             &GV_Volage_Abnor_Vol[0],              CLVolage_Abnor_Vol,             1},
/*195*/{E2Addr_Loss_Volage_Curr,             &GV_Loss_Volage_Curr[0][0],           CLLoss_Volage_Curr,             5},
/*196*/{E2Addr_Pluse_Most__Lim,              &GV_Pluse_Most__Lim[0],               CLPluse_Most__Lim,              1},
/*197*/{E2Addr_Curr_Ratio_30A,               &GV_Curr_Ratio_30A[0],                CLCurr_Ratio_30A,               1},
/*198*/{E2Addr_Pulse_Constant,               &GV_Pulse_Constant[0],                CLPulse_Constant,               1},
/*199*/{E2Addr_SoftIJ_Valid_Time,            &GV_SoftIJ_Valid_Time[0],             CLSoftIJ_Valid_Time,            1},
/*200*/{E2Addr_Extern_Relay_PulW,            &GV_Extern_Relay_PulW[0],             CLExtern_Relay_PulW,            1},
/*201*/{E2Addr_MeterRunStatic,               &GV_MeterRunStatic[0],                CLMeterRunStatic,               1},
/*202*/{E2Addr_Alarm_Status,                 &GV_Alarm_Status[0],                  CLAlarm_Status,                 1},
/*203*/{E2Addr_Rst_ReportState_Timer,        &GV_Rst_ReportState_Timer[0],         CLRst_ReportState_Timer,        1},
/*204*/{E2Addr_Relay_Open_CurrTimer,         &GV_Relay_Open_CurrTimer[0],          CLRelay_Open_CurrTimer,         1},
/*205*/{E2Addr__IRAuth_Timer,                &GV__IRAuth_Timer[0],                 CL_IRAuth_Timer,                1},
/*206*/{E2Addr_Relay_RemoteOrder,            &GV_Relay_RemoteOrder[0],             CLRelay_RemoteOrder,            1},
/*207*/{E2Addr_Relay_State,                  &GV_Relay_State[0],                   CLRelay_State,                  1},
/*208*/{E2Addr_Relay_LocalOrder,             &GV_Relay_LocalOrder[0],              CLRelay_LocalOrder,             1},
/*209*/{E2Addr_Remote_Local_State,           &GV_Remote_Local_State[0],            CLRemote_Local_State,           1},
/*210*/{E2Addr_Drive_Report_Mode,            &GV_Drive_Report_Mode[0],             CLDrive_Report_Mode,            1},

/*211*/{E2Addr_AppProInformation,            &GV_AppProInformation[0],             CLAppProInformation,            1},
/*212*/{E2Addr_AppMaxReAPDU,                 &GV_AppMaxReAPDU[0],                  CLAppMaxReAPDU,                 1},
/*213*/{E2Addr_AppMaxSeAPDU,                 &GV_AppMaxSeAPDU[0],                  CLAppMaxSeAPDU,                 1},
/*214*/{E2Addr_AppMaxHandleAPDU,             &GV_AppMaxHandleAPDU[0],              CLAppMaxHandleAPDU,             1},
/*215*/{E2Addr_AppProConsistency,            &GV_AppProConsistency[0],             CLAppProConsistency,            1},
/*216*/{E2Addr_AppFunConsistency,            &GV_AppFunConsistency[0],             CLAppFunConsistency,            1},
/*217*/{E2Addr_AppStaticTimeout,             &GV_AppStaticTimeout[0],              CLAppStaticTimeout,             1},

/*218*/{E2Addr_AppStaticTimeout_termal,      &GV_AppStaticTimeout_terminal[0],     CLAppStaticTimeout,             1},

/*219*/{E2Addr_ConAutheMechanism,            &GV_ConAutheMechanism[0],             CLConAutheMechanism,            1},
/*220*/{E2Addr_SafeModePara,                 &GV_SafeModePara[0],                  CLSafeModePara,                 1},

/*221*/{E2Addr_I_Free_OADTabLen_T,           &GV_Free_OADTabLen_T[0][0],           CLI_Free_OADTabLen_T,           1},
/*222*/{E2Addr_Min_Free_OADTabLen_T,         &GV_Free_OADTabLen_T[1][0],           CLI_Free_OADTabLen_T,           1},
/*223*/{E2Addr_H_Free_OADTabLen_T,           &GV_Free_OADTabLen_T[2][0],           CLI_Free_OADTabLen_T,           1},
/*224*/{E2Addr_D_Free_OADTabLen_T,           &GV_Free_OADTabLen_T[3][0],           CLI_Free_OADTabLen_T,           1},
/*225*/{E2Addr_Sett_Free_OADTabLen_T,        &GV_Free_OADTabLen_T[4][0],           CLI_Free_OADTabLen_T,           1},
/*226*/{E2Addr_M_Free_OADTabLen_T,           &GV_Free_OADTabLen_T[5][0],           CLI_Free_OADTabLen_T,           1},
/*227*/{E2Addr_Y_Free_OADTabLen_T,           &GV_Free_OADTabLen_T[6][0],           CLI_Free_OADTabLen_T,           1},
/*228*/{E2Addr_TZ_Free_OADTabLen_T,          &GV_Free_OADTabLen_T[7][0],           CLI_Free_OADTabLen_T,           1},
/*229*/{E2Addr_PT_Free_OADTabLen_T,          &GV_Free_OADTabLen_T[8][0],           CLI_Free_OADTabLen_T,           1},
/*230*/{E2Addr_R_Free_OADTabLen_T,           &GV_Free_OADTabLen_T[9][0],           CLI_Free_OADTabLen_T,           1},
/*231*/{E2Addr_L_Free_OADTabLen_T,           &GV_Free_OADTabLen_T[10][0],          CLI_Free_OADTabLen_T,           1},
/*232*/{E2Addr_D_Free_StartTime,             &GV_Free_StartTime[0][0],             CLD_Free_StartTime,             3},

/*233*/{E2Addr_I_Free_OADTab,                &GV_Free_OADTab[0][0],                C_698Free_OADTabLen,            1},
/*234*/{E2Addr_Min_Free_OADTab,              &GV_Free_OADTab[1][0],                C_698Free_OADTabLen,            1},
/*235*/{E2Addr_H_Free_OADTab,                &GV_Free_OADTab[2][0],                C_698Free_OADTabLen,            1},
/*236*/{E2Addr_D_Free_OADTab,                &GV_Free_OADTab[3][0],                C_698Free_OADTabLen,            1},
/*237*/{E2Addr_Sett_Free_OADTab,             &GV_Free_OADTab[4][0],                C_698Free_OADTabLen,            1},
/*238*/{E2Addr_M_Free_OADTab,                &GV_Free_OADTab[5][0],                C_698Free_OADTabLen,            1},
/*239*/{E2Addr_Y_Free_OADTab,                &GV_Free_OADTab[6][0],                C_698Free_OADTabLen,            1},
/*240*/{E2Addr_TZ_Free_OADTab,               &GV_Free_OADTab[7][0],                C_698Free_OADTabLen,            1},
/*241*/{E2Addr_PT_Free_OADTab,               &GV_Free_OADTab[8][0],                C_698Free_OADTabLen,            1},
/*242*/{E2Addr_R_Free_OADTab,                &GV_Free_OADTab[9][0],                C_698Free_OADTabLen,            1},
/*243*/{E2Addr_L_Free_OADTab,                &GV_Free_OADTab[10][0],               C_698Free_OADTabLen,            1},

/*244*/{E2Addr_LossVolage_Report_Mode,       &GV_LossVolage_Report_Mode[0],        CLReport_Mode,                  1},
/*245*/{E2Addr_LowVolage_Report_Mode,        &GV_LowVolage_Report_Mode[0],         CLReport_Mode,                  1},
/*246*/{E2Addr_OverVolage_Report_Mode,       &GV_OverVolage_Report_Mode[0],        CLReport_Mode,                  1},
/*247*/{E2Addr_BreakVol_Report_Mode,         &GV_BreakVol_Report_Mode[0],          CLReport_Mode,                  1},
/*248*/{E2Addr_LossCurr_Report_Mode,         &GV_LossCurr_Report_Mode[0],          CLReport_Mode,                  1},
/*249*/{E2Addr_OverCurr_Report_Mode,         &GV_OverCurr_Report_Mode[0],          CLReport_Mode,                  1},
/*250*/{E2Addr_BreakCurr_Report_Mode,        &GV_BreakCurr_Report_Mode[0],         CLReport_Mode,                  1},
/*251*/{E2Addr_PowerRev_Report_Mode,         &GV_PowerRev_Report_Mode[0],          CLReport_Mode,                  1},
/*252*/{E2Addr_OverLoad_Report_Mode,         &GV_OverLoad_Report_Mode[0],          CLReport_Mode,                  1},
/*253*/{E2Addr_PosAcDemandOv_Report_Mode,    &GV_PosAcDemandOv_Report_Mode[0],     CLReport_Mode,                  1},
/*254*/{E2Addr_RevAcDemandOv_Report_Mode,    &GV_RevAcDemandOv_Report_Mode[0],     CLReport_Mode,                  1},
/*255*/{E2Addr_ReDemandOv_Report_Mode,       &GV_ReDemandOv_Report_Mode[0],        CLReport_Mode,                  1},
/*256*/{E2Addr_PowerFactor_Report_Mode,      &GV_PowerFactor_Report_Mode[0],       CLReport_Mode,                  1},
/*257*/{E2Addr_AllLossVolage_Report_Mode,    &GV_AllLossVolage_Report_Mode[0],     CLReport_Mode,                  1},
/*258*/{E2Addr_AuxPowDown_Report_Mode,       &GV_AuxPowDown_Report_Mode[0],        CLReport_Mode,                  1},
/*259*/{E2Addr_ReversedVoltage_Report_Mode,  &GV_ReversedVoltage_Report_Mode[0],   CLReport_Mode,                  1},
/*260*/{E2Addr_ReversedCurrent_Report_Mode,  &GV_ReversedCurrent_Report_Mode[0],   CLReport_Mode,                  1},
/*261*/{E2Addr_PowerOff_Report_Mode,         &GV_PowerOff_Report_Mode[0],          CLReport_Mode,                  1},
/*262*/{E2Addr_Program_Report_Mode,          &GV_Program_Report_Mode[0],           CLReport_Mode,                  1},
/*263*/{E2Addr_TolClear_Report_Mode,         &GV_TolClear_Report_Mode[0],          CLReport_Mode,                  1},
/*264*/{E2Addr_DemandClear_Report_Mode,      &GV_DemandClear_Report_Mode[0],       CLReport_Mode,                  1},
/*265*/{E2Addr_EventClear_Report_Mode,       &GV_EventClear_Report_Mode[0],        CLReport_Mode,                  1},
/*266*/{E2Addr_AdjTime_Report_Mode,          &GV_AdjTime_Report_Mode [0],          CLReport_Mode,                  1},
/*267*/{E2Addr_ProgPT_Report_Mode,           &GV_ProgPT_Report_Mode[0],            CLReport_Mode,                  1},
/*268*/{E2Addr_ProgPZ_Report_Mode,           &GV_ProgPZ_Report_Mode[0],            CLReport_Mode,                  1},
/*269*/{E2Addr_ProgWRe_Report_Mode,          &GV_ProgWRe_Report_Mode[0],           CLReport_Mode,                  1},
/*270*/{E2Addr_ProgSettD_Report_Mode,        &GV_ProgSettD_Report_Mode[0],         CLReport_Mode,                  1},
/*271*/{E2Addr_OpenW_Report_Mode,            &GV_OpenW_Report_Mode[0],             CLReport_Mode,                  1},
/*272*/{E2Addr_OpenCW_Report_Mode,           &GV_OpenCW_Report_Mode[0],            CLReport_Mode,                  1},
/*273*/{E2Addr_NoBalVol_Report_Mode,         &GV_NoBalVol_Report_Mode[0],          CLReport_Mode,                  1},
/*274*/{E2Addr_NoBalCurr_Report_Mode,        &GV_NoBalCurr_Report_Mode[0],         CLReport_Mode,                  1},
/*275*/{E2Addr_RelayOpen_Report_Mode,        &GV_RelayOpen_Report_Mode[0],         CLReport_Mode,                  1},
/*276*/{E2Addr_RelayClose_Report_Mode,       &GV_RelayClose_Report_Mode[0],        CLReport_Mode,                  1},
/*277*/{E2Addr_ProgHol_Report_Mode,          &GV_ProgHol_Report_Mode[0],           CLReport_Mode,                  1},
/*278*/{E2Addr_ProgAcC_Report_Mode,          &GV_ProgAcC_Report_Mode[0],           CLReport_Mode,                  1},
/*279*/{E2Addr_ProgReC_Report_Mode,          &GV_ProgReC_Report_Mode[0],           CLReport_Mode,                  1},
/*280*/{E2Addr_ProgTPara_Report_Mode,        &GV_ProgTPara_Report_Mode[0],         CLReport_Mode,                  1},
/*281*/{E2Addr_ProgLad_Report_Mode,          &GV_ProgLad_Report_Mode[0],           CLReport_Mode,                  1},
/*282*/{E2Addr_Key_Update_Report_Mode,       &GV_Key_Update_Report_Mode[0],        CLReport_Mode,                  1},
/*283*/{E2Addr_AbnorC_Report_Mode,           &GV_AbnorC_Report_Mode[0],            CLReport_Mode,                  1},
/*284*/{E2Addr_BuyCurr_Report_Mode,          &GV_BuyCurr_Report_Mode[0],           CLReport_Mode,                  1},
/*285*/{E2Addr_ReturnMoney_Report_Mode,      &GV_ReturnMoney_Report_Mode[0],       CLReport_Mode,                  1},
/*286*/{E2Addr_ConMEndEn_Report_Mode,        &GV_ConMEndEn_Report_Mode[0],         CLReport_Mode,                  1},
/*287*/{E2Addr_RelayFaEndEn_Report_Mode,     &GV_RelayFaEndEn_Report_Mode[0],      CLReport_Mode,                  1},
/*288*/{E2Addr_PowerFa_EndT_Report_Mode,     &GV_PowerFa_EndT_Report_Mode[0],      CLReport_Mode,                  1},
/*289*/{E2Addr_SeriNoBalCurr_Report_Mode,    &GV_SeriNoBalCurr_Report_Mode[0],     CLReport_Mode,                  1},
/*290*/{E2Addr_ClockFault_Report_Mode,       &GV_ClockFault_Report_Mode[0],        CLReport_Mode,                  1},
/*291*/{E2Addr_MeteringChipFault_Report_Mode,&GV_MeteringChipFault_Report_Mode[0], CLReport_Mode,                  1},
/*292*/{E2Addr_BroadcastTime_Report_Mode,    &GV_BroadcastTime_Report_Mode[0],     CLReport_Mode,                  1},
/*293*/{E2Addr_ABnor_ZeroCurrent_Report_Mode,&GV_ABnor_ZeroCurrent_Report_Mode[0], CLReport_Mode,                  1},/*零线电流异常上报模式字*/

/*294*/{E2Addr_LossVolage_Report_Type,       &GV_LossVolage_Report_Type[0],        CLReport_Type,                  1},/*失压上报方式*/
/*295*/{E2Addr_LowVolage_Report_Type,        &GV_LowVolage_Report_Type[0],         CLReport_Type,                  1},/*欠压上报方式*/
/*296*/{E2Addr_OverVolage_Report_Type,       &GV_OverVolage_Report_Type[0],        CLReport_Type,                  1},/*过压上报方式*/
/*297*/{E2Addr_BreakVol_Report_Type,         &GV_BreakVol_Report_Type[0],          CLReport_Type,                  1},/*断相上报方式*/
/*298*/{E2Addr_LossCurr_Report_Type,         &GV_LossCurr_Report_Type[0],          CLReport_Type,                  1},/*失流上报方式*/
/*299*/{E2Addr_OverCurr_Report_Type,         &GV_OverCurr_Report_Type[0],          CLReport_Type,                  1},/*过流上报方式*/
/*300*/{E2Addr_BreakCurr_Report_Type,        &GV_BreakCurr_Report_Type[0],         CLReport_Type,                  1},/*断流上报方式*/
/*301*/{E2Addr_PowerRev_Report_Type,         &GV_PowerRev_Report_Type[0],          CLReport_Type,                  1},/*功率反向上报方式*/
/*302*/{E2Addr_OverLoad_Report_Type,         &GV_OverLoad_Report_Type[0],          CLReport_Type,                  1},/*过载上报方式*/
/*303*/{E2Addr_PosAcDemandOv_Report_Type,    &GV_PosAcDemandOv_Report_Type[0],     CLReport_Type,                  1},/*正向有功需量超限事件上报方式*/
/*304*/{E2Addr_RevAcDemandOv_Report_Type,    &GV_RevAcDemandOv_Report_Type[0],     CLReport_Type,                  1},/*反向有功需量超限事件上报方式*/
/*305*/{E2Addr_ReDemandOv_Report_Type,       &GV_ReDemandOv_Report_Type[0],        CLReport_Type,                  1},/*无功需量超限事件上报方式*/
/*306*/{E2Addr_PowerFactor_Report_Type,      &GV_PowerFactor_Report_Type[0],       CLReport_Type,                  1},/*功率因数超下限事件上报方式*/
/*307*/{E2Addr_AllLossVolage_Report_Type,    &GV_AllLossVolage_Report_Type[0],     CLReport_Type,                  1},/*全失压上报方式*/
/*308*/{E2Addr_AuxPowDown_Report_Type,       &GV_AuxPowDown_Report_Type[0],        CLReport_Type,                  1},/*辅助电源失电上报方式*/
/*309*/{E2Addr_ReversedVoltage_Report_Type,  &GV_ReversedVoltage_Report_Type[0],   CLReport_Type,                  1},/*电压逆相序上报方式*/
/*310*/{E2Addr_ReversedCurrent_Report_Type,  &GV_ReversedCurrent_Report_Type[0],   CLReport_Type,                  1},/*电流逆相序上报方式*/
/*311*/{E2Addr_PowerOff_Report_Type,         &GV_PowerOff_Report_Type[0],          CLReport_Type,                  1},/*掉电上报方式*/
/*312*/{E2Addr_Program_Report_Type,          &GV_Program_Report_Type[0],           CLReport_Type,                  1},/*编程上报方式*/
/*313*/{E2Addr_TolClear_Report_Type,         &GV_TolClear_Report_Type[0],          CLReport_Type,                  1},/*电表清零上报方式*/
/*314*/{E2Addr_DemandClear_Report_Type,      &GV_DemandClear_Report_Type[0],       CLReport_Type,                  1},/*需量清零上报方式*/
/*315*/{E2Addr_EventClear_Report_Type,       &GV_EventClear_Report_Type[0],        CLReport_Type,                  1},/*事件清零上报方式*/
/*316*/{E2Addr_AdjTime_Report_Type,          &GV_AdjTime_Report_Type [0],          CLReport_Type,                  1},/*校时上报方式*/
/*317*/{E2Addr_ProgPT_Report_Type,           &GV_ProgPT_Report_Type[0],            CLReport_Type,                  1},/*时段表编程上报方式*/
/*318*/{E2Addr_ProgPZ_Report_Type,           &GV_ProgPZ_Report_Type[0],            CLReport_Type,                  1},/*时区表编程上报方式*/
/*319*/{E2Addr_ProgWRe_Report_Type,          &GV_ProgWRe_Report_Type[0],           CLReport_Type,                  1},/*周休日编程上报方式*/
/*320*/{E2Addr_ProgSettD_Report_Type,        &GV_ProgSettD_Report_Type[0],         CLReport_Type,                  1},/*结算日编程上报方式*/
/*321*/{E2Addr_OpenW_Report_Type,            &GV_OpenW_Report_Type[0],             CLReport_Type,                  1},/*开表盖上报方式*/
/*322*/{E2Addr_OpenCW_Report_Type,           &GV_OpenCW_Report_Type[0],            CLReport_Type,                  1},/*开端钮盖上报方式*/
/*323*/{E2Addr_NoBalVol_Report_Type,         &GV_NoBalVol_Report_Type[0],          CLReport_Type,                  1},/*电压不平衡上报方式*/
/*324*/{E2Addr_NoBalCurr_Report_Type,        &GV_NoBalCurr_Report_Type[0],         CLReport_Type,                  1},/*电流不平衡上报方式*/
/*325*/{E2Addr_RelayOpen_Report_Type,        &GV_RelayOpen_Report_Type[0],         CLReport_Type,                  1},/*跳闸上报方式*/
/*326*/{E2Addr_RelayClose_Report_Type,       &GV_RelayClose_Report_Type[0],        CLReport_Type,                  1},/*合闸上报方式*/
/*327*/{E2Addr_ProgHol_Report_Type,          &GV_ProgHol_Report_Type[0],           CLReport_Type,                  1},/*节假日编程上报方式*/
/*328*/{E2Addr_ProgAcC_Report_Type,          &GV_ProgAcC_Report_Type[0],           CLReport_Type,                  1},/*有功组合方式编程上报方式*/
/*329*/{E2Addr_ProgReC_Report_Type,          &GV_ProgReC_Report_Type[0],           CLReport_Type,                  1},/*无功组合方式编程上报方式*/
/*330*/{E2Addr_ProgTPara_Report_Type,        &GV_ProgTPara_Report_Type[0],         CLReport_Type,                  1},/*费率参数表编程上报方式*/
/*331*/{E2Addr_ProgLad_Report_Type,          &GV_ProgLad_Report_Type[0],           CLReport_Type,                  1},/*阶梯表编程上报方式*/
/*332*/{E2Addr_Key_Update_Report_Type,       &GV_Key_Update_Report_Type[0],        CLReport_Type,                  1},/*密钥更新上报方式*/
/*333*/{E2Addr_AbnorC_Report_Type,           &GV_AbnorC_Report_Type[0],            CLReport_Type,                  1},/*异常插卡上报方式*/
/*334*/{E2Addr_BuyCurr_Report_Type,          &GV_BuyCurr_Report_Type[0],           CLReport_Type,                  1},/*购电上报方式*/
/*335*/{E2Addr_ReturnMoney_Report_Type,      &GV_ReturnMoney_Report_Type[0],       CLReport_Type,                  1},/*退费上报方式*/
/*336*/{E2Addr_ConMEndEn_Report_Type,        &GV_ConMEndEn_Report_Type[0],         CLReport_Type,                  1},/*恒定磁场干扰上报方式*/
/*337*/{E2Addr_RelayFaEndEn_Report_Type,     &GV_RelayFaEndEn_Report_Type[0],      CLReport_Type,                  1},/*负荷开关误动作上报方式*/
/*338*/{E2Addr_PowerFa_EndT_Report_Type,     &GV_PowerFa_EndT_Report_Type[0],      CLReport_Type,                  1},/*电源异常上报方式*/
/*339*/{E2Addr_SeriNoBalCurr_Report_Type,    &GV_SeriNoBalCurr_Report_Type[0],     CLReport_Type,                  1},/*电流严重不平衡上报方式*/
/*340*/{E2Addr_ClockFault_Report_Type,       &GV_ClockFault_Report_Type[0],        CLReport_Type,                  1},/*时钟故障上报方式*/
/*341*/{E2Addr_MeteringChipFault_Report_Type,&GV_MeteringChipFault_Report_Type[0], CLReport_Type,                  1},/*计量芯片故障上报方式*/
/*342*/{E2Addr_BroadcastTime_Report_Type,    &GV_BroadcastTime_Report_Type[0],     CLReport_Type,                  1},/*广播校时上报方式*/
/*343*/{E2Addr_ABnor_ZeroCurrent_Report_Type,&GV_ABnor_ZeroCurrent_Report_Type[0], CLReport_Type,                  1},/*零线电流异常上报方式*/
/*344*/{E2Addr_Drive_Report_Type,            &GV_Drive_Report_Type[0],             CLReport_Type,                  1}, /*2015跟随上报方式*/


/*345*/{E2Addr_Relay_Delay_Time_645,         &GV_Relay_Delay_Time_645[0],          CLRelay_Delay_Time_645,         1},
/*346*/{E2Addr_Drive_Report_Mode_645,        &GV_Drive_Report_Mode_645[0],         CLDrive_Report_Mode_645,        1},
/*347*/{E2Addr_Meter_Work_Char1_645,         &GV_Meter_Work_Char1_645[0],          CLMeter_Work_Char1_645,         1},
/*348*/{E2Addr_Meter_Work_Char1,             &GV_Meter_Work_Char1[0],              CLMeter_Work_Char1,             1},

};
#define Str_3aTable_E23RAM_Len  (sizeof(Str_3aTable_E23RAM)/sizeof(Str_3aTable))

#define C_No4TableAllFF    0xFFFFFFFF
const Str_3cTable Str_3cTable_Flash[]=
{/*记录块Flash首页地址       记录块Flash尾页地址      4级表格结构体数组地址,当4级表不分项时，为全FF       次数存E2第1处备份地址      1个记录块数据总长度     4级表格结构体数组数据长度,当不存在4级表时，数据为全零*/
    {FlashStAddr_Rec_Meter,             FlashEndAddr_Rec_Meter,             (ulong32)(&Str_4Table_Rec_Meter[0]),    E2Addr_Rec_Meter_Degree,             Rec_Meter_Data_Len,             Str_4Table_Rec_Meter_Len},
    {FlashStAddr_CurrentPart_ProgPT,    FlashEndAddr_CurrentPart_ProgPT,    (ulong32)(&Str_4Table_ProgPT[0]),       E2Addr_ProgPT_CurrentPart_Degree,    ProgPT_Data_CurrentPart_Len,    Str_4Table_ProgPT_Len},
    {FlashStAddr_CurrentPart_ProgTZ,    FlashEndAddr_CurrentPart_ProgTZ,    C_No4TableAllFF,                        E2Addr_ProgTZ_CurrentPart_Degree,    ProgTZ_Data_CurrentPart_Len,    0},
    {FlashStAddr_Program_645,           FlashEndAddr_Program_645,           C_No4TableAllFF,                        E2Addr_Program_Degree_645,           Program_Data_Len_645,           0},
};
#define Str_3cTable_Flash_Len  (sizeof(Str_3cTable_Flash)/sizeof(Str_3cTable))

const Str_3eTable Str_3eTable_2E2[]=
{/*关联OAD序号表E2地址       关联序号表OAD个数E2地址*/
  {E2Addr_All_Loss_Vol_OADTab,			E2Addr_All_Loss_Vol_OADTabLen},
  {E2Addr_Aux_Pow_Down_OADTab,			E2Addr_Aux_Pow_Down_OADTabLen},
  {E2Addr_Pow_Down_OADTab,				E2Addr_Pow_Down_OADTabLen},
  {E2Addr_Pos_Ac_De_Over_OADTab,		E2Addr_Pos_Ac_De_Over_OADTabLen},
  {E2Addr_Rev_Ac_De_Over_OADTab,		E2Addr_Rev_Ac_De_Over_OADTabLen},
  {E2Addr_Qua_Re_De_Over_OADTab,		E2Addr_Qua_Re_De_Over_OADTabLen},
  {E2Addr_Loss_Vol_OADTab,				E2Addr_Loss_Vol_OADTabLen},
  {E2Addr_Low_Vol_OADTab,				E2Addr_Low_Vol_OADTabLen},
  {E2Addr_Over_Vol_OADTab,				E2Addr_Over_Vol_OADTabLen},
  {E2Addr_Break_Vol_OADTab,				E2Addr_Break_Vol_OADTabLen},
  {E2Addr_RevPS_Vol_OADTab,				E2Addr_RevPS_Vol_OADTabLen},
  {E2Addr_RevPS_Curr_OADTab,			E2Addr_RevPS_Curr_OADTabLen},
  {E2Addr_NoBal_Vol_OADTab,	 			E2Addr_NoBal_Vol_OADTabLen},
  {E2Addr_NoBal_Curr_OADTab,			E2Addr_NoBal_Curr_OADTabLen},
  {E2Addr_SevNoBal_Curr_OADTab,			E2Addr_SevNoBal_Curr_OADTabLen},
  {E2Addr_Loss_Curr_OADTab,				E2Addr_Loss_Curr_OADTabLen},
  {E2Addr_Over_Curr_OADTab,				E2Addr_Over_Curr_OADTabLen},
  {E2Addr_Break_Curr_OADTab,			E2Addr_Break_Curr_OADTabLen},
  {E2Addr_Power_Rev_OADTab,				E2Addr_Power_Rev_OADTabLen},
  {E2Addr_Over_Lo_OADTab,				E2Addr_Over_Lo_OADTabLen},
  {E2Addr_Tol_Clear_OADTab,				E2Addr_Tol_Clear_OADTabLen},
  {E2Addr_De_Clear_OADTab,				E2Addr_De_Clear_OADTabLen},
  {E2Addr_Even_Clear_OADTab,			E2Addr_Even_Clear_OADTabLen},
  {E2Addr_Program_OADTab,				E2Addr_Program_OADTabLen},
  {E2Addr_AbnorC_OADTab,				E2Addr_AbnorC_OADTabLen},
  {E2Addr_OpenW_OADTab,					E2Addr_OpenW_OADTabLen},
  {E2Addr_OpenCW_OADTab,				E2Addr_OpenCW_OADTabLen},
  {E2Addr_BuyCurr_OADTab,				E2Addr_BuyCurr_OADTabLen},
  {E2Addr_Return_M_OADTab,				E2Addr_Return_M_OADTabLen},
  {E2Addr_ConM_OADTab,					E2Addr_ConM_OADTabLen},
  {E2Addr_RelayFa_OADTab,				E2Addr_RelayFa_OADTabLen},
  {E2Addr_PowerFa_OADTab,				E2Addr_PowerFa_OADTabLen},
  {E2Addr_RelayOpen_OADTab,				E2Addr_RelayOpen_OADTabLen},
  {E2Addr_RelayClose_OADTab,			E2Addr_RelayClose_OADTabLen},
  {E2Addr_PFactorT_Over_OADTab,			E2Addr_PFactorT_Over_OADTabLen},
  {E2Addr_AdjTime_OADTab,				E2Addr_AdjTime_OADTabLen},
  {E2Addr_ProgPT_OADTab,				E2Addr_ProgPT_OADTabLen},
  {E2Addr_ProgTZ_OADTab,				E2Addr_ProgTZ_OADTabLen},
  {E2Addr_ProgWRe_OADTab,				E2Addr_ProgWRe_OADTabLen},
  {E2Addr_ProgHol_OADTab,				E2Addr_ProgHol_OADTabLen},
  {E2Addr_ProgAcC_OADTab,				E2Addr_ProgAcC_OADTabLen},
  {E2Addr_ProgReC_OADTab,				E2Addr_ProgReC_OADTabLen},
  {E2Addr_ProgSettD_OADTab,				E2Addr_ProgSettD_OADTabLen},
  {E2Addr_ProgTPara_OADTab,				E2Addr_ProgTPara_OADTabLen},
  {E2Addr_ProgLad_OADTab,				E2Addr_ProgLad_OADTabLen},
  {E2Addr_ProgKD_OADTab,				E2Addr_ProgKD_OADTabLen},
  {E2Addr_MeterFa_OADTab,				E2Addr_MeterFa_OADTabLen},
  {E2Addr_ClockFa_OADTab,				E2Addr_ClockFa_OADTabLen},
  {E2Addr_BroadcastTime_OADTab,			E2Addr_BroadcastTime_OADTabLen},
  {E2Addr_NeutralCurrentAbnormal_OADTab,E2Addr_NeutralCurrentAbnormal_OADTabLen},
//  {E2Addr_BroadTimeAbnormal_OADTab,	E2Addr_BroadTimeAbnormal_OADTabLen},
};
#define Str_3eTable_Flash_Len  (sizeof(Str_3eTable_2E2)/sizeof(Str_3eTable))

/************标识码是否支持读写及消息写权限*************/
#define C_Read_Data                             0x80                                 /**/
#define C_WR_All                                0xFF                                 /*支持所有模块写，目前只用电表运行状态字*/
#define C_WR_Data                               0x7F
#define C_Only_Read                             0x80                                 /*只支持读*/
#define C_No_WR                                 0x00                                 /*即不支持读，也不支持写*/
#define C_WR_Msg_PowerNetworkMonitoring         (0x80|C_Msg_PowerNetworkMonitoring)  /*支持读，同时支持电网监测判断消息写*/
#define C_W_Msg_PowerNetworkMonitoring          C_Msg_PowerNetworkMonitoring         /*只支持电网监测判断消息写*/

#define C_WR_Msg_Write_PowerNetworkMonitoring   (0x80|C_Msg_Write_PowerNetworkMonitoring)
#define C_W_Msg_Write_PowerNetworkMonitoring    C_Msg_Write_PowerNetworkMonitoring

#define C_WR_Msg_EnergyMetering                 (0x80|C_Msg_EnergyMetering)
#define C_W_Msg_EnergyMetering                  C_Msg_EnergyMetering

#define C_WR_Msg_DemandMetering                 (0x80|C_Msg_DemandMetering)
#define C_W_Msg_DemandMetering                  C_Msg_DemandMetering

#define C_WR_Msg_Communication                  (0x80|C_Msg_Communication)
#define C_W_Msg_Communication                   C_Msg_Communication

#define C_WR_Msg_SettleAccounts                 (0x80|C_Msg_SettleAccounts)
#define C_W_Msg_SettleAccounts                  C_Msg_SettleAccounts

#define C_WR_Msg_Freeze                         (0x80|C_Msg_Freeze)
#define C_W_Msg_Freeze                          C_Msg_Freeze

#define C_WR_Msg_LoadProfile                    (0x80|C_Msg_LoadProfile)
#define C_W_Msg_LoadProfile                     C_Msg_LoadProfile

#define C_WR_Msg_Display                        (0x80|C_Msg_Display)
#define C_W_Msg_Display                         C_Msg_Display

#define C_WR_Msg_Deal_RelayStatus               (0x80|C_Msg_Deal_RelayStatus)
#define C_W_Msg_Deal_RelayStatus                C_Msg_Deal_RelayStatus

#define C_WR_Msg_Deal_MultiRates                (0x80|C_Msg_Deal_MultiRates)
#define C_W_Msg_Deal_MultiRates                 C_Msg_Deal_MultiRates

#define C_WR_Msg_BatteryVoltagleMetering        (0x80|C_Msg_BatteryVoltagleMetering)
#define C_W_Msg_BatteryVoltagleMetering         C_Msg_BatteryVoltagleMetering

#define C_WR_Msg_VoltageQualifiedRateMetering   (0x80|C_Msg_VoltageQualifiedRateMetering)
#define C_W_Msg_VoltageQualifiedRateMetering    C_Msg_VoltageQualifiedRateMetering

#define C_WR_Msg_Dispatch                       (0x80|C_Msg_Dispatch)
#define C_W_Msg_Dispatch                        C_Msg_Dispatch

#define C_WR_Msg_MeterIC                        (0x80|C_Msg_MeterIC)
#define C_W_Msg_MeterIC                         C_Msg_MeterIC

#define C_WR_Msg_Card                           (0x80|C_Msg_Card)
#define C_W_Msg_Card                            C_Msg_Card

#define C_WR_Msg_Esam                           (0x80|C_Msg_Esam)
#define C_W_Msg_Esam                            C_Msg_Esam


/**********组合消息定义***************/
#define C_Com_Msg_Star                          80                               /*组合消息号从80开始,非组合消息即单独模块消息号，不能≥该值，并且消息号不能从0开始*/
#define C_Msg_PDDF                              C_Com_Msg_Star                   /*组合消息C_Msg_PowerNetworkMonitoring,C_Msg_Dispatch,C_Msg_Display,C_Msg_Freeze*/
#define C_WR_Msg_PDDF                           (0x80|C_Msg_PDDF)
#define C_W_Msg_PDDF                            C_Msg_PDDF

#define C_Msg_Comm_Card                         (C_Com_Msg_Star+1)               /*组合消息C_Msg_Communication,C_Msg_Card*/
#define C_WR_Msg_Comm_Card                      (0x80|C_Msg_Comm_Card)
#define C_W_Msg_Comm_Card                       C_Msg_Comm_Card

#define C_Msg_Comm_Dis                          (C_Msg_Comm_Card+1)              /*组合消息C_Msg_Communication,C_Msg_Dispatch*/
#define C_WR_Msg_Comm_Dis                       (0x80|C_Msg_Comm_Dis)
#define C_W_Msg_Comm_Dis                        C_Msg_Comm_Dis

#define C_Msg_Card_Deal                         (C_Msg_Comm_Dis+1)               /*组合消息C_Msg_Card,C_Msg_Deal_MultiRates*/
#define C_WR_Msg_Card_Deal                      (0x80|C_Msg_Card_Deal)
#define C_W_Msg_Card_Deal                       C_Msg_Card_Deal

#define C_Msg_En_Deal                           (C_Msg_Card_Deal+1)              /*组合消息C_Msg_EnergyMetering,C_Msg_Deal_MultiRates*/
#define C_WR_Msg_En_Deal                        (0x80|C_Msg_En_Deal)
#define C_W_Msg_En_Deal                         C_Msg_En_Deal

#define C_Msg_Comm_Deal                         (C_Msg_En_Deal+1)                /*组合消息C_Msg_Communication,C_Msg_Deal_MultiRates*/
#define C_WR_Msg_Comm_Deal                      (0x80|C_Msg_Comm_Deal)
#define C_W_Msg_Comm_Deal                       C_Msg_Comm_Deal

#define C_Msg_Comm_Deal_Card                    (C_Msg_Comm_Deal+1)              /*组合消息C_Msg_Communication,C_Msg_Deal_MultiRates,C_Msg_Card*/
#define C_WR_Msg_Comm_Deal_Card                 (0x80|C_Msg_Comm_Deal_Card)
#define C_W_Msg_Comm_Deal_Card                  C_Msg_Comm_Deal_Card

#define C_Msg_Comm_Relay                        (C_Msg_Comm_Deal_Card+1)         /*组合消息C_Msg_Communication,C_Msg_Deal_RelayStatus*/
#define C_WR_Msg_Comm_Relay                     (0x80|C_Msg_Comm_Relay)
#define C_W_Msg_Comm_Relay                      C_Msg_Comm_Relay


#define C_Com_Msg_Len                           4
const uchar8 GP_Com_Msg[][C_Com_Msg_Len]=
{
	{C_Msg_PowerNetworkMonitoring,    C_Msg_Dispatch,           C_Msg_Display,    C_Msg_Freeze},    /*C_Com_Msg_Star，对应组合消息号80*/
	{C_Msg_Communication,             C_Msg_Card,               0,                0           },
	{C_Msg_Communication,             C_Msg_Dispatch,           0,                0           },
	{C_Msg_Card,                      C_Msg_Deal_MultiRates,    0,                0           },
	{C_Msg_EnergyMetering,            C_Msg_Deal_MultiRates,    0,                0           },
	{C_Msg_Communication,             C_Msg_Deal_MultiRates,    0,                0           },
	{C_Msg_Communication,             C_Msg_Deal_MultiRates,    C_Msg_Card,       0           },
	{C_Msg_Communication,             C_Msg_Deal_RelayStatus,   0,                0           },
};
#define C_Com_Msg_Len_Max (sizeof(GP_Com_Msg)/C_Com_Msg_Len)

/***********电能量类**************/
const Str_2Table Str_2Table_DIEn[]=
{/*数据标示(对于电能模块此为脉冲数，其他模块此为精确电能，获取数据时电能模块负责数据转换) 对应三级表结构体数组地址                    应三级表行号  具体数据长度              对应消息号及是否支持读             数据类型    */
    {CPos_Ac_T1_PreEn_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          0,      C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CPos_Ac_T2_PreEn_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          1,      C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CPos_Ac_T3_PreEn_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          2,      C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CPos_Ac_T4_PreEn_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          3,      C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CPos_Ac_T5_PreEn_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          4,      C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CPos_Ac_T6_PreEn_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          5,      C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CPos_Ac_T7_PreEn_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          6,      C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CPos_Ac_T8_PreEn_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          7,      C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CPos_Ac_T9_PreEn_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          8,      C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CPos_Ac_T10_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          9,      C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CPos_Ac_T11_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          10,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CPos_Ac_T12_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          11,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},

    {CRev_Ac_T1_PreEn_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          12,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CRev_Ac_T2_PreEn_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          13,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CRev_Ac_T3_PreEn_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          14,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CRev_Ac_T4_PreEn_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          15,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CRev_Ac_T5_PreEn_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          16,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CRev_Ac_T6_PreEn_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          17,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CRev_Ac_T7_PreEn_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          18,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CRev_Ac_T8_PreEn_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          19,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CRev_Ac_T9_PreEn_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          20,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CRev_Ac_T10_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          21,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CRev_Ac_T11_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          22,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CRev_Ac_T12_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          23,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},

    {CQua1_Re_T1_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          24,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua1_Re_T2_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          25,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua1_Re_T3_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          26,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua1_Re_T4_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          27,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua1_Re_T5_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          28,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua1_Re_T6_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          29,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua1_Re_T7_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          30,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua1_Re_T8_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          31,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua1_Re_T9_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          32,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua1_Re_T10_PreEn_0,          (ulong32)(&Str_3aTable_E23RAM[0]),          33,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua1_Re_T11_PreEn_0,          (ulong32)(&Str_3aTable_E23RAM[0]),          34,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua1_Re_T12_PreEn_0,          (ulong32)(&Str_3aTable_E23RAM[0]),          35,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},

    {CQua2_Re_T1_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          36,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua2_Re_T2_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          37,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua2_Re_T3_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          38,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua2_Re_T4_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          39,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua2_Re_T5_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          40,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua2_Re_T6_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          41,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua2_Re_T7_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          42,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua2_Re_T8_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          43,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua2_Re_T9_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          44,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua2_Re_T10_PreEn_0,          (ulong32)(&Str_3aTable_E23RAM[0]),          45,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua2_Re_T11_PreEn_0,          (ulong32)(&Str_3aTable_E23RAM[0]),          46,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua2_Re_T12_PreEn_0,          (ulong32)(&Str_3aTable_E23RAM[0]),          47,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},

    {CQua3_Re_T1_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          48,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua3_Re_T2_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          49,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua3_Re_T3_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          50,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua3_Re_T4_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          51,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua3_Re_T5_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          52,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua3_Re_T6_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          53,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua3_Re_T7_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          54,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua3_Re_T8_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          55,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua3_Re_T9_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          56,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua3_Re_T10_PreEn_0,          (ulong32)(&Str_3aTable_E23RAM[0]),          57,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua3_Re_T11_PreEn_0,          (ulong32)(&Str_3aTable_E23RAM[0]),          58,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua3_Re_T12_PreEn_0,          (ulong32)(&Str_3aTable_E23RAM[0]),          59,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},

    {CQua4_Re_T1_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          60,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua4_Re_T2_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          61,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua4_Re_T3_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          62,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua4_Re_T4_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          63,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua4_Re_T5_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          64,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua4_Re_T6_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          65,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua4_Re_T7_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          66,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua4_Re_T8_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          67,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua4_Re_T9_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          68,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua4_Re_T10_PreEn_0,          (ulong32)(&Str_3aTable_E23RAM[0]),          69,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua4_Re_T11_PreEn_0,          (ulong32)(&Str_3aTable_E23RAM[0]),          70,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua4_Re_T12_PreEn_0,          (ulong32)(&Str_3aTable_E23RAM[0]),          71,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},

    {CPosA_Ac_PreEn_0,              (ulong32)(&Str_3aTable_E23RAM[0]),          72,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CRevA_Ac_PreEn_0,              (ulong32)(&Str_3aTable_E23RAM[0]),          73,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua1A_Re_PreEn_0,             (ulong32)(&Str_3aTable_E23RAM[0]),          74,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua2A_Re_PreEn_0,             (ulong32)(&Str_3aTable_E23RAM[0]),          75,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua3A_Re_PreEn_0,             (ulong32)(&Str_3aTable_E23RAM[0]),          76,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua4A_Re_PreEn_0,             (ulong32)(&Str_3aTable_E23RAM[0]),          77,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},

    {CPosB_Ac_PreEn_0,              (ulong32)(&Str_3aTable_E23RAM[0]),          78,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CRevB_Ac_PreEn_0,              (ulong32)(&Str_3aTable_E23RAM[0]),          79,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua1B_Re_PreEn_0,             (ulong32)(&Str_3aTable_E23RAM[0]),          80,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua2B_Re_PreEn_0,             (ulong32)(&Str_3aTable_E23RAM[0]),          81,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua3B_Re_PreEn_0,             (ulong32)(&Str_3aTable_E23RAM[0]),          82,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua4B_Re_PreEn_0,             (ulong32)(&Str_3aTable_E23RAM[0]),          83,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},

    {CPosC_Ac_PreEn_0,              (ulong32)(&Str_3aTable_E23RAM[0]),          84,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CRevC_Ac_PreEn_0,              (ulong32)(&Str_3aTable_E23RAM[0]),          85,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua1C_Re_PreEn_0,             (ulong32)(&Str_3aTable_E23RAM[0]),          86,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua2C_Re_PreEn_0,             (ulong32)(&Str_3aTable_E23RAM[0]),          87,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua3C_Re_PreEn_0,             (ulong32)(&Str_3aTable_E23RAM[0]),          88,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua4C_Re_PreEn_0,             (ulong32)(&Str_3aTable_E23RAM[0]),          89,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},

#if 0   /*注意清零命令，下述对象标识已移到其他表格*/
    {CM_Com_Ac_Tol_En_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          91,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CY_Com_Ac_Tol_En_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          92,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CChargeBal_Hex_Cent,           (ulong32)(&Str_3aTable_E23RAM[0]),          93,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CChargeBal_Hex_Full,           (ulong32)(&Str_3aTable_E23RAM[0]),          93,     C_CurrDataLen5,            C_W_Msg_EnergyMetering,             DT_Ti_E23_RAMCRC},
    {COverDraft_Hex_Cent,           (ulong32)(&Str_3aTable_E23RAM[0]),          94,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {COverDraft_Hex_Full,           (ulong32)(&Str_3aTable_E23RAM[0]),          94,     C_CurrDataLen5,            C_W_Msg_EnergyMetering,             DT_Ti_E23_RAMCRC},
    {CM_Pos_Ac_Tol_En_Pul_1,        (ulong32)(E2Addr_M_Pos_Ac_Tol_En_Pul_1),    0,      C_CurrDataLen5,            C_WR_Msg_SettleAccounts,            DT_E23_Clear},
    {CM_Rev_Ac_Tol_En_Pul_1,        (ulong32)(E2Addr_M_Rev_Ac_Tol_En_Pul_1),    0,      C_CurrDataLen5,            C_WR_Msg_SettleAccounts,            DT_E23_Clear},
#endif
};
#define Str_2Table_DIEn_Len  (sizeof(Str_2Table_DIEn)/sizeof(Str_2Table))

/***********最大需量类**************/
const Str_2Table Str_2Table_DIDe10[]=
{ /* 数据标示                       对应三级表结构体数组地址                    应三级表行号  具体数据长度              对应消息号及是否支持读             数据类型    */
    {CPos_Ac_Tol_De_0,              (ulong32)(E2Addr_Pos_Ac_Tol_De_0),          0,      (CLPos_Ac_Tol_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CPos_Ac_T1_De_0,               (ulong32)(E2Addr_Pos_Ac_T1_De_0),           0,      (CLPos_Ac_T1_De_0),             C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CPos_Ac_T2_De_0,               (ulong32)(E2Addr_Pos_Ac_T2_De_0),           0,      (CLPos_Ac_T2_De_0),             C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CPos_Ac_T3_De_0,               (ulong32)(E2Addr_Pos_Ac_T3_De_0),           0,      (CLPos_Ac_T3_De_0),             C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CPos_Ac_T4_De_0,               (ulong32)(E2Addr_Pos_Ac_T4_De_0),           0,      (CLPos_Ac_T4_De_0),             C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CPos_Ac_T5_De_0,               (ulong32)(E2Addr_Pos_Ac_T5_De_0),           0,      (CLPos_Ac_T5_De_0),             C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CPos_Ac_T6_De_0,               (ulong32)(E2Addr_Pos_Ac_T6_De_0),           0,      (CLPos_Ac_T6_De_0),             C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CPos_Ac_T7_De_0,               (ulong32)(E2Addr_Pos_Ac_T7_De_0),           0,      (CLPos_Ac_T7_De_0),             C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CPos_Ac_T8_De_0,               (ulong32)(E2Addr_Pos_Ac_T8_De_0),           0,      (CLPos_Ac_T8_De_0),             C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CPos_Ac_T9_De_0,               (ulong32)(E2Addr_Pos_Ac_T9_De_0),           0,      (CLPos_Ac_T9_De_0),             C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CPos_Ac_T10_De_0,              (ulong32)(E2Addr_Pos_Ac_T10_De_0),          0,      (CLPos_Ac_T10_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CPos_Ac_T11_De_0,              (ulong32)(E2Addr_Pos_Ac_T11_De_0),          0,      (CLPos_Ac_T11_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CPos_Ac_T12_De_0,              (ulong32)(E2Addr_Pos_Ac_T12_De_0),          0,      (CLPos_Ac_T12_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},

    {CRev_Ac_Tol_De_0,              (ulong32)(E2Addr_Rev_Ac_Tol_De_0),          0,      (CLRev_Ac_Tol_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CRev_Ac_T1_De_0,               (ulong32)(E2Addr_Rev_Ac_T1_De_0),           0,      (CLRev_Ac_T1_De_0),             C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CRev_Ac_T2_De_0,               (ulong32)(E2Addr_Rev_Ac_T2_De_0),           0,      (CLRev_Ac_T2_De_0),             C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CRev_Ac_T3_De_0,               (ulong32)(E2Addr_Rev_Ac_T3_De_0),           0,      (CLRev_Ac_T3_De_0),             C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CRev_Ac_T4_De_0,               (ulong32)(E2Addr_Rev_Ac_T4_De_0),           0,      (CLRev_Ac_T4_De_0),             C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CRev_Ac_T5_De_0,               (ulong32)(E2Addr_Rev_Ac_T5_De_0),           0,      (CLRev_Ac_T5_De_0),             C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CRev_Ac_T6_De_0,               (ulong32)(E2Addr_Rev_Ac_T6_De_0),           0,      (CLRev_Ac_T6_De_0),             C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CRev_Ac_T7_De_0,               (ulong32)(E2Addr_Rev_Ac_T7_De_0),           0,      (CLRev_Ac_T7_De_0),             C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CRev_Ac_T8_De_0,               (ulong32)(E2Addr_Rev_Ac_T8_De_0),           0,      (CLRev_Ac_T8_De_0),             C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CRev_Ac_T9_De_0,               (ulong32)(E2Addr_Rev_Ac_T9_De_0),           0,      (CLRev_Ac_T9_De_0),             C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CRev_Ac_T10_De_0,              (ulong32)(E2Addr_Rev_Ac_T10_De_0),          0,      (CLRev_Ac_T10_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CRev_Ac_T11_De_0,              (ulong32)(E2Addr_Rev_Ac_T11_De_0),          0,      (CLRev_Ac_T11_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CRev_Ac_T12_De_0,              (ulong32)(E2Addr_Rev_Ac_T12_De_0),          0,      (CLRev_Ac_T12_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},

    {CQua1_Re_Tol_De_0,             (ulong32)(E2Addr_Qua1_Re_Tol_De_0),         0,      (CLQua1_Re_Tol_De_0),           C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua1_Re_T1_De_0,              (ulong32)(E2Addr_Qua1_Re_T1_De_0),          0,      (CLQua1_Re_T1_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua1_Re_T2_De_0,              (ulong32)(E2Addr_Qua1_Re_T2_De_0),          0,      (CLQua1_Re_T2_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua1_Re_T3_De_0,              (ulong32)(E2Addr_Qua1_Re_T3_De_0),          0,      (CLQua1_Re_T3_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua1_Re_T4_De_0,              (ulong32)(E2Addr_Qua1_Re_T4_De_0),          0,      (CLQua1_Re_T4_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua1_Re_T5_De_0,              (ulong32)(E2Addr_Qua1_Re_T5_De_0),          0,      (CLQua1_Re_T5_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua1_Re_T6_De_0,              (ulong32)(E2Addr_Qua1_Re_T6_De_0),          0,      (CLQua1_Re_T6_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua1_Re_T7_De_0,              (ulong32)(E2Addr_Qua1_Re_T7_De_0),          0,      (CLQua1_Re_T7_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua1_Re_T8_De_0,              (ulong32)(E2Addr_Qua1_Re_T8_De_0),          0,      (CLQua1_Re_T8_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua1_Re_T9_De_0,              (ulong32)(E2Addr_Qua1_Re_T9_De_0),          0,      (CLQua1_Re_T9_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua1_Re_T10_De_0,             (ulong32)(E2Addr_Qua1_Re_T10_De_0),         0,      (CLQua1_Re_T10_De_0),           C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua1_Re_T11_De_0,             (ulong32)(E2Addr_Qua1_Re_T11_De_0),         0,      (CLQua1_Re_T11_De_0),           C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua1_Re_T12_De_0,             (ulong32)(E2Addr_Qua1_Re_T12_De_0),         0,      (CLQua1_Re_T12_De_0),           C_WR_Msg_DemandMetering,            DT_E23_Clear},

    {CQua2_Re_Tol_De_0,             (ulong32)(E2Addr_Qua2_Re_Tol_De_0),         0,      (CLQua2_Re_Tol_De_0),           C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua2_Re_T1_De_0,              (ulong32)(E2Addr_Qua2_Re_T1_De_0),          0,      (CLQua2_Re_T1_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua2_Re_T2_De_0,              (ulong32)(E2Addr_Qua2_Re_T2_De_0),          0,      (CLQua2_Re_T2_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua2_Re_T3_De_0,              (ulong32)(E2Addr_Qua2_Re_T3_De_0),          0,      (CLQua2_Re_T3_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua2_Re_T4_De_0,              (ulong32)(E2Addr_Qua2_Re_T4_De_0),          0,      (CLQua2_Re_T4_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua2_Re_T5_De_0,              (ulong32)(E2Addr_Qua2_Re_T5_De_0),          0,      (CLQua2_Re_T5_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua2_Re_T6_De_0,              (ulong32)(E2Addr_Qua2_Re_T6_De_0),          0,      (CLQua2_Re_T6_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua2_Re_T7_De_0,              (ulong32)(E2Addr_Qua2_Re_T7_De_0),          0,      (CLQua2_Re_T7_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua2_Re_T8_De_0,              (ulong32)(E2Addr_Qua2_Re_T8_De_0),          0,      (CLQua2_Re_T8_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua2_Re_T9_De_0,              (ulong32)(E2Addr_Qua2_Re_T9_De_0),          0,      (CLQua2_Re_T9_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua2_Re_T10_De_0,             (ulong32)(E2Addr_Qua2_Re_T10_De_0),         0,      (CLQua2_Re_T10_De_0),           C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua2_Re_T11_De_0,             (ulong32)(E2Addr_Qua2_Re_T11_De_0),         0,      (CLQua2_Re_T11_De_0),           C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua2_Re_T12_De_0,             (ulong32)(E2Addr_Qua2_Re_T12_De_0),         0,      (CLQua2_Re_T12_De_0),           C_WR_Msg_DemandMetering,            DT_E23_Clear},

    {CQua3_Re_Tol_De_0,             (ulong32)(E2Addr_Qua3_Re_Tol_De_0),         0,      (CLQua3_Re_Tol_De_0),           C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua3_Re_T1_De_0,              (ulong32)(E2Addr_Qua3_Re_T1_De_0),          0,      (CLQua3_Re_T1_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua3_Re_T2_De_0,              (ulong32)(E2Addr_Qua3_Re_T2_De_0),          0,      (CLQua3_Re_T2_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua3_Re_T3_De_0,              (ulong32)(E2Addr_Qua3_Re_T3_De_0),          0,      (CLQua3_Re_T3_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua3_Re_T4_De_0,              (ulong32)(E2Addr_Qua3_Re_T4_De_0),          0,      (CLQua3_Re_T4_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua3_Re_T5_De_0,              (ulong32)(E2Addr_Qua3_Re_T5_De_0),          0,      (CLQua3_Re_T5_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua3_Re_T6_De_0,              (ulong32)(E2Addr_Qua3_Re_T6_De_0),          0,      (CLQua3_Re_T6_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua3_Re_T7_De_0,              (ulong32)(E2Addr_Qua3_Re_T7_De_0),          0,      (CLQua3_Re_T7_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua3_Re_T8_De_0,              (ulong32)(E2Addr_Qua3_Re_T8_De_0),          0,      (CLQua3_Re_T8_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua3_Re_T9_De_0,              (ulong32)(E2Addr_Qua3_Re_T9_De_0),          0,      (CLQua3_Re_T9_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua3_Re_T10_De_0,             (ulong32)(E2Addr_Qua3_Re_T10_De_0),         0,      (CLQua3_Re_T10_De_0),           C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua3_Re_T11_De_0,             (ulong32)(E2Addr_Qua3_Re_T11_De_0),         0,      (CLQua3_Re_T11_De_0),           C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua3_Re_T12_De_0,             (ulong32)(E2Addr_Qua3_Re_T12_De_0),         0,      (CLQua3_Re_T12_De_0),           C_WR_Msg_DemandMetering,            DT_E23_Clear},

    {CQua4_Re_Tol_De_0,             (ulong32)(E2Addr_Qua4_Re_Tol_De_0),         0,      (CLQua4_Re_Tol_De_0),           C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua4_Re_T1_De_0,              (ulong32)(E2Addr_Qua4_Re_T1_De_0),          0,      (CLQua4_Re_T1_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua4_Re_T2_De_0,              (ulong32)(E2Addr_Qua4_Re_T2_De_0),          0,      (CLQua4_Re_T2_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua4_Re_T3_De_0,              (ulong32)(E2Addr_Qua4_Re_T3_De_0),          0,      (CLQua4_Re_T3_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua4_Re_T4_De_0,              (ulong32)(E2Addr_Qua4_Re_T4_De_0),          0,      (CLQua4_Re_T4_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua4_Re_T5_De_0,              (ulong32)(E2Addr_Qua4_Re_T5_De_0),          0,      (CLQua4_Re_T5_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua4_Re_T6_De_0,              (ulong32)(E2Addr_Qua4_Re_T6_De_0),          0,      (CLQua4_Re_T6_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua4_Re_T7_De_0,              (ulong32)(E2Addr_Qua4_Re_T7_De_0),          0,      (CLQua4_Re_T7_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua4_Re_T8_De_0,              (ulong32)(E2Addr_Qua4_Re_T8_De_0),          0,      (CLQua4_Re_T8_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua4_Re_T9_De_0,              (ulong32)(E2Addr_Qua4_Re_T9_De_0),          0,      (CLQua4_Re_T9_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua4_Re_T10_De_0,             (ulong32)(E2Addr_Qua4_Re_T10_De_0),         0,      (CLQua4_Re_T10_De_0),           C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua4_Re_T11_De_0,             (ulong32)(E2Addr_Qua4_Re_T11_De_0),         0,      (CLQua4_Re_T11_De_0),           C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua4_Re_T12_De_0,             (ulong32)(E2Addr_Qua4_Re_T12_De_0),         0,      (CLQua4_Re_T12_De_0),           C_WR_Msg_DemandMetering,            DT_E23_Clear},

    {CPosA_Ac_De_0,                 (ulong32)(E2Addr_PosA_Ac_De_0),             0,      (CLPosA_Ac_De_0),               C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CRevA_Ac_De_0,                 (ulong32)(E2Addr_RevA_Ac_De_0),             0,      (CLRevA_Ac_De_0),               C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CComA_Re1_De_0,                (ulong32)(E2Addr_ComA_Re1_De_0),            0,      (CLComA_Re1_De_0),              C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CComA_Re2_De_0,                (ulong32)(E2Addr_ComA_Re2_De_0),            0,      (CLComA_Re2_De_0),              C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua1A_Re_De_0,                (ulong32)(E2Addr_Qua1A_Re_De_0),            0,      (CLQua1A_Re_De_0),              C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua2A_Re_De_0,                (ulong32)(E2Addr_Qua2A_Re_De_0),            0,      (CLQua2A_Re_De_0),              C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua3A_Re_De_0,                (ulong32)(E2Addr_Qua3A_Re_De_0),            0,      (CLQua3A_Re_De_0),              C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua4A_Re_De_0,                (ulong32)(E2Addr_Qua4A_Re_De_0),            0,      (CLQua4A_Re_De_0),              C_WR_Msg_DemandMetering,            DT_E23_Clear},

    {CPosB_Ac_De_0,                 (ulong32)(E2Addr_PosB_Ac_De_0),             0,      (CLPosB_Ac_De_0),               C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CRevB_Ac_De_0,                 (ulong32)(E2Addr_RevB_Ac_De_0),             0,      (CLRevB_Ac_De_0),               C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CComB_Re1_De_0,                (ulong32)(E2Addr_ComB_Re1_De_0),            0,      (CLComB_Re1_De_0),              C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CComB_Re2_De_0,                (ulong32)(E2Addr_ComB_Re2_De_0),            0,      (CLComB_Re2_De_0),              C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua1B_Re_De_0,                (ulong32)(E2Addr_Qua1B_Re_De_0),            0,      (CLQua1B_Re_De_0),              C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua2B_Re_De_0,                (ulong32)(E2Addr_Qua2B_Re_De_0),            0,      (CLQua2B_Re_De_0),              C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua3B_Re_De_0,                (ulong32)(E2Addr_Qua3B_Re_De_0),            0,      (CLQua3B_Re_De_0),              C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua4B_Re_De_0,                (ulong32)(E2Addr_Qua4B_Re_De_0),            0,      (CLQua4B_Re_De_0),              C_WR_Msg_DemandMetering,            DT_E23_Clear},

    {CPosC_Ac_De_0,                 (ulong32)(E2Addr_PosC_Ac_De_0),             0,      (CLPosC_Ac_De_0),               C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CRevC_Ac_De_0,                 (ulong32)(E2Addr_RevC_Ac_De_0),             0,      (CLRevC_Ac_De_0),               C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CComC_Re1_De_0,                (ulong32)(E2Addr_ComC_Re1_De_0),            0,      (CLComC_Re1_De_0),              C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CComC_Re2_De_0,                (ulong32)(E2Addr_ComC_Re2_De_0),            0,      (CLComC_Re2_De_0),              C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua1C_Re_De_0,                (ulong32)(E2Addr_Qua1C_Re_De_0),            0,      (CLQua1C_Re_De_0),              C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua2C_Re_De_0,                (ulong32)(E2Addr_Qua2C_Re_De_0),            0,      (CLQua2C_Re_De_0),              C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua3C_Re_De_0,                (ulong32)(E2Addr_Qua3C_Re_De_0),            0,      (CLQua3C_Re_De_0),              C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua4C_Re_De_0,                (ulong32)(E2Addr_Qua4C_Re_De_0),            0,      (CLQua4C_Re_De_0),              C_WR_Msg_DemandMetering,            DT_E23_Clear},
};
#define Str_2Table_DIDe10_Len  sizeof(Str_2Table_DIDe10)/sizeof(Str_2Table)

/***********变量类**************/
const Str_2Table Str_2Table_DIEvent20[]=
{ /* 数据标示                       对应三级表结构体数组地址                    应三级表行号  具体数据长度              对应消息号及是否支持读             数据类型    */

    /*注意：以下4个对象，通讯电表清零命令中清零，为提高搜索效率，放在表格前面，CY_Com_Ac_Tol_En_0对象必须放在4个对象最下面*/
    {CChargeBal_Hex_Cent,           (ulong32)(&Str_3aTable_E23RAM[0]),          93,     CLChargeBal_Hex_Deal,           C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {COverDraft_Hex_Cent,           (ulong32)(&Str_3aTable_E23RAM[0]),          94,     CLOverDraft_Hex_Deal,           C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CM_Com_Ac_Tol_En_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          91,     CLM_Com_Ac_Tol_En_Pul_0,        C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CY_Com_Ac_Tol_En_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          92,     CLY_Com_Ac_Tol_En_Pul_0,        C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},

    {CPhaseC_Volage,                (ulong32)(&GV_PhaseA_Volage[0][0]),         0,      CLPhaseC_Volage,                C_WR_Msg_MeterIC,                   DT_RAM_DI0},
    {CPhaseFF_Volage,               (ulong32)(&GV_PhaseA_Volage[0][0]),         0,      CLPhaseFF_Volage,               C_Only_Read,                        DT_RAM},
    {CInstantC_AcPow,               (ulong32)(&GV_Instant_TolAcPow[0][0]),      0,      CLInstantC_AcPow,               C_WR_Msg_MeterIC,                   DT_RAM_DI0},
    {CInstantFF_AcPow,              (ulong32)(&GV_Instant_TolAcPow[0][0]),      0,      CLInstantFF_AcPow,              C_Only_Read,                        DT_RAM},
    {CInstantC_RePow ,              (ulong32)(&GV_Instant_TolRePow[0][0]),      0,      CLInstantC_RePow,               C_WR_Msg_MeterIC,                   DT_RAM_DI0},
    {CInstantFF_RePow,              (ulong32)(&GV_Instant_TolRePow[0][0]),      0,      CLInstantFF_RePow,              C_Only_Read,                        DT_RAM},
    {CInstantC_AppaPow,             (ulong32)(&GV_Instant_TolAppaPow[0][0]),    0,      CLInstantC_AppaPow,             C_WR_Msg_MeterIC,                   DT_RAM_DI0},
    {CInstantFF_AppaPow,            (ulong32)(&GV_Instant_TolAppaPow[0][0]),    0,      CLInstantFF_AppaPow,            C_Only_Read,                        DT_RAM},
    {CPhaseC_PowerFactor,           (ulong32)(&GV_Tol_PowerFactor[0][0]),       0,      CLPhaseC_PowerFactor,           C_WR_Msg_MeterIC,                   DT_RAM_DI0},
    {CPhaseFF_PowerFactor,          (ulong32)(&GV_Tol_PowerFactor[0][0]),       0,      CLPhaseFF_PowerFactor,          C_Only_Read,                        DT_RAM},
    {CPhaseC_Angle,                 (ulong32)(&GV_PhaseA_Angle[0][0]),          0,      CLPhaseC_Angle,                 C_WR_Msg_MeterIC,                   DT_RAM_DI0},
    {CPhaseFF_Angle,                (ulong32)(&GV_PhaseA_Angle[0][0]),          0,      CLPhaseFF_Angle,                C_Only_Read,                        DT_RAM},
    {CZero_Current,                 (ulong32)(&GV_Zero_Current[0]),             0,      CLZero_Current,                 C_WR_Msg_MeterIC,                   DT_RAM},
    {CElecNet_Freq,                 (ulong32)(&GV_ElecNet_Freq[0]),             0,      CLElecNet_Freq,                 C_WR_Msg_MeterIC,                   DT_RAM},
    {CCurr_AcDemand,                (ulong32)(&GV_Curr_AcDemand[0]),            0,      CLCurr_AcDemand,                C_WR_Msg_DemandMetering,            DT_RAM},
    {CCurr_ReDemand,                (ulong32)(&GV_Curr_ReDemand[0]),            0,      CLCurr_ReDemand,                C_WR_Msg_DemandMetering,            DT_RAM},
    {CMeter_Temp,                   (ulong32)(&GV_Meter_Temp[0]),               0,      CLMeter_Temp,                   C_WR_Msg_MeterIC,                   DT_RAM},
    {CCloc_Batt_Vol,                (ulong32)(&GV_Cloc_Batt_Vol[0]),            0,      CLCloc_Batt_Vol,                C_WR_Msg_BatteryVoltagleMetering,   DT_RAM},
    {CReadMeter_Batt_Vol,           (ulong32)(&GV_ReadMeter_Batt_Vol[0]),       0,      CLReadMeter_Batt_Vol,           C_WR_Msg_BatteryVoltagleMetering,   DT_RAM},
    {CBatt_Work_Time,               (ulong32)(E2Addr_Batt_Work_Time),           0,      CLBatt_Work_Time,               C_WR_Msg_Dispatch,                  DT_E23},
    {CCurr_Ladder_Price,            (ulong32)(&GV_Curr_Ladder_Price[0]),        0,      CLCurr_Ladder_Price,            C_WR_Msg_EnergyMetering,            DT_RAM},
    {CCurr_Price,                   (ulong32)(&GV_Curr_Price[0]),               0,      CLCurr_Price,                   C_WR_Msg_EnergyMetering,            DT_RAM},
    {CCurr_Rate_Price,              (ulong32)(&GV_Curr_Rate_Price[0]),          0,      CLCurr_Rate_Price,              C_WR_Msg_En_Deal,                   DT_RAMCRC},
    {CMeter_Work_State7,            (ulong32)(&GV_Meter_Work_State[0][0]),      0,      CLMeter_Work_State7,            C_WR_All,                           DT_RAM_DI0},
    {CControl_ExecuteState,         (ulong32)(E2Addr_Control_ExecuteState),     0,      CLControl_ExecuteState,         C_WR_Msg_Comm_Relay,                DT_E21},
    {CControl_ErrorState,           (ulong32)(E2Addr_Control_ErrorState),       0,      CLControl_ErrorState,           C_WR_Msg_Comm_Relay,                DT_E21},
#if 0
    {CControl_ExecuteStateUn,       (ulong32)(E2Addr_Control_ExecuteStateUn),   0,      CLControl_ExecuteStateUn,       C_WR_Msg_Comm_Relay,                DT_E21},
#endif
    {CVolC_Phase,                   (ulong32)(&GV_VolA_Phase[0][0]),            0,      CLVolC_Phase,                   C_WR_Msg_MeterIC,                   DT_RAM_DI0},
    {CVolFF_Phase,                  (ulong32)(&GV_VolA_Phase[0][0]),            0,      CLVolFF_Phase,                  C_Only_Read,                        DT_RAM},
    {CDrive_Report_Mode,            (ulong32)(&Str_3aTable_E23RAM[0]),          210,    CLDrive_Report_Mode,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CBuyCurr_TMoney,               (ulong32)(E2Addr_BuyCurr_TMoney),           0,      CLBuyCurr_TMoney,               C_WR_Msg_EnergyMetering,            DT_E23},
    {CDrive_Report_State,           (ulong32)(E2Drive_Report_State_New),        0,      CLDrive_Report_State_New,       C_WR_Msg_Communication,             DT_E21},
    {CDrive_Report_Type,            (ulong32)(&Str_3aTable_E23RAM[0]),          344,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CVector_Current ,              (ulong32)(&GV_Vector_Current[0]),           0,      CLVector_Current,               C_WR_Msg_MeterIC,                   DT_RAM},
};
#define Str_2Table_DIEvent20_Len  sizeof(Str_2Table_DIEvent20)/sizeof(Str_2Table)

const Str_2Table Str_2Table_DIEvent21[]=
{ /* 数据标示                       对应三级表结构体数组地址                    应三级表行号  具体数据长度              对应消息号及是否支持读                 数据类型    */
    {CVolA_Per_Pass_0,              (ulong32)(&GV_CurrMVolPerPass[1][0]),       0,      CLVolA_Per_Pass_M,		C_WR_Msg_VoltageQualifiedRateMetering,DT_RAMCRC},
    {CVolB_Per_Pass_0,              (ulong32)(&GV_CurrMVolPerPass[2][0]),       0,      CLVolB_Per_Pass_M,		C_WR_Msg_VoltageQualifiedRateMetering,DT_RAMCRC},
    {CVolC_Per_Pass_0,              (ulong32)(&GV_CurrMVolPerPass[3][0]),       0,      CLVolC_Per_Pass_M,		C_WR_Msg_VoltageQualifiedRateMetering,DT_RAMCRC},
    {CVolA_Per_Pass_0_Freeze,       (ulong32)(&GV_CurrDVolPerPass[1][0]),       0,      CLVolA_Per_Pass_D,		C_WR_Msg_VoltageQualifiedRateMetering,DT_RAMCRC},
    {CVolB_Per_Pass_0_Freeze,       (ulong32)(&GV_CurrDVolPerPass[2][0]),       0,      CLVolB_Per_Pass_D,		C_WR_Msg_VoltageQualifiedRateMetering,DT_RAMCRC},
    {CVolC_Per_Pass_0_Freeze,       (ulong32)(&GV_CurrDVolPerPass[3][0]),       0,      CLVolC_Per_Pass_D,		C_WR_Msg_VoltageQualifiedRateMetering,DT_RAMCRC},

};
#define Str_2Table_DIEvent21_Len  sizeof(Str_2Table_DIEvent21)/sizeof(Str_2Table)

/***********事件类**************/
const Str_2Table Str_2Table_DIEvent30[]=
{ /* 数据标示                       对应三级表结构体数组地址                    应三级表行号  具体数据长度              对应消息号及是否支持读             数据类型    */
    {CLossVolage_Vol_UpLim,         (ulong32)(&Str_3aTable_E23RAM[0]),          141,    CLLossVolage_Vol_UpLim,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CLossVolage_Vol_LowLim,        (ulong32)(&Str_3aTable_E23RAM[0]),          142,    CLLossVolage_Vol_LowLim,        C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CLossVolage_Curr_LowLim,       (ulong32)(&Str_3aTable_E23RAM[0]),          143,    CLLossVolage_Curr_LowLim,       C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CLossVolage_Delay_T,           (ulong32)(&Str_3aTable_E23RAM[0]),          144,    CLLossVolage_Delay_T,           C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {CLowVolage_Vol_UpLim,          (ulong32)(&Str_3aTable_E23RAM[0]),          145,    CLLowVolage_Vol_UpLim,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CLowVolage_Delay_T,            (ulong32)(&Str_3aTable_E23RAM[0]),          146,    CLLowVolage_Delay_T,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {COverVolage_Vol_LowLim,        (ulong32)(&Str_3aTable_E23RAM[0]),          147,    CLOverVolage_Vol_LowLim,        C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {COverVolage_Delay_T,           (ulong32)(&Str_3aTable_E23RAM[0]),          148,    CLOverVolage_Delay_T,           C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {CBreakVol_Vol_UpLim,           (ulong32)(&Str_3aTable_E23RAM[0]),          149,    CLBreakVol_Vol_UpLim,           C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CBreakVol_Curr_UpLim,          (ulong32)(&Str_3aTable_E23RAM[0]),          150,    CLBreakVol_Curr_UpLim,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CBreakVol_Delay_T,             (ulong32)(&Str_3aTable_E23RAM[0]),          151,    CLBreakVol_Delay_T,             C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {CNoBal_Vol_Lim,                (ulong32)(&Str_3aTable_E23RAM[0]),          152,    CLNoBal_Vol_Lim,                C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CNoBal_Vol_Delay_T,            (ulong32)(&Str_3aTable_E23RAM[0]),          153,    CLNoBal_Vol_Delay_T,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CNoBal_Curr_Lim,               (ulong32)(&Str_3aTable_E23RAM[0]),          154,    CLNoBal_Curr_Lim,               C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CNoBal_Curr_Delay_T,           (ulong32)(&Str_3aTable_E23RAM[0]),          155,    CLNoBal_Curr_Delay_T,           C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {CSeriNoBal_Curr_Lim,           (ulong32)(&Str_3aTable_E23RAM[0]),          156,    CLSeriNoBal_Curr_Lim,           C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CSeriNoBal_Curr_Delay_T,       (ulong32)(&Str_3aTable_E23RAM[0]),          157,    CLSeriNoBal_Curr_Delay_T,       C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {CLossCurr_Vol_LowLim,          (ulong32)(&Str_3aTable_E23RAM[0]),          158,    CLLossCurr_Vol_LowLim,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CLossCurr_Curr_UpLim,          (ulong32)(&Str_3aTable_E23RAM[0]),          159,    CLLossCurr_Curr_UpLim,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CLossCurr_Curr_LowLim,         (ulong32)(&Str_3aTable_E23RAM[0]),          160,    CLLossCurr_Curr_LowLim,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CLossCurr_Delay_T,             (ulong32)(&Str_3aTable_E23RAM[0]),          161,    CLLossCurr_Delay_T,             C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {COverCurr_Curr_LowLim,         (ulong32)(&Str_3aTable_E23RAM[0]),          162,    CLOverCurr_Curr_LowLim,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {COverCurr_Delay_T,             (ulong32)(&Str_3aTable_E23RAM[0]),          163,    CLOverCurr_Delay_T,             C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {CBreakCurr_Vol_LowLim,         (ulong32)(&Str_3aTable_E23RAM[0]),          164,    CLBreakCurr_Vol_LowLim,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CBreakCurr_Curr_UpLim,         (ulong32)(&Str_3aTable_E23RAM[0]),          165,    CLBreakCurr_Curr_UpLim,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CBreakCurr_Delay_T,            (ulong32)(&Str_3aTable_E23RAM[0]),          166,    CLBreakCurr_Delay_T,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {COverLoad_AcPower_LowLim,      (ulong32)(&Str_3aTable_E23RAM[0]),          167,    CLOverLoad_AcPower_LowLim,      C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {COverLoad_Delay_T,             (ulong32)(&Str_3aTable_E23RAM[0]),          168,    CLOverLoad_Delay_T,             C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {CPosAcDemandOv_De_LowLim,      (ulong32)(&Str_3aTable_E23RAM[0]),          169,    CLPosAcDemandOv_De_LowLim,      C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CPosAcDemandOv_Delay_T,        (ulong32)(&Str_3aTable_E23RAM[0]),          170,    CLPosAcDemandOv_Delay_T,        C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CRevAcDemandOv_De_LowLim,      (ulong32)(&Str_3aTable_E23RAM[0]),          171,    CLRevAcDemandOv_De_LowLim,      C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CRevAcDemandOv_Delay_T,        (ulong32)(&Str_3aTable_E23RAM[0]),          172,    CLRevAcDemandOv_Delay_T,        C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CReDemandOv_De_LowLim,         (ulong32)(&Str_3aTable_E23RAM[0]),          173,    CLReDemandOv_De_LowLim,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CReDemandOv_Delay_T,           (ulong32)(&Str_3aTable_E23RAM[0]),          174,    CLReDemandOv_Delay_T,           C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {CPowerFactor_LowLim,           (ulong32)(&Str_3aTable_E23RAM[0]),          175,    CLPowerFactor_LowLim,           C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CPowerFactor_Delay_T,          (ulong32)(&Str_3aTable_E23RAM[0]),          176,    CLPowerFactor_Delay_T,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CPowerRev_AcPower_LowLim,      (ulong32)(&Str_3aTable_E23RAM[0]),          177,    CLPowerRev_AcPower_LowLim,      C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CPowerRev_Delay_T,             (ulong32)(&Str_3aTable_E23RAM[0]),          178,    CLPowerRev_Delay_T,             C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {CNeutralAbnormal_Curr_LowLim,  (ulong32)(&Str_3aTable_E23RAM[0]),          179,    CLNeutralAbnormal_Curr_LowLim,  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CNeutralUnbalanceRate,         (ulong32)(&Str_3aTable_E23RAM[0]),          180,    CLNeutralUnbalanceRate,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CNeutralAbnormal_Delay_T,      (ulong32)(&Str_3aTable_E23RAM[0]),          181,    CLNeutralAbnormal_Delay_T,      C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {CReversedVoltage_Delay_T,      (ulong32)(&Str_3aTable_E23RAM[0]),          182,    CLReversedVoltage_Delay_T,      C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CReversedCurrent_Delay_T,      (ulong32)(&Str_3aTable_E23RAM[0]),          183,    CLReversedCurrent_Delay_T,      C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {CPowerOff_Delay_T,             (ulong32)(&Str_3aTable_E23RAM[0]),          184,    CLPowerOff_Delay_T,             C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {CAux_Pow_Down_Delay_T,         (ulong32)(&Str_3aTable_E23RAM[0]),          185,    CLAux_Pow_Down_Delay_T,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {CClockFa_Delay_T,              (ulong32)(&Str_3aTable_E23RAM[0]),          186,    CLClockFa_Delay_T,              C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CMeterFa_Delay_T,              (ulong32)(&Str_3aTable_E23RAM[0]),          187,    CLMeterFa_Delay_T,              C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {CLossVolage_Report_Mode,       (ulong32)(&Str_3aTable_E23RAM[0]),          244,    CLLossVolage_Report_Mode,       C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CLowVolage_Report_Mode,        (ulong32)(&Str_3aTable_E23RAM[0]),          245,    CLLowVolage_Report_Mode,        C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {COverVolage_Report_Mode,       (ulong32)(&Str_3aTable_E23RAM[0]),          246,    CLOverVolage_Report_Mode,       C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CBreakVol_Report_Mode,         (ulong32)(&Str_3aTable_E23RAM[0]),          247,    CLBreakVol_Report_Mode,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CLossCurr_Report_Mode,         (ulong32)(&Str_3aTable_E23RAM[0]),          248,    CLLossCurr_Report_Mode,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {COverCurr_Report_Mode,         (ulong32)(&Str_3aTable_E23RAM[0]),          249,    CLOverCurr_Report_Mode,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CBreakCurr_Report_Mode,        (ulong32)(&Str_3aTable_E23RAM[0]),          250,    CLBreakCurr_Report_Mode,        C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CPowerRev_Report_Mode,         (ulong32)(&Str_3aTable_E23RAM[0]),          251,    CLPowerRev_Report_Mode,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {COverLoad_Report_Mode,         (ulong32)(&Str_3aTable_E23RAM[0]),          252,    CLOverLoad_Report_Mode,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CPosAcDemandOv_Report_Mode,    (ulong32)(&Str_3aTable_E23RAM[0]),          253,    CLPosAcDemandOv_Report_Mode,    C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CRevAcDemandOv_Report_Mode,    (ulong32)(&Str_3aTable_E23RAM[0]),          254,    CLRevAcDemandOv_Report_Mode,    C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CReDemandOv_Report_Mode,       (ulong32)(&Str_3aTable_E23RAM[0]),          255,    CLReDemandOv_Report_Mode,       C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CPowerFactor_Report_Mode,      (ulong32)(&Str_3aTable_E23RAM[0]),          256,    CLPowerFactor_Report_Mode,      C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CAllLossVolage_Report_Mode,    (ulong32)(&Str_3aTable_E23RAM[0]),          257,    CLAllLossVolage_Report_Mode,    C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CAuxPowDown_Report_Mode,       (ulong32)(&Str_3aTable_E23RAM[0]),          258,    CLAuxPowDown_Report_Mode,       C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CReversedVoltage_Report_Mode,  (ulong32)(&Str_3aTable_E23RAM[0]),          259,    CLReversedVoltage_Report_Mode,  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CReversedCurrent_Report_Mode,  (ulong32)(&Str_3aTable_E23RAM[0]),          260,    CLReversedCurrent_Report_Mode,  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CPowerOff_Report_Mode,         (ulong32)(&Str_3aTable_E23RAM[0]),          261,    CLPowerOff_Report_Mode,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgram_Report_Mode,          (ulong32)(&Str_3aTable_E23RAM[0]),          262,    CLProgram_Report_Mode,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CTolClear_Report_Mode,         (ulong32)(&Str_3aTable_E23RAM[0]),          263,    CLTolClear_Report_Mode,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CDemandClear_Report_Mode,      (ulong32)(&Str_3aTable_E23RAM[0]),          264,    CLDemandClear_Report_Mode,      C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CEventClear_Report_Mode,       (ulong32)(&Str_3aTable_E23RAM[0]),          265,    CLEventClear_Report_Mode,       C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CAdjTime_Report_Mode,          (ulong32)(&Str_3aTable_E23RAM[0]),          266,    CLAdjTime_Report_Mode,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgPT_Report_Mode,           (ulong32)(&Str_3aTable_E23RAM[0]),          267,    CLProgPT_Report_Mode,           C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgPZ_Report_Mode,           (ulong32)(&Str_3aTable_E23RAM[0]),          268,    CLProgPZ_Report_Mode,           C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgWRe_Report_Mode,          (ulong32)(&Str_3aTable_E23RAM[0]),          269,    CLProgWRe_Report_Mode,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgSettD_Report_Mode,        (ulong32)(&Str_3aTable_E23RAM[0]),          270,    CLProgSettD_Report_Mode,        C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {COpenW_Report_Mode,            (ulong32)(&Str_3aTable_E23RAM[0]),          271,    CLOpenW_Report_Mode,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {COpenCW_Report_Mode,           (ulong32)(&Str_3aTable_E23RAM[0]),          272,    CLOpenCW_Report_Mode,           C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CNoBalVol_Report_Mode,         (ulong32)(&Str_3aTable_E23RAM[0]),          273,    CLNoBalVol_Report_Mode,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CNoBalCurr_Report_Mode,        (ulong32)(&Str_3aTable_E23RAM[0]),          274,    CLNoBalCurr_Report_Mode,        C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CRelayOpen_Report_Mode,        (ulong32)(&Str_3aTable_E23RAM[0]),          275,    CLRelayOpen_Report_Mode,        C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CRelayClose_Report_Mode,       (ulong32)(&Str_3aTable_E23RAM[0]),          276,    CLRelayClose_Report_Mode,       C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgHol_Report_Mode,          (ulong32)(&Str_3aTable_E23RAM[0]),          277,    CLProgHol_Report_Mode,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgAcC_Report_Mode,          (ulong32)(&Str_3aTable_E23RAM[0]),          278,    CLProgAcC_Report_Mode,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgReC_Report_Mode,          (ulong32)(&Str_3aTable_E23RAM[0]),          279,    CLProgReC_Report_Mode,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgTPara_Report_Mode,        (ulong32)(&Str_3aTable_E23RAM[0]),          280,    CLProgTPara_Report_Mode,        C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgLad_Report_Mode,          (ulong32)(&Str_3aTable_E23RAM[0]),          281,    CLProgLad_Report_Mode,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CKey_Update_Report_Mode,       (ulong32)(&Str_3aTable_E23RAM[0]),          282,    CLKey_Update_Report_Mode,       C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CAbnorC_Report_Mode,           (ulong32)(&Str_3aTable_E23RAM[0]),          283,    CLAbnorC_Report_Mode,           C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CBuyCurr_Report_Mode,          (ulong32)(&Str_3aTable_E23RAM[0]),          284,    CLBuyCurr_Report_Mode,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CReturnMoney_Report_Mode,      (ulong32)(&Str_3aTable_E23RAM[0]),          285,    CLReturnMoney_Report_Mode,      C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CConMEndEn_Report_Mode,        (ulong32)(&Str_3aTable_E23RAM[0]),          286,    CLConMEndEn_Report_Mode,        C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CRelayFaEndEn_Report_Mode,     (ulong32)(&Str_3aTable_E23RAM[0]),          287,    CLRelayFaEndEn_Report_Mode,     C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CPowerFa_EndT_Report_Mode,     (ulong32)(&Str_3aTable_E23RAM[0]),          288,    CLPowerFa_EndT_Report_Mode,     C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CSeriNoBalCurr_Report_Mode,    (ulong32)(&Str_3aTable_E23RAM[0]),          289,    CLSeriNoBalCurr_Report_Mode,    C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CClockFault_Report_Mode,       (ulong32)(&Str_3aTable_E23RAM[0]),          290,    CLClockFault_Report_Mode,       C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CMeteringChipFault_Report_Mode,(ulong32)(&Str_3aTable_E23RAM[0]),          291,    CLMeteringChipFault_Report_Mode,C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CBroadcastTime_Report_Mode,    (ulong32)(&Str_3aTable_E23RAM[0]),          292,    CLBroadcastTime_Report_Mode,    C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CABnor_ZeroCurrent_Report_Mode,(ulong32)(&Str_3aTable_E23RAM[0]),          293,    CLABnor_ZeroCurrent_Report_Mode,C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {CAll_Loss_Vol_Note_1,          (ulong32)(&Str_3d698EventTable_Flash[0]),   0,      CLAll_Loss_Vol_Note_1,          C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CAll_Loss_Vol_OADTab,          (ulong32)(&Str_3eTable_2E2[0]),             0,      C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CAux_Pow_Down_OADTab,          (ulong32)(&Str_3eTable_2E2[0]),             1,      C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CAux_Pow_Down_Note_1,          (ulong32)(&Str_3d698EventTable_Flash[0]),   1,      CLAux_Pow_Down_Note_1,          C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CPow_Down_OADTab,              (ulong32)(&Str_3eTable_2E2[0]),             2,      C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CPow_Down_Note_1,              (ulong32)(&Str_3d698EventTable_Flash[0]),   2,      CLPow_Down_Note_1,              C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CPos_Ac_De_Over_OADTab,        (ulong32)(&Str_3eTable_2E2[0]),             3,      C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CPos_Ac_De_Over_Note_1,        (ulong32)(&Str_3d698EventTable_Flash[0]),   3,      CLPos_Ac_De_Over_Note_1,        C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CRev_Ac_De_Over_OADTab,        (ulong32)(&Str_3eTable_2E2[0]),             4,      C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CRev_Ac_De_Over_Note_1,        (ulong32)(&Str_3d698EventTable_Flash[0]),   4,      CLRev_Ac_De_Over_Note_1,        C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CQua_Re_De_Over_OADTab,        (ulong32)(&Str_3eTable_2E2[0]),             5,      C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CQua1_Re_De_Over_Note_1,       (ulong32)(&Str_3d698EventTable_Flash[0]),   5,      CLQua1_Re_De_Over_Note_1,       C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CQua2_Re_De_Over_Note_1,       (ulong32)(&Str_3d698EventTable_Flash[0]),   6,      CLQua2_Re_De_Over_Note_1,       C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CQua3_Re_De_Over_Note_1,       (ulong32)(&Str_3d698EventTable_Flash[0]),   7,      CLQua3_Re_De_Over_Note_1,       C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CQua4_Re_De_Over_Note_1,       (ulong32)(&Str_3d698EventTable_Flash[0]),   8,      CLQua4_Re_De_Over_Note_1,       C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CLoss_Vol_OADTab,              (ulong32)(&Str_3eTable_2E2[0]),             6,      C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CLossAVol_FF_1,                (ulong32)(&Str_3d698EventTable_Flash[0]),   9,      CLLossAVol_FF_1,                C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CLossBVol_FF_1,                (ulong32)(&Str_3d698EventTable_Flash[0]),   10,     CLLossBVol_FF_1,                C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CLossCVol_FF_1,                (ulong32)(&Str_3d698EventTable_Flash[0]),   11,     CLLossCVol_FF_1,                C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CLow_Vol_OADTab,               (ulong32)(&Str_3eTable_2E2[0]),             7,      C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CLowAVol_FF_1,                 (ulong32)(&Str_3d698EventTable_Flash[0]),   12,     CLLowAVol_FF_1,                 C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CLowBVol_FF_1,                 (ulong32)(&Str_3d698EventTable_Flash[0]),   13,     CLLowBVol_FF_1,                 C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CLowCVol_FF_1,                 (ulong32)(&Str_3d698EventTable_Flash[0]),   14,     CLLowCVol_FF_1,                 C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {COver_Vol_OADTab,              (ulong32)(&Str_3eTable_2E2[0]),             8,      C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {COverAVol_FF_1,                (ulong32)(&Str_3d698EventTable_Flash[0]),   15,     CLOverAVol_FF_1,                C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {COverBVol_FF_1,                (ulong32)(&Str_3d698EventTable_Flash[0]),   16,     CLOverBVol_FF_1,                C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {COverCVol_FF_1,                (ulong32)(&Str_3d698EventTable_Flash[0]),   17,     CLOverCVol_FF_1,                C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CBreak_Vol_OADTab,             (ulong32)(&Str_3eTable_2E2[0]),             9,      C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CBreakAVol_FF_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   18,     CLBreakAVol_FF_1,               C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CBreakBVol_FF_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   19,     CLBreakBVol_FF_1,               C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CBreakCVol_FF_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   20,     CLBreakCVol_FF_1,               C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CRevPS_Vol_OADTab,             (ulong32)(&Str_3eTable_2E2[0]),             10,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CRevPSVol_FF_1,                (ulong32)(&Str_3d698EventTable_Flash[0]),   21,     CLRevPSVol_FF_1,                C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CRevPS_Curr_OADTab,            (ulong32)(&Str_3eTable_2E2[0]),             11,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CRevPSCurr_FF_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   22,     CLRevPSCurr_FF_1,               C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CNoBal_Vol_OADTab,             (ulong32)(&Str_3eTable_2E2[0]),             12,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CNoBalVol_FF_1,                (ulong32)(&Str_3d698EventTable_Flash[0]),   23,     CLNoBalVol_FF_1,                C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CNoBal_Curr_OADTab,            (ulong32)(&Str_3eTable_2E2[0]),             13,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CNoBalCurr_FF_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   24,     CLNoBalCurr_FF_1,               C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CSevNoBal_Curr_OADTab,         (ulong32)(&Str_3eTable_2E2[0]),             14,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CSevNoBalCurr_FF_1,            (ulong32)(&Str_3d698EventTable_Flash[0]),   25,     CLSevNoBalCurr_FF_1,            C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CLoss_Curr_OADTab,             (ulong32)(&Str_3eTable_2E2[0]),             15,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CLossACurr_FF_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   26,     CLLossACurr_FF_1,               C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CLossBCurr_FF_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   27,     CLLossBCurr_FF_1,               C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CLossCCurr_FF_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   28,     CLLossCCurr_FF_1,               C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {COver_Curr_OADTab,             (ulong32)(&Str_3eTable_2E2[0]),             16,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {COverACurr_FF_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   29,     CLOverACurr_FF_1,               C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {COverBCurr_FF_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   30,     CLOverBCurr_FF_1,               C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {COverCCurr_FF_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   31,     CLOverCCurr_FF_1,               C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CBreak_Curr_OADTab,            (ulong32)(&Str_3eTable_2E2[0]),             17,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CBreakACurr_FF_1,              (ulong32)(&Str_3d698EventTable_Flash[0]),   32,     CLBreakACurr_FF_1,              C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CBreakBCurr_FF_1,              (ulong32)(&Str_3d698EventTable_Flash[0]),   33,     CLBreakBCurr_FF_1,              C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CBreakCCurr_FF_1,              (ulong32)(&Str_3d698EventTable_Flash[0]),   34,     CLBreakCCurr_FF_1,              C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CPower_Rev_OADTab,             (ulong32)(&Str_3eTable_2E2[0]),             18,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CPowerTRev_FF_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   70,     CLPowerTRev_FF_1,               C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CPowerARev_FF_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   35,     CLPowerARev_FF_1,               C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CPowerBRev_FF_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   36,     CLPowerBRev_FF_1,               C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CPowerCRev_FF_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   37,     CLPowerCRev_FF_1,               C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {COver_Lo_OADTab,               (ulong32)(&Str_3eTable_2E2[0]),             19,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {COverALo_FF_1,                 (ulong32)(&Str_3d698EventTable_Flash[0]),   38,     CLOverALo_FF_1,                 C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {COverBLo_FF_1,                 (ulong32)(&Str_3d698EventTable_Flash[0]),   39,     CLOverBLo_FF_1,                 C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {COverCLo_FF_1,                 (ulong32)(&Str_3d698EventTable_Flash[0]),   40,     CLOverCLo_FF_1,                 C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CTol_Clear_OADTab,             (ulong32)(&Str_3eTable_2E2[0]),             20,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CTol_Clear_Note_1,             (ulong32)(&Str_3d698EventTable_Flash[0]),   41,     CLTol_Clear_Note_1,             C_WR_Msg_Communication,             DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CDe_Clear_OADTab,              (ulong32)(&Str_3eTable_2E2[0]),             21,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CDe_Clear_Note_1,              (ulong32)(&Str_3d698EventTable_Flash[0]),   42,     CLDe_Clear_Note_1,              C_WR_Msg_Communication,             DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CEven_Clear_OADTab,            (ulong32)(&Str_3eTable_2E2[0]),             22,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CEven_Clear_Note_1,            (ulong32)(&Str_3d698EventTable_Flash[0]),   43,     CLEven_Clear_Note_1,            C_WR_Msg_Communication,             DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CProgram_OADTab,               (ulong32)(&Str_3eTable_2E2[0]),             23,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CProgram_Note_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   44,     CLProgram_Note_1,               C_WR_Msg_Communication,             DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CAbnorC_OADTab,                (ulong32)(&Str_3eTable_2E2[0]),             24,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CAbnorC_Note_1,                (ulong32)(&Str_3d698EventTable_Flash[0]),   45,     CLAbnorC_Note_1,                C_WR_Msg_Card,                      DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CLawlessC_Degree,              (ulong32)(E2Addr_LawlessC_Degree),          0,      CLLawlessC_Degree,              C_WR_Msg_Card,                      DT_E23},
    {COpenW_OADTab,                 (ulong32)(&Str_3eTable_2E2[0]),             25,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {COpenW_Note_1,                 (ulong32)(&Str_3d698EventTable_Flash[0]),   46,     CLOpenW_Note_1,                 C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {COpenCW_OADTab,                (ulong32)(&Str_3eTable_2E2[0]),             26,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {COpenCW_Note_1,                (ulong32)(&Str_3d698EventTable_Flash[0]),   47,     CLOpenCW_Note_1,                C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CBuyCurr_OADTab,               (ulong32)(&Str_3eTable_2E2[0]),             27,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CBuyCurr_FF_Note_1,            (ulong32)(&Str_3d698EventTable_Flash[0]),   48,     CLBuyCurr_FF_Note_1,            C_WR_Msg_Comm_Card,                 DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CReturn_M_OADTab,              (ulong32)(&Str_3eTable_2E2[0]),             28,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CReturn_M_Note_1,              (ulong32)(&Str_3d698EventTable_Flash[0]),   49,     CLReturn_M_Note_1,              C_WR_Msg_Communication,             DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CConM_OADTab,                  (ulong32)(&Str_3eTable_2E2[0]),             29,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CConM_Note_1,                  (ulong32)(&Str_3d698EventTable_Flash[0]),   50,     CLConM_Note_1,                  C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CRelayFa_OADTab,               (ulong32)(&Str_3eTable_2E2[0]),             30,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CRelayFa_Note_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   51,     CLRelayFa_Note_1,               C_WR_Msg_Deal_RelayStatus,          DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CPowerFa_OADTab,               (ulong32)(&Str_3eTable_2E2[0]),             31,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CPowerFa_Note_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   52,     CLPowerFa_Note_1,               C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CRelayOpen_OADTab,             (ulong32)(&Str_3eTable_2E2[0]),             32,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CRelayOpen_FF_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   53,     CLRelayOpen_FF_1,               C_WR_Msg_Deal_RelayStatus,          DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CRelayClose_OADTab,            (ulong32)(&Str_3eTable_2E2[0]),             33,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CRelayClose_FF_1,              (ulong32)(&Str_3d698EventTable_Flash[0]),   54,     CLRelayClose_FF_1,              C_WR_Msg_Deal_RelayStatus,          DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CPFactorT_FF_1,                (ulong32)(&Str_3d698EventTable_Flash[0]),   55,     CLPFactorT_FF_1,                C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CPFactorA_FF_1,                (ulong32)(&Str_3d698EventTable_Flash[0]),   72,     CLPFactorA_FF_1,                C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CPFactorB_FF_1,                (ulong32)(&Str_3d698EventTable_Flash[0]),   73,     CLPFactorB_FF_1,                C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CPFactorC_FF_1,                (ulong32)(&Str_3d698EventTable_Flash[0]),   74,     CLPFactorC_FF_1,                C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CPFactorT_Over_OADTab,         (ulong32)(&Str_3eTable_2E2[0]),             34,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CAdjTime_Note_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   56,     CLAdjTime_Note_1,               C_WR_Msg_Communication,             DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CAdjTime_OADTab,               (ulong32)(&Str_3eTable_2E2[0]),             35,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CProgPT_Note_1,                (ulong32)(&Str_3d698EventTable_Flash[0]),   57,     CLProgPT_Note_1,                C_WR_Msg_Communication,             DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CProgPT_OADTab,                (ulong32)(&Str_3eTable_2E2[0]),             36,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CProgTZ_Note_1,                (ulong32)(&Str_3d698EventTable_Flash[0]),   58,     CLProgTZ_Note_1,                C_WR_Msg_Communication,             DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CProgTZ_OADTab,                (ulong32)(&Str_3eTable_2E2[0]),             37,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CProgWRe_Note_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   59,     CLProgWRe_Note_1,               C_WR_Msg_Communication,             DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CProgWRe_OADTab,               (ulong32)(&Str_3eTable_2E2[0]),             38,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CProgHol_Note_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   60,     CLProgHol_Note_1,               C_WR_Msg_Communication,             DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CProgHol_OADTab,               (ulong32)(&Str_3eTable_2E2[0]),             39,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CProgAcC_Note_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   61,     CLProgAcC_Note_1,               C_WR_Msg_Communication,             DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CProgAcC_OADTab,               (ulong32)(&Str_3eTable_2E2[0]),             40,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CProgReC_Note_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   62,     CLProgReC_Note_1,               C_WR_Msg_Communication,             DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CProgReC_OADTab,               (ulong32)(&Str_3eTable_2E2[0]),             41,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CProgSettD_Note_1,             (ulong32)(&Str_3d698EventTable_Flash[0]),   63,     CLProgSettD_Note_1,             C_WR_Msg_Communication,             DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CProgSettD_OADTab,             (ulong32)(&Str_3eTable_2E2[0]),             42,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CProgTPara_Note_1,             (ulong32)(&Str_3d698EventTable_Flash[0]),   64,     CLProgTPara_Note_1,             C_WR_Msg_Communication,             DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CProgTPara_OADTab,             (ulong32)(&Str_3eTable_2E2[0]),             43,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CProgLad_Note_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   65,     CLProgLad_Note_1,               C_WR_Msg_Communication,             DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CProgLad_OADTab,               (ulong32)(&Str_3eTable_2E2[0]),             44,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CProgKD_Note_1,                (ulong32)(&Str_3d698EventTable_Flash[0]),   66,     CLProgKD_Note_1,                C_WR_Msg_Communication,             DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CProgKD_OADTab,                (ulong32)(&Str_3eTable_2E2[0]),             45,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CMeterFa_Note_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   67,     CLMeterFa_Note_1,               C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CMeterFa_OADTab,               (ulong32)(&Str_3eTable_2E2[0]),             46,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CClockFa_Note_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   68,     CLClockFa_Note_1,               C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CClockFa_OADTab,               (ulong32)(&Str_3eTable_2E2[0]),             47,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CBroadcastTime_Note_1,         (ulong32)(&Str_3d698EventTable_Flash[0]),   69,     CLBroadcastTime_Note_1,         C_WR_Msg_Communication,             DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CBroadcastTime_OADTab,         (ulong32)(&Str_3eTable_2E2[0]),             48,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CNeutralCurrentAbnormal_Note_1,(ulong32)(&Str_3d698EventTable_Flash[0]),   71,     CLNeutralCurrentAbnormal_Note_1,C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*读数据时，长度需计算*/
    {CNeutralCurrentAbnormal_OADTab,(ulong32)(&Str_3eTable_2E2[0]),             49,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},

    {CLossVolage_Report_Type,       (ulong32)(&Str_3aTable_E23RAM[0]),          294,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CLowVolage_Report_Type,        (ulong32)(&Str_3aTable_E23RAM[0]),          295,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {COverVolage_Report_Type,       (ulong32)(&Str_3aTable_E23RAM[0]),          296,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CBreakVol_Report_Type,         (ulong32)(&Str_3aTable_E23RAM[0]),          297,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CLossCurr_Report_Type,         (ulong32)(&Str_3aTable_E23RAM[0]),          298,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {COverCurr_Report_Type,         (ulong32)(&Str_3aTable_E23RAM[0]),          299,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CBreakCurr_Report_Type,        (ulong32)(&Str_3aTable_E23RAM[0]),          300,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CPowerRev_Report_Type,         (ulong32)(&Str_3aTable_E23RAM[0]),          301,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {COverLoad_Report_Type,         (ulong32)(&Str_3aTable_E23RAM[0]),          302,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CPosAcDemandOv_Report_Type,    (ulong32)(&Str_3aTable_E23RAM[0]),          303,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CRevAcDemandOv_Report_Type,    (ulong32)(&Str_3aTable_E23RAM[0]),          304,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CReDemandOv_Report_Type,       (ulong32)(&Str_3aTable_E23RAM[0]),          305,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CPowerFactor_Report_Type,      (ulong32)(&Str_3aTable_E23RAM[0]),          306,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CAllLossVolage_Report_Type,    (ulong32)(&Str_3aTable_E23RAM[0]),          307,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CAuxPowDown_Report_Type,       (ulong32)(&Str_3aTable_E23RAM[0]),          308,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CReversedVoltage_Report_Type,  (ulong32)(&Str_3aTable_E23RAM[0]),          309,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CReversedCurrent_Report_Type,  (ulong32)(&Str_3aTable_E23RAM[0]),          310,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CPowerOff_Report_Type,         (ulong32)(&Str_3aTable_E23RAM[0]),          311,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgram_Report_Type,          (ulong32)(&Str_3aTable_E23RAM[0]),          312,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CTolClear_Report_Type,         (ulong32)(&Str_3aTable_E23RAM[0]),          313,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CDemandClear_Report_Type,      (ulong32)(&Str_3aTable_E23RAM[0]),          314,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CEventClear_Report_Type,       (ulong32)(&Str_3aTable_E23RAM[0]),          315,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CAdjTime_Report_Type,          (ulong32)(&Str_3aTable_E23RAM[0]),          316,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgPT_Report_Type,           (ulong32)(&Str_3aTable_E23RAM[0]),          317,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgPZ_Report_Type,           (ulong32)(&Str_3aTable_E23RAM[0]),          318,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgWRe_Report_Type,          (ulong32)(&Str_3aTable_E23RAM[0]),          319,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgSettD_Report_Type,        (ulong32)(&Str_3aTable_E23RAM[0]),          320,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {COpenW_Report_Type,            (ulong32)(&Str_3aTable_E23RAM[0]),          321,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {COpenCW_Report_Type,           (ulong32)(&Str_3aTable_E23RAM[0]),          322,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CNoBalVol_Report_Type,         (ulong32)(&Str_3aTable_E23RAM[0]),          323,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CNoBalCurr_Report_Type,        (ulong32)(&Str_3aTable_E23RAM[0]),          324,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CRelayOpen_Report_Type,        (ulong32)(&Str_3aTable_E23RAM[0]),          325,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CRelayClose_Report_Type,       (ulong32)(&Str_3aTable_E23RAM[0]),          326,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgHol_Report_Type,          (ulong32)(&Str_3aTable_E23RAM[0]),          327,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgAcC_Report_Type,          (ulong32)(&Str_3aTable_E23RAM[0]),          328,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgReC_Report_Type,          (ulong32)(&Str_3aTable_E23RAM[0]),          329,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgTPara_Report_Type,        (ulong32)(&Str_3aTable_E23RAM[0]),          330,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgLad_Report_Type,          (ulong32)(&Str_3aTable_E23RAM[0]),          331,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CKey_Update_Report_Type,       (ulong32)(&Str_3aTable_E23RAM[0]),          332,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CAbnorC_Report_Type,           (ulong32)(&Str_3aTable_E23RAM[0]),          333,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CBuyCurr_Report_Type,          (ulong32)(&Str_3aTable_E23RAM[0]),          334,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CReturnMoney_Report_Type,      (ulong32)(&Str_3aTable_E23RAM[0]),          335,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CConMEndEn_Report_Type,        (ulong32)(&Str_3aTable_E23RAM[0]),          336,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CRelayFaEndEn_Report_Type,     (ulong32)(&Str_3aTable_E23RAM[0]),          337,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CPowerFa_EndT_Report_Type,     (ulong32)(&Str_3aTable_E23RAM[0]),          338,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CSeriNoBalCurr_Report_Type,    (ulong32)(&Str_3aTable_E23RAM[0]),          339,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CClockFault_Report_Type,       (ulong32)(&Str_3aTable_E23RAM[0]),          340,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CMeteringChipFault_Report_Type,(ulong32)(&Str_3aTable_E23RAM[0]),          341,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CBroadcastTime_Report_Type,    (ulong32)(&Str_3aTable_E23RAM[0]),          342,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CABnor_ZeroCurrent_Report_Type,(ulong32)(&Str_3aTable_E23RAM[0]),          343,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
};
#define Str_2Table_DIEvent30_Len  sizeof(Str_2Table_DIEvent30)/sizeof(Str_2Table)

const Str_2Table Str_2Table_DIReport[]=
{ /* 数据标示                       对应三级表结构体数组地址                    应三级表行号  具体数据长度          对应消息号及是否支持读     数据类型   */
    {CNewReportList,                (ulong32)(E2NewReportList),                 0,      CLNewReportList,            C_WR_Msg_Communication,     DT_E21},
};
#define Str_2Table_DIReport_Len  sizeof(Str_2Table_DIReport)/sizeof(Str_2Table)

/***********参变量类**************/
const Str_2Table Str_2Table_DIParamChild40[]=
{ /* 数据标示                       对应三级表结构体数组地址                    对应三级表行号   具体数据长度           对应消息号及是否支持读              数据类型   */
    {CChange_TZ_Time,               (ulong32)(&Str_3aTable_E23RAM[0]),          99,     CLChange_TZ_Time,               C_WR_Msg_Comm_Deal,                 DT_Ref_E23_RAMCRC},
    {CChange_PT_Time,               (ulong32)(&Str_3aTable_E23RAM[0]),          100,    CLChange_PT_Time,               C_WR_Msg_Comm_Deal,                 DT_Ref_E23_RAMCRC},
    {CChange_Rate,                  (ulong32)(&Str_3aTable_E23RAM[0]),          101,    CLChange_Rate,                  C_WR_Msg_Comm_Deal_Card,            DT_Ref_E23_RAMCRC},
    {CChange_Ladder,                (ulong32)(&Str_3aTable_E23RAM[0]),          102,    CLChange_Ladder,                C_WR_Msg_Comm_Deal_Card,            DT_Ref_E23_RAMCRC},

    {CYear_Zone_Num,                (ulong32)(&Str_3aTable_E23RAM[0]),          103,    CLYear_Zone_Num,                C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CDay_Table_Num,                (ulong32)(&Str_3aTable_E23RAM[0]),          104,    CLDay_Table_Num,                C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CDay_Time_Num,                 (ulong32)(&Str_3aTable_E23RAM[0]),          105,    CLDay_Time_Num,                 C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CRate_Num,                     (ulong32)(&Str_3aTable_E23RAM[0]),          106,    CLRate_Num,                     C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CHoliday_Num,                  (ulong32)(&Str_3aTable_E23RAM[0]),          107,    CLHoliday_Num,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CStep_Num,                     (ulong32)(&Str_3aTable_E23RAM[0]),          108,    CLStep_Num,                     C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

#if 0
    {CKey_Tol_Num,                  (ulong32)(&Str_3aTable_E23RAM[0]),          59,     CLKey_Tol_Num,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
#endif
    {CPowerOn_Dis_All_Time,         (ulong32)(&Str_3aTable_E23RAM[0]),          115,    CLPowerOn_Dis_All_Time,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CBacklightTime,                (ulong32)(&Str_3aTable_E23RAM[0]),          116,    CLBacklightTime,                C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*背光点亮时间*/
    {CSViewBacklightTime,           (ulong32)(&Str_3aTable_E23RAM[0]),          117,    CLSViewBacklightTime,           C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*显示查看背光点亮时间*/
    {CNEScreenDisplay,              (ulong32)(&Str_3aTable_E23RAM[0]),          118,    CLNEScreenDisplay,              C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*无电按键屏幕驻留最大时间*/
    {CEnergy_Decimal_Num,           (ulong32)(&Str_3aTable_E23RAM[0]),          119,    CLEnergy_Decimal_Num,           C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CPower_Decimal_Num,            (ulong32)(&Str_3aTable_E23RAM[0]),          120,    CLPower_Decimal_Num,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {C1And2Display,                 (ulong32)(&Str_3aTable_E23RAM[0]),          121,    CL1And2Display,                 C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*液晶①②字样意义*/

    {CRatio_Curr_Tran,              (ulong32)(&Str_3aTable_E23RAM[0]),          122,    CLRatio_Curr_Tran,              C_WR_Msg_Comm_Card,                 DT_Ref_E23_RAMCRC},
    {CRatio_Vol_Tran,               (ulong32)(&Str_3aTable_E23RAM[0]),          123,    CLRatio_Vol_Tran,               C_WR_Msg_Comm_Card,                 DT_Ref_E23_RAMCRC},

    {CComm_Address,                 (ulong32)(&Str_3aTable_E23RAM[0]),          135,    CLComm_Address,                 C_WR_Msg_Communication,               DT_Ref_E23_RAMCRC},
    {CMeter_Num,                    (ulong32)(E2Addr_Meter_Num),                0,      CLMeter_Num,                    C_WR_Msg_Comm_Card,                 DT_E23},
    {CCustomer_Num,                 (ulong32)(E2Addr_Customer_Num),             0,      CLCustomer_Num,                 C_WR_Msg_Comm_Card,                 DT_E23},
    {CMeter_Position,               (ulong32)(E2Addr_Meter_Position),           0,      CLMeter_Position,               C_WR_Msg_Communication,             DT_E23},

    {CWeek_RestDay,                 (ulong32)(&Str_3aTable_E23RAM[0]),          131,    CLWeek_RestDay ,                C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CWeek_RestDay_DTable,          (ulong32)(&Str_3aTable_E23RAM[0]),          132,    CLWeek_RestDay_DTable,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {CAlam2_Money,                  (ulong32)(&Str_3aTable_E23RAM[0]),          133,    CLAlam2_Money,                  C_WR_Msg_Comm_Card,                 DT_Ref_E23_RAMCRC_DI0},
    {CClose_Relay_Money,            (ulong32)(&Str_3aTable_E23RAM[0]),          134,    CLClose_Relay_Money,            C_WR_Msg_Comm_Card,                 DT_Ref_E23_RAMCRC_DI0},

    {CInset_Card_State,             (ulong32)(&GV_Inset_Card_State[0]),         0,      CLInset_Card_State,             C_WR_Msg_Card,                      DT_RAM},

    {CFirst_TZone_Data,             (ulong32)(E2Addr_First_TZone_Data),         0,      CLFirst_TZone_Data,             C_WR_Msg_Comm_Deal_Card,            DT_E23},
    {CFirst_TZone_8PT_Data,         (ulong32)(E2Addr_First_TZone_1PT_Data),     0,      CLFirst_TZone_8PT_Data,         C_WR_Msg_Comm_Deal_Card,            DT_E23_DI0},
    {CSec_TZone_Data,               (ulong32)(E2Addr_Sec_TZone_Data),           0,      CLSec_TZone_Data,               C_WR_Msg_Communication,             DT_E23},
    {CSec_TZone_8PT_Data,           (ulong32)(E2Addr_Sec_TZone_1PT_Data),       0,      CLSec_TZone_8PT_Data,           C_WR_Msg_Communication,             DT_E23_DI0},
    {CHolidy_PT_Table20,            (ulong32)(E2Addr_Holidy_PT_Table1),         0,      CLHolidy_PT_Table1,            	C_WR_Msg_Communication,             DT_E21_DI0},

    {CCurrent_Rate12_Price,         (ulong32)(&Str_3aTable_E23RAM[0]),          137,    CLCurrent_Rate4_Price,          C_Only_Read,                        DT_Ref_E23_RAMCRC_DI0},
    {CCurrent_RateFF_Price,         (ulong32)(&Str_3aTable_E23RAM[0]),          137,    CLCurrent_RateFF_Price,         C_W_Msg_Card_Deal,                  DT_W_Ref_E23_RAMCRC_Te},
    {CBackUp_Rate12_Price,          (ulong32)(&Str_3aTable_E23RAM[0]),          138,    CLBackUp_Rate4_Price,           C_Only_Read,                        DT_Ref_E23_RAMCRC_DI0},
    {CBackUp_RateFF_Price,          (ulong32)(&Str_3aTable_E23RAM[0]),          138,    CLBackUp_RateFF_Price,          C_W_Msg_Comm_Card,                  DT_W_Ref_E23_RAMCRC_Te},

    {CCurrent_Ladder_Table,         (ulong32)(&Str_3aTable_E23RAM[0]),          139,    CLCurrent_Ladder_Table,         C_WR_Msg_Card_Deal,                 DT_Ref_E23_RAMCRC},
    {CCurrent_Ladder_Table_LadNum,  (ulong32)(&Str_3aTable_E23RAM[0]),          139,    CLCurrent_Ladder_Table_LadNum,  C_Only_Read,                        DT_R_Ref_E23_RAMCRC_Lad},
    {CCurrent_Ladder_Table_LadPri,  (ulong32)(&Str_3aTable_E23RAM[0]),          139,    CLCurrent_Ladder_Table_LadPri,  C_Only_Read,                        DT_R_Ref_E23_RAMCRC_Lad},
    {CCurrent_Ladder_Table_LadSett, (ulong32)(&Str_3aTable_E23RAM[0]),          139,    CLCurrent_Ladder_Table_LadSett, C_Only_Read,                        DT_R_Ref_E23_RAMCRC_Lad},

    {CBackUp_Ladder_Table,          (ulong32)(&Str_3aTable_E23RAM[0]),          140,    CLBackUp_Ladder_Table,          C_WR_Msg_Comm_Card,                 DT_Ref_E23_RAMCRC},
    {CBackUp_Ladder_Table_LadNum,   (ulong32)(&Str_3aTable_E23RAM[0]),          140,    CLBackUp_Ladder_Table_LadNum,   C_Only_Read,                        DT_R_Ref_E23_RAMCRC_Lad},
    {CBackUp_Ladder_Table_LadPri,   (ulong32)(&Str_3aTable_E23RAM[0]),          140,    CLBackUp_Ladder_Table_LadPri,   C_Only_Read,                        DT_R_Ref_E23_RAMCRC_Lad},
    {CBackUp_Ladder_Table_LadSett,  (ulong32)(&Str_3aTable_E23RAM[0]),          140,    CLBackUp_Ladder_Table_LadSett,  C_Only_Read,                        DT_R_Ref_E23_RAMCRC_Lad},

    {CVoltage_UpLim,                (ulong32)(&Str_3aTable_E23RAM[0]),          188,    CLVoltage_UpLim  ,              C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CVoltage_LowLim,               (ulong32)(&Str_3aTable_E23RAM[0]),          189,    CLVoltage_LowLim ,              C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CVolage_Check_LowLim,          (ulong32)(&Str_3aTable_E23RAM[0]),          190,    CLVolage_Check_LowLim,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC_DI0},

    {CDate_Time,                    (ulong32)(&GV_Date_Time[0]),                0,      CLDate_Week_Time ,              C_WR_Msg_Comm_Dis,                  DT_RAM_Time_Data},
    {CBroadcastTimeOffset_Min,      (ulong32)(&Str_3aTable_E23RAM[0]),          95,     CLBroadcastTimeOffset_Min,      C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*广播校时偏差最小值*/
    {CBroadcastTimeOffset_Max,      (ulong32)(&Str_3aTable_E23RAM[0]),          96,     CLBroadcastTimeOffset_Max,      C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*广播校时偏差最大值*/
};
#define Str_2Table_DIParamChild40_Len  (sizeof(Str_2Table_DIParamChild40)/sizeof(Str_2Table))

const Str_2Table Str_2Table_DIParamChild41[]=
{ /* 数据标示                       对应三级表结构体数组地址                    应三级表行号  具体数据长度              对应消息号及是否支持读             数据类型    */
    {CDemand_Cycle,                 (ulong32)(&Str_3aTable_E23RAM[0]),          97,     CLDemand_Cycle,                 C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CSliding_Time,                 (ulong32)(&Str_3aTable_E23RAM[0]),          98,     CLSliding_Time,                 C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CManage_Code,                  (ulong32)(E2Addr_Manage_Code),              0,      CLManage_Code,                  C_WR_Msg_Communication,             DT_E23},
    {CRated_Vol,                    (ulong32)(E2Addr_Rated_Vol),                0,      CLRated_Vol,                    C_WR_Msg_Communication,             DT_E23},
    {CRated_Curr,                   (ulong32)(E2Addr_Rated_Curr),               0,      CLRated_Curr,                   C_WR_Msg_Communication,             DT_E23},
    {CMax_Curr,                     (ulong32)(E2Addr_Max_Curr),                 0,      CLMax_Curr,                     C_WR_Msg_Communication,             DT_E23},
    {CMin_Curr,                     (ulong32)(E2Addr_Min_Curr),                 0,      CLMin_Curr,                     C_WR_Msg_Communication,             DT_E23},
    {CTurn_Curr,                    (ulong32)(E2Addr_Turn_Curr),                0,      CLTurn_Curr,                    C_WR_Msg_Communication,             DT_E23},
    {CActive_Accur_Deg,             (ulong32)(E2Addr_Active_Accur_Deg),         0,      CLActive_Accur_Deg,             C_WR_Msg_Communication,             DT_E23},
    {CReactive_Accur_Deg ,          (ulong32)(E2Addr_Reactive_Accur_Deg),       0,      CLReactive_Accur_Deg,           C_WR_Msg_Communication,             DT_E23},
    {CMeter_Ac_Const,               (ulong32)(E2Addr_Meter_Ac_Const),           0,      CLMeter_Ac_Const,               C_WR_Msg_Communication,             DT_E23},
    {CMeter_Re_Const,               (ulong32)(E2Addr_Meter_Re_Const),           0,      CLMeter_Re_Const,               C_WR_Msg_Communication,             DT_E23},
    {CMeter_Model,                  (ulong32)(E2Addr_Meter_Model),              0,      CLMeter_Model,                  C_WR_Msg_Communication,             DT_E23},
    {CActive_Com_State,             (ulong32)(&Str_3aTable_E23RAM[0]),          124,    CLActive_Com_State,             C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CReactive_Com_State1,          (ulong32)(&Str_3aTable_E23RAM[0]),          125,    CLReactive_Com_State1,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CReactive_Com_State2,          (ulong32)(&Str_3aTable_E23RAM[0]),          126,    CLReactive_Com_State2,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CSettle_Day3,                  (ulong32)(E2Addr_Settle_Day1),              0,      CLSettle_Day3,                  C_WR_Msg_Communication,             DT_E23_DI0},
    {CSoftw_Record_Number,          (ulong32)(E2Addr_Softw_Record_Number),      0,      CLSoftw_Record_Number,          C_WR_Msg_Communication,             DT_E21},
    {CMeter_Work_Char1,             (ulong32)(&Str_3aTable_E23RAM[0]),          348,    CLMeter_Work_Char1,             C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
};
#define Str_2Table_DIParamChild41_Len  (sizeof(Str_2Table_DIParamChild41)/sizeof(Str_2Table))

const Str_2Table Str_2Table_DIParamChild43[]=
{ /* 数据标示                       对应三级表结构体数组地址                    应三级表行号  具体数据长度              对应消息号及是否支持读             数据类型   */
    {CFactory_Softw_Version,        (ulong32)(E2Addr_Factory_Softw_Version),    0,      CLFactory_Softw_Version,        C_WR_Msg_Communication,             DT_E21},
    {CFactory_Hardw_Version,        (ulong32)(E2Addr_Factory_Hardw_Version),    0,      CLFactory_Hardw_Version,        C_WR_Msg_Communication,             DT_E21},
    {CProd_Date,                    (ulong32)(E2Addr_Prod_Date),                0,      CLProd_Date,                    C_WR_Msg_Communication,             DT_E23},
    {CFactory_Number,               (ulong32)(E2Addr_Factory_Number),           0,      CLFactory_Number,               C_WR_Msg_Communication,             DT_E21},
    {CFactory_Softw_VersionDate,    (ulong32)(E2Addr_Factory_Softw_VersionDate),0,      CLFactory_Softw_VersionDate,    C_WR_Msg_Communication,             DT_E21},
    {CFactory_Hardw_VersionDate,    (ulong32)(E2Addr_Factory_Hardw_VersionDate),0,      CLFactory_Hardw_VersionDate,    C_WR_Msg_Communication,             DT_E21},
    {CFactory_ExternSign,           (ulong32)(E2Addr_Factory_ExternSign),       0,      CLFactory_ExternSign,           C_WR_Msg_Communication,             DT_E21},
    {CAllowFollowUpTell,            (ulong32)(E2Addr_AllowFollowUpTell),        0,      CLAllowFollowUpTell,            C_WR_Msg_Communication,             DT_E23},
    {CAllowAccordUpTell,            (ulong32)(E2Addr_AllowAccordUpTell),        0,      CLAllowAccordUpTell,            C_WR_Msg_Communication,             DT_E23},
    {CEquipmentDis,                 (ulong32)(E2Addr_EquipmentDis),             0,      CLEquipmentDis,                 C_WR_Msg_Communication,             DT_E21},
    {CAllowMasterCall,              (ulong32)(E2Addr_AllowMasterCall),          0,      CLAllowMasterCall,              C_WR_Msg_Communication,             DT_E23},
    {CMeter_CommPro2,               (ulong32)(E2Addr_Meter_CommPro1),           0,      CLMeter_CommPro1,               C_WR_Msg_Communication,             DT_E21_DI0},
    {CUpTellChannel,                (ulong32)(E2Addr_UpTellChannel),            0,      CLUpTellChannel,                C_WR_Msg_Communication,             DT_E23},
};
#define Str_2Table_DIParamChild43_Len  (sizeof(Str_2Table_DIParamChild43)/sizeof(Str_2Table))

const Str_2Table Str_2Table_DIParamChild44[]=
{/* 数据标示                        对应三级表结构体数组地址                    对应三级表行号 具体数据长度              对应消息号及是否支持读             数据类型   */
    {CAppProInformation,            (ulong32)(&Str_3aTable_E23RAM[0]),          211,    CLAppProInformation,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*协议版本信息*/
    {CAppMaxReAPDU,                 (ulong32)(&Str_3aTable_E23RAM[0]),          212,    CLAppMaxReAPDU,                 C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*最大接收APDU尺寸*/
    {CAppMaxSeAPDU,                 (ulong32)(&Str_3aTable_E23RAM[0]),          213,    CLAppMaxSeAPDU,                 C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*最大发送APDU尺寸*/
    {CAppMaxHandleAPDU,             (ulong32)(&Str_3aTable_E23RAM[0]),          214,    CLAppMaxHandleAPDU,             C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*最大可处理APDU尺寸*/
    {CAppProConsistency,            (ulong32)(&Str_3aTable_E23RAM[0]),          215,    CLAppProConsistency,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*协议一致性块*/
    {CAppFunConsistency,            (ulong32)(&Str_3aTable_E23RAM[0]),          216,    CLAppFunConsistency,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*功能一致性块*/
    {CAppStaticTimeout,             (ulong32)(&Str_3aTable_E23RAM[0]),          217,    CLAppStaticTimeout,             C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*静态超时时间*/
    {CAppStaticTimeout_termal,      (ulong32)(&Str_3aTable_E23RAM[0]),          218,    CLAppStaticTimeout,             C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*终端静态超时时间*/
    {CConAutheMechanism,            (ulong32)(&Str_3aTable_E23RAM[0]),          219,    CLConAutheMechanism,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*连接认证机制*/
    {C698Key,                       (ulong32)(E2Addr_698Key),                   0,      CL698Key,                       C_WR_Msg_Communication,             DT_E23},
    {CClientAddr,                   (ulong32)(E2Addr_ClientAddr),               0,      CLClientAddr,                   C_WR_Msg_Communication,             DT_E21},
};
#define Str_2Table_DIParamChild44_Len (sizeof(Str_2Table_DIParamChild44)/sizeof(Str_2Table))

const Str_2Table Str_2Table_DIParamChild45[]=
{ /* 数据标示                   对应三级表结构体数组地址                        应三级表行号  具体数据长度              对应消息号及是否支持读             数据类型    */
    {CGPS_Signal,                   (ulong32)(&GV_GPS_Signal[0]),               0,      CLGPS_Signal,                   C_WR_Msg_Communication,             DT_RAM},
};
#define Str_2Table_DIParamChild45_Len  (sizeof(Str_2Table_DIParamChild45)/sizeof(Str_2Table))

const Str_2Table Str_2Table_DIParamChild80[]=
{/* 数据标示                        对应三级表结构体数组地址                   应三级表行号  具体数据长度               对应消息号及是否支持读             数据类型   */
#if 0
    {CRelay_Delay_Time,             (ulong32)(&Str_3aTable_E23RAM[0]),          90,     CLRelay_Delay_Time,             C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
#endif
    {CRelay_Open_CurrTreshold,      (ulong32)(&Str_3aTable_E23RAM[0]),          136,    CLRelay_Open_CurrTreshold,      C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CRelay_Open_CurrTimer,         (ulong32)(&Str_3aTable_E23RAM[0]),          204,    CLRelay_Open_CurrTimer,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
};
#define Str_2Table_DIParamChild80_Len  (sizeof(Str_2Table_DIParamChild80)/sizeof(Str_2Table))

const Str_2Table Str_2Table_DIParameterF1[]=
{ /* 数据标示                       对应三级表结构体数组地址                    应三级表行号  具体数据长度              对应消息号及是否支持读             数据类型    */
    {CID_Auth_Remain_Time,          (ulong32)(&GV_ID_Auth_Remain_Time[0]),      0,      CLID_Auth_Remain_Time,          C_WR_Msg_Communication,             DT_RAM},
    {CSafeModePara,                 (ulong32)(&Str_3aTable_E23RAM[0]),          220,    CLSafeModePara,                 C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*安全模式参数*/
#if 0
    {CKey_State,                    (ulong32)(&Str_3aTable_E23RAM[0]),          68,     CLKey_State,                    C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
#endif
    {CSafeModeParaNat3,             (ulong32)(E2Addr_SafeModeParaNat3),         0,      CLSafeModeParaNat3,             C_WR_Msg_Communication,             DT_E21CRC_MaxLen},
    {C_IRAuth_Timer,                (ulong32)(&Str_3aTable_E23RAM[0]),          205,    CL_IRAuth_Timer,                C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CInfra_Auth_Remain_Time,       (ulong32)(&GV_Infra_Auth_Remain_Time[0]),   0,      CLInfra_Auth_Remain_Time,       C_WR_Msg_Communication,             DT_RAM},
    {CID_Auth_T_Remain_Time,        (ulong32)(&GV_ID_Auth_T_Remain_Time[0]),    0,      CLInfra_Auth_Remain_Time,       C_WR_Msg_Communication,             DT_RAM},
};
#define Str_2Table_DIParameterF1_Len  sizeof(Str_2Table_DIParameterF1)/sizeof(Str_2Table)

const Str_2Table Str_2Table_DIParamChildF2[]=
{/* 数据标示                        对应三级表结构体数组地址                    应三级表行号  具体数据长度              对应消息号及是否支持读             数据类型   */
    {COne485_Baud,                  (ulong32)(&Str_3aTable_E23RAM[0]),          128,    CLOne485_Baud,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CTwo485_Baud,                  (ulong32)(&Str_3aTable_E23RAM[0]),          129,    CLTwo485_Baud,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CModular_Baud,                 (ulong32)(&Str_3aTable_E23RAM[0]),          130,    CLModular_Baud,                 C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
};
#define Str_2Table_DIParamChildF2_Len (sizeof(Str_2Table_DIParamChildF2)/sizeof(Str_2Table))

const Str_2Table Str_2Table_DIParamChildF3[]=
{ /* 数据标示                   对应三级表结构体数组地址                        对应三级表行号 具体数据长度             对应消息号及是否支持读              数据类型    */
    {CAuto_Dis_99ScreenCode,        (ulong32)(E2Addr_Auto_Dis_1ScreenCode),     0,      CLAuto_Dis_99ScreenCode,        C_WR_Msg_Communication,             DT_E21CRC_DI0},
    {CPer_Dis_Screen_Time,          (ulong32)(&Str_3aTable_E23RAM[0]),          109,    CLPer_Dis_Screen_Time,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CAuto_Dis_Screen_Num,          (ulong32)(&Str_3aTable_E23RAM[0]),          110,    CLAuto_Dis_Screen_Num,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {CKey_Dis_99ScreenCode,         (ulong32)(E2Addr_Key_Dis_1ScreenCode),      0,      CLKey_Dis_99ScreenCode,         C_WR_Msg_Communication,             DT_E21CRC_DI0},
    {CPerkey_Dis_Screen_Time,       (ulong32)(&Str_3aTable_E23RAM[0]),          112,    CLPerkey_Dis_Screen_Time,       C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CKey_CycDis_Screen_Num,        (ulong32)(&Str_3aTable_E23RAM[0]),          113,    CLKey_CycDis_Screen_Num,        C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
};
#define Str_2Table_DIParamChildF3_Len (sizeof(Str_2Table_DIParamChildF3)/sizeof(Str_2Table))

const Str_2Table Str_2Table_DIParam00[]=
{   /* 数据标示                     对应三级表结构体数组地址                   应三级表行号  具体数据长度              对应消息号及是否支持读              数据类型   */
    /*645规约支持，698规约不支持，依旧按照645数据标识定义*/
    {CProt_Version_Num,             (ulong32)(E2Addr_Prot_Version_Num),         0,      CLProt_Version_Num,             C_WR_Msg_Communication,             DT_E23},
    {CKey_4_Class,                  (ulong32)(E2Addr_Key_0_Class),              0,      CLKey_4_Class,                  C_WR_Msg_Comm_Dis,                  DT_E23_DI0},
    {CRst_ReportState_Timer,        (ulong32)(&Str_3aTable_E23RAM[0]),          203,    CLRst_ReportState_Timer,        C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
#if 0
    {CTiming_Freeze_Time,           (ulong32)(&Str_3aTable_E23RAM[0]),          89,     CLTiming_Freeze_Time,           C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
#endif
    {CRelay_Delay_Time_645,         (ulong32)(&Str_3aTable_E23RAM[0]),          345,    CLRelay_Delay_Time_645,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CDrive_Report_Mode_645,        (ulong32)(&Str_3aTable_E23RAM[0]),          346,    CLDrive_Report_Mode_645,        C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CMeter_Work_Char1_645,         (ulong32)(&Str_3aTable_E23RAM[0]),          347,    CLMeter_Work_Char1_645,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
};
#define Str_2Table_DIParam00_Len  (sizeof(Str_2Table_DIParam00)/sizeof(Str_2Table))

/***********参变量类，2级表分级表**************/
typedef struct
{
    ulong32 PStr_2TableParamChildAddr;  /*2级表分级表**/
    ushort16 V_Str_2TableLen;           /*2级表分级表--结构体数据长度*/
    uchar8 V_DI2;                       /*数据标识DI2*/
}Str_2TableChild;
const Str_2TableChild Str_2Table_DIParamChild[]=
{/* 2级表分级表                                2级表分级表--结构体数据长度        V_DI2*/
   {(ulong32)(Str_2Table_DIParam00),            Str_2Table_DIParam00_Len,          0x00},

};
#define Str_2Table_DIParamChild_Len  sizeof(Str_2Table_DIParamChild)/sizeof(Str_2TableChild)

/***********自扩类**************/
const Str_2Table    Str_2Table_DIParameterFF[]=
{
    /*电能量类*/
    /*注意：以下2个对象，通讯电表清零命令中清零，为提高搜索效率，放在表格前面，CM_Rev_Ac_Tol_En_Pul_1对象必须放在2个对象最下面*/
    {CM_Pos_Ac_Tol_En_Pul_1,        (ulong32)(E2Addr_M_Pos_Ac_Tol_En_Pul_1),    0,      CLM_Pos_Ac_Tol_En_Pul_1,        C_WR_Msg_SettleAccounts,            DT_E23_Clear},
    {CM_Rev_Ac_Tol_En_Pul_1,        (ulong32)(E2Addr_M_Rev_Ac_Tol_En_Pul_1),    0,      CLM_Rev_Ac_Tol_En_Pul_1,        C_WR_Msg_SettleAccounts,            DT_E23_Clear},
    {CChargeBal_Hex_Full,           (ulong32)(&Str_3aTable_E23RAM[0]),          93,     CLChargeBal_Hex_Full,           C_WR_Msg_EnergyMetering,             DT_Ti_E23_RAMCRC},
    {COverDraft_Hex_Full,           (ulong32)(&Str_3aTable_E23RAM[0]),          94,     CLOverDraft_Hex_Full,           C_WR_Msg_EnergyMetering,             DT_Ti_E23_RAMCRC},

    /*变量类*/
    {COneMin_AcPower_C_Pre,         (ulong32)(&GV_OneMin_AcPower[0][0]),        0,      CLOneMin_AcPower,               C_WR_Msg_MeterIC,            		DT_RAM_DI0},
    {COneMin_AcPower_Pre_FF,        (ulong32)(&GV_OneMin_AcPower[0][0]),        0,      CLOneMin_AcPower_FF,            C_Only_Read,                        DT_RAM},
    {COneMin_RePower_C_Pre,         (ulong32)(&GV_OneMin_RePower[0][0]),        0,      CLOneMin_RePower,               C_WR_Msg_MeterIC,            		DT_RAM_DI0},
    {COneMin_RePower_Pre_FF,        (ulong32)(&GV_OneMin_RePower[0][0]),        0,      CLOneMin_RePower_FF,            C_Only_Read,                        DT_RAM},

    {CSoftI_J_RemainTime,           (ulong32)(FRAMAddr_SoftI_J_RemainTime),     0,      CLSoftI_J_RemainTime,           C_WR_Msg_Communication,             DT_FRAM1CRC},
    {CCurrMon_Vol_Pass_Time,        (ulong32)(&GV_CurrMon_Vol_Pass_Time[0]),    0,      CLCurrMon_Vol_Pass_Time,        C_WR_Msg_VoltageQualifiedRateMetering,DT_RAM},
    {CCurr_Rate_No,                 (ulong32)(&GV_Curr_Rate_No[0]),             0,      CLCurr_Rate_No,                 C_WR_Msg_Deal_MultiRates,           DT_RAM},
    {CCurr_Step_No,                 (ulong32)(&GV_Curr_Step_No[0]),             0,      CLCurr_Step_No,                 C_WR_Msg_EnergyMetering,            DT_RAM},
    {CEnter_LowPower_Time,          (ulong32)(FRAMAddr_Enter_LowPower_Time),    0,      CLEnter_LowPower_Time,          C_WR_Msg_Dispatch,                  DT_FRAM1CRC},
    {CExit_LowPower_Time,           (ulong32)(FRAMAddr_Exit_LowPower_Time),     0,      CLExit_LowPower_Time,           C_WR_Msg_Dispatch,                  DT_FRAM1CRC},
    {CCurrC_Phase,                  (ulong32)(&GV_CurrA_Phase[0][0]),           0,      CLCurrC_Phase,                  C_WR_Msg_MeterIC,                   DT_RAM_DI0},
    {CPhaseC_Curr_4Dig,             (ulong32)(&GV_PhaseA_Curr_4Dig[0][0]),      0,      CLPhaseC_Curr_4Dig,             C_WR_Msg_MeterIC,                   DT_RAM_DI0},
    {CPhaseFF_Curr_4Dig,            (ulong32)(&GV_PhaseA_Curr_4Dig[0][0]),      0,      CLPhaseFF_Curr_4Dig,            C_Only_Read,                        DT_RAM},
    {CRemote_Local_State,           (ulong32)(&Str_3aTable_E23RAM[0]),          209,    CLRemote_Local_State,           C_WR_Msg_Comm_Card,                 DT_Ref_E23_RAMCRC},
    {CReadMeter_Batt_LowState,      (ulong32)(E2Addr_Cloc_Batt_LowState),       0,      CLReadMeter_Batt_LowState,      C_WR_Msg_BatteryVoltagleMetering,   DT_E23_DI0},
    {CESAM_FaultState,              (ulong32)(E2Addr_ESAM_FaultState),          0,      CLESAM_FaultState,              C_WR_Msg_Esam,                      DT_E23},
    {CClock_FaultState,             (ulong32)(E2Addr_Clock_FaultState),         0,      CLClock_FaultState,             C_WR_Msg_Dispatch,                  DT_E23},
    {CReportNewAddNum,              (ulong32)(E2Addr_ReportNewAddNum),          0,      CLReportNewAddNum,              C_WR_Msg_Communication,             DT_E23},
    {CHaveReportState,              (ulong32)(E2Addr_HaveReportState),          0,      CLHaveReportState,              C_WR_Msg_Communication,             DT_E23},
    {CCap_Vol,                      (ulong32)(&GV_Cap_Vol[0]),                  0,      CLCap_Vol,                      C_WR_Msg_BatteryVoltagleMetering,   DT_RAM},
    {CID_Auth_Remain_Time_645,      (ulong32)(&GV_ID_Auth_Remain_Time_645[0]),  0,      CLID_Auth_Remain_Time_645,      C_WR_Msg_Communication,             DT_RAM},
    {CInfra_Auth_Remain_Time_645,   (ulong32)(&GV_Infra_Auth_Remain_Time_645[0]),0,     CLInfra_Auth_Remain_Time_645,   C_WR_Msg_Communication,             DT_RAM},
    {CClock_FaultTime,              (ulong32)(E2Addr_Clock_FaultTime),          0,      CLClock_FaultTime,              C_WR_Msg_Communication,             DT_E21},
    {CDoubleAgreementFlag,          (ulong32)(E2Addr_CDoubleAgreementFlag),     0,      CLDoubleAgreementFlag,          C_WR_Msg_Communication,             DT_E21},
    /*参变量类*/
    {CAlarm_Status,                 (ulong32)(&Str_3aTable_E23RAM[0]),          202,    CLAlarm_Status,                 C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CNeutralCurrentAbnormal_OADTabLen,  (ulong32)(E2Addr_All_Loss_Vol_OADTabLen),   0,      CLNeutralCurrentAbnormal_OADTabLen,  C_WR_Msg_Communication,             DT_E23_DI0},
    {CL_Free_OADTabLen_T,           (ulong32)(&Str_3aTable_E23RAM[0]),          221,    CLI_Free_OADTabLen_T,           C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC_DI0},
    {CI_Free_OADTab,                (ulong32)(&Str_3aTable_E23RAM[0]),          233,    C_698Free_OADTabLen,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*查2级表长度判断特殊处理*/
    {CMin_Free_OADTab,              (ulong32)(&Str_3aTable_E23RAM[0]),          234,    C_698Free_OADTabLen,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*查2级表长度判断特殊处理*/
    {CH_Free_OADTab,                (ulong32)(&Str_3aTable_E23RAM[0]),          235,    C_698Free_OADTabLen,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*查2级表长度判断特殊处理*/
    {CD_Free_OADTab,                (ulong32)(&Str_3aTable_E23RAM[0]),          236,    C_698Free_OADTabLen,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*查2级表长度判断特殊处理*/
    {CSett_Free_OADTab,             (ulong32)(&Str_3aTable_E23RAM[0]),          237,    C_698Free_OADTabLen,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*查2级表长度判断特殊处理*/
    {CM_Free_OADTab,                (ulong32)(&Str_3aTable_E23RAM[0]),          238,    C_698Free_OADTabLen,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*查2级表长度判断特殊处理*/
    {CYSettle_Free_OADTab,          (ulong32)(&Str_3aTable_E23RAM[0]),          239,    C_698Free_OADTabLen,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*查2级表长度判断特殊处理*/
    {CTZ_Free_OADTab,               (ulong32)(&Str_3aTable_E23RAM[0]),          240,    C_698Free_OADTabLen,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*查2级表长度判断特殊处理*/
    {CPT_Free_OADTab,               (ulong32)(&Str_3aTable_E23RAM[0]),          241,    C_698Free_OADTabLen,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*查2级表长度判断特殊处理*/
    {CR_Free_OADTab,                (ulong32)(&Str_3aTable_E23RAM[0]),          242,    C_698Free_OADTabLen,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*查2级表长度判断特殊处理*/
    {CL_Free_OADTab,                (ulong32)(&Str_3aTable_E23RAM[0]),          243,    C_698Free_OADTabLen,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*查2级表长度判断特殊处理*/
    {CZero_Current_Sign,            (ulong32)(&Str_3aTable_E23RAM[0]),          191,    CLZero_Current_Sign,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC_DI0},
    {CStart_Up_Current,             (ulong32)(&Str_3aTable_E23RAM[0]),          192,    CLStart_Up_Current,             C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CStart_Up_Power,               (ulong32)(&Str_3aTable_E23RAM[0]),          193,    CLStart_Up_Power,               C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CVolage_Abnor_Vol,             (ulong32)(&Str_3aTable_E23RAM[0]),          194,    CLVolage_Abnor_Vol,             C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CRelayOpen_Vol__UpLim,         (ulong32)(&Str_3aTable_E23RAM[0]),          195,    CLRelayOpen_Vol__UpLim,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC_DI0_2},
    {CPluse_Most__Lim,              (ulong32)(&Str_3aTable_E23RAM[0]),          196,    CLPluse_Most__Lim,              C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CCurr_Ratio_30A,               (ulong32)(&Str_3aTable_E23RAM[0]),          197,    CLCurr_Ratio_30A,               C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CPulse_Constant,               (ulong32)(&Str_3aTable_E23RAM[0]),          198,    CLPulse_Constant,               C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CSoftIJ_Valid_Time,            (ulong32)(&Str_3aTable_E23RAM[0]),          199,    CLSoftIJ_Valid_Time,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CExtern_Relay_PulW,            (ulong32)(&Str_3aTable_E23RAM[0]),          200,    CLExtern_Relay_PulW,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CKey_Update_ID,                (ulong32)(E2Addr_Key_Update_ID),            0,      CLKey_Update_ID,                C_WR_Msg_Communication,             DT_E23},
#if 0
    {CTemp_Key_State0,              (ulong32)(E2Addr_Temp_Key_State0),          0,      CLTemp_Key_State0,              C_WR_Msg_Communication,             DT_E21},
    {CTemp_Key_State31,             (ulong32)(E2Addr_Temp_Key_State1),          0,      CLTemp_Key_State31,             C_WR_Msg_Communication,             DT_E21_DI0},
    {CTemp_Key_StateFF,             (ulong32)(E2Addr_Temp_Key_State0),          0,      CLTemp_Key_StateFF,             C_WR_Msg_Communication,             DT_E21},
    {CTemp_Key_Save0,               (ulong32)(E2Addr_Temp_Key_Save0),           0,      CLTemp_Key_Save0,               C_WR_Msg_Communication,             DT_E21},
    {CTemp_Key_Save31,              (ulong32)(E2Addr_Temp_Key_Save1),           0,      CLTemp_Key_Save31,              C_WR_Msg_Communication,             DT_E21_DI0},
#endif
    {CMeterRunStatic,               (ulong32)(&Str_3aTable_E23RAM[0]),          201,    CLMeterRunStatic,               C_WR_Msg_Comm_Deal,                 DT_Ref_E23_RAMCRC},
    {CHardError_State,              (ulong32)(&GV_HardError_State[0]),          0,      CLHardError_State,              C_WR_Msg_MeterIC,                   DT_RAM},
    {CF1_TerUpCommParam,            (ulong32)(E2Addr_F1_TerUpCommParam),        0,      CLF1_TerUpCommParam,            C_WR_Msg_Communication,             DT_E23},
    {CF3_MainStaCommParam,          (ulong32)(E2Addr_F3_MainStaCommParam),      0,      CLF3_MainStaCommParam,          C_WR_Msg_Communication,             DT_E23},
    {CF4_SMSCommParam,              (ulong32)(E2Addr_F4_SMSCommParam),          0,      CLF4_SMSCommParam,              C_WR_Msg_Communication,             DT_E23},
    {CF7_TerminalIPAddr,            (ulong32)(E2Addr_F7_TerminalIPAddr),        0,      CLF7_TerminalIPAddr,            C_WR_Msg_Communication,             DT_E23},
    {CF8_ConnectParam,              (ulong32)(E2Addr_F8_ConnectParam),          0,      CLF8_ConnectParam,              C_WR_Msg_Communication,             DT_E23},
    {CF16_MoveAPNPassWord,          (ulong32)(E2Addr_F16_MoveAPNPassWord),      0,      CLF16_MoveAPNPassWord,          C_WR_Msg_Communication,             DT_E23},
    {CF89_TerminalAddr,             (ulong32)(E2Addr_F89_TerminalAddr),         0,      CLF89_TerminalAddr,             C_WR_Msg_Communication,             DT_E23},
    {CRelay_RemoteOrder,            (ulong32)(&Str_3aTable_E23RAM[0]),          206,    CLRelay_RemoteOrder,            C_WR_Msg_Deal_RelayStatus,          DT_Ref_E23_RAMCRC},
    {CRelay_State,                  (ulong32)(&Str_3aTable_E23RAM[0]),          207,    CLRelay_State,                  C_WR_Msg_Deal_RelayStatus,          DT_Ref_E23_RAMCRC},
    {CRelay_LocalOrder,             (ulong32)(&Str_3aTable_E23RAM[0]),          208,    CLRelay_LocalOrder,             C_WR_Msg_Deal_RelayStatus,          DT_Ref_E23_RAMCRC},
    {CRec_MeterSequence,            (ulong32)(E2Addr_Rec_MeterSequence),        0,      CLRec_MeterSequence,            C_WR_Msg_Communication,             DT_E23},
    {CRec_MeterPassWord,            (ulong32)(E2Addr_Rec_MeterPassWord),        0,      CLRec_MeterPassWord,            C_WR_Msg_Communication,             DT_E23},
    {C_UserCardNo,                  (ulong32)(E2Addr_UserCardNo),               0,      CL_UserCardNo,                  C_WR_Msg_Comm_Card,                 DT_E23},
    {CFactoryInMeterNum,            (ulong32)(E2Addr_FactoryInMeterNum),        0,      CLFactoryInMeterNum,            C_WR_Msg_Communication,             DT_E23},
    {CSafeModeParaNat3_Num,         (ulong32)(E2Addr_SafeModeParaNat3_Num),     0,      CLSafeModeParaNat3_Num,         C_WR_Msg_Communication,             DT_E23},
    {CProgReC2_Degree,              (ulong32)(E2Addr_ProgReC1),                 0,      CLProgReC1_Degree,              C_WR_Msg_Communication,             DT_E23_DI0},
    {C_OddHar_AddData1,             (ulong32)(E2Addr_Odd_Harmonic_AddData1),    0,      CL_OddHar_AddData1,             C_WR_Msg_Communication,             DT_E23},
    {C_OddHar_AddData2,             (ulong32)(E2Addr_Odd_Harmonic_AddData2),    0,      CL_OddHar_AddData2,             C_WR_Msg_Communication,             DT_E23},
    {C_EvenHar_AddData_A0,          (ulong32)(E2Addr_Even_Harmonic_AddData_A0), 0,      CL_EvenHar_AddData_A0,          C_WR_Msg_Communication,             DT_E23},
    {C_EvenHar_AddData_A1,          (ulong32)(E2Addr_Even_Harmonic_AddData_A1), 0,      CL_EvenHar_AddData_A1,          C_WR_Msg_Communication,             DT_E23},
    {C_EvenHar_AddData_B0,          (ulong32)(E2Addr_Even_Harmonic_AddData_B0), 0,      CL_EvenHar_AddData_B0,          C_WR_Msg_Communication,             DT_E23},
    {C_EvenHar_AddData_B1,          (ulong32)(E2Addr_Even_Harmonic_AddData_B1), 0,      CL_EvenHar_AddData_B1,          C_WR_Msg_Communication,             DT_E23},
    {C_EvenHar_AddData_C0,          (ulong32)(E2Addr_Even_Harmonic_AddData_C0), 0,      CL_EvenHar_AddData_C0,          C_WR_Msg_Communication,             DT_E23},
    {C_EvenHar_AddData_C1,          (ulong32)(E2Addr_Even_Harmonic_AddData_C1), 0,      CL_EvenHar_AddData_C1,          C_WR_Msg_Communication,             DT_E23},
    {C_EvenHar_Time,                (ulong32)(E2Addr_Even_Harmonic_Time),       0,      CL_EvenHar_Time,                C_WR_Msg_Communication,             DT_E21},
    {CBackTime_OneSec,              (ulong32)(FRAMAddr_BackTime_OneSec),        0,      CLBackTime_OneSec,              C_WR_Msg_Comm_Dis,                  DT_FRAM1CRC},
    {CDisplayBorrowPoint,           (ulong32)(&GV_DisplayBorrowPoint[0]),       0,      CLDisplayBorrowPoint,           C_WR_Msg_Display,                   DT_RAMCRC},
    {CDisplayBorrowPoint_RecFlag,   (ulong32)(&GV_DisplayBorrowPoint_RecFlag[0]),0,     CLDisplayBorrowPoint_RecFlag,   C_WR_Msg_Display,                   DT_RAMCRC},
    /*事件类*/
    {CLossA_Vol_Degree,             (ulong32)(E2Addr_LossA_Vol_Degree),         0,      CLLossA_Vol_Degree,             C_Only_Read,                        DT_E23_Hex},
    {CLossB_Vol_Degree,             (ulong32)(E2Addr_LossB_Vol_Degree),         0,      CLLossB_Vol_Degree,             C_Only_Read,                        DT_E23_Hex},
    {CLossC_Vol_Degree,             (ulong32)(E2Addr_LossC_Vol_Degree),         0,      CLLossC_Vol_Degree,             C_Only_Read,                        DT_E23_Hex},
    {CLossA_Vol_Time,               (ulong32)(E2Addr_LossA_Vol_Time),           0,      CLLossA_Vol_Time,               C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CLossB_Vol_Time,               (ulong32)(E2Addr_LossB_Vol_Time),           0,      CLLossB_Vol_Time,               C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CLossC_Vol_Time,               (ulong32)(E2Addr_LossC_Vol_Time),           0,      CLLossC_Vol_Time,               C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CLowA_Vol_Degree,              (ulong32)(E2Addr_LowA_Vol_Degree),          0,      CLLowA_Vol_Degree,              C_Only_Read,                        DT_E23_Hex},
    {CLowB_Vol_Degree,              (ulong32)(E2Addr_LowB_Vol_Degree),          0,      CLLowB_Vol_Degree,              C_Only_Read,                        DT_E23_Hex},
    {CLowC_Vol_Degree,              (ulong32)(E2Addr_LowC_Vol_Degree),          0,      CLLowC_Vol_Degree,              C_Only_Read,                        DT_E23_Hex},
    {CLowA_Vol_Time,                (ulong32)(E2Addr_LowA_Vol_Time),            0,      CLLowA_Vol_Time,                C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CLowB_Vol_Time,                (ulong32)(E2Addr_LowB_Vol_Time),            0,      CLLowB_Vol_Time,                C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CLowC_Vol_Time,                (ulong32)(E2Addr_LowC_Vol_Time),            0,      CLLowC_Vol_Time,                C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {COverA_Vol_Degree,             (ulong32)(E2Addr_OverA_Vol_Degree),         0,      CLOverA_Vol_Degree,             C_Only_Read,                        DT_E23_Hex},
    {COverB_Vol_Degree,             (ulong32)(E2Addr_OverB_Vol_Degree),         0,      CLOverB_Vol_Degree,             C_Only_Read,                        DT_E23_Hex},
    {COverC_Vol_Degree,             (ulong32)(E2Addr_OverC_Vol_Degree),         0,      CLOverC_Vol_Degree,             C_Only_Read,                        DT_E23_Hex},
    {COverA_Vol_Time,               (ulong32)(E2Addr_OverA_Vol_Time),           0,      CLOverA_Vol_Time,               C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {COverB_Vol_Time,               (ulong32)(E2Addr_OverB_Vol_Time),           0,      CLOverB_Vol_Time,               C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {COverC_Vol_Time,               (ulong32)(E2Addr_OverC_Vol_Time),           0,      CLOverC_Vol_Time,               C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CBreakA_Vol_Degree,            (ulong32)(E2Addr_BreakA_Vol_Degree),        0,      CLBreakA_Vol_Degree,            C_Only_Read,                        DT_E23_Hex},
    {CBreakB_Vol_Degree,            (ulong32)(E2Addr_BreakB_Vol_Degree),        0,      CLBreakB_Vol_Degree,            C_Only_Read,                        DT_E23_Hex},
    {CBreakC_Vol_Degree,            (ulong32)(E2Addr_BreakC_Vol_Degree),        0,      CLBreakC_Vol_Degree,            C_Only_Read,                        DT_E23_Hex},
    {CBreakA_Vol_Time,              (ulong32)(E2Addr_BreakA_Vol_Time),          0,      CLBreakA_Vol_Time,              C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CBreakB_Vol_Time,              (ulong32)(E2Addr_BreakB_Vol_Time),          0,      CLBreakB_Vol_Time,              C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CBreakC_Vol_Time,              (ulong32)(E2Addr_BreakC_Vol_Time),          0,      CLBreakC_Vol_Time,              C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CLossA_Curr_Degree,            (ulong32)(E2Addr_LossA_Curr_Degree),        0,      CLLossA_Curr_Degree,            C_Only_Read,                        DT_E23_Hex},
    {CLossB_Curr_Degree,            (ulong32)(E2Addr_LossB_Curr_Degree),        0,      CLLossB_Curr_Degree,            C_Only_Read,                        DT_E23_Hex},
    {CLossC_Curr_Degree,            (ulong32)(E2Addr_LossC_Curr_Degree),        0,      CLLossC_Curr_Degree,            C_Only_Read,                        DT_E23_Hex},
    {CLossA_Curr_Time,              (ulong32)(E2Addr_LossA_Curr_Time),          0,      CLLossA_Curr_Time,              C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CLossB_Curr_Time,              (ulong32)(E2Addr_LossB_Curr_Time),          0,      CLLossB_Curr_Time,              C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CLossC_Curr_Time,              (ulong32)(E2Addr_LossC_Curr_Time),          0,      CLLossC_Curr_Time,              C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {COverA_Curr_Degree,            (ulong32)(E2Addr_OverA_Curr_Degree),        0,      CLOverA_Curr_Degree,            C_Only_Read,                        DT_E23_Hex},
    {COverB_Curr_Degree,            (ulong32)(E2Addr_OverB_Curr_Degree),        0,      CLOverB_Curr_Degree,            C_Only_Read,                        DT_E23_Hex},
    {COverC_Curr_Degree,            (ulong32)(E2Addr_OverC_Curr_Degree),        0,      CLOverC_Curr_Degree,            C_Only_Read,                        DT_E23_Hex},
    {COverA_Curr_Time,              (ulong32)(E2Addr_OverA_Curr_Time),          0,      CLOverA_Curr_Time,              C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {COverB_Curr_Time,              (ulong32)(E2Addr_OverB_Curr_Time),          0,      CLOverB_Curr_Time,              C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {COverC_Curr_Time,              (ulong32)(E2Addr_OverC_Curr_Time),          0,      CLOverC_Curr_Time,              C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CBreakA_Curr_Degree,           (ulong32)(E2Addr_BreakA_Curr_Degree),       0,      CLBreakA_Curr_Degree,           C_Only_Read,                        DT_E23_Hex},
    {CBreakB_Curr_Degree,           (ulong32)(E2Addr_BreakB_Curr_Degree),       0,      CLBreakB_Curr_Degree,           C_Only_Read,                        DT_E23_Hex},
    {CBreakC_Curr_Degree,           (ulong32)(E2Addr_BreakC_Curr_Degree),       0,      CLBreakC_Curr_Degree,           C_Only_Read,                        DT_E23_Hex},
    {CBreakA_Curr_Time,             (ulong32)(E2Addr_BreakA_Curr_Time),         0,      CLBreakA_Curr_Time,             C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CBreakB_Curr_Time,             (ulong32)(E2Addr_BreakB_Curr_Time),         0,      CLBreakB_Curr_Time,             C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CBreakC_Curr_Time,             (ulong32)(E2Addr_BreakC_Curr_Time),         0,      CLBreakC_Curr_Time,             C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CPowerT_Rev_Degree,            (ulong32)(E2Addr_PowerT_Rev_Degree),        0,      CLPowerT_Rev_Degree,            C_Only_Read,                        DT_E23_Hex},
    {CPowerA_Rev_Degree,            (ulong32)(E2Addr_PowerA_Rev_Degree),        0,      CLPowerA_Rev_Degree,            C_Only_Read,                        DT_E23_Hex},
    {CPowerB_Rev_Degree,            (ulong32)(E2Addr_PowerB_Rev_Degree),        0,      CLPowerB_Rev_Degree,            C_Only_Read,                        DT_E23_Hex},
    {CPowerC_Rev_Degree,            (ulong32)(E2Addr_PowerC_Rev_Degree),        0,      CLPowerC_Rev_Degree,            C_Only_Read,                        DT_E23_Hex},
    {CPowerT_Rev_Time,              (ulong32)(E2Addr_PowerT_Rev_Time),          0,      CLPowerT_Rev_Time,              C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CPowerA_Rev_Time,              (ulong32)(E2Addr_PowerA_Rev_Time),          0,      CLPowerA_Rev_Time,              C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CPowerB_Rev_Time,              (ulong32)(E2Addr_PowerB_Rev_Time),          0,      CLPowerB_Rev_Time,              C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CPowerC_Rev_Time,              (ulong32)(E2Addr_PowerC_Rev_Time),          0,      CLPowerC_Rev_Time,              C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {COverA_Lo_Degree,              (ulong32)(E2Addr_OverA_Lo_Degree),          0,      CLOverA_Lo_Degree,              C_Only_Read,                        DT_E23_Hex},
    {COverB_Lo_Degree,              (ulong32)(E2Addr_OverB_Lo_Degree),          0,      CLOverB_Lo_Degree,              C_Only_Read,                        DT_E23_Hex},
    {COverC_Lo_Degree,              (ulong32)(E2Addr_OverC_Lo_Degree),          0,      CLOverC_Lo_Degree,              C_Only_Read,                        DT_E23_Hex},
    {COverA_Lo_Time,                (ulong32)(E2Addr_OverA_Lo_Time),            0,      CLOverA_Lo_Time,                C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {COverB_Lo_Time,                (ulong32)(E2Addr_OverB_Lo_Time),            0,      CLOverB_Lo_Time,                C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {COverC_Lo_Time,                (ulong32)(E2Addr_OverC_Lo_Time),            0,      CLOverC_Lo_Time,                C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CPos_Ac_De_Over_Degree,        (ulong32)(E2Addr_Pos_Ac_De_Over_Degree),    0,      CLPos_Ac_De_Over_Degree,        C_Only_Read,                        DT_E23_Hex},
    {CPos_Ac_De_Over_Time,          (ulong32)(E2Addr_Pos_Ac_De_Over_Time),      0,      CLPos_Ac_De_Over_Time,          C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CRev_Ac_De_Over_Degree,        (ulong32)(E2Addr_Rev_Ac_De_Over_Degree),    0,      CLRev_Ac_De_Over_Degree,        C_Only_Read,                        DT_E23_Hex},
    {CRev_Ac_De_Over_Time,          (ulong32)(E2Addr_Rev_Ac_De_Over_Time),      0,      CLRev_Ac_De_Over_Time,          C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CQua1_Re_De_Over_Degree,       (ulong32)(E2Addr_Qua1_Re_De_Over_Degree),   0,      CLQua1_Re_De_Over_Degree,       C_Only_Read,                        DT_E23_Hex},
    {CQua2_Re_De_Over_Degree,       (ulong32)(E2Addr_Qua2_Re_De_Over_Degree),   0,      CLQua2_Re_De_Over_Degree,       C_Only_Read,                        DT_E23_Hex},
    {CQua3_Re_De_Over_Degree,       (ulong32)(E2Addr_Qua3_Re_De_Over_Degree),   0,      CLQua3_Re_De_Over_Degree,       C_Only_Read,                        DT_E23_Hex},
    {CQua4_Re_De_Over_Degree,       (ulong32)(E2Addr_Qua4_Re_De_Over_Degree),   0,      CLQua4_Re_De_Over_Degree,       C_Only_Read,                        DT_E23_Hex},
    {CQua1_Re_De_Over_Time,         (ulong32)(E2Addr_Qua1_Re_De_Over_Time),     0,      CLQua1_Re_De_Over_Time,         C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CQua2_Re_De_Over_Time,         (ulong32)(E2Addr_Qua2_Re_De_Over_Time),     0,      CLQua2_Re_De_Over_Time,         C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CQua3_Re_De_Over_Time,         (ulong32)(E2Addr_Qua3_Re_De_Over_Time),     0,      CLQua3_Re_De_Over_Time,         C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CQua4_Re_De_Over_Time,         (ulong32)(E2Addr_Qua4_Re_De_Over_Time),     0,      CLQua4_Re_De_Over_Time,         C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CAll_Loss_Vol_Degree,          (ulong32)(E2Addr_All_Loss_Vol_Degree),      0,      CLAll_Loss_Vol_Degree,          C_Only_Read,                        DT_E23_Hex},
    {CAll_Loss_Vol_Time,            (ulong32)(E2Addr_All_Loss_Vol_Time),        0,      CLAll_Loss_Vol_Time,            C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CAux_Pow_Down_Degree,          (ulong32)(E2Addr_Aux_Pow_Down_Degree),      0,      CLAux_Pow_Down_Degree,          C_Only_Read,                        DT_E23_Hex},
    {CAux_Pow_Down_Time,            (ulong32)(E2Addr_Aux_Pow_Down_Time),        0,      CLAux_Pow_Down_Time,            C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CRevPS_Vol_Degree,             (ulong32)(E2Addr_RevPS_Vol_Degree),         0,      CLRevPS_Vol_Degree,             C_Only_Read,                        DT_E23_Hex},
    {CRevPS_Vol_Time,               (ulong32)(E2Addr_RevPS_Vol_Time),           0,      CLRevPS_Vol_Time,               C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CRevPS_Curr_Degree,            (ulong32)(E2Addr_RevPS_Curr_Degree),        0,      CLRevPS_Curr_Degree,            C_Only_Read,                        DT_E23_Hex},
    {CRevPS_Curr_Time,              (ulong32)(E2Addr_RevPS_Curr_Time),          0,      CLRevPS_Curr_Time,              C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CPow_Down_Degree,              (ulong32)(E2Addr_Pow_Down_Degree),          0,      CLPow_Down_Degree,              C_Only_Read,                        DT_E23_Hex},
    {CPow_Down_Time,                (ulong32)(E2Addr_Pow_Down_Time),            0,      CLPow_Down_Time,                C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CProgram_Degree,               (ulong32)(E2Addr_Program_Degree),           0,      CLProgram_Degree,               C_Only_Read,                        DT_E23_Hex},
    {CTol_Clear_Degree,             (ulong32)(E2Addr_Tol_Clear_Degree),         0,      CLTol_Clear_Degree,             C_Only_Read,                        DT_E23_Hex},
    {CDe_Clear_Degree,              (ulong32)(E2Addr_De_Clear_Degree),          0,      CLDe_Clear_Degree,              C_Only_Read,                        DT_E23_Hex},
    {CEven_Clear_Degree,            (ulong32)(E2Addr_Even_Clear_Degree),        0,      CLEven_Clear_Degree,            C_Only_Read,                        DT_E23_Hex},
    {CAdjTime_Degree,               (ulong32)(E2Addr_AdjTime_Degree),           0,      CLAdjTime_Degree,               C_Only_Read,                        DT_E23_Hex},
    {CProgPT_Degree,                (ulong32)(E2Addr_ProgPT_Degree),            0,      CLProgPT_Degree,                C_Only_Read,                        DT_E23_Hex},
    {CProgTZ_Degree,                (ulong32)(E2Addr_ProgTZ_Degree),            0,      CLProgTZ_Degree,                C_Only_Read,                        DT_E23_Hex},
    {CProgWRe_Degree,               (ulong32)(E2Addr_ProgWRe_Degree),           0,      CLProgWRe_Degree,               C_Only_Read,                        DT_E23_Hex},
    {CProgSettD_Degree,             (ulong32)(E2Addr_ProgSettD_Degree),         0,      CLProgSettD_Degree,             C_Only_Read,                        DT_E23_Hex},
    {COpenW_Degree,                 (ulong32)(E2Addr_OpenW_Degree),             0,      CLOpenW_Degree,                 C_Only_Read,                        DT_E23_Hex},
    {COpenW_Time,                   (ulong32)(E2Addr_OpenW_Time),               0,      CLOpenW_Time,                   C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {COpenCW_Degree,                (ulong32)(E2Addr_OpenCW_Degree),            0,      CLOpenCW_Degree,                C_Only_Read,                        DT_E23_Hex},
    {COpenCW_Time,                  (ulong32)(E2Addr_OpenCW_Time),              0,      CLOpenCW_Time,                  C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CNoBal_Vol_Degree,             (ulong32)(E2Addr_NoBal_Vol_Degree),         0,      CLNoBal_Vol_Degree,             C_Only_Read,                        DT_E23_Hex},
    {CNoBal_Vol_Time,               (ulong32)(E2Addr_NoBal_Vol_Time),           0,      CLNoBal_Vol_Time,               C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CNoBal_Curr_Degree,            (ulong32)(E2Addr_NoBal_Curr_Degree),        0,      CLNoBal_Curr_Degree,            C_Only_Read,                        DT_E23_Hex},
    {CNoBal_Curr_Time,              (ulong32)(E2Addr_NoBal_Curr_Time),          0,      CLNoBal_Curr_Time,              C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CRelayOpen_Degree,             (ulong32)(E2Addr_RelayOpen_Degree),         0,      CLRelayOpen_Degree,             C_Only_Read,                        DT_E23_Hex},
    {CRelayClose_Degree,            (ulong32)(E2Addr_RelayClose_Degree),        0,      CLRelayClose_Degree,            C_Only_Read,                        DT_E23_Hex},
    {CProgHol_Degree,               (ulong32)(E2Addr_ProgHol_Degree),           0,      CLProgHol_Degree,               C_Only_Read,                        DT_E23_Hex},
    {CProgAcC_Degree,               (ulong32)(E2Addr_ProgAcC_Degree),           0,      CLProgAcC_Degree,               C_Only_Read,                        DT_E23_Hex},
    {CProgReC_Degree,               (ulong32)(E2Addr_ProgReC1_Degree),          0,      CLProgReC_Degree,               C_Only_Read,                        DT_E23_Hex},
    {CProgTPara_Degree,             (ulong32)(E2Addr_ProgTPara_Degree),         0,      CLProgTPara_Degree,             C_Only_Read,                        DT_E23_Hex},
    {CProgLad_Degree,               (ulong32)(E2Addr_ProgLad_Degree),           0,      CLProgLad_Degree,               C_Only_Read,                        DT_E23_Hex},
    {CProgKD_Degree,                (ulong32)(E2Addr_ProgKD_Degree),            0,      CLProgKD_Degree,                C_Only_Read,                        DT_E23_Hex},
    {CAbnorC_Degree,                (ulong32)(E2Addr_AbnorC_Degree),            0,      CLAbnorC_Degree,                C_Only_Read,                        DT_E23_Hex},
    {CBuyCurr_Degree,               (ulong32)(E2Addr_BuyCurr_Degree),           0,      CLBuyCurr_Degree,               C_Only_Read,                        DT_E23_Hex},
    {CReturn_M_Degree,              (ulong32)(E2Addr_Return_M_Degree),          0,      CLReturn_M_Degree,              C_Only_Read,                        DT_E23_Hex},
    {CConM_Degree,                  (ulong32)(E2Addr_ConM_Degree),              0,      CLConM_Degree,                  C_Only_Read,                        DT_E23_Hex},
    {CConM_Time,                    (ulong32)(E2Addr_ConM_Time),                0,      CLConM_Time,                    C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CRelayFa_Degree,               (ulong32)(E2Addr_RelayFa_Degree),           0,      CLRelayFa_Degree,               C_Only_Read,                        DT_E23_Hex},
    {CRelayFa_Time,                 (ulong32)(E2Addr_RelayFa_Time),             0,      CLRelayFa_Time,                 C_WR_Msg_Deal_RelayStatus,          DT_E23},
    {CPowerFa_Degree,               (ulong32)(E2Addr_PowerFa_Degree),           0,      CLPowerFa_Degree,               C_Only_Read,                        DT_E23_Hex},
    {CPowerFa_Time,                 (ulong32)(E2Addr_PowerFa_Time),             0,      CLPowerFa_Time,                 C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CSevNoBal_Curr_Degree,         (ulong32)(E2Addr_SevNoBal_Curr_Degree),     0,      CLSevNoBal_Curr_Degree,         C_Only_Read,                        DT_E23_Hex},
    {CSevNoBal_Curr_Time,           (ulong32)(E2Addr_SevNoBal_Curr_Time),       0,      CLSevNoBal_Curr_Time,           C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CClockFa_Degree,               (ulong32)(E2Addr_ClockFa_Degree),           0,      CLClockFa_Degree,               C_Only_Read,                        DT_E23_Hex},
    {CClockFa_Time,                 (ulong32)(E2Addr_ClockFa_Time),             0,      CLClockFa_Time,                 C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CMeterFa_Degree,               (ulong32)(E2Addr_MeterFa_Degree),           0,      CLMeterFa_Degree,               C_Only_Read,                        DT_E23_Hex},
    {CMeterFa_Time,                 (ulong32)(E2Addr_MeterFa_Time),             0,      CLMeterFa_Time,                 C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CPFactorT_Over_Degree,         (ulong32)(E2Addr_PFactorT_Over_Degree),     0,      CLPFactorT_Over_Degree,         C_Only_Read,                        DT_E23_Hex},
    {CPFactorA_Over_Degree,         (ulong32)(E2Addr_PFactorA_Over_Degree),     0,      CLPFactorA_Over_Degree,         C_Only_Read,                        DT_E23_Hex},
    {CPFactorB_Over_Degree,         (ulong32)(E2Addr_PFactorB_Over_Degree),     0,      CLPFactorB_Over_Degree,         C_Only_Read,                        DT_E23_Hex},
    {CPFactorC_Over_Degree,         (ulong32)(E2Addr_PFactorC_Over_Degree),     0,      CLPFactorC_Over_Degree,         C_Only_Read,                        DT_E23_Hex},
    {CPFactorT_Over_Time,           (ulong32)(E2Addr_PFactorT_Over_Time),       0,      CLPFactorT_Over_Time,           C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CPFactorA_Over_Time,           (ulong32)(E2Addr_PFactorA_Over_Time),       0,      CLPFactorA_Over_Time,           C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CPFactorB_Over_Time,           (ulong32)(E2Addr_PFactorB_Over_Time),       0,      CLPFactorB_Over_Time,           C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CPFactorC_Over_Time,           (ulong32)(E2Addr_PFactorC_Over_Time),       0,      CLPFactorC_Over_Time,           C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CBroadcastTime_Degree,         (ulong32)(E2Addr_BroadcastTime_Degree),     0,      CLBroadcastTime_Degree,         C_Only_Read,                        DT_E23_Hex},
    {CNeutralCurrentAbnormal_Degree,(ulong32)(E2Addr_NeutralCurrentAbnormal_Degree),0,CLNeutralCurrentAbnormal_Degree,  C_Only_Read,                        DT_E23_Hex},
    {CNeutralCurrentAbnormal_Time,  (ulong32)(E2Addr_NeutralCurrentAbnormal_Time),0,    CLNeutralCurrentAbnormal_Time,  C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CSoft_I_J_Prog_1,              (ulong32)(E2Addr_Soft_I_J_Prog_1),          0,      CLSoft_I_J_Prog_1,              C_WR_Msg_Communication,             DT_E23},
    {CSoft_I_J_Prog_2,              (ulong32)(E2Addr_Soft_I_J_Prog_2),          0,      CLSoft_I_J_Prog_2,              C_WR_Msg_Communication,             DT_E23},
    {CRec_Meter_Degree,             (ulong32)(E2Addr_Rec_Meter_Degree),         0,      CLRec_Meter_Degree,             C_Only_Read,                        DT_E23_Hex},
    {CRec_Meter_Hp_T_1,             (ulong32)(&Str_3cTable_Flash[0]),           0,      CLRec_Meter_Hp_T_1,             C_WR_Msg_Communication,             DT_Flash_Tol_DI0_DI1},
    {CRec_Meter_Bef1_Data_254,      (ulong32)(&Str_3cTable_Flash[0]),           0,      CLRec_Meter_Bef1_Data_254,      C_WR_Msg_Communication,             DT_Flash_Tol_DI0_DI1Max},
    {CProgPT_CurrentPart_Degree,    (ulong32)(E2Addr_ProgPT_CurrentPart_Degree),0,      CLProgPT_CurrentPart_Degree,    C_Only_Read,                        DT_E23_Hex},
    {CProgPT_NoteC_1,               (ulong32)(&Str_3cTable_Flash[0]),           1,      CLProgPT_NoteC_1,               C_WR_Msg_Communication,             DT_Flash_DI04},
    {CProgPT_NoteD_1,               (ulong32)(&Str_3cTable_Flash[0]),           1,      CLProgPT_NoteD_1,               C_WR_Msg_Communication,             DT_Flash_DI04},
    {CProgPT_NoteE_1,               (ulong32)(&Str_3cTable_Flash[0]),           1,      CLProgPT_NoteE_1,               C_WR_Msg_Communication,             DT_Flash_DI04},
    {CProgPT_NoteF_1,               (ulong32)(&Str_3cTable_Flash[0]),           1,      CLProgPT_NoteF_1,               C_WR_Msg_Communication,             DT_Flash_DI04},
    {CProgTZ_CurrentPart_Degree,    (ulong32)(E2Addr_ProgTZ_CurrentPart_Degree),0,      CLProgTZ_CurrentPart_Degree,    C_Only_Read,                        DT_E23_Hex},
    {CProgTZ_CurrentPart_Note_1,    (ulong32)(&Str_3cTable_Flash[0]),           2,      CLProgTZ_CurrentPart_Note_1,    C_WR_Msg_Communication,             DT_Flash_DI04},
    {CProgram_Degree_645_2,         (ulong32)(E2Addr_Program_Degree_645),       0,      CLProgram_Degree_645,           C_Only_Read,                        DT_E23_Hex},
    {CProgram_Note_1_645,           (ulong32)(&Str_3cTable_Flash[0]),           3,      CLProgram_Note_1_645,           C_WR_Msg_Comm_Card,                 DT_Flash_Tol_DI0},
};
#define Str_2Table_DIParameterFF_Len  (sizeof(Str_2Table_DIParameterFF)/sizeof(Str_2Table))

const Str_1Table Str_1Table_DI3[]=
{/* 2级表格结构体数组地址                      对应2级表结构体数据长度                  V_DI3*/
	{(ulong32)(Str_2Table_DIEn),                 Str_2Table_DIEn_Len,                     0x00},            /***电能量类*/
	{(ulong32)(Str_2Table_DIDe10),               Str_2Table_DIDe10_Len,                   0x10},            /***最大需量类****/
	{(ulong32)(Str_2Table_DIEvent20),            Str_2Table_DIEvent20_Len,                0x20},            /***变量类DI3=20*****/
	{(ulong32)(Str_2Table_DIEvent21),            Str_2Table_DIEvent21_Len,                0x21},            /***变量类DI3=21*****/
	{(ulong32)(Str_2Table_DIEvent30),            Str_2Table_DIEvent30_Len,                0x30},            /***事件类DI3=03*****/
	{(ulong32)(Str_2Table_DIReport),             Str_2Table_DIReport_Len,                 0x33},             /***上报类*****/
	{(ulong32)(Str_2Table_DIParamChild40),       Str_2Table_DIParamChild40_Len,           0x40},            /***参变量类698 40*****/
	{(ulong32)(Str_2Table_DIParamChild41),       Str_2Table_DIParamChild41_Len,           0x41},            /***参变量类698 41*****/
	{(ulong32)(Str_2Table_DIParamChild43),       Str_2Table_DIParamChild43_Len,           0x43},            /***参变量类698 43*****/
	{(ulong32)(Str_2Table_DIParamChild44),       Str_2Table_DIParamChild44_Len,           0x44},            /***参变量类698 44*****/
	{(ulong32)(Str_2Table_DIParamChild45),       Str_2Table_DIParamChild45_Len,           0x45},            /***参变量类698 45*****/
	{(ulong32)(Str_2Table_DIParamChild80),       Str_2Table_DIParamChild80_Len,           0x80},            /***参变量类698 80*****/
	{(ulong32)(Str_2Table_DIParameterF1),        Str_2Table_DIParameterF1_Len,            0xF1},            /***参变量类698 F1*****/
	{(ulong32)(Str_2Table_DIParamChildF2),       Str_2Table_DIParamChildF2_Len,           0xF2},            /***参变量类698 F2*****/
	{(ulong32)(Str_2Table_DIParamChildF3),       Str_2Table_DIParamChildF3_Len,           0xF3},            /***参变量类698 F3*****/
	{(ulong32)(Str_2Table_DIParamChild),         Str_2Table_DIParamChild_Len,             0x04},            /***参变量类645 04*****/
	{(ulong32)(Str_2Table_DIParameterFF),        Str_2Table_DIParameterFF_Len,            0xFF}             /*33自扩参变量类698 FF*/
};
#define Str_1Table_DI3_Len  (sizeof(Str_1Table_DI3)/sizeof(Str_1Table))

/********************************************事件记录E2表格*******************************************/
#define EventDI    0x000000FF

const Str_EvenTable  Str_EvenTableE2[]=               /*不包含电表清零记录及事件清零记录(后698增加用于，修改关联列表时清相关记录)，类似DI1有分项标识码事件，分项事件清零时该标识码为FF，即块操作*/
{/*ulong32 V_DI                          数据标识对应E2起始地址 数据标识对应E2结束地址 事件上报表格对应E2起始地址		事件上报表格对应E2结束地址	 				数据标示对应EventNum号，学云宏定义*/
	{(CAll_Loss_Vol|EventDI),              E2Addr_All_Loss_Vol_Degree,        E2Addr_Aux_Pow_Down_Degree,     /*E2Addr_AllLossVolage_Report_Record_1,E2Addr_AuxPowDown_Report_Record_1, 		*/C_TotalVoltageLoseEventNo		},
	{(CAux_Pow_Down|EventDI),              E2Addr_Aux_Pow_Down_Degree,        E2Addr_Pow_Down_Degree    ,     /*E2Addr_AuxPowDown_Report_Record_1,		E2Addr_RevVol_Report_Record_1,		 		*/C_ACPowerFailEventNo			  },
	{(CPow_Down_Degree|EventDI),           E2Addr_Pow_Down_Degree,            E2Addr_Pos_Ac_De_Over_Degree,   /*E2Addr_PowerOff_Report_Record_1,			E2Addr_Program_Report_Record_1,				*/C_PowerfailEventNo				  },
	{(CPos_Ac_De_Over_Note_1|EventDI),     E2Addr_Pos_Ac_De_Over_Degree,      E2Addr_Rev_Ac_De_Over_Degree,   /*E2Addr_AcDemandOv_Report_Record_1,		E2Addr_PosDemandOv_Report_Record_1, 	*/C_OverForwardActiveEventNo  },
	{(CRev_Ac_De_Over_Note_1|EventDI),     E2Addr_Rev_Ac_De_Over_Degree,      E2Addr_Qua1_Re_De_Over_Degree,  /*E2Addr_PosDemandOv_Report_Record_1,	E2Addr_1ReDemandOv_Report_Record_1, 	*/C_OverReverseActiveEventNo  },
	{(CQua1_Re_De_Over_Note_1|EventDI),    E2Addr_Qua1_Re_De_Over_Degree,     E2Addr_Qua2_Re_De_Over_Degree,  /*E2Addr_1ReDemandOv_Report_Record_1,	E2Addr_2ReDemandOv_Report_Record_1, 	*/C_1OverIdleDemandEventNo	  },
	{(CQua2_Re_De_Over_Note_1|EventDI),    E2Addr_Qua2_Re_De_Over_Degree,     E2Addr_Qua3_Re_De_Over_Degree,  /*E2Addr_2ReDemandOv_Report_Record_1,	E2Addr_3ReDemandOv_Report_Record_1, 	*/C_2OverIdleDemandEventNo	  },
	{(CQua3_Re_De_Over_Note_1|EventDI),    E2Addr_Qua3_Re_De_Over_Degree,     E2Addr_Qua4_Re_De_Over_Degree,  /*E2Addr_3ReDemandOv_Report_Record_1,	E2Addr_4ReDemandOv_Report_Record_1, 	*/C_3OverIdleDemandEventNo	  },
	{(CQua4_Re_De_Over_Note_1|EventDI),    E2Addr_Qua4_Re_De_Over_Degree,     E2Addr_LossA_Vol_Degree,        /*E2Addr_4ReDemandOv_Report_Record_1,	E2Addr_PowerFactor_Report_Record_1, 	*/C_4OverIdleDemandEventNo	  },
	{(CLossAVol_FF_1|EventDI),             E2Addr_LossA_Vol_Degree,           E2Addr_LossB_Vol_Degree    ,    /*E2Addr_ALossVolage_Report_Record_1,	E2Addr_BLossVolage_Report_Record_1, 	*/C_AlossvoltageEventNo			  },
	{(CLossBVol_FF_1|EventDI),             E2Addr_LossB_Vol_Degree,           E2Addr_LossC_Vol_Degree,        /*E2Addr_BLossVolage_Report_Record_1,	E2Addr_CLossVolage_Report_Record_1, 	*/C_BlossvoltageEventNo			  },
	{(CLossCVol_FF_1|EventDI),             E2Addr_LossC_Vol_Degree,           E2Addr_LowA_Vol_Degree    ,     /*E2Addr_CLossVolage_Report_Record_1,	E2Addr_ALowVolage_Report_Record_1,		*/C_ClossvoltageEventNo			  },
	{(CLowAVol_FF_1|EventDI),              E2Addr_LowA_Vol_Degree,            E2Addr_LowB_Vol_Degree,         /*E2Addr_ALowVolage_Report_Record_1,		E2Addr_BLowVolage_Report_Record_1,		*/C_ALessvoltageEventNo			  },
	{(CLowBVol_FF_1|EventDI),              E2Addr_LowB_Vol_Degree,            E2Addr_LowC_Vol_Degree    ,     /*E2Addr_BLowVolage_Report_Record_1,		E2Addr_CLowVolage_Report_Record_1, 		*/C_BLessvoltageEventNo			  },
	{(CLowCVol_FF_1|EventDI),              E2Addr_LowC_Vol_Degree,            E2Addr_OverA_Vol_Degree,        /*E2Addr_CLowVolage_Report_Record_1,		E2Addr_AOverVolage_Report_Record_1, 	*/C_CLessvoltageEventNo			  },
	{(COverAVol_FF_1|EventDI),             E2Addr_OverA_Vol_Degree,           E2Addr_OverB_Vol_Degree   ,     /*E2Addr_AOverVolage_Report_Record_1,	E2Addr_BOverVolage_Report_Record_1, 	*/C_AOvervoltageEventNo			  },
	{(COverBVol_FF_1|EventDI),             E2Addr_OverB_Vol_Degree,           E2Addr_OverC_Vol_Degree,        /*E2Addr_BOverVolage_Report_Record_1,	E2Addr_COverVolage_Report_Record_1, 	*/C_BOvervoltageEventNo			  },
	{(COverCVol_FF_1|EventDI),             E2Addr_OverC_Vol_Degree,           E2Addr_BreakA_Vol_Degree    ,   /*E2Addr_COverVolage_Report_Record_1,	E2Addr_ABreakVolage_Report_Record_1,	*/C_COvervoltageEventNo			  },
	{(CBreakAVol_FF_1|EventDI),            E2Addr_BreakA_Vol_Degree,          E2Addr_BreakB_Vol_Degree,       /*E2Addr_ABreakVolage_Report_Record_1,	E2Addr_BBreakVolage_Report_Record_1,	*/C_ALossphaseEventNo				  },
	{(CBreakBVol_FF_1|EventDI),            E2Addr_BreakB_Vol_Degree,          E2Addr_BreakC_Vol_Degree    ,   /*E2Addr_BBreakVolage_Report_Record_1,	E2Addr_CBreakVolage_Report_Record_1,	*/C_BLossphaseEventNo				  },
	{(CBreakCVol_FF_1|EventDI),            E2Addr_BreakC_Vol_Degree,          E2Addr_RevPS_Vol_Degree,        /*E2Addr_CBreakVolage_Report_Record_1,	E2Addr_ALossCurr_Report_Record_1,			*/C_CLossphaseEventNo				  },
	{(CRevPSVol_FF_1|EventDI),             E2Addr_RevPS_Vol_Degree,           E2Addr_RevPS_Curr_Degree    ,   /*E2Addr_RevVol_Report_Record_1,				E2Addr_RevCurr_Report_Record_1,				*/C_ReversephaseVoltageEventNo},
	{(CRevPSCurr_FF_1|EventDI),            E2Addr_RevPS_Curr_Degree,          E2Addr_NoBal_Vol_Degree,        /*E2Addr_RevCurr_Report_Record_1,			E2Addr_PowerOff_Report_Record_1,			*/C_ReversephaseCurrentEventNo},
	{(CNoBalVol_FF_1|EventDI),             E2Addr_NoBal_Vol_Degree,           E2Addr_NoBal_Curr_Degree    ,   /*E2Addr_NoBalVol_Report_Record_1,			E2Addr_NoBalCurr_Report_Record_1,			*/C_UnbanlanceVoltageEventNo	},
	{(CNoBalCurr_FF_1|EventDI),            E2Addr_NoBal_Curr_Degree,          E2Addr_SevNoBal_Curr_Degree,    /*E2Addr_NoBalCurr_Report_Record_1,		E2Addr_RelayOpen_Report_Record_1,			*/C_UnbanlanceCurrentEventNo	},
	{(CSevNoBalCurr_FF_1|EventDI),         E2Addr_SevNoBal_Curr_Degree,       E2Addr_LossA_Curr_Degree,       /*E2Addr_SeriNoBalCurr_Report_Record_1,E2Addr_ClockFault_Report_Record_1,		*/C_SUnbanlanceCurrentEventNo	},
	{(CLossACurr_FF_1|EventDI),            E2Addr_LossA_Curr_Degree,          E2Addr_LossB_Curr_Degree    ,   /*E2Addr_ALossCurr_Report_Record_1,		E2Addr_BLossCurr_Report_Record_1,			*/C_ALosscurrentEventNo			  },
	{(CLossBCurr_FF_1|EventDI),            E2Addr_LossB_Curr_Degree,          E2Addr_LossC_Curr_Degree,       /*E2Addr_BLossCurr_Report_Record_1,		E2Addr_CLossCurr_Report_Record_1,			*/C_BLosscurrentEventNo			  },
	{(CLossCCurr_FF_1|EventDI),            E2Addr_LossC_Curr_Degree,          E2Addr_OverA_Curr_Degree    ,   /*E2Addr_CLossCurr_Report_Record_1,		E2Addr_AOverCurr_Report_Record_1,			*/C_CLosscurrentEventNo			  },
	{(COverACurr_FF_1|EventDI),            E2Addr_OverA_Curr_Degree,          E2Addr_OverB_Curr_Degree,       /*E2Addr_AOverCurr_Report_Record_1,		E2Addr_BOverCurr_Report_Record_1,			*/C_AOvercurrentEventNo			  },
	{(COverBCurr_FF_1|EventDI),            E2Addr_OverB_Curr_Degree,          E2Addr_OverC_Curr_Degree    ,   /*E2Addr_BOverCurr_Report_Record_1,		E2Addr_COverCurr_Report_Record_1,			*/C_BOvercurrentEventNo			  },
	{(COverCCurr_FF_1|EventDI),            E2Addr_OverC_Curr_Degree,          E2Addr_BreakA_Curr_Degree,      /*E2Addr_COverCurr_Report_Record_1,		E2Addr_ABreakCurr_Report_Record_1,		*/C_COvercurrentEventNo			  },
	{(CBreakACurr_FF_1|EventDI),           E2Addr_BreakA_Curr_Degree,         E2Addr_BreakB_Curr_Degree    ,  /*E2Addr_ABreakCurr_Report_Record_1,		E2Addr_BBreakCurr_Report_Record_1,		*/C_AFailcurrentEventNo			  },
	{(CBreakBCurr_FF_1|EventDI),           E2Addr_BreakB_Curr_Degree,         E2Addr_BreakC_Curr_Degree,      /*E2Addr_BBreakCurr_Report_Record_1,		E2Addr_CBreakCurr_Report_Record_1,		*/C_BFailcurrentEventNo			  },
	{(CBreakCCurr_FF_1|EventDI),           E2Addr_BreakC_Curr_Degree,         E2Addr_PowerT_Rev_Degree    ,   /*E2Addr_CBreakCurr_Report_Record_1,		E2Addr_TrendRev_Report_Record_1,	 		*/C_CFailcurrentEventNo			  },
	{(CPowerTRev_FF_1|EventDI),            E2Addr_PowerT_Rev_Degree,          E2Addr_PowerA_Rev_Degree,       /*E2Addr_TTrendRev_Report_Record_1,		E2Addr_ATrendRev_Report_Record_1,			*/C_TReversecurrentEventNo	  },
	{(CPowerARev_FF_1|EventDI),            E2Addr_PowerA_Rev_Degree,          E2Addr_PowerB_Rev_Degree,       /*E2Addr_ATrendRev_Report_Record_1,		E2Addr_BTrendRev_Report_Record_1,			*/C_AReversecurrentEventNo	  },
	{(CPowerBRev_FF_1|EventDI),            E2Addr_PowerB_Rev_Degree,          E2Addr_PowerC_Rev_Degree    ,   /*E2Addr_BTrendRev_Report_Record_1,		E2Addr_CTrendRev_Report_Record_1,			*/C_BReversecurrentEventNo	  },
	{(CPowerCRev_FF_1|EventDI),            E2Addr_PowerC_Rev_Degree,          E2Addr_OverA_Lo_Degree,         /*E2Addr_CTrendRev_Report_Record_1,		E2Addr_AOverLoad_Report_Record_1,			*/C_CReversecurrentEventNo	  },
	{(COverALo_FF_1|EventDI),              E2Addr_OverA_Lo_Degree,            E2Addr_OverB_Lo_Degree    ,     /*E2Addr_AOverLoad_Report_Record_1,		E2Addr_BOverLoad_Report_Record_1,		 	*/C_AOverloadEventNo				  },
	{(COverBLo_FF_1|EventDI),              E2Addr_OverB_Lo_Degree,            E2Addr_OverC_Lo_Degree,         /*E2Addr_BOverLoad_Report_Record_1,		E2Addr_COverLoad_Report_Record_1,		 	*/C_BOverloadEventNo				  },
	{(COverCLo_FF_1|EventDI),              E2Addr_OverC_Lo_Degree,            E2Addr_PFactorT_Over_Degree    ,    /*E2Addr_COverLoad_Report_Record_1,		E2Addr_AcDemandOv_Report_Record_1,	 	*/C_COverloadEventNo				  },
	{(CPFactorT_FF_1|EventDI),             E2Addr_PFactorT_Over_Degree,       E2Addr_PFactorA_Over_Degree,         /*E2Addr_PowerFactor_Report_Record_1,	E2Addr_AllLossVolage_Report_Record_1,	*/C_OverpowerfactEventNo		  },
	{(CPFactorA_FF_1|EventDI),             E2Addr_PFactorA_Over_Degree,       E2Addr_PFactorB_Over_Degree,                                                                                         C_AOverpowerfactEventNo		  },
	{(CPFactorB_FF_1|EventDI),             E2Addr_PFactorB_Over_Degree,       E2Addr_PFactorC_Over_Degree,                                                                                         C_BOverpowerfactEventNo		  },
	{(CPFactorC_FF_1|EventDI),             E2Addr_PFactorC_Over_Degree,       E2Addr_NeutralCurrentAbnormal_Degree,                                                                                          C_COverpowerfactEventNo		  },
	{(COpenW_Degree|EventDI),              E2Addr_OpenW_Degree,               E2Addr_OpenCW_Degree    ,       /*E2Addr_OpenW_Report_Record_1,				E2Addr_OpenCW_Report_Record_1,			 	*/C_OpenMeterCoverEventNo		  },
	{(COpenCW_Degree|EventDI),             E2Addr_OpenCW_Degree,              E2Addr_BuyCurr_Degree,          /*E2Addr_OpenCW_Report_Record_1,				E2Addr_NoBalVol_Report_Record_1,		 	*/C_OpenTerminalCoverEventNo  },
	{(CConM_Degree|EventDI),               E2Addr_ConM_Degree,                E2Addr_RelayFa_Degree    ,      /*E2Addr_ConMEndEn_Report_Record_1,		E2Addr_RelayFaEndEn_Report_Record_1, 	*/C_MagneticCheckEventNo		  },
	{(CPowerFa_Degree|EventDI),            E2Addr_PowerFa_Degree,             E2Addr_MeterFa_Degree,          /*E2Addr_PowerFa_EndT_Report_Record_1,	E2Addr_SeriNoBalCurr_Report_Record_1,	*/C_PowerAbnormalEventNo		  },
	{(CMeterFa|EventDI),			       E2Addr_MeterFa_Degree,             E2Addr_ClockFa_Degree  ,  	/*E2Addr_MeterChipFault_Report_Record_1,        CEventUpTellTable_EndE2Addr,*/          C_MeterFaEventNo			},
	{(CClockFa|EventDI),			       E2Addr_ClockFa_Degree,             E2Addr_RelayOpen_Degree,  	/*E2Addr_ClockFault_Report_Record_1,		E2Addr_MeterChipFault_Report_Record_1,*/ C_ClockFaEventNo			},
	{(CDe_Clear_Degree|EventDI),           E2Addr_De_Clear_Degree,            E2Addr_RelayClose_Degree,       /*E2Addr_DemandClear_Report_Record_1,	E2Addr_EventClear_Report_Record_1,	  */C_DemandClearEventNo  },
	{(CProgram_Degree|EventDI),            E2Addr_Program_Degree,             E2Addr_AdjTime_Degree,          /*E2Addr_Program_Report_Record_1,			E2Addr_TolClear_Report_Record_1,		  */C_ProgramEventNo  },
	{(CAdjTime_Degree|EventDI),            E2Addr_AdjTime_Degree,             E2Addr_BroadcastTime_Degree,           /*E2Addr_AdjTime_Report_Record_1,			E2Addr_ProgPT_Report_Record_1,			  */C_AdjTimeEventNo  },
	{(CProgPT_Degree|EventDI),             E2Addr_ProgPT_Degree,              E2Addr_ProgTZ_Degree,           /*E2Addr_ProgPT_Report_Record_1,				E2Addr_ProgPZ_Report_Record_1,			  */C_ProgPTEventNo  },
	{(CProgTZ_Degree|EventDI),             E2Addr_ProgTZ_Degree,              E2Addr_ProgWRe_Degree,          /*E2Addr_ProgPZ_Report_Record_1,				E2Addr_ProgWRe_Report_Record_1,			  */C_ProgPZEventNo  },
	{(CProgWRe_Degree|EventDI),            E2Addr_ProgWRe_Degree,             E2Addr_ProgHol_Degree,        	 /*E2Addr_ProgWRe_Report_Record_1,			E2Addr_ProgSettD_Report_Record_1,		  */C_ProgWReEventNo  },
	{(CProgHol_Degree|EventDI),            E2Addr_ProgHol_Degree,             E2Addr_ProgAcC_Degree,          /*E2Addr_ProgHol_Report_Record_1,			E2Addr_ProgAcC_Report_Record_1,			  */C_ProgHolEventNo  },
	{(CProgAcC_Degree|EventDI),            E2Addr_ProgAcC_Degree,             E2Addr_ProgReC1_Degree,         /*E2Addr_ProgAcC_Report_Record_1,			E2Addr_ProgReC_Report_Record_1,			  */C_ProgAcCEventNo  },
	{(CProgReC_Degree|EventDI),            E2Addr_ProgReC1_Degree,            E2Addr_ProgSettD_Degree,        /*E2Addr_ProgReC_Report_Record_1,			E2Addr_ProgTPara_Report_Record_1,		  */C_ProgReCEventNo  },
	{(CProgSettD_Degree|EventDI),          E2Addr_ProgSettD_Degree,           E2Addr_ProgTPara_Degree,        /*E2Addr_ProgSettD_Report_Record_1,		E2Addr_OpenW_Report_Record_1,				  */C_ProgSettDEventNo	},
	{(CProgTPara_Degree|EventDI),          E2Addr_ProgTPara_Degree,           E2Addr_ProgLad_Degree,          /*E2Addr_ProgTPara_Report_Record_1,		E2Addr_ProgLad_Report_Record_1,			  */C_ProgTParaEventNo	},
	{(CProgLad_Degree|EventDI),            E2Addr_ProgLad_Degree,             E2Addr_ProgKD_Degree,           /*E2Addr_ProgLad_Report_Record_1,			E2Addr_Key_Update_Report_Record_1,	  */C_ProgLadEventNo	},
	{(CProgKD_Degree|EventDI),             E2Addr_ProgKD_Degree,              E2Addr_AbnorC_Degree,           /*E2Addr_Key_Update_Report_Record_1,		E2Addr_AbnorC_Report_Record_1,			  */C_Key_UpdateEventNo	},
	{(CAbnorC_Degree|EventDI),             E2Addr_AbnorC_Degree,              E2Addr_OpenW_Degree,            /*E2Addr_AbnorC_Report_Record_1,				E2Addr_BuyCurr_Report_Record_1,			  */C_AbnorCEventNo	},
	{(CBuyCurr_FF_Note_1|EventDI),         E2Addr_BuyCurr_Degree,             E2Addr_Return_M_Degree,         /*E2Addr_BuyCurr_Report_Record_1,			E2Addr_ReturnMoney_Report_Record_1,	  */C_BuyCurrEventNo},
	{(CReturn_M_Degree|EventDI),           E2Addr_Return_M_Degree,            E2Addr_LawlessC_Degree,         /*E2Addr_ReturnMoney_Report_Record_1,	E2Addr_ConMEndEn_Report_Record_1,		  */C_ReturnMoneyEventNo },
	{(CRelayFa_Degree|EventDI),            E2Addr_RelayFa_Degree,             E2Addr_PowerFa_Degree    ,      /*E2Addr_RelayFaEndEn_Report_Record_1,	E2Addr_PowerFa_EndT_Report_Record_1,  */C_RelayFaEndEnEventNo  },
	{(CRelayOpen_FF_1|EventDI),            E2Addr_RelayOpen_Degree,           E2Addr_Soft_I_J_Prog_Degree,    /*E2Addr_RelayOpen_Report_Record_1,		E2Addr_RelayClose_Report_Record_1,	  */C_RelayOpenEventNo	},
	{(CRelayClose_FF_1|EventDI),           E2Addr_RelayClose_Degree,          E2Addr_Program_Degree,          /*E2Addr_RelayClose_Report_Record_1,		E2Addr_ProgHol_Report_Record_1,			  */C_RelayCloseEventNo	},
	{(CSoft_I_J_Prog_Degree|EventDI),      E2Addr_Soft_I_J_Prog_1,            E2Addr_Rec_MeterSequence,       /*E2_Max_Addr,				E2_Max_Addr,		 				*/C_SoftIJProgEventNo},
	{(CLawlessC_Degree|EventDI),           E2Addr_LawlessC_Degree,            E2Addr_ConM_Degree,             /*E2_Max_Addr,				E2_Max_Addr,		 				*/C_LawlessCardEventNo},  /*非法插卡，总次数。与异常插卡记录单独清零*/
	{(CBroadcastTime_Degree|EventDI), 	   E2Addr_BroadcastTime_Degree,	      E2Addr_ProgPT_Degree,           /*E2Addr_BroadcastTime_Report_Record_1, E2Addr_ProgPT_Report_Record_1,			  */C_BroadcastTimeEventNo  },
	{(CNeutralCurrentAbnormal_Note_1|EventDI), 	E2Addr_NeutralCurrentAbnormal_Degree,	E2Addr_De_Clear_Degree,/*E2Addr_BroadcastTime_Report_Record_1, E2Addr_ProgPT_Report_Record_1,			  */C_NeutralCurrentAbnormalEventNo  },
	{(CTol_Clear_Degree|EventDI), 			    E2Addr_Tol_Clear_Degree,       E2Addr_Tol_Clear_In_End,       /*E2_Max_Addr,				E2_Max_Addr,		 			*/C_TolClearEventNo },		/*698方案用于修改总清、事件清零关联列表时，清对应事件记录*/
	{(CEven_Clear_Degree|EventDI),         E2Addr_Even_Clear_Degree,           E2Addr_Rec_Meter_Degree,       /*E2_Max_Addr,				E2_Max_Addr,		 				*/C_EventClearEventNo },
};
#define Str_EvenTableE2_Len  (sizeof(Str_EvenTableE2)/sizeof(Str_EvenTable))/*该表格 e2中数据长度与事件清零有关系注意事件清零程序*/

/****************************内部函数*****************************/
uchar8 SF_Find1Table_Data(uchar8  V_Data_Id3,ushort16 * P_Line);
uchar8 SF_Find2Table_DIParamChild(uchar8  V_Data_Id2,ushort16 * P_Line);
uchar8 SF_Find2Table_Data( uchar8  V_WR_Mes,ulong32  V_Data_Id,ushort16 * P_Data_Length,Str_2Table  * PStr_2Table,ushort16 * P_Line,ushort16 V_MaxLine);
uchar8 SF_WriteE2Three(ushort16 V_E2Addr,uchar8 V_DataLen,uchar8 * P_Data);
uchar8 SF_WriteFRAMThree(ushort16 V_E2Addr,uchar8 V_DataLen,uchar8 * P_Data);
uchar8 SF_WriteE2Three698(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 * P_Data);
uchar8 SF_WR_E23_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 * P_Data);
uchar8 SF_WR_E23_RAM_Data698(Str_3aTable * PStr_3aTable_E23RAM,ushort16 V_DataLen,uchar8 * P_Data,uchar8 V_DT_Type,uchar8 V_DI);
uchar8 SF_WR_E23_RAM_EnergyData(Str_3aTable * PStr_3aTable_E23RAM,ushort16 V_3aTable_Line,ushort16 V_DataLen,uchar8 * P_Data,uchar8 V_DT_Type,uchar8 V_DI);
uchar8 SF_WR_E23_RAM_Data(Str_3aTable * PStr_3aTable_E23RAM,ushort16 V_3aTable_Line,ushort16 V_DataLen,uchar8 * P_Data,uchar8 V_DT_Type,uchar8 V_DI);
uchar8 SF_Read_E21CRC_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 * P_Data);
uchar8 SF_Read_FRAM1CRC_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 * P_Data);
uchar8 SF_ReadE2Three(ushort16 V_E2Addr,uchar8 V_DataLen,uchar8 * P_Data);
#if 0
uchar8 SF_ReadFRAMThree1(ushort16 V_E2Addr,uchar8 V_DataLen,uchar8 * P_Data);
#endif
uchar8 SF_ReadFRAMThree(ushort16 V_E2Addr,uchar8 V_DataLen,uchar8 * P_Data);
uchar8 SF_ReadE21(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 * P_Data,uchar8 V_DT_Type,uchar8 V_WR_Mes);
ushort16 SF_GetOffAddr(Str_4Table * PStr_4TableAddr,ulong32 V_Data_Id,uchar8 V_Type,uchar8 V_4Table_Len);
void SF_GetFlashAddr(ulong32 V_NumE2,ulong32 V_StartFlashAddr,ushort16 V_NoteDataLength,ulong32 V_EndFlashAddr,ulong32 * P_ReturnFlashAddr);
uchar8 SF_WriteFlash(ulong32 V_FlashAddr,uchar8 * P_Data,ushort16 V_Data_Length,uchar8 V_EvenSign);
uchar8 SF_WriteFlash_Data(uchar8 * P_Data,ushort16 V_Data_Length,Str_3cTable * PStr_3cTable,ulong32 V_Data_Id,ushort16 V_3cTable_Line,uchar8 V_Type);
uchar8 SF_WR_E21CRC_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 * P_Data);
uchar8 SF_WR_FRAM1CRC_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 * P_Data);
uchar8 SF_WR_E21_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 * P_Data);
uchar8 SF_WR_RAM_Data(uchar8 * P_RamAddr,ushort16 V_DataLen,uchar8 * P_Data,uchar8 V_DT_Type,uchar8 Msg_Num);
uchar8 SF_WR_RAMCRC_Data(uchar8 * P_RamAddr,ushort16 V_DataLen,uchar8 * P_Data);
uchar8 SF_Re_E23_RAM_Data698(Str_3aTable * PStr_3aTable_E23RAM,ushort16 V_DataLen,uchar8 * P_Data);
uchar8 SF_Re_E23_RAM_Data(Str_3aTable * PStr_3aTable_E23RAM,ushort16 V_3aTable_Line,ushort16 V_DataLen,uchar8 * P_Data,uchar8 V_DT_Type,uchar8 V_DI,ulong32 V_Data_Id);
uchar8 SF_Re_E23_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 * P_Data,uchar8 V_DT_Type,uchar8 V_WR_Mes);
uchar8 SF_ReadFlash_Data(uchar8 * P_Data,ushort16 V_Data_Length,ulong32 Str_3TableAddr,ulong32 V_Data_Id,ushort16 V_3cTable_Line,uchar8 V_Type,uchar8 V_WR_Mes);
uchar8 SF_Re_RAM_Data(uchar8 * P_RamAddr,ushort16 V_DataLen,uchar8 * P_Data,uchar8 V_DT_Type,uchar8 V_DI0);
uchar8 SF_Re_RAMCRC_Data(uchar8 * P_RamAddr,ushort16 V_DataLen,uchar8 * P_Data);
uchar8 SF_Read_Data(ulong32 V_ulData_Id, uchar8 *pV_ucData, ushort16 *pV_usData_Length, uchar8 V_MesNum, ushort16 *pV_usDataEncode);
ushort16 SF_JudgeWriteDataLen( uchar8  V_DI2);
void SF_GetCurrLoadProfileFlashAddr(ushort16 V_Len,ulong32 * V_W_FlashAddr,ushort16 V_E2Addr_LoadP_Flash_Late,ushort16 V_E2Addr_LoadP_Flash_Ear,ulong32 V_FlashStAddr_LoadProfile,ulong32 V_FlashEndAddr_LoadProfile);
#if 0
void SF_EarlistLoadRefresh_E2_FlashLoadProfileMode(ulong32 V_WR_FlashAddr);
#endif
void SF_EarlistLoadProfileFlashAddrAdjust(ushort16 V_E2Addr_LoadP_Flash_Late,ushort16 V_E2Addr_LoadP_Flash_Ear,ulong32 V_FlashStAddr_LoadProfile,ulong32 V_FlashEndAddr_LoadProfile);
#if 0
uchar8 SF_Refresh_E2_FlashLoadProfileMode(ulong32 V_WR_FlashAddr,uchar8 V_Mode);
#endif
uchar8 SF_Write698FreezeData(uchar8 V_DI2Temp, uchar8  Message_Num, uchar8 * 	P_Data, ushort16 V_Data_Length);
void SF_ChageTime_ChageFlashNote(ulong32 V_FlashAddr,uchar8 V_Order,uchar8 V_ProNum);
#if 0
uchar8 SF_GetFlashAddrInE2BlockNum(ulong32 V_WR_FlashAddr);
uchar8 SF_CombOneFlashPageMode(uchar8 * V_Mode,uchar8 V_ModeNum);
void SF_ChageTime_RefreshE2_FlashLoadProfileMode(ulong32 V_FlashAddrLate,uchar8 V_Line,ulong32 V_FlashAddrEar);
#endif
ulong32 SF_GetFixedLoadModeNoteFlashAddr(uchar8 V_ProNum,uchar8 V_Order,ulong32 V_FindFlashAddr);
ulong32 SF_FindOneFlashPageGiveTimeFlashAddr(uchar8 V_ProNum,uchar8 V_Order,ulong32 V_FindFlashAddr,uchar8 * P_FixTime,uchar8 V_LoadDichotomyFindWay);
ulong32 SF_LoadDichotomyFixedFlashData(uchar8 V_ProNum,uchar8 V_Order,uchar8 * P_FixTime,ulong32 V_FlashAddrEar,ulong32 V_FlashAddrLate,uchar8 V_LoadDichotomyFindWay);
ulong32 SF_LoadDichotomyFlashData(uchar8 V_ProNum,uchar8 V_Order,uchar8 * P_FixTime,ulong32 V_FlashAddrEar,ulong32 V_FlashAddrLate,uchar8 V_LoadDichotomyFindWay);
ulong32 SF_FindLoadProfileFlashPage(void);
ushort16 SF_GetMinFreezeNum_OADTab(uchar8 V_ProNum,uchar8 * P_Data,ushort16 V_DataLen);
ushort16 SF_GetFreezeSaveDeep( uchar8  V_DI2Temp);
uchar8 SF_Clear_Engry(uchar8 V_D_SafeFlag);
uchar8 SF_Clear_Event(uchar8 V_D_SafeFlag);
uchar8 SF_Clear_Other(uchar8 V_D_SafeFlag);
uchar8 SF_Clear_Parm(uchar8 V_D_SafeFlag);
uchar8 SF_Clear_Custom(uchar8 V_D_SafeFlag);

ulong32 SF_FindEvenFlashPage(void);
#if 0
uchar8 SF_WriteMeterICData(uchar8 * P_Data,uchar8 V_MeterICData_Num);      /*写校表数据*/
#endif
uchar8 SF_AllDataZero_Judge(uchar8 * P_Data,uchar8 V_DataLen);
ulong32 SF_FindMinFreezeFirstVolidOAD(ulong32 * P_Data_Id_OAD);
/******************提供外部接口函数**********************/
uchar8 InF_Write_RecMeterData(uchar8 Msg_Num,uchar8 * P_Data,uchar8 V_Data_Length,uchar8 V_W_Safe_Flag,uchar8 V_Data_Num); 	/*写校表数据接口函数*/
uchar8 InF_Write_Data(uchar8 Msg_Num,ulong32 V_Data_Id,uchar8 * P_Data,ushort16 V_Data_Length,uchar8 V_W_Safe_Flag); 			/*写数据层接口函数*/
uchar8 InF_Read_RecMeterData(uchar8 V_Data_Num,uchar8 * P_Data,uchar8 * P_Data_Length);                              			/*读校表数据*/
uchar8 InF_Read_Data(ulong32 V_ulData_Id, uchar8 *pV_ucData, ushort16 *pV_usData_Length, ushort16 *pV_usDataEncode);           /*读数据层接口函数*/
#if 0
uchar8 InF_Read_Data_For_Dis(ulong32 V_ulData_Id, uchar8 *pV_ucData, ushort16 *pV_usData_Length);                              /*读数据层接口函数,专为显示模块提供接口函数*/
#endif
void InF_PowerOn_CurrEnergyDeal(void);                        /*上电电量处理接口函数,调度调用*/
#if 0
void InF_PowerDown_CurrEnergySave(void);                      /*当前电量停电保存接口函数,目前暂不启用该功能,调度调用*/
#endif
void InF_ChangeTime_LoadProfileCover(void);                   /*修改时间负荷记录覆盖接口函数,通信调用*/

void SF_UpdateE2CurrEnergy(void);
uchar8 InF_ReadLoadData(ulong32 V_Data_Id,uchar8 * P_FixTime,uchar8 * P_Data,uchar8 * V_BlockNum,uchar8 * V_Length,uchar8 V_ReadSign);	/**读负荷记录**/
uchar8 InF_Total_Clear(uchar8 Msg_Num,uchar8 V_CurrentState,uchar8 C_Safe_Flag);	/*电表总清,通信调用*/
uchar8 InF_EventNote_Clear(uchar8 Msg_Num,ulong32 V_Data_Id,uchar8 C_Safe_Flag);	/*事件记录清零,通信调用*/
uchar8 InF_Demand_Clear(uchar8 Msg_Num,uchar8 C_Safe_Flag);                     	/*需量清零,通信、结算调用*/
void Data_CruiseCheck_Message(Str_Msg_Parameter * P_Msg_Parameter);            	/*数据层巡航程序，调度每5s触发，不用带参数*/
void InF_Initial_Data(void);            /*初始化数据层参数，调度调用*/
uchar8 InF_EventNumFind(ulong32 V_Data_Id);    /*提供事件记录接口函数*/
uchar8 InF_ReadLastTimeLoadData(ulong32 V_Data_Id,uchar8 * P_FixTime,uchar8 * P_Data,uchar8 * V_BlockNum,uchar8 * V_Length);    /*负荷记录模块读上次负荷记录接口函数*/
uchar8 InF_RecMeterNote_Clear(uchar8 Msg_Num,uchar8 C_Safe_Flag);/*清校表记录*/
uchar8 InF_ReadFreezeData(ulong32 * P_Data_Id_OAD,uchar8 * P_FixTime,uchar8 * P_Data,ushort16 * V_BlockNum,ushort16 * V_Length,ushort16 V_IntervalTime,uchar8 * pV_FreezeTimeBuf,uchar8 V_Mode);
uchar8 InF_ReadEventData(ulong32 * P_Data_Id_OAD,uchar8 * P_FixTime,uchar8 * P_Data,uchar8 * V_NextSign,ushort16 * P_Data_Length,uchar8 V_timeFlash);
void InF_ReadE2_Flash_Data(uchar8  * PV_Data,uchar8 V_Len,uchar8 V_Sign,ulong32 V_Addr);/*后加调试代码*/
void InF_RAMDataRecoverFromE2(void);/*由通信模块触发调用，用于E2数据对RAM数据进行恢复*/
uchar8 SF_Read_698SpecialData(ulong32 V_ulData_Id, uchar8 *pV_ucData, ushort16 *pV_usData_Length, ushort16 *pV_usDataEncode);
void SF_EraseCodeFlash_Sector(ulong32 V_ulAddInSector);
void SF_WriteCodeFlash(ulong32 V_ulCodeFlashAdd, uchar8 *pV_ucDataIn, ushort16 V_usDataInLen);
#if 0
void SF_EraseCodeFlash_Block(ulong32 V_ulAddInBlock);
#endif
uchar8 SF_Deal_FF86(ulong32 V_Data_Id,uchar8 * P_Data,ushort16 V_Data_Length);
uchar8 SF_Deal_UpdataFlag(uchar8 V_ucOperationFlag, uchar8 *pV_ucData, ushort16 V_usDataIn_Len);

/******升级流程控制字结构体***/
typedef struct
{
	uchar8	ControlFlag[4];	/*升级流程控制标志：该数据高2字节为升级标志，96 87 ，底2字节为96 88 的CRC16校验值8A 4A（高字节在前）*/
	uchar8	FlowFlag;		/*升级流程控制状态：0表示未进入升级模式，1表示进入升级模式但是未下发升级版本信息，2表示支持升级*/
	uchar8	OverTimer;		/*升级流程控制超时定时器：初始值0，有相应正确操作则赋值超时定时器，reset定时器赋值2s，其他赋值10s*/
	uchar8	ucCRC[2];		/*升级流程CRC*/
}Str_UpdataFlag_Type;
static Str_UpdataFlag_Type SStr_UpdataFlag;		/*升级流程控制*/
#define C_Str_UpdataFlag_Len	sizeof(Str_UpdataFlag_Type)
#define C_UpdataFlag_OKFlag		0x96878A4A		/*标志正确数据*/

#define C_Updata_Init			0xFF			/*初始状态*/
#define C_Enter_UpdataFlag		1				/*进入升级模式*/
#define C_WriteFlag_OK			2				/*版本核对正确*/
#define C_ResetFlag_OK			3				/*reset flag*/
#define C_TimerDecrease			4				/*if OverTimer > 0, Timer--*/
#define C_OverTimer_10s			10				/*基于秒的10s定时器*/
#define C_OverTimer_2s			2				/*基于秒的2s定时器*/



#pragma pack()

#endif
