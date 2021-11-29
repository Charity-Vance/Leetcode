/*******************************************************************************************************
**** Copyright��  (c)Copyright 2019,�㽭��̩�����Ǳ��������ι�˾,���ܱ�Ӧ���з�                       
****                            All rights reserved.                                                 
**** FileName:    AppPowerOff.c                                                                          
**** Brief:       ���������ļ�                                                                      
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
static void ApiPwOff_CloseDevices(void);
static void ApiPwOff_DataSave(void);
static void ApiPwOff_EnterSleep(void);
static void ApiPwOff_PeripheralInit(void);
static void ApiPwOff_DataProcess(void);
static void ApiPwOff_Display(void); 
static void ApiPwOff_SysClkInit(void);
static void ApiPwOff_BLEPOWERInit(void);
static void ApiPwOff_McuTimerInit(void);
static void ApiPwOff_McuGpioInit(void);
static void ApiPwOff_McuUartInit(void);
static void ApiPwOff_McuDispInit(void);
static void ApiPwOff_EmuInit(void);
static void ApiPwOff_McuLPDInit(void);
static void ApiPwOff_McuEnterSleep(void);
void ApiPwOff_PowerOffTask(void);

/*----------------< �������� >----------------------------------*/

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ���������
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
 
void ApiPwOff_PowerOffTask(void)
{
	uchar8	V_ucCnti;
	
	if ( GStr_Flag.ucSystem & F_PWOFF_NOW )	// �����������ж��м�⣬��⵽������������ж�
	{
		// @brief ---- �ر�֮ǰ�����Ĺ���ģ��   
			ApiPwOff_CloseDevices();	 
		
		// @brief ---- ���ϵͳ���������˾�Ҫ����һ����Ҫ��������ݣ�������β�� 
		if ( GStr_Flag.ucSystem & F_PWRUN )	
		{
			ApiPwOff_DataSave();
			GStr_Flag.ucSystem &= ~F_PWRUN ;
		}
		
		// @brief ---- ��ʱ�ж�һ���Ƿ���ĵ��磬�����ĵ����˾����������͹��� 
		for ( V_ucCnti = 0; V_ucCnti<10; V_ucCnti++ )
		{
			LibPub_DelayNms(10);
			if ( _FALSE == ApiPwOn_PowerChk() )	///* ���ж�һ�µ������ *///
			{
				GStr_Flag.ucSystem = GStr_Flag.ucSystem | F_PWOFF_NOW;
				ApiPwOff_EnterSleep();
			}
			WDT_Clr();
		}
		
		// @brief ---- ���⻹û�н���͹��ģ��Ǿ�������һ�� 
		if ( (GStr_Flag.ucSystem & F_PWOFF_NOW) != F_PWOFF_NOW )	
		{
			GStr_Flag.ucSystem &= (~F_PWOFF_NOW);
			GStr_Flag.ucSystem |= F_PWON;			///* ���ϵ��־ */// 
		}
		
		// @brief ---- ���⻹û�н���͹��ģ��Ǿ�������һ�� 
		ApiPwOn_SysTemInit();
		
	}
	
	/* ����ܵ�������ʾ�Ѿ��ϵ������ˣ����ϵ����б�־ */
	if ( 0 == ( GStr_Flag.ucSystem & F_PWRUN ) )
	{
		GStr_Flag.ucSystem |= F_PWRUN ;
	}
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ����ر����輰����ģ��
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
 
static void ApiPwOff_CloseDevices(void)
{
	/* �ر�����ģ�鹩�磨�������ֱ��ֹͣ���磩 */
	ApiPwOff_BLEPOWERInit();

	/* �رն�ʱ�� */
	ApiPwOff_McuTimerInit();
	
	/* �رմ��� */
	ApiPwOff_McuUartInit( );
	
	/* �رռ��� */
	ApiPwOff_EmuInit( );
	
	/* �ر���ʾ */
	ApiPwOff_McuDispInit( );

	
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ��������
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
 
static void ApiPwOff_McuLPDInit(void)
{
	PASLO_POWER_SWITCH_ON();
    LPDCON1 = 0x00;/*�ص��͵�ѹ���*/

    PASLO_POWER_SWITCH_ON();
	LPDCON2 = 0x00;/*�ص��͵�ѹ���*/ 
	
    PASLO_POWER_SWITCH_ON();;
		#if(METER_TYPE==METER_TYPE_DDSYU666)   //�����͵�ѹ���Ϊ3.00V
			LPDCON2 |= 0xA3;    //�͵�ѹ��⣬3.00V
		#else
			LPDCON2 |= 0xA9;    //�������Ӧ����Ϊ 0xA4  
		#endif
	
	PASLO_POWER_SWITCH_ON();
 		#if(METER_TYPE==METER_TYPE_DDSYU666)   //������ֹ�����Զ��л�
			PWRCON1 = 1;
		#else
			PWRCON1 = 0;				//�������ҲӦ����Ϊ��ֹ�����Զ��л�
		#endif
	
    PASLO_POWER_SWITCH_ON();
    PWRCON2 = 0x00;
	
    PASLO_POWER_SWITCH_ON();
		#if(METER_TYPE==METER_TYPE_DDSYU666)   //������ֹ�����Զ��л�
			PWRCON1 = 1;
		#else
			PWRCON1 = 0;				//�������ҲӦ����Ϊ��ֹ�����Զ��л�
		#endif
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    �������ݴ洢����Ҫ��E2 
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
 
static void ApiPwOff_DataSave(void)
{
	uchar8	V_ucTempBuff[4];
	
		// ʣ���͸֧����һ��
	GStr_Money.usCRC16 = LibPub_CRC16_CCITT(&GStr_Money.ucaRemainMoney[0], GStr_MONEY_Type_LEN-2);
	DrvE2p_WriteData( LIB_E2P_Money_Addr,&GStr_Money.ucaRemainMoney[0] ,GStr_MONEY_Type_LEN);///дʣ���͸֧��������������д����
	
	// ����β������һ��
	V_ucTempBuff[0] =  GStr_EnergyPulseFw.ucaPulseRemain[0];
	V_ucTempBuff[1] = ~GStr_EnergyPulseFw.ucaPulseRemain[0];
	V_ucTempBuff[2] =  GStr_EnergyPulseBk.ucaPulseRemain[1];
	V_ucTempBuff[3] = ~GStr_EnergyPulseFw.ucaPulseRemain[1]; 
	LibPub_WriteDataToE2prom( LIB_E2P_ENERGY_DECPULSE_WS, 0, V_ucTempBuff );	///* ����β����һ�£������ľͲ����� *///
	
	
	
	/* ������� */
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ����͹���  
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
 
static void ApiPwOff_EnterSleep(void)
{
	/* ���ÿ��� */
	ApiPwOff_PeripheralInit();
	
	/* �رմ򿪵�ģ�� */
	ApiPwOff_CloseDevices();
	 
	/* ���ݴ��� */	
	ApiPwOff_DataProcess();
	
	/* �ر�LDO��� */
	ApiPwOff_McuLPDInit();
	
	/* ����ͣ����ʾ */		
	ApiPwOff_Display(); 
	
	/* ����ϵͳʱ��*/		
	ApiPwOff_SysClkInit();
	
	/* ����sleepģʽ */
	ApiPwOff_McuEnterSleep();
	
	
	
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ������������    
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
 
static void ApiPwOff_PeripheralInit(void)
{
	ApiPwOff_McuGpioInit();
}


/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    �������ݴ���    
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
 
static void ApiPwOff_DataProcess(void)
{
	
}


/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ������ʾ����     
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
 
static void ApiPwOff_Display(void)
{
	
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ����ʱ�Ӵ���     
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
 
static void ApiPwOff_SysClkInit(void)
{
	
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ����ر�����ģ�鹩��   
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
static void ApiPwOff_BLEPOWERInit(void)
{
	BLE_POWER_OFF();
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    �������ö�ʱ�����رն�ʱ����     
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
static void ApiPwOff_McuTimerInit(void)
{
	TCON &= ~TCON_TF0;	// �����־ 
	IEN0 &= ~IEN0_ET0;	// ��ֹ�ж�
	STOP_TR0();
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ��������GPIO     
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
#if( METER_TYPE == METER_TYPE_DDSYU666 )
void ApiPwOff_McuGpioInit(void)
{
// @brief P0�� �ܹ�4������ p0.1/2/3/7  Lamp/RelayB/RelayA/Alarm
	// ����
	GPIO_IOCFG_P0_DIR_I( 1);	
	GPIO_IOCFG_P0_DIR_I( 2);	// 01 ��բ 10 ��բ
	GPIO_IOCFG_P0_DIR_I( 3);
	GPIO_IOCFG_P0_DIR_I( 7);
	// ����     0        
	GPIO_IOCFG_P0_PUP_F( 1);
	GPIO_IOCFG_P0_PUP_F( 2);
	GPIO_IOCFG_P0_PUP_F( 3);
	GPIO_IOCFG_P0_PUP_F( 7);
	// ״̬     0        
	GPIO_IOCFG_P0_SET_0( 1);	// ����
	GPIO_IOCFG_P0_SET_0( 2);
	GPIO_IOCFG_P0_SET_0( 3);
	GPIO_IOCFG_P0_SET_0( 7);	// ��բ��
	// ���ģʽѡ��      
	GPIO_IOCFG_P0_OUT_C( 1);	// ��������
	GPIO_IOCFG_P0_OUT_C( 2);
	GPIO_IOCFG_P0_OUT_C( 3);
	GPIO_IOCFG_P0_OUT_C( 7);
	// �˿��������������ģʽѡ��
	GPIO_IOCFG_P0_OUTH_WEAKEN( 1);
	GPIO_IOCFG_P0_OUTH_WEAKEN( 2);
	GPIO_IOCFG_P0_OUTH_WEAKEN( 3);
	GPIO_IOCFG_P0_OUTH_WEAKEN( 7);
	// ��������ģʽѡ��Ĵ���
	GPIO_IOCFG_P0_PUPM_SWITCH( 1);
	GPIO_IOCFG_P0_PUPM_SWITCH( 2);
	GPIO_IOCFG_P0_PUPM_SWITCH( 3);
	GPIO_IOCFG_P0_PUPM_SWITCH( 7);
	// �˿�������Դѡ��Ĵ���
	GPIO_IOCFG_P0_INM_DATA( 1);
	GPIO_IOCFG_P0_INM_DATA( 2);
	GPIO_IOCFG_P0_INM_DATA( 3);
	GPIO_IOCFG_P0_INM_DATA( 7);


// @brief P1�� �ܹ�1������ p1.4	 PFout
	// ����
//	GPIO_IOCFG_P1_DIR_I( 0);
//	GPIO_IOCFG_P1_DIR_I( 3);
	GPIO_IOCFG_P1_DIR_I( 4);
	// ����     1        
//	GPIO_IOCFG_P1_PUP_F( 0);
//	GPIO_IOCFG_P1_PUP_F( 3);
	GPIO_IOCFG_P1_PUP_F( 4);
	// ״̬     1        
//	GPIO_IOCFG_P1_SET_1( 0);
//	GPIO_IOCFG_P1_SET_1( 3); 
	GPIO_IOCFG_P1_SET_0( 4); // �ϵ�����������������Ϊ����

//// @brief P2�� �ܹ�3������ p2.2/6/7	DISPKEY / 485RXD / 485TXD
//	GPIO_IOCFG_P2_DIR_I( 2);
//	GPIO_IOCFG_P2_DIR_I( 6);
//	GPIO_IOCFG_P2_DIR_O( 7);
//	// ����     2
//	GPIO_IOCFG_P2_PUP_F( 2);
//	GPIO_IOCFG_P2_PUP_F( 6);
//	GPIO_IOCFG_P2_PUP_F( 7);
//	// ״̬     2        
//	GPIO_IOCFG_P2_SET_0( 2);
//	GPIO_IOCFG_P2_SET_0( 6);
//	GPIO_IOCFG_P2_SET_0( 7);
//	// ���ģʽѡ��      
//	GPIO_IOCFG_P2_OUT_N( 2);
//	GPIO_IOCFG_P2_OUT_N( 6);
//	GPIO_IOCFG_P2_OUT_N( 7);
//	// �˿��������������ģʽѡ��
//	GPIO_IOCFG_P2_OUTH_WEAKEN( 2);
//	GPIO_IOCFG_P2_OUTH_WEAKEN( 6);
//	GPIO_IOCFG_P2_OUTH_WEAKEN( 7);
//	// ��������ģʽѡ��Ĵ���  
//	GPIO_IOCFG_P2_PUPM_SWITCH( 2);
//	GPIO_IOCFG_P2_PUPM_SWITCH( 6);
//	GPIO_IOCFG_P2_PUPM_SWITCH( 7);
//	// �˿�������Դѡ��Ĵ���
//	GPIO_IOCFG_P2_INM_DATA( 2);
//	GPIO_IOCFG_P2_INM_DATA( 6);
//	GPIO_IOCFG_P2_INM_DATA( 7);

// @brief P3�� �ܹ�3������ p3.0/1/2/3/4	 BT_RXD / BT_TXD / KEY1/ SCL / SDA
	GPIO_IOCFG_P3_DIR_I( 0);
	GPIO_IOCFG_P3_DIR_I( 1);
	GPIO_IOCFG_P3_DIR_I( 2);
	GPIO_IOCFG_P3_DIR_I( 3);
	GPIO_IOCFG_P3_DIR_I( 4);
	// ����     3        
	GPIO_IOCFG_P3_PUP_F( 0);
	GPIO_IOCFG_P3_PUP_F( 1);
	GPIO_IOCFG_P3_PUP_F( 2);
	GPIO_IOCFG_P3_PUP_F( 3);
	GPIO_IOCFG_P3_PUP_F( 4);
	// ״̬     3        
	GPIO_IOCFG_P3_SET_0( 0);
	GPIO_IOCFG_P3_SET_0( 1);
	GPIO_IOCFG_P3_SET_0( 2);	
	GPIO_IOCFG_P3_SET_0( 3);	 
	GPIO_IOCFG_P3_SET_0( 4); 	 
	// ���ģʽѡ��
	GPIO_IOCFG_P3_OUT_N( 0);
	GPIO_IOCFG_P3_OUT_N( 1);
	GPIO_IOCFG_P3_OUT_N( 2);
	GPIO_IOCFG_P3_OUT_N( 3);
	GPIO_IOCFG_P3_OUT_N( 4);

// @brief P4�� �ܹ�4������ p4.4/5/6/7 SEG1/SEG2/SEG3/SEG4
	GPIO_IOCFG_P4_DIR_I( 4);
	GPIO_IOCFG_P4_DIR_I( 5);
	GPIO_IOCFG_P4_DIR_I( 6);
	GPIO_IOCFG_P4_DIR_I( 7);
	// ����     4        
	GPIO_IOCFG_P4_PUP_F( 4);
	GPIO_IOCFG_P4_PUP_F( 5);
	GPIO_IOCFG_P4_PUP_F( 6);
	GPIO_IOCFG_P4_PUP_F( 7);
	// ״̬     4        
	GPIO_IOCFG_P4_SET_0( 4);
	GPIO_IOCFG_P4_SET_0( 5);
	GPIO_IOCFG_P4_SET_0( 6);
	GPIO_IOCFG_P4_SET_0( 7);

// @brief P5�� �ܹ�8������ p5.0/1/2/3/4/5/6/7	BT_CTL / BT_ATEN / SEG5 / SEG8 / SEG9(DCK) / SEG10(TDI) /SEG11(TMS) / SEG12(TDO)
	GPIO_IOCFG_P5_DIR_I( 0);
	GPIO_IOCFG_P5_DIR_I( 1);
	GPIO_IOCFG_P5_DIR_I( 2);
	GPIO_IOCFG_P5_DIR_I( 3);
	GPIO_IOCFG_P5_DIR_I( 4);
	GPIO_IOCFG_P5_DIR_I( 5);
	GPIO_IOCFG_P5_DIR_I( 6);
	GPIO_IOCFG_P5_DIR_I( 7);
	// ����     5        
	GPIO_IOCFG_P5_PUP_F( 0);
	GPIO_IOCFG_P5_PUP_F( 1);
	GPIO_IOCFG_P5_PUP_F( 2);
	GPIO_IOCFG_P5_PUP_F( 3);
	GPIO_IOCFG_P5_PUP_F( 4);
	GPIO_IOCFG_P5_PUP_F( 5);
	GPIO_IOCFG_P5_PUP_F( 6);
	GPIO_IOCFG_P5_PUP_F( 7);
	// ״̬     5        
	GPIO_IOCFG_P5_SET_0( 0);
	GPIO_IOCFG_P5_SET_0( 1);
	GPIO_IOCFG_P5_SET_0( 2);
	GPIO_IOCFG_P5_SET_0( 3);
	GPIO_IOCFG_P5_SET_0( 4);
	GPIO_IOCFG_P5_SET_0( 5);
	GPIO_IOCFG_P5_SET_0( 6);
	GPIO_IOCFG_P5_SET_0( 7);

//// @brief P6�� �ܹ�7������ p6.1/2/3/4/5/6/7   SEG8/ SEG7/ SEG6/ SEG5/ SEG4/ SEG3/ SEG2
//	GPIO_IOCFG_P6_DIR_O( 1);
//	GPIO_IOCFG_P6_DIR_O( 2);
//	GPIO_IOCFG_P6_DIR_O( 3);
//	GPIO_IOCFG_P6_DIR_O( 4);
//	GPIO_IOCFG_P6_DIR_O( 5);
//	GPIO_IOCFG_P6_DIR_O( 6);
//	GPIO_IOCFG_P6_DIR_O( 7);
//	// ����     6        
//	GPIO_IOCFG_P6_PUP_F( 1);
//	GPIO_IOCFG_P6_PUP_F( 2);
//	GPIO_IOCFG_P6_PUP_F( 3);
//	GPIO_IOCFG_P6_PUP_F( 4);
//	GPIO_IOCFG_P6_PUP_F( 5);
//	GPIO_IOCFG_P6_PUP_F( 6);
//	GPIO_IOCFG_P6_PUP_F( 7);
//	// ״̬     6        
//	GPIO_IOCFG_P6_SET_0( 1);
//	GPIO_IOCFG_P6_SET_0( 2);
//	GPIO_IOCFG_P6_SET_0( 3);
//	GPIO_IOCFG_P6_SET_0( 4);
//	GPIO_IOCFG_P6_SET_0( 5);
//	GPIO_IOCFG_P6_SET_0( 6);
//	GPIO_IOCFG_P6_SET_0( 7); 

// @brief P7�� �ܹ�5������ p7.5/6/7/ �����ֲ�Ĵ�������ʾ��5������ʵ�ʷ�װֻ��3�� SEG13/ SEG14/ SEG15
	GPIO_IOCFG_P7_DIR_I( 5);
	GPIO_IOCFG_P7_DIR_I( 6);
	GPIO_IOCFG_P7_DIR_I( 7);
	// ����     7        
	GPIO_IOCFG_P7_PUP_F( 5);
	GPIO_IOCFG_P7_PUP_F( 6);
	GPIO_IOCFG_P7_PUP_F( 7);
	// ״̬     7        
	GPIO_IOCFG_P7_SET_0( 5);
	GPIO_IOCFG_P7_SET_0( 6);
	GPIO_IOCFG_P7_SET_0( 7);

//// @brief P8�� �ܹ�2������ p8.6/7 SDA/ SCL
//	GPIO_IOCFG_P8_DIR_O( 6);
//	GPIO_IOCFG_P8_DIR_O( 7);
//	// ����     8        
//	GPIO_IOCFG_P8_PUP_F( 6);
//	GPIO_IOCFG_P8_PUP_F( 7);
//	// ״̬     8        
//	GPIO_IOCFG_P8_SET_1( 6);
//	GPIO_IOCFG_P8_SET_1( 7); 

// @brief P9�� �ܹ�8������ p9.2/3/4/5/6/7   COM1-COM6 /  
	GPIO_IOCFG_P9_DIR_I( 2);
	GPIO_IOCFG_P9_DIR_I( 3);
	GPIO_IOCFG_P9_DIR_I( 4);
	GPIO_IOCFG_P9_DIR_I( 5);
	GPIO_IOCFG_P9_DIR_I( 6);
	GPIO_IOCFG_P9_DIR_I( 7);	
	// ����     9         
	GPIO_IOCFG_P9_PUP_F( 2);
	GPIO_IOCFG_P9_PUP_F( 3);
	GPIO_IOCFG_P9_PUP_F( 4);
	GPIO_IOCFG_P9_PUP_F( 5);
	GPIO_IOCFG_P9_PUP_F( 6);
	GPIO_IOCFG_P9_PUP_F( 7);
	// ״̬     9         
	GPIO_IOCFG_P9_SET_0( 2);
	GPIO_IOCFG_P9_SET_0( 3); 
	GPIO_IOCFG_P9_SET_0( 4);
	GPIO_IOCFG_P9_SET_0( 5); 
	GPIO_IOCFG_P9_SET_0( 6);
	GPIO_IOCFG_P9_SET_0( 7); 

} 

#else
static void ApiPwOff_McuGpioInit(void)
{
	// @brief P0�� �ܹ�4������ p0.1/2/3/7  Relay1/Relay2/Null/Null
	// ����
	GPIO_IOCFG_P0_DIR_I( 1);// 01 ��բ 10 ��բ
	GPIO_IOCFG_P0_DIR_I( 2);
	GPIO_IOCFG_P0_DIR_I( 3);
	GPIO_IOCFG_P0_DIR_I( 7);
	// ����
	GPIO_IOCFG_P0_PUP_F( 1);
	GPIO_IOCFG_P0_PUP_F( 2);
	GPIO_IOCFG_P0_PUP_F( 3);
	GPIO_IOCFG_P0_PUP_F( 7);
	// ״̬
	GPIO_IOCFG_P0_SET_0( 1);
	GPIO_IOCFG_P0_SET_0( 2);
	GPIO_IOCFG_P0_SET_0( 3);
	GPIO_IOCFG_P0_SET_0( 7);
	// ���ģʽѡ��
	GPIO_IOCFG_P0_OUT_N( 1);	// ��������
	GPIO_IOCFG_P0_OUT_N( 2);
	GPIO_IOCFG_P0_OUT_N( 3);
	GPIO_IOCFG_P0_OUT_N( 7);
	// �˿��������������ģʽѡ��
	GPIO_IOCFG_P0_OUTH_WEAKEN( 1);
	GPIO_IOCFG_P0_OUTH_WEAKEN( 2);
	GPIO_IOCFG_P0_OUTH_WEAKEN( 3);
	GPIO_IOCFG_P0_OUTH_WEAKEN( 7);
	// ��������ģʽѡ��Ĵ���
	GPIO_IOCFG_P0_PUPM_SWITCH( 1);
	GPIO_IOCFG_P0_PUPM_SWITCH( 2);
	GPIO_IOCFG_P0_PUPM_SWITCH( 3);
	GPIO_IOCFG_P0_PUPM_SWITCH( 7);
	// �˿�������0Դѡ��Ĵ���
	GPIO_IOCFG_P0_INM_DATA( 1);
	GPIO_IOCFG_P0_INM_DATA( 2);
	GPIO_IOCFG_P0_INM_DATA( 3);
	GPIO_IOCFG_P0_INM_DATA( 7);


// @brief P1�� �ܹ�3������ p1.0/3/4	 Null/LED_yellow/PFout
	// ����
	GPIO_IOCFG_P1_DIR_I( 0);
	GPIO_IOCFG_P1_DIR_I( 3);
	GPIO_IOCFG_P1_DIR_I( 4);
	// ����     1        
	GPIO_IOCFG_P1_PUP_F( 0);
	GPIO_IOCFG_P1_PUP_F( 3);
	GPIO_IOCFG_P1_PUP_F( 4);
	// ״̬     1        
	GPIO_IOCFG_P1_SET_0( 0);
	GPIO_IOCFG_P1_SET_0( 3);
	GPIO_IOCFG_P1_SET_0( 4);

// @brief P2�� �ܹ�3������ p2.2/6/7	DISPKEY / 485RXD / 485TXD
	GPIO_IOCFG_P2_DIR_I( 2);
	GPIO_IOCFG_P2_DIR_I( 6);
	GPIO_IOCFG_P2_DIR_I( 7);
	// ����     2        
	GPIO_IOCFG_P2_PUP_F( 2);
	GPIO_IOCFG_P2_PUP_F( 6);
	GPIO_IOCFG_P2_PUP_F( 7);
	// ״̬     2        
	GPIO_IOCFG_P2_SET_0( 2);
	GPIO_IOCFG_P2_SET_0( 6);
	GPIO_IOCFG_P2_SET_0( 7);
	// ���ģʽѡ��      
	GPIO_IOCFG_P2_OUT_N( 2);
	GPIO_IOCFG_P2_OUT_N( 6);
	GPIO_IOCFG_P2_OUT_N( 7);
	// �˿��������������ģʽѡ��
	GPIO_IOCFG_P2_OUTH_WEAKEN( 2);
	GPIO_IOCFG_P2_OUTH_WEAKEN( 6);
	GPIO_IOCFG_P2_OUTH_WEAKEN( 7);
	// ��������ģʽѡ��Ĵ���
	GPIO_IOCFG_P2_PUPM_SWITCH( 2);
	GPIO_IOCFG_P2_PUPM_SWITCH( 6);
	GPIO_IOCFG_P2_PUPM_SWITCH( 7);
	// �˿�������Դѡ��Ĵ���
	GPIO_IOCFG_P2_INM_DATA( 2);
	GPIO_IOCFG_P2_INM_DATA( 6);
	GPIO_IOCFG_P2_INM_DATA( 7);

// @brief P3�� �ܹ�3������ p3.0/1/4/5/6	 BT_RXD / BT_TXD / BT_RST/ BT_ATEN / BT_CTL
	GPIO_IOCFG_P3_DIR_I( 0);
	GPIO_IOCFG_P3_DIR_I( 1);
	GPIO_IOCFG_P3_DIR_I( 4);
	GPIO_IOCFG_P3_DIR_I( 5);
	GPIO_IOCFG_P3_DIR_I( 6);
	// ����     3        
	GPIO_IOCFG_P3_PUP_F( 0);
	GPIO_IOCFG_P3_PUP_F( 1);
	GPIO_IOCFG_P3_PUP_F( 4);
	GPIO_IOCFG_P3_PUP_F( 5);
	GPIO_IOCFG_P3_PUP_F( 6);
	// ״̬     3        
	GPIO_IOCFG_P3_SET_0( 0);
	GPIO_IOCFG_P3_SET_0( 1);
	GPIO_IOCFG_P3_SET_1( 4);	// 0��λ��1����λ
	GPIO_IOCFG_P3_SET_0( 5);
	GPIO_IOCFG_P3_SET_0( 6); 	// 0���磬1������
	// ���ģʽѡ��
	GPIO_IOCFG_P3_OUT_N( 0);
	GPIO_IOCFG_P3_OUT_N( 1);
	GPIO_IOCFG_P3_OUT_N( 4);
	GPIO_IOCFG_P3_OUT_N( 5);
	GPIO_IOCFG_P3_OUT_N( 6);

// @brief P4�� �ܹ�4������ p4.4/5/6/7 SEG9/SEG10/SEG11/SEG12
	GPIO_IOCFG_P4_DIR_I( 4);
	GPIO_IOCFG_P4_DIR_I( 5);
	GPIO_IOCFG_P4_DIR_I( 6);
	GPIO_IOCFG_P4_DIR_I( 7);
	// ����     4        
	GPIO_IOCFG_P4_PUP_F( 4);
	GPIO_IOCFG_P4_PUP_F( 5);
	GPIO_IOCFG_P4_PUP_F( 6);
	GPIO_IOCFG_P4_PUP_F( 7);
	// ״̬     4        
	GPIO_IOCFG_P4_SET_0( 4);
	GPIO_IOCFG_P4_SET_0( 5);
	GPIO_IOCFG_P4_SET_0( 6);
	GPIO_IOCFG_P4_SET_0( 7);

// @brief P5�� �ܹ�8������ p5.0/1/2/3/4/5/6/7	SEG13 / SEG14 / I_J / NULL / DCK / TDI /TMS / TDO
	GPIO_IOCFG_P5_DIR_I( 0);
	GPIO_IOCFG_P5_DIR_I( 1);
	GPIO_IOCFG_P5_DIR_I( 2);
	GPIO_IOCFG_P5_DIR_I( 3);
	GPIO_IOCFG_P5_DIR_I( 4);
	GPIO_IOCFG_P5_DIR_I( 5);
	GPIO_IOCFG_P5_DIR_I( 6);
	GPIO_IOCFG_P5_DIR_I( 7);
	// ����     5        
	GPIO_IOCFG_P5_PUP_F( 0);
	GPIO_IOCFG_P5_PUP_F( 1);
	GPIO_IOCFG_P5_PUP_F( 2);
	GPIO_IOCFG_P5_PUP_F( 3);
	GPIO_IOCFG_P5_PUP_F( 4);
	GPIO_IOCFG_P5_PUP_F( 5);
	GPIO_IOCFG_P5_PUP_F( 6);
	GPIO_IOCFG_P5_PUP_F( 7);
	// ״̬     5        
	GPIO_IOCFG_P5_SET_0( 0);
	GPIO_IOCFG_P5_SET_0( 1);
	GPIO_IOCFG_P5_SET_0( 2);
	GPIO_IOCFG_P5_SET_0( 3);
	GPIO_IOCFG_P5_SET_0( 4);
	GPIO_IOCFG_P5_SET_0( 5);
	GPIO_IOCFG_P5_SET_0( 6);
	GPIO_IOCFG_P5_SET_0( 7);

// @brief P6�� �ܹ�7������ p6.1/2/3/4/5/6/7   SEG8/ SEG7/ SEG6/ SEG5/ SEG4/ SEG3/ SEG2
	GPIO_IOCFG_P6_DIR_I( 1);
	GPIO_IOCFG_P6_DIR_I( 2);
	GPIO_IOCFG_P6_DIR_I( 3);
	GPIO_IOCFG_P6_DIR_I( 4);
	GPIO_IOCFG_P6_DIR_I( 5);
	GPIO_IOCFG_P6_DIR_I( 6);
	GPIO_IOCFG_P6_DIR_I( 7);
	// ����     6        
	GPIO_IOCFG_P6_PUP_F( 1);
	GPIO_IOCFG_P6_PUP_F( 2);
	GPIO_IOCFG_P6_PUP_F( 3);
	GPIO_IOCFG_P6_PUP_F( 4);
	GPIO_IOCFG_P6_PUP_F( 5);
	GPIO_IOCFG_P6_PUP_F( 6);
	GPIO_IOCFG_P6_PUP_F( 7);
	// ״̬     6        
	GPIO_IOCFG_P6_SET_0( 1);
	GPIO_IOCFG_P6_SET_0( 2);
	GPIO_IOCFG_P6_SET_0( 3);
	GPIO_IOCFG_P6_SET_0( 4);
	GPIO_IOCFG_P6_SET_0( 5);
	GPIO_IOCFG_P6_SET_0( 6);
	GPIO_IOCFG_P6_SET_0( 7); 

// @brief P7�� �ܹ�5������ p7.0/1/5/ �����ֲ�Ĵ�������ʾ��5������ʵ�ʷ�װֻ��3�� SEG1/ NULL/ NULL
	GPIO_IOCFG_P7_DIR_I( 0);
	GPIO_IOCFG_P7_DIR_I( 1);
	GPIO_IOCFG_P7_DIR_I( 5);
	// ����     7        
	GPIO_IOCFG_P7_PUP_F( 0);
	GPIO_IOCFG_P7_PUP_F( 1);
	GPIO_IOCFG_P7_PUP_F( 5);
	// ״̬     7        
	GPIO_IOCFG_P7_SET_0( 0);
	GPIO_IOCFG_P7_SET_0( 1);
	GPIO_IOCFG_P7_SET_0( 5);

// @brief P8�� �ܹ�2������ p8.6/7 SDA/ SCL
	GPIO_IOCFG_P8_DIR_I( 6);
	GPIO_IOCFG_P8_DIR_I( 7);
	// ����     8        
	GPIO_IOCFG_P8_PUP_F( 6);
	GPIO_IOCFG_P8_PUP_F( 7);
	// ״̬     8        
	GPIO_IOCFG_P8_SET_0( 6);
	GPIO_IOCFG_P8_SET_0( 7); 

// @brief P9�� �ܹ�8������ p9.0/1/2/3/4/5/6/7   WP/ LED_CTL/ COM1-COM6 / 
	GPIO_IOCFG_P9_DIR_I( 0);	
	GPIO_IOCFG_P9_DIR_I( 1);	// �����ó�����,����ϵ��ʱ����һ��
	GPIO_IOCFG_P9_DIR_I( 2);
	GPIO_IOCFG_P9_DIR_I( 3);
	GPIO_IOCFG_P9_DIR_I( 4);
	GPIO_IOCFG_P9_DIR_I( 5);
	GPIO_IOCFG_P9_DIR_I( 6);
	GPIO_IOCFG_P9_DIR_I( 7);	
	// ����     9        
	GPIO_IOCFG_P9_PUP_F( 0);
	GPIO_IOCFG_P9_PUP_F( 1);
	GPIO_IOCFG_P9_PUP_F( 2);
	GPIO_IOCFG_P9_PUP_F( 3);
	GPIO_IOCFG_P9_PUP_F( 4);
	GPIO_IOCFG_P9_PUP_F( 5);
	GPIO_IOCFG_P9_PUP_F( 6);
	GPIO_IOCFG_P9_PUP_F( 7);
	// ״̬     9        
	GPIO_IOCFG_P9_SET_0( 0);
	GPIO_IOCFG_P9_SET_0( 1);  // ������ʱ������
	GPIO_IOCFG_P9_SET_0( 2);
	GPIO_IOCFG_P9_SET_0( 3); 
	GPIO_IOCFG_P9_SET_0( 4);
	GPIO_IOCFG_P9_SET_0( 5); 
	GPIO_IOCFG_P9_SET_0( 6);
	GPIO_IOCFG_P9_SET_0( 7); 
}
#endif
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ��������uart     
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/

static void ApiPwOff_McuUartInit(void)
{
	SCON &= ~(SCON_RI | SCON_TI);
	IEN0 &= ~IEN0_ES0;
	
	SCON1 &= ~(SCON1_RI1 | SCON1_TI1);
	IEN1  &= ~IEN1_ES1;
	 
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ����������ʾ    
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/

static void ApiPwOff_McuDispInit(void)
{
	LCDDrv_Init(POWER_OFF);
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    �������ü���ģ��   
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/

static void ApiPwOff_EmuInit(void)
{
	ApiMS_DisOrEnable(EMU_DISENABLE);
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    �������ģʽ  
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/

static void ApiPwOff_McuEnterSleep(void)
{
//	ENTER_POWERDWN();
}



