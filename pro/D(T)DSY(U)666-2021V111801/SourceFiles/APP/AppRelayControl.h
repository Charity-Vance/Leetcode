/*******************************************************************************************************
**** Copyright��  (c)Copyright 2019,�㽭��̩�����Ǳ��������ι�˾,���ܱ�Ӧ���з�                       
****                            All rights reserved.                                                 
**** FileName:    AppPowerOn.h                                                                         
**** Brief:       �ϵ�ϵͳ����                                                                      
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

#ifndef   _APPRELAYCONTROL_H
#define   _APPRELAYCONTROL_H

/*-------------------------------- H�ļ�ʹ��˵�� -------------------------------------------------------*/
/*
 *  ���ļ��궨���ǰ׺Ϊ:
 *
*/

 
/*----------------< �����ļ� >----------------------------------*/


/*----------------< �궨���� >----------------------------------*/
#if(METER_TYPE==METER_TYPE_DTSY666)
#define API_Relayact_Voltage			22*83		//�����ֻ��һ���ѹʱ���ж��Ƿ����ĵ�ѹ��ֵ 220V*0.83=1826V
#endif


/*----------------< �������� >----------------------------------*/


/*----------------< �������� >----------------------------------*/
extern  void ApiRelay_ControlProcess(void);
	    	
extern void ApiRelay_SubtractMoneyRelayJudge(void);
extern void Api_PowerLoadLimitedCheck(void);


#endif

