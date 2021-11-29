/********************************************************************************************
Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     MeterICDrive.c
Version:       V1
Author:        
Date:          2014-3-12
Description:   ����оƬ�����ļ������������оƬ���н����Ķ��ڴ��ļ��У�������ȡʵʱ����������
---------------------------------------------------------------------------------------------
History1:      ��1���޸�
����1. Date:
       Author:
       Modification:
---------------------------------------------------------------------------------------------
����2. Date:
       Author:
       Modification:
---------------------------------------------------------------------------------------------
History2:      ��2���޸�
����1. Date:
       Author:
       Modification:
---------------------------------------------------------------------------------------------
����2. Date:
       Author:
       Modification:
---------------------------------------------------------------------------------------------
History3:      ��3���޸�
����1. Date:2021.09.27
       Author:zlj
       Modification:
---------------------------------------------------------------------------------------------
����2. Date:
       Author:
       Modification:
********************************************************************************************/
#ifndef	__MeterIC_H
#define	__MeterIC_H

/********************************��̬��������*********************************************************/


uchar8 GV_ucWriteRegSafeFlag;									/*д����оƬ���ݰ�ȫ��־ д���ݰ�ȫ:C_DataSafe д���ݲ���ȫ:C_DataUnsafe*/
uchar8 GV_ucCalibrationState;									/*У��״̬ ����У��״̬:C_StartCalibrationOK  ���ڷ�У��״̬C_CalibrationOK*/
uchar8 GV_ucCheckTime;											/*У�����У���У��ͼ���ʱ��*/
uchar8 GV_ucUpdateTime;											/*�������ݲ����ݼ��ʱ��*/
uchar8 GV_ucEnergyLock;											/*�������ݱ���ʱ��*/
uchar8 GV_ucMeterICErrorState;									/*����оƬ����״̬*/
uchar8 GV_ucMeterICErrorNum;									/*��¼����оƬ���Ϸ�������*/
uchar8 GV_ucMeterICErrorTime;									/*��¼����оƬ���ϻָ�����*/
uchar8 GV_ucMeterICErrorFlag;									/*����оƬ���ϱ�־ ����оƬ����:C_MeterICError ����оƬ����C_MeterICNormal*/
uchar8 GV_ucMeterICNum;											/*����оƬcheck����������������5�Σ�����м���оƬ��λ�����Ҵ����ڼ䲻����˲ʱ��*/
ulong32 GV_ulCalDataChk0SUM;									/*CHECK0У���*/
ulong32 GV_ulCalDataChk1SUM;									/*CHECK1У���*/
uchar8  GV_ucPowerFactor_Flag@".DataProcessADDR";				/*���г�����������������Ƿ����������־*/
uchar8  GV_ucCurrent_Flag1@".DataProcessADDR";					/*���г�������������Ƿ����������־(2.8-4A)*/
uchar8  GV_ucCurrent_Flag2@".DataProcessADDR";					/*���г�������������Ƿ����������־(1.4-2A)*/
#define NOP()	__no_operation()

/**********************************���ݲ㺭�ǵ����в���ԭʼֵ�ṹ��*************************************************/
typedef struct
{
	ulong32 WATTReg[4];					/*�ܡ�A��B��C���й����� 24bit*/
	ulong32 VARReg[4];					/*�ܡ�A��B��C���޹����� 24bit*/
	ulong32 VAReg[4];					/*�ܡ�A��B��C�����ڹ��� 24bit*/
	ulong32 PfReg[4];					/*�ֹܷ������� 24bit*/
	ulong32 VRmsVReg[3];				/*��ѹ���� 24bit*/
	ulong32 VRmsIReg[3];				/*�������� 24bit*/
	ulong32 IRmsN0;						/*�������ʸ���� 24bit*/
	ulong32 IRmsNOSample;				/*���ߵ��� 24bit*/
	ulong32 FREQUENCY;					/*Ƶ������ 16bit*/
	ulong32 YUIReg[3];					/*A��B��C����ƽ�����*/
/*	ulong32 TempReg;*/					/*�¶�����*/
	ulong32 YUReg[3];					/*A��B��C��ѹ��� */
	ulong32 YIReg[3];					/*ABC�������*/
}Str_VARREGTYPE_Type;
/*********************************����ϵ��RAM�洢�ṹ��************************************************/
typedef struct
{
	ulong64 PowerCoeffData;
	ushort16 Crc;
}Str_PowerCoeff_Type;
/********************************����ԭʼֵ�ṹ��***************************************************/
typedef struct
{
	ushort16 V_ucActiveEnergy_TABC[4];
	ushort16 V_ucReactiveEnergy_TABC[4];
	ushort16 V_ucApparentEnergy_TABC[4];
}Str_EnergyData_Type;
/*********************************��������(���ݲ�����)HEX�ṹ��**************************************************/
typedef struct
{
	long32 ActivePowerHEX_TABC[4];		/*�ܡ�A��B��C���й����� 32bit*/
	long32 ReativePowerHEX_TABC[4];		/*�ܡ�A��B��C���޹����� 32bit*/
	long32 ApparentPowerHEX_TABC[4];	/*��A��B��C�����ڹ��� 32bit*/
	long32 VRmsILSBRegHEX_ABC[3];		/*��������XXXX.XXXX 32bit*/ 
    long32 VRmsIRegHEX_ABC[3];			/*��������XXXXX.XXX 32bit*/
	long32 IRmsN0_HEX;					/*�������ʸ���� 16bit*/
	long32 IRmsNOSample_HEX;			/*���ߵ��� 16bit*/    
	
	ushort16 VRmsVRegHEX_ABC[3];		/*��ѹ���� 32bit*/
	short16 PowerFactorHEX_TABC[4];		/*�ֹܷ������� 16bit*/
	ushort16 FREQUENCY_HEX;				/*Ƶ������ 16bit*/
	ushort16 YUIRegHEX_ABC[3];			/*A��B��C����ƽ�����*/
/*	ushort16 TempReg_HEX;*/				/*�¶�����*/
	ushort16 YURegHEX_ABC[3];			/*A��B��C��ѹ��� */
	ushort16 YIRegHEX_ABC[3];			/*A��B��C�������*/
}Str_HEX_VARREGTYPE_Type;
/*********************************���������ʵֵ(xxx.x��)**************************************************/
typedef struct
{
	ulong32 YUIRealData_ABC[3];
	ulong32 YURealData_ABC[3];
	ulong32 YIRealData_ABC[3];
}Str_RealAngleData_Type;
	
/********************************�궨��*********************************************************/
#define C_EnWriteCalDataMeterIC					0xC900005A		/*дУ�����ʹ�ܼ���оƬ*/
#define C_DisWriteCalDataMeterIC				0xC9000000		/*дУ�����ʧ�ܼ���оƬ*/
#define C_EnReadCalDataMeterIC					0xC600005A		/*��У������ʹ�ܼ���оƬ*/
#define C_EnReadMeaDataMeterIC					0xC6000000		/*����������ʹ�ܼ���оƬ*/

#define C_MeterICDataLEN						4				/*ʹ�ܼ���оƬ���ݳ���*/

#define C_DELAY1US								0x00000001		/*��ʱ1΢��*/
#define C_DELAY2US								0x00000002		/*��ʱ2΢��*/
#define C_DELAY4US								0x00000007		/*��ʱ4΢��*/
#define C_DELAY25MS								0x0000DDF0		/*��ʱ25����*/
#define C_DELAY25MSPowerDown					0x00006A00		/*�͹�������ʱ25����*/
#define C_DELAY1MS								0x00000900		/*��ʱ1����*/
#define C_DELAY1MSPowerDown						0x000002A0		/*�͹�������ʱ1����*/

#define C_WriteDataMeterIC						0x80			/*����д����ʱ��д�����ݼĴ�����ַ���ֽ���1:|=C_WriteDataMeterIC*/
#define C_ReadDataMeterIC						0x7F			/*���ڶ�����ʱ��д�����ݼĴ�����ַ���ֽ���0:&=C_ReadDataMeterIC*/
#define C_DataSafe								0x86			/*����оƬд�����ݰ�ȫ*/
#define C_DataUnsafe							0x68			/*����оƬд�����ݲ���ȫ*/
#define C_ReadMeaDataRegFlag					0x00			/*���Ĵ�����ȡģʽ���óɶ�ȡ���������Ĵ���*/
#define C_ReadCalDataRegFlag					0x01			/*���Ĵ�����ȡģʽ���óɶ�ȡУ������Ĵ���*/

#define C_ModeCfg_Data					 		0xB97F			/*ģʽ��ؿ������ݣ��������ߵ�����*/
#define C_PorDownModeCfg_Data					0xB97F			/*�͹�����ģʽ��ؿ������ݣ��������ߵ�����*/

#define C_ModuleCFG_Data						0x3437			/*��·ģ�����üĴ���*/
#define C_Iregion1_Data							240				/**/
#define C_Iregion0_Data							2784			/**/

#define C_CalDataLen							3				/*У��������ݳ���*/
#define C_MeaDataLen							3				/*������������*/
#define C_DispatchMsgLen						2				/*������Ϣ���ݳ���*/

#define C_CheckTime								5				/*У�����У���У��ͼ�����ʱ��*/
#define C_UpdateTime							3				/*�ϵ��ʼ��ʱ����оƬ�ı���ʱ�䣺1.5s������500ms��*/
#define C_MAXRepeatTime							20				/*���ѭ�����ʱ��*/
#define C_RepeatTime							2				/*У�������У���У�顢�������ݲ�ѭ�����ʱ��*/
#define C_MeterICErrorTime						10				/*����оƬ��Ч����ʱ������ֵLSB=500mS*/
#define C_MeterICRecoverTime					20				/*����оƬ�ָ�ʱ�䷧ֵLSB=500mS*/

#define C_MeterICErrorNum						2				/*����оƬ����״̬���ж�����Ч��������ֵ*/
#define C_MeterICErrorFlag						254				/*����оƬ���ڹ���״̬*/
#define C_MeterICErrorState						0x01			/*����оƬ����״̬����Ϊ����V_Data|=*/
#define C_MeterICRecoverState					0xFE			/*����оƬ����״̬����Ϊ����V_Data&=*/

#define C_OneByteLen							1				/*һ�ֽڳ���*/
#define C_TwoByteLen							2				/*���ֽڳ���*/
#define C_FourByteLen							4				/*���ֽڳ���*/

#define C_VoltageThreshold						20				/*��ѹ��ֵ(X.X V)*/
#define C_VoltageThreshold220					80				/*��ѹ��ֵ(X.X V)��220��380V���㣬8V*/
#define C_CurrentThreshold						15				/*������ֵ(X.XXX A)*/
#define C_PowerFactor							1000			/*��������Ĭ��ֵ*/
#define C_PowerFactorThreshold					995				/*����������ֵ*/
#define C_FrequencyThreshold					4999			/*Ƶ�ʷ�ֵ*/
#define C_FrequencyData							5000			/*Ƶ��Ĭ��ֵ*/

#define C_PowerFlag_T							0x55			/*�ܹ��ʱ�־*/
#define C_PowerFlag_ABC							0xAA			/*���๦�ʱ�־*/

#define C_PowerHexLen							3 				/*��������Hex�����ֽڳ���*/
#define C_VoltageHexLen							3				/*��ѹ����Hex�����ֽڳ���*/
#define C_CurrentHexLen							3				/*��������Hex�����ֽڳ���*/
#define C_PowerFactorHexLen						3				/*������������Hex�����ֽڳ���*/
#define C_NOCurrentHexLen						3				/*���ߵ�������Hex�����ֽڳ���*/
#define C_FrequencyHexLen						3 				/*����Ƶ������Hex�����ֽڳ���*/
#define C_PhaseAngleHexLen						3 				/*ƽ�������������Hex�����ֽڳ���*/
#define C_TemperatureHexLen						3 				/*�¶�����Hex�����ֽڳ���*/

#define C_Ib0_3A								0x00			/*���ܱ��������ΪIb=0.3A*/
#define C_Ib1A									0x01			/*���ܱ��������ΪIb=1A*/
#define C_Ib1_5A								0x02			/*���ܱ��������ΪIb=1.5A*/
#define C_Ib5A									0x03			/*���ܱ��������ΪIb=5A*/
#define C_Ib10A									0x04			/*���ܱ��������ΪIb=10A*/
#define C_Ib15A									0x05			/*���ܱ��������ΪIb=15A*/
#define C_Ib20A									0x06			/*���ܱ��������ΪIb=20A*/
#define C_Ib30A									0x07			/*���ܱ��������ΪIb=30A*/

#define C_N0_3A									1000			/*Ib=0.3Aʱ�ı���ϵ��*/
#define C_N1A									300				/*Ib=1Aʱ�ı���ϵ��*/
#define C_N1_5A									200				/*Ib=1.5Aʱ�ı���ϵ��*/
#define C_N5A									60				/*Ib=5Aʱ�ı���ϵ��*/
#define C_N10A									30				/*Ib=10Aʱ�ı���ϵ��*/
#define C_N15A									20				/*Ib=15Aʱ�ı���ϵ��*/
#define C_N20A									15				/*Ib=20Aʱ�ı���ϵ��*/
#define C_N30A									10				/*Ib=30Aʱ�ı���ϵ��*/

#define C_AngleMAXData							1800			/*����������ֵXXX.X һλС��*/
#define C_AngleMAXRealData						3600			/*�������ʵ�����ֵXXX.X һλС��*/
#define C_InitialMsgDataLen						0x01			/*��ʼ����Ϣ���ݳ���*/
#define C_MAXPulse								20				/*������������*/

#define C_PhaseLossFlag							0x01			/*��ѹ���ߵ��������־*/
#define C_NoPhaseLossFlag						0x00			/*�޵�ѹ���ߵ��������־*/
#define C_InitPowerDown							0x00			/*�͹����³�ʼ������оƬ��־*/
#define C_InitNormal							0x01			/*����ģʽ�³�ʼ������оƬ��־*/

#define C_Phase_A								0x00			/*A���ʾ�����ڵ�ѹ������ʾ������*/
#define C_Phase_B								0x01			/*B���ʾ�����ڵ�ѹ������ʾ������*/
#define C_Phase_C								0x02			/*C���ʾ�����ڵ�ѹ������ʾ������*/

#define C_Reverse_Ia							0x01			/*A��������ŷ����ж�*/
#define C_Reverse_Ib							0x02			/*B��������ŷ����ж�*/
#define C_Reverse_Ic							0x04			/*C��������ŷ����ж�*/

#define C_PQsign2								0x08			/*�����ж�ʱʹ��*/
#define C_PQsign3								0x88			/*�����ж�ʱʹ��*/
#define C_PQsign4								0x80			/*�����ж�ʱʹ��*/

#define C_ReverseCurr4Dig						0x80000000		/*��������4λС������BCD�������Ӹ���*/
#define C_ReverseCurr3Dig						0x00800000		/*��������3λС������BCD�������Ӹ���*/
#define C_ReversePower3Dig						0x00800000		/*�����������Ӹ���*/

#define C_PowerT								0x00			/*���ڹ��ʼ���ʱ�õ�*/
#define C_PowerA								0x01			/*���ڹ��ʼ���ʱ�õ�*/
#define C_PowerB								0x02			/*���ڹ��ʼ���ʱ�õ�*/
#define C_PowerC								0x03			/*���ڹ��ʼ���ʱ�õ�*/

#define C_PTplus								0xFFEF			/*���й����ʷ����������ڵ������״̬������1*/
#define C_PTminus								0x0010			/*���й����ʷ���*/
#define C_QTplus								0xFFDF			/*���޹����ʷ�����*/
#define C_QTminus								0x0020			/*���޹����ʷ���*/

#define C_PAplus								0xFFFE			/*A���й����ʷ����������ڵ������״̬������2*/
#define C_PAminus								0x0001			/*A���й����ʷ���*/
#define C_PBplus								0xFFFD			/*B���й����ʷ�����*/
#define C_PBminus								0x0002			/*B���й����ʷ���*/
#define C_PCplus								0xFFFB			/*C���й����ʷ�����*/
#define C_PCminus								0x0004			/*C���й����ʷ���*/
#define C_QAplus								0xFFEF			/*A���޹����ʷ�����*/
#define C_QAminus								0x0010			/*A���޹����ʷ���*/
#define C_QBplus								0xFFDF			/*B���޹����ʷ�����*/
#define C_QBminus								0x0020			/*B���޹����ʷ���*/
#define C_QCplus								0xFFBF			/*C���޹����ʷ�����*/
#define C_QCminus								0x0040			/*C���޹����ʷ���*/

#define C_ActiveEnergyT_Plus					0xF7			/*���ܶ�ȡ�ṹ���й�������-����*/
#define C_ActiveEnergyT_Minus					0x08			/*���ܶ�ȡ�ṹ���й�������-����*/
#define C_ActiveEnergyA_Plus					0xFE			/*���ܶ�ȡ�ṹ���й�����A��-����*/
#define C_ActiveEnergyA_Minus					0x01			/*���ܶ�ȡ�ṹ���й�����A��-����*/
#define C_ActiveEnergyB_Plus					0xFD			/*���ܶ�ȡ�ṹ���й�����B��-����*/
#define C_ActiveEnergyB_Minus					0x02			/*���ܶ�ȡ�ṹ���й�����B��-����*/
#define C_ActiveEnergyC_Plus					0xFB			/*���ܶ�ȡ�ṹ���й�����C��-����*/
#define C_ActiveEnergyC_Minus					0x04			/*���ܶ�ȡ�ṹ���й�����C��-����*/
#define C_ReactiveEnergyT_Plus					0x7F			/*���ܶ�ȡ�ṹ���޹�������-����*/
#define C_ReactiveEnergyT_Minus					0x80			/*���ܶ�ȡ�ṹ���޹�������-����*/
#define C_ReactiveEnergyA_Plus					0xEF			/*���ܶ�ȡ�ṹ���޹�����A��-����*/
#define C_ReactiveEnergyA_Minus					0x10			/*���ܶ�ȡ�ṹ���޹�����A��-����*/
#define C_ReactiveEnergyB_Plus					0xDF			/*���ܶ�ȡ�ṹ���޹�����B��-����*/
#define C_ReactiveEnergyB_Minus					0x20			/*���ܶ�ȡ�ṹ���޹�����B��-����*/
#define C_ReactiveEnergyC_Plus					0xBF			/*���ܶ�ȡ�ṹ���޹�����C��-����*/
#define C_ReactiveEnergyC_Minus					0x40			/*���ܶ�ȡ�ṹ���޹�����C��-����*/
#define C_DirectionType							0x80000000		/*���ڹ��ʷ����ж�*/
#define C_NODirectionType						0x7FFFFFFF		/*��������������λ����λ*/
#define C_NOSign_3Byte   						0x007FFFFF		/*ȥ��3�ֽڵķ���λ*/

#define C_EnergyLock							0x00			/*�����������ɶ�*/
#define C_EnergyUnlock							0x01			/*���ܽ����ɶ�ȡ*/

#define C_TP									25				/*�¶�У����׼�¶�*/

#define C_MeterICError				0x01						/*����оƬ���ڹ���״̬*/
#define C_MeterICNormal				0x00						/*����оƬ��������״̬*/
#define C_MeterICRstNum				5							/*����оƬ����5��Check����Ž��и�λ*/

#define C_Odd_Harmonic_3TimesFitCon			0x07				/*���г�����������жϣ�3�ξ�����������־*/
#define C_Odd_Harmonic_CurrentFitFlag1		0x01				/*���г�������������ж�����1��־(2.8-4A)*/
#define C_Odd_Harmonic_CurrentFitFlag2		0x02				/*���г�������������ж�����2��־(1.4-2A)*/

#define C_EvenHarmonicCompensationTime		24*60				/*24h*60min*/

/********************************offset�Զ��������ݶ���*********************************************************/
#define C_Check0RetData		0x016F1F	/*check0����ͳ�ʼ����:���������й̶�ֵд������ݺͲ�����������ݣ��������ߵ�����*/

#define C_VrefAotu			0x00		/*0x00:����������0x01:�رղ���*/
#define C_Vref2_Data		0xFF12		/*�ο���ѹ����2��ϵ��*/
#define C_Vref1_Data		0x5819		/*�ο���ѹ����1��ϵ��*/
#define C_VrefC_Data		0xEF18		/*�ο���ѹ����������*/
#define C_Check1RetData		0			/*REF+��Χ check1����ͳ�ʼ����:���������й̶�ֵд������ݺͲ������������.��У��ͼ���*/

#define C_Allgain_EnTemp	0xFFDC		/*ʹ���¶Ȳ�������ֹ����¶�����*/
#define C_Allgain_DisTemp	0			/*�ر��¶Ȳ���������Ĭ��ֵ0*/

#define C_VrefAotu_En		0x02		/*ʹ���¶Ȳ���*/
#define C_VrefAotu_Dis		0x00		/*�ر��¶Ȳ���*/
#define C_TempOverData		-35			/*�¶ȱ������ֵ*/


/********************************���������Ĵ�����ַ*********************************************************/
#define C_DeviceIDReg							0x00			/*����оƬ������ݱ���*/
#define C_ActivePowerA_Reg						0x01			/*A���й����ʼĴ�����ַ*/
#define C_ActivePowerB_Reg						0x02			/*B���й����ʼĴ�����ַ*/
#define C_ActivePowerC_Reg						0x03			/*C���й����ʼĴ�����ַ*/
#define C_ActivePowerT_Reg						0x04			/*�����й����ʼĴ�����ַ*/
#define C_ReativePowerA_Reg						0x05			/*A���޹����ʼĴ�����ַ*/
#define C_ReativePowerB_Reg						0x06			/*B���޹����ʼĴ�����ַ*/
#define C_ReativePowerC_Reg						0x07			/*C���޹����ʼĴ�����ַ*/
#define C_ReativePowerT_Reg						0x08			/*�����޹����ʼĴ�����ַ*/
#define C_ApparentPowerA_Reg					0x09			/*A�����ڹ��ʼĴ�����ַ*/
#define C_ApparentPowerB_Reg					0x0A			/*B�����ڹ��ʼĴ�����ַ*/
#define C_ApparentPowerC_Reg					0x0B			/*C�����ڹ��ʼĴ�����ַ*/
#define C_ApparentPowerT_Reg					0x0C			/*�������ڹ��ʼĴ�����ַ*/
#define C_VRmsVReg_AReg							0x0D			/*A���ѹ�Ĵ�����ַ*/
#define C_VRmsVReg_BReg							0x0E			/*B���ѹ�Ĵ�����ַ*/
#define C_VRmsVReg_CReg							0x0F			/*C���ѹ�Ĵ�����ַ*/
#define C_VRmsIReg_AReg							0x10			/*A������Ĵ�����ַ*/
#define C_VRmsIReg_BReg							0x11			/*B������Ĵ�����ַ*/
#define C_VRmsIReg_CReg							0x12			/*C������Ĵ�����ַ*/
#define C_IRmsN0_Reg							0x13			/*�������ʸ������Чֵ*/
#define C_PowerFactor_AReg						0x14			/*A�๦�������Ĵ�����ַ*/
#define C_PowerFactor_BReg						0x15			/*B�๦�������Ĵ�����ַ*/
#define C_PowerFactor_CReg						0x16			/*C�๦�������Ĵ�����ַ*/
#define C_PowerFactor_TReg						0x17			/*���๦�������Ĵ�����ַ*/
#define C_YUIAngle_AReg							0x18			/*A��������ѹ��ǼĴ�����ַ*/
#define C_YUIAngle_BReg							0x19			/*B��������ѹ��ǼĴ�����ַ*/
#define C_YUIAngle_CReg							0x1A			/*C��������ѹ��ǼĴ�����ַ*/
#define C_INTFlag_Reg							0x1B			/*�жϱ�־����������*/
#define C_FREQUENCY_Reg							0x1C			/*����Ƶ�ʼĴ�����ַ*/
#define C_EnergyRegState_Reg					0x1D			/*���ܼĴ�������״̬�Ĵ��������ڼ��ӵ��ܼĴ����Ƿ������ ���Ϊ1 Ĭ��Ϊ0 ��������*/
#define C_ActiveEnergy_AReg						0x1E			/*�й�A���������*/
#define C_ActiveEnergy_BReg						0x1F			/*�й�B���������*/
#define C_ActiveEnergy_CReg						0x20			/*�й�C���������*/
#define C_ActiveEnergy_TReg						0x21			/*�й������������*/
#define C_ReativeEnergy_AReg					0x22			/*�޹�A���������*/
#define C_ReativeEnergy_BReg					0x23			/*�޹�B���������*/
#define C_ReativeEnergy_CReg					0x24			/*�޹�C���������*/
#define C_ReativeEnergy_TReg					0x25			/*�޹������������*/
#define C_YUAngle_AReg							0x26			/*A���ѹ��ǼĴ�����ַ*/
#define C_YUAngle_BReg							0x27			/*B���ѹ��ǼĴ�����ַ*/
#define C_YUAngle_CReg							0x28			/*C���ѹ��ǼĴ�����ַ*/
#define C_IORms_Reg								0x29			/*���ߵ���IO����ͨ����Чֵ*/
#define C_TempReg_Reg							0x2A			/*�¶ȼĴ�����ַ*/
#define C_VRmsNO_Reg							0x2B			/*�����ѹʸ������Чֵ*/
#define C_SFlag_Reg								0x2C			/*��Ŷ��ࡢ����SIG�ȱ�־״̬(B0=1:A��ʧѹ;B1=1:B��ʧѹ;B2=1:C��ʧѹ;B3=1:��ѹ�����;B4=1:���������;B5=1:������һ���й�����Ϊ��;B6=1:������һ���޹�����Ϊ��;B7=1:^^^^^*/
#define C_TheLastData_Reg						0x2D			/*����оƬ��һ��SPIͨѶ���ݱ��ݼĴ�����ַ*/
#define C_ComChkSum_Reg							0x2E			/*ͨѶУ��ͼĴ���*/
#define C_ADCDataSample_IAReg					0x2F			/*A�����ͨ��ADC��������*/
#define C_ADCDataSample_IBReg					0x30			/*B�����ͨ��ADC��������*/
#define C_ADCDataSample_ICReg					0x31			/*C�����ͨ��ADC��������*/
#define C_ADCDataSample_VAReg					0x32			/*A���ѹͨ��ADC��������*/
#define C_ADCDataSample_VBReg					0x33			/*B���ѹͨ��ADC��������*/
#define C_ADCDataSample_VCReg					0x34			/*C���ѹͨ��ADC��������*/
#define C_ApparentEnergy_AReg					0x35			/*����A���������*/
#define C_ApparentEnergy_BReg					0x36			/*����B���������*/
#define C_ApparentEnergy_CReg					0x37			/*����C���������*/
#define C_ApparentEnergy_TReg					0x38			/*�����ܵ�������*/
#define C_FastCnt_AReg							0x39			/*A������������*/
#define C_FastCnt_BReg							0x3A			/*B������������*/
#define C_FastCnt_CReg							0x3B			/*C������������*/
#define C_FastCnt_TReg							0x3C			/*��������������*/
#define C_PowerFlag_Reg							0x3D			/*�й�/�޹����ʷ�������Ϊ0������Ϊ1*/
#define C_CheckSum_Reg							0x3E			/*У������У���(У����Ǵӵ�ַ0x01~0x39������У������֮�ͣ������޷��ŷ�ʽ�ۼӣ���ֻ������24λ)*/
#define C_IRmsNOSample_Reg						0x3F			/*���ߵ���IOͨ�������������*/
#define C_LinePa_Reg							0x40			/*A������й�����*/
#define C_LinePb_Reg							0x41			/*B������й�����*/
#define C_LinePc_Reg							0x42			/*C������й�����*/
#define C_LinePt_Reg							0x43			/*��������й�����*/
#define C_LineEpa_Reg							0x44			/*A������й�����*/
#define C_LineEpb_Reg							0x45			/*B������й�����*/
#define C_LineEpc_Reg							0x46			/*C������й�����*/
#define C_LineEpt_Reg							0x47			/*��������й�����*/
#define C_LineUaRrms_Reg						0x48			/*����A���ѹ��Чֵ*/
#define C_LineUbRrms_Reg						0x49			/*����B���ѹ��Чֵ*/
#define C_LineUcRrms_Reg						0x4A			/*����C���ѹ��Чֵ*/
#define C_LineIaRrms_Reg						0x4B			/*����A�������Чֵ*/
#define C_LineIbRrms_Reg						0x4C			/*����B�������Чֵ*/
#define C_LineIcRrms_Reg						0x4D			/*����C�������Чֵ*/
#define C_LEFlag_Reg							0x4E			/*�������ܼĴ����Ĺ���״̬����������*/
#define C_SAGFlag_Reg							0x4F			/*SAG��־�Ĵ���*/
#define C_PeakUa_Reg							0x50			/*A���ѹ���ֵ*/
#define C_PeakUb_Reg							0x51			/*B���ѹ���ֵ*/
#define C_PeakUc_Reg							0x52			/*C���ѹ���ֵ*/
#define C_LineQa_Reg							0x57			/*A������޹�����*/
#define C_LineQb_Reg							0x58			/*B������޹�����*/
#define C_LineQc_Reg							0x59			/*C������޹�����*/
#define C_LineQt_Reg							0x5A			/*��������޹�����*/
#define C_Vrefgain_Reg							0x5C			/*Vref�Զ�����ϵ��*/
#define C_ChipID_Reg							0x5D			/*оƬ�汾ָʾ�Ĵ���*/
#define C_ChkSum1_Reg							0x5E			/*����У��Ĵ���У���(0x60~0x70)*/
#define C_PtrWavebuff_Reg						0x7E			/*��������ָ�룬ֻ���ڲ�����buffer�������ݳ���*/
#define C_WaveBuff_Reg							0x7F			/*�������ݼĴ������ڲ������棬�ظ���ȡֱ�����껺�����ݳ���*/
/********************************У������Ĵ�����ַ*********************************************************/
#define C_Reserved_Reg							0x00			/*У������Ĵ�����ʼ��־*/
#define C_ModeCfg_Reg							0x01			/*ģʽ��ؿ���*/
#define C_PGACtrl_Reg							0x02			/*ADC��������*/
#define C_EMUCfg_Reg							0x03			/*EMU��λ����*/
#define C_PgainA_Reg							0x04			/*A���й���������*/
#define C_PgainB_Reg							0x05			/*B���й���������*/
#define C_PgainC_Reg							0x06			/*C���й���������*/
#define C_QgainA_Reg							0x07			/*A���޹���������*/
#define C_QgainB_Reg							0x08			/*B���޹���������*/
#define C_QgainC_Reg							0x09			/*C���޹���������*/
#define C_SgainA_Reg							0x0A			/*A�����ڹ�������*/
#define C_SgainB_Reg							0x0B			/*B�����ڹ�������*/
#define C_SgainC_Reg							0x0C			/*C�����ڹ�������*/
#define C_PhSregApq0_Reg						0x0D			/*A����λУ��0*/
#define C_PhSregBpq0_Reg						0x0E			/*B����λУ��0*/
#define C_PhSregCpq0_Reg						0x0F			/*C����λУ��0*/
#define C_PhSregApq1_Reg						0x10			/*A����λУ��1*/
#define C_PhSregBpq1_Reg						0x11			/*B����λУ��1*/
#define C_PhSregCpq1_Reg						0x12			/*C����λУ��1*/
#define C_PoffsetA_Reg							0x13			/*A���й�����OffsetУ��*/
#define C_PoffsetB_Reg							0x14			/*B���й�����OffsetУ��*/
#define C_PoffsetC_Reg							0x15			/*C���й�����OffsetУ��*/
#define C_QPhscal_Reg							0x16			/*�޹���λУ��*/
#define C_UgainA_Reg							0x17			/*A���ѹ����*/
#define C_UgainB_Reg							0x18			/*B���ѹ����*/
#define C_UgainC_Reg							0x19			/*C���ѹ����*/
#define C_IgainA_Reg							0x1A			/*A���������*/
#define C_IgainB_Reg							0x1B			/*B���������*/
#define C_IgainC_Reg							0x1C			/*C���������*/
#define C_Istarup_Reg							0x1D			/*�𶯵�����ֵ����*/
#define C_Hfconst_Reg							0x1E			/*��Ƶ�����������*/
#define C_FailVoltage_Reg						0x1F			/*ʧѹ��ֵ����*/
#define C_GainADC7_Reg							0x20			/*����·ADC�����ź�����*/
#define C_QoffsetA_Reg							0x21			/*A���޹�����offsetУ��*/
#define C_QoffsetB_Reg							0x22			/*B���޹�����offsetУ��*/
#define C_QoffsetC_Reg							0x23			/*C���޹�����offsetУ��*/
#define C_UaRmsoffset_Reg						0x24			/*A���ѹ��ЧֵoffsetУ��*/
#define C_UbRmsoffset_Reg						0x25			/*B���ѹ��ЧֵoffsetУ��*/
#define C_UcRmsoffset_Reg						0x26			/*C���ѹ��ЧֵoffsetУ��*/
#define C_IaRmsoffset_Reg						0x27			/*A�������ЧֵoffsetУ��*/
#define C_IbRmsoffset_Reg						0x28			/*B�������ЧֵoffsetУ��*/
#define C_IcRmsoffset_Reg						0x29			/*C�������ЧֵoffsetУ��*/
#define C_UoffsetA_Reg							0x2A			/*A���ѹͨ��ADC offsetУ��*/
#define C_UoffsetB_Reg							0x2B			/*B���ѹͨ��ADC offsetУ��*/
#define C_UoffsetC_Reg							0x2C			/*C���ѹͨ��ADC offsetУ��*/
#define C_IoffsetA_Reg							0x2D			/*A�����ͨ��ADC offsetУ��*/
#define C_IoffsetB_Reg							0x2E			/*B�����ͨ��ADC offsetУ��*/
#define C_IoffsetC_Reg							0x2F			/*C�����ͨ��ADC offsetУ��*/
#define C_EMUIE_Reg								0x30			/*�ж�ʹ��*/
#define C_ModuleCFG_Reg							0x31			/*��·ģ�����üĴ���*/
#define C_AllGain_Reg							0x32			/*ȫͨ�����棬����Vref���¶�У��*/
#define C_HFDouble_Reg							0x33			/*���峣���ӱ�ѡ��*/
#define C_LineGain_Reg							0x34			/*��������У��*/
#define C_PinCtrl_Reg							0x35			/*����pin����������ѡ�����*/
#define C_Pstart_Reg							0x36			/*�𶯹������üĴ���*/
#define C_Iregion0_Reg							0x37			/*��λ�����������üĴ���0*/
#define C_Cyclengrh_Reg							0x38			/*SAG���ݳ������üĴ���*/
#define C_SAGLel_Reg							0x39			/*SAG��ֵⷧ���üĴ���*/
#define C_Iregion1_Reg							0x60			/*��λ�����������üĴ���1*/
#define C_PhSregApq2_Reg						0x61			/*A����λУ��2*/
#define C_PhSregBpq2_Reg						0x62			/*B����λУ��2*/
#define C_PhSregCpq2_Reg						0x63			/*C����λУ��2*/
#define C_PoffsetAL_Reg							0x64			/*A���й�����offsetУ�����ֽ�*/
#define C_PoffsetBL_Reg							0x65			/*B���й�����offsetУ�����ֽ�*/
#define C_PoffsetCL_Reg							0x66			/*C���й�����offsetУ�����ֽ�*/
#define C_QoffsetAL_Reg							0x67			/*A���޹�����offsetУ�����ֽ�*/
#define C_QoffsetBL_Reg							0x68			/*B���޹�����offsetУ�����ֽ�*/
#define C_QoffsetCL_Reg							0x69			/*C���޹�����offsetУ�����ֽ�*/
#define C_ItRmsoffset_Reg						0x6A			/*����ʸ����offsetУ���Ĵ���*/
#define C_TPSoffset_Reg							0x6B			/*TPS��ֵУ���Ĵ���*/
#define C_TPSgain_Reg							0x6C			/*TPSб��У���Ĵ���*/
#define C_TCcoffA_Reg							0x6D			/*Verfgain�Ķ���ϵ��*/
#define C_TCcoffB_Reg							0x6E			/*Verfgain��һ��ϵ��*/
#define C_TCcoffC_Reg							0x6F			/*Verfgain�ĳ�����*/
#define C_EMCfg_Reg								0x70			/*�����㷨���ƼĴ���*/
#define C_OILVL_Reg								0x71			/*������ֵ���üĴ���*/
#define C_NT_Reg								0xFE			/*����Ҫд�Ĵ���*/
/**********************************����оƬ�������ݼĴ�����ַ*******************************************************/
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
#define C_EnergyRegADDrTol						(sizeof(Str_EnergyRegADDr)/sizeof(uchar8))		/*�������ݼĴ�������*/

/**********************************����оƬ�������ݼĴ�����ַ*******************************************************/
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
#define C_PowerRegADDrTol						(sizeof(Str_PowerRegADDr)/sizeof(uchar8))	/*�������ݼĴ�������*/

/*********************************���������Ĵ�����ַ**************************************************/
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
/********************************��ѹ�Ĵ�����ַ***************************************************/
const ushort16 Str_UrmsRegADDr[]=
{
	C_VRmsVReg_AReg,
	C_VRmsVReg_BReg,
	C_VRmsVReg_CReg
};
#define C_UrmsRegADDrTol					(sizeof(Str_UrmsRegADDr)/sizeof(ushort16))				/*��ѹ�Ĵ�������*/

/********************************�����Ĵ�����ַ***************************************************/
const ushort16 Str_IrmsRegADDr[]=
{
	C_VRmsIReg_AReg,
	C_VRmsIReg_BReg,
	C_VRmsIReg_CReg,
};
#define C_IrmsRegADDrTol					(sizeof(Str_IrmsRegADDr)/sizeof(ushort16))				/*�����Ĵ�������*/

/******************************���ݲ�����˲ʱ���������ݱ�ʶ��ͳ���****************************************************/
typedef struct
{
	ulong32 C_InstantOAD;    /*˲ʱ����OAD*/
	uchar8  CL_InstantOAD;   /*˲ʱ��OAD�ĳ���*/

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
	
	{CVector_Current, CLVector_Current},		/*�������ʸ����*/
	{CZero_Current,   CLZero_Current},			/*���ߵ���*/
	
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

	/*zlj��ע���������Str_HEX_VARREGTYPE_Typeһһ��Ӧ��д���ݲ�ʱ����һһ��Ӧ*/
};

/*������Щ˲ʱ��Str_DataProcess[]��ƫ�ƣ������Str_DataProcess[]һһ��Ӧ*/
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

#define C_InstantNum					37		/*��Ҫд�����ݲ��˲ʱ������*/
#define C_fourLenthNum                  20      /*4���ֽڵĳ�Ա����*/


/***************************�������ݽ����õ��ĺ궨��************************/
#define C_Control_DI1					0x87		/*У���������DI1*/
#define C_StartCalibration_DI0			0x68		/*У���������DI0֮����У��*/
#define C_StopCalibration_DI0			0x69		/*У���������DI0֮����У��*/
#define C_ClearCalData_DI0				0x6A		/*У���������DI0֮У����������*/
#define C_CalDataMeterIC_DI1			0x86		/*��д����оƬУ�����DI1*/
#define C_CalDataDProcess_DI1			0x85		/*��д���ݲ�У�����DI1*/
#define C_MeaDataMeterIC_DI1			0x83		/*��д����оƬ��������DI1*/
#define C_TWCalDataMeterIC_DI1			0x82		/*��д����оƬ����У�����DT1*/
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
/************************Table2���Ͷ���********************
MeterIC_WR��EE_WR��ȡֵ0xX X
						 | |
						 | |__Ϊ�ȱ�־:Ϊ1�ɶ���Ϊ0���ɶ�
						 |____Ϊд��־:Ϊ1��д��Ϊ0����д
								�ɶ���дC_WandR_Table2
								�ɶ�����дC_Read_Table2
								���ɶ���дC_Write_Table2
								���ɶ�����дC_NoWR_Table2
NO_Amount��ʵ���ݵı�ʶ���������
NO_Buffer2��λ���ݱ�ʶ�����
NO_Buffer2��λ���ݱ�ʶ�����
NO_Buffer2��λ���ݱ�ʶ�����
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
/************************Table2����оƬУ�������д����********************/
#define C_CalData_Len				0x74							/*У����������ݳ���*/
const Str_MeterICTable2_Type Str_Table2_CalData[C_CalData_Len]=
{
/*  DI0		����оƬ��дȨ��	   ���ݲ��дȨ��		У��ͼĴ���	��Ÿ���		��λ��ʵ�������	��λ��ʵ�������	��λ��ʵ�������*/
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
/************************Table3���Ͷ���********************
MeterIC_WR��EE_WR��ȡֵ0xX X
						 | |
						 | |__Ϊ�ȱ�־:Ϊ1�ɶ���Ϊ0���ɶ�
						 |____Ϊд��־:Ϊ1��д��Ϊ0����д
								�ɶ���дC_WandR_Table2
								�ɶ�����дC_Read_Table2
								���ɶ���дC_Write_Table2
								���ɶ�����дC_NoWR_Table2
NO_Amount��ʵ���ݵı�ʶ���������
NO_Buffer2��λ���ݱ�ʶ�����
NO_Buffer2��λ���ݱ�ʶ�����
NO_Buffer2��λ���ݱ�ʶ�����
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
/*  DI0		����оƬ��дȨ��	���ݲ��дȨ��		У��ͼĴ���	��Ÿ���		0λ��ʵ�������		1λ��ʵ�������		2λ��ʵ������� 	3λ��ʵ�������		4λ��ʵ�������		5λ��ʵ������� 	6λ��ʵ�������		7λ��ʵ�������		8λ��ʵ�������*/
	0x00,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_ThreeDIAmount,0x17,				0x18,				0x19,				C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			/*��ѹ����У������*/
	0x01,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_ThreeDIAmount,0x1A,				0x1B,				0x1C,				C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			/*��������У������*/
	0x02,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_ThreeDIAmount,0x04,				0x05,				0x06,				C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			/*�й���������У������*/
	0x03,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_ThreeDIAmount,0x0D,				0x0E,				0x0F,				C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			/*��λУ��0����*/
	0x04,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_ThreeDIAmount,0x10,				0x11,				0x12,				C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			/*��λУ��1����*/
	0x05,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_ThreeDIAmount,0x61,				0x62,				0x63,				C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,		 	/*��λУ��2����*/
	0x06,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_ThreeDIAmount,0x27,				0x28,				0x29,				C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			/*������ЧֵoffsetУ������*/
	0x07,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_ThreeDIAmount,0x07,				0x08,				0x09,				C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			/*�޹���������У������*/
	0x08,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_ThreeDIAmount,0x0A,				0x0B,				0x0C,				C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			/*���ڹ�������У������*/
	0x09,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_SixDIAmount,	0x10,				0x11,				0x12,				0x0D,				0x0E,				0x0F,				C_NT_NO,			C_NT_NO,			C_NT_NO,			/*˳�����ABC��ѹABCԭʼֵ��ȡ����*/
	0x0A,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_FourDIAmount,	0x01,				0x02,				0x03,				0x04,				C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			C_NT_NO,			/*�й�����ԭʼֵ��˳��ABC����*/
	0x0B,	C_NoWR_Table2,		C_NoWR_Table2,		C_NT_Check,		C_SixDIAmount,	0x1A,				0x1B,				0x1C,				0x17,				0x18,				0x19,				C_NT_NO,			C_NT_NO,			C_NT_NO,			/*˳�����ABC��ѹABC��������У������*/
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

/* ֱ��ż��г������ */
void InF_InitialEvenHarmonicCompensationTime( void );
uchar8 SF_GetEvenHarmonicCompensationFlag( void );
void SF_GetEvenHarmonicContent(void);
void SF_GetEvenHarmonicCompensationValue( ushort16 *pV_usCompTemp );
void SF_EvenHarmonicCompensation( ushort16 *pV_usCompTemp, uchar8 V_ucRegAddress );

/*zlj����*/
typedef struct
{
	long64 ActivePowerSummer_TABC[4];		/*1min����ABC�й������ۼӺ�*/
	long64 ReativePowerSummer_TABC[4];		/*1min����ABC�޹������ۼӺ�*/
	uchar8 Number;							/*1min�����ۼӴ���*/
}Str_PowerAdd_Type;

#define C_PowerTypeNum			8		/*��������*/

/*˲ʱ����������ABC��TABC��ƫ�ƣ����е�ABC��TABCƫ�ƶ�ͳһ������궨��*/
#define C_offA		0		/*����T������ABCƫ��*/
#define C_offB		1
#define C_offC		2

#define C_offTT		0		/*��T������TABCƫ��*/
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
