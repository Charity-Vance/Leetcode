/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    BLEDrv.c                                                                          
**** Brief:       蓝牙驱动文件，接口统一                                                                    
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
#define	BLE_MODUL_FACTORY	BLE_MODUL_FACTORY_SW
#define	BLE_MODUL_FACTORY_SW     1
#define	BLE_MODUL_FACTORY_BX     2

#define	RXBUF_LEN	100		// 蓝牙发送接收缓冲区的最大长度

/*----------------< 常量定义 >----------------------------------*/ 

/*----------------< 变量定义 >----------------------------------*/ 
typedef struct 
{
	uchar8		ucIndex;		/*索引*/
	ulong32  	ucaDataId;		/*数据标识*/
	uchar8		IsWrite;		/*是否可写*/
	uchar8		ucaDataLen;		/*数据长度*/
}Str_BleData_MAP;

uchar8 code C_cBlePayload_Head[] = {0x02,0x01,0x06, 0x0B,0xFF, 0xF0,0xFF, 0x01, 0x43,0x48,0x49,0x4e,0x54,0x49,0x4d, 0x0F,0x09, 0x4b,0x4c };	/*广播数据的前缀，数据内容固定*/
	#define C_cBlePayload_Head_Len	sizeof(C_cBlePayload_Head)

Str_BleData_MAP code C_StrBle_MAP_TAB[ ]={		/*这几项数据不能删除，需要增加的数据项放在最后面*/
	/*索引					数据标识         是否可写    长度*/
	{ COMM_BLE_MAC	,	0x01000001	,	_TRUE	,	21	, },	/*本设备Mac地址+设备名称+本设备配对码(3字节hex) 6+12+3 */
	{ COMM_BLE_TPL	,	0x01000006	,	_TRUE	,	1	, },	/*修改发射功率 00表示0db(不可设);01表示-2db;02表示-4db;03表示-10db;04表示-20db;05表示2db;06表示3db(默认);*/
	//{ 0x01000007	,	_TRUE	,	1	, },	/*设置SMP等级00：不启用配对（默认）01：JUST WORK02：MITM_KEY(有输入能力)03：MITM_DISPLAY（有显示能力）*/
	{ COMM_BLE_EADV	,	0x0100010A	,	_TRUE	,	31	, },	/*广播包1广播内容（主广播）（设置MAC地址和广播内容后才开始广播）*/
	{ COMM_BLE_MOD	,	0x0100000B	,	_TRUE	,	1	, },	/*设置蓝牙工作模式 01：从（仅做从）*/
	{ COMM_BLE_TTP	,	0x0100000D	,	_TRUE	,	1	, },	/*透传协议（要求透传数据需要符合协议要求，可以不判断数据是否合法，但必须符合数据帧格式要求，要求发起透传时整帧数据已经收全，一次下发）01：645协议（默认）02：698协议*/
	{ COMM_BLE_STAT	,	0x00000002	,	_FALSE	,	6	, },	/*读取当前连接的设备MAC（如果没有连接，返回全FF）*/
	{ COMM_BLE_MFV	,	0x00000003	,	_FALSE	,	32	, },	/*模块固件版本号ASCII*/
};
#define	MAX_C_StrBle_MAP_TAB	sizeof(C_StrBle_MAP_TAB)/sizeof(Str_BleData_MAP)

/*----------------< 函数声明 >----------------------------------*/

static uchar8 BleDrv_BleComm(uchar8 v_ucOptIndex, uchar8 C_cBleCmd, uchar8 *p_ucDataBuff);
static uchar8 BleDrv_GetBlePara( uchar8 V_ucCmdIndex, uchar8 *p_ucDataBuf, uchar8 v_ucLen );
static uchar8 BleDrv_SetBlePara( uchar8 V_ucCmdIndex, uchar8 *p_ucDataBuf, uchar8 v_ucLen );

void BleDrv_SetBleRunPara( void );
void BleDrv_InitBleRunPara( void );

void BleDrv_WakeUpBle( uchar8 v_ucTRMode );
void BleDrv_InitPwn(void);

uchar8 BleDrv_GetBleStat(void);
uchar8 BleDrv_GetBleADVP(uchar8 *p_ucDataBuf);
uchar8 BleDrv_GetBleKey(uchar8 *p_ucDataBuf);
uchar8 BleDrv_GetBleMac(uchar8 *p_ucDataBuf);
uchar8 BleDrv_GetBleName(uchar8 *p_ucDataBuf);
uchar8 BleDrv_GetBlePSK( uchar8 *p_ucDataBuf );
uchar8 BleDrv_GetBleSMPLv(uchar8 *p_ucDataBuf);

uchar8 BleDrv_SetBleStat(void);
uchar8 BleDrv_SetBleADVP(uchar8 *p_ucDataBuf);
uchar8 BleDrv_SetBleCLRBond( uchar8 *p_ucDataBuf );
uchar8 BleDrv_SetBleKey(uchar8 *p_ucDataBuf);
uchar8 BleDrv_SetBleMac(uchar8 *p_ucDataBuf);
//uchar8 BleDrv_SetBleName(uchar8 *p_ucDataBuf);
uchar8 BleDrv_SetBlePSK(uchar8 *p_ucDataBuf);
uchar8 BleDrv_SetBleSMPLv(uchar8 *p_ucDataBuf);
uchar8 BleDrv_SetBleTPL(uchar8 *p_ucDataBuf);
//uchar8 BleDrv_GetOneByteFromUart( uchar8 *p_ucDatabuf );
//uchar8 BleDrv_SetOneByteToUart( uchar8 v_ucDataBuff ); 
uchar8 BleDrv_CommSetBlePara(uchar8 v_ucComIndex, uchar8 v_ucLen, uchar8 *p_ucDataBuf);
uchar8 BleDrv_CommGetBlePara(uchar8 v_ucComIndex, uchar8 v_ucLen, uchar8 *p_ucDataBuf);
uchar8 BleDrv_BleParaChk(uchar8 v_ucMode);
void BleDrv_BleStatuChk(void);
uchar8 BleDrv_GetBleUartSta(void);
void BleDrv_BleReset(void);

/*----------------< 函数定义 >----------------------------------*/

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    设置蓝牙参数
 *
 *  @param    p_ucDataBuf :要设置的名称首地址
 *			  v_ucLen :需要设置的数据的长度
 *  @return   
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
uchar8 BleDrv_SetBlePara( uchar8 V_ucCmdIndex, uchar8 *p_ucDataBuf, uchar8 v_ucLen )
{ 
	uchar8 V_ucTempBuff[RXBUF_LEN]="";
	uchar8 *P_ucDataEcho=V_ucTempBuff;	
	uchar8 V_ucResult=_FAILED;
	
	if( v_ucLen )
	{
		LibPub_MemCopyBytes( p_ucDataBuf, V_ucTempBuff, v_ucLen ); 
	}
	
	if( _SUCCESS == BleDrv_BleComm( V_ucCmdIndex, BLE_RW_WRITE, V_ucTempBuff ) )
	{
		V_ucResult =  _SUCCESS ;
	}
	
	return ( V_ucResult );
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    读蓝牙参数
 *
 *  @param    p_ucDataBuf :要获取的Mac的首地址
 *            v_ucLen ：读取数据的长度
 *  @return   
 *
 *  @note      
 *
 */
/*------------------------------------------------------------------------------------------------------*/
uchar8 BleDrv_GetBlePara( uchar8 V_ucCmdIndex, uchar8 *p_ucDataBuf, uchar8 v_ucLen )
{ 
	uchar8 V_ucTempBuff[RXBUF_LEN]=""; 
	uchar8 V_ucResult=_FAILED; 
	
	if( _SUCCESS == BleDrv_BleComm( V_ucCmdIndex, BLE_RW_READ, V_ucTempBuff ) )	/*读数据，按照索引找*/
	{
		LibPub_MemCopyBytes( V_ucTempBuff, p_ucDataBuf, v_ucLen ); 	/*数据标识不反回*/
		V_ucResult = _SUCCESS;
	}		
	
	return V_ucResult;
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    获取蓝牙状态
 *
 *  @return   蓝牙状态，具体见头文件中的宏定义
 *
 *  @note     xx
/*------------------------------------------------------------------------------------------------------*/
uchar8 BleDrv_GetBleStat( void )
{	
	return GStr_Flag.ucBLESTATFlag;
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    设置蓝牙工作模式，起动广播，起动扫描等
 *
 *  @param    xx :
 *
 *  @return   
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
uchar8 BleDrv_SetBleStat( void )
{ 
	uchar8 V_ucTempBuff[40]="";
	uchar8 V_ucResult = _FAILED;
	
	LibPub_MemCopyBytes( &C_cBlePayload_Head[0], &V_ucTempBuff[0], C_cBlePayload_Head_Len );	
	LibPub_HEXtoAscii( &GStr_MeterIFO.ucaCommAddr[0], &V_ucTempBuff[C_cBlePayload_Head_Len], 6 );	
	
	if( _SUCCESS == BleDrv_BleComm( COMM_BLE_EADV, BLE_RW_WRITE, V_ucTempBuff ) )
	{
		V_ucResult =  _SUCCESS ;
		GStr_Flag.ucBLESTATFlag = BLE_STAT_ADV_ON;		/*蓝牙状态设置为启动广播*/
	}
	return ( V_ucResult );
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    设置蓝牙Mac
 *
 *  @param    p_ucDataBuf :要设置的Mac首地址
 *
 *  @return   
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
uchar8 BleDrv_SetBleMac(uchar8 *p_ucDataBuf)
{  
	return( BleDrv_SetBlePara( COMM_BLE_MAC, p_ucDataBuf, BLE_MAC_Len ) );	/*新模块有名称，4+6+3+12*/	
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    获取蓝牙Mac
 *
 *  @param    p_ucDataBuf :要获取的Mac的首地址
 *
 *  @return   
 *
 *  @note     
 *
 */
/*------------------------------------------------------------------------------------------------------*/
uchar8 BleDrv_GetBleMac(uchar8 *p_ucDataBuf)
{  
	return( BleDrv_GetBlePara( COMM_BLE_MAC, p_ucDataBuf, BLE_MAC_Len ) );
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    设置蓝牙配对码
 *
 *  @param    p_ucDataBuf :要设置的key首地址
 *
 *  @return   
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
//uchar8 BleDrv_SetBleKey(uchar8 *p_ucDataBuf)
//{  
//	return( BleDrv_SetBlePara( BLE_AT_SET_PSK, p_ucDataBuf, 6 ) );
//}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    获取蓝牙key
 *
 *  @param    p_ucDataBuf :要获取的Mac的首地址
 *
 *  @return   
 *
 *  @note      
 *
 */
/*------------------------------------------------------------------------------------------------------*/
//uchar8 BleDrv_GetBleKey(uchar8 *p_ucDataBuf)
//{  
//	return( BleDrv_GetBlePara( BLE_AT_GET_PSK, p_ucDataBuf, 6 ) );
//}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    设置蓝牙名称
 *
 *  @param    p_ucDataBuf :要设置的名称首地址
 *
 *  @return   
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
//uchar8 BleDrv_SetBleName(uchar8 *p_ucDataBuf)
//{  
//	return( BleDrv_SetBlePara(  0x01000001, 13, 01, p_ucDataBuf ) );///*设置蓝牙名称，新协议不能设置*///
//}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    获取蓝牙名称
 *
 *  @param    p_ucDataBuf :要获取的名称的首地址
 *
 *  @return   
 *
 *  @note      
 *
 */
/*------------------------------------------------------------------------------------------------------*/
uchar8 BleDrv_GetBleName(uchar8 *p_ucDataBuf)
{  
	uchar8 V_ucReasult = _FAILED;
	uchar8 V_ucTempBuff[25] = "";

	V_ucReasult = BleDrv_GetBlePara( COMM_BLE_MAC, V_ucTempBuff, BLE_MAC_Len );

	if( _SUCCESS == V_ucReasult )
	{
		LibPub_MemCopyBytes(&V_ucTempBuff[6], &p_ucDataBuf[0], 12);	/*mac+名称+配对码；6+12+3*/
	}	
	return( V_ucReasult );
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    设置配对等级
 *
 *  @param    p_ucDataBuf :要设置的名称首地址
 *
 *  @return   
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
//uchar8 BleDrv_SetBleSMPLv(uchar8 *p_ucDataBuf)
//{  
//	return( BleDrv_SetBlePara( BLE_AT_SET_SMPLV, p_ucDataBuf, 1 ) );
//}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    获取配对等级
 *
 *  @param    p_ucDataBuf :要获取的数据的首地址
 *
 *  @return   
 *
 *  @note      
 *
 */
/*------------------------------------------------------------------------------------------------------*/
//uchar8 BleDrv_GetBleSMPLv(uchar8 *p_ucDataBuf)
//{  
//	return( BleDrv_GetBlePara( BLE_AT_GET_SMPLV, p_ucDataBuf, 1 ) );
//}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    设置蓝牙广播周期
 *
 *  @param    p_ucDataBuf :要设置的参数首地址
 *
 *  @return   
 *
 *  @note     向串口  RX 输入以下字符串"TTM:ADP-%s "，%s  格式为%dms，也可以设置模块的广播周期，
              如"TTM:ADP-20ms",设置广播周期为 20ms，取值范围为 20ms~10000ms。
 *
 */
/*------------------------------------------------------------------------------------------------------*/
//uchar8 BleDrv_SetBleADVP(uchar8 *p_ucDataBuf)
//{  
//	uchar8 V_ucLen ;
//	V_ucLen = strlen(p_ucDataBuf);
//	return( BleDrv_SetBlePara( BLE_AT_SET_ADP, p_ucDataBuf, V_ucLen ) );
//}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    获取蓝牙广播周期
 *
 *  @param    p_ucDataBuf :要设置的参数首地址
 *
 *  @return   
 *
 *  @note     向串口  RX 输入以下字符串"TTM:ADP-?"查询当前的广播周期， 模组返回"TTM:ADP-%s\r\n\0"，%s 
为字符串表示当前广播间隔，如"TTM:ADP-200ms\r\n\0"表示当前广播间隔为 200ms
 *
 */
/*------------------------------------------------------------------------------------------------------*/
//uchar8 BleDrv_GetBleADVP(uchar8 *p_ucDataBuf)
//{
//	uchar8 V_ucReasult,V_ucCnti;
//	uchar8 V_ucTempBuff[5]="";
//	
//	V_ucReasult = BleDrv_GetBlePara( BLE_AT_GET_ADP, V_ucTempBuff, 5 ) ;
//	if( _SUCCESS == V_ucReasult  )
//	{
//		for( V_ucCnti = 0; V_ucCnti<5; V_ucCnti++ )
//		{
//			if( (V_ucTempBuff[V_ucCnti]>=0x30)&&(V_ucTempBuff[V_ucCnti]<=0x39) )
//			{
//				p_ucDataBuf[V_ucCnti] = V_ucTempBuff[V_ucCnti];
//			}
//		}
//	}
//	return( V_ucReasult );
//}


/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    设置蓝牙发射功率
 *
 *  @param    p_ucDataBuf :要设置的参数首地址,最大3字节，否则返回错误
 *
 *  @return   
 *
 *  @note     数据为ASCII:-20,-8,-4,0,+2等 TTM:TPL-(X)
 *
 */
/*------------------------------------------------------------------------------------------------------*/
uchar8 BleDrv_SetBleTPL( uchar8 *p_ucDataBuf )
{
	uchar8	V_ucLen = BLE_TPL_Len;
	uchar8 V_ucTempBuff[5] = "";

	LibPub_MemCopyBytes( p_ucDataBuf, &V_ucTempBuff[0], V_ucLen );
	return( BleDrv_SetBlePara( COMM_BLE_TPL, V_ucTempBuff, BLE_TPL_Len ) );
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    通信设置蓝牙模块参数
 *
 *  @param    p_ucDataBuf :要设置的参数首地址,最大3字节，否则返回错误
 *            v_ucComIndex ：要设置的参数元素索引
 *  @return   
 *
 *  @note     
 *
 */
/*------------------------------------------------------------------------------------------------------*/

uchar8 BleDrv_CommSetBlePara(uchar8 v_ucComIndex, uchar8 v_ucLen, uchar8 *p_ucDataBuf)
{
	uchar8 V_ucTempBuff[35] = "";

	LibPub_MemCopyBytes( p_ucDataBuf, &V_ucTempBuff[0], v_ucLen );

	return( BleDrv_SetBlePara( v_ucComIndex, V_ucTempBuff, v_ucLen ) );
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    通信读蓝牙模块参数
 *
 *  @param    p_ucDataBuf :要设置的参数首地址,最大3字节，否则返回错误
 *            v_ucComIndex ：要设置的参数元素索引
 *  @return   
 *
 *  @note     
 *
 */
/*------------------------------------------------------------------------------------------------------*/

uchar8 BleDrv_CommGetBlePara( uchar8 v_ucComIndex, uchar8 v_ucLen, uchar8 *p_ucDataBuf )
{
	return( BleDrv_GetBlePara( v_ucComIndex, p_ucDataBuf, v_ucLen ) );
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    获取蓝牙发射功率
 *
 *  @param    p_ucDataBuf :要获取的参数的首地址，最大5字节
 *
 *  @return   
 *
 *  @note      
 *
 */
/*------------------------------------------------------------------------------------------------------*/
uchar8 BleDrv_GetBleTPL(uchar8 *p_ucDataBuf)
{  
	return( BleDrv_GetBlePara( COMM_BLE_TPL, p_ucDataBuf, BLE_TPL_Len ));
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    清除绑定信息
 *
 *  @param    p_ucDataBuf :要设置的参数首地址,这个命令没有数据，所以长度可以写成0
 *
 *  @return   
 *
 *  @note     清除配对绑定的信息
 *
 */
/*------------------------------------------------------------------------------------------------------*/
//uchar8 BleDrv_SetBleCLRBond( uchar8 *p_ucDataBuf )
//{ 
//	return( BleDrv_SetBlePara( BLE_AT_CLR_BOND, p_ucDataBuf, 0 ) ); 
//}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    设置配对密码
 *
 *  @param    p_ucDataBuf :要设置的参数首地址，6字节ASCII
 *
 *  @return   
 *
 *  @note     配对密码
 *
 */
/*------------------------------------------------------------------------------------------------------*/
//uchar8 BleDrv_SetBlePSK( uchar8 *p_ucDataBuf )
//{ 
//	return( BleDrv_SetBlePara( BLE_AT_SET_PSK, p_ucDataBuf, 6 ) ); 
//}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    获取配对密码
 *
 *  @param    p_ucDataBuf :要获取的参数首地址，6字节ASCII
 *
 *  @return   
 *
 *  @note     配对密码
 *
 */
/*------------------------------------------------------------------------------------------------------*/
//uchar8 BleDrv_GetBlePSK( uchar8 *p_ucDataBuf )
//{ 
//	return( BleDrv_SetBlePara( BLE_AT_GET_PSK, p_ucDataBuf, 6 ) ); 
//}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    上电配置蓝牙通信参数，上电不管串口是否空闲，均配置，如果是平时检查，要判断当前串口状态，如果空闲才操作，否则不操作
 *
 *  @return   xx
 *
 *  @note     1. 先判定是否为广播状态，不是则设置成广播状态
 *  @note     2.校验一下Mac参数，另外将更新Mac和名称
 *  @note     3.更新配对码等参数

 *
 */
/*------------------------------------------------------------------------------------------------------*/
void BleDrv_InitPwn(void)
{	
		
	/*--------------------------------------------------------------------------*/
	// 校验一下Mac、配对码、广播周期和名称 	
	BleDrv_BleParaChk(INT_Mode);
	
	/*--------------------------------------------------------------------------*/
//	// 上电直接写运行参数，运行参数需要1分钟检测一次
	BleDrv_SetBleRunPara();
	
//	/*--------------------------------------------------------------------------*/
//	// 判断一下如果不是连接状态，开启广播状态
	BleDrv_BleStatuChk();
//	
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    定时检查蓝牙参数，1分钟一次
 *
*  @return   _SUCCESS 处理成功; _FAILED 处理失败，会初始化蓝牙模组参数
 *
 *  @note     
 *
 */
/*------------------------------------------------------------------------------------------------------*/
uchar8 BleDrv_BleParaChk(uchar8 v_ucMode)
{
	uchar8 V_ucResult = _SUCCESS;
	//uchar8 p_ucDataBuff[20];
	
	/* 先检查一下RAM，如果crc出错，就从E2中恢复一下，然后不管是否正确都重新初始化一下蓝牙模组参数 */
	///上电直接写MAC，不判MAC是否正确

	if (( _TRUE != LibPub_CrcCheck( (uchar8*)&GStr_BLEGroup.ucBleMAC[0], GStr_BLE_GROUP_TypeLEN-2, GStr_BLEGroup.usCRC16 ) )
		||(v_ucMode==INT_Mode))
	{
		if( _FAILED == LibPub_ReadDataFromE2prom( LIB_E2P_BLE_PARA, 0, (uchar8*)&GStr_BLEGroup.ucBleMAC[0] ) )
		{  
			V_ucResult = _FAILED;
		}
			
		/* 如果RAM参数有变化，从E2恢复以后也重新设置一下蓝牙参数，设置成广播态 */
		BleDrv_BleReset();
		BleDrv_InitBleRunPara();
		BleDrv_SetBleStat();	 
	}
	 
	return V_ucResult; 
}


/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    定时检查蓝牙状态，暂定1min 1次
 *
 *  @return   xx
 *
 *  @note      
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void BleDrv_BleStatuChk(void)
{
	uchar8	V_ucBleStatus=BLE_STAT_NORESP;
	uchar8	p_ucDataBuf[RXBUF_LEN] = ""; 
	uchar8	i = 0;
	
	V_ucBleStatus = BleDrv_GetBleStat();
	
	do{
		/*如果检测到电表修改表地址命令未完成，则不进行这次蓝牙参数检查*/
		if( (BLE_STAT_MAC_MOD == V_ucBleStatus)||(BLE_STAT_RST == V_ucBleStatus) )
		{
			break;
		}
		
		/*检查一下蓝牙的状态，如果不是连接状态或者广播状态就设定成广播*/
		if( BLE_STAT_CONNECTED != V_ucBleStatus )
		{ 
			/*不在广播状态直接进行广播*/
			if( BLE_STAT_ADV_ON != V_ucBleStatus )
			{
				GStr_Monitor.ucBleAdvCnt=0;
				BleDrv_SetBleStat();				/*设置为广播状态*/
			}
			/*间隔三个小时，定时广播一下*/
			if( GStr_Monitor.ucBleAdvCnt > 180 )
			{
				GStr_Monitor.ucBleAdvCnt = 0;
				BleDrv_SetBleStat();				/*设置为广播状态*/
			}
		}
		if( BLE_STAT_IDLE == V_ucBleStatus )		/* 处于空闲状态*/
		{
			GStr_Monitor.ucBleAdvCnt=0;
			BleDrv_SetBleRunPara();					/*设置运行参数，起动广播*/
		}
		else if( BLE_STAT_IDLE == V_ucBleStatus )	/* 处于广播状态*/
		{
			/*间隔三个小时，定时广播一下*/
			if( GStr_Monitor.ucBleAdvCnt > 180 )
			{
				GStr_Monitor.ucBleAdvCnt=0;
				GStr_Flag.ucBLESTATFlag = BLE_STAT_RST;	/*蓝牙模块需要重启，重新设置参数*/
			}
		}
		else if( BLE_STAT_CONNECTED == V_ucBleStatus )	/* 处于连接状态*/
		{
			GStr_Monitor.ucBleAdvCnt=0;
			BleDrv_BleReset();
			GStr_Flag.ucBLESTATFlag = BLE_STAT_RST;	/*蓝牙模块需要重启，重新设置参数*/
		}

		/*没有到4分钟的时间间隔，直接break退出*/
		if( (GStr_Monitor.ucBleAdvCnt & B0000_0011) != B0000_0011 )
		{ 
			break;
		}
		
		/*连接状态，每隔4分钟进行校验，读mac查看是否有问题*/
		if( _SUCCESS == BleDrv_GetBlePara(COMM_BLE_MAC, p_ucDataBuf, BLE_MAC_Len) )
		{
			for( i=0; i<6; i++ )	/*检验读回来的MAC是否一致*/
			{
				if( p_ucDataBuf[i] != GStr_BLEGroup.ucBleMAC[5-i])
					break;
			}
			if( i < 6 )
			{
				BleDrv_BleReset();
				BleDrv_InitBleRunPara();
				BleDrv_SetBleStat();	 
			}
		}
		else	/*数据没有读成功，直接初始化*/
		{
			BleDrv_BleReset();
			BleDrv_InitBleRunPara();
			BleDrv_SetBleStat();	 
		}
	}while(0);
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    获取蓝牙串口状态
 *
 *  @return   _IDLE：空闲  _BUSY：忙
 *
 *  @note     除了接收和发送状态，其余状态都为空闲状态
 *
 */
/*------------------------------------------------------------------------------------------------------*/
uchar8 BleDrv_GetBleUartSta(void)
{
	if( (API_COMM_STATUS_SEND == Gstr_UartComm[CH_BLE].ucCommChStatus) || 
		(API_COMM_STATUS_RECV == Gstr_UartComm[CH_BLE].ucCommChStatus) )
	{
		return _BUSY;
	}
	return _IDLE;
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    初始化蓝牙运行参数
 *
 *  @return   无
 *
 *  @note      
 *
 */
/*------------------------------------------------------------------------------------------------------*/

void BleDrv_InitBleRunPara( void )
{
	/*-----------------------------------------------------------*/
	// MAC默认为6字节bcd格式的通信地址转给5字节hex格式，高两位恒定为C0H，随机地址中的静态地址，mcu无法实现转化，直接将地址传给模块，让模块自行转化
	LibPub_MemCopyBytes( &GStr_MeterIFO.ucaCommAddr[0], &GStr_BLEGroup.ucBleMAC[0], 6 );	
	//GStr_BLEGroup.ucBleMAC[5] = 0xC0; 
	
	/*-----------------------------------------------------------*/
	// 设备名称默认为MAC地址
	LibPub_HEXtoAscii(&GStr_BLEGroup.ucBleMAC[0], &GStr_BLEGroup.ucBleName[0], 6 ); 
	
	/*-----------------------------------------------------------*/
	// 配对密码默认为FFFFFF	
	GStr_BLEGroup.ucBleKey[0] = 0x00;//12;
	GStr_BLEGroup.ucBleKey[1] = 0x00;//34;
	GStr_BLEGroup.ucBleKey[2] = 0x00;//56;
	
	/*-----------------------------------------------------------*/
	// 广播间隔默认100ms	
	GStr_BLEGroup.usAdvTime = 0x0100;
	
	/*-----------------------------------------------------------*/
	// 设置蓝牙发射功率等级，默认06级 00表示0db(不可设);01表示-2db;02表示-4db;03表示-10db;04表示-20db;05表示2db;06表示3db(默认)
	//GStr_BLEGroup.ucBleTPL = 0x06;
	
	// 设置蓝牙smp等级	默认需要配对
	//GStr_BLEGroup.ucSMPLevel = '0';

	/*-----------------------------------------------------------*/
	// 设置运行参数	
	BleDrv_SetBleRunPara();
	
	LibPub_WriteDataToE2prom( LIB_E2P_BLE_PARA, 0, (uchar8*)&GStr_BLEGroup.ucBleMAC[0] );
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    设置蓝牙运行参数
 *
 *  @return   无
 *
 *  @note      
 *
 */
/*------------------------------------------------------------------------------------------------------*/

void BleDrv_SetBleRunPara( void )
{
	uchar8 V_ucTempBufA[25]="";
//	uchar8 V_ucTempBufB[20]="";
//	uchar8 V_ucCnti,V_ucCntj;
	
	/*----------------------------------------------------------*/
	// 设置Mac
	LibPub_MemExchangeBytes( &GStr_BLEGroup.ucBleMAC[0], V_ucTempBufA, 6);		/* MAC，倒序传输 */ 
	LibPub_MemCopyBytes( &GStr_BLEGroup.ucBleName[0], V_ucTempBufA+6, 12);	/* 名称 */ 
	LibPub_MemCopyBytes( &GStr_BLEGroup.ucBleKey[0], V_ucTempBufA+18, 3);	/* 配对码 */ 
	BleDrv_SetBleMac( V_ucTempBufA );

	V_ucTempBufA[0] = GStr_BLEGroup.ucBleTPL;

	//设置发射功率 
	BleDrv_SetBleTPL( &V_ucTempBufA[0] );
	
	//启动广播
	BleDrv_SetBleStat();
	// LibPub_MemCopyBytes(&GStr_BLEGroup.ucBleMAC[0], &p_ucDataBuff[0], 6);
	// LibPub_MemCopyBytes(&GStr_BLEGroup.ucBleKey[0], &p_ucDataBuff[10], 3);
		
	/*----------------------------------------------------------*/
	// 设置配对码
	/*
	LibPub_MemSetBytes( &V_ucTempBufA, 0x00, 20 );
	LibPub_HEXtoAscii( &GStr_BLEGroup.ucBleKey[0], V_ucTempBufA, 3);
	BleDrv_SetBleKey( V_ucTempBufA );
	*/
	
//	/*----------------------------------------------------------*/
//	// 设置模块名称
//	BleDrv_SetBleName( &GStr_BLEGroup.ucBleName[0] );
	
	/*----------------------------------------------------------*/
	// 设置广播周期
	/*
	LibPub_MemSetBytes( &V_ucTempBufA, 0x00, 20 );
	LibPub_MemSetBytes( &V_ucTempBufB, 0x00, 20 );
	V_ucTempBufA[0] = (uchar8) ( (GStr_BLEGroup.usAdvTime>>8) & 0x00ff );
	V_ucTempBufA[1] = (uchar8) ( (GStr_BLEGroup.usAdvTime   ) & 0x00ff );
//	LibPub_HEXtoAscii( (uchar8 *) &(GStr_BLEGroup.usAdvTime), V_ucTempBufA, 2);	
	LibPub_HEXtoAscii(  &V_ucTempBufA[0], &V_ucTempBufA[10], 2 );	
	for(V_ucCnti=0;V_ucCnti<4;V_ucCnti++)
	{
		if(V_ucTempBufA[10+V_ucCnti] != '0' )
		{
			for(V_ucCntj=0; V_ucCntj<4; V_ucCntj++)
			{
				V_ucTempBufB[V_ucCntj] = V_ucTempBufA[10+V_ucCnti+V_ucCntj];
			}
			break;
		}
	}
	BleDrv_SetBleADVP( V_ucTempBufB );
	*/
	
	/*----------------------------------------------------------*/
	// 设置配对等级
	/*
	BleDrv_SetBleSMPLv( &GStr_BLEGroup.ucSMPLevel );
	*/
	
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    设置或查询模块信息
 *
 *  @param    v_ucOptIndex : 功能字索引
 *  @param    C_cBleCmd : 控制码
 *  @param    p_ucDataBuff : 要设置或者数据返回的指针
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
uchar8 BleDrv_BleComm(uchar8 v_ucOptIndex, uchar8 C_cBleCmd, uchar8 *p_ucDataBuff)
{
	uchar8	V_ucResult = _FAILED,V_ucRxFlg=_FALSE;
	uchar8	V_ucCnti=0,V_ucCntk=0,V_ucLen=0,v_ucLen=0;
	uchar8	V_ucTempDataBuf[RXBUF_LEN]=""; 
	uchar8	*P_ucTempDataBuf = V_ucTempDataBuf;
	uchar8	V_ucIndex;
	ushort16	V_usCntj;
	ulong32 V_ucDataId;	 

	/*掉电就退出*/
	if ( GStr_Flag.ucSystem & F_PWOFF_NOW )
	{
		return V_ucResult;
	}
	/*判断串口是否是空闲状态*/
	if( _BUSY == BleDrv_GetBleUartSta() )
	{
		return BLE_STAT_BUSY;
	}
	
	do{	
		/*判断索引是否在范围内*/
		for( V_ucIndex=0; V_ucIndex< MAX_C_StrBle_MAP_TAB; V_ucIndex++ )	
		{
			if( C_StrBle_MAP_TAB[V_ucIndex].ucIndex == v_ucOptIndex )
			{
				V_ucDataId = C_StrBle_MAP_TAB[V_ucIndex].ucaDataId;
				v_ucLen = C_StrBle_MAP_TAB[V_ucIndex].ucaDataLen;
				break;	/*找到了跳出for循环*/
			}
		}
		if( V_ucIndex >= MAX_C_StrBle_MAP_TAB )
		{
			break;	/*找不到就直接退出跳出do-while循环*/
		}

		/*找到对应的索引号了，准备数据*/  
		for( V_ucCntk=0; V_ucCntk< 3; V_ucCntk++ )	/*错了重试，总共3次*/
		{
			/*掉电就退出*/
			if ( GStr_Flag.ucSystem & F_PWOFF_NOW )
			{ 
				break;
			}
			
			v_ucLen = v_ucLen +4;	/*数据长度需要加上4个字节的数据标识长度*/
			if( C_cBleCmd == BLE_RW_READ )	/*读数据，数据长度永远为4，数据标识*/
			{
				v_ucLen = 4;
			}

			LibPub_MemSetBytes( &V_ucTempDataBuf[0], 0xFE, 4 );	/*组织4个FE*/
			V_ucTempDataBuf[4] = 0x68;	/*帧起始符*/
			V_ucTempDataBuf[5] = (uchar8)(v_ucLen&0xFF);	/*长度低8位*/
			V_ucTempDataBuf[6] = (uchar8)(0xFF00&v_ucLen>>8);	/*长度高8位*/
			LibPub_MemSetBytes( &V_ucTempDataBuf[7], 0xFF, 6 );	/*目标设备地址,设置命令为全F*/
			V_ucTempDataBuf[13] = 0x00;		/*链路状态为00，非透传*/
			V_ucTempDataBuf[14] = 0x00;		/*预留扩展字节，默认00*/
			V_ucTempDataBuf[15] = 0x68;		/*帧起始符*/
			V_ucTempDataBuf[16] = C_cBleCmd;		/*控制码*/
			V_ucTempDataBuf[17] = (uchar8)(V_ucDataId>>24);
			V_ucTempDataBuf[18] = (uchar8)(V_ucDataId>>16);
			V_ucTempDataBuf[19] = (uchar8)(V_ucDataId>>8);
			V_ucTempDataBuf[20] = (uchar8)(V_ucDataId);
			LibPub_MemCopyBytes( p_ucDataBuff, &V_ucTempDataBuf[21], v_ucLen-4 );		/*数据域*/
			V_ucTempDataBuf[17+v_ucLen] = LibPub_CalSum( &V_ucTempDataBuf[4], v_ucLen + 13) ;
			V_ucTempDataBuf[v_ucLen + 18] = 0x16;		/*帧尾*/

			V_ucLen = v_ucLen + 19;		/*发送数据总长度*/

			/*开始发送数据*/
			ApiPwOn_UART_SendEn(CH_UART_UART1);
			IEN1  &= ~IEN1_ES1;		/*不需要中断*/
			//BleDrv_WakeUpBle(BLE_TRMODE_AT);	//不采用AT协议，取消唤醒口线

			for( V_ucCnti=0; V_ucCnti< V_ucLen; V_ucCnti++ )
			{
				ACC = V_ucTempDataBuf[V_ucCnti];
				if( P )
				{
					TB81 = 1;
				}
				else
				{
					TB81 = 0;
				}
				SBUF1 = V_ucTempDataBuf[V_ucCnti];
				for( V_usCntj=0; V_usCntj< 2000; V_usCntj++ ) 
				{
					if( TI1 )
					{
						TI1 = 0;
						break;
					}
					LibPub_Delay2us();
				}
				if( V_usCntj>=2000 )
				{
					break;		/*超时一次就退出*/
				}
			}
			
			/*配置串口*/
			SCON1 |=  SCON1_REN1;
			IEN1  &= ~IEN1_ES1;		/*不需要中断*/

			V_ucLen = RXBUF_LEN;
			
			/*开始接收数据*/
			for( V_ucCnti=0; V_ucCnti< V_ucLen; V_ucCnti++ )
			{ 
				for( V_usCntj=0; V_usCntj< 8000; V_usCntj++ ) 
				{
					if( RI1 )
					{
						RI1 = 0;
						V_ucTempDataBuf[V_ucCnti] = SBUF1;  

						V_ucRxFlg = _TRUE;		/*只要有数据回，则认为就是有响应，认为通信成功*/
						break;
					}
				}
				if( V_usCntj>=8000 )
				{
					break;		/*超时一次就退出*/
				}
			}
			if( V_ucRxFlg == _TRUE )		/*有数据返回，就认为本次发送已经发给蓝牙模块，表示成功*/
			{
				V_ucResult = _SUCCESS;
				V_ucCntk = 3;
			}
			
			if( V_ucResult == _SUCCESS )		/*有数据返回，则把数据带回即可*/
			{
				LibPub_MemCopyBytes( &V_ucTempDataBuf[21], &p_ucDataBuff[0], C_StrBle_MAP_TAB[V_ucIndex].ucaDataLen);	/*第18个开始为数据*/
			}
			
			/*蓝牙可以进入休眠*/
			//BleDrv_WakeUpBle(BLE_TRMODE_DIS); 	//不采用AT协议，取消唤醒口线			
		}
	}while(0);

	/*结束退出*/	
	return(V_ucResult);
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    通过蓝牙AT命令操作蓝牙模块，设置或查询模块信息
 *
 *  @param    v_ucTRMode : 唤醒模式   唤醒串口，唤醒后持续，传输AT命令
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
//void BleDrv_WakeUpBle( uchar8 v_ucTRMode )
//{
//	
//	// 先激活蓝牙模块串口，拉低2ms在拉高，表示唤醒，如果持续拉低则表示需要发送的数据是AT命令
//	if(  BLE_TRMODE_DIS & v_ucTRMode )
//	{
//		BLE_WAKEUP_IO_H();	// 拉高，会进入睡眠模式
//	}
//	else
//	{
//		BLE_WAKEUP_IO_L();	// 拉低唤醒	
//		
//		LibPub_DelayNms(3);			// 延迟 3ms
//		
//		if( BLE_TRMODE_UART & v_ucTRMode )	// 如果是串口传输模式，则将AT口拉高，否则持续拉低即可
//		{
//			BLE_WAKEUP_IO_H();;
//		}
//	}   
//} 
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    通信不正常时，复位蓝牙模组
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void BleDrv_BleReset(void)
{
	BLE_POWER_OFF();
	LibPub_DelayNms(150);
	BLE_POWER_ON();
	LibPub_DelayNms(500);
	Gstr_UartComm[CH_BLE].ucCommChStatus = API_COMM_STATUS_IDLE;	/*串口处于空闲状态*/
}