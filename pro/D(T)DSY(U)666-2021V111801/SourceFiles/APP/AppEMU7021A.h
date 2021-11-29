/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    AppEMU7021A.h                                                                          
**** Brief:       计量模块                                                                      
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

#ifndef   _APPEMU7021A_H
#define   _APPEMU7021A_H

#if ( METER_TYPE != METER_TYPE_DTSY666 )
/*-------------------------------- H文件使用说明 -------------------------------------------------------*/
/*
 *  该文件宏定义的前缀为:
 *
 */

 
/*----------------< 包含文件 >----------------------------------*/


/*----------------< 宏定义区 >----------------------------------*/




// 计量寄存器定义 间接寻址寄存器
// 计量参数寄存器
// 计量参数寄存器除FREQ外都为只读寄存器， 只能通过EADR和EDTAH/EDTAM/EDTAL寄存器间接读取。
#define		C_ECADR_I1DTA 			0x00
#define		C_ECADR_I2DTA 			0x01
#define		C_ECADR_VDTA  			0x02
#define		C_ECADR_APWR1  			0x03
#define		C_ECADR_RPWR1 			0x04
#define		C_ECADR_APWR2 			0x05
#define		C_ECADR_RPWR2 			0x06
#define		C_ECADR_AERY  			0x07
#define		C_ECADR_RERY  			0x08
#define		C_ECADR_FREQ			0x09
#define		C_ECADR_I1Rms 			0x0A
#define		C_ECADR_I2Rms  			0x0B
#define		C_ECADR_VRms  			0x0C
#define		C_ECADR_WPA				0x0D
#define		C_ECADR_VARPA 			0x0E
#define		C_ECADR_APWRA1			0x0F
#define		C_ECADR_RPWRA1			0x10
#define		C_ECADR_APWRA2 			0x11
#define		C_ECADR_RPWRA2 			0x12
#define		C_ECADR_AERYL  			0x13
#define		C_ECADR_RERYL  			0x14
#define		C_ECADR_VDTAMAX 		0x15
#define		C_ECADR_AERY_CONSTH 	0x16
#define		C_ECADR_RERY_CONSTH  	0x17
#define		C_ECADR_AERY_CONSTL 	0x18
#define		C_ECADR_RERY_CONSTL  	0x19
#define		C_ECADR_WPA_CONST		0x1A
#define		C_ECADR_VARPA_CONST 	0x1B
#define		C_ECADR_RMPATWR 		0x1C
#define		C_ECADR_RMTQPWR 		0x1D
#define		C_ECADR_RMTIRMS 		0x1E
#define		C_ECADR_RMTVRMS 		0x1F
#define		C_ECADR_APWRA1L 		0x20
#define		C_ECADR_RPWRA1L 		0x21
#define		C_ECADR_APWRA2L 		0x22
#define		C_ECADR_RPWRA2L 		0x23
#define		C_ECADR_APWR1L 			0x24
#define		C_ECADR_RPWR1L 			0x25
#define		C_ECADR_APWR2L 			0x26
#define		C_ECADR_RPWR2L 			0x27

// 计量参数寄存器 
#define		  C_EPADR_EMUCFG0       0x30			// 30H EMUCFG0 3 EMU计量配置寄存器0
#define     C_EPADR_EMUCFG1       0x31			// 31H EMUCFG1 3 EMU计量配置寄存器1
#define     C_EPADR_EMUCFG2       0x32			// 32H EMUCFG2 3 EMU计量配置寄存器2
#define     C_EPADR_EMUCFG3       0x33			// 33H EMUCFG3 2 EMU计量配置寄存器3
#define     C_EPADR_W1GAIN        0x34			// 34H W1GAIN     2 通道1功率增益寄存器 (有功无功使用同一组)
#define     C_EPADR_P1CAL         0x35			// 35H P1CAL      2 通道1电压电流相位补偿寄存器
#define     C_EPADR_W2GAIN        0x36			// 36H W2GAIN     2 通道2功率增益寄存器 (有功无功使用同一组)
#define     C_EPADR_P2CAL         0x37			// 37H P2CAL      2 通道2电压电流相位补偿寄存器
#define     C_EPADR_I2GAIN        0x38			// 38H I2GAIN     2 通道2电流增益设置寄存器
#define     C_EPADR_WATT1OS       0x39			// 39H WATT1OS    3 通道1有功功率偏置
#define     C_EPADR_WATT2OS       0x3A			// 3AH WATT2OS    3 通道2有功功率偏置
#define     C_EPADR_VAR1OS        0x3B			// 3BH VAR1OS     3 通道1无功功率偏置
#define     C_EPADR_VAR2OS        0x3C			// 3CH VAR2OS     3 通道2无功功率偏置
#define     C_EPADR_IRMS1OS       0x3D			// 3DH IRMS1OS    3 通道1电流有效值偏置
#define     C_EPADR_IRMS2OS       0x3E			// 3EH IRMS2OS    3 通道2电流有效值偏置
#define     C_EPADR_VRMSOS        0x3F			// 3FH VRMSOS     3 电压有效值偏置
#define     C_EPADR_ADCOSI1       0x40			// 40H ADCOSI1    2 电流通道1 ADC偏置设置SH79F7021A 
#define     C_EPADR_ADCOSI2       0x41			// 41H ADCOSI2    2 电流通道1 ADC偏置设置
#define     C_EPADR_ADCOSU        0x42			// 42H ADCOSU     2 电压通道 ADC偏置设置
#define     C_EPADR_SPTSP         0x43			// 43H SPTSP      2 有功功率启动设置寄存器
#define     C_EPADR_SPTSQ         0x44			// 44H SPTSQ      2 无功功率启动设置寄存器
#define     C_EPADR_VCONST        0x45			// 45H VCONST     3 掉零线电压固定值
#define     C_EPADR_SAGTHR        0x46			// 46H SAGTHR     2 失压门限设置
#define     C_EPADR_SAGCNT        0x47			// 47H SAGCNT     2 失压采样计数
#define     C_EPADR_ICONT         0x48			// 48H ICONT      2 输出脉冲频率设置
#define     C_EPADR_PCNT          0x49			// 49H PCNT       2 快速有功脉冲计数， 二进制补码表示有符号值
#define     C_EPADR_QCNT          0x4A			// 4AH QCNT       2 快速无功脉冲计数， 二进制补码表示有符号值
#define     C_EPADR_SUMSAMPS      0x4B			// 4BH SUMSAMPS   2 计算周期设置寄存器
#define     C_EPADR_APCONST       0x4C			// 4CH APCONST    3 有功功率常数设置寄存器
#define     C_EPADR_RPCONST       0x4D			// 4DH RPCONST    3 无功功率常数设置寄存器
#define     C_EPADR_PCNT_CONST    0x4E			// 4EH PCNT_CONST 2 快速有功常数脉冲计数， 二进制补码表示有符号值
#define     C_EPADR_QCNT_CONST    0x4F			// 4FH QCNT_CONST 2 快速无功常数脉冲计数， 二进制补码表示有符号值
#define     C_EPADR_DIMTHR        0x50			// 50H DIMTHR     3 DIMMER判断阀值设置
#define     C_EPADR_DIMCNT        0x51			// 51H DIMCNT     1 DIMMER超差计数阀值
#define     C_EPADR_SAMPCON       0x52			// 52H SAMPCON    1 波形采样配置寄存器								
#define     C_EPADR_RMTCON        0x53			// 
#define     C_EPADR_RMTVREFS      0x54			// 
#define     C_EPADR_RMTVREFR      0x55			// 
#define     C_EPADR_RMTPCALP      0x56			// 
#define     C_EPADR_RMTFLAG       0x57			// 
#define     C_EPADR_HPFEFFB       0x5A			// 5AH HPFEFFB 3 高通系数B
#define     C_EPADR_HPFEFFA       0x5B			// 5BH HPFEFFA 3 高通系数A
#define     C_EPADR_LPFEFFB       0x60			// 60H LPFEFFB 3 低通系数B
#define     C_EPADR_LPFEFFA       0x61			// 61H LPFEFFA 3 低通系数A
#define     C_EPADR_ULPCTRL       0x62			// 62H ULPCTRL 2 超低功耗设置（控制DIMMER和无功是否工作）
#define     C_EPADR_AERY1H        0x70			// 70H AERY1H  3 通道1有功电能累加值高位
#define     C_EPADR_RERY1H        0x71			// 71H RERY1H  3 通道1无功电能累加值高位  
#define     C_EPADR_AERY1M        0x72			// 72H AERY1M  3 通道1有功电能累加值中位
#define		C_EPADR_RERY1M        0x73			// 73H RERY1M  3 通道1无功电能累加值中位
#define		C_EPADR_AERY1L        0x74			// 74H AERY1L  2 通道1有功电能累加值低位
#define		C_EPADR_RERY1L        0x75			// 75H RERY1L  2 通道1无功电能累加值低位
#define		C_EPADR_AERY2H        0x76			// 76H AERY2H  3 通道2有功电能累加值高位
#define		C_EPADR_RERY2H        0x77			// 77H RERY2H  3 通道2无功电能累加值高位
#define		C_EPADR_AERY2M        0x78			// 78H AERY2M  3 通道2有功电能累加值中位
#define		C_EPADR_RERY2M        0x79			// 79H RERY2M  3 通道2无功电能累加值中位
#define		C_EPADR_AERY2L        0x7A			// 7AH AERY2L  2 通道2有功电能累加值低位
#define		C_EPADR_RERY2L        0x7B			// 7BH RERY2L  2 通道2无功电能累加值低位
#define		C_EPADR_ICONT1        0x7C			// 7CH ICONT1  2 第二路输出脉冲频率设置
#define		C_EPADR_EMUCFG4       0x7D			// 7DH EMUCFG4 2 EMU计量配置寄存器4

 
//#define		C_EPADR_EMUCFG0_DATA	( EMUCFG0_APGAI_16 | EMUCFG0_ADCUON | EMUCFG0_ADCI1ON ) // 固定32K，电压通道增益：2倍， 电流通道1增益16倍，打开电压和电流通道1ADC
//#define		C_EPADR_EMUCFG1_DATA	( EMUCFG1_POL | EMUCFG1_PFEN | EMUCFG1_QRUN | EMUCFG1_PRUN | EMUCFG1_Cmodeen ) //低电平有效，打开PF引脚输出，有功/无功累加使能，累加模块总使能
//#define		C_EPADR_EMUCFG2_DATA	( 


/*----------------< 变量声明 >----------------------------------*/
typedef	struct{
	uchar8		ucEmuAddr;			///* 校表参数地址 *///
	ulong32		ulEmuRegData;		///* 对应值 *///
}EMU_EPADR_Type;
#define	EMU_EPADR_Type_LEN		sizeof( EMU_EPADR_Type )

typedef	struct{	/* 注意要和EMU_CALPARA_DEF_TAB表格顺序要一一对应 */
	ulong32		ulaCalPara[5];
// 	ulong32		ulICONST;			///* 输出脉冲频率，相当于钜泉芯片的HFCONST *///
// 	ulong32		ulW1GAIN;			///* 通道1有功功率增益调校寄存器 *///
// 	ulong32		ulP1CAL;			///* 通道1相位调校寄存器 *///	
// 	ulong32		ulWATT1OS;			///* 通道1小信号调校寄存器 */// 
// 	ulong32		ulSPTSP;			///* 潜动阈值 */// 
	ushort16	usCRC16;			///* 校验 *///
}EMU_CALPARA_Type;
#define	EMU_CALPARA_Type_LEN		sizeof( EMU_CALPARA_Type )

typedef	struct{
	ulong32     ulaKmsuip[3];
// 	ulong32		ulKmsU;				///* 电压有效值系数 *///
// 	ulong32		ulKmsP;				///* 功率有效值系数 *///	
// 	ulong32		ulKmsI;				///* 电流有效值系数 *///
	ushort16	usCRC16;			///* 校验 *///
}EMU_UIPKms_Type;
#define	EMU_UIPKms_Type_LEN		sizeof( EMU_UIPKms_Type )

typedef	struct{
	uchar8		ucCommDI1;			///* 对应DI1 *///
	uchar8		ucEmuAddr;			///* 对应地址 *///
}EMU_COMM_CAL_TAB_Type;
#define	EMU_COMM_CAL_TAB_Type_LEN		sizeof( EMU_COMM_CAL_TAB_Type )
/*----------------< 函数声明 >----------------------------------*/
// extern INT32U  ApiEMU_Read_ECADR(INT8U xdata address);
// extern void    ApiEMU_Write_ECADR(INT8U xdata address, INT32U xdata Data) ;
extern ulong32 ApiEMU_ReadEmuReg( ushort16 v_usRegAddress );
extern void    ApiEMU_WriteEmuReg( ushort16 v_usRegAddress, ulong32 v_ulRegData );
extern void    ApiEMU_CommStartCal( uchar8 v_ucChID );
extern void    ApiEMU_CommEndCal( uchar8 v_ucChID );
extern uchar8  ApiEMU_CommErrCal( uchar8 v_ucChID );
extern void    ApiEMU_EMUInit( void );
extern void	   ApiEMU_EMUParaCheck( void );
extern uchar8  ApiEMU_UpdateUIP(void);
extern uchar8  ApiEMU_GetDirP(void);
extern void ApiEMU_DisOrEnable(uchar8 v_ucWorkMode);


#endif 


#endif
