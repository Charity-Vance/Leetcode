/*******************************************************************************************************
**** Copyright��  (c)Copyright 2019,�㽭��̩�����Ǳ��������ι�˾,���ܱ�Ӧ���з�                       
****                            All rights reserved.                                                 
**** FileName:    IICDrv.c                                                                          
**** Brief:       IIC������������                                                                     
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
 *  ���ļ����к�����ǰ׺Ϊxxxx_
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
#if( METER_TYPE == METER_TYPE_DDSY666 )
	#define	 I2C_SCL_OUT()		    GPIO_IOCFG_P8_DIR_O( 7)
	#define	 I2C_SCL_IN()		    GPIO_IOCFG_P8_DIR_I( 7)  /// SCL ����Ϊ�������
	#define	 I2C_SCL_HIGHT()	    GPIO_IOCFG_P8_SET_1( 7)  ///����SCL�����Ϊ1
	#define	 I2C_SCL_LOW()		    GPIO_IOCFG_P8_SET_0( 7)  ///����SCL�����Ϊ0

	#define	 I2C_SDA_OUT()	        GPIO_IOCFG_P8_DIR_O( 6)
	#define	 I2C_SDA_IN()	        GPIO_IOCFG_P8_DIR_I( 6)  /// SDA����Ϊ�������
	#define	 I2C_SDA_HIGHT()	    GPIO_IOCFG_P8_SET_1( 6)  ///����SDA�����Ϊ1
	#define	 I2C_SDA_LOW()		    GPIO_IOCFG_P8_SET_0( 6)  ///����SDA�����Ϊ0
	#define	 I2C_SDA_Status_HIGHT	GPIO_IOCFG_P8_STAT_H(6)  //��ȡSDA��״̬Ϊ1	
	#define	 I2C_SDA_Status_LOW		GPIO_IOCFG_P8_STAT_H(6)  //��ȡSDA��״̬Ϊ0

	#define	 I2C_WP_OUT()	        GPIO_IOCFG_P9_DIR_O( 0)  ///WP����Ϊ���	
	#define	 I2C_WP_LOW()	        GPIO_IOCFG_P9_SET_0( 0)  ///WP����Ϊ0
#endif

#if( METER_TYPE == METER_TYPE_DTSY666 )
	#define	 I2C_SCL_OUT()		    GPIO_IOCFG_P8_DIR_O( 7)
	#define	 I2C_SCL_IN()		    GPIO_IOCFG_P8_DIR_I( 7)  /// SCL ����Ϊ�������
	#define	 I2C_SCL_HIGHT()	    GPIO_IOCFG_P8_SET_1( 7)  ///����SCL�����Ϊ1
	#define	 I2C_SCL_LOW()		    GPIO_IOCFG_P8_SET_0( 7)  ///����SCL�����Ϊ0

	#define	 I2C_SDA_OUT()	        GPIO_IOCFG_P8_DIR_O( 6)
	#define	 I2C_SDA_IN()	        GPIO_IOCFG_P8_DIR_I( 6)  /// SDA����Ϊ�������
	#define	 I2C_SDA_HIGHT()	    GPIO_IOCFG_P8_SET_1( 6)  ///����SDA�����Ϊ1
	#define	 I2C_SDA_LOW()		    GPIO_IOCFG_P8_SET_0( 6)  ///����SDA�����Ϊ0
	#define	 I2C_SDA_Status_HIGHT	GPIO_IOCFG_P8_STAT_H(6)  //��ȡSDA��״̬Ϊ1	
	#define	 I2C_SDA_Status_LOW		GPIO_IOCFG_P8_STAT_H(6)  //��ȡSDA��״̬Ϊ0

	#define	 I2C_WP_OUT()	        GPIO_IOCFG_P9_DIR_O( 0)  ///WP����Ϊ���	
	#define	 I2C_WP_LOW()	        GPIO_IOCFG_P9_SET_0( 0)  ///WP����Ϊ0
#endif

#if( METER_TYPE == METER_TYPE_DDSYU666 )
	#define	 I2C_SCL_OUT()		    GPIO_IOCFG_P3_DIR_O( 3)
	#define	 I2C_SCL_IN()		    GPIO_IOCFG_P3_DIR_I( 3)  /// SCL ����Ϊ�������
	#define	 I2C_SCL_HIGHT()	    GPIO_IOCFG_P3_SET_1( 3)  ///����SCL�����Ϊ1
	#define	 I2C_SCL_LOW()		    GPIO_IOCFG_P3_SET_0( 3)  ///����SCL�����Ϊ0

	#define	 I2C_SDA_OUT()	        GPIO_IOCFG_P3_DIR_O( 4)
	#define	 I2C_SDA_IN()	        GPIO_IOCFG_P3_DIR_I( 4)  /// SDA����Ϊ�������
	#define	 I2C_SDA_HIGHT()	    GPIO_IOCFG_P3_SET_1( 4)  ///����SDA�����Ϊ1
	#define	 I2C_SDA_LOW()		    GPIO_IOCFG_P3_SET_0( 4)  ///����SDA�����Ϊ0
	#define	 I2C_SDA_Status_HIGHT	GPIO_IOCFG_P3_STAT_H(4)  //��ȡSDA��״̬Ϊ1	
	#define	 I2C_SDA_Status_LOW		GPIO_IOCFG_P3_STAT_H(4)  //��ȡSDA��״̬Ϊ0

	#define	 I2C_WP_OUT()	        NOP()//GPIO_IOCFG_P9_DIR_O( 0)  ///WP����Ϊ���	
	#define	 I2C_WP_LOW()	        NOP()//GPIO_IOCFG_P9_SET_0( 0)  ///WP����Ϊ0

#endif

#define	DRV_E2P_DEV_ADDR_WRITE	0xa0
#define	DRV_E2P_DEV_ADDR_READ	0xa1
#define DRV_E2P_DEV_ADDR_WRPAGE1	0xa2
#define DRV_E2P_Max_Page_LEN     8
#define DRV_E2P_Max_Data_LEN     32

/*----------------< �������� >----------------------------------*/


/*----------------< �������� >----------------------------------*/
#pragma SAVE
#pragma OT(0)
/*----------------< �������� >----------------------------------*/
uchar8 DrvE2p_ReadData(ushort16 v_usAddress, uchar8 *p_ucDatabuf, uchar8 v_ucLen);
uchar8 DrvE2p_WriteData(ushort16 v_usAddress, uchar8 *p_ucDatabuf, uchar8 v_ucLen);


/*----------------< �������� >----------------------------------*/
static void DrvE2p_I2CStart(void);
static void DrvE2p_I2CStop(void);
static uchar8 DrvE2p_ReadOneByteAck(void);
static uchar8 DrvE2p_ReadOneByteNoAck(void);
static uchar8 DrvE2p_WriteOneByte(uchar8 v_ucData);
static void DrvE2p_I2CDelay_5us(void);
static void DrvE2p_I2CDelay_2us(void);
static void DrvE2p_I2CDelay_3us(void);
static uchar8 DrvE2p_WRDataTemp(ushort16 v_usAddress, uchar8 *p_ucDatabuf, uchar8 v_ucLen);
static void DrvE2p_ChkBusBusy(void);

static void DrvE2p_I2CDelay_5us(void)
{
	uchar8 i = 1;
	while(i--)
	{
	}
}

static void DrvE2p_I2CDelay_3us(void)
{
	uchar8 i = 1;
//	while(i--)
//	{
//		
//	}	
	
}

static void DrvE2p_I2CDelay_2us(void)
{
	return;
}



void DrvI2C_Init( void )
{
	P8SS &= ( ~P8SS_P8S7 )|( ~P8SS_P8S6 );//P8.6,P8.7ΪIO��  SCL  SDA
	P9SS &= ( ~P9SS_P9S0 );//P9.0ΪIO  Wp
    I2C_WP_OUT();
	I2C_WP_LOW();
}
///**********************************************************************///
///* Brief:  ��ѯ�����Ƿ�æ                  		                    *///
///*                                                                    *///
///* Return: ��                                                         *///
///*                                                                    *///
///* Note:                                                              *///
///**********************************************************************///
void DrvE2p_ChkBusBusy(void)
{
	uchar8 v_ucCnt;
	uchar8 v_ucCst = 255;																		///* ��ֵ������ *///
	
	for (v_ucCnt = 0;v_ucCnt < v_ucCst; v_ucCnt++)
	{
		DrvE2p_I2CStart();
		if	(DrvE2p_WriteOneByte(DRV_E2P_DEV_ADDR_WRITE) == _SUCCESS)	
		{
				DrvE2p_I2CStop();
				break;	
		}		///* �豸��ַ(д),�ж������Ƿ���� *///
	}
}

///**********************************************************************///
///* Brief:  I2C���߼���                  		                        *///
///*                                                                    *///
///* Return: ��                                                         *///
///*                                                                    *///
///* Note:                                                              *///
///**********************************************************************///
static void DrvE2p_I2CStart(void)
{
	DrvI2C_Init();
	
	I2C_SDA_OUT();
	I2C_SDA_HIGHT();
	I2C_SCL_OUT();
	I2C_SCL_HIGHT();
	DrvE2p_I2CDelay_5us();
	I2C_SDA_LOW();
	DrvE2p_I2CDelay_5us();	///* ��ʱ����4us *///
	I2C_SCL_LOW();
}
///**********************************************************************///
///* Brief:  I2C����ֹͣ                  		                        *///
///*                                                                    *///
///* Return: ��                                                         *///
///*                                                                    *///
///* Note:                                                              *///
///**********************************************************************///
static void DrvE2p_I2CStop(void)
{
	uchar8 V_Couter = 0;
	
	I2C_SDA_IN();
	
	for (V_Couter=20 ;V_Couter > 0; V_Couter--)
	{

		if (I2C_SDA_Status_HIGHT)
		{
			break;
		}
		I2C_SCL_HIGHT();
		DrvE2p_I2CDelay_5us();
	    I2C_SCL_LOW();
	}
	I2C_SDA_OUT();
	I2C_SCL_OUT();
	I2C_SDA_LOW();
	I2C_SCL_LOW();
	DrvE2p_I2CDelay_5us();	///* ��ʱ����4us *///
    I2C_SCL_HIGHT();
	DrvE2p_I2CDelay_5us();	///* ��ʱ����4us *///
	I2C_SDA_HIGHT();
}

///**********************************************************************///
///* Brief:  ��1�ֽڴ�Ack                  		                        *///
///*                                                                    *///
///* Return: ���ض�����ֵ                                               *///
///*                                                                    *///
///* Note:                                                              *///
///**********************************************************************///
static uchar8 DrvE2p_ReadOneByteAck(void)
{
	volatile uchar8 V_ucResult = 0;
	uchar8 V_ucCnt_i = 8;
	
	I2C_SCL_OUT();
	I2C_SDA_IN();
	I2C_SCL_LOW();
	
	for (V_ucCnt_i = 0; V_ucCnt_i < 8; V_ucCnt_i++)		///* ��8λ���� *///
	{
		DrvE2p_I2CDelay_3us();
		V_ucResult = V_ucResult << 1;
		I2C_SCL_HIGHT();
		if (I2C_SDA_Status_HIGHT)
		{
			V_ucResult = V_ucResult|0x01;
		}
		DrvE2p_I2CDelay_3us();
		V_ucResult = V_ucResult;
		I2C_SCL_LOW();
	}
	
	I2C_SDA_OUT();
	I2C_SDA_LOW();
	I2C_SCL_HIGHT();
	DrvE2p_I2CDelay_5us();	///* ��ʱ����4us *///
	I2C_SCL_LOW();
	I2C_SDA_HIGHT();
	
	return V_ucResult;
}
///**********************************************************************///
///* Brief:  ��1�ֽڴ���Ack               		                        *///
///*                                                                    *///
///* Return: ���ض�����ֵ                                               *///
///*                                                                    *///
///* Note:                                                              *///
///**********************************************************************///
static uchar8 DrvE2p_ReadOneByteNoAck(void)
{
	uchar8 V_ucResult = 0;
	uchar8 V_ucCnt_i = 0;
	
	I2C_SCL_OUT();
	I2C_SDA_IN();
	I2C_SCL_LOW();
	
	for ( V_ucCnt_i = 0; V_ucCnt_i < 8; V_ucCnt_i++)		///* ��8λ���� *///
	{
		DrvE2p_I2CDelay_3us();
		V_ucResult = V_ucResult << 1;
		I2C_SCL_HIGHT();
		
		if (I2C_SDA_Status_HIGHT)
		{
			V_ucResult = V_ucResult|0x01;
		}
		DrvE2p_I2CDelay_3us();
		I2C_SCL_LOW();
	}
	I2C_SDA_OUT();
	I2C_SDA_HIGHT();
	I2C_SCL_HIGHT();
	DrvE2p_I2CDelay_5us();	///* ��ʱ����4us *///
	I2C_SCL_LOW();
	
	return V_ucResult;	
}
///**********************************************************************///
///* Brief:  ��E2д1�ֽ�����               		                        *///
///*                                                                    *///
///* Param:  v_data����Ҫд������                                       *///
///*                                                                    *///
///* Return:                                                            *///
///* Note:                                                              *///
///**********************************************************************///
static uchar8 DrvE2p_WriteOneByte(uchar8 v_ucData)
{
	uchar8 V_ucOprResult = _SUCCESS;
	uchar8 V_ucCnt_i = 0;	
	
	I2C_SCL_OUT();
	I2C_SCL_LOW();
	I2C_SDA_OUT();
	
	for (V_ucCnt_i = 0; V_ucCnt_i < 8; V_ucCnt_i++)			///* д8λ���� *///
	{
		if (v_ucData & 0x80)		
		{
			I2C_SDA_HIGHT();
		}
		else			
		{
			I2C_SDA_LOW();
		}
		
		I2C_SCL_HIGHT();
		v_ucData = v_ucData << 1;
		DrvE2p_I2CDelay_3us();
		I2C_SCL_LOW();
	}
	DrvE2p_I2CDelay_2us();
	I2C_SDA_IN();
	I2C_SCL_HIGHT();
	
	DrvE2p_I2CDelay_2us();						///* ��ʱ����4us *///
	
	if (I2C_SDA_Status_HIGHT) 	///* ���ACK *///
	{ 
		V_ucOprResult = _FAILED;
	}
	I2C_SCL_LOW();
	return V_ucOprResult; 
}
///**********************************************************************///
///* Brief:  ��E2дlen�ֽ�����               		                    *///
///*                                                                    *///
///* Param:  v_address��E2��ַ                                          *///
///* Param:  p_databuf��������ָ��                                      *///
///* Param:  v_len�����ݳ���                                            *///
///*                                                                    *///
///* Return: _SUCCESS:д�ɹ���FAILED��дʧ��                            *///
///*                                                                    *///
///* Note:��ʱ���� ���ܿ�ҳ                                             *///
///**********************************************************************///
uchar8 DrvE2p_WRDataTemp(ushort16 v_usAddress, uchar8 *p_ucDatabuf, uchar8 v_ucLen)
{
	ushort16 i;
	uchar8 *j;
	uchar8 Temp= 0;
	
	if ( (v_ucLen == 0) || (v_ucLen > DRV_E2P_Max_Data_LEN) )					///* �г����Ƿ�Ϸ� *///
	{	
		return _FAILED;
	}
	if ( v_usAddress > 0x01ff )					
	{
		return _FAILED;
	}
	if ( ( (v_usAddress + v_ucLen) <= 0x00ff) || (v_usAddress > 0x00ff) )	///* ��д�����Ƿ��ҳ *///
	{
		DrvE2p_I2CStart();
		
		if	((v_usAddress + v_ucLen) <= 0x00ff) { Temp = DRV_E2P_DEV_ADDR_WRITE; }		///* д�ڵ�1��ҳ *///
		if	(v_usAddress > 0x00ff) 			   { Temp = DRV_E2P_DEV_ADDR_WRPAGE1; }		///* д�ڵ�2��ҳ *///
		
		if	(DrvE2p_WriteOneByte(Temp) != _SUCCESS)										///* �豸��ַ(д) *///
		{
			DrvE2p_I2CStop();return _FAILED;
		}
		
		if  (DrvE2p_WriteOneByte( (uchar8) (v_usAddress) ) != _SUCCESS)					///* ���ݵ�ַLSB *///
		{
			DrvE2p_I2CStop();return _FAILED; 
		}
		j = p_ucDatabuf;
		for (i = 0; i < v_ucLen; i++)													///* д���� *///
		{
			if (DrvE2p_WriteOneByte(*j) != _SUCCESS)
			{
				DrvE2p_I2CStop();
				return _FAILED; 
			}
			j++;
		}
		DrvE2p_I2CStop(); 
		DrvE2p_ChkBusBusy();
	}
	
	else									///* ���ҳд���ɹ� *///
	{
		return _FAILED;
	}
	
	return _SUCCESS;
}
///**********************************************************************///
///* Brief:  ��E2дlen�ֽ�����               		                    *///
///*                                                                    *///
///* Param:  v_address��E2��ַ                                          *///
///* Param:  p_databuf��������ָ��                                      *///
///* Param:  v_len�����ݳ���                                            *///
///*                                                                    *///
///* Return: _SUCCESS:д�ɹ���FAILED��дʧ��                            *///
///*                                                                    *///
///* Note:ÿҳ���д8�ֽ�     ��֧�ֿ��ҳд����                                         *///
///**********************************************************************///
uchar8 DrvE2p_WriteData(ushort16 v_usAddress, uchar8 *p_ucDatabuf, uchar8 v_ucLen)
{
// 	uchar8 V_ucFstPageLen;		///* ��һҳҪд���ֽ��� *///
// 	uchar8 V_ucTemp1,i,V_ucTemp2;
	
	ushort16 V_usEEAdr;
	uchar8  V_ucDataLen,V_ucCnti;
	
	V_usEEAdr = v_usAddress;	
	V_ucDataLen = DRV_E2P_Max_Page_LEN - (v_usAddress & 0x0007);	/* �����һ��Ҫд�����ݳ��ȣ���һ��д��������������ַ */	
	V_ucCnti = 0; 
	if( v_ucLen < V_ucDataLen )
	{
		V_ucDataLen = v_ucLen;
	}
	
	do
	{
		if( _FAILED == DrvE2p_WRDataTemp(V_usEEAdr, p_ucDatabuf+V_ucCnti, V_ucDataLen) )
		{
			return _FAILED;
		}
		
		V_ucCnti = V_ucCnti + V_ucDataLen;			// ��һ��ƫ���������ݸ������ƫ������
		V_usEEAdr = v_usAddress + V_ucCnti;			// ���¼���һ����һ��Ҫд�ĵ�ַ		
		V_ucDataLen = v_ucLen - V_ucCnti;			// ������һ����һ��Ҫд�ĳ���
		if( V_ucDataLen > DRV_E2P_Max_Page_LEN )	// ������ȴ���8���Ͱ�8�ֽڣ����С�ڣ�д������Ժ�ͽ�����
		{
			V_ucDataLen = DRV_E2P_Max_Page_LEN;
		}
		
	}while( V_ucDataLen );
	
	
// 	
//     
// 	V_ucTemp1 = ( (uchar8) (v_usAddress & 0x0007) + v_ucLen) / (DRV_E2P_Max_Page_LEN);	// ÿҳ8��,����һ����Ҫ����ҳ
// 	V_ucTemp2 = ( (uchar8) (v_usAddress & 0x000f) + v_ucLen) % (DRV_E2P_Max_Page_LEN);	// ÿҳ8��֮��ʣ�µ��ֽ���
// 	
// 	if( V_ucTemp2 )	// ʣ����ֽ�����Ϊ0  Ҫ��дһҳ
// 	{
// 		V_ucTemp1 += 1;
// 	}
// 	
// 	if ( V_ucTemp1 == 1 )																	///* ֻдһҳ������ҳ *///
// 	{
// 		if( _FAILED == DrvE2p_WRDataTemp(v_usAddress, p_ucDatabuf, v_ucLen) )
// 		{
// 			return _FAILED;
// 		}
// 	}
// 	else
// 	{
// 		V_ucFstPageLen = (uchar8)(0x0008 - (v_usAddress & 0x0007)) ;
// 		if(_FAILED==DrvE2p_WRDataTemp(v_usAddress, p_ucDatabuf, V_ucFstPageLen))
// 		{
// 			return _FAILED;
// 		}
// 			
// 		for( i=1; i<(V_ucTemp1-1);i++ )
// 		{
// 			
// 			if(_FAILED==DrvE2p_WRDataTemp((v_usAddress & 0xfff0)+(DRV_E2P_Max_Page_LEN*i), p_ucDatabuf+V_ucFstPageLen+DRV_E2P_Max_Page_LEN*(i-1), DRV_E2P_Max_Page_LEN))
// 			{
// 				return _FAILED;
// 			}
// 		}
// 		
// 		if(i==(V_ucTemp1-1))
// 		{
// 			if(_FAILED==DrvE2p_WRDataTemp((v_usAddress & 0xfff0)+(DRV_E2P_Max_Page_LEN*i), p_ucDatabuf+V_ucFstPageLen+DRV_E2P_Max_Page_LEN*(i-1), v_ucLen-V_ucFstPageLen-DRV_E2P_Max_Page_LEN*(i-1)))
// 			{
// 				return _FAILED;
// 			}
// 		}
// 			
// 	}
	return _SUCCESS;
}
///**********************************************************************///
///* Brief:  ��E2��len�ֽ�����               		                    *///
///*                                                                    *///
///* Return: _SUCCESS:���ɹ���FAILED����ʧ��                            *///
///*                                                                    *///
///* Note:   ��ʧ�ܲ�����                                               *///
///**********************************************************************///
uchar8 DrvE2p_ReadData(ushort16 v_usAddress, uchar8 *p_ucDatabuf, uchar8 v_ucLen)
{
	uchar8 V_ucOprResult = _SUCCESS;
	uchar8 V_ucCnt;
	uchar8 *P_ucTempData;
	
	if (v_ucLen == 0)					///* �г����Ƿ�Ϸ� *///
	{
		return _FAILED;
	}
	
	if ( ( v_usAddress + v_ucLen ) > 0x01ff )	///* ���ܳ����Ƿ񳬳� *///
	{	
		return _FAILED;
	}
	
	V_ucCnt = (v_usAddress >> 8) & 0x00ff;
	
	V_ucCnt = V_ucCnt << 1;
	
	DrvE2p_I2CStart();
	
	if (DrvE2p_WriteOneByte( DRV_E2P_DEV_ADDR_WRITE + V_ucCnt ) != _SUCCESS)			///* �豸��ַ��д�� *///
	{  DrvE2p_I2CStop(); return _FAILED; }
	
	
	if (DrvE2p_WriteOneByte( (uchar8) (v_usAddress) )!= _SUCCESS)			///* д���ݵ�ַLSB *///
	{  DrvE2p_I2CStop(); return _FAILED; }
	
	DrvE2p_I2CStart();		///* ����I2C *///
	
	if (DrvE2p_WriteOneByte(DRV_E2P_DEV_ADDR_READ + V_ucCnt) != _SUCCESS)				///* �豸��ַ������ *///
	{  DrvE2p_I2CStop(); return _FAILED; }
	
	P_ucTempData = p_ucDatabuf;
	
	for (V_ucCnt = 0; V_ucCnt < (v_ucLen-1); V_ucCnt++)						///* ������ *///
	{
		P_ucTempData[V_ucCnt] = DrvE2p_ReadOneByteAck(); 
	}
	P_ucTempData[V_ucCnt]  = DrvE2p_ReadOneByteNoAck();							///* �������һ�ֽڻ�NoAck *///
	
	DrvE2p_I2CStop();
	
	return V_ucOprResult;
}
#pragma RESTORE
