/*******************************************************************************************************
**** Copyright��  (c)Copyright 2019,�㽭��̩�����Ǳ��������ι�˾,���ܱ�Ӧ���з�                       
****                            All rights reserved.                                                 
**** FileName:    AppMeasure.h                                                                          
**** Brief:       ������ز���ͷ�ļ�                                                                      
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

#ifndef   _APPMEASURE_H
#define   _APPMEASURE_H

/*-------------------------------- H�ļ�ʹ��˵�� -------------------------------------------------------*/
/*
 *  ���ļ��궨���ǰ׺Ϊ:
 *
 */

 
/*----------------< �����ļ� >----------------------------------*/


/*----------------< �궨���� >----------------------------------*/


/*----------------< �������� >----------------------------------*/


/*----------------< �������� >----------------------------------*/
extern void ApiMS_UpdateUIP(void);
extern void ApiMS_MeasureTask(void);
extern void ApiMS_EnergyPulseUpdate(void);
extern uchar8 ApiMS_EnergyProcess( GStr_ENERGY_PULSE_Type *p_strEnergyPulse );
extern uchar8 ApiMS_CalibrationMeterComm( uchar8 v_ucChID );
extern void ApiMS_InitMeterICPara( void );
extern void ApiMS_MeterICParaCheck( void );
extern void ApiMS_DisOrEnable( uchar8 v_ucWorkMode);



#endif
