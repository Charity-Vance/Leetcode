
///*******************************************************************************************************///
///* Copyright：  (c)Copyright 2016,浙江正泰仪器仪表有限责任公司,智能电表研发一部                        *///
///*                            All rights reserved.                                                     *///
///* FileName:   LibPublic.h                                                                             *///
///* Brief:       通用函数管理模块		                                                                 */// 
///* Author:      作者                                                                                   *///
///* Version:     版本                                                                                   *///
///* Date:        日期                                                                                   *///
///*                                                                                                     *///
///* note:修改历史记录列表，每条修改记录应包括修改日期、修改者及修                                       *///
///* 1.  Author:                                                                                         *///
///*     Version:                                                                                        *///
///*     Date :                                                                                          *///
///* 2.  Author:                                                                                         *///
///*     Version:                                                                                        *///
///*     Date:                                                                                           *///
///*******************************************************************************************************///

#ifndef   _LIBPUBLIC_H
#define   _LIBPUBLIC_H

///*------------------------------- H文件使用说明 -------------------------------------------------------*///
///*                                                                                                     *///
///* 该文件宏定义的前缀为: LIBPUB_                                                                       *///
///*                                                                                                     *///
///*                                                                                                     *///

///* 注释格式均采用三斜杠加星号的方式，注释与注释符之间用空格隔开 *///
///* 代码控制均采用tab制表符（设置成占4个空格）或者直接敲4个空格  *///
///*-------------------------------- 宏定义区 -----------------------------------------------------------*///





///*-------------------------------- 函数声明区 ---------------------------------------------------------*///
///* 主要是申明对应.c文件里的函数 *///
extern ushort16 LibPub_CRC16_CCITT(uchar8 *cp, ushort16 len);
extern void LibPub_MemCopyBytes(uchar8 *pSourceData, uchar8 *pTargetData, uchar8 len);
extern void LibPub_MemExchangeBytes(uchar8 *pSourceData, uchar8 *pTargetData, uchar8 len);
extern uchar8 LibPub_ZeroCheck( uchar8 *cp, uchar8 len);
extern uchar8 LibPub_0xFFCheckInt( uchar8 *cp, uchar8 len);
extern uchar8 LibPub_CrcCheck( uchar8 *cp, uchar8 len, ushort16 cmpcrc);
extern ulong32 LibPub_GetTimerBeat(void);
extern ulong32 LibPub_GetTimerBeatInt0(void);
extern ulong32 LibPub_GetTimerBeatInt1(void);
extern uchar8 LibPub_GetDiffTime( ulong32 timer, ulong32 basetimer, ulong32 duration );
extern void LibPub_MemSetBytes( uchar8 *p_ucdatahead, uchar8 v_ucVal, ushort16 v_usLen );
extern uchar8 LibPub_CalSum(uchar8 *pData, uchar8 v_ucLen);
extern uchar8 LibPub_IsBCD(uchar8 *p_ucData, uchar8 v_ucLen );
extern uchar8 LibPub_1Hex_2_1BCD( uchar8 hexdata);
extern uchar8 LibPub_1BCD_2_1HEX( uchar8 v_ucBcdData );
extern void LibPub_NBtyesBcdAdd(uchar8 *p_ucBcdA, uchar8 *p_ucBcdB, uchar8 v_ucLen);
extern void LibPub_NBytesBCDSub(uchar8 *p_ucBufA, uchar8 *p_ucBufB, uchar8 v_ucLen);

extern uchar8	LibPub_WriteDataToE2prom( ushort16 v_usAddrIndex, uchar8 v_ucOffset, uchar8 *ptr_ucData );
extern uchar8	LibPub_ReadDataFromE2prom(ushort16 v_usAddrIndex, uchar8 v_ucOffset, uchar8 *ptr_ucData);
extern uchar8	LibPub_CheckE2promPara(ushort16 address, ushort16 addressbak, ushort16 *ptr_data, ushort16 len, uchar8 isCRC);
extern void LibPub_Inverse( uchar8 *p_ucData, uchar8 DataLen );
extern uchar8	LibPub_CheckPassword( uchar8 *p_ucPsw);
extern uchar8	LibPub_CompareData(uchar8 *P_ucData1, uchar8 *P_ucData2, uchar8 v_ucDataLength, uchar8 v_ucCmpMode);
extern uchar8 LibPub_CompareNBufs(uchar8 *P_ucSourceData,uchar8 *P_ucResultData,uchar8 V_ucLen,uchar8 V_Num,uchar8 V_Mode,uchar8 v_ucCmpMode);

extern ushort16 LibPub_Buffer2ToUshort16( uchar8 *p_ucBytesBuffer );
extern ulong32  LibPub_Buffer4ToUlong32( uchar8 *p_ucBytesBuffer );
extern void LibPub_Ushort16ToBuffer2(uchar8 *p_ucBytesBuffer,ushort16 v_usShort16Buffer);
extern void LibPub_Ulong32ToBuffer4(uchar8 *p_ucBytesBuffer, ulong32 v_ulDoubleWordBuffer);
extern ulong32 LibPub_DECtoHEXBytes(uchar8 *P_ucSourceData,uchar8 V_ucDataLength);
extern void LibPub_HEXtoBCDBytes(ulong32 V_ulSourceData,uchar8 *P_ucResultData,uchar8 V_ucLen);
extern void LibPub_HEXtoAscii(uchar8 *p_ucSourceData, uchar8 *p_ucResultData, uchar8 v_ucLen );

extern void LibPub_Delay2us(void);
extern void LibPub_Delay5us(void);
extern void LibPub_Delay10us(void);
extern void LibPub_DelayNms(ushort16 v_uiNums);
extern void LibPub_Delay10xus(ushort16 v_uiNums);

#endif
