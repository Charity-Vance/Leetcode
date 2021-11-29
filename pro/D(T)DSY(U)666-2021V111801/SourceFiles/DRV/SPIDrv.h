/*******************************************************************************************************
**** Copyright��  (c)Copyright 2019,�㽭��̩�����Ǳ��������ι�˾,���ܱ�Ӧ���з�                       
****                            All rights reserved.                                                 
**** FileName:    SPIDrv.c                                                                          
**** Brief:       SPIͨ�Žӿ�����ͷ�ļ�                                                                      
**** Author:      peter.he@chint.com                                                                 
**** Version:     V1.0                                                                               
**** Date:        2019��3��14��                                                                         
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

#ifndef   _SPIDRV_H
#define   _SPIDRV_H

#if ( METER_TYPE == METER_TYPE_DTSY666)
/*-------------------------------- H�ļ�ʹ��˵�� -------------------------------------------------------*/
/*
 *  ���ļ��궨���ǰ׺Ϊ:
 *
 */

 
/*----------------< �����ļ� >----------------------------------*/


/*----------------< �궨���� >----------------------------------*/

#define  	SPI_DOUT_H()    	GPIO_IOCFG_P7_DIR_O(1);GPIO_IOCFG_P7_SET_1(1) // SPI���1  
#define   	SPI_DOUT_L()    	GPIO_IOCFG_P7_DIR_O(1);GPIO_IOCFG_P7_SET_0(1) // SPI���0  
#define		SPI_CLK_H()     	GPIO_IOCFG_P5_DIR_O(3);GPIO_IOCFG_P5_SET_1(3) // CLK���1
#define  	SPI_CLK_L()     	GPIO_IOCFG_P5_DIR_O(3);GPIO_IOCFG_P5_SET_0(3) // CLK���0
#define   	SPI_CS_H()      	GPIO_IOCFG_P3_DIR_O(4);GPIO_IOCFG_P3_SET_1(4) // CS���1
#define   	SPI_CS_L()      	GPIO_IOCFG_P3_DIR_O(4);GPIO_IOCFG_P3_SET_0(4) // CS���0

#define		SPI_DIN_In()			GPIO_IOCFG_P7_DIR_I(5); GPIO_IOCFG_PX_PUP_F(7,5)	///*SPI_DIN����̬,���������ֹ*///
#define		SPI_DIN_Status_HIGHT	GPIO_IOCFG_PX_STAT_H(7,5)
#define		SPI_DIN_Status_LOW 		GPIO_IOCFG_PX_STAT_L(7,5)


/*----------------< �������� >----------------------------------*/


/*----------------< �������� >----------------------------------*/
extern uchar8 SPIDrv_ReceiveByte(void);
extern void SPIDrv_SendBtye ( uchar8 v_ucSendData );
extern void SPIDrv_ENSPIMode(void);
extern void SPIDrv_Eable_MeterIC(void);
extern void SPIDrv_Disable_MeterIC(void);




#endif




#endif
