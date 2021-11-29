/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    ComDefine.h                                                                         
**** Brief:       通用宏定义头文件                                                                      
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

#ifndef   COMDEFINE_H
#define   COMDEFINE_H

/*-------------------------------- H文件使用说明 -------------------------------------------------------*/
/*
 *  该文件宏定义的前缀为:
 *
 */

 
/*----------------< 包含文件 >----------------------------------*/


/*----------------< 宏定义区 >----------------------------------*/
// 功能定义
#ifdef DDSYU666
	#define	METER_TYPE		METER_TYPE_DDSYU666
#endif
#ifdef DDSY666
	#define	METER_TYPE		METER_TYPE_DDSY666
#endif
#ifdef DTSY666
	#define	METER_TYPE		METER_TYPE_DTSY666
#endif 
	#define	METER_TYPE_DDSY666		1		// 单相壁挂表 DDSY666
	#define	METER_TYPE_DDSYU666		2		// 单相导轨表 DDSYU666
	#define	METER_TYPE_DTSY666		3		// 三相四线壁挂表 DTSY666

#define STORAGE_MODE     BIG_MODE
	#define  BIG_MODE    1       //大端模式   低地址高字节
    #define  SMALL_MODE  2      //小端模式    高地址高字节



// EEPROM 存储是否开启
#define	DATA_DEVICE_EEPROM_EN		_ON 	// 不需要就改成_OFF
// 类E2存储是否开启
#define	DATA_DEVICE_INEEPROM_EN		_ON 	// 不需要就改成_OFF 





// 通信通道定义
#define	CH_UART_UART0	0	// uart0485通道
#define	CH_UART_UART1	1	// uart1蓝牙通道
#define	CH_UART_UART2	2	// uart2
#define	CH_UART_UART3	3	// uart3

#define	CH_485		CH_UART_UART0	// 485通道
#define	CH_BLE		CH_UART_UART1	// 蓝牙通道  

#define	UART_CHNUMS		2 


#if( METER_TYPE == METER_TYPE_DDSY666 )
	#define	UART0_ENABLE		_ENABLE		// UART0使能与否
	#define	UART1_ENABLE		_ENABLE		// UART1使能与否
	#define	UART2_ENABLE		_DISABLE	// UART2使能与否
	#define	UART3_ENABLE		_DISABLE	// UART3使能与否 
#endif


#if( METER_TYPE == METER_TYPE_DTSY666 )
	#define	UART0_ENABLE		_ENABLE		// UART0使能与否
	#define	UART1_ENABLE		_ENABLE		// UART1使能与否
	#define	UART2_ENABLE		_DISABLE	// UART2使能与否
	#define	UART3_ENABLE		_DISABLE	// UART3使能与否 
#endif

#if( METER_TYPE == METER_TYPE_DDSYU666 )
	#define	UART0_ENABLE		_DISABLE	// UART0使能与否
	#define	UART1_ENABLE		_ENABLE		// UART1使能与否
	#define	UART2_ENABLE		_DISABLE	// UART2使能与否
	#define	UART3_ENABLE		_DISABLE	// UART3使能与否 
#endif

///总清模式
//#define MoneyClear  0x55  ///钱包初始化总清///不清剩余金额
//#define CommClear   0xAA  ///通信总清

/* 安全流程字相关的常量定义 */
///*######################################################################*///

#define		C_SafeByte_Step0		 			0x00		///* 安全流程第零步 *///
#define		C_SafeByte_Step1		 			0x40		///* 安全流程第一步 *///
#define		C_SafeByte_Step2		 			0x20		///* 安全流程第二步 *///
#define		C_SafeByte_Step3		 			0x08		//* 安全流程第三步 *///
#define		C_SafeByte				 			(C_SafeByte_Step1|C_SafeByte_Step2|C_SafeByte_Step3)	///*安全流程字常量*/// 


#define	EMU_ENABLE		0X55	// 使能计量模块
#define	EMU_DISENABLE	0XAA	// 关闭计量模块

#define	CMP_MODE_HIGHT	0X55	// 高位开始比校数据
#define	CMP_MODE_LOW	0XAA	// 低位开始比较数据

#define C_GreaterThan   0x00	// 大于
#define C_LessThan  	0x01	// 小于
#define C_Equal   		0x02	// 等于

#define C_MAX          0x55
#define C_MIN          0xAA

#define	POWER_ON	0
#define	POWER_OFF	1

#define	INT_Mode	0
#define	TIMEING_Mode	1

#define _OFF       0
#define _ON        1

#define _OK        0
#define _NOK       1

#define _TRUE      0
#define _FALSE     1 

#define	_UNBACKUP  0
#define	_BACKUP    1

#define	_IDLE		0
#define	_BUSY		1

#define	_CRC_EN    0
#define	_CRC_DIS   1

#define _UNLOCK    0
#define _LOCKED    1

#define _DISABLE   0
#define _ENABLE    1

#define _SUCCESS  0
#define _FAILED    1

#define _VALID     0
#define _INVALID   1

#define _LOW       0
#define _HIGH      1

#define NO_BITS   ( 0x00 )
#define _BIT0     ( 0x01 )
#define _BIT1     ( 0x02 )
#define _BIT2     ( 0x04 )
#define _BIT3     ( 0x08 )
#define _BIT4     ( 0x10 )
#define _BIT5     ( 0x20 )
#define _BIT6     ( 0x40 )
#define _BIT7     ( 0x80 )
#define _BIT8     ( 0x0100u )
#define _BIT9     ( 0x0200u )
#define _BIT10    ( 0x0400u )
#define _BIT11    ( 0x0800u )
#define _BIT12    ( 0x1000u )
#define _BIT13    ( 0x2000u )
#define _BIT14    ( 0x4000u )
#define _BIT15    ( 0x8000u )
#define _BIT16    ( 0x010000u )
#define _BIT17    ( 0x020000u )
#define _BIT18    ( 0x040000u )
#define _BIT19    ( 0x080000u )
#define _BIT20    ( 0x100000u )
#define _BIT21    ( 0x200000u )
#define _BIT22    ( 0x400000u )
#define _BIT23    ( 0x800000u )
#define _BIT24    ( 0x01000000u )
#define _BIT25    ( 0x02000000u )
#define _BIT26    ( 0x04000000u )
#define _BIT27    ( 0x08000000u )
#define _BIT28    ( 0x10000000u )
#define _BIT29    ( 0x20000000u )
#define _BIT30    ( 0x40000000u )
#define _BIT31    ( 0x80000000u )
#define B0000_0000 0x00
#define B0000_0001 0x01
#define B0000_0010 0x02
#define B0000_0011 0x03
#define B0000_0100 0x04
#define B0000_0101 0x05
#define B0000_0110 0x06
#define B0000_0111 0x07
#define B0000_1000 0x08
#define B0000_1001 0x09
#define B0000_1010 0x0A
#define B0000_1011 0x0B
#define B0000_1100 0x0C
#define B0000_1101 0x0D
#define B0000_1110 0x0E
#define B0000_1111 0x0F

#define B0001_0000 0x10
#define B0001_0001 0x11
#define B0001_0010 0x12
#define B0001_0011 0x13
#define B0001_0100 0x14
#define B0001_0101 0x15
#define B0001_0110 0x16
#define B0001_0111 0x17
#define B0001_1000 0x18
#define B0001_1001 0x19
#define B0001_1010 0x1A
#define B0001_1011 0x1B
#define B0001_1100 0x1C
#define B0001_1101 0x1D
#define B0001_1110 0x1E
#define B0001_1111 0x1F

#define B0010_0000 0x20
#define B0010_0001 0x21
#define B0010_0010 0x22
#define B0010_0011 0x23
#define B0010_0100 0x24
#define B0010_0101 0x25
#define B0010_0110 0x26
#define B0010_0111 0x27
#define B0010_1000 0x28
#define B0010_1001 0x29
#define B0010_1010 0x2A
#define B0010_1011 0x2B
#define B0010_1100 0x2C
#define B0010_1101 0x2D
#define B0010_1110 0x2E
#define B0010_1111 0x2F

#define B0011_0000 0x30
#define B0011_0001 0x31
#define B0011_0010 0x32
#define B0011_0011 0x33
#define B0011_0100 0x34
#define B0011_0101 0x35
#define B0011_0110 0x36
#define B0011_0111 0x37
#define B0011_1000 0x38
#define B0011_1001 0x39
#define B0011_1010 0x3A
#define B0011_1011 0x3B
#define B0011_1100 0x3C
#define B0011_1101 0x3D
#define B0011_1110 0x3E
#define B0011_1111 0x3F

#define B0100_0000 0x40
#define B0100_0001 0x41
#define B0100_0010 0x42
#define B0100_0011 0x43
#define B0100_0100 0x44
#define B0100_0101 0x45
#define B0100_0110 0x46
#define B0100_0111 0x47
#define B0100_1000 0x48
#define B0100_1001 0x49
#define B0100_1010 0x4A
#define B0100_1011 0x4B
#define B0100_1100 0x4C
#define B0100_1101 0x4D
#define B0100_1110 0x4E
#define B0100_1111 0x4F

#define B0101_0000 0x50
#define B0101_0001 0x51
#define B0101_0010 0x52
#define B0101_0011 0x53
#define B0101_0100 0x54
#define B0101_0101 0x55
#define B0101_0110 0x56
#define B0101_0111 0x57
#define B0101_1000 0x58
#define B0101_1001 0x59
#define B0101_1010 0x5A
#define B0101_1011 0x5B
#define B0101_1100 0x5C
#define B0101_1101 0x5D
#define B0101_1110 0x5E
#define B0101_1111 0x5F

#define B0110_0000 0x60
#define B0110_0001 0x61
#define B0110_0010 0x62
#define B0110_0011 0x63
#define B0110_0100 0x64
#define B0110_0101 0x65
#define B0110_0110 0x66
#define B0110_0111 0x67
#define B0110_1000 0x68
#define B0110_1001 0x69
#define B0110_1010 0x6A
#define B0110_1011 0x6B
#define B0110_1100 0x6C
#define B0110_1101 0x6D
#define B0110_1110 0x6E
#define B0110_1111 0x6F

#define B0111_0000 0x70
#define B0111_0001 0x71
#define B0111_0010 0x72
#define B0111_0011 0x73
#define B0111_0100 0x74
#define B0111_0101 0x75
#define B0111_0110 0x76
#define B0111_0111 0x77
#define B0111_1000 0x78
#define B0111_1001 0x79
#define B0111_1010 0x7A
#define B0111_1011 0x7B
#define B0111_1100 0x7C
#define B0111_1101 0x7D
#define B0111_1110 0x7E
#define B0111_1111 0x7F

#define B1000_0000 0x80
#define B1000_0001 0x81
#define B1000_0010 0x82
#define B1000_0011 0x83
#define B1000_0100 0x84
#define B1000_0101 0x85
#define B1000_0110 0x86
#define B1000_0111 0x87
#define B1000_1000 0x88
#define B1000_1001 0x89
#define B1000_1010 0x8A
#define B1000_1011 0x8B
#define B1000_1100 0x8C
#define B1000_1101 0x8D
#define B1000_1110 0x8E
#define B1000_1111 0x8F

#define B1001_0000 0x90
#define B1001_0001 0x91
#define B1001_0010 0x92
#define B1001_0011 0x93
#define B1001_0100 0x94
#define B1001_0101 0x95
#define B1001_0110 0x96
#define B1001_0111 0x97
#define B1001_1000 0x98
#define B1001_1001 0x99
#define B1001_1010 0x9A
#define B1001_1011 0x9B
#define B1001_1100 0x9C
#define B1001_1101 0x9D
#define B1001_1110 0x9E
#define B1001_1111 0x9F

#define B1010_0000 0xA0
#define B1010_0001 0xA1
#define B1010_0010 0xA2
#define B1010_0011 0xA3
#define B1010_0100 0xA4
#define B1010_0101 0xA5
#define B1010_0110 0xA6
#define B1010_0111 0xA7
#define B1010_1000 0xA8
#define B1010_1001 0xA9
#define B1010_1010 0xAA
#define B1010_1011 0xAB
#define B1010_1100 0xAC
#define B1010_1101 0xAD
#define B1010_1110 0xAE
#define B1010_1111 0xAF

#define B1011_0000 0xB0
#define B1011_0001 0xB1
#define B1011_0010 0xB2
#define B1011_0011 0xB3
#define B1011_0100 0xB4
#define B1011_0101 0xB5
#define B1011_0110 0xB6
#define B1011_0111 0xB7
#define B1011_1000 0xB8
#define B1011_1001 0xB9
#define B1011_1010 0xBA
#define B1011_1011 0xBB
#define B1011_1100 0xBC
#define B1011_1101 0xBD
#define B1011_1110 0xBE
#define B1011_1111 0xBF

#define B1100_0000 0xC0
#define B1100_0001 0xC1
#define B1100_0010 0xC2
#define B1100_0011 0xC3
#define B1100_0100 0xC4
#define B1100_0101 0xC5
#define B1100_0110 0xC6
#define B1100_0111 0xC7
#define B1100_1000 0xC8
#define B1100_1001 0xC9
#define B1100_1010 0xCA
#define B1100_1011 0xCB
#define B1100_1100 0xCC
#define B1100_1101 0xCD
#define B1100_1110 0xCE
#define B1100_1111 0xCF

#define B1101_0000 0xD0
#define B1101_0001 0xD1
#define B1101_0010 0xD2
#define B1101_0011 0xD3
#define B1101_0100 0xD4
#define B1101_0101 0xD5
#define B1101_0110 0xD6
#define B1101_0111 0xD7
#define B1101_1000 0xD8
#define B1101_1001 0xD9
#define B1101_1010 0xDA
#define B1101_1011 0xDB
#define B1101_1100 0xDC
#define B1101_1101 0xDD
#define B1101_1110 0xDE
#define B1101_1111 0xDF

#define B1110_0000 0xE0
#define B1110_0001 0xE1
#define B1110_0010 0xE2
#define B1110_0011 0xE3
#define B1110_0100 0xE4
#define B1110_0101 0xE5
#define B1110_0110 0xE6
#define B1110_0111 0xE7
#define B1110_1000 0xE8
#define B1110_1001 0xE9
#define B1110_1010 0xEA
#define B1110_1011 0xEB
#define B1110_1100 0xEC
#define B1110_1101 0xED
#define B1110_1110 0xEE
#define B1110_1111 0xEF

#define B1111_0000 0xF0
#define B1111_0001 0xF1
#define B1111_0010 0xF2
#define B1111_0011 0xF3
#define B1111_0100 0xF4
#define B1111_0101 0xF5
#define B1111_0110 0xF6
#define B1111_0111 0xF7
#define B1111_1000 0xF8
#define B1111_1001 0xF9
#define B1111_1010 0xFA
#define B1111_1011 0xFB
#define B1111_1100 0xFC
#define B1111_1101 0xFD
#define B1111_1110 0xFE
#define B1111_1111 0xFF
/*----------------< 变量声明 >----------------------------------*/


/*----------------< 函数声明 >----------------------------------*/






#endif
