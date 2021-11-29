/*******************************************************************************************************
**** Copyright��  (c)Copyright 2019,�㽭��̩�����Ǳ��������ι�˾,���ܱ�Ӧ���з�                       
****                            All rights reserved.                                                 
**** FileName:    AppMoney.c                                                                          
**** Brief:       �����ļ�                                                                      
**** Author:      peter.he@chint.com                                                                 
**** Version:     V1.0                                                                               
**** Date:        2016-7-14                                                                          
****                                                                                                 
**** note:�޸���ʷ��¼�б�ÿ���޸ļ�¼Ӧ�����޸����ڡ��޸���                                          
**** 1.  Author:                                                                                     
****     Version:                                                                                    
****     Date :                                                                                      
**** 2.  Author:                                                                                     
****     Version:                                                                                       
****     Date:
****                                                                                        
****  addtogroup:Library                                                             
**********************************************************************************************************/

/*--------------------------------- �ļ�����˵�� -------------------------------------------------------*/
/*
 *  ���ļ����к�����ǰ׺Ϊ ApiMoney_
 *  �ļ��������Ͷ��⺯��������ļ����ײ���������������Ҫ���ڵ�һ��λ��;
 *  ����ע�Ͳ��ñ�׼ģ�壬�����ڲ�ע�Ͳ���//;
 *  ����ע�ͽ϶�Ĳ��֣���������һ��ע�ͷ���Ȼ����ϸ˵�������ļ���β��;
 *--------------------------------- �ļ�����˵�� -------------------------------------------------------*/
 
/**���βεĺ�����ʽ:*/
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    xx��������
 *
 *  @param    xx :
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
/**���βεĺ�����ʽ:*/
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    �ϵ����п������óɳ�ʼ״̬������ɸ�����Ҫ����������
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
 
 
/*----------------< �����ļ� >----------------------------------*/
#include "..\SourceFiles\PUB\Include.h"

/*----------------< �궨���� >----------------------------------*/


/*----------------< �������� >----------------------------------*/


/*----------------< �������� >----------------------------------*/


/*----------------< �������� >----------------------------------*/
void ApiMoney_RemainMoneyProcess(void);
// void ApiMoney_RemainMoneyCheck(void); 
void ApiMoney_RefreshPrice(void);
void ApiMoney_TimeingHoldMoney(void);
static void ApiMoney_MultPTCT(ulong32 *sourceptr,ulong32 *resultptr);
/*----------------< �������� >----------------------------------*/

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ʣ���������������ۼ������ۼ�ÿ0.01kWh�ۼ�һ��
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
	#if(METER_TYPE==METER_TYPE_DTSY666)///�����Ҫ����PTCT�������PTCTǿ��Ϊ1.��۲�������
	ulong32 V_ulBuff[2];
	#endif
	/*------------------------------------------------------------------------------------------------------*/	
	/* ���ж�һ���Ƿ��пۼ���־��û�о�ֱ���˳� */
	if( F_SYS_MONEY_MoneyDEC != (GStr_Flag.ucMoney & F_SYS_MONEY_MoneyDEC) )
	{
		return;
	}
	GStr_Flag.ucMoney &= ~ F_SYS_MONEY_MoneyDEC;
	
	/*------------------------------------------------------------------------------------------------------*/	
	/* У��һ��ʣ���� */
	ApiPwOn_MoneyParaCheck();
	LibPub_MemCopyBytes( &GStr_Money.ucaRemainMoney[0],  &V_ucaBuff_RemainMoney[0], 6 ); 	// ����ʣ���� 
	LibPub_MemCopyBytes( &GStr_Money.ucaTickMoney[0],  &V_ucaBuff_TickMoney[0], 6 );		// ����͸֧���
	
	/*------------------------------------------------------------------------------------------------------*/		
	/* ��ȡһ�¿ۼ����ۣ�����=PT*CT*��ۣ�����Ҫ��ˢ��һ�µ�� */
	ApiMoney_RefreshPrice();
	#if(METER_TYPE==METER_TYPE_DTSY666)///�����Ҫ����PTCT�������PTCTǿ��Ϊ1.��۲�������
//	V_ulBuff[0]=LibPub_Buffer4ToUlong32(&GStr_PRICE.ucaPrice[0]);
	V_ulBuff[0]=LibPub_DECtoHEXBytes(&GStr_PRICE.ucaPrice[0],4);///���תulong32  HEX
	ApiMoney_MultPTCT(&V_ulBuff[0],&V_ulBuff[1]);///���*PT*CT//��ʵ���ѵ��
	LibPub_HEXtoBCDBytes(V_ulBuff[1],&V_ucaBuff_Price[2],4);///��ʵ���ѵ�ۣ�ת��BCD
	#else
	LibPub_MemCopyBytes( &GStr_PRICE.ucaPrice[0],  &V_ucaBuff_Price[2], 4 );
	#endif
	V_ucaBuff_Price[0] = 0;
	V_ucaBuff_Price[1] = 0;

	
	/*------------------------------------------------------------------------------------------------------*/		
	/* �ж�ʣ����Ϳۼ����۵Ĵ�С��ϵ�����н��ۼ� */
	if( C_LessThan != LibPub_CompareData( &GStr_Money.ucaRemainMoney[0], &V_ucaBuff_Price[0], 6, CMP_MODE_HIGHT ) )
	{
		if( C_Equal == LibPub_CompareData( &GStr_Money.ucaRemainMoney[0], &V_ucaBuff_Price[0], 6, CMP_MODE_HIGHT ) )
		{
			// �����ȣ����һ��E2
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
	/* ����ʣ�����͸֧��� */
	LibPub_MemCopyBytes( &V_ucaBuff_RemainMoney[0], &GStr_Money.ucaRemainMoney[0],  6 );	// ����ʣ���� 
	LibPub_MemCopyBytes( &V_ucaBuff_TickMoney[0], &GStr_Money.ucaTickMoney[0],  6 ); 		// ����͸֧���
	
	GStr_Money.usCRC16 = LibPub_CRC16_CCITT ( &GStr_Money.ucaRemainMoney[0], GStr_MONEY_Type_LEN-2 );	// ��һ��CRC
	
	/*------------------------------------------------------------------------------------------------------*/		
	/* �ж�ʣ�����Ƿ���Ҫ�洢E2--������Ƚ�λ������һ�´洢E2�Ĵ���  */
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
///*--------------------------------- ע������� ---------------------------------------------------------*///

///* ע��1:  ʣ���6���ֽڣ��ṹΪXXXXXX.XXxxxx,���4λΪ����β������۰�4�ֽڣ���ʽΪXXXX.XXXXԪ����Ϊ��0.01kWh
///* �ۼ�һ�Σ�����ÿһ�οۼ����ǵ�۵�1%���磺ʣ����Ϊ123.15Ԫ���洢��ʾΪ0x00012315������
///* ��Ϊ0.4Ԫ/kWh���洢��ʾΪ0x00004000����Ϊ��Ǯ�ǿ�0.01kWh��Ӧ�ĵ�ۣ�Ϊ�˷�������������ʣ����
///* ����10000������������ ����ʣ����Ϊ0x000123150000,���Ϊ0x00004000,���������£�
///*  0x000123150000
///* -0x000000004000
///* =0x000123146000
///* �������ݶ���BCD��

///* ע��2:  

///*------------------------------------------------------------------------------------------------------*///
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    У��ʣ����
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
 *  @brief    У����
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
			GStr_PRICE.ucaPrice[2]=0x50;///���Ĭ��Ϊ0.5
			LibPub_WriteDataToE2prom(LIB_E2P_Price, 0, &GStr_PRICE.ucaPrice[0]);
		}
	}
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    2min��ʱ����ʣ���͸֧���
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
		///ʣ����͸֧���дEE
		DrvE2p_WriteData((LIB_E2P_HoldFirstMoney_Addr+V_ucTemp*14), &V_MoneyDataCRC[0],14);///��CRCдEe
		
//		V_usCRC16 = LibPub_CRC16_CCITT(&GStr_Money.ucaTickMoney[0], 6);
//		LibPub_MemCopyBytes( &GStr_Money.ucaTickMoney[0], &V_MoneyDataCRC[0],  6 );
//		V_MoneyDataCRC[6] = (uchar8)(V_usCRC16>>8);
//		V_MoneyDataCRC[7] = (uchar8)(V_usCRC16 &0x00ff); 
//		DrvE2p_WriteData((LIB_E2P_HoldFirstTickMoney_Addr+V_ucTemp*6),&V_MoneyDataCRC[0],8);///��CRCдEE
	}
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    PT*CT*���
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/

#if(METER_TYPE==METER_TYPE_DTSY666)///�����Ҫ����PTCT�������PTCTǿ��Ϊ1.��۲�������
void ApiMoney_MultPTCT(ulong32 *sourceptr,ulong32 *resultptr)
{  
	///**PT*CT*///
	ulong32  V_ulBuff[2];
	V_ulBuff[0] = LibPub_DECtoHEXBytes(&GStr_MeterIFO.ucVoltageTrans[0],3);  ///*PT��BCDת��Hex*///
	V_ulBuff[1] = LibPub_DECtoHEXBytes(&GStr_MeterIFO.ucCurrentTrans[0],3);  ///*CT��BCDת��Hex*///
			
	(*resultptr) = (*sourceptr)*(V_ulBuff[0])*(V_ulBuff[1]); ///* ���*CT*PT */// 
}
#endif
