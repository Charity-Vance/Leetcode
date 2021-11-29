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

#include "Public.h"
#include "MeterICDrive.h"
#include "MeterIC.h"

/*******************************************************************************
����������	ż��г������
*******************************************************************************/
//���������
#define	C_BuffStr		0xC0		/*�������ݻ�����������*/
#define	C_BuffSet		0xC1		/*�������ݶ�ָ������*/
#define	C_ClrCali		0xC3		/*��У������*/
#define	C_SyncSet		0xC4		/*ͬ������ϵ������*/
#define	C_SyncStr		0xC5		/*ͬ��������������*/
#define	C_EnRdCali		0xC6		/*У�����ݶ�ʹ��*/
#define	C_EnWrCali		0xC9		/*У������дʹ��*/
#define	C_SoftRst		0xD3		/*��λ*/

#define CL_HD2Rate		6			/*ż��г������������*/

/****************************************�������ƶ���*************************************************/
Str_RealtimePower_Type		GStr_PowerData;				/*�����ù������ݴ洢�ṹ��*/
Str_EnergyData_Type			GStr_EnergyData;			/*����ԭʼֵ���ݴ洢�ṹ��*/
Str_HEX_VARREGTYPE_Type		GStr_HEX_VARREGTYPE;		/*HEX��ʽԤд���ݲ�˲ʱ���洢�ṹ��*/
Str_PowerCoeff_Type			GStr_PowerCoeff;			/*����ϵ���ṹ��*/
ulong32						GV_ulSlipCurrentBuff[3][3];	/*ABC�������3������*/
Str_PowerAdd_Type			GStr_PowerAdd;				/*1min�����ۼӺ�*/

/*****************************ȫ�ֱ�������*********************************************/
long32 GV_lHD2Rate[CL_HD2Rate];
uchar8 GV_ucStepNum;
uchar8 GV_ucEvenHarmonicDelayTimer;
uchar8 GV_ucEvenHarmonicSecondTimer;
ushort16 GV_usEvenHarmonicCompensationTime;

/*******************************************************************************
����ԭ��: void SF_Delay(ulong32 V_ulData)
��������: ��ʱ�����������Ѿ��궨��õ�Delay1uS��ʱ�亯���������ض�ʱ����ʱ
�������: DELAY1US��DELAY2US��DELAY4US��DELAY25MS��DELAY1MS�ض�ʱ���Ѿ�����
�������: ��
���ز���: ��
����λ��: 
��    ע: ����ʱΪӲ��ʱ����ʱ׼ȷ��ȡ����MCU�ڲ�ʱ��Ƶ�ʣ�����ڲ�Ƶ�ʷ����仯����ᵼ����ʱ��׼ȷ��
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
����ԭ��: void SF_ClearUcharArray(uchar8 *pV_ucArray, uchar8 V_ucLength)
��������: ��������
�������: uchar8 *pV_ucArray��uchar8 V_ucLength�����ֽ���
�������: ��
���ز���: ��
����λ��: 
��    ע: ����������ֻ������uchar8���͵����飬��������ushort16���͵����������void SF_ClearUshortArray(ushort16 *pV_usArray, uchar8 V_ucLength)
*******************************************************************************/
void SF_ClearUcharArray(uchar8 *pV_ucArray, uchar8 V_ucLength)
{
	memset(pV_ucArray, 0, V_ucLength);
}

/*******************************************************************************
����ԭ��: void SF_ClearUshortArray(ushort16 *pV_usArray, uchar8 V_ucLength)
��������: ��������
�������: ushort16 *pV_usArray�����׵�ַ,uchar8 V_ucLength��������
�������: ��
���ز���: ��
����λ��: 
��    ע: ������ֻ������ushort16���͵�����
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
����ԭ��: void SF_ClearUlongArray(ulong32 *pV_ulArray, uchar8 V_ucLength)
��������: ��������
�������: ulong32 *pV_ulArray�����׵�ַ,uchar8 V_ucLength��������
�������: ��
���ز���: ��
����λ��: 
��    ע: ������ֻ������ushort16���͵�����
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
����ԭ��: void SF_ENSPIMode_MeterIC(void)
��������: ʹ�ܼ���оƬSPI����
�������: ��
�������: ��
���ز���: ��
����λ��: 
��    ע: ͨ������CS���߿��Ƽ���оƬ
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
����ԭ��: void SF_WriteOneByte_MeterIC(uchar8 V_ucSendData)
��������: д����оƬһ�ֽ�����
�������: uchar8 V_ucSendData׼��д�������
�������: ��
���ز���: ��
����λ��: 
��    ע: ��Ƭ���Ƽ���оƬд���ݲ�������ײ㺯����д�����ݰ��մӸ�λ����λ˳��д��
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
����ԭ��: uchar8 SF_ReadOneByte_MeterIC(void)
��������: ��ȡ����оƬһ�ֽ�����
�������: ��
�������: ��
���ز���: V_ucDataTemp����оƬ��ȡ�����ݣ���ȡ����λ˳��Ϊ�Ӹ�λ����λ
����λ��: 
��    ע: 
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
����ԭ��: void SF_Eable_MeterIC(void)
��������: ʹ�ܼ���оƬ
�������: ��
�������: ��
���ز���: ��
����λ��: 
��    ע: ����CS�ţ�ʹ�ܼ���оƬ
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
����ԭ��: void SF_Disable_MeterIC(void)
��������: ʧ�ܼ���оƬ
�������: ��
�������: ��
���ز���: ��
����λ��: 
��    ע: �ø�CS�ţ�ʧ�ܼ���оƬ
*******************************************************************************/
void SF_Disable_MeterIC(void)
{
	SET_EMETERCS_OUTPUT();
	EMETERCS_DIS;
	SF_Delay(C_DELAY2US);
}

/*******************************************************************************
����ԭ��: void SF_WriteEnable_MeterIC(void)
��������: ����оƬдʹ��
�������: ��
�������: ��
���ز���: ��
����λ��: 
��    ע: ����оƬдʹ��
*******************************************************************************/
void SF_WriteEnable_MeterIC(void)
{
	uchar8 V_ucData[4], V_uci;
	ulong32 V_ulEnWriteData;

	V_ulEnWriteData = C_EnWriteCalDataMeterIC;	/*дʹ��ֱ��д��0xC900005A���ֽ�Ϊ����Ĵ�����ַ,�����ֽ�Ϊд������*/
	SF_Eable_MeterIC();
	PF_Ulong32ToBufferX(V_ucData, &V_ulEnWriteData, C_MeterICDataLEN);
	for (V_uci = C_MeterICDataLEN; V_uci > 0; V_uci--)
	{
		SF_WriteOneByte_MeterIC(V_ucData[V_uci - 1]);
	}
	SF_Disable_MeterIC();
}

/*******************************************************************************
����ԭ��: void SF_WriteDisable_MeterIC(void)
��������: ����оƬдʧ��
�������: ��
�������: ��
���ز���: ��
����λ��: 
��    ע: ����оƬдʹ����Ҫ�ǶԼ���оƬC9����Ĵ������в�����д��0x000000Ϊдʧ�ܣ�д��0x00005AΪдʹ��
*******************************************************************************/
void SF_WriteDisable_MeterIC(void)
{
	uchar8 V_ucData[4], V_uci;
	ulong32 V_ulDisWriteData;

	V_ulDisWriteData = C_DisWriteCalDataMeterIC;	/*дʧ��ֱ��д��0xc9000000���ֽ�Ϊ����Ĵ�����ַ,�����ֽ�Ϊд������*/
	SF_Eable_MeterIC();
	PF_Ulong32ToBufferX(V_ucData, &V_ulDisWriteData, C_MeterICDataLEN);
	for (V_uci = 0; V_uci < C_MeterICDataLEN; V_uci++)
	{
		SF_WriteOneByte_MeterIC(V_ucData[V_uci]);
	}
	SF_Disable_MeterIC();
}

/*******************************************************************************
����ԭ��: uchar8 SF_WriteOneReg_MeterIC(uchar8 *pV_ucData, uchar8 V_ucRegAddr, uchar8 V_ucSafeFlag)
��������: �����ֽ�����д�����оƬ�Ĵ���ָ����ַ(��������дУ������Ĵ���)
�������: uchar8 *pV_ucData��Ԥд������ָ��;uchar8 V_ucRegAddr������оƬ�Ĵ�����ַ;uchar8 V_ucSafeFlag����ȫ��־
�������: ��
���ز���: C_OK��д��ɹ�;C_SafeFlagError�����ݲ���ȫ
����λ��: 
��    ע: ͨ��дһ�ֽ����ݣ�д�뽫��ַ����ַ������λҪ��1��Ȼ�����3��дһ�ֽ����ݣ����Ӹ��ֽڵ����ֽڽ�3�ֽ�����д�����оƬ
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
		SF_WriteOneByte_MeterIC(V_ucRegAddr | C_WriteDataMeterIC);	/*��ַ������λ��1��д������*/
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
����ԭ��: void SF_ReadDataModeSet(uchar8 V_ucModeData)
��������: ѡ�����оƬ�Ĵ�����ȡ����:��ȡ���������Ĵ����Ͷ�ȡУ������Ĵ���
�������: uchar8 V_ucModeData:C_ReadMeaDataRegFlag=��ȡ�������ݼĴ�����C_ReadCalDataRegFlag=��ȡУ������Ĵ���
�������: ��
���ز���: ��
����λ��: 
��    ע: ��ȡ����оƬ�Ĵ������ú�����ͨ����������Ĵ���C6Ϊ0x000000��ȡ���������Ĵ�����Ϊ0x00005A��ȡУ������Ĵ���
*******************************************************************************/
void SF_ReadDataModeSet(uchar8 V_ucModeData)
{
	uchar8 V_ucData[4], V_uci;
	ulong32 V_ulEnWriteData;

	if (V_ucModeData == C_ReadMeaDataRegFlag)
	{
		V_ulEnWriteData = C_EnReadMeaDataMeterIC;	/*����оƬ����Ϊ��ȡ(����)�������ֽ�Ϊ�Ĵ�����ַ�������ֽ�Ϊд������*/
	}
	else
	{
		V_ulEnWriteData = C_EnReadCalDataMeterIC;	/*����оƬ����Ϊ��ȡ(У��)�������ֽ�Ϊ�Ĵ�����ַ�������ֽ�Ϊд������*/
	}
	SF_Eable_MeterIC();								/*CSʹ�ܼ���оƬ*/
	PF_Ulong32ToBufferX(V_ucData, &V_ulEnWriteData, C_MeterICDataLEN);
	for (V_uci = C_MeterICDataLEN; V_uci > 0; V_uci--)
	{
		SF_WriteOneByte_MeterIC(V_ucData[V_uci - 1]);
	}
	SF_Disable_MeterIC();	/*CSʧ�ܼ���оƬ*/
}

/*******************************************************************************
����ԭ��: void SF_ReadOneReg_MeterIC(uchar8 V_ucRegAddr, uchar8 *pV_ucData, uchar8 V_ucMeaORCal)
��������: �Ӽ���оƬ���������Ĵ����ж�ȡ���ֽ�����
�������: uchar8 V_ucRegAddr��Ԥ��ȡ����оƬ�Ĵ�����ַ;uchar8 *pV_ucData������ת��ָ��;uchar8 V_ucMeaORCal  C_ReadMeaDataRegFlag:��ȡ���������Ĵ���   C_ReadCalDataRegFlag:��ȡУ������Ĵ���
�������: uchar8 *pV_ucData����ָ���д洢V_ucRegAddr��ַ�µ����ֽ�����(7022EоƬ��ȡ�ļ�������Ϊ���ֽ���Ч��У�����Ϊ���ֽ���Ч)
���ز���: ��ȡ�ɹ�C_OK
����λ��: 
��    ע: ��ȡ����оƬ�Ĵ������ú�����ͨ����������Ĵ���C6Ϊ0x000000��ȡ���������Ĵ�����Ϊ0x00005A��ȡУ������Ĵ���
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
����ԭ��: void SF_ReadBufferReg_MeterIC(uchar8 V_ucRegAddr, uchar8 *pV_ucData)
��������: �Ӽ���оƬ���ݻ���Ĵ����ж�ȡ���ֽ�����
�������: uchar8 V_ucRegAddr��Ԥ��ȡ����оƬ�Ĵ�����ַ;uchar8 *pV_ucData������ת��ָ��
�������: uchar8 *pV_ucData����ָ���д洢V_usRegAddr��ַ�µ����ֽ�����(7022EоƬ��ȡ�ļ�������Ϊ���ֽ���Ч��У�����Ϊ���ֽ���Ч)
���ز���: ��ȡ�ɹ�C_OK
����λ��: 
��    ע: ��ȡ����оƬ�Ĵ������ú�����ͨ����������Ĵ���C6Ϊ0x000000��ȡ���������Ĵ�����Ϊ0x00005A��ȡУ������Ĵ���
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
����ԭ��: void SF_HardwareRESET_MeterIC(void)
��������: ͨ����λRESET�ܽţ���λ����оƬ�������������оƬ�������ݼĴ���
�������: ��
�������: ��
���ز���: ��
����λ��: 
��    ע: Ӳ����λ����оƬ���ڸ�λ������IRQ����ߵ�ƽ�������ڸ�λ�ָ���������֮��IRQ��Ϊ�͵�ƽ����д��У�����֮��IRQ�ֻ�����
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
����ԭ��: void SF_PowerDownHardwareRESET_MeterIC(void)
��������: ͨ����λRESET�ܽţ���λ����оƬ�������������оƬ�������ݼĴ���
�������: ��
�������: ��
���ز���: ��
����λ��: 
��    ע: �͹���״̬��Ӳ����λ����оƬ���ڸ�λ������IRQ����ߵ�ƽ�������ڸ�λ�ָ���������֮��IRQ��Ϊ�͵�ƽ����д��У�����֮��IRQ�ֻ�����
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
����ԭ��: void  SF_Initial_MeterIC(uchar8 V_ucInitMode)
��������: ��ʼ������оƬ�����ü���оƬ��ʼ�Ĵ�����������У���
�������: uchar8 V_ucInitModeΪC_InitPowerDownʱΪ�͹���ģʽ�³�ʼ������оƬ��ΪC_InitNormalʱΪ����ģʽ�³�ʼ������оƬ
�������: ��
���ز���: ��
����λ��: 
��    ע: 
*******************************************************************************/
void  SF_Initial_MeterIC(uchar8 V_ucInitMode)
{
	uchar8 V_ucCalRegData[4], V_uci, V_ucDataLen;
	ushort16 V_usData;
	ulong32 V_ulCalData;

	SF_HardwareRESET_MeterIC();												/*Ӳ����λ����оƬ*/
	SF_ENSPIMode_MeterIC();
	SF_Eable_MeterIC();
	GV_ulCalDataChk0SUM = C_Check0RetData;
	GV_ulCalDataChk1SUM = C_Check1RetData;
	SF_ClearUcharArray(V_ucCalRegData, 4);
	V_usData = C_ModeCfg_Data;
	if (V_ucInitMode == C_InitPowerDown)
	{
		V_usData &= 0xDFFF;													/*�͹��ĳ�ʼ��ģʽ���bit13����*/
	}
	PF_Ushort16ToBuffer2(V_ucCalRegData, &V_usData);
	SF_WriteOneReg_MeterIC(V_ucCalRegData, C_ModeCfg_Reg, C_DataSafe);		/*ģʽ��ؿ��Ƴ�ʼ��*/
	SF_TemRectify_MeterIC();
	SF_ClearUcharArray(V_ucCalRegData, 4);
	V_usData = C_ModuleCFG_Data;
	PF_Ushort16ToBuffer2(V_ucCalRegData, &V_usData);
	SF_WriteOneReg_MeterIC(V_ucCalRegData, C_ModuleCFG_Reg, C_DataSafe);	/*����ģ��������ó�ʼ��*/
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
					if (Str_Table2_CalData[V_uci].Check == C_Check0_Reg)	/*У���0����*/
					{
						GV_ulCalDataChk0SUM += V_ulCalData;
						GV_ulCalDataChk0SUM &= 0x00FFFFFF;
					}
					if (Str_Table2_CalData[V_uci].Check == C_Check1_Reg)	/*У���1����*/
					{
						GV_ulCalDataChk1SUM += V_ulCalData;
						GV_ulCalDataChk1SUM &= 0x00FFFFFF;
					}
					GV_ucWriteRegSafeFlag = C_DataSafe;
					if ( (V_uci == 0x03) && (V_ucInitMode == C_InitPowerDown) )
					{
						V_ucCalRegData[1] &= 0x0F;							/*�͹�������EMU�������ر��������*/
					}
					SF_WriteOneReg_MeterIC(V_ucCalRegData, V_uci, GV_ucWriteRegSafeFlag);
				}
				else
				{
					if (InF_Read_RecMeterData(V_uci, V_ucCalRegData, &V_ucDataLen) == C_OK)
					{
						PF_BufferXToUlong32(V_ucCalRegData, &V_ulCalData, V_ucDataLen);
						if (Str_Table2_CalData[V_uci].Check == C_Check0_Reg)	/*У���0����*/
						{
							GV_ulCalDataChk0SUM += V_ulCalData;
							GV_ulCalDataChk0SUM &= 0x00FFFFFF;
						}
						if (Str_Table2_CalData[V_uci].Check == C_Check1_Reg)	/*У���1����*/
						{
							GV_ulCalDataChk1SUM += V_ulCalData;
							GV_ulCalDataChk1SUM &= 0x00FFFFFF;
						}
						GV_ucWriteRegSafeFlag = C_DataSafe;
						if ( (V_uci == 0x03) && (V_ucInitMode == C_InitPowerDown) )
						{
							V_ucCalRegData[1] &= 0x0F;							/*�͹�������EMU�������ر��������*/
						}
						SF_WriteOneReg_MeterIC(V_ucCalRegData, V_uci, GV_ucWriteRegSafeFlag);
					}
					else
					{
						GV_ulCalDataChk0SUM = ~GV_ulCalDataChk0SUM;				/*������ݲ��ȡУ�����ʧ����У�������ȥ����ʹУ������ݴ���*/
						GV_ulCalDataChk1SUM = ~GV_ulCalDataChk1SUM;
						break;
					}
				}
			}
		}
	}
	GStr_PowerData.Deriction = 0;												/*���ʷ���ȫ����ʼΪ����*/
}

/*******************************************************************************
����ԭ��: void SF_ClearEnergyData_MeterIC(void)
��������: �����оƬ���ܼĴ���
�������: ��
�������: ��
���ز���: ��
����λ��: 
��    ע: ͨ����ȡ����оƬ�ĵ��ܼĴ���������������ܼĴ�����Ŀ�ģ�����оƬ����Ϊ������
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
����ԭ��: void SF_TemRectify_MeterIC(void)
��������: �����¶Ȳ������У�����
�������: ��
�������: ��
���ز���: ��
����λ��: 
��    ע: (��δʹ��)�����¶Ȳ����Ĵ�����ȫͨ������Ĵ���(��ַ��0x32)���ϵ��ʼ������1��û��У�üĴ���������Ĭ��ֵ
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
		if ( (V_ucReturnFlag != C_OK) || (V_ulCalData32 == 0) )												/*�����Ҳ����Ĭ��ֵ*/
		{
			V_ucDataLen = C_CalDataLen;
			InF_Write_RecMeterData(C_Msg_Communication, V_ucCalRegData, V_ucDataLen, C_W_SafeFlag, V_ucj);	/*дE2����,�ȵ�����У���ʱ���¸��¼����Ĵ���*/
		}
	}
	V_ucj = C_AllGain_Reg;
	V_ucDataLen = C_CalDataLen;
	if (C_Temp_VrefAotu == C_Temp_VrefAotu_En)																/*ʹ���¶Ȳ�����*/
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
		InF_Write_RecMeterData(C_Msg_Communication, V_ucCalRegData, V_ucDataLen, C_W_SafeFlag, V_ucj);		/*дE2����,�ȵ�����У���ʱ���¸��¼����Ĵ���*/
	}
	else											/*У�����ȷ���жϽ�ֹ�¶�ʹ�ܣ���ֵ����Ϊ0����ֹԭ��ʹ�ܣ������ֱ���Ϊ��ֹʹ�����*/
	{
		if (C_Temp_VrefAotu != C_Temp_VrefAotu_En)	/*��ֹ�¶Ȳ�����*/
		{
			if (C_Equal != PF_Campare_Data(V_ucCalRegData1, V_ucCalRegData, C_CalDataLen) )
			{
				InF_Write_RecMeterData(C_Msg_Communication, V_ucCalRegData, V_ucDataLen, C_W_SafeFlag, V_ucj);		/*дE2����,�ȵ�����У���ʱ���¸��¼����Ĵ���*/
			}
		}
		else
		{
			V_ucCalRegData1[3] = 0;
			PF_BufferXToUlong32(V_ucCalRegData1, &V_ulCalData32, 4);
			if (V_ulCalData32 == 0)					/*�����Ҳ����Ĭ��ֵ*/
			{
				InF_Write_RecMeterData(C_Msg_Communication, V_ucCalRegData, V_ucDataLen, C_W_SafeFlag, V_ucj);		/*дE2����,�ȵ�����У���ʱ���¸��¼����Ĵ���*/
			}
		}
	}
}

/*******************************************************************************
����ԭ��: void SF_Power_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE)
��������: �������ݶ�ȡ
�������: Str_VARREGTYPE_Type *pStr_VARREGTYPE:ԭʼֵ���ָ��
�������: Str_VARREGTYPE_Type *pStr_VARREGTYPE:ԭʼֵ���ָ��
          Str_VARREGTYPE�ṹ���е��й��������ݡ��޹��������ݺ����ڹ�������(��Ϊ����оƬ�е�����ԭʼֵ)
���ز���: ��
����λ��: 
��    ע: ������оƬ�еĹ�������ԭʼֵ��ȡ�������洢����Ӧ�Ľṹ�嵱��
*******************************************************************************/
void SF_Power_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE)
{
	uchar8 V_uci, V_ucData[4];
	/*************�й��������ݶ�ȡ**************/
	for (V_uci = 0; V_uci < 4; V_uci++)
	{
		SF_ClearUcharArray(V_ucData, 4);
		SF_ReadOneReg_MeterIC(Str_PowerRegADDr[V_uci], V_ucData, C_ReadMeaDataRegFlag);
		PF_BufferXToUlong32(V_ucData, &pStr_VARREGTYPE->WATTReg[V_uci], C_MeaDataLen);
	}
	/*************�޹��������ݶ�ȡ**************/
	for (V_uci = 0; V_uci < 4; V_uci++)
	{
		SF_ClearUcharArray(V_ucData, 4);
		SF_ReadOneReg_MeterIC(Str_PowerRegADDr[V_uci + 4], V_ucData, C_ReadMeaDataRegFlag);
		PF_BufferXToUlong32(V_ucData, &pStr_VARREGTYPE->VARReg[V_uci], C_MeaDataLen);
	}
	/*************���ڹ������ݶ�ȡ**************/
	for (V_uci = 0; V_uci < 4; V_uci++)
	{
		SF_ClearUcharArray(V_ucData, 4);
		SF_ReadOneReg_MeterIC(Str_PowerRegADDr[V_uci + 8], V_ucData, C_ReadMeaDataRegFlag);
		PF_BufferXToUlong32(V_ucData, &pStr_VARREGTYPE->VAReg[V_uci], C_MeaDataLen);
	}
}

/*******************************************************************************
����ԭ��: void SF_Variable_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE)
��������: ��ȡ������������Ƶ�ʡ���ǡ��¶ȡ���ѹ�н����ݣ��洢���ض��ṹ����
�������: Str_VARREGTYPE_Type *pStr_VARREGTYPE��ԭʼֵָ��
�������: Str_VARREGTYPE�ṹ���еĹ����������ݡ�����Ƶ�ʡ�������ǡ��¶ȡ���ѹ������ݣ���Ϊ����оƬԭʼֵ
���ز���: ��
����λ��: 
��    ע: ��һЩ����������ԭʼֵ��ȡ�������洢����Ӧ�ṹ�嵱��
*******************************************************************************/
void SF_Variable_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE)
{
	uchar8 V_uci, V_ucData[4];
	ulong32 *pV_ulVARREGTYPE[11] = {&pStr_VARREGTYPE->PfReg[0],  &pStr_VARREGTYPE->PfReg[1],  &pStr_VARREGTYPE->PfReg[2], &pStr_VARREGTYPE->PfReg[3],	/*��������ԭʼֵ�ṹ��*/
									&pStr_VARREGTYPE->FREQUENCY,																						/*����Ƶ��ԭʼֵ�ṹ��*/
									&pStr_VARREGTYPE->YUIReg[0], &pStr_VARREGTYPE->YUIReg[1], &pStr_VARREGTYPE->YUIReg[2],								/*�������ԭʼֵ�ṹ��*/ 
									&pStr_VARREGTYPE->YUReg[0],  &pStr_VARREGTYPE->YUReg[1],  &pStr_VARREGTYPE->YUReg[2]};								/*��ѹ���ԭʼֵ�ṹ��*/ 

	/******************��������+����Ƶ��+�������+��ѹ��Ƕ�ȡ(4+1+3+3��=11����*****************/
	for (V_uci = 0; V_uci < 11; V_uci++)
	{
		SF_ClearUcharArray(V_ucData, 4);
		SF_ReadOneReg_MeterIC(Str_VariableRegADDr[V_uci], V_ucData, C_ReadMeaDataRegFlag);
		PF_BufferXToUlong32(V_ucData, pV_ulVARREGTYPE[V_uci], C_MeaDataLen);
	}
}

/*******************************************************************************
����ԭ��: void SF_Urms_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE)
��������: ��ȡ��ѹ���ݣ��洢���ض��ṹ����
�������: Str_VARREGTYPE_Type *pStr_VARREGTYPE:ԭʼֵָ��
�������: Str_VARREGTYPE�ṹ���еĵ�ѹ���ݣ�Ϊ����оƬ�е�ԭʼֵ
���ز���: ��
����λ��: 
��    ע: ��ȡ��ѹ����ԭʼ���ݣ��洢����Ӧ�ṹ�嵱��
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
����ԭ��: void SF_Irms_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE)
��������: ��ȡ�������ݣ��洢���ض��ṹ����
�������: Str_VARREGTYPE_Type *pStr_VARREGTYPE:ԭʼֵָ��
�������: Str_VARREGTYPE�ṹ���еĵ������ݺ����ߵ������ݣ���Ϊ����оƬԭʼֵ
���ز���: ��
����λ��: 
��    ע: ��ȡ��������ԭʼ���ݣ��洢����Ӧ�ṹ�嵱��
*******************************************************************************/
void SF_Irms_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE)
{
	uchar8 V_uci, V_ucData[4];

	/**********************�������ݶ�ȡ**********************/
	for (V_uci = 0; V_uci < C_IrmsRegADDrTol; V_uci++)
	{
		SF_ClearUcharArray(V_ucData, 4);
		SF_ReadOneReg_MeterIC(Str_IrmsRegADDr[V_uci], V_ucData, C_ReadMeaDataRegFlag);
		PF_BufferXToUlong32(V_ucData, &pStr_VARREGTYPE->VRmsIReg[V_uci], C_MeaDataLen);
	}
	/**********************�������ʸ�������ݶ�ȡ******************/
	SF_ClearUcharArray(V_ucData, 4);
	SF_ReadOneReg_MeterIC(C_IRmsN0_Reg, V_ucData, C_ReadMeaDataRegFlag);
	PF_BufferXToUlong32(V_ucData, &pStr_VARREGTYPE->IRmsN0, C_MeaDataLen);
	/**********************���ߵ������ݶ�ȡ******************/
	SF_ClearUcharArray(V_ucData, 4);
	SF_ReadOneReg_MeterIC(C_IORms_Reg, V_ucData, C_ReadMeaDataRegFlag);
	PF_BufferXToUlong32(V_ucData, &pStr_VARREGTYPE->IRmsNOSample, C_MeaDataLen);
}

/*******************************************************************************
����ԭ��: void SF_CurrentThreshold_MeterIC(ulong32 *pV_ulIrmsData)
��������: ������ĵ���ԭʼֵ���з�ֵ�жϣ�Ȼ�󷵻ؾ�����ֵ�ж�֮��ĵ���ԭʼֵ
�������: ulong32  *pV_ulIrmsData����ԭʼֵ
�������: ulong32 *pV_ulIrmsData����ԭʼֵ
���ز���: ��
����λ��: 
��    ע: ��ȡ��������ԭʼ���ݣ��洢����Ӧ�ṹ�嵱��
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
����ԭ��: void  SF_ReadEnergyData_MeterIC (void)
��������: ͨ���˺��������������ݴӼ���оƬ�ж�ȡ�������洢����Ӧ�ṹ���У��Ա�����
�������: ��
�������: GStr_EnergyData�ṹ���еĵ������ݣ�Ϊ����оƬԭʼֵ
���ز���: ��
����λ��: 
��    ע: ��ȡ��������ԭʼ���ݣ��洢����Ӧ�ṹ�嵱��
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
����ԭ��: void InF_MeterIC_ParseMessage(Str_Msg_Parameter *pStr_Msg_Parameter)
��������: ����оƬ500mS��Ϣ����
�������: pStr_Msg_Parameter: ͳһ��Str_Msg_Parameter�ͱ���
�������: GStr_EnergyData�ṹ���еĵ������ݣ�Ϊ����оƬԭʼֵ
         SourceAddr= C_Msg_Dispatch��Դ��ַΪ����
         SourceAddr= C_Msg_MeterIC��Դ��ַΪ����ģ��
         DerictAddr = C_Msg_MeterIC
         Length=2��
         *Parameter=C_HalfSecond������500mS
         Length=1��
         �����ݡ��ϵ��ʼ������оƬ
���ز���: ��
����λ��: ����ÿ500ms���û����ϵ�ʱ�ɼ���ģ��ӿں���������ʼ������оƬ��Ϣ��
��    ע: 
*******************************************************************************/
void InF_MeterIC_ParseMessage(Str_Msg_Parameter *pStr_Msg_Parameter)
{
	uchar8 V_ucData;
	ushort16 V_usDataLEN, V_usDataLenth, V_usDataEncode = 0;
	if (pStr_Msg_Parameter->DerictAddr == C_Msg_MeterIC)
	{
		/*************************500mS��Ϣ����*************************/
		if ( (pStr_Msg_Parameter->SourceAddr == C_Msg_Dispatch) && (pStr_Msg_Parameter->PowerFlag == C_PowerOn) )
		{
			if (pStr_Msg_Parameter->Length == (Pt_Dispatch_Timing_Len + 1) )
			{
				if (*(pStr_Msg_Parameter->Parameter + 1) == C_HalfSecond)
				{
					SF_500mS_MeterIC();
				}
				if(*(pStr_Msg_Parameter->Parameter + 1) == C_SystemMinChange)			/*zlj��������min�仯*/
				{
					SF_Cal1minAveragePower(&GStr_PowerAdd);
				}
			}
		}
		/*************************������ʼ����Ϣ����*************************/
		if ( (pStr_Msg_Parameter->SourceAddr == C_Msg_MeterIC) && (pStr_Msg_Parameter->PowerFlag == C_PowerOn) )
		{
			if (pStr_Msg_Parameter->Length == (Pt_InitialMeterIC_Len + 1) )
			{

				SF_InitialALL_MeterIC(C_InitNormal);
			}
		}
		/*************************����оƬ����������Ϣ����*************************/
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
����ԭ��: void  SF_InitialALL_MeterIC (uchar8 V_ucInitMode)
��������: ��ʼ������ģ��
�������: uchar8 V_ucInitModeΪC_InitPowerDownʱΪ�͹���ģʽ�³�ʼ������оƬ��ΪC_InitNormalʱΪ����ģʽ�³�ʼ������оƬ
�������: GV_ucUpdateTime:˲ʱ���������ݲ㶨ʱ����ʼ��
          GV_ucCheckTime:У���У�鶨ʱ����ʼ��
          GV_ucEnergyLock:���ܱ�����־��Ϊ����״̬
          GStr_HEX_VARREGTYPE�ṹ������
���ز���: ��
����λ��: 
��    ע: ���ó�ʼ������оƬ�Ӻ������������м���ģ���ڲ�ʱ��̬������ʼ��
*******************************************************************************/
void  SF_InitialALL_MeterIC (uchar8 V_ucInitMode)
{
	uchar8 V_ucData;
	ushort16 V_usDataLen, V_usDataEncode = 0;
	ulong32 V_ulCurrentThresholdData;
    
	V_ulCurrentThresholdData = SF_CurrentThresholdGain_MeterIC();
	SF_Initial_MeterIC(V_ucInitMode);
	SF_InitialPowerCoeff();				/*��ʼ������ϵ����RAM*/
	GV_ucUpdateTime = C_UpdateTime;		/*˲ʱ���������ݲ㶨ʱ����ʼ��*/
	GV_ucCheckTime = C_CheckTime;		/*У���У�鶨ʱ����ʼ��*/
	GV_ucEnergyLock = C_EnergyLock;		/*���ܱ�����־��Ϊ����״̬*/
	GV_ucMeterICNum = 0;
	GV_ucMeterICErrorFlag = C_MeterICNormal;

	GV_ulSlipCurrentBuff[C_offA][0] = V_ulCurrentThresholdData;
	GV_ulSlipCurrentBuff[C_offB][0] = V_ulCurrentThresholdData;
	GV_ulSlipCurrentBuff[C_offC][0] = V_ulCurrentThresholdData;

	/*************************Ӳ������״̬�ִ���**************************/
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
	/************************HEX���ݽṹ������**************************/
	memset(&GStr_HEX_VARREGTYPE, 0x00 , sizeof(GStr_HEX_VARREGTYPE) );

	/************************���ݲ�˲ʱ������****************************/
	InF_ClearHexVarregtype_MeterIC(C_ClearCurrData);
}

/*******************************************************************************
����ԭ��: void SF_Odd_Harmonic_CheckCurrent(uchar8 V_ucConditionFlag)
��������: �������г������,���������жϴ���
�������: C_Odd_Harmonic_CurrentFitFlag1 ���г�������������ж�����1��־(2.8-4A)
          C_Odd_Harmonic_CurrentFitFlag2 ���г�������������ж�����2��־(1.4-2A)
�������: ��
���ز���: C_OK  C_Error
����λ��: 
��    ע: ���г������������������2��������Ӧ����̨�壩��2.8-4A��1.4-2A���������������в���
*******************************************************************************/
void SF_Odd_Harmonic_CheckCurrent(uchar8 V_ucConditionFlag)
{
	uchar8 V_uci;
	ulong32 V_ulCurrent; 
	
	switch (V_ucConditionFlag)
	{
		case C_Odd_Harmonic_CurrentFitFlag1:							/*��������1�жϣ�2.8-4A��*/
		{
			for (V_uci = 0; V_uci < 3; V_uci++)							/*A��B��C�����ж�*/
			{
				V_ulCurrent = SF_ABS(GStr_HEX_VARREGTYPE.VRmsIRegHEX_ABC[V_uci]);
				if ( (V_ulCurrent < 2800) || (V_ulCurrent > 4000) )		/*��������1��Χ*/
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

		case C_Odd_Harmonic_CurrentFitFlag2:							/*��������2�жϣ�1.4-2A)*/
		{
			for (V_uci = 0; V_uci < 3; V_uci++)							/*A��B��C�����ж�*/
			{
				V_ulCurrent = SF_ABS(GStr_HEX_VARREGTYPE.VRmsIRegHEX_ABC[V_uci]);
				if ( (V_ulCurrent < 1400) || (V_ulCurrent > 2000) )		/*��������2��Χ*/
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
����ԭ��: uchar8 SF_Odd_Harmonic_AddData(uchar8 V_ucPhaseCh, uchar8 *pV_ucAddData, ulong32 *pV_ulPgain_Data)
��������: �������г�������У��Թ���������в���
�������: V_ucPhaseCh:�����ж�ABC�࣬pV_ucAddData������ֵ��ַ
�������: pV_ulPgain_Data���������й���������ֵ��ַ
���ز���: C_OK  C_Error
����λ��: 
��    ע: 
*******************************************************************************/
uchar8 SF_Odd_Harmonic_AddData(uchar8 V_ucPhaseCh, uchar8 *pV_ucAddData, ulong32 *pV_ulPgain_Data)
{
	uchar8 V_ucDataLength, V_ucReturnFlag;
	uchar8 V_ucPgain_Data[3];

	V_ucDataLength = C_CalDataLen;
	V_ucReturnFlag = InF_Read_RecMeterData(V_ucPhaseCh, V_ucPgain_Data, &V_ucDataLength);	/*A���й���������0x04*/

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
����ԭ��: uchar8 SF_Odd_Harmonic_NOAddData(uchar8 V_ucPhaseCh, uchar8 *pV_ucAddData, ulong32 *pV_ulPgain_Data)
��������: �������г������ʱ����ȡ��������
�������: V_ucPhaseCh:�����ж�ABC�࣬pV_ucAddData������ֵ��ַ
�������: pV_ulPgain_Data���������й���������ֵ��ַ
���ز���: C_OK  C_Error
����λ��: 
��    ע: 
*******************************************************************************/
uchar8 SF_Odd_Harmonic_NOAddData(uchar8 V_ucPhaseCh, uchar8 *pV_ucAddData, ulong32 *pV_ulPgain_Data)
{
	uchar8 V_ucDataLength, V_ucReturnFlag;
	uchar8 V_ucPgain_Data[3];

	V_ucDataLength = C_CalDataLen;
	V_ucReturnFlag = InF_Read_RecMeterData(V_ucPhaseCh, V_ucPgain_Data, &V_ucDataLength);	/*A���й���������0x04*/

	PF_BufferXToUlong32(V_ucPgain_Data, pV_ulPgain_Data, C_CalDataLen);

	return V_ucReturnFlag;
}

/*******************************************************************************
����ԭ��: void SF_Odd_Harmonic_Deal(void)
��������: �������г����������
�������: ��
�������: ��
���ز���: ��
����λ��: 
��    ע: ���г��������������������Լ0.650-0.860��������2��������Ӧ����̨�壩��2.8-4A��1.4-2A���������������в���
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
      && (SF_ABS(GStr_HEX_VARREGTYPE.PowerFactorHEX_TABC[C_offTT]) <= 860) )							/*���������Ƿ���0.650-0.860��Χ��*/
	{
		GV_ucPowerFactor_Flag |= 0x01;
	}
	else
	{
		GV_ucPowerFactor_Flag &= 0xFE;
	}
	/********��������1�жϣ�2.8-4A��***********/
	SF_Odd_Harmonic_CheckCurrent(C_Odd_Harmonic_CurrentFitFlag1);
	/********��������2�жϣ�1.4-2A��***********/
	SF_Odd_Harmonic_CheckCurrent(C_Odd_Harmonic_CurrentFitFlag2);
	if ( (GV_ucPowerFactor_Flag & C_Odd_Harmonic_3TimesFitCon) == C_Odd_Harmonic_3TimesFitCon)
	{
		if ( (GV_ucCurrent_Flag1 & C_Odd_Harmonic_3TimesFitCon) == C_Odd_Harmonic_3TimesFitCon)			/*3�ζ���������*/
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
			if ( (GV_ucCurrent_Flag2 & C_Odd_Harmonic_3TimesFitCon) == C_Odd_Harmonic_3TimesFitCon)		/*3�ζ���������*/
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
			else	/*�ɲ���ģʽ���뵽������ʱ����Ҫ����д�Ĵ���*/
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
					/*ABC����¼���оƬ�Ĵ�����У���*/
				SF_ReadOneReg_MeterIC(V_ucPgainABC_Reg[V_uci], V_ucData, C_ReadCalDataRegFlag);
				PF_BufferXToUlong32(V_ucData, &V_ulDataBefor, 3);
				if (V_ulDataBefor != V_ulPgainABC_Data[V_uci])
				{
					PF_Ulong32ToBufferX(V_ucData, &V_ulPgainABC_Data[V_uci], 4);
					SF_WriteOneReg_MeterIC(V_ucData, V_ucPgainABC_Reg[V_uci], C_DataSafe);/*���¼���оƬ�Ĵ���*/
					GV_ulCalDataChk0SUM = GV_ulCalDataChk0SUM - V_ulDataBefor + V_ulPgainABC_Data[V_uci];
				}
			}
		}
	}
}

/*******************************************************************************
����ԭ��: Void SF_500mS_MeterIC(void)
��������: ���ڼ���ģ����Ϣ������ã�ÿ������һ��Ϊ500mSʱ�䣬ͨ����500mSʱ��ļ�����ȡ���ڲ�ʵʱʱ��
�������: ��
�������: ��
���ز���: ��
����λ��: 
��    ע: ͨ�����ȴ���500mSʱ�亯����������ʱ��̬�������м������������ʱ�����㽫������Ӧ��������
*******************************************************************************/
void SF_500mS_MeterIC(void)
{
	uchar8 V_ucData, V_ucDataLen, V_ucTempDataBuffer[5];
	uchar8 V_ucReturnFlag;
	char8 V_cTemp;
	ushort16 V_usCompTemp[3], V_usDataLen, V_usDataEncode = 0;

	/*******************У���У��**********************/
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
			if (C_Temp_VrefAotu == C_Temp_VrefAotu_En)	/*ʹ���¶Ȳ�����ÿs�ж�TPSdata�Ĵ����¶�ֵ*/
			{
				SF_ReadOneReg_MeterIC(C_TempReg_Reg, V_ucTempDataBuffer, C_ReadMeaDataRegFlag);

				if (V_ucTempDataBuffer[0] > 128)
				{
					V_cTemp = V_ucTempDataBuffer[0] - 256;
				}
				else									/*128����*/
				{
					V_cTemp = (char8)(V_ucTempDataBuffer[0]);
					if (V_ucTempDataBuffer[0] == 128)
					{
						V_cTemp = 0;					/*ʹ���¶Ȳ���*/
					}
				}
				V_ucDataLen = C_CalDataLen;
				V_ucReturnFlag = InF_Read_RecMeterData(C_EMCfg_Reg, V_ucTempDataBuffer, &V_ucDataLen);	/*�¶Ȳ����Ĵ���0x70*/
				V_ucDataLen = C_CalDataLen;
				if (C_OK == V_ucReturnFlag)
				{
					if (V_cTemp < C_TempOverData)		/*�ر��¶Ȳ���*/
					{
						if ( (V_ucTempDataBuffer[0] & C_VrefAotu_En) != C_VrefAotu_Dis)
						{
							V_ucTempDataBuffer[0] &= (~C_VrefAotu_En);
							SF_WriteOneReg_MeterIC(V_ucTempDataBuffer, C_EMCfg_Reg, C_DataSafe);		/*���¼���оƬ�Ĵ���*/
							InF_Write_RecMeterData(C_Msg_Communication, V_ucTempDataBuffer, V_ucDataLen, C_W_SafeFlag, C_EMCfg_Reg);	/*дE2����*/
							GV_ulCalDataChk1SUM -= C_VrefAotu_En;										/*����У���*/
						}
					}
					else								/*ʹ���¶Ȳ���*/
					{
						if ( (V_ucTempDataBuffer[0] & C_VrefAotu_En) != C_VrefAotu_En)
						{
							V_ucTempDataBuffer[0] |= C_VrefAotu_En;
							SF_WriteOneReg_MeterIC(V_ucTempDataBuffer, C_EMCfg_Reg, C_DataSafe);		/*���¼���оƬ�Ĵ���*/
							InF_Write_RecMeterData(C_Msg_Communication, V_ucTempDataBuffer, V_ucDataLen, C_W_SafeFlag, C_EMCfg_Reg);	/*дE2����*/
							GV_ulCalDataChk1SUM += C_VrefAotu_En;										/*����У���*/
						}
					}
				}
			}
			else										/*��ֹ����ԭ������Ϊʹ�ܣ����ֱ���Ϊ�ر�ʹ�������*/
			{
				V_ucDataLen = C_CalDataLen;
				InF_Read_RecMeterData(C_EMCfg_Reg, V_ucTempDataBuffer, &V_ucDataLen);					/*�¶Ȳ����Ĵ���0x70*/
				V_ucDataLen = C_CalDataLen;
				if ( (V_ucTempDataBuffer[0] & C_VrefAotu_En) != C_VrefAotu_Dis)
				{
					V_ucTempDataBuffer[0] &= (~C_VrefAotu_En);
					SF_WriteOneReg_MeterIC(V_ucTempDataBuffer, C_EMCfg_Reg, C_DataSafe);				/*���¼���оƬ�Ĵ���*/
					InF_Write_RecMeterData(C_Msg_Communication, V_ucTempDataBuffer, V_ucDataLen, C_W_SafeFlag, C_EMCfg_Reg);			/*дE2����*/
					GV_ulCalDataChk1SUM -= C_VrefAotu_En;												/*����У���*/
				}
			}
			
			if (C_Odd_Harmonic == C_Odd_Harmonic_En)
			{
				SF_Odd_Harmonic_Deal();
			}
			
			if (C_Even_Harmonic == C_Even_Harmonic_En)
			{
					/*ֱ��ż��г���ĵ��㲹��*/
				if (SF_GetEvenHarmonicCompensationFlag() == C_Even_Harmonic_En)
				{
					/*��ȡż��г��������*/
					SF_GetEvenHarmonicContent();
					/*��ȡż��г����������*/
					SF_GetEvenHarmonicCompensationValue(V_usCompTemp);
					/*����ż��г������*/
					SF_EvenHarmonicCompensation(V_usCompTemp, C_PhSregApq0_Reg);
					SF_EvenHarmonicCompensation(V_usCompTemp, C_PhSregApq1_Reg);	/*�е���*/
#if 0
					SF_EvenHarmonicCompensation(V_usCompTemp, C_PhSregApq2_Reg);	/*С����*/
#endif
				}
				else
				{
					SF_ClearUlongArray( (ulong32 *)GV_lHD2Rate, CL_HD2Rate);		/*ż��г������ʧ�ܣ�ż��г������������*/
					GV_ucStepNum = 0;												/*ż��г������ʧ�ܣ����в�������*/
					V_usCompTemp[0] = 0;											/*ż��г������ʧ�ܣ�����ֵ����*/
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
	/**********************���ݲ�˲ʱ������************************/
	GV_ucUpdateTime--;
	if ( (GV_ucUpdateTime == 0) || (GV_ucUpdateTime > C_MAXRepeatTime) )
	{
		GV_ucUpdateTime = C_RepeatTime;
		if (GV_ucMeterICErrorFlag == C_MeterICNormal)
		{
			SF_PowerDataTidy_MeterIC();
		}
	}

	/**********************����оƬ���ϻָ��������ݲ�**************************/
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
����ԭ��: uchar8 SF_Check_MeterIC (void)
��������: ��ȡУ��Ĵ�������У��������м���ó�У������ݣ�Ȼ��ͼĴ����ж�ȡ����У������ݽ��жԱ�
�������: ��
�������: ��
���ز���: C_OKУ��������C_CSErrorУ���쳣
����λ��: 
��    ע: �Լ���ģ���������У�飬ͨ��500mSʱ������ɽ���У���ʱ����ƣ�ÿһ���ӽ���һ��У���У����Ĵ���У��
*******************************************************************************/
uchar8 SF_Check_MeterIC (void)
{
	uchar8 V_ucCalRegDataSUM[4];
	ulong32 V_ulRegCS0SUM, V_ulRegCS1SUM;

	if ( (GV_ucCalibrationState == C_StartCalibrationOK) && (InF_JudgeIJTimer() == C_OK) )		/*����ҲҪ��һ��IJ*/
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
����ԭ��: uchar8  InF_ValtageType(void)
��������: ��ȡ���ݲ㣬��ȡ��ǰ���ܱ��ѹ���
�������: ��
�������: ��
���ز���: 220��380V��C_OK��57.7��100V��C_Error��
����λ��: 
��    ע: ���ڵ�ѹ�����жϣ�220V��380V����Ϊ8V��57.7\100V����ֵΪ2V���������ݲ�ʧ��ʱ��Ĭ��Ϊ57.7V��
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
����ԭ��: uchar8  SF_PhaseSequenceGain_MeterIC(void)
��������: ��ȡ���ݲ㣬��ȡ���ܱ�����
�������: ��
�������: ��
���ز���: �������ߣ�C_3P3W���������ߣ�C_3P4W
����λ��: 
��    ע: ����Ҫ���ܱ�������Ϣʱ��ֱ�ӵ��ô˺���������ֱֵ�Ӿ��ǵ��ܱ�������Ϣ
*******************************************************************************/
uchar8 SF_PhaseSequenceGain_MeterIC(void)
{
	uchar8 V_ucData;
	ushort16 V_usDataLen, V_usDataEncode = 0;

	V_ucData = C_3P4W;	/*��ʼĬ��Ϊ��������*/
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
����ԭ��: ulong32 SF_CurrentThresholdGain_MeterIC(void)
��������: ͨ����ȡ���ݲ㣬��õ�����ֵHEX��
�������: ��
�������: ��
���ز���: ������ֵ��HEX�룩��V_ulCurrentData ��λС��
����λ��: 
��    ע: ͨ����ȡ���ݲ��ȡ������ֵ������HEX��ʽ,����һλС�������ڶԵ�����������
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
	V_ulCurrentData *= 10;	/*����һλС�������ݲ�������������Ϊ��λС�������ǵ�����ֵ�жϳ�������Ҫ��λС������*/
/*���õ�ʱ���Ѿ�������90%��ֵ�Ĵ�������Ͳ�����������*/
	return V_ulCurrentData;
}

/*******************************************************************************
����ԭ��: ulong32 SF_PowerThresholdGain_MeterIC(void)
��������: ͨ����ȡ���ݲ㣬��ú��๦�ʷ�ֵHEX��
�������: ��
�������: ��
���ز���: ���ʷ�ֵ��HEX�룩��V_ulPowerData	XXX.XXXw �޷��� (������Ϊ���๦�ʷ�ֵ)
����λ��: 
��    ע: ͨ����ȡ���ݲ��ȡ���ʷ�ֵHEX�룬���ڶԹ����������㣬����Ϊ�˹������ݡ��������ݺ͵�ѹ����ͳһ���㣬��������������ʱ�ο������͵�ѹ�����Ƿ�Ϊ�㡣
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
	V_ulPowerData *= 75;				/*75%��������Ϊ���ʷ�ֵ*/
	V_ulPowerData /= 100;
	return V_ulPowerData;
}

/*******************************************************************************
����ԭ��: long32 SF_CountRealPower_MeterIC(ulong32 V_ulPowerData, uchar8 V_ucFlagPower)
��������: �����ָ����С��޹�����ԭʼ����ת���ɷ�������ģ��Ҫ���hex����
�������: ulong32 V_ulPowerData��������ԭʼ����
          uchar8 V_ucFlagPower�����������ͣ�C_PowerFlag_TΪ�ܹ��ʱ�ʶ��C_PowerFlag_ABCΪ�����ʶ
          ���C_PowerFactorNO�д洢�Ĺ���ϵ�������ڹ������ݼ���
�������: ��
���ز���: long32 V_lPowerData�з��Ź���ֵ����ЧλΪ1LSB=0.001W
����λ��: 
��    ע: ͨ���˺��������Խ�����ԭʼ���ݻ���ɷ�������Ҫ��Ĺ�����ʵ����hex��ʽ��
*******************************************************************************/
long32 SF_CountRealPower_MeterIC(ulong32 V_ulPowerData, uchar8 V_ucFlagPower)
{
	uchar8 V_ucPowerDataBuffer[8];
	long32 V_lPowerData;				/*zlj�ĳ��з�����*/
	ulong64 V_ullPowerFactorData, V_ullPower8ByteBuffer, V_ullPowerRealData;
	uchar8 V_ucsign = C_Plus;

	/*******************��ȡ����ϵ��***********************/
	V_ullPowerFactorData = SF_GetPowerCoeff();
	/********************�������ݼ���***********************************/
	V_lPowerData = V_ulPowerData & 0x00FFFFFF;
	if (V_lPowerData & 0x00800000)
	{
		V_lPowerData |= 0xFF000000;		/*����оƬ��������ԭʼֵ��3���ֽڵģ����λ�Ƿ���λ��������lon32�ĸ�����ʽ������ת����lon32�ĸ�����ʽ*/
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
����ԭ��: void SF_DemandPowerDataTidy_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE)
��������: ͨ���˺�����������ԭʼֵ����ó���������Ҫ�����ʵֵ����ת�浽�����ù������ݽṹ���С����ﲻ��Ҫ����ʹ洢�������
�������: Str_VARREGTYPE_Type *pStr_VARREGTYPE��ԭʼֵָ��
          Str_VARREGTYPE�й����޹�����,����ԭʼֵ,HEX,���ֽ��з�������,���ֽ���λ����λ,�����λһ�ֽ����ݲ���
�������: GStr_PowerData.Deriction���ʷ���:0~2:�й�A/B/C 3:�й��� 4~6:�޹�A/B/C  7:�޹��� (0)�� (1)��
          GStr_PowerData�������� HEX 4�ֽ����� �޷����� XXXX.XXXw
���ز���: ��
����λ��: 
��    ע: �����ù������ݻ��������洢���ض��ṹ�嵱�У�Ȼ����ýӿں��������������ݸ�����ģ��
*******************************************************************************/
void SF_DemandPowerDataTidy_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE)
{
	uchar8 V_ucStateBuffer[5], V_ucPowerDeriction;
	ushort16 V_usState0, V_usStateLen, V_usDataEncode = 0;
	ulong32 V_ulPowerThresholdGain, V_ulPowerT_ThresholdGain;

	uchar8 V_uci, V_ucDerictionFlag_A, V_ucDerictionFlag_R;

	/**************ȡ���ʷ�ֵ����(XXX.XXXw HEX)***********************/
	V_ulPowerT_ThresholdGain = SF_PowerThresholdGain_MeterIC();
	V_ulPowerThresholdGain = V_ulPowerT_ThresholdGain / 3;
	/********����ԭʼֵ��ȡ*********/
	SF_Power_MeterIC(pStr_VARREGTYPE);
	/************�ܹ������ݼ��㡢�������������ʾ***************/
	V_ucPowerDeriction = GStr_PowerData.Deriction;		/*ת��ԭ�й��ʷ�������*/

	if ( ( (GStr_HEX_VARREGTYPE.VRmsVRegHEX_ABC[C_offA] == 0) || ( GStr_HEX_VARREGTYPE.VRmsIRegHEX_ABC[C_offA] == 0) )
      && ( (GStr_HEX_VARREGTYPE.VRmsVRegHEX_ABC[C_offB] == 0) || ( GStr_HEX_VARREGTYPE.VRmsIRegHEX_ABC[C_offB] == 0) )
      && ( (GStr_HEX_VARREGTYPE.VRmsVRegHEX_ABC[C_offC] == 0) || ( GStr_HEX_VARREGTYPE.VRmsIRegHEX_ABC[C_offC] == 0) ) )
	{
		GStr_PowerData.ActivePower_TABC[C_offTT] = 0;	/*�������������ʧѹ����ʧ��ʱ�����й����ʺ����޹���������*/
		GStr_PowerData.ReativePower_TABC[C_offTT] = 0;
	}
	else
	{
		GStr_PowerData.ActivePower_TABC[C_offTT] = SF_CountRealPower_MeterIC(pStr_VARREGTYPE->WATTReg[0], C_PowerFlag_T);	/*���й����ʼ���*/
		GStr_PowerData.ReativePower_TABC[C_offTT] = SF_CountRealPower_MeterIC(pStr_VARREGTYPE->VARReg[0], C_PowerFlag_T);	/*���޹����ʼ���*/
		/*********�������ݷ�ֵ�жϣ�ֻ�Դ��ڹ��ʷ�ֵ�Ĺ��ʷ�����и��£��������ݲ��������㴦��******/
		/******���й��������ݷ����ȡ******/
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

		/******���޹��������ݷ����ȡ******/
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

	V_usStateLen = CLMeter_Work_State1;					/*�õ������״̬��1��־λ*/
	InF_Read_Data(CMeter_Work_State1, V_ucStateBuffer, &V_usStateLen, &V_usDataEncode);
	PF_Buffer2ToUshort16(V_ucStateBuffer, &V_usState0);
	if ( (V_ucPowerDeriction & 0x88) == C_PQsign2)
	{
		SF_Display_MeterIC(C_Q2Sign, C_AlwaysDisplay);	/*��ʾ�ڶ�����*/
		V_usState0 |= C_PTminus;
		V_usState0 &= C_QTplus;
	}
	else if ( (V_ucPowerDeriction & 0x88) == C_PQsign3)
	{
		SF_Display_MeterIC(C_Q3Sign, C_AlwaysDisplay);	/*��ʾ��������*/
		V_usState0 |= C_PTminus;
		V_usState0 |= C_QTminus;

	}
	else if ( (V_ucPowerDeriction & 0x88) == C_PQsign4)
	{
		SF_Display_MeterIC(C_Q4Sign, C_AlwaysDisplay);	/*��ʾ��������*/
		V_usState0 &= C_PTplus;
		V_usState0 |= C_QTminus;
	}
	else
	{
		SF_Display_MeterIC(C_Q1Sign, C_AlwaysDisplay);	/*��ʾ��һ����*/
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
			/*********�������ݷ�ֵ�жϣ�ֻ�Դ��ڹ��ʷ�ֵ�Ĺ��ʷ�����и��£��������ݲ��������㴦��******/
			/*******�й�����A�෽���ȡ********/
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

			/*******�޹�����A�෽���ȡ********/
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
	if (SF_PhaseSequenceGain_MeterIC() == C_3P3W)			/*��������ֱ�Ӹ�ֵB���С��޹����ʷ���Ϊ��*/
	{
		V_ucPowerDeriction &= 0xDD;
	}
	GStr_PowerData.Deriction = V_ucPowerDeriction;			/*�������úõı�ʱ�̹��ʷ���ת���������ù������ݽṹ��*/
	SF_Cal1minPowerSum(&GStr_PowerAdd, &GStr_PowerData);
	InF_PowerChanggeInitDemand(&GStr_PowerData);
}

/*******************************************************************************
����ԭ��: void SF_PowerDataTidy_MeterIC(void)
��������: ��������Ҫ������˲ʱ��ԭʼ���ݾ�������ת���ɷ������ݲ����Ҫ������ݸ�ʽ��Ȼ��д�����ݲ�
�������: GStr_HEX_VARREGTYPE�ṹ���е�����HEX������
          Str_DataProcess�����е����ݲ��ַ
�������: ��
���ز���: ��
����λ��: 
��    ע: ���м��������������㣬����ϴ����ݲ�
*******************************************************************************/
void SF_PowerDataTidy_MeterIC(void)
{
	uchar8 V_uci, V_ucData[C_FourByteLen];
	Str_VARREGTYPE_Type Str_VARREGTYPE;													/*˲ʱ��ԭʼֵ�洢�ṹ��*/
	Str_RealAngleData_Type Str_RealAngleData;											/*�����ʵ���ݴ洢�ṹ��*/

	SF_Variable_MeterIC(&Str_VARREGTYPE);												/*��ȡ������������Ƶ�ʡ���ǡ��¶ȡ���ѹ�н�����ԭʼֵ*/
	SF_Urms_MeterIC(&Str_VARREGTYPE);													/*��ȡ��ѹ����ԭʼֵ*/
	SF_Irms_MeterIC(&Str_VARREGTYPE);													/*��ȡ��������ԭʼֵ*/
	SF_CurrentDatatoHEX_MeterIC(&Str_VARREGTYPE);										/*�����������֮��ת����HEX*/
	if (GV_C_SlipCurrent__Flag == 0)													/*��������*/
	{
		SF_SlipCurrent();
	}
	SF_VoltageDatatoHEX_MeterIC(&Str_VARREGTYPE);										/*�����ѹ����֮��ת����HEX*/
	SF_DemandPowerDataTidy_MeterIC(&Str_VARREGTYPE);									/*���㹦������֮��HEX���͸�����ģ��*/
	SF_CurrentSignDisplay();															/*����������ʾ*/
	SF_PowerDatatoHEX_MeterIC(&Str_VARREGTYPE);											/*�������ݼ���֮��ת����HEX*/
	SF_PowerFactorDatatoHEX_MeterIC(&Str_VARREGTYPE);									/*�����������ݼ���֮��ת����HEX*/
	SF_FrequencyDatatoHEX_MeterIC(&Str_VARREGTYPE);										/*����Ƶ�����ݼ���֮��ת����HEX*/
	SF_VoltagePhaseAngleDatatoHEX_MeterIC(&Str_VARREGTYPE, &Str_RealAngleData);			/*��ѹ������ݼ���֮��ת����HEX*/
	SF_PhaseAngleDatatoHEX_MeterIC(&Str_VARREGTYPE, &Str_RealAngleData);				/*�������������ݼ���֮��ת����HEX*/
	SF_CurrentPhaseAngleDatatoHEX_MeterIC(&Str_RealAngleData);							/*����������ݼ���֮��ת����HEX*/
/*	SF_TemperatureDatatoHEX_MeterIC();*/												/*�¶����ݼ���֮��ת����HEX*/
	SF_WorkingState();																	/*�������״̬��2����*/
	/*****************�������ݲ�*******************/
	for (V_uci = 0; V_uci < C_InstantNum; V_uci++)
	{
		if ( (V_uci == C_offCPhaseA_Curr) || (V_uci == C_offCPhaseB_Curr) || (V_uci == C_offCPhaseC_Curr) ) /*3λС��������д�����ݲ㣬���ݲ�ֻ��4λС��*/
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
	GV_ucEnergyLock = C_EnergyUnlock;	/*�������ܶ�ȡ*/
}

/*******************************************************************************
����ԭ��: void SF_PowerDatatoHEX_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE)
��������: ���������ݸ������ݲ����ݸ�ʽת����HEX
�������: Str_VARREGTYPE_Type *pStr_VARREGTYPE:ԭʼֵָ��
         GStr_PowerData�ṹ��(�˽ṹ�����������ù������ݴ���)�еĹ�������
         Str_VARREGTYPE�ṹ���е����ڹ���ԭʼֵ
�������: GStr_HEX_VARREGTYPE�ṹ���е��й����޹������ڹ���HEX������XXX.XXXXkw ���ֽ����� ���ಹ�� ��λ����λ (0)�� (1)�� ע:���ڹ�����λ����λ���й�������ͬ
���ز���: ��
����λ��: 
��    ע: ���޹����ʴ������ù������ݽṹ����ȡ���ݣ�Ȼ��ȥ����λС�����������ݲ㣻���ڹ�������Ҫ��ԭʼ���ݼ���
*******************************************************************************/
void SF_PowerDatatoHEX_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE)
{
	long32 V_lData = 0;
	uchar8 V_uci;
	uchar8 V_ucPowerDataFlag;
	
	/****************�й����޹���������:�������ù�������XXXXX.XXXwת����XXXXXXX.Xw*********************/
	for (V_uci = 0; V_uci < 4; V_uci++)
	{
		GStr_HEX_VARREGTYPE.ActivePowerHEX_TABC[V_uci] = GStr_PowerData.ActivePower_TABC[V_uci] / 100;
		GStr_HEX_VARREGTYPE.ReativePowerHEX_TABC[V_uci] = GStr_PowerData.ReativePower_TABC[V_uci] / 100;
	}

	/**************************���ڹ������ݼ���:HEX ���ֽ� XXXX.XXXX kVA****************************/

	for (V_uci = 0; V_uci < 4; V_uci++)
	{
		if ( (V_uci == C_offTB) && ( SF_PhaseSequenceGain_MeterIC( ) == C_3P3W ) )	/*��������B�����ڹ���Ϊ��*/
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

		/*���Ÿ����й����ʷ���*/
		if ( (GStr_HEX_VARREGTYPE.ActivePowerHEX_TABC[V_uci] < 0) && (GStr_HEX_VARREGTYPE.ApparentPowerHEX_TABC[V_uci] > 0)
          || (GStr_HEX_VARREGTYPE.ActivePowerHEX_TABC[V_uci] > 0) && (GStr_HEX_VARREGTYPE.ApparentPowerHEX_TABC[V_uci] < 0) )
		{
			GStr_HEX_VARREGTYPE.ApparentPowerHEX_TABC[V_uci] = 0 - GStr_HEX_VARREGTYPE.ApparentPowerHEX_TABC[V_uci];
		}
	}
}

/*******************************************************************************
����ԭ��: void SF_PowerFactorDatatoHEX_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE)
��������: �������������ݣ��������ݲ����ݸ�ʽת��
�������: Str_VARREGTYPE��������ԭʼ����
�������: GStr_HEX_VARREGTYPE�ṹ���еĹ����������� HEX 2�ֽ� X.XXX �з�����
���ز���: ��
����λ��: 
��    ע: ���������������������ѹ���ߵ������࣬�����Ĺ�������Ĭ��Ϊ1
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
		
		if ( (V_uci == C_offTB) && (SF_PhaseSequenceGain_MeterIC() == C_3P3W) )	/*��������B�๦������Ϊ0*/
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
			if (V_ullPowerFactorUsData >= C_PowerFactorThreshold)		/*���ڵ���0.999�Ĺ�������ͳһΪ1.000*/
			{
				V_ullPowerFactorUsData = C_PowerFactor;
			}
			if (GStr_HEX_VARREGTYPE.ApparentPowerHEX_TABC[V_uci] == 0)	/*���ڹ���Ϊ�㣬���Ӧ�๦������Ĭ��Ϊ1*/
			{
				V_ullPowerFactorUsData = C_PowerFactor;
			}
			SF_ClearUcharArray(V_ucData, 8);
			SF_ClearUcharArray(V_ucHEXData, 2);
			V_ulPowerFactorData = 0;
			PF_Ulong64ToBuffer8(V_ucData, &V_ullPowerFactorUsData, V_ucHexLen);
			PF_BufferXToUlong32(V_ucData, &V_ulPowerFactorData, V_ucHexLen);
			GStr_HEX_VARREGTYPE.PowerFactorHEX_TABC[V_uci] = V_ulPowerFactorData;

			/*���������������й�����ͬ��*/
			if (GStr_PowerData.Deriction & V_ucDeriction[V_uci])
			{
				GStr_HEX_VARREGTYPE.PowerFactorHEX_TABC[V_uci] = 0 - GStr_HEX_VARREGTYPE.PowerFactorHEX_TABC[V_uci];
			}
		}
	}
}

/*******************************************************************************
����ԭ��: void SF_VoltageDatatoHEX_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE)
��������: ����ѹ���ݸ������ݲ����ݸ�ʽת����HEX�룬�����ݵ�ѹ��ֵ��������
�������: Str_VARREGTYPE_Type *pStr_VARREGTYPE:ԭʼֵ�ṹ��ָ��
�������: GStr_HEX_VARREGTYPE�ṹ���еĵ�ѹ���� HEX 2�ֽ� XXX.X �޷���
���ز���: ��
����λ��: 
��    ע:  
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
		if ( (V_uci == C_offB) && (SF_PhaseSequenceGain_MeterIC() == C_3P3W) )	/*��������B���ѹΪ��*/
		{
			V_ulVoltageData = 0;
			V_ucDisplayFlag = C_NotDisplay;
		}
		V_ulVoltageDataTemp = C_VoltageThreshold;
		if (C_OK == InF_ValtageType() )											/*220V\380V*/
		{
			V_ulVoltageDataTemp = C_VoltageThreshold220;
		}
		if (V_ulVoltageData < V_ulVoltageDataTemp)								/*��ѹ��������*/
		{
			V_ulVoltageData = 0;
			V_ucDisplayFlag = C_NotDisplay;
		}
		/*******��ѹ������ʾ*******/
		SF_Display_MeterIC(V_ucSign[V_uci], V_ucDisplayFlag);

		GStr_HEX_VARREGTYPE.VRmsVRegHEX_ABC[V_uci] = V_ulVoltageData;
	}
}

/*******************************************************************************
����ԭ��: void SF_CurrentDatatoHEX_MeterIC_Part(ulong32 *pV_ulVARREGTYPE_VRmsIReg, long32 *pV_lHEX_VARREGTYPE_VRmsILSBRegHEX, long32 *pV_lHEX_VARREGTYPE_VRmsIRegHEX, ulong32 V_ulN, uchar8 V_ucFlag)
��������: ���������ݸ������ݲ����ݸ�ʽת����HEX�룬�����ݵ�����ֵ��������
�������: ulong32 *pV_ulVARREGTYPE_VRmsIReg������ԭʼֵ
         long32 *pV_lHEX_VARREGTYPE_VRmsILSBRegHEX��4λС������ָ��
         long32 *pV_lHEX_VARREGTYPE_VRmsIRegHEX��3λС������ָ��
         ulong32 V_ulN������ϵ��
         uchar8 V_ucFlag����������־
�������: GStr_HEX_VARREGTYPE�ṹ���е������� HEX XXXXX.XXXA 4�ֽ� �� HEX XXXX.XXXXA 4�ֽ� 
���ز���: ��
����λ��: 
��    ע:  
*******************************************************************************/
void SF_CurrentDatatoHEX_MeterIC_Part(ulong32 *pV_ulVARREGTYPE_VRmsIReg, long32 *pV_lHEX_VARREGTYPE_VRmsILSBRegHEX, long32 *pV_lHEX_VARREGTYPE_VRmsIRegHEX, ulong32 V_ulN, uchar8 V_ucFlag)
{
	uchar8 V_ucData[8];
	ulong32 V_ulCurrentData, V_ulCurrentThresholdData;					/*zlj��ʱ������û�з��ţ��ں���Ž��з��Ŵ���*/
	ulong64 V_ullCurrentData;
	/**********************************/
	V_ulCurrentThresholdData = SF_CurrentThresholdGain_MeterIC();		/*��ȡ������ֵ*/

	SF_ClearUcharArray(V_ucData, 8);
	PF_Ulong32ToBufferX(V_ucData, pV_ulVARREGTYPE_VRmsIReg, 4);
	PF_Buffer8ToUlong64(V_ucData, &V_ullCurrentData, 8);
	V_ullCurrentData &= 0x0000000000FFFFFF;
	V_ullCurrentData *= 125;
	V_ullCurrentData >>= 2;
	V_ullCurrentData *= 25;
	V_ullCurrentData /= V_ulN;
	V_ullCurrentData >>= 5;
	if (V_ucFlag != 0)													/*�����������һλ*/
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

	if (V_ucFlag != 0)													/*A/B/C�����Ҫ����4λС���ĵ���*/
	{
		*pV_lHEX_VARREGTYPE_VRmsILSBRegHEX = (long32)V_ulCurrentData;
	}
/********************����3λС������*************************/
	V_ulCurrentData = V_ulCurrentData / 10;
	*pV_lHEX_VARREGTYPE_VRmsIRegHEX = (long32)V_ulCurrentData;
}

/*******************************************************************************
����ԭ��: void SF_CurrentDatatoHEX_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE)
��������: �����������
�������: Str_VARREGTYPE_Type *pStr_VARREGTYPE��˲ʱ��ԭʼֵָ��
�������: ��
���ز���: ��
����λ��: 
��    ע:  
*******************************************************************************/
void SF_CurrentDatatoHEX_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE)
{
	uchar8 V_uci, V_ucIb;   /*,V_Data[4],V_usData[8]*/
	ushort16 V_usLen, V_usDataEncode = 0;
	long32 V_lCurrentData;	/*,V_CurrentThresholdData*/
	ulong32 V_ulN;
	/*******************���ݵ��������ȡ����ϵ��********************/
	V_usLen = CLCurrent_Type;
	InF_Read_Data(CCurrent_Type, &V_ucIb, &V_usLen, &V_usDataEncode);
	switch (V_ucIb & 0x0F)
	{
		case C_Ib0_3A:
		{
			V_ulN = C_N0_3A;
		}break;		/*������������ѹΪ50mAʱ����Ӧ����ЧֵΪ60��V_ulN=60/Ib*/

		case C_Ib1A:
		{
			V_ulN = C_N1A;
		}break;		/*������������ѹΪ25mA����ʱ����ô��Ӧ����Чֵ����60/2=30,V_ulN=30/Ib*/

		case C_Ib1_5A:
		{
			V_ulN = C_N1_5A;
		}break;		/*�������е�V_N������10����������Ϊʲô��10���Լ���һ�¾�֪��Ϊʲô��10�� */

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

	/******************�����������*********************/
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

/*�������ʸ����*/
	SF_CurrentDatatoHEX_MeterIC_Part(&pStr_VARREGTYPE->IRmsN0, &V_lCurrentData, &GStr_HEX_VARREGTYPE.IRmsN0_HEX, V_ulN, 0);
/*���ߵ���*/
	SF_CurrentDatatoHEX_MeterIC_Part(&pStr_VARREGTYPE->IRmsNOSample, &V_lCurrentData, &GStr_HEX_VARREGTYPE.IRmsNOSample_HEX, V_ulN, 1);
	if (SF_PhaseSequenceGain_MeterIC() == C_3P3W)	/*�������������ߵ�������������ʸ����*/
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
����ԭ��: void SF_SlipCurrent(ulong32 *pV_ulSlipCurrentBuff, long32 *pV_lHEX_VARREGTYPE_VRmsILSBRegHEX, long32 *pV_lHEX_VARREGTYPE_VRmsIRegHEX, ulong32 V_ulCurrentThreshold)
��������: �����Ѿ�����õĵ������ݣ����е���������˲���
�������: ulong32 *pV_ulSlipCurrentBuff:����棻
         long32 *pV_lHEX_VARREGTYPE_VRmsILSBRegHEX��4�ֽڵ���ֵ
         long32 *pV_lHEX_VARREGTYPE_VRmsIRegHEX��3�ֽڵ���ֵ
         ulong32 V_ulCurrentThreshold��������ֵ
�������: ��
���ز���: ��
����λ��: 
��    ע: �˻�����������ڵ�������װ��HEX֮�󣬷�����ʾ֮ǰ 
*******************************************************************************/
void SF_SlipCurrent_OnePhase(ulong32 *pV_ulSlipCurrentBuff, long32 *pV_lHEX_VARREGTYPE_VRmsILSBRegHEX, long32 *pV_lHEX_VARREGTYPE_VRmsIRegHEX, ulong32 V_ulCurrentThreshold)
{
	pV_ulSlipCurrentBuff[2] = pV_ulSlipCurrentBuff[1];
	pV_ulSlipCurrentBuff[1] = pV_ulSlipCurrentBuff[0];
	pV_ulSlipCurrentBuff[0] = *pV_lHEX_VARREGTYPE_VRmsILSBRegHEX;
	if ( (ulong32)*pV_lHEX_VARREGTYPE_VRmsILSBRegHEX < V_ulCurrentThreshold)     /*��ʱ������û�и�ֵ����*/
	{
		if ( (pV_ulSlipCurrentBuff[2] == 0) || (pV_ulSlipCurrentBuff[1] == 0) || (pV_ulSlipCurrentBuff[0] == 0) )
		{
			*pV_lHEX_VARREGTYPE_VRmsILSBRegHEX = 0;
			*pV_lHEX_VARREGTYPE_VRmsIRegHEX = 0;
		}
	}
}

/*******************************************************************************
����ԭ��: void SF_SlipCurrent(void)
��������: ��������
�������: ��
�������: ��
���ز���: ��
����λ��: 
��    ע:  
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
		/******ABC���������*****/
		SF_SlipCurrent_OnePhase(&GV_ulSlipCurrentBuff[V_uci][0], &GStr_HEX_VARREGTYPE.VRmsILSBRegHEX_ABC[V_uci], &GStr_HEX_VARREGTYPE.VRmsIRegHEX_ABC[V_uci], V_ulCurrentThresholdData);
	}
}

/*******************************************************************************
����ԭ��: void SF_CurrentSignDisplay(void)
��������: �����Ѿ�����õĵ������ݣ����е���������ʾ
�������: GStr_HEX_VARREGTYPE�ṹ���еĵ�������
         GStr_PowerData.Deriction�ṹ���еĹ��ʷ�������
�������: GStr_HEX_VARREGTYPE�ṹ���еĵ�������
���ز���: ��
����λ��: 
��    ע:  
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
/************************����������ʾ************************/
		V_ucDisFlag = V_ucDisplayFlag;

		if ( (GStr_PowerData.Deriction & V_ucReverse[V_uci]) != 0)/*��Э���й�����Ϊ0�������*/
		{
			if (GStr_HEX_VARREGTYPE.VRmsILSBRegHEX_ABC[V_uci] == 0)
			{/*����Ϊ0����ʾ"-"*/
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
����ԭ��: void SF_FrequencyDatatoHEX_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE)
��������: ��Ƶ������ת�������ݲ����ݸ�ʽ
�������: Str_VARREGTYPE.FREQUENCY����Ƶ��ԭʼ����
�������: GStr_HEX_VARREGTYPE�ṹ���еĵ���Ƶ������ HEX 2�ֽ� XX.XXHz �޷���
���ز���: ��
����λ��: 
��    ע: �������ѹ��Ϊ��ʱ������Ƶ��Ϊ�� 
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
		V_ulFrequencyData = 0;	/*�����ѹΪ�㣬Ƶ��Ϊ��*/
	}
	GStr_HEX_VARREGTYPE.FREQUENCY_HEX = V_ulFrequencyData;
}

/*******************************************************************************
����ԭ��: ulong32 SF_AngleDataSUM_MeterIC(ulong32 V_ulData)
��������: ��������ݴӼĴ�������װ������ʵ����0~360.0�㱣��һλС��
�������: ulong32 V_ulData�������ԭʼֵ
�������: ��
���ز���: ���ؼ���õ��������0~360.0��
����λ��: 
��    ע: 
*******************************************************************************/
ulong32 SF_AngleDataSUM_MeterIC(ulong32 V_ulData)
{
	if (V_ulData >= 0x00100000)
	{
		V_ulData = 0 - V_ulData;
		V_ulData &= 0x000FFFFF;
		V_ulData *= 225;				/*Pg=(��/2^20)��180����������һλС��������Ҫ��10*/
		V_ulData >>= 17;
		V_ulData = 3600 - V_ulData;
		return V_ulData;
	}
	else
	{
		V_ulData *= 225;				/*Pg=(��/2^20)��180����������һλС��������Ҫ��10*/
		V_ulData >>= 17;
		return V_ulData;
	}
}

/*******************************************************************************
����ԭ��: void SF_PhaseAngleDatatoHEX_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE, Str_RealAngleData_Type *pStr_RealAngleData)
��������: ������������ݸ������ݲ����ݸ�ʽת����HEX��
�������: Str_VARREGTYPE�еĵ�ѹ��Ǻ͵������
�������: GStr_HEX_VARREGTYPE�ṹ���еĹ������ HEX XXX.X��2�ֽ� �޷��� 0.0~360.0��
���ز���: ��
����λ��: 
��    ע: ��Ǽ���Ϊͨ��7022E���㷨���㣬��������ֲ�
*******************************************************************************/
void SF_PhaseAngleDatatoHEX_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE, Str_RealAngleData_Type *pStr_RealAngleData)
{
	uchar8 V_uci;
	for (V_uci = 0; V_uci < 3; V_uci++)
	{
		pStr_RealAngleData->YUIRealData_ABC[V_uci] = SF_AngleDataSUM_MeterIC(pStr_VARREGTYPE->YUIReg[V_uci]);
		
		/*********ABC���ѹ����������ݼ����ת����HEX**********/

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
����ԭ��: void SF_VoltagePhaseAngleDatatoHEX_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE, Str_RealAngleData_Type *pStr_RealAngleData)
��������: ����ѹ�������ת�������ݲ����ݸ�ʽ��
�������: Str_VARREGTYPE��ѹ�������
�������: GStr_HEX_VARREGTYPE�ṹ���е�ѹ��� HEX XXX.X�� 2�ֽ� 0.0~360.0��
���ز���: ��
����λ��: 
��    ע: ��ѹ���Ϊֱ�ӴӼ���оƬ�Ĵ����ж�ȡ����Ч���ݣ�����оƬ�������㷨��
*******************************************************************************/
void SF_VoltagePhaseAngleDatatoHEX_MeterIC(Str_VARREGTYPE_Type *pStr_VARREGTYPE, Str_RealAngleData_Type *pStr_RealAngleData)
{
	uchar8 V_ucPhaseSequenceGain;

	V_ucPhaseSequenceGain = SF_PhaseSequenceGain_MeterIC();		/*ȡ���߷�ʽ����*/
	GStr_HEX_VARREGTYPE.YURegHEX_ABC[C_offA] = 0;
	pStr_RealAngleData->YURealData_ABC[C_offA] = 0;
	/*���Ĵ�����ȡ����������ݣ�ת����0~360�����ʵ����**///
	pStr_RealAngleData->YURealData_ABC[C_offB] = SF_AngleDataSUM_MeterIC(pStr_VARREGTYPE->YUReg[0]);
	pStr_RealAngleData->YURealData_ABC[C_offC] = SF_AngleDataSUM_MeterIC(pStr_VARREGTYPE->YUReg[1]);
	/******************B���ѹ��Ǽ���********************/
	if (V_ucPhaseSequenceGain == C_3P3W)						/*�������������B���ѹ���Ϊ��*/
	{
		pStr_RealAngleData->YURealData_ABC[C_offB] = 0;
	}
	else
	{
		if ( (GStr_HEX_VARREGTYPE.VRmsVRegHEX_ABC[C_offA] == 0) || (GStr_HEX_VARREGTYPE.VRmsVRegHEX_ABC[C_offB] == 0) )    /*���A���ѹ����0����B���ѹ���Ĭ��Ϊ120��*/
		{
			pStr_RealAngleData->YURealData_ABC[C_offB] = 1200;
		}
	}
	GStr_HEX_VARREGTYPE.YURegHEX_ABC[C_offB] = pStr_RealAngleData->YURealData_ABC[C_offB];

	/********************C���ѹ��Ǽ���**************************/
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
����ԭ��: void SF_ CurrentPhaseAngleDatatoHEX_MeterIC(Str_RealAngleData_Type *pStr_RealAngleData)
��������: �����������ת��ΪHEX
�������: Str_VARREGTYPE�ṹ���еĵ����������
�������: GStr_HEX_VARREGTYPE�ṹ���еĵ���������� HEX XXX.X�� 2�ֽ� �޷��� 0.0��~360.0��
���ز���: ��
����λ��: 
��    ע: �����������Ϊ�Ĵ�����ȡ����Ч���ݣ�����оƬʹ�����㷨��
*******************************************************************************/
void SF_CurrentPhaseAngleDatatoHEX_MeterIC(Str_RealAngleData_Type *pStr_RealAngleData)
{
	ulong32 V_ulIaAngleData, V_ulIbAngleData, V_ulIcAngleData;

	GStr_HEX_VARREGTYPE.YIRegHEX_ABC[C_offA] = 0;
	V_ulIaAngleData = pStr_RealAngleData->YUIRealData_ABC[C_offA];
	V_ulIbAngleData = pStr_RealAngleData->YURealData_ABC[C_offB] + pStr_RealAngleData->YUIRealData_ABC[C_offB];
	V_ulIcAngleData = pStr_RealAngleData->YURealData_ABC[C_offC] + pStr_RealAngleData->YUIRealData_ABC[C_offC];
	/*******************B�����������ݼ���***************************/
	if (SF_PhaseSequenceGain_MeterIC() == C_3P3W)	/*�������������B��������Ϊ��*/
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
			if (V_ulIbAngleData >= V_ulIaAngleData)	/*B�������������Ƿ���ڵ���A�����������ݣ�������м�360�㴦��*/
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

	/********************C�����������ݼ���***********************************/
	if ( (GStr_HEX_VARREGTYPE.VRmsVRegHEX_ABC[C_offA] == 0) || (GStr_HEX_VARREGTYPE.VRmsVRegHEX_ABC[C_offC] == 0) )
	{
		pStr_RealAngleData->YIRealData_ABC[C_offC] = 2400;
	}
	else
	{
		if (V_ulIcAngleData >= V_ulIaAngleData)		/*C�������������Ƿ���ڵ���A�����������ݣ�������м�360�㴦��*/
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
����ԭ��: void SF_ClearCalReg_MeterIC(void)
��������: ���У��Ĵ���
�������: ��
�������: ��
���ز���: ��
����λ��: 
��    ע: �����������Ϊ�Ĵ�����ȡ����Ч���ݣ�����оƬʹ�����㷨��
*******************************************************************************/
void SF_ClearCalReg_MeterIC(void)
{
	uchar8 V_ucAddr, V_ucWriteData[4];
	ushort16 V_usData;

	SF_ClearUcharArray(V_ucWriteData, 4);
	V_ucAddr = 0xC3;
	SF_WriteOneReg_MeterIC(V_ucWriteData, V_ucAddr, C_DataSafe);	/*0xC3��ַд��000000,��ʼ������оƬУ��Ĵ�����ֵ*/
	SF_Delay(C_DELAY25MS);
	SF_Delay(C_DELAY25MS);
	SF_ENSPIMode_MeterIC();
	SF_Eable_MeterIC();
	GV_ulCalDataChk0SUM = C_Check0RetData;
	GV_ulCalDataChk1SUM = C_Check1RetData;
	SF_ClearUcharArray(V_ucWriteData, 4);
	V_usData = C_ModeCfg_Data;										/*ģʽ��ؿ��ƼĴ�������*/
	PF_Ushort16ToBuffer2(V_ucWriteData, &V_usData);
	SF_WriteOneReg_MeterIC(V_ucWriteData, C_ModeCfg_Reg, C_DataSafe);
	SF_TemRectify_MeterIC();
	SF_ClearUcharArray(V_ucWriteData, 4);
	V_usData = C_ModuleCFG_Data;									/*��·ģ������*/
	PF_Ushort16ToBuffer2(V_ucWriteData, &V_usData);
	SF_WriteOneReg_MeterIC(V_ucWriteData, C_ModuleCFG_Reg, C_DataSafe);
	/*SF_ClearUcharArray(V_ucWriteData, 4);*/
}

/*******************************************************************************
����ԭ��: void SF_Display_MeterIC(uchar8 V_ucData, uchar8 V_ucFlag)
��������: ��ʾ����ģ�鸺���'Va' 'Vb' 'Vc' '-' 'Ia' '-' 'Ib' '-' 'Ic'
�������: uchar8 V_ucData��ʾ��ͬ����:C_UaSign ��ʾVa;
                                     C_UbSign ��ʾVb;
                                     C_UcSign ��ʾVc;
                                     C_IaSign ��ʾIa;
                                     C_IbSign ��ʾIb;
                                     C_IcSign ��ʾIc;
                                     C_IaNegativeSign ��ʾ-;
                                     C_IbNegativeSign ��ʾ-;
                                     C_IcNegativeSign ��ʾ-;
          uchar8 V_ucFlag��ʾ���ݵĲ�ͬ״̬:C_TwinkleDisplay ��˸��ʾ
                                           C_AlwaysDisplay ����
                                           C_NotDisplay ����
�������: ��
���ز���: ��
����λ��: 
��    ע: 
*******************************************************************************/
void SF_Display_MeterIC(uchar8 V_ucData, uchar8 V_ucFlag)
{
	uchar8 V_ucDisplay, V_ucDisPlayData[8];
	Str_Msg_Parameter Str_Msg_Display;		/*��ʾ��Ϣ�ṹ��*/

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
����ԭ��: void SF_WorkingState(void)
��������: ���ܱ�����״̬��2����
�������: Str_PowerData.Deriction�����ù��ʷ�������
�������: ��
���ز���: ��
����λ��: 
��    ע: 
*******************************************************************************/
void SF_WorkingState(void)
{
	uchar8 V_ucStateBuffer[5];
	ushort16 V_usStateLen, V_usState1, V_usDataEncode = 0;

	V_usStateLen = CLMeter_Work_State2;
	InF_Read_Data(CMeter_Work_State2, V_ucStateBuffer, &V_usStateLen, &V_usDataEncode);
	PF_Buffer2ToUshort16(V_ucStateBuffer, &V_usState1);
	if (GStr_PowerData.Deriction & C_ActiveEnergyA_Minus)	/*A���й�����ֵ*/
	{
		V_usState1 |= C_PAminus;
	}
	else
	{
		V_usState1 &= C_PAplus;
	}

	if (GStr_PowerData.Deriction & C_ReactiveEnergyA_Minus)	/*A���޹�����ֵ*/
	{
		V_usState1 |= C_QAminus;
	}
	else
	{
		V_usState1 &= C_QAplus;
	}

	if (GStr_PowerData.Deriction & C_ActiveEnergyB_Minus)	/*B���й�����ֵ*/
	{
		V_usState1 |= C_PBminus;
	}
	else
	{
		V_usState1 &= C_PBplus;
	}

	if (GStr_PowerData.Deriction & C_ReactiveEnergyB_Minus)	/*B���޹�����ֵ*/
	{
		V_usState1 |= C_QBminus;
	}
	else
	{
		V_usState1 &= C_QBplus;
	}

	if (GStr_PowerData.Deriction & C_ActiveEnergyC_Minus)	/*C���й�����ֵ*/
	{
		V_usState1 |= C_PCminus;
	}
	else
	{
		V_usState1 &= C_PCplus;
	}

	if (GStr_PowerData.Deriction & C_ReactiveEnergyC_Minus)	/*C���޹�����ֵ*/
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
����ԭ��: void SF_CalTemp(void)
��������: У���¶ȴ�����
�������: Str_PowerData.Deriction�����ù��ʷ�������
�������: ��
���ز���: ��
����λ��: 
��    ע: �ڽ���У���ڽ��е��ã�У���¶�Ϊ��׼25�档
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
����ԭ��: void SF_InitialPowerCoeff(void)
��������: ������ϵ�������ݲ��ȡ�����������RAM�д�CRC
�������: ��
�������: ��
���ز���: ��
����λ��: 
��    ע: 
*******************************************************************************/
void SF_InitialPowerCoeff(void)
{
	uchar8	V_ucPowerFactorBuffer[8], V_ucDataLength;

	SF_ClearUcharArray(V_ucPowerFactorBuffer, 8);
	V_ucDataLength = C_MeaDataLen;
	InF_Read_RecMeterData(C_PowerFactorNO, V_ucPowerFactorBuffer, &V_ucDataLength);	/*�����ݲ�ȡ��������*/
	GStr_PowerCoeff.Crc = PF_Cal_CRC(V_ucPowerFactorBuffer, 8);
	PF_Buffer8ToUlong64(V_ucPowerFactorBuffer, &GStr_PowerCoeff.PowerCoeffData, C_CalDataLen);
}

/*******************************************************************************
����ԭ��: SF_GetPowerCoeff(void)
��������: ��ȡ����ϵ��
�������: ��
�������: ��
���ز���: ��
����λ��: 
��    ע: 
*******************************************************************************/
ulong64 SF_GetPowerCoeff(void)
{
	uchar8 V_ucPowerCoeffBuffer[10];
	ulong64 V_ullPowerCoeffData;

	SF_ClearUcharArray(V_ucPowerCoeffBuffer, 10);
	PF_Ulong64ToBuffer8(&V_ucPowerCoeffBuffer[0], &GStr_PowerCoeff.PowerCoeffData, C_CalDataLen);
	PF_Ushort16ToBuffer2(&V_ucPowerCoeffBuffer[8], &GStr_PowerCoeff.Crc);
	if (PF_Check_CRC(V_ucPowerCoeffBuffer, 10) == C_OK)	/*CRCУ�飬���У����������¶�ȡ���ݲ�(8�ֽ�����+2�ֽ�CRC)*/
	{
		PF_Buffer8ToUlong64(V_ucPowerCoeffBuffer, &V_ullPowerCoeffData, C_CalDataLen);
	}
	else												/*���¶�ȡ���ݲ㹦��ϵ������֮�󣬲�������CRCУ�飬ֱ��ʹ�ù���ϵ������*/
	{
		SF_InitialPowerCoeff();
		V_ullPowerCoeffData = GStr_PowerCoeff.PowerCoeffData;
	}
	return V_ullPowerCoeffData;
}

/*******************************************************************************
����ԭ�ͣ�void InF_ClearHexVarregtype_MeterIC(uchar8 V_ucClearType)
�����������������ݲ���˲ʱ������
���������uchar8 V_ucClearType:�Ƿ����������:C_ClearCurrData�������˲ʱ��
                                            C_NotClearCurrData���������˲ʱ��
�����������
���ز�������
����λ�ã������ڽ���͹���֮ǰ���������ݲ��е�˲ʱ�����ݣ������Ƿ�������衣
��    ע��
*******************************************************************************/
void InF_ClearHexVarregtype_MeterIC(uchar8 V_ucClearType)
{
	uchar8 V_uci, V_ucData[4] = {0x00};
	for (V_uci = 0; V_uci < C_InstantNum; V_uci++)
	{
        if ( (V_uci == C_offCPhaseA_Curr) || (V_uci == C_offCPhaseB_Curr) || (V_uci == C_offCPhaseC_Curr) )	/*3λС��������д�����ݲ㣬���ݲ�ֻ��4λС��*/
        {
            continue;
        }
		SF_ClearUcharArray(V_ucData, 4);
		if (V_ucClearType == C_NotClearCurrData)
		{
			if ( (V_uci < C_offCPhaseA_Curr_4Dig) || (V_uci > C_offCPhaseC_Curr_4Dig) )						/*������C_offCPhaseA_Curr_4Dig--C_offCPhaseC_Curr_4Dig��λ��*/
			{
				InF_Write_Data(C_Msg_MeterIC, Str_DataProcess[V_uci].C_InstantOAD, V_ucData, Str_DataProcess[V_uci].CL_InstantOAD, C_W_SafeFlag);
			}
		}
		else
		{
			InF_Write_Data(C_Msg_MeterIC, Str_DataProcess[V_uci].C_InstantOAD, V_ucData, Str_DataProcess[V_uci].CL_InstantOAD, C_W_SafeFlag);
		}
	}

	/*zlj������1minƽ������*/
	SF_ClrCurrentPower();
}

/*******************************************************************************
����ԭ��: void  InF_Initial_MeterIC (void)
��������: ������ʼ������оƬ��Ϣ���������м���ʱ��ʱ���ֵ
�������: ��
�������: GV_ucUpdateTime���ݲ����˲ʱ����ʱ����ʼ��
          GV_ucCheckTimeУ���У�鶨ʱ����ʼ��
          GV_ucEnergyLock�������ܶ�ȡ����
���ز���: ��
����λ��: 
��    ע: 
*******************************************************************************/
void  InF_Initial_MeterIC (void)
{
	uchar8 V_ucData;

	Str_Msg_Parameter Str_Msg_InitalTrigger;	/*������ʼ����Ϣ�ṹ��*/

	GStr_PowerData.Deriction = 0;				/*���ʷ���ȫ����ʼΪ����*/
	V_ucData = Pt_InitialMeterIC;
	GV_ucUpdateTime = C_UpdateTime;				/*���ݲ����˲ʱ����ʱ����ʼ��*/
	GV_ucCheckTime = C_CheckTime;				/*У���У�鶨ʱ����ʼ��*/
	GV_ucEnergyLock = C_EnergyLock;				/*�������ܶ�ȡ����*/
	/*���г������*/
	GV_ucPowerFactor_Flag = 0;					/*���г�����������������Ƿ����������־��ʼ��*/
	GV_ucCurrent_Flag1 = 0;						/*���г�������������Ƿ����������־(2.8-4A)��ʼ��*/
	GV_ucCurrent_Flag2 = 0;						/*���г�������������Ƿ����������־(1.4-2A)��ʼ��*/

	/*ż��г������*/
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
����ԭ��: uchar8 InF_ReadReg_MeterIC(ushort16 V_usData_Id, uchar8 *pV_ucData, uchar8 *pV_ucLength)
��������: ͨ���˽ӿں������Զ�ȡ��Ӧ��ʶ���У�������ʵʱ����
�������: ushort16  V_usData_IdԤ��ȡ��ʶ��
�������: uchar8 *pV_ucData��ȡ���ݻ���ָ��
          uchar8 *pV_ucLength��ȡ���ݵĳ���ָ��
���ز���: ��ȡ�ɹ���C_OK����ȡͨѶʧ�ܣ�C_SPIError�����ݳ��ȴ���:C_DataLenError;���ݱ�ʶ�����:C_IDError
����λ��: 
��    ע: ��������ͨ��������������ݱ�ʶ�룬��ȡ��Ӧ����оƬ�ļĴ�����ַ��Ȼ�����ݴӼ���оƬ��ȡ����
*******************************************************************************/
uchar8 InF_ReadReg_MeterIC(ushort16 V_usData_Id, uchar8 *pV_ucData, uchar8 *pV_ucLength)
{
	uchar8 V_uci, V_ucMeterData[3], V_ucDataDI[2], V_ucNUM;

	PF_Ushort16ToBuffer2(V_ucDataDI, &V_usData_Id);
	if ( V_ucDataDI[1] == C_CalDataMeterIC_DI1)							/*�ж��Ƿ��Ƕ�ȡ����оƬУ�����*/
	{
		if (Str_Table2_CalData[V_ucDataDI[0]].MeterIC_WR | 0x01)		/*�Ա�2�еļ���оƬдȨ�޽����ж�*/
		{
			SF_ClearUcharArray(V_ucMeterData, 3);
			if (SF_ReadOneReg_MeterIC (V_ucDataDI[0], V_ucMeterData, C_ReadCalDataRegFlag) == C_OK)	/*��ȡ��ʶ��Я���ļĴ�����ַ������*/
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
	else if (V_ucDataDI[1] == C_MeaDataMeterIC_DI1)	/*�ж��Ƿ�Ϊ��ȡ��������*/
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
	else if (V_ucDataDI[1] == C_TWCalDataMeterIC_DI1)	/*�ж��Ƿ��ǿ��ȡУ�����*/
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
����ԭ��: uchar8  InF_WriteCalReg_MeterIC(ushort16 V_usData_Id, uchar8 *pV_ucData, uchar8 V_ucDataLen, uchar8 *pV_ucPhaseNO, uchar8 *pV_ucNOAmount)
��������: ͨ���˽ӿں������Խ�У�����д�����оƬ
�������: ushort16 V_usData_Id        ���ݱ�ʶ��
         uchar8 *pV_ucData    Ԥд�����ݴ洢ָ��
         uchar8 V_ucDataLen  ���ݳ���(�ֽ�)
�������: uchar8 *pV_ucPhaseNO   ������ʵ�����ʶ������ָ��
         uchar8 *pV_ucNOAmount   ������ʵ��ʶ����������(����)
���ز���: д��ɹ���C_OK��
         д�����ݱ�ʶ����C_IDError
         д��ͨѶʧ�ܣ�C_SPIError��
         ����У��ɹ���C_StartCalibrationOK
         ����У��ɹ���C_CalibrationOK
         ��У������ɹ�:C_ClearCalRegOK
         У��״̬����C_NOStartCalibration
����λ��: 
��    ע: ��������ͨ��������������ݱ�ʶ�룬��ȡ��Ӧ����оƬ�ļĴ�����ַ��Ȼ������д�����оƬ
         0x87:+68����У��+69����У��+6A����
         0x86+�Ĵ�����ַ:��дУ�����
         0x83+�Ĵ�����ַ:������оƬ��������
         0x82+��չ��ַ:��дУ�����
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
����ԭ��: uchar8  InF_Read_MeterIC_EnergyData(Struct_Energy_Type *pStr_EnergyData)
��������: ͨ���˽ӿں�������ȡ��������
�������: ���ܴ洢�ýṹ��ָ��
�������: Str_EnergyData�������ݽṹ��������� ��λimp
���ز���: �ɹ���C_OK;ʧ�ܣ�C_SPIError
����λ��: 
��    ע: �������ڱ����õ�ʱ�򣬻��ȡ����оƬ�������ݣ���������д��������������Ľṹ��ָ�뵱�У���ȡ����
         ���жϵ��ܱ�����־�Ƿ�Ϊ����״̬�����Ϊ����״̬�����ص�������ȫ��Ϊ�㡣
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
����ԭ��: void  InF_PowerDownInitial_MeterIC (void)
��������: �͹���״̬��ʼ������оƬ
�������: ��
�������: ��
���ز���: ��
����λ��: 
��    ע: 
*******************************************************************************/
void  InF_PowerDownInitial_MeterIC(void)
{
	uchar8 V_uci, V_ucCalRegData[4], V_ucDataLen;
	ushort16 V_usData;

	SF_PowerDownHardwareRESET_MeterIC();
	SF_ENSPIMode_MeterIC();
	SF_Eable_MeterIC();
	V_usData = C_PorDownModeCfg_Data;	/*�͹�����ģʽ��ؿ�������*/
	SF_ClearUcharArray(V_ucCalRegData, 4);
	PF_Ushort16ToBuffer2(V_ucCalRegData, &V_usData);
	SF_WriteOneReg_MeterIC(V_ucCalRegData, C_ModeCfg_Reg, C_DataSafe);
	SF_ClearUcharArray(V_ucCalRegData, 4);
	V_usData = C_ModuleCFG_Data;		/*��·ģ������*/
	PF_Ushort16ToBuffer2(V_ucCalRegData, &V_usData);
	SF_WriteOneReg_MeterIC(V_ucCalRegData, C_ModuleCFG_Reg, C_DataSafe);
	V_ucDataLen = C_CalDataLen;			/*ADC����ѡ��*/
	SF_ClearUcharArray(V_ucCalRegData, 4);
	InF_Read_RecMeterData(0x02, V_ucCalRegData, &V_ucDataLen);
	SF_WriteOneReg_MeterIC(V_ucCalRegData, 0x02, C_DataSafe);
	/****************��ѹ�͵���У����������****************/
	for (V_uci = 0x17; V_uci < 0x1D; V_uci++)
	{
		SF_ClearUcharArray(V_ucCalRegData, 4);
		InF_Read_RecMeterData(V_uci, V_ucCalRegData, &V_ucDataLen);
		SF_WriteOneReg_MeterIC(V_ucCalRegData, V_uci, C_DataSafe);
	}
}

/*******************************************************************************
����ԭ��: uchar8 InF_PowerDownReadData_MeterIC(void)
��������: �͹���״̬��ȡ��������
�������: ��
�������: GStr_HEX_VARREGTYPE�ṹ���еĵ�ѹ���ݺ͵�������
���ز���: ��ȡ�ɹ���C_OK����ȡͨѶʧ�ܣ�C_SPIError��
����λ��: 
��    ע: 
*******************************************************************************/
uchar8 InF_PowerDownReadData_MeterIC(void)
{
	uchar8 V_uci, V_ucDIData[5], V_ucData[5];
    Str_VARREGTYPE_Type Str_VARREGTYPE_temp;
    
	/****************��ȡ��ѹ��������****************/
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
	/****************����ѹ�͵������ݼ����HEX***************************/
	SF_VoltageDatatoHEX_MeterIC(&Str_VARREGTYPE_temp);
	SF_CurrentDatatoHEX_MeterIC(&Str_VARREGTYPE_temp);
	/****************�������ݲ��ѹ�͵�������****************************/
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
����ԭ��: void  InF_Initial(void)
��������: ��ʼ������оƬ�����¼���ʱ��
�������: ��
�������: ��
���ز���: ��
����λ��: 
��    ע: 
*******************************************************************************/
void  InF_Initial(void)
{
	GV_ucMeterICErrorNum = 0;
	GV_ucMeterICErrorTime = 0;
	GV_ucMeterICErrorState = C_MeterICNormal;
}

/*******************************************************************************
����������	ż��г������
*******************************************************************************/
#define C_HD2Rate_Low       0x0000005A	/*ż��г��������С��ֵ30%��0.3*0.3*1000��*/
#define C_HD2Rate_High      0x000000FA	/*ż��г�����������ֵ50%��0.5*0.5*1000��*/

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

#if 0	/*���㲹��*/

#define CurrentLimit5A_Low		0x018000	/*5(60)Aż��г�����������С��ֵ18A*/
#define CurrentLimit5A_High		0x028000	/*5(60)Aż��г��������������ֵ28A*/

#define CurrentLimit10A_Low		0x030000	/*10(100)Aż��г�����������С��ֵ30A*/
#define CurrentLimit10A_High	0x040000	/*10(100)Aż��г��������������ֵ40A*/

#define C_EvenHarmonicDelayTimer	6		/*����5ms��ʱ��һ���ܲ��ӳ�30ms*/
#endif

#if 1	/*���Բ���*/

#define CurrentLimit5A_Low		0x001500	/*5(60)Aż��г�����������С��ֵ1.5A*/
#define CurrentLimit5A_High		0xFFFFFF	/*5(60)Aż��г��������������ֵ��*/

#define CurrentLimit10A_Low		0x003000	/*10(100)Aż��г�����������С��ֵ3A*/
#define CurrentLimit10A_High	0xFFFFFF	/*10(100)Aż��г��������������ֵ��*/

#define C_EvenHarmonicDelayTimer	10		/*����5ms��ʱ�������ܲ��ӳ�50ms*/
#endif
/**********************************************************************************
����ԭ�ͣ�void InF_InitialEvenHarmonicCompensationTime (void)
����������ż��г������ʱ���ʼ��
�����������
�����������
���ز�������
����λ�ã�
��    ע��
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
		GV_usEvenHarmonicCompensationTime = C_EvenHarmonicCompensationTime;	/*Ĭ��24h*/
	}
}

/**********************************************************************************
����ԭ�ͣ�uchar8 SF_GetEvenHarmonicCompensationFlag (void)
������������ȡż��г��������־
�����������
�����������
���ز�����C_Even_Harmonic_En:����ʹ�ܣ�C_Even_Harmonic_Dis������ʧ��
����λ�ã�
��    ע��
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
			GV_ucEvenHarmonicSecondTimer = 60;	/*60s��ʱ*/
			GV_usEvenHarmonicCompensationTime--;
		}
		return C_Even_Harmonic_En;
	}
	return C_Even_Harmonic_Dis;
}

/**********************************************************************************
����ԭ�ͣ�uchar8 SF_GetEvenHarmonicCurrent (Str_CurrentLimit_Type *pStr_CurrentLimit)
������������ȡż��г������ʱ������Χ
�����������
�����������
���ز�����C_OK:A��B��C������������һ���ڷ�Χ�ڣ�C_Error��A��B��C���඼���ڷ�Χ��
����˵����
���û��ƣ�
��    ע��
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
		case C_Ib5A:	/*������Χ18.000A~28.000A*/
		{
			pStr_CurrentLimit->V_ulCurrentLimit_Low = CurrentLimit5A_Low;
			pStr_CurrentLimit->V_ulCurrentLimit_High = CurrentLimit5A_High;
		}break;

		case C_Ib10A:	/*������Χ30.000A~40.000A*/
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
����ԭ�ͣ�void SF_GetEvenHarmonicContent (void)
������������ȡ�������ż��г������
�����������
�����������
���ز�������
����˵����
���û��ƣ�GV_EvenHarmonicFlag == C_DoEvenHarmonicFlag ����ż��г������
��    ע��г����ִ��150ms����Ҫ�������ݲɼ�
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

	/*�жϵ�ǰ�����Ƿ���ż��г��Ҫ��Χ��*/
	if (SF_GetEvenHarmonicCurrent ( &Str_CurrentLimit ) != C_OK)
	{
		SF_ClearUlongArray( (ulong32 *)GV_lHD2Rate, CL_HD2Rate);	/*ż��г������������*/
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
			SF_WriteOneReg_MeterIC(V_ucBuffer, C_BuffStr, 0x86);	/*�������ݻ���ֹͣ(0x000000,0xc0,0x86)*/

			SF_Delay(C_DELAY1MS);

			V_ucBuffer[0] = 0xCB;
			V_ucBuffer[1] = 0xCC;
			V_ucBuffer[2] = 0x00;
			V_ucBuffer[3] = 0x00;
			SF_WriteOneReg_MeterIC(V_ucBuffer, C_BuffStr, 0x86);    /*�������ݻ��忪��(0x00CCCB,0xc0,0x86)*/

			GV_ucEvenHarmonicDelayTimer = C_EvenHarmonicDelayTimer;	/*��ʱ30ms,����5ms*/
			while (GV_ucEvenHarmonicDelayTimer != 0)
			{
				SF_Delay(C_DELAY1MS);
			}

			memset(V_ucBuffer, 0x00, 4);
			SF_WriteOneReg_MeterIC(V_ucBuffer, C_BuffStr, 0x86);	/*�������ݻ���ֹͣ(0x000000,0xc0,0x86)*/

			GV_ucStepNum = 1;

		}break;

		case 0x01:
		{
			GV_ucStepNum = 0;										/*���̿���������*/

			memset(&V_ucBuffer[0], 0x00, 4);
			V_ucBuffer[0] = 0x0F;
			SF_WriteOneReg_MeterIC(V_ucBuffer, C_BuffSet, 0x86);	/*ָ������������ʼ��(0x00000F,0xc1,0x86)*/

			SF_WriteEnable_MeterIC();

			SF_ReadDataModeSet(C_ReadMeaDataRegFlag);

			SF_WriteDisable_MeterIC();								/* д����оƬ�Ĵ���ʹ��-�رգ�����������д����оƬ�Ĵ��� */

	/**********************����һ���ܲ���������****************************/
			SF_Eable_MeterIC();
			memset(&V_ucBuffer[0], 0x00, 4);

			for (V_usi = 0; V_usi < C_SampNum; V_usi++)				/*��forѭ����ʱ33ms��30~35ms��*/
			{
				for (V_uschl = 0; V_uschl < 3; V_uschl++)			/*ÿһ��forѭ��֮����12us*/
				{
					SF_ReadBufferReg_MeterIC(0x7f, &V_ucBuffer[0]);
					PF_Buffer2ToUshort16(&V_ucBuffer[0], &V_usSampBuffer);
					V_ssamp[V_uschl][V_usi] = (short16)V_usSampBuffer;
				}
			}
			SF_Disable_MeterIC();
			
			/*����ż��г������*/
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

				V_lsum1c >>= 16;					/*��λ,�Ա�������*/
				V_lsum1s >>= 16;
				V_lsum2c >>= 16;
				V_lsum2s >>= 16;

				V_ulsum1 = V_lsum1c * V_lsum1c + V_lsum1s * V_lsum1s;
				V_ulsum2 = V_lsum2c * V_lsum2c + V_lsum2s * V_lsum2s;
				
				if ( (V_ucIb & 0x0F) == C_Ib10A)
				{
					V_ulCurrentType = 0x00009000;	/*��10��100��A�ı�ʵ�����ڵ�����ЧֵΪ3Aʱ��sum1Ϊ0x0000A100����*/
													/*���ڴ�ֵ�������������ȣ��������輰���������йأ���˴˴�����10��100��A�ı�ʵ�ʵ���*/
				}
				else
				{
					V_ulCurrentType = 0x00005000;	/*ʵ�����ڵ�����ЧֵΪ1.5Aʱ��sum1Ϊ0x00006000����*/
				}
				if (V_ulsum1 >= V_ulCurrentType)	/*�޳�С��������������*/
				{
					V_ulFundamental[V_uschl] = V_ulsum1;
					V_ullsum2 = 1000 * (ulong64)V_ulsum2;
					GV_lHD2Rate[V_uschl] = V_ullsum2 / V_ulsum1;								/*����1000��*/
				}
				else
				{
					GV_lHD2Rate[V_uschl] = 0;
				}
			}

			/*�ж�г���������Ƿ���30%~50%֮��*/
			if ( ( (GV_lHD2Rate[0] < C_HD2Rate_Low) || (GV_lHD2Rate[0] > C_HD2Rate_High) ) &&
                 ( (GV_lHD2Rate[1] < C_HD2Rate_Low) || (GV_lHD2Rate[1] > C_HD2Rate_High) ) &&
                 ( (GV_lHD2Rate[2] < C_HD2Rate_Low) || (GV_lHD2Rate[2] > C_HD2Rate_High) ) )	/*40%��ƽ������1000��*/
			{
				SF_ClearUlongArray( (ulong32 *)GV_lHD2Rate, CL_HD2Rate);						/*ż��г������������*/
				return;								/*�˳�ż��г����������*/
			}

		/***********************��ȡ�ڶ����ܲ���������************************/
			SF_Eable_MeterIC();
			
			memset(&V_ucBuffer[0],0x00,4);

			for (V_usi = 0; V_usi < C_SampNum; V_usi++)			/*��forѭ����ʱ33ms��30~35ms��*/
			{
				for (V_uschl = 0; V_uschl < 3; V_uschl++)		/*ÿһ��forѭ��֮����12us*/
				{
					SF_ReadBufferReg_MeterIC(0x7f, &V_ucBuffer[0]);								/*����������*/
					PF_Buffer2ToUshort16(&V_ucBuffer[0], &V_usSampBuffer);
					V_ssamp[V_uschl][V_usi] = (short16)V_usSampBuffer;
				}
			}
			SF_Disable_MeterIC();

			/*����ż��г������*/
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

				V_lsum1c >>= 16;					/*��λ,�Ա�������*/
				V_lsum1s >>= 16;
				V_lsum2c >>= 16;
				V_lsum2s >>= 16;

				V_ulsum1 = V_lsum1c * V_lsum1c + V_lsum1s * V_lsum1s;
				V_ulsum2 = V_lsum2c * V_lsum2c + V_lsum2s * V_lsum2s;

				if ( (V_ucIb & 0x0F) == C_Ib10A)
				{
					V_ulCurrentType = 0x00009000;	/*��10��100��A�ı�ʵ�����ڵ�����ЧֵΪ3Aʱ��sum1Ϊ0x0000A100����*/
													/*���ڴ�ֵ�������������ȣ��������輰���������йأ���˴˴�����10��100��A�ı�ʵ�ʵ���*/
				}
				else
				{
					V_ulCurrentType = 0x00005000;	/*ʵ�����ڵ�����ЧֵΪ1.5Aʱ��sum1Ϊ0x00006000����*/
				}
				
				if (V_ulsum1 >= V_ulCurrentType)	/*�޳�С��������������*/
				{
					V_fFundamentalRate = ( (float)V_ulsum1) / ( (float)V_ulFundamental[V_uschl]);

					if ( (V_fFundamentalRate < 0.9) || (V_fFundamentalRate > 1.1) )		/*�ж������ܲ��Ļ���ֵ�Ƿ���10%����*/
					{
						GV_lHD2Rate[3 + V_uschl] = 0;
					}
					else
					{
						V_ullsum2 = 1000 * (ulong64)V_ulsum2;
						GV_lHD2Rate[3 + V_uschl] = V_ullsum2 / V_ulsum1;				/*����1000��*/
					}

				}
				else
				{
					GV_lHD2Rate[3 + V_uschl] = 0;
				}
			}

			/*�ж�г���������Ƿ���30%~50%֮��*/
			if ( ( (GV_lHD2Rate[0] < C_HD2Rate_Low) || (GV_lHD2Rate[0] > C_HD2Rate_High) || (GV_lHD2Rate[3] > C_HD2Rate_High) || (GV_lHD2Rate[3] > C_HD2Rate_High) ) &&
                 ( (GV_lHD2Rate[1] < C_HD2Rate_Low) || (GV_lHD2Rate[1] > C_HD2Rate_High) || (GV_lHD2Rate[4] > C_HD2Rate_High) || (GV_lHD2Rate[4] > C_HD2Rate_High) ) &&
                 ( (GV_lHD2Rate[2] < C_HD2Rate_Low) || (GV_lHD2Rate[2] > C_HD2Rate_High) || (GV_lHD2Rate[5] > C_HD2Rate_High) || (GV_lHD2Rate[5] > C_HD2Rate_High) ) )	/*40%��ƽ������1000��*/
			{
				SF_ClearUlongArray( (ulong32 *)GV_lHD2Rate, CL_HD2Rate);				/*ż��г������������*/				
				return;		/*�˳�ż��г����������*/
			}

		}break;

		default:
		{
			SF_ClearUlongArray( (ulong32 *)GV_lHD2Rate, CL_HD2Rate);					/*ż��г������������*/			
			GV_ucStepNum = 0;
		}break;
	}
}

/**********************************************************************************
����ԭ�ͣ�void SF_GetEvenHarmonicCompensationValue( ushort16 *pV_usCompTemp );
������������ȡż��г������ֵ
���������ushort16 *pV_usCompTemp:
���������ushort16 *pV_usCompTemp:
���ز�������
����˵����
���û��ƣ�
��    ע���˺����������ڵ��㲹��
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

	/*��ȡż��г��������Χ*/
	if ( SF_GetEvenHarmonicCurrent( &Str_CurrentLimit ) != C_OK )
	{
		for ( V_ucI = 0; V_ucI < 3; V_ucI ++ )
		{
			*(pV_usCompTemp + V_ucI) = 0;
		}
		return;
	}

	/*��ȡABC��ż��г�����ϵ��*/
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

	/*��ȡ��ǰ����ֵHex*/
	for ( V_ucI = 0; V_ucI < 3; V_ucI ++ )
	{
		/*������Чֵ����һλС������ֹ��������������д�������ݵ�����о*/
		V_ulCurrentTemp[V_ucI] = SF_ABS(GStr_HEX_VARREGTYPE.VRmsIRegHEX_ABC[V_ucI] & 0xFFFFFF00);
	}

	/*�������ż��г������ֵ*/
	for ( V_ucI = 0; V_ucI < 3; V_ucI ++ )
	{
		/*���ȼ������ֵ*/
		/*y=kx+b,k,bֵ��ʵ������100����xֵ��ʵ������1000�������yֵ��ʵ������100000��*/
		V_lCompTemp[V_ucI] = ( (long32)(*( &Str_EvenHarmonicError.V_usDataTemp_ABC1[V_ucI] ) ) * (long32)( V_ulCurrentTemp[V_ucI]) )
							+ (long32)( *( &Str_EvenHarmonicError.V_usDataTemp_ABC0[V_ucI] ) ) * 1000;

		/*Ȼ����㲹��ֵ*/
		/*ԭ��ʽΪV_lCompTemp = (((((0 - V_lCompTemp)/100)*1000)/ 1732)/100000) * 32768)+65536;
		�򻯹�ʽΪV_lCompTemp = (((((0 - V_lCompTemp )/ 1732)/10000) * 32768)+65536;*/
		V_lCompTemp[V_ucI] = ( ( ( (0 - V_lCompTemp[V_ucI] ) / 1732) * 32768) / 10000) + 65536;

		/*�Բ���ֵ������������ת��*/
		V_ulCompValue[V_ucI] = (ulong32)V_lCompTemp[V_ucI];

		memset( &V_ucDataBuff[0], 0x00, 6 );

		PF_Ulong32ToBufferX(&V_ucDataBuff[0], &V_ulCompValue[V_ucI], 2);

		PF_Buffer2ToUshort16(&V_ucDataBuff[0], (pV_usCompTemp + V_ucI) );
	}

		/*�ж�г���������Ƿ���30%~50%֮��,�ҵ����ڹ涨��Χ��,���ڷ�Χ�ڲ���ֵ����*/
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
����ԭ�ͣ�void SF_EvenHarmonicCompensation( ushort16 *pV_usCompTemp, uchar8 V_ucRegAddress )
�������������и���ż��г�����в���
���������ushort16 *pV_usCompTemp, uchar8 V_ucRegAddress
�����������
���ز�������
����˵����
���û��ƣ�GV_EvenHarmonicFlag == C_DoEvenHarmonicFlag ����ż��г������
��    ע��ż��г������������30%С��50%����ʾ����ż��г��״̬
***********************************************************************************/
void SF_EvenHarmonicCompensation( ushort16 *pV_usCompTemp, uchar8 V_ucRegAddress )
{
	uchar8 V_ucI = 0;
	uchar8 V_ucDataBuff1[C_CalDataLen] = {0}, V_ucDataBuff2[C_CalDataLen] = {0}, V_ucDataLength = 0;
	short16 V_sCompData = 0;
	ushort16 V_usCalDataTemp = 0, V_usCompData = 0, V_usCalData = 0;
	/*����ż��г������*/
	for (V_ucI = 0; V_ucI < 3; V_ucI ++)
	{
		/*��ȡE2��У������*/
		V_ucDataLength = C_CalDataLen;
		if ( InF_Read_RecMeterData( (V_ucRegAddress + V_ucI), &V_ucDataBuff1[0], &V_ucDataLength ) != C_OK )
		{
			continue;
		}

		PF_Buffer2ToUshort16( &V_ucDataBuff1[0], &V_usCalDataTemp);

		V_sCompData = (short16)*(pV_usCompTemp + V_ucI) + (short16)V_usCalDataTemp;

		V_usCompData = (ushort16)V_sCompData;

		PF_Ushort16ToBuffer2( &V_ucDataBuff1[0], &V_usCompData );

		/*У������д�����о֮ǰ���Ƚ������Ƿ�һ�£�һ������д��*/
		SF_ReadOneReg_MeterIC( (V_ucRegAddress + V_ucI), &V_ucDataBuff2[0], C_ReadCalDataRegFlag );

		PF_Buffer2ToUshort16( &V_ucDataBuff2[0], &V_usCalData );

		if (PF_Campare_Data( &V_ucDataBuff1[0], &V_ucDataBuff2[0], 2) != C_Equal )
		{
			SF_WriteOneReg_MeterIC( &V_ucDataBuff1[0], (V_ucRegAddress + V_ucI), C_DataSafe );

			if ( ( (V_ucRegAddress + V_ucI) > 0x03 ) && ( (V_ucRegAddress + V_ucI) < 0x13 ) )
			{
				GV_ulCalDataChk0SUM = GV_ulCalDataChk0SUM - V_usCalData + V_usCompData;		/*����У���*/
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
����ԭ��: uchar8 SF_Test_MeterIC()
��������: ��ȡУ��Ĵ�������У��������м���ó�У������ݣ�Ȼ��ͼĴ����ж�ȡ����У������ݽ��жԱȣ��������ȷ��������Ӧ��־����ʼ��
�������: ��
�������: ��
���ز���: C_OK������C_Error�쳣
����λ��: 
��    ע: 
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
����ԭ��: SF_Cal1minPowerSum(Str_PowerAdd_Type *pStr_PowerAdd, Str_RealtimePower_Type *pStr_RealtimePower)
��������: 1min�����ۼӺͼ��� 
�������: Str_PowerAdd_Type *pStr_PowerAdd: 1min�����ۼӽṹ��
          Str_RealtimePower_Type *pStr_RealtimePower��ʵʱ���ʽṹ��
�������: ��
���ز���: ��
����λ��: 
��    ע: ÿ1s����1��
*******************************************************************************/
void SF_Cal1minPowerSum(Str_PowerAdd_Type *pStr_PowerAdd, Str_RealtimePower_Type *pStr_RealtimePower)
{
	uchar8 V_uci;

	pStr_PowerAdd->Number++;
	for (V_uci = 0; V_uci < 4; V_uci++)
	{
	/*********************************��ABC�й����ʴ���**********************************************/
		pStr_PowerAdd->ActivePowerSummer_TABC[V_uci] += pStr_RealtimePower->ActivePower_TABC[V_uci];
		
	/*********************************��ABC�޹����ʴ���**********************************************/
		pStr_PowerAdd->ReativePowerSummer_TABC[V_uci] += pStr_RealtimePower->ReativePower_TABC[V_uci];
	}
}

/*******************************************************************************
����ԭ��: void SF_Cal1minAveragePower(Str_PowerAdd_Type *pStr_PowerAdd)  
��������: ����1minƽ������ 
�������: Str_PowerAdd_Type *pStr_PowerAdd��1min�����ۼӽṹ��
�������: ��
���ز���: ��
����λ��: 
��    ע: ϵͳ���ӱ仯ʱ���ã����ú�1min�����ۼӽṹ����������
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

	/*************************���ȼ���1minƽ������*****************************/
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
		
		*pV_lldata = 0;			/*�����ۼӺ�����*/
		pV_lldata++;

		PF_Ulong64ToBuffer8(V_ucBuffer, (ulong64 *)&V_llPower, 8);
		InF_Write_Data(C_Msg_MeterIC, V_ulComDemandRAMAddeTable[V_uci], V_ucBuffer, CLOneMin_AcPower, C_W_SafeFlag);
	}

    pStr_PowerAdd->Number = 0;	/*�ۼƴ�������*/
}

/*******************************************************************************
����ԭ��: void SF_ClrCurrentPower(void)
��������: ����ǰ1����ƽ����������
�������: ��
�������: ��
���ز���: ��
����λ��: 
��    ע: 
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
����ԭ�ͣ�uchar8 InF_Get_MeterICModule(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, ushort16 *pV_usDataEncode)
������������˲ʱ���ӿ�
���������V_ulOAD:��Ҫ��ȡ��OAD��
          pV_ucDataBuf:��ȡ���ݵĻ�����׵�ַ
          *pV_usDataLen:��ȡ���ݵĻ������󳤶ȣ�
���������pV_ucDataBuf:��ȡ���ݵĻ�����׵�ַ
          *pV_usDataLen:��ȡ����ʵ�ʳ��ȣ�
          *pV_usDataEncode:�����ڲ����룻
���ز�����C_OK,��ȡ�ɹ�;��������;
����λ�ã���������
��    ע��
************************************************************************************************************************************/
uchar8 InF_Get_MeterICModule(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, ushort16 *pV_usDataEncode)
{
	uchar8 V_uci, V_ucFlag = C_Error;
	ulong32 V_ulOneMin_AcPower[C_PowerTypeNum][2] = {{COneMin_AcPower,   COneMin_AcPower_Pre},	/*4λС��ƽ�����ʺ�6λС��ƽ������*/
                                                     {COneMin_AcPower_A, COneMin_AcPower_A_Pre},
                                                     {COneMin_AcPower_B, COneMin_AcPower_B_Pre},
                                                     {COneMin_AcPower_C, COneMin_AcPower_C_Pre},
                                                     {COneMin_RePower,   COneMin_RePower_Pre},
                                                     {COneMin_RePower_A, COneMin_RePower_A_Pre},
                                                     {COneMin_RePower_B, COneMin_RePower_B_Pre},
                                                     {COneMin_RePower_C, COneMin_RePower_C_Pre}};
        
	ulong32 V_ulCurr_3ig[3][2] = {{CPhaseA_Curr,   CPhaseA_Curr_4Dig},	/*3λС��������4λС������*/
                                  {CPhaseB_Curr,   CPhaseB_Curr_4Dig},
                                  {CPhaseC_Curr,   CPhaseC_Curr_4Dig}};
    
	ulong32 V_ulFFTab[] = {CInstantFF_AcPow,			/*�й��������ݿ�*/
                           CInstantFF_RePow,			/*�޹��������ݿ�*/
                           CInstantFF_AppaPow,		    /*˲ʱ���ڹ������ݿ�*/
                           CPhaseFF_Curr_4Dig,		    /*�������ݿ�*/
                           CPhaseFF_Volage,			    /*��ѹ���ݿ�*/
                           CPhaseFF_PowerFactor,		/*�����������ݿ�*/
                           CPhaseFF_Angle,			    /*������ݿ�*/
                           CVolFF_Phase,				/*��ѹ������ݿ�*/
                           CCurrFF_Phase,			    /*����������ݿ�*/
                           COneMin_AcPower_Pre_FF,      /*1�����й���ƽ���������ݿ�(6λС��)*/
                           COneMin_RePower_Pre_FF};     /*1�����޹���ƽ���������ݿ�(6λС��)*/

	/*�Ƿ��3λС���������ǵĻ������ݲ��4λС����������ת����3λС��*/
	for (V_uci = 0; V_uci < 3; V_uci++)
	{
		if (V_ulCurr_3ig[V_uci][0] == V_ulOAD)
		{
			V_ucFlag = InF_Read_Data(V_ulCurr_3ig[V_uci][1], pV_ucDataBuf, pV_usDataLen, pV_usDataEncode);
			SF_LessData(pV_ucDataBuf, 10);		/*������С10��*/
			return V_ucFlag;
		}
	}

	/*�Ƿ������ݲ��˲ʱ��*/
	for (V_uci = 0; V_uci < C_InstantNum; V_uci++)
	{
		if (Str_DataProcess[V_uci].C_InstantOAD == V_ulOAD)   
		{
			V_ucFlag = InF_Read_Data(V_ulOAD, pV_ucDataBuf, pV_usDataLen, pV_usDataEncode);
			return V_ucFlag;
		}
	}

	/*�Ƿ���1minƽ������6λС��*/
	for (V_uci = 0; V_uci < C_PowerTypeNum; V_uci++)
	{
		if (V_ulOAD == V_ulOneMin_AcPower[V_uci][1])
		{
			V_ucFlag = InF_Read_Data(V_ulOAD, pV_ucDataBuf, pV_usDataLen, pV_usDataEncode);
			return V_ucFlag;
		}
	}

	/*�Ƿ���1minƽ������4λС��*/
	for (V_uci = 0; V_uci < C_PowerTypeNum; V_uci++)
	{
		if (V_ulOAD == V_ulOneMin_AcPower[V_uci][0])
		{
			V_ucFlag = InF_Read_Data(V_ulOneMin_AcPower[V_uci][1], pV_ucDataBuf, pV_usDataLen, pV_usDataEncode);
			if (V_ucFlag == C_OK)
			{ 
				SF_6digpowTo4digpow(pV_ucDataBuf);	/*6λС��ת��4λС��������������*/
			}
			return V_ucFlag;
		}
	}

	/*�Ƿ��������Ŀ鳭��*/
	for (V_uci = 0; V_uci < (sizeof(V_ulFFTab)/sizeof(ulong32) ); V_uci++)
	{
		if (V_ulOAD == V_ulFFTab[V_uci])
		{
			V_ucFlag = InF_Read_Data(V_ulOAD, pV_ucDataBuf, pV_usDataLen, pV_usDataEncode);
			return V_ucFlag;
		}
	}

	/*3λС�������鳭��*/
	if (V_ulOAD == CPhaseFF_Curr)
	{
		V_ucFlag = InF_Read_Data(CPhaseFF_Curr_4Dig, pV_ucDataBuf, pV_usDataLen, pV_usDataEncode);
		if (V_ucFlag == C_OK)
		{
			for (V_uci = 0; V_uci < 3; V_uci++)    /*ABC����ֱ���С10��*/
			{
				SF_LessData(&pV_ucDataBuf[V_uci * CLPhaseA_Curr], 10);
			}
		}
		return V_ucFlag;
	}

	/*4λС��1minƽ�����ʿ鳭��*/
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
			for (V_uci = 0; V_uci < 4; V_uci++)    /*TABC��4��*/
			{
				SF_6digpowTo4digpow(&pV_ucDataBuf[V_uci * COneMin_AcPower_Pre] );   /*6λС��ת��4λС��������������*/
			}
		}
		return V_ucFlag;
	}
	return V_ucFlag;
}

/**********************************************************************************************************************************
����ԭ�ͣ�void SF_LessData(uchar8 *pV_ucDataBuf, ushort16 V_ustemp)
�����������ѻ��������������С���ٱ�����ʱֻ֧��4�ֽ����ݣ����ڶ�������4λС������ת����3λС������
���������uchar8 *pV_ucDataBuf��Ҫת���������׵�ַ
          ushort16 V_ustemp:��С���ٱ�
���������uchar8 *pV_ucDataBuf����С��������׵�ַ
���ز�������
����λ�ã�
��    ע��
************************************************************************************************************************************/
void SF_LessData(uchar8 *pV_ucDataBuf, ushort16 V_ustemp)
{
	long32 V_ldata;
	PF_BufferXToUlong32(pV_ucDataBuf, (ulong32 *)&V_ldata, 4);
	V_ldata /= V_ustemp;
	PF_Ulong32ToBufferX(pV_ucDataBuf, (ulong32 *)&V_ldata, 4);
}

/**********************************************************************************************************************************
����ԭ�ͣ�void SF_6digpowTo4digpow(uchar8 *pV_ucDataBuf)
������������6λС����ƽ������ת����4λС����ƽ�����ʣ�����������
���������uchar8 *pV_ucDataBuf��Ҫת���������׵�ַ
���������uchar8 *pV_ucDataBuf��ת����������׵�ַ
���ز�������
����λ�ã��ڲ����ڶ�������4λС������ת����3λС������
��    ע��
************************************************************************************************************************************/
void SF_6digpowTo4digpow(uchar8 *pV_ucDataBuf)
{
	long32 V_ldata;
	PF_BufferXToUlong32(pV_ucDataBuf, (ulong32 *)&V_ldata, 4);
	if (V_ldata > 0)
	{
		if ( (V_ldata % 100) >= 50)				/*��������*/
		{
			V_ldata += 100;
		}
	}
	else
	{
		if ( (SF_ABS(V_ldata) % 100) >= 50)		/*��������*/
		{
			V_ldata -= 100;
		}
	}
	V_ldata /= 100;								/*����4��С��λ*/

	PF_Ulong32ToBufferX(pV_ucDataBuf, (ulong32 *)&V_ldata, 4);
}

/**********************************************************************************************************************************
����ԭ�ͣ�void Inf_deal_EvenHarmonicDelayTimer()
������������time.cģ��50ms����еݼ�
�����������
�����������
���ز�������
����λ�ã�
��    ע��
************************************************************************************************************************************/
void Inf_deal_EvenHarmonicDelayTimer()
{
	if( GV_ucEvenHarmonicDelayTimer != 0 )
	{
		GV_ucEvenHarmonicDelayTimer--;
	}
}
