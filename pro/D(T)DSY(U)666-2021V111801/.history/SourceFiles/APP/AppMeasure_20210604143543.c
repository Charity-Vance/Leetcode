/*******************************************************************************************************
**** Copyright��  (c)Copyright 2019,�㽭��̩�����Ǳ��������ι�˾,���ܱ�Ӧ���з�                       
****                            All rights reserved.                                                 
**** FileName:    AppMeasure.c                                                                          
**** Brief:       ������ز����ļ�����У��˲ʱ���ȡ�                                                                      
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
void ApiMS_UpdateUIP(void);
void ApiMS_MeasureTask(void);
void ApiMS_EnergyPulseUpdate(void);
uchar8 ApiMS_EnergyProcess( GStr_ENERGY_PULSE_Type *p_strEnergyPulse );
uchar8 ApiMS_CalibrationMeterComm( uchar8 v_ucChID );
void ApiMS_InitMeterICPara( void );
void ApiMS_MeterICParaCheck( void );
uchar8 ApiMS_GetPowerDir( void );
void ApiMS_DisOrEnable( uchar8 v_ucWorkMode);
/*----------------< �������� >----------------------------------*/



/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ���ܼ���������ÿ��ѭ����ѯ��������ʹ���û�о�ֱ���˳������ļ�������ں�����main��������
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
 
void ApiMS_MeasureTask(void)
{

	///* ����������´���  ÿ��ѭ����һ�� *///
	ApiMS_EnergyPulseUpdate();
	
	/* ����˲ʱ����1s����һ�� */
	ApiMS_UpdateUIP();
	
	
}
 
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    �������������������������Ϊ0����д��������˳�
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
 
void ApiMS_EnergyPulseUpdate(void)
{
	uchar8  V_ucDirection;
	ulong32 V_ulPowerReg = 0;
	uchar8	V_ucPulseAdd = 0;
	
	if ( GStr_EnergyPulseFw.ucPulseAdd )
	{
		#if(METER_TYPE==METER_TYPE_DTSY666)	
		GStr_Counter.ucRelayon_Cnt = 0;	//���բ���߼����������������������Ϊ�Ǻ�բ״̬��������
		#endif
		
		///* �ж�һ�¹��ʷ��� *///
		V_ucDirection = ApiMS_GetPowerDir();
		
		GStr_EnergyPulseFw.ucPulseStatu |= F_PULSESTATU_BUSY;		///* ��ʾ�������ڴ��� *///
		V_ucPulseAdd = GStr_EnergyPulseFw.ucPulseAdd;
		GStr_EnergyPulseFw.ucPulseAdd = 0;
		
		if ( _FAILED == ApiPwOn_EnergyZSCheck() ) return;			///* ����У��һ�£��������ͷ��أ��������������ô�������ݵõ�����Ľ�� *///
		
		GStr_EnergyPulseFw.ucaPulseRemain[0] += V_ucPulseAdd;		///* �������ƣ������������ۼ�,���򵥶��ۼ� *///
		if ( _FALSE == V_ucDirection )	
		{
			GStr_EnergyPulseBk.ucaPulseRemain[0] += V_ucPulseAdd;
		}
		
		///* ����������� *///
		if ( _FALSE == ApiMS_EnergyProcess( &GStr_EnergyPulseFw) )
		{
			
		}
		if ( _FALSE == ApiMS_EnergyProcess( &GStr_EnergyPulseBk ) )
		{
			
		}
		
		
		GStr_EnergyPulseFw.ucPulseStatu &= ~F_PULSESTATU_BUSY;		///* �������ˣ���״̬�ָ����������״̬ */// 
	}
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ������������С��������,ͬʱ�ᴥ�����ۼ���ز���
 *
 *  @param    *p_strEnergyPulse : �����ṹ��ָ��
 *
 *  @return   _FALSE:β��̫�󣬲�������_TURE������ɹ�
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/

uchar8 ApiMS_EnergyProcess( GStr_ENERGY_PULSE_Type *p_strEnergyPulse )
{
	uchar8	  V_ucaTempBuff[4] ;
	uchar8	  V_ucTemp08=0,V_ucCnt_i;
	ushort16  V_usE2pIndex = 0;

	/*------------------------------------------------------------------------------------------------------*/
	///* ���β��̫���������˳� *///
	if ( p_strEnergyPulse->ucaPulseRemain[0] > (GStr_FunConfigPara.ucFunMeterConst*3) ) 
	{
		p_strEnergyPulse->ucaPulseRemain[0] = 0;
		return _FALSE;
	}
	p_strEnergyPulse->ucPulseStatu &= ~F_PULSESTATU_Add1;
	/*------------------------------------------------------------------------------------------------------*/
	///* ÿ0.01kWhˢ��һ�µ��� *///
	while ( p_strEnergyPulse->ucaPulseRemain[0] >= GStr_FunConfigPara.ucFunMeterConst )
	{
		GStr_Flag.ucRunState2 |=F_RUN_Current_State;
		p_strEnergyPulse->ucaPulseRemain[0] -=  GStr_FunConfigPara.ucFunMeterConst;
		
		p_strEnergyPulse->ucPulseDecimal++;				///* С��������λ0.01 *///
		p_strEnergyPulse->ucPulseStatu |= F_PULSESTATU_Add1;			///* 0.01kWh��λ��־ *///
		
		if ( p_strEnergyPulse->ucPulseDecimal >= 100 )	///* С��������100�Ժ��ʾ����Ҫ��λ��С������ *///
		{ 
			p_strEnergyPulse->ucPulseStatu |= F_PULSESTATU_1KWH; 
		}
		
		/*-------------------------------------------------------------------------------------------------*/
		///* С��������E2 *///
		if ( p_strEnergyPulse == &GStr_EnergyPulseFw )	///* ����С����λ *///
		{
			V_usE2pIndex = LIB_E2P_ENERGY_DECPULSE_FW;
			GStr_Energy.ucaFw_Energy[3] = LibPub_1Hex_2_1BCD( p_strEnergyPulse->ucPulseDecimal );  
			GStr_Flag.ucMoney |= F_SYS_MONEY_MoneyDEC;
		}
		else
		{
			V_usE2pIndex = LIB_E2P_ENERGY_DECPULSE_BK; 
			GStr_Energy.ucaBk_Energy[3] = LibPub_1Hex_2_1BCD( p_strEnergyPulse->ucPulseDecimal  );  
		}
		
		ApiPwOn_DLXS_READ( p_strEnergyPulse, V_usE2pIndex ); // ÿ�δ������һ�£�����һ��С��������ָ��
		p_strEnergyPulse->ucPulseDecimal++;	///���������С��λ�����ϴεģ�����Ҫ��1
		p_strEnergyPulse->ucPulseDecSaveNoFF = (p_strEnergyPulse->ucPulseDecSaveNoFF >> 1) | 0x80;
		LibPub_WriteDataToE2prom(V_usE2pIndex, p_strEnergyPulse->ucPulseDecSavePtr, &p_strEnergyPulse->ucPulseDecSaveNoFF ) ;
		
	}
	
	/*------------------------------------------------------------------------------------------------------*/
	///* ���Ƚ�λ������һ��E2 *///
	if ( p_strEnergyPulse->ucPulseStatu & F_PULSESTATU_1KWH )
	{
		V_ucaTempBuff[0] = 0x00;
		V_ucaTempBuff[1] = 0x00;
		V_ucaTempBuff[2] = 0x01;
		if ( p_strEnergyPulse == &GStr_EnergyPulseFw )	///* �������Ƚ�λ *///
		{ 
			LibPub_NBtyesBcdAdd( &GStr_Energy.ucaFw_Energy[0], &V_ucaTempBuff[0], 3 ); 
		}
		else
		{
			LibPub_NBtyesBcdAdd( &GStr_Energy.ucaBk_Energy[0], &V_ucaTempBuff[0], 3 );
		}
		
		/*---------------------------------------------------------------------------------------*/
		///* ��λ��ɺ�дһ��E2 *///
		LibPub_WriteDataToE2prom( LIB_E2P_ENRGY, 0, &GStr_Energy.ucaFw_Energy[0] );
		
		///* ���Ƚ�λ�Ժ�,���С���������֣�ע�⣺���С����ָ���´μ����Ǿ���0*///
		V_ucTemp08 = 0;
		p_strEnergyPulse->ucPulseDecimal = 0;
		for( V_ucCnt_i=0; V_ucCnt_i<13; V_ucCnt_i++ )
		{
			LibPub_WriteDataToE2prom(V_usE2pIndex, V_ucCnt_i, &V_ucTemp08 );
		}
		
		GStr_Flag.ucMoney |= F_SYS_MONEY_Money2E2;
	}
	else
	{
		GStr_Energy.usCRC16 = LibPub_CRC16_CCITT ( &GStr_Energy.ucaFw_Energy[0], GStr_ENERGY_Type_LEN-2);
	}
	
	/*------------------------------------------------------------------------------------------------------*/
	// �������������Ҫ��һ�½��ۼ�����
	if ( p_strEnergyPulse == &GStr_EnergyPulseFw ) 
	{
		ApiMoney_RemainMoneyProcess();
	}
	ApiRelay_SubtractMoneyRelayJudge();///����ʣ�����ж��¼̵����Ƿ���
	ApiRelay_ControlProcess();
	
	p_strEnergyPulse->ucPulseStatu &= ~F_PULSESTATU_1KWH; 
	
	/*------------------------------------------------------------------------------------------------------*/
	return _TRUE;
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ����˲ʱ����1s����һ��
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
 
void ApiMS_UpdateUIP(void)
{
	if ( _TRUE == LibPub_GetDiffTime( GStr_Monitor.ulUpDateUIPTime, LibPub_GetTimerBeat(), UIP_UPDATE_INTERVAL) ) 
	{
		GStr_Monitor.ulUpDateUIPTime = LibPub_GetTimerBeat();
		
		/* ��ʼ����˲ʱ�����ݣ���ѹ�����������ʡ�Ƶ�ʡ����������� */
		ApiEMU_UpdateUIP();

	}
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ͨ�Ŷ�emu�Ĵ�����ַ 
 *
 *  @param    v_ucChID : ͨ��ͨ��
 *  @param    p_ulEmuRegData : Ҫ���ص�����
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
///* FE FE FE FE 68 00 00 00 00 00 00 68 2E 04 [33 33 39 B3] cs 16   8006xxxx*///
///* FE FE FE FE 68 00 00 00 00 00 00 68 2E 04 [33 36 34 B3] cs 16   80010300 ����ԭʼֵ*///
///* ֧��8003xxxx��8004xxxx

///* fe fe fe fe 68	A0 �� A5 68 2F 0C DI0-DI3 PA P0-P2 C0-C3 N1-Nn CS	16  *///
///* 0  1     3  4  5     10          14      18       22                   *///
uchar8 ApiMS_CalibrationMeterComm( uchar8 v_ucChID )
{
	#if ( METER_TYPE != METER_TYPE_DTSY666)
	ushort16 V_usRegAddress;		// �Ĵ�����ַ
	ulong32  V_ulResult, V_ulRegData;
	#else
	uchar8   V_WriteData[4],V_Addr;
	#endif
	ulong32  V_ulDI3DI2DI1DI0;
	uchar8   V_ucErrorType = _SUCCESS;

	
	// Brief: ׼��һ�����ݱ�ʶ
	V_ulDI3DI2DI1DI0  = (ulong32) Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0];
	V_ulDI3DI2DI1DI0 |= (ulong32) Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+1]<<8;
	V_ulDI3DI2DI1DI0 |= (ulong32) Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+2]<<16;
	V_ulDI3DI2DI1DI0 |= (ulong32) Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+3]<<24;
	

	// Brief: ����һ�µ�ַ
	#if ( METER_TYPE != METER_TYPE_DTSY666)
	V_usRegAddress  = Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+1];	///* �ߵ�ַ *///
	V_usRegAddress  = (V_usRegAddress<<8) & 0xff00;
	V_usRegAddress |= Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA];		///* �͵�ַ *///
	#else
	V_Addr=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA];
	#endif
	
	// Brief: ���Ĵ���
	if( API_DLT645_CMD_RD_EMU_REG == Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_CMD] )
	{			 
		// Brief: ��ʼ��ȡ�Ĵ���ֵ 
		#if ( METER_TYPE != METER_TYPE_DTSY666)
		V_ulResult = ApiEMU_ReadEmuReg( V_usRegAddress );
		
		// Brief: ͨ�����ݸ�ֵ 
		Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+4] = (uchar8)(V_ulResult);
		Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+5] = (uchar8)(V_ulResult>>8);
		Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+6] = (uchar8)(V_ulResult>>16);
		Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+7] = (uchar8)(V_ulResult>>24); 
		V_ucErrorType = _SUCCESS; 
		#else 
		V_ucErrorType=AppEMU_TripReadEmuReg(v_ucChID);
		#endif
	}
	
	// д�Ĵ���,У��
	if( API_DLT645_CMD_WR_EMU_REG == Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_CMD] )
	{  
		#if ( METER_TYPE != METER_TYPE_DTSY666)
		// Brief:׼������
		V_ulRegData  = (ulong32)Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+3] << 24;
		V_ulRegData |= (ulong32)Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+2] << 16;
		V_ulRegData |= (ulong32)Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+1] << 8;
		V_ulRegData |= (ulong32)Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+0];
		#else
		LibPub_MemExchangeBytes( &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W], V_WriteData, 4);
		#endif
		
		// Brief: ��ʼ����У��
		switch ( Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+2] ) ///* ����DI2 *///
		{
			case 0x06:	///* дָ���Ĵ��� *///
			case 0x07:	///* дָ���Ĵ��� *///
			{
				#if ( METER_TYPE != METER_TYPE_DTSY666)
				ApiEMU_WriteEmuReg ( V_usRegAddress, V_ulRegData ); 	
				#else
				AppEMU_WriteOneReg_MeterIC(V_WriteData,V_Addr);
				#endif
			}break;
			
			case 0x00:	///* ��У��,��ʼ��У��Ĵ�����дhfconst 8000xxxx*///
			{
				switch(Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0])
				{
					case 0x00:  ///80000000��У��
					{
						ApiEMU_CommStartCal(v_ucChID); 
					}break;
					#if ( METER_TYPE == METER_TYPE_DTSY666)
					case 0x01:////80000001��������
					{
						AppEMU_TRipCommSetReg( v_ucChID );
					}break;
					#endif
					default:
					{
						V_ucErrorType = _FAILED;	
					}break;
				}
			}break;
			
			case 0x02:	///* ����У�� 80020000 ����У��Уһ��Ǳ����ֵ *///
			{
				ApiEMU_CommEndCal(v_ucChID);
			}break;
			
			case 0x01:	///* ����У80010X00*///
			{
				ApiEMU_CommErrCal(v_ucChID);
			}break;
			
			default: 
			{
				V_ucErrorType = _FAILED;			
			}break;
		}
		
	}
		
	return V_ucErrorType;
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ������ʼ������Ҫ�ǳ�ʼ������оƬ����
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/

void ApiMS_InitMeterICPara( void )
{
	ApiEMU_EMUInit();
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ������ʼ������Ҫ�ǳ�ʼ������оƬ����
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/

void ApiMS_MeterICParaCheck( void )
{
	ApiEMU_EMUParaCheck();
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ��ȡ���ʷ���
 *
 *  @return   _FALSE������  _TRUE������
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/

uchar8 ApiMS_GetPowerDir( void )
{
	return( ApiEMU_GetDirP() );

}
 /*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ʹ�ܻ�رռ���ģ�� 
 *
 *  @param    v_ucWorkMode : EMU_ENABLEʹ�� EMU_DISENABLE���ر�
 *  @param    p_ulEmuRegData : Ҫ���ص�����
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/

void ApiMS_DisOrEnable( uchar8 v_ucWorkMode)
{
	ApiEMU_DisOrEnable(v_ucWorkMode);

}