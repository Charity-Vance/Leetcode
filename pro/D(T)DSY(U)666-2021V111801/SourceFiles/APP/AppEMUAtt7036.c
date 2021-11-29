/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    AppEMUAtt7036.c                                                                          
**** Brief:       7036计量芯片文件                                                                    
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
 *  该文件所有函数的前缀为ApiEMU_
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
#if ( METER_TYPE == METER_TYPE_DTSY666)
/*----------------< 宏定义区 >----------------------------------*/

#define chk_reg_num  	28
#define const_reg_num 	11
#define C_ClearVoltage   50///电压低于5V灭零
/*----------------< 常量定义 >----------------------------------*/
uchar8 xdata GA_EmuRegData[TRIPEMU_CALPARA_Type_LEN];

const ulong32 code Dl_Cpu_Init[chk_reg_num]=
{
	0x37007FFF,///相位区域0
	0x60000000,///相位区域1   ///前面4个为配置数据
	0x36000030,///起动功率阀值设置
	0x1E000050,///HFCONST
	
	0x04000000,///A相有功功率增益
	0x05000000,///B
	0x06000000,///C
	0x07000000,///A相无功功率增益
	0x08000000,///B
	0x09000000,///C
	0x0A000000,///A相视在功率增益
	0x0B000000,///B
	0x0C000000,///C
	0x0D000000,///A相相位校正0
	0x0E000000,///B
	0x0F000000,///C
	0x10000000,///A相相位校正1
	0x11000000,///B
	0x12000000,///C
	0x17000000,///A相电压增益
	0x18000000,///B相电压增益
	0x19000000,///C相电压增益
	0x1A000000,///A相电流增益
	0x1B000000,///B相电流增益
	0x1C000000,///C相电流增益
	0x61000000,///A相相位校正2
	0x62000000,///B相相位校正2
	0x63000000,///C相相位校正2
};

const ulong32 code Const_Cpu_Init[const_reg_num]=
{
	0x0100B97E  ,///模式相关控制
	0x0300F884,	 ///EMU模块控制寄存器
	0x31003427,	 ///电路模块控制寄存器
	0x02000100, ///ADC增益选择
	0x1F000000,///失压阈值选择
	0x1D000160,///起动电流设置
	0x27000007,///A相电流有效值offset校正
	0x28000007,///B相电流有效值offset校正?
	0x29000007,///C相电流有效值offset校正
	0x70000000,///EMUCFG
	0x33003300,///脉冲常数倍数
	
};

///电能数据寄存器
const uchar8 Str_EnergyRegADDr[]=
{
	C_ActiveEnergy_TReg,
	C_ActiveEnergy_AReg,
	C_ActiveEnergy_BReg,
	C_ActiveEnergy_CReg,
	C_ReativeEnergy_TReg,
	C_ReativeEnergy_AReg,
	C_ReativeEnergy_BReg,
	C_ReativeEnergy_CReg,
	C_ApparentEnergy_TReg,
	C_ApparentEnergy_AReg,
	C_ApparentEnergy_BReg,
	C_ApparentEnergy_CReg
};
///瞬时量数据寄存器
const uchar8 Str_RmsRegADDr[]=
{
	C_rPa,		//A相有功功率0
	C_rPb,		//B相有功功率1
	C_rPc,		//C相有功功率2
	C_rPt,		//合相有功功率3
	C_UaRms	,   //A相电压有效值4
	C_UbRms	,   //B相电压有效值5
    C_UcRms	,   //C相电压有效值6
	C_UtRms	,	//合相电压有效值表用7
	C_IaRms	,	//A相电流有效值8
	C_IbRms	,	//B相电流有效值9
	C_IcRms	,	//C相电流有效值10
	C_ItRms	,	//合相电流有效值11
	C_Pfa	,	//A相功率因数12
	C_Pfb	,	//B相功率因数13
	C_Pfc	,	//C相功率因数14
	C_Pft	,	//合相功率因数15
	C_Freq	,	//线频率16
};	

#define C_ucUIPREG_TAB_Index  sizeof(Str_RmsRegADDr)
	        
///校表用
EMU_COMM_TRIPCAL_TAB_Type code EMU_COMM_TRIPEMUC_TAB[]={   ////可读写
	{ 0x00,		{C_PGainA    	,   C_PGainB 		,C_PGainC		}	,	},  ///有功功率增益校正
	{ 0x01,		{C_QGainA   	,   C_QGainB 		,C_QGainC		}	,	},  ///无功功率增益校正
	{ 0x02,		{C_SGainA    	,   C_SGainB 		,C_SGainC		}	,	},  ///视在功率增益校正
	{ 0x04,		{C_UGainA    	,   C_UGainB 		,C_UGainC		}	,	},  ///电压增益校正
	{ 0x06,		{C_IGainA    	,   C_IGainB 		,C_IGainC		}	,	},  ///电流增益校正
	{ 0x08,		{C_PhSregApq0   ,   C_PhSregBpq0 	,C_PhSregCpq0	}	,	},  ///大电流相位校正
	{ 0x09,		{C_PhSregApq1   ,   C_PhSregBpq1 	,C_PhSregCpq1	}	,	},  ///中电流相位校正
	{ 0x0A,		{C_PhSregApq2   ,   C_PhSregBpq2 	,C_PhSregCpq2	}	,	},  ///小电流相位校正	
};

EMU_Read_TRIPCAL_TAB_Type code EMU_READ_TRIPEMUC_TAB[]={   ////只读
	{ 0x03,		{	C_rPa    	,   C_rPb 		,C_rPc		,C_rPt  	},	},  ///功率
	{ 0x05,		{	C_UaRms   	,   C_UbRms 	,C_UcRms	,C_UtRms	},	},  ///电压
	{ 0x07,		{	C_IaRms    	,   C_IbRms 	,C_IcRms	,C_ItRms	},	},  ///电流
	
};

/*----------------< 变量定义 >----------------------------------*/

TRIPEMU_CALPARA_Type	Str_TRIPEmuCalPara;		// 校表参数

TRIPEMU_UIPKms_Type		Str_TRIPUIPKmsPara;		// 瞬时量系数
/*----------------< 函数声明 >----------------------------------*/
static uchar8 AppEMU_TripCheckCalParaCRC( void );
static void AppEMU_ClearCalReg_MeterIC(void);

void  ApiEMU_EMUInit();
uchar8 AppEMU_TripReadEmuReg( uchar8 v_ucChID );
void ApiEMU_CommEndCal( uchar8 v_ucChID );
uchar8 ApiEMU_CommErrCal( uchar8 v_ucChID );
void ApiEMU_CommStartCal(v_ucChID);
void AppEMU_TRipCommSetReg( uchar8 v_ucChID );
void AppEMU_WriteOneReg_MeterIC(uchar8 *P_Data,uchar8 V_RegAddr);
void AppEMU_WriteRegToEE(uchar8 *P_Data,uchar8 V_RegAddr);
void  ApiEMU_EMUParaCheck();
void ApiEMU_DisOrEnable(uchar8 v_ucWorkMode);
	
void Hal_EraseFlashSector(INT16U adr, INT8U dat, INT8U sta);
INT8U Hal_ReadEEPROM(INT8U  *Dst, INT16U Src, INT16U Len);
INT8U Hal_WriteEEPROM(INT16U Dst, INT8U  *Src, INT16U Len);
/*----------------< 函数定义 >----------------------------------*/

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
		SPIDrv_Eable_MeterIC();
	}
	else	// 关闭计量模块
	{
		SPIDrv_Disable_MeterIC();
	}
}

///*****************************************************************************************///
///*函数原型：void SPIDrv_WriteEnable_MeterIC(void)
///*功能描述：计量芯片写使能
///*输入参数：无
///*输出参数：无
///*返回参数：无
///*功能说明：计量芯片写使能主要是对计量芯片C9特殊寄存器进行操作，写入0x000000为写失能，写入0x00005A为写使能
///*调用机制：
///*备    注：
///*****************************************************************************************///
void AppEMU_WriteEnable_MeterIC(void)
{
	uchar8 V_Data[4],i;
	ulong32 V_EnWriteData;
	V_EnWriteData=0xC900005A;	//写使能直接写入0xC900005A高字节为特殊寄存器地址,低三字节为写入数据
	SPIDrv_Eable_MeterIC();
	LibPub_Ulong32ToBuffer4(&V_Data[0],V_EnWriteData);///该转换为大端，要先写C9级data0
	for(i=4;i>0;i--)
	{
		SPIDrv_SendBtye(V_Data[4-i]);
	}
	SPIDrv_Disable_MeterIC();
}
///*****************************************************************************************///
///*函数原型：void SPIDrv_WriteDisable_MeterIC(void)
///*功能描述：计量芯片写失能
///*输入参数：无
///*输出参数：无
///*返回参数：无
///*功能说明：计量芯片写使能主要是对计量芯片C9特殊寄存器进行操作，写入0x000000为写失能，写入0x00005A为写使能
///*调用机制：
///*备    注：
///*****************************************************************************************///
void AppEMU_WriteDisable_MeterIC(void)
{
	uchar8 V_Data[4],i;
	ulong32 V_DisWriteData;
	V_DisWriteData=0xC9000000;	//写失能直接写入0xc9000000高字节为特殊寄存器地址,低三字节为写入数据
	SPIDrv_Eable_MeterIC();
	LibPub_Ulong32ToBuffer4(&V_Data[0],V_DisWriteData);///该转换为大端，需先写data0
	for(i=0;i<4;i++)
	{
		SPIDrv_SendBtye(V_Data[i]);
	}
	SPIDrv_Disable_MeterIC();
}

///*****************************************************************************************///
///*函数原型：void SPIDrv_ReadDataModeSet(uchar8 V_Data)
///*功能描述：选择计量芯片寄存器读取控制:读取计量参数寄存器和读取校表参数寄存器
///*输入参数：00=读取计量数据寄存器；01=读取校表参数寄存器
///*输出参数：无
///*返回参数：无
///*功能说明：读取计量芯片寄存器设置函数，通过配置特殊寄存器C6为0x000000读取计量参数寄存器、为0x00005A读取校表参数寄存器
///*调用机制：
///*备    注：
///*****************************************************************************************///
void AppEMU_ReadDataModeSet(uchar8 V_ModeData)
{
	uchar8 V_Data[4],i;
	ulong32 V_EnWriteData;
	if(V_ModeData==C_MeterPara)
	{
		V_EnWriteData=0xC6000000;	//计量芯片设置为读取(计量)参数高字节为寄存器地址，低三字节为写入数据
	}
	else
	{
		V_EnWriteData=0xC600005A;	//计量芯片设置为读取(校表)参数高字节为寄存器地址，低三字节为写入数据
	}
	SPIDrv_Eable_MeterIC();		//CS使能计量芯片
	LibPub_Ulong32ToBuffer4(&V_Data[0],V_EnWriteData);
	for(i=4;i>0;i--)
	{
		SPIDrv_SendBtye(V_Data[4-i]);
	}
	SPIDrv_Disable_MeterIC();	//CS失能计量芯片
}
///*****************************************************************************************///
///*函数原型：void SPI_ReadOneReg_MeterIC(uchar8 V_usRegAddr, uchar8* P_Data)
///*功能描述：从计量芯片计量参数寄存器中读取三字节数据
///*输入参数：
///*		uchar8 V_usRegAddr：预读取计量芯片寄存器地址
///*		uchar8* P_Data：数据转存指针
///*		uchar8 V_MeaORCal  00:读取计量参数寄存器   01:读取校表参数寄存器
///*输出参数： uchar8* P_Data数据指针中存储V_usRegAddr地址下的三字节数据(7038芯片读取的计量参数为三字节有效，校表参数为两字节有效)
///*返回参数：读取成功C_OK
///*功能说明：
///*调用机制：
///*备    注：
///*****************************************************************************************///
void AppEMU_ReadOneReg_MeterIC(uchar8 V_usRegAddr, uchar8* P_Data,uchar8 V_MeaORCal)
{
	AppEMU_ReadDataModeSet(V_MeaORCal);	
	SPIDrv_Eable_MeterIC();
	SPIDrv_SendBtye(V_usRegAddr&0x7F);
	LibPub_Delay2us();
	*P_Data=SPIDrv_ReceiveByte();
	*(P_Data+1)=SPIDrv_ReceiveByte();
	*(P_Data+2)=SPIDrv_ReceiveByte();
	SPIDrv_Disable_MeterIC();
}

///*****************************************************************************************///
///*函数原型：uchar8 SPIDrv_WriteOneReg_MeterIC(uchar8 *P_Data,uchar8 V_RegAddr)
///*功能描述：将三字节数据写入计量芯片寄存器指定地址(仅适用于写校表参数寄存器)
///*输入参数：
///*		uchar8 *P_Data：预写入数据指针
///*		uchar8 V_RegAddr：计量芯片寄存器地址
///*输出参数：无37
///*返回参数：
///*		C_OK：写入成功
///*功能说明：通过写一字节数据，写入将地址，地址数据首位要置1，然后调用3次写一字节数据，按从高字节到低字节将3字节数据写入计量芯片
///*调用机制：
///*备    注：
///*****************************************************************************************///
void AppEMU_WriteOneReg_MeterIC(uchar8 *P_Data,uchar8 V_RegAddr)
{
	uchar8 V_Data[3],i;
	V_Data[0]=*P_Data;
	V_Data[1]=*(P_Data+1);
	V_Data[2]=*(P_Data+2);
	AppEMU_WriteEnable_MeterIC();
	SPIDrv_Eable_MeterIC();
	SPIDrv_SendBtye(V_RegAddr|0x80);	//地址数据首位置1，写入数据
	for(i=3;i>0;i--)
	{
		SPIDrv_SendBtye(V_Data[3-i]);
	}
	SPIDrv_Disable_MeterIC();
	AppEMU_WriteDisable_MeterIC();
}
///*****************************************************************************************///
///*函数原型：uchar8 AppEMU_WriteRegToEE(uchar8 *P_Data,uchar8 V_RegAddr)
///*功能描述：将三字节数据写入类EE(仅适用于写校表参数寄存器)
///*输入参数：
///*		uchar8 *P_Data：预写入数据指针
///*		uchar8 V_RegAddr：计量芯片寄存器地址
///*输出参数：无37
///*返回参数：
///*		C_OK：写入成功
///*功能说明：通过写一字节数据，写入将地址，地址数据首位要置1，然后调用3次写一字节数据，按从高字节到低字节将3字节数据写入计量芯片
///*调用机制：
///*备    注：
///*****************************************************************************************///
void AppEMU_WriteRegToEE(uchar8 *P_Data,uchar8 V_RegAddr)
{
	uchar8 V_Data[3],i,V_WriteData[4];
	V_Data[0]=*P_Data;
	V_Data[1]=*(P_Data+1);
	V_Data[2]=*(P_Data+2);
	GStr_Flag.ucWrE2promSafeByte|=C_SafeByte_Step1;
	for ( i=0; i<chk_reg_num; i++ )
	{
		LibPub_Ulong32ToBuffer4(V_WriteData, Dl_Cpu_Init[i]);
		if( V_WriteData[0] == V_RegAddr  )
		{ 
			GStr_Flag.ucWrE2promSafeByte|=C_SafeByte_Step2;
			V_WriteData[0] = V_RegAddr;
			LibPub_MemCopyBytes(V_Data, &V_WriteData[1] ,3);
			Hal_ReadEEPROM(GA_EmuRegData,CAddr_EMU_CALPARA_Note,TRIPEMU_CALPARA_Type_LEN);
			LibPub_MemCopyBytes(V_WriteData,&GA_EmuRegData[4*i],4);
			
			LibPub_MemCopyBytes(&GA_EmuRegData[0],(uchar8*)&Str_TRIPEmuCalPara.ulaCalPara[0],TRIPEMU_CALPARA_Type_LEN-2);
			Str_TRIPEmuCalPara.usCRC16=LibPub_CRC16_CCITT((uchar8*) &Str_TRIPEmuCalPara.ulaCalPara[0], TRIPEMU_CALPARA_Type_LEN-2);
			////更新RAM
			GStr_Flag.ucWrE2promSafeByte|=C_SafeByte_Step3;
			Hal_EraseFlashSector(CAddr_EMU_CALPARA_Note, 0x00, FLASH_RW_ENABLE);///擦除类EE中校表数据
			Hal_EraseFlashSector(CAddr_EMU_CALPARA_BAK_Note, 0x00, FLASH_RW_ENABLE);

			Hal_WriteEEPROM(CAddr_EMU_CALPARA_Note, (uchar8*)&Str_TRIPEmuCalPara.ulaCalPara[0], TRIPEMU_CALPARA_Type_LEN);
			Hal_WriteEEPROM(CAddr_EMU_CALPARA_BAK_Note, (uchar8*)&Str_TRIPEmuCalPara.ulaCalPara[0], TRIPEMU_CALPARA_Type_LEN);///数据写入类EE
			GStr_Flag.ucWrE2promSafeByte=C_SafeByte_Step0;
			break;
		}
	}
}
///***********************************************************************************///
///*函数原型：void SPIDrv_ClearCalReg_MeterIC(void)
///*功能描述：清除校表寄存器
///*输入参数：无
///*输出参数：无
///*返回参数：无
///*功能说明：
///*调用机制：
///*备    注：
///***********************************************************************************///
static void AppEMU_ClearCalReg_MeterIC(void)
{
	uchar8 V_Addr,V_WriteData[4];
	uchar8 i;
	LibPub_MemSetBytes(V_WriteData,0,4);	
	V_Addr=0xC3;
	AppEMU_WriteOneReg_MeterIC(V_WriteData,V_Addr);//0xC3地址写入000000,初始化计量芯片校表寄存器初值
	LibPub_DelayNms(25);
	LibPub_DelayNms(25);
	SPIDrv_ENSPIMode();
	SPIDrv_Eable_MeterIC();
	
	for(i=0;i<const_reg_num;i++)
	{
		LibPub_Ulong32ToBuffer4(V_WriteData, Const_Cpu_Init[i]);
		V_Addr=V_WriteData[0];
		AppEMU_WriteOneReg_MeterIC(&V_WriteData[1],V_Addr);	
	}
}

///*****************************************************************************************///
///*函数原型：void SPIDrv_ClearEnergyData_MeterIC(void)
///*功能描述：清计量芯片电能寄存器
///*输入参数：无
///*输出参数：无
///*返回参数：无
///*功能说明：通过读取计量芯片的电能寄存器，来起到清零电能寄存器的目的，计量芯片配置为读后清
///*调用机制：
///*备    注：
///*****************************************************************************************///
void AppEMU_ClearEnergyData_MeterIC(void)
{
	uchar8 i,V_Data[3];
	for(i=0;i<sizeof(Str_EnergyRegADDr);i++)
	{
		AppEMU_ReadOneReg_MeterIC(Str_EnergyRegADDr[i], V_Data,0x00);
	}
}
///*****************************************************************************************///
///*函数原型：void SPIDrv_SoftwareRESET_MeterIC(void)
///*功能描述：通过复位RESET管脚，复位计量芯片，并重新清计量芯片电能数据寄存器
///*输入参数：无
///*输出参数：无
///*返回参数：无
///*功能说明
///*调用机制：
///*备    注：
///*****************************************************************************************///
void AppEMU_SoftwareRESET_MeterIC(void)
{
	uchar8 V_Addr,V_WriteData[4];
	LibPub_MemSetBytes(V_WriteData,0,4);	
	V_Addr=0xD3;
	AppEMU_WriteOneReg_MeterIC(V_WriteData,V_Addr);//0xD3地址写入000000
	LibPub_DelayNms(1);
	SPIDrv_ENSPIMode();		
	AppEMU_ClearCalReg_MeterIC();
}

///*****************************************************************************************///
///*函数原型：void  AppEMU_EMUPara_Check(void)
///*功能描述：校表参数效验
///*输入参数：
///*输出参数：无
///*返回参数：无
///*功能说明：
///*调用机制：
///*备    注：
///*****************************************************************************************///
void  ApiEMU_EMUParaCheck()
{
	uchar8   V_ucResult = _FAILED;
	uchar8   V_ucCnti,V_Addr,V_ReadData[4],V_WriteData[4];
	
	do{

		/* 先检查固定值  */
		for( V_ucCnti = 0; V_ucCnti<const_reg_num; V_ucCnti++ )
		{
			LibPub_Ulong32ToBuffer4(V_WriteData, Const_Cpu_Init[V_ucCnti]);
			V_Addr=V_WriteData[0];
			AppEMU_ReadOneReg_MeterIC(V_Addr, &V_ReadData[1],C_EMUPara);
			
			if( C_Equal!=LibPub_CompareData(&V_ReadData[1], &V_WriteData[1], 3,CMP_MODE_HIGHT) )
			{
				break;
			}
		}
		if( V_ucCnti < const_reg_num ) break;
		
		/* 检查一下校表数据 */
		if ( _FAILED == AppEMU_TripCheckCalParaCRC() )///* 错了就直接退出，初始化一下计量芯片，这里break是退出do while 循环 */// 
		{
			 break;		
		}
		
		for( V_ucCnti = 0; V_ucCnti<chk_reg_num; V_ucCnti++ )
		{
			LibPub_Ulong32ToBuffer4(V_WriteData, Str_TRIPEmuCalPara.ulaCalPara[V_ucCnti]);
			V_Addr=V_WriteData[0];
			AppEMU_ReadOneReg_MeterIC(V_Addr, &V_ReadData[1],C_EMUPara);
				
			if( C_Equal!=LibPub_CompareData(&V_ReadData[1], &V_WriteData[1], 3,CMP_MODE_HIGHT) )
			{
				break;
			}
		}
		if( V_ucCnti < chk_reg_num ) break;
		
		V_ucResult = _SUCCESS;  
		
	}while(0);
	
	/* 如果有错就直接初始化芯片 */
	if(( _FAILED == V_ucResult )&&(0==GStr_Flag.ucPowerOnFlag))
	{
		ApiEMU_EMUInit();
	}
	
//	// 校表系数参数校验一下
//	ApiEMU_CheckKmsParaCRC();
}
///*****************************************************************************************///
///*函数原型：void  SPIDrv_Initial_MeterIC (void)
///*功能描述：初始化计量芯片，配置计量芯片考寄存器
///*输入参数：
///*输出参数：无
///*返回参数：无
///*功能说明：
///*调用机制：
///*备    注：
///*****************************************************************************************///
void  ApiEMU_EMUInit()
{
	uchar8 V_CalRegData[3],i,V_Addr,V_WriteData[4];
	ushort16 V_Data;
	
	EMUSR &= ~EMUSR_DSPEN;
	IEN1 &= ~IEN1_EEMU;///关闭SOC计量单元
	
	AppEMU_SoftwareRESET_MeterIC();

	 Hal_ReadEEPROM((uchar8*)&Str_TRIPEmuCalPara.ulaCalPara[0],CAddr_EMU_CALPARA_Note,TRIPEMU_CALPARA_Type_LEN);
	 if(_TRUE!=LibPub_CrcCheck((uchar8*)&Str_TRIPEmuCalPara.ulaCalPara[0],TRIPEMU_CALPARA_Type_LEN-2,Str_TRIPEmuCalPara.usCRC16))
	 {
		 Hal_ReadEEPROM((uchar8*)&Str_TRIPEmuCalPara.ulaCalPara[0],CAddr_EMU_CALPARA_BAK_Note,TRIPEMU_CALPARA_Type_LEN);///读备份
		 {
			 if(_TRUE!=LibPub_CrcCheck((uchar8*)&Str_TRIPEmuCalPara.ulaCalPara[0],TRIPEMU_CALPARA_Type_LEN-2,Str_TRIPEmuCalPara.usCRC16))
			 {	
				for(i=0;i<chk_reg_num;i++)
				{
					Str_TRIPEmuCalPara.ulaCalPara[i]=Dl_Cpu_Init[i];///类EE中数据错取默认值
				}	
			 }	 
		 }
	 }

	AppEMU_ClearCalReg_MeterIC();		//清计量芯片校表参数寄存器,顺便写了一下固定值
	
	LibPub_MemSetBytes(V_CalRegData,0,3);
	V_Data=C_EMUCfg&0x0FFF;	//配置寄存器
	LibPub_Ushort16ToBuffer2(&V_CalRegData[1],V_Data);
	AppEMU_WriteOneReg_MeterIC(V_CalRegData,C_EMUCfg_Reg);
	
	for(i=0;i<chk_reg_num;i++)
	{
		LibPub_Ulong32ToBuffer4(V_WriteData, Str_TRIPEmuCalPara.ulaCalPara[i]);
		V_Addr=V_WriteData[0];
		AppEMU_WriteOneReg_MeterIC(&V_WriteData[1],V_Addr);
	}
	
	LibPub_MemSetBytes(V_CalRegData,0,3);
	V_Data=C_EMUCfg;	//配置寄存器
	LibPub_Ushort16ToBuffer2(&V_CalRegData[1],V_Data);
	AppEMU_WriteOneReg_MeterIC(V_CalRegData,C_EMUCfg_Reg);
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
static uchar8 AppEMU_TripCheckCalParaCRC( void )
{
	if ( _TRUE != LibPub_CrcCheck( (uchar8*)&Str_TRIPEmuCalPara.ulaCalPara[0], TRIPEMU_CALPARA_Type_LEN-2, Str_TRIPEmuCalPara.usCRC16 ) )
	{
		 Hal_ReadEEPROM((uchar8*)&Str_TRIPEmuCalPara.ulaCalPara[0],CAddr_EMU_CALPARA_Note,TRIPEMU_CALPARA_Type_LEN);
		 if(_TRUE!=LibPub_CrcCheck((uchar8*)&Str_TRIPEmuCalPara.ulaCalPara[0],TRIPEMU_CALPARA_Type_LEN-2,Str_TRIPEmuCalPara.usCRC16))
		 {
			 Hal_ReadEEPROM((uchar8*)&Str_TRIPEmuCalPara.ulaCalPara[0],CAddr_EMU_CALPARA_BAK_Note,TRIPEMU_CALPARA_Type_LEN);///读备份
			 {
				 if(_TRUE!=LibPub_CrcCheck((uchar8*)&Str_TRIPEmuCalPara.ulaCalPara[0],TRIPEMU_CALPARA_Type_LEN-2,Str_TRIPEmuCalPara.usCRC16))
				 {	
					return _FAILED;
				 }	 
			 }
		 }

	}

	return _SUCCESS;
}

///*------------------------------------------------------------------------------------------------------*/
///**
// *  @brief    校验系数CRC是否正确
// *
// *  @return   _FALSE:数据正确  _TRUE：数据错误
// *
// *  @note     xx
// *
// */
///*------------------------------------------------------------------------------------------------------*/
//static uchar8 AppEMU_TripCheckKmsParaCRC( void )
//{
//	if ( _TRUE != LibPub_CrcCheck( (uchar8*)&Str_TRIPUIPKmsPara.ulaKmsuip, TRIPEMU_UIPKms_Type_LEN-2, Str_TRIPUIPKmsPara.usCRC16 ))
//	{
//		LibPub_ReadDataFromE2prom( LIB_E2P_EMU_UIPKms, 0, (uchar8*)&Str_TRIPUIPKmsPara.ulaKmsuip);
//		return _FAILED;
//	}
//	
//	return _SUCCESS;
//}
///*------------------------------------------------------------------------------------------------------*/
///**
// *  @brief    起动校表
// *
// *  @return   
// *
// *  @note     xx
// *///主要是初始化校表寄存器
// */
///*------------------------------------------------------------------------------------------------------*/
void ApiEMU_CommStartCal(v_ucChID)
{
	uchar8 V_Addr,V_WriteData[4],i;

	GStr_Flag.ucWrE2promSafeByte|=C_SafeByte_Step1;
	
	LibPub_MemSetBytes( GA_EmuRegData, 0, TRIPEMU_CALPARA_Type_LEN );
	
	AppEMU_ClearCalReg_MeterIC();///请校表寄存器
	
	GStr_Flag.ucWrE2promSafeByte|=C_SafeByte_Step2;
	for( i=0;i<chk_reg_num;i++ )///校表寄存器写默认值
	{
		LibPub_Ulong32ToBuffer4(V_WriteData, Dl_Cpu_Init[i]);
		V_Addr=V_WriteData[0];
		AppEMU_WriteOneReg_MeterIC(&V_WriteData[1],V_Addr);
	}
		GStr_Flag.ucWrE2promSafeByte|=C_SafeByte_Step3;
	Hal_EraseFlashSector(CAddr_EMU_CALPARA_Note, 0x00, FLASH_RW_ENABLE);///擦除类EE中校表数据
	Hal_EraseFlashSector(CAddr_EMU_CALPARA_BAK_Note, 0x00, FLASH_RW_ENABLE);
	
	Hal_WriteEEPROM(CAddr_EMU_CALPARA_Note, (uchar8*)&Dl_Cpu_Init[0], TRIPEMU_CALPARA_Type_LEN);
	Hal_WriteEEPROM(CAddr_EMU_CALPARA_BAK_Note, (uchar8*)&Dl_Cpu_Init[0], TRIPEMU_CALPARA_Type_LEN);///数据写入类EE
	GStr_Flag.ucWrE2promSafeByte =C_SafeByte_Step0;
//	LibPub_MemCopyBytes((uchar8*) &Dl_Cpu_Init[0], (uchar8*) &Str_TRIPEmuCalPara.ulaCalPara[0], chk_reg_num*4);
//	Str_TRIPEmuCalPara.usCRC16=LibPub_CRC16_CCITT((uchar8*) &Str_TRIPEmuCalPara.ulaCalPara[0], chk_reg_num*4);
}
///*------------------------------------------------------------------------------------------------------*/
///**
// *  @brief   参数设置
// *
// *  @return   
// *
// *  @note     xx
// *///主要设置配置寄存器并写入HFCONST
// */
///*------------------------------------------------------------------------------------------------------*/
void AppEMU_TRipCommSetReg( uchar8 v_ucChID )
{
	uchar8 V_WriteData[4];
	
//	Hal_EraseFlashSector(CAddr_EMU_CALPARA_Note, 0x00, FLASH_RW_ENABLE);///擦除类EE中校表数据
//	Hal_EraseFlashSector(CAddr_EMU_CALPARA_BAK_Note, 0x00, FLASH_RW_ENABLE);	
	V_WriteData[0]=0x37;  ///相位区域0
	V_WriteData[1]=0;
	V_WriteData[2]=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+41];
	V_WriteData[3]=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+40];
	AppEMU_WriteRegToEE(&V_WriteData[1],V_WriteData[0]);///校表参数存EE
	AppEMU_WriteOneReg_MeterIC(&V_WriteData[1],V_WriteData[0]);
//	LibPub_MemCopyBytes(V_WriteData, GA_EmuRegData, 4);
	
	V_WriteData[0]=0x60;  ///相位区域1
	V_WriteData[1]=0;
	V_WriteData[2]=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+45];
	V_WriteData[3]=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+44];
	AppEMU_WriteRegToEE(&V_WriteData[1],V_WriteData[0]);	
	AppEMU_WriteOneReg_MeterIC(&V_WriteData[1],V_WriteData[0]);
//	LibPub_MemCopyBytes(V_WriteData, &GA_EmuRegData[4], 4);
	
	V_WriteData[0]=0x36;  ///起动功率设置
	V_WriteData[1]=0;
	V_WriteData[2]=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+21];
	V_WriteData[3]=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+20];
	AppEMU_WriteRegToEE(&V_WriteData[1],V_WriteData[0]);
	AppEMU_WriteOneReg_MeterIC(&V_WriteData[1],V_WriteData[0]);	
//	LibPub_MemCopyBytes(V_WriteData, &GA_EmuRegData[8], 4);
	
	V_WriteData[0]=0x1E;  ///HFCONST
	V_WriteData[1]=0;
	V_WriteData[2]=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+5];
	V_WriteData[3]=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+4];
	AppEMU_WriteRegToEE(&V_WriteData[1],V_WriteData[0]);
	AppEMU_WriteOneReg_MeterIC(&V_WriteData[1],V_WriteData[0]);

//	LibPub_MemCopyBytes(V_WriteData, &GA_EmuRegData[12], 4);
	
//	Hal_WriteEEPROM(CAddr_EMU_CALPARA_Note, GA_EmuRegData, TRIPEMU_CALPARA_Type_LEN);
//	Hal_WriteEEPROM(CAddr_EMU_CALPARA_BAK_Note, GA_EmuRegData, TRIPEMU_CALPARA_Type_LEN);///数据写入类EE
	
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
	uchar8   V_ucResult = _SUCCESS,i,j;
	uchar8   V_ucRegAddress;		// 寄存器地址
	uchar8 	 V_WriteData[3][4];
	
	do{
		
		if(( 0x02 <Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0] )	
			&&(0xFF !=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0]))///* 仅支持DI0==00\01\02\FF *///
		{
			V_ucResult = _FAILED; 
			break;  // 跳出do-while循环
		} 
		
		///* 准备数据 *///
		//---------------------------------------------------------------------------
		LibPub_MemExchangeBytes(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W], &V_WriteData[0][0], 4);
		if(0xFF ==Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0])
		{
			LibPub_MemExchangeBytes(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+4],&V_WriteData[1][0], 4);
			LibPub_MemExchangeBytes(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+8],&V_WriteData[2][0], 4);
		}
		//---------------------------------------------------------------------------
		///* DI1:0x00 1.0L 100%Ib 有功功率增益校正 对应寄存器 0c *///
		///* DI1:0x09 0.5L 100%Ib 相位校正  对应寄存器 18*///
		///* DI1:0x0D 1.0L 5%Ib 功率offset校正  对应寄存器 78*///
		for( i=0;i<(sizeof(EMU_COMM_TRIPEMUC_TAB)/sizeof(EMU_COMM_TRIPCAL_TAB_Type));i++)
		{
			if(EMU_COMM_TRIPEMUC_TAB[i].ucCommDI1==(Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+1]))
			{
				if(0xFF !=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0])
				{
					V_ucRegAddress=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0];
					V_ucRegAddress=EMU_COMM_TRIPEMUC_TAB[i].ucEmuAddr[V_ucRegAddress];
					AppEMU_WriteRegToEE(&V_WriteData[0][1],V_ucRegAddress);	
					AppEMU_WriteOneReg_MeterIC(&V_WriteData[0][1],V_ucRegAddress);
					V_WriteData[0][0]=V_ucRegAddress;
				}
				else
				{
					for(j=0;j<3;j++)
					{
						V_ucRegAddress=EMU_COMM_TRIPEMUC_TAB[i].ucEmuAddr[j];
						AppEMU_WriteRegToEE(&V_WriteData[j][1],V_ucRegAddress);						
						AppEMU_WriteOneReg_MeterIC(&V_WriteData[j][1],V_ucRegAddress);
						V_WriteData[i][0]=V_ucRegAddress;
					}
				}
				break;
			}
		
		}
			
//			case 0x11:	///* 功率有效值校正，校一下系数 *///
//			{ 
//				// 设置一下潜动阈值
//				ApiEMU_SetStartVal(); 
//				
//				// 校一下系数
//				ApiEMU_SetUIPKms();
//				
//			}break;
			
//			default:break;
//		} 
	}while(0);
	
	//---------------------------------------------------------------------------
	return( V_ucResult );
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
	
	AppEMU_ClearEnergyData_MeterIC();
	
	V_ucTemp = v_ucChID;
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    读寄存器
 *
 *  @param    v_ucChID : 寄存器地址
 *
 *  @return   成功：_SUCCESS；失败：_FAILED
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
uchar8 AppEMU_TripReadEmuReg( uchar8 v_ucChID )
{
	uchar8   V_ucResult = _SUCCESS,i,j;
	uchar8   V_ucRegAddress;		// 寄存器地址
	uchar8   V_ReadData[4];
	
	if( 0x01 ==Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+2] )	///0x8001XXXX
	{
		for( i=0;i<(sizeof(EMU_COMM_TRIPEMUC_TAB)/sizeof(EMU_COMM_TRIPCAL_TAB_Type));i++)
		{
			if(EMU_COMM_TRIPEMUC_TAB[i].ucCommDI1==(Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+1]))///说明是校表参数
			{
				if(0xFF !=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0])
				{
					V_ucRegAddress=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0];
					V_ucRegAddress=EMU_COMM_TRIPEMUC_TAB[i].ucEmuAddr[V_ucRegAddress];
					AppEMU_ReadOneReg_MeterIC(V_ucRegAddress, &V_ReadData[1],C_EMUPara);
					V_ReadData[0]=0;
					LibPub_MemExchangeBytes(V_ReadData,&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+4], 4);
				}
				else
				{
					for(j=0;j<3;j++)
					{
						V_ucRegAddress=EMU_COMM_TRIPEMUC_TAB[i].ucEmuAddr[j];
						AppEMU_ReadOneReg_MeterIC(V_ucRegAddress, &V_ReadData[1],C_EMUPara);
						V_ReadData[0]=0;
						LibPub_MemExchangeBytes(V_ReadData,&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+4*(j+1)], 4);
					}
				}
				return( V_ucResult );
			}
		}
		for( i=0;i<(sizeof(EMU_READ_TRIPEMUC_TAB)/sizeof(EMU_COMM_TRIPCAL_TAB_Type));i++)///说明计量参数参数
		{
			if(EMU_READ_TRIPEMUC_TAB[i].ucCommDI1==(Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+1]))///说明是有效值数据
			{
				if(0xFF !=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0])
				{
					V_ucRegAddress=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0];
					V_ucRegAddress=EMU_READ_TRIPEMUC_TAB[i].ucEmuAddr[V_ucRegAddress];
					AppEMU_ReadOneReg_MeterIC(V_ucRegAddress, &V_ReadData[1],C_MeterPara);
					V_ReadData[0]=0;
					LibPub_MemExchangeBytes(V_ReadData,&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+4], 4);
				}
				else
				{
					for(j=0;j<4;j++)////计量参数带合相，所以需要读4个寄存器
					{
						V_ucRegAddress=EMU_READ_TRIPEMUC_TAB[i].ucEmuAddr[j];
						AppEMU_ReadOneReg_MeterIC(V_ucRegAddress, &V_ReadData[1],C_MeterPara);
						V_ReadData[0]=0;
						LibPub_MemExchangeBytes(V_ReadData,&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+4*(j+1)], 4);
					}
				}
				return( V_ucResult );
			}
		}
		V_ucResult = _FAILED;
		return( V_ucResult );  ///不是表格里的数据，回错
	}
	
	if( 0x03 ==Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+2] )	///0x8003XXXX //读指定地址计量参数
	{
		if(0x00!=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+1] )
		{
			V_ucResult = _FAILED; 
			return( V_ucResult );
		}
		V_ucRegAddress=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0];
		AppEMU_ReadOneReg_MeterIC(V_ucRegAddress, &V_ReadData[1],C_MeterPara);
		V_ReadData[0]=0;
		LibPub_MemExchangeBytes(V_ReadData,&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+4], 4);
		return( V_ucResult );
	}
	if( 0x04 ==Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+2] )	///0x8003XXXX //读指定地址校表参数
	{
		if(0x00!=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+1] )
		{
			V_ucResult = _FAILED; 
			return( V_ucResult );
		}
		V_ucRegAddress=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0];
		AppEMU_ReadOneReg_MeterIC(V_ucRegAddress, &V_ReadData[1],C_EMUPara);
		V_ReadData[0]=0;
		LibPub_MemExchangeBytes(V_ReadData,&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+4], 4);
		return( V_ucResult );
	}
	
	V_ucResult = _FAILED; 
	return( V_ucResult );///都不是回错
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    更新瞬时量
 *
 *  @param    v_ucChID : 寄存器地址
 *
 *  @return   成功：_SUCCESS；失败：_FAILED
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
ushort16 C_ucCurrentTab[]={ 10,15,25,50,100,150,200,300 };

uchar8 ApiEMU_UpdateUIP(void)
{
	uchar8 i;
	uchar8   V_ucaRegData[C_ucUIPREG_TAB_Index][4];
	ulong32  V_ulaRegData[C_ucUIPREG_TAB_Index];
	ulong32  V_ulTemp[4],V_ulKms1,V_ulKms2;
	uchar8   V_ucaReverseData[3];
	uchar8   V_ucaReverseFlag_A,V_ucaReverseFlag_B,V_ucaReverseFlag_C;
	V_ucaReverseFlag_A=0;
	V_ucaReverseFlag_B=0;
	V_ucaReverseFlag_C=0;
	
	
	Str_TRIPUIPKmsPara.ulaKmsuip=3000/C_ucCurrentTab[GStr_FunConfigPara.ucFunCurrentVal];////电流系数固定为30/Ib,此处为300/Ib
//	AppEMU_TripCheckKmsParaCRC();///校验一下电流系数
	
	for( i=0;i<C_ucUIPREG_TAB_Index;i++ )
	{
		AppEMU_ReadOneReg_MeterIC(Str_RmsRegADDr[i], &V_ucaRegData[i][1],C_MeterPara);
		V_ucaRegData[i][0]=0;///高位为0
		V_ulaRegData[i]=LibPub_Buffer4ToUlong32( &V_ucaRegData[i][0] );
	}
	
	///开始计算瞬时量
	///电压  实际值为寄存器值Vrms/2^13
	GStr_UIPGroup.ulVoltage[0] = 10.0*V_ulaRegData[4] /8192;        ///A相电压
	GStr_UIPGroup.ulVoltage[1] = 10.0*V_ulaRegData[5] /8192;        ///B相电压
	GStr_UIPGroup.ulVoltage[2] = 10.0*V_ulaRegData[6] /8192;        ///C相电压
	GStr_UIPGroup.ulVoltage[3] = 10.0*V_ulaRegData[7] /4096;        ///合相电压
	
	for(i=0;i<4;i++)
	{
		////电压灭零  当电压小于5V时，灭零
		if( GStr_UIPGroup.ulVoltage[i] < C_ClearVoltage )
		{
			GStr_UIPGroup.ulVoltage[i]=0;
		}
		V_ulTemp[i]=GStr_UIPGroup.ulVoltage[i]*10;	
	}
	///A相
	LibPub_HEXtoBCDBytes(V_ulTemp[0],&GStr_UIPDisplay.ucVoltageA[0],4);///转换为BCD用于显示 两位小数
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulVoltage[0],&GStr_UIPDisplay.ucCOMMVoltageA[0],4);///转换为BCD用于通信
	///B相
	LibPub_HEXtoBCDBytes(V_ulTemp[1],&GStr_UIPDisplay.ucVoltageB[0],4);///转换为BCD用于显示 两位小数
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulVoltage[1],&GStr_UIPDisplay.ucCOMMVoltageB[0],4);///转换为BCD用于通信
	///C相
	LibPub_HEXtoBCDBytes(V_ulTemp[2],&GStr_UIPDisplay.ucVoltageC[0],4);///转换为BCD用于显示 两位小数
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulVoltage[2],&GStr_UIPDisplay.ucCOMMVoltageC[0],4);///转换为BCD用于通信
	///合相
	LibPub_HEXtoBCDBytes(V_ulTemp[3],&GStr_UIPDisplay.ucVoltage[0],4);///转换为BCD用于显示 两位小数
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulVoltage[3],&GStr_UIPDisplay.ucCOMMVoltage[0],4);///转换为BCD用于通信
	
	///电流   实际值为寄存器值(Vrms/2^13)/N
	GStr_UIPGroup.ulCurrent[0] = 1000.0*V_ulaRegData[8] /8192*10/Str_TRIPUIPKmsPara.ulaKmsuip;        ///A相电流
	GStr_UIPGroup.ulCurrent[1] = 1000.0*V_ulaRegData[9] /8192*10/Str_TRIPUIPKmsPara.ulaKmsuip;        ///B相电流
	GStr_UIPGroup.ulCurrent[2] = 1000.0*V_ulaRegData[10] /8192*10/Str_TRIPUIPKmsPara.ulaKmsuip;        ///C相电流
	GStr_UIPGroup.ulCurrent[3] = 1000.0*V_ulaRegData[11] /4096*10/Str_TRIPUIPKmsPara.ulaKmsuip;        ///合相电流
	
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulCurrent[0],&GStr_UIPDisplay.ucCurrentA[0],4);///转换为BCD用于显示
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulCurrent[1],&GStr_UIPDisplay.ucCurrentB[0],4);///转换为BCD用于显示
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulCurrent[2],&GStr_UIPDisplay.ucCurrentC[0],4);///转换为BCD用于显示
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulCurrent[3],&GStr_UIPDisplay.ucCurrent[0],4);///转换为BCD用于显示
	
	LibPub_MemCopyBytes(&GStr_UIPDisplay.ucCurrentA[0],&GStr_UIPDisplay.ucCOMMCurrentA[0],4);///用于通信
	LibPub_MemCopyBytes(&GStr_UIPDisplay.ucCurrentB[0],&GStr_UIPDisplay.ucCOMMCurrentB[0],4);///用于通信
	LibPub_MemCopyBytes(&GStr_UIPDisplay.ucCurrentC[0],&GStr_UIPDisplay.ucCOMMCurrentC[0],4);///用于通信
	LibPub_MemCopyBytes(&GStr_UIPDisplay.ucCurrent[0],&GStr_UIPDisplay.ucCOMMCurrent[0],4);///用于通信
	
	///功率
	///寄存器值为X，若X>2^23  XX=X-2^24,否则XX=X   分相实际值为XXX=XX*K    合相实际值为XXX=XX*2*K
	///K=2.592*10^10/(HFCONST*EC*2^23)   单位为W
	V_ulKms1=(Str_TRIPEmuCalPara.ulaCalPara[3]&0x00FFFFFF)*GStr_FunConfigPara.ucFunMeterConst*83886.08;
	///							   HFCONST					* 脉冲常数的百分之一*2^23	
	V_ulKms2=2592000;
	for(i=0;i<4;i++)
	{
		if(V_ulaRegData[i]>8388608)
		{
			V_ulTemp[i]=16777216-V_ulaRegData[i];   ////功率
		}
		else
		{
			V_ulTemp[i]=V_ulaRegData[i];
		}
		if(i!=3)
		{
			GStr_UIPGroup.ulPower[i]=10.0*V_ulTemp[i]*V_ulKms2/V_ulKms1;///分相功率///单位为W切换为kW，四位小数
		}
		else
		{
			GStr_UIPGroup.ulPower[i]=10.0*V_ulTemp[i]*V_ulKms2/V_ulKms1*2;///合相功率
		}	
	}
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulPower[0],&GStr_UIPDisplay.ucPowerA[0],4);///转换为BCD用于显示
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulPower[1],&GStr_UIPDisplay.ucPowerB[0],4);///转换为BCD用于显示
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulPower[2],&GStr_UIPDisplay.ucPowerC[0],4);///转换为BCD用于显示
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulPower[3],&GStr_UIPDisplay.ucPower[0],4);///转换为BCD用于显示
	
	LibPub_MemCopyBytes(&GStr_UIPDisplay.ucPowerA[0],&GStr_UIPDisplay.ucCOMMPowerA[0],4);///用于通信
	LibPub_MemCopyBytes(&GStr_UIPDisplay.ucPowerB[0],&GStr_UIPDisplay.ucCOMMPowerB[0],4);///用于通信
	LibPub_MemCopyBytes(&GStr_UIPDisplay.ucPowerC[0],&GStr_UIPDisplay.ucCOMMPowerC[0],4);///用于通信
	LibPub_MemCopyBytes(&GStr_UIPDisplay.ucPower[0],&GStr_UIPDisplay.ucCOMMPower[0],4);///用于通信
	
	///功率因数
	///寄存器值为X，若X>2^23  XX=X-2^24,否则XX=X   实际功率因数pf=XX/2^23
	for(i=0;i<4;i++)
	{
		if(V_ulaRegData[12+i]>8388608)
		{
			V_ulTemp[i]=16777216-V_ulaRegData[12+i];   ////功率因数
		}
		else
		{
			V_ulTemp[i]=V_ulaRegData[12+i];
		}
		GStr_UIPGroup.ulFactory[i]=100.0*V_ulTemp[i]/8388608*10;
	}
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulFactory[0],&GStr_UIPDisplay.ucFactoryA[0],4);///转换为BCD用于通信和显示
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulFactory[1],&GStr_UIPDisplay.ucFactoryB[0],4);///转换为BCD用于通信和显示
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulFactory[2],&GStr_UIPDisplay.ucFactoryC[0],4);///转换为BCD用于通信和显示
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulFactory[3],&GStr_UIPDisplay.ucFactory[0],4);///转换为BCD用于通信和显示
	
	LibPub_MemCopyBytes(&GStr_UIPDisplay.ucFactoryA[0],&GStr_UIPDisplay.ucCOMMFactoryA[0],4);///用于通信
	LibPub_MemCopyBytes(&GStr_UIPDisplay.ucFactoryB[0],&GStr_UIPDisplay.ucCOMMFactoryB[0],4);///用于通信
	LibPub_MemCopyBytes(&GStr_UIPDisplay.ucFactoryC[0],&GStr_UIPDisplay.ucCOMMFactoryC[0],4);///用于通信
	LibPub_MemCopyBytes(&GStr_UIPDisplay.ucFactory[0],&GStr_UIPDisplay.ucCOMMFactory[0],4);///用于通信
	
	///频率
	///寄存器值为X   freq=X/2^13
	V_ulTemp[0]=V_ulaRegData[16];
	GStr_UIPGroup.ulFrequency=100.0*V_ulTemp[0]/8192;
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulFrequency,&GStr_UIPDisplay.ucFrequency[0],4);///转换为BCD用于通信和显示
	
	AppEMU_ReadOneReg_MeterIC(C_Psign, &V_ucaReverseData[0],C_MeterPara);//读功率方向寄存器
	if(V_ucaReverseData[2]&0x01)
	{
		V_ucaReverseFlag_A=1;
		GStr_UIPDisplay.ucCOMMFactoryA[2] |=0x80;///A相反向，电压电流功率功率因数最高位置1
		GStr_UIPDisplay.ucCOMMPowerA[1] |=0x80;///A相反向，电压电流功率功率因数最高位置1
		GStr_UIPDisplay.ucCOMMCurrentA[1]|=0x80;///A相反向，电压电流功率功率因数最高位置1
	}
	if(V_ucaReverseData[2]&0x02)
	{
		V_ucaReverseFlag_B=1;
		GStr_UIPDisplay.ucCOMMFactoryB[2] |=0x80;///B相反向，电压电流功率功率因数最高位置1
		GStr_UIPDisplay.ucCOMMPowerB[1] |=0x80;///B相反向，电压电流功率功率因数最高位置1
		GStr_UIPDisplay.ucCOMMCurrentB[1]|=0x80;///B相反向，电压电流功率功率因数最高位置1
	}
	if(V_ucaReverseData[2]&0x04)
	{
		V_ucaReverseFlag_C=1;
		GStr_UIPDisplay.ucCOMMFactoryC[2] |=0x80;///C相反向，电压电流功率功率因数最高位置1
		GStr_UIPDisplay.ucCOMMPowerC[1] |=0x80;///C相反向，电压电流功率功率因数最高位置1
		GStr_UIPDisplay.ucCOMMCurrentC[1]|=0x80;///C相反向，电压电流功率功率因数最高位置1
	}
	if(V_ucaReverseData[2]&0x08)
	{
		GStr_UIPDisplay.ucCOMMFactory[2] |=0x80;///合相反向，电压电流功率功率因数最高位置1
		GStr_UIPDisplay.ucCOMMPower[1] |=0x80;///合相反向，电压电流功率功率因数最高位置1
		GStr_UIPDisplay.ucCOMMCurrent[1]|=0x80;///合相反向，电压电流功率功率因数最高位置1
	}
	
	// 6. 判断是否潜起动
	//---------------------------------------------------------------------------
	AppEMU_ReadOneReg_MeterIC(C_EmuState, &V_ucaReverseData[0],C_MeterPara);//读标志寄存器
	// 电流和功率在厂内不灭零，厂外灭零
	if(V_ucaReverseData[1]&0x02)///A相潜动  
	{
		if( (GStr_Flag.ucMeterMode & F_FACTORY_MODE)!= F_FACTORY_MODE )	
		{
			if(GStr_UIPGroup.ulCurrent[0]<=(2*(100*C_ucCurrentTab[GStr_FunConfigPara.ucFunCurrentVal])/1000))
			{
				LibPub_MemSetBytes( &GStr_UIPDisplay.ucCurrentA[0], 0x00, 4 );
				LibPub_MemSetBytes( &GStr_UIPDisplay.ucCOMMCurrentA[0],0x00,4);
			}
			LibPub_MemSetBytes( &GStr_UIPDisplay.ucPowerA[0], 0x00, 4 );
			LibPub_MemSetBytes( &GStr_UIPDisplay.ucCOMMPowerA[0],0x00,4);
		}
		LibPub_MemSetBytes( &GStr_UIPDisplay.ucFactoryA[0], 0x00, 4 );
		LibPub_MemSetBytes( &GStr_UIPDisplay.ucCOMMFactoryA[0], 0x00, 4 );
		GStr_UIPDisplay.ucFactoryA[2] = 0x10;
		GStr_UIPDisplay.ucCOMMFactoryA[2] = 0x10;
		V_ucaReverseFlag_A=0;///清A相反向标志
	}
	if(V_ucaReverseData[1]&0x04)///B相潜动  
	{
		if( (GStr_Flag.ucMeterMode & F_FACTORY_MODE)!= F_FACTORY_MODE )	
		{
			if(GStr_UIPGroup.ulCurrent[1]<=(2*(100*C_ucCurrentTab[GStr_FunConfigPara.ucFunCurrentVal])/1000))
			{
				LibPub_MemSetBytes( &GStr_UIPDisplay.ucCurrentB[0], 0x00, 4 );
				LibPub_MemSetBytes( &GStr_UIPDisplay.ucCOMMCurrentB[0],0x00,4);
			}
			LibPub_MemSetBytes( &GStr_UIPDisplay.ucPowerB[0], 0x00, 4 );
			LibPub_MemSetBytes( &GStr_UIPDisplay.ucCOMMPowerB[0],0x00,4);
		}
		LibPub_MemSetBytes( &GStr_UIPDisplay.ucFactoryB[0], 0x00, 4 );
		LibPub_MemSetBytes( &GStr_UIPDisplay.ucCOMMFactoryB[0], 0x00, 4 );
		GStr_UIPDisplay.ucFactoryB[2] = 0x10;
		GStr_UIPDisplay.ucCOMMFactoryB[2] = 0x10;
		V_ucaReverseFlag_B=0;///清B相反向标志
	}
	if(V_ucaReverseData[1]&0x08)///C相潜动  
	{
		if( (GStr_Flag.ucMeterMode & F_FACTORY_MODE)!= F_FACTORY_MODE )	
		{
			if(GStr_UIPGroup.ulCurrent[2]<=(2*(100*C_ucCurrentTab[GStr_FunConfigPara.ucFunCurrentVal])/1000))
			{
				LibPub_MemSetBytes( &GStr_UIPDisplay.ucCurrentC[0], 0x00, 4 );
				LibPub_MemSetBytes( &GStr_UIPDisplay.ucCOMMCurrentC[0],0x00,4);
			}
			LibPub_MemSetBytes( &GStr_UIPDisplay.ucPowerC[0], 0x00, 4 );
			LibPub_MemSetBytes( &GStr_UIPDisplay.ucCOMMPowerC[0],0x00,4);
		}
		LibPub_MemSetBytes( &GStr_UIPDisplay.ucFactoryC[0], 0x00, 4 );
		LibPub_MemSetBytes( &GStr_UIPDisplay.ucCOMMFactoryC[0], 0x00, 4 );
		GStr_UIPDisplay.ucFactoryC[2] = 0x10;
		GStr_UIPDisplay.ucCOMMFactoryC[2] = 0x10;
		V_ucaReverseFlag_C=0;///清C相反向标志
	}
	if((V_ucaReverseData[1]&0x02)&&(V_ucaReverseData[1]&0x04)&&(V_ucaReverseData[1]&0x08))///A\B\C相都潜动  
	{
		if( (GStr_Flag.ucMeterMode & F_FACTORY_MODE)!= F_FACTORY_MODE )	
		{
			if(GStr_UIPGroup.ulCurrent[3]<=(6*(100*C_ucCurrentTab[GStr_FunConfigPara.ucFunCurrentVal])/1000))
			{
				LibPub_MemSetBytes( &GStr_UIPDisplay.ucCurrent[0], 0x00, 4 );
				LibPub_MemSetBytes( &GStr_UIPDisplay.ucCOMMCurrent[0],0x00,4);
			}
			LibPub_MemSetBytes( &GStr_UIPDisplay.ucPower[0], 0x00, 4 );
			LibPub_MemSetBytes( &GStr_UIPDisplay.ucCOMMPower[0],0x00,4);
		}
		LibPub_MemSetBytes( &GStr_UIPDisplay.ucFactory[0], 0x00, 4 );
		LibPub_MemSetBytes( &GStr_UIPDisplay.ucCOMMFactory[0], 0x00, 4 );
		GStr_UIPDisplay.ucFactory[2] = 0x10;
		GStr_UIPDisplay.ucCOMMFactory[2] = 0x10;
	}
		
	if((V_ucaReverseFlag_A)||(V_ucaReverseFlag_B)||(V_ucaReverseFlag_C))
	{
		GStr_Flag.ucRunState1 |=F_RUN_POWER_REVERSE;  //置功率反向标志
	}
	else
	{
		GStr_Flag.ucRunState1 &=~F_RUN_POWER_REVERSE; //清功率反向标志
	}
//---------------------------------------------------------------------------
	
	return(_SUCCESS);
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    获取功率方向
 *
 *  @return   _FALSE：反向  _TRUE：正向
 *
 *  @note     xx///该函数只用于判断正反向脉冲，用合相的方向为准
 *
 */
/*------------------------------------------------------------------------------------------------------*/
uchar8  ApiEMU_GetDirP(void)
{
	uchar8 V_ucaRegData[3];
	
	AppEMU_ReadOneReg_MeterIC(C_Psign, &V_ucaRegData[0],C_MeterPara);//读功率方向寄存器
	
	if(V_ucaRegData[2]&0x08)/// 合相反向
	{
		return _FALSE;
	}
	return _TRUE;
}

#endif
