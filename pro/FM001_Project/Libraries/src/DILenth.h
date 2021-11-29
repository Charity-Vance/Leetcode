/****************************************************************************************
Copyright:	ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:	DILenth.h
Version:	V1
Date:		2014-3-12
Description:OAD长度文件
Function List:
****************************************************************************************
History1:	第1次修改
内容1.	Date:
		Author:
		Modification:
		**********************************************
内容2.	Date:
		Author:
		Modification:
		********************************************************************************
History2:	第2次修改
内容1.	Date:
		Author:
		Modification:
		**********************************************
内容2.	Date:
		Author:
		Modification:
****************************************************************************************/
#ifndef __DILenth_H
#define __DILenth_H

/************************当前组合有功电能*****************************************/
#define CLCom_Ac_Tol_En_0                 4        /*当前组合有功总电能*/
#define CLCom_Ac_T1_En_0                  4        /*当前组合有功费率1电能*/
#define CLCom_Ac_T2_En_0                  4        /*当前组合有功费率2电能*/
#define CLCom_Ac_T3_En_0                  4        /*当前组合有功费率3电能*/
#define CLCom_Ac_T4_En_0                  4        /*当前组合有功费率4电能*/
#define CLCom_Ac_T5_En_0                  4        /*当前组合有功费率5电能*/
#define CLCom_Ac_T6_En_0                  4        /*当前组合有功费率6电能*/
#define CLCom_Ac_T7_En_0                  4        /*当前组合有功费率7电能*/
#define CLCom_Ac_T8_En_0                  4        /*当前组合有功费率8电能*/
#define CLCom_Ac_T9_En_0                  4        /*当前组合有功费率9电能*/
#define CLCom_Ac_T10_En_0                 4        /*当前组合有功费率10电能*/
#define CLCom_Ac_T11_En_0                 4        /*当前组合有功费率11电能*/
#define CLCom_Ac_T12_En_0                 4        /*当前组合有功费率12电能*/
#define CLCom_Ac_En_FF_0                  52       /*当前组合有功电能数据块*/

/*精确电能数据层存储5字节，通讯自扩为8字节*/
#define CLCom_Ac_Tol_PreEn_0              5        /*当前组合有功总精确电能*/
#define CLCom_Ac_T1_PreEn_0               5        /*当前组合有功费率1精确电能*/
#define CLCom_Ac_T2_PreEn_0               5        /*当前组合有功费率2精确电能*/
#define CLCom_Ac_T3_PreEn_0               5        /*当前组合有功费率3精确电能*/
#define CLCom_Ac_T4_PreEn_0               5        /*当前组合有功费率4精确电能*/
#define CLCom_Ac_T5_PreEn_0               5        /*当前组合有功费率8精确电能*/
#define CLCom_Ac_T6_PreEn_0               5        /*当前组合有功费率6精确电能*/
#define CLCom_Ac_T7_PreEn_0               5        /*当前组合有功费率7精确电能*/
#define CLCom_Ac_T8_PreEn_0               5        /*当前组合有功费率8精确电能*/
#define CLCom_Ac_T9_PreEn_0               5        /*当前组合有功费率9精确电能*/
#define CLCom_Ac_T10_PreEn_0              5        /*当前组合有功费率10精确电能*/
#define CLCom_Ac_T11_PreEn_0              5        /*当前组合有功费率11精确电能*/
#define CLCom_Ac_T12_PreEn_0              5        /*当前组合有功费率12精确电能*/
#define CLCom_Ac_PreEn_FF_0               65       /*当前组合有功精确电能数据块*/

#define CLCom_Ac_Tol_LastPulse_0          1        /*当前组合有功总脉冲尾数*/
#define CLCom_Ac_T1_LastPulse_0           1        /*当前组合有功费率1脉冲尾数*/
#define CLCom_Ac_T2_LastPulse_0           1        /*当前组合有功费率2脉冲尾数*/
#define CLCom_Ac_T3_LastPulse_0           1        /*当前组合有功费率3脉冲尾数*/
#define CLCom_Ac_T4_LastPulse_0           1        /*当前组合有功费率4脉冲尾数*/
#define CLCom_Ac_T5_LastPulse_0           1        /*当前组合有功费率5脉冲尾数*/
#define CLCom_Ac_T6_LastPulse_0           1        /*当前组合有功费率6脉冲尾数*/
#define CLCom_Ac_T7_LastPulse_0           1        /*当前组合有功费率7脉冲尾数*/
#define CLCom_Ac_T8_LastPulse_0           1        /*当前组合有功费率8脉冲尾数*/
#define CLCom_Ac_T9_LastPulse_0           1        /*当前组合有功费率9脉冲尾数*/
#define CLCom_Ac_T10_LastPulse_0          1        /*当前组合有功费率10脉冲尾数*/
#define CLCom_Ac_T11_LastPulse_0          1        /*当前组合有功费率11脉冲尾数*/
#define CLCom_Ac_T12_LastPulse_0          1        /*当前组合有功费率12脉冲尾数*/
#define CLCom_Ac_LastPulse_FF_0           13       /*当前组合有功脉冲尾数数据块*/

/************************当前正向有功电能*****************************************/
#define CLPos_Ac_T1_En_Pul_0              5        /*当前正向有功费率1电能脉冲数*/
#define CLPos_Ac_T2_En_Pul_0              5        /*当前正向有功费率2电能脉冲数*/
#define CLPos_Ac_T3_En_Pul_0              5        /*当前正向有功费率3电能脉冲数*/
#define CLPos_Ac_T4_En_Pul_0              5        /*当前正向有功费率4电能脉冲数*/
#define CLPos_Ac_T5_En_Pul_0              5        /*当前正向有功费率5电能脉冲数*/
#define CLPos_Ac_T6_En_Pul_0              5        /*当前正向有功费率6电能脉冲数*/
#define CLPos_Ac_T7_En_Pul_0              5        /*当前正向有功费率7电能脉冲数*/
#define CLPos_Ac_T8_En_Pul_0              5        /*当前正向有功费率8电能脉冲数*/
#define CLPos_Ac_T9_En_Pul_0              5        /*当前正向有功费率9电能脉冲数*/
#define CLPos_Ac_T10_En_Pul_0             5        /*当前正向有功费率10电能脉冲数*/
#define CLPos_Ac_T11_En_Pul_0             5        /*当前正向有功费率11电能脉冲数*/
#define CLPos_Ac_T12_En_Pul_0             5        /*当前正向有功费率12电能脉冲数*/

#define CLPos_Ac_Tol_En_0                 4        /*当前正向有功总电能*/
#define CLPos_Ac_T1_En_0                  4        /*当前正向有功费率1电能*/
#define CLPos_Ac_T2_En_0                  4        /*当前正向有功费率2电能*/
#define CLPos_Ac_T3_En_0                  4        /*当前正向有功费率3电能*/
#define CLPos_Ac_T4_En_0                  4        /*当前正向有功费率4电能*/
#define CLPos_Ac_T5_En_0                  4        /*当前正向有功费率5电能*/
#define CLPos_Ac_T6_En_0                  4        /*当前正向有功费率6电能*/
#define CLPos_Ac_T7_En_0                  4        /*当前正向有功费率7电能*/
#define CLPos_Ac_T8_En_0                  4        /*当前正向有功费率8电能*/
#define CLPos_Ac_T9_En_0                  4        /*当前正向有功费率9电能*/
#define CLPos_Ac_T10_En_0                 4        /*当前正向有功费率10电能*/
#define CLPos_Ac_T11_En_0                 4        /*当前正向有功费率11电能*/
#define CLPos_Ac_T12_En_0                 4        /*当前正向有功费率12电能*/
#define CLPos_Ac_En_FF_0                  52       /*当前正向有功电能数据块*/

/*精确电能数据层存储5字节，通讯自扩为8字节*/
#define CLPos_Ac_Tol_PreEn_0              5        /*当前正向有功总精确电能*/
#define CLPos_Ac_T1_PreEn_0               5        /*当前正向有功费率1精确电能*/
#define CLPos_Ac_T2_PreEn_0               5        /*当前正向有功费率2精确电能*/
#define CLPos_Ac_T3_PreEn_0               5        /*当前正向有功费率3精确电能*/
#define CLPos_Ac_T4_PreEn_0               5        /*当前正向有功费率4精确电能*/
#define CLPos_Ac_T5_PreEn_0               5        /*当前正向有功费率8精确电能*/
#define CLPos_Ac_T6_PreEn_0               5        /*当前正向有功费率6精确电能*/
#define CLPos_Ac_T7_PreEn_0               5        /*当前正向有功费率7精确电能*/
#define CLPos_Ac_T8_PreEn_0               5        /*当前正向有功费率8精确电能*/
#define CLPos_Ac_T9_PreEn_0               5        /*当前正向有功费率9精确电能*/
#define CLPos_Ac_T10_PreEn_0              5        /*当前正向有功费率10精确电能*/
#define CLPos_Ac_T11_PreEn_0              5        /*当前正向有功费率11精确电能*/
#define CLPos_Ac_T12_PreEn_0              5        /*当前正向有功费率12精确电能*/
#define CLPos_Ac_En_PreFF_0               65       /*当前正向有功精确电能数据块*/

#define CLPos_Ac_Tol_LastPulse_0          1        /*当前正向有功总脉冲尾数*/
#define CLPos_Ac_T1_LastPulse_0           1        /*当前正向有功费率1脉冲尾数*/
#define CLPos_Ac_T2_LastPulse_0           1        /*当前正向有功费率2脉冲尾数*/
#define CLPos_Ac_T3_LastPulse_0           1        /*当前正向有功费率3脉冲尾数*/
#define CLPos_Ac_T4_LastPulse_0           1        /*当前正向有功费率4脉冲尾数*/
#define CLPos_Ac_T5_LastPulse_0           1        /*当前正向有功费率5脉冲尾数*/
#define CLPos_Ac_T6_LastPulse_0           1        /*当前正向有功费率6脉冲尾数*/
#define CLPos_Ac_T7_LastPulse_0           1        /*当前正向有功费率7脉冲尾数*/
#define CLPos_Ac_T8_LastPulse_0           1        /*当前正向有功费率8脉冲尾数*/
#define CLPos_Ac_T9_LastPulse_0           1        /*当前正向有功费率9脉冲尾数*/
#define CLPos_Ac_T10_LastPulse_0          1        /*当前正向有功费率10脉冲尾数*/
#define CLPos_Ac_T11_LastPulse_0          1        /*当前正向有功费率11脉冲尾数*/
#define CLPos_Ac_T12_LastPulse_0          1        /*当前正向有功费率12脉冲尾数*/
#define CLPos_Ac_LastPulse_FF_0           13       /*当前正向有功脉冲尾数数据块*/

/************************当前反向有功电能*****************************************/
#define CLRev_Ac_T1_En_Pul_0             5        /*当前反向有功费率1电能脉冲数*/
#define CLRev_Ac_T2_En_Pul_0             5        /*当前反向有功费率2电能脉冲数*/
#define CLRev_Ac_T3_En_Pul_0             5        /*当前反向有功费率3电能脉冲数*/
#define CLRev_Ac_T4_En_Pul_0             5        /*当前反向有功费率4电能脉冲数*/
#define CLRev_Ac_T5_En_Pul_0             5        /*当前反向有功费率5电能脉冲数*/
#define CLRev_Ac_T6_En_Pul_0             5        /*当前反向有功费率6电能脉冲数*/
#define CLRev_Ac_T7_En_Pul_0             5        /*当前反向有功费率7电能脉冲数*/
#define CLRev_Ac_T8_En_Pul_0             5        /*当前反向有功费率8电能脉冲数*/
#define CLRev_Ac_T9_En_Pul_0             5        /*当前反向有功费率9电能脉冲数*/
#define CLRev_Ac_T10_En_Pul_0            5        /*当前反向有功费率10电能脉冲数*/
#define CLRev_Ac_T11_En_Pul_0            5        /*当前反向有功费率11电能脉冲数*/
#define CLRev_Ac_T12_En_Pul_0            5        /*当前反向有功费率12电能脉冲数*/

#define CLRev_Ac_Tol_En_0                4        /*当前反向有功总电能*/
#define CLRev_Ac_T1_En_0                 4        /*当前反向有功费率1电能*/
#define CLRev_Ac_T2_En_0                 4        /*当前反向有功费率2电能*/
#define CLRev_Ac_T3_En_0                 4        /*当前反向有功费率3电能*/
#define CLRev_Ac_T4_En_0                 4        /*当前反向有功费率4电能*/
#define CLRev_Ac_T5_En_0                 4        /*当前反向有功费率5电能*/
#define CLRev_Ac_T6_En_0                 4        /*当前反向有功费率6电能*/
#define CLRev_Ac_T7_En_0                 4        /*当前反向有功费率7电能*/
#define CLRev_Ac_T8_En_0                 4        /*当前反向有功费率8电能*/
#define CLRev_Ac_T9_En_0                 4        /*当前反向有功费率9电能*/
#define CLRev_Ac_T10_En_0                4        /*当前反向有功费率10电能*/
#define CLRev_Ac_T11_En_0                4        /*当前反向有功费率11电能*/
#define CLRev_Ac_T12_En_0                4        /*当前反向有功费率12电能*/
#define CLRev_Ac_En_FF_0                 52       /*当前反向有功电能数据块*/

/*精确电能数据层存储5字节，通讯自扩为8字节*/
#define CLRev_Ac_Tol_PreEn_0             5        /*当前反向有功总精确电能*/
#define CLRev_Ac_T1_PreEn_0              5        /*当前反向有功费率1精确电能*/
#define CLRev_Ac_T2_PreEn_0              5        /*当前反向有功费率2精确电能*/
#define CLRev_Ac_T3_PreEn_0              5        /*当前反向有功费率3精确电能*/
#define CLRev_Ac_T4_PreEn_0              5        /*当前反向有功费率4精确电能*/
#define CLRev_Ac_T5_PreEn_0              5        /*当前反向有功费率8精确电能*/
#define CLRev_Ac_T6_PreEn_0              5        /*当前反向有功费率6精确电能*/
#define CLRev_Ac_T7_PreEn_0              5        /*当前反向有功费率7精确电能*/
#define CLRev_Ac_T8_PreEn_0              5        /*当前反向有功费率8精确电能*/
#define CLRev_Ac_T9_PreEn_0              5        /*当前反向有功费率9精确电能*/
#define CLRev_Ac_T10_PreEn_0             5        /*当前反向有功费率10精确电能*/
#define CLRev_Ac_T11_PreEn_0             5        /*当前反向有功费率11精确电能*/
#define CLRev_Ac_T12_PreEn_0             5        /*当前反向有功费率12精确电能*/
#define CLRev_Ac_En_PreFF_0              65       /*当前反向有功精确电能数据块*/

#define CLRev_Ac_Tol_LastPulse_0         1        /*当前反向有功总脉冲尾数*/
#define CLRev_Ac_T1_LastPulse_0          1        /*当前反向有功费率1脉冲尾数*/
#define CLRev_Ac_T2_LastPulse_0          1        /*当前反向有功费率2脉冲尾数*/
#define CLRev_Ac_T3_LastPulse_0          1        /*当前反向有功费率3脉冲尾数*/
#define CLRev_Ac_T4_LastPulse_0          1        /*当前反向有功费率4脉冲尾数*/
#define CLRev_Ac_T5_LastPulse_0          1        /*当前反向有功费率5脉冲尾数*/
#define CLRev_Ac_T6_LastPulse_0          1        /*当前反向有功费率6脉冲尾数*/
#define CLRev_Ac_T7_LastPulse_0          1        /*当前反向有功费率7脉冲尾数*/
#define CLRev_Ac_T8_LastPulse_0          1        /*当前反向有功费率8脉冲尾数*/
#define CLRev_Ac_T9_LastPulse_0          1        /*当前反向有功费率9脉冲尾数*/
#define CLRev_Ac_T10_LastPulse_0         1        /*当前反向有功费率10脉冲尾数*/
#define CLRev_Ac_T11_LastPulse_0         1        /*当前反向有功费率11脉冲尾数*/
#define CLRev_Ac_T12_LastPulse_0         1        /*当前反向有功费率12脉冲尾数*/
#define CLRev_Ac_LastPulse_FF_0          13       /*当前反向有功脉冲尾数数据块*/

/************************当前组合无功1电能*****************************************/
#define CLCom_Re1_Tol_En_0               4        /*当前组合无功1总电能*/
#define CLCom_Re1_T1_En_0                4        /*当前组合无功1费率1电能*/
#define CLCom_Re1_T2_En_0                4        /*当前组合无功1费率2电能*/
#define CLCom_Re1_T3_En_0                4        /*当前组合无功1费率3电能*/
#define CLCom_Re1_T4_En_0                4        /*当前组合无功1费率4电能*/
#define CLCom_Re1_T5_En_0                4        /*当前组合无功1费率5电能*/
#define CLCom_Re1_T6_En_0                4        /*当前组合无功1费率6电能*/
#define CLCom_Re1_T7_En_0                4        /*当前组合无功1费率7电能*/
#define CLCom_Re1_T8_En_0                4        /*当前组合无功1费率8电能*/
#define CLCom_Re1_T9_En_0                4        /*当前组合无功1费率9电能*/
#define CLCom_Re1_T10_En_0               4        /*当前组合无功1费率10电能*/
#define CLCom_Re1_T11_En_0               4        /*当前组合无功1费率11电能*/
#define CLCom_Re1_T12_En_0               4        /*当前组合无功1费率12电能*/
#define CLCom_Re1_En_FF_0                52       /*当前组合无功1电能数据块*/

/*精确电能数据层存储5字节，通讯自扩为8字节*/
#define CLCom_Re1_Tol_PreEn_0            5        /*当前组合无功1精确总电能*/
#define CLCom_Re1_T1_PreEn_0             5        /*当前组合无功1费率1精确电能*/
#define CLCom_Re1_T2_PreEn_0             5        /*当前组合无功1费率2精确电能*/
#define CLCom_Re1_T3_PreEn_0             5        /*当前组合无功1费率3精确电能*/
#define CLCom_Re1_T4_PreEn_0             5        /*当前组合无功1费率4精确电能*/
#define CLCom_Re1_T5_PreEn_0             5        /*当前组合无功1费率8精确电能*/
#define CLCom_Re1_T6_PreEn_0             5        /*当前组合无功1费率6精确电能*/
#define CLCom_Re1_T7_PreEn_0             5        /*当前组合无功1费率7精确电能*/
#define CLCom_Re1_T8_PreEn_0             5        /*当前组合无功1费率8精确电能*/
#define CLCom_Re1_T9_PreEn_0             5        /*当前组合无功1费率9精确电能*/
#define CLCom_Re1_T10_PreEn_0            5        /*当前组合无功1费率10精确电能*/
#define CLCom_Re1_T11_PreEn_0            5        /*当前组合无功1费率11精确电能*/
#define CLCom_Re1_T12_PreEn_0            5        /*当前组合无功1费率12精确电能*/
#define CLCom_Re1_PreEn_FF_0             65       /*当前组合无功1精确电能数据块*/

#define CLCom_Re1_Tol_LastPulse_0        1        /*当前组合无功1脉冲尾数*/
#define CLCom_Re1_T1_LastPulse_0         1        /*当前组合无功1费率1脉冲尾数*/
#define CLCom_Re1_T2_LastPulse_0         1        /*当前组合无功1费率2脉冲尾数*/
#define CLCom_Re1_T3_LastPulse_0         1        /*当前组合无功1费率3脉冲尾数*/
#define CLCom_Re1_T4_LastPulse_0         1        /*当前组合无功1费率4脉冲尾数*/
#define CLCom_Re1_T5_LastPulse_0         1        /*当前组合无功1费率5脉冲尾数*/
#define CLCom_Re1_T6_LastPulse_0         1        /*当前组合无功1费率6脉冲尾数*/
#define CLCom_Re1_T7_LastPulse_0         1        /*当前组合无功1费率7脉冲尾数*/
#define CLCom_Re1_T8_LastPulse_0         1        /*当前组合无功1费率8脉冲尾数*/
#define CLCom_Re1_T9_LastPulse_0         1        /*当前组合无功1费率9脉冲尾数*/
#define CLCom_Re1_T10_LastPulse_0        1        /*当前组合无功1费率10脉冲尾数*/
#define CLCom_Re1_T11_LastPulse_0        1        /*当前组合无功1费率11脉冲尾数*/
#define CLCom_Re1_T12_LastPulse_0        1        /*当前组合无功1费率12脉冲尾数*/
#define CLCom_Re1_LastPulse_FF_0         13       /*当前组合无功1脉冲尾数数据块*/

/************************当前组合无功2电能*****************************************/
#define CLCom_Re2_Tol_En_0               4        /*当前组合无功2总电能*/
#define CLCom_Re2_T1_En_0                4        /*当前组合无功2费率1电能*/
#define CLCom_Re2_T2_En_0                4        /*当前组合无功2费率2电能*/
#define CLCom_Re2_T3_En_0                4        /*当前组合无功2费率3电能*/
#define CLCom_Re2_T4_En_0                4        /*当前组合无功2费率4电能*/
#define CLCom_Re2_T5_En_0                4        /*当前组合无功2费率5电能*/
#define CLCom_Re2_T6_En_0                4        /*当前组合无功2费率6电能*/
#define CLCom_Re2_T7_En_0                4        /*当前组合无功2费率7电能*/
#define CLCom_Re2_T8_En_0                4        /*当前组合无功2费率8电能*/
#define CLCom_Re2_T9_En_0                4        /*当前组合无功2费率9电能*/
#define CLCom_Re2_T10_En_0               4        /*当前组合无功2费率10电能*/
#define CLCom_Re2_T11_En_0               4        /*当前组合无功2费率11电能*/
#define CLCom_Re2_T12_En_0               4        /*当前组合无功2费率12电能*/
#define CLCom_Re2_En_FF_0                52       /*当前组合无功2电能数据块*/

/*精确电能数据层存储5字节，通讯自扩为8字节*/
#define CLCom_Re2_Tol_PreEn_0            5        /*当前组合无功2总电能*/
#define CLCom_Re2_T1_PreEn_0             5        /*当前组合无功2费率1电能*/
#define CLCom_Re2_T2_PreEn_0             5        /*当前组合无功2费率2电能*/
#define CLCom_Re2_T3_PreEn_0             5        /*当前组合无功2费率3电能*/
#define CLCom_Re2_T4_PreEn_0             5        /*当前组合无功2费率4电能*/
#define CLCom_Re2_T5_PreEn_0             5        /*当前组合无功2费率8电能*/
#define CLCom_Re2_T6_PreEn_0             5        /*当前组合无功2费率6电能*/
#define CLCom_Re2_T7_PreEn_0             5        /*当前组合无功2费率7电能*/
#define CLCom_Re2_T8_PreEn_0             5        /*当前组合无功2费率8电能*/
#define CLCom_Re2_T9_PreEn_0             5        /*当前组合无功2费率9电能*/
#define CLCom_Re2_T10_PreEn_0            5        /*当前组合无功2费率10电能*/
#define CLCom_Re2_T11_PreEn_0            5        /*当前组合无功2费率11电能*/
#define CLCom_Re2_T12_PreEn_0            5        /*当前组合无功2费率12电能*/
#define CLCom_Re2_PreEn_FF_0             65       /*当前组合无功2电能数据块*/

#define CLCom_Re2_Tol_LastPulse_0        1        /*当前组合无功2总脉冲尾数*/
#define CLCom_Re2_T1_LastPulse_0         1        /*当前组合无功2费率1脉冲尾数*/
#define CLCom_Re2_T2_LastPulse_0         1        /*当前组合无功2费率2脉冲尾数*/
#define CLCom_Re2_T3_LastPulse_0         1        /*当前组合无功2费率3脉冲尾数*/
#define CLCom_Re2_T4_LastPulse_0         1        /*当前组合无功2费率4脉冲尾数*/
#define CLCom_Re2_T5_LastPulse_0         1        /*当前组合无功2费率5脉冲尾数*/
#define CLCom_Re2_T6_LastPulse_0         1        /*当前组合无功2费率6脉冲尾数*/
#define CLCom_Re2_T7_LastPulse_0         1        /*当前组合无功2费率7脉冲尾数*/
#define CLCom_Re2_T8_LastPulse_0         1        /*当前组合无功2费率8脉冲尾数*/
#define CLCom_Re2_T9_LastPulse_0         1        /*当前组合无功2费率9脉冲尾数*/
#define CLCom_Re2_T10_LastPulse_0        1        /*当前组合无功2费率10脉冲尾数*/
#define CLCom_Re2_T11_LastPulse_0        1        /*当前组合无功2费率11脉冲尾数*/
#define CLCom_Re2_T12_LastPulse_0        1        /*当前组合无功2费率12脉冲尾数*/
#define CLCom_Re2_LastPulse_FF_0         13       /*当前组合无功2脉冲尾数数据块*/

/************************当前1象限无功电能*****************************************/
#define CLQua1_Re_T1_En_Pul_0            5        /*当前1象限无功费率1电能脉冲数*/
#define CLQua1_Re_T2_En_Pul_0            5        /*当前1象限无功费率2电能脉冲数*/
#define CLQua1_Re_T3_En_Pul_0            5        /*当前1象限无功费率3电能脉冲数*/
#define CLQua1_Re_T4_En_Pul_0            5        /*当前1象限无功费率4电能脉冲数*/
#define CLQua1_Re_T5_En_Pul_0            5        /*当前1象限无功费率5电能脉冲数*/
#define CLQua1_Re_T6_En_Pul_0            5        /*当前1象限无功费率6电能脉冲数*/
#define CLQua1_Re_T7_En_Pul_0            5        /*当前1象限无功费率7电能脉冲数*/
#define CLQua1_Re_T8_En_Pul_0            5        /*当前1象限无功费率8电能脉冲数*/
#define CLQua1_Re_T9_En_Pul_0            5        /*当前1象限无功费率9电能脉冲数*/
#define CLQua1_Re_T10_En_Pul_0           5        /*当前1象限无功费率10电能脉冲数*/
#define CLQua1_Re_T11_En_Pul_0           5        /*当前1象限无功费率11电能脉冲数*/
#define CLQua1_Re_T12_En_Pul_0           5        /*当前1象限无功费率12电能脉冲数*/

#define CLQua1_Re_Tol_En_0               4        /*当前1象限无功总电能*/
#define CLQua1_Re_T1_En_0                4        /*当前1象限无功费率1电能*/
#define CLQua1_Re_T2_En_0                4        /*当前1象限无功费率2电能*/
#define CLQua1_Re_T3_En_0                4        /*当前1象限无功费率3电能*/
#define CLQua1_Re_T4_En_0                4        /*当前1象限无功费率4电能*/
#define CLQua1_Re_T5_En_0                4        /*当前1象限无功费率5电能*/
#define CLQua1_Re_T6_En_0                4        /*当前1象限无功费率6电能*/
#define CLQua1_Re_T7_En_0                4        /*当前1象限无功费率7电能*/
#define CLQua1_Re_T8_En_0                4        /*当前1象限无功费率8电能*/
#define CLQua1_Re_T9_En_0                4        /*当前1象限无功费率9电能*/
#define CLQua1_Re_T10_En_0               4        /*当前1象限无功费率10电能*/
#define CLQua1_Re_T11_En_0               4        /*当前1象限无功费率11电能*/
#define CLQua1_Re_T12_En_0               4        /*当前1象限无功费率12电能*/
#define CLQua1_Re_En_FF_0                52       /*当前1象限无功电能数据块*/

/*精确电能数据层存储5字节，通讯自扩为8字节*/
#define CLQua1_Re_Tol_PreEn_0            5        /*当前1象限无功总精确电能*/
#define CLQua1_Re_T1_PreEn_0             5        /*当前1象限无功费率1精确电能*/
#define CLQua1_Re_T2_PreEn_0             5        /*当前1象限无功费率2精确电能*/
#define CLQua1_Re_T3_PreEn_0             5        /*当前1象限无功费率3精确电能*/
#define CLQua1_Re_T4_PreEn_0             5        /*当前1象限无功费率4精确电能*/
#define CLQua1_Re_T5_PreEn_0             5        /*当前1象限无功费率8精确电能*/
#define CLQua1_Re_T6_PreEn_0             5        /*当前1象限无功费率6精确电能*/
#define CLQua1_Re_T7_PreEn_0             5        /*当前1象限无功费率7精确电能*/
#define CLQua1_Re_T8_PreEn_0             5        /*当前1象限无功费率8精确电能*/
#define CLQua1_Re_T9_PreEn_0             5        /*当前1象限无功费率9精确电能*/
#define CLQua1_Re_T10_PreEn_0            5        /*当前1象限无功费率10精确电能*/
#define CLQua1_Re_T11_PreEn_0            5        /*当前1象限无功费率11精确电能*/
#define CLQua1_Re_T12_PreEn_0            5        /*当前1象限无功费率12精确电能*/
#define CLQua1_Re_PreEn_FF_0             65       /*当前1象限无功精确电能数据块*/

#define CLQua1_Re_Tol_LastPulse_0        1        /*当前1象限无功总脉冲尾数*/
#define CLQua1_Re_T1_LastPulse_0         1        /*当前1象限无功费率1脉冲尾数*/
#define CLQua1_Re_T2_LastPulse_0         1        /*当前1象限无功费率2脉冲尾数*/
#define CLQua1_Re_T3_LastPulse_0         1        /*当前1象限无功费率3脉冲尾数*/
#define CLQua1_Re_T4_LastPulse_0         1        /*当前1象限无功费率4脉冲尾数*/
#define CLQua1_Re_T5_LastPulse_0         1        /*当前1象限无功费率5脉冲尾数*/
#define CLQua1_Re_T6_LastPulse_0         1        /*当前1象限无功费率6脉冲尾数*/
#define CLQua1_Re_T7_LastPulse_0         1        /*当前1象限无功费率7脉冲尾数*/
#define CLQua1_Re_T8_LastPulse_0         1        /*当前1象限无功费率8脉冲尾数*/
#define CLQua1_Re_T9_LastPulse_0         1        /*当前1象限无功费率9脉冲尾数*/
#define CLQua1_Re_T10_LastPulse_0        1        /*当前1象限无功费率10脉冲尾数*/
#define CLQua1_Re_T11_LastPulse_0        1        /*当前1象限无功费率11脉冲尾数*/
#define CLQua1_Re_T12_LastPulse_0        1        /*当前1象限无功费率12脉冲尾数*/
#define CLQua1_Re_LastPulse_FF_0         13       /*当前1象限无功脉冲尾数数据块*/

/************************当前2象限无功电能*****************************************/
#define CLQua2_Re_T1_En_Pul_0            5        /*当前2象限无功费率1电能脉冲数*/
#define CLQua2_Re_T2_En_Pul_0            5        /*当前2象限无功费率2电能脉冲数*/
#define CLQua2_Re_T3_En_Pul_0            5        /*当前2象限无功费率3电能脉冲数*/
#define CLQua2_Re_T4_En_Pul_0            5        /*当前2象限无功费率4电能脉冲数*/
#define CLQua2_Re_T5_En_Pul_0            5        /*当前2象限无功费率5电能脉冲数*/
#define CLQua2_Re_T6_En_Pul_0            5        /*当前2象限无功费率6电能脉冲数*/
#define CLQua2_Re_T7_En_Pul_0            5        /*当前2象限无功费率7电能脉冲数*/
#define CLQua2_Re_T8_En_Pul_0            5        /*当前2象限无功费率8电能脉冲数*/
#define CLQua2_Re_T9_En_Pul_0            5        /*当前2象限无功费率9电能脉冲数*/
#define CLQua2_Re_T10_En_Pul_0           5        /*当前2象限无功费率10电能脉冲数*/
#define CLQua2_Re_T11_En_Pul_0           5        /*当前2象限无功费率11电能脉冲数*/
#define CLQua2_Re_T12_En_Pul_0           5        /*当前2象限无功费率12电能脉冲数*/

#define CLQua2_Re_Tol_En_0               4        /*当前2象限无功总电能*/
#define CLQua2_Re_T1_En_0                4        /*当前2象限无功费率1电能*/
#define CLQua2_Re_T2_En_0                4        /*当前2象限无功费率2电能*/
#define CLQua2_Re_T3_En_0                4        /*当前2象限无功费率3电能*/
#define CLQua2_Re_T4_En_0                4        /*当前2象限无功费率4电能*/
#define CLQua2_Re_T5_En_0                4        /*当前2象限无功费率5电能*/
#define CLQua2_Re_T6_En_0                4        /*当前2象限无功费率6电能*/
#define CLQua2_Re_T7_En_0                4        /*当前2象限无功费率7电能*/
#define CLQua2_Re_T8_En_0                4        /*当前2象限无功费率8电能*/
#define CLQua2_Re_T9_En_0                4        /*当前2象限无功费率9电能*/
#define CLQua2_Re_T10_En_0               4        /*当前2象限无功费率10电能*/
#define CLQua2_Re_T11_En_0               4        /*当前2象限无功费率11电能*/
#define CLQua2_Re_T12_En_0               4        /*当前2象限无功费率12电能*/
#define CLQua2_Re_En_FF_0                52       /*当前2象限无功电能数据块*/

/*精确电能数据层存储5字节，通讯自扩为8字节*/
#define CLQua2_Re_Tol_PreEn_0            5        /*当前2象限无功总精确电能*/
#define CLQua2_Re_T1_PreEn_0             5        /*当前2象限无功费率1精确电能*/
#define CLQua2_Re_T2_PreEn_0             5        /*当前2象限无功费率2精确电能*/
#define CLQua2_Re_T3_PreEn_0             5        /*当前2象限无功费率3精确电能*/
#define CLQua2_Re_T4_PreEn_0             5        /*当前2象限无功费率4精确电能*/
#define CLQua2_Re_T5_PreEn_0             5        /*当前2象限无功费率8精确电能*/
#define CLQua2_Re_T6_PreEn_0             5        /*当前2象限无功费率6精确电能*/
#define CLQua2_Re_T7_PreEn_0             5        /*当前2象限无功费率7精确电能*/
#define CLQua2_Re_T8_PreEn_0             5        /*当前2象限无功费率8精确电能*/
#define CLQua2_Re_T9_PreEn_0             5        /*当前2象限无功费率9精确电能*/
#define CLQua2_Re_T10_PreEn_0            5        /*当前2象限无功费率10精确电能*/
#define CLQua2_Re_T11_PreEn_0            5        /*当前2象限无功费率11精确电能*/
#define CLQua2_Re_T12_PreEn_0            5        /*当前2象限无功费率12精确电能*/
#define CLQua2_Re_PreEn_FF_0             65       /*当前2象限无功精确电能数据块*/

#define CLQua2_Re_Tol_LastPulse_0        1        /*当前2象限无功总脉冲尾数*/
#define CLQua2_Re_T1_LastPulse_0         1        /*当前2象限无功费率1脉冲尾数*/
#define CLQua2_Re_T2_LastPulse_0         1        /*当前2象限无功费率2脉冲尾数*/
#define CLQua2_Re_T3_LastPulse_0         1        /*当前2象限无功费率3脉冲尾数*/
#define CLQua2_Re_T4_LastPulse_0         1        /*当前2象限无功费率4脉冲尾数*/
#define CLQua2_Re_T5_LastPulse_0         1        /*当前2象限无功费率5脉冲尾数*/
#define CLQua2_Re_T6_LastPulse_0         1        /*当前2象限无功费率6脉冲尾数*/
#define CLQua2_Re_T7_LastPulse_0         1        /*当前2象限无功费率7脉冲尾数*/
#define CLQua2_Re_T8_LastPulse_0         1        /*当前2象限无功费率8脉冲尾数*/
#define CLQua2_Re_T9_LastPulse_0         1        /*当前2象限无功费率9脉冲尾数*/
#define CLQua2_Re_T10_LastPulse_0        1        /*当前2象限无功费率10脉冲尾数*/
#define CLQua2_Re_T11_LastPulse_0        1        /*当前2象限无功费率11脉冲尾数*/
#define CLQua2_Re_T12_LastPulse_0        1        /*当前2象限无功费率12脉冲尾数*/
#define CLQua2_Re_LastPulse_FF_0         13       /*当前2象限无功脉冲尾数数据块*/

/************************当前3象限无功电能*****************************************/
#define CLQua3_Re_T1_En_Pul_0            5        /*当前3象限无功费率1电能脉冲数*/
#define CLQua3_Re_T2_En_Pul_0            5        /*当前3象限无功费率2电能脉冲数*/
#define CLQua3_Re_T3_En_Pul_0            5        /*当前3象限无功费率3电能脉冲数*/
#define CLQua3_Re_T4_En_Pul_0            5        /*当前3象限无功费率4电能脉冲数*/
#define CLQua3_Re_T5_En_Pul_0            5        /*当前3象限无功费率5电能脉冲数*/
#define CLQua3_Re_T6_En_Pul_0            5        /*当前3象限无功费率6电能脉冲数*/
#define CLQua3_Re_T7_En_Pul_0            5        /*当前3象限无功费率7电能脉冲数*/
#define CLQua3_Re_T8_En_Pul_0            5        /*当前3象限无功费率8电能脉冲数*/
#define CLQua3_Re_T9_En_Pul_0            5        /*当前3象限无功费率9电能脉冲数*/
#define CLQua3_Re_T10_En_Pul_0           5        /*当前3象限无功费率10电能脉冲数*/
#define CLQua3_Re_T11_En_Pul_0           5        /*当前3象限无功费率11电能脉冲数*/
#define CLQua3_Re_T12_En_Pul_0           5        /*当前3象限无功费率12电能脉冲数*/

#define CLQua3_Re_Tol_En_0               4        /*当前3象限无功总电能*/
#define CLQua3_Re_T1_En_0                4        /*当前3象限无功费率1电能*/
#define CLQua3_Re_T2_En_0                4        /*当前3象限无功费率2电能*/
#define CLQua3_Re_T3_En_0                4        /*当前3象限无功费率3电能*/
#define CLQua3_Re_T4_En_0                4        /*当前3象限无功费率4电能*/
#define CLQua3_Re_T5_En_0                4        /*当前3象限无功费率5电能*/
#define CLQua3_Re_T6_En_0                4        /*当前3象限无功费率6电能*/
#define CLQua3_Re_T7_En_0                4        /*当前3象限无功费率7电能*/
#define CLQua3_Re_T8_En_0                4        /*当前3象限无功费率8电能*/
#define CLQua3_Re_T9_En_0                4        /*当前3象限无功费率9电能*/
#define CLQua3_Re_T10_En_0               4        /*当前3象限无功费率10电能*/
#define CLQua3_Re_T11_En_0               4        /*当前3象限无功费率11电能*/
#define CLQua3_Re_T12_En_0               4        /*当前3象限无功费率12电能*/
#define CLQua3_Re_En_FF_0                52       /*当前3象限无功电能数据块*/

/*精确电能数据层存储5字节，通讯自扩为8字节*/
#define CLQua3_Re_Tol_PreEn_0            5        /*当前3象限无功总精确电能*/
#define CLQua3_Re_T1_PreEn_0             5        /*当前3象限无功费率1精确电能*/
#define CLQua3_Re_T2_PreEn_0             5        /*当前3象限无功费率2精确电能*/
#define CLQua3_Re_T3_PreEn_0             5        /*当前3象限无功费率3精确电能*/
#define CLQua3_Re_T4_PreEn_0             5        /*当前3象限无功费率4精确电能*/
#define CLQua3_Re_T5_PreEn_0             5        /*当前3象限无功费率8精确电能*/
#define CLQua3_Re_T6_PreEn_0             5        /*当前3象限无功费率6精确电能*/
#define CLQua3_Re_T7_PreEn_0             5        /*当前3象限无功费率7精确电能*/
#define CLQua3_Re_T8_PreEn_0             5        /*当前3象限无功费率8精确电能*/
#define CLQua3_Re_T9_PreEn_0             5        /*当前3象限无功费率9精确电能*/
#define CLQua3_Re_T10_PreEn_0            5        /*当前3象限无功费率10精确电能*/
#define CLQua3_Re_T11_PreEn_0            5        /*当前3象限无功费率11精确电能*/
#define CLQua3_Re_T12_PreEn_0            5        /*当前3象限无功费率12精确电能*/
#define CLQua3_Re_PreEn_FF_0             65       /*当前3象限无功精确电能数据块*/

#define CLQua3_Re_Tol_LastPulse_0        1        /*当前3象限无功总脉冲尾数*/
#define CLQua3_Re_T1_LastPulse_0         1        /*当前3象限无功费率1脉冲尾数*/
#define CLQua3_Re_T2_LastPulse_0         1        /*当前3象限无功费率2脉冲尾数*/
#define CLQua3_Re_T3_LastPulse_0         1        /*当前3象限无功费率3脉冲尾数*/
#define CLQua3_Re_T4_LastPulse_0         1        /*当前3象限无功费率4脉冲尾数*/
#define CLQua3_Re_T5_LastPulse_0         1        /*当前3象限无功费率5脉冲尾数*/
#define CLQua3_Re_T6_LastPulse_0         1        /*当前3象限无功费率6脉冲尾数*/
#define CLQua3_Re_T7_LastPulse_0         1        /*当前3象限无功费率7脉冲尾数*/
#define CLQua3_Re_T8_LastPulse_0         1        /*当前3象限无功费率8脉冲尾数*/
#define CLQua3_Re_T9_LastPulse_0         1        /*当前3象限无功费率9脉冲尾数*/
#define CLQua3_Re_T10_LastPulse_0        1        /*当前3象限无功费率10脉冲尾数*/
#define CLQua3_Re_T11_LastPulse_0        1        /*当前3象限无功费率11脉冲尾数*/
#define CLQua3_Re_T12_LastPulse_0        1        /*当前3象限无功费率12脉冲尾数*/
#define CLQua3_Re_LastPulse_FF_0         13       /*当前3象限无功脉冲尾数数据块*/

/************************当前4象限无功电能*****************************************/
#define CLQua4_Re_T1_En_Pul_0            5        /*当前4象限无功费率1电能脉冲数*/
#define CLQua4_Re_T2_En_Pul_0            5        /*当前4象限无功费率2电能脉冲数*/
#define CLQua4_Re_T3_En_Pul_0            5        /*当前4象限无功费率3电能脉冲数*/
#define CLQua4_Re_T4_En_Pul_0            5        /*当前4象限无功费率4电能脉冲数*/
#define CLQua4_Re_T5_En_Pul_0            5        /*当前4象限无功费率5电能脉冲数*/
#define CLQua4_Re_T6_En_Pul_0            5        /*当前4象限无功费率6电能脉冲数*/
#define CLQua4_Re_T7_En_Pul_0            5        /*当前4象限无功费率7电能脉冲数*/
#define CLQua4_Re_T8_En_Pul_0            5        /*当前4象限无功费率8电能脉冲数*/
#define CLQua4_Re_T9_En_Pul_0            5        /*当前4象限无功费率9电能脉冲数*/
#define CLQua4_Re_T10_En_Pul_0           5        /*当前4象限无功费率10电能脉冲数*/
#define CLQua4_Re_T11_En_Pul_0           5        /*当前4象限无功费率11电能脉冲数*/
#define CLQua4_Re_T12_En_Pul_0           5        /*当前4象限无功费率12电能脉冲数*/

#define CLQua4_Re_Tol_En_0               4        /*当前4象限无功总电能*/
#define CLQua4_Re_T1_En_0                4        /*当前4象限无功费率1电能*/
#define CLQua4_Re_T2_En_0                4        /*当前4象限无功费率2电能*/
#define CLQua4_Re_T3_En_0                4        /*当前4象限无功费率3电能*/
#define CLQua4_Re_T4_En_0                4        /*当前4象限无功费率4电能*/
#define CLQua4_Re_T5_En_0                4        /*当前4象限无功费率5电能*/
#define CLQua4_Re_T6_En_0                4        /*当前4象限无功费率6电能*/
#define CLQua4_Re_T7_En_0                4        /*当前4象限无功费率7电能*/
#define CLQua4_Re_T8_En_0                4        /*当前4象限无功费率8电能*/
#define CLQua4_Re_T9_En_0                4        /*当前4象限无功费率9电能*/
#define CLQua4_Re_T10_En_0               4        /*当前4象限无功费率10电能*/
#define CLQua4_Re_T11_En_0               4        /*当前4象限无功费率11电能*/
#define CLQua4_Re_T12_En_0               4        /*当前4象限无功费率12电能*/
#define CLQua4_Re_En_FF_0                52       /*当前4象限无功电能数据块*/

/*精确电能数据层存储5字节，通讯自扩为8字节*/
#define CLQua4_Re_Tol_PreEn_0            5        /*当前4象限无功总精确电能*/
#define CLQua4_Re_T1_PreEn_0             5        /*当前4象限无功费率1精确电能*/
#define CLQua4_Re_T2_PreEn_0             5        /*当前4象限无功费率2精确电能*/
#define CLQua4_Re_T3_PreEn_0             5        /*当前4象限无功费率3精确电能*/
#define CLQua4_Re_T4_PreEn_0             5        /*当前4象限无功费率4精确电能*/
#define CLQua4_Re_T5_PreEn_0             5        /*当前4象限无功费率8精确电能*/
#define CLQua4_Re_T6_PreEn_0             5        /*当前4象限无功费率6精确电能*/
#define CLQua4_Re_T7_PreEn_0             5        /*当前4象限无功费率7精确电能*/
#define CLQua4_Re_T8_PreEn_0             5        /*当前4象限无功费率8精确电能*/
#define CLQua4_Re_T9_PreEn_0             5        /*当前4象限无功费率9精确电能*/
#define CLQua4_Re_T10_PreEn_0            5        /*当前4象限无功费率10精确电能*/
#define CLQua4_Re_T11_PreEn_0            5        /*当前4象限无功费率11精确电能*/
#define CLQua4_Re_T12_PreEn_0            5        /*当前4象限无功费率12精确电能*/
#define CLQua4_Re_PreEn_FF_0             65       /*当前4象限无功精确电能数据块*/

#define CLQua4_Re_Tol_LastPulse_0        1        /*当前4象限无功总脉冲尾数*/
#define CLQua4_Re_T1_LastPulse_0         1        /*当前4象限无功费率1脉冲尾数*/
#define CLQua4_Re_T2_LastPulse_0         1        /*当前4象限无功费率2脉冲尾数*/
#define CLQua4_Re_T3_LastPulse_0         1        /*当前4象限无功费率3脉冲尾数*/
#define CLQua4_Re_T4_LastPulse_0         1        /*当前4象限无功费率4脉冲尾数*/
#define CLQua4_Re_T5_LastPulse_0         1        /*当前4象限无功费率5脉冲尾数*/
#define CLQua4_Re_T6_LastPulse_0         1        /*当前4象限无功费率6脉冲尾数*/
#define CLQua4_Re_T7_LastPulse_0         1        /*当前4象限无功费率7脉冲尾数*/
#define CLQua4_Re_T8_LastPulse_0         1        /*当前4象限无功费率8脉冲尾数*/
#define CLQua4_Re_T9_LastPulse_0         1        /*当前4象限无功费率9脉冲尾数*/
#define CLQua4_Re_T10_LastPulse_0        1        /*当前4象限无功费率10脉冲尾数*/
#define CLQua4_Re_T11_LastPulse_0        1        /*当前4象限无功费率11脉冲尾数*/
#define CLQua4_Re_T12_LastPulse_0        1        /*当前4象限无功费率12脉冲尾数*/
#define CLQua4_Re_LastPulse_FF_0         13        /*当前4象限无功脉冲尾数数据块*/

/************************当前A相电能*****************************************/
#define CLPosA_Ac_En_Pul_0               5        /*当前A相正向有功电能脉冲数*/
#define CLRevA_Ac_En_Pul_0               5        /*当前A相反向有功电能脉冲数*/
#define CLQua1A_Re_En_Pul_0              5        /*当前A相1象限无功电能脉冲数*/
#define CLQua2A_Re_En_Pul_0              5        /*当前A相2象限无功电能脉冲数*/
#define CLQua3A_Re_En_Pul_0              5        /*当前A相3象限无功电能脉冲数*/
#define CLQua4A_Re_En_Pul_0              5        /*当前A相4象限无功电能脉冲数*/

#define CLPosA_Ac_En_0                   4        /*当前A相正向有功电能*/
#define CLRevA_Ac_En_0                   4        /*当前A相反向有功电能*/
#define CLComA_Re1_En_0                  4        /*当前A相组合无功1电能*/
#define CLComA_Re2_En_0                  4        /*当前A相组合无功2电能*/
#define CLQua1A_Re_En_0                  4        /*当前A相1象限无功电能*/
#define CLQua2A_Re_En_0                  4        /*当前A相2象限无功电能*/
#define CLQua3A_Re_En_0                  4        /*当前A相3象限无功电能*/
#define CLQua4A_Re_En_0                  4        /*当前A相4象限无功电能*/

/*精确电能数据层存储5字节，通讯自扩为8字节*/
#define CLPosA_Ac_PreEn_0                5        /*当前A相正向有功精确电能*/
#define CLRevA_Ac_PreEn_0                5        /*当前A相反向有功精确电能*/
#define CLComA_Re1_PreEn_0               5        /*当前A相组合无功1精确电能*/
#define CLComA_Re2_PreEn_0               5        /*当前A相组合无功2精确电能*/
#define CLQua1A_Re_PreEn_0               5        /*当前A相1象限无功精确电能*/
#define CLQua2A_Re_PreEn_0               5        /*当前A相2象限无功精确电能*/
#define CLQua3A_Re_PreEn_0               5        /*当前A相3象限无功精确电能*/
#define CLQua4A_Re_PreEn_0               5        /*当前A相4象限无功精确电能*/

#define CLPosA_Ac_LastPulse_0            1        /*当前A相正向有功脉冲尾数*/
#define CLRevA_Ac_LastPulse_0            1        /*当前A相反向有功脉冲尾数*/
#define CLComA_Re1_LastPulse_0           1        /*当前A相组合无功1脉冲尾数*/
#define CLComA_Re2_LastPulse_0           1        /*当前A相组合无功2脉冲尾数*/
#define CLQua1A_Re_LastPulse_0           1        /*当前A相1象限无功脉冲尾数*/
#define CLQua2A_Re_LastPulse_0           1        /*当前A相2象限无功脉冲尾数*/
#define CLQua3A_Re_LastPulse_0           1        /*当前A相3象限无功脉冲尾数*/
#define CLQua4A_Re_LastPulse_0           1        /*当前A相4象限无功脉冲尾数*/

/************************当前B相电能*****************************************/
#define CLPosB_Ac_En_Pul_0               5        /*当前B相正向有功电能脉冲数*/
#define CLRevB_Ac_En_Pul_0               5        /*当前B相反向有功电能脉冲数*/
#define CLQua1B_Re_En_Pul_0              5        /*当前B相1象限无功电能脉冲数*/
#define CLQua2B_Re_En_Pul_0              5        /*当前B相2象限无功电能脉冲数*/
#define CLQua3B_Re_En_Pul_0              5        /*当前B相3象限无功电能脉冲数*/
#define CLQua4B_Re_En_Pul_0              5        /*当前B相4象限无功电能脉冲数*/

#define CLPosB_Ac_En_0                   4        /*当前B相正向有功电能*/
#define CLRevB_Ac_En_0                   4        /*当前B相反向有功电能*/
#define CLComB_Re1_En_0                  4        /*当前B相组合无功1电能*/
#define CLComB_Re2_En_0                  4        /*当前B相组合无功2电能*/
#define CLQua1B_Re_En_0                  4        /*当前B相1象限无功电能*/
#define CLQua2B_Re_En_0                  4        /*当前B相2象限无功电能*/
#define CLQua3B_Re_En_0                  4        /*当前B相3象限无功电能*/
#define CLQua4B_Re_En_0                  4        /*当前B相4象限无功电能*/

/*精确电能数据层存储5字节，通讯自扩为8字节*/
#define CLPosB_Ac_PreEn_0                5        /*当前B相正向有功精确电能*/
#define CLRevB_Ac_PreEn_0                5        /*当前B相反向有功精确电能*/
#define CLComB_Re1_PreEn_0               5        /*当前B相组合无功1精确电能*/
#define CLComB_Re2_PreEn_0               5        /*当前B相组合无功2精确电能*/
#define CLQua1B_Re_PreEn_0               5        /*当前B相1象限无功精确电能*/
#define CLQua2B_Re_PreEn_0               5        /*当前B相2象限无功精确电能*/
#define CLQua3B_Re_PreEn_0               5        /*当前B相3象限无功精确电能*/
#define CLQua4B_Re_PreEn_0               5        /*当前B相4象限无功精确电能*/

#define CLPosB_Ac_LastPulse_0            1        /*当前B相正向有功脉冲尾数*/
#define CLRevB_Ac_LastPulse_0            1        /*当前B相反向有功脉冲尾数*/
#define CLComB_Re1_LastPulse_0           1        /*当前B相组合无功1脉冲尾数*/
#define CLComB_Re2_LastPulse_0           1        /*当前B相组合无功2脉冲尾数*/
#define CLQua1B_Re_LastPulse_0           1        /*当前B相1象限无功脉冲尾数*/
#define CLQua2B_Re_LastPulse_0           1        /*当前B相2象限无功脉冲尾数*/
#define CLQua3B_Re_LastPulse_0           1        /*当前B相3象限无功脉冲尾数*/
#define CLQua4B_Re_LastPulse_0           1        /*当前B相4象限无功脉冲尾数*/

/************************当前C相电能*****************************************/
#define CLPosC_Ac_En_Pul_0               5        /*当前C相正向有功电能脉冲数*/
#define CLRevC_Ac_En_Pul_0               5        /*当前C相反向有功电能脉冲数*/
#define CLQua1C_Re_En_Pul_0              5        /*当前C相1象限无功电能脉冲数*/
#define CLQua2C_Re_En_Pul_0              5        /*当前C相2象限无功电能脉冲数*/
#define CLQua3C_Re_En_Pul_0              5        /*当前C相3象限无功电能脉冲数*/
#define CLQua4C_Re_En_Pul_0              5        /*当前C相4象限无功电能脉冲数*/

#define CLPosC_Ac_En_0                   4        /*当前C相正向有功电能*/
#define CLRevC_Ac_En_0                   4        /*当前C相反向有功电能*/
#define CLComC_Re1_En_0                  4        /*当前C相组合无功1电能*/
#define CLComC_Re2_En_0                  4        /*当前C相组合无功2电能*/
#define CLQua1C_Re_En_0                  4        /*当前C相1象限无功电能*/
#define CLQua2C_Re_En_0                  4        /*当前C相2象限无功电能*/
#define CLQua3C_Re_En_0                  4        /*当前C相3象限无功电能*/
#define CLQua4C_Re_En_0                  4        /*当前C相4象限无功电能*/

/*精确电能数据层存储5字节，通讯自扩为8字节*/
#define CLPosC_Ac_PreEn_0                5        /*当前C相正向有功精确电能*/
#define CLRevC_Ac_PreEn_0                5        /*当前C相反向有功精确电能*/
#define CLComC_Re1_PreEn_0               5        /*当前C相组合无功1精确电能*/
#define CLComC_Re2_PreEn_0               5        /*当前C相组合无功2精确电能*/
#define CLQua1C_Re_PreEn_0               5        /*当前C相1象限无功精确电能*/
#define CLQua2C_Re_PreEn_0               5        /*当前C相2象限无功精确电能*/
#define CLQua3C_Re_PreEn_0               5        /*当前C相3象限无功精确电能*/
#define CLQua4C_Re_PreEn_0               5        /*当前C相4象限无功精确电能*/

#define CLPosC_Ac_LastPulse_0            1        /*当前C相正向有功脉冲尾数*/
#define CLRevC_Ac_LastPulse_0            1        /*当前C相反向有功脉冲尾数*/
#define CLComC_Re1_LastPulse_0           1        /*当前C相组合无功1脉冲尾数*/
#define CLComC_Re2_LastPulse_0           1        /*当前C相组合无功2脉冲尾数*/
#define CLQua1C_Re_LastPulse_0           1        /*当前C相1象限无功脉冲尾数*/
#define CLQua2C_Re_LastPulse_0           1        /*当前C相2象限无功脉冲尾数*/
#define CLQua3C_Re_LastPulse_0           1        /*当前C相3象限无功脉冲尾数*/
#define CLQua4C_Re_LastPulse_0           1        /*当前C相4象限无功脉冲尾数*/

/*********************************需量*****************************************/
#define CLPos_Ac_Tol_De_0        11     /*当前正向有功总最大需量及发生时刻*/
#define CLPos_Ac_T1_De_0         11     /*当前正向有功费率1最大需量及发生时刻*/
#define CLPos_Ac_T2_De_0         11     /*当前正向有功费率2最大需量及发生时刻*/
#define CLPos_Ac_T3_De_0         11     /*当前正向有功费率3最大需量及发生时刻*/
#define CLPos_Ac_T4_De_0         11     /*当前正向有功费率4最大需量及发生时刻*/
#define CLPos_Ac_T5_De_0         11     /*当前正向有功费率5最大需量及发生时刻*/
#define CLPos_Ac_T6_De_0         11     /*当前正向有功费率6最大需量及发生时刻*/
#define CLPos_Ac_T7_De_0         11     /*当前正向有功费率7最大需量及发生时刻*/
#define CLPos_Ac_T8_De_0         11     /*当前正向有功费率11最大需量及发生时刻*/
#define CLPos_Ac_T9_De_0         11     /*当前正向有功费率9最大需量及发生时刻*/
#define CLPos_Ac_T10_De_0        11     /*当前正向有功费率10最大需量及发生时刻*/
#define CLPos_Ac_T11_De_0        11     /*当前正向有功费率11最大需量及发生时刻*/
#define CLPos_Ac_T12_De_0        11     /*当前正向有功费率12最大需量及发生时刻*/
#define CLPos_Ac_De_FF_0         143    /*当前正向有功最大需量及发生时刻数据块12费率*/

#define CLRev_Ac_Tol_De_0        11     /*当前反向有功总最大需量及发生时刻*/
#define CLRev_Ac_T1_De_0         11     /*当前反向有功费率1最大需量及发生时刻*/
#define CLRev_Ac_T2_De_0         11     /*当前反向有功费率2最大需量及发生时刻*/
#define CLRev_Ac_T3_De_0         11     /*当前反向有功费率3最大需量及发生时刻*/
#define CLRev_Ac_T4_De_0         11     /*当前反向有功费率4最大需量及发生时刻*/
#define CLRev_Ac_T5_De_0         11     /*当前反向有功费率5最大需量及发生时刻*/
#define CLRev_Ac_T6_De_0         11     /*当前反向有功费率6最大需量及发生时刻*/
#define CLRev_Ac_T7_De_0         11     /*当前反向有功费率7最大需量及发生时刻*/
#define CLRev_Ac_T8_De_0         11     /*当前反向有功费率11最大需量及发生时刻*/
#define CLRev_Ac_T9_De_0         11     /*当前反向有功费率9最大需量及发生时刻*/
#define CLRev_Ac_T10_De_0        11     /*当前反向有功费率10最大需量及发生时刻*/
#define CLRev_Ac_T11_De_0        11     /*当前反向有功费率11最大需量及发生时刻*/
#define CLRev_Ac_T12_De_0        11     /*当前反向有功费率12最大需量及发生时刻*/
#define CLRev_Ac_De_FF_0         143    /*当前反向有功最大需量及发生时刻数据块*/

#define CLCom_Re1_Tol_De_0       11     /*当前组合无功1总最大需量及发生时刻*/
#define CLCom_Re1_T1_De_0        11     /*当前组合无功1费率1最大需量及发生时刻*/
#define CLCom_Re1_T2_De_0        11     /*当前组合无功1费率2最大需量及发生时刻*/
#define CLCom_Re1_T3_De_0        11     /*当前组合无功1费率3最大需量及发生时刻*/
#define CLCom_Re1_T4_De_0        11     /*当前组合无功1费率4最大需量及发生时刻*/
#define CLCom_Re1_T5_De_0        11     /*当前组合无功1费率5最大需量及发生时刻*/
#define CLCom_Re1_T6_De_0        11     /*当前组合无功1费率6最大需量及发生时刻*/
#define CLCom_Re1_T7_De_0        11     /*当前组合无功1费率7最大需量及发生时刻*/
#define CLCom_Re1_T8_De_0        11     /*当前组合无功1费率11最大需量及发生时刻*/
#define CLCom_Re1_T9_De_0        11     /*当前组合无功1费率9最大需量及发生时刻*/
#define CLCom_Re1_T10_De_0       11     /*当前组合无功1费率10最大需量及发生时刻*/
#define CLCom_Re1_T11_De_0       11     /*当前组合无功1费率11最大需量及发生时刻*/
#define CLCom_Re1_T12_De_0       11     /*当前组合无功1费率12最大需量及发生时刻*/
#define CLCom_Re1_De_FF_0        143    /*当前组合无功1最大需量及发生时刻数据块*/

#define CLCom_Re2_Tol_De_0       11     /*当前组合无功2总最大需量及发生时刻*/
#define CLCom_Re2_T1_De_0        11     /*当前组合无功2费率1最大需量及发生时刻*/
#define CLCom_Re2_T2_De_0        11     /*当前组合无功2费率2最大需量及发生时刻*/
#define CLCom_Re2_T3_De_0        11     /*当前组合无功2费率3最大需量及发生时刻*/
#define CLCom_Re2_T4_De_0        11     /*当前组合无功2费率4最大需量及发生时刻*/
#define CLCom_Re2_T5_De_0        11     /*当前组合无功2费率5最大需量及发生时刻*/
#define CLCom_Re2_T6_De_0        11     /*当前组合无功2费率6最大需量及发生时刻*/
#define CLCom_Re2_T7_De_0        11     /*当前组合无功2费率7最大需量及发生时刻*/
#define CLCom_Re2_T8_De_0        11     /*当前组合无功2费率8最大需量及发生时刻*/
#define CLCom_Re2_T9_De_0        11     /*当前组合无功2费率9最大需量及发生时刻*/
#define CLCom_Re2_T10_De_0       11     /*当前组合无功2费率10最大需量及发生时刻*/
#define CLCom_Re2_T11_De_0       11     /*当前组合无功2费率11最大需量及发生时刻*/
#define CLCom_Re2_T12_De_0       11     /*当前组合无功2费率12最大需量及发生时刻*/
#define CLCom_Re2_De_FF_0        143    /*当前组合无功2最大需量及发生时刻数据块*/

#define CLQua1_Re_Tol_De_0       11     /*当前1象限无功总最大需量及发生时刻*/
#define CLQua1_Re_T1_De_0        11     /*当前1象限无功费率1最大需量及发生时刻*/
#define CLQua1_Re_T2_De_0        11     /*当前1象限无功费率2最大需量及发生时刻*/
#define CLQua1_Re_T3_De_0        11     /*当前1象限无功费率3最大需量及发生时刻*/
#define CLQua1_Re_T4_De_0        11     /*当前1象限无功费率4最大需量及发生时刻*/
#define CLQua1_Re_T5_De_0        11     /*当前1象限无功费率5最大需量及发生时刻*/
#define CLQua1_Re_T6_De_0        11     /*当前1象限无功费率6最大需量及发生时刻*/
#define CLQua1_Re_T7_De_0        11     /*当前1象限无功费率7最大需量及发生时刻*/
#define CLQua1_Re_T8_De_0        11     /*当前1象限无功费率8最大需量及发生时刻*/
#define CLQua1_Re_T9_De_0        11     /*当前1象限无功费率9最大需量及发生时刻*/
#define CLQua1_Re_T10_De_0       11     /*当前1象限无功费率10最大需量及发生时刻*/
#define CLQua1_Re_T11_De_0       11     /*当前1象限无功费率11最大需量及发生时刻*/
#define CLQua1_Re_T12_De_0       11     /*当前1象限无功费率12最大需量及发生时刻*/
#define CLQua1_Re_De_FF_0        143    /*当前1象限无功最大需量及发生时刻数据块*/

#define CLQua2_Re_Tol_De_0       11     /*当前2象限无功总最大需量及发生时刻*/
#define CLQua2_Re_T1_De_0        11     /*当前2象限无功费率1最大需量及发生时刻*/
#define CLQua2_Re_T2_De_0        11     /*当前2象限无功费率2最大需量及发生时刻*/
#define CLQua2_Re_T3_De_0        11     /*当前2象限无功费率3最大需量及发生时刻*/
#define CLQua2_Re_T4_De_0        11     /*当前2象限无功费率4最大需量及发生时刻*/
#define CLQua2_Re_T5_De_0        11     /*当前2象限无功费率5最大需量及发生时刻*/
#define CLQua2_Re_T6_De_0        11     /*当前2象限无功费率6最大需量及发生时刻*/
#define CLQua2_Re_T7_De_0        11     /*当前2象限无功费率7最大需量及发生时刻*/
#define CLQua2_Re_T8_De_0        11     /*当前2象限无功费率8最大需量及发生时刻*/
#define CLQua2_Re_T9_De_0        11     /*当前2象限无功费率9最大需量及发生时刻*/
#define CLQua2_Re_T10_De_0       11     /*当前2象限无功费率10最大需量及发生时刻*/
#define CLQua2_Re_T11_De_0       11     /*当前2象限无功费率11最大需量及发生时刻*/
#define CLQua2_Re_T12_De_0       11     /*当前2象限无功费率12最大需量及发生时刻*/
#define CLQua2_Re_De_FF_0        143    /*当前2象限无功最大需量及发生时刻数据块*/

#define CLQua3_Re_Tol_De_0       11     /*当前3象限无功总最大需量及发生时刻*/
#define CLQua3_Re_T1_De_0        11     /*当前3象限无功费率1最大需量及发生时刻*/
#define CLQua3_Re_T2_De_0        11     /*当前3象限无功费率2最大需量及发生时刻*/
#define CLQua3_Re_T3_De_0        11     /*当前3象限无功费率3最大需量及发生时刻*/
#define CLQua3_Re_T4_De_0        11     /*当前3象限无功费率4最大需量及发生时刻*/
#define CLQua3_Re_T5_De_0        11     /*当前3象限无功费率5最大需量及发生时刻*/
#define CLQua3_Re_T6_De_0        11     /*当前3象限无功费率6最大需量及发生时刻*/
#define CLQua3_Re_T7_De_0        11     /*当前3象限无功费率7最大需量及发生时刻*/
#define CLQua3_Re_T8_De_0        11     /*当前3象限无功费率8最大需量及发生时刻*/
#define CLQua3_Re_T9_De_0        11     /*当前3象限无功费率9最大需量及发生时刻*/
#define CLQua3_Re_T10_De_0       11     /*当前3象限无功费率10最大需量及发生时刻*/
#define CLQua3_Re_T11_De_0       11     /*当前3象限无功费率11最大需量及发生时刻*/
#define CLQua3_Re_T12_De_0       11     /*当前3象限无功费率12最大需量及发生时刻*/
#define CLQua3_Re_De_FF_0        143    /*当前3象限无功最大需量及发生时刻数据块*/

#define CLQua4_Re_Tol_De_0       11     /*当前4象限无功总最大需量及发生时刻*/
#define CLQua4_Re_T1_De_0        11     /*当前4象限无功费率1最大需量及发生时刻*/
#define CLQua4_Re_T2_De_0        11     /*当前4象限无功费率2最大需量及发生时刻*/
#define CLQua4_Re_T3_De_0        11     /*当前4象限无功费率3最大需量及发生时刻*/
#define CLQua4_Re_T4_De_0        11     /*当前4象限无功费率4最大需量及发生时刻*/
#define CLQua4_Re_T5_De_0        11     /*当前4象限无功费率5最大需量及发生时刻*/
#define CLQua4_Re_T6_De_0        11     /*当前4象限无功费率6最大需量及发生时刻*/
#define CLQua4_Re_T7_De_0        11     /*当前4象限无功费率7最大需量及发生时刻*/
#define CLQua4_Re_T8_De_0        11     /*当前4象限无功费率8最大需量及发生时刻*/
#define CLQua4_Re_T9_De_0        11     /*当前4象限无功费率9最大需量及发生时刻*/
#define CLQua4_Re_T10_De_0       11     /*当前4象限无功费率10最大需量及发生时刻*/
#define CLQua4_Re_T11_De_0       11     /*当前4象限无功费率11最大需量及发生时刻*/
#define CLQua4_Re_T12_De_0       11     /*当前4象限无功费率12最大需量及发生时刻*/
#define CLQua4_Re_De_FF_0        143    /*当前4象限无功最大需量及发生时刻数据块*/

#define CLPosA_Ac_De_0           11     /*当前A相正向有功最大需量及发生时刻*/
#define CLRevA_Ac_De_0           11     /*当前A相反向有功最大需量及发生时刻*/
#define CLComA_Re1_De_0          11     /*当前A相组合无功1最大需量及发生时刻*/
#define CLComA_Re2_De_0          11     /*当前A相组合无功2最大需量及发生时刻*/
#define CLQua1A_Re_De_0          11     /*当前A相1象限无功最大需量及发生时刻*/
#define CLQua2A_Re_De_0          11     /*当前A相2象限无功最大需量及发生时刻*/
#define CLQua3A_Re_De_0          11     /*当前A相3象限无功最大需量及发生时刻*/
#define CLQua4A_Re_De_0          11     /*当前A相4象限无功最大需量及发生时刻*/

#define CLPosB_Ac_De_0           11     /*当前B相正向有功最大需量及发生时刻*/
#define CLRevB_Ac_De_0           11     /*当前B相反向有功最大需量及发生时刻*/
#define CLComB_Re1_De_0          11     /*当前B相组合无功1最大需量及发生时刻*/
#define CLComB_Re2_De_0          11     /*当前B相组合无功2最大需量及发生时刻*/
#define CLQua1B_Re_De_0          11     /*当前B相1象限无功最大需量及发生时刻*/
#define CLQua2B_Re_De_0          11     /*当前B相2象限无功最大需量及发生时刻*/
#define CLQua3B_Re_De_0          11     /*当前B相3象限无功最大需量及发生时刻*/
#define CLQua4B_Re_De_0          11     /*当前B相4象限无功最大需量及发生时刻*/

#define CLPosC_Ac_De_0           11     /*当前C相正向有功最大需量及发生时刻*/
#define CLRevC_Ac_De_0           11     /*当前C相反向有功最大需量及发生时刻*/
#define CLComC_Re1_De_0          11     /*当前C相组合无功1最大需量及发生时刻*/
#define CLComC_Re2_De_0          11     /*当前C相组合无功2最大需量及发生时刻*/
#define CLQua1C_Re_De_0          11     /*当前C相1象限无功最大需量及发生时刻*/
#define CLQua2C_Re_De_0          11     /*当前C相2象限无功最大需量及发生时刻*/
#define CLQua3C_Re_De_0          11     /*当前C相3象限无功最大需量及发生时刻*/
#define CLQua4C_Re_De_0          11     /*当前C相4象限无功最大需量及发生时刻*/

/*********************************变量类**********************************************/
#define	CLPhaseA_Volage                  2              /*A相电压*/
#define	CLPhaseB_Volage                  2              /*B相电压*/
#define	CLPhaseC_Volage                  2              /*C相电压*/
#define	CLPhaseFF_Volage                 6              /*电压数据块*/

#define	CLPhaseA_Curr                    4              /*A相电流*/
#define	CLPhaseB_Curr                    4              /*B相电流*/
#define	CLPhaseC_Curr                    4              /*C相电流*/
#define	CLPhaseFF_Curr                   12             /*电流数据块*/

#define	CLVector_Current                 4              /*三相电流矢量和*/
#define	CLZero_Current                   4              /*零线电流*/

#define	CLPhaseA_Curr_4Dig               4              /*A相电流,4位小数*/
#define	CLPhaseB_Curr_4Dig               4              /*B相电流,4位小数*/
#define	CLPhaseC_Curr_4Dig               4              /*C相电流,4位小数*/
#define	CLPhaseFF_Curr_4Dig              12             /*电流数据块*/

#define	CLVolA_Phase                     2              /*A相电压相角*/
#define	CLVolB_Phase                     2              /*B相电压相角*/
#define	CLVolC_Phase                     2              /*C相电压流相角*/
#define	CLVolFF_Phase                    6              /*电压相角数据块*/

#define	CLCurrA_Phase                    2              /*A相电流相角*/
#define	CLCurrB_Phase                    2              /*B相电流相角*/
#define	CLCurrC_Phase                    2              /*C相电流相角*/
#define	CLCurrFF_Phase                   6              /*电流相角数据块*/

#define	CLPhaseA_Angle                   2              /*A相相角*/
#define	CLPhaseB_Angle                   2              /*B相相角*/
#define	CLPhaseC_Angle                   2              /*C相相角*/
#define	CLPhaseFF_Angle                  6              /*相角数据块*/

#define	CLInstant_TolAcPow               4              /*瞬时总有功功率*/
#define	CLInstantA_AcPow                 4              /*A相瞬时有功功率*/
#define	CLInstantB_AcPow                 4              /*B相瞬时有功功率*/
#define	CLInstantC_AcPow                 4              /*C相瞬时有功功率*/
#define	CLInstantFF_AcPow                16             /*瞬时有功功率数据块*/

#define	CLInstant_TolRePow               4              /*瞬时总无功功率*/
#define	CLInstantA_RePow                 4              /*A相瞬时无功功率*/
#define	CLInstantB_RePow                 4              /*B相瞬时无功功率*/
#define	CLInstantC_RePow                 4              /*C相瞬时无功功率*/
#define	CLInstantFF_RePow                16             /*瞬时无功功率数据块*/

#define	CLInstant_TolAppaPow             4              /*瞬时总视在功率*/
#define	CLInstantA_AppaPow               4              /*A相瞬时视在功率*/
#define	CLInstantB_AppaPow               4              /*B相瞬时视在功率*/
#define	CLInstantC_AppaPow               4              /*C相瞬时视在功率*/
#define	CLInstantFF_AppaPow              16             /*瞬时视在功率数据块*/

#define	CLTol_PowerFactor                2              /*总功率因数*/
#define	CLPhaseA_PowerFactor             2              /*A相功率因数*/
#define	CLPhaseB_PowerFactor             2              /*B相功率因数*/
#define	CLPhaseC_PowerFactor             2              /*C相功率因数*/
#define	CLPhaseFF_PowerFactor            8              /*功率因数数据块*/

#define	CLOneMin_AcPower                 4              /*1分钟有功总平均功率*/
#define	CLOneMin_AcPower_A               4              /*1分钟有功总平均功率A*/
#define	CLOneMin_AcPower_B               4              /*1分钟有功总平均功率B*/
#define	CLOneMin_AcPower_C               4              /*1分钟有功总平均功率C*/
#define	CLOneMin_AcPower_FF              16             /*1分钟有功平均功率数据块*/

#define	CLOneMin_RePower                 4              /*1分钟无功总平均功率*/
#define	CLOneMin_RePower_A               4              /*1分钟无功总平均功率A*/
#define	CLOneMin_RePower_B               4              /*1分钟无功总平均功率B*/
#define	CLOneMin_RePower_C               4              /*1分钟无功总平均功率C*/
#define	CLOneMin_RePower_FF              16             /*1分钟无功平均功率数据块*/

#define	CLCurr_AcDemand                  4              /*当前有功需量*/
#define	CLCurr_ReDemand                  4              /*当前无功需量*/
#define	CLCurr_AppaDemand                4              /*当前视在需量*/

#define	CLElecNet_Freq                   2              /*电网频率*/
#define	CLMeter_Temp                     2              /*表内温度*/
#define	CLCloc_Batt_Vol                  2              /*时钟电池电压*/
#define	CLReadMeter_Batt_Vol             2              /*抄表电池电压*/
#define	CLBatt_Work_Time                 4              /*时钟电池工作时间*/

#define CLMeter_Work_State1              2              /*电表运行状态字1*/
#define CLMeter_Work_State2              2              /*电表运行状态字2*/
#define CLMeter_Work_State3              2              /*电表运行状态字3*/
#define CLMeter_Work_State4              2              /*电表运行状态字4*/
#define CLMeter_Work_State5              2              /*电表运行状态字5*/
#define CLMeter_Work_State6              2              /*电表运行状态字6*/
#define CLMeter_Work_State7              2              /*电表运行状态字7*/
#define CLMeter_Work_StateFF             14             /*电表运行状态字1-7*/

#define	CLControl_ExecuteState           2              /*控制命令执行状态字*/
#define	CLControl_ErrorState             2              /*控制命令错误状态字*/

#define	CLCurr_Price                     4              /*当前电价*/
#define	CLCurr_Rate_Price                4              /*当前费率电价*/
#define	CLCurr_Ladder_Price              4              /*当前阶梯电价*/

#define CLChargeBal_BCD                  4              /*当前剩余金额BCD格式*/
#define CLOverDraft_BCD                  4              /*当前透支金额BCD格式*/
#define CLBuyCurr_TMoney                 4              /*累计购电金额*/
#define CLChargeBal_Hex_Cent             4              /*当前剩余金额,单位为分*/
#define CLOverDraft_Hex_Cent             4              /*当前透支金额,单位为分*/
#define CLChargeBal_Hex_Full             5              /*当前剩余金额,电能模块充值时*/
#define CLOverDraft_Hex_Full             5              /*当前透支金额,电能模块充值时*/
#define CLChargeBal_Hex_Deal             5              /*当前剩余金额,电能处理模块*/
#define CLOverDraft_Hex_Deal             5              /*当前透支金额,电能处理模块*/

#define CLSC_Com_Ac_Tol_En_0             4              /*当前结算周期内组合有功总累计用电量*/
#define CLSC_Com_Ac_Tol_En_Pul_0         5              /*当前结算周期内组合有功总累计用电量-脉冲数格式*/
#define CLSC_Com_Ac_Tol_En_Pul_0_Sett    5              /*当前结算周期内组合有功总累计用电量-脉冲数格式,电能结算，清当前结算电能RAM、E2用*/

#define CLSC_Com_Ac_Tol_En_1             4              /*上1结算周期内组合有功总累计用电量*/
#define CLSC_Pos_Ac_Tol_En_Pul_1         5              /*上1结算周期内正向有功总电量-脉冲数格式*/
#define CLSC_Rev_Ac_Tol_En_Pul_1         5              /*上1结算周期内反向有功总电量-脉冲数格式*/

#define CLM_Com_Ac_Tol_En_0              4              /*当前月度组合有功总累计用电量*/
#define CLM_Com_Ac_Tol_En_Pul_0          5              /*当前月度组合有功总累计用电量-脉冲数格式*/
#define CLM_Com_Ac_Tol_En_Pul_0_Sett     5              /*当前月度组合有功总累计用电量-脉冲数格式,电能结算，清当前结算电能RAM、E2用*/

#define CLM_Com_Ac_Tol_En_1              4              /*上1月度组合有功总累计用电量*/
#define CLM_Pos_Ac_Tol_En_Pul_1          5              /*上1月度正向有功累计电量-脉冲数格式*/
#define CLM_Rev_Ac_Tol_En_Pul_1          5              /*上1月度反向有功累计电量-脉冲数格式*/

#define CLY_Com_Ac_Tol_En_0              4              /*阶梯结算用电量*/
#define CLY_Com_Ac_Tol_En_Pul_0          5              /*阶梯结算用电量-脉冲数格式*/
#define CLY_Com_Ac_Tol_En_Pul_0_Sett     5              /*阶梯结算用电量-脉冲数格式,电能结算，清当前结算电能RAM、E2用*/

#define CLY_Com_Ac_Tol_En_1              8              /*上1次年结算日结算时间及上1年结算周期组合有功总累计用电量*/
#define CLY_Com_Ac_Tol_En_2              8              /*上2次年结算日结算时间及上2年结算周期组合有功总累计用电量*/
#define CLY_Com_Ac_Tol_En_3              8              /*上3次年结算日结算时间及上3年结算周期组合有功总累计用电量*/
#define CLY_Com_Ac_Tol_En_4              8              /*上4次年结算日结算时间及上4年结算周期组合有功总累计用电量*/
#define CLY_Com_Ac_En_FF                 32             /*上1--4次年结算日结算时间及上1--4年结算周期组合有功总累计用电量*/

/****************************电压合格率*******************************/
#if 1
#define	CLPer_Pass_MonitorTime			4				/*电压监测时间长度*//*zlj之前是3，改成4*/
#define	CLPer_Pass_PassRate				2				/*电压合格率长度*/
#define	CLPer_Pass_OverRate				2				/*电压超限率长度*/
#define	CLPer_Pass_OverUpTime			4				/*电压超上限时间长度*/
#define	CLPer_Pass_OverLowTime			4				/*电压超下限时间长度*/

#define	CLVolA_Per_Pass_D				16				/*A相日电压合格率统计数据*/
#define	CLVolA_Per_Pass_M				16				/*A相月电压合格率统计数据*/
#define	CLVolA_Per_Pass_FF				32				/*A相电压合格率统计数据块*/

#define	CLVolB_Per_Pass_D				16				/*B相日电压合格率统计数据*/
#define	CLVolB_Per_Pass_M				16				/*B相月电压合格率统计数据*/
#define	CLVolB_Per_Pass_FF				32				/*B相电压合格率统计数据块*/

#define	CLVolC_Per_Pass_D				16				/*C相日电压合格率统计数据*/
#define	CLVolC_Per_Pass_M				16				/*C相月电压合格率统计数据*/
#define	CLVolC_Per_Pass_FF				32				/*C相电压合格率统计数据块*/

#define	CLVol_Per_Pass_D				48				/*日电压合格率统计数据*/
#define	CLVol_Per_Pass_M				48				/*月电压合格率统计数据*/

#define	CLVol_PassTime_D				3				/*日电压合格时间长度*/
#define	CLVol_PassTime_M				3				/*月电压合格时间长度*/

#define	CLCurrMon_Vol_Pass_Time			3				/*本月总电压合格时间*/
#endif

/*645冻结相关定义*/
/******************************负荷曲线******************************/
#define CLVoltageA_Load                   2         /*负荷中A相电压*/
#define CLVoltageB_Load                   2         /*负荷中B相电压*/
#define CLVoltageC_Load                   2         /*负荷中C相电压*/
#define CLVoltageBlock_Load               6         /*电压曲线数据块*/
#define CLCurrentA_Load                   3         /*负荷中A相电流*/
#define CLCurrentB_Load                   3         /*负荷中B相电流*/
#define CLCurrentC_Load                   3         /*负荷中C相电流*/
#define CLCurrentBlock_Load               9         /*电流曲线数据块*/
#define CLActPowerT_Load                  3         /*负荷中总有功功率*/
#define CLActPowerA_Load                  3         /*负荷中A相有功功率*/
#define CLActPowerB_Load                  3         /*负荷中B相有功功率*/
#define CLActPowerC_Load                  3         /*负荷中C相有功功率*/
#define CLActPowerBlock_Load              12        /*有功功率曲线数据块*/
#define CLReActPowerT_Load                3         /*负荷中总无功功率*/
#define CLReActPowerA_Load                3         /*负荷中A相无功功率*/
#define CLReActPowerB_Load                3         /*负荷中B相无功功率*/
#define CLReActPowerC_Load                3         /*负荷中C相无功功率*/
#define CLReActPowerBlock_Load            12        /*无功功率曲线数据块*/
#define CLPowFactorT_Load                 2         /*负荷中总功率因素*/
#define CLPowFactorA_Load                 2         /*负荷中A相功率因素*/
#define CLPowFactorB_Load                 2         /*负荷中B相功率因素*/
#define CLPowFactorC_Load                 2         /*负荷中C相功率因素*/
#define CLPowFactorBlock_Load             8         /*功率因素曲线数据块*/
#define CLPosActEnergyT_Load              4         /*负荷中正向有功总电能*/
#define CLRevActEnergyT_Load              4         /*负荷中反向有功总电能*/
#define CLComReAct1T_Load                 4         /*负荷中组合无功1总电能*/
#define CLComReAct2T_Load                 4         /*负荷中组合无功2总电能*/
#define CLTotEnergyBlock_Load             16        /*有无功总电能曲线数据块*/
#define CLReActQuad1_Load                 4         /*负荷中1象限无功电能*/
#define CLReActQuad2_Load                 4         /*负荷中2象限无功电能*/
#define CLReActQuad3_Load                 4         /*负荷中3象限无功电能*/
#define CLReActQuad4_Load                 4         /*负荷中4象限无功电能*/
#define CLReActQuadTBlock_Load            16        /*4象限无功电能曲线数据块*/
#define CLActDemand_Load                  3         /*负荷中当前有功需量*/
#define CLReActDemand_Load                3         /*负荷中当前无功需量*/
#define CLDemandBlock_Load                6         /*当前需量曲线数据块*/
#define CLengthRec1_Load                  17        /*第1类负荷记录单块数据长度*/
#define CLengthRec2_Load                  24        /*第2类负荷记录单块数据长度*/
#define CLengthRec3_Load                  8         /*第3类负荷记录单块数据长度*/
#define CLengthRec4_Load                  16        /*第4类负荷记录单块数据长度*/
#define CLengthRec5_Load                  16        /*第5类负荷记录单块数据长度*/
#define CLengthRec6_Load                  6         /*第6类负荷记录单块数据长度*/

/*****************************整点冻结****************************************/
/*上2次-上254次整点冻结未定义*/
#define CLH_Free_Time_1           5         /*上1次整点冻结时间*/
#define CLH_Free_Pos_Ac_TolEn_1   4         /*上1次整点冻结正向有功总电能数据*/
#define CLH_Free_Rev_Ac_En_1      4         /*上1次整点冻结反向有功总电能数据*/
#define CLH_Free_FF_1             13        /*上1次整点冻结数据块*/

/*****************************日冻结****************************************/
/*上2次-上62次日冻结未定义*/
#define CLD_Free_Time_1           5        /*上1次日冻结时间*/
#define CLD_Free_Pos_Ac_En_1      20       /*上1次日冻结正向有功电能数据*/
#define CLD_Free_Rev_Ac_En_1      20       /*上1次日冻结反向有功电能数据*/
#define CLD_Free_Com_Re1_En_1     20       /*上1次日冻结组合无功1电能数据*/
#define CLD_Free_Com_Re2_En_1     20       /*上1次日冻结组合无功2电能数据*/
#define CLD_Free_Qua1_Re_En_1     20       /*上1次日冻结1象限无功电能数据*/
#define CLD_Free_Qua2_Re_En_1     20       /*上1次日冻结2象限无功电能数据*/
#define CLD_Free_Qua3_Re_En_1     20       /*上1次日冻结3象限无功电能数据*/
#define CLD_Free_Qua4_Re_En_1     20       /*上1次日冻结4象限无功电能数据*/
#define CLD_Free_Pos_Ac_De_1      40       /*上1次日冻结正向有功最大需量及发生时刻数据*/
#define CLD_Free_Rev_Ac_De_1      40       /*上1次日冻结反向有功最大需量及发生时刻数据*/
#define CLD_Free_Variable_1       24       /*上1次日冻结变量数据*/
#define CLD_Free_TVolRate_1       27       /*上1次日冻结T电压合格率数据*/
#define CLD_Free_AVolRate_1       27       /*上1次日冻结A电压合格率数据*/
#define CLD_Free_BVolRate_1       27       /*上1次日冻结B电压合格率数据*/
#define CLD_Free_CVolRate_1       27       /*上1次日冻结C电压合格率数据*/
#define CLD_Free_FF_1             377      /*上1次日冻结数据块*/

/***************************两套时区表切换冻结*********************************/
/*上2次时区表切换冻结数据长度同上1次*/
#define CLTZ_Free_Time_1          5        /*2套时区表切换约定时间*/
#define CLTZ_Free_Pos_Ac_En_1     20       /*上1次2套时区表切换约定冻结正向有功电能数据*/
#define CLTZ_Free_Rev_Ac_En_1     20       /*上1次2套时区表切换约定冻结反向有功电能数据*/
#define CLTZ_Free_Com_Re1_En_1    20       /*上1次2套时区表切换约定冻结组合无功1电能数据*/
#define CLTZ_Free_Com_Re2_En_1    20       /*上1次2套时区表切换约定冻结组合无功2电能数据*/
#define CLTZ_Free_Qua1_Re_En_1    20       /*上1次2套时区表切换约定冻结1象限无功电能数据*/
#define CLTZ_Free_Qua2_Re_En_1    20       /*上1次2套时区表切换约定冻结2象限无功电能数据*/
#define CLTZ_Free_Qua3_Re_En_1    20       /*上1次2套时区表切换约定冻结3象限无功电能数据*/
#define CLTZ_Free_Qua4_Re_En_1    20       /*上1次2套时区表切换约定冻结4象限无功电能数据*/
#define CLTZ_Free_Pos_Ac_De_1     40       /*上1次2套时区表切换约定冻结正向有功最大需量及发生时刻数据*/
#define CLTZ_Free_Rev_Ac_De_1     40       /*上1次2套时区表切换约定冻结反向有功最大需量及发生时刻数据*/
#define CLTZ_Free_Variable_1      24       /*上1次2套时区表切换约定冻结变量数据*/
#define CLTZ_Free_FF_1            269      /*上1次2套时区表切换约定冻结数据块*/

/***************************两套时段表切换冻结*********************************/
/*上2次时段表切换冻结数据长度同上1次*/
#define CLPT_Free_Time_1          5          /*2套日时段表切换约定时间*/
#define CLPT_Free_Pos_Ac_En_1     20         /*上1次2套日时段表切换约定冻结正向有功电能数据*/
#define CLPT_Free_Rev_Ac_En_1     20         /*上1次2套日时段表切换约定冻结反向有功电能数据*/
#define CLPT_Free_Com_Re1_En_1    20         /*上1次2套日时段表切换约定冻结组合无功1电能数据*/
#define CLPT_Free_Com_Re2_En_1    20         /*上1次2套日时段表切换约定冻结组合无功2电能数据*/
#define CLPT_Free_Qua1_Re_En_1    20         /*上1次2套日时段表切换约定冻结1象限无功电能数据*/
#define CLPT_Free_Qua2_Re_En_1    20         /*上1次2套日时段表切换约定冻结2象限无功电能数据*/
#define CLPT_Free_Qua3_Re_En_1    20         /*上1次2套日时段表切换约定冻结3象限无功电能数据*/
#define CLPT_Free_Qua4_Re_En_1    20         /*上1次2套日时段表切换约定冻结4象限无功电能数据*/
#define CLPT_Free_Pos_Ac_De_1     40         /*上1次2套日时段表切换约定冻结正向有功最大需量及发生时刻数据*/
#define CLPT_Free_Rev_Ac_De_1     40         /*上1次2套日时段表切换约定冻结反向有功最大需量及发生时刻数据*/
#define CLPT_Free_Variable_1      24         /*上1次2套日时段表切换约定冻结变量数据*/
#define CLPT_Free_FF_1            269        /*上1次2套日时段表切换约定冻结数据块*/

/***************************两套费率电价切换冻结*********************************/
/*上2次费率电价切换冻结数据长度同上1次*/
#define CLR_Free_Time_1           5          /*2套费率电价切换约定时间*/
#define CLR_Free_Pos_Ac_En_1      20         /*上1次2套费率电价切换约定冻结正向有功电能数据*/
#define CLR_Free_Rev_Ac_En_1      20         /*上1次2套费率电价切换约定冻结反向有功电能数据*/
#define CLR_Free_Com_Re1_En_1     20         /*上1次2套费率电价切换约定冻结组合无功1电能数据*/
#define CLR_Free_Com_Re2_En_1     20         /*上1次2套费率电价切换约定冻结组合无功2电能数据*/
#define CLR_Free_Qua1_Re_En_1     20         /*上1次2套费率电价切换约定冻结1象限无功电能数据*/
#define CLR_Free_Qua2_Re_En_1     20         /*上1次2套费率电价切换约定冻结2象限无功电能数据*/
#define CLR_Free_Qua3_Re_En_1     20         /*上1次2套费率电价切换约定冻结3象限无功电能数据*/
#define CLR_Free_Qua4_Re_En_1     20         /*上1次2套费率电价切换约定冻结4象限无功电能数据*/
#define CLR_Free_Pos_Ac_De_1      40         /*上1次2套费率电价切换约定冻结正向有功最大需量及发生时刻数据*/
#define CLR_Free_Rev_Ac_De_1      40         /*上1次2套费率电价切换约定冻结反向有功最大需量及发生时刻数据*/
#define CLR_Free_Variable_1       24         /*上1次2套费率电价切换约定冻结变量数据*/
#define CLR_Free_FF_1             269        /*上1次2套费率电价切换约定冻结数据块*/

/**************************两套阶梯切换冻结*********************************/
/*上2次阶梯切换冻结数据长度同上1次*/
#define CLL_Free_Time_1           5          /*2套阶梯切换约定时间*/
#define CLL_Free_Pos_Ac_En_1      20         /*上1次2套阶梯切换约定冻结正向有功电能数据*/
#define CLL_Free_Rev_Ac_En_1      20         /*上1次2套阶梯切换约定冻结反向有功电能数据*/
#define CLL_Free_Com_Re1_En_1     20         /*上1次2套阶梯切换约定冻结组合无功1电能数据*/
#define CLL_Free_Com_Re2_En_1     20         /*上1次2套阶梯切换约定冻结组合无功2电能数据*/
#define CLL_Free_Qua1_Re_En_1     20         /*上1次2套阶梯切换约定冻结1象限无功电能数据*/
#define CLL_Free_Qua2_Re_En_1     20         /*上1次2套阶梯切换约定冻结2象限无功电能数据*/
#define CLL_Free_Qua3_Re_En_1     20         /*上1次2套阶梯切换约定冻结3象限无功电能数据*/
#define CLL_Free_Qua4_Re_En_1     20         /*上1次2套阶梯切换约定冻结4象限无功电能数据*/
#define CLL_Free_Pos_Ac_De_1      40         /*上1次2套阶梯切换约定冻结正向有功最大需量及发生时刻数据*/
#define CLL_Free_Rev_Ac_De_1      40         /*上1次2套阶梯切换约定冻结反向有功最大需量及发生时刻数据*/
#define CLL_Free_Variable_1       24         /*上1次2套阶梯切换约定冻结变量数据*/
#define CLL_Free_FF_1             269        /*上1次2套阶梯切换约定冻结数据块*/

/***************************剩余金额日冻结****************************/
#define CLChargeBal_Free_Degree   3        /*剩余金额日冻结总次数*/
/*上2次-上62次剩余金额日冻结数据长度同上1次*/
#define CLChargeBal_Free_1        10       /*上1次剩余金额日冻结*/

/***************************电网类事件********************************/
#define CLEventHPTime             CLDate_Time	/*事件发生时间*/
#define CLEventEndTime            CLDate_Time	/*事件结束时间*/
#define CLEventNum                4				/*事件记录序号*/

/**********全失压************/
/*698相关定义*/
#define CLAll_Loss_Vol_Current    9        /*全失压当前值记录表*/
#define CLAll_Loss_Vol_Source     1        /*全失压事件发生源*/
#define CLAll_Loss_Vol_Degree     4        /*全失压事件发生次数*/
#define CLAll_Loss_Vol_Time       4        /*全失压事件累计时间*/
/*645相关定义*/
#define CLAll_Loss_Vol_Note_1     15       /*上1次全失压记录*/

/*******辅助电源掉电********/
/*698相关定义*/
#define CLAux_Pow_Down_Current    9        /*辅助电源掉电当前值记录表*/
#define CLAux_Pow_Down_Source     1        /*辅助电源掉电事件发生源*/
#define CLAux_Pow_Down_Degree     4        /*辅助电源掉电事件发生次数*/
#define CLAux_Pow_Down_Time       4        /*辅助电源掉电事件累计时间*/
/*645相关定义*/
#define	CLAux_Pow_Down_Note_1     12       /*上1次辅助电源掉电记录*/

/**********掉电************/
/*698相关定义*/
#define CLPow_Down_Current        9        /*掉电当前值记录表*/
#define CLPow_Down_Source         1        /*掉电事件发生源*/
#define CLPow_Down_Degree         4        /*掉电事件发生次数*/
#define CLPow_Down_Time           4        /*掉电事件累计时间*/
/*645相关定义*/
#define	CLPow_Down_Note_1         12       /*上1次掉电记录*/

/**********需量超限************/
/*698相关定义*/
#define CLPos_Ac_De_Over_Current      9        /*正向有功需量超限当前值记录表*/
#define CLPos_Ac_De_Over_Source       1        /*正向有功需量超限事件发生源*/
#define CLPos_Ac_De_Over_Degree       4        /*正向有功需量超限事件发生次数*/
#define CLPos_Ac_De_Over_Time         4        /*正向有功需量超限事件累计时间*/

#define CLRec_Ac_De_Over_Current      9        /*反向有功需量超限当前值记录表*/
#define CLRec_Ac_De_Over_Source       1        /*反向有功需量超限事件发生源*/
#define CLRev_Ac_De_Over_Degree       4        /*反向有功需量超限事件发生次数*/
#define CLRev_Ac_De_Over_Time         4        /*反向有功需量超限事件累计时间*/

#define CLQua1_Re_De_Over_Current     8        /*1象限无功需量超限当前值记录表*/
#define CLQua1_Re_De_Over_Degree      4        /*1象限无功需量超限事件发生次数*/
#define CLQua1_Re_De_Over_Time        4        /*1象限无功需量超限事件累计时间*/

#define CLQua2_Re_De_Over_Current     8        /*2象限无功需量超限当前值记录表*/
#define CLQua2_Re_De_Over_Degree      4        /*2象限无功需量超限事件发生次数*/
#define CLQua2_Re_De_Over_Time        4        /*2象限无功需量超限事件累计时间*/

#define CLQua3_Re_De_Over_Current     8        /*3象限无功需量超限当前值记录表*/
#define CLQua3_Re_De_Over_Degree      4        /*3象限无功需量超限事件发生次数*/
#define CLQua3_Re_De_Over_Time        4        /*3象限无功需量超限事件累计时间*/

#define CLQua4_Re_De_Over_Current     8        /*4象限无功需量超限当前值记录表*/
#define CLQua4_Re_De_Over_Degree      4        /*4象限无功需量超限事件发生次数*/
#define CLQua4_Re_De_Over_Time        4        /*4象限无功需量超限事件累计时间*/

#define CLOverDemandRenew_Demand      4        /*需量超限事件,超限期间需量最大值*/
#define CLOverDemandRenew_HapTime     7        /*需量超限事件,超限期间需量最大值发生时间*/

/*645相关定义*/
/*上2次-上10次正向有功需量超限记录数据长度同上1次*/
#define CLPos_Ac_De_Over_Hp_1         6        /*上1次正向有功需量超限发生时刻*/
#define CLPos_Ac_De_Over_End_1        6        /*上1次正向有功需量超限结束时刻*/
#define CLPos_Ac_De_Over_1            8        /*上1次需量超限期间正向有功最大需量及发生时刻*/
#define	CLPos_Ac_De_Over_Note_1       20       /*上1次正向有功需量超限记录*/

/*上2次-上10次反向有功需量超限记录数据长度同上1次*/
#define CLRev_Ac_De_Over_Hp_1         6        /*上1次反向有功需量超限发生时刻*/
#define CLRev_Ac_De_Over_End_1        6        /*上1次反向有功需量超限结束时刻*/
#define CLRev_Ac_De_Over_1            8        /*上1次需量超限期间反向有功最大需量及发生时刻*/
#define	CLRev_Ac_De_Over_Note_1       20       /*上1次反向有功需量超限记录*/

/*上2次-上10次1象限无功需量超限记录数据长度同上1次*/
#define CLQua1_Re_De_Over_Hp_1        6        /*上1次1象限无功需量超限发生时刻*/
#define CLQua1_Re_De_Over_End_1       6        /*上1次1象限无功需量超限结束时刻*/
#define CLQua1_Re_De_Over_1           8        /*上1次需量超限期间1象限无功最大需量及发生时刻*/
#define	CLQua1_Re_De_Over_Note_1      20       /*上1次1象限无功需量超限记录*/

/*上2次-上10次2象限无功需量超限记录数据长度同上1次*/
#define CLQua2_Re_De_Over_Hp_1        6        /*上1次2象限无功需量超限发生时刻*/
#define CLQua2_Re_De_Over_End_1       6        /*上1次2象限无功需量超限结束时刻*/
#define CLQua2_Re_De_Over_1           8        /*上1次需量超限期间2象限无功最大需量及发生时刻*/
#define	CLQua2_Re_De_Over_Note_1      20       /*上1次2象限无功需量超限记录*/

/*上2次-上10次3象限无功需量超限记录数据长度同上1次*/
#define CLQua3_Re_De_Over_Hp_1        6          /*上1次3象限无功需量超限发生时刻*/
#define CLQua3_Re_De_Over_End_1       6          /*上1次3象限无功需量超限结束时刻*/
#define CLQua3_Re_De_Over_1           8          /*上1次需量超限期间3象限无功最大需量及发生时刻*/
#define	CLQua3_Re_De_Over_Note_1      20         /*上1次3象限无功需量超限记录*/

/*上2次-上10次4象限无功需量超限记录数据长度同上1次*/
#define CLQua4_Re_De_Over_Hp_1        6          /*上1次4象限无功需量超限发生时刻*/
#define CLQua4_Re_De_Over_End_1       6          /*上1次4象限无功需量超限结束时刻*/
#define CLQua4_Re_De_Over_1           8          /*上1次需量超限期间4象限无功最大需量及发生时刻*/
#define	CLQua4_Re_De_Over_Note_1      20         /*上1次4象限无功需量超限记录*/

/**********失压************/
/*698相关定义*/
#define CLLoss_Vol_Gather             22         /*失压统计集合*/
#define CLLoss_Vol_Degree             4          /*失压事件发生次数*/
#define CLLoss_Vol_Time               4          /*失压事件累计时间*/
#define CLLoss_Vol_Hp                 7          /*最近1次失压发生时刻*/
#define CLLoss_Vol_End                7          /*最近1次失压结束时刻*/

#define CLLossA_Vol_Current           8          /*A相失压当前值记录表*/
#define CLLossA_Vol_Degree            4          /*A相失压事件发生次数*/
#define CLLossA_Vol_Time              4          /*A相失压事件累计时间*/

#define CLLossB_Vol_Current           8          /*B相失压当前值记录表*/
#define CLLossB_Vol_Degree            4          /*B相失压事件发生次数*/
#define CLLossB_Vol_Time              4          /*B相失压事件累计时间*/

#define CLLossC_Vol_Current           8          /*C相失压当前值记录表*/
#define CLLossC_Vol_Degree            4          /*C相失压事件发生次数*/
#define CLLossC_Vol_Time              4          /*C相失压事件累计时间*/

/*645相关定义*/
/*********A相******/
/*上2次-上10次A相失压事件记录数据长度同上1次*/
#define	CLLossA_Vol_Hp_1              6       /*上1次A相失压发生时刻*/
#define	CLLossAVolHp_PosAcTolEn_1     4       /*上1次A相失压发生时刻正向有功总电能*/
#define	CLLossAVolHp_RevAcTolEn_1     4       /*上1次A相失压发生时刻反向有功总电能*/
#define	CLLossAVolHp_ComRe1TolEn_1    4       /*上1次A相失压发生时刻组合无功1总电能*/
#define	CLLossAVolHp_ComRe2TolEn_1    4       /*上1次A相失压发生时刻组合无功2总电能*/
#define	CLLossAVolHp_APosAcEn_1       4       /*上1次A相失压发生时刻A相正向有功电能*/
#define	CLLossAVolHp_ARevAcEn_1       4       /*上1次A相失压发生时刻A相反向有功电能*/
#define	CLLossAVolHp_AComRe1En_1      4       /*上1次A相失压发生时刻A相组合无功1总电能*/
#define	CLLossAVolHp_AComRe2En_1      4       /*上1次A相失压发生时刻A相组合无功2总电能*/
#define	CLLossAVolHp_AVol_1           2       /*上1次A相失压发生时刻A相电压*/
#define	CLLossAVolHp_ACurr_1          3       /*上1次A相失压发生时刻A相电流*/
#define	CLLossAVolHp_AAcP_1           3       /*上1次A相失压发生时刻A相有功功率*/
#define	CLLossAVolHp_AReP_1           3       /*上1次A相失压发生时刻A相无功功率*/
#define	CLLossAVolHp_APF_1            2       /*上1次A相失压发生时刻A相功率因数*/
#define	CLLossAVolHp_BPosAcEn_1       4       /*上1次A相失压发生时刻B相正向有功电能*/
#define	CLLossAVolHp_BRevAcEn_1       4       /*上1次A相失压发生时刻B相反向有功电能*/
#define	CLLossAVolHp_BComRe1En_1      4       /*上1次A相失压发生时刻B相组合无功1总电能*/
#define	CLLossAVolHp_BComRe2En_1      4       /*上1次A相失压发生时刻B相组合无功2总电能*/
#define	CLLossAVolHp_BVol_1           2       /*上1次A相失压发生时刻B相电压*/
#define	CLLossAVolHp_BCurr_1          3       /*上1次A相失压发生时刻B相电流*/
#define	CLLossAVolHp_BAcP_1           3       /*上1次A相失压发生时刻B相有功功率*/
#define	CLLossAVolHp_BReP_1           3       /*上1次A相失压发生时刻B相无功功率*/
#define	CLLossAVolHp_BPF_1            2       /*上1次A相失压发生时刻B相功率因数*/
#define	CLLossAVolHp_CPosAcEn_1       4       /*上1次A相失压发生时刻C相正向有功电能*/
#define	CLLossAVolHp_CRevAcEn_1       4       /*上1次A相失压发生时刻C相反向有功电能*/
#define	CLLossAVolHp_CComRe1En_1      4       /*上1次A相失压发生时刻C相组合无功1总电能*/
#define	CLLossAVolHp_CComRe2En_1      4       /*上1次A相失压发生时刻C相组合无功2总电能*/
#define	CLLossAVolHp_CVol_1           2       /*上1次A相失压发生时刻C相电压*/
#define	CLLossAVolHp_CCurr_1          3       /*上1次A相失压发生时刻C相电流*/
#define	CLLossAVolHp_CAcP_1           3       /*上1次A相失压发生时刻C相有功功率*/
#define	CLLossAVolHp_CReP_1           3       /*上1次A相失压发生时刻C相无功功率*/
#define	CLLossAVolHp_CPF_1            2       /*上1次A相失压发生时刻C相功率因数*/
#define	CLLossAVol_TolAh_1            4       /*上1次A相失压期间总Ah数*/
#define	CLLossAVol_AAh_1              4       /*上1次A相失压期间A相Ah数*/
#define	CLLossAVol_BAh_1              4       /*上1次A相失压期间B相Ah数*/
#define	CLLossAVol_CAh_1              4       /*上1次A相失压期间C相Ah数*/
#define	CLLossA_Vol_End_1             6       /*上1次A相失压结束时刻*/
#define	CLLossAVolEnd_PosAcTolEn_1    4       /*上1次A相失压结束时刻正向有功总电能*/
#define	CLLossAVolEnd_RevAcTolEn_1    4       /*上1次A相失压结束时刻反向有功总电能*/
#define	CLLossAVolEnd_ComRe1TolEn_1   4       /*上1次A相失压结束时刻组合无功1总电能*/
#define	CLLossAVolEnd_ComRe2TolEn_1   4       /*上1次A相失压结束时刻组合无功2总电能*/
#define	CLLossAVolEnd_APosAcEn_1      4       /*上1次A相失压结束时刻A相正向有功电能*/
#define	CLLossAVolEnd_ARevAcEn_1      4       /*上1次A相失压结束时刻A相反向有功电能*/
#define	CLLossAVolEnd_AComRe1En_1     4       /*上1次A相失压结束时刻A相组合无功1电能*/
#define	CLLossAVolEnd_AComRe2En_1     4       /*上1次A相失压结束时刻A相组合无功2电能*/
#define	CLLossAVolEnd_BPosAcEn_1      4       /*上1次A相失压发生时刻B相正向有功电能*/
#define	CLLossAVolEnd_BRevAcEn_1      4       /*上1次A相失压发生时刻B相反向有功电能*/
#define	CLLossAVolEnd_BComRe1En_1     4       /*上1次A相失压结束时刻B相组合无功1电能*/
#define	CLLossAVolEnd_BComRe2En_1     4       /*上1次A相失压结束时刻B相组合无功2电能*/
#define	CLLossAVolEnd_CPosAcEn_1      4       /*上1次A相失压发生时刻C相正向有功电能*/
#define	CLLossAVolEnd_CRevAcEn_1      4       /*上1次A相失压发生时刻C相反向有功电能*/
#define	CLLossAVolEnd_CComRe1En_1     4       /*上1次A相失压结束时刻C相组合无功1电能*/
#define	CLLossAVolEnd_CComRe2En_1     4       /*上1次A相失压结束时刻C相组合无功2电能*/
#define	CLLossAVol_FF_1               195     /*上1次A相失压数据块*/
#define	CLLossAVol_HpData_1           109     /*上1次A相失压发生数据*/
#define	CLLossAVol_EndData_1          86      /*上1次A相失压结束数据*/

/*********B相**********/
/*上2次-上10次B相失压事件数据长度同上1次*/
#define	CLLossB_Vol_Hp_1             6         /*上1次B相失压发生时刻*/
#define CLLossBVolHp_PosAcTolEn_1    4         /*上1次B相失压发生时刻正向有功总电能*/
#define CLLossBVolHp_RevAcTolEn_1    4         /*上1次B相失压发生时刻反向有功总电能*/
#define CLLossBVolHp_ComRe1TolEn_1   4         /*上1次B相失压发生时刻组合无功1总电能*/
#define CLLossBVolHp_ComRe2TolEn_1   4         /*上1次B相失压发生时刻组合无功2总电能*/
#define CLLossBVolHp_APosAcEn_1      4         /*上1次B相失压发生时刻A相正向有功电能*/
#define CLLossBVolHp_ARevAcEn_1      4         /*上1次B相失压发生时刻A相反向有功电能*/
#define CLLossBVolHp_AComRe1En_1     4         /*上1次B相失压发生时刻A相组合无功1总电能*/
#define CLLossBVolHp_AComRe2En_1     4         /*上1次B相失压发生时刻A相组合无功2总电能*/
#define CLLossBVolHp_AVol_1          2         /*上1次B相失压发生时刻A相电压*/
#define CLLossBVolHp_ACurr_1         3         /*上1次B相失压发生时刻A相电流*/
#define CLLossBVolHp_AAcP_1          3         /*上1次B相失压发生时刻A相有功功率*/
#define CLLossBVolHp_AReP_1          3         /*上1次B相失压发生时刻A相无功功率*/
#define CLLossBVolHp_APF_1           2         /*上1次B相失压发生时刻A相功率因数*/
#define CLLossBVolHp_BPosAcEn_1      4         /*上1次B相失压发生时刻B相正向有功电能*/
#define CLLossBVolHp_BRevAcEn_1      4         /*上1次B相失压发生时刻B相反向有功电能*/
#define CLLossBVolHp_BComRe1En_1     4         /*上1次B相失压发生时刻B相组合无功1总电能*/
#define CLLossBVolHp_BComRe2En_1     4         /*上1次B相失压发生时刻B相组合无功2总电能*/
#define CLLossBVolHp_BVol_1          2         /*上1次B相失压发生时刻B相电压*/
#define CLLossBVolHp_BCurr_1         3         /*上1次B相失压发生时刻B相电流*/
#define CLLossBVolHp_BAcP_1          3         /*上1次B相失压发生时刻B相有功功率*/
#define CLLossBVolHp_BReP_1          3         /*上1次B相失压发生时刻B相无功功率*/
#define CLLossBVolHp_BPF_1           2         /*上1次B相失压发生时刻B相功率因数*/
#define CLLossBVolHp_CPosAcEn_1      4         /*上1次B相失压发生时刻C相正向有功电能*/
#define CLLossBVolHp_CRevAcEn_1      4         /*上1次B相失压发生时刻C相反向有功电能*/
#define CLLossBVolHp_CComRe1En_1     4         /*上1次B相失压发生时刻C相组合无功1总电能*/
#define CLLossBVolHp_CComRe2En_1     4         /*上1次B相失压发生时刻C相组合无功2总电能*/
#define CLLossBVolHp_CVol_1          2         /*上1次B相失压发生时刻C相电压*/
#define CLLossBVolHp_CCurr_1         3         /*上1次B相失压发生时刻C相电流*/
#define CLLossBVolHp_CAcP_1          3         /*上1次B相失压发生时刻C相有功功率*/
#define CLLossBVolHp_CReP_1          3         /*上1次B相失压发生时刻C相无功功率*/
#define CLLossBVolHp_CPF_1           2         /*上1次B相失压发生时刻C相功率因数*/
#define CLLossBVol_TolAh_1           4         /*上1次B相失压期间总Ah数*/
#define CLLossBVol_AAh_1             4         /*上1次B相失压期间A相Ah数*/
#define CLLossBVol_BAh_1             4         /*上1次B相失压期间B相Ah数*/
#define CLLossBVol_CAh_1             4         /*上1次B相失压期间C相Ah数*/
#define CLLossB_Vol_End_1            6         /*上1次B相失压结束时刻*/
#define CLLossBVolEnd_PosAcTolEn_1   4         /*上1次B相失压结束时刻正向有功总电能*/
#define CLLossBVolEnd_RevAcTolEn_1   4         /*上1次B相失压结束时刻反向有功总电能*/
#define CLLossBVolEnd_ComRe1TolEn_1  4         /*上1次B相失压结束时刻组合无功1总电能*/
#define CLLossBVolEnd_ComRe2TolEn_1  4         /*上1次B相失压结束时刻组合无功2总电能*/
#define CLLossBVolEnd_APosAcEn_1     4         /*上1次B相失压结束时刻A相正向有功电能*/
#define CLLossBVolEnd_ARevAcEn_1     4         /*上1次B相失压结束时刻A相反向有功电能*/
#define CLLossBVolEnd_AComRe1En_1    4         /*上1次B相失压结束时刻A相组合无功1电能*/
#define CLLossBVolEnd_AComRe2En_1    4         /*上1次B相失压结束时刻A相组合无功2电能*/
#define CLLossBVolEnd_BPosAcEn_1     4         /*上1次B相失压发生时刻B相正向有功电能*/
#define CLLossBVolEnd_BRevAcEn_1     4         /*上1次B相失压发生时刻B相反向有功电能*/
#define CLLossBVolEnd_BComRe1En_1    4         /*上1次B相失压结束时刻B相组合无功1电能*/
#define CLLossBVolEnd_BComRe2En_1    4         /*上1次B相失压结束时刻B相组合无功2电能*/
#define CLLossBVolEnd_CPosAcEn_1     4         /*上1次B相失压发生时刻C相正向有功电能*/
#define CLLossBVolEnd_CRevAcEn_1     4         /*上1次B相失压发生时刻C相反向有功电能*/
#define CLLossBVolEnd_CComRe1En_1    4         /*上1次B相失压结束时刻C相组合无功1电能*/
#define CLLossBVolEnd_CComRe2En_1    4         /*上1次B相失压结束时刻C相组合无功2电能*/
#define CLLossBVol_FF_1              195       /*上1次B相失压数据块*/
#define CLLossBVol_HpData_1          109       /*上1次B相失压发生数据*/
#define CLLossBVol_EndData_1         86        /*上1次B相失压结束数据*/
/*********C相**********/
/*上2次-上10次C相失压事件数据长度同上1次*/
#define CLLossC_Vol_Hp_1             6         /*上1次C相失压发生时刻*/
#define	CLLossCVolHp_PosAcTolEn_1    4         /*上1次C相失压发生时刻正向有功总电能*/
#define	CLLossCVolHp_RevAcTolEn_1    4         /*上1次C相失压发生时刻反向有功总电能*/
#define	CLLossCVolHp_ComRe1TolEn_1   4         /*上1次C相失压发生时刻组合无功1总电能*/
#define	CLLossCVolHp_ComRe2TolEn_1   4         /*上1次C相失压发生时刻组合无功2总电能*/
#define	CLLossCVolHp_APosAcEn_1      4         /*上1次C相失压发生时刻A相正向有功电能*/
#define	CLLossCVolHp_ARevAcEn_1      4         /*上1次C相失压发生时刻A相反向有功电能*/
#define	CLLossCVolHp_AComRe1En_1     4         /*上1次C相失压发生时刻A相组合无功1总电能*/
#define	CLLossCVolHp_AComRe2En_1     4         /*上1次C相失压发生时刻A相组合无功2总电能*/
#define	CLLossCVolHp_AVol_1          2         /*上1次C相失压发生时刻A相电压*/
#define	CLLossCVolHp_ACurr_1         3         /*上1次C相失压发生时刻A相电流*/
#define	CLLossCVolHp_AAcP_1          3         /*上1次C相失压发生时刻A相有功功率*/
#define	CLLossCVolHp_AReP_1          3         /*上1次C相失压发生时刻A相无功功率*/
#define	CLLossCVolHp_APF_1           2         /*上1次C相失压发生时刻A相功率因数*/
#define	CLLossCVolHp_BPosAcEn_1      4         /*上1次C相失压发生时刻B相正向有功电能*/
#define	CLLossCVolHp_BRevAcEn_1      4         /*上1次C相失压发生时刻B相反向有功电能*/
#define	CLLossCVolHp_BComRe1En_1     4         /*上1次C相失压发生时刻B相组合无功1总电能*/
#define	CLLossCVolHp_BComRe2En_1     4         /*上1次C相失压发生时刻B相组合无功2总电能*/
#define	CLLossCVolHp_BVol_1          2         /*上1次C相失压发生时刻B相电压*/
#define	CLLossCVolHp_BCurr_1         3         /*上1次C相失压发生时刻B相电流*/
#define	CLLossCVolHp_BAcP_1          3         /*上1次C相失压发生时刻B相有功功率*/
#define	CLLossCVolHp_BReP_1          3         /*上1次C相失压发生时刻B相无功功率*/
#define	CLLossCVolHp_BPF_1           2         /*上1次C相失压发生时刻B相功率因数*/
#define	CLLossCVolHp_CPosAcEn_1      4         /*上1次C相失压发生时刻C相正向有功电能*/
#define	CLLossCVolHp_CRevAcEn_1      4         /*上1次C相失压发生时刻C相反向有功电能*/
#define	CLLossCVolHp_CComRe1En_1     4         /*上1次C相失压发生时刻C相组合无功1总电能*/
#define	CLLossCVolHp_CComRe2En_1     4         /*上1次C相失压发生时刻C相组合无功2总电能*/
#define	CLLossCVolHp_CVol_1          2         /*上1次C相失压发生时刻C相电压*/
#define	CLLossCVolHp_CCurr_1         3         /*上1次C相失压发生时刻C相电流*/
#define	CLLossCVolHp_CAcP_1          3         /*上1次C相失压发生时刻C相有功功率*/
#define	CLLossCVolHp_CReP_1          3         /*上1次C相失压发生时刻C相无功功率*/
#define	CLLossCVolHp_CPF_1           2         /*上1次C相失压发生时刻C相功率因数*/
#define	CLLossCVol_TolAh_1           4         /*上1次C相失压期间总Ah数*/
#define	CLLossCVol_AAh_1             4         /*上1次C相失压期间A相Ah数*/
#define	CLLossCVol_BAh_1             4         /*上1次C相失压期间B相Ah数*/
#define	CLLossCVol_CAh_1             4         /*上1次C相失压期间C相Ah数*/
#define	CLLossC_Vol_End_1            6         /*上1次C相失压结束时刻*/
#define	CLLossCVolEnd_PosAcTolEn_1   4         /*上1次C相失压结束时刻正向有功总电能*/
#define	CLLossCVolEnd_ComRe1TolEn_1  4         /*上1次C相失压结束时刻组合无功1总电能*/
#define	CLLossCVolEnd_ComRe2TolEn_1  4         /*上1次C相失压结束时刻组合无功2总电能*/
#define	CLLossCVolEnd_APosAcEn_1     4         /*上1次C相失压结束时刻A相正向有功电能*/
#define	CLLossCVolEnd_ARevAcEn_1     4         /*上1次C相失压结束时刻A相反向有功电能*/
#define	CLLossCVolEnd_AComRe1En_1    4         /*上1次C相失压结束时刻A相组合无功1电能*/
#define	CLLossCVolEnd_AComRe2En_1    4         /*上1次C相失压结束时刻A相组合无功2电能*/
#define	CLLossCVolEnd_BPosAcEn_1     4         /*上1次C相失压发生时刻B相正向有功电能*/
#define	CLLossCVolEnd_BRevAcEn_1     4         /*上1次C相失压发生时刻B相反向有功电能*/
#define	CLLossCVolEnd_BComRe1En_1    4         /*上1次C相失压结束时刻B相组合无功1电能*/
#define	CLLossCVolEnd_BComRe2En_1    4         /*上1次C相失压结束时刻B相组合无功2电能*/
#define	CLLossCVolEnd_CPosAcEn_1     4         /*上1次C相失压发生时刻C相正向有功电能*/
#define	CLLossCVolEnd_CRevAcEn_1     4         /*上1次C相失压发生时刻C相反向有功电能*/
#define	CLLossCVolEnd_CComRe1En_1    4         /*上1次C相失压结束时刻C相组合无功1电能*/
#define	CLLossCVolEnd_CComRe2En_1    4         /*上1次C相失压结束时刻C相组合无功2电能*/
#define	CLLossCVol_FF_1              195       /*上1次C相失压数据块*/
#define	CLLossCVol_HpData_1          109       /*上1次C相失压发生数据*/
#define	CLLossCVol_EndData_1         86        /*上1次C相失压结束数据*/

/**********欠压************/
/*698相关定义*/
#define CLLowA_Vol_Current           8         /*A相欠压当前值记录表*/
#define CLLowA_Vol_Degree            4         /*A相欠压事件发生次数*/
#define CLLowA_Vol_Time              4         /*A相欠压事件累计时间*/

#define CLLowB_Vol_Current           8         /*B相欠压当前值记录表*/
#define CLLowB_Vol_Degree            4         /*B相欠压事件发生次数*/
#define CLLowB_Vol_Time              4         /*B相欠压事件累计时间*/

#define CLLowC_Vol_Current           8         /*C相欠压当前值记录表*/
#define CLLowC_Vol_Degree            4         /*C相欠压事件发生次数*/
#define CLLowC_Vol_Time              4         /*C相欠压事件累计时间*/

/*645相关定义*/
/*******A相*****/
/*上2次-上10次A相欠压事件记录数据长度同上1次*/
#define	CLLowA_Vol_Hp_1              6         /*上1次A相欠压发生时刻*/
#define	CLLowAVolHp_PosAcTolEn_1     4         /*上1次A相欠压发生时刻正向有功总电能*/
#define	CLLowAVolHp_RevAcTolEn_1     4         /*上1次A相欠压发生时刻反向有功总电能*/
#define	CLLowAVolHp_ComRe1TolEn_1    4         /*上1次A相欠压发生时刻组合无功1总电能*/
#define	CLLowAVolHp_ComRe2TolEn_1    4         /*上1次A相欠压发生时刻组合无功2总电能*/
#define	CLLowAVolHp_APosAcEn_1       4         /*上1次A相欠压发生时刻A相正向有功电能*/
#define	CLLowAVolHp_ARevAcEn_1       4         /*上1次A相欠压发生时刻A相反向有功电能*/
#define	CLLowAVolHp_AComRe1En_1      4         /*上1次A相欠压发生时刻A相组合无功1总电能*/
#define	CLLowAVolHp_AComRe2En_1      4         /*上1次A相欠压发生时刻A相组合无功2总电能*/
#define	CLLowAVolHp_AVol_1           2         /*上1次A相欠压发生时刻A相电压*/
#define	CLLowAVolHp_ACurr_1          3         /*上1次A相欠压发生时刻A相电流*/
#define	CLLowAVolHp_AAcP_1           3         /*上1次A相欠压发生时刻A相有功功率*/
#define	CLLowAVolHp_AReP_1           3         /*上1次A相欠压发生时刻A相无功功率*/
#define	CLLowAVolHp_APF_1            2         /*上1次A相欠压发生时刻A相功率因数*/
#define	CLLowAVolHp_BPosAcEn_1       4         /*上1次A相欠压发生时刻B相正向有功电能*/
#define	CLLowAVolHp_BRevAcEn_1       4         /*上1次A相欠压发生时刻B相反向有功电能*/
#define	CLLowAVolHp_BComRe1En_1      4         /*上1次A相欠压发生时刻B相组合无功1总电能*/
#define	CLLowAVolHp_BComRe2En_1      4         /*上1次A相欠压发生时刻B相组合无功2总电能*/
#define	CLLowAVolHp_BVol_1           2         /*上1次A相欠压发生时刻B相电压*/
#define	CLLowAVolHp_BCurr_1          3         /*上1次A相欠压发生时刻B相电流*/
#define	CLLowAVolHp_BAcP_1           3         /*上1次A相欠压发生时刻B相有功功率*/
#define	CLLowAVolHp_BReP_1           3         /*上1次A相欠压发生时刻B相无功功率*/
#define	CLLowAVolHp_BPF_1            2         /*上1次A相欠压发生时刻B相功率因数*/
#define	CLLowAVolHp_CPosAcEn_1       4         /*上1次A相欠压发生时刻C相正向有功电能*/
#define	CLLowAVolHp_CRevAcEn_1       4         /*上1次A相欠压发生时刻C相反向有功电能*/
#define	CLLowAVolHp_CComRe1En_1      4         /*上1次A相欠压发生时刻C相组合无功1总电能*/
#define	CLLowAVolHp_CComRe2En_1      4         /*上1次A相欠压发生时刻C相组合无功2总电能*/
#define	CLLowAVolHp_CVol_1           2         /*上1次A相欠压发生时刻C相电压*/
#define	CLLowAVolHp_CCurr_1          3         /*上1次A相欠压发生时刻C相电流*/
#define	CLLowAVolHp_CAcP_1           3         /*上1次A相欠压发生时刻C相有功功率*/
#define	CLLowAVolHp_CReP_1           3         /*上1次A相欠压发生时刻C相无功功率*/
#define	CLLowAVolHp_CPF_1            2         /*上1次A相欠压发生时刻C相功率因数*/
#define	CLLowAVol_TolAh_1            4         /*上1次A相欠压期间总Ah数*/
#define	CLLowAVol_AAh_1              4         /*上1次A相欠压期间A相Ah数*/
#define	CLLowAVol_BAh_1              4         /*上1次A相欠压期间B相Ah数*/
#define	CLLowAVol_CAh_1              4         /*上1次A相欠压期间C相Ah数*/
#define	CLLowA_Vol_End_1             6         /*上1次A相欠压结束时刻*/
#define	CLLowAVolEnd_PosAcTolEn_1    4         /*上1次A相欠压结束时刻正向有功总电能*/
#define	CLLowAVolEnd_RevAcTolEn_1    4         /*上1次A相欠压结束时刻反向有功总电能*/
#define	CLLowAVolEnd_ComRe1TolEn_1   4         /*上1次A相欠压结束时刻组合无功1总电能*/
#define	CLLowAVolEnd_ComRe2TolEn_1   4         /*上1次A相欠压结束时刻组合无功2总电能*/
#define	CLLowAVolEnd_APosAcEn_1      4         /*上1次A相欠压结束时刻A相正向有功电能*/
#define	CLLowAVolEnd_ARevAcEn_1      4         /*上1次A相欠压结束时刻A相反向有功电能*/
#define	CLLowAVolEnd_AComRe1En_1     4         /*上1次A相欠压结束时刻A相组合无功1电能*/
#define	CLLowAVolEnd_AComRe2En_1     4         /*上1次A相欠压结束时刻A相组合无功2电能*/
#define	CLLowAVolEnd_BPosAcEn_1      4         /*上1次A相欠压发生时刻B相正向有功电能*/
#define	CLLowAVolEnd_BRevAcEn_1      4         /*上1次A相欠压发生时刻B相反向有功电能*/
#define	CLLowAVolEnd_BComRe1En_1     4         /*上1次A相欠压结束时刻B相组合无功1电能*/
#define	CLLowAVolEnd_BComRe2En_1     4         /*上1次A相欠压结束时刻B相组合无功2电能*/
#define	CLLowAVolEnd_CPosAcEn_1      4         /*上1次A相欠压发生时刻C相正向有功电能*/
#define	CLLowAVolEnd_CRevAcEn_1      4         /*上1次A相欠压发生时刻C相反向有功电能*/
#define	CLLowAVolEnd_CComRe1En_1     4         /*上1次A相欠压结束时刻C相组合无功1电能*/
#define	CLLowAVolEnd_CComRe2En_1     4         /*上1次A相欠压结束时刻C相组合无功2电能*/
#define	CLLowAVol_FF_1               195       /*上1次A相欠压数据块*/
#define	CLLowAVol_HpData_1           109       /*上1次A相欠压发生数据*/
#define	CLLowAVol_EndData_1          86        /*上1次A相欠压结束数据*/
/*******B相**********/
/*上2次-上10次B相欠压事件记录数据长度同上1次*/
#define CLLowB_Vol_Hp_1              6         /*上1次B相欠压发生时刻*/
#define	CLLowBVolHp_PosAcTolEn_1     4         /*上1次B相欠压发生时刻正向有功总电能*/
#define	CLLowBVolHp_RevAcTolEn_1     4         /*上1次B相欠压发生时刻反向有功总电能*/
#define	CLLowBVolHp_ComRe1TolEn_1    4         /*上1次B相欠压发生时刻组合无功1总电能*/
#define	CLLowBVolHp_ComRe2TolEn_1    4         /*上1次B相欠压发生时刻组合无功2总电能*/
#define	CLLowBVolHp_APosAcEn_1       4         /*上1次B相欠压发生时刻A相正向有功电能*/
#define	CLLowBVolHp_ARevAcEn_1       4         /*上1次B相欠压发生时刻A相反向有功电能*/
#define	CLLowBVolHp_AComRe1En_1      4         /*上1次B相欠压发生时刻A相组合无功1总电能*/
#define	CLLowBVolHp_AComRe2En_1      4         /*上1次B相欠压发生时刻A相组合无功2总电能*/
#define	CLLowBVolHp_AVol_1           2         /*上1次B相欠压发生时刻A相电压*/
#define	CLLowBVolHp_ACurr_1          3         /*上1次B相欠压发生时刻A相电流*/
#define	CLLowBVolHp_AAcP_1           3         /*上1次B相欠压发生时刻A相有功功率*/
#define	CLLowBVolHp_AReP_1           3         /*上1次B相欠压发生时刻A相无功功率*/
#define	CLLowBVolHp_APF_1            2         /*上1次B相欠压发生时刻A相功率因数*/
#define	CLLowBVolHp_BPosAcEn_1       4         /*上1次B相欠压发生时刻B相正向有功电能*/
#define	CLLowBVolHp_BRevAcEn_1       4         /*上1次B相欠压发生时刻B相反向有功电能*/
#define	CLLowBVolHp_BComRe1En_1      4         /*上1次B相欠压发生时刻B相组合无功1总电能*/
#define	CLLowBVolHp_BComRe2En_1      4         /*上1次B相欠压发生时刻B相组合无功2总电能*/
#define	CLLowBVolHp_BVol_1           2         /*上1次B相欠压发生时刻B相电压*/
#define	CLLowBVolHp_BCurr_1          3         /*上1次B相欠压发生时刻B相电流*/
#define	CLLowBVolHp_BAcP_1           3         /*上1次B相欠压发生时刻B相有功功率*/
#define	CLLowBVolHp_BReP_1           3         /*上1次B相欠压发生时刻B相无功功率*/
#define	CLLowBVolHp_BPF_1            2         /*上1次B相欠压发生时刻B相功率因数*/
#define	CLLowBVolHp_CPosAcEn_1       4         /*上1次B相欠压发生时刻C相正向有功电能*/
#define	CLLowBVolHp_CRevAcEn_1       4         /*上1次B相欠压发生时刻C相反向有功电能*/
#define	CLLowBVolHp_CComRe1En_1      4         /*上1次B相欠压发生时刻C相组合无功1总电能*/
#define	CLLowBVolHp_CComRe2En_1      4         /*上1次B相欠压发生时刻C相组合无功2总电能*/
#define	CLLowBVolHp_CVol_1           2         /*上1次B相欠压发生时刻C相电压*/
#define	CLLowBVolHp_CCurr_1          3         /*上1次B相欠压发生时刻C相电流*/
#define	CLLowBVolHp_CAcP_1           3         /*上1次B相欠压发生时刻C相有功功率*/
#define	CLLowBVolHp_CReP_1           3         /*上1次B相欠压发生时刻C相无功功率*/
#define	CLLowBVolHp_CPF_1            2         /*上1次B相欠压发生时刻C相功率因数*/
#define	CLLowBVol_TolAh_1            4         /*上1次B相欠压期间总Ah数*/
#define	CLLowBVol_AAh_1              4         /*上1次B相欠压期间A相Ah数*/
#define	CLLowBVol_BAh_1              4         /*上1次B相欠压期间B相Ah数*/
#define	CLLowBVol_CAh_1              4         /*上1次B相欠压期间C相Ah数*/
#define	CLLowB_Vol_End_1             6         /*上1次B相欠压结束时刻*/
#define	CLLowBVolEnd_PosAcTolEn_1    4         /*上1次B相欠压结束时刻正向有功总电能*/
#define	CLLowBVolEnd_RevAcTolEn_1    4         /*上1次B相欠压结束时刻反向有功总电能*/
#define	CLLowBVolEnd_ComRe1TolEn_1   4         /*上1次B相欠压结束时刻组合无功1总电能*/
#define	CLLowBVolEnd_ComRe2TolEn_1   4         /*上1次B相欠压结束时刻组合无功2总电能*/
#define	CLLowBVolEnd_APosAcEn_1      4         /*上1次B相欠压结束时刻A相正向有功电能*/
#define	CLLowBVolEnd_ARevAcEn_1      4         /*上1次B相欠压结束时刻A相反向有功电能*/
#define	CLLowBVolEnd_AComRe1En_1     4         /*上1次B相欠压结束时刻A相组合无功1电能*/
#define	CLLowBVolEnd_AComRe2En_1     4         /*上1次B相欠压结束时刻A相组合无功2电能*/
#define	CLLowBVolEnd_BPosAcEn_1      4         /*上1次B相欠压发生时刻B相正向有功电能*/
#define	CLLowBVolEnd_BRevAcEn_1      4         /*上1次B相欠压发生时刻B相反向有功电能*/
#define	CLLowBVolEnd_BComRe1En_1     4         /*上1次B相欠压结束时刻B相组合无功1电能*/
#define	CLLowBVolEnd_BComRe2En_1     4         /*上1次B相欠压结束时刻B相组合无功2电能*/
#define	CLLowBVolEnd_CPosAcEn_1      4         /*上1次B相欠压发生时刻C相正向有功电能*/
#define	CLLowBVolEnd_CRevAcEn_1      4         /*上1次B相欠压发生时刻C相反向有功电能*/
#define	CLLowBVolEnd_CComRe1En_1     4         /*上1次B相欠压结束时刻C相组合无功1电能*/
#define	CLLowBVolEnd_CComRe2En_1     4         /*上1次B相欠压结束时刻C相组合无功2电能*/
#define	CLLowBVol_FF_1               195       /*上1次B相欠压数据块*/
#define	CLLowBVol_HpData_1           109       /*上1次B相欠压发生数据*/
#define	CLLowBVol_EndData_1          86        /*上1次B相欠压结束数据*/
/*******C相**********/
/*上2次-上10次C相欠压事件记录数据长度同上1次*/
#define	CLLowC_Vol_Hp_1              6           /*上1次C相欠压发生时刻*/
#define	CLLowCVolHp_PosAcTolEn_1     4           /*上1次C相欠压发生时刻正向有功总电能*/
#define	CLLowCVolHp_RevAcTolEn_1     4           /*上1次C相欠压发生时刻反向有功总电能*/
#define	CLLowCVolHp_ComRe1TolEn_1    4           /*上1次C相欠压发生时刻组合无功1总电能*/
#define	CLLowCVolHp_ComRe2TolEn_1    4           /*上1次C相欠压发生时刻组合无功2总电能*/
#define	CLLowCVolHp_APosAcEn_1       4           /*上1次C相欠压发生时刻A相正向有功电能*/
#define	CLLowCVolHp_ARevAcEn_1       4           /*上1次C相欠压发生时刻A相反向有功电能*/
#define	CLLowCVolHp_AComRe1En_1      4           /*上1次C相欠压发生时刻A相组合无功1总电能*/
#define	CLLowCVolHp_AComRe2En_1      4           /*上1次C相欠压发生时刻A相组合无功2总电能*/
#define	CLLowCVolHp_AVol_1           2           /*上1次C相欠压发生时刻A相电压*/
#define	CLLowCVolHp_ACurr_1          3           /*上1次C相欠压发生时刻A相电流*/
#define	CLLowCVolHp_AAcP_1           3           /*上1次C相欠压发生时刻A相有功功率*/
#define	CLLowCVolHp_AReP_1           3           /*上1次C相欠压发生时刻A相无功功率*/
#define	CLLowCVolHp_APF_1            2           /*上1次C相欠压发生时刻A相功率因数*/
#define	CLLowCVolHp_BPosAcEn_1       4           /*上1次C相欠压发生时刻B相正向有功电能*/
#define	CLLowCVolHp_BRevAcEn_1       4           /*上1次C相欠压发生时刻B相反向有功电能*/
#define	CLLowCVolHp_BComRe1En_1      4           /*上1次C相欠压发生时刻B相组合无功1总电能*/
#define	CLLowCVolHp_BComRe2En_1      4           /*上1次C相欠压发生时刻B相组合无功2总电能*/
#define	CLLowCVolHp_BVol_1           2           /*上1次C相欠压发生时刻B相电压*/
#define	CLLowCVolHp_BCurr_1          3           /*上1次C相欠压发生时刻B相电流*/
#define	CLLowCVolHp_BAcP_1           3           /*上1次C相欠压发生时刻B相有功功率*/
#define	CLLowCVolHp_BReP_1           3           /*上1次C相欠压发生时刻B相无功功率*/
#define	CLLowCVolHp_BPF_1            2           /*上1次C相欠压发生时刻B相功率因数*/
#define	CLLowCVolHp_CPosAcEn_1       4           /*上1次C相欠压发生时刻C相正向有功电能*/
#define	CLLowCVolHp_CRevAcEn_1       4           /*上1次C相欠压发生时刻C相反向有功电能*/
#define	CLLowCVolHp_CComRe1En_1      4           /*上1次C相欠压发生时刻C相组合无功1总电能*/
#define	CLLowCVolHp_CComRe2En_1      4           /*上1次C相欠压发生时刻C相组合无功2总电能*/
#define	CLLowCVolHp_CVol_1           2           /*上1次C相欠压发生时刻C相电压*/
#define	CLLowCVolHp_CCurr_1          3           /*上1次C相欠压发生时刻C相电流*/
#define	CLLowCVolHp_CAcP_1           3           /*上1次C相欠压发生时刻C相有功功率*/
#define	CLLowCVolHp_CReP_1           3           /*上1次C相欠压发生时刻C相无功功率*/
#define	CLLowCVolHp_CPF_1            2           /*上1次C相欠压发生时刻C相功率因数*/
#define	CLLowCVol_TolAh_1            4           /*上1次C相欠压期间总Ah数*/
#define	CLLowCVol_AAh_1              4           /*上1次C相欠压期间A相Ah数*/
#define	CLLowCVol_BAh_1              4           /*上1次C相欠压期间B相Ah数*/
#define	CLLowCVol_CAh_1              4           /*上1次C相欠压期间C相Ah数*/
#define	CLLowC_Vol_End_1             6           /*上1次C相欠压结束时刻*/
#define	CLLowCVolEnd_PosAcTolEn_1    4           /*上1次C相欠压结束时刻正向有功总电能*/
#define	CLLowCVolEnd_RevAcTolEn_1    4           /*上1次C相欠压结束时刻反向有功总电能*/
#define	CLLowCVolEnd_ComRe1TolEn_1   4           /*上1次C相欠压结束时刻组合无功1总电能*/
#define	CLLowCVolEnd_ComRe2TolEn_1   4           /*上1次C相欠压结束时刻组合无功2总电能*/
#define	CLLowCVolEnd_APosAcEn_1      4           /*上1次C相欠压结束时刻A相正向有功电能*/
#define	CLLowCVolEnd_ARevAcEn_1      4           /*上1次C相欠压结束时刻A相反向有功电能*/
#define	CLLowCVolEnd_AComRe1En_1     4           /*上1次C相欠压结束时刻A相组合无功1电能*/
#define	CLLowCVolEnd_AComRe2En_1     4           /*上1次C相欠压结束时刻A相组合无功2电能*/
#define	CLLowCVolEnd_BPosAcEn_1      4           /*上1次C相欠压发生时刻B相正向有功电能*/
#define	CLLowCVolEnd_BRevAcEn_1      4           /*上1次C相欠压发生时刻B相反向有功电能*/
#define	CLLowCVolEnd_BComRe1En_1     4           /*上1次C相欠压结束时刻B相组合无功1电能*/
#define	CLLowCVolEnd_BComRe2En_1     4           /*上1次C相欠压结束时刻B相组合无功2电能*/
#define	CLLowCVolEnd_CPosAcEn_1      4           /*上1次C相欠压发生时刻C相正向有功电能*/
#define	CLLowCVolEnd_CRevAcEn_1      4           /*上1次C相欠压发生时刻C相反向有功电能*/
#define	CLLowCVolEnd_CComRe1En_1     4           /*上1次C相欠压结束时刻C相组合无功1电能*/
#define	CLLowCVolEnd_CComRe2En_1     4           /*上1次C相欠压结束时刻C相组合无功2电能*/
#define	CLLowCVol_FF_1               195         /*上1次C相欠压数据块*/
#define	CLLowCVol_HpData_1           109         /*上1次C相欠压发生数据*/
#define	CLLowCVol_EndData_1          86          /*上1次C相欠压结束数据*/
/**********过压************/
/*698相关定义*/
#define CLOverA_Vol_Current          8           /*A相过压当前值记录表*/
#define CLOverA_Vol_Degree           4           /*A相过压事件发生次数*/
#define CLOverA_Vol_Time             4           /*A相过压事件累计时间*/

#define CLOverB_Vol_Current          8           /*B相过压当前值记录表*/
#define CLOverB_Vol_Degree           4           /*B相过压事件发生次数*/
#define CLOverB_Vol_Time             4           /*B相过压事件累计时间*/

#define CLOverC_Vol_Current          8           /*C相过压当前值记录表*/
#define CLOverC_Vol_Degree           4           /*C相过压事件发生次数*/
#define CLOverC_Vol_Time             4           /*C相过压事件累计时间*/

/*645相关定义*/
/*****A相*****/
/*上2次-上10次A相过压事件记录数据长度同上1次*/
#define	CLOverA_Vol_Hp_1             6           /*上1次A相过压发生时刻*/
#define	CLOverAVolHp_PosAcTolEn_1    4           /*上1次A相过压发生时刻正向有功总电能*/
#define	CLOverAVolHp_RevAcTolEn_1    4           /*上1次A相过压发生时刻反向有功总电能*/
#define	CLOverAVolHp_ComRe1TolEn_1   4           /*上1次A相过压发生时刻组合无功1总电能*/
#define	CLOverAVolHp_ComRe2TolEn_1   4           /*上1次A相过压发生时刻组合无功2总电能*/
#define	CLOverAVolHp_APosAcEn_1      4           /*上1次A相过压发生时刻A相正向有功电能*/
#define	CLOverAVolHp_ARevAcEn_1      4           /*上1次A相过压发生时刻A相反向有功电能*/
#define	CLOverAVolHp_AComRe1En_1     4           /*上1次A相过压发生时刻A相组合无功1总电能*/
#define	CLOverAVolHp_AComRe2En_1     4           /*上1次A相过压发生时刻A相组合无功2总电能*/
#define	CLOverAVolHp_AVol_1          2           /*上1次A相过压发生时刻A相电压*/
#define	CLOverAVolHp_ACurr_1         3           /*上1次A相过压发生时刻A相电流*/
#define	CLOverAVolHp_AAcP_1          3           /*上1次A相过压发生时刻A相有功功率*/
#define	CLOverAVolHp_AReP_1          3           /*上1次A相过压发生时刻A相无功功率*/
#define	CLOverAVolHp_APF_1           2           /*上1次A相过压发生时刻A相功率因数*/
#define	CLOverAVolHp_BPosAcEn_1      4           /*上1次A相过压发生时刻B相正向有功电能*/
#define	CLOverAVolHp_BRevAcEn_1      4           /*上1次A相过压发生时刻B相反向有功电能*/
#define	CLOverAVolHp_BComRe1En_1     4           /*上1次A相过压发生时刻B相组合无功1总电能*/
#define	CLOverAVolHp_BComRe2En_1     4           /*上1次A相过压发生时刻B相组合无功2总电能*/
#define	CLOverAVolHp_BVol_1          2           /*上1次A相过压发生时刻B相电压*/
#define	CLOverAVolHp_BCurr_1         3           /*上1次A相过压发生时刻B相电流*/
#define	CLOverAVolHp_BAcP_1          3           /*上1次A相过压发生时刻B相有功功率*/
#define	CLOverAVolHp_BReP_1          3           /*上1次A相过压发生时刻B相无功功率*/
#define	CLOverAVolHp_BPF_1           2           /*上1次A相过压发生时刻B相功率因数*/
#define	CLOverAVolHp_CPosAcEn_1      4           /*上1次A相过压发生时刻C相正向有功电能*/
#define	CLOverAVolHp_CRevAcEn_1      4           /*上1次A相过压发生时刻C相反向有功电能*/
#define	CLOverAVolHp_CComRe1En_1     4           /*上1次A相过压发生时刻C相组合无功1总电能*/
#define	CLOverAVolHp_CComRe2En_1     4           /*上1次A相过压发生时刻C相组合无功2总电能*/
#define	CLOverAVolHp_CVol_1          2           /*上1次A相过压发生时刻C相电压*/
#define	CLOverAVolHp_CCurr_1         3           /*上1次A相过压发生时刻C相电流*/
#define	CLOverAVolHp_CAcP_1          3           /*上1次A相过压发生时刻C相有功功率*/
#define	CLOverAVolHp_CReP_1          3           /*上1次A相过压发生时刻C相无功功率*/
#define	CLOverAVolHp_CPF_1           2           /*上1次A相过压发生时刻C相功率因数*/
#define	CLOverAVol_TolAh_1           4           /*上1次A相过压期间总Ah数*/
#define	CLOverAVol_AAh_1             4           /*上1次A相过压期间A相Ah数*/
#define	CLOverAVol_BAh_1             4           /*上1次A相过压期间B相Ah数*/
#define	CLOverAVol_CAh_1             4           /*上1次A相过压期间C相Ah数*/
#define	CLOverA_Vol_End_1            6           /*上1次A相过压结束时刻*/
#define	CLOverAVolEnd_PosAcTolEn_1   4           /*上1次A相过压结束时刻正向有功总电能*/
#define	CLOverAVolEnd_RevAcTolEn_1   4           /*上1次A相过压结束时刻反向有功总电能*/
#define	CLOverAVolEnd_ComRe1TolEn_1  4           /*上1次A相过压结束时刻组合无功1总电能*/
#define	CLOverAVolEnd_ComRe2TolEn_1  4           /*上1次A相过压结束时刻组合无功2总电能*/
#define	CLOverAVolEnd_APosAcEn_1     4           /*上1次A相过压结束时刻A相正向有功电能*/
#define	CLOverAVolEnd_ARevAcEn_1     4           /*上1次A相过压结束时刻A相反向有功电能*/
#define	CLOverAVolEnd_AComRe1En_1    4           /*上1次A相过压结束时刻A相组合无功1电能*/
#define	CLOverAVolEnd_AComRe2En_1    4           /*上1次A相过压结束时刻A相组合无功2电能*/
#define	CLOverAVolEnd_BPosAcEn_1     4           /*上1次A相过压发生时刻B相正向有功电能*/
#define	CLOverAVolEnd_BRevAcEn_1     4           /*上1次A相过压发生时刻B相反向有功电能*/
#define	CLOverAVolEnd_BComRe1En_1    4           /*上1次A相过压结束时刻B相组合无功1电能*/
#define	CLOverAVolEnd_BComRe2En_1    4           /*上1次A相过压结束时刻B相组合无功2电能*/
#define	CLOverAVolEnd_CPosAcEn_1     4           /*上1次A相过压发生时刻C相正向有功电能*/
#define	CLOverAVolEnd_CRevAcEn_1     4           /*上1次A相过压发生时刻C相反向有功电能*/
#define	CLOverAVolEnd_CComRe1En_1    4           /*上1次A相过压结束时刻C相组合无功1电能*/
#define	CLOverAVolEnd_CComRe2En_1    4           /*上1次A相过压结束时刻C相组合无功2电能*/
#define	CLOverAVol_FF_1              195         /*上1次A相过压数据块*/
#define	CLOverAVol_HpData_1          109         /*上1次A相过压发生数据*/
#define	CLOverAVol_EndData_1         86          /*上1次A相过压结束数据*/
/*******B相**********/
/*上2次-上10次B相过压事件记录数据长度同上1次*/
#define	CLOverB_Vol_Hp_1             6           /*上1次B相过压发生时刻*/
#define	CLOverBVolHp_PosAcTolEn_1    4           /*上1次B相过压发生时刻正向有功总电能*/
#define	CLOverBVolHp_RevAcTolEn_1    4           /*上1次B相过压发生时刻反向有功总电能*/
#define	CLOverBVolHp_ComRe1TolEn_1   4           /*上1次B相过压发生时刻组合无功1总电能*/
#define	CLOverBVolHp_ComRe2TolEn_1   4           /*上1次B相过压发生时刻组合无功2总电能*/
#define	CLOverBVolHp_APosAcEn_1      4           /*上1次B相过压发生时刻A相正向有功电能*/
#define	CLOverBVolHp_ARevAcEn_1      4           /*上1次B相过压发生时刻A相反向有功电能*/
#define	CLOverBVolHp_AComRe1En_1     4           /*上1次B相过压发生时刻A相组合无功1总电能*/
#define	CLOverBVolHp_AComRe2En_1     4           /*上1次B相过压发生时刻A相组合无功2总电能*/
#define	CLOverBVolHp_AVol_1          2           /*上1次B相过压发生时刻A相电压*/
#define	CLOverBVolHp_ACurr_1         3           /*上1次B相过压发生时刻A相电流*/
#define	CLOverBVolHp_AAcP_1          3           /*上1次B相过压发生时刻A相有功功率*/
#define	CLOverBVolHp_AReP_1          3           /*上1次B相过压发生时刻A相无功功率*/
#define	CLOverBVolHp_APF_1           2           /*上1次B相过压发生时刻A相功率因数*/
#define	CLOverBVolHp_BPosAcEn_1      4           /*上1次B相过压发生时刻B相正向有功电能*/
#define	CLOverBVolHp_BRevAcEn_1      4           /*上1次B相过压发生时刻B相反向有功电能*/
#define	CLOverBVolHp_BComRe1En_1     4           /*上1次B相过压发生时刻B相组合无功1总电能*/
#define	CLOverBVolHp_BComRe2En_1     4           /*上1次B相过压发生时刻B相组合无功2总电能*/
#define	CLOverBVolHp_BVol_1          2           /*上1次B相过压发生时刻B相电压*/
#define	CLOverBVolHp_BCurr_1         3           /*上1次B相过压发生时刻B相电流*/
#define	CLOverBVolHp_BAcP_1          3           /*上1次B相过压发生时刻B相有功功率*/
#define	CLOverBVolHp_BReP_1          3           /*上1次B相过压发生时刻B相无功功率*/
#define	CLOverBVolHp_BPF_1           2           /*上1次B相过压发生时刻B相功率因数*/
#define	CLOverBVolHp_CPosAcEn_1      4           /*上1次B相过压发生时刻C相正向有功电能*/
#define	CLOverBVolHp_CRevAcEn_1      4           /*上1次B相过压发生时刻C相反向有功电能*/
#define	CLOverBVolHp_CComRe1En_1     4           /*上1次B相过压发生时刻C相组合无功1总电能*/
#define	CLOverBVolHp_CComRe2En_1     4           /*上1次B相过压发生时刻C相组合无功2总电能*/
#define	CLOverBVolHp_CVol_1          2           /*上1次B相过压发生时刻C相电压*/
#define	CLOverBVolHp_CCurr_1         3           /*上1次B相过压发生时刻C相电流*/
#define	CLOverBVolHp_CAcP_1          3           /*上1次B相过压发生时刻C相有功功率*/
#define	CLOverBVolHp_CReP_1          3           /*上1次B相过压发生时刻C相无功功率*/
#define	CLOverBVolHp_CPF_1           2           /*上1次B相过压发生时刻C相功率因数*/
#define	CLOverBVol_TolAh_1           4           /*上1次B相过压期间总Ah数*/
#define	CLOverBVol_AAh_1             4           /*上1次B相过压期间A相Ah数*/
#define	CLOverBVol_BAh_1             4           /*上1次B相过压期间B相Ah数*/
#define	CLOverBVol_CAh_1             4           /*上1次B相过压期间C相Ah数*/
#define	CLOverB_Vol_End_1            6           /*上1次B相过压结束时刻*/
#define	CLOverBVolEnd_PosAcTolEn_1   4           /*上1次B相过压结束时刻正向有功总电能*/
#define	CLOverBVolEnd_RevAcTolEn_1   4           /*上1次B相过压结束时刻反向有功总电能*/
#define	CLOverBVolEnd_ComRe1TolEn_1  4           /*上1次B相过压结束时刻组合无功1总电能*/
#define	CLOverBVolEnd_ComRe2TolEn_1  4           /*上1次B相过压结束时刻组合无功2总电能*/
#define	CLOverBVolEnd_APosAcEn_1     4           /*上1次B相过压结束时刻A相正向有功电能*/
#define	CLOverBVolEnd_ARevAcEn_1     4           /*上1次B相过压结束时刻A相反向有功电能*/
#define	CLOverBVolEnd_AComRe1En_1    4           /*上1次B相过压结束时刻A相组合无功1电能*/
#define	CLOverBVolEnd_AComRe2En_1    4           /*上1次B相过压结束时刻A相组合无功2电能*/
#define	CLOverBVolEnd_BPosAcEn_1     4           /*上1次B相过压发生时刻B相正向有功电能*/
#define	CLOverBVolEnd_BRevAcEn_1     4           /*上1次B相过压发生时刻B相反向有功电能*/
#define	CLOverBVolEnd_BComRe1En_1    4           /*上1次B相过压结束时刻B相组合无功1电能*/
#define	CLOverBVolEnd_BComRe2En_1    4           /*上1次B相过压结束时刻B相组合无功2电能*/
#define	CLOverBVolEnd_CPosAcEn_1     4           /*上1次B相过压发生时刻C相正向有功电能*/
#define	CLOverBVolEnd_CRevAcEn_1     4           /*上1次B相过压发生时刻C相反向有功电能*/
#define	CLOverBVolEnd_CComRe1En_1    4           /*上1次B相过压结束时刻C相组合无功1电能*/
#define	CLOverBVolEnd_CComRe2En_1    4           /*上1次B相过压结束时刻C相组合无功2电能*/
#define	CLOverBVol_FF_1              195         /*上1次B相过压数据块*/
#define	CLOverBVol_HpData_1          109         /*上1次B相过压发生数据*/
#define	CLOverBVol_EndData_1         86          /*上1次B相过压结束数据*/
/*******C相**********/
/*上2次-上10次C相过压事件记录数据长度同上1次*/
#define	CLOverC_Vol_Hp_1             6           /*上1次C相过压发生时刻*/
#define	CLOverCVolHp_PosAcTolEn_1    4           /*上1次C相过压发生时刻正向有功总电能*/
#define	CLOverCVolHp_RevAcTolEn_1    4           /*上1次C相过压发生时刻反向有功总电能*/
#define	CLOverCVolHp_ComRe1TolEn_1   4           /*上1次C相过压发生时刻组合无功1总电能*/
#define	CLOverCVolHp_ComRe2TolEn_1   4           /*上1次C相过压发生时刻组合无功2总电能*/
#define	CLOverCVolHp_APosAcEn_1      4           /*上1次C相过压发生时刻A相正向有功电能*/
#define	CLOverCVolHp_ARevAcEn_1      4           /*上1次C相过压发生时刻A相反向有功电能*/
#define	CLOverCVolHp_AComRe1En_1     4           /*上1次C相过压发生时刻A相组合无功1总电能*/
#define	CLOverCVolHp_AComRe2En_1     4           /*上1次C相过压发生时刻A相组合无功2总电能*/
#define	CLOverCVolHp_AVol_1          2           /*上1次C相过压发生时刻A相电压*/
#define	CLOverCVolHp_ACurr_1         3           /*上1次C相过压发生时刻A相电流*/
#define	CLOverCVolHp_AAcP_1          3           /*上1次C相过压发生时刻A相有功功率*/
#define	CLOverCVolHp_AReP_1          3           /*上1次C相过压发生时刻A相无功功率*/
#define	CLOverCVolHp_APF_1           2           /*上1次C相过压发生时刻A相功率因数*/
#define	CLOverCVolHp_BPosAcEn_1      4           /*上1次C相过压发生时刻B相正向有功电能*/
#define	CLOverCVolHp_BRevAcEn_1      4           /*上1次C相过压发生时刻B相反向有功电能*/
#define	CLOverCVolHp_BComRe1En_1     4           /*上1次C相过压发生时刻B相组合无功1总电能*/
#define	CLOverCVolHp_BComRe2En_1     4           /*上1次C相过压发生时刻B相组合无功2总电能*/
#define	CLOverCVolHp_BVol_1          2           /*上1次C相过压发生时刻B相电压*/
#define	CLOverCVolHp_BCurr_1         3           /*上1次C相过压发生时刻B相电流*/
#define	CLOverCVolHp_BAcP_1          3           /*上1次C相过压发生时刻B相有功功率*/
#define	CLOverCVolHp_BReP_1          3           /*上1次C相过压发生时刻B相无功功率*/
#define	CLOverCVolHp_BPF_1           2           /*上1次C相过压发生时刻B相功率因数*/
#define	CLOverCVolHp_CPosAcEn_1      4           /*上1次C相过压发生时刻C相正向有功电能*/
#define	CLOverCVolHp_CRevAcEn_1      4           /*上1次C相过压发生时刻C相反向有功电能*/
#define	CLOverCVolHp_CComRe1En_1     4           /*上1次C相过压发生时刻C相组合无功1总电能*/
#define	CLOverCVolHp_CComRe2En_1     4           /*上1次C相过压发生时刻C相组合无功2总电能*/
#define	CLOverCVolHp_CVol_1          2           /*上1次C相过压发生时刻C相电压*/
#define	CLOverCVolHp_CCurr_1         3           /*上1次C相过压发生时刻C相电流*/
#define	CLOverCVolHp_CAcP_1          3           /*上1次C相过压发生时刻C相有功功率*/
#define	CLOverCVolHp_CReP_1          3           /*上1次C相过压发生时刻C相无功功率*/
#define	CLOverCVolHp_CPF_1           2           /*上1次C相过压发生时刻C相功率因数*/
#define	CLOverCVol_TolAh_1           4           /*上1次C相过压期间总Ah数*/
#define	CLOverCVol_AAh_1             4           /*上1次C相过压期间A相Ah数*/
#define	CLOverCVol_BAh_1             4           /*上1次C相过压期间B相Ah数*/
#define	CLOverCVol_CAh_1             4           /*上1次C相过压期间C相Ah数*/
#define	CLOverC_Vol_End_1            6           /*上1次C相过压结束时刻*/
#define	CLOverCVolEnd_PosAcTolEn_1   4           /*上1次C相过压结束时刻正向有功总电能*/
#define	CLOverCVolEnd_RevAcTolEn_1   4           /*上1次C相过压结束时刻反向有功总电能*/
#define	CLOverCVolEnd_ComRe1TolEn_1  4           /*上1次C相过压结束时刻组合无功1总电能*/
#define	CLOverCVolEnd_ComRe2TolEn_1  4           /*上1次C相过压结束时刻组合无功2总电能*/
#define	CLOverCVolEnd_APosAcEn_1     4           /*上1次C相过压结束时刻A相正向有功电能*/
#define	CLOverCVolEnd_ARevAcEn_1     4           /*上1次C相过压结束时刻A相反向有功电能*/
#define	CLOverCVolEnd_AComRe1En_1    4           /*上1次C相过压结束时刻A相组合无功1电能*/
#define	CLOverCVolEnd_AComRe2En_1    4           /*上1次C相过压结束时刻A相组合无功2电能*/
#define	CLOverCVolEnd_BPosAcEn_1     4           /*上1次C相过压发生时刻B相正向有功电能*/
#define	CLOverCVolEnd_BRevAcEn_1     4           /*上1次C相过压发生时刻B相反向有功电能*/
#define	CLOverCVolEnd_BComRe1En_1    4           /*上1次C相过压结束时刻B相组合无功1电能*/
#define	CLOverCVolEnd_BComRe2En_1    4           /*上1次C相过压结束时刻B相组合无功2电能*/
#define	CLOverCVolEnd_CPosAcEn_1     4           /*上1次C相过压发生时刻C相正向有功电能*/
#define	CLOverCVolEnd_CRevAcEn_1     4           /*上1次C相过压发生时刻C相反向有功电能*/
#define	CLOverCVolEnd_CComRe1En_1    4           /*上1次C相过压结束时刻C相组合无功1电能*/
#define	CLOverCVolEnd_CComRe2En_1    4           /*上1次C相过压结束时刻C相组合无功2电能*/
#define	CLOverCVol_FF_1              195         /*上1次C相过压数据块*/
#define	CLOverCVol_HpData_1          109         /*上1次C相过压发生数据*/
#define	CLOverCVol_EndData_1         86          /*上1次C相过压结束数据*/

/**********断相************/
/*698相关定义*/
#define CLBreakA_Vol_Current         8           /*A相断相当前值记录表*/
#define CLBreakA_Vol_Degree          4           /*A相断相事件发生次数*/
#define CLBreakA_Vol_Time            4           /*A相断相事件累计时间*/

#define CLBreakB_Vol_Current         8           /*B相断相当前值记录表*/
#define CLBreakB_Vol_Degree          4           /*B相断相事件发生次数*/
#define CLBreakB_Vol_Time            4           /*B相断相事件累计时间*/

#define CLBreakC_Vol_Current         8           /*C相断相当前值记录表*/
#define CLBreakC_Vol_Degree          4           /*C相断相事件发生次数*/
#define CLBreakC_Vol_Time            4           /*C相断相事件累计时间*/

/*645相关定义*/
/*****A相*****/
/*上2次-上10次A相断相事件记录数据长度同上1次*/
#define	CLBreakA_Vol_Hp_1              6         /*上1次A相断相发生时刻*/
#define	CLBreakAVolHp_PosAcTolEn_1     4         /*上1次A相断相发生时刻正向有功总电能*/
#define	CLBreakAVolHp_RevAcTolEn_1     4         /*上1次A相断相发生时刻反向有功总电能*/
#define	CLBreakAVolHp_ComRe1TolEn_1    4         /*上1次A相断相发生时刻组合无功1总电能*/
#define	CLBreakAVolHp_ComRe2TolEn_1    4         /*上1次A相断相发生时刻组合无功2总电能*/
#define	CLBreakAVolHp_APosAcEn_1       4         /*上1次A相断相发生时刻A相正向有功电能*/
#define	CLBreakAVolHp_ARevAcEn_1       4         /*上1次A相断相发生时刻A相反向有功电能*/
#define	CLBreakAVolHp_AComRe1En_1      4         /*上1次A相断相发生时刻A相组合无功1总电能*/
#define	CLBreakAVolHp_AComRe2En_1      4         /*上1次A相断相发生时刻A相组合无功2总电能*/
#define	CLBreakAVolHp_AVol_1           2         /*上1次A相断相发生时刻A相电压*/
#define	CLBreakAVolHp_ACurr_1          3         /*上1次A相断相发生时刻A相电流*/
#define	CLBreakAVolHp_AAcP_1           3         /*上1次A相断相发生时刻A相有功功率*/
#define	CLBreakAVolHp_AReP_1           3         /*上1次A相断相发生时刻A相无功功率*/
#define	CLBreakAVolHp_APF_1            2         /*上1次A相断相发生时刻A相功率因数*/
#define	CLBreakAVolHp_BPosAcEn_1       4         /*上1次A相断相发生时刻B相正向有功电能*/
#define	CLBreakAVolHp_BRevAcEn_1       4         /*上1次A相断相发生时刻B相反向有功电能*/
#define	CLBreakAVolHp_BComRe1En_1      4         /*上1次A相断相发生时刻B相组合无功1总电能*/
#define	CLBreakAVolHp_BComRe2En_1      4         /*上1次A相断相发生时刻B相组合无功2总电能*/
#define	CLBreakAVolHp_BVol_1           2         /*上1次A相断相发生时刻B相电压*/
#define	CLBreakAVolHp_BCurr_1          3         /*上1次A相断相发生时刻B相电流*/
#define	CLBreakAVolHp_BAcP_1           3         /*上1次A相断相发生时刻B相有功功率*/
#define	CLBreakAVolHp_BReP_1           3         /*上1次A相断相发生时刻B相无功功率*/
#define	CLBreakAVolHp_BPF_1            2         /*上1次A相断相发生时刻B相功率因数*/
#define	CLBreakAVolHp_CPosAcEn_1       4         /*上1次A相断相发生时刻C相正向有功电能*/
#define	CLBreakAVolHp_CRevAcEn_1       4         /*上1次A相断相发生时刻C相反向有功电能*/
#define	CLBreakAVolHp_CComRe1En_1      4         /*上1次A相断相发生时刻C相组合无功1总电能*/
#define	CLBreakAVolHp_CComRe2En_1      4         /*上1次A相断相发生时刻C相组合无功2总电能*/
#define	CLBreakAVolHp_CVol_1           2         /*上1次A相断相发生时刻C相电压*/
#define	CLBreakAVolHp_CCurr_1          3         /*上1次A相断相发生时刻C相电流*/
#define	CLBreakAVolHp_CAcP_1           3         /*上1次A相断相发生时刻C相有功功率*/
#define	CLBreakAVolHp_CReP_1           3         /*上1次A相断相发生时刻C相无功功率*/
#define	CLBreakAVolHp_CPF_1            2         /*上1次A相断相发生时刻C相功率因数*/
#define	CLBreakAVol_TolAh_1            4         /*上1次A相断相期间总Ah数*/
#define	CLBreakAVol_AAh_1              4         /*上1次A相断相期间A相Ah数*/
#define	CLBreakAVol_BAh_1              4         /*上1次A相断相期间B相Ah数*/
#define	CLBreakAVol_CAh_1              4         /*上1次A相断相期间C相Ah数*/
#define	CLBreakA_Vol_End_1	           6         /*上1次A相断相结束时刻*/
#define	CLBreakAVolEnd_PosAcTolEn_1    4         /*上1次A相断相结束时刻正向有功总电能*/
#define	CLBreakAVolEnd_RevAcTolEn_1    4         /*上1次A相断相结束时刻反向有功总电能*/
#define	CLBreakAVolEnd_ComRe1TolEn_1   4         /*上1次A相断相结束时刻组合无功1总电能*/
#define	CLBreakAVolEnd_ComRe2TolEn_1   4         /*上1次A相断相结束时刻组合无功2总电能*/
#define	CLBreakAVolEnd_APosAcEn_1      4         /*上1次A相断相结束时刻A相正向有功电能*/
#define	CLBreakAVolEnd_ARevAcEn_1      4         /*上1次A相断相结束时刻A相反向有功电能*/
#define	CLBreakAVolEnd_AComRe1En_1     4         /*上1次A相断相结束时刻A相组合无功1电能*/
#define	CLBreakAVolEnd_AComRe2En_1     4         /*上1次A相断相结束时刻A相组合无功2电能*/
#define	CLBreakAVolEnd_BPosAcEn_1      4         /*上1次A相断相发生时刻B相正向有功电能*/
#define	CLBreakAVolEnd_BRevAcEn_1      4         /*上1次A相断相发生时刻B相反向有功电能*/
#define	CLBreakAVolEnd_BComRe1En_1     4         /*上1次A相断相结束时刻B相组合无功1电能*/
#define	CLBreakAVolEnd_BComRe2En_1     4         /*上1次A相断相结束时刻B相组合无功2电能*/
#define	CLBreakAVolEnd_CPosAcEn_1      4         /*上1次A相断相发生时刻C相正向有功电能*/
#define	CLBreakAVolEnd_CRevAcEn_1      4         /*上1次A相断相发生时刻C相反向有功电能*/
#define	CLBreakAVolEnd_CComRe1En_1     4         /*上1次A相断相结束时刻C相组合无功1电能*/
#define	CLBreakAVolEnd_CComRe2En_1     4         /*上1次A相断相结束时刻C相组合无功2电能*/
#define	CLBreakAVol_FF_1               195       /*上1次A相断相数据块*/
#define	CLBreakAVol_HpData_1           109       /*上1次A相断相发生数据*/
#define	CLBreakAVol_EndData_1          86        /*上1次A相断相结束数据*/
/********B相**********/
/*上2次-上10次B相断相事件记录数据长度同上1次*/
#define	CLBreakB_Vol_Hp_1              6         /*上1次B相断相发生时刻*/
#define	CLBreakBVolHp_PosAcTolEn_1     4         /*上1次B相断相发生时刻正向有功总电能*/
#define	CLBreakBVolHp_RevAcTolEn_1     4         /*上1次B相断相发生时刻反向有功总电能*/
#define	CLBreakBVolHp_ComRe1TolEn_1    4         /*上1次B相断相发生时刻组合无功1总电能*/
#define	CLBreakBVolHp_ComRe2TolEn_1    4         /*上1次B相断相发生时刻组合无功2总电能*/
#define	CLBreakBVolHp_APosAcEn_1       4         /*上1次B相断相发生时刻A相正向有功电能*/
#define	CLBreakBVolHp_ARevAcEn_1       4         /*上1次B相断相发生时刻A相反向有功电能*/
#define	CLBreakBVolHp_AComRe1En_1      4         /*上1次B相断相发生时刻A相组合无功1总电能*/
#define	CLBreakBVolHp_AComRe2En_1      4         /*上1次B相断相发生时刻A相组合无功2总电能*/
#define	CLBreakBVolHp_AVol_1           2         /*上1次B相断相发生时刻A相电压*/
#define	CLBreakBVolHp_ACurr_1          3         /*上1次B相断相发生时刻A相电流*/
#define	CLBreakBVolHp_AAcP_1           3         /*上1次B相断相发生时刻A相有功功率*/
#define	CLBreakBVolHp_AReP_1           3         /*上1次B相断相发生时刻A相无功功率*/
#define	CLBreakBVolHp_APF_1            2         /*上1次B相断相发生时刻A相功率因数*/
#define	CLBreakBVolHp_BPosAcEn_1       4         /*上1次B相断相发生时刻B相正向有功电能*/
#define	CLBreakBVolHp_BRevAcEn_1       4         /*上1次B相断相发生时刻B相反向有功电能*/
#define	CLBreakBVolHp_BComRe1En_1      4         /*上1次B相断相发生时刻B相组合无功1总电能*/
#define	CLBreakBVolHp_BComRe2En_1      4         /*上1次B相断相发生时刻B相组合无功2总电能*/
#define	CLBreakBVolHp_BVol_1           2         /*上1次B相断相发生时刻B相电压*/
#define	CLBreakBVolHp_BCurr_1          3         /*上1次B相断相发生时刻B相电流*/
#define	CLBreakBVolHp_BAcP_1           3         /*上1次B相断相发生时刻B相有功功率*/
#define	CLBreakBVolHp_BReP_1           3         /*上1次B相断相发生时刻B相无功功率*/
#define	CLBreakBVolHp_BPF_1            2         /*上1次B相断相发生时刻B相功率因数*/
#define	CLBreakBVolHp_CPosAcEn_1       4         /*上1次B相断相发生时刻C相正向有功电能*/
#define	CLBreakBVolHp_CRevAcEn_1       4         /*上1次B相断相发生时刻C相反向有功电能*/
#define	CLBreakBVolHp_CComRe1En_1      4         /*上1次B相断相发生时刻C相组合无功1总电能*/
#define	CLBreakBVolHp_CComRe2En_1      4         /*上1次B相断相发生时刻C相组合无功2总电能*/
#define	CLBreakBVolHp_CVol_1           2         /*上1次B相断相发生时刻C相电压*/
#define	CLBreakBVolHp_CCurr_1          3         /*上1次B相断相发生时刻C相电流*/
#define	CLBreakBVolHp_CAcP_1           3         /*上1次B相断相发生时刻C相有功功率*/
#define	CLBreakBVolHp_CReP_1           3         /*上1次B相断相发生时刻C相无功功率*/
#define	CLBreakBVolHp_CPF_1            2         /*上1次B相断相发生时刻C相功率因数*/
#define	CLBreakBVol_TolAh_1            4         /*上1次B相断相期间总Ah数*/
#define	CLBreakBVol_AAh_1              4         /*上1次B相断相期间A相Ah数*/
#define	CLBreakBVol_BAh_1              4         /*上1次B相断相期间B相Ah数*/
#define	CLBreakBVol_CAh_1              4         /*上1次B相断相期间C相Ah数*/
#define	CLBreakB_Vol_End_1	           6         /*上1次B相断相结束时刻*/
#define	CLBreakBVolEnd_PosAcTolEn_1    4         /*上1次B相断相结束时刻正向有功总电能*/
#define	CLBreakBVolEnd_RevAcTolEn_1    4         /*上1次B相断相结束时刻反向有功总电能*/
#define	CLBreakBVolEnd_ComRe1TolEn_1   4         /*上1次B相断相结束时刻组合无功1总电能*/
#define	CLBreakBVolEnd_ComRe2TolEn_1   4         /*上1次B相断相结束时刻组合无功2总电能*/
#define	CLBreakBVolEnd_APosAcEn_1      4         /*上1次B相断相结束时刻A相正向有功电能*/
#define	CLBreakBVolEnd_ARevAcEn_1      4         /*上1次B相断相结束时刻A相反向有功电能*/
#define	CLBreakBVolEnd_AComRe1En_1     4         /*上1次B相断相结束时刻A相组合无功1电能*/
#define	CLBreakBVolEnd_AComRe2En_1     4         /*上1次B相断相结束时刻A相组合无功2电能*/
#define	CLBreakBVolEnd_BPosAcEn_1      4         /*上1次B相断相发生时刻B相正向有功电能*/
#define	CLBreakBVolEnd_BRevAcEn_1      4         /*上1次B相断相发生时刻B相反向有功电能*/
#define	CLBreakBVolEnd_BComRe1En_1     4         /*上1次B相断相结束时刻B相组合无功1电能*/
#define	CLBreakBVolEnd_BComRe2En_1     4         /*上1次B相断相结束时刻B相组合无功2电能*/
#define	CLBreakBVolEnd_CPosAcEn_1      4         /*上1次B相断相发生时刻C相正向有功电能*/
#define	CLBreakBVolEnd_CRevAcEn_1      4         /*上1次B相断相发生时刻C相反向有功电能*/
#define	CLBreakBVolEnd_CComRe1En_1     4         /*上1次B相断相结束时刻C相组合无功1电能*/
#define	CLBreakBVolEnd_CComRe2En_1     4         /*上1次B相断相结束时刻C相组合无功2电能*/
#define	CLBreakBVol_FF_1               195       /*上1次B相断相数据块*/
#define	CLBreakBVol_HpData_1           109       /*上1次B相断相发生数据*/
#define	CLBreakBVol_EndData_1          86        /*上1次B相断相结束数据*/
/*****C相**********/
/*上2次-上10次 C相断相 事件记录数据长度 同上1次*/
#define	CLBreakC_Vol_Hp_1              6         /*上1次C相断相发生时刻*/
#define	CLBreakCVolHp_PosAcTolEn_1     4         /*上1次C相断相发生时刻正向有功总电能*/
#define	CLBreakCVolHp_RevAcTolEn_1     4         /*上1次C相断相发生时刻反向有功总电能*/
#define	CLBreakCVolHp_ComRe1TolEn_1    4         /*上1次C相断相发生时刻组合无功1总电能*/
#define	CLBreakCVolHp_ComRe2TolEn_1    4         /*上1次C相断相发生时刻组合无功2总电能*/
#define	CLBreakCVolHp_APosAcEn_1       4         /*上1次C相断相发生时刻A相正向有功电能*/
#define	CLBreakCVolHp_ARevAcEn_1       4         /*上1次C相断相发生时刻A相反向有功电能*/
#define	CLBreakCVolHp_AComRe1En_1      4         /*上1次C相断相发生时刻A相组合无功1总电能*/
#define	CLBreakCVolHp_AComRe2En_1      4         /*上1次C相断相发生时刻A相组合无功2总电能*/
#define	CLBreakCVolHp_AVol_1           2         /*上1次C相断相发生时刻A相电压*/
#define	CLBreakCVolHp_ACurr_1          3         /*上1次C相断相发生时刻A相电流*/
#define	CLBreakCVolHp_AAcP_1           3         /*上1次C相断相发生时刻A相有功功率*/
#define	CLBreakCVolHp_AReP_1           3         /*上1次C相断相发生时刻A相无功功率*/
#define	CLBreakCVolHp_APF_1            2         /*上1次C相断相发生时刻A相功率因数*/
#define	CLBreakCVolHp_BPosAcEn_1       4         /*上1次C相断相发生时刻B相正向有功电能*/
#define	CLBreakCVolHp_BRevAcEn_1       4         /*上1次C相断相发生时刻B相反向有功电能*/
#define	CLBreakCVolHp_BComRe1En_1      4         /*上1次C相断相发生时刻B相组合无功1总电能*/
#define	CLBreakCVolHp_BComRe2En_1      4         /*上1次C相断相发生时刻B相组合无功2总电能*/
#define	CLBreakCVolHp_BVol_1           2         /*上1次C相断相发生时刻B相电压*/
#define	CLBreakCVolHp_BCurr_1          3         /*上1次C相断相发生时刻B相电流*/
#define	CLBreakCVolHp_BAcP_1           3         /*上1次C相断相发生时刻B相有功功率*/
#define	CLBreakCVolHp_BReP_1           3         /*上1次C相断相发生时刻B相无功功率*/
#define	CLBreakCVolHp_BPF_1            2         /*上1次C相断相发生时刻B相功率因数*/
#define	CLBreakCVolHp_CPosAcEn_1       4         /*上1次C相断相发生时刻C相正向有功电能*/
#define	CLBreakCVolHp_CRevAcEn_1       4         /*上1次C相断相发生时刻C相反向有功电能*/
#define	CLBreakCVolHp_CComRe1En_1      4         /*上1次C相断相发生时刻C相组合无功1总电能*/
#define	CLBreakCVolHp_CComRe2En_1      4         /*上1次C相断相发生时刻C相组合无功2总电能*/
#define	CLBreakCVolHp_CVol_1           2         /*上1次C相断相发生时刻C相电压*/
#define	CLBreakCVolHp_CCurr_1          3         /*上1次C相断相发生时刻C相电流*/
#define	CLBreakCVolHp_CAcP_1           3         /*上1次C相断相发生时刻C相有功功率*/
#define	CLBreakCVolHp_CReP_1           3         /*上1次C相断相发生时刻C相无功功率*/
#define	CLBreakCVolHp_CPF_1            2         /*上1次C相断相发生时刻C相功率因数*/
#define	CLBreakCVol_TolAh_1            4         /*上1次C相断相期间总Ah数*/
#define	CLBreakCVol_AAh_1              4         /*上1次C相断相期间A相Ah数*/
#define	CLBreakCVol_BAh_1              4         /*上1次C相断相期间B相Ah数*/
#define	CLBreakCVol_CAh_1              4         /*上1次C相断相期间C相Ah数*/
#define	CLBreakC_Vol_End_1	           6         /*上1次C相断相结束时刻*/
#define	CLBreakCVolEnd_PosAcTolEn_1    4         /*上1次C相断相结束时刻正向有功总电能*/
#define	CLBreakCVolEnd_RevAcTolEn_1    4         /*上1次C相断相结束时刻反向有功总电能*/
#define	CLBreakCVolEnd_ComRe1TolEn_1   4       /*上1次C相断相结束时刻组合无功1总电能*/
#define	CLBreakCVolEnd_ComRe2TolEn_1   4       /*上1次C相断相结束时刻组合无功2总电能*/
#define	CLBreakCVolEnd_APosAcEn_1      4       /*上1次C相断相结束时刻A相正向有功电能*/
#define	CLBreakCVolEnd_ARevAcEn_1      4       /*上1次C相断相结束时刻A相反向有功电能*/
#define	CLBreakCVolEnd_AComRe1En_1     4       /*上1次C相断相结束时刻A相组合无功1电能*/
#define	CLBreakCVolEnd_AComRe2En_1     4       /*上1次C相断相结束时刻A相组合无功2电能*/
#define	CLBreakCVolEnd_BPosAcEn_1      4       /*上1次C相断相发生时刻B相正向有功电能*/
#define	CLBreakCVolEnd_BRevAcEn_1      4       /*上1次C相断相发生时刻B相反向有功电能*/
#define	CLBreakCVolEnd_BComRe1En_1     4       /*上1次C相断相结束时刻B相组合无功1电能*/
#define	CLBreakCVolEnd_BComRe2En_1     4       /*上1次C相断相结束时刻B相组合无功2电能*/
#define	CLBreakCVolEnd_CPosAcEn_1      4       /*上1次C相断相发生时刻C相正向有功电能*/
#define	CLBreakCVolEnd_CRevAcEn_1      4       /*上1次C相断相发生时刻C相反向有功电能*/
#define	CLBreakCVolEnd_CComRe1En_1     4       /*上1次C相断相结束时刻C相组合无功1电能*/
#define	CLBreakCVolEnd_CComRe2En_1     4       /*上1次C相断相结束时刻C相组合无功2电能*/
#define	CLBreakCVol_FF_1               195     /*上1次C相断相数据块*/
#define	CLBreakCVol_HpData_1           109     /*上1次C相断相发生数据*/
#define	CLBreakCVol_EndData_1          86      /*上1次C相断相结束数据*/

/**********电压逆相序************/
/*698相关定义*/
#define CLRevPS_Vol_Current            9       /*电压逆相序当前值记录表*/
#define CLRevPS_Vol_Source             1       /*电压逆相序事件发生源*/
#define CLRevPS_Vol_Degree             4       /*电压逆相序事件发生次数*/
#define CLRevPS_Vol_Time               4       /*电压逆相序事件累计时间*/

/*645相关定义*/
/*上2次-上10次 电压逆相序 事件记录数据长度 同上1次*/
#define	CLRevPS_Vol_Hp_1               6       /*上1次电压逆相序发生时刻*/
#define	CLRevPSVolHp_PosAcTolEn_1      4       /*上1次电压逆相序发生时刻正向有功总电能*/
#define	CLRevPSVolHp_RevAcTolEn_1      4       /*上1次电压逆相序发生时刻反向有功总电能*/
#define	CLRevPSVolHp_ComRe1TolEn_1     4       /*上1次电压逆相序发生时刻组合无功1总电能*/
#define	CLRevPSVolHp_ComRe2TolEn_1     4       /*上1次电压逆相序发生时刻组合无功2总电能*/
#define	CLRevPSVolHp_APosAcEn_1        4       /*上1次电压逆相序发生时刻A相正向有功电能*/
#define	CLRevPSVolHp_ARevAcEn_1        4       /*上1次电压逆相序发生时刻A相反向有功电能*/
#define	CLRevPSVolHp_AComRe1En_1       4       /*上1次电压逆相序发生时刻A相组合无功1总电能*/
#define	CLRevPSVolHp_AComRe2En_1       4       /*上1次电压逆相序发生时刻A相组合无功2总电能*/
#define	CLRevPSVolHp_BPosAcEn_1        4       /*上1次电压逆相序发生时刻B相正向有功电能*/
#define	CLRevPSVolHp_BRevAcEn_1        4       /*上1次电压逆相序发生时刻B相反向有功电能*/
#define	CLRevPSVolHp_BComRe1En_1       4       /*上1次电压逆相序发生时刻B相组合无功1总电能*/
#define	CLRevPSVolHp_BComRe2En_1       4       /*上1次电压逆相序发生时刻B相组合无功2总电能*/
#define	CLRevPSVolHp_CPosAcEn_1        4       /*上1次电压逆相序发生时刻C相正向有功电能*/
#define	CLRevPSVolHp_CRevAcEn_1        4       /*上1次电压逆相序发生时刻C相反向有功电能*/
#define	CLRevPSVolHp_CComRe1En_1       4       /*上1次电压逆相序发生时刻C相组合无功1总电能*/
#define	CLRevPSVolHp_CComRe2En_1       4       /*上1次电压逆相序发生时刻C相组合无功2总电能*/
#define	CLRevPS_Vol_End_1              6       /*上1次电压逆相序结束时刻*/
#define	CLRevPSVolEnd_PosAcTolEn_1     4       /*上1次电压逆相序结束时刻正向有功总电能*/
#define	CLRevPSVolEnd_RevAcTolEn_1     4       /*上1次电压逆相序结束时刻反向有功总电能*/
#define	CLRevPSVolEnd_ComRe1TolEn_1    4       /*上1次电压逆相序结束时刻组合无功1总电能*/
#define	CLRevPSVolEnd_ComRe2TolEn_1    4       /*上1次电压逆相序结束时刻组合无功2总电能*/
#define	CLRevPSVolEnd_APosAcEn_1       4       /*上1次电压逆相序结束时刻A相正向有功电能*/
#define	CLRevPSVolEnd_ARevAcEn_1       4       /*上1次电压逆相序结束时刻A相反向有功电能*/
#define	CLRevPSVolEnd_AComRe1En_1      4       /*上1次电压逆相序结束时刻A相组合无功1电能*/
#define	CLRevPSVolEnd_AComRe2En_1      4       /*上1次电压逆相序结束时刻A相组合无功2电能*/
#define	CLRevPSVolEnd_BPosAcEn_1       4       /*上1次电压逆相序发生时刻B相正向有功电能*/
#define	CLRevPSVolEnd_BRevAcEn_1       4       /*上1次电压逆相序发生时刻B相反向有功电能*/
#define	CLRevPSVolEnd_BComRe1En_1      4       /*上1次电压逆相序结束时刻B相组合无功1电能*/
#define	CLRevPSVolEnd_BComRe2En_1      4       /*上1次电压逆相序结束时刻B相组合无功2电能*/
#define	CLRevPSVolEnd_CPosAcEn_1       4       /*上1次电压逆相序发生时刻C相正向有功电能*/
#define	CLRevPSVolEnd_CRevAcEn_1       4       /*上1次电压逆相序发生时刻C相反向有功电能*/
#define	CLRevPSVolEnd_CComRe1En_1      4       /*上1次电压逆相序结束时刻C相组合无功1电能*/
#define	CLRevPSVolEnd_CComRe2En_1      4       /*上1次电压逆相序结束时刻C相组合无功2电能*/
#define	CLRevPSVol_FF_1                140     /*上1次电压逆相序数据块*/
#define	CLRevPSVol_HpData_1            70      /*上1次电压逆相序发生数据*/
#define	CLRevPSVol_EndData_1           70      /*上1次电压逆相序结束数据*/

/**********电流逆相序************/
/*698相关定义*/
#define CLRevPS_Curr_Current           9       /*电流逆相序当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CLRevPS_Curr_Source            1       /*电流逆相序发生源*/
#define CLRevPS_Curr_Degree            4       /*电流逆相序总次数*/
#define CLRevPS_Curr_Time              4       /*电流逆相序总累计时间*/

/*645相关定义*/
/*上2次-上10次 电流逆相序 事件记录数据长度 同上1次*/
#define	CLRevPS_Curr_Hp_1              6       /*上1次电流逆相序发生时刻*/
#define	CLRevPSCurrHp_PosAcTolEn_1     4       /*上1次电流逆相序发生时刻正向有功总电能*/
#define	CLRevPSCurrHp_RevAcTolEn_1     4       /*上1次电流逆相序发生时刻反向有功总电能*/
#define	CLRevPSCurrHp_ComRe1TolEn_1    4       /*上1次电流逆相序发生时刻组合无功1总电能*/
#define	CLRevPSCurrHp_ComRe2TolEn_1    4       /*上1次电流逆相序发生时刻组合无功2总电能*/
#define	CLRevPSCurrHp_APosAcEn_1       4       /*上1次电流逆相序发生时刻A相正向有功电能*/
#define	CLRevPSCurrHp_ARevAcEn_1       4       /*上1次电流逆相序发生时刻A相反向有功电能*/
#define	CLRevPSCurrHp_AComRe1En_1      4       /*上1次电流逆相序发生时刻A相组合无功1总电能*/
#define	CLRevPSCurrHp_AComRe2En_1      4       /*上1次电流逆相序发生时刻A相组合无功2总电能*/
#define	CLRevPSCurrHp_BPosAcEn_1       4       /*上1次电流逆相序发生时刻B相正向有功电能*/
#define	CLRevPSCurrHp_BRevAcEn_1       4       /*上1次电流逆相序发生时刻B相反向有功电能*/
#define	CLRevPSCurrHp_BComRe1En_1      4       /*上1次电流逆相序发生时刻B相组合无功1总电能*/
#define	CLRevPSCurrHp_BComRe2En_1      4       /*上1次电流逆相序发生时刻B相组合无功2总电能*/
#define	CLRevPSCurrHp_CPosAcEn_1       4       /*上1次电流逆相序发生时刻C相正向有功电能*/
#define	CLRevPSCurrHp_CRevAcEn_1       4       /*上1次电流逆相序发生时刻C相反向有功电能*/
#define	CLRevPSCurrHp_CComRe1En_1      4       /*上1次电流逆相序发生时刻C相组合无功1总电能*/
#define	CLRevPSCurrHp_CComRe2En_1      4       /*上1次电流逆相序发生时刻C相组合无功2总电能*/
#define	CLRevPS_Curr_End_1             6       /*上1次电流逆相序结束时刻*/
#define	CLRevPSCurrEnd_PosAcTolEn_1    4       /*上1次电流逆相序结束时刻正向有功总电能*/
#define	CLRevPSCurrEnd_RevAcTolEn_1    4       /*上1次电流逆相序结束时刻反向有功总电能*/
#define	CLRevPSCurrEnd_ComRe1TolEn_1   4       /*上1次电流逆相序结束时刻组合无功1总电能*/
#define	CLRevPSCurrEnd_ComRe2TolEn_1   4       /*上1次电流逆相序结束时刻组合无功2总电能*/
#define	CLRevPSCurrEnd_APosAcEn_1      4       /*上1次电流逆相序结束时刻A相正向有功电能*/
#define	CLRevPSCurrEnd_ARevAcEn_1      4       /*上1次电流逆相序结束时刻A相反向有功电能*/
#define	CLRevPSCurrEnd_AComRe1En_1     4       /*上1次电流逆相序结束时刻A相组合无功1电能*/
#define	CLRevPSCurrEnd_AComRe2En_1     4       /*上1次电流逆相序结束时刻A相组合无功2电能*/
#define	CLRevPSCurrEnd_BPosAcEn_1      4       /*上1次电流逆相序发生时刻B相正向有功电能*/
#define	CLRevPSCurrEnd_BRevAcEn_1      4       /*上1次电流逆相序发生时刻B相反向有功电能*/
#define	CLRevPSCurrEnd_BComRe1En_1     4       /*上1次电流逆相序结束时刻B相组合无功1电能*/
#define	CLRevPSCurrEnd_BComRe2En_1     4       /*上1次电流逆相序结束时刻B相组合无功2电能*/
#define	CLRevPSCurrEnd_CPosAcEn_1      4       /*上1次电流逆相序发生时刻C相正向有功电能*/
#define	CLRevPSCurrEnd_CRevAcEn_1      4       /*上1次电流逆相序发生时刻C相反向有功电能*/
#define	CLRevPSCurrEnd_CComRe1En_1     4       /*上1次电流逆相序结束时刻C相组合无功1电能*/
#define	CLRevPSCurrEnd_CComRe2En_1     4       /*上1次电流逆相序结束时刻C相组合无功2电能*/
#define	CLRevPSCurr_FF_1               140     /*上1次电流逆相序数据块*/
#define	CLRevPSCurr_HpData_1           70      /*上1次电流逆相序发生数据*/
#define	CLRevPSCurr_EndData_1          70      /*上1次电流逆相序结束数据*/

/**********电压不平衡************/
/*698相关定义*/
#define CLNoBal_Vol_Current            9       /*电压不平衡事件当前值记录表*/
#define CLNoBal_Vol_Source             1       /*电压不平衡事件发生源*/
#define CLNoBal_Vol_Degree             4       /*电压不平衡事件发生次数*/
#define CLNoBal_Vol_Time               4       /*电压不平衡事件累计时间*/

/*645相关定义*/
/*上2次-上10次 电压不平衡 事件记录数据长度 同上1次*/
#define	CLNoBal_Vol_Hp_1               6       /*上1次电压不平衡发生时刻*/
#define	CLNoBalVolHp_PosAcTolEn_1      4       /*上1次电压不平衡发生时刻正向有功总电能*/
#define	CLNoBalVolHp_RevAcTolEn_1      4       /*上1次电压不平衡发生时刻反向有功总电能*/
#define	CLNoBalVolHp_ComRe1TolEn_1     4       /*上1次电压不平衡发生时刻组合无功1总电能*/
#define	CLNoBalVolHp_ComRe2TolEn_1     4       /*上1次电压不平衡发生时刻组合无功2总电能*/
#define	CLNoBalVolHp_APosAcEn_1        4       /*上1次电压不平衡发生时刻A相正向有功电能*/
#define	CLNoBalVolHp_ARevAcEn_1        4       /*上1次电压不平衡发生时刻A相反向有功电能*/
#define	CLNoBalVolHp_AComRe1En_1       4       /*上1次电压不平衡发生时刻A相组合无功1总电能*/
#define	CLNoBalVolHp_AComRe2En_1       4       /*上1次电压不平衡发生时刻A相组合无功2总电能*/
#define	CLNoBalVolHp_BPosAcEn_1        4       /*上1次电压不平衡发生时刻B相正向有功电能*/
#define	CLNoBalVolHp_BRevAcEn_1        4       /*上1次电压不平衡发生时刻B相反向有功电能*/
#define	CLNoBalVolHp_BComRe1En_1       4       /*上1次电压不平衡发生时刻B相组合无功1总电能*/
#define	CLNoBalVolHp_BComRe2En_1       4       /*上1次电压不平衡发生时刻B相组合无功2总电能*/
#define	CLNoBalVolHp_CPosAcEn_1        4       /*上1次电压不平衡发生时刻C相正向有功电能*/
#define	CLNoBalVolHp_CRevAcEn_1        4       /*上1次电压不平衡发生时刻C相反向有功电能*/
#define	CLNoBalVolHp_CComRe1En_1       4       /*上1次电压不平衡发生时刻C相组合无功1总电能*/
#define	CLNoBalVolHp_CComRe2En_1       4       /*上1次电压不平衡发生时刻C相组合无功2总电能*/
#define	CLNoBalRate_Vol_End_1          3       /*上1次电压不平衡最大不平衡率*/
#define	CLNoBal_Vol_End_1              6       /*上1次电压不平衡结束时刻*/
#define	CLNoBalVolEnd_PosAcTolEn_1     4       /*上1次电压不平衡结束时刻正向有功总电能*/
#define	CLNoBalVolEnd_RevAcTolEn_1     4       /*上1次电压不平衡结束时刻反向有功总电能*/
#define	CLNoBalVolEnd_ComRe1TolEn_1    4       /*上1次电压不平衡结束时刻组合无功1总电能*/
#define	CLNoBalVolEnd_ComRe2TolEn_1    4       /*上1次电压不平衡结束时刻组合无功2总电能*/
#define	CLNoBalVolEnd_APosAcEn_1       4       /*上1次电压不平衡结束时刻A相正向有功电能*/
#define	CLNoBalVolEnd_ARevAcEn_1       4       /*上1次电压不平衡结束时刻A相反向有功电能*/
#define	CLNoBalVolEnd_AComRe1En_1      4       /*上1次电压不平衡结束时刻A相组合无功1电能*/
#define	CLNoBalVolEnd_AComRe2En_1      4       /*上1次电压不平衡结束时刻A相组合无功2电能*/
#define	CLNoBalVolEnd_BPosAcEn_1       4       /*上1次电压不平衡发生时刻B相正向有功电能*/
#define	CLNoBalVolEnd_BRevAcEn_1       4       /*上1次电压不平衡发生时刻B相反向有功电能*/
#define	CLNoBalVolEnd_BComRe1En_1      4       /*上1次电压不平衡结束时刻B相组合无功1电能*/
#define	CLNoBalVolEnd_BComRe2En_1      4       /*上1次电压不平衡结束时刻B相组合无功2电能*/
#define	CLNoBalVolEnd_CPosAcEn_1       4       /*上1次电压不平衡发生时刻C相正向有功电能*/
#define	CLNoBalVolEnd_CRevAcEn_1       4       /*上1次电压不平衡发生时刻C相反向有功电能*/
#define	CLNoBalVolEnd_CComRe1En_1      4       /*上1次电压不平衡结束时刻C相组合无功1电能*/
#define	CLNoBalVolEnd_CComRe2En_1      4       /*上1次电压不平衡结束时刻C相组合无功2电能*/
#define	CLNoBalVol_FF_1                143     /*上1次电压不平衡数据块*/
#define	CLNoBalVol_HpData_1            70      /*上1次电压不平衡发生数据*/
#define	CLNoBalVol_EndData_1           73      /*上1次电压不平衡结束数据*/

/**********电流不平衡************/
/*698相关定义*/
#define CLNoBal_Curr_Current           9        /*电流不平衡事件当前值记录表*/
#define CLNoBal_Curr_Source            1        /*电流不平衡事件发生源*/
#define CLNoBal_Curr_Degree            4        /*电流不平衡事件发生次数*/
#define CLNoBal_Curr_Time              4        /*电流不平衡事件累计时间*/

/*645相关定义*/
/*上2次-上10次 电流不平衡 事件记录数据长度 同上1次*/
#define	CLNoBal_Curr_Hp_1              6        /*上1次电流不平衡发生时刻*/
#define	CLNoBalCurrHp_PosAcTolEn_1     4        /*上1次电流不平衡发生时刻正向有功总电能*/
#define	CLNoBalCurrHp_RevAcTolEn_1     4        /*上1次电流不平衡发生时刻反向有功总电能*/
#define	CLNoBalCurrHp_ComRe1TolEn_1    4        /*上1次电流不平衡发生时刻组合无功1总电能*/
#define	CLNoBalCurrHp_ComRe2TolEn_1    4        /*上1次电流不平衡发生时刻组合无功2总电能*/
#define	CLNoBalCurrHp_APosAcEn_1       4        /*上1次电流不平衡发生时刻A相正向有功电能*/
#define	CLNoBalCurrHp_ARevAcEn_1       4        /*上1次电流不平衡发生时刻A相反向有功电能*/
#define	CLNoBalCurrHp_AComRe1En_1      4        /*上1次电流不平衡发生时刻A相组合无功1总电能*/
#define	CLNoBalCurrHp_AComRe2En_1      4        /*上1次电流不平衡发生时刻A相组合无功2总电能*/
#define	CLNoBalCurrHp_BPosAcEn_1       4        /*上1次电流不平衡发生时刻B相正向有功电能*/
#define	CLNoBalCurrHp_BRevAcEn_1       4        /*上1次电流不平衡发生时刻B相反向有功电能*/
#define	CLNoBalCurrHp_BComRe1En_1      4        /*上1次电流不平衡发生时刻B相组合无功1总电能*/
#define	CLNoBalCurrHp_BComRe2En_1      4        /*上1次电流不平衡发生时刻B相组合无功2总电能*/
#define	CLNoBalCurrHp_CPosAcEn_1       4        /*上1次电流不平衡发生时刻C相正向有功电能*/
#define	CLNoBalCurrHp_CRevAcEn_1       4        /*上1次电流不平衡发生时刻C相反向有功电能*/
#define	CLNoBalCurrHp_CComRe1En_1      4        /*上1次电流不平衡发生时刻C相组合无功1总电能*/
#define	CLNoBalCurrHp_CComRe2En_1      4        /*上1次电流不平衡发生时刻C相组合无功2总电能*/
#define	CLNoBalRate_Curr_1             3        /*上1次电流不平衡最大不平衡率*/
#define	CLNoBal_Curr_End_1             6        /*上1次电流不平衡结束时刻*/
#define	CLNoBalCurrEnd_PosAcTolEn_1    4        /*上1次电流不平衡结束时刻正向有功总电能*/
#define	CLNoBalCurrEnd_RevAcTolEn_1    4        /*上1次电流不平衡结束时刻反向有功总电能*/
#define	CLNoBalCurrEnd_ComRe1TolEn_1   4        /*上1次电流不平衡结束时刻组合无功1总电能*/
#define	CLNoBalCurrEnd_ComRe2TolEn_1   4        /*上1次电流不平衡结束时刻组合无功2总电能*/
#define	CLNoBalCurrEnd_APosAcEn_1      4        /*上1次电流不平衡结束时刻A相正向有功电能*/
#define	CLNoBalCurrEnd_ARevAcEn_1      4        /*上1次电流不平衡结束时刻A相反向有功电能*/
#define	CLNoBalCurrEnd_AComRe1En_1     4        /*上1次电流不平衡结束时刻A相组合无功1电能*/
#define	CLNoBalCurrEnd_AComRe2En_1     4        /*上1次电流不平衡结束时刻A相组合无功2电能*/
#define	CLNoBalCurrEnd_BPosAcEn_1      4        /*上1次电流不平衡发生时刻B相正向有功电能*/
#define	CLNoBalCurrEnd_BRevAcEn_1      4        /*上1次电流不平衡发生时刻B相反向有功电能*/
#define	CLNoBalCurrEnd_BComRe1En_1     4        /*上1次电流不平衡结束时刻B相组合无功1电能*/
#define	CLNoBalCurrEnd_BComRe2En_1     4        /*上1次电流不平衡结束时刻B相组合无功2电能*/
#define	CLNoBalCurrEnd_CPosAcEn_1      4        /*上1次电流不平衡发生时刻C相正向有功电能*/
#define	CLNoBalCurrEnd_CRevAcEn_1      4        /*上1次电流不平衡发生时刻C相反向有功电能*/
#define	CLNoBalCurrEnd_CComRe1En_1     4        /*上1次电流不平衡结束时刻C相组合无功1电能*/
#define	CLNoBalCurrEnd_CComRe2En_1     4        /*上1次电流不平衡结束时刻C相组合无功2电能*/
#define	CLNoBalCurr_FF_1               143      /*上1次电流不平衡数据块*/
#define	CLNoBalCurr_HpData_1           70       /*上1次电流不平衡发生数据*/
#define	CLNoBalCurr_EndData_1          73       /*上1次电流不平衡结束数据*/

/**********电流严重不平衡************/
/*698相关定义*/
#define CLSevNoBal_Curr_Current            9        /*电流严重不平衡事件当前值记录表*/
#define CLSevNoBal_Curr_Source             1        /*电流严重不平衡事件发生源*/
#define CLSevNoBal_Curr_Degree             4        /*电流严重不平衡事件发生次数*/
#define CLSevNoBal_Curr_Time               4        /*电流严重不平衡事件累计时间*/

/*645相关定义*/
/*上2次-上10次 电流严重不平衡 事件记录数据长度 同上1次*/
#define	CLSevNoBal_Curr_Hp_1               6        /*上1次电流严重不平衡发生时刻*/
#define	CLSevNoBalCurrHp_PosAcTolEn_1      4        /*上1次电流严重不平衡发生时刻正向有功总电能*/
#define	CLSevNoBalCurrHp_RevAcTolEn_1      4        /*上1次电流严重不平衡发生时刻反向有功总电能*/
#define	CLSevNoBalCurrHp_ComRe1TolEn_1     4        /*上1次电流严重不平衡发生时刻组合无功1总电能*/
#define	CLSevNoBalCurrHp_ComRe2TolEn_1     4        /*上1次电流严重不平衡发生时刻组合无功2总电能*/
#define	CLSevNoBalCurrHp_APosAcEn_1        4        /*上1次电流严重不平衡发生时刻A相正向有功电能*/
#define	CLSevNoBalCurrHp_ARevAcEn_1        4        /*上1次电流严重不平衡发生时刻A相反向有功电能*/
#define	CLSevNoBalCurrHp_AComRe1En_1       4        /*上1次电流严重不平衡发生时刻A相组合无功1总电能*/
#define	CLSevNoBalCurrHp_AComRe2En_1       4        /*上1次电流严重不平衡发生时刻A相组合无功2总电能*/
#define	CLSevNoBalCurrHp_BPosAcEn_1        4        /*上1次电流严重不平衡发生时刻B相正向有功电能*/
#define	CLSevNoBalCurrHp_BRevAcEn_1        4        /*上1次电流严重不平衡发生时刻B相反向有功电能*/
#define	CLSevNoBalCurrHp_BComRe1En_1       4        /*上1次电流严重不平衡发生时刻B相组合无功1总电能*/
#define	CLSevNoBalCurrHp_BComRe2En_1       4        /*上1次电流严重不平衡发生时刻B相组合无功2总电能*/
#define	CLSevNoBalCurrHp_CPosAcEn_1        4        /*上1次电流严重不平衡发生时刻C相正向有功电能*/
#define	CLSevNoBalCurrHp_CRevAcEn_1        4        /*上1次电流严重不平衡发生时刻C相反向有功电能*/
#define	CLSevNoBalCurrHp_CComRe1En_1       4        /*上1次电流严重不平衡发生时刻C相组合无功1总电能*/
#define	CLSevNoBalCurrHp_CComRe2En_1       4        /*上1次电流严重不平衡发生时刻C相组合无功2总电能*/
#define	CLSevNoBalRate_Curr_1              3        /*上1次电流严重不平衡最大不平衡率*/
#define	CLSevNoBal_Curr_End_1              6        /*上1次电流严重不平衡结束时刻*/
#define	CLSevNoBalCurrEnd_PosAcTolEn_1     4        /*上1次电流严重不平衡结束时刻正向有功总电能*/
#define	CLSevNoBalCurrEnd_RevAcTolEn_1     4        /*上1次电流严重不平衡结束时刻反向有功总电能*/
#define	CLSevNoBalCurrEnd_ComRe1TolEn_1    4        /*上1次电流严重不平衡结束时刻组合无功1总电能*/
#define	CLSevNoBalCurrEnd_ComRe2TolEn_1    4        /*上1次电流严重不平衡结束时刻组合无功2总电能*/
#define	CLSevNoBalCurrEnd_APosAcEn_1       4        /*上1次电流严重不平衡结束时刻A相正向有功电能*/
#define	CLSevNoBalCurrEnd_ARevAcEn_1       4        /*上1次电流严重不平衡结束时刻A相反向有功电能*/
#define	CLSevNoBalCurrEnd_AComRe1En_1      4        /*上1次电流严重不平衡结束时刻A相组合无功1电能*/
#define	CLSevNoBalCurrEnd_AComRe2En_1      4        /*上1次电流严重不平衡结束时刻A相组合无功2电能*/
#define	CLSevNoBalCurrEnd_BPosAcEn_1       4        /*上1次电流严重不平衡发生时刻B相正向有功电能*/
#define	CLSevNoBalCurrEnd_BRevAcEn_1       4        /*上1次电流严重不平衡发生时刻B相反向有功电能*/
#define	CLSevNoBalCurrEnd_BComRe1En_1      4        /*上1次电流严重不平衡结束时刻B相组合无功1电能*/
#define	CLSevNoBalCurrEnd_BComRe2En_1      4        /*上1次电流严重不平衡结束时刻B相组合无功2电能*/
#define	CLSevNoBalCurrEnd_CPosAcEn_1       4        /*上1次电流严重不平衡发生时刻C相正向有功电能*/
#define	CLSevNoBalCurrEnd_CRevAcEn_1       4        /*上1次电流严重不平衡发生时刻C相反向有功电能*/
#define	CLSevNoBalCurrEnd_CComRe1En_1      4        /*上1次电流严重不平衡结束时刻C相组合无功1电能*/
#define	CLSevNoBalCurrEnd_CComRe2En_1      4        /*上1次电流严重不平衡结束时刻C相组合无功2电能*/
#define	CLSevNoBalCurr_FF_1                143      /*上1次电流严重不平衡数据块*/
#define	CLSevNoBalCurr_HpData_1            70       /*上1次电流严重不平衡发生数据*/
#define	CLSevNoBalCurr_EndData_1           73       /*上1次电流严重不平衡结束数据*/

/**********失流************/
/*698相关定义*/
#define CLLossA_Curr_Current               8        /*A相失流事件当前值记录表*/
#define CLLossA_Curr_Degree                4        /*A相失流事件发生次数*/
#define CLLossA_Curr_Time                  4        /*A相失流事件累计时间*/

#define CLLossB_Curr_Current               8        /*B相失流事件当前值记录表*/
#define CLLossB_Curr_Degree                4        /*B相失流事件发生次数*/
#define CLLossB_Curr_Time                  4        /*B相失流事件累计时间*/

#define CLLossC_Curr_Current               8        /*C相失流事件当前值记录表*/
#define CLLossC_Curr_Degree                4        /*C相失流事件发生次数*/
#define CLLossC_Curr_Time                  4        /*C相失流事件累计时间*/

/*645相关定义*/
/*******A相******/
/*上2次-上10次 A相失流 事件记录数据长度 同上1次*/
#define	CLLossA_Curr_Hp_1                  6       /*上1次A相失流发生时刻*/
#define	CLLossACurrHp_PosAcTolEn_1         4       /*上1次A相失流发生时刻正向有功总电能*/
#define	CLLossACurrHp_RevAcTolEn_1         4       /*上1次A相失流发生时刻反向有功总电能*/
#define	CLLossACurrHp_ComRe1TolEn_1        4       /*上1次A相失流发生时刻组合无功1总电能*/
#define	CLLossACurrHp_ComRe2TolEn_1        4       /*上1次A相失流发生时刻组合无功2总电能*/
#define	CLLossACurrHp_APosAcEn_1           4       /*上1次A相失流发生时刻A相正向有功电能*/
#define	CLLossACurrHp_ARevAcEn_1           4       /*上1次A相失流发生时刻A相反向有功电能*/
#define	CLLossACurrHp_AComRe1En_1          4       /*上1次A相失流发生时刻A相组合无功1总电能*/
#define	CLLossACurrHp_AComRe2En_1          4       /*上1次A相失流发生时刻A相组合无功2总电能*/
#define	CLLossACurrHp_AVol_1               2       /*上1次A相失流发生时刻A相电压*/
#define	CLLossACurrHp_ACurr_1              3       /*上1次A相失流发生时刻A相电流*/
#define	CLLossACurrHp_AAcP_1               3       /*上1次A相失流发生时刻A相有功功率*/
#define	CLLossACurrHp_AReP_1               3       /*上1次A相失流发生时刻A相无功功率*/
#define	CLLossACurrHp_APF_1                2       /*上1次A相失流发生时刻A相功率因数*/
#define	CLLossACurrHp_BPosAcEn_1           4       /*上1次A相失流发生时刻B相正向有功电能*/
#define	CLLossACurrHp_BRevAcEn_1           4       /*上1次A相失流发生时刻B相反向有功电能*/
#define	CLLossACurrHp_BComRe1En_1          4       /*上1次A相失流发生时刻B相组合无功1总电能*/
#define	CLLossACurrHp_BComRe2En_1          4       /*上1次A相失流发生时刻B相组合无功2总电能*/
#define	CLLossACurrHp_BVol_1               2       /*上1次A相失流发生时刻B相电压*/
#define	CLLossACurrHp_BCurr_1              3       /*上1次A相失流发生时刻B相电流*/
#define	CLLossACurrHp_BAcP_1               3       /*上1次A相失流发生时刻B相有功功率*/
#define	CLLossACurrHp_BReP_1               3       /*上1次A相失流发生时刻B相无功功率*/
#define	CLLossACurrHp_BPF_1                2       /*上1次A相失流发生时刻B相功率因数*/
#define	CLLossACurrHp_CPosAcEn_1           4       /*上1次A相失流发生时刻C相正向有功电能*/
#define	CLLossACurrHp_CRevAcEn_1           4       /*上1次A相失流发生时刻C相反向有功电能*/
#define	CLLossACurrHp_CComRe1En_1          4       /*上1次A相失流发生时刻C相组合无功1总电能*/
#define	CLLossACurrHp_CComRe2En_1          4       /*上1次A相失流发生时刻C相组合无功2总电能*/
#define	CLLossACurrHp_CVol_1               2       /*上1次A相失流发生时刻C相电压*/
#define	CLLossACurrHp_CCurr_1              3       /*上1次A相失流发生时刻C相电流*/
#define	CLLossACurrHp_CAcP_1               3       /*上1次A相失流发生时刻C相有功功率*/
#define	CLLossACurrHp_CReP_1               3       /*上1次A相失流发生时刻C相无功功率*/
#define	CLLossACurrHp_CPF_1                2       /*上1次A相失流发生时刻C相功率因数*/
#define	CLLossA_Curr_End_1	               6       /*上1次A相失流结束时刻*/
#define	CLLossACurrEnd_PosAcTolEn_1        4       /*上1次A相失流结束时刻正向有功总电能*/
#define	CLLossACurrEnd_RevAcTolEn_1        4       /*上1次A相失流结束时刻反向有功总电能*/
#define	CLLossACurrEnd_ComRe1TolEn_1       4       /*上1次A相失流结束时刻组合无功1总电能*/
#define	CLLossACurrEnd_ComRe2TolEn_1       4       /*上1次A相失流结束时刻组合无功2总电能*/
#define	CLLossACurrEnd_APosAcEn_1          4       /*上1次A相失流结束时刻A相正向有功电能*/
#define	CLLossACurrEnd_ARevAcEn_1          4       /*上1次A相失流结束时刻A相反向有功电能*/
#define	CLLossACurrEnd_AComRe1En_1         4       /*上1次A相失流结束时刻A相组合无功1电能*/
#define	CLLossACurrEnd_AComRe2En_1         4       /*上1次A相失流结束时刻A相组合无功2电能*/
#define	CLLossACurrEnd_BPosAcEn_1          4       /*上1次A相失流发生时刻B相正向有功电能*/
#define	CLLossACurrEnd_BRevAcEn_1          4       /*上1次A相失流发生时刻B相反向有功电能*/
#define	CLLossACurrEnd_BComRe1En_1         4       /*上1次A相失流结束时刻B相组合无功1电能*/
#define	CLLossACurrEnd_BComRe2En_1         4       /*上1次A相失流结束时刻B相组合无功2电能*/
#define	CLLossACurrEnd_CPosAcEn_1          4       /*上1次A相失流发生时刻C相正向有功电能*/
#define	CLLossACurrEnd_CRevAcEn_1          4       /*上1次A相失流发生时刻C相反向有功电能*/
#define	CLLossACurrEnd_CComRe1En_1         4       /*上1次A相失流结束时刻C相组合无功1电能*/
#define	CLLossACurrEnd_CComRe2En_1         4       /*上1次A相失流结束时刻C相组合无功2电能*/
#define	CLLossACurr_FF_1                   179     /*上1次A相失流数据块*/
#define	CLLossACurr_HpData_1               109     /*上1次A相失流发生数据*/
#define	CLLossACurr_EndData_1              70      /*上1次A相失流结束数据*/

/*********B相**********/
/*上2次-上10次 B相失流 事件记录数据长度 同上1次*/
#define	CLLossB_Curr_Hp_1                  6       /*上1次B相失流发生时刻*/
#define	CLLossBCurrHp_PosAcTolEn_1         4       /*上1次B相失流发生时刻正向有功总电能*/
#define	CLLossBCurrHp_RevAcTolEn_1         4       /*上1次B相失流发生时刻反向有功总电能*/
#define	CLLossBCurrHp_ComRe1TolEn_1        4       /*上1次B相失流发生时刻组合无功1总电能*/
#define	CLLossBCurrHp_ComRe2TolEn_1        4       /*上1次B相失流发生时刻组合无功2总电能*/
#define	CLLossBCurrHp_APosAcEn_1           4       /*上1次B相失流发生时刻A相正向有功电能*/
#define	CLLossBCurrHp_ARevAcEn_1           4       /*上1次B相失流发生时刻A相反向有功电能*/
#define	CLLossBCurrHp_AComRe1En_1          4       /*上1次B相失流发生时刻A相组合无功1总电能*/
#define	CLLossBCurrHp_AComRe2En_1          4       /*上1次B相失流发生时刻A相组合无功2总电能*/
#define	CLLossBCurrHp_AVol_1               2       /*上1次B相失流发生时刻A相电压*/
#define	CLLossBCurrHp_ACurr_1              3       /*上1次B相失流发生时刻A相电流*/
#define	CLLossBCurrHp_AAcP_1               3       /*上1次B相失流发生时刻A相有功功率*/
#define	CLLossBCurrHp_AReP_1               3       /*上1次B相失流发生时刻A相无功功率*/
#define	CLLossBCurrHp_APF_1                2       /*上1次B相失流发生时刻A相功率因数*/
#define	CLLossBCurrHp_BPosAcEn_1           4       /*上1次B相失流发生时刻B相正向有功电能*/
#define	CLLossBCurrHp_BRevAcEn_1           4       /*上1次B相失流发生时刻B相反向有功电能*/
#define	CLLossBCurrHp_BComRe1En_1          4       /*上1次B相失流发生时刻B相组合无功1总电能*/
#define	CLLossBCurrHp_BComRe2En_1          4       /*上1次B相失流发生时刻B相组合无功2总电能*/
#define	CLLossBCurrHp_BVol_1               2       /*上1次B相失流发生时刻B相电压*/
#define	CLLossBCurrHp_BCurr_1              3       /*上1次B相失流发生时刻B相电流*/
#define	CLLossBCurrHp_BAcP_1               3       /*上1次B相失流发生时刻B相有功功率*/
#define	CLLossBCurrHp_BReP_1               3       /*上1次B相失流发生时刻B相无功功率*/
#define	CLLossBCurrHp_BPF_1                2       /*上1次B相失流发生时刻B相功率因数*/
#define	CLLossBCurrHp_CPosAcEn_1           4       /*上1次B相失流发生时刻C相正向有功电能*/
#define	CLLossBCurrHp_CRevAcEn_1           4       /*上1次B相失流发生时刻C相反向有功电能*/
#define	CLLossBCurrHp_CComRe1En_1          4       /*上1次B相失流发生时刻C相组合无功1总电能*/
#define	CLLossBCurrHp_CComRe2En_1          4       /*上1次B相失流发生时刻C相组合无功2总电能*/
#define	CLLossBCurrHp_CVol_1               2       /*上1次B相失流发生时刻C相电压*/
#define	CLLossBCurrHp_CCurr_1              3       /*上1次B相失流发生时刻C相电流*/
#define	CLLossBCurrHp_CAcP_1               3       /*上1次B相失流发生时刻C相有功功率*/
#define	CLLossBCurrHp_CReP_1               3       /*上1次B相失流发生时刻C相无功功率*/
#define	CLLossBCurrHp_CPF_1                2       /*上1次B相失流发生时刻C相功率因数*/
#define	CLLossB_Curr_End_1                 6       /*上1次B相失流结束时刻*/
#define	CLLossBCurrEnd_PosAcTolEn_1        4       /*上1次B相失流结束时刻正向有功总电能*/
#define	CLLossBCurrEnd_RevAcTolEn_1        4       /*上1次B相失流结束时刻反向有功总电能*/
#define	CLLossBCurrEnd_ComRe1TolEn_1       4       /*上1次B相失流结束时刻组合无功1总电能*/
#define	CLLossBCurrEnd_ComRe2TolEn_1       4       /*上1次B相失流结束时刻组合无功2总电能*/
#define	CLLossBCurrEnd_APosAcEn_1          4       /*上1次B相失流结束时刻A相正向有功电能*/
#define	CLLossBCurrEnd_ARevAcEn_1          4       /*上1次B相失流结束时刻A相反向有功电能*/
#define	CLLossBCurrEnd_AComRe1En_1         4       /*上1次B相失流结束时刻A相组合无功1电能*/
#define	CLLossBCurrEnd_AComRe2En_1         4       /*上1次B相失流结束时刻A相组合无功2电能*/
#define	CLLossBCurrEnd_BPosAcEn_1          4       /*上1次B相失流发生时刻B相正向有功电能*/
#define	CLLossBCurrEnd_BRevAcEn_1          4       /*上1次B相失流发生时刻B相反向有功电能*/
#define	CLLossBCurrEnd_BComRe1En_1         4       /*上1次B相失流结束时刻B相组合无功1电能*/
#define	CLLossBCurrEnd_BComRe2En_1         4       /*上1次B相失流结束时刻B相组合无功2电能*/
#define	CLLossBCurrEnd_CPosAcEn_1          4       /*上1次B相失流发生时刻C相正向有功电能*/
#define	CLLossBCurrEnd_CRevAcEn_1          4       /*上1次B相失流发生时刻C相反向有功电能*/
#define	CLLossBCurrEnd_CComRe1En_1         4       /*上1次B相失流结束时刻C相组合无功1电能*/
#define	CLLossBCurrEnd_CComRe2En_1         4       /*上1次B相失流结束时刻C相组合无功2电能*/
#define	CLLossBCurr_FF_1                   179     /*上1次B相失流数据块*/
#define	CLLossBCurr_HpData_1               109     /*上1次B相失流发生数据*/
#define	CLLossBCurr_EndData_1              70      /*上1次B相失流结束数据*/

/*********C相**********/
/*上2次-上10次 C相失流 事件记录数据长度 同上1次*/
#define	CLLossC_Curr_Hp_1                  6       /*上1次C相失流发生时刻*/
#define	CLLossCCurrHp_PosAcTolEn_1         4       /*上1次C相失流发生时刻正向有功总电能*/
#define	CLLossCCurrHp_RevAcTolEn_1         4       /*上1次C相失流发生时刻反向有功总电能*/
#define	CLLossCCurrHp_ComRe1TolEn_1        4       /*上1次C相失流发生时刻组合无功1总电能*/
#define	CLLossCCurrHp_ComRe2TolEn_1        4       /*上1次C相失流发生时刻组合无功2总电能*/
#define	CLLossCCurrHp_APosAcEn_1           4       /*上1次C相失流发生时刻A相正向有功电能*/
#define	CLLossCCurrHp_ARevAcEn_1           4       /*上1次C相失流发生时刻A相反向有功电能*/
#define	CLLossCCurrHp_AComRe1En_1          4       /*上1次C相失流发生时刻A相组合无功1总电能*/
#define	CLLossCCurrHp_AComRe2En_1          4       /*上1次C相失流发生时刻A相组合无功2总电能*/
#define	CLLossCCurrHp_AVol_1               2       /*上1次C相失流发生时刻A相电压*/
#define	CLLossCCurrHp_ACurr_1              3       /*上1次C相失流发生时刻A相电流*/
#define	CLLossCCurrHp_AAcP_1               3       /*上1次C相失流发生时刻A相有功功率*/
#define	CLLossCCurrHp_AReP_1               3       /*上1次C相失流发生时刻A相无功功率*/
#define	CLLossCCurrHp_APF_1                2       /*上1次C相失流发生时刻A相功率因数*/
#define	CLLossCCurrHp_BPosAcEn_1           4       /*上1次C相失流发生时刻B相正向有功电能*/
#define	CLLossCCurrHp_BRevAcEn_1           4       /*上1次C相失流发生时刻B相反向有功电能*/
#define	CLLossCCurrHp_BComRe1En_1          4       /*上1次C相失流发生时刻B相组合无功1总电能*/
#define	CLLossCCurrHp_BComRe2En_1          4       /*上1次C相失流发生时刻B相组合无功2总电能*/
#define	CLLossCCurrHp_BVol_1               2       /*上1次C相失流发生时刻B相电压*/
#define	CLLossCCurrHp_BCurr_1              3       /*上1次C相失流发生时刻B相电流*/
#define	CLLossCCurrHp_BAcP_1               3       /*上1次C相失流发生时刻B相有功功率*/
#define	CLLossCCurrHp_BReP_1               3       /*上1次C相失流发生时刻B相无功功率*/
#define	CLLossCCurrHp_BPF_1                2       /*上1次C相失流发生时刻B相功率因数*/
#define	CLLossCCurrHp_CPosAcEn_1           4       /*上1次C相失流发生时刻C相正向有功电能*/
#define	CLLossCCurrHp_CRevAcEn_1           4       /*上1次C相失流发生时刻C相反向有功电能*/
#define	CLLossCCurrHp_CComRe1En_1          4       /*上1次C相失流发生时刻C相组合无功1总电能*/
#define	CLLossCCurrHp_CComRe2En_1          4       /*上1次C相失流发生时刻C相组合无功2总电能*/
#define	CLLossCCurrHp_CVol_1               2       /*上1次C相失流发生时刻C相电压*/
#define	CLLossCCurrHp_CCurr_1              3       /*上1次C相失流发生时刻C相电流*/
#define	CLLossCCurrHp_CAcP_1               3       /*上1次C相失流发生时刻C相有功功率*/
#define	CLLossCCurrHp_CReP_1               3       /*上1次C相失流发生时刻C相无功功率*/
#define	CLLossCCurrHp_CPF_1                2       /*上1次C相失流发生时刻C相功率因数*/
#define	CLLossC_Curr_End_1	               6       /*上1次C相失流结束时刻*/
#define	CLLossCCurrEnd_PosAcTolEn_1        4       /*上1次C相失流结束时刻正向有功总电能*/
#define	CLLossCCurrEnd_RevAcTolEn_1        4       /*上1次C相失流结束时刻反向有功总电能*/
#define	CLLossCCurrEnd_ComRe1TolEn_1       4       /*上1次C相失流结束时刻组合无功1总电能*/
#define	CLLossCCurrEnd_ComRe2TolEn_1       4       /*上1次C相失流结束时刻组合无功2总电能*/
#define	CLLossCCurrEnd_APosAcEn_1          4       /*上1次C相失流结束时刻A相正向有功电能*/
#define	CLLossCCurrEnd_ARevAcEn_1          4       /*上1次C相失流结束时刻A相反向有功电能*/
#define	CLLossCCurrEnd_AComRe1En_1         4       /*上1次C相失流结束时刻A相组合无功1电能*/
#define	CLLossCCurrEnd_AComRe2En_1         4       /*上1次C相失流结束时刻A相组合无功2电能*/
#define	CLLossCCurrEnd_BPosAcEn_1          4       /*上1次C相失流发生时刻B相正向有功电能*/
#define	CLLossCCurrEnd_BRevAcEn_1          4       /*上1次C相失流发生时刻B相反向有功电能*/
#define	CLLossCCurrEnd_BComRe1En_1         4       /*上1次C相失流结束时刻B相组合无功1电能*/
#define	CLLossCCurrEnd_BComRe2En_1         4       /*上1次C相失流结束时刻B相组合无功2电能*/
#define	CLLossCCurrEnd_CPosAcEn_1          4       /*上1次C相失流发生时刻C相正向有功电能*/
#define	CLLossCCurrEnd_CRevAcEn_1          4       /*上1次C相失流发生时刻C相反向有功电能*/
#define	CLLossCCurrEnd_CComRe1En_1         4       /*上1次C相失流结束时刻C相组合无功1电能*/
#define	CLLossCCurrEnd_CComRe2En_1         4       /*上1次C相失流结束时刻C相组合无功2电能*/
#define	CLLossCCurr_FF_1                   179     /*上1次C相失流数据块*/
#define	CLLossCCurr_HpData_1               109     /*上1次C相失流发生数据*/
#define	CLLossCCurr_EndData_1              70      /*上1次C相失流结束数据*/

/**********过流************/
/*698相关定义*/
#define CLOverA_Curr_Current               8       /*A相过流事件当前值记录表*/
#define CLOverA_Curr_Degree                4       /*A相过流事件发生次数*/
#define CLOverA_Curr_Time                  4       /*A相过流事件累计时间*/

#define CLOverB_Curr_Current               8       /*B相过流事件当前值记录表*/
#define CLOverB_Curr_Degree                4       /*B相过流事件发生次数*/
#define CLOverB_Curr_Time                  4       /*B相过流事件累计时间*/

#define CLOverC_Curr_Current               8       /*C相过流事件当前值记录表*/
#define CLOverC_Curr_Degree                4       /*C相过流事件发生次数*/
#define CLOverC_Curr_Time                  4       /*C相过流事件累计时间*/

/*645相关定义*/
/*******A相******/
/*上2次-上10次 A相过流 事件记录数据长度 同上1次*/
#define	CLOverA_Curr_Hp_1                  6       /*上1次A相过流发生时刻*/
#define	CLOverACurrHp_PosAcTolEn_1         4       /*上1次A相过流发生时刻正向有功总电能*/
#define	CLOverACurrHp_RevAcTolEn_1         4       /*上1次A相过流发生时刻反向有功总电能*/
#define	CLOverACurrHp_ComRe1TolEn_1        4       /*上1次A相过流发生时刻组合无功1总电能*/*/
#define	CLOverACurrHp_ComRe2TolEn_1        4       /*上1次A相过流发生时刻组合无功2总电能*/
#define	CLOverACurrHp_APosAcEn_1           4       /*上1次A相过流发生时刻A相正向有功电能*/
#define	CLOverACurrHp_ARevAcEn_1           4       /*上1次A相过流发生时刻A相反向有功电能*/
#define	CLOverACurrHp_AComRe1En_1          4       /*上1次A相过流发生时刻A相组合无功1总电能*/
#define	CLOverACurrHp_AComRe2En_1          4       /*上1次A相过流发生时刻A相组合无功2总电能*/
#define	CLOverACurrHp_AVol_1               2       /*上1次A相过流发生时刻A相电压*/
#define	CLOverACurrHp_ACurr_1              3       /*上1次A相过流发生时刻A相电流*/
#define	CLOverACurrHp_AAcP_1               3       /*上1次A相过流发生时刻A相有功功率*/
#define	CLOverACurrHp_AReP_1               3       /*上1次A相过流发生时刻A相无功功率*/
#define	CLOverACurrHp_APF_1                2       /*上1次A相过流发生时刻A相功率因数*/
#define	CLOverACurrHp_BPosAcEn_1           4       /*上1次A相过流发生时刻B相正向有功电能*/
#define	CLOverACurrHp_BRevAcEn_1           4       /*上1次A相过流发生时刻B相反向有功电能*/
#define	CLOverACurrHp_BComRe1En_1          4       /*上1次A相过流发生时刻B相组合无功1总电能*/
#define	CLOverACurrHp_BComRe2En_1          4       /*上1次A相过流发生时刻B相组合无功2总电能*/
#define	CLOverACurrHp_BVol_1               2       /*上1次A相过流发生时刻B相电压*/
#define	CLOverACurrHp_BCurr_1              3       /*上1次A相过流发生时刻B相电流*/
#define	CLOverACurrHp_BAcP_1               3       /*上1次A相过流发生时刻B相有功功率*/
#define	CLOverACurrHp_BReP_1               3       /*上1次A相过流发生时刻B相无功功率*/
#define	CLOverACurrHp_BPF_1                2       /*上1次A相过流发生时刻B相功率因数*/
#define	CLOverACurrHp_CPosAcEn_1           4       /*上1次A相过流发生时刻C相正向有功电能*/
#define	CLOverACurrHp_CRevAcEn_1           4       /*上1次A相过流发生时刻C相反向有功电能*/
#define	CLOverACurrHp_CComRe1En_1          4       /*上1次A相过流发生时刻C相组合无功1总电能*/
#define	CLOverACurrHp_CComRe2En_1          4       /*上1次A相过流发生时刻C相组合无功2总电能*/
#define	CLOverACurrHp_CVol_1               2       /*上1次A相过流发生时刻C相电压*/
#define	CLOverACurrHp_CCurr_1              3       /*上1次A相过流发生时刻C相电流*/
#define	CLOverACurrHp_CAcP_1               3       /*上1次A相过流发生时刻C相有功功率*/
#define	CLOverACurrHp_CReP_1               3       /*上1次A相过流发生时刻C相无功功率*/
#define	CLOverACurrHp_CPF_1                2       /*上1次A相过流发生时刻C相功率因数*/
#define	CLOverA_Curr_End_1                 6       /*上1次A相过流结束时刻*/
#define	CLOverACurrEnd_PosAcTolEn_1        4       /*上1次A相过流结束时刻正向有功总电能*/
#define	CLOverACurrEnd_RevAcTolEn_1        4       /*上1次A相过流结束时刻反向有功总电能*/
#define	CLOverACurrEnd_ComRe1TolEn_1       4       /*上1次A相过流结束时刻组合无功1总电能*/
#define	CLOverACurrEnd_ComRe2TolEn_1       4       /*上1次A相过流结束时刻组合无功2总电能*/
#define	CLOverACurrEnd_APosAcEn_1          4       /*上1次A相过流结束时刻A相正向有功电能*/
#define	CLOverACurrEnd_ARevAcEn_1          4       /*上1次A相过流结束时刻A相反向有功电能*/
#define	CLOverACurrEnd_AComRe1En_1         4       /*上1次A相过流结束时刻A相组合无功1电能*/
#define	CLOverACurrEnd_AComRe2En_1         4       /*上1次A相过流结束时刻A相组合无功2电能*/
#define	CLOverACurrEnd_BPosAcEn_1          4       /*上1次A相过流发生时刻B相正向有功电能*/
#define	CLOverACurrEnd_BRevAcEn_1          4       /*上1次A相过流发生时刻B相反向有功电能*/
#define	CLOverACurrEnd_BComRe1En_1         4       /*上1次A相过流结束时刻B相组合无功1电能*/
#define	CLOverACurrEnd_BComRe2En_1         4       /*上1次A相过流结束时刻B相组合无功2电能*/
#define	CLOverACurrEnd_CPosAcEn_1          4       /*上1次A相过流发生时刻C相正向有功电能*/
#define	CLOverACurrEnd_CRevAcEn_1          4       /*上1次A相过流发生时刻C相反向有功电能*/
#define	CLOverACurrEnd_CComRe1En_1         4       /*上1次A相过流结束时刻C相组合无功1电能*/
#define	CLOverACurrEnd_CComRe2En_1         4       /*上1次A相过流结束时刻C相组合无功2电能*/
#define	CLOverACurr_FF_1                   179     /*上1次A相过流数据块*/
#define	CLOverACurr_HpData_1               109     /*上1次A相过流发生数据*/
#define	CLOverACurr_EndData_1              70      /*上1次A相过流结束数据*/

/*********B相**********/
/*上2次-上10次 B相过流 事件记录数据长度 同上1次*/
#define	CLOverB_Curr_Hp_1                  6       /*上1次B相过流发生时刻*/
#define	CLOverBCurrHp_PosAcTolEn_1         4       /*上1次B相过流发生时刻正向有功总电能*/
#define	CLOverBCurrHp_RevAcTolEn_1         4       /*上1次B相过流发生时刻反向有功总电能*/
#define	CLOverBCurrHp_ComRe1TolEn_1        4       /*上1次B相过流发生时刻组合无功1总电能*/
#define	CLOverBCurrHp_ComRe2TolEn_1        4       /*上1次B相过流发生时刻组合无功2总电能*/
#define	CLOverBCurrHp_APosAcEn_1           4       /*上1次B相过流发生时刻A相正向有功电能*/
#define	CLOverBCurrHp_ARevAcEn_1           4       /*上1次B相过流发生时刻A相反向有功电能*/
#define	CLOverBCurrHp_AComRe1En_1          4       /*上1次B相过流发生时刻A相组合无功1总电能*/
#define	CLOverBCurrHp_AComRe2En_1          4       /*上1次B相过流发生时刻A相组合无功2总电能*/
#define	CLOverBCurrHp_AVol_1               2       /*上1次B相过流发生时刻A相电压*/
#define	CLOverBCurrHp_ACurr_1              3       /*上1次B相过流发生时刻A相电流*/
#define	CLOverBCurrHp_AAcP_1               3       /*上1次B相过流发生时刻A相有功功率*/
#define	CLOverBCurrHp_AReP_1               3       /*上1次B相过流发生时刻A相无功功率*/
#define	CLOverBCurrHp_APF_1                2       /*上1次B相过流发生时刻A相功率因数*/
#define	CLOverBCurrHp_BPosAcEn_1           4       /*上1次B相过流发生时刻B相正向有功电能*/
#define	CLOverBCurrHp_BRevAcEn_1           4       /*上1次B相过流发生时刻B相反向有功电能*/
#define	CLOverBCurrHp_BComRe1En_1          4       /*上1次B相过流发生时刻B相组合无功1总电能*/
#define	CLOverBCurrHp_BComRe2En_1          4       /*上1次B相过流发生时刻B相组合无功2总电能*/
#define	CLOverBCurrHp_BVol_1               2       /*上1次B相过流发生时刻B相电压*/
#define	CLOverBCurrHp_BCurr_1              3       /*上1次B相过流发生时刻B相电流*/
#define	CLOverBCurrHp_BAcP_1               3       /*上1次B相过流发生时刻B相有功功率*/
#define	CLOverBCurrHp_BReP_1               3       /*上1次B相过流发生时刻B相无功功率*/
#define	CLOverBCurrHp_BPF_1                2       /*上1次B相过流发生时刻B相功率因数*/
#define	CLOverBCurrHp_CPosAcEn_1           4       /*上1次B相过流发生时刻C相正向有功电能*/
#define	CLOverBCurrHp_CRevAcEn_1           4       /*上1次B相过流发生时刻C相反向有功电能*/
#define	CLOverBCurrHp_CComRe1En_1          4       /*上1次B相过流发生时刻C相组合无功1总电能*/
#define	CLOverBCurrHp_CComRe2En_1          4       /*上1次B相过流发生时刻C相组合无功2总电能*/
#define	CLOverBCurrHp_CVol_1               2       /*上1次B相过流发生时刻C相电压*/
#define	CLOverBCurrHp_CCurr_1              3       /*上1次B相过流发生时刻C相电流*/
#define	CLOverBCurrHp_CAcP_1               3       /*上1次B相过流发生时刻C相有功功率*/
#define	CLOverBCurrHp_CReP_1               3       /*上1次B相过流发生时刻C相无功功率*/
#define	CLOverBCurrHp_CPF_1                2       /*上1次B相过流发生时刻C相功率因数*/
#define	CLOverB_Curr_End_1	               6       /*上1次B相过流结束时刻*/
#define	CLOverBCurrEnd_PosAcTolEn_1        4       /*上1次B相过流结束时刻正向有功总电能*/
#define	CLOverBCurrEnd_RevAcTolEn_1        4       /*上1次B相过流结束时刻反向有功总电能*/
#define	CLOverBCurrEnd_ComRe1TolEn_1       4       /*上1次B相过流结束时刻组合无功1总电能*/
#define	CLOverBCurrEnd_ComRe2TolEn_1       4       /*上1次B相过流结束时刻组合无功2总电能*/
#define	CLOverBCurrEnd_APosAcEn_1          4       /*上1次B相过流结束时刻A相正向有功电能*/
#define	CLOverBCurrEnd_ARevAcEn_1          4       /*上1次B相过流结束时刻A相反向有功电能*/
#define	CLOverBCurrEnd_AComRe1En_1         4       /*上1次B相过流结束时刻A相组合无功1电能*/
#define	CLOverBCurrEnd_AComRe2En_1         4       /*上1次B相过流结束时刻A相组合无功2电能*/
#define	CLOverBCurrEnd_BPosAcEn_1          4       /*上1次B相过流发生时刻B相正向有功电能*/
#define	CLOverBCurrEnd_BRevAcEn_1          4       /*上1次B相过流发生时刻B相反向有功电能*/
#define	CLOverBCurrEnd_BComRe1En_1         4       /*上1次B相过流结束时刻B相组合无功1电能*/
#define	CLOverBCurrEnd_BComRe2En_1         4       /*上1次B相过流结束时刻B相组合无功2电能*/
#define	CLOverBCurrEnd_CPosAcEn_1          4       /*上1次B相过流发生时刻C相正向有功电能*/
#define	CLOverBCurrEnd_CRevAcEn_1          4       /*上1次B相过流发生时刻C相反向有功电能*/
#define	CLOverBCurrEnd_CComRe1En_1         4       /*上1次B相过流结束时刻C相组合无功1电能*/
#define	CLOverBCurrEnd_CComRe2En_1         4       /*上1次B相过流结束时刻C相组合无功2电能*/
#define	CLOverBCurr_FF_1                   179     /*上1次B相过流数据块*/
#define	CLOverBCurr_HpData_1               109     /*上1次B相过流发生数据*/
#define	CLOverBCurr_EndData_1              70      /*上1次B相过流结束数据*/

/*********C相**********/
/*上2次-上10次 C相过流 事件记录数据长度 同上1次*/
#define	CLOverC_Curr_Hp_1                  6       /*上1次C相过流发生时刻*/
#define	CLOverCCurrHp_PosAcTolEn_1         4       /*上1次C相过流发生时刻正向有功总电能*/
#define	CLOverCCurrHp_RevAcTolEn_1         4       /*上1次C相过流发生时刻反向有功总电能*/
#define	CLOverCCurrHp_ComRe1TolEn_1        4       /*上1次C相过流发生时刻组合无功1总电能*/
#define	CLOverCCurrHp_ComRe2TolEn_1        4       /*上1次C相过流发生时刻组合无功2总电能*/
#define	CLOverCCurrHp_APosAcEn_1           4       /*上1次C相过流发生时刻A相正向有功电能*/
#define	CLOverCCurrHp_ARevAcEn_1           4       /*上1次C相过流发生时刻A相反向有功电能*/
#define	CLOverCCurrHp_AComRe1En_1          4       /*上1次C相过流发生时刻A相组合无功1总电能*/
#define	CLOverCCurrHp_AComRe2En_1          4       /*上1次C相过流发生时刻A相组合无功2总电能*/
#define	CLOverCCurrHp_AVol_1               2       /*上1次C相过流发生时刻A相电压*/
#define	CLOverCCurrHp_ACurr_1              3       /*上1次C相过流发生时刻A相电流*/
#define	CLOverCCurrHp_AAcP_1               3       /*上1次C相过流发生时刻A相有功功率*/
#define	CLOverCCurrHp_AReP_1               3       /*上1次C相过流发生时刻A相无功功率*/
#define	CLOverCCurrHp_APF_1                2       /*上1次C相过流发生时刻A相功率因数*/
#define	CLOverCCurrHp_BPosAcEn_1           4       /*上1次C相过流发生时刻B相正向有功电能*/
#define	CLOverCCurrHp_BRevAcEn_1           4       /*上1次C相过流发生时刻B相反向有功电能*/
#define	CLOverCCurrHp_BComRe1En_1          4       /*上1次C相过流发生时刻B相组合无功1总电能*/
#define	CLOverCCurrHp_BComRe2En_1          4       /*上1次C相过流发生时刻B相组合无功2总电能*/
#define	CLOverCCurrHp_BVol_1               2       /*上1次C相过流发生时刻B相电压*/
#define	CLOverCCurrHp_BCurr_1              3       /*上1次C相过流发生时刻B相电流*/
#define	CLOverCCurrHp_BAcP_1               3       /*上1次C相过流发生时刻B相有功功率*/
#define	CLOverCCurrHp_BReP_1               3       /*上1次C相过流发生时刻B相无功功率*/
#define	CLOverCCurrHp_BPF_1                2       /*上1次C相过流发生时刻B相功率因数*/
#define	CLOverCCurrHp_CPosAcEn_1           4       /*上1次C相过流发生时刻C相正向有功电能*/
#define	CLOverCCurrHp_CRevAcEn_1           4       /*上1次C相过流发生时刻C相反向有功电能*/
#define	CLOverCCurrHp_CComRe1En_1          4       /*上1次C相过流发生时刻C相组合无功1总电能*/
#define	CLOverCCurrHp_CComRe2En_1          4       /*上1次C相过流发生时刻C相组合无功2总电能*/
#define	CLOverCCurrHp_CVol_1               2       /*上1次C相过流发生时刻C相电压*/
#define	CLOverCCurrHp_CCurr_1              3       /*上1次C相过流发生时刻C相电流*/
#define	CLOverCCurrHp_CAcP_1               3       /*上1次C相过流发生时刻C相有功功率*/
#define	CLOverCCurrHp_CReP_1               3       /*上1次C相过流发生时刻C相无功功率*/
#define	CLOverCCurrHp_CPF_1                2       /*上1次C相过流发生时刻C相功率因数*/
#define	CLOverC_Curr_End_1	               6       /*上1次C相过流结束时刻*/
#define	CLOverCCurrEnd_PosAcTolEn_1        4       /*上1次C相过流结束时刻正向有功总电能*/
#define	CLOverCCurrEnd_RevAcTolEn_1        4       /*上1次C相过流结束时刻反向有功总电能*/
#define	CLOverCCurrEnd_ComRe1TolEn_1       4       /*上1次C相过流结束时刻组合无功1总电能*/
#define	CLOverCCurrEnd_ComRe2TolEn_1       4       /*上1次C相过流结束时刻组合无功2总电能*/
#define	CLOverCCurrEnd_APosAcEn_1          4       /*上1次C相过流结束时刻A相正向有功电能*/
#define	CLOverCCurrEnd_ARevAcEn_1          4       /*上1次C相过流结束时刻A相反向有功电能*/
#define	CLOverCCurrEnd_AComRe1En_1         4       /*上1次C相过流结束时刻A相组合无功1电能*/
#define	CLOverCCurrEnd_AComRe2En_1         4       /*上1次C相过流结束时刻A相组合无功2电能*/
#define	CLOverCCurrEnd_BPosAcEn_1          4       /*上1次C相过流发生时刻B相正向有功电能*/
#define	CLOverCCurrEnd_BRevAcEn_1          4       /*上1次C相过流发生时刻B相反向有功电能*/
#define	CLOverCCurrEnd_BComRe1En_1         4       /*上1次C相过流结束时刻B相组合无功1电能*/
#define	CLOverCCurrEnd_BComRe2En_1         4       /*上1次C相过流结束时刻B相组合无功2电能*/
#define	CLOverCCurrEnd_CPosAcEn_1          4       /*上1次C相过流发生时刻C相正向有功电能*/
#define	CLOverCCurrEnd_CRevAcEn_1          4       /*上1次C相过流发生时刻C相反向有功电能*/
#define	CLOverCCurrEnd_CComRe1En_1         4       /*上1次C相过流结束时刻C相组合无功1电能*/
#define	CLOverCCurrEnd_CComRe2En_1         4       /*上1次C相过流结束时刻C相组合无功2电能*/
#define	CLOverCCurr_FF_1                   179     /*上1次C相过流数据块*/
#define	CLOverCCurr_HpData_1               109     /*上1次C相过流发生数据*/
#define	CLOverCCurr_EndData_1              70      /*上1次C相过流结束数据*/

/**********断流************/
/*698相关定义*/
#define CLBreakA_Curr_Current              8       /*A相断流事件当前值记录表*/
#define CLBreakA_Curr_Degree               4       /*A相断流事件发生次数*/
#define CLBreakA_Curr_Time                 4       /*A相断流事件累计时间*/

#define CLBreakB_Curr_Current              8       /*B相断流事件当前值记录表*/
#define CLBreakB_Curr_Degree               4       /*B相断流事件发生次数*/
#define CLBreakB_Curr_Time                 4       /*B相断流事件累计时间*/

#define CLBreakC_Curr_Current              8       /*C相断流事件当前值记录表*/
#define CLBreakC_Curr_Degree               4       /*C相断流事件发生次数*/
#define CLBreakC_Curr_Time                 4       /*C相断流事件累计时间*/

/*645相关定义*/
/*******A相******/
/*上2次-上10次 A相断流 事件记录数据长度 同上1次*/
#define	CLBreakA_Curr_Hp_1                 6       /*上1次A相断流发生时刻*/
#define	CLBreakACurrHp_PosAcTolEn_1        4       /*上1次A相断流发生时刻正向有功总电能*/
#define	CLBreakACurrHp_RevAcTolEn_1        4       /*上1次A相断流发生时刻反向有功总电能*/
#define	CLBreakACurrHp_ComRe1TolEn_1       4       /*上1次A相断流发生时刻组合无功1总电能*/
#define	CLBreakACurrHp_ComRe2TolEn_1       4       /*上1次A相断流发生时刻组合无功2总电能*/
#define	CLBreakACurrHp_APosAcEn_1          4       /*上1次A相断流发生时刻A相正向有功电能*/
#define	CLBreakACurrHp_ARevAcEn_1          4       /*上1次A相断流发生时刻A相反向有功电能*/
#define	CLBreakACurrHp_AComRe1En_1         4       /*上1次A相断流发生时刻A相组合无功1总电能*/
#define	CLBreakACurrHp_AComRe2En_1         4       /*上1次A相断流发生时刻A相组合无功2总电能*/
#define	CLBreakACurrHp_AVol_1              2       /*上1次A相断流发生时刻A相电压*/
#define	CLBreakACurrHp_ACurr_1             3       /*上1次A相断流发生时刻A相电流*/
#define	CLBreakACurrHp_AAcP_1              3       /*上1次A相断流发生时刻A相有功功率*/
#define	CLBreakACurrHp_AReP_1              3       /*上1次A相断流发生时刻A相无功功率*/
#define	CLBreakACurrHp_APF_1               2       /*上1次A相断流发生时刻A相功率因数*/
#define	CLBreakACurrHp_BPosAcEn_1          4       /*上1次A相断流发生时刻B相正向有功电能*/
#define	CLBreakACurrHp_BRevAcEn_1          4       /*上1次A相断流发生时刻B相反向有功电能*/
#define	CLBreakACurrHp_BComRe1En_1         4       /*上1次A相断流发生时刻B相组合无功1总电能*/
#define	CLBreakACurrHp_BComRe2En_1         4       /*上1次A相断流发生时刻B相组合无功2总电能*/
#define	CLBreakACurrHp_BVol_1              2       /*上1次A相断流发生时刻B相电压*/
#define	CLBreakACurrHp_BCurr_1             3       /*上1次A相断流发生时刻B相电流*/
#define	CLBreakACurrHp_BAcP_1              3       /*上1次A相断流发生时刻B相有功功率*/
#define	CLBreakACurrHp_BReP_1              3       /*上1次A相断流发生时刻B相无功功率*/
#define	CLBreakACurrHp_BPF_1               2       /*上1次A相断流发生时刻B相功率因数*/
#define	CLBreakACurrHp_CPosAcEn_1          4       /*上1次A相断流发生时刻C相正向有功电能*/
#define	CLBreakACurrHp_CRevAcEn_1          4       /*上1次A相断流发生时刻C相反向有功电能*/
#define	CLBreakACurrHp_CComRe1En_1         4       /*上1次A相断流发生时刻C相组合无功1总电能*/
#define	CLBreakACurrHp_CComRe2En_1         4       /*上1次A相断流发生时刻C相组合无功2总电能*/
#define	CLBreakACurrHp_CVol_1              2       /*上1次A相断流发生时刻C相电压*/
#define	CLBreakACurrHp_CCurr_1             3       /*上1次A相断流发生时刻C相电流*/
#define	CLBreakACurrHp_CAcP_1              3       /*上1次A相断流发生时刻C相有功功率*/
#define	CLBreakACurrHp_CReP_1              3       /*上1次A相断流发生时刻C相无功功率*/
#define	CLBreakACurrHp_CPF_1               2       /*上1次A相断流发生时刻C相功率因数*/
#define	CLBreakA_Curr_End_1	               6       /*上1次A相断流结束时刻*/
#define	CLBreakACurrEnd_PosAcTolEn_1       4       /*上1次A相断流结束时刻正向有功总电能*/
#define	CLBreakACurrEnd_RevAcTolEn_1       4       /*上1次A相断流结束时刻反向有功总电能*/
#define	CLBreakACurrEnd_ComRe1TolEn_1      4       /*上1次A相断流结束时刻组合无功1总电能*/
#define	CLBreakACurrEnd_ComRe2TolEn_1      4       /*上1次A相断流结束时刻组合无功2总电能*/
#define	CLBreakACurrEnd_APosAcEn_1         4       /*上1次A相断流结束时刻A相正向有功电能*/
#define	CLBreakACurrEnd_ARevAcEn_1         4       /*上1次A相断流结束时刻A相反向有功电能*/
#define	CLBreakACurrEnd_AComRe1En_1        4       /*上1次A相断流结束时刻A相组合无功1电能*/
#define	CLBreakACurrEnd_AComRe2En_1        4       /*上1次A相断流结束时刻A相组合无功2电能*/
#define	CLBreakACurrEnd_BPosAcEn_1         4       /*上1次A相断流发生时刻B相正向有功电能*/
#define	CLBreakACurrEnd_BRevAcEn_1         4       /*上1次A相断流发生时刻B相反向有功电能*/
#define	CLBreakACurrEnd_BComRe1En_1        4       /*上1次A相断流结束时刻B相组合无功1电能*/
#define	CLBreakACurrEnd_BComRe2En_1        4       /*上1次A相断流结束时刻B相组合无功2电能*/
#define	CLBreakACurrEnd_CPosAcEn_1         4       /*上1次A相断流发生时刻C相正向有功电能*/
#define	CLBreakACurrEnd_CRevAcEn_1         4       /*上1次A相断流发生时刻C相反向有功电能*/
#define	CLBreakACurrEnd_CComRe1En_1        4       /*上1次A相断流结束时刻C相组合无功1电能*/
#define	CLBreakACurrEnd_CComRe2En_1        4       /*上1次A相断流结束时刻C相组合无功2电能*/
#define	CLBreakACurr_FF_1                  179     /*上1次A相断流数据块*/
#define	CLBreakACurr_HpData_1              109     /*上1次A相断流发生数据*/
#define	CLBreakACurr_EndData_1             70      /*上1次A相断流结束数据*/

/*********B相**********/
/*上2次-上10次 B相断流 事件记录数据长度 同上1次*/
#define	CLBreakB_Curr_Hp_1                 6       /*上1次B相断流发生时刻*/
#define	CLBreakBCurrHp_PosAcTolEn_1        4       /*上1次B相断流发生时刻正向有功总电能*/
#define	CLBreakBCurrHp_RevAcTolEn_1        4       /*上1次B相断流发生时刻反向有功总电能*/
#define	CLBreakBCurrHp_ComRe1TolEn_1       4       /*上1次B相断流发生时刻组合无功1总电能*/
#define	CLBreakBCurrHp_ComRe2TolEn_1       4       /*上1次B相断流发生时刻组合无功2总电能*/
#define	CLBreakBCurrHp_APosAcEn_1          4       /*上1次B相断流发生时刻A相正向有功电能*/
#define	CLBreakBCurrHp_ARevAcEn_1          4       /*上1次B相断流发生时刻A相反向有功电能*/
#define	CLBreakBCurrHp_AComRe1En_1         4       /*上1次B相断流发生时刻A相组合无功1总电能*/
#define	CLBreakBCurrHp_AComRe2En_1         4       /*上1次B相断流发生时刻A相组合无功2总电能*/
#define	CLBreakBCurrHp_AVol_1              2       /*上1次B相断流发生时刻A相电压*/
#define	CLBreakBCurrHp_ACurr_1             3       /*上1次B相断流发生时刻A相电流*/
#define	CLBreakBCurrHp_AAcP_1              3       /*上1次B相断流发生时刻A相有功功率*/
#define	CLBreakBCurrHp_AReP_1              3       /*上1次B相断流发生时刻A相无功功率*/
#define	CLBreakBCurrHp_APF_1               2       /*上1次B相断流发生时刻A相功率因数*/
#define	CLBreakBCurrHp_BPosAcEn_1          4       /*上1次B相断流发生时刻B相正向有功电能*/
#define	CLBreakBCurrHp_BRevAcEn_1          4       /*上1次B相断流发生时刻B相反向有功电能*/
#define	CLBreakBCurrHp_BComRe1En_1         4       /*上1次B相断流发生时刻B相组合无功1总电能*/
#define	CLBreakBCurrHp_BComRe2En_1         4       /*上1次B相断流发生时刻B相组合无功2总电能*/
#define	CLBreakBCurrHp_BVol_1              2       /*上1次B相断流发生时刻B相电压*/
#define	CLBreakBCurrHp_BCurr_1             3       /*上1次B相断流发生时刻B相电流*/
#define	CLBreakBCurrHp_BAcP_1              3       /*上1次B相断流发生时刻B相有功功率*/
#define	CLBreakBCurrHp_BReP_1              3       /*上1次B相断流发生时刻B相无功功率*/
#define	CLBreakBCurrHp_BPF_1               2       /*上1次B相断流发生时刻B相功率因数*/
#define	CLBreakBCurrHp_CPosAcEn_1          4       /*上1次B相断流发生时刻C相正向有功电能*/
#define	CLBreakBCurrHp_CRevAcEn_1          4       /*上1次B相断流发生时刻C相反向有功电能*/
#define	CLBreakBCurrHp_CComRe1En_1         4       /*上1次B相断流发生时刻C相组合无功1总电能*/
#define	CLBreakBCurrHp_CComRe2En_1         4       /*上1次B相断流发生时刻C相组合无功2总电能*/
#define	CLBreakBCurrHp_CVol_1              2       /*上1次B相断流发生时刻C相电压*/
#define	CLBreakBCurrHp_CCurr_1             3       /*上1次B相断流发生时刻C相电流*/
#define	CLBreakBCurrHp_CAcP_1              3       /*上1次B相断流发生时刻C相有功功率*/
#define	CLBreakBCurrHp_CReP_1              3       /*上1次B相断流发生时刻C相无功功率*/
#define	CLBreakBCurrHp_CPF_1               2       /*上1次B相断流发生时刻C相功率因数*/
#define	CLBreakB_Curr_End_1                6       /*上1次B相断流结束时刻*/
#define	CLBreakBCurrEnd_PosAcTolEn_1       4       /*上1次B相断流结束时刻正向有功总电能*/
#define	CLBreakBCurrEnd_RevAcTolEn_1       4       /*上1次B相断流结束时刻反向有功总电能*/
#define	CLBreakBCurrEnd_ComRe1TolEn_1      4       /*上1次B相断流结束时刻组合无功1总电能*/
#define	CLBreakBCurrEnd_ComRe2TolEn_1      4       /*上1次B相断流结束时刻组合无功2总电能*/
#define	CLBreakBCurrEnd_APosAcEn_1         4       /*上1次B相断流结束时刻A相正向有功电能*/
#define	CLBreakBCurrEnd_ARevAcEn_1         4       /*上1次B相断流结束时刻A相反向有功电能*/
#define	CLBreakBCurrEnd_AComRe1En_1        4       /*上1次B相断流结束时刻A相组合无功1电能*/
#define	CLBreakBCurrEnd_AComRe2En_1        4       /*上1次B相断流结束时刻A相组合无功2电能*/
#define	CLBreakBCurrEnd_BPosAcEn_1         4       /*上1次B相断流发生时刻B相正向有功电能*/
#define	CLBreakBCurrEnd_BRevAcEn_1         4       /*上1次B相断流发生时刻B相反向有功电能*/
#define	CLBreakBCurrEnd_BComRe1En_1        4       /*上1次B相断流结束时刻B相组合无功1电能*/
#define	CLBreakBCurrEnd_BComRe2En_1        4       /*上1次B相断流结束时刻B相组合无功2电能*/
#define	CLBreakBCurrEnd_CPosAcEn_1         4       /*上1次B相断流发生时刻C相正向有功电能*/
#define	CLBreakBCurrEnd_CRevAcEn_1         4       /*上1次B相断流发生时刻C相反向有功电能*/
#define	CLBreakBCurrEnd_CComRe1En_1        4       /*上1次B相断流结束时刻C相组合无功1电能*/
#define	CLBreakBCurrEnd_CComRe2En_1        4       /*上1次B相断流结束时刻C相组合无功2电能*/
#define	CLBreakBCurr_FF_1                  179     /*上1次B相断流数据块*/
#define	CLBreakBCurr_HpData_1              109     /*上1次B相断流发生数据*/
#define	CLBreakBCurr_EndData_1             70      /*上1次B相断流结束数据*/

/*********C相**********/
/*上2次-上10次 C相断流 事件记录数据长度 同上1次*/
#define	CLBreakC_Curr_Hp_1                 6       /*上1次C相断流发生时刻*/
#define	CLBreakCCurrHp_PosAcTolEn_1        4       /*上1次C相断流发生时刻正向有功总电能*/
#define	CLBreakCCurrHp_RevAcTolEn_1        4       /*上1次C相断流发生时刻反向有功总电能*/
#define	CLBreakCCurrHp_ComRe1TolEn_1       4       /*上1次C相断流发生时刻组合无功1总电能*/
#define	CLBreakCCurrHp_ComRe2TolEn_1       4       /*上1次C相断流发生时刻组合无功2总电能*/
#define	CLBreakCCurrHp_APosAcEn_1          4       /*上1次C相断流发生时刻A相正向有功电能*/
#define	CLBreakCCurrHp_ARevAcEn_1          4       /*上1次C相断流发生时刻A相反向有功电能*/
#define	CLBreakCCurrHp_AComRe1En_1         4       /*上1次C相断流发生时刻A相组合无功1总电能*/
#define	CLBreakCCurrHp_AComRe2En_1         4       /*上1次C相断流发生时刻A相组合无功2总电能*/
#define	CLBreakCCurrHp_AVol_1              2       /*上1次C相断流发生时刻A相电压*/
#define	CLBreakCCurrHp_ACurr_1             3       /*上1次C相断流发生时刻A相电流*/
#define	CLBreakCCurrHp_AAcP_1              3       /*上1次C相断流发生时刻A相有功功率*/
#define	CLBreakCCurrHp_AReP_1              3       /*上1次C相断流发生时刻A相无功功率*/
#define	CLBreakCCurrHp_APF_1               2       /*上1次C相断流发生时刻A相功率因数*/
#define	CLBreakCCurrHp_BPosAcEn_1          4       /*上1次C相断流发生时刻B相正向有功电能*/
#define	CLBreakCCurrHp_BRevAcEn_1          4       /*上1次C相断流发生时刻B相反向有功电能*/
#define	CLBreakCCurrHp_BComRe1En_1         4       /*上1次C相断流发生时刻B相组合无功1总电能*/
#define	CLBreakCCurrHp_BComRe2En_1         4       /*上1次C相断流发生时刻B相组合无功2总电能*/
#define	CLBreakCCurrHp_BVol_1              2       /*上1次C相断流发生时刻B相电压*/
#define	CLBreakCCurrHp_BCurr_1             3       /*上1次C相断流发生时刻B相电流*/
#define	CLBreakCCurrHp_BAcP_1              3       /*上1次C相断流发生时刻B相有功功率*/
#define	CLBreakCCurrHp_BReP_1              3       /*上1次C相断流发生时刻B相无功功率*/
#define	CLBreakCCurrHp_BPF_1               2       /*上1次C相断流发生时刻B相功率因数*/
#define	CLBreakCCurrHp_CPosAcEn_1          4       /*上1次C相断流发生时刻C相正向有功电能*/
#define	CLBreakCCurrHp_CRevAcEn_1          4       /*上1次C相断流发生时刻C相反向有功电能*/
#define	CLBreakCCurrHp_CComRe1En_1         4       /*上1次C相断流发生时刻C相组合无功1总电能*/
#define	CLBreakCCurrHp_CComRe2En_1         4       /*上1次C相断流发生时刻C相组合无功2总电能*/
#define	CLBreakCCurrHp_CVol_1              2       /*上1次C相断流发生时刻C相电压*/
#define	CLBreakCCurrHp_CCurr_1             3       /*上1次C相断流发生时刻C相电流*/
#define	CLBreakCCurrHp_CAcP_1              3       /*上1次C相断流发生时刻C相有功功率*/
#define	CLBreakCCurrHp_CReP_1              3       /*上1次C相断流发生时刻C相无功功率*/
#define	CLBreakCCurrHp_CPF_1               2       /*上1次C相断流发生时刻C相功率因数*/
#define	CLBreakC_Curr_End_1                6       /*上1次C相断流结束时刻*/
#define	CLBreakCCurrEnd_PosAcTolEn_1       4       /*上1次C相断流结束时刻正向有功总电能*/
#define	CLBreakCCurrEnd_RevAcTolEn_1       4       /*上1次C相断流结束时刻反向有功总电能*/
#define	CLBreakCCurrEnd_ComRe1TolEn_1      4       /*上1次C相断流结束时刻组合无功1总电能*/
#define	CLBreakCCurrEnd_ComRe2TolEn_1      4       /*上1次C相断流结束时刻组合无功2总电能*/
#define	CLBreakCCurrEnd_APosAcEn_1         4       /*上1次C相断流结束时刻A相正向有功电能*/
#define	CLBreakCCurrEnd_ARevAcEn_1         4       /*上1次C相断流结束时刻A相反向有功电能*/
#define	CLBreakCCurrEnd_AComRe1En_1        4       /*上1次C相断流结束时刻A相组合无功1电能*/
#define	CLBreakCCurrEnd_AComRe2En_1        4       /*上1次C相断流结束时刻A相组合无功2电能*/
#define	CLBreakCCurrEnd_BPosAcEn_1         4       /*上1次C相断流发生时刻B相正向有功电能*/
#define	CLBreakCCurrEnd_BRevAcEn_1         4       /*上1次C相断流发生时刻B相反向有功电能*/
#define	CLBreakCCurrEnd_BComRe1En_1        4       /*上1次C相断流结束时刻B相组合无功1电能*/
#define	CLBreakCCurrEnd_BComRe2En_1        4       /*上1次C相断流结束时刻B相组合无功2电能*/
#define	CLBreakCCurrEnd_CPosAcEn_1         4       /*上1次C相断流发生时刻C相正向有功电能*/
#define	CLBreakCCurrEnd_CRevAcEn_1         4       /*上1次C相断流发生时刻C相反向有功电能*/
#define	CLBreakCCurrEnd_CComRe1En_1        4       /*上1次C相断流结束时刻C相组合无功1电能*/
#define	CLBreakCCurrEnd_CComRe2En_1        4       /*上1次C相断流结束时刻C相组合无功2电能*/
#define	CLBreakCCurr_FF_1                  179     /*上1次C相断流数据块*/
#define	CLBreakCCurr_HpData_1              109     /*上1次C相断流发生数据*/
#define	CLBreakCCurr_EndData_1             70      /*上1次C相断流结束数据*/

/**********功率反向*************/
/*698相关定义*/
#define CLPowerT_Rev_Current               8        /*总功率反向事件当前值记录表*/
#define CLPowerT_Rev_Degree                4        /*总功率反向事件发生次数*/
#define CLPowerT_Rev_Time                  4        /*总功率反向事件累计时间*/

#define CLPowerA_Rev_Current               8        /*A相功率反向事件当前值记录表*/
#define CLPowerA_Rev_Degree                4        /*A相功率反向事件发生次数*/
#define CLPowerA_Rev_Time                  4        /*A相功率反向事件累计时间*/

#define CLPowerB_Rev_Current               8        /*B相功率反向事件当前值记录表*/
#define CLPowerB_Rev_Degree                4        /*B相功率反向事件发生次数*/
#define CLPowerB_Rev_Time                  4        /*B相功率反向事件累计时间*/

#define CLPowerC_Rev_Current               8        /*C相功率反向事件当前值记录表*/
#define CLPowerC_Rev_Degree                4        /*C相功率反向事件发生次数*/
#define CLPowerC_Rev_Time                  4        /*C相功率反向事件累计时间*/

/*645相关定义*/
/*上2次-上10次 总功率反向 事件记录数据长度 同上1次*/
#define	CLPowerT_Rev_Hp_1                  6       /*上1次总功率反向发生时刻*/
#define	CLPowerTRevHp_PosAcTolEn_1         4       /*上1次总功率反向发生时刻正向有功总电能*/
#define	CLPowerTRevHp_RevAcTolEn_1         4       /*上1次总功率反向发生时刻反向有功总电能*/
#define	CLPowerTRevHp_ComRe1TolEn_1        4       /*上1次总功率反向发生时刻组合无功1总电能*/
#define	CLPowerTRevHp_ComRe2TolEn_1        4       /*上1次总功率反向发生时刻组合无功2总电能*/
#define	CLPowerTRevHp_APosAcEn_1           4       /*上1次总功率反向发生时刻A相正向有功电能*/
#define	CLPowerTRevHp_ARevAcEn_1           4       /*上1次总功率反向发生时刻A相反向有功电能*/
#define	CLPowerTRevHp_AComRe1En_1          4       /*上1次总功率反向发生时刻A相组合无功1总电能*/
#define	CLPowerTRevHp_AComRe2En_1          4       /*上1次总功率反向发生时刻A相组合无功2总电能*/
#define	CLPowerTRevHp_BPosAcEn_1           4       /*上1次总功率反向发生时刻B相正向有功电能*/
#define	CLPowerTRevHp_BRevAcEn_1           4       /*上1次总功率反向发生时刻B相反向有功电能*/
#define	CLPowerTRevHp_BComRe1En_1          4       /*上1次总功率反向发生时刻B相组合无功1总电能*/
#define	CLPowerTRevHp_BComRe2En_1          4       /*上1次总功率反向发生时刻B相组合无功2总电能*/
#define	CLPowerTRevHp_CPosAcEn_1           4       /*上1次总功率反向发生时刻C相正向有功电能*/
#define	CLPowerTRevHp_CRevAcEn_1           4       /*上1次总功率反向发生时刻C相反向有功电能*/
#define	CLPowerTRevHp_CComRe1En_1          4       /*上1次总功率反向发生时刻C相组合无功1总电能*/
#define	CLPowerTRevHp_CComRe2En_1          4       /*上1次总功率反向发生时刻C相组合无功2总电能*/
#define	CLPowerT_Rev_End_1                 6       /*上1次总功率反向结束时刻*/
#define	CLPowerTRevEnd_PosAcTolEn_1        4       /*上1次总功率反向结束时刻正向有功总电能*/
#define	CLPowerTRevEnd_RevAcTolEn_1        4       /*上1次总功率反向结束时刻反向有功总电能*/
#define	CLPowerTRevEnd_ComRe1TolEn_1       4       /*上1次总功率反向结束时刻组合无功1总电能*/
#define	CLPowerTRevEnd_ComRe2TolEn_1       4       /*上1次总功率反向结束时刻组合无功2总电能*/
#define	CLPowerTRevEnd_APosAcEn_1          4       /*上1次总功率反向结束时刻A相正向有功电能*/
#define	CLPowerTRevEnd_ARevAcEn_1          4       /*上1次总功率反向结束时刻A相反向有功电能*/
#define	CLPowerTRevEnd_AComRe1En_1         4       /*上1次总功率反向结束时刻A相组合无功1电能*/
#define	CLPowerTRevEnd_AComRe2En_1         4       /*上1次总功率反向结束时刻A相组合无功2电能*/
#define	CLPowerTRevEnd_BPosAcEn_1          4       /*上1次总功率反向发生时刻B相正向有功电能*/
#define	CLPowerTRevEnd_BRevAcEn_1          4       /*上1次总功率反向发生时刻B相反向有功电能*/
#define	CLPowerTRevEnd_BComRe1En_1         4       /*上1次总功率反向结束时刻B相组合无功1电能*/
#define	CLPowerTRevEnd_BComRe2En_1         4       /*上1次总功率反向结束时刻B相组合无功2电能*/
#define	CLPowerTRevEnd_CPosAcEn_1          4       /*上1次总功率反向发生时刻C相正向有功电能*/
#define	CLPowerTRevEnd_CRevAcEn_1          4       /*上1次总功率反向发生时刻C相反向有功电能*/
#define	CLPowerTRevEnd_CComRe1En_1         4       /*上1次总功率反向结束时刻C相组合无功1电能*/
#define	CLPowerTRevEnd_CComRe2En_1         4       /*上1次总功率反向结束时刻C相组合无功2电能*/
#define	CLPowerTRev_FF_1                   140     /*上1次总功率反向数据块*/
#define	CLPowerTRev_HpData_1               70      /*上1次总功率反向发生数据*/
#define	CLPowerTRev_EndData_1              70      /*上1次总功率反向结束数据*/

/**************A相****************/
/*上2次-上10次 A相功率反向 事件记录数据长度 同上1次*/
#define	CLPowerA_Rev_Hp_1                  6       /*上1次A相功率反向发生时刻*/
#define	CLPowerARevHp_PosAcTolEn_1         4       /*上1次A相功率反向发生时刻正向有功总电能*/
#define	CLPowerARevHp_RevAcTolEn_1         4       /*上1次A相功率反向发生时刻反向有功总电能*/
#define	CLPowerARevHp_ComRe1TolEn_1        4       /*上1次A相功率反向发生时刻组合无功1总电能*/
#define	CLPowerARevHp_ComRe2TolEn_1        4       /*上1次A相功率反向发生时刻组合无功2总电能*/
#define	CLPowerARevHp_APosAcEn_1           4       /*上1次A相功率反向发生时刻A相正向有功电能*/
#define	CLPowerARevHp_ARevAcEn_1           4       /*上1次A相功率反向发生时刻A相反向有功电能*/
#define	CLPowerARevHp_AComRe1En_1          4       /*上1次A相功率反向发生时刻A相组合无功1总电能*/
#define	CLPowerARevHp_AComRe2En_1          4       /*上1次A相功率反向发生时刻A相组合无功2总电能*/
#define	CLPowerARevHp_BPosAcEn_1           4       /*上1次A相功率反向发生时刻B相正向有功电能*/
#define	CLPowerARevHp_BRevAcEn_1           4       /*上1次A相功率反向发生时刻B相反向有功电能*/
#define	CLPowerARevHp_BComRe1En_1          4       /*上1次A相功率反向发生时刻B相组合无功1总电能*/
#define	CLPowerARevHp_BComRe2En_1          4       /*上1次A相功率反向发生时刻B相组合无功2总电能*/
#define	CLPowerARevHp_CPosAcEn_1           4       /*上1次A相功率反向发生时刻C相正向有功电能*/
#define	CLPowerARevHp_CRevAcEn_1           4       /*上1次A相功率反向发生时刻C相反向有功电能*/
#define	CLPowerARevHp_CComRe1En_1          4       /*上1次A相功率反向发生时刻C相组合无功1总电能*/
#define	CLPowerARevHp_CComRe2En_1          4       /*上1次A相功率反向发生时刻C相组合无功2总电能*/
#define	CLPowerA_Rev_End_1                 6       /*上1次A相功率反向结束时刻*/
#define	CLPowerARevEnd_PosAcTolEn_1        4       /*上1次A相功率反向结束时刻正向有功总电能*/
#define	CLPowerARevEnd_RevAcTolEn_1        4       /*上1次A相功率反向结束时刻反向有功总电能*/
#define	CLPowerARevEnd_ComRe1TolEn_1       4       /*上1次A相功率反向结束时刻组合无功1总电能*/
#define	CLPowerARevEnd_ComRe2TolEn_1       4       /*上1次A相功率反向结束时刻组合无功2总电能*/
#define	CLPowerARevEnd_APosAcEn_1          4       /*上1次A相功率反向结束时刻A相正向有功电能*/
#define	CLPowerARevEnd_ARevAcEn_1          4       /*上1次A相功率反向结束时刻A相反向有功电能*/
#define	CLPowerARevEnd_AComRe1En_1         4       /*上1次A相功率反向结束时刻A相组合无功1电能*/
#define	CLPowerARevEnd_AComRe2En_1         4       /*上1次A相功率反向结束时刻A相组合无功2电能*/
#define	CLPowerARevEnd_BPosAcEn_1          4       /*上1次A相功率反向发生时刻B相正向有功电能*/
#define	CLPowerARevEnd_BRevAcEn_1          4       /*上1次A相功率反向发生时刻B相反向有功电能*/
#define	CLPowerARevEnd_BComRe1En_1         4       /*上1次A相功率反向结束时刻B相组合无功1电能*/
#define	CLPowerARevEnd_BComRe2En_1         4       /*上1次A相功率反向结束时刻B相组合无功2电能*/
#define	CLPowerARevEnd_CPosAcEn_1          4       /*上1次A相功率反向发生时刻C相正向有功电能*/
#define	CLPowerARevEnd_CRevAcEn_1          4       /*上1次A相功率反向发生时刻C相反向有功电能*/
#define	CLPowerARevEnd_CComRe1En_1         4       /*上1次A相功率反向结束时刻C相组合无功1电能*/
#define	CLPowerARevEnd_CComRe2En_1         4       /*上1次A相功率反向结束时刻C相组合无功2电能*/
#define	CLPowerARev_FF_1                   140     /*上1次A相功率反向数据块*/
#define	CLPowerARev_HpData_1               70      /*上1次A相功率反向发生数据*/
#define	CLPowerARev_EndData_1              70      /*上1次A相功率反向结束数据*/

/**************B相****************/
/*上2次-上10次 B相功率反向 事件记录数据长度 同上1次*/
#define	CLPowerB_Rev_Hp_1                  6         /*上1次B相功率反向发生时刻*/
#define	CLPowerBRevHp_PosAcTolEn_1         4         /*上1次B相功率反向发生时刻正向有功总电能*/
#define	CLPowerBRevHp_RevAcTolEn_1         4         /*上1次B相功率反向发生时刻反向有功总电能*/
#define	CLPowerBRevHp_ComRe1TolEn_1        4         /*上1次B相功率反向发生时刻组合无功1总电能*/
#define	CLPowerBRevHp_ComRe2TolEn_1        4         /*上1次B相功率反向发生时刻组合无功2总电能*/
#define	CLPowerBRevHp_APosAcEn_1           4         /*上1次B相功率反向发生时刻A相正向有功电能*/
#define	CLPowerBRevHp_ARevAcEn_1           4         /*上1次B相功率反向发生时刻A相反向有功电能*/
#define	CLPowerBRevHp_AComRe1En_1          4         /*上1次B相功率反向发生时刻A相组合无功1总电能*/
#define	CLPowerBRevHp_AComRe2En_1          4         /*上1次B相功率反向发生时刻A相组合无功2总电能*/
#define	CLPowerBRevHp_BPosAcEn_1           4         /*上1次B相功率反向发生时刻B相正向有功电能*/
#define	CLPowerBRevHp_BRevAcEn_1           4         /*上1次B相功率反向发生时刻B相反向有功电能*/
#define	CLPowerBRevHp_BComRe1En_1          4         /*上1次B相功率反向发生时刻B相组合无功1总电能*/
#define	CLPowerBRevHp_BComRe2En_1          4         /*上1次B相功率反向发生时刻B相组合无功2总电能*/
#define	CLPowerBRevHp_CPosAcEn_1           4         /*上1次B相功率反向发生时刻C相正向有功电能*/
#define	CLPowerBRevHp_CRevAcEn_1           4         /*上1次B相功率反向发生时刻C相反向有功电能*/
#define	CLPowerBRevHp_CComRe1En_1          4         /*上1次B相功率反向发生时刻C相组合无功1总电能*/
#define	CLPowerBRevHp_CComRe2En_1          4         /*上1次B相功率反向发生时刻C相组合无功2总电能*/
#define	CLPowerB_Rev_End_1	               6         /*上1次B相功率反向结束时刻*/
#define	CLPowerBRevEnd_PosAcTolEn_1        4         /*上1次B相功率反向结束时刻正向有功总电能*/
#define	CLPowerBRevEnd_RevAcTolEn_1        4         /*上1次B相功率反向结束时刻反向有功总电能*/
#define	CLPowerBRevEnd_ComRe1TolEn_1       4         /*上1次B相功率反向结束时刻组合无功1总电能*/
#define	CLPowerBRevEnd_ComRe2TolEn_1       4         /*上1次B相功率反向结束时刻组合无功2总电能*/
#define	CLPowerBRevEnd_APosAcEn_1          4         /*上1次B相功率反向结束时刻A相正向有功电能*/
#define	CLPowerBRevEnd_ARevAcEn_1          4         /*上1次B相功率反向结束时刻A相反向有功电能*/
#define	CLPowerBRevEnd_AComRe1En_1         4         /*上1次B相功率反向结束时刻A相组合无功1电能*/
#define	CLPowerBRevEnd_AComRe2En_1         4         /*上1次B相功率反向结束时刻A相组合无功2电能*/
#define	CLPowerBRevEnd_BPosAcEn_1          4         /*上1次B相功率反向发生时刻B相正向有功电能*/
#define	CLPowerBRevEnd_BRevAcEn_1          4         /*上1次B相功率反向发生时刻B相反向有功电能*/
#define	CLPowerBRevEnd_BComRe1En_1         4         /*上1次B相功率反向结束时刻B相组合无功1电能*/
#define	CLPowerBRevEnd_BComRe2En_1         4         /*上1次B相功率反向结束时刻B相组合无功2电能*/
#define	CLPowerBRevEnd_CPosAcEn_1          4         /*上1次B相功率反向发生时刻C相正向有功电能*/
#define	CLPowerBRevEnd_CRevAcEn_1          4         /*上1次B相功率反向发生时刻C相反向有功电能*/
#define	CLPowerBRevEnd_CComRe1En_1         4         /*上1次B相功率反向结束时刻C相组合无功1电能*/
#define	CLPowerBRevEnd_CComRe2En_1         4         /*上1次B相功率反向结束时刻C相组合无功2电能*/
#define	CLPowerBRev_FF_1                   140       /*上1次B相功率反向数据块*/
#define	CLPowerBRev_HpData_1               70        /*上1次B相功率反向发生数据*/
#define	CLPowerBRev_EndData_1              70        /*上1次B相功率反向结束数据*/

/**************C相****************/
/*上2次-上10次 C相功率反向 事件记录数据长度 同上1次*/
#define	CLPowerC_Rev_Hp_1                  6         /*上1次C相功率反向发生时刻*/
#define	CLPowerCRevHp_PosAcTolEn_1         4         /*上1次C相功率反向发生时刻正向有功总电能*/
#define	CLPowerCRevHp_RevAcTolEn_1         4         /*上1次C相功率反向发生时刻反向有功总电能*/
#define	CLPowerCRevHp_ComRe1TolEn_1        4         /*上1次C相功率反向发生时刻组合无功1总电能*/
#define	CLPowerCRevHp_ComRe2TolEn_1        4         /*上1次C相功率反向发生时刻组合无功2总电能*/
#define	CLPowerCRevHp_APosAcEn_1           4         /*上1次C相功率反向发生时刻A相正向有功电能*/
#define	CLPowerCRevHp_ARevAcEn_1           4         /*上1次C相功率反向发生时刻A相反向有功电能*/
#define	CLPowerCRevHp_AComRe1En_1          4         /*上1次C相功率反向发生时刻A相组合无功1总电能*/
#define	CLPowerCRevHp_AComRe2En_1          4         /*上1次C相功率反向发生时刻A相组合无功2总电能*/
#define	CLPowerCRevHp_BPosAcEn_1           4         /*上1次C相功率反向发生时刻B相正向有功电能*/
#define	CLPowerCRevHp_BRevAcEn_1           4         /*上1次C相功率反向发生时刻B相反向有功电能*/
#define	CLPowerCRevHp_BComRe1En_1          4         /*上1次C相功率反向发生时刻B相组合无功1总电能*/
#define	CLPowerCRevHp_BComRe2En_1          4         /*上1次C相功率反向发生时刻B相组合无功2总电能*/
#define	CLPowerCRevHp_CPosAcEn_1           4         /*上1次C相功率反向发生时刻C相正向有功电能*/
#define	CLPowerCRevHp_CRevAcEn_1           4         /*上1次C相功率反向发生时刻C相反向有功电能*/
#define	CLPowerCRevHp_CComRe1En_1          4         /*上1次C相功率反向发生时刻C相组合无功1总电能*/
#define	CLPowerCRevHp_CComRe2En_1          4         /*上1次C相功率反向发生时刻C相组合无功2总电能*/
#define	CLPowerC_Rev_End_1	               6         /*上1次C相功率反向结束时刻*/
#define	CLPowerCRevEnd_PosAcTolEn_1        4         /*上1次C相功率反向结束时刻正向有功总电能*/
#define	CLPowerCRevEnd_RevAcTolEn_1        4         /*上1次C相功率反向结束时刻反向有功总电能*/
#define	CLPowerCRevEnd_ComRe1TolEn_1       4         /*上1次C相功率反向结束时刻组合无功1总电能*/
#define	CLPowerCRevEnd_ComRe2TolEn_1       4         /*上1次C相功率反向结束时刻组合无功2总电能*/
#define	CLPowerCRevEnd_APosAcEn_1          4         /*上1次C相功率反向结束时刻A相正向有功电能*/
#define	CLPowerCRevEnd_ARevAcEn_1          4         /*上1次C相功率反向结束时刻A相反向有功电能*/
#define	CLPowerCRevEnd_AComRe1En_1         4         /*上1次C相功率反向结束时刻A相组合无功1电能*/
#define	CLPowerCRevEnd_AComRe2En_1         4         /*上1次C相功率反向结束时刻A相组合无功2电能*/
#define	CLPowerCRevEnd_BPosAcEn_1          4         /*上1次C相功率反向发生时刻B相正向有功电能*/
#define	CLPowerCRevEnd_BRevAcEn_1          4         /*上1次C相功率反向发生时刻B相反向有功电能*/
#define	CLPowerCRevEnd_BComRe1En_1         4         /*上1次C相功率反向结束时刻B相组合无功1电能*/
#define	CLPowerCRevEnd_BComRe2En_1         4         /*上1次C相功率反向结束时刻B相组合无功2电能*/
#define	CLPowerCRevEnd_CPosAcEn_1          4         /*上1次C相功率反向发生时刻C相正向有功电能*/
#define	CLPowerCRevEnd_CRevAcEn_1          4         /*上1次C相功率反向发生时刻C相反向有功电能*/
#define	CLPowerCRevEnd_CComRe1En_1         4         /*上1次C相功率反向结束时刻C相组合无功1电能*/
#define	CLPowerCRevEnd_CComRe2En_1         4         /*上1次C相功率反向结束时刻C相组合无功2电能*/
#define	CLPowerCRev_FF_1                   140       /*上1次C相功率反向数据块*/
#define	CLPowerCRev_HpData_1               70        /*上1次C相功率反向发生数据*/
#define	CLPowerCRev_EndData_1              70        /*上1次C相功率反向结束数据*/

/***********过载**********/
/*698相关定义*/
#define CLOverA_Lo_Current                 8        /*A相过载事件当前值记录表*/
#define CLOverA_Lo_Degree                  4        /*A相过载事件发生次数*/
#define CLOverA_Lo_Time                    4        /*A相过载事件累计时间*/

#define CLOverB_Lo_Current                 8        /*B相过载事件当前值记录表*/
#define CLOverB_Lo_Degree                  4        /*B相过载事件发生次数*/
#define CLOverB_Lo_Time                    4        /*B相过载事件累计时间*/

#define CLOverC_Lo_Current                 8        /*C相过载事件当前值记录表*/
#define CLOverC_Lo_Degree                  4        /*C相过载事件发生次数*/
#define CLOverC_Lo_Time                    4        /*C相过载事件累计时间*/

/*645相关定义*/
/**************A相**************/
/*上2次-上10次 A相过载 事件记录数据长度 同上1次*/
#define	CLOverA_Lo_Hp_1                    6         /*上1次A相过载发生时刻*/
#define	CLOverALoHp_PosAcTolEn_1           4         /*上1次A相过载发生时刻正向有功总电能*/
#define	CLOverALoHp_RevAcTolEn_1           4         /*上1次A相过载发生时刻反向有功总电能*/
#define	CLOverALoHp_ComRe1TolEn_1          4         /*上1次A相过载发生时刻组合无功1总电能*/
#define	CLOverALoHp_ComRe2TolEn_1          4         /*上1次A相过载发生时刻组合无功2总电能*/
#define	CLOverALoHp_APosAcEn_1             4         /*上1次A相过载发生时刻A相正向有功电能*/
#define	CLOverALoHp_ARevAcEn_1             4         /*上1次A相过载发生时刻A相反向有功电能*/
#define	CLOverALoHp_AComRe1En_1            4         /*上1次A相过载发生时刻A相组合无功1总电能*/
#define	CLOverALoHp_AComRe2En_1            4         /*上1次A相过载发生时刻A相组合无功2总电能*/
#define	CLOverALoHp_BPosAcEn_1             4         /*上1次A相过载发生时刻B相正向有功电能*/
#define	CLOverALoHp_BRevAcEn_1             4         /*上1次A相过载发生时刻B相反向有功电能*/
#define	CLOverALoHp_BComRe1En_1            4         /*上1次A相过载发生时刻B相组合无功1总电能*/
#define	CLOverALoHp_BComRe2En_1            4         /*上1次A相过载发生时刻B相组合无功2总电能*/
#define	CLOverALoHp_CPosAcEn_1             4         /*上1次A相过载发生时刻C相正向有功电能*/
#define	CLOverALoHp_CRevAcEn_1             4         /*上1次A相过载发生时刻C相反向有功电能*/
#define	CLOverALoHp_CComRe1En_1            4         /*上1次A相过载发生时刻C相组合无功1总电能*/
#define	CLOverALoHp_CComRe2En_1            4         /*上1次A相过载发生时刻C相组合无功2总电能*/
#define	CLOverA_Lo_End_1                   6         /*上1次A相过载结束时刻*/
#define	CLOverALoEnd_PosAcTolEn_1          4         /*上1次A相过载结束时刻正向有功总电能*/
#define	CLOverALoEnd_RevAcTolEn_1          4         /*上1次A相过载结束时刻反向有功总电能*/
#define	CLOverALoEnd_ComRe1TolEn_1         4         /*上1次A相过载结束时刻组合无功1总电能*/
#define	CLOverALoEnd_ComRe2TolEn_1         4         /*上1次A相过载结束时刻组合无功2总电能*/
#define	CLOverALoEnd_APosAcEn_1            4         /*上1次A相过载结束时刻A相正向有功电能*/
#define	CLOverALoEnd_ARevAcEn_1            4         /*上1次A相过载结束时刻A相反向有功电能*/
#define	CLOverALoEnd_AComRe1En_1           4         /*上1次A相过载结束时刻A相组合无功1电能*/
#define	CLOverALoEnd_AComRe2En_1           4         /*上1次A相过载结束时刻A相组合无功2电能*/
#define	CLOverALoEnd_BPosAcEn_1            4         /*上1次A相过载发生时刻B相正向有功电能*/
#define	CLOverALoEnd_BRevAcEn_1            4         /*上1次A相过载发生时刻B相反向有功电能*/
#define	CLOverALoEnd_BComRe1En_1           4         /*上1次A相过载结束时刻B相组合无功1电能*/
#define	CLOverALoEnd_BComRe2En_1           4         /*上1次A相过载结束时刻B相组合无功2电能*/
#define	CLOverALoEnd_CPosAcEn_1            4         /*上1次A相过载发生时刻C相正向有功电能*/
#define	CLOverALoEnd_CRevAcEn_1            4         /*上1次A相过载发生时刻C相反向有功电能*/
#define	CLOverALoEnd_CComRe1En_1           4         /*上1次A相过载结束时刻C相组合无功1电能*/
#define	CLOverALoEnd_CComRe2En_1           4         /*上1次A相过载结束时刻C相组合无功2电能*/
#define	CLOverALo_FF_1                     140       /*上1次A相过载数据块*/
#define	CLOverALo_HpData_1                 70        /*上1次A相过载发生数据*/
#define	CLOverALo_EndData_1                70        /*上1次A相过载结束数据*/

/**************B相****************/
/*上2次-上10次 B相过载 事件记录数据长度 同上1次*/
#define	CLOverB_Lo_Hp_1                    6         /*上1次B相过载发生时刻*/
#define	CLOverBLoHp_PosAcTolEn_1           4         /*上1次B相过载发生时刻正向有功总电能*/
#define	CLOverBLoHp_RevAcTolEn_1           4         /*上1次B相过载发生时刻反向有功总电能*/
#define	CLOverBLoHp_ComRe1TolEn_1          4         /*上1次B相过载发生时刻组合无功1总电能*/
#define	CLOverBLoHp_ComRe2TolEn_1          4         /*上1次B相过载发生时刻组合无功2总电能*/
#define	CLOverBLoHp_APosAcEn_1             4         /*上1次B相过载发生时刻A相正向有功电能*/
#define	CLOverBLoHp_ARevAcEn_1             4         /*上1次B相过载发生时刻A相反向有功电能*/
#define	CLOverBLoHp_AComRe1En_1            4         /*上1次B相过载发生时刻A相组合无功1总电能*/
#define	CLOverBLoHp_AComRe2En_1            4         /*上1次B相过载发生时刻A相组合无功2总电能*/
#define	CLOverBLoHp_BPosAcEn_1             4         /*上1次B相过载发生时刻B相正向有功电能*/
#define	CLOverBLoHp_BRevAcEn_1             4         /*上1次B相过载发生时刻B相反向有功电能*/
#define	CLOverBLoHp_BComRe1En_1            4         /*上1次B相过载发生时刻B相组合无功1总电能*/
#define	CLOverBLoHp_BComRe2En_1            4         /*上1次B相过载发生时刻B相组合无功2总电能*/
#define	CLOverBLoHp_CPosAcEn_1             4         /*上1次B相过载发生时刻C相正向有功电能*/
#define	CLOverBLoHp_CRevAcEn_1             4         /*上1次B相过载发生时刻C相反向有功电能*/
#define	CLOverBLoHp_CComRe1En_1            4         /*上1次B相过载发生时刻C相组合无功1总电能*/
#define	CLOverBLoHp_CComRe2En_1            4         /*上1次B相过载发生时刻C相组合无功2总电能*/
#define	CLOverB_Lo_End_1                   6         /*上1次B相过载结束时刻*/
#define	CLOverBLoEnd_PosAcTolEn_1          4         /*上1次B相过载结束时刻正向有功总电能*/
#define	CLOverBLoEnd_RevAcTolEn_1          4         /*上1次B相过载结束时刻反向有功总电能*/
#define	CLOverBLoEnd_ComRe1TolEn_1         4         /*上1次B相过载结束时刻组合无功1总电能*/
#define	CLOverBLoEnd_ComRe2TolEn_1         4         /*上1次B相过载结束时刻组合无功2总电能*/
#define	CLOverBLoEnd_APosAcEn_1            4         /*上1次B相过载结束时刻A相正向有功电能*/
#define	CLOverBLoEnd_ARevAcEn_1            4         /*上1次B相过载结束时刻A相反向有功电能*/
#define	CLOverBLoEnd_AComRe1En_1           4         /*上1次B相过载结束时刻A相组合无功1电能*/
#define	CLOverBLoEnd_AComRe2En_1           4         /*上1次B相过载结束时刻A相组合无功2电能*/
#define	CLOverBLoEnd_BPosAcEn_1            4         /*上1次B相过载发生时刻B相正向有功电能*/
#define	CLOverBLoEnd_BRevAcEn_1            4         /*上1次B相过载发生时刻B相反向有功电能*/
#define	CLOverBLoEnd_BComRe1En_1           4         /*上1次B相过载结束时刻B相组合无功1电能*/
#define	CLOverBLoEnd_BComRe2En_1           4         /*上1次B相过载结束时刻B相组合无功2电能*/
#define	CLOverBLoEnd_CPosAcEn_1            4         /*上1次B相过载发生时刻C相正向有功电能*/
#define	CLOverBLoEnd_CRevAcEn_1            4         /*上1次B相过载发生时刻C相反向有功电能*/
#define	CLOverBLoEnd_CComRe1En_1           4         /*上1次B相过载结束时刻C相组合无功1电能*/
#define	CLOverBLoEnd_CComRe2En_1           4         /*上1次B相过载结束时刻C相组合无功2电能*/
#define	CLOverBLo_FF_1                     140       /*上1次B相过载数据块*/
#define	CLOverBLo_HpData_1                 70        /*上1次B相过载发生数据*/
#define	CLOverBLo_EndData_1                70        /*上1次B相过载结束数据*/

/**************C相*****************/
/*上2次-上10次 C相过载 事件记录数据长度 同上1次*/
#define	CLOverC_Lo_Hp_1                    6         /*上1次C相过载发生时刻*/
#define	CLOverCLoHp_PosAcTolEn_1           4         /*上1次C相过载发生时刻正向有功总电能*/
#define	CLOverCLoHp_RevAcTolEn_1           4         /*上1次C相过载发生时刻反向有功总电能*/
#define	CLOverCLoHp_ComRe1TolEn_1          4         /*上1次C相过载发生时刻组合无功1总电能*/
#define	CLOverCLoHp_ComRe2TolEn_1          4         /*上1次C相过载发生时刻组合无功2总电能*/
#define	CLOverCLoHp_APosAcEn_1             4         /*上1次C相过载发生时刻A相正向有功电能*/
#define	CLOverCLoHp_ARevAcEn_1             4         /*上1次C相过载发生时刻A相反向有功电能*/
#define	CLOverCLoHp_AComRe1En_1            4         /*上1次C相过载发生时刻A相组合无功1总电能*/
#define	CLOverCLoHp_AComRe2En_1            4         /*上1次C相过载发生时刻A相组合无功2总电能*/
#define	CLOverCLoHp_BPosAcEn_1             4         /*上1次C相过载发生时刻B相正向有功电能*/
#define	CLOverCLoHp_BRevAcEn_1             4         /*上1次C相过载发生时刻B相反向有功电能*/
#define	CLOverCLoHp_BComRe1En_1            4         /*上1次C相过载发生时刻B相组合无功1总电能*/
#define	CLOverCLoHp_BComRe2En_1            4         /*上1次C相过载发生时刻B相组合无功2总电能*/
#define	CLOverCLoHp_CPosAcEn_1             4         /*上1次C相过载发生时刻C相正向有功电能*/
#define	CLOverCLoHp_CRevAcEn_1             4         /*上1次C相过载发生时刻C相反向有功电能*/
#define	CLOverCLoHp_CComRe1En_1            4         /*上1次C相过载发生时刻C相组合无功1总电能*/
#define	CLOverCLoHp_CComRe2En_1            4         /*上1次C相过载发生时刻C相组合无功2总电能*/
#define	CLOverC_Lo_End_1                   6         /*上1次C相过载结束时刻*/
#define	CLOverCLoEnd_PosAcTolEn_1          4         /*上1次C相过载结束时刻正向有功总电能*/
#define	CLOverCLoEnd_RevAcTolEn_1          4         /*上1次C相过载结束时刻反向有功总电能*/
#define	CLOverCLoEnd_ComRe1TolEn_1         4         /*上1次C相过载结束时刻组合无功1总电能*/
#define	CLOverCLoEnd_ComRe2TolEn_1         4         /*上1次C相过载结束时刻组合无功2总电能*/
#define	CLOverCLoEnd_APosAcEn_1            4         /*上1次C相过载结束时刻A相正向有功电能*/
#define	CLOverCLoEnd_ARevAcEn_1            4         /*上1次C相过载结束时刻A相反向有功电能*/
#define	CLOverCLoEnd_AComRe1En_1           4         /*上1次C相过载结束时刻A相组合无功1电能*/
#define	CLOverCLoEnd_AComRe2En_1           4         /*上1次C相过载结束时刻A相组合无功2电能*/
#define	CLOverCLoEnd_BPosAcEn_1            4         /*上1次C相过载发生时刻B相正向有功电能*/
#define	CLOverCLoEnd_BRevAcEn_1            4         /*上1次C相过载发生时刻B相反向有功电能*/
#define	CLOverCLoEnd_BComRe1En_1           4         /*上1次C相过载结束时刻B相组合无功1电能*/
#define	CLOverCLoEnd_BComRe2En_1           4         /*上1次C相过载结束时刻B相组合无功2电能*/
#define	CLOverCLoEnd_CPosAcEn_1            4         /*上1次C相过载发生时刻C相正向有功电能*/
#define	CLOverCLoEnd_CRevAcEn_1            4         /*上1次C相过载发生时刻C相反向有功电能*/
#define	CLOverCLoEnd_CComRe1En_1           4         /*上1次C相过载结束时刻C相组合无功1电能*/
#define	CLOverCLoEnd_CComRe2En_1           4         /*上1次C相过载结束时刻C相组合无功2电能*/
#define	CLOverCLo_FF_1                     140       /*上1次C相过载数据块*/
#define	CLOverCLo_HpData_1                 70        /*上1次C相过载发生数据*/
#define	CLOverCLo_EndData_1                70        /*上1次C相过载结束数据*/

/**********功率因数超下限**********/
/*698相关定义*/
#define CLPFactorT_Over_Current            8        /*总功率因数超下限事件当前值记录表*/
#define CLPFactorT_Over_Degree             4        /*总功率因数超下限事件发生次数*/
#define CLPFactorT_Over_Time               4        /*总功率因数超下限事件累计时间*/

#define CLPFactorA_Over_Current            8        /*A相功率因数超下限事件当前值记录表*/
#define CLPFactorA_Over_Degree             4        /*A相功率因数超下限事件发生次数*/
#define CLPFactorA_Over_Time               4        /*A相功率因数超下限事件累计时间*/

#define CLPFactorB_Over_Current            8        /*B相功率因数超下限事件当前值记录表*/
#define CLPFactorB_Over_Degree             4        /*B相功率因数超下限事件发生次数*/
#define CLPFactorB_Over_Time               4        /*B相功率因数超下限事件累计时间*/

#define CLPFactorC_Over_Current            8        /*C相功率因数超下限事件当前值记录表*/
#define CLPFactorC_Over_Degree             4        /*C相功率因数超下限事件发生次数*/
#define CLPFactorC_Over_Time               4        /*C相功率因数超下限事件累计时间*/

/*645相关定义*/
/**********总功率因数超下限**********/
/*上2次-上10次 总功率因数超下限 事件记录数据长度 同上1次*/
#define	CLPFactorT_Over_Hp_1               6       /*上1次总功率因数超下限发生时刻*/
#define	CLPFactorTHp_PosAcTolEn_1          4       /*上1次总功率因数超下限发生时刻正向有功总电能*/
#define	CLPFactorTHp_RevAcTolEn_1          4       /*上1次总功率因数超下限发生时刻反向有功总电能*/
#define	CLPFactorTHp_ComRe1TolEn_1         4       /*上1次总功率因数超下限发生时刻组合无功1总电能*/
#define	CLPFactorTHp_ComRe2TolEn_1         4       /*上1次总功率因数超下限发生时刻组合无功2总电能*/
#define	CLPFactorT_Over_End_1              6       /*上1次总功率因数超下限结束时刻*/
#define	CLPFactorTEnd_PosAcTolEn_1         4       /*上1次总功率因数超下限结束时刻正向有功总电能*/
#define	CLPFactorTEnd_RevAcTolEn_1         4       /*上1次总功率因数超下限结束时刻反向有功总电能*/
#define	CLPFactorTEnd_ComRe1TolEn_1        4       /*上1次总功率因数超下限结束时刻组合无功1总电能*/
#define	CLPFactorTEnd_ComRe2TolEn_1        4       /*上1次总功率因数超下限结束时刻组合无功2总电能*/
#define	CLPFactorT_FF_1                    44      /*上1次总功率因数超下限数据块*/
#define	CLPFactorT_HpData_1                22      /*上1次总功率因数超下限发生数据*/
#define	CLPFactorT_EndData_1               22      /*上1次总功率因数超下限结束数据*/

/**************A相**************/
/*上2次-上10次 A相功率因数超下限 事件记录数据长度 同上1次*/
#define	CLPFactorA_Over_Hp_1               6       /*上1次A相功率因数超下限发生时刻*/
#define	CLPFactorAHp_PosAcTolEn_1          4       /*上1次A相功率因数超下限发生时刻正向有功总电能*/
#define	CLPFactorAHp_RevAcTolEn_1          4       /*上1次A相功率因数超下限发生时刻反向有功总电能*/
#define	CLPFactorAHp_ComRe1TolEn_1         4       /*上1次A相功率因数超下限发生时刻组合无功1总电能*/
#define	CLPFactorAHp_ComRe2TolEn_1         4       /*上1次A相功率因数超下限发生时刻组合无功2总电能*/
#define	CLPFactorA_Over_End_1              6       /*上1次A相功率因数超下限结束时刻*/
#define	CLPFactorAEnd_PosAcTolEn_1         4       /*上1次A相功率因数超下限结束时刻正向有功总电能*/
#define	CLPFactorAEnd_RevAcTolEn_1         4       /*上1次A相功率因数超下限结束时刻反向有功总电能*/
#define	CLPFactorAEnd_ComRe1TolEn_1        4       /*上1次A相功率因数超下限结束时刻组合无功1总电能*/
#define	CLPFactorAEnd_ComRe2TolEn_1        4       /*上1次A相功率因数超下限结束时刻组合无功2总电能*/
#define	CLPFactorA_FF_1                    44      /*上1次A相功率因数超下限数据块*/
#define	CLPFactorA_HpData_1                22      /*上1次A相功率因数超下限发生数据*/
#define	CLPFactorA_EndData_1               22      /*上1次A相功率因数超下限结束数据*/

/**************B相**************/
/*上2次-上10次 B相功率因数超下限 事件记录数据长度 同上1次*/
#define	CLPFactorB_Over_Hp_1               6       /*上1次B相功率因数超下限发生时刻*/
#define	CLPFactorBHp_PosAcTolEn_1          4       /*上1次B相功率因数超下限发生时刻正向有功总电能*/
#define	CLPFactorBHp_RevAcTolEn_1          4       /*上1次B相功率因数超下限发生时刻反向有功总电能*/
#define	CLPFactorBHp_ComRe1TolEn_1         4       /*上1次B相功率因数超下限发生时刻组合无功1总电能*/
#define	CLPFactorBHp_ComRe2TolEn_1         4       /*上1次B相功率因数超下限发生时刻组合无功2总电能*/
#define	CLPFactorB_Over_End_1              6       /*上1次B相功率因数超下限结束时刻*/
#define	CLPFactorBEnd_PosAcTolEn_1         4       /*上1次B相功率因数超下限结束时刻正向有功总电能*/
#define	CLPFactorBEnd_RevAcTolEn_1         4       /*上1次B相功率因数超下限结束时刻反向有功总电能*/
#define	CLPFactorBEnd_ComRe1TolEn_1        4       /*上1次B相功率因数超下限结束时刻组合无功1总电能*/
#define	CLPFactorBEnd_ComRe2TolEn_1        4       /*上1次B相功率因数超下限结束时刻组合无功2总电能*/
#define	CLPFactorB_FF_1                    44      /*上1次B相功率因数超下限数据块*/
#define	CLPFactorB_HpData_1                22      /*上1次B相功率因数超下限发生数据*/
#define	CLPFactorB_EndData_1               22      /*上1次B相功率因数超下限结束数据*/

/**************C相**************/
/*上2次-上10次 C相功率因数超下限 事件记录数据长度 同上1次*/
#define	CLPFactorC_Over_Hp_1               6       /*上1次C相功率因数超下限发生时刻*/
#define	CLPFactorCHp_PosAcTolEn_1          4       /*上1次C相功率因数超下限发生时刻正向有功总电能*/
#define	CLPFactorCHp_RevAcTolEn_1          4       /*上1次C相功率因数超下限发生时刻反向有功总电能*/
#define	CLPFactorCHp_ComRe1TolEn_1         4       /*上1次C相功率因数超下限发生时刻组合无功1总电能*/
#define	CLPFactorCHp_ComRe2TolEn_1         4       /*上1次C相功率因数超下限发生时刻组合无功2总电能*/
#define	CLPFactorC_Over_End_1              6       /*上1次C相功率因数超下限结束时刻*/
#define	CLPFactorCEnd_PosAcTolEn_1         4       /*上1次C相功率因数超下限结束时刻正向有功总电能*/
#define	CLPFactorCEnd_RevAcTolEn_1         4       /*上1次C相功率因数超下限结束时刻反向有功总电能*/
#define	CLPFactorCEnd_ComRe1TolEn_1        4       /*上1次C相功率因数超下限结束时刻组合无功1总电能*/
#define	CLPFactorCEnd_ComRe2TolEn_1        4       /*上1次C相功率因数超下限结束时刻组合无功2总电能*/
#define	CLPFactorC_FF_1                    44      /*上1次C相功率因数超下限数据块*/
#define	CLPFactorC_HpData_1                22      /*上1次C相功率因数超下限发生数据*/
#define	CLPFactorC_EndData_1               22      /*上1次C相功率因数超下限结束数据*/

/***********************************计量芯片故障记录*******************************************/
/*698相关定义*/
#define CLMeterFa_Current                  9        /*计量芯片故障事件当前值记录表*/
#define CLMeterFa_Source                   1        /*计量芯片故障事件发生源*/
#define CLMeterFa_Degree                   4        /*计量芯片故障事件发生次数*/
#define CLMeterFa_Time                     4        /*计量芯片故障事件累计时间*/
#define CLMeterFa_Note_1                   25       /*上1次计量芯片故障记录，此长度用于填充表格，具体值以数据层返回长度为准*/

/***********************************时钟故障记录*******************************************/
/*698相关定义*/
#define CLClockFa_Current                  9        /*时钟故障事件当前值记录表*/
#define CLClockFa_Source                   1        /*时钟故障事件发生源*/
#define CLClockFa_Degree                   4        /*时钟故障事件发生次数*/
#define CLClockFa_Time                     4        /*时钟故障事件累计时间*/
#define CLClockFa_Note_1                   25       /*上1次时钟故障记录，此长度用于填充表格，具体值以数据层返回长度为准*/

/***********************************零线电流异常记录*******************************************/
/*698相关定义*/
#define CLNeutralCurrentAbnormal_Current       9        /*零线电流异常事件当前值记录表*/
#define CLNeutralCurrentAbnormal_Source        1        /*零线电流异常事件发生源*/
#define CLNeutralCurrentAbnormal_Degree        4        /*零线电流异常事件发生次数*/
#define CLNeutralCurrentAbnormal_Time          4        /*零线电流异常事件累计时间*/
#define CLNeutralCurrentAbnormal_Note_1        25       /*上1次(上10次）零线电流异常记录*/


/***********************************编程及其他事件记录*******************************************/
/***********************************电表总清*******************************************/
/*698相关定义*/
#define CLTol_Clear_Current                9            /*电表清零当前值记录表*/
#define CLTol_Clear_Source                 1            /*电表清零发生源*/
#define CLTol_Clear                        8            /*电表清零发生次数、累计时间*/
#define CLTol_Clear_Degree                 4            /*电表清零发生次数*/
#define CLTol_Clear_Time                   4            /*电表清零累计时间*/
#define CLTol_Clear_Note_1                 106          /*上1次(上10次)电表清零记录*/

/**********************************需量清零*******************************************/
/*698相关定义*/
#define CLDe_Clear_Source                  1            /*电表需清发生源*/
#define CLDe_Clear_Degree                  4            /*电表需量发生次数*/
#define CLDe_Clear_Note_1                  202          /*上1次(上10次)需量清零记录*/

/***********************************事件清零*******************************************/
/*698相关定义*/
#define CLEven_Clear_Source                1            /*事件清零发生源*/
#define CLEven_Clear_Degree                4            /*事件清零发生次数*/
#define CLEven_Clear_Note_1                14           /*上1次(上10次)事件清零记录*/

/***********************************编程记录*******************************************/
/*698相关定义*/
#define CLProgram_Source                   1            /*编程事件发生源*/
#define CLProgram_Degree                   4            /*编程事件发生次数*/
#define CLProgram_Note_1                   70           /*上1次(上10次)编程记录*/

/*山东双协议增加*/
#define CLProgram_Degree_645               4            /*编程记录总次数*/
#define CLProgram_Note_1_645               50           /*上1次(上10次)编程记录*/

/***********************************校时记录*******************************************/
/*698相关定义*/
#define CLAdjTime_Source                   1            /*校时事件发生源*/
#define CLAdjTime_Degree                   4            /*校时事件发生次数*/
#define CLAdjTime_Note_1                   33           /*上1次(上10次)校时记录*/

/***********************************广播校时记录*******************************************/
/*698相关定义*/
#define CLBroadcastTime_Source             1            /*广播校时事件发生源*/
#define CLBroadcastTime_Degree             4            /*广播校时事件发生次数*/
#define CLBroadcastTime_Note_1             33           /*上1次(上100次)广播校时记录*/

/***********************************时段表编程记录*******************************************/
/*698相关定义*/
#define CLProgPT_Source                    1            /*时段表编程事件发生源*/
#define CLProgPT_Degree                    4            /*时段表编程事件发生次数*/

/*645相关定义*/
#define CLProgPT_Note_1                    65           /*上1次(上10次)时段表编程记录*/
#define CLProgPT_NoteC_1                   178          /*上1次(上10次)时段表编程记录自扩C*/
#define CLProgPT_NoteD_1                   168          /*上1次(上10次)时段表编程记录自扩D*/
#define CLProgPT_NoteE_1                   168          /*上1次(上10次)时段表编程记录自扩E*/
#define CLProgPT_NoteF_1                   168          /*上1次(上10次)时段表编程记录自扩F*/

/*山东双协议增加*/
#define CLProgPT_CurrentPart_Degree        4            /*时段表编程记录总次数*/
#define CLProgPT_CurrentPart_Note_1        682          /*上1次(上10次)时段表编程记录*/

/***********************************时区表编程记录*******************************************/
/*698相关定义*/
#define CLProgTZ_Source                    1            /*时区表编程事件发生源*/
#define CLProgTZ_Degree                    4            /*时区表编程事件发生次数*/
#define CLProgTZ_Note_1                    61           /*上1次(上10次)时区表编程记录*/

/*山东双协议增加,用于645协议存储记录中当前套时区表，用于数据层存储(时间6+数据3*14)*/
#define CLProgTZ_CurrentPart_Degree        4            /*时区表编程记录总次数*/
#define CLProgTZ_CurrentPart_Note_1        48           /*上1次(上10次)时区表编程记录*/

/***********************************周休日编程记录*******************************************/
/*698相关定义*/
#define CLProgWRe_Source                   1            /*周休日编程事件发生源*/
#define CLProgWRe_Degree                   4            /*周休日编程事件发生次数*/
#define CLProgWRe_Note_1                   20           /*上1次(上10次)周休日编程记录*/

/***********************************节假日编程记录*******************************************/
/*698相关定义*/
#define CLProgHol_Source                   1            /*节假日编程事件发生源*/
#define CLProgHol_Degree                   4            /*节假日编程事件发生次数*/

/*645相关定义*/
#define CLProgHol_Note_1                   29           /*上1次(上10次)节假日编程记录*/
#define CLProgHol_Note9_1                  194          /*上1次(上10次)节假日编程记录自扩9*/
#define CLProgHol_NoteA_1                  192          /*上1次(上10次)节假日编程记录自扩A*/
#define CLProgHol_NoteB_1                  192          /*上1次(上10次)节假日编程记录自扩B*/
#define CLProgHol_NoteC_1                  192          /*上1次(上10次)节假日编程记录自扩C*/
#define CLProgHol_NoteD_1                  192          /*上1次(上10次)节假日编程记录自扩D*/
#define CLProgHol_NoteE_1                  64           /*上1次(上10次)节假日编程记录自扩E*/

/***********************************有功组合方式编程记录*******************************************/
#define CLProgAcC_Source                   1            /*有功组合方式编程事件发生源*/
#define CLProgAcC_Degree                   4            /*有功组合方式编程事件发生次数*/
#define CLProgAcC_Note_1                   20           /*上1次(上10次)有功组合方式编程记录*/

/***********************************无功组合方式编程记录*******************************************/
#define CLProgReC_Current                  9            /*无功组合方式编程事件当前值记录表*/
#define CLProgReC_Source                   1            /*无功组合方式编程事件发生源,适用无功1、无功2*/
#define CLProgReC                          8            /*无功组合方式编程事件发生次数、累计时间,适用无功1、无功2*/
#define CLProgReC_Degree                   4            /*无功组合方式编程事件发生次数,适用无功1、无功2*/
#define CLProgReC_Time                     4            /*无功组合方式编程事件累计时间,适用无功1、无功2*/
#define CLProgReC_Note_1                   20           /*上1次(上10次)无功组合方式编程记录,适用无功1、无功2*/

#define CLProgReC1_Source                  1            /*无功组合方式编程录发生源,适用无功1、无功2*/
#define CLProgReC1_Degree                  4            /*无功组合方式1编程记录总次数*/
#define CLProgReC1_Note_1                  20           /*上1次(上10次)无功组合方式1编程记录*/

#define CLProgReC2_Source                  1            /*无功组合方式编程录发生源,适用无功1、无功2*/
#define CLProgReC2_Degree                  4            /*无功组合方式2编程记录总次数*/
#define CLProgReC2_Note_1                  20           /*上1次(上10次)无功组合方式2编程记录*/

/**********************************结算日编程记录*******************************************/
#define CLProgSettD_Source                 1            /*结算日编程事件发生源*/
#define CLProgSettD_Degree                 4            /*结算日编程事件发生次数*/
#define CLProgSettD_Note_1                 16           /*上1次(上10次)结算日编程记录*/

/**********************************费率参数表编程记录*******************************************/
#define CLProgTPara_Source                 1           /*费率参数表编程事件发生源*/
#define CLProgTPara_Degree                 4           /*费率参数表编程事件发生次数*/
#define CLProgTPara_Note_1                 106         /*上1次(上10次)费率参数表编程记录*/

/***********************************阶梯表编程记录*******************************************/
#define CLProgLad_Source                   1           /*阶梯表编程事件发生源*/
#define CLProgLad_Degree                   4           /*阶梯表编程事件发生次数*/
#define CLProgLad_Note_1                   138         /*上1次(上10次)阶梯表编程记录*/

/***********************************密钥编程记录*******************************************/
#define CLProgKD_Source                    1           /*密钥编程事件发生源*/
#define CLProgKD_Degree                    4           /*密钥编程事件发生次数*/
#define CLProgKD_Note_1                    15          /*上1次(上10次)密钥编程记录*/

/***********************************异常插卡记录*******************************************/
#define CLAbnorC_Source                    1           /*异常插卡事件发生源*/
#define CLAbnorC_Degree                    4           /*异常插卡事件发生次数*/
#define CLAbnormalCard_CareNo			   8		   /*异常插卡卡序列号*/
#define CLAbnormalCard_ErrorStatus		   1		   /*异常插卡错误状态字*/
#define CLAbnormalCard_OrderHead		   5		   /*异常插卡插卡操作命令头*/
#define CLAbnormalCard_ErrorRespondStatus  2		   /*异常插卡插卡错误响应状态*/
#define CLAbnorC_NoteRelate4               16          /*异常插卡记录相关数据包含：卡序列号、插卡错误信息字、插卡操作命令头、插卡错误响应状态*/
#define CLLawlessC_Degree                  4           /*非法插卡总次数*/
#define CLAbnorC_Note_1                    36          /*上1次(上10次)异常插卡记录*/

/***********************************开表盖记录*******************************************/
#define CLOpenW_Current                    9           /*开表盖事件当前值记录表*/
#define CLOpenW_Source                     1           /*开表盖事件发生源*/
#define CLOpenW_Degree                     4           /*开表盖事件发生次数*/
#define CLOpenW_Time                       4           /*开表盖事件累计时间*/
#define CLOpenW_Note_1                     60          /*上1次(上10次)开表盖记录*/

/***********************************开端钮盖记录*******************************************/
#define CLOpenCW_Current                   9           /*开端钮盖事件当前值记录表*/
#define CLOpenCW_Source                    1           /*开端钮盖事件发生源*/
#define CLOpenCW_Degree                    4           /*开端钮盖事件发生次数*/
#define CLOpenCW_Time                      4           /*开端钮盖事件累计时间*/
#define CLOpenCW_Note_1                    60          /*上1次(上10次)开端钮盖记录*/

/***********************************购电记录*******************************************/
#define CLBuyCurr_Source                   1          /*购电事件发生源*/
#define CLBuyCurr_Degree                   4          /*购电事件发生次数*/

#define CLBuyCurr_T_1                      5          /*上1次(上10次)购电日期*/
#define CLBuyCurr_Degree_1                 2          /*上1次(上10次)购电后总购电次数*/
#define CLBuyCurr_Money_1                  4          /*上1次(上10次)购电金额*/
#define CLBuyCurr_BMoney_1                 4          /*上1次(上10次)购电前剩余金额*/
#define CLBuyCurr_AMoney_1                 4          /*上1次(上10次)购电后剩余金额*/
#define CLBuyCurr_TMoney_1                 4          /*上1次(上10次)购电后累计购电金额*/
#define CLBuyCurr_FF_Note_1                23         /*上1次(上10次)购电记录*/

/***********************************退费记录*******************************************/
#define CLReturn_M_Source                  1          /*退费事件发生源*/
#define CLReturn_M_Degree                  4          /*退费事件发生次数*/
#define CLReturn_M_Note_1                  19         /*上1次(上10次)退费记录*/

/***********************************恒定磁场干扰记录*******************************************/
#define CLConM_Current                     9          /*恒定磁场干扰事件当前值记录表*/
#define CLConM_Source                      1          /*恒定磁场干扰事件发生源*/
#define CLConM_Degree                      4          /*恒定磁场干扰事件发生次数*/
#define CLConM_Time                        4          /*恒定磁场干扰事件累计时间*/
#define CLConM_Note_1                      28         /*上1次(上10次)恒定磁场干扰记录*/

/***********************************负荷开关误动作记录*******************************************/
#define CLRelayFa_Current                  9          /*负荷开关误动作事件当前值记录表*/
#define CLRelayFa_Source                   1          /*负荷开关误动作事件发生源*/
#define CLRelayFa_Degree                   4          /*负荷开关误动作事件发生次数*/
#define CLRelayFa_Time                     4          /*负荷开关误动作事件累计时间*/

/*645相关定义*/
#define CLRelayFa_Note_1                   29         /*上1次(上10次)负荷开关误动作记录*/
#define CLRelayFa_HpT_NoteB_1              6          /*上1次(上10次)负荷开关误动作发生时刻自扩B*/
#define CLRelayFa_Sta_NoteC_1              1          /*上1次(上10次)负荷开关误动作后状态自扩C*/
#define CLRelayFa_HpEn_NoteD_1             8          /*上1次(上10次)负荷开关误动作发生时刻正、反向有功总电能自扩D*/
#define CLRelayFa_EndT_NoteE_1             6          /*上1次(上10次)负荷开关误动作结束时刻自扩E*/
#define CLRelayFa_EndEn_NoteF_1            8          /*上1次(上10次)负荷开关误动作结束时刻正、反向有功总电能自扩F*/

/***********************************电源异常记录*******************************************/
#define CLPowerFa_Current                  9          /*电源异常事件当前值记录表*/
#define CLPowerFa_Source                   1          /*电源异常事件发生源*/
#define CLPowerFa_Degree                   4          /*电源异常事件发生次数*/
#define CLPowerFa_Time                     4          /*电源异常事件累计时间*/
#define CLPowerFa_Note_1                   20         /*上1次(上10次)电源异常记录*/

/**********************************跳闸记录*****************************************/
#define CLRelayOpen_Source                 1          /*跳闸事件发生源*/
#define CLRelayOpen_Degree                 4          /*跳闸事件发生次数*/

/*645相关定义*/
#define	CLRelayOpen_Hp_T_1                 6          /*上1次(上10次)跳闸发生时刻*/
#define	CLRelayOpen_OpeCode_1              4          /*上1次(上10次)跳闸操作者代码*/
#define	CLRelayOpen_Pos_Ac_En_1            4          /*上1次(上10次)跳闸时正向有功总电能*/
#define	CLRelayOpen_Rev_Ac_En_1            4          /*上1次(上10次)跳闸时反向有功总电能*/
#define	CLRelayOpen_Qua1_Re_En_1           4          /*上1次(上10次)跳闸时第1象限无功总电能*/
#define	CLRelayOpen_Qua2_Re_En_1           4          /*上1次(上10次)跳闸时第2象限无功总电能*/
#define	CLRelayOpen_Qua3_Re_En_1           4          /*上1次(上10次)跳闸时第3象限无功总电能*/
#define	CLRelayOpen_Qua4_Re_En_1           4          /*上1次(上10次)跳闸时第4象限无功总电能*/
#define	CLRelayOpen_FF_1                   34         /*上1次(上10次)跳闸记录数据块*/

/***********************************合闸记录*******************************************/
#define CLRelayClose_Source                1          /*合闸事件发生源*/
#define CLRelayClose_Degree                4          /*合闸事件发生次数*/

/*645相关定义*/
#define	CLRelayClose_Hp_T_1                6          /*上1次(上10次)合闸发生时刻*/
#define	CLRelayClose_OpeCode_1             4          /*上1次(上10次)合闸操作者代码*/
#define	CLRelayClose_Pos_Ac_En_1           4          /*上1次(上10次)合闸时正向有功总电能*/
#define	CLRelayClose_Rev_Ac_En_1           4          /*上1次(上10次)合闸时反向有功总电能*/
#define	CLRelayClose_Qua1_Re_En_1          4          /*上1次(上10次)合闸时第1象限无功总电能*/
#define	CLRelayClose_Qua2_Re_En_1          4          /*上1次(上10次)合闸时第2象限无功总电能*/
#define	CLRelayClose_Qua3_Re_En_1          4          /*上1次(上10次)合闸时第3象限无功总电能*/
#define	CLRelayClose_Qua4_Re_En_1          4          /*上1次(上10次)合闸时第4象限无功总电能*/
#define	CLRelayClose_FF_1                  34         /*上1次(上10次)合闸记录数据块*/

/***************************软IJ有效时间编程记录**************************************/
/*645相关定义*/
#define CLSoft_I_J_Prog_Degree             4          /*软IJ有效时间编程总次数*/
/*上3次-上10次软IJ编程记录数据长度未定义*/
#define	CLSoft_I_J_Prog_1                  11      /*上1次软IJ编程记录*/
#define	CLSoft_I_J_Prog_2                  11      /*上2次软IJ编程记录*/

/***********************************校表记录*******************************************/
/*645相关定义*/
#define CLRec_Meter_Degree                 4          /*校表总次数*/
/*上2次-上9次校表发生时刻数据长度未定义*/
#define	CLRec_Meter_Hp_T_1	               7          /*上1次校表发生时刻*/
#define	CLRec_Meter_Hp_T_10	               7          /*上10次校表发生时刻*/
/*2号-253号校表参数校表前数据长度未定义*/
#define	CLRec_Meter_Bef1_Data_1            4          /*上1次1号校表参数校表前数据*/
#define	CLRec_Meter_Bef1_Data_254          4          /*上1次254号校表参数校表前数据*/
#define	CLRec_Meter_Bef2_Data_1            4          /*上2次1号校表参数校表前数据*/
#define	CLRec_Meter_Bef2_Data_254          4          /*上2次254号校表参数校表前数据*/
#define	CLRec_Meter_Bef3_Data_1            4          /*上3次1号校表参数校表前数据*/
#define	CLRec_Meter_Bef3_Data_254          4          /*上3次254号校表参数校表前数据*/
#define	CLRec_Meter_Bef4_Data_1            4          /*上4次1号校表参数校表前数据*/
#define	CLRec_Meter_Bef4_Data_254          4          /*上4次254号校表参数校表前数据*/
#define	CLRec_Meter_Bef5_Data_1            4          /*上5次1号校表参数校表前数据*/
#define	CLRec_Meter_Bef5_Data_254          4          /*上5次254号校表参数校表前数据*/
#define	CLRec_Meter_Bef6_Data_1            4          /*上6次1号校表参数校表前数据*/
#define	CLRec_Meter_Bef6_Data_254          4          /*上6次254号校表参数校表前数据*/
#define	CLRec_Meter_Bef7_Data_1            4          /*上7次1号校表参数校表前数据*/
#define	CLRec_Meter_Bef7_Data_254          4          /*上7次254号校表参数校表前数据*/
#define	CLRec_Meter_Bef8_Data_1            4          /*上8次1号校表参数校表前数据*/
#define	CLRec_Meter_Bef8_Data_254          4          /*上8次254号校表参数校表前数据*/
#define	CLRec_Meter_Bef9_Data_1            4          /*上9次1号校表参数校表前数据*/
#define	CLRec_Meter_Bef9_Data_254          4          /*上9次254号校表参数校表前数据*/
#define	CLRec_Meter_Bef10_Data_1           4          /*上10次1号校表参数校表前数据*/
#define	CLRec_Meter_Bef10_Data_254         4          /*上10次254号校表参数校表前数据*/
#define	CLRec_Meter_FF_Data_1              1022       /*上1次校表记录数据集合*/

/*********************************事件类参数相关定义**************************************/
#define	CLLossVolage_Vol_UpLim             2          /*失压事件电压触发上限*/
#define	CLLossVolage_Vol_LowLim            2          /*失压事件电压恢复下限*/
#define	CLLossVolage_Curr_LowLim           4          /*失压事件电流触发下限*/
#define	CLLossVolage_Delay_T               1          /*失压事件判断延时时间*/
#define	CLLossVolage_Parameter             9          /*失压事件判断条件数据块*/

#define	CLLowVolage_Vol_UpLim              2          /*欠压事件电压触发上限*/
#define	CLLowVolage_Delay_T                1          /*欠压事件判断延时时间*/
#define	CLLowVolage_Parameter              3          /*欠压事件判断条件数据块*/

#define	CLOverVolage_Vol_LowLim            2          /*过压事件电压触发下限*/
#define	CLOverVolage_Delay_T               1          /*过压事件判断延时时间*/
#define	CLOverVolage_Parameter             3          /*过压事件判断条件数据块*/

#define	CLBreakVol_Vol_UpLim               2          /*断相事件电压触发上限*/
#define	CLBreakVol_Curr_UpLim              4          /*断相事件电流触发上限*/
#define	CLBreakVol_Delay_T                 1          /*断相事件判定延时时间*/
#define	CLBreakVol_Parameter               7          /*断相事件判断条件数据块*/

#define	CLLossCurr_Vol_LowLim              2          /*失流事件电压触发下限*/
#define	CLLossCurr_Curr_UpLim              4          /*失流事件电流触发上限*/
#define	CLLossCurr_Curr_LowLim             4          /*失流事件电流触发下限*/
#define	CLLossCurr_Delay_T                 1          /*失流事件判断延时时间*/
#define	CLLossCurr_Parameter               11         /*失流事件判断条件数据块*/

#define	CLOverCurr_Curr_LowLim             4          /*过流事件电流触发下限*/
#define	CLOverCurr_Delay_T                 1          /*过流事件判断延时时间*/
#define	CLOverCurr_Parameter               5          /*过流事件判断条件数据块*/

#define	CLBreakCurr_Vol_LowLim             2          /*断流事件电压触发下限*/
#define	CLBreakCurr_Curr_UpLim             4          /*断流事件电流触发上限*/
#define	CLBreakCurr_Delay_T                1          /*断流事件判定延时时间*/
#define	CLBreakCurr_Parameter              7          /*断流事件判断条件数据块*/

#define	CLPowerRev_AcPower_LowLim          4          /*功率反向事件有功功率触发下限*/
#define	CLPowerRev_Delay_T                 1          /*功率反向事件判定延时时间*/
#define	CLPowerRev_Parameter               5          /*功率反向事件判断条件数据块*/

#if 1	/*潮流反向事件已不存在，后续需删除*/
#define	CLTrendRev_AcPower_LowLim          4          /*潮流反向事件有功功率触发下限*/
#define	CLTrendRev_Delay_T                 1          /*潮流反向事件判定延时时间*/
#endif

#define	CLOverLoad_AcPower_LowLim          4          /*过载事件有功功率触发下限*/
#define	CLOverLoad_Delay_T                 1          /*过载事件判定延时时间*/
#define	CLOverLoad_Parameter               5          /*过载事件判断条件数据块*/

#define	CLReDemandOv_De_LowLim             4          /*无功需量超限事件需量触发下限*/
#define	CLReDemandOv_Delay_T               1          /*无功需量超限事件判定延时时间*/
#define	CLReDemandOv_Parameter             5          /*无功需量超限事件判断条件数据块*/

#define	CLPowerFactor_LowLim               2          /*功率因数超下限阀值*/
#define	CLPowerFactor_Delay_T              1          /*功率因素超下限判定延时时间*/
#define	CLPowerFactor_Parameter            3          /*功率因素超下限判断条件数据块*/

#define	CLPosAcDemandOv_De_LowLim          4          /*正向有功需量超限事件需量触发下限*/
#define	CLPosAcDemandOv_Delay_T            1          /*正向有功需量超限事件判定延时时间*/
#define	CLPosAcDemandOv_Parameter          5          /*正向有功需量超限事件判断条件数据块*/

#define	CLRevAcDemandOv_De_LowLim          4          /*反向有功需量超限事件需量触发下限*/
#define	CLRevAcDemandOv_Delay_T            1          /*反向有功需量超限事件判定延时时间*/
#define	CLRevAcDemandOv_Parameter          5          /*反向有功需量超限事件判断条件数据块*/

#define	CLReversedVoltage_Delay_T          1          /*电压逆相序事件判定延时时间*/
#define	CLReversedVoltage_Parameter        1          /*电压逆相序事件判断条件数据块*/

#define	CLReversedCurrent_Delay_T          1          /*电流逆相序事件判定延时时间*/
#define	CLReversedCurrent_Parameter        1          /*电流逆相序事件判断条件数据块*/

#define	CLPowerOff_Delay_T                 1          /*掉电事件判定延时时间*/
#define	CLPowerOff_Parameter               1          /*掉电事件判断条件数据块*/

#define	CLNoBal_Vol_Lim                    2          /*电压不平衡率限值*/
#define	CLNoBal_Vol_Delay_T                1          /*电压不平衡率判定延时时间*/
#define	CLNoBal_Parameter                  3          /*电压不平衡率判断条件数据块*/

#define	CLNoBal_Curr_Lim                   2          /*电流不平衡率限值*/
#define	CLNoBal_Curr_Delay_T               1          /*电流不平衡率判定延时时间*/
#define	CLNoBal_Parameter                  3          /*电流不平衡率判断条件数据块*/

#define	CLSeriNoBal_Curr_Lim               2          /*电流严重不平衡率限值*/
#define	CLSeriNoBal_Curr_Delay_T           1          /*电流严重不平衡率判定延时时间*/
#define	CLSeriNoBal_Parameter              3          /*电流严重不平衡率判断条件数据块*/

#define	CLNeutralAbnormal_Curr_LowLim      4          /*零线电流异常电流触发下限*/
#define	CLNeutralUnbalanceRate             2          /*零线电流异常不平衡率限值*/
#define	CLNeutralAbnormal_Delay_T          1          /*零线电流异常判定延迟时间*/
#define	CLNeutralAbnormal_Parameter        7          /*零线电流异常判断条件数据块*/

#define	CLAux_Pow_Down_Delay_T             1          /*辅助电源掉电判定延时时间*/
#define	CLAux_Pow_Down_Parameter           1          /*辅助电源掉电判断条件数据块*/

#define	CLClockFa_Delay_T                  1          /*时钟故障判定延时时间*/
#define	CLClockFa_Parameter                1          /*时钟故障判断条件数据块*/

#define	CLMeterFa_Delay_T                  1          /*计量芯片故障判定延时时间*/
#define	CLMeterFa_Parameter                1          /*计量芯片故障判断条件数据块*/

#define CLReport_Type                      1          /*上报方式*/

/***************************事件上报模式字数据长度**************************************/
#define CLReport_Mode                      1          /*上报标识*/
#if 1	/*以下数据后续可统一使用 CLReport_Mode */
#define CLLossVolage_Report_Mode           CLReport_Mode    /*失压上报模式字*/
#define CLLowVolage_Report_Mode            CLReport_Mode    /*欠压上报模式字*/
#define CLOverVolage_Report_Mode           CLReport_Mode    /*过压上报模式字*/
#define CLBreakVol_Report_Mode             CLReport_Mode    /*断相上报模式字*/
#define CLLossCurr_Report_Mode             CLReport_Mode    /*失流上报模式字*/
#define CLOverCurr_Report_Mode             CLReport_Mode    /*过流上报模式字*/
#define CLBreakCurr_Report_Mode            CLReport_Mode    /*断流上报模式字*/
#define CLPowerRev_Report_Mode             CLReport_Mode    /*功率反向上报模式字*/
#define CLOverLoad_Report_Mode             CLReport_Mode    /*过载上报模式字*/
#define CLPosAcDemandOv_Report_Mode        CLReport_Mode    /*正向有功需量超限事件上报模式字*/
#define CLRevAcDemandOv_Report_Mode        CLReport_Mode    /*反向有功需量超限事件上报模式字*/
#define CLReDemandOv_Report_Mode           CLReport_Mode    /*无功需量超限事件上报模式字*/
#define CLPowerFactor_Report_Mode          CLReport_Mode    /*功率因数超下限事件上报模式字*/
#define CLAllLossVolage_Report_Mode        CLReport_Mode    /*全失压上报模式字*/
#define CLAuxPowDown_Report_Mode           CLReport_Mode    /*辅助电源失电上报模式字*/
#define CLReversedVoltage_Report_Mode      CLReport_Mode    /*电压逆相序上报模式字*/
#define CLReversedCurrent_Report_Mode      CLReport_Mode    /*电流逆相序上报模式字*/
#define CLPowerOff_Report_Mode             CLReport_Mode    /*掉电上报模式字*/
#define CLProgram_Report_Mode              CLReport_Mode    /*编程上报模式字*/
#define CLTolClear_Report_Mode             CLReport_Mode    /*电表清零上报模式字*/
#define CLDemandClear_Report_Mode          CLReport_Mode    /*需量清零上报模式字*/
#define CLEventClear_Report_Mode           CLReport_Mode    /*事件清零上报模式字*/
#define CLAdjTime_Report_Mode              CLReport_Mode    /*校时上报模式字*/
#define CLBroadcastTime_Report_Mode        CLReport_Mode    /*广播校时上报模式字*/
#define CLProgPT_Report_Mode               CLReport_Mode    /*时段表编程上报模式字*/
#define CLProgPZ_Report_Mode               CLReport_Mode    /*时区表编程上报模式字*/
#define CLProgWRe_Report_Mode              CLReport_Mode    /*周休日编程上报模式字*/
#define CLProgSettD_Report_Mode            CLReport_Mode    /*结算日编程上报模式字*/
#define CLOpenW_Report_Mode                CLReport_Mode    /*开表盖上报模式字*/
#define CLOpenCW_Report_Mode               CLReport_Mode    /*开端钮盖上报模式字*/
#define CLNoBalVol_Report_Mode             CLReport_Mode    /*电压不平衡上报模式字*/
#define CLNoBalCurr_Report_Mode            CLReport_Mode    /*电流不平衡上报模式字*/
#define CLRelayOpen_Report_Mode            CLReport_Mode    /*跳闸上报模式字*/
#define CLRelayClose_Report_Mode           CLReport_Mode    /*合闸上报模式字*/
#define CLProgHol_Report_Mode              CLReport_Mode    /*节假日编程上报模式字*/
#define CLProgAcC_Report_Mode              CLReport_Mode    /*有功组合方式编程上报模式字*/
#define CLProgReC_Report_Mode              CLReport_Mode    /*无功组合方式编程上报模式字*/
#define CLProgTPara_Report_Mode            CLReport_Mode    /*费率参数表编程上报模式字*/
#define CLProgLad_Report_Mode              CLReport_Mode    /*阶梯表编程上报模式字*/
#define CLKey_Update_Report_Mode           CLReport_Mode    /*密钥更新上报模式字*/
#define CLAbnorC_Report_Mode               CLReport_Mode    /*异常插卡上报模式字*/
#define CLBuyCurr_Report_Mode              CLReport_Mode    /*购电上报模式字*/
#define CLReturnMoney_Report_Mode          CLReport_Mode    /*退费上报模式字*/
#define CLConMEndEn_Report_Mode            CLReport_Mode    /*恒定磁场干扰上报模式字*/
#define CLRelayFaEndEn_Report_Mode         CLReport_Mode    /*负荷开关误动作上报模式字*/
#define CLPowerFa_EndT_Report_Mode         CLReport_Mode    /*电源异常上报模式字*/
#define CLSeriNoBalCurr_Report_Mode        CLReport_Mode    /*电流严重不平衡上报模式字*/
#define CLClockFault_Report_Mode           CLReport_Mode    /*时钟故障上报模式字*/
#define CLMeteringChipFault_Report_Mode    CLReport_Mode    /*计量芯片故障上报模式字*/
#define CLABnor_ZeroCurrent_Report_Mode    CLReport_Mode    /*零线电流异常上报模式字*/
#endif

#define CLFreeTime                         7          /*冻结时间*/
#define CLFreeNum                          4          /*冻结序号*/

/***************************关联列表OAD个数存储时数据长度**************************************/
#define CLVariableAssociatedOADNum         1          /*可变关联OAD个数*/
#if 1	/*以下数据后续可统一使用 CLVariableAssociatedOADNum */
/*冻结类*/
#define CLI_Free_OADTabLen_T               CLVariableAssociatedOADNum    /*瞬时冻结OAD序号表实际长度及周期，原2字节关联列表OAD个数+2字节最小周期，修改为CLVariableAssociatedOADNum字节关联列表OAD个数*/
#define CLMin_Free_OADTabLen_T             CLVariableAssociatedOADNum    /*分钟冻结OAD序号表实际长度及周期*/
#define CLH_Free_OADTabLen_T               CLVariableAssociatedOADNum    /*小时冻结OAD序号表实际长度及周期*/
#define CLD_Free_OADTabLen_T               CLVariableAssociatedOADNum    /*日冻结OAD序号表实际长度及周期*/
#define CLSett_Free_OADTabLen_T            CLVariableAssociatedOADNum    /*结算日冻结OAD序号表实际长度及周期*/
#define CLM_Free_OADTabLen_T               CLVariableAssociatedOADNum    /*月冻结OAD序号表实际长度及周期*/
#define CLYSettle_Free_OADTabLen_T         CLVariableAssociatedOADNum    /*年冻结OAD序号表实际长度及周期，后改为阶梯结算*/
#define CLTZ_Free_OADTabLen_T              CLVariableAssociatedOADNum    /*时区表切换冻结OAD序号表实际长度及周期*/
#define CLPT_Free_OADTabLen_T              CLVariableAssociatedOADNum    /*日时段表切换冻结OAD序号表实际长度及周期*/
#define CLR_Free_OADTabLen_T               CLVariableAssociatedOADNum    /*费率电价切换冻结OAD序号表实际长度及周期*/
#define CLL_Free_OADTabLen_T               CLVariableAssociatedOADNum    /*阶梯电价切换冻结OAD序号表实际长度及周期*/
#define CLY_Free_OADTabLen_T               CLVariableAssociatedOADNum    /*年冻结OAD序号表实际长度及周期*/
/*事件类*/
#define CLAll_Loss_Vol_OADTabLen           CLVariableAssociatedOADNum    /*全失压可变关联列表OAD个数*/
#define CLAux_Pow_Down_OADTabLen           CLVariableAssociatedOADNum    /*辅助电源掉电可变关联列表OAD个数*/
#define CLPow_Down_OADTabLen               CLVariableAssociatedOADNum    /*电源掉电可变关联列表OAD个数*/
#define CLPos_Ac_De_Over_OADTabLen         CLVariableAssociatedOADNum    /*正向有功需量可变关联列表OAD个数*/
#define CLRev_Ac_De_Over_OADTabLen         CLVariableAssociatedOADNum    /*反向有功需量超限事件可变关联列表OAD个数*/
#define CLQua_Re_De_Over_OADTabLen         CLVariableAssociatedOADNum    /*无功需量超限可变关联列表OAD个数*/
#define CLLoss_Vol_OADTabLen               CLVariableAssociatedOADNum    /*失压可变关联列表OAD个数*/
#define CLLow_Vol_OADTabLen                CLVariableAssociatedOADNum    /*欠压可变关联列表OAD个数*/
#define CLOver_Vol_OADTabLen               CLVariableAssociatedOADNum    /*过压可变关联列表OAD个数*/
#define CLBreak_Vol_OADTabLen              CLVariableAssociatedOADNum    /*断相可变关联列表OAD个数*/
#define CLRevPS_Vol_OADTabLen              CLVariableAssociatedOADNum    /*电压逆相序可变关联列表OAD个数*/
#define CLRevPS_Curr_OADTabLen             CLVariableAssociatedOADNum    /*电流逆相序可变关联列表OAD个数*/
#define CLNoBal_Vol_OADTabLen              CLVariableAssociatedOADNum    /*电压不平衡可变关联列表OAD个数*/
#define CLNoBal_Curr_OADTabLen             CLVariableAssociatedOADNum    /*电流不平衡可变关联列表OAD个数*/
#define CLSevNoBal_Curr_OADTabLen          CLVariableAssociatedOADNum    /*电流严重不平衡可变关联列表OAD个数*/
#define CLLoss_Curr_OADTabLen              CLVariableAssociatedOADNum    /*失流可变关联列表OAD个数*/
#define CLOver_Curr_OADTabLen              CLVariableAssociatedOADNum    /*过流可变关联列表OAD个数*/
#define CLBreak_Curr_OADTabLen             CLVariableAssociatedOADNum    /*断流可变关联列表OAD个数*/
#define CLPower_Rev_OADTabLen              CLVariableAssociatedOADNum    /*功率反向可变关联列表OAD个数*/
#define CLOver_Lo_OADTabLen                CLVariableAssociatedOADNum    /*过载可变关联列表OAD个数*/
#define CLTol_Clear_OADTabLen              CLVariableAssociatedOADNum    /*总清可变关联列表OAD个数*/
#define CLDe_Clear_OADTabLen               CLVariableAssociatedOADNum    /*需清可变关联列表OAD个数*/
#define CLEven_Clear_OADTabLen             CLVariableAssociatedOADNum    /*编程记录可变关联列表OAD个数*/
#define CLProgram_OADTabLen                CLVariableAssociatedOADNum    /*异常插卡记录可变关联列表OAD个数*/
#define CLAbnorC_OADTabLen                 CLVariableAssociatedOADNum    /*异常插卡记录可变关联列表OAD个数*/
#define CLOpenW_OADTabLen                  CLVariableAssociatedOADNum    /*开盖记录可变关联列表OAD个数*/
#define CLOpenCW_OADTabLen                 CLVariableAssociatedOADNum    /*购电记录可变关联列表OAD个数*/
#define CLBuyCurr_OADTabLen                CLVariableAssociatedOADNum    /*购电记录可变关联列表OAD个数*/
#define CLReturn_M_OADTabLen               CLVariableAssociatedOADNum    /*退费记录可变关联列表OAD个数*/
#define CLConM_OADTabLen                   CLVariableAssociatedOADNum    /*恒定磁场可变关联列表OAD个数*/
#define CLRelayFa_OADTabLen                CLVariableAssociatedOADNum    /*继电器异常可变关联列表OAD个数*/
#define CLPowerFa_OADTabLen                CLVariableAssociatedOADNum    /*电源异常可变关联列表OAD个数*/
#define CLRelayOpen_OADTabLen              CLVariableAssociatedOADNum    /*跳闸记录可变关联列表OAD个数*/
#define CLRelayClose_OADTabLen             CLVariableAssociatedOADNum    /*合闸记录可变关联列表OAD个数*/
#define CLPFactorT_Over_OADTabLen          CLVariableAssociatedOADNum    /*总功率因数超限可变关联列表OAD个数*/
#define CLAdjTime_OADTabLen                CLVariableAssociatedOADNum    /*校时可变关联列表OAD个数*/
#define CLBroadcastTime_OADTabLen          CLVariableAssociatedOADNum    /*广播校时可变关联列表OAD个数*/
#define CLProgPT_OADTabLen                 CLVariableAssociatedOADNum    /*时段表编程可变关联列表OAD个数*/
#define CLProgTZ_OADTabLen                 CLVariableAssociatedOADNum    /*时区表编程可变关联列表OAD个数*/
#define CLProgWRe_OADTabLen                CLVariableAssociatedOADNum    /*周休日编程可变关联列表OAD个数*/
#define CLProgHol_OADTabLen                CLVariableAssociatedOADNum    /*节假日编程可变关联列表OAD个数*/
#define CLProgAcC_OADTabLen                CLVariableAssociatedOADNum    /*有功组合方式编程可变关联列表OAD个数*/
#define CLProgReC_OADTabLen                CLVariableAssociatedOADNum    /*无功组合方式编程可变关联列表OAD个数*/
#define CLProgSettD_OADTabLen              CLVariableAssociatedOADNum    /*结算日编程可变关联列表OAD个数*/
#define CLProgTPara_OADTabLen              CLVariableAssociatedOADNum    /*费率参数编程可变关联列表OAD个数*/
#define CLProgLad_OADTabLen                CLVariableAssociatedOADNum    /*阶梯表编程可变关联列表OAD个数*/
#define CLProgKD_OADTabLen                 CLVariableAssociatedOADNum    /*密钥更新编程可变关联列表OAD个数*/
#define CLMeterFa_OADTabLen                CLVariableAssociatedOADNum    /*计量芯片故障编程可变关联列表OAD个数*/
#define CLClockFa_OADTabLen                CLVariableAssociatedOADNum    /*时钟故障编程可变关联列表OAD个数*/
#define CLNeutralCurrentAbnormal_OADTabLen CLVariableAssociatedOADNum    /*零线电流异常可变关联列表OAD个数*/

#if 0	/*后续删除*/
#define CLBroadTimeAbnormal_OADTabLen      CLVariableAssociatedOADNum    /*广播校时异常可变关联列表OAD个数*/
#endif

#endif

/*****************************参变量**************************************/
/*698相关定义*/
#define CLDate_Time                        7     /*date_time_s*/
#define CLBackTime_OneSec                  7     /*备份时间，每s写铁电,date_time_s*/

#define CLBroadcastTimeOffset_Min          2     /*广播校时偏差最小值*/
#define CLBroadcastTimeOffset_Max          2     /*广播校时偏差最大值*/
#define CLBroadcastTimeParameter           4     /*广播校时参数数据块*/

#define CLComm_Address                     6     /*通讯地址*/

#define CLMeter_Num                        8     /*表号*/

#if 1	/*后续删除*/
#define CLMeter_Num_698                    8     /*698表号8个字节*/
#endif

#define CLCustomer_Num                     6     /*客户编号*/

#define CLMeter_Position_Longitude         4     /*电能表位置信息:经度*/
#define CLMeter_Position_Latitude          4     /*电能表位置信息:纬度*/
#define CLMeter_Position_High              4     /*电能表位置信息:高度*/
#define CLMeter_Position                   12    /*电能表位置信息:经度、纬度、高度*/

/*LCD参数*/
#define CLPowerOn_Dis_All_Time             1     /*上电全显时间*/
#define CLBacklightTime                    2     /*背光点亮时间*/
#define CLSViewBacklightTime               2     /*显示查看背光点亮时间*/
#define CLNEScreenDisplay                  2     /*无电按键屏幕驻留最大时间*/
#define CLEnergy_Decimal_Num               1     /*电能小数位数*/
#define CLPower_Decimal_Num                1     /*显示功率（最大需量）小数位数*/
#define CL1And2Display                     1     /*液晶①②字样意义*/
#define CLLCDParameter                     10    /*LCD参数数据块*/

#define CLEScreenDisplay                   2     /*有电按键屏幕驻留最大时间*/

#define CLChange_TZ_Time                   7     /*两套时区表切换时间*/
#define CLChange_PT_Time                   7     /*两套日时段表切换时间*/
#define CLChange_Rate                      7     /*两套费率电价切换时间*/
#define CLChange_Ladder                    7     /*两套阶梯电价切换时间*/

/*时区时段数*/
#define CLYear_Zone_Num                    1     /*年时区数*/
#define CLDay_Table_Num                    1     /*日时段表数*/
#define CLDay_Time_Num                     1     /*日时段数*/
#define CLRate_Num                         1     /*费率数*/
#define CLHoliday_Num                      1     /*公共假日数*/
#define CLZone_PT_Parameter                5     /*时区时段参数数据块*/

#define CLStep_Num                         1     /*阶梯数*/
#define CLKey_Tol_Num                      1     /*密钥总条数*/
#define CLLine_Num                         1     /*计量单元数*/

#define	CLHolidy_PT_Table1                 6         /*第1公共假日日期及日时段表号*/
#define	CLHolidy_PT_TableFF                (6*20)    /*第1-20公共假日日期及日时段表号*/

#if 0
#define	CLHolidy_PT_Table_Fa01_698         208   /*第1-52公共假日日期及日时段表号*/
#define	CLHolidy_PT_Table_Fa02_698         208   /*第53-104公共假日日期及日时段表号*/
#define	CLHolidy_PT_Table_Fa03_698         208   /*第105-156公共假日日期及日时段表号*/
#define	CLHolidy_PT_Table_Fa04_698         208   /*第157-208公共假日日期及日时段表号*/
#define	CLHolidy_PT_Table_Fa05_698         184   /*第209-254公共假日日期及日时段表号*/
#endif

#define	CLWeek_RestDay                     1     /*周休日特征字*/
#define	CLWeek_RestDay_DTable              1     /*周休日采取的日时段表号*/

#define	CLFirst_TZone_Data                 42    /*第一套时区表数据*/
#define	CLSec_TZone_Data                   42    /*第二套时区表数据*/

#define	CLFirst_TZone_1PT_Data             42    /*第一套第1日时段表数据*/
#define	CLFirst_TZone_2PT_Data             42    /*第一套第2日时段表数据*/
#define	CLFirst_TZone_3PT_Data             42    /*第一套第3日时段表数据*/
#define	CLFirst_TZone_4PT_Data             42    /*第一套第4日时段表数据*/
#define	CLFirst_TZone_5PT_Data             42    /*第一套第5日时段表数据*/
#define	CLFirst_TZone_6PT_Data             42    /*第一套第6日时段表数据*/
#define	CLFirst_TZone_7PT_Data             42    /*第一套第7日时段表数据*/
#define	CLFirst_TZone_8PT_Data             42    /*第一套第8日时段表数据*/

#define	CLSec_TZone_1PT_Data               42    /*第二套第1日时段表数据*/
#define	CLSec_TZone_2PT_Data               42    /*第二套第2日时段表数据*/
#define	CLSec_TZone_3PT_Data               42    /*第二套第3日时段表数据*/
#define	CLSec_TZone_4PT_Data               42    /*第二套第4日时段表数据*/
#define	CLSec_TZone_5PT_Data               42    /*第二套第5日时段表数据*/
#define	CLSec_TZone_6PT_Data               42    /*第二套第6日时段表数据*/
#define	CLSec_TZone_7PT_Data               42    /*第二套第7日时段表数据*/
#define	CLSec_TZone_8PT_Data               42    /*第二套第8日时段表数据*/

#define	CLCurrent_Rate1_Price              4     /*当前费率1电价*/
#define	CLCurrent_Rate2_Price              4     /*当前费率2电价*/
#define	CLCurrent_Rate3_Price              4     /*当前费率3电价*/
#define	CLCurrent_Rate4_Price              4     /*当前费率4电价*/
#define	CLCurrent_Rate5_Price              4     /*当前费率5电价*/
#define	CLCurrent_Rate6_Price              4     /*当前费率6电价*/
#define	CLCurrent_Rate7_Price              4     /*当前费率7电价*/
#define	CLCurrent_Rate8_Price              4     /*当前费率8电价*/
#define	CLCurrent_Rate9_Price              4     /*当前费率9电价*/
#define	CLCurrent_Rate10_Price             4     /*当前费率10电价*/
#define	CLCurrent_Rate11_Price             4     /*当前费率11电价*/
#define	CLCurrent_Rate12_Price             4     /*当前费率12电价*/
#define	CLCurrent_RateFF_Price             48    /*当前套费率电价数据块*/

#define	CLBackUp_Rate1_Price               4     /*备用套费率1电价*/
#define	CLBackUp_Rate2_Price               4     /*备用套费率2电价*/
#define	CLBackUp_Rate3_Price               4     /*备用套费率3电价*/
#define	CLBackUp_Rate4_Price               4     /*备用套费率4电价*/
#define	CLBackUp_Rate5_Price               4     /*备用套费率5电价*/
#define	CLBackUp_Rate6_Price               4     /*备用套费率6电价*/
#define	CLBackUp_Rate7_Price               4     /*备用套费率7电价*/
#define	CLBackUp_Rate8_Price               4     /*备用套费率8电价*/
#define	CLBackUp_Rate9_Price               4     /*备用套费率9电价*/
#define	CLBackUp_Rate10_Price              4     /*备用套费率10电价*/
#define	CLBackUp_Rate11_Price              4     /*备用套费率11电价*/
#define	CLBackUp_Rate12_Price              4     /*备用套费率12电价*/
#define	CLBackUp_RateFF_Price              48    /*备用套费率电价数据块*/

#define	CLCurrent_Ladder_Table             64    /*当前套阶梯表*/
#define	CLCurrent_Ladder_Table_LadNum      24    /*当前套阶梯表,阶梯值*/
#define	CLCurrent_Ladder_Table_LadPri      28    /*当前套阶梯表,阶梯电价*/
#define	CLCurrent_Ladder_Table_LadSett     12    /*当前套阶梯表,阶梯结算日*/

#define	CLBackUp_Ladder_Table              64     /*备用套阶梯表*/
#define	CLBackUp_Ladder_Table_LadNum       24     /*备用套阶梯表,阶梯值*/
#define	CLBackUp_Ladder_Table_LadPri       28     /*备用套阶梯表,阶梯电价*/
#define	CLBackUp_Ladder_Table_LadSett      12     /*备用套阶梯表,阶梯结算日*/

#define	CLRatio_Curr_Tran                  4      /*电流互感器变比*/
#define	CLRatio_Vol_Tran                   4      /*电压互感器变比*/

#define	CLAlam1_Money                      4      /*报警金额1限值*/
#define	CLAlam2_Money                      4      /*报警金额2限值*/
#define	CLAlamFF_Money                     8      /*报警金额数据块*/

#define	CLOverDraft_Money                  4      /*透支金额限值*/
#define	CLHoarding_Money                   4      /*囤积金额限值*/
#define	CLClose_Relay_Money                4      /*合闸允许金额限值*/
#define	CLOther_Money                      12     /*其他金额数据块*/

#define	CLInset_Card_State                 2      /*插卡状态字*/

#define	CLVoltage_UpLim                    2      /*电压上限值*/
#define	CLVoltage_LowLim                   2      /*电压下限值*/
#define	CLVolage_Check_UpLim               2      /*电压考核上限*/
#define	CLVolage_Check_LowLim              2      /*电压考核下限*/
#define	CLVolage_QualifRateParameter       8      /*电压合格率参数数据块*/

#define CLDemand_Cycle                     1      /*最大需量周期*/
#define CLSliding_Time                     1      /*滑差时间*/
#define CLPluse_Wide                       1      /*脉冲宽度*/
#define CLManage_Code                      32     /*资产管理编码*/
#define CLRated_Vol                        6      /*额定电压*/
#define CLRated_Curr                       6      /*额定电流/基本电流*/
#define CLMax_Curr                         6      /*最大电流*/
#define CLMin_Curr                         32     /*最小电流*/
#define CLTurn_Curr                        32     /*转折电流*/
#define CLAddByte                          1      /*最小电流与转折电流空间存储预留33字节*/
#define CLActive_Accur_Deg                 4      /*有功准确度等级*/
#define CLReactive_Accur_Deg               4      /*无功准确度等级*/
#define CLMeter_Ac_Const                   4      /*电表有功常数*/
#define CLMeter_Re_Const                   4      /*电表无功常数*/
#define CLMeter_Model                      32     /*电表型号*/
#define CLSoftw_Record_Number              16     /*软件备案号*/

#define CLActive_Com_State                 1      /*有功组合状态字*/
#define CLReactive_Com_State1              1      /*无功组合状态字1*/
#define CLReactive_Com_State2              1      /*无功组合状态字2*/

#define CLSettle_Day1                      2      /*每月第1结算日*/
#define CLSettle_Day2                      2      /*每月第2结算日*/
#define CLSettle_Day3                      2      /*每月第3结算日*/
#define CLSettle_DayFF                     6      /*结算日数据块*/

/*电气设备*/
#define	CLEquipmentDis                     32     /*设备描述符*/

#define	CLFactory_Number                   4      /*厂家编号*/
#define	CLFactory_Softw_Version            4      /*厂家软件版本号*/
#define	CLFactory_Softw_VersionDate        6      /*厂家软件版本日期*/
#define	CLFactory_Hardw_Version            4      /*厂家硬件版本号*/
#define	CLFactory_Hardw_VersionDate        6      /*厂家硬件版本日期*/
#define	CLFactory_ExternSign               8      /*厂家扩展信息*/
#define	CLFactoryInfomation                32    /*厂家信息*/

#define	CLProd_Date                        7      /*生产日期*/

#define	CLMeter_CommPro1                   32     /*支持规约列表1*/
#define	CLMeter_CommPro2                   32     /*支持规约列表2*/

#define	CLAllowFollowUpTell                1      /*是否允许跟随上报*/
#define	CLAllowAccordUpTell                1      /*是否允许主动上报*/
#define	CLAllowMasterCall                  1      /*允许与主站通话*/
#define	CLUpTellChannel                    13     /*上报通道*/

/*应用连接*/
#define CLAppProInformation                2      /*协议版本信息*/
#define CLAppMaxReAPDU                     2      /*最大接收APDU尺寸*/
#define CLAppMaxSeAPDU                     2      /*最大发送APDU尺寸*/
#define CLAppMaxHandleAPDU                 2      /*最大可处理APDU尺寸*/
#define CLAppProConsistency                8      /*协议一致性块*/
#define CLAppFunConsistency                16     /*功能一致性块*/
#define CLAppStaticTimeout                 4      /*静态超时时间*/
#define CLAppParameter                     36     /*应用语境信息数据块*/

#define CLClientAddr                       1      /*当前连接的客户机地址*/
#define CLConAutheMechanism                1      /*连接认证机制*/

/*应用连接认证密码*/
#define CL698Key                           8      /*698,认证密码*/

/*信号强度*/
#define CLGPS_Signal                       2      /*无线通讯在线级信号强弱指示*/

/*显示*/
#define CLAuto_Dis_1ScreenCode             9      /*自动循显显示第1屏显示代码*/
#define CLAuto_Dis_99ScreenCode            9      /*自动循显显示第99屏显示代码*/

#define CLPer_Dis_Screen_Time              2      /*自动每屏显示时间*/

#define CLAuto_Dis_Screen_Num              1      /*自动循显屏数*/
#define CLAuto_Dis_Screen_MaxNum           1      /*自动循显最大屏数*/
#define CLAuto_Dis_Parameter               2      /*自动循显参数数据块*/

#define CLKey_Dis_1ScreenCode              9      /*按键显示第1屏显示代码*/
#define CLKey_Dis_99ScreenCode             9      /*按键显示第99屏显示代码*/

#define CLPerkey_Dis_Screen_Time           2      /*按键每屏显示时间*/

#define CLKey_CycDis_Screen_Num            1      /*按键循显屏数*/
#define CLKey_CycDis_Screen_MaxNum         1      /*按键循显最大屏数*/
#define CLKey_CycDis_Parameter             2      /*按键循显参数数据块*/

/*ESAM*/
#define CLKey_State_698                    16     /*对称密钥版本*/
#define	CLID_Auth_Remain_Time              4      /*身份认证时效剩余时间*/
#define	CLInfra_Auth_Remain_Time           4      /*红外认证时效剩余时间*/
#define	CL_IRAuth_Timer                    4      /*红外认证时效*/

#if 1	/*后续可删除*/
#define	CL_IRAuth_Timer1                   1      /*红外认证时效,避免E2地址调整原长度保存*/
#endif

#define	CLF1_TerUpCommParam                6      /*F1终端上行通信参数*/
#define	CLF3_MainStaCommParam              28     /*F3主站通信参数*/
#define	CLF4_SMSCommParam                  16     /*F4短信通信参数*/
#define	CLF7_TerminalIPAddr                64     /*F7终端IP地址*/
#define	CLF8_ConnectParam                  8      /*F8 连接参数*/
#define	CLF16_MoveAPNPassWord              64     /*F16 移动APN密码*/
#define	CLF89_TerminalAddr                 8      /*F89 终端地址*/

/*安全模式参数*/
#define CLSafeModePara                     1      /*安全模式参数*/

#if 1	/*后续删除*/
#define CLSafeModeParaNat3                 1020   /*安全模式参数,属性3*/
#define CLSafeModeParaNat3_Num             1      /*安全模式参数,属性3,元素个数*/
#endif

#if 0	/*后续修改*/
#define CLSafeModeParaNat3                 (1+50*4)    /*安全模式参数,属性3*/
#endif

/*输入输出设备*/
#define CLMod_InFr_Baud                    5     /*调制型红外光口波特率特征字*/
#define CLTouch_InFr_Baud                  5     /*接触式红外光口波特率特征字*/
#define CLOne485_Baud                      5     /*1路485波特率特征字*/
#define CLTwo485_Baud                      5     /*2路485波特率特征字*/
#define CLModular_Baud                     5     /*模块通道波特率特征字*/
#define CLModular_BaudConsult              5     /*模块通道协商波特率特征字*/

/*2015*/
#define	CLDrive_Report_Mode                4     /*主动上报模式字*/
#define	CLDrive_Report_State               4     /*主动上报状态字，4通道*/
#define	CLRst_ReportState_Timer            1     /*主动上报自动复位延时时间*/
#define	CLRst_Report_State                 4     /*复位主动上报状态字*/

#if 1	/*后续删除*/
/*逻辑设备列表*/
#define	CLFactory_Address_4031             1     /*模组逻辑地址*/
#define	CLFactory_Softw_Version_4031       16    /*厂家软件版本号*/
#define	CLFactory_Hardw_Version_4031       16    /*硬件版本*/
#define	CLFactory_Number_4031              4     /*厂家编号*/
#define	CLFactory_Softw_VersionDate_4031   6     /*厂家软件版本日期*/
#define	CLFactory_Hardw_VersionDate_4031   6     /*厂家硬件版本日期*/
#define	CLFactory_ExternSign_4031          16    /*厂家扩展信息*/
#define	CLFactoryInf_4031                  65    /*模组版本信息*/
#endif

/****************************************645数据长度定义**********************************/
/*645相关定义*/
#define CLDate_Week                        4     /*日期及星期（0表示星期天）*/
#define CLTime                             3     /*时间*/
#define CLMonthAndDay                      2     /*日期及月份*/
#define CLDate_Week_Time                   7     /*645格式数据长度*/

#define CL04Pos_Ac_Tol_En_0_645            5     /*当前正向有功总精确电能645数据长度*/

#define CLPos_Ac_Tol_En_1                  4     /*上1次(上12次)正向有功总电能645数据长度*/
#define CLPos_Ac_En_FF_1                   20    /*上1次(上12次)正向有功电能数据块645数据长度*/

#define CLPrePos_Ac_Tol_En_1               5     /*上1次(上12次)正向有功总精确电能645数据长度*/
#define CLPrePos_Ac_En_FF_1                25    /*上1次(上12次)正向有功精确电能数据块645数据长度*/

#define CLPos_Ac_De_FF_0_4Rate             55    /*当前正向有功最大需量及发生时刻数据块4费率*/

#define CLSettle_Time_1                    4     /*上1次(上12次)结算日结算时间*/
#define CLSettle_Time_FF                   48    /*上1次(上12次)结算日结算时间数据块*/

#define CLFreeTime_645                     5     /*645冻结时间YYMMDDHHMM*/
#define CLOne485_Baud_645                  1     /*645通信口波特率*/
#define CLID_Auth_Remain_Time_645          2     /*645身份认证时效剩余时间*/
#define CLInfra_Auth_Remain_Time_645       1     /*645红外认证时效剩余时间*/

#define CLLCD_View                         5     /*液晶查看*/

#define CLMeter_Ac_Const645                3     /*645电表有功常数*/
#define CLMeter_Re_Const645                3     /*645电表有无功常数*/
#define CLMeter_Model645                   10    /*645电表型号*/
#define CLProd_Date645                     10    /*645生产日期*/
#define CLProd_Date_YMDHM                  5     /*698生产日期,年月日时分长度*/

#define CLMeter_Num_645                    6     /*645表号6个字节*/
#define CLProt_Version_Num                 16    /*协议版本号*/
#define CLKey_State                        8      /*对称密钥版本*/

#define CLLoad_Rec_Mode                    1     /*负荷记录模式字*/
#define CLTiming_Freeze                    1     /*定时冻结数据模式字*/
#define CLInstant_Freeze                   1     /*瞬时冻结数据模式字*/
#define CLAppoint_Freeze                   1     /*约定冻结数据模式字*/
#define CLHour_Freeze                      1     /*整点冻结数据模式字*/
#define CLDay_Freeze                       1     /*日冻结数据模式字*/

#define CLLoad_Rec_Time                    4     /*负荷记录起始时间,MMDDhhmm*/
#define CLLoad_Rec_Time_Year               5     /*负荷记录起始时间,YYMMDDhhmm*/
#define CLLoad_Rec1_Inte_Time              2     /*第1类负荷记录间隔时间*/
#define CLLoad_Rec2_Inte_Time              2     /*第2类负荷记录间隔时间*/
#define CLLoad_Rec3_Inte_Time              2     /*第3类负荷记录间隔时间*/
#define CLLoad_Rec4_Inte_Time              2     /*第4类负荷记录间隔时间*/
#define CLLoad_Rec5_Inte_Time              2     /*第5类负荷记录间隔时间*/
#define CLLoad_Rec6_Inte_Time              2     /*第6类负荷记录间隔时间*/

#define	CLKey_0_Class                      3     /*0级密码*/
#define	CLKey_1_Class                      3     /*1级密码*/
#define	CLKey_2_Class                      3     /*2级密码*/
#define	CLKey_3_Class                      3     /*3级密码*/
#define	CLKey_4_Class                      3     /*4级密码*/
#define	CLKey_5_Class                      3     /*5级密码*/
#define	CLKey_6_Class                      3     /*6级密码*/
#define	CLKey_7_Class                      3     /*7级密码*/
#define	CLKey_8_Class                      3     /*8级密码*/
#define	CLKey_9_Class                      3     /*9级密码*/

#define	CLPos_Ac_Power_UpLim               3     /*正向有功功率上限值*/
#define	CLRev_Ac_Power_UpLim               3     /*反向有功功率上限值*/

#define	CLDrive_Report_Mode_645            8     /*主动上报模式字*/
#define	CLDrive_Report_State_645           8     /*主动上报状态字，4通道*/
#define	CLRst_Report_State_645             12    /*复位主动上报状态字*/

#define	CLHour_Freeze_StTime               5     /*整点冻结起始时间*/
#define	CLHour_Freeze_InteTime             1     /*整点冻结时间间隔*/
#define	CLDay_Freeze_Time                  2     /*日冻结时间*/
#define	CLTiming_Freeze_Time               4     /*定时冻结时间*/

#if 1	/*后续删除*/
#define	CLRelay_Delay_Time                 1     /*跳闸延时时间*/
#endif
#define	CLRelay_Open_CurrTreshold          4     /*继电器拉闸控制电流门限值*/
#define	CLRelay_Open_CurrTimer             2     /*拉闸控制电流门限保护延时时间*/

#define	CLRelay_Delay_Time_645             2     /*698兼容645,645跳闸延时时间*/
#define	CLOverCurr_Curr_LowLim645          2     /*645过流事件电流触发下限*/

#define	CLHardError_State                  1     /*硬件故障运行状态字*/

#define	CLAlarm_Status                     12    /*报警模式字*/
#define	CLRelay_RemoteOrder                3     /*远程控制命令*/
#define	CLRelay_State                      3     /*继电器状态*/
#define	CLRelay_LocalOrder                 2     /*本地控制命令*/

#define	CLSoftw_Record_Number_645          8     /*645软件备案号*/

#define	CLHolidy_PT_Table_Fa00             230   /*第1-46公共假日日期及日时段表号*/
#define	CLHolidy_PT_Table_Fa01             230   /*第47-92公共假日日期及日时段表号*/
#define	CLHolidy_PT_Table_Fa02             230   /*第93-138公共假日日期及日时段表号*/
#define	CLHolidy_PT_Table_Fa03             230   /*第139-184公共假日日期及日时段表号*/
#define	CLHolidy_PT_Table_Fa04             230   /*第185-230公共假日日期及日时段表号*/
#define	CLHolidy_PT_Table_Fa05             120   /*第231-254公共假日日期及日时段表号*/

#define	CLFirst_TZone_1To4PT_Data          168   /*第一套第1-4日时段表数据*/
#define	CLFirst_TZone_5To8PT_Data          168   /*第一套第5-8日时段表数据*/

#define	CLSec_TZone_1To4PT_Data            168   /*第二套第1-4日时段表数据*/
#define	CLSec_TZone_5To8PT_Data            168   /*第二套第5-8日时段表数据*/

#define	CLLoadWriteNum                     3     /*负荷记录次数*/
#define	CLOne485_Baud_645                  1     /*645协议1路485波特率特征字长度*/

/***************************************自扩参数数据长度***************************************/
#define	CLVolage_Type                    1              /*电压类型*/
#define	CLCurrent_Type                   1              /*电流类型*/
#define	CLLine_Type                      1              /*相线类型*/
#define	CLAuxi_Power_Sign                1              /*辅助电源标志*/
#define	CLRelay_Type                     1              /*负荷开关类型*/
#define	CLComm_Way                       1              /*通信方式*/
#define	CLProgram_Valid                  1              /*编程有效标志*/
#define	CLZero_Current_Sign              1              /*零线电流标志*/

#define	CLStart_Up_Current               3              /*电流瞬时量阀值*/
#define	CLStart_Up_Power                 4              /*启动功率功率瞬时量阀值*/

#define	CLVolage_Abnor_Vol               4              /*电压异常判断电压*/
#define CLVolage_Abnor_Vol_Single        2              /*电压异常判断电压阀值单个长度*/
#define	CLLoss_Volage_Curr               2              /*全失压电流*/
#define	CLLoss_Volage_Vol                2              /*全失压电压*/
#define	CLRev_Phase_Vol                  2              /*逆相序判断电压*/
#define	CLRelayOpen_Vol__LowLim          2              /*跳闸下门限*/
#define	CLRelayOpen_Vol__UpLim           2              /*跳闸上门限*/

#define	CLPluse_Most__Lim                2              /*从计量芯片读出的脉冲最大阀值*/
#define	CLCurr_Ratio_30A                 2              /*校表30A对应的相应电流规格系数*/
#define	CLPulse_Constant                 4              /*脉冲常数*/
#define	CLSoftIJ_Valid_Time              4              /*软IJ有效时间*/
#define	CLExtern_Relay_PulW              2              /*外置继电器脉冲宽度*/

#define	CL_OddHar_AddData1               3              /*奇次谐波补偿值1,(电流：2.8A~4A 条件)*/
#define	CL_OddHar_AddData2               3              /*奇次谐波补偿值2,(电流：1.4A~2A 条件)*/
#define	CL_OddHar_AddData_A              0              /*奇次谐波补偿值，A相数据偏移*/
#define	CL_OddHar_AddData_B              1              /*奇次谐波补偿值，B相数据偏移*/
#define	CL_OddHar_AddData_C              2              /*奇次谐波补偿值，C相数据偏移*/

#define	CL_EvenHar_AddData_A0            3              /*偶次谐波补偿值A0,(0.5L条件，A相补偿值)*/
#define	CL_EvenHar_AddData_A1            3              /*偶次谐波补偿值A1,(0.5L条件，A相补偿值)*/
#define	CL_EvenHar_AddData_B0            3              /*偶次谐波补偿值B0,(0.5L条件，B相补偿值)*/
#define	CL_EvenHar_AddData_B1            3              /*偶次谐波补偿值B1,(0.5L条件，B相补偿值)*/
#define	CL_EvenHar_AddData_C0            3              /*偶次谐波补偿值C0,(0.5L条件，C相补偿值)*/
#define	CL_EvenHar_AddData_C1            3              /*偶次谐波补偿值C1,(0.5L条件，C相补偿值)*/
#define	CL_EvenHar_Time                  2              /*偶次谐波补偿计时，默认24h*60min*/

#define	CLMCU_Version_Num                2              /*MCU版本号*/
#define	CLFactoryInMeterNum              2              /*电表内部序号*/
#define	CLCurr_Rate_No                   1              /*当前费率号*/
#define	CLCurr_Step_No                   1              /*当前阶梯号*/
#define	CLEnter_LowPower_Time            7              /*进入低功耗时间*/
#define	CLExit_LowPower_Time             7              /*退出低功耗时间*/
#define CLSoftI_J_RemainTime             4              /*软IJ有效剩余时间*/
#define	CLRemote_Local_State             2              /*远程、本地开户状态*/
#define	CLCloc_Batt_LowState             1              /*时钟电池欠压状态*/
#define	CLReadMeter_Batt_LowState        1              /*唤醒电池欠压状态*/
#define	CLESAM_FaultState                1              /*ESAM故障状态*/
#define	CLClock_FaultState               1              /*时钟故障状态*/
#define	CLClock_FaultTime                7              /*广播校时异常引起的时钟故障时间*/
#define	CLDoubleAgreementFlag            1              /*是否双协议的标志，主要是用于协议版本号一个还是两个*/
#define	CLReportNewAddNum                96             /*上报次数*/
#define	CLHaveReportState                14             /*已上报标志*/
#define	CLCap_Vol                        2              /*超级电容电压(原645停抄电池标识码)*/
#define	CLMeterRunStatic                 2              /*当前运行在第几套时区表、时段表。时区表在前（低地址）*/
#define	CLFlashAddress                   4              /*Flash地址长度*/
#define	CLKey_Update_ID                  4              /*密钥更新第1个标识码是操作者代码*/

#if 1	/*后续删除*/
#define	CLTemp_Key_State0                1              /*临时密钥状态0(31)*/
#define	CLTemp_Key_State1                1              /*临时密钥状态1*/
#define	CLTemp_Key_StateFF               32             /*临时密钥状态数据块(0-31)*/
#define	CLTemp_Key_Save0                 32             /*临时密钥存储0(31)*/
#define	CLTemp_Key_Save1                 32             /*临时密钥存储1*/
#endif

#define CLD_Free_StartTime               5              /*日冻结起始日期时间，分钟冻结采用负荷记录起始时间04000A0F*/
#define CLM_Free_StartTime               5              /*月冻结起始日期时间，小时冻结采用整点冻结起始时间04001201*/
#define CLY_Free_StartTime               5              /*年冻结起始日期时间*/
#define CLDisplayBorrowPoint             1              /*显示借位位数*/
#define CLDisplayBorrowPoint_RecFlag     1              /*显示借位位数矫正标志*/
#define	CLReturn_Money                   4              /*退费金额*/

#define	CLRec_MeterSequence              5              /*校表序列号*/
#define	CLRec_MeterPassWord              4              /*校表密码*/
#define	CL_UserCardNo                    8              /*用户卡卡片序列号*/
#define	CLMeter_Work_Char1               1              /*电表运行特征字1*/
#if 1	/*后续删除*/
#define	CLMeter_Work_Char1_645           1              /*电表运行特征字1*/
#endif
#define	CLRTC_Inital                     0              /*RTC初始化命令，矩泉*/
#define	CLRTC_Adjust                     4              /*RTC校准命令*/
#define	CLRTC_AdjustTemp                 8              /*RTC校准温度值*/


/****不适合放置在此文件中***/
#define CLProgOADGather                  50             /*编程对象OAD，array格式，目前支持最大10个*/
#define CProgOADNum                      10             /*编程对象OAD，array格式，目前支持最大10个*/
#define CLProgTypeOADGather              5              /*编程对象类型和OAD总长度5字节*/
#define CLProgOAD                        4              /*编程对象OAD，类似编程时段表对象 OAD，数据层支持列读*/
#define CLSettleDatebeforePro            6              /*结算日编程记录中结算日长度*/
#define CLReturn_M_Sum3                  4              /*退费金额*/

#define CLProgTZ_645Comm_Note_OnlyData        84        /*645协议时区表编程记录除去时间、操作者代码的数据，94-6-4=84*/
#define CLProgTZ_CurrentPart_Note_OnlyData    42        /*时区表编程记录除去时间的长度*/


/*复旦微RTC时钟调校*/
/*如果要使用复旦微提供的日计时误差调整工具，则存储数据的位置不可修改
(或者特殊处理读1e命令，将数据正确应答给上位机，才可调整数据存储位置)*/
/*EE数据存储定义*/
#define	ee_remainmoney_page             0x00            /*剩余金额数据页地址*/
#define	ee_remainmoney_inpage           0
#define	ee_remainmoney_lenth            16
#define	ee_esampara_page                0x00            /*esam里报警金额到身份认证时效参数页地址*/
#define	ee_esampara_inpage              (ee_remainmoney_inpage+ee_remainmoney_lenth+4)
#define	ee_esampara_lenth               29
/*温度补偿系数页*/
#define	ee_temperature_page             0x00            /*温度补偿系数*/
#define	ee_temperature_inpage           (ee_esampara_inpage+ee_esampara_lenth+2)
#define	ee_temperature_lenth            11
/*常温RTC查表区*/
#define	ee_commaddr_lenth               6
#define	ee_ptatvalue_page               0x2a            /*查表温度ADC页地址*/
#define	ee_ptatvalue_inpage             0
#define	ee_ptatvalue_lenth              42
#define	ee_trimvalue_page               0x2b            /*查表补偿值页地址*/
#define	ee_trimvalue_inpage             0
#define	ee_trimvalue_lenth              42
/*高低温RTC查表区 前32字节低温+crc，后32字节高温+crc*/
#define	ee_ptatvalue_lt_page            0x1fe           /*查表温度ADC页地址*/
#define	ee_ptatvalue_lt_inpage          0
#define	ee_ptatvalue_lt_lenth           30
#define	ee_ptatvalue_ht_page            0x1fe           /*查表温度ADC页地址*/
#define	ee_ptatvalue_ht_inpage          32
#define	ee_ptatvalue_ht_lenth           30

#define	ee_trimvalue_lt_page            0x1ff           /*查表补偿值页地址*/
#define	ee_trimvalue_lt_inpage          0
#define	ee_trimvalue_lt_lenth           30
#define	ee_trimvalue_ht_page            0x1ff           /*查表补偿值页地址*/
#define	ee_trimvalue_ht_inpage          32
#define	ee_trimvalue_ht_lenth           30

#define	ee_trl_page                     0x244           /*低温温度记录*/
#define	ee_trl_inpage                   0
#define	ee_trl_lenth                    64
#define	ee_trh_page                     0x245           /*高温温度记录*/
#define	ee_trh_inpage                   0
#define	ee_trh_lenth                    64
#define	ee_pre_dayfreeze_page           0x18            /*专门用于上电补存的上一次日冻结时间页地址*/
#define	ee_predayfreeze_inpage          44
#define	ee_predayfreeze_lenth           5
#define	ee_rtcadj_time_page             0x18            /*写常温顶点调校值时时间记录页地址(始终不清)*/
#define	ee_rtcadjtime_inpage            (ee_predayfreeze_inpage+ee_predayfreeze_lenth+2)
#define	ee_rtcadjtime_lenth             10

#endif
