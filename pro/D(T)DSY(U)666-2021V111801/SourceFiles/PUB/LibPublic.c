 
///*******************************************************************************************************///
///* Copyright：  (c)Copyright 2016,浙江正泰仪器仪表有限责任公司,智能电表研发一部                        *///
///*                            All rights reserved.                                                     *///
///* FileName:    LibPublic.c                                                                            *///
///* Brief:       通用函数库文件                                                                         */// 
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
///*                                                                                                     *///
///*  addtogroup:Template                                                                                *///
///*******************************************************************************************************///

///*-------------------------------- 文件功能说明 -------------------------------------------------------*///
///*                                                                                                     *///
///*  该文件所有函数的前缀为LibPub_                                                                      *///
///*  文件主函数和对外函数需放在文件的首部，并且主函数需要放在第一个位置;                                *///
///*  函数注释采用标准模板，函数内部注释采用//;                                                          *///
///*  对于注释较多的部分，可以增加一个注释符，然后详细说明放在文件的尾部;                                *///
///*                                                                                                     *///
///*-----------------------------------------------------------------------------------------------------*///


///* 注释格式均采用三斜杠加星号的方式，注释与注释符之间用空格隔开 *///
///* 代码控制均采用tab制表符（设置成占4个空格）或者直接敲4个空格  *///
///*--------------------------------- 头文件包含区 ------------------------------------------------------*///
//#include "..\SourceFiles\PUB\TypeDefine.h"
//#include "..\SourceFiles\PUB\LibPublic.h"
#include "..\SourceFiles\PUB\Include.h"

///*--------------------------------- 变量声明区 --------------------------------------------------------*///

const ushort16 code fcstab[256] = {
0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf,
0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7,
0x1081, 0x0108, 0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e,
0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876,
0x2102, 0x308b, 0x0210, 0x1399, 0x6726, 0x76af, 0x4434, 0x55bd,
0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5,
0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e, 0x54b5, 0x453c,
0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd, 0xc974,
0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb,
0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3,
0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a,
0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72,
0x6306, 0x728f, 0x4014, 0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9,
0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a, 0xb8e3, 0x8a78, 0x9bf1,
0x7387, 0x620e, 0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x0738,
0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862, 0x9af9, 0x8b70,
0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7,
0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff,
0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036,
0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e,
0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5,
0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd,
0xb58b, 0xa402, 0x9699, 0x8710, 0xf3af, 0xe226, 0xd0bd, 0xc134,
0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c,
0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1, 0xa33a, 0xb2b3,
0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72, 0x3efb,
0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232,
0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a,
0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1,
0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9,
0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330,
0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3, 0x2c6a, 0x1ef1, 0x0f78
};

///*--------------------------------- 函数声明区 --------------------------------------------------------*///
ushort16 LibPub_CRC16_CCITT(uchar8 *cp, ushort16 len);
void LibPub_MemCopyBytes(uchar8 *pSourceData, uchar8 *pTargetData, uchar8 len);
void LibPub_MemExchangeBytes(uchar8 *pSourceData, uchar8 *pTargetData, uchar8 len);
uchar8 LibPub_ZeroCheck( uchar8 *cp, uchar8 len);
uchar8 LibPub_0xFFCheckInt( uchar8 *cp, uchar8 len);
uchar8 LibPub_CrcCheck( uchar8 *cp, uchar8 len, ushort16 cmpcrc);
ulong32 LibPub_GetTimerBeat(void);
ulong32 LibPub_GetTimerBeatInt0(void);
ulong32 LibPub_GetTimerBeatInt1(void);
uchar8 LibPub_GetDiffTime( ulong32 timer, ulong32 basetimer, ulong32 duration );
void LibPub_MemSetBytes( uchar8 *p_ucdatahead, uchar8 v_ucVal, ushort16 v_usLen );
uchar8 LibPub_CalSum(uchar8 *pData, uchar8 v_ucLen);
uchar8 LibPub_IsBCD(uchar8 *p_ucData, uchar8 v_ucLen );
uchar8 LibPub_1Hex_2_1BCD( uchar8 hexdata);
uchar8 LibPub_1BCD_2_1HEX( uchar8 v_ucBcdData);
void LibPub_NBtyesBcdAdd(uchar8 *p_ucBcdA, uchar8 *p_ucBcdB, uchar8 v_ucLen);
void LibPub_NBytesBCDSub(uchar8 *p_ucBufA, uchar8 *p_ucBufB, uchar8 v_ucLen);

uchar8	LibPub_WriteDataToE2prom( ushort16 v_usAddrIndex, uchar8 v_ucOffset, uchar8 *ptr_ucData );
uchar8	LibPub_ReadDataFromE2prom(ushort16 v_usAddrIndex, uchar8 v_ucOffset, uchar8 *ptr_ucData);
uchar8	LibPub_CheckE2promPara(ushort16 address, ushort16 addressbak, ushort16 *ptr_data, ushort16 len, uchar8 isCRC);
void LibPub_Inverse( uchar8 *p_ucData, uchar8 DataLen );
uchar8	LibPub_CheckPassword( uchar8 *p_ucPsw);
uchar8	 LibPub_CompareData(uchar8 *P_ucData1, uchar8 *P_ucData2, uchar8 v_ucDataLength, uchar8 v_ucCmpMode);

ushort16 LibPub_Buffer2ToUshort16( uchar8 *p_ucBytesBuffer );
ulong32  LibPub_Buffer4ToUlong32( uchar8 *p_ucBytesBuffer );
void LibPub_Ushort16ToBuffer2(uchar8 *p_ucBytesBuffer,ushort16 v_usShort16Buffer);
void LibPub_Ulong32ToBuffer4(uchar8 *p_ucBytesBuffer, ulong32 v_ulDoubleWordBuffer);
ulong32 LibPub_DECtoHEXBytes(uchar8 *P_ucSourceData,uchar8 V_ucDataLength);
void LibPub_HEXtoBCDBytes(ulong32 V_ulSourceData,uchar8 *P_ucResultData,uchar8 V_ucLen);
void LibPub_HEXtoAscii(uchar8 *p_ucSourceData, uchar8 *p_ucResultData, uchar8 v_ucLen );

void LibPub_Delay2us(void);
void LibPub_Delay5us(void);
void LibPub_Delay10us(void);
void LibPub_DelayNms(ushort16 v_uiNums);
void LibPub_Delay10xus(ushort16 v_uiNums);
///*--------------------------------- 函数区 ------------------------------------------------------------*///

///* 有形参的函数格式:*///
///**********************************************************************///
///* Brief:  函数功能简要描述                                           *///
///*                                                                    *///
///* Param:  入口参数说明，一个参数占一行                               *///
///*                                                                    *///
///* Return: 函数返回值的说明                                           *///
///*                                                                    *///
///* Note:   修改及其他说明                                             *///
///**********************************************************************///


///* 无形参的函数格式: *///
///**********************************************************************///
///* Brief:  检查RAM数据和E2数据正确性，只有带CRC和CEC+BAK的数据才检查  *///
///*                                                                    *///
///* Param:  address:E2地址                                             *///
///* Param:  addressbak:E2备份地址                                      *///
///* Param:  *ptr_data:要校验的数据头指针                               *///
///* Param:  len:数据长度，不含crc2字节                                 *///
///* Param:  isbackup:是否带备份标志                                    *///
///*                                                                    *///
///* Return: 校验正确则返回TRUE,错误则返回FALSE                         *///
///*                                                                    *///
///* Note:   修改及其他说明                                             *///
///**********************************************************************///
//uchar8	LibPub_CheckE2promPara(ushort16 address, ushort16 addressbak, ushort16 *ptr_data, ushort16 len, uchar8 isCRC)
//{
//	uchar8	V_ucResult = TRUE;
//	
//	///* 先算一下RAM中的CRC是不是正确 正确则直接返回，不需要再校验E2 *///
//	if ( CRC_EN == isCRC )
//	{
//		
//	}
//	
//	///* 如果第1出错误，则从第二处恢复，恢复后写第1处 *///
//	if ( address != addressbak )	///* 地址不相等则代表需要备份 *///
//	{
//		;
//	}
//	return V_ucResult;
//}
/////**********************************************************************///
/////* Brief:  向E2中写数据，应用层就使用该函数							  *///
/////*                                                                    *///
/////* Param:  v_usAddrIndex:E2地址索引                                   *///
/////* Param:  *ptr_ucData:要校验的数据头指针                               *///
/////*                                                                    *///
/////* Return: 正确则返回_SUCCESS,错误则返回FAILED                       	  *///
/////*                                                                    *///
/////* Note:   修改及其他说明                                             *///
/////**********************************************************************///
uchar8	LibPub_WriteDataToE2prom( ushort16 v_usAddrIndex, uchar8 v_ucOffset, uchar8 *ptr_ucData )
{
	uchar8		V_ucResult = _FAILED; 
	uchar8		V_ucIndex;
	ushort16	V_usCRC16 = 0;
	
	if ( v_usAddrIndex < LIB_E2P_INDEX_MAX )
	{
		for ( V_ucIndex=0; V_ucIndex<LIB_E2P_INDEX_MAX;  V_ucIndex++ )
		{
			if ( EEPROM_MAP_TAB[V_ucIndex].ucE2pAddressIndex == v_usAddrIndex )
			{ 
				if ( _TRUE == EEPROM_MAP_TAB[v_usAddrIndex].ucIsCRC )
				{
					V_usCRC16 = LibPub_CRC16_CCITT(ptr_ucData, EEPROM_MAP_TAB[v_usAddrIndex].ucE2pLen-2);
					ptr_ucData[EEPROM_MAP_TAB[v_usAddrIndex].ucE2pLen-2] = (uchar8)(V_usCRC16>>8);
					ptr_ucData[EEPROM_MAP_TAB[v_usAddrIndex].ucE2pLen-1] = (uchar8)(V_usCRC16 &0x00ff); 
				}
				
				if ( _SUCCESS == DrvE2p_WriteData( EEPROM_MAP_TAB[v_usAddrIndex].usE2pAddress+v_ucOffset,  ptr_ucData, EEPROM_MAP_TAB[v_usAddrIndex].ucE2pLen) )
				{
					V_ucResult = _SUCCESS;
					if ( _TRUE == EEPROM_MAP_TAB[v_usAddrIndex].ucIsBak )
					{
						if ( _SUCCESS == DrvE2p_WriteData( EEPROM_MAP_TAB[v_usAddrIndex+1].usE2pAddress+v_ucOffset,  ptr_ucData, EEPROM_MAP_TAB[v_usAddrIndex+1].ucE2pLen) )
						{
//							DrvE2p_WriteData( EEPROM_MAP_TAB[v_usAddrIndex+2].usE2pAddress+v_ucOffset,  ptr_ucData, EEPROM_MAP_TAB[v_usAddrIndex+2].ucE2pLen) ;
						    ///*只备份一处
						}
						else
						{
							V_ucResult = _FAILED;
						}
					}
				}
				break;
			}
		}
	}  
	
	return V_ucResult;
}
/////**********************************************************************///
/////* Brief:  从E2中读数据，应用层就使用该函数							   *///
/////*                                                                    *///
/////* Param:  v_usAddrIndex:E2地址索引                                   *///
/////* Param:  v_ucOffset:偏移量，			                               *///
/////* Param:  *ptr_ucData:要校验的数据头指针                              *///
/////*                                                                    *///
/////* Return: 正确则返回_SUCCESS,错误则返回FAILED                               *///
/////*                                                                    *///
/////* Note:   修改及其他说明                                              *///
/////**********************************************************************///
uchar8	LibPub_ReadDataFromE2prom(ushort16 v_usAddrIndex, uchar8 v_ucOffset, uchar8 *ptr_ucData)
{
	uchar8		V_ucResult = _FAILED;
	uchar8		V_ucIndex = 0,V_ucCnt = 0;
	uchar8		V_ucaE2pBuff[64];
	ushort16	V_usCRC16 = 0;
	
	if ( v_usAddrIndex < LIB_E2P_INDEX_MAX )
	{
		for ( V_ucIndex=0; V_ucIndex<LIB_E2P_INDEX_MAX;  V_ucIndex++ )
		{
			if ( EEPROM_MAP_TAB[V_ucIndex].ucE2pAddressIndex == v_usAddrIndex )
			{
				for ( V_ucCnt = 0; V_ucCnt < 3;  V_ucCnt++ )	///* 总共读3次 *///
				{
					if ( _FAILED == DrvE2p_ReadData( EEPROM_MAP_TAB[v_usAddrIndex].usE2pAddress+v_ucOffset,  V_ucaE2pBuff, EEPROM_MAP_TAB[v_usAddrIndex].ucE2pLen) )
					{
						if ( _TRUE == EEPROM_MAP_TAB[v_usAddrIndex].ucIsBak )
						{
							if ( _FAILED == DrvE2p_ReadData( EEPROM_MAP_TAB[v_usAddrIndex+1].usE2pAddress+v_ucOffset,  V_ucaE2pBuff, EEPROM_MAP_TAB[v_usAddrIndex+1].ucE2pLen) )
							{
//								if ( _FAILED == DrvE2p_ReadData( EEPROM_MAP_TAB[v_usAddrIndex+2].usE2pAddress+v_ucOffset,  V_ucaE2pBuff, EEPROM_MAP_TAB[v_usAddrIndex+2].ucE2pLen) )
								{
									continue;
								}
							}
							else
							{
								break; 
							}
						} 
					}
					else
					{
						break; 
					} 
				}///* end for ( V_ucCnt = 0; V_ucCnt < 3;  V_ucCnt++ ) *///
				if ( V_ucCnt >= 3 )	///* 如果3次都没有读成功，则直接返回错误 *///
				{
					return _FAILED;
				} 
				
				///* 如果有CRC,就比较一下crc是否正确 *///
				if ( _TRUE == EEPROM_MAP_TAB[v_usAddrIndex].ucIsCRC ) 
				{
					V_usCRC16  = (ushort16)V_ucaE2pBuff[EEPROM_MAP_TAB[v_usAddrIndex].ucE2pLen-1];
					V_usCRC16 |= (ushort16)(V_ucaE2pBuff[EEPROM_MAP_TAB[v_usAddrIndex].ucE2pLen-2] << 8); 
					
					if ( V_usCRC16 != LibPub_CRC16_CCITT( V_ucaE2pBuff, EEPROM_MAP_TAB[v_usAddrIndex].ucE2pLen-2 ) ) ///*  只判断crc是否正确，不判断是否
					{
						return _FAILED;
					}
				}
				///* 准备一下数据 *///
				LibPub_MemCopyBytes(V_ucaE2pBuff, ptr_ucData, EEPROM_MAP_TAB[v_usAddrIndex].ucE2pLen);
				
				V_ucResult = _SUCCESS;
				
				break;	///* break for( V_ucIndex=0; V_ucIndex<LIB_E2P_INDEX_MAX;  V_ucIndex++ ) *///
			}
		}///* end of for( V_ucIndex=0; V_ucIndex<LIB_E2P_INDEX_MAX;  V_ucIndex++ ) *///
	}
		
	return V_ucResult;
}
///**********************************************************************///
///*                                                                    *///
///* @brief    CRC16校验处理函数                                        *///
///*                                                                    *///
///* @param    fcs :校验数据原始值                                      *///
///* @param    cp :校验数据缓存的开始地址                               *///
///* @param    len :校验数据的总长度                                    *///
///* @param    result :校验数据结果选择，TRUE则输出校验结果             *///
///*                                                                    *///
///* @return   返回校验值，高位在前                                     *///
///*                                                                    *///
///* @note     多项式：G(x) =x16+ x12+ x5+ 1                            *///
///*                                                                    *///
///**********************************************************************/// 
ushort16 LibPub_CRC16_CCITT(uchar8 *cp, ushort16 len)
{
	ushort16 usVfcs=0x0000;
	
	while (len--)
	{
		usVfcs = (uint16_t)((usVfcs >> 8) ^ fcstab[(usVfcs ^ *cp++) & 0xff]);
	}
	
	return usVfcs;
}
///**********************************************************************///
///* Brief:  按字节拷贝数据                                             *///
///*                                                                    *///
///* Param:  pSourceData：原始数据                                      */// 
///* Param:  pResultData：目标数据                                      */// 
///*                                                                    *///
///* Param:  len：数据长度                                              */// 
///*                                                                    *///
///* Return:                                                            *///
///* Note:                                                              *///
///**********************************************************************///
void LibPub_MemCopyBytes(uchar8 *pSourceData, uchar8 *pTargetData, uchar8 len)
{
	uchar8 i;
	
	for ( i=0; i<len; i++ )
	{
		*(pTargetData+i) = *(pSourceData+i);
	}
}

/////**********************************************************************///
/////* Brief:  校验crc是否正确                                            *///
/////*                                                                    *///
/////* Param:  *cp：要校验数据的头指针                                    */// 
/////* Param:  len：数据长度                                              */// 
/////*                                                                    *///
/////* Return: TRUE:校验成功； FALSE:校验失败                             *///
/////*                                                                    *///
/////* Note:                                                              *///
/////**********************************************************************///
uchar8 LibPub_CrcCheck( uchar8 *cp, uchar8 len, ushort16 cmpcrc)
{
	ushort16 V_usResult;
	
	if ( LibPub_ZeroCheck(cp, len) == _TRUE ) return _FALSE;	///* 如果都是0，就不需要再试了，认为数据是错误的 *///
	
	V_usResult = LibPub_CRC16_CCITT( cp, len);
	
	if ( V_usResult != cmpcrc )  return _FALSE;
	
	return _TRUE;
}

/////**********************************************************************///
/////* Brief:  数据是否为0检查                                            *///
/////*                                                                    *///
/////* Param:  *cp：要校验数据的头指针                                    */// 
/////* Param:  len：数据长度                                              */// 
/////*                                                                    *///
/////* Return: TRUE:数据为0； FALSE:数据不为0                             *///
/////*                                                                    *///
/////* Note:                                                              *///
/////**********************************************************************///
uchar8 LibPub_ZeroCheck( uchar8 *cp, uchar8 len)
{
	uchar8 i;
	
	for ( i=0; i<len; i++ )
	{
		if ( *(cp+i) != 0) return _FALSE;
	}
	return _TRUE;
}

///**********************************************************************///
///* Brief:  数据是否为全F检查                                            *///
///*                                                                    *///
///* Param:  *cp：要校验数据的头指针                                    */// 
///* Param:  len：数据长度                                              */// 
///*                                                                    *///
///* Return: TRUE:数据为0； FALSE:数据不为0                             *///
///*                                                                    *///
///* Note: 此函数用于中断ApiDLT645_UARTReceiveDataJudge判断目标设备地址是否为全F *///
///**********************************************************************///
uchar8 LibPub_0xFFCheckInt( uchar8 *cp, uchar8 len)
{
	uchar8 i;
	
	for ( i=0; i<len; i++ )
	{
		if ( *(cp+i) != 0xFF) return _FALSE;
	}
	return _TRUE;
}

///**********************************************************************///
///* Brief:  1字节hex转换成1字节BCD                                      *///
///*                                                                    *///
///* Param:  hexdata:需要转换的数据                                      */// 
///*                                                                    *///
///* Return: 返回转换后的结果                                            *///
///*                                                                    *///
///* Note:   如果hex大于99，则返回00，                                   *///
///**********************************************************************///
uchar8 LibPub_1Hex_2_1BCD( uchar8 hexdata)
{
	if ( hexdata > 99 ) return 0;
	
	return ( ((hexdata/10)<<4) + hexdata%10 );
}
///**********************************************************************///
///* Brief:  1字节BCD转换成1字节hex                                      *///
///*                                                                    *///
///* Param:  v_ucBcdData:需要转换的数据                                  */// 
///*                                                                    *///
///* Return: 返回转换后的结果                                            *///
///*                                                                    *///
///* Note:    传过来的数据理论上必须是BCD码，这里不判数据是否合理          *///
///**********************************************************************///
uchar8 LibPub_1BCD_2_1HEX( uchar8 v_ucBcdData)
{
	return ( ( (v_ucBcdData>>4)*10 ) + (v_ucBcdData & 0x0f) );
}

///**********************************************************************///
///* Brief:  1字节BCD加法                                                *///
///*                                                                    *///
///* Param:  v_ucBcdA:被加数                                            */// 
///* Param:  v_ucBcdB:  加数                                            */// 
///* Param:  *p_ucCarry:进位                                            */// 
///*                                                                    *///
///* Return: 返回加完后的结果                                            *///
///*                                                                    *///
///* Note:   如果hex大于99，则返回00，                                   *///
///**********************************************************************///
uchar8 LibPub_1BtyeBcdAdd(uchar8 v_ucBcdA, uchar8 v_ucBcdB, uchar8 *p_ucCarry)
{
	uchar8	V_ucResult;	 
	
	V_ucResult = LibPub_1BCD_2_1HEX(v_ucBcdA) + LibPub_1BCD_2_1HEX(v_ucBcdB) ;
	V_ucResult += *p_ucCarry;
	*p_ucCarry = 0;
	
	if ( V_ucResult >= 100 )
	{
		*p_ucCarry = 1;
		V_ucResult = V_ucResult-100;
	}
	  
	return (LibPub_1Hex_2_1BCD(V_ucResult));
	
}
///**********************************************************************///
///* Brief:  多字节BCD加法                                               *///
///*                                                                    *///
///* Param:  *p_ucBcdA:被加数                                            *///
///* Param:  *p_ucBcdB:被加数                                            */// 
///* Param:  v_ucLen:数据长度                                            */// 
///*                                                                    *///
///* Return: 无                                                         *///
///*                                                                    *///
///* Note:   加法从最低位开始加，进位到最高位                             *///
///**********************************************************************///
void LibPub_NBtyesBcdAdd(uchar8 *p_ucBcdA, uchar8 *p_ucBcdB, uchar8 v_ucLen)
{
	uchar8	V_ucCarry = 0; 
	uchar8	V_ucCnti;
	
	for ( V_ucCnti = 0; V_ucCnti < v_ucLen; V_ucCnti++ )
	{
		p_ucBcdA[v_ucLen-V_ucCnti-1] = LibPub_1BtyeBcdAdd(p_ucBcdA[v_ucLen-V_ucCnti-1], p_ucBcdB[v_ucLen-V_ucCnti-1], &V_ucCarry );
	}
	
}
///**********************************************************************///
///* Brief:  获取系统节拍                                               *///
///*                                                                    *///
///* Return: 返回定时计数                                               *///
///*                                                                    *///
///* Note:   主要用于计算时间差，如超时                                 *///
///**********************************************************************///
ulong32 LibPub_GetTimerBeat(void)
{
	ulong32 V_ulTimeOld,V_ulTimeNew;
	
	do
	{
		V_ulTimeOld = GStr_Monitor.ulTimer_ms_old;
		V_ulTimeNew = GStr_Monitor.ulTimer_ms;
		
		if ( V_ulTimeNew == 0 )
		{
			if ( (V_ulTimeOld==0xFFFFFFFF) || (V_ulTimeOld==0) )
			{
				return V_ulTimeOld;
			}
			continue;
		}
	}while ( V_ulTimeNew != (V_ulTimeOld+1) );
	
	return V_ulTimeOld;
}
///**********************************************************************///
///* Brief:  获取系统节拍                                                *///
///*                                                                    *///
///* Return: 返回定时计数                                                *///
///*                                                                    *///
///* Note:   用于串口中断调用，其他情况调用 LibPub_GetTimerBeat		    *///
///**********************************************************************///
ulong32 LibPub_GetTimerBeatInt0(void)
{
	ulong32 V_ulTimeOld,V_ulTimeNew;
	
	do
	{
		V_ulTimeOld = GStr_Monitor.ulTimer_ms_old;
		V_ulTimeNew = GStr_Monitor.ulTimer_ms;
		
		if ( V_ulTimeNew == 0 )
		{
			if ( (V_ulTimeOld==0xFFFFFFFF) || (V_ulTimeOld==0) )
			{
				return V_ulTimeOld;
			}
			continue;
		}
	}while ( V_ulTimeNew != (V_ulTimeOld+1) );
	
	return V_ulTimeOld;
}
///**********************************************************************///
///* Brief:  获取系统节拍                                                *///
///*                                                                    *///
///* Return: 返回定时计数                                                *///
///*                                                                    *///
///* Note:   用于串口中断调用，其他情况调用 LibPub_GetTimerBeat		    *///
///**********************************************************************///
ulong32 LibPub_GetTimerBeatInt1(void)
{
	ulong32 V_ulTimeOld,V_ulTimeNew;
	
	do
	{
		V_ulTimeOld = GStr_Monitor.ulTimer_ms_old;
		V_ulTimeNew = GStr_Monitor.ulTimer_ms;
		
		if ( V_ulTimeNew == 0 )
		{
			if ( (V_ulTimeOld==0xFFFFFFFF) || (V_ulTimeOld==0) )
			{
				return V_ulTimeOld;
			}
			continue;
		}
	}while ( V_ulTimeNew != (V_ulTimeOld+1) );
	
	return V_ulTimeOld;
}
///**********************************************************************///
///* Brief:  获取时间差跟指定数值比较大小                               *///
///*                                                                    *///
///* Param:  timer:给定时间                                             */// 
///* Param:  basetimer:给定时间，通常是LibPub_GetTimerBeat()            */// 
///* Param:  duration:指定间隔                                          */// 
///*                                                                    *///
///* Return: TRUE：时间差大于指定间隔，FALSE:时间差小于指定间隔         *///
///*                                                                    *///
///* Note:   主要用于计算时间差，如超时                                 *///
///**********************************************************************///
uchar8 LibPub_GetDiffTime( ulong32 timer, ulong32 basetimer, ulong32 duration )
{
	if (basetimer < timer)
	{
		basetimer = basetimer + (0xffffffff - timer);
	}
	else
	{
		basetimer = basetimer - timer;
	}
	
	if ( basetimer >= duration )
	{
		return (_TRUE);
	}
 
	return (_FALSE); 
}
///**********************************************************************///
///* Brief:  指定变量数据设置指定值                                     *///
///*                                                                    *///
///* Param:  p_datahead:变量首指针                                      */// 
///* Param:  val:设定值                                                 */// 
///* Param:  len:数据长度                                               */// 
///*                                                                    *///
///* Return: 返回定时计数                                               *///
///*                                                                    *///
///* Note:                                                              *///
///**********************************************************************///
void LibPub_MemSetBytes( uchar8 *p_ucdatahead, uchar8 v_ucVal, ushort16 v_usLen )
{
	ushort16 V_ucCnt_i;
	
	for ( V_ucCnt_i = 0; V_ucCnt_i < v_usLen; V_ucCnt_i++ )
	{
		*(p_ucdatahead + V_ucCnt_i) = v_ucVal;
	}
}

///**********************************************************************///
///* Brief:  计算制定数据长度的累加和                                     *///
///*                                                                    *///
///* Param:  pData:数据首地址                                            */// 
///* Param:  v_ucLen：数据长度                                           *///  
///*                                                                    *///
///* Return: 返回累加和                                                  *///
///*                                                                    *///
///* Note:                                                              *///
///**********************************************************************///
uchar8 LibPub_CalSum(uchar8 *pData, uchar8 v_ucLen)
{
	uchar8 i,V_ucSum = 0;
	
	for ( i=0; i<v_ucLen; i++ )
	{
		V_ucSum += pData[i];
	}
	
	return V_ucSum;
}
///**********************************************************************///
///* Brief:  原始数据倒向后赋给目标数据                                   *///
///*                                                                    *///
///* Param:  pSourceData：原始数据                                      */// 
///* Param:  pResultData：目标数据                                      *///  
///* Param:  len：数据长度                                              */// 
///*                                                                    *///
///* Return:                                                            *///
///* Note:                                                              *///
///**********************************************************************///
void LibPub_MemExchangeBytes(uchar8 *pSourceData, uchar8 *pTargetData, uchar8 len)
{
	uchar8 V_ucCnt;
	
	for ( V_ucCnt=0; V_ucCnt<len; V_ucCnt++ )
	{
		*(pTargetData+V_ucCnt) = *(pSourceData+len-1-V_ucCnt);
	}
}
/////**********************************************************************///
/////* Brief:  判断指定长度数据是否为BCD                                    *///
/////*                                                                    *///
/////* Param:  p_ucData：数据指针                                          *///  
/////* Param:  v_ucLen：数据长度                                           */// 
/////*                                                                    *///
/////* Return: 判断结果，是回TRUE,不是回FALSE                              *///
/////* Note:                                                              *///
/////**********************************************************************///
uchar8 LibPub_IsBCD(uchar8 *p_ucData, uchar8 v_ucLen )
{
	uchar8 V_ucCnt;
	
	for ( V_ucCnt=0; V_ucCnt<v_ucLen; V_ucCnt++ )
	{
		if ( ( (p_ucData[V_ucCnt] & 0x0F) > 0x09 )|| ((p_ucData[V_ucCnt] & 0xF0) > 0x90 ) )
		{
			return _FAILED;
		}
	}
	
	return _SUCCESS;
}
/////**********************************************************************///
/////* Brief:  数据倒向                                                   *///
/////*                                                                    *///
/////* Param:  p_ucData：数据指针                                          *///  
/////* Param:  v_ucLen：数据长度                                           */// 
/////*                                                                    */// 
/////* Note:                                                              *///
/////**********************************************************************///
void LibPub_Inverse( uchar8 *p_ucData, uchar8 DataLen )
{
	uchar8 V_ucCnt, V_ucTemp08;
	
	for( V_ucCnt=0; V_ucCnt<DataLen/2; V_ucCnt++ )
	{
		V_ucTemp08 = p_ucData[V_ucCnt];
		p_ucData[V_ucCnt] = p_ucData[DataLen-1-V_ucCnt];
		p_ucData[DataLen-1-V_ucCnt] = V_ucTemp08;//交换数据
	}
}
///**********************************************************************///
///* Brief:  判断密码                                                   *///
///*                                                                    *///
///* Param:  p_ucData：数据指针                                          *///  
///* Param:  v_ucLen：数据长度                                           */// 
///*                                                                    */// 
///* Return: 判断结果，是回TRUE,不是回FALSE                              *///
///* Note:                                                              *///
///**********************************************************************///
uchar8	LibPub_CheckPassword( uchar8 *p_ucPsw)
{
	uchar8 V_ucTemp,V_ucCnt_i,V_ucTempBuff[11];
	if(GStr_Counter.ucPasswordErr_Cnt[*p_ucPsw]>=3)
	{
			GStr_Counter.ucPasswordErr_Cnt[*p_ucPsw]=3;
			return _FAILED;
	}
	
	if(_FAILED==LibPub_ReadDataFromE2prom( LIB_E2P_Password, 0, V_ucTempBuff ))
	{
		return _FAILED;
	}
	
	if( *p_ucPsw == 0x00 ) 
	{ 
		V_ucTemp = 0;             ///*00级密码 偏移为0  
	}
	else if( *p_ucPsw == 0x01 ) 
	{ 
		V_ucTemp = 3; 
	}
	else if( *p_ucPsw == 0x02 ) 
	{
		V_ucTemp = 6; 
	}	
	else
	{
		return _FAILED;
	}

	for( V_ucCnt_i=0; V_ucCnt_i<3; V_ucCnt_i++ )
	{
		if ( p_ucPsw[V_ucCnt_i+1] != V_ucTempBuff[V_ucTemp+V_ucCnt_i] )
		{
				GStr_Counter.ucPasswordErr_Cnt[*p_ucPsw]++;
			  if(GStr_Counter.ucPasswordErr_Cnt[*p_ucPsw]>=3)
				{		
						GStr_Monitor.usPasswordErrTime[*p_ucPsw]=1440;///24小时。已分钟为单位
				}
				return _FAILED;
		}
	}
	
	GStr_Counter.ucPasswordErr_Cnt[*p_ucPsw]=0;
	return _SUCCESS;
}
///**********************************************************************///
///* Brief:  延时2us								                    *///
///*                                                                    *///
///* Return: 无                                                         *///
///*                                                                    *///
///* Note:     大约2.2us                                                *///
///**********************************************************************///
void LibPub_Delay2us(void)
{
	return;
}


///**********************************************************************///
///* Brief:  延时5us								                    *///
///*                                                                    *///
///* Return: 无                                                         *///
///*                                                                    *///
///* Note:     等于1大约5us                                           *///
///**********************************************************************///
void LibPub_Delay5us(void)
{
	uchar8 V_ucVnt = 1; 
	
	while ( V_ucVnt-- )
	{
		;
	}
}

///**********************************************************************///
///* Brief:  延时10us								                    *///
///*                                                                    *///
///* Return: 无                                                         *///
///*                                                                    *///
///* Note:  大约10us                                                    *///
///**********************************************************************///
void LibPub_Delay10us(void)
{
//	uchar8 V_ucCnt ;
	
//	for( V_ucCnt=0;V_ucCnt<3;V_ucCnt++ )
	{
		LibPub_Delay2us();
		LibPub_Delay2us();
		LibPub_Delay5us();
	}
}

///**********************************************************************///
///* Brief:  延时1ms								                    *///
///*                                                                    *///
///* Param:  v_uiNums: 延时时间，最大两字节                              *///  
///*                                                                    *///
///* Return: 无                                                         *///
///*                                                                    *///
///* Note:   误差较小，基本可以忽略,数值越小越精准
///*         1-1；2-2；4-3.9；8-7.9；10-9.8；50-48；100-96.8；500-488
///**********************************************************************///
void LibPub_DelayNms(ushort16 v_uiNums)
{
	ulong32 V_ulCnt;
	
	for( V_ulCnt=0; V_ulCnt<(v_uiNums*19); V_ulCnt++ )
	{
		LibPub_Delay10us();
	}
}

///**********************************************************************///
///* Brief:  延时10倍us								                    *///
///*                                                                    *///
///* Param:  v_uiNums: 延时时间，最大两字节                              *///  
///*                                                                    *///
///* Return: 无                                                         *///
///*                                                                    *///
///* Note:  如果超过1ms建议使用ms延时，参数为50时大约为650us延时          *///
///**********************************************************************///
#if ( METER_TYPE != METER_TYPE_DTSY666 )
void LibPub_Delay10xus(ushort16 v_uiNums)
{
	ushort16 V_ulCnt;
	
	for( V_ulCnt=0; V_ulCnt<(v_uiNums); V_ulCnt++ )
	{
		LibPub_Delay10us();
	}
}
#endif

///**********************************************************************///
///* Brief:  比较一组数据的大小，从最后一个数组成员开始								                    *///
///*                                                                    *///
///* Param:                              *///  
///*                                                                    *///
///* Return:                                                        *///
///*                                                                    *///
///* Note:          *///
///**********************************************************************///

uchar8	 LibPub_CompareData(uchar8 *P_ucData1, uchar8 *P_ucData2, uchar8 v_ucDataLength, uchar8 v_ucCmpMode)
{
	uchar8 V_ucCnt_i;
	
    for( V_ucCnt_i = 0;  V_ucCnt_i < v_ucDataLength; V_ucCnt_i++ )
	{		
		if( CMP_MODE_HIGHT == v_ucCmpMode )
		{
			if( P_ucData1[V_ucCnt_i] > P_ucData2[V_ucCnt_i] )
			{
				return C_GreaterThan;
			}
			else if(  P_ucData1[V_ucCnt_i] < P_ucData2[V_ucCnt_i] )
			{
				return C_LessThan;
			}
		}
		else
		{
			if( P_ucData1[v_ucDataLength-1-V_ucCnt_i] > P_ucData2[v_ucDataLength-1-V_ucCnt_i] )
			{
				return C_GreaterThan;
			}
			else if(  P_ucData1[v_ucDataLength-1-V_ucCnt_i] < P_ucData2[v_ucDataLength-1-V_ucCnt_i]  )
			{
				return C_LessThan;
			}
		}	 
	}
	
	return C_Equal;	
}


///**********************************************************************///
///* Brief: 2字节转short整型						                        *///
///*                                                                    *///
///* Param: p_ucBytesBuffer：2字节数据指针                               *///  
///*                                                                    *///
///* Return:转换后的数据                                                 *///
///*                                                                    *///
///* Note:                                                              *///
///**********************************************************************///
ushort16 LibPub_Buffer2ToUshort16( uchar8 *p_ucBytesBuffer )
{
	ushort16 v_usShort16Buffer;
	
	#if(STORAGE_MODE==SMALL_MODE)
    {
		v_usShort16Buffer  = p_ucBytesBuffer[1];
		v_usShort16Buffer <<= 8;
		v_usShort16Buffer |= p_ucBytesBuffer[0];
	}
	#else
	{
		v_usShort16Buffer  = p_ucBytesBuffer[0];
		v_usShort16Buffer <<= 8;
		v_usShort16Buffer |= p_ucBytesBuffer[1];
	}
	#endif
	
	return v_usShort16Buffer;
}


///**********************************************************************///
///* Brief: 1个short转2字节uart8							                *///
///*                                                                    *///
///* Param: p_ucBytesBuffer：2字节数据指针                               *///  
///* Param: v_usShort16Buffer：short整型待转数据                         *///  
///*                                                                    *///
///* Return:                                                            *///
///*                                                                    *///
///* Note:                                                              *///
///**********************************************************************///
#if( METER_TYPE == METER_TYPE_DTSY666 )
void LibPub_Ushort16ToBuffer2(uchar8 *p_ucBytesBuffer,ushort16 v_usShort16Buffer)
{
    ushort16 V_usTempData;
	
    V_usTempData = v_usShort16Buffer;
	
	#if(STORAGE_MODE==SMALL_MODE)
    {
		p_ucBytesBuffer[0] = (uchar8)V_usTempData;
		V_usTempData >>= 8;
		p_ucBytesBuffer[1] = (uchar8)V_usTempData;
	#else
   {
		p_ucBytesBuffer[1] = (uchar8)V_usTempData;
		V_usTempData >>= 8;
		p_ucBytesBuffer[0] = (uchar8)V_usTempData;
   }
	#endif
	
}
#endif
///**********************************************************************///
///* Brief: 1个long转4字节uart8							                *///
///*                                                                    *///
///* Param: p_ucBytesBuffer：4字节数据指针                               *///  
///* Param: v_ulDoubleWordBuffer：4字节整型数据                          *///  
///*                                                                    *///
///* Return:                                                            *///
///*                                                                    *///
///* Note:                                                              *///
///**********************************************************************///
///**********************************************************************************************///
#if( METER_TYPE == METER_TYPE_DTSY666 )
void LibPub_Ulong32ToBuffer4(uchar8 *p_ucBytesBuffer, ulong32 v_ulDoubleWordBuffer)
{
	ulong32 V_ulTempData=0;
	uchar8  V_ucCnti;
 
	V_ulTempData = v_ulDoubleWordBuffer;
	
	for( V_ucCnti=0; V_ucCnti<4; V_ucCnti++ )
	{
		#if(STORAGE_MODE==SMALL_MODE)
		{
			p_ucBytesBuffer[V_ucCnti] = (uchar8)V_ulTempData;
		}
		#else
		{
			p_ucBytesBuffer[3-V_ucCnti] = (uchar8)V_ulTempData;
		}
		#endif
		
		V_ulTempData >>= 8;
	} 
} 
#endif
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    4字节uart8	转1个long
 *
 *  @param    p_ucBytesBuffer : 4字节数据指针
 *
 *  @return   转换后的数据
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
///**********************************************************************************************///
ulong32  LibPub_Buffer4ToUlong32( uchar8 *p_ucBytesBuffer )
{
	ulong32 V_ulResult = 0;
	uchar8 V_ucCnti;
	
	for( V_ucCnti=0; V_ucCnti<4; V_ucCnti++ )
	{
		V_ulResult <<= 8;
		#if(STORAGE_MODE==SMALL_MODE)
		{
			V_ulResult |= p_ucBytesBuffer[3-V_ucCnti];
		}
		#else
		{
			V_ulResult |= p_ucBytesBuffer[  V_ucCnti];
		}
        #endif
	}
    
	return V_ulResult;	
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    多字节BCD减法,
 *
 *  @param    p_ucBufA : 被减数,同时存储转换结果
 *  @param    p_ucBufB : 减数
 *  @param    ucLen : 长度
 *
 *  @return   none
 *
 *  @note     注意：调用函数之前要确保被减数比减数大并且是低地址是高位，高地址是低位
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void LibPub_NBytesBCDSub(uchar8 *p_ucBufA, uchar8 *p_ucBufB, uchar8 v_ucLen)
{
	uchar8 V_ucCnt_i,V_ucCnt_j,V_ucCnt_k;
	uchar8 V_ucBfCarry=0; // 进位标志
	
	for( V_ucCnt_i = (v_ucLen-1); V_ucCnt_i<v_ucLen; V_ucCnt_i-- )
	{
		V_ucCnt_j = p_ucBufB[V_ucCnt_i] + V_ucBfCarry;
		V_ucCnt_k = 0;
		
		if( V_ucCnt_j < p_ucBufB[V_ucCnt_i] )
		{
			V_ucCnt_k = 1;
		}
		
		V_ucBfCarry = 0;
		if( (p_ucBufA[V_ucCnt_i]&0x0f) < (V_ucCnt_j&0x0f) )
		{
			if( p_ucBufA[V_ucCnt_i] < V_ucCnt_j )
			{
				p_ucBufA[V_ucCnt_i] = 0x9a - V_ucCnt_j + p_ucBufA[V_ucCnt_i];			//0xa0-6;
	           	V_ucBfCarry = 1;
	        }
			else
			{
				p_ucBufA[V_ucCnt_i] = p_ucBufA[V_ucCnt_i] - V_ucCnt_j - 6;
			}
		}
		else
		{
			if( p_ucBufA[V_ucCnt_i] < V_ucCnt_j )
			{
				p_ucBufA[V_ucCnt_i] = 0xa0 - V_ucCnt_j + p_ucBufA[V_ucCnt_i];
	            V_ucBfCarry = 1;
	        }
			else
				p_ucBufA[V_ucCnt_i] = p_ucBufA[V_ucCnt_i] - V_ucCnt_j;
		}
		if( V_ucCnt_k )
		{
			V_ucBfCarry = 1;		//由于V_ucCnt_k=1时，不会产生借位
		}
	}
	
	return;
}


///**********************************************************************///
///* Brief: 多字节bcd转hex   返回值为4字节无符号长整型不能超过数据范围					                    *///
///*                                                                    *///
///* Param:                              *///  
///*                                                                    *///
///* Return:                                                        *///
///*                                                                    *///
///* Note:          *///
///**********************************************************************///
///**********************************************************************************************///
ulong32 LibPub_DECtoHEXBytes(uchar8 *P_ucSourceData,uchar8 V_ucDataLength)
{
	uchar8  V_ucFlagTemp = 1;
	ulong32 V_ulTemp = 1;
    ulong32 V_ulDataTemp = 0;
	uchar8 	V_ucTurnTemp = 0;
	
	if((V_ucDataLength>0)&&(V_ucDataLength<5))
	{
		for(V_ucTurnTemp = V_ucDataLength;V_ucTurnTemp >0;V_ucTurnTemp-- )
		{
			V_ulDataTemp += ((*(P_ucSourceData+V_ucTurnTemp-1)&0x0f)%10)*V_ulTemp;
			V_ulTemp*=10;
			V_ulDataTemp += ((*(P_ucSourceData+V_ucTurnTemp-1)&0xf0)>>4)*V_ulTemp;			
			V_ulTemp *= 10;
		}
	}
	return(V_ulDataTemp);
}

///**********************************************************************///
///* Brief: 多字节bcd转hex   返回值为4字节无符号长整型不能超过数据范围					                    *///
///*                                                                    *///
///* Param:                              *///  
///*                                                                    *///
///* Return:                                                        *///
///*                                                                    *///
///* Note:          *///
///**********************************************************************///
///**********************************************************************************************///
void LibPub_HEXtoBCDBytes(ulong32 V_ulSourceData,uchar8 *P_ucResultData,uchar8 V_ucLen)
{
	uchar8   V_ucTurnTemp ;
 	ulong32  V_ulDataTemp;
	
  	V_ulDataTemp = V_ulSourceData;  
		
	for( V_ucTurnTemp =V_ucLen ; V_ucTurnTemp>0; V_ucTurnTemp-- )
	{   
		*(P_ucResultData+V_ucTurnTemp-1) =(uchar8)(V_ulDataTemp%10);
		V_ulDataTemp = V_ulDataTemp/10;
		*(P_ucResultData+V_ucTurnTemp-1) |=((uchar8)(V_ulDataTemp%10) << 4);		
		V_ulDataTemp = V_ulDataTemp/10;
	} 
}

///**********************************************************************///
///* Brief: 比较多字节数组大小，取最大值或者最小值					                    *///
///*                                                                    *///
///* Param:    P_ucSourceData需要比较的数组 需放在一起
///  P_ucResultData 最大的数组或者最小的数组	V_ucLen 数组的长度  V_Num 数组个数
///   V_Mode  取最大值还是最小值 C_MAX  C_MIN  v_ucCmpMode大小端比较

///*                                                                    *///
///* Return:                                                        *///
///*                                                                    *///
///* Note:          *///
///**********************************************************************///
///**********************************************************************************************///
uchar8 LibPub_CompareNBufs(uchar8 *P_ucSourceData,uchar8 *P_ucResultData,uchar8 V_ucLen,uchar8 V_Num,uchar8 V_Mode,uchar8 v_ucCmpMode)
{
//	uchar8   *p_ucBufData;
	uchar8 i;
// 	ulong32  v_ulDataTemp;
	
	if(V_Num<=1)
	{
		return _FAILED;
	}
//	LibPub_MemCopyBytes(P_ucSourceData,p_ucBufData, V_ucLen*V_Num);

    LibPub_MemCopyBytes((P_ucSourceData+(V_Num-1)*V_ucLen),P_ucResultData, V_ucLen);///刚开始要比较的最后一个数组为最大的

	
	for(i=V_Num;i>1;i--)
	{
		if(V_Mode==C_MAX)
		{
			if(C_GreaterThan!=LibPub_CompareData(P_ucResultData,  (P_ucSourceData+(i-2)*V_ucLen), V_ucLen, v_ucCmpMode))
			{
				 LibPub_MemCopyBytes((P_ucSourceData+(i-2)*V_ucLen),P_ucResultData, V_ucLen);
			}
		}
		else
		{
			if(C_LessThan!=LibPub_CompareData(P_ucResultData,  (P_ucSourceData+(i-2)*V_ucLen), V_ucLen, v_ucCmpMode))
			{
				 LibPub_MemCopyBytes((P_ucSourceData+(i-2)*V_ucLen),P_ucResultData, V_ucLen);
			}
		}
	}
	return _SUCCESS;
}


void LibPub_HEXtoAscii(uchar8 *p_ucSourceData, uchar8 *p_ucResultData, uchar8 v_ucLen )
{
	uchar8 V_ucCnti,V_ucCntj ; 
	uchar8 V_ucAscTemp[2];
	
	for( V_ucCnti = 0; V_ucCnti < v_ucLen; V_ucCnti++ )
	{    
		V_ucAscTemp[0] = ( (p_ucSourceData[V_ucCnti] >> 4 ) & 0x0f );
		V_ucAscTemp[1] = (  p_ucSourceData[V_ucCnti] & 0x0f );
		
		for( V_ucCntj = 0; V_ucCntj < 2; V_ucCntj++ )
		{
			if( V_ucAscTemp[V_ucCntj] < 10 )
			{
				V_ucAscTemp[V_ucCntj] = V_ucAscTemp[V_ucCntj] + 0x30;
			}
			else if( V_ucAscTemp[V_ucCntj] < 16 )
			{
				V_ucAscTemp[V_ucCntj] = V_ucAscTemp[V_ucCntj] + 0x37;
			}
		}
		
		LibPub_MemCopyBytes( V_ucAscTemp,  p_ucResultData+V_ucCnti*2, 2 );
	} 
}
/////*--------------------------------- 注释详解区 ---------------------------------------------------------*///

/////* 注释1: 一些复杂的功能可以在这里注释，主要是注释上面函数的功能，如有需要可以每一个函数配一个注释详解区*///

/////* 注释2: *///

/////*------------------------------------------------------------------------------------------------------*///

