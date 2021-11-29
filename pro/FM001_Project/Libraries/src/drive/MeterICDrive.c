/********************************************************************************************
Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     MeterICDrive.c
Version:       V1
Author:        
Date:          2014-3-12
Description:   计量芯片驱动文件，所有与计量芯片进行交互的都在此文件中，包括读取实时量及电能量
---------------------------------------------------------------------------------------------
History1:      第1次修改
内容1. Date:
       Author:
       Modification:
---------------------------------------------------------------------------------------------
内容2. Date:
       Author:
       Modification:
---------------------------------------------------------------------------------------------
History2:      第2次修改
内容1. Date:
       Author:
       Modification:
---------------------------------------------------------------------------------------------
内容2. Date:
       Author:
       Modification:
---------------------------------------------------------------------------------------------
History3:      第3次修改
内容1. Date:2021.09.27
       Author:zlj
       Modification:
---------------------------------------------------------------------------------------------
内容2. Date:
       Author:
       Modification:
********************************************************************************************/

#include "Public.h"
#include "MeterICDrive.h"
#include "MeterIC.h"

/*******************************************************************************
功能描述：	偶次谐波计算
*******************************************************************************/
//特殊命令定义
#define	C_BuffStr		0xC0		/*采样数据缓冲启动命令*/
#define	C_BuffSet		0xC1		/*缓冲数据读指针设置*/
#define	C_ClrCali		0xC3		/*清校表数据*/
#define	C_SyncSet		0xC4		/*同步数据系数设置*/
#define	C_SyncStr		0xC5		/*同步数据启动命令*/
#define	C_EnRdCali		0xC6		/*校表数据读使能*/
#define	C_EnWrCali		0xC9		/*校表数据写使能*/
#define	C_SoftRst		0xD3		/*软复位*/

#define CL_HD2Rate		6			/*偶次谐波含有量长度*/

/****************************************类型名称定义*************************************************/
Str_RealtimePower_Type		GStr_PowerData;				/*需量用功率数据存储结构体*/
Str_EnergyData_Type			GStr_EnergyData;			/*电能原始值数据存储结构体*/
Str_HEX_VARREGTYPE_Type		GStr_HEX_VARREGTYPE;		/*HEX格式预写数据层瞬时量存储结构体*/
Str_PowerCoeff_Type			GStr_PowerCoeff;			/*功率系数结构体*/
ulong32						GV_ulSlipCurrentBuff[3][3];	/*ABC滑差电流3级缓存*/
Str_PowerAdd_Type			GStr_PowerAdd;				/*1min功率累加和*/

/*****************************全局变量定义*********************************************/
long32 GV_lHD2Rate[CL_HD2Rate];
uchar8 GV_ucStepNum;
uchar8 GV_ucEvenHarmonicDelayTimer;
uchar8 GV_ucEvenHarmonicSecondTimer;
ushort16 GV_usEvenHarmonicCompensationTime;

/*******************************************************************************
函数原型: void SF_Delay(ulong32 V_ulData)
功能描述: 延时函数，根据已经宏定义好的Delay1uS等时间函数来给出特定时间延时
输入参数: DELAY1US、DELAY2US、DELAY4US、DELAY25MS、DELAY1MS特定时间已经调试
输出参数: 无
返回参数: 无
调用位置: 
备    注: 此延时为硬延时，延时准确性取决于MCU内部时钟频率，如果内部频率发生变化，则会导致延时不准确。
*******************************************************************************/
void SF_Delay(ulong32 V_ulData)
{
	ulong32 V_uli;

	for (V_uli = 0; V_uli < V_ulData; V_uli++)
	{
		NOP();
	}
}

/*******************************************************************************
函数原型: void SF_ClearUcharArray(uchar8 *pV_ucArray, uchar8 V_ucLength)
功能描述: 数组清零
输入参数: uchar8 *pV_ucArray、uchar8 V_ucLength数组字节数
输出参数: 无
返回参数: 无
调用位置: 
备    注: 本数组清零只适用于uchar8类型的数组，如果想清除ushort16类型的数组请调用void SF_ClearUshortArray(ushort16 *pV_usArray, uchar8 V_ucLength)
*******************************************************************************/
void SF_ClearUcharArray(uchar8 *pV_ucArray, uchar8 V_ucLength)
{
	memset(pV_ucArray, 0, V_ucLength);
}

/*******************************************************************************
函数原型: void SF_ClearUshortArray(ushort16 *pV_usArray, uchar8 V_ucLength)
功能描述: 数组清零
输入参数: ushort16 *pV_usArray数组首地址,uchar8 V_ucLength数组字数
输出参数: 无
返回参数: 无
调用位置: 
备    注: 本数组只适用于ushort16类型的数据
*******************************************************************************/
void SF_ClearUshortArray(ushort16 *pV_usArray, uchar8 V_ucLength)
{
	uchar8 V_uci;

	for (V_uci = 0; V_uci < V_ucLength; V_uci++)
	{
		*(pV_usArray + V_uci) = 0;
	}
}

/*******************************************************************************
函数原型: void SF_ClearUlongArray(ulong32 *pV_ulArray, uchar8 V_ucLength)
功能描述: 数组清零
输入参数: ulong32 *pV_ulArray数组首地址,uchar8 V_ucLength数组字数
输出参数: 无
返回参数: 无
调用位置: 
备    注: 本数组只适用于ushort16类型的数据
*******************************************************************************/
void SF_ClearUlongArray(ulong32 *pV_ulArray, uchar8 V_ucLength)
{
	uchar8 V_uci;

	for (V_uci = 0; V_uci < V_ucLength; V_uci++)
	{
		*(pV_ulArray + V_uci) = 0;
	}
}

/*******************************************************************************
函数原型: void SF_ENSPIMode_MeterIC(void)
功能描述: 使能计量芯片SPI总线
输入参数: 无
输出参数: 无
返回参数: 无
调用位置: 
备    注: 通过控制CS口线控制计量芯片
*******************************************************************************/
void SF_ENSPIMode_MeterIC(void)
{
	SET_EMETERDOUT_INPUT();
	SET_EMETERDIN_OUTPUT();
	SET_EMETERSCK_OUTPUT();
	SET_EMETERCS_OUTPUT();
	EMETERSCK_OUT_1;
	SF_Delay(C_DELAY2US);
	EMETERCS_EN;
	SF_Delay(C_DELAY2US);
	EMETERCS_DIS;
	SF_Delay(C_DELAY2US);
	EMETERCS_EN;
}

/*******************************************************************************
函数原型: void SF_WriteOneByte_MeterIC(uchar8 V_ucSendData)
功能描述: 写计量芯片一字节数据
输入参数: uchar8 V_ucSendData准备写入的数据
输出参数: 无
返回参数: 无
调用位置: 
备    注: 单片控制计量芯片写数据操作的最底层函数，写入数据按照从高位到低位顺序写入
*******************************************************************************/
void SF_WriteOneByte_MeterIC(uchar8 V_ucSendData)
{
	uchar8 V_uci;

	SET_EMETERDOUT_INPUT();
	SET_EMETERSCK_OUTPUT();
	SET_EMETERDIN_OUTPUT();
	EMETERSCK_OUT_0;
	for (V_uci = 0; V_uci < 8; V_uci++)
	{
		EMETERSCK_OUT_1;
		if ( (V_ucSendData & 0x80) != 0)
		{
			EMETERDIN_OUT_1;
		}
		else
		{
			EMETERDIN_OUT_0;
		}
		SF_Delay(C_DELAY2US);
		EMETERSCK_OUT_0;
		V_ucSendData = V_ucSendData << 1;
		SF_Delay(C_DELAY2US);
	}
	EMETERSCK_OUT_0;
}

/*******************************************************************************
函数原型: uchar8 SF_ReadOneByte_MeterIC(void)
功能描述: 读取计量芯片一字节数据
输入参数: 无
输出参数: 无
返回参数: V_ucDataTemp计量芯片读取的数据，读取数据位顺序为从高位到低位
调用位置: 
备    注: 
*******************************************************************************/
uchar8 SF_ReadOneByte_MeterIC(void)
{
	uchar8 V_uci, V_ucDataTemp;

	SET_EMETERDOUT_INPUT();
	SET_EMETERSCK_OUTPUT();
	SET_EMETERDIN_OUTPUT();
	V_ucDataTemp = 0;
	EMETERSCK_OUT_0;
	for (V_uci = 0;V_uci < 8;V_uci++)
	{
		V_ucDataTemp = V_ucDataTemp << 1;
		EMETERSCK_OUT_1;
		SF_Delay(C_DELAY2US);
		if (READ_EMETERDOUT)
		{
			V_ucDataTemp |= 0x01;
		}
		EMETERSCK_OUT_0;
		SF_Delay(C_DELAY2US);
	}
	EMETERSCK_OUT_0;
	return V_ucDataTemp;
}

/*******************************************************************************
函数原型: void SF_Eable_MeterIC(void)
功能描述: 使能计量芯片
输入参数: 无
输出参数: 无
返回参数: 无
调用位置: 
备    注: 拉低CS脚，使能计量芯片
*******************************************************************************/
void SF_Eable_MeterIC(void)
{
	SET_EMETERCS_OUTPUT();
	EMETERCS_DIS;
	SF_Delay(C_DELAY2US);
	SET_EMETERSCK_OUTPUT();
	EMETERSCK_OUT_0;
	SF_Delay(C_DELAY2US);
	EMETERCS_EN;
	SF_Delay(C_DELAY4US);
}

/*******************************************************************************
函数原型: void SF_Disable_MeterIC(void)
功能描述: 失能计量芯片
输入参数: 无
输出参数: 无
返回参数: 无
调用位置: 
备    注: 置高CS脚，失能计量芯片
*******************************************************************************/
void SF_Disable_MeterIC(void)
{
	SET_EMETERCS_OUTPUT();
	EMETERCS_DIS;
	SF_Delay(C_DELAY2US);
}

/*******************************************************************************
函数原型: void SF_WriteEnable_MeterIC(void)
功能描述: 计量芯片写使能
输入参数: 无
输出参数: 无
返回参数: 无
调用位置: 
备    注: 计量芯片写使能
*******************************************************************************/
void SF_WriteEnable_MeterIC(void)
{
	uchar8 V_ucData[4], V_uci;
	ulong32 V_ulEnWriteData;

	V_ulEnWriteData = C_EnWriteCalDataMeterIC;	/*写使能直接写入0xC900005A高字节为特殊寄存器地址,低三字节为写入数据*/
	SF_Eable_MeterIC();
	PF_Ulong32ToBufferX(V_ucData, &V_ulEnWriteData, C_MeterICDataLEN);
	for (V_uci = C_MeterICDataLEN; V_uci > 0; V_uci--)
	{
		SF_WriteOneByte_MeterIC(V_ucData[V_uci - 1]);
	}
	SF_Disable_MeterIC();
}

/*******************************************************************************
函数原型: void SF_WriteDisable_MeterIC(void)
功能描述: 计量芯片写失能
输入参数: 无
输出参数: 无
返回参数: 无
调用位置: 
备    注: 计量芯片写使能主要是对计量芯片C9特殊寄存器进行操作，写入0x000000为写失能，写入0x00005A为写使能
*******************************************************************************/
void SF_WriteDisable_MeterIC(void)
{
	uchar8 V_ucData[4], V_uci;
	ulong32 V_ulDisWriteData;

	V_ulDisWriteData = C_DisWriteCalDataMeterIC;	/*写失能直接写入0xc9000000高字节为特殊寄存器地址,低三字节为写入数据*/
	SF_Eable_MeterIC();
	PF_Ulong32ToBufferX(V_ucData, &V_ulDisWriteData, C_MeterICDataLEN);
	for (V_uci = 0; V_uci < C_MeterICDataLEN; V_uci++)
	{
		SF_WriteOneByte_MeterIC(V_ucData[V_uci]);
	}
	SF_Disable_MeterIC();
}

/*******************************************************************************
函数原型: uchar8 SF_WriteOneReg_MeterIC(uchar8 *pV_ucData, uchar8 V_ucRegAddr, uchar8 V_ucSafeFlag)
功能描述: 将三字节数据写入计量芯片寄存器指定地址(仅适用于写校表参数寄存器)
输入参数: uchar8 *pV_ucData：预写入数据指针;uchar8 V_ucRegAddr：计量芯片寄存器地址;uchar8 V_ucSafeFlag：安全标志
输出参数: 无
返回参数: C_OK：写入成功;C_SafeFlagError：数据不安全
调用位置: 
备    注: 通过写一字节数据，写入将地址，地址数据首位要置1，然后调用3次写一字节数据，按从高字节到低字节将3字节数据写入计量芯片
*******************************************************************************/
uchar8 SF_WriteOneReg_MeterIC(uchar8 *pV_ucData, uchar8 V_ucRegAddr, uchar8 V_ucSafeFlag)
{
	uchar8 V_Data[3], V_uci;

	V_Data[0] = *pV_ucData;
	V_Data[1] = *(pV_ucData + 1);
	V_Data[2] = *(pV_ucData + 2);
	if (V_ucSafeFlag == C_DataSafe)
	{
		SF_WriteEnable_MeterIC();
		SF_Eable_MeterIC();
		SF_WriteOneByte_MeterIC(V_ucRegAddr | C_WriteDataMeterIC);	/*地址数据首位置1，写入数据*/
		for (V_uci = 3; V_uci > 0; V_uci--)
		{
			SF_WriteOneByte_MeterIC(V_Data[V_uci - 1]);
		}
		SF_Disable_MeterIC();
		SF_WriteDisable_MeterIC();
		GV_ucWriteRegSafeFlag = C_DataUnsafe;
		return C_OK;
	}
	else
	{
		GV_ucWriteRegSafeFlag = C_DataUnsafe;
		return C_SafeFlagError;
	}
}

/*******************************************************************************
函数原型: void SF_ReadDataModeSet(uchar8 V_ucModeData)
功能描述: 选择计量芯片寄存器读取控制:读取计量参数寄存器和读取校表参数寄存器
输入参数: uchar8 V_ucModeData:C_ReadMeaDataRegFlag=读取计量数据寄存器；C_ReadCalDataRegFlag=读取校表参数寄存器
输出参数: 无
返回参数: 无
调用位置: 
备    注: 读取计量芯片寄存器设置函数，通过配置特殊寄存器C6为0x000000读取计量参数寄存器、为0x00005A读取校表参数寄存器
*******************************************************************************/
void SF_ReadDataModeSet(uchar8 V_ucModeData)
{
	uchar8 V_ucData[4], V_uci;
	ulong32 V_ulEnWriteData;

	if (V_ucModeData == C_ReadMeaDataRegFlag)
	{
		V_ulEnWriteData = C_EnReadMeaDataMeterIC;	/*计量芯片设置为读取(计量)参数高字节为寄存器地址，低三字节为写入数据*/
	}
	else
	{
		V_ulEnWriteData = C_EnReadCalDataMeterIC;	/*计量芯片设置为读取(校表)参数高字节为寄存器地址，低三字节为写入数据*/
	}
	SF_Eable_MeterIC();								/*CS使能计量芯片*/
	PF_Ulong32ToBufferX(V_ucData, &V_ulEnWriteData, C_MeterICDataLEN);
	for (V_uci = C_MeterICDataLEN; V_uci > 0; V_uci--)
	{
		SF_WriteOneByte_MeterIC(V_ucData[V_uci - 1]);
	}
	SF_Disable_MeterIC();	/*CS失能计量芯片*/
}

/*******************************************************************************
函数原型: void SF_ReadOneReg_MeterIC(uchar8 V_ucRegAddr, uchar8 *pV_ucData, uchar8 V_ucMeaORCal)
功能描述: 从计量芯片计量参数寄存器中读取三字节数据
输入参数: uchar8 V_ucRegAddr：预读取计量芯片寄存器地址;uchar8 *pV_ucData：数据转存指针;uchar8 V_ucMeaORCal  C_ReadMeaDataRegFlag:读取计量参数寄存器   C_ReadCalDataRegFlag:读取校表参数寄存器
输出参数: uchar8 *pV_ucData数据指针中存储V_ucRegAddr地址下的三字节数据(7022E芯片读取的计量参数为三字节有效，校表参数为两字节有效)
返回参数: 读取成功C_OK
调用位置: 
备    注: 读取计量芯片寄存器设置函数，通过配置特殊寄存器C6为0x000000读取计量参数寄存器、为0x00005A读取校表参数寄存器
*******************************************************************************/
uchar8 SF_ReadOneReg_MeterIC(uchar8 V_ucRegAddr, uchar8 *pV_ucData, uchar8 V_ucMeaORCal)
{
	SF_WriteEnable_MeterIC();
	SF_ReadDataModeSet(V_ucMeaORCal);
	SF_Eable_MeterIC();
	SF_WriteOneByte_MeterIC(V_ucRegAddr & C_ReadDataMeterIC);
	SF_Delay(C_DELAY2US);
	*(pV_ucData + 2) = SF_ReadOneByte_MeterIC();
	*(pV_ucData + 1) = SF_ReadOneByte_MeterIC();
	*pV_ucData = SF_ReadOneByte_MeterIC();
	return C_OK;
}

/*******************************************************************************
函数原型: void SF_ReadBufferReg_MeterIC(uchar8 V_ucRegAddr, uchar8 *pV_ucData)
功能描述: 从计量芯片数据缓冲寄存器中读取三字节数据
输入参数: uchar8 V_ucRegAddr：预读取计量芯片寄存器地址;uchar8 *pV_ucData：数据转存指针
输出参数: uchar8 *pV_ucData数据指针中存储V_usRegAddr地址下的三字节数据(7022E芯片读取的计量参数为三字节有效，校表参数为两字节有效)
返回参数: 读取成功C_OK
调用位置: 
备    注: 读取计量芯片寄存器设置函数，通过配置特殊寄存器C6为0x000000读取计量参数寄存器、为0x00005A读取校表参数寄存器
*******************************************************************************/
uchar8 SF_ReadBufferReg_MeterIC(uchar8 V_ucRegAddr, uchar8 *pV_ucData)
{
	SF_WriteOneByte_MeterIC(V_ucRegAddr & C_ReadDataMeterIC);
	SF_Delay(C_DELAY2US);
	*(pV_ucData + 2) = SF_ReadOneByte_MeterIC();
	*(pV_ucData + 1) = SF_ReadOneByte_MeterIC();
	*pV_ucData = SF_ReadOneByte_MeterIC();
	return C_OK;
}

/*******************************************************************************
函数原型: void SF_HardwareRESET_MeterIC(void)
功能描述: 通过复位RESET管脚，复位计量芯片，并重新清计量芯片电能数据寄存器
输入参数: 无
输出参数: 无
返回参数: 无
调用位置: 
备    注: 硬件复位计量芯片，在复位过程中IRQ输出高电平，但是在复位恢复正常工作之后，IRQ变为低电平，在写入校表参数之后，IRQ又会拉高
*******************************************************************************/
void SF_HardwareRESET_MeterIC(void)
{
	uchar8 V_uci, V_ucj;

	SET_EMETERRST_OUTPUT();
	SET_EMETERIRQ_INPUT();
	EMETERRST_WORK;
	SF_Delay(C_DELAY1MS);
	SF_Delay(C_DELAY1MS);
	for (V_uci = 0; V_uci < 3; V_uci++)
	{
		EMETERRST_RESET;
		SF_Delay(C_DELAY1MS);
		SF_Delay(C_DELAY1MS);
		EMETERRST_WORK;
		for (V_ucj = 0; V_ucj < 100; V_ucj++)
		{
			SF_Delay(C_DELAY1MS);
			if (READ_EMETERIRQ == 0)
			{
				return;
			}
		}
	}
}

/*******************************************************************************
函数原型: void SF_PowerDownHardwareRESET_MeterIC(void)
功能描述: 通过复位RESET管脚，复位计量芯片，并重新清计量芯片电能数据寄存器
输入参数: 无
输出参数: 无
返回参数: 无
调用位置: 
备    注: 低功耗状态下硬件复位计量芯片，在复位过程中IRQ输出高电平，但是在复位恢复正常工作之后，IRQ变为低电平，在写入校表参数之后，IRQ又会拉高
*******************************************************************************/
void SF_PowerDownHardwareRESET_MeterIC(void)
{
	uchar8 V_uci, V_ucj;

	SET_EMETERRST_OUTPUT();
	SET_EMETERIRQ_INPUT();
	EMETERRST_WORK;
	SF_Delay(C_DELAY1MSPowerDown);
	SF_Delay(C_DELAY1MSPowerDown);
	for (V_uci = 0; V_uci < 3; V_uci++)
	{
		EMETERRST_RESET;
		SF_Delay(C_DELAY1MSPowerDown);
		SF_Delay(C_DELAY1MSPowerDown);
		EMETERRST_WORK;
		for (V_ucj = 0; V_ucj < 100; V_ucj++)
		{
			SF_Delay(C_DELAY1MSPowerDown);
			if (READ_EMETERIRQ == 0)
			{
				return;
			}
		}
	}
}

/*******************************************************************************
函数原型: void  SF_Initial_MeterIC(uchar8 V_ucInitMode)
功能描述: 初始化计量芯片，配置计量芯片开始寄存器，并更新校验和
输入参数: uchar8 V_ucInitMode为C_InitPowerDown时为低功耗模式下初始化计量芯片；为C_InitNormal时为正常模式下初始化计量芯片
输出参数: 无
返回参数: 无
调用位置: 
备    注: 
*******************************************************************************/
void  SF_Initial_MeterIC(uchar8 V_ucInitMode)
{
	uchar8 V_ucCalRegData[4], V_uci, V_ucDataLen;
	ushort16 V_usData;
	ulong32 V_ulCalData;

	SF_HardwareRESET_MeterIC();												/*硬件复位计量芯片*/
	SF_ENSPIMode_MeterIC();
	SF_Eable_MeterIC();
	GV_ulCalDataChk0SUM = C_Check0RetData;
	GV_ulCalDataChk1SUM = C_Check1RetData;
	SF_ClearUcharArray(V_ucCalRegData, 4);
	V_usData = C_ModeCfg_Data;
	if (V_ucInitMode == C_InitPowerDown)
	{
		V_usData &= 0xDFFF;													/*低功耗初始化模式相关bit13置零*/
	}
	PF_Ushort16ToBuffer2(V_ucCalRegData, &V_usData);
	SF_WriteOneReg_MeterIC(V_ucCalRegData, C_ModeCfg_Reg, C_DataSafe);		/*模式相关控制初始化*/
	SF_TemRectify_MeterIC();
	SF_ClearUcharArray(V_ucCalRegData, 4);
	V_usData = C_ModuleCFG_Data;
	PF_Ushort16ToBuffer2(V_ucCalRegData, &V_usData);
	SF_WriteOneReg_MeterIC(V_ucCalRegData, C_ModuleCFG_Reg, C_DataSafe);	/*电能模块控制配置初始化*/
	for (V_uci = 0; V_uci < C_CalData_Len; V_uci++)
	{
		SF_ClearUcharArray(V_ucCalRegData, 4);
		V_ucDataLen = C_CalDataLen;
		if (Str_Table2_CalData[V_uci].MeterIC_WR | C_Write_Table2)
		{
			if (Str_Table2_CalData[V_uci].DataProcess_WR == C_WandR_Table2)
			{
				if (InF_Read_RecMeterData(V_uci, V_ucCalRegData, &V_ucDataLen) == C_OK)
				{
					PF_BufferXToUlong32(V_ucCalRegData, &V_ulCalData, V_ucDataLen);
					if (Str_Table2_CalData[V_uci].Check == C_Check0_Reg)	/*校验和0计算*/
					{
						GV_ulCalDataChk0SUM += V_ulCalData;
						GV_ulCalDataChk0SUM &= 0x00FFFFFF;
					}
					if (Str_Table2_CalData[V_uci].Check == C_Check1_Reg)	/*校验和1计算*/
					{
						GV_ulCalDataChk1SUM += V_ulCalData;
						GV_ulCalDataChk1SUM &= 0x00FFFFFF;
					}
					GV_ucWriteRegSafeFlag = C_DataSafe;
					if ( (V_uci == 0x03) && (V_ucInitMode == C_InitPowerDown) )
					{
						V_ucCalRegData[1] &= 0x0F;							/*低功耗配置EMU参数，关闭脉冲输出*/
					}
					SF_WriteOneReg_MeterIC(V_ucCalRegData, V_uci, GV_ucWriteRegSafeFlag);
				}
				else
				{
					if (InF_Read_RecMeterData(V_uci, V_ucCalRegData, &V_ucDataLen) == C_OK)
					{
						PF_BufferXToUlong32(V_ucCalRegData, &V_ulCalData, V_ucDataLen);
						if (Str_Table2_CalData[V_uci].Check == C_Check0_Reg)	/*校验和0计算*/
						{
							GV_ulCalDataChk0SUM += V_ulCalData;
							GV_ulCalDataChk0SUM &= 0x00FFFFFF;
						}
						if (Str_Table2_CalData[V_uci].Check == C_Check1_Reg)	/*校验和1计算*/
						{
							GV_ulCalDataChk1SUM += V_ulCalData;
							GV_ulCalDataChk1SUM &= 0x00FFFFFF;
						}
						GV_ucWriteRegSafeFlag = C_DataSafe;
						if ( (V_uci == 0x03) && (V_ucInitMode == C_InitPowerDown) )
						{
							V_ucCalRegData[1] &= 0x0F;							/*低功耗配置EMU参数，关闭脉冲输出*/
						}
						SF_WriteOneReg_MeterIC(V_ucCalRegData, V_uci, GV_ucWriteRegSafeFlag);
					}
					else
					{
						GV_ulCalDataChk0SUM = ~GV_ulCalDataChk0SUM;				/*如果数据层读取校表参数失败则校验和数据去反，使校验和数据错误*/
						GV_ulCalDataChk1SUM = ~GV_ulCalDataChk1SUM;
						break;
					}
				}
			}
		}
	}
	GStr_PowerData.Deriction = 0;												/*功率方向全部初始为正向*/
}

/*******************************************************************************
函数原型: void SF_ClearEnergyData_MeterIC(void)
功能描述: 清计量芯片电能寄存器
输入参数: 无
输出参数: 无
返回参数: 无
调用位置: 
备    注: 通过读取计量芯片的电能寄存器，来起到清零电能寄存器的目的，计量芯片配置为读后清
*******************************************************************************/
void SF_ClearEnergyData_MeterIC(void)
{
	uchar8 V_uci, V_ucData[3];

	for (V_uci = 0; V_uci < C_EnergyRegADDrTol; V_uci++)
	{
		SF_ReadOneReg_MeterIC(Str_EnergyRegADDr[V_uci], V_ucData, C_ReadMeaDataRegFlag);
	}
}

/*******************************************************************************
函数原型: void SF_TemRectify_MeterIC(void)
功能描述: 配置温度补偿相关校表参数
输入参数: 无
输出参数: 无
返回参数: 无
调用位置: 
备    注: (暂未使用)配置温度补偿寄存器及全通道增益寄存器(地址：0x32)，上电初始化。第1次没有校该寄存器表，采用默认值
*******************************************************************************/
void SF_TemRectify_MeterIC(void)
{
	uchar8 V_ucCalRegData[4], V_ucCalRegData1[4], V_ucDataLen, V_uci, V_ucj;
	uchar8 V_ucReturnFlag;
	ulong32 V_ulCalData, V_ulCalData32;

	V_ucDataLen = C_CalDataLen;

	for (V_uci = 0;V_uci < 3; V_uci++)
	{
		switch (V_uci)
		{
			case 0:					/*C_TCcoffA_Reg:*/
            {
				V_ulCalData = C_Vref2_Data;
				V_ucj = C_TCcoffA_Reg;
            }break;
				
			case 1:					/*C_TCcoffB_Reg:*/
            {
				V_ulCalData = C_Vref1_Data;
				V_ucj = C_TCcoffB_Reg;
            }break;
				
			case 2:					/*C_TCcoffC_Reg:*/
            {
				V_ulCalData = C_VrefC_Data;
				V_ucj = C_TCcoffC_Reg;
            }break;
				
			default:
            break;
		}
		PF_Ulong32ToBufferX(V_ucCalRegData, &V_ulCalData, 4);
		V_ucDataLen = C_CalDataLen;
		V_ucReturnFlag = InF_Read_RecMeterData(V_ucj, V_ucCalRegData1, &V_ucDataLen);
		V_ucCalRegData1[3] = 0;
		PF_BufferXToUlong32(V_ucCalRegData1, &V_ulCalData32, 4);
		if ( (V_ucReturnFlag != C_OK) || (V_ulCalData32 == 0) )												/*总清后也采用默认值*/
		{
			V_ucDataLen = C_CalDataLen;
			InF_Write_RecMeterData(C_Msg_Communication, V_ucCalRegData, V_ucDataLen, C_W_SafeFlag, V_ucj);	/*写E2数据,等到更新校验和时重新更新计量寄存器*/
		}
	}
	V_ucj = C_AllGain_Reg;
	V_ucDataLen = C_CalDataLen;
	if (C_Temp_VrefAotu == C_Temp_VrefAotu_En)																/*使能温度补偿，*/
	{
		V_ulCalData = C_Allgain_EnTemp;
	}
	else
	{
		V_ulCalData = C_Allgain_DisTemp;
	}
	PF_Ulong32ToBufferX(V_ucCalRegData, &V_ulCalData, 4);
	V_ucDataLen = C_CalDataLen;

	if (InF_Read_RecMeterData(V_ucj, V_ucCalRegData1, &V_ucDataLen) != C_OK)
	{
		InF_Write_RecMeterData(C_Msg_Communication, V_ucCalRegData, V_ucDataLen, C_W_SafeFlag, V_ucj);		/*写E2数据,等到更新校验和时重新更新计量寄存器*/
	}
	else											/*校验和正确，判断禁止温度使能，改值必须为0，防止原来使能，后面又编译为禁止使能情况*/
	{
		if (C_Temp_VrefAotu != C_Temp_VrefAotu_En)	/*禁止温度补偿，*/
		{
			if (C_Equal != PF_Campare_Data(V_ucCalRegData1, V_ucCalRegData, C_CalDataLen) )
			{
				InF_Write_RecMeterData(C_Msg_Communication, V_ucCalRegData, V_ucDataLen, C_W_SafeFlag, V_ucj);		/*写E2数据,等到更新校验和时重新更新计量寄存器*/
			}
		}
		else
		{
			V_ucCalRegData1[3] = 0;
			PF_BufferXToUlong32(V_ucCalRegData1, &V_ulCalData32, 4);
			if (V_ulCalData32 == 0)					/*总清后也采用默认值*/
			{
				InF_Write_RecMeterData(C_Msg_Communication, V_ucCalRegData, V_ucDataLen, C_W_SafeFlag, V_ucj);		/*写E2数据,等到更新校验和时重新更新计量寄存器*/
			}
		}
	}
}

/*******************************************************************************
函数原型: void SF_Power_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE)
功能描述: 功率数据读取
输入参数: Str_VARREGTYPE_Type *pStr_VARREGTYPE:原始值存放指针
输出参数: Str_VARREGTYPE_Type *pStr_VARREGTYPE:原始值存放指针
          Str_VARREGTYPE结构体中的有功功率数据、无功功率数据和视在功率数据(均为计量芯片中的数据原始值)
返回参数: 无
调用位置: 
备    注: 将计量芯片中的功率数据原始值读取出来，存储在相应的结构体当中
*******************************************************************************/
void SF_Power_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE)
{
	uchar8 V_uci, V_ucData[4];
	/*************有功功率数据读取**************/
	for (V_uci = 0; V_uci < 4; V_uci++)
	{
		SF_ClearUcharArray(V_ucData, 4);
		SF_ReadOneReg_MeterIC(Str_PowerRegADDr[V_uci], V_ucData, C_ReadMeaDataRegFlag);
		PF_BufferXToUlong32(V_ucData, &pStr_VARREGTYPE->WATTReg[V_uci], C_MeaDataLen);
	}
	/*************无功功率数据读取**************/
	for (V_uci = 0; V_uci < 4; V_uci++)
	{
		SF_ClearUcharArray(V_ucData, 4);
		SF_ReadOneReg_MeterIC(Str_PowerRegADDr[V_uci + 4], V_ucData, C_ReadMeaDataRegFlag);
		PF_BufferXToUlong32(V_ucData, &pStr_VARREGTYPE->VARReg[V_uci], C_MeaDataLen);
	}
	/*************视在功率数据读取**************/
	for (V_uci = 0; V_uci < 4; V_uci++)
	{
		SF_ClearUcharArray(V_ucData, 4);
		SF_ReadOneReg_MeterIC(Str_PowerRegADDr[V_uci + 8], V_ucData, C_ReadMeaDataRegFlag);
		PF_BufferXToUlong32(V_ucData, &pStr_VARREGTYPE->VAReg[V_uci], C_MeaDataLen);
	}
}

/*******************************************************************************
函数原型: void SF_Variable_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE)
功能描述: 读取出功率因数、频率、相角、温度、电压夹角数据，存储到特定结构体中
输入参数: Str_VARREGTYPE_Type *pStr_VARREGTYPE：原始值指针
输出参数: Str_VARREGTYPE结构体中的功率因数数据、电网频率、电流相角、温度、电压相角数据，均为计量芯片原始值
返回参数: 无
调用位置: 
备    注: 将一些计量参数的原始值读取出来，存储在相应结构体当中
*******************************************************************************/
void SF_Variable_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE)
{
	uchar8 V_uci, V_ucData[4];
	ulong32 *pV_ulVARREGTYPE[11] = {&pStr_VARREGTYPE->PfReg[0],  &pStr_VARREGTYPE->PfReg[1],  &pStr_VARREGTYPE->PfReg[2], &pStr_VARREGTYPE->PfReg[3],	/*功率因数原始值结构体*/
									&pStr_VARREGTYPE->FREQUENCY,																						/*电网频率原始值结构体*/
									&pStr_VARREGTYPE->YUIReg[0], &pStr_VARREGTYPE->YUIReg[1], &pStr_VARREGTYPE->YUIReg[2],								/*电流相角原始值结构体*/ 
									&pStr_VARREGTYPE->YUReg[0],  &pStr_VARREGTYPE->YUReg[1],  &pStr_VARREGTYPE->YUReg[2]};								/*电压相角原始值结构体*/ 

	/******************功率因数+电网频率+电流相角+电压相角读取(4+1+3+3个=11个）*****************/
	for (V_uci = 0; V_uci < 11; V_uci++)
	{
		SF_ClearUcharArray(V_ucData, 4);
		SF_ReadOneReg_MeterIC(Str_VariableRegADDr[V_uci], V_ucData, C_ReadMeaDataRegFlag);
		PF_BufferXToUlong32(V_ucData, pV_ulVARREGTYPE[V_uci], C_MeaDataLen);
	}
}

/*******************************************************************************
函数原型: void SF_Urms_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE)
功能描述: 读取电压数据，存储到特定结构体中
输入参数: Str_VARREGTYPE_Type *pStr_VARREGTYPE:原始值指针
输出参数: Str_VARREGTYPE结构体中的电压数据，为计量芯片中的原始值
返回参数: 无
调用位置: 
备    注: 读取电压数据原始数据，存储到相应结构体当中
*******************************************************************************/
void SF_Urms_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE)
{
	uchar8 V_uci, V_ucData[4];

	for (V_uci = 0; V_uci < C_UrmsRegADDrTol; V_uci++)
	{
		SF_ClearUcharArray(V_ucData, 4);
		SF_ReadOneReg_MeterIC(Str_UrmsRegADDr[V_uci], V_ucData, C_ReadMeaDataRegFlag);
		PF_BufferXToUlong32(V_ucData, &pStr_VARREGTYPE->VRmsVReg[V_uci], C_MeaDataLen);
	}
}

/*******************************************************************************
函数原型: void SF_Irms_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE)
功能描述: 读取电流数据，存储到特定结构体中
输入参数: Str_VARREGTYPE_Type *pStr_VARREGTYPE:原始值指针
输出参数: Str_VARREGTYPE结构体中的电流数据和零线电流数据，均为计量芯片原始值
返回参数: 无
调用位置: 
备    注: 读取电流数据原始数据，存储到相应结构体当中
*******************************************************************************/
void SF_Irms_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE)
{
	uchar8 V_uci, V_ucData[4];

	/**********************电流数据读取**********************/
	for (V_uci = 0; V_uci < C_IrmsRegADDrTol; V_uci++)
	{
		SF_ClearUcharArray(V_ucData, 4);
		SF_ReadOneReg_MeterIC(Str_IrmsRegADDr[V_uci], V_ucData, C_ReadMeaDataRegFlag);
		PF_BufferXToUlong32(V_ucData, &pStr_VARREGTYPE->VRmsIReg[V_uci], C_MeaDataLen);
	}
	/**********************三相电流矢量和数据读取******************/
	SF_ClearUcharArray(V_ucData, 4);
	SF_ReadOneReg_MeterIC(C_IRmsN0_Reg, V_ucData, C_ReadMeaDataRegFlag);
	PF_BufferXToUlong32(V_ucData, &pStr_VARREGTYPE->IRmsN0, C_MeaDataLen);
	/**********************零线电流数据读取******************/
	SF_ClearUcharArray(V_ucData, 4);
	SF_ReadOneReg_MeterIC(C_IORms_Reg, V_ucData, C_ReadMeaDataRegFlag);
	PF_BufferXToUlong32(V_ucData, &pStr_VARREGTYPE->IRmsNOSample, C_MeaDataLen);
}

/*******************************************************************************
函数原型: void SF_CurrentThreshold_MeterIC(ulong32 *pV_ulIrmsData)
功能描述: 对输入的电流原始值进行阀值判断，然后返回经过阀值判断之后的电流原始值
输入参数: ulong32  *pV_ulIrmsData电流原始值
输出参数: ulong32 *pV_ulIrmsData电流原始值
返回参数: 无
调用位置: 
备    注: 读取电流数据原始数据，存储到相应结构体当中
*******************************************************************************/
void SF_CurrentThreshold_MeterIC(ulong32 *pV_ulIrmsData)
{
	ulong32 V_ulIrmsData;
	ulong64 V_ullData;

	V_ulIrmsData = *pV_ulIrmsData;
	V_ullData = V_ulIrmsData;
	V_ullData *= 1000;
	V_ullData >>= 13;
	if (V_ullData < C_CurrentThreshold)
	{
		*pV_ulIrmsData = 0;
	}
	else
	{
		*pV_ulIrmsData = V_ulIrmsData;
	}
}

/*******************************************************************************
函数原型: void  SF_ReadEnergyData_MeterIC (void)
功能描述: 通过此函数，将电能数据从计量芯片中读取出，并存储到相应结构体中，以备调用
输入参数: 无
输出参数: GStr_EnergyData结构体中的电能数据，为计量芯片原始值
返回参数: 无
调用位置: 
备    注: 读取电能数据原始数据，存储到相应结构体当中
*******************************************************************************/
void SF_ReadEnergyData_MeterIC(void)
{
	uchar8 V_uci, V_ucData[4];

	for (V_uci = 0; V_uci < C_EnergyRegADDrTol; V_uci++)
	{
		SF_ClearUcharArray(V_ucData, 4);
		SF_ReadOneReg_MeterIC(Str_EnergyRegADDr[V_uci], V_ucData, C_ReadMeaDataRegFlag);
		PF_Buffer2ToUshort16(V_ucData, (GStr_EnergyData.V_ucActiveEnergy_TABC + V_uci) );
	}
}

/*******************************************************************************
函数原型: void InF_MeterIC_ParseMessage(Str_Msg_Parameter *pStr_Msg_Parameter)
功能描述: 计量芯片500mS消息处理
输入参数: pStr_Msg_Parameter: 统一的Str_Msg_Parameter型变量
输出参数: GStr_EnergyData结构体中的电能数据，为计量芯片原始值
         SourceAddr= C_Msg_Dispatch：源地址为调度
         SourceAddr= C_Msg_MeterIC：源地址为计量模块
         DerictAddr = C_Msg_MeterIC
         Length=2；
         *Parameter=C_HalfSecond；调度500mS
         Length=1；
         无数据。上电初始化计量芯片
返回参数: 无
调用位置: 调度每500ms调用或者上电时由计量模块接口函数触发初始化计量芯片消息。
备    注: 
*******************************************************************************/
void InF_MeterIC_ParseMessage(Str_Msg_Parameter *pStr_Msg_Parameter)
{
	uchar8 V_ucData;
	ushort16 V_usDataLEN, V_usDataLenth, V_usDataEncode = 0;
	if (pStr_Msg_Parameter->DerictAddr == C_Msg_MeterIC)
	{
		/*************************500mS消息处理*************************/
		if ( (pStr_Msg_Parameter->SourceAddr == C_Msg_Dispatch) && (pStr_Msg_Parameter->PowerFlag == C_PowerOn) )
		{
			if (pStr_Msg_Parameter->Length == (Pt_Dispatch_Timing_Len + 1) )
			{
				if (*(pStr_Msg_Parameter->Parameter + 1) == C_HalfSecond)
				{
					SF_500mS_MeterIC();
				}
				if(*(pStr_Msg_Parameter->Parameter + 1) == C_SystemMinChange)			/*zlj新增调度min变化*/
				{
					SF_Cal1minAveragePower(&GStr_PowerAdd);
				}
			}
		}
		/*************************计量初始化消息处理*************************/
		if ( (pStr_Msg_Parameter->SourceAddr == C_Msg_MeterIC) && (pStr_Msg_Parameter->PowerFlag == C_PowerOn) )
		{
			if (pStr_Msg_Parameter->Length == (Pt_InitialMeterIC_Len + 1) )
			{

				SF_InitialALL_MeterIC(C_InitNormal);
			}
		}
		/*************************计量芯片故障总清消息处理*************************/
		if ( ( (pStr_Msg_Parameter->SourceAddr == C_Msg_Communication) || (pStr_Msg_Parameter->SourceAddr == C_Msg_Card) )
		&& (pStr_Msg_Parameter->PowerFlag == C_PowerOn) )
		{
			if (*pStr_Msg_Parameter->Parameter == Pt_MeterClear)
			{
				GV_ucMeterICErrorState = C_MeterICNormal;
				GV_ucMeterICErrorNum = 0;
				GV_ucMeterICErrorTime = 0;
				V_usDataLenth = CLHardError_State;
				InF_Read_Data(CHardError_State, &V_ucData, &V_usDataLenth, &V_usDataEncode);
				if (V_ucData & 0x01)
				{
					V_ucData &= C_MeterICRecoverState;
					V_usDataLEN = CLHardError_State;
					InF_Write_Data(C_Msg_MeterIC, CHardError_State, &V_ucData, V_usDataLEN, C_W_SafeFlag);
				}
			}
		}
	}
}

/*******************************************************************************
函数原型: void  SF_InitialALL_MeterIC (uchar8 V_ucInitMode)
功能描述: 初始化计量模块
输入参数: uchar8 V_ucInitMode为C_InitPowerDown时为低功耗模式下初始化计量芯片；为C_InitNormal时为正常模式下初始化计量芯片
输出参数: GV_ucUpdateTime:瞬时量更新数据层定时器初始化
          GV_ucCheckTime:校验和校验定时器初始化
          GV_ucEnergyLock:电能闭锁标志置为闭锁状态
          GStr_HEX_VARREGTYPE结构体清零
返回参数: 无
调用位置: 
备    注: 调用初始化计量芯片子函数，并将所有计量模块内部时序静态变量初始化
*******************************************************************************/
void  SF_InitialALL_MeterIC (uchar8 V_ucInitMode)
{
	uchar8 V_ucData;
	ushort16 V_usDataLen, V_usDataEncode = 0;
	ulong32 V_ulCurrentThresholdData;
    
	V_ulCurrentThresholdData = SF_CurrentThresholdGain_MeterIC();
	SF_Initial_MeterIC(V_ucInitMode);
	SF_InitialPowerCoeff();				/*初始化功率系数到RAM*/
	GV_ucUpdateTime = C_UpdateTime;		/*瞬时量更新数据层定时器初始化*/
	GV_ucCheckTime = C_CheckTime;		/*校验和校验定时器初始化*/
	GV_ucEnergyLock = C_EnergyLock;		/*电能闭锁标志置为闭锁状态*/
	GV_ucMeterICNum = 0;
	GV_ucMeterICErrorFlag = C_MeterICNormal;

	GV_ulSlipCurrentBuff[C_offA][0] = V_ulCurrentThresholdData;
	GV_ulSlipCurrentBuff[C_offB][0] = V_ulCurrentThresholdData;
	GV_ulSlipCurrentBuff[C_offC][0] = V_ulCurrentThresholdData;

	/*************************硬件故障状态字处理**************************/
	if (GV_ucMeterICErrorState != C_MeterICError)
	{
		if (GV_ucMeterICErrorNum++ > C_MeterICErrorNum)
		{
			GV_ucMeterICErrorState = C_MeterICError;
			V_usDataLen = CLHardError_State;
			InF_Read_Data(CHardError_State, &V_ucData, &V_usDataLen, &V_usDataEncode);
			V_ucData |= C_MeterICErrorState;
			V_usDataLen = C_OneByteLen;
			InF_Write_Data(C_Msg_MeterIC, CHardError_State, &V_ucData, V_usDataLen, C_W_SafeFlag);
			GV_ucMeterICErrorNum = 0;
		}
	}
	/************************HEX数据结构体清零**************************/
	memset(&GStr_HEX_VARREGTYPE, 0x00 , sizeof(GStr_HEX_VARREGTYPE) );

	/************************数据层瞬时量清零****************************/
	InF_ClearHexVarregtype_MeterIC(C_ClearCurrData);
}

/*******************************************************************************
函数原型: void SF_Odd_Harmonic_CheckCurrent(uchar8 V_ucConditionFlag)
功能描述: 用于奇次谐波补偿,电流条件判断处理
输入参数: C_Odd_Harmonic_CurrentFitFlag1 奇次谐波补偿，电流判断条件1标志(2.8-4A)
          C_Odd_Harmonic_CurrentFitFlag2 奇次谐波补偿，电流判断条件2标志(1.4-2A)
输出参数: 无
返回参数: C_OK  C_Error
调用位置: 
备    注: 奇次谐波补偿条件：电流（2种条件对应两种台体）：2.8-4A（1.4-2A），符合条件进行补偿
*******************************************************************************/
void SF_Odd_Harmonic_CheckCurrent(uchar8 V_ucConditionFlag)
{
	uchar8 V_uci;
	ulong32 V_ulCurrent; 
	
	switch (V_ucConditionFlag)
	{
		case C_Odd_Harmonic_CurrentFitFlag1:							/*电流条件1判断（2.8-4A）*/
		{
			for (V_uci = 0; V_uci < 3; V_uci++)							/*A、B、C三相判断*/
			{
				V_ulCurrent = SF_ABS(GStr_HEX_VARREGTYPE.VRmsIRegHEX_ABC[V_uci]);
				if ( (V_ulCurrent < 2800) || (V_ulCurrent > 4000) )		/*电流条件1范围*/
				{
					break;
				}
			}
			if (V_uci == 3 )
			{
				GV_ucCurrent_Flag1 |= 0x01;
			}
			else
			{
				GV_ucCurrent_Flag1 &= 0xFE;
			}
		}break;

		case C_Odd_Harmonic_CurrentFitFlag2:							/*电流条件2判断（1.4-2A)*/
		{
			for (V_uci = 0; V_uci < 3; V_uci++)							/*A、B、C三相判断*/
			{
				V_ulCurrent = SF_ABS(GStr_HEX_VARREGTYPE.VRmsIRegHEX_ABC[V_uci]);
				if ( (V_ulCurrent < 1400) || (V_ulCurrent > 2000) )		/*电流条件2范围*/
				{
					break;
				}
			}
			if (V_uci == 3 )
			{
				GV_ucCurrent_Flag2 |= 0x01;
			}
			else
			{
				GV_ucCurrent_Flag2 &= 0xFE;
			}
		}break;

		default:
		break;
	}
}

/*******************************************************************************
函数原型: uchar8 SF_Odd_Harmonic_AddData(uchar8 V_ucPhaseCh, uchar8 *pV_ucAddData, ulong32 *pV_ulPgain_Data)
功能描述: 用于奇次谐波补偿中，对功率增益进行补偿
输入参数: V_ucPhaseCh:用于判断ABC相，pV_ucAddData：补偿值地址
输出参数: pV_ulPgain_Data：计算后的有功功率增益值地址
返回参数: C_OK  C_Error
调用位置: 
备    注: 
*******************************************************************************/
uchar8 SF_Odd_Harmonic_AddData(uchar8 V_ucPhaseCh, uchar8 *pV_ucAddData, ulong32 *pV_ulPgain_Data)
{
	uchar8 V_ucDataLength, V_ucReturnFlag;
	uchar8 V_ucPgain_Data[3];

	V_ucDataLength = C_CalDataLen;
	V_ucReturnFlag = InF_Read_RecMeterData(V_ucPhaseCh, V_ucPgain_Data, &V_ucDataLength);	/*A相有功功率增益0x04*/

	PF_BufferXToUlong32(V_ucPgain_Data, pV_ulPgain_Data, C_CalDataLen);
	if ( ( (pV_ucAddData[0]) & 0x80) == 0x00)
	{
		(*pV_ulPgain_Data) += pV_ucAddData[0];
	}
	else
	{
		(*pV_ulPgain_Data) -= pV_ucAddData[0] & 0x7F;
	}

	return V_ucReturnFlag;
}

/*******************************************************************************
函数原型: uchar8 SF_Odd_Harmonic_NOAddData(uchar8 V_ucPhaseCh, uchar8 *pV_ucAddData, ulong32 *pV_ulPgain_Data)
功能描述: 处理奇次谐波补偿时，获取功率增益
输入参数: V_ucPhaseCh:用于判断ABC相，pV_ucAddData：补偿值地址
输出参数: pV_ulPgain_Data：计算后的有功功率增益值地址
返回参数: C_OK  C_Error
调用位置: 
备    注: 
*******************************************************************************/
uchar8 SF_Odd_Harmonic_NOAddData(uchar8 V_ucPhaseCh, uchar8 *pV_ucAddData, ulong32 *pV_ulPgain_Data)
{
	uchar8 V_ucDataLength, V_ucReturnFlag;
	uchar8 V_ucPgain_Data[3];

	V_ucDataLength = C_CalDataLen;
	V_ucReturnFlag = InF_Read_RecMeterData(V_ucPhaseCh, V_ucPgain_Data, &V_ucDataLength);	/*A相有功功率增益0x04*/

	PF_BufferXToUlong32(V_ucPgain_Data, pV_ulPgain_Data, C_CalDataLen);

	return V_ucReturnFlag;
}

/*******************************************************************************
函数原型: void SF_Odd_Harmonic_Deal(void)
功能描述: 用于奇次谐波补偿处理
输入参数: 无
输出参数: 无
返回参数: 无
调用位置: 
备    注: 奇次谐波补偿条件：功率因数约0.650-0.860；电流（2种条件对应两种台体）：2.8-4A（1.4-2A），符合条件进行补偿
*******************************************************************************/
void SF_Odd_Harmonic_Deal(void)
{
	uchar8 V_ucReturnFlag, V_ucFlag, V_ucRead_RecMeterDataFlag = 0;
	uchar8 V_ucOddHar_AddData[3] = {0};
	uchar8 V_ucData[4] = {0};
	ulong32 V_ulPgainABC_Data[3], V_ulDataBefor;
	uchar8 V_uci;
	uchar8 V_ucPgainABC_Reg[3] = {C_PgainA_Reg, C_PgainA_Reg, C_PgainA_Reg};
	ushort16 V_usDataLength, V_usDataEncode = 0;

	GV_ucPowerFactor_Flag <<= 1;
	GV_ucCurrent_Flag1 <<= 1;
	GV_ucCurrent_Flag2 <<= 1;
	V_ucFlag = C_Error;

	if ( (SF_ABS(GStr_HEX_VARREGTYPE.PowerFactorHEX_TABC[C_offTT]) >= 650)
      && (SF_ABS(GStr_HEX_VARREGTYPE.PowerFactorHEX_TABC[C_offTT]) <= 860) )							/*功率因数是否在0.650-0.860范围内*/
	{
		GV_ucPowerFactor_Flag |= 0x01;
	}
	else
	{
		GV_ucPowerFactor_Flag &= 0xFE;
	}
	/********电流条件1判断（2.8-4A）***********/
	SF_Odd_Harmonic_CheckCurrent(C_Odd_Harmonic_CurrentFitFlag1);
	/********电流条件2判断（1.4-2A）***********/
	SF_Odd_Harmonic_CheckCurrent(C_Odd_Harmonic_CurrentFitFlag2);
	if ( (GV_ucPowerFactor_Flag & C_Odd_Harmonic_3TimesFitCon) == C_Odd_Harmonic_3TimesFitCon)
	{
		if ( (GV_ucCurrent_Flag1 & C_Odd_Harmonic_3TimesFitCon) == C_Odd_Harmonic_3TimesFitCon)			/*3次都符合条件*/
		{
			V_usDataLength = CL_OddHar_AddData1;
			V_ucFlag = InF_Read_Data(C_OddHar_AddData1, V_ucOddHar_AddData, &V_usDataLength, &V_usDataEncode);
			if (V_ucFlag != C_OK)
			{
				return;
			}
		}
		else
		{
			if ( (GV_ucCurrent_Flag2 & C_Odd_Harmonic_3TimesFitCon) == C_Odd_Harmonic_3TimesFitCon)		/*3次都符合条件*/
			{
				V_usDataLength = CL_OddHar_AddData2;
				V_ucFlag = InF_Read_Data(C_OddHar_AddData2, V_ucOddHar_AddData, &V_usDataLength, &V_usDataEncode);
				if(V_ucFlag != C_OK)
				{
					return;
				}
			}
		}
	}
	if (V_ucFlag == C_OK)
	{
		for (V_uci = 0; V_uci < 3; V_uci++)
		{
			if (V_ucFlag == C_OK)
			{
				V_ucReturnFlag = SF_Odd_Harmonic_AddData(V_ucPgainABC_Reg[V_uci], &V_ucOddHar_AddData[V_uci], &V_ulPgainABC_Data[V_uci]);
			}
			else	/*由补偿模式进入到不补偿时，需要重新写寄存器*/
			{
				V_ucReturnFlag = SF_Odd_Harmonic_NOAddData(V_ucPgainABC_Reg[V_uci], &V_ucOddHar_AddData[V_uci], &V_ulPgainABC_Data[V_uci]);
			}
			if (V_ucReturnFlag != C_OK)
			{
				V_ucRead_RecMeterDataFlag += 1;
			}
		}
		
		if (V_ucRead_RecMeterDataFlag == 0)
		{
			for (V_uci = 0; V_uci < 3; V_uci++)
			{
					/*ABC相更新计量芯片寄存器和校验和*/
				SF_ReadOneReg_MeterIC(V_ucPgainABC_Reg[V_uci], V_ucData, C_ReadCalDataRegFlag);
				PF_BufferXToUlong32(V_ucData, &V_ulDataBefor, 3);
				if (V_ulDataBefor != V_ulPgainABC_Data[V_uci])
				{
					PF_Ulong32ToBufferX(V_ucData, &V_ulPgainABC_Data[V_uci], 4);
					SF_WriteOneReg_MeterIC(V_ucData, V_ucPgainABC_Reg[V_uci], C_DataSafe);/*更新计量芯片寄存器*/
					GV_ulCalDataChk0SUM = GV_ulCalDataChk0SUM - V_ulDataBefor + V_ulPgainABC_Data[V_uci];
				}
			}
		}
	}
}

/*******************************************************************************
函数原型: Void SF_500mS_MeterIC(void)
功能描述: 用于计量模块消息处理调用，每被调用一次为500mS时间，通过对500mS时间的计数，取得内部实时时间
输入参数: 无
输出参数: 无
返回参数: 无
调用位置: 
备    注: 通过调度触发500mS时间函数，对所有时序静态变量进行减操作，如果有时间满足将触发相应计量操作
*******************************************************************************/
void SF_500mS_MeterIC(void)
{
	uchar8 V_ucData, V_ucDataLen, V_ucTempDataBuffer[5];
	uchar8 V_ucReturnFlag;
	char8 V_cTemp;
	ushort16 V_usCompTemp[3], V_usDataLen, V_usDataEncode = 0;

	/*******************校验和校验**********************/
	if ( (GV_ucCheckTime == 0) || (GV_ucCheckTime > C_MAXRepeatTime) )
	{
		GV_ucCheckTime = C_RepeatTime;
		if (SF_Test_MeterIC() != C_OK)
		{
			return;
		}
	}
	else
	{
		GV_ucCheckTime--;
		if (GV_ucCheckTime == 0)
		{
			GV_ucCheckTime = C_RepeatTime;
			if (C_Temp_VrefAotu == C_Temp_VrefAotu_En)	/*使能温度补偿，每s判断TPSdata寄存器温度值*/
			{
				SF_ReadOneReg_MeterIC(C_TempReg_Reg, V_ucTempDataBuffer, C_ReadMeaDataRegFlag);

				if (V_ucTempDataBuffer[0] > 128)
				{
					V_cTemp = V_ucTempDataBuffer[0] - 256;
				}
				else									/*128测试*/
				{
					V_cTemp = (char8)(V_ucTempDataBuffer[0]);
					if (V_ucTempDataBuffer[0] == 128)
					{
						V_cTemp = 0;					/*使能温度补偿*/
					}
				}
				V_ucDataLen = C_CalDataLen;
				V_ucReturnFlag = InF_Read_RecMeterData(C_EMCfg_Reg, V_ucTempDataBuffer, &V_ucDataLen);	/*温度补偿寄存器0x70*/
				V_ucDataLen = C_CalDataLen;
				if (C_OK == V_ucReturnFlag)
				{
					if (V_cTemp < C_TempOverData)		/*关闭温度补偿*/
					{
						if ( (V_ucTempDataBuffer[0] & C_VrefAotu_En) != C_VrefAotu_Dis)
						{
							V_ucTempDataBuffer[0] &= (~C_VrefAotu_En);
							SF_WriteOneReg_MeterIC(V_ucTempDataBuffer, C_EMCfg_Reg, C_DataSafe);		/*更新计量芯片寄存器*/
							InF_Write_RecMeterData(C_Msg_Communication, V_ucTempDataBuffer, V_ucDataLen, C_W_SafeFlag, C_EMCfg_Reg);	/*写E2数据*/
							GV_ulCalDataChk1SUM -= C_VrefAotu_En;										/*更新校验和*/
						}
					}
					else								/*使能温度补偿*/
					{
						if ( (V_ucTempDataBuffer[0] & C_VrefAotu_En) != C_VrefAotu_En)
						{
							V_ucTempDataBuffer[0] |= C_VrefAotu_En;
							SF_WriteOneReg_MeterIC(V_ucTempDataBuffer, C_EMCfg_Reg, C_DataSafe);		/*更新计量芯片寄存器*/
							InF_Write_RecMeterData(C_Msg_Communication, V_ucTempDataBuffer, V_ucDataLen, C_W_SafeFlag, C_EMCfg_Reg);	/*写E2数据*/
							GV_ulCalDataChk1SUM += C_VrefAotu_En;										/*更新校验和*/
						}
					}
				}
			}
			else										/*防止程序原来编译为使能，后又编译为关闭使能情况。*/
			{
				V_ucDataLen = C_CalDataLen;
				InF_Read_RecMeterData(C_EMCfg_Reg, V_ucTempDataBuffer, &V_ucDataLen);					/*温度补偿寄存器0x70*/
				V_ucDataLen = C_CalDataLen;
				if ( (V_ucTempDataBuffer[0] & C_VrefAotu_En) != C_VrefAotu_Dis)
				{
					V_ucTempDataBuffer[0] &= (~C_VrefAotu_En);
					SF_WriteOneReg_MeterIC(V_ucTempDataBuffer, C_EMCfg_Reg, C_DataSafe);				/*更新计量芯片寄存器*/
					InF_Write_RecMeterData(C_Msg_Communication, V_ucTempDataBuffer, V_ucDataLen, C_W_SafeFlag, C_EMCfg_Reg);			/*写E2数据*/
					GV_ulCalDataChk1SUM -= C_VrefAotu_En;												/*更新校验和*/
				}
			}
			
			if (C_Odd_Harmonic == C_Odd_Harmonic_En)
			{
				SF_Odd_Harmonic_Deal();
			}
			
			if (C_Even_Harmonic == C_Even_Harmonic_En)
			{
					/*直流偶次谐波的单点补偿*/
				if (SF_GetEvenHarmonicCompensationFlag() == C_Even_Harmonic_En)
				{
					/*获取偶次谐波含有量*/
					SF_GetEvenHarmonicContent();
					/*获取偶次谐波补偿数据*/
					SF_GetEvenHarmonicCompensationValue(V_usCompTemp);
					/*进行偶次谐波补偿*/
					SF_EvenHarmonicCompensation(V_usCompTemp, C_PhSregApq0_Reg);
					SF_EvenHarmonicCompensation(V_usCompTemp, C_PhSregApq1_Reg);	/*中电流*/
#if 0
					SF_EvenHarmonicCompensation(V_usCompTemp, C_PhSregApq2_Reg);	/*小电流*/
#endif
				}
				else
				{
					SF_ClearUlongArray( (ulong32 *)GV_lHD2Rate, CL_HD2Rate);		/*偶次谐波补偿失能，偶次谐波含有量清零*/
					GV_ucStepNum = 0;												/*偶次谐波补偿失能，运行步骤清零*/
					V_usCompTemp[0] = 0;											/*偶次谐波补偿失能，补偿值清零*/
					V_usCompTemp[1] = 0;
					V_usCompTemp[2] = 0;
					SF_EvenHarmonicCompensation(V_usCompTemp, C_PhSregApq0_Reg);
					SF_EvenHarmonicCompensation(V_usCompTemp, C_PhSregApq1_Reg);
#if 0 
					SF_EvenHarmonicCompensation(V_usCompTemp, C_PhSregApq2_Reg);
#endif
				}
			}

			if (SF_Test_MeterIC() != C_OK)
			{
				return;
			}
		}
	}
	/**********************数据层瞬时量更新************************/
	GV_ucUpdateTime--;
	if ( (GV_ucUpdateTime == 0) || (GV_ucUpdateTime > C_MAXRepeatTime) )
	{
		GV_ucUpdateTime = C_RepeatTime;
		if (GV_ucMeterICErrorFlag == C_MeterICNormal)
		{
			SF_PowerDataTidy_MeterIC();
		}
	}

	/**********************计量芯片故障恢复更新数据层**************************/
	if (GV_ucMeterICErrorState == C_MeterICError)
	{
		GV_ucMeterICErrorTime++;
		if (GV_ucMeterICErrorTime > C_MeterICErrorTime)
		{
			GV_ucMeterICErrorState = C_MeterICNormal;
			V_usDataLen = CLHardError_State;
			InF_Read_Data(CHardError_State, &V_ucData, &V_usDataLen, &V_usDataEncode);
			V_ucData &= C_MeterICRecoverState;
			InF_Write_Data(C_Msg_MeterIC, CHardError_State, &V_ucData, CLHardError_State, C_W_SafeFlag);
			GV_ucMeterICErrorTime = 0;
		}
	}
}

/*******************************************************************************
函数原型: uchar8 SF_Check_MeterIC (void)
功能描述: 读取校表寄存器，对校表参数进行计算得出校验和数据，然后和寄存器中读取出的校验和数据进行对比
输入参数: 无
输出参数: 无
返回参数: C_OK校验正常；C_CSError校验异常
调用位置: 
备    注: 对计量模块参数进行校验，通过500mS时序来完成交替校验的时间控制，每一分钟进行一次校验和校验与寄存器校验
*******************************************************************************/
uchar8 SF_Check_MeterIC (void)
{
	uchar8 V_ucCalRegDataSUM[4];
	ulong32 V_ulRegCS0SUM, V_ulRegCS1SUM;

	if ( (GV_ucCalibrationState == C_StartCalibrationOK) && (InF_JudgeIJTimer() == C_OK) )		/*这里也要判一下IJ*/
	{
		return C_OK;
	}
	else
	{
		SF_ClearUcharArray(V_ucCalRegDataSUM, 4);
		SF_ReadOneReg_MeterIC(C_CheckSum_Reg, V_ucCalRegDataSUM, C_ReadMeaDataRegFlag);
		PF_BufferXToUlong32(V_ucCalRegDataSUM, &V_ulRegCS0SUM, C_MeaDataLen);
		SF_ClearUcharArray(V_ucCalRegDataSUM, 4);
		SF_ReadOneReg_MeterIC(C_ChkSum1_Reg, V_ucCalRegDataSUM, C_ReadMeaDataRegFlag);
		PF_BufferXToUlong32(V_ucCalRegDataSUM, &V_ulRegCS1SUM, C_MeaDataLen);
		if ( (GV_ulCalDataChk0SUM == V_ulRegCS0SUM) && (GV_ulCalDataChk1SUM == V_ulRegCS1SUM) )
		{
			return C_OK;
		}
		else
		{
			return C_CSError;
		}
	}
}

/*******************************************************************************
函数原型: uchar8  InF_ValtageType(void)
功能描述: 读取数据层，获取当前电能表电压规格
输入参数: 无
输出参数: 无
返回参数: 220、380V：C_OK；57.7、100V：C_Error；
调用位置: 
备    注: 用于电压灭零判断，220V、380V灭零为8V，57.7\100V灭零值为2V；当读数据层失败时，默认为57.7V；
*******************************************************************************/
uchar8 InF_ValtageType(void)
{
	uchar8 V_ucData[CLVolage_Type];
	ushort16 V_usDataLen, V_usDataEncode = 0;
	uchar8 V_ucReturnFlag;

	V_usDataLen = CLVolage_Type;
	V_ucReturnFlag = InF_Read_Data(CVolage_Type, &V_ucData[0], &V_usDataLen, &V_usDataEncode);
	if (C_OK == V_ucReturnFlag)
	{
		if (V_ucData[0] < 2)	/*100V,57.7*/
		{
			V_ucReturnFlag = C_Error;
		}
	}
	else
	{
		V_ucReturnFlag = C_Error;
	}
	return V_ucReturnFlag;
}

/*******************************************************************************
函数原型: uchar8  SF_PhaseSequenceGain_MeterIC(void)
功能描述: 读取数据层，获取电能表类型
输入参数: 无
输出参数: 无
返回参数: 三相三线：C_3P3W，三相四线：C_3P4W
调用位置: 
备    注: 在需要电能表类型信息时，直接调用此函数，返回值直接就是电能表类型信息
*******************************************************************************/
uchar8 SF_PhaseSequenceGain_MeterIC(void)
{
	uchar8 V_ucData;
	ushort16 V_usDataLen, V_usDataEncode = 0;

	V_ucData = C_3P4W;	/*初始默认为三相四线*/
	V_usDataLen = CLLine_Type;
	if (InF_Read_Data(CLine_Type, &V_ucData, &V_usDataLen, &V_usDataEncode) != C_OK)
	{
		V_ucData = C_3P4W;
	}
	else if( (V_ucData != C_3P4W) && (V_ucData != C_3P3W) )
	{
		V_ucData = C_3P4W;
	}
	return V_ucData;
}

/*******************************************************************************
函数原型: ulong32 SF_CurrentThresholdGain_MeterIC(void)
功能描述: 通过读取数据层，获得电流阀值HEX码
输入参数: 无
输出参数: 无
返回参数: 电流阀值（HEX码）：V_ulCurrentData 四位小数
调用位置: 
备    注: 通过读取数据层获取电流阀值现在是HEX格式,增加一位小数，用于对电流数据灭零
*******************************************************************************/
ulong32 SF_CurrentThresholdGain_MeterIC(void)
{
	uchar8 V_ucData[4];
	ulong32 V_ulCurrentData;
	ushort16 V_usDataLen, V_usDataEncode = 0;

	SF_ClearUcharArray(V_ucData, 4);
	V_usDataLen = CLStart_Up_Current;
	InF_Read_Data(CStart_Up_Current, V_ucData, &V_usDataLen, &V_usDataEncode);
	PF_BufferXToUlong32(V_ucData, &V_ulCurrentData, C_FourByteLen);
	V_ulCurrentData *= 10;	/*增加一位小数，数据层启动电流数据为三位小数，但是电流阀值判断程序中需要四位小数数据*/
/*设置的时候已经经过了90%阈值的处理，这里就不再做处理了*/
	return V_ulCurrentData;
}

/*******************************************************************************
函数原型: ulong32 SF_PowerThresholdGain_MeterIC(void)
功能描述: 通过读取数据层，获得合相功率阀值HEX码
输入参数: 无
输出参数: 无
返回参数: 功率阀值（HEX码）：V_ulPowerData	XXX.XXXw 无符号 (此数据为合相功率阀值)
调用位置: 
备    注: 通过读取数据层获取功率阀值HEX码，用于对功率数据灭零，但是为了功率数据、电流数据和电压数据统一灭零，功率数据灭零暂时参考电流和电压数据是否为零。
*******************************************************************************/
ulong32 SF_PowerThresholdGain_MeterIC(void)
{
	uchar8 V_ucData[4];
	ulong32 V_ulPowerData;
	ushort16 V_usDataLen, V_usDataEncode = 0; 

	SF_ClearUcharArray(V_ucData, 4);
	V_usDataLen = CLStart_Up_Power;
	InF_Read_Data(CStart_Up_Power, V_ucData, &V_usDataLen, &V_usDataEncode);
	PF_BufferXToUlong32(V_ucData, &V_ulPowerData, V_usDataLen);
	V_ulPowerData *= 75;				/*75%启动功率为功率阀值*/
	V_ulPowerData /= 100;
	return V_ulPowerData;
}

/*******************************************************************************
函数原型: long32 SF_CountRealPower_MeterIC(ulong32 V_ulPowerData, uchar8 V_ucFlagPower)
功能描述: 本部分负责将有、无功功率原始数据转换成符合需量模块要求的hex数据
输入参数: ulong32 V_ulPowerData功率数据原始参数
          uchar8 V_ucFlagPower功率数据类型：C_PowerFlag_T为总功率标识，C_PowerFlag_ABC为分相标识
          序号C_PowerFactorNO中存储的功率系数，用于功率数据计算
输出参数: 无
返回参数: long32 V_lPowerData有符号功率值，有效位为1LSB=0.001W
调用位置: 
备    注: 通过此函数，可以将功率原始数据换算成符合需量要求的功率真实数据hex格式。
*******************************************************************************/
long32 SF_CountRealPower_MeterIC(ulong32 V_ulPowerData, uchar8 V_ucFlagPower)
{
	uchar8 V_ucPowerDataBuffer[8];
	long32 V_lPowerData;				/*zlj改成有符号数*/
	ulong64 V_ullPowerFactorData, V_ullPower8ByteBuffer, V_ullPowerRealData;
	uchar8 V_ucsign = C_Plus;

	/*******************读取功率系数***********************/
	V_ullPowerFactorData = SF_GetPowerCoeff();
	/********************功率数据计算***********************************/
	V_lPowerData = V_ulPowerData & 0x00FFFFFF;
	if (V_lPowerData & 0x00800000)
	{
		V_lPowerData |= 0xFF000000;		/*计量芯片读出来的原始值是3个字节的，最高位是符号位，不符合lon32的负数格式，这里转化成lon32的负数格式*/
		V_lPowerData = 0 - V_lPowerData;
		V_ucsign = C_Minus;
	}
	SF_ClearUcharArray(V_ucPowerDataBuffer, 8);
	PF_Ulong32ToBufferX(V_ucPowerDataBuffer, (ulong32 *)&V_lPowerData, C_MeaDataLen);
	PF_Buffer8ToUlong64(V_ucPowerDataBuffer, &V_ullPower8ByteBuffer, C_MeaDataLen);
	if (V_ucFlagPower == C_PowerFlag_T)
	{
		V_ullPowerRealData = V_ullPower8ByteBuffer * 2 * V_ullPowerFactorData / 1000;
	}
	else
	{
		V_ullPowerRealData = V_ullPower8ByteBuffer * V_ullPowerFactorData / 1000;
	}
	SF_ClearUcharArray(V_ucPowerDataBuffer, 8);
	PF_Ulong64ToBuffer8(V_ucPowerDataBuffer, &V_ullPowerRealData, 4);
	PF_BufferXToUlong32(V_ucPowerDataBuffer, (ulong32 *)&V_lPowerData, 4);

	if (V_ucsign == C_Minus)
	{
		V_lPowerData = 0 - V_lPowerData;
	}
	return V_lPowerData;
}

/*******************************************************************************
函数原型: void SF_DemandPowerDataTidy_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE)
功能描述: 通过此函数，将功率原始值计算得出符合需量要求的真实值，并转存到需量用功率数据结构体中。这里不需要灭零和存储方向参数
输入参数: Str_VARREGTYPE_Type *pStr_VARREGTYPE：原始值指针
          Str_VARREGTYPE有功和无功数据,功率原始值,HEX,三字节有符号数据,三字节首位符号位,多余高位一字节数据补零
输出参数: GStr_PowerData.Deriction功率方向:0~2:有功A/B/C 3:有功总 4~6:无功A/B/C  7:无功总 (0)正 (1)负
          GStr_PowerData功率数据 HEX 4字节数据 无符号数 XXXX.XXXw
返回参数: 无
调用位置: 
备    注: 需量用功率数据换算整理，存储到特定结构体当中，然后调用接口函数，将功率数据给需量模块
*******************************************************************************/
void SF_DemandPowerDataTidy_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE)
{
	uchar8 V_ucStateBuffer[5], V_ucPowerDeriction;
	ushort16 V_usState0, V_usStateLen, V_usDataEncode = 0;
	ulong32 V_ulPowerThresholdGain, V_ulPowerT_ThresholdGain;

	uchar8 V_uci, V_ucDerictionFlag_A, V_ucDerictionFlag_R;

	/**************取功率阀值数据(XXX.XXXw HEX)***********************/
	V_ulPowerT_ThresholdGain = SF_PowerThresholdGain_MeterIC();
	V_ulPowerThresholdGain = V_ulPowerT_ThresholdGain / 3;
	/********功率原始值读取*********/
	SF_Power_MeterIC(pStr_VARREGTYPE);
	/************总功率数据计算、灭零和坐标轴显示***************/
	V_ucPowerDeriction = GStr_PowerData.Deriction;		/*转存原有功率方向数据*/

	if ( ( (GStr_HEX_VARREGTYPE.VRmsVRegHEX_ABC[C_offA] == 0) || ( GStr_HEX_VARREGTYPE.VRmsIRegHEX_ABC[C_offA] == 0) )
      && ( (GStr_HEX_VARREGTYPE.VRmsVRegHEX_ABC[C_offB] == 0) || ( GStr_HEX_VARREGTYPE.VRmsIRegHEX_ABC[C_offB] == 0) )
      && ( (GStr_HEX_VARREGTYPE.VRmsVRegHEX_ABC[C_offC] == 0) || ( GStr_HEX_VARREGTYPE.VRmsIRegHEX_ABC[C_offC] == 0) ) )
	{
		GStr_PowerData.ActivePower_TABC[C_offTT] = 0;	/*当各分相均出现失压或者失流时，总有功功率和总无功功率灭零*/
		GStr_PowerData.ReativePower_TABC[C_offTT] = 0;
	}
	else
	{
		GStr_PowerData.ActivePower_TABC[C_offTT] = SF_CountRealPower_MeterIC(pStr_VARREGTYPE->WATTReg[0], C_PowerFlag_T);	/*总有功功率计算*/
		GStr_PowerData.ReativePower_TABC[C_offTT] = SF_CountRealPower_MeterIC(pStr_VARREGTYPE->VARReg[0], C_PowerFlag_T);	/*总无功功率计算*/
		/*********功率数据阀值判断，只对大于功率阀值的功率方向进行更新，功率数据不进行灭零处理******/
		/******总有功功率数据方向获取******/
		if (SF_ABS(GStr_PowerData.ActivePower_TABC[C_offTT]) > V_ulPowerT_ThresholdGain)   
		{
			if (GStr_PowerData.ActivePower_TABC[C_offTT] < 0)
			{
				V_ucPowerDeriction |= C_ActiveEnergyT_Minus;
			}
			else
			{
				V_ucPowerDeriction &= C_ActiveEnergyT_Plus;
			}
		}

		/******总无功功率数据方向获取******/
		if (SF_ABS(GStr_PowerData.ReativePower_TABC[C_offTT]) > V_ulPowerT_ThresholdGain)
		{
			if (GStr_PowerData.ReativePower_TABC[C_offTT] < 0)
			{
				V_ucPowerDeriction |= C_ReactiveEnergyT_Minus;
			}
			else
			{
				V_ucPowerDeriction &= C_ReactiveEnergyT_Plus;
			}
		}
	}

	V_usStateLen = CLMeter_Work_State1;					/*置电表运行状态字1标志位*/
	InF_Read_Data(CMeter_Work_State1, V_ucStateBuffer, &V_usStateLen, &V_usDataEncode);
	PF_Buffer2ToUshort16(V_ucStateBuffer, &V_usState0);
	if ( (V_ucPowerDeriction & 0x88) == C_PQsign2)
	{
		SF_Display_MeterIC(C_Q2Sign, C_AlwaysDisplay);	/*显示第二象限*/
		V_usState0 |= C_PTminus;
		V_usState0 &= C_QTplus;
	}
	else if ( (V_ucPowerDeriction & 0x88) == C_PQsign3)
	{
		SF_Display_MeterIC(C_Q3Sign, C_AlwaysDisplay);	/*显示第三象限*/
		V_usState0 |= C_PTminus;
		V_usState0 |= C_QTminus;

	}
	else if ( (V_ucPowerDeriction & 0x88) == C_PQsign4)
	{
		SF_Display_MeterIC(C_Q4Sign, C_AlwaysDisplay);	/*显示第四象限*/
		V_usState0 &= C_PTplus;
		V_usState0 |= C_QTminus;
	}
	else
	{
		SF_Display_MeterIC(C_Q1Sign, C_AlwaysDisplay);	/*显示第一象限*/
		V_usState0 &= C_PTplus;
		V_usState0 &= C_QTplus;
	}
	SF_ClearUcharArray(V_ucStateBuffer, 2);
	PF_Ushort16ToBuffer2(V_ucStateBuffer, &V_usState0);
	InF_Write_Data(C_Msg_MeterIC, CMeter_Work_State1, V_ucStateBuffer, CLMeter_Work_State1, C_W_SafeFlag);

	for (V_uci = 0; V_uci < 3; V_uci++)
	{
		V_ucDerictionFlag_A = (0x01 << V_uci);
		V_ucDerictionFlag_R = (0x10 << V_uci);

		if ( (GStr_HEX_VARREGTYPE.VRmsVRegHEX_ABC[V_uci] == 0) || ( (GStr_HEX_VARREGTYPE.VRmsIRegHEX_ABC[V_uci]) == 0) )
		{
			GStr_PowerData.ActivePower_TABC[C_offTA + V_uci] = 0;
			GStr_PowerData.ReativePower_TABC[C_offTA + V_uci] = 0;
		}
		else
		{
			GStr_PowerData.ActivePower_TABC[C_offTA + V_uci] = SF_CountRealPower_MeterIC(pStr_VARREGTYPE->WATTReg[C_offTA + V_uci], C_PowerFlag_ABC);
			GStr_PowerData.ReativePower_TABC[C_offTA + V_uci] = SF_CountRealPower_MeterIC(pStr_VARREGTYPE->VARReg[C_offTA + V_uci], C_PowerFlag_ABC);
			/*********功率数据阀值判断，只对大于功率阀值的功率方向进行更新，功率数据不进行灭零处理******/
			/*******有功功率A相方向获取********/
			if (SF_ABS(GStr_PowerData.ActivePower_TABC[C_offTA + V_uci]) > V_ulPowerThresholdGain)
			{
				if (GStr_PowerData.ActivePower_TABC[C_offTA + V_uci] < 0)
				{
					V_ucPowerDeriction |= V_ucDerictionFlag_A;
				}
				else
				{
					V_ucPowerDeriction &= (~V_ucDerictionFlag_A);
				}
			}

			/*******无功功率A相方向获取********/
			if (SF_ABS(GStr_PowerData.ReativePower_TABC[C_offTA + V_uci]) > V_ulPowerThresholdGain)
			{
				if (GStr_PowerData.ReativePower_TABC[C_offTA + V_uci] < 0)
				{
					V_ucPowerDeriction |= V_ucDerictionFlag_R;
				}
				else
				{
					V_ucPowerDeriction &= (~V_ucDerictionFlag_R);
				}
			}
		}
	}
	if (SF_PhaseSequenceGain_MeterIC() == C_3P3W)			/*三相三线直接赋值B相有、无功功率方向为正*/
	{
		V_ucPowerDeriction &= 0xDD;
	}
	GStr_PowerData.Deriction = V_ucPowerDeriction;			/*将已配置好的本时刻功率方向转存至需量用功率数据结构体*/
	SF_Cal1minPowerSum(&GStr_PowerAdd, &GStr_PowerData);
	InF_PowerChanggeInitDemand(&GStr_PowerData);
}

/*******************************************************************************
函数原型: void SF_PowerDataTidy_MeterIC(void)
功能描述: 本部分需要将所有瞬时量原始数据经过计算转换成符合数据层变量要求的数据格式，然后写入数据层
输入参数: GStr_HEX_VARREGTYPE结构体中的所有HEX码数据
          Str_DataProcess数组中的数据层地址
输出参数: 无
返回参数: 无
调用位置: 
备    注: 所有计量数据整理、换算，完成上传数据层
*******************************************************************************/
void SF_PowerDataTidy_MeterIC(void)
{
	uchar8 V_uci, V_ucData[C_FourByteLen];
	Str_VARREGTYPE_Type Str_VARREGTYPE;													/*瞬时量原始值存储结构体*/
	Str_RealAngleData_Type Str_RealAngleData;											/*相角真实数据存储结构体*/

	SF_Variable_MeterIC(&Str_VARREGTYPE);												/*读取出功率因数、频率、相角、温度、电压夹角数据原始值*/
	SF_Urms_MeterIC(&Str_VARREGTYPE);													/*读取电压数据原始值*/
	SF_Irms_MeterIC(&Str_VARREGTYPE);													/*读取电流数据原始值*/
	SF_CurrentDatatoHEX_MeterIC(&Str_VARREGTYPE);										/*计算电流数据之后转换成HEX*/
	if (GV_C_SlipCurrent__Flag == 0)													/*电流滑差*/
	{
		SF_SlipCurrent();
	}
	SF_VoltageDatatoHEX_MeterIC(&Str_VARREGTYPE);										/*计算电压数据之后转换成HEX*/
	SF_DemandPowerDataTidy_MeterIC(&Str_VARREGTYPE);									/*计算功率数据之后HEX传送给需量模块*/
	SF_CurrentSignDisplay();															/*电流符号显示*/
	SF_PowerDatatoHEX_MeterIC(&Str_VARREGTYPE);											/*功率数据计算之后转换成HEX*/
	SF_PowerFactorDatatoHEX_MeterIC(&Str_VARREGTYPE);									/*功率因数数据计算之后转换成HEX*/
	SF_FrequencyDatatoHEX_MeterIC(&Str_VARREGTYPE);										/*电网频率数据计算之后转换成HEX*/
	SF_VoltagePhaseAngleDatatoHEX_MeterIC(&Str_VARREGTYPE, &Str_RealAngleData);			/*电压相角数据计算之后转换成HEX*/
	SF_PhaseAngleDatatoHEX_MeterIC(&Str_VARREGTYPE, &Str_RealAngleData);				/*功率因数角数据计算之后转换成HEX*/
	SF_CurrentPhaseAngleDatatoHEX_MeterIC(&Str_RealAngleData);							/*电流相角数据计算之后转换成HEX*/
/*	SF_TemperatureDatatoHEX_MeterIC();*/												/*温度数据计算之后转换成HEX*/
	SF_WorkingState();																	/*电表运行状态字2更新*/
	/*****************更新数据层*******************/
	for (V_uci = 0; V_uci < C_InstantNum; V_uci++)
	{
		if ( (V_uci == C_offCPhaseA_Curr) || (V_uci == C_offCPhaseB_Curr) || (V_uci == C_offCPhaseC_Curr) ) /*3位小数电流不写入数据层，数据层只存4位小数*/
		{
			continue;
		}
		if (V_uci < C_fourLenthNum) 
		{
			PF_Ulong32ToBufferX(V_ucData, (ulong32 *)(&GStr_HEX_VARREGTYPE.ActivePowerHEX_TABC[0] + V_uci), C_FourByteLen);
			InF_Write_Data(C_Msg_MeterIC, Str_DataProcess[V_uci].C_InstantOAD, V_ucData, Str_DataProcess[V_uci].CL_InstantOAD, C_W_SafeFlag);
		}
		else 
		{
			PF_Ushort16ToBuffer2(V_ucData, (&GStr_HEX_VARREGTYPE.VRmsVRegHEX_ABC[0] + V_uci - C_fourLenthNum) );
			InF_Write_Data(C_Msg_MeterIC, Str_DataProcess[V_uci].C_InstantOAD, V_ucData, Str_DataProcess[V_uci].CL_InstantOAD, C_W_SafeFlag);
		}
	}
	GV_ucEnergyLock = C_EnergyUnlock;	/*解锁电能读取*/
}

/*******************************************************************************
函数原型: void SF_PowerDatatoHEX_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE)
功能描述: 将功率数据根据数据层数据格式转换成HEX
输入参数: Str_VARREGTYPE_Type *pStr_VARREGTYPE:原始值指针
         GStr_PowerData结构体(此结构体用于需量用功率数据传递)中的功率数据
         Str_VARREGTYPE结构体中的视在功率原始值
输出参数: GStr_HEX_VARREGTYPE结构体中的有功、无功和视在功率HEX码数据XXX.XXXXkw 三字节数据 多余补零 首位符号位 (0)正 (1)负 注:视在功率首位符号位与有功功率相同
返回参数: 无
调用位置: 
备    注: 有无功功率从需量用功率数据结构体中取数据，然后去掉两位小数，更新数据层；视在功率则需要从原始数据计算
*******************************************************************************/
void SF_PowerDatatoHEX_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE)
{
	long32 V_lData = 0;
	uchar8 V_uci;
	uchar8 V_ucPowerDataFlag;
	
	/****************有功、无功功率数据:由需量用功率数据XXXXX.XXXw转换成XXXXXXX.Xw*********************/
	for (V_uci = 0; V_uci < 4; V_uci++)
	{
		GStr_HEX_VARREGTYPE.ActivePowerHEX_TABC[V_uci] = GStr_PowerData.ActivePower_TABC[V_uci] / 100;
		GStr_HEX_VARREGTYPE.ReativePowerHEX_TABC[V_uci] = GStr_PowerData.ReativePower_TABC[V_uci] / 100;
	}

	/**************************视在功率数据计算:HEX 四字节 XXXX.XXXX kVA****************************/

	for (V_uci = 0; V_uci < 4; V_uci++)
	{
		if ( (V_uci == C_offTB) && ( SF_PhaseSequenceGain_MeterIC( ) == C_3P3W ) )	/*三相三线B相视在功率为零*/
		{
			GStr_HEX_VARREGTYPE.ApparentPowerHEX_TABC[C_offTB] = 0;
		}
		else
		{
			if (V_uci == C_offTT)
			{
				V_ucPowerDataFlag = C_PowerFlag_T;
			}
			else
			{
				V_ucPowerDataFlag = C_PowerFlag_ABC;
			}
			V_lData = SF_CountRealPower_MeterIC(pStr_VARREGTYPE->VAReg[V_uci], V_ucPowerDataFlag);
			GStr_HEX_VARREGTYPE.ApparentPowerHEX_TABC[V_uci] = V_lData / 100;

			if (V_uci == C_offTT)	/*T*/
			{
				if ( ( (GStr_HEX_VARREGTYPE.VRmsVRegHEX_ABC[C_offA] == 0) || ( GStr_HEX_VARREGTYPE.VRmsIRegHEX_ABC[C_offA] == 0) )
                  && ( (GStr_HEX_VARREGTYPE.VRmsVRegHEX_ABC[C_offB] == 0) || ( GStr_HEX_VARREGTYPE.VRmsIRegHEX_ABC[C_offB] == 0) )
                  && ( (GStr_HEX_VARREGTYPE.VRmsVRegHEX_ABC[C_offC] == 0) || ( GStr_HEX_VARREGTYPE.VRmsIRegHEX_ABC[C_offC] == 0) ) )
				{
					GStr_HEX_VARREGTYPE.ApparentPowerHEX_TABC[V_uci] = 0;
				}
			}
			else				/*ABC*/
			{
				if ( (GStr_HEX_VARREGTYPE.VRmsVRegHEX_ABC[V_uci - C_offTA] == 0) || ( GStr_HEX_VARREGTYPE.VRmsIRegHEX_ABC[V_uci - C_offTA] == 0) )
				{
					GStr_HEX_VARREGTYPE.ApparentPowerHEX_TABC[V_uci] = 0;
				}
			}
		}

		/*符号根据有功功率符号*/
		if ( (GStr_HEX_VARREGTYPE.ActivePowerHEX_TABC[V_uci] < 0) && (GStr_HEX_VARREGTYPE.ApparentPowerHEX_TABC[V_uci] > 0)
          || (GStr_HEX_VARREGTYPE.ActivePowerHEX_TABC[V_uci] > 0) && (GStr_HEX_VARREGTYPE.ApparentPowerHEX_TABC[V_uci] < 0) )
		{
			GStr_HEX_VARREGTYPE.ApparentPowerHEX_TABC[V_uci] = 0 - GStr_HEX_VARREGTYPE.ApparentPowerHEX_TABC[V_uci];
		}
	}
}

/*******************************************************************************
函数原型: void SF_PowerFactorDatatoHEX_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE)
功能描述: 将功率因数数据，根据数据层数据格式转换
输入参数: Str_VARREGTYPE功率因数原始数据
输出参数: GStr_HEX_VARREGTYPE结构体中的功率因数数据 HEX 2字节 X.XXX 有符号数
返回参数: 无
调用位置: 
备    注: 功率因数有正负；如果电压或者电流断相，则此相的功率因数默认为1
*******************************************************************************/
void SF_PowerFactorDatatoHEX_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE)
{
	uchar8 V_uci, V_ucData[8], V_ucHEXData[2], V_ucMeaLen, V_ucHexLen;
	ulong32 V_ulPowerFactorData;
	ulong64 V_ullPowerFactorUsData;
	uchar8 V_ucDeriction[4] = {C_ActiveEnergyT_Minus, C_ActiveEnergyA_Minus, C_ActiveEnergyB_Minus, C_ActiveEnergyC_Minus};
	V_ucMeaLen = C_MeaDataLen;
	V_ucHexLen = C_PowerFactorHexLen;

	for (V_uci = 0; V_uci < 4; V_uci++)
	{
		SF_ClearUcharArray(V_ucData, 8);
		SF_ClearUcharArray(V_ucHEXData, 2);
		
		if ( (V_uci == C_offTB) && (SF_PhaseSequenceGain_MeterIC() == C_3P3W) )	/*三相三线B相功率因数为0*/
		{
			GStr_HEX_VARREGTYPE.PowerFactorHEX_TABC[C_offTB] = 0;
		}
		else
		{
			if (pStr_VARREGTYPE->PfReg[V_uci] & 0x00800000)
			{
				V_ulPowerFactorData = 0 - pStr_VARREGTYPE->PfReg[V_uci];
				V_ulPowerFactorData &= 0x00FFFFFF;
			}
			else
			{
				V_ulPowerFactorData = pStr_VARREGTYPE->PfReg[V_uci];
			}
			PF_Ulong32ToBufferX(V_ucData, &V_ulPowerFactorData, V_ucMeaLen);
			PF_Buffer8ToUlong64(V_ucData, &V_ullPowerFactorUsData, V_ucMeaLen);
			V_ullPowerFactorUsData = V_ullPowerFactorUsData * 1000;
			V_ullPowerFactorUsData >>= 23;
			if (V_ullPowerFactorUsData >= C_PowerFactorThreshold)		/*大于等于0.999的功率因数统一为1.000*/
			{
				V_ullPowerFactorUsData = C_PowerFactor;
			}
			if (GStr_HEX_VARREGTYPE.ApparentPowerHEX_TABC[V_uci] == 0)	/*视在功率为零，则对应相功率因数默认为1*/
			{
				V_ullPowerFactorUsData = C_PowerFactor;
			}
			SF_ClearUcharArray(V_ucData, 8);
			SF_ClearUcharArray(V_ucHEXData, 2);
			V_ulPowerFactorData = 0;
			PF_Ulong64ToBuffer8(V_ucData, &V_ullPowerFactorUsData, V_ucHexLen);
			PF_BufferXToUlong32(V_ucData, &V_ulPowerFactorData, V_ucHexLen);
			GStr_HEX_VARREGTYPE.PowerFactorHEX_TABC[V_uci] = V_ulPowerFactorData;

			/*功率因数符号与有功功率同步*/
			if (GStr_PowerData.Deriction & V_ucDeriction[V_uci])
			{
				GStr_HEX_VARREGTYPE.PowerFactorHEX_TABC[V_uci] = 0 - GStr_HEX_VARREGTYPE.PowerFactorHEX_TABC[V_uci];
			}
		}
	}
}

/*******************************************************************************
函数原型: void SF_VoltageDatatoHEX_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE)
功能描述: 将电压数据根据数据层数据格式转换成HEX码，并根据电压阀值进行灭零
输入参数: Str_VARREGTYPE_Type *pStr_VARREGTYPE:原始值结构体指针
输出参数: GStr_HEX_VARREGTYPE结构体中的电压数据 HEX 2字节 XXX.X 无符号
返回参数: 无
调用位置: 
备    注:  
*******************************************************************************/
void SF_VoltageDatatoHEX_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE)
{
	uchar8 V_uci;
	uchar8 V_ucDisplayFlag;
	ulong32 V_ulVoltageData, V_ulVoltageDataTemp;
	uchar8 V_ucSign[3] = {C_UaSign, C_UbSign, C_UcSign};

	for (V_uci = 0; V_uci < 3; V_uci++)
	{
		V_ulVoltageData = pStr_VARREGTYPE->VRmsVReg[V_uci] & 0x00FFFFFF;
		V_ucDisplayFlag = C_AlwaysDisplay;
		V_ulVoltageData *= 10;
		V_ulVoltageData >>= 13;
		if ( (V_uci == C_offB) && (SF_PhaseSequenceGain_MeterIC() == C_3P3W) )	/*三相三线B相电压为零*/
		{
			V_ulVoltageData = 0;
			V_ucDisplayFlag = C_NotDisplay;
		}
		V_ulVoltageDataTemp = C_VoltageThreshold;
		if (C_OK == InF_ValtageType() )											/*220V\380V*/
		{
			V_ulVoltageDataTemp = C_VoltageThreshold220;
		}
		if (V_ulVoltageData < V_ulVoltageDataTemp)								/*电压数据灭零*/
		{
			V_ulVoltageData = 0;
			V_ucDisplayFlag = C_NotDisplay;
		}
		/*******电压符号显示*******/
		SF_Display_MeterIC(V_ucSign[V_uci], V_ucDisplayFlag);

		GStr_HEX_VARREGTYPE.VRmsVRegHEX_ABC[V_uci] = V_ulVoltageData;
	}
}

/*******************************************************************************
函数原型: void SF_CurrentDatatoHEX_MeterIC_Part(ulong32 *pV_ulVARREGTYPE_VRmsIReg, long32 *pV_lHEX_VARREGTYPE_VRmsILSBRegHEX, long32 *pV_lHEX_VARREGTYPE_VRmsIRegHEX, ulong32 V_ulN, uchar8 V_ucFlag)
功能描述: 将电流数据根据数据层数据格式转换成HEX码，并根据电流阀值进行灭零
输入参数: ulong32 *pV_ulVARREGTYPE_VRmsIReg：电流原始值
         long32 *pV_lHEX_VARREGTYPE_VRmsILSBRegHEX：4位小数电流指针
         long32 *pV_lHEX_VARREGTYPE_VRmsIRegHEX：3位小数电流指针
         ulong32 V_ulN：电流系数
         uchar8 V_ucFlag：分相合相标志
输出参数: GStr_HEX_VARREGTYPE结构体中电流数据 HEX XXXXX.XXXA 4字节 和 HEX XXXX.XXXXA 4字节 
返回参数: 无
调用位置: 
备    注:  
*******************************************************************************/
void SF_CurrentDatatoHEX_MeterIC_Part(ulong32 *pV_ulVARREGTYPE_VRmsIReg, long32 *pV_lHEX_VARREGTYPE_VRmsILSBRegHEX, long32 *pV_lHEX_VARREGTYPE_VRmsIRegHEX, ulong32 V_ulN, uchar8 V_ucFlag)
{
	uchar8 V_ucData[8];
	ulong32 V_ulCurrentData, V_ulCurrentThresholdData;					/*zlj此时电流还没有符号，在后面才进行符号处理*/
	ulong64 V_ullCurrentData;
	/**********************************/
	V_ulCurrentThresholdData = SF_CurrentThresholdGain_MeterIC();		/*读取电流阀值*/

	SF_ClearUcharArray(V_ucData, 8);
	PF_Ulong32ToBufferX(V_ucData, pV_ulVARREGTYPE_VRmsIReg, 4);
	PF_Buffer8ToUlong64(V_ucData, &V_ullCurrentData, 8);
	V_ullCurrentData &= 0x0000000000FFFFFF;
	V_ullCurrentData *= 125;
	V_ullCurrentData >>= 2;
	V_ullCurrentData *= 25;
	V_ullCurrentData /= V_ulN;
	V_ullCurrentData >>= 5;
	if (V_ucFlag != 0)													/*分相电流多移一位*/
	{
		V_ullCurrentData >>= 1;
	}
	SF_ClearUcharArray(V_ucData, 8);
	PF_Ulong64ToBuffer8(V_ucData, &V_ullCurrentData, 8);
	PF_BufferXToUlong32(V_ucData, &V_ulCurrentData, 4);
	if (V_ulCurrentData <= V_ulCurrentThresholdData)
	{
		V_ulCurrentData = 0;
	}

	if (V_ucFlag != 0)													/*A/B/C相才需要计算4位小数的电流*/
	{
		*pV_lHEX_VARREGTYPE_VRmsILSBRegHEX = (long32)V_ulCurrentData;
	}
/********************计算3位小数电流*************************/
	V_ulCurrentData = V_ulCurrentData / 10;
	*pV_lHEX_VARREGTYPE_VRmsIRegHEX = (long32)V_ulCurrentData;
}

/*******************************************************************************
函数原型: void SF_CurrentDatatoHEX_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE)
功能描述: 计算电流数据
输入参数: Str_VARREGTYPE_Type *pStr_VARREGTYPE：瞬时量原始值指针
输出参数: 无
返回参数: 无
调用位置: 
备    注:  
*******************************************************************************/
void SF_CurrentDatatoHEX_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE)
{
	uchar8 V_uci, V_ucIb;   /*,V_Data[4],V_usData[8]*/
	ushort16 V_usLen, V_usDataEncode = 0;
	long32 V_lCurrentData;	/*,V_CurrentThresholdData*/
	ulong32 V_ulN;
	/*******************根据电表电流规格，取电流系数********************/
	V_usLen = CLCurrent_Type;
	InF_Read_Data(CCurrent_Type, &V_ucIb, &V_usLen, &V_usDataEncode);
	switch (V_ucIb & 0x0F)
	{
		case C_Ib0_3A:
		{
			V_ulN = C_N0_3A;
		}break;		/*当电流采样电压为50mA时，对应的有效值为60，V_ulN=60/Ib*/

		case C_Ib1A:
		{
			V_ulN = C_N1A;
		}break;		/*当电流采样电压为25mA左右时，那么对应的有效值就是60/2=30,V_ulN=30/Ib*/

		case C_Ib1_5A:
		{
			V_ulN = C_N1_5A;
		}break;		/*这里所有的V_N都做乘10处理，不明白为什么乘10就自己算一下就知道为什么乘10了 */

		case C_Ib5A	:
		{
			V_ulN = C_N5A;
		}break;
	
		case C_Ib10A:
		{
			V_ulN = C_N10A;
		}break;

		case C_Ib15A:
		{
			V_ulN = C_N15A;
		}break;

		case C_Ib20A:
		{
			V_ulN = C_N20A;
		}break;

		case C_Ib30A:
		{
			V_ulN = C_N30A;
		}break;

		default:
		{
			V_ulN = C_N30A;
		}break;
	}

	/******************计算电流数据*********************/
	for (V_uci = 0; V_uci < 3; V_uci++)
	{
		if ( (V_uci == C_offB) && (SF_PhaseSequenceGain_MeterIC() == C_3P3W) )
		{
			GStr_HEX_VARREGTYPE.VRmsIRegHEX_ABC[C_offB] = 0;
		}
		else
		{
			SF_CurrentDatatoHEX_MeterIC_Part(&pStr_VARREGTYPE->VRmsIReg[V_uci], &GStr_HEX_VARREGTYPE.VRmsILSBRegHEX_ABC[V_uci], &GStr_HEX_VARREGTYPE.VRmsIRegHEX_ABC[V_uci], V_ulN, V_uci + 1);
		}
	}

/*三相电流矢量和*/
	SF_CurrentDatatoHEX_MeterIC_Part(&pStr_VARREGTYPE->IRmsN0, &V_lCurrentData, &GStr_HEX_VARREGTYPE.IRmsN0_HEX, V_ulN, 0);
/*零线电流*/
	SF_CurrentDatatoHEX_MeterIC_Part(&pStr_VARREGTYPE->IRmsNOSample, &V_lCurrentData, &GStr_HEX_VARREGTYPE.IRmsNOSample_HEX, V_ulN, 1);
	if (SF_PhaseSequenceGain_MeterIC() == C_3P3W)	/*三相三线无零线电流、三相三线矢量和*/
	{
		GStr_HEX_VARREGTYPE.IRmsN0_HEX = 0;
		GStr_HEX_VARREGTYPE.IRmsNOSample_HEX = 0;
	}
	else
	{
		if ( (GStr_HEX_VARREGTYPE.VRmsILSBRegHEX_ABC[C_offA] == 0)
          && (GStr_HEX_VARREGTYPE.VRmsILSBRegHEX_ABC[C_offB] == 0)
          && (GStr_HEX_VARREGTYPE.VRmsILSBRegHEX_ABC[C_offC] == 0) )
		{
			GStr_HEX_VARREGTYPE.IRmsN0_HEX = 0;
		}
	}
}

/*******************************************************************************
函数原型: void SF_SlipCurrent(ulong32 *pV_ulSlipCurrentBuff, long32 *pV_lHEX_VARREGTYPE_VRmsILSBRegHEX, long32 *pV_lHEX_VARREGTYPE_VRmsIRegHEX, ulong32 V_ulCurrentThreshold)
功能描述: 根据已经处理好的电流数据，进行电流滑差处理，此参数
输入参数: ulong32 *pV_ulSlipCurrentBuff:滑差缓存；
         long32 *pV_lHEX_VARREGTYPE_VRmsILSBRegHEX：4字节电流值
         long32 *pV_lHEX_VARREGTYPE_VRmsIRegHEX：3字节电流值
         ulong32 V_ulCurrentThreshold：电流阀值
输出参数: 无
返回参数: 无
调用位置: 
备    注: 此滑差处理函数放置在电流数据装换HEX之后，符号显示之前 
*******************************************************************************/
void SF_SlipCurrent_OnePhase(ulong32 *pV_ulSlipCurrentBuff, long32 *pV_lHEX_VARREGTYPE_VRmsILSBRegHEX, long32 *pV_lHEX_VARREGTYPE_VRmsIRegHEX, ulong32 V_ulCurrentThreshold)
{
	pV_ulSlipCurrentBuff[2] = pV_ulSlipCurrentBuff[1];
	pV_ulSlipCurrentBuff[1] = pV_ulSlipCurrentBuff[0];
	pV_ulSlipCurrentBuff[0] = *pV_lHEX_VARREGTYPE_VRmsILSBRegHEX;
	if ( (ulong32)*pV_lHEX_VARREGTYPE_VRmsILSBRegHEX < V_ulCurrentThreshold)     /*此时电流还没有赋值符号*/
	{
		if ( (pV_ulSlipCurrentBuff[2] == 0) || (pV_ulSlipCurrentBuff[1] == 0) || (pV_ulSlipCurrentBuff[0] == 0) )
		{
			*pV_lHEX_VARREGTYPE_VRmsILSBRegHEX = 0;
			*pV_lHEX_VARREGTYPE_VRmsIRegHEX = 0;
		}
	}
}

/*******************************************************************************
函数原型: void SF_SlipCurrent(void)
功能描述: 电流滑差
输入参数: 无
输出参数: 无
返回参数: 无
调用位置: 
备    注:  
*******************************************************************************/
void SF_SlipCurrent(void)
{
	uchar8 V_uci;
	ulong32 V_ulCurrentThresholdData;

	V_ulCurrentThresholdData = SF_CurrentThresholdGain_MeterIC();
	V_ulCurrentThresholdData *= 33;
	V_ulCurrentThresholdData /= 10;
	for (V_uci = 0; V_uci < 3; V_uci++)
	{
		/******ABC相电流滑差*****/
		SF_SlipCurrent_OnePhase(&GV_ulSlipCurrentBuff[V_uci][0], &GStr_HEX_VARREGTYPE.VRmsILSBRegHEX_ABC[V_uci], &GStr_HEX_VARREGTYPE.VRmsIRegHEX_ABC[V_uci], V_ulCurrentThresholdData);
	}
}

/*******************************************************************************
函数原型: void SF_CurrentSignDisplay(void)
功能描述: 根据已经处理好的电流数据，进行电流符号显示
输入参数: GStr_HEX_VARREGTYPE结构体中的电流数据
         GStr_PowerData.Deriction结构体中的功率方向数据
输出参数: GStr_HEX_VARREGTYPE结构体中的电流数据
返回参数: 无
调用位置: 
备    注:  
*******************************************************************************/
void SF_CurrentSignDisplay(void)
{
	uchar8 V_ucDisplayFlag, V_uci;
	uchar8 V_ucDisFlag;
	uchar8 V_ucReverse[3] = {C_Reverse_Ia, C_Reverse_Ib, C_Reverse_Ic};
	uchar8 V_ucSign[3] = {C_IaSign, C_IbSign, C_IcSign};
	uchar8 V_ucNegativeSign[3] = {C_IaNegativeSign, C_IbNegativeSign ,C_IcNegativeSign};

	for (V_uci = 0; V_uci < 3; V_uci++)
	{
		if (GStr_HEX_VARREGTYPE.VRmsILSBRegHEX_ABC[V_uci] == 0)
		{
			V_ucDisplayFlag = C_NotDisplay;
		}
		else if ( (V_uci == C_offB) && (SF_PhaseSequenceGain_MeterIC() == C_3P3W) )
		{
			V_ucDisplayFlag = C_NotDisplay;
		}
		else
		{
			V_ucDisplayFlag = C_AlwaysDisplay;
		}
/************************电流符号显示************************/
		V_ucDisFlag = V_ucDisplayFlag;

		if ( (GStr_PowerData.Deriction & V_ucReverse[V_uci]) != 0)/*新协议有功功率为0需带方向*/
		{
			if (GStr_HEX_VARREGTYPE.VRmsILSBRegHEX_ABC[V_uci] == 0)
			{/*电流为0不显示"-"*/
				V_ucDisFlag = C_NotDisplay;
			}
			GStr_HEX_VARREGTYPE.VRmsILSBRegHEX_ABC[V_uci] = 0 - GStr_HEX_VARREGTYPE.VRmsILSBRegHEX_ABC[V_uci];
			GStr_HEX_VARREGTYPE.VRmsIRegHEX_ABC[V_uci] = 0 - GStr_HEX_VARREGTYPE.VRmsIRegHEX_ABC[V_uci];
		}
		else if (V_ucDisplayFlag != C_NotDisplay)
		{
			V_ucDisFlag = C_NotDisplay;
		}
		SF_Display_MeterIC(V_ucSign[V_uci], V_ucDisplayFlag);
		SF_Display_MeterIC(V_ucNegativeSign[V_uci], V_ucDisFlag);
	}
}

/*******************************************************************************
函数原型: void SF_FrequencyDatatoHEX_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE)
功能描述: 将频率数据转换成数据层数据格式
输入参数: Str_VARREGTYPE.FREQUENCY电网频率原始数据
输出参数: GStr_HEX_VARREGTYPE结构体中的电网频率数据 HEX 2字节 XX.XXHz 无符号
返回参数: 无
调用位置: 
备    注: 当三相电压仅为零时，电网频率为零 
*******************************************************************************/
void SF_FrequencyDatatoHEX_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE)
{
	ulong32 V_ulFrequencyData;

	V_ulFrequencyData = pStr_VARREGTYPE->FREQUENCY;
	V_ulFrequencyData *= 25;
	V_ulFrequencyData >>= 11;
	if ( (V_ulFrequencyData >= C_FrequencyThreshold) && (V_ulFrequencyData <= C_FrequencyThreshold + 2) )
	{
		V_ulFrequencyData = C_FrequencyData;
	}
	if ( (GStr_HEX_VARREGTYPE.VRmsVRegHEX_ABC[C_offA] == 0) && (GStr_HEX_VARREGTYPE.VRmsVRegHEX_ABC[C_offB] == 0) && (GStr_HEX_VARREGTYPE.VRmsVRegHEX_ABC[C_offC] == 0) )
	{
		V_ulFrequencyData = 0;	/*三相电压为零，频率为零*/
	}
	GStr_HEX_VARREGTYPE.FREQUENCY_HEX = V_ulFrequencyData;
}

/*******************************************************************************
函数原型: ulong32 SF_AngleDataSUM_MeterIC(ulong32 V_ulData)
功能描述: 将相角数据从寄存器数据装换成真实数据0~360.0°保留一位小数
输入参数: ulong32 V_ulData相角数据原始值
输出参数: 无
返回参数: 返回计算好的相角数据0~360.0°
调用位置: 
备    注: 
*******************************************************************************/
ulong32 SF_AngleDataSUM_MeterIC(ulong32 V_ulData)
{
	if (V_ulData >= 0x00100000)
	{
		V_ulData = 0 - V_ulData;
		V_ulData &= 0x000FFFFF;
		V_ulData *= 225;				/*Pg=(θ/2^20)×180，这里留有一位小数，则需要乘10*/
		V_ulData >>= 17;
		V_ulData = 3600 - V_ulData;
		return V_ulData;
	}
	else
	{
		V_ulData *= 225;				/*Pg=(θ/2^20)×180，这里留有一位小数，则需要乘10*/
		V_ulData >>= 17;
		return V_ulData;
	}
}

/*******************************************************************************
函数原型: void SF_PhaseAngleDatatoHEX_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE, Str_RealAngleData_Type *pStr_RealAngleData)
功能描述: 将功率相角数据根据数据层数据格式转换成HEX码
输入参数: Str_VARREGTYPE中的电压相角和电流相角
输出参数: GStr_HEX_VARREGTYPE结构体中的功率相角 HEX XXX.X°2字节 无符号 0.0~360.0°
返回参数: 无
调用位置: 
备    注: 相角计算为通过7022E新算法计算，详见数据手册
*******************************************************************************/
void SF_PhaseAngleDatatoHEX_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE, Str_RealAngleData_Type *pStr_RealAngleData)
{
	uchar8 V_uci;
	for (V_uci = 0; V_uci < 3; V_uci++)
	{
		pStr_RealAngleData->YUIRealData_ABC[V_uci] = SF_AngleDataSUM_MeterIC(pStr_VARREGTYPE->YUIReg[V_uci]);
		
		/*********ABC相电压电流相角数据计算后转换成HEX**********/

		if ( ( GStr_HEX_VARREGTYPE.VRmsIRegHEX_ABC[V_uci] == 0 ) || (GStr_HEX_VARREGTYPE.VRmsVRegHEX_ABC[V_uci] == 0) || ( (V_uci == C_offB) && (SF_PhaseSequenceGain_MeterIC() == C_3P3W ) ) )  
		{
			pStr_RealAngleData->YUIRealData_ABC[V_uci] = 0;
		}


		if (pStr_RealAngleData->YUIRealData_ABC[V_uci] >= 3600)
		{
			pStr_RealAngleData->YUIRealData_ABC[V_uci] -= 3600;
		}
		GStr_HEX_VARREGTYPE.YUIRegHEX_ABC[V_uci] = pStr_RealAngleData->YUIRealData_ABC[V_uci];

	}
}

/*******************************************************************************
函数原型: void SF_VoltagePhaseAngleDatatoHEX_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE, Str_RealAngleData_Type *pStr_RealAngleData)
功能描述: 将电压相角数据转换成数据层数据格式、
输入参数: Str_VARREGTYPE电压相角数据
输出参数: GStr_HEX_VARREGTYPE结构体中电压相角 HEX XXX.X° 2字节 0.0~360.0°
返回参数: 无
调用位置: 
备    注: 电压相角为直接从计量芯片寄存器中读取的有效数据，计量芯片采用新算法。
*******************************************************************************/
void SF_VoltagePhaseAngleDatatoHEX_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE, Str_RealAngleData_Type *pStr_RealAngleData)
{
	uchar8 V_ucPhaseSequenceGain;

	V_ucPhaseSequenceGain = SF_PhaseSequenceGain_MeterIC();		/*取接线方式数据*/
	GStr_HEX_VARREGTYPE.YURegHEX_ABC[C_offA] = 0;
	pStr_RealAngleData->YURealData_ABC[C_offA] = 0;
	/*将寄存器读取出的相角数据，转换成0~360°的真实数据**///
	pStr_RealAngleData->YURealData_ABC[C_offB] = SF_AngleDataSUM_MeterIC(pStr_VARREGTYPE->YUReg[0]);
	pStr_RealAngleData->YURealData_ABC[C_offC] = SF_AngleDataSUM_MeterIC(pStr_VARREGTYPE->YUReg[1]);
	/******************B相电压相角计算********************/
	if (V_ucPhaseSequenceGain == C_3P3W)						/*三相三线情况下B相电压相角为零*/
	{
		pStr_RealAngleData->YURealData_ABC[C_offB] = 0;
	}
	else
	{
		if ( (GStr_HEX_VARREGTYPE.VRmsVRegHEX_ABC[C_offA] == 0) || (GStr_HEX_VARREGTYPE.VRmsVRegHEX_ABC[C_offB] == 0) )    /*如果A相电压等于0，则B相电压相角默认为120°*/
		{
			pStr_RealAngleData->YURealData_ABC[C_offB] = 1200;
		}
	}
	GStr_HEX_VARREGTYPE.YURegHEX_ABC[C_offB] = pStr_RealAngleData->YURealData_ABC[C_offB];

	/********************C相电压相角计算**************************/
	if (V_ucPhaseSequenceGain == C_3P3W)
	{
		if ( (GStr_HEX_VARREGTYPE.VRmsVRegHEX_ABC[C_offA]==0) || (GStr_HEX_VARREGTYPE.VRmsVRegHEX_ABC[C_offC] == 0) )
		{
			pStr_RealAngleData->YURealData_ABC[C_offC] = 3000;
		}
	}
	else
	{
		if ( (GStr_HEX_VARREGTYPE.VRmsVRegHEX_ABC[C_offA] == 0) || (GStr_HEX_VARREGTYPE.VRmsVRegHEX_ABC[C_offC] == 0) )
		{
			pStr_RealAngleData->YURealData_ABC[C_offC] = 2400;
		}
	}
	GStr_HEX_VARREGTYPE.YURegHEX_ABC[C_offC] = pStr_RealAngleData->YURealData_ABC[C_offC];
}

/*******************************************************************************
函数原型: void SF_ CurrentPhaseAngleDatatoHEX_MeterIC(Str_RealAngleData_Type *pStr_RealAngleData)
功能描述: 电流相角数据转换为HEX
输入参数: Str_VARREGTYPE结构体中的电流相角数据
输出参数: GStr_HEX_VARREGTYPE结构体中的电流相角数据 HEX XXX.X° 2字节 无符号 0.0°~360.0°
返回参数: 无
调用位置: 
备    注: 电流相角数据为寄存器读取的有效数据，计量芯片使用新算法。
*******************************************************************************/
void SF_CurrentPhaseAngleDatatoHEX_MeterIC(Str_RealAngleData_Type *pStr_RealAngleData)
{
	ulong32 V_ulIaAngleData, V_ulIbAngleData, V_ulIcAngleData;

	GStr_HEX_VARREGTYPE.YIRegHEX_ABC[C_offA] = 0;
	V_ulIaAngleData = pStr_RealAngleData->YUIRealData_ABC[C_offA];
	V_ulIbAngleData = pStr_RealAngleData->YURealData_ABC[C_offB] + pStr_RealAngleData->YUIRealData_ABC[C_offB];
	V_ulIcAngleData = pStr_RealAngleData->YURealData_ABC[C_offC] + pStr_RealAngleData->YUIRealData_ABC[C_offC];
	/*******************B相电流相角数据计算***************************/
	if (SF_PhaseSequenceGain_MeterIC() == C_3P3W)	/*三相三线情况下B相电流相角为零*/
	{
		pStr_RealAngleData->YIRealData_ABC[C_offB] = 0;
	}
	else
	{
		if ( (GStr_HEX_VARREGTYPE.VRmsVRegHEX_ABC[C_offA] == 0) || (GStr_HEX_VARREGTYPE.VRmsVRegHEX_ABC[C_offB] == 0) )
		{
			pStr_RealAngleData->YIRealData_ABC[C_offB] = 1200;
		}
		else
		{
			if (V_ulIbAngleData >= V_ulIaAngleData)	/*B相电流相角数据是否大于等于A相电流相角数据，否则进行加360°处理*/
			{
				pStr_RealAngleData->YIRealData_ABC[C_offB] = V_ulIbAngleData - V_ulIaAngleData;
			}
			else
			{
				pStr_RealAngleData->YIRealData_ABC[C_offB] = (V_ulIbAngleData + 3600) - V_ulIaAngleData;
			}
		}
		if (pStr_RealAngleData->YIRealData_ABC[C_offB] >= 3600)
		{
			pStr_RealAngleData->YIRealData_ABC[C_offB] -= 3600;
		}
	}
	GStr_HEX_VARREGTYPE.YIRegHEX_ABC[C_offB] = pStr_RealAngleData->YIRealData_ABC[C_offB];

	/********************C相电流相角数据计算***********************************/
	if ( (GStr_HEX_VARREGTYPE.VRmsVRegHEX_ABC[C_offA] == 0) || (GStr_HEX_VARREGTYPE.VRmsVRegHEX_ABC[C_offC] == 0) )
	{
		pStr_RealAngleData->YIRealData_ABC[C_offC] = 2400;
	}
	else
	{
		if (V_ulIcAngleData >= V_ulIaAngleData)		/*C相电流相角数据是否大于等于A相电流相角数据，否则进行加360°处理*/
		{
			pStr_RealAngleData->YIRealData_ABC[C_offC] = V_ulIcAngleData - V_ulIaAngleData;
		}
		else
		{
			pStr_RealAngleData->YIRealData_ABC[C_offC] = (V_ulIcAngleData + 3600) - V_ulIaAngleData;
		}
		if(pStr_RealAngleData->YIRealData_ABC[C_offC] >= 3600)
		{
			pStr_RealAngleData->YIRealData_ABC[C_offC] -= 3600;
		}
	}
	GStr_HEX_VARREGTYPE.YIRegHEX_ABC[C_offC] = pStr_RealAngleData->YIRealData_ABC[C_offC];
}

/*******************************************************************************
函数原型: void SF_ClearCalReg_MeterIC(void)
功能描述: 清除校表寄存器
输入参数: 无
输出参数: 无
返回参数: 无
调用位置: 
备    注: 电流相角数据为寄存器读取的有效数据，计量芯片使用新算法。
*******************************************************************************/
void SF_ClearCalReg_MeterIC(void)
{
	uchar8 V_ucAddr, V_ucWriteData[4];
	ushort16 V_usData;

	SF_ClearUcharArray(V_ucWriteData, 4);
	V_ucAddr = 0xC3;
	SF_WriteOneReg_MeterIC(V_ucWriteData, V_ucAddr, C_DataSafe);	/*0xC3地址写入000000,初始化计量芯片校表寄存器初值*/
	SF_Delay(C_DELAY25MS);
	SF_Delay(C_DELAY25MS);
	SF_ENSPIMode_MeterIC();
	SF_Eable_MeterIC();
	GV_ulCalDataChk0SUM = C_Check0RetData;
	GV_ulCalDataChk1SUM = C_Check1RetData;
	SF_ClearUcharArray(V_ucWriteData, 4);
	V_usData = C_ModeCfg_Data;										/*模式相关控制寄存器配置*/
	PF_Ushort16ToBuffer2(V_ucWriteData, &V_usData);
	SF_WriteOneReg_MeterIC(V_ucWriteData, C_ModeCfg_Reg, C_DataSafe);
	SF_TemRectify_MeterIC();
	SF_ClearUcharArray(V_ucWriteData, 4);
	V_usData = C_ModuleCFG_Data;									/*电路模块配置*/
	PF_Ushort16ToBuffer2(V_ucWriteData, &V_usData);
	SF_WriteOneReg_MeterIC(V_ucWriteData, C_ModuleCFG_Reg, C_DataSafe);
	/*SF_ClearUcharArray(V_ucWriteData, 4);*/
}

/*******************************************************************************
函数原型: void SF_Display_MeterIC(uchar8 V_ucData, uchar8 V_ucFlag)
功能描述: 显示计量模块负责的'Va' 'Vb' 'Vc' '-' 'Ia' '-' 'Ib' '-' 'Ic'
输入参数: uchar8 V_ucData显示不同内容:C_UaSign 显示Va;
                                     C_UbSign 显示Vb;
                                     C_UcSign 显示Vc;
                                     C_IaSign 显示Ia;
                                     C_IbSign 显示Ib;
                                     C_IcSign 显示Ic;
                                     C_IaNegativeSign 显示-;
                                     C_IbNegativeSign 显示-;
                                     C_IcNegativeSign 显示-;
          uchar8 V_ucFlag显示内容的不同状态:C_TwinkleDisplay 闪烁显示
                                           C_AlwaysDisplay 常显
                                           C_NotDisplay 不显
输出参数: 无
返回参数: 无
调用位置: 
备    注: 
*******************************************************************************/
void SF_Display_MeterIC(uchar8 V_ucData, uchar8 V_ucFlag)
{
	uchar8 V_ucDisplay, V_ucDisPlayData[8];
	Str_Msg_Parameter Str_Msg_Display;		/*显示消息结构体*/

	Str_Msg_Display.SourceAddr = C_Msg_MeterIC;
	Str_Msg_Display.DerictAddr = C_Msg_Display;
	Str_Msg_Display.Length = 0x04;
	V_ucDisplay = 0;
	SF_ClearUcharArray(V_ucDisPlayData, 8);
	V_ucDisPlayData[0] = Pt_DisplayStatus;
	V_ucDisplay |= V_ucData;
	V_ucDisplay |= V_ucFlag;
	V_ucDisPlayData[1] = V_ucDisplay;
	V_ucDisPlayData[2] = 0xFF;
	V_ucDisPlayData[3] = 0xFF;
	Str_Msg_Display.Parameter = V_ucDisPlayData;
	InF_Display_Message(&Str_Msg_Display);
}

/*******************************************************************************
函数原型: void SF_WorkingState(void)
功能描述: 电能表运行状态字2更新
输入参数: Str_PowerData.Deriction需量用功率方向数据
输出参数: 无
返回参数: 无
调用位置: 
备    注: 
*******************************************************************************/
void SF_WorkingState(void)
{
	uchar8 V_ucStateBuffer[5];
	ushort16 V_usStateLen, V_usState1, V_usDataEncode = 0;

	V_usStateLen = CLMeter_Work_State2;
	InF_Read_Data(CMeter_Work_State2, V_ucStateBuffer, &V_usStateLen, &V_usDataEncode);
	PF_Buffer2ToUshort16(V_ucStateBuffer, &V_usState1);
	if (GStr_PowerData.Deriction & C_ActiveEnergyA_Minus)	/*A相有功方向赋值*/
	{
		V_usState1 |= C_PAminus;
	}
	else
	{
		V_usState1 &= C_PAplus;
	}

	if (GStr_PowerData.Deriction & C_ReactiveEnergyA_Minus)	/*A相无功方向赋值*/
	{
		V_usState1 |= C_QAminus;
	}
	else
	{
		V_usState1 &= C_QAplus;
	}

	if (GStr_PowerData.Deriction & C_ActiveEnergyB_Minus)	/*B相有功方向赋值*/
	{
		V_usState1 |= C_PBminus;
	}
	else
	{
		V_usState1 &= C_PBplus;
	}

	if (GStr_PowerData.Deriction & C_ReactiveEnergyB_Minus)	/*B相无功方向赋值*/
	{
		V_usState1 |= C_QBminus;
	}
	else
	{
		V_usState1 &= C_QBplus;
	}

	if (GStr_PowerData.Deriction & C_ActiveEnergyC_Minus)	/*C相有功方向赋值*/
	{
		V_usState1 |= C_PCminus;
	}
	else
	{
		V_usState1 &= C_PCplus;
	}

	if (GStr_PowerData.Deriction & C_ReactiveEnergyC_Minus)	/*C相无功方向赋值*/
	{
		V_usState1 |= C_QCminus;
	}
	else
	{
		V_usState1 &= C_QCplus;
	}
	SF_ClearUcharArray(V_ucStateBuffer, 2);
	PF_Ushort16ToBuffer2(V_ucStateBuffer, &V_usState1);
	InF_Write_Data(C_Msg_MeterIC, CMeter_Work_State2, V_ucStateBuffer, CLMeter_Work_State2, C_W_SafeFlag);
}

/*******************************************************************************
函数原型: void SF_CalTemp(void)
功能描述: 校正温度传感器
输入参数: Str_PowerData.Deriction需量用功率方向数据
输出参数: 无
返回参数: 无
调用位置: 
备    注: 在结束校表环节进行调用，校正温度为基准25℃。
*******************************************************************************/
void SF_CalTemp(void)
{
	uchar8 V_ucTempDataBuffer[4], V_ucData, V_ucLen;
	ulong32 V_ulTempData, V_ulTP, V_ulTC;

	SF_ReadOneReg_MeterIC(C_TempReg_Reg, V_ucTempDataBuffer, C_MeaDataLen);
	V_ucData = V_ucTempDataBuffer[0];
	V_ulTP = C_TP * 10;

	if (V_ucData & 0x80)
	{
		V_ucData = 0 - V_ucData;
	}
	SF_ClearUcharArray(V_ucTempDataBuffer, 4);
	V_ucTempDataBuffer[0] = V_ucData;
	PF_BufferXToUlong32(V_ucTempDataBuffer, &V_ulTempData, C_MeaDataLen);
	V_ulTempData = (V_ulTempData * 363) / 50;
	if (V_ucData & 0x80)
	{
		V_ulTC = V_ulTP + V_ulTempData;
	}
	else
	{
		V_ulTC = V_ulTP - V_ulTempData;
	}
	V_ulTC /= 10;
	V_ucLen = 3;
	SF_ClearUcharArray(V_ucTempDataBuffer, 4);
	PF_Ulong32ToBufferX(V_ucTempDataBuffer, &V_ulTC, C_MeaDataLen);
	InF_Write_RecMeterData(C_Msg_Communication, V_ucTempDataBuffer, V_ucLen, C_W_SafeFlag, C_TempoffsetNO);
}

/*******************************************************************************
函数原型: void SF_InitialPowerCoeff(void)
功能描述: 将功率系数从数据层读取出来，存放在RAM中带CRC
输入参数: 无
输出参数: 无
返回参数: 无
调用位置: 
备    注: 
*******************************************************************************/
void SF_InitialPowerCoeff(void)
{
	uchar8	V_ucPowerFactorBuffer[8], V_ucDataLength;

	SF_ClearUcharArray(V_ucPowerFactorBuffer, 8);
	V_ucDataLength = C_MeaDataLen;
	InF_Read_RecMeterData(C_PowerFactorNO, V_ucPowerFactorBuffer, &V_ucDataLength);	/*从数据层取功率因数*/
	GStr_PowerCoeff.Crc = PF_Cal_CRC(V_ucPowerFactorBuffer, 8);
	PF_Buffer8ToUlong64(V_ucPowerFactorBuffer, &GStr_PowerCoeff.PowerCoeffData, C_CalDataLen);
}

/*******************************************************************************
函数原型: SF_GetPowerCoeff(void)
功能描述: 读取功率系数
输入参数: 无
输出参数: 无
返回参数: 无
调用位置: 
备    注: 
*******************************************************************************/
ulong64 SF_GetPowerCoeff(void)
{
	uchar8 V_ucPowerCoeffBuffer[10];
	ulong64 V_ullPowerCoeffData;

	SF_ClearUcharArray(V_ucPowerCoeffBuffer, 10);
	PF_Ulong64ToBuffer8(&V_ucPowerCoeffBuffer[0], &GStr_PowerCoeff.PowerCoeffData, C_CalDataLen);
	PF_Ushort16ToBuffer2(&V_ucPowerCoeffBuffer[8], &GStr_PowerCoeff.Crc);
	if (PF_Check_CRC(V_ucPowerCoeffBuffer, 10) == C_OK)	/*CRC校验，如果校验错误则重新读取数据层(8字节数据+2字节CRC)*/
	{
		PF_Buffer8ToUlong64(V_ucPowerCoeffBuffer, &V_ullPowerCoeffData, C_CalDataLen);
	}
	else												/*重新读取数据层功率系数参数之后，不再重新CRC校验，直接使用功率系数参数*/
	{
		SF_InitialPowerCoeff();
		V_ullPowerCoeffData = GStr_PowerCoeff.PowerCoeffData;
	}
	return V_ullPowerCoeffData;
}

/*******************************************************************************
函数原型：void InF_ClearHexVarregtype_MeterIC(uchar8 V_ucClearType)
功能描述：总清数据层中瞬时量参数
输入参数：uchar8 V_ucClearType:是否清电流数据:C_ClearCurrData清除电流瞬时量
                                            C_NotClearCurrData不清除电流瞬时量
输出参数：无
返回参数：无
调用位置：用于在进入低功耗之前，清理数据层中的瞬时量数据，电流是否清除可设。
备    注：
*******************************************************************************/
void InF_ClearHexVarregtype_MeterIC(uchar8 V_ucClearType)
{
	uchar8 V_uci, V_ucData[4] = {0x00};
	for (V_uci = 0; V_uci < C_InstantNum; V_uci++)
	{
        if ( (V_uci == C_offCPhaseA_Curr) || (V_uci == C_offCPhaseB_Curr) || (V_uci == C_offCPhaseC_Curr) )	/*3位小数电流不写入数据层，数据层只存4位小数*/
        {
            continue;
        }
		SF_ClearUcharArray(V_ucData, 4);
		if (V_ucClearType == C_NotClearCurrData)
		{
			if ( (V_uci < C_offCPhaseA_Curr_4Dig) || (V_uci > C_offCPhaseC_Curr_4Dig) )						/*电流在C_offCPhaseA_Curr_4Dig--C_offCPhaseC_Curr_4Dig的位置*/
			{
				InF_Write_Data(C_Msg_MeterIC, Str_DataProcess[V_uci].C_InstantOAD, V_ucData, Str_DataProcess[V_uci].CL_InstantOAD, C_W_SafeFlag);
			}
		}
		else
		{
			InF_Write_Data(C_Msg_MeterIC, Str_DataProcess[V_uci].C_InstantOAD, V_ucData, Str_DataProcess[V_uci].CL_InstantOAD, C_W_SafeFlag);
		}
	}

	/*zlj新增清1min平均功率*/
	SF_ClrCurrentPower();
}

/*******************************************************************************
函数原型: void  InF_Initial_MeterIC (void)
功能描述: 触发初始化计量芯片消息，配置所有减定时器时间初值
输入参数: 无
输出参数: GV_ucUpdateTime数据层更新瞬时量定时器初始化
          GV_ucCheckTime校验和校验定时器初始化
          GV_ucEnergyLock锁定电能读取功能
返回参数: 无
调用位置: 
备    注: 
*******************************************************************************/
void  InF_Initial_MeterIC (void)
{
	uchar8 V_ucData;

	Str_Msg_Parameter Str_Msg_InitalTrigger;	/*计量初始化消息结构体*/

	GStr_PowerData.Deriction = 0;				/*功率方向全部初始为正向*/
	V_ucData = Pt_InitialMeterIC;
	GV_ucUpdateTime = C_UpdateTime;				/*数据层更新瞬时量定时器初始化*/
	GV_ucCheckTime = C_CheckTime;				/*校验和校验定时器初始化*/
	GV_ucEnergyLock = C_EnergyLock;				/*锁定电能读取功能*/
	/*奇次谐波增加*/
	GV_ucPowerFactor_Flag = 0;					/*奇次谐波补偿，功率因数是否符合条件标志初始化*/
	GV_ucCurrent_Flag1 = 0;						/*奇次谐波补偿，电流是否符合条件标志(2.8-4A)初始化*/
	GV_ucCurrent_Flag2 = 0;						/*奇次谐波补偿，电流是否符合条件标志(1.4-2A)初始化*/

	/*偶次谐波增加*/
	SF_ClearUlongArray( (ulong32 *)GV_lHD2Rate, CL_HD2Rate); 
	GV_ucStepNum = 0;

	memset(&GStr_PowerAdd, 0x00, sizeof(GStr_PowerAdd) );

	Str_Msg_InitalTrigger.SourceAddr = C_Msg_MeterIC;
	Str_Msg_InitalTrigger.DerictAddr = C_Msg_MeterIC;
	Str_Msg_InitalTrigger.Length = Pt_InitialMeterIC_Len+1;
	Str_Msg_InitalTrigger.Parameter = &V_ucData;
	InF_WriteMessege(&Str_Msg_InitalTrigger);
}

/*******************************************************************************
函数原型: uchar8 InF_ReadReg_MeterIC(ushort16 V_usData_Id, uchar8 *pV_ucData, uchar8 *pV_ucLength)
功能描述: 通过此接口函数可以读取对应标识码的校表参数和实时参数
输入参数: ushort16  V_usData_Id预读取标识码
输出参数: uchar8 *pV_ucData读取数据缓存指针
          uchar8 *pV_ucLength读取数据的长度指针
返回参数: 读取成功：C_OK；读取通讯失败：C_SPIError；数据长度错误:C_DataLenError;数据标识码错误:C_IDError
调用位置: 
备    注: 本函数会通过输入参数的数据标识码，获取相应计量芯片的寄存器地址，然后将数据从计量芯片读取出来
*******************************************************************************/
uchar8 InF_ReadReg_MeterIC(ushort16 V_usData_Id, uchar8 *pV_ucData, uchar8 *pV_ucLength)
{
	uchar8 V_uci, V_ucMeterData[3], V_ucDataDI[2], V_ucNUM;

	PF_Ushort16ToBuffer2(V_ucDataDI, &V_usData_Id);
	if ( V_ucDataDI[1] == C_CalDataMeterIC_DI1)							/*判断是否是读取计量芯片校表参数*/
	{
		if (Str_Table2_CalData[V_ucDataDI[0]].MeterIC_WR | 0x01)		/*对表2中的计量芯片写权限进行判断*/
		{
			SF_ClearUcharArray(V_ucMeterData, 3);
			if (SF_ReadOneReg_MeterIC (V_ucDataDI[0], V_ucMeterData, C_ReadCalDataRegFlag) == C_OK)	/*读取标识码携带的寄存器地址的数据*/
			{
				if (*pV_ucLength >= C_CalDataLen)
				{
					PF_CopyDataBytes(V_ucMeterData, pV_ucData, 3);
					*pV_ucLength = C_CalDataLen;
					return C_OK;
				}
				else
				{
					return C_DataLenError;
				}
			}
			else
			{
				return C_SPIError;
			}
		}
		else
		{
			return C_IDError;
		}
	}
	else if (V_ucDataDI[1] == C_MeaDataMeterIC_DI1)	/*判断是否为读取计量参数*/
	{
		if (InF_JudgeIJTimer() == C_OK)
		{
			if (V_ucDataDI[0] < C_MaxMeaDataReg)
			{
				if (*pV_ucLength >= C_CalDataLen)
				{
					SF_ClearUcharArray(V_ucMeterData, 3);
					if (SF_ReadOneReg_MeterIC(V_ucDataDI[0], V_ucMeterData, C_ReadMeaDataRegFlag) == C_OK)
					{
						PF_CopyDataBytes(V_ucMeterData, pV_ucData, 3);
						*pV_ucLength = C_CalDataLen;
						return C_OK;
					}
					else
					{
						return C_SPIError;
					}
				}
				else
				{
					return C_DataLenError;
				}
			}
			else
			{
				return C_DataLenError;
			}
		}
		else
		{
			return C_Error;
		}
	}
	else if (V_ucDataDI[1] == C_TWCalDataMeterIC_DI1)	/*判断是否是块读取校表参数*/
	{
		if (GV_ucCalibrationState == C_StartCalibrationOK)
		{
			V_ucNUM = Str_Table3_CalData[V_ucDataDI[0]].NO_Amount;
			for (V_uci = 0;V_uci < V_ucNUM; V_uci++)
			{
				SF_ClearUcharArray(V_ucMeterData, 3);
				if (SF_ReadOneReg_MeterIC(*(&Str_Table3_CalData[V_ucDataDI[0]].NO_Buffer0 + V_uci), V_ucMeterData, C_ReadMeaDataRegFlag) == C_OK)
				{
					PF_CopyDataBytes(V_ucMeterData, (pV_ucData + (3 * V_uci) ), 3);
				}
				else
				{
					return C_SPIError;
				}
			}
			if (*pV_ucLength < (C_CalDataLen * V_ucNUM) )
			{
				return C_DataLenError;
			}
			else
			{
				*pV_ucLength = C_CalDataLen * V_ucNUM;
				return C_OK;
			}
		}
		else
		{
			return C_IDError;
		}
	}
	else
	{
		return C_IDError;
	}
}

/*******************************************************************************
函数原型: uchar8  InF_WriteCalReg_MeterIC(ushort16 V_usData_Id, uchar8 *pV_ucData, uchar8 V_ucDataLen, uchar8 *pV_ucPhaseNO, uchar8 *pV_ucNOAmount)
功能描述: 通过此接口函数可以将校表参数写入计量芯片
输入参数: ushort16 V_usData_Id        数据标识码
         uchar8 *pV_ucData    预写入数据存储指针
         uchar8 V_ucDataLen  数据长度(字节)
输出参数: uchar8 *pV_ucPhaseNO   返回真实分相标识码的序号指针
         uchar8 *pV_ucNOAmount   返回真实标识码的序号数量(个数)
返回参数: 写入成功：C_OK；
         写入数据标识错误：C_IDError
         写入通讯失败：C_SPIError；
         启动校表成功：C_StartCalibrationOK
         结束校表成功：C_CalibrationOK
         清校表参数成功:C_ClearCalRegOK
         校表状态错误：C_NOStartCalibration
调用位置: 
备    注: 本函数会通过输入参数的数据标识码，获取相应计量芯片的寄存器地址，然后将数据写入计量芯片
         0x87:+68启动校表、+69结束校表、+6A总清
         0x86+寄存器地址:读写校表参数
         0x83+寄存器地址:读计量芯片计量参数
         0x82+扩展地址:块写校表参数
*******************************************************************************/
uchar8  InF_WriteCalReg_MeterIC(ushort16 V_usData_Id, uchar8 *pV_ucData, uchar8 V_ucDataLen, uchar8 *pV_ucPhaseNO, uchar8 *pV_ucNOAmount)
{
	uchar8 V_uci, V_ucDataId[2], V_ucData[9], V_ucNUM;

	PF_Ushort16ToBuffer2(V_ucDataId, &V_usData_Id);
	if (V_ucDataId[1] == C_Control_DI1)
	{
		if (InF_JudgeIJTimer() == C_OK)
		{
			if (V_ucDataId[0] == C_StartCalibration_DI0)
			{
				GV_ucCalibrationState = C_StartCalibrationOK;
				return C_StartCalibrationOK;
			}
			else if (V_ucDataId[0] == C_StopCalibration_DI0)
			{
				SF_CalTemp();
				InF_Initial_MeterIC();
				GV_ucCalibrationState = C_CalibrationOK;
				return C_CalibrationOK;
			}
			else if (V_ucDataId[0] == C_ClearCalData_DI0)
			{
				if (GV_ucCalibrationState == C_StartCalibrationOK)
				{
					SF_ClearCalReg_MeterIC();
					return C_ClearCalRegOK;
				}
				else
				{
					return C_NOStartCalibration;
				}
			}
			else
			{
				return C_IDError;
			}
		}
		else
		{
			return C_IDError;
		}
	}
	else if (InF_JudgeIJTimer() == C_OK)
	{
		if (GV_ucCalibrationState == C_StartCalibrationOK)
		{
			if (V_ucDataId[1] == C_CalDataMeterIC_DI1)
			{
				if (Str_Table2_CalData[V_ucDataId[0]].NO_Amount == C_NorDIAmount)
				{
					if (Str_Table2_CalData[V_ucDataId[0]].MeterIC_WR | 0x10)
					{
						SF_ClearUcharArray(V_ucData, 9);
						V_ucData[0] = *pV_ucData;
						V_ucData[1] = *(pV_ucData + 1);
						V_ucData[2] = 0;
						GV_ucWriteRegSafeFlag = C_DataSafe;
						if (SF_WriteOneReg_MeterIC(V_ucData, V_ucDataId[0], GV_ucWriteRegSafeFlag) == C_OK)
						{
							GV_ucWriteRegSafeFlag = C_DataUnsafe;
							*pV_ucPhaseNO = V_ucDataId[0];
							*pV_ucNOAmount = C_NorDIAmount;
							return C_OK;
						}
						else
						{
							return C_SPIError;
						}
					}
					else if (Str_Table2_CalData[V_ucDataId[0]].DataProcess_WR | 0x10)
					{
						*pV_ucPhaseNO = V_ucDataId[0];
						*pV_ucNOAmount = C_NorDIAmount;
						return C_OK;
					}
					else
					{
						return C_IDError;
					}

				}
				else
				{
					return C_IDError;
				}
			}
			else if (V_ucDataId[1] == C_TWCalDataMeterIC_DI1)
			{
				V_ucNUM = Str_Table3_CalData[V_ucDataId[0]].NO_Amount;
				for (V_uci = 0; V_uci < V_ucNUM; V_uci++)
				{
					GV_ucWriteRegSafeFlag = C_DataSafe;
					if (SF_WriteOneReg_MeterIC(pV_ucData + (3 * V_uci), *(&Str_Table3_CalData[V_ucDataId[0]].NO_Buffer0 + V_uci), GV_ucWriteRegSafeFlag) == C_OK)
					{
						*(pV_ucPhaseNO + V_uci) = *(&Str_Table3_CalData[V_ucDataId[0]].NO_Buffer0 + V_uci);
					}
					else
					{
						return C_SPIError;
					}
				}
				if (*pV_ucNOAmount < Str_Table3_CalData[V_ucDataId[0]].NO_Amount)
				{
					return C_DataLenError;
				}
				else
				{
					*pV_ucNOAmount = Str_Table3_CalData[V_ucDataId[0]].NO_Amount;
					return C_OK;
				}
			}
			else
			{
				return C_IDError;
			}
		}
		else
		{
			return C_NOStartCalibration;
		}
	}
	else
	{
		GV_ucCalibrationState = C_CalibrationOK;
		return C_IDError;
	}
}

/*******************************************************************************
函数原型: uchar8  InF_Read_MeterIC_EnergyData(Struct_Energy_Type *pStr_EnergyData)
功能描述: 通过此接口函数，读取电能数据
输入参数: 电能存储用结构体指针
输出参数: Str_EnergyData电能数据结构体电能数据 单位imp
返回参数: 成功：C_OK;失败：C_SPIError
调用位置: 
备    注: 本函数在被调用的时候，会读取计量芯片电能数据，并将数据写入输入参数给出的结构体指针当中，读取过程
         会判断电能闭锁标志是否为闭锁状态，如果为闭锁状态，返回电能数据全部为零。
*******************************************************************************/
uchar8  InF_Read_MeterIC_EnergyData(Struct_Energy_Type *pStr_EnergyData)
{
	uchar8 V_uci;
	if (GV_ucEnergyLock == C_EnergyUnlock)
	{
		SF_ReadEnergyData_MeterIC();
		for (V_uci = 0; V_uci < 8; V_uci++)
		{
			*(&pStr_EnergyData->V_usActiveEnergy_T + V_uci) = *(&GStr_EnergyData.V_ucActiveEnergy_TABC[0] + V_uci);
		}
		pStr_EnergyData->V_ucPowerDeriction = GStr_PowerData.Deriction;
		return C_OK;
	}
	else
	{
		for (V_uci = 0; V_uci < 8; V_uci++)
		{
			*(&pStr_EnergyData->V_usActiveEnergy_T + V_uci) = 0;
			pStr_EnergyData->V_ucPowerDeriction = 0;
		}
		return C_SPIError;
	}
}

/*******************************************************************************
函数原型: void  InF_PowerDownInitial_MeterIC (void)
功能描述: 低功耗状态初始化计量芯片
输入参数: 无
输出参数: 无
返回参数: 无
调用位置: 
备    注: 
*******************************************************************************/
void  InF_PowerDownInitial_MeterIC(void)
{
	uchar8 V_uci, V_ucCalRegData[4], V_ucDataLen;
	ushort16 V_usData;

	SF_PowerDownHardwareRESET_MeterIC();
	SF_ENSPIMode_MeterIC();
	SF_Eable_MeterIC();
	V_usData = C_PorDownModeCfg_Data;	/*低功耗下模式相关控制配置*/
	SF_ClearUcharArray(V_ucCalRegData, 4);
	PF_Ushort16ToBuffer2(V_ucCalRegData, &V_usData);
	SF_WriteOneReg_MeterIC(V_ucCalRegData, C_ModeCfg_Reg, C_DataSafe);
	SF_ClearUcharArray(V_ucCalRegData, 4);
	V_usData = C_ModuleCFG_Data;		/*电路模块配置*/
	PF_Ushort16ToBuffer2(V_ucCalRegData, &V_usData);
	SF_WriteOneReg_MeterIC(V_ucCalRegData, C_ModuleCFG_Reg, C_DataSafe);
	V_ucDataLen = C_CalDataLen;			/*ADC增益选择*/
	SF_ClearUcharArray(V_ucCalRegData, 4);
	InF_Read_RecMeterData(0x02, V_ucCalRegData, &V_ucDataLen);
	SF_WriteOneReg_MeterIC(V_ucCalRegData, 0x02, C_DataSafe);
	/****************电压和电流校表增益配置****************/
	for (V_uci = 0x17; V_uci < 0x1D; V_uci++)
	{
		SF_ClearUcharArray(V_ucCalRegData, 4);
		InF_Read_RecMeterData(V_uci, V_ucCalRegData, &V_ucDataLen);
		SF_WriteOneReg_MeterIC(V_ucCalRegData, V_uci, C_DataSafe);
	}
}

/*******************************************************************************
函数原型: uchar8 InF_PowerDownReadData_MeterIC(void)
功能描述: 低功耗状态读取计量数据
输入参数: 无
输出参数: GStr_HEX_VARREGTYPE结构体中的电压数据和电流数据
返回参数: 读取成功：C_OK；读取通讯失败：C_SPIError；
调用位置: 
备    注: 
*******************************************************************************/
uchar8 InF_PowerDownReadData_MeterIC(void)
{
	uchar8 V_uci, V_ucDIData[5], V_ucData[5];
    Str_VARREGTYPE_Type Str_VARREGTYPE_temp;
    
	/****************读取电压电流数据****************/
	for (V_uci = 0; V_uci < 6; V_uci++)
	{
		SF_ClearUcharArray(V_ucDIData, 4);
		if (SF_ReadOneReg_MeterIC(C_VRmsVReg_AReg + V_uci, V_ucDIData, C_ReadMeaDataRegFlag) == C_OK)
		{
			PF_BufferXToUlong32(V_ucDIData, &Str_VARREGTYPE_temp.VRmsVReg[0] + V_uci, C_CalDataLen);
		}
		else
		{
			return C_SPIError;
		}
	}
	/****************将电压和电流数据计算成HEX***************************/
	SF_VoltageDatatoHEX_MeterIC(&Str_VARREGTYPE_temp);
	SF_CurrentDatatoHEX_MeterIC(&Str_VARREGTYPE_temp);
	/****************更新数据层电压和电流数据****************************/
	for (V_uci = 0; V_uci < 3; V_uci++)
	{
		SF_ClearUcharArray(V_ucData, 4);
		PF_Ushort16ToBuffer2(V_ucData, &GStr_HEX_VARREGTYPE.VRmsVRegHEX_ABC[V_uci]);
		InF_Write_Data(C_Msg_MeterIC, Str_DataProcess[V_uci + C_offCPhaseA_Volage].C_InstantOAD, V_ucData, Str_DataProcess[V_uci + C_offCPhaseA_Volage].CL_InstantOAD, C_W_SafeFlag);
	}
	for (V_uci = 0;V_uci < 3; V_uci++)
	{
		SF_ClearUcharArray(V_ucData, 4);
		PF_Ulong32ToBufferX(V_ucData, (ulong32 *)&GStr_HEX_VARREGTYPE.VRmsILSBRegHEX_ABC[V_uci], 4);
		InF_Write_Data(C_Msg_MeterIC,Str_DataProcess[V_uci + C_offCPhaseA_Curr_4Dig].C_InstantOAD, V_ucData, Str_DataProcess[V_uci + C_offCPhaseA_Curr_4Dig].CL_InstantOAD, C_W_SafeFlag);
	}
	return C_OK;
}

/*******************************************************************************
函数原型: void  InF_Initial(void)
功能描述: 初始化计量芯片故障事件定时器
输入参数: 无
输出参数: 无
返回参数: 无
调用位置: 
备    注: 
*******************************************************************************/
void  InF_Initial(void)
{
	GV_ucMeterICErrorNum = 0;
	GV_ucMeterICErrorTime = 0;
	GV_ucMeterICErrorState = C_MeterICNormal;
}

/*******************************************************************************
功能描述：	偶次谐波计算
*******************************************************************************/
#define C_HD2Rate_Low       0x0000005A	/*偶次谐波含量最小限值30%（0.3*0.3*1000）*/
#define C_HD2Rate_High      0x000000FA	/*偶次谐波含量最大限值50%（0.5*0.5*1000）*/

#define	C_SampNum	72

static const short16 TAB_Cos1[C_SampNum] =
{
    1000,  996,  985,  966,  940,  906,  866,  819,  766,  707,  643,  574,  500,  423,  342,  259,  174,   87,
       0,  -87, -174, -259, -342, -423, -500, -574, -643, -707, -766, -819, -866, -906, -940, -966, -985, -996,
   -1000, -996, -985, -966, -940, -906, -866, -819, -766, -707, -643, -574, -500, -423, -342, -259, -174,  -87,
       0,   87,  174,  259,  342,  423,  500,  574,  643,  707,  766,  819,  866,  906,  940,  966,  985,  996,
};
static const short16 TAB_Sin1[C_SampNum] =
{
       0,   87,  174,  259,  342,  423,  500,  574,  643,  707,  766,  819,  866,  906,  940,  966,  985,  996,
    1000,  996,  985,  966,  940,  906,  866,  819,  766,  707,  643,  574,  500,  423,  342,  259,  174,   87,
       0,  -87, -174, -259, -342, -423, -500, -574, -643, -707, -766, -819, -866, -906, -940, -966, -985, -996,
   -1000, -996, -985, -966, -940, -906, -866, -819, -766, -707, -643, -574, -500, -423, -342, -259, -174,  -87,
};
static const short16 TAB_Cos2[C_SampNum] =
{
    1000,  985,  940,  866,  766,  643,  500,  342,  174,    0, -174, -342, -500, -643, -766, -866, -940, -985,
   -1000, -985, -940, -866, -766, -643, -500, -342, -174,    0,  174,  342,  500,  643,  766,  866,  940,  985,
    1000,  985,  940,  866,  766,  643,  500,  342,  174,    0, -174, -342, -500, -643, -766, -866, -940, -985,
   -1000, -985, -940, -866, -766, -643, -500, -342, -174,    0,  174,  342,  500,  643,  766,  866,  940,  985,
};
static const short16 TAB_Sin2[C_SampNum] =
{
    0,  174,  342,  500,  643,  766,  866,  940,  985, 1000,  985,  940,  866,  766,  643,  500,  342,  174,
    0, -174, -342, -500, -643, -766, -866, -940, -985,-1000, -985, -940, -866, -766, -643, -500, -342, -174,
    0,  174,  342,  500,  643,  766,  866,  940,  985, 1000,  985,  940,  866,  766,  643,  500,  342,  174,
    0, -174, -342, -500, -643, -766, -866, -940, -985,-1000, -985, -940, -866, -766, -643, -500, -342, -174,
};

#if 0	/*单点补偿*/

#define CurrentLimit5A_Low		0x018000	/*5(60)A偶次谐波试验电流最小限值18A*/
#define CurrentLimit5A_High		0x028000	/*5(60)A偶次谐波试验电流最大限值28A*/

#define CurrentLimit10A_Low		0x030000	/*10(100)A偶次谐波试验电流最小限值30A*/
#define CurrentLimit10A_High	0x040000	/*10(100)A偶次谐波试验电流最大限值40A*/

#define C_EvenHarmonicDelayTimer	6		/*基于5ms定时，一个周波延迟30ms*/
#endif

#if 1	/*线性补偿*/

#define CurrentLimit5A_Low		0x001500	/*5(60)A偶次谐波试验电流最小限值1.5A*/
#define CurrentLimit5A_High		0xFFFFFF	/*5(60)A偶次谐波试验电流最大限值无*/

#define CurrentLimit10A_Low		0x003000	/*10(100)A偶次谐波试验电流最小限值3A*/
#define CurrentLimit10A_High	0xFFFFFF	/*10(100)A偶次谐波试验电流最大限值无*/

#define C_EvenHarmonicDelayTimer	10		/*基于5ms定时，两个周波延迟50ms*/
#endif
/**********************************************************************************
函数原型：void InF_InitialEvenHarmonicCompensationTime (void)
功能描述：偶次谐波补偿时间初始化
输入参数：无
输出参数：无
返回参数：无
调用位置：
备    注：
**********************************************************************************/
void InF_InitialEvenHarmonicCompensationTime (void)
{
	uchar8 V_ucDataBuffer[2];
	ushort16 V_usDataLength, V_usDataEncode = 0;
	
	GV_ucEvenHarmonicSecondTimer = 60;

	V_usDataLength =  CL_EvenHar_Time;
	if (InF_Read_Data(C_EvenHar_Time, V_ucDataBuffer, &V_usDataLength, &V_usDataEncode) == C_OK)
	{
		PF_Buffer2ToUshort16(V_ucDataBuffer, &GV_usEvenHarmonicCompensationTime);
	}
	else
	{
		GV_usEvenHarmonicCompensationTime = C_EvenHarmonicCompensationTime;	/*默认24h*/
	}
}

/**********************************************************************************
函数原型：uchar8 SF_GetEvenHarmonicCompensationFlag (void)
功能描述：获取偶次谐波补偿标志
输入参数：无
输出参数：无
返回参数：C_Even_Harmonic_En:补偿使能，C_Even_Harmonic_Dis：补偿失能
调用位置：
备    注：
**********************************************************************************/
uchar8 SF_GetEvenHarmonicCompensationFlag (void)
{
	if (GV_usEvenHarmonicCompensationTime != 0 )
	{
		if (GV_ucEvenHarmonicSecondTimer != 0)
		{
			GV_ucEvenHarmonicSecondTimer--;
		}
		else
		{
			GV_ucEvenHarmonicSecondTimer = 60;	/*60s计时*/
			GV_usEvenHarmonicCompensationTime--;
		}
		return C_Even_Harmonic_En;
	}
	return C_Even_Harmonic_Dis;
}

/**********************************************************************************
函数原型：uchar8 SF_GetEvenHarmonicCurrent (Str_CurrentLimit_Type *pStr_CurrentLimit)
功能描述：获取偶次谐波补偿时电流范围
输入参数：无
输出参数：无
返回参数：C_OK:A、B、C三相中至少有一相在范围内，C_Error：A、B、C三相都不在范围内
功能说明：
调用机制：
备    注：
**********************************************************************************/
uchar8 SF_GetEvenHarmonicCurrent(Str_CurrentLimit_Type *pStr_CurrentLimit)
{
	uchar8 V_ucIb;
	ushort16 V_usDataLength, V_usDataEncode = 0;

	V_usDataLength = CLCurrent_Type;
	if (InF_Read_Data(CCurrent_Type, &V_ucIb, &V_usDataLength, &V_usDataEncode) != C_OK)
	{
		pStr_CurrentLimit->V_ulCurrentLimit_Low = 0xFFFFFFFF;
		pStr_CurrentLimit->V_ulCurrentLimit_High = 0xFFFFFFFF;

		return C_Error;
	}

	switch (V_ucIb & 0x0F)
	{
		case C_Ib5A:	/*电流范围18.000A~28.000A*/
		{
			pStr_CurrentLimit->V_ulCurrentLimit_Low = CurrentLimit5A_Low;
			pStr_CurrentLimit->V_ulCurrentLimit_High = CurrentLimit5A_High;
		}break;

		case C_Ib10A:	/*电流范围30.000A~40.000A*/
		{
			pStr_CurrentLimit->V_ulCurrentLimit_Low = CurrentLimit10A_Low;
			pStr_CurrentLimit->V_ulCurrentLimit_High = CurrentLimit10A_High;
		}break;

		default:
		{
			pStr_CurrentLimit->V_ulCurrentLimit_Low = 0xFFFFFFFF;
			pStr_CurrentLimit->V_ulCurrentLimit_High = 0xFFFFFFFF;
		}break;
	}

	if ( ( ( SF_ABS(GStr_HEX_VARREGTYPE.VRmsIRegHEX_ABC[C_offA]) < pStr_CurrentLimit->V_ulCurrentLimit_Low ) || ( SF_ABS(GStr_HEX_VARREGTYPE.VRmsIRegHEX_ABC[C_offA]) > pStr_CurrentLimit->V_ulCurrentLimit_High ) )
      && ( ( SF_ABS(GStr_HEX_VARREGTYPE.VRmsIRegHEX_ABC[C_offB]) < pStr_CurrentLimit->V_ulCurrentLimit_Low ) || ( SF_ABS(GStr_HEX_VARREGTYPE.VRmsIRegHEX_ABC[C_offB]) > pStr_CurrentLimit->V_ulCurrentLimit_High ) )
      && ( ( SF_ABS(GStr_HEX_VARREGTYPE.VRmsIRegHEX_ABC[C_offC]) < pStr_CurrentLimit->V_ulCurrentLimit_Low ) || ( SF_ABS(GStr_HEX_VARREGTYPE.VRmsIRegHEX_ABC[C_offC]) > pStr_CurrentLimit->V_ulCurrentLimit_High ) ) )
	{
		return C_Error;
	}

	return C_OK;
}

/**********************************************************************************
函数原型：void SF_GetEvenHarmonicContent (void)
功能描述：获取各相电流偶次谐波含量
输入参数：无
输出参数：无
返回参数：无
功能说明：
调用机制：GV_EvenHarmonicFlag == C_DoEvenHarmonicFlag 开启偶次谐波补偿
备    注：谐波总执行150ms，主要用于数据采集
**********************************************************************************/
void SF_GetEvenHarmonicContent (void)
{
	ushort16 V_usi, V_uschl, V_usDataLength;
	uchar8 V_ucBuffer[4], V_ucIb;
	ulong32 V_ulsum1, V_ulsum2;
	long32 V_lsum1c, V_lsum1s, V_lsum2c, V_lsum2s;
	ushort16 V_usSampBuffer, V_usDataEncode = 0;
	short16 V_ssamp[3][C_SampNum];		/*ADC data:72*3*/
	ulong64 V_ullsum2;
	ulong32 V_ulFundamental[3];
	float V_fFundamentalRate;
	ulong32 V_ulCurrentType;
	Str_CurrentLimit_Type Str_CurrentLimit;

	/*判断当前电流是否在偶次谐波要求范围内*/
	if (SF_GetEvenHarmonicCurrent ( &Str_CurrentLimit ) != C_OK)
	{
		SF_ClearUlongArray( (ulong32 *)GV_lHD2Rate, CL_HD2Rate);	/*偶次谐波含有量清零*/
		GV_ucStepNum = 0;
		return;
	}

	V_usDataLength = CLCurrent_Type;
	if(InF_Read_Data(CCurrent_Type, &V_ucIb, &V_usDataLength, &V_usDataEncode) != C_OK)
	{
		return;
	}
	
	switch (GV_ucStepNum)
	{
		case 0x00:
		{
			memset(V_ucBuffer, 0x00, 4);
			SF_WriteOneReg_MeterIC(V_ucBuffer, C_BuffStr, 0x86);	/*采样数据缓冲停止(0x000000,0xc0,0x86)*/

			SF_Delay(C_DELAY1MS);

			V_ucBuffer[0] = 0xCB;
			V_ucBuffer[1] = 0xCC;
			V_ucBuffer[2] = 0x00;
			V_ucBuffer[3] = 0x00;
			SF_WriteOneReg_MeterIC(V_ucBuffer, C_BuffStr, 0x86);    /*采样数据缓冲开启(0x00CCCB,0xc0,0x86)*/

			GV_ucEvenHarmonicDelayTimer = C_EvenHarmonicDelayTimer;	/*延时30ms,基于5ms*/
			while (GV_ucEvenHarmonicDelayTimer != 0)
			{
				SF_Delay(C_DELAY1MS);
			}

			memset(V_ucBuffer, 0x00, 4);
			SF_WriteOneReg_MeterIC(V_ucBuffer, C_BuffStr, 0x86);	/*采样数据缓冲停止(0x000000,0xc0,0x86)*/

			GV_ucStepNum = 1;

		}break;

		case 0x01:
		{
			GV_ucStepNum = 0;										/*流程控制字清零*/

			memset(&V_ucBuffer[0], 0x00, 4);
			V_ucBuffer[0] = 0x0F;
			SF_WriteOneReg_MeterIC(V_ucBuffer, C_BuffSet, 0x86);	/*指定缓冲数据起始点(0x00000F,0xc1,0x86)*/

			SF_WriteEnable_MeterIC();

			SF_ReadDataModeSet(C_ReadMeaDataRegFlag);

			SF_WriteDisable_MeterIC();								/* 写计量芯片寄存器使能-关闭，即不再允许写计量芯片寄存器 */

	/**********************读第一个周波缓存数据****************************/
			SF_Eable_MeterIC();
			memset(&V_ucBuffer[0], 0x00, 4);

			for (V_usi = 0; V_usi < C_SampNum; V_usi++)				/*此for循环用时33ms（30~35ms）*/
			{
				for (V_uschl = 0; V_uschl < 3; V_uschl++)			/*每一次for循环之间间隔12us*/
				{
					SF_ReadBufferReg_MeterIC(0x7f, &V_ucBuffer[0]);
					PF_Buffer2ToUshort16(&V_ucBuffer[0], &V_usSampBuffer);
					V_ssamp[V_uschl][V_usi] = (short16)V_usSampBuffer;
				}
			}
			SF_Disable_MeterIC();
			
			/*计算偶次谐波含量*/
			for (V_uschl = 0; V_uschl < 3; V_uschl++)
			{
				V_lsum1c = 0;
				V_lsum1s = 0;
				V_lsum2c = 0;
				V_lsum2s = 0;

				for (V_usi = 0; V_usi < C_SampNum; V_usi++)
				{
					V_lsum1c += TAB_Cos1[V_usi] * V_ssamp[V_uschl][V_usi];
					V_lsum1s += TAB_Sin1[V_usi] * V_ssamp[V_uschl][V_usi];
					V_lsum2c += TAB_Cos2[V_usi] * V_ssamp[V_uschl][V_usi];
					V_lsum2s += TAB_Sin2[V_usi] * V_ssamp[V_uschl][V_usi];
				}

				V_lsum1c >>= 16;					/*缩位,以便做运算*/
				V_lsum1s >>= 16;
				V_lsum2c >>= 16;
				V_lsum2s >>= 16;

				V_ulsum1 = V_lsum1c * V_lsum1c + V_lsum1s * V_lsum1s;
				V_ulsum2 = V_lsum2c * V_lsum2c + V_lsum2s * V_lsum2s;
				
				if ( (V_ucIb & 0x0F) == C_Ib10A)
				{
					V_ulCurrentType = 0x00009000;	/*用10（100）A的表实测电表内电流有效值为3A时，sum1为0x0000A100左右*/
													/*由于此值与电流互感器变比，采样电阻及电流增益有关，因此此处需用10（100）A的表实际调试*/
				}
				else
				{
					V_ulCurrentType = 0x00005000;	/*实测电表内电流有效值为1.5A时，sum1为0x00006000左右*/
				}
				if (V_ulsum1 >= V_ulCurrentType)	/*剔出小电流，以免误判*/
				{
					V_ulFundamental[V_uschl] = V_ulsum1;
					V_ullsum2 = 1000 * (ulong64)V_ulsum2;
					GV_lHD2Rate[V_uschl] = V_ullsum2 / V_ulsum1;								/*扩大1000倍*/
				}
				else
				{
					GV_lHD2Rate[V_uschl] = 0;
				}
			}

			/*判断谐波含有量是否在30%~50%之间*/
			if ( ( (GV_lHD2Rate[0] < C_HD2Rate_Low) || (GV_lHD2Rate[0] > C_HD2Rate_High) ) &&
                 ( (GV_lHD2Rate[1] < C_HD2Rate_Low) || (GV_lHD2Rate[1] > C_HD2Rate_High) ) &&
                 ( (GV_lHD2Rate[2] < C_HD2Rate_Low) || (GV_lHD2Rate[2] > C_HD2Rate_High) ) )	/*40%的平方扩大1000倍*/
			{
				SF_ClearUlongArray( (ulong32 *)GV_lHD2Rate, CL_HD2Rate);						/*偶次谐波含有量清零*/
				return;								/*退出偶次谐波含量计算*/
			}

		/***********************读取第二个周波缓存数据************************/
			SF_Eable_MeterIC();
			
			memset(&V_ucBuffer[0],0x00,4);

			for (V_usi = 0; V_usi < C_SampNum; V_usi++)			/*此for循环用时33ms（30~35ms）*/
			{
				for (V_uschl = 0; V_uschl < 3; V_uschl++)		/*每一次for循环之间间隔12us*/
				{
					SF_ReadBufferReg_MeterIC(0x7f, &V_ucBuffer[0]);								/*读缓冲数据*/
					PF_Buffer2ToUshort16(&V_ucBuffer[0], &V_usSampBuffer);
					V_ssamp[V_uschl][V_usi] = (short16)V_usSampBuffer;
				}
			}
			SF_Disable_MeterIC();

			/*计算偶次谐波含量*/
			for (V_uschl = 0; V_uschl < 3; V_uschl++)
			{
				V_lsum1c = 0;
				V_lsum1s = 0;
				V_lsum2c = 0;
				V_lsum2s = 0;

				for (V_usi = 0; V_usi < C_SampNum; V_usi++)
				{
					V_lsum1c += TAB_Cos1[V_usi] * V_ssamp[V_uschl][V_usi];
					V_lsum1s += TAB_Sin1[V_usi] * V_ssamp[V_uschl][V_usi];
					V_lsum2c += TAB_Cos2[V_usi] * V_ssamp[V_uschl][V_usi];
					V_lsum2s += TAB_Sin2[V_usi] * V_ssamp[V_uschl][V_usi];
				}

				V_lsum1c >>= 16;					/*缩位,以便做运算*/
				V_lsum1s >>= 16;
				V_lsum2c >>= 16;
				V_lsum2s >>= 16;

				V_ulsum1 = V_lsum1c * V_lsum1c + V_lsum1s * V_lsum1s;
				V_ulsum2 = V_lsum2c * V_lsum2c + V_lsum2s * V_lsum2s;

				if ( (V_ucIb & 0x0F) == C_Ib10A)
				{
					V_ulCurrentType = 0x00009000;	/*用10（100）A的表实测电表内电流有效值为3A时，sum1为0x0000A100左右*/
													/*由于此值与电流互感器变比，采样电阻及电流增益有关，因此此处需用10（100）A的表实际调试*/
				}
				else
				{
					V_ulCurrentType = 0x00005000;	/*实测电表内电流有效值为1.5A时，sum1为0x00006000左右*/
				}
				
				if (V_ulsum1 >= V_ulCurrentType)	/*剔出小电流，以免误判*/
				{
					V_fFundamentalRate = ( (float)V_ulsum1) / ( (float)V_ulFundamental[V_uschl]);

					if ( (V_fFundamentalRate < 0.9) || (V_fFundamentalRate > 1.1) )		/*判断两个周波的基波值是否在10%以内*/
					{
						GV_lHD2Rate[3 + V_uschl] = 0;
					}
					else
					{
						V_ullsum2 = 1000 * (ulong64)V_ulsum2;
						GV_lHD2Rate[3 + V_uschl] = V_ullsum2 / V_ulsum1;				/*扩大1000倍*/
					}

				}
				else
				{
					GV_lHD2Rate[3 + V_uschl] = 0;
				}
			}

			/*判断谐波含有量是否在30%~50%之间*/
			if ( ( (GV_lHD2Rate[0] < C_HD2Rate_Low) || (GV_lHD2Rate[0] > C_HD2Rate_High) || (GV_lHD2Rate[3] > C_HD2Rate_High) || (GV_lHD2Rate[3] > C_HD2Rate_High) ) &&
                 ( (GV_lHD2Rate[1] < C_HD2Rate_Low) || (GV_lHD2Rate[1] > C_HD2Rate_High) || (GV_lHD2Rate[4] > C_HD2Rate_High) || (GV_lHD2Rate[4] > C_HD2Rate_High) ) &&
                 ( (GV_lHD2Rate[2] < C_HD2Rate_Low) || (GV_lHD2Rate[2] > C_HD2Rate_High) || (GV_lHD2Rate[5] > C_HD2Rate_High) || (GV_lHD2Rate[5] > C_HD2Rate_High) ) )	/*40%的平方扩大1000倍*/
			{
				SF_ClearUlongArray( (ulong32 *)GV_lHD2Rate, CL_HD2Rate);				/*偶次谐波含有量清零*/				
				return;		/*退出偶次谐波含量计算*/
			}

		}break;

		default:
		{
			SF_ClearUlongArray( (ulong32 *)GV_lHD2Rate, CL_HD2Rate);					/*偶次谐波含有量清零*/			
			GV_ucStepNum = 0;
		}break;
	}
}

/**********************************************************************************
函数原型：void SF_GetEvenHarmonicCompensationValue( ushort16 *pV_usCompTemp );
功能描述：获取偶次谐波补偿值
输入参数：ushort16 *pV_usCompTemp:
输出参数：ushort16 *pV_usCompTemp:
返回参数：无
功能说明：
调用机制：
备    注：此函数仅适用于单点补偿
**********************************************************************************/
void SF_GetEvenHarmonicCompensationValue( ushort16 *pV_usCompTemp )
{
    ushort16 V_usDataLength = 0, V_usDataEncode = 0;
	uchar8 V_ucDataBuff[6] = {0};
	uchar8 V_ucI = 0;
	ulong32 V_ulCurrentTemp[3], V_ulCompValue[3];
	long32 V_lCompTemp[3];
	Str_EvenHarmonicError_Type Str_EvenHarmonicError;
	Str_CurrentLimit_Type Str_CurrentLimit;
	ulong32 V_ulEvenHar_AddData_ABC[3][2] = {{C_EvenHar_AddData_A0, C_EvenHar_AddData_A1},
                                             {C_EvenHar_AddData_B0, C_EvenHar_AddData_B1},
                                             {C_EvenHar_AddData_C0, C_EvenHar_AddData_C1}};

	/*获取偶次谐波电流范围*/
	if ( SF_GetEvenHarmonicCurrent( &Str_CurrentLimit ) != C_OK )
	{
		for ( V_ucI = 0; V_ucI < 3; V_ucI ++ )
		{
			*(pV_usCompTemp + V_ucI) = 0;
		}
		return;
	}

	/*获取ABC相偶次谐波误差系数*/
	for ( V_ucI = 0; V_ucI < 3; V_ucI ++ )
	{
		memset( &V_ucDataBuff[0], 0x00, 6 );
		V_usDataLength = CL_EvenHar_AddData_A0;
		if ( ( InF_Read_Data( V_ulEvenHar_AddData_ABC[V_ucI][0], &V_ucDataBuff[0], &V_usDataLength, &V_usDataEncode ) == C_OK )
          && ( InF_Read_Data( V_ulEvenHar_AddData_ABC[V_ucI][1], &V_ucDataBuff[3], &V_usDataLength, &V_usDataEncode ) == C_OK ) )
		{
			PF_Buffer2ToUshort16( &V_ucDataBuff[0], &Str_EvenHarmonicError.V_usDataTemp_ABC0[V_ucI] );
			PF_Buffer2ToUshort16( &V_ucDataBuff[3], &Str_EvenHarmonicError.V_usDataTemp_ABC1[V_ucI] );
		}
		else
		{
			memset( &V_ucDataBuff[0], 0x00, 6 );
			PF_Buffer2ToUshort16( &V_ucDataBuff[0], &Str_EvenHarmonicError.V_usDataTemp_ABC0[V_ucI] );
			PF_Buffer2ToUshort16( &V_ucDataBuff[3], &Str_EvenHarmonicError.V_usDataTemp_ABC1[V_ucI] );
		}
	}

	/*获取当前电流值Hex*/
	for ( V_ucI = 0; V_ucI < 3; V_ucI ++ )
	{
		/*电流有效值保留一位小数，防止电流跳动，不断写补偿数据到计量芯*/
		V_ulCurrentTemp[V_ucI] = SF_ABS(GStr_HEX_VARREGTYPE.VRmsIRegHEX_ABC[V_ucI] & 0xFFFFFF00);
	}

	/*计算各相偶次谐波补偿值*/
	for ( V_ucI = 0; V_ucI < 3; V_ucI ++ )
	{
		/*首先计算误差值*/
		/*y=kx+b,k,b值比实际扩大100倍，x值比实际扩大1000倍，因而y值比实际扩大100000倍*/
		V_lCompTemp[V_ucI] = ( (long32)(*( &Str_EvenHarmonicError.V_usDataTemp_ABC1[V_ucI] ) ) * (long32)( V_ulCurrentTemp[V_ucI]) )
							+ (long32)( *( &Str_EvenHarmonicError.V_usDataTemp_ABC0[V_ucI] ) ) * 1000;

		/*然后计算补偿值*/
		/*原公式为V_lCompTemp = (((((0 - V_lCompTemp)/100)*1000)/ 1732)/100000) * 32768)+65536;
		简化公式为V_lCompTemp = (((((0 - V_lCompTemp )/ 1732)/10000) * 32768)+65536;*/
		V_lCompTemp[V_ucI] = ( ( ( (0 - V_lCompTemp[V_ucI] ) / 1732) * 32768) / 10000) + 65536;

		/*对补偿值进行数据类型转换*/
		V_ulCompValue[V_ucI] = (ulong32)V_lCompTemp[V_ucI];

		memset( &V_ucDataBuff[0], 0x00, 6 );

		PF_Ulong32ToBufferX(&V_ucDataBuff[0], &V_ulCompValue[V_ucI], 2);

		PF_Buffer2ToUshort16(&V_ucDataBuff[0], (pV_usCompTemp + V_ucI) );
	}

		/*判断谐波含有量是否在30%~50%之间,且电流在规定范围内,不在范围内补偿值清零*/
	for ( V_ucI = 0; V_ucI < 3; V_ucI++ )
	{
		if ( ( GV_lHD2Rate[V_ucI] < C_HD2Rate_Low )
          || ( GV_lHD2Rate[(3 + V_ucI)] < C_HD2Rate_Low )
          || ( GV_lHD2Rate[V_ucI] > C_HD2Rate_High ) 
          || ( GV_lHD2Rate[(3 + V_ucI)] > C_HD2Rate_High )
          || ( SF_ABS(GStr_HEX_VARREGTYPE.VRmsIRegHEX_ABC[V_ucI]) < Str_CurrentLimit.V_ulCurrentLimit_Low )
          || ( SF_ABS(GStr_HEX_VARREGTYPE.VRmsIRegHEX_ABC[V_ucI]) > Str_CurrentLimit.V_ulCurrentLimit_High ) )
		{
			*(pV_usCompTemp + V_ucI) = 0;
		}
	}
}

/***********************************************************************************
函数原型：void SF_EvenHarmonicCompensation( ushort16 *pV_usCompTemp, uchar8 V_ucRegAddress )
功能描述：进行各相偶次谐波进行补偿
输入参数：ushort16 *pV_usCompTemp, uchar8 V_ucRegAddress
输出参数：无
返回参数：无
功能说明：
调用机制：GV_EvenHarmonicFlag == C_DoEvenHarmonicFlag 开启偶次谐波补偿
备    注：偶次谐波含有量大于30%小于50%，表示处于偶次谐波状态
***********************************************************************************/
void SF_EvenHarmonicCompensation( ushort16 *pV_usCompTemp, uchar8 V_ucRegAddress )
{
	uchar8 V_ucI = 0;
	uchar8 V_ucDataBuff1[C_CalDataLen] = {0}, V_ucDataBuff2[C_CalDataLen] = {0}, V_ucDataLength = 0;
	short16 V_sCompData = 0;
	ushort16 V_usCalDataTemp = 0, V_usCompData = 0, V_usCalData = 0;
	/*进行偶次谐波补偿*/
	for (V_ucI = 0; V_ucI < 3; V_ucI ++)
	{
		/*获取E2内校表数据*/
		V_ucDataLength = C_CalDataLen;
		if ( InF_Read_RecMeterData( (V_ucRegAddress + V_ucI), &V_ucDataBuff1[0], &V_ucDataLength ) != C_OK )
		{
			continue;
		}

		PF_Buffer2ToUshort16( &V_ucDataBuff1[0], &V_usCalDataTemp);

		V_sCompData = (short16)*(pV_usCompTemp + V_ucI) + (short16)V_usCalDataTemp;

		V_usCompData = (ushort16)V_sCompData;

		PF_Ushort16ToBuffer2( &V_ucDataBuff1[0], &V_usCompData );

		/*校表数据写入计量芯之前，比较数据是否一致，一致则不再写入*/
		SF_ReadOneReg_MeterIC( (V_ucRegAddress + V_ucI), &V_ucDataBuff2[0], C_ReadCalDataRegFlag );

		PF_Buffer2ToUshort16( &V_ucDataBuff2[0], &V_usCalData );

		if (PF_Campare_Data( &V_ucDataBuff1[0], &V_ucDataBuff2[0], 2) != C_Equal )
		{
			SF_WriteOneReg_MeterIC( &V_ucDataBuff1[0], (V_ucRegAddress + V_ucI), C_DataSafe );

			if ( ( (V_ucRegAddress + V_ucI) > 0x03 ) && ( (V_ucRegAddress + V_ucI) < 0x13 ) )
			{
				GV_ulCalDataChk0SUM = GV_ulCalDataChk0SUM - V_usCalData + V_usCompData;		/*更新校验和*/
			}
			else if( ( (V_ucRegAddress + V_ucI) > 0x60 ) && ( (V_ucRegAddress + V_ucI) < 0x64 ) )
			{
				GV_ulCalDataChk1SUM = GV_ulCalDataChk1SUM - V_usCalData + V_usCompData;
			}
			else
			{
				GV_ulCalDataChk0SUM = ~GV_ulCalDataChk0SUM;
				GV_ulCalDataChk1SUM = ~GV_ulCalDataChk1SUM;
			}
		}
	}
}

/*******************************************************************************
函数原型: uchar8 SF_Test_MeterIC()
功能描述: 读取校表寄存器，对校表参数进行计算得出校验和数据，然后和寄存器中读取出的校验和数据进行对比，如果不正确，则置相应标志及初始化
输入参数: 无
输出参数: 无
返回参数: C_OK正常；C_Error异常
调用位置: 
备    注: 
*******************************************************************************/
uchar8 SF_Test_MeterIC()
{
	uchar8 V_ucreturnFlag;
	if (SF_Check_MeterIC() != C_OK)
	{
		GV_ucMeterICNum ++;
		GV_ucMeterICErrorFlag = C_MeterICError;
		GV_ucMeterICErrorTime = 0;
		if (GV_ucMeterICNum >= C_MeterICRstNum)
		{
			GV_ucMeterICNum = 0;
			InF_Initial_MeterIC();
		}
		V_ucreturnFlag = C_Error;
	}
	else
	{
		GV_ucMeterICErrorFlag = C_MeterICNormal;
		GV_ucMeterICNum = 0;
		GV_ucMeterICErrorNum = 0;
		V_ucreturnFlag = C_OK;
	}
	return V_ucreturnFlag;
}

/*******************************************************************************
函数原型: SF_Cal1minPowerSum(Str_PowerAdd_Type *pStr_PowerAdd, Str_RealtimePower_Type *pStr_RealtimePower)
功能描述: 1min功率累加和计算 
输入参数: Str_PowerAdd_Type *pStr_PowerAdd: 1min功率累加结构体
          Str_RealtimePower_Type *pStr_RealtimePower：实时功率结构体
输出参数: 无
返回参数: 无
调用位置: 
备    注: 每1s调用1次
*******************************************************************************/
void SF_Cal1minPowerSum(Str_PowerAdd_Type *pStr_PowerAdd, Str_RealtimePower_Type *pStr_RealtimePower)
{
	uchar8 V_uci;

	pStr_PowerAdd->Number++;
	for (V_uci = 0; V_uci < 4; V_uci++)
	{
	/*********************************总ABC有功功率处理**********************************************/
		pStr_PowerAdd->ActivePowerSummer_TABC[V_uci] += pStr_RealtimePower->ActivePower_TABC[V_uci];
		
	/*********************************总ABC无功功率处理**********************************************/
		pStr_PowerAdd->ReativePowerSummer_TABC[V_uci] += pStr_RealtimePower->ReativePower_TABC[V_uci];
	}
}

/*******************************************************************************
函数原型: void SF_Cal1minAveragePower(Str_PowerAdd_Type *pStr_PowerAdd)  
功能描述: 计算1min平均功率 
输入参数: Str_PowerAdd_Type *pStr_PowerAdd：1min功率累加结构体
输出参数: 无
返回参数: 无
调用位置: 
备    注: 系统分钟变化时调用，调用后，1min功率累加结构体数据清零
*******************************************************************************/
void SF_Cal1minAveragePower(Str_PowerAdd_Type *pStr_PowerAdd)
{
	uchar8 V_uci;
	long64 V_llPower;
	uchar8 V_ucBuffer[8];
	long64 *pV_lldata;
	ulong32 V_ulComDemandRAMAddeTable[C_PowerTypeNum] =
	{
		COneMin_AcPower_Pre,
		COneMin_AcPower_A_Pre,
		COneMin_AcPower_B_Pre,
		COneMin_AcPower_C_Pre,
		COneMin_RePower_Pre,
		COneMin_RePower_A_Pre,
		COneMin_RePower_B_Pre,
		COneMin_RePower_C_Pre
	};

	/*************************首先计算1min平均功率*****************************/
	pV_lldata = &pStr_PowerAdd->ActivePowerSummer_TABC[0];
	for (V_uci = 0; V_uci < C_PowerTypeNum; V_uci++)
	{
		if (pStr_PowerAdd->Number == 0)
		{
			V_llPower = 0;
		}
		else
		{
			V_llPower = *pV_lldata / pStr_PowerAdd->Number;
		}
		
		*pV_lldata = 0;			/*功率累加和清零*/
		pV_lldata++;

		PF_Ulong64ToBuffer8(V_ucBuffer, (ulong64 *)&V_llPower, 8);
		InF_Write_Data(C_Msg_MeterIC, V_ulComDemandRAMAddeTable[V_uci], V_ucBuffer, CLOneMin_AcPower, C_W_SafeFlag);
	}

    pStr_PowerAdd->Number = 0;	/*累计次数清零*/
}

/*******************************************************************************
函数原型: void SF_ClrCurrentPower(void)
功能描述: 将当前1分钟平均功率清零
输入参数: 无
输出参数: 无
返回参数: 无
调用位置: 
备    注: 
*******************************************************************************/
void SF_ClrCurrentPower(void)
{
	uchar8 V_ucData[CLOneMin_AcPower] = {0x00};
	uchar8 V_uci;
	ulong32 V_ulComDemandRAMAddeTable[C_PowerTypeNum] =
	{
		COneMin_AcPower_Pre,
		COneMin_AcPower_A_Pre,
		COneMin_AcPower_B_Pre,
		COneMin_AcPower_C_Pre,
		COneMin_RePower_Pre,
		COneMin_RePower_A_Pre,
		COneMin_RePower_B_Pre,
		COneMin_RePower_C_Pre
	};
	for (V_uci = 0; V_uci < C_PowerTypeNum; V_uci++)
	{
		InF_Write_Data(C_Msg_MeterIC, V_ulComDemandRAMAddeTable[V_uci], V_ucData, CLOneMin_AcPower, C_W_SafeFlag);
	} 
}

/**********************************************************************************************************************************
函数原型：uchar8 InF_Get_MeterICModule(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, ushort16 *pV_usDataEncode)
功能描述：读瞬时量接口
输入参数：V_ulOAD:需要读取的OAD；
          pV_ucDataBuf:读取数据的缓存的首地址
          *pV_usDataLen:读取数据的缓存的最大长度；
输出参数：pV_ucDataBuf:读取数据的缓存的首地址
          *pV_usDataLen:读取数据实际长度；
          *pV_usDataEncode:数据内部编码；
返回参数：C_OK,读取成功;其他错误;
调用位置：对象管理层
备    注：
************************************************************************************************************************************/
uchar8 InF_Get_MeterICModule(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, ushort16 *pV_usDataEncode)
{
	uchar8 V_uci, V_ucFlag = C_Error;
	ulong32 V_ulOneMin_AcPower[C_PowerTypeNum][2] = {{COneMin_AcPower,   COneMin_AcPower_Pre},	/*4位小数平均功率和6位小数平均功率*/
                                                     {COneMin_AcPower_A, COneMin_AcPower_A_Pre},
                                                     {COneMin_AcPower_B, COneMin_AcPower_B_Pre},
                                                     {COneMin_AcPower_C, COneMin_AcPower_C_Pre},
                                                     {COneMin_RePower,   COneMin_RePower_Pre},
                                                     {COneMin_RePower_A, COneMin_RePower_A_Pre},
                                                     {COneMin_RePower_B, COneMin_RePower_B_Pre},
                                                     {COneMin_RePower_C, COneMin_RePower_C_Pre}};
        
	ulong32 V_ulCurr_3ig[3][2] = {{CPhaseA_Curr,   CPhaseA_Curr_4Dig},	/*3位小数电流和4位小数电流*/
                                  {CPhaseB_Curr,   CPhaseB_Curr_4Dig},
                                  {CPhaseC_Curr,   CPhaseC_Curr_4Dig}};
    
	ulong32 V_ulFFTab[] = {CInstantFF_AcPow,			/*有功功率数据块*/
                           CInstantFF_RePow,			/*无功功率数据块*/
                           CInstantFF_AppaPow,		    /*瞬时视在功率数据块*/
                           CPhaseFF_Curr_4Dig,		    /*电流数据块*/
                           CPhaseFF_Volage,			    /*电压数据块*/
                           CPhaseFF_PowerFactor,		/*功率因数数据块*/
                           CPhaseFF_Angle,			    /*相角数据块*/
                           CVolFF_Phase,				/*电压相角数据块*/
                           CCurrFF_Phase,			    /*电流相角数据块*/
                           COneMin_AcPower_Pre_FF,      /*1分钟有功总平均功率数据块(6位小数)*/
                           COneMin_RePower_Pre_FF};     /*1分钟无功总平均功率数据块(6位小数)*/

	/*是否读3位小数电流，是的话从数据层读4位小数电流，再转化成3位小数*/
	for (V_uci = 0; V_uci < 3; V_uci++)
	{
		if (V_ulCurr_3ig[V_uci][0] == V_ulOAD)
		{
			V_ucFlag = InF_Read_Data(V_ulCurr_3ig[V_uci][1], pV_ucDataBuf, pV_usDataLen, pV_usDataEncode);
			SF_LessData(pV_ucDataBuf, 10);		/*数据缩小10倍*/
			return V_ucFlag;
		}
	}

	/*是否是数据层的瞬时量*/
	for (V_uci = 0; V_uci < C_InstantNum; V_uci++)
	{
		if (Str_DataProcess[V_uci].C_InstantOAD == V_ulOAD)   
		{
			V_ucFlag = InF_Read_Data(V_ulOAD, pV_ucDataBuf, pV_usDataLen, pV_usDataEncode);
			return V_ucFlag;
		}
	}

	/*是否是1min平均功率6位小数*/
	for (V_uci = 0; V_uci < C_PowerTypeNum; V_uci++)
	{
		if (V_ulOAD == V_ulOneMin_AcPower[V_uci][1])
		{
			V_ucFlag = InF_Read_Data(V_ulOAD, pV_ucDataBuf, pV_usDataLen, pV_usDataEncode);
			return V_ucFlag;
		}
	}

	/*是否是1min平均功率4位小数*/
	for (V_uci = 0; V_uci < C_PowerTypeNum; V_uci++)
	{
		if (V_ulOAD == V_ulOneMin_AcPower[V_uci][0])
		{
			V_ucFlag = InF_Read_Data(V_ulOneMin_AcPower[V_uci][1], pV_ucDataBuf, pV_usDataLen, pV_usDataEncode);
			if (V_ucFlag == C_OK)
			{ 
				SF_6digpowTo4digpow(pV_ucDataBuf);	/*6位小数转成4位小数，并四舍五入*/
			}
			return V_ucFlag;
		}
	}

	/*是否是正常的块抄读*/
	for (V_uci = 0; V_uci < (sizeof(V_ulFFTab)/sizeof(ulong32) ); V_uci++)
	{
		if (V_ulOAD == V_ulFFTab[V_uci])
		{
			V_ucFlag = InF_Read_Data(V_ulOAD, pV_ucDataBuf, pV_usDataLen, pV_usDataEncode);
			return V_ucFlag;
		}
	}

	/*3位小数电流块抄读*/
	if (V_ulOAD == CPhaseFF_Curr)
	{
		V_ucFlag = InF_Read_Data(CPhaseFF_Curr_4Dig, pV_ucDataBuf, pV_usDataLen, pV_usDataEncode);
		if (V_ucFlag == C_OK)
		{
			for (V_uci = 0; V_uci < 3; V_uci++)    /*ABC三相分别缩小10倍*/
			{
				SF_LessData(&pV_ucDataBuf[V_uci * CLPhaseA_Curr], 10);
			}
		}
		return V_ucFlag;
	}

	/*4位小数1min平均功率块抄读*/
	if ( (V_ulOAD == COneMin_AcPower_FF) || (V_ulOAD == COneMin_RePower_FF) )
	{
        if (V_ulOAD == COneMin_AcPower_FF)
        {
            V_ucFlag = InF_Read_Data(COneMin_AcPower_Pre_FF, pV_ucDataBuf, pV_usDataLen, pV_usDataEncode);
        }
        else
        {
            V_ucFlag = InF_Read_Data(COneMin_RePower_Pre_FF, pV_ucDataBuf, pV_usDataLen, pV_usDataEncode);
        }
		if (V_ucFlag == C_OK)
		{
			for (V_uci = 0; V_uci < 4; V_uci++)    /*TABC共4个*/
			{
				SF_6digpowTo4digpow(&pV_ucDataBuf[V_uci * COneMin_AcPower_Pre] );   /*6位小数转成4位小数，并四舍五入*/
			}
		}
		return V_ucFlag;
	}
	return V_ucFlag;
}

/**********************************************************************************************************************************
函数原型：void SF_LessData(uchar8 *pV_ucDataBuf, ushort16 V_ustemp)
功能描述：把缓存区里的数据缩小多少倍，暂时只支持4字节数据，用于读出来的4位小数电流转化成3位小数电流
输入参数：uchar8 *pV_ucDataBuf：要转化的数据首地址
          ushort16 V_ustemp:缩小多少倍
输出参数：uchar8 *pV_ucDataBuf：缩小后的数据首地址
返回参数：无
调用位置：
备    注：
************************************************************************************************************************************/
void SF_LessData(uchar8 *pV_ucDataBuf, ushort16 V_ustemp)
{
	long32 V_ldata;
	PF_BufferXToUlong32(pV_ucDataBuf, (ulong32 *)&V_ldata, 4);
	V_ldata /= V_ustemp;
	PF_Ulong32ToBufferX(pV_ucDataBuf, (ulong32 *)&V_ldata, 4);
}

/**********************************************************************************************************************************
函数原型：void SF_6digpowTo4digpow(uchar8 *pV_ucDataBuf)
功能描述：把6位小数的平均功率转化成4位小数的平均功率，并四舍五入
输入参数：uchar8 *pV_ucDataBuf：要转化的数据首地址
输出参数：uchar8 *pV_ucDataBuf：转化后的数据首地址
返回参数：无
调用位置：内部用于读出来的4位小数电流转化成3位小数电流
备    注：
************************************************************************************************************************************/
void SF_6digpowTo4digpow(uchar8 *pV_ucDataBuf)
{
	long32 V_ldata;
	PF_BufferXToUlong32(pV_ucDataBuf, (ulong32 *)&V_ldata, 4);
	if (V_ldata > 0)
	{
		if ( (V_ldata % 100) >= 50)				/*四舍五入*/
		{
			V_ldata += 100;
		}
	}
	else
	{
		if ( (SF_ABS(V_ldata) % 100) >= 50)		/*四舍五入*/
		{
			V_ldata -= 100;
		}
	}
	V_ldata /= 100;								/*保留4个小数位*/

	PF_Ulong32ToBufferX(pV_ucDataBuf, (ulong32 *)&V_ldata, 4);
}

/**********************************************************************************************************************************
函数原型：void Inf_deal_EvenHarmonicDelayTimer()
功能描述：在time.c模块50ms里进行递减
输入参数：无
输出参数：无
返回参数：无
调用位置：
备    注：
************************************************************************************************************************************/
void Inf_deal_EvenHarmonicDelayTimer()
{
	if( GV_ucEvenHarmonicDelayTimer != 0 )
	{
		GV_ucEvenHarmonicDelayTimer--;
	}
}
