/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    AppDLT645.h                                                                          
**** Brief:       645通信协议头文件                                                                      
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

#ifndef   _APPDLT645_H
#define   _APPDLT645_H

/*-------------------------------- H文件使用说明 -------------------------------------------------------*/
/*
 *  该文件宏定义的前缀为:
 *
 */

 
/*----------------< 包含文件 >----------------------------------*/


/*----------------< 宏定义区 >----------------------------------*/
typedef struct{
	ulong32  	ucaDataId;	        ///* 数据标识 	*///
	uchar8*	    ucaRamAdd;		    ///* RAM地址 	*///
	uchar8		IsWrite;			///* 是否可写	*///
	ushort16	ucaE2pIndex;		///* E2地址索引 *///
	uchar8		ucaE2offset;		///* E2偏移	    *///
	uchar8		ucaDataLen;			///* 数据长度 	*///
	uchar8      IsBCD;				///* 是否为BCD  *///
	uchar8      EEIsHEX;				///* 是否为BCD  *///
}GStr_Comm_MAP;

///* 645数据帧宏定义长度,带4个fe的位置 *///
///* FE FE FE FE 68 A0 A1 A2 A3 A4 A5 68 C  L  Dn CS 16 *///
///* 0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16
#define	API_DLT645_1STFE		0		///* 第1个FE *///
#define	API_DLT645_1ST68H		4		///* 第1个68 *///
#define	API_DLT645_ADDRLSB		5		///* 通信地址低地址 *///
#define	API_DLT645_ADDRMSB		10		///* 通信地址高地址 *///
#define	API_DLT645_2ND68H		11		///* 第2个68 *///
#define	API_DLT645_CMD			12		///* 控制码 *///
#define	API_DLT645_LEN			13		///* 长度 *///
#define	API_DLT645_1STDATA		14		///* 第1个数据 *///
#define	API_DLT645_DI0			14		///* 标识码*///
#define	API_DLT645_PA0			18		///* 密码*///
#define	API_DLT645_C0			22		///* 操作者代码*///
#define	API_DLT645_D0_W			26		///* 数据 *///
#define	API_DLT645_D0_R			18		///* 数据 *///
#define	API_DLT645_D0_R97		16		///* 数据 *///
// 蓝牙数据帧宏定义长度，有两位留着，接收中断的接收数据帧判断需要用到
// #define	API_DLT645_FELen		4					///* 通信地址前FE的个数，会影响其他数据所在的位置 *///
#define	API_DLT645_BLE1STFE		0						///* 第1个FE *///
#define	API_DLT645_BLELENLSB	5						///* 蓝牙数据帧长度（低8位） *///
// #define	API_DLT645_BLELENMSB	6						///* 蓝牙数据帧长度（高8位） *///
#define	API_DLT645_MACADDRLSB	7						///* MAC地址低地址 *///
// #define	API_DLT645_MACADDRMSB	12						///* MAC地址高地址 *///
#define	API_DLT645_BLELinkSTA	13						///* 链路状态 *///
#define	API_DLT645_BLE1STDATA	17						///* 链路用户第一个数据 *///
// #define	API_DLT645_1ST68H		17+API_DLT645_FELen		///* 第1个68 *///
// #define	API_DLT645_ADDRLSB		18+API_DLT645_FELen		///* 通信地址低地址 *///
// #define	API_DLT645_ADDRMSB		23+API_DLT645_FELen		///* 通信地址高地址 *///
// #define	API_DLT645_2ND68H		24+API_DLT645_FELen		///* 第2个68 *///
// #define	API_DLT645_CMD			25+API_DLT645_FELen		///* 控制码 *///
// #define	API_DLT645_LEN			26+API_DLT645_FELen		///* 长度 *///
// #define	API_DLT645_1STDATA		27+API_DLT645_FELen		///* 第1个数据 *///
// #define	API_DLT645_DI0			27+API_DLT645_FELen		///* 标识码*///
// #define	API_DLT645_PA0			31+API_DLT645_FELen		///* 密码*///
// #define	API_DLT645_C0			35+API_DLT645_FELen		///* 操作者代码*///
// #define	API_DLT645_D0_W			39+API_DLT645_FELen		///* 数据 *///
// #define	API_DLT645_D0_R			31+API_DLT645_FELen		///* 数据 *///
// #define	API_DLT645_D0_R97		29+API_DLT645_FELen		///* 数据 *///

///* 645 控制码宏定义 *///
//#define	API_DLT645_CMD_RD_DATA97		0x01	///* 控制码：读数据 *///
//#define	API_DLT645_CMD_WR_DATA97		0x04	///* 控制码：写数据 *///
#define	API_DLT645_CMD_Safe_Certification	0x03	///* 控制码：身份认证 *///
#define	API_DLT645_CMD_Account_Transaction	0x04	///* 控制码：自扩命令，充值退费，身份认证 *///
#define	API_DLT645_CMD_RD_METER_ADDR	    0x13	///* 控制码：读通信地址 *///
#define	API_DLT645_CMD_RD_DATA07		    0x11	///* 控制码：读数据 *///
#define	API_DLT645_CMD_WR_DATA07		    0x14	///* 控制码：写数据 *///
#define	API_DLT645_CMD_WR_METER_ADDR	    0x15	///* 控制码：写通信地址 *///
#define	API_DLT645_CMD_WR_SET_BPS		    0x17	///* 控制码：修改波特率 *///
#define	API_DLT645_CMD_WR_SET_PSW		    0x18	///* 控制码：修改密码 *///
#define	API_DLT645_CMD_METER_CLR		    0x1A	///* 控制码：电表总清 *///
#define	API_DLT645_CMD_RELAY_CTRL		    0x1C	///* 控制码：费控命令 *///
#define	API_DLT645_CMD_FACTORY_1E		    0x1E	///* 控制码：厂内自扩命令 *///
#define	API_DLT645_CMD_FACTORY_1F		    0x1F	///* 控制码：厂内自扩命令 *///
#define	API_DLT645_CMD_RD_EMU_REG		    0x2E	///* 控制码：读emu寄存器地址 *///
#define	API_DLT645_CMD_WR_EMU_REG		    0x2F	///* 控制码：写emu寄存器地址 *///

///* 645 错误信息宏定义 *///
#define	API_DLT645_COMM_ERR_OK			NO_BITS
#define	API_DLT645_COMM_ERR_OTHER		0x01	///* 其他错误 *///
#define	API_DLT645_COMM_ERR_NODATA		0x02	///* 无请求数据 *///
#define	API_DLT645_SAFE_CERT_ERR		0x03	///* 安全认证错误 *///
#define	API_DLT645_COMM_ERR_NOAUTH		0x04 	///* 密码错/未授权 *///
#define	API_DLT645_COMM_ERR_BPSERR		0x08	///* 波特率不能更改 *///
#define	API_DLT645_COMM_ERR_NSQSC		0x10	///* 年时区数超 *///
#define	API_DLT645_COMM_ERR_RSDSC		0x20	///* 日时段数超 *///
#define	API_DLT645_COMM_ERR_FLSC		0x40	///* 费率数超 *///
#define	API_DLT645_COMM_ERR_NOACK		0x80	///* 不应答 *///

///* 通信解析返回类型 *///
#define	API_DLT645_COMM_RD_OK			0x11	///* 读数据正确 *///
#define	API_DLT645_COMM_WR_OK			0x14	///* 写数据正确 *///


#define	API_DLT645_FRAME_RSPN_TIME_MAX	500	///* 帧响应超时时间 以1ms为单位 20≤T≤500ms*///
#define	API_DLT645_FRAME_RSPN_TIME_MIN	20		///* 帧响应超时时间 以1ms为单位 *///
#define	API_DLT645_BYTE_INTEVAL_TIME	500		///* 字节响应时间 以1ms为单位 *///

/* 接收发射接收缓存大小 */
#define API_COMM_BUF_MAX_LEN		190			///* 发射接收缓存大小，最大不要超过255 多数据项设置时，缓存超出，120改为190*///
#define API_COMM_UART_INIT_TIME		1000		///* 1秒，以毫秒为单位 */// 

/*----------------< 变量声明 >----------------------------------*/
extern GU_BoolWordVariable	 						GU_SecurityErr;						///* 安全认证错误字//
	#define	B_Err_Other								GU_SecurityErr.BIT.B0				///* 其它错误*///
	#define	B_Err_RepeatCharge						GU_SecurityErr.BIT.B1				///* 重复充值*///
	#define B_Err_ESAMAuthenFail					GU_SecurityErr.BIT.B2				///* ESAM验证失败*///
	#define B_Err_IDAuthenFail						GU_SecurityErr.BIT.B3				///* 身份认证失败*///
	#define B_Err_CustomNumUnmatch					GU_SecurityErr.BIT.B4				///* 客户编号不匹配*///
	#define	B_Err_RechargeTimesErr					GU_SecurityErr.BIT.B5				///* 充值次数错误*///
	#define	B_Err_OverPurchase						GU_SecurityErr.BIT.B6				///* 购电超囤积*///	
	#define	B_Err_AddrAbnormal						GU_SecurityErr.BIT.B7				///* 地址异常*///	
	#define	B_Err_MeterSuspend						GU_SecurityErr.BIT.B8				///* 电表挂起*///	

extern const 	uchar8	code GT_ucVirtualEsam[26][4];
extern uchar8      bdata 	GV_bDesRepbit;


//extern uchar8      xdata 	GV_ClearFlag;
extern uchar8      xdata GA_ucDesTata[8];				    ///* 3des加密数据 *///
extern uchar8		xdata  GA_ucDesKey[16];					///* 3des加密key *///
extern uchar8		xdata GA_uc7816CommBuffer[250];			///* 7816通信缓存数据*/// 
/*----------------< 函数声明 >----------------------------------*/
extern void ApiDLT645_UARTReceiveDataJudge0( uchar8 v_ucChID, uchar8 v_ucData );
extern void ApiDLT645_UARTReceiveDataJudge1( uchar8 v_ucChID, uchar8 v_ucData );
extern void ApiDLT645_FrameAnalysis( uchar8 v_ucChID); 





#endif
