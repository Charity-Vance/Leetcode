/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    BLEDrv.h                                                                          
**** Brief:       蓝牙驱动头文件                                                                     
**** Author:      peter.he@chint.com                                                                 
**** Version:     V1.0                                                                               
**** Date:        2019年3月14日                                                                         
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

#ifndef   BLEDRV_H
#define   BLEDRV_H

/*-------------------------------- H文件使用说明 -------------------------------------------------------*/
/*
 *  该文件宏定义的前缀为:
 *
 */

 
/*----------------< 包含文件 >----------------------------------*/


/*----------------< 宏定义区 >----------------------------------*/
#if( METER_TYPE == METER_TYPE_DDSY666 )
	#define BLE_WAKEUP_IO_H()  { GPIO_IOCFG_P3_DIR_O(5);GPIO_IOCFG_P3_SET_1( 5);}	// 拉高，会进入睡眠模式
	#define BLE_WAKEUP_IO_L()  { GPIO_IOCFG_P3_DIR_O(5);GPIO_IOCFG_P3_SET_0( 5);}	// 拉高，会进入睡眠模式
	
	#define BLE_POWER_ON()     { GPIO_IOCFG_P3_DIR_O(6);GPIO_IOCFG_P3_SET_0( 6);}	// 拉低，供电
	#define BLE_POWER_OFF()    { GPIO_IOCFG_P3_DIR_O(6);GPIO_IOCFG_P3_SET_1( 6);}	// 拉高，断电，断电到供电延时500ms
	
#endif

#if( METER_TYPE == METER_TYPE_DTSY666 )
	#define BLE_WAKEUP_IO_H()  { GPIO_IOCFG_P3_DIR_O(5);GPIO_IOCFG_P3_SET_1( 5);}	// 拉高，会进入睡眠模式
	#define BLE_WAKEUP_IO_L()  { GPIO_IOCFG_P3_DIR_O(5);GPIO_IOCFG_P3_SET_0( 5);}	// 拉高，会进入睡眠模式
	
	#define BLE_POWER_ON()     { GPIO_IOCFG_P3_DIR_O(6);GPIO_IOCFG_P3_SET_0( 6);}	// 拉低，供电
	#define BLE_POWER_OFF()    { GPIO_IOCFG_P3_DIR_O(6);GPIO_IOCFG_P3_SET_1( 6);}	// 拉高，断电，断电到供电延时500ms
	
#endif
	
#if( METER_TYPE == METER_TYPE_DDSYU666 )
	#define BLE_WAKEUP_IO_H()  { GPIO_IOCFG_P5_DIR_O(1);GPIO_IOCFG_P5_SET_1( 1);}	// 拉高，会进入睡眠模式
	#define BLE_WAKEUP_IO_L()  { GPIO_IOCFG_P5_DIR_O(1);GPIO_IOCFG_P5_SET_0( 1);}	// 拉高，会进入睡眠模式
	
	#define BLE_POWER_ON()     { GPIO_IOCFG_P5_DIR_O(0);GPIO_IOCFG_P5_SET_0( 0);}	// 拉低，供电
	#define BLE_POWER_OFF()    { GPIO_IOCFG_P5_DIR_O(0);GPIO_IOCFG_P5_SET_1( 0);}	// 拉高，断电
#endif	
	
#define	BLE_RW_READ			2	///*读取本模块参数*///
#define	BLE_RW_WRITE		1	///*设置本模块参数*///


#define	BLE_TRMODE_UART			_BIT0	// 唤醒仅操作串口
#define	BLE_TRMODE_AT			_BIT1	// 唤醒需要传输AT命令
#define	BLE_TRMODE_DIS			_BIT2	// 传输结束后操作一下，特别是AT命令时

// 蓝牙状态宏定义
#define	BLE_STAT_IDLE		0x00	// 空闲
#define	BLE_STAT_ADV_ON		0x01	// 起动广播
#define	BLE_STAT_SCAN_ON	0x02	// 起动扫描
#define	BLE_STAT_CONNECTING	0x03	// 连接中状态
#define	BLE_STAT_CONNECTED	0x04	// 连接
#define	BLE_STAT_ERP		0x05	// 错误
#define	BLE_STAT_BUSY		0x06	// 通信中
#define	BLE_STAT_MAC_MOD	0x07	// 修改表地址
#define	BLE_STAT_RST		0x08	// 模块复位
#define	BLE_STAT_ERRREP		0x09	// 模块连接上报异常
#define	BLE_STAT_NORESP		0xff	// 回复数据不对

/*蓝牙参数参数定义*/
#define BLE_MAC_Len			21		/*本设备MAC地址、名称、配对码*/
#define BLE_TPL_Len			1		/*发射功率*/
#define BLE_EADV_Len		31		/*广播内容*/
#define BLE_MOD_Len			1		/*工作模式*/
#define BLE_TTP_Len			1		/*透传协议*/
#define BLE_STAT_Len		6		/*连接设备的MAC*/
#define BLE_MFV_Len			32		/*固件版本号*/

typedef enum{
	 
	COMM_BLE_MAC = 0,		/*本设备MAC地址*/
	COMM_BLE_TPL,			/*蓝牙模块发射功率*/
	COMM_BLE_EADV,			/*设置广播*/
	COMM_BLE_MOD,			/*蓝牙模块工作模式*/
	COMM_BLE_TTP,			/*蓝牙模块透传模式*/
	COMM_BLE_STAT,			/*当前连接的设备MAC*/
	COMM_BLE_MFV,			/*模块固件版本号*/
	
	MAX_BLE_INDEX,		// 索引最大值
	
}BLE_DRV_OPERATION_INDEX;	// 蓝牙设备操作索引
/*----------------< 变量声明 >----------------------------------*/


/*----------------< 函数声明 >----------------------------------*/
extern void BleDrv_SetBleRunPara( void );
extern void BleDrv_InitBleRunPara( void );
extern void BleDrv_WakeUpBle( uchar8 v_ucTRMode );
extern void BleDrv_InitPwn(void);

extern uchar8 BleDrv_GetBleStat(void);
extern uchar8 BleDrv_GetBleADVP(uchar8 *p_ucDataBuf);
extern uchar8 BleDrv_GetBleKey(uchar8 *p_ucDataBuf);
extern uchar8 BleDrv_GetBleMac(uchar8 *p_ucDataBuf);
extern uchar8 BleDrv_GetBleName(uchar8 *p_ucDataBuf);
extern uchar8 BleDrv_GetBlePSK( uchar8 *p_ucDataBuf );

extern uchar8 BleDrv_SetBleStat(void);
extern uchar8 BleDrv_SetBleADVP(uchar8 *p_ucDataBuf);
extern uchar8 BleDrv_SetBleCLRBond( uchar8 *p_ucDataBuf );
extern uchar8 BleDrv_SetBleKey(uchar8 *p_ucDataBuf);
extern uchar8 BleDrv_SetBleMac(uchar8 *p_ucDataBuf);
extern uchar8 BleDrv_SetBleName(uchar8 *p_ucDataBuf);
extern uchar8 BleDrv_SetBlePSK( uchar8 *p_ucDataBuf );
extern uchar8 BleDrv_SetBleSMPLv(uchar8 *p_ucDataBuf);
extern uchar8 BleDrv_GetBleSMPLv(uchar8 *p_ucDataBuf);
extern uchar8 BleDrv_SetBleTPL(uchar8 *p_ucDataBuf);
extern uchar8 BleDrv_GetBleTPL(uchar8 *p_ucDataBuf);
extern uchar8 BleDrv_CommSetBlePara(uchar8 v_ucComIndex, uchar8 v_ucLen, uchar8 *p_ucDataBuf);
extern uchar8 BleDrv_CommGetBlePara(uchar8 v_ucComIndex, uchar8 v_ucLen, uchar8 *p_ucDataBuf);

extern uchar8 BleDrv_BleParaChk(uchar8 v_ucMode);
extern void BleDrv_BleStatuChk(void);
extern uchar8 BleDrv_GetBleUartSta(void);
extern void BleDrv_BleReset(void);
#endif
