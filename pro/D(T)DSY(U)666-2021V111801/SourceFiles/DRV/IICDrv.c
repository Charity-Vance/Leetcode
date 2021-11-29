/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    IICDrv.c                                                                          
**** Brief:       IIC总线驱动函数                                                                     
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
#if( METER_TYPE == METER_TYPE_DDSY666 )
	#define	 I2C_SCL_OUT()		    GPIO_IOCFG_P8_DIR_O( 7)
	#define	 I2C_SCL_IN()		    GPIO_IOCFG_P8_DIR_I( 7)  /// SCL 设置为输入输出
	#define	 I2C_SCL_HIGHT()	    GPIO_IOCFG_P8_SET_1( 7)  ///设置SCL的输出为1
	#define	 I2C_SCL_LOW()		    GPIO_IOCFG_P8_SET_0( 7)  ///设置SCL的输出为0

	#define	 I2C_SDA_OUT()	        GPIO_IOCFG_P8_DIR_O( 6)
	#define	 I2C_SDA_IN()	        GPIO_IOCFG_P8_DIR_I( 6)  /// SDA设置为输入输出
	#define	 I2C_SDA_HIGHT()	    GPIO_IOCFG_P8_SET_1( 6)  ///设置SDA的输出为1
	#define	 I2C_SDA_LOW()		    GPIO_IOCFG_P8_SET_0( 6)  ///设置SDA的输出为0
	#define	 I2C_SDA_Status_HIGHT	GPIO_IOCFG_P8_STAT_H(6)  //读取SDA的状态为1	
	#define	 I2C_SDA_Status_LOW		GPIO_IOCFG_P8_STAT_H(6)  //读取SDA的状态为0

	#define	 I2C_WP_OUT()	        GPIO_IOCFG_P9_DIR_O( 0)  ///WP设置为输出	
	#define	 I2C_WP_LOW()	        GPIO_IOCFG_P9_SET_0( 0)  ///WP设置为0
#endif

#if( METER_TYPE == METER_TYPE_DTSY666 )
	#define	 I2C_SCL_OUT()		    GPIO_IOCFG_P8_DIR_O( 7)
	#define	 I2C_SCL_IN()		    GPIO_IOCFG_P8_DIR_I( 7)  /// SCL 设置为输入输出
	#define	 I2C_SCL_HIGHT()	    GPIO_IOCFG_P8_SET_1( 7)  ///设置SCL的输出为1
	#define	 I2C_SCL_LOW()		    GPIO_IOCFG_P8_SET_0( 7)  ///设置SCL的输出为0

	#define	 I2C_SDA_OUT()	        GPIO_IOCFG_P8_DIR_O( 6)
	#define	 I2C_SDA_IN()	        GPIO_IOCFG_P8_DIR_I( 6)  /// SDA设置为输入输出
	#define	 I2C_SDA_HIGHT()	    GPIO_IOCFG_P8_SET_1( 6)  ///设置SDA的输出为1
	#define	 I2C_SDA_LOW()		    GPIO_IOCFG_P8_SET_0( 6)  ///设置SDA的输出为0
	#define	 I2C_SDA_Status_HIGHT	GPIO_IOCFG_P8_STAT_H(6)  //读取SDA的状态为1	
	#define	 I2C_SDA_Status_LOW		GPIO_IOCFG_P8_STAT_H(6)  //读取SDA的状态为0

	#define	 I2C_WP_OUT()	        GPIO_IOCFG_P9_DIR_O( 0)  ///WP设置为输出	
	#define	 I2C_WP_LOW()	        GPIO_IOCFG_P9_SET_0( 0)  ///WP设置为0
#endif

#if( METER_TYPE == METER_TYPE_DDSYU666 )
	#define	 I2C_SCL_OUT()		    GPIO_IOCFG_P3_DIR_O( 3)
	#define	 I2C_SCL_IN()		    GPIO_IOCFG_P3_DIR_I( 3)  /// SCL 设置为输入输出
	#define	 I2C_SCL_HIGHT()	    GPIO_IOCFG_P3_SET_1( 3)  ///设置SCL的输出为1
	#define	 I2C_SCL_LOW()		    GPIO_IOCFG_P3_SET_0( 3)  ///设置SCL的输出为0

	#define	 I2C_SDA_OUT()	        GPIO_IOCFG_P3_DIR_O( 4)
	#define	 I2C_SDA_IN()	        GPIO_IOCFG_P3_DIR_I( 4)  /// SDA设置为输入输出
	#define	 I2C_SDA_HIGHT()	    GPIO_IOCFG_P3_SET_1( 4)  ///设置SDA的输出为1
	#define	 I2C_SDA_LOW()		    GPIO_IOCFG_P3_SET_0( 4)  ///设置SDA的输出为0
	#define	 I2C_SDA_Status_HIGHT	GPIO_IOCFG_P3_STAT_H(4)  //读取SDA的状态为1	
	#define	 I2C_SDA_Status_LOW		GPIO_IOCFG_P3_STAT_H(4)  //读取SDA的状态为0

	#define	 I2C_WP_OUT()	        NOP()//GPIO_IOCFG_P9_DIR_O( 0)  ///WP设置为输出	
	#define	 I2C_WP_LOW()	        NOP()//GPIO_IOCFG_P9_SET_0( 0)  ///WP设置为0

#endif

#define	DRV_E2P_DEV_ADDR_WRITE	0xa0
#define	DRV_E2P_DEV_ADDR_READ	0xa1
#define DRV_E2P_DEV_ADDR_WRPAGE1	0xa2
#define DRV_E2P_Max_Page_LEN     8
#define DRV_E2P_Max_Data_LEN     32

/*----------------< 常量定义 >----------------------------------*/


/*----------------< 变量定义 >----------------------------------*/
#pragma SAVE
#pragma OT(0)
/*----------------< 函数声明 >----------------------------------*/
uchar8 DrvE2p_ReadData(ushort16 v_usAddress, uchar8 *p_ucDatabuf, uchar8 v_ucLen);
uchar8 DrvE2p_WriteData(ushort16 v_usAddress, uchar8 *p_ucDatabuf, uchar8 v_ucLen);


/*----------------< 函数定义 >----------------------------------*/
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
	P8SS &= ( ~P8SS_P8S7 )|( ~P8SS_P8S6 );//P8.6,P8.7为IO口  SCL  SDA
	P9SS &= ( ~P9SS_P9S0 );//P9.0为IO  Wp
    I2C_WP_OUT();
	I2C_WP_LOW();
}
///**********************************************************************///
///* Brief:  查询总线是否忙                  		                    *///
///*                                                                    *///
///* Return: 无                                                         *///
///*                                                                    *///
///* Note:                                                              *///
///**********************************************************************///
void DrvE2p_ChkBusBusy(void)
{
	uchar8 v_ucCnt;
	uchar8 v_ucCst = 255;																		///* 数值待测试 *///
	
	for (v_ucCnt = 0;v_ucCnt < v_ucCst; v_ucCnt++)
	{
		DrvE2p_I2CStart();
		if	(DrvE2p_WriteOneByte(DRV_E2P_DEV_ADDR_WRITE) == _SUCCESS)	
		{
				DrvE2p_I2CStop();
				break;	
		}		///* 设备地址(写),判断总线是否空闲 *///
	}
}

///**********************************************************************///
///* Brief:  I2C总线激活                  		                        *///
///*                                                                    *///
///* Return: 无                                                         *///
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
	DrvE2p_I2CDelay_5us();	///* 延时大于4us *///
	I2C_SCL_LOW();
}
///**********************************************************************///
///* Brief:  I2C总线停止                  		                        *///
///*                                                                    *///
///* Return: 无                                                         *///
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
	DrvE2p_I2CDelay_5us();	///* 延时大于4us *///
    I2C_SCL_HIGHT();
	DrvE2p_I2CDelay_5us();	///* 延时大于4us *///
	I2C_SDA_HIGHT();
}

///**********************************************************************///
///* Brief:  读1字节带Ack                  		                        *///
///*                                                                    *///
///* Return: 返回读出的值                                               *///
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
	
	for (V_ucCnt_i = 0; V_ucCnt_i < 8; V_ucCnt_i++)		///* 读8位数据 *///
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
	DrvE2p_I2CDelay_5us();	///* 延时大于4us *///
	I2C_SCL_LOW();
	I2C_SDA_HIGHT();
	
	return V_ucResult;
}
///**********************************************************************///
///* Brief:  读1字节带无Ack               		                        *///
///*                                                                    *///
///* Return: 返回读出的值                                               *///
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
	
	for ( V_ucCnt_i = 0; V_ucCnt_i < 8; V_ucCnt_i++)		///* 读8位数据 *///
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
	DrvE2p_I2CDelay_5us();	///* 延时大于4us *///
	I2C_SCL_LOW();
	
	return V_ucResult;	
}
///**********************************************************************///
///* Brief:  向E2写1字节数据               		                        *///
///*                                                                    *///
///* Param:  v_data：需要写的数据                                       *///
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
	
	for (V_ucCnt_i = 0; V_ucCnt_i < 8; V_ucCnt_i++)			///* 写8位数据 *///
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
	
	DrvE2p_I2CDelay_2us();						///* 延时大于4us *///
	
	if (I2C_SDA_Status_HIGHT) 	///* 检测ACK *///
	{ 
		V_ucOprResult = _FAILED;
	}
	I2C_SCL_LOW();
	return V_ucOprResult; 
}
///**********************************************************************///
///* Brief:  向E2写len字节数据               		                    *///
///*                                                                    *///
///* Param:  v_address：E2地址                                          *///
///* Param:  p_databuf：数据首指针                                      *///
///* Param:  v_len：数据长度                                            *///
///*                                                                    *///
///* Return: _SUCCESS:写成功；FAILED：写失败                            *///
///*                                                                    *///
///* Note:临时函数 不能跨页                                             *///
///**********************************************************************///
uchar8 DrvE2p_WRDataTemp(ushort16 v_usAddress, uchar8 *p_ucDatabuf, uchar8 v_ucLen)
{
	ushort16 i;
	uchar8 *j;
	uchar8 Temp= 0;
	
	if ( (v_ucLen == 0) || (v_ucLen > DRV_E2P_Max_Data_LEN) )					///* 判长度是否合法 *///
	{	
		return _FAILED;
	}
	if ( v_usAddress > 0x01ff )					
	{
		return _FAILED;
	}
	if ( ( (v_usAddress + v_ucLen) <= 0x00ff) || (v_usAddress > 0x00ff) )	///* 判写数据是否跨页 *///
	{
		DrvE2p_I2CStart();
		
		if	((v_usAddress + v_ucLen) <= 0x00ff) { Temp = DRV_E2P_DEV_ADDR_WRITE; }		///* 写在第1大页 *///
		if	(v_usAddress > 0x00ff) 			   { Temp = DRV_E2P_DEV_ADDR_WRPAGE1; }		///* 写在第2大页 *///
		
		if	(DrvE2p_WriteOneByte(Temp) != _SUCCESS)										///* 设备地址(写) *///
		{
			DrvE2p_I2CStop();return _FAILED;
		}
		
		if  (DrvE2p_WriteOneByte( (uchar8) (v_usAddress) ) != _SUCCESS)					///* 数据地址LSB *///
		{
			DrvE2p_I2CStop();return _FAILED; 
		}
		j = p_ucDatabuf;
		for (i = 0; i < v_ucLen; i++)													///* 写数据 *///
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
	
	else									///* 跨大页写不成功 *///
	{
		return _FAILED;
	}
	
	return _SUCCESS;
}
///**********************************************************************///
///* Brief:  向E2写len字节数据               		                    *///
///*                                                                    *///
///* Param:  v_address：E2地址                                          *///
///* Param:  p_databuf：数据首指针                                      *///
///* Param:  v_len：数据长度                                            *///
///*                                                                    *///
///* Return: _SUCCESS:写成功；FAILED：写失败                            *///
///*                                                                    *///
///* Note:每页最多写8字节     不支持跨大页写数据                                         *///
///**********************************************************************///
uchar8 DrvE2p_WriteData(ushort16 v_usAddress, uchar8 *p_ucDatabuf, uchar8 v_ucLen)
{
// 	uchar8 V_ucFstPageLen;		///* 第一页要写的字节数 *///
// 	uchar8 V_ucTemp1,i,V_ucTemp2;
	
	ushort16 V_usEEAdr;
	uchar8  V_ucDataLen,V_ucCnti;
	
	V_usEEAdr = v_usAddress;	
	V_ucDataLen = DRV_E2P_Max_Page_LEN - (v_usAddress & 0x0007);	/* 先算第一次要写的数据长度，第一次写完正好是整数地址 */	
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
		
		V_ucCnti = V_ucCnti + V_ucDataLen;			// 算一下偏移量，数据根据这个偏移量来
		V_usEEAdr = v_usAddress + V_ucCnti;			// 重新计算一下下一次要写的地址		
		V_ucDataLen = v_ucLen - V_ucCnti;			// 重新算一下下一次要写的长度
		if( V_ucDataLen > DRV_E2P_Max_Page_LEN )	// 如果长度大于8，就按8字节，如果小于，写完这次以后就结束了
		{
			V_ucDataLen = DRV_E2P_Max_Page_LEN;
		}
		
	}while( V_ucDataLen );
	
	
// 	
//     
// 	V_ucTemp1 = ( (uchar8) (v_usAddress & 0x0007) + v_ucLen) / (DRV_E2P_Max_Page_LEN);	// 每页8个,计算一下需要多少页
// 	V_ucTemp2 = ( (uchar8) (v_usAddress & 0x000f) + v_ucLen) % (DRV_E2P_Max_Page_LEN);	// 每页8个之后剩下的字节数
// 	
// 	if( V_ucTemp2 )	// 剩余的字节数不为0  要多写一页
// 	{
// 		V_ucTemp1 += 1;
// 	}
// 	
// 	if ( V_ucTemp1 == 1 )																	///* 只写一页，不跨页 *///
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
///* Brief:  从E2读len字节数据               		                    *///
///*                                                                    *///
///* Return: _SUCCESS:读成功；FAILED：读失败                            *///
///*                                                                    *///
///* Note:   读失败不更新                                               *///
///**********************************************************************///
uchar8 DrvE2p_ReadData(ushort16 v_usAddress, uchar8 *p_ucDatabuf, uchar8 v_ucLen)
{
	uchar8 V_ucOprResult = _SUCCESS;
	uchar8 V_ucCnt;
	uchar8 *P_ucTempData;
	
	if (v_ucLen == 0)					///* 判长度是否合法 *///
	{
		return _FAILED;
	}
	
	if ( ( v_usAddress + v_ucLen ) > 0x01ff )	///* 判总长度是否超出 *///
	{	
		return _FAILED;
	}
	
	V_ucCnt = (v_usAddress >> 8) & 0x00ff;
	
	V_ucCnt = V_ucCnt << 1;
	
	DrvE2p_I2CStart();
	
	if (DrvE2p_WriteOneByte( DRV_E2P_DEV_ADDR_WRITE + V_ucCnt ) != _SUCCESS)			///* 设备地址（写） *///
	{  DrvE2p_I2CStop(); return _FAILED; }
	
	
	if (DrvE2p_WriteOneByte( (uchar8) (v_usAddress) )!= _SUCCESS)			///* 写数据地址LSB *///
	{  DrvE2p_I2CStop(); return _FAILED; }
	
	DrvE2p_I2CStart();		///* 重启I2C *///
	
	if (DrvE2p_WriteOneByte(DRV_E2P_DEV_ADDR_READ + V_ucCnt) != _SUCCESS)				///* 设备地址（读） *///
	{  DrvE2p_I2CStop(); return _FAILED; }
	
	P_ucTempData = p_ucDatabuf;
	
	for (V_ucCnt = 0; V_ucCnt < (v_ucLen-1); V_ucCnt++)						///* 读数据 *///
	{
		P_ucTempData[V_ucCnt] = DrvE2p_ReadOneByteAck(); 
	}
	P_ucTempData[V_ucCnt]  = DrvE2p_ReadOneByteNoAck();							///* 读完最后一字节回NoAck *///
	
	DrvE2p_I2CStop();
	
	return V_ucOprResult;
}
#pragma RESTORE
