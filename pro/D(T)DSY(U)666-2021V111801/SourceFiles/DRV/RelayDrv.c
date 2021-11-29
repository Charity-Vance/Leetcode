/*******************************************************************************************************
**** Copyright��  (c)Copyright 2019,�㽭��̩�����Ǳ��������ι�˾,���ܱ�Ӧ���з�                       
****                            All rights reserved.                                                 
**** FileName:    RelayDrv.c                                                                          
**** Brief:       �̵�����������                                                                     
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
	#define	RELAY1_ON()				 GPIO_IOCFG_P0_SET_1(1) 	// relay1������1   P0.1
	#define	RELAY1_OFF()			 GPIO_IOCFG_P0_SET_0(1) 	//  relay1������0
	#define	RELAY2_ON()				 GPIO_IOCFG_P0_SET_1(2) 	//  relay2������1   P0.2
	#define	RELAY2_OFF()			 GPIO_IOCFG_P0_SET_0(2) 	//  relay2������0
#endif

#if( METER_TYPE == METER_TYPE_DTSY666 )
	#define	RELAY1_ON()				 GPIO_IOCFG_P0_SET_1(1) 	// relay1������1   P0.1
	#define	RELAY1_OFF()			 GPIO_IOCFG_P0_SET_0(1) 	//  relay1������0
	#define	RELAY2_ON()				 GPIO_IOCFG_P0_SET_1(2) 	//  relay2������1   P0.2
	#define	RELAY2_OFF()			 GPIO_IOCFG_P0_SET_0(2) 	//  relay2������0
	#define RELAYOUT_WORK()          GPIO_IOCFG_P0_SET_1(7)
	#define RELAYOUT_NORAML()        GPIO_IOCFG_P0_SET_0(7) 
#endif

#if( METER_TYPE == METER_TYPE_DDSYU666 )
	#define	RELAY1_ON()				 GPIO_IOCFG_P0_SET_1(3) 	// relay1������1   P0.3
	#define	RELAY1_OFF()			 GPIO_IOCFG_P0_SET_0(3) 	//  relay1������0
	#define	RELAY2_ON()				 GPIO_IOCFG_P0_SET_1(2) 	//  relay2������1   P0.2
	#define	RELAY2_OFF()			 GPIO_IOCFG_P0_SET_0(2) 	//  relay2������0
#endif
/*----------------< �������� >----------------------------------*/



/*----------------< �������� >----------------------------------*/

/*----------------< �������� >----------------------------------*/
void RelayDrv_Closerelay();
void RelayDrv_Openrelay();
void RelayDrv_DelayTimeMonitor();

static void RelayDrv_RelayNormal();
/*----------------< �������� >----------------------------------*/

void RelayDrv_Closerelay()               //��բ
{

	RELAY1_OFF();
	_nop_();
	_nop_();
	RELAY2_ON()	;

	#if ( METER_TYPE == METER_TYPE_DTSY666)
	RELAYOUT_NORAML();///ͬʱ������ؿ���
	#endif
	
}



void RelayDrv_Openrelay()              //��բ
{

	RELAY1_ON();
	_nop_();
    _nop_();
	RELAY2_OFF();

	#if ( METER_TYPE == METER_TYPE_DTSY666)
	RELAYOUT_WORK() ;///ͬʱ������ؿ���
	#endif
	
}

void RelayDrv_RelayNormal()   ///���߻ع鳣̬
{
	RELAY1_OFF();
	_nop_();
	RELAY2_OFF();
	#if ( METER_TYPE == METER_TYPE_DTSY666)
	RELAYOUT_NORAML();///ͬʱ������ؿ���///ͬʱ������ؿ���
	#endif
}

void RelayDrv_DelayTimeMonitor()   ///
{
	if(GStr_Counter.ucRelayDelay_Cnt)
	{	
		GStr_Counter.ucRelayDelay_Cnt--;
		if(GStr_Counter.ucRelayDelay_Cnt==RelayDrvDrv_Delaytimer)///�ڿؿ�����λ
		{
			RelayDrv_RelayNormal();
		}
		#if ( METER_TYPE == METER_TYPE_DTSY666)
		if(GStr_Counter.ucRelayDelay_Cnt==RelayOutsideDrv_Delaytimer)///��ؿ�����λ
		{
			RelayDrv_Closerelay();
		}
		#endif
	}
	else
	{
		RelayDrv_RelayNormal();
	}
}