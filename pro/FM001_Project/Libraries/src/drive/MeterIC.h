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
#ifndef	__MeterIC_H
#define	__MeterIC_H

/********************************静态变量设置*********************************************************/


uchar8 GV_ucWriteRegSafeFlag;									/*写计量芯片数据安全标志 写数据安全:C_DataSafe 写数据不安全:C_DataUnsafe*/
uchar8 GV_ucCalibrationState;									/*校表状态 处于校表状态:C_StartCalibrationOK  处于非校表状态C_CalibrationOK*/
uchar8 GV_ucCheckTime;											/*校表参数校验和校验和检验时间*/
uchar8 GV_ucUpdateTime;											/*更新数据层数据间隔时间*/
uchar8 GV_ucEnergyLock;											/*电能数据闭锁时间*/
uchar8 GV_ucMeterICErrorState;									/*计量芯片故障状态*/
uchar8 GV_ucMeterICErrorNum;									/*记录计量芯片故障发生计数*/
uchar8 GV_ucMeterICErrorTime;									/*记录计量芯片故障恢复计数*/
uchar8 GV_ucMeterICErrorFlag;									/*计量芯片故障标志 计量芯片故障:C_MeterICError 计量芯片正常C_MeterICNormal*/
uchar8 GV_ucMeterICNum;											/*计量芯片check错误次数，如果超过5次，则进行计量芯片复位，并且错误期间不更新瞬时量*/
ulong32 GV_ulCalDataChk0SUM;									/*CHECK0校验和*/
ulong32 GV_ulCalDataChk1SUM;									/*CHECK1校验和*/
uchar8  GV_ucPowerFactor_Flag@".DataProcessADDR";				/*奇次谐波补偿，功率因数是否符合条件标志*/
uchar8  GV_ucCurrent_Flag1@".DataProcessADDR";					/*奇次谐波补偿，电流是否符合条件标志(2.8-4A)*/
uchar8  GV_ucCurrent_Flag2@".DataProcessADDR";					/*奇次谐波补偿，电流是否符合条件标志(1.4-2A)*/
#define NOP()	__no_operation()

/**********************************数据层涵盖的所有参数原始值结构体*************************************************/
typedef struct
{
	ulong32 WATTReg[4];					/*总、A、B、C相有功功率 24bit*/
	ulong32 VARReg[4];					/*总、A、B、C相无功功率 24bit*/
	ulong32 VAReg[4];					/*总、A、B、C相视在功率 24bit*/
	ulong32 PfReg[4];					/*总分功率因数 24bit*/
	ulong32 VRmsVReg[3];				/*电压数据 24bit*/
	ulong32 VRmsIReg[3];				/*电流数据 24bit*/
	ulong32 IRmsN0;						/*三相电流矢量和 24bit*/
	ulong32 IRmsNOSample;				/*零线电流 24bit*/
	ulong32 FREQUENCY;					/*频率数据 16bit*/
	ulong32 YUIReg[3];					/*A、B、C功率平均相角*/
/*	ulong32 TempReg;*/					/*温度数据*/
	ulong32 YUReg[3];					/*A、B、C电压相角 */
	ulong32 YIReg[3];					/*ABC电流相角*/
}Str_VARREGTYPE_Type;
/*********************************功率系数RAM存储结构体************************************************/
typedef struct
{
	ulong64 PowerCoeffData;
	ushort16 Crc;
}Str_PowerCoeff_Type;
/********************************电能原始值结构体***************************************************/
typedef struct
{
	ushort16 V_ucActiveEnergy_TABC[4];
	ushort16 V_ucReactiveEnergy_TABC[4];
	ushort16 V_ucApparentEnergy_TABC[4];
}Str_EnergyData_Type;
/*********************************计量数据(数据层数据)HEX结构体**************************************************/
typedef struct
{
	long32 ActivePowerHEX_TABC[4];		/*总、A、B、C相有功功率 32bit*/
	long32 ReativePowerHEX_TABC[4];		/*总、A、B、C相无功功率 32bit*/
	long32 ApparentPowerHEX_TABC[4];	/*总A、B、C相视在功率 32bit*/
	long32 VRmsILSBRegHEX_ABC[3];		/*电流数据XXXX.XXXX 32bit*/ 
    long32 VRmsIRegHEX_ABC[3];			/*电流数据XXXXX.XXX 32bit*/
	long32 IRmsN0_HEX;					/*三相电流矢量和 16bit*/
	long32 IRmsNOSample_HEX;			/*零线电流 16bit*/    
	
	ushort16 VRmsVRegHEX_ABC[3];		/*电压数据 32bit*/
	short16 PowerFactorHEX_TABC[4];		/*总分功率因数 16bit*/
	ushort16 FREQUENCY_HEX;				/*频率数据 16bit*/
	ushort16 YUIRegHEX_ABC[3];			/*A、B、C功率平均相角*/
/*	ushort16 TempReg_HEX;*/				/*温度数据*/
	ushort16 YURegHEX_ABC[3];			/*A、B、C电压相角 */
	ushort16 YIRegHEX_ABC[3];			/*A、B、C电流相角*/
}Str_HEX_VARREGTYPE_Type;
/*********************************相角数据真实值(xxx.x°)**************************************************/
typedef struct
{
	ulong32 YUIRealData_ABC[3];
	ulong32 YURealData_ABC[3];
	ulong32 YIRealData_ABC[3];
}Str_RealAngleData_Type;
	
/********************************宏定义*********************************************************/
#define C_EnWriteCalDataMeterIC					0xC900005A		/*写校表参数使能计量芯片*/
#define C_DisWriteCalDataMeterIC				0xC9000000		/*写校表参数失能计量芯片*/
#define C_EnReadCalDataMeterIC					0xC600005A		/*读校表数据使能计量芯片*/
#define C_EnReadMeaDataMeterIC					0xC6000000		/*读计量参数使能计量芯片*/

#define C_MeterICDataLEN						4				/*使能计量芯片数据长度*/

#define C_DELAY1US								0x00000001		/*延时1微秒*/
#define C_DELAY2US								0x00000002		/*延时2微秒*/
#define C_DELAY4US								0x00000007		/*延时4微秒*/
#define C_DELAY25MS								0x0000DDF0		/*延时25毫秒*/
#define C_DELAY25MSPowerDown					0x00006A00		/*低功耗下延时25毫秒*/
#define C_DELAY1MS								0x00000900		/*延时1毫秒*/
#define C_DELAY1MSPowerDown						0x000002A0		/*低功耗下延时1毫秒*/

#define C_WriteDataMeterIC						0x80			/*用于写数据时将写入数据寄存器地址首字节置1:|=C_WriteDataMeterIC*/
#define C_ReadDataMeterIC						0x7F			/*用于读数据时将写入数据寄存器地址首字节置0:&=C_ReadDataMeterIC*/
#define C_DataSafe								0x86			/*计量芯片写入数据安全*/
#define C_DataUnsafe							0x68			/*计量芯片写入数据不安全*/
#define C_ReadMeaDataRegFlag					0x00			/*将寄存器读取模式设置成读取计量参数寄存器*/
#define C_ReadCalDataRegFlag					0x01			/*将寄存器读取模式设置成读取校表参数寄存器*/

#define C_ModeCfg_Data					 		0xB97F			/*模式相关控制数据（开启零线电流）*/
#define C_PorDownModeCfg_Data					0xB97F			/*低功耗下模式相关控制数据（开启零线电流）*/

#define C_ModuleCFG_Data						0x3437			/*电路模块配置寄存器*/
#define C_Iregion1_Data							240				/**/
#define C_Iregion0_Data							2784			/**/

#define C_CalDataLen							3				/*校表参数数据长度*/
#define C_MeaDataLen							3				/*计量参数长度*/
#define C_DispatchMsgLen						2				/*调度消息数据长度*/

#define C_CheckTime								5				/*校表参数校验和校验和检验间隔时间*/
#define C_UpdateTime							3				/*上电初始化时计量芯片的闭锁时间：1.5s（基于500ms）*/
#define C_MAXRepeatTime							20				/*最大循环间隔时间*/
#define C_RepeatTime							2				/*校表参数、校验和校验、更新数据层循环间隔时间*/
#define C_MeterICErrorTime						10				/*计量芯片有效故障时间间隔阀值LSB=500mS*/
#define C_MeterICRecoverTime					20				/*计量芯片恢复时间阀值LSB=500mS*/

#define C_MeterICErrorNum						2				/*计量芯片故障状态字判断用有效故障数阀值*/
#define C_MeterICErrorFlag						254				/*计量芯片处于故障状态*/
#define C_MeterICErrorState						0x01			/*计量芯片故障状态字置为故障V_Data|=*/
#define C_MeterICRecoverState					0xFE			/*计量芯片故障状态字置为正常V_Data&=*/

#define C_OneByteLen							1				/*一字节长度*/
#define C_TwoByteLen							2				/*两字节长度*/
#define C_FourByteLen							4				/*四字节长度*/

#define C_VoltageThreshold						20				/*电压阀值(X.X V)*/
#define C_VoltageThreshold220					80				/*电压阀值(X.X V)，220、380V灭零，8V*/
#define C_CurrentThreshold						15				/*电流阀值(X.XXX A)*/
#define C_PowerFactor							1000			/*功率因数默认值*/
#define C_PowerFactorThreshold					995				/*功率因数阀值*/
#define C_FrequencyThreshold					4999			/*频率阀值*/
#define C_FrequencyData							5000			/*频率默认值*/

#define C_PowerFlag_T							0x55			/*总功率标志*/
#define C_PowerFlag_ABC							0xAA			/*分相功率标志*/

#define C_PowerHexLen							3 				/*功率数据Hex数据字节长度*/
#define C_VoltageHexLen							3				/*电压数据Hex数据字节长度*/
#define C_CurrentHexLen							3				/*电流数据Hex数据字节长度*/
#define C_PowerFactorHexLen						3				/*功率因数数据Hex数据字节长度*/
#define C_NOCurrentHexLen						3				/*零线电流数据Hex数据字节长度*/
#define C_FrequencyHexLen						3 				/*电网频率数据Hex数据字节长度*/
#define C_PhaseAngleHexLen						3 				/*平均功率相角数据Hex数据字节长度*/
#define C_TemperatureHexLen						3 				/*温度数据Hex数据字节长度*/

#define C_Ib0_3A								0x00			/*电能表基本电流为Ib=0.3A*/
#define C_Ib1A									0x01			/*电能表基本电流为Ib=1A*/
#define C_Ib1_5A								0x02			/*电能表基本电流为Ib=1.5A*/
#define C_Ib5A									0x03			/*电能表基本电流为Ib=5A*/
#define C_Ib10A									0x04			/*电能表基本电流为Ib=10A*/
#define C_Ib15A									0x05			/*电能表基本电流为Ib=15A*/
#define C_Ib20A									0x06			/*电能表基本电流为Ib=20A*/
#define C_Ib30A									0x07			/*电能表基本电流为Ib=30A*/

#define C_N0_3A									1000			/*Ib=0.3A时的比例系数*/
#define C_N1A									300				/*Ib=1A时的比例系数*/
#define C_N1_5A									200				/*Ib=1.5A时的比例系数*/
#define C_N5A									60				/*Ib=5A时的比例系数*/
#define C_N10A									30				/*Ib=10A时的比例系数*/
#define C_N15A									20				/*Ib=15A时的比例系数*/
#define C_N20A									15				/*Ib=20A时的比例系数*/
#define C_N30A									10				/*Ib=30A时的比例系数*/

#define C_AngleMAXData							1800			/*相角数据最大值XXX.X 一位小数*/
#define C_AngleMAXRealData						3600			/*相角数据实际最大值XXX.X 一位小数*/
#define C_InitialMsgDataLen						0x01			/*初始化消息数据长度*/
#define C_MAXPulse								20				/*最大电能脉冲数*/

#define C_PhaseLossFlag							0x01			/*电压或者电流断相标志*/
#define C_NoPhaseLossFlag						0x00			/*无电压或者电流断相标志*/
#define C_InitPowerDown							0x00			/*低功耗下初始化计量芯片标志*/
#define C_InitNormal							0x01			/*正常模式下初始化计量芯片标志*/

#define C_Phase_A								0x00			/*A相标示，用于电压符号显示函数用*/
#define C_Phase_B								0x01			/*B相标示，用于电压符号显示函数用*/
#define C_Phase_C								0x02			/*C相标示，用于电压符号显示函数用*/

#define C_Reverse_Ia							0x01			/*A相电流符号方向判断*/
#define C_Reverse_Ib							0x02			/*B相电流符号方向判断*/
#define C_Reverse_Ic							0x04			/*C相电流符号方向判断*/

#define C_PQsign2								0x08			/*象限判断时使用*/
#define C_PQsign3								0x88			/*象限判断时使用*/
#define C_PQsign4								0x80			/*象限判断时使用*/

#define C_ReverseCurr4Dig						0x80000000		/*电流数据4位小数电流BCD数据增加负号*/
#define C_ReverseCurr3Dig						0x00800000		/*电流数据3位小数电流BCD数据增加负号*/
#define C_ReversePower3Dig						0x00800000		/*功率数据增加负号*/

#define C_PowerT								0x00			/*视在功率计算时用到*/
#define C_PowerA								0x01			/*视在功率计算时用到*/
#define C_PowerB								0x02			/*视在功率计算时用到*/
#define C_PowerC								0x03			/*视在功率计算时用到*/

#define C_PTplus								0xFFEF			/*总有功功率方向正，用于电表运行状态特征字1*/
#define C_PTminus								0x0010			/*总有功功率方向负*/
#define C_QTplus								0xFFDF			/*总无功功率方向正*/
#define C_QTminus								0x0020			/*总无功功率方向负*/

#define C_PAplus								0xFFFE			/*A相有功功率方向正，用于电表运行状态特征字2*/
#define C_PAminus								0x0001			/*A相有功功率方向负*/
#define C_PBplus								0xFFFD			/*B相有功功率方向正*/
#define C_PBminus								0x0002			/*B相有功功率方向负*/
#define C_PCplus								0xFFFB			/*C相有功功率方向正*/
#define C_PCminus								0x0004			/*C相有功功率方向负*/
#define C_QAplus								0xFFEF			/*A相无功功率方向正*/
#define C_QAminus								0x0010			/*A相无功功率方向负*/
#define C_QBplus								0xFFDF			/*B相无功功率方向正*/
#define C_QBminus								0x0020			/*B相无功功率方向负*/
#define C_QCplus								0xFFBF			/*C相无功功率方向正*/
#define C_QCminus								0x0040			/*C相无功功率方向负*/

#define C_ActiveEnergyT_Plus					0xF7			/*电能读取结构体有功电能总-正号*/
#define C_ActiveEnergyT_Minus					0x08			/*电能读取结构体有功电能总-负号*/
#define C_ActiveEnergyA_Plus					0xFE			/*电能读取结构体有功电能A相-正号*/
#define C_ActiveEnergyA_Minus					0x01			/*电能读取结构体有功电能A相-负号*/
#define C_ActiveEnergyB_Plus					0xFD			/*电能读取结构体有功电能B相-正号*/
#define C_ActiveEnergyB_Minus					0x02			/*电能读取结构体有功电能B相-负号*/
#define C_ActiveEnergyC_Plus					0xFB			/*电能读取结构体有功电能C相-正号*/
#define C_ActiveEnergyC_Minus					0x04			/*电能读取结构体有功电能C相-负号*/
#define C_ReactiveEnergyT_Plus					0x7F			/*电能读取结构体无功电能总-正号*/
#define C_ReactiveEnergyT_Minus					0x80			/*电能读取结构体无功电能总-负号*/
#define C_ReactiveEnergyA_Plus					0xEF			/*电能读取结构体无功电能A相-正号*/
#define C_ReactiveEnergyA_Minus					0x10			/*电能读取结构体无功电能A相-负号*/
#define C_ReactiveEnergyB_Plus					0xDF			/*电能读取结构体无功电能B相-正号*/
#define C_ReactiveEnergyB_Minus					0x20			/*电能读取结构体无功电能B相-负号*/
#define C_ReactiveEnergyC_Plus					0xBF			/*电能读取结构体无功电能C相-正号*/
#define C_ReactiveEnergyC_Minus					0x40			/*电能读取结构体无功电能C相-负号*/
#define C_DirectionType							0x80000000		/*用于功率方向判断*/
#define C_NODirectionType						0x7FFFFFFF		/*消除功率数据首位符号位*/
#define C_NOSign_3Byte   						0x007FFFFF		/*去除3字节的符号位*/

#define C_EnergyLock							0x00			/*电能锁定不可读*/
#define C_EnergyUnlock							0x01			/*电能解锁可读取*/

#define C_TP									25				/*温度校正基准温度*/

#define C_MeterICError				0x01						/*计量芯片处于故障状态*/
#define C_MeterICNormal				0x00						/*计量芯片处于正常状态*/
#define C_MeterICRstNum				5							/*计量芯片出现5次Check错误才进行复位*/

#define C_Odd_Harmonic_3TimesFitCon			0x07				/*奇次谐波补偿滑差判断，3次均符合条件标志*/
#define C_Odd_Harmonic_CurrentFitFlag1		0x01				/*奇次谐波补偿，电流判断条件1标志(2.8-4A)*/
#define C_Odd_Harmonic_CurrentFitFlag2		0x02				/*奇次谐波补偿，电流判断条件2标志(1.4-2A)*/

#define C_EvenHarmonicCompensationTime		24*60				/*24h*60min*/

/********************************offset自动补偿数据定义*********************************************************/
#define C_Check0RetData		0x016F1F	/*check0检验和初始数据:包括程序中固定值写入的数据和不做处理的数据（开启零线电流）*/

#define C_VrefAotu			0x00		/*0x00:开启补偿，0x01:关闭补偿*/
#define C_Vref2_Data		0xFF12		/*参考电压补偿2次系数*/
#define C_Vref1_Data		0x5819		/*参考电压补偿1次系数*/
#define C_VrefC_Data		0xEF18		/*参考电压补偿常数项*/
#define C_Check1RetData		0			/*REF+外围 check1检验和初始数据:包括程序中固定值写入的数据和不做处理的数据.后校验和计算*/

#define C_Allgain_EnTemp	0xFFDC		/*使能温度补偿，防止溢出温度跳变*/
#define C_Allgain_DisTemp	0			/*关闭温度补偿，采用默认值0*/

#define C_VrefAotu_En		0x02		/*使能温度补偿*/
#define C_VrefAotu_Dis		0x00		/*关闭温度补偿*/
#define C_TempOverData		-35			/*温度保护溢出值*/


/********************************计量参数寄存器地址*********************************************************/
#define C_DeviceIDReg							0x00			/*计量芯片驱动身份编码*/
#define C_ActivePowerA_Reg						0x01			/*A相有功功率寄存器地址*/
#define C_ActivePowerB_Reg						0x02			/*B相有功功率寄存器地址*/
#define C_ActivePowerC_Reg						0x03			/*C相有功功率寄存器地址*/
#define C_ActivePowerT_Reg						0x04			/*合相有功功率寄存器地址*/
#define C_ReativePowerA_Reg						0x05			/*A相无功功率寄存器地址*/
#define C_ReativePowerB_Reg						0x06			/*B相无功功率寄存器地址*/
#define C_ReativePowerC_Reg						0x07			/*C相无功功率寄存器地址*/
#define C_ReativePowerT_Reg						0x08			/*合相无功功率寄存器地址*/
#define C_ApparentPowerA_Reg					0x09			/*A相视在功率寄存器地址*/
#define C_ApparentPowerB_Reg					0x0A			/*B相视在功率寄存器地址*/
#define C_ApparentPowerC_Reg					0x0B			/*C相视在功率寄存器地址*/
#define C_ApparentPowerT_Reg					0x0C			/*合相视在功率寄存器地址*/
#define C_VRmsVReg_AReg							0x0D			/*A相电压寄存器地址*/
#define C_VRmsVReg_BReg							0x0E			/*B相电压寄存器地址*/
#define C_VRmsVReg_CReg							0x0F			/*C相电压寄存器地址*/
#define C_VRmsIReg_AReg							0x10			/*A相电流寄存器地址*/
#define C_VRmsIReg_BReg							0x11			/*B相电流寄存器地址*/
#define C_VRmsIReg_CReg							0x12			/*C相电流寄存器地址*/
#define C_IRmsN0_Reg							0x13			/*三相电流矢量和有效值*/
#define C_PowerFactor_AReg						0x14			/*A相功率因数寄存器地址*/
#define C_PowerFactor_BReg						0x15			/*B相功率因数寄存器地址*/
#define C_PowerFactor_CReg						0x16			/*C相功率因数寄存器地址*/
#define C_PowerFactor_TReg						0x17			/*合相功率因数寄存器地址*/
#define C_YUIAngle_AReg							0x18			/*A相电流与电压相角寄存器地址*/
#define C_YUIAngle_BReg							0x19			/*B相电流与电压相角寄存器地址*/
#define C_YUIAngle_CReg							0x1A			/*C相电流与电压相角寄存器地址*/
#define C_INTFlag_Reg							0x1B			/*中断标志，读后清零*/
#define C_FREQUENCY_Reg							0x1C			/*电网频率寄存器地址*/
#define C_EnergyRegState_Reg					0x1D			/*电能寄存器工作状态寄存器，用于监视电能寄存器是否有溢出 溢出为1 默认为0 读后清零*/
#define C_ActiveEnergy_AReg						0x1E			/*有功A相电能数据*/
#define C_ActiveEnergy_BReg						0x1F			/*有功B相电能数据*/
#define C_ActiveEnergy_CReg						0x20			/*有功C相电能数据*/
#define C_ActiveEnergy_TReg						0x21			/*有功合相电能数据*/
#define C_ReativeEnergy_AReg					0x22			/*无功A相电能数据*/
#define C_ReativeEnergy_BReg					0x23			/*无功B相电能数据*/
#define C_ReativeEnergy_CReg					0x24			/*无功C相电能数据*/
#define C_ReativeEnergy_TReg					0x25			/*无功合相电能数据*/
#define C_YUAngle_AReg							0x26			/*A相电压相角寄存器地址*/
#define C_YUAngle_BReg							0x27			/*B相电压相角寄存器地址*/
#define C_YUAngle_CReg							0x28			/*C相电压相角寄存器地址*/
#define C_IORms_Reg								0x29			/*零线电流IO采样通道有效值*/
#define C_TempReg_Reg							0x2A			/*温度寄存器地址*/
#define C_VRmsNO_Reg							0x2B			/*三相电压矢量和有效值*/
#define C_SFlag_Reg								0x2C			/*存放断相、相序、SIG等标志状态(B0=1:A相失压;B1=1:B相失压;B2=1:C相失压;B3=1:电压相序错;B4=1:电流相序错;B5=1:至少有一相有功功率为负;B6=1:至少有一相无功功率为负;B7=1:^^^^^*/
#define C_TheLastData_Reg						0x2D			/*计量芯片上一次SPI通讯数据备份寄存器地址*/
#define C_ComChkSum_Reg							0x2E			/*通讯校验和寄存器*/
#define C_ADCDataSample_IAReg					0x2F			/*A相电流通道ADC采样数据*/
#define C_ADCDataSample_IBReg					0x30			/*B相电流通道ADC采样数据*/
#define C_ADCDataSample_ICReg					0x31			/*C相电流通道ADC采样数据*/
#define C_ADCDataSample_VAReg					0x32			/*A相电压通道ADC采样数据*/
#define C_ADCDataSample_VBReg					0x33			/*B相电压通道ADC采样数据*/
#define C_ADCDataSample_VCReg					0x34			/*C相电压通道ADC采样数据*/
#define C_ApparentEnergy_AReg					0x35			/*视在A相电能数据*/
#define C_ApparentEnergy_BReg					0x36			/*视在B相电能数据*/
#define C_ApparentEnergy_CReg					0x37			/*视在C相电能数据*/
#define C_ApparentEnergy_TReg					0x38			/*视在总电能数据*/
#define C_FastCnt_AReg							0x39			/*A相快速脉冲计数*/
#define C_FastCnt_BReg							0x3A			/*B相快速脉冲计数*/
#define C_FastCnt_CReg							0x3B			/*C相快速脉冲计数*/
#define C_FastCnt_TReg							0x3C			/*合相快速脉冲计数*/
#define C_PowerFlag_Reg							0x3D			/*有功/无功功率方向，正向为0，反向为1*/
#define C_CheckSum_Reg							0x3E			/*校表数据校验和(校验和是从地址0x01~0x39的所有校表数据之和，采用无符号方式累加，且只保留低24位)*/
#define C_IRmsNOSample_Reg						0x3F			/*零线电流IO通道采样数据输出*/
#define C_LinePa_Reg							0x40			/*A相基波有功功率*/
#define C_LinePb_Reg							0x41			/*B相基波有功功率*/
#define C_LinePc_Reg							0x42			/*C相基波有功功率*/
#define C_LinePt_Reg							0x43			/*合相基波有功功率*/
#define C_LineEpa_Reg							0x44			/*A相基波有功电能*/
#define C_LineEpb_Reg							0x45			/*B相基波有功电能*/
#define C_LineEpc_Reg							0x46			/*C相基波有功电能*/
#define C_LineEpt_Reg							0x47			/*合相基波有功电能*/
#define C_LineUaRrms_Reg						0x48			/*基波A相电压有效值*/
#define C_LineUbRrms_Reg						0x49			/*基波B相电压有效值*/
#define C_LineUcRrms_Reg						0x4A			/*基波C相电压有效值*/
#define C_LineIaRrms_Reg						0x4B			/*基波A相电流有效值*/
#define C_LineIbRrms_Reg						0x4C			/*基波B相电流有效值*/
#define C_LineIcRrms_Reg						0x4D			/*基波C相电流有效值*/
#define C_LEFlag_Reg							0x4E			/*基波电能寄存器的工作状态，读后清零*/
#define C_SAGFlag_Reg							0x4F			/*SAG标志寄存器*/
#define C_PeakUa_Reg							0x50			/*A相电压最大值*/
#define C_PeakUb_Reg							0x51			/*B相电压最大值*/
#define C_PeakUc_Reg							0x52			/*C相电压最大值*/
#define C_LineQa_Reg							0x57			/*A相基波无功功率*/
#define C_LineQb_Reg							0x58			/*B相基波无功功率*/
#define C_LineQc_Reg							0x59			/*C相基波无功功率*/
#define C_LineQt_Reg							0x5A			/*合相基波无功功率*/
#define C_Vrefgain_Reg							0x5C			/*Vref自动补偿系数*/
#define C_ChipID_Reg							0x5D			/*芯片版本指示寄存器*/
#define C_ChkSum1_Reg							0x5E			/*新增校表寄存器校验和(0x60~0x70)*/
#define C_PtrWavebuff_Reg						0x7E			/*缓冲数据指针，只是内部缓冲buffer已有数据长度*/
#define C_WaveBuff_Reg							0x7F			/*缓冲数据寄存器，内部自增益，重复读取直至读完缓冲数据长度*/
/********************************校表参数寄存器地址*********************************************************/
#define C_Reserved_Reg							0x00			/*校表参数寄存器起始标志*/
#define C_ModeCfg_Reg							0x01			/*模式相关控制*/
#define C_PGACtrl_Reg							0x02			/*ADC增益配置*/
#define C_EMUCfg_Reg							0x03			/*EMU单位配置*/
#define C_PgainA_Reg							0x04			/*A相有功功率增益*/
#define C_PgainB_Reg							0x05			/*B相有功功率增益*/
#define C_PgainC_Reg							0x06			/*C相有功功率增益*/
#define C_QgainA_Reg							0x07			/*A相无功功率增益*/
#define C_QgainB_Reg							0x08			/*B相无功功率增益*/
#define C_QgainC_Reg							0x09			/*C相无功功率增益*/
#define C_SgainA_Reg							0x0A			/*A相视在功率增益*/
#define C_SgainB_Reg							0x0B			/*B相视在功率增益*/
#define C_SgainC_Reg							0x0C			/*C相视在功率增益*/
#define C_PhSregApq0_Reg						0x0D			/*A相相位校正0*/
#define C_PhSregBpq0_Reg						0x0E			/*B相相位校正0*/
#define C_PhSregCpq0_Reg						0x0F			/*C相相位校正0*/
#define C_PhSregApq1_Reg						0x10			/*A相相位校正1*/
#define C_PhSregBpq1_Reg						0x11			/*B相相位校正1*/
#define C_PhSregCpq1_Reg						0x12			/*C相相位校正1*/
#define C_PoffsetA_Reg							0x13			/*A相有功功率Offset校正*/
#define C_PoffsetB_Reg							0x14			/*B相有功功率Offset校正*/
#define C_PoffsetC_Reg							0x15			/*C相有功功率Offset校正*/
#define C_QPhscal_Reg							0x16			/*无功相位校正*/
#define C_UgainA_Reg							0x17			/*A相电压增益*/
#define C_UgainB_Reg							0x18			/*B相电压增益*/
#define C_UgainC_Reg							0x19			/*C相电压增益*/
#define C_IgainA_Reg							0x1A			/*A相电流增益*/
#define C_IgainB_Reg							0x1B			/*B相电流增益*/
#define C_IgainC_Reg							0x1C			/*C相电流增益*/
#define C_Istarup_Reg							0x1D			/*起动电流阀值设置*/
#define C_Hfconst_Reg							0x1E			/*高频脉冲输出设置*/
#define C_FailVoltage_Reg						0x1F			/*失压阀值设置*/
#define C_GainADC7_Reg							0x20			/*第七路ADC输入信号增益*/
#define C_QoffsetA_Reg							0x21			/*A相无功功率offset校正*/
#define C_QoffsetB_Reg							0x22			/*B相无功功率offset校正*/
#define C_QoffsetC_Reg							0x23			/*C相无功功率offset校正*/
#define C_UaRmsoffset_Reg						0x24			/*A相电压有效值offset校正*/
#define C_UbRmsoffset_Reg						0x25			/*B相电压有效值offset校正*/
#define C_UcRmsoffset_Reg						0x26			/*C相电压有效值offset校正*/
#define C_IaRmsoffset_Reg						0x27			/*A相电流有效值offset校正*/
#define C_IbRmsoffset_Reg						0x28			/*B相电流有效值offset校正*/
#define C_IcRmsoffset_Reg						0x29			/*C相电流有效值offset校正*/
#define C_UoffsetA_Reg							0x2A			/*A相电压通道ADC offset校正*/
#define C_UoffsetB_Reg							0x2B			/*B相电压通道ADC offset校正*/
#define C_UoffsetC_Reg							0x2C			/*C相电压通道ADC offset校正*/
#define C_IoffsetA_Reg							0x2D			/*A相电流通道ADC offset校正*/
#define C_IoffsetB_Reg							0x2E			/*B相电流通道ADC offset校正*/
#define C_IoffsetC_Reg							0x2F			/*C相电流通道ADC offset校正*/
#define C_EMUIE_Reg								0x30			/*中断使能*/
#define C_ModuleCFG_Reg							0x31			/*电路模块配置寄存器*/
#define C_AllGain_Reg							0x32			/*全通道增益，用于Vref的温度校正*/
#define C_HFDouble_Reg							0x33			/*脉冲常数加倍选择*/
#define C_LineGain_Reg							0x34			/*基波增益校正*/
#define C_PinCtrl_Reg							0x35			/*数字pin上下拉电阻选择控制*/
#define C_Pstart_Reg							0x36			/*起动功率设置寄存器*/
#define C_Iregion0_Reg							0x37			/*相位补偿区域设置寄存器0*/
#define C_Cyclengrh_Reg							0x38			/*SAG数据长度设置寄存器*/
#define C_SAGLel_Reg							0x39			/*SAG检测阀值设置寄存器*/
#define C_Iregion1_Reg							0x60			/*相位补偿区域设置寄存器1*/
#define C_PhSregApq2_Reg						0x61			/*A相相位校正2*/
#define C_PhSregBpq2_Reg						0x62			/*B相相位校正2*/
#define C_PhSregCpq2_Reg						0x63			/*C相相位校正2*/
#define C_PoffsetAL_Reg							0x64			/*A相有功功率offset校正低字节*/
#define C_PoffsetBL_Reg							0x65			/*B相有功功率offset校正低字节*/
#define C_PoffsetCL_Reg							0x66			/*C相有功功率offset校正低字节*/
#define C_QoffsetAL_Reg							0x67			/*A相无功功率offset校正低字节*/
#define C_QoffsetBL_Reg							0x68			/*B相无功功率offset校正低字节*/
#define C_QoffsetCL_Reg							0x69			/*C相无功功率offset校正低字节*/
#define C_ItRmsoffset_Reg						0x6A			/*电流矢量和offset校正寄存器*/
#define C_TPSoffset_Reg							0x6B			/*TPS初值校正寄存器*/
#define C_TPSgain_Reg							0x6C			/*TPS斜率校正寄存器*/
#define C_TCcoffA_Reg							0x6D			/*Verfgain的二次系数*/
#define C_TCcoffB_Reg							0x6E			/*Verfgain的一次系数*/
#define C_TCcoffC_Reg							0x6F			/*Verfgain的常数项*/
#define C_EMCfg_Reg								0x70			/*新增算法控制寄存器*/
#define C_OILVL_Reg								0x71			/*过流阀值设置寄存器*/
#define C_NT_Reg								0xFE			/*不需要写寄存器*/
/**********************************计量芯片电能数据寄存器地址*******************************************************/
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
#define C_EnergyRegADDrTol						(sizeof(Str_EnergyRegADDr)/sizeof(uchar8))		/*电能数据寄存器总数*/

/**********************************计量芯片功率数据寄存器地址*******************************************************/
const uchar8 Str_PowerRegADDr[]=
{
	C_ActivePowerT_Reg,
	C_ActivePowerA_Reg,
	C_ActivePowerB_Reg,
	C_ActivePowerC_Reg,
	C_ReativePowerT_Reg,
	C_ReativePowerA_Reg,
	C_ReativePowerB_Reg,
	C_ReativePowerC_Reg,
	C_ApparentPowerT_Reg,
	C_ApparentPowerA_Reg,
	C_ApparentPowerB_Reg,
	C_ApparentPowerC_Reg
};
#define C_PowerRegADDrTol						(sizeof(Str_PowerRegADDr)/sizeof(uchar8))	/*功率数据寄存器总数*/

/*********************************计量参数寄存器地址**************************************************/
const ushort16 Str_VariableRegADDr[11]=
{
	C_PowerFactor_TReg,
	C_PowerFactor_AReg,
	C_PowerFactor_BReg,
	C_PowerFactor_CReg,
	C_FREQUENCY_Reg,
	C_YUIAngle_AReg,
	C_YUIAngle_BReg,
	C_YUIAngle_CReg,
/*	C_TempReg_Reg,*/
	C_YUAngle_AReg,
	C_YUAngle_BReg,
	C_YUAngle_CReg
};
/********************************电压寄存器地址***************************************************/
const ushort16 Str_UrmsRegADDr[]=
{
	C_VRmsVReg_AReg,
	C_VRmsVReg_BReg,
	C_VRmsVReg_CReg
};
#define C_UrmsRegADDrTol					(sizeof(Str_UrmsRegADDr)/sizeof(ushort16))				/*电压寄存器总数*/

/********************************电流寄存器地址***************************************************/
const ushort16 Str_IrmsRegADDr[]=
{
	C_VRmsIReg_AReg,
	C_VRmsIReg_BReg,
	C_VRmsIReg_CReg,
};
#define C_IrmsRegADDrTol					(sizeof(Str_IrmsRegADDr)/sizeof(ushort16))				/*电流寄存器总数*/

/******************************数据层所有瞬时量参数数据标识码和长度****************************************************/
typedef struct
{
	ulong32 C_InstantOAD;    /*瞬时量的OAD*/
	uchar8  CL_InstantOAD;   /*瞬时量OAD的长度*/

}Str_DataProcess_Type;

const Str_DataProcess_Type Str_DataProcess[]=
{
	{CInstant_TolAcPow, CLInstant_TolAcPow},
	{CInstantA_AcPow,   CLInstantA_AcPow},
	{CInstantB_AcPow,   CLInstantB_AcPow},
	{CInstantC_AcPow,   CLInstantC_AcPow},

	{CInstant_TolRePow, CLInstant_TolRePow},
	{CInstantA_RePow,   CLInstantA_RePow},
	{CInstantB_RePow,   CLInstantB_RePow},
	{CInstantC_RePow,   CLInstantC_RePow},

	{CInstant_TolAppaPow,CLInstant_TolAppaPow},
	{CInstantA_AppaPow,  CLInstantA_AppaPow},
	{CInstantB_AppaPow,  CLInstantB_AppaPow},
	{CInstantC_AppaPow,  CLInstantC_AppaPow},
	
	{CPhaseA_Curr_4Dig, CLPhaseA_Curr_4Dig},
	{CPhaseB_Curr_4Dig, CLPhaseB_Curr_4Dig},
	{CPhaseC_Curr_4Dig, CLPhaseC_Curr_4Dig},

    {CPhaseA_Curr,   CLPhaseA_Curr},
    {CPhaseB_Curr,   CLPhaseB_Curr},
    {CPhaseC_Curr,   CLPhaseC_Curr},
	
	{CVector_Current, CLVector_Current},		/*三相电流矢量和*/
	{CZero_Current,   CLZero_Current},			/*零线电流*/
	
	{CPhaseA_Volage,  CLPhaseA_Volage},
	{CPhaseB_Volage,  CLPhaseB_Volage},
	{CPhaseC_Volage,  CLPhaseC_Volage},
	
	{CTol_PowerFactor,    CLTol_PowerFactor},
	{CPhaseA_PowerFactor, CLPhaseA_PowerFactor},
	{CPhaseB_PowerFactor, CLPhaseB_PowerFactor},
	{CPhaseC_PowerFactor, CLPhaseC_PowerFactor},
	
	{CElecNet_Freq, CLElecNet_Freq},
	
	{CPhaseA_Angle, CLPhaseA_Angle},
	{CPhaseB_Angle, CLPhaseB_Angle},
	{CPhaseC_Angle, CLPhaseC_Angle},
	
/*	CMeter_Temp,*/
	
	{CVolA_Phase, CLVolA_Phase},
	{CVolB_Phase, CLVolB_Phase},
	{CVolC_Phase, CLVolC_Phase},
	
	{CCurrA_Phase, CLCurrA_Phase},
	{CCurrB_Phase, CLCurrB_Phase},
	{CCurrC_Phase, CLCurrC_Phase},

	/*zlj，注意以上需和Str_HEX_VARREGTYPE_Type一一对应，写数据层时必须一一对应*/
};

/*上面这些瞬时量Str_DataProcess[]的偏移，必须和Str_DataProcess[]一一对应*/
#define C_offInstant_TolAcPow			0
#define C_offInstantA_AcPow				1
#define C_offCInstantB_AcPow			2
#define C_offCInstantC_AcPow			3

#define C_offCInstant_TolRePow			4
#define C_offCInstantA_RePow			5
#define C_offCInstantB_RePow			6
#define C_offCInstantC_RePow			7

#define C_offCInstant_TolAppaPow		8
#define C_offCInstantA_AppaPow			9
#define C_offCInstantB_AppaPow			10
#define C_offCInstantC_AppaPow			11

#define C_offCPhaseA_Curr_4Dig			12
#define C_offCPhaseB_Curr_4Dig			13
#define C_offCPhaseC_Curr_4Dig			14

#define C_offCPhaseA_Curr				15
#define C_offCPhaseB_Curr				16
#define C_offCPhaseC_Curr				17

#define C_offCVector_Current			18
#define C_offCZero_Current				19

#define C_offCPhaseA_Volage				20
#define C_offCPhaseB_Volage				21
#define C_offCPhaseC_Volage				22

#define C_offCTol_PowerFactor			23
#define C_offCPhaseA_PowerFactor		24
#define C_offCPhaseB_PowerFactor		25
#define C_offCPhaseC_PowerFactor		26

#define C_offCElecNet_Freq				27

#define C_offCPhaseA_Angle				28
#define C_offCPhaseB_Angle				29
#define C_offCPhaseC_Angle				30

#define C_offCVolA_Phase				31
#define C_offCVolB_Phase				32
#define C_offCVolC_Phase				33

#define C_offCCurrA_Phase				34
#define C_offCCurrB_Phase				35
#define C_offCCurrC_Phase				36

#define C_InstantNum					37		/*需要写入数据层的瞬时量个数*/
#define C_fourLenthNum                  20      /*4个字节的成员个数*/


/***************************计量数据交互用到的宏定义************************/
#define C_Control_DI1					0x87		/*校表控制命令DI1*/
#define C_StartCalibration_DI0			0x68		/*校表控制命令DI0之启动校表*/
#define C_StopCalibration_DI0			0x69		/*校表控制命令DI0之结束校表*/
#define C_ClearCalData_DI0				0x6A		/*校表控制命令DI0之校表数据清零*/
#define C_CalDataMeterIC_DI1			0x86		/*读写计量芯片校表参数DI1*/
#define C_CalDataDProcess_DI1			0x85		/*读写数据层校表参数DI1*/
#define C_MeaDataMeterIC_DI1			0x83		/*读写计量芯片计量参数DI1*/
#define C_TWCalDataMeterIC_DI1			0x82		/*读写计量芯片集合校表参数DT1*/
#define C_Write_Table2					0x10
#define C_Read_Table2					0x01
#define C_WandR_Table2					0x11
#define C_NoWR_Table2					0x00
#define C_Check0_Reg					0x3E
#define C_Check1_Reg					0x5E
#define C_NorDIAmount					0x01
#define C_ThreeDIAmount					0x03
#define C_FourDIAmount					0x04
#define C_SixDIAmount					0x06
#define C_NT_NO							C_MeterICDataNum_T
#define C_NT_Check						0x4E
#define C_MaxMeaDataReg					0x5F
#define C_PowerFactorNO					0x72
#define C_TempoffsetNO					0x73
/************************Table2类型定义********************
MeterIC_WR和EE_WR可取值0xX X
						 | |
						 | |__为度标志:为1可读，为0不可读
						 |____为写标志:为1可写，为0不可写
								可读可写C_WandR_Table2
								可读不可写C_Read_Table2
								不可读可写C_Write_Table2
								不可读不可写C_NoWR_Table2
NO_Amount真实数据的标识码序号数量
NO_Buffer2高位数据标识码序号
NO_Buffer2中位数据标识码序号
NO_Buffer2低位数据标识码序号
*********************************************************/
typedef struct
{
	uchar8 DI0;
	uchar8 MeterIC_WR;
	uchar8 DataProcess_WR;
	uchar8 Check;
	uchar8 NO_Amount;
	uchar8 NO_Buffer2;
	uchar8 NO_Buffer1;
	uchar8 NO_Buffer0;
}Str_MeterICTable2_Type;
/************************Table2计量芯片校表参数读写定义********************/
#define C_CalData_Len				0x74							/*校表参数表数据长度*/
const Str_MeterICTable2_Type Str_Table2_CalData[C_CalData_Len]=
{
/*  DI0		计量芯片读写权限	   数据层读写权限		校验和寄存器	序号个数		高位真实数据序号	中位真实数据序号	低位真实数据序号*/
	0x00,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0X01,	C_Read_Table2,		C_NoWR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0X02,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x03,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x04,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x05,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x06,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x07,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x08,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x09,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x0A,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x0B,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x0C,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x0D,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x0E,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x0F,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x10,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x11,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x12,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x13,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x14,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x15,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x16,	C_NoWR_Table2,		C_NoWR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x17,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x18,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x19,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x1A,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x1B,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x1C,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x1D,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x1E,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x1F,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x20,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x21,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x22,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x23,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x24,	C_NoWR_Table2,		C_NoWR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x25,	C_NoWR_Table2,		C_NoWR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x26,	C_NoWR_Table2,		C_NoWR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x27,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x28,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x29,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x2A,	C_NoWR_Table2,		C_NoWR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x2B,	C_NoWR_Table2,		C_NoWR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x2C,	C_NoWR_Table2,		C_NoWR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x2D,	C_NoWR_Table2,		C_NoWR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x2E,	C_NoWR_Table2,		C_NoWR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x2F,	C_NoWR_Table2,		C_NoWR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x30,	C_NoWR_Table2,		C_NoWR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x31,	C_Read_Table2,		C_NoWR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x32,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x33,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x34,	C_NoWR_Table2,		C_NoWR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x35,	C_NoWR_Table2,		C_NoWR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x36,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x37,	C_WandR_Table2,		C_WandR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x38,	C_NoWR_Table2,		C_NoWR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x39,	C_NoWR_Table2,		C_NoWR_Table2,		C_Check0_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x3A,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x3B,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x3C,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x3D,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x3E,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x3F,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x40,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x41,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x42,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x43,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x44,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x45,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x46,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x47,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x48,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x49,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x4A,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x4B,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x4C,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x4D,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x4E,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x4F,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x50,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x51,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x52,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x53,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x54,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x55,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x56,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x57,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x58,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x59,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x5A,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x5B,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x5C,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x5D,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x5E,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x5F,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x60,	C_WandR_Table2,		C_WandR_Table2,		C_Check1_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x61,	C_WandR_Table2,		C_WandR_Table2,		C_Check1_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x62,	C_WandR_Table2,		C_WandR_Table2,		C_Check1_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x63,	C_WandR_Table2,		C_WandR_Table2,		C_Check1_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x64,	C_WandR_Table2,		C_WandR_Table2,		C_Check1_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x65,	C_WandR_Table2,		C_WandR_Table2,		C_Check1_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x66,	C_WandR_Table2,		C_WandR_Table2,		C_Check1_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x67,	C_WandR_Table2,		C_WandR_Table2,		C_Check1_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x68,	C_WandR_Table2,		C_WandR_Table2,		C_Check1_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x69,	C_WandR_Table2,		C_WandR_Table2,		C_Check1_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x6A,	C_WandR_Table2,		C_WandR_Table2,		C_Check1_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x6B,	C_WandR_Table2,		C_WandR_Table2,		C_Check1_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x6C,	C_NoWR_Table2,		C_NoWR_Table2,		C_Check1_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x6D,	C_WandR_Table2,		C_WandR_Table2,		C_Check1_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x6E,	C_WandR_Table2,		C_WandR_Table2,		C_Check1_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x6F,	C_WandR_Table2,		C_WandR_Table2,		C_Check1_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x70,	C_WandR_Table2,		C_WandR_Table2,		C_Check1_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x71,	C_NoWR_Table2,		C_NoWR_Table2,		C_Check1_Reg,	C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x72,	C_NoWR_Table2,		C_WandR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,
	0x73,	C_NoWR_Table2,		C_WandR_Table2,		C_NT_Check,		C_NorDIAmount,	C_NT_NO,			C_NT_NO,			C_NT_NO,		
};
/************************Table3类型定义********************
MeterIC_WR和EE_WR可取值0xX X
						 | |
						 | |__为度标志:为1可读，为0不可读
						 |____为写标志:为1可写，为0不可写
								可读可写C_WandR_Table2
								可读不可写C_Read_Table2
								不可读可写C_Write_Table2
								不可读不可写C_NoWR_Table2
NO_Amount真实数据的标识码序号数量
NO_Buffer2高位数据标识码序号
NO_Buffer2中位数据标识码序号
NO_Buffer2低位数据标识码序号
*********************************************************/
typedef struct
{
	uchar8 DI0;
	uchar8 MeterIC_WR;
	uchar8 DataProcess_WR;
	uchar8 Check;
	uchar8 NO_Amount;
	uchar8 NO_Buffer0;
	uchar8 NO_Buffer1;
	uchar8 NO_Buffer2;
	uchar8 NO_Buffer3;
	uchar8 NO_Buffer4;
	uchar8 NO_Buffer5;
	uchar8 NO_Buffer6;
	uchar8 NO_Buffer7;
	uchar8 NO_Buffer8;
}Str_MeterICTable3_Type;

#define C_CalDataTotal_Len 			0x0C
const Str_MeterICTable3_Type Str_Table3_CalData[C_CalDataTotal_Len]=
{
/*  DI0		计量芯片读写权限	数据层读写权限		校验和寄存器	序号个数		0位真实数据序号		1位真实数据序号		2位真实数据序号 	3位真实数据序号		4位真实数据序号		5位真实数据序号 	6位真实数据序号		7位真实数据序号		8位真实数据序号*/
	0x00,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_ThreeDIAmount,0x17,				0x18,				0x19,				C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			/*电压增益校正集合*/
	0x01,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_ThreeDIAmount,0x1A,				0x1B,				0x1C,				C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			/*电流增益校正集合*/
	0x02,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_ThreeDIAmount,0x04,				0x05,				0x06,				C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			/*有功功率增益校正集合*/
	0x03,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_ThreeDIAmount,0x0D,				0x0E,				0x0F,				C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			/*相位校正0集合*/
	0x04,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_ThreeDIAmount,0x10,				0x11,				0x12,				C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			/*相位校正1集合*/
	0x05,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_ThreeDIAmount,0x61,				0x62,				0x63,				C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,		 	/*相位校正2集合*/
	0x06,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_ThreeDIAmount,0x27,				0x28,				0x29,				C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			/*电流有效值offset校正集合*/
	0x07,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_ThreeDIAmount,0x07,				0x08,				0x09,				C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			/*无功功率增益校正集合*/
	0x08,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_ThreeDIAmount,0x0A,				0x0B,				0x0C,				C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			/*视在功率增益校正集合*/
	0x09,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_SixDIAmount,	0x10,				0x11,				0x12,				0x0D,				0x0E,				0x0F,				C_NT_NO,			C_NT_NO,			C_NT_NO,			/*顺序电流ABC电压ABC原始值读取集合*/
	0x0A,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_FourDIAmount,	0x01,				0x02,				0x03,				0x04,				C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			/*有功功率原始值读顺序ABC合相*/
	0x0B,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_SixDIAmount,	0x1A,				0x1B,				0x1C,				0x17,				0x18,				0x19,				C_NT_NO,			C_NT_NO,			C_NT_NO,			/*顺序电流ABC电压ABC增益数据校正集合*/
};

typedef struct
{
	ushort16 V_usDataTemp_ABC0[3];
	ushort16 V_usDataTemp_ABC1[3];
}Str_EvenHarmonicError_Type;

typedef struct
{
	ulong32 V_ulCurrentLimit_Low;
	ulong32 V_ulCurrentLimit_High;
}Str_CurrentLimit_Type;




void SF_ClearEnergyData_MeterIC(void);
void SF_TemRectify_MeterIC(void);
void SF_500mS_MeterIC(void);
void SF_InitialALL_MeterIC (uchar8 V_ucInitMode);
uchar8 SF_Check_MeterIC(void);
void SF_PowerDataTidy_MeterIC(void);
void SF_PowerDatatoHEX_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE);
void SF_PowerFactorDatatoHEX_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE);
void SF_VoltageDatatoHEX_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE);
void SF_CurrentDatatoHEX_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE);
void SF_FrequencyDatatoHEX_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE);
void SF_PhaseAngleDatatoHEX_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE, Str_RealAngleData_Type *pStr_RealAngleData);
void SF_VoltagePhaseAngleDatatoHEX_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE, Str_RealAngleData_Type *pStr_RealAngleData);
void SF_CurrentPhaseAngleDatatoHEX_MeterIC(Str_RealAngleData_Type *pStr_RealAngleData);
void SF_ClearCalReg_MeterIC(void);
void SF_Display_MeterIC (uchar8 V_ucData, uchar8 V_ucFlag);
void SF_WorkingState(void);
void SF_CurrentSignDisplay(void);
void SF_CurrentThreshold_MeterIC(ulong32* pV_ulIrmsData);
void SF_InitialPowerCoeff(void);
ulong64 SF_GetPowerCoeff(void);
void SF_SlipCurrent(void);
ulong32  SF_CurrentThresholdGain_MeterIC(void);

/* 直流偶次谐波补偿 */
void InF_InitialEvenHarmonicCompensationTime( void );
uchar8 SF_GetEvenHarmonicCompensationFlag( void );
void SF_GetEvenHarmonicContent(void);
void SF_GetEvenHarmonicCompensationValue( ushort16 *pV_usCompTemp );
void SF_EvenHarmonicCompensation( ushort16 *pV_usCompTemp, uchar8 V_ucRegAddress );

/*zlj新增*/
typedef struct
{
	long64 ActivePowerSummer_TABC[4];		/*1min合相ABC有功功率累加和*/
	long64 ReativePowerSummer_TABC[4];		/*1min合相ABC无功功率累加和*/
	uchar8 Number;							/*1min功率累加次数*/
}Str_PowerAdd_Type;

#define C_PowerTypeNum			8		/*功率类型*/

/*瞬时量、电能里ABC和TABC的偏移，所有的ABC和TABC偏移都统一用下面宏定义*/
#define C_offA		0		/*不带T的数组ABC偏移*/
#define C_offB		1
#define C_offC		2

#define C_offTT		0		/*带T的数组TABC偏移*/
#define C_offTA		1
#define C_offTB		2
#define C_offTC		3

#define SF_ABS(X) (X >= 0 ? X : -X)

uchar8 SF_Test_MeterIC(void);
void SF_Cal1minPowerSum(Str_PowerAdd_Type *pStr_PowerAdd_Type, Str_RealtimePower_Type *pStr_RealtimePower);
void SF_Cal1minAveragePower(Str_PowerAdd_Type *pStr_PowerAdd);
void SF_ClrCurrentPower(void);
void SF_LessData(uchar8 *pV_ucDataBuf, ushort16 V_ustemp);
void SF_6digpowTo4digpow(uchar8 *pV_ucDataBuf);
#endif
