/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    AppMeasure.c                                                                          
**** Brief:       计量相关操作文件，如校表，瞬时量等。                                                                      
**** Author:      peter.he@chint.com                                                                 
**** Version:     V1.0                                                                               
**** Date:        2016-7-14                                                                          
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

/*--------------------------------- 文件功能说明 -------------------------------------------------------*/
/*
 *  该文件所有函数的前缀为xxxx_
 *  文件主函数和对外函数需放在文件的首部，并且主函数需要放在第一个位置;
 *  函数注释采用标准模板，函数内部注释采用//;
 *  对于注释较多的部分，可以增加一个注释符，然后详细说明放在文件的尾部;
 *--------------------------------- 文件功能说明 -------------------------------------------------------*/
 
/**有形参的函数格式:*/
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    xx任务处理函数
 *
 *  @param    xx :
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
/**无形参的函数格式:*/
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    上电所有口线配置成初始状态，后面可根据需要开启和配置
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
 
 
/*----------------< 包含文件 >----------------------------------*/
#include "..\SourceFiles\PUB\Include.h"

/*----------------< 宏定义区 >----------------------------------*/


/*----------------< 常量定义 >----------------------------------*/


/*----------------< 变量定义 >----------------------------------*/


/*----------------< 函数声明 >----------------------------------*/
void ApiMS_UpdateUIP(void);
void ApiMS_MeasureTask(void);
void ApiMS_EnergyPulseUpdate(void);
uchar8 ApiMS_EnergyProcess( GStr_ENERGY_PULSE_Type *p_strEnergyPulse );
uchar8 ApiMS_CalibrationMeterComm( uchar8 v_ucChID );
void ApiMS_InitMeterICPara( void );
void ApiMS_MeterICParaCheck( void );
uchar8 ApiMS_GetPowerDir( void );
void ApiMS_DisOrEnable( uchar8 v_ucWorkMode);
/*----------------< 函数定义 >----------------------------------*/



/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    电能计量任务处理，每个循环查询，有脉冲就处理，没有就直接退出，本文件的主入口函数，main函数调用
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
 
void ApiMS_MeasureTask(void)
{

	///* 脉冲电量更新处理  每个循环做一次 *///
	ApiMS_EnergyPulseUpdate();
	
	/* 更新瞬时量，1s更新一次 */
	ApiMS_UpdateUIP();
	
	
}
 
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    脉冲电量处理函数，脉冲增量不为0则进行处理，否则退出
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
		GStr_Counter.ucRelayon_Cnt = 0;	//清合闸口线计数器，有脉冲产生，则认为是合闸状态，需清零
		#endif
		
		///* 判断一下功率方向 *///
		V_ucDirection = ApiMS_GetPowerDir();
		
		GStr_EnergyPulseFw.ucPulseStatu |= F_PULSESTATU_BUSY;		///* 表示脉冲正在处理 *///
		V_ucPulseAdd = GStr_EnergyPulseFw.ucPulseAdd;
		GStr_EnergyPulseFw.ucPulseAdd = 0;
		
		if ( _FAILED == ApiPwOn_EnergyZSCheck() ) return;			///* 整数校验一下，如果错误就返回，不做处理，避免用错误的数据得到错误的结果 *///
		
		GStr_EnergyPulseFw.ucaPulseRemain[0] += V_ucPulseAdd;		///* 反向正计，不管正向反向都累加,反向单独累加 *///
		if ( _FALSE == V_ucDirection )	
		{
			GStr_EnergyPulseBk.ucaPulseRemain[0] += V_ucPulseAdd;
		}
		
		///* 正向电量处理 *///
		if ( _FALSE == ApiMS_EnergyProcess( &GStr_EnergyPulseFw) )
		{
			
		}
		if ( _FALSE == ApiMS_EnergyProcess( &GStr_EnergyPulseBk ) )
		{
			
		}
		
		
		GStr_EnergyPulseFw.ucPulseStatu &= ~F_PULSESTATU_BUSY;		///* 处理完了，把状态恢复到处理结束状态 */// 
	}
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    电量处理函数，小数和整数,同时会触发金额扣减相关操作
 *
 *  @param    *p_strEnergyPulse : 电量结构体指针
 *
 *  @return   _FALSE:尾数太大，不做处理；_TURE：处理成功
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
	///* 如果尾数太大，则清零退出 *///
	if ( p_strEnergyPulse->ucaPulseRemain[0] > (GStr_FunConfigPara.ucFunMeterConst*3) ) 
	{
		p_strEnergyPulse->ucaPulseRemain[0] = 0;
		return _FALSE;
	}
	p_strEnergyPulse->ucPulseStatu &= ~F_PULSESTATU_Add1;
	/*------------------------------------------------------------------------------------------------------*/
	///* 每0.01kWh刷新一下电量 *///
	while ( p_strEnergyPulse->ucaPulseRemain[0] >= GStr_FunConfigPara.ucFunMeterConst )
	{
		GStr_Flag.ucRunState2 |=F_RUN_Current_State;
		p_strEnergyPulse->ucaPulseRemain[0] -=  GStr_FunConfigPara.ucFunMeterConst;
		
		p_strEnergyPulse->ucPulseDecimal++;				///* 小数电量进位0.01 *///
		p_strEnergyPulse->ucPulseStatu |= F_PULSESTATU_Add1;			///* 0.01kWh进位标志 *///
		
		if ( p_strEnergyPulse->ucPulseDecimal >= 100 )	///* 小数电量到100以后表示整数要进位，小数归零 *///
		{ 
			p_strEnergyPulse->ucPulseStatu |= F_PULSESTATU_1KWH; 
		}
		
		/*-------------------------------------------------------------------------------------------------*/
		///* 小数电量存E2 *///
		if ( p_strEnergyPulse == &GStr_EnergyPulseFw )	///* 正向小数进位 *///
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
		
		ApiPwOn_DLXS_READ( p_strEnergyPulse, V_usE2pIndex ); // 每次从这里读一下，更新一下小数电量和指针
		p_strEnergyPulse->ucPulseDecimal++;	///上面读出的小数位数是上次的，还需要加1
		p_strEnergyPulse->ucPulseDecSaveNoFF = (p_strEnergyPulse->ucPulseDecSaveNoFF >> 1) | 0x80;
		LibPub_WriteDataToE2prom(V_usE2pIndex, p_strEnergyPulse->ucPulseDecSavePtr, &p_strEnergyPulse->ucPulseDecSaveNoFF ) ;
		
	}
	
	/*------------------------------------------------------------------------------------------------------*/
	///* 整度进位，保存一下E2 *///
	if ( p_strEnergyPulse->ucPulseStatu & F_PULSESTATU_1KWH )
	{
		V_ucaTempBuff[0] = 0x00;
		V_ucaTempBuff[1] = 0x00;
		V_ucaTempBuff[2] = 0x01;
		if ( p_strEnergyPulse == &GStr_EnergyPulseFw )	///* 电量整度进位 *///
		{ 
			LibPub_NBtyesBcdAdd( &GStr_Energy.ucaFw_Energy[0], &V_ucaTempBuff[0], 3 ); 
		}
		else
		{
			LibPub_NBtyesBcdAdd( &GStr_Energy.ucaBk_Energy[0], &V_ucaTempBuff[0], 3 );
		}
		
		/*---------------------------------------------------------------------------------------*/
		///* 进位完成后，写一下E2 *///
		LibPub_WriteDataToE2prom( LIB_E2P_ENRGY, 0, &GStr_Energy.ucaFw_Energy[0] );
		
		///* 整度进位以后,清除小数电量部分，注意：清除小数后指针下次计算是就是0*///
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
	// 如果是正向，这里要做一下金额扣减处理
	if ( p_strEnergyPulse == &GStr_EnergyPulseFw ) 
	{
		ApiMoney_RemainMoneyProcess();
	}
	ApiRelay_SubtractMoneyRelayJudge();///根据剩余金额判断下继电器是否动作
	ApiRelay_ControlProcess();
	
	p_strEnergyPulse->ucPulseStatu &= ~F_PULSESTATU_1KWH; 
	
	/*------------------------------------------------------------------------------------------------------*/
	return _TRUE;
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    更新瞬时量，1s更新一次
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
		
		/* 开始更新瞬时量数据，电压、电流、功率、频率、功率因数等 */
		ApiEMU_UpdateUIP();

	}
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    通信读emu寄存器地址 
 *
 *  @param    v_ucChID : 通信通道
 *  @param    p_ulEmuRegData : 要返回的数据
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
///* FE FE FE FE 68 00 00 00 00 00 00 68 2E 04 [33 33 39 B3] cs 16   8006xxxx*///
///* FE FE FE FE 68 00 00 00 00 00 00 68 2E 04 [33 36 34 B3] cs 16   80010300 功率原始值*///
///* 支持8003xxxx和8004xxxx

///* fe fe fe fe 68	A0 … A5 68 2F 0C DI0-DI3 PA P0-P2 C0-C3 N1-Nn CS	16  *///
///* 0  1     3  4  5     10          14      18       22                   *///
uchar8 ApiMS_CalibrationMeterComm( uchar8 v_ucChID )
{
	#if ( METER_TYPE != METER_TYPE_DTSY666)
	ushort16 V_usRegAddress;		// 寄存器地址
	ulong32  V_ulResult, V_ulRegData;
	#else
	uchar8   V_WriteData[4],V_Addr;
	#endif
	ulong32  V_ulDI3DI2DI1DI0;
	uchar8   V_ucErrorType = _SUCCESS;

	
	// Brief: 准备一下数据标识
	V_ulDI3DI2DI1DI0  = (ulong32) Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0];
	V_ulDI3DI2DI1DI0 |= (ulong32) Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+1]<<8;
	V_ulDI3DI2DI1DI0 |= (ulong32) Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+2]<<16;
	V_ulDI3DI2DI1DI0 |= (ulong32) Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+3]<<24;
	

	// Brief: 解析一下地址
	#if ( METER_TYPE != METER_TYPE_DTSY666)
	V_usRegAddress  = Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+1];	///* 高地址 *///
	V_usRegAddress  = (V_usRegAddress<<8) & 0xff00;
	V_usRegAddress |= Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA];		///* 低地址 *///
	#else
	V_Addr=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA];
	#endif
	
	// Brief: 读寄存器
	if( API_DLT645_CMD_RD_EMU_REG == Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_CMD] )
	{			 
		// Brief: 开始读取寄存器值 
		#if ( METER_TYPE != METER_TYPE_DTSY666)
		V_ulResult = ApiEMU_ReadEmuReg( V_usRegAddress );
		
		// Brief: 通信数据赋值 
		Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+4] = (uchar8)(V_ulResult);
		Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+5] = (uchar8)(V_ulResult>>8);
		Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+6] = (uchar8)(V_ulResult>>16);
		Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+7] = (uchar8)(V_ulResult>>24); 
		V_ucErrorType = _SUCCESS; 
		#else 
		V_ucErrorType=AppEMU_TripReadEmuReg(v_ucChID);
		#endif
	}
	
	// 写寄存器,校表
	if( API_DLT645_CMD_WR_EMU_REG == Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_CMD] )
	{  
		#if ( METER_TYPE != METER_TYPE_DTSY666)
		// Brief:准备数据
		V_ulRegData  = (ulong32)Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+3] << 24;
		V_ulRegData |= (ulong32)Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+2] << 16;
		V_ulRegData |= (ulong32)Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+1] << 8;
		V_ulRegData |= (ulong32)Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+0];
		#else
		LibPub_MemExchangeBytes( &Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W], V_WriteData, 4);
		#endif
		
		// Brief: 开始处理校表
		switch ( Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+2] ) ///* 遍历DI2 *///
		{
			case 0x06:	///* 写指定寄存器 *///
			case 0x07:	///* 写指定寄存器 *///
			{
				#if ( METER_TYPE != METER_TYPE_DTSY666)
				ApiEMU_WriteEmuReg ( V_usRegAddress, V_ulRegData ); 	
				#else
				AppEMU_WriteOneReg_MeterIC(V_WriteData,V_Addr);
				#endif
			}break;
			
			case 0x00:	///* 起动校表,初始化校表寄存器，写hfconst 8000xxxx*///
			{
				switch(Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0])
				{
					case 0x00:  ///80000000起动校表
					{
						ApiEMU_CommStartCal(v_ucChID); 
					}break;
					#if ( METER_TYPE == METER_TYPE_DTSY666)
					case 0x01:////80000001参数设置
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
			
			case 0x02:	///* 结束校表 80020000 结束校表校一下潜动阈值 *///
			{
				ApiEMU_CommEndCal(v_ucChID);
			}break;
			
			case 0x01:	///* 误差调校80010X00*///
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
 *  @brief    计量初始化，主要是初始化计量芯片参数
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
 *  @brief    计量初始化，主要是初始化计量芯片参数
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
 *  @brief    获取功率方向
 *
 *  @return   _FALSE：反向  _TRUE：正向
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
 *  @brief    使能或关闭计量模块 
 *
 *  @param    v_ucWorkMode : EMU_ENABLE使能 EMU_DISENABLE：关闭
 *  @param    p_ulEmuRegData : 要返回的数据
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