/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    SPIDrv.c                                                                          
**** Brief:       SPI通信接口驱动头文件                                                                      
**** Author:      peter.he@chint.com                                                                 
**** Version:     V1.0                                                                               
**** Date:        2019年3月14日                                                                         
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

#ifndef   _SPIDRV_H
#define   _SPIDRV_H

#if ( METER_TYPE == METER_TYPE_DTSY666)
/*-------------------------------- H文件使用说明 -------------------------------------------------------*/
/*
 *  该文件宏定义的前缀为:
 *
 */

 
/*----------------< 包含文件 >----------------------------------*/


/*----------------< 宏定义区 >----------------------------------*/

#define  	SPI_DOUT_H()    	GPIO_IOCFG_P7_DIR_O(1);GPIO_IOCFG_P7_SET_1(1) // SPI输出1  
#define   	SPI_DOUT_L()    	GPIO_IOCFG_P7_DIR_O(1);GPIO_IOCFG_P7_SET_0(1) // SPI输出0  
#define		SPI_CLK_H()     	GPIO_IOCFG_P5_DIR_O(3);GPIO_IOCFG_P5_SET_1(3) // CLK输出1
#define  	SPI_CLK_L()     	GPIO_IOCFG_P5_DIR_O(3);GPIO_IOCFG_P5_SET_0(3) // CLK输出0
#define   	SPI_CS_H()      	GPIO_IOCFG_P3_DIR_O(4);GPIO_IOCFG_P3_SET_1(4) // CS输出1
#define   	SPI_CS_L()      	GPIO_IOCFG_P3_DIR_O(4);GPIO_IOCFG_P3_SET_0(4) // CS输出0

#define		SPI_DIN_In()			GPIO_IOCFG_P7_DIR_I(5); GPIO_IOCFG_PX_PUP_F(7,5)	///*SPI_DIN输入态,上拉电阻禁止*///
#define		SPI_DIN_Status_HIGHT	GPIO_IOCFG_PX_STAT_H(7,5)
#define		SPI_DIN_Status_LOW 		GPIO_IOCFG_PX_STAT_L(7,5)


/*----------------< 变量声明 >----------------------------------*/


/*----------------< 函数声明 >----------------------------------*/
extern uchar8 SPIDrv_ReceiveByte(void);
extern void SPIDrv_SendBtye ( uchar8 v_ucSendData );
extern void SPIDrv_ENSPIMode(void);
extern void SPIDrv_Eable_MeterIC(void);
extern void SPIDrv_Disable_MeterIC(void);




#endif




#endif
