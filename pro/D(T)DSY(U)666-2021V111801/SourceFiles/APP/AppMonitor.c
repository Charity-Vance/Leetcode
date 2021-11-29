/*******************************************************************************************************
**** Copyright��  (c)Copyright 2019,�㽭��̩�����Ǳ��������ι�˾,���ܱ�Ӧ���з�                       
****                            All rights reserved.                                                 
**** FileName:    AppMonitor.c                                                                          
**** Brief:       ��ʱ����ļ�                                                                     
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


/*----------------< �������� >----------------------------------*/


/*----------------< �������� >----------------------------------*/


/*----------------< �������� >----------------------------------*/

void ApiMntr_PeripheralMonitor(void);

void ApiMntr_MonitorTask(void);
/*----------------< �������� >----------------------------------*/




/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ��ʱ��غ�������ʽ���Ӳ�����������Ĵ������õ�
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
 
void ApiMntr_MonitorTask(void)
{
	uchar8 i;
	// @brief  ���һ�°����ͳ���ģʽ�̽ӵ�
	ApiMntr_PeripheralMonitor();
	
	ApiPwOn_SysClkInit();	// ���һ��ϵͳʱ��
	
	ApiPwOn_McuTimerInit(); // ��ʱ����飨�������Ķ�ʱ����
	
   // @brief  1S
	if ( _TRUE == LibPub_GetDiffTime( GStr_Monitor.ulTimers, LibPub_GetTimerBeat(), 1000) ) ///* 1S��ʱ *///
	{ 
		GStr_Monitor.ulTimers= LibPub_GetTimerBeat();
				
		if( GStr_Monitor.ucPowerOnTimer < 60 )
		{
			GStr_Monitor.ucPowerOnTimer++;				
			
			/* �ϵ�5s���ݶ����Ժ��ٲ�������ģ��*/
			if( 5 == GStr_Monitor.ucPowerOnTimer )	
			{
				ApiPwOn_BleInit();
			}
		}
		
		APiDisp_LcdledControl(); 
		ApiRelay_ControlProcess();//ÿ���ж�һ���Ƿ�����բ����û���ɹ���
		Api_PowerLoadLimitedCheck();//������բ���
		if(GStr_Flag.ucRunState1&F_RUN_OVER_DEMAND_CLOSE)
		{
			if(_TRUE == LibPub_GetDiffTime( GStr_Monitor.ulOverDemandCloseTime, LibPub_GetTimerBeat(), 300000) )
			{///���غ�5min �Զ���բ
				GStr_Monitor.ulOverDemandCloseTime=LibPub_GetTimerBeat();
				GStr_Flag.ucRunState1 &=~F_RUN_OVER_DEMAND_CLOSE;///����ػָ���բ���ֱ�Ӻ�բ
				ApiRelay_ControlProcess();
			}
		}
		/*����޸���ͨ�ŵ�ַ����Ҫ��������ģ�飬������������*/
		if( (BLE_STAT_RST == GStr_Flag.ucBLESTATFlag)
			|| (BLE_STAT_ERRREP == GStr_Flag.ucBLESTATFlag) )	/* ģ���ϱ������쳣��ֱ�Ӹ�λ */
		{
			/*д��ͨ�ŵ�ַ����Ҫ������������ģ������������¹㲥*/
			BleDrv_BleReset();
			BleDrv_InitBleRunPara();
			BleDrv_SetBleStat();	 
		}
//		if((GV_ClearFlag==MoneyClear)||(GV_ClearFlag==CommClear))///���崦��
//		{
//				ApiPwOn_MeterClear(GV_ClearFlag);
//		}
		if((!(GStr_Flag.ucRunState2&F_RUN_INTAUTHAvailabilityFlag))&&(GStr_Flag.ucRunState3&F_RUN_READ_RANDOM2))
		{
			if(_TRUE == LibPub_GetDiffTime( GStr_Monitor.ulReadRandom2DelayTime, LibPub_GetTimerBeat(), 300000) )
			///5min�������֤����ʧЧ�����־���������������2
			{
				GStr_Flag.ucRunState3 &=~F_RUN_READ_RANDOM2;///����������־
				PrepaymentModule_GetChallenge(&GStr_VirtualEsamPara.ucRs485RandNum2[0], 0x04) ;///��ȡ�����2
				LibPub_MemSetBytes(&GStr_VirtualEsamPara.ucRs485RandNum2[4], 0x00, 4);///�����2��������
			}	
		}
		if(GStr_Flag.ucRunState2 &F_RUN_PROG_10MIN_FLAG)
		{
			if(_TRUE == LibPub_GetDiffTime( GStr_Monitor.ulProgEventDelayTime, LibPub_GetTimerBeat(), 600000) )
			{
				GStr_Flag.ucRunState2 &=~F_RUN_PROG_10MIN_FLAG;///���־
			}
		}
		if(GStr_AVAIL.ulAutRemainingTime)
		{
			GStr_Flag.ucRunState2 |= F_RUN_INTAUTHAvailabilityFlag;
			GStr_AVAIL.ulAutRemainingTime--;
			if(0==GStr_AVAIL.ulAutRemainingTime)
			{
				GStr_Flag.ucRunState2 &= ~F_RUN_INTAUTHAvailabilityFlag;
			}
		}
		else
		{
			GStr_Flag.ucRunState2 &= ~F_RUN_INTAUTHAvailabilityFlag;
			GStr_Flag.ucRunState3 &=~F_RUN_READ_RANDOM2;///����������־
			PrepaymentModule_GetChallenge(&GStr_VirtualEsamPara.ucRs485RandNum2[0], 0x04) ;///��ȡ�����2
			LibPub_MemSetBytes(&GStr_VirtualEsamPara.ucRs485RandNum2[4], 0x00, 4);///�����2��������
		}		
	}
	
	// @brief  1���Ӷ�ʱ�����ز��� ��ʱ��������ʱ
	 
	if ( _TRUE == LibPub_GetDiffTime( GStr_Monitor.ulTimerMin, LibPub_GetTimerBeat(), 60000) ) ///* 1���� *///
	{
		GStr_Monitor.ulTimerMin = LibPub_GetTimerBeat();
		
		GStr_Flag.ucPowerOnFlag=0;///RAM����Ҫ��ʼ������
		
		ApiPwOn_EmuParaCheck() ; 		///* ��������У�� *///
		ApiPwOn_MeterInfoParaCheck();	///* ����Ϣ��ͨ�ŵ�ַ����š������ʡ����������������� *///  
		ApiPwOn_DisplayParaCheck();     ///* ��ʾ��ϢУ��
		ApiPwOn_MoneyParaCheck();       ///* �������Ȳ���У��  ����ʣ����Ч��
		ApiMoney_RefreshPrice(); 		////*��۲���Ч��
		ApiPwOn_FunConfigParaCheck();	///* �������ö��ڼ�� */// 
		ApiPwOn_KeyStatusCheck();       ///* ��Կ״̬�Ϳ���״̬ *///
		ApiPwOn_BleParaChk();			///* ���ڼ���������� */// 
		ApiPwOn_EventPointCheck();      ///* �¼�ָ��Ч��
		ApiMoney_TimeingHoldMoney();	///��ʱ����ʣ�����͸֧���
		

	  
		for( i=0; i<4; i++)
		{
			if( GStr_Monitor.usPasswordErrTime[i] != 0 )
			{
				GStr_Monitor.usPasswordErrTime[i]--;
				if( GStr_Monitor.usPasswordErrTime[i] == 0 )
				{
					if( i== 3 )
					{
						PrepaymentModule_Comm_ClrMACErrNum();
					}
					else
					{
						GStr_Counter.ucPasswordErr_Cnt[i]=0;
					}

				}
			}
		}
		 
		if( GStr_Monitor.ulSoftI_JTime != 0 )
		{
			GStr_Flag.ucMeterMode |= F_FACTORY_MODE;
			
			GStr_Monitor.ulSoftI_JTime--;
			if( GStr_Monitor.ulSoftI_JTime == 0 )
			{
				GStr_Flag.ucMeterMode &= ~F_FACTORY_MODE;
			}
			LibPub_WriteDataToE2prom( LIB_E2P_SOFTI_J, 0, (uchar8 *)&GStr_Monitor.ulSoftI_JTime);
		}
		else
		{ 
			GStr_Flag.ucMeterMode &= ~F_FACTORY_MODE;
		}
		
		#if(METER_TYPE==METER_TYPE_DTSY666)	
		if(	(GStr_Flag.ucRunState3 & F_RUN_Relayact_Voltage) && !(GStr_Flag.ucRunState2&F_RUN_RELAY_STATE) )	//��һ���ѹ����82%Un,�ҵ����Ϊ�Ǻ�բ״̬
		{
			GStr_Counter.ucRelayon_Cnt++;
			if( GStr_Counter.ucRelayon_Cnt >= Relayon_Delaytimer )				//һ��ʱ����û�������źţ�����Ϊ����բ״̬û�к�բ
			{ 
				GStr_Counter.ucRelayon_Cnt = 0;
				RelayDrv_Closerelay();									//�̵�����բ
				GStr_Counter.ucRelayDelay_Cnt = RelayOnce_Delaytimer;	//3s��λ
			}
		}
		else
		{
			GStr_Counter.ucRelayon_Cnt = 0;
		}
		#endif
		
	} 
	
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    �����غ�������Ҫ�ǰ������̽ӵ��///��բ������λ��ʱҲ��������
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
 
void ApiMntr_PeripheralMonitor(void)
{
	/* 5ms���һ�� */
	if ( _TRUE == LibPub_GetDiffTime( GStr_Monitor.ulTimer5ms, LibPub_GetTimerBeat(), 5) )
	{
		GStr_Monitor.ulTimer5ms =  LibPub_GetTimerBeat();
		DrvKey_FactoryKeyMonitor();
		DrvKey_DisplayKeyMonitor();
		RelayDrv_DelayTimeMonitor();
		if(((GStr_Flag.ucRunState1&F_RUN_L2_ALRAM)&&(!(GStr_Flag.ucRunState&F_RUN_CLOSE_L2)))
		||((GStr_Flag.ucRunState1&F_RUN_REMAIND_ZERO)&&(!(GStr_Flag.ucRunState&F_RUN_CLOSE_ZERO))))
		{
				DrvKey_DisplayKeyInit();  
				if(DISPLAY_KEY_LOW)
				{
					GStr_Counter.ucKeyRelayOn_Cnt++;
				}
				if(GStr_Counter.ucKeyRelayOn_Cnt>=1000)
				{
						if(GStr_Flag.ucRunState1&F_RUN_L2_ALRAM)
						{
								GStr_Flag.ucRunState|=F_RUN_CLOSE_L2;
						}
						if(GStr_Flag.ucRunState1&F_RUN_REMAIND_ZERO)
						{
								GStr_Flag.ucRunState|=F_RUN_CLOSE_ZERO;
						}
						LibPub_MemSetBytes(GA_ucRelayOperCode,0xFF,4);///������բ�Ĳ����ߴ���ΪFFFFFFFF
						ApiRelay_ControlProcess();
						LibPub_WriteDataToE2prom(LIB_E2P_RUN_STATE,0,&GStr_Flag.ucRunState);	
				}
		}
		else
		{
				GStr_Counter.ucKeyRelayOn_Cnt=0;
		}

	}
}

