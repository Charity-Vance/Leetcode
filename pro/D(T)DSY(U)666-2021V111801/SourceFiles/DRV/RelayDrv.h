/*******************************************************************************************************
**** Copyright��  (c)Copyright 2019,�㽭��̩�����Ǳ��������ι�˾,���ܱ�Ӧ���з�                       
****                            All rights reserved.                                                 
**** FileName:    RELAYDRV.h                                                                          
**** Brief:       �̵�������ͷ�ļ�                                                                     
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

#ifndef   _RELAYDRV_H
#define   _RELAYDRV_H

/*-------------------------------- H�ļ�ʹ��˵�� -------------------------------------------------------*/
/*
 *  ���ļ��궨���ǰ׺Ϊ:
 *
 */

 
/*----------------< �����ļ� >----------------------------------*/


/*----------------< �궨���� >----------------------------------*/


/*----------------< �������� >----------------------------------*/
#define  RelayOnce_Delaytimer        200*3       ///�̵����ж�����
#define  RelayDrvDrv_Delaytimer      RelayOnce_Delaytimer-24       ///�ڿؿ�����λʱ��120ms
#if ( METER_TYPE == METER_TYPE_DTSY666)
#define  RelayOutsideDrv_Delaytimer      RelayOnce_Delaytimer-200       ///��ؿ�����λʱ��120ms
#endif

/*----------------< �������� >----------------------------------*/
extern void RelayDrv_Closerelay();
extern void RelayDrv_Openrelay();
extern void RelayDrv_DelayTimeMonitor();



#endif
