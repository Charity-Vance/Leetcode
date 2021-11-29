/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    AppEMU7021A.c                                                                         
**** Brief:       计量模块                                                                     
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

#if ( METER_TYPE != METER_TYPE_DTSY666)
/*----------------< 宏定义区 >----------------------------------*/

#define	C_EPDAT_EMUCFG3  0x000000E8u
#define	C_EPDAT_EMUCFG2  0x00000C84u
#define	C_EPDAT_EMUCFG1  0x00A000C1u
#define	C_EPDAT_EMUCFG0  0x00000035u
/*----------------< 常量定义 >----------------------------------*/
EMU_EPADR_Type code EMU_EPADR_INIT_TAB[] = {
	// 地址                       数据
// 	{ C_EPADR_EMUCFG0,         0x00000035 },     // 30H EMUCFG0    3 EMU计量配置寄存器0  固定32K，电压通道增益：2倍， 电流通道1增益16倍，打开电压和电流通道1ADC
// 	{ C_EPADR_EMUCFG1,         0x00A000C1 },     // 31H EMUCFG1    3 EMU计量配置寄存器1  低电平有效，打开PF引脚输出，有功/无功累加使能，累加模块总使能
//	{ C_EPADR_EMUCFG2,         0x00000C84 },     // 32H EMUCFG2    3 EMU计量配置寄存器2  默认值
//	{ C_EPADR_EMUCFG3,         0x000000E8 },     // 33H EMUCFG3    2 EMU计量配置寄存器3  默认值
	
//	{ C_EPADR_W1GAIN ,         0x00000000 },     // 34H W1GAIN     RW 2 通道1功率增益寄存器 ***
//	{ C_EPADR_P1CAL  ,         0x00000000 },     // 35H P1CAL      RW 2 通道1电压电流相位补偿寄存器 ***
    { C_EPADR_W2GAIN ,         0x00000000 },     // 36H W2GAIN     RW 2 通道2功率增益寄存器
    { C_EPADR_P2CAL  ,         0x00000000 },     // 37H P2CAL      RW 2 通道2电压电流相位补偿寄存器
    { C_EPADR_I2GAIN ,         0x00000000 },     // 38H I2GAIN     RW 2 通道2电流增益设置
//	{ C_EPADR_WATT1OS,         0x00000000 },	 // 39H WATT1OS    RW 3 通道1有功功率偏置 ***
    { C_EPADR_WATT2OS,         0x00000000 },     // 3AH WATT2OS    RW 3 通道2有功功率偏置
	{ C_EPADR_VAR1OS ,         0x00000000 },	 // 3BH VAR1OS     RW 3 通道1无功功率偏置
	{ C_EPADR_VAR2OS ,         0x00000000 },     // 3CH VAR2OS     RW 3 通道2无功功率偏置
	{ C_EPADR_IRMS1OS,         0x00FD2700 },     // 3DH IRMS1OS    RW 3 通道1电流有效值偏置   //电流有偏置 固定写为FD2700（偏置为16mA）
    { C_EPADR_IRMS2OS,         0x00000000 },     // 3EH IRMS2OS    RW 3 通道2电流有效值偏置
	{ C_EPADR_VRMSOS ,         0x00000000 },     // 3FH VRMSOS     RW 3 电压有效值偏置
    { C_EPADR_ADCOSI1,         0x00000000 },     // 40H ADCOSI1    RW 2 电流通道1 ADC偏置设置
    { C_EPADR_ADCOSI2,         0x00000000 },     // 41H ADCOSI2    RW 2 电流通道2 ADC偏置设置
    { C_EPADR_ADCOSU ,         0x00000000 },     // 42H ADCOSU     RW 2 电压通道ADC偏置设置
//	{ C_EPADR_SPTSP  ,         0x0000001B },	 // 43H SPTSP      RW 2 有功功率启动设置寄存器 ***
	{ C_EPADR_SPTSQ  ,         0x0000001B },     // 44H SPTSQ      RW 2 无功功率启动设置寄存器
    { C_EPADR_VCONST ,         0x00000000 },     // 45H VCONST     RW 3 掉零线电压固定值
    { C_EPADR_SAGTHR ,         0x00000000 },     // 46H SAGTHR     RW 2 失压门限设置
    { C_EPADR_SAGCNT ,         0x00000180 },     // 47H SAGCNT     RW 2 失压采样计数
//	{ C_EPADR_ICONT  ,         0x00000080 },	 // 48H ICONT      RW 2 输出脉冲频率设置 ***
//	{ C_EPADR_PCNT   ,         0x00000000 },     // 49H PCNT       RW 2 快速有功脉冲计数
//	{ C_EPADR_QCNT   ,         0x00000000 },     // 4AH QCNT       RW 2 快速无功脉冲计数
	{ C_EPADR_SUMSAMPS  ,      0x000001ff },     // 4BH SUMSAMPS   RW 2 计算周期设置寄存器
//	{ C_EPADR_APCONST   ,      0x00000000 },     // 4CH APCONST    R  3 有功功率常数设置寄存器
//	{ C_EPADR_RPCONST   ,      0x00000000 },     // 4DH RPCONST    R  3 无功功率常数设置寄存器
// 	{ C_EPADR_PCNT_CONST,      0x00000000 },     // 4EH PCNT_CONST RW 2 快速有功常数脉冲计数
// 	{ C_EPADR_QCNT_CONST,      0x00000000 },     // 4FH QCNT_CONST RW 2 快速无功常数脉冲计数
	{ C_EPADR_DIMTHR    ,      0x00000000 },     // 50H DIMTHR     RW 3 DIMMER 判断阀值设置
	{ C_EPADR_DIMCNT    ,      0x00000004 },     // 51H DIMCNT     RW 1 DIMMER超差计数阀值
	{ C_EPADR_SAMPCON   ,      0x00000000 },     // 52H SAMPCON    RW 1 EMU波形采样配置寄存器
	{ C_EPADR_RMTCON    ,      0x00000000 },     // @7021A无关，配置成默认即可
	{ C_EPADR_RMTVREFS  ,      0x00000000 },     // @7021A无关，配置成默认即可
	{ C_EPADR_RMTVREFR  ,      0x00000000 },     // @7021A无关，配置成默认即可
	{ C_EPADR_RMTPCALP  ,      0x00000000 },     // @7021A无关，配置成默认即可
	{ C_EPADR_RMTFLAG   ,      0x00000000 },     // @7021A无关，配置成默认即可
	{ C_EPADR_HPFEFFB   ,      0x00800000 },     // 5AH HPFEFFB   RW  3 高通系数B
	{ C_EPADR_HPFEFFA   ,      0x007FF547 },     // 5BH HPFEFFA   RW  3 高通系数A
	{ C_EPADR_LPFEFFB   ,      0x0000055D },     // 60H LPFEFFB   RW  3 低通系数B
	{ C_EPADR_LPFEFFA   ,      0x007FF546 },     // 61H LPFEFFA   RW  3 低通系数A
	
	#if ( METER_TYPE == METER_TYPE_DDSY666)
	{ C_EPADR_ULPCTRL,         0x00000000 },     // 62H ULPCTRL   RW  2 超低功耗设置（控制DIMMER和无功是否工作）
	{ C_EPADR_ICONT1 ,         0x00000080 },     // 7CH ICONT1    RW  2 第二路输出脉冲频率设置
	{ C_EPADR_EMUCFG4,         0x00000000 },     // 7DH EMUCFG4   RW  2 EMU计量配置寄存器4
	#endif
	
	#if ( METER_TYPE == METER_TYPE_DDSYU666)	 // 导轨表用的是7019，这个寄存器读出来是0x007FF546
	{ C_EPADR_ULPCTRL,         0x00000000 },     // 62H ULPCTRL   RW  2 超低功耗设置（控制DIMMER和无功是否工作）
	{ C_EPADR_ICONT1 ,         0x00000080 },     // 7CH ICONT1    RW  2 第二路输出脉冲频率设置
	{ C_EPADR_EMUCFG4,         0x00000000 },     // 7DH EMUCFG4   RW  2 EMU计量配置寄存器4
	#endif
	
// 	{ C_EPADR_AERY1H ,         0x00000000 },     // 70H AERY1H    R   3 通道1有功电能累加值高位
// 	{ C_EPADR_RERY1H ,         0x00000000 },     // 71H RERY1H    R   3 通道1无功电能累加值高位  
// 	{ C_EPADR_AERY1M ,         0x00000000 },     // 72H AERY1M    R   3 通道1有功电能累加值中位
// 	{ C_EPADR_RERY1M ,         0x00000000 },     // 73H RERY1M    R   3 通道1无功电能累加值中位
// 	{ C_EPADR_AERY1L ,         0x00000000 },     // 74H AERY1L    R   2 通道1有功电能累加值低位
// 	{ C_EPADR_RERY1L ,         0x00000000 },     // 75H RERY1L    R   2 通道1无功电能累加值低位
// 	{ C_EPADR_AERY2H ,         0x00000000 },     // 76H AERY2H    R   3 通道2有功电能累加值高位
// 	{ C_EPADR_RERY2H ,         0x00000000 },     // 77H RERY2H    R   3 通道2无功电能累加值高位
// 	{ C_EPADR_AERY2M ,         0x00000000 },     // 78H AERY2M    R   3 通道2有功电能累加值中位
// 	{ C_EPADR_RERY2M ,         0x00000000 },     // 79H RERY2M    R   3 通道2无功电能累加值中位
// 	{ C_EPADR_AERY2L ,         0x00000000 },     // 7AH AERY2L    R   2 通道2有功电能累加值低位
// 	{ C_EPADR_RERY2L ,         0x00000000 },     // 7BH RERY2L    R   2 通道2无功电能累加值低位
};
#define	 EMU_EPADR_INIT_TAB_INDEX	( sizeof( EMU_EPADR_INIT_TAB ) / EMU_EPADR_Type_LEN )


// 校表参数初始化,跟校表参数一一对应
EMU_EPADR_Type code EMU_CALPARA_DEF_TAB[] = {
	{ C_EPADR_ICONT,			0x00000182 },
	{ C_EPADR_W1GAIN,			0x00000000 },
	{ C_EPADR_P1CAL,			0x00000000 },
	{ C_EPADR_WATT1OS,			0x00000000 },
	{ C_EPADR_SPTSP,			0x0000001b },
};
#define	 EMU_CALPARA_DEF_TAB_INDEX	( sizeof( EMU_CALPARA_DEF_TAB ) / EMU_EPADR_Type_LEN )

// 检查用
EMU_EPADR_Type code EMU_CFG0_3_DEF_TAB[] = {
	{ C_EPADR_EMUCFG0,			C_EPDAT_EMUCFG0 },
	{ C_EPADR_EMUCFG1,			C_EPDAT_EMUCFG1 },
	{ C_EPADR_EMUCFG2,			C_EPDAT_EMUCFG2 },
	{ C_EPADR_EMUCFG3,			C_EPDAT_EMUCFG3 }, 
};
#define	 EMU_CFG0_3_DEF_TAB_INDEX	( sizeof( EMU_CFG0_3_DEF_TAB ) / EMU_EPADR_Type_LEN )

// 校表用
EMU_COMM_CAL_TAB_Type code EMU_COMM_EMUC_TAB[]={
	{ 0x00,		C_EPADR_W1GAIN 		},
	{ 0x09,		C_EPADR_P1CAL		},
	{ 0x0D,		C_EPADR_WATT1OS		}, 
};
#define	EMU_COMM_EMUC_TAB_INDEX	(sizeof(EMU_COMM_EMUC_TAB) / EMU_COMM_CAL_TAB_Type_LEN)

uchar8  code C_ucUIPREG_TAB[] ={C_ECADR_VRms, C_ECADR_APWRA1, C_ECADR_I1Rms, C_ECADR_RPWRA1, C_ECADR_FREQ };	// 电压，功率，电流, 无功，频率寄存器
	#define C_ucUIPREG_TAB_Index	sizeof(C_ucUIPREG_TAB)

ushort16  code C_usUIP_KMS_DEF_VAL_TAB[]={0x1bd3, 0x0000, 0x0000 };	// 电压，功率，电流系数默认值
	#define C_usUIP_KMS_DEF_VAL_TAB_Index	(sizeof(C_usUIP_KMS_DEF_VAL_TAB) / 2)

/*----------------< 变量定义 >----------------------------------*/
EMU_CALPARA_Type	Str_EmuCalPara;		// 校表参数
EMU_UIPKms_Type		Str_UIPKmsPara;		// 瞬时量系数
/*----------------< 函数声明 >----------------------------------*/

static INT32U 	ApiEMU_Read_ECADR(INT8U xdata address);
static void 	ApiEMU_Write_ECADR(INT8U xdata address, INT32U xdata Data) ;
static void     ApiEMU_SetStartVal(void); 
static uchar8   ApiEMU_SetUIPKms(void);
static uchar8   ApiEMU_CheckCalParaCRC( void );
static uchar8   ApiEMU_CheckKmsParaCRC( void );

void 	ApiEMU_EMUInit( void );
void	ApiEMU_EMUParaCheck( void );
uchar8	ApiEMU_UpdateUIP(void);
ulong32 ApiEMU_ReadEmuReg( ushort16 v_usRegAddress );
void    ApiEMU_WriteEmuReg( ushort16 v_usRegAddress, ulong32 v_ulRegData );
void 	ApiEMU_CommStartCal( uchar8 v_ucChID );
void    ApiEMU_CommEndCal( uchar8 v_ucChID );
uchar8  ApiEMU_CommErrCal( uchar8 v_ucChID );
uchar8  ApiEMU_GetDirP(void);
void 	ApiEMU_DisOrEnable(uchar8 ucWorkMode);
/*----------------< 函数定义 >----------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    写电能相关寄存器（适用于间接寻址的寄存器）
 *
 *  @param    address : 寄存器地址
 *  @param    Data : 要写的数据，32位
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void ApiEMU_Write_ECADR(INT8U xdata address, INT32U xdata Data) 
{
    typedef union
    {
        INT32U u32_ChangeData;
        INT8U ChangeDataTb[4];
    }TypeUn_ChangeData;
	
    TypeUn_ChangeData xdata Un_ChangeData;
	
    Un_ChangeData.u32_ChangeData = Data;
//    GV_u16WatchDogTMR =1000;
    EADR = 0;
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
	LibPub_Delay10xus(6);
    EA = 0;
    EDTAH = Un_ChangeData.ChangeDataTb[1];
    EDTAM = Un_ChangeData.ChangeDataTb[2];
    EDTAL = Un_ChangeData.ChangeDataTb[3];
    NOP();NOP();NOP();
    NOP();NOP();NOP();
    NOP();NOP();NOP();
    NOP();NOP();NOP();
    NOP();NOP();NOP();
    NOP();NOP();NOP();
    NOP();NOP();NOP();
    NOP();NOP();NOP();
    EADR = (address|0x80);
	LibPub_Delay10xus(6);
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
    EA = 1;
//    NOP();NOP();NOP();
//    NOP();NOP();NOP();	
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    读电能相关寄存器（适用于间接寻址的寄存器）
 *
 *  @param    address : 寄存器地址
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
INT32U ApiEMU_Read_ECADR(INT8U xdata address) 
{
	INT32U xdata V_u32ReadData;
	
    typedef union
    {
        INT32U u32_ChangeData;
        INT8U ChangeDataTb[4];
    }TypeUn_ChangeData;
    TypeUn_ChangeData xdata Un_ChangeData;
	
//    GV_u16WatchDogTMR =1000;
    V_u32ReadData = 0;
    EA = 0;
    EADR = (address&0x7F);
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
	LibPub_Delay10xus(6);
    Un_ChangeData.u32_ChangeData = 0;
    Un_ChangeData.ChangeDataTb[1] = EDTAH;
    Un_ChangeData.ChangeDataTb[2] = EDTAM; 
    Un_ChangeData.ChangeDataTb[3] = EDTAL;
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
    EA = 1;
    V_u32ReadData = Un_ChangeData.u32_ChangeData;
	return (V_u32ReadData);
}


/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    使能/关闭计量模块
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
 
void ApiEMU_DisOrEnable(uchar8 v_ucWorkMode)
{
	if( EMU_ENABLE == v_ucWorkMode )	// 使能计量模块
	{
		EMUSR |=  EMUSR_DSPEN;
	}
	else	// 关闭计量模块
	{
		EMUSR = 0x00;
		EMUIE = 0x00;
		EMUIF = 0x00;
		IEN1 &= ~IEN1_EEMU;
	}
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    计量模块初始化
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void ApiEMU_EMUInit( void )
{
	uchar8 V_ucCnti=0;
	
	ApiEMU_DisOrEnable( EMU_DISENABLE );
	
	// @brief 先配置 EMUSR 为 60H: 计量模块禁止、系统时钟选择PLL、清除各种标志
	EMUSR = 0x60;
	EMUIE = 0x00;
	EMUIF = 0x00;
	IEN1 &= ~IEN1_EEMU;
	
	// @brief 开启计量前段电源，将 PWRCON2 设置为 0X80 
	PWRCON2 |= PWRCON2_LDO28ON;
	
	// @brief 开启VREF，将EMUCFG3 设置为0x0000E8
	ApiEMU_Write_ECADR( C_EPADR_EMUCFG3, C_EPDAT_EMUCFG3);
	
	// @brief 等待1MS
	LibPub_DelayNms(5);
	
	// @brief 设置 ADC,PGA 工作电流和 CHOP 频率，EMUCFG2 典型设置为 0x000C84
	ApiEMU_Write_ECADR( C_EPADR_EMUCFG2, C_EPDAT_EMUCFG2);	
	
	// @brief 配置计量其它参数，如 W1GAIN,P1CAL，W1ATTOS 等（恢复计量参数）	
	for( V_ucCnti = 0; V_ucCnti<EMU_EPADR_INIT_TAB_INDEX; V_ucCnti++ )	/* 固定参数配置，后续可以封装成函数，check时也可以用 */
	{
		ApiEMU_Write_ECADR( EMU_EPADR_INIT_TAB[V_ucCnti].ucEmuAddr, EMU_EPADR_INIT_TAB[V_ucCnti].ulEmuRegData);
	}
	
	/* 增加从E2恢复校表数据代码 */
	LibPub_ReadDataFromE2prom( LIB_E2P_EMU_CALPARA, 0, (uchar8*)&Str_EmuCalPara.ulaCalPara[0] );
	for( V_ucCnti = 0; V_ucCnti<EMU_CALPARA_DEF_TAB_INDEX; V_ucCnti++ )	
	{
		ApiEMU_Write_ECADR ( EMU_CALPARA_DEF_TAB[V_ucCnti].ucEmuAddr, Str_EmuCalPara.ulaCalPara[V_ucCnti] );
	}
	
	// @brief 開啟开启 ADC 動作必須保證距开启VREF 間隔 60mS，这里延时100ms
	LibPub_DelayNms(100);	
	
	// @brief 开启 ADC&PGA，EMUCFG0 设置为 0x000037 高精度模式、电压通道2倍增益、电流通道16倍增益、打开电压电流通道ADC
	ApiEMU_Write_ECADR( C_EPADR_EMUCFG0, C_EPDAT_EMUCFG0);	/* 通道2不开启 */
	

	// @brief 配置 EMUSR，典型配置为 0XE0；开启
	ApiEMU_DisOrEnable( EMU_ENABLE );
	
	// @brief 配置 EMUCFG1 低电平有效（b23)、允许有功脉冲输出（21）、打开高通滤波、脉宽90ms
	ApiEMU_Write_ECADR( C_EPADR_EMUCFG1, C_EPDAT_EMUCFG1);
	
	// @brief 延时500ms	
	LibPub_DelayNms(500);
	
	EMUIF = 0x00;
	EMUIE = EMUIE_PFIE; // 这里只允许PF中断，所以采用赋值，将其他中断关闭
	IEN1 |= IEN1_EEMU;
	
}
/*--------------------------------- 注释详解区 ---------------------------------------------------------*/
/**
 *  注释1:计量相关寄存器的配置应按照以下步骤配置（中颖FAQ文档要求）: 
 A.  將 EMUSR 設置為 0x60; 
 B.  开启计量模拟前端电源，将 PWRCON2 设置为 0X80 
 C.  开启 VREF，将 EMUCFG3 设置为 0x000000E8 
 D.  等待 1MS 
 E.  设置 ADC,PGA 工作电流和 CHOP 频率，EMUCFG2 典型设置为 0x000C84,低功耗典型
     设置为 0x00098C 
 F.  配置计量其它参数，如 W1GAIN,P1CAL，W1ATTOS 等
 G.  开启 ADC&PGA，EMUCFG0 设置为 0x000037，低功耗模式设置为 0X100037。如果應
     用需要只開倆路 ADC，本操作步驟也是必須的。開啟开启 ADC 動作必須保證距开启
     VREF 間隔 60mS。
 H.  设置开启对应的 ADC 通道，关闭不用的通道；（if necessary）
 I.  配置 EMUSR，典型配置为 0XE0；
 J.  配置 EMUCFG1 
 K.  等待 500ms  
 L.  配置 EMUIE,使能有功或者无功脉冲输出
 */
/**
 *  注释2:
 *
 */
/**
 * @}
 */
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    计量参数检查,只要有寄存器不对，就直接复位一下，重新配置
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void ApiEMU_EMUParaCheck( void )
{
	uchar8   V_ucResult = _FAILED;
	uchar8   V_ucCnti;
	ushort16 V_usRegAddress = 0;
	ulong32  V_ulRegData;
	
	do{

		/* 先检查一下配置寄存器  */
		for( V_ucCnti = 0; V_ucCnti<EMU_CFG0_3_DEF_TAB_INDEX; V_ucCnti++ )
		{
			V_usRegAddress = EMU_CFG0_3_DEF_TAB[V_ucCnti].ucEmuAddr;
			V_ulRegData = ApiEMU_ReadEmuReg( V_usRegAddress );
			if( EMU_CFG0_3_DEF_TAB[V_ucCnti].ulEmuRegData != V_ulRegData )
			{
				break;
			}
		}
		if( V_ucCnti < EMU_CFG0_3_DEF_TAB_INDEX ) break;
		
		/* 检查一下固定值 */
		for( V_ucCnti = 0; V_ucCnti<EMU_EPADR_INIT_TAB_INDEX; V_ucCnti++ )
		{
			V_usRegAddress = EMU_EPADR_INIT_TAB[V_ucCnti].ucEmuAddr;
			V_ulRegData = ApiEMU_ReadEmuReg( V_usRegAddress );
			if( EMU_EPADR_INIT_TAB[V_ucCnti].ulEmuRegData != V_ulRegData )
			{
				break;
			}
		}
		if( V_ucCnti < EMU_EPADR_INIT_TAB_INDEX ) break;
		
		/* 检查一下校表数据 */
		if ( _FAILED == ApiEMU_CheckCalParaCRC( ) )///* 错了就直接退出，初始化一下计量芯片，这里break是退出do while 循环 */// 
		{
			 break;		
		}
		
		for( V_ucCnti = 0; V_ucCnti<EMU_CALPARA_DEF_TAB_INDEX; V_ucCnti++ )
		{
			V_usRegAddress = EMU_CALPARA_DEF_TAB[V_ucCnti].ucEmuAddr;
			V_ulRegData = ApiEMU_ReadEmuReg( V_usRegAddress );
			
			if( Str_EmuCalPara.ulaCalPara[V_ucCnti] != V_ulRegData )
			{
				break;
			}
		}
		if( V_ucCnti < EMU_CALPARA_DEF_TAB_INDEX ) break;
		
		V_ucResult = _SUCCESS;  
		
	}while(0);
	
	/* 如果有错就直接初始化芯片 */
	if(( _FAILED == V_ucResult )&&(0==GStr_Flag.ucPowerOnFlag))
	{
		ApiEMU_EMUInit();
	}
	
	// 校表系数参数校验一下
	ApiEMU_CheckKmsParaCRC();
	
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    更新计量瞬时量
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
uchar8 ApiEMU_UpdateUIP(void)
{
	uchar8   V_ucCnt_i;
	ulong32  V_ulaRegData[C_ucUIPREG_TAB_Index];
//	ulong32  V_ulRegData=0;
	ulong32  V_ulTemp;
//	FP32	 V_fPowerP,V_fPowerQ,V_fPowerS;
	
	FP64	 V_fPowerQ,V_fPowerS;	
	
	ApiEMU_CheckKmsParaCRC();		// 校验一下系数参数
	
	//---------------------------------------------------------------------------
	// 先读一下原始值
	for( V_ucCnt_i=0; V_ucCnt_i<C_ucUIPREG_TAB_Index; V_ucCnt_i++ )
	{
		V_ulaRegData[V_ucCnt_i] = ApiEMU_ReadEmuReg( C_ucUIPREG_TAB[V_ucCnt_i] ) ;
	}
 	// 开始计算瞬时量
	// 1. 电压 
	//---------------------------------------------------------------------------
	if( Str_UIPKmsPara.ulaKmsuip[0] != 0 )
	{
		GStr_UIPGroup.ulVoltage[0] = 10.0 * V_ulaRegData[0] / Str_UIPKmsPara.ulaKmsuip[0];
	}
	else
	{
		GStr_UIPGroup.ulVoltage[0] = 0;
	}
	 V_ulTemp=GStr_UIPGroup.ulVoltage[0]*10;
	 LibPub_HEXtoBCDBytes(V_ulTemp,&GStr_UIPDisplay.ucVoltageA[0],4);///转换为BCD用于显示 两位小数
	 LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulVoltage[0],&GStr_UIPDisplay.ucCOMMVoltageA[0],4);///转换为BCD用于通信
	
	//	 LibPub_Buffer4ToUlong32( uchar8 *p_ucBytesBuffer )
	// 2. 功率
	//---------------------------------------------------------------------------
	if( Str_UIPKmsPara.ulaKmsuip[1] != 0 )
	{
		if( V_ulaRegData[1] & 0x00800000 )
		{
			V_ulaRegData[1] = ~(V_ulaRegData[1] | 0xFF000000) + 1;
		}
		GStr_UIPGroup.ulPower[0] =  1000.0 * V_ulaRegData[1] / Str_UIPKmsPara.ulaKmsuip[1] ;
	} 
	
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulPower[0],&GStr_UIPDisplay.ucPower[0],4);///转换为BCD用于通信和显示
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulPower[0],&GStr_UIPDisplay.ucPowerA[0],4);//单相表总功率等于A相功率
	
	LibPub_MemCopyBytes(&GStr_UIPDisplay.ucPower[0],&GStr_UIPDisplay.ucCOMMPower[0],4);///用于通信
	LibPub_MemCopyBytes(&GStr_UIPDisplay.ucPowerA[0],&GStr_UIPDisplay.ucCOMMPowerA[0],4);///用于通信
	
	// 3. 电流
	//---------------------------------------------------------------------------
	if( Str_UIPKmsPara.ulaKmsuip[2] != 0 )
	{
		GStr_UIPGroup.ulCurrent[0] = 1000.0 * V_ulaRegData[2] / Str_UIPKmsPara.ulaKmsuip[2] ;
	}
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulCurrent[0],&GStr_UIPDisplay.ucCurrentA[0],4);///转换为BCD用于通信和显示
	
	LibPub_MemCopyBytes(&GStr_UIPDisplay.ucCurrentA[0],&GStr_UIPDisplay.ucCOMMCurrentA[0],4);///用于通信

	
	// 4. 功率因数x.xxx 有功功率/视在功率；视在功率=sqrt( 有功功率平方+无功功率平方)
	//---------------------------------------------------------------------------
	if( V_ulaRegData[3] & 0x00800000 )
	{
		V_ulaRegData[3] = ~(V_ulaRegData[3] | 0xFF000000) + 1;
	}
	V_fPowerS = V_ulaRegData[1];
	V_fPowerS = V_fPowerS * V_fPowerS;
	
	V_fPowerQ = V_ulaRegData[3];
	V_fPowerQ = V_fPowerQ * V_fPowerQ;
	
	V_fPowerS = V_fPowerS + V_fPowerQ;	// S = sqrt(P*P+Q*Q)
	V_fPowerS = sqrt(V_fPowerS);
	 
	if( V_ulaRegData[1] != 0 )
	{
		GStr_UIPGroup.ulFactory[0] = ( V_ulaRegData[1]*1000 ) / V_fPowerS;
	}
	else
	{
		GStr_UIPGroup.ulFactory[0] = 1000;
	}
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulFactory[0],&GStr_UIPDisplay.ucFactory[0],4);///转换为BCD用于通信和显示
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulFactory[0],&GStr_UIPDisplay.ucFactoryA[0],4);//单相表总功率因数等于A相功率
	
	LibPub_MemCopyBytes(&GStr_UIPDisplay.ucFactory[0],&GStr_UIPDisplay.ucCOMMFactory[0],4);///用于通信
	LibPub_MemCopyBytes(&GStr_UIPDisplay.ucFactoryA[0],&GStr_UIPDisplay.ucCOMMFactoryA[0],4);///用于通信
	
	
	// 5. 频率 xx.xx
	//---------------------------------------------------------------------------
	if( V_ulaRegData[4] != 0 )
	{
		GStr_UIPGroup.ulFrequency = 245760000.0 / V_ulaRegData[4];
	}
	else
	{
		GStr_UIPGroup.ulFrequency = 5000;
	}
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulFrequency,&GStr_UIPDisplay.ucFrequency[0],4);
	
	//#if ( METER_TYPE == METER_TYPE_DDSYU666)
	//if(_TRUE==ApiEMU_GetDirP())
	//#else
	if(_FALSE==ApiEMU_GetDirP())
	//#endif
	{  
		GStr_Flag.ucRunState1 |=F_RUN_POWER_REVERSE;  //置功率反向标志
		GStr_UIPDisplay.ucCOMMFactory[2] |=0x80;///反向，电流功率功率因数最高位置1
		GStr_UIPDisplay.ucCOMMFactoryA[2] |=0x80;///反向，电流功率功率因数最高位置1
		GStr_UIPDisplay.ucCOMMPower[1] |=0x80;///反向，  功率最高位置1
		GStr_UIPDisplay.ucCOMMPowerA[1] |=0x80;///反向， A相功率最高位置1
		GStr_UIPDisplay.ucCOMMCurrent[1]|=0x80;///反向， 电流最高位置1
		GStr_UIPDisplay.ucCOMMCurrentA[1]|=0x80;///反向，A相电流最高位置1
	}
	else
	{
		GStr_Flag.ucRunState1 &=~F_RUN_POWER_REVERSE; //清功率反向标志
	}
		
	// 6. 判断是否潜起动
	//---------------------------------------------------------------------------
	if( (EMUSR & EMUSR_NoPLd ) && (EMUSR & EMUSR_NoQLd ) )	// 有功，无功同时潜动状态下，电流灭零
	{
		// 电流和功率在厂内不灭零，厂外灭零
		//----------------------------------------------------------------------
		if( (GStr_Flag.ucMeterMode & F_FACTORY_MODE)!= F_FACTORY_MODE )	
		{
			LibPub_MemSetBytes( &GStr_UIPDisplay.ucCurrentA[0], 0x00, 4 );
			LibPub_MemSetBytes( &GStr_UIPDisplay.ucPower[0], 0x00, 4 );
			LibPub_MemSetBytes( &GStr_UIPDisplay.ucPowerA[0], 0x00, 4 );
			
			LibPub_MemSetBytes( &GStr_UIPDisplay.ucCOMMCurrentA[0], 0x00, 4 );    //新增
			LibPub_MemSetBytes( &GStr_UIPDisplay.ucCOMMPower[0], 0x00, 4 );
			LibPub_MemSetBytes( &GStr_UIPDisplay.ucCOMMPowerA[0], 0x00, 4 );

			
		}
		// 只要是潜动，功率因数默认1，功率方向默认正向
		//----------------------------------------------------------------------
		LibPub_MemSetBytes( &GStr_UIPDisplay.ucFactory[0], 0x00, 4 );
		LibPub_MemSetBytes( &GStr_UIPDisplay.ucFactoryA[0], 0x00, 4 );
		
		LibPub_MemSetBytes( &GStr_UIPDisplay.ucCOMMFactory[0], 0x00, 4 );
		LibPub_MemSetBytes( &GStr_UIPDisplay.ucCOMMFactoryA[0], 0x00, 4 );		
		
		GStr_UIPDisplay.ucFactory[2]  = 0x10;
		GStr_UIPDisplay.ucFactoryA[2] = 0x10;
		
		GStr_Flag.ucRunState1 &=~F_RUN_POWER_REVERSE; //清功率反向标志
	}
	
	
	//---------------------------------------------------------------------------
	
	return(_SUCCESS);
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    读计量芯片寄存器地址
 *
 *  @param    v_usRegAddress : 寄存器地址
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
ulong32 ApiEMU_ReadEmuReg( ushort16 v_usRegAddress )
{
	uchar8 V_ucRegAddress;
	
	V_ucRegAddress = (uchar8)v_usRegAddress; 
	return(ApiEMU_Read_ECADR( V_ucRegAddress ) );
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    写计量芯片寄存器
 *
 *  @param    v_usRegAddress : 寄存器地址
 *  @param    v_ulRegData : 要写的数据
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void ApiEMU_WriteEmuReg( ushort16 v_usRegAddress, ulong32 v_ulRegData )
{
	uchar8 V_ucRegAddress;
	uchar8 V_ucCnt_i;
	
	V_ucRegAddress = (uchar8)v_usRegAddress;
	ApiEMU_Write_ECADR ( V_ucRegAddress, v_ulRegData );
	
	if (V_ucRegAddress == C_EPADR_W2GAIN)
	{
		ApiEMU_Write_ECADR ( C_EPADR_W2GAIN, v_ulRegData ); 
	}
	
	/* 如果写的是校表寄存器，要存一下E2 */
	for ( V_ucCnt_i=0; V_ucCnt_i<EMU_CALPARA_DEF_TAB_INDEX; V_ucCnt_i++ )
	{
		if( EMU_CALPARA_DEF_TAB[V_ucCnt_i].ucEmuAddr == V_ucRegAddress  )
		{ 
			Str_EmuCalPara.ulaCalPara[V_ucCnt_i] = v_ulRegData;
			LibPub_WriteDataToE2prom( LIB_E2P_EMU_CALPARA, 0, (uchar8*)&Str_EmuCalPara.ulaCalPara[0] );
			break;
		}
	}
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    起动校表
 *
 *  @param    v_usRegAddress : 寄存器地址
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void ApiEMU_CommStartCal( uchar8 v_ucChID )
{
	uchar8  V_ucCnt_i;
	ulong32 V_ulRegData;
	
	///* 数据 *///
	V_ulRegData  = (ulong32)Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+3] << 24;
	V_ulRegData |= (ulong32)Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+2] << 16;
	V_ulRegData |= (ulong32)Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+1] << 8;
	V_ulRegData |= (ulong32)Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+0];
	
	V_ucCnt_i = EMU_CALPARA_DEF_TAB_INDEX;
	/* 先初始化一下校表寄存器 */
	//---------------------------------------------------------------------------
	for ( V_ucCnt_i=0; V_ucCnt_i<EMU_CALPARA_DEF_TAB_INDEX; V_ucCnt_i++ )
	{
		ApiEMU_WriteEmuReg( EMU_CALPARA_DEF_TAB[V_ucCnt_i].ucEmuAddr, EMU_CALPARA_DEF_TAB[V_ucCnt_i].ulEmuRegData);  
	}
	
	/* 写一下UIP系数 */
	//---------------------------------------------------------------------------
	for ( V_ucCnt_i=0; V_ucCnt_i<C_usUIP_KMS_DEF_VAL_TAB_Index; V_ucCnt_i++ )
	{
		Str_UIPKmsPara.ulaKmsuip[V_ucCnt_i] = C_usUIP_KMS_DEF_VAL_TAB[V_ucCnt_i];
	}
	LibPub_WriteDataToE2prom( LIB_E2P_EMU_UIPKms, 0, (uchar8*)&Str_UIPKmsPara.ulaKmsuip[0] );
	
	
	/* 写一下校表常数 */
	//---------------------------------------------------------------------------
	ApiEMU_WriteEmuReg( C_EPADR_ICONT, V_ulRegData ); 
	
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    结束校表
 *
 *  @param    v_ucChID : 寄存器地址
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void ApiEMU_CommEndCal( uchar8 v_ucChID )
{
	uchar8 V_ucTemp;
	
	V_ucTemp = v_ucChID;
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    调校误差
 *
 *  @param    v_ucChID : 寄存器地址
 *
 *  @return   成功：_SUCCESS；失败：_FAILED
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
uchar8 ApiEMU_CommErrCal( uchar8 v_ucChID )
{
	uchar8   V_ucResult = _SUCCESS,V_ucCnt_i;
	uchar8   V_ucRegAddress;		// 寄存器地址
	ulong32  V_ulRegData;
	
	do{
		
		if( 0x00 != Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0] )	///* 仅支持DI0==00 *///
		{
			V_ucResult = _FAILED; 
			break;  // 跳出do-while循环
		} 
		
		///* 准备数据 *///
		//---------------------------------------------------------------------------
		V_ulRegData  = (ulong32)Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+3] << 24;
		V_ulRegData |= (ulong32)Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+2] << 16;
		V_ulRegData |= (ulong32)Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+1] << 8;
		V_ulRegData |= (ulong32)Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+0];
		
		//---------------------------------------------------------------------------
		///* DI1:0x00 1.0L 100%Ib 有功功率增益校正 对应寄存器 0c *///
		///* DI1:0x09 0.5L 100%Ib 相位校正  对应寄存器 18*///
		///* DI1:0x0D 1.0L 5%Ib 功率offset校正  对应寄存器 78*///
		switch( Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+1] )
		{
			case 0x00:
			case 0x09:
			case 0x0D:
			{
				for ( V_ucCnt_i=0; V_ucCnt_i<EMU_COMM_EMUC_TAB_INDEX; V_ucCnt_i++ )
				{
					if( EMU_COMM_EMUC_TAB[V_ucCnt_i].ucCommDI1 == Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+1] )
					{
						V_ucRegAddress = EMU_COMM_EMUC_TAB[V_ucCnt_i].ucEmuAddr; 
						ApiEMU_WriteEmuReg( V_ucRegAddress, V_ulRegData );  
						break;
					}
				}
			}break;
			
			case 0x11:	///* 功率有效值校正，校一下系数 *///
			{ 
				// 设置一下潜动阈值
				ApiEMU_SetStartVal(); 
				
				// 校一下系数
				ApiEMU_SetUIPKms();
				
			}break;
			
			default:break;
		} 
	}while(0);
	
	//---------------------------------------------------------------------------
	return( V_ucResult );
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    设置潜动阈值
 *
 *  @return   None
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
static void ApiEMU_SetStartVal(void)
{
	ulong32  V_ulRegData;
	
	V_ulRegData = ApiEMU_ReadEmuReg( C_ECADR_APWRA1 );	///* APWR1 为瞬时有功功率，用于有功电能的累加，有一定的波动。APWRA1 为平均有功功率，比较稳定 *///
	
	#if ( METER_TYPE == METER_TYPE_DDSYU666 )
	if( V_ulRegData & 0x00800000 )	//导轨表电流线反，测出来的功率要做相反处理
	{
		V_ulRegData = ~(V_ulRegData | 0xFF000000) + 1;
	}
	#endif
	V_ulRegData =  ( V_ulRegData*3 ) / 1000 ;			///* 按1级表启动功率75%设置潜动阈值 *///
	
	ApiEMU_WriteEmuReg( C_EPADR_SPTSP, V_ulRegData ); 
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    校瞬时量系数
 *
 *  @return   None
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
uchar8 C_ucCurrentTab[]={ 10,15,25,50,100,150,200};

static uchar8 ApiEMU_SetUIPKms(void)
{
	ulong32  V_ulRegData;
	do
	{	 
		//---------------------------------------------------------------------------
		// KmsU  电压有效值格式 XXX.X 
		V_ulRegData = ApiEMU_ReadEmuReg( C_ECADR_VRms );	///*   *///
		Str_UIPKmsPara.ulaKmsuip[0] =   V_ulRegData / 220.0; 
		
		//---------------------------------------------------------------------------
		// KmsP 功率有效值格式 XX.XXXX 
		V_ulRegData = ApiEMU_ReadEmuReg( C_ECADR_APWRA1 );	///* APWR1 为瞬时有功功率，用于有功电能的累加，有一定的波动。APWRA1 为平均有功功率，比较稳定 *///
		
		#if ( METER_TYPE == METER_TYPE_DDSYU666 )
		if( V_ulRegData & 0x00800000 )
		{
			V_ulRegData = ~(V_ulRegData | 0xFF000000) + 1;
		}
		#endif
		Str_UIPKmsPara.ulaKmsuip[1] =   V_ulRegData / ((C_ucCurrentTab[GStr_FunConfigPara.ucFunCurrentVal]*220.0)/1000.0);
		
		//---------------------------------------------------------------------------
		// KmsI1 电流有效值格式 XXX.XXX
		V_ulRegData = ApiEMU_ReadEmuReg( C_ECADR_I1Rms );	///*   */// 
		Str_UIPKmsPara.ulaKmsuip[2] =   V_ulRegData / ( C_ucCurrentTab[GStr_FunConfigPara.ucFunCurrentVal] / 10.0 ); 
		
		//---------------------------------------------------------------------------
		LibPub_WriteDataToE2prom( LIB_E2P_EMU_UIPKms, 0, (uchar8*)&Str_UIPKmsPara.ulaKmsuip[0] );
		
	}while(0);
	
	//---------------------------------------------------------------------------
	return _SUCCESS;
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
uchar8 ApiEMU_GetDirP(void)
{
	ulong32  V_ulRegData;
	  
	V_ulRegData = ApiEMU_ReadEmuReg( C_ECADR_APWRA1 );	///*   */// 
	
	if( V_ulRegData & 0x00800000 )
	{
		#if ( METER_TYPE == METER_TYPE_DDSY666 )
		return _FALSE;	// 反向
		#else
		return _TRUE;	//导轨表电流线反，读出反向功率实际为正向
		#endif
	}
	#if ( METER_TYPE == METER_TYPE_DDSY666 )
	return _TRUE;		// 反向
	#else
	return _FALSE;
	#endif
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    校验校表参数CRC是否正确
 *
 *  @return   _FALSE:数据正确  _TRUE：数据错误
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
static uchar8 ApiEMU_CheckCalParaCRC( void )
{
	if ( _TRUE != LibPub_CrcCheck( (uchar8*)&Str_EmuCalPara.ulaCalPara[0], EMU_CALPARA_Type_LEN-2, Str_EmuCalPara.usCRC16 ) )
	{
		LibPub_ReadDataFromE2prom( LIB_E2P_EMU_CALPARA, 0, (uchar8*)&Str_EmuCalPara.ulaCalPara[0] );
		return _FAILED;
	}
	
	return _SUCCESS;
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    校验校表参数CRC是否正确
 *
 *  @return   _FALSE:数据正确  _TRUE：数据错误
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
static uchar8 ApiEMU_CheckKmsParaCRC( void )
{
	if ( _TRUE != LibPub_CrcCheck( (uchar8*)&Str_UIPKmsPara.ulaKmsuip[0], EMU_UIPKms_Type_LEN-2, Str_UIPKmsPara.usCRC16 ) )
	{
		LibPub_ReadDataFromE2prom( LIB_E2P_EMU_UIPKms, 0, (uchar8*)&Str_UIPKmsPara.ulaKmsuip[0] );
		return _FAILED;
	}
	
	return _SUCCESS;
}

#endif 
