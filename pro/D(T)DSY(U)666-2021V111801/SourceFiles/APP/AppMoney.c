/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    AppMoney.c                                                                          
**** Brief:       金额处理文件                                                                      
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
 *  该文件所有函数的前缀为 ApiMoney_
 *  文件主函数和对外函数需放在文件的首部，并且主函数需要放在第一个位置;
 *  函数注释采用标准模板，函数内部注释采用//;
 *  对于注释较多的部分，可以增加一个注释符，然后详细说明放在文件的尾部;
 *--------------------------------- 文件功能说明 -------------------------------------------------------*/
 
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
void ApiMoney_RemainMoneyProcess(void);
// void ApiMoney_RemainMoneyCheck(void); 
void ApiMoney_RefreshPrice(void);
void ApiMoney_TimeingHoldMoney(void);
static void ApiMoney_MultPTCT(ulong32 *sourceptr,ulong32 *resultptr);
/*----------------< 函数定义 >----------------------------------*/

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    剩余金额处理函数，处理金额扣减，金额扣减每0.01kWh扣减一次
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
 
void ApiMoney_RemainMoneyProcess(void)
{
	uchar8 V_ucaBuff_RemainMoney[6];
	uchar8 V_ucaBuff_TickMoney[6];
	uchar8 V_ucaBuff_Price[6];
	#if(METER_TYPE==METER_TYPE_DTSY666)///三相表要乘以PTCT，单相表PTCT强制为1.电价不作处理
	ulong32 V_ulBuff[2];
	#endif
	/*------------------------------------------------------------------------------------------------------*/	
	/* 先判断一下是否有扣减标志，没有就直接退出 */
	if( F_SYS_MONEY_MoneyDEC != (GStr_Flag.ucMoney & F_SYS_MONEY_MoneyDEC) )
	{
		return;
	}
	GStr_Flag.ucMoney &= ~ F_SYS_MONEY_MoneyDEC;
	
	/*------------------------------------------------------------------------------------------------------*/	
	/* 校验一下剩余金额 */
	ApiPwOn_MoneyParaCheck();
	LibPub_MemCopyBytes( &GStr_Money.ucaRemainMoney[0],  &V_ucaBuff_RemainMoney[0], 6 ); 	// 复制剩余金额 
	LibPub_MemCopyBytes( &GStr_Money.ucaTickMoney[0],  &V_ucaBuff_TickMoney[0], 6 );		// 复制透支金额
	
	/*------------------------------------------------------------------------------------------------------*/		
	/* 获取一下扣减单价（单价=PT*CT*电价），主要是刷新一下电价 */
	ApiMoney_RefreshPrice();
	#if(METER_TYPE==METER_TYPE_DTSY666)///三相表要乘以PTCT，单相表PTCT强制为1.电价不作处理
//	V_ulBuff[0]=LibPub_Buffer4ToUlong32(&GStr_PRICE.ucaPrice[0]);
	V_ulBuff[0]=LibPub_DECtoHEXBytes(&GStr_PRICE.ucaPrice[0],4);///电价转ulong32  HEX
	ApiMoney_MultPTCT(&V_ulBuff[0],&V_ulBuff[1]);///电价*PT*CT//真实消费电价
	LibPub_HEXtoBCDBytes(V_ulBuff[1],&V_ucaBuff_Price[2],4);///真实消费电价，转成BCD
	#else
	LibPub_MemCopyBytes( &GStr_PRICE.ucaPrice[0],  &V_ucaBuff_Price[2], 4 );
	#endif
	V_ucaBuff_Price[0] = 0;
	V_ucaBuff_Price[1] = 0;

	
	/*------------------------------------------------------------------------------------------------------*/		
	/* 判断剩余金额和扣减单价的大小关系，进行金额扣减 */
	if( C_LessThan != LibPub_CompareData( &GStr_Money.ucaRemainMoney[0], &V_ucaBuff_Price[0], 6, CMP_MODE_HIGHT ) )
	{
		if( C_Equal == LibPub_CompareData( &GStr_Money.ucaRemainMoney[0], &V_ucaBuff_Price[0], 6, CMP_MODE_HIGHT ) )
		{
			// 如果相等，则存一下E2
			GStr_Flag.ucMoney |= F_SYS_MONEY_Money2E2;
		}
		
		LibPub_NBytesBCDSub(  &V_ucaBuff_RemainMoney[0], &V_ucaBuff_Price[0], 6 );
	}
	else
	{
		LibPub_NBytesBCDSub(  &V_ucaBuff_Price[0], &V_ucaBuff_RemainMoney[0], 6 );
		LibPub_MemSetBytes( &V_ucaBuff_RemainMoney[0], 0x00, 6 );
		LibPub_NBtyesBcdAdd( &V_ucaBuff_TickMoney[0], &V_ucaBuff_Price[0], 6 );
	}
	/*------------------------------------------------------------------------------------------------------*/		
	/* 更新剩余金额和透支金额 */
	LibPub_MemCopyBytes( &V_ucaBuff_RemainMoney[0], &GStr_Money.ucaRemainMoney[0],  6 );	// 更新剩余金额 
	LibPub_MemCopyBytes( &V_ucaBuff_TickMoney[0], &GStr_Money.ucaTickMoney[0],  6 ); 		// 更新透支金额
	
	GStr_Money.usCRC16 = LibPub_CRC16_CCITT ( &GStr_Money.ucaRemainMoney[0], GStr_MONEY_Type_LEN-2 );	// 算一下CRC
	
	/*------------------------------------------------------------------------------------------------------*/		
	/* 判断剩余金额是否需要存储E2--如果整度进位，就做一下存储E2的处理  */
	if( GStr_Flag.ucMoney & F_SYS_MONEY_Money2E2 )
	{
		GStr_Flag.ucMoney &= ~F_SYS_MONEY_Money2E2;
		#if(METER_TYPE!=METER_TYPE_DTSY666)
		LibPub_WriteDataToE2prom(LIB_E2P_Money, 0, &GStr_Money.ucaRemainMoney[0]);
		#else
		if(_FAILED==LibPub_WriteDataToE2prom(LIB_E2P_Money, 0, &GStr_Money.ucaRemainMoney[0]))
		{
			LibPub_WriteDataToE2prom(LIB_E2P_Money, 0, &GStr_Money.ucaRemainMoney[0]);
		}
		#endif
	}
	
} 
///*--------------------------------- 注释详解区 ---------------------------------------------------------*///

///* 注释1:  剩余金额按6个字节，结构为XXXXXX.XXxxxx,最后4位为消费尾数，电价按4字节，格式为XXXX.XXXX元，因为是0.01kWh
///* 扣减一次，所以每一次扣减都是电价的1%例如：剩余金额为123.15元（存储表示为0x00012315），电
///* 价为0.4元/kWh（存储表示为0x00004000）因为扣钱是扣0.01kWh对应的电价，为了方便做减法，将剩余金额
///* 扩大10000倍来做减法， 这样剩余金额为0x000123150000,电价为0x00004000,做减法如下：
///*  0x000123150000
///* -0x000000004000
///* =0x000123146000
///* 以上数据都是BCD码

///* 注释2:  

///*------------------------------------------------------------------------------------------------------*///
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    校验剩余金额
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
// void ApiMoney_RemainMoneyCheck(void)
// {
// 	
// }
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    校验电价
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void ApiMoney_RefreshPrice(void)
{
	if(_TRUE != LibPub_CrcCheck( &GStr_PRICE.ucaPrice[0], GStr_PRICE_Type_LEN-2, GStr_PRICE.usCRC16) )
	{
		if ( _FAILED == LibPub_ReadDataFromE2prom(LIB_E2P_Price, 0, &GStr_PRICE.ucaPrice[0]) )
		{
			LibPub_MemSetBytes( &GStr_PRICE.ucaPrice[0], 0x00, 12 ) ;
			GStr_PRICE.ucaPrice[2]=0x50;///电价默认为0.5
			LibPub_WriteDataToE2prom(LIB_E2P_Price, 0, &GStr_PRICE.ucaPrice[0]);
		}
	}
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    2min定时保存剩余金额、透支金额
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void ApiMoney_TimeingHoldMoney(void)
{
	uchar8 V_ucTemp,V_usCRC16;
	uchar8 V_MoneyDataCRC[14];
	
	GStr_Counter.ucHoldMoney_Cnt++;
	if(GStr_Counter.ucHoldMoney_Cnt>=8)
	{
		GStr_Counter.ucHoldMoney_Cnt=0;
	}
	if(0==GStr_Counter.ucHoldMoney_Cnt%2)
	{
		V_ucTemp=GStr_Counter.ucHoldMoney_Cnt/2;
		V_usCRC16 = LibPub_CRC16_CCITT(&GStr_Money.ucaRemainMoney[0], 12);
		LibPub_MemCopyBytes( &GStr_Money.ucaRemainMoney[0], &V_MoneyDataCRC[0],  12 );
		V_MoneyDataCRC[12] = (uchar8)(V_usCRC16>>8);
		V_MoneyDataCRC[13] = (uchar8)(V_usCRC16 &0x00ff); 
		///剩余金额透支金额写EE
		DrvE2p_WriteData((LIB_E2P_HoldFirstMoney_Addr+V_ucTemp*14), &V_MoneyDataCRC[0],14);///带CRC写Ee
		
//		V_usCRC16 = LibPub_CRC16_CCITT(&GStr_Money.ucaTickMoney[0], 6);
//		LibPub_MemCopyBytes( &GStr_Money.ucaTickMoney[0], &V_MoneyDataCRC[0],  6 );
//		V_MoneyDataCRC[6] = (uchar8)(V_usCRC16>>8);
//		V_MoneyDataCRC[7] = (uchar8)(V_usCRC16 &0x00ff); 
//		DrvE2p_WriteData((LIB_E2P_HoldFirstTickMoney_Addr+V_ucTemp*6),&V_MoneyDataCRC[0],8);///带CRC写EE
	}
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    PT*CT*电价
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/

#if(METER_TYPE==METER_TYPE_DTSY666)///三相表要乘以PTCT，单相表PTCT强制为1.电价不作处理
void ApiMoney_MultPTCT(ulong32 *sourceptr,ulong32 *resultptr)
{  
	///**PT*CT*///
	ulong32  V_ulBuff[2];
	V_ulBuff[0] = LibPub_DECtoHEXBytes(&GStr_MeterIFO.ucVoltageTrans[0],3);  ///*PT由BCD转成Hex*///
	V_ulBuff[1] = LibPub_DECtoHEXBytes(&GStr_MeterIFO.ucCurrentTrans[0],3);  ///*CT由BCD转成Hex*///
			
	(*resultptr) = (*sourceptr)*(V_ulBuff[0])*(V_ulBuff[1]); ///* 电价*CT*PT */// 
}
#endif
