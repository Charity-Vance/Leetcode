
///*######################################################################*///
///* 头文件包含  *///
#include "..\SourceFiles\PUB\Include.h"

Gstr_VirtualEsam      GStr_VirtualEsamPara;
uchar8  GA_ucDisperFactor[8];
uchar8 GV_ucMACErrNum;

///*######################################################################*///
///* 函数声明 */// 
void PrepaymentModule_InValidation();
void PrepaymentModule_Comm_MACErrNum();
void PrepaymentModule_Comm_ClrMACErrNum();
uchar8 PrepaymentModule_Comm_INTAUTH(uchar8 *P_DataPtr);
uchar8 PrepaymentModule_Comm_ModifyKey(uchar8 *P_DataPtr);
uchar8 PrepaymentModule_Comm_OpenAccout(uchar8 *P_DataPtr);
uchar8 PrepaymentModule_Comm_HandBackMoney(uchar8 *P_DataPtr);
uchar8 PrepaymentModule_Comm_TimeAvailableIn(uchar8 *P_DataPtr);
uchar8 PrepaymentModule_DataEncription(uchar8 *P_DataPtr,uchar8 *P_ucLen);
uchar8 PrepaymentModule_DataDecription(uchar8 *P_DataPtr, uchar8 V_ucMACType, uchar8 *P_ucLen);
uchar8 PrepaymentModule_Comm_INTAUTH_Invalidation(uchar8 *P_DataPtr);
uchar8 PrepaymentModule_Comm_Control(uchar8 *P_DataPtr);
uchar8 PrepaymentModule_GetWorkkey(uchar8 V_ucKeyNum); 
uchar8 PrepaymentModule_CommWriteESAMBinaryMAC(uchar8 *P_ucData, uchar8 V_ucLen, uchar8 V_ucHeadNum, uchar8 V_ucType);
uchar8 PrepaymentModule_GetChallenge(uchar8 *P_DataPtr, uchar8 V_DataLen);
uchar8 PrepaymentModule_Comm_Excerption(uchar8 *P_DataPtr);
uchar8 PrepaymentModule_Comm_StateQuery(uchar8 *P_DataPtr);
uchar8 Money_Recharge( uchar8 V_ProcessType);
void ApiEvent_WriteRecord(uchar8 v_ucEventType);

///***********************************************************************************///
///*PrepaymentModule_Comm_INTAUTH                                                    *///
///*Description：远程身份认证                                                        *///
///*Input：*P_DataPoint为入口数据指针DI0                                             *///      
///*                                                                                 *///
///*                                                                                 *///
///*Output：返回值=C_OK：操作正常                                                    *///
///*              =C_ERR：操作异常                                                   *///
///*Calls：                                                                          *///
///*Called By：                                                                      *///
///*Influence：                                                                      *///
///*Tips：函数正确执行后自动将需要应答的数据保存到通讯缓存相应地址                   *///
///*Others：                                                                         *///
///*Author:chenshou                                                                  *///
///***********************************************************************************///
///*frame::FE FE FE FE 68 A0 A1 A2 A3 A4 A5 68 03 L  DI0 DI1 DI2 DI3 C0 C1 C2 C3 N1...Nm CS 16*///
///*offset:0  1  2  3  4  5  6  4  8  9  10 11 12 13 14  15  16  17  18 19 20 21 22...........*/// 
///*接收8-15密文1   16-23随机数  24-31分散因子*/// 
///*ACKNo: FE FE FE FE 68 A0 A1 A2 A3 A4 A5 68 C3 02 SERR  CS  16 异常应答*///
uchar8 PrepaymentModule_Comm_INTAUTH(uchar8 *P_ucDataPtr)
{
	uchar8	 k;
    uchar8   V_ucBuffer[3];
	 uchar8   V_uctest[16];
	
	LibPub_Inverse (P_ucDataPtr+24, 8); ///表号倒序
	if(LibPub_CompareData(&GStr_MeterIFO.ucaMeterID[0],P_ucDataPtr+26,6,CMP_MODE_HIGHT)!=C_Equal)///*命令帧中下发的表号与实际表号不同，则返回错误*///
	{B_Err_Other=1;return C_ERR;}

	///* 数据倒向，低位在前倒为高位在前 *///
	for ( k = 0; k < 2; k++ )
	{ LibPub_Inverse (P_ucDataPtr+8+8*k, 0x08); }
	
	LibPub_MemCopyBytes ( P_ucDataPtr+16, &GStr_VirtualEsamPara.ucRs485RandNum[0], 0x08);	///*存随机数1*///
	LibPub_MemCopyBytes ( P_ucDataPtr+24, &GA_ucDisperFactor[0], 0x08);     				///*存分散因子*///
	
	///* 3DES加密分散因子得到临时密钥，密钥存在GA_ucDesKey中*///
	if( C_ERR == PrepaymentModule_GetWorkkey(C_KeyNum00) )
	{ B_Err_IDAuthenFail=1; return C_ERR; }

	///* 3DES加密随机数，得到密文 *///
	if( C_ERR == TripleDES_DeOrEncryption( C_KeyNumTp, P_ucDataPtr+16, ENCRYPTION) )
	{ B_Err_IDAuthenFail=1; return C_ERR; }
	LibPub_MemCopyBytes ( P_ucDataPtr+16, V_uctest, 0x08);
	LibPub_MemCopyBytes ( P_ucDataPtr+8, &V_uctest[7], 0x08);

	///* 比较随机数密文和上位机传过来的密文，相等则继续，错误退出 */// 
	if ( C_Equal != LibPub_CompareData ( P_ucDataPtr+8, P_ucDataPtr+16, 0x08,CMP_MODE_HIGHT ) )
	{ B_Err_IDAuthenFail=1; return C_ERR; }
	
	
	///* 获取随机数2，以便使用后续的认证操作 */// 
	if(GStr_Flag.ucRunState3&F_RUN_READ_RANDOM2)///读取过随机数，直接回提前返回的随机数
	{
			LibPub_MemCopyBytes(&GStr_VirtualEsamPara.ucRs485RandNum2[0], &GStr_VirtualEsamPara.ucRs485RandNum[0], 4);
	}
	else///没读取过随机数2，要重新生成随机数
	{
			if( C_ERR == PrepaymentModule_GetChallenge(&GStr_VirtualEsamPara.ucRs485RandNum[0], 0x04) )
			{ B_Err_IDAuthenFail=1; return C_ERR; }  
	}

   LibPub_MemSetBytes(&GStr_VirtualEsamPara.ucRs485RandNum[4], 0x00, 4);
   LibPub_MemExchangeBytes(&GStr_VirtualEsamPara.ucRs485RandNum[0], P_ucDataPtr+4, 0x04 );	///* 数据倒向以便数据返回 *///
   
	///* 获取ESAM序列号(表号) *///
	*(P_ucDataPtr+14) = 0x00;
	*(P_ucDataPtr+15) = 0x00;
	LibPub_MemExchangeBytes( &GStr_MeterIFO.ucaMeterID[0], P_ucDataPtr+8, 6); 

	///* 身份认证有效时长 */// 
	if ( _FAILED == LibPub_ReadDataFromE2prom(LIB_E2P_AvailTimer, 0, &V_ucBuffer[0] ))
	{
 		GStr_AVAIL.ulAutRemainingTime = C_AvailTimer;  ///*如果读失败，默认时效为5min*///
	}
	else
	{  		
		V_ucBuffer[0] = LibPub_1BCD_2_1HEX(V_ucBuffer[0]);
		GStr_AVAIL.ulAutRemainingTime = (ulong32)V_ucBuffer[0];
		V_ucBuffer[1] = LibPub_1BCD_2_1HEX(V_ucBuffer[1]);
		GStr_AVAIL.ulAutRemainingTime = GStr_AVAIL.ulAutRemainingTime * 100 + V_ucBuffer[1];	///*加入到分钟基本定时器中*///
		if ( GStr_AVAIL.ulAutRemainingTime == 0 )		///*如果数据为0，默认时效为5min*///
		{
			GStr_AVAIL.ulAutRemainingTime = C_AvailTimer;
		}
	}
	GStr_AVAIL.ulAutRemainingTime = GStr_AVAIL.ulAutRemainingTime*60;
	
	GStr_Flag.ucRunState2 |=F_RUN_INTAUTHAvailabilityFlag;///*置身份认证有效标志*/// 
	GStr_Flag.ucRunState2 |=F_RUN_FirstProgFlag;
	return(C_OK);   
}
///***********************************************************************************///
///*PrepaymentModule_Comm_TimeAvailableIn                                            *///
///*Description：远程身份认证时效设置                                                *///
///*Input：*P_DataPoint为入口数据指针DI0                                             *///      
///*                                                                                 *///
///*                                                                                 *///
///*Output：返回值=C_OK：操作正常                                                    *///
///*              =C_ERR：操作异常                                                   *///
///*Calls：                                                                          *///
///*Called By：                                                                      *///
///*Influence：                                                                      *///
///*Tips：函数正确执行后自动将需要应答的数据保存到通讯缓存相应地址                   *///
///*Others：执行时间63ms                                                             *///
///*Author:chenshou                                                                  *///
///***********************************************************************************///
///*frame::FE FE FE FE 68 A0 A1 A2 A3 A4 A5 68 03 L  DI0 DI1 DI2 DI3 C0 C1 C2 C3 N1...Nm CS 16*///
///*offset:0  1  2  3  4  5  6  4  8  9  10 11 12 13 14  15  16  17  18 19 20 21 22...........*///
///*接收22-23身份认证时效 24-27计算MAC*///
///*接收8-9身份认证时效   10-13计算MAC  *///
///*ACKNo: FE FE FE FE 68 A0 A1 A2 A3 A4 A5 68 C3 02 SERR  CS  16 异常应答*///
uchar8 PrepaymentModule_Comm_TimeAvailableIn(uchar8 *P_DataPtr)
{ 
	uchar8 V_Buffer[3] ;
	///* 身份认证超时 *///
    if(F_RUN_INTAUTHAvailabilityFlag!=( GStr_Flag.ucRunState2 &F_RUN_INTAUTHAvailabilityFlag))
	{
		B_Err_IDAuthenFail=1;  return C_ERR;
	} 
	
	///*网络数据倒向，低位在前倒为高位在前*///
	LibPub_Inverse(P_DataPtr + 8,0x02);              
	LibPub_Inverse(P_DataPtr + 10,0x04);
	
	///* 数据有效性判断 *///	
	if(   (LibPub_IsBCD(P_DataPtr + 8, 2))
		||( (*(P_DataPtr + 8) == 0) && (*(P_DataPtr + 9) == 0) ) ) 
	{ B_Err_Other=1; return C_ERR;  } 
	

	///* 验证MAC *///
	if(C_ERR == PrepaymentModule_CommWriteESAMBinaryMAC(P_DataPtr+8, 0x02, 11, 0x01) )
	{ B_Err_ESAMAuthenFail = 1;  return C_ERR; } 
	
	///* 更新身份认证有效时间 */// 
	if ( _SUCCESS == LibPub_ReadDataFromE2prom(LIB_E2P_AvailTimer, 0, &V_Buffer[0] ))
	{
		V_Buffer[0] = *(P_DataPtr+8);
		V_Buffer[1] = *(P_DataPtr+9);
	}
	
	if( C_OK == LibPub_WriteDataToE2prom(LIB_E2P_AvailTimer , 0, &V_Buffer[0]) )
	{
		V_Buffer[0] = LibPub_1BCD_2_1HEX( *(P_DataPtr+8) );
		GStr_AVAIL.ulAutRemainingTime = (ulong32)V_Buffer[0];
		V_Buffer[1] = LibPub_1BCD_2_1HEX( *(P_DataPtr+9) );
		GStr_AVAIL.ulAutRemainingTime = GStr_AVAIL.ulAutRemainingTime * 100 + V_Buffer[1];	///*加入到分钟基本定时器中*///
		GStr_AVAIL.ulAutRemainingTime = GStr_AVAIL.ulAutRemainingTime*60; 

		GStr_AVAIL.us_IDAvailTimer=LibPub_Buffer2ToUshort16( P_DataPtr+8 );
		GStr_AVAIL.usCRC16=LibPub_CRC16_CCITT((uchar8*)&GStr_AVAIL.us_IDAvailTimer,3);
		
		
//		GStr_AvailTimer.us_IDAvailTimer.B08[0] = *(P_DataPtr+8);
//		GStr_AvailTimer.us_IDAvailTimer.B08[1] = *(P_DataPtr+9);
//		CRC_Generate(&GStr_AvailTimer.us_IDAvailTimer.B08[0],CAddr_AvailTimer_Lenth);
	}
	else
 	{ 
		B_Err_Other = 1;
		return C_ERR;   ///*其他错误*///;
	} 
	
	PrepaymentModule_Comm_ClrMACErrNum();
	GStr_Flag.ucRunState2 |=F_RUN_INTAUTHAvailabilityFlag;///*置身份认证有效标志*/// 
	
    return	C_OK ;     
}
///***********************************************************************************///
///*PrepaymentModule_Comm_MACErrNum、PrepaymentModule_Comm_ClrMACErrNum              *///
///*Description：Mac错误次数+1/清零                                                  *///
///*Input：                                                                          *///      
///*                                                                                 *///
///*                                                                                 *///
///*Output：                                                     *///
///*                                                                 *///
///*Calls：                                                                          *///
///*Called By：                                                                      *///
///*Influence：                                                                      *///
///*Tips：                                                                           *///
///*Others：                                                                         *///
///*Author:                                                                   *///
///***********************************************************************************///
void PrepaymentModule_Comm_MACErrNum()
{
	if(GV_ucMACErrNum<200)
	{
		GV_ucMACErrNum++;
		GStr_Flag.ucRunState2 &= ~ F_RUN_INTAUTH_MACNumErrFlag;
	}
	if(GV_ucMACErrNum >= 200)
	{
		GStr_Flag.ucRunState2 |=  F_RUN_INTAUTH_MACNumErrFlag;
		GStr_Monitor.usPasswordErrTime[3]=1440;///24小时
		PrepaymentModule_InValidation();
	}
}
///***********************************************************************************///
///*PrepaymentModule_Comm_ClrMACErrNum              *///
///*Description：Mac错误次数 和状态清零                                                  *///
///*Input：                                                                          *///      
///*                                                                                 *///
///*                                                                                 *///
///*Output：                                                     *///
///*                                                                 *///
///*Calls：                                                                          *///
///*Called By：                                                                      *///
///*Influence：                                                                      *///
///*Tips：                                                                           *///
///*Others：                                                                         *///
///*Author:chenshou                                                                  *///
///***********************************************************************************///
void PrepaymentModule_Comm_ClrMACErrNum()
{	
	GV_ucMACErrNum = 0;
	GStr_Flag.ucRunState2 &= ~ F_RUN_INTAUTH_MACNumErrFlag;
}
///***********************************************************************************///
///*PrepaymentModule_InValidation              *///
///*Description：清除身份认证状态                                                   *///
///*Input：                                                                          *///      
///*                                                                                 *///
///*                                                                                 *///
///*Output：                                                     *///
///*                                                                 *///
///*Calls：                                                                          *///
///*Called By：                                                                      *///
///*Influence：                                                                      *///
///*Tips：                                                                           *///
///*Others：                                                                         *///
///*Author:chenshou                                                                  *///
///***********************************************************************************///
void PrepaymentModule_InValidation()
{
	GStr_Flag.ucRunState2 &= ~ F_RUN_INTAUTHAvailabilityFlag;		                ///*身份认证标志 清零*///
	GStr_AVAIL.ulAutRemainingTime = 0;				///*身份认证有效时长 清零*///
	GStr_Flag.ucRunState2 &= ~ F_RUN_FirstProgFlag;
	
}
///***********************************************************************************///
///*PrepaymentModule_Comm_OpenAccout                                                 *///
///*Description：网络开户01\充值02 \钱包初始化03                                           *///
///*Input：*P_DataPoint为入口数据指针DI0                                             *///      
///*                                                                                 *///
///*                                                                                 *///
///*Output：返回值=C_OK：操作正常                                                    *///
///*              =C_ERR：操作异常                                                   *///
///*Calls：                                                                          *///
///*Called By：                                                                      *///
///*Influence：                                                                      *///
///*Tips：函数正确执行后自动将需要应答的数据保存到通讯缓存相应地址                   *///
///*Others：                                                                         *///
///*Author:chenshou                                                                  *///
///***********************************************************************************///
///*frame::FE FE FE FE 68 A0 A1 A2 A3 A4 A5 68 03 L  DI0 DI1 DI2 DI3 C0 C1 C2 C3 N1...Nm CS 16*///
///*offset:0  1  2  3  4  5  6  4  8  9  10 11 12 13 14  15  16  17  18 19 20 21 22...........*///
///*接收22-29购电金额、购电次数  30-33 MAC 22-29客户编号 30-33 MAC 开户、充值*///
///*充值：充值金额、购电次数、电价参数、报警金额1、报警金额2、CT/PT、透支金额限值*///
///*接收8-15 购电金额、购电次数  16-19 MAC 20-25客户编号 26-29 MAC  *///
///*接收22-25预置金额 26-29 MAC 30-33购电次数 34-37 MAC 钱包初始化*///
///*接收8-11 预置金额 12-15 MAC 16-19购电次数 20-23 MAC  *///
///*ACKNo: FE FE FE FE 68 A0 A1 A2 A3 A4 A5 68 C3 02 SERR  CS  16 异常应答*///
uchar8 PrepaymentModule_Comm_OpenAccout(uchar8 *P_DataPtr)
{
	uchar8 		DI1;///**///
	uchar8 		i,k; 
	uchar8 		V_Buff[25]; 
	ulong32  	V_ulBuff[2];
	uchar8		V_ucUserIdMac[10];///* 客户编码 *///
	GU_B32_B08_Type V_unlMoneyMac[4];	///* 购电金额+次数+MAC1 / 预置金额+MAC1+购电次数+MAC2*/// 
	GU_B32_B08_Type V_unlTempBuff;
	
	DI1 = *(P_DataPtr+1); 
	
	if( ( (0x00 == DI1)||(0x04 < DI1) ) )
	{ B_Err_Other = 1; return C_ERR; }  ///其它错误
	if(0x03 != DI1)
	{
		if(!(GStr_Flag.ucRunState2&F_RUN_EsamKeyFlag) )
		{ B_Err_Other = 1;  return C_ERR;  }	///公钥下不准开户和充值
	}

	if(F_RUN_INTAUTHAvailabilityFlag!=(GStr_Flag.ucRunState2&F_RUN_INTAUTHAvailabilityFlag)	)
	{ B_Err_IDAuthenFail = 1; return C_ERR;}    ///*身份认证超时*///
	  
	if( 0x03 == DI1 ) { k = 4; }	//钱包初始化
	else              { k = 3; }	//充值、开户
	
	
	for( i = 0; i < k; i++ ) 
	{
		LibPub_MemExchangeBytes(P_DataPtr+8+i*4, &V_unlMoneyMac[0].B08[i*4], 4);
	}
	if( 0x01 == DI1 )///* 开户 *///
	{
		LibPub_MemExchangeBytes(P_DataPtr+8+12, &V_ucUserIdMac[0], 6);	///* 客户编号 *///
		LibPub_MemExchangeBytes(P_DataPtr+8+18, &V_ucUserIdMac[6], 4);	///* 客户编号MAC *///
	
		///* 不是钱包初始化，要校验一下购电金额和次数 *///
		if( C_ERR == PrepaymentModule_CommWriteESAMBinaryMAC(&V_unlMoneyMac[0].B08[0], 0x08, 10, 0x01) )
		{ B_Err_ESAMAuthenFail = 1;  return C_ERR; } 
			
		///* 验证客户编号MAC *///
		if(C_ERR == PrepaymentModule_CommWriteESAMBinaryMAC(&V_ucUserIdMac[0], 0x06, 7, 0x01) )
		{ B_Err_ESAMAuthenFail = 1;  return C_ERR; }  
			
		///* 充值、处于开户的表再开户，比较客户编号*///
		if( (0x01 != DI1) || ( (0x01 == DI1 )&&(GStr_Flag.ucRunState2&F_RUN_OpenAccoutFlag) ) )
		{
			LibPub_MemExchangeBytes(P_DataPtr+20,V_Buff,6);
			if(C_Equal != LibPub_CompareData(&GStr_MeterIFO.ucaUserID[0], V_Buff, 6,CMP_MODE_HIGHT) ) 
			{ B_Err_CustomNumUnmatch = 1;return C_ERR; }    ///客户编号不匹配 *///
		}
	}
	else if( 0x03 == DI1)///* 钱包初始化 *///
	{	
		if(GStr_Flag.ucRunState2&F_RUN_EsamKeyFlag) ///* 私钥状态下不允许钱包初始化 *///
		{ B_Err_Other = 1;  return C_ERR;  }	
		
		if(C_ERR == PrepaymentModule_CommWriteESAMBinaryMAC(&V_unlMoneyMac[0].B08[0], 0x04, 8, 0x01) )
		{ B_Err_ESAMAuthenFail = 1;  return C_ERR; } 
		
		if(C_ERR == PrepaymentModule_CommWriteESAMBinaryMAC(&V_unlMoneyMac[2].B08[0], 0x04, 9, 0x01) )
		{ B_Err_ESAMAuthenFail = 1;  return C_ERR; } 
	}  
	else///* 充值 *///
	{
		if( (0x01 != DI1) && ((GStr_Flag.ucRunState2&F_RUN_OpenAccoutFlag) != F_RUN_OpenAccoutFlag) ) /* 充值必须是在开户情况下方可执行 */
		{ B_Err_Other = 1; return C_ERR; }  ///其它错误

		LibPub_MemExchangeBytes(P_DataPtr+8+12, &V_ucUserIdMac[0], 6);	///* 客户编号 *///
		LibPub_MemExchangeBytes(P_DataPtr+8+18, &V_ucUserIdMac[6], 4);	///* 客户编号MAC *///
	
		///* 不是钱包初始化，要校验一下购电金额和次数 *///
		if( C_ERR == PrepaymentModule_CommWriteESAMBinaryMAC(&V_unlMoneyMac[0].B08[0], 0x08, 10, 0x01) )
		{ B_Err_ESAMAuthenFail = 1;  return C_ERR; } 
			
		///* 验证客户编号MAC *///
		if(C_ERR == PrepaymentModule_CommWriteESAMBinaryMAC(&V_ucUserIdMac[0], 0x06, 7, 0x01) )
		{ B_Err_ESAMAuthenFail = 1;  return C_ERR; }  
			
		///* 充值、处于开户的表再开户，比较客户编号*///
		if( (0x01 != DI1) || ( (0x01 == DI1 )&&(GStr_Flag.ucRunState2&F_RUN_OpenAccoutFlag) ) )
		{
			LibPub_MemExchangeBytes(P_DataPtr+20,V_Buff,6);
			if(C_Equal != LibPub_CompareData(&GStr_MeterIFO.ucaUserID[0], V_Buff, 6,CMP_MODE_HIGHT) ) 
			{ B_Err_CustomNumUnmatch = 1;return C_ERR; }    ///客户编号不匹配 *///
		}

	}
 
	///* 比较一下购电次数 *//////*购电次数(4)/
//	if(_TRUE != LibPub_CrcCheck( &GStr_EventRecordNum.ucEventTimes[0][0], GStr_EventRecordNum_TypeLEN-2, GStr_EventRecordNum.usCRC16))
//	{
//		if(_FAILED==LibPub_ReadDataFromE2prom(LIB_E2P_EventNum,0,&GStr_EventRecordNum.ucEventTimes[0][0])  )
//		{
//			if(LibPub_ZeroCheck(&GStr_EventRecordNum.ucEventTimes[0][0], GStr_EventRecordNum_TypeLEN-2) == _FALSE )
//			{
//				B_Err_Other = 1; return C_ERR;
//			}
//		}
//	}
	if(_TRUE != LibPub_CrcCheck( &GStr_PRICE.ucPurchaseTimes[0], GStr_PRICE_Type_LEN-2, GStr_PRICE.usCRC16))
	{
		if(_FAILED==LibPub_ReadDataFromE2prom(LIB_E2P_Price,0,&GStr_PRICE.ucaPrice[0])  )
		{
			if(LibPub_ZeroCheck(&GStr_PRICE.ucPurchaseTimes[0], GStr_PRICE_Type_LEN-2) == _FALSE )
			{
				B_Err_Other = 1; return C_ERR;
			}
		}
	}
    if((0x02==DI1)||(0x04==DI1))///处于二级报警和过零跳闸时，充值时继电器合闸
	{
		if(GStr_Flag.ucRunState1&F_RUN_L2_ALRAM)
		{
			 GStr_Flag.ucRunState |=F_RUN_CLOSE_L2;
		}
		if(GStr_Flag.ucRunState1&F_RUN_REMAIND_ZERO)
		{
			GStr_Flag.ucRunState |=F_RUN_CLOSE_ZERO;
		}
		ApiRelay_ControlProcess();
		LibPub_WriteDataToE2prom(LIB_E2P_RUN_STATE,0,&GStr_Flag.ucRunState);
	}
	V_ulBuff[0]= LibPub_DECtoHEXBytes(&GStr_PRICE.ucPurchaseTimes[0],4);
	if( ((0x02==DI1)||(0x04==DI1))&&(V_unlMoneyMac[1].B32<=V_ulBuff[0]))
		//(C_GreaterThan!=LibPub_CompareData(V_unlMoneyMac[1].B08, &GStr_PRICE.ucPurchaseTimes[0], 4,CMP_MODE_HIGHT)) )
	{ 
		
		B_Err_RepeatCharge = 1;return C_ERR; 
	}///* 购电次数相等则重复充值 *///
    
	
	if(  ( (0x01==DI1)&& ((V_unlMoneyMac[1].B32>1)||(V_ulBuff[0]>1)) )	///* 开户，购电次数大于1*///
	  || ( ((0x02==DI1)||(0x04==DI1))&&((V_unlMoneyMac[1].B32-1) > V_ulBuff[0]) ) 	///* 非开户，购电次数比表内大2 *///
	  || ( (0x03==DI1)&&(V_unlMoneyMac[2].B32 != 0) )  )	///* 钱包初始化，购电次数不等于0*///
	{ B_Err_RechargeTimesErr = 1; return C_ERR; }  

	
	///* 判断一下充值金额是否超出囤积金额 *///
	if( 0x03 != DI1 )///* 钱包初始化不判断囤积金额限值 *///
	{
		if((V_unlMoneyMac[1].B32!=V_ulBuff[0])&&(V_unlMoneyMac[1].B32!=0))///*开户判断表内购电次数及开户时的购电次数*///
		{
			if(_FAILED == LibPub_ReadDataFromE2prom(LIB_E2P_Money_Para, 0, &V_Buff[0]))
			{ B_Err_Other = 1; return C_ERR; } 
			
			LibPub_MemCopyBytes( &GStr_Money.ucaRemainMoney[0], &V_unlTempBuff.B08[0], 4);
			
			if(*(ulong32 *)&V_Buff[8]==0)
			{
				*(ulong32 *)&V_Buff[8]=0x99999999;///*充值时若囤积金额限值为0，则默认为99999999*///
			}
			
			V_ulBuff[0] = LibPub_DECtoHEXBytes( &V_Buff[8], 4 );	///*囤积金额BCD转Hex*///
			 V_ulBuff[1]=LibPub_Buffer4ToUlong32(GStr_Money.ucaTickMoney);
			if( V_unlMoneyMac[0].B32 > V_ulBuff[1] )
			{
				V_ulBuff[1] = V_unlMoneyMac[0].B32 - V_ulBuff[1];
			}
			else
			{
				V_ulBuff[1] = V_ulBuff[1]- V_unlMoneyMac[0].B32;
			}
			V_unlTempBuff.B32=LibPub_DECtoHEXBytes( &V_unlTempBuff.B08[0], 4 );///剩余金额转HEX
			V_ulBuff[1] += V_unlTempBuff.B32 ;
			
			if(  V_ulBuff[0]  < V_ulBuff[1])   ///*囤积金额 < 购电金额+总剩余金额-透支金额 *///
			{ B_Err_OverPurchase = 1;return C_ERR; } 
		}
	}
	
	if( 0x01 == DI1 ) 
	{   
		V_ulBuff[0]= LibPub_Buffer4ToUlong32(&GStr_PRICE.ucPurchaseTimes[0]);
		if( V_unlMoneyMac[1].B32 >= V_ulBuff[0] )
		{
			///* 不管三七二十一，开个户先 *///  
			///* 写客户编号 */// 
			LibPub_MemExchangeBytes( P_DataPtr+20, &GStr_MeterIFO.ucaUserID[0], 6);
			if(_FAILED == LibPub_WriteDataToE2prom(LIB_E2P_METER_INFO,0,GStr_MeterIFO.ucaCommAddr) )
			{ B_Err_Other = 1; return C_ERR; }
			GStr_MeterIFO.usCRC16=LibPub_CRC16_CCITT(GStr_MeterIFO.ucaCommAddr,GStr_METER_IFO_Type_LEN-2);
			
			PrepaymentModule_Comm_ClrMACErrNum();	///* 清MAC错误次数和挂起标志 *///
			///* 开户标志更新 *///
			GStr_AVAIL.ucBackMonFlag |= B0000_0010;  
			if(_FAILED == LibPub_WriteDataToE2prom(LIB_E2P_AvailTimer,0,(uchar8*)&GStr_AVAIL.us_IDAvailTimer) )
			{ GStr_AVAIL.ucBackMonFlag &= ~B0000_0010; B_Err_Other = 1; return C_ERR; }

			GStr_Flag.ucRunState2 |= F_RUN_OpenAccoutFlag ;
			GStr_AVAIL.usCRC16=LibPub_CRC16_CCITT((uchar8*)&GStr_AVAIL.us_IDAvailTimer,3);
			
			if(V_unlMoneyMac[1].B32 == V_ulBuff[0])///* 购电次数相等，只开户*///
			{ 
				GStr_Flag.ucRunState1  &= ~F_RUN_L2_ALRAM;
//				Money_Subtraction();						///* 充值后结算一下 *///				
				ApiRelay_SubtractMoneyRelayJudge();					///* 扣减后检测一下继电器状态 *///		函数待补充	
				ApiRelay_ControlProcess();
				return C_OK; 
			}
		}
		else
		{
			B_Err_RechargeTimesErr = 1; return C_ERR;
		}
	}

	///* 开始充值 *///
	*(ulong32*)&GStr_AVAIL.ucRechangeMoney[0] = V_unlMoneyMac[0].B32;
	if( C_OK == Money_Recharge( DI1 ) )				///* 充值 *///
	{
		if(_FALSE==LibPub_ZeroCheck(GStr_Money.ucaRemainMoney,4))///剩余金额不为0
		{
			GStr_Flag.ucRunState &=~F_RUN_CLOSE_ZERO;///再次为0后，继电器跳闸
			if(C_GreaterThan==LibPub_CompareData(GStr_Money.ucaRemainMoney, GStr_MoneyPara.ucaAlarmMoneyL2, 4, CMP_MODE_HIGHT))
			{///充值后金额比二级报警要大，清掉二级报警合闸标志，再次二级报警时合闸
				GStr_Flag.ucRunState &=~F_RUN_CLOSE_L2;
			}
		}
//		Money_Subtraction();						///* 充值后结算一下 *///			
		ApiRelay_SubtractMoneyRelayJudge();					///* 扣减后检测一下继电器状态 *///
		ApiRelay_ControlProcess();
//		EnergyStorageNmin(C_EnergyStorMode_Add1kWh, C_RechargeWrite);
//		if( C_OK == Money_RechargeWriteE2Money() )	///* 充值存E2后做事件记录 *///
		{ 
			PrepaymentModule_Comm_ClrMACErrNum();	///* 清MAC错误次数和挂起标志 *///
			return C_OK; 
		}
	}
	
	B_Err_Other = 1;	
	return C_ERR;	 
}
///***********************************************************************************///
///*PrepaymentModule_Comm_ModifyKey                                                  *///
///*Description：远程密钥更新                                                        *///
///*Input：*P_DataPoint为入口数据指针DI0                                             *///      
///*                                                                                 *///
///*                                                                                 *///
///*Output：返回值=C_OK：操作正常                                                    *///
///*              =C_ERR：操作异常                                                   *///
///*Calls：                                                                          *///
///*Called By：                                                                      *///
///*Influence：                                                                      *///
///*Tips：函数正确执行后自动将需要应答的数据保存到通讯缓存相应地址                   *///
///*Others：290ms                                                                    *///
///*Author:chenshou                                                                  *///
///***********************************************************************************///
///*frame::FE FE FE FE 68 A0 A1 A2 A3 A4 A5 68 03 L  DI0 DI1 DI2 DI3 C0 C1 C2 C3 N1...Nm CS 16*///
///*offset:0  1  2  3  4  5  6  4  8  9  10 11 12 13 14  15  16  17  18 19 20 21 22...........*///
///*接收8-11 更新标志 12-19 临时密钥 20-35修改密钥 36-39 MAC  */// 
///*ACKNo: FE FE FE FE 68 A0 A1 A2 A3 A4 A5 68 C3 02 SERR  CS  16 异常应答*///
///* 密钥版本和更新方式：D0D1D2D3D4：01+00+00+标志*///
uchar8 PrepaymentModule_Comm_ModifyKey(uchar8 *P_DataPtr)
{
	uchar8 i,V_ucTempBuff[16];  
	
    if((GStr_Flag.ucRunState2&F_RUN_INTAUTHAvailabilityFlag) != F_RUN_INTAUTHAvailabilityFlag)
	{ B_Err_IDAuthenFail = 1;  return C_ERR; } 
	
	///* 01000000或01000001*///
	if(   (0x01 <  *(P_DataPtr+8)) 
		||(0x00 != *(P_DataPtr+9)) 
		||(0x00 != *(P_DataPtr+10)) 
		||(0x01 != *(P_DataPtr+11)) )
	{ B_Err_Other = 1; return C_ERR; }

	if(   ((F_RUN_EsamKeyFlag==(GStr_Flag.ucRunState2&F_RUN_EsamKeyFlag)) && (0x01 == *(P_DataPtr+8)))		///* 如果正式密钥，再发下装命令，则不让下装 *///
		||((F_RUN_EsamKeyFlag!=(GStr_Flag.ucRunState2&F_RUN_EsamKeyFlag))&& (0x00 == *(P_DataPtr+8))) )	///* 如果是测试密钥，再发恢复，则不恢复 *///
	{ 
		B_Err_IDAuthenFail = 1; return C_ERR;
	}

	 ///*2)翻转数据*///
	LibPub_Inverse(P_DataPtr+8,  4);	///* 更新标志 *///
	LibPub_Inverse(P_DataPtr+12, 16);	///* 临时密钥 *///
	LibPub_Inverse(P_DataPtr+28, 16);	///* 修改密钥 *///
	LibPub_Inverse(P_DataPtr+44, 4); 	///* MAC *///
	///* 加密随机数，获得临时密钥跟下发的比 *///
	LibPub_MemCopyBytes( &GStr_VirtualEsamPara.ucRs485RandNum[0], &V_ucTempBuff[0], 8);
	if( C_ERR == TripleDES_DeOrEncryption( C_KeyNum00, &V_ucTempBuff[0], ENCRYPTION) )
	{ B_Err_IDAuthenFail = 1; return C_ERR; }  
	for( i = 0; i < 8; i++ )
	{
		V_ucTempBuff[i+8] = ~V_ucTempBuff[i];
	}
	if( C_Equal != LibPub_CompareData( &V_ucTempBuff[0], P_DataPtr+12, 16,CMP_MODE_HIGHT) )
	{ B_Err_IDAuthenFail = 1; return C_ERR; }  
	
    ///* 计算密钥更新MAC *///
	if( C_ERR == PrepaymentModule_CommWriteESAMBinaryMAC(P_DataPtr+8, 36, 6, 0x01) )
	{   B_Err_ESAMAuthenFail = 1;   return C_ERR;  } 
	///* 更新密钥 *///

	if(  C_ERR == LibPub_WriteDataToE2prom(LIB_E2P_SecretKey, 0, P_DataPtr+28) )
	{ B_Err_Other = 1; return C_ERR; } 
	///* 判断更新方式 *///
	
	if( 0x01 == *(P_DataPtr+11) )///* 下装(正式密钥） *///  修改
	{
		GStr_AVAIL.ucBackMonFlag |= B0000_0100;	///* 置私钥状态 *///
		GStr_Flag.ucRunState2 |=F_RUN_EsamKeyFlag;
	}
	else
	{
		GStr_AVAIL.ucBackMonFlag &= ~B0000_0100;	///* 置公钥状态 *///
		GStr_Flag.ucRunState2 &=~F_RUN_EsamKeyFlag;
	} 
	
	if(  C_ERR == LibPub_WriteDataToE2prom(LIB_E2P_AvailTimer,0,(uchar8*)&GStr_AVAIL.us_IDAvailTimer))
	{ B_Err_Other = 1; return C_ERR; }
	GStr_AVAIL.usCRC16=LibPub_CRC16_CCITT((uchar8*)&GStr_AVAIL.ulAutRemainingTime,3);
	
	
	return C_OK;   
}
///***********************************************************************************///
///*PrepaymentModule_Comm_HandBackMoney                                                  *///
///*Description：退费                                                                *///
///*Input：*P_DataPoint为入口数据指针DI0                                             *///      
///*                                                                                 *///
///*                                                                                 *///
///*Output：返回值=C_OK：操作正常                                                    *///
///*              =C_ERR：操作异常                                                   *///
///*Calls：                                                                          *///
///*Called By：                                                                      *///
///*Influence：                                                                      *///
///*Tips：		1. 数据传过来已经是明文且数据没有经过倒向，直接做明文判断就可以了  *///
///*Others：                                                                     *///
///*Author:                                                                   *///
///***********************************************************************************///
uchar8 PrepaymentModule_Comm_HandBackMoney(uchar8 *P_DataPtr)
{  
	GU_B32_B08_Type	V_unlTemp;
	ulong32			V_ulTemp;

	if( 0x00 == (GStr_AVAIL.ucBackMonFlag & B0000_0010) )///开户之后允许退费
	{ return C_ERR;}
	
	if(!(GStr_Flag.ucRunState2&F_RUN_EsamKeyFlag) ) ///公钥不允许退费
	{ return C_ERR;}

	///* 结算一下金额 *///
//	Money_Subtraction();   后续补充
    LibPub_Inverse( P_DataPtr, 4 );
	V_unlTemp.B32 = LibPub_Buffer4ToUlong32(P_DataPtr);

	///* 判断下剩余金额和退费金额 *///
    V_ulTemp= LibPub_Buffer4ToUlong32(GStr_Money.ucaRemainMoney);
	if( V_ulTemp < V_unlTemp.B32)
	{ return C_ERR;}
   
	///* 执行退费操作 */// 
    LibPub_MemCopyBytes(V_unlTemp.B08,GStr_AVAIL.ucRechangeMoney,4);///*退费金额 *///
	LibPub_MemCopyBytes(&GStr_Money.ucaRemainMoney[0],&GStr_AVAIL.ucBuybeforeMoney[0],4);//退费前剩余金额保存，用于事件记录

    LibPub_NBytesBCDSub(GStr_Money.ucaRemainMoney,GStr_AVAIL.ucRechangeMoney,4);
	GStr_Money.usCRC16=LibPub_CRC16_CCITT(GStr_Money.ucaRemainMoney,GStr_MONEY_Type_LEN-2);
    
    
    ///定时存储电量和金额  待补充
//	EnergyStorageNmin(C_EnergyStorMode_Add1kWh, C_NormalWrite);
	
//	Money_WriteE2Money ( C_NormalWrite );    ///* 存E2 *///  	
	///* 记录退费事件 *///
	
//	WriteEventRecord(CAddr_RejectMoneyP_Inpage);
	LibPub_WriteDataToE2prom(LIB_E2P_Money,0,GStr_Money.ucaRemainMoney);///剩余金额写EE
	///* 退费标志清除 *///
	ApiEvent_WriteRecord(C_RejectMoney);///做退费事件记录
//	GStr_AVAIL.ucBackMonFlag &= ~B0000_0001; 
//	RamCheck_Money();	 剩余金额效验 待补充

	
	if(  C_ERR == LibPub_WriteDataToE2prom(LIB_E2P_AvailTimer,0,(uchar8*)&GStr_AVAIL.us_IDAvailTimer))
	{ B_Err_Other = 1; return C_ERR; }
	GStr_AVAIL.usCRC16=LibPub_CRC16_CCITT((uchar8*)&GStr_AVAIL.ulAutRemainingTime,3);
	GStr_Flag.ucRunState1  &= ~F_RUN_L2_ALRAM;	
	ApiRelay_SubtractMoneyRelayJudge();			///*退费成功后根据当前剩余金额判断继电器状态*///待补充
	ApiRelay_ControlProcess();

	return C_OK;
}

///***********************************************************************************///
///*FunctionName：PrepaymentModule_DataDecription		                             *///
///*Description：数据加密                     		                                 *///
///*Input：*P_DataPtr为入口数据指针                                           		 *///      
///*       V_ucMACType MAC类型（见table表格）                                    	 *///
///*       *P_ucLen 数据长度，结束后会改变                                   		 *///
///*Output：返回值=C_OK：操作正常                                                    *///
///*              =C_ERR：操作异常                                                   *///
///*Calls：                                                                          *///
///*Called By：                                                                      *///
///*Influence：                                                                      *///
///*Tips：函数正确执行后自动将需要应答的数据保存到通讯缓存相应地址                   *///
///*Others： 
///*Author:                                                                          *///
///***********************************************************************************///
///* 解密（加密的逆过程） *///
uchar8 PrepaymentModule_DataDecription(uchar8 *P_DataPtr, uchar8 V_ucMACType, uchar8 *P_ucLen)
{
	uchar8	i,j,V_ucTempLen;
	
	V_ucTempLen = (*P_ucLen) % 8;

	if( V_ucTempLen ) return C_ERR;

///* 验证一下MAC是否正确 *///
	if( C_ERR == PrepaymentModule_CommWriteESAMBinaryMAC(P_DataPtr, *P_ucLen, V_ucMACType, 0x01) )
	{ return C_ERR; }

	V_ucTempLen = *P_ucLen / 8;
	LibPub_MemCopyBytes( P_DataPtr, &GA_uc7816CommBuffer[0], *P_ucLen); 
	
///* 先对BLOCKL解密 *///
	PrepaymentModule_GetWorkkey(C_KeyNum00);
	if( V_ucTempLen > 1)
	{
		if( C_ERR == TripleDES_DeOrEncryption( C_KeyNumTp, &GA_uc7816CommBuffer[(V_ucTempLen-1)*8], DECRYPTION) )
		{ return C_ERR; }

///* 对剩下的BLOCK进行异或处理 *///
		for( i = V_ucTempLen-1; i > 0; i-- )
		{
			for( j = 0; j < 8; j++ )
			{
				GA_uc7816CommBuffer[i*8+j] ^=  GA_uc7816CommBuffer[(i-1)*8+j];
			}
		} 
	}

///* 对第一组数据在进行一次解密 *///
	if( C_ERR == TripleDES_DeOrEncryption( C_KeyNumTp, &GA_uc7816CommBuffer[0], DECRYPTION) )
	{ return C_ERR; }
	
///* 算一下长度，然后返回 *///
	for( i = (*P_ucLen); i > 0; i-- )
	{
		if( 0x80 == GA_uc7816CommBuffer[i-1] ) break;
	}
	if( i == 0 ) return C_ERR; 

	*P_ucLen = i-1;
	LibPub_MemCopyBytes(  &GA_uc7816CommBuffer[0], P_DataPtr, *P_ucLen);
	
	return C_OK;
	
}



///***********************************************************************************///
///*PrepaymentModule_Comm_Control                                                    *///
///*Description：远程控制命令                                                        *///
///*Input：*P_DataPoint为入口数据指针PA密码权限                                      *///
///*                                                                                 *///
///*                                                                                 *///
///*Output：返回值=C_OK：操作正常                                                    *///
///*              =C_ERR：操作异常                                                   *///
///*Calls：                                                                          *///
///*Called By：                                                                      *///
///*Influence：                                                                      *///
///*Tips：函数正确执行后自动将需要应答的数据保存到通讯缓存相应地址                   *///
///*Others：命令正确执行后将控制码写入E2CAddr_usRemoteContral，bit0：跳闸，bit1：报警*///
///*bit2：保电，bit3：保电解除														 *///
///*Author:chenshou                                                                  *///
///***********************************************************************************///
/*Frame :PA P0 P1 P2 C0 C1 C2 C3 N1...Nm CS 16*///
//uchar8 PrepaymentModule_Comm_Control(uchar8 *P_DataPtr)
//{		
//	uchar8 V_TimeBuff[6];
//		
//		///*将系统时钟暂存到临时缓存*///
//		LibPub_MemSetBytes(&V_TimeBuff[0], 0x99, 6);  
//		
//		///*命令有效时间 - 系统时钟，若结果为正则执行操作*///因无时钟，强制命令有效时间为999999999999，否则回失败
//		if(LibPub_CompareData(P_DataPtr + 10, &V_TimeBuff[0], 6,CMP_MODE_HIGHT) != C_Equal)
//		{  return	C_ERR; } 

//		///* 当前处于保电状态，发跳闸命令返回错 *///
//		if( (GStr_Flag.ucRunState&F_RUN_KEEP_ELEC) && (*(P_DataPtr + 8) == 0x1A) )
//		{ return	C_ERR; }

//		switch(*(P_DataPtr + 8))
//		{
//			case  0x1A:	
//			{ 	
//				GStr_Flag.ucRunState |= F_RUN_COMM_RELAYOFF;
//			}break;///* 跳闸命令///
//			case  0x1C:	
//			{
//				GStr_Flag.ucRunState &= F_RUN_COMM_RELAYOFF;
//			}break;///* 直接合闸命令，清跳闸命令*///
//			case  0x3A:	
//			{
//				GStr_Flag.ucRunState |=F_RUN_KEEP_ELEC;	
//			}break;///* 保电命令 *///
//			case  0x3B:	 
//			{
//				GStr_Flag.ucRunState &=~F_RUN_KEEP_ELEC;	
//			}break;///* 保电解除命令 *///
//			
//			default:{ return	C_ERR;	}
//		}
//		
//		///* 存一下状态字 *///
//		if(_FAILED==LibPub_WriteDataToE2prom(LIB_E2P_RUN_STATE,0,&GStr_Flag.ucRunState))
//		{  return	C_ERR; 	}
//		GStr_Flag.usCRC16=LibPub_CRC16_CCITT(&GStr_Flag.ucRunState,1);
//		return	C_OK;  
//}

///***********************************************************************************///
///*FunctionName: PrepaymentModule_GetWorkkey										 *///
///*Description： 加密分散因子得到临时密钥                                         *///
///*Input：*                                               							 */// 
///*Output：                                             							 */// 
///*Calls：                                                                          *///
///*Called By：                                                                      *///
///*Influence：                                                                      *///
///*Tips                   															 *///
///*Others：                                                                         *///
///*Author:chenshou                                                                  *///
///***********************************************************************************///
uchar8 PrepaymentModule_GetWorkkey(uchar8 V_ucKeyNum)
{
	uchar8 i ;
	
	///* 获取分散因子。远程表分散因子存在GA_ucPcDiffusionFactor中 *///
	LibPub_MemCopyBytes( &GA_ucDisperFactor[0], &GA_ucDesTata[0], 0x08);
	
	///* 3DES加密分散因子,得到临时密钥 *///
	if( C_ERR==TripleDES_DeOrEncryption( V_ucKeyNum, &GA_ucDesTata[0], ENCRYPTION))
	{ return C_ERR; }
	
	LibPub_MemCopyBytes( &GA_ucDesTata[0], &GA_ucDesKey[0],  0x08);		///* 左密钥 *///
	
	///* 加密后的结果取反组成右密钥*///
	for (i = 0; i < 8; i++ )
	{
		GA_ucDesKey[i+8] = ~GA_ucDesTata[i];
	}
	
// 	///* 对取反后的分散因子进行加密再得到一组临时密钥 *///
// 	if( C_ERR == TripleDES_DeOrEncryption( V_ucKeyNum, &GA_ucDesTata[0], ENCRYPTION))
// 	{ return C_ERR; }
// 		 
// 	///* 将两组密钥合在一起就得到了分散因子分散后的临时密钥 *///
// 	CopyData( &A_ucTempbuff[0], &GA_ucDesKey[0],  0x08); 
// 	CopyData( &GA_ucDesTata[0], &GA_ucDesKey[8],  0x08);
	
	return C_OK;
} 

/* 参数设置时验证MAC是否合适 */
uchar8 PrepaymentModule_CommWriteESAMBinaryMAC(uchar8 *P_ucData, uchar8 V_ucLen, uchar8 V_ucHeadNum, uchar8 V_ucType)
{
	uchar8 V_ucResult;
	/* 准备数据 命令头+数据*/
	GA_uc7816CommBuffer[0] = GT_ucVirtualEsam[V_ucHeadNum][0];
	GA_uc7816CommBuffer[1] = GT_ucVirtualEsam[V_ucHeadNum][1];
	GA_uc7816CommBuffer[2] = GT_ucVirtualEsam[V_ucHeadNum][2];
	GA_uc7816CommBuffer[3] = GT_ucVirtualEsam[V_ucHeadNum][3];
	GA_uc7816CommBuffer[4] = V_ucLen+4;	///* 数据长度LC，数据长度+4字节MAC长度 *///
	LibPub_MemCopyBytes (P_ucData, &GA_uc7816CommBuffer[5], V_ucLen+4);	/* 数据+MAC */
	
	V_ucResult = Data_MAC( &GA_uc7816CommBuffer[0], V_ucLen+5, &GStr_VirtualEsamPara.ucRs485RandNum[0], V_ucType );
    if ( C_OK != V_ucResult)
	{
		PrepaymentModule_Comm_MACErrNum();	///*MAC错,次数+1 *///
	}
	return(V_ucResult);
}
///***********************************************************************************///
///*PrepaymentModule_Comm_INTAUTH_Invalidation                                       *///
///*Description：身份认证失效                                                        *///
///*Input：*P_DataPoint为入口数据指针DI0                                             *///
///*                                                                                 *///
///*                                                                                 *///
///*Output：返回值=C_OK：操作正常                                                    *///
///*              =C_ERR：操作异常                                                   *///
///*Calls：                                                                          *///
///*Called By：                                                                      *///
///*Influence：                                                                      *///
///*Tips：函数正确执行后自动将需要应答的数据保存到通讯缓存相应地址                   *///
///*Others：                                                                         *///
///*Author:                                                                   *///
///***********************************************************************************///
uchar8 PrepaymentModule_Comm_INTAUTH_Invalidation(uchar8 *P_DataPtr)
{  
	if((GStr_Flag.ucRunState2&F_RUN_INTAUTHAvailabilityFlag) != F_RUN_INTAUTHAvailabilityFlag)///* 身份认证超时 *///
	{
		B_Err_IDAuthenFail = 1;  return C_ERR;     
	} 
	
    ///* 客户编号 *///
	LibPub_MemExchangeBytes(&GStr_MeterIFO.ucaUserID[0], P_DataPtr + 4, 6);

	///* 返回剩余金额 *///
	LibPub_MemExchangeBytes( &GStr_Money.ucaRemainMoney[0], P_DataPtr + 10 ,4);
	
	///*返回购电次数*///
	LibPub_MemExchangeBytes(&GStr_PRICE.ucPurchaseTimes[0], P_DataPtr + 14, 4);					

	///* 返回密钥状态  *///
	if((GStr_Flag.ucRunState2&F_RUN_EsamKeyFlag)==F_RUN_EsamKeyFlag)
	{*(P_DataPtr + 18) = 0x01;}///私钥
	else {*(P_DataPtr + 18) = 0x00;}
	*(P_DataPtr + 19) = 0;
	*(P_DataPtr + 20) = 0;
	*(P_DataPtr + 21) = 1;
	 
	///* 清身份认证有效标志 *///
	PrepaymentModule_InValidation();  

	return C_OK; 
}
///*============================================================================================*///
///* Function:   	EsamRandom
///* Description:	取指定长度数据的随机数
///* Calls: 
///* Called By:  	
///* Input:        
///* Output:		
///* Return: 
///* Others:		 
///*============================================================================================*///
uchar8 PrepaymentModule_GetChallenge(uchar8 *P_DataPtr, uchar8 V_DataLen)
{
	uchar8 i;
	ushort16 V_usTempData;
	V_usTempData=TH0;
	V_usTempData<<=8;
	V_usTempData+=TL0;
	srand(V_usTempData);
	for( i = 0; i < V_DataLen; i++)
	{
		P_DataPtr[i] = rand();
	}
	return C_OK;
}

///*============================================================================================*///
///* Function:   	
///* Description:	充值函数
///* Calls: 
///* Called By:  	
///* Input:        V_ProcessType  01 开户充值  02充值 03钱包初始化
///* Output:		
///* Return: 
///* Others:		 
///*============================================================================================*///
uchar8 Money_Recharge( uchar8 V_ProcessType)
{ 
	uchar8 V_Buff[25];
	ulong32 V_ulBuff;
	uchar8 V_ucErrorType;
	
	V_ucErrorType = C_ERR;
	if((V_ProcessType==0x00)||(V_ProcessType>0x03))
	{return V_ucErrorType;}                          ///只能为 0x01  0x02 0x03

	LibPub_HEXtoBCDBytes(*(ulong32*)&GStr_AVAIL.ucRechangeMoney[0],&GStr_AVAIL.ucRechangeMoney[0],4);
    ///操作金额转换成BCD
	if( V_ProcessType == 0x03 )///钱包初始化
	{ 	
		///准备清零记录的数据
		LibPub_MemCopyBytes(&GStr_Energy.ucaFw_Energy[0],&GStr_AVAIL.ucbeforeFwEnergy[0],4);///操作前的正向电量保存用于事件记录
		LibPub_MemCopyBytes(&GStr_Energy.ucaBk_Energy[0],&GStr_AVAIL.ucbeforeBkEnergy[0],4);///操作前的反向电量保存用于事件记录
		
		ApiPwOn_MeterClear();
		
		///准备购电记录数据///清零后保存剩余金额为0
		LibPub_MemCopyBytes(&GStr_Money.ucaRemainMoney[0],&GStr_AVAIL.ucBuybeforeMoney[0],4);///操作前剩余金额

		// GV_ClearFlag=MoneyClear;
		///电表总清
		LibPub_MemSetBytes( GStr_Money.ucaRemainMoney, 0x00, 6 );
		LibPub_MemCopyBytes(GStr_AVAIL.ucRechangeMoney, &GStr_Money.ucaRemainMoney[0], 4);  //剩余金额等于购电金额
		LibPub_MemSetBytes( GStr_Money.ucaTickMoney, 0x00, 6 );///透支金额清零
		LibPub_MemCopyBytes(GStr_AVAIL.ucRechangeMoney, &GStr_PRICE.ucaPurchaseMoneyAll[0], 4);  //总购电金额等于购电金额
		LibPub_MemSetBytes( GStr_PRICE.ucPurchaseTimes, 0x00, 6 );///购电次数清零
		LibPub_WriteDataToE2prom(LIB_E2P_Money,0,GStr_Money.ucaRemainMoney) ;  ///剩余金额透支金额写EE
		LibPub_WriteDataToE2prom(LIB_E2P_Price, 0, &GStr_PRICE.ucaPrice[0]);//总购电金额和购电次数写EE
		
		///* 清开户状态 *///
		GStr_AVAIL.ucBackMonFlag &= ~B0000_0010;
		GStr_AVAIL.usCRC16=LibPub_CRC16_CCITT((uchar8*)&GStr_AVAIL.us_IDAvailTimer,3);
		if(_FAILED == LibPub_WriteDataToE2prom(LIB_E2P_AvailTimer,0,(uchar8*)&GStr_AVAIL.us_IDAvailTimer) )
		{ GStr_AVAIL.ucBackMonFlag |= B0000_0010; return V_ucErrorType; }
		GStr_Flag.ucRunState2 &= ~F_RUN_OpenAccoutFlag ;
		///*清本地报警状态*///
		LibPub_ReadDataFromE2prom(LIB_E2P_Money_Para, 0, &V_Buff[0]);
		V_ulBuff = LibPub_Buffer4ToUlong32(&V_Buff[4]);
		if(*(ulong32*)&GStr_AVAIL.ucRechangeMoney[0]<=V_ulBuff)  GStr_Flag.ucRunState1  |=F_RUN_L2_ALRAM;///*初始金额小于等于二级报警*///
		if(*(ulong32*)&GStr_AVAIL.ucRechangeMoney[0]==0)   GStr_Flag.ucRunState1  |=F_RUN_REMAIND_ZERO  ;///*初始金额为0*///
		GStr_Flag.ucRunState1 &= ~F_RUN_OVER_DRAFT;    ///清透支状态
		///* 清远程跳闸状态*///
		GStr_Flag.ucRunState &= ~F_RUN_COMM_RELAYOFF; 
    	GStr_Flag.ucRunState &= ~F_RUN_CLOSE_L2; 		
		GStr_Flag.ucRunState &= ~F_RUN_CLOSE_ZERO; 
		GStr_Flag.ucRunState &= ~F_RUN_DISABLE_CLOSE; 
		GStr_Flag.ucRunState &= ~F_RUN_OVER_DRAFTRELAY; 
		///请二级报警和过零合闸标志
		
		LibPub_WriteDataToE2prom(LIB_E2P_RUN_STATE,0,(uchar8*)&GStr_Flag.ucRunState) ;  
		

        if(!(GStr_Flag.ucMeterMode &F_FACTORY_MODE))///厂外模式在做事件记录
		{
			 ApiEvent_WriteRecord(C_Clear);///做清零事件记录 ////总清之后做事件记录
		}
		///准备购电记录的数据
			ApiEvent_WriteRecord(C_BuyMoney);///做购电时间记录
		///待补充
		
	}
	else
	{
		LibPub_MemSetBytes(V_Buff, 0x00, 6 );
		V_Buff[3]=0x01;
		LibPub_NBtyesBcdAdd(&GStr_PRICE.ucPurchaseTimes[0],V_Buff,4);///购电次数加1
		LibPub_MemSetBytes(V_Buff, 0x00, 6 );
		LibPub_MemCopyBytes(GStr_AVAIL.ucRechangeMoney, V_Buff, 4);  //购电金额转换成6字节，与透支金额比较	
		LibPub_MemCopyBytes(&GStr_Money.ucaRemainMoney[0],GStr_AVAIL.ucBuybeforeMoney,4);//购电前剩余金额保存，用于事件记录
		if(_FALSE==LibPub_ZeroCheck(GStr_Money.ucaTickMoney,6))///有透支金额
		{
			if(C_LessThan!=LibPub_CompareData(V_Buff, GStr_Money.ucaTickMoney, 6 , CMP_MODE_HIGHT))///购电金额不小于透支金额
			{
				LibPub_NBytesBCDSub(V_Buff,GStr_Money.ucaTickMoney,6);
				LibPub_MemSetBytes(GStr_Money.ucaTickMoney, 0x00, 6 );///透支金额清零
				LibPub_MemCopyBytes(V_Buff, &GStr_Money.ucaRemainMoney[0], 4);  //剩余金额=购电金额-透支金额
			}
			else
			{
				LibPub_NBytesBCDSub(GStr_Money.ucaTickMoney,V_Buff,6); ///购电金额小于透支金额   ，透支金额=透支金额-购电金额
				LibPub_MemSetBytes(GStr_Money.ucaRemainMoney, 0x00, 6 );//剩余金额为0
			}
		}
		else///无透支金额
		{
			LibPub_NBtyesBcdAdd(&GStr_Money.ucaRemainMoney[0],V_Buff,6);  //无透支，剩余金额=原剩余金额+购电金额
		}
		LibPub_NBtyesBcdAdd(GStr_PRICE.ucaPurchaseMoneyAll,GStr_AVAIL.ucRechangeMoney,4);///总购电金额累加
		LibPub_WriteDataToE2prom(LIB_E2P_Price, 0, &GStr_PRICE.ucaPrice[0] );///购电次数及总购电金额存EE
		LibPub_WriteDataToE2prom(LIB_E2P_Money, 0, GStr_Money.ucaRemainMoney );///剩余透支金额存EE
		
        
	    ApiEvent_WriteRecord(C_BuyMoney);///做购电事件记录
//		GStr_AVAIL.ucBackMonFlag|=B0000_0001;  ///退费标志置1
		
	} 
     
	GStr_Money.usCRC16=LibPub_CRC16_CCITT(GStr_Money.ucaRemainMoney,GStr_MONEY_Type_LEN-2);
	GStr_MeterIFO.usCRC16=LibPub_CRC16_CCITT(GStr_MeterIFO.ucaCommAddr,GStr_METER_IFO_Type_LEN-2);
	GStr_PRICE.usCRC16=LibPub_CRC16_CCITT(&GStr_PRICE.ucaPrice[0],GStr_PRICE_Type_LEN-2);

	V_ucErrorType =C_OK;	    

    return(V_ucErrorType);
	
}