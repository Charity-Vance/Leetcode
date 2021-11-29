/*******************************************************************************************************
**** Copyright��  (c)Copyright 2019,�㽭��̩�����Ǳ��������ι�˾,���ܱ�Ӧ���з�                       
****                            All rights reserved.                                                 
**** FileName:    INTERNALE2DRV.H                                                                        
**** Brief:       ��E2����ͷ�ļ�                                                                      
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

#ifndef   INTERNALE2DRV_H
#define   INTERNALE2DRV_H

/*-------------------------------- H�ļ�ʹ��˵�� -------------------------------------------------------*/
/*
 *  ���ļ��궨���ǰ׺Ϊ:
 *
 */

 
/*----------------< �����ļ� >----------------------------------*/


/*----------------< �궨���� >----------------------------------*/
#define	FLASH_RW_ENABLE			0X68
#define	FLASH_RW_DISENABLE		0X00

#define	FLASH_RW_ENABLE_STEP1	0X08
#define	FLASH_RW_ENABLE_STEP2	0X20
#define	FLASH_RW_ENABLE_STEP3	0X40

/*----------------< �������� >----------------------------------*/


/*----------------< �������� >----------------------------------*/

extern void Hal_WriteFlash_byte(INT16U adr, INT8U dat, INT8U sta);
extern INT8U Hal_ReadFlash_byte(INT16U adr, INT8U sta);
extern INT8U Hal_ReadEEPROM(INT8U  *Dst, INT16U Src, INT16U Len);


#endif
